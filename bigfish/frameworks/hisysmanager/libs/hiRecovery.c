//#define LOG_NDEBUG 0
#include <utils/Log.h>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "mtdutils.h"

#define MISC_OFFSET         0
#define MAX_BOOTARGS_LEN    1024

static const int MISC_PAGES = 3;         // number of pages to save
static const int MISC_COMMAND_PAGE = 1;  // bootloader command is this page

static int get_bootargs(char *bootargs)
{
    FILE *fp;

    if( NULL == bootargs)
    {
        ALOGE("bootargs is null.\n");
        return -1;
    }
    if(NULL == (fp = fopen("/proc/cmdline", "r")))
    {
        ALOGE("Failed to open '/proc/cmdline'.\n");
        return -1;
    }
    if(NULL == fgets((char*)bootargs, MAX_BOOTARGS_LEN, fp))
    {
        ALOGE("Failed to fgets string.\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);

    return 0;
}

static void recordUUID2File(const char* pMnt)
{
    struct stat buf;
    int ret = stat("/cache/recovery/", &buf);
    if(ret < 0)
    {
        system("mkdir -p /cache/recovery/");
    }

    FILE *fp = fopen("/cache/recovery/uuid", "w");
    if (fp) {
        FILE *fpMnt = NULL;
        if ((fpMnt = fopen("/proc/mounts", "r"))) {
            char line[1024] = {0};
            char device[256] = {0};
            char mount_path[256]= {0};
            char rest[256] = {0};

            while(fgets(line, sizeof(line), fpMnt)) {
                line[strlen(line)-1] = '\0';

                sscanf(line, "%255s %255s %255s\n", device, mount_path, rest);

                if (0 == strcmp(mount_path, pMnt)) {
                    char cmdStr[256] = {0};
                    char resStr[256] = {0};
                    FILE   *stream = NULL ;

                    snprintf( cmdStr, sizeof(cmdStr), "%s %s", "blkid", device );
                    stream = popen( cmdStr, "r" );
                    if ( stream ) {
                        fread( resStr, sizeof(char), sizeof(resStr),  stream);
                        if (strlen(resStr) !=0 ) {
                            ALOGE("==write %s to /cache/recovery/uuid\n",resStr);
                            fwrite( resStr, sizeof(char), sizeof(resStr), fp);
                        } else {
                            fwrite("path=sdcard", 1, strlen("path=sdcard"), fp);
                            ALOGE("==wirte,%s to /cache/recovery/uuid\n","path=sdcard");
                        }
                        pclose( stream );
                    }
                    break;
                }
            }
            fclose(fpMnt);
        }
        fclose(fp);
    } else {
        ALOGE("failed to open [/cache/recovery/uuid]");
    }
}

static int resume_factory()
{
    struct bootloader_message boot;
    memset(&boot, 0, sizeof(boot));
    strlcpy(boot.command, "boot-recovery", sizeof(boot.command));
    strlcpy(boot.recovery, "recovery\n", sizeof(boot.recovery));

    char bootargs[MAX_BOOTARGS_LEN];
    get_bootargs(bootargs);
    ALOGI("bootargs=%s", bootargs);
    if(strstr(bootargs, "hinand:") != NULL) {
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

    } else if (strstr(bootargs, "mmcblk") != NULL ){
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
    return 0;
}

int rebootForReset()
{
    resume_factory();

    return 0;
}

int rebootForUpgrade(char* path)
{
    recordUUID2File(path);
    return 0;
}
