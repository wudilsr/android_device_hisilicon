/*********************************************************************************************************************
*  @file     com_FileExplorer_jni_Jni.c
*  @brief    define samba client interface file
*  @version  1.0
**********************************************************************************************************************/

#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <android/log.h>
#define LOG_TAG "------JniLog Main--------"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO  , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN  , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Samba.h"
#include "HiNSClient.h"
#include "IHiNSService.h"
#include <signal.h>
#include <setjmp.h>
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

#define CIFS_INSMOD "insmod /data/cifs.ko"
#define SHARE_PATH "/sdcard/share"
#define MAX_SIZE 512
#define CIFS_DIR1 "/proc/fs/cifs"
#define CIFS_DIR2 "/sys/module/cifs"

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "jni.h"
#include "JNIHelp.h"
#include <android_runtime/AndroidRuntime.h>

using namespace android;
typedef unsigned int UINT;

/*		C PLUS PLUS		*/
#include <string>
#include <vector>

std::string ip_mountpoint;
std::string buf, pcName;
std::vector <std::string> ip_mount;

UINT mountpoint_flag = 0;
const UINT total_num = 16;
#define SDCARD_USER
#ifndef SDCARD_USER
const char *mountpoint[] = {
		"/data/app/mountpoint_01",
		"/data/app/mountpoint_02",
		"/data/app/mountpoint_03",
		"/data/app/mountpoint_04",
		"/data/app/mountpoint_05",
		"/data/app/mountpoint_06",
		"/data/app/mountpoint_07",
		"/data/app/mountpoint_08",
		"/data/app/mountpoint_09",
		"/data/app/mountpoint_10",
		"/data/app/mountpoint_11",
		"/data/app/mountpoint_12",
		"/data/app/mountpoint_13",
		"/data/app/mountpoint_14",
		"/data/app/mountpoint_15",
		"/data/app/mountpoint_16",
		NULL,
		};
#else
const char *mountpoint[] = {
		"/mnt/smb/mountpoint_01",
		"/mnt/smb/mountpoint_02",
		"/mnt/smb/mountpoint_03",
		"/mnt/smb/mountpoint_04",
		"/mnt/smb/mountpoint_05",
		"/mnt/smb/mountpoint_06",
		"/mnt/smb/mountpoint_07",
		"/mnt/smb/mountpoint_08",
		"/mnt/smb/mountpoint_09",
		"/mnt/smb/mountpoint_10",
		"/mnt/smb/mountpoint_11",
		"/mnt/smb/mountpoint_12",
		"/mnt/smb/mountpoint_13",
		"/mnt/smb/mountpoint_14",
		"/mnt/smb/mountpoint_15",
		"/mnt/smb/mountpoint_16",
		NULL,
		};
#endif
struct CreateSambaFile : private Samba
{
	CreateSambaFile() { }
	virtual ~CreateSambaFile() { }
};


void replacespace(const char *str, char *retstr)
{
	if(str == NULL) return;
	for(int i = 0, j = 0; i < strlen(str); ++i)
	{
		if(str[i] == ' ')
		{
            retstr[j ++] = '\\';
            retstr[j ++] = '0';
            retstr[j ++] = '4';
            retstr[j ++] = '0';
		}
		else
		{
		retstr[j ++] = str[i];
		}
	}
}

/**
 *	get 'arguments' from samba-test to jni
 *	@param[in]			void
 *	@param[in|out]
 *	@return		    int
 *	@note
 */
static void alarm_func(int sig)
{
	if(canjump == 0)
		return;
	canjump = 0;
	siglongjmp(jmpbuf, 1);
}

/**
 *	get Array Num
 *	@param[in]			const char *
 *	@param[in|out]
 *	@return		    	int -1 fail
 *	@note
 */
static int getMountpointOrderNum(const char *str)
{
	if(str == NULL)
		return -1;
	for(UINT i = 0; i < total_num; i++)
	{
		if(strcmp(str, mountpoint[i]) == 0)
		return i;
	}
	return -1;
}

