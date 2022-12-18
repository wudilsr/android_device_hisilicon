#include <sys/mount.h> /* BLKGETSIZE64 */
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <limits.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/reboot.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
extern "C" {
#include "uuid.h"
}
static void *volume_id_get_buffer(struct volume_id *id, uint64_t off, size_t len);

static void volume_id_set_uuid(struct volume_id *id, const uint8_t *buf, enum uuid_format format)
{
    dbg("set_uuid");
    unsigned i;
    unsigned count = 0;

    switch (format) {
    case UUID_DOS:
        count = 4;
        break;
    case UUID_NTFS:
    case UUID_HFS:
        count = 8;
        break;
    case UUID_DCE:
        count = 16;
        break;
    case UUID_DCE_STRING:
        /* 36 is ok, id->uuid has one extra byte for NUL */
        count = VOLUME_ID_UUID_SIZE;
        break;
    }
    for (i = 0; i < count; i++)
        if (buf[i] != 0)
            goto set;
    return; /* all bytes are zero, leave it empty ("") */

set:
    dbg("set_uuid");
    switch (format) {
    case UUID_DOS:
        sprintf(id->uuid, "%02X%02X-%02X%02X",
            buf[3], buf[2], buf[1], buf[0]);
        break;
    case UUID_NTFS:
        sprintf(id->uuid, "%02X%02X%02X%02X%02X%02X%02X%02X",
            buf[7], buf[6], buf[5], buf[4],
            buf[3], buf[2], buf[1], buf[0]);
        break;
    case UUID_HFS:
        sprintf(id->uuid, "%02X%02X%02X%02X%02X%02X%02X%02X",
            buf[0], buf[1], buf[2], buf[3],
            buf[4], buf[5], buf[6], buf[7]);
        break;
    case UUID_DCE:
        sprintf(id->uuid,
            "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
            buf[0], buf[1], buf[2], buf[3],
            buf[4], buf[5],
            buf[6], buf[7],
            buf[8], buf[9],
            buf[10], buf[11], buf[12], buf[13], buf[14], buf[15]);
        break;
    case UUID_DCE_STRING:
        memcpy(id->uuid, buf, count);
    dbg("set_uuid=%s",id->uuid);
        id->uuid[count] = '\0';
        break;
    }
}


static uint8_t *get_attr_volume_id(struct vfat_dir_entry *dir, int count)
{
    for (;--count >= 0; dir++) {
        /* end marker */
        if (dir->name[0] == 0x00) {
            dbg("end of dir");
            break;
        }

        /* empty entry */
        if (dir->name[0] == FAT_ENTRY_FREE)
            continue;

        /* long name */
        if ((dir->attr & FAT_ATTR_MASK) == FAT_ATTR_LONG_NAME)
            continue;

        if ((dir->attr & (FAT_ATTR_VOLUME_ID | FAT_ATTR_DIR)) == FAT_ATTR_VOLUME_ID) {
            /* labels do not have file data */
            if (dir->cluster_high != 0 || dir->cluster_low != 0)
                continue;

            dbg("found ATTR_VOLUME_ID id in root dir");
            return dir->name;
        }

        dbg("skip dir entry");
    }

    return NULL;
}

struct ext2_super_block {
    uint32_t    inodes_count;
    uint32_t    blocks_count;
    uint32_t    r_blocks_count;
    uint32_t    free_blocks_count;
    uint32_t    free_inodes_count;
    uint32_t    first_data_block;
    uint32_t    log_block_size;
    uint32_t    dummy3[7];
    uint8_t     magic[2];
    uint16_t    state;
    uint32_t    dummy5[8];
    uint32_t    feature_compat;
    uint32_t    feature_incompat;
    uint32_t    feature_ro_compat;
    uint8_t     uuid[16];
    uint8_t     volume_name[16];
} PACKED;

