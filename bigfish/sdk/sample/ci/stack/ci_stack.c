/******************************************************************************

  Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ci_stack.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2014/6/20
  Description   :
  History       :
  1.Date        : 2014/6/20
    Author      : z00268517
    Modification: Created file

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "hi_unf_common.h"
#include "hi_unf_ci.h"
#include "ci_stack.h"

//#define _DEBUG


#define DEF_CIMAXPLUS_RESET_GPIO (7*8+0)       /* Reset CIMaX+ GPIO: 12_7 */
#define DEF_CIMAXPLUS_INT_GPIO   (7*8+4)       /* power ctrl GPIO: 13_0 */
#define DEF_HICI_POWER_CTRL_GPIO (5*8+0)       /* power ctrl GPIO: 5_0 */

#define HI_ERR_CI(fmt...) \
    HI_ERR_PRINT(HI_ID_CI, fmt)

#define HI_INFO_CI(fmt...) \
    HI_INFO_PRINT(HI_ID_CI, fmt)
    
#define HI_MALLOC_CI(size)  HI_MEM_Malloc(HI_ID_CI, size)
#define HI_FREE_CI(pAddr)   HI_MEM_Free(HI_ID_CI, pAddr)

#define ASN_READ_U16(ptr) (HI_U16)((*(HI_U8*)(ptr)) <<  8 | (*(HI_U8*)((ptr)+1)))
#define ASN_READ_U24(ptr) (HI_U32)((*(HI_U8*)(ptr)) << 16 | (*(HI_U8*)((ptr)+1)) << 8 | (*(HI_U8*)((ptr)+2)))
#define ASN_READ_U32(ptr) (HI_U32)((*(HI_U8*)(ptr)) << 24 | (*(HI_U8*)((ptr)+1)) << 16 | (*(HI_U8*)((ptr)+2)) << 8 |(*(HI_U8*)((ptr)+3)))

#define ASN_WRITE_U16(ptr, val) do \
                                { \
                                	*(HI_U8*)(ptr)     = (HI_U8)((val) >> 8); \
                                	*(HI_U8*)((ptr)+1) = (HI_U8)((val)); \
                                }while(0)
#define ASN_WRITE_U24(ptr, val) do \
                                { \
                                    *(HI_U8*)(ptr)     = (HI_U8)((val) >> 16); \
                                    *(HI_U8*)((ptr)+1) = (HI_U8)((val) >> 8); \
                                    *(HI_U8*)((ptr)+2) = (HI_U8)((val)); \
                                }while(0)
#define ASN_WRITE_U32(ptr, val) do												\
                                {												\
                                	*(HI_U8*)(ptr)     = (HI_U8)((val) >> 24); \
                                	*(HI_U8*)((ptr)+1) = (HI_U8)((val) >> 16); \
                                	*(HI_U8*)((ptr)+2) = (HI_U8)((val) >> 8); \
                                	*(HI_U8*)((ptr)+3) = (HI_U8)((val)); \
                                }while(0)

#define T_SB            0x80
#define T_RCV           0x81
#define T_CREATE_T_C    0x82
#define T_C_T_C_REPLY   0x83
#define T_DELETE_T_C    0x84
#define T_D_T_C_REPLY   0x85
#define T_REQUEST_T_C   0x86
#define T_NEW_T_C       0x87
#define T_T_C_ERROR     0x88
#define T_DATA_LAST     0xA0
#define T_DATA_MORE     0xA1

#define T_OPEN_SESSION_REQUEST      0x91
#define T_OPEN_SESSION_RESPONSE     0x92
#define T_CREATE_SESSION            0x93
#define T_CREATE_SESSION_RESPONSE   0x94  
#define T_CLOSE_SESSION_REQUEST     0x95
#define T_CLOSE_SESSION_RESPONSE    0x96
#define T_SESSION_NUMBER            0x90

#define RES_ID_RESOURCE_MANAGER             0x00010041
#define RES_ID_APPLICATION_INFORMATION      0x00020041
#define RES_ID_CONDITIONAL_ACCESS_SUPPORT   0x00030041
#define RES_ID_MMI                          0x00400041
#define RES_ID_DATE_TIME                    0x00240041
#define RES_ID_TUNE                         0x00200041

#define A_RM_PROFILE_ENQ                0x9F8010
#define A_RM_PROFILE                    0x9F8011
#define A_RM_PROFILE_CHANGE             0x9F8012
#define A_AI_APPLICATION_INFO_ENQ       0x9F8020 
#define A_AI_APPLICATION_INFO           0x9F8021
#define A_AI_ENTER_MENU                 0x9F8022
#define A_CA_INFO_ENQ                   0x9F8030
#define A_CA_INFO                       0x9F8031
#define A_CA_PMT                        0x9F8032
#define A_CA_PMT_REPLY                  0x9F8033
#define A_MMI_DISPLAY_CONTROL           0x9F8801
#define A_MMI_DISPLAY_REPLY             0x9F8802
#define A_MMI_TEXT_LAST                 0x9F8803
#define A_MMI_ENQ                       0x9F8807
#define A_MMI_ANSW                      0x9F8808
#define A_MMI_MENU_LAST                 0x9F8809
#define A_MMI_MENU_MORE                 0x9F880A
#define A_MMI_MENU_ANSW                 0x9F880B
#define A_MMI_LIST_LAST                 0x9F880C
#define A_MMI_LIST_MORE                 0x9F880D
#define A_DATE_TIME_ENQ                 0x9F8440
#define A_DATE_TIME                     0x9F8441
#define A_TUNE                          0x9F8400

#define WAIT_TIME (300)
#define HOST_BUFFERSIZE (1024)

#define MAX_TPDU_BUF_SIZE   4096
#define LPDU_HEAD_SIZE      2
#define MAX_TPDU_HEAD_SIZE  10
#define MAX_TPDU_SIZE       1024 - LPDU_HEAD_SIZE
#define MAX_SPDU_SIZE       9
#define MAX_APDU_SIZE       MAX_TPDU_SIZE - MAX_TPDU_HEAD_SIZE - MAX_SPDU_SIZE
#define MAX_CA_NUM          16

#ifdef HI_CI_DEV_CIMAXPLUS
#define DEVICE_CI_SLOT_NUM  2
#else
#define DEVICE_CI_SLOT_NUM  1
#endif

typedef enum ciRES_SESSION_NUM_E
{
    RES_SESSION_NUM_RESERVED,
    RES_SESSION_NUM_RM,
    RES_SESSION_NUM_AI,
    RES_SESSION_NUM_CA,
    RES_SESSION_NUM_MMI,
    RES_SESSION_NUM_DATE_TIME,
    RES_SESSION_NUM_TUNE,
    RES_SESSION_NUM_BUTT
}RES_SESSION_NUM_E;

typedef enum
{
    CI_EVENT_CAM_INSERT,
    CI_EVENT_CAM_REMOVE,
    CI_EVENT_DATA_SEND,
    CI_EVENT_POLLING,
	CI_EVENT_DESTORY,
    CI_EVENT_BUTT
}CI_EVENT_E;

typedef struct ciAPDU_S
{
    HI_U16 u16SessionNum;
    HI_U8  u8Data[MAX_APDU_SIZE];
    HI_U32 u32Size;
}APDU_S;

typedef struct ciSPDU_S
{
    HI_U8  u8Data[MAX_SPDU_SIZE];
    HI_U32 u32Size;
    APDU_S stAPDU;
}SPDU_S;

typedef struct ciTPDU_S
{
    HI_U8  u8Data[MAX_TPDU_HEAD_SIZE];
    HI_U32 u32Size;
    SPDU_S stSPDU;
}TPDU_S;

typedef struct ciEvent
{
    CI_EVENT_E enEvent;
    HI_UNF_CI_PCCD_E enCardId;
    HI_VOID *pParam;
    HI_U32  u32ParamSize;
}CI_EVENT_S;

typedef struct ciCI_EVENT_QUEUE_S
{
    CI_EVENT_S stEvent;
    struct ciCI_EVENT_QUEUE_S *stNext;
}CI_EVENT_QUEUE_S;

typedef struct ciSESSION_S
{
    HI_BOOL isOpen;
}SESSION_S;

typedef struct ciSTACK_INFO_S
{
    SESSION_S stSession[RES_SESSION_NUM_BUTT];
    HI_U8 *pBuffer;
    HI_U32 u32BufSize;
	HI_U16  u16CaIds[MAX_CA_NUM];
    HI_U8   u8NumCaIds;
}STACK_INFO_S;

static CI_EVENT_QUEUE_S *s_stQueueHead = HI_NULL;
static sem_t s_CISem;
    
static pthread_t          g_CIThdMonitor;
static pthread_t          g_CIThdMain;
static pthread_mutex_t    g_CIMutex;
static HI_BOOL g_bStopCIThread = HI_FALSE;

static STACK_INFO_S stStackInfo[HI_UNF_CI_PCCD_BUTT];
static HI_U8 s_u8TPDUBuf[MAX_TPDU_BUF_SIZE] = {0};
static HI_U32 s_u32ResoureId[]= 
{
    RES_ID_RESOURCE_MANAGER,
    RES_ID_APPLICATION_INFORMATION,
    RES_ID_CONDITIONAL_ACCESS_SUPPORT,
    RES_ID_MMI,
    RES_ID_DATE_TIME,
    RES_ID_TUNE
};

static HI_CI_HANDLE_FUN_S s_HandlerFun = {HI_NULL};

HI_U32 HI_CI_GetHandleFunc(HI_CI_HANDLE_FUN_S *funCI)
{
    *funCI = s_HandlerFun;
    return HI_SUCCESS;
}

