/******************************************************************************

Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : mpi_mem.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2006-07-18
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#ifndef __MPI_MEM_H__
#define __MPI_MEM_H__

#include "hi_type.h"
#include "hi_common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/******************************* MPI declaration *****************************/

/*malloc memory for mmz and map to user-state address, bufname and bufsize used to input,
	physic address and user-state used to output*/
/*CNcomment: ����mmz�ڴ棬��ӳ���û�̬��ַ,bufname��bufsize��Ϊ����, �����ַ���û�̬�����ַ��Ϊ��� */
HI_S32 HI_MPI_MMZ_Malloc(HI_MMZ_BUF_S *pstBuf);

/*free user-state map, release mmz memory, make sure that physic address, user-state address and lengh is right*/
/*CNcomment: ����û�̬��ַ��ӳ�䣬���ͷ�mmz�ڴ�,��֤����������ַ���û�̬�����ַ�ͳ�����ȷ*/
HI_S32 HI_MPI_MMZ_Free(HI_MMZ_BUF_S *pstBuf);

/*malloc mmz memory for appointed mmz name, return physic address*/
/*CNcomment: ָ��mmz����������mmz�ڴ棬���������ַ*/
HI_VOID *HI_MPI_MMZ_New(HI_U32 u32Size , HI_U32 u32Align, HI_CHAR *ps8MMZName, HI_CHAR *ps8MMBName);

/*CNcomment: �ͷ�mmz�ڴ� */
HI_S32 HI_MPI_MMZ_Delete(HI_U32 u32PhysAddr);

/*get physic address accordint to virtual address*/
/**CNcomment:  ���������ַ����ȡ��Ӧ�������ַ */
HI_S32 HI_MPI_MMZ_GetPhyAddr(HI_VOID *pRefAddr, HI_U32 *pu32PhyAddr, HI_U32 *pu32Size);

/*map physic address of mmz memory to user-state virtual address, can appoint whether cached*/
/**CNcomment:  ��mmz����������ַӳ����û�̬�����ַ������ָ���Ƿ�cached*/
HI_VOID *HI_MPI_MMZ_Map(HI_U32 u32PhysAddr, HI_U32 u32Cached);

/*unmap user-state address of mmz memory*/
/**CNcomment:  ���mmz�ڴ��û�̬��ַ��ӳ�� */
HI_S32 HI_MPI_MMZ_Unmap(HI_U32 u32PhysAddr);

/*for cached memory, flush cache to memory*/
/**CNcomment:  ����cached�ڴ棬ˢDcache���ڴ� */
HI_S32 HI_MPI_MMZ_Flush(HI_U32 u32PhysAddr);


#ifdef MMZ_V2_SUPPORT
HI_VOID *HI_MPI_MMZ_New_Share(HI_U32 size , HI_U32 align, HI_CHAR *mmz_name, HI_CHAR *mmb_name );

HI_VOID *HI_MPI_MMZ_New_Shm_Com(HI_U32 size , HI_U32 align, HI_CHAR *mmz_name, HI_CHAR *mmb_name );

HI_S32 HI_MPI_MMZ_Get_Shm_Com(HI_U32 *phyaddr, HI_U32 *size);
HI_S32 HI_MPI_MMZ_Force_Delete(HI_U32 phys_addr);

HI_S32 HI_MPI_MMZ_Flush_Dirty(HI_U32 phys_addr, HI_U32 virt_addr, HI_U32 size);

HI_S32 HI_MPI_MMZ_GetPhyAddr_S(HI_VOID *refaddr, HI_U32 *viraddr_s, HI_U32 *phyaddr_s, HI_U32 *size);

HI_S32 HI_MPI_MMZ_open(HI_VOID);

HI_S32 HI_MPI_MMZ_close(HI_VOID);
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MPI_MEM_H__ */
