/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : ta_framework.h
* Description :
* Author      : yaodongdong@huawei.com
* Date        : 2012.12.31
* Notes       :
*
*------------------------------------------------------------------------------
* Modifications:
*   Date        Author          Modifications
*******************************************************************************/
/*******************************************************************************
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
*******************************************************************************/

#ifndef __TA_FRAMWORK_H_
#define __TA_FRAMWORK_H_

#include <sre_task.h>
#include <sre_mem.h>
#include <sre_sem.h>
#include <sre_msg.h>
#include "tee_internal_api.h"
#include "tee_common.h"
#include "tee_fs.h"
#include "tee_time_api.h"

#define CALL_TRUSTZONE_API  0x1

#define TASK_INVALID_HANDLE    ((TSK_HANDLE_T)0xffffffff)
#define MSG_DEFAULT_HANDLE    (0)
#define MSG_DEFAULT_VALUE    (0xff)
#define MSG_ABORT_VALUE     (0xf0)

#define GLOBAL_SERVICE_NAME   OS_INIT_TASK_NAME

typedef unsigned int     pa_t;
typedef unsigned int     va_t;

typedef struct {
    unsigned int    uuid_phys;
    unsigned int    cmd_id;
    unsigned int    dev_file_id;
    unsigned int    context;    // high_16bits = service_index | low16_bits = session_id
    unsigned int    agent_id;
    unsigned int    operation_phys;
    unsigned int    login_method;
    unsigned int    login_data;
    unsigned int    err_origin;
} smc_cmd_t;

#define SERVICE_NAME_MAX    100
#define SESSION_MAX         10  //concurrent opened session count

#define AGENT_BUFF_SIZE     (4*1024)
//agent id
#define TEE_FS_AGENT_ID     0x46536673      //FSfs
#define TEE_MISC_AGENT_ID   0x4d495343      //MISC

//session context contain of service index(high 16 bits) and session id(low 16 bits)
#define SET_SESSION_CONTEXT(index, id)  ((index<<16) | (id&0x0000ffff))
#define SERVICE_INDEX_OF_CONTEXT(context)   (context >> 16)
#define SESSION_ID_OF_CONTEXT(context)  (context&0x0000ffff)

typedef struct {
    TEE_UUID uuid;
    uint32_t stack_size;
    uint32_t heap_size;
    bool single_instance;
    bool multi_session;
    bool keep_alive;
    char reserved;
    char *other_buff;   //TA's non-std property
    uint32_t other_len; //non-std propery buff len
}TA_property_t;

typedef struct {
    TEE_Result ret_val;
    uint32_t ret_origin;
    bool cmd_processed;
}TA_retval_t;

//data for async call
struct timer_notify_data {
    uint32_t dev_id;
    TEE_UUID uuid;
    uint32_t session_id;
};

//global call TA entrypoit cmd
#define CALL_TA_INIT                0x01
#define CALL_TA_CLEAR               0x02
#define CALL_TA_INIT_NOSTD_PROP     0x03
#define CALL_TA_CREATE              0x10
#define CALL_TA_OPEN_SESSION        0x11
#define CALL_TA_INVOKE_CMD          0x12
#define CALL_TA_CLOSE_SESSION       0x13
#define CALL_TA_DESTROY             0x14
#define CALL_TA_CP_INIT             0x15
#define CALL_TA_CP_TERMINATE        0x16

struct global_to_TA_msg{
    uint32_t session_id;
    uint32_t cmd_id;
    uint32_t param_type;
    TEE_Param *params;
    void *session_context;
    uint32_t dev_id;
};

struct TA_to_global_msg{
    TEE_Result ret;
    uint32_t agent_id;
    void *session_context;
};

struct TA_init_msg{
    void *fs_mem;   //fs agent share mem
    void *misc_mem; //misc agent share mem
    TA_property_t prop;
    uint32_t login_method;
    void *time_data;    //async call notify share data
    uint32_t dev_id;
    uint32_t session_id;
    TEE_Time sys_time;
    uint32_t rtc_time;
};

#define MIX_MSG_SIZE (sizeof(struct TA_init_msg) > sizeof(struct global_to_TA_msg)  ? \
                        sizeof(struct TA_init_msg):sizeof(struct global_to_TA_msg))

TEE_Result register_service(const char *name,TEE_UUID *uuid, struct sessison_task_info* info, bool build_in);
void ta_framework_init(void);
void reset_ta_context(void);
void init_service_property(TEE_UUID *uuid, uint32_t stack, uint32_t heap,
                           bool single_instance, bool multi_session, bool keep_alive,
                           const char *other_buff, uint32_t other_len);
TEE_Result get_build_in_services_property(TEE_UUID *service, TA_property_t *property);
void init_task_handle_array(void);
void set_TEE_return(TEE_Result ret_val, bool processed);
void proceed_return_code(void);
TEE_Result get_TEE_return(void);
bool is_command_processed(void);
TEE_Result start_TA_task(void);
void get_operation_params(uint32_t* param_type, TEE_Param** params);
TEE_Result init_ta_context(bool *is_global, uint32_t *cmd_id, uint32_t *cmd_type);
bool need_load_srv(TEE_UUID *uuid);
TEE_Result open_session_from_normal(void);
TEE_Result close_session_from_normal(void);
TEE_Result kill_crash_task(void);
TEE_Result map_ns_operation(void);
TEE_Result unmap_ns_operation(void);
TEE_Result register_notify_memery(void);
TEE_Result unregister_notify_memery(void);
TEE_Result register_agent(void);
TEE_Result unregister_agent(void);
void map_exception_mem(void);
TEE_Result init_content_path(void);
TEE_Result terminate_content_path(void);
void init_startup_time(void);
TEE_Result get_tee_time(void);

#endif
