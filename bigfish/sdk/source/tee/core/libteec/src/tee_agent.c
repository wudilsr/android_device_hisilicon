#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h> /*for errno*/
#include <sys/types.h> /*for open close*/
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h> /*for ioctl*/
#include <sys/mman.h> /*for mmap*/
#include <signal.h>
#include <sys/time.h>
#include <sys/mount.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/statfs.h>

//debug switch
#define LOG_NDEBUG 0
#define LOG_TAG "teecd"
#define PAGE_SIZE 4096 //f00216599
#ifdef _ANDROID_PLATFORM
/*DTS2014040405270 chown sec_stroage_data q00209673 */
#include <private/android_filesystem_config.h>
#include <cutils/log.h>
#include <cutils/properties.h>
#endif

#include "tc_ns_client.h"
//add by q00209673 for bootloaderlock status
#include "tee_nv_info.h"
#include "tee_client_storage_api.h"
#include "tee_ca_daemon.h"

//#ifdef K3V3_FPGA
//#define LOGE ALOGE
//#define LOGV
//#endif
#define AID_SYSTEM        1000
//#define ANDROID

#ifdef _ANDROID_PLATFORM
#if LOG_NDEBUG
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define LOGV(...)
#endif
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else//else _ANDROID_PLATFORM
#if LOG_NDEBUG
#define LOGV(fmt, args...) printf("[debug]%s %s: " fmt "", LOG_TAG, __FUNCTION__, ## args)
#else
#define LOGV(...)
#endif
#define LOGE(fmt, args...) printf("[error]%s %s: " fmt "", LOG_TAG, __FUNCTION__, ## args)
#endif
#define FILE_NAME_MAX_BUF 256
#ifndef _ANDROID_PLATFORM
//added by fangjian00208632
typedef void (*sighandler_t)(int);
#endif

//static func declare
static void agent_exit(unsigned int id, int fd);

typedef enum{
    sec_open,
    sec_close,
    sec_read,
    sec_write,
    sec_seek,
    sec_remove,
    sec_truncate,
    sec_rename,
    sec_create,
    sec_info,
    sec_access,
    sec_access2,
    sec_fsync,
    sec_cp,
    sec_diskusage
}fs_cmd_t;

typedef enum{
    sec_nv_info,//add by q00209673 for bootloaderlock status in nv partition
    sec_get_time,
}misc_cmd_t;

struct sec_storage_t{
    fs_cmd_t cmd;   //for s to n
    int32_t ret;    //fxxx call's return
    int32_t ret2;   //just for fread, judge end-of-file or error
    uint32_t userid;
    uint32_t magic;
    uint32_t error;
    union args1{
        struct{
            char mode[4];
            uint32_t name_len;
            uint32_t name[1];   /* change name[0] --> name[1], for pc-lint */
        }open;
        struct{
            int32_t fd;
        }close;
        struct{
            int32_t fd;
            uint32_t count;
            uint32_t buffer[1]; /* the same as name[0] --> name[1] */
        }read;
        struct{
            int32_t fd;
            uint32_t count;
            uint32_t buffer[1];
        }write;
        struct{
            int32_t fd;
            int32_t offset;
            uint32_t whence;
        }seek;
        struct{
            uint32_t name_len;
            uint32_t name[1];
        }remove;
        struct{
            uint32_t len;
            uint32_t name_len;
            uint32_t name[1];
        }truncate;
        struct{
            uint32_t old_name_len;
            uint32_t new_name_len;
            uint32_t buffer[1];   //old_name + new_name
        }rename;
        struct{
            uint32_t from_path_len;
            uint32_t to_path_len;
            uint32_t buffer[1];   //from_path+to_path
        }cp;
        struct{
            char mode[4];
            uint32_t name_len;
            uint32_t name[1];
        }create;
        struct{
            int32_t fd;
            uint32_t cur_pos;
            uint32_t file_len;
        }info;
        struct{
            int mode;
            uint32_t name_len;
            uint32_t name[1];
        }access;
        struct{
            int32_t fd;
        }fsync;
        struct{
            uint32_t sec_storage;
            uint32_t data;
        }diskusage;
    }args;
};

struct misc_control_t{
    misc_cmd_t cmd;   //for s to n
    int32_t ret;
    int32_t magic;
    union args2{
        //add by q00209673 for bootloader lock status in nv partition
        struct{
            uint8_t bootloader_info[WIDEVINE_NV_WVLOCK_SIZE];
        }nv_info;
        struct{
            uint32_t seconds;
            uint32_t millis;
            char time_str[30];
        }get_time;
    }args;
};

//added by fangjian00208632:USER_DATA_DIR must end with '/'
#ifdef CFG_TEE_STORAGE_DIR
#define USER_DATA_DIR CFG_TEE_STORAGE_DIR
#else
#define USER_DATA_DIR "/data/"
#endif

#define TRANS_BUFF_SIZE (4*1024)    //agent transfer share buffer size
/*when reset to factory mode, keep the data in this patition*/
#define SEC_STORAGE_ROOT_DIR    USER_DATA_DIR"/sec_storage/"
/*when reset to factory mode, clear the data in this patition*/
#define SEC_STORAGE_DATA_DIR    USER_DATA_DIR"/sec_storage_data/"

#define ROOT_DIR_PERM   (S_IRUSR|S_IWUSR)   //0600 only root can read and write sec_storage folder
#define SEC_STORAGE_PARTITION "/dev/block/platform/hi_mci.0/by-name/securetystorage"
#define SFS_PARTITION_PERSISTENT "sec_storage"
#define SFS_PARTITION_TRANSIENT "sec_storage_data"

struct opened_file{
    FILE* file;
    struct opened_file *next;
    struct opened_file *prev;
};

// open file list head
struct opened_file *g_first_file=(struct opened_file *)NULL;

/* record the current userid */
static uint32_t userid = 0;
static uint32_t set_current_userid(uint32_t id) {
    userid = id;
    return userid;
}
static uint32_t get_current_userid() {
    return userid;
}

/* add to tail */
static void add_open_file(struct opened_file *new_file)
{
    if(g_first_file == NULL){
        g_first_file = new_file;
        new_file->next = new_file;
        new_file->prev = new_file;
    }else{
        g_first_file->prev->next = new_file;
        new_file->prev = g_first_file->prev;
        new_file->next = g_first_file;
        g_first_file->prev = new_file;
    }
}

static void del_open_file(struct opened_file *file)
{
    struct opened_file *next;

    next = file->next;

    if(file == next){   //only 1 node
        g_first_file = NULL;
    }else{
        if(file == g_first_file)
            g_first_file = file->next;
        next->prev = file->prev;
        file->prev->next = next;
    }
}

