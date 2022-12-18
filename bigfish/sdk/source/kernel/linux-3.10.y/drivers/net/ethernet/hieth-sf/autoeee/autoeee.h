#ifndef	_AUTO_EEE_H

#define NO_EEE          0
#define MAC_EEE         1
#define PHY_EEE         2
#define PARTNER_EEE     2
//#define debug(fmt...) printk(fmt)
#define debug(fmt...)
struct phy_info {
	char *name;
	int phy_id;
	char eee_available;/* eee support by this phy */
	int (*eee_init)(struct phy_device *phy_dev);
};

/* GMAC register definition */
#define EEE_ENABLE		0x488
#define BIT_EEE_ENABLE		(1 << 0)
#define EEE_TIMER		0x48C
#define EEE_LINK_STATUS		0x490
#define BIT_PHY_LINK_STATUS	(1 << 0)
#define EEE_TIME_CLK_CNT	0x494


/* ----------------------------phy register-------------------------------*/
/* MMD: MDIO Manageable Device */
#define MACR		0x0D
#define MAADR		0x0E
#define EEE_DEV		0x3
#define EEE_CAPABILITY	0x14
#define	EEELPAR_DEV	0x7
#define EEELPAR		0x3D	/* EEE link partner ability register */
#define EEE_ADVERTISE	0x3c
#define LP_1000BASE_EEE	(1 << 2)
#define LP_100BASE_EEE	(1 << 1)

extern struct phy_info *phy_search_ids(int phy_id);

extern void init_autoeee(struct hieth_netdev_local *ld, int link_stat);

#endif
