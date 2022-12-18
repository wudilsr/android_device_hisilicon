/*
 * Copyright (C) 2008 The Android Open Source Project
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

/*
    Modification of display module.
        1. UNF interfaces contain in libhi_avplay.so and other unforeseeable libraries.
        2. BASEPARAME macros do not exist in SDK. It will need to be added when transplanting to formal version.


 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <linux/kd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/resource.h>
#include <linux/loop.h>

#include <dlfcn.h>
#include <stdint.h>
#include <cutils/properties.h>
#include <cutils/sockets.h>
#include <linux/capability.h>
#include <linux/prctl.h>
#include <private/android_filesystem_config.h>
#include "hi_unf_pmoc.h"

#include <cutils/log.h>
#include <dirent.h>
#include <ctype.h>
#include <utime.h>
#include <sys/wait.h>
#include "hiRecovery.h"
//#include "sambamanager.h"
#include "flashInfo.h"
#include "hinetutils.h"
#include "sysmanager.h"

#define BUFFER_MAX    1024  /* input buffer for commands */
#define TOKEN_MAX     24     /* max number of arguments in buffer */
#define REPLY_MAX     256   /* largest reply allowed */
#define READ_ERROR    -1   /*read error*/

struct cmdinfo {
    const char *name;
    int (*func)(char **arg, char reply[REPLY_MAX]);
};
int do_upgrade(const char* path)
{
    rebootForUpgrade(path);
    return 100;
}
int do_reset()
{
    rebootForReset();
    return 0;
}
int do_updateCAFile(const char* path1,const char* path2)
{
#ifdef CFG_HI_ADVCA_SUPPORT
    //    SLOGE("#######%s,arg[0]=%s,arg[1]=%s",__FUNCTION__,arg[0],arg[1]);
    int ret = HI_SYS_Init();
    if (-1 == ret)
    {
        SLOGE("HI_SYS_Init Failed!(%s->%d)",__FUNCTION__,__LINE__);
        return -1;
    }
    if((NULL!=path1)&&(NULL!=path2)){
        return CA_Android_authUpdateFile(path1,path2);
    }else return -1;
#endif
    return 0;
}
int do_EnterSmartStandby()
{
    SLOGE("do_EnterSmartStandby!(%s->%d)",__FUNCTION__,__LINE__);
    system("echo 2 > /proc/inputblock/status");
    HI_UNF_PMOC_Init();
    HI_UNF_PMOC_EnterSmartStandby(0x1ffbfff);
    return 0;
}
int do_QuitSmartStandby()
{
    SLOGE("do_QuitSmartStandby!(%s->%d)",__FUNCTION__,__LINE__);
    system("echo 0 > /proc/inputblock/status");
    HI_UNF_PMOC_QuitSmartStandby();
    HI_UNF_PMOC_DeInit();
    return 0;
}
int do_setFlashInfo(const char* flag,int offset,int offlen,const char* info)
{
    char mtdname[1024]={0};
    char minfo[1024]={0};
    unsigned long moffset=-1;
    unsigned int mofflen=-1;
    int i=0;

    if(flag!=NULL)
    {
        strcat(mtdname,flag);
    }
    if(info=NULL)
    {
        strcat(minfo,info);
    }
    moffset = offset;
    mofflen = offlen;
    SLOGE("do_setFlashInfo= %s %d %d %s", mtdname,moffset,mofflen,minfo);
    if(strlen(mtdname)>0 && moffset >= 0 && mofflen > 0)
    {
        return set_flash_info(mtdname,moffset,mofflen,minfo);
    }
    return -1;
}
int do_getFlashInfo(const char* flag,int offset,int offlen)
{
    char mtdname[1024]={0};
    unsigned long moffset=-1;
    unsigned int mofflen=-1;
    int i=0;

    if(flag!=NULL)
    {
        strcat(mtdname,flag);
    }
    moffset = offset;
    mofflen = offlen;
    SLOGE("get_flash_info= %s %d %d", mtdname,moffset,mofflen);

    if(strlen(mtdname)>0 && moffset >= 0 && mofflen > 0)
    {
        return get_flash_info(mtdname,moffset,mofflen);
    }
    return -1;
}
int do_enableInterface(const char* interfacename)
{
    char interface[1024] = {0};

    if(interfacename != NULL)
    {
        strcat(interface, interfacename);
    }

    if(strlen(interface) > 0)
    {
        SLOGE("do_enableInterface(iface:%s)", interface);
        return enableInterface(interface);
    }
    return -1;
}
int do_disableInterface(const char* interfacename)
{
    char interface[1024] = {0};
    if(interfacename != NULL)
    {
        strcat(interface, interfacename);
    }
    if(strlen(interface) > 0)
    {
        SLOGE("do_disableInterface(iface:%s)", interface);
        return disableInterface(interface);
    }
    return -1;
}
int do_addRoute(const char* interfacename,const char* dst,int length,const char* gw)
{
    char minterface[1024] = {0};
    char mdst[1024] = {0};
    unsigned int prefix_length = 0;
    char mgw[1024] = {0};

    if(interfacename != NULL)
    {
        strcat(minterface, interfacename);
    }

    if(dst != NULL)
    {
        strcat(mdst, dst);
    }
    if(gw != NULL)
    {
        strcat(mgw, gw);
    }
    prefix_length = length;

    if(strlen(minterface) > 0 && strlen(mdst) > 0 && strlen(mgw) > 0)
    {
        SLOGE("do_addRoute(iface:%s, dst:%s, prefix_length:%d, gw:%s)",
        minterface, mdst, prefix_length, mgw);
        return addRoute(minterface, mdst, prefix_length, mgw);
    }
    return -1;
}
int do_removeRoute(const char* interfacename,const char* dst,int length,const char* gw)
{
    char minterface[1024] = {0};
    char mdst[1024] = {0};
    unsigned int prefix_length = 0;
    char mgw[1024] = {0};

    if(interfacename != NULL)
    {
        strcat(minterface, interfacename);
    }

    if(dst != NULL)
    {
        strcat(mdst, dst);
    }
    if(gw != NULL)
    {
        strcat(mgw, gw);
    }
    prefix_length = length;

    if(strlen(minterface) > 0 && strlen(mdst) > 0 && strlen(mgw) > 0)
    {
        SLOGD("do_addRoute(iface:%s, dst:%s, prefix_length:%d, gw:%s)",
        minterface, mdst, prefix_length, mgw);
        return removeRoute(minterface, mdst, prefix_length, mgw);
    }
    return -1;
}
int do_setDefaultRoute(const char* interfacename, int gw)
{
    char minterface[1024] = {0};
    unsigned int mgw = 0;

    if(interfacename!= NULL)
    {
        strcat(minterface, interfacename);
    }
    mgw = gw;
    if(strlen(minterface) > 0 && mgw > 0)
    {
        SLOGE("do_setDefaultRoute(iface:%s, gw:%d)", minterface, mgw);
        return setDefaultRoute(minterface, mgw);
    }
    return -1;
}
int do_removeDefaultRoute(const char* interfacename)
{
    char minterface[1024] = {0};

    if(interfacename!= NULL)
    {
        strcat(minterface, interfacename);
    }

    if(strlen(minterface) > 0)
    {
        SLOGE("do_removeDefaultRoute(iface:%s)", minterface);
        return removeDefaultRoute(minterface);
    }
    return -1;
}
int do_removeNetRoute(const char* interfacename)
{
    char minterface[1024] = {0};

    if(interfacename!= NULL)
    {
        strcat(minterface, interfacename);
    }

    if(strlen(minterface) > 0)
    {
        SLOGE("do_removeNetRoute(iface:%s)", minterface);
        return removeNetRoute(minterface);
    }
    return -1;
}
int do_setHDCPKey(const char* tdname,int offset,const char* filename,int datasize)
{
    FILE *fp = NULL;
    char mtdname[256] = {0};
    char hdcpfile_name[256] = {0};
    char *pBuf = NULL;
    long moffset = -1;
    int mdatasize = -1;
    int ret = -1;
    if (tdname != NULL)
    {
        strcat(mtdname, tdname);
    }
    moffset = offset;
    if (filename != NULL)
    {
        strcat(hdcpfile_name, filename);
    }
    mdatasize = datasize;
    pBuf = (char *)malloc(mdatasize);
    if (pBuf == NULL)
    {
        SLOGE("Failed to malloc %d memory!!", mdatasize);
        return -1;
    }
    memset(pBuf, 0, mdatasize);
    SLOGE("do_setHDCPKey = %s %d %s %d", mtdname, moffset, hdcpfile_name, mdatasize);
    // Get HDCP Key.
    fp = fopen(hdcpfile_name, "r");
    if (NULL == fp)
    {
        SLOGE("Failed to get HDCP Key! Interupt the burn process!\n");
        free(pBuf);
        return -1;
    }
    fread(pBuf, 1, mdatasize, fp);
    fclose(fp);
    remove(hdcpfile_name);
    if (strlen(mtdname) > 0 && offset >= 0 && mdatasize > 0)
    {
        ret = set_HDCP2x_Key(mtdname, moffset, pBuf, mdatasize);
    }
    memset(pBuf, 0, mdatasize);
    free(pBuf);
    pBuf = NULL;
    return ret;
}
int do_getHDCPKey(const char* tdname,int offset,const char* filename,int datasize)
{
    int ret = -1;
    char mtdname[256] = {0};
    char hdcpfile_name[256] = {0};
    unsigned long moffset = -1;
    unsigned int mofflen = -1;
    char *pBuf = NULL;
    FILE *fp = NULL;
    if (tdname!= NULL)
    {
        strcat(mtdname, tdname);
    }
    moffset = offset;

    if (filename != NULL)
    {
        strcat(hdcpfile_name, filename);
    }
    mofflen = datasize;
    SLOGE("do_getHDCPKey = %s %d %s %d", mtdname, moffset, hdcpfile_name, mofflen);

    pBuf = (char *)malloc(mofflen);
    if (pBuf == NULL)
    {
        SLOGE("Failed to malloc %d memory!!", mofflen);
        return -1;
    }
    memset(pBuf, 0, mofflen);
    if (strlen(mtdname) >0 && mofflen > 0)
    {
        ret = get_HDCP2x_Key(mtdname, moffset, pBuf, mofflen);
    }
    if (ret == 0)
    {
        fp = fopen(hdcpfile_name, "wb");
        if (NULL == fp)
        {
        SLOGE("Failed to get HDCP Key!\n");
        free(pBuf);
        pBuf = NULL;
        return -1;
        }
        fwrite(pBuf, 1, mofflen, fp);
        fflush(fp);
        fclose(fp);
    }
    free(pBuf);
    pBuf = NULL;
    return ret;
}
int do_setDRMKey(const char* tdname,int offset,const char* filename,int datasize)
{
    FILE *fp = NULL;
    char mtdname[256] = {0};
    char hdcpfile_name[256] = {0};
    char *pBuf = NULL;
    long moffset = -1;
    int mdatasize = -1;
    int ret = -1;
    int i;

    if (tdname != NULL)
    {
        strcat(mtdname, tdname);
    }
    moffset = offset;

    if (filename != NULL)
    {
        strcat(hdcpfile_name, filename);
    }
    mdatasize = datasize;
    pBuf = (char *)malloc(mdatasize);
    if (pBuf == NULL)
    {
        SLOGE("Failed to malloc %d memory!!", mdatasize);
        return -1;
    }
    memset(pBuf, 0, mdatasize);

    //SLOGE("do_setDRMKey = %s %d %s %d", mtdname, offset, hdcpfile_name, datasize);

    // Get DRM Key.
    fp = fopen(hdcpfile_name, "r");
    if (NULL == fp)
    {
        SLOGE("Failed to get DRM Key! Interupt the burn process!\n");
        free(pBuf);
        return -1;
    }
    fread(pBuf, 1, mdatasize, fp);
    fclose(fp);
    remove(hdcpfile_name);

    if (strlen(mtdname) > 0 && moffset >= 0 && mdatasize > 0)
    {
        ret = set_DRM_Key(mtdname, moffset, pBuf, mdatasize);
    }

    memset(pBuf, 0, mdatasize);
    free(pBuf);
    pBuf = NULL;
    return ret;
}


