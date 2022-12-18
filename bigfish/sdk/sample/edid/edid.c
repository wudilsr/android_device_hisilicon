#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#include <assert.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include <fcntl.h>
#include "hi_unf_mce.h"
#include "hi_unf_pdm.h"
#include "hi_unf_i2c.h"
#include "hi_unf_edid.h"
#include "hi_mpi_edid.h"
#include "hi_adp.h"
#include "hi_adp_hdmi.h"

#define  VGA_SCL (9*8+6)   /*GPIO 9_6*/
#define  VGA_SDA (9*8+7)   /*GPIO 9_7*/
#define  VGA_CHECK_PIN (2 * 8 + 0)   /*GPIO 2_0*/

#define  EDID_BLOCK_NUM (128)   
#define  VGA_I2C_ADDR (0xA0)  


#define  CV200GPIO2_0MODE_REG_ADDR  (0xf8a21040)   
#define  CV200GPIO2_0MODE_VALUE  (0x0)  

#define  CV200GPIO9_6MODE_REG_ADDR  (0xf8a2111c)   
#define  CV200GPIO9_6MODE_VALUE  (0x2)   


#define  CV200GPIO9_7MODE_REG_ADDR (0xf8a21118) 
#define  CV200GPIO9_7MODE_VALUE  (0x2)   


static pthread_t   g_VGAThd;

HI_BOOL g_bStopTsThread = HI_FALSE;

#define  VGA_PLUG  HI_FALSE  
#define  VGA_UNPLUG HI_TRUE  

HI_BOOL g_bVGAStatus = VGA_UNPLUG;

typedef struct cfgREAD_EDID_S
{
    HI_U32         u32DeviceAddress;
    HI_U32         u32RegAddr;
    HI_U32         u32ReadNumber;
    HI_U32         u32RegAddrCount;
} CFG_READ_EDID_S;


HI_VOID SaveDateToFile(HI_CHAR* pFilePath, HI_U8* pDateBuf, HI_U32 u32DataLen)
{
    HI_S32 Ret = 0;
    FILE* pFileSave = HI_NULL;/*struct */

    pFileSave = fopen(pFilePath, "wb");
    if (NULL == pFileSave )
    {
        printf("\n:open file err!! \n");
        return;
    }
    Ret = fwrite(pDateBuf, 1, u32DataLen, pFileSave);
    printf("\n:fwrite (%d):\n", Ret);
    fflush(pFileSave);
    fclose(pFileSave);
    printf("Save  EDID file :%s,length %d Bytes\n",pFilePath,u32DataLen);
    return ;
}

