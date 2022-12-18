#include "QaTestFuncDeclaration.h"
#include "QaUtils.h"
//////////////////////////////////////////////
// createDeviceKey test -
//////////////////////////////////////////////
DxStatus createDeviceKey(DxUint32 id, DxUint8 *buff, DxUint32 length)
{
    DxStatus status=DX_SUCCESS;
    DxUint8* localbuff=DX_NULL;

    localbuff = DxTzService_Malloc(length);
    if (DX_NULL == localbuff ){
        REPORT_ERROR0("DxTzService_Malloc failed");
        status=DX_FAILURE;
        PERFORM_CLEANUP;
    }

    status = DxTzService_GetDeviceKey( id, localbuff, length);
    if (DX_SUCCESS != status ){
        REPORT_ERROR1("DxTzService_GetDeviceKey failed with return value 0x%08X",status);
        PERFORM_CLEANUP;
    }

    if (DxTzService_MemCpy(buff,localbuff,length) == DX_NULL){
        REPORT_ERROR0("DxTzService_MemCpy failed");
        status=DX_FAILURE;
        PERFORM_CLEANUP;
    }

CLEANUP_SECTION:
    DxTzService_Free(localbuff);
    return status;
}

//////////////////////////////////////////////
// GetUniqueDeviceKey test
//////////////////////////////////////////////
DxStatus GetUniqueDeviceKey(DxUint8* pDevUniqueID, DxUint32 *length)
{
    DxStatus status=DX_SUCCESS;
#ifndef DX_MSM8960Qsee
    //issue 7203
    DxUint8* localDevUniqueID=DX_NULL;
    DxUint32 localLen=0;

    localDevUniqueID = DxTzService_Malloc(*length);
    if (DX_NULL == localDevUniqueID ){
        REPORT_ERROR0("DxTzService_Malloc failed");
        status=DX_FAILURE;
        PERFORM_CLEANUP;
    }
    localLen=*length;

    status = DxTzService_Get_Device_UniqueId(localDevUniqueID, &localLen);
    if (DX_SUCCESS != status ){
        REPORT_ERROR1("DxTzService_Get_Device_UniqueId failed with return value 0x%08X",status);
        PERFORM_CLEANUP;
    }

    if (DxTzService_MemCpy(pDevUniqueID,localDevUniqueID,localLen) == DX_NULL){
        REPORT_ERROR0("DxTzService_MemCpy failed");
        status=DX_FAILURE;
        PERFORM_CLEANUP;
    }
    *length=localLen;

CLEANUP_SECTION:

    DxTzService_Free(localDevUniqueID);
#else
    status = DX_FAILURE;
    REPORT_ERROR0("DxTzService_Get_Device_UniqueId failed - issue 7203");
#endif
    return status;
}

