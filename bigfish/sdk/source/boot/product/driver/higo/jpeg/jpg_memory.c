#include "hi_type.h"
#include "hi_debug.h"
#include "higo_common.h"
#include "hi_api_mmz.h"
#include "jpg_common.h"

HI_VOID JPGFMW_Free(JPG_MEM_S* pstMem)
{
	HI_U32  PhysAddr = pstMem->PhysAddr;

	if( pstMem->pVirtAddr != NULL && pstMem->Total != 0 )
	{

	 	HI_MMB_Unmap(PhysAddr);
		HI_MMB_Delete(PhysAddr);
		VCOS_memset(pstMem, 0, sizeof(JPG_MEM_S));
	}
}
#if 1
HI_VOID*  JPGFMW_Alloc(JPG_MEM_S* pstMem, HI_U32 Size)
{
 	HI_U32  PhysAddr = 0;
	HI_VOID* pVirtAddr = NULL;

	if( pstMem->pVirtAddr != NULL && pstMem->Total != 0 )
      {
           if( pstMem->Total >= Size )
           {
                pstMem->Offset = 0;
                return pstMem->pVirtAddr;
           }
           else
           {
               JPGFMW_Free( pstMem );
           }
      }

	PhysAddr = (HI_U32)HI_MMB_New(Size, 64, (HI_U8*)MMB_TAG, (HI_U8*)"JPEG_DECODE_BOOT");
	if(0 == PhysAddr)
	{
        HIGO_ERROR(0);
		return HI_NULL;
	}

	pVirtAddr = (HI_VOID*)HI_MMB_Map(PhysAddr, 1);
	if(HI_NULL == pVirtAddr)
    {
        HIGO_ERROR(0);
		HI_MMB_Delete(PhysAddr);
		return HI_NULL;
	}

    pstMem->pVirtAddr = pVirtAddr;
    pstMem->PhysAddr = PhysAddr;
    pstMem->Total = Size;
    pstMem->Offset = 0;
   
#ifdef HI_MINIBOOT_SUPPORT
    mmu_cache_enable();
#else
    dcache_enable(0);
#endif 
    VCOS_memset(pstMem->pVirtAddr, 0, Size);
#ifdef HI_MINIBOOT_SUPPORT
    mmu_cache_disable();
#else
    dcache_disable();
#endif    
    return pVirtAddr;
}

HI_VOID JPGFMW_MemReset(JPG_MEM_S* pstMem, HI_U32  RsvSize)
{
	pstMem->Offset = RsvSize;
#ifdef HI_MINIBOOT_SUPPORT
    mmu_cache_enable();
#else
    dcache_enable(0);
#endif
	VCOS_memset((HI_U8*)pstMem->pVirtAddr + pstMem->Offset,
		                0, pstMem->Total - pstMem->Offset);
#ifdef HI_MINIBOOT_SUPPORT
    mmu_cache_disable();
#else
    dcache_disable();
#endif
}

HI_VOID* JPGFMW_MemGet(JPG_MEM_S* pstMem, HI_U32  Size)
{
  	HI_VOID* pVirtAddr = NULL;
      HI_U32   Offset;

      Size = (Size + 3) & (~3);  

      Offset = pstMem->Offset + Size;
      if(Offset > pstMem->Total)
      {
           pVirtAddr = NULL;
      }
      else
      {
          pVirtAddr = (HI_U8*)pstMem->pVirtAddr + pstMem->Offset;
	    pstMem->Offset = Offset;

      }

	return pVirtAddr;
}
#endif