HI_S32 VGA_ReadEDID(CFG_READ_EDID_S *pstCfgReadEdid, HI_U8* pData)
{
    HI_S32 s32Ret = 0;
    HI_U32 u32I2cID;

    HI_SYS_WriteRegister( CV200GPIO9_6MODE_REG_ADDR, CV200GPIO9_6MODE_VALUE);/*GPIO 9_6  GPIO mode*/
    HI_SYS_WriteRegister( CV200GPIO9_7MODE_REG_ADDR, CV200GPIO9_7MODE_VALUE);/*GPIO 9_7  GPIO mode*/

    s32Ret = HI_UNF_I2C_Init();
    if (HI_SUCCESS != s32Ret)
    {
        printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, s32Ret);
        return s32Ret;
    }

    s32Ret =  HI_UNF_I2C_CreateGpioI2c(&u32I2cID, VGA_SCL, VGA_SDA);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_I2C_Read failed.\n");
        HI_UNF_I2C_DeInit();

        return s32Ret;
    }

    s32Ret = HI_UNF_I2C_Read(u32I2cID, VGA_I2C_ADDR, 0, 1, pData, pstCfgReadEdid->u32ReadNumber);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_I2C_Read failed.\n");
        HI_UNF_I2C_DeInit();
        return s32Ret;
    }

    printf("extern  --------------------------%d\n", pData[126]);
    if (0x0 == pData[126])
    {
        printf("no extern block\n");
    }
    else  if (0x1 == pData[126])
    {
        printf(" extern block num  1\n");
        pstCfgReadEdid->u32ReadNumber = EDID_BLOCK_NUM + pData[126] * EDID_BLOCK_NUM;
        s32Ret = HI_UNF_I2C_Read(u32I2cID, VGA_I2C_ADDR, 0, 1, pData, pstCfgReadEdid->u32ReadNumber);
        if (s32Ret != HI_SUCCESS)
        {
            printf("call HI_I2C_Read failed.\n");
            HI_UNF_I2C_DeInit();
            return s32Ret;
        }

    }
    else  if (0x2 == pData[126])
    {
        printf("CEA_EXT extern block\n");
        pstCfgReadEdid->u32ReadNumber = EDID_BLOCK_NUM + pData[126] * EDID_BLOCK_NUM;
        s32Ret = HI_UNF_I2C_Read(u32I2cID, VGA_I2C_ADDR, pstCfgReadEdid->u32RegAddr, pstCfgReadEdid->u32RegAddrCount, pData, pstCfgReadEdid->u32ReadNumber);
        if (s32Ret != HI_SUCCESS)
        {
            printf("call HI_I2C_Read failed.\n");
            HI_UNF_I2C_DeInit();
            return s32Ret;
        }
    }
    else  if (0x10 == pData[126])
    {
        printf("VTB_EXT extern block\n");
    }
    else  if (0x40 == pData[126])
    {
        printf("DI_EXT extern block\n");
    }
    else  if (0x50 == pData[126])
    {
        printf("LS_EXT extern block\n");
    }
    else  if (0x60 == pData[126])
    {
        printf("DPVL_EXT extern block\n");
    }
    else  if (0xf0 == pData[126])
    {
        printf(" extern block map\n");
    }
    else  if (0xff == pData[126])
    {
        printf(" extern block defined by the display manufacturer\n");
    }
    else
    {
        printf(" extern block err\n");
    }

    HI_UNF_I2C_DeInit();
    return HI_SUCCESS;
}
HI_VOID Show_EDIDData(HI_U8 *pu8EdidData,HI_U32 u32EdidLengh)
{
    HI_U32 i= 0;
    printf("----------edid date start------------\n");
    for (i = 0; i < u32EdidLengh; i++)
    {
        printf("%02x ", pu8EdidData[i]);
        if (0 == ((i + 1) % 16))        
        {           
            printf("\n");       
        }
    }
    printf("----------edid date end------------\n");
}
HI_VOID Show_DetailTiming(HI_UNF_EDID_TIMING_S*  pstDetailTiming)
{
    printf("\n***Customer Detailed Timing***\nVFB\t\t: %d,\nVBB\t\t: %d,\nVACT\t\t: %d,\nHFB\t\t: %d,\nHBB\t\t: %d,\nHACT\t\t: %d,\nVPW\t\t: %d,\nHPW\t\t: %d,\nIDV\t\t: %d,\nIHS\t\t: %d,\nIVS\t\t: %d,\npixel_clock\t: %dkHz\n", \
                  pstDetailTiming->u32VFB, \
                  pstDetailTiming->u32VBB, \
                  pstDetailTiming->u32VACT, \
                  pstDetailTiming->u32HFB, \
                  pstDetailTiming->u32HBB, \
                  pstDetailTiming->u32HACT, \
                  pstDetailTiming->u32VPW, \
                  pstDetailTiming->u32HPW, \
                  pstDetailTiming->bIDV, \
                  pstDetailTiming->bIHS, \
                  pstDetailTiming->bIVS, \
                  pstDetailTiming->u32PixelClk) ;
    printf("----------------end------------------\n" );
}

HI_VOID Show_SimpleTiming(HI_UNF_EDID_SIMPLE_TIMING_S*  pstSimpleTiming)
{
    printf("%dx%d@%d[%d]->%d\n",
                  pstSimpleTiming->u32Hact, \
                  pstSimpleTiming->u32Vact, \
                  pstSimpleTiming->u32VerFreq, \
                  pstSimpleTiming->enTimingAttr, \
                  pstSimpleTiming->enTimingType);
}