static int my_atoi(const char *str)
{
	char buf[MAX_SIZE / 2] = {0};
	if(str)
	{
		int j = 0;
		for(int i = 0; i < strlen(str) + 1; i++)
		{
		if(isdigit(str[i]) && str[i] != '0')
		{
		buf[j] = str[i];
		j++;
		}
		}
	}
	return atoi(buf);
}

/**
 *	get flag bit
 *	@param[in]			UINT
 *	@param[in|out]
 *	@return		    	int -1 fail
 *	@note
 */
static int getFlag(UINT sign)
{
	int j = -1;
	for(UINT i = 0; i < total_num; i++)
	{
		j = (sign >> i) & 1;
		if(!j) return i;
	}
	return -1;
}

/**
 *	get Mount List
 *	@param[in]			void
 *	@param[in|out]
 *	@return		    	const char * ERROR or ,MountList;
 *	@note
 */

static UINT findChar(std::string &str, UINT num, char chr = ' ')
{
	UINT i = 0, j = 0;
	for(std::string::iterator it = str.begin(); it != str.end(); it ++, i++)
	{
		if (*it == chr)
		{
		j ++;
		if (j == num)
		break;
		}
	}
	return i;
}


static UINT getMountList(void)
{
	UINT mountpoint_count = 0;
	char buf[MAX_SIZE] = {0};
	ip_mount.clear();
	FILE *fd;
	fd = popen("mount", "r");
	if(fd == NULL)
	{
		LOGE("%d : Popen Fail!", __LINE__);
		return -1;
	}
	while((fgets(buf, sizeof(buf), fd)) != NULL)
	{
		if(buf != NULL)
		{
			if(strstr(buf, " cifs "))
			{
				ip_mount.push_back(buf);
				mountpoint_count ++;
			}
		}

	}
	pclose(fd);
	return mountpoint_count;
}

static const char *getMountList(const char *str)
{
	buf.clear();
	getMountList();
	if(ip_mount.empty())
	{
		LOGE("%d : Mount List is NULL!", __LINE__);
		return "ERROR";
	}
	if(str == NULL) return "ERROR";
	char retstr[MAX_SIZE] = {0};
	replacespace(str, retstr);
	LOGI("line : %d, UI send needed unmount path = %s", __LINE__, retstr);
	sprintf(retstr, "%s /", retstr);
	for(std::vector <std::string>::iterator it = ip_mount.begin(); it != ip_mount.end(); it ++)
	{
		if(!(*it).empty())
		{
		if((*it).find(retstr, 0) != std::string::npos)
		{
		buf = (*it).substr(findChar(*it, 1) + 1, findChar(*it, 2) - findChar(*it, 1) -1);
		LOGI("%d : Return UI Need Umount path = %s", __LINE__, buf.c_str());
		return buf.c_str();
		}
		}
	}
	LOGE("%d : get mount path error!", __LINE__);
	return "ERROR";
}


static const char *substr(const char *buf)
{
	pcName.clear();
	for(int i = 0; i < strlen(buf) + 1; i++)
	{
		if (buf[i] == '\t')
		continue;
		if(buf[i] == ' ')
		break;
		pcName += buf[i];
	}
	return pcName.empty() ? "ERROR" : pcName.c_str();
}

/**
 *	for get PC name of server's ip
 *	@param[in]			const char *ip
 *	@param[in|out]
 *	@return		    const char *
 *						return	"ERROR" : No PC info
 *	@note
 */
static const char *getPcName(const char *ip)
{
	CreateSambaFile samba;
	if(ip == NULL)
	{
		LOGE("%d : ip = NULL", __LINE__);
		return "ERROR";
	}
	char buf[MAX_SIZE] = {0};
	FILE *fd;
	sprintf(buf, "nmblookup -A %s", ip);
	if ( (fd = popen(buf, "r")) == NULL )
	{
		LOGE("%d : popen error!", __LINE__);
		return "ERROR";
	}
	while(fgets(buf, sizeof(buf), fd) != NULL)
	{
		if(strlen(buf) > 0)
		{
		if(strstr(buf, "Looking up") || strstr(buf, "<GROUP>") || strstr(buf, "MAC Address")
		|| strstr(buf, "No reply") || strstr(buf, "Packet send failed"))
		continue;
		if(strstr(buf, "<ACTIVE>"))
		return substr(buf);
		}
	}
	pclose(fd);
	return "ERROR";
}

