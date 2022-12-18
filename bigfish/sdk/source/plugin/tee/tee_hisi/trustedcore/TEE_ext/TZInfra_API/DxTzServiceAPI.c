#include "DxTzServiceAPI.h"
#include "tee_internal_api.h"
//#define TA_DEBUG
#include "tee_log.h"
#include "tee_fs.h"
#include "DxTzServiceSfs.h"

//switch of SFS define
#define SFS
//swith of crypto file
#define SECURE_STORAGE

HSFS g_hsfs = NULL;
bool sfs_init_flag = false;
#define SFS_SIZE (32*1024)

DxStatus sfs_init(void)
{
    void* sfs_buf;
    if (sfs_init_flag == false)
    {
        sfs_buf = DxTzService_Malloc(SFS_SIZE);
        if(sfs_buf == DX_NULL)
            return DX_MEM_ALLOCATION_ERROR;
        if(DxSfsInitialize(&g_hsfs, sfs_buf, SFS_SIZE) != DX_SUCCESS){
            ta_error("DxSfsInitialize failed\n");
            return DX_NOT_INITIALIZED;
        }
        sfs_init_flag= true;
    }
    return DX_SUCCESS;
}

HSFS get_current_sfs(void)
{
    return g_hsfs;
}

void DxTzService_SetGlobalInstance(void *instance)
{
    TEE_SetInstanceData(instance);
}

/**
 * Get an internal global instance assigned in TZ application.
 *	Global instance behaves like a regular pointer, which can be used for any purpose in TZ application code.
 *	The global instance is accessible for all sessions opened on the context.
 *
 * @return pointer to the previously assigned instance.
 */
void *DxTzService_GetGlobalInstance(void)
{
    return TEE_GetInstanceData();
}

/**
 * Reads data from secure storage.
 *
 * @param[in] fileName		-	input file name.
 * @param[out] aBuf			-	output buffer.
 * @param[in,out] anInOutLen-	[in]  address of a variable containing the output buffer size(size of aBuf in bytes).
 *								[out] address of a variable contain number fo bytes actually read from file.
 *
 * @return DX_SUCCESS on success, DX_ITEM_NOT_FOUND if the file is not exist, else non ZERO error.
 */
DxStatus DxTzService_ReadFromSecureStorage(const DxChar* fileName, DxUint8* aBuf, DxUint32 *anInOutLen)
{
    int32_t fd;
    uint32_t count;
    int32_t error;

    if(fileName == NULL || aBuf == NULL || anInOutLen == NULL)
        return DX_BAD_ARGUMENTS;

    if(*anInOutLen == 0)
        return DX_BAD_ARGUMENTS;

#ifdef SFS
    return DxSfsRead(get_current_sfs(), fileName, 0, aBuf, anInOutLen);
#else
#ifdef SECURE_STORAGE
    fd = s_fopen(fileName, TEE_DATA_FLAG_ACCESS_READ);
#else
    fd = fopen(fileName, TEE_DATA_FLAG_ACCESS_READ);
#endif
    if(fd  < 0){
        ta_error("fopen file %s failed\n", fileName);
        return DX_TZ_ITEM_NOT_FOUND;
    }

#ifdef SECURE_STORAGE
    count = s_fread(aBuf, *anInOutLen, fd, &error);
#else
    count = fread(aBuf, *anInOutLen, fd, &error);
#endif

    if(count != *anInOutLen && error == -1){
        ta_error("fread file error : read/len = %d/%d\n", count, *anInOutLen);
        *anInOutLen = count;
        return DX_TZ_FAILURE;
    }
    *anInOutLen = count;

    return DX_SUCCESS;
#endif
}

/**
 * Writes data in secure storage.
 *
 * @param[in] fileName - output file name.
 * @param[in] aBuf - input buffer.
 *   if aBuf is DX_NULL, just delete the specified file without over-writing.
 * @param[in] aLen - size of data to write.
 *
 * @return DX_SUCCESS on success, else non ZERO error.
 * @return DX_ITEM_NOT_FOUND in case the file does not exist on the specified path.
 */