HI_S32 Test_Edid_UNF_Prase(HI_U8* pu8EdidData, HI_U32 u32EdidLengh)
{
    HI_S32 Ret = HI_FAILURE;
    HI_U32   i  = 0;
    HI_UNF_EDID_INFO_S stEdidInfo;
    Show_EDIDData(pu8EdidData,u32EdidLengh);

    Ret = HI_UNF_EDID_EdidParse(pu8EdidData, u32EdidLengh, &stEdidInfo);
    if (Ret != HI_SUCCESS)
    {
        printf("EDID_EdidPrase  err %d.\n", Ret);
        return HI_FAILURE;
    }
    
    printf("Version :%d.%d\n", stEdidInfo.stEDIDBaseInfo.u8Version, stEdidInfo.stEDIDBaseInfo.u8Revision );
    printf("MfName :%s\n", stEdidInfo.stEDIDBaseInfo.stMfrsInfo.u8MfrsName);
    printf("SerialNum :%d\n", stEdidInfo.stEDIDBaseInfo.stMfrsInfo.u32SerialNumber);
    printf("ProductCode :%d\n",  stEdidInfo.stEDIDBaseInfo.stMfrsInfo.u32ProductCode);
    printf("SerialNum :%d\n", stEdidInfo.stEDIDBaseInfo.stMfrsInfo.u32SerialNumber);
    printf("MfYear :%d\n", stEdidInfo.stEDIDBaseInfo.stMfrsInfo.u32Year);
    printf("MfWeek :%d\n", stEdidInfo.stEDIDBaseInfo.stMfrsInfo.u32Week);
    printf("VideoPort :%d\n", stEdidInfo.enVideoPort);

    printf("support  fmt:\n");
    for ( i = 0; i < HI_UNF_ENC_FMT_BUTT ; i++)
    {
        if (stEdidInfo.stEDIDBaseInfo.bSupportFormat[i])
            printf("%d,", i);
    }
    printf("\n");
    
    printf("------------Native  Format  --------%d\n",stEdidInfo.stEDIDBaseInfo.enNativeFormat);
    printf("------------Perfer Timing---------------\n ");
    Show_DetailTiming(&stEdidInfo.stEDIDBaseInfo.stPerferTiming);
        
    printf("\nSimpleTimingNum :%d\n", stEdidInfo.u32SimpleTimingNum);
    printf("DetailTimingNum :%d\n", stEdidInfo.u32DetailTimingNum);

    /*only one member */

    for (i = 0; i < stEdidInfo.u32SimpleTimingNum; i++)
    { 
        Show_SimpleTiming(&(stEdidInfo.pstSimpleTiming[i])); 
    }
    for (i = 0; i < stEdidInfo.u32DetailTimingNum; i++)
    { 
        Show_DetailTiming(&stEdidInfo.pstDetailTiming[i].stTiming); 
    }

    HI_UNF_EDID_EdidRelease(&stEdidInfo);
    return HI_SUCCESS;
}


