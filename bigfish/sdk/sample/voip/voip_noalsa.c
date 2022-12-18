#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "hi_adp_audio.h"
#include "hi_adp_mpi.h"
#include "hi_unf_voip.h"
#include "hi_unf_sound.h"

#define MAX_FILE_LEN (5*1024*1024)

static HI_UNF_VOIP_CHN_ATTR_S  stChAttr;
static HI_U32  hVoipHandle;
static HI_U8  u8VoipFuncSel = 0;      //function select , 0-- Normal 1-- Play Announcement
static HI_S32 s32AudioDevId = HI_UNF_VOIP_AUD_DEV_SIO;       // 0 -- SIO (SLIC)  1--Bluetooth  2--USB MIC+HIAO
static HI_U8   u8SrcIp[4] = {10,85,180,91};
static HI_U8   u8DstIp[4] = {10,85,180,95};
static HI_U16    u16VoipSrcPort = 8100;
static HI_U16    u16VoipDstPort = 8100;

//static HI_U16    u16VpSrcPort = 8200;
//static HI_U16    u16VpDstPort = 8200;

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
                    printf("\nInvalid input.\n");
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
        
        printf("Src IP %d:%d:%d:%d \n",u8SrcIp[0],u8SrcIp[1],u8SrcIp[2],u8SrcIp[3]);
        printf("Dest IP %d:%d:%d:%d \n",u8DstIp[0],u8DstIp[1],u8DstIp[2],u8DstIp[3]);
        
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
        printf("null pointer pstNetCfg\n");
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
    printf("%s(), handle 0x%x, event type %d, event value %d, args 0x%x\n",__FUNCTION__,hVoip,enEvent,s32EventValue,u32Args);
    return HI_SUCCESS;
}

