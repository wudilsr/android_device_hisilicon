/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2014
*------------------------------------------------------------------------------
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
*******************************************************************************/
#ifndef _TEE_CA_DAEMON_H_
#define _TEE_CA_DAEMON_H_

#define TC_NS_SOCKET_NAME "#tc_ns_socket"

#define TEE_MULTIUSER_SOCKET_NAME "tee-multi-user"
#define SFS_PARTITION_USER_SYMLINK "sec_storage_data_users/"
#define SEC_STORAGE_DATA_USERS "/data/"SFS_PARTITION_USER_SYMLINK
#define SEC_STORAGE_DATA_USER_0 "/data/"SFS_PARTITION_USER_SYMLINK"0"

#define TRANS_BUFF_SIZE (4*1024)    //agent transfer share buffer size
/*when reset to factory mode, keep the data in this patition*/
#define SEC_STORAGE_ROOT_DIR    "/sec_storage/"
/*when reset to factory mode, clear the data in this patition*/
#define SEC_STORAGE_DATA_DIR    "/data/sec_storage_data/"
#define USER_DATA_DIR "/data/"
#define ROOT_DIR "/"
#define ROOT_DIR_PERM   (S_IRUSR|S_IWUSR)   //0600 only root can read and write sec_storage folder
#define SEC_STORAGE_PARTITION "/dev/block/platform/hi_mci.0/by-name/securetystorage"
#define SFS_PARTITION_PERSISTENT "sec_storage/"
#define SFS_PARTITION_TRANSIENT "sec_storage_data/"

#define THREAD_CA_SERVER_PROPERTY           "thread_ca_server_work_property"
#define THREAD_CA_SERVER_PROPERTY_READY     "1"

typedef struct {
    int magic;
    int status;
    int userid;
    int reserved;
} recv_msg_t;
#define MU_MSG_MAGIC 0xff00ff00
enum MU_MSG_Status {
    MU_MSG_STAT_NEW_USER = 0x01,
    MU_MSG_STAT_RM_USER = 0x02,
    MU_MSG_STAT_SWITCH_USER = 0x03,
};
enum MU_MSG_USERID {
    MU_MSG_USERID_OWNER = 0x0,
    MU_MSG_USERID_MAX = 0xFF,
};

int unlink_recursive(const char* name);
//int make_sec_storage_dir(char* storage_dir); //del by f00216599
void* thread_multi_user_server_work(void *dummy);
void* thread_ca_server_work(void *dummy);
#endif
