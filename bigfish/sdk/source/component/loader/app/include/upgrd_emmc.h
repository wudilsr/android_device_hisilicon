/***********************************************************
 *                      Copyright    , 2009-2014, Hisilicon Tech. Co., Ltd.
 *                                   ALL RIGHTS RESERVED
 * FileName:  upgrd_fdisk.h
 * Description:
 *
 * History:
 * Version   Date          Author         DefectNum      Description
 * main\1    2011-09-16     lidongxiang     NULL
 ************************************************************/
#ifndef __UPGRD_IP_NET_H__
#define __UPGRD_IP_NET_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

#define EMMC_LOGIC_PART_FLAG (0xFFFFFFF0)
#define EMMC_BOOTARGS_ADDR (0x100000)
#define EMMC_BOOTARGS_SIZE (0x20000)

HI_S32 upgrd_emmc_fdisk_proc(HI_CHAR *pu8Data);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
#endif
