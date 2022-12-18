#include <stdio.h>
#include <string.h>
#include "DxTzClientAPI.h"
#include "tee_client_api.h"
#include "DX_VOS_Errors.h"
#include "hi_unf_hdmi.h"
#include "hi_tz_common.h"
#define LOG_TAG "DxTzClientAPI"
#include <android/log.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_PHY_MEM_SIZE   (4*1024*1024)

static Dx_Client_Tz_Context gContext=DX_NULL;
//static DxUint32 gDxTzNumOpenSessions = 0;

struct Dx_Client_Tz_MemHandler_s{
    TEEC_SharedMemory mem;
};

struct Dx_Client_Tz_Context_s{
    Dx_TzAppId id;
    TEEC_Context context;
};

struct Dx_Client_Tz_Session_s{
    TEEC_Session session;
};
DxInt32 DxTzClient_HDMI_Init(void *session);
void DxTzClient_HDMI_DeInit(void);


/*----------------------Link list code ------------------*/
struct list_struct
{
    void *val;
    struct list_struct *next;
};

struct list_struct *head = NULL;
struct list_struct *curr = NULL;

struct list_struct* create_list(void *val)
{
    TEEC_Debug(" creating list with headnode as [%x]\n",val);
    struct list_struct *ptr = (struct list_struct*)malloc(sizeof(struct list_struct));
    if(NULL == ptr)
    {
    	TEEC_Debug(" Node creation failed \n");
        return NULL;
    }
    ptr->val = val;
    ptr->next = NULL;

    head = curr = ptr;
    return ptr;
}

struct list_struct* add_to_list(void *val)
{
    if(NULL == head)
    {
        return (create_list(val));
    }

    TEEC_Debug(" Adding node to end of list with value [%x]\n",val);

    struct list_struct *ptr = (struct list_struct*)malloc(sizeof(struct list_struct));
    if(NULL == ptr)
    {
    	TEEC_Error(" Node creation failed \n");
        return NULL;
    }
    ptr->val = val;
    ptr->next = NULL;

    curr->next = ptr;
    curr = ptr;

    return ptr;
}

struct list_struct* search_in_list(void *val, struct list_struct **prev)
{
    struct list_struct *ptr = head;
    struct list_struct *tmp = NULL;
    bool found = false;

    TEEC_Debug(" Searching the list for value [%x] \n",val);

