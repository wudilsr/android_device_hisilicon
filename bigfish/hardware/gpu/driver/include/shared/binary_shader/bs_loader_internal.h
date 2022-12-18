/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */


/**
 * @file bs_loader_internal.h
 * @brief Holds internal loader structures, contructs and such
 */

#ifndef BS_LOADER_INTERNAL_H
#define BS_LOADER_INTERNAL_H

/**
 * The bs_stream struct contains all that is required from one stream.
 */
struct bs_stream
{
	const void *data;
	u32 position;
	u32 size;
};

/* @brief The following 6 functions reads out one u8, s8, u16, s16, u32 or s32 from a stream and increments the
 * stream positions accordingly.
 * @param stream The stream to read from.
 * @return The variable read.
 * @note The function will assert-crash if there isn't enough data in the stream or if the stream is incorrectly aligned.
 */

MALI_STATIC_FORCE_INLINE u8 load_u8_value(struct bs_stream *stream)
{
	u8 retval;
	MALI_DEBUG_ASSERT(stream->position < stream->size, ("insufficient data in stream")); /* assert enough data */
	retval = ((const u8 *)stream->data)[stream->position];
	stream->position += 1;
	return retval;
}

MALI_STATIC_FORCE_INLINE s8 load_s8_value(struct bs_stream *stream)
{
	s8 retval;
	MALI_DEBUG_ASSERT(stream->position < stream->size, ("insufficient data in stream")); /* assert enough data */
	retval = ((const s8 *)stream->data)[stream->position];
	stream->position += 1;
	return retval;
}


MALI_STATIC_FORCE_INLINE u16 load_u16_value(struct bs_stream *stream)
{
	u16 retval;
	retval = load_u8_value(stream) + (load_u8_value(stream) << 8); /* always little endian datastream */
	return retval;
}


MALI_STATIC_FORCE_INLINE s16 load_s16_value(struct bs_stream *stream)
{
	s16 retval;
	retval = load_u8_value(stream) + (load_u8_value(stream) << 8); /* always little endian datastream */
	return retval;
}


MALI_STATIC_FORCE_INLINE u32 load_u32_value(struct bs_stream *stream)
{
	u32 retval;
	retval = load_u16_value(stream) + (load_u16_value(stream) << 16); /* always little endian datastream */
	return retval;
}


MALI_STATIC_FORCE_INLINE s32 load_s32_value(struct bs_stream *stream)
{
	s32 retval;
	retval = load_u16_value(stream) + (load_u16_value(stream) << 16); /* always little endian datastream */
	return retval;
}

MALI_STATIC_FORCE_INLINE float load_float_value(struct bs_stream *stream)
{
	union
	{
		u32 uval;
		float fval;
	} retval;
	retval.uval = load_u32_value(stream); /* always little endian datastream */
	return retval.fval;
}

/**
 * @brief returns the number of bytes remaining in a stream
 * @param stream the stream to inspect
 */

MALI_STATIC_FORCE_INLINE u32 bs_stream_bytes_remaining(struct bs_stream *stream)
{
	MALI_DEBUG_ASSERT(stream->size >= stream->position, ("unable to get size, stream is corrupt"));
	return stream->size - stream->position;
}

/**
 * @brief returns the current stream head as an u8 stream. This is used in reading operations
 * @param stream the stream to read from.
 */
MALI_STATIC_FORCE_INLINE u8 *bs_stream_head(struct bs_stream *stream)
{
	MALI_DEBUG_ASSERT(stream->size >= stream->position, ("unable to get stream head, stream is corrupt"));
	return ((u8 *) stream->data) + stream->position;
}


/* creates a blocktype enum from 4 chars given in reading order */
#define MAKE_BLOCKTYPE(a, b, c, d) ( (((u32)(a)) << 24) + (((u32)(b)) << 16) + (((u32)(c)) << 8) + (((u32)(d))) )

