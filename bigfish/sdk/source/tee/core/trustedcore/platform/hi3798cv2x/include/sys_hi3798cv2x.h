#ifndef __SYS_K3V3_H__
#define __SYS_K3V3_H__

#define REG_BASE_SCTRL          (0xF8000000)       //SCTRL
#define REG_BASE_PERI_CRG       (0xF8A20000)       //PERI_CRG


#define SCCTRL	               (REG_BASE_SCTRL + 0x000)
#define SCSYSSTAT	           (REG_BASE_SCTRL + 0x004)

#if 1 /* TODO: Not support */
/*used in NMI watchdog to save ctx*/
/* DUMP_DDR is virt of 0x1df000000     */
#define DUMP_DDR                    (0x9FE00000)
#define STORE_OFFSET_UNIT           0x200
#define SAVE_CTX_OFFSET             68
#endif

#endif /*__SYS_K3V3_H__ */
