/*
 * FileName:
 * Author:         l00202565  Version: 0.0.1  Date: 2013-5-20
 * Description:
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */

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

#include "tee_client_api.h"
#include "tee_client_id.h"
#include "tc_ns_client.h"
#include "tee_client_app_load.h"

const char* IMAGE_PATH = "/data";

static TEEC_Result TEEC_AppLoadCmd(TEEC_SharedMemory* sharedMem,
        TEEC_Context* context, uint32_t cmd_id, uint32_t ioctrl_id);

static int32_t TEEC_NeedLoadApp(TEEC_Context* context,
        const TEEC_UUID *srv_uuid);

static int32_t TEEC_LoadApp(TEEC_Context* context,
        const char *loadfile);

static void TEEC_LoadApp_Exception(TEEC_Context* context);

extern TEEC_Result TEEC_CheckOperation (
        TEEC_Operation *operation);

extern void TEEC_Encode(
        TC_NS_ClientContext* cli_context,
        TEEC_UUID service_id,
        uint32_t session_id,
        uint32_t cmd_id,
        TC_NS_ClientLogin cli_login,
        TEEC_Operation* operation);

/*
 * Function:       TEEC_StartApp
 * Description:    This function starts an app
 * Parameters:     context: a pointer to an initialized TEE Context.
 *                 srv_uuid: a pointer to the secure service application UUID.
 * Return:         > 0: application load success
 *                 == 0: no need to load application
 *                 < 0: erro
 */
int32_t TEEC_StartApp(
        TEEC_Context* context,
        const TEEC_UUID *srv_uuid)
{
    int32_t ret;
    const char* fpath;
    char fname[MAX_FILE_NAME_LEN];
    int32_t file_path_len;
    int32_t len;
    char temp_fname[MAX_FILE_PATH_LEN + MAX_FILE_NAME_LEN + MAX_FILE_EXT_LEN];

    if (NULL == context || NULL == srv_uuid) {
        TEEC_Error(" param erro!\n");
        return -1;
    }

    /* judge if commom service, image file may not exist */
    ret = TEEC_NeedLoadApp(context, srv_uuid);
    if (ret < 0) {
        TEEC_Error("NeedLoadApp service erro\n");
        return ret;
    } else if (ret == 0) {
        TEEC_Debug("no need to load service\n");
        return ret;
    }
    /* else, not common service, need load */
    TEEC_Debug("need to load app image\n");

    /* get file name and file patch */
    if(context->ta_path && strstr(context->ta_path, ".sec")){
        /* app load */
        ret = TEEC_LoadApp(context, context->ta_path);
        if (ret < 0) {
            TEEC_Error("teec load app %s erro\n", context->ta_path);
        }
    }
    else{
        fpath = IMAGE_PATH;
        ret = snprintf(fname, MAX_FILE_NAME_LEN,
                "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                srv_uuid->timeLow, srv_uuid->timeMid, srv_uuid->timeHiAndVersion,
                srv_uuid->clockSeqAndNode[0], srv_uuid->clockSeqAndNode[1],
                srv_uuid->clockSeqAndNode[2], srv_uuid->clockSeqAndNode[3],
                srv_uuid->clockSeqAndNode[4], srv_uuid->clockSeqAndNode[5],
                srv_uuid->clockSeqAndNode[6], srv_uuid->clockSeqAndNode[7]);
        if (ret > MAX_FILE_NAME_LEN) {
            TEEC_Error("get file name err\n");
            return -1;
        }

        file_path_len = strnlen(fpath, MAX_FILE_PATH_LEN);
        file_path_len = file_path_len + strnlen(fname, MAX_FILE_NAME_LEN);
        file_path_len = file_path_len + MAX_FILE_EXT_LEN;
        len = snprintf(temp_fname, file_path_len, "%s/%s.sec", fpath, fname);
        if (len > (file_path_len -1)) {
            TEEC_Error("file path too long\n");
            return -1;
        }

        /* app load */
        ret = TEEC_LoadApp(context, temp_fname);
        if (ret < 0) {
            TEEC_Error("teec load app erro\n");
        }
    }

    return ret;
}

