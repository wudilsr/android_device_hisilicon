/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2011, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_named_list.h
 * @brief interface for mali_named_list
 */

#ifndef MALI_NAMED_LIST_H
#define MALI_NAMED_LIST_H

#include <mali_system.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The initial log2( size of the hash-array ) */
#define MALI_HASH_LIST_INITIAL_LOG2_SIZE 8

#define MALI_NUM_VALUES_FLAT (1 << MALI_HASH_LIST_INITIAL_LOG2_SIZE)

struct mali_hash_list_entry;

typedef struct mali_named_list
{
	struct mali_hash_list_entry **list;   /**< The array representing the hash-list */
	u32 max;                              /**< The largest id inserted in the list */
	u32 log2_size;                        /**< The log2(size of hash-list with unused entries) */
	u32 size;                             /**< The size of the hash-list */
	u32 num_elements;                     /**< The number of inserted elements in the entire list */
	u32 num_elements_flat;                /**< The number of elements present in the flat-array */
	u32 num_elements_hash;                /**< The number of elements present in the hash-array */

	void *flat[ MALI_NUM_VALUES_FLAT ];   /**< The list of entries that are directly inserted(hash=name) */
	mali_mutex_handle list_mutex;         /**< The mutex lock for this list */

	/** Helper variables for iterating the list */
	u32 num_elements_iterated_flat_array; /**< The number of elements iterated through in the flat-array since last iterate_begin */
	u32 last_hash_index;                  /**< The last index used for iterating through the hash-list */
} mali_named_list;


/**
 * Initialize and return a named list.
 * @return The allocated named list, or NULL on error
 */
MALI_IMPORT mali_named_list *__mali_named_list_allocate(void);

/**
 * Delete a named list. this fuction must be called after operating on it, to ensure that memory has been freed.
 * @param list the list to be freed
 * @param freefunc The function called on each remaining element data, or NULL if not deleting anything
 */
MALI_IMPORT void __mali_named_list_free(mali_named_list *list, void (*freefunc)());

/**
 * Lookup data in the non flat list given a name
 * @param list the list to lookup in
 * @param name the name to search for
 * @return the data of the given element, or NULL if there was none.
 */
MALI_IMPORT void *__mali_named_list_get_non_flat(mali_named_list *list, u32 name);

/**
 * Lookup data in a list given a name
 * @param hlist the list to lookup in
 * @param name the name to search for
 * @return the data of the given element, or NULL if there was none.
 */
MALI_STATIC_FORCE_INLINE  void *__mali_named_list_get(mali_named_list *hlist, u32 name)
{
	MALI_DEBUG_ASSERT_POINTER(hlist);

	/* First try to find it in the flat-array(if the name is in the range) */
	if (name < MALI_NUM_VALUES_FLAT)
	{
		return hlist->flat[ name ];
	}

	return __mali_named_list_get_non_flat(hlist, name);
}


/**
 * Inserts a data element into the named list at position "name"
 * @param list The named list to add to
 * @param name The name to set data for.
 * @param data The data to add
 * @return mali_err_code stating what went wrong, if anything. Possible return values are
 *          MALI_ERR_FUNCTION_FAILED - list already contained something on the name given. Try another name or use the set funciton.
 *          MALI_ERR_OUT_OF_MEMORY - not enough memory to insert the data - operation failed.
 *          MALI_ERR_NO_ERROR - data was added successfully.
 **/
MALI_IMPORT mali_err_code __mali_named_list_insert(mali_named_list *list, u32 name, void *data) MALI_CHECK_RESULT;

/**
 * Sets the data pointer in an existing named element. If the element does not already
 * exists, then it is inserted. Note that no attempt is made to free or otherwise act
 * upon the existing data pointer in an element - it is simply overwritten.
 *
 * @param list The named list to find the element in
 * @param name The name to set data for
 * @param data The data to add
 * @return mali_err_code stating what went wrong, if anything.
 **/
MALI_IMPORT mali_err_code __mali_named_list_set(mali_named_list *list, u32 name, void *data) MALI_CHECK_RESULT;

/**
 * Removes and returns the data in a given slot
 * @param list the list to delete from
 * @param name The name of the list entry to delete
 * @return The data from the given slot, or NULL if none was found.
 */
MALI_IMPORT void *__mali_named_list_remove(mali_named_list *list, u32 name);

/**
 * Return a name that is not currently used in the list.
 * @param list the list to search
 * @return the unused name, or 0 if there were no more unused names
 */
MALI_IMPORT u32 __mali_named_list_get_unused_name(mali_named_list *list);

/**
 * Begins iteration through the named list. Iteration is slower than lookups.
    Each iteration step is still O(1), totally O(size of list, not number of inserted elements )
 * @param list The list of which to iterate through.
 * @param iterator A u32 name, which always holds the name of the current node in the iteration.
 * @return Returns NULL if the iteration step was unsuccessful, otherwise the data at this iteration.
 * @note Adding/removing elements while iterating will result in undefined behavior,
 * @see https://inside.trondheim.arm.com/wiki/index.php/OpenGL_ES_2.x_VG/GLES_Shared_API_Design#Named_List for an in-use example
 */
MALI_IMPORT void    *__mali_named_list_iterate_begin(mali_named_list *list, u32 *iterator);
MALI_IMPORT void    *__mali_named_list_iterate_next(mali_named_list *list, u32 *iterator);

/**
 * Get an exclusive lock on a list, to perform atomic operations on it
 * @param list the list to lock
 */
MALI_IMPORT void __mali_named_list_lock(mali_named_list *list);

/**
 * Release the exclusive lock on a list
 * @param list the list to lock
 */
MALI_IMPORT void __mali_named_list_unlock(mali_named_list *list);

/**
 * Returns the number of elements in the list
 * @param tree The list to inspect
 */
MALI_IMPORT u32 __mali_named_list_size(mali_named_list *tree);


#ifdef __cplusplus
}
#endif


#endif /* MALI_NAMED_LIST */