#define EXT3_FEATURE_COMPAT_HAS_JOURNAL     0x00000004
#define EXT3_FEATURE_INCOMPAT_JOURNAL_DEV   0x00000008
#define EXT_SUPERBLOCK_OFFSET               0x400

static int volume_id_probe_ext(struct volume_id *id /*,uint64_t off*/)
{
    uint64_t off = 0;
    struct ext2_super_block *es;

    dbg("ext: probing at offset 0x%llx", (unsigned long long) off);

    es = (struct ext2_super_block *)volume_id_get_buffer(id, off + EXT_SUPERBLOCK_OFFSET, 0x200);
    if (es == NULL)
        return -1;

    if (es->magic[0] != 0123 || es->magic[1] != 0357) {
        dbg("ext: no magic found");
        return -1;
    }

    //volume_id_set_label_string(id, es->volume_name, 16);
    volume_id_set_uuid(id, es->uuid, UUID_DCE);

#if ENABLE_FEATURE_BLKID_TYPE
    if ((le32_to_cpu(es->feature_compat) & EXT3_FEATURE_COMPAT_HAS_JOURNAL) != 0)
        id->type = "ext3";
    else
        id->type = "ext2";
#endif

    return 0;
}

static int volume_id_probe_vfat(struct volume_id *id /*,uint64_t fat_partition_off*/)
{
#define fat_partition_off ((uint64_t)0)
    struct vfat_super_block *vs;
    struct vfat_dir_entry *dir;
    uint16_t sector_size_bytes;
    uint16_t dir_entries;
    uint32_t sect_count;
    uint16_t reserved_sct;
    uint32_t fat_size_sct;
    uint32_t root_cluster;
    uint32_t dir_size_sct;
    uint32_t cluster_count;
    uint64_t root_start_off;
    uint32_t start_data_sct;
    uint8_t *buf;
    uint32_t buf_size;
    uint8_t *label = NULL;
    uint32_t next_cluster;
    int maxloop;

    dbg("probing at offset 0x%llx", (unsigned long long) fat_partition_off);

    vs = (struct vfat_super_block *)volume_id_get_buffer(id, fat_partition_off, 0x200);
    if (vs == NULL)
        return -1;


    /* believe only that's fat, don't trust the version
     * the cluster_count will tell us
     */
    if (memcmp(vs->sysid, "NTFS", 4) == 0)
        return -1;

    if (memcmp(vs->type.fat32.magic, "MSWIN", 5) == 0)
        goto valid;

    if (memcmp(vs->type.fat32.magic, "FAT32   ", 8) == 0)
        goto valid;

    if (memcmp(vs->type.fat.magic, "FAT16   ", 8) == 0)
        goto valid;

    if (memcmp(vs->type.fat.magic, "MSDOS", 5) == 0)
        goto valid;

    if (memcmp(vs->type.fat.magic, "FAT12   ", 8) == 0)
        goto valid;

    /*
     * There are old floppies out there without a magic, so we check
     * for well known values and guess if it's a fat volume
     */

    /* boot jump address check */
    if ((vs->boot_jump[0] != 0xeb || vs->boot_jump[2] != 0x90) &&
         vs->boot_jump[0] != 0xe9)
        return -1;

    /* heads check */
    if (vs->heads == 0)
        return -1;

    /* cluster size check */
    if (vs->sectors_per_cluster == 0 ||
        (vs->sectors_per_cluster & (vs->sectors_per_cluster-1)))
        return -1;

    /* media check */
    if (vs->media < 0xf8 && vs->media != 0xf0)
        return -1;

    /* fat count*/
    if (vs->fats != 2)
        return -1;

 valid:
    /* sector size check */
    sector_size_bytes = (vs->sector_size_bytes);
    if (sector_size_bytes != 0x200 && sector_size_bytes != 0x400 &&
        sector_size_bytes != 0x800 && sector_size_bytes != 0x1000)
        return -1;

    dbg("sector_size_bytes 0x%x", sector_size_bytes);
    dbg("sectors_per_cluster 0x%x", vs->sectors_per_cluster);

    reserved_sct = (vs->reserved_sct);
    dbg("reserved_sct 0x%x", reserved_sct);

    sect_count = vs->sectors;
    if (sect_count == 0)
        sect_count = (vs->total_sect);
    dbg("sect_count 0x%x", sect_count);

    fat_size_sct = (vs->fat_length);
    if (fat_size_sct == 0)
        fat_size_sct = (vs->type.fat32.fat32_length);
    fat_size_sct *= vs->fats;
    dbg("fat_size_sct 0x%x", fat_size_sct);

    dir_entries = (vs->dir_entries);
    dir_size_sct = ((dir_entries * sizeof(struct vfat_dir_entry)) +
            (sector_size_bytes-1)) / sector_size_bytes;
    dbg("dir_size_sct 0x%x", dir_size_sct);

    cluster_count = sect_count - (reserved_sct + fat_size_sct + dir_size_sct);
    cluster_count /= vs->sectors_per_cluster;
    dbg("cluster_count 0x%x", cluster_count);

    //if (cluster_count < FAT12_MAX) {
    //    strcpy(id->type_version, "FAT12");
    //} else if (cluster_count < FAT16_MAX) {
    //    strcpy(id->type_version, "FAT16");
    //} else {
    //    strcpy(id->type_version, "FAT32");
    //    goto fat32;
    //}
    if (cluster_count >= FAT16_MAX)
        goto fat32;

    /* the label may be an attribute in the root directory */
    root_start_off = (reserved_sct + fat_size_sct) * sector_size_bytes;
    dbg("root dir start 0x%llx", (unsigned long long) root_start_off);
    dbg("expected entries 0x%x", dir_entries);

    buf_size = dir_entries * sizeof(struct vfat_dir_entry);
    buf = (uint8_t *)volume_id_get_buffer(id, fat_partition_off + root_start_off, buf_size);
    if (buf == NULL)
        goto ret;

    label = get_attr_volume_id((struct vfat_dir_entry*) buf, dir_entries);

    vs = (struct vfat_super_block *)volume_id_get_buffer(id, fat_partition_off, 0x200);
    if (vs == NULL)
        return -1;

    if (label != NULL && memcmp(label, "NO NAME    ", 11) != 0) {
        //volume_id_set_label_raw(id, label, 11);
        //volume_id_set_label_string(id, label, 11);
    } else if (memcmp(vs->type.fat.label, "NO NAME    ", 11) != 0) {
        //volume_id_set_label_raw(id, vs->type.fat.label, 11);
        //volume_id_set_label_string(id, vs->type.fat.label, 11);
    }
    volume_id_set_uuid(id, vs->type.fat.serno, UUID_DOS);
    goto ret;

 fat32:
    /* FAT32 root dir is a cluster chain like any other directory */
    buf_size = vs->sectors_per_cluster * sector_size_bytes;
    root_cluster = (vs->type.fat32.root_cluster);
    start_data_sct = reserved_sct + fat_size_sct;

    next_cluster = root_cluster;
    maxloop = 100;
    while (--maxloop) {
        uint64_t next_off_sct;
        uint64_t next_off;
        uint64_t fat_entry_off;
        int count;

        dbg("next_cluster 0x%x", (unsigned)next_cluster);
        next_off_sct = (uint64_t)(next_cluster - 2) * vs->sectors_per_cluster;
        next_off = (start_data_sct + next_off_sct) * sector_size_bytes;
        dbg("cluster offset 0x%llx", (unsigned long long) next_off);

        /* get cluster */
        buf = (uint8_t *)volume_id_get_buffer(id, fat_partition_off + next_off, buf_size);
        if (buf == NULL)
            goto ret;

        dir = (struct vfat_dir_entry*) buf;
        count = buf_size / sizeof(struct vfat_dir_entry);
        dbg("expected entries 0x%x", count);

        label = get_attr_volume_id(dir, count);
        if (label)
            break;

        /* get FAT entry */
        fat_entry_off = (reserved_sct * sector_size_bytes) + (next_cluster * sizeof(uint32_t));
        dbg("fat_entry_off 0x%llx", (unsigned long long)fat_entry_off);
        buf = (uint8_t *)volume_id_get_buffer(id, fat_partition_off + fat_entry_off, buf_size);
        if (buf == NULL)
            goto ret;

        /* set next cluster */
        next_cluster = (*(uint32_t*)buf) & 0x0fffffff;
        if (next_cluster < 2 || next_cluster > FAT32_MAX)
            break;
    }
    if (maxloop == 0) {
        dbg("reached maximum follow count of root cluster chain, give up");
    }

    vs = (struct vfat_super_block *)volume_id_get_buffer(id, fat_partition_off, 0x200);
    if (vs == NULL)
        return -1;

    if (label != NULL && memcmp(label, "NO NAME    ", 11) != 0) {
        //volume_id_set_label_raw(id, label, 11);
        //volume_id_set_label_string(id, label, 11);
    } else if (memcmp(vs->type.fat32.label, "NO NAME    ", 11) != 0) {
        //volume_id_set_label_raw(id, vs->type.fat32.label, 11);
        //volume_id_set_label_string(id, vs->type.fat32.label, 11);
    }
    volume_id_set_uuid(id, vs->type.fat32.serno, UUID_DOS);

 ret:
    //volume_id_set_usage(id, VOLUME_ID_FILESYSTEM);
    //id->type = "vfat";

    return 0;
}

