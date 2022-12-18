/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_INTERFACE_H_
#define _MALI_INTERFACE_H_

/* MALI_IMPORT and MALI_EXPORT macros.
 * For Symbian OS must be defined for both ARMCC and GCCE
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

#endif /* _MALI_INTERFACE_H_ */
