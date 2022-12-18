/*
 * svr_sys.h
 *
 *  Created on: 2014Äê9ÔÂ23ÈÕ
 *      Author: z00187490
 */

#ifndef SVR_SYS_H_
#define SVR_SYS_H_

#include <hi_type.h>

HI_S32 platform_set_property(const HI_CHAR* pszKey, const HI_CHAR* pszVal);

HI_S32 platform_get_property(const HI_CHAR* pszKey, HI_CHAR* pszVal, HI_S32 s32Len);



#endif /* SVR_SYS_H_ */
