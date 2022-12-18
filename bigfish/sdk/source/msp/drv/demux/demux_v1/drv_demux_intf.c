/*******************************************************************************
 *              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: drv_demux_intf.c
 * Description: demux interface of module.
 *
 * History:
 * Version   Date         Author     DefectNum    Description
 * main\1    2010-01-25   j40671     NULL         init.
 ********************************************************************************/

/***************************** included files ******************************/
#include "hi_type.h"
#include "hi_drv_struct.h"
#include "hi_drv_dev.h"
#include "hi_drv_proc.h"
#include "hi_drv_stat.h"
#include "hi_drv_mem.h"
#include "hi_module.h"
#include "hi_kernel_adapt.h"

#include "demux_debug.h"
#include "hi_mpi_demux.h"
#include "hi_drv_demux.h"

#include "drv_demux.h"
#include "drv_demux_ioctl.h"
#include "drv_demux_ext.h"
#include "drv_demux_func.h"

#ifdef DMX_DESCRAMBLER_SUPPORT
#include "drv_descrambler.h"
#include "drv_descrambler_func.h"
#endif

/**************************** global variables ****************************/
static UMAP_DEVICE_S g_stDemuxDev;
extern DMX_DEV_OSI_S *g_pDmxDevOsi;
#define INVALID_OQ_ID 256
#ifdef HI_DEMUX_PROC_SUPPORT
/****************************** internal function *****************************/
char* SAVE_ES_STR = "save es";
char* SAVE_ALLTS_STR = "save allts";
char* SAVE_IPTS_STR = "save ipts";
char* SAVE_DMXTS_STR = "save dmxts";
char* HELP_STR = "help";
char* START_STR = "start";
char* STOP_STR = "stop";
char* DEBUG_OPEN_STR = "debug open";
char* DEBUG_CLOSE_STR = "debug close";

static HI_BOOL      DebugEn           = HI_FALSE;
extern DMX_Proc_Global_Info_S GlobalProcInfo;
OQ_HeaderInfor_t            OQInfo[DMX_OQ_CNT];
FQ_HeaderInfor_t            FQInfo[DMX_OQ_CNT];
ChannelDataFlow_info_t      ChannelDF[DMX_OQ_CNT];


HI_U8 DescProcList[10][40]  = {   "DescPhyAddr (0xc800+0x100*t)",
                                  "DescDepth   (0xc804+0x100*t)",
                                  "DescWPtr    (0xc808+0x100*t)",
                                  "DescRPtr    (0xc808+0x100*t)",
                                  "ValidDescNum(0xc80c+0x100*t)",
                                  "AddDescNum  (0xc810+0x100*t)",
                                  "DescWAddr   (     *DescWPtr)",
                                  "DescRAddr   (     *DescRPtr)",
                                  "DescSize    ( *DescWPtr + 1)",
                                  };

HI_U8 BPProcList[10][40]    = {   "FQLow32BPEn       (0x0xC220)",
                                  "FQHigh8BPEn       (0x0xC224)",
                                  "FQBP          (0xc340+t*0x8)",
                                  "SwitchBufferBp      (0xc204)",
                                  "OverflowBp          (0xc204)",
                                  "Rate        (0xc830+0x100*t)",
                                  "DebugEn     (0xC890+0x100*t)",
                                  "OutByte     (0xC894+0x100*t)",
                                  "OutTSNum    (0xC898+0x100*t)",
                                  "BPCount     (0xC89c+0x100*t)",

                                  };

HI_U8 OQProcInfo[13][40]  = {   "OQID                    :",
                                "BBWAddr    (0xe008[15:0])",
                                "BBEopAddr (0xe008[31:16])",
                                "OQUse      (0xe00c[13:0])",
                                "BBSize    (0xe00c[31:16])",
                                "BBSAddr          (0xe800)",
                                "OQWPtr      (0xe804[9:0])",
                                "OQRPtr    (0xe804[25:16])",
                                "OQWAddr         (*OQWPtr)",
                                "OQRAddr         (*OQRPtr)",
                                "FQCfg       (0xe808[9:0])",
                                "OQSize    (0xe808[25:16])",
                                "OQSAddr          (0xe80c)"

                            };

HI_U8 OQComments[13][40]  = {   "OQ ID",
                                "Cur BB Writing offset addr",
                                "Cur BB EOP offset addr",
                                "Out OQ Desc total num",
                                "BB(BufferBlock) size",
                                "Cur (Writing)BB start addr",
                                "OQ Writing ptr",
                                "OQ Reading ptr",
                                "OQ Writing ptr DDR Addr",
                                "OQ Reading ptr DDR Addr",
                                "FQ ID",
                                "OQ depth",
                                "OQ Start addr",

                            };

HI_U8 FQProcInfo[6][40]  = {    "FQUse      (0xd000[15:0])",
                                "FQRPtr     (0xd004[15:0])",
                                "FQVal      (0xd004[31:16)",
                                "FQWPtr     (0xd008[15:0])",
                                "FQSize    (0xd008[31:16])",
                                "FQStartAddr      (0xd00c)"
                            };
HI_U8 FQComments[6][40]  = {    "Total FQ Desc Num used",
                                "FQ Reading ptr",
                                "Valid FQ Desc (logic)",
                                "FQ Writing ptr",
                                "FQ depth",
                                "FQ Start addr",
                            };

HI_U8 ChanDataFlow[4][40]  = {  "PIDTsPacket  (0xda00+4*n)",
                                "BufferTsNum  (0xd800+4*n)",
                                "OQEn         (0xc130+4*n)",
                                "FQEn         (0xc140+4*n)",
                            };

HI_U8 ChanDFComments[4][40] = { "Ts  Num passed chan",
                                "Ts  Num entered Chan buf",
                                "OQ Enable",
                                "OFQ Enable",
                            };


static HI_VOID DMXDebugShowHelp(HI_VOID)
{
    HI_DRV_PROC_EchoHelper("echo %s %s > /proc/msp/demux_main  -- begin save es\n",SAVE_ES_STR,START_STR);
    HI_DRV_PROC_EchoHelper("echo %s %s > /proc/msp/demux_main  -- stop save es\n",SAVE_ES_STR,STOP_STR);
    HI_DRV_PROC_EchoHelper("echo %s %s x[portid] > /proc/msp/demux_main  -- begin save allts\n",SAVE_ALLTS_STR,START_STR);
    HI_DRV_PROC_EchoHelper("echo %s %s > /proc/msp/demux_main  -- stop save allts\n",SAVE_ALLTS_STR,STOP_STR);
    HI_DRV_PROC_EchoHelper("echo %s %s x[ram portid]> /proc/msp/demux_main  -- begin save ram port ts\n",SAVE_IPTS_STR,START_STR);
    HI_DRV_PROC_EchoHelper("echo %s %s > /proc/msp/demux_main  -- stop save ram port ts\n",SAVE_IPTS_STR,STOP_STR);
    HI_DRV_PROC_EchoHelper("echo %s %s x[dmxid] > /proc/msp/demux_main  -- begin save all channels ts\n",SAVE_DMXTS_STR,START_STR);
    HI_DRV_PROC_EchoHelper("echo %s %s > /proc/msp/demux_main  -- stop save dmx ts\n",SAVE_DMXTS_STR,STOP_STR);
    HI_DRV_PROC_EchoHelper("echo %s > /proc/msp/demux_main  -- show help info\n",HELP_STR);
}

#define STRSKIPBLANK(str)      \
        while (str[0] == ' ')\
        {\
        (str)++;\
        }\

static HI_S32 DMXProcWrite(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    HI_U32 cmd = 0xff;
    HI_U32 param = 0;
    HI_U32 needparam = 0;
    DMX_DEBUG_CMD_CTRl cmdctrl;
    char kbuf[256] = {0};
    char *p1;
    char *p2;
    HI_S32 ret;

    if (copy_from_user(kbuf, buf, count < sizeof(kbuf) ? count : sizeof(kbuf)))
    {
        HI_ERR_DEMUX("copy from user failed\n");
        return -1;
    }

    kbuf[sizeof(kbuf) - 1] = '\0';

    p1 = kbuf;
    p2 = p1;
    STRSKIPBLANK(p1);
    if (strstr(p1,SAVE_ES_STR) && p1[0] == 's')
    {
        cmd = DMX_DEBUG_CMD_SAVE_ES;
        p1 += strlen(SAVE_ES_STR);
    }
    else if (strstr(p1,SAVE_ALLTS_STR) && p1[0] == 's')
    {
        cmd = DMX_DEBUG_CMD_SAVE_ALLTS;
        p1 += strlen(SAVE_ALLTS_STR);
        needparam = 1;
    }
    else if (strstr(p1,SAVE_IPTS_STR) && p1[0] == 's')
    {
        cmd = DMX_DEBUG_CMD_SAVE_IPTS;
        p1 += strlen(SAVE_IPTS_STR);
        needparam = 1;
    }
    else if (strstr(p1,SAVE_DMXTS_STR) && p1[0] == 's')
    {
        cmd = DMX_DEBUG_CMD_SAVE_DMXTS;
        p1 += strlen(SAVE_DMXTS_STR);
        needparam = 1;
    }
    else if (strstr(p1,HELP_STR) && p1[0] == 'h')
    {
        DMXDebugShowHelp();
        return count;
    }
    else if (strstr(p1,DEBUG_OPEN_STR) && p1[0] == 'd')
    {
        DebugEn = HI_TRUE;
        return count;
    }
    else if (strstr(p1,DEBUG_CLOSE_STR) && p1[0] == 'd')
    {
        DebugEn = HI_FALSE;
        return count;
    }
    else
    {
        HI_PRINT("unknow command:%s\n",p1);
        DMXDebugShowHelp();
        return (-1);
    }
    STRSKIPBLANK(p1);
    if (strstr(p1,START_STR))
    {
        cmdctrl = DMX_DEBUG_CMD_START;
        p1 += strlen(START_STR);
    }
    else if (strstr(p1,STOP_STR))
    {
        cmdctrl = DMX_DEBUG_CMD_STOP;
        p1 += strlen(STOP_STR);
        needparam = 0;
    }
    else
    {
        HI_PRINT("command is not correct:%s\n",p2);
        DMXDebugShowHelp();
        return (-1);
    }
    if (needparam)
    {
        STRSKIPBLANK(p1);
        if (p1[0] == '\n')//do not have param
        {
            HI_PRINT("command is not correct:%s\n",p2);
            DMXDebugShowHelp();
            return (-1);
        }
        param = (HI_U32)simple_strtoul(p1, &p1, 10);
    }

    ret = DMX_OsrDebugCtrl(cmd,cmdctrl,param);
    if (ret != HI_SUCCESS)
    {
        HI_PRINT("command is not correct:%s\n",p2);
        DMXDebugShowHelp();
        return ret;
    }

    return count;
}

