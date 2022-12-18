/*
 * FileName:      rootagent_api.c
 * Author:        z00321956
 * Description:   rootagent  API
 * Version:       0.0.1
 * Date:          2016-04-01
 */
 #include <linux/mutex.h>
 #include <linux/random.h>
 #include <linux/slab.h>
 #include <linux/mm.h>

 #include "teek_client_api.h"
 #include "teek_client_id.h"

 #include "rootagent_mem.h"
 #include "rootagent_api.h"
 #include "rootagent_crypto.h"

 static TEEC_Context gContext = {0};
 static TEEC_Session gSession = {0};
 static int gInited = 0;//是否初始化
 static int gCount = 0;//初始化次数统计
 static TEEC_UUID uuid = UUID_RM_TA;//内置TA唯一ID
 static TEEC_TempMemoryReference gMem = {0};//申请的读写内存
 static DEFINE_MUTEX(root_monitor_lock);//锁
 static TEEC_TempMemoryReference m_swap_mem;
 static uint8_t m_chal_req_key[CHALLENGE_REQ_KEY_LENGTH];
 static uint8_t m_chal_key[CHALLENGE_KEY_LENGTH];
 static uint8_t m_nounce[CHALLENGE_NOUNCE_LENGTH];

 //出现未知异常后，释放资源，重新初始化
void root_monitor_finalize(void){
	 mutex_lock(&root_monitor_lock);
	 rm_mem_destroy();
	 TEEK_CloseSession(&gSession);
	 TEEK_FinalizeContext(&gContext);
	 gInited--;
	 mutex_unlock(&root_monitor_lock);
 }


TEEC_Result root_monitor_tee_init(void){
	TEEC_Result result;
	uint32_t origin;
    TEEC_Operation operation = {0};
    u8 package_name[] = "antiroot-ca";
    u32 root_id = 0;

	mutex_lock(&root_monitor_lock);
    if (gInited){
        antiroot_debug(ROOTAGENT_DEBUG_API, "RootAgent has already initialized");
		mutex_unlock(&root_monitor_lock);
        return 0;
    }
	result = rm_mem_init();
	if(result){
		antiroot_error("rm_mem_init failed\n");
		mutex_unlock(&root_monitor_lock);
		return -1;
	}
    if(initial_rm_shared_mem(&gMem, &m_swap_mem)){
		antiroot_error("Initial swap or share memory failed\n");
		mutex_unlock(&root_monitor_lock);
		return -1;
    }
	result = TEEK_InitializeContext(NULL, &gContext);
    if(result != TEEC_SUCCESS){
        antiroot_error("root_monitor_tee_init failed\n");
        goto cleanup_2;
    }

    operation.started = 1;
    operation.cancel_flag = 0;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_MEMREF_TEMP_INPUT);
    operation.params[2].tmpref.buffer = (void *)(&root_id);
    operation.params[2].tmpref.size = sizeof(root_id);
    operation.params[3].tmpref.buffer = (void *)(package_name);
    operation.params[3].tmpref.size = strlen(package_name) + 1;
    result = TEEK_OpenSession(&gContext, &gSession,
            &uuid, TEEC_LOGIN_IDENTIFY , NULL, &operation, &origin);
    if (result != TEEC_SUCCESS) {
		antiroot_error("root agent open session failed\n");
		goto cleanup_1;
    }
    gInited++;
	gCount++;
	antiroot_debug(ROOTAGENT_DEBUG_API,
			"root_monitor_tee_init ok, initialized count: %d, gInited: %d\n",
			gCount, gInited);
	mutex_unlock(&root_monitor_lock);
    return 0;

cleanup_1:
    TEEK_FinalizeContext(&gContext);
cleanup_2:
    rm_mem_destroy();
	mutex_unlock(&root_monitor_lock);
    return result;
}

