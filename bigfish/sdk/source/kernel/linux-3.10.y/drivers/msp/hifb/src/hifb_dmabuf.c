/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************/

#ifdef CONFIG_DMA_SHARED_BUFFER

#include <linux/version.h>
#include <linux/dma-buf.h>
#include <linux/highmem.h>
#include <linux/memblock.h>
#include <linux/slab.h>

struct hifb_memblock_pdata {
	phys_addr_t base;
};

static struct sg_table *hifb_memblock_map(struct dma_buf_attachment *attach,
		enum dma_data_direction direction)
{
	struct hifb_memblock_pdata *pdata = attach->dmabuf->priv;
	unsigned long pfn = PFN_DOWN(pdata->base);
	struct page *page = pfn_to_page(pfn);
	struct sg_table *table;
	struct scatterlist *sg;
	int i;
	int ret;
	table = kzalloc(sizeof(*table), GFP_KERNEL);
	if (!table)
		return ERR_PTR(-ENOMEM);

	ret = sg_alloc_table(table, 1, GFP_KERNEL);
	if (ret < 0)
		goto err;
 
	sg_set_page(table->sgl, page, attach->dmabuf->size, 0);
        for_each_sg(table->sgl, sg, table->nents, i)
                sg_dma_address(sg) = sg_phys(sg);
	return table;

err:
	kfree(table);
	return ERR_PTR(ret);
}

static void hifb_memblock_unmap(struct dma_buf_attachment *attach,
		struct sg_table *table, enum dma_data_direction direction)
{
	sg_free_table(table);
	kfree(table);
}

static void __init_memblock hifb_memblock_release(struct dma_buf *buf)
{
	struct hifb_memblock_pdata *pdata = buf->priv;
	/*int err = memblock_free(pdata->base, buf->size);*/
	kfree(pdata);
	buf->priv = NULL;
}

static void *hifb_memblock_do_kmap(struct dma_buf *buf, unsigned long pgoffset,
		bool atomic)
{
	struct hifb_memblock_pdata *pdata = buf->priv;
	unsigned long pfn = PFN_DOWN(pdata->base) + pgoffset;
	struct page *page = pfn_to_page(pfn);

	if (atomic)
		return kmap_atomic(page);
	else
		return kmap(page);
}

static void *hifb_memblock_kmap_atomic(struct dma_buf *buf,
		unsigned long pgoffset)
{
	return hifb_memblock_do_kmap(buf, pgoffset, true);
}

static void hifb_memblock_kunmap_atomic(struct dma_buf *buf,
		unsigned long pgoffset, void *vaddr)
{
	kunmap_atomic(vaddr);
}

static void *hifb_memblock_kmap(struct dma_buf *buf, unsigned long pgoffset)
{
	return hifb_memblock_do_kmap(buf, pgoffset, false);
}

static void hifb_memblock_kunmap(struct dma_buf *buf, unsigned long pgoffset,
		void *vaddr)
{	
	kunmap(vaddr);
}

static int hifb_memblock_mmap(struct dma_buf *buf, struct vm_area_struct *vma)
{
	struct hifb_memblock_pdata *pdata = buf->priv;

	vma->vm_page_prot =  pgprot_writecombine(vma->vm_page_prot);
	return remap_pfn_range(vma, vma->vm_start, PFN_DOWN(pdata->base),
			vma->vm_end - vma->vm_start, vma->vm_page_prot);
}


struct dma_buf_ops hifb_memblock_ops = {
	.map_dma_buf = hifb_memblock_map,
	.unmap_dma_buf = hifb_memblock_unmap,
	.release = hifb_memblock_release,
	.kmap_atomic = hifb_memblock_kmap_atomic,
	.kunmap_atomic = hifb_memblock_kunmap_atomic,
	.kmap = hifb_memblock_kmap,
	.kunmap = hifb_memblock_kunmap,
	.mmap = hifb_memblock_mmap,
};

/**
 * hifb_memblock_export - export a memblock reserved area as a dma-buf
 *
 * @base: base physical address
 * @size: memblock size
 * @flags: mode flags for the dma-buf's file
 *
 * @base and @size must be page-aligned.
 *
 * Returns a dma-buf on success or ERR_PTR(-errno) on failure.
 */
struct dma_buf *hifb_memblock_export(phys_addr_t base, size_t size, int flags)
{
	struct hifb_memblock_pdata *pdata = NULL;
	struct dma_buf *buf = NULL;

	if (PAGE_ALIGN(base) != base || PAGE_ALIGN(size) != size)
		return ERR_PTR(-EINVAL);

	pdata = kzalloc(sizeof(struct hifb_memblock_pdata), GFP_KERNEL);

	if(NULL == pdata){
		return ERR_PTR(-ENOMEM);
	}
	
	pdata->base = base;
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0))
        buf = dma_buf_export(pdata, &hifb_memblock_ops, size, flags);
#else
        buf = dma_buf_export(pdata, &hifb_memblock_ops, size, flags, NULL);
#endif
	if( IS_ERR(buf) )
		kfree(pdata);

	return buf;
}
#endif
