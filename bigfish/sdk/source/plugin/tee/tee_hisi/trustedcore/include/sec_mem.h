
#ifndef __SEC_MEM_H
#define __SEC_MEM_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#define NON_SEC_OS_MEM        0
#define SEC_OS_MEM            1
#define SEC_MMZ_MEM           2
#define NON_SEC_MMZ_MEM       3

int HI_TEE_IsSecureMem(unsigned long phys_addr, unsigned long size);

int HI_TEE_IsNonSecureMem(unsigned long phys_addr, unsigned long size);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
