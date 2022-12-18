#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <utils/Log.h>
#include <sys/stat.h>
#include "mtdutils.h"
#include <sys/reboot.h>

#define MISC_OFFSET         0
#define MAX_BOOTARGS_LEN    1024


static const int MISC_PAGES = 3;         // number of pages to save
static const int MISC_COMMAND_PAGE = 1;  // bootloader command is this page

void usage()
{
    printf("usage: write_raw partition_name rawdatafile or clean \n"
            "      for example : \n"
            "      writ_raw recovery /mnt/sdcard/recovery.img\n"
            "      writ_raw recovery clean\n"
            );
    ALOGE("usage: write_raw partition_name rawdatafile or clean\n"
            "      for example : \n"
            "      writ_raw recovery /mnt/sdcard/recovery.img\n"
            "      writ_raw recovery clean\n"
            );

}

static unsigned long get_size(const char * filename)
{
    struct stat statbuf;

    stat(filename, &statbuf);

    return statbuf.st_size;
}
int write_emmc_clean(const char* partition) {

    char partition_path[1024];
    memset(partition_path,0,sizeof(partition_path));
    sprintf(partition_path,"/dev/block/platform/hi_mci.1/by-name/%s",partition);
    FILE* fw = fopen(partition_path, "wb");
    if (fw == NULL) {
        printf("can't fopen %s: %s", partition_path,strerror(errno));
        ALOGE("can't fopen %s: %s", partition_path,strerror(errno));
        return -1;
    }
    int fw_fd = fileno(fw);

    unsigned char readbuf[32*1024];
    unsigned long  nFileSize = 1;
    ssize_t n = 0;
    while (n != -1) {
        memset(readbuf,0xff,sizeof(readbuf));
        n = write(fw_fd,readbuf,sizeof(readbuf));
    }
    fclose(fw);
    return 0;
}