static HI_S32 DMXProcRead_debug(struct seq_file *p, HI_VOID *v)
{
    PROC_PRINT(p, "\n");
    PROC_PRINT(p, "----demux global inner debug information----\n");
    PROC_PRINT(p, "  release err count     : %d\n", GlobalProcInfo.ErrInfo.ReleaseErrCount);
    PROC_PRINT(p, "  release err Last chan : %d\n", GlobalProcInfo.ErrInfo.ReleaseErrLastChan);
    PROC_PRINT(p, "  release err Last OQ ID: %d\n", GlobalProcInfo.ErrInfo.ReleaseErrLastOQId);

    PROC_PRINT(p, " Reset Poolbuf count    : %d\n", GlobalProcInfo.ErrInfo.ResetPoolbufCount);

    PROC_PRINT(p, "  Dmx   Ref Multiprocess: %d\n", GlobalProcInfo.Ref);
    PROC_PRINT(p, "Dmx Ref max Multiprocess: %d\n", GlobalProcInfo.MaxRef);
    return HI_SUCCESS;
}

static HI_S32 DMXProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_U32 DmxId;

    if (DMX_DEV_INACTIVED == g_pDmxDevOsi->State)
    {
        HI_WARN_DEMUX("Demux has not started.\n");
        goto out;
    }

#ifdef DMX_TAG_DEAL_SUPPORT
    PROC_PRINT(p, "DmxId\tPortId\tTagPortId\n");
#else
    PROC_PRINT(p, "DmxId\tPortId\n");
#endif

    for (DmxId = 0; DmxId < DMX_CNT; DmxId++)
    {
        HI_S32              ret;
        HI_CHAR             PortStr[8] = "--";
        DMX_PORT_MODE_E     PortMode;
        HI_U32              PortId;
#ifdef DMX_TAG_DEAL_SUPPORT
        HI_U32 u32TagPortId ;
        HI_CHAR TagPortStr[8] = "--";
#endif

        ret = HI_DRV_DMX_GetPortId(DmxId, &PortMode, &PortId);
        if (HI_SUCCESS == ret)
        {
            if (PortMode == DMX_PORT_MODE_TUNER)
            {
                if ( DMX_IFPORT_CNT == 0 )
                {
                    PortId += HI_UNF_DMX_PORT_TSI_0;
                }
                else if(PortId >= DMX_IFPORT_CNT)
                {
                    PortId += HI_UNF_DMX_PORT_TSI_0 - DMX_IFPORT_CNT;
                }
            }
            else if(PortMode == DMX_PORT_MODE_RAM )
            {
                PortId += HI_UNF_DMX_PORT_RAM_0;
            }
            snprintf(PortStr, 8,"%u", PortId);
        }

#ifdef DMX_TAG_DEAL_SUPPORT
        ret = HI_DRV_DMX_GetTagPortId(DmxId, &u32TagPortId);
        if (HI_SUCCESS == ret)
        {
            snprintf(TagPortStr, sizeof(TagPortStr), "%u", u32TagPortId);
        }

        PROC_PRINT(p, "  %u\t%s\t%s\n", DmxId, PortStr, TagPortStr);
#else
        PROC_PRINT(p, "  %u\t%s\n", DmxId, PortStr);
#endif
    }

    if ( DebugEn )
    {
        DMXProcRead_debug(p,v);
    }

    PROC_PRINT(p, "type \"echo help > /proc/msp/demux_main\" to get help information\n");

out:
    return HI_SUCCESS;
}

static HI_VOID PortTypeToString(HI_CHAR *str, HI_U32 len, HI_U32 Type)

{
    switch (Type)
    {
        case HI_UNF_DMX_PORT_TYPE_PARALLEL_BURST :
            strncpy(str, "PARALLEL_BURST",len);
            break;

        case HI_UNF_DMX_PORT_TYPE_PARALLEL_VALID :
            strncpy(str, "PARALLEL_VALID",len);
            break;

        case HI_UNF_DMX_PORT_TYPE_PARALLEL_NOSYNC_204 :
            strncpy(str, "PARALLEL_NOSYNC_204",len);
            break;

        case HI_UNF_DMX_PORT_TYPE_PARALLEL_NOSYNC_188_204 :
            strncpy(str, "PARALLEL_NOSYNC_188_204",len);
            break;

        case HI_UNF_DMX_PORT_TYPE_SERIAL :
            strncpy(str, "SERIAL",len);
            break;

        case HI_UNF_DMX_PORT_TYPE_SERIAL2BIT :
            strncpy(str, "SERIAL2BIT",len);
            break;

        case HI_UNF_DMX_PORT_TYPE_SERIAL_NOSYNC :
            strncpy(str, "SERIAL_NOSYNC",len);
            break;

        case HI_UNF_DMX_PORT_TYPE_SERIAL2BIT_NOSYNC :
            strncpy(str, "SERIAL2BIT_NOSYNC",len);
            break;

        case HI_UNF_DMX_PORT_TYPE_USER_DEFINED :
            strncpy(str, "USER_DEFINED",len);
            break;

        case HI_UNF_DMX_PORT_TYPE_AUTO :
            strncpy(str, "AUTO",len);
            break;

        case HI_UNF_DMX_PORT_TYPE_PARALLEL_NOSYNC_188 :
        default :
            strncpy(str, "PARALLEL_NOSYNC_188",len);
    }
}

static HI_S32 DMXPortProcRead_debug(struct seq_file *p, HI_VOID *v)
{
    HI_U32                      i;
    HI_U32                      j;
    DMX_Proc_RamPort_DescInfo_S DescInfo[DMX_RAMPORT_CNT];
    DMX_Proc_RamPort_BPStatus_S BPStatus[DMX_RAMPORT_CNT];
    HI_U32 * pFiled = NULL;



    memset(&DescInfo[0],0x0,sizeof(DescInfo));
    memset(&BPStatus[0],0x0,sizeof(BPStatus));
    for (i = 0; i < 1; i++)
    {
        DMX_OsiRamPortGetDescInfo(i,&DescInfo[i]);
        DMX_OsiRamPortGetBPStatus(i,&BPStatus[i]);
    }
    PROC_PRINT(p,"\n-----------------------RAM Port inner debug information----------------------------\n");
    PROC_PRINT(p, "    information\\Port ID          128         129         130         131         132\n");
    PROC_PRINT(p,"Desc information:\n");
    for ( i = 0 ; i < 9 ; i++ )
    {

        PROC_PRINT(p,"%s     ",DescProcList[i]);
        for (j = 0; j < DMX_RAMPORT_CNT; j++)
        {
            pFiled = (HI_U32 *)&(DescInfo[j].DescPhyAddr);
            PROC_PRINT(p,"0x%-8x  ", *(pFiled + i) );
        }
        PROC_PRINT(p,"\n");
    }

    PROC_PRINT(p,"\nBack Pressure information:\n");
    for ( i = 0 ; i < 2 ; i++ )
    {
        PROC_PRINT(p,"%s     ",BPProcList[i]);
        for (j = 0; j < DMX_RAMPORT_CNT; j++)
        {
            pFiled = (HI_U32 *)&(BPStatus[j].FQLow32BPEn);
            PROC_PRINT(p,"0x%-8x  ", *(pFiled + i) );
        }
        PROC_PRINT(p,"\n");
    }

    for ( i = 2 ; i < 10 ; i++ )
    {
        PROC_PRINT(p,"%s     ",BPProcList[i]);
        for (j = 0; j < DMX_RAMPORT_CNT; j++)
        {
            pFiled = (HI_U32 *)&(BPStatus[j].FQLow32BPEn);
            PROC_PRINT(p," %-9d  ", *(pFiled + i) );
        }
        PROC_PRINT(p,"\n");
    }

    return HI_SUCCESS;
}