static int volume_id_probe_linux_raid(struct volume_id *id /*,uint64_t off*/, uint64_t size)
{
    uint64_t off = 0;
    uint64_t sboff;
    uint8_t uuid[16];
    struct mdp_super_block *mdp;

    dbg("probing at offset 0x%llx, size 0x%llx",
            (unsigned long long) off, (unsigned long long) size);

    if (size < 0x10000)
        return -1;

    sboff = (size & ~(MD_RESERVED_BYTES - 1)) - MD_RESERVED_BYTES;
    mdp = (struct mdp_super_block *)volume_id_get_buffer(id, off + sboff, 0x800);
    if (mdp == NULL)
        return -1;
    if (mdp->md_magic != MD_MAGIC)
        return -1;

    *(uint32_t*)uuid = mdp->set_uuid0;
    memcpy(&uuid[4], &mdp->set_uuid1, 12);
    volume_id_set_uuid(id, uuid, UUID_DCE);

    return 0;
}

static void volume_id_set_unicode16(char *str, size_t len, const uint8_t *buf, enum endian endianess, size_t count)
{
    unsigned i, j;
    unsigned c;

    j = 0;
    for (i = 0; i + 2 <= count; i += 2) {
        if (endianess == LE)
            c = (buf[i+1] << 8) | buf[i];
        else
            c = (buf[i] << 8) | buf[i+1];
        if (c == 0) {
            str[j] = '\0';
            break;
        } else if (c < 0x80) {
            if (j+1 >= len)
                break;
            str[j++] = (uint8_t) c;
        } else if (c < 0x800) {
            if (j+2 >= len)
                break;
            str[j++] = (uint8_t) (0xc0 | (c >> 6));
            str[j++] = (uint8_t) (0x80 | (c & 0x3f));
        } else {
            if (j+3 >= len)
                break;
            str[j++] = (uint8_t) (0xe0 | (c >> 12));
            str[j++] = (uint8_t) (0x80 | ((c >> 6) & 0x3f));
            str[j++] = (uint8_t) (0x80 | (c & 0x3f));
        }
    }
    str[j] = '\0';
}

