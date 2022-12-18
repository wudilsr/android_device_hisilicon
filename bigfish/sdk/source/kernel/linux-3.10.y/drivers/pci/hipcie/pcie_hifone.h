#ifndef __HISI_PCIE_H__
#define __HISI_PCIE_H__
#define PCIe1_CONFIG
#undef PCIE0_LOCAL_LOOPBACK_EN
#undef PCIE0_REMOTE_LOOPBACK_EN
#undef PCIE1_LOCAL_LOOPBACK_EN
#undef PCIE1_REMOTE_LOOPBACK_EN
#define PCIE0_SYS_BASE_PHYS	0xF9860000
#define PCIE0_BASE_ADDR_PHYS	0xE0000000
#define PCIE0_MEMIO_BASE	0xE4000000
#define PCIE_BASE_ADDR_SIZE	0x04000000
#define DBI_BASE_ADDR_0         0xF0000000

#define PCIE1_SYS_BASE_PHYS	0xF9861000
#define PCIE1_BASE_ADDR_PHYS	0xE8000000
#define PCIE1_MEMIO_BASE	0xEC000000
#define DBI_BASE_ADDR_1         0xF0002000

#define PERI_CTRL      (void __iomem *)IO_ADDRESS(0xF8A20008)
#define pcie_usb3_sata3_sel_combphy3 (0x3<<14)//00 PCIE,01 USB3.0,10 SATA
#define sata1_pwren (1<<13)
#define sata0_pwren (1<<10)
#define pcie_usb3_sata3_sel_combphy1 (0x3<<11)//00 PCIE,01 USB3.0,10 SATA

#define PERI_COMBPHY1_CFG (void __iomem *)IO_ADDRESS(0xF8A20858)
#define PERI_COMBPHY3_CFG (void __iomem *)IO_ADDRESS(0xF8A20868)
#define nano_bypass_codec 1<<31
#define bypass_pciectrl_analog 1<<30 
#define nano_buffer_mode 0x3<<28
#define nano_test_write 1<<24
#define nano_test_data 0xf<<20
#define nano_test_addr 0x1f<<12
#define nano_rx_standby 1<<11
#define nano_tx_margin 0x7<<8
#define nano_tx_deemp 0x3<<5
#define nano_tx_swing 1<<4
#define nano_tx_pattern 0x3<<2
#define clkref_out_ien 1<<1
#define clkref_out_oen 1<<0

#define PERI_COMBPHY1_STATE (void __iomem *)IO_ADDRESS(0xF8A2085C)
#define PERI_COMBPHY3_STATE (void __iomem *)IO_ADDRESS(0xF8A2086C)
#define nano_test_o 0xf<<8
#define nano_data_bus_width 0x3<<4
#define nano_rx_data_valid 1<<2
#define nano_rx_standby_status 1<<1
#define nano_align_detect 1<<0

#define CRG_BASE	(void __iomem *)IO_ADDRESS(0xF8A22000)
#define PERI_CRG98      0x188
 //pcie1
#define combphy3_rstn_sel_ctrl (1<<29)
#define combphy3_srst_req (1<<28)
#define combphy3_refclk_sel (0x7<<25)//BPLL/EPLL/FPLL:000/010/100 100MHz,001/011/101 25MHz
#define combphy3_ref_cken (1<<24)
//pcie0
#define combphy1_rstn_sel_ctrl (1<<13)
#define combphy1_srst_req (1<<12)
#define combphy1_refclk_sel (0x7<<9)//BPLL/EPLL/FPLL:000/010/100 100MHz,001/011/101 25MHz
#define combphy1_ref_cken (1<<8)
 
#define PERI_CRG99      0x18c
#define pcie0_bus_cken		0
#define pcie0_sys_cken       1
#define pcie0_pipe_cken       2
#define pcie0_aux_cken		3
#define pcie0_bus_srst_req	4
#define pcie0_sys_srst_req	5
#define pcie0_srst_req	6

#define pcie1_bus_cken 8
#define pcie1_sys_cken 9
#define pcie1_pipe_cken 10
#define pcie1_aux_cken 11
#define pcie1_bus_srst_req 12
#define pcie1_sys_srst_req 13
#define pcie1_srst_req 14

#define PCIE_SYS_CTRL0		0x0000
#define pcie_slv_device_type	28
#define PCIE_WM_EP		0x0
#define PCIE_WM_LEGACY		0x1
#define PCIE_WM_RC		0x4


#define PCIE_SYS_CTRL1		0x0004
#define pcie_bit_reg_dev_ctrl   21

#define PCIE_SYS_CTRL7		0x001C
#define pcie0_app_ltssm_enable	11

#define PCIE_SYS_STAT0          0x0100
#define PCIE_SYS_STAT4          0x0110
#define pcie0_xmlh_link_up	15
#define pcie0_rdlh_link_up	5

#define IRQ_BASE		32

#define PCIE0_IRQ_INTA          (IRQ_BASE + 131)
#define PCIE0_IRQ_INTB          (IRQ_BASE + 131)
#define PCIE0_IRQ_INTC          (IRQ_BASE + 131)
#define PCIE0_IRQ_INTD          (IRQ_BASE + 131)
#define PCIE0_IRQ_PM	(IRQ_BASE + 130)
#define PCIE0_IRQ_MSI		(IRQ_BASE + 128)
#define PCIE0_IRQ_LINK_DOWN	(IRQ_BASE + 129)

#define PCIE1_IRQ_INTA          (IRQ_BASE + 135)
#define PCIE1_IRQ_INTB          (IRQ_BASE + 135)
#define PCIE1_IRQ_INTC          (IRQ_BASE + 135)
#define PCIE1_IRQ_INTD          (IRQ_BASE + 135)
#define PCIE1_IRQ_PM	(IRQ_BASE + 134)
#define PCIE1_IRQ_MSI		(IRQ_BASE + 132)
#define PCIE1_IRQ_LINK_DOWN	(IRQ_BASE + 133)

#define PCIE_INTA_PIN		1
#define PCIE_INTB_PIN		2
#define PCIE_INTC_PIN		3
#define PCIE_INTD_PIN		4

#endif
