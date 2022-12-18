/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2005-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_debug.h
 *
 * The file include several useful macros for debugging and printing.
 * - MALI_PRINTF(...)           Do not use this function: Will be included in Release builds.
 * - MALI_DEBUG_TRACE()         Prints current location in code.
 * - MALI_DEBUG_PRINT(nr, (X) ) Prints the second argument if nr<=MALI_DEBUG_LEVEL.
 * - MALI_DEBUG_TPRINT(nr, X )  Prints the source trace and second argument if nr<=MALI_DEBUG_LEVEL.
 * - MALI_DEBUG_ERROR( (X) )    Prints an errortext, a source trace, and the given error message.
 * - MALI_DEBUG_ASSERT(exp,(X)) If the asserted expr is false, the program will exit.
 * - MALI_DEBUG_ASSERT_RANGE(x, min, max) Triggers if variable x is not between or equal to max and min.
 * - MALI_DEBUG_ASSERT_LEQ(x, max) Triggers if variable x is not less than equal to max.
 * - MALI_DEBUG_ASSERT_POINTER(pointer)  Triggers if the pointer is a zero pointer.
 * - MALI_DEBUG_CODE( X )       The code inside the macro is only copiled in Debug builds.
 *
 * The (X) means that you must add an extra parantese around the argumentlist.
 *
 * The  printf function: MALI_PRINTF(...) is routed to _mali_sys_printf
 *
 * Suggested range for the DEBUG-LEVEL is [1:6] where
 * [1:2] Is messages with highest priority, indicate possible errors.
 * [3:4] Is messages with medium priority, output important variables.
 * [5:6] Is messages with low priority, used during extensive debugging.
 *
 */
#ifndef _MALI_DEBUG_H_
#define _MALI_DEBUG_H_

#include <base/mali_runtime.h>
#include <shared/mali_systrace.h>

#ifdef __cplusplus
extern "C" {
#endif

#if MALI_MEM_STATUS || MALI_MEMORY_PROFILING
extern u32 mali_global_frame_counter;
#endif

/* START: Configuration */
#ifndef MALI_PRINTF
#define MALI_PRINTF _mali_sys_printf
#endif /* MALI_PRINTF */

#ifndef MALI_PRINT_FLUSH
#define MALI_PRINT_FLUSH do {} while (0)
#endif /* MALI_PRINT_FLUSH */

#ifndef MALI_DEBUG_BREAKPOINT
#define MALI_DEBUG_BREAKPOINT _mali_sys_break
#endif /* MALI_DEBUG_BREAKPOINT */

#ifndef MALI_DEBUG_LEVEL
#define MALI_DEBUG_LEVEL 1
#endif /* MALI_DEBUG_LEVEL */

#ifndef MALI_DEBUG_ERROR_START_MSG
#define MALI_DEBUG_ERROR_START_MSG do {\
		MALI_PRINTF("*********************************************************************\n");\
		MALI_PRINT_FLUSH; } while (0)
#endif /* MALI_DEBUG_ERROR_START_MSG */

#ifndef MALI_DEBUG_ERROR_STOP_MSG
#define MALI_DEBUG_ERROR_STOP_MSG  do { MALI_PRINTF("\n"); MALI_PRINT_FLUSH; } while (0)
#endif /* MALI_DEBUG_ERROR_STOP_MSG */

#ifndef MALI_ASSERT_QUIT_CMD
#define MALI_ASSERT_QUIT_CMD    _mali_sys_abort()
#endif /* MALI_ASSERT_QUIT_CMD */
/* STOP: Configuration */

/**
 * @def     MALI_DEBUG_TRACE()
 * @brief   Prints current location in code.
 *          Can be turned off by defining MALI_DEBUG_SKIP_TRACE
 */

#ifndef MALI_DEBUG_SKIP_TRACE
#ifndef MALI_DEBUG_SKIP_PRINT_FUNCTION_NAME
#define MALI_DEBUG_TRACE()  do { MALI_PRINTF( "In file: " __FILE__ \
	        "  function: %s()   line:%4d\n" , MALI_FUNCTION, __LINE__);  MALI_PRINT_FLUSH; } while (0)
#else
#define MALI_DEBUG_TRACE()  do { MALI_PRINTF( "In file: " __FILE__ "  line:%4d\n" , __LINE__);  MALI_PRINT_FLUSH; } while (0)
#endif /* MALI_DEBUG_SKIP_PRINT_FUNCTION_NAME */
#else
#define MALI_DEBUG_TRACE()
#endif /* MALI_DEBUG_SKIP_TRACE */

