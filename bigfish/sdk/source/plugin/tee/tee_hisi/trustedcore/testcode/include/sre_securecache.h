

#ifndef __ARMV7_CACHE_H__
#define __ARMV7_CACHE_H__

#include "sre_base.h"

void SRE_ICacheEnable(void);
void SRE_ICacheDisable(void);
void SRE_DCacheEnable(void);
void SRE_DCacheDisable(void);
void enable_l1_cache(void);
void disable_l1_cache(void);
void enable_branch_prediction(void);

void flush_page_table_entry (UINT32 *l1_pte);
void flush_tlb_all(void);
void flush_tlb_region(UINT32* addr);
void flush_tlb_region_full(UINT32* addr);


void osDsb();
void osIsb();
void osDmb();

void SRE_DCacheFlushAll(void);
void SRE_DCacheInvAll(void);
void SRE_DCacheCleanAll(void);
void SRE_DCacheClean(UINT32* addr, UINT32 size, UINT32 wait);
void SRE_DCacheFlush(UINT32* addr, UINT32 size, UINT32 wait);
void SRE_DCacheInv(UINT32* addr, UINT32 size, UINT32 wait);

void SRE_ICacheInvAll(void);
void SRE_ICacheInv(UINT32* addr, UINT32 size, UINT32 wait);

void SRE_CacheFlushAll(void);

void SRE_BranchPredictInv(void);

void SRE_CacheCodeUpdate(UINT32* addr, UINT32 size);
void l2x0_flush_all(void);
#endif