static HI_S32 DMXPortProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_U32                      i;
    HI_U32                      TsPacks;
    HI_U32                      ErrTsPacks;
    HI_UNF_DMX_PORT_ATTR_S      PortAttr;
    HI_UNF_DMX_TSO_PORT_ATTR_S  TSOPortAttr;
    HI_U32                      PortID;
    HI_UNF_DMX_TSO_PORT_E       TSIAttachTSO;

    if (DMX_DEV_INACTIVED == g_pDmxDevOsi->State)
    {
        HI_WARN_DEMUX("Demux has not started.\n");
        goto out;
    }

    PROC_PRINT(p, " --------------------------------IF port--------------------------\n");
    PROC_PRINT(p, " Id  AllTsCnt   ErrTsCnt  Lock/lost  ClkReverse    BitSel   Type\n");
    for (i = 0; i < DMX_IFPORT_CNT; i++)
    {
        HI_CHAR str[32] = "";
        HI_CHAR BitSel[16]  = "";
        HI_DRV_DMX_TunerPortGetAttr(i, &PortAttr);

        HI_DRV_DMX_TunerPortGetPacketNum(i, &TsPacks, &ErrTsPacks);

        PortTypeToString(str, sizeof(str),PortAttr.enPortType);
        if ( PortAttr.u32SerialBitSelector == 0x0 )
        {
            strncpy(BitSel, "D7",sizeof(BitSel));
        }
        else
        {
            strncpy(BitSel, "D0",sizeof(BitSel));
        }

        PROC_PRINT(p, "%3u    0x%-8x 0x%-4x     %u/%u        %d          %s       %s\n",
            i, TsPacks, ErrTsPacks, PortAttr.u32SyncLockTh, PortAttr.u32SyncLostTh, PortAttr.u32TunerInClk,BitSel,str);
    }

    PROC_PRINT(p, "\n-------------------------------TSI port-----------------------------------\n");
    PROC_PRINT(p, " Id  AllTsCnt   ErrTsCnt  Lock/lost  ClkReverse    BitSel   AttachTSO   Type\n");

    for (i = DMX_IFPORT_CNT; i < DMX_TUNERPORT_CNT; i++)
    {
        HI_CHAR str[32] = "";
        HI_CHAR BitSel[16]  = "";
        HI_CHAR AttachTSO[16]  = "";
        if ( DMX_IFPORT_CNT != 0 )
        {
            PortID = i + HI_UNF_DMX_PORT_TSI_0 - DMX_IFPORT_CNT;
        }
        else
        {
            PortID = i + HI_UNF_DMX_PORT_TSI_0;
        }
        HI_DRV_DMX_TunerPortGetAttr(i, &PortAttr);

        HI_DRV_DMX_TunerPortGetPacketNum(i, &TsPacks, &ErrTsPacks);

        PortTypeToString(str, sizeof(str),PortAttr.enPortType);
        if ( PortAttr.u32SerialBitSelector == 0x0 )
        {
            strncpy(BitSel, "D7",sizeof(BitSel));
        }
        else
        {
            strncpy(BitSel, "D0",sizeof(BitSel));
        }

        if ( HI_DRV_DMX_IsTSIAttachTSO(i, &TSIAttachTSO))
        {
            snprintf(AttachTSO, sizeof(AttachTSO),"%d",TSIAttachTSO);   
        }
        else
        {
            strncpy(AttachTSO, "-",sizeof(AttachTSO));
        }

        PROC_PRINT(p, "%3u    0x%-8x 0x%-4x     %u/%u        %d          %s           %s       %s\n",
            PortID, TsPacks, ErrTsPacks, PortAttr.u32SyncLockTh, PortAttr.u32SyncLostTh, PortAttr.u32TunerInClk,BitSel,AttachTSO,str);

    }

    PROC_PRINT(p, "\n------------------------------------------TSO port--------------------------------------------------\n");
    PROC_PRINT(p, " Id   Enable  ClkReverse  TSPortID    ClkMode     VldMode   Sync    Serial  BitSel  LSB   Clk   ClkDiv\n");

    for (i = 0; i < DMX_TSOPORT_CNT; i++)
    {
        HI_CHAR ClkMode[16] = "";
        HI_CHAR Sync[16]    = "";
        HI_CHAR BitSel[16]  = "";
        HI_CHAR Clk[16]  = "";


        HI_DRV_DMX_TSOPortGetAttr(i, &TSOPortAttr);

        if ( TSOPortAttr.enClkMode ==  HI_UNF_DMX_TSO_CLK_MODE_JITTER)
        {
            strncpy(ClkMode, "JITTER",sizeof(ClkMode));
        }
        else
        {
            strncpy(ClkMode, "NORMAL",sizeof(ClkMode));
        }

        if ( TSOPortAttr.bBitSync ==  HI_TRUE)
        {
            strncpy(Sync, "Bit ",sizeof(Sync));
        }
        else
        {
            strncpy(Sync, "Byte",sizeof(Sync));
        }

        if ( TSOPortAttr.enBitSelector == 0x0 )
        {
            strncpy(BitSel, "D0",sizeof(BitSel));
        }
        else
        {
            strncpy(BitSel, "D7",sizeof(BitSel));
        }

        switch(TSOPortAttr.enClk)
        {
            case HI_UNF_DMX_TSO_CLK_100M:
                strncpy(Clk, " 100M",sizeof(Clk));
                break;
            case HI_UNF_DMX_TSO_CLK_150M:
                strncpy(Clk, " 150M",sizeof(Clk));
                break;
            case HI_UNF_DMX_TSO_CLK_1200M:
                strncpy(Clk, "1200M",sizeof(Clk));
                break;
            case HI_UNF_DMX_TSO_CLK_1500M:
                strncpy(Clk, "1500M",sizeof(Clk));
                break;
            default:
                strncpy(Clk, "  Err",sizeof(Clk));
                break;
        }


        PROC_PRINT(p, " %d      %d         %d          %-3d      %s        %d       %s      %d      %s      %d   %s     %d\n",
        i,
        TSOPortAttr.bEnable,
        TSOPortAttr.bClkReverse,
        TSOPortAttr.enTSSource,
        ClkMode,
        TSOPortAttr.enValidMode,
        Sync,
        TSOPortAttr.bSerial,
        BitSel,
        TSOPortAttr.bLSB,
        Clk,
        TSOPortAttr.u32ClkDiv
        );

    }


    PROC_PRINT(p, "\n------------------------------------------------------------------RAM port-----------------------------------------------------\n");
    PROC_PRINT(p, " Id  AllTsCnt  TsChkRange Lock/lost   BufAddr      BufSize      BufUsed       Read       Write      Get(Try/Ok)     Put      Type\n");

    for (i = 0; i < DMX_RAMPORT_CNT; i++)
    {
        HI_CHAR Type[32] = "";
        HI_CHAR TsChkRange[16] = "";
        HI_CHAR BufUsed[20] = "";
        HI_U32  BufUsedRatio = 0;

        DMX_Proc_RamPort_BufInfo_S BufInfo;

        HI_DRV_DMX_RamPortGetAttr(i, &PortAttr);

        HI_DRV_DMX_RamPortGetPacketNum(i, &TsPacks);

        PortTypeToString(Type, sizeof(Type),PortAttr.enPortType);
        if ( PortAttr.enPortType !=  HI_UNF_DMX_PORT_TYPE_USER_DEFINED)
        {
            snprintf(TsChkRange, sizeof(TsChkRange),"  none   ");
        }
        else
        {
            snprintf(TsChkRange, sizeof(TsChkRange),"%d ~ %d",PortAttr.u32UserDefLen1,PortAttr.u32UserDefLen2);
        }

        if (HI_SUCCESS == DMX_OsiRamPortGetBufInfo(i, &BufInfo))
        {
            BufUsedRatio = (BufInfo.UsedSize/1024 * 100)/(BufInfo.BufSize/1024);
            snprintf(BufUsed,sizeof(BufUsed),"0x%x(%d%%)",BufInfo.UsedSize,BufUsedRatio);

            PROC_PRINT(p, "%3u    0x%-8x%s   %u/%u     0x%-8x    0x%-8x   %-10s    0x%-8x 0x%-8x%6u/%-10u%-5u    %s \n",
            HI_UNF_DMX_PORT_RAM_0 + i,
            TsPacks,
            TsChkRange,
            PortAttr.u32SyncLockTh,
            PortAttr.u32SyncLostTh,
            BufInfo.PhyAddr,
            BufInfo.BufSize,
            BufUsed,
            BufInfo.Read,
            BufInfo.Write,
            BufInfo.GetCount,
            BufInfo.GetValidCount,
            BufInfo.PutCount,
            Type);
        }
        else
        {
            PROC_PRINT(p, "%3u    0x%-8x%s   %u/%u                                                                                             %s\n",
            HI_UNF_DMX_PORT_RAM_0 + i, TsPacks, TsChkRange,PortAttr.u32SyncLockTh, PortAttr.u32SyncLostTh, Type);
        }


    }
    if ( DebugEn )
    {
        DMXPortProcRead_debug(p,v);
    }

#ifdef DMX_TAG_DEAL_SUPPORT
    {
        PROC_PRINT(p, "\n----------------------TagDeal port-------------------------------\n");
        PROC_PRINT(p, " Id  Enable  SyncMode TagLen              Tag               \n");

        for (i = 0; i < DMX_TAG_MAX_TS_WAY; i ++)
        {
            HI_UNF_DMX_TAG_ATTR_S TagPortAttrs;
            HI_U32 * pu32Low = (HI_U32 *)&(TagPortAttrs.au8Tag[0]);                   /* 0~4 bytes */
            HI_U32 * pu32Mid = (HI_U32 *)&(TagPortAttrs.au8Tag[4]);                /* 4~8 bytes */
            HI_U32 * pu32High = (HI_U32 *)&(TagPortAttrs.au8Tag[4 + 4]);         /* 8~12 bytes*/

            DMX_OsiGetTagPortAttr(i, &TagPortAttrs);

            PROC_PRINT(p, "  %u     %u       %u       %u     0x%08x%08x%08x\n", i, TagPortAttrs.bEnabled, TagPortAttrs.enSyncMod, TagPortAttrs.u32TagLen,
                *pu32Low, *pu32Mid, *pu32High);
        }
    }
#endif

out:
    return HI_SUCCESS;
}

static HI_S32 DMXChanProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_U32  ChanId;

    if (DMX_DEV_INACTIVED == g_pDmxDevOsi->State)
    {
        HI_WARN_DEMUX("Demux has not started.\n");
        goto out;
    }

    PROC_PRINT(p, "Id DmxId  PID\tType Mod Stat  KeyId    Acquire(Try/Ok)    Release\n");

    for (ChanId = 0; ChanId < DMX_CHANNEL_CNT; ChanId++)
    {
        DMX_ChanInfo_S *ChanInfo;
        HI_CHAR         ChanType[][8]   = {"SEC", "PES", "AUD", "VID", "PST", "ECM"};
        HI_CHAR         OutMode[][8]    = {"Reserve","PLY", "REC", "P&R"};
        HI_CHAR         KeyStr[8]       = "--";

        ChanInfo = DMX_OsiGetChannelProc(ChanId);
        if (!ChanInfo)
        {
            continue;
        }

        if (ChanInfo->KeyId < DMX_KEY_CNT)
        {
            snprintf(KeyStr, 8,"%-2u", ChanInfo->KeyId);
        }

        PROC_PRINT(p, "%-2u   %u   0x%x\t%s  %s %s\t%s   %10u/%-10u %u\n",
                        ChanId,
                        ChanInfo->DmxId,
                        ChanInfo->ChanPid,
                        ChanType[ChanInfo->ChanType],
                        (ChanInfo->ChanOutMode == HI_UNF_DMX_CHAN_OUTPUT_MODE_BUTT)?"UNO":OutMode[ChanInfo->ChanOutMode ],
                        (ChanInfo->ChanStatus == HI_UNF_DMX_CHAN_CLOSE)  ? "CLOSE" : "OPEN",
                        KeyStr,
                        ChanInfo->u32TotolAcq,
                        ChanInfo->u32HitAcq,
                        ChanInfo->u32Release
             );
    }

out:
    return HI_SUCCESS;
}

