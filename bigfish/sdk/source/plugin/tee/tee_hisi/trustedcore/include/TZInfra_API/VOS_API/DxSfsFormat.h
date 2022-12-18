/**
 * @file DxSfsFormat.h
 * @brief private functions of Secure File System backend called from HLOS and TrustZone
 *
 */

#ifndef	__DX_SFS_FORMAT_H_
#define	__DX_SFS_FORMAT_H_

#include "DxTypes.h"

/* Version independent */

    /* Constants */
#define SFS_MAGIC_VALUE		0x53465344	/* 'DSFS' */
#define DIGEST_SIZE	        32	        /* SHA256_SIGNATURE_SIZE */

    /* Recommendations */
#define NAME_LEN_MAX        32
#define NUM_FAT_ENTRIES     20


/* Version dependent */
#define SFS_VERSION_V1	    1			/* A version of the FAT format */
#define	KEY_SIZE_V1	        16
#define	IV_SIZE_V1	        16

/* Types */

typedef struct
{
	DxUint32    offset;             /* The offset of the file data within the data area.*/
	DxUint32    size;               /* The length of the data for this file.*/
	DxByte      key[KEY_SIZE_V1];   /* Key used for encrypting this file.*/
	DxByte      iv[IV_SIZE_V1];     /* iv used for encrypting this file.*/
	/*DxChar      name[0];             Placeholder for the name of this file. Since its
                                       length may very, we don't include it in the
                                       structure, but keep in mind that it follows
                                       right after.*/
}
FatEntryV1_t;

typedef struct
{
	DxUint32    version;            /* File System version (SFS_VERSION_V1).*/
	DxUint32    dataBlockSize;      /* Size of the following "Data Area" block.*/
	DxUint32    numEntries;         /* The number of entries in this FAT.*/
	DxUint32    nameLength;         /* The length of the "name" field in FAT entry.*/
	DxUint32    dataSizeUsed;       /* Actually used data size.*/
	DxByte      dataDigest[DIGEST_SIZE];    /* SHA256 for the whole data block.*/
}
FatHdrV1_t;

typedef struct
{
	DxUint32    magic;              /* SFS_MAGIC_VALUE or 0 in case of uninitialized FAT.*/
	DxUint32    wrappedFatSize;     /* Size of the following "FAT" block.*/
   /* DxByte      wrappedFatHdr[0];    Placeholder for the FAT. Since its length may very,
                                       we don't include it in the structure, but keep in
                                       mind that it follows right after.*/
}
ContainerHdr_t;

/* The container looks as following:

    open        |                             Wrapped                                     | AES128 CTR FatEntryV1_t.key/iv |
---------------------------------------------------------------------------------------------------------------------
 ContainerHdr_t | FatHdrV1_t | (FatEntryV1_t+FatHdrV1_t.nameLength)*FatHdrV1_t.numEntries |     FatHdrV1_t.dataBlockSize   |
*/

#endif /* __DX_SFS_FORMAT_H_ */
