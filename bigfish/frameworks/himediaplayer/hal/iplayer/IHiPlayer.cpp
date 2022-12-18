// IPlayer.cpp: implementation of the IPlayer class.
//
//////////////////////////////////////////////////////////////////////
#define LOG_NDEBUG 0

#include "IHiPlayer.h"
#include "../HiMediaPlayer.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <android/log.h>
#include <unistd.h>
#include <sys/un.h>
#include <cutils/sockets.h>
#include <utils/Log.h>
#include "HiNSClient.h"
#include "IHiNSService.h"

#define LOG_TAG         "IHiPlayer"

#define MOUNT_POINT     "/mnt/xbmc"
#define MOUNT_ISO_POINT "/mnt/xbmciso"
#define BUFFER_SIZE     4096

using namespace android;

extern "C"{
static HiMediaPlayer * g_hiMediaPlayer=NULL;
static char g_newurl[BUFFER_SIZE] = {0};

static char* intToBytes2(int n) {
    char *b = (char *)malloc(4);
    for (int i = 3; i >= 0; i--) {
        b[i] = (char) (n >> (i * 8));
    }
    return b;
}

static int writex(int s, char *_buf, int count)
{
    char *buf = _buf;
    int n = 0, r;
    if (count < 0) return -1;
    while (n < count) {
        r = write(s, buf + n, count - n);
        if (r < 0) {
            if (errno == EINTR)
            {
                continue;
            }
            //write error
            return -1;
        }
        n += r;
    }
    return 0;
}
static int isMount(const char* mountpoint)
{
    FILE * fp;
    char tmp[1024]={0};
    if((fp = popen("mount","r"))==NULL){
        ALOGE("check mount error !");
        return -1;
    }
    while(fgets(tmp,sizeof(tmp),fp)!= NULL){
        if(strstr(tmp,mountpoint)){
            pclose(fp);
            LOGD("isMount %s",mountpoint);
            return 0;
        }
    }
    pclose(fp);
    return -1;
}
static int runCMD(char *cmd)
{
    FILE *fb =NULL;
    extern int errno;
    char tmp[1024]={0};
    if((fb = popen(cmd,"r")) == NULL)
    {
        char * mesg = strerror(errno);
        ALOGE("runCMD error :%d:%s: %s",errno,mesg,cmd);
        return -1;
    }

    if(fgets(tmp,sizeof(tmp),fb)!= NULL){
        ALOGV("runCMD : %s",tmp);
    }
    pclose(fb);
    ALOGV("runCMD ok : %s",cmd);
    return 0;
}

static int mkNotExitDir(const char* dir)
{
    char tmp[1024]={0};
    if (access(dir,0) !=0)
    {
        snprintf( tmp, sizeof(tmp), "%s -p %s","/system/bin/mkdir",dir);
        return runCMD(tmp);
    }
    return 0;
}







                //do nothing
////////////////
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/wait.h>

#include <linux/kdev_t.h>
#include <linux/fs.h>

#include <cutils/log.h>
#include <cutils/properties.h>

#include <dirent.h>
#include <ctype.h>

int readSymLink(const char *path, char *link, size_t max) {
    struct stat s;
    int length;

    if (lstat(path, &s) < 0)
        return 0;
    if ((s.st_mode & S_IFMT) != S_IFLNK)
        return 0;

    // we have a symlink
    length = readlink(path, link, max- 1);
    if (length <= 0)
        return 0;
    link[length] = 0;
    return 1;
}

int pathMatchesMountPoint(const char* path, const char* mountPoint) {
    int length = strlen(mountPoint);
    if (length > 1 && strncmp(path, mountPoint, length) == 0) {
        // we need to do extra checking if mountPoint does not end in a '/'
        if (mountPoint[length - 1] == '/')
            return 1;
        // if mountPoint does not have a trailing slash, we need to make sure
        // there is one in the path to avoid partial matches.
        return (path[length] == 0 || path[length] == '/');
    }

    return 0;
}

void getProcessName(int pid, char *buffer, size_t max) {
    int fd;
    snprintf(buffer, max, "/proc/%d/cmdline", pid);
    fd = open(buffer, O_RDONLY);
    if (fd < 0) {
        strcpy(buffer, "???");
    } else {
        int length = read(fd, buffer, max - 1);
        buffer[length] = 0;
        close(fd);
    }
}

int checkFileDescriptorSymLinks(int pid, const char *mountPoint, char *openFilename, size_t max) {


    // compute path to process's directory of open files
    char    path[PATH_MAX];
    sprintf(path, "/proc/%d/fd", pid);
    DIR *dir = opendir(path);
    if (!dir)
        return 0;

    // remember length of the path
    int parent_length = strlen(path);
    // append a trailing '/'
    path[parent_length++] = '/';

    struct dirent* de;
    while ((de = readdir(dir))) {
        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")
                || strlen(de->d_name) + parent_length + 1 >= PATH_MAX)
            continue;

        // append the file name, after truncating to parent directory
        path[parent_length] = 0;
        strcat(path, de->d_name);

        char link[PATH_MAX];

        if (readSymLink(path, link, sizeof(link)) && pathMatchesMountPoint(link, mountPoint)) {
            if (openFilename) {
                memset(openFilename, 0, max);
                strncpy(openFilename, link, max-1);
            }
            closedir(dir);
            return 1;
        }
    }

    closedir(dir);
    return 0;
}


