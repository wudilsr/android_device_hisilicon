/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : util.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/12/17
  Description   : xmem.c header file
  History       :
  1.Date        : 2010/12/17
    Author      : dvb
    Modification: Created file

******************************************************************************/

#ifndef __UTIL_H__
#define __UTIL_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#include "hi_type.h"
#include "hi_ref_mod.h"

/**************************************************
\brief CRC verify
\attention \n
无
\param[in] ulCrc the last calculated crc value
\param[in] pucData pointer to data
\param[in] ulLen length of data
\param[out] pulResult return a crc32 value

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 失败

\see \n
无
**************************************************/

HI_S32 HI_UTIL_CRC(const HI_U8* pucData, HI_U32 ulLen, HI_U32 *pulResult);

/****************************
\brief CRC verify
\support Accumulate verify
****************************/
HI_S32 HI_UTIL_CRCAccumulate32(HI_U32 ulCrc,
                                const HI_U8* pucData,
                                HI_U32 ulLen,
                                HI_U32 *pulResult);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif /* End of #ifndef __UTIL_H__ */
