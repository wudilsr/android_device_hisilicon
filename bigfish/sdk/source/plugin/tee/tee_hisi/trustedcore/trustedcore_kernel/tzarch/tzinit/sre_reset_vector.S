@                           ALL RIGHTS RESERVED                             */
@ Author: wangdaneng
@ Description: reset vector processing
@ History:
@  wangdaneng  2012-10-25  import from RVDS sample
@*****************************************************************************/

    .text
    .include "sre_asm_macro.ph"

    .equ MODE_BITS,           0x1F        @ Bit mask for mode bits in CPSR
    .equ USR_MODE,            0x10        @ User mode
    .equ FIQ_MODE,            0x11        @ Fast Interrupt Request mode
    .equ IRQ_MODE,            0x12        @ Interrupt Request mode
    .equ SVC_MODE,            0x13        @ Supervisor mode
    .equ MON_MODE,            0x16         @ monitor mode
    .equ ABT_MODE,            0x17        @ Abort mode
    .equ UND_MODE,            0x1B        @ Undefined Instruction mode
    .equ SYS_MODE,            0x1F        @ System mode

    .equ TTB_TEXT,         0x00004c06     @(NS)0 (nG)0 (S)0 (AP[2])0 (TEX[2:0])100  (AP[1:0])11 (IMP)0 (Domain)0000 (XN)0 (C)0 (B)1 10
    .equ TTB_LO_DATA,      0x00000c1e     @(NS)0 (nG)0 (S)0 (AP[2])0 (TEX)000 (AP[1:0])11 (IMP)0 (DOMAIN)0000 (XN)1 (C)1 (B)1 10
    .equ TTB_SH_DATA,      0x00000c1e     @(NS)0 (nG)0 (S)0 (AP[2])0 (TEX)000 (AP[1:0])11 (IMP)0 (DOMAIN)0000 (XN)1 (C)1 (B)1 10
    .equ TTB_DEVICE,       0x00000c06     @(NS)0 (nG)0 (S)0 (AP[2])0 (TEX)000  (AP[1:0])11 (IMP)0 (Domain)0000 (XN)0 (C)0 (B)1 10

    .equ NSACR_REG_VAL,      0x43fff
    .equ SCR_FIQ_BIT,        0x4
    .equ SECURE_IMG_DDR_ADDR,0x22000000


    .global  osResetVector
    .extern  clean_invalidate_dcache

    .extern  Image$$TEXT$$Base
    .extern  Image$$LO_DATA$$Base
    .extern  Image$$LO_DATA$$Limit
    .extern  Image$$SH_DATA$$Base
    .extern  Image$$SH_DATA$$Limit
    @.extern  Image$$TTB$$Base
    .extern  g_aucSmpOnline
    .extern  osRelocVector
    .extern  Normal_CONTEXT_ENTRY
    .extern  N_PC
    .extern  N_SVC_R13
    .extern  N_SVC_R14
    .extern  N_SVC_SPSR
    .extern  N_IRQ_R13
    .extern  N_ABT_R13
    .extern  N_CPSR
    .extern  S_CPSR
    .extern  secure_uart_enable

   @ .extern  __main
    .extern  main

    @ENTRY

    .global _start

_start:

osResetVector:

@==================================================================
@ TrustedCore Entry
@ Boot sequence
@ 1.Fastboot execute in Secure World.
@ 2.Fastboot load TrustedCore and jump to TrustedCore entry point.
@ 3.TrustedCore build normal world context(Normal_CONTEXT_ENTRY)
@    for return and world changes.
@ 4.TrustedCore execute secure world init and rtock run successfully.
@ 5.TrustedCore switch to normal world(Normal_CONTEXT_ENTRY loaded).
@ 6.Fastboot execute in Normal World(non-secure DDR runing environment)
@   and boot linux kernel and Android.
@
@ As above,when comeinto TrustedCore.The first thing is build
@ the normal world context using the secure world context.
@ Make sure the normal world context is same to secure world context.
@ When TrustedCore switch to normal world(First time execute SMC), the
@ normal world context can be loaded.
@==================================================================
/*l00209118 add for world switch*/
/*<DTS2013030100725 y00201671 20130305 begin*/
    push    {r0-r1}

    /*Build return address of normal world and store it to N_PC*/
    mov    r0, lr
    ldr    r1, =N_PC
    str    r0, [r1]

    /*Build CPSR of normal world and store it to N_CPSR*/
    mrs    r0, cpsr
    ldr    r1, =N_CPSR
    str    r0, [r1]

    pop    {r0-r1}

    /*Build normal world context(Normal_CONTEXT_ENTRY) using the secure world context.
     *While SaveState execute in supervisor mode, SP and LR are corrupt.
     *Then the stored sp(N_SVC_R13) and lr(N_SVC_R14) is not correct
     */
    mov    lr, sp			@Backup sp
    ldr    sp, =Normal_CONTEXT_ENTRY    @Start address for non-secure context save.
    SaveState
    cps    #0x13                        @Change to supervisor mode(When SaveState executed, CPU is in Monitor mode)
    mov    sp, lr                       @Restore sp

    /*Modify the svc LR and SP to the correct value*/
    ldr	  r0, =N_SVC_R13
    str	  sp, [r0]                     @Build normal world svc SP and store it to N_SVC_R13
    ldr   r0, =N_SVC_R14
    ldr   r1, =N_PC
    ldr   r1, [r1]
    str   r1, [r0]                     @Build normal world svc LR and store it to N_SVC_R14