HI_S32 DMXChanBufProcRead_debug(struct seq_file *p, HI_VOID *v)
{
    HI_U32                      i;
    HI_U32                      j;
    HI_U32                      FiledCount;
    HI_U32                      PrintCount;
    HI_U32                      ChanId;
    HI_U32                      FQID;
    HI_U32                      OQID;
    HI_U32                      * pFiled = NULL;
    DMX_ChanInfo_S              *ChanInfo;
    HI_U32                      ChannelOQID[DMX_CHANNEL_CNT]  ;



    memset(&OQInfo[0],0x0,sizeof(OQInfo));
    memset(&FQInfo[0],0x0,sizeof(FQInfo));
    memset(&ChannelDF[0],0x0,sizeof(ChannelDF));

    for ( ChanId = 0 ; ChanId < DMX_CHANNEL_CNT ; ChanId++ )
    {
        ChannelOQID[ChanId] = INVALID_OQ_ID;

    }

    for (ChanId = 0; ChanId < DMX_CHANNEL_CNT; ChanId++)
    {
        ChanInfo = DMX_OsiGetChannelProc(ChanId);
        if (!ChanInfo)
        {
            break;
        }

        if ( ChanInfo->ChanOutMode == HI_UNF_DMX_CHAN_OUTPUT_MODE_REC)
        {
            OQID = DMX_CHANNEL_CNT + ChanInfo->DmxId*2;
        }
        else
        {
            OQID = ChanId;
        }
        ChannelOQID[ChanId] = OQID;

        DMX_OsiGetOQInfo(OQID, &OQInfo[OQID]);
        FQID = OQInfo[OQID].FQCfg;
        DMX_OsiGetFQInfo(FQID, &FQInfo[FQID]);
        DMX_OsiGetChannelDataFlow(ChanId, &ChannelDF[ChanId]);
    }


    PROC_PRINT(p,"\n-----------Channel buf  inner debug information--------------\n");

    ChanId = 0;
    while ( ChanId <  DMX_CHANNEL_CNT)
    {
        if ( ChannelOQID[ChanId] == INVALID_OQ_ID )
        {

            ChanId++;
            continue;
        }
        //=============================print the title=========================
        PROC_PRINT(p, " information\\Channel ID      ");
        PrintCount = 0;
        for (i = ChanId; i< DMX_CHANNEL_CNT; i++)
        {
            if ( ChannelOQID[i] == INVALID_OQ_ID  )
            {
                continue;
            }
            PROC_PRINT(p," %-9d  ", i );
            PrintCount++;
            if ( PrintCount >= 7 )
            {
                break;
            }
        }
        PROC_PRINT(p," Comments\n");
        //=============================print OQ information=========================
        PROC_PRINT(p,"OQ information:\n");
        for ( FiledCount = 0 ; FiledCount < 13 ; FiledCount++ )
        {
            PROC_PRINT(p,"%s     ",OQProcInfo[FiledCount]);
            PrintCount = 0;
            for (j = ChanId; j <DMX_CHANNEL_CNT; j++)
            {
                OQID = ChannelOQID[j];
                if ( OQID == INVALID_OQ_ID  )
                {
                    continue;
                }

                pFiled = (HI_U32 *)&(OQInfo[OQID].OQID);
                PROC_PRINT(p,"0x%-8x  ", *(pFiled + FiledCount) );
                PrintCount++;
                if ( PrintCount >= 7 )
                {
                    break;
                }

            }
            PROC_PRINT(p,"%s\n",OQComments[FiledCount]);
        }
        //=============================print FQ information=========================
        PROC_PRINT(p,"\nFQ information:\n");
        for ( FiledCount = 0 ; FiledCount < 6 ; FiledCount++ )
        {
            PROC_PRINT(p,"%s     ",FQProcInfo[FiledCount]);
            PrintCount = 0;
            for (j = ChanId; j <DMX_CHANNEL_CNT; j++)
            {
                OQID = ChannelOQID[j];
                if ( OQID == INVALID_OQ_ID  )
                {
                    continue;
                }

                FQID = OQInfo[OQID].FQCfg;
                pFiled = (HI_U32 *)&(FQInfo[FQID].FQUse);
                PROC_PRINT(p,"0x%-8x  ", *(pFiled + FiledCount) );
                PrintCount++;
                if ( PrintCount >= 7 )
                {
                    break;
                }


            }
            PROC_PRINT(p,"%s\n",FQComments[FiledCount]);
        }

        //=============================print Data flow information=========================
        PROC_PRINT(p,"\nChannel Data flow:\n");

        for ( FiledCount = 0 ; FiledCount < 4 ; FiledCount++ )
        {
            PROC_PRINT(p,"%s     ",ChanDataFlow[FiledCount]);
            PrintCount = 0;
            for (j = ChanId; j <DMX_CHANNEL_CNT; j++)
            {
                if ( ChannelOQID[j] == INVALID_OQ_ID  )
                {
                    continue;
                }

                pFiled = (HI_U32 *)&(ChannelDF[j].PIDTsPacket);
                PROC_PRINT(p,"0x%-8x  ", *(pFiled + FiledCount) );
                PrintCount++;
                if ( PrintCount >= 7 )
                {
                    break;
                }
            }
            PROC_PRINT(p,"%s\n",ChanDFComments[FiledCount]);
        }

        ChanId = j;
        PROC_PRINT(p,"\n-------------------------------------------------------------\n");

    }
    return 0;

}

static HI_S32 DMXChanBufProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_U32 i;

    if (DMX_DEV_INACTIVED == g_pDmxDevOsi->State)
    {
        HI_WARN_DEMUX("Demux has not started.\n");
        goto out;
    }

    PROC_PRINT(p, "Id  Size  BlkCnt BlkSize Read Write Used Overflow\n");

    for (i = 0; i < DMX_CHANNEL_CNT; i++)
    {
        DMX_Proc_ChanBuf_S  BufInfo;
        HI_U32              UsedPercent = 0;
        HI_U32              Size;

        if (HI_SUCCESS != DMX_OsiGetChanBufProc(i, &BufInfo))
        {
            continue;
        }

        if (BufInfo.DescDepth)
        {
            if (BufInfo.DescRead <= BufInfo.DescWrite)
            {
                UsedPercent = (BufInfo.DescWrite - BufInfo.DescRead) * 100 / BufInfo.DescDepth;
            }
            else
            {
                UsedPercent = (BufInfo.DescDepth + BufInfo.DescWrite - BufInfo.DescRead) * 100 / BufInfo.DescDepth;
            }
        }

        Size = BufInfo.DescDepth * BufInfo.BlockSize / 1024;

        PROC_PRINT(p, "%2u %5uK %-6u %-7u %-4u %-5u %3u%% %u\n",
            i, Size, BufInfo.DescDepth, BufInfo.BlockSize, BufInfo.DescRead, BufInfo.DescWrite, UsedPercent, BufInfo.Overflow);
    }

    if ( DebugEn )
    {
        DMXChanBufProcRead_debug(p,v);
    }

out:    
    return HI_SUCCESS;
}

static HI_S32 DMXFilterProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_U32 FilterId;
    HI_U32 i;

    if (DMX_DEV_INACTIVED == g_pDmxDevOsi->State)
    {
        HI_WARN_DEMUX("Demux has not started.\n");
        goto out;
    }

    PROC_PRINT(p, "Id ChanId Depth Param\n");

    for (FilterId = 0; FilterId < DMX_FILTER_CNT; FilterId++)
    {
        DMX_FilterInfo_S   *FilterInfo;
        HI_CHAR             str[16] = "--";

        FilterInfo = DMX_OsiGetFilterProc(FilterId);
        if (!FilterInfo)
        {
            continue;
        }

        if (FilterInfo->ChanId < DMX_CHANNEL_CNT)
        {
            snprintf(str, 16,"%2u", FilterInfo->ChanId);
        }

        PROC_PRINT(p, "%2u   %s   %3u   Match :", FilterId, str, FilterInfo->Depth);

        for (i = 0; i < FilterInfo->Depth; i++)
        {
            PROC_PRINT(p, " %02x", FilterInfo->Match[i]);
        }

        PROC_PRINT(p, "\n\t\tMask  :");
        for (i = 0; i < FilterInfo->Depth; i++)
        {
            PROC_PRINT(p, " %02x", FilterInfo->Mask[i]);
        }

        PROC_PRINT(p, "\n\t\tNegate:");
        for (i = 0; i < FilterInfo->Depth; i++)
        {
            PROC_PRINT(p, " %02x", FilterInfo->Negate[i]);
        }

        PROC_PRINT(p, "\n");
    }

out:
    return HI_SUCCESS;
}

static HI_S32 DMXPcrProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_U32 PcrId;

    if (DMX_DEV_INACTIVED == g_pDmxDevOsi->State)
    {
        HI_WARN_DEMUX("Demux has not started.\n");
        goto out;
    }

    PROC_PRINT(p, "Id DmxId PID    CurrPcr     CurrScr\n");

    for (PcrId = 0; PcrId < DMX_PCR_CHANNEL_CNT; PcrId++)
    {
        DMX_PCR_Info_S *PcrInfo;

        PcrInfo = DMX_OsiGetPcrChannelProc(PcrId);
        if (!PcrInfo)
        {
            continue;
        }

        PROC_PRINT(p, "%-2u   %u   0x%-4x 0x%-9llx 0x%-9llx\n",
            PcrId, PcrInfo->DmxId, PcrInfo->PcrPid, PcrInfo->PcrValue, PcrInfo->ScrValue);
    }

out:
    return HI_SUCCESS;
}

static HI_S32 DMXRecProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_U32 RecId;

    if (DMX_DEV_INACTIVED == g_pDmxDevOsi->State)
    {
        HI_WARN_DEMUX("Demux has not started.\n");
        goto out;
    }

    PROC_PRINT(p, "DmxId Type Descramed Status  Size  BlkCnt BlkSize Read Write Overflow\n");

    for (RecId = 0; RecId < DMX_CNT; RecId++)
    {
        DMX_Proc_Rec_BufInfo_S  RecInfo;
        HI_CHAR                *Type;
        HI_CHAR                *Status;
        HI_U32                  Size;

        if (HI_SUCCESS != DMX_OsiGetDmxRecProc(RecId, &RecInfo))
        {
            continue;
        }

        switch (RecInfo.RecType)
        {
            case HI_UNF_DMX_REC_TYPE_SELECT_PID :
                Type = "pid";
                break;

            case HI_UNF_DMX_REC_TYPE_ALL_PID :
                Type = "all";
                break;

            default :
                continue;
        }

        Size    = RecInfo.BlockCnt * RecInfo.BlockSize / 1024;
        Status  = RecInfo.RecStatus ? "start" : "stop ";

        PROC_PRINT(p, "%3u   %s      %u     %s  %5uK %-6u %-7u %-4u %-5u %u\n",
            RecId, Type, RecInfo.Descramed, Status, Size, RecInfo.BlockCnt,
            RecInfo.BlockSize, RecInfo.BufRead, RecInfo.BufWrite, RecInfo.Overflow);
    }