/**
 * @def     MALI_DEBUG_PRINT(nr, (X) )
 * @brief   Prints the second argument if nr<=MALI_DEBUG_LEVEL.
 *          Can be turned off by defining MALI_DEBUG_SKIP_PRINT
 * @param   nr   If nr <= MALI_DEBUG_LEVEL, we print the text.
 * @param   X  A parantese with the contents to be sent to MALI_PRINTF
 */
#ifndef MALI_DEBUG_SKIP_PRINT
#define MALI_DEBUG_PRINT(nr, X )  do { if ( nr<=MALI_DEBUG_LEVEL ) { MALI_PRINTF X ; MALI_PRINT_FLUSH; } } while (0)
#else
#define MALI_DEBUG_PRINT(nr, X )
#endif /* MALI_DEBUG_SKIP_PRINT */

/**
 * @def     MALI_DEBUG_TPRINT(nr, (X) )
 * @brief   Prints the second argument if nr<=MALI_DEBUG_LEVEL.
 *          Can be turned off by defining MALI_DEBUG_SKIP_TPRINT.
 *          Can be shortened by defining MALI_DEBUG_TPRINT_SKIP_FUNCTION.
 * @param   nr   If nr <= MALI_DEBUG_LEVEL, we print the text.
 * @param   X  A parantese with the contents to be sent to MALI_PRINTF
 */

/* helper to handle if the function name should be included or not */
#ifndef MALI_DEBUG_TPRINT_SKIP_FUNCTION
#define MALI_DEBUG_TPRINT_INTERN do {MALI_PRINTF( "" __FILE__ " %s()%4d " , MALI_FUNCTION, __LINE__); MALI_PRINT_FLUSH; }  while (0)
#else
#define MALI_DEBUG_TPRINT_INTERN do {MALI_PRINTF( "" __FILE__ "%4d " , __LINE__); MALI_PRINT_FLUSH; }  while (0)
#endif /* MALI_DEBUG_TPRINT_SKIP_FUNCTION */

#ifndef MALI_DEBUG_SKIP_TPRINT
#define MALI_DEBUG_TPRINT(nr, X ) \
	do{\
		if ( nr<=MALI_DEBUG_LEVEL )\
		{\
			MALI_DEBUG_TPRINT_INTERN;\
			MALI_PRINTF X ;\
			MALI_PRINT_FLUSH;\
		}\
	} while (0)
#else
#define MALI_DEBUG_TPRINT(nr, X )
#endif /* MALI_DEBUG_SKIP_TPRINT */

/**
 * @def     MALI_DEBUG_ERROR( (X) )
 * @brief   Prints an errortext, a source Trace, and the given error message.
 *          Prints filename, function, linenr, and the given error message.
 *          The error message must be inside a second parantese.
 *          The error message is written on a separate line, and a NL char is added.
 *          Can be turned of by defining MALI_DEBUG_SKIP_ERROR;
 *          You do not need to type the words ERROR in the message, since it will
 *          be added anyway.
 *
 * @note    You should not end the text with a newline, since it is added by the macro.
 * @note    You should not write "ERROR" in the text, since it is added by the macro.
 * @param    X  A parantese with the contents to be sent to MALI_PRINTF
 */

#ifndef MALI_DEBUG_SKIP_ERROR
#define MALI_DEBUG_ERROR( X )  \
	do{ \
		MALI_DEBUG_ERROR_START_MSG;\
		MALI_PRINTF("ERROR: ");\
		MALI_PRINT_FLUSH;\
		MALI_DEBUG_TRACE(); \
		MALI_PRINTF X ; \
		MALI_PRINT_FLUSH;\
		MALI_DEBUG_ERROR_STOP_MSG;\
	} while (0)
#else
#define MALI_DEBUG_ERROR( X ) do{ ; } while ( 0 )
#endif /* MALI_DEBUG_SKIP_ERROR */

/**
 * @def     MALI_DEBUG_ASSERT(expr, (X) )
 * @brief   If the asserted expr is false, the program will exit.
 *          Prints filename, function, linenr, and the given error message.
 *          The error message must be inside a second parantese.
 *          The error message is written on a separate line, and a NL char is added.
 *          Can be turned of by defining MALI_DEBUG_SKIP_ERROR;
 *          You do not need to type the words ASSERT in the message, since it will
 *          be added anyway.
 *
 * @param    X  A parantese with the contents to be sent to MALI_PRINTF
 *          Prints filename, function, linenr, and the error message
 *          on a separte line. A newline char is added at the end.
 *          Can be turned of by defining MALI_DEBUG_SKIP_ASSERT
 * @param   expr  Will exit program if \a expr is false;
 * @param   (X)  Text that will be written if the assertion toggles.
 */