    while(ptr != NULL)
    {
        if(ptr->val == val)
        {
            found = true;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }

    if(true == found)
    {
        if(prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}

int delete_from_list(void *val)
{
    struct list_struct *prev = NULL;
    struct list_struct *del = NULL;

    TEEC_Debug(" Deleting value [%x] from list\n",val);

    del = search_in_list(val,&prev);
    if(del == NULL)
    {
        return -1;
    }
    else
    {
        if(prev != NULL)
            prev->next = del->next;

        if(del == curr)
        {
            curr = prev;
        }

        if(del == head)
        {
            head = del->next;
        }
    }
    free(del);
    del = NULL;

    return 0;
}
struct list_struct* get_position(int i)
{
	struct list_struct *ptr = head;
	bool found = false;
	int x=0;

	TEEC_Debug(" getting item from position [%d] \n",i);

    while(ptr != NULL && x<i)
    {
        ptr = ptr->next;
    }

    if (x != i)
    {
    	TEEC_Debug(" trying to get item from position [%d] which is not exist in the list\n",i);
    	return NULL;
    }

    return ptr;
}

/*---------------------Link list end ---------------------*/
static int g_reg_sighandle = 0;
static struct sigaction g_sigsegv_new,g_sigsegv_default;
static struct sigaction g_sigbus_new,g_sigbus_default;
static struct sigaction g_sigterm_new,g_sigterm_default;
#define IS_SET_SIGHANDLER() (g_reg_sighandle == 1 ? 1 : 0)
#define SET_SIGHANDLER() do{g_reg_sighandle = 1;}while(0)
#define UNSET_SIGHANDLER() do{g_reg_sighandle = 0;}while(0)
static void sig_handler(int signo)
{
	switch(signo){
		case SIGSEGV:
			sigaction(SIGSEGV,&g_sigsegv_default,NULL);
			// * release the input buffer memory and unmap it.
			DxTzClient_CleanupOnSignal();
			raise(SIGSEGV);
			break;
		case SIGBUS:
			sigaction(SIGBUS,&g_sigbus_default,NULL);
			 //* release the input buffer memory and unmap it.
			DxTzClient_CleanupOnSignal();
			raise(SIGBUS);
			break;
		case SIGTERM:
			sigaction(SIGTERM,&g_sigterm_default,NULL);
			 //* release the input buffer memory and unmap it.
			DxTzClient_CleanupOnSignal();
			raise(SIGTERM);
			break;
		default:
			// Do not raise
			break;
	}
}

static void reg_signal_handler()
{
/* TODO When signal occurs there is an infinite loop*/
	if(!IS_SET_SIGHANDLER())
	{
		g_sigsegv_new.sa_handler = sig_handler;
		sigemptyset((sigset_t *)&g_sigsegv_new.sa_mask);
		sigaddset((sigset_t *)&g_sigsegv_new.sa_mask,SIGSEGV);
		sigaction(SIGSEGV,&g_sigsegv_new,&g_sigsegv_default);

		g_sigbus_new.sa_handler = sig_handler;
		sigemptyset((sigset_t *)&g_sigbus_new.sa_mask);
		sigaddset((sigset_t *)&g_sigbus_new.sa_mask,SIGBUS);
		sigaction(SIGBUS,&g_sigbus_new,&g_sigbus_default);

		g_sigterm_new.sa_handler = sig_handler;
		sigemptyset((sigset_t *)&g_sigterm_new.sa_mask);
		sigaddset((sigset_t *)&g_sigterm_new.sa_mask,SIGTERM);
		sigaction(SIGTERM,&g_sigterm_new,&g_sigterm_default);

		SET_SIGHANDLER();
	}
}

static void unreg_signal_handler()
{
	if(IS_SET_SIGHANDLER()){
		sigaction(SIGSEGV,&g_sigsegv_default,NULL);
		sigaction(SIGBUS,&g_sigbus_default,NULL);
		sigaction(SIGTERM,&g_sigterm_default,NULL);

		UNSET_SIGHANDLER();
	}
}


// ------------------------ Cleanup On Signal ---------------------------

// Clean up system resources.
void DxTzClient_CleanupOnSignal()
{
	DxStatus ret;
	int i=0;
	struct list_struct *curre_cell=NULL;

	TEEC_Error("DxTzClient_CleanupOnSignal has been called due to signal");

	if(gContext == DX_NULL)
	{
		TEEC_Error("parameter context is NULL");
		return;
	}

	curre_cell= get_position(i);
	while(curre_cell != NULL)
	{
		DxTzClient_CloseSession((Dx_Client_Tz_Session)curre_cell->val);
	}

	DxTzClient_DestroyContext(gContext);
}

static void DxOperation2TEEOperation(Dx_Client_Tz_Operation *dx_operation, TEEC_Operation *tee_operation)
{
    tee_operation->started = 1;
    memcpy(&tee_operation->paramTypes, dx_operation, sizeof(Dx_Client_Tz_Operation));
#if 0
    int i;

    //tee_operation->paramTypes = dx_operation->paramTypes;

    for(i=0; i<4; i++){
        unsigned int DxOpParamType = DX_TZ_PARAM_TYPE_GET(dx_operation->paramTypes, i);
        switch (DxOpParamType){
        case DX_TZ_PARAM_TYPE_NONE:
//            break;
        case DX_TZ_PARAM_TYPE_VALUE_INPUT:
        case DX_TZ_PARAM_TYPE_VALUE_OUTPUT:
        case DX_TZ_PARAM_TYPE_VALUE_INOUT:
//            tee_operation->params[i].value.a = dx_operation->params[i].value.a;
//            tee_operation->params[i].value.b = dx_operation->params[i].value.b;
//            break;
        case DX_TZ_PARAM_TYPE_MEMREF_INPUT:
        case DX_TZ_PARAM_TYPE_MEMREF_OUTPUT:
        case DX_TZ_PARAM_TYPE_MEMREF_INOUT:
//            tee_operation->params[i].tmpref.buffer = dx_operation->params[i].memRef.buffer;
//           tee_operation->params[i].tmpref.size = dx_operation->params[i].memRef.size;
            break;
        case DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT:
            //printf("******** DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT ********\n");

            break;
        }
    }
#endif
}

static void TEEOperation2DxOperation(TEEC_Operation *tee_operation, Dx_Client_Tz_Operation *dx_operation)
{
    memcpy(dx_operation, &tee_operation->paramTypes, sizeof(Dx_Client_Tz_Operation));
#if 0
    int i;

    //dx_operation->paramTypes = tee_operation->paramTypes;

    for(i=0; i<4; i++){
        unsigned int teeParamType = TEEC_PARAM_TYPE_GET(tee_operation->paramTypes, i);
        switch (teeParamType){
        case TEEC_NONE:
            break;
        case TEEC_VALUE_INPUT:
        case TEEC_VALUE_OUTPUT:
        case TEEC_VALUE_INOUT:
            dx_operation->params[i].value.a = tee_operation->params[i].value.a;
            dx_operation->params[i].value.b = tee_operation->params[i].value.b;
            break;
        case TEEC_MEMREF_TEMP_INPUT:
        case TEEC_MEMREF_TEMP_OUTPUT:
        case TEEC_MEMREF_TEMP_INOUT:
//            dx_operation->params[i].memRef.buffer = tee_operation->params[i].tmpref.buffer;
            dx_operation->params[i].memRef.size = tee_operation->params[i].tmpref.size;
            break;
        case TEEC_MEMREF_WHOLE:
	    case TEEC_MEMREF_PARTIAL_INPUT:
	    case TEEC_MEMREF_PARTIAL_OUTPUT:
	    case TEEC_MEMREF_PARTIAL_INOUT:
            printf("******** TEEC_MEMREF share ********\n");
            break;
        }
    }
#endif
}

//this function is dummy for trustedcore
void DxTzClient_InitializeCapabilitiesStruct(DxTzClientCapabilities * clientCapabilitiesPtr)
{
	if(DX_NULL == clientCapabilitiesPtr)
	{
		TEEC_Error("InitializeCapabilities: clientCapabilitiesPtr is NULL");
		return;
	}

	memset(clientCapabilitiesPtr, 0, sizeof(DxTzClientCapabilities));
}

DxStatus DxTzClient_CreateContext2(Dx_Client_Tz_Context *pcontext, Dx_TzAppId  *appId, DxTzClientCapabilities * clientCapabilitiesPtr)
{
	return DxTzClient_CreateContext(pcontext,appId);
}

DxStatus DxTzClient_CreateContext(Dx_Client_Tz_Context *context, Dx_TzAppId  *appId)
{
    Dx_Client_Tz_Context tmp_context;

    tmp_context = malloc(sizeof(struct Dx_Client_Tz_Context_s));
    if(tmp_context == NULL){
        TEEC_Error("%s : malloc fail\n", __func__);
        return DX_TZ_NO_MEMORY;
    }
    TEEC_Debug("app uuid1 = 0x%x, uuid2 = 0x%x, uuid3 = 0x%x\n", appId->uuid.a, appId->uuid.b, appId->uuid.c);

    memcpy(&tmp_context->id, appId, sizeof(Dx_TzAppId));

    if(TEEC_InitializeContext(NULL, &tmp_context->context) != TEEC_SUCCESS){
        TEEC_Error("%s : TEEC_InitializeContext error\n", __func__);
        return DX_TZ_FAILURE;
    }

    *context = tmp_context;
    gContext = tmp_context;

    reg_signal_handler();

    return DX_TZ_SUCCESS;
}


void DxTzClient_DestroyContext(Dx_Client_Tz_Context context)
{
    TEEC_FinalizeContext(&context->context);
    free(context);
    unreg_signal_handler();
    gContext=NULL;
}

/**
* Open client session (that means communication channel to the trust zone).
*
* @param [in] context points previously allocated and initialized instance of Dx_Client_Tz_Context structure.
*	The Dx_Client_Tz_Context is platform-independent opaque type of structure,
*	whose complete type is defined in the platform-dependent code.
*
* @param [out] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*	Will be used to call DxTzClient_InvokeCommand.
*	The Dx_Client_Tz_Session is platform-independent opaque type of structure,
*	whose complete type is defined in the platform-dependent code.
*	Its instance is allocated in this function.
*
* @param [in,out] operation points additional data used to create a session.
*	The Dx_Client_Tz_Operation is platform-independent structure type, defined in the DxTzCommon.h.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return platform-specified value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_OpenSession (
    Dx_Client_Tz_Context    context,
    Dx_Client_Tz_Session*    session,
    Dx_Client_Tz_Operation*  operation)
{
    Dx_Client_Tz_Session tmp_session;
    TEEC_Result ret;
    TEEC_Operation tee_operation = {0};

    tmp_session = malloc(sizeof(struct Dx_Client_Tz_Session_s));
    if(tmp_session == NULL){
        TEEC_Error("%s : malloc fail\n", __func__);
        return DX_TZ_NO_MEMORY;
    }

    DxOperation2TEEOperation(operation, &tee_operation);

    TEEC_Debug("operation->paramTypes = 0x%x\n", operation->paramTypes);
    TEEC_Debug("%s : app uuid1 = 0x%x, uuid2 = 0x%x, uuid3 = 0x%x\n", __func__,
                context->id.uuid.a, context->id.uuid.b, context->id.uuid.c);

    ret = TEEC_OpenSession(&context->context,
                           &tmp_session->session,
                           &context->id.uuid,
                           TEEC_LOGIN_PUBLIC,
                           NULL,
                           &tee_operation,
                           NULL);
    if(ret != TEEC_SUCCESS){
        TEEC_Error("%s : TEEC_OpenSession error\n", __func__);
        return DX_TZ_FAILURE;
    }

    *session = tmp_session;

    if (add_to_list((void*)*session) == NULL)
    {
    	TEEC_Error("%s :fail to add session to the link list", __func__);
    	DxTzClient_CloseSession (*session);
    }

    TEEOperation2DxOperation(&tee_operation, operation);
//    DxTzClient_HDMI_Init((void *)tmp_session);
    return DX_TZ_SUCCESS;
}


/**
* Close previously open client session.
*
* @param [in] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*	The Dx_Client_Tz_Session is platform-independent opaque type of structure,
*	whose complete type is defined in the platform-dependent code.
*	Its instance is deallocated in this function.
*
*/
void DxTzClient_CloseSession (
    Dx_Client_Tz_Session session)
{
    TEEC_CloseSession(&session->session);

    if (delete_from_list((void*)session) != 0)
    {
       	TEEC_Error("%s :fail to remove session from the link list", __func__);
    }

    free(session);

    return DX_TZ_SUCCESS;
}


/**
* Execute the specified command on the trust zone.
*
* @param [in] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*
* @param [in] commandID: Unique ID agreed between the client and the service defining each operation.
* The command ID used in an application must not use a values between 0x0 and 0x01000,
* as they are reserved for internal TZ implementation.
*
* @param [in,out] operation: parameters passed from the client and values returned from the service.
* The Dx_Client_Tz_Operation is platform-depended structure type, defined in the DxTzPlatClientAPI.h.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return platform-specified value other than DX_SUCCESS if operation failed.
*/
DxStatus	 DxTzClient_InvokeCommand(
    Dx_Client_Tz_Session   session,
    DxUint32				commandID,
    Dx_Client_Tz_Operation* operation)
{
    TEEC_Result ret;
    TEEC_Operation tee_operation = {0};
    int i=0;

    DxOperation2TEEOperation(operation, &tee_operation);

//    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s : calling TEEC_InvokeCommand with command id %x\n", __func__,commandID);
    TEEC_Debug("DxTzClient_InvokeCommand, commandID:0x%x\n", commandID);
    for ( i=0; i<4; i++)
    {
    	switch(DX_TZ_PARAM_TYPE_GET(operation->paramTypes,i))
		{
			case DX_TZ_PARAM_TYPE_MEMREF_INPUT:
			case DX_TZ_PARAM_TYPE_MEMREF_INOUT:
			case DX_TZ_PARAM_TYPE_MEMREF_OUTPUT:
			case DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT:
		//		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "TEEC_InvokeCommand parameter %d buffer %x size %d\n",i, operation->params[i].memRef.buffer, operation->params[i].memRef.size);
				break;
			case DX_TZ_PARAM_TYPE_NONE://no parameter here,just verify 0
			case DX_TZ_PARAM_TYPE_VALUE_OUTPUT://not handled in building command request
			case DX_TZ_PARAM_TYPE_VALUE_INPUT:
			case DX_TZ_PARAM_TYPE_VALUE_INOUT:
				break;
		}
    }


    ret = TEEC_InvokeCommand(&session->session, commandID, &tee_operation, NULL);
    if(ret != TEEC_SUCCESS){
        TEEC_Error("TEEC_InvokeCommand error %x\n", ret);
//        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s : TEEC_InvokeCommand error %x\n ", __func__,ret);
        return ret;
    }

//    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s : TEEC_InvokeCommand success\n", __func__);

    TEEOperation2DxOperation(&tee_operation, operation);

    return DX_TZ_SUCCESS;
}


/**
* Set the root directory for provisioning and secure data storage on the trust zone.
*
* @param [in] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*
* @param [in] sfsPath is null-terminated string, which contains a path
*		to be used as root directory for provisioning and secure data storage in the specified session.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return platform-specified value other than DX_SUCCESS if operation failed.
*/
DxStatus	 DxTzClient_SetSfsPath(
	Dx_Client_Tz_Session   session,
	const DxChar *sfsPath)
{
    return DX_TZ_SUCCESS;
}

/**
* This is required to be called just before first play of secure buffer.
*
* @param [in] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return platform-specified value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_InitSecureContentPath(Dx_Client_Tz_Session pSession)
{
    return DX_TZ_SUCCESS;
}


/**
* This is required to be called after finishing last play of secure buffer.
*
* @param [in] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return platform-specified value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_TerminateSecureContentPath(Dx_Client_Tz_Session pSession)
{
    return DX_TZ_SUCCESS;
}

/**
* Answer maximal size of the physical memory that can be allocated.
*
* @param [in] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*
* @return the maximal possible size.
*/
DxUint32 DxTzClient_MaxPhysicalMemoryChunk(Dx_Client_Tz_Session pSession)
{
    return MAX_PHY_MEM_SIZE;
}

/**
* Bit values used in allocationFlags parameter of the DxTzClient_ShaaredmemAlloc.
*
* DX_ALLOC_PHYS_ADDR_REQUIRED
*	(0/1)to be used on platforms, required physical address of memory buffer for TEE operations.
* (0/1)DX_ALLOC_TZ_VIRT_ADDR_REQUIRED
*	to be used on platforms, required virtual address of memory buffer related to the specified TEE context.
* (0/1)DX_ALLOC_SECURE
*	if the specified bit is set, allocate secure memory buffer, which can't be mapped in HLOS.
*
*/
#define DX_ALLOC_PHYS_ADDR_REQUIRED			0x01
#define DX_ALLOC_TZ_VIRT_ADDR_REQUIRED		0x02
#define DX_ALLOC_SECURE						0x04

/**
* Allocate shared memory buffer.
*
* @param [in] context points previously allocated and initialized instance of Dx_Client_Tz_Context structure.
* @param [in,out] memHandler: points a pointer to platform-dependent handle to keep full information about allocated data.
*     To be filled in this function.
* @param [in] size: Required allocated memory size in bytes.
* @param [in] allocationFlags: set of bit flags :
* DX_ALLOC_PHYS_ADDR_REQUIRED       - physical memory should be allocated
* DX_ALLOC_TZ_VIRT_ADDR_REQUIRED    - TZ virtual memory should be allocated
* DX_ALLOC_SECURE                   - secured memory should be allocated
* *** Note : OR-ed combination of flag is possible.
* ***        Not all combinations are supported on all platforms.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return a value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_SharedMemAlloc(Dx_Client_Tz_Context context, Dx_Client_Tz_MemHandler *memHandler, DxUint32 size, DxUint32 allocationFlags)
{
    TEEC_Result ret;
    Dx_Client_Tz_MemHandler tmp_handle;

    tmp_handle = malloc(sizeof(struct Dx_Client_Tz_MemHandler_s));
    if(tmp_handle == NULL){
        TEEC_Error("%s : malloc fail\n", __func__);
        return DX_TZ_NO_MEMORY;
    }

    tmp_handle->mem.size = size;
    tmp_handle->mem.flags = allocationFlags;

    ret = TEEC_AllocateSharedMemory(&context->context, &tmp_handle->mem);
    if(ret != TEEC_SUCCESS){
        TEEC_Error("%s : TEEC_AllocateSharedMemory error\n", __func__);
        return DX_TZ_FAILURE;
    }
    *memHandler = tmp_handle;

    return DX_TZ_SUCCESS;
}


/**
* Free shared memory buffer, previously allocated with the DxTzClient_SharedMemAlloc().
*
* @param [in] context points previously allocated and initialized instance of Dx_Client_Tz_Context structure.
* @param [in] memHandler: points a platform-dependent handle to keep full information about allocated data
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return a value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_SharedMemFree(Dx_Client_Tz_Context context, Dx_Client_Tz_MemHandler memHandler)
{
    TEEC_ReleaseSharedMemory(&memHandler->mem);
    free(memHandler);

    return DX_TZ_SUCCESS;
}


/**
* Get allocation flags used by DxTzClient_SharedMemAlloc() function.
*
* @param [in] memHandler: Handler to opaque structure, which holds all the necessary mapping data (allocated through DxTzClient_SharedMemAlloc() call)
* @param [out] *pAllocationFlags: allocation flags used by DxTzClient_SharedMemAlloc()
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return a value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_SharedMemGetFlags(Dx_Client_Tz_MemHandler memHandler, DxUint32 *pAllocationFlags)
{
    *pAllocationFlags = memHandler->mem.flags;

    return DX_TZ_SUCCESS;
}

/**
* Map user space pointer onto shared memory buffer.
*
* @param [in] memHandler: Handler to opaque structure, which holds all the necessary mapping data (allocated through DxTzClient_SharedMemAlloc() call)
* @param [out] virtualMemBuffer: Address, which will hold a pointer to a shared memory buffer (allocated through DxTzClient_SharedMemAlloc() call)
*   using information, provided with memHandler.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return a value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_SharedMemMap(Dx_Client_Tz_MemHandler memHandler, DxByte **virtualMemBuffer)
{
    *virtualMemBuffer = memHandler->mem.buffer;

    return DX_TZ_SUCCESS;
}


/**
* Unmap virtual memory buffer previously mapped with the DxTzClient_SharedMemMap().
*
* @param [in] memHandler: points a platform-dependent handle to keep full information about allocated data
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return a value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_SharedMemUnmap(Dx_Client_Tz_MemHandler memHandler)
{
    return DX_TZ_SUCCESS;
}


/* This is special value for bufferSize parameter in function DxTzClient_ConvertToSharedMemRef.
	When function gets this value instead of bufferSize, it will set buffer size to maximal possible value*/
#define BUFFER_SIZE_MAX_AVAILABLE 0xFFFFFFFF

/**
* Prior to sending shared memory buffer through DxTzClient_InvokeCommand, transform it into appropriate structure.
* This function converts allocation metadata structire (Dx_Client_Tz_MemHandler) to structure which can be sent
* to TZ (Dx_Client_Tz_SharedMemRef).
*
* @param [out] destSharedMemRefPtr: points structure, whose fields are to be assigned
*   using information, provided with memHandler.
*
* @param [in] bufferOffset: offset from which buffer starts
*
* @param [in] bufferSize: desired buffer size of destination buffer. This size should be smaller or equal to
* 						  maximal available memory size.
*   *** Note : pass BUFFER_SIZE_MAX_AVAILABLE to set destination buffer size to maximal available memory size.
*
* @param [in] srcMemHandler: points a platform-dependent handle to keep full information about allocated data
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return a value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_ConvertToSharedMemRef(Dx_Client_Tz_SharedMemRef *destSharedMemRefPtr, DxUint32 bufferOffset, DxUint32 bufferSize, Dx_Client_Tz_MemHandler srcMemHandler)
{
    if(bufferSize != BUFFER_SIZE_MAX_AVAILABLE){
        /* user gave preferred size : validate that bufferSize does not overflow maximal available size */
        if(srcMemHandler->mem.size - bufferOffset < bufferSize){
            return DX_TZ_BAD_PARAMETERS;
        }

        destSharedMemRefPtr->size = bufferSize;
	}else{
        /* user did not give preferred size : set size to maximal available size */
        destSharedMemRefPtr->size = srcMemHandler->mem.size - bufferOffset;
    }

    destSharedMemRefPtr->handle1 = srcMemHandler->mem.buffer;
    destSharedMemRefPtr->handle2 = NULL;
    destSharedMemRefPtr->offset = bufferOffset;
    //destSharedMemRefPtr->size = bufferSize;

    return DX_TZ_SUCCESS;
}

#if 0
static HI_UNF_HDMI_CALLBACK_FUNC_S g_stCallbackFunc;
DxStatus DxTzClient_SetHDMIStatus(Dx_Client_Tz_Session pSession, DxUint32 u32HdmiStatus)
{
        DxStatus result;
        Dx_Client_Tz_Operation operation;
        operation.paramTypes = DX_TZ_PARAM_TYPES(DX_TZ_PARAM_TYPE_VALUE_INPUT, DX_TZ_PARAM_TYPE_NONE, DX_TZ_PARAM_TYPE_NONE, DX_TZ_PARAM_TYPE_NONE);
        operation.params[0].value.a = u32HdmiStatus;
        operation.params[0].value.b = TEEC_VALUE_UNDEF;
        result = DxTzClient_InvokeCommand(pSession, CMD_TZ_HDCP_SETHDMISTATUS, &operation);
        if (result != DX_SUCCESS)
        {
            TEEC_Error("%s : failed, result:0x%08x\n", __func__, (DxUint)result);
            return(result);
        }
        return(result);
}
DxStatus DxTzClient_HDMI_EventProcess(HI_UNF_HDMI_EVENT_TYPE_E event, void *pPrivateData)
{
    DxUint32   enHdmiStatus = 0xFFFFFFFF;
    switch(event)
    {
    case HI_UNF_HDMI_EVENT_HOTPLUG:
        printf("HI_UNF_HDMI_EVENT_HOTPLUG\n");
        enHdmiStatus = DX_TZ_HDMI_HDCP1_HDCP1_NOT_AUTH;
        break;
    case HI_UNF_HDMI_EVENT_NO_PLUG:
        printf("HI_UNF_HDMI_EVENT_NO_PLUG\n");
        enHdmiStatus = DX_TZ_HDMI_HDCP1_HDCP1_DISABLED_OR_NOT_CONNECTED;
        break;
    case HI_UNF_HDMI_EVENT_EDID_FAIL:
        printf("HI_UNF_HDMI_EVENT_EDID_FAIL\n");
        break;
    case HI_UNF_HDMI_EVENT_HDCP_FAIL:
        printf("HI_UNF_HDMI_EVENT_HDCP_FAIL\n");
        enHdmiStatus = DX_TZ_HDMI_HDCP1_HDCP1_FAILURE;
        break;
    case HI_UNF_HDMI_EVENT_HDCP_SUCCESS:
        printf("HI_UNF_HDMI_EVENT_HDCP_SUCCESS\n");
        enHdmiStatus = DX_TZ_HDMI_HDCP1_HDCP1_AUTHENTICATED;
        break;
    case HI_UNF_HDMI_EVENT_RSEN_CONNECT:
        printf("HI_UNF_HDMI_EVENT_RSEN_CONNECT\n");
        break;
    case HI_UNF_HDMI_EVENT_RSEN_DISCONNECT:
        printf("HI_UNF_HDMI_EVENT_RSEN_DISCONNECT\n");
        break;
    default:
        printf("Unknown Event\n");
        enHdmiStatus = DX_TZ_HDMI_HDCP1_STATUS_UNKNOWN;
        break;
    } 
    if(enHdmiStatus != 0xFFFFFFFF)
    {
        return DxTzClient_SetHDMIStatus((Dx_Client_Tz_Session) pPrivateData, enHdmiStatus);
    }
    return DX_SUCCESS;
}

DxInt32 DxTzClient_HDMI_Init(void * psession)
{
    DxInt32 Ret;
    HI_UNF_HDMI_OPEN_PARA_S stOpenParam;
    printf("DxTzClient_HDMI_Init START\n");
    Ret = HI_UNF_HDMI_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("HI_UNF_HDMI_Init failed:%#x\n", (unsigned int)Ret);
        return DX_FAILURE;
    }
    g_stCallbackFunc.pfnHdmiEventCallback = DxTzClient_HDMI_EventProcess;
    g_stCallbackFunc.pPrivateData = psession;
    Ret = HI_UNF_HDMI_RegCallbackFunc(HI_UNF_HDMI_ID_0, &g_stCallbackFunc);
    if (Ret != HI_SUCCESS)
    {
        printf("hdmi reg failed:%#x\n", (unsigned int)Ret);
        HI_UNF_HDMI_DeInit();
        return DX_FAILURE;
    }
    stOpenParam.enDefaultMode = HI_UNF_HDMI_DEFAULT_ACTION_HDMI;
    Ret = HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_0, &stOpenParam);
    if (Ret != HI_SUCCESS)
    {
        printf("HI_UNF_HDMI_Open failed:%#x\n", (unsigned int)Ret);
        HI_UNF_HDMI_DeInit();
        return DX_FAILURE;
    }
    printf("DxTzClient_HDMI_Init SUCCESS\n");
    return DX_SUCCESS;
}
void DxTzClient_HDMI_DeInit(void)
{
    printf("DxTzClient_HDMI_DeInit START\n");
    HI_UNF_HDMI_Stop(HI_UNF_HDMI_ID_0);
    HI_UNF_HDMI_Close(HI_UNF_HDMI_ID_0);
    HI_UNF_HDMI_UnRegCallbackFunc(HI_UNF_HDMI_ID_0, &g_stCallbackFunc);
    HI_UNF_HDMI_DeInit(); 
    printf("DxTzClient_HDMI_DeInit END\n");
}
#endif
#ifdef __cplusplus
}
#endif
