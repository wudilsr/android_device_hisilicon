/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_test.h
 * Optional test API declarations
 */

#ifndef _MALI_TEST_H_
#define _MALI_TEST_H_

#include <base/mali_types.h>
/*
 *  Only define the test API if specifically requested.
 */
#ifdef MALI_TEST_API

#define MALI_TEST_ENV                          "MALI_TEST"           /* Environment variable name */
#define MALI_TEST_ENV_MEMFAIL_ITERATION        "MALI_TEST_MEMFAIL_ITERATION"    /* Override memfail iteration */
#define MALI_TEST_ENV_MEMFAIL_FILE_NAME        "MALI_MEM_TEST_MEMFAIL_FILE"     /* Define the output file of memfail */
#define MALI_TEST_ENV_LEAK                     "leak"                /* Setting to test leaks */
#define MALI_TEST_ENV_MEMFAIL                  "memfail"             /* Setting to test memory fails */
#define MALI_TEST_ENV_MEM_DETECT_DOUBLE_FREE   "dblfree"             /* Setting to enable detection of double free */
#define MALI_TEST_ENV_MEM_DETECT_CORRUPTION    "corruption"          /* Setting to test for memory corruption (detect writes to free'd memory) */
#define MALI_TEST_ENV_MEM_STATS_REPORT         "cpumempeak"          /* Setting to report memory usage statistics on exit */
#define MALI_TEST_ENV_MALI_MEM_STATS_REPORT    "malimempeak"         /* Setting to report Mali memory usage statistics on exit */

/* Value of environment variable that should be set for enabling failures
 * for CHECK macro */
#define MALI_TEST_ENV_CHECK_MACROFAIL           "checkfail"

/* Value of environment variable that should be set for enabling failures
 * for MALI_CHECK_NO_ERROR macro */
#define MALI_TEST_ENV_CHECKNOERROR_MACROFAIL    "checknoerrorfail"

/* Value of environment variable that should be set for enabling failures
 * for MALI_CHECK_RANGE macro */
#define MALI_TEST_ENV_CHECKRANGE_MACROFAIL      "checkrangefail"

/* Value of environment variable that should be set for enabling failures
 * for MALI_CHECK_NON_NULL macro */
#define MALI_TEST_ENV_CHECKNONNULL_MACROFAIL    "checknonnullfail"

/* Value of environment variable that should be set for enabling failures
 * for MALI_CHECK_GOTO macro */
#define MALI_TEST_ENV_CHECKGOTO_MACROFAIL       "checkgotofail"

/* File name that is used for keeping track of the count of the iteration */
#define MALI_TEST_FILENAME_MACROFAIL            "MALI_TEST_MACROFAIL"

#ifdef HAVE_ANDROID_OS
#define MALI_TEST_FILENAME_MEMFAIL             "/data/MALI_TEST_MEMFAIL"   /* Filename to store fail number */
#else
#define MALI_TEST_FILENAME_MEMFAIL             "MALI_TEST_MEMFAIL"   /* Filename to store fail number */
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum mali_test_option
{
	MALI_TEST_OPTION_MEM_LEAK                = 0x0001,
	MALI_TEST_OPTION_MEM_MEMFAIL             = 0x0002,
	MALI_TEST_OPTION_MEM_DETECT_DOUBLE_FREE  = 0x0004,
	MALI_TEST_OPTION_MEM_DETECT_CORRUPTION   = 0x0008,
	MALI_TEST_OPTION_MEM_REPORT_PEAK         = 0x0010,

	MALI_TEST_OPTION_MALIMEM_REPORT_PEAK     = 0x0020,
	MALI_TEST_OPTION_CHECK_MACROFAIL         = 0x0040,
	MALI_TEST_OPTION_CHECKNOERROR_MACROFAIL  = 0x0080,
	MALI_TEST_OPTION_CHECKRANGE_MACROFAIL    = 0x0100,
	MALI_TEST_OPTION_CHECKNONNULL_MACROFAIL  = 0x0200,
	MALI_TEST_OPTION_CHECKGOTO_MACROFAIL     = 0x0400
} mali_test_option;

MALI_TEST_VARS_API extern u32 _mali_macro_tracking_features;
MALI_TEST_VARS_API extern u32 _mali_mem_tracking_features;
MALI_TEST_VARS_API extern u32 _mali_macro_call_counter;
MALI_TEST_VARS_API extern u32 _mali_macro_fail_at;

extern void _mali_check_failing(s32 fail_at_invocation);
extern void _mali_test_auto_init(void);

