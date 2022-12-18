/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_SW_CONVERT_LIBRARY_H_
#define _MALI_SW_CONVERT_LIBRARY_H_

#include <mali_system.h>
#include <shared/mali_surface.h>


typedef struct mali_surface_rectangle_t
{
	float x;
	float y;
	float width;
	float height;
} mali_surface_rectangle;

/**
 * The big generic "convert anything to anything in SW" function.
 *
 * This function will take the data present in the src_ptr, defined by the metadata in src_parameters,
 * and convert it into the format, flags, layout, colorspace and pitch defined by dst_parameters
 * before storing the result in dst_ptr. If all parameters match up, this function will simply do the
 * equivalent of a memcopy. This function requires src_ptr and dst_ptr to be of size at least to the
 * datasize member of a regular surface created with these parameters.
 *
 * Typically, the src_ptr and dst_ptr are the mapped pointers from the surface defining the
 * respective parameters. In cases where the input or output goes to a CPU-side pointer
 * the parameters will simply be a transient structure created by the caller reflecting the
 * pitch, layout, flags and format of the CPU-side pointer.
 *
 * The src_ptr and the dst_ptr should not overlap. Attempts to do this will result in
 * undefined behavior.
 *
 * The size needs not to be identical. But certain constraints need to be met. Source area need to be
 * larger than or equal to destination area. Both areas need to be located within their respective
 * surfaces. Furthermore, it is possible to specify NULL areas which is interpreted as full area of surface.
 *
 * NOTE: When mapping / locking multiple surfaces, it is important to consider that another
 * thread may lock the same surfaces in a different order. If this is a potential issue,
 * always lock the surfaces in the order given by the surface pointer value, or inject a temporary
 * surface inbetween the operations (slower) to avoid locking both surfaces at the same time.
 *
 * @param src_parameters [in] A structure defining the size, pitch, format, layout, flags and colorspace of the input data.
 * @param src_area       [in] A structure defining the rectangular area to be read from.
 * @param dst_parameters [in] A structure defining the size, pitch, format, layout, flags and colorspace of the output data.
 * @param dst_area       [in] A structure defining the rectangular area to be written to.
 * @param src_ptr [in] The data that will be read by this function
 * @param dst_ptr [out] The location where the data will be written
 *
 */
MALI_IMPORT void _mali_convert(struct mali_surface *src_parameters, mali_surface_rectangle *src_area, const void *src_ptr,
                               struct mali_surface *dst_parameters, mali_surface_rectangle *dst_area, void *dst_ptr);

/**
 * This function performs downsampling. The function only work if the destination is
 * half the size (rounded down) of the source. Attempts to use other size relations
 * will result in an assert.
 *
 * For Power-of-two textures, this will perform a 2x2 box filter reduction.
 * For Non-power of two textures, this will do a sample-based reduction.
 *
 * @param src_parameters [in] A structure defining the size, pitch, format, layout, flags and colorspace of the input data.
 * @param dst_parameters [in] A structure defining the size, pitch, format, layout, flags and colorspace of the output data.
 * @param src_ptr [in] The data that will be read by this function
 * @param dst_ptr [out] The location where the data will be written
 *
 */
MALI_IMPORT void _mali_convert_downsample(struct mali_surface *src_parameters, const void *src_ptr,
        struct mali_surface *dst_parameters, void *dst_ptr);

/**
 * A lesser version of the first function, which only converts format flags.
 * If you know that the format, pitch, layout and colorspace will be identical, then this function will be faster.
 *
 * @param src_parameters [in] A structure defining the size, pitch, format, layout, flags and colorspace of the input data.
 * @param dst_parameters [in] A structure defining the size, pitch, format, layout, flags and colorspace of the output data.
 * @param src_ptr [in] The data that will be read by this function
 * @param dst_ptr [out] The location where the data will be written
 *
 */
MALI_IMPORT void _mali_convert_flags(struct mali_surface *src_parameters, const void *src_ptr,
                                     struct mali_surface *dst_parameters, void *dst_ptr);

/**
 * A lesser version of the first function, which only converts layout.
 * If you know that the format, flags and colorspace will be identical, this function will
 * be slightly faster.
 *
 * @param src_parameters [in] A structure defining the size, pitch, format, layout, flags and colorspace of the input data.
 * @param dst_parameters [in] A structure defining the size, pitch, format, layout, flags and colorspace of the output data.
 * @param src_ptr [in] The data that will be read by this function
 * @param dst_ptr [out] The location where the data will be written
 *
 */
MALI_IMPORT void _mali_convert_layout(struct mali_surface *src_parameters, const void *src_ptr,
                                      struct mali_surface *dst_parameters, void *dst_ptr);

/**
 * A lesser version of the first function, which only converts layout and flags.
 * If you know that the format and colorspace will be identical, this function will
 * be slightly faster.
 *
 * @param src_parameters [in] A structure defining the size, pitch, format, layout, flags and colorspace of the input data.
 * @param dst_parameters [in] A structure defining the size, pitch, format, layout, flags and colorspace of the output data.
 * @param src_ptr [in] The data that will be read by this function
 * @param dst_ptr [out] The location where the data will be written
 *
 */
MALI_IMPORT void _mali_convert_layout_flags(struct mali_surface *src_parameters, const void *src_ptr,
        struct mali_surface *dst_parameters, void *dst_ptr);




#endif /* _MALI_SW_CONVERT_LIBRARY_H_ */
