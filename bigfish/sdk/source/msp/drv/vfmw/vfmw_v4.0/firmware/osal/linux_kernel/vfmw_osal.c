/*-----------------------------------------------------------------------*/
/*!!Warning: Huawei key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCDadN5jJKSuVyxmmaCmKFU6eJEbB2fyHF9weu4/jer/hxLHb+S1e
E0zVg4C3NiZh4b+GnwjAHj8JYHgZh/mRmQno22+dG7COxUFa9FUMSEmwiqyHLY6kItjWlyOj
ANaheCHM0Y1Qgm/LYRy5PVoEItwt79vLAEouINIId+EKvdX0KfQUcsMtJmSFBmcakRShnjPW
s7ar/TGCM1IcCmVkodwDFdSHxGNu4UFGOJKiQQgiS/4+jM26YlxJ2s94ELHRIA==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/










 
/******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
    文 件 名   : vfmw_osal.c
    版 本 号   : 初稿
    作    者   : 
    生成日期   : 
    最近修改   :
    功能描述   : 为vfmw定制的操作系统抽象模块
                 

    修改历史   :
    1.日    期 : 2009-05-12
    作    者   : 
    修改内容   : 

******************************************************************************/

#include "vfmw_osal.h"
#include "public.h"


OSAL_SEMA g_stSem;

/************************************************************************/
/* OSAL_GetTimeInMs():  获取系统时间                                    */
/************************************************************************/
UINT32 OSAL_GetTimeInMs(VOID)
{
	UINT64   SysTime;
    
    SysTime = sched_clock();
    do_div(SysTime, 1000000);
    return (UINT32)SysTime;
}

UINT32 OSAL_GetTimeInUs(VOID)
{
	UINT32 CurrUs = 0;
	
    struct timeval CurrentTime;      
    do_gettimeofday(&CurrentTime);
    CurrUs = (UINT32)(CurrentTime.tv_sec*1000000 + CurrentTime.tv_usec);
	
	return CurrUs;
}

/*  创建任务                                                            */
/************************************************************************/
SINT32 OSAL_CreateTask( OSAL_TASK *pTask, SINT8 TaskName[], VOID *pTaskFunction )
{
    *pTask = kthread_create(pTaskFunction, (VOID *)NULL, TaskName);
    if( NULL == (*pTask) ) 
    {
        dprint(PRN_FATAL, "can not create thread!\n");
        return( VF_ERR_SYS );
    }
    wake_up_process(*pTask);	
    return OSAL_OK;
}

/************************************************************************/
/* 激活任务                                                             */
/************************************************************************/
SINT32 OSAL_WakeupTask( OSAL_TASK *pTask )
{
    return OSAL_OK;
}

/************************************************************************/
/* 销毁任务                                                             */
/************************************************************************/
SINT32 OSAL_DeleteTask(OSAL_TASK *pTask)
{
    return OSAL_OK;
}

/************************************************************************/
/* 初始化事件                                                           */
/************************************************************************/
SINT32 OSAL_InitEvent( OSAL_EVENT *pEvent, SINT32 InitVal )
{
	pEvent->flag = InitVal;
	init_waitqueue_head( &(pEvent->queue_head) );	
	return OSAL_OK;
}

/************************************************************************/
/* 发出事件                                                             */
/************************************************************************/
SINT32 OSAL_GiveEvent( OSAL_EVENT *pEvent )
{
	pEvent->flag = 1;
	wake_up_interruptible ( &(pEvent->queue_head) );
	
	return OSAL_ERR;
}

/************************************************************************/
/* 等待事件                                                             */
/* 事件发生返回OSAL_OK，超时返回OSAL_ERR 若condition不满足就阻塞等待    */
/************************************************************************/
SINT32 OSAL_WaitEvent( OSAL_EVENT *pEvent, SINT32 msWaitTime )
{
	SINT32 l_ret;

    l_ret = wait_event_interruptible_timeout( pEvent->queue_head, (pEvent->flag != 0), msecs_to_jiffies(msWaitTime) );

    pEvent->flag = 0;//(pEvent->flag>0)? (pEvent->flag-1): 0;

	return (l_ret==0)? OSAL_OK: OSAL_ERR;
}
UINT8 *KernelRegisterMap(UINT32 PhyAddr)
{
	return (UINT8*)ioremap_nocache( PhyAddr,0x10000 );
}

