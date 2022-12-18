/* media-mem.c
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
#include "sre_mem.h"
#include "sre_securecache.h"
#include "sre_securemmu.h"
#include "boot.h"
#include "hi_mmz.h"
#include "secure_mem.h"

#define MMZ_DBG_LEVEL 0x0
#define mmz_trace(level, s, params...) do { \
        if (level & MMZ_DBG_LEVEL) \
        PRINTK_CA("[%s, %d]: " s "\n", \
            __FUNCTION__, __LINE__, params);\
} while (0)

#define mmz_trace_func() mmz_trace(0x02, "%s", __FILE__)

#define SECTION_SIZE    (1 << 20)
#define MMZ_GRAIN       SECTION_SIZE

#define mmz_align2(x, g)      ((((x) + (g) - 1) / (g)) * (g))
#define mmz_grain_align(x)    mmz_align2(x, MMZ_GRAIN)
#define mmz_length2grain(len) (mmz_grain_align(len) / MMZ_GRAIN)

#define MACH_MMB(p, val, member) do {\
        hil_mmz_t *__mach_mmb_zone__; \
        (p) = NULL; \
        list_for_each_entry(__mach_mmb_zone__, &mmz_list, list) { \
            hil_mmb_t *__mach_mmb__; \
            list_for_each_entry(__mach_mmb__, &__mach_mmb_zone__->mmb_list, list) { \
                if (__mach_mmb__->member == (val)){ \
                    (p) = __mach_mmb__; \
                    break; \
                } \
            } \
            if (p) break;\
        } \
    } while (0)


#define BUG_ON(x, ret) do { \
    if (x) { \
        PRINTK_CA("Fatal error!\n"); \
        return ret; \
    } \
} while (0)

//#define hil_mmb_length(p)   ({hil_mmb_t *__mmb= (hil_mmb_t *)(p); BUG_ON((__mmb==NULL),  0); __mmb->length;})

#define SZ_1K 1024
#define HIL_MMZ_FMT_S "PHYS(0x%x, 0x%x), nBYTES=%dKB,   NAME=\"%s\""
#define hil_mmz_fmt_arg(p) (p)->phys_start,(p)->phys_start+(p)->nbytes-1,(p)->nbytes/SZ_1K,(p)->name

#define HIL_MMB_FMT_S "phys(0x%08lX, 0x%08lX), kvirt=0x%p, flags=0x%08lX, length=%luKB,    name=\"%s\""
#define hil_mmb_fmt_arg(p) (p)->phys_addr,mmz_grain_align((p)->phys_addr+(p)->length)-1,(p)->kvirt,(p)->flags,(p)->length/SZ_1K,(p)->name


/* flags */
#define HIL_MMB_MAP2KERN          (1<<0)
#define HIL_MMB_MAP2KERN_CACHED   (1<<1)
#define HIL_MMB_MAP2UK            (1<<2)
#define HIL_MMB_MAP2UK_CACHED     (1<<3)
#define HIL_MMB_RELEASED          (1<<4)


#define HIL_MMZ_NAME_LEN 32
struct hil_media_memory_zone {
    char name[HIL_MMZ_NAME_LEN];
    unsigned long phys_start;
    unsigned long nbytes;
    struct list_head list;
    struct list_head mmb_list;
    unsigned int alloc_type;
    void (*destructor)(void *);
};
typedef struct hil_media_memory_zone hil_mmz_t;

#define HIL_MMB_NAME_LEN 16
struct hil_media_memory_block {
    char name[HIL_MMB_NAME_LEN];
    struct hil_media_memory_zone *zone;
    struct list_head list;
    unsigned long phys_addr;
    void *kvirt;
    unsigned long length;
    unsigned long flags;
    int map_ref;
};
typedef struct hil_media_memory_block hil_mmb_t;


static LIST_HEAD(mmz_list);

static int anony = 0;

static void *mmz_alloc(unsigned long size)
{
    return SRE_MemAlloc(OS_MID_SYS, OS_MEM_DEFAULT_FSC_PT, size);
}

// Deallocates or frees a memory block
static void mmz_free(void *memblock)
{
    SRE_MemFree(OS_MID_SYS, memblock);
}