HI_S32 Test_Edid_MPI_Prase(HI_U8* pu8EdidData, HI_U32 u32EdidLengh)
{
    struct list_head* pos = HI_NULL;
    HI_S32 Ret  = HI_FAILURE;
    EDID_INFO_S stEdidInfo;
    EDID_DETAIL_TIMING_S*  pstDetailTimingList;
    EDID_SIMPLE_TIMING_S*  pstSimpleTimingList;

    Show_EDIDData(pu8EdidData,u32EdidLengh);
    
    Ret = HI_MPI_EDID_EdidParse(pu8EdidData, u32EdidLengh, &stEdidInfo);
    if (Ret != HI_SUCCESS)
    {
        printf("EDID_EdidPrase  err %d.\n", Ret);
        return Ret;
    }
    printf("Version :%d.%d\n", stEdidInfo.stVersion.u8Version, stEdidInfo.stVersion.u8Revision );
    printf("MfName :%s\n", stEdidInfo.stVendor.cMfName);
    printf("MonitorName :%s\n", stEdidInfo.stVendor.pMonitorName);
    printf("MonitorSerialNum :%s\n", stEdidInfo.stVendor.pMonitorSerialNum);
    printf("ProductCode :%d\n", stEdidInfo.stVendor.u16ProductCode);
    printf("SerialNum :%d\n", stEdidInfo.stVendor.u32SerialNum);
    printf("MfYear :%d\n", stEdidInfo.stVendor.u32MfYear);
    printf("MfWeek :%d\n", stEdidInfo.stVendor.u32MfWeek);
    printf("port :%d\n", stEdidInfo.enVideoPort);
    printf("InputSignalType :%d\n", stEdidInfo.stDevDispInfo.enInputSignalType);
    printf("SignalLevel :%d\n", stEdidInfo.stDevDispInfo.enSignalLevel);
    printf("DisplayType :%d\n", stEdidInfo.stDevDispInfo.enDisplayType);
    printf("ImgeWMax :%d\n", stEdidInfo.stDevDispInfo.u32ImgeWMax);
    printf("ImgeHMax :%d\n", stEdidInfo.stDevDispInfo.u32ImgeHMax);
    printf("Gamma :%d\n", stEdidInfo.stDevDispInfo.u32Gamma);
    printf("ColorDepth :%d\n", stEdidInfo.stDevDispInfo.enColorDepth);
    printf("ColorEncoding :%d\n", stEdidInfo.stDevDispInfo.enColorEncoding);

    printf("SimpleTimingNum :%d\n", stEdidInfo.u32SimpleTimingNum);
    printf("DetailTimingNum :%d\n", stEdidInfo.u32DetailTimingNum);

    if (HI_NULL != stEdidInfo.pstSimpleTimingList)
    {
        pstSimpleTimingList = stEdidInfo.pstSimpleTimingList;
        pos = &pstSimpleTimingList->head;
        do
        {
            pstSimpleTimingList = list_entry(pos, EDID_SIMPLE_TIMING_S, head);
            Show_SimpleTiming(&pstSimpleTimingList->stSimpleTiming);
            pos = pos->next;
        }
        while (pos != &(stEdidInfo.pstSimpleTimingList->head));
    }


    if (NULL != stEdidInfo.pstDetailTimingList )
    {

        pstDetailTimingList = stEdidInfo.pstDetailTimingList;
        pos = &pstDetailTimingList->head;
        do
        {
            pstDetailTimingList = list_entry(pos, EDID_DETAIL_TIMING_S, head);
            Show_DetailTiming(&pstDetailTimingList->stDetailTiming.stTiming);
            pos = pos->next;
        }
        while (pos != &(stEdidInfo.pstDetailTimingList->head));
       
    }
    else
    {
        printf("---------------no Detail Timing------------------\n");
    }

    printf("---------------pstExitenInfo start-------------------\n");
    if (NULL != stEdidInfo.pstExitenInfo)
    {
        printf("block :%d\n", stEdidInfo.pstExitenInfo->block);
        printf("cec_id :%d\n", stEdidInfo.pstExitenInfo->u16CEC_ID);
        if (stEdidInfo.pstExitenInfo->pstExitensionOther )
        {
            printf("stExitensionOther.entype :%d\n", stEdidInfo.pstExitenInfo->pstExitensionOther->enExtenType);
        }

        if (stEdidInfo.pstExitenInfo->pstAudioInfo )
        {
            printf("audio sample_rate :%d\n", stEdidInfo.pstExitenInfo->pstAudioInfo->u8SampleRate); 
        }
        if (stEdidInfo.pstExitenInfo->pstVideoTiming )
        { 
            printf("TimingType :%d\n", stEdidInfo.pstExitenInfo->pstVideoTiming->enTimingType); 
        }

        if (stEdidInfo.pstExitenInfo )
        { 
            printf("Version :%d\n", stEdidInfo.pstExitenInfo->u8Version); 
        }

        if (stEdidInfo.pstExitenInfo )
        { 
            printf("Speaker :%d\n", stEdidInfo.pstExitenInfo->u32Speaker); 
            }
    }
    else
    {
        printf("stExitenInfo   -----NULL-----------------------------\n");
    }
    printf("stExitenInfo   -----end-----------------------------\n");

    HI_MPI_EDID_EdidRelease(&stEdidInfo);
    return HI_SUCCESS;

}

