/*********************************************************************************************************************
*  @file     samba-test.cpp
*  @brief    for samba mount.cifs and umount
*  @version  1.0
**********************************************************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <utils/Log.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include<sys/wait.h>

#include "netShareHal.h"

#define CIFS_INSMOD "insmod /data/cifs.ko"
#define CIFS_DIR1 "/proc/fs/cifs"
#define CIFS_DIR2 "/sys/module/cifs"

#define MAX_SIZE  512

int isSystemSuccessful(pid_t status)
{
	if(-1 == status){
		SLOGE("system error!!");
		return -1;
	}else{
		if (WIFEXITED(status)){
			if (0 == WEXITSTATUS(status)){
				return 0;

			}else{
				SLOGE("run shell script fail, script exit code: %d",WEXITSTATUS(status));
				return -1;
			}
		}else{
			SLOGE("exit status = [%d]",WEXITSTATUS(status));
			return -1;
		}
	}

}


/**
 *  test Nestwork,with "ping"
 *  @param[in]          void
 *  @param[in|out]
 *  @return         int
 *  @note
 */
static int ping_ip(const char *str)
{
	int i = 0 ;
	char ip[20] = {0};
	char temp[100] = {0};
	char isnum[8] = {0};
	char *t = NULL;
	char *tm = NULL;
	if(str)
        strncpy(temp, str, 100);
    for(  ;temp[i]!=0;i++ ){
        if (isdigit(temp[i])){
            strncpy(isnum ,&temp[i] ,7);
            if((strchr(isnum,0x2e)) && (!strchr(isnum,0x20))) {
                t = &temp[i];
                break;
            }
        }
    }
	if(!t){
		ALOGE("%d, Server haven't ip !", __LINE__);
		return 0;
	}
	ALOGE("(%s-%d)temp=%s",__FUNCTION__,__LINE__,t);
	if (( (tm = strchr(t ,':')) != NULL) || ((tm = strchr(t ,'/')) != NULL)) {
		*tm = 0 ;
	}else {
		ALOGE("%d, Server haven't ip !", __LINE__);
		return 0;
	}

	strcpy(ip, t);
	char buf[100] = {0};
	char buf_popen[100] = {0};
	char *tmip = NULL ;
	sprintf(buf, "%s%s", "ping -c 1 ", ip);
	ALOGE("(%s-%d)buf=(%s)",__FUNCTION__,__LINE__,buf);

	if(tmip = strstr(ip,".")) {
		if(tmip = strstr(tmip+1,".")) {
			if(tmip = strstr(tmip+1,".")) {
				ALOGE("(%s-%d) ip is real",__FUNCTION__,__LINE__);
			} else return 0;
		} else return 0;
	} else return 0;

	FILE *streamout = popen(buf, "r");
	if(streamout == NULL)
	{
		ALOGE("(%s-%d)popen() call error!",__FUNCTION__,__LINE__);
		return -4;
	}
	while(fgets(buf_popen, sizeof(buf_popen), streamout))
	{
		if(strstr(buf_popen, "1 received") != NULL)
		{
			pclose(streamout);
			ALOGI("Net OK");
			return 0;
		}
		else if(strstr(buf_popen, "0 received") != NULL)
		{
			pclose(streamout);
			ALOGE("Net Error!");
			return -5;
		}
	}
	pclose(streamout);
	return -5;
}


/**
 *  UI_mount mount.cifs //ip/dir /localpath -o user= ,pass=
 *  @param[in]          char *pMount
 *  @param[in|out]
 *  @return         int
 *  @note
 */
static int UI_mount(const char *pMount)
{
	ALOGI("mountpoint's string:%s", pMount);
	char retStr[MAX_SIZE] = {0};
	sprintf(retStr, "busybox mount %s;echo $?", pMount);
	int i = 0;
	char buf[MAX_SIZE] = {0};
	FILE *fd = popen(retStr, "r");

	if(fd == NULL)
	{
		ALOGE("line : %d, popen() error!", __LINE__);
		return -1;
	}
	while(fgets(buf, sizeof(buf), fd) != NULL)
	{
		ALOGI("retStr = %s", buf);
		int retValue = atoi(buf);
		if(retValue == 32)
		{
			ALOGE("line : %d, USER or PASS Error", __LINE__);
			pclose(fd);
			return -6;
		}
		if(retValue == 1 || retValue == 130 || retValue == 255)
		{
			ALOGE("line : %d, Mount Error", __LINE__);
			pclose(fd);
			return -1;
		}
	}
	pclose(fd);
	return 0;
}


/**
 *  umount path
 *  @param[in]          char *path
 *  @param[in|out]
 *  @return         int
 *  @note
 */
