/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : dx_client_api.c
* Description :
* Platform    :
* Author      : qiqingchao
* Version     : V1.0
* Date        : 2013.5.29
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
//#include <sys/mman.h> /*for mmap*/
#include <stdio.h>
#include <stdlib.h>
#include "dx_client_api.h"
#include "tee_client_api.h"
#include "tc_ns_client.h"
#include "tee_client_id.h"

//��Ҫ�밲ȫ��ta_framework.c��һ��
typedef struct{
    uint32_t session_id;  /**< Session ID  */
    TEEC_UUID service_id;  /**< Service ID  */
}dx_session_info;

static uint32_t g_multiple_size = 0;

static TEEC_Result global_task_of_content_path(Dx_Client_Tz_Session pSession){
    TEEC_Result ret = TEEC_SUCCESS;
    uint32_t multiple_size = g_multiple_size;
    TEEC_SharedMemory sharedMem;
    //global task
    TEEC_Context *context = pSession->session->context;
    TEEC_Operation operation;
    uint32_t origin;
    TEEC_Result result;
    TEEC_UUID global_uuid = TEE_SERVICE_GLOBAL;
    TEEC_Session session;
    dx_session_info session_info;
    uint32_t cmdID = (pSession->cp_init_flag)?
        GLOBAL_CMD_ID_TERMINATE_CONTENT_PATH:GLOBAL_CMD_ID_INIT_CONTENT_PATH;

    //ͨ��global task�����ô˽ӿڵ�session��Ӧ��content path����
    result = TEEC_OpenSession(
                context,
                &session,
                &global_uuid,
                TEEC_LOGIN_PUBLIC,
                NULL,
                NULL,
                NULL);

    if(result != TEEC_SUCCESS) {
        goto cleanup_2;
    }

    //����session�����ڴ棬������contentpath��session���ݸ�globaltask
    sharedMem.size = sizeof(dx_session_info);
    sharedMem.flags = TEEC_MEM_INPUT;
    ret = TEEC_AllocateSharedMemory(context, &sharedMem);
    if(ret != TEEC_SUCCESS){
        TEEC_Error("TEEC_AllocateSharedMemory failed\n");
        goto cleanup_3;
    }
    session_info.session_id = pSession->session->session_id;
    memcpy(&session_info.service_id, &pSession->session->service_id, sizeof(TEEC_UUID));
    memcpy(sharedMem.buffer, &session_info, sizeof(dx_session_info));

    //����invokecommand֪ͨ��ȫ�ཫ���뵽��buffer����Ϊ��Ӧ��ȫ��־λ
    operation.started = 1;
    operation.cancel_flag = 0;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_MEMREF_PARTIAL_INOUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INOUT,
        TEEC_NONE);
    operation.params[0].memref.parent = pSession->sharedMem;
    operation.params[0].memref.offset = 0;
    operation.params[0].memref.size = multiple_size;
    operation.params[1].memref.parent = &sharedMem;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(dx_session_info);
    //���ڼ�¼��ȫ�ഫ�����ĵ�ַ�����offset
    operation.params[2].value.a = 0;
    operation.params[2].value.b = 0;
    ret = TEEC_InvokeCommand(&session, cmdID, &operation, &origin);
    if(ret != TEEC_SUCCESS){
        TEEC_Error("GLOBAL_CMD_ID_INIT_CONTENT_PATH failed\n");
        goto cleanup_4;
    }
    else{
        TEEC_Debug("GLOBAL_CMD_ID_INIT_CONTENT_PATH success\n");
    }

    //TEEC_Debug("param0:size %d, offset %d, parentaddr 0x%x, parentsize %d\n",
      //  multiple_size, operation.params[2].value.a,
       // (uint32_t)pSession->sharedMem->buffer, pSession->sharedMem->size);
    //�û�̬��Ҫ���ݰ�ȫ���ַƫ������Ӧ��offset
    pSession->virtual_addr = operation.params[2].value.a + pSession->base_addr;

cleanup_4:
    TEEC_ReleaseSharedMemory(&sharedMem);
cleanup_3:
    TEEC_CloseSession(&session);
cleanup_2:
    return ret;

}