static int my_umount(const char *path);
static int umountlist()
{
	std::string mountlist;
	getMountList();
	for(std::vector <std::string>::iterator it = ip_mount.begin(); it != ip_mount.end(); ++it)
	{
		int i = 0;
		for(std::string::iterator it_str = (*it).begin(); it_str != (*it).end(); ++it_str)
		{
		if((*it_str == ' '))
		{
		++i;
		if(i == 1)
		continue;
		if(i == 2)
		break;
		}
		if( i == 1)
		mountlist += *it_str;
		}
		mountlist += ":";
	}
	int ret = my_umount(mountlist.c_str());
	switch (ret)
    {
		case -1 : return -1;      //Create FIFO fail;
		case -2 : return -2;      //Open FIFO fail;
		case -3 : return -3;      //Write FIFO fail;
		case -5 : return -5;	  //Net Error!;
		default : return 0 ;      //Success;
    }
}

static int my_umount(const char *path)
{
	char buf[MAX_SIZE] = {0};
	int ret = HiNSClient::NSUnMount(path);
	if(ret == 0 && strstr(path, ":") == NULL)
	{
		int i = getMountpointOrderNum(path);
		if(i < 0)
		{
			LOGE("%d : Path does not exist!", __LINE__);
			return -1;
		}
		getMountList();
		for(std::vector <std::string>::iterator it = ip_mount.begin(); it != ip_mount.end(); it++)
		{
			if((*it).find(path, 0) != std::string::npos)
			{
				LOGE("Maybe device is busy!");
				return -6;	//Umount Error.
			}
		}
		mountpoint_flag &= ~(1 << i);
		LOGI("%d : uMount Success! \t mountpoint_flag = %d", __LINE__, mountpoint_flag);
	}
	else if(ret == 0 && strstr(path, ":") != NULL)
	{
		mountpoint_flag &= 0;
		LOGI("%d, All of cifs's mounting delete!", __LINE__);
	}
	switch (ret)
	{
		case -1 : return -1;      //Create FIFO fail;
		case -2 : return -2;      //Open FIFO fail;
		case -3 : return -3;      //Write FIFO fail;
		case -5 : return -5;	  //Net Error!;
		default : return 0 ;      //Success;
	}
}

static int mountStatus(const char *replace_buf)
{
	if(!ip_mount.empty())
	{
		for(std::vector <std::string>::iterator it = ip_mount.begin(); it != ip_mount.end(); it ++)
		{
		if((*it).find(replace_buf, 0) != std::string::npos)
		{
		return 1;	 // Server have existed in List.
		}
		}
		return 0;
	}
	return 0;
}

/**
 *	call mount.cifs
 *	@param[in]			JNIEnv *env,jobject obj, jstring addr, jstring mp, jstring us, jstring passwd
 *	@param[in|out]
 *	@return			int 0  ,Success
 *				    int -4 ,/mnt does not access
 *					int -5 ,Net Error
 *					int -6 ,user or pass or mount dir error
 *					int -7 ,Server have existed in List
 *					int -10,Server's nums are over  upper limit
 *	@note
 */
