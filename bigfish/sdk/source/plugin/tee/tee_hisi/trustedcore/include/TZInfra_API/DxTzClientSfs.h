/**
 * @file DxSFSClient.h
 * @brief API functions used by TZinfra HLOS client API (DxTzClient.c) for implementing Secure File System
 *
 */

#ifndef	__DX_SFS_CLIENT_H__
#define	__DX_SFS_CLIENT_H__

#include "DxTypes.h"

/**
* Obtains a size of SFS_SW container stored as file in an HLOS filesystem
*
* @param [in]   name    - the HLOS name of file which stores an SFS_SW container
* @param [out]  pSize   - pointer to be filled with the container size. 0 means file
*                         doesn't exist.
* @return DX_BAD_ARGUMENTS      - invalid arguments (NULL argument pointers)
*         Other non-zero values - internal VOS errors
*         DX_SUCCESS            - operation has been successfully completed.
*/
DxStatus DxSfsGetContainerSize (DxChar* name, DxUint* pSize);

/**
* Reads an HLOS SFS_SW container from a file into a buffer
*
* @param [in]   name    - the HLOS name of file which stores an SFS_SW container
* @param [out]  buffer  - the buffer to be filled with the SFS_SW container
* @param [inout] pSize  - pointer to be filled with:
*                            in: size of the destination buffer
*                            out: actual size of the data red
* @return DX_BAD_ARGUMENTS      - invalid arguments (NULL argument pointers)
*         DX_BUFFER_IS_NOT_BIG_ENOUGH - *pSize(in) is smaller then actual file size
*         Other non-zero values - internal VOS errors
*         DX_SUCCESS  if operation has been successfully completed.
*/
DxStatus DxSfsLoadContainerFile (DxChar* name, DxByte* buffer, DxUint* pSize);


/**
* Stores an HLOS SFS_SW container from a buffer into a file
*
* @param [in]   name    - the HLOS name of file to store the SFS_SW container
* @param [out]  buffer  - a container to save
* @param [inout] size   - the size of the container
* @return DX_BAD_ARGUMENTS      - invalid arguments (NULL argument pointers)
*         Other non-zero values - internal VOS errors
*         DX_SUCCESS  if operation has been successfully completed.
*/
DxStatus DxSfsSaveContainerFile (DxChar* name, DxByte* buffer, DxUint size);


#endif //__DX_SFS_CLIENT_H__