unsigned long strlcpy(char *dest, const char *src, unsigned long size)
{
    unsigned long ret = strlen(src);

    if (size) {
        unsigned long len = (ret >= size) ? size - 1 : ret;
        memcpy(dest, src, len);
        dest[len] = '\0';
    }
    return ret;
}

static int mmz_check(hil_mmz_t *zone)
{
    hil_mmz_t *p;

    unsigned long new_start = zone->phys_start;
    unsigned long new_end = zone->phys_start + zone->nbytes;

    if (zone->nbytes == 0) {
        return -1;
    }

    list_for_each_entry(p, &mmz_list, list) {
        unsigned long start, end;

        start = p->phys_start;
        end = p->phys_start + p->nbytes;

        if (new_start >= end) {
            continue;
        } else if ((new_start < start) && (new_end <= start)) {
            continue;
        }

        PRINTK_CA("ERROR: Conflict MMZ:\n");
        PRINTK_CA("MMZ new:   " HIL_MMZ_FMT_S "\n", hil_mmz_fmt_arg(zone));
        PRINTK_CA("MMZ exist: " HIL_MMZ_FMT_S "\n", hil_mmz_fmt_arg(p));
        PRINTK_CA("Add new MMZ failed!\n");
        return -1;
    }

    return 0;
}

static unsigned long _find_fixed_region(unsigned long *region_len, hil_mmz_t *mmz,
                                    unsigned long size/*, unsigned long align*/)
{
    unsigned long start;
    unsigned long fixed_start = 0;
    unsigned long len =0;
    unsigned long blank_len =0;
    long fixed_len = -1;
    hil_mmb_t *p = NULL;

    mmz_trace_func();

    /* align to phys address first! */
    start = mmz_align2(mmz->phys_start, MMZ_GRAIN);
    len = mmz_grain_align(size); //size to align to 1M

    list_for_each_entry(p,&mmz->mmb_list, list) {
        hil_mmb_t *next;
        mmz_trace(4,"p->phys_addr=0x%08lX p->length = %luKB \t",p->phys_addr,
                    p->length/SZ_1K);
        next = list_entry(p->list.next, typeof(*p), list);
        mmz_trace(4,",next = 0x%08lX\n\n", next->phys_addr);

        /*if p is the first entry or not*/
        if(list_first_entry(&mmz->mmb_list,typeof(*p),list) == p) {
            blank_len = p->phys_addr - start;
            if((blank_len < fixed_len) && (blank_len>=len)) {
                fixed_len = blank_len;
                fixed_start = start;
                mmz_trace(4,"%d: fixed_region: start=0x%08lX, len=%luKB\n",__LINE__,
                            fixed_start, fixed_len/SZ_1K);
            }
        }

        start = mmz_align2((p->phys_addr + p->length), MMZ_GRAIN); //start align to usr's align
        BUG_ON( ((start < mmz->phys_start) || (start > (mmz->phys_start + mmz->nbytes))), 0 );
        /*if we have to alloc after the last node*/
        if ( list_is_last(&p->list, &mmz->mmb_list) ) {
            blank_len = mmz->phys_start + mmz->nbytes - start;
            if ((blank_len < fixed_len) && (blank_len >= len)){
                fixed_len = blank_len;
                fixed_start = start;
                mmz_trace(4,"%d: fixed_region: start=0x%08lX, len=%luKB\n",__LINE__,
                            fixed_start, fixed_len/SZ_1K);
                break;
            } else {
                if(fixed_len != -1)
                    goto out;
                fixed_start = 0;
                mmz_trace(4,"%d: fixed_region: start=0x%08lX, len=%luKB\n",__LINE__,
                            fixed_start, fixed_len/SZ_1K);
                goto out;
            }
        }

        //blank is too little
        if ((start + len) > next->phys_addr) {
            mmz_trace(4,"start=0x%08lX ,len=%lu,next=0x%08lX\n",start,len,next->phys_addr);
            continue;
        }

        blank_len = next->phys_addr - start;
        if((blank_len < fixed_len) && (blank_len >= len)) {
            fixed_len = blank_len;
            fixed_start = start;
            mmz_trace(4,"%d: fixed_region: start=0x%08lX, len=%luKB\n",__LINE__,
                        fixed_start, fixed_len/SZ_1K);
        }
    }

    if ((mmz_grain_align(start+len) <= (mmz->phys_start + mmz->nbytes))
        && (start >= mmz->phys_start) && (start < (mmz->phys_start + mmz->nbytes))) {
        fixed_len = len;
        fixed_start = start;
        mmz_trace(4,"%d: fixed_region: start=0x%08lX, len=%luKB\n",__LINE__,
                    fixed_start, fixed_len/SZ_1K);
    } else {
        fixed_start = 0;
        mmz_trace(4,"%d: fixed_region: start=0x%08lX, len=%luKB\n",__LINE__,
                    fixed_start, len/SZ_1K);
    }

out:
    *region_len = len;

    return fixed_start;
}


