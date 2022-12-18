#include <linux/phy.h>
#include "../hieth.h"
#include "../mac.h"
#include "autoeee.h"

void init_autoeee(struct hieth_netdev_local *ld, int link_stat)
{
	int phy_id = ld->phy->phy_id;
	int eee_available, lp_eee_capable, v;
	struct phy_info *phy_info;

	if (ld->eee_init)
		goto eee_init;

	phy_info = phy_search_ids(phy_id);
	if (phy_info) {
		eee_available = phy_info->eee_available;
			debug("fit phy_id:0x%x, phy_name:%s, eee:%d\n",
				phy_info->phy_id, phy_info->name,
				eee_available);

		if (!eee_available)
			goto not_support;

		if (eee_available == PHY_EEE) {
			debug("enter phy-EEE mode\n");
			v = readl(ld->iobase + EEE_ENABLE);
			v &= ~BIT_EEE_ENABLE;/* disable auto-EEE */
			writel(v, ld->iobase + EEE_ENABLE);
			return;
		}

		ld->eee_init = phy_info->eee_init;
eee_init:
		lp_eee_capable = ld->eee_init(ld->phy);
		if (link_stat & HIETH_LINKED) {
			if (lp_eee_capable & link_stat) {
				/* EEE_1us: 0x7c for 125M */
				writel(0x7c, ld->iobase + EEE_TIME_CLK_CNT);
				writel(0x4002710, ld->iobase + EEE_TIMER);/* FIXME */

				v = readl(ld->iobase + EEE_LINK_STATUS);
				v |= 0x3 << 1;/* auto EEE and ... */
				v |= BIT_PHY_LINK_STATUS;/* phy linkup */
				writel(v, ld->iobase + EEE_LINK_STATUS);

				v = readl(ld->iobase + EEE_ENABLE);
				v |= BIT_EEE_ENABLE;/* enable EEE */
				writel(v, ld->iobase + EEE_ENABLE);

				debug("enter auto-EEE mode\n");
				return;
			} else {
				debug("link partner not support EEE\n");
				return;
			}
		} else {
			v = readl(ld->iobase + EEE_LINK_STATUS);
			v &= ~(BIT_PHY_LINK_STATUS);/* phy linkdown */
			writel(v, ld->iobase + EEE_LINK_STATUS);
			return;
		}
	}

not_support:
	ld->eee_init = NULL;
	debug("non-EEE mode\n");
}

void eee_phy_linkdown(struct hieth_netdev_local *ld)
{
	int v = readl(ld->iobase + EEE_LINK_STATUS);
	/* update phy link state */
	v &= ~BIT_PHY_LINK_STATUS;
	writel(v, ld->iobase + EEE_LINK_STATUS);
}

void eee_phy_linkup(struct hieth_netdev_local *ld)
{
	int v = readl(ld->iobase + EEE_LINK_STATUS);
	/* update phy link state */
	v |= BIT_PHY_LINK_STATUS;
	writel(v, ld->iobase + EEE_LINK_STATUS);
}
