/**
 * @file DxSFSClient.h
 * @brief API functions used by TZinfra HLOS client API (DxTzClient.c) for implementing Secure File System
 * @author Discretix
 *  		2013-03-11	Ben Baron
 */

#include "DX_VOS_String.h"
#include "DX_VOS_File.h"
#include "DX_VOS_Mem.h"
#include "DxTzClientSfs.h"

DxStatus DxSfsGetContainerSize (DxChar* name, DxUint* pSize)
{
	DxStatus    result;
	DxVosFile   hFile;
    DxUint32    size = *pSize;

    if (DX_NULL == name || DX_NULL == pSize)
    {
        DX_DBG_PRINT2 (DX_DBGPRINT_ERROR_LEVEL,
                       "DxSfsGetContainerSize: Invalid parameters: %p, %p\n",
                       name, pSize);
        return DX_BAD_ARGUMENTS;
    }

    if (DX_TRUE != DX_VOS_IsFileExists (name))
    {
        *pSize = 0;
        return DX_SUCCESS;
    }

    result = DX_VOS_FOpen (&hFile, name, "rb");
	if (DX_SUCCESS != result)
    {
        DX_DBG_PRINT1 (DX_DBGPRINT_ERROR_LEVEL,
                       "DxSfsGetContainerSize: Failed to open file %s\n", name);
        return result;
    }

    result = DX_VOS_FGetFileSize (hFile, &size);
    if (DX_SUCCESS != result)
    {
        DX_DBG_PRINT1 (DX_DBGPRINT_ERROR_LEVEL, "DxSfsGetContainerSize: "
                      "Failed to obtain a size of file %s\n", name);
        goto end;
    }

    *pSize = size;

end:

	DX_VOS_FClose (hFile);

	return result;
}

/******************************************************************************
*******************************************************************************
******************************************************************************/

DxStatus DxSfsLoadContainerFile (DxChar* name, DxByte* buffer, DxUint* pSize)
{
	DxStatus    result;
	DxVosFile   hFile;
    DxUint32    fileSize  = 0;
	DxUint32    bytesRead = 0;

    if (DX_NULL == name || DX_NULL == pSize)
    {
        DX_DBG_PRINT2 (DX_DBGPRINT_ERROR_LEVEL,
                       "DxSfsLoadContainerFile: Invalid parameters: %p, %p\n",
                       name, pSize);
        return DX_BAD_ARGUMENTS;
    }

    result = DX_VOS_FOpen (&hFile, name, "rb");
	if (DX_SUCCESS != result)
    {
        DX_DBG_PRINT1 (DX_DBGPRINT_ERROR_LEVEL,
                       "DxSfsLoadContainerFile: Failed to open file %s\n", name);
        return DX_ITEM_NOT_FOUND;
    }

    result = DX_VOS_FGetFileSize (hFile, &fileSize);
    if (DX_SUCCESS != result)
    {
        DX_DBG_PRINT1 (DX_DBGPRINT_ERROR_LEVEL, "DxSfsLoadContainerFile: "
                      "Failed to obtain a size of file %s\n", name);
        goto end;
    }

    if (fileSize > *pSize)
    {
        DX_DBG_PRINT3 (DX_DBGPRINT_ERROR_LEVEL, "DxSfsLoadContainerFile: "
                       "The size of file %s (%u) is bigger then the provided buffer (%u)\n",
                       name, fileSize, *pSize);
        result = DX_BUFFER_IS_NOT_BIG_ENOUGH;
        goto end;
    }

    result = DX_VOS_FReadEx (hFile, buffer, fileSize, &bytesRead);
    if (DX_SUCCESS != result)
    {
        DX_DBG_PRINT3 (DX_DBGPRINT_ERROR_LEVEL, "DxSfsLoadContainerFile: "
                       "Failed to read file %s (%u) into buffer of %u bytes\n",
                       name, fileSize, *pSize);
        goto end;
    }

    if (bytesRead != fileSize)
    {
        DX_DBG_PRINT3 (DX_DBGPRINT_ERROR_LEVEL, "DxSfsLoadContainerFile: "
                       "The read bytes (%u) differ from the expected (%u) for file %s\n",
                       bytesRead, fileSize, name);
        goto end;
    }

    *pSize = bytesRead;

end:

	DX_VOS_FClose (hFile);

	return result;
}

/******************************************************************************
*******************************************************************************
******************************************************************************/

DxStatus DxSfsSaveContainerFile (DxChar* name, DxByte* buffer, DxUint size)
{
	DxStatus    result = DX_SUCCESS;
	DxVosFile   hFile;

    if (DX_NULL == name || DX_NULL == buffer)
    {
        DX_DBG_PRINT2 (DX_DBGPRINT_ERROR_LEVEL,
                       "DxSfsSaveContainerFile: Invalid parameters: %p, %p\n",
                       name, buffer);
        return DX_BAD_ARGUMENTS;
    }

    result = DX_VOS_FOpen (&hFile, name, "w+b");
	if (DX_SUCCESS != result)
    {
        DX_DBG_PRINT1 (DX_DBGPRINT_ERROR_LEVEL,
                       "DxSfsSaveContainerFile: Failed to open file %s\n", name);
        return result;
    }

    result = DX_VOS_FWrite (hFile, buffer, size);
    {
        DX_DBG_PRINT3 (DX_DBGPRINT_ERROR_LEVEL,
                       "DxSfsSaveContainerFile: Failed to write file %s (%p, %u)\n",
                       name, buffer, size);
    }

	DX_VOS_FClose (hFile);

	return result;
}