VOID KernelRegisterUnMap(UINT8 *VirAddr)
{
    iounmap(VirAddr);
	return;
}

struct file *klib_fopen(const char *filename, int flags, int mode)
{
    struct file *filp = filp_open(filename, flags, mode);
    return (IS_ERR(filp)) ? NULL : filp;
}

void klib_fclose(struct file *filp)
{
    if (filp)
        filp_close(filp, NULL);
}

int klib_fread(char *buf, unsigned int len, struct file *filp)
{
    int readlen;
    mm_segment_t oldfs;

    if (filp == NULL)
            return -ENOENT;
    if (filp->f_op->read == NULL)
            return -ENOSYS;
    if (((filp->f_flags & O_ACCMODE) & (O_RDONLY | O_RDWR)) == 0)
            return -EACCES;
    oldfs = get_fs();
    set_fs(KERNEL_DS);
    readlen = filp->f_op->read(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);

    return readlen;
}

int klib_fwrite(char *buf, int len, struct file *filp)
{
    int writelen;
    mm_segment_t oldfs;

    if (filp == NULL)
            return -ENOENT;
    if (filp->f_op->write == NULL)
            return -ENOSYS;
    if (((filp->f_flags & O_ACCMODE) & (O_WRONLY | O_RDWR)) == 0)
            return -EACCES;
    oldfs = get_fs();
    set_fs(KERNEL_DS);
    writelen = filp->f_op->write(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);

    return writelen;
}

VOID OSAL_SEMA_INTIT(VOID)
{
    sema_init(&g_stSem,1);
}

SINT32 OSAL_DOWN_INTERRUPTIBLE(VOID)
{
    HI_S32 s32Ret;
	s32Ret = down_interruptible(&g_stSem);
	return s32Ret;
}
VOID OSAL_UP(VOID)
{
	up(&g_stSem);
}

/************************************************************************/
/* 锁初始化                                                             */
/************************************************************************/
inline VOID OSAL_SpinLockIRQInit(OSAL_IRQ_SPIN_LOCK *pIntrMutex)
{
    spin_lock_init(&pIntrMutex->irq_lock);  
    pIntrMutex->isInit = 1;

    return;
}


/************************************************************************/
/* 中断互斥加锁(关中断且加锁)                                           */
/************************************************************************/
inline SINT32 OSAL_SpinLockIRQ(OSAL_IRQ_SPIN_LOCK *pIntrMutex)
{
    if(pIntrMutex->isInit == 0)
    {
        spin_lock_init(&pIntrMutex->irq_lock);  
        pIntrMutex->isInit = 1;
    }
    spin_lock_irqsave(&pIntrMutex->irq_lock, pIntrMutex->irq_lockflags);

    return OSAL_OK;
}

/************************************************************************/
/* 中断互斥解锁(开中断且去锁)                                           */
/************************************************************************/
inline SINT32 OSAL_SpinUnLockIRQ(OSAL_IRQ_SPIN_LOCK *pIntrMutex)
{
    spin_unlock_irqrestore(&pIntrMutex->irq_lock, pIntrMutex->irq_lockflags);

    return OSAL_OK;
}


/******************************************************************************
                       这里开始是产品差异化代码
******************************************************************************/

#ifdef VFMW_BVT_SUPPORT

extern MEM_DESC_S    (*mem_malloc)(UINT8 * MemName, UINT32 len, UINT32 align);
extern VOID          (*mem_free)( MEM_DESC_S mem);

