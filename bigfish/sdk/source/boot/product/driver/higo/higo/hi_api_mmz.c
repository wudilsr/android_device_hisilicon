#include "hi_type.h"
#include "exports.h"
#include "hifb_debug.h"
#include "jpg_common.h"
#ifndef WIN32


//static HI_S32 g_s32fd = 0;

#define CHECK_INIT() 	do{ if( g_s32fd <=0) g_s32fd =open("/dev/himedia/mmz_userdev", O_RDWR); \
												if( g_s32fd <=0) return HI_FAILURE; \
										  }while(0); 

#define CHECK_INIT2() do{ if( g_s32fd <=0) g_s32fd =open("/dev/himedia/mmz_userdev", O_RDWR); \
												if( g_s32fd <=0) return NULL; \
										  }while(0); 
#define JPG_MEM_BASE_ADDR   0xc3000005
#define JPG_MEM_SIZE        (8*1024*1024)
HI_U32  g_JpgMemOffset = 0;

//extern HI_U32 g_JpgDecAddr;
static HI_U32 g_JpgDecAddr = 0;
static HI_U32 g_JpgDecLen = 0;

HI_S32 HI_MMB_Init(HI_U32 uStartAddr , HI_U32 uLen)
{
    g_JpgDecAddr = uStartAddr;
    g_JpgDecLen = uLen;
    return HI_SUCCESS;
}

HI_S32 HI_MMB_DeInit( HI_VOID)
{
#ifdef HI_MINIBOOT_SUPPORT
    mmu_cache_enable();
#else
    dcache_enable(0);
#endif
    VCOS_memset((HI_VOID*)g_JpgDecAddr, 0, g_JpgDecLen);
#ifdef HI_MINIBOOT_SUPPORT
    mmu_cache_disable();
#else
    dcache_disable();
#endif
    g_JpgMemOffset = 0;
    return HI_SUCCESS;
}

HI_VOID *HI_MMB_New(HI_U32 size , HI_U32 align, HI_U8 *mmz_name, HI_U8 *mmb_name )
{


    HI_U32  StartPhyAddr;
	StartPhyAddr = g_JpgDecAddr + g_JpgMemOffset;
    if( align > 0 )
    {
	    StartPhyAddr = (StartPhyAddr + align - 1);
		StartPhyAddr = (StartPhyAddr / align) * align;
	}
    if(StartPhyAddr + size  >= g_JpgDecAddr + g_JpgDecLen)
    {
        Debug("HI_MMB_New failed. TotalLen 0x%x offset 0x%x acquiresize 0x%x", g_JpgDecLen,g_JpgMemOffset,size);
        return HI_NULL;
    }
	g_JpgMemOffset = StartPhyAddr + size - g_JpgDecAddr;
    return (HI_VOID*)(StartPhyAddr);


}

HI_VOID *HI_MMB_Map(HI_U32 phys_addr, HI_U32 cached)
{

	return (HI_VOID*)phys_addr;

}

HI_S32 HI_MMB_Unmap(HI_U32 phys_addr)
{

	return HI_SUCCESS;

}
 
HI_S32 HI_MMB_Delete(HI_U32 phys_addr)
{

	return HI_SUCCESS;


}

HI_S32 HI_MMB_Flush(HI_VOID)
{

	return HI_SUCCESS;

}

#endif

