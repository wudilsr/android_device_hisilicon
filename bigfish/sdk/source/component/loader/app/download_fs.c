/***********************************************************
 *                      Copyright    , 2009-2014, Hisilicon Tech. Co., Ltd.
 *                                   ALL RIGHTS RESERVED
 * FileName:  upgrd_usb.c
 * Description: usb upgrade mode
 *
 * History:
 * Version   Date           Author            DefectNum      Description
 * main\1    2009-2-12    chenling102556      NULL          Create this file.
 ************************************************************/

/* C++ support */
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

/*include header files  */
#include "hi_type.h"
#include "download_fs.h"
#include "hi_loader_info.h"
#include "upgrd_common.h"
#include "upgrd_osd.h"
#include "loaderdb_info.h"
#include "loader_upgrade.h"
#include "protocol_hisi_file.h"
#ifdef HI_LOADER_BOOTLOADER
 #include <uboot.h>
#else
 #include<sys/mount.h>
#endif

static HI_U32 g_u32ReadOffset = 0;
static char g_acFileName[LOADER_FILE_NAME_LEN];

static HI_S32 UsbCheckDevice(HI_VOID);

static HI_BOOL g_bInit = HI_FALSE;

#ifdef HI_LOADER_BOOTLOADER

static HI_S32 UsbCheckDevice(HI_VOID)
{
	usb_set_negotiation_timeout(5);
    return usb_detect();
}

static HI_S32 UsbCheckFile(const HI_CHAR *pstrFileName)
{
    return usb_file_check(pstrFileName);
}
static long UsbRead(const char *filename, void *buffer, unsigned long offset, unsigned long maxsize)
{
    return usb_file_read(filename, buffer, offset, maxsize);
}

#else

#define FS_CHK_NTFS_OK 0x1

typedef enum
{
    HI_FS_FSTYPE_FAT = 0x0,
    HI_FS_FSTYPE_FAT32,
    HI_FS_FSTYPE_NTFS,
    HI_FS_FSTYPE_EXT2,
    HI_FS_FSTYPE_EXT3,
    HI_FS_FSTYPE_EXT4,

    HI_FS_FSTYPE_BUT,
} HI_FS_FSTYPE_E;

static HI_U8* GetDataBuf(HI_U32 len)
{
    HI_U8 *pu8Temp = HI_NULL;

    /* allocate memory for partitions  */
    pu8Temp = (HI_U8*)malloc(len);
    return pu8Temp;
}

/* To fix errors on the desk */
static HI_S32 FS_Chkntfs(const HI_CHAR *pcExtName)
{
    HI_S32 s32Status;
    pid_t child_pid;
	char string[2][12] = {"ntfsck", "-f"};
    HI_CHAR * argv_list[] =
    {NULL,
     NULL,
     NULL,
     NULL};

    if (NULL == pcExtName)
    {
        return HI_FAILURE;
    }

	argv_list[0] = string[0];
    argv_list[1] = (HI_CHAR *)pcExtName;
	argv_list[2] = string[1];

    child_pid = fork();
    if (0 == child_pid)
    {
        execvp((const char *)argv_list[0], (char * const*)argv_list);
        HI_ERR_LOADER("on error occurred in execvp!\r\n");
        abort();
    }

    if (-1 == child_pid)
    {
        return HI_FAILURE;
    }

    waitpid(child_pid, &s32Status, 0);
/*lint -save -e69 -e155*/
    if (WIFEXITED(s32Status))
    {
        return (WEXITSTATUS(s32Status));
    }
/*lint -restore*/
    return HI_FAILURE;
}

static HI_S32 FS_Mount(const char * source, const char * target, const char *fs, HI_FS_FSTYPE_E * fs_mnt)
{
	HI_S32 ret;

	/* Specified format to load.*/
	if (fs != NULL)
	{
		ret = mount(source, target, fs, 0, NULL);
		if (ret < 0)
		{
			HI_DBG_LOADER("<ERROR>mount %s on %s type %s failed!\n", source, target, fs);
		}

		return ret;
	}

	/* Automatically choose filesystem type to mount when unspecified filesystem type.  */
	if (FS_Mount(source, target, "vfat", NULL) >= 0)
	{
		*fs_mnt = HI_FS_FSTYPE_FAT32;
		return HI_SUCCESS;
	}

	if (FS_Mount(source, target, "ext4", NULL) >= 0)
	{
		*fs_mnt = HI_FS_FSTYPE_EXT4;
		return HI_SUCCESS;
	}

	if (FS_Mount(source, target, "ext3", NULL) >= 0)
	{
		*fs_mnt = HI_FS_FSTYPE_EXT3;
		return HI_SUCCESS;
	}

	if (FS_Mount(source, target, "ext2", NULL) >= 0)
	{
		*fs_mnt = HI_FS_FSTYPE_EXT2;
		return HI_SUCCESS;
	}

	FS_Chkntfs(source);
	if (FS_Mount(source, target, "tntfs", NULL) >= 0)
	{
		*fs_mnt = HI_FS_FSTYPE_NTFS;
		return HI_SUCCESS;
	}

	return HI_FAILURE;
}

