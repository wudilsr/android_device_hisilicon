/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <errno.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>


#include "mtdutils/mtdutils.h"
#include "mtdutils/ubiutils.h"
#include "mtdutils/mounts.h"
#include "roots.h"
#include "common.h"
#include "make_ext4fs.h"

extern "C" {
#include "uuid.h"
}

#define SDCARD_MOUNTPOINT   "/sdcard"
#define MAX_DEV_NAME_LENGTH 64
#define MAX_RETRY_TIMES     10

static int num_volumes = 0;
static Volume* device_volumes = NULL;

extern struct selabel_handle *sehandle;

static void wait_for_device(const char* fn) {
    int tries = 0;
    int ret;
    struct stat buf;
    do {
        ++tries;
        ret = stat(fn, &buf);
        if (ret) {
            LOGE("stat %s try %d: %s\n", fn, tries, strerror(errno));
            sleep(1);
        }
    } while (ret && tries < MAX_RETRY_TIMES);
    if (ret) {
        LOGE("failed to stat %s\n", fn);
    }
}

static int parse_options(char* options, Volume* volume) {
    char* option;
    while ((option = strtok(options, ","))) {
        options = NULL;

        if (strncmp(option, "length=", 7) == 0) {
            volume->length = strtoll(option+7, NULL, 10);
        } else {
            LOGE("bad option \"%s\"\n", option);
            return -1;
        }
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
                LOGE("error!!, Can't get Flash Type in Cmdline %s\n",buffer);
            }
        }
        fclose(fp);
    }
    return ret;
}

void load_volume_table() {
    int alloc = 2;
    device_volumes = (Volume*)malloc(alloc * sizeof(Volume));

    // Insert an entry for /tmp, which is the ramdisk and is always mounted.
    device_volumes[0].mount_point = "/tmp";
    device_volumes[0].fs_type = "ramdisk";
    device_volumes[0].device = NULL;
    device_volumes[0].device2 = NULL;
    device_volumes[0].length = 0;
    num_volumes = 1;

    FILE* fstab = NULL;

    if ( check_flash_type() == NAND_TYPE ) {
        LOGI("Load the recovery.fstab\n");
        fstab = fopen("/etc/recovery.fstab", "r");
    }
    else if ( check_flash_type() == EMMC_TYPE ) {
        LOGI("Load the recovery.emmc.fstab\n");
        fstab = fopen("/etc/recovery.emmc.fstab", "r");
    } else {
        fstab = fopen("/etc/recovery.fstab", "r");
    }

    if (fstab == NULL) {
        LOGE("failed to open /etc/recovery.fstab (%s)\n", strerror(errno));
        return;
    }

    char buffer[1024];
    int i;
    while (fgets(buffer, sizeof(buffer)-1, fstab)) {
        for (i = 0; buffer[i] && isspace(buffer[i]); ++i);
        if (buffer[i] == '\0' || buffer[i] == '#') continue;

        char* original = strdup(buffer);

        char* mount_point = strtok(buffer+i, " \t\n");
        char* fs_type = strtok(NULL, " \t\n");
        char* device = strtok(NULL, " \t\n");
        // lines may optionally have a second device, to use if
        // mounting the first one fails.
        char* options = NULL;
        char* device2 = strtok(NULL, " \t\n");
        if (device2) {
            if (device2[0] == '/') {
                options = strtok(NULL, " \t\n");
            } else {
                options = device2;
                device2 = NULL;
            }
        }

        if (mount_point && fs_type && device) {
            while (num_volumes >= alloc) {
                alloc *= 2;
                device_volumes = (Volume*)realloc(device_volumes, alloc*sizeof(Volume));
            }
            device_volumes[num_volumes].mount_point = strdup(mount_point);
            device_volumes[num_volumes].fs_type = strdup(fs_type);
            device_volumes[num_volumes].device = strdup(device);
            device_volumes[num_volumes].device2 =
                device2 ? strdup(device2) : NULL;

            device_volumes[num_volumes].length = 0;
            if (parse_options(options, device_volumes + num_volumes) != 0) {
                LOGE("skipping malformed recovery.fstab line: %s\n", original);
            } else {
                ++num_volumes;
            }
        } else {
            LOGE("skipping malformed recovery.fstab line: %s\n", original);
        }
        free(original);
    }

    fclose(fstab);

    printf("recovery filesystem table\n");
    printf("=========================\n");
    for (i = 0; i < num_volumes; ++i) {
        Volume* v = &device_volumes[i];
        printf("  %d %s %s %s %s %lld\n", i, v->mount_point, v->fs_type,
               v->device, v->device2, v->length);
    }
    printf("\n");
}