static int _do_mmb_alloc(hil_mmb_t *mmb)
{
    hil_mmb_t *p = NULL;

    mmz_trace_func();

    /* add mmb sorted */
    list_for_each_entry(p, &mmb->zone->mmb_list, list) {
        if (mmb->phys_addr < p->phys_addr) {
            break;
        }

        if (mmb->phys_addr == p->phys_addr) {
            PRINTK_CA("ERROR: media-mem allocator bad in %s! (%s, %d)",
                   mmb->zone->name, __FUNCTION__, __LINE__);
        }
    }
    list_add(&mmb->list, p->list.prev);

    mmz_trace(1, HIL_MMB_FMT_S, hil_mmb_fmt_arg(mmb));

    return 0;
}

static hil_mmb_t *mmb_alloc(const char *name, unsigned long size, unsigned int alloc_type,
				const char *mmz_name)
{
    hil_mmz_t *mmz;
    hil_mmb_t *mmb;

    unsigned long start;
    unsigned long region_len;

    unsigned long fixed_start = 0;
    long fixed_len = -1;
    hil_mmz_t *fixed_mmz = NULL;

    mmz_trace_func();

    if ((size <= 0) || (size > 0x40000000UL)) {
        return NULL;
    }

    if ((SECURE_MEM != alloc_type) && (NON_SECURE_MEM != alloc_type)) {
        PRINTK_CA("%s: invalid alloc type!", __FUNCTION__);
        return NULL;
    }

    size = mmz_grain_align(size);

    mmz_trace(1, "size=%luKB", size / SZ_1K);

    list_for_each_entry(mmz, &mmz_list, list) {
        if (alloc_type != mmz->alloc_type)
            continue;

        if ((mmz_name != NULL) && (*mmz_name != '\0')
            && strcmp(mmz_name, mmz->name)) {
            continue;
        }

        if ((mmz_name == NULL) && (anony == 1)) {
            if (strcmp("anonymous", mmz->name))
                continue;
        }
        mmz_trace(1, HIL_MMZ_FMT_S, hil_mmz_fmt_arg(mmz));

        start = _find_fixed_region(&region_len, mmz, size);
        if ((fixed_len > region_len) && (start != 0)) {
            fixed_len   = region_len;
            fixed_start = start;
            fixed_mmz = mmz;
        }
    }

    if (fixed_mmz == NULL) {
        return NULL;
    }

    mmb = mmz_alloc(sizeof(hil_mmb_t) + 1);
    if (mmb == NULL) {
        PRINTK_CA("%s: malloc failed!", __FUNCTION__);
        return NULL;
    }

    memset(mmb, 0, sizeof(hil_mmb_t) + 1);
    mmb->zone = fixed_mmz;
    mmb->phys_addr = fixed_start;
    mmb->length = size;
    if (name) {
        strlcpy(mmb->name, name, sizeof(mmb->name));
    } else {
        strcpy(mmb->name, "<null>");
    }

    if (_do_mmb_alloc(mmb)) {
        mmz_free(mmb);
        mmb = NULL;
    }

    return mmb;
}


static void *mmb_remap_cached(unsigned long pa, unsigned long size)
{
    /* 0 indicat remap succeed and va equal with pa */
    return (0 != map_to_s(pa, size)) ? NULL : (void *)pa;
}

static void *mmb_remap_nocache(unsigned long pa, unsigned long size)
{
    /* 0 indicat remap succeed and va equal with pa */
    return (0 != map_to_s_nocache(pa, size)) ? NULL : (void *)pa;
}

static void *mmb_remap_uk_cached(unsigned long pa, unsigned long size)
{
    /* 0 indicat remap succeed and va equal with pa */
    return (0 != map_to_s(pa, size)) ? NULL : (void *)pa;
}

