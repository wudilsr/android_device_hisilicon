/**
 * @file DxSFSService.h
 * @brief API functions Secure File System backend (called only from TrustZone only)
 *
 */

#ifndef	__DXSFS_H__
#define	__DXSFS_H__

#include "DxTypes.h"

#ifndef DECLARE_OPAQUE
#define DECLARE_OPAQUE(name)  struct name##__ { DxInt unused; }; \
                    typedef const struct name##__ * name;
#endif

DECLARE_OPAQUE (HSFS)

/**
* Initializes the SFS. !!! Note, the overall size of the container is predefined !!!
*
* @param [out] phSfs a pointer to a HSFS variable to be filled with handle value
* @param [in] pEncryptedContainer the buffer containing encrypted filesystem data (as read from HLOS SFS file)
* @return DX_SUCCESS  if operation has been successfully completed.
*/
DxStatus DxSfsInitialize (HSFS*         phSfs,
                          const DxByte* pContainer,
                          DxUint        containerSize);

/**
* Cleanup and invalidate the handle
*
* @param [out] phSfs a pointer to a HSFS variable to be cleared
* @return DX_SUCCESS  if operation has been successfully completed.
*/
DxStatus DxSfsFinalize (HSFS    hSfs);

DxStatus DxSfsGetSize (HSFS hSfs, const DxChar* name, DxUint* pLen);

DxStatus DxSfsRead (HSFS            hSfs,
                    const DxChar*   name,
                    DxUint          offset,
                    DxByte*         pDst,
                    DxUint*         pSize2read);

DxStatus DxSfsWrite (HSFS           hSfs,
                     const DxChar*  name,
                     const DxByte*  pSrc,
                     DxUint         offset,
                     DxUint         size2write);

DxStatus DxSfsDelete (HSFS hSfs, const DxChar* name);

DxStatus DxSfsCreateContainer (HSFS hSfs, DxByte* pContainer, DxUint* pSize);

#endif /*__DXSFS_H__*/