int checkFileMaps(int pid, const char *mountPoint, char *openFilename, size_t max) {
    FILE *file;
    char buffer[PATH_MAX + 100];

    sprintf(buffer, "/proc/%d/maps", pid);
    file = fopen(buffer, "r");
    if (!file)
        return 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        // skip to the path
        const char* path = strchr(buffer, '/');
        if (path && pathMatchesMountPoint(path, mountPoint)) {
            if (openFilename) {
                memset(openFilename, 0, max);
                strncpy(openFilename, path, max-1);
            }
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}


int checkSymLink(int pid, const char *mountPoint, const char *name) {
    char    path[PATH_MAX];
    char    link[PATH_MAX];

    sprintf(path, "/proc/%d/%s", pid, name);
    if (readSymLink(path, link, sizeof(link)) && pathMatchesMountPoint(link, mountPoint))
        return 1;
    return 0;
}

int getPid(const char *s) {
    int result = 0;
    while (*s) {
        if (!isdigit(*s)) return -1;
        result = 10 * result + (*s++ - '0');
    }
    return result;
}

/*
 * Hunt down processes that have files open at the given mount point.
 * action = 0 to just warn,
 * action = 1 to SIGHUP,
 * action = 2 to SIGKILL
 */
// hunt down and kill processes that have files open on the given mount point
void killProcessesWithOpenFiles(const char *path, int action) {
    DIR*    dir;
    struct dirent* de;

    if (!(dir = opendir("/proc"))) {
        SLOGE("opendir failed (%s)", strerror(errno));
        return;
    }

    while ((de = readdir(dir))) {
        int killed = 0;
        int pid = getPid(de->d_name);
        char name[PATH_MAX];

        if (pid == -1)
            continue;
        getProcessName(pid, name, sizeof(name));

        char openfile[PATH_MAX];

        if (checkFileDescriptorSymLinks(pid, path, openfile, sizeof(openfile))) {
            SLOGE("Process %s (%d) has open file %s", name, pid, openfile);
        } else if (checkFileMaps(pid, path, openfile, sizeof(openfile))) {
            SLOGE("Process %s (%d) has open filemap for %s", name, pid, openfile);
        } else if (checkSymLink(pid, path, "cwd")) {
            SLOGE("Process %s (%d) has cwd within %s", name, pid, path);
        } else if (checkSymLink(pid, path, "root")) {
            SLOGE("Process %s (%d) has chroot within %s", name, pid, path);
        } else if (checkSymLink(pid, path, "exe")) {
            SLOGE("Process %s (%d) has executable path within %s", name, pid, path);
        } else {
            continue;
        }
        if (action == 1) {
            SLOGW("Sending SIGHUP to process %d", pid);
            kill(pid, SIGTERM);
        } else if (action == 2) {
            SLOGE("Sending SIGKILL to process %d", pid);
            kill(pid, SIGKILL);
        }
    }
    closedir(dir);
}

#define LOOP_DIR  "/dev"
#define LOOP_BLOCK_DIR  "/dev/block"
#define NOD_CMD_SIZE 512
#define UNMOUNT_RETRIES  5

int ISOdoMount(const char *fsPath, const char *mountPoint)
{
    int rt = -1;
    pid_t status ;
    static unsigned loopNum = 0;
    unsigned loopMax = 0;
    unsigned nodNum = 0;
    char * p = NULL;
    struct dirent* ent = NULL;
    DIR *pDir;
    char tmp[2048]={0};
    FILE *fb =NULL;
    char *buff =(char *)malloc(strlen(fsPath) + 100);
    char *nod_cmd_buf =(char *)malloc(NOD_CMD_SIZE);
    ALOGV("fsPath=%s,mountPoint=%s",fsPath,mountPoint);
    pDir=opendir(LOOP_BLOCK_DIR);
    while (NULL != (ent=readdir(pDir))) {
        if(0 == strncmp(ent->d_name, "loop", 4)
                &&((ent->d_name[4])> 0x2f)
                &&((ent->d_name[4]) < 0x3a)) {
            p = strstr(ent->d_name,"loop");
            nodNum = atoi(p+4);
            loopMax = (nodNum > loopMax)? nodNum : loopMax ;
        }
    }
    closedir(pDir);

    if((loopMax + 1) >= loopNum){
        for(loopNum; loopNum <= (loopMax +1) ; loopNum ++){
            memset(nod_cmd_buf,0,NOD_CMD_SIZE);
            sprintf(nod_cmd_buf, "/dev/loop%d b 7 %d",loopNum,loopNum);
            HiNSClient::NSSh(HI_NS_CMD_TYPE_ISOMKNODM ,nod_cmd_buf);
        }
    }

    mkNotExitDir(mountPoint);

    memset(buff,0,sizeof(buff));
    sprintf(buff, "%s %s","/system/bin/blkid",fsPath);
    if((fb = popen(buff,"r"))!= NULL){
        if(fgets(tmp,sizeof(tmp),fb)!= NULL){
            char *p = strstr(tmp,"TYPE=");
            if((strncmp("udf",p+6,3)==0)||(strncmp("UDF",p+6,3)==0)){
                memset(buff,0,sizeof(buff));
                sprintf(buff, "-t udf -o loop \"%s\" %s", fsPath, mountPoint);

                rt = HiNSClient::NSMount(buff);
                if(rt==0)
                {
                    goto doClose;
                }
            }
        }
    }
    memset(buff,0,sizeof(buff));
    sprintf(buff, "-o loop \"%s\" %s", fsPath, mountPoint);
    rt = HiNSClient::NSMount(buff);
doClose:
    if(fb){
        pclose(fb);
    }
    free(buff);
    free(nod_cmd_buf);

    return rt;
}

int ISOdoUnmount(const char *path)
{
    int i = 0;
    int action = 0;
    int ret = -1;
    char *buff =(char *)malloc(strlen(path) + 100);
    ALOGV("Unmounting %s", path);
    for (i = 1; i <= UNMOUNT_RETRIES; i++) {
        sprintf(buff, "%s %s","umount -l ", path);
        ret = HiNSClient::NSUnMount(buff);
        if (ret==0)
        {
            break;
        }
        int action = 0; // default is to just complain

        if (i > (UNMOUNT_RETRIES - 2))
            action = 2; // SIGKILL
        else if (i > (UNMOUNT_RETRIES - 3))
            action = 1; // SIGHUP

        killProcessesWithOpenFiles(path, action);
        usleep(100*1000);
    }

    HiNSClient::NSSh(HI_NS_CMD_TYPE_RMM ,path);

    struct dirent* ent = NULL;
    DIR *pDir;
    pDir=opendir(LOOP_DIR);
    while (NULL != (ent=readdir(pDir))) {
        if(0 == strncmp(ent->d_name, "loop", 4)
                &&((ent->d_name[4])> 0x2f)
                &&((ent->d_name[4]) < 0x3a)) {
            char loop_dev[32] = {0};
            sprintf(loop_dev, "%s/%s", "/dev", ent->d_name);
            HiNSClient::NSSh(HI_NS_CMD_TYPE_LOSETUPM ,loop_dev);
        }
    }
    free(buff);
    return 0;
}

//////////////////
int umount_samba_nfs(const char* mountpoint)
{
    if(isMount(mountpoint) !=0)
    {
        return 0;
    }

    int ret = -1;

    if( strcmp(MOUNT_ISO_POINT, mountpoint)== 0)
    {
        ret = ISOdoUnmount(mountpoint);
    }

    char cmdStr[BUFFER_SIZE] = {0};
    snprintf( cmdStr, BUFFER_SIZE, "%s %s","umount ", mountpoint);
    ret = HiNSClient::NSUnMount(cmdStr);
    if(ret != 0)
    {
        snprintf( cmdStr, BUFFER_SIZE, "%s %s","umount -l ", mountpoint);
        ret = HiNSClient::NSUnMount(cmdStr);
    }

    return ret;
}

static void findChar(char *buf)
{
    int num = 0;
    if(!buf) return;
    for(unsigned int i = 0; i < strlen(buf) + 1; i++)
    {
        if(buf[i] == '.')
            num ++;
        if(num == 2)
        {
            buf[i] = '\0';
            break;
        }
    }
}

#define SMB_PATH_LIB      "/data/app/samba/lib"
#define SMB_VALID_DAT     "/data/app/samba/lib/valid.dat"

int init_samba()
{
#if 0
    int ret = 0;
    char buf[1024] = {0};

    if (access(SMB_VALID_DAT,0)==-1)
    {
        sprintf(buf, "system busybox mkdir -p %s", SMB_PATH_LIB);
        ALOGI("[%4d] buf=(%s)", __LINE__, buf);
        if (0==sendCMD(buf))
        {
            sprintf(buf, "system busybox touch %s", SMB_VALID_DAT);
            ALOGI("[%4d] buf=(%s)", __LINE__, buf);
            ret = sendCMD(buf);
        }
    }
    ALOGI("[%4d] ret=(%d)", __LINE__, ret);
#endif
    return 0;
}
int hostnametoip(const char *pc, char* ipstr)
{
    if(!pc)
    {
        LOGE("Argument is NULL!");
        return  -1;
    }
    init_samba();

    FILE *fd;
    LOGI("%d : start getting IP", __LINE__);
    char buf[255] = {0};
    sprintf(buf, "nmblookup %s", pc);
    fd = popen(buf, "r");
    if(fd == NULL)
    {
        LOGE("%d : popen fail", __LINE__);
        return  -1;
    }
    char ip_prefix[255] = {0};
    int  counter = 0;
    while(fgets(buf, sizeof(buf), fd) != NULL)
    {
        counter++;
        if (counter>100){
            ALOGE("%d %s()try 100 times give up!!",__LINE__,__FUNCTION__);
            pclose(fd);
            return -1;
        }
        if(strstr(buf, "name_query failed to find name")){
            pclose(fd);
            return -1;
        }
        if(strstr(buf, "querying"))
        {
            strcpy(ip_prefix, strstr(buf, "on") != NULL ? (strstr(buf, "on") + 3) : NULL);
            findChar(ip_prefix);
            continue;
        }
        if(strlen(ip_prefix) == 0)
            continue;
        if(strstr(buf, ip_prefix))
        {
            for(unsigned int i = 0; i < sizeof(buf); i++)
            {
                if(buf[i] == ' '){
                    pclose(fd);
                    return 0;
                }
                *(ipstr++) = buf[i];
            }
        }
    }
    pclose(fd);

    return 0;
}

int mount_samba_nfs(IPlay_URL_S *urls, const char* mountpoint, char* target_filename)
{
    ALOGV("mount_samba_nfs()");
    ALOGV("uri     :(%s)", urls->uri);
    ALOGV("hostname:(%s)", urls->hostName);
    ALOGV("username:(%s)", urls->userName);
    ALOGV("password:(%s)", urls->password);
    ALOGV("protocol:(%s)", urls->protocol);
    ALOGV("dir     :(%s)", urls->dir);
    ALOGV("filename:(%s)", urls->fileName);
    ALOGV("isofile :(%s)", urls->isofile);
    ALOGV("filetype:(%s)", urls->fileType);
    ALOGV("port    :(%d)", urls->port);

    int ret = 0;
    char cmdStr[BUFFER_SIZE] = {0};

    umount_samba_nfs(MOUNT_ISO_POINT);
    umount_samba_nfs(mountpoint);

    if (strcasecmp("nfs", urls->protocol) == 0) //nfs
    {
        mkNotExitDir(mountpoint);

        char exportdir[1024] = {0};
        ret = -1;
        strcpy(exportdir, urls->dir);

        while (ret!=0 && strlen(exportdir)>=1)//cyclic mount
        {
            snprintf( cmdStr, BUFFER_SIZE, "-o nolock,tcp  -t nfs \"%s:/%s\" %s", urls->hostName, exportdir, mountpoint);
            ret = HiNSClient::NSMount(cmdStr);
            if (ret!=0 && (strlen(exportdir)>=2) && (exportdir[strlen(exportdir)-1]=='/'))
            {
                exportdir[strlen(exportdir)-1] = 0; //del '/'
                snprintf( cmdStr, BUFFER_SIZE, "-o nolock,tcp  -t nfs \"%s:/%s\" %s", urls->hostName, exportdir, mountpoint);
                ret = HiNSClient::NSMount(cmdStr);
            }
            if (ret!=0)
            {
                while(exportdir[strlen(exportdir)-1]!='/')
                {
                    exportdir[strlen(exportdir)-1] = 0; //del '/'
                }
            }
        }
        char* pReardir = NULL;
        pReardir = strstr(urls->dir, exportdir) + strlen(exportdir);

        if (strcasecmp("bluray",urls->fileType) == 0 || strcasecmp("iso",urls->fileType) == 0)
        {
            sprintf(target_filename, "%s/%s", mountpoint, pReardir);
        }
        else
        {
            sprintf(target_filename, "%s/%s%s", mountpoint, pReardir, urls->fileName);
        }
    }
    else if (strcasecmp("smb",urls->protocol) == 0) //samba
    {
        mkNotExitDir(mountpoint);
        char ip[32] = {0};
        char username[1024] = {0};
        char fulldir[4096] = {0};
        for (int i=0;i<2;i++)
        {
            if (i==0)
            {
                strcpy(username, urls->userName);
            }else if (NULL!=strstr(urls->userName, "\\"))
            {
                strcpy(username, strstr(urls->userName, "\\")+2);
            }
            strcpy(fulldir, urls->dir);
            if ( (strlen(urls->dir)>0)
                &&(fulldir[strlen(urls->dir)-1]=='/') )
            {
                fulldir[strlen(urls->dir)-1] = 0;
            }

            if (hostnametoip(urls->hostName, ip)==0)
            {
                ALOGI("\nsamba:Hostname[%s] IP[%s]", urls->hostName, ip);
                snprintf(cmdStr, BUFFER_SIZE, "-t cifs \"//%s/%s\" %s -o user=%s,pass=%s,iocharset=utf8"
                        ",uid=1001,gid=1001,file_mode=0777,dir_mode=0777",
                        ip, fulldir, mountpoint, username, urls->password);
            }
            else
            {
                snprintf(cmdStr, BUFFER_SIZE, "-t cifs \"//%s/%s\" %s -o user=%s,pass=%s,iocharset=utf8"
                        ",uid=1001,gid=1001,file_mode=0777,dir_mode=0777",
                        urls->hostName, fulldir, mountpoint, username, urls->password);
            }

            ret = HiNSClient::NSMount(cmdStr);
            if (0==ret)
            {
                break;
            }
        }

        if (strcasecmp("bluray", urls->fileType) == 0 || strcasecmp("iso", urls->fileType) == 0)
        {
            sprintf(target_filename, "%s", mountpoint);
        }
        else
        {
            sprintf(target_filename, "%s/%s", mountpoint, urls->fileName);
        }
    }
    else if (strcasecmp("bluray", urls->protocol) == 0) //bluray
    {
        if (strncmp(urls->dir, "/",1) ==0)
        {
            sprintf(target_filename, "%s", urls->dir);
        }
        else
        {
            sprintf(target_filename, "/%s", urls->dir);
        }
    }
    else
    {
        sprintf(target_filename, "%s", urls->uri);
    }


    ALOGV("mount_samba_nfs on [%s]", target_filename);

    if (strcasecmp("iso", urls->fileType) == 0) //iso
    {
        char tmp[2048] = {0};
        sprintf(tmp, "%s/%s", target_filename, urls->isofile);
        sprintf(target_filename, "%s", tmp);
        ret =ISOdoMount(target_filename, MOUNT_ISO_POINT);
        if (0 != ret)
        {
            ALOGV("mount_samba_nfs iso error");
            return -1;
        }
        sprintf(target_filename, "%s", MOUNT_ISO_POINT);
    }

    //bluray
    if (strcasecmp("bluray", urls->protocol) == 0
            || strcasecmp("bluray", urls->fileType) == 0
            || strcasecmp("iso", urls->fileType) == 0)
    {
        int index = 0;
        char bdmvfile[2048] = {0};
        char tmp[2048] = {0};
        sscanf(urls->fileName, "%d.mpls", &index);
        sprintf(bdmvfile, "%s/BDMV/index.bdmv", target_filename);
        sprintf(tmp, "bluray:%s?playlist=%d", target_filename, index);
        sprintf(target_filename, "%s", tmp);

        ALOGV("bdmvfile =(%s) target_filename=(%s)", bdmvfile, target_filename);
        if (access(bdmvfile,0)==0)
        {
            ALOGV("mount_samba_nfs iso on [%s]  target_filename=[%s]", bdmvfile, target_filename);
            return 0;
        }
        /*sprintf(target_filename,"%s/VIDEO_TS/VIDEO_TS.IFO",MOUNT_ISO_POINT);
          if (access(target_filename,0) ==0)
          {
          ALOGV("mount_samba_nfs iso on [%s]",target_filename);
          return 0;
          }*/
        ALOGV("mount_samba_nfs iso error");
        return -1;

    }

    return ret;
}

bool IPlay_init(IPlay_URL_S *urls, void * p_cookie)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if(mount_samba_nfs(urls,MOUNT_POINT,g_newurl) != 0)
    {
        return false;
    }

    if (g_hiMediaPlayer == NULL)
    {
        g_hiMediaPlayer = new HiMediaPlayer(p_cookie);
    }

    return true;
}