out:
    return HI_SUCCESS;
}

static HI_S32 DMXRecScdProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_U32 RecId;

    if (DMX_DEV_INACTIVED == g_pDmxDevOsi->State)
    {
        HI_WARN_DEMUX("Demux has not started.\n");
        goto out;
    }

    PROC_PRINT(p, "DmxId Type  Pid    Size BlkCnt BlkSize Read Write Overflow\n");

    for (RecId = 0; RecId < DMX_CNT; RecId++)
    {
        DMX_Proc_RecScd_BufInfo_S   ScdInfo;
        HI_CHAR                    *Type;
        HI_U32                      Size;

        if (HI_SUCCESS != DMX_OsiGetDmxRecScdProc(RecId, &ScdInfo))
        {
            continue;
        }

        switch (ScdInfo.IndexType)
        {
            case HI_UNF_DMX_REC_INDEX_TYPE_VIDEO :
                Type = "video";
                break;

            case HI_UNF_DMX_REC_INDEX_TYPE_AUDIO :
                Type = "audio";
                break;

            case HI_UNF_DMX_REC_INDEX_TYPE_NONE :
            default :
                Type = "none ";
        }

        Size = ScdInfo.BlockCnt * ScdInfo.BlockSize / 1024;

        PROC_PRINT(p, "%3u   %s 0x%-4x %3uK %-6u %-7u %-4u %-5u %u\n",
            RecId, Type, ScdInfo.IndexPid, Size, ScdInfo.BlockCnt,
            ScdInfo.BlockSize, ScdInfo.BufRead, ScdInfo.BufWrite, ScdInfo.Overflow);
    }

out:
    return HI_SUCCESS;
}
#endif

/**************************** external functions ******************************/

static HI_S32 DMXGlobalIoctl(struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 ret = HI_FAILURE;

    switch (cmd)
    {
        case CMD_DEMUX_GET_POOLBUF_ADDR:
        {
            DMX_MMZ_BUF_S *Param = (DMX_MMZ_BUF_S*)arg;

            ret = HI_DRV_DMX_GetPoolBufAddr(Param);

            break;
        }

        case CMD_DEMUX_GET_CAPABILITY:
        {
            HI_UNF_DMX_CAPABILITY_S *Param = (HI_UNF_DMX_CAPABILITY_S*)arg;

            ret = HI_DRV_DMX_GetCapability(Param);

            break;
        }
        case CMD_DEMUX_SET_PUSI:
        {
            HI_UNF_DMX_PUSI_SET_S *pPara = (HI_UNF_DMX_PUSI_SET_S *)arg;
            ret = HI_DRV_DMX_SetPusi(pPara->bPusi);
            break;
        }
        case CMD_DEMUX_SET_TEI:
        {
            HI_UNF_DMX_TEI_SET_S *pPara = (HI_UNF_DMX_TEI_SET_S *)arg;
            ret = HI_DRV_DMX_SetTei(pPara);
            break;
        }
        case CMD_DEMUX_TSI_ATTACH_TSO:
        {
            HI_UNF_DMX_TSI_ATTACH_TSO_S *pPara = (HI_UNF_DMX_TSI_ATTACH_TSO_S *)arg;
            ret = HI_DRV_DMX_TSIAttachTSO(pPara);
            break;
        }

        case CMD_DEMUX_GET_RESUME_COUNT:
        {
            HI_U32 *pCount = (HI_U32 *)arg;
            ret = HI_DRV_DMX_GetResumeCount(pCount);
            break;
        }

        default:
        {
            HI_ERR_DEMUX("unknown cmd: 0x%x\n", cmd);
        }
    }

    return ret;
}

static HI_S32 DMXPortIoctl(struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 ret = HI_FAILURE;

    switch (cmd)
    {
        case CMD_DEMUX_PORT_GET_ATTR:
        {
            DMX_Port_GetAttr_S *Param = (DMX_Port_GetAttr_S*)arg;

            if (DMX_PORT_MODE_RAM == Param->PortMode)
            {
                ret = HI_DRV_DMX_RamPortGetAttr(Param->PortId, &Param->PortAttr);
            }
            else
            {
                ret = HI_DRV_DMX_TunerPortGetAttr(Param->PortId, &Param->PortAttr);
            }

            break;
        }

        case CMD_DEMUX_PORT_SET_ATTR:
        {
            DMX_Port_SetAttr_S *Param = (DMX_Port_SetAttr_S*)arg;

            if (DMX_PORT_MODE_RAM == Param->PortMode)
            {
                ret = HI_DRV_DMX_RamPortSetAttr(Param->PortId, &Param->PortAttr);
            }
            else
            {
                ret = HI_DRV_DMX_TunerPortSetAttr(Param->PortId, &Param->PortAttr);
            }

            break;
        }

        case CMD_DEMUX_TSO_PORT_GET_ATTR:
        {
            DMX_TSO_Port_Attr_S *Param = (DMX_TSO_Port_Attr_S*)arg;
            ret = HI_DRV_DMX_TSOPortGetAttr(Param->PortId, &Param->PortAttr);
            break;
        }

        case CMD_DEMUX_TSO_PORT_SET_ATTR:
        {
            DMX_TSO_Port_Attr_S *Param = (DMX_TSO_Port_Attr_S*)arg;
            ret = HI_DRV_DMX_TSOPortSetAttr(Param->PortId, &Param->PortAttr);
            break;
        }

        case CMD_DEMUX_DMX_GET_TAG_ATTR:
        {
            #ifdef DMX_TAG_DEAL_SUPPORT
            DMX_Tag_GetAttr_S *Param = (DMX_Tag_GetAttr_S*)arg;

            ret = HI_DRV_DMX_GetTagAttr(Param->DmxId, &Param->TagAttr);
            #else
            ret = HI_ERR_NOT_SUPPORT_TAGDEAL;
            #endif
            break;
        }

        case CMD_DEMUX_DMX_SET_TAG_ATTR:
        {
            #ifdef DMX_TAG_DEAL_SUPPORT
            DMX_Tag_SetAttr_S *Param = (DMX_Tag_GetAttr_S*)arg;

            ret = HI_DRV_DMX_SetTagAttr(Param->DmxId, &Param->TagAttr);
            #else
            ret = HI_ERR_NOT_SUPPORT_TAGDEAL;
            #endif
            break;
        }

        case CMD_DEMUX_PORT_ATTACH:
        {
            DMX_Port_Attach_S *Param = (DMX_Port_Attach_S*)arg;

            if (DMX_PORT_MODE_RAM == Param->PortMode)
            {
                ret = HI_DRV_DMX_AttachRamPort(Param->DmxId, Param->PortId);
            }
            else
            {
                ret = HI_DRV_DMX_AttachTunerPort(Param->DmxId, Param->PortId);
            }

            break;
        }

        case CMD_DEMUX_PORT_DETACH:
        {
            ret = HI_DRV_DMX_DetachPort(*(HI_U32*)arg);

            break;
        }

        case CMD_DEMUX_PORT_GETID:
        {
            DMX_Port_GetId_S *Param = (DMX_Port_GetId_S*)arg;

            ret = HI_DRV_DMX_GetPortId(Param->DmxId, &Param->PortMode, &Param->PortId);

            break;
        }

        case CMD_DEMUX_PORT_GETPACKETNUM:
        {
            DMX_PortPacketNum_S *Param = (DMX_PortPacketNum_S*)arg;

            if (DMX_PORT_MODE_RAM == Param->PortMode)
            {
                Param->ErrTsPackCnt = 0;

                ret = HI_DRV_DMX_RamPortGetPacketNum(Param->PortId, &Param->TsPackCnt);
            }
            else
            {
                ret = HI_DRV_DMX_TunerPortGetPacketNum(Param->PortId, &Param->TsPackCnt, &Param->ErrTsPackCnt);
            }

            break;
        }

        default:
        {
            HI_ERR_DEMUX("unknown cmd: 0x%x\n", cmd);
        }
    }

    return ret;
}

static HI_S32 DMXTsBufferIoctl(struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 ret = HI_FAILURE;

    switch (cmd)
    {
        case CMD_DEMUX_TS_BUFFER_INIT:
        {
            DMX_TsBufInit_S *Param = (DMX_TsBufInit_S*)arg;

            ret = HI_DRV_DMX_CreateTSBuffer(Param->PortId, Param->BufSize, &Param->TsBuf, (HI_U32)file);

            break;
        }

        case CMD_DEMUX_TS_BUFFER_DEINIT:
        {
            ret = HI_DRV_DMX_DestroyTSBuffer(*(HI_U32*)arg);
            break;
        }

        case CMD_DEMUX_TS_BUFFER_GET:
        {
            DMX_TsBufGet_S *Param = (DMX_TsBufGet_S*)arg;

            ret = HI_DRV_DMX_GetTSBuffer(Param->PortId, Param->ReqLen, &Param->Data, Param->TimeoutMs);

            break;
        }

        case CMD_DEMUX_TS_BUFFER_PUT:
        {
            DMX_TsBufPut_S *Param = (DMX_TsBufPut_S*)arg;

            ret = HI_DRV_DMX_PutTSBuffer(Param->PortId, Param->ValidDataLen, Param->StartPos);

            break;
        }

        case CMD_DEMUX_TS_BUFFER_RESET:
        {
            ret = HI_DRV_DMX_ResetTSBuffer(*(HI_U32*)arg);

            break;
        }

        case CMD_DEMUX_TS_BUFFER_GET_STATUS:
        {
            DMX_TsBufStaGet_S *Param = (DMX_TsBufStaGet_S*)arg;

            ret = HI_DRV_DMX_GetTSBufferStatus(Param->PortId, &Param->Status);

            break;
        }

        default:
        {
            HI_ERR_DEMUX("unknown cmd: 0x%x\n", cmd);
        }
    }

    return ret;
}