enum blocktype
{
	/* list of strings indentifiers, packed into an int for easy comparison.
	 * This int is always in little endian, but does not really matter as long
	 * as every blocktype constructor use the MAKE_BLOCKTYPE macro */
	MBS1 = MAKE_BLOCKTYPE('M', 'B', 'S', '1'),
	CVER = MAKE_BLOCKTYPE('C', 'V', 'E', 'R'),
	CFRA = MAKE_BLOCKTYPE('C', 'F', 'R', 'A'),
	SUNI = MAKE_BLOCKTYPE('S', 'U', 'N', 'I'),
	SATT = MAKE_BLOCKTYPE('S', 'A', 'T', 'T'),
	SVAR = MAKE_BLOCKTYPE('S', 'V', 'A', 'R'),
	VUNI = MAKE_BLOCKTYPE('V', 'U', 'N', 'I'),
	VATT = MAKE_BLOCKTYPE('V', 'A', 'T', 'T'),
	VVAR = MAKE_BLOCKTYPE('V', 'V', 'A', 'R'),
	DBIN = MAKE_BLOCKTYPE('D', 'B', 'I', 'N'),
	VPRO = MAKE_BLOCKTYPE('V', 'P', 'R', 'O'),
	STRI = MAKE_BLOCKTYPE('S', 'T', 'R', 'I'),
	FPOI = MAKE_BLOCKTYPE('F', 'P', 'O', 'I'),
	FTRA = MAKE_BLOCKTYPE('F', 'T', 'R', 'A'),
	FDIS = MAKE_BLOCKTYPE('F', 'D', 'I', 'S'),
	FSTA = MAKE_BLOCKTYPE('F', 'S', 'T', 'A'),
	FBUU = MAKE_BLOCKTYPE('F', 'B', 'U', 'U'),
	VINI = MAKE_BLOCKTYPE('V', 'I', 'N', 'I'),
	FINS = MAKE_BLOCKTYPE('F', 'I', 'N', 'S'),
	BATT = MAKE_BLOCKTYPE('B', 'A', 'T', 'T'),
	VIDX = MAKE_BLOCKTYPE('V', 'I', 'D', 'X'),
	DPRO = MAKE_BLOCKTYPE('D', 'P', 'R', 'O'),
	VSOP = MAKE_BLOCKTYPE('V', 'S', 'O', 'P'),
	VACT = MAKE_BLOCKTYPE('V', 'A', 'C', 'T'),
	EXPR = MAKE_BLOCKTYPE('E', 'X', 'P', 'R'),
	OPND = MAKE_BLOCKTYPE('O', 'P', 'N', 'D'),
	VERS = MAKE_BLOCKTYPE('V', 'E', 'R', 'S'),

	NO_BLOCK = 0
};

/**
 * @brief Peeks at the binary data stream, returns the next header name in the stream.
 *        This function makes NO alterations to the stream under any circumstances.
 * @param stream - a pointer to the data stream.
 * @return The name of the next header, or 0 if no next header available.
 */
enum blocktype bs_peek_header_name(struct bs_stream *stream);

/**
 * @brief Reads the next header from the stream, asserts it is identical with the expected header.
 *        If this is the case, the stream jumps to the start of the data segment of the block.
 *        If false, the stream jumps to the start of the next block header.
 *        This function is thus useful for both skipping unknown blocks as
 *        well as getting the block you actually want.
 *        As a lightweight alternative to a full block graph, this functionality covers
 *        60% of all the required validation (peek covering the last 40%). Why make it more difficult?
 * @param stream A pointer to the stream struct. This parameter acts as an in-out parameter,
 *        with its input value being the start of the block to read, the output value being the
 *        place in the stream to continue reading (start of data or next block depending on outcome).
 * @param expected_header The header we are expecting to find; and thus ultimately the condition for
 *        reading or skipping the block.
 * @return The size of the block found, or 0 if the block was a mismatch or otherwise problem reading the stream.
 * @note  If the block considered is too big to actually fit the remaining stream data, we have a faulty stream.
 *        The function will handle this by emptying the stream, then return 0 as if we had a mismatch.
 *        This means that no matter what stream data exists, a while loop that runs until the stream
 *        empties by repeatedly calling this function, always will terminate at some point.
 *        This is a desired feature which greatly simplifies error handling. If you find a block with this function,
 *        you are guaranteed it is exactly [return value] number of bytes large, and that those bytes are available
 *        in the stream.
 */
