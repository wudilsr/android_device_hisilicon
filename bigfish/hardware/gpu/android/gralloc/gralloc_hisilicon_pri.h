#ifndef GRALLOC_HISILICON_PRIV_H_
#define GRALLOC_HISILICON_PRIV_H_

#define GRALLOC_USAGE_PHYSICAL_MEM  (GRALLOC_USAGE_PRIVATE_3) //Alloc physical memory

#define GRALLOC_USAGE_HISI_VDP      (GRALLOC_USAGE_PRIVATE_0)//VDP

#define GRALLOC_HISI_METADATA_BUF (1)//private frame info for overlay
#define GRALLOC_HISI_METADATA_BUF_SIZE (32*1024)

#define GRALLOC_HISI_NEW_FDS_NUM (1)
#define GRALLOC_HISI_NEW_INTS_NUM (3)

#define HISI_NEW_FD_MEMBER \
    int metadata_fd ;

#define HISI_NEW_INT_MEMBER \
    ion_user_handle_t ion_metadata_hnd ; \
    unsigned long ion_metadata_phy_addr ; \
    size_t ion_metadata_size ;

#define HISI_NEW_FD_MEMBER_INIT \
    metadata_fd(-1)

#define HISI_NEW_INT_MEMBER_INIT \
    ion_metadata_hnd(ION_INVALID_HANDLE), \
    ion_metadata_phy_addr(-1), \
    ion_metadata_size(0)

#endif
