/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */


#ifndef _MALI_GP_VS_CONFIG_H_
#define _MALI_GP_VS_CONFIG_H_

#include <mali_gp_vs_cmd.h>
#include <base/mali_byteorder.h>

/** The required alignment of memory addresses that are added to VS registers */
#define GP_VS_CONF_REG_ADDRESS_ALIGNMENT 64

#define GP_INPUT_STREAM_COUNT 16
#define GP_OUTPUT_STREAM_COUNT 16

/** A variation of the macros below that allows for seperation between input and output */
#define GP_VS_CONF_REG_STREAM_ADDR(x) (2 * (x) + 0)
#define GP_VS_CONF_REG_STREAM_SPEC(x) (2 * (x) + 1)

/** Input stream registers for the VS. The first 32 registers.
    X is a number [0-15]. */
#define GP_VS_CONF_REG_INP_ADDR(X)      GP_VS_CONF_REG_STREAM_ADDR(X)
#define GP_VS_CONF_REG_INP_SPEC(X)      GP_VS_CONF_REG_STREAM_SPEC(X)


/** Macro for creating spec in GP_VS_CONF_REG_INP_SPEC(X)*/
#define GP_VS_CONF_REG_INP_SPEC_CREATE(format, commaloc, stride) \
	( \
	  ( (u32)GP_VS_CMD_BMASK(format,   6)       ) | \
	  (((u32)GP_VS_CMD_BMASK(commaloc, 5)) <<  6) | \
	  (((u32)GP_VS_CMD_BMASK(stride,  21)) << 11) \
	)



#define GP_VS_CONF_REG_INP_STREAM_SET(stream, x, addr) \
	( \
	  (stream)[GP_VS_CONF_REG_INP_ADDR(x)] = _SWAP_ENDIAN_U32_U8(addr) \
	)

#define GP_VS_CONF_REG_INP_STREAM_GET(stream, x) \
	( \
	  _SWAP_ENDIAN_U32_U8((stream)[GP_VS_CONF_REG_INP_ADDR(x)]) \
	)

#define GP_VS_CONF_REG_INP_STREAM_ADD(stream, x, addr) \
	( \
	  (stream)[GP_VS_CONF_REG_INP_ADDR(x)] += _SWAP_ENDIAN_U32_U8(addr) \
	)

#if MALI_BIG_ENDIAN

/** BigEndian bit shift used in GP_VS_CONF_REG_INP_SPEC(X) Register */
#define GP_VS_REG_BIGENDIAN_SHIFT (31)

#define GP_VS_CONF_REG_INP_SPEC_SET(stream, x, spec) \
	( \
	  (stream)[GP_VS_CONF_REG_INP_SPEC(x)] = \
	          _SWAP_ENDIAN_U32_U8( \
	                               (spec) | \
	                               (((u32)GP_VS_CMD_BMASK(1, 1)) << GP_VS_REG_BIGENDIAN_SHIFT) \
	                             ) \
	)

#else

#define GP_VS_CONF_REG_INP_SPEC_SET(stream, x, spec) \
	( \
	  (stream)[GP_VS_CONF_REG_INP_SPEC(x)] = spec \
	)

#endif


#define GP_VS_CONF_REG_INP_SPEC_GET(stream, x) \
	( \
	  _SWAP_ENDIAN_U32_U8((stream)[GP_VS_CONF_REG_INP_SPEC(x)]) \
	)



/** Output stream registers for the VS. 32 registers.
    X is a number [0-15]. */
#define GP_VS_CONF_REG_OUTP_ADDR(X)     (2 * GP_INPUT_STREAM_COUNT + GP_VS_CONF_REG_STREAM_ADDR(X))
#define GP_VS_CONF_REG_OUTP_SPEC(X)     (2 * GP_INPUT_STREAM_COUNT + GP_VS_CONF_REG_STREAM_SPEC(X))

/** Macro for creating spec in GP_VS_CONF_REG_OUTP_SPEC(X)*/
#define GP_VS_CONF_REG_OUTP_SPEC_CREATE(format,commaloc,stride) GP_VS_CONF_REG_INP_SPEC_CREATE(format,commaloc,stride)


#define GP_VS_CONF_REG_OUTP_STREAM_SET(stream, x, addr) \
	( \
	  (stream)[GP_VS_CONF_REG_OUTP_ADDR(x)] = _SWAP_ENDIAN_U32_U8(addr) \
	)

