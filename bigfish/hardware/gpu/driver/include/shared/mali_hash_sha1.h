/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2013-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file
 * @brief Functions implementing the SHA1 hashing algorithm.
 *
 */

#ifndef MALI_HASH_SHA1_H
#define MALI_HASH_SHA1_H

#include <mali_system.h>

/** SHA1 processing block size is 64 bytes. */
#define MALI_HASH_SHA1_BLOCK_LEN_BYTES        ((u32)64)
#define MALI_HASH_SHA1_BLOCK_LEN_WORDS        ((u32)MALI_HASH_SHA1_BLOCK_LEN_BYTES/4)

/** SHA1 hash output is 5 words long. */
#define MALI_HASH_SHA1_HASH_LEN_BYTES         ((u32)20)
#define MALI_HASH_SHA1_HASH_LEN_WORDS         ((u32)MALI_HASH_SHA1_HASH_LEN_BYTES/4)

/**
 * @brief Structure to hold values used throughout the SHA-1 algorithm.
 */
typedef struct mali_hash_sha1
{
	/** Current hash value. */
	u32                hash_value[MALI_HASH_SHA1_HASH_LEN_WORDS];
	/** Pointer to next block to hash. */
	u8 const          *next_block;
	/** The algorithm scrambling schedule for the 80 core loops. */
	u32                schedule[80];
	/** Pointer to location of current data chunk input. */
	u8 const          *current_chunk_loc;
	/** How many bytes of the current data chunk are left to process? */
	u32                current_chunk_size;
	/** The input message segment - but only if it needs padding. */
	u8                 tmp_block[MALI_HASH_SHA1_BLOCK_LEN_BYTES];
	/** Block status of previous block: 0 = normal, 1 = pad with 0x80. */
	u32                status;
	/** Number of bytes in the message to date. */
	u32                size;
} mali_hash_sha1;

/**
 * @brief Initializes the SHA state structure.
 *
 * Calling this function initializes the SHA state structure pointed
 * to by @p state. This function must be called to initialize any new hash.
 *
 * @param state pointer to the the state structure for this digest.
 *
 */
MALI_IMPORT void _mali_hash_sha1_init(mali_hash_sha1 *state);

/**
 * @brief Updates the digest with new data.
 *
 * Calling this function updates the SHA digest with the current data
 * increment.
 *
 * @param[in,out] state    Pointer to the the state structure for this digest.
 * @param[in]      data     Pointer to the data buffer to append to digest.
 * @param          length   The length of the data, in bytes.
 *
 */
MALI_IMPORT void _mali_hash_sha1_update(mali_hash_sha1 *state,
                                        u8 const *data,
                                        u32 length);

/**
 * @brief Completes the SHA digest.
 *
 * Calling this completes the SHA digest, returning the hash in the
 * state structure.
 *
 * @param[in,out] state pointer to the the state structure for this algorithm.
 *
 */
MALI_IMPORT void _mali_hash_sha1_final(mali_hash_sha1 *state);
#endif