static void *mmb_remap_uk_nocache(unsigned long pa, unsigned long size)
{
    /* 0 indicat remap succeed and va equal with pa */
    return (0 != map_to_s_nocache(pa, size)) ? NULL : (void *)pa;
}

static void mmb_unmap(void * va, unsigned long size, unsigned long flags)
{
    if (0 != unmap_from_s(va, size)) {
		cprintf("unmap memory(va:0x%x, size:0x%x) failed.\n", va, size);
	}
}

static void *mmb_map2kern(hil_mmb_t *mmb, unsigned long cached)
{
    if (mmb->flags & HIL_MMB_MAP2UK) {
        PRINTK_CA("mmb<%s> already mapped to both usr and kern.",
               mmb->name);
        return NULL;
    }

    if (mmb->flags & HIL_MMB_MAP2KERN) {
        if ((cached * HIL_MMB_MAP2KERN_CACHED) != (mmb->flags & HIL_MMB_MAP2KERN_CACHED)) {
            PRINTK_CA("mmb<%s> already kernel-mapped %s, can not be re-mapped as %s.",
               mmb->name,
               (mmb->flags & HIL_MMB_MAP2KERN_CACHED) ? "cached" : "non-cached",
               (cached) ? "cached" : "non-cached" );
            return NULL;
        }

        mmb->map_ref++;

        return mmb->kvirt;
    }

    if (cached) {
        mmb->flags |= HIL_MMB_MAP2KERN_CACHED;
        mmb->kvirt = mmb_remap_cached(mmb->phys_addr, mmb->length);
    } else {
        mmb->flags &= ~HIL_MMB_MAP2KERN_CACHED;
        mmb->kvirt = mmb_remap_nocache(mmb->phys_addr, mmb->length);
    }

    if (mmb->kvirt) {
        mmb->flags |= HIL_MMB_MAP2KERN;
        mmb->map_ref++;
    }

    return mmb->kvirt;
}

static void *mmb_map2uk(hil_mmb_t *mmb, unsigned long cached)
{
    if (mmb->flags & HIL_MMB_MAP2KERN) {
        PRINTK_CA("mmb<%s> already mapped to kernel.",
               mmb->name);
        return NULL;
    }

    if (mmb->flags & HIL_MMB_MAP2UK) {
        if ((cached * HIL_MMB_MAP2UK_CACHED) != (mmb->flags & HIL_MMB_MAP2UK_CACHED)) {
            PRINTK_CA("mmb<%s> already uk-mapped %s, can not be re-mapped as %s.",
               mmb->name,
               (mmb->flags & HIL_MMB_MAP2UK_CACHED) ? "cached" : "non-cached",
               (cached) ? "cached" : "non-cached" );
            return NULL;
        }

        mmb->map_ref++;

        return mmb->kvirt;
    }

    if (cached) {
        mmb->flags |= HIL_MMB_MAP2UK_CACHED;
        mmb->kvirt = mmb_remap_uk_cached(mmb->phys_addr, mmb->length);
    } else {
        mmb->flags &= ~HIL_MMB_MAP2UK_CACHED;
        mmb->kvirt = mmb_remap_uk_nocache(mmb->phys_addr, mmb->length);
    }

    if (mmb->kvirt) {
        mmb->flags |= HIL_MMB_MAP2UK;
        mmb->map_ref++;
    }

    return mmb->kvirt;
}

static int mmb_free(hil_mmb_t *mmb)
{
    if ((mmb->flags & HIL_MMB_MAP2KERN_CACHED)
        || (mmb->flags & HIL_MMB_MAP2UK_CACHED)) {
        SRE_DCacheFlush((void *)mmb->kvirt, mmb->length, 1);
        l2x0_flush_range(mmb->phys_addr, mmb->phys_addr + mmb->length);
    }

    list_del(&mmb->list);
    mmz_free(mmb);

    return 0;
}