static void volume_id_set_label_unicode16(struct volume_id *id, const uint8_t *buf, enum endian endianess, size_t count)
{
    volume_id_set_unicode16(id->label, sizeof(id->label), buf, endianess, count);
}

static int volume_id_probe_ntfs(struct volume_id *id )
{
#define OFF_I ((uint64_t)0)
    unsigned sector_size;
    unsigned cluster_size;
    uint64_t mft_cluster;
    uint64_t mft_off;
    unsigned mft_record_size;
    unsigned attr_type;
    unsigned attr_off;
    unsigned attr_len;
    unsigned val_off;
    unsigned val_len;
    struct master_file_table_record *mftr;
    struct ntfs_super_block *ns;
    const uint8_t *buf;
    const uint8_t *val;

    dbg("probing at offset 0x%llx", (unsigned long long) OFF_I);

    ns = (struct ntfs_super_block *)volume_id_get_buffer(id, OFF_I, 0x200);
    if (ns == NULL)
        return -1;

    if (memcmp(ns->oem_id, "NTFS", 4) != 0)
        return -1;

    volume_id_set_uuid(id, ns->volume_serial, UUID_NTFS);

    sector_size = (ns->bytes_per_sector);
    cluster_size = ns->sectors_per_cluster * sector_size;
    mft_cluster = (ns->mft_cluster_location);
    mft_off = mft_cluster * cluster_size;

    if (ns->cluster_per_mft_record < 0)
        mft_record_size = 1 << -ns->cluster_per_mft_record;
    else
        mft_record_size = ns->cluster_per_mft_record * cluster_size;
    dbg("sectorsize  0x%x", sector_size);
    dbg("clustersize 0x%x", cluster_size);
    dbg("mftcluster  %llu", (unsigned long long) mft_cluster);
    dbg("mftoffset  0x%llx", (unsigned long long) mft_off);
    dbg("cluster per mft_record  %i", ns->cluster_per_mft_record);
    dbg("mft record size  %i", mft_record_size);

    buf = (uint8_t *)volume_id_get_buffer(id, OFF_I + mft_off + (MFT_RECORD_VOLUME * mft_record_size), mft_record_size);
    if (buf == NULL)
        goto found;

    mftr = (struct master_file_table_record*) buf;

    dbg("mftr->magic '%c%c%c%c'", mftr->magic[0], mftr->magic[1], mftr->magic[2], mftr->magic[3]);
    if (memcmp(mftr->magic, "FILE", 4) != 0)
        goto found;

    attr_off = (mftr->attrs_offset);
    dbg("file $Volume's attributes are at offset %i", attr_off);

    while (1) {
        struct file_attribute *attr;

        attr = (struct file_attribute*) &buf[attr_off];
        attr_type = (attr->type);
        attr_len = (attr->len);
        val_off = (attr->value_offset);
        val_len = (attr->value_len);
        attr_off += attr_len;

        if (attr_len == 0)
            break;

        if (attr_off >= mft_record_size)
            break;

        if (attr_type == MFT_RECORD_ATTR_END)
            break;

        dbg("found attribute type 0x%x, len %i, at offset %i",
                attr_type, attr_len, attr_off);

        if (attr_type == MFT_RECORD_ATTR_VOLUME_NAME) {
            dbg("found label, len %i", val_len);
            if (val_len > VOLUME_ID_LABEL_SIZE)
                val_len = VOLUME_ID_LABEL_SIZE;

            val = ((uint8_t *) attr) + val_off;
            volume_id_set_label_unicode16(id, val, LE, val_len);
        }
    }
found:

    return 0;
}