/**
 * Error macros that get called in case of MALI_TEST is defined
 */
#define MALI_TEST_CHECK_NON_NULL(pointer, error_code) do {\
		_mali_test_auto_init();\
		if ( 0 == (_mali_macro_tracking_features & MALI_TEST_OPTION_CHECKNONNULL_MACROFAIL) )\
		{\
			if ( NULL == pointer )\
			{\
				return error_code;\
			}\
		}\
		else\
		{\
			_mali_macro_call_counter++;\
			if (_mali_macro_call_counter==_mali_macro_fail_at)\
			{\
				_mali_check_failing(_mali_macro_call_counter);\
				return error_code;\
			}\
			else\
			{\
				if ( NULL == pointer )\
				{\
					return error_code;\
				}\
			}\
		}\
	} while(0);

#define MALI_TEST_CHECK_NO_ERROR(expression) do {\
		mali_err_code _check_no_error_result;\
		_mali_test_auto_init();\
		if ( 0 == (_mali_macro_tracking_features & MALI_TEST_OPTION_CHECKNOERROR_MACROFAIL) )\
		{\
			_check_no_error_result=(expression); \
			if(_check_no_error_result != MALI_ERR_NO_ERROR) \
				return(_check_no_error_result); \
		}\
		else\
		{\
			_mali_macro_call_counter++;\
			if (_mali_macro_call_counter==_mali_macro_fail_at)\
			{\
				_mali_check_failing(_mali_macro_call_counter);\
				return MALI_ERR_CHECK_ERROR;\
			}\
			else\
			{\
				_check_no_error_result=(expression); \
				if(_check_no_error_result != MALI_ERR_NO_ERROR) \
					return(_check_no_error_result); \
			}\
		}\
	} while(0);

#define MALI_TEST_CHECK(condition, error_code) do {\
		_mali_test_auto_init();\
		if ( 0 == (_mali_macro_tracking_features & MALI_TEST_OPTION_CHECK_MACROFAIL) )\
		{\
			if(!(condition))\
			{\
				return error_code;\
			}\
		}\
		else\
		{\
			_mali_macro_call_counter++;\
			if (_mali_macro_call_counter==_mali_macro_fail_at)\
			{\
				_mali_check_failing(_mali_macro_call_counter);\
				return error_code;\
			}\
			else\
			{\
				if(!(condition))\
				{\
					return error_code;\
				}\
			}\
		}\
	} while(0);

#define MALI_TEST_CHECK_RANGE(value, min, max, error_code) do {\
		_mali_test_auto_init();\
		if ( 0 == (_mali_macro_tracking_features & MALI_TEST_OPTION_CHECKRANGE_MACROFAIL) )\
		{\
			if( !((value)>=(min) && (value)<=(max)) )\
			{\
				return error_code;\
			}\
		}\
		else\
		{\
			_mali_macro_call_counter++;\
			if (_mali_macro_call_counter==_mali_macro_fail_at)\
			{\
				_mali_check_failing(_mali_macro_call_counter);\
				return error_code;\
			}\
			else\
			{\
				if( !((value)>=(min) && (value)<=(max)) )\
				{\
					return error_code;\
				}\
			}\
		}\
	} while(0);

#define MALI_TEST_CHECK_GOTO(condition, label) do {\
		_mali_test_auto_init();\
		if ( 0 == (_mali_macro_tracking_features & MALI_TEST_OPTION_CHECKGOTO_MACROFAIL) )\
		{\
			if(!(condition))\
			{\
				goto label;\
			}\
		}\
		else\
		{\
			_mali_macro_call_counter++;\
			if (_mali_macro_call_counter==_mali_macro_fail_at)\
			{\
				_mali_check_failing(_mali_macro_call_counter);\
				goto label;\
			}\
			else\
			{\
				if(!(condition))\
				{\
					goto label;\
				}\
			}\
		}\
	} while(0);

/* the mapping between the MALI_TEST_ENV* strings and the enums are in src/base/test/mali_test_core.c */

/* core functions */
/**
 * Mali test system open
 * Must be called before calling any of the other test functions
 * Multiple calls supported
 * Each open call must be matched by a @see _mali_test_close call
 * @return A normal Mali error code
 */
MALI_IMPORT mali_err_code _mali_test_open(void);

/**
 * Mali test system close
 * Must be matched by a call to @see _mali_test_open
 */
MALI_IMPORT void _mali_test_close(void);

/**
 * Check if a Mali test option is enabled
 * @param test_option The test option to check for
 * @return MALI_TRUE if the option is enabled, MALI_FALSE if not
 */