static HI_S32 DMXChanIoctl(struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 ret = HI_FAILURE;

    switch (cmd)
    {
        case CMD_DEMUX_CHAN_NEW:
        {
            DMX_ChanNew_S *pPara = (DMX_ChanNew_S *)arg;
            ret = HI_DRV_DMX_CreateChannel(pPara->u32DemuxId, &pPara->stChAttr,
                                    &pPara->hChannel, &pPara->stChBuf, (HI_U32)file);
            break;
        }

        case CMD_DEMUX_CHAN_DEL:
        {
            ret = HI_DRV_DMX_DestroyChannel(*(HI_HANDLE*)arg);
            break;
        }

        case CMD_DEMUX_CHAN_OPEN:
        {
            ret = HI_DRV_DMX_OpenChannel(*(HI_HANDLE*)arg);
            break;
        }

        case CMD_DEMUX_CHAN_CLOSE:
        {
            ret = HI_DRV_DMX_CloseChannel(*(HI_HANDLE*)arg);
            break;
        }

        case CMD_DEMUX_CHAN_ATTR_GET:
        {
            DMX_GetChan_Attr_S *pPara = (DMX_GetChan_Attr_S *)arg;
            ret = HI_DRV_DMX_GetChannelAttr(pPara->hChannel, &pPara->stChAttr);
            break;
        }

        case CMD_DEMUX_CHAN_ATTR_SET:
        {
            DMX_SetChan_Attr_S *pPara = (DMX_SetChan_Attr_S *)arg;
            ret = HI_DRV_DMX_SetChannelAttr(pPara->hChannel, &pPara->stChAttr);
            break;
        }

        case CMD_DEMUX_GET_CHAN_STATUS:
        {
            DMX_ChanStatusGet_S *pPara = (DMX_ChanStatusGet_S *)arg;
            ret = HI_DRV_DMX_GetChannelStatus(pPara->hChannel, &pPara->stStatus);
            break;
        }

        case CMD_DEMUX_PID_SET:
        {
            DMX_ChanPIDSet_S *pPara = (DMX_ChanPIDSet_S *)arg;
            ret = HI_DRV_DMX_SetChannelPID(pPara->hChannel, pPara->u32Pid);
            break;
        }

        case CMD_DEMUX_PID_GET:
        {
            DMX_ChanPIDGet_S *pPara = (DMX_ChanPIDGet_S *)arg;
            ret = HI_DRV_DMX_GetChannelPID(pPara->hChannel, &pPara->u32Pid);
            break;
        }

        case CMD_DEMUX_CHANID_GET:
        {
            DMX_ChannelIdGet_S *pPara = (DMX_ChannelIdGet_S *)arg;
            ret = HI_DRV_DMX_GetChannelHandle(pPara->u32DmxId, pPara->u32Pid, &pPara->hChannel);
            break;
        }

        case CMD_DEMUX_FREECHAN_GET:
        {
            DMX_FreeChanGet_S *pPara = (DMX_FreeChanGet_S *)arg;
            ret = HI_DRV_DMX_GetFreeChannelCount(pPara->u32DmxId, &pPara->u32FreeCount);
            break;
        }

        case CMD_DEMUX_SCRAMBLEFLAG_GET:
        {
            DMX_ScrambledFlagGet_S *pPara = (DMX_ScrambledFlagGet_S *)arg;
            ret = HI_DRV_DMX_GetScrambledFlag(pPara->hChannel, &pPara->enScrambleFlag);
            break;
        }

        case CMD_DEMUX_CHAN_SET_EOS_FLAG:
        {
            ret = HI_DRV_DMX_SetChannelEosFlag(*(HI_HANDLE*)arg);
            break;
        }

#ifdef DMX_USE_ECM
        case CMD_DEMUX_GET_CHAN_SWFLAG:
        {
            DMX_ChanSwGet_S *pPara = (DMX_ChanSwGet_S *)arg;
            ret = DMX_OsrGetChannelSwFlag(pPara->hChannel, &pPara->u32SwFlag);
            break;
        }

        case CMD_DEMUX_GET_CHAN_SWBUF_ADDR:
        {
            DMX_ChanSwBufGet_S *pPara = (DMX_ChanSwBufGet_S *)arg;
            ret = DMX_OsrGetChannelSwBufAddr(pPara->hChannel, &(pPara->stChnBuf));
            break;
        }
#endif

        case CMD_DEMUX_GET_CHAN_TSCNT:
        {
            DMX_ChanChanTsCnt_S *pPara = (DMX_ChanChanTsCnt_S *)arg;
            ret = HI_DRV_DMX_GetChannelTsCount(pPara->hChannel, &(pPara->u32ChanTsCnt));
            break;
        }
        case CMD_DEMUX_CHAN_CC_REPEAT_SET:
        {
            DMX_SetChan_CC_REPEAT_S *pPara = (DMX_SetChan_CC_REPEAT_S *)arg;
            ret = HI_DRV_DMX_SetChannelCCRepeat(pPara->stChCCRepeatSet.hChannel, &pPara->stChCCRepeatSet);
            break;
        }

        default:
        {
            HI_ERR_DEMUX("unknown cmd: 0x%x\n", cmd);
        }
    }

    return ret;
}

static HI_S32 DMXFiltIoctl(struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 ret = HI_FAILURE;

    switch (cmd)
    {
        case CMD_DEMUX_FLT_NEW:
        {
            DMX_NewFilter_S *Param = (DMX_NewFilter_S*)arg;

            ret = HI_DRV_DMX_CreateFilter(Param->DmxId, &Param->FilterAttr, &Param->Filter, (HI_U32)file);

            break;
        }

        case CMD_DEMUX_FLT_DEL:
        {
            ret = HI_DRV_DMX_DestroyFilter(*(HI_HANDLE*)arg);

            break;
        }

        case CMD_DEMUX_FLT_SET:
        {
            DMX_FilterSet_S *Param = (DMX_FilterSet_S*)arg;

            ret = HI_DRV_DMX_SetFilterAttr(Param->Filter, &Param->FilterAttr);

            break;
        }

        case CMD_DEMUX_FLT_GET:
        {
            DMX_FilterGet_S *Param = (DMX_FilterGet_S*)arg;

            ret = HI_DRV_DMX_GetFilterAttr(Param->Filter, &Param->FilterAttr);

            break;
        }

        case CMD_DEMUX_FLT_ATTACH:
        {
            DMX_FilterAttach_S *Param = (DMX_FilterAttach_S*)arg;

            ret = HI_DRV_DMX_AttachFilter(Param->Filter, Param->Channel);

            break;
        }

        case CMD_DEMUX_FLT_DETACH:
        {
            DMX_FilterDetach_S *Param = (DMX_FilterDetach_S*)arg;

            ret = HI_DRV_DMX_DetachFilter(Param->Filter, Param->Channel);

            break;
        }

        case CMD_DEMUX_FREEFLT_GET:
        {
            DMX_FreeFilterGet_S *Param = (DMX_FreeFilterGet_S*)arg;

            ret = HI_DRV_DMX_GetFreeFilterCount(Param->DmxId, &Param->FreeCount);

            break;
        }

        case CMD_DEMUX_FLT_DELALL:
        {
            ret = HI_DRV_DMX_DestroyAllFilter(*(HI_HANDLE*)arg);

            break;
        }

        case CMD_DEMUX_FLT_CHANID_GET:
        {
            DMX_FilterChannelIDGet_S *Param = (DMX_FilterChannelIDGet_S*)arg;

            ret = HI_DRV_DMX_GetFilterChannelHandle(Param->Filter, &Param->Channel);

            break;
        }

        default:
        {
            HI_ERR_DEMUX("unknown cmd: 0x%x\n", cmd);
        }
    }

    return ret;
}



