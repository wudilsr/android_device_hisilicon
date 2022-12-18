#include "QaTestFuncDeclaration.h"
#include "DxTzServiceAPI.h"
#include "QaUtils.h"


// TODO remove following declarations
DxUint32 g_userRootDirLength = 0;
DxChar *userRootDir = DX_NULL;
DxUint cekDataLength = 1;
DxChar cekData[1];



DxStatus memoryAlloc(DxUint32 maxMemorySize){
    DxStatus status = DX_SUCCESS;
    DxUint32 size;
    DxUint32 counter=0;
    void* memoryPtr = DX_NULL;
    DxUint32 repeatCounter = getNumOfLoops();

    DxHwLogTrace(DX_FALSE,"Testing memory DxTzService_Malloc and DxTzService_Free APIs");

    while (0 < repeatCounter--){

        while ((size = power(2,counter++)) < maxMemorySize){

            memoryPtr = DxTzService_Malloc(size);

            if (DX_NULL == memoryPtr){

                REPORT_ERROR1("DxTzService_Malloc failed to allocate memory buffer of 0x%08X size", size);

                status = DX_FAILURE;

                break;
            }

            DxTzService_Free(memoryPtr);
        }

        counter = 0;

        while ((size = power(2,counter++) + 3) < maxMemorySize){

            memoryPtr = DxTzService_Malloc(size);

            if (DX_NULL == memoryPtr){

                REPORT_ERROR1("DxTzService_Malloc failed to allocate memory buffer of 0x%08X size", size);

                status = DX_FAILURE;

                break;
            }

            DxTzService_Free(memoryPtr);
        }

        if (DX_SUCCESS != status){

            break;
        }
    }

    return status;
}

DxStatus memoryReAlloc( DxUint32 maxMemorySize){
    DxStatus status = DX_SUCCESS;
    DxUint32 size, newSize;
    DxUint32 counter=0;
    DxUint16* memoryPtr = DX_NULL;
    DxUint16 i;
    DxUint32 repeatCounter = getNumOfLoops();

    DxHwLogTrace(DX_FALSE,"Testing memory DxTzService_Realloc API");

    while (0 < repeatCounter--){

        //increase realloc size loop
        while ((size = power(sizeof(DxUint16),counter++)) < maxMemorySize){

            memoryPtr = (DxUint16*)DxTzService_Malloc(size);

            if (DX_NULL == memoryPtr){

                REPORT_ERROR1("DxTzService_Malloc failed to allocate memory buffer of 0x%08X size", size);

                status = DX_FAILURE;

                break;
            }

            for (i = 0; i < size/2; i++){

                memoryPtr[i]=i;
            }

            newSize = size + size/2 + 3;

            memoryPtr = (DxUint16*)DxTzService_Realloc(memoryPtr,newSize);

            if (DX_NULL == memoryPtr){

                REPORT_ERROR2("DxTzService_Realloc failed to reallocate memory buffer from 0x%08X to 0x%08X", size, newSize);

                status = DX_FAILURE;

                break;
            }

            for (i = 0; i< size/2; ++i){

                if (memoryPtr[i] != i){

                    REPORT_ERROR0("DxTzService_Realloc returned invalid data in reallocated buffer");

                    status = DX_FAILURE;

                    break;
                }
            }

            DxTzService_Free(memoryPtr);

            memoryPtr = DX_NULL;
        }

        if (DX_SUCCESS != status){

            break;
        }

        counter = 4;

        //decrease realloc size loop
        while ((size = power(sizeof(DxUint16),counter++)) < maxMemorySize){

            memoryPtr = (DxUint16*)DxTzService_Malloc(size);

            if (DX_NULL == memoryPtr){

                REPORT_ERROR1("DxTzService_Malloc failed to allocate memory buffer of 0x%08X size", size);

                status = DX_FAILURE;

                break;
            }

            for (i = 0; i < size/2; i++){

                memoryPtr[i]=i;
            }

            newSize = size - size/2 - 5;

            memoryPtr = (DxUint16*)DxTzService_Realloc(memoryPtr,newSize);

            if (DX_NULL == memoryPtr){

                REPORT_ERROR2("DxTzService_Realloc failed to reallocate memory buffer from 0x%08X to 0x%08X", size, newSize);

                status = DX_FAILURE;

                break;
            }

            for (i = 0; i< newSize/2; ++i){

                if (memoryPtr[i] != i){

                    REPORT_ERROR0("DxTzService_Realloc returned invalid data in reallocated buffer");

                    status = DX_FAILURE;

                    break;
                }
            }

            DxTzService_Free(memoryPtr);

            memoryPtr = DX_NULL;
        }


        if (DX_SUCCESS != status){

            break;
        }
    }

    if (DX_NULL != memoryPtr)

        DxTzService_Free(memoryPtr);


    return status;
}

