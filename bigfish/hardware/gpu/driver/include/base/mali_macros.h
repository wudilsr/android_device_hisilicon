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
 * @file mali_macros.h
 * Implementation of common macros.
 */

#ifndef _MALI_MACROS_H_
#define _MALI_MACROS_H_

#include <base/mali_types.h>

/* MALI_IMPORT and MALI_EXPORT macros.
 * For Symbian OS must be defined for both ARMCC and GCCE
 * Must be defined before inclusion of mali_test.h
 */
#ifndef MALI_IMPORT
#if HAVE_ANDROID_OS
#define MALI_IMPORT __attribute__((visibility("default")))
#else
#define MALI_IMPORT
#endif
#endif /* MALI_IMPORT */

#ifndef MALI_EXPORT
#if HAVE_ANDROID_OS
#define MALI_EXPORT __attribute__((visibility("default")))
#else
#define MALI_EXPORT
#endif
#endif /* MALI_EXPORT */

/* the function tracing uses GCC-specific functionality and will only be used
 * with GCC. The "no_instrument_function" attribute is therefore only necessary
 * when using GCC. */
#ifndef MALI_NOTRACE
#if defined(__GNUC__) && defined(MALI_GCC_TRACING)
#define MALI_NOTRACE __attribute__((no_instrument_function))
#else
#define MALI_NOTRACE
#endif
#endif /* MALI_NOTRACE */

#if HAVE_ANDROID_OS
#define MALI_TEST_EXPORT __attribute__((visibility("default")))
#define MALI_TEST_IMPORT __attribute__((visibility("default")))
#else
#define MALI_TEST_EXPORT
#define MALI_TEST_IMPORT
#endif

#if defined(UNDER_CE) && defined(MALI_TEST_API)
#ifdef __BASE_TEST_VARS_EXPORTS
#define MALI_TEST_VARS_API /* already exported in .def file */
#else
#define MALI_TEST_VARS_API __declspec(dllimport)
#endif
#else
#define MALI_TEST_VARS_API
#endif


#include <base/mali_test.h>
/*  *************************************************************************************
 *  Macros for flagging code which is otherwise unclear, odd-looking or which needs to be
 *  flagged to the developer as "special" in some way.
 */

/**
 *  Explicitly ignore a parameter passed into a function, to suppress compiler warnings.
 *  Should only be used with parameter names.
 */
#define MALI_IGNORE(x) (void)x

/**
 *  Flag a cast as a reinterpretation, usually of a pointer type.
 */
#define MALI_REINTERPRET_CAST(type) (type)

/**
 *  Flag a cast as casting away const, usually of a pointer type.
 */
#define MALI_CONST_CAST(type) (type)

/**
 *  Flag a cast as a (potentially complex) value conversion, usually of a numerical type.
 */
#define MALI_STATIC_CAST(type) (type)

/**
 *  Swap two variables of a given type. (e.g. MALI_SWAP(int, x, y); or MALI_SWAP(void*, p, q); )
 *  Should only be used for simple variables.
 */
#define MALI_SWAP(type,a,b) do { type temp; temp=(a); (a)=(b); (b)=temp; } while(0)

/** get the number of elements in an array */
#define MALI_ARRAY_SIZE(x) ( sizeof(x) / sizeof(x[0]) )

/**
 * Align a positive integer to the nearest equal or higher multiple of some base.
 *
 * @param[in] value Unsigned value to be aligned (e.g. a pointer or size in bytes)
 * @param[in] base Coarseness of alignment required (e.g. 4 to align to word boundary)
 *
 * @return Closest multiple of base value that is greater than or equal to the input value.
 */
#define MALI_ALIGN( value, base ) (((value) + ((base) - 1)) & ~((base) - 1))