Volume* volume_for_path(const char* path) {
    int i;
    for (i = 0; i < num_volumes; ++i) {
        Volume* v = device_volumes+i;
        int len = strlen(v->mount_point);
        if (strncmp(path, v->mount_point, len) == 0 &&
            (path[len] == '\0' || path[len] == '/')) {
            return v;
        }
    }
    return NULL;
}

int ensure_path_mounted(const char* path) {
    Volume* v = volume_for_path(path);
    if (v == NULL) {
        LOGE("unknown volume for path [%s]\n", path);
        return -1;
    }
    if (strcmp(v->fs_type, "ramdisk") == 0) {
        // the ramdisk is always mounted.
        return 0;
    }

    int result;
    result = scan_mounted_volumes();
    if (result < 0) {
        LOGE("failed to scan mounted volumes\n");
        return -1;
    }

    const MountedVolume* mv =
        find_mounted_volume_by_mount_point(v->mount_point);
    if (mv) {
        // volume is already mounted
        return 0;
    }

    mkdir(v->mount_point, 0755);  // in case it doesn't already exist

    if (strcmp(v->fs_type, "yaffs2") == 0) {
        // mount an MTD partition as a YAFFS2 filesystem.
        mtd_scan_partitions();
        const MtdPartition* partition;
        partition = mtd_find_partition_by_name(v->device);
        if (partition == NULL) {
            LOGE("failed to find \"%s\" partition to mount at \"%s\"\n",
                 v->device, v->mount_point);
            return -1;
        }
        return mtd_mount_partition(partition, v->mount_point, v->fs_type, 0);
    } else if (strcmp(v->fs_type, "ubifs") == 0) {

        mtd_scan_partitions();
        const MtdPartition* mtd;
        mtd = mtd_find_partition_by_name(v->device);
        if (mtd == NULL) {
            LOGE("failed to find \"%s\" partition to mount at \"%s\"\n",
                 v->device, v->mount_point);
            return -1;
        }

        int dev_num;
        int ret;
        ret = mtd_num2ubi_dev(mtd->device_index,&dev_num);
        if (ret == -1) {
            LOGE("%s do not attach ubi,please check\n",v->device);
            return -1;
        }
        char device[20];
        sprintf(device,"/dev/ubi%d_0", dev_num);
        LOGE("try mount %s to %s\n",device,v->mount_point);
        if (mount(device, v->mount_point, v->fs_type,
                    MS_NOATIME | MS_NODEV | MS_NODIRATIME, "") < 0) {
            LOGE("%s failed to mount %s (%s)\n",device,v->mount_point, strerror(errno));
            return -1;
        }
        return 0;
    } else if (strcmp(v->fs_type, "ext4") == 0 ||
               strcmp(v->fs_type, "vfat") == 0 ||
               strcmp(v->fs_type, "ntfs") == 0 ) {
        result = mount(v->device, v->mount_point, v->fs_type,
                       MS_NOATIME | MS_NODEV | MS_NODIRATIME, "");
        if (result == 0) return 0;

        if (v->device2) {
            LOGW("failed to mount %s (%s); trying %s\n",
                 v->device, strerror(errno), v->device2);
            result = mount(v->device2, v->mount_point, v->fs_type,
                           MS_NOATIME | MS_NODEV | MS_NODIRATIME, "");
            if (result == 0) return 0;
        }

        LOGE("failed to mount %s (%s)\n", v->mount_point, strerror(errno));
        return -1;
    } else if (strcmp(v->fs_type, "auto") == 0) {
        wait_for_device(v->device);
        if ( (result = mount(v->device, v->mount_point, "vfat", MS_NOATIME | MS_NODEV | MS_NODIRATIME, ""))) {
            if ( (result = mount(v->device, v->mount_point, "ext4", MS_NOATIME | MS_NODEV | MS_NODIRATIME, ""))) {
                result = mount(v->device, v->mount_point, "ntfs", MS_NOATIME | MS_NODEV | MS_NODIRATIME, "");
            }
        }
        if (result == 0) return 0;

        if (v->device2) {
            wait_for_device(v->device2);
            if ( (result = mount(v->device2, v->mount_point, "vfat", MS_NOATIME | MS_NODEV | MS_NODIRATIME, ""))) {
                if ( (result = mount(v->device2, v->mount_point, "ext4", MS_NOATIME | MS_NODEV | MS_NODIRATIME, ""))) {
                    result = mount(v->device2, v->mount_point, "ntfs", MS_NOATIME | MS_NODEV | MS_NODIRATIME, "");
                }
            }
            if (result == 0) return 0;
        }

        LOGE("failed to mount %s (%s)\n", v->mount_point, strerror(errno));
        return -1;
    }

    LOGE("unknown fs_type \"%s\" for %s\n", v->fs_type, v->mount_point);
    return -1;
}

