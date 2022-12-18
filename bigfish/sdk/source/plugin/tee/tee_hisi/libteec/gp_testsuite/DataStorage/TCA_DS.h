#ifndef __TCA_DS_H
#define __TCA_DS_H


/** Command ids **/
#define CMD_DS_AllocateTransientChain                          0x00001001
#define CMD_DS_GetObjectInfoPanic                              0x00001002
#define CMD_DS_RestrictObjectUsagePanic                        0x00001003
#define CMD_DS_CloseObjectPanic                                0x00001004
#define CMD_DS_CloseFreeAndResetObjectSuccessHandleNull        0x00001005
#define CMD_DS_FreeTransientObjectPanic                        0x00001006
#define CMD_DS_ResetTransientObjectPanic                       0x00001007
#define CMD_DS_StoreAndReadBufferAttribute                     0x00001008
#define CMD_DS_InitRefAttributePanic                           0x00001009
#define CMD_DS_InitObjectAndAttributes                         0x0000100A
#define CMD_DS_GenerateKey                                     0x0000100B
#define CMD_DS_CreatePersistentObjectPanic                     0x0000100C
#define CMD_DS_CreatePersistentObject_ItemNotFound             0x0000100D
#define CMD_DS_CreatePersistentObject_AccessConflict           0x0000100E
#define CMD_DS_CreatePersistentObject_Success                  0x0000100F
#define CMD_DS_OpenPersistentObjectPanic                       0x00001010
#define CMD_DS_OpenPersistentObject_ItemNotFound               0x00001011
#define CMD_DS_OpenPersistentObject_Success                    0x00001012
#define CMD_DS_RenamePersistentObjectPanic                     0x00001013
#define CMD_DS_RenamePersistentObject_AccessConflict           0x00001014
#define CMD_DS_RenamePersistentObject_Success                  0x00001015
#define CMD_DS_EnumeratorOnPersistentObjects                   0x00001016
#define CMD_DS_CloseAndDeletePersistentObjectPanic             0x00001017
#define CMD_DS_FreeCloseAndDeletePersistentObjectSuccessHandleNull   0x00001018
#define CMD_DS_FreePersistentObjectEnumeratorPanic             0x00001019
#define CMD_DS_ResetPersistentObjectEnumeratorPanic            0x0000101A
#define CMD_DS_StartPersistentObjectEnumeratorPanic            0x0000101B
#define CMD_DS_GetNextPersistentObjectPanic                    0x0000101C
#define CMD_DS_StartNGetPersistentObjectEnumerator_itemNotFound   0x0000101D
#define CMD_DS_GetBufferAttribute_object_uninitialized         0x0000101E
#define CMD_DS_InitValueAttribute                              0x0000101F
#define CMD_DS_OpenPersistentObject_conflict                   0x00001020
#define CMD_DS_GetRSAAttributes                                0x00001021
#define CMD_DS_GetObjectValueAttributePanic                    0x00001022
#define CMD_DS_GetDHAttributes                                 0x00001023
#define CMD_DS_ReadObjectData_panic                            0x00001024
#define CMD_DS_WriteObjectData_panic                           0x00001025
#define CMD_DS_TruncateObjectData_panic                        0x00001026
#define CMD_DS_SeekObjectData_panic                            0x00001027
#define CMD_DS_ReadObjectData                                  0x00001028
#define CMD_DS_SeekWriteReadObjectData                         0x00001029
#define CMD_DS_TruncateReadObjectData                          0x0000102A



#endif