HI_S32 Sample_AudAdp_EventCallBack(HI_UNF_AUDADP_EVENT_S *pstAudadpEvent)
{
    printf("%s(), Audio%sDevId %d, Event %d, Status %d\n",__FUNCTION__,
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
        printf("%s %d Voip malloc failure!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    /*fill with data from play file*/ /*CNcomment:填写播放文件的数据*/
    fp = fopen(cFileName, "rb");
    if (NULL == fp)
    {
        free(pu8AudioFileAddr);
        pu8AudioFileAddr = NULL;
        printf("%s %d open audio file %s failure!\n",__FUNCTION__,__LINE__,cFileName);
        return HI_FAILURE;
    }
    
    s32AudioFileLen = fread(pu8AudioFileAddr, 1, MAX_FILE_LEN, fp);
    if (s32AudioFileLen <= 0)
    {
        fclose(fp);
        free(pu8AudioFileAddr);
        fp = NULL;
        pu8AudioFileAddr = NULL;
        printf("%s %d read audio file %s failure!\n",__FUNCTION__,__LINE__,cFileName);
        return HI_FAILURE;
    }

    printf("read audio file %s success, len:%d addr:0x%x\n", cFileName,s32AudioFileLen, (HI_U32)pu8AudioFileAddr);
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

    
HI_S32 Sample_Voip_GetAudioDevice(HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType,HI_ALSA_CARD_INFO_S * pstCardInfo,HI_U32 *pu32SampleRate)
{
    HI_S32 s32Ret;
    HI_ALSA_CARD_INFO_S stCardList[10];
    HI_U32 u32Count=0,u32RateMin,u32RateMax,i;

    if(NULL == pstCardInfo)
    {
        printf("%s %d , pstCardInfo is null pointer!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    /*Set default card info*/
    pstCardInfo->enType = enAudioDevType;
    pstCardInfo->s32CardNo = -1;
    
    s32Ret = HI_ALSA_GetAudioDevList(enAudioDevType,stCardList,10,&u32Count);
    if(HI_SUCCESS != s32Ret)
    {
        printf("\n%s %d , Get audio %s device list failure, ErrCode is %x!\n",__FUNCTION__,__LINE__,enAudioDevType?"in":"out",s32Ret);
        return HI_FAILURE;
    }

    if(u32Count <= 0)
    {
        printf("\n%s %d , No audio %s device found!\n",__FUNCTION__,__LINE__,enAudioDevType?"in":"out");
        return HI_FAILURE;
    }
    else if(u32Count == 1)
    {
       *pstCardInfo = stCardList[0]; 
    }
    else
    {
        HI_CHAR c;
        printf("\nplease select the sound card :\n");
        for(i=0;i<u32Count;i++)
        {
            printf("  %d :  card [%d] name [%s]\n",i,stCardList[i].s32CardNo,stCardList[i].szName);
        }
        printf("\n");
        
        while(1)
        {
            c = getchar();
            if((c < '0') || (c > '9'))
                continue;
            i = c - '0';
            if(i >= u32Count)
                continue;
            
            *pstCardInfo = stCardList[i]; 
            break;
        }
    }
        
    if(pstCardInfo->s32CardNo >= 0)
    {
        s32Ret = HI_ALSA_GetAudioDevRateRange(pstCardInfo, &u32RateMin, &u32RateMax);
        if(HI_SUCCESS != s32Ret)
        {
            printf("%s %d , Get audio %s device [%d - %s] rate range failure, ErrCode is %x!\n",
                __FUNCTION__,__LINE__,
                pstCardInfo->enType?"in":"out",
                pstCardInfo->s32CardNo,
                pstCardInfo->szName,
                s32Ret);
        }
        else
        {
            printf("Card [%d], name [%s], type [%s], rate_min [%d], rate_max[%d]\n",
                    pstCardInfo->s32CardNo,
                    pstCardInfo->szName,
                    enAudioDevType?"IN":"OUT",
                    u32RateMin,
                    u32RateMax);

            s32Ret = Sample_Voip_GetValidRateMax(u32RateMin,u32RateMax,pu32SampleRate);
        }
    }
    else
    {
        printf("%s %d Inavlid card number\n",__FUNCTION__,__LINE__);
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}
    
HI_S32 Sample_Voip_GetAudioOutDevice(HI_ALSA_CARD_INFO_S * pstAudIn,HI_ALSA_CARD_INFO_S * pstAudOut,HI_U32 *pu32SampleRate)
{
    HI_S32 s32Ret;
    HI_ALSA_CARD_INFO_S stCardList[10];
    HI_U32 u32Count=0,u32RateMin,u32RateMax,i;
    
    if((NULL == pstAudIn)||(NULL == pstAudOut)||(NULL == pu32SampleRate))
    {
        printf("%s %d , null pointer!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    /*Set default card info*/
    pstAudOut->s32CardNo = -1;      //default to hiao
    pstAudOut->enType = HI_UNF_VOIP_AUD_OUT_DEV;

    if(pstAudIn->s32CardNo < 0)
    {
        printf("%s %d , invalid audio in device card number!\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }
    
    s32Ret = HI_ALSA_GetAudioDevList(HI_UNF_VOIP_AUD_OUT_DEV,stCardList,10,&u32Count);
    if(HI_SUCCESS != s32Ret)        //use default audio out device (hiao)
    {
        return HI_SUCCESS;
    }
    
    for(i=0;i<u32Count;i++)
    {
        if(stCardList[i].s32CardNo == pstAudIn->s32CardNo)
        {
            *pstAudOut = stCardList[i];
            break;
        }
    }

    if(pstAudOut->s32CardNo >= 0)
    {
        s32Ret = HI_ALSA_GetAudioDevRateRange(pstAudOut, &u32RateMin, &u32RateMax);
        if(HI_SUCCESS != s32Ret)
        {
            printf("%s %d , Get audio %s device [%d - %s] rate range failure, ErrCode is %x!\n",
                __FUNCTION__,__LINE__,
                pstAudOut->enType?"in":"out",
                pstAudOut->s32CardNo,
                pstAudOut->szName,
                s32Ret);
        }
        else
        {
            printf("Card [%d], name [%s], type [%s], rate_min [%d], rate_max[%d]\n",
                    pstAudOut->s32CardNo,
                    pstAudOut->szName,
                    pstAudOut->enType?"IN":"OUT",
                    u32RateMin,
                    u32RateMax);
            
            s32Ret = Sample_Voip_GetValidRateMax(u32RateMin,u32RateMax,pu32SampleRate);
        }
    }
    else
    {
        *pu32SampleRate = HI_UNF_SAMPLE_RATE_48K;
    }
    
    return HI_SUCCESS;
}    


#define AIAO_SAMPLERATE 8000
#define AIAO_SAMPLE_PER_FRAME  80

HI_S32  Sample_Voip_Run(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_CHAR cInput;
    HI_BOOL bCircle =  HI_FALSE;
    HI_UNF_AUDADP_AUDDEV_PARA_S stAudDevPara;
    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;  
    HI_ALSA_CARD_INFO_S stAudioInDevice; //for USB MIC
    HI_U32  u32AiSampleRate = HI_UNF_SAMPLE_RATE_8K;
    HI_ALSA_CARD_INFO_S stAudioOutDevice; //for HIAO
    HI_U32  u32AoSampleRate = HI_UNF_SAMPLE_RATE_48K;
    
    hVoipHandle = 0;
    memset(&stChAttr,0,sizeof(HI_UNF_VOIP_CHN_ATTR_S));
    memset(&stAudDevPara,0,sizeof(HI_UNF_AUDADP_AUDDEV_PARA_S));
    memset(&stAudioInDevice,0,sizeof(HI_ALSA_CARD_INFO_S));
    memset(&stAudioOutDevice,0,sizeof(HI_ALSA_CARD_INFO_S));

    if(s32AudioDevId == HI_UNF_VOIP_AUD_DEV_ALSA)
    {
        //Get the ALSA audio in device
        s32Ret = Sample_Voip_GetAudioDevice(HI_UNF_VOIP_AUD_IN_DEV, &stAudioInDevice, &u32AiSampleRate);
        
        //Get the ALSA audio out device
        s32Ret = Sample_Voip_GetAudioOutDevice(&stAudioInDevice, &stAudioOutDevice, &u32AoSampleRate);
        sleep(1);  //only for printing the previous ALSA audio device info clearly.
    }
    
    s32Ret = HI_UNF_VOIP_Init();
    if(s32Ret != HI_SUCCESS)
    {
        printf("%s %d Voip initial failure! ErrCode=%x\n",__FILE__,__LINE__,s32Ret);
        return s32Ret;
    }
    
    s32Ret = HI_UNF_AUDADP_Init();
    if (HI_SUCCESS != s32Ret)
    {
        goto Voip_DeInit;
    }

    HI_UNF_AUDADP_RegisterEvent(Sample_AudAdp_EventCallBack, 0);

//    printf("\n Initial success, press 's' to start application !\n\n");
//    while(getchar()!='s');

    
    s32Ret= HI_UNF_VOIP_GetChDefaultAttr(HI_UNF_VOIP_MODE_VOIVE, &stChAttr);
    if(s32Ret != HI_SUCCESS)
    {
        printf("%s %d Voip get default attribute failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
        goto Voip_DeInit;
    }

    if(s32AudioDevId == HI_UNF_VOIP_AUD_DEV_SIO)
    {
        stChAttr.stDigitPara.stBody.u32DigitEnableFlag = 1; //enable DTMF process
    }

    if(s32AudioDevId == HI_UNF_VOIP_AUD_DEV_ALSA)
    {
        stAudDevPara.s32AiCardNo = stAudioInDevice.s32CardNo;
        stAudDevPara.s32AoCardNo = stAudioOutDevice.s32CardNo;
        stChAttr.stAudevPara.stBody.s32AiSampleRate = u32AiSampleRate;
        stChAttr.stAudevPara.stBody.s32AoSampleRate = u32AoSampleRate;
        HI_UNF_SND_SetSampleRate(HI_UNF_SND_0, stChAttr.stAudevPara.stBody.s32AoSampleRate);
//        printf("Selected audio in device: card [%d], name [%s] ,rate [%d\n", stAudioInDevice.s32CardNo,stAudioInDevice.szName,u32AiSampleRate);
    }
    
    stAudDevPara.s32AudioDevId = s32AudioDevId;
    stAudDevPara.s32AiSampleRate = stChAttr.stAudevPara.stBody.s32AiSampleRate;
    stAudDevPara.s32AiBitPerSample = stChAttr.stAudevPara.stBody.s32AiBitPerSample;
    stAudDevPara.s32AiChannels = stChAttr.stAudevPara.stBody.s32AiChannels;

    stAudDevPara.s32AoSampleRate = stChAttr.stAudevPara.stBody.s32AoSampleRate;
    stAudDevPara.s32AoBitPerSample = stChAttr.stAudevPara.stBody.s32AoBitPerSample;
    stAudDevPara.s32AoChannels = stChAttr.stAudevPara.stBody.s32AoChannels;
    
    stAudDevOptFlag.bit1AudInDev = 1;
    stAudDevOptFlag.bit1AudOutDev = 1;

    do
    {
    	s32Ret = HI_UNF_AUDADP_AudDev_Open(&stAudDevPara, stAudDevOptFlag);
        if(s32Ret != HI_SUCCESS)
        {
            printf("%s %d Audio adapter device open failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
            goto Voip_DeInit;
        }

        Sample_Voip_SetNetPara(&stChAttr.stNetPara);
        stChAttr.stAudevPara.stBody.s32AudioDevId = s32AudioDevId; 	// 0 -- SIO (SLIC)  1--Bluetooth  2--USB MIC+HIAO
        s32Ret = HI_UNF_VOIP_CreateChannel(HI_UNF_VOIP_MODE_VOIVE, &stChAttr, &hVoipHandle);
        if(s32Ret != HI_SUCCESS)
        {
            printf("%s %d Voip create channel failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
            goto Voip_DeInit;
        }
        s32Ret = HI_UNF_AUDADP_AudDev_Start(stAudDevPara.s32AudioDevId, stAudDevOptFlag);
        if(s32Ret != HI_SUCCESS)
        {
            printf("%s %d audio adapter start failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
            goto Voip_DestroyChannel;
        }

        s32Ret = HI_UNF_VOIP_RegisterEvent(hVoipHandle, Sample_Voip_EventCallBack, hVoipHandle);
        if(s32Ret != HI_SUCCESS)
        {
            printf("%s %d Voip register event cb function failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
            goto Voip_DestroyChannel;
        }

        if(u8VoipFuncSel == 1)
        {

            printf("\nSample voip play announcemount!\n");
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
                printf("%s %d Voip play announcemount failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
                goto Voip_CloseAudioFile;
            }
        
        }
        
//        sleep(1);
        printf("\npress 'q' key to quit!\n");
        printf("\npress '0~2' key to change the audio device!\n");
        printf("\npress 'r' key to continue next voip Create/Destroy channel circle!\n");
        
        while(1)
        {
            cInput = getchar();
            if(cInput == 'q')
            {
                bCircle = HI_FALSE;
                break;
            }
            else if(cInput == 'r')
            {
                bCircle = HI_TRUE;
                break;
            }
            else if((cInput>='0')&&(cInput<'3'))
            {
                HI_UNF_AUDADP_AudDev_Close(stAudDevPara.s32AudioDevId, stAudDevOptFlag);
                usleep(100*1000);   //To make sure the audio device be closed before open on next time

                s32AudioDevId = cInput-'0'; 	// 0 -- SIO(SLIC)  1--Bluetooth  2--USB MIC+HIAO

                if(s32AudioDevId == HI_UNF_VOIP_AUD_DEV_ALSA)
                {
                    //Get the ALSA audio in device
                    s32Ret = Sample_Voip_GetAudioDevice(HI_UNF_VOIP_AUD_IN_DEV, &stAudioInDevice, &u32AiSampleRate);
                    
                    //Get the ALSA audio out device
                    s32Ret = Sample_Voip_GetAudioOutDevice(&stAudioInDevice, &stAudioOutDevice, &u32AoSampleRate);
                    usleep(100*1000);   //To make sure the audio device be closed before open on next time

                    stAudDevPara.s32AiCardNo = stAudioInDevice.s32CardNo;
                    stAudDevPara.s32AoCardNo = stAudioOutDevice.s32CardNo;
                    stChAttr.stAudevPara.stBody.s32AiSampleRate = u32AiSampleRate;
                    stChAttr.stAudevPara.stBody.s32AoSampleRate = u32AoSampleRate;
                    HI_UNF_SND_SetSampleRate(HI_UNF_SND_0, stChAttr.stAudevPara.stBody.s32AoSampleRate);
                }
                else
                {
                    stChAttr.stAudevPara.stBody.s32AiSampleRate = HI_UNF_SAMPLE_RATE_8K;
                    stChAttr.stAudevPara.stBody.s32AoSampleRate = HI_UNF_SAMPLE_RATE_8K;
                }

                stAudDevPara.s32AudioDevId = s32AudioDevId;
                stAudDevPara.s32AiSampleRate = stChAttr.stAudevPara.stBody.s32AiSampleRate;
                stAudDevPara.s32AoSampleRate = stChAttr.stAudevPara.stBody.s32AoSampleRate;
                
	            s32Ret = HI_UNF_AUDADP_AudDev_Open(&stAudDevPara, stAudDevOptFlag);
                if(s32Ret != HI_SUCCESS)
                {
                    printf("%s %d Audio adapter device open failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
                    bCircle = HI_FALSE;
                    break;
                }

                if(s32AudioDevId == HI_UNF_VOIP_AUD_DEV_SIO)
                {
                    stChAttr.stDigitPara.stBody.u32DigitEnableFlag = 1; //enable DTMF process
                }
                else
                {
                    stChAttr.stDigitPara.stBody.u32DigitEnableFlag = 0; //disable DTMF process
                }
                stChAttr.stDigitPara.stChange.bit1DigitEnable = 1;
                
                stChAttr.stAudevPara.stBody.s32AudioDevId = s32AudioDevId;
                memset(&stChAttr.stAudevPara.stChang,0xff,sizeof(HI_UNF_AUDDEV_FLAG_S));
                s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stChAttr);
                if(s32Ret != HI_SUCCESS)
                {
                    printf("%s %d Voip modify channel attr failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
                    bCircle = HI_FALSE;
                    break;
                }
                else
                {
                    s32Ret = HI_UNF_AUDADP_AudDev_Start(stAudDevPara.s32AudioDevId, stAudDevOptFlag);
                    if(s32Ret != HI_SUCCESS)
                    {
                        printf("%s %d audio adapter start failure! ErrCode=%x\n",__FUNCTION__,__LINE__,s32Ret);
                        bCircle = HI_FALSE;
                        break;
                    }
                }
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
        HI_UNF_AUDADP_AudDev_Close(stAudDevPara.s32AudioDevId, stAudDevOptFlag);

    if(bCircle)
    {
        usleep(100*1000);   //To make sure the audio device be closed before open on next time
    }

}while(bCircle);    


Voip_DeInit:
    HI_UNF_VOIP_DeInit();
    HI_UNF_AUDADP_DeInit();
    return s32Ret;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 DevId = 0;
    HI_S32 AI_Ch = 0;
    HI_S32 AO_Ch = 1;

    if(3 == argc)
    {
        u8VoipFuncSel = strtol(argv[2],NULL,0);
        s32AudioDevId = strtol(argv[1],NULL,0);
    }
    else if(2 == argc)
    {
        s32AudioDevId = strtol(argv[1],NULL,0);
    }
    else
    {
        printf("Usage: %s para1 para2\n"
               "       para1 : audio device select, 0--SIO(SLIC),1--BLUETOOTH,2--USB MIC+HIAO\n"               
               "       para2 : function select, 0--Normal,1--Play Announcement\n"               
               ,argv[0]);
        printf("Example:%s 0 0\n", argv[0]);
        return (0);
    }

    if((s32AudioDevId<HI_UNF_VOIP_AUD_DEV_SIO)||(s32AudioDevId>HI_UNF_VOIP_AUD_DEV_ALSA))
    {
        printf("Invalid audio device selection : %d .\n",s32AudioDevId);
        printf("       para1 : 0--SIO(SLIC),1--BLUETOOTH,2--USB MIC+HIAO\n");
        return (0);
    }

    if(u8VoipFuncSel>1)
    {
        printf("Invalid function selection : %d .\n",u8VoipFuncSel);
        printf("       para2 : 0--Normal,1--Play Announcement\n");
        return (0);
    }
    
    HI_SYS_Init();
    //HI_SYS_PreAV(NULL);
    HI_SYS_SetLogLevel(HI_ID_VOIP_HME, HI_LOG_LEVEL_ERROR);
    //HI_SYS_SetLogLevel(HME_LOG_API, HI_LOG_LEVEL_ERROR);
    
    s32Ret = HIADP_Disp_Init(HI_UNF_ENC_FMT_720P_50);  
    
    /*Initial HIAO*/
    s32Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HIADP_Snd_Init failed.\n");
    }
    
    /*Initial SLIC*/
    s32Ret = HIADP_AIAO_Init(DevId, AI_Ch, AO_Ch, HI_UNF_SAMPLE_RATE_8K, AIAO_SAMPLE_PER_FRAME);
    if(s32Ret != HI_SUCCESS)
    {
        printf("%s %d Initial AIAO+SLIC failure! ErrCode=%d\n",__FILE__,__LINE__,s32Ret);
    }
    
    Sample_NetPara_Input();

    Sample_Voip_Run();
    
    HIADP_Snd_DeInit();
    HIADP_AIAO_DeInit();

    HIADP_Disp_DeInit();    
    
    HI_SYS_DeInit();
    
    return s32Ret;
}


