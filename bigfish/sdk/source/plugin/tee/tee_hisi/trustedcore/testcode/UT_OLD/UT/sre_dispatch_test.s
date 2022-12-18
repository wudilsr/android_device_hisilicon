@                           ALL RIGHTS RESERVED                             */
@ Author: gaoxiong
@ Description: thread scheduler
@ History:
@  gaoxiong  2011-11-15  implememt task and swi
@  leilulu   2011-11-16  implement hwi
@  gaoxiong  2011-11-17  modify hwi
@
@ NOTICE: keep R8 <-&g_vuwUniFlag  and R1 <- g_vuwUniFlag fresh between scheduler modules
@*****************************************************************************/

  @  AREA  KERNEL,CODE,READONLY
    .text

    @.include "..\include\sre_asm_macro.ph"
    .include "sre_asm_macro.ph"

    .global ostestIrqDispatcher
    .global osTaskContextSwitch_test
    .global _osSwiTrap_test

    .extern g_pRunningTask
    .extern g_pHighestTask
    .extern g_vuwUniFlag
    .extern m_astHwiForm
    .extern g_vuwIntCount
    .extern g_pstSwiActive
    .extern g_usSwiPriorityLevel
    .extern g_vuwSwiRdy
    .extern g_astSwiReadyList
    .extern g_aucSwiNum
    @.extern osTskEntry

    @.extern Swi_Dispatch
    @.extern Image$$ARM_LIB_STACKHEAP$$ZI$$Limit @ Linker symbol from scatter file

.equ OS_ARM_PSR_IRQ_DIS, 0x80
.equ OS_ARM_PSR_FIQ_DIS, 0x40
.equ OS_ARM_PSR_SVC, 0x13
.equ OS_ARM_PSR_THUMB, 0x20
.equ OS_ARM_PSR_ASYABORT_MASK, 0x100

.equ OS_FLG_SWI_REQ, 0x0200
.equ OS_FLG_TSK_REQ, 0x1000
.equ OS_FLG_HWI_ACTIVE, 0x0001
.equ OS_FLG_SWI_ACTIVE, 0x0004
.equ OS_FLG_SWI_ENABLE, 0x0100

.equ OS_TSK_RUNNING, 0x0080

_osSwiTrap_test:
    STMFD  SP!, {LR}  @ PC
    STMFD  SP!, {LR}  @ LR
    STMFD  SP!, {R0-R12}
    MRS    R0, CPSR
    TST    LR, #1
    ORRNE  R0, R0, #OS_ARM_PSR_THUMB
    STMFD  SP!, {R0}

    LDR    R0, =g_pRunningTask
    LDR    R1, [R0]
    STR    SP, [R1]

    CPSID  if

    LDR    R8, =g_vuwUniFlag
    LDR    R1, [R8]
    TST    R1, #OS_FLG_SWI_REQ
    BEQ    osTaskContextSwitch_test

    LDR    SP, =ARM_LIB_STACKHEAP
    B      osSwiDispatcher

@===================================================================
@ HWI dispatcher
@ l00184321 add the code start
@===================================================================
ostestIrqDispatcher:

    SUB     LR, LR, #4
    STMFD   SP!, {R0-R2}
    MOV     R0, SP
    MRS     R1, SPSR
    MOV     R2, LR

    MSR    CPSR_c, #(OS_ARM_PSR_IRQ_DIS | OS_ARM_PSR_FIQ_DIS | OS_ARM_PSR_SVC)
	MSR    CPSR_x, #OS_ARM_PSR_ASYABORT_MASK

	@MSR     CPSR_c, #(OS_ARM_PSR_FIQ_DIS | OS_ARM_PSR_SVC)

    STMFD   SP!, {R2}         @ Push task's PC,
    STMFD   SP!, {LR}         @ Push task's LR,
    STMFD   SP!, {R3-R12}     @ Push task's R12-R3,
    LDMFD   R0!, {R5-R7}      @ Move task's R2-R0 from exception stack to task's stack.
    STMFD   SP!, {R5-R7}
    STMFD   SP!, {R1}         @ Push task's CPSR (i.e. exception SPSR).

    LDR    R0, =g_vuwUniFlag
    LDR    R1, [R0]
    TST    R1, #(OS_FLG_HWI_ACTIVE | OS_FLG_SWI_ACTIVE)
    BNE    osHwiDispatchBegin

    @ g_pRunningTask->pStackPointer = SP
    LDR    R2, =g_pRunningTask
    LDR    R3, [R2]
    STR    SP, [R3]
    LDR    SP, =ARM_LIB_STACKHEAP

