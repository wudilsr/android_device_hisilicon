#include <stdarg.h>
#include "sre_base.h"
#include "sre_mem.h"
#include "sre_config.h"
#include "sre_sys.h"
#include "sre_buildef.h"
#include "sre_exc.h"
#include "sre_msg.h"


typedef struct {
    UINT32 SPSR;
    UINT32 R13;
    UINT32 R14;
} other_mode_regs_t;

typedef struct {
    UINT32 SCR; //fix
    UINT32 ISR;
    UINT32 MVBAR;
    UINT32 NSACR;
    UINT32 SDER;
    UINT32 VBAR;
} cp15_regs_t;

typedef struct {
    UINT32 PC;
    UINT32 CPSR;
    cp15_regs_t CP15_REGS;
    UINT32 USR_REG[15];
    other_mode_regs_t IRQ_REG;
    other_mode_regs_t SVC_REG;
    other_mode_regs_t ABT_REG;
    other_mode_regs_t UND_REG;
    UINT32 FIQ_SPSR;
    UINT32 FIQ_REG[7];
} regs_t;

regs_t all_regs;
UINT32* all_regs_entry = &(all_regs.IRQ_REG);

VOID osuart_show_regs(regs_t *d_regs)
{
    int i;
    uart_printf("&&&&&&&&&&&&&&&&&&&&&[Begin]&&&&&&&&&&&&&&&&&&&&&&&&\n");
    uart_printf("CP15::SCR: %x, ISR :%x\n", d_regs->CP15_REGS.SCR, d_regs->CP15_REGS.ISR);
    uart_printf("CP15::MVBAR: %x, NSACR :%x\n", d_regs->CP15_REGS.MVBAR, d_regs->CP15_REGS.NSACR);
    uart_printf("CP15::SDER: %x, VBAR :%x\n", d_regs->CP15_REGS.SDER, d_regs->CP15_REGS.VBAR);

    uart_printf("PC: %x, CPSR: %x\n", d_regs->PC, d_regs->CPSR);
    for (i=0;i<15;i++)
        uart_printf("USR reg%d: %x\n", i, d_regs->USR_REG[i]);

    uart_printf("IRQ--SPSR: %x, R13: %x, R14: %x\n",
                d_regs->IRQ_REG.SPSR, d_regs->IRQ_REG.R13, d_regs->IRQ_REG.R14);
    uart_printf("SVC--SPSR: %x, R13: %x, R14: %x\n",
                d_regs->SVC_REG.SPSR, d_regs->SVC_REG.R13, d_regs->SVC_REG.R14);
    uart_printf("ABT--SPSR: %x, R13: %x, R14: %x\n",
                d_regs->ABT_REG.SPSR, d_regs->ABT_REG.R13, d_regs->ABT_REG.R14);
    uart_printf("UND--SPSR: %x, R13: %x, R14: %x\n",
                d_regs->UND_REG.SPSR, d_regs->UND_REG.R13, d_regs->UND_REG.R14);

    uart_printf("FIQ--SPSR: %x\n", d_regs->FIQ_SPSR);

    for (i=0;i<7;i++)
        uart_printf("FIQ reg%d: %x\n", i+8, d_regs->FIQ_REG[i]);

    uart_printf("&&&&&&&&&&&&&&&&&&&&&[End]&&&&&&&&&&&&&&&&&&&&&&&&\n");
}
