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
#include <pthread.h>
//debug switch
#define LOG_NDEBUG 0
#define LOG_TAG "teecd"
#ifdef ANDROID
#include <cutils/log.h>
#endif
#include "tc_ns_client.h"
#include "tee_client_type.h"
//add by q00209673 for bootloaderlock status
#include "tee_nv_info.h"

#ifdef K3V3_FPGA_OR_STB
//#define LOGE ALOGE
//#define LOGV ALOGV
#define LOGE(fmt, args...) printf("%s %s: " fmt "", LOG_TAG, __FUNCTION__, ## args)
#define LOGV(fmt, args...) printf("%s %s: " fmt "", LOG_TAG, __FUNCTION__, ## args)
#else
#define LOGE
#define LOGV
#endif

typedef void (*sighandler_t)(int);

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
}fs_cmd_t;

typedef enum{
    sec_nv_info,//add by q00209673 for bootloaderlock status in nv partition
    sec_get_time,
}misc_cmd_t;

struct sec_storage_t{
    fs_cmd_t cmd;   //for s to n
    int32_t ret;    //fxxx call's return
    int32_t ret2;   //just for fread, judge end-of-file or error
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
    }args;
};

struct misc_control_t{
    misc_cmd_t cmd;   //for s to n
    int32_t ret;
    union args2{
        //add by q00209673 for bootloader lock status in nv partition
        struct{
            uint8_t bootloader_info[WIDEVINE_NV_WVLOCK_SIZE];
        }nv_info;
        struct{
            uint32_t seconds;
            uint32_t millis;
        }get_time;
    }args;
};

#define TRANS_BUFF_SIZE (4*1024)    //agent transfer share buffer size
#define AGENT_FS_ID 0x46536673      //FSfs
#define AGENT_MISC_ID 0x4d495343    //MISC
#ifdef K3V3_FPGA_OR_STB
#define SEC_STORAGE_ROOT_DIR    "/data/sec_storage/"
#else
#define SEC_STORAGE_ROOT_DIR    "/sec_storage/"
#endif
#define ROOT_DIR_PERM   (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)   //0666 TODO should be change

struct opened_file{
    FILE* file;
    struct opened_file *next;
    struct opened_file *prev;
};

// open file list head
struct opened_file *g_first_file=(struct opened_file *)NULL;

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
            if(fileno(p->file) == fd){
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

/*
 * if agent exit accidently, this handler do some clean work.
 */
static void crash_handler(int signum)
{
#ifdef DEBUG_ON
    char buff[20];
    int fd;

    fd = open("/dev/ttyAMA0",O_RDWR);
    sprintf(buff, "-->crash sig=%d\n", signum);
    write(fd, buff, strlen(buff) + 1);
    close(fd);
#endif
    LOGV("crash signal num = %d\n", signum);

    agent_exit(AGENT_FS_ID, fs_fd);
    agent_exit(AGENT_MISC_ID, misc_fd);

    exit(0);
}

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

static int join_file_name(const char* name, char *path)
{
    if(name == NULL)
        return -1;

    strncpy(path, SEC_STORAGE_ROOT_DIR, sizeof(SEC_STORAGE_ROOT_DIR));
    strncat(path, name, strlen(name)+1);
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

    if(!join_file_name((char*)(trans_control->args.open.name), name_buff)){
        if(trans_control->cmd == sec_create){  //create a exist file, remove it at first
            strncpy(trans_control->args.open.mode, "w+", 4);
        }else{
            if(is_file_exist(name_buff) == 0){  //open a nonexist file, return fail
                trans_control->ret = -1;
                return;
            }
        }

        pFile = fopen(name_buff, trans_control->args.open.mode);
        if(pFile == NULL){
            LOGE("open file(%s) failed\n", (char*)(trans_control->args.open.name));
            trans_control->ret = -1;
        }else{
            LOGV("open file(%s) success : fd = %d\n", (char*)(trans_control->args.open.name), fileno(pFile));
            sel_file = (struct opened_file*)malloc(sizeof(struct opened_file));
            if(!sel_file){
                LOGE("malloc opened_file failed\n");
                trans_control->ret = -1;
            }else{
                sel_file->file = pFile;
                trans_control->ret = fileno(sel_file->file);  //return fileno
                //list_add(&g_file_list, &sel_file->head);
                add_open_file(sel_file);
            }
        }
    }else{
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
            LOGE("close file(%d) failed\n", trans_control->args.close.fd);
        }
    }else{
        LOGE("can't find opened file(fileno = %d)\n", trans_control->args.close.fd);
        trans_control->ret = -1;
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
                LOGE("read end of file\n");
            }else{
                trans_control->ret2 = -1;
                LOGE("read file failed\n");
            }
        }else{
            trans_control->ret2 = 0;
            LOGV("read file success, content len=%d\n", count);
        }
    }else{
        trans_control->ret = 0;
        trans_control->ret2 = -1;
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
        trans_control->ret = count;
        if(count < trans_control->args.write.count)
            LOGE("write file failed\n");
        else
            LOGV("write file success, content len=%d\n", count);

        //TODO need?
        if(fflush(sel_file->file) != 0)
            LOGE("fflush file failed\n");
    }else{
        LOGE("can't find opened file(fileno = %d)\n", trans_control->args.write.fd);
        trans_control->ret = 0;
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
            LOGE("seek file failed\n");
        }else{
            LOGV("seek file success\n");
        }
    }else{
        LOGE("can't find opened file(fileno = %d)\n", trans_control->args.seek.fd);
        trans_control->ret = -1;
    }
}