int write_emmc_raw(const char* partition, const char* filename) {

    char partition_path[1024];
    memset(partition_path,0,sizeof(partition_path));
    sprintf(partition_path,"/dev/block/platform/hi_mci.1/by-name/%s",partition);
    FILE* fw = fopen(partition_path, "wb");
    if (fw == NULL) {
        printf("can't fopen %s: %s", partition_path,strerror(errno));
        ALOGE("can't fopen %s: %s", partition_path,strerror(errno));
        return -1;
    }
    int fw_fd = fileno(fw);

    FILE* fr = fopen(filename, "rb");
    if (fr == NULL) {
        printf("can't fopen %s: %s", filename,strerror(errno));
        ALOGE("can't fopen %s: %s", filename,strerror(errno));
        fclose(fw);
        return -1;
    }
    int fr_fd = fileno(fr);

    unsigned char readbuf[32 * 1024];

    unsigned long  nFileSize = 0;
    nFileSize = get_size(filename);
    unsigned long count = 0;

    ALOGE("write %s to %s ,datalen = 0x%lx\n",filename,partition_path,nFileSize);
    printf("write %s to %s ,datalen = 0x%lx\n",filename,partition_path,nFileSize);

    while (nFileSize != 0) {

        count = nFileSize ;
        if (count > sizeof(readbuf)) {
            count = sizeof(readbuf);
        }

        memset(readbuf,0,sizeof(readbuf));

        read(fr_fd,readbuf,count);

        ssize_t n = write(fw_fd,readbuf,count);
        if ( n != count) {
            ALOGE("wirte error %s n = %ld count = %ld\n",filename,n,count);
            printf("wirte error %s n = %ld count = %ld\n",filename,n,count);
            fclose(fr);
            fclose(fw);
            return -1;
        }

        nFileSize = nFileSize - count;
    }
    fclose(fw);
    fclose(fr);
    sync();

    return 0;
}
int write_spi_nand_clean(const char* partition) {

    mtd_scan_partitions();

    const MtdPartition* mtd = mtd_find_partition_by_name(partition);
    if (mtd == NULL) {
        printf("not find the %s\n",partition);
        ALOGE("not find the %s\n",partition);
        return -1;
    }

    MtdWriteContext* ctx = mtd_write_partition(mtd);
    if (ctx == NULL) {
        ALOGE("can't write %s", partition);
        return -1;
    }

    if (mtd_erase_blocks(ctx, -1) == -1) {
        printf("error erasing blocks of %s\n", partition);
        ALOGE("error erasing blocks of %s\n", partition);
        return -1;
    }

    if (mtd_write_close(ctx) != 0) {
        printf("%s: error closing write of %s\n",partition);
        ALOGE("%s: error closing write of %s\n",partition);
        return -1;
    }

    return 0;
}
int write_spi_nand_raw(const char* partition, const char* filename) {

    mtd_scan_partitions();

    const MtdPartition* mtd = mtd_find_partition_by_name(partition);
    if (mtd == NULL) {
        printf("not find the %s\n",partition);
        ALOGE("not find the %s\n",partition);
        return -1;
    }

    MtdWriteContext* ctx = mtd_write_partition(mtd);
    if (ctx == NULL) {
        ALOGE("can't write %s", partition);
        return -1;
    }

    struct mtd_info_user mtd_info;
    unsigned int nand_write_size;
    GetMtdInfo((int)(ctx->fd), &mtd_info);
    nand_write_size = mtd_info.writesize;

    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        printf("can't fopen %s: %s", filename,strerror(errno));
        ALOGE("can't fopen %s: %s", filename,strerror(errno));
        return -1;
    }

    int success = 1;
    char* buffer = malloc(nand_write_size);
    int read;
    while (success && (read = fread(buffer, 1, nand_write_size, f)) > 0) {
        int wrote = mtd_write_data(ctx, buffer, read);
        success = success && (wrote == read);
    }
    free(buffer);
    fclose(f);

    if (!success) {
        printf(" %s mtd_write_data to %s failed:\n",
                filename, partition);

        ALOGE(" %s mtd_write_data to %s failed:\n",
                filename, partition);
    }

    if (mtd_erase_blocks(ctx, -1) == -1) {
        printf("%s: error erasing blocks of %s\n", filename, partition);
        ALOGE("%s: error erasing blocks of %s\n", filename, partition);
    }

    if (mtd_write_close(ctx) != 0) {
        printf("%s: error closing write of %s\n", filename, partition);
        ALOGE("%s: error closing write of %s\n", filename, partition);
    }

    return 0;
}

