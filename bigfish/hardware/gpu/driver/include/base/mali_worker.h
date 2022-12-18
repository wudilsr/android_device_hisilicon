/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_worker.h
 * @brief Worker thread implementation.
 */

#ifndef _MALI_WORKER_H_
#define _MALI_WORKER_H_

#include <mali_system.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Handle/pointer to worker system internal data structures.
 */
typedef void *mali_base_worker_handle;

/**
 * An invalid worker handle. Used to signal errors.
 */
#define MALI_BASE_WORKER_NO_HANDLE ((mali_base_worker_handle)(void *)NULL)

/**
 * Type of callback function that will be executed by the worker thread.
 */
typedef void (*mali_base_worker_task_proc)(void *);

/**
 * Create and start worker thread.
 *
 * @param idle_policy Set scheduling policy to idle if MALI_TRUE. Leave unchanged if MALI_FALSE.
 * @return The handle to the worker thread object or MALI_BASE_WORKER_NO_HANDLE if the worker thread
 *         creation failed for some reason.
 */
mali_base_worker_handle _mali_base_worker_create(mali_bool idle_policy);

/**
 * Execute any remaining tasks, stop the worker thread and deallocate internal resources.
 *
 * @param worker Handle to the worker thread that should be destroyed.
 * @note This function will block until all tasks in the queue are done.
 */
void _mali_base_worker_destroy(mali_base_worker_handle worker);

/**
 * Add task to worker thread for execution and return immediately.  The tasks are stored in a FIFO
 * queue.
 *
 * @param worker Handle to the worker thread that should handle the task.
 * @param task_proc A function that will be executed in the worker thread.
 * @param task_param A parameter passed to the task function.
 * @return MALI_ERR_NO_ERROR if the task was added successfully, MALI_ERR_OUT_OF_MEMORY if the
 *         function was unable to add the task due to an OOM situation or MALI_ERR_FUNCTION_FAILED
 *         if the worker thread has been signaled to shut down.
 * @note If MALI_INSTRUMENTED is true, the active instrumented frame should be set before adding a task.
 */
mali_err_code _mali_base_worker_task_add(mali_base_worker_handle worker, mali_base_worker_task_proc task_proc, void *task_param);

/**
 * Signal to the worker thread to quit and wait for thread to end. Will effectively execute all tasks in FIFO.
 * Thread will be left in terminated state and all attempts at adding tasks will fail from this point.
 *
 * NB! The thread will not be cleaned up. A call to _mali_base_worker_destroy is needed for proper cleanup.
 *
 * Usecase: Safely ensure that no more work is outstanding nor can be added to the thread.
 *
 * @param worker Handle to worker thread that should quit working.
 */
void _mali_base_worker_quit(mali_base_worker_handle worker);


#ifdef __cplusplus
}
#endif

#endif /* !_MALI_WORKER_H_ */
