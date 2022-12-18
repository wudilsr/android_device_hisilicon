#ifndef     __RECOVERY_UUID_
#define     __RECOVERY_UUID_
#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64
#if !defined(BLKGETSIZE64)
# define BLKGETSIZE64 _IOR(0x12,114,size_t)
#endif
#define SB_BUFFER_SIZE                  0x11000
#define VOLUME_ID_VERSION               48
#define SEEK_BUFFER_SIZE                0x10000

#define VOLUME_ID_LABEL_SIZE            64
#define VOLUME_ID_UUID_SIZE             36
#define VOLUME_ID_FORMAT_SIZE           32
#define VOLUME_ID_PARTITIONS_MAX        256

#undef FALSE
#define FALSE   ((int) 0)
#undef TRUE
#define TRUE    ((int) 1)
#undef SKIP
#define SKIP    ((int) 2)

#define UNUSED_PARAM __attribute__ ((__unused__))
#define DOT_OR_DOTDOT(s) ((s)[0] == '.' && (!(s)[1] || ((s)[1] == '.' && !(s)[2])))
#define dbg(msg...)

#if 0
#define dbg(msg...) do{ \
    printf("%s  ->   %d       :",__FUNCTION__,__LINE__);\
    printf(msg);\
    printf("\n");\
    }while(0)
#endif

enum {
    ACTION_RECURSE        = (1 << 0),
    ACTION_FOLLOWLINKS    = (1 << 1),
    ACTION_FOLLOWLINKS_L0 = (1 << 2),
    ACTION_DEPTHFIRST     = (1 << 3),
    /*ACTION_REVERSE      = (1 << 4), - unused */
    ACTION_QUIET          = (1 << 5),
    ACTION_DANGLING_OK    = (1 << 6),
};


static struct uuidCache_s {
    struct uuidCache_s *next;
    char *device;
    char *label;
    char *uc_uuid; /* prefix makes it easier to grep for */
} *uuidCache;


struct volume_id {
    int             fd;
    int             error;
    size_t          sbbuf_len;
    size_t          seekbuf_len;
    uint8_t         *sbbuf;
    uint8_t         *seekbuf;
    uint64_t        seekbuf_off;
#ifdef UNUSED_PARTITION_CODE
    struct volume_id_partition *partitions;
    size_t          partition_count;
#endif
    char            label[VOLUME_ID_LABEL_SIZE+1];
    char            uuid[VOLUME_ID_UUID_SIZE+1];
};


#define FAT12_MAX               0xff4
#define FAT16_MAX               0xfff4
#define FAT32_MAX               0x0ffffff6

#define FAT_ATTR_VOLUME_ID      0x08
#define FAT_ATTR_DIR            0x10
#define FAT_ATTR_LONG_NAME      0x0f
#define FAT_ATTR_MASK           0x3f
#define FAT_ENTRY_FREE          0xe5

enum uuid_format {
    UUID_DCE_STRING,
    UUID_DCE,
    UUID_DOS,
    UUID_NTFS,
    UUID_HFS,
};

struct mdp_super_block {
    uint32_t    md_magic;
    uint32_t    major_version;
    uint32_t    minor_version;
    uint32_t    patch_version;
    uint32_t    gvalid_words;
    uint32_t    set_uuid0;
    uint32_t    ctime;
    uint32_t    level;
    uint32_t    size;
    uint32_t    nr_disks;
    uint32_t    raid_disks;
    uint32_t    md_minor;
    uint32_t    not_persistent;
    uint32_t    set_uuid1;
    uint32_t    set_uuid2;
    uint32_t    set_uuid3;
} ;