int ensure_path_unmounted(const char* path) {
    Volume* v = volume_for_path(path);
    if (v == NULL) {
        LOGE("unknown volume for path [%s]\n", path);
        return -1;
    }
    if (strcmp(v->fs_type, "ramdisk") == 0) {
        // the ramdisk is always mounted; you can't unmount it.
        return -1;
    }

    int result;
    result = scan_mounted_volumes();
    if (result < 0) {
        LOGE("failed to scan mounted volumes\n");
        return -1;
    }

    const MountedVolume* mv =
        find_mounted_volume_by_mount_point(v->mount_point);
    if (mv == NULL) {
        // volume is already unmounted
        return 0;
    }

    return unmount_mounted_volume(mv);
}

int format_volume(const char* volume) {
    Volume* v = volume_for_path(volume);
    if (v == NULL) {
        LOGE("unknown volume \"%s\"\n", volume);
        return -1;
    }
    if (strcmp(v->fs_type, "ramdisk") == 0) {
        // you can't format the ramdisk.
        LOGE("can't format_volume \"%s\"", volume);
        return -1;
    }
    if (strcmp(v->mount_point, volume) != 0) {
        LOGE("can't give path \"%s\" to format_volume\n", volume);
        return -1;
    }

    if (ensure_path_unmounted(volume) != 0) {
        LOGE("format_volume failed to unmount \"%s\"\n", v->mount_point);
        return -1;
    }

    if (strcmp(v->fs_type, "yaffs2") == 0 || strcmp(v->fs_type, "mtd") == 0) {
        mtd_scan_partitions();
        const MtdPartition* partition = mtd_find_partition_by_name(v->device);
        if (partition == NULL) {
            LOGE("format_volume: no MTD partition \"%s\"\n", v->device);
            return -1;
        }

        MtdWriteContext *write = mtd_write_partition(partition);
        if (write == NULL) {
            LOGW("format_volume: can't open MTD \"%s\"\n", v->device);
            return -1;
        } else if (mtd_erase_blocks(write, -1) == (off_t) -1) {
            LOGW("format_volume: can't erase MTD \"%s\"\n", v->device);
            mtd_write_close(write);
            return -1;
        } else if (mtd_write_close(write)) {
            LOGW("format_volume: can't close MTD \"%s\"\n", v->device);
            return -1;
        }
        return 0;
    }

    if (strcmp(v->fs_type, "ext4") == 0) {
        int result = make_ext4fs(v->device, v->length, volume, sehandle);
        if (result != 0) {
            LOGE("format_volume: make_extf4fs failed on %s\n", v->device);
            return -1;
        }
        return 0;
    }

    if (strcmp(v->fs_type, "ubifs") == 0) {
        int result = ubi_clear_volume((char *)v->device, 0);
        if (result != 0) {
            LOGE("format_volume: clear_volume failed on %s\n", v->device);
            return -1;
        }
        return 0;
    }

    LOGE("format_volume: fs_type \"%s\" unsupported\n", v->fs_type);
    return -1;
}


int update_sdcard_volume_by_uuid(const char* uuid, const char* fstype)
{
    LOGI("uuid=%s, fstype=%s\n", uuid, fstype);

    int iRet = 0;

    if (NULL == uuid)
        return -1;

    int i;
    for (i = 0; i < num_volumes; ++i) {
        if (0 == strcmp(device_volumes[i].mount_point, SDCARD_MOUNTPOINT))
            break;
    }

    if (i == num_volumes)
        return -1;

    int tries = 0;
    char *buf_dev = NULL;

    do {
        ++tries;
        buf_dev = get_devname_from_uuid(uuid);
        if (buf_dev == NULL) {
            LOGW("can not get devname from uuid\n");
            sleep(1);
        } else {
            LOGI("get device name from uuid success\n");
        }
    } while (!buf_dev && tries < MAX_RETRY_TIMES);

    if (NULL != buf_dev) {
        if (device_volumes[i].device)
            free((void *)device_volumes[i].device);
        if (fstype) {
            if (device_volumes[i].fs_type)
                free((void *)device_volumes[i].fs_type);
            device_volumes[i].fs_type = strdup(fstype);
        }
        device_volumes[i].device = buf_dev;
        LOGI("the new sdcard device is  \"%s\", and the new fstype is \"%s\"\n",
            device_volumes[i].device, device_volumes[i].fs_type);
    } else {
        LOGE("can not get device name from uuid\n");
    }

    return iRet;
}

