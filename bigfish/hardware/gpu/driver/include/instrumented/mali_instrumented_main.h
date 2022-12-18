/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011, 2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_INSTRUMENTED_MAIN_H_
#define _MALI_INSTRUMENTED_MAIN_H_

#include "mali_system.h"

/**
 * Initialize instrumentation. Called when EGL initializes for the first time.
 * @return MALI_TRUE on success, MALI_FALSE on failure
 */
MALI_IMPORT mali_bool MALI_CHECK_RESULT _mali_instrumented_init(void);

/**
 * Terminates instrumentation. Called when EGL terminates.
 */
MALI_IMPORT void _mali_instrumented_term(void);

#endif /* _MALI_INSTRUMENTED_MAIN_H_ */
