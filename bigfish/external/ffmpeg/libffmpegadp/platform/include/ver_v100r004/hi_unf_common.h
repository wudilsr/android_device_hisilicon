/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_disp.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/17
  Description   :
  History       :
  1.Date        : 2009/12/17
    Author      : w58735
    Modification: Created file

*******************************************************************************/

#ifndef __HI_UNF_COMMON_H__
#define __HI_UNF_COMMON_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_common.h"
#include "hi_unf_audio.h"
#include "hi_unf_video.h"

/**Defines the stream buffer.*/
/**CNcomment: ������������ṹ�� */
typedef struct hiUNF_STREAM_BUF_S
{
    HI_U8   *pu8Data;        /**<Data pointer*/ /**<CNcomment: ����ָ�� */
    HI_U32  u32Size;         /**<Data size*/ /**<CNcomment: ���ݳ��� */
} HI_UNF_STREAM_BUF_S;

/**Defines the structure of the ES buffer.*/
/**CNcomment: ����ES��������ṹ�� */
typedef struct hiUNF_ES_BUF_S
{
    HI_U8  *pu8Buf;    /**<User-state virtual address of the buffer*/ /**<CNcomment: buffer���û�̬���ַ*/
    HI_U32 u32BufLen;  /**<Buffer length*/ /**<CNcomment: buffer�ĳ���*/
    HI_U32 u32PtsMs;   /**<Presentation time stamp (PTS) value corresponding to the start of the stream. The invalid value is 0xFFFFFFFF.*/
                       /**<CNcomment: ������ʼ����Ӧ��PTSֵ����ЧΪ0xffffffff*/
}HI_UNF_ES_BUF_S;

/** Defines of video frame crop parameter */
/** CNcomment:��Ƶ֡�ü����� */
typedef struct hiUNF_CROP_RECT_S
{
    HI_U32 u32LeftOffset;   /**<Left offset of crop*//**<CNcomment:�ü���ƫ��*/
    HI_U32 u32TopOffset;    /**<Top offset of crop*//**<CNcomment:�ü���ƫ��*/
    HI_U32 u32RightOffset;  /**<Right offset of crop*//**<CNcomment:�ü���ƫ��*/
    HI_U32 u32BottomOffset; /**<Bottom offset of crop*//**<CNcomment:�ü���ƫ��*/
}HI_UNF_CROP_RECT_S;

/** @} */  /** <!-- ==== Structure Definition End ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_COMMON_ H*/