JNIEXPORT jint JNICALL Java_com_hisilicon_android_Jni_UImount(JNIEnv *env,jobject obj, jstring Ip, jstring Dir, jstring Mount, jstring us, jstring passwd)
{
    const char *ip, *dir, *user, *password, *jni_mountpoint;
    ip = env->GetStringUTFChars(Ip, NULL);
	dir = env->GetStringUTFChars(Dir, NULL);
	user = env->GetStringUTFChars(us, NULL);
	password = env->GetStringUTFChars(passwd, NULL);
	jni_mountpoint = env->GetStringUTFChars(Mount, NULL);
	DIR *d, *dd;
	std::string str;
	char buf[MAX_SIZE] = {0};
	char replace_buf[MAX_SIZE] = {0};
	if(dir && ip)
	{
		sprintf(buf, "%s/%s", ip, dir);
	        replacespace(buf, replace_buf);
	        LOGI("line : %d, Mount Info = %s", __LINE__, replace_buf);
		sprintf(replace_buf, "%s /", replace_buf);
	}
	else return -1;
	int flagBit = 0;
	int mountpoint_num = 0;
	if((mountpoint_num = getMountList()) >= 16)
	{
		LOGE("%d : Server are over  upper limit", __LINE__);
		return -10;		//Server's num are over  upper limit
	}

		static char old_buf[MAX_SIZE] = {0};
		char new_buf[MAX_SIZE] = {0};
		static time_t old_time;
		static UINT mount_count = 0;
		UINT isMount = mountStatus(replace_buf);
		if(!mount_count)
		{
		LOGW("line : %d, The first mount", __LINE__);
		if(isMount)
		{
		LOGW("line : %d : Server has existed in List.", __LINE__);
		return 0;
		}
		sprintf(old_buf, "%s, %s, %s, %s", ip, dir, user, password);
		time(&old_time);
		mount_count = 1;
		}
		else
		{
		sprintf(new_buf, "%s, %s, %s, %s", ip, dir, user, password);
		LOGW("line : %d, Mount_count == 1, and old buf = %s, new_buf = %s", __LINE__, old_buf, new_buf);
		if(!strncmp(old_buf, new_buf, strlen(new_buf)))
		{
		time_t new_time = time(NULL);
		time_t sleep_time = 0;
	                        LOGW("line : %d, Coming in old buf equal to new buf! old time = %d, new time = %d", __LINE__, old_time, new_time);
		if(old_time && (abs((int)(new_time - old_time)) < 10) && (abs((int)(new_time - old_time)) >= 5) && !isMount)
		{
		LOGW("line : %d, Coming in new time - old time < 10", __LINE__);
		for( ; ;)
		{
		sleep(1);
		getMountList();
		time(&sleep_time);
		if(mountStatus(replace_buf) == 1 || abs((int)(sleep_time - new_time)) >= 5)
		goto MOUNTSTATUS;
		}
		}
		else if(old_time && ((abs((int)(new_time - old_time))) >= 10))
		{
		LOGW("line : %d, Coming in new time - old time  >= 10", __LINE__);
		getMountList();
		if(mountStatus(replace_buf))
		goto MOUNTSTATUS;
		else	goto THEFIRSTMOUNT;
		}
		getMountList();
		if(mountStatus(replace_buf))
                                {
                                        LOGW("line : %d, Mount Error!", __LINE__);
                                        mount_count = 0;
                                        return -1;
                                }
MOUNTSTATUS:
		if(sleep_time != 0 && (sleep_time - new_time) >= 5)
		{
                                        LOGW("line : %d, Sleep time is UP! Mount Error!", __LINE__);
                                        mount_count = 0;
                                        return -1;
		}
		if(mountStatus(replace_buf))
		{
		flagBit = getFlag(mountpoint_flag);
		mountpoint_flag |= 1 << flagBit;
		LOGW("line : %d, Notice : Mount time is too long!! But Mount Success! So can you find some problem?", __LINE__);
		mount_count = 0;
		old_time = 0;
		memset(old_buf, '\0', sizeof(old_buf));
		memset(new_buf, '\0', sizeof(new_buf));
		return 0;
		}
		}
		LOGW("line : %d, Mount continue!", __LINE__);
		mount_count = 0;
		old_time = 0;
		memset(old_buf, '\0', sizeof(old_buf));
		memset(new_buf, '\0', sizeof(new_buf));
		}
THEFIRSTMOUNT:
	if ((d = opendir("/mnt")) == NULL)
    {
		LOGE("%d : dir = /mnt does not access!", __LINE__);
		return -4;		// mnt does not access!
    }
    else
    {
        closedir(d);
        if ((d = opendir("/mnt/smb")) == NULL)
        {
            mkdir("/mnt/smb",0777);
        }else closedir(d);

        char jni_mountStr[MAX_SIZE] = {0};
        if(strstr(jni_mountpoint, " "))
		{
		flagBit = getFlag(mountpoint_flag);
		if( flagBit < 0 )
		return -1;
		strncpy(jni_mountStr, mountpoint[flagBit], sizeof(jni_mountStr));
		}
		else
		{

		strncpy(jni_mountStr, jni_mountpoint, sizeof(jni_mountStr));
		flagBit = my_atoi(jni_mountpoint) - 1;
		if( flagBit < 0 )
		{
		LOGE("%d : MountPoint is ERROR!", __LINE__);
		return -1;
		}
		LOGI("%d : Receive Jni's mountpoint String = %s, and flagBit = %d", __LINE__, jni_mountStr, flagBit);
		}

		if((dd = opendir(jni_mountStr)) == NULL)
		{
		char directory[MAX_SIZE] = {0};
		LOGI("%d : mount flag order = %d, mountpoint = %s", __LINE__, flagBit, jni_mountStr);
		sprintf(directory, "mkdir %s", mountpoint[flagBit]);
		system(directory);
		LOGI("%d : Create dir success! dir = %s", __LINE__, jni_mountStr);
		}
		else closedir(dd);

    }

	char mount_cifs_addr[MAX_SIZE * 2] = {0};

	sprintf(mount_cifs_addr, "-t cifs //%s/\"%s\" %s -o user=%s,pass=%s,iocharset=utf8,cache=loose"
		",uid=1001,gid=1001,file_mode=0777,dir_mode=0777",
		ip, dir, mountpoint[flagBit], user, password);

	int ret = HiNSClient::NSMount((char *)mount_cifs_addr);
	if(ret != 0) {
		LOGE("can't mount cifs , set password");
		memset(mount_cifs_addr,0,sizeof(mount_cifs_addr));
		sprintf(mount_cifs_addr, "-t cifs //%s/\"%s\" %s -o user=%s,pass=%s,sec=ntlm,iocharset=utf8,cache=loose"
				",uid=1001,gid=1001,file_mode=0777,dir_mode=0777",
				ip, dir, mountpoint[flagBit], user, password);
		ret = HiNSClient::NSMount((char *)mount_cifs_addr);
	}
	if(ret == 0)
	{
		old_time = 0;
		mount_count = 0;
		memset(old_buf, '\0', sizeof(old_buf));
                memset(new_buf, '\0', sizeof(new_buf));
		mountpoint_flag |= 1 << flagBit;
		LOGI("%d : Mount Success! \t Mountpoint numuber = %d , Mountpoint_flag = %d", __LINE__, mountpoint_num, mountpoint_flag);
	}

	env->ReleaseStringUTFChars(Ip, ip);
	env->ReleaseStringUTFChars(Dir, dir);
	env->ReleaseStringUTFChars(us, user);
	env->ReleaseStringUTFChars(passwd, password);
	switch (ret)
	{
		case -1 : return -1;      //Create FIFO fail;
		case -2 : return -2;      //Open FIFO fail;
		case -3 : return -3;      //Write FIFO fail;
		case -5 : return -5;	  //Net Error!;
		case -6 : return -6;	  //USER or PASS Error!;
		default : return 0;       //Success;
	}

}