#define GP_VS_CONF_REG_OUTP_STREAM_GET(stream, x) \
	( \
	  _SWAP_ENDIAN_U32_U8((stream)[GP_VS_CONF_REG_OUTP_ADDR(x)]) \
	)

#define GP_VS_CONF_REG_OUTP_STREAM_ADD(stream, x, addr) \
	( \
	  (stream)[GP_VS_CONF_REG_OUTP_ADDR(x)] += _SWAP_ENDIAN_U32_U8(addr) \
	)



#define GP_VS_CONF_REG_OUTP_SPEC_SET(stream, x, spec) \
	( \
	  (stream)[GP_VS_CONF_REG_OUTP_SPEC(x)] = _SWAP_ENDIAN_U32_U8(spec) \
	)


#define GP_VS_CONF_REG_OUTP_SPEC_GET(stream, x) \
	(\
	 _SWAP_ENDIAN_U32_U8((stream)[GP_VS_CONF_REG_OUTP_SPEC(x)]) \
	)


/** General stream registers setting for the VS. 32 registers */
#define GP_VS_CONF_REG_SPEC_CREATE(format,commaloc,stride) GP_VS_CONF_REG_INP_SPEC_CREATE(format,commaloc,stride)

#define GP_VS_CONF_REG_STREAM_SET(stream, x, addr) \
	( \
	  (stream)[GP_VS_CONF_REG_STREAM_ADDR(x)] = _SWAP_ENDIAN_U32_U8(addr) \
	)

#define GP_VS_CONF_REG_STREAM_GET(stream, x) \
	( \
	  _SWAP_ENDIAN_U32_U8((stream)[GP_VS_CONF_REG_STREAM_ADDR(x)]) \
	)

#define GP_VS_CONF_REG_STREAM_ADD(stream, x, addr) \
	( \
	  (stream)[GP_VS_CONF_REG_STREAM_ADDR(x)] += _SWAP_ENDIAN_U32_U8(addr) \
	)


#define GP_VS_CONF_REG_SPEC_SET(stream, x, spec) \
	( \
	  (stream)[GP_VS_CONF_REG_STREAM_SPEC(x)] = _SWAP_ENDIAN_U32_U8(spec) \
	)

#define GP_VS_CONF_REG_SPEC_GET(stream, x) \
	(\
	 _SWAP_ENDIAN_U32_U8((stream)[GP_VS_CONF_REG_STREAM_SPEC(x)]) \
	)

/* Parameterized versions of the variants below that support 1-4 components */
#define GP_VS_VSTREAM_FORMAT_FP32(components)    ( 0 << 2 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_FIX_S32(components) ( 1 << 2 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_FIX_U32(components) ( 2 << 2 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_FP16(components)    ( 3 << 2 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_FIX_S16(components) ( 4 << 2 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_FIX_U16(components) ( 5 << 2 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_FIX_S8(components)  ( 6 << 2 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_FIX_U8(components)  ( 7 << 2 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_FP24(components)    (12 << 2 | ((components)-1))

/* These formats are input/attribute formats only.
 * They are designed for MaliGP to handle normalized attribute inputs. */
#define GP_VS_VSTREAM_FORMAT_NORM_S8(components)  ( 8 << 4 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_NORM_U8(components)  ( 9 << 4 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_NORM_S16(components)  ( 10 << 4 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_NORM_U16(components)  ( 11 << 4 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_NORM_S32(components)  ( 13 << 4 | ((components)-1))
#define GP_VS_VSTREAM_FORMAT_NORM_U32(components)  ( 14 << 4 | ((components)-1))

/** The different stream formats used by VS. */
#define GP_VS_VSTREAM_FORMAT_NO_DATA        63

#define GP_VS_VSTREAM_FORMAT_1_FP32         0
#define GP_VS_VSTREAM_FORMAT_2_FP32         1
#define GP_VS_VSTREAM_FORMAT_3_FP32         2
#define GP_VS_VSTREAM_FORMAT_4_FP32         3

#define GP_VS_VSTREAM_FORMAT_1_FIX_S32      4
#define GP_VS_VSTREAM_FORMAT_2_FIX_S32      5
#define GP_VS_VSTREAM_FORMAT_3_FIX_S32      6
#define GP_VS_VSTREAM_FORMAT_4_FIX_S32      7