static ssize_t safe_read(int fd, void *buf, size_t count)
{
    ssize_t n;

    do {
        n = read(fd, buf, count);
    } while (n < 0 && errno == EINTR);

    return n;
}

static ssize_t full_read(int fd, void *buf, size_t len)
{
    ssize_t cc;
    ssize_t total;

    total = 0;

    while (len) {
        cc = safe_read(fd, buf, len);

        if (cc < 0) {
            if (total) {
                /* we already have some! */
                /* user can do another read to know the error code */
                return total;
            }
            return cc; /* read() returns -1 on failure. */
        }
        if (cc == 0)
            break;
        buf = ((char *)buf) + cc;
        total += cc;
        len -= cc;
    }

    return total;
}

static void volume_id_free_buffer(struct volume_id *id)
{
    free(id->sbbuf);
    id->sbbuf = NULL;
    id->sbbuf_len = 0;
    free(id->seekbuf);
    id->seekbuf = NULL;
    id->seekbuf_len = 0;
    id->seekbuf_off = 0;
}

static void *volume_id_get_buffer(struct volume_id *id, uint64_t off, size_t len)
{
    uint8_t *dst;
    unsigned small_off;
    ssize_t read_len;

    dbg("get buffer off 0x%llx(%llu), len 0x%zx",
        (unsigned long long) off, (unsigned long long) off, len);

    /* check if requested area fits in superblock buffer */
    if (off + len <= SB_BUFFER_SIZE    ) {
        if (id->sbbuf == NULL) {
            id->sbbuf = (uint8_t *)malloc(SB_BUFFER_SIZE);
        }
        small_off = off;
        dst = id->sbbuf;

        /* check if we need to read */
        len += off;
        if (len <= id->sbbuf_len)
            goto ret; /* we already have it */

        dbg("read sbbuf len:0x%x", (unsigned) len);
        id->sbbuf_len = len;
        off = 0;
        goto do_read;
    }

    if (len > SEEK_BUFFER_SIZE) {
        dbg("seek buffer too small %d", SEEK_BUFFER_SIZE);
        return NULL;
    }
    dst = id->seekbuf;

    /* check if we need to read */
    if ((off >= id->seekbuf_off)
     && ((off + len) <= (id->seekbuf_off + id->seekbuf_len))
    ) {
        small_off = off - id->seekbuf_off; /* can't overflow */
        goto ret; /* we already have it */
    }

    id->seekbuf_off = off;
    id->seekbuf_len = len;
    id->seekbuf = (uint8_t *)realloc(id->seekbuf, len);
    small_off = 0;
    dst = id->seekbuf;
    dbg("read seekbuf off:0x%llx len:0x%zx",
                (unsigned long long) off, len);
 do_read:
    if (lseek(id->fd, off, SEEK_SET) != (long)off) {
        dbg("seek(0x%llx) failed", (unsigned long long) off);
        //goto err;
    }
    dbg("seek return %x", lseek(id->fd, off, SEEK_SET));
    read_len = full_read(id->fd, dst, len);
    //dbg(dst);
    if ((unsigned )read_len != len) {
        dbg("requested 0x%x bytes, got 0x%x bytes",
                (unsigned) len, (unsigned) read_len);
 err:
        if (off < 64*1024)
            id->error = 1;
        volume_id_free_buffer(id);
        return NULL;
    }
ret:
    return dst + small_off;
}

