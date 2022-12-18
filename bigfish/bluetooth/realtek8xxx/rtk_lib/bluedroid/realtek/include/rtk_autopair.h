#ifndef __BLUETOOTH_RTK_AUTOPAIR_H__
#define __BLUETOOTH_RTK_AUTOPAIR_H__

#ifdef BLUETOOTH_RTK_AUTOPAIR
#include "btm_api.h"
#include "hardware/bluetooth.h"

#define BLUETOOTH_RTK_AUTOPAIR_VENDOR   (0x005d)
#define BLUETOOTH_RTK_AUTOPAIR_CMDID    (0x0002)
extern int RTKBT_AUTOPAIR_CheckMSD(UINT8 * p, UINT8 len, UINT32 * p_rcuid, UINT8 * p_classic_supported,bt_bdaddr_t * p_classic_addr);       //MSD: Manufacturer Specific Data
#endif

#endif