#define GP_VS_VSTREAM_FORMAT_1_FIX_U32      8
#define GP_VS_VSTREAM_FORMAT_2_FIX_U32      9
#define GP_VS_VSTREAM_FORMAT_3_FIX_U32      10
#define GP_VS_VSTREAM_FORMAT_4_FIX_U32      11

#define GP_VS_VSTREAM_FORMAT_1_FP16         12
#define GP_VS_VSTREAM_FORMAT_2_FP16         13
#define GP_VS_VSTREAM_FORMAT_3_FP16         14
#define GP_VS_VSTREAM_FORMAT_4_FP16         15

#define GP_VS_VSTREAM_FORMAT_1_FIX_S16      16
#define GP_VS_VSTREAM_FORMAT_2_FIX_S16      17
#define GP_VS_VSTREAM_FORMAT_3_FIX_S16      18
#define GP_VS_VSTREAM_FORMAT_4_FIX_S16      19

#define GP_VS_VSTREAM_FORMAT_1_FIX_U16      20
#define GP_VS_VSTREAM_FORMAT_2_FIX_U16      21
#define GP_VS_VSTREAM_FORMAT_3_FIX_U16      22
#define GP_VS_VSTREAM_FORMAT_4_FIX_U16      23

#define GP_VS_VSTREAM_FORMAT_1_FIX_S8       24
#define GP_VS_VSTREAM_FORMAT_2_FIX_S8       25
#define GP_VS_VSTREAM_FORMAT_3_FIX_S8       26
#define GP_VS_VSTREAM_FORMAT_4_FIX_S8       27

#define GP_VS_VSTREAM_FORMAT_1_FIX_U8       28
#define GP_VS_VSTREAM_FORMAT_2_FIX_U8       29
#define GP_VS_VSTREAM_FORMAT_3_FIX_U8       30
#define GP_VS_VSTREAM_FORMAT_4_FIX_U8       31

#define GP_VS_VSTREAM_FORMAT_1_FP24         48
#define GP_VS_VSTREAM_FORMAT_2_FP24         49
#define GP_VS_VSTREAM_FORMAT_3_FP24         50
#define GP_VS_VSTREAM_FORMAT_4_FP24         51

/* These formats are input/attribute formats only.
 * They are designed for MaliGP to handle normalized attribute inputs. */
#define GP_VS_VSTREAM_FORMAT_1_NORM_S8  32
#define GP_VS_VSTREAM_FORMAT_2_NORM_S8  33
#define GP_VS_VSTREAM_FORMAT_3_NORM_S8  34
#define GP_VS_VSTREAM_FORMAT_4_NORM_S8  35

#define GP_VS_VSTREAM_FORMAT_1_NORM_U8  36
#define GP_VS_VSTREAM_FORMAT_2_NORM_U8  37
#define GP_VS_VSTREAM_FORMAT_3_NORM_U8  38
#define GP_VS_VSTREAM_FORMAT_4_NORM_U8  39

#define GP_VS_VSTREAM_FORMAT_1_NORM_S16  40
#define GP_VS_VSTREAM_FORMAT_2_NORM_S16  41
#define GP_VS_VSTREAM_FORMAT_3_NORM_S16  42
#define GP_VS_VSTREAM_FORMAT_4_NORM_S16  43

#define GP_VS_VSTREAM_FORMAT_1_NORM_U16  44
#define GP_VS_VSTREAM_FORMAT_2_NORM_U16  45
#define GP_VS_VSTREAM_FORMAT_3_NORM_U16  46
#define GP_VS_VSTREAM_FORMAT_4_NORM_U16  47

#define GP_VS_VSTREAM_FORMAT_1_NORM_S32  52
#define GP_VS_VSTREAM_FORMAT_2_NORM_S32  53
#define GP_VS_VSTREAM_FORMAT_3_NORM_S32  54
#define GP_VS_VSTREAM_FORMAT_4_NORM_S32  55

#define GP_VS_VSTREAM_FORMAT_1_NORM_U32  56
#define GP_VS_VSTREAM_FORMAT_2_NORM_U32  57
#define GP_VS_VSTREAM_FORMAT_3_NORM_U32  58
#define GP_VS_VSTREAM_FORMAT_4_NORM_U32  59

/* These 3 formats are for GP outputs only, and overlap with the normalized formats */
#define GP_VS_VSTREAM_FORMAT_VDATA_BLOCK        32
#define GP_VS_VSTREAM_FORMAT_POINT_SIZE         33
#define GP_VS_VSTREAM_FORMAT_RGB565             46