void *hil_mmz_create(const char *name, unsigned int alloc_type,
                unsigned long phys_start, unsigned long nbytes)
{
    hil_mmz_t *p = NULL;

    mmz_trace_func();

    if (name == NULL) {
        PRINTK_CA("%s: 'name' can not be zero!", __FUNCTION__);
        return NULL;
    }

    if ((SECURE_MEM != alloc_type) && (NON_SECURE_MEM != alloc_type)) {
        PRINTK_CA("%s: invalid alloc type!", __FUNCTION__);
        return NULL;
    }

    p = mmz_alloc(sizeof(hil_mmz_t) + 1);
    if (p == NULL){
        PRINTK_CA("%s: malloc failed!", __FUNCTION__);
        return NULL;
    }

    memset(p, 0, sizeof(hil_mmz_t) + 1);
    strlcpy(p->name, name, sizeof(p->name));
    p->phys_start = phys_start;
    p->nbytes = nbytes;
    p->alloc_type = alloc_type;
    p->destructor = mmz_free;

    INIT_LIST_HEAD(&p->list);
    INIT_LIST_HEAD(&p->mmb_list);

    return (void *)p;
}

int hil_mmz_destroy(void *mmz)
{
    if (mmz == NULL) {
        return -1;
    }

    hil_mmz_t *zone = (hil_mmz_t *)mmz;

    if (zone->destructor) {
        zone->destructor(zone);
    } else
        PRINTK_CA("%s: missed destructor!", __FUNCTION__);

    return 0;
}

int hil_mmz_register(void *mmz)
{
    int ret = 0;

    if (mmz == NULL) {
        cprintf("NULL zone!\n");
        return -1;
    }

    hil_mmz_t *zone = (hil_mmz_t *)mmz;
    mmz_trace(1, HIL_MMZ_FMT_S, hil_mmz_fmt_arg(zone));

    ret = mmz_check(zone);
    if (ret) {
        cprintf("%s, %d, illegal mmz!!!\n", __func__, __LINE__);
        return ret;
    }

    INIT_LIST_HEAD(&zone->mmb_list);

    list_add(&zone->list, &mmz_list);

    return 0;
}

int hil_mmz_unregister(void *mmz)
{
    int losts = 0;
    hil_mmb_t *p;

    if (mmz == NULL) {
        cprintf("%s, %d\n", __func__, __LINE__);
        return -1;
    }

    hil_mmz_t *zone = (hil_mmz_t *)mmz;
    mmz_trace_func();

    list_for_each_entry(p, &zone->mmb_list, list) {
        losts++;
    }

    if (losts) {
        cprintf("%s, %d\n", __func__, __LINE__);
        PRINTK_CA("%d mmbs not free, mmz<%s> can not be deregistered!\n",
                losts, zone->name);
        return -1;
    }

    list_del(&zone->list);

    return 0;
}

void *hil_mmb_alloc(const char *name, unsigned long size,
                unsigned int alloc_type, const char *mmz_name)
{
    hil_mmb_t *mmb;

    mmb = mmb_alloc(name, size, alloc_type, mmz_name);

    return (void *)mmb;
}

void *hil_mmb_map2kern(void *_mmb)
{
    void *p;

    if (_mmb == NULL) {
        cprintf("%s, %d\n", __func__, __LINE__);
        return NULL;
    }

    hil_mmb_t *mmb = (hil_mmb_t *)_mmb;
    p = mmb_map2kern(mmb, 0);

    return p;
}

void *hil_mmb_map2kern_cached(void *_mmb)
{
    void *p;

    if (_mmb == NULL) {
        return NULL;
    }

    hil_mmb_t *mmb = (hil_mmb_t *)_mmb;
    p = mmb_map2kern(mmb, 1);

    return p;
}

void *hil_mmb_map2uk(void *_mmb)
{
    void *p;

    if (_mmb == NULL) {
        cprintf("%s, %d\n", __func__, __LINE__);
        return NULL;
    }

    hil_mmb_t *mmb = (hil_mmb_t *)_mmb;
    p = mmb_map2uk(mmb, 0);

    return p;
}

void *hil_mmb_map2uk_cached(void *_mmb)
{
    void *p;

    if (_mmb == NULL) {
        return NULL;
    }

    hil_mmb_t *mmb = (hil_mmb_t *)_mmb;
    p = mmb_map2uk(mmb, 1);

    return p;
}


