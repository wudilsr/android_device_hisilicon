/******************************************************************************
Copyright (C), 2009-2019, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : mmz_struct.h
Version       : Initial Draft
Author        : Hisilicon
Created       : 2009/12/16
Last Modified :
Description   : Defines the common data type of the system.
                CNcomment: ϵͳ���õ��������Ͷ���
Function List :
History       :
******************************************************************************/
/**
 * \file
 * \brief Describes the information about basic data types. CNcomment: �ṩ�����������͵������Ϣ
 */
#ifndef __MMZ_STRUCT_H__
#define __MMZ_STRUCT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_1_2 */
/** @{ */  /** <!-- ��Common data structure. CNcomment: ͨ�����ݽṹ�� */


/**Maximum bytes of a buffer name*/
/**CNcomment:  buffer����������ֽ��� */
#define MAX_BUFFER_NAME_SIZE 16

/**alloc_type*/
/**CNcomment:  alloc_type */
#define SECURE_MEM 0
#define NON_SECURE_MEM 1

/**Structure of an MMZ buffer*/
/**CNcomment:  MMZ buffer��Ϣ�ṹ */
typedef struct hiMMZ_BUF_S
{
    char bufname[MAX_BUFFER_NAME_SIZE];  /**<Strings of an MMZ buffer name*/ /**<CNcomment:  MMZ buffer�����ַ��� */
    unsigned int  phyaddr;                /**<Physical address of an MMZ buffer*/ /**<CNcomment:  MMZ buffer�����ַ */
    unsigned int alloc_type;        /**<Indicate to alloc mem from the non-secure or secure memory*/ /**<CNcomment:  ָʾ�Ӱ�ȫ�ڴ滹�Ƿǰ�ȫ�ڴ��з��� */
    char  *kernel_viraddr;         /**<Kernel-state virtual address of an MMZ buffer*/ /**<CNcomment:  MMZ buffer�ں�̬�����ַ */
    char  *user_viraddr;           /**<User-state virtual address of an MMZ buffer*/ /**<CNcomment:  MMZ buffer�û�̬�����ַ */
    unsigned int  bufsize;                /**<Size of an MMZ buffer*/ /**<CNcomment:  MMZ buffer��С */
    unsigned int  overflow_threshold;     /**<Overflow threshold of an MMZ buffer, in percentage. For example, the value 100 indicates 100%.*/ /**<CNcomment:  MMZ buffer����ˮ�ߣ����ٷֱ����ã�����: 100 indicates 100%.*/
    unsigned int  underflow_threshold;    /**<Underflow threshold of an MMZ buffer, in percentage. For example, the value 0 indicates 0%.*/ /**<CNcomment:  MMZ buffer����ˮ�ߣ����ٷֱ����ã�����: 0 indicates 0%.*/
}HI_MMZ_BUF_S;

/*End of CMPI */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __MMZ_STRUCT_H__ */

