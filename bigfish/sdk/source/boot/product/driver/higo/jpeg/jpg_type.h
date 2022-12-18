/***********************************************************************************
 *             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: jpg_type.h
 * Description: 
 *
 * History:
 * Version   Date             Author     DefectNum    Description
 * main\1    2008-03-27       d37024                  Create this file.
 ***********************************************************************************/

#ifndef  _JPG_TYPE_H_
#define  _JPG_TYPE_H_
 
#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /* __cplusplus */
#endif  /* __cplusplus */


typedef enum hiJPG_INTTYPE_E
{
    JPG_INTTYPE_NONE = 0, 
    JPG_INTTYPE_CONTINUE, 
    JPG_INTTYPE_FINISH,   
    JPG_INTTYPE_ERROR,    
    JPG_INTTYPE_BUTT
}JPG_INTTYPE_E;

typedef struct hiJPG_GETINTTYPE_S
{
    JPG_INTTYPE_E IntType;  
    HI_U32 TimeOut;           
}JPG_GETINTTYPE_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#endif /* _JPG_TYPE_H_*/



