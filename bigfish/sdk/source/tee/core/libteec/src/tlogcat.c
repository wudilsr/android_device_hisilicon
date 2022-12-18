/*
 * FileName:
 * Author:         z00202529  Version: 1.0.0  Date: 2014-11-10
 * Description: tee logcat
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include "tee_client_api.h"
#include "tee_client_id.h"
#include<signal.h>
#include<sys/types.h>
#ifdef ANDROID
#include <log/logger.h>
#include <log/logd.h>
#include <log/logprint.h>
#include <log/event_tag_map.h>
#include <cutils/sockets.h>
#endif
#include <sys/stat.h>
#include <sys/ioctl.h> /*for ioctl*/
#include <sys/mman.h> /*for mmap*/
#include "tc_ns_client.h"


/*for ioctl*/
#define AID_SYSTEM        1000
#define __TEELOGGERIO	0xBE
#define TEELOGGER_GET_LOG_LEVEL		_IO(__TEELOGGERIO, 1) /* get the TEE log level */
#define TEELOGGER_SET_LOG_LEVEL		_IO(__TEELOGGERIO, 2) /* set the TEE log leve */
#define TEELOGGER_GET_LOG_SIZE		_IO(__TEELOGGERIO, 3) /* get the TEE log size */
#define TEELOGGER_GET_MEMORY_STATUS		_IO(__TEELOGGERIO, 4) /* get the TEE memory status */
#define TEELOGGER_RESERVE		_IO(__TEELOGGERIO, 5) /* reserve */
#define LOGGER_ENTRY_MAX_LEN 1024

#define SYNC_LIMITS    1024     /*for fflush file per SYNC_LIMITS bytes*/
#define SUM_LOG (453*1024-64-156)  /* log size */
static uint32_t write_size=SUM_LOG;
#define LOG_FILE_LIMIT (500*1024)  /* log file size limit */

//#define TDEBUG
#ifdef TDEBUG
#define DEBUG_TAG "TDEBUG:"
#define TDEBUG(fmt, args...)   printf("%s" fmt "\n", DEBUG_TAG, ##args)
#else
#define TDEBUG
#endif

#define ERROR_TAG "TERROR:"
#define TERROR(fmt, args...)   printf("%s" fmt "\n", ERROR_TAG, ##args)

#define NAME_SIZE       256
#define NAME_NUM        3
#define NAME_LIMITS   64
char log_name_attr[NAME_NUM][NAME_SIZE] =
{"/data/hisi_logs/running_trace/teeos_logs/teeOS_log-1",
    "/data/hisi_logs/running_trace/teeos_logs/teeOS_log-2",
    "/data/hisi_logs/running_trace/teeos_logs/teeOS_log-3"};
