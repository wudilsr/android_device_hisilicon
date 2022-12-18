#ifndef __SRE_SYSCALLS_EXT_H__
#define __SRE_SYSCALLS_EXT_H__

#include "sre_base.h"
#include "sre_task.h"
#include "sre_ticktimer.h"
#include "sre_msg.h"
#include "sre_swi.h"
#include "sre_sem.h"
#include "sre_fsem.h"
#include "sre_task.h"
#include "sre_hwi.h"
#include "sre_mem.h"
#include "sre_package.h"

#include <hi_type.h>
#include <drv_cipher_define.h>
#include "mmz_struct.h"


typedef struct swi_temp_regs_ext {
    UINT32 spsr;
    UINT32 regs[4];
    UINT32 regs_r4_12[9];
    UINT32 regs_lr;   //r12 and lr pushed in sre_vector.s
    UINT32 regs_lr_2; //this push occur in sre_syscalls.S
    UINT32 args[12];

}stSWITempRegs_ext;


extern HI_S32 __Cipher_Init(HI_VOID);
extern HI_VOID __Cipher_Exit(HI_VOID);
extern HI_S32 __Cipher_CreateHandle(HI_HANDLE* phCipher, const HI_UNF_CIPHER_ATTS_S *pstCipherAttr);
extern HI_S32 __Cipher_DestroyHandle(HI_HANDLE hCipher);
extern HI_S32 __Cipher_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl);
extern HI_S32 __Cipher_GetHandleConfig(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl);
extern HI_S32 __Cipher_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);
extern HI_S32 __Cipher_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);
extern HI_S32 __Cipher_EncryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum);
extern HI_S32 __Cipher_DecryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum);
extern HI_S32 __Cipher_CalcMAC(HI_HANDLE hCipherHandle, HI_U8 *pInputData, HI_U32 u32InputDataLen,HI_U8 *pOutputMAC, HI_BOOL bIsLastBlock);
extern HI_S32 __Cipher_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle);
extern HI_S32 __Cipher_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen);
extern HI_S32 __Cipher_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash);
extern HI_S32 __RNG_GetRandomNumber(HI_U32 *pu32Rnd);
extern HI_S32 __Cipher_GetIVOut(HI_HANDLE hCipher, HI_U8 *pu8IVOut);

extern HI_S32 __VDEC_Suspend(HI_VOID);
extern HI_S32 __VDEC_Init(HI_U32 pCallback);
extern HI_S32 __VDEC_Resume(HI_VOID);
extern HI_S32 __VFMW_CTRL_thread_sec(HI_VOID);
extern HI_S32 __VDEC_Control(HI_U32 ChanID, HI_U32 eCmdID, HI_U32 pArgs);
extern HI_S32 __VDEC_InitWithOperation(HI_U32 pArgs);
extern HI_S32 __VCTRL_WriteProc(HI_U32 option, HI_U32 value);
extern HI_S32 __VCTRL_ReadProc(HI_U32 page, HI_U32 pagelen);
extern HI_S32 __VCTRL_SetDbgOption(HI_U32 opt, HI_U32 p_ags);
extern HI_S32 __VCTRL_GetChanImage(HI_U32 ChanID, HI_U32 p_image);
extern HI_S32 __VCTRL_ReleaseChanImage(HI_U32 ChanID, HI_U32 p_image);
extern HI_S32 __VDEC_Exit(HI_VOID);
extern HI_S32 __Cipher_Test(HI_U32 u32Cmd, HI_U32 *pu32Result, HI_U32 u32Param1, HI_U32 u32Param2);

/*MMZ*/
extern int __MMZ_MALLOC(HI_MMZ_BUF_S *pBuf);
extern int __MMZ_FREE(HI_MMZ_BUF_S *pBuf);
extern int __MMZ_NEW(HI_MMZ_BUF_S *pBuf, char *mmz_name, char *mmb_name);
extern int __MMZ_DEL(unsigned long addr);
extern int __MMZ_MAP(unsigned long addr, unsigned long cached);
extern int __MMZ_UNMAP(unsigned long addr);
extern int __MMZ_FLUSH(unsigned long addr);

extern int __TEE_IsSecMem(unsigned long phys_addr, unsigned long size);
extern int __TEE_IsNonSecMem(unsigned long phys_addr, unsigned long size);
extern int __call_debug(unsigned long arg0, unsigned long arg1, unsigned long arg2, unsigned long arg3);

extern int __mem_copy(unsigned long src, unsigned long dest, int size);

#endif