u32 bs_read_or_skip_header(struct bs_stream *stream, enum blocktype expected_header);

/**
 * @brief Creates a new substream from the parent stream. The childstream will contain the header, as well
 *        as the contents of the next block in the parent stream. The parent stream position will be set to
 *        right after the end of the subblock.
 * @param parent A pointer to the parent stream.
 * @param child A pointer to the stream of the child block.
 * @return MALI_ERR_NO_ERROR if the child stream was created without problems and MALI_ERR_FUNCTION_FAILED if
 *         corrupt datastream was present.
 * @note  If the block concidered is too big to actually fit the remaining stream data, we have a faulty stream.
 *        The function will handle this by emptying the parent stream, then return MALI_ERR_FUNCTION_FAILED.
 */
mali_err_code bs_create_subblock_stream(struct bs_stream *parent, struct bs_stream *child);

/**
 * @brief Reads a string block and allocates a buffer for it.
 * @param stream The stream to read from
 * @param output A legal pointer where the allocated buffer will be referenced.
 * @note Unless the stream points to a STRI block, this function will fail, returning MALI_ERR_FUNCITON_FAILED.
 *       The output pointer will in such cases be unaltered. Always check the return value!
 * @note The caller is responsible for freeing this string. Should be free's with _mali_sys_free
 */

mali_err_code bs_read_and_allocate_string(struct bs_stream *stream, char **output) MALI_CHECK_RESULT;


/**
 * @brief Reads a VPRO block's content into an allocated memory area.
 * @param stream The stream to read from
 * @param out_size An output parameter, returning the position of the shader end instruction
 * @return A mali_err_code. Output parameters are only valid if errocde == MALI_ERR_NO_ERROR
 */
mali_err_code bs_read_VPRO_block(struct bs_stream *stream, u32 *out_size) MALI_CHECK_RESULT;

/**
 * @brief Reads a DBIN block's content into an allocated memory area.
 * @param stream The stream to read from
 * @param out_size An output parameter, returning the size of the block, always
 * @param out_data a pointer to a newly allocated buffer, containing the block's content in binary form.
 * @return A mali_err_code. Output parameters are only valid if errocde == MALI_ERR_NO_ERROR
 * @note The caller is responsible of freeing the allocated memory. Should be freed with _mali_sys_free
 */
mali_err_code bs_read_and_allocate_binary_block_contents(struct bs_stream *stream,
        void **out_data, u32 *out_size) MALI_CHECK_RESULT;

/**
 * @brief copies a block from the stream and allocates it into a memory area
 * @param stream The stream to read from.
 * @param blockname The expected blockname you want to read. Peek this if uncertain, but typically you already know.
 * @param out_size output parameter, returning the size of the block, always
 * @param out_data output param, a pointer to a newly allocated block copy
 * @return A mali_err_code. Output parameters are only valid if errocde == MALI_ERR_NO_ERROR
 * @note The allocated out_data should be freed through _mali_sys_free
 */

mali_err_code bs_copy_binary_block(struct bs_stream *stream, enum blocktype blockname,
                                   void **out_data, u32 *out_size) MALI_CHECK_RESULT;

/**
 * @brief set up the attribute stream structures based on symbol info. Called automatically on link and attribute rewrites.
 * @param po The program object to modify
 * @return MALI_ERR_NO_ERROR or MALI_ERR_OUT_OF_MEMORY
 * @note Will never leak memory, removes old attribute stream structs if present
 */
mali_err_code bs_setup_attribute_streams(struct bs_program *po);

#endif