DxStatus memorySet(DxUint32 maxMemorySize){
    DxStatus status = DX_SUCCESS;
    DxUint8* memoryPtr = DX_NULL;
    DxUint32 size = maxMemorySize/2;
    DxUint32 i;

    QA_LOG_MSG("Testing memory DxTzService_MemSet API");

    memoryPtr = (DxUint8*)DxTzService_Malloc(size);

    if (DX_NULL == memoryPtr){

        REPORT_ERROR1("DxTzService_Malloc failed to allocate memory buffer of 0x%08X size", size);

        status = DX_FAILURE;

        goto ERROR_EXIT;
    }


    //zero memory
    for (i = 0; i < size; i++){

        memoryPtr[i]=0;
    }

    DxTzService_MemSet(memoryPtr + size/4, 0xFF, size/2);

    //test out of scope that memory is unchanged
    for (i = 0; i < size/4; i++){

        if ((memoryPtr[i] != 0) || (memoryPtr[size-1-i] != 0)){

            REPORT_ERROR0("DxTzService_MemSet corrupted out of scope memory");

            status = DX_FAILURE;

            goto ERROR_EXIT;
        }
    }

    //test processed memory
    for (i = size/4; i < size - size/4; i++){

        if (memoryPtr[i] != 0xFF){

            REPORT_ERROR0("DxTzService_MemSet set invalid values");

            status = DX_FAILURE;

            goto ERROR_EXIT;
        }
    }


ERROR_EXIT:

    if (DX_NULL != memoryPtr)

        DxTzService_Free(memoryPtr);

    return status;
}

DxStatus memoryCopy(DxUint32 maxMemorySize){
    DxStatus status = DX_SUCCESS;
    DxUint8* memoryTargetPtr = DX_NULL;
    DxUint8* memorySourcePtr = DX_NULL;
    DxUint32 size = maxMemorySize/4;
    DxUint32 i;

    DxHwLogTrace(DX_FALSE,"Testing memory DxTzService_MemCpy API");

    memoryTargetPtr = (DxUint8*)DxTzService_Malloc(size);

    if (DX_NULL == memoryTargetPtr){

        REPORT_ERROR1("DxTzService_Malloc failed to allocate memory buffer of 0x%08X size", size);

        status = DX_FAILURE;

        goto ERROR_EXIT;
    }

    memorySourcePtr = (DxUint8*)DxTzService_Malloc(size/2);

    if (DX_NULL == memorySourcePtr){

        REPORT_ERROR1("DxTzService_Malloc failed to allocate memory buffer of 0x%08X size", size/2);

        status = DX_FAILURE;

        goto ERROR_EXIT;
    }

    DxTzService_MemSet(memoryTargetPtr, 0, size);

    DxTzService_MemSet(memorySourcePtr, 0xFF, size/2);

    DxTzService_MemCpy(memoryTargetPtr + size/4, memorySourcePtr, size/2);

    //test out of scope that memory is unchanged
    for (i = 0; i < size/4; i++){

        if ((memoryTargetPtr[i] != 0) || (memoryTargetPtr[size-1-i] != 0)){

            REPORT_ERROR0("DxTzService_MemCpy corrupted out of scope target memory");

            status = DX_FAILURE;

            goto ERROR_EXIT;
        }
    }

    //test processed memory
    for (i = size/4; i < size - size/4; i++){

        if (memoryTargetPtr[i] != 0xFF){

            REPORT_ERROR0("DxTzService_MemCpy set invalid target values");

            status = DX_FAILURE;

            goto ERROR_EXIT;
        }
    }

    //test source memory
    for (i = 0; i < size/2; i++){

        if (memorySourcePtr[i] != 0xFF){

            REPORT_ERROR0("DxTzService_MemCpy corrupted source memory");

            status = DX_FAILURE;

            goto ERROR_EXIT;
        }
    }

ERROR_EXIT:

    if (DX_NULL != memoryTargetPtr)

        DxTzService_Free(memoryTargetPtr);

    if (DX_NULL != memorySourcePtr)

        DxTzService_Free(memorySourcePtr);

    return status;
}