HI_VOID PLUG_Process(HI_VOID)
{

    HI_S32 nRet;
    HI_U8 u8EdidData[512];
    EDID_INFO_S stEdidInfo;

    CFG_READ_EDID_S stCfgReadEdid;
    printf("*****VGA interface plug ***********in******* \n");
    
    stCfgReadEdid.u32DeviceAddress = VGA_I2C_ADDR;
    stCfgReadEdid.u32RegAddr = 0;
    stCfgReadEdid.u32RegAddrCount = 1;
    stCfgReadEdid.u32ReadNumber = 128;

    nRet = VGA_ReadEDID(&stCfgReadEdid, &u8EdidData[0]);
    if (nRet != HI_SUCCESS)
    {
        printf(" VGA_ReadEDID err!\n");
        return ;
    }

    nRet = HI_MPI_EDID_EdidParse(&u8EdidData[0], stCfgReadEdid.u32ReadNumber, &stEdidInfo);
    if (nRet != HI_SUCCESS)
    {
        printf("EDID_EdidPrase  err %d.\n", nRet);
        return;
    }
    printf("Version :%d.%d\n", stEdidInfo.stVersion.u8Version, stEdidInfo.stVersion.u8Revision );
    printf("MfName :%s\n", stEdidInfo.stVendor.cMfName);
    printf("MonitorName :%s\n", stEdidInfo.stVendor.pMonitorName);
    printf("MonitorSerialNum :%s\n", stEdidInfo.stVendor.pMonitorSerialNum);
    printf("ProductCode :%d\n", stEdidInfo.stVendor.u16ProductCode);
    printf("SerialNum :%d\n", stEdidInfo.stVendor.u32SerialNum);
    printf("MfYear :%d\n", stEdidInfo.stVendor.u32MfYear);
    printf("MfWeek :%d\n", stEdidInfo.stVendor.u32MfWeek);
    printf("port :%d\n", stEdidInfo.enVideoPort);
    printf("InputSignalType :%d\n", stEdidInfo.stDevDispInfo.enInputSignalType);
    printf("SignalLevel :%d\n", stEdidInfo.stDevDispInfo.enSignalLevel);
    printf("DisplayType :%d\n", stEdidInfo.stDevDispInfo.enDisplayType);
    printf("ImgeWMax :%d\n", stEdidInfo.stDevDispInfo.u32ImgeWMax);
    printf("ImgeHMax :%d\n", stEdidInfo.stDevDispInfo.u32ImgeHMax);
    printf("Gamma :%d\n", stEdidInfo.stDevDispInfo.u32Gamma);
    printf("ColorDepth :%d\n", stEdidInfo.stDevDispInfo.enColorDepth);
    printf("ColorEncoding :%d\n", stEdidInfo.stDevDispInfo.enColorEncoding);

    HI_MPI_EDID_EdidRelease(&stEdidInfo);

}
HI_VOID unPLUG_Process(HI_VOID)
{
     printf("*****VGA interface plug **********out******* \n");
}

HI_VOID VGACheckTthread(HI_VOID* args)
{
    HI_S32                Ret;
    HI_BOOL bReadBitVal;

    while (!g_bStopTsThread)
    {
        Ret = HI_UNF_GPIO_ReadBit(VGA_CHECK_PIN, &bReadBitVal);
        if (HI_SUCCESS != Ret)
        {
            printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, Ret);
            return;
        }
        
        if ((VGA_UNPLUG == g_bVGAStatus) && (bReadBitVal))
        {
            g_bVGAStatus  = VGA_PLUG;
            printf("VGA PLUG IN !\n");
            PLUG_Process();
        }
        else if ((VGA_PLUG == g_bVGAStatus) && (!bReadBitVal))
        {
            g_bVGAStatus  = VGA_UNPLUG;
            printf("VGA PLUG OUT !\n");
            unPLUG_Process();
        }
        else
        {
            //printf("VGA status no change !\n");
        }
        
        usleep(80 * 1000);
    }

    return;
}


