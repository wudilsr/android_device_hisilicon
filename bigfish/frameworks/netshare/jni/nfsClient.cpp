#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <android/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Samba.h"
#include <signal.h>
#include <setjmp.h>

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "jni.h"
#include "JNIHelp.h"
#include <android_runtime/AndroidRuntime.h>
#include "HiNSClient.h"
#include "IHiNSService.h"

#if 1
#define NFS_DEBUG_PF
#endif

#ifdef NFS_DEBUG_PF
#define LOG_TAG "------Nfs search WARN--------"
#define DB_LOG(...) __android_log_print(ANDROID_LOG_WARN , LOG_TAG, __VA_ARGS__)
#else
#define DB_LOG(x,...)
#endif

#define SLOGE(...)  __android_log_print(ANDROID_LOG_ERROR  , "------ Nfs search ERROR--------", __VA_ARGS__)
#define NFS_ARP_FILE "/mnt/.nfs_search_arp"
#define CMDLEN  256
#define TMPLEN  1024

/*		C PLUS PLUS		*/
#include <string>
#include <cstdlib>
#include <list>
#include <sstream>
using namespace std ;
using namespace android ;

typedef struct {
    string path ;
    string mountPoint ;
} NFS_MOUNT ;

typedef struct {
    string ip ;
    string shareDir ;
} NFS_SEARCH ;

vector<NFS_SEARCH*> nsr ;
vector<NFS_SEARCH*>::iterator numSr;

vector<NFS_MOUNT*> nm ;
vector<NFS_MOUNT*>::iterator numMount;

int dirnum = -1;
static bool findIpScan()
{
    DIR *d;
    int pcmd;
    struct dirent *de;
    char cmdStr[CMDLEN] = {0};
    bool val = false;
    int num = 0 ;
    d = opendir("/sys/class/net");
    if(d == NULL) return val;
    while((de = readdir(d))) {
        if((de->d_name[0] == '.') || (0 == strcmp(de->d_name,"lo"))) continue;
        if(0 == num ){
            snprintf( cmdStr, sizeof(cmdStr), "--interface=%s -l > %s", de->d_name, NFS_ARP_FILE);
        }else {
            snprintf( cmdStr, sizeof(cmdStr), "--interface=%s -l >> %s", de->d_name, NFS_ARP_FILE);
        }
		if(0 == HiNSClient::NSSh(HI_NS_CMD_TYPE_SCANM,cmdStr)) {
            val = true ;
            DB_LOG("true");
        }
        num ++ ;
        memset(cmdStr,0,CMDLEN);
    }
    closedir(d);
    return val;
}

JNIEXPORT static jint JNICALL  Java_com_hisilicon_android_nfsClient_init(JNIEnv *env, jobject obj)
{
    FILE * fp;
    char tmp[TMPLEN]={0};
    if((fp = popen("mount","r"))==NULL){
        SLOGE("check mount error !");
        return -1;
    }
    nm.clear();
    while(fgets(tmp,sizeof(tmp),fp)!= NULL){
        if(strstr(tmp," nfs ")){
            NFS_MOUNT * index = new NFS_MOUNT;
            index->path = strtok(tmp," ");
            index->mountPoint = strtok(NULL," ");
            DB_LOG("init index->path=%s,index->mountPoint=%s",(index->path).c_str(),(index->mountPoint).c_str());
            nm.push_back(index);

            if((index->mountPoint).length()<=23)//debug for mount by cmdline and mountPoint string too short.
                continue;

            string k((index->mountPoint),23);
            dirnum = ((atoi(k.c_str())) > dirnum) ? atoi(k.c_str()): dirnum ;
        }
    }
    pclose(fp);
    return 0;
}