/************************************************************************/
/* 申请虚拟内存（可能非物理连续）                                       */
/************************************************************************/
VOID *OSAL_AllocVirMem(SINT32 Size)
{
	return vmalloc(Size);
}

/************************************************************************/
/* 释放虚拟内存（可能非物理连续）                                       */
/************************************************************************/
VOID OSAL_FreeVirMem(VOID *p)
{
	if(p)vfree(p);
}

SINT32 KernelMemMalloc(UINT8 * MemName, UINT32 len, UINT32 align, UINT32 IsCached, MEM_DESC_S *pMemDesc)
{
    MEM_DESC_S AllocMem;
	if (mem_malloc == NULL)
	{
	    return -1;
	}
    AllocMem = mem_malloc( MemName, len, align);
    if( NULL == AllocMem.VirAddr )
    {
        memset(pMemDesc, 0, sizeof(MEM_DESC_S));
    	return -1;
    }
    else
    {
        pMemDesc->PhyAddr = AllocMem.PhyAddr;
        pMemDesc->VirAddr = AllocMem.VirAddr;
        pMemDesc->Length  = AllocMem.Length;
    	return 0;
    }
}

SINT32 KernelMemFree(MEM_DESC_S *pMemDesc)
{
    MEM_DESC_S AllocMem;

    memset(&AllocMem, 0, sizeof(MEM_DESC_S));
	if (mem_free == NULL)
	{
	    return -1;
	}	
	AllocMem.Length = pMemDesc->Length;
	AllocMem.VirAddr = pMemDesc->VirAddr;
	AllocMem.PhyAddr = pMemDesc->PhyAddr;
	mem_free(AllocMem);
	
    return 0;	
}		

UINT8 *KernelMmap(UINT32 phyaddr, UINT32 len)
{
    /*由于BVT相关内存操作由外部进行，且不会进入软解码分支，因此直接返回NULL即可*/
    return NULL;
}

UINT8 *KernelMmapCache(UINT32 phyaddr, UINT32 len)
{
    /*由于BVT相关内存操作由外部进行，且不会进入软解码分支，因此直接返回NULL即可*/
    return NULL;
}

VOID KernelMunmap(UINT8 *p )
{
    /*由于BVT相关内存操作由外部进行，且不会进入软解码分支，因此什么都不做即可*/
    return;
}

VOID KernelFlushCache(VOID *ptr, UINT32 phy_addr, UINT32 len)
{
    /*由于BVT相关内存操作由外部进行，且不会进入软解码分支，因此什么都不做即可*/
    return;
}

void klib_flush_cache(void *ptr, unsigned int phy_addr, unsigned int len)
{
    /*由于BVT相关内存操作由外部进行，且不会进入软解码分支，因此什么都不做即可*/
    return;
}

#else

/************************************************************************/
/* 申请虚拟内存（可能非物理连续）                                       */
/************************************************************************/
VOID *OSAL_AllocVirMem(SINT32 Size)
{
	return HI_VMALLOC(HI_ID_VFMW, Size);
}

/************************************************************************/
/* 释放虚拟内存（可能非物理连续）                                       */
/************************************************************************/
VOID OSAL_FreeVirMem(VOID *p)
{
    if(p)
    {
        HI_VFREE(HI_ID_VFMW, p);
    }
}