static void remove_work(struct sec_storage_t* trans_control)
{
    int ret;
    char name_buff[256];

    if(!join_file_name((char*)(trans_control->args.remove.name), name_buff)){
        ret = remove(name_buff);
        trans_control->ret = ret;
        if(ret)
            LOGE("remove file failed\n");
        else
            LOGV("remove file success\n");
    }else{
        trans_control->ret = -1;
    }
}

static void truncate_work(struct sec_storage_t* trans_control)
{
    int ret;
    char name_buff[256];

    if(!join_file_name((char*)(trans_control->args.truncate.name), name_buff)){
        ret = truncate(name_buff, trans_control->args.truncate.len);
        trans_control->ret = ret;
        if(ret){
            LOGE("truncate file failed:errno=%d, err:%s\n",errno, strerror(errno));
        }
        else
            LOGV("truncate file success\n");
    }else{
        trans_control->ret = -1;
    }
}

static void rename_work(struct sec_storage_t* trans_control)
{
    int ret;
    char name_buff[256], name_buff2[256];

    if(!join_file_name((char*)(trans_control->args.rename.buffer), name_buff) &&
        !join_file_name((char*)(trans_control->args.rename.buffer) + trans_control->args.rename.old_name_len, name_buff2)){
        ret = rename(name_buff, name_buff2);
        trans_control->ret = ret;
        if(ret)
            LOGE("rename file failed\n");
        else
            LOGV("rename file success\n");
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
        }else
            LOGE("fstat file failed\n");
        trans_control->ret = ret;
    }else{
        trans_control->ret = -1;
    }
}

static void file_access_work(struct sec_storage_t* trans_control)
{
    int ret;
    char name_buff[256];

    if(trans_control->cmd == sec_access){
        if(!join_file_name((char*)(trans_control->args.access.name), name_buff)){
            ret = access(name_buff, trans_control->args.access.mode);
            trans_control->ret = ret;
            LOGV("access file's mode %d ret = %d\n", trans_control->args.access.mode, ret);
        }else{
            trans_control->ret = -1;
        }
    }else{
        ret = access((char*)(trans_control->args.access.name), trans_control->args.access.mode);
        trans_control->ret = ret;
        LOGV("access2 file's mode %d ret = %d\n", trans_control->args.access.mode, ret);
    }
}

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
        case sec_info:
            LOGV("sec storage : file info\n");
            file_info_work(trans_control);
            break;
        case sec_access:
        case sec_access2:
            LOGV("sec storage : file access\n");
            file_access_work(trans_control);
            break;
        default:
            //TODO write a special error code will better?
            LOGE("fs agent error cmd\n");
            break;
        }

        ret = ioctl(fs_fd, TC_NS_CLIENT_IOCTL_SEND_EVENT_REPONSE, AGENT_FS_ID);
        if(ret){
            LOGE("fs agent send reponse failed\n");
            break;
        }

        LOGV(" -- fs agent loop -- \n");
    }

    return NULL;
}
#ifndef K3V3_FPGA_OR_STB
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
static void get_time_work(struct misc_control_t* trans_control)
{
    struct timeval time_val;

    if(gettimeofday(&time_val, NULL) == 0){
        trans_control->ret = 0;
        trans_control->args.get_time.seconds = time_val.tv_sec;
        trans_control->args.get_time.millis = (time_val.tv_usec/1000);
    }else{
        trans_control->ret = -1;
        trans_control->args.get_time.seconds = 0;
        trans_control->args.get_time.millis = 0;
    }
}

