
    .include "sre_asm_macro.ph"
    .global show_regs
    .extern osuart_show_regs
    .extern all_regs_entry
    .extern all_regs

show_regs:

    push {r0-r8}
    ldr r0, =all_regs
    mrc p15, 0, r3, c1, c1, 0
    mov r4, #0x2
    mcr p15, 0, r4, c1, c1, 0
    mov r1, lr
    mrs r2, cpsr
    stmia r0!, {r1-r3}
    /*other cp15 regs*/
    mrc p15, 0, r1, c12, c1, 0
    mrc p15, 0, r2, c12, c0, 1
    mrc p15, 0, r3, c1, c1, 2
    mrc p15, 0, r4, c1, c1, 1
    mrc p15, 0, r5, c12, c0, 0

    stmia r0!, {r1-r5}

    pop {r0-r8}
    mov lr, sp
    ldr sp, =all_regs_entry
    ldr sp, [sp]
    SaveState
    mov sp, lr

    ldr r0, =all_regs
    bl osuart_show_regs

    mov lr, sp
    ldr sp, =all_regs_entry
    ldr sp, [sp]
    LoadState
    mov sp, lr

    push {r0-r3}
    ldr r0, =all_regs

    ldmia r0!, {r1-r3}


    mcr p15, 0, r3, c1, c1, 0
    msr cpsr_cxsf, r2

    mov lr, r1
    pop {r0-r3}
    mov pc, lr