/*DTS2013030100725 y00201671 20130305 end>*/

    LDR   r0, =monitor_Vectors          @Install monitor's vector table
    MCR   p15, 0, r0, c12, c0, 1        @Write Monitor Vector Base Address Register

/*l00209118 end*/

    @IF      {ENDIAN} = "big"
    @SETEND  BE
    @ENDIF

    @MRC     p15, 0, r0, c1, c0, 0       @ read CP15 register 1
    @BIC     r0, r0, #0x1                @ clear bit 0

    @IF      {ENDIAN} = "big"
    @ORR     r0, r0, #0x2000000
    @ENDIF

    @MCR     p15, 0, r0, c1, c0, 0       @ write value back

    @.extern  Image$$ARM_LIB_SYS_STACKHEAP$$ZI$$Limit
    @CPSID  aif, #SYS_MODE
    @LDR     SP, =Image$$ARM_LIB_SYS_STACKHEAP$$ZI$$Limit

    CPSID  aif, #IRQ_MODE
    LDR     SP, =ARM_LIB_IRQ_STACKHEAP

    CPSID  aif, #ABT_MODE
    LDR     SP, =ARM_LIB_ABT_STACKHEAP

    CPSID  aif, #UND_MODE
    LDR     SP, =ARM_LIB_UND_STACKHEAP

    CPSID  aif, #FIQ_MODE
    LDR     SP, =ARM_LIB_FIQ_STACKHEAP

    CPSID  aif, #MON_MODE
    LDR     SP, =ARM_LIB_MON_STACKHEAP

    CPSID    aif, #SVC_MODE
	LDR     SP, =ARM_LIB_STACKHEAP

@==================================================================
@ reloc vectors
@==================================================================

    LDR     r0, =osRelocVector
    MCR     p15, 0, r0, c12, c0, 0






@==================================================================
@ setup page table
@==================================================================

	bl   cpu_init

@no need NEON and VFP, delete
#if 0
@==================================================================
@ Enable access to NEON/VFP by enabling access to Coprocessors 10 and 11.
@ Enables Full Access i.e. in both priv and non priv modes
@==================================================================
    MRC     p15, 0, r0, c1, c0, 2      @ read CP access register
    ORR     r0, r0, #(0x3  <<20)       @ enable access CP 10
    ORR     r0, r0, #(0x3  <<22)       @ enable access CP 11
    MCR     p15, 0, r0, c1, c0, 2      @ write CP access register back

@=================================================================
@ Switch on the VFP and NEON Hardware
@=================================================================
    MOV     r0, #0                      @ Set up a register
    ORR     r0, r0, #(0x1 << 30)
    @@@@@@@@@@@@@@@@@@VMSR    FPEXC, r0                   @ Write FPEXC register, EN bit set
#endif

