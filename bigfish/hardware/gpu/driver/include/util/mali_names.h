/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2008-2010, 2012-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_NAMES_H_
#define _MALI_NAMES_H_

#define MALI_PRODUCT_ID_MASK    0xFFFF0000
#define MALI_VERSION_MAJOR_MASK 0x0000FF00
#define MALI_VERSION_MINOR_MASK 0x000000FF
#define MALI_VERSION_MASK       (MALI_VERSION_MAJOR_MASK | MALI_VERSION_MINOR_MASK)

#define MALI_NAME_PRODUCT_MALI300 "Mali-300"
#define MALI_PRODUCT_ID_PP_MALI300 ((u32)0xCE07)
#define MALI_PRODUCT_ID_GP_MALI300 ((u32)0xC07)

#define MALI_NAME_PRODUCT_MALI400 "Mali-400 MP"
#define MALI_PRODUCT_ID_PP_MALI400 ((u32)0xCD07)
#define MALI_PRODUCT_ID_GP_MALI400 ((u32)0xB07)

#define MALI_NAME_PRODUCT_MALI450 "Mali-450 MP"
#define MALI_PRODUCT_ID_PP_MALI450 ((u32)0xCF07)
#define MALI_PRODUCT_ID_GP_MALI450 ((u32)0xD07)

#if defined(USING_MALI400)

#define MALI_NAME_PRODUCT MALI_NAME_PRODUCT_MALI400
#define MALI_NAME_PP "Mali-400 PP"
#define MALI_NAME_GP "Mali-400 GP"
#define MALI_NAME_L2 "Mali L2 cache"
#define MALI_PRODUCT_ID_PP MALI_PRODUCT_ID_PP_MALI400
#define MALI_PRODUCT_ID_GP MALI_PRODUCT_ID_GP_MALI400
#define MALI_HWVER MALI400_HWVER

#elif defined(USING_MALI450)

#define MALI_NAME_PRODUCT MALI_NAME_PRODUCT_MALI450
#define MALI_NAME_PP "Mali-450 PP"
#define MALI_NAME_GP "Mali-450 GP"
#define MALI_NAME_L2 "Mali L2 cache"
#define MALI_PRODUCT_ID_PP MALI_PRODUCT_ID_PP_MALI450
#define MALI_PRODUCT_ID_GP MALI_PRODUCT_ID_GP_MALI450
#define MALI_HWVER MALI450_HWVER

#else
#error "No known Mali core defined"
#endif

#endif /* _MALI_NAMES_H_ */