HI_U32 HI_CI_SetHandleFunc(HI_CI_HANDLE_FUN_S *funCI)
{
    s_HandlerFun = *funCI;
    return HI_SUCCESS;
}

static HI_U32 SetLengthField(HI_U8 *pu8Data, HI_U32 u32Length)
{
    HI_U32 u32Len = 0;
    
    if (pu8Data == HI_NULL)
    {
        return 0;
    }
    
    if (u32Length < 0x80)
    {
        pu8Data[0] = (HI_U8)u32Length;
        u32Len = 1;
    }
    else if (u32Length < 0x100)
    {
        pu8Data[0] = 0x81;
        pu8Data[1] = (HI_U8)u32Length;
        u32Len = 2;
    }
    else if (u32Length < 0x10000)
    {
        pu8Data[0] = 0x82;
        ASN_WRITE_U16(&pu8Data[1], u32Length);
        u32Len = 3;
    }
    else if (u32Length < 0x1000000)
    {
        pu8Data[0] = 0x83;
        ASN_WRITE_U24(&pu8Data[1], u32Length);
        u32Len = 4;
    }
    else
    {
        pu8Data[0] = 0x84;
        ASN_WRITE_U32(&pu8Data[1], u32Length);
        u32Len = 5;
    }
    
    return u32Len;
}

static HI_U32 GetLengthField(HI_U8 *pu8Data, HI_U32 *pu32Length)
{
    HI_U32 u32Len = 0;

    *pu32Length = 0;
    
    if (pu8Data == HI_NULL)
    {
        return 0;
    }
    
    if (pu8Data[0] < 0x80)
    {
        *pu32Length = pu8Data[0];
        u32Len = 1;
    }
    else if (pu8Data[0] == 0x81)
    {
        *pu32Length = pu8Data[1];
        u32Len = 2;
    }
    else if (pu8Data[0] == 0x82)
    {
        *pu32Length = ASN_READ_U16(&pu8Data[1]);
        u32Len = 3;
    }
    else if (pu8Data[0] == 0x83)
    {
        *pu32Length = ASN_READ_U24(&pu8Data[1]);
        u32Len = 4;
    }
    else if (pu8Data[0] == 0x84)
    {
        *pu32Length = ASN_READ_U32(&pu8Data[1]);
        u32Len = 5;
    }
    
    return u32Len;
}

static HI_VOID QueueReset(HI_UNF_CI_PCCD_E enCardId)
{
    CI_EVENT_QUEUE_S *stQueue;
    CI_EVENT_QUEUE_S *stQueueTmp;

    stQueue = s_stQueueHead;
    pthread_mutex_lock(&g_CIMutex);
    while(stQueue != HI_NULL)
    {
        if (stQueue->stEvent.enCardId == enCardId)
        {
            stQueueTmp = stQueue;
            stQueue = stQueue->stNext;
            HI_FREE_CI(stQueueTmp->stEvent.pParam);    
            HI_FREE_CI(stQueueTmp);
        }
    }
    pthread_mutex_unlock(&g_CIMutex);
}

static void PrintQueueInfo(const char *name)
{
/*
	CI_EVENT_QUEUE_S *stQueue;
	HI_U32 id = 0;
	
	stQueue = s_stQueueHead;
	
	printf("%s\n", name);
	while(stQueue != HI_NULL)
    {
		printf("******************************\n");
		printf("id   : %d\n", id++);
		printf("Event: %d\n", stQueue->stEvent.enEvent);
		printf("Card : %d\n", stQueue->stEvent.enCardId);
		stQueue = stQueue->stNext;
	}
	
	int sval;
	sem_getvalue(&s_CISem, &sval);
	printf("sval %d\n", sval);
*/
}

static HI_BOOL QueueIsEmpty(HI_UNF_CI_PCCD_E enCardId)
{
    HI_BOOL bIsEmpty = HI_TRUE;
	CI_EVENT_QUEUE_S *stQueue;
	
	stQueue = s_stQueueHead;
    pthread_mutex_lock(&g_CIMutex);
	
	PrintQueueInfo(__FUNCTION__);
	
	while(stQueue != HI_NULL)
    {
		if (stQueue->stEvent.enCardId == enCardId)
		{
			bIsEmpty = HI_FALSE;
			break;
		}
		stQueue = stQueue->stNext;
	}
	
    pthread_mutex_unlock(&g_CIMutex);
	
    return bIsEmpty;
}

static HI_S32 QueuePutEvent(CI_EVENT_S *pstEvent)
{
    CI_EVENT_QUEUE_S *stQueue;
    CI_EVENT_QUEUE_S *stNext;

    if (pstEvent == HI_NULL )
    {
        return HI_SUCCESS;
    }
    
    pthread_mutex_lock(&g_CIMutex);
    
    stQueue = (CI_EVENT_QUEUE_S *)HI_MALLOC_CI(sizeof(CI_EVENT_QUEUE_S));
    if (stQueue == HI_NULL)
    {
        HI_ERR_CI("Malloc memory failed.\n");
        pthread_mutex_unlock(&g_CIMutex);
        return HI_FAILURE;
    }
    memset(stQueue, 0, sizeof(CI_EVENT_QUEUE_S));
    stQueue->stEvent = *pstEvent;
    stQueue->stNext = HI_NULL;
    if (s_stQueueHead == HI_NULL)
    {
        s_stQueueHead = stQueue;
    }
    else
    {
        stNext = s_stQueueHead;
        while(stNext->stNext != HI_NULL)
        {
            stNext = stNext->stNext;
        }
        stNext->stNext = stQueue;
    }
	
	sem_post(&s_CISem);

    pthread_mutex_unlock(&g_CIMutex);

	PrintQueueInfo(__FUNCTION__);
		
    return HI_SUCCESS;
}

static HI_S32 QueuePutTPDU(HI_UNF_CI_PCCD_E enCardId, TPDU_S *pstTPDU)
{
    CI_EVENT_S stEvent;

    if (pstTPDU == HI_NULL || pstTPDU->u32Size == 0)
    {
        return HI_SUCCESS;
    }
    
    stEvent.pParam= HI_MALLOC_CI(sizeof(TPDU_S));
    if (stEvent.pParam == HI_NULL)
    {
        HI_ERR_CI("Malloc memory failed.\n");
        return HI_FAILURE;
    }
    memset(stEvent.pParam, 0, sizeof(TPDU_S));
    memcpy(stEvent.pParam , pstTPDU, sizeof(TPDU_S));
    stEvent.u32ParamSize = sizeof(TPDU_S);
    stEvent.enCardId = enCardId;
    stEvent.enEvent = CI_EVENT_DATA_SEND;

    return QueuePutEvent(&stEvent);
    
}

static HI_S32 QueueGetEvent(CI_EVENT_S *pstEvent, HI_U32 u2TimeOutMs)
{
    struct timespec stTimeout;
    CI_EVENT_QUEUE_S *stQueue;
    HI_U32 s32Ret;

	PrintQueueInfo(__FUNCTION__);
			
    if (-1 == u2TimeOutMs)
    {
        s32Ret = sem_wait(&s_CISem);
        if (0 != s32Ret)
        {
            return HI_FAILURE; 
        }
    }
    else 
	{
		if (u2TimeOutMs > 1000)
		{
			stTimeout.tv_sec = u2TimeOutMs / 1000;
			stTimeout.tv_nsec = u2TimeOutMs % 1000 * 1000000;
		}
		else
		{
			stTimeout.tv_sec = 0;
			stTimeout.tv_nsec = u2TimeOutMs * 1000000;
		}
		s32Ret = sem_timedwait(&s_CISem, &stTimeout);
		if (0 != s32Ret)
		{
			return HI_FAILURE;
		}
	}

    pthread_mutex_lock(&g_CIMutex);

    if (s_stQueueHead == HI_NULL)
    {
        pthread_mutex_unlock(&g_CIMutex);
        return HI_FAILURE;
    }

    *pstEvent = s_stQueueHead->stEvent;
    stQueue = s_stQueueHead;
    s_stQueueHead = s_stQueueHead->stNext;
    HI_FREE_CI(stQueue);
    
    pthread_mutex_unlock(&g_CIMutex);
    
    return HI_SUCCESS;
}

static HI_S32 QueuePutSPDU(HI_UNF_CI_PCCD_E enCardId, SPDU_S *pstSPDU)
{   
    TPDU_S stTPDU;
    HI_U32 u32Index = 0;
    
    if (pstSPDU == HI_NULL || pstSPDU->u32Size == 0)
    {
        return HI_SUCCESS;
    }
	
    stTPDU.u8Data[u32Index++] = T_DATA_LAST;
    u32Index+=SetLengthField(&stTPDU.u8Data[u32Index], pstSPDU->u32Size + pstSPDU->stAPDU.u32Size + 1);
    stTPDU.u8Data[u32Index++] = enCardId+1;
    stTPDU.u32Size = u32Index;
    stTPDU.stSPDU = *pstSPDU;
#ifndef _DEBUG 
    HI_U32 i;

    HI_PRINT("send: ");
	for (i = 0; i < stTPDU.u32Size; i++)
    {
        HI_PRINT("%02x ", stTPDU.u8Data[i]);
    }
    for (i = 0; i < pstSPDU->u32Size; i++)
    {
        HI_PRINT("%02x ", pstSPDU->u8Data[i]);
    }
    for (i = 0; i < pstSPDU->stAPDU.u32Size; i++)
    {
        HI_PRINT("%02x ", pstSPDU->stAPDU.u8Data[i]);
    }
    HI_PRINT("\n");
 #endif   
    return QueuePutTPDU(enCardId, &stTPDU);
}

