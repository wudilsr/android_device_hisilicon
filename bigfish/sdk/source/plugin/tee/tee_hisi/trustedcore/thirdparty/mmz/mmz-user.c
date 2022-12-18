/* userdev.c
*
* Copyright (c) 2006 Hisilicon Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*
*/

#include "mmz_struct.h"
#include "media-mem.h"
#include "hi_mmz.h"
#include "sre_debug.h"

#include "sre_securemmu.h"

int MMZ_MALLOC(HI_MMZ_BUF_S *pBuf)
{
    mmb_addr_t mmb;
    void *va;

    mmb = new_mmb(pBuf->bufname, pBuf->bufsize, pBuf->alloc_type, NULL);
    if (MMB_ADDR_INVALID == mmb) {
        return -1;
    }

    va = remap_mmb_uk(mmb);
    if(NULL == va) {
        delete_mmb(mmb);
        return -1;
    }

    pBuf->phyaddr = mmb;
    pBuf->user_viraddr = (char *)va;
    pBuf->overflow_threshold = 100;
    pBuf->underflow_threshold = 0;

    return 0;
}

int MMZ_FREE(HI_MMZ_BUF_S *pBuf)
{
    int ret = -1;
    mmb_addr_t mmb;
    void *va;

    mmb = pBuf->phyaddr;
    va = pBuf->user_viraddr;

    ret = unmap_mmb(va);
    delete_mmb(mmb);

    return ret;
}

int MMZ_NEW(HI_MMZ_BUF_S *pBuf, char *mmz_name, char *mmb_name)
{
    mmb_addr_t mmb;

    mmb = new_mmb(mmb_name, pBuf->bufsize, pBuf->alloc_type, mmz_name);

    return mmb;
}

int MMZ_DEL(unsigned long addr)
{
    delete_mmb(addr);
    return 0;
}

int MMZ_MAP(unsigned long addr, unsigned long cached)
{
    if(cached) {
        return remap_mmb_uk_cached(addr);
    } else {
        return remap_mmb_uk(addr);
    }
}

int MMZ_UNMAP(unsigned long addr)
{
    void *mmb;
    int ret = -1;

    mmb = hil_mmb_getby_phys(addr);
    if (mmb) {
        ret = unmap_mmb(hil_mmb_kvirt(mmb));
    }

    delete_mmb(addr);

    return ret;
}

int MMZ_FLUSH(unsigned long addr)
{
    flush_mmb(addr);

    return 0;
}

int mem_copy(unsigned long va_src, unsigned long va_dest, int size)
{
    memcpy(va_dest, va_src, size);
    return 0;
}

int TEE_IsSecMem(unsigned long phys_addr, unsigned long size)
{
    return hil_tee_is_sec_mem(phys_addr, size);
}

int TEE_IsNonSecMem(unsigned long phys_addr, unsigned long size)
{
    return hil_tee_is_nonsec_mem(phys_addr, size);
}