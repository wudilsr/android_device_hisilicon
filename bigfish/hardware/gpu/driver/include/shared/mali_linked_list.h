/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2010, 2012-2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_linked_list.h
 * @brief interface for mali_linked_list
 */

#ifndef MALI_LINKED_LIST_H
#define MALI_LINKED_LIST_H

#include <mali_system.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *mali_linked_list_cb_param;
typedef void (*mali_linked_list_cb_func)(mali_linked_list_cb_param);

/**
 * An entry in the list of integer linked-pointers. Currently implemented as a linked list.
 */
typedef struct mali_linked_list_entry_
{
	struct mali_linked_list_entry_ *next; /**< pointer to the next entry in list. NULL if this is the last entry */
	struct mali_linked_list_entry_ *prev; /**< pointer to the previous entry in list. NULL if this is the first entry */
	void *data;                           /**< a pointer to the actual data structure */
} mali_linked_list_entry;

/**
 * The container structure for the linked list. This is used as the handle to all methods.
 */
typedef struct mali_linked_list_
{
	mali_linked_list_entry *first; /**< pointer to the first entry in list. NULL if the list is empty */
	mali_linked_list_entry *last;  /**< pointer to the last entry in list. NULL if the list is empty */

	mali_mutex_handle list_mutex; /**< The mutex lock for this list */

} mali_linked_list;

/**
 * Initialize a linked list. this function must always be called before any other operation
 * @param list the list to be initialized
 * @note in the current implementation, this only sets a couple of pointers to NULL. This behavour is subject to change, and that memseting might not be enough in the future.
 * @return an error code
 */
MALI_IMPORT mali_err_code MALI_CHECK_RESULT __mali_linked_list_init(mali_linked_list *list);

/**
 * Delete the contents of a linked list. this fuction must be called after operating on it, to ensure that memory has been freed.
 * @param list the list to be deinited
 * @note the memory pointed to by the entries is not deleted, so the list should be traversed to delete all memory not deleted elsewhere before calling this fuction.
 */
MALI_IMPORT void __mali_linked_list_deinit(mali_linked_list *list);

/**
 * Allocates a new linked list.
 * @return a new list, or NULL if allocation failed.
 * @note Consider using a stack/non-pointer linked list instead, and call init. less mallocs make jack a happy boy.
 */
MALI_IMPORT mali_linked_list *MALI_CHECK_RESULT __mali_linked_list_alloc(void);

/**
 * Frees an allocated list
 * @param list list to free
 * @note Consider using a stack/non-pointer list instad, and call deinit. ; that way this function should never be used.
 */
MALI_IMPORT void __mali_linked_list_free(mali_linked_list *list);

/**
 * Removes all entries from a list
 * @param list list to free
 * @param callback callback function to call for all data-members
 */
MALI_IMPORT void __mali_linked_list_empty(mali_linked_list *list, mali_linked_list_cb_func callback);


/**
 * Returns the first entry in a list.
 * @param list the given list
 * @return the pointer to the first element, NULL if there is no elements.
 */
MALI_IMPORT mali_linked_list_entry *__mali_linked_list_get_first_entry(mali_linked_list *list);

/**
 * Returns the next element in a list, given an entry.
 * @param entry the current entry to traverse from
 * @return the pointer to the next element, NULL if entry was the last one.
 */
MALI_IMPORT mali_linked_list_entry *__mali_linked_list_get_next_entry(mali_linked_list_entry *entry);

/**
 * Remove an entry from a list
 * @param list the list to remove from
 * @param entry the element to remove
 * @return the pointer to the next valid element after deletion, NULL if element was the last one in the list.
 */
MALI_IMPORT mali_linked_list_entry *__mali_linked_list_remove_entry(mali_linked_list *list, mali_linked_list_entry *entry);

/**
 * Creates a new linked list node with the input data, adds it to end of linked list
 * @param list The list to add
 * @param data The data to add
 */
MALI_IMPORT mali_err_code MALI_CHECK_RESULT __mali_linked_list_insert_data(mali_linked_list *list, void *data);

/**
 * Get an exclusive lock on a list, to perform atomic operations on it
 * @param list the list to lock
 */
MALI_IMPORT void __mali_linked_list_lock(mali_linked_list *list);

/**
 * Release the exclusive lock on a list
 * @param list the list to lock
 */
MALI_IMPORT void __mali_linked_list_unlock(mali_linked_list *list);


#ifdef __cplusplus
}
#endif

#endif /* MALI_LINKED_LIST_H */