DxStatus memoryReverseCopy(DxUint32 maxMemorySize){
    DxStatus status = DX_SUCCESS;
    DxUint8* memoryTargetPtr = DX_NULL;
    DxUint8* memorySourcePtr = DX_NULL;

    DxUint32 size = maxMemorySize/4;
    DxUint32 i;

    QA_LOG_MSG("Testing memory DxTzService_MemCpyReverse API");

    memoryTargetPtr = (DxUint8*)DxTzService_Malloc(size);

    if (DX_NULL == memoryTargetPtr){

        REPORT_ERROR1("DxTzService_Malloc failed to allocate memory buffer of 0x%08X size", size);

        status = DX_FAILURE;

        goto ERROR_EXIT;
    }

    memorySourcePtr = (DxUint8*)DxTzService_Malloc(size/2);

    if (DX_NULL == memorySourcePtr){

        REPORT_ERROR1("DxTzService_Malloc failed to allocate memory buffer of 0x%08X size", size/2);

        status = DX_FAILURE;

        goto ERROR_EXIT;
    }

    DxTzService_MemSet(memoryTargetPtr, 0, size);

    for (i = 0; i < size/2; i++){

        memorySourcePtr[i] = (DxUint8)(i & 0xFF) ;
    }

    DxTzService_MemCpyReverse(memoryTargetPtr + size/4, memorySourcePtr, size/2);

    //test out of scope that memory is unchanged
    for (i = 0; i < size/4; i++){

        if ((memoryTargetPtr[i] != 0) || (memoryTargetPtr[size-1-i] != 0)){

            REPORT_ERROR0("DxTzService_MemCpyReverse corrupted out of scope target memory");

            status = DX_FAILURE;

            goto ERROR_EXIT;
        }
    }

    //test processed memory
    for (i = 0; i < size/2; i++){

        if (memoryTargetPtr[i + size/4] != (DxUint8)((size/2 -i -1)& 0xFF)){

            REPORT_ERROR0("DxTzService_MemCpyReverse set invalid target values");

            status = DX_FAILURE;

            goto ERROR_EXIT;

        }
    }

    //test source memory
    for (i = 0; i < size/2; i++){

        if (memorySourcePtr[i] != (DxUint8)(i & 0xFF)){

            REPORT_ERROR0("DxTzService_MemCpyReverse corrupted source memory");

            status = DX_FAILURE;

            goto ERROR_EXIT;
        }
    }

ERROR_EXIT:

    if (DX_NULL != memoryTargetPtr)

        DxTzService_Free(memoryTargetPtr);

    if (DX_NULL != memorySourcePtr)

        DxTzService_Free(memorySourcePtr);

    return status;
}



DxStatus memoryCompare(DxUint32 maxMemorySize){
    DxStatus status = DX_SUCCESS;
    DxUint8* memoryTargetPtr = DX_NULL;
    DxUint8* memorySourcePtr = DX_NULL;
    DxUint8* opMemoryTargetPtr = DX_NULL;
    DxUint8* opMemorySourcePtr = DX_NULL;

    DxUint32 size = maxMemorySize/4;
    DxUint32 opSize = size/2;
    DxUint32 i;

    DxHwLogTrace(DX_FALSE,"Testing memory DxTzService_MemCmp API");


    memoryTargetPtr = (DxUint8*)DxTzService_Malloc(size);

    if (DX_NULL == memoryTargetPtr){

        REPORT_ERROR1("DxTzService_Malloc failed to allocate memory buffer of 0x%08X size", size);

        status = DX_FAILURE;

        goto ERROR_EXIT;

    }

    opMemoryTargetPtr = memoryTargetPtr + size/4;

    memorySourcePtr = (DxUint8*)DxTzService_Malloc(size);

    if (DX_NULL == memorySourcePtr){

        REPORT_ERROR1("DxTzService_Malloc failed to allocate memory buffer of 0x%08X size", size);

        status = DX_FAILURE;

        goto ERROR_EXIT;
    }

    opMemorySourcePtr = memorySourcePtr + size/4;

    DxTzService_MemSet(memoryTargetPtr, 0, size);

    DxTzService_MemSet(memorySourcePtr, 0, size);

    if (0 != DxTzService_MemCmp(opMemorySourcePtr, opMemorySourcePtr, opSize)){

        REPORT_ERROR0("DxTzService_MemCmp returned non 0 for while comparing buffer to itself");

        status = DX_FAILURE;

        goto ERROR_EXIT;
    }

    if (0 != DxTzService_MemCmp(opMemorySourcePtr, opMemoryTargetPtr, opSize)){

        REPORT_ERROR0("DxTzService_MemCmp returned non 0 for while comparing two equal buffers");

        status = DX_FAILURE;

        goto ERROR_EXIT;
    }

    for (i = 0; i < size; i++){

        if ((memorySourcePtr[i] != 0) || (memoryTargetPtr[i] != 0)){

            REPORT_ERROR0("DxTzService_MemCmp corrupted memory");

            status = DX_FAILURE;

            goto ERROR_EXIT;
        }
    }


    DxTzService_MemSet(memorySourcePtr, 0xFF, size);

    if (0 == DxTzService_MemCmp(opMemorySourcePtr, opMemoryTargetPtr, opSize)){

        REPORT_ERROR0("DxTzService_MemCmp returned 0 while comparing non equal buffers");

        status = DX_FAILURE;

        goto ERROR_EXIT;
    }


    for (i = 0; i < size; i++){

        if ((memorySourcePtr[i] != 0xFF) || (memoryTargetPtr[i] != 0)){

            REPORT_ERROR0("DxTzService_MemCmp corrupted memory");

            status = DX_FAILURE;

            goto ERROR_EXIT;
        }
    }

ERROR_EXIT:

    if (DX_NULL != memoryTargetPtr)

        DxTzService_Free(memoryTargetPtr);

    if (DX_NULL != memorySourcePtr)

        DxTzService_Free(memorySourcePtr);

    return status;
}