static HI_S32 QueuePutAPDU(HI_UNF_CI_PCCD_E enCardId, APDU_S *pstAPDU)
{   
    SPDU_S stSPDU;
    
    if (pstAPDU == HI_NULL || pstAPDU->u32Size == 0)
    {
        return HI_SUCCESS;
    }

    stSPDU.u8Data[0] = T_SESSION_NUMBER;
    stSPDU.u8Data[1] = 2;
    ASN_WRITE_U16(&stSPDU.u8Data[2], pstAPDU->u16SessionNum);
    stSPDU.u32Size = 4;
    stSPDU.stAPDU = *pstAPDU;
    
    return QueuePutSPDU(enCardId, &stSPDU);
}

static HI_VOID ShowString(HI_U8 *pu8Text, HI_U32 u32Size)
{
    HI_U32 i;  

    for (i=0; i<u32Size; i++)
    {
        HI_PRINT("%c", pu8Text[i]);
    }
}

static HI_U32 ShowUIMenu(HI_U8 **pu8Text, HI_U32 u32Size[], HI_U32 u32ItemNum)
{
    HI_U32 i;

    // TODO: Add your UI handler code here
    
    HI_PRINT("-------------------MMI MENU------------------:\n");
    HI_PRINT("[PTITLE]:  ");
    ShowString(pu8Text[0], u32Size[0]);
    HI_PRINT("\n");
    HI_PRINT("[STITLE]:  ");
    ShowString(pu8Text[1], u32Size[1]);
    HI_PRINT("\n");
    HI_PRINT("[BOTTOM]:  ");
    ShowString(pu8Text[2], u32Size[2]);
    HI_PRINT("\n");
    for (i=0; i<u32ItemNum; i++)
    {
        HI_PRINT("%d.  ", i+1);
        ShowString(pu8Text[i+3], u32Size[i+3]);
        HI_PRINT("\n");
    }
    HI_PRINT("---------------------------------------------\n");
    HI_PRINT("Please input 's' to start choice a item.\n");   
    
    if(s_HandlerFun.ShowUIMenu)
    {
        s_HandlerFun.ShowUIMenu(pu8Text, u32Size, u32ItemNum);
    }

    return HI_SUCCESS;
}

static HI_U32 ShowUIInput(HI_U8 *pu8Text, HI_U32 u32Size)
{
    // TODO: Add your UI handler code here

    HI_PRINT("-------------------MMI ENQ-------------------\n");
    ShowString(pu8Text, u32Size);
    HI_PRINT("\n");
    HI_PRINT("---------------------------------------------\n");
    HI_PRINT("Please input 'c' to start input pin code.\n");
    
    if(s_HandlerFun.ShowUIReq)                                   
    {                                                                      
        s_HandlerFun.ShowUIReq(pu8Text, u32Size);    
    }                                                                      

    return HI_SUCCESS;
}

HI_VOID tune(HI_U16 network_id,
             HI_U16 original_network_id,
             HI_U16 transport_stream_id,
             HI_U16 service_id)
{
    // TODO: Add your Tune handler code here

    if(s_HandlerFun.Tune)                                   
    {                                                                      
        s_HandlerFun.Tune(network_id, original_network_id, transport_stream_id, service_id);    
    } 
    
    return;
}