/*  *************************************************************************************
 *  Macros for standardised error handling

    The reason for the error handling macros is threefold:

    1. It signals to anyone reading the code that this is an error code, not just another return value.
    2. It allows for deliberate triggering of failures, for stress testing.
    3. It insulates the code from any changes made to the error handling mechanims in the future.

    The basic syntax is this:

        CHECK(condition, error_code)

    And can be read as

        Check <condition>, else it's an <error_code>

    Example:

        ptr = _mali_sys_malloc(some_size);
        CHECK( ptr!=NULL, MALI_ERR_OUT_OF_MEMORY);

        Read as: "Check pointer is not null, else it's out of memory"

    There are some variants for common use:

        MALI_CHECK_NO_ERROR(expr)
        This checks if expression is not MALI_ERR_NO_ERROR, and if so, reports it as an error.
        The expression is only evaluated once, so it is safe to use this with function calls.
        This is used to propagate errors up the call stack.

        MALI_CHECK_RANGE(expr, min, max, error_code)
        Checks is expression is in the range min to max, inclusive, and reports an error if not.

        MALI_CHECK_NON_NULL(ptr, error_code)
        Shorthand null pointer check, equivalent to CHECK(ptr!=NULL, error_code).

        MALI_CHECK_GOTO(condition, label)
        Used when we need to clear something up before returning. Read as "check condition is true,
        else goto label". This is useful for cleaning up allocated memory, closing stats intervals,
        or any other cleanup required after an error.

    And some related macros that should be used to highlight that you are signalling an error without a check:

        ERROR(error_code)
        Just reports the error code directly, with no check. Equivalent to CHECK( MALI_FALSE, error_code).

        SUCCESS
        Reports success - equivalent to ERROR(MALI_ERR_NO_ERROR)

    Since it is OK to put critical code in the check, unlike an assert, you can also do things like this:

        MALI_CHECK_NO_ERROR( initialize_module_data() );
        use_module_data();
 */


/**
 *  Fundamental error macro. Reports an error code. This is abstracted to allow us to
 *  easily switch to a different error reporting method if we want, and also to allow
 *  us to search for error returns easily.
 *
 *  Note no closing semicolon - this is supplied in typical usage:
 *
 *  MALI_ERROR(MALI_ERROR_OUT_OF_MEMORY);
 */
#define MALI_ERROR(error_code) return (error_code)
/**
 *  Basic error macro, to indicate success.
 *  Note no closing semicolon - this is supplied in typical usage:
 *
 *  MALI_SUCCESS;
 */
#define MALI_SUCCESS MALI_ERROR(MALI_ERR_NO_ERROR)

/**
 *  Basic error macro, to indicate success in OpenGL
 */
#define GL_SUCCESS MALI_ERROR(GL_NO_ERROR)

/**
 *  Basic error macro. This checks whether the given condition is true, and if not returns
 *  from this function with the supplied error code.
 *
 *  Note that this uses the do-while-0 wrapping to ensure that we don't get problems with dangling
 *  else clauses. Note also no closing semicolon - this is supplied in typical usage:
 *
 *  CHECK((p!=NULL), ERROR_NO_OBJECT);
 */
#define MALI_CHECK(condition, error_code) do { if(!(condition)) MALI_ERROR(error_code); } while(0)

/**
 *  Error propagation macro. If the expression given is anything other than MALI_ERR_NO_ERROR,
 *  then the value is returned from the enclosing function as an error code. This effectively
 *  acts as a guard clause, and propagates error values up the call stack. This uses a
 *  temporary value to ensure that the error expression is not evaluated twice.
 */
#ifdef MALI_TEST_API
#define MALI_CHECK_NO_ERROR(expression) do { MALI_TEST_CHECK_NO_ERROR(expression) } while(0)
#else

#define MALI_CHECK_NO_ERROR(expression) \
	do { mali_err_code _check_no_error_result=(expression); \
		if(_check_no_error_result != MALI_ERR_NO_ERROR) \
			MALI_ERROR(_check_no_error_result); \
	} while(0)

#endif

/**
 *  Range check macro. If the value is outside the given range (min, max), then it
 *  returns from this function with the given error code. Value should not have side-effects
 *  as it is evaluated twice.
 */

#ifdef MALI_TEST_API
#define MALI_CHECK_RANGE(value, min, max, error_code) do { MALI_TEST_CHECK_RANGE(value, min, max, error_code) } while(0)
#else
#define MALI_CHECK_RANGE(value, min, max, error_code) MALI_CHECK( ((value)>=(min) && (value)<=(max)), (error_code) )
#endif

/**
 *  Pointer check macro. Checks non-null pointer.
 */
