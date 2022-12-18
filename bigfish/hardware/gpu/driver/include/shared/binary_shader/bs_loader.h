/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2010, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file bs_loader.h
 * @brief Loads a binary shader into a binary state object
 */

#ifndef _BS_LOADER_H
#define _BS_LOADER_H

#include "bs_object.h"

/**
 *  Shader type ( NOTE : values MUST be the same as the GL counterparts )
 */
#define BS_FRAGMENT_SHADER                0x8B30
#define BS_VERTEX_SHADER                  0x8B31

/**
 * Datatype for streams. Defined in bs_loader_internal.h, This is a public stub
 */
struct bs_stream;

/**
 * @brief Loads the attribute set chunk, sets the po->attribute_symbols parameter of the program object, or returns a failure message through the log.
 * @param po The program object to modify
 * @param stream the stream containing the data to load
 * @return Returns the status from this function.
 * @note Check the log parameter in the bs_program in case something went wrong.
 */
MALI_IMPORT mali_err_code __mali_binary_shader_load_attribute_table(bs_program *po, struct bs_stream *stream) MALI_CHECK_RESULT;

/**
 * @brief Loads the uniform chunks from both shaders, sets the binary.uniform_symbols of the program object, or a failure error message
 * @param po The program object to modify
 * @param vertex_stream the stream containing the data to load in ther vertex shader
 * @param fragment_stream the stream containing the data to load in the fragment shader
 * @return Returns the status from this function
 */
MALI_IMPORT mali_err_code __mali_binary_shader_load_uniform_table(bs_program *po, struct bs_stream *vertex_stream, struct bs_stream *fragment_stream) MALI_CHECK_RESULT;

/**
 * @brief Loads the varying chunks from both shaders, sets the binary.varying_symbols for the program object, or a failure error message
 * @param po The program object to modify
 * @param vertex_stream the stream containing the data to load in ther vertex shader
 * @param fragment_stream the stream containing the data to load in the fragment shader
 * @return The status of the operation done.
 */
MALI_IMPORT mali_err_code __mali_binary_shader_load_varying_table(bs_program *po, struct bs_stream *vertex_stream, struct bs_stream *fragment_stream) MALI_CHECK_RESULT;

/**
 * @brief Top-level binary loader function. Loads a chunk of data and inserts it into a shader object.
 * @param so The shader object to recieve data.
 * @param shadertype The type corresponsing to the object encompassing this binary state struct.
 *                   BS_FRAGMENT_SHADER, BS_VERTEX_SHADER, GL_FRAGMENT_SHADER or GL_VERTEX_SHADER.
 *                   Yes. All four are accepted.
 * @param binary_data The binary data to parse
 * @param binary_length Not really needed (binary_data holds its own size), but
 * used for ensuring that we never read past the end of the binary data, creating segfaults and otherwise security holes.
 * @note Binary data must contain a binary shader fitting the TYPE of the shader object.
 */
MALI_IMPORT mali_err_code __mali_binary_shader_load(bs_shader *so, u32 shadertype, const void *binary_data, u32 binary_length) MALI_CHECK_RESULT;

#endif /* _BS_LOADER_H */
