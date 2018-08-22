/*
 * Copyright 2009 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *     Alex Deucher <alexander.deucher@amd.com>
 */

#include <linux/bug.h>
#include <linux/types.h>
#include <linux/kernel.h>

/*
 * R6xx+ cards need to use the 3D engine to blit data which requires
 * quite a bit of hw state setup.  Rather than pull the whole 3D driver
 * (which normally generates the 3D state) into the DRM, we opt to use
 * statically generated state tables.  The register state and shaders
 * were hand generated to support blitting functionality.  See the 3D
 * driver or documentation for descriptions of the registers and
 * shader instructions.
 */

const u32 r6xx_default_state[] =
{
	0xc0002400, /* START_3D_CMDBUF */
	0x00000000,

	0xc0012800, /* CONTEXT_CONTROL */
	0x80000000,
	0x80000000,

	0xc0016800,
	0x00000010,
	0x00008000, /* WAIT_UNTIL */

	0xc0016800,
	0x00000542,
	0x07000003, /* TA_CNTL_AUX */

	0xc0016800,
	0x000005c5,
	0x00000000, /* VC_ENHANCE */

	0xc0016800,
	0x00000363,
	0x00000000, /* SQ_DYN_GPR_CNTL_PS_FLUSH_REQ */

	0xc0016800,
	0x0000060c,
	0x82000000, /* DB_DEBUG */

	0xc0016800,
	0x0000060e,
	0x01020204, /* DB_WATERMARKS */

	0xc0026f00,
	0x00000000,
	0x00000000, /* SQ_VTX_BASE_VTX_LOC */
	0x00000000, /* SQ_VTX_START_INST_LOC */

	0xc0096900,
	0x0000022a,
	0x00000000, /* SQ_ESGS_RING_ITEMSIZE */
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,

	0xc0016900,
	0x00000004,
	0x00000000, /* DB_DEPTH_INFO */

	0xc0026900,
	0x0000000a,
	0x00000000, /* DB_STENCIL_CLEAR */
	0x00000000, /* DB_DEPTH_CLEAR */

	0xc0016900,
	0x00000200,
	0x00000000, /* DB_DEPTH_CONTROL */

	0xc0026900,
	0x00000343,
	0x00000060, /* DB_RENDER_CONTROL */
	0x00000040, /* DB_RENDER_OVERRIDE */

	0xc0016900,
	0x00000351,
	0x0000aa00, /* DB_ALPHA_TO_MASK */

	0xc00f6900,
	0x00000100,
	0x00000800, /* VGT_MAX_VTX_INDX */
	0x00000000, /* VGT_MIN_VTX_INDX */
	0x00000000, /* VGT_INDX_OFFSET */
	0x00000000, /* VGT_MULTI_PRIM_IB_RESET_INDX */
	0x00000000, /* SX_ALPHA_TEST_CONTROL */
	0x00000000, /* CB_BLEND_RED */
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000, /* CB_FOG_RED */
	0x00000000,
	0x00000000,
	0x00000000, /* DB_STENCILREFMASK */
	0x00000000, /* DB_STENCILREFMASK_BF */
	0x00000000, /* SX_ALPHA_REF */

	0xc0046900,
	0x0000030c,
	0x01000000, /* CB_CLRCMP_CNTL */
	0x00000000,
	0x00000000,
	0x00000000,

	0xc0046900,
	0x00000048,
	0x3f800000, /* CB_CLEAR_RED */
	0x00000000,
	0x3f800000,
	0x3f800000,

	0xc0016900,
	0x00000080,
	0x00000000, /* PA_SC_WINDOW_OFFSET */

	0xc00a6900,
	0x00000083,
	0x0000ffff, /* PA_SC_CLIP_RECT_RULE */
	0x00000000, /* PA_SC_CLIPRECT_0_TL */
	0x20002000,
	0x00000000,
	0x20002000,
	0x00000000,
	0x20002000,
	0x00000000,
	0x20002000,
	0x00000000, /* PA_SC_EDGERULE */

	0xc0406900,
	0x00000094,
	0x80000000, /* PA_SC_VPORT_SCISSOR_0_TL */
	0x20002000, /* PA_SC_VPORT_SCISSOR_0_BR */
	0x80000000, /* PA_SC_VPORT_SCISSOR_1_TL */
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x00000000, /* PA_SC_VPORT_ZMIN_0 */
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,

	0xc0026900,
	0x00000292,
	0x00000000, /* PA_SC_MPASS_PS_CNTL */
	0x00004010, /* PA_SC_MODE_CNTL */

	0xc0096900,
	0x00000300,
	0x00000000, /* PA_SC_LINE_CNTL */
	0x00000000, /* PA_SC_AA_CONFIG */
	0x0000002d, /* PA_SU_VTX_CNTL */
	0x3f800000, /* PA_CL_GB_VERT_CLIP_ADJ */
	0x3f800000,
	0x3f800000,
	0x3f800000,
	0x00000000, /* PA_SC_SAMPLE_LOCS_MCTX */
	0x00000000,

	0xc0016900,
	0x00000312,
	0xffffffff, /* PA_SC_AA_MASK */

	0xc0066900,
	0x0000037e,
	0x00000000, /* PA_SU_POLY_OFFSET_DB_FMT_CNTL */
	0x00000000, /* PA_SU_POLY_OFFSET_CLAMP */
	0x00000000, /* PA_SU_POLY_OFFSET_FRONT_SCALE */
	0x00000000, /* PA_SU_POLY_OFFSET_FRONT_OFFSET */
	0x00000000, /* PA_SU_POLY_OFFSET_BACK_SCALE */
	0x00000000, /* PA_SU_POLY_OFFSET_BACK_OFFSET */

	0xc0046900,
	0x000001b6,
	0x00000000, /* SPI_INPUT_Z */
	0x00000000, /* SPI_FOG_CNTL */
	0x00000000, /* SPI_FOG_FUNC_SCALE */
	0x00000000, /* SPI_FOG_FUNC_BIAS */

	0xc0016900,
	0x00000225,
	0x00000000, /* SQ_PGM_START_FS */

	0xc0016900,
	0x00000229,
	0x00000000, /* SQ_PGM_RESOURCES_FS */

	0xc0016900,
	0x00000237,
	0x00000000, /* SQ_PGM_CF_OFFSET_FS */

	0xc0026900,
	0x000002a8,
	0x00000000, /* VGT_INSTANCE_STEP_RATE_0 */
	0x00000000, /* VGT_INSTANCE_STEP_RATE_1 */

	0xc0116900,
	0x00000280,
	0x00000000, /* PA_SU_POINT_SIZE */
	0x00000000, /* PA_SU_POINT_MINMAX */
	0x00000008, /* PA_SU_LINE_CNTL */
	0x00000000, /* PA_SC_LINE_STIPPLE */
	0x00000000, /* VGT_OUTPUT_PATH_CNTL */
	0x00000000, /* VGT_HOS_CNTL */
	0x00000000, /* VGT_HOS_MAX_TESS_LEVEL */
	0x00000000, /* VGT_HOS_MIN_TESS_LEVEL */
	0x00000000, /* VGT_HOS_REUSE_DEPTH */
	0x00000000, /* VGT_GROUP_PRIM_TYPE */
	0x00000000, /* VGT_GROUP_FIRST_DECR */
	0x00000000, /* VGT_GROUP_DECR */
	0x00000000, /* VGT_GROUP_VECT_0_CNTL */
	0x00000000, /* VGT_GROUP_VECT_1_CNTL */
	0x00000000, /* VGT_GROUP_VECT_0_FMT_CNTL */
	0x00000000, /* VGT_GROUP_VECT_1_FMT_CNTL */
	0x00000000, /* VGT_GS_MODE */

	0xc0016900,
	0x000002a1,
	0x00000000, /* VGT_PRIMITIVEID_EN */

	0xc0016900,
	0x000002a5,
	0x00000000, /* VGT_MULTI_PRIM_ID_RESET_EN */

	0xc0036900,
	0x000002ac,
	0x00000000, /* VGT_STRMOUT_EN */
	0x00000000, /* VGT_REUSE_OFF */
	0x00000000, /* VGT_VTX_CNT_EN */

	0xc0016900,
	0x000000d4,
	0x00000000, /* SX_MISC */

	0xc0016900,
	0x000002c8,
	0x00000000, /* VGT_STRMOUT_BUFFER_EN */

	0xc0076900,
	0x00000202,
	0x00cc0000, /* CB_COLOR_CONTROL */
	0x00000210, /* DB_SHADER_CNTL */
	0x00010000, /* PA_CL_CLIP_CNTL */
	0x00000244, /* PA_SU_SC_MODE_CNTL */
	0x00000100, /* PA_CL_VTE_CNTL */
	0x00000000, /* PA_CL_VS_OUT_CNTL */
	0x00000000, /* PA_CL_NANINF_CNTL */

	0xc0026900,
	0x0000008e,
	0x0000000f, /* CB_TARGET_MASK */
	0x0000000f, /* CB_SHADER_MASK */

	0xc0016900,
	0x000001e8,
	0x00000001, /* CB_SHADER_CONTROL */

	0xc0016900,
	0x00000185,
	0x00000000, /* SPI_VS_OUT_ID_0 */

	0xc0016900,
	0x00000191,
	0x00000b00, /* SPI_PS_INPUT_CNTL_0 */

	0xc0056900,
	0x000001b1,
	0x00000000, /* SPI_VS_OUT_CONFIG */
	0x00000000, /* SPI_THREAD_GROUPING */
	0x00000001, /* SPI_PS_IN_CONTROL_0 */
	0x00000000, /* SPI_PS_IN_CONTROL_1 */
	0x00000000, /* SPI_INTERP_CONTROL_0 */

	0xc0036e00, /* SET_SAMPLER */
	0x00000000,
	0x00000012,
	0x00000000,
	0x00000000,
};