/** 0x40 This register specifies the number of vertex shader
    instructions, in the native format, to run per vertex.*/
#define GP_VS_CONF_REG_PROG_PARAM       64

/** Macro: creating input to reg GP_VS_CONF_REG_PROG_PARAM
   Start    Start of vertex shader program.
   End      End of vertex shader program.
   Index    Index of last instruction to touch input registers*/
#define GP_VS_CONF_REG_PROG_PARAM_CREATE(start,end,idx_last) \
	(\
	 ( (u32)GP_VS_CMD_BMASK(start,    10)       ) | \
	 (((u32)GP_VS_CMD_BMASK(end,      10)) << 10) | \
	 (((u32)GP_VS_CMD_BMASK(idx_last, 12)) << 20) \
	)

/** This register specifies the number of cache lines to
    prefetch in the Vertex Shader when loading vertex data.*/
#define GP_VS_CONF_REG_PREFETCH         65

/** Sets: Input and output modes. Regs to write back,
    toggle: floor/truncate, and VDB format.
    Consult document P0081_media_proc_data_struct
    and P0035_mali_data_struct for more info.*/
#define GP_VS_CONF_REG_OPMOD            66

#define GP_VS_CONF_REG_OPMOD_CREATE( num_input_regs, num_output_regs) \
	( \
	  (((u32)GP_VS_CMD_BMASK((num_input_regs  - 1), 4)) <<  24) | \
	  (((u32)GP_VS_CMD_BMASK((num_output_regs - 1), 4)) <<  8)  \
	)

/** Operation modes in the macro above is one of the following:*/
#define GP_VS_INP_MODE_VERTEX       0
#define GP_VS_INP_MODE_DSP          1
#define GP_VS_INP_MODE_RGB          4
#define GP_VS_INP_MODE_YUV420       5
#define GP_VS_INP_MODE_YUV422       6
#define GP_VS_INP_MODE_DCT          7

#define GP_VS_OUTP_MODE_VERTEX      0
#define GP_VS_OUTP_MODE_VERTEXII    1
#define GP_VS_OUTP_MODE_DSP         3
#define GP_VS_OUTP_MODE_RGB         4
#define GP_VS_OUTP_MODE_YUV420      5
#define GP_VS_OUTP_MODE_YUV422      6
#define GP_VS_OUTP_MODE_ADD         7

/** VDB format in the macro above is one of the following:*/
#define GP_VS_VDB_FORMAT_1          3
#define GP_VS_VDB_FORMAT_2          0
#define GP_VS_VDB_FORMAT_3          1

/** Vertices per alternative stride (YUV modes) */
#define GP_VS_CONF_REG_VERTICES_ALT_STRIDE      67

/** Macro for creating GP_VS_CONF_REG_VERTICES_ALT_STRIDE */
#define GP_VS_CONF_REG_VERTICES_ALT_STRIDE_CREATE(\
        input_vertices_pr_alt_stride,\
        output_vertices_pr_alt_stride)\
(\
 ( (u32)GP_VS_CMD_BMASK(input_vertices_pr_alt_stride,14)        ) | \
 (((u32)GP_VS_CMD_BMASK(output_vertices_pr_alt_stride,14)) << 16)   \
)

/** Alternative stride for input vertices [0-3] [4-7] [8-11] [12-16]*/
#define GP_VS_CONF_REG_INPUT_ALT_STRIDE_0       68
#define GP_VS_CONF_REG_INPUT_ALT_STRIDE_4       69
#define GP_VS_CONF_REG_INPUT_ALT_STRIDE_8       70
#define GP_VS_CONF_REG_INPUT_ALT_STRIDE_12      71

/** Alternative stride for output vertices [0-3] [4-7] [8-11] [12-16]*/
#define GP_VS_CONF_REG_OUTP_ALT_STRIDE_0        72
#define GP_VS_CONF_REG_OUTP_ALT_STRIDE_4        73
#define GP_VS_CONF_REG_OUTP_ALT_STRIDE_8        74
#define GP_VS_CONF_REG_OUTP_ALT_STRIDE_12       75

/* Semaphore wait value has 16 bit width. Writing to the 16th bit is
 * an undocumented value which means no timeout  */
#define MALI_GP2_VS_SEMAPHORE_NO_TIMEOUT (1<<15)


#endif