SINT32 KernelMemMalloc(UINT8 * MemName, UINT32 len, UINT32 align, UINT32 IsCached, MEM_DESC_S *pMemDesc)
{
    MMZ_BUFFER_S stMmzBuffer;
    memset(&stMmzBuffer, 0, sizeof(MMZ_BUFFER_S));

    if(HI_SUCCESS != HI_DRV_MMZ_Alloc(MemName, NULL, len, align, &stMmzBuffer))
    {
        memset(pMemDesc, 0, sizeof(MEM_DESC_S));
        return -1;
    }
    
    if( 0 != stMmzBuffer.u32StartPhyAddr )
    {
        if(IsCached == 1)
        {
            if(HI_SUCCESS != HI_DRV_MMZ_MapCache(&stMmzBuffer))
            {
                memset(pMemDesc, 0, sizeof(MEM_DESC_S));
                return -1;
            }
        }
        else
        {
            if(HI_SUCCESS != HI_DRV_MMZ_Map(&stMmzBuffer))
            {
                memset(pMemDesc, 0, sizeof(MEM_DESC_S));
                return -1;
            }
        }
    }
    else
    {
    	memset(pMemDesc, 0, sizeof(MEM_DESC_S));
		return -1;
    }

    pMemDesc->PhyAddr = (SINT32)stMmzBuffer.u32StartPhyAddr;
    pMemDesc->VirAddr = (UINT8*)stMmzBuffer.u32StartVirAddr;
    pMemDesc->Length  = (SINT32)stMmzBuffer.u32Size;

    
    return 0;
}

SINT32 KernelMemFree(MEM_DESC_S *pMemDesc)
{
    MMZ_BUFFER_S stMBuf;
    memset(&stMBuf, 0, sizeof(MMZ_BUFFER_S));

    stMBuf.u32StartPhyAddr = (UINT32)pMemDesc->PhyAddr;
    stMBuf.u32StartVirAddr = (UINT32)pMemDesc->VirAddr;
    stMBuf.u32Size         = (UINT32)pMemDesc->Length;

    HI_DRV_MMZ_Unmap(&stMBuf);
    HI_DRV_MMZ_Release(&stMBuf);

    return 0;	
}		

UINT8 *KernelMmap(UINT32 phyaddr, UINT32 len)
{
    SINT32 s32Ret = 0;
    MMZ_BUFFER_S stMemBuf;
    memset(&stMemBuf, 0, sizeof(MMZ_BUFFER_S));
    stMemBuf.u32StartPhyAddr = phyaddr;

    s32Ret = HI_DRV_MMZ_Map(&stMemBuf);
	if(s32Ret !=HI_SUCCESS)
	{
	    dprint(PRN_FATAL, "vfmw_osal.c, line %d: HI_DRV_MMZ_Map ERR\n", __LINE__);
	}

    return (UINT8 *)(stMemBuf.u32StartVirAddr);

}

UINT8 *KernelMmapCache(UINT32 phyaddr, UINT32 len)
{
    MMZ_BUFFER_S stMemBuf;
    memset(&stMemBuf, 0, sizeof(MMZ_BUFFER_S));
    stMemBuf.u32StartPhyAddr = phyaddr;

    (VOID)HI_DRV_MMZ_MapCache(&stMemBuf);

    return (UINT8 *)(stMemBuf.u32StartVirAddr);
}

VOID KernelMunmap(UINT8 *p )
{
    MMZ_BUFFER_S stMemBuf;
    memset(&stMemBuf, 0, sizeof(MMZ_BUFFER_S));
    stMemBuf.u32StartVirAddr = (UINT32)(p);

    HI_DRV_MMZ_Unmap(&stMemBuf);
}

VOID KernelFlushCache(VOID *ptr, UINT32 phy_addr, UINT32 len)
{
    unsigned long flags;
    DEFINE_SPINLOCK(cache_lock);
    
    spin_lock_irqsave(&cache_lock, flags);
    __cpuc_flush_dcache_area((void *)ptr, (size_t)len); // flush l1cache
    outer_flush_range(phy_addr, phy_addr+len); // flush l2cache
    
    spin_unlock_irqrestore(&cache_lock, flags);
    return;
}

void klib_flush_cache(void *ptr, unsigned int phy_addr, unsigned int len)
{
    unsigned long flags;
    DEFINE_SPINLOCK(cache_lock);
    
    spin_lock_irqsave(&cache_lock, flags);

    __cpuc_flush_dcache_area((void *)ptr, (size_t)len); // flush l1cache
    outer_flush_range(phy_addr, phy_addr+len); // flush l2cache

    spin_unlock_irqrestore(&cache_lock, flags);
    return;
}

#endif

