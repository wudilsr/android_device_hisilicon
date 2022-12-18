

 #ifndef _DX_VOS_MEMMAP_H
#define _DX_VOS_MEMMAP_H

/*! \file DX_VOS_Memmap.h
    \brief This file enables mapping memory operations
*/

#include "DX_VOS_BaseTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_NUMBER_ENTRIES 100

typedef struct DX_PhysicalAddr_t{
        DxUint16 nEntries;
        DxUint32 *entry_addr[MAX_NUMBER_ENTRIES];
        DxUint32 entrySize[MAX_NUMBER_ENTRIES];
}DX_PhysicalAddr_t;

/*! Returns the base virtual address that maps the base physical address.
	\return
	- DX_SUCCESS - On success.
	- DX_BAD_ARGUMENTS - if argument equals NULL.
	- DX_VOS_MEMMAP_ERROR - if operation fails.
 **/
DxStatus DX_VOS_MemMap(
	DxUint32 aPhysicalAddress, /*!< [in]  Starts physical address of the I/O range to be mapped. */
	DxUint32 aMapSize,		 /*!< [in]  Number of bytes that were mapped. */
	DxUint32 *aVirtualAddr	 /*!< [out] Pointer to the base virtual address to which the physical pages were mapped */
	);


/*! Unmaps a specified address range previously mapped by DX_VOS_MemMap.
	\return
	- DX_SUCCESS - On success.
	- DX_BAD_ARGUMENTS - if argument equals NULL.
	- DX_VOS_MEMMAP_ERROR - if operation fails.
 **/

DxStatus DX_VOS_MemUnMap(
	void *aVirtualAddr, /*!< [in] Pointer to the base virtual address to which the physical pages were mapped */
	DxUint32 aMapSize /*!< [in] Number of bytes that were mapped. */
	);

/*! Converts the virtual memory to physical memory.
	\return
	- DX_SUCCESS - On success.
	- DX_BAD_ARGUMENTS - if argument equals NULL.
	- DX_VOS_MEMMAP_ERROR - if operation fails.
*/
DxStatus DX_VOS_MemVirtualToPhysical(
	void *aVirtualAddr,  /*!< [in]  Pointer to the base virtual address to which the physical pages were mapped */
	DxUint32 aMapSize, /*!< [in]  Number of bytes that were mapped. */
	DX_PhysicalAddr_t *aPhysicalAdrr /*! [out] Pointer to physical address array. */
	);


#ifdef __cplusplus
}
#endif

#endif /*_DX_VOS_MEMMAP_H*/