#ifdef MALI_TEST_API
#define MALI_CHECK_NON_NULL(pointer, error_code) do { MALI_TEST_CHECK_NON_NULL(pointer, error_code) } while(0)
#else
#define MALI_CHECK_NON_NULL(pointer, error_code) MALI_CHECK( ((pointer)!=NULL), (error_code) )
#endif

/**
 *  Error macro with goto. This checks whether the given condition is true, and if not jumps
 *  to the specified label using a goto. The label must therefore be local to the function in
 *  which this macro appears. This is most usually used to execute some clean-up code before
 *  exiting with a call to ERROR.
 *
 *  Like the other macros, this is a macro to allow us to override the condition if we wish,
 *  e.g. to force an error during stress testing.
 */

#ifdef MALI_TEST_API
#define MALI_CHECK_GOTO(condition, label) do { MALI_TEST_CHECK_GOTO(condition, label) } while(0)
#else
#define MALI_CHECK_GOTO(condition, label) do { if(!(condition)) goto label; } while(0)
#endif

/*  *************************************************************************************
 *  Function attributes. These are annotations for functions, which are placed after the
 *  function declaration, e.g.
 *
 *      int foo(int arg) MALI_CHECK_RESULT;
 *
 *  These are compile-time checks only, and are available only on GCC.
 */

/* Supported by GCC, but not ARMCC in gcc emulation mode */
#if defined(__GNUC__) && !defined(__ARMCC_VERSION)
#   define MALI_CHECK_RESULT __attribute__((warn_unused_result))    /**< Callers must always check the result. Should be use for ALL functions that return error codes. */
#   define MALI_NORETURN __attribute__((noreturn)) /**< Function will never return. */
#else
#   define MALI_CHECK_RESULT
#   define MALI_NORETURN
#endif


#if defined(__GNUC__)
/* Supported by GCC and ARMCC in gcc emulation mode */

#   define MALI_WEAK __attribute__((weak))                      /**< Weak symbol - may be overridden in other compilation units */
#   define MALI_DEPRECATED __attribute__((deprecated))          /**< Function is deprecated and should not be used */
#if __GNUC__ >= 4
#   define MALI_VISIBLE  __attribute__ ((visibility ("default")))       /**< Function should be visible from outside the dll */
#else
#   define MALI_VISIBLE
#endif

#elif defined(__ARMCC_VERSION)
/* ARMCC specific */

#   define MALI_WEAK __weak                     /**< Weak symbol - may be overridden in other compilation units */
#   define MALI_DEPRECATED
#   define MALI_VISIBLE  __declspec(dllexport)

#else

#   define MALI_WEAK
#   define MALI_DEPRECATED
#   define MALI_VISIBLE

#endif

/*  *************************************************************************************
 *  Other compiler-dependent macros
 */

/**
 *  The macro MALI_FUNCTION evaluates to the name of the function enclosing
 *  this macro's usage, or "<unknown>" if not supported.
 */
#if defined(_MSC_VER)
#   define MALI_FUNCTION __FUNCTION__
#elif __STDC__  && __STDC_VERSION__ >= 199901L
#   define MALI_FUNCTION __FUNCTION__
#elif defined(__GNUC__) && __GNUC__ >= 2
#   define MALI_FUNCTION __FUNCTION__
#elif defined(__func__)
#   define MALI_FUNCTION __func__
#else
#   define MALI_FUNCTION "<unknown>"
#endif



/* enable ARM and THUMB defines */
#if defined(__GNUC__) && defined(__arm__)
# ifndef ARM
#  define ARM
# endif
# ifdef __thumb__
#  define THUMB
# endif
#elif defined(__CC_ARM)
# ifndef ARM
#  define ARM
# endif
# ifdef __thumb__
#  define THUMB
# endif
#endif

/* TLS macro. MALI_THREAD can be used to declare variables as thread-local,
 * without going through the base driver's posix-like thread functions.
 */
#if defined (__GNUC__) || defined(__CC_ARM)
# define MALI_THREAD __thread
#else
# define MALI_THREAD
#endif

#define MALI_STRINGIZE(arg) #arg
#define MALI_STRINGIZE_MACRO(arg) MALI_STRINGIZE(arg)

#endif /* _MALI_MACROS_H_ */