int hil_mmb_unmap(void *_mmb)
{
    int ref;

    if (_mmb == NULL) {
        return -1;
    }

    hil_mmb_t *mmb = (void *)_mmb;
    if ((mmb->flags & HIL_MMB_MAP2KERN_CACHED) 
        || (mmb->flags & HIL_MMB_MAP2UK_CACHED)) {
        SRE_DCacheFlush((void *)mmb->kvirt, mmb->length, /*0*/1);
        l2x0_flush_range(mmb->phys_addr, mmb->phys_addr + mmb->length);
    }

    if ((mmb->flags & HIL_MMB_MAP2KERN) || (mmb->flags & HIL_MMB_MAP2UK)) {
        ref = --mmb->map_ref;
        if (mmb->map_ref != 0) {
            return ref;
        }

        mmb_unmap(mmb->kvirt, mmb->length, mmb->flags);
    }

    mmb->kvirt  = NULL;
    mmb->flags &= ~HIL_MMB_MAP2KERN;
    mmb->flags &= ~HIL_MMB_MAP2KERN_CACHED;
    mmb->flags &= ~HIL_MMB_MAP2UK;
    mmb->flags &= ~HIL_MMB_MAP2UK_CACHED;

    if (mmb->flags & HIL_MMB_RELEASED) {
        cprintf("%s, %d\n", __func__, __LINE__);
        mmb_free(mmb);
    }

    return 0;
}

int hil_mmb_free(void *_mmb)
{
    mmz_trace_func();

    if (_mmb == NULL) {
        return -1;
    }

    hil_mmb_t *mmb = (hil_mmb_t *)_mmb;
    mmz_trace(1, HIL_MMB_FMT_S, hil_mmb_fmt_arg(mmb));

    if (mmb->flags & HIL_MMB_RELEASED) {
        PRINTK_CA("hil_mmb_free: amazing, mmb<%s> is released before, but still used!\n", mmb->name);

        return 0;
    }

    if ((mmb->flags & HIL_MMB_MAP2KERN) || (mmb->flags & HIL_MMB_MAP2UK)) {
        PRINTK_CA("hil_mmb_free: free mmb<%s> delayed for which is kernel-mapped to 0x%p with map_ref %d!\n",
               mmb->name, mmb->kvirt, mmb->map_ref);
        mmb->flags |= HIL_MMB_RELEASED;

        return 0;
    }

    mmb_free(mmb);

    return 0;
}

void hil_mmz_dump(void)
{
	hil_mmz_t *p;
	hil_mmb_t *q;
	unsigned long mmz_no = 0;
	unsigned long mmb_no = 0;

	list_for_each_entry(p, &mmz_list, list) {
	cprintf("\n-----------------------------------------------------------------------------\n");
	cprintf("MMZ %d(%s)  Addr=0x%X  Size=0x%X  Type=0x%X\n", mmz_no, 
			p->name?p->name:"null", p->phys_start, p->nbytes, p->alloc_type);
	cprintf("-----------------------------------------------------------------------------\n");

        mmb_no = 0;
        list_for_each_entry(q,&p->mmb_list, list) {
            cprintf("MMB No.%d  ", mmb_no);
            cprintf("Name: %s  ", q->name);
            cprintf("Addr=0x%x  ", q->phys_addr);
            cprintf("Size=0x%x  ", q->length);
            cprintf("Flags=0x%x  ", q->flags);
            mmb_no++;
	    cprintf("\n");
        }
        mmz_no++;
    }
    cprintf("-----------------------------------------------------------------------------\n");
}

void *hil_mmb_getby_phys(unsigned long addr)
{
    hil_mmb_t *p;

    MACH_MMB(p, addr, phys_addr);

    return (void *)p;
}

void *hil_mmb_getby_kvirt(void *virt)
{
    hil_mmb_t *p;

    if (virt == NULL) {
        return NULL;
    }

    MACH_MMB(p, virt, kvirt);

    return (void *)p;
}

void *hil_mmb_kvirt(void *_mmb)
{
    if (_mmb == NULL) {
        return NULL;
    }

    hil_mmb_t *mmb = (hil_mmb_t *)_mmb;
    return mmb->kvirt;
}

unsigned long hil_mmb_phys(void *_mmb)
{
    if (_mmb == NULL) {
        return NULL;
    }

    hil_mmb_t *mmb = (hil_mmb_t *)_mmb;
    return mmb->phys_addr;
}

