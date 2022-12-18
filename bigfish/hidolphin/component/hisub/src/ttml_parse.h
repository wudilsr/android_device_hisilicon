/**
\file
\brief ttml 解析头文件
\copyright Shenzhen Hisilicon Co., Ltd.
\date 2008-2018
\version draft
\author l00167705
\date 2013-9-2
*/

#ifndef __TTML_PARSE_H__
#define __TTML_PARSE_H__

/* add include here */
#include "subparse.h"

#ifdef __cplusplus
extern "C" {
#endif
/***************************** Macro Definition ******************************/



/*************************** Structure Definition ****************************/



/********************** Global Variable declaration **************************/



/******************************* API declaration *****************************/
int TTML_Parse(HI_SUB_PROTOCOL_S* pstProtocl,HI_S64 s64PtsAjustTimeMs);


#ifdef __cplusplus
}
#endif
#endif /* __TTML_PARSE_H__ */
