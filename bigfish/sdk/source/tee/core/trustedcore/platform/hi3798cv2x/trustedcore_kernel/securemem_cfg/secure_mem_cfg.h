#ifndef _SECURE_MEM_CFG_H_
#define _SECURE_MEM_CFG_H_

#include "stdint.h"

/* TZASC */
#define MAX_REGIONS                             16

#define TZASC_BASE_ADDR                   (0xf8a31000)


#define SEC_CONFIG                       (TZASC_BASE_ADDR + 0x00)
#define SEC_BYPASS                       (TZASC_BASE_ADDR + 0x04)
#define SEC_LOCKDOWN_SEL                 (TZASC_BASE_ADDR + 0x10)
#define SEC_INT_EN                       (TZASC_BASE_ADDR + 0x20)
#define SEC_INT_STATUS                   (TZASC_BASE_ADDR + 0x24)
#define SEC_INT_CLEAR                    (TZASC_BASE_ADDR + 0x28)
#define SEC_FAIL_ADDRESS_LOW             (TZASC_BASE_ADDR + 0x80)
#define SEC_FAIL_STATUS                  (TZASC_BASE_ADDR + 0x84)
#define SEC_FAIL_ID                      (TZASC_BASE_ADDR + 0x88)

#define SEC_RGN_MAP(x)                   (TZASC_BASE_ADDR + 0x100 + 0x10 * (x))
#define SET_RGN_ATTR(x)                  (TZASC_BASE_ADDR + 0x104 + 0x10 * (x))
#define SET_RGN_MID_W(x)                 (TZASC_BASE_ADDR + 0x108 + 0x10 * (x))
#define SET_RGN_MID_R(x)                 (TZASC_BASE_ADDR + 0x10C + 0x10 * (x))

#define SEC_SHARE_RGN_EN                 (TZASC_BASE_ADDR + 0x300)
#define SEC_SHARE_RGN_START              (TZASC_BASE_ADDR + 0x304)
#define SEC_SHARE_RGN_END                (TZASC_BASE_ADDR + 0x308)
#define SEC_MASTER_TYPE_SHARE            (TZASC_BASE_ADDR + 0x30C)
#define SEC_MASTER_TYPE_RSV              (TZASC_BASE_ADDR + 0x310)
#define SEC_SHARE_RGN_FAIL_CMD_STATUS    (TZASC_BASE_ADDR + 0x314)
#define SEC_SHARE_RGN_FAIL_CMD_ADDR      (TZASC_BASE_ADDR + 0x318)
#define SEC_SHARE_RGN_FAIL_ID            (TZASC_BASE_ADDR + 0x31C)

//TZPC
#define TZPC_BASE_ADDR                          (0xf8a80000)

#define TZMA_ROSIZE_REG                        	(TZPC_BASE_ADDR + 0x00)
#define TZASC_RST_REG                          	(TZPC_BASE_ADDR + 0x04)
#define TZASC_SEC_LOCK_REG                      (TZPC_BASE_ADDR + 0x08)
#define CPU_DBG_CTRL_REG                        (TZPC_BASE_ADDR + 0x0c)
#define SEC_ATTR_CTRL_0_REG                     (TZPC_BASE_ADDR + 0x10)
#define SEC_MISC_CTRL_REG                       (TZPC_BASE_ADDR + 0x1c)
#define SEC_DDRC_CTRL_REG                       (TZPC_BASE_ADDR + 0x24)

