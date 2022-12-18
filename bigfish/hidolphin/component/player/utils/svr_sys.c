/*
 * svr_sys.c
 *
 *  Created on: 2014Äê9ÔÂ23ÈÕ
 *      Author: z00187490
 */

#include "svr_sys.h"

HI_S32 SVR_SYS_SetProperty(const HI_CHAR* pszKey, const HI_CHAR* pszVal)
{
    return platform_set_property(pszKey, pszVal);
}

HI_S32 SVR_SYS_GetProperty(const HI_CHAR* pszKey, HI_CHAR* pszVal, HI_S32 s32Len)
{
    return platform_get_property(pszKey, pszVal, s32Len);
}