void IPlay_release()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    umount_samba_nfs(MOUNT_ISO_POINT);
    umount_samba_nfs(MOUNT_POINT);
    if (g_hiMediaPlayer)
    {
        delete g_hiMediaPlayer;
        g_hiMediaPlayer = NULL;
    }
}

int IPlay_setDataSource(const char *sHeader)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }
    return g_hiMediaPlayer->setDataSource(g_newurl, NULL);
}



int IPlay_prepare()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    return g_hiMediaPlayer->prepare();
}

int IPlay_start()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    return g_hiMediaPlayer->start();
}

int IPlay_stop()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    int ret = -1;
    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    ret = g_hiMediaPlayer->stop();
    return ret;
}

int IPlay_seekTo(int p_position)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    return g_hiMediaPlayer->seekTo(p_position);
}

int IPlay_pause()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    return g_hiMediaPlayer->pause();
}

bool IPlay_isPlaying()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return false;
    }

    return g_hiMediaPlayer->isPlaying();
}

int IPlay_getCurrentPosition(int * p_position)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    return g_hiMediaPlayer->getCurrentPosition(p_position);
}

int IPlay_getFileInfo(HI_FORMAT_FILE_INFO_S **ppstFileInfo)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }
    HI_HANDLE hPlayer = g_hiMediaPlayer->getHandle();
    return HI_SVR_PLAYER_GetFileInfo(hPlayer, ppstFileInfo);
}