#define _SEC_NR_RGNS_SHIFT                  (0)
#define _SEC_NR_RGNS_BITS                   (8)
#define _SEC_BYPASS_SHIFT                   (0)
#define _SEC_BYPASS_BITS                    (4)
#define _SEC_INT_EN_SHIFT                   (0)
#define _SEC_INT_EN_BITS                    (1)
#define _SEC_INT_OVERRUN_SHIFT              (1)
#define _SEC_INT_OVERRUN_BITS               (1)
#define _SEC_INT_STATUS_SHIFT               (0)
#define _SEC_INT_STATUS_BITS                (1)
#define _SEC_FAIL_CMD_ADDR_LOW_SHIFT        (0)
#define _SEC_FAIL_CMD_ADDR_BITS             (32)
#define _SEC_FAIL_CMD_ACC_TYPE_SHIFT        (20)
#define _SEC_FAIL_CMD_ACC_TYPE_BITS         (1)
#define _SEC_FAIL_CMD_NS_SHIFT              (17)
#define _SEC_FAIL_CMD_NS_BITS               (1)
#define _SEC_FAIL_CMD_PRVLG_SHIFT           (16)
#define _SEC_FAIL_CMD_PRVLG_BITS            (1)
#define _SEC_FAIL_CMD_ADDR_HIGH_SHIFT       (0)
#define _SEC_FAIL_CMD_ADDR_HIGH_BITS        (8)
#define _SEC_FAIL_CMD_MID_SHIFT             (24)
#define _SEC_FAIL_CMD_MID_BITS              (8)
#define _SEC_FAIL_CMD_ID_SHIFT              (0)
#define _SEC_FAIL_CMD_ID_BITS               (24)
#define _SEC_RGN_BASE_ADDR_SHIFT            (0)
#define _SEC_RGN_BASE_ADDR_BITS             (24)
#define _SEC_RGN_SIZE_SHIFT                 (24)
#define _SEC_RGN_SIZE_BITS                  (6)
#define _SEC_RGN_EN_SHIFT                   (31)
#define _SEC_RGN_EN_BITS                    (1)
#define _SEC_RGN_SP_SHIFT                   (0)
#define _SEC_RGN_SP_BITS                    (4)
#define _SEC_RGN_SEC_INV_SHIFT              (4)
#define _SEC_RGN_SEC_INV_BITS               (1)
#define _SEC_RGN_MID_EN_SHIFT               (8)
#define _SEC_RGN_MID_EN_BITS                (1)
#define _SEC_RGN_MID_INV_SHIFT              (9)
#define _SEC_RGN_MID_INV_BITS               (1)
#define _SEC_SUBRGN_EN_SHIFT                (16)
#define _SEC_SUBRGN_EN_BITS                 (16)
#define _SEC_MID_CPU_SHIFT                  (0)
#define _SEC_MID_CPU_BITS                   (1)
#define _SEC_MID_DDRT_SHIFT                 (9)
#define _SEC_MID_DDRT_BITS                  (1)
#define _SEC_MID_SHA_SEC_SHIFT		        (3)
#define _SEC_MID_CIPHER_SHIFT		        (5)
#define _SEC_MID_CIPHER_BITS		        (1)
#define _SEC_MID_PASTC_SHIFT                (23)
#define _SEC_MID_PASTC_BITS                 (1)
#define _SEC_SHARE_RGN_EN_SHIFT             (0)
#define _SEC_SHARE_RGN_EN_BITS              (1)
#define _SEC_SHARE_RGN_START_SHIFT          (0)
#define _SEC_SHARE_RGN_START_BITS           (32)
#define _SEC_SHARE_RGN_END_SHIFT            (0)
#define _SEC_SHARE_RGN_END_BITS             (32)
#define _SEC_SHARE_RGN_FAIL_STATUS_SHIFT    (0)
#define _SEC_SHARE_RGN_FAIL_STATUS_BITS     (1)
#define _SEC_SHARE_RGN_FAIL_ADDR_SHIFT      (0)
#define _SEC_SHARE_RGN_FAIL_ADDR_BITS       (32)
#define _SEC_SHARE_RGN_FAIL_CMDID_SHIFT     (0)
#define _SEC_SHARE_RGN_FAIL_CMDID_BITS      (9)
#define _SEC_SHARE_RGN_FAIL_MID_SHIFT       (12)
#define _SEC_SHARE_RGN_FAIL_MID_BITS        (5)

#define _SEC_BOOT_LOCK_SHIFT                (0)
#define _SEC_BOOT_LOCK_BITS                 (1)
#define _SEC_ERR_RESP_SHIFT                 (0)
#define _SEC_ERR_RESP_BITS                  (1)

