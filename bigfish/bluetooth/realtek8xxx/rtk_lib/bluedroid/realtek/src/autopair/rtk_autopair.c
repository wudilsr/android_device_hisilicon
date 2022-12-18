#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "rtk_autopair.h"
#include "btm_int.h"

/************************************************************************************
**  Constants & Macros
************************************************************************************/

/************************************************************************************
**  Local type definitions
************************************************************************************/

/************************************************************************************
**  Static variables
************************************************************************************/

/************************************************************************************
**  Static functions
************************************************************************************/

/************************************************************************************
**  Externs
************************************************************************************/
extern UINT32 remote_controller_id;

/************************************************************************************
**  Functions
************************************************************************************/
#ifdef  DUMMY_CLASSIC_INQUIRY_RESULT
int bluetooth_rtk_AutoPair_SendBLEInquiryResults()
{
    return 0;
}
int bluetooth_rtk_AutoPair_SendClassicInquiryResults(bt_bdaddr_t* p_classic_addr)
{
    UINT8 res[64];
    UINT8 *p = res;

//    if(btm_inq_db_find(p_classic_addr->address) != NULL)
//        return 0;

    UINT8_TO_STREAM(p,0x01); //Num_Responses
    BDADDR_TO_STREAM(p,p_classic_addr->address); //BD_ADDR
    UINT8_TO_STREAM(p,0x01); //Page_Scan_Repetition_Mode   R1
    UINT8_TO_STREAM(p,0x00); //Reserved 1
    UINT8_TO_STREAM(p,0x00); //Reserved 2

    UINT8_TO_STREAM(p,0x00); //ClassofDevice
    UINT8_TO_STREAM(p,0x05); //ClassofDevice
    UINT8_TO_STREAM(p,0x00); //ClassofDevice

    UINT8_TO_STREAM(p,0x00); //Clock_Offset
    UINT8_TO_STREAM(p,0x00); //Clock_Offset

    BTIF_TRACE_ERROR6("AutoPairing:SendClassicInquiryResults:addr %02x:%02x:%02x:%02x:%02x:%02x\n", \
        p_classic_addr->address[0], p_classic_addr->address[1], p_classic_addr->address[2], p_classic_addr->address[3], p_classic_addr->address[4], p_classic_addr->address[5]);
    btm_process_inq_results (res, BTM_INQ_RESULT_STANDARD);
    return 1;
}
#endif
int RTKBT_AUTOPAIR_CheckMSD(UINT8 * p, UINT8 len, UINT32 * p_rcuid, UINT8 * p_classic_supported,bt_bdaddr_t * p_classic_addr)   //MSD: Manufacturer Specific Data
{
    UINT32 cmd,vendor,rcu_id,classic_supported;
    UINT8 val,type,left;

    left = len;
    STREAM_TO_UINT16(vendor,p);
    BTIF_TRACE_ERROR1("AutoPairing:ITEM:vendor %04x\n",vendor);
    left -= 2;
    if((vendor == 0x7966)||(vendor == 0x6679))
    {
        *p_rcuid = 2;
        *p_classic_supported = 0;
        BTIF_TRACE_ERROR2("AutoPairing: IflyTek Vendor %04x ==> RcuID:%d\n",vendor,*p_rcuid);
        return 0;
    }
    if(vendor == BLUETOOTH_RTK_AUTOPAIR_VENDOR)
    {
        if(left<2) return -4;
        STREAM_TO_UINT16(cmd, p);
        BTIF_TRACE_ERROR1("AutoPairing:ITEM:cmd %04x\n",cmd);
        left -= 2;
        if(cmd == BLUETOOTH_RTK_AUTOPAIR_CMDID)
        {
            if(left<1) return -5;
            STREAM_TO_UINT8(val, p);
            left--;
            rcu_id = val<<8;
            if(left<1) return -6;
            STREAM_TO_UINT8(val, p);
            left--;
            rcu_id |= val;
/*
                    if(rcu_id&0x8000)
                    {
                    rcu_id = rcu_id<<8;
                    if(left<1) return -7;
                    STREAM_TO_UINT8(val, p);
                    left--;
                    rcu_id |= val;
                    }
*/
            BTIF_TRACE_ERROR1("AutoPairing:ITEM:rcu_id %08x\n",rcu_id);
            if(left>=6)
            {
                STREAM_TO_BDADDR(p_classic_addr->address, p);
                BTIF_TRACE_ERROR6("AutoPairing:ITEM:addr %02x:%02x:%02x:%02x:%02x:%02x\n", \
                p_classic_addr->address[0], p_classic_addr->address[1], p_classic_addr->address[2], p_classic_addr->address[3], p_classic_addr->address[4], p_classic_addr->address[5]);
#ifdef  DUMMY_CLASSIC_INQUIRY_RESULT
                bluetooth_rtk_AutoPair_SendClassicInquiryResults(p_classic_addr);
#endif
                classic_supported = 1;
                left -= 6;
            }else{
                classic_supported = 0;
                memset(p_classic_addr, 0 , sizeof(bt_bdaddr_t));
            }
            if(remote_controller_id == rcu_id){
                *p_rcuid = rcu_id;
            }
            else
                *p_rcuid = 0;
            *p_classic_supported = classic_supported;
            return 0;
        }
    }
    return 0;
}


