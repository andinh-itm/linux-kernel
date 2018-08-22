/*
 * Bitbanging I2C bus driver using the GPIO API
 *
 * Copyright (C) 2007 Atmel Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/i2c-algo-bit.h>
#include <linux/platform_data/i2c-gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/gpio/consumer.h>
#include <linux/of.h>

struct i2c_gpio_private_data {
	struct gpio_desc *sda;
	struct gpio_desc *scl;
	struct i2c_adapter adap;
	struct i2c_algo_bit_data bit_data;
	struct i2c_gpio_platform_data pdata;
#ifdef CONFIG_I2C_GPIO_FAULT_INJECTOR
	struct dentry *debug_dir;
#endif
};

/*
 * Toggle SDA by changing the output value of the pin. This is only
 * valid for pins configured as open drain (i.e. setting the value
 * high effectively turns off the output driver.)
 */
static void i2c_gpio_setsda_val(void *data, int state)
{
	struct i2c_gpio_private_data *priv = data;

	gpiod_set_value_cansleep(priv->sda, state);
}

/*
 * Toggle SCL by changing the output value of the pin. This is used
 * for pins that are configured as open drain and for output-only
 * pins. The latter case will break the i2c protocol, but it will
 * often work in practice.
 */
static void i2c_gpio_setscl_val(void *data, int state)
{
	struct i2c_gpio_private_data *priv = data;

	gpiod_set_value_cansleep(priv->scl, state);
}

static int i2c_gpio_getsda(void *data)
{
	struct i2c_gpio_private_data *priv = data;

	return gpiod_get_value_cansleep(priv->sda);
}

static int i2c_gpio_getscl(void *data)
{
	struct i2c_gpio_private_data *priv = data;

	return gpiod_get_value_cansleep(priv->scl);
}

#ifdef CONFIG_I2C_GPIO_FAULT_INJECTOR
static struct dentry *i2c_gpio_debug_dir;

#define setsda(bd, val)	((bd)->setsda((bd)->data, val))
#define setscl(bd, val)	((bd)->setscl((bd)->data, val))
#define getsda(bd)	((bd)->getsda((bd)->data))
#define getscl(bd)	((bd)->getscl((bd)->data))

