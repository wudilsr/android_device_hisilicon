/* kcom.c
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

#include "list.h"
#include "media-mem.h"
#include "hi_mmz.h"
#include "sre_debug.h"
void mmz_dump(void);

void *new_zone(const char *name, unsigned long phys_start,
            unsigned long size, unsigned int alloc_type)
{
    void *mmz;

    mmz = hil_mmz_create(name, alloc_type, phys_start, size);
    if(mmz == NULL) {
        uart_printf("Create mem zone failed!\n");
        return NULL;
    }

    if(hil_mmz_register(mmz) != 0) {
        uart_printf("%s, %d, mmz=0x%x\n", __func__, __LINE__, mmz);
        hil_mmz_destroy(mmz);
        return NULL;
    }

    return mmz;
}

void delete_zone(void *zone)
{
    hil_mmz_unregister(zone);
    hil_mmz_destroy(zone);
}

mmb_addr_t new_mmb(const char *name, int size, unsigned int alloc_type,
			const char *zone_name)
{
    void *mmb;

    mmb = hil_mmb_alloc(name, size, alloc_type, zone_name);
    if(mmb == NULL) {
        //mmz_dump();
        return MMB_ADDR_INVALID;
    }


    return (mmb_addr_t)hil_mmb_phys(mmb);
}

void delete_mmb(mmb_addr_t addr)
{
    void *mmb;

    mmb = hil_mmb_getby_phys((unsigned long)addr);
    if(mmb ==NULL)
        return;

    hil_mmb_free(mmb);
}

void *remap_mmb(mmb_addr_t addr)
{
    void *mmb;

    mmb = hil_mmb_getby_phys((unsigned long)addr);
    if(mmb == NULL) {
        uart_printf("%s, %d\n", __func__, __LINE__);
        return NULL;
    }

    return hil_mmb_map2kern(mmb);
}

void *remap_mmb_cached(mmb_addr_t addr)
{
    void *mmb;

    mmb = hil_mmb_getby_phys((unsigned long)addr);
    if(mmb ==NULL) {
        uart_printf("%s, %d\n", __func__, __LINE__);
        return NULL;
    }

    return hil_mmb_map2kern_cached(mmb);
}

void *remap_mmb_uk(mmb_addr_t addr)
{
    void *mmb;

    mmb = hil_mmb_getby_phys((unsigned long)addr);
    if(mmb ==NULL) {
        uart_printf("%s, %d\n", __func__, __LINE__);
        return NULL;
    }

    return hil_mmb_map2uk(mmb);
}

void *remap_mmb_uk_cached(mmb_addr_t addr)
{
    void *mmb;

    mmb = hil_mmb_getby_phys((unsigned long)addr);
    if(mmb ==NULL) {
        uart_printf("%s, %d\n", __func__, __LINE__);
        return NULL;
    }

    return hil_mmb_map2uk_cached(mmb);
}

int unmap_mmb(void *mapped_addr)
{
    void *mmb;

    mmb = hil_mmb_getby_kvirt(mapped_addr);
    if(mmb == NULL) {
        uart_printf("%s, %d\n", __func__, __LINE__);
        return -1;
    }

    return hil_mmb_unmap(mmb);
}

int flush_mmb(unsigned long addr)
{
    void *mmb;

    mmb = hil_mmb_getby_phys(addr);

    hil_mmb_flush_l2cached(mmb);

    return 0;
}

void mmz_dump(void)
{
    hil_mmz_dump();
}

