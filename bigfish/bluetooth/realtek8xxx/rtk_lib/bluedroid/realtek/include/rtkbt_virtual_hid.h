#ifndef RTK_POWER_H
#define RTK_POWER_H

BT_API void RTKBT_vhid_destroy();

BT_API BOOLEAN RTKBT_vhid_setup();

BT_API extern void RTKBT_process_vendor_event(UINT8 len, UINT8  *data);

#endif /* RTK_POWER_H */


