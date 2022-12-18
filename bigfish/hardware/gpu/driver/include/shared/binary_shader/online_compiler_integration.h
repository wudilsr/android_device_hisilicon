/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2010, 2013-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */


/**
 * @file online_compiler_integration.h
 * @brief Works as an interface towards any compiler-related functionality
 */

#ifndef _ONLINE_COMPILER_INTEGRATION_H_
#define _ONLINE_COMPILER_INTEGRATION_H_

#include "bs_object.h"

/**
 * @brief This function acceps a set of essl source code and returns the binary of a shader, performing compilation.
 * @param so A binary shader object. The result will be placed in this struct.
 * @param shadertype Either BS_FRAGMENT_SHADER or BS_VERTEX_SHADER
 * @param concatenated_strings The concatenated string containing the shader code to compile.
 * @param string_lengths The length of each substring in the concatenated string. An array of u32 values.
 * @param source_string_count The number of source strings that the concatenated string was built from (also arraysize of string_lengths).
 * @return Whether this function failed or not, according to the following rules:
 *
 *          MALI_ERR_NO_ERROR - there was no internal errors, compilation may or may not have succeeded.
 *                              Check the compiled flag and/or log. Shader object state is valid.
 *          MALI_ERR_FUNCTION_FAILED - Compiler failed on an internal error. Compilation has failed. Error log
 *                              may or may not be present. Shader object state is valid, but not nescessarily
 *                              complete. Contains the information created up to the point of the crash.
 *          MALI_ERR_OUT_OF_MEMORY - Compiler ran out of memory, compilation failed. Error log may or may not be present.
 *                              Shader object -may- contain information up to the point of the crash, but it may also be
 *                              zeroed out.
 *
 */
MALI_IMPORT mali_err_code __mali_compile_essl_shader(struct bs_shader *so, u32 shadertype, char *concatenated_strings, s32 *string_lengths, int source_string_count) MALI_CHECK_RESULT;


#endif /* _ONLINE_COMPILER_INTEGRATION_H*/