static char* last_char_is(const char *s, int c)
{
    if (s && *s) {
        size_t sz = strlen(s) - 1;
        s += sz;
        if ( (unsigned char)*s == c)
            return (char*)s;
    }
    return NULL;
}


static char* concat_path_file(const char *path, const char *filename)
{
    char *lc;
    char *buf;
    buf=(char *)malloc(100);
    memset(buf,0,100);
    if (!path)
        path = "";
    lc = last_char_is(path, '/');
    while (*filename == '/')
        filename++;
    sprintf(buf,"%s%s%s", path, (lc==NULL ? "/" : ""), filename);
    return buf ;
}

static char* concat_subpath_file(const char *path, const char *f)
{
    if (f && DOT_OR_DOTDOT(f))
        return NULL;
    return concat_path_file(path, f);
}

static int Action_null(const char *fileName, struct stat *statbuf, void* userData, int depth)
{
    return 1;
}

static int recursive_action(const char *fileName,
        unsigned flags,
        int (*fileAction)(const char *fileName, struct stat *statbuf, void* userData, int depth),
        int (*dirAction)(const char *fileName, struct stat *statbuf, void* userData, int depth),
        void* userData,
        unsigned depth)
{
    struct stat statbuf;
    unsigned follow;
    int status;
    DIR *dir;
    struct dirent *next;

    if (!fileAction) fileAction = Action_null;
    if (!dirAction) dirAction = Action_null;

    follow = ACTION_FOLLOWLINKS;
    if (depth == 0)
        follow = ACTION_FOLLOWLINKS | ACTION_FOLLOWLINKS_L0;
    follow &= flags;
    status = (follow ? stat : lstat)(fileName, &statbuf);
    if (status < 0) {
        dbg("status=%d flags=%x", status, flags);
        if ((flags & ACTION_DANGLING_OK)
         && errno == ENOENT
         && lstat(fileName, &statbuf) == 0
        ) {
            /* Dangling link */
            return fileAction(fileName, &statbuf, userData, depth);
        }
        goto done_nak_warn;
    }

    /* If S_ISLNK(m), then we know that !S_ISDIR(m).
     * Then we can skip checking first part: if it is true, then
     * (!dir) is also true! */
    if ( /* (!(flags & ACTION_FOLLOWLINKS) && S_ISLNK(statbuf.st_mode)) || */
     !S_ISDIR(statbuf.st_mode)
    ) {
        return fileAction(fileName, &statbuf, userData, depth);
    }

    /* It's a directory (or a link to one, and followLinks is set) */

    if (!(flags & ACTION_RECURSE)) {
        return dirAction(fileName, &statbuf, userData, depth);
    }

    if (!(flags & ACTION_DEPTHFIRST)) {
        status = dirAction(fileName, &statbuf, userData, depth);
        if (!status)
            goto done_nak_warn;
        if (status == SKIP)
            return TRUE;
    }

    dir = opendir(fileName);
    if (!dir) {
        goto done_nak_warn;
    }
    status = TRUE;
    while ((next = readdir(dir)) != NULL) {
        char *nextFile;

        nextFile = concat_subpath_file(fileName, next->d_name);
        if (nextFile == NULL)
            continue;
        if (!recursive_action(nextFile, flags, fileAction, dirAction,
                        userData, depth + 1))
            status = FALSE;
        free(nextFile);
    }
    closedir(dir);

    if (flags & ACTION_DEPTHFIRST) {
        if (!dirAction(fileName, &statbuf, userData, depth))
            goto done_nak_warn;
    }

    return status;

 done_nak_warn:
    if (!(flags & ACTION_QUIET))
        printf("\nerror filename =%s\n",fileName);
    return FALSE;
}