static HI_S32 DMXRecvIoctl(struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 ret = HI_FAILURE;

    switch (cmd)
    {
        case CMD_DEMUX_GET_DATA_FLAG:
        {
            DMX_GetDataFlag_S *pPara = (DMX_GetDataFlag_S *)arg;
            ret = HI_DRV_DMX_GetDataHandle(pPara->u32Flag, pPara->u32TimeOutMs);
            break;
        }

        case CMD_DEMUX_SELECT_DATA_FLAG:
        {
            DMX_SelectDataFlag_S *pPara = (DMX_SelectDataFlag_S*)arg;
            ret = HI_DRV_DMX_SelectDataHandle(pPara->channel, pPara->channelnum, pPara->u32Flag, pPara->u32TimeOutMs);
            break;
        }

        case CMD_DEMUX_ACQUIRE_MSG:
        {
            DMX_AcqMsg_S *pPara = (DMX_AcqMsg_S *)arg;
            DMX_UserMsg_S stReqBufTmp[DMX_DEFAULT_BUF_NUM];
            DMX_UserMsg_S* pstBufTmp;
            HI_U32 u32AcquireNum = pPara->u32AcquireNum;
            HI_UNF_DMX_DATA_S *pstBuf;
            if (u32AcquireNum > DMX_DEFAULT_BUF_NUM)
            {
                pstBufTmp = HI_VMALLOC(HI_ID_DEMUX, sizeof(DMX_UserMsg_S) * u32AcquireNum);
                if (NULL == pstBufTmp)
                {
                    HI_FATAL_DEMUX("malloc failed.\n");
                    ret = HI_ERR_DMX_ALLOC_MEM_FAILED;
                    break;
                }
            }
            else
            {
                pstBufTmp = stReqBufTmp;
            }

            ret = HI_DRV_DMX_AcquireBuf(pPara->hChannel, pPara->u32AcquireNum,
                                    &pPara->u32AcquiredNum, pstBufTmp, pPara->u32TimeOutMs);

            if (ret == HI_SUCCESS && pPara->u32AcquiredNum)
            {
                HI_UNF_DMX_DATA_S stUsrBuf;
                HI_U32 i;

                pstBuf = pPara->pstBuf;
                for (i = 0; i < pPara->u32AcquiredNum; i++)
                {
                    stUsrBuf.pu8Data = (HI_U8*)pstBufTmp[i].u32BufStartAddr;
                    stUsrBuf.u32Size = pstBufTmp[i].u32MsgLen;
                    stUsrBuf.enDataType = pstBufTmp[i].enDataType;

                    if (copy_to_user(&pstBuf[i], &stUsrBuf, sizeof(HI_UNF_DMX_DATA_S)))
                    {
                        HI_ERR_DEMUX("copy data buf to usr failed\n");
                        ret = HI_FAILURE;
                        break;
                    }
                }
            }
            if (u32AcquireNum > DMX_DEFAULT_BUF_NUM)
            {
                HI_VFREE(HI_ID_DEMUX, pstBufTmp);
            }

            break;
        }

        case CMD_DEMUX_RELEASE_MSG:
        {
            DMX_RelMsg_S *pPara = (DMX_RelMsg_S *)arg;
            DMX_UserMsg_S *pstBufTmp;
            DMX_UserMsg_S stReqBufTmp[DMX_DEFAULT_BUF_NUM];
            HI_U32 u32ReleaseNum;
            HI_UNF_DMX_DATA_S* pstBuf;
            HI_UNF_DMX_DATA_S stUsrBuf;
            HI_U32 i;

            u32ReleaseNum = pPara->u32ReleaseNum;
            if (u32ReleaseNum > DMX_DEFAULT_BUF_NUM)
            {
                pstBufTmp = HI_VMALLOC(HI_ID_DEMUX, sizeof(DMX_UserMsg_S) * u32ReleaseNum);
            }
            else
            {
                pstBufTmp = stReqBufTmp;
            }

            if (NULL == pstBufTmp)
            {
                HI_FATAL_DEMUX("malloc failed u32ReleaseNum:%x.\n", u32ReleaseNum);
                ret =  HI_ERR_DMX_ALLOC_MEM_FAILED;
                break;
            }
            pstBuf = pPara->pstBuf;
            for (i = 0; i < u32ReleaseNum; i++)
            {
                if (copy_from_user(&stUsrBuf, &pstBuf[i], sizeof(HI_UNF_DMX_DATA_S)))
                {
                    HI_ERR_DEMUX("copy data buf to usr failed\n");
                    ret = HI_FAILURE;
                    break;
                }

                pstBufTmp[i].u32BufStartAddr = (HI_U32)stUsrBuf.pu8Data;
                pstBufTmp[i].u32MsgLen = stUsrBuf.u32Size;
            }
            ret = HI_DRV_DMX_ReleaseBuf(pPara->hChannel, u32ReleaseNum, pstBufTmp);
            if (u32ReleaseNum > DMX_DEFAULT_BUF_NUM)
            {
                HI_VFREE(HI_ID_DEMUX, pstBufTmp);
            }


            break;
        }

        default:
        {
            HI_ERR_DEMUX("unknown cmd: 0x%x\n", cmd);
        }
    }

    return ret;
}

static HI_S32 DMXPcrIoctl(struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 ret = HI_FAILURE;

    switch (cmd)
    {
        case CMD_DEMUX_PCR_NEW:
        {
            DMX_NewPcr_S *pPara = (DMX_NewPcr_S *)arg;
            ret = HI_DRV_DMX_CreatePcrChannel(pPara->u32DmxId, &pPara->u32PcrId, (HI_U32)file);
            break;
        }

        case CMD_DEMUX_PCR_DEL:
        {
            ret = HI_DRV_DMX_DestroyPcrChannel(*(HI_U32*)arg);
            break;
        }

        case CMD_DEMUX_PCRPID_SET:
        {
            DMX_PcrPidSet_S *pPara = (DMX_PcrPidSet_S *)arg;
            ret = HI_DRV_DMX_PcrPidSet(pPara->pu32PcrChId, pPara->u32Pid);
            break;
        }

        case CMD_DEMUX_PCRPID_GET:
        {
            DMX_PcrPidGet_S *pPara = (DMX_PcrPidGet_S *)arg;
            ret = HI_DRV_DMX_PcrPidGet(pPara->pu32PcrChId, &pPara->u32Pid);
            break;
        }

        /* not support PCR user mode get, presently */
        case CMD_DEMUX_CURPCR_GET:
        {
            DMX_PcrScrGet_S *pPara = (DMX_PcrScrGet_S *)arg;
            ret = HI_DRV_DMX_PcrScrGet(pPara->pu32PcrChId, &pPara->u64PcrValue, &pPara->u64ScrValue);
            break;
        }

        case CMD_DEMUX_PCRSYN_ATTACH:
        {
            DMX_PCRSYNC_S *pPara = (DMX_PCRSYNC_S *)arg;
            ret = HI_DRV_DMX_PcrSyncAttach(pPara->u32PcrChId, pPara->u32SyncHandle);
            break;
        }

        case CMD_DEMUX_PCRSYN_DETACH:
        {
            DMX_PCRSYNC_S *pPara = (DMX_PCRSYNC_S *)arg;
            ret = HI_DRV_DMX_PcrSyncDetach(pPara->u32PcrChId);
            break;
        }

        default:
        {
            HI_ERR_DEMUX("unknown cmd: 0x%x\n", cmd);
        }
    }

    return ret;
}

static HI_S32 DMXAvIoctl(struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 ret = HI_FAILURE;

    switch (cmd)
    {
        case CMD_DEMUX_PES_BUFFER_GETSTAT:
        {
            DMX_PesBufStaGet_S *pPara = (DMX_PesBufStaGet_S *)arg;
            ret = HI_DRV_DMX_GetPESBufferStatus(pPara->hChannel, &pPara->stBufStat);
            break;
        }

        case CMD_DEMUX_ES_BUFFER_GET:
        {
            DMX_PesBufGet_S *pPara = (DMX_PesBufGet_S *)arg;
            DMX_Stream_S stEsBuf;
            stEsBuf.u32BufLen = 0;
            stEsBuf.u32PtsMs = INVALID_PTS;
            ret = HI_DRV_DMX_AcquireEs(pPara->hChannel, &stEsBuf);
            if (HI_SUCCESS == ret)
            {
                pPara->stEsBuf.pu8Buf = (HI_U8*)stEsBuf.u32BufPhyAddr;
                pPara->stEsBuf.u32BufLen = stEsBuf.u32BufLen;
                pPara->stEsBuf.u32PtsMs = stEsBuf.u32PtsMs;
            }

            break;
        }

        case CMD_DEMUX_ES_BUFFER_PUT:
        {
            DMX_PesBufGet_S *pPara = (DMX_PesBufGet_S *)arg;
            DMX_Stream_S stEsBuf;

            stEsBuf.u32BufPhyAddr = (HI_U32)pPara->stEsBuf.pu8Buf;
            stEsBuf.u32BufLen = pPara->stEsBuf.u32BufLen;
            stEsBuf.u32PtsMs = pPara->stEsBuf.u32PtsMs;

            ret = HI_DRV_DMX_ReleaseEs(pPara->hChannel, &stEsBuf);
            break;
        }

        default:
        {
            HI_ERR_DEMUX("unknown cmd: 0x%x\n", cmd);
        }
    }

    return ret;
}

static HI_S32 DMXRecIoctl(struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 ret = HI_FAILURE;

    switch (cmd)
    {
        case CMD_DEMUX_REC_CHAN_CREATE :
        {
            DMX_Rec_CreateChan_S *Param = (DMX_Rec_CreateChan_S*)arg;

            ret = HI_DRV_DMX_CreateRecChn(
                    &Param->RecAttr,
                    &Param->RecHandle,
                    &Param->RecBufPhyAddr,
                    &Param->RecBufSize,
                    (HI_U32)file
                );

            break;
        }

        case CMD_DEMUX_REC_CHAN_DESTROY :
        {
            ret = HI_DRV_DMX_DestroyRecChn(*(HI_HANDLE*)arg);

            break;
        }

        case CMD_DEMUX_REC_CHAN_ADD_PID :
        {
            DMX_Rec_AddPid_S *Param = (DMX_Rec_AddPid_S*)arg;

            ret = HI_DRV_DMX_AddRecPid(Param->RecHandle, Param->Pid, &Param->ChanHandle, (HI_U32)file);

            break;
        }

        case CMD_DEMUX_REC_CHAN_DEL_PID :
        {
            DMX_Rec_DelPid_S *Param = (DMX_Rec_DelPid_S*)arg;

            ret = HI_DRV_DMX_DelRecPid(Param->RecHandle, Param->ChanHandle);

            break;
        }

        case CMD_DEMUX_REC_CHAN_DEL_ALL_PID :
        {
            ret = HI_DRV_DMX_DelAllRecPid(*(HI_HANDLE*)arg);

            break;
        }

        case CMD_DEMUX_REC_CHAN_ADD_EXCLUDE_PID :
        {
            DMX_Rec_ExcludePid_S *Param = (DMX_Rec_ExcludePid_S*)arg;

            ret = HI_DRV_DMX_AddExcludeRecPid(Param->RecHandle, Param->Pid);

            break;
        }

        case CMD_DEMUX_REC_CHAN_DEL_EXCLUDE_PID :
        {
            DMX_Rec_ExcludePid_S *Param = (DMX_Rec_ExcludePid_S*)arg;

            ret = HI_DRV_DMX_DelExcludeRecPid(Param->RecHandle, Param->Pid);

            break;
        }

        case CMD_DEMUX_REC_CHAN_CANCEL_EXCLUDE :
        {
            ret = HI_DRV_DMX_DelAllExcludeRecPid(*(HI_HANDLE*)arg);

            break;
        }

        case CMD_DEMUX_REC_CHAN_START :
        {
            ret = HI_DRV_DMX_StartRecChn(*(HI_HANDLE*)arg);

            break;
        }

        case CMD_DEMUX_REC_CHAN_STOP :
        {
            ret = HI_DRV_DMX_StopRecChn(*(HI_HANDLE*)arg);

            break;
        }

        case CMD_DEMUX_REC_CHAN_ACQUIRE_DATA :
        {
            DMX_Rec_AcquireData_S *Param = (DMX_Rec_AcquireData_S*)arg;

            ret = HI_DRV_DMX_AcquireRecData(Param->RecHandle, &Param->RecData, Param->TimeoutMs);

            break;
        }

        case CMD_DEMUX_REC_CHAN_RELEASE_DATA :
        {
            DMX_Rec_ReleaseData_S *Param = (DMX_Rec_ReleaseData_S*)arg;

            ret = HI_DRV_DMX_ReleaseRecData(Param->RecHandle, &Param->RecData);

            break;
        }

        case CMD_DEMUX_REC_CHAN_ACQUIRE_INDEX :
        {
            DMX_Rec_AcquireIndex_S *Param = (DMX_Rec_AcquireIndex_S*)arg;

            ret = HI_DRV_DMX_AcquireRecIndex(Param->RecHandle, &Param->IndexData, Param->TimeoutMs);

            break;
        }
        case CMD_DEMUX_REC_CHAN_ACQUIRE_DATA_INDEX :
        {
            DMX_Rec_ProcessDataIndex_S *Param = (DMX_Rec_ProcessDataIndex_S*)arg;

            ret = HI_DRV_DMX_AcquireRecDataIndex(Param->RecHandle, &Param->RecDataIdx);

            break;
        }
        case CMD_DEMUX_REC_CHAN_RELEASE_DATA_INDEX :
        {
            DMX_Rec_ProcessDataIndex_S *Param = (DMX_Rec_ProcessDataIndex_S*)arg;

            ret = HI_DRV_DMX_ReleaseRecDataIndex(Param->RecHandle, &Param->RecDataIdx);

            break;
        }
        
        case CMD_DEMUX_REC_CHAN_GET_BUF_STATUS :
        {
            DMX_Rec_BufStatus_S *Param = (DMX_Rec_BufStatus_S*)arg;

            ret = HI_DRV_DMX_GetRecBufferStatus(Param->RecHandle, &Param->BufStatus);

            break;
        }

        default:
        {
            HI_ERR_DEMUX("unknown cmd: 0x%x\n", cmd);
        }
    }

    return ret;
}

