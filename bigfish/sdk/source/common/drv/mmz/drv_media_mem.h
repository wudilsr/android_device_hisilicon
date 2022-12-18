/*********************************************************************************
*
*  Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
*  This program is confidential and proprietary to Hisilicon Technologies Co., Ltd.
*  (Hisilicon), and may not be copied, reproduced, modified, disclosed to
*  others, published or used, in whole or in part, without the express prior
*  written permission of Hisilicon.
*
***********************************************************************************/

#ifndef __ASM_ARCH_MEDIA_MEM_H
#define __ASM_ARCH_MEDIA_MEM_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MMZ_V2_SUPPORT
#define MMB_SHARE_SUPPORT
#endif

#define HIL_MMZ_NAME_LEN        32

#ifndef PRINTK_CA
#ifdef  CONFIG_SUPPORT_CA_RELEASE
#define PRINTK_CA(fmt, args...)
#else
#define PRINTK_CA(fmt, args...) do{\
        HI_PRINT("%s(%d): " fmt, __FILE__, __LINE__, ##args); \
} while (0)
#endif
#endif

#define CFG_MMZ_MINI   //CFG_MMZ_MINI not compile *_v2, code size is smaller.

/* just for inf */
struct hil_media_memory_zone {
    char name[HIL_MMZ_NAME_LEN];
    unsigned long gfp;
    unsigned long phys_start;
    unsigned long nbytes;
    struct list_head list;
  //  unsigned char *bitmap;
    struct device *cma_dev; 	
    struct list_head mmb_list;
    unsigned int alloc_type;
    unsigned long block_align;
    void (*destructor)(const void *);
};
typedef struct hil_media_memory_zone hil_mmz_t;

#define HIL_MMZ_FMT_S "PHYS(0x%08lX, 0x%08lX), GFP=%lu, nBYTES=%luKB,   NAME=\"%s\""
#define hil_mmz_fmt_arg(p) (p)->phys_start,(p)->phys_start+(p)->nbytes-1,(p)->gfp,(p)->nbytes/SZ_1K,(p)->name


/* for inf & usr */
#define HIL_MMB_NAME_LEN 16
struct hil_media_memory_block {
    char name[HIL_MMB_NAME_LEN];
    struct hil_media_memory_zone *zone;
    struct list_head list;
    unsigned long phys_addr;
    void *kvirt;
    unsigned long length;
    unsigned long flags;
    unsigned int order;
    int phy_ref;
    int map_ref;
    int kphy_ref;
};
typedef struct hil_media_memory_block hil_mmb_t;

#define hil_mmb_kvirt(p)    ({hil_mmb_t *__mmb=(p); BUG_ON(__mmb==NULL); __mmb->kvirt;})
#define hil_mmb_phys(p)     ({hil_mmb_t *__mmb=(p); BUG_ON(__mmb==NULL); __mmb->phys_addr;})
#define hil_mmb_length(p)   ({hil_mmb_t *__mmb=(p); BUG_ON(__mmb==NULL); __mmb->length;})
#define hil_mmb_name(p)     ({hil_mmb_t *__mmb=(p); BUG_ON(__mmb==NULL); __mmb->name;})
#define hil_mmb_zone(p)     ({hil_mmb_t *__mmb=(p); BUG_ON(__mmb==NULL); __mmb->zone;})

#define HIL_MMB_MAP2KERN    (1<<0)
#define HIL_MMB_MAP2KERN_CACHED (1<<1)
#define HIL_MMB_RELEASED    (1<<2)

#define HIL_MMB_FMT_S "phys(0x%08lX, 0x%08lX), kvirt=0x%p, flags=0x%08lX, length=%luKB,    name=\"%s\""
#define hil_mmb_fmt_arg(p) (p)->phys_addr,mmz_grain_align((p)->phys_addr+(p)->length)-1,(p)->kvirt,(p)->flags,(p)->length/SZ_1K,(p)->name



/********** API_0 for inf *********/
extern hil_mmz_t *hil_mmz_create(const char *name, unsigned long gfp, unsigned long phys_start,
            unsigned long nbytes);
extern hil_mmz_t *hil_mmz_create_v2(const char *name, unsigned long gfp, unsigned long phys_start,
            unsigned long nbytes,  unsigned int alloc_type, unsigned long block_align);
extern int hil_mmz_destroy(hil_mmz_t *zone);
extern int hil_mmz_register(hil_mmz_t *zone);
extern int hil_mmz_unregister(hil_mmz_t *zone);
extern hil_mmb_t *hil_mmb_getby_phys(unsigned long addr);
extern hil_mmb_t *hil_mmb_getby_phys_2(unsigned long addr, unsigned long *Outoffset);
extern hil_mmb_t *hil_mmb_getby_kvirt(void *virt);
extern void* hil_mmb_map2kern(hil_mmb_t *mmb);
extern void* hil_mmb_map2kern_cached(hil_mmb_t *mmb);
extern int hil_mmb_unmap(hil_mmb_t *mmb);



/********** API_1 for inf & usr *********/

extern hil_mmb_t *hil_mmb_alloc(const char *name, unsigned long size, unsigned long align,
        unsigned long gfp, const char *mmz_name);
extern int hil_mmb_free(hil_mmb_t *mmb);
extern hil_mmb_t *hil_mmb_alloc_v2(const char *name, unsigned long size, unsigned long align,
        unsigned long gfp, const char *mmz_name, unsigned int order);

extern int hil_mmb_get(hil_mmb_t *mmb);
extern int hil_mmb_put(hil_mmb_t *mmb);
#ifdef MMB_SHARE_SUPPORT
extern int hil_mmb_force_put(hil_mmb_t *mmb);
#endif
extern int get_mmz_info_phys_start(void);

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
extern int mmz_read_proc(char *page, char **start, off_t off,
                            int count, int *eof, void *data);
#else
extern int mmz_read_proc(struct seq_file *m, void *v);
#endif

extern int mmz_write_proc(struct file *file, const char __user *buffer,
                                   unsigned long count, void *data);

int HI_DRV_MMZ_Init(void);
void HI_DRV_MMZ_Exit(void);

#ifdef __cplusplus
}
#endif

#endif
