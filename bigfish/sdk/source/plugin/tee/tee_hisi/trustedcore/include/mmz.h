

#ifndef __MMZ_H__
#define __MMZ_H__

#include "mmz_struct.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */
/**
\brief Memory malloc，the memory is already mapped.
CNcomment:\brief 内存动态分配。CNend
\attention \n
N/A
\param[inout]  pBuf    Input bufname and bufsize, allocation type. Output the phisical address,
kernel virtual address, user virtual address.                       CNcomment:输入分配的内存块名称，尺寸大小，安全标志，输出分配内存的物理地址和虚拟地址 CNend
\retval ::0   Success                                               CNcomment:成功 CNend
\retval ::-1  Calling this API fails.                               CNcomment:API调用失败 CNend
\see \n
N/A
*/
int HI_MMZ_Malloc(HI_MMZ_BUF_S *pBuf);

/**
\brief Free the memory block.
CNcomment:\brief 释放分配的内存块。CNend
\attention \n
N/A
\param[in]  pBuf    The struct indicating the memory block to be freed.             CNcomment:指示要被释放的内存块 CNend
\retval ::0   Success                                                               CNcomment:成功 CNend
\retval ::-1  Calling this API fails.                                               CNcomment:API调用失败 CNend
\see \n
N/A
*/
int HI_MMZ_Free(HI_MMZ_BUF_S *pBuf);

/**
\brief Allocate memory block.
CNcomment:\brief 分配内存块。CNend
\attention \n
N/A
\param[in]  size        The size of the memory block to be allocated.             CNcomment:内存块尺寸 CNend
\param[in]  alloc_type  Indicates whether the memory is secure or non-secure.     CNcomment:内存块的安全属性。CNend
\param[in]  mmz_name    The name of the memory pool to allocate from.             CNcomment:内存池名字 CNend
\param[in]  mmb_name    The name of the memory block.                             CNcomment:内存块名字。CNend
\retval ::non-zero   Success, return the phisical address of the block.           CNcomment:成功, 返回内存块物理地址 CNend
\retval ::NULL       Calling this API fails.                                      CNcomment:API调用失败 CNend
\see \n
N/A
*/
void *HI_MMZ_New(unsigned int size , unsigned int alloc_type, char *mmz_name, char *mmb_name);

/**
\brief Relieve the memory block.
CNcomment:\brief 释放内存块。CNend
\attention \n
N/A
\param[in]  phys_addr    The phisical address of the memory block.  CNcomment:待释放内存块的物理地址 CNend
\retval ::0   Success                                               CNcomment:成功 CNend
\see \n
N/A
*/
int HI_MMZ_Delete(unsigned int phys_addr);

/**
\brief Map the memory block.
CNcomment:\brief 映射内存块。CNend
\attention \n
N/A
\param[in]  phys_addr    The phisical address of the memory block.                       CNcomment:内存块的物理地址 CNend
\param[in]  cached       Indicating whether the memory is cached or non-cacheable..      CNcomment:指定映射是否带cache。CNend
\retval ::The virtual address   Success                                                  CNcomment:返回映射的虚拟地址 CNend
\see \n
N/A
*/
void *HI_MMZ_Map(unsigned int phys_addr, unsigned int cached);

/**
\brief Unmap the memory block.
CNcomment:\brief 解映射内存。CNend
\attention \n
N/A
\param[in]  phys_addr    The phisical address of the memory block.           CNcomment:内存块的物理地址 CNend
\retval ::0   Success                                                        CNcomment:成功 CNend
\retval ::-1  Calling this API fails.                                        CNcomment:API调用失败 CNend
\see \n
N/A
*/
int HI_MMZ_Unmap(unsigned int phys_addr);

/**
\brief Cache flush.
CNcomment:\brief 刷cache接口。CNend
\attention \n
N/A
\param[in]  phys_addr    The phisical address of the memory block.           CNcomment:内存块的物理地址 CNend
\retval ::0   Success                                                        CNcomment:成功 CNend
\see \n
N/A
*/
int HI_MMZ_Flush(unsigned int phys_addr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __MMZ_H__ */