HI_VOID GetDateTime(HI_U8* mjd)
{
    static HI_U16 MONTH_DAYS[] = {
        0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    time_t curTime;
    struct tm *p;
    HI_U16 year;
    HI_U16 month;
    HI_U16 days;
    HI_U16 leap_count = 0;
    HI_U16 i = 0;
    
    time(&curTime);
    p = localtime(&curTime);
    year = p->tm_year + 1900;
    month = p->tm_mon;
    days = 0;
    
    for (i = 1859; i < year; i++)
    {
        if (i%400 == 0 || (i%4 == 0 && i%100 != 0))
        {
            leap_count++;
        }
    }
                                  
    days = (year - 1859) * 365;
    /* Add leap days (number of years divisible by 4) */
    days += leap_count;

    /*if this year is leap,then month_days[2] is 29*/
    if (year%400 == 0 || (year%4 == 0 && year%100 != 0))
    {
        MONTH_DAYS[2] = 29;
    }
   
    /* Add days for current year */
    for (i = 1; i < month; ++i)
    {
       days += MONTH_DAYS[i];
    }

    /*add days for current month*/
    days += p->tm_mday - 1;

    /*add the days between 1858-11-17 to 1858-12-31*/
    days += 45;

    mjd[0] = (HI_U8)(days >> 8);
    mjd[1] = (HI_U8)(days);
    mjd[2] = p->tm_hour;
    mjd[3] = p->tm_min;
    mjd[4] = p->tm_sec;
    mjd[5] = 0;
    mjd[6] = 0;

    printf("current date: %d.%d.%d %d:%d:%d\n", p->tm_year + 1900, p->tm_mon+1, 
        p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    
    return ;
}

static HI_S32 ApplicationLayer(HI_UNF_CI_PCCD_E enCardId, HI_U16 u16SessionNum, HI_U8 *pu8APDU, HI_U32 u32CmdLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Cmd;
    HI_U32 u32Index = 0;
    HI_U32 u32Length;
    HI_U32 u32TextLen;
    HI_U32 u32Nb;
    APDU_S stAPDU;
    HI_U8 *pu8Text[128] = {HI_NULL};
    HI_U32 au32Size[128] = {0};
    HI_U16 network_id;
    HI_U16 original_network_id;
    HI_U16 transport_stream_id;
    HI_U16 service_id;
    HI_U32 i;

    if (u16SessionNum >= RES_SESSION_NUM_BUTT)
    {                
        HI_ERR_CI("Invalid sessiom num 0x%04X\n", u16SessionNum);            
        return HI_FAILURE;         
    }
    
    memset(&stAPDU, 0, sizeof(stAPDU));
    stAPDU.u16SessionNum = u16SessionNum;

    u32Cmd = ASN_READ_U24(&pu8APDU[u32Index]);
    u32Index+=3;
    u32Index+=GetLengthField(&pu8APDU[u32Index], &u32Length);

    HI_INFO_CI("Application cmd 0x%02X\n", u32Cmd);
    switch(u32Cmd)
    {
    case A_RM_PROFILE_ENQ:
        u32Nb = sizeof(s_u32ResoureId)/sizeof(s_u32ResoureId[0]);
        stAPDU.u32Size = 0;
        ASN_WRITE_U24(&stAPDU.u8Data[stAPDU.u32Size], A_RM_PROFILE);
        stAPDU.u32Size += 3;
        stAPDU.u32Size+=SetLengthField(&stAPDU.u8Data[stAPDU.u32Size], u32Nb * 4);
        for (i=0; i<u32Nb; i++)
        {
            ASN_WRITE_U32(&stAPDU.u8Data[stAPDU.u32Size], s_u32ResoureId[i]);
            stAPDU.u32Size += 4; 
        }
        s32Ret = QueuePutAPDU(enCardId, &stAPDU);
				break;  
				    
    case A_RM_PROFILE:  
        stAPDU.u32Size = 0;
        ASN_WRITE_U24(&stAPDU.u8Data[stAPDU.u32Size], A_RM_PROFILE_CHANGE);
        stAPDU.u32Size += 3;
        stAPDU.u32Size+=SetLengthField(&stAPDU.u8Data[stAPDU.u32Size], 0);
        s32Ret = QueuePutAPDU(enCardId, &stAPDU);
    	break; 
    	          
    case A_RM_PROFILE_CHANGE:  
        stAPDU.u32Size = 0;
        ASN_WRITE_U24(&stAPDU.u8Data[stAPDU.u32Size], A_RM_PROFILE_ENQ);
        stAPDU.u32Size += 3;
        stAPDU.u32Size+=SetLengthField(&stAPDU.u8Data[stAPDU.u32Size], 0);
        s32Ret = QueuePutAPDU(enCardId, &stAPDU);;
    	break; 
    	    
    case A_AI_APPLICATION_INFO:
        HI_PRINT("Application Info:\n");
        HI_PRINT("application_type         0x%02X\n", pu8APDU[u32Index++]);
        HI_PRINT("application_manufacturer 0x%04X\n", ASN_READ_U16(&pu8APDU[u32Index]));
        u32Index+=2;
        HI_PRINT("manufacturer_code        0x%04X\n", ASN_READ_U16(&pu8APDU[u32Index]));
        u32Index+=2;
        u32Index++;
        HI_PRINT("menu_string: ");
        ShowString(&pu8APDU[u32Index], u32CmdLen - u32Index);
        HI_PRINT("\n");
    	break;
    	
    case A_CA_INFO:
        stStackInfo[enCardId].u8NumCaIds = 0;
        for (i=0; i<u32Length/2; i++)
        {
            stStackInfo[enCardId].u16CaIds[i] = ASN_READ_U16(&pu8APDU[u32Index]);
            u32Index+=2;
            stStackInfo[enCardId].u8NumCaIds++;
            HI_PRINT("CA_system_id: 0x%04X\n", stStackInfo[enCardId].u16CaIds[i]); 
        }
        if(s_HandlerFun.UpdateSystemId)                                   
        {                                                                      
            s_HandlerFun.UpdateSystemId(stStackInfo[enCardId].u16CaIds, stStackInfo[enCardId].u8NumCaIds);    
        } 
        break;
        
    case A_MMI_DISPLAY_CONTROL:
        stAPDU.u32Size = 0;
        ASN_WRITE_U24(&stAPDU.u8Data[stAPDU.u32Size], A_MMI_DISPLAY_REPLY);
        stAPDU.u32Size += 3;
        stAPDU.u32Size+=SetLengthField(&stAPDU.u8Data[stAPDU.u32Size], 2);
        stAPDU.u8Data[stAPDU.u32Size++] = 0x01;
        stAPDU.u8Data[stAPDU.u32Size++] = 0x01;
        s32Ret = QueuePutAPDU(enCardId, &stAPDU);;
        break;
    case A_MMI_ENQ:
        u32Index++;//blind_answer
        u32Index++;//answer_text_length
        s32Ret = ShowUIInput(&pu8APDU[u32Index], u32Length-2);
        break;
        
    case A_MMI_MENU_LAST:
    case A_MMI_LIST_LAST:
        u32Nb = pu8APDU[u32Index++];
        u32Index+=3;//text_tag
        u32Index += GetLengthField(&pu8APDU[u32Index], &u32TextLen);
        pu8Text[0] = &pu8APDU[u32Index];
        au32Size[0] = u32TextLen;
        u32Index+=u32TextLen;
        u32Index+=3;//text_tag
        u32Index += GetLengthField(&pu8APDU[u32Index], &u32TextLen);
        pu8Text[1] = &pu8APDU[u32Index];
        au32Size[1] = u32TextLen;
        u32Index+=u32TextLen;
        u32Index+=3;//text_tag
        u32Index += GetLengthField(&pu8APDU[u32Index], &u32TextLen);
        pu8Text[2] = &pu8APDU[u32Index];
        au32Size[2] = u32TextLen;
        u32Index+=u32TextLen;
        for (i=0; i<u32Nb; i++)
        {
            u32Index+=3;//text_tag
            u32Index += GetLengthField(&pu8APDU[u32Index], &u32TextLen);
            pu8Text[i+3] = &pu8APDU[u32Index];
            au32Size[i+3] = u32TextLen;
            u32Index+=u32TextLen;
        }
        s32Ret = ShowUIMenu(pu8Text, au32Size, u32Nb);
        break;
        
    case A_DATE_TIME_ENQ:
        stAPDU.u32Size = 0;
        ASN_WRITE_U24(&stAPDU.u8Data[stAPDU.u32Size], A_DATE_TIME);
        stAPDU.u32Size += 3;
        stAPDU.u32Size+=SetLengthField(&stAPDU.u8Data[stAPDU.u32Size], 7);
        GetDateTime(&stAPDU.u8Data[stAPDU.u32Size]);
        stAPDU.u32Size += 7;
        s32Ret = QueuePutAPDU(enCardId, &stAPDU);
    	break; 
    	
   case A_TUNE:
        network_id = ASN_READ_U16(&pu8APDU[u32Index]);
        u32Index+=2;
        original_network_id = ASN_READ_U16(&pu8APDU[u32Index]);
        u32Index+=2;
        transport_stream_id = ASN_READ_U16(&pu8APDU[u32Index]);
        u32Index+=2;
        service_id = ASN_READ_U16(&pu8APDU[u32Index]);
        u32Index+=2;
        tune(network_id, original_network_id, transport_stream_id, service_id);
    	break; 
    	
    default:
        HI_ERR_CI("Unsupport APDU 0x%06X\n", u32Cmd);
        s32Ret = HI_FAILURE;
    	break;     
    }

    return s32Ret;
}

static HI_U32 SessionOpen(HI_UNF_CI_PCCD_E enCardId, HI_U32 u32ResourceId, APDU_S *pstAPDU)
{
    HI_S32 s32Ret = HI_SUCCESS;

    switch(u32ResourceId)
    {
    case RES_ID_RESOURCE_MANAGER:
    {
        ASN_WRITE_U24(&pstAPDU->u8Data[0], A_RM_PROFILE_ENQ);
        pstAPDU->u8Data[3] = 0x00;
        pstAPDU->u32Size = 4;
        pstAPDU->u16SessionNum = RES_SESSION_NUM_RM;
        break;
    }
    case RES_ID_APPLICATION_INFORMATION:
    {
        ASN_WRITE_U24(&pstAPDU->u8Data[0], A_AI_APPLICATION_INFO_ENQ);
        pstAPDU->u8Data[3] = 0x00;
        pstAPDU->u32Size = 4;
        pstAPDU->u16SessionNum = RES_SESSION_NUM_AI;
        break;
    }
    case RES_ID_CONDITIONAL_ACCESS_SUPPORT:
    {
        ASN_WRITE_U24(&pstAPDU->u8Data[0], A_CA_INFO_ENQ);
        pstAPDU->u8Data[3] = 0x00;
        pstAPDU->u32Size = 4;
        pstAPDU->u16SessionNum = RES_SESSION_NUM_CA;
        break;
    }
    case RES_ID_MMI:
        pstAPDU->u16SessionNum = RES_SESSION_NUM_MMI;
        break;
	case RES_ID_DATE_TIME:
		pstAPDU->u16SessionNum = RES_SESSION_NUM_DATE_TIME;
        break;
	case RES_ID_TUNE:
		pstAPDU->u16SessionNum = RES_SESSION_NUM_TUNE;
        break;
    default:
        HI_ERR_CI("unsupport resource id 0x%08X\n", u32ResourceId);
        s32Ret = HI_FAILURE;
    }

    if (s32Ret == HI_SUCCESS)
    {
        stStackInfo[enCardId].stSession[pstAPDU->u16SessionNum].isOpen = HI_TRUE;
		printf("Session setup: 0x%x\r\n", pstAPDU->u16SessionNum);
    }

    return s32Ret;
    
}

static HI_U32 SessionClose(HI_UNF_CI_PCCD_E enCardId, HI_U16 u16SessionNum)
{
    if (u16SessionNum >= RES_SESSION_NUM_BUTT)
    {    
        HI_ERR_CI("Invalid sessiom num 0x%04X\n", u16SessionNum);
        return HI_FAILURE; 
    }
    
    stStackInfo[enCardId].stSession[u16SessionNum].isOpen = HI_FALSE;
    return HI_SUCCESS;    
}

static HI_S32 SessionLayer(HI_UNF_CI_PCCD_E enCardId, HI_U8 *pu8SPDU, HI_U32 u32CmdLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 u8Cmd;
    HI_U32 u32ResourceId;
    HI_U16 u16SessionNum;
    HI_U8 u8Status;
    HI_U32 u32Index = 0;
    HI_U32 u32Length;
    SPDU_S stSPDU;
    APDU_S stAPDU;

    memset(&stSPDU, 0, sizeof(stSPDU));
    memset(&stAPDU, 0, sizeof(stAPDU));

    u8Cmd = pu8SPDU[u32Index++];
    u32Length= pu8SPDU[u32Index++];
    HI_INFO_CI("Session cmd 0x%02X\n", u8Cmd);
    switch(u8Cmd)
    {
    case T_OPEN_SESSION_REQUEST:
        u32ResourceId  = ASN_READ_U32(&pu8SPDU[u32Index]);
        u32Index+=4;
        s32Ret = SessionOpen(enCardId, u32ResourceId, &stAPDU);
        u8Status = (s32Ret == HI_SUCCESS ? 0x00 : 0xF0);
        stSPDU.u8Data[0] = T_OPEN_SESSION_RESPONSE;
        stSPDU.u8Data[1] = 7;
        stSPDU.u8Data[2] = u8Status;
        ASN_WRITE_U32(&stSPDU.u8Data[3], u32ResourceId);
        stSPDU.u8Data[7] = (HI_U8)(stAPDU.u16SessionNum >> 8);;
        stSPDU.u8Data[8] = (HI_U8)stAPDU.u16SessionNum;
        stSPDU.u32Size = 9;
        s32Ret = QueuePutSPDU(enCardId, &stSPDU);
        s32Ret |= QueuePutAPDU(enCardId, &stAPDU);
        break;
        
    case T_CLOSE_SESSION_REQUEST: 
        u16SessionNum = ASN_READ_U16(&pu8SPDU[u32Index]);
        s32Ret = SessionClose(enCardId, u16SessionNum);
        u8Status = (s32Ret == HI_SUCCESS ? 0x00 : 0xF0);
        stSPDU.u8Data[0] = T_CLOSE_SESSION_RESPONSE;
        stSPDU.u8Data[1] = 3;
        stSPDU.u8Data[2] = u8Status;  
        ASN_WRITE_U16(&stSPDU.u8Data[3], u16SessionNum);
        stSPDU.u32Size = 5;
        s32Ret = QueuePutSPDU(enCardId, &stSPDU);
        break;
        
    case T_SESSION_NUMBER:
        u16SessionNum = ASN_READ_U16(&pu8SPDU[u32Index]);
        u32Index+=2;
        if (u16SessionNum < RES_SESSION_NUM_BUTT)
        {
            s32Ret = ApplicationLayer(enCardId, u16SessionNum, &pu8SPDU[u32Index], u32CmdLen - u32Index);
        }
        else
        {    
            HI_ERR_CI("Invalid sessiom num 0x%04X\n", u16SessionNum);
            s32Ret = HI_FAILURE; 
        }
        break;
        
    default:
        HI_ERR_CI("Unsupport Session cmd 0x%02X\n", u8Cmd);
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
    
}

static HI_S32 TransportLayer(HI_UNF_CI_PCCD_E enCardId, HI_U8 *pu8TPDU, HI_U32 u32TPDUCmdLen)
{
    static HI_U8  s_abTpdu[HI_UNF_CI_PCCD_BUTT][MAX_TPDU_BUF_SIZE]= {{0},{0}};
    static HI_U32 s_u32TpduLen[HI_UNF_CI_PCCD_BUTT] = {0,0}; 
    HI_S32 s32Ret = HI_SUCCESS;    
    HI_U8 u8Cmd;
    HI_U32 u32Index = 0;
    HI_U32 u32Length;
    TPDU_S stTPDU;
    HI_U32 i;
	HI_U8  *pbTpdu = HI_NULL;
	HI_U32 u32TpduLen = 0;
	pbTpdu = s_abTpdu[enCardId];
	u32TpduLen = s_u32TpduLen[enCardId];

    memset(&stTPDU, 0, sizeof(stTPDU));

    while(u32Index < u32TPDUCmdLen)
    {
        u8Cmd = pu8TPDU[u32Index++];
        u32Index += GetLengthField(&pu8TPDU[u32Index], &u32Length);
        u32Index++;//t_c_id
        HI_INFO_CI("TC cmd 0x%02X\n", u8Cmd);
        switch(u8Cmd)
        {
        case T_SB:  
            if (pu8TPDU[u32Index] == 0x80)
            {
                stTPDU.u8Data[0] = T_RCV;
                stTPDU.u8Data[1] = 0x01;
                stTPDU.u8Data[2] = enCardId+1;
                stTPDU.u32Size = 3;
                s32Ret = QueuePutTPDU(enCardId, &stTPDU);
            }
            break;
            
         case T_DATA_MORE:
            {
#ifndef _DEBUG 
				if(u32Length - 1 > 0)
				{
					HI_PRINT("recv: ");
					HI_PRINT("%02x %02x %02x ", u8Cmd, u32Length, enCardId+1);
					for (i = 0; i < u32Length - 1; i++)
					{
						HI_PRINT("%02x ", pu8TPDU[u32Index+i]);
					}
					HI_PRINT("\n");
				}
#endif
                memcpy(&s_abTpdu[s_u32TpduLen], &pu8TPDU[u32Index], u32Length - 1);
                s_u32TpduLen += u32Length - 1;
            }
            break;

         case T_DATA_LAST:
		    {
#ifndef _DEBUG 
				if(u32Length - 1 > 0)
				{
					HI_PRINT("recv: ");
					HI_PRINT("%02x %02x %02x ", u8Cmd, u32Length, enCardId+1);
					for (i = 0; i < u32Length - 1; i++)
					{
						HI_PRINT("%02x ", pu8TPDU[u32Index+i]);
					}
					HI_PRINT("\n");
				}
#endif
				memcpy(&s_abTpdu[s_u32TpduLen], &pu8TPDU[u32Index], u32Length - 1);
                s_u32TpduLen += u32Length - 1;
				
	 			if (s_u32TpduLen > 0)
				{
					s32Ret = SessionLayer(enCardId, s_abTpdu, s_u32TpduLen);
				}
				memset(s_abTpdu,0x00, sizeof(s_abTpdu));
				s_u32TpduLen = 0;
			}
            break;
            
        case T_C_T_C_REPLY:
            break;
            
        default:
            HI_ERR_CI("Unsupport TC cmd 0x%02X\n", u8Cmd);
            s32Ret = HI_FAILURE;
        }
        u32Index+=u32Length-1;
    }
    return s32Ret;
}

static HI_S32 TSByPass(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId, HI_BOOL bTSByPass)
{
    HI_S32 s32Ret = HI_SUCCESS;

#ifdef HI_CI_DEV_HICI
    HI_UNF_CI_PCCD_TSCTRL_PARAM_U unParam;

    unParam.stByPass.bByPass = bTSByPass;
    s32Ret = HI_UNF_CI_PCCD_TSCtrl(enCIPort, enCardId, HI_UNF_CI_PCCD_TSCTRL_BYPASS, &unParam);

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CI("HI_UNF_CI_PCCD_TSCtrl(%d, %d) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
    }
#endif
    return s32Ret;
}

static HI_S32 CardInsert(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId)
{
    HI_S32 s32Ret;
    HI_U32 u32WaitTimes;
    HI_U16 u16BufferSize = HOST_BUFFERSIZE;
    HI_UNF_CI_PCCD_READY_E enReady = HI_UNF_CI_PCCD_BUSY;

    /* Power ON */
    s32Ret = HI_UNF_CI_PCCD_CtrlPower(enCIPort, enCardId, HI_UNF_CI_PCCD_CTRLPOWER_ON);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CI("HI_UNF_CI_PCCD_CtrlPower(%d, %d, ON) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
        return s32Ret;
    }
    /* Reset Card */
    s32Ret = HI_UNF_CI_PCCD_Reset(enCIPort, enCardId);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CI("HI_UNF_CI_PCCD_Reset(%d, %d) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
        return s32Ret;
    }
    HI_PRINT("HI_UNF_CI_PCCD_Reset(%d, %d) success !!!\n", enCIPort, enCardId);
    /* Wait ready, 3s, optional, automatically wait in HI_UNF_CI_PCCD_CheckCIS() */
    for (u32WaitTimes = 0; u32WaitTimes < WAIT_TIME; u32WaitTimes++)
    {
        s32Ret = HI_UNF_CI_PCCD_IsReady(enCIPort, enCardId, &enReady);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_CI("HI_UNF_CI_PCCD_IsReady(%d, %d) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
            return s32Ret;
        }
        if (HI_UNF_CI_PCCD_READY == enReady)
        {
            HI_INFO_CI("HI_UNF_CI_PCCD_IsReady(%d, %d) Card ready.\n", enCIPort, enCardId);
            break;
        }

        /* 10ms */
        usleep(10000);
    }

    if (u32WaitTimes == WAIT_TIME)
    {
        HI_ERR_CI("HI_UNF_CI_PCCD_IsReady(%d, %d) Card ready timeout.\n", enCIPort, enCardId);
        return HI_FAILURE;
    }
    /* Check CIS */
    s32Ret = HI_UNF_CI_PCCD_CheckCIS(enCIPort, enCardId);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CI("HI_UNF_CI_PCCD_CheckCIS(%d, %d) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
        return s32Ret;
    }
    HI_PRINT("HI_UNF_CI_PCCD_CheckCIS(%d, %d) success !!!\n", enCIPort, enCardId);
    /* Configure COR */
    s32Ret = HI_UNF_CI_PCCD_WriteCOR(enCIPort, enCardId);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CI("HI_UNF_CI_PCCD_WriteCOR(%d, %d) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
        return s32Ret;
    }
    HI_PRINT("HI_UNF_CI_PCCD_WriteCOR(%d, %d) success !!!\n", enCIPort, enCardId);
    /* Reset IO interface */
    s32Ret = HI_UNF_CI_PCCD_IOReset(enCIPort, enCardId);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CI("HI_UNF_CI_PCCD_IOReset(%d, %d) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
        return s32Ret;
    }
    HI_PRINT("HI_UNF_CI_PCCD_IOReset(%d, %d) success !!!\n", enCIPort, enCardId);
    /* Negotiate buffer size */
    s32Ret = HI_UNF_CI_PCCD_NegBufferSize(enCIPort, enCardId, &u16BufferSize);
    if (HI_SUCCESS == s32Ret)
    {
        HI_PRINT("HI_UNF_CI_PCCD_NegBufferSize(%d, %d) SUCCESS: %d Bytes.\n", enCIPort, enCardId, u16BufferSize);
    }
    else
    {
        HI_ERR_CI("HI_UNF_CI_PCCD_NegBufferSize(%d, %d) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
        return s32Ret;
    }
    stStackInfo[enCardId].u32BufSize = u16BufferSize;
    stStackInfo[enCardId].pBuffer = (HI_U8*)HI_MALLOC_CI(u16BufferSize);
    if (HI_NULL == stStackInfo[enCardId].pBuffer)
    {
        HI_ERR_CI("memory alloc fail\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

static HI_S32 CardRemove(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId)
{    
    if (HI_NULL != stStackInfo[enCardId].pBuffer)
    {
        HI_FREE_CI(stStackInfo[enCardId].pBuffer);
        stStackInfo[enCardId].pBuffer = HI_NULL;
    }

    QueueReset(enCardId);

    /* Power OFF */
    return HI_UNF_CI_PCCD_CtrlPower(enCIPort, enCardId, HI_UNF_CI_PCCD_CTRLPOWER_OFF);
}

static HI_S32 WriteLPDU(HI_UNF_CI_PORT_E enCIPort, 
                        HI_UNF_CI_PCCD_E enCardId, 
                        HI_U8 *pu8LPDU, 
                        HI_U32 u32LPDULen)
{
    HI_S32 s32Ret;
    HI_U32 u32WaitTimes;

    HI_U32 u32WriteOKLen = 0;
    HI_U8 u8StatusValue;
    
    /*
     * Wait FRee status, 300ms timeout
     */
    for (u32WaitTimes = 0; u32WaitTimes < WAIT_TIME; u32WaitTimes++)
    {
        s32Ret = HI_UNF_CI_PCCD_GetStatus(enCIPort, enCardId, HI_UNF_CI_PCCD_STATUS_BIT_FR, &u8StatusValue);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_CI("HI_UNF_CI_PCCD_GetStatus(%d, %d, FR) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
            return s32Ret;
        }

        if (u8StatusValue)
        {
            break;
        }

        usleep(1000);
    }

    if (u32WaitTimes == WAIT_TIME)
    {
        HI_ERR_CI("WriteLPDU(%d, %d) FAIL!!! Wait FREE time out.\n", enCIPort, enCardId);
        return HI_FAILURE;
    }

    /* Write data */
    s32Ret = HI_UNF_CI_PCCD_IOWrite(enCIPort, enCardId, pu8LPDU, u32LPDULen, &u32WriteOKLen);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CI("HI_UNF_CI_PCCD_IOWrite(%d, %d) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
        return s32Ret;
    }
#ifdef _DEBUG
    HI_U32 i;

    HI_PRINT("Send: ");
    for (i = 0; i < u32WriteOKLen; i++)
    {
        HI_PRINT("%02x ", pu8LPDU[i]);
    }
    HI_PRINT("\n");
#endif

    return HI_SUCCESS;
}

static HI_S32 ReadLPDU(HI_UNF_CI_PORT_E enCIPort, 
                        HI_UNF_CI_PCCD_E enCardId, 
                        HI_U8 *pu8LPDU, 
                        HI_U32 *pu32LPDULen)
{
    HI_S32 s32Ret;
    HI_U32 u32WaitTimes;
    HI_U32 u32ReadLen = 0;
    HI_U8 u8StatusValue;
    
    /*
     * Wait Data Avalible status, 300ms timeout.
     */
    for (u32WaitTimes = 0; u32WaitTimes < WAIT_TIME; u32WaitTimes++)
    {
        s32Ret = HI_UNF_CI_PCCD_GetStatus(enCIPort, enCardId, HI_UNF_CI_PCCD_STATUS_BIT_DA, &u8StatusValue);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_CI("HI_UNF_CI_PCCD_GetStatus(%d, %d, DA) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
            return s32Ret;
        }

        if (u8StatusValue)
        {
            break;
        }

        usleep(1000);
    }

    if (u32WaitTimes == WAIT_TIME)
    {
        HI_ERR_CI("ReadLPDU(%d, %d) FAIL!!! Wait DA time out.\n", enCIPort, enCardId);
        return HI_FAILURE;
    }

    /* Read data */
    s32Ret = HI_UNF_CI_PCCD_IORead(enCIPort, enCardId, pu8LPDU, &u32ReadLen);
    if (HI_SUCCESS == s32Ret)
    {
#ifdef _DEBUG
        HI_U32 i;

        HI_PRINT("recv: ");
        for (i = 0; i < u32ReadLen; i++)
        {
            HI_PRINT("%02x ", pu8LPDU[i]);
        }
        HI_PRINT("\n");
#endif
        *pu32LPDULen = u32ReadLen;
    }
    else
    {
        HI_ERR_CI("HI_UNF_CI_PCCD_IORead(%d, %d) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

static HI_S32 AccessCam(HI_UNF_CI_PCCD_E enCardId, HI_U8 *pTPDU, HI_U32 *u32TpduLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_CI_PORT_E enCIPort;
    HI_U32 u32RWLen;
    HI_U32 u32LPDULen;
    HI_U32 u32CmdLen;
    HI_U8 *pLPDU = HI_NULL;

    enCIPort = HI_UNF_CI_PORT_0;
    u32CmdLen = *u32TpduLen;
	pLPDU = stStackInfo[enCardId].pBuffer;
	
    if((pTPDU == HI_NULL) || (*u32TpduLen == 0))
    {
        return HI_SUCCESS;
    }
        
    /* Write a TPDU */
    u32RWLen = 0;
    pLPDU[1] = 0x80;
    pLPDU[0] = enCardId+1;
    while(pLPDU[1] == 0x80)
    {
        if (u32CmdLen > stStackInfo[enCardId].u32BufSize - LPDU_HEAD_SIZE)
        {
            u32LPDULen = stStackInfo[enCardId].u32BufSize - LPDU_HEAD_SIZE;                                
            pLPDU[1] = 0x80;
        }
        else
        {
            u32LPDULen = u32CmdLen;                                
            pLPDU[1] = 0x00;
        }
        memcpy(&pLPDU[2], &pTPDU[u32RWLen], u32LPDULen);
        s32Ret = WriteLPDU(enCIPort, enCardId, pLPDU, u32LPDULen+LPDU_HEAD_SIZE);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_CI("WriteLPDU(%d, %d) fail: 0x%08x.\n", enCIPort, enCardId, s32Ret);
            return HI_FAILURE;
        }
        u32RWLen+=u32LPDULen;
        u32CmdLen-=u32LPDULen;
    }

    /* Read a TPDU */
	pLPDU[0] = enCardId+1;
    pLPDU[1] = 0x80;
    u32RWLen = 0;
    while(pLPDU[1] == 0x80)
    {
        s32Ret = ReadLPDU(enCIPort, enCardId, pLPDU, &u32LPDULen);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_CI("ReadLPDU(%d, %d) fail: 0x%08x.\n", enCIPort, enCardId, s32Ret);
            return HI_FAILURE;
        }
        u32LPDULen-=LPDU_HEAD_SIZE;
        memcpy(&pTPDU[u32RWLen], &pLPDU[2],  u32LPDULen);
        u32RWLen+=u32LPDULen;
    }

    *u32TpduLen = u32RWLen;
    
    return HI_SUCCESS;
}

static HI_VOID CITthreadMonitor(HI_VOID *args)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_CI_PORT_E enCIPort;
    HI_UNF_CI_PCCD_E enCardId;
    HI_UNF_CI_PCCD_STATUS_E enStatus;
    HI_UNF_CI_PCCD_STATUS_E aenCardStatus[HI_UNF_CI_PCCD_BUTT] =
    {HI_UNF_CI_PCCD_STATUS_ABSENT, HI_UNF_CI_PCCD_STATUS_ABSENT};
    CI_EVENT_S stEvent;

    enCIPort = HI_UNF_CI_PORT_0;
    enCardId = HI_UNF_CI_PCCD_A;
    stEvent.pParam= HI_NULL;
    stEvent.u32ParamSize = 0;

    while (!g_bStopCIThread)
    {      
        for (enCardId=HI_UNF_CI_PCCD_A; enCardId<DEVICE_CI_SLOT_NUM; enCardId++)
        {
            /* Detect card  */
            s32Ret = HI_UNF_CI_PCCD_Detect(enCIPort, enCardId, &enStatus);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_CI("HI_UNF_CI_PCCD_Detect(%d, %d) fail: 0x%08x.\n", enCIPort, enCardId, s32Ret);
            }
            else
            {
                /* Insert or remove */
                if (enStatus != aenCardStatus[enCardId])
                {
                    /* Remove */
                    if (HI_UNF_CI_PCCD_STATUS_ABSENT == enStatus)
                    {
                        HI_PRINT("Card %c remove.\n", enCardId == HI_UNF_CI_PCCD_A ? 'A' : 'B');
                        stEvent.enEvent = CI_EVENT_CAM_REMOVE;
                    }
                    /* Insert */
                    else if (HI_UNF_CI_PCCD_STATUS_PRESENT == enStatus)
                    {
                        HI_PRINT("Card %c insert.\n", enCardId == HI_UNF_CI_PCCD_A ? 'A' : 'B');
                        stEvent.enEvent = CI_EVENT_CAM_INSERT;
                    }           
                    aenCardStatus[enCardId] = enStatus;
                    stEvent.enCardId = enCardId;
                    s32Ret = QueuePutEvent(&stEvent);
                    if (HI_SUCCESS != s32Ret)
                    {
                        HI_ERR_CI("QueuePutEvent fail: 0x%x.\n", s32Ret);
                    }
                }
                else if ((enStatus == HI_UNF_CI_PCCD_STATUS_PRESENT) && QueueIsEmpty(enCardId))
                {
                    stEvent.enEvent = CI_EVENT_POLLING;
                    stEvent.enCardId = enCardId;
                    s32Ret = QueuePutEvent(&stEvent);
                }
            }
        }
        usleep(100000);    /* 100ms */
    }
	
	stEvent.enEvent = CI_EVENT_DESTORY;
	s32Ret = QueuePutEvent(&stEvent);
	
    return;
}

static HI_VOID CITthreadMain(HI_VOID *args)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_CI_PORT_E enCIPort;
	HI_UNF_CI_PCCD_E enCardId;
    HI_U32 u32CmdLen = 0;
	HI_BOOL bIsRun = HI_TRUE;
    HI_BOOL bIsConnect[HI_UNF_CI_PCCD_BUTT] = {HI_FALSE};
    TPDU_S *pstTPDU;

    CI_EVENT_S stEvent;

    enCIPort = HI_UNF_CI_PORT_0;

    while (bIsRun)
    {      
        u32CmdLen = 0;
        memset(&stEvent,0, sizeof(stEvent));
        s32Ret = QueueGetEvent(&stEvent, -1);//100ms
        if(s32Ret == HI_FAILURE)
        {
             continue;
        }
		enCardId = stEvent.enCardId;
//		HI_PRINT("enCardId %d stEvent.enEvent %d\n", enCardId, stEvent.enEvent);
        switch(stEvent.enEvent)
        {
        case CI_EVENT_CAM_REMOVE:
            s32Ret = CardRemove(enCIPort, enCardId);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_CI("CardRemove(%d, %d) fail: 0x%08x.\n", enCIPort, enCardId, s32Ret);
            }
            /* Control TS pass card or not */
            s32Ret = TSByPass(enCIPort, enCardId, HI_TRUE);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_CI("TSByPass(%d, %d) fail: 0x%08x.\n", enCIPort, enCardId, s32Ret);
            }
			HI_PRINT("TSByPass(%d, %d) success: TRUE\n", enCIPort, enCardId);
            memset(&stStackInfo[enCardId], 0, sizeof(stStackInfo[0]));
            bIsConnect[enCardId] = HI_FALSE;
            break;
            
        case CI_EVENT_CAM_INSERT:
            s32Ret = CardInsert(enCIPort, enCardId);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_CI("CardInsert(%d, %d) fail: 0x%08x.\n", enCIPort, enCardId, s32Ret);
                break;
            }
            /* Control TS pass card or not */
            s32Ret = TSByPass(enCIPort, enCardId, HI_FALSE);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_CI("TSByPass(%d, %d) fail: 0x%08x.\n", enCIPort, enCardId, s32Ret);
            }
			HI_PRINT("TSByPass(%d, %d) success: FALSE\n", enCIPort, enCardId);
            u32CmdLen = 3;
			s_u8TPDUBuf[0] = T_CREATE_T_C;
			s_u8TPDUBuf[1] = 0x01;
			s_u8TPDUBuf[2] = enCardId+1;
            bIsConnect[enCardId] = HI_TRUE;
            break;
            
        case CI_EVENT_DATA_SEND:
            pstTPDU = (TPDU_S*)stEvent.pParam;
            if (HI_NULL != pstTPDU)
            {
                 u32CmdLen = 0;
                 memcpy(&s_u8TPDUBuf[u32CmdLen], pstTPDU->u8Data, pstTPDU->u32Size);
                 u32CmdLen += pstTPDU->u32Size;
                 memcpy(&s_u8TPDUBuf[u32CmdLen], pstTPDU->stSPDU.u8Data, pstTPDU->stSPDU.u32Size);
                 u32CmdLen += pstTPDU->stSPDU.u32Size;
                 memcpy(&s_u8TPDUBuf[u32CmdLen], pstTPDU->stSPDU.stAPDU.u8Data, pstTPDU->stSPDU.stAPDU.u32Size);
                 u32CmdLen += pstTPDU->stSPDU.stAPDU.u32Size;
                 break;
            }
            
        case CI_EVENT_POLLING:
            u32CmdLen = 3;
			s_u8TPDUBuf[0] = T_DATA_LAST;
			s_u8TPDUBuf[1] = 0x01;
			s_u8TPDUBuf[2] = enCardId+1;
            break;
			
        case CI_EVENT_DESTORY:
			bIsRun = HI_FALSE;
			break;
			
        default:
            break;
        }

        HI_FREE_CI(stEvent.pParam);
        if ((bIsConnect[enCardId] == HI_TRUE) && (u32CmdLen > 0))
        {
            s32Ret = AccessCam(enCardId, s_u8TPDUBuf, &u32CmdLen);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_CI("AccessCam(%d, %d) fail: 0x%08x.\n", enCIPort, enCardId, s32Ret);
                bIsConnect[enCardId] = HI_FALSE;
                continue;
            }
            s32Ret = TransportLayer(enCardId, s_u8TPDUBuf, u32CmdLen);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_CI("TransportLayer(%d, %d) fail: 0x%08x.\n", enCIPort, enCardId, s32Ret);
                continue;
            }
        }
    }

    return;
}

