#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <dirent.h>
#include <sys/stat.h>

#include "hi_adp_mpi.h"
#include "hi_unf_voip.h"
#include "hi_unf_sound.h"
//#include "hi_bluetooth.h"
//#include "hi_usbphone.h"


#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf
#else
#define sample_printf printf
#endif

#define MAX_FILE_LEN (5*1024*1024)

/*----------------------------------------------------------------------------------------------*/
//#define ENABLE_AUDIO_DEVICE_MONITOR

#define HI_AUD_DEV_LIST_MAX 10

typedef enum
{
    HI_VOIP_AUD_DEV_TYPE_SLIC = 0,
    HI_VOIP_AUD_DEV_TYPE_BLUETOOTH,      
    HI_VOIP_AUD_DEV_TYPE_USB_PHONE,       
    HI_VOIP_AUD_DEV_TYPE_SNDCARD,       
    HI_VOIP_AUD_DEV_TYPE_BUTT
}HI_VOIP_AUDIO_DEVICE_TYPE_E;

typedef struct
{
    HI_U32 u32BusNum;
    HI_U32 u32DevNum;
    HI_U32 u32VendorId;                         /*  */
    HI_U32 u32ProductId;                        /*  */
}USB_DEV_INFO_S;

typedef struct
{
    HI_U32 u32VendorId;                         /*  */
    HI_U32 u32ProductId;                        /*  */
}USB_PRODUCT_INFO_S;

typedef struct
{
    HI_U32 u32AudDevId;                         /* HI_UNF_VOIP_AUDIO_DEVICE_E */
    HI_S32 s32SndCardNo;                        /* ALSA sound card number */
    HI_U32 u32AudDevTpye;                       /* HI_VOIP_AUDIO_DEVICE_TYPE_E */
    HI_CHAR szName[HI_ALSA_AUD_DEV_NAME_LEN];   /*card name*/
}HI_AUD_DEV_INFO_S;

typedef struct
{
    HI_U32 u32AudDevId;                         /* HI_UNF_VOIP_AUDIO_DEVICE_E */
    HI_U32 u32AudDevTpye;                       /* HI_VOIP_AUDIO_DEVICE_TYPE_E */
    HI_S32 s32InSndCardNo;                      /* ALSA sound card number */
    HI_S32 s32InFlag;                           /*0--invalid 1--valid*/
    HI_CHAR szInName[HI_ALSA_AUD_DEV_NAME_LEN]; /*card name*/
    HI_S32 s32OutSndCardNo;                     /* ALSA sound card number */
    HI_S32 s32OutFlag;                          /*0--invalid 1--valid*/
    HI_CHAR szOutName[HI_ALSA_AUD_DEV_NAME_LEN];/*card name*/
}HI_AUD_DEV_TOTAL_INFO_S;   


static const HI_CHAR *szTypeStr[HI_VOIP_AUD_DEV_TYPE_BUTT]={
    "SLIC",
    "BLUETOOTH",
    "USBPHONE",
    "SNDCARD"     //this type support  arbitrary combination
};

static HI_S32 s32SlicFlag = 0;
static HI_U32 u32AudInDevNum = 0;
static HI_U32 u32AudOutDevNum = 0;
static HI_AUD_DEV_INFO_S stAudevInList[HI_AUD_DEV_LIST_MAX];
static HI_AUD_DEV_INFO_S stAudevOutList[HI_AUD_DEV_LIST_MAX];
static HI_AUD_DEV_TOTAL_INFO_S stAudDevSel;
static HI_S32 s32InitVolume = 100;
static HI_S32 s32Gain = 0;

#ifdef ENABLE_AUDIO_DEVICE_MONITOR

#define AUDDEV_NAME_LEN 50
static HI_CHAR s_acInAudDevName[AUDDEV_NAME_LEN] = "unknow";
static HI_CHAR s_acOutAudDevName[AUDDEV_NAME_LEN] = "unknow";

typedef struct
{
    pthread_t   tThread;
    pthread_mutex_t  tMutex;
    HI_U32   u32RunFlag;
    HI_U32   u32Used;
} AUDDEV_MONITOR_THREAD_STRU;

static AUDDEV_MONITOR_THREAD_STRU stThreadAudDevMonitor;

#define HI_AUD_DEV_LOCK()     (void)pthread_mutex_lock(&stThreadAudDevMonitor.tMutex);
#define HI_AUD_DEV_UNLOCK()   (void)pthread_mutex_unlock(&stThreadAudDevMonitor.tMutex);

#else

#define HI_AUD_DEV_LOCK()
#define HI_AUD_DEV_UNLOCK()

#endif

/*----------------------------------------------------------------------------------------------*/


static HI_UNF_VOIP_CHN_ATTR_S  stChAttr;
static HI_U32  hVoipHandle;
static HI_U8   u8VoipFuncSel = 0;            //function select , 0-- Normal 1-- Play Announcement
//static HI_VOIP_AUDIO_DEVICE_TYPE_E enAudDevType = HI_VOIP_AUD_DEV_TYPE_SLIC;       // 0 -- SIO (SLIC)  1--Bluetooth  2--USB MIC+HIAO
static HI_U8   u8SrcIp[4] = {10,67,222,182};
static HI_U8   u8DstIp[4] = {10,67,222,182};
static HI_U16  u16VoipSrcPort = 8100;
static HI_U16  u16VoipDstPort = 8100;


static HI_CHAR cFileName[64]="love1999.wav";  // The default audio file for play announcement.
static HI_U8 * pu8AudioFileAddr = NULL;
static HI_S32  s32AudioFileLen;
static FILE *fp = NULL;

static HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S    stAnnAttr;

HI_S32  Sample_NetPara_Input(HI_VOID)
{
    HI_CHAR cTemp[128];

    /*input IP*/ /*CNcomment:输入IP地址*/
    {
        HI_U8 j=0;
        HI_U32 data[4];
        HI_U8 type = 0;
        HI_U8 num = 0;    /*the number of input data*/ /*CNcomment:输入的数字的数目*/

        while(1)
        {
            memset(cTemp,0,sizeof(cTemp));
            memset(data,0,sizeof(data));
            j = 0;
            
            if(type == 0)
                printf("Please input Source IP , format is 192.168.1.10,'q' to use default setting.\n");
            else if(type == 1)
                printf("Please input Dest IP , format is 192.168.1.10.\n");
            else
                break;
            
            num = scanf("%u.%u.%u.%u",&data[0],&data[1],&data[2],&data[3]);
            if(num < 4)
            {
                SAMPLE_GET_INPUTCMD(cTemp);
                if((num == 0)&&(cTemp[0]=='q')&&(type == 0))
                {
                    break;
                }
                else
                {
                    sample_printf("\nInvalid input.\n");
                }
            }
            else
            {
                if(type == 0)
                {
                    for(j=0;j<4;j++)
                        u8SrcIp[j] = data[j];
                }
                else if(type == 1)
                {
                    for(j=0;j<4;j++)
                        u8DstIp[j] = data[j];
                }
                type++;
            }
        }
        sample_printf("Src IP %d:%d:%d:%d \n",u8SrcIp[0],u8SrcIp[1],u8SrcIp[2],u8SrcIp[3]);
        sample_printf("Dest IP %d:%d:%d:%d \n",u8DstIp[0],u8DstIp[1],u8DstIp[2],u8DstIp[3]);
    }
    sleep(1);    
    return HI_SUCCESS;
}

static HI_S32   Sample_Voip_SetNetPara(HI_UNF_NET_CONFIG_PARA_S *pstNetCfg)
{
    HI_UNF_NET_CONFIG_BODY_S    *pstNetPara = NULL;
    HI_UNF_NET_CHANGE_FLAG_S    *pstNetFlag = NULL;

    if(pstNetCfg == NULL)
    {
        sample_printf("null pointer pstNetCfg\n");
        return HI_FAILURE;
    }

    pstNetPara = &pstNetCfg->stBody;
    pstNetFlag = &pstNetCfg->stChange;
    
    pstNetFlag->bit1SrcIP = 1;
    pstNetPara->u32SrcIPLen = sizeof(u8SrcIp);
    memcpy(pstNetPara->u8SrcIP,u8SrcIp,sizeof(u8SrcIp));
    pstNetFlag->bit1DstIP = 1;
    pstNetPara->u32DstIPLen = sizeof(u8DstIp);
    memcpy(pstNetPara->u8DstIP,u8DstIp,sizeof(u8DstIp));
    pstNetFlag->bit1SrcPort= 1;
    pstNetPara->u16SrcPort = u16VoipSrcPort;
    pstNetFlag->bit1DstPort= 1;
    pstNetPara->u16DstPort= u16VoipDstPort;
    
    return HI_SUCCESS;
}