const u32 r7xx_default_state[] =
{
	0xc0012800, /* CONTEXT_CONTROL */
	0x80000000,
	0x80000000,

	0xc0016800,
	0x00000010,
	0x00008000, /* WAIT_UNTIL */

	0xc0016800,
	0x00000542,
	0x07000002, /* TA_CNTL_AUX */

	0xc0016800,
	0x000005c5,
	0x00000000, /* VC_ENHANCE */

	0xc0016800,
	0x00000363,
	0x00004000, /* SQ_DYN_GPR_CNTL_PS_FLUSH_REQ */

	0xc0016800,
	0x0000060c,
	0x00000000, /* DB_DEBUG */

	0xc0016800,
	0x0000060e,
	0x00420204, /* DB_WATERMARKS */

	0xc0026f00,
	0x00000000,
	0x00000000, /* SQ_VTX_BASE_VTX_LOC */
	0x00000000, /* SQ_VTX_START_INST_LOC */

	0xc0096900,
	0x0000022a,
	0x00000000, /* SQ_ESGS_RING_ITEMSIZE */
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,

	0xc0016900,
	0x00000004,
	0x00000000, /* DB_DEPTH_INFO */

	0xc0026900,
	0x0000000a,
	0x00000000, /* DB_STENCIL_CLEAR */
	0x00000000, /* DB_DEPTH_CLEAR */

	0xc0016900,
	0x00000200,
	0x00000000, /* DB_DEPTH_CONTROL */

	0xc0026900,
	0x00000343,
	0x00000060, /* DB_RENDER_CONTROL */
	0x00000000, /* DB_RENDER_OVERRIDE */

	0xc0016900,
	0x00000351,
	0x0000aa00, /* DB_ALPHA_TO_MASK */

	0xc0096900,
	0x00000100,
	0x00000800, /* VGT_MAX_VTX_INDX */
	0x00000000, /* VGT_MIN_VTX_INDX */
	0x00000000, /* VGT_INDX_OFFSET */
	0x00000000, /* VGT_MULTI_PRIM_IB_RESET_INDX */
	0x00000000, /* SX_ALPHA_TEST_CONTROL */
	0x00000000, /* CB_BLEND_RED */
	0x00000000,
	0x00000000,
	0x00000000,

	0xc0036900,
	0x0000010c,
	0x00000000, /* DB_STENCILREFMASK */
	0x00000000, /* DB_STENCILREFMASK_BF */
	0x00000000, /* SX_ALPHA_REF */

	0xc0046900,
	0x0000030c, /* CB_CLRCMP_CNTL */
	0x01000000,
	0x00000000,
	0x00000000,
	0x00000000,

	0xc0016900,
	0x00000080,
	0x00000000, /* PA_SC_WINDOW_OFFSET */

	0xc00a6900,
	0x00000083,
	0x0000ffff, /* PA_SC_CLIP_RECT_RULE */
	0x00000000, /* PA_SC_CLIPRECT_0_TL */
	0x20002000,
	0x00000000,
	0x20002000,
	0x00000000,
	0x20002000,
	0x00000000,
	0x20002000,
	0xaaaaaaaa, /* PA_SC_EDGERULE */

	0xc0406900,
	0x00000094,
	0x80000000, /* PA_SC_VPORT_SCISSOR_0_TL */
	0x20002000, /* PA_SC_VPORT_SCISSOR_0_BR */
	0x80000000, /* PA_SC_VPORT_SCISSOR_1_TL */
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x00000000, /* PA_SC_VPORT_ZMIN_0 */
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,
	0x00000000,
	0x3f800000,

	0xc0026900,
	0x00000292,
	0x00000000, /* PA_SC_MPASS_PS_CNTL */
	0x00514000, /* PA_SC_MODE_CNTL */

	0xc0096900,
	0x00000300,
	0x00000000, /* PA_SC_LINE_CNTL */
	0x00000000, /* PA_SC_AA_CONFIG */
	0x0000002d, /* PA_SU_VTX_CNTL */
	0x3f800000, /* PA_CL_GB_VERT_CLIP_ADJ */
	0x3f800000,
	0x3f800000,
	0x3f800000,
	0x00000000, /* PA_SC_SAMPLE_LOCS_MCTX */
	0x00000000,

	0xc0016900,
	0x00000312,
	0xffffffff, /* PA_SC_AA_MASK */

	0xc0066900,
	0x0000037e,
	0x00000000, /* PA_SU_POLY_OFFSET_DB_FMT_CNTL */
	0x00000000, /* PA_SU_POLY_OFFSET_CLAMP */
	0x00000000, /* PA_SU_POLY_OFFSET_FRONT_SCALE */
	0x00000000, /* PA_SU_POLY_OFFSET_FRONT_OFFSET */
	0x00000000, /* PA_SU_POLY_OFFSET_BACK_SCALE */
	0x00000000, /* PA_SU_POLY_OFFSET_BACK_OFFSET */

	0xc0046900,
	0x000001b6,
	0x00000000, /* SPI_INPUT_Z */
	0x00000000, /* SPI_FOG_CNTL */
	0x00000000, /* SPI_FOG_FUNC_SCALE */
	0x00000000, /* SPI_FOG_FUNC_BIAS */

	0xc0016900,
	0x00000225,
	0x00000000, /* SQ_PGM_START_FS */

	0xc0016900,
	0x00000229,
	0x00000000, /* SQ_PGM_RESOURCES_FS */

	0xc0016900,
	0x00000237,
	0x00000000, /* SQ_PGM_CF_OFFSET_FS */

	0xc0026900,
	0x000002a8,
	0x00000000, /* VGT_INSTANCE_STEP_RATE_0 */
	0x00000000, /* VGT_INSTANCE_STEP_RATE_1 */

	0xc0116900,
	0x00000280,
	0x00000000, /* PA_SU_POINT_SIZE */
	0x00000000, /* PA_SU_POINT_MINMAX */
	0x00000008, /* PA_SU_LINE_CNTL */
	0x00000000, /* PA_SC_LINE_STIPPLE */
	0x00000000, /* VGT_OUTPUT_PATH_CNTL */
	0x00000000, /* VGT_HOS_CNTL */
	0x00000000, /* VGT_HOS_MAX_TESS_LEVEL */
	0x00000000, /* VGT_HOS_MIN_TESS_LEVEL */
	0x00000000, /* VGT_HOS_REUSE_DEPTH */
	0x00000000, /* VGT_GROUP_PRIM_TYPE */
	0x00000000, /* VGT_GROUP_FIRST_DECR */
	0x00000000, /* VGT_GROUP_DECR */
	0x00000000, /* VGT_GROUP_VECT_0_CNTL */
	0x00000000, /* VGT_GROUP_VECT_1_CNTL */
	0x00000000, /* VGT_GROUP_VECT_0_FMT_CNTL */
	0x00000000, /* VGT_GROUP_VECT_1_FMT_CNTL */
	0x00000000, /* VGT_GS_MODE */

	0xc0016900,
	0x000002a1,
	0x00000000, /* VGT_PRIMITIVEID_EN */

	0xc0016900,
	0x000002a5,
	0x00000000, /* VGT_MULTI_PRIM_ID_RESET_EN */

	0xc0036900,
	0x000002ac,
	0x00000000, /* VGT_STRMOUT_EN */
	0x00000000, /* VGT_REUSE_OFF */
	0x00000000, /* VGT_VTX_CNT_EN */

	0xc0016900,
	0x000000d4,
	0x00000000, /* SX_MISC */

	0xc0016900,
	0x000002c8,
	0x00000000, /* VGT_STRMOUT_BUFFER_EN */

	0xc0076900,
	0x00000202,
	0x00cc0000, /* CB_COLOR_CONTROL */
	0x00000210, /* DB_SHADER_CNTL */
	0x00010000, /* PA_CL_CLIP_CNTL */
	0x00000244, /* PA_SU_SC_MODE_CNTL */
	0x00000100, /* PA_CL_VTE_CNTL */
	0x00000000, /* PA_CL_VS_OUT_CNTL */
	0x00000000, /* PA_CL_NANINF_CNTL */

	0xc0026900,
	0x0000008e,
	0x0000000f, /* CB_TARGET_MASK */
	0x0000000f, /* CB_SHADER_MASK */

	0xc0016900,
	0x000001e8,
	0x00000001, /* CB_SHADER_CONTROL */

	0xc0016900,
	0x00000185,
	0x00000000, /* SPI_VS_OUT_ID_0 */

	0xc0016900,
	0x00000191,
	0x00000b00, /* SPI_PS_INPUT_CNTL_0 */

	0xc0056900,
	0x000001b1,
	0x00000000, /* SPI_VS_OUT_CONFIG */
	0x00000001, /* SPI_THREAD_GROUPING */
	0x00000001, /* SPI_PS_IN_CONTROL_0 */
	0x00000000, /* SPI_PS_IN_CONTROL_1 */
	0x00000000, /* SPI_INTERP_CONTROL_0 */

	0xc0036e00, /* SET_SAMPLER */
	0x00000000,
	0x00000012,
	0x00000000,
	0x00000000,
};

/* same for r6xx/r7xx */
const u32 r6xx_vs[] =
{
	0x00000004,
	0x81000000,
	0x0000203c,
	0x94000b08,
	0x00004000,
	0x14200b1a,
	0x00000000,
	0x00000000,
	0x3c000000,
	0x68cd1000,
#ifdef __BIG_ENDIAN
	0x000a0000,
#else
	0x00080000,
#endif
	0x00000000,
};

const u32 r6xx_ps[] =
{
	0x00000002,
	0x80800000,
	0x00000000,
	0x94200688,
	0x00000010,
	0x000d1000,
	0xb0800000,
	0x00000000,
};

const u32 r6xx_ps_size = ARRAY_SIZE(r6xx_ps);
const u32 r6xx_vs_size = ARRAY_SIZE(r6xx_vs);
const u32 r6xx_default_size = ARRAY_SIZE(r6xx_default_state);
const u32 r7xx_default_size = ARRAY_SIZE(r7xx_default_state);
newcodenewcodenewcodenewcodenewcodenewcodenewcode