int IPlay_getStreamID(HI_SVR_PLAYER_STREAMID_S *streamID)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }
    HI_HANDLE hPlayer = g_hiMediaPlayer->getHandle();
    memset(streamID, 0, sizeof(*streamID));
    return HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_STREAMID, streamID);
}

int IPlay_reset()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    int ret = -1;

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    ret = g_hiMediaPlayer->reset();

    return ret;
}

int IPlay_setLooping(int p_loop)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    return g_hiMediaPlayer->setLooping(p_loop);
}

int IPlay_setVolume(float p_leftVolume, float p_rightVolume)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    return g_hiMediaPlayer->setVolume(p_leftVolume, p_rightVolume);
}

int IPlay_suspend()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    return g_hiMediaPlayer->suspend();
}
int IPlay_resume()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    return g_hiMediaPlayer->resume();
}


void IPlay_setNotifyCallback(void * p_cookie, IPlay_notify_callback_f p_notifyFunc)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return;
    }

    g_hiMediaPlayer->setNotifyCallback(p_cookie, (notify_callback_f)p_notifyFunc);
}


int IPlay_setOutRange(int p_left, int p_top, int p_width, int p_height)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    return g_hiMediaPlayer->setOutRange(p_left, p_top, p_width, p_height);
}

int IPlay_setSurfaceXY(int x,int y)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    return NO_INIT;
    /*if (g_hiMediaPlayer == NULL)
      {
      return NO_INIT;
      }

      return g_hiMediaPlayer->setSurfaceXY(x, y);*/
}