static HI_S32 ParsePMT(HI_U8 *u8PmtBuffer, HI_U8 *pHead, HI_U8 *pu8CADes, HI_U32 *pu32Len)
{
    HI_S32 s32Ret = HI_SUCCESS;  
    HI_U8   *source_p;
    int pmt_section_len;
    int info_len;
    HI_U16  index;
    HI_U16 u16InfoLeIndex;
    HI_U32 u32DesLen = 0;

    source_p = u8PmtBuffer;

    if(*source_p != 0x02)       /*PMT Table ID*/
    {
        s32Ret = HI_FAILURE;
        HI_ERR_CI(("CA PMT err!\n"));
        return s32Ret;
    }
   
    pmt_section_len = (((source_p[1]&0x0f)<<8)|source_p[2])-4;
    if(pmt_section_len<9)
    {
        s32Ret = HI_FAILURE;
        HI_ERR_CI(("CA PMT err!\n"));
        return s32Ret;
    }

	memcpy(pHead, &source_p[3], 3);/*program_number,version_number,current_next_indicator*/
 
    source_p += 10;
    pmt_section_len -= 7;
    
    info_len = ((source_p[0]&0x0f)<<8)|source_p[1];     /*program_info_length*/
    source_p += 2;
    pmt_section_len -= 2;

    *pu32Len = 0;
    u16InfoLeIndex = u32DesLen;
    u32DesLen+=2;

    pu8CADes[u32DesLen++] = 0x01; /*ca_pmt_cmd_id*/
	
    while (info_len>0)
    {        
        if (*source_p == 0x09)       /*CA descriptor*/
        {
            memcpy(&pu8CADes[u32DesLen], source_p, source_p[1]+2);
            u32DesLen+=source_p[1]+2;
        }
            
        index = source_p[1] + 2;    /*descriptor_length*/
        pmt_section_len -= index;
        info_len -= index;
        source_p += index;
    }

    if (u32DesLen - u16InfoLeIndex == 3)
    {
        u32DesLen--;
        pu8CADes[u16InfoLeIndex] = 0x00;
        pu8CADes[u16InfoLeIndex+1] = 0x00;
    }
    else
    {
        pu8CADes[u16InfoLeIndex] = (HI_U8)((u32DesLen - u16InfoLeIndex - 2) >> 8);
        pu8CADes[u16InfoLeIndex+1] = (HI_U8)(u32DesLen - u16InfoLeIndex - 2);
    }
	
    while (pmt_section_len>0)
    {   
        index = 0;
		
        pu8CADes[u32DesLen++] = source_p[index++]; /*stream_type*/
        pu8CADes[u32DesLen++] = source_p[index++];
        pu8CADes[u32DesLen++] = source_p[index++]; /*elementary_PID*/
        
        source_p += index;
        pmt_section_len -= index;
        
        info_len = ((source_p[0]&0x0f)<<8)|source_p[1];     /*es_info_length*/
        source_p += 2;
        pmt_section_len -= 2;

        u16InfoLeIndex = u32DesLen;
        u32DesLen+=2; /*ES_info_length*/
		pu8CADes[u32DesLen++] = 0x01;/*ca_pmt_cmd_id*/
        while (info_len>0)
        {
            if (*source_p == 0x09)       /*CA descriptor*/
            {
                memcpy(&pu8CADes[u32DesLen], source_p, source_p[1]+2);
                u32DesLen+=source_p[1]+2;
            }
            index = source_p[1] + 2;    /*descriptor_length*/
            pmt_section_len -= index;
            info_len -= index;
            source_p += index;
        }
		if (u32DesLen - u16InfoLeIndex - 2 > 1)
        {
			pu8CADes[u16InfoLeIndex] = (HI_U8)((u32DesLen - u16InfoLeIndex - 2) >> 8);
			pu8CADes[u16InfoLeIndex+1] = (HI_U8)(u32DesLen - u16InfoLeIndex - 2); 
		}
		else
		{
			pu8CADes[u16InfoLeIndex] = 0x00;
			pu8CADes[u16InfoLeIndex+1] = 0x00; 
			u32DesLen--;
		}
    }
	
		
	*pu32Len = u32DesLen;
		
    return s32Ret;
}