static TEEC_Result TEEC_AppLoadCmd(TEEC_SharedMemory* sharedMem,
        TEEC_Context* context, uint32_t cmd_id, uint32_t ioctrl_id)
{
    int32_t ret;
    TEEC_Operation operation;
    TEEC_Result teec_ret;
    TC_NS_ClientContext cli_context;
    TC_NS_ClientLogin cli_login = {0, 0};
    TEEC_UUID uuid;

    if (sharedMem == NULL || context == NULL) {
        TEEC_Error("param erro!\n");
        return (TEEC_Result)TEEC_ERROR_GENERIC;
    }

    /* load app operation */
    operation.started = 1;
    operation.cancel_flag = 0;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_MEMREF_PARTIAL_INOUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    operation.params[0].memref.parent = sharedMem;
    operation.params[0].memref.offset = 0;
    operation.params[0].memref.size = sharedMem->size;
    teec_ret = TEEC_CheckOperation(&operation);
    if (teec_ret != TEEC_SUCCESS) {
        TEEC_Error("operation is invalid\n");
        return teec_ret;
    }

    /* uuid = 0, means global task */
    memset(&uuid, 0, sizeof(TEEC_UUID));

    /* encode load app client context */
    TEEC_Encode(&cli_context, uuid, 0, cmd_id, cli_login, &operation);

    /* driver app load */
    TEEC_Debug("invoke an app load command, fd %d, cmd id %d\n", context->fd, cli_context.cmd_id);
    ret = ioctl(context->fd, ioctrl_id, &cli_context);
    if (ret) {
        TEEC_Error("invoke cmd failed %d\n", ret);
        teec_ret = (TEEC_Result)ret;
    } else {
        teec_ret = TEEC_SUCCESS;
    }

    return teec_ret;
}

static int32_t TEEC_NeedLoadApp(
        TEEC_Context* context,
        const TEEC_UUID *srv_uuid)
{
    int32_t ret;
    TEEC_SharedMemory sharedMem;
    TEEC_Result result;
    uint32_t mem_input = (uint32_t)TEEC_MEM_INPUT;
    uint32_t mem_output = (uint32_t)TEEC_MEM_OUTPUT;

    if (context == NULL || srv_uuid == NULL) {
        TEEC_Error(" param erro!\n");
        return -1;
    }

    TEEC_Debug("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
            srv_uuid->timeLow, srv_uuid->timeMid, srv_uuid->timeHiAndVersion,
            srv_uuid->clockSeqAndNode[0], srv_uuid->clockSeqAndNode[1],
            srv_uuid->clockSeqAndNode[2], srv_uuid->clockSeqAndNode[3],
            srv_uuid->clockSeqAndNode[4], srv_uuid->clockSeqAndNode[5],
            srv_uuid->clockSeqAndNode[6], srv_uuid->clockSeqAndNode[7]);

    /* allocate sharememory send uuid */
    sharedMem.size = sizeof(TEEC_UUID);
    /* sharedMem.flags = TEEC_MEM_INPUT | TEEC_MEM_OUTPUT; */
    sharedMem.flags = mem_input | mem_output;
    result = TEEC_AllocateSharedMemory(context, &sharedMem);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed, %x\n", result);
        ret = -1;
        goto ALLOC_ERR;
    }
    memcpy((char*)sharedMem.buffer, (char*)srv_uuid, sizeof(TEEC_UUID));

    TEEC_Debug("need load app cmd %d\n", GLOBAL_CMD_ID_NEED_LOAD_APP);
    result = TEEC_AppLoadCmd(&sharedMem, context, GLOBAL_CMD_ID_NEED_LOAD_APP,
            TC_NS_CLIENT_IOCTL_NEED_LOAD_APP);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("app load ret err\n");
        ret = -1;
        goto EXIT_ERR;
    }

    ret = *(int32_t*)sharedMem.buffer;
    TEEC_Debug("need load app ret %d\n", ret);

EXIT_ERR:
    TEEC_ReleaseSharedMemory(&sharedMem);

ALLOC_ERR:
    return ret;
}


