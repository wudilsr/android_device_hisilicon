#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h> /*for errno*/
#include <fcntl.h>
#include <sys/types.h> /*for open close*/
#include <sys/stat.h>
#include <sys/ioctl.h> /*for ioctl*/
#include <sys/mman.h> /*for mmap*/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <signal.h>
#include <sys/time.h>
#include <sys/mount.h>
#include <pthread.h>


//debug switch
#define LOG_NDEBUG 0
#define LOG_TAG "teecd"

#define BUF_MAX_SIZE 4096

#ifdef _ANDROID_PLATFORM_HISI
#include <cutils/log.h>
#include <cutils/properties.h>
/*DTS2014040405270 chown sec_stroage_data q00209673 */
#include <private/android_filesystem_config.h>
#endif

#include "tc_ns_client.h"
#include "tee_ca_daemon.h"
#include "tee_client_type.h"

#ifdef _ANDROID_PLATFORM_HISI
#if LOG_NDEBUG
#define ALOGI(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define ALOGI(...)
#endif
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else//else _ANDROID_PLATFORM
#if LOG_NDEBUG
#define ALOGI(fmt, args...) printf("[debug]%s %s: " fmt "", LOG_TAG, __FUNCTION__, ## args)
#else
#define ALOGI(...)
#endif
#define ALOGE(fmt, args...) printf("[error]%s %s: " fmt "", LOG_TAG, __FUNCTION__, ## args)
#endif


#define BACKLOG_LEN 10

#ifndef _ANDROID_PLATFORM_HISI /* for hisi */

struct ucred {
    pid_t   pid;     /* 发送进程的进程标识 */
    uid_t   uid;     /* 发送进程的用户标识 */
    gid_t   gid;     /* 发送进程的组标识 */
    };
#endif

static int
send_file_descriptor(int socket, int fd_to_send)
{
    struct msghdr message;
    struct iovec iov[1];
    struct cmsghdr *control_message = NULL;
    char ctrl_buf[CMSG_SPACE(sizeof(int))];
    char data[1];

    memset(&message, 0, sizeof(struct msghdr));
    memset(ctrl_buf, 0, CMSG_SPACE(sizeof(int)));

    /* We are passing at least one byte of data so that recvmsg() will not return 0 */
    data[0] = ' ';
    iov[0].iov_base = data;
    iov[0].iov_len = sizeof(data);

    message.msg_name = NULL;
    message.msg_namelen = 0;
    message.msg_iov = iov;
    message.msg_iovlen = 1;
    message.msg_controllen =  CMSG_SPACE(sizeof(int));
    message.msg_control = ctrl_buf;

    control_message = CMSG_FIRSTHDR(&message);
    control_message->cmsg_level = SOL_SOCKET;
    control_message->cmsg_type = SCM_RIGHTS;
    control_message->cmsg_len = CMSG_LEN(sizeof(int));

    *((int *) CMSG_DATA(control_message)) = fd_to_send;

    return sendmsg(socket, &message, 0);
}

#define __le8  unsigned char
#define MAX_PATH_LENGTH      256

void tee_get_ca_name(unsigned long pid, char *ca_name, unsigned int len) {
	FILE *fd;

	(void)snprintf(ca_name, len, "/proc/%ld/cmdline", pid);
	fd = fopen(ca_name, "r");
	if(NULL == fd) {
	    ALOGE("fopen[%s] is error\n", ca_name);
	    return;
	}

	memset(ca_name, 0x00, len);
	(void)fread(ca_name, 1, len, fd);
	fclose(fd);
	fd = NULL;
}