static int dev_fd = 0;
static int tee_log_fd=0;
static uint32_t logsize=0;
FILE* pFile=NULL;
static bool name_flag=false;
/* check weather /data/hisi_logs  and /data/hisi_logs/running_trace and /data/hisi_logs/teeos_logs exist, if not exist just create the folder*/
int32_t log_dir_check()
{
    int ret=0;
    struct stat statbuf_dir;
    /* check the "hisi_logs" dir is exist or not ,if not create */
    ret = stat("data/hisi_logs",&statbuf_dir);
    if(ret != 0 ){
        ret = mkdir("data/hisi_logs", S_IRWXU | S_IRWXG);
	if (ret != 0) {
	    TERROR("failed to mkdir data/hisi_logs:errno is %d\n", errno);
	    return -1;
	}
        ret = chown("data/hisi_logs", -1, AID_SYSTEM);
        if (ret < 0)
            TERROR("chown err\n");
	ret = chmod("data/hisi_logs", 0770);
	if (ret < 0)
	    TERROR("chmod err\n");
    }
    /* check the "running_trace" dir is exist or not ,if not create */
    ret = stat("data/hisi_logs/running_trace",&statbuf_dir);
    if(ret != 0 ){
        ret = mkdir("data/hisi_logs/running_trace", S_IRWXU | S_IRWXG);
	if (ret != 0) {
	    TERROR("failed to mkdir data/hisi_logs/running_trace:errno is %d\n", errno);
	    return -1;
	}
        ret = chown("data/hisi_logs/running_trace", -1, AID_SYSTEM);
        if (ret < 0)
            TERROR("chown err\n");
	ret = chmod("data/hisi_logs/running_trace", 0770);
	if (ret < 0)
	    TERROR("chmod err\n");
    }

    /* test the "teeos_logs" dir is exist or not ,if not create */
    ret = stat("data/hisi_logs/running_trace/teeos_logs",&statbuf_dir);
    if(ret != 0 ){
        ret = mkdir("data/hisi_logs/running_trace/teeos_logs", S_IRWXU | S_IRWXG);
	if (ret != 0) {
	    TERROR("failed to mkdir data/hisi_logs/running_trace/teeos_logs:errno is %d\n", errno);
	    return -1;
	}
        ret = chown("data/hisi_logs/running_trace/teeos_logs", -1, AID_SYSTEM);
         if (ret < 0)
            TERROR("chown err\n"); 
	 ret = chmod("data/hisi_logs/running_trace/teeos_logs", 0770);
	 if (ret < 0)
	     TERROR("chmod err\n");
    }
    TDEBUG("data/hisi_logs/running_trace/teeos_logs exist\n");
    return 0;
}
/* if the logsize of current log file  is over the LOG_LIMIT, rename old log file, and create new "log_name_attr[0]" */
int32_t log_overflow()
{
    uint32_t i;
    int ret = 0;

    fclose(pFile);
    ret = log_dir_check();
    if (ret != 0) {
	TERROR("teeos log dir does not find, ret = %d\n", ret);
	return -1;
    }
    for(i=2;i>0;i--)
    {
        if(access(log_name_attr[i-1], F_OK)==0){
            if(rename(log_name_attr[i-1], log_name_attr[i])){
                TERROR("logsize_over rename error, errno is %d\n", errno);
                ret = -1;
            }
        }
    }

    pFile=fopen(log_name_attr[0],"w+");
    if(pFile == NULL){
        TERROR("get_logfile fcreate is error\n");
        ret =  -1;
	return ret;
    }
    ret = chown(log_name_attr[0], -1, AID_SYSTEM);
    if (ret < 0)
           TERROR("chown error\n");
    ret = chmod(log_name_attr[0], S_IRUSR|S_IWUSR|S_IRGRP);
    if (ret < 0)
           TERROR("chmod error\n");

    //tee_log_fd = pFile->_file;
    tee_log_fd = fileno(pFile);
    logsize = 0;
    return ret;
}




/* get the log file's FILE */
int32_t log_getfile(char *filename)
{
    TDEBUG("save tee log start ++\n");
    int ret=0;
    struct stat stat_buff;
    char name[NAME_SIZE]={"/data/hisi_logs/running_trace/teeos_logs/"};

    ret = log_dir_check();
    if (ret != 0) {
	TERROR("teeos log dir does not find, ret = %d\n", ret);
	return -1;
    }

    if(filename == NULL){
        TDEBUG("filename is null\n");
        pFile=fopen(log_name_attr[0],"a+");
	if (pFile == NULL) {
	    TERROR("failed to open %s, errno is %d\n", log_name_attr[0], errno);
	    return -1;
	}
        ret = chown(log_name_attr[0], -1, AID_SYSTEM);
        if (ret < 0)
           TERROR("chown error\n");
        ret = chmod(log_name_attr[0], S_IRUSR|S_IWUSR|S_IRGRP);
        if (ret < 0)
           TERROR("chmod error\n");
    }
    else{
        memcpy(name+strlen(name),filename,strlen(filename));
        TDEBUG("filename is %s  name is %s \n",filename,name);
        name_flag = true;
        pFile=fopen(name,"a+");
	if (pFile == NULL) {
	    TERROR("failed to open %s, errno is %d\n", name, errno);
	    return -1;
	}
        ret = chown(name, -1, AID_SYSTEM);
        if (ret < 0)
           TERROR("chown error\n");
        ret = chmod(name, S_IRUSR|S_IWUSR|S_IRGRP);
        if (ret < 0)
           TERROR("chmod error\n");
    }

    //tee_log_fd = pFile->_file;
    tee_log_fd = fileno(pFile);

    ret = fstat(tee_log_fd, &stat_buff) ;
    logsize = stat_buff.st_size;

    //TDEBUG(" tee_log_fd=%d logsize=%d \n", pFile->_file, logsize);
    TDEBUG(" tee_log_fd=%d logsize=%d \n", fileno(pFile), logsize);
    return 0;
}