/* open volume by device node */
static struct volume_id* volume_id_open_node(int fd)
{
    struct volume_id *id;

    id = (volume_id *)malloc(sizeof(struct volume_id));
    memset(id,0,sizeof(struct volume_id));
    id->fd = fd;
    ///* close fd on device close */
    //id->fd_close = 1;
    return id;
}
static void free_volume_id(struct volume_id *id)
{
    if (id == NULL)
        return;

    //if (id->fd_close != 0) - always true
    close(id->fd);
    volume_id_free_buffer(id);
#ifdef UNUSED_PARTITION_CODE
    free(id->partitions);
#endif
    free(id);
}

/* Returns !0 on error.
 * Otherwise, returns malloc'ed strings for label and uuid
 * (and they can't be NULL, although they can be "").
 * NB: closes fd. */
static int
get_label_uuid(int fd, char **label, char **uuid)
{
    int rv = 1;
    uint64_t size;
    //unsigned long long int size;
    struct volume_id *vid;

    /* fd is owned by vid now */
    vid = volume_id_open_node(fd);

    if (ioctl(/*vid->*/fd, BLKGETSIZE64, &size) != 0)
        size = 0;
    //size = 0x250 ;
    dbg("size=%llx",size);

    if (volume_id_probe_vfat(vid)) {
        if (volume_id_probe_ntfs(vid)) {
            volume_id_probe_ext(vid);
        }
    }
    volume_id_get_buffer(vid, 0, SB_BUFFER_SIZE);
    //goto ret;

    if (vid->label[0] != '\0' || vid->uuid[0] != '\0') {
        dbg("get uuid");
        *label = strndup(vid->label, sizeof(vid->label));
        *uuid  = strndup(vid->uuid, sizeof(vid->uuid));
        dbg("found label '%s', uuid '%s'", *label, *uuid);
        rv = 0;
    }
 ret:
    free_volume_id(vid); /* also closes fd */
    return rv;
}