HI_S32 Sample_Voip_EventCallBack(HI_HANDLE hVoip, HI_UNF_VOIP_EVENT_E enEvent, HI_S32 s32EventValue, HI_U32 u32Args)
{
    sample_printf("%s(), handle 0x%x, event type %d, event value %d, args 0x%x\n",__FUNCTION__,hVoip,enEvent,s32EventValue,u32Args);
    return HI_SUCCESS;
}

HI_S32 Sample_AudAdp_EventCallBack(HI_UNF_AUDADP_EVENT_S *pstAudadpEvent)
{
    sample_printf("%s(), Audio%sDevId %d, Event %d, Status %d\n",__FUNCTION__,
        (pstAudadpEvent->enAudioDevType==HI_UNF_VOIP_AUD_IN_DEV)?"In":"Out",
         pstAudadpEvent->s32AudioDevId,
         pstAudadpEvent->enEvent,
         pstAudadpEvent->enStatus);
    return HI_SUCCESS;
}

HI_S32 Sample_Voip_Load_AudioFile(HI_VOID)
{

    fp = NULL;
    pu8AudioFileAddr = NULL;
    
    pu8AudioFileAddr = malloc(MAX_FILE_LEN);
    if (NULL == pu8AudioFileAddr)
    {
        sample_printf("%s %d Voip malloc failure!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    /*fill with data from play file*/ /*CNcomment:填写播放文件的数据*/
    fp = fopen(cFileName, "rb");
    if (NULL == fp)
    {
        free(pu8AudioFileAddr);
        pu8AudioFileAddr = NULL;
        sample_printf("%s %d open audio file %s failure!\n",__FUNCTION__,__LINE__,cFileName);
        return HI_FAILURE;
    }
    
    s32AudioFileLen = fread(pu8AudioFileAddr, 1, MAX_FILE_LEN, fp);
    if (s32AudioFileLen <= 0)
    {
        fclose(fp);
        free(pu8AudioFileAddr);
        fp = NULL;
        pu8AudioFileAddr = NULL;
        sample_printf("%s %d read audio file %s failure!\n",__FUNCTION__,__LINE__,cFileName);
        return HI_FAILURE;
    }

    sample_printf("read audio file %s success, len:%d addr:0x%x\n", cFileName,s32AudioFileLen, (HI_U32)pu8AudioFileAddr);
    return HI_SUCCESS;
}

HI_VOID Sample_Voip_Close_AudioFile(HI_VOID)
{
    if(fp!=NULL)
    {
        fclose(fp);
    }
    if(pu8AudioFileAddr != NULL)
    {
        free(pu8AudioFileAddr);
    }
    fp = NULL;
    pu8AudioFileAddr = NULL;
}

HI_S32 Sample_Voip_GetValidRateMax(HI_U32 u32RateMin,HI_U32 u32RateMax,HI_U32 *pu32Rate)
{
    HI_U32 i;
    HI_U32 u32SampleRateList[4]={48000,32000,16000,8000};
    
    if(u32RateMin > u32RateMax)
        return HI_FAILURE;
    
    for(i=0;i<4;i++)
    {
        if((u32SampleRateList[i]>=u32RateMin)&&(u32SampleRateList[i]<=u32RateMax))
        {
            *pu32Rate = u32SampleRateList[i];
            return HI_SUCCESS;
        }
    }
    return HI_FAILURE;   
}

HI_S32 Sample_Voip_GetValidRateMin(HI_U32 u32RateMin,HI_U32 u32RateMax,HI_U32 *pu32Rate)
{
    HI_U32 i;
    HI_U32 u32SampleRateList[4]={8000,16000,32000,48000};
    
    if(u32RateMin > u32RateMax)
        return HI_FAILURE;
    
    for(i=0;i<4;i++)
    {
        if((u32SampleRateList[i]>=u32RateMin)&&(u32SampleRateList[i]<=u32RateMax))
        {
            *pu32Rate = u32SampleRateList[i];
            return HI_SUCCESS;
        }
    }
    return HI_FAILURE;   
}

#if 0
HI_S32 Sample_Voip_GetAudDev_Slic(HI_AUD_DEV_INFO_S * pstAudDev)
{
    if(NULL == pstAudDev)
    {
        sample_printf("%s %d , null pointer!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    if(0 == s32SlicFlag)
    {
        return HI_FAILURE;
    }
    
    pstAudDev->u32AudDevId = HI_UNF_VOIP_AUD_DEV_SIO;
    pstAudDev->s32SndCardNo = -1;
    pstAudDev->u32AudDevTpye = HI_VOIP_AUD_DEV_TYPE_SLIC;
    sprintf(pstAudDev->szName,"SLIC");
        
    return HI_SUCCESS;
}

HI_S32 Sample_Voip_GetAudDev_Bluetooth(HI_AUD_DEV_INFO_S * pstAudDev)
{
    HI_S32 ret;
    HI_BLUETOOTH_ADP_ATTR_S stBTAdp;
    HI_BLUETOOTH_DEV_ATTR_S stBTDev;
    
    if(NULL == pstAudDev)
    {
        sample_printf("%s %d , null pointer!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    ret = HI_BLUETOOTH_GetDefaultAdapter(&stBTAdp);
    if(HI_SUCCESS != ret)
        return HI_FAILURE;
    
    ret = HI_BLUETOOTH_GetConnectedHeadset(&stBTAdp, &stBTDev);
    if(HI_SUCCESS != ret)
        return HI_FAILURE;

    pstAudDev->u32AudDevId = HI_UNF_VOIP_AUD_DEV_BLUETOOTH;
    pstAudDev->s32SndCardNo = -1;
    pstAudDev->u32AudDevTpye = HI_VOIP_AUD_DEV_TYPE_BLUETOOTH;
    sprintf(pstAudDev->szName,"BLUETOOTH");

    return HI_SUCCESS;
}

HI_S32 Sample_Voip_GetUsbDevInfoBySndCardNo(HI_S32 s32SndCardNo,USB_DEV_INFO_S *pstUsbDevInfo)
{
    FILE *pf = NULL;
    HI_CHAR szFile[64];

    if(s32SndCardNo < 0)
    {
        sample_printf("%s %d, Invalid sound card number.\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }
    
    if(HI_NULL == pstUsbDevInfo)
    {
        sample_printf("%s %d, Null pointer.\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    /*get usb bus and device number*/
    memset(pstUsbDevInfo,0,sizeof(USB_DEV_INFO_S));
    memset(szFile,0,sizeof(szFile));
    sprintf(szFile,"/proc/asound/card%d/usbbus",s32SndCardNo);

    pf = fopen(szFile, "r");
    if (NULL == pf)
    {
        sample_printf("%s %d, open %s failure!\n",__FUNCTION__,__LINE__,szFile);
        return HI_FAILURE;
    }

    fscanf(pf,"%03d/%03d",&pstUsbDevInfo->u32BusNum,&pstUsbDevInfo->u32DevNum);
    fclose(pf);

    /*get vendor and product id*/
    memset(szFile,0,sizeof(szFile));
    sprintf(szFile,"/proc/asound/card%d/usbid",s32SndCardNo);

    pf = fopen(szFile, "r");
    if (NULL == pf)
    {
        sample_printf("%s %d, open %s failure!\n",__FUNCTION__,__LINE__,szFile);
        return HI_FAILURE;
    }
    fscanf(pf,"%04x:%04x",&pstUsbDevInfo->u32VendorId,&pstUsbDevInfo->u32ProductId);
    fclose(pf);

    return HI_SUCCESS;
}
#endif

HI_S32 Sample_Voip_GetAudioList(HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType, HI_AUD_DEV_INFO_S * pstAudDevList, 
                                            HI_U32 u32ListMax, HI_U32 *pu32DevNum)
{
    HI_S32 s32Ret;
    HI_ALSA_CARD_INFO_S stAlsaDevList[HI_AUD_DEV_LIST_MAX];
    HI_U32 u32Count = 0, i, j;
    HI_AUD_DEV_INFO_S *pstAudDev = NULL;
#if 0
    USB_DEV_INFO_S stUsbDevInfo;
    const USB_PRODUCT_INFO_S usbphonelist[]={{0xdada,0xb001}};
#endif

    if((NULL == pstAudDevList)||(NULL == pu32DevNum))
    {
        sample_printf("%s %d , null pointer!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }
    
    if(u32ListMax == 0)
    {
        sample_printf("%s %d , invalid para, u32ListMax is %d!\n",__FUNCTION__,__LINE__,u32ListMax);
        return HI_FAILURE;
    }

    HI_AUD_DEV_LOCK();
    memset(pstAudDevList,0,sizeof(HI_AUD_DEV_INFO_S)*u32ListMax);
    pstAudDev = &pstAudDevList[0];
    *pu32DevNum = 0;

#if 0  
    /* slic */
    s32Ret = Sample_Voip_GetAudDev_Slic(pstAudDev);
    if(HI_SUCCESS == s32Ret)
    {
       pstAudDev++;
       (*pu32DevNum)++;
    }
    
    /* bluetooth */
    s32Ret = Sample_Voip_GetAudDev_Bluetooth(pstAudDev);
    if(HI_SUCCESS == s32Ret)
    {
       pstAudDev++;
       (*pu32DevNum)++;
    }
#endif

    /* ALSA device */
    memset(stAlsaDevList,0,sizeof(HI_ALSA_CARD_INFO_S)*HI_AUD_DEV_LIST_MAX);
    s32Ret = HI_ALSA_GetAudioDevList(enAudioDevType,stAlsaDevList,HI_AUD_DEV_LIST_MAX-(*pu32DevNum),&u32Count);
    if(HI_SUCCESS != s32Ret)
    {
        HI_AUD_DEV_UNLOCK();
        sample_printf("\n%s %d , Get audio in device list failure, ErrCode is %x!\n",__FUNCTION__,__LINE__,s32Ret);
        return HI_SUCCESS;
    }

    if(u32Count <= 0)
    {
        HI_AUD_DEV_UNLOCK();
        sample_printf("\n%s %d , No alsa audio device found!\n",__FUNCTION__,__LINE__);
        return HI_SUCCESS;
    }

    for(i=0; i<u32Count; i++)
    {
        pstAudDev->u32AudDevId = HI_UNF_VOIP_AUD_DEV_ALSA;
        pstAudDev->s32SndCardNo = stAlsaDevList[i].s32CardNo;
        strcpy(pstAudDev->szName,stAlsaDevList[i].szName);
        if(0 == strcmp(pstAudDev->szName, "HISI-AIAO"))   
        {
            pstAudDev->s32SndCardNo = -1;   //for voip sdk code being not modified
        }
        
        pstAudDev->u32AudDevTpye = HI_VOIP_AUD_DEV_TYPE_SNDCARD;
#if 0
        s32Ret = Sample_Voip_GetUsbDevInfoBySndCardNo(stAlsaDevList[i].s32CardNo, &stUsbDevInfo);
        if(HI_SUCCESS == s32Ret)
        {
            for(j=0;j<sizeof(usbphonelist)/sizeof(USB_PRODUCT_INFO_S);j++)
            {
                if((usbphonelist[j].u32VendorId == stUsbDevInfo.u32VendorId)
                    &&(usbphonelist[j].u32ProductId == stUsbDevInfo.u32ProductId))
                {
                    pstAudDev->u32AudDevTpye = HI_VOIP_AUD_DEV_TYPE_USB_PHONE;
                    break;
                }
            }
        }
#endif   
        pstAudDev++;
        (*pu32DevNum)++;
    }
    HI_AUD_DEV_UNLOCK();
    
    usleep(200*1000);
    
    return HI_SUCCESS;
}

HI_S32 Sample_Voip_SelectAudDevByName(HI_AUD_DEV_INFO_S * pstAudInDevList, HI_U32 u32AudInDevNum, HI_CHAR *pcAudInDevName,  
                                      HI_AUD_DEV_INFO_S * pstAudOutDevList,HI_U32 u32AudOutDevNum,HI_CHAR *pcAudOutDevName, HI_AUD_DEV_TOTAL_INFO_S *pstAudDevSel)
{
    HI_U32 i = 0, j = 0;
    if((NULL == pstAudInDevList)||(NULL == pstAudInDevList)||(NULL == pstAudDevSel) 
        ||(NULL == pcAudInDevName) || (NULL == pcAudOutDevName))
    {
        sample_printf("%s %d , null pointer!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    HI_AUD_DEV_LOCK();

    pstAudDevSel->u32AudDevId = HI_UNF_VOIP_AUD_DEV_BUTT;
    pstAudDevSel->u32AudDevTpye = HI_VOIP_AUD_DEV_TYPE_BUTT;
    pstAudDevSel->s32InSndCardNo = -1;
    pstAudDevSel->s32InFlag = 0;

    pstAudDevSel->s32OutSndCardNo = -1;
    pstAudDevSel->s32OutFlag = 0;

    if(0 == u8VoipFuncSel)
    {
        if(u32AudInDevNum == 0) 
        {
            sample_printf("%s %d , invalid para, u32AudInDevNum is 0!\n",__FUNCTION__,__LINE__);
            HI_AUD_DEV_UNLOCK();
            return HI_FAILURE;
        }
    }

    if(u32AudOutDevNum == 0) 
    {
        sample_printf("%s %d , invalid para, u32AudOutDevNum is 0!\n",__FUNCTION__,__LINE__);
        HI_AUD_DEV_UNLOCK();
        return HI_FAILURE;
    }

    if(0 == u8VoipFuncSel)
    {
        for(i = 0; i < u32AudInDevNum; i++)
        {
            if(0 == strcmp(pstAudInDevList[i].szName, pcAudInDevName))
                break;
        }
        if(i == u32AudInDevNum)
        {
            sample_printf("%s %d , don't find the wanted in device(%s) !\n",__FUNCTION__,__LINE__,pcAudInDevName);
            i = 0;
        }
        pstAudDevSel->s32InSndCardNo = pstAudInDevList[i].s32SndCardNo;
        strcpy(pstAudDevSel->szInName, pstAudInDevList[i].szName);
        pstAudDevSel->s32InFlag = 1;  
    }

    for(j = 0; j < u32AudOutDevNum; j++)
    {
        if(0 == strcmp(pstAudOutDevList[j].szName, pcAudOutDevName))
            break;
    }

    if(0 == u8VoipFuncSel)
    {
        if(j < u32AudOutDevNum)
        {
            if(pstAudInDevList[i].u32AudDevTpye != pstAudOutDevList[j].u32AudDevTpye)
            {
                j = u32AudOutDevNum;
            }
        }
        if(j == u32AudOutDevNum)
        {
            for(j = 0; j < u32AudOutDevNum; j++)
            {
                if(pstAudInDevList[i].u32AudDevTpye == pstAudOutDevList[j].u32AudDevTpye)
                    break;
            }
        }    
    }
    else
    {
        if(j == u32AudOutDevNum)
        {
            j = 0;
        }
    }    

    pstAudDevSel->u32AudDevId = pstAudOutDevList[j].u32AudDevId;
    pstAudDevSel->u32AudDevTpye = pstAudOutDevList[j].u32AudDevTpye;
    pstAudDevSel->s32OutSndCardNo = pstAudOutDevList[j].s32SndCardNo;
    strcpy(pstAudDevSel->szOutName, pstAudOutDevList[j].szName);
    pstAudDevSel->s32OutFlag = 1;

    sample_printf("\nSelected audio device : DevId [%d] InType [%s]\n", pstAudDevSel->u32AudDevId, szTypeStr[pstAudDevSel->u32AudDevTpye]);

    if(1 == pstAudDevSel->s32InFlag)
    {
        sample_printf("InCardNo [%d] InName [%s]\n", pstAudDevSel->s32InSndCardNo, pstAudDevSel->szInName);
    }

    if(1 == pstAudDevSel->s32OutFlag)
    {
        sample_printf("OutCardNo [%d] OutName [%s]\n", pstAudDevSel->s32OutSndCardNo, pstAudDevSel->szOutName);
    }
    
    HI_AUD_DEV_UNLOCK();
    return HI_SUCCESS;
}

HI_S32 Sample_Voip_SelectAudDev(HI_AUD_DEV_INFO_S * pstAudInDevList, HI_U32 u32AudInDevNum, 
                                        HI_AUD_DEV_INFO_S * pstAudOutDevList, HI_U32 u32AudOutDevNum, HI_AUD_DEV_TOTAL_INFO_S *pstAudDevSel)
{
    HI_U32 i, j;
    
    if((NULL == pstAudInDevList)||(NULL == pstAudInDevList)||(NULL == pstAudDevSel))
    {
        sample_printf("%s %d , null pointer!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    HI_AUD_DEV_LOCK();

    pstAudDevSel->u32AudDevId = HI_UNF_VOIP_AUD_DEV_BUTT;
    pstAudDevSel->u32AudDevTpye = HI_VOIP_AUD_DEV_TYPE_BUTT;
    pstAudDevSel->s32InSndCardNo = 0;
    pstAudDevSel->s32InFlag = 0;

    pstAudDevSel->s32OutSndCardNo = 0;
    pstAudDevSel->s32OutFlag = 0;

    if(0 == u8VoipFuncSel)
    {
        if(u32AudInDevNum == 0) 
        {
            sample_printf("%s %d , invalid para, u32AudInDevNum is 0!\n",__FUNCTION__,__LINE__);
            HI_AUD_DEV_UNLOCK();
            return HI_FAILURE;
        }
    }

    if(u32AudOutDevNum == 0) 
    {
        sample_printf("%s %d , invalid para, u32AudOutDevNum is 0!\n",__FUNCTION__,__LINE__);
        HI_AUD_DEV_UNLOCK();
        return HI_FAILURE;
    }

    printf("\nplease select the audio device :\n");
    printf("\nInput device :\n");
    for(i=0; i<u32AudInDevNum; i++)
    {
        printf("  %d :  DevId [%d] CardNo [%d] type [%s] name [%s]\n",
            i,
            pstAudInDevList[i].u32AudDevId,
            pstAudInDevList[i].s32SndCardNo,
            szTypeStr[pstAudInDevList[i].u32AudDevTpye],
            pstAudInDevList[i].szName
            );
    }
    printf("\nOutput device :\n");
    for(i=0; i<u32AudOutDevNum; i++)
    {
        printf("  %d :  DevId [%d] CardNo [%d] type [%s] name [%s]\n",
            i,
            pstAudOutDevList[i].u32AudDevId,
            pstAudOutDevList[i].s32SndCardNo,
            szTypeStr[pstAudOutDevList[i].u32AudDevTpye],
            pstAudOutDevList[i].szName
            );
    }
    printf("\nInput Device number(for example:0 0)\n\n");

    scanf("%u %u",&i, &j);
    
    if(0 == u8VoipFuncSel)
    {
        if((i >= u32AudInDevNum)||(j >= u32AudOutDevNum))
        {
            sample_printf("Select Input Device %d, Output Device %d Failed!\n", i, j); 
            HI_AUD_DEV_UNLOCK();
            return HI_FAILURE;   
        }

        if(pstAudInDevList[i].u32AudDevId != pstAudOutDevList[j].u32AudDevId)
        {
            sample_printf("Don't Support the combination of the diffirent DevIDs !\n");
            HI_AUD_DEV_UNLOCK();
            return HI_FAILURE;   
        }

        if(pstAudInDevList[i].u32AudDevTpye != pstAudOutDevList[j].u32AudDevTpye)
        {
            sample_printf("Don't Support the combination of the diffirent DevTypes !\n"); 
            HI_AUD_DEV_UNLOCK();
            return HI_FAILURE;   
        }

        pstAudDevSel->s32InSndCardNo = pstAudInDevList[i].s32SndCardNo;
        strcpy(pstAudDevSel->szInName, pstAudInDevList[i].szName);
        pstAudDevSel->s32InFlag = 1;
    }
    else
    {   
        if(j >= u32AudOutDevNum)
         {
             sample_printf("Select Device %d Failed!\n", j); 
             HI_AUD_DEV_UNLOCK();
             return HI_FAILURE;  
         }
    }

    pstAudDevSel->u32AudDevId = pstAudOutDevList[j].u32AudDevId;
    pstAudDevSel->u32AudDevTpye = pstAudOutDevList[j].u32AudDevTpye;
    pstAudDevSel->s32OutSndCardNo = pstAudOutDevList[j].s32SndCardNo;
    strcpy(pstAudDevSel->szOutName, pstAudOutDevList[j].szName);
    pstAudDevSel->s32OutFlag = 1;
    
    HI_AUD_DEV_UNLOCK();
    return HI_SUCCESS;
}

/*Should call when ALSA device be closed*/
HI_S32 Sample_Voip_GetAudDevSampleRate(HI_AUD_DEV_TOTAL_INFO_S * pstAudDev, HI_U32 *pu32AudInRate, HI_U32 *pu32AudOutRate)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RateMin,u32RateMax;
    HI_ALSA_CARD_INFO_S stAlsaCardInfo;
    
    if((NULL == pstAudDev)||(NULL == pu32AudInRate)||(NULL == pu32AudOutRate))
    {
        sample_printf("%s %d , null pointer!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }
    HI_AUD_DEV_LOCK();

    if((HI_VOIP_AUD_DEV_TYPE_SLIC == pstAudDev->u32AudDevTpye)||(HI_VOIP_AUD_DEV_TYPE_BLUETOOTH == pstAudDev->u32AudDevTpye))
    {
        *pu32AudInRate = HI_UNF_SAMPLE_RATE_8K;
        *pu32AudOutRate = HI_UNF_SAMPLE_RATE_8K;
    }
    else if((HI_VOIP_AUD_DEV_TYPE_USB_PHONE == pstAudDev->u32AudDevTpye)||(HI_VOIP_AUD_DEV_TYPE_SNDCARD == pstAudDev->u32AudDevTpye))        
    {
        /*output device*/
        if(0 > pstAudDev->s32OutSndCardNo) //todo ao need adapt the interface of alsa get rate 
        {
            *pu32AudOutRate = HI_UNF_SAMPLE_RATE_48K;
        }
        else
        {
            stAlsaCardInfo.s32CardNo = pstAudDev->s32OutSndCardNo;
            stAlsaCardInfo.enType = HI_UNF_VOIP_AUD_OUT_DEV;
            strcpy(stAlsaCardInfo.szName,pstAudDev->szOutName);
                
            s32Ret = HI_ALSA_GetAudioDevRateRange(&stAlsaCardInfo, &u32RateMin, &u32RateMax);
            if(HI_SUCCESS != s32Ret)
            {
                sample_printf("%s %d , Get audio OUT device [%d : %s] sample rate range failure, ErrCode is %x!\n",
                    __FUNCTION__,__LINE__,
                    stAlsaCardInfo.s32CardNo,
                    stAlsaCardInfo.szName,
                    s32Ret);
            }
            else
            {
                sample_printf("Audio OUT device [%d], name [%s], rate_min [%d], rate_max[%d]\n",
                        stAlsaCardInfo.s32CardNo,
                        stAlsaCardInfo.szName,
                        u32RateMin,
                        u32RateMax);
                
                s32Ret = Sample_Voip_GetValidRateMax(u32RateMin,u32RateMax,pu32AudOutRate);
            }
        }

//modify by x00190696
//voip2.0 loop resample dosn't support 32k(inrate)-48k(outrate) or 48k(inrate)-32k(outrate)
        /*input device*/
        if(0 == pstAudDev->s32InSndCardNo)  //todo ai need adapt the interface of alsa get rate 
        {
            *pu32AudInRate = HI_UNF_SAMPLE_RATE_48K;
        }
        else
        {
            stAlsaCardInfo.s32CardNo = pstAudDev->s32InSndCardNo;
            stAlsaCardInfo.enType = HI_UNF_VOIP_AUD_IN_DEV;
            strcpy(stAlsaCardInfo.szName,pstAudDev->szInName);
               
            s32Ret = HI_ALSA_GetAudioDevRateRange(&stAlsaCardInfo, &u32RateMin, &u32RateMax);
            if(HI_SUCCESS != s32Ret)
            {
               sample_printf("%s %d , Get audio IN device [%d : %s] sample rate range failure, ErrCode is %x!\n",
                   __FUNCTION__,__LINE__,
                   stAlsaCardInfo.s32CardNo,
                   stAlsaCardInfo.szName,
                   s32Ret);
            }
            else
            {
               sample_printf("Audio IN device [%d], name [%s], rate_min [%d], rate_max[%d]\n",
                       stAlsaCardInfo.s32CardNo,
                       stAlsaCardInfo.szName,
                       u32RateMin,
                       u32RateMax);

               if (*pu32AudOutRate == HI_UNF_SAMPLE_RATE_48K)
               {
                    if (u32RateMax >= HI_UNF_SAMPLE_RATE_32K && u32RateMax < HI_UNF_SAMPLE_RATE_48K)
                    {
                        if (u32RateMin > HI_UNF_SAMPLE_RATE_16K)
                        {
                            sample_printf("voip doesn't support 32k to 48k\n");
                            return HI_FAILURE;
                        }
                        else
                        {
                            u32RateMax = HI_UNF_SAMPLE_RATE_16K;
                        }
                    }
               }
               
               if (*pu32AudOutRate == HI_UNF_SAMPLE_RATE_32K)
               {
                    if (u32RateMax >= HI_UNF_SAMPLE_RATE_48K)
                    {
                        if (u32RateMin <= HI_UNF_SAMPLE_RATE_32K)
                        {
                            u32RateMax = HI_UNF_SAMPLE_RATE_32K;
                        }
                        else
                        {
                            sample_printf("voip doesn't support 48k to 32k\n");
                            return HI_FAILURE;
                        }
                    }
               }

               s32Ret = Sample_Voip_GetValidRateMax(u32RateMin,u32RateMax,pu32AudInRate);
            }
//modify by x00190696
        }
    }

    HI_AUD_DEV_UNLOCK();
    
    if(HI_UNF_VOIP_AUD_DEV_ALSA == pstAudDev->u32AudDevId)
    {
        usleep(100*1000);
    }
    
    return HI_SUCCESS;
}

HI_S32 Sample_Voip_SetAudDevPara(HI_AUD_DEV_TOTAL_INFO_S * pstAudDev,
                                 HI_U32 u32AudInRate,
                                 HI_U32 u32AudOutRate,
                                 HI_UNF_AUDDEV_BODY_S *pstVoipAudDevPara,
                                 HI_UNF_AUDADP_AUDDEV_PARA_S *pstAudAdpDevPara)
{
    if((NULL == pstAudDev)||(NULL == pstVoipAudDevPara)||(NULL == pstAudAdpDevPara))
    {
        sample_printf("%s %d , null pointer!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    HI_AUD_DEV_LOCK();

    pstVoipAudDevPara->s32AudioDevId = pstAudDev->u32AudDevId;
    pstVoipAudDevPara->s32AiSampleRate = u32AudInRate;
    pstVoipAudDevPara->s32AiBitPerSample = 16;
    pstVoipAudDevPara->s32AiChannels = 1;
    
    pstVoipAudDevPara->s32AoSampleRate = u32AudOutRate;
    pstVoipAudDevPara->s32AoBitPerSample = 16;
    pstVoipAudDevPara->s32AoChannels = 1;


    pstAudAdpDevPara->s32AudioDevId = pstAudDev->u32AudDevId;
    pstAudAdpDevPara->s32AiSampleRate = u32AudInRate;
    pstAudAdpDevPara->s32AiBitPerSample = 16;
    pstAudAdpDevPara->s32AiChannels = 1;
    pstAudAdpDevPara->s32AiCardNo = pstAudDev->s32InSndCardNo;
    
    pstAudAdpDevPara->s32AoSampleRate = u32AudOutRate;
    pstAudAdpDevPara->s32AoBitPerSample = 16;
    pstAudAdpDevPara->s32AoChannels = 1;
    pstAudAdpDevPara->s32AoCardNo = pstAudDev->s32OutSndCardNo;
    
    HI_AUD_DEV_UNLOCK();
    return HI_SUCCESS;
}

#ifdef ENABLE_AUDIO_DEVICE_MONITOR

static HI_VOID *Sample_Voip_AudDev_Monitor(HI_VOID *arg)
{
    HI_S32 ret;
    HI_CHAR acInLast[AUDDEV_NAME_LEN];
    HI_CHAR acOutLast[AUDDEV_NAME_LEN];
    
    sample_printf("\nstart audio device monitor thread!\n");

    while(stThreadAudDevMonitor.u32RunFlag)
    {
        usleep(1000*1000);
        
        strcpy(acInLast, stAudDevSel.szInName);
        strcpy(acOutLast, stAudDevSel.szOutName);
        ret = Sample_Voip_GetAudioList(HI_UNF_VOIP_AUD_IN_DEV, stAudevInList, HI_AUD_DEV_LIST_MAX, &u32AudInDevNum);
        if(HI_SUCCESS != ret)
        {
            sample_printf("%s %d ,Get audio in list failure! ErrCode=%x, AudDevNum=%d\n",__FUNCTION__,__LINE__,ret,u32AudInDevNum);
            continue;
        }

        ret = Sample_Voip_GetAudioList(HI_UNF_VOIP_AUD_OUT_DEV, stAudevOutList, HI_AUD_DEV_LIST_MAX, &u32AudOutDevNum);
        if(HI_SUCCESS != ret)
        {
            sample_printf("%s %d ,Get audio in list failure! ErrCode=%x, AudDevNum=%d\n",__FUNCTION__,__LINE__,ret,u32AudOutDevNum);
            continue;
        }
        
        ret = Sample_Voip_SelectAudDevByName(stAudevInList, u32AudInDevNum, s_acInAudDevName, stAudevOutList, u32AudOutDevNum, s_acInAudDevName, &stAudDevSel);
        if(HI_SUCCESS != ret)
        {
            sample_printf("%s %d , Select audio device failure!\n",__FUNCTION__,__LINE__);
            continue;
        }

        if(0 == strcmp(stAudDevSel.szInName, acInLast) || 0 == strcmp(stAudDevSel.szOutName, acOutLast))
        {
            sample_printf("\nAudio device changed\n");
        }
    }
    sample_printf("\nexit audio device monitor thread!\n");
    return NULL;
}

static HI_S32 Sample_Voip_CreateAudDevMonitorThread(HI_VOID)
{
    HI_S32 ret;

    if(stThreadAudDevMonitor.u32Used)
        return HI_SUCCESS;
    
    memset(&stThreadAudDevMonitor, 0, sizeof(AUDDEV_MONITOR_THREAD_STRU));
    ret = pthread_mutex_init(&stThreadAudDevMonitor.tMutex,NULL);
    if(ret != HI_SUCCESS)
    {
        sample_printf("Initial thread mutex err.\n");
        return HI_FAILURE;
    }

    stThreadAudDevMonitor.u32RunFlag = 1;
    
    ret = pthread_create(&stThreadAudDevMonitor.tThread, HI_NULL, Sample_Voip_AudDev_Monitor, HI_NULL);
    if(ret != HI_SUCCESS)
    {
        sample_printf("create audio device monitor pthread err.\n");
        pthread_mutex_destroy(&stThreadAudDevMonitor.tMutex);
        return HI_FAILURE;
    }
    stThreadAudDevMonitor.u32Used = 1;
    
    sample_printf("Create audio device monitor thread success.\n");
    return HI_SUCCESS;
}

static HI_S32 Sample_Voip_DestroyAudDevMonitorThread(HI_VOID)
{
    if(!stThreadAudDevMonitor.u32Used)
        return HI_SUCCESS;

    stThreadAudDevMonitor.u32RunFlag = 0;
    pthread_join(stThreadAudDevMonitor.tThread, NULL);
    pthread_mutex_destroy(&stThreadAudDevMonitor.tMutex);
    memset(&stThreadAudDevMonitor,0,sizeof(AUDDEV_MONITOR_THREAD_STRU));

    sample_printf("Destroy audio device monitor thread success.\n");
    return HI_SUCCESS;
}

#endif

#if 0
HI_S32 Sample_UsbPhone_GetSerialPort(HI_S32 s32SndCardNo, HI_CHAR *pszUsbSerialPort)
{
    HI_S32 s32Ret;
    USB_DEV_INFO_S stUsbDevInfo;
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    HI_CHAR szDir[128];
    HI_CHAR szCurDir[128];

    if(HI_NULL == pszUsbSerialPort)
    {
        sample_printf("%s %d, Null pointer.\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }
    HI_AUD_DEV_LOCK();

    sprintf(pszUsbSerialPort,"/dev/ttyUSB0");    

    if(s32SndCardNo < 0)
    {
        HI_AUD_DEV_UNLOCK();
        sample_printf("%s %d, Invalid sound card number.\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }
    
    s32Ret = Sample_Voip_GetUsbDevInfoBySndCardNo(s32SndCardNo, &stUsbDevInfo);
    if(HI_SUCCESS != s32Ret)
    {
        HI_AUD_DEV_UNLOCK();
        sample_printf("%s %d , Get USB device info failure!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    memset(szDir,0,sizeof(szDir));
    sprintf(szDir,"/dev/usb/by-devid/%d_%d",stUsbDevInfo.u32BusNum,stUsbDevInfo.u32DevNum);
    if((dp = opendir(szDir)) == HI_NULL)
    {
        HI_AUD_DEV_UNLOCK();
        sample_printf("%s %d , open dir %s failure!\n",__FUNCTION__,__LINE__,szDir);
        return HI_FAILURE;
    }
    
    if(getcwd(szCurDir,sizeof(szCurDir)) == HI_NULL)
    {
        HI_AUD_DEV_UNLOCK();
        sample_printf("%s %d , get cur dir failure!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }
        
    chdir(szDir);
    while((entry = readdir(dp))!= HI_NULL)
    {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode))
        {
            continue;
        }
        else
        {
            if(0 == strncmp("ttyUSB", entry->d_name, 6))
            {
                sprintf(pszUsbSerialPort,"/dev/%s",entry->d_name);    
                sample_printf("get usb phone serial port success, ret is %s\n",pszUsbSerialPort);
                break;
            }
        }
    }
    chdir(szCurDir);
    closedir(dp);
    HI_AUD_DEV_UNLOCK();
    return HI_SUCCESS;
}

#define USB_PHONE_HELP_INFO  \
"\n ------------- usb phone help info ------------------------- \n " \
"  h           : help info                                    \n " \
"  ringon      : ring on                                      \n " \
"  ringoff     : ring off                                     \n " \
"  busytone    : play busy tone                               \n " \
"  howlertone  : play howler tone                             \n " \
"  stoptone    : stop tone and on hook / stop tone only       \n " \
"  display     : display call in id                           \n " \
"  cfgcontone  : enable/disable connect tone                  \n " \
"  getver      : display usb phone version                    \n " \
" ----------------------------------------------------------- \n\n " \


HI_S32 usb_phone_event_proc(HI_USB_PHONE_EVENT_E enEvent, HI_S32 s32EventValue, HI_U32 u32Args)
{
    switch(enEvent)
    {
        case HI_USB_PHONE_EVENT_BS_REG:
            sample_printf("\nusb phone event: BS REG , state %d, args 0x%x\n",s32EventValue,u32Args);
            break;
        case HI_USB_PHONE_EVENT_OFF_HOOK:
            sample_printf("\nusb phone event: OFF HOOK, args 0x%x\n",u32Args);
            break;
        case HI_USB_PHONE_EVENT_ON_HOOK:
            sample_printf("\nusb phone event: ON HOOK, args 0x%x\n",u32Args);
            break;
        case HI_USB_PHONE_EVENT_KEY:
            sample_printf("\nusb phone event: KEY %c , args 0x%x\n",(HI_CHAR)s32EventValue,u32Args);
            break;
        case HI_USB_PHONE_EVENT_HOLD:
            sample_printf("\nusb phone event: HOLD , state %d, args 0x%x\n",s32EventValue,u32Args);
            break;
        case HI_USB_PHONE_EVENT_DISCON:
            sample_printf("\nusb phone event: DISCON , args 0x%x\n",u32Args);
            break;
        default:
            sample_printf("\nusb phone event: UNKNOWN , value %d, args 0x%x\n",s32EventValue,u32Args);
            break;
    }
    return HI_SUCCESS;
}

HI_S32 usb_phone_cmd_proc(HI_CHAR * InputCmd)
{
    HI_S32 ret = HI_SUCCESS;
    
    if(HI_NULL == InputCmd)
    {
        return HI_FAILURE;
    }
    
    if (0 == strncmp("ringon", InputCmd, 6))        
    {
        ret = HI_USB_PHONE_Ring(HI_TRUE);
    }
    else if (0 == strncmp("ringoff", InputCmd, 7))        
    {
        ret = HI_USB_PHONE_Ring(HI_FALSE);
    }
    else if (0 == strncmp("busytone", InputCmd, 8))        
    {
        ret = HI_USB_PHONE_PlayTone(HI_USB_PHONE_BUSY_TONE);
    }
    else if (0 == strncmp("howlertone", InputCmd, 10))        
    {
        ret = HI_USB_PHONE_PlayTone(HI_USB_PHONE_HOWLER_TONE);
    }
    else if (0 == strncmp("stoptone", InputCmd, 8))        
    {
        HI_CHAR c;
        c = InputCmd[8];
        if(c == '0')
            ret = HI_USB_PHONE_StopTone(HI_FALSE);
        else
            ret = HI_USB_PHONE_StopTone(HI_TRUE);
    }
    else if (0 == strncmp("display", InputCmd, 7))        
    {
        ret = HI_USB_PHONE_DisplayCallID(&InputCmd[7]);
    }
    else if (0 == strncmp("cfgcontone", InputCmd, 10))        
    {
        HI_CHAR c;
        c = InputCmd[10];
        if((c == '0')||(c == '1'))
            ret = HI_USB_PHONE_Config_ConTone(c - '0');
        else
            sample_printf("invalid input\n");
    }
    else if (0 == strncmp("getver", InputCmd, 6))        
    {
        HI_CHAR *pszVer = HI_NULL;
        ret = HI_USB_PHONE_GetBSVersion(&pszVer);
        sample_printf("\nusb phone version:   %s\n",pszVer);
    }
    else if ('h' == InputCmd[0])
    {
        sample_printf("%s",USB_PHONE_HELP_INFO);
    }
    else
    {
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}
#endif

#define AIAO_SAMPLERATE 8000
#define AIAO_SAMPLE_PER_FRAME  80

HI_S32  Sample_Voip_Run(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_BOOL bCircle =  HI_FALSE;
    HI_CHAR InputCmd[32];
    HI_UNF_AUDADP_AUDDEV_PARA_S stAudAdpDevPara;
    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;  
    HI_U32  u32AiSampleRate = HI_UNF_SAMPLE_RATE_8K;
    HI_U32  u32AoSampleRate = HI_UNF_SAMPLE_RATE_48K;
    HI_CHAR szUsbSerialPort[32];

    hVoipHandle = 0;
    memset(&stChAttr,0,sizeof(HI_UNF_VOIP_CHN_ATTR_S));
    memset(&stAudAdpDevPara,0,sizeof(HI_UNF_AUDADP_AUDDEV_PARA_S));

    s32Ret = Sample_Voip_GetAudioList(HI_UNF_VOIP_AUD_IN_DEV, stAudevInList, HI_AUD_DEV_LIST_MAX, &u32AudInDevNum);
    if(HI_SUCCESS != s32Ret)
    {
        sample_printf("%s %d ,Get audio in list failure! ErrCode=%x, AudDevNum=%d\n",__FUNCTION__,__LINE__,s32Ret,u32AudInDevNum);
        return s32Ret;
    }

    s32Ret = Sample_Voip_GetAudioList(HI_UNF_VOIP_AUD_OUT_DEV, stAudevOutList, HI_AUD_DEV_LIST_MAX, &u32AudOutDevNum);
    if(HI_SUCCESS != s32Ret)
    {
        sample_printf("%s %d ,Get audio in list failure! ErrCode=%x, AudDevNum=%d\n",__FUNCTION__,__LINE__,s32Ret,u32AudOutDevNum);
        return s32Ret;
    }

    
    s32Ret = Sample_Voip_SelectAudDev(stAudevInList, u32AudInDevNum, stAudevOutList, u32AudOutDevNum, &stAudDevSel);
    if(HI_SUCCESS != s32Ret)
    {
        sample_printf("%s %d , Select audio device failure!\n",__FUNCTION__,__LINE__);
        return s32Ret;
    }
    else
    {
        sample_printf("\nSelected audio device : DevId [%d] InType [%s]\n", stAudDevSel.u32AudDevId, szTypeStr[stAudDevSel.u32AudDevTpye]);
        
        if(1 == stAudDevSel.s32InFlag)
        {
            sample_printf("InCardNo [%d] InName [%s]\n", stAudDevSel.s32InSndCardNo, stAudDevSel.szInName);
        }

        if(1 == stAudDevSel.s32OutFlag)
        {
            sample_printf("OutCardNo [%d] OutName [%s]\n\n", stAudDevSel.s32OutSndCardNo, stAudDevSel.szOutName);
        }
    }

    do
    {
        s32Ret = Sample_Voip_GetAudDevSampleRate(&stAudDevSel, &u32AiSampleRate, &u32AoSampleRate);
        if(HI_SUCCESS != s32Ret)
        {
            sample_printf("%s %d , Get audio device sample rate failure!\n",__FUNCTION__,__LINE__);
            return s32Ret;
        }

#if 0
        if(stAudDevSel.u32AudDevTpye == HI_VOIP_AUD_DEV_TYPE_USB_PHONE)
        {
            memset(szUsbSerialPort,0,sizeof(szUsbSerialPort));
            s32Ret = Sample_UsbPhone_GetSerialPort(stAudDevSel.s32OutSndCardNo, szUsbSerialPort);
            if(HI_SUCCESS != s32Ret)
            {
                sample_printf("%s %d , Get usb phone serial port failure!\n",__FUNCTION__,__LINE__);
                return s32Ret;
            }

            s32Ret = HI_USB_PHONE_Open(szUsbSerialPort);
        }
#endif

        s32Ret= HI_UNF_VOIP_GetChDefaultAttr(HI_UNF_VOIP_MODE_VOIVE, &stChAttr);
        if(s32Ret != HI_SUCCESS)
        {
            sample_printf("%s %d , Voip get default attribute failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
            return s32Ret;
        }
        

        s32Ret = Sample_Voip_SetAudDevPara(&stAudDevSel, u32AiSampleRate, u32AoSampleRate, &stChAttr.stAudevPara.stBody, &stAudAdpDevPara);
        if(s32Ret != HI_SUCCESS)
        {
            sample_printf("%s %d , Set audio device para failure!\n",__FUNCTION__,__LINE__);
            return s32Ret;
        }

        if((HI_VOIP_AUD_DEV_TYPE_SLIC == stAudDevSel.u32AudDevTpye)
            ||(HI_VOIP_AUD_DEV_TYPE_USB_PHONE == stAudDevSel.u32AudDevTpye))
        {
            stChAttr.stDigitPara.stBody.u32DigitEnableFlag = 1; //enable DTMF process
        }
        
        stAudDevOptFlag.bit1AudInDev = stAudDevSel.s32InFlag;
        stAudDevOptFlag.bit1AudOutDev = stAudDevSel.s32OutFlag;
    
        s32Ret = HI_UNF_AUDADP_AudDev_Open(&stAudAdpDevPara, stAudDevOptFlag);
        if(s32Ret != HI_SUCCESS)
        {
            sample_printf("\n%s %d Audio adapter open failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
            return s32Ret;
        }

        Sample_Voip_SetNetPara(&stChAttr.stNetPara);
        s32Ret = HI_UNF_VOIP_CreateChannel(HI_UNF_VOIP_MODE_VOIVE, &stChAttr, &hVoipHandle);
        if(s32Ret != HI_SUCCESS)
        {
            sample_printf("\n%s %d Voip create channel failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
            goto Voip_DestroyChannel;
        }
        s32Ret = HI_UNF_AUDADP_AudDev_Start(stAudAdpDevPara.s32AudioDevId, stAudDevOptFlag);
        if(s32Ret != HI_SUCCESS)
        {
            sample_printf("\n%s %d Audio adapter start failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
            goto Voip_DestroyChannel;
        }

        s32Ret = HI_UNF_VOIP_RegisterEvent(hVoipHandle, Sample_Voip_EventCallBack, hVoipHandle);
        if(s32Ret != HI_SUCCESS)
        {
            sample_printf("%s %d Voip register event cb function failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
            goto Voip_DestroyChannel;
        }

        if(u8VoipFuncSel == 1)
        {

            sample_printf("\nSample voip play announcemount!\n");
            HI_UNF_VOIP_StopAnnouncement(hVoipHandle, stAnnAttr.u32Direction);    

            s32Ret= Sample_Voip_Load_AudioFile();
            if(s32Ret != HI_SUCCESS)
            {
                goto Voip_DestroyChannel;
            }
            
            memset(&stAnnAttr,0,sizeof(HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S));

            stAnnAttr.u32DataAddr = (HI_U32)pu8AudioFileAddr;
            stAnnAttr.u32DataLen = s32AudioFileLen;
            stAnnAttr.u16SourceFormat = 0;      //0-G711A 1-G711U
            stAnnAttr.u32Direction = 0;
            stAnnAttr.u32LoopTime = 0xff;
            stAnnAttr.u32MixFlag = 0;
            
            s32Ret = HI_UNF_VOIP_PlayAnnouncement( hVoipHandle, &stAnnAttr);
            if(s32Ret != HI_SUCCESS)
            {
                sample_printf("%s %d Voip play announcemount failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
                goto Voip_CloseAudioFile;
            }
        
        }
        
        usleep(100*1000); //for display and not to close too quickly 

        printf("\n");
        printf("    press 'q' key to quit!\n");
        printf("    press 'r' key to continue next voip Create/Destroy channel circle!\n");
        printf("    press 's' key to change the audio device!\n");
        if(stAudDevSel.u32AudDevTpye == HI_VOIP_AUD_DEV_TYPE_USB_PHONE)
        {
            printf("    press 'h' to display usb phone help info!\n");
        }
        printf("\n");
        
        while(1)
        {
            
            SAMPLE_GET_INPUTCMD(InputCmd);

#if 0
            s32Ret = usb_phone_cmd_proc(InputCmd);
            if(HI_SUCCESS == s32Ret)
                continue;
#endif
            
            if(InputCmd[0] == 'q')
            {
                bCircle = HI_FALSE;
                break;
            }
            else if(InputCmd[0] == 'r')
            {
                bCircle = HI_TRUE;
                break;
            }
            else if (InputCmd[0] == 't')
            {
                HI_UNF_VOIP_RTCP_STATIC_INFO_S stRtcpInfo;
                s32Ret = HI_UNF_VOIP_GetRtcpStaticInfo(hVoipHandle, &stRtcpInfo);
                if (s32Ret != HI_SUCCESS)
                {
                    sample_printf("ret 0%x\n", s32Ret);
                    continue;
                }
                sample_printf("recpack is %d, bytes is %d\n", stRtcpInfo.u32RecPacketNum, stRtcpInfo.u32RecBytes);
                continue;
            }
            else if(InputCmd[0] == 'd')
            {
                HI_S32 volume = s32InitVolume;
                HI_UNF_VOIP_CHN_ATTR_S stVoipChnAttr;
                s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stVoipChnAttr);
                if (s32Ret != HI_SUCCESS)
                {
                    sample_printf("get chn attr failed\n");
                    continue;
                }

                stVoipChnAttr.stEcPara.stChange.bit1OutputVolume = 1;
                stVoipChnAttr.stEcPara.stBody.u8OutputVolume = s32InitVolume;
                s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
                s32InitVolume -= 5;

                if (s32Ret == HI_SUCCESS)
                {                    
                    sample_printf("down volume is %d\n",volume);
                }
                else
                    sample_printf("modify chn attr failed\n");
            }
            else if(InputCmd[0] == 'u')
            {
                HI_S32 gain = s32Gain;
                HI_UNF_VOIP_CHN_ATTR_S stVoipChnAttr;
                s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stVoipChnAttr);
                if (s32Ret != HI_SUCCESS)
                {
                    sample_printf("get chn attr failed\n");
                    continue;
                }
                
#if 0                
                stVoipChnAttr.stEcPara.stChange.bit1OutputGain = 1;
                stVoipChnAttr.stEcPara.stBody.s8OutputGain = s32Gain;
                s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
                s32Gain -= 5;
#endif
                stVoipChnAttr.stEcPara.stChange.bit1OutputVolume= 1;
                stVoipChnAttr.stEcPara.stBody.u8OutputVolume = (HI_U8)s32InitVolume;
                s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
                s32InitVolume += 5;
                if (s32Ret == HI_SUCCESS)
                {                    
//                    sample_printf("up gain is %d\n",gain);
                    sample_printf("up volume is %d\n", s32InitVolume);
                }
                else
                    sample_printf("modify chn attr failed\n");
            }
            else if(InputCmd[0] == 'm')  //for verify
            {
                static int count = 0;
                if(count%2 == 0)
                {
                    HI_UNF_VOIP_CHN_ATTR_S stVoipChnAttr;
                    s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stVoipChnAttr);
                    if (s32Ret != HI_SUCCESS)
                    {
                        sample_printf("get chn attr failed\n");
                        continue;
                    }
                    stVoipChnAttr.stEcPara.stChange.bit1OutputMute = 1;
                    stVoipChnAttr.stEcPara.stBody.u8OutputMute = 0;
                    s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
                    if (s32Ret == HI_SUCCESS)
                        sample_printf("cp unmute success\n");
                    else
                        sample_printf("cp unmute failed\n");
                }
                else
                {
                    HI_UNF_VOIP_CHN_ATTR_S stVoipChnAttr;
                    s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stVoipChnAttr);
                    if (s32Ret != HI_SUCCESS)
                    {
                        sample_printf("get chn attr failed\n");
                        continue;
                    }
                    stVoipChnAttr.stEcPara.stChange.bit1OutputMute = 1;
                    stVoipChnAttr.stEcPara.stBody.u8OutputMute = 1;
                    s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
                    if (s32Ret == HI_SUCCESS)
                        sample_printf("cp mute success\n");
                    else
                        sample_printf("cp mute failed\n");
                }
                count++;
            }
            else if(InputCmd[0] == 's')  //for verify
            {
                s32Ret = Sample_Voip_SelectAudDev(stAudevInList, u32AudInDevNum, stAudevOutList, u32AudOutDevNum, &stAudDevSel);
                if(HI_SUCCESS != s32Ret)
                {
                    sample_printf("%s %d , Select audio device failure!\n",__FUNCTION__,__LINE__);
                    continue;
                }
    
                HI_UNF_AUDADP_AudDev_Close(stAudAdpDevPara.s32AudioDevId, stAudDevOptFlag);
                usleep(1000*1000);   //To make sure the audio device be closed before open on next time
                
                s32Ret = Sample_Voip_GetAudDevSampleRate(&stAudDevSel, &u32AiSampleRate, &u32AoSampleRate);
                if(HI_SUCCESS != s32Ret)
                {
                    sample_printf("%s %d , Get audio device sample rate failure!\n",__FUNCTION__,__LINE__);
                    continue;
                }

                s32Ret = Sample_Voip_SetAudDevPara(&stAudDevSel, u32AiSampleRate, u32AoSampleRate, &stChAttr.stAudevPara.stBody, &stAudAdpDevPara);
                if(s32Ret != HI_SUCCESS)
                {
                    sample_printf("%s %d , Set audio device para failure!\n",__FUNCTION__,__LINE__);
                    continue;
                }
                memset(&stChAttr.stAudevPara.stChang,0xff,sizeof(HI_UNF_AUDDEV_FLAG_S));

                if((HI_VOIP_AUD_DEV_TYPE_SLIC == stAudDevSel.u32AudDevTpye)
                    ||(HI_VOIP_AUD_DEV_TYPE_USB_PHONE == stAudDevSel.u32AudDevTpye))  
                {
                    stChAttr.stDigitPara.stBody.u32DigitEnableFlag = 1; //enable DTMF process
                }
                else
                {
                    stChAttr.stDigitPara.stBody.u32DigitEnableFlag = 0; //disable DTMF process
                }
                stChAttr.stDigitPara.stChange.bit1DigitEnable = 1;
                
                s32Ret = HI_UNF_AUDADP_AudDev_Open(&stAudAdpDevPara, stAudDevOptFlag);
                if(s32Ret != HI_SUCCESS)
                {
                    sample_printf("\n%s %d Audio adapter open failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
                    bCircle = HI_FALSE;
                    break;
                }
                
                s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stChAttr);
                if(s32Ret != HI_SUCCESS)
                {
                    sample_printf("\n%s %d Voip modify channel attr failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
                    bCircle = HI_FALSE;
                    break;
                }
                else
                {
                    s32Ret = HI_UNF_AUDADP_AudDev_Start(stAudAdpDevPara.s32AudioDevId, stAudDevOptFlag);
                    if(s32Ret != HI_SUCCESS)
                    {
                        sample_printf("\n%s %d Audio adapter start failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
                        bCircle = HI_FALSE;
                        break;
                    }
                }             
            }
            if (InputCmd[0] == 'n')
            {
                s32Ret = HI_UNF_SND_SetMute(HI_UNF_SND_0,HI_UNF_SND_OUTPUTPORT_ALL,HI_FALSE);
                if (s32Ret == HI_SUCCESS)
                sample_printf("set unmute\n");
            }
        }

        if(u8VoipFuncSel == 1)
        {
            goto Voip_StopAnn;
        }
        else
        {
            goto Voip_DestroyChannel;
        }
        
    Voip_StopAnn:    
        HI_UNF_VOIP_StopAnnouncement(hVoipHandle, stAnnAttr.u32Direction);    
    Voip_CloseAudioFile:    
        Sample_Voip_Close_AudioFile();
    Voip_DestroyChannel:
        HI_UNF_VOIP_DestroyChannel(hVoipHandle);
        HI_UNF_AUDADP_AudDev_Close(stAudAdpDevPara.s32AudioDevId, stAudDevOptFlag);
#if 0
        if(stAudDevSel.u32AudDevTpye == HI_VOIP_AUD_DEV_TYPE_USB_PHONE)
        {
            HI_USB_PHONE_Close();
        }
#endif
        if(bCircle)
        {
            usleep(100*1000);   //To make sure the audio device be closed before open on next time
        }

    }while(bCircle);    

    return s32Ret;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32 s32Ret = HI_SUCCESS;

    if(2 == argc)
    {
        u8VoipFuncSel = strtol(argv[1],NULL,0);
    }
    else
    {
        printf("Usage: %s para\n"              
               "       para : function select, 0--Normal,1--Play Announcement\n"               
               ,argv[0]);
        printf("Example:%s 0\n", argv[0]);
        return (0);
    }

    if(u8VoipFuncSel>1)
    {
        printf("Invalid function selection : %d .\n",u8VoipFuncSel);
        printf("       para: 0--Normal,1--Play Announcement\n");
        return (0);
    }
    
    HI_SYS_Init();
    HI_SYS_SetLogLevel(HI_ID_VOIP_HME, HI_LOG_LEVEL_ERROR);
    
    s32Ret = HIADP_Disp_Init(HI_UNF_ENC_FMT_720P_50);  
    
    /*Initial HIAO*/
    s32Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HIADP_Snd_Init failed.\n");
    }

#if 0
    s32Ret = HI_USB_PHONE_Init();
    HI_USB_PHONE_RegisterEvent(usb_phone_event_proc, 0);
#endif
    
    s32Ret = HI_UNF_VOIP_Init();
    if(s32Ret != HI_SUCCESS)
    {
        sample_printf("%s %d , Voip initial failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
        goto Voip_DeInit;
    }
    
    s32Ret = HI_UNF_AUDADP_Init();
    if (HI_SUCCESS != s32Ret)
    {
        goto Voip_DeInit;
    }

    HI_UNF_AUDADP_RegisterEvent(Sample_AudAdp_EventCallBack, 0);

    Sample_NetPara_Input();

#ifdef ENABLE_AUDIO_DEVICE_MONITOR
    Sample_Voip_CreateAudDevMonitorThread();
#endif

    Sample_Voip_Run();

#ifdef ENABLE_AUDIO_DEVICE_MONITOR
    Sample_Voip_DestroyAudDevMonitorThread();
#endif

Voip_DeInit:
    HI_UNF_VOIP_DeInit();
    HI_UNF_AUDADP_DeInit();

//    HI_USB_PHONE_DeInit();
    
    HIADP_Snd_DeInit();

    HIADP_Disp_DeInit();    
    
    HI_SYS_DeInit();
    
    return s32Ret;
}