DxStatus DxTzService_WriteToSecureStorage(const DxChar* aFileName, const DxUint8 *aBuf, DxUint32 aLen)
{
    int32_t fd;
    uint32_t count;
    DxStatus ret;

#ifdef SFS
    if(aBuf == NULL)
        return DxSfsDelete(get_current_sfs(), aFileName);

    if(aLen == 0)
        return DX_BAD_ARGUMENTS;

    return DxSfsWrite(get_current_sfs(), aFileName, aBuf, 0, aLen);
#else
    if(aBuf == NULL){
#ifdef SECURE_STORAGE
        if(s_fremove(aFileName) != 0){
#else
        if(fremove(aFileName) != 0){
#endif
            ta_error("fremove file %s failed\n", aFileName);
            return DX_TZ_FAILURE;
        }
        return DX_SUCCESS;
    }

    if(aLen == 0)
        return DX_BAD_ARGUMENTS;

#ifdef SECURE_STORAGE
    fd = s_fcreate(aFileName, TEE_DATA_FLAG_ACCESS_WRITE);
#else
    fd = fcreate(aFileName, TEE_DATA_FLAG_ACCESS_WRITE);
#endif

    if(fd  < 0){
        ta_error("fcreate file %s failed\n", aFileName);
        return DX_TZ_FAILURE;
    }

#ifdef SECURE_STORAGE
    count = s_fwrite(aBuf, aLen, fd, aFileName);
#else
    count = fwrite(aBuf, aLen, fd);
#endif

    if(count != aLen){
        ta_error("fwrite error : write/count = %d/%d\n", count, aLen);
        return DX_TZ_FAILURE;
    }

    return DX_SUCCESS;
#endif
}

/**
 * Get secure stroage file size.
 *
 * @param[in] fileName - secure storage file name.
 * @param[out] aLen - size of file.
 *
 * @return DX_SUCCESS on success, else non ZERO error.
 * @return DX_ITEM_NOT_FOUND in case the file does not exist on the specified path.
 */
DxStatus DxTzService_GetSecureStorageFileSize(const DxChar* aFileName, DxUint32 *aLen)
{
    int32_t fd;

    if(aFileName == NULL || aLen == NULL)
        return DX_BAD_ARGUMENTS;

#ifdef SFS
    return DxSfsGetSize (get_current_sfs(), aFileName, aLen);
#else
#ifdef SECURE_STORAGE
    fd = s_fopen(aFileName, TEE_DATA_FLAG_ACCESS_READ);
#else
    fd = fopen(aFileName, TEE_DATA_FLAG_ACCESS_READ);
#endif
    if(fd  < 0){
        ta_error("fopen file %s failed\n", aFileName);
        return DX_ITEM_NOT_FOUND;
    }

#ifdef SECURE_STORAGE
    if(s_finfo(fd, NULL, aLen) == -1){
#else
    if(finfo(fd, NULL, aLen) == -1){
#endif
        ta_error("finfo file %s failed\n", aFileName);
        return DX_TZ_FAILURE;
    }

    return DX_SUCCESS;
#endif
}

/**
 * Allocates buffer in heap with specified size.
 * Minimum and maximum size of the allocation is platform-dependent.
 * It's required that the heap and the allocation in the heap exist from SRVX_Create_impl() call
 * till SRVXDestroy_impl() call.
 *
 * @param [in] size specifies the number of bytes in the allocated buffer.
 *
 * @return address of allocated buffer or DX_NULL if allocation failed..
 */
void *DxTzService_Malloc(DxUint32 size)
{
    return TEE_Malloc(size, 0);
}

/**
 * Reallocates buffer with specified new size.
 * The content of the old buffer is moved to the new location.
 *
 * @param [in] size specifies the number of bytes in the re-allocated buffer.
 *
 * @return address of re-allocated buffer or DX_NULL if allocation failed..
 */
void *DxTzService_Realloc(void* ptr,DxUint32 newSize)
{
    return TEE_Realloc(ptr, newSize);
}

/**
 * Releases allocated memory.
 * If ptr is NULL function does nothing.
 *
 * @param [in] ptr points to the previously allocated buffer.
 */
void DxTzService_Free(void* ptr)
{
    return TEE_Free(ptr);
}


/**
 * Copies buffer source to target.
 *
 * @param [in,out] pDest points the target.
 * @param [in] pSrc points the source.
 * @param [in] nBytes specifies number of copied bytes.
 *
 * @return target pointer.
 */
void *DxTzService_MemCpy(void *pDest, const void *pSrc, DxUint32 nBytes)
{
    TEE_MemMove(pDest, pSrc, nBytes);

    return pDest;
}

/**
 * Copies buffer source to target in reversed order.
 *
 * @param [in,out] pDest points the target.
 * @param [in] pSrc points the source.
 * @param [in] nBytes specifies number of copied bytes.
 *
 * @return target pointer.
 */
void *DxTzService_MemCpyReverse(void *pDest, const void *pSrc, DxUint32 nBytes)
{
    unsigned char *p1;
    const unsigned char *p2;

    if(pDest == NULL || pSrc == NULL)
        return NULL;

    p1 = (unsigned char*)pDest;
    p2 = (const unsigned char*)pSrc;

    while(nBytes > 0) {
        *p1++ = *(p2+nBytes-1);
        nBytes --;
    }

    return pDest;
}

/**
 * Set the specified amount of bytes in the target by the specified value.
 *
 * @param [in,out] pDest points the target.
 * @param [in] c  is the assigned value.
 * @param [in] nBytes specifies number of assigned bytes.
 *
 * @return target pointer.
 */
void *DxTzService_MemSet(void *pDest, DxChar c, DxUint32 nBytes)
{
    TEE_MemFill(pDest, c, nBytes);

    return pDest;
}

/**
 * Compares buffers (source buffer with target buffer).
 *
 * @param [in] ptr1 points the first buffer.
 * @param [in] ptr2 points the second.
 * @param [in] nBytes specifies number of compared bytes.
 *
 * @return
 *  0 - if buffers are identical.
 * <0 - if first buffer is smaller then second buffer
 * >0 - if second buffer is smaller then first buffer
 */
DxInt DxTzService_MemCmp(const void *ptr1, const void * ptr2, DxUint32 nBytes)
{
    return TEE_MemCompare(ptr1, ptr2, nBytes);
}

/**
 * Provides unique device key values.
 * Implementation note:
 * - must provide with identical result for identical id and the same key length.
 * - if the key was created and then removed, and then created again, the next value may be different.
 *
 * @param [in] id - Key id
 * @param [out] buff - points the output buffer.
 *	The allocated buffer must be big enough to include the required key length.
 * @param [in] length - the required key length.
 *
 * @return DX_SUCCESS on success, else non ZERO error.
 */
DxStatus DxTzService_GetDeviceKey(DxUint32 id, DxUint8 *buff, DxUint32 length)
{
    return DX_TZ_FAILURE;
}

/**
 * Provides with unique id of device.
 *
 * @param [out] pDevUniqueID - buffer to be filled with unique id
 * @param [in,out] length	 - in: points max buffer length; out: points required buffer size.
 *
 * @return DX_SUCCESS on success, else non ZERO error.
 */
DxStatus DxTzService_Get_Device_UniqueId(DxUint8* pDevUniqueID, DxUint32 *length)
{
    return DX_TZ_FAILURE;
}


/**
 * Provides the current timestamp.
 * The DxTzTimestamp_t is an integer type.
 * The API must be independent on any SetTime operations;
 * - must be monotonous counting since boot time;
 * - (desirable) counting during a power saving mode.
 *
 * @param[out] ts - pointer to timestamp
 * to be filled with the current timestamp.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
 * @return DX_TZ_NOT_IMPLEMENTED in a default implementation
 */
DxStatus DxTzService_GetTimestamp(DxTzTimestamp_t *ts)
{
    return DX_TZ_FAILURE;
}

/**
 * Provides duration in milliseconds since the specified timestamp.
 * Must support durations of up to 10 seconds.
 *
 * @param[in] ts - timestamp value
 * @param[out] duration_ms - pointer to integer
 * to be filled with the duration in milliseconds.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
 * @return DX_TZ_FAILUREURE in case if timestamp source was lost (e.g. timer was power-cycled).
 * @return DX_TZ_NOT_IMPLEMENTED in a default implementation
 */
DxStatus DxTzService_DurationSinceTimestamp(DxTzTimestamp_t ts, DxUint32 *duration_ms)
{
    return DX_TZ_FAILURE;
}

/**
 * Answers whether the current device is rooted.
 *
 * @return DX_TRUE  if device is rooted, or the state is unknown
 * @return DX_FALSE if device is not rooted,
 */
DxBool DxTzService_IsDeviceRooted(void)
{
    return DX_TZ_FAILURE;
}

/**
 * Answers whether the boot loader is unlocked.
 *
 * @return DX_TRUE  if the boot loader is unlocked,
 * @return DX_FALSE if it is locked,
 * @return DX_FALSE in a default implementation
*/
DxBool DxTzService_IsBootLoaderUnlocked(void)
{
    return DX_TZ_FAILURE;
}

/**
 * Answers HDMI/HDCP connection status by checking for HDCP compliance if the HDMI port is active.
 *
 @return DX_TZ_HDMI_HDCP1_HDCP1_AUTHENTICATED				 HDMI with HDCP1 authenticated
 @return DX_TZ_HDMI_HDCP1_HDCP1_DISABLED_OR_NOT_CONNECTED,	 HDMI disabled or not connected
 @return DX_TZ_HDMI_HDCP1_HDCP1_NOT_AUTH,					 HDMI cable connected, but HDCP1 is not authenticated
 @return DX_TZ_HDMI_HDCP1_HDCP1_FAILURE,					 HDMI cable IS NOT connected, but HDCP1 IS authenticated (seems like hack case)
 @return DX_TZ_HDMI_HDCP1_STATUS_UNKNOWN,					 in case of status function failure
 @return DX_TZ_HDMI_HDCP1_NOT_SUPPORTED,					 Not supported (platform does not support HDMI/HDCP1 status reading)
 */
EDxTz_HDMI_HDCP1_Status_t DxTzService_Get_HDMI_HDCP1_Status(void)
{
    return DX_TZ_FAILURE;
}


/**
* Answers HDCP 2 connection status.
*
* @return DX_TZ_CONNECTION_CONNECTED  if there is HDCP 2 connected,
* @return DX_TZ_CONNECTION_NOT_CONNECTED if there is no HDCP 2 connected,
* @return DX_TZ_CONNECTION_STATUS_UNKNOWN if cannot retrieve the required data,
* @return DX_TZ_CONNECTION_STATUS_UNSUPPORTED in a default implementation
 */
EDxTzConnectionStatus_t DxTzService_GetHDCP2ConnectionStatus(void)
{
    return DX_TZ_FAILURE;
}


/**
 * Set/unset HDCP 2 connection.
 *
 * @param[in] connected specify whether set/unset.
 * (DX_TRUE to connect on, DX_FALSE off).
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
 * @return DX_TZ_NOT_IMPLEMENTED in a default implementation
 */
DxStatus DxTzService_SetHDCP2ConnectionStatus(DxBool connected)
{
    return DX_TZ_FAILURE;
}


/**
 * 1. When HDMI cable is connected by the user, the HDCP1 authentication process starts automatically.
 * 2. The HDCP1 authentication process takes some time (depends on the platform capabilities).
 * 3. In order to prevent a situation when end user will wait till HDCP1 authentication process will finish
      we decided to allow contennt decryption for limited time.
 * 3. During this time, the TZ application should be able to decrypt protected content even if HDCP1
      authentication process is not yet finished.
 * 4. In order to limit this time period we will provide a limited number of video frames that the TZ application
      will be allowed to decrypt.
 * 5. We cannot use time based solution because not all platforms has timers in TZ.
 * 6. To verify HDMI/HDCP1 status, TZ application should use DxTzService_Get_HDMI_HDCP1_Status() API.
 * 7. If HDCP1 authentication process will not be complited wihin certain number of video frames decryption,
 *    The TZ application shoould fail the next call to decrypt API.
 *
 * @return Number of video frames that should be decrypted after HDMI cable is connected and before HDCP1
 * authentication process will be complited.
 */
DxUint32 DxTzService_HDCP1RelaxationCycles(void)
{
    return DX_TZ_FAILURE;
}

#define DxTzService_numberOfExtraDecryptionsUntilHDCPConnectedTestWorks DxTzService_HDCP1RelaxationCycles

/**
 * Activate SCP.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
 * @return DX_SUCCESS in a default implementation
 */
DxStatus DxTzService_InitSecureContentPath(void)
{
    return DX_TZ_FAILURE;
}

/**
 * De-activate SCP.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
 * @return DX_SUCCESS in a default implementation
 */
DxStatus DxTzService_TerminateSecureContentPath(void)
{
    return DX_TZ_FAILURE;
}

/**
 * Get TZ service application name.
 * An implementation of this API and the point of its call is fully platform dependent.
 *
 * @param[in,out] buffSize - points a variable, containing the available buffer size in bytes.
 *		Input: pointer to the variable, containing the avilable buffer size in bytes;
 *		Output: number of bytes actually written to the buffer, including termination zero.
 *
 * @return DX_SUCCESS if operation has been successfully completed.
 *		DX_BUFFER_IS_NOT_BIG_ENOUGH if the buffer size is not big enough to contain the provisioning path.
 *			in this case the *buffSize will contain the required minimal buffer size;
 *		DX_NOT_AVAILABLE if not available for specific platform;
 *		any other value indicates another failure.
 */
DxStatus DxTzService_GetAppName(DxChar *buffer, DxUint32 *buffSize)
{
}

/**
 * Get TZ service sfs root path name.
 * This function should answer the path name, which was set in DxTzClient_SetSfsPath() API.
 * If this API was never called, the function should answer a platform-dependent default path name.
 *
 *
 * @param[in,out] buffSize - points a variable, containing the available buffer size in bytes.
 *		Input: pointer to the variable, containing the avilable buffer size in bytes;
 *		Output: number of bytes actually written to the buffer, including termination zero.
 *
 * @return DX_SUCCESS if operation has been successfully completed.
 *		DX_BUFFER_IS_NOT_BIG_ENOUGH if the buffer size is not big enough to contain the provisioning path.
 *			in this case the *buffSize will contain the required minimal buffer size;
 *		DX_NOT_AVAILABLE if not available for specific platform;
 *		any other value indicates another failure.
 */
DxStatus DxTzService_GetSfsRootPath(DxChar *buffer, DxUint32 *buffSize)
{
}

/**
 * Converts regular memory pointer into shared memory parameter type.
 *
 * @param[out] pDest - points an instance of the shared memory parameter, which should be filled with the result.
 *
 * @param[in] bufferOffset - offset(in bytes) of start of available memory region in memory buffer pointed by <mem>
 *
 * @param[in] mem 	- points the regular memory buffer
 *
 * @param[in] size 	- size of the memory buffer in bytes from offset in memory buffer
 * 				      Note : <size> of destination shared memory parameter type logically starts <bufferOffset> bytes
 *                              from address <mem>. Region [0... bufferOffset-1] is not avaliable for user.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
 */
DxStatus DxTzService_ConvertToSharedMemRef(DxTzServiceSharedMemRef *pDest, DxUint32 bufferOffset, DxByte *mem, DxUint32 size)
{
    pDest->handle1 = mem;
    pDest->handle2 = NULL;
    pDest->offset = bufferOffset;
    pDest->nSize = size - bufferOffset;

    return DX_SUCCESS;
}

/**
 * Copies number of bytes from the "pSrc" shared memory buffer(s) into "pDest".
 *
 * @param[in] pDest - presents the destination memory buffer(s)
 * @param[in] destOffset - offset from the start of the destination memory buffer in bytes
 * @param[in] pSrc - presents the source memory buffer(s)
 * @param[in] srcOffset - offset from the start of the source memory buffer in bytes
 * @param[in] nBytes - number of copied bytes
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
 */
DxStatus DxTzService_MemCpyEx(DxTzServiceSharedMemRef *pDest, DxUint32 destOffset, DxTzServiceSharedMemRef *pSrc, DxUint32 srcOffset, DxUint32 nBytes)
{
    DxUint32 size1, size2;

    size1 = (destOffset + nBytes) > pDest->nSize ?
                (pDest->nSize - destOffset) : nBytes;
    size2 = (srcOffset + nBytes) > pSrc->nSize ?
                (pSrc->nSize - srcOffset) : nBytes;

    TEE_MemMove((char*)(pDest->handle1) + pDest->offset + destOffset, (char*)(pSrc->handle1) + pSrc->offset + srcOffset, size1 > size2 ? size2 : size1);

    return DX_SUCCESS;
}

/**
 * Sets number of bytes in the specified shared memory buffer(s) with the specified value.
 *
 * @param[in] pDest - presents the destination memory buffer(s)
 * @param[in] destOffset - offset from the start of the destination memory buffer in bytes
 * @param[in] value - assigned value
 * @param[in] nBytes - number of set bytes
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
 */
DxStatus DxTzService_MemSetEx(DxTzServiceSharedMemRef *pDest, DxUint32 destOffset, DxByte value, DxUint32 nBytes)
{
    DxUint32 set_size;

    set_size = (destOffset + nBytes) > pDest->nSize ?
                    (pDest->nSize - destOffset) : nBytes;

    TEE_MemFill((char*)(pDest->handle1) + pDest->offset + destOffset, value, set_size);

    return DX_SUCCESS;
}

/**
 * Compares shared memory buffers (ptr1 buffer with ptr2 buffer).
 *
 * @param[in] ptr1 - presents the first memory buffer(s)
 * @param[in] ptr1Offset - offset from the start of the first memory buffer in bytes
 * @param[in] ptr2 - presents the second memory buffer(s)
 * @param[in] ptr2Offset - offset from the start of the second memory buffer in bytes
 * @param[in] nBytes - number of set bytes
 * @param[out] res - points integer variable to be filled with the result:
 *  0 - if buffers are identical.
 * <0 - if first buffer is smaller then second buffer
 * >0 - if second buffer is smaller then first buffer
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
*/
DxStatus DxTzService_MemCmpEx(DxTzServiceSharedMemRef *ptr1, DxUint32 ptr1Offset, DxTzServiceSharedMemRef *ptr2, DxUint32 ptr2Offset, DxUint32 nBytes, DxInt *res)
{
    int32_t ret;
    DxUint32 size1, size2;

    size1 = (ptr1Offset + nBytes) > ptr1->nSize ?
                (ptr1->nSize - ptr1Offset) : nBytes;
    size2 = (ptr2Offset + nBytes) > ptr2->nSize ?
                (ptr2->nSize - ptr2Offset) : nBytes;

    ret = TEE_MemCompare((char*)(ptr1->handle1) + ptr1->offset + ptr1Offset, (char*)(ptr2->handle1) + ptr2->offset + ptr2Offset, size1 > size2 ? size2 : size1);

    *res = ret;
    return DX_SUCCESS;
}

/**
 * Verifies that buffer is protected by TZ and not accessible by HLOS.
 *
 * @param[in] ptr   	- presents the tested shared memory buffer(s)
 * @param[in] dataOffset- offset of data from the start of the memory in bytes
 * @param[in] size 		- number of tested bytes
 * @param[out] res 		- points a boolean variable.
 *		Output: DX_TRUE if the specified memory is secure, DX_FALSE otherwise.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
 */
DxStatus DxTzService_IsSecureContentMemory(DxTzServiceSharedMemRef *ptr, DxUint32 dataOffset, DxUint32 size, DxBool *res)
{
    return DX_TZ_FAILURE;
}

/**
 * Verifies that the whole buffer is in a non-secured memory area
 *
 * @param[in]  ptr	  		- A pointer to the tested shared memory buffer
 * @param[in]  dataOffset 	- Offset from the start of ptr (in bytes)
 * @param[in]  size   		- Number of tested bytes
 * @param[out] res 	  		- A pointer to boolean. Output: DX_TRUE if the whole specified memory is non-secure. DX_FALSE otherwise
 *
 * @return DX_SUCCESS if operation has been successfully completed. Any other value indicates a failure
 */
DxStatus DxTzService_IsNonSecureContentMemory(DxTzServiceSharedMemRef *ptr, DxUint32 dataOffset, DxUint32 size, DxBool *res)
{
    return DX_TZ_FAILURE;
}


/**
 * Checks if a given buffer of plain (not encrypted) data is of Audio type
 *
 * @param[in]  pSharedMemRef	 - A pointer to SharedMemRef structure that holds inside the memory to be checked
 * @param[in]  uiDataOffset		 - Offset in bytes from start of buffer to the start of the memory to be checked
 * @param[in]  uiSize   	   	 - Size in bytes of memory to be checked
 * @param[in]  uiStreamType		 - The stream type
 * @param[in]  enCipherAlgorithm - Cipher algorithm (for example: AES128CBC / AES128CTR)
 * @param[in]  pIV_Nonce_Counter - 16 bytes buffer. For CBC cipher: Initialization Vector. For CTR cipher: Nonce and Counter concatenated
 * @param[out] pbResult		   	 - A pointer to boolean that will be set if operation completed successfully: DX_TRUE if the memory to be checked points to data of Audio type; DX_FALSE otherwise
 *
 * @return DX_SUCCESS if operation has been successfully completed. Any other value indicates a failure
 */
 DxStatus DxTzService_IsAudioPacket( DxTzServiceSharedMemRef *pSharedMemRef,
		 	 	 	 	 	 	 	 DxUint32 			      uiDataOffset,
                                     DxUint32 			      uiSize,
                                     DxUint32 			      uiStreamType,
                                     EDxTzCipherAlgorithm_t   enCipherAlgorithm,
                                     DxUint8 			  	  pIV_Nonce_Counter[IV_NONCE_COUNTER_LENGTH],
                                     DxBool 				 *pbResult
                                   )
{
    return DX_TZ_FAILURE;
}

/*!	Copies string from aSrc to aTarget (aSize - 1 characters at most).
\return
- DX_SUCCESS - all string was copied including the terminating NULL.
- DX_BAD_ARGUMENTS - if one or more of the arguments are NULL.
- DX_BUFFER_IS_NOT_BIG_ENOUGH - if not the whole string was copied.
	In this case only the characters that fit into the target buffer are copied.
\note The aTarget will always be NULL terminated on return.
**/
DxStatus DxTzService_StrNCopy(
	DxChar *aTarget,		/*!< [out]  Destination string*/
	DxUint aTargetSize,	/*!< [in]   aTarget buffer size*/
	const DxChar *aSource	/*!< [in]   Source string*/
	)
{
    unsigned char *p1;
    const unsigned char *p2;
    bool end_flag = 0;

    if(aTarget == NULL || aSource == NULL)
        return DX_TZ_BAD_PARAMETERS;

    p1 = (unsigned char*)aTarget;
    p2 = (const unsigned char*)aSource;

    while(aTargetSize-- > 0) {
        *p1++ = *p2++;
        if(*p2 == '\0'){
            end_flag = 1;
            break;
        }
    }

    if(end_flag == 0)
        return DX_TZ_BUFFER_IS_NOT_BIG_ENOUGH;

    return DX_SUCCESS;
}


/*!	Calculates the length of a string.
\return    Returns the number of characters in a string without counting the null termination character.
if string is longer then aMaxSize - 1, aMaxSize will be returned.
**/
DxUint DxTzService_StrNLen(
	const DxChar *aStr,		/*!< [in]  A pointer to an input string. if  NULL 0 will be returned. */
	DxUint aMaxSize		/*!< [in]  Max expected size of string */
	)
{
    uint32_t len = 0;

    while(*aStr++){
        len++;
        if(len == aMaxSize)
            break;
    }
    return len;
}

/*!	Compares strings (source with target)
\return *
- 0 - if strings are identical.
- -1 - if first string is smaller then second string
- 1 - if second string is smaller then second string
\note DX_NULL is considered to be the smallest string.
**/
DxInt DxTzService_StrNCmp(
	const DxChar* Str1,	/*!< [in] First string to compare */
	const DxChar* Str2,	/*!< [in] Second string to compare */
	DxUint aMaxSize	/*!< [in] Max number of characters to compare */
	)
{
    unsigned char *p1, *p2;
    int32_t val=0;

    if(Str1 == NULL && Str2 == NULL)
        return 0;
    else if(Str1 == NULL && Str2 != NULL)
        return -1;
    else if(Str1 != NULL && Str2 == NULL)
        return 1;
    else if(Str1 != NULL && Str2 != NULL){    //add this useless judge for pc-lint
        p1 = (unsigned char*)Str1;
        p2 = (unsigned char*)Str2;

        while(aMaxSize-- > 0)
        {
            val = (*p1++) - (*p2++);
            if(val)
                return (val>0 ? 1:-1);

            if(*p1 == '\0'){
                if(*p2 == '\0')
                    return 0;
                else return -1;
            }else if(*p2 == '\0'){
                return 1;
            }
        }
    }

    return 0;
}

/**
 * Moves chunk of memory taking care of all possible overlaps.
 *
 * @param [in] pDest    - destination pointer
 * @param [out] pSrc    - source pointer
 * @param [in] nBytes   - source size in bytes
 * @return pointer to destination
 * @note Platform dependent
 */
void *DxTzService_MemMove(void *pDest, const void *pSrc, DxUint32 nBytes)
{
    TEE_MemMove(pDest, pSrc, nBytes);

    return pDest;
}