int update_sdcard_volume_by_path(const char* path, const char* fstype)
{
    int iRet = 0;

    if (NULL == path)
        return -1;

    int i;
    for (i = 0; i < num_volumes; ++i) {
        if (0 == strcmp(device_volumes[i].mount_point, SDCARD_MOUNTPOINT))
            break;
    }

    if (i == num_volumes)
        return -1;

    if (device_volumes[i].device)
        free((char *)device_volumes[i].device);
    if (fstype) {
        if (device_volumes[i].fs_type)
            free((char *)device_volumes[i].fs_type);
        device_volumes[i].fs_type = strdup(fstype);
    }

    if(0 == strcmp(fstype, "ubifs")) {
        device_volumes[i].device = strdup(path);
    }else if (0 == strcmp(fstype, "yaffs2")) {
        device_volumes[i].device = strdup(path);
    } else {
        LOGE("unsupport fstype:%s\n", fstype);
        return -1;
    }

    LOGI("the new sdcard device is  \"%s\", and the new fstype is \"%s\"\n",
        device_volumes[i].device, device_volumes[i].fs_type);

    return iRet;
}

#define DEV_DIR "/dev/block/"
#define DEV_MOUNTPOINT "/sdcard/"
static void update_volume_by_dir(const char *dir_buf)
{
	int i;
	for (i = 0; i < num_volumes; ++i) {
		if (0 == strcmp(device_volumes[i].mount_point, SDCARD_MOUNTPOINT))
			break;
	}
	if (i == num_volumes)
		return ;

	if (NULL != dir_buf) {
		if (device_volumes[i].device)
			free((void *)device_volumes[i].device);
		device_volumes[i].device = strdup(dir_buf);
		device_volumes[i].fs_type = strdup("auto");
		LOGI("the new sdcard device is  \"%s\", and the new fstype is \"%s\"\n",
				device_volumes[i].device, device_volumes[i].fs_type);
	}
}
void find_upzip_and_update_volume()
{
	DIR * dir;
	struct dirent *dirent;
	int ret,result;
	char dir_buf[255];
	char mountData[255];

	LOGI("find update.zip \n");
	wait_for_device("/dev/block/sda");

	dir = opendir(DEV_DIR);
	if (dir) {
		while((dirent = readdir(dir))) {
			if (strstr((dirent->d_name),"sd")){
				strcpy(dir_buf,DEV_DIR);
				strcat(dir_buf,dirent->d_name);
				umount(DEV_MOUNTPOINT);
				if((result = mount(dir_buf,DEV_MOUNTPOINT,"vfat", MS_NOATIME | MS_NODEV | MS_NODIRATIME, ""))) {
					if((result = mount(dir_buf,DEV_MOUNTPOINT,"ntfs", MS_NODEV | MS_NOSUID | MS_NODIRATIME, ""))){
						if((result = mount(dir_buf,DEV_MOUNTPOINT,"ext4",MS_NOATIME | MS_NODEV | MS_NODIRATIME, ""))){
							LOGI("can't mount %s\n",dir_buf);
							continue;
						}
					}
				}
				ret = access("/sdcard/update.zip",F_OK);
				if (ret == 0) {
					LOGI("find update.zip in %s\n",dir_buf);
					ret = umount(DEV_MOUNTPOINT);
					if (ret !=0) {
						LOGE("umount failed %s\n",dir_buf);
					}
					update_volume_by_dir(dir_buf);
					break;
				} else {
					LOGI("there is no update.zip in %s \n ",dir_buf);
					ret = umount(DEV_MOUNTPOINT);
					if (ret !=0) {
						LOGE("umount failed %s\n",dir_buf);
					}
				}
				sleep(1);
			}
		}
		closedir(dir);
   }
}