static HI_S32 FS_Umount(const char * target)
{
    HI_S32 ret;

    /* 2: MNT_DETACH:
    ** Perform a lazy unmount: make the mount point unavailable for new accesses,
    ** and actually perform the unmount when the mount point ceases  to be busy. */
    ret = umount2(target, 2);
    if (ret < 0)
    {
        perror("umount");
        HI_DBG_LOADER("<ERROR>umount %s failed!\n", target);
    }

    return ret;
}

static HI_S32 Upgrd_FS_Probe(const HI_CHAR *pstrParName)
{
    struct stat statbuf;
	LOADER_PARTITION_INDEX_S stLoaderBootargsInfo;
	HI_S8 fs_dev[64] = {0};

	if (HI_SUCCESS != Loader_GetFlashParIndex(pstrParName, &stLoaderBootargsInfo))
	{
		HI_ERR_LOADER("call Loader_GetFlashParIndex in %s!\n", __FUNCTION__);
		return HI_FAILURE;
	}

	if (HI_FLASH_TYPE_EMMC_0 == stLoaderBootargsInfo.u32FlashType)
	{
		HI_OSAL_Snprintf(fs_dev, sizeof(fs_dev), "/dev/mmcblk0p%d", stLoaderBootargsInfo.u32FlashIndex+1);
	}

	memset(&statbuf, 0, sizeof(statbuf));
    if (0 != lstat(fs_dev, &statbuf))
    {
        return HI_FAILURE;
    }

    if (S_ISBLK(statbuf.st_mode))
    {
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

/*Trim away the space, return or table character of right string.*/
static void Fs_rtrim(HI_CHAR *pcString)
{
    HI_CHAR *pc;

    if (HI_NULL == pcString)
    {
        HI_ERR_LOADER("Invalid pointer.\n");
        return;
    }

    if (0 == strlen(pcString))
    {
        return;
    }

    pc = pcString + 1;
    while (*pc)
    {
        if ((0x20 == *pc) || ('\t' == *pc) || ('\n' == *pc) || ('\r' == *pc))
        {
            *pc = '\0';
            return;
        }

        pc++;
    }
}

static HI_S32 FsCheckDevice(HI_CHAR *pcDeviceName)
{
	HI_S32 s32Loop = 0;

	HI_DBG_LOADER("Probing fs device now.\n");
	for (s32Loop = 0; s32Loop < UPGRD_FS_TRY_TIMES; s32Loop++)
	{
		LOADER_Delayms(250);

		if (HI_SUCCESS == Upgrd_FS_Probe(pcDeviceName))
		{
			HI_DBG_LOADER("\nprobe a fs device.\n");
			break;
		}
	}

	if (UPGRD_FS_TRY_TIMES <= s32Loop)
	{
		HI_ERR_LOADER("\nNo found  fs device.\n");
		return HI_FAILURE;
	}

	HI_DBG_LOADER("\n****Find a fs device*****.\n");

	return HI_SUCCESS;
}

static HI_S32 FsCheckFile(const HI_CHAR *pstrFileName, const HI_CHAR *pstrParName)
{
	HI_FS_FSTYPE_E fs_mnt;
	FILE *pf_read;
	struct stat statbuf;
	HI_S32 try_count = UPGRD_FS_TRY_TIMES;
	LOADER_PARTITION_INDEX_S stLoaderBootargsInfo;
	HI_S8 fs_dev[64] = {0};

	if (HI_SUCCESS != Loader_GetFlashParIndex(pstrParName, &stLoaderBootargsInfo))
	{
		HI_ERR_LOADER("can't find %s partition!\n", pstrParName);
		return HI_FAILURE;
	}

	if (HI_FLASH_TYPE_EMMC_0 == stLoaderBootargsInfo.u32FlashType)
	{
		HI_OSAL_Snprintf(fs_dev, sizeof(fs_dev), "/dev/mmcblk0p%d", stLoaderBootargsInfo.u32FlashIndex+1);
	}

	//LOADER_Delayms(1000);

	while (try_count > 0)
	{
		try_count--;
		HI_DBG_LOADER("Search update file in %s", pstrParName);

        if (HI_SUCCESS != FS_Mount(fs_dev, "/tmp", NULL, &fs_mnt))
        {
            continue;
        }

		HI_DBG_LOADER("upgrade file name:%s\n", pstrFileName);

		memset(&statbuf, 0, sizeof(statbuf));
		if (0 != lstat(pstrFileName, &statbuf))
		{
			HI_ERR_LOADER("No found update file in %s", pstrParName);
			FS_Umount("/tmp");
			LOADER_Delayms(250);
			continue;
		}

		HI_DBG_LOADER("Have found update file, file system is: %d\r\n", fs_mnt);
		return HI_SUCCESS;
	}

	HI_DBG_LOADER("Have found update file, file system is: %d\r\n", fs_mnt);
	return HI_FAILURE;
}


static long FsRead(const char *filename, void *buffer, unsigned long offset, unsigned long maxsize)
{
    FILE* fp = NULL;
    long Redlen = 0;

    fp = fopen(filename, "r");
    if (NULL == fp)
    {
        HI_ERR_LOADER("Open file %s failed.\n", filename);
        return -1;
    }

    if (0 != fseek(fp, offset, SEEK_SET))
    {
        fclose(fp );
        return -1;
    }

    Redlen = fread(buffer, 1, maxsize, fp);
    fclose(fp );

    return Redlen;
}

static long file_get_size(const char *filename)
{
    FILE* fp = NULL;
    long filelen = 0;

    fp = fopen(filename, "r");
    if (NULL == fp)
    {
        HI_ERR_LOADER("Open file %s failed.\n", filename);
        return -1;
    }

    fseek(fp, 0L, SEEK_END);
    filelen = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    fclose(fp );

    return filelen;
}

#endif

/**
 \brief initialize USB download mode.
 \attention \n
 \param[in] Para:
 \retval ::HI_SUCCESS : get data success
 \retval ::HI_FAILURE : failed to get data
 */

// OTA
HI_S32 LOADER_DOWNLOAD_FS_Init(HI_VOID * Para)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (g_bInit == HI_TRUE)
    {
        return HI_SUCCESS;
    }

    g_u32ReadOffset = 0;

    memset((HI_VOID *)g_acFileName, 0, sizeof(g_acFileName));

    if (HI_NULL == Para)
    {
#ifdef HI_LOADER_BOOTLOADER
        memcpy((HI_VOID *)g_acFileName, DEFAULT_UPDATE_FILE_NAME,
        strlen(DEFAULT_UPDATE_FILE_NAME)+1);
#else
        HI_OSAL_Snprintf(g_acFileName, sizeof(g_acFileName), "/tmp/%s", DEFAULT_UPDATE_FILE_NAME);
#endif
    }
    else
    {
        HI_U32 u32Len = strlen((HI_CHAR *)Para)+1;

        HI_DBG_LOADER("FS upgrade file : %s\n", Para);

        if (u32Len > sizeof(g_acFileName))
        {
            u32Len = sizeof(g_acFileName);
        }
#ifdef HI_LOADER_BOOTLOADER
        memcpy((HI_VOID *)g_acFileName, Para, u32Len);
#else
		if (((HI_CHAR *)Para)[0] == '/')
		{
			HI_OSAL_Snprintf(g_acFileName, sizeof(g_acFileName), "/tmp%s", (HI_CHAR*)Para);
		}
		else
		{
			HI_OSAL_Snprintf(g_acFileName, sizeof(g_acFileName), "/tmp/%s", (HI_CHAR*)Para);
		}
#endif
    }

    if ((HI_SUCCESS == FsCheckDevice(CACHE))
        && (HI_SUCCESS == FsCheckFile(g_acFileName, CACHE)))
    {
        HI_INFO_LOADER("Have found update file %s in %s\n", g_acFileName, CACHE);
        s32Ret = HI_SUCCESS;
    }
    else if ((HI_SUCCESS == FsCheckDevice(SDCARD))
        && (HI_SUCCESS == FsCheckFile(g_acFileName, SDCARD)))
    {
        HI_INFO_LOADER("Have found update file %s in %s\n", g_acFileName, SDCARD);
        s32Ret = HI_SUCCESS;
    }
    else if ((HI_SUCCESS == FsCheckDevice(USERDATA))
        && (HI_SUCCESS == FsCheckFile(g_acFileName, USERDATA)))
    {
        HI_INFO_LOADER("Have found update file %s in %s\n", g_acFileName, USERDATA);
        s32Ret = HI_SUCCESS;
    }
    else
    {
        HI_ERR_LOADER("Have no found update file %s in %s or %s or %s\n",
        g_acFileName, CACHE, SDCARD, USERDATA);
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

/**
 \brief deinitialize USB download mode.
 \attention \n
 \retval ::HI_SUCCESS : get data success
 \retval ::HI_FAILURE : failed to get data
 */
HI_S32 LOADER_DOWNLOAD_FS_DeInit(HI_VOID)
{
    g_bInit = HI_FALSE;

#ifdef HI_LOADER_APPLOADER
	FS_Umount("/tmp");
#endif
    return HI_SUCCESS;
}

/**
 \brief Get upgrade data through USB.
 \attention \n
 \param[in] pbuffer: data buffer, allocate by caller
 \param[in] size: the max expected size, it must be samller than the buffer length
 \param[out] outlen: the really length of data
 \retval ::HI_SUCCESS : get data success
 \retval ::HI_FAILURE : failed to get data
 */
HI_S32 LOADER_DOWNLOAD_FS_Getdata(HI_VOID * pbuffer, HI_U32 size, HI_U32 * outlen)
{
    long lRet = 0;

    if ((HI_NULL == pbuffer) || (HI_NULL == outlen))
        return HI_FAILURE;

    lRet = FsRead(g_acFileName, pbuffer, (unsigned long)g_u32ReadOffset, (unsigned long)size);
    if (lRet < 0)
        return HI_FAILURE;

    *outlen = lRet;
    g_u32ReadOffset += lRet;

    return HI_SUCCESS;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif  /* __cplusplus */