static int32_t TEEC_LoadApp(
        TEEC_Context* context,
        const char *loadfile)
{
    int32_t ret;
    FILE *fp;
    TEEC_image_head image_head;
    TEEC_image_identity img_identity;
    char *file_buf_pt;
    TEEC_SharedMemory sharedMem;
    TEEC_Result result;
    int32_t load_flag;
    int32_t send_img_len, total_img_len;
    uint32_t mem_input = (uint32_t)TEEC_MEM_INPUT;
    uint32_t mem_output = (uint32_t)TEEC_MEM_OUTPUT;
    uint32_t ta_hd_len = 0;

    if (context == NULL || loadfile == NULL) {
        TEEC_Error(" param erro!\n");
        return -1;
    }

    /* open image file */
    TEEC_Debug("load image file: %s\n", loadfile);
    fp = fopen(loadfile, "r");
    if (fp == NULL) {
        TEEC_Error("open file erro\n");
        TEEC_LoadApp_Exception(context);
        ret = -1;
        goto OPEN_ERR;
    }

    /* get magic-num & version-num */
    ret = fread(&img_identity, sizeof(TEEC_image_identity), 1, fp);
    TEEC_Debug("image idetity read ret %d\n", ret);
    if (ret != 1) {
        TEEC_Error("read file erro\n");
        TEEC_LoadApp_Exception(context);
        ret = -1;
        goto FREAD_ERR;
    }

    /* decide the TA verison */
    if (img_identity.magic_num1 == TA_HEAD_MAGIC1 &&
            img_identity.magic_num2 == TA_HEAD_MAGIC2 &&
            img_identity.version_num > 1) {
        TEEC_Debug("new verison ta\n");
        ta_hd_len = sizeof(TEEC_TA_HEAD);
    } else {
        /* read the oldverison head again */
        TEEC_Debug("old verison ta\n");
        ta_hd_len = sizeof(TEEC_image_head);
        ret = fseek(fp, 0, SEEK_SET);
        if (ret != 0) {
            TEEC_Error("fseek error\n");
            TEEC_LoadApp_Exception(context);
            ret = -1;
            goto FREAD_ERR;
        }
    }

    /* get image head */
    ret = fread(&image_head, sizeof(TEEC_image_head), 1, fp);
    TEEC_Debug("read ret %d\n", ret);
    if ((ret != 1) ||
            (image_head.context_len + ta_hd_len > MAX_IMAGE_LEN)) {
        TEEC_Error("read file erro\n");
        TEEC_LoadApp_Exception(context);
        ret = -1;
        goto FREAD_ERR;
    }

    ret = fseek(fp, 0, SEEK_SET);
    if (ret != 0) {
        TEEC_Error("fseek error\n");
        TEEC_LoadApp_Exception(context);
        ret = -1;
        goto FREAD_ERR;
    }

    TEEC_Debug("image_head context_len %d, manifest_crypto_len %d, manifest_plain_len %d\n",
            image_head.context_len, image_head.manifest_crypto_len, image_head.manifest_plain_len);
    TEEC_Debug("image_head manifest_str_len %d, cipher_bin_len %d, sign_len %d\n",
            image_head.manifest_str_len, image_head.cipher_bin_len, image_head.sign_len);

    /* allocate share memory */
    if (image_head.context_len + ta_hd_len + LOAD_IMAGE_FLAG_OFFSET
            > MAX_SHARE_BUF_LEN) {
        sharedMem.size = MAX_SHARE_BUF_LEN;
    } else {
        sharedMem.size = ta_hd_len + image_head.context_len
            + LOAD_IMAGE_FLAG_OFFSET;
    }
    /* sharedMem.flags = TEEC_MEM_INPUT | TEEC_MEM_OUTPUT; */
    sharedMem.flags = mem_input | mem_output;
    result = TEEC_AllocateSharedMemory(context, &sharedMem);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed, %x\n", result);
        TEEC_LoadApp_Exception(context);
        ret = -1;
        goto ALLOC_ERR;
    }

    /* send total elf image to secure world */
    total_img_len = image_head.context_len + ta_hd_len;
    while (total_img_len) {
        if (total_img_len > SEND_IMAGE_LEN) {
            load_flag = 1;
            send_img_len = SEND_IMAGE_LEN;
            total_img_len -= SEND_IMAGE_LEN;
        } else {
            load_flag = 0;
            send_img_len = total_img_len;
            total_img_len = 0;
        }

        /* load image data to share memory */
        file_buf_pt = (char*)sharedMem.buffer;
        *(int32_t*)file_buf_pt = load_flag;

        file_buf_pt += LOAD_IMAGE_FLAG_OFFSET;
        ret = fread(file_buf_pt, 1, send_img_len, fp);/* [false alarm]:´óÐ¡ÒÑ¾­½øÐÐ´¦Àí£¬²»»áÔ½½çÐ´Èë */
        if (ret != send_img_len) {
            TEEC_Error("read file erro, read ret %d\n, send_img_len %d\n", ret, send_img_len);
            TEEC_LoadApp_Exception(context);
            ret = -1;
            goto EXIT_ERR;
        }
        sharedMem.size = send_img_len;

        /* invoke a command */
        TEEC_Debug("load_flag %d\n", *(int32_t*)sharedMem.buffer);
        result = TEEC_AppLoadCmd(&sharedMem, context, GLOBAL_CMD_ID_LOAD_SECURE_APP,
                TC_NS_CLIENT_IOCTL_LOAD_APP_REQ);
        if (result != TEEC_SUCCESS) {
            TEEC_Error("app load com ret err\n");
            ret = -1;
            goto EXIT_ERR;
        }
    }

    /* app load success ret */
    ret = *(int32_t*)sharedMem.buffer;
    TEEC_Debug("tee app load sucess, share buf ret value: %d\n", ret);

    /* app load fail ret */
EXIT_ERR:
    TEEC_ReleaseSharedMemory(&sharedMem);
ALLOC_ERR:
FREAD_ERR:
    fclose(fp);

OPEN_ERR:
    return ret;
}

static void TEEC_LoadApp_Exception(TEEC_Context* context)
{
    int ret = 0;

    ret = ioctl(context->fd, TC_NS_CLIENT_IOCTL_LOAD_APP_EXCEPT, ret);
    if (ret) {
        TEEC_Error("load app exception handle err\n");
    }
}