static void* thread_misc_work(void *control)
{
    struct misc_control_t* trans_control = (struct misc_control_t*)control;
    int ret;

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
#ifndef K3V3_FPGA_OR_STB
            nv_info_work(trans_control);
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

        ret = ioctl(fs_fd, TC_NS_CLIENT_IOCTL_SEND_EVENT_REPONSE, AGENT_MISC_ID);
        if(ret){
            LOGE("misc agent send reponse failed\n");
            break;
        }

        LOGV(" -- misc agent loop -- \n");
    }

    return NULL;
}

static int agent_init(unsigned int id, int *dev_fd, void** control)
{
    int fd;
    void *buff = NULL;
    int ret;

    fd = open(TC_NS_CLIENT_DEV_NAME, O_RDWR);
    if(fd == -1){
        LOGE("open tee client dev failed\n");
        return -1;
    }

    //register agent
    buff = mmap(0, TRANS_BUFF_SIZE, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, 0);
    if((void*)buff == MAP_FAILED){
        (void)close(fd);
        LOGE("mmap failed\n");
        return -1;
    }

    ret = ioctl(fd, TC_NS_CLIENT_IOCTL_REGISTER_AGENT, id);
    if(ret){
        (void)close(fd);
        LOGE("ioctl failed\n");
        return -1;
    }

    *dev_fd = fd;
    *control = buff;

    return 0;
}

static void agent_exit(unsigned int id, int fd)
{
    int ret;

    ret = ioctl(fd, TC_NS_CLIENT_IOCTL_UNREGISTER_AGENT, id);
    if(ret){
        LOGE("ioctl failed\n");
    }

    (void)close(fd);
}
//TODO maybe it's a partition in feature
static int make_sec_storage_dir(void)
{
    struct stat statbuf;

    if(stat(SEC_STORAGE_ROOT_DIR, &statbuf)){
        if(errno == ENOENT){ //folder not exist
            if (mkdir(SEC_STORAGE_ROOT_DIR, ROOT_DIR_PERM) == -1){
                return -1;
            }
        }else{
            if(S_ISDIR(statbuf.st_mode)){
                LOGE("ROOT DIR is exist, but not a dir\n");
                //TODO rm it and mkdir?
                return -1;
            }
        }
    }

    return 0;
}
int main(int argc, char* argv[])
{
    struct sec_storage_t* fs_control;
    struct misc_control_t* misc_control;
    int i;
    sighandler_t sig_ret;
    pthread_t  th_fs, th_misc;

    LOGV("tee client daemon start\n");
#ifdef K3V3_FPGA_OR_STB
	if(make_sec_storage_dir()){
        LOGE("make root dir failed\n");
        return -1;
    }
#endif
    if(agent_init(AGENT_FS_ID, &fs_fd, (void**)(&fs_control))){
        LOGE("fs agent init failed\n");
        return -1;
    }

    if(agent_init(AGENT_MISC_ID, &misc_fd, (void**)(&misc_control))){
        LOGE("misc agent init failed\n");
        agent_exit(AGENT_FS_ID, fs_fd);
        return -1;
    }

    /*
     * register our signal handler, catch signal which default action is exit
     */
    for(i=0; i<NSIG; i++){
        if(i==SIGHUP || i==SIGINT || i==SIGPIPE || i==SIGALRM || i==SIGTERM || i==SIGSEGV){
            sig_ret = signal(i, crash_handler);
            if(sig_ret == SIG_ERR)
                LOGE("setup SIGINT new handler failed\n");
        }
    }

    (void)pthread_create(&th_fs, NULL, thread_fs_work, fs_control);
    (void)pthread_create(&th_misc, NULL, thread_misc_work, misc_control);

    (void)pthread_join(th_fs, NULL);
    (void)pthread_join(th_misc, NULL);

    agent_exit(AGENT_FS_ID, fs_fd);
    agent_exit(AGENT_MISC_ID, misc_fd);

    return 0;
}