int IPlay_setSurfaceWH (int w,int h)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    return NO_INIT;
    /*if (g_hiMediaPlayer == NULL)
      {
      return NO_INIT;
      }

      return g_hiMediaPlayer->setSurfaceWH(w, h);*/
}

int IPlay_resetOutRange()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    return NO_INIT;
    /*if (g_hiMediaPlayer == NULL)
      {
      return NO_INIT;
      }

      return g_hiMediaPlayer->resetOutRange();*/
}

int IPlay_setVideoRatio(int p_ratio)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    // xbmc do not support now,please call g_hiMediaPlayer->setVideoRatio() to support
    ALOGV("not support IPlay_setVideoRatio",__LINE__, __FUNCTION__);
    return 0;
}

int IPlay_setVideoCvrs(int crvs)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    return g_hiMediaPlayer->setVideoCvrs(crvs);
}

int IPlay_setMute(bool bOnOff)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }
    int iMute = (bOnOff==true)?1:0;

    Parcel request;
    Parcel reply;
    request.writeInt32(CMD_SET_AUDIO_MUTE_STATUS);
    request.writeInt32(iMute);
    request.setDataPosition(0);
    g_hiMediaPlayer->invoke(request, &reply);
    reply.setDataPosition(0);
    return reply.readInt32();
}

