/*
 *  $Id: macros.h,v 1.4 2003/05/16 12:27:29 bootc Exp $
 *  libdaap: macros.h
 *
 *  Created by Chris Boot on Thu May 08 2003.
 *  Copyright (C) 2003 Chris Boot
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef __DAAP_MACROS_H__
#define __DAAP_MACROS_H__
#include <string.h>
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if WORDS_BIGENDIAN

/*
 *  UINT16_SWAB()
 *
 *  Discussion:
 *    Converts a 16-bit integer from big-endian format to the machine's
 *    native format, or vice versa.
 */
#define UINT16_SWAB(x) \
    ((uint16_t)(x))

/*
 *  UINT32_SWAB()
 *
 *  Discussion:
 *    Converts a 32-bit integer from big-endian format to the machine's
 *    native format, or vice versa.
 */
#define UINT32_SWAB(x) \
    ((uint32_t)(x))

/*
 *  UINT64_SWAB()
 *
 *  Discussion:
 *    Converts a 64-bit integer from big-endian format to the machine's
 *    native format, or vice versa.
 */
#define UINT64_SWAB(x) \
    ((uint64_t)(x))

/*
 *  FOUR_CHAR_CODE()
 *
 *  Discussion:
 *    Builds a uint32_t which consists of four char constants tacked
 *    together.  FOUR_CHAR_CODE('a', 'b', 'c', 'd') is equivalent to 'abcd'
 *    but apparently the latter isn't portable (and isn't endian-safe).
 */
#define FOUR_CHAR_CODE(a, b, c, d) \
    (((uint32_t)(a)) << 24) | \
    (((uint32_t)(b)) << 16) | \
    (((uint32_t)(c)) << 8) | \
    ((uint32_t)(d))

#else /* WORDS_BIGENDIAN */

#define UINT16_SWAB(x) \
    (((uint16_t)((x) & 0x00FF)) << 8) | \
    (((uint16_t)((x) & 0xFF00)) >> 8)

#define UINT32_SWAB(x) \
    (((uint32_t)((x) & 0x000000FF)) << 24) | \
    (((uint32_t)((x) & 0x0000FF00)) << 8) | \
    (((uint32_t)((x) & 0x00FF0000)) >> 8) | \
    (((uint32_t)((x) & 0xFF000000)) >> 24)

#define UINT64_SWAB(x) \
    (((uint64_t)((x) & 0x00000000000000FFLL)) << 56) | \
    (((uint64_t)((x) & 0x000000000000FF00LL)) << 40) | \
    (((uint64_t)((x) & 0x0000000000FF0000LL)) << 24) | \
    (((uint64_t)((x) & 0x00000000FF000000LL)) << 8) | \
    (((uint64_t)((x) & 0x000000FF00000000LL)) >> 8) | \
    (((uint64_t)((x) & 0x0000FF0000000000LL)) >> 24) | \
    (((uint64_t)((x) & 0x00FF000000000000LL)) >> 40) | \
    (((uint64_t)((x) & 0xFF00000000000000LL)) >> 56)

#define FOUR_CHAR_CODE(a, b, c, d) \
    ((uint32_t)(a)) | \
    (((uint32_t)(b)) << 8) | \
    (((uint32_t)(c)) << 16) | \
    (((uint32_t)(d)) << 24)

#endif

#endif /* __DAAP_MACROS_H__ */