#define WIRE_ATTRIBUTE(wire) \
static int fops_##wire##_get(void *data, u64 *val)	\
{							\
	struct i2c_gpio_private_data *priv = data;	\
							\
	i2c_lock_adapter(&priv->adap);			\
	*val = get##wire(&priv->bit_data);		\
	i2c_unlock_adapter(&priv->adap);		\
	return 0;					\
}							\
static int fops_##wire##_set(void *data, u64 val)	\
{							\
	struct i2c_gpio_private_data *priv = data;	\
							\
	i2c_lock_adapter(&priv->adap);			\
	set##wire(&priv->bit_data, val);		\
	i2c_unlock_adapter(&priv->adap);		\
	return 0;					\
}							\
DEFINE_DEBUGFS_ATTRIBUTE(fops_##wire, fops_##wire##_get, fops_##wire##_set, "%llu\n")

WIRE_ATTRIBUTE(scl);
WIRE_ATTRIBUTE(sda);

static int fops_incomplete_transfer_set(void *data, u64 addr)
{
	struct i2c_gpio_private_data *priv = data;
	struct i2c_algo_bit_data *bit_data = &priv->bit_data;
	int i, pattern;

	if (addr > 0x7f)
		return -EINVAL;

	/* ADDR (7 bit) + RD (1 bit) + SDA hi (1 bit) */
	pattern = (addr << 2) | 3;

	i2c_lock_adapter(&priv->adap);

	/* START condition */
	setsda(bit_data, 0);
	udelay(bit_data->udelay);

	/* Send ADDR+RD, request ACK, don't send STOP */
	for (i = 8; i >= 0; i--) {
		setscl(bit_data, 0);
		udelay(bit_data->udelay / 2);
		setsda(bit_data, (pattern >> i) & 1);
		udelay((bit_data->udelay + 1) / 2);
		setscl(bit_data, 1);
		udelay(bit_data->udelay);
	}

	i2c_unlock_adapter(&priv->adap);

	return 0;
}
DEFINE_DEBUGFS_ATTRIBUTE(fops_incomplete_transfer, NULL, fops_incomplete_transfer_set, "%llu\n");

static void i2c_gpio_fault_injector_init(struct platform_device *pdev)
{
	struct i2c_gpio_private_data *priv = platform_get_drvdata(pdev);

	/*
	 * If there will be a debugfs-dir per i2c adapter somewhen, put the
	 * 'fault-injector' dir there. Until then, we have a global dir with
	 * all adapters as subdirs.
	 */
	if (!i2c_gpio_debug_dir) {
		i2c_gpio_debug_dir = debugfs_create_dir("i2c-fault-injector", NULL);
		if (!i2c_gpio_debug_dir)
			return;
	}

	priv->debug_dir = debugfs_create_dir(pdev->name, i2c_gpio_debug_dir);
	if (!priv->debug_dir)
		return;

	debugfs_create_file_unsafe("scl", 0600, priv->debug_dir, priv, &fops_scl);
	debugfs_create_file_unsafe("sda", 0600, priv->debug_dir, priv, &fops_sda);
	debugfs_create_file_unsafe("incomplete_transfer", 0200, priv->debug_dir,
				   priv, &fops_incomplete_transfer);
}

static void i2c_gpio_fault_injector_exit(struct platform_device *pdev)
{
	struct i2c_gpio_private_data *priv = platform_get_drvdata(pdev);

	debugfs_remove_recursive(priv->debug_dir);
}
#else
static inline void i2c_gpio_fault_injector_init(struct platform_device *pdev) {}
static inline void i2c_gpio_fault_injector_exit(struct platform_device *pdev) {}
#endif /* CONFIG_I2C_GPIO_FAULT_INJECTOR*/

static void of_i2c_gpio_get_props(struct device_node *np,
				  struct i2c_gpio_platform_data *pdata)
{
	u32 reg;

	of_property_read_u32(np, "i2c-gpio,delay-us", &pdata->udelay);

	if (!of_property_read_u32(np, "i2c-gpio,timeout-ms", &reg))
		pdata->timeout = msecs_to_jiffies(reg);

	pdata->sda_is_open_drain =
		of_property_read_bool(np, "i2c-gpio,sda-open-drain");
	pdata->scl_is_open_drain =
		of_property_read_bool(np, "i2c-gpio,scl-open-drain");
	pdata->scl_is_output_only =
		of_property_read_bool(np, "i2c-gpio,scl-output-only");
}

static struct gpio_desc *i2c_gpio_get_desc(struct device *dev,
					   const char *con_id,
					   unsigned int index,
					   enum gpiod_flags gflags)
{
	struct gpio_desc *retdesc;
	int ret;

	retdesc = devm_gpiod_get(dev, con_id, gflags);
	if (!IS_ERR(retdesc)) {
		dev_dbg(dev, "got GPIO from name %s\n", con_id);
		return retdesc;
	}

	retdesc = devm_gpiod_get_index(dev, NULL, index, gflags);
	if (!IS_ERR(retdesc)) {
		dev_dbg(dev, "got GPIO from index %u\n", index);
		return retdesc;
	}

	ret = PTR_ERR(retdesc);

	/* FIXME: hack in the old code, is this really necessary? */
	if (ret == -EINVAL)
		retdesc = ERR_PTR(-EPROBE_DEFER);

	/* This happens if the GPIO driver is not yet probed, let's defer */
	if (ret == -ENOENT)
		retdesc = ERR_PTR(-EPROBE_DEFER);

	if (ret != -EPROBE_DEFER)
		dev_err(dev, "error trying to get descriptor: %d\n", ret);

	return retdesc;
}

static int i2c_gpio_probe(struct platform_device *pdev)
{
	struct i2c_gpio_private_data *priv;
	struct i2c_gpio_platform_data *pdata;
	struct i2c_algo_bit_data *bit_data;
	struct i2c_adapter *adap;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	enum gpiod_flags gflags;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	adap = &priv->adap;
	bit_data = &priv->bit_data;
	pdata = &priv->pdata;

	if (np) {
		of_i2c_gpio_get_props(np, pdata);
	} else {
		/*
		 * If all platform data settings are zero it is OK
		 * to not provide any platform data from the board.
		 */
		if (dev_get_platdata(dev))
			memcpy(pdata, dev_get_platdata(dev), sizeof(*pdata));
	}

	/*
	 * First get the GPIO pins; if it fails, we'll defer the probe.
	 * If the SDA line is marked from platform data or device tree as
	 * "open drain" it means something outside of our control is making
	 * this line being handled as open drain, and we should just handle
	 * it as any other output. Else we enforce open drain as this is
	 * required for an I2C bus.
	 */
	if (pdata->sda_is_open_drain)
		gflags = GPIOD_OUT_HIGH;
	else
		gflags = GPIOD_OUT_HIGH_OPEN_DRAIN;
	priv->sda = i2c_gpio_get_desc(dev, "sda", 0, gflags);
	if (IS_ERR(priv->sda))
		return PTR_ERR(priv->sda);

	/*
	 * If the SCL line is marked from platform data or device tree as
	 * "open drain" it means something outside of our control is making
	 * this line being handled as open drain, and we should just handle
	 * it as any other output. Else we enforce open drain as this is
	 * required for an I2C bus.
	 */
	if (pdata->scl_is_open_drain)
		gflags = GPIOD_OUT_HIGH;
	else
		gflags = GPIOD_OUT_HIGH_OPEN_DRAIN;
	priv->scl = i2c_gpio_get_desc(dev, "scl", 1, gflags);
	if (IS_ERR(priv->scl))
		return PTR_ERR(priv->scl);

	if (gpiod_cansleep(priv->sda) || gpiod_cansleep(priv->scl))
		dev_warn(dev, "Slow GPIO pins might wreak havoc into I2C/SMBus bus timing");

	bit_data->setsda = i2c_gpio_setsda_val;
	bit_data->setscl = i2c_gpio_setscl_val;

	if (!pdata->scl_is_output_only)
		bit_data->getscl = i2c_gpio_getscl;
	bit_data->getsda = i2c_gpio_getsda;

	if (pdata->udelay)
		bit_data->udelay = pdata->udelay;
	else if (pdata->scl_is_output_only)
		bit_data->udelay = 50;			/* 10 kHz */
	else
		bit_data->udelay = 5;			/* 100 kHz */

	if (pdata->timeout)
		bit_data->timeout = pdata->timeout;
	else
		bit_data->timeout = HZ / 10;		/* 100 ms */

	bit_data->data = priv;

	adap->owner = THIS_MODULE;
	if (np)
		strlcpy(adap->name, dev_name(dev), sizeof(adap->name));
	else
		snprintf(adap->name, sizeof(adap->name), "i2c-gpio%d", pdev->id);

	adap->algo_data = bit_data;
	adap->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	adap->dev.parent = dev;
	adap->dev.of_node = np;

	adap->nr = pdev->id;
	ret = i2c_bit_add_numbered_bus(adap);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, priv);

	/*
	 * FIXME: using global GPIO numbers is not helpful. If/when we
	 * get accessors to get the actual name of the GPIO line,
	 * from the descriptor, then provide that instead.
	 */
	dev_info(dev, "using lines %u (SDA) and %u (SCL%s)\n",
		 desc_to_gpio(priv->sda), desc_to_gpio(priv->scl),
		 pdata->scl_is_output_only
		 ? ", no clock stretching" : "");

	i2c_gpio_fault_injector_init(pdev);

	return 0;
}