int IPlay_tplay(int speed)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);

    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }

    Parcel request;
    Parcel reply;
    request.writeInt32(CMD_SET_FORWORD);
    request.writeInt32(speed);
    request.setDataPosition(0);
    g_hiMediaPlayer->invoke(request, &reply);
    reply.setDataPosition(0);
    return reply.readInt32();
}

//subtitle
int IPlay_invoke(int invokeID, int value)
{
    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }
    Parcel request;
    Parcel reply;
    request.writeInt32(invokeID);
    request.writeInt32(value);
    request.setDataPosition(0);
    g_hiMediaPlayer->invoke(request, &reply);
    reply.setDataPosition(0);

    int ret = reply.readInt32();
    if (value==-1){
        ALOGV("[%4d]%s  ID:%d  ret:%d",__LINE__, __FUNCTION__, invokeID, ret);
    }else{
        ALOGV("[%4d]%s  ID:%d  value:%d ret:%d",__LINE__, __FUNCTION__, invokeID, value, ret);
    }

    return ret;
}

void IPlay_getSubString(unsigned char* pSubString)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    if (g_hiMediaPlayer == NULL)
    {
        return ;
    }
    int ret = g_hiMediaPlayer->getSubString(pSubString);

    ALOGV("[%4d]%s  ret=%d",__LINE__, __FUNCTION__, ret);
    return;
}