int tee_check_ca_cert(int type, unsigned char* block, unsigned int bufl,
            unsigned long uid, unsigned long pid)
{
    #define TA_COUNTER_NATIVE 50
    const static __le8 *array_cert_native[TA_COUNTER_NATIVE] = {
        "widevine_ce_cdm_unittest 0",
        "tee_test_agent 0",
        "tee_test_CA 0",
        "tee_test_cancellation 0",
        "tee_test_cipher 0",
        "tee_test_elfload 0",
        "tee_test_hdcp_storekey 0",
        "tee_test_hdcp_write 0",
        "tee_test_login 0",
        "tee_test_random 0",
        "tee_test_random 0",
        "tee_test_hwi_ipc 0",
        "tee_test_invoke 0",
        "tee_test_mem 0",
        "tee_test_secboot 0",
        "tee_test_secure_timer 0",
        "tee_test_sess 0",
        "tee_test_stability 0",
        "/bin/tee_test_storage 0",
        "tee_test_ut 0",
        "tee_test_time 0",
        "teec_hello 0",
        "teec_permctrl 0",
        "hisi_keymaster_test 0",
        "hisi_gatekeeper_test 0",
        "hisi_demo_client 0",
        "./tee_test_cipher 0",
        "tee_test_beidou 0",
	    "./st_cipher 0",
        "./st_mmz 0",
	    "./st_demux 0",
	    "./sample_tee_tsplay 0",
	    "./sample_tee_tsplay_pid 0",
        "sample_omxvdec 0",
        "sample_rawplay 0",
        "sample_esplay 0",
		"hisi_drv_hdmi 0",
        "/system/bin/mediaserver 0",
        "/system/bin/mediaserver 1013",
        "/system/bin/drmserver 0",
        "/system/bin/drmserver 1019",
        "sample_keybox 0",
        "sample_checkkeybox 0",
        "test_modularwv_hal 0",
        "oemcrypto_test 0",
        "upgrade_keybox 0",
        "sample_playreadypk_play 0",
        "sample_playreadypk_provision 0",
        "/system/bin/mediadrmserver 0",
        "/system/bin/mediadrmserver 1013",
    };
    int ret = -1;
    int index = 0;
    char path[MAX_PATH_LENGTH] = {0};
    __le8 ca_cert[BUF_MAX_SIZE] = {0};
    FILE *fd;

    if(CA_CERT_NATIVE == type)
    {
        (void)snprintf(path,MAX_PATH_LENGTH-1,"/proc/%ld/cmdline", pid);
        fd = fopen(path,"r");
        if(NULL == fd) {
            ALOGE("fopen is error\n");
            return -1;
        }

        memset(path, 0x00, MAX_PATH_LENGTH);
        (void)fread(path,1,MAX_PATH_LENGTH-1,fd);
        fclose(fd);
        fd = NULL;
        memset(ca_cert, 0x00, BUF_MAX_SIZE);
        (void)snprintf(ca_cert, BUF_MAX_SIZE-1, "%s %ld", path, uid);

        for(index=0; index < TA_COUNTER_NATIVE; index++)
        if(0 == (ret = memcmp(ca_cert, array_cert_native[index], strlen(array_cert_native[index]))))
        {
            ret = 0;
            break;
        }
    }
    else if(CA_CERT_APK == type)
    {
        ret = 0;
    }
    return ret;
}