static int i2c_gpio_remove(struct platform_device *pdev)
{
	struct i2c_gpio_private_data *priv;
	struct i2c_adapter *adap;

	i2c_gpio_fault_injector_exit(pdev);

	priv = platform_get_drvdata(pdev);
	adap = &priv->adap;

	i2c_del_adapter(adap);

	return 0;
}

#if defined(CONFIG_OF)
static const struct of_device_id i2c_gpio_dt_ids[] = {
	{ .compatible = "i2c-gpio", },
	{ /* sentinel */ }
};

MODULE_DEVICE_TABLE(of, i2c_gpio_dt_ids);
#endif

static struct platform_driver i2c_gpio_driver = {
	.driver		= {
		.name	= "i2c-gpio",
		.of_match_table	= of_match_ptr(i2c_gpio_dt_ids),
	},
	.probe		= i2c_gpio_probe,
	.remove		= i2c_gpio_remove,
};

static int __init i2c_gpio_init(void)
{
	int ret;

	ret = platform_driver_register(&i2c_gpio_driver);
	if (ret)
		printk(KERN_ERR "i2c-gpio: probe failed: %d\n", ret);

	return ret;
}
subsys_initcall(i2c_gpio_init);

static void __exit i2c_gpio_exit(void)
{
	platform_driver_unregister(&i2c_gpio_driver);
}
module_exit(i2c_gpio_exit);

MODULE_AUTHOR("Haavard Skinnemoen (Atmel)");
MODULE_DESCRIPTION("Platform-independent bitbanging I2C driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:i2c-gpio");
newcodenewcodenewcodenewcodenewcodenewcodenewcode