//设置白名单
TEEC_Result setting_config(RAGENT_CONFIG *config, RAGENT_ROOTPROC *root_proc){

	uint32_t origin;
	TEEC_Result result;
	if (!gInited || !gMem.buffer){
        antiroot_error("Agent should be initialized first!\n");
		return -1;
	}
	if(!config || !root_proc || !root_proc->procid){
		antiroot_error("Bad params!\n");
		return -1;
	}

	memset(gMem.buffer, 0x0, gMem.size);
	antiroot_debug(ROOTAGENT_DEBUG_API,
			"gMem.buffer add: %p, gMem.size: %d\n",
			gMem.buffer, gMem.size);
	TEEC_Operation operation;
	memset(&operation, 0, sizeof(TEEC_Operation));
	operation.started = 1;
	operation.paramTypes = TEEC_PARAM_TYPES( TEEC_MEMREF_TEMP_INOUT,
												TEEC_NONE,
												TEEC_NONE ,
												TEEC_NONE );
	operation.params[0].tmpref.buffer = gMem.buffer;
    operation.params[0].tmpref.size = gMem.size;
	RAGENT_COMMAND *rm_command = (RAGENT_COMMAND*)gMem.buffer;
	rm_command->magic = MAGIC;
	rm_command->version = VERSION;
	rm_command->interface = ROOTAGENT_CONFIG_ID;
	rm_command->content.config.white_list.selinux = config->white_list.selinux;
	rm_command->content.config.white_list.proclength = root_proc->length;
    memcpy(m_chal_req_key, config->cipher_key.cha_req_key, CHALLENGE_REQ_KEY_LENGTH);
    memcpy(rm_command->content.config.cipher_key.cha_req_key,
			config->cipher_key.cha_req_key, CHALLENGE_REQ_KEY_LENGTH);
    memcpy(m_chal_key, config->cipher_key.cha_key, CHALLENGE_KEY_LENGTH);
    memcpy(rm_command->content.config.cipher_key.cha_key,
			config->cipher_key.cha_key, CHALLENGE_KEY_LENGTH);

    memcpy(rm_command->content.config.white_list.kcodes,
			config->white_list.kcodes, KERNEL_CODE_LENGTH_SHA);
    memcpy(rm_command->content.config.white_list.syscalls,
			config->white_list.syscalls, SYSTEM_CALL_LENGTH_SHA);
    memcpy(rm_command->content.config.white_list.sehooks,
			config->white_list.sehooks, SELINUX_HOOKS_LENGTH_SHA);

	antiroot_debug(ROOTAGENT_DEBUG_API,
			"setting_config-------proclength:%d\n",
			rm_command->content.config.white_list.proclength);
    if(root_proc->length!=0 && root_proc->procid){
        memcpy(gMem.buffer + sizeof(RAGENT_COMMAND), root_proc->procid, root_proc->length);
    }else{
        antiroot_error("root_proc is NULL!");
        return -1;
    }
    antiroot_debug(ROOTAGENT_DEBUG_API,
			"rm_command add: %p, magic: %d, version: %d, interface:%d, selinux:%d, root_proc.length:%d \n",
			rm_command, rm_command->magic, rm_command->version, rm_command->interface,
				rm_command->content.config.white_list.selinux,
				rm_command->content.config.white_list.proclength);

	result = TEEK_InvokeCommand( &gSession, ROOTAGENT_CONFIG_ID, &operation, &origin);
	if(result != TEEC_SUCCESS){
		antiroot_error("Setting_config failed \n");
	}
	memset(gMem.buffer, 0x0, gMem.size);
	return result;
}
//请求挑战字
TEEC_Result request_challenge(RAGENT_CHALLENGE *ichallenge){

	uint32_t origin;
	TEEC_Result result;
	if (!gInited || !gMem.buffer){
        antiroot_error("Agent should be initialized first!\n");
		return -1;
	}
	if(!ichallenge){
		antiroot_error("Bad params!\n");
		return -1;
	}
	memset(gMem.buffer, 0x0, gMem.size);
	memset(m_swap_mem.buffer, 0x0, m_swap_mem.size);
	antiroot_debug(ROOTAGENT_DEBUG_API, "gMem.buffer add: %p, gMem.size: %d \n", gMem.buffer, gMem.size);

	TEEC_Operation operation;
	memset(&operation, 0, sizeof(TEEC_Operation));
	operation.started = 1;
	operation.paramTypes = TEEC_PARAM_TYPES( TEEC_MEMREF_TEMP_INOUT,
								TEEC_NONE,
								TEEC_NONE ,
								TEEC_NONE );
	operation.params[0].tmpref.buffer = gMem.buffer;
    operation.params[0].tmpref.size = gMem.size;

    get_random_bytes(gMem.buffer, IV_SIZE);//generate random iv
	void *rm_command_out_in = (void *)(gMem.buffer + IV_SIZE);
	void *rm_command_in_out = (void *)m_swap_mem.buffer;
    if(!rm_command_in_out){
        antiroot_error("malloc failed!\n");
        return -1;
    }
	RAGENT_COMMAND *rm_command = (RAGENT_COMMAND *)rm_command_in_out;
	rm_command->magic = MAGIC;
	rm_command->version = VERSION;
	rm_command->interface = ROOTAGENT_CHALLENGE_ID;
	rm_command->content.challenge.cpuload = ichallenge->cpuload;
	rm_command->content.challenge.battery = ichallenge->battery;
	rm_command->content.challenge.charging = ichallenge->charging;
	rm_command->content.challenge.time = ichallenge->time;
	rm_command->content.challenge.timezone = ichallenge->timezone;
    memset(rm_command->content.challenge.nounce, 0, CHALLENGE_NOUNCE_LENGTH);
    memset(m_nounce, 0, CHALLENGE_NOUNCE_LENGTH);
    do_aes256_cbc(rm_command_out_in, rm_command_in_out,
			gMem.buffer, &m_chal_req_key, ANTIROOT_SRC_LEN, ENCRYPT);
    result = TEEK_InvokeCommand( &gSession, ROOTAGENT_CHALLENGE_ID, &operation, &origin);
    if(result != TEEC_SUCCESS){
		antiroot_error("Request_challenge failed\n");
	}else{

        do_aes256_cbc(rm_command_in_out,
				rm_command_out_in,gMem.buffer, &m_chal_key, ANTIROOT_SRC_LEN, DECRYPT);

        memcpy(m_nounce, rm_command->content.challenge.nounce,
				CHALLENGE_NOUNCE_LENGTH);
        memcpy(ichallenge->challengeid,
				rm_command->content.challenge.challengeid,
				CHALLENGE_MAX_LENGTH*sizeof(uint32_t));
        antiroot_debug(ROOTAGENT_DEBUG_API, "Request_challenge successful \n");
	}
    return result;
}
//返回扫描结果
TEEC_Result feedback_response(RAGENT_RESPONSE *response, RAGENT_ROOTPROC *root_proc){

	uint32_t origin;
	TEEC_Result result;
	TEEC_Operation operation;

	if (!gInited || !gMem.buffer){
        antiroot_error("Agent should be initialized first!\n");
		return -1;
	}

	if(!response){
		antiroot_error("Bad params!\n");
		return -1;
	}
	memset(gMem.buffer, 0x0, gMem.size);
	memset(m_swap_mem.buffer, 0x0, m_swap_mem.size);
	antiroot_debug(ROOTAGENT_DEBUG_API,
			"gMem.buffer add: %p, gMem.size: %d \n", gMem.buffer, gMem.size);
	antiroot_debug(ROOTAGENT_DEBUG_API,
			"m_swap_mem.buffer add: %p, m_swap_mem.size: %d \n",
			m_swap_mem.buffer, m_swap_mem.size);
	memset(&operation, 0, sizeof(TEEC_Operation));
	operation.started = 1;
	operation.paramTypes = TEEC_PARAM_TYPES( TEEC_MEMREF_TEMP_INOUT,
												TEEC_NONE,
												TEEC_NONE ,
												TEEC_NONE );
	operation.params[0].tmpref.buffer = gMem.buffer;
    operation.params[0].tmpref.size = gMem.size;
	get_random_bytes(gMem.buffer, IV_SIZE);//generate random iv
	void *rm_command_out = (void *)(gMem.buffer + IV_SIZE);
	void *rm_command_in = (void *)m_swap_mem.buffer;
    if(!rm_command_in){
        antiroot_error("response kmalloc failed! \n");
        return -1;
    }
	RAGENT_COMMAND *rm_command = (RAGENT_COMMAND *)rm_command_in;
	rm_command->magic = MAGIC;
	rm_command->version = VERSION;
	rm_command->interface = ROOTAGENT_RESPONSE_ID;
	rm_command->content.response.proc_integrated = response->proc_integrated;
	rm_command->content.response.noop = response->noop;
	rm_command->content.response.runtime_white_list.selinux
		= response->runtime_white_list.selinux;
	rm_command->content.response.runtime_white_list.proclength = root_proc->length;
    memcpy(rm_command->content.response.runtime_white_list.kcodes,
			response->runtime_white_list.kcodes, KERNEL_CODE_LENGTH_SHA);
    memcpy(rm_command->content.response.runtime_white_list.syscalls,
			response->runtime_white_list.syscalls, SYSTEM_CALL_LENGTH_SHA);
    memcpy(rm_command->content.response.runtime_white_list.sehooks,
			response->runtime_white_list.sehooks, SELINUX_HOOKS_LENGTH_SHA);

    if(root_proc->procid&&(root_proc->length!=0)){
        int size = sizeof(RAGENT_COMMAND) + root_proc->length;
        if(size > (ANTIROOT_SRC_LEN)){
            antiroot_error("response is oom!! \n");
            return -1;
        }
        memcpy((char*)rm_command + sizeof(RAGENT_COMMAND),
				root_proc->procid, root_proc->length);
    }

    do_aes256_cbc(rm_command_out, rm_command_in,
			gMem.buffer, m_nounce, ANTIROOT_SRC_LEN, ENCRYPT);
   	result = TEEK_InvokeCommand(
			&gSession, ROOTAGENT_RESPONSE_ID, &operation, &origin);
	if(result != TEEC_SUCCESS){
		antiroot_error("Feedback_response failed. result = 0x%x\n", result);
	}
    if(result == RA_ERROR_PH_ROOT || result == RA_ERROR_PH_LOCK )
        antiroot_info("need to power off \n");
    return result;
}
