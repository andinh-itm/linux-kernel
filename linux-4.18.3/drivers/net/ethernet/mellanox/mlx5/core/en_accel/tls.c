/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <linux/netdevice.h>
#include <net/ipv6.h>
#include "en_accel/tls.h"
#include "accel/tls.h"

static void mlx5e_tls_set_ipv4_flow(void *flow, struct sock *sk)
{
	struct inet_sock *inet = inet_sk(sk);

	MLX5_SET(tls_flow, flow, ipv6, 0);
	memcpy(MLX5_ADDR_OF(tls_flow, flow, dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
	       &inet->inet_daddr, MLX5_FLD_SZ_BYTES(ipv4_layout, ipv4));
	memcpy(MLX5_ADDR_OF(tls_flow, flow, src_ipv4_src_ipv6.ipv4_layout.ipv4),
	       &inet->inet_rcv_saddr, MLX5_FLD_SZ_BYTES(ipv4_layout, ipv4));
}

#if IS_ENABLED(CONFIG_IPV6)
static void mlx5e_tls_set_ipv6_flow(void *flow, struct sock *sk)
{
	struct ipv6_pinfo *np = inet6_sk(sk);

	MLX5_SET(tls_flow, flow, ipv6, 1);
	memcpy(MLX5_ADDR_OF(tls_flow, flow, dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
	       &sk->sk_v6_daddr, MLX5_FLD_SZ_BYTES(ipv6_layout, ipv6));
	memcpy(MLX5_ADDR_OF(tls_flow, flow, src_ipv4_src_ipv6.ipv6_layout.ipv6),
	       &np->saddr, MLX5_FLD_SZ_BYTES(ipv6_layout, ipv6));
}
#endif

static void mlx5e_tls_set_flow_tcp_ports(void *flow, struct sock *sk)
{
	struct inet_sock *inet = inet_sk(sk);

	memcpy(MLX5_ADDR_OF(tls_flow, flow, src_port), &inet->inet_sport,
	       MLX5_FLD_SZ_BYTES(tls_flow, src_port));
	memcpy(MLX5_ADDR_OF(tls_flow, flow, dst_port), &inet->inet_dport,
	       MLX5_FLD_SZ_BYTES(tls_flow, dst_port));
}

static int mlx5e_tls_set_flow(void *flow, struct sock *sk, u32 caps)
{
	switch (sk->sk_family) {
	case AF_INET:
		mlx5e_tls_set_ipv4_flow(flow, sk);
		break;
#if IS_ENABLED(CONFIG_IPV6)
	case AF_INET6:
		if (!sk->sk_ipv6only &&
		    ipv6_addr_type(&sk->sk_v6_daddr) == IPV6_ADDR_MAPPED) {
			mlx5e_tls_set_ipv4_flow(flow, sk);
			break;
		}
		if (!(caps & MLX5_ACCEL_TLS_IPV6))
			goto error_out;

		mlx5e_tls_set_ipv6_flow(flow, sk);
		break;
#endif
	default:
		goto error_out;
	}

	mlx5e_tls_set_flow_tcp_ports(flow, sk);
	return 0;
error_out:
	return -EINVAL;
}

static int mlx5e_tls_add(struct net_device *netdev, struct sock *sk,
			 enum tls_offload_ctx_dir direction,
			 struct tls_crypto_info *crypto_info,
			 u32 start_offload_tcp_sn)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct mlx5_core_dev *mdev = priv->mdev;
	u32 caps = mlx5_accel_tls_device_caps(mdev);
	int ret = -ENOMEM;
	void *flow;

	if (direction != TLS_OFFLOAD_CTX_DIR_TX)
		return -EINVAL;

	flow = kzalloc(MLX5_ST_SZ_BYTES(tls_flow), GFP_KERNEL);
	if (!flow)
		return ret;

	ret = mlx5e_tls_set_flow(flow, sk, caps);
	if (ret)
		goto free_flow;

	if (direction == TLS_OFFLOAD_CTX_DIR_TX) {
		struct mlx5e_tls_offload_context *tx_ctx =
		    mlx5e_get_tls_tx_context(tls_ctx);
		u32 swid;

		ret = mlx5_accel_tls_add_tx_flow(mdev, flow, crypto_info,
						 start_offload_tcp_sn, &swid);
		if (ret < 0)
			goto free_flow;

		tx_ctx->swid = htonl(swid);
		tx_ctx->expected_seq = start_offload_tcp_sn;
	}

	return 0;
free_flow:
	kfree(flow);
	return ret;
}

static void mlx5e_tls_del(struct net_device *netdev,
			  struct tls_context *tls_ctx,
			  enum tls_offload_ctx_dir direction)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);

	if (direction == TLS_OFFLOAD_CTX_DIR_TX) {
		u32 swid = ntohl(mlx5e_get_tls_tx_context(tls_ctx)->swid);

		mlx5_accel_tls_del_tx_flow(priv->mdev, swid);
	} else {
		netdev_err(netdev, "unsupported direction %d\n", direction);
	}
}

static const struct tlsdev_ops mlx5e_tls_ops = {
	.tls_dev_add = mlx5e_tls_add,
	.tls_dev_del = mlx5e_tls_del,
};

void mlx5e_tls_build_netdev(struct mlx5e_priv *priv)
{
	struct net_device *netdev = priv->netdev;

	if (!mlx5_accel_is_tls_device(priv->mdev))
		return;

	netdev->features |= NETIF_F_HW_TLS_TX;
	netdev->hw_features |= NETIF_F_HW_TLS_TX;
	netdev->tlsdev_ops = &mlx5e_tls_ops;
}

int mlx5e_tls_init(struct mlx5e_priv *priv)
{
	struct mlx5e_tls *tls = kzalloc(sizeof(*tls), GFP_KERNEL);

	if (!tls)
		return -ENOMEM;

	priv->tls = tls;
	return 0;
}

void mlx5e_tls_cleanup(struct mlx5e_priv *priv)
{
	struct mlx5e_tls *tls = priv->tls;

	if (!tls)
		return;

	kfree(tls);
	priv->tls = NULL;
}
newcodenewcodenewcodenewcodenewcodenewcodenewcode