HI_U32 HI_CI_UpdatePMT(HI_UNF_CI_PCCD_E enCardId, HI_U8  *pPmtData)
{
    APDU_S stAPDU;
    HI_U8 u8CADes[1024] = {0};
    HI_U32 u32Len;
    HI_U8 u8Head[3];

    if (pPmtData == HI_NULL)
    {
        HI_ERR_CI("Invalid para\n");
        return HI_FAILURE;
    }
    if (!stStackInfo[enCardId].stSession[RES_SESSION_NUM_CA].isOpen)
    {
        HI_ERR_CI("CA Session not opened\n");
        return HI_FAILURE;
    }

    if (ParsePMT(pPmtData, u8Head, u8CADes, &u32Len) != HI_SUCCESS)
    {
        HI_ERR_CI("Parse PMT error\n");
        return HI_FAILURE;
    }    
    
    stAPDU.u32Size = 0;
    stAPDU.u16SessionNum = RES_SESSION_NUM_CA;
    ASN_WRITE_U24(&stAPDU.u8Data[stAPDU.u32Size], A_CA_PMT);
    stAPDU.u32Size += 3;
    stAPDU.u32Size+=SetLengthField(&stAPDU.u8Data[stAPDU.u32Size], u32Len + 4);
    stAPDU.u8Data[stAPDU.u32Size++] = 0x03;
	memcpy(&stAPDU.u8Data[stAPDU.u32Size], u8Head, 3);/*program_number,version_number,current_next_indicator*/
    stAPDU.u32Size += 3;
    memcpy(&stAPDU.u8Data[stAPDU.u32Size], u8CADes, u32Len);
    stAPDU.u32Size += u32Len;
    
    return QueuePutAPDU(enCardId, &stAPDU);;
    
}