#ifndef MALI_DEBUG_SKIP_ASSERT
#define MALI_DEBUG_ASSERT(expr, X ) \
	do{\
		if ( !(expr) ) \
		{ \
			MALI_DEBUG_ERROR_START_MSG;\
			MALI_PRINTF("ASSERT EXIT: ");\
			MALI_PRINT_FLUSH;\
			MALI_DEBUG_TRACE(); \
			MALI_PRINTF X ; \
			MALI_PRINT_FLUSH;\
			MALI_DEBUG_ERROR_STOP_MSG;\
			MALI_ASSERT_QUIT_CMD;\
		}\
	} while (0)
#else
#define MALI_DEBUG_ASSERT(expr, X)
#endif /* MALI_DEBUG_SKIP_ASSERT */


/**
 * @def     MALI_DEBUG_ASSERT_POINTER(pointer)
 * @brief   If the asserted pointer is NULL, the program terminates and TRACE info is printed
 *          The checking is disabled if "MALI_DEBUG_SKIP_ASSERT" is defined.
 */
#define MALI_DEBUG_ASSERT_POINTER(pointer) MALI_DEBUG_ASSERT(pointer, ("Null pointer " #pointer) )

/**
 * @def     MALI_DEBUG_ASSERT_HANDLE(handle)
 * @brief   If the asserted handle is not a valid handle, the program terminates and TRACE info is printed
 *          The checking is disabled if "MALI_DEBUG_SKIP_ASSERT" is defined.
 */
#define MALI_DEBUG_ASSERT_HANDLE(handle) MALI_DEBUG_ASSERT(MALI_NO_HANDLE != (handle), ("Invalid handle " #handle) )

/**
 * @def     MALI_DEBUG_ASSERT_ALIGNMENT(ptr, align)
 * @brief   If the asserted pointer is  not aligned to align, the program terminates with trace info printed.
 *          The checking is disabled if "MALI_DEBUG_SKIP_ASSERT" is defined.
 */
#ifndef MALI_DEBUG_SKIP_ASSERT
#define MALI_DEBUG_ASSERT_ALIGNMENT(ptr, align) do { \
		MALI_DEBUG_ASSERT(0 == ((align) & ((align) - 1)), \
		                  ("align %d is not a power-of-two", (align))); \
		MALI_DEBUG_ASSERT(0 == (((uintptr_t)(ptr)) & ((align) - 1)), \
		                  ("ptr %p not aligned to %d bytes", (uintptr_t)(ptr), (align))); \
	} while (0)
#else
#define MALI_DEBUG_ASSERT_ALIGNMENT(ptr, align)
#endif /* MALI_DEBUG_SKIP_ASSERT */

/**
 * @def     MALI_DEBUG_ASSERT_RANGE(x,min,max)
 * @brief   If variable x is not between or equal to max and min, the assertion triggers.
 *          The checking is disabled if "MALI_DEBUG_SKIP_ASSERT" is defined.
 */
#define MALI_DEBUG_ASSERT_RANGE(x, min, max) \
	MALI_DEBUG_ASSERT( (x) >= (min) && (x) <= (max), \
	                   (#x " out of range (%2.2f)", (double)x ) \
	                 )

/**
 * @def     MALI_DEBUG_ASSERT_LEQ(x,max)
 * @brief   If variable x is less than or equal to max, the assertion triggers.
 *          The checking is disabled if "MALI_DEBUG_SKIP_ASSERT" is defined.
 */
#define MALI_DEBUG_ASSERT_LEQ(x, max) \
	MALI_DEBUG_ASSERT( (x) <= (max), \
	                   (#x " out of range (%2.2f)", (double)x ) \
	                 )

/**
 * @def     MALI_DEBUG_CODE( X )
 * @brief   Run the code X on debug builds.
 *          The code will not be used if MALI_DEBUG_SKIP_CODE is defined .
 *
 */
#ifdef MALI_DEBUG_SKIP_CODE
#define MALI_DEBUG_CODE( X )
#else
#define MALI_DEBUG_CODE( X ) X
#endif /* MALI_DEBUG_SKIP_CODE */

#ifdef __cplusplus
}
#endif

#endif /* _MALI_DEBUG_H_ */
