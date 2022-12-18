
.equ CPSR_MODE_USR,                    0x10
.equ CPSR_MODE_FIQ,                      0x11
.equ CPSR_MODE_IRQ,                       0x12
.equ CPSR_MODE_SVC,                       0x13
.equ CPSR_MODE_MON,                        0x16
.equ CPSR_MODE_ABT,                    0x17
.equ CPSR_MODE_UND,                     0x1b
.equ CPSR_MODE_SYS,                    0x1f


    .macro dcache_line_size  Rd, Rm
        mrc p15, 1, \Rm, c0, c0, 0
    and \Rm, \Rm, #7
    mov \Rd, #16
        mov \Rd, \Rd, lsl \Rm
    .endm

    .macro SWAP32  Rd, Rm
    NOP
    .endm

    .macro RTEV_SETEND
    NOP
    .endm

@MACRO: SaveState
@ Saves registers to the workspace r13 points into.
@ Registers r0-r3 are not corrupted.


    .macro SaveState
        stmdb   sp, {r0-r14}^         @Workspace_N_Begin,r0-r14 addr
        mov     r4, sp
        cps     #CPSR_MODE_IRQ
        mrs     r12, SPSR
        stmia   r4!, {r12-r14}
        cps     #CPSR_MODE_SVC
        mrs     r12, SPSR
        stmia   r4!, {r12-r14}
        cps     #CPSR_MODE_ABT
        mrs     r12, SPSR
        stmia   r4!, {r12-r14}
        cps     #CPSR_MODE_UND
        mrs     r12, SPSR
        stmia   r4!, {r12-r14}
        cps     #CPSR_MODE_FIQ
        mrs     r7, SPSR
        stmia   r4, {r7-r14}
        cps     #CPSR_MODE_MON
    .endm

@MACRO: LoadState, Loads registers from the workspace r13 points into.


    .macro LoadState
        mov     r1, sp
        cps     #CPSR_MODE_IRQ
        ldmia   r1!, {r12-r14}
        msr     SPSR_fsxc, r12
        cps     #CPSR_MODE_SVC
        ldmia   r1!, {r12-r14}
        msr     SPSR_fsxc, r12
        cps     #CPSR_MODE_ABT
        ldmia   r1!, {r12-r14}
        msr     SPSR_fsxc, r12
        cps     #CPSR_MODE_UND
        ldmia   r1!, {r12-r14}
        msr     SPSR_fsxc, r12
        cps     #CPSR_MODE_FIQ
        ldmia   r1,  {r7-r14}
        msr     SPSR_fsxc, r7
        cps     #CPSR_MODE_MON
        ldmdb   sp, {r0-r14}^
    .endm

   .macro   SaveStateNoGp
       mov     r4, sp
       cps     #CPSR_MODE_IRQ
       mrs     r12, SPSR
       stmia   r4!, {r12-r14}
       cps     #CPSR_MODE_SVC
       mrs     r12, SPSR
       stmia   r4!, {r12-r14}
       cps     #CPSR_MODE_ABT
       mrs     r12, SPSR
       stmia   r4!, {r12-r14}
       cps     #CPSR_MODE_UND
       mrs     r12, SPSR
       stmia   r4!, {r12-r14}
       cps     #CPSR_MODE_FIQ
       mrs     r7, SPSR
       stmia   r4, {r7-r14}
       cps     #CPSR_MODE_MON
   .endm

@h00206996 modify, add debug macro SHOWREGS
@this macro can only be used in monitor.S
@enable uart print so you can see the output.

.ifdef MONITOR_TEST_DEF
   .macro SHOWREGS
          .extern show_regs
          push {lr}
          bl show_regs
          pop {lr}
   .endm
.else
    .macro SHOWREGS
    .endm
.endif