HI_U32 HI_CI_MMIMenuAnsw(HI_UNF_CI_PCCD_E enCardId, HI_U8 u32Nb)
{
    APDU_S stAPDU;

    if (!stStackInfo[enCardId].stSession[RES_SESSION_NUM_MMI].isOpen)
    {
        HI_ERR_CI("Card %d, MMI Session not opened\n", enCardId);
        return HI_FAILURE;
    }

    stAPDU.u32Size = 0;
    stAPDU.u16SessionNum = RES_SESSION_NUM_MMI;
    ASN_WRITE_U24(&stAPDU.u8Data[stAPDU.u32Size], A_MMI_ANSW);
    stAPDU.u32Size += 3;
    stAPDU.u32Size+=SetLengthField(&stAPDU.u8Data[stAPDU.u32Size], 1);
    stAPDU.u8Data[stAPDU.u32Size++] = u32Nb;
 
    return QueuePutAPDU(enCardId, &stAPDU);
}

HI_U32 HI_CI_MMIAnsw(HI_UNF_CI_PCCD_E enCardId, HI_CHAR *pu8Text, HI_U32 u32Size)
{
    APDU_S stAPDU;

    if (pu8Text == HI_NULL)
    {
        HI_ERR_CI("Invalid para\n");
        return HI_FAILURE;
    }
    if (!stStackInfo[enCardId].stSession[RES_SESSION_NUM_MMI].isOpen)
    {
        HI_ERR_CI("Card %d, MMI Session not opened\n", enCardId);
        return HI_FAILURE;
    }
    
    stAPDU.u32Size = 0;
    stAPDU.u16SessionNum = RES_SESSION_NUM_MMI;
    ASN_WRITE_U24(&stAPDU.u8Data[stAPDU.u32Size], A_MMI_ANSW);
    stAPDU.u32Size += 3;
    stAPDU.u32Size+=SetLengthField(&stAPDU.u8Data[stAPDU.u32Size], u32Size + 1);
    stAPDU.u8Data[stAPDU.u32Size++] = u32Size > 0 ? 0x01 : 0x00;
    memcpy((HI_CHAR*)&stAPDU.u8Data[stAPDU.u32Size], pu8Text, u32Size);
    stAPDU.u32Size += u32Size;
    
    return QueuePutAPDU(enCardId, &stAPDU);;
}