int do_getDRMKey(const char* tdname,int offset,const char* filename,int datasize)
{
    int ret = -1;
    char mtdname[256] = {0};
    char hdcpfile_name[256] = {0};
    unsigned long moffset = -1;
    unsigned int mofflen = -1;
    char *pBuf = NULL;
    FILE *fp = NULL;

    if (tdname != NULL)
    {
        strcat(mtdname, tdname);
    }
    moffset = offset;
    if (filename != NULL)
    {
        strcat(hdcpfile_name, filename);
    }
    mofflen = datasize;
    //SLOGE("do_getDRMKey = %s %d %s %d", mtdname, offset, hdcpfile_name, offlen);

    pBuf = (char *)malloc(mofflen);
    if (pBuf == NULL)
    {
        SLOGE("Failed to malloc %d memory!!", mofflen);
        return -1;
    }
    memset(pBuf, 0, mofflen);

    if (strlen(mtdname) >0 && mofflen > 0)
    {
        ret = get_DRM_Key(mtdname, moffset, pBuf, mofflen);
    }
    if (ret == 0)
    {
        fp = fopen(hdcpfile_name, "wb");
        if (NULL == fp)
        {
            SLOGE("Failed to get DRM Key!\n");
            free(pBuf);
            pBuf = NULL;
            return -1;
        }
        fwrite(pBuf, 1, mofflen, fp);
        fflush(fp);
        fclose(fp);
    }
    free(pBuf);
    pBuf = NULL;

    return ret;
}


