/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2012-2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _SHADERGEN_INTERFACE_H_
#define _SHADERGEN_INTERFACE_H_

#include <shared/mali_interface.h>
#include <base/mali_types.h>

#include "shadergen_state.h"
#include "shadergen_maligp2/shadergen_maligp2.h"
#include "shader_pieces.h"
#include "shadergen_mali200/shadergen_mali200.h"

/**
 * Generates a vertex shader
 * @param state A pointer to the vertex generator state. Must be != NULL
 * @param size_out A pointer to a location to store the size of the generated shader. Must be != NULL
 * @param alloc Memory allocation function
 * @param free Memory deallocation function
 * @return A pointer to the generated shader. NULL on failure.
 * @note As the vertex shader generator only glues together pregenerated machine code, it doesn't need a hardware revision flag.
 */
MALI_IMPORT unsigned *_gles_vertex_shadergen_generate_shader(const struct vertex_shadergen_state *state, unsigned *size_out, alloc_func alloc, free_func free);

/**
 * Retrieves the uniform initializers.
 * @param n_inits A pointer to a location to store the number uniform initializers. Must be != NULL
 * @return A pointer to the uniform initializers.
 */
MALI_IMPORT const uniform_initializer *_gles_piecegen_get_uniform_initializers(unsigned *n_inits);

/**
 * Generates a fragment shader
 * @param state A pointer to the fragment generator state. Must be != NULL
 * @param size_out A pointer to a location to store the size of the generated shader. Must be != NULL
 * @param hw_rev Hardware revision, where rApB is written as 0xAAAABBBB.
 * @param alloc Memory allocation function
 * @param free Memory deallocation function
 * @return A pointer to the generated shader. NULL on failure.
 */
MALI_IMPORT unsigned *_gles_fragment_shadergen_generate_shader(const struct fragment_shadergen_state *state, unsigned *size_out, unsigned int hw_rev, alloc_func alloc, free_func free);

/**
 * Checks if two fragment generator states are equivalent.
 * @param state1 A pointer to the first fragment generator state. Must be != NULL
 * @param state2 A pointer to the second fragment generator state. Must be != NULL
 * @return 1 if the states are equivalent, 0 if not
 */
MALI_IMPORT int _gles_fragment_shadergen_states_equivalent(const struct fragment_shadergen_state *state1, const struct fragment_shadergen_state *state2);

/**
* Checks if two vertex generator states are equivalent.
   Faster than _gles_vertex_shadergen_states_equivalent
*/
#define COMPARE_VERTEX_SHADERGEN_STATES_EQUIVALENT(st1, st2)  (st1.bits[0] == st2.bits[0] && st1.bits[1] == st2.bits[1])


#endif /* _SHADERGEN_INTERFACE_H_ */