void hil_mmb_flush_l2cached(void *_mmb)
{
    if (_mmb == NULL) {
        return;
    }

    hil_mmb_t *mmb = (hil_mmb_t *)_mmb;

    if (mmb && (mmb->flags & HIL_MMB_MAP2KERN_CACHED)) {
        SRE_DCacheFlush((void *)mmb->kvirt, mmb->length, 1);
        l2x0_flush_range(mmb->phys_addr, mmb->phys_addr + mmb->length);
    }
}

int hil_tee_is_sec_mem(unsigned long phy_addr, unsigned long size)
{
	unsigned long zone_size;
	unsigned long phy_addr_start, phy_addr_end;
	unsigned long sec_os_start, sec_os_end;
	unsigned long sec_mmz_start, sec_mmz_end;

	phy_addr_start = phy_addr;
	phy_addr_end = phy_addr_start + size;
	//cprintf("%s, %d, phy_addr_start:0x%x, phy_addr_end:0x%x\n", __func__, __LINE__, phy_addr_start, phy_addr_end);

	sec_os_start = (unsigned long)sec_mem_get_zone_range(SEC_OS_MEM, &zone_size);
	sec_os_end = sec_os_start + zone_size;
	//cprintf("%s, %d, sec_os_start:0x%x, sec_os_end:0x%x\n", __func__, __LINE__, sec_os_start, sec_os_end);

	sec_mmz_start = (unsigned long)sec_mem_get_zone_range(SEC_MMZ_MEM, &zone_size);
	sec_mmz_end = sec_mmz_start + zone_size;
	//cprintf("%s, %d, sec_mmz_start:0x%x, sec_mmz_end:0x%x\n", __func__, __LINE__, sec_mmz_start, sec_mmz_end);
	if(((phy_addr_start >= sec_os_start && phy_addr_start < sec_os_end)
	&& (phy_addr_end > sec_os_start && phy_addr_end < sec_os_end)
	&& (phy_addr_end >= phy_addr_start)) ||
	((phy_addr_start >= sec_mmz_start && phy_addr_start < sec_mmz_end)
	&& (phy_addr_end > sec_mmz_start && phy_addr_end < sec_mmz_end)
	&& (phy_addr_end >= phy_addr_start))) {
		//cprintf("%s, %d\n", __func__, __LINE__);
		return 1;
	}
	//cprintf("%s, %d\n", __func__, __LINE__);

	return 0;
    
}

int hil_tee_is_nonsec_mem(unsigned long phy_addr, unsigned long size)
{
	unsigned long zone_size;
	unsigned long phy_addr_start, phy_addr_end;
	unsigned long nonsec_os_start, nonsec_os_end;
	unsigned long nonsec_mmz_start, nonsec_mmz_end;

	phy_addr_start = phy_addr;
	phy_addr_end = phy_addr_start + size;
	//cprintf("%s, %d, phy_addr_start:0x%x, phy_addr_end:0x%x\n", __func__, __LINE__, phy_addr_start, phy_addr_end);

	nonsec_os_start = (unsigned long)sec_mem_get_zone_range(NON_SEC_OS_MEM, &zone_size);
	nonsec_os_end = nonsec_os_start + zone_size;
	//cprintf("%s, %d, nonsec_os_start:0x%x, nonsec_os_end:0x%x\n", __func__, __LINE__, nonsec_os_start, nonsec_os_end);

	nonsec_mmz_start = (unsigned long)sec_mem_get_zone_range(NON_SEC_MMZ_MEM, &zone_size);
	nonsec_mmz_end = nonsec_mmz_start + zone_size;
	//cprintf("%s, %d, nonsec_mmz_start:0x%x, nonsec_mmz_end:0x%x\n", __func__, __LINE__, nonsec_mmz_start, nonsec_mmz_end);
	if(((phy_addr_start >= nonsec_os_start && phy_addr_start < nonsec_os_end)
	    && (phy_addr_end > nonsec_os_start && phy_addr_end < nonsec_os_end)
	    && (phy_addr_end >= phy_addr_start)) ||
	    ((phy_addr_start >= nonsec_mmz_start && phy_addr_start < nonsec_mmz_end)
	    && (phy_addr_end > nonsec_mmz_start && phy_addr_end <= nonsec_mmz_end)
	    && (phy_addr_end >= phy_addr_start))) {
	    	//cprintf("%s, %d\n", __func__, __LINE__);
	    	return 1;
	}
	//cprintf("%s, %d\n", __func__, __LINE__);
    	return 0;
}