static int find_open_file(int fd, struct opened_file** file)
{
    struct opened_file* p=g_first_file;
    int find_flag=0;

    if(p != NULL){
        do{
#ifdef _ANDROID_PLATFORM
            if(p->file->_file == fd){
#else
			if(fileno(p->file) == fd){
#endif
                find_flag = 1;
                break;
            }
            p = p->next;
        }while(p != g_first_file);
    }

    if(!find_flag)
        p = NULL;
    *file = p;

    return find_flag;
}

// smc dev
static int fs_fd=0, misc_fd=0;
#ifdef TEE_SUPPORT_RPMB_DEVICE
static int rpmb_agent_fd = 0, rpmb_device_fd = 0;
#endif
/*
 * if agent exit accidently, this handler do some clean work.
 */
static void crash_handler(int signum)
{
    int ret;
#ifdef DEBUG_ON
    char buff[20];
    int fd;

    fd = open("/dev/ttyAMA0",O_RDWR);
    snprintf(buff, sizeof(buff), "-->crash sig=%d\n", signum);
    write(fd, buff, strlen(buff) + 1);
    close(fd);
#endif
    LOGE("crash signal num = %d\n", signum);

#if 0//deleted by fangjian00208632
    ret = ioctl(fs_fd, TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE, AGENT_FS_ID);
    if(ret){
        LOGE("crash_handler:fs agent send reponse failed\n");
    }
    ret = ioctl(misc_fd, TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE, AGENT_MISC_ID);
    if(ret){
        LOGE("crash_handler:fs agent send reponse failed\n");
    }
#endif
#ifdef TEE_SUPPORT_RPMB_DEVICE
    if (rpmb_device_fd != -1) {
        close(rpmb_device_fd);
        ret = ioctl(rpmb_agent_fd, TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE, AGENT_RPMB_ID);
        if(ret){
            LOGE("crash_handler:rpmb agent send reponse failed\n");
        }
    }
#endif
#ifdef TEE_SUPPORT_SOCKET
    ret = ioctl(socket_agent_fd, TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE, AGENT_MISC_ID);
    if(ret){
        LOGE("crash_handler:socket agent send reponse failed\n");
    }
#endif
    agent_exit(AGENT_FS_ID, fs_fd);
    agent_exit(AGENT_MISC_ID, misc_fd);
#ifdef TEE_SUPPORT_RPMB_DEVICE
    if (rpmb_device_fd != -1)
        agent_exit(AGENT_RPMB_ID, rpmb_agent_fd);
#endif
#ifdef TEE_SUPPORT_SOCKET
    socket_agent_exit();
    agent_exit(AGENT_SOCKET_ID, socket_agent_fd);
#endif
    exit(0);
}
/*DTS2014040405270 chown sec_stroage_data q00209673 begin */
/*
* path:file or dir to change own
* flag: 0(dir);1(file)
*/
static void chown_sec_storage_data_to_system(char *path, int flag)
{
    int ret = 0;
    /*check path is SEC_STORAGE_ROOT_DIR or SEC_STORAGE_DATA_DIR,
    * we only need to change SEC_STORAGE_DATA_DIR from root to system
    */
    if(strstr(path, "sec_storage_data")){
	    ret = chown(path, AID_SYSTEM, AID_SYSTEM);
	    if (ret < 0)
		    LOGE("chown erro\n");

	    if(flag){
		    ret = chmod(path, S_IRUSR|S_IWUSR);
		    if (ret < 0)
			    LOGE("chmod erro\n");
	    }else{
		    ret = chmod(path, S_IRUSR|S_IWUSR|S_IXUSR);
		    if (ret < 0)
			    LOGE("chmod erro\n");
	    }
    }
}
/*DTS2014040405270 chown sec_stroage_data q00209673 end */

/*static int find_open_file(int fd, struct opened_file** file)
{
    struct opened_file* sel_file;
    int find_flag=0;

    list_for_each_entry(sel_file, &g_file_list, head){
        if(fd == sel_file->file->_file){
            find_flag = 1;
            break;
        }
    }

    if(find_flag)
        *file = sel_file;

    return find_flag;
}*/

/*
* path:file path name.
* e.g. sec_storage_data/app1/sub1/fileA.txt
* then mkdir_r will make dir sec_storage_data, app1 and sub1.
*/
int mkdir_r(const char *path) {
    if (path == NULL) {
            return -1;
    }
    char *temp = strdup(path);
    char *pos = temp;
    if (temp == NULL) {
        LOGE("strdup error\n");
        return -1;
    }
    /* 去掉开头的 './' 或 '/' */
    if (strncmp(temp, "/", 1) == 0) {
        pos += 1;
    } else if (strncmp(temp, "./", 2) == 0) {
        pos += 2;
    }
    /* 循环创建目录 */
    /* 如果最后一级是文件名，不是以'/'结尾，
    遇到'\0'就中止循环，
    因此不会创建与文件名相同的目录 */
    for ( ; *pos != '\0'; ++ pos) {
        if (*pos == '/') {
            *pos = '\0';
#if 0
            if (0 == access(temp, F_OK)) {
                *pos = '/';
                continue;
            }
            if (mkdir(temp, ROOT_DIR_PERM) != 0) {
                LOGE("mkdir %s fail\n", temp);
                free(temp);
                return -1;
            }
#endif
        mkdir(temp, ROOT_DIR_PERM);
            /*DTS2014040405270 chown sec_stroage_data q00209673 */
#ifdef _ANDROID_PLATFORM//hisi_linux no need do chown:by fangjian 00208632
            chown_sec_storage_data_to_system(temp, 0);
#endif
            LOGV("for %s\n", temp);
            *pos = '/';
        }
    }

    /*如果最后一级字符串是目录名不是文件名，
    则需要打开下面的屏蔽代码*/
    /*
    if (*(pos - 1) != '/') {
        LOGV("if %s\n", temp);
        mkdir(temp, ROOT_DIR_PERM);
    }
    */
    
    free(temp);
    return 0;
}

#define FW_SHOW_MULTIUSERUI "fw.show_multiuserui"
#define FW_MAX_USERS "fw.max_users"
static int system_support_multi_users()
{
#if 0 
    char prop_show_multiuser[PROPERTY_VALUE_MAX] = {0};
    char prop_max_users[PROPERTY_VALUE_MAX] = {0};
    int multi_user = 0, max_users = 0;

    if(!(property_get(FW_SHOW_MULTIUSERUI, prop_show_multiuser, "0"))){
        LOGE("property %s is invalid\n", FW_SHOW_MULTIUSERUI);
        return 0;
    }
    if(!(property_get(FW_MAX_USERS, prop_max_users, "0"))){
        LOGE("property %s is invalid\n", FW_MAX_USERS);
        return 0;
    }

    multi_user = atoi(prop_show_multiuser);
    max_users = atoi(prop_max_users);
    if (multi_user == 1 && max_users > 1)
        return 1;
    else
        return 0;
#endif
    return 0;
}

/*
 * example for join_file_name:
 *
 * name                         userid        path
 * -------------------------------------------------------------------------
 * abc/def                      DC          /data/sec_storage/abc/def
 * sec_storage/abc/def          DC          /data/sec_storage/abc/def
 * sec_storage_data/abc/def     0           /data/sec_storage_data/abc/def
 * sec_storage_data/abc/def     1           /data/sec_storage_data/1/abc/def
 */
static int join_file_name(const char* name, char *path)
{
    if(name == NULL)
        return -1;

    strncpy(path, USER_DATA_DIR, sizeof(USER_DATA_DIR));
#ifdef _ANDROID_PLATFORM
    /*If the path name does not start with sec_storage or sec_storage_data, add sec_storage str for the path*/
    if ((name == strstr(name, SFS_PARTITION_TRANSIENT)) || (name == strstr(name, SFS_PARTITION_PERSISTENT)))
        strncat(path, name, strlen(name)+1);
    else {
        strncat(path, SFS_PARTITION_PERSISTENT, strlen(SFS_PARTITION_PERSISTENT)+1);
        strncat(path, "/", strlen("/")+1);//add "/" for path
        strncat(path, name, strlen(name)+1);
    }
#else
    /*for hisi_linux, only use sec_storage path:by fangjian 00208632 2015-07-24*/
    if (name == strstr(name, SFS_PARTITION_PERSISTENT"/"))
        strncat(path, name, strlen(name)+1);
    else {
        strncat(path, SFS_PARTITION_PERSISTENT, strlen(SFS_PARTITION_PERSISTENT)+1);
        strncat(path, "/", strlen("/")+1);//add "/" for path
        strncat(path, name, strlen(name)+1);
    }
#endif
    LOGV("joined path is \"%s\"\n", path);

    return 0;
}

static int is_file_exist(const char* name)
{
    struct stat statbuf;

    if(stat(name, &statbuf)){
        if(errno == ENOENT) //file not exist
            return 0;
        else{
            LOGE("file stat failed\n");
            return 1;
        }
    }

    return 1;
}

static void open_work(struct sec_storage_t* trans_control)
{
    struct opened_file *sel_file;
    FILE* pFile;
    char name_buff[256];

    set_current_userid(trans_control->userid);
    if(!join_file_name((char*)(trans_control->args.open.name), name_buff)){
        if(trans_control->cmd == sec_create){  //create a exist file, remove it at first
            strncpy(trans_control->args.open.mode, "w+", 4);
        }else{
            if(is_file_exist(name_buff) == 0){  //open a nonexist file, return fail
                LOGE("file(%s) not exist, open failed\n", name_buff);
                trans_control->ret = -1;
                trans_control->error = ENOENT;
                return;
            }
        }

        /*mkdir -p for new create files*/
        if (mkdir_r(name_buff)) {
		    LOGE("mkdir_r(%s) fail\n", name_buff);
            trans_control->ret = -1;
            trans_control->error = errno;
            return;
        }

        pFile = fopen(name_buff, trans_control->args.open.mode);
        if(pFile == NULL){
            LOGE("open file(%s) with flag(%s) failed: %s\n",
                name_buff, trans_control->args.open.mode, strerror(errno));
            trans_control->ret = -1;
            trans_control->error = errno;
        }else{
            /*DTS2014040405270 chown sec_stroage_data q00209673 */
#ifdef _ANDROID_PLATFORM//hisi_linux no need do chown:by fangjian 00208632
            chown_sec_storage_data_to_system(name_buff, 1);
#endif
#ifdef _ANDROID_PLATFORM
            LOGV("open file(%s) success : fd = %d\n", (char*)(trans_control->args.open.name), pFile->_file);
#else
			LOGV("open file(%s) success : fd = %d\n", (char*)(trans_control->args.open.name), fileno(pFile));
#endif
            sel_file = (struct opened_file*)malloc(sizeof(struct opened_file));
            if(!sel_file){
                LOGE("malloc opened_file failed\n");
                trans_control->ret = -1;
            }else{
                sel_file->file = pFile;
#ifdef _ANDROID_PLATFORM
                trans_control->ret = sel_file->file->_file;  //return fileno
#else
				trans_control->ret = fileno(sel_file->file);  //return fileno
#endif
                //list_add(&g_file_list, &sel_file->head);
                add_open_file(sel_file);
            }
        }
    }else{
        //NEVER in this case
        trans_control->ret = -1;
    }
}

static void close_work(struct sec_storage_t* trans_control)
{
    int ret;
    struct opened_file *sel_file;

    if(find_open_file(trans_control->args.close.fd, &sel_file)){
        ret = fclose(sel_file->file);
        trans_control->ret = ret;
        if(ret == 0){
            LOGV("close file(%d) success\n", trans_control->args.close.fd);
            //list_del(&sel_file->head);
            del_open_file(sel_file);
            free(sel_file);
        }else{
            LOGE("close file(%d) failed: %s\n", trans_control->args.close.fd, strerror(errno));
            trans_control->error = errno;
        }
    }else{
        LOGE("can't find opened file(fileno = %d)\n", trans_control->args.close.fd);
        trans_control->ret = -1;
        trans_control->error = EBADF;
    }
}

static void read_work(struct sec_storage_t* trans_control)
{
    struct opened_file *sel_file;
    size_t count;

    if(find_open_file(trans_control->args.read.fd, &sel_file)){
        count = fread((void*)(trans_control->args.read.buffer), 1,
                    trans_control->args.read.count, sel_file->file);
        trans_control->ret = count;
        if(count < trans_control->args.read.count){
            if(feof(sel_file->file)){
                trans_control->ret2 = 0;
                LOGV("read end of file\n");
            }else{
                trans_control->ret2 = -1;
                trans_control->error = errno;
                LOGE("read file failed: %s\n", strerror(errno));
            }
        }else{
            trans_control->ret2 = 0;
            LOGV("read file success, content len=%d\n", count);
        }
    }else{
        trans_control->ret = 0;
        trans_control->ret2 = -1;
        trans_control->error = EBADF;
        LOGE("can't find opened file(fileno = %d)\n", trans_control->args.read.fd);
    }
}

static void write_work(struct sec_storage_t* trans_control)
{
    struct opened_file *sel_file;
    size_t count;

    if(find_open_file(trans_control->args.write.fd, &sel_file)){
        count = fwrite((void*)(trans_control->args.write.buffer), 1,
                             trans_control->args.write.count, sel_file->file);
        if(count < trans_control->args.write.count) {
            LOGE("write file failed: %s\n", strerror(errno));
            trans_control->ret = count;
            trans_control->error = errno;
            return;
        }

        //TODO need?
        if(fflush(sel_file->file) != 0) {
            LOGE("fflush file failed: %s\n", strerror(errno));
            trans_control->ret = 0;
            trans_control->error = errno;
        } else {
            trans_control->ret = count;
        }

        //TODO need?
        if(fflush(sel_file->file) != 0)
            LOGE("fflush file failed\n");
    }else{
        LOGE("can't find opened file(fileno = %d)\n", trans_control->args.write.fd);
        trans_control->ret = 0;
        trans_control->error = EBADF;
    }
}

static void seek_work(struct sec_storage_t* trans_control)
{
    int ret;
    struct opened_file *sel_file;

    if(find_open_file(trans_control->args.seek.fd, &sel_file)){
        ret = fseek(sel_file->file, trans_control->args.seek.offset, trans_control->args.seek.whence);
        trans_control->ret = ret;
        if(ret){
            LOGE("seek file failed: %s\n", strerror(errno));
            trans_control->error = errno;
        }else{
            LOGV("seek file success\n");
        }
    }else{
        LOGE("can't find opened file(fileno = %d)\n", trans_control->args.seek.fd);
        trans_control->ret = -1;
        trans_control->error = EBADF;
    }
}

/* return -1 on failure, with errno set to the first error */
int unlink_recursive(const char* name)
{
    struct stat st;
    DIR *dir;
    struct dirent *de;
    int fail = 0;
    int ret = 0;
    char dn[PATH_MAX];

    /* is it a file or directory? */
    if (lstat(name, &st) < 0){
        LOGE("lstat %s failed, errno is %x\n", name, errno);
        return -1;
    }
    /* a file, so unlink it */
    if (!S_ISDIR(st.st_mode)){
        if(unlink(name) < 0){
            LOGE("unlink %s failed, errno is %d\n", name, errno);
            return -1;
        }
        return 0;
    }
    /* a directory, so open handle */
    dir = opendir(name);
    if (dir == NULL){
        LOGE("dir %s open failed\n", name);
        return -1;
    }
    /* recurse over components */
    errno = 0;
    while ((de = readdir(dir)) != NULL) {
        if (!strcmp(de->d_name, "..") || !strcmp(de->d_name, "."))
            continue;
        snprintf(dn, sizeof(dn), "%s/%s", name, de->d_name);
        if (unlink_recursive(dn) < 0) {
            LOGE("loop unlink_recursive() failed, there are read-only file\n");
            fail = 1;
            break;
        }
        errno = 0;
    }
    /* in case readdir or unlink_recursive failed */
    if (fail || errno < 0) {
        int save = errno;
        closedir(dir);
        errno = save;
        LOGE("fail is %d, errno is %d\n", fail, errno);
        return -1;
    }

    /* close directory handle */
    if (closedir(dir) < 0){
        LOGE("closedir %s failed, errno is %d\n", name, errno);
        return -1;
    }
    /* delete target directory */
    if(rmdir(name) < 0){
        LOGE("rmdir %s failed, errno is %d\n", name, errno);
        return -1;
    }
    return 0;
}

static void remove_work(struct sec_storage_t* trans_control)
{
    int ret;
    char name_buff[256];

    set_current_userid(trans_control->userid);
    if(!join_file_name((char*)(trans_control->args.remove.name), name_buff)){
        ret = unlink_recursive(name_buff);
        trans_control->ret = ret;
        if(ret) {
            LOGE("remove file failed: %s\n", strerror(errno));
            trans_control->error = errno;
        } else {
            LOGV("remove file success\n");
        }
    }else{
        trans_control->ret = -1;
    }
}

static void truncate_work(struct sec_storage_t* trans_control)
{
    int ret;
    char name_buff[256];

    set_current_userid(trans_control->userid);
    if(!join_file_name((char*)(trans_control->args.truncate.name), name_buff)){
        ret = truncate(name_buff, trans_control->args.truncate.len);
        trans_control->ret = ret;
        if(ret){
            LOGE("truncate file failed: %s\n", strerror(errno));
            trans_control->error = errno;
        } else {
            LOGV("truncate file success\n");
        }
    }else{
        trans_control->ret = -1;
    }
}

static void rename_work(struct sec_storage_t* trans_control)
{
    int ret;
    char name_buff[256], name_buff2[256];

    set_current_userid(trans_control->userid);
    if(!join_file_name((char*)(trans_control->args.rename.buffer), name_buff) &&
        !join_file_name((char*)(trans_control->args.rename.buffer) + trans_control->args.rename.old_name_len, name_buff2)){
        ret = rename(name_buff, name_buff2);
        trans_control->ret = ret;
        if(ret) {
            LOGE("rename file failed: %s\n", strerror(errno));
            trans_control->error = errno;
        } else {
            LOGV("rename file success\n");
        }
    }else{
        trans_control->ret = -1;
    }
}

#define MAXBSIZE 65536

static int copy_file(const char *from_path, const char *to_path)
{
    int from_fd = -1, to_fd = -1;
    ssize_t rcount, wcount;
    static char buf[MAXBSIZE];
    struct stat from_stat;
    int ret;

    if ((from_fd = open(from_path, O_RDONLY, 0)) == -1) {
        printf("open file %s failed: %s\n", from_path, strerror(errno));
        ret = -1;
        goto out;
    }
    if (fstat(from_fd, &from_stat) == -1) {
        printf("stat file %s failed: %s\n", from_path, strerror(errno));
        ret = -1;
        goto out;
    }

    if ((to_fd = open(to_path, O_WRONLY | O_TRUNC | O_CREAT, from_stat.st_mode)) == -1) {
        printf("stat file %s failed: %s\n", to_path, strerror(errno));
        ret = -1;
        goto out;
    }

    while ((rcount = read(from_fd, buf, MAXBSIZE)) > 0) {
        wcount = write(to_fd, buf, (size_t)rcount);
        if (rcount != wcount || wcount == -1) {
            printf("write file %s failed: %s\n", to_path, strerror(errno));
            ret = -1;
            goto out;
        }
    }
    if (rcount < 0) {
        printf("read file %s failed: %s\n", from_path, strerror(errno));
        ret = -1;
        goto out;
    }
    chown_sec_storage_data_to_system(to_path, 1);
    ret = 0;
out:
    close(from_fd);
    close(to_fd);
    return ret;
}

static void copy_work(struct sec_storage_t* trans_control)
{
    int ret;
    char from_path[256], to_path[256];

    set_current_userid(trans_control->userid);
    if(!join_file_name((char*)(trans_control->args.cp.buffer), from_path) &&
        !join_file_name((char*)(trans_control->args.cp.buffer) + trans_control->args.cp.from_path_len, to_path)){
        ret = copy_file(from_path, to_path);
        trans_control->ret = ret;
        if(ret) {
            LOGE("copy file failed: %s\n", strerror(errno));
            trans_control->error = errno;
        } else {
            LOGV("copy file success\n");
        }
    }else{
        trans_control->ret = -1;
    }
}

static void file_info_work(struct sec_storage_t* trans_control)
{
    int ret;
    struct opened_file *sel_file;
    struct stat stat_buff;

    trans_control->args.info.file_len = trans_control->args.info.cur_pos = 0;

    if(find_open_file(trans_control->args.info.fd, &sel_file)){
        if((ret = fstat(trans_control->args.info.fd, &stat_buff)) == 0){
            trans_control->args.info.file_len = stat_buff.st_size;
            trans_control->args.info.cur_pos = ftell(sel_file->file);
            LOGV("derive file info success : pos/len = %d/%d\n",
                     trans_control->args.info.cur_pos,
                     trans_control->args.info.file_len);
        }else {
            LOGE("fstat file failed: %s\n", strerror(errno));
            trans_control->error = errno;
        }
        trans_control->ret = ret;
    }else{
        trans_control->ret = -1;
        trans_control->error = EBADF;
    }
}

static void file_access_work(struct sec_storage_t* trans_control)
{
    int ret;
    char name_buff[256];

    if(trans_control->cmd == sec_access){
        set_current_userid(trans_control->userid);
        if(!join_file_name((char*)(trans_control->args.access.name), name_buff)){
            ret = access(name_buff, trans_control->args.access.mode);
            trans_control->ret = ret;
            trans_control->error = errno;
            if (ret < 0)
                LOGE("access file(%s) mode(%d) failed: %s\n",
                    name_buff, trans_control->args.access.mode, strerror(errno));
        }else{
            trans_control->ret = -1;
        }
    }else{
        ret = access((char*)(trans_control->args.access.name), trans_control->args.access.mode);
        trans_control->ret = ret;
        trans_control->error = errno;
        if (ret < 0)
            LOGE("access2 file(%s) mode(%d) failed: %s\n",
                trans_control->args.access.name, trans_control->args.access.mode, strerror(errno));
    }
}

static void fsync_work(struct sec_storage_t* trans_control)
{
    int ret,fd;
    struct opened_file *sel_file;
    //opened file
    if(trans_control->args.fsync.fd && find_open_file(trans_control->args.fsync.fd, &sel_file)){
        //first,flush memory from user to kernel
        if(ret = fflush(sel_file->file)){
            LOGE("fsync:fflush file failed: %s\n", strerror(errno));
            trans_control->ret = -1;
            trans_control->error = errno;
            return;
        }
        //second,fsync memory from kernel to disk
        fd = fileno(sel_file->file);
        if(ret = fsync(fd)){
            LOGE("fsync:fsync file failed: %s\n", strerror(errno));
            trans_control->ret = -1;
            trans_control->error = errno;
            return;
        }
        //ret = 0;
        trans_control->ret = 0;
        LOGV("fsync file(%d) success\n", trans_control->args.fsync.fd);
    }else{
        LOGE("can't find opened file(fileno = %d)\n", trans_control->args.fsync.fd);
        trans_control->ret = -1;
        trans_control->error = EBADF;
    }
}

static void disk_usage_work(struct sec_storage_t* trans_control)
{
    int ret = 0;
    struct statfs st;
    uint32_t data_remain, sec_storage_remain;

    if (statfs("/data", &st) < 0) {
        LOGE("statfs /data failed, err=%s\n", strerror(errno));
        goto error;
    }
    data_remain = (long)st.f_bfree * (long)st.f_bsize / 1024;


    if (statfs("/sec_storage", &st) < 0) {
        LOGE("statfs /sec_storage failed, err=%s\n", strerror(errno));
        goto error;
    }
    sec_storage_remain = (long)st.f_bfree * (long)st.f_bsize / 1024;

    trans_control->ret = 0;
    trans_control->args.diskusage.data = data_remain;
    trans_control->args.diskusage.sec_storage = sec_storage_remain;
    return;

error:
    trans_control->ret = -1;
    trans_control->error = errno;
}

/* add by fangjian  */
#ifdef _ANDROID_PLATFORM
#define USERDATA_READY_PROPERTY	"sys.userdata_is_ready"
static int is_userdata_ready(void)
{
    char property[PROPERTY_VALUE_MAX];

    if(property_get(USERDATA_READY_PROPERTY, property, NULL))
        LOGV("userdata ready property is %s\n", property);
    else {
        LOGE("property %s is invalid\n", USERDATA_READY_PROPERTY);
        return 0;
    }

    if (!memcmp(property, "1", sizeof("1")))
        return 1;

    return 0;
}
#endif

static void* thread_fs_work(void *control)
{
    struct sec_storage_t* trans_control = (struct sec_storage_t*)control;
    int ret;

    while(1){
        LOGV(" ++ fs agent loop ++ \n");
        ret = ioctl(fs_fd, TC_NS_CLIENT_IOCTL_WAIT_EVENT, AGENT_FS_ID);
        if(ret){
            LOGE("fs agent  wait event failed\n");
            break;
        }

        LOGV("fs agent wake up and working!! \n");
/* add by fangjian   */
#ifdef _ANDROID_PLATFORM
        if (is_userdata_ready() == 0) {
            trans_control->ret = -1;
            LOGE("do secure storage while userdata is not ready, skip!\n");
            goto file_work_done;
        }
#endif
        switch(trans_control->cmd){
        case sec_open:
        case sec_create:
            LOGV("sec storage : open/create\n");
            LOGV("open file name=%s, mode = %s\n", (char*)(trans_control->args.open.name), trans_control->args.open.mode);
            open_work(trans_control);
            break;
        case sec_close:
            LOGV("sec storage : close\n");
            close_work(trans_control);
            break;
        case sec_read:
            LOGV("sec storage : read count = %d\n", trans_control->args.read.count);
            read_work(trans_control);
            break;
        case sec_write:
            LOGV("sec storage : write count = %d\n", trans_control->args.write.count);
            write_work(trans_control);
            break;
        case sec_seek:
            LOGV("sec storage : seek offset=%d, whence=%d\n",
                      trans_control->args.seek.offset, trans_control->args.seek.whence);
            seek_work(trans_control);
            break;
        case sec_remove:
            LOGV("sec storage : remove \"%s\"\n", (char*)(trans_control->args.remove.name));
            remove_work(trans_control);
            break;
        case sec_truncate:
            LOGV("sec storage : truncate \"%s\", len=%d\n",
                      (char*)(trans_control->args.truncate.name), trans_control->args.truncate.len);
            truncate_work(trans_control);
            break;
        case sec_rename:
            LOGV("sec storage : rename old = \"%s\", new = \"%s\"\n",
                      (char*)(trans_control->args.rename.buffer),
                      (char*)(trans_control->args.rename.buffer) + trans_control->args.rename.old_name_len);
            rename_work(trans_control);
            break;
        case sec_cp:
            LOGV("sec storage : copy from = \"%s\", to = \"%s\"\n",
                      (char*)(trans_control->args.cp.buffer),
                      (char*)(trans_control->args.cp.buffer) + trans_control->args.cp.from_path_len);
            copy_work(trans_control);
            break;
        case sec_info:
            LOGV("sec storage : file info\n");
            file_info_work(trans_control);
            break;
        case sec_access:
        case sec_access2:
            LOGV("sec storage : file access\n");
            file_access_work(trans_control);
            break;
        case sec_fsync:
            LOGV("sec storage : file fsync\n");
            fsync_work(trans_control);
            break;
        case sec_diskusage:
            LOGV("sec storage : disk usage\n");
            disk_usage_work(trans_control);
            break;
        default:
            //TODO write a special error code will better?
            LOGE("fs agent error cmd:trans_control->cmd=%x\n", trans_control->cmd);
            break;
        }

file_work_done:
	trans_control->magic = AGENT_FS_ID;
        ret = ioctl(fs_fd, TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE, AGENT_FS_ID);
        if(ret){
            LOGE("fs agent send reponse failed\n");
            break;
        }

        LOGV(" -- fs agent loop -- \n");
    }

    return NULL;
}
#ifndef K3V3_FPGA
#if 0//deleted by fangjian00208632
//add by q00209673 for bootloaderlock status in nv partition
static void nv_info_work(struct misc_control_t* trans_control){
    int ret;
    SecureBoot_LockInfo info;
    ret = handle_nv(&info);
    if(ret){
        LOGE("we get bootloader info in nv partition failed\n");
        trans_control->ret = -1;
        return;
    }
    if(sizeof(SecureBoot_LockInfo) != WIDEVINE_NV_WVLOCK_SIZE){
        LOGE("SecureBoot_LockInfo had been changed\n");
        trans_control->ret = -1;
        return;
    }
    memcpy(trans_control->args.nv_info.bootloader_info, &info, WIDEVINE_NV_WVLOCK_SIZE);
    trans_control->ret = ret;
    LOGV("we get bootloader info successfully\n");
    return;
}
#endif
#endif
static void get_time_work(struct misc_control_t* trans_control)
{
    struct timeval time_val;

    if(gettimeofday(&time_val, NULL) == 0){
        trans_control->ret = 0;
        trans_control->args.get_time.seconds = time_val.tv_sec;
        trans_control->args.get_time.millis = (time_val.tv_usec/1000);
        struct tm *tstruct = NULL;
        tstruct = localtime(&(time_val.tv_sec));
	if (NULL != tstruct) {
		snprintf(trans_control->args.get_time.time_str, sizeof(trans_control->args.get_time.time_str), "%04d-%02d-%02d %02d:%02d:%02d.%03d ", //year months days hour min second
				tstruct->tm_year + 1900,
				tstruct->tm_mon + 1,
				tstruct->tm_mday,
				tstruct->tm_hour,
				tstruct->tm_min,
				tstruct->tm_sec,
				time_val.tv_usec/1000);
	} else {
		LOGE("get localtiem error\n");
	}
    }else{
        trans_control->ret = -1;
        trans_control->args.get_time.seconds = 0;
        trans_control->args.get_time.millis = 0;
    }
}


static void sync_sys_time_to_secure(void *control)
{
    struct misc_control_t* trans_control = (struct misc_control_t*)control;
    TC_NS_Time tc_ns_time;
    int ret;

    get_time_work(trans_control);

    tc_ns_time.seconds = trans_control->args.get_time.seconds;
    tc_ns_time.millis = trans_control->args.get_time.millis;

    ret = ioctl(misc_fd, TC_NS_CLIENT_IOCTL_SYC_SYS_TIME, (unsigned long)&tc_ns_time);

    if(ret){
        LOGE("failed to send sys time to teeos\n");
        return;
    }
}

static void* thread_misc_work(void *control)
{
    struct misc_control_t* trans_control = (struct misc_control_t*)control;
    int ret;

    sync_sys_time_to_secure(trans_control);

    while(1){
        LOGV(" ++ misc agent loop ++ \n");
        ret = ioctl(misc_fd, TC_NS_CLIENT_IOCTL_WAIT_EVENT, AGENT_MISC_ID);
        if(ret){
            LOGE("misc agent wait event failed\n");
            break;
        }

        LOGV("misc agent wake up and working!! \n");
        switch(trans_control->cmd){
        case sec_nv_info://add by q00209673 for bootloaderlock status in nv partition
            LOGV("sec nv info access\n");
#ifndef K3V3_FPGA
//deleted by fangjian00208632
//            nv_info_work(trans_control);
#endif
            break;
        case sec_get_time:
            LOGV("sec get time of day\n");
            get_time_work(trans_control);
            break;
        default:
            //TODO write a special error code will better?
            LOGE("misc agent error cmd\n");
            break;
        }
	trans_control->magic = AGENT_MISC_ID;
        ret = ioctl(misc_fd, TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE, AGENT_MISC_ID);
        if(ret){
            LOGE("misc agent send reponse failed\n");
            break;
        }

        LOGV(" -- misc agent loop -- \n");
    }

    return NULL;
}

/***************************************************/
/*************For RPMB agent begin********************/
/***************************************************/
#ifdef TEE_SUPPORT_RPMB_DEVICE
#include <sys/param.h> //for MAXPATHLEN
#include <unistd.h> //for access
#include <sys/utsname.h> //for uname
#include "mmc_ioctl.h"

typedef enum{
    sec_get_devinfo,
    sec_send_ioccmd
} rpmb_cmd_t;

#define RPMB_EMMC_CID_SIZE 32
struct rpmb_devinfo {
    uint8_t cid[RPMB_EMMC_CID_SIZE]; /* eMMC card ID */
    uint8_t rpmb_size_mult; /* EXT CSD-slice 168 "RPMB Size" */
    uint8_t rel_wr_sec_cnt; /* EXT CSD-slice 222 "Reliable Write Sector Count" */
    uint32_t blk_size; /* RPMB blocksize*/
    uint32_t max_blk_idx; /* The highest block index supported by current device */
};

struct rpmb_ioc{
    struct mmc_ioc_rpmb ioc_rpmb;
    uint32_t buf_offset[MMC_IOC_MAX_RPMB_CMD];
    uint32_t buf[1];
};

struct rpmb_ctrl_t{
    rpmb_cmd_t cmd;
    int32_t ret;
    union __args{
        struct rpmb_devinfo get_devinfo;
        struct rpmb_ioc send_ioccmd;
    } args;
};

/* the mmc path in sysfs is same in the platform of k3v3 and k3v3+ */
#define MMC_INFO_PATH "/sys/devices/ff390000.sdhci/mmc_host/mmc0/mmc0:0001/"
#define MMC_CID_NAME "cid"
#define MMC_RPMB_SIZE_NAME "raw_rpmb_size_mult"
#define MMC_RPMB_RELSEC_NAME "rel_sectors"

#ifdef _ANDROID_PLATFORM_HISI
#define RPMB_DEVICE_NAME "/dev/block/mmcblk0rpmb"
#else
#define RPMB_DEVICE_NAME "/dev/mmcblk0rpmb"
#endif

static int read_file(const char *filename, char *buf, size_t buflen) {
    int fd, ret;
    if ((fd = open(filename, O_RDONLY)) == -1) {
        printf("open file %s failed\n", filename);
        return -1;
    }
    ret = read(fd, buf, buflen);
    close(fd);
    return ret;
}

static void get_devinfo(struct rpmb_ctrl_t *trans_ctrl) {
    char filename[MAXPATHLEN];
    char readbuf[RPMB_EMMC_CID_SIZE];
    struct utsname buf;

    memset(trans_ctrl, 0x0, sizeof(struct rpmb_ctrl_t));

    /* 1. Get EMMC CID*/
    memset(filename, 0x0, sizeof(filename));
    strncpy(filename, MMC_INFO_PATH, sizeof(filename) - 1);
    strncat(filename, MMC_CID_NAME, sizeof(filename) - strlen(filename) - 1);
    memset(readbuf, 0x0, sizeof(readbuf));
    if (read_file(filename, readbuf, sizeof(readbuf)) == -1) {
        printf("read file %s failed\n", filename);
        goto error;
    }
    memcpy(trans_ctrl->args.get_devinfo.cid, readbuf, sizeof(trans_ctrl->args.get_devinfo.cid));

    /* 2. Get RPMB size*/
    memset(filename, 0x0, sizeof(filename));
    strncpy(filename, MMC_INFO_PATH, sizeof(filename) - 1);
    strncat(filename, MMC_RPMB_SIZE_NAME, sizeof(filename) - strlen(filename) - 1);
    memset(readbuf, 0x0, sizeof(readbuf));
    if (read_file(filename, readbuf, sizeof(readbuf)) == -1) {
        printf("read file %s failed\n", filename);
        goto error;
    }
    sscanf(readbuf, "%x", &trans_ctrl->args.get_devinfo.rpmb_size_mult);

    /* 3. Get reliable write sector count */
    memset(filename, 0x0, sizeof(filename));
    strncpy(filename, MMC_INFO_PATH, sizeof(filename) - 1);
    strncat(filename, MMC_RPMB_RELSEC_NAME, sizeof(filename) - strlen(filename) - 1);
    memset(readbuf, 0x0, sizeof(readbuf));
    if (read_file(filename, readbuf, sizeof(readbuf)) == -1) {
        printf("read file %s failed\n", filename);
        goto error;
    }
    sscanf(readbuf, "%x", &trans_ctrl->args.get_devinfo.rel_wr_sec_cnt);

    trans_ctrl->ret = 0;
    return;
error:
    trans_ctrl->ret = -1;
}

/*
 * the data_ptr from SecureOS is physical address,
 * so, we MUST update to the virtual address,
 * otherwise, segment default
 */
static void update_dataptr(struct rpmb_ctrl_t *trans_ctrl) {
    uint32_t i, offset=0, datasize;
    uint8_t *dst;
    for (i=0;i<MMC_IOC_MAX_RPMB_CMD;i++) {
        offset = trans_ctrl->args.send_ioccmd.buf_offset[i];
        if (trans_ctrl->args.send_ioccmd.ioc_rpmb.cmds[i].data_ptr) {
            dst = (uint8_t*)trans_ctrl->args.send_ioccmd.buf + offset;
            datasize = trans_ctrl->args.send_ioccmd.ioc_rpmb.cmds[i].blksz
                * trans_ctrl->args.send_ioccmd.ioc_rpmb.cmds[i].blocks;
            //update the data_ptr
            mmc_ioc_cmd_set_data(trans_ctrl->args.send_ioccmd.ioc_rpmb.cmds[i], dst);
        }
    }
}

static void send_ioccmd(struct rpmb_ctrl_t *trans_ctrl) {

    update_dataptr(trans_ctrl);

    int32_t ret;
    ret = ioctl(rpmb_device_fd, MMC_IOC_RPMB_CMD, (unsigned long)&trans_ctrl->args.send_ioccmd);
    if (ret)
        LOGE("ioctl rpmb failed: %s\n", strerror(errno));
    trans_ctrl->ret = ret;
}

static void* thread_rpmb_work(void *ctrl) {
    struct rpmb_ctrl_t *trans_ctrl = (struct rpmb_ctrl_t *)ctrl;
    int ret;

    while (1) {
        LOGV(" ++ rpmb agent loop ++ \n");
        ret = ioctl(rpmb_agent_fd, TC_NS_CLIENT_IOCTL_WAIT_EVENT, AGENT_RPMB_ID);
        if(ret){
            LOGE("rpmb agent wait event failed\n");
            break;
        }

        LOGV("rpmb agent wake up and working!! \n");
        switch (trans_ctrl->cmd) {
        case sec_get_devinfo:
            get_devinfo(trans_ctrl);
            break;
        case sec_send_ioccmd:
            send_ioccmd(trans_ctrl);
            break;
        default :
            break;
        }

        ret = ioctl(rpmb_agent_fd, TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE, AGENT_RPMB_ID);
        if(ret){
            LOGE("rpmb agent send reponse failed\n");
            break;
        }
        LOGV(" -- rpmb agent loop -- \n");
    }
    return NULL;
}
#endif
/***************************************************/
/*****************RPMB agent end********************/
/***************************************************/

static int agent_init(unsigned int id, int *dev_fd, void** control)
{
    int fd;
    void *buff = NULL;
    int ret;
    int index = 0;

    fd = open(TC_NS_CLIENT_DEV_NAME, O_RDWR);
    if(fd < 0){
        LOGE("open tee client dev failed, fd is %d\n", fd);
        return -1;
    }
    //the trick is using vm_pgoff to identify which agent it is in kernel
    if(id == AGENT_FS_ID)
	index = 1;
    else if(id == AGENT_MISC_ID)
	index = 2;
#ifdef TEE_SUPPORT_SOCKET
    else if(id == AGENT_SOCKET_ID)
	index = 3;
#endif

    //register agent
    buff = mmap(0, TRANS_BUFF_SIZE, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, index * PAGE_SIZE);
    if((void*)buff == MAP_FAILED){
        (void)close(fd);
        LOGE("mmap failed\n");
        return -1;
    }

    ret = ioctl(fd, TC_NS_CLIENT_IOCTL_REGISTER_AGENT, id);
    if(ret){
        (void)close(fd);
        LOGE("ioctl failed\n");
        (void)munmap(buff,TRANS_BUFF_SIZE);
        return -1;
    }

    *dev_fd = fd;
    *control = buff;

    return 0;
}

static void agent_exit(unsigned int id, int fd)
{
    int ret;
#if 0//by fangjian00208632
    ret = ioctl(fd, TC_NS_CLIENT_IOCTL_UNREGISTER_AGENT, id);
    if(ret){
        LOGE("ioctl failed\n");
    }
#endif
    (void)close(fd);
}

//just mkdir sec_storage_data, mount sec_storage partition in init.chip.rc
static int make_sec_storage_dir(void)
{
    struct stat statbuf;

/*added by fangjian00208632 : for hisi_linux platform begin*/
#ifndef _ANDROID_PLATFORM
    /*recursive mkdir USER_DATA_DIR*/
    if (stat(USER_DATA_DIR, &statbuf)){
        if (errno == ENOENT){ //folder not exist
            if (mkdir_r(USER_DATA_DIR) == -1){
                LOGE("make dir(%s) error\n", USER_DATA_DIR);
                return -1;
            }
        }else{
            if (S_ISDIR(statbuf.st_mode)){
                LOGE("USER DATA DIR is exist, but not a dir\n");
                //TODO rm it and mkdir?
                return -1;
            }
        }
    }

    /*mkdir for sec_storage*/
    if(stat(SEC_STORAGE_ROOT_DIR, &statbuf)){
        if(errno == ENOENT){ //folder not exist
            /*DTS2014040405270 chown sec_stroage_data q00209673 begin*/
            if (mkdir(SEC_STORAGE_ROOT_DIR, S_IRUSR|S_IWUSR|S_IXUSR) == -1){
                return -1;
            }
            //chown(SEC_STORAGE_ROOT_DIR, AID_SYSTEM, AID_SYSTEM);
            /*DTS2014040405270 chown sec_stroage_data q00209673 end*/
        }else{
            if(S_ISDIR(statbuf.st_mode)){
                LOGE("SEC STORAGE ROOT DIR is exist, but not a dir\n");
                //TODO rm it and mkdir?
                return -1;
            }
        }
    }
#endif
/*added by fangjian00208632 : for hisi_linux platform end*/

#ifdef _ANDROID_PLATFORM
    /*mkdir for sec_storage_data partition*/
    if(stat(SEC_STORAGE_DATA_DIR, &statbuf)){
        if(errno == ENOENT){ //folder not exist
            /*DTS2014040405270 chown sec_stroage_data q00209673 begin*/
            if (mkdir(SEC_STORAGE_DATA_DIR, S_IRUSR|S_IWUSR|S_IXUSR) == -1){
                return -1;
            }
            chown(SEC_STORAGE_DATA_DIR, AID_SYSTEM, AID_SYSTEM);
            /*DTS2014040405270 chown sec_stroage_data q00209673 end*/
        }else{
            if(S_ISDIR(statbuf.st_mode)){
                LOGE("ROOT DATA DIR is exist, but not a dir\n");
                //TODO rm it and mkdir?
                return -1;
            }
        }
    }
#endif
    return 0;
}

#define READ_PROC_MOUNT_SIZE 0x1000
int check_partition_ready(const char* mp)
{
    int fd = -1;
    char *pbuf = NULL;
    int ret = -1;
    char* PROC_SELF_MOUNTS = "/proc/mounts";
    char* ptmp = NULL;
    int buf_scale = 1;

retry:
    fd = open(PROC_SELF_MOUNTS, O_RDWR);
    if (fd < 0) {
        goto err0;
    }
    pbuf = (char*)malloc(READ_PROC_MOUNT_SIZE*buf_scale + 1);
    if (pbuf == NULL) {
        goto err1;
    }
    ret = read(fd, pbuf, READ_PROC_MOUNT_SIZE*buf_scale);
    if (ret >= READ_PROC_MOUNT_SIZE*buf_scale) {
        buf_scale++;
        free(pbuf);
        pbuf = NULL;
        close(fd);
        ret = -1;
        goto retry;
    }
    pbuf[READ_PROC_MOUNT_SIZE*buf_scale] = '\0';
    if (NULL == (ptmp = strstr(pbuf, mp))){
        ret = -1;
    } else {
        *(ptmp+strlen(mp))= '\0';
        ret = 1;
    }
    free(pbuf);
    pbuf = NULL;
err1:
    close(fd);
err0:
    return ret;
}
//by hxw, do not chg, leading tee_test_storage fail
int main(void)
{
    struct sec_storage_t* fs_control;
    struct misc_control_t* misc_control;
    struct rpmb_ctrl_t* rpmb_control;
    int i;
    sighandler_t sig_ret;
    pthread_t  th_fs, th_misc, th_ca_daemon, th_rpmb, th_multi_user_daemon;
    int th_fs_create_flag = 0, th_multi_flag;
#ifdef TEE_SUPPORT_SOCKET
    struct socket_ctrl_t* socket_control;
    pthread_t th_socket;
#endif

    LOGV("tee client daemon start\n");
    (void)pthread_create(&th_ca_daemon, NULL, thread_ca_server_work, NULL);

#if 0
    if(0 < check_partition_ready("/data/sec_storage"))
        th_fs_create_flag = 1;
    else
        LOGE("check_/data/sec_storage partition_ready failed ----------->\n");
#endif

    th_fs_create_flag = 1;
    if(th_fs_create_flag == 1 && make_sec_storage_dir()){
        LOGE("make root dir failed\n");
        th_fs_create_flag = 0;
        return -1;
    }

    if(th_fs_create_flag == 1 &&
        agent_init(AGENT_FS_ID, &fs_fd, (void**)(&fs_control))){
        LOGE("fs agent init failed\n");
        th_fs_create_flag = 0;
    }

#ifdef _ANDROID_PLATFORM
    if(th_fs_create_flag == 1 &&
        property_set(SFS_PROPERTY, SFS_PROPERTY_VALUE)){
        LOGE("property set error\n");
        th_fs_create_flag = 0;
    }
    LOGV("property set ok\n");
#endif

    if(agent_init(AGENT_MISC_ID, &misc_fd, (void**)(&misc_control))){
        LOGE("misc agent init failed\n");
        agent_exit(AGENT_FS_ID, fs_fd);
        return -1;
    }

#ifdef TEE_SUPPORT_RPMB_DEVICE
    /*init rpmb agent*/
    rpmb_device_fd = open(RPMB_DEVICE_NAME, O_RDWR | O_NDELAY);
    if (rpmb_device_fd != -1) {
        if(agent_init(AGENT_RPMB_ID, &rpmb_agent_fd, (void**)(&rpmb_control))){
            LOGE("rpmb agent init failed\n");
            close(rpmb_device_fd);
            agent_exit(AGENT_FS_ID, fs_fd);
            agent_exit(AGENT_MISC_ID, misc_fd);
            return -1;
        }
    }
#endif

#ifdef TEE_SUPPORT_SOCKET
    if(agent_init(AGENT_SOCKET_ID, &socket_agent_fd, (void**)(&socket_control)) ||
        socket_agent_init()) {
        LOGE("socket agent init failed\n");
        agent_exit(AGENT_FS_ID, fs_fd);
        agent_exit(AGENT_MISC_ID, misc_fd);
#ifdef TEE_SUPPORT_RPMB_DEVICE
        close(rpmb_device_fd);
        agent_exit(AGENT_RPMB_ID, rpmb_agent_fd);
#endif
        return -1;
    }
#endif

    /*
     * register our signal handler, catch signal which default action is exit
     */
    //ignore SIGPIPE(happened when CA created socket then be killed), teecd will not restart.
    signal(SIGPIPE, SIG_IGN);
    /*for(i=0; i<NSIG; i++){
        if(i==SIGHUP || i==SIGINT || i==SIGALRM || i==SIGTERM || i==SIGSEGV){
            sig_ret = signal(i, crash_handler);
            if(sig_ret == SIG_ERR)
                LOGE("setup SIGINT new handler failed\n");
        }
    }*/

    if(th_fs_create_flag == 1)
        (void)pthread_create(&th_fs, NULL, thread_fs_work, fs_control);

    (void)pthread_create(&th_misc, NULL, thread_misc_work, misc_control);
#ifdef TEE_SUPPORT_RPMB_DEVICE
    (void)pthread_create(&th_rpmb, NULL, thread_rpmb_work, rpmb_control);
#endif
    th_multi_flag = system_support_multi_users();
    if (th_multi_flag)
        (void)pthread_create(&th_multi_user_daemon, NULL, thread_multi_user_server_work, NULL);
#ifdef TEE_SUPPORT_SOCKET
    (void)pthread_create(&th_socket, NULL, thread_socket_work, socket_control);
#endif

    if (th_fs_create_flag == 1)
        (void)pthread_join(th_fs, NULL);
    (void)pthread_join(th_misc, NULL);
    (void)pthread_join(th_ca_daemon, NULL);
#ifdef TEE_SUPPORT_RPMB_DEVICE
    (void)pthread_join(th_rpmb, NULL);
#endif
    if (th_multi_flag)
        (void)pthread_join(th_multi_user_daemon, NULL);
#ifdef TEE_SUPPORT_SOCKET
    (void)pthread_join(th_socket, NULL);
#endif

    agent_exit(AGENT_FS_ID, fs_fd);
    agent_exit(AGENT_MISC_ID, misc_fd);
#ifdef TEE_SUPPORT_RPMB_DEVICE
    if (rpmb_device_fd != -1) {
        close(rpmb_device_fd);
        agent_exit(AGENT_RPMB_ID, rpmb_agent_fd);
    }
#endif
#ifdef TEE_SUPPORT_SOCKET
    socket_agent_exit();
    agent_exit(AGENT_SOCKET_ID, socket_agent_fd);
#endif

    return 0;
}