MALI_IMPORT mali_bool _mali_test_is_enabled(mali_test_option test_option);

/* memory functions */
/**
 *  Resets the memory allocation state. This must be called at the start
 *  of a test, and sets the current allocation count to 0, as well as initializing
 *  any internal state. If this function is not called, then the operation of any
 *  of the other functions is undefined.
 */
MALI_IMPORT void _mali_test_mem_alloc_init(void);

/**
 *  Gets the current memory allocation count value. This is usually queried at
 *  the end of a dummy test run in order to determine how many allocations happened
 *  in total. Any call to malloc, calloc or realloc is treated as a single allocation
 *  for counting purposes (even if, in the case of realloc, it would not normally cause
 *  an allocation to happen), and increments the current count by 1.
 *
 *  @return The current count value.
 */
MALI_IMPORT u32  _mali_test_mem_alloc_get_count(void);

/**
 *  Sets the number of the allocation to fail. At each allocation, the current allocation
 *  number is compared with the failure count, and if they match then the allocation is
 *  forcibly failed. Note that this happens before the allocation count is incremented
 *  so that the setting the current count to 0 and the failure count to 0 will fail the
 *  next allocation.
 *
 *  @param  count   The number of the allocation to fail.
 */
MALI_IMPORT void _mali_test_mem_alloc_fail(u32 count);

/**
 *  Sets values to fill memory to on allocation and freeing.
 *  If this function is never called, the alloc and free values default
 *  to 0xCDCDCDCD and 0xFDFDFDFD respectively.
 *
 *  @param  alloc_value Value with which to fill newly-allocated memory.
 *  @param  free_value  Value with which to fill newly-freed memory.
 */
MALI_IMPORT void _mali_test_mem_alloc_fill(u32 alloc_value, u32 free_value);

/**
 *  Start memory leak tracking. After this point, all memory allocations
 *  are recorded, and error checking is enabled for double-frees etc.
 *
 *  @see _mali_test_mem_tracking_print_status
 */
MALI_IMPORT void _mali_test_mem_tracking_start(void);

/**
 *  Stop memory leak tracking. After this point, no memory allocations
 *  are recorded, and error checking is disabled for double-frees etc.
 *
 *  @see _mali_test_mem_tracking_print_status
 */
MALI_IMPORT void _mali_test_mem_tracking_stop(void);

/**
 *  Prints a memory leak tracking status report to stdout. This can be
 *  called at any time, even after leak tracking has been stopped.
 *
 *  While memory tracking is on, other error messages may be reported
 *  in the same format, as they are are discovered. This covers cases
 *  such as double-free errors.
 *
 *  The report consists of one line for each error discovered, in a consistent
 *  format:
 *
 *  _mali_test_mem_ ERROR ALLOC ADDRESS SIZE other notes
 *
 *  Each line starts with the literal characters "_mali_test_mem_",so they
 *  can easily be distinguished from other output.
 *
 *  ERROR is an error type identifier, and should be a single token with no
 *  spaces. Typical error types are LEAK, DOUBLEFREE, CORRUPT, etc.
 *
 *  ALLOC is the current allocation number.
 *
 *  ADDRESS is the address of the memory block being considered.
 *
 *  SIZE is the size of the memory block, or 0 if this is not available (e.g.
 *  during a double-free situation).
 *
 *  The rest of the line is reserved for optional free-form notes.
 *
 *  Example:
 *
 *      _mali_test_mem_ LEAK 44 0x00401C4C 64
 *      _mali_test_mem_ CORRUPT 180 0x0048CE84 768 lower guard area corrupt
 */
MALI_IMPORT mali_bool _mali_test_mem_tracking_print_status(void);

/**
 *  Called by the driver at shutdown which supports automatic support for
 *
 */
MALI_IMPORT void _mali_test_auto_term(void);

/** trigger a breakpoint at given allocation */
MALI_IMPORT void _mali_test_set_alloc_break(int alloc_number);


/**
 * Current number of bytes allocated
 * Returns the number of bytes currently allocated
 * @return Number of bytes currently allocated
 */
MALI_IMPORT u32 _mali_test_mem_usage_current(void);

/**
 * Peak number of bytes allocated
 * Returns the peak number of bytes allocated since startup
 * @return Peak number of bytes allocated since startup
 */
MALI_IMPORT u32 _mali_test_mem_usage_peak(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifdef MALI_TEST_API */

#endif /* _MALI_TEST_H_ */
