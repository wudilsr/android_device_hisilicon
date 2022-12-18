/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_mmz.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/15
  Description   : Common apis for hisilicon system.
  History       :
  1.Date        : 2010/01/25
    Author      : jianglei
    Modification: Created file

*******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
{
#endif
#endif

#include "mmz_struct.h"
#include "mmz.h"
#include "hi_mmz.h"
#include "sre_syscall.h"

int HI_MMZ_Malloc(HI_MMZ_BUF_S *pBuf)
{
    int l_return;

    /*parameters check*/
    if (NULL == pBuf)
    {
        uart_printf_func("%s:pBuf is NULL pointer!\n", __FUNCTION__);
        return -1;
    }

    if (pBuf->bufsize < 0x100000) //TODO: XXX
    {
        pBuf->bufsize = 0x100000;
    }

    if (strlen(pBuf->bufname) >= MAX_BUFFER_NAME_SIZE)
    {
        uart_printf_func("%s:the buffer name len is overflow!\n", __FUNCTION__);
        return -1;
    }

    l_return = __MMZ_MALLOC(pBuf);

    return l_return;
}

int HI_MMZ_Free(HI_MMZ_BUF_S *pBuf)
{
    int l_return;

    /*parameters check*/
    if (NULL == pBuf)
    {
        uart_printf_func("%s:pBuf is NULL pointer!\n", __FUNCTION__);
        return -1;
    }

    l_return = __MMZ_FREE(pBuf);

    return l_return;
}

void *HI_MMZ_New(unsigned int size , unsigned int alloc_type,
    char *mmz_name, char *mmb_name)
{
    HI_MMZ_BUF_S Buf;
    int ret;

    if( size ==0 || size > 0x40000000) return NULL;
    Buf.bufsize = size;

    Buf.alloc_type = alloc_type;

    ret = __MMZ_NEW(&Buf, mmz_name, mmb_name);

    if(ret == -1)
            return NULL;
    else
            return (void *)ret;
}

int HI_MMZ_Delete(unsigned int phys_addr)
{
    return __MMZ_DEL(phys_addr);
}

void *HI_MMZ_Map(unsigned int phys_addr, unsigned int cached)
{
    int ret;

    if(cached != 0 && cached != 1)  return NULL;

    ret = __MMZ_MAP(phys_addr, cached);

    return (void *)ret;
}

int HI_MMZ_Unmap(unsigned int phys_addr)
{
    return __MMZ_UNMAP(phys_addr);
}

int HI_MMZ_Flush(unsigned int phys_addr)
{
    return __MMZ_FLUSH(phys_addr);
}

void *HI_SEC_MMZ_New(unsigned long size , char *mmz_name, char *mmb_name)
{
	return HI_MMZ_New(size , 0, mmz_name, mmb_name);
}

int HI_SEC_MMZ_Delete(unsigned long phys_addr)
{
	return HI_MMZ_Delete(phys_addr);
}

void *HI_SEC_MMZ_Map(unsigned int phys_addr, unsigned int cached)
{
	return HI_MMZ_Map(phys_addr, cached);
}

int HI_SEC_MMZ_Unmap(unsigned int phys_addr)
{
	return HI_MMZ_Unmap(phys_addr);
}

int HI_SEC_MMZ_Flush(unsigned int phys_addr)
{
    return HI_MMZ_Flush(phys_addr);
}

void *HI_SEC_MMZ_NewAndMap(unsigned long size , unsigned int cached,
        char *mmz_name, char *mmb_name, char **phys_addr)
{
	char *paddr = NULL;
	char *vaddr = NULL;

	paddr = HI_MMZ_New(size , 0, mmz_name, mmb_name);
	if (!paddr)
		return NULL;

	vaddr = HI_SEC_MMZ_Map(paddr, cached);
	if (!vaddr) {
		HI_SEC_MMZ_Delete(paddr);
		return NULL;
	}

	*phys_addr = (char *)paddr;

	return vaddr;
}

int HI_SEC_MMZ_DelAndUnmap(unsigned long phys_addr)
{
	int ret = 0;
	
	ret = HI_SEC_MMZ_Unmap(phys_addr);
	if (!ret)
		return HI_MMZ_Delete(phys_addr);

	return ret;
}

int HI_TEE_IsSecureMem(unsigned long phys_addr, unsigned long size)
{
	int ret = 0;
	ret = __TEE_IsSecMem(phys_addr, size);
	return ret;
}

int HI_TEE_IsNonSecureMem(unsigned long phys_addr, unsigned long size)
{
	int ret = 0;
	ret = __TEE_IsNonSecMem(phys_addr, size);
	return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
