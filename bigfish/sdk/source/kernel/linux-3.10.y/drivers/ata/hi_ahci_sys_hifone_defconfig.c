
#define PERI_CTRL	                     __io_address(0xF8A20008)
#define PCIE_USB3_SATA3_SEL_COMBPHY3        (0x3<<14)//00 PCIE,01 USB3.0,10 SATA
#define SATA1_PWREN (1<<13)
#define SATA0_PWREN (1<<10)

#define PERI_COMBPHY2_CFG                    __io_address(0xF8A20860)
#define PERI_COMBPHY3_CFG                    __io_address(0xF8A20868)
#define NANO_BYPASS_CODEC                    (0x1<<31)
#define BYPASS_PCIECTRL_ANALOG               (0x1<<30) //only in COMBOPHY3
#define NANO_BUFFER_MODE                     (0x3<<28)
#define NANO_TEST_WRITE                      (0x1<<24)
#define NANO_TEST_DATA                       (0xf<<20)
#define NANO_TEST_ADDR                       (0x1f<<12)
#define NANO_RX_STANDBY                      (0x1<<11)
#define NANO_TX_MARGIN                       (0x7<<8)//only in COMBOPHY3
#define NANO_TX_DEEMP                        (0x3<<5)//only in COMBOPHY3
#define NANO_TX_SWING                        (0x1<<4)//only in COMBOPHY3
#define NANO_TX_PATTERN                      (0x3<<2)

#define PERI_COMBPHY2_STATE                  __io_address(0xF8A20864)
#define PERI_COMBPHY3_STATE                  __io_address(0xF8A2086C)
#define NANO_TEST_O                          (0xf<<8)
#define NANO_DATA_BUS_WIDTH                  (0x3<<4)
#define NANO_RX_DATA_VALID                   (0x1<<2)
#define NANO_RX_STANDBY_STATUS               (0x1<<1)
#define NANO_ALIGN_DETECT                    (0x1<<0)

#define CRG_BASE                             __io_address(0xF8A22000)
#define PERI_CRG42                           0xA8
//port1
#define SATA1_SRST_REQ                       (1<<27)
#define SATA_RX1_SRST_REQ                    (1<<26)
#define SATA_TX1_CKEN                        (1<<19)
#define SATA_RX1_CKEN                        (1<<17)
//port0
#define SATA0_SRST_REQ                       (1<<11)
#define SATA_RX0_SRST_REQ                    (1<<10)
#define SATA_CKO_ALIVE_SRST_REQ              (1<<9)
#define SATA_BUS_SRST_REQ                    (1<<8)
#define SATA_TX0_CKEN                        (1<<3)
#define SATA_CKO_ALIVE_CKEN                  (1<<2)
#define SATA_RX0_CKEN                        (1<<1)
#define SATA_BUS_CKEN                        (1<<0)

#define PERI_CRG98                           0x188
//port1
#define COMBPHY3_RSTN_SEL_CTRL               (1<<29)
#define COMBPHY3_SRST_REQ                    (1<<28)
#define COMBPHY3_REFCLK_SEL                  (0x7<<25)//BPLL/EPLL/FPLL:000/010/100 100MHz,001/011/101 25MHz
#define COMBPHY3_REF_CKEN                    (1<<24)
//port0
#define COMBPHY2_RSTN_SEL_CTRL               (1<<21)
#define COMBPHY2_SRST_REQ                    (1<<20)
#define COMBPHY2_REFCLK_SEL                  (0x7<<17)//BPLL/EPLL/FPLL:000/010/100 100MHz,001/011/101 25MHz
#define COMBPHY2_REF_CKEN                    (1<<16)

#define HI_SATA_HOST_BASE                     __io_address(0xf9900000)
#define HI_SATA_PORT0_BASE                   (HI_SATA_HOST_BASE+0x100+0x80*0)
#define HI_SATA_PORT1_BASE                   (HI_SATA_HOST_BASE+0x100+0x80*1)