enum {
    NAND_TYPE,
    EMMC_TYPE,
    NULL_TYPE
};
static int check_flash_type()
{
    int ret = NULL_TYPE;
    char buffer[1024];
    FILE *fp;

    fp = fopen("/proc/cmdline","r");
    if (fp !=NULL ) {
        if (fgets(buffer,1024,fp) != NULL) {
            if (strstr(buffer,"hinand")) {
                ret = NAND_TYPE;
            } else if (strstr(buffer,"mmcblk")) {
                ret = EMMC_TYPE;
            } else {
                ALOGE("error!!, Can't get Flash Type in Cmdline %s\n",buffer);
            }
        }
        fclose(fp);
    }
    return ret;
}
static int resume_factory( const char *flag)
{
    struct bootloader_message boot;
    memset(&boot, 0, sizeof(boot));
    strlcpy(boot.command, "boot-recovery", sizeof(boot.command));
    strlcpy(boot.recovery, "recovery\n", sizeof(boot.recovery));
    if (check_flash_type() == NAND_TYPE ) {
        size_t write_size;
        mtd_scan_partitions();
        const MtdPartition *part = mtd_find_partition_by_name("misc");
        if (part == NULL || mtd_partition_info(part, NULL, NULL, &write_size)) {
            ALOGE("Can't find %s\n", "misc");
            return -1;
        }

        MtdReadContext *read = mtd_read_partition(part);
        if (read == NULL) {
            ALOGE("Can't open %s\n(%s)\n", "misc", strerror(errno));
            return -1;
        }

        ssize_t size = write_size * MISC_PAGES;
        char data[size];
        ssize_t r = mtd_read_data(read, data, size);
        if (r != size) ALOGE("Can't read %s\n(%s)\n", "misc", strerror(errno));
        mtd_read_close(read);
        if (r != size) return -1;

        memcpy(&data[write_size * MISC_COMMAND_PAGE], &boot, sizeof(boot));

        MtdWriteContext *write = mtd_write_partition(part);
        if (write == NULL) {
            ALOGE("Can't open %s\n(%s)\n", "misc", strerror(errno));
            return -1;
        }
        if (mtd_write_data(write, data, size) != size) {
            ALOGE("Can't write %s\n(%s)\n", "misc", strerror(errno));
            mtd_write_close(write);
            return -1;
        }
        if (mtd_write_close(write)) {
            ALOGE("Can't finish %s\n(%s)\n", "misc", strerror(errno));
            return -1;
        }

    } else if (check_flash_type() == EMMC_TYPE ) {
        const char *device = "/dev/block/platform/hi_mci.1/by-name/misc";

        FILE* f = fopen(device, "wb");
        if (f == NULL) {
            ALOGE("Can't open %s\n(%s)\n", device, strerror(errno));
            return -1;
        }

        if(fseek(f, MISC_OFFSET, SEEK_SET)) {
             ALOGE("Can't lseek %lu: %s\n", MISC_OFFSET, strerror(errno));
        }

        int count = fwrite(&boot, sizeof(boot), 1, f);
        if (count != 1) {
            ALOGE("Failed writing %s\n(%s)\n", device, strerror(errno));
            return -1;
        }
        if (fclose(f) != 0) {
            ALOGE("Failed closing %s\n(%s)\n", device, strerror(errno));
            return -1;
        }
    } else {
        ALOGE("unknown flash chip type");
    }

    if (strcmp(flag,"wipe_data") == 0) {

        FILE *fp;
        fp = fopen("/cache/recovery/command","wb");

        if(fp != NULL ) {

            printf("write --wipe_data\n");
            fwrite("--wipe_data\n",sizeof("--wipe_data\n"),1,fp);
            fclose(fp);
            //--wipe_data
            //--locale=en_US
        }
    }
    sync();
    reboot(RB_AUTOBOOT);
    return 0;
}


int main(int argc, char *argv[])
{

    const char* partition = argv[1];
    const char* filename = argv[2];

    if (argc != 3) {
        usage();
        return -1;
    }

    printf("argc =%d partition =%s,filename =%s\n",argc, partition, filename);
    ALOGE("argc =%d partition =%s,filename =%s\n",argc, partition, filename);

    printf("cmd = %s, %s, %s\n",argv[0],argv[1],argv[2]);
    ALOGE("cmd = %s, %s, %s\n",argv[0],argv[1],argv[2]);

    if(strcmp(filename,"wipe_data") == 0 && strcmp(partition,"misc") == 0) {

        resume_factory("wipe_data");

    } else if(strcmp(filename,"enable") == 0 && strcmp(partition,"misc") == 0) {

        resume_factory("enable");
    }
    else {

        if (check_flash_type() == NAND_TYPE) {

            printf("nand type\n");
            ALOGE(" nand type\n");

            if(strcmp(filename,"clean") ==  0) {
                ALOGE(" clean  %s\n",partition);
                printf(" clean %s\n", partition);
                write_spi_nand_clean(partition);
            }else{
                write_spi_nand_raw(partition,filename);
            }
        }

        if (check_flash_type() ==  EMMC_TYPE) {

            printf("emmc type\n");
            ALOGE(" emmc type\n");

            if(strcmp(filename,"clean") ==  0) {
                ALOGE(" clean  %s\n",partition);
                printf(" clean %s\n", partition);
                write_emmc_clean(partition);
            } else {
                write_emmc_raw(partition,filename);
            }
        }
    }
    return 0;
}