void IPlay_SetAudioStream(int iStream)
{
    ALOGV("[%4d]%s  IN  %d",__LINE__, __FUNCTION__,iStream);
    IPlay_invoke(CMD_SET_AUDIO_TRACK_PID,iStream);

    return;
}
int IPlay_GetAudioStream()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }
    Parcel request;
    Parcel reply;
    request.writeInt32(CMD_GET_AUDIO_TRACK_PID);
    request.setDataPosition(0);
    g_hiMediaPlayer->invoke(request, &reply);
    reply.setDataPosition(0);
    int ret = reply.readInt32();
    int audiostream  = reply.readInt32();

    ALOGE("[%4d]%s  ID:%d  audiostream:%d ret:%d",__LINE__, __FUNCTION__, CMD_GET_AUDIO_TRACK_PID, audiostream, ret);
    return audiostream;
}

void IPlay_SetSubTitleDelay(float fValue)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    int subdelay = (int)fValue*1000;

    if (g_hiMediaPlayer == NULL)
    {
        return;
    }
    Parcel request;
    Parcel reply;
    request.writeInt32(CMD_SET_SUB_TIME_SYNC);
    request.writeInt32(0);//video
    request.writeInt32(0);//audio
    request.writeInt32(subdelay);//audio
    request.setDataPosition(0);
    g_hiMediaPlayer->invoke(request, &reply);
    reply.setDataPosition(0);

    ALOGV("[%4d]%s  ID:%d  subdelay:%d   ret=%d",__LINE__, __FUNCTION__, CMD_SET_SUB_TIME_SYNC, subdelay, reply.readInt32());
    return;
}

float IPlay_GetSubTitleDelay()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }
    Parcel request;
    Parcel reply;
    request.writeInt32(CMD_GET_SUB_TIME_SYNC);
    request.setDataPosition(0);
    g_hiMediaPlayer->invoke(request, &reply);
    reply.setDataPosition(0);
    reply.readInt32();//ret
    reply.readInt32();//video
    reply.readInt32();//audio
    float fValue = reply.readInt32()/1000.0;

    ALOGV("[%4d]%s  ID:%d  fValue:%f   ret=%d",__LINE__, __FUNCTION__, CMD_SET_SUB_TIME_SYNC, fValue, reply.readInt32());
    return fValue;
}