#define SATA_PORT_PHYCTL1                    0x48
#define TX_MARGIN                            (0x7<<4)
#define TX_DEEMPH                            (0x3<<2)
#define TX_SWING                             (1<<1)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon osdrv group");

u32 nano_reg_read(u32 nano_testread_addr,u32 comboPHY_num)
{
	unsigned int tmp_val;
	void __iomem *cfg_addr, *state_addr;

	if (2 == comboPHY_num) {
		cfg_addr=PERI_COMBPHY2_CFG;
		state_addr=PERI_COMBPHY2_STATE;
	}

	if (3==comboPHY_num) {
		cfg_addr=PERI_COMBPHY3_CFG;
		state_addr=PERI_COMBPHY3_STATE;
	}

	tmp_val=readl(cfg_addr);
	msleep(10);
	tmp_val &=~(NANO_TEST_WRITE);
	tmp_val &=~(NANO_TEST_ADDR);
	tmp_val |= (nano_testread_addr<<12);
 	writel(tmp_val,cfg_addr);
	msleep(10);
	tmp_val=readl(state_addr);
	msleep(10);
	tmp_val =(tmp_val&NANO_TEST_O)>>8;
//	printk("Nano ComboPHY(%s):addr(%#x),value(%#x)\n",__FUNCTION__,nano_testread_addr,tmp_val);
	return tmp_val;
}
void nano_reg_write(u32 nano_testwrite_addr,u32 nano_testwrite_value,u32 comboPHY_num)
{
	unsigned int tmp_val;
	void __iomem *cfg_addr, *state_addr;

	if(2 == comboPHY_num) {
		cfg_addr=PERI_COMBPHY2_CFG;
		state_addr=PERI_COMBPHY2_STATE;
	}

	if(3 == comboPHY_num) {
		cfg_addr=PERI_COMBPHY3_CFG;
		state_addr=PERI_COMBPHY3_STATE;
	}

	tmp_val=readl(cfg_addr);
	msleep(10);
	tmp_val &=~(NANO_TEST_ADDR);
	tmp_val &=~(NANO_TEST_DATA);
	tmp_val |=(nano_testwrite_addr<<12);
	tmp_val |=(nano_testwrite_value<<20);
	writel(tmp_val, cfg_addr);
	msleep(10);
	
	tmp_val=readl(cfg_addr);
	tmp_val |=NANO_TEST_WRITE;
	writel(tmp_val,cfg_addr);
	msleep(10);
//	printk("Nano ComboPHY(%s):addr(%#x),value(%#x)\n",__FUNCTION__,nano_testwrite_addr,nano_testwrite_value);
	tmp_val=readl(cfg_addr);
	tmp_val &=~(NANO_TEST_WRITE);
	writel(tmp_val,cfg_addr);
	msleep(10);tmp_val=readl(cfg_addr);
}

void nano_tx_margin_sata(u32 margin_value,u32 port_num)
{
	unsigned int tmp_val;
	void __iomem *port_addr;

	if(0==port_num)
		port_addr=HI_SATA_PORT0_BASE;
	if(1==port_num)
		port_addr=HI_SATA_PORT1_BASE;
	tmp_val=readl(port_addr+SATA_PORT_PHYCTL1);
	tmp_val &=~(TX_MARGIN);
	tmp_val |=(margin_value<<4);
	writel(tmp_val,port_addr+SATA_PORT_PHYCTL1);
	msleep(10);
}
void nano_tx_deemp_sata(u32 deemp_value,u32 port_num)
{
	unsigned int tmp_val;
	void __iomem *port_addr;

	if(0==port_num)
		port_addr=HI_SATA_PORT0_BASE;
	if(1==port_num)
		port_addr=HI_SATA_PORT1_BASE;
	tmp_val=readl(port_addr+SATA_PORT_PHYCTL1);
	tmp_val &=~(TX_DEEMPH);
	tmp_val |=(deemp_value<<2);
	writel(tmp_val,port_addr+SATA_PORT_PHYCTL1);
	msleep(10);
}