HI_S32 DMX_OsrIoctl(struct inode *inode, struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32  ret     = HI_FAILURE;
    HI_U32  CmdType = cmd & DEMUX_CMD_MASK;

    switch (CmdType)
    {
        case DEMUX_GLOBAL_CMD:
        {
            ret = DMXGlobalIoctl(file, cmd, arg);

            break;
        }

        case DEMUX_PORT_CMD:
        {
            ret = DMXPortIoctl(file, cmd, arg);

            break;
        }

        case DEMUX_TSBUFFER_CMD:
        {
            ret = DMXTsBufferIoctl(file, cmd, arg);

            break;
        }

        case DEMUX_CHAN_CMD:
        {
            ret = DMXChanIoctl(file, cmd, arg);

            break;
        }

        case DEMUX_FILT_CMD:
        {
            ret = DMXFiltIoctl(file, cmd, arg);

            break;
        }

    #ifdef DMX_DESCRAMBLER_SUPPORT
        case DEMUX_KSET_CMD:
        {
            ret = DMXKeyIoctl(file, cmd, arg);

            break;
        }
    #endif

        case DEMUX_RECV_CMD:
        {
            ret = DMXRecvIoctl(file, cmd, arg);

            break;
        }

        case DEMUX_PCR_CMD:
        {
            ret = DMXPcrIoctl(file, cmd, arg);

            break;
        }

        case DEMUX_AV_CMD:
        {
            ret = DMXAvIoctl(file, cmd, arg);

            break;
        }

        case DEMUX_REC_CMD:
        {
            ret = DMXRecIoctl(file, cmd, arg);

            break;
        }

        default:
        {
            HI_ERR_DEMUX("unknown cmd: 0x%x\n", cmd);
        }
    }

    return ret;
}

/*****************************************************************************
 Prototype    : DMX_DRV_Open
 Description  : open function in DEMUX module
 Input        : None
 Output       : None
 Return Value :
*****************************************************************************/
static HI_S32 DMX_DRV_Open(struct inode * inode, struct file * file)
{
    HI_DRV_DMX_Open();

    return 0;
}

/*****************************************************************************
 Prototype    : DMX_DRV_Release
 Description  : release function in DEMUX module
 Input        : None
 Output       : None
 Return Value :
*****************************************************************************/
static HI_S32 DMX_DRV_Release(struct inode * inode, struct file * file)
{
    HI_DRV_DMX_Close((HI_U32)file);

    return 0;
}

/*****************************************************************************
 Prototype    : DMX_DRV_Ioctl
 Description  : Ioctl function in DEMUX module
 Input        : None
 Output       : None
 Return Value :
*****************************************************************************/
static long DMX_DRV_Ioctl(struct file *file, HI_U32 cmd, unsigned long arg)
{
    return (long)HI_DRV_UserCopy(file->f_dentry->d_inode, file, cmd, arg, DMX_OsrIoctl);
}

static struct file_operations DMX_DRV_Fops =
{
    .owner          = THIS_MODULE,
    .open           = DMX_DRV_Open,
    .unlocked_ioctl = DMX_DRV_Ioctl,
    .release        = DMX_DRV_Release,
};

static PM_BASEOPS_S dmx_drvops =
{
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = DMX_OsiSuspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = DMX_OsiResume,
};

/*****************************************************************************
 Prototype    : DMX_DRV_ModInit
 Description  : initialize function in DEMUX module
 Input        : None
 Output       : None
 Return Value :
*****************************************************************************/
HI_S32 DMX_DRV_ModInit(HI_VOID)
{
#ifdef HI_DEMUX_PROC_SUPPORT
    DRV_PROC_ITEM_S *item;
    DRV_PROC_EX_S stFnOpt = {0};
#endif

#ifndef HI_MCE_SUPPORT
    if (HI_SUCCESS != HI_DRV_DMX_BasicInit())
    {
        goto out;
    }
#endif

    strncpy(g_stDemuxDev.devfs_name, UMAP_DEVNAME_DEMUX, strlen(UMAP_DEVNAME_DEMUX));
    g_stDemuxDev.devfs_name[strlen(UMAP_DEVNAME_DEMUX)] = '\0';
    g_stDemuxDev.fops   = &DMX_DRV_Fops;
    g_stDemuxDev.minor  = UMAP_MIN_MINOR_DEMUX;
    g_stDemuxDev.owner  = THIS_MODULE;
    g_stDemuxDev.drvops = &dmx_drvops;

    if (HI_DRV_DEV_Register(&g_stDemuxDev) < 0)
    {
        HI_FATAL_DEMUX("Unable to register demux dev\n");
        goto out;
    }

#ifdef HI_DEMUX_PROC_SUPPORT
    item = HI_DRV_PROC_AddModule("demux_main", NULL, NULL);
    if (!item)
    {
        HI_ERR_DEMUX("add proc demux_main failed\n");
    }
    else
    {
        item->read  = DMXProcRead;
        item->write = DMXProcWrite;
    }

    stFnOpt.fnRead = DMXPortProcRead;
    item = HI_DRV_PROC_AddModule("demux_port", &stFnOpt, NULL);
    if (!item)
    {
        HI_ERR_DEMUX("add proc demux_port failed\n");
    }

    stFnOpt.fnRead = DMXChanProcRead;
    item = HI_DRV_PROC_AddModule("demux_chan", &stFnOpt, NULL);
    if (!item)
    {
        HI_ERR_DEMUX("add proc demux_chan failed\n");
    }

    stFnOpt.fnRead = DMXChanBufProcRead;
    item = HI_DRV_PROC_AddModule("demux_chanbuf", &stFnOpt, NULL);
    if (!item)
    {
        HI_ERR_DEMUX("add proc demux_chanbuf failed\n");
    }

    stFnOpt.fnRead = DMXFilterProcRead;
    item = HI_DRV_PROC_AddModule("demux_filter", &stFnOpt, NULL);
    if (!item)
    {
        HI_ERR_DEMUX("add proc demux_filter failed\n");
    }

/******* proc function begin ********/
#ifdef DMX_DESCRAMBLER_SUPPORT
    stFnOpt.fnRead = DMXKeyProcRead;
    item = HI_DRV_PROC_AddModule("demux_key", &stFnOpt, NULL);
    if (!item)
    {
        HI_ERR_DEMUX("add proc demux_key failed\n");
    }
#endif
/******* proc function end ********/

    stFnOpt.fnRead = DMXPcrProcRead;
    item = HI_DRV_PROC_AddModule("demux_pcr", &stFnOpt, NULL);
    if (!item)
    {
        HI_ERR_DEMUX("add proc demux_pcr failed\n");
    }

    stFnOpt.fnRead = DMXRecProcRead;
    item = HI_DRV_PROC_AddModule("demux_rec", &stFnOpt, NULL);
    if (!item)
    {
        HI_ERR_DEMUX("add proc demux_rec failed\n");
    }

    stFnOpt.fnRead = DMXRecScdProcRead;
    item = HI_DRV_PROC_AddModule("demux_rec_index", &stFnOpt, NULL);
    if (!item)
    {
        HI_ERR_DEMUX("add proc demux_rec_index failed\n");
    }
#endif

#ifdef MODULE
    HI_PRINT("Load hi_demux.ko success.  \t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;

out :
    DMX_DRV_ModExit();

    return HI_FAILURE;
}

/*****************************************************************************
 Prototype    : DMX_DRV_ModExit
 Description  : exit function in DEMUX module
 Input        : None
 Output       : None
 Return Value :
*****************************************************************************/
HI_VOID DMX_DRV_ModExit(HI_VOID)
{
#ifdef HI_DEMUX_PROC_SUPPORT
    HI_DRV_PROC_RemoveModule("demux_rec_index");
    HI_DRV_PROC_RemoveModule("demux_rec");
    HI_DRV_PROC_RemoveModule("demux_pcr");
/******* proc function begin ********/
#ifdef DMX_DESCRAMBLER_SUPPORT
    HI_DRV_PROC_RemoveModule("demux_key");
#endif
/******* proc function end ********/
    HI_DRV_PROC_RemoveModule("demux_filter");
    HI_DRV_PROC_RemoveModule("demux_chanbuf");
    HI_DRV_PROC_RemoveModule("demux_chan");
    HI_DRV_PROC_RemoveModule("demux_tsbuf");
    HI_DRV_PROC_RemoveModule("demux_port");
    HI_DRV_PROC_RemoveModule("demux_main");
#endif

    HI_DRV_DEV_UnRegister(&g_stDemuxDev);

#ifndef HI_MCE_SUPPORT
    HI_DRV_DMX_DeInit();
#endif
}

#ifdef MODULE
module_init(DMX_DRV_ModInit);
module_exit(DMX_DRV_ModExit);
#endif

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");