int  IPlay_GetSubtitleCount()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }
    HI_HANDLE hPlayer = g_hiMediaPlayer->getHandle();
    HI_FORMAT_FILE_INFO_S* pstFileInfo = NULL;

    int ret = HI_SVR_PLAYER_GetFileInfo(hPlayer, &pstFileInfo);

    if (ret==0)
    {
        int subcount = pstFileInfo->pastProgramInfo->u32SubStreamNum;
        ALOGV("[%4d]%s  subcount=%d",__LINE__, __FUNCTION__, subcount);
        return subcount;
    }

    ALOGE("[%4d]%s  failed ret=%d",__LINE__, __FUNCTION__, ret);
    return ret;
}

int  IPlay_GetSubtitle()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }
    Parcel request;
    Parcel reply;
    request.writeInt32(CMD_GET_SUB_ID);
    request.setDataPosition(0);
    g_hiMediaPlayer->invoke(request, &reply);
    reply.setDataPosition(0);
    reply.readInt32();//ret
    int subIndex = reply.readInt32();//sub index

    ALOGV("[%4d]%s  subIndex=%d",__LINE__, __FUNCTION__, subIndex);
    return subIndex;
}

void IPlay_GetSubtitleName(int iStream, char* pStrSubName)
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    if (g_hiMediaPlayer == NULL)
    {
        return ;
    }
    HI_HANDLE hPlayer = g_hiMediaPlayer->getHandle();
    HI_FORMAT_FILE_INFO_S* pstFileInfo = NULL;

    int ret = HI_SVR_PLAYER_GetFileInfo(hPlayer, &pstFileInfo);

    if (ret==0)
    {
        int subcount = pstFileInfo->pastProgramInfo->u32SubStreamNum;
        if (iStream<subcount && pStrSubName!=NULL)
        {
            memcpy(pStrSubName, pstFileInfo->pastProgramInfo->pastSubStream[iStream].paszLanguage, HI_FORMAT_MAX_LANGUAGE_NUM*HI_FORMAT_LANG_LEN);
            ALOGV("[%4d]%s  %d / %d   %s",__LINE__, __FUNCTION__, iStream, subcount, pStrSubName);
        }
    }

    return;
}

void IPlay_SetSubtitle(int iStream)
{
    ALOGV("[%4d]%s  IN iStream=%d",__LINE__, __FUNCTION__, iStream);
    int ret = IPlay_invoke(CMD_SET_SUB_ID,iStream);

    ALOGV("[%4d]%s  iStream=%d ret=%d",__LINE__, __FUNCTION__, iStream, ret);
    return;
}

bool IPlay_GetSubtitleVisible()
{
    ALOGV("[%4d]%s  IN",__LINE__, __FUNCTION__);
    if (g_hiMediaPlayer == NULL)
    {
        return false;
    }
    int ret = IPlay_invoke(CMD_GET_SUB_DISABLE, -1);

    return (ret==0)?true:false;
}

void IPlay_SetSubtitleVisible(bool bVisible, ANativeWindow* pNativeWindow)
{
    ALOGV("[%4d]%s  IN bVisible=%s",__LINE__, __FUNCTION__,bVisible==true?"true":"false");
    if (g_hiMediaPlayer == NULL)
    {
        return;
    }
    //sp<Surface> surface = create_surface();
    int ret = IPlay_invoke(CMD_SET_SUB_DISABLE, (bVisible==true)?0:1);

    g_hiMediaPlayer->setSubSurface(pNativeWindow, true);

    return;
}

//bool GetSubtitleExtension(unsigned char* pStrSubtitleExtension) { return false; }
int  IPlay_AddSubtitle(const char* strSubPath)
{
    ALOGV("[%4d]%s  IN  strSubPath=%s",__LINE__, __FUNCTION__,strSubPath);
    if (g_hiMediaPlayer == NULL)
    {
        return NO_INIT;
    }
    Parcel request;
    Parcel reply;
    request.writeInt32(CMD_SET_SUB_EXTRA_SUBNAME);
    String16 pstr16(strSubPath, strlen(strSubPath));
    request.writeString16(pstr16);
    request.setDataPosition(0);
    g_hiMediaPlayer->invoke(request, &reply);
    reply.setDataPosition(0);

    ALOGV("[%4d]%s  ret=%d",__LINE__, __FUNCTION__, reply.readInt32());
    return reply.readInt32();
}
//subtitle end

}//extern C