/* RNG register */
#define RNG_REG_BASE                		(0xF8005200)
#define SC_RNG_DATA_CTRL            		(RNG_REG_BASE + 0x0)
#define SC_RNG_DATA_CNT             		(RNG_REG_BASE + 0x8)
#define SC_RNG_DATA_VAL             		(RNG_REG_BASE + 0x4)

/* system reset register */
#define SC_SYSRES_REG                		(0xF8000004)

#define DDR_SIZE_MIN  (256 * 1024 * 1024)

#define BITS_MASK(nbits)			((1<<nbits)-1)
#define GET_BITS_SHIFT(x, nbits, nshift)	(((x)>>nshift)&BITS_MASK(nbits))
#define BITS_SHIFT_MASK(nbits, nshift)		(BITS_MASK(nbits)<<nshift)
#define BITS_SHIFT_VAL(x, nbits, nshift)	(((x)&BITS_MASK(nbits))<<nshift)

/* Lock qosbuf/axiif/rbc/phy/dmc */
#define _SEC_DDRC_LOCK_CFG     ((1UL<<0) | (1UL<<1) | (1UL<<2) | (1UL<<3) | (1UL<<4))

#define _SEC_LOCKDOWN_SEL_CFG  (0xFF1F1F)

#define NONE_RIGHT                              0x0
#define NON_SECURE_RIGHT                        0xB
#define SECURE_RIGHT                            0xc
#define FULL_RIGHT                              0xf

#define SEC_TZASC_ERR_IRQ                       (110)  /* AXI_SEC_INT */

#define _RGN_ALIGN_SHIFT                        (16)
#define _RGN_ALIGN                              (1<<_RGN_ALIGN_SHIFT) //region size and addr should be aligned with 64KB
#define MAX_DDR_LEN                             0x100000000ULL

#define sec_mem_printf(format, arg...)          uart_printf_func(" [SecMem]: " format, ##arg)

#define sec_mem_dsb()                    __asm__ __volatile__ ("dsb" : : : "memory")

#undef SEC_MEM_REG_TRACE
#undef SEC_MEM_DEBUG
#undef SEC_MEM_SELFTEST

#ifdef SEC_MEM_REG_TRACE
#define sec_mem_readl(addr)             ({ u32 __v = (*(volatile uint32_t *)(addr)); sec_mem_dsb(); sec_mem_printf("read %p = 0x%X\n", (uint32_t *)(addr), __v);__v; })
#define sec_mem_writel(val, addr)       ({ sec_mem_dsb(); sec_mem_printf("write %p = 0x%X\n", (uint32_t *)(addr), val); ((*(volatile uint32_t *)(addr)) = (val)); sec_mem_dsb();})
#else
#define sec_mem_readl(addr)             ({ u32 __v = (*(volatile uint32_t *)(addr)); sec_mem_dsb(); __v; })
#define sec_mem_writel(val, addr)       ({ sec_mem_dsb(); ((*(volatile uint32_t *)(addr)) = (val)); sec_mem_dsb();})
#endif

#ifdef  SEC_MEM_DEBUG
#define sec_mem_dbginfo(format, arg...)        sec_mem_printf( "%s,%d: " format , __FUNCTION__, __LINE__, ##arg)
#else
#define sec_mem_dbginfo(format, arg...)
#endif

struct tzascregion {
	int en;
	uint64_t base;
	uint64_t size;
	uint32_t sp;
	uint32_t mid_en;
	uint32_t mid_w;
	uint32_t mid_r;
};

struct tzasc_share_region {
	int en;
	uint64_t base;
	uint64_t size;
	uint32_t master_type0;
//	uint32_t master_type1;
};


int sys_security_config(void);
void random_delay(void);
void sec_sys_reset(void);
unsigned int sec_get_rng(unsigned int *num);
extern void v7_dma_flush_range(unsigned long start, unsigned long end);
#endif /* _SECURE_MEM_CFG_H_ */