JNIEXPORT jstring JNICALL Java_com_hisilicon_android_nfsClient_getWorkgroups(JNIEnv *env, jobject obj)
{
    int ret = -1;
    FILE *farp;
    FILE *fshow;
    char cmdStr[CMDLEN] = {0};
    char arpLineTmp[TMPLEN] = {0};
    char showLineTmp[TMPLEN] = {0};
    char* aliveip = NULL;
	unsigned cun = 0 ;
    string shareIp;

	nsr.clear();
	if(!findIpScan()){
		SLOGE("arp-scan error !");
		return env->NewStringUTF("ERROR");
	}
	while(access(NFS_ARP_FILE,F_OK) && cun<6){
		usleep(500);
		cun++;
	}
	farp=fopen(NFS_ARP_FILE,"r");
	if(!farp)
		SLOGE("(getWorkgroups,%d)(%s) !",__LINE__,strerror(errno));
	while(fgets(arpLineTmp,sizeof(arpLineTmp),farp)!= NULL)
	{
		if(strstr(arpLineTmp,"last octet is VRID")){
			continue;
		}
        aliveip = strtok(arpLineTmp,"\t");
        DB_LOG("aliveip=%s",aliveip);
        memset(cmdStr,0,CMDLEN);
        memset(showLineTmp,0,TMPLEN);
        snprintf( cmdStr, sizeof(cmdStr), "%s %s","/system/bin/showmount -e",aliveip);
        if((fshow = popen(cmdStr,"r")) == NULL){
            SLOGE("showmount \"%s\" error !",aliveip);
        }
        if(fshow==NULL) continue ;
        if(fgets(showLineTmp,sizeof(showLineTmp),fshow)!= NULL){
            if(strstr(showLineTmp,"Export list for")){
                if(shareIp.find(aliveip)!=string::npos){
                    DB_LOG("find ip continue");
                    pclose(fshow);
                    memset(arpLineTmp,0,TMPLEN);
                    continue ;
                }
                NFS_SEARCH * sr = new NFS_SEARCH() ;
                sr->ip = string(aliveip);
                shareIp = shareIp + "|" + sr->ip;
                sr->shareDir = string("ip:")+sr->ip ;
                while(fgets(showLineTmp,sizeof(showLineTmp),fshow)!= NULL)
                {
                    sr->shareDir = sr->shareDir + "|" + string(strdup(strtok(showLineTmp," ")));
                }
                nsr.push_back(sr);
            }
        }
        pclose(fshow);
        memset(arpLineTmp,0,TMPLEN);
    }
	HiNSClient::NSSh(HI_NS_CMD_TYPE_RMM,NFS_ARP_FILE);
    fclose(farp);
    DB_LOG("shareip=%s",shareIp.c_str()+1);
    return env->NewStringUTF((shareIp.c_str()+1)) ;

}

JNIEXPORT jstring JNICALL Java_com_hisilicon_android_nfsClient_getShareFolders(JNIEnv *env, jobject obj, jstring ip)
{
    const char * Ip = env->GetStringUTFChars(ip,NULL);
    for(numSr=nsr.begin();numSr!=nsr.end();numSr++){
        if((((*numSr)->ip).compare(Ip)) == 0){
            return env->NewStringUTF(((*numSr)->shareDir).c_str());
        }
    }
    return env->NewStringUTF("ERROR");
}

JNIEXPORT jint JNICALL Java_com_hisilicon_android_nfsClient_mount(JNIEnv *env, jobject obj, jstring path)
{
    FILE * fm;
    const char * Path = env ->GetStringUTFChars(path,NULL);
    DB_LOG("mount Path=%s",Path);
    for(numMount=nm.begin();numMount!=nm.end();numMount++){
        DB_LOG("mount list numMount->path=%s,numMount->mountpoint=%s",((*numMount)->path).c_str(),((*numMount)->mountPoint).c_str());
        if(((*numMount)->path).compare(Path) == 0)
            return 0;
    }
    char cmdStr[CMDLEN] = {0};
    char showLineTmp[TMPLEN] = {0};
    char mountPoint[CMDLEN] = {0};
    FILE * pm;
    dirnum ++ ;
    snprintf( mountPoint, sizeof(mountPoint), "/mnt/nfsShare/nfs_share%d",dirnum);
    snprintf( cmdStr, sizeof(cmdStr), "%s -p %s","/system/bin/mkdir",mountPoint);
    if((pm = popen(cmdStr,"r")) == NULL){
        SLOGE("mkdir \"%s\" error !",mountPoint);
        return -1;
    }
    pclose(pm);
    memset(cmdStr,0,CMDLEN);
    snprintf( cmdStr, sizeof(cmdStr), "%s %s %s","-o nolock,tcp",Path ,mountPoint);
    DB_LOG("mount cmdstr=%s",cmdStr);
	HiNSClient::NSMount(cmdStr);

    DB_LOG("add new mountlist Path=%s,mountPoint=%s",Path,mountPoint);
    NFS_MOUNT * mountlist =new NFS_MOUNT;
    mountlist->path = Path ;
    mountlist->mountPoint = mountPoint ;
    nm.push_back(mountlist);
    return 0;
}