static int my_umount(const char *path)
{
	if(!path)
	{
		ALOGE("Path is using Default's Path!Please check the path right or wrong?");
		return -1;
	}
	char *mountlist[MAX_SIZE / 32];
	int i = 0;
	for( ; i < MAX_SIZE / 32; ++i)
		mountlist[i] = (char *)malloc(sizeof(char) * MAX_SIZE / 4);
	ALOGI("Come in 'my_umount',path = %s", path);
	char buf[MAX_SIZE] = {0};
	if(strstr(path, ":") != NULL)
	{
		unsigned k = 0;
		unsigned m = 0;
		unsigned n = 0;
		for(k = 0, m = 0, n = 0; k < (strlen(path)) + 1 && m < MAX_SIZE / 32 && n < MAX_SIZE / 4; ++k)
		{
			if(*(path + k) == ':')
			{
				++m;
				n = 0;
				continue;
			}
			*(mountlist[m] + n) = *(path + k);
			++n;
		}
	}
	else {
		strncpy(mountlist[0], path, MAX_SIZE / 4);
	}
	FILE *fd = NULL;

	for (i = 0; i < MAX_SIZE / 32 && strlen(mountlist[i]) > 0; ++i)
	{
		if(strstr(mountlist[i], "umount") != NULL)
			sprintf(buf, "%s;echo $?", mountlist[i]);
		else sprintf(buf, "umount %s;echo $?", mountlist[i]);
		ALOGI("line : %d, mountlist[%d] = %s", __LINE__, i, mountlist[i]);
		if((fd = popen(buf, "r")) == NULL)
		{
			ALOGE("%d : popen() error!", __LINE__);
			return -1;
		}
		while(fgets(buf, sizeof(buf), fd) != NULL)
		{
			if(atoi(buf) == 1 || atoi(buf) == 2)
			{
				ALOGE("%d : Umount fail!!", __LINE__);
				pclose(fd);
				return -1;
			}
		}

	}
	pclose(fd);
	i = 0;
	for( ; i < MAX_SIZE / 32; ++i)
		free(mountlist[i]);
	return 0;
}



int netShareMount(const char *buf)
{
	ALOGI("In function start mount");
	if( ping_ip(buf) == -5 )
	{
		return -1;
	}
	if(UI_mount(buf) != 0)
	{
		return -1;
	}
	return 0;
}

int netShareUnMount(const char *buf)
{
	if(my_umount(buf) < 0)
	{
		return -1;
	}
	return 0;
}

int netShareSambaStart()
{
	pid_t status;
	if(setuid(0))
	{
		ALOGE("setuid failed");
		return -1;
	}

	ALOGI("In function start smbd");
	status = system("smbd");
	if (isSystemSuccessful(status) != 0) {
		ALOGE("SMBD start fail !");
		return -1;
	}
	ALOGI("In function start nmbd");
	status = system("nmbd");
	if (isSystemSuccessful(status) != 0) {
		ALOGE("NMBD start fail !");
		return -1;
	}
	return 0;
}

int netShareSambaStop()
{
	if(setuid(0))
	{
		ALOGE("setuid failed");
		return -1;
	}

	if(!system("kill -15 `busybox pidof smbd`"))
		if(!system("kill -15 `busybox pidof nmbd`"))
			if(!system("kill -15 `busybox pidof smbd nmbd`"))
				ALOGI("Stop SMBD NMBD Success!");
	return 0;
}

int netShareChangePassword(const char *buff)
{
	const char *user = "radio";
	const char *newPasswd = buff;
	char cmd[255] = {0};
	pid_t status;
	if(setuid(0))
	{
		ALOGE("setuid failed");
		return -1;
	}


	sprintf(cmd,"smbpasswd -a -n %s", user);
	ALOGI("sambaChangePassword1 = %s", cmd);
	status = system(cmd);
	if (isSystemSuccessful(status) != 0) {
		ALOGE("sambaChangePassword run system error!");
		return -1;
	}
	sprintf(cmd, "(echo \"%s\";echo \"%s\") | smbpasswd -s %s", buff, newPasswd, user);
	ALOGI("sambaChangePassword2 = %s", cmd);
	status = system(cmd);
	if (isSystemSuccessful(status) != 0) {
		ALOGE("sambaChangePassword run system error!");
		return -1;
	}
	return 0;
}

int netShareNssh(HI_NS_CMD_TYPE_E cmd,const char *buf)
{
	pid_t status;
	char tmp[1024] = {0};
	ALOGE("nssh(%d,%s) run !",cmd,buf);
	switch(cmd) {
		case HI_NS_CMD_TYPE_RMM :
			sprintf(tmp,"rm -rf %s",buf);
			status = system(tmp);
			if (isSystemSuccessful(status) != 0) {
				ALOGE("HI_NS_CMD_TYPE_RMM (%s) run system error!",buf);
				return -1;
			}
			break;
		case HI_NS_CMD_TYPE_PSM :
			sprintf(tmp,"ps > %s",buf);
			status = system(tmp);
			if (isSystemSuccessful(status) != 0) {
				ALOGE("HI_NS_CMD_TYPE_PSM (%s) run system error!",buf);
				return -1;
			}
			break;
		case HI_NS_CMD_TYPE_SCANM :
			sprintf(tmp,"/system/bin/arp-scan %s",buf);
			status = system(tmp);
			if (isSystemSuccessful(status) != 0) {
				ALOGE("HI_NS_CMD_TYPE_SCANM (%s) run system error!",buf);
				return -1;
			}
			break;
		case HI_NS_CMD_TYPE_CPM :
			sprintf(tmp,"cp -a %s",buf);
			status = system(tmp);
			if (isSystemSuccessful(status) != 0) {
				ALOGE("HI_NS_CMD_TYPE_CPM (%s) run system error!",buf);
				return -1;
			}
		case HI_NS_CMD_TYPE_ISOMKNODM :
			sprintf(tmp,"busybox mknod %s",buf);
			status = system(tmp);
			if (isSystemSuccessful(status) != 0) {
				ALOGE("HI_NS_CMD_TYPE_ISOMKNODM (%s) run system error!",buf);
				return -1;
			}
		case HI_NS_CMD_TYPE_LOSETUPM :
			sprintf(tmp,"busybox losetup %s",buf);
			status = system(tmp);
			if (isSystemSuccessful(status) != 0) {
				ALOGE("HI_NS_CMD_TYPE_LOSETUPM (%s) run system error!",buf);
				return -1;
			}
			break;
		default:
				ALOGE(" error cmd!");
				return -1;
	}
		return 0;
}