void hi_sata_init_hifone(void __iomem *mmio)
{	
	//Nano ComboPHY
	unsigned int tmp_val;
#ifdef CONFIG_SATA_PINMUX
	//SATA0 PWREN and SATA0 LED_N PIN MUX
	writel(0x2, __io_address(0xF8A21070));//Demo board use SATA0 PWREN
	msleep(10);
	writel(0x2, __io_address(0xF8A21074));
	msleep(10);
	//SATA1 PWREN and SATA1 LED_N PIN MUX
	writel(0x1, __io_address(0xF8A21040));
	msleep(10);
	writel(0x1, __io_address(0xF8A21058));//Test board only use SATA1 PWREN
	msleep(10);
#endif
	//Power on SATA0 and SATA1
	tmp_val = readl(PERI_CTRL);
	writel(tmp_val | SATA0_PWREN | SATA1_PWREN, PERI_CTRL);//Test board only use SATA1 PWREN
	msleep(10);

	//Config Nano ComboPHY2 to bypass 8B10B
	tmp_val = readl(PERI_COMBPHY2_CFG);
	tmp_val |=NANO_BYPASS_CODEC;
	writel(tmp_val, PERI_COMBPHY2_CFG);
	msleep(10);
	
	//reset Nano ComboPHY2
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	writel(tmp_val|COMBPHY2_SRST_REQ, CRG_BASE+PERI_CRG98);
	msleep(10);

	//close Nano ComboPHY2 cken
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~(COMBPHY2_REF_CKEN);
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);
	
	//Config Nano ComboPHY2 refclk
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~(COMBPHY2_REFCLK_SEL);
	tmp_val |=0x0<<17;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);
	
	//open Nano ComboPHY2 cken
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val |=COMBPHY2_REF_CKEN;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);

	//release reset Nano ComboPHY2
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~(COMBPHY2_SRST_REQ);
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);
	
	//open SATA Controller(Port0) Clock
	tmp_val=readl(CRG_BASE+PERI_CRG42);
	tmp_val |=SATA_TX0_CKEN
			|SATA_CKO_ALIVE_CKEN
			|SATA_RX0_CKEN
			|SATA_BUS_CKEN;
	writel(tmp_val, CRG_BASE+PERI_CRG42);
	msleep(10);

	//release reset SATA Controller(Port0)
	tmp_val=readl(CRG_BASE+PERI_CRG42);
	tmp_val &=~(SATA0_SRST_REQ
			|SATA_RX0_SRST_REQ
			|SATA_CKO_ALIVE_SRST_REQ
			|SATA_BUS_SRST_REQ);
	writel(tmp_val, CRG_BASE+PERI_CRG42);
	msleep(10);
	//Config Nano PHY
	//Config Nano Tx De-emphasis/TX_MARGIN/TX_SWING
	nano_tx_deemp_sata(0x1, 0x0);//De-emphasis -3.5dB
	nano_tx_margin_sata(0x2, 0x0);//TX_MARGIN 900mV
	//DOUBLE_PI_CURRETN&DOUBLE_PI_CMP_CURRENT
	nano_reg_write(0xd,0xe,0x2);
	//SSC on
	nano_reg_write(0x2,0x0,0x2);
	//SSC Off 
	/*nano_reg_write(0x2,0x8,0x2);*/
	//PWDN_6G_IDLE
	nano_reg_write(0x4,0x19,0x2);
	//sata_switch_clk
	nano_reg_write(0x0,0x0,0x2);
	//Data invert between phy and sata controller
	writel(0x8, HI_SATA_HOST_BASE+0xA4);
	msleep(10);

	//Config Port0 Spin-up
	writel(0x600000, HI_SATA_PORT0_BASE+0x18);
	msleep(10);
	writel(0x600002, HI_SATA_PORT0_BASE+0x18);
	msleep(10);

	//Config SATA Port0 phy controller
	writel(0xE400000, HI_SATA_PORT0_BASE+0x74);//6Gbps
	if (1 == modelimit)
		writel(0xE200000, HI_SATA_PORT0_BASE+0x74);//Force to 3Gbps
	if (0 == modelimit)
		writel(0xE000000, HI_SATA_PORT0_BASE+0x74);//Force to 1.5Gbps
	msleep(10);