JNIEXPORT jint JNICALL Java_com_hisilicon_android_nfsClient_unmount(JNIEnv *env, jobject obj, jstring mntpoint)
{
    const char * mntPoint = env->GetStringUTFChars(mntpoint,NULL);
    DB_LOG("umount mntPoint=%s",mntPoint);
    if(0 == strcasecmp(mntPoint,"all")){
        for(numMount=nm.begin();numMount!=nm.end();numMount++){
            DB_LOG("umount mntPoint=%s",((*numMount)->mountPoint).c_str());
            if(HiNSClient::NSUnMount(((*numMount)->mountPoint).c_str()) == 0 ){
                if( HiNSClient::NSSh(HI_NS_CMD_TYPE_RMM,((*numMount)->mountPoint).c_str()) != 0){
                    SLOGE("umount \"%s\" error !,is busy",((*numMount)->mountPoint).c_str() );
                }
            }
        }
        nm.clear();
        return 0 ;
    }else{
        for(numMount=nm.begin();numMount!=nm.end();numMount++){
            if(((*numMount)->mountPoint).compare(mntPoint) == 0){
            	if( HiNSClient::NSUnMount(mntPoint) == 0 ){
                	if( HiNSClient::NSSh(HI_NS_CMD_TYPE_RMM,mntPoint) != 0){
                        SLOGE("umount \"%s\" error !,is busy",mntPoint);
                        return -1;
                    }
                    DB_LOG("del mountlist=%s",mntPoint);
                    numMount = nm.erase(numMount);
                    return 0 ;
                }
                return -1 ;
            }
        }
    }
    return 0;
}

JNIEXPORT jstring JNICALL Java_com_hisilicon_android_nfsClient_getMountPoint(JNIEnv *env, jobject obj, jstring path)
{
    const char * Path = env->GetStringUTFChars(path,NULL);
    for(numMount=nm.begin();numMount!=nm.end();numMount++){
        if(((*numMount)->path).compare(Path) == 0){
            return env->NewStringUTF(((*numMount)->mountPoint).c_str());
        }
    }
    return env->NewStringUTF("ERROR");
}

static const JNINativeMethod g_methods[] = {
    { "getWorkgroups", "()Ljava/lang/String;", (void *)Java_com_hisilicon_android_nfsClient_getWorkgroups },
    { "getShareFolders", "(Ljava/lang/String;)Ljava/lang/String;", (void *)Java_com_hisilicon_android_nfsClient_getShareFolders },
    { "mount", "(Ljava/lang/String;)I", (void *)Java_com_hisilicon_android_nfsClient_mount },
    { "nfsInit", "()I", (void *)Java_com_hisilicon_android_nfsClient_init },
    { "unmount", "(Ljava/lang/String;)I", (void *)Java_com_hisilicon_android_nfsClient_unmount },
    { "getMountPoint", "(Ljava/lang/String;)Ljava/lang/String;", (void *)Java_com_hisilicon_android_nfsClient_getMountPoint },
};

int register_com_hisilicon_android_nfsClient(JNIEnv* env)
{
    jclass clazz;
    clazz = env->FindClass("com/hisilicon/android/netshare/NfsClient");
    if (clazz == NULL)
        return JNI_FALSE;
    if (env->RegisterNatives(clazz, g_methods, NELEM(g_methods)) < 0)
        return JNI_FALSE;
    return JNI_TRUE;
}