/**
 *	umount path
 *	@param[in]			JNIEnv *env, jobject obj, jstring ph
 *	@param[in|out]
 *	@return		    int		0 : success
 *							-1:
 *							-2:
 *							-5: Net Error
 *							-6: Umount Error
 *	@note
 */
JNIEXPORT jint JNICALL Java_com_hisilicon_android_Jni_myUmount(JNIEnv *env, jobject obj, jstring ph)
{
	const char *path;
    path = env->GetStringUTFChars(ph, NULL);

		if(!path)
	{
		LOGE("%d : Umount Path = NULL!", __LINE__);
		return -4;	//Have not path!
	}
		int ret = my_umount(path);
		env->ReleaseStringUTFChars(ph, path);
		switch (ret)
		{
		case -1 : return -1;      //Create FIFO fail;
		case -2 : return -2;      //Open FIFO fail;
		case -3 : return -3;      //Write FIFO fail;
		case -5 : return -5;	  //Net Error!;
		default : return 0 ;      //Success;
    }

}

/*
 * Class:     com_explorer_jni_Jni
 * Method:    getMountList
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_hisilicon_android_Jni_getMountList(JNIEnv *env, jobject obj, jstring ph)
  {
	const char *path;
		path = env->GetStringUTFChars(ph, NULL);
	jstring mountList = env->NewStringUTF(getMountList(path));
		env->ReleaseStringUTFChars(ph, path);
	return mountList;
  }


/*
 * Class:     com_explorer_jni_Jni
 * Method:    getPcName
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_hisilicon_android_Jni_getPcName(JNIEnv *env, jobject obj, jstring ip)
{
		const char *ipAddress;
		ipAddress = env->GetStringUTFChars(ip, NULL);
		jstring pcName = env->NewStringUTF(getPcName(ipAddress));
		env->ReleaseStringUTFChars(ip, ipAddress);
		return pcName;
}

/*
 * Class:     com_explorer_jni_Jni
 * Method:    umountlist
 * Signature: void
 */
