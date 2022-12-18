#ifndef __MEDIA_MEM_INTF_H__
#define __MEDIA_MEM_INTF_H__

#include "sre_securecache.h"

//typedef void kcom_mmz_t;
typedef unsigned long mmb_addr_t;

#define MMB_ADDR_INVALID (~0)

#ifndef NULL
#define NULL (void *)0
#endif

#define SECURE_MEM 0

#define NON_SECURE_MEM 1

/**
\brief Add a memory pool.
CNcomment:\brief ����һ���ڴ�ء�CNend
\attention \n
N/A
\param[in]  name        The name of the memory pool to create.                         CNcomment:�ڴ������ CNend
\param[in]  phys_addr   The phisical address of the memory pool.                       CNcomment:�ڴ�ص�������ַ CNend
\param[in]  size        The size of the memory pool.                                   CNcomment:�ڴ�سߴ� CNend
\param[in]  alloc_type  Indicates whether the memory pool is secure or non-secure.     CNcomment:�ڴ�صİ�ȫ���ԡ�CNend
\retval ::non-zero      Success, the memory pool pointer.                              CNcomment:�ɹ�, �����ڴ��������ַ CNend
\retval ::NULL          Calling this API fails.                                        CNcomment:API����ʧ�� CNend
\see \n
N/A
*/
void *    new_zone(const char *name, unsigned long phys_start, unsigned long size, unsigned int alloc_type);

/**
\brief Delete a memory pool.
CNcomment:\brief ɾ��һ���ڴ�ء�CNend
\attention \n
N/A
\param[in]  zone        The size of the memory block to be allocated.             CNcomment:�ڴ��ߴ� CNend
\no retval
\see \n
N/A
*/
void        delete_zone(void *zone);

/**
\brief Allocate memory block.
CNcomment:\brief �����ڴ�顣CNend
\attention \n
N/A
\param[in]  name        The name of the memory block.                             CNcomment:�ڴ�����֡�CNend
\param[in]  size        The size of the memory block to be allocated.             CNcomment:�ڴ��ߴ� CNend
\param[in]  alloc_type  Indicates whether the memory is secure or non-secure.     CNcomment:�ڴ��İ�ȫ���ԡ�CNend
\param[in]  zone_name   The name of the memory pool to allocate from.             CNcomment:�ڴ������ CNend
\retval ::   Return the phisical address of the block if succeed, else return -1. CNcomment:�ɹ�ʱ�����ڴ��������ַ�����򷵻�-1 CNend
\see \n
N/A
*/
mmb_addr_t  new_mmb(const char *name, int size, unsigned int alloc_type, const char *zone_name);

/**
\brief Delete memory block.
CNcomment:\brief �ͷ��ڴ�顣CNend
\attention \n
N/A
\param[in]  addr        The address of the memory block to be deleted.             CNcomment:�ڴ����ʼ������ַ CNend
\see \n
N/A
*/
void        delete_mmb(mmb_addr_t addr);

/**
\brief Remap memory block��non-cacheable.
CNcomment:\brief ӳ���ڴ��, ����cache��CNend
\attention \n
N/A
\param[in]  addr        The address of the memory block to be remaped.             CNcomment:�ڴ����ʼ������ַ CNend
\retval ::Return the virtual address of the block.                                 CNcomment:�����ڴ�������ַ CNend
\see \n
N/A
*/
void *      remap_mmb(mmb_addr_t addr);

/**
\brief Remap memory block��cached.
CNcomment:\brief ӳ���ڴ��, ��cache��CNend
\attention \n
N/A
\param[in]  addr        The address of the memory block to be remaped.             CNcomment:�ڴ����ʼ������ַ CNend
\retval ::Return the virtual address of the block.                                 CNcomment:�����ڴ�������ַ CNend
\see \n
N/A
*/
void *      remap_mmb_cached(mmb_addr_t addr);

/**
\brief Unmap memory block.
CNcomment:\brief ��ӳ���ڴ�顣CNend
\attention \n
N/A
\param[in]  mapped_addr        The address of the memory block to be unmaped.     CNcomment:�ڴ���ַ CNend
\retval ::0        Success.                                                       CNcomment:�ɹ�, �����ڴ��������ַ CNend
\retval ::-1       Calling this API fails.                                        CNcomment:API����ʧ�� CNend
\see \n
N/A
*/
int         unmap_mmb(void *mapped_addr);

/**
\brief print all mmz struct link list.
CNcomment:\brief ��ӡmmz�����нṹ��Ա��CNend
\attention \n
N/A
*/
void        mmz_dump(void);

/**
\brief print all mmb struct link list.
CNcomment:\brief ��ӡmmb�����нṹ��Ա��CNend
\attention \n
N/A
*/
void        mmb_dump(void);

/**
\brief flush mmb L2 data cache
CNcomment:\brief ˢ��mmb��L2�����ݻ���CNend
\attention \n
N/A
*/
int flush_mmb(unsigned long addr);

#endif
