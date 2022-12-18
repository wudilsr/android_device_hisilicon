/*
 * svr_sys_android.c
 *
 *  Created on: 2014Äê9ÔÂ23ÈÕ
 *      Author: z00187490
 */
#include <stdio.h>
#include <cutils/properties.h>
#include "svr_sys.h"

HI_S32 platform_set_property(const HI_CHAR* pszKey, const HI_CHAR* pszVal)
{
    return property_set(pszKey, pszVal);
}

HI_S32 platform_get_property(const HI_CHAR* pszKey, HI_CHAR* pszVal, HI_S32 s32Len)
{
    char tmp[PROPERTY_VALUE_MAX];

    if (pszVal && property_get(pszKey, tmp, NULL)) {
        snprintf(pszVal, s32Len, "%s", tmp);
        return HI_SUCCESS;
    }
    return HI_FAILURE;
}