DxStatus DxTzClient_InitSecureContentPath(Dx_Client_Tz_Session pSession){
    TEEC_Result ret = TEEC_SUCCESS;
    uint32_t align_size = ALIGN_SIZE;//32KB����
    uint32_t multiple_size = 0;

    if(!pSession){
        TEEC_Error("pSession is NULL\n");
        return (DxStatus)TEEC_ERROR_BAD_PARAMETERS;
    }
    if(!pSession->size){
        TEEC_Error("pSession->size is 0\n");
        return (DxStatus)TEEC_ERROR_BAD_PARAMETERS;
    }
    //buffer��С������32KB��2��ָ������������Ϊ��ȫ������ʱ��ȫ�ڴ���С������32KB����ַҲҪ32KB����
    /*DTS2013070205024 begin q00209673*/
    if(pSession->size <= ALIGN_SIZE)
        multiple_size = ALIGN_SIZE;//32KB
    else if(pSession->size > ALIGN_SIZE && pSession->size <= ALIGN_SIZE*2)
        multiple_size = ALIGN_SIZE*2;//64KB
    else if(pSession->size > ALIGN_SIZE*2 && pSession->size <= ALIGN_SIZE*4)
        multiple_size = ALIGN_SIZE*4;//128KB
    else if(pSession->size > ALIGN_SIZE*4 && pSession->size <= ALIGN_SIZE*8)
        multiple_size = ALIGN_SIZE*8;//256KB
    else if(pSession->size > ALIGN_SIZE*8 && pSession->size <= ALIGN_SIZE*16)
        multiple_size = ALIGN_SIZE*16;//512KB
    else if(pSession->size > ALIGN_SIZE*16 && pSession->size <= ALIGN_SIZE*32)
        multiple_size = ALIGN_SIZE*32;//1MB
    else if(pSession->size > ALIGN_SIZE*32 && pSession->size <= ALIGN_SIZE*64)
        multiple_size = ALIGN_SIZE*64;//2MB
    else if(pSession->size > ALIGN_SIZE*64 && pSession->size <= (ALIGN_SIZE*128-ALIGN_SIZE))
        multiple_size = ALIGN_SIZE*128-ALIGN_SIZE;//4MB-32KB
    else{
        TEEC_Error("The largest memroy is 4M-32KB\n");
        return (DxStatus)TEEC_ERROR_OUT_OF_MEMORY;
    }
    g_multiple_size = multiple_size;
    /*DTS2013070205024 end q00209673*/
    if(!pSession->sharedMem){
        TEEC_Error("pSession->sharedMem is NULL\n");
        return (DxStatus)TEEC_ERROR_BAD_PARAMETERS;
    }

    pSession->sharedMem->size = multiple_size + align_size;
    pSession->sharedMem->flags = TEEC_MEM_INOUT;
    ret = TEEC_AllocateSharedMemory(pSession->session->context, pSession->sharedMem);
    if(ret != TEEC_SUCCESS){
        TEEC_Error("TEEC_AllocateSharedMemory failed\n");
        return ret;
    }

    pSession->base_addr = (uint8_t *)pSession->sharedMem->buffer;
    //��Ҫ��֤��ȫ�������ַ32KB���룬���������Ӧoffset���طǰ�ȫ��
    pSession->virtual_addr = NULL;
    pSession->cp_init_flag = 0;
    //ͨ��global task��contentpath������Ӧ��session
    ret = global_task_of_content_path(pSession);
    if(ret != TEEC_SUCCESS){
        TEEC_Error("global_task_of_content_path failed\n");
        TEEC_ReleaseSharedMemory(pSession->sharedMem);
        return ret;
    }
    //check the addr is secure or not
    #if 0
    if(pSession->virtual_addr){
        *pSession->virtual_addr = 0xff;
        TEEC_Debug("addr: 0x%x = 0x%x\n", (uint32_t)pSession->virtual_addr, *pSession->virtual_addr);
    }
    #endif

    return ret;
}

DxStatus DxTzClient_TerminateSecureContentPath(Dx_Client_Tz_Session pSession){
    uint32_t ret = TEEC_SUCCESS;
    TEEC_SharedMemory* sharedMem;

    if(!pSession){
        TEEC_Error("pSession is NULL\n");
        return (DxStatus)TEEC_ERROR_BAD_PARAMETERS;
    }
    if(!pSession->base_addr || !pSession->size){
        TEEC_Error("pSession->base_addr or size is NULL\n");
        return (DxStatus)TEEC_ERROR_BAD_PARAMETERS;
    }
    sharedMem = pSession->sharedMem;
    pSession->cp_init_flag = 1;
    ret = global_task_of_content_path(pSession);
    if(ret != TEEC_SUCCESS){
        TEEC_Error("global_task_of_content_path failed\n");
    }

    TEEC_ReleaseSharedMemory(sharedMem);
    return ret;
}