/* NB: we take ownership of (malloc'ed) label and uuid */
static void
uuidcache_addentry(char *device, /*int major, int minor,*/ char *label, char *uuid)
{
    struct uuidCache_s *last;

    if (!uuidCache) {
        last = uuidCache = (uuidCache_s *)malloc(sizeof(*uuidCache));
        memset(last,0,sizeof(*uuidCache));
    } else {
        for (last = uuidCache; last->next; last = last->next)
            continue;
        last->next = (uuidCache_s *)malloc(sizeof(*uuidCache));
        memset(last->next,0,sizeof(*uuidCache));
        last = last->next;
    }
    /*last->next = NULL; - xzalloc did it*/
    //last->major = major;
    //last->minor = minor;
    last->device = device;
    last->label = label;
    last->uc_uuid = uuid;
}

/* If get_label_uuid() on device_name returns success,
 * add a cache entry for this device.
 * If device node does not exist, it will be temporarily created. */
static int
uuidcache_check_device(const char *device,
        struct stat *statbuf,
        void *userData UNUSED_PARAM,
        int depth UNUSED_PARAM)
{
    char *uuid ; /* for compiler */
    char *label ;
    int fd;

    /* note: this check rejects links to devices, among other nodes */
    if (!S_ISBLK(statbuf->st_mode))
        return 1;

    if (major(statbuf->st_rdev) == 2)
        return 1;
    //if(strcmp(device, "/dev/block/sda")&& strcmp(device, "/dev/block/sda1")) return 1;
    dbg(device);
    fd = open(device, O_RDONLY);
    if (fd < 0)
        return 1;

    /* get_label_uuid() closes fd in all cases (success & failure) */
    if (get_label_uuid(fd, &label, &uuid) == 0) {
        /* uuidcache_addentry() takes ownership of all three params */
        uuidcache_addentry(strdup(device), /*ma, mi,*/ label, uuid);
    }
    return 1;
}

static void
uuidcache_init(void)
{
    recursive_action("/dev/block", ACTION_RECURSE,
        uuidcache_check_device, /* file_action */
        NULL, /* dir_action */
        NULL, /* userData */
        0 /* depth */);
}

static char *get_devname_from_label(const char *spec)
{
    struct uuidCache_s *uc;

    uuidcache_init();
    uc = uuidCache;
    while (uc) {
        if (uc->label[0] && strcmp(spec, uc->label) == 0) {
            return strdup(uc->device);
        }
        uc = uc->next;
    }
    return NULL;
}

char *get_devname_from_uuid(const char *spec)
{
    struct uuidCache_s *uc;
    uuidcache_init();
    uc = uuidCache;
    while (uc) {
        printf("uuid=%s,device=%s\n",uc->uc_uuid,uc->device);
        dbg("spec=%s",spec);
        if (strcasecmp(spec, uc->uc_uuid) == 0) {
            return strdup(uc->device);
        }
        uc = uc->next;
    }
    return NULL;
}
