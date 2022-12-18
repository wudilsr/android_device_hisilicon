/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : secure_extension.h
* Description : external used
* Platform    :
* Author      :
* Version     : 1.0
* Date        :
* Notes       :
*
*------------------------------------------------------------------------------
* Modifications:
*   Date         Author          Modifications
    2013-02-19   h00206996       created
*******************************************************************************/
/*******************************************************************************
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
*******************************************************************************/

#ifndef _SECURE_EXTENSION_H
#define _SECURE_EXTENSION_H

#define SEC_SUSPEND_FLAG   0xF800FFF0
#define SEC_SUSPEND_MARK   0xA5A5A5A5
/*These addresses below defined in trustcore.ld file.
  Ensure values consistent in both places.
*/
#define SEC_MONITOR_ADDRESS 0xF800F800


/*Monitor API enum*/
#define MAPI_TZ_API           0x1
#define MAPI_RET_FROM_SECURE  0x2
#define MAPI_FIRST_SWITCH     0xf0
#define MAPI_SUSPEND_TASK     0xf1
#define MAPI_L2CACHE_POWER    0xf3
#define MAPI_L2CACHE_SR       0xf5
#define MAPI_SECURERAM_S      0xf6
#define MAPI_SECURERAM_R      0xf7
#define MAPI_SECURERAM_C      0xf8
#define MAPI_DMA_CFG_RESUME   0xfd
#define MAPI_SR_BACK_TO_NS    0xfe

#endif