#ifdef CONFIG_HI_SATA_PORT1
#ifdef CONFIG_SATA_PINMUX
	//SATA1 PWREN and SATA1 LED_N PIN MUX
	writel(0x1, __io_address(0xF8A21038));
	msleep(10);
#endif
	//Config Nano ComboPHY3 to SATA mode
	/*
	tmp_val = readl(PERI_CTRL);
	tmp_val &= ~(PCIE_USB3_SATA3_SEL_COMBPHY3);
	tmp_val |=0x2<<14;
	writel(tmp_val, PERI_CTRL);
	msleep(10);
	*/
	tmp_val = readl(PERI_CTRL);
	tmp_val = (tmp_val & PCIE_USB3_SATA3_SEL_COMBPHY3)>>14;
	if (0x2 == tmp_val) {
		//Config Nano ComboPHY3 to bypass 8B10B
		tmp_val = readl(PERI_COMBPHY3_CFG);
		tmp_val &=~(NANO_BYPASS_CODEC);
		writel(tmp_val, PERI_COMBPHY3_CFG);
		msleep(10);
		
		//reset Nano ComboPHY3
		tmp_val=readl(CRG_BASE+PERI_CRG98);
		writel(tmp_val|COMBPHY3_SRST_REQ, CRG_BASE+PERI_CRG98);
		msleep(10);
		
		//close Nano ComboPHY3 cken
		tmp_val=readl(CRG_BASE+PERI_CRG98);
		tmp_val &=~(COMBPHY3_REF_CKEN);
		writel(tmp_val, CRG_BASE+PERI_CRG98);
		msleep(10);
		
		//Config Nano ComboPHY3 refclk
		tmp_val=readl(CRG_BASE+PERI_CRG98);
		tmp_val &=~(COMBPHY3_REFCLK_SEL);
		tmp_val |=0x0<<25;
		writel(tmp_val, CRG_BASE+PERI_CRG98);
		msleep(10);
		
		//open Nano ComboPHY3 cken
		tmp_val=readl(CRG_BASE+PERI_CRG98);
		tmp_val |=COMBPHY3_REF_CKEN;
		writel(tmp_val, CRG_BASE+PERI_CRG98);
		msleep(10);
		
		//release reset Nano ComboPHY3
		tmp_val=readl(CRG_BASE+PERI_CRG98);
		tmp_val &=~(COMBPHY3_SRST_REQ);
		writel(tmp_val, CRG_BASE+PERI_CRG98);
		msleep(10);
		
		//open SATA Controller(Port1) Clock
		tmp_val=readl(CRG_BASE+PERI_CRG42);
		tmp_val |=SATA_TX1_CKEN
				|SATA_RX1_CKEN;
		writel(tmp_val, CRG_BASE+PERI_CRG42);
		
		//release reset SATA Controller(Port1)
		tmp_val=readl(CRG_BASE+PERI_CRG42);
		tmp_val &=~(SATA1_SRST_REQ
				|SATA_RX1_SRST_REQ);
		writel(tmp_val, CRG_BASE+PERI_CRG42);
		msleep(10);
		//Config Nano PHY
		//TODO:
		//Config Nano Tx De-emphasis/TX_MARGIN/TX_SWING
		nano_tx_deemp_sata(0x1, 0x1);//De-emphasis -3.5dB
		nano_tx_margin_sata(0x2, 0x1);//TX_MARGIN 900mV
		//DOUBLE_PI_CURRETN&DOUBLE_PI_CMP_CURRENT
		nano_reg_write(0xd,0xe,0x3);
		//SSC on
		nano_reg_write(0x2,0x0,0x3);
		//SSC off
		/*nano_reg_write(0x2,0x8,0x3);*/
		//PWDN_6G_IDLE
		nano_reg_write(0x4,0x19,0x3);
		//sata_switch_clk
		nano_reg_write(0x0,0x0,0x3);
		//Config Port1 Spin-up
		writel(0x600000, HI_SATA_PORT1_BASE+0x18);
		msleep(10);
		writel(0x600002, HI_SATA_PORT1_BASE+0x18);
		msleep(10);

		//Config SATA Port0 phy controller
		writel(0xE400000, HI_SATA_PORT1_BASE+0x74);//6Gbps
		if (1 == modelimit)
			writel(0xE200000, HI_SATA_PORT1_BASE+0x74);//Force to 3Gbps
		if (0 == modelimit)
			writel(0xE000000, HI_SATA_PORT1_BASE+0x74);//Force to 1.5Gbps
		msleep(10);
	}