static int memory_func()
{
    TEEC_Context context;
    TEEC_Session session;
    TEEC_Result result;
    TEEC_UUID global_uuid = TEE_SERVICE_GLOBAL;
    TEEC_Operation operation;
    uint32_t origin;
    uint32_t cmd =GLOBAL_CMD_ID_TEE_INFO;

    result = TEEC_InitializeContext(
            NULL,
            &context);
    if(result != TEEC_SUCCESS) {
        goto cleanup_1;
    }
    result = TEEC_OpenSession(
            &context,
            &session,
            &global_uuid,
            TEEC_LOGIN_PUBLIC,
            NULL,
            NULL,
            NULL);
    if (result != TEEC_SUCCESS) {
        TERROR("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_2;
    }

    memset(&operation, 0, sizeof(operation));
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INOUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);
    operation.params[0].value.a = 0;
    operation.params[0].value.b = 1;

    result = TEEC_InvokeCommand(
            &session,
            cmd,
            &operation,
            &origin);
    if (result != TEEC_SUCCESS)
        TERROR("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);

    printf("memory use:\n");
    printf("    global-  %d/10000\n",operation.params[0].value.a);
    printf("    teeos-   %d/10000\n",operation.params[0].value.b);

    TEEC_CloseSession(&session);
cleanup_2:
    TEEC_FinalizeContext(&context);
cleanup_1:
    return result;
}

static int  log_setlevel(int level)
{
    int ret;
    ret = ioctl(dev_fd,TEELOGGER_SET_LOG_LEVEL, level);
    return ret;
}

static int log_getlevel()
{
    int ret = 0;
    ret = ioctl(dev_fd, TEELOGGER_GET_LOG_LEVEL, NULL);
    return ret;
}

void help_show()
{
    printf("this is help, you should input:\n");
    printf("    -f:  save teeos log to /data/teeos_logs/teeOS_log-1, 2 and 3 \n");
    printf("          -flog.txt:  save teeos log to /data/teeos_logs/log.txt , file name shoud be less 64\n");
    printf("    -g:  get tee log level \n");
    printf("    -s:  set tee log level \n");
    printf("          -s1:  set tee log level to be 1, you can input 0,1 or 2 \n");
    printf("    -m: get tee memory status \n");
}

void f_func(bool flag, char *filename)
{
    int tlog_dev_fd = 0;
    int result=1;
    int ret = 0;
    bool sleep = true;
    fd_set readset;
    char read_buff[1025]={0};
    uint32_t flush_num=0;//if want to improve performance, can fflush per flush_num*k

    TDEBUG("f_func\n");
    tlog_dev_fd = dev_fd;
    if(flag == true)
        if(log_getfile(filename)) {
	    TERROR("failed to get teelog file\n");
	    exit(EXIT_FAILURE);
	}
    while (1) {
        do {
            struct timeval timeout = { 0, 5000 /* 5ms */ }; // If we oversleep it's ok, i.e. ignore EINTR.
            FD_ZERO(&readset);
            FD_SET(tlog_dev_fd, &readset);
            TDEBUG("while select\n");
            result = select((tlog_dev_fd+1), &readset, NULL, NULL, sleep ? NULL : &timeout);
        } while (result == -1 && errno == EINTR);
        if (result >= 0) {
            if (FD_ISSET(tlog_dev_fd, &readset)) {
                ret = read(tlog_dev_fd, read_buff, LOGGER_ENTRY_MAX_LEN);
                if (ret < 0) {
                    if (errno == EINTR) {
                        TERROR("step 1 =-----errno == EINTR-----\n");
                    }
                    if (errno == EAGAIN) {
                        TERROR("step 2 =-----errno == EAGAIN-----\n");
                    }
                    TERROR("tlogcat read ret=%d\n",ret);
                    exit(EXIT_FAILURE);
                }
                else if (!ret) {
                    TERROR("read: Unexpected EOF!\n");
                    exit(EXIT_FAILURE);
                }
                else if (ret) {
                    TDEBUG("read length. ret = %d \n",ret);
                }

                read_buff[ret] = '\0';
                if(flag == true)
                {
                    if((logsize > LOG_FILE_LIMIT) && !name_flag) {
                        ret = log_overflow();
			if (ret != 0) {
			    TERROR("failed to get tlog file fd, ret is %d\n", ret);
			    exit(EXIT_FAILURE);
			}
		    }
                    int numm;
                    numm =fwrite(read_buff,1,ret,pFile);
                    int ret_flush=0;
                    ret_flush = fflush(pFile);

                if(numm < ret){
                        TERROR("fwrite   error !!!!!!!!!!!!!!tee_log_fd=%d!!!!!!pFile->_file=%d!!!!!!!!!!!!!!!!\n",tee_log_fd, fileno(pFile));

			        fclose(pFile);
			        if(log_getfile(filename)) {
			            TERROR("when write retry,failed to get teelog file\n");
			            exit(EXIT_FAILURE);
			        }
                numm =fwrite(read_buff,1,ret,pFile);
                ret_flush = fflush(pFile);
               }

               logsize+=numm;
          }else
               printf("%s\n",read_buff);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    printf("tlogcat start ++ \n");
    int ch;
    int ret = 0;
    bool default_op=true;

    dev_fd = open( "/dev/hisi_teelog",  O_RDONLY);
    if(dev_fd < 0){
        TERROR("open log device error\n");
        goto error1;
    }
    else
        TDEBUG("open dev success dev_fd=%d\n",dev_fd);

    while ((ch = getopt(argc, argv, "f::ms:gh")) != -1)
    {
        default_op=false;
        TDEBUG("optind: %d,argc:%d,argv[%d]:%s\n", optind,argc,optind,argv[optind]);
        switch (ch) {
            case 'm':
                printf("HAVE option: -m\n\n");
                memory_func();
                break;
            case 'f':
                printf("HAVE option: -f\n");
                TDEBUG("The argument of -f is %s len should less %d\n", optarg,NAME_LIMITS);
                if(optarg != NULL)
                    if(strlen(optarg) > NAME_LIMITS){
                        TERROR("filename len is error, name shoud be less %d\n",NAME_LIMITS);
                        goto error;
                    }
                f_func(true,optarg);
                break;
            case 's':
                printf("HAVE option: -s\n");
                TDEBUG("The argument of -s is %s\n", optarg);
                if(!optarg)
                    goto error;
                if((strlen(optarg)>1) || *optarg>'2' || *optarg<'0'){
                    TERROR("log level input  is error, it should 0, 1 or 2.  (strlen(optarg)=%d \n",strlen(optarg));
                    goto error;
                }
                int level;
                level = atoi(optarg);
                ret = log_setlevel(level);
                printf("New level is %d, ret=%d \n",level, ret);
                break;
            case 'g':
                TDEBUG("HAVE option: -g\n");
                ret = log_getlevel();
                printf("tee log level is %d\n",ret);
                break;
            case 'h':
                printf("HAVE option: -h\n");
                help_show();
                break;
            default:
                printf("Unknown option: %c\n",(char)optopt);
                help_show();
                break;
        }

        printf("----------------------------\n");
        TDEBUG("optind=%d,argv[%d]=%s\n",optind,optind,argv[optind]);
    }

    if(default_op)
        f_func(false,optarg);
    printf("tlogcat end -- \n");
    close(dev_fd);
    return 0;
error:
    help_show();
    close(dev_fd);
error1:
    return 0;
}