@=================================================================
@ master core start here
@=================================================================
    @ ------ enable SCU ----------------
    MRC     p15, 4, r0, c15, c0, 0  @ Read periph base address
    LDR     r1, [r0, #0x0]          @ Read the SCU Control Register
    ORR     r1, r1, #0x1            @ Set bit 0 (The Enable bit)
    STR     r1, [r0, #0x0]          @ Write back modifed value

    @ ------ secure SCU invalidate -------
    MRC     p15, 0, r0, c0, c0, 5     @ Read CPU ID register
    ANDS    r0, r0, #0x03             @ Mask off, leaving the CPU ID field
    MOV     r1, #0xF                  @ Move 0xF (represents all four ways) into r1
    BL      secure_SCU_invalidate

    @ ------ join smp  -------
    @MRC     p15, 0, r0, c1, c0, 1   @ Read ACTLR
    @ORR     r0, r0, #0x041          @ Set bit 6
    @MCR     p15, 0, r0, c1, c0, 1   @ Write ACTLR

#ifdef STB_CIPHER_DRIVER
    @ ------ set NSACR  -------
    /* l00209118 add for set NSACR*/
    ldr     r0,=0x00070c00           @Bit 10:unsecure access cp10       Bit 11:unsecure access cp11
    mcr     p15, 0, r0, c1, c1, 2    @Bit 16:PLE unsecure access bit    Bit 17:TLB can be allocated    Bit 18:non_secure can access actlr smp bit
    /*l00209118  end */

    @ ------ set ACTLR  -------
    /* l00202565 add for enable actlr  FW bit */
    mrc     p15, 0, r0, c1, c0, 1
    orr     r0, #0x1
    mcr     p15, 0, r0, c1, c0, 1
    /* l00202565 end*/
#endif

    @B .

    @ ------ data section copy
    /*no need to copy*/
/*
    ldr r0, = TEXT_END
    ldr r1, = g_uwSwCodeStart
    ldr r1, [r1]
    sub r0, r0, r1
    ldr r1, = SECURE_IMG_DDR_ADDR      @img addr

    add r1, r1, r0            @r1,img data section start addr
    ldr r0, = DATA_START      @r0, elf data section start addr
    ldr r2, = DATA_END

copy_data_section:
      LDMIA           r1!, {r4-r7}
      STMIA           r0!, {r4-r7}
      CMP             r0, r2
      BLO             copy_data_section
*/
    /*h00206996 add  ------ copy secmonitor code to sram*/
    ldr r1, = _sram_start          @src
    ldr r0, = SEC_MONITOR_START
    ldr r2, = SEC_MONITOR_END
copy_secmonitor:
    LDMIA           r1!, {r4-r7}
    STMIA           r0!, {r4-r7}
    CMP             r0, r2
    BLO             copy_secmonitor
    /*h00206996 end*/

    @ ------ bss  bss section init
    ldr  r0, = BSS_START
    ldr  r1, = BSS_END
    mov r2, #0
memset_bss:
    str r2, [r0]
    add r0, r0, #0x4
    cmp r0, r1
    blo memset_bss

    ldr  r0, = SHARED_BSS_START
    ldr  r1, = SHARED_BSS_END
memset_shared_bss:
    str r2, [r0]
    add r0, r0, #0x4
    cmp r0, r1
    blo memset_shared_bss

/* DTS: l00202565 add for secure uart init begin */
    ldr r0, =secure_uart_enable
#ifdef DEBUG_EXTERN
    ldr r1, =0x1
    str r1, [r0]
#else
    ldr r1, =0x0
    str r1, [r0]
#endif
/* DTS: l00202565 add for secure uart init begin */

    /* DTS: for rtosck test suite task config, l00202565 add begin */
    ldr r0, = 0x0
#ifdef TESTSUITE_RTOSck_UT
    ldr r0, = osTestInit
#endif
    /* DTS: for rtosck test suite task config, l00202565 add end */
    ldr r1, =TASK_ADDR
    BL  main

secure_SCU_invalidate:
  AND     r0, r0, #0x03           @ Mask off unused bits of CPU ID
  MOV     r0, r0, LSL #2          @ Convert into bit offset (four bits per core)

  AND     r1, r1, #0x0F           @ Mask off unused bits of ways
  MOV     r1, r1, LSL r0          @ Shift ways into the correct CPU field

  MRC     p15, 4, r2, c15, c0, 0  @ Read periph base address

  STR     r1, [r2, #0x0C]         @ Write to SCU Invalidate All in Secure State

  BX      lr


cpu_init :
    push {r1, lr}
@Disable MMU
    mrc p15, 0, r1, c1, c0, 0       @Read Configuration Register
    bic r1, r1, #0x1
    mcr p15, 0, r1, c1, c0, 0       @Write Configuration Register

@Disable L1 Caches
    mrc p15, 0, r1, c1, c0, 0
    bic r1, r1, #(0x1 << 12)    @Disable I cache
    bic r1, r1, #(0x1 << 2)     @Disable D cache
    mcr p15, 0, r1, c1, c0, 0

@Invalidate Instruction cache
    mov R1,#0
    mcr p15, 0, r1, c7, c5, 0

@Invalidate Data caches
    bl SRE_DCacheInvAll

@Invalidate Branch predictor arrays
    mov r1,#0
    mcr     p15, 0, r1, c7, c5,  6

@Invalidate TLBs
    mov r1, #0x0
    mcr p15, 0, r1, c8, c3, 0

    mrc     p15, 0, r1, c1, c0, 0        @Read SCTLR
    bic     r1, r1, #0x10000000
    bic     r1, r1, #0x00002000
    mcr     p15, 0, r1, c1, c0, 0

    @NSACR configuration
    mrc     p15, 0, r1, c1, c1, 2        @Read Non-Secure Access Control Register
    ldr     r2, =NSACR_REG_VAL
    orr     r1, r1, r2
    mcr     p15, 0, r1, c1, c1, 2

    @set this in monitor mode, delelte
#if 0
    @Set the FIQ bit so as to route FIQs to monitor mode
    mrc     p15, 0, r1, c1, c1, 0        @Read Secure Configuration Register data
    ldr     r2, =SCR_FIQ_BIT
    orr     r1, r1, r2
    mcr     p15, 0, r1, c1, c1, 0        @Write Secure Configuration Register data
#endif

    pop {r1, lr}
    bx lr