#define MD_RESERVED_BYTES   0x10000
#define MD_MAGIC            0xa92b4efc
struct vfat_super_block {
    uint8_t     boot_jump[3];
    uint8_t     sysid[8];
    uint16_t    sector_size_bytes;
    uint8_t     sectors_per_cluster;
    uint16_t    reserved_sct;
    uint8_t     fats;
    uint16_t    dir_entries;
    uint16_t    sectors;
    uint8_t     media;
    uint16_t    fat_length;
    uint16_t    secs_track;
    uint16_t    heads;
    uint32_t    hidden;
    uint32_t    total_sect;
    union {
        struct fat_super_block {
            uint8_t         unknown[3];
            uint8_t         serno[4];
            uint8_t         label[11];
            uint8_t         magic[8];
            uint8_t         dummy2[192];
            uint8_t         pmagic[2];
        } __attribute__     ((__packed__)) fat;
        struct fat32_super_block {
            uint32_t        fat32_length;
            uint16_t        flags;
            uint8_t        version[2];
            uint32_t        root_cluster;
            uint16_t        insfo_sector;
            uint16_t        backup_boot;
            uint16_t        reserved2[6];
            uint8_t         unknown[3];
            uint8_t         serno[4];
            uint8_t         label[11];
            uint8_t         magic[8];
            uint8_t         dummy2[164];
            uint8_t         pmagic[2];
        } __attribute__     ((__packed__)) fat32;
    } __attribute__ ((__packed__)) type;
} __attribute__ ((__packed__));

struct vfat_dir_entry {
    uint8_t     name[11];
    uint8_t     attr;
    uint16_t    time_creat;
    uint16_t    date_creat;
    uint16_t    time_acc;
    uint16_t    date_acc;
    uint16_t    cluster_high;
    uint16_t    time_write;
    uint16_t    date_write;
    uint16_t    cluster_low;
    uint32_t    size;
} ;


struct ntfs_super_block {
    uint8_t     jump[3];
    uint8_t     oem_id[8];
    uint16_t    bytes_per_sector;
    uint8_t     sectors_per_cluster;
    uint16_t    reserved_sectors;
    uint8_t     fats;
    uint16_t    root_entries;
    uint16_t    sectors;
    uint8_t     media_type;
    uint16_t    sectors_per_fat;
    uint16_t    sectors_per_track;
    uint16_t    heads;
    uint32_t    hidden_sectors;
    uint32_t    large_sectors;
    uint16_t    unused[2];
    uint64_t    number_of_sectors;
    uint64_t    mft_cluster_location;
    uint64_t    mft_mirror_cluster_location;
    int8_t      cluster_per_mft_record;
    uint8_t     reserved1[3];
    int8_t      cluster_per_index_record;
    uint8_t     reserved2[3];
    uint8_t     volume_serial[8];
    uint16_t    checksum;
} __attribute__ ((__packed__));

struct master_file_table_record {
    uint8_t     magic[4];
    uint16_t    usa_ofs;
    uint16_t    usa_count;
    uint64_t    lsn;
    uint16_t    sequence_number;
    uint16_t    link_count;
    uint16_t    attrs_offset;
    uint16_t    flags;
    uint32_t    bytes_in_use;
    uint32_t    bytes_allocated;
} __attribute__ ((__packed__));

struct file_attribute {
    uint32_t    type;
    uint32_t    len;
    uint8_t     non_resident;
    uint8_t     name_len;
    uint16_t    name_offset;
    uint16_t    flags;
    uint16_t    instance;
    uint32_t    value_len;
    uint16_t    value_offset;
} __attribute__ ((__packed__));

struct volume_info {
    uint64_t        reserved;
    uint8_t         major_ver;
    uint8_t         minor_ver;
} __attribute__     ((__packed__));

#define MFT_RECORD_VOLUME               3
#define MFT_RECORD_ATTR_VOLUME_NAME     0x60
#define MFT_RECORD_ATTR_VOLUME_INFO     0x70
#define MFT_RECORD_ATTR_OBJECT_ID       0x40
#define MFT_RECORD_ATTR_END             0xffffffffu

enum endian {
    LE = 0,
    BE = 1
};

char *get_devname_from_uuid(const char *spec);

#endif
