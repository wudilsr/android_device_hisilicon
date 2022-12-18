#ifndef UBIUTILS_H_INCLUDED
#define UBIUTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _IOC_NRBITS     8
#define _IOC_TYPEBITS   8

/*
 * Let any architecture override either of the following before
 * including this file.
 */

#ifndef _IOC_SIZEBITS
# define _IOC_SIZEBITS  14
#endif

#ifndef _IOC_DIRBITS
# define _IOC_DIRBITS   2
#endif
#define _IOC_NRMASK     ((1 << _IOC_NRBITS)-1)
#define _IOC_TYPEMASK   ((1 << _IOC_TYPEBITS)-1)
#define _IOC_SIZEMASK   ((1 << _IOC_SIZEBITS)-1)
#define _IOC_DIRMASK    ((1 << _IOC_DIRBITS)-1)

#define _IOC_NRSHIFT    0
#define _IOC_TYPESHIFT  (_IOC_NRSHIFT+_IOC_NRBITS)
#define _IOC_SIZESHIFT  (_IOC_TYPESHIFT+_IOC_TYPEBITS)
#define _IOC_DIRSHIFT   (_IOC_SIZESHIFT+_IOC_SIZEBITS)

#define _IOC(dir,type,nr,size)    \
    (((dir)  << _IOC_DIRSHIFT)  | \
     ((type) << _IOC_TYPESHIFT) | \
     ((nr)   << _IOC_NRSHIFT)   | \
     ((size) << _IOC_SIZESHIFT))

#define _IOC_TYPECHECK(t)   (sizeof(t))

#define _IOC_WRITE          1U

/* used to create numbers */
#define _IOW(type,nr,size)  _IOC(_IOC_WRITE,(type),(nr),(_IOC_TYPECHECK(size)))

#define UBI_VOL_NUM_AUTO    (-1)
#define UBI_DEV_NUM_AUTO    (-1)

/* Maximum volume name length */
#define UBI_MAX_VOLUME_NAME 127
#define EINVAL              22  /* Invalid argument */
#define O_RDONLY            00000000

#define UBI_IOC_MAGIC       'o'
#define UBI_CTRL_IOC_MAGIC  'o'
#define UBI_VOL_IOC_MAGIC   'O'

/* Create an UBI volume */
#define UBI_IOCMKVOL _IOW(UBI_IOC_MAGIC, 0, struct ubi_mkvol_req)

/* Attach an MTD device */
#define UBI_IOCATT _IOW(UBI_CTRL_IOC_MAGIC, 64, struct ubi_attach_req)

/* Start UBI volume update */
#define UBI_IOCVOLUP _IOW(UBI_VOL_IOC_MAGIC, 0, long long)

#define UBI_IOCDET _IOW(UBI_CTRL_IOC_MAGIC, 65, int32_t)

enum {
    UBI_DYNAMIC_VOLUME = 3,
    UBI_STATIC_VOLUME  = 4,
};

struct ubi_attach_request
{
    int dev_num;
    int mtd_num;
    int vid_hdr_offset;
};

struct ubi_mkvol_request
{
    int         vol_id;
    int         alignment;
    long long   bytes;
    int         vol_type;
    const char* name;
};

struct ubi_attach_req {
    int32_t ubi_num;
    int32_t mtd_num;
    int32_t vid_hdr_offset;
    int8_t padding[12];
};

struct ubi_mkvol_req {
    int32_t vol_id;
    int32_t alignment;
    int64_t bytes;
    int8_t  vol_type;
    int8_t  padding1;
    int16_t name_len;
    int8_t  padding2[4];
    char    name[UBI_MAX_VOLUME_NAME + 1];
} __attribute__ ((packed));

struct ubi_info
{
    int dev_count;
    int lowest_dev_num;
    int highest_dev_num;
    int version;
};

int ubi_attach_volume(int mtd_num);
int ubi_deatch_volume(int mtd_num);
int ubi_make_volume  (int mtd_num);
int ubi_clear_volume (char *location, long long fs_size);
int mtd_num2ubi_dev( int mtd_num, int *dev_num);

#ifdef __cplusplus
}
#endif

#endif /*UBIUTILS_H_INCLUDED*/