JNIEXPORT jint JNICALL Java_com_hisilicon_android_Jni_umountlist(JNIEnv *env, jobject obj)
{
	return umountlist();
}

JNIEXPORT static jint JNICALL  Java_com_hisilicon_android_sambaClient_init(JNIEnv *env, jobject obj)
{
	char buf[MAX_SIZE] = {0};
	char* mpoint;
	int flagBit = 0;
	FILE *fd;
	fd = popen("mount", "r");
	if(fd == NULL)
	{
		LOGE("%d : Popen Fail!", __LINE__);
		return -1;
	}
	while((fgets(buf, sizeof(buf), fd)) != NULL)
	{
		if(buf != NULL)
		{
			if(strstr(buf, " cifs "))
			{
				strtok(buf," ");
				mpoint = strtok(NULL," ");
				for(int i = 0; i < total_num; i++) {
					if(strcmp(mpoint, mountpoint[i]) == 0)
						flagBit = i;
				}
				mountpoint_flag |= 1 << flagBit;
			}
		}

	}
	pclose(fd);
	return 0;
}

static const JNINativeMethod g_methods[] = {
	{ "myUmount", "(Ljava/lang/String;)I", (void *)Java_com_hisilicon_android_Jni_myUmount },
	{ "UImount", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I", (void *)Java_com_hisilicon_android_Jni_UImount },
	{ "getMountPoint", "(Ljava/lang/String;)Ljava/lang/String;", (void *)Java_com_hisilicon_android_Jni_getMountList },
	{ "getPcName", "(Ljava/lang/String;)Ljava/lang/String;", (void *)Java_com_hisilicon_android_Jni_getPcName },
	{ "umountlist", "()I", (void *)Java_com_hisilicon_android_Jni_umountlist },
	{ "sambaInit", "()I", (void *)Java_com_hisilicon_android_sambaClient_init },
};
int register_com_FileExplorer_jni_Jni(JNIEnv* env)
{

	jclass clazz;
	clazz = env->FindClass("com/hisilicon/android/netshare/Jni");
	if (clazz == NULL)
		return JNI_FALSE;
	if (env->RegisterNatives(clazz, g_methods, NELEM(g_methods)) < 0)
		return JNI_FALSE;
	return JNI_TRUE;
}
/*
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	JNIEnv* env = NULL;
	jint result = -1;

	if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
		goto bail;
	if (!register_com_FileExplorer_jni_Jni(env))
		goto bail;

	result = JNI_VERSION_1_4;
bail:
	return result;
}*/