int tee_get_app_cert(int ca_pid, int ca_uid, uint32_t* len, uint8_t *buffer, uint32_t* type);
void* thread_ca_server_work(void *dummy)
{
    struct ucred cr;
    int ret, t;
    int s, s2;
    uint8_t *buf = NULL;
    size_t bufl;
    uint32_t type = 0;
	char ca_name[MAX_PATH_LENGTH] = {0};

    if (access(TC_NS_CLIENT_DEV_NAME, O_RDWR)) {
        ALOGE("No access to %s: %s\n",   TC_NS_CLIENT_DEV_NAME, strerror(errno));
        pthread_exit(-1);
    }

    // Open a socket (a UNIX domain stream socket)
    s = socket(AF_UNIX, SOCK_STREAM, 0);
    if(s < 0) {
        ALOGE("can't open stream socket, errno=%d", errno);
        pthread_exit(-1);
    }
    // Fill in address structure and bind to socket
    struct sockaddr_un local, remote;
    local.sun_family = AF_UNIX;
    strncpy(local.sun_path, TC_NS_SOCKET_NAME, sizeof(TC_NS_SOCKET_NAME));

    socklen_t len = strlen(local.sun_path) + sizeof(local.sun_family);
    // Make the socket in the Abstract Domain(no path but everyone can connect)
    local.sun_path[0] = 0;
    if (bind(s, (struct sockaddr *) &local, len) < 0)
    {
        ALOGE("bind() to server socket failed, errno=%d", errno);
        pthread_exit(-1);
    }

    // Start listening on the socket
    if (listen(s, BACKLOG_LEN) < 0)
    {
        ALOGE("listen() failed, errno=%d", errno);
        pthread_exit(-1);
    }
#ifdef _ANDROID_PLATFORM
    ALOGI("\n********* successfully initialized *********\n");

    if(property_set(THREAD_CA_SERVER_PROPERTY, THREAD_CA_SERVER_PROPERTY_READY)){
        ALOGE("THREAD_CA_SERVER_PROPERTY property set error\n");
        pthread_exit(-1);
    }
#endif

    while(1) {
        //int done, n;
        ALOGI("Waiting for a connection...\n");
        t = sizeof(remote);
        if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
            ALOGE("accept() to server socket failed, errno=%d", errno);
            break;
        }


        len = sizeof(struct ucred);
        if(getsockopt(s2, SOL_SOCKET, SO_PEERCRED, &cr, &len) < 0){
            ALOGE("peercred failed %s\n", strerror(errno));
            break;
        }

        int fd = open(TC_NS_CLIENT_DEV_NAME, O_RDWR);
        if (fd < 0) {
            ALOGE("Failed to open %s: %s\n", TC_NS_CLIENT_DEV_NAME, strerror(errno));
            goto close_socket;
        }

        buf = malloc(BUF_MAX_SIZE);
        if (NULL == buf) {
            ALOGE("malloc fail\n");
            goto close_socket;
        }
        bufl = BUF_MAX_SIZE;
       	memset(buf, 0, BUF_MAX_SIZE);
		tee_get_ca_name(cr.pid, ca_name, MAX_PATH_LENGTH);
        if(!tee_get_app_cert(cr.pid, cr.uid, &bufl, buf, &type)) {
			ret = tee_check_ca_cert(type, buf, bufl, cr.uid, cr.pid);
            if ( 0 == ret) {
                ret = ioctl(fd, TC_NS_CLIENT_IOCTL_LOGIN, buf);
                if(ret) {
                    ALOGE("Failed to set login information for client[%s] uid[0x%x] err=%u!\n", ca_name, cr.uid, ret);
                    /* Since login information was not set we can't allow the client
                    * to get the socket */
                    //close(fd);
                    goto close_socket;
                }
            } else {
                ALOGE("CERT check client[%s] uid[0x%x] failed<%d>.\n", ca_name, cr.uid, ret);
                goto close_socket;
            }
        }
        else {
            ALOGE("Failed to get app[%s] cert!\n", ca_name);
            /* Inform the driver the cert could not be set */
            ret = ioctl(fd, TC_NS_CLIENT_IOCTL_LOGIN, NULL);
            if(ret) {
                ALOGE("Failed to set login information for client[%s] uid[0x%x] err=%u!\n", ca_name, cr.uid, ret);
                goto close_socket;
            }
        }

        if(fd > 0)
            ret = send_file_descriptor(s2, fd);
            if(ret < 0) {
                ALOGE("Failed to send file desc client[%s] uid[0x%x] err=%u!\n", ca_name,cr.uid, ret);
            }

close_socket:
        if(fd > 0)
            close(fd);
	if (buf != NULL )
	    free(buf);
        close(s2);
    }

    pthread_exit(0);
    return NULL;
}