#endif

}
EXPORT_SYMBOL(hi_sata_init_hifone);

void hi_sata_exit_hifone(void)
{
	unsigned int tmp_val;

	//reset SATA Controller(Port0)
	tmp_val=readl(CRG_BASE+PERI_CRG42);
	tmp_val |=SATA0_SRST_REQ
			|SATA_RX0_SRST_REQ
			|SATA_CKO_ALIVE_SRST_REQ
			|SATA_BUS_SRST_REQ;
	writel(tmp_val, CRG_BASE+PERI_CRG42);
	msleep(10);

	//close SATA Controller(Port0) Clock
	tmp_val=readl(CRG_BASE+PERI_CRG42);
	tmp_val &=~(SATA_TX0_CKEN
			|SATA_CKO_ALIVE_CKEN
			|SATA_RX0_CKEN
			|SATA_BUS_CKEN);
	writel(tmp_val, CRG_BASE+PERI_CRG42);
	msleep(10);

	//reset Nano ComboPHY2
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	writel(tmp_val|COMBPHY2_SRST_REQ, CRG_BASE+PERI_CRG98);
	msleep(10);

	//close Nano ComboPHY2
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~(COMBPHY2_REF_CKEN);
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);

	//Power off SATA0 PWREN
	tmp_val = readl(PERI_CTRL);
	writel(tmp_val&(~(SATA0_PWREN)), PERI_CTRL);
	msleep(10);
#ifdef CONFIG_HI_SATA_PORT1
	tmp_val = readl(PERI_CTRL);
	tmp_val = (tmp_val & PCIE_USB3_SATA3_SEL_COMBPHY3)>>14;
	if (0x2 == tmp_val) {
		//reset SATA Controller(Port1)
		tmp_val=readl(CRG_BASE+PERI_CRG42);
		tmp_val |= SATA1_SRST_REQ | SATA_RX1_SRST_REQ;
		writel(tmp_val, CRG_BASE+PERI_CRG42);
		msleep(10);
		
		//close SATA Controller(Port1) Clock
		tmp_val=readl(CRG_BASE+PERI_CRG42);
		tmp_val &=~(SATA_TX1_CKEN | SATA_RX1_CKEN);
		writel(tmp_val, CRG_BASE+PERI_CRG42);
		msleep(10);
		
		//reset Nano ComboPHY3
		tmp_val=readl(CRG_BASE+PERI_CRG98);
		writel(tmp_val|COMBPHY3_SRST_REQ, CRG_BASE+PERI_CRG98);
		msleep(10);

		//close Nano ComboPHY3
		tmp_val=readl(CRG_BASE+PERI_CRG98);
		tmp_val &=~(COMBPHY3_REF_CKEN);
		writel(tmp_val, CRG_BASE+PERI_CRG98);
		msleep(10);
		
		//Power off SATA1 PWREN
		tmp_val = readl(PERI_CTRL);
		writel(tmp_val&(~(SATA1_PWREN)), PERI_CTRL);
		msleep(10);
	}
#endif
}
EXPORT_SYMBOL(hi_sata_exit_hifone);