HI_VOID VGA_PLUG_CheckInit(HI_VOID)
{
    HI_S32 Ret;
    

    HI_SYS_WriteRegister( CV200GPIO2_0MODE_REG_ADDR,  CV200GPIO2_0MODE_VALUE);/*GPIO 2_0  GPIO mode*/
    
    Ret = HI_UNF_GPIO_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, Ret);
        return;
    }
    Ret = HI_UNF_GPIO_SetDirBit(VGA_CHECK_PIN, HI_TRUE);
    if (HI_SUCCESS != Ret)
    {
        printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, Ret);
        return;
    }
    pthread_create(&g_VGAThd, HI_NULL, (HI_VOID*)VGACheckTthread, HI_NULL);
    g_bStopTsThread = HI_FALSE;

}
HI_VOID VGA_PLUG_CheckDeInit(HI_VOID)
{
    HI_S32 Ret;
    
    g_bStopTsThread = HI_TRUE;
    pthread_join(g_VGAThd, HI_NULL);
    
    Ret = HI_UNF_GPIO_DeInit();
    if (HI_SUCCESS != Ret)
    {
        printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, Ret);
    }
}

HI_S32 main(HI_S32 argc, HI_CHAR* argv[])
{
    static FILE *fp = NULL;
    HI_S32 nRet;
    HI_U32 u32Size;
    HI_U8 u8TestEdidData[514];
    CFG_READ_EDID_S stCfgReadEdid;
    HI_UNF_DISP_INTF_S stIntf[2];
    HI_CHAR InputCmd[32];
    HI_UNF_DISP_E enDisp = HI_UNF_DISPLAY1;
    HI_UNF_ENC_FMT_E enFormat = HI_UNF_ENC_FMT_VESA_1680X1050_60_RB;

    if (argc >= 2)
    {
        fp=fopen(argv[1], "r");
        if (HI_NULL == fp)
        {        
            printf("Usage: samle_edid file \n");
            printf("Example:./samle_edid /mnt/VGAedid.bin\n");   
           return HI_FAILURE;        
        }

        fseek(fp, 0, SEEK_SET);        
        fseek(fp, 0, SEEK_END);                
        u32Size = ftell(fp);        
        fseek(fp, 0, SEEK_SET);                
        if((128 <= u32Size)&& (513 >= u32Size))
        {            
            printf("\n\n****Open EDID size=%d****\n\n",u32Size);        
        }        
        else        
        {            
            printf("\n\n****file error size=%d****\n\n",u32Size);        
        }        
        fread(u8TestEdidData,1, u32Size, fp);
        fclose(fp);
        stCfgReadEdid.u32ReadNumber = u32Size;

        Show_EDIDData(u8TestEdidData,u32Size);
    }
    (HI_VOID)HI_SYS_Init();
    
    nRet = HI_UNF_DISP_Init();
    if (nRet != HI_SUCCESS)
    {
        printf("call HI_UNF_DISP_Init failed.\n");
        return nRet;
    }

    stIntf[0].enIntfType                = HI_UNF_DISP_INTF_TYPE_VGA;
    stIntf[0].unIntf.stYPbPr.u8DacY     = 2;
    stIntf[0].unIntf.stYPbPr.u8DacPb    = 1;
    stIntf[0].unIntf.stYPbPr.u8DacPr    = 0;

    stIntf[1].enIntfType                = HI_UNF_DISP_INTF_TYPE_HDMI;
    stIntf[1].unIntf.enHdmi             = HI_UNF_HDMI_ID_0;
    nRet = HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY1, &stIntf[0], 2);
    if (HI_SUCCESS != nRet)
    {
        printf("call HI_UNF_DISP_SetFormat failed, Ret=%#x.\n", nRet);
        goto EXIT3;
    }

    nRet = HI_UNF_DISP_SetFormat(enDisp, enFormat);
    if (HI_SUCCESS != nRet)
    {
        printf("call HI_UNF_DISP_SetFormat failed, Ret=%#x.\n", nRet);
        goto EXIT3;
    }

    nRet = HI_UNF_DISP_Open(HI_UNF_DISPLAY1);
    if (nRet != HI_SUCCESS)
    {
        printf("call HI_UNF_DISP_Open failed.\n");
        goto EXIT1;
    }

    nRet = HIADP_HDMI_Init(HI_UNF_HDMI_ID_0, enFormat);
    if (HI_SUCCESS != nRet)    
    {
        printf("call HIADP_HDMI_Init failed, Ret=%#x.\n", nRet);
        goto EXIT1;
    }
    
    VGA_PLUG_CheckInit();
    memset(&stCfgReadEdid,0x0,sizeof(CFG_READ_EDID_S));
    while (1)
    {
        printf("please select EDID test !\n");
        printf("    0  Read VGA EDID  \n");
        printf("    1  Read DVI/HDMI EDID  \n");
        printf("    2  EDID MPI Parse\n");
        printf("    3  EDID UNF Parse\n");
        printf("please input 'q' to quit!\n");
        SAMPLE_GET_INPUTCMD(InputCmd);
        
        if ('0'== InputCmd[0])
        {
            stCfgReadEdid.u32DeviceAddress = VGA_I2C_ADDR;
            stCfgReadEdid.u32RegAddr = 0;
            stCfgReadEdid.u32RegAddrCount = 1;
            stCfgReadEdid.u32ReadNumber = 128;

            nRet = VGA_ReadEDID(&stCfgReadEdid, &u8TestEdidData[0]);
            if (nRet == HI_SUCCESS)
            {
                Show_EDIDData(u8TestEdidData,stCfgReadEdid.u32ReadNumber);
                SaveDateToFile("/mnt/VGAedid.bin", u8TestEdidData, stCfgReadEdid.u32ReadNumber);
            }
            else
            {
                printf(" Read VGA EDID err!\n");
            }
        }
        else if ('1'== InputCmd[0])
        {
            memset(u8TestEdidData,0x0,sizeof(u8TestEdidData));
            HI_UNF_HDMI_ReadEDID(u8TestEdidData, &stCfgReadEdid.u32ReadNumber);
            if (nRet == HI_SUCCESS)
            {
                Show_EDIDData(u8TestEdidData,stCfgReadEdid.u32ReadNumber);
                SaveDateToFile("/mnt/HDMIedid.bin", u8TestEdidData, stCfgReadEdid.u32ReadNumber);
            }
            else
            {
                printf(" Read HDMI EDID err!\n");
            }
        }
        else if ('2' == InputCmd[0])
        {
            Test_Edid_MPI_Prase(&u8TestEdidData[0], stCfgReadEdid.u32ReadNumber);
        }
        else if ('3'== InputCmd[0])
        {
            Test_Edid_UNF_Prase(&u8TestEdidData[0], stCfgReadEdid.u32ReadNumber);
        }

        if ('q'== InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
    }
    

    VGA_PLUG_CheckDeInit();
 EXIT1:   
    nRet = HI_UNF_DISP_Close(HI_UNF_DISPLAY1);
    if (nRet != HI_SUCCESS)
    {
        printf("call HI_UNF_DISP_Close failed, Ret=%#x.\n", nRet);
        return nRet;
    }

    nRet = HI_UNF_DISP_Close(HI_UNF_DISPLAY0);
    if (nRet != HI_SUCCESS)
    {
        printf("call HI_UNF_DISP_Close failed, Ret=%#x.\n", nRet);
        return nRet;
    }
EXIT3:
    nRet = HI_UNF_DISP_DeInit();
    if (nRet != HI_SUCCESS)
    {
        printf("call HI_UNF_DISP_DeInit failed, Ret=%#x.\n", nRet);
        return nRet;
    }
    
    (HI_VOID) HIADP_HDMI_DeInit(HI_UNF_HDMI_ID_0);
    (HI_VOID) HI_SYS_DeInit();
    return nRet;
}


