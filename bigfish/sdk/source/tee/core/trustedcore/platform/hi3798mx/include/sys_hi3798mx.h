#ifndef __SYS_HI3798MX_H__
#define __SYS_HI3798MX_H__


#define REG_BASE_SCTRL          (0xF8000000)       //SCTRL
#define REG_BASE_PERI_CRG       (0xF8A20000)       //PERI_CRG

#if 0
#ifndef CONFIG_RDR_MEM_ADDR
#define CONFIG_RDR_MEM_ADDR     (0x2000000)
#endif
#ifdef CONFIG_RDR_MEM_ADDR           /* TODO: XXX */
#define RDR_MEM_ADDR                (CONFIG_RDR_MEM_ADDR)
#define RDR_MEM_SIZE                (0x600000)
#define EXCEPT_CORE_ADDR            (64)
#define EXCEPT_REASON_ADDR          (68)
#define EXCEPT_CORE_VALUE           0x01000000
#define EXCEPT_REASON_VALUE         0x00000003
#endif
#endif

#ifndef CONFIG_DUMP_DDR
//#define CONFIG_DUMP_DDR             (0x2A800000)
//by fangjian:for 4k
#define CONFIG_DUMP_DDR             (0x9FE00000)
#endif

#ifdef CONFIG_DUMP_DDR              /* TODO: XXX */
/*used in NMI watchdog to save ctx*/
#define DUMP_DDR                    CONFIG_DUMP_DDR
#define STORE_OFFSET_UNIT           0x200
#define SAVE_CTX_OFFSET             68
#endif

#endif /*__SYS_HI3798MX_H__ */
