/******************************************************************************

  Copyright (C), 2013-2023, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : svr_platformcheck.h
  Version       : Initial Draft
  Author        :
  Created       : 2013/09/03
  Description   : platform check head file for hidolphin component.
  History       :
  1.Date        : 2013/09/03
    Author      : dingsongxing
    Modification: Created file

*******************************************************************************/

#ifndef __SVR_PLATFORM_CHECK_H__
#define __SVR_PLATFORM_CHECK_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "hi_common.h"

//////////////////////////////////////////////////////////////////////////////////////
/// STATIC CONST Variable
//////////////////////////////////////////////////////////////////////////////////////

/// STATIC Variable

/// DEFINATION MACRO
#define SVR_PLATFORMCHECK_SUCCESS     0x304568
#define SVR_PLATFORMCHECK_FAILURE     0x508727

///function

/**
\brief check whether support the platform
\attention \n
This interface should be called When hidolphin component initialization.

\param[in] none
\retval ::SVR_PLATFORMCHECK_SUCCESS  platform check pass
\retval ::SVR_PLATFORMCHECK_FAILURE  platform check fail
\see \n

*/
HI_S32 SVR_PlatformCheck(HI_VOID);


#ifdef __cplusplus
}
#endif

#endif //__SVR_PLATFORM_CHECK_H__