HI_U32 HI_CI_MMIEnterMenu(HI_UNF_CI_PCCD_E enCardId)
{
    APDU_S stAPDU;

    if (!stStackInfo[enCardId].stSession[RES_SESSION_NUM_AI].isOpen)
    {
        HI_ERR_CI("Card %d, AI Session not opened\n", enCardId);
        return HI_FAILURE;
    }
    
    ASN_WRITE_U24(&stAPDU.u8Data[0], A_AI_ENTER_MENU);
    stAPDU.u8Data[3] = 0x00;
    stAPDU.u32Size = 4;
    stAPDU.u16SessionNum = RES_SESSION_NUM_AI;

    return QueuePutAPDU(enCardId, &stAPDU);;
}

HI_U32 HI_CI_GetCaSystemID(HI_UNF_CI_PCCD_E enCardId, HI_U16 u16CaIds[], HI_U8 *pu8NumCaIds)
{
    HI_U8 u8Count;
        
    if (u16CaIds == HI_NULL)
    {
        HI_PRINT("Invalid para: u16CaIds\n");
        return HI_FAILURE;
    }

    if (!stStackInfo[enCardId].stSession[RES_SESSION_NUM_CA].isOpen)
    {
        HI_ERR_CI("Card %d, CA Session not opened\n", enCardId);
        return HI_FAILURE;
    }

    for (u8Count=0; u8Count<stStackInfo[enCardId].u8NumCaIds; u8Count++)
    {
        u16CaIds[u8Count] = stStackInfo[enCardId].u16CaIds[u8Count];
    }
    *pu8NumCaIds = stStackInfo[enCardId].u8NumCaIds;

    return HI_SUCCESS;
}

HI_U32 HI_CI_Init(HI_UNF_CI_TS_MODE_E enTSMode[], HI_UNF_CI_TSI_SERIAL_PORT_E enTsiSerialPort[])
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_CI_PORT_E enCIPort = HI_UNF_CI_PORT_0;
    HI_UNF_CI_PCCD_E enCardId = HI_UNF_CI_PCCD_A;
    HI_UNF_CI_ATTR_S stCIAttr;
    
    /* Init CI */
    s32Ret = HI_UNF_CI_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_PRINT("HI_UNF_CI_Init() FAIL!!! 0x%08x.\n", s32Ret);
        return HI_FAILURE;
    }

    HI_PRINT("HI_UNF_CI_Init success.\n");

    memset(&stCIAttr, 0, sizeof(stCIAttr));
    s32Ret = HI_UNF_CI_GetAttr(enCIPort, &stCIAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_PRINT("HI_UNF_CI_SetAttr() FAIL!!! 0x%08x.\n", s32Ret);
         return HI_FAILURE;
    }

    // TODO: here config the ts-mode, tsi-port, gpio-no, and so on
    for (enCardId=HI_UNF_CI_PCCD_A; enCardId<DEVICE_CI_SLOT_NUM; enCardId++)
    {
        stCIAttr.enTSMode[enCardId] = enTSMode[enCardId];
        if (stCIAttr.enDevType == HI_UNF_CI_DEV_CIMAXPLUS)
        {
            stCIAttr.unDevAttr.stCIMaXPlus.enTsiSerialPort[enCardId] = enTsiSerialPort[enCardId];
            stCIAttr.unDevAttr.stCIMaXPlus.u32ResetGpioNo = DEF_CIMAXPLUS_RESET_GPIO;
            stCIAttr.unDevAttr.stCIMaXPlus.u32IntGpioNo = DEF_CIMAXPLUS_INT_GPIO;
     //     stCIAttr.unDevAttr.stCIMaXPlus.enCmdExchangeChan = HI_UNF_CI_CMD_EXCHANGE_CHAN_SPI;
        }
        if (stCIAttr.enDevType == HI_UNF_CI_DEV_HICI)
        {
            stCIAttr.unDevAttr.stCIHICI.bIsPowerCtrlGpioUsed = HI_TRUE;
            stCIAttr.unDevAttr.stCIHICI.u32PowerCtrlGpioNo[enCardId] = DEF_HICI_POWER_CTRL_GPIO;
        }
    }
    s32Ret = HI_UNF_CI_SetAttr(enCIPort, &stCIAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_PRINT("HI_UNF_CI_SetAttr() FAIL!!! 0x%08x.\n", s32Ret);
         return HI_FAILURE;
    }
    /* Open CI Port */
    s32Ret = HI_UNF_CI_Open(enCIPort);
    if (HI_SUCCESS != s32Ret)
    {
        HI_PRINT("HI_UNF_CI_Open(%d) FAIL!!! 0x%08x.\n", enCIPort, s32Ret);
        return HI_FAILURE;
    }
    HI_PRINT("HI_UNF_CI_Open(%d) success.\n", enCIPort);

    for (enCardId=HI_UNF_CI_PCCD_A; enCardId<DEVICE_CI_SLOT_NUM; enCardId++)
    {
        /* Open card*/
        s32Ret = HI_UNF_CI_PCCD_Open(enCIPort, enCardId);
        if (HI_SUCCESS != s32Ret)
        {
            HI_PRINT("HI_UNF_CI_PCCD_Open(%d, %d) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
            return HI_FAILURE;
        }
        HI_PRINT("HI_UNF_CI_PCCD_Open(%d, %d) success.\n", enCIPort, enCardId);
        s32Ret = TSByPass(enCIPort, enCardId, HI_TRUE);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_CI("TSByPass(%d, %d) fail: 0x%08x.\n", enCIPort, enCardId, s32Ret);
        }
        HI_PRINT("HI_UNF_CI_PCCD_TSCtrl(%d, %d) set by-pass Success!!!.\n", enCIPort, enCardId);
    }  
    memset(&stStackInfo, 0, sizeof(stStackInfo));   
    g_bStopCIThread = HI_FALSE;
    pthread_mutex_init(&g_CIMutex,NULL);
    sem_init(&s_CISem, 0, 0);
    pthread_create(&g_CIThdMonitor, HI_NULL, (HI_VOID *)CITthreadMonitor, HI_NULL);
    pthread_create(&g_CIThdMain, HI_NULL, (HI_VOID *)CITthreadMain, HI_NULL);
    sleep(3);
    return HI_SUCCESS;
    
}

HI_S32 HI_CI_DeInit(void)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_CI_PORT_E enCIPort;
    HI_UNF_CI_PCCD_E enCardId;

    enCIPort = HI_UNF_CI_PORT_0;
    enCardId = HI_UNF_CI_PCCD_A;
     
    g_bStopCIThread = HI_TRUE;
    pthread_join(g_CIThdMonitor, HI_NULL);
    pthread_join(g_CIThdMain, HI_NULL);
    sem_destroy(&s_CISem);
    pthread_mutex_destroy(&g_CIMutex);
        
    for (enCardId=HI_UNF_CI_PCCD_A; enCardId<DEVICE_CI_SLOT_NUM; enCardId++)
    {
        /* Power OFF */
        s32Ret = HI_UNF_CI_PCCD_CtrlPower(enCIPort, enCardId, HI_UNF_CI_PCCD_CTRLPOWER_OFF);
        if (HI_SUCCESS != s32Ret)
        {
            HI_PRINT("HI_UNF_CI_PCCD_CtrlPower(%d, %d) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
            return HI_FAILURE;
        }

        if (HI_NULL != stStackInfo[enCardId].pBuffer)
        {
            HI_FREE_CI(stStackInfo[enCardId].pBuffer);
            stStackInfo[enCardId].pBuffer = HI_NULL;
        }
        QueueReset(enCardId);
        
        s32Ret = HI_UNF_CI_PCCD_Close(enCIPort, enCardId);
        if (HI_SUCCESS != s32Ret)
        {
            HI_PRINT("HI_UNF_CI_PCCD_Close(%d, %d) FAIL!!! 0x%08x.\n", enCIPort, enCardId, s32Ret);
            return HI_FAILURE;
        }
    }
    
    s32Ret = HI_UNF_CI_Close(enCIPort);
    if (HI_SUCCESS != s32Ret)
    {
        HI_PRINT("HI_UNF_CI_PCCD_Close(%d) FAIL!!! 0x%08x.\n", enCIPort, s32Ret);
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_CI_DeInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_PRINT("HI_UNF_CI_DeInit() FAIL!!! 0x%08x.\n", s32Ret);
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}