osHwiDispatchBegin:

    @ g_vuwUniFlag |= OS_FLG_HWI_ACTIVE
    ORR    R1, #OS_FLG_HWI_ACTIVE
    STR    R1, [R0]

    @ g_vuwIntCount++
    LDR    R0, =g_vuwIntCount
    LDR    R1, [R0]
    ADD    R1, #1
    STR    R1, [R0]

    MRC    p15, 4, r4, c15, c0, 0  @ Read periph base address
    ADD    R4, R4, #0x100
    LDR    R5, [R4, #0xc]
    SWAP32 R5, R5
    LDR    R1, =0x3ff         @get the ackid [9:0]
    AND    R0, R5, R1

    LSL    R0, #3             @r0*8 index the function
    LDR    R1, =m_astHwiForm
    ADD    R1, R1, r0
    LDR    R12, [R1]          @ r12  = m_astHwiForm[index].pfnIntHook
    LDR    R0, [R1, #4]       @ r0 = m_astHwiForm[index].uwIntParam

    CPSIE  f
    BLX    R12
    CPSID  if

    SWAP32 R5, R5
    STR    R5, [R4, #0x10]    @clear fiq bit

    @ g_vuwIntCount--
    LDR   R0, =g_vuwIntCount
    LDR   R1, [R0]
    SUBS  R1, #1
    STR   R1, [R0]

    @ nest irq: g_vuwIntCount > 0
    BNE   osThrdContextLoad

    @ g_vuwUniFlag &= ~OS_FLG_HWI_ACTIVE
    LDR    R8, =g_vuwUniFlag
    LDR    R1, [R8]
    BIC    R1, #OS_FLG_HWI_ACTIVE
    STR    R1, [R8]

@===================================================================

@===================================================================
osSwiDispatcher:
    @ if (OS_FLG_SWI_ENABLE & OS_FLG_SWI_REQ) goto SwiLoopFinish
    MOV    R0, #(OS_FLG_SWI_ENABLE | OS_FLG_SWI_REQ)
    BICS   R0, R0, R1
    BNE    osSwiDispatchEnd

    LDR    R7, =g_vuwSwiRdy
    LDR    R9, =g_pstSwiActive
    LDR    R10, =g_usSwiPriorityLevel
    LDR    R11, =g_astSwiReadyList

    LDR    R5, [R9]  @ pstOldSwi

osSwiLoopBegin:
    LDRH   R2, [R10]

    @ if (!pstOldSwi)  goto osHighestSwiSet
    CMP    R5, #0
    BEQ    osSwiSetHighest

    @ R1 <- (pstOldSwi->usPriority)
    LDRH   R1, [R5, #6]
    CMP    R1, R2
    MOVLS  R2, R1

osSwiSetHighest:
    @ R1 <- swiHighest
    LDR    R3, [R7]
    CLZ    R1, R3

    CMP    R1, R2
    BGE    osSwiLoopEnd

    @ R6 <- uwSwiPriorBit
    MOV    R0, #0x80000000
    LSR    R6, R0, R1

    LDR    R2, =g_aucSwiNum
    LDRB   R2, [R2, R1]       @ R1 <- g_aucSwiNum[swiHighest]
    CMP    R2, #1             @ if(g_aucSwiNum[swiHighest] > 0)
    BHI    osSwiMultReady

    LDR    R4, [R11, R1, LSL #3]  @R0 <-(SWI_ATTRIBUTE_S *)(g_astSwiReadyList[swiHighest].pstPrev)
    STR    R4, [R9]               @ g_pstSwiActive = ...

    @ g_vuwSwiRdy &= ~uwSwiPriorBit
    BIC    R0, R3, R6  @ R3 == g_vuwSwiRdy
    STR    R0, [R7]

    B    osSwiLoopCommon

osSwiMultReady:
    @ pstReadyList = &g_astSwiReadyList[swiHighest]
    ADD  R3, R11, R1, LSL #3

    @ g_pstSwiActive = LIST_COMPONENT(pstReadyList->pstNext, SWI_ATTRIBUTE_S, stObjList)
    LDR   R0, [R3, #4]
    SUB   R4, R0, #0x20
    STR   R4, [R9, #0]

    @ ListDelete
    LDM    R0, {R1, R2}
    STR    R1, [R2, #0]
    STR    R2, [R1, #4]

    @ ListEmpty
    CMP    R2, R3
    BNE    osSwiLoopCommon

    @g_vuwSwiRdy &= ~uwSwiPriorBit
    LDR    R0, [R7, #0]
    BIC    R0, R0, R6
    STR    R0, [R7]

@ R4 <- g_pstSwiActive
@ R0 <- g_vuwSwiRdy
osSwiLoopCommon:
    @ if (g_vuwSwiRdy == 0) g_vuwUniFlag &= ~OS_FLG_SWI_REQ@
    CMP    R0, #0
    LDREQ  R0, [R8, #0]
    BICEQ  R0, R0, #OS_FLG_SWI_REQ
    STREQ  R0, [R8, #0]

    @ g_pstSwiActive->usStatus &= ~OS_SWI_READY@
    @ g_pstSwiActive->usStatus |= OS_SWI_ACTIVE@
    LDRH   R6, [R4, #4]
    BIC    R6, R6, #4
    ORR    R6, R6, #8
    STRH   R6, [R4, #4]

    @ g_pstSwiActive->uwLockValue = g_pstSwiActive->uwRealValue
    @ g_pstSwiActive->uwRealValue = g_pstSwiActive->uwInitValue
    LDR    R0, [R4, #8]
    STR    R0, [R4, #0xc]
    LDR    R0, [R4, #0x10]
    STR    R0, [R4, #8]

    @ g_vuwUniFlag |= OS_FLG_SWI_ACTIVE
    LDR    R2, [R8, #0]
    ORR    R2, R2, #OS_FLG_SWI_ACTIVE
    STR    R2, [R8, #0]

    @ g_pstSwiActive->pfnHandler(r0)
    LDR    R12, [R4, #0]

    CPSIE  f
    BLX    R12
    CPSID  f

    @ g_pstSwiActive->usStatus &= ~OS_SWI_ACTIVE
    BIC    R6, R6, #8  @ R6 == g_pstSwiActive->usStatus
    STRH   R6, [R4, #4]

    @ if (OS_FLG_SWI_ENABLE && OS_FLG_SWI_REQ) goto SwiLoopBegin
    MOV    R0, #(OS_FLG_SWI_ENABLE | OS_FLG_SWI_REQ)
    LDR    R1, [R8]
    BICS   R0, R0, R1
    BEQ    osSwiLoopBegin

osSwiLoopEnd:
    @g_pstSwiActive = pstOldSwi
    STR    R5, [R9]

    LDR   R1, [R8] @ fresh g_vuwUniFlag

    @ if (g_pstSwiActive) g_vuwUniFlag &= ~OS_FLG_SWI_ACTIVE
    CMP    R5, #0
    BNE    osSwiDispatchEnd

    BIC    R1, R1, #OS_FLG_SWI_ACTIVE
    STR    R1, [R8]

osSwiDispatchEnd:
    TST   R1, #OS_FLG_SWI_ACTIVE
    BNE   osThrdContextLoad

@===================================================================
@if (g_vuwUniFlag & OS_FLG_TSK_REQ)
@{
@   g_pRunningTask->usTaskStatus &= ~OS_TSK_RUNNING
@   g_pRunningTask = g_pHighestTask
@   g_pRunningTask->usTaskStatus |= OS_TSK_RUNNING
@}
@
@ R1: g_vuwUniFlag
@ R2: g_pRunningTask
@ R3: &g_pRunningTask
@===================================================================
osTaskContextSwitch_test:
    LDR    R3, =g_pRunningTask
    LDR    R2, [R3]
    TST    R1, #OS_FLG_TSK_REQ
    BEQ    osTaskContextLoad

    @ g_vuwUniFlag &= ~(OS_FLG_TSK_REQ)
    BIC    R1, #(OS_FLG_TSK_REQ)
    STR    R1, [R8]

    @ g_pRunningTask->usTaskStatus &= ~OS_TSK_RUNNING
    LDRH   R4, [R2, #4]
    BIC    R4, #OS_TSK_RUNNING
    STRH   R4, [R2, #4]

    @ g_pRunningTask  = g_pHighestTask
    LDR    R0, =g_pHighestTask
    LDR    R2, [R0]
    STR    R2, [R3]

    @ g_pRunningTask->usTaskStatus |= OS_TSK_RUNNING
    LDRH   R4, [R2, #4] @LDRH
    ORR    R4, #OS_TSK_RUNNING
    STRH   R4, [R2, #4]

osTaskContextLoad:
    @ SP = g_pRunningTask->pStackPointer
    LDR    SP, [R2]

osThrdContextLoad:
    LDMFD  SP!, {R0}
    @MRS    R0,  CPSR
    MSR    SPSR_cxsf, R0

    LDMFD  SP!, {R0-R12, LR, PC}^

    .end
