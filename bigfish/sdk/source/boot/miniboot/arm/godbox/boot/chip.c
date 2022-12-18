/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Cai Zhiyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
******************************************************************************/

#include <config.h>

#define readl(_a)        (*(volatile unsigned int *)(_a))
#define writel(_v, _a)   (*(volatile unsigned int *)(_a) = (_v))

/******************************************************************************/

static inline void delay(unsigned int cnt)
{
	while (cnt--)
		__asm__ __volatile__("nop");
}

/******************************************************************************/

long long get_chipid_reg(void)
{
        long long chipid = 0;
        unsigned int subchipid;
        unsigned int regval;

        regval = readl(REG_BASE_PERI_CTRL + REG_START_MODE);
        chipid = (long long)((regval >> 14) & 0x1F);

        regval = readl(REG_BASE_SCTL + REG_SC_SYSID0);
        subchipid = (regval & 0xFF);
        regval = readl(REG_BASE_SCTL + REG_SC_SYSID1);
        subchipid |= ((regval & 0xFF) << 8); 
        regval = readl(REG_BASE_SCTL + REG_SC_SYSID2);
        subchipid |= ((regval & 0xFF) << 16);
        regval = readl(REG_BASE_SCTL + REG_SC_SYSID3);
        subchipid |= ((regval & 0xFF) << 24);

        chipid = ((chipid << 32) | (long long)subchipid);

        return chipid;
}


/******************************************************************************/

unsigned int get_ca_vendor_reg(void)
{
	   unsigned long ca_vendor = 0;

	   /*
	    * enable CA module.
	    * set CA clock register default value(0x0000_0100)
	    */
	   writel(0x00000100, (REG_BASE_CRG + REG_PERI_CRG29));

	   /* delay 100 nop */
	   delay(100);

	   if (get_chipid_reg() == _HI3716M_V300) {
		   ca_vendor = readl(HI3716MV300_CA_BASE
			   + HI3716MV300_CA_BASE_MAILBOX);
		   ca_vendor = (ca_vendor & HI3716MV300_CA_BASE_MAILBOX_ENABLE);
	   } else {
		   ca_vendor = readl(REG_BASE_CA + CA_CTRL_PROC);
		   ca_vendor = ((ca_vendor >> CA_VENDOR_OFFSET) & CA_VENDOR_MASK);
	   }

	   return ca_vendor;
}

/******************************************************************************/

unsigned int get_ca_vendor(void)
{
	   static unsigned long ca_vendor = 0;
	   if (ca_vendor)
		   return ca_vendor;
	   ca_vendor = get_ca_vendor_reg();
	   return ca_vendor;
}

/******************************************************************************/

void reset_cpu(unsigned long addr)
{
	/*
	 * We should config the follow gpio before reset
	 * The config turn the pin to "start config" mode.
	 */
	if (get_chipid_reg() == _HI3716M_V300) {
		writel(0x02, 0x1020301C);
		writel(0x01, 0x10203030);
		writel(0x01, 0x10203034);
		writel(0x01, 0x1020304C);
		writel(0x01, 0x10203050);
		writel(0x01, 0x1020306C);
		writel(0x03, 0x10203074);
	} else {
		writel(0x01, 0x10203030);
		writel(0x01, 0x10203034);
		writel(0x01, 0x1020304C);
		writel(0x01, 0x10203050);
		writel(0x01, 0x1020306C);
		writel(0x03, 0x10203074);
	}

	/* unclock wdg */
	writel(0x1ACCE551, REG_BASE_WDG + 0x0C00);
	/* wdg load value */
	writel(0x00000100, REG_BASE_WDG + 0x0000);
	/* bit0: int enable bit1: reboot enable */
	writel(0x00000003, REG_BASE_WDG + 0x0008);
	while (1) ;
}
/******************************************************************************/
