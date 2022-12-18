/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-07-04
 *
******************************************************************************/
#ifndef HIFMC100_DBGH
#define HIFMC100_DBGH
/******************************************************************************/

#define MAX_OPTION_SIZE                20

struct hifmc100_dbg_inf_t {
	const char name[MAX_OPTION_SIZE];
	int enable;
	int (*init)(struct dentry *root, struct hifmc_host *host);
	int (*uninit)(struct hifmc_host *host);

	void (*read)(struct hifmc_host *host);
	void (*write)(struct hifmc_host *host);
	void (*erase)(struct hifmc_host *host);

	void (*read_retry)(struct hifmc_host *host, int index);
};

#define CMD_WORD_ADDRESS            "address="
#define CMD_WORD_OFFSET             "offset="
#define CMD_WORD_LENGTH             "length="
#define CMD_WORD_CLEAN              "clear"
#define CMD_WORD_ON                 "on"
#define CMD_WORD_OFF                "off"

/******************************************************************************/
#endif /* HIFMC100_DBGH */
