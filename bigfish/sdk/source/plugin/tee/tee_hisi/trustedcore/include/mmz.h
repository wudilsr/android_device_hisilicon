

#ifndef __MMZ_H__
#define __MMZ_H__

#include "mmz_struct.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */
/**
\brief Memory malloc��the memory is already mapped.
CNcomment:\brief �ڴ涯̬���䡣CNend
\attention \n
N/A
\param[inout]  pBuf    Input bufname and bufsize, allocation type. Output the phisical address,
kernel virtual address, user virtual address.                       CNcomment:���������ڴ�����ƣ��ߴ��С����ȫ��־����������ڴ�������ַ�������ַ CNend
\retval ::0   Success                                               CNcomment:�ɹ� CNend
\retval ::-1  Calling this API fails.                               CNcomment:API����ʧ�� CNend
\see \n
N/A
*/
int HI_MMZ_Malloc(HI_MMZ_BUF_S *pBuf);

/**
\brief Free the memory block.
CNcomment:\brief �ͷŷ�����ڴ�顣CNend
\attention \n
N/A
\param[in]  pBuf    The struct indicating the memory block to be freed.             CNcomment:ָʾҪ���ͷŵ��ڴ�� CNend
\retval ::0   Success                                                               CNcomment:�ɹ� CNend
\retval ::-1  Calling this API fails.                                               CNcomment:API����ʧ�� CNend
\see \n
N/A
*/
int HI_MMZ_Free(HI_MMZ_BUF_S *pBuf);

/**
\brief Allocate memory block.
CNcomment:\brief �����ڴ�顣CNend
\attention \n
N/A
\param[in]  size        The size of the memory block to be allocated.             CNcomment:�ڴ��ߴ� CNend
\param[in]  alloc_type  Indicates whether the memory is secure or non-secure.     CNcomment:�ڴ��İ�ȫ���ԡ�CNend
\param[in]  mmz_name    The name of the memory pool to allocate from.             CNcomment:�ڴ������ CNend
\param[in]  mmb_name    The name of the memory block.                             CNcomment:�ڴ�����֡�CNend
\retval ::non-zero   Success, return the phisical address of the block.           CNcomment:�ɹ�, �����ڴ�������ַ CNend
\retval ::NULL       Calling this API fails.                                      CNcomment:API����ʧ�� CNend
\see \n
N/A
*/
void *HI_MMZ_New(unsigned int size , unsigned int alloc_type, char *mmz_name, char *mmb_name);

/**
\brief Relieve the memory block.
CNcomment:\brief �ͷ��ڴ�顣CNend
\attention \n
N/A
\param[in]  phys_addr    The phisical address of the memory block.  CNcomment:���ͷ��ڴ��������ַ CNend
\retval ::0   Success                                               CNcomment:�ɹ� CNend
\see \n
N/A
*/
int HI_MMZ_Delete(unsigned int phys_addr);

/**
\brief Map the memory block.
CNcomment:\brief ӳ���ڴ�顣CNend
\attention \n
N/A
\param[in]  phys_addr    The phisical address of the memory block.                       CNcomment:�ڴ��������ַ CNend
\param[in]  cached       Indicating whether the memory is cached or non-cacheable..      CNcomment:ָ��ӳ���Ƿ��cache��CNend
\retval ::The virtual address   Success                                                  CNcomment:����ӳ��������ַ CNend
\see \n
N/A
*/
void *HI_MMZ_Map(unsigned int phys_addr, unsigned int cached);

/**
\brief Unmap the memory block.
CNcomment:\brief ��ӳ���ڴ档CNend
\attention \n
N/A
\param[in]  phys_addr    The phisical address of the memory block.           CNcomment:�ڴ��������ַ CNend
\retval ::0   Success                                                        CNcomment:�ɹ� CNend
\retval ::-1  Calling this API fails.                                        CNcomment:API����ʧ�� CNend
\see \n
N/A
*/
int HI_MMZ_Unmap(unsigned int phys_addr);

/**
\brief Cache flush.
CNcomment:\brief ˢcache�ӿڡ�CNend
\attention \n
N/A
\param[in]  phys_addr    The phisical address of the memory block.           CNcomment:�ڴ��������ַ CNend
\retval ::0   Success                                                        CNcomment:�ɹ� CNend
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
