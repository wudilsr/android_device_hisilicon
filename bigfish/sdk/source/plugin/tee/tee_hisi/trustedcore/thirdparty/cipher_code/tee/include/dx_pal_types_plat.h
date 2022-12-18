/*******************************************************************  
* (c) Copyright 2011-2012 Discretix Technologies Ltd.              *
* This software is protected by copyright, international           *
* treaties and patents.                                            *
* Use of this Software as part of or with the Discretix CryptoCell *
* or Packet Engine products is governed by the products'           *
* commercial end user license agreement ("EULA").                  *
* It is possible that copies of this Software might be distributed *
* under some type of GNU General Public License ("GPL").           *
* Notwithstanding any such distribution under the terms of GPL,    *
* GPL does not govern the use of this Software as part of or with  *
* the Discretix CryptoCell or Packet Engine products, for which a  *
* EULA is required.                                                *
* If the product's EULA allows any copy or reproduction of this    *
* Software, then such copy or reproduction must include this       *
* Copyright Notice as well as any other notices provided           *
* thereunder.                                                      *
********************************************************************/

 
#ifndef DX_PAL_TYPES_PLAT_H
#define DX_PAL_TYPES_PLAT_H
/* Host specific types for standard (ISO-C99) compilant platforms */

#include "tee_internal_api.h"

#define DX_NULL NULL

typedef unsigned int            DxUint_t;
typedef uint8_t                 DxUint8_t;
typedef uint16_t                DxUint16_t;
typedef uint32_t                DxUint32_t;

typedef int                   	DxInt_t;
typedef int8_t                  DxInt8_t;
typedef int16_t                 DxInt16_t;
typedef int32_t                 DxInt32_t;

typedef char                    DxChar_t;
typedef short                   DxWideChar_t;

#endif /*DX_PAL_TYPES_PLAT_H*/
