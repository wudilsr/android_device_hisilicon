/**
* @file osTets.inc
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* ??:??????????? \n
*/

#ifndef _OSTEST_INC
#define _OSTEST_INC

//#include <stdlib.h>
//#include <string.h>
#include "sre_base.h"
#include "sre_list.ph"
#include "sre_config.h"
#include "sre_mem.h"
#include "sre_mem.ph"
#include "sre_fscmem.ph"
#include "sre_task.h"
#include "sre_sys.h"
#include "osTest.h"
#include "sre_err.h"
#include "sre_hwi.h"
#include "sre_swi.h"
#include "sre_sem.h"
#include "sre_msg.h"
#include "sre_typedef.h"
#include "app_data_common.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


BOOL  g_bRebootFlg     = TRUE;

/*****************************************************************************
Description : É¾³ý·ÖÇø
Input       : ucPtNo - ·ÖÇøºÅ
Output      :
Return      : None
*****************************************************************************/

VOID Ut_MemPtDelete(UINT8 ucPtNo)
{
    MCMEM_FSCMEM_PT_CTRL_S *pstPtCtrlFSC;
    MCMEM_MEM_PT_CTRL_S *pstPtCtrlPOOL;

    if ((0x0 != ucPtNo) && (0x1 != ucPtNo))
    {
        //printf("ucPtNo = %d\n",ucPtNo);
        m_astMemPtInfo[ucPtNo].bInstalled = 0;
        m_astMemPtInfo[ucPtNo].pPtAddr = NULL;
        m_astMemPtInfo[ucPtNo].uwPtSize = 0;
        if(m_astMemPtInfo[ucPtNo].enArith == MEM_ARITH_MCDYNFSC)
        {
            pstPtCtrlFSC = (MCMEM_FSCMEM_PT_CTRL_S *)g_astMemPtCheck[ucPtNo].pPtCtrl;
            pstPtCtrlFSC->uwState = OS_MCMEM_CTRL_STATE_INVALID;
            pstPtCtrlFSC->enArith = MEM_ARITH_MCDYNFSC;
        }
        else if(m_astMemPtInfo[ucPtNo].enArith == MEM_ARITH_MCPOOL)
        {
            pstPtCtrlPOOL = (MCMEM_MEM_PT_CTRL_S *)g_astMemPtCheck[ucPtNo].pPtCtrl;
            pstPtCtrlPOOL->uwState = OS_MCMEM_CTRL_STATE_INVALID;
            pstPtCtrlPOOL->enArith = MEM_ARITH_MCPOOL;
        }
        else
        {
            //g_astMemPtCheck[ucPtNo].pPtCtrl = NULL;    /*¶àºË¼ì²é*/
        }
    }
}

#if 0


#define MemInfoReStore_param_Err    0xf1
#define MemFile_open_Err            0xf2
#define MemFileReStore_SUCCESS      0X0
#define DEL_SWTMRGRP                YES

#define CDA_AUTO_DUMP           YES
#define MEM_DUMP_SUCCESS            0X0         //cda??
BOOL  g_bRebootFlg     = TRUE;


/*?v0?????*/
#if(OS_HARDWARE_PLATFORM == OS_DSP170)
OS_SEC_TEST7_TEXT VOID WriteVector(UINT8 *uwParam)
{
    __asm__ __volatile__("lvu32.i v0, %0, 0     \n\
                          lvh.i   v0, %0, 16    \n\
                         ": : "a" (uwParam):"v0");
}

#elif((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
OS_SEC_TEST7_TEXT VOID WriteVector(UINT8 *uwParam)
{
     __asm__ __volatile__("lv128.i v0, %0, 0     \n\
                          ": : "a" (uwParam):"v0");
}

#endif

/*?v0?????*/
#if(OS_HARDWARE_PLATFORM == OS_DSP170)
OS_SEC_TEST7_TEXT VOID ReadVector(UINT8 *uwParam)
{
     __asm__ __volatile__("svl.i v0, %0, 0     \n\
                           svh.i v0, %0, 16    \n\
                          ": : "a" (uwParam):"v0");
}

#elif((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
OS_SEC_TEST7_TEXT VOID ReadVector(UINT8 *uwParam)
{
     __asm__ __volatile__("sv128.i v0, %0, 0x000  \n\
                          " : : "a"(uwParam) : "v0" );
}

#endif

/*******************************************************************
*
*                      ??????????
*
*********************************************************************/
#if(YES == DEL_SWTMRGRP)
/*************************????***************************/
typedef UINT32 (*SWTMR_SCAN_FUNC)(VOID);
typedef enum
{
    TIMER_TYPE_HWTMR,       /**< ?????      */
    TIMER_TYPE_SWTMR,       /**< ?????      */
    TIMER_TYPE_INVALID
} OS_FS_TYPE_E;
typedef struct tagSwTmrCtrl
{
    struct tagSwTmrCtrl *pstPrev;                          /*????????*/
    struct tagSwTmrCtrl *pstNext;                          /*????????*/
    UINT8                ucState;                          /*?????*/
    UINT8                ucMode;                           /*?????*/
    UINT16               usTimerID;                        /*???ID*/
    UINT32               uwIdxRollNum;                     /*???SortLink??,???uwRollNum,???uwSortIndex*/
    UINT32               uwInterval;                       /*???????*/
    UINT32               uwArg1;                           /**< ???????1     */
    UINT32               uwArg2;                           /**< ???????2     */
    UINT32               uwArg3;                           /**< ???????3     */
    UINT32               uwArg4;                           /**< ???????4     */
    SRE_TMR_PROC_FUNC    pfnHandler;                       /*?????????*/
} SWTMR_CTRL_S;
typedef struct tagListObject
{
    struct tagListObject *pstPrev;
    struct tagListObject *pstNext;
} LIST_OBJECT_S;
typedef struct tagSwTmrSortLinkAttr
{
    LIST_OBJECT_S        *pstSortLink;                     /*?????????*/
    UINT16                usCursor;                        /*Tick????*/
    UINT16                usUnUsed;                        /*????*/
} SWTMR_SORTLINK_ATTRIBUTE_S;
typedef UINT32 (*TIMER_CREATE_F)(TIMER_CREATE_PARA_S *pstCreatePara,TIMER_HANDLE_T *pstTimerHdl);
typedef UINT32 (*TIMER_START_F)
(
    TIMER_HANDLE_T timerHdl
);
typedef UINT32 (*TIMER_STOP_F)
(
    TIMER_HANDLE_T timerHdl
);
typedef UINT32 (*TIMER_DELETE_F)
(
    TIMER_HANDLE_T timerHdl
);
typedef UINT32 (*TIMER_RESTART_F)
(
    TIMER_HANDLE_T timerHdl
);
typedef UINT32 (*TIMER_SET_INTERVAL_F)
(
    TIMER_HANDLE_T timerHdl,
    UINT32 uwInterVal
);
typedef struct tagFuncsLibTimer
{
    TIMER_CREATE_F    pfnCreateTimer;
    TIMER_START_F     pfnStartTimer;
    TIMER_STOP_F      pfnStopTimer;
    TIMER_DELETE_F    pfnDeleteTimer;
    TIMER_RESTART_F   pfnRestartTimer;
}TIMER_API_S;
/****************************??????****************************/
extern SWTMR_CTRL_S                  *g_pstSwtmrCBArray;
extern SWTMR_SORTLINK_ATTRIBUTE_S     g_stSwTmrSortLink;
extern TIMER_API_S                    m_astTimerAPI[TIMER_TYPE_SWTMR];
extern TICK_MOD_INFO_S                m_stTickModInfo;
extern UINT32                         m_uwMaxTimerNum;
EXTERN_FAR SWTMR_SCAN_FUNC            g_pfnSwtmrScanHook;
/*******************************************************************
*????:
*????:
*********************************************************************/
UINT32 Test_SwTimerGroupDelete(void)
{
    UINT32 uwRet;
    UINTPTR  uvIntSave;

    uvIntSave = __SRE_IntLock();
    m_uwMaxTimerNum = 0;

    uwRet = SRE_MemFree(OS_MID_SWTMR, (VOID*)g_stSwTmrSortLink.pstSortLink);
    if(uwRet != SRE_OK)
    {
       return uwRet;
    }
    uwRet = SRE_MemFree(OS_MID_SWTMR, (VOID*)g_pstSwtmrCBArray);
    if(uwRet != SRE_OK)
    {
       return uwRet;
    }

    m_astTimerAPI[TIMER_TYPE_SWTMR].pfnCreateTimer   = NULL;
    m_astTimerAPI[TIMER_TYPE_SWTMR].pfnStartTimer    = NULL;
    m_astTimerAPI[TIMER_TYPE_SWTMR].pfnStopTimer     = NULL;
    m_astTimerAPI[TIMER_TYPE_SWTMR].pfnDeleteTimer   = NULL;
    m_astTimerAPI[TIMER_TYPE_SWTMR].pfnRestartTimer  = NULL;
    g_pfnSwtmrScanHook = NULL;

    (VOID)__SRE_IntRestore(uvIntSave);
    return SRE_OK;
}
#endif

/*******************************************************--- MSG ????????? ---*********************************************************/


typedef struct tagListObject
{
    struct tagListObject *pstPrev;
    struct tagListObject *pstNext;
} LIST_OBJECT_S;
#endif

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
#define OS_SMSG_MAX_LEN                 8
#else
#define OS_SMSG_MAX_LEN                 0
#endif


#define MSG_PUBLIC_HEAD               \
    LIST_OBJECT_S stList;       /* ????????????,??????   */ \
    MSG_PID_T uwDstPid;         /* ??????pid                          */ \
    MSG_PID_T uwSrcPid;         /* ??????pid                      */     \
    UINT32 uwMsgID;             /* 4???????  */                         \
    UINT8  ucQID;               /* ?????QID                            */ \
    UINT8  ucMsgType;           /* ????:????,???,???       */

typedef struct tagMsgPubHead
{
    MSG_PUBLIC_HEAD
}MSG_PUB_HEAD_S;

typedef struct tagMsgHead
{
    MSG_PUBLIC_HEAD
    UINT8  bShared;             /* ????????                         */
    UINT8  bCachable;           /* ??????????Cache            */
    UINT16 usLength;            /* ??????????                     */
    UINT16 usMagicWord;         /* ???                                   */
    VOID   *pMemBlock ;         /* ???????????????       */
} MSG_HEAD_S;

typedef struct tagMsgNode
{
    MSG_PUBLIC_HEAD
    UINT8  ucSmsgLen;           /* ????? */
    UINT8  ucReleasable;        /* ????? */
    UINT32 auwData[1 + (OS_SMSG_MAX_LEN/sizeof(UINT32))];  /*????0?WORD????????,???WORD???????????*/
} MSG_NODE_S;


extern  MSG_NODE_S       *g_pstFreeLcMsgHead;      /* ?????????????   */
extern  MSG_NODE_S       *g_pstLcMsgArray;         /* ?????????????   */

/*******************************************************--- MSG ????????? ---*********************************************************/

#if 0

/*******************************************************************
*
*                               ????????
*
*********************************************************************/
/*??????????? */
typedef struct tagSliceCtrlHead
{
    UINT32 uwHead;                              /* ???                                     */
    struct tagSliceCtrlHead *pNextFree;         /* ???,????????                   */
    UINT8  ucPtNo;                              /* ???                                     */
    UINT8  ucType;                              /* ???                                     */
    UINT16 usOffset;                            /* ?????POOL??:??????????   */
    UINT32 *uwAlignPad;                         /* ?????????                         */
} OS_MEM_SLICE_CTRL_HEAD_S;

/*	???????	*/
typedef VOID* (*MEM_ALLOC_F)
(
	UINT32	 uwMid,
	UINT8	 ucPtNo,
	UINT32	 uwSize,
	OS_MEM_ALIGN_E	  ucAlignPow
);

/*	???????	*/
typedef UINT32 (*MEM_FREE_F)
(
	UINT32	uwMid,
	UINT8	 cPtNo,
	OS_MEM_SLICE_CTRL_HEAD_S	 *pstSHead,
	UINT32 *puwSize
);

/* ???????*/
typedef struct tagMemPtInfo
{
	OS_MEM_ARITH_E	   enArith; 				/* ?????????						  */
	VOID			  *pPtAddr; 				/* ?????? 							  */
	VOID			  *pPtCtrl; 				/* ??????,???????????????????,????FSC,?????????*/
	UINT32			   uwPtSize;				/* ???? 								  */
	UINT32			   uwSliceMaxSize;			/* ?????								  */
	UINT32			   uwTotalSize; 			/* ???????							  */
	UINT32			   uwFreeSize;				/* ???????????					  */
	UINT8			   bInstalled;				/* ???????							  */
	UINT8			   bCachable;				/* ????cache							  */
	UINT8			   bShared; 				/* ?????????						  */
	UINT8			   Reserved;
	UINT32			   uwBitMap;				/* ??FSC?????Bitmap					  */
	MEM_ALLOC_F 	   pfnAlloc;				/* ?????????						  */
	MEM_FREE_F		   pfnFree; 				/* ?????????						  */
}MEM_PT_INFO_S;

/* ?????????,??????????????? */
typedef struct tagMemPtCheck
{
    VOID                    *pPtCtrl;          /* ????????? */
} MEM_PT_CHECK_S;

/*FSC????????*/
typedef struct tagFscMemCtrl
{
    struct tagFscMemCtrl *pstNext;
    UINT16 usSize;
    UINT16 usPrev;
    UINT8  ucPtNo;
    UINT8  ucBlkId;
    UINT16 usUserSize;
    struct tagFscMemCtrl *pstPrev;
}OS_FSC_MEM_CTRL_S;

/* ??FSC????? */
typedef struct tagFSCMemPtCtrl
{
    UINT32                      uwPeakSize;
    OS_FSC_MEM_CTRL_S          *pstFscFreeHead;
}FSCMEM_MEM_PT_CTRL_S;


EXTERN_FAR MEM_PT_INFO_S  *m_astMemPtInfo;
#endif

extern VOID 	*g_pFscList;
extern UINT16 (*m_ausSliceTypeToSize)[OS_SLICE_MAXTYPE];
extern UINT8  **m_aucSliceSizeToType;
extern UINT8  m_ucMaxPtNum;


VOID TEST_MemPtDelete(UINT8 ucPtNo)
{
	UINT8    ucLoop;
	FSCMEM_MEM_PT_CTRL_S *pstFSCMemPtCtrl;
	UINT8    ucIndex = 0xFF;

	m_astMemPtInfo[ucPtNo].bInstalled = 0;
	m_astMemPtInfo[ucPtNo].pPtAddr = NULL;
	m_astMemPtInfo[ucPtNo].uwPtSize = 0;
	g_astMemPtCheck[ucPtNo].pPtCtrl = NULL;

	if (MEM_ARITH_FSC == m_astMemPtInfo[ucPtNo].enArith)
	{
		if (NULL != g_pFscList)
		{
			pstFSCMemPtCtrl = (FSCMEM_MEM_PT_CTRL_S *)m_astMemPtInfo[ucPtNo].pPtCtrl;
			(VOID)SRE_MemFree(0, pstFSCMemPtCtrl->pstFscFreeHead);

			g_pFscList = NULL;
		}

		(VOID)SRE_MemFree(0, m_astMemPtInfo[ucPtNo].pPtCtrl);
	}

	if ((MEM_ARITH_POOL == m_astMemPtInfo[ucPtNo].enArith)||(MEM_ARITH_MCPOOL == m_astMemPtInfo[ucPtNo].enArith))
	{
		for (ucLoop = OS_MEM_DEFAULT_PTNUM; ucLoop < m_ucMaxPtNum; ucLoop++)
	    {
	        if (ucPtNo == ucLoop)
	        {
	            continue;
	        }

	        if (0 == memcmp(m_ausSliceTypeToSize[ucLoop], m_ausSliceTypeToSize[ucPtNo], (sizeof(UINT16) * OS_SLICE_MAXTYPE)))
	        {
	            ucIndex = ucLoop;
	            break;
	        }
	    }
		if (0xFF == ucIndex)
		{
			(VOID)SRE_MemFree(0, (VOID *)m_aucSliceSizeToType[ucPtNo]);
		}

		memset(&(m_aucSliceSizeToType[ucPtNo]), 0, sizeof(UINT8 **));
        memset(m_ausSliceTypeToSize[ucPtNo], 0, sizeof(UINT16) * OS_SLICE_MAXTYPE);
	}

}


#if 0
#if(YES == CDA_AUTO_DUMP)
static CHAR  acPool_Temp[8]={0,0,0,0,0,0,0,0};
static CHAR  *File_name = "*****";
static CHAR  *acDumpPath = "D:\\CDA_DUMP\\";
#endif

typedef struct tagITestCDAinfo
{
   VOID * uwMemStartAddr;
   UINT32 uwMemInfolen;
} IT_CDAINfO_S;

#if 0
static IT_CDAINfO_S g_astITCDAinfo[5] =
{
    {0x01000000, 0x80000},      /*8108 dsp L1???????*/
    {0x01000000, 0x20000},      /*8108 cpu L1???????*/
    {0x08000000, 0x80000},      /*82   Cpu/Dsp LL2???????*/
    {0x08000000, 0x40000},      /*82   Hac LL2???????*/
    {0x01000000, 0x30000}       /*6155 L1???????*/
};
#endif

#define Test_Auto_Dump             NO

EXTERN_FAR UINT8  m_ucMaxPtNum;
extern UINT8 m_aucTraceRegion[OS_SYS_CORE_RUN_NUM][OS_TRACE_AREA_SIZE];
#if(OS_HARDWARE_PLATFORM == OS_SC3850)
extern UINT64 osGetCycle(VOID);
#endif

static CHAR acTemp_pool[8]={0};
static CHAR acFilePath[32] = {"D:\\CDA\\"};

OS_SEC_BSS CDA_PT_INFO_S astCDAPtInfo[40];

extern  volatile UINT32 g_vuwMcInitGuard;
extern  volatile UINT32 g_vuwSyncInitPhase;
OS_SEC_DATA_SHARED  UINT32    g_TestvuwSyncInitPhase = 0;

//extern volatile OS_SYNC_BARRIER_S g_stSharedCoresBarrier;   /* ?????? */
#define IT_HWSEM_ID   7
#if 0
OS_SEC_TEXT_MINOR VOID IT_syncBarrierWait(volatile OS_SYNC_BARRIER_S *pstBarrier)
{
    UINT32  uwLocalChnID;
    UINTPTR uvIntSave;
    UINT16  usLocalGate;

    if ((NULL == pstBarrier) || (0 == pstBarrier->vuwInitValue))
    {
        return;
    }

    usLocalGate = pstBarrier->vusGateValue;

    osHwSemPend(IT_HWSEM_ID);

    if (OS_SYNC_BARRIER_MODE_CHNID == pstBarrier->vuwMode)
    {
        uwLocalChnID = (UINT32)1 << SRE_GetCoreID();

        if (0 == (uwLocalChnID & pstBarrier->vuwRealValue))
        {
            osHwSemPost(IT_HWSEM_ID);

            return;
        }

        pstBarrier->vuwRealValue &= ~uwLocalChnID;
    }
    else
    {
        pstBarrier->vuwRealValue--;
    }

    if (0 == pstBarrier->vuwRealValue)
    {
        pstBarrier->vusGateValue = ~usLocalGate;
        pstBarrier->vuwRealValue = pstBarrier->vuwInitValue;
    }

    osHwSemPost(IT_HWSEM_ID);

    while (pstBarrier->vusGateValue == usLocalGate)
    {
        /* ????????????? */
        asm(" nop");asm(" nop");asm(" nop");asm(" nop");
        asm(" nop");asm(" nop");asm(" nop");asm(" nop");
        asm(" nop");asm(" nop");asm(" nop");asm(" nop");
        asm(" nop");asm(" nop");asm(" nop");asm(" nop");
    }

}


OS_SEC_TEXT_MINOR VOID IT_WaitForAllCores(VOID)
{
    IT_syncBarrierWait(&g_stSharedCoresBarrier);
}
#endif

#if (OS_HARDWARE_PLATFORM == OS_SC3400)
typedef union AGR_SP26XX_DSS_SOFTINT_UT
{
    struct
    {
        volatile unsigned int
            softint : 8,
            fill0 : 24;
    } fields;
   volatile unsigned int reg;
} agr_sp26xx_dss_softint_ut;
VOID TEST_HwiTrigger(UINT32 uwSoftNum)
{
    UINT8 ucSoftNum = (UINT8) uwSoftNum;

    ucSoftNum = ucSoftNum - 91;
    ((agr_sp26xx_dss_softint_ut *)0xC0600118)->reg |= (0x00000001<<ucSoftNum);
    asm("syncio");
}
VOID uniNmiTrag(VOID)
{
    UINT32 uwNmiFlag;
    uwNmiFlag = 0x22221110 | SRE_GetCoreID();
    *(UINT32 *)0xC02ffff0 = uwNmiFlag;
}
VOID uniNmiTragCoreID(UINT32 uwCoreID)
{
    UINT32 uwNmiFlag;
    uwNmiFlag = 0x22221110 | uwCoreID;
    *(UINT32 *)0xC02ffff0 = uwNmiFlag;
}
VOID uniSoftReboot(VOID)
{
    UINT32 uwResetFlag;
    __SRE_IntLock();

    uwResetFlag = 0x11112220 | SRE_GetCoreID();

    *(UINT32 *)0xC02ffff0 = uwResetFlag;
    while(1);
}
#elif (OS_HARDWARE_PLATFORM == OS_SC3850)
#define OS_VIRTUAL_INT_BASE         185         /*?????????*/
VOID TEST_HwiTrigger(UINT32 uwIntNum)
{
    UINT32 uwVIRQNum,i=5000;
    volatile UINT32 *puwVIGR = (UINT32 *)0xFFF27000; //?????????????

    uwVIRQNum = uwIntNum - OS_VIRTUAL_INT_BASE;
    WRITE_UINT32(*puwVIGR, ((uwVIRQNum & 0x8) << 5) | (uwVIRQNum & 0x7));
    asm(" syncio");
    while(i--);
}

#elif (OS_HARDWARE_PLATFORM == OS_C64XPLUS)
static volatile UINT32 m_testMsgDelay = 0;
static VOID TEST_HwiDelay()
{
    UINT32 uwIndex;

    for (uwIndex = 0; uwIndex < 2; uwIndex++)
    {
        m_testMsgDelay += uwIndex;
    }
}

/* ??????? */
VOID TEST_HwiTrigger(UINT32 uwEvtNum)
{
    UINT32 uwRegIdx;
    UINT32 uwFlgBit;
    volatile UINT32 *pvuwEvtSet = (volatile UINT32 *)0x01800020;

    uwRegIdx = uwEvtNum >> 5;
    uwFlgBit = (UINT32)1 << (uwEvtNum & 0x1f);

    WRITE_UINT32(pvuwEvtSet[uwRegIdx], uwFlgBit);

    /* ?????? */
    TEST_HwiDelay();
}
#elif (OS_HARDWARE_PLATFORM == OS_XTENSA2)
static volatile UINT32 m_testMsgDelay = 0;
UINT32 int_tempvalue = 0;
typedef volatile INT32  VINT32;
#define INT_TRIG_ADDR  (0x68000000)//??LEVEL2???
#define INT_INIT_ADDR  (0x68000004)//??LEVEL2???
#define REG32(addr) (*(VINT32 *)(addr))//LEVEL2??????

#define WRITE_REG(uwValue) \
        REG32(INT_TRIG_ADDR) = int_tempvalue;\
       __asm__ __volatile__("nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;                             nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;                             nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;                             nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;                             nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;                             nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;");

VOID uniIntTrigInit()
{//FPGA???
    REG32(INT_INIT_ADDR) = 0x5a5a5a5a;
    REG32(INT_TRIG_ADDR) = 0;
}

VOID test_L2_EMPTY(VOID)
{//???????
    REG32(INT_TRIG_ADDR) = 0;
    int_tempvalue = 0;
}

VOID test_L2_TRIG(UINT32 num)
{//??level2:3~16??
    int_tempvalue |= 1<<(num-2);
    WRITE_REG(int_tempvalue);
}

VOID test_L2_UNTRIG(UINT32 num)
{//?LEVEL2??
    int_tempvalue &= ~(1<<(num-2));
    WRITE_REG(int_tempvalue);
}

VOID test_L3_TRIG(UINT32 num)
{//??level3:17~24,????????19~24
    int_tempvalue |= 1<<(num-4);
    WRITE_REG(int_tempvalue);
}

VOID test_L45_TRIG(UINT32 num)
{//??level4:25~26,level5:27~30,??????26~30
    int_tempvalue |= 1<<(num - 5);
    WRITE_REG(int_tempvalue);
}

VOID test_L45_UNTRIG(UINT32 num)
{//??LEVEL4?LEVEL5??
    int_tempvalue &= ~(1<<(num-5));
   WRITE_REG(int_tempvalue);
}

VOID test_L3_UNTRIG(UINT32 num)
{//??LEVEL3??
    int_tempvalue &= ~(1<<(num-4));
    WRITE_REG(int_tempvalue);
}

VOID test_L1_TRIG(VOID)
{//??level1:0~2,???????2
    int_tempvalue |= 1;
    WRITE_REG(int_tempvalue);
}

VOID test_L1_UNTRIG(VOID)
{//??LEVLE1??
    int_tempvalue &= ~1;
    WRITE_REG(int_tempvalue);
}
void TEST_HwiTrigger(UINT32 uwEvtNum)
{
  #if(IT_SIMULATE == YES)
      UINT8 ucIntNum = (UINT8)uwEvtNum;
      __asm__ __volatile__( "wsr   %0, INTSET" : : "a" (0x1 << ucIntNum) );
  #else
    if(2 == uwEvtNum)
    {
        test_L1_TRIG(uwEvtNum);
    }
    else if((2 < uwEvtNum)&&(17 > uwEvtNum))
    {
        test_L2_TRIG(uwEvtNum);
    }
    else if((18 < uwEvtNum)&&(25 > uwEvtNum))
    {
        test_L3_TRIG(uwEvtNum);
    }
    else if((25 < uwEvtNum)&&(31 > uwEvtNum))
    {
        test_L45_TRIG(uwEvtNum);
    }
    else
    {
        UINT8 ucIntNum = (UINT8)uwEvtNum;
        __asm__ __volatile__( "wsr   %0, INTSET" : : "a" (0x1 << ucIntNum) );
    }
  #endif
}

void TEST_HwiCleanBit(UINT32 uwEvtNum)
{
  #if(IT_SIMULATE == YES)
      SRE_HwiClearPendingBit(uwEvtNum);
  #else
    if(2 == uwEvtNum)
    {
        test_L1_UNTRIG(uwEvtNum);
    }
    else if((2 < uwEvtNum)&&(17 > uwEvtNum))
    {
        test_L2_UNTRIG(uwEvtNum);
    }
    else if((18 < uwEvtNum)&&(25 > uwEvtNum))
    {
        test_L3_UNTRIG(uwEvtNum);
    }
    else if((25 < uwEvtNum)&&(31 > uwEvtNum))
    {
        test_L45_UNTRIG(uwEvtNum);
    }
    else
    {
        SRE_HwiClearPendingBit(uwEvtNum);
    }
  #endif
}

void TEST_HwiCleanAllBit(void)
{
  #if(!IT_SIMULATE)
      test_L2_EMPTY();
  #endif
      SRE_ClearAllPending();
}

#elif (OS_HARDWARE_PLATFORM == OS_RISC170 || OS_HARDWARE_PLATFORM == OS_DSP170 \
    || (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC))
VOID TEST_HwiTrigger(UINT32 uwIntNum)
{
    __asm__ __volatile__( "wsr   %0, intset; rsync" : : "a" (0x1 << uwIntNum) );
}

#else
VOID TEST_HwiTrigger(UINT32 uwIntNum)
{
}
#endif
#if (OS_HARDWARE_PLATFORM == OS_C64XPLUS)
typedef struct tagMapHwi_IT
{
    volatile UINT32 vauwEvtFlag[4];             /* Event Flag Register */
    volatile UINT32 vauwReserved0[4];
    volatile UINT32 vauwEvtSet[4];              /* Event Set Register */
    volatile UINT32 vauwReserved1[4];
    volatile UINT32 vauwEvtClr[4];              /* Event Clear Register */
    volatile UINT32 vauwReserved2[12];
    volatile UINT32 vauwEvtMask[4];             /* Event Mask Register */
    volatile UINT32 vauwReserved3[4];
    volatile UINT32 vauwMEvtFlag[4];            /* Masked Event Flag Status Register */
    volatile UINT32 vauwReserved4[4];
    volatile UINT32 vauwExpMask[4];             /* Exception Mask Register */
    volatile UINT32 vauwReserved5[4];
    volatile UINT32 vauwMExpFlag[4];            /* Masked Exception Flag Register */
    volatile UINT32 vauwReserved6[4];
    volatile UINT32 vauwIntMux[4];              /* Interrupt Multiplexor Register */
    volatile UINT32 vauwReserved7[12];
    volatile UINT32 vauwAegMux[2];              /* Advanced Event Generator Mux Register */
    volatile UINT32 vauwReserved8[14];
    volatile UINT32 vuwIntXStat;                /* Interrupt Exception Status Register */
    volatile UINT32 vuwIntXClr;                 /* Interrupt Exception Clear Register */
    volatile UINT32 vuwIntDMask;                /* Dropped Interrupt Mask Register */
    volatile UINT32 vauwReserved9[13];
    volatile UINT32 vuwEvtAsrt;                 /* Dropped Interrupt Mask Register */
    volatile UINT8  vaucReserved[0xe3c];
} IT_MAP_HWI_S;
UINT32 m_uwITestHwiDelay;
IT_MAP_HWI_S *m_pstHwiMap = ((IT_MAP_HWI_S *)0x01800000);

void uniSetISR(UINT32 uwIntNum)
{
    ISR = 1<<uwIntNum;
    return;
}
VOID IT_HwiSetDelay()
{
    UINT32 uwIndex;

    for (uwIndex = 0; uwIndex < 100; uwIndex++)
    {
        m_uwITestHwiDelay += uwIndex;
    }
}
VOID IT_HwiSetIntFlg(UINT32 uwVecNum)             /*TI?????????hwi????*/
{
    uniSetISR(uwVecNum);

    IT_HwiSetDelay();
}

VOID IT_HwiSetEvtFlg(UINT32 uwEvtNum)           /*TI?????????hwi????*/
{
    UINT32 uwRegIdx;
    UINT32 uwFlgBit;
    IT_MAP_HWI_S *pstHwiMap = ((IT_MAP_HWI_S *)0x01800000);

    uwRegIdx = uwEvtNum >> 5;
    uwFlgBit = (UINT32)1 << (uwEvtNum & 0x1f);

    WRITE_UINT32(pstHwiMap->vauwEvtSet[uwRegIdx], uwFlgBit);

    IT_HwiSetDelay();
}
#endif

/*
    dump mem data to file
    yKF23243  2010-6-4
*/

UINT32 Itest_MemInfoReStore(const char * pacMemFilePath, VOID * uwMemStartAddr, UINT32 uwMemInfolen)
{
    FILE * pstFile;

    if ((NULL == pacMemFilePath)||(0 == uwMemInfolen)||(NULL == uwMemStartAddr))
    {
         //uart_printf("Itest_MemInfoReStore param Err!\n");
         return MemInfoReStore_param_Err;
    }

    pstFile = fopen(pacMemFilePath, "wb");
    if (NULL == pstFile)
    {
        //uart_printf("MemFile open Err!\n");
        return MemFile_open_Err;
    }

    fwrite(uwMemStartAddr, sizeof(char), uwMemInfolen, pstFile);

    fclose(pstFile);

    return MemFileReStore_SUCCESS;
}

/**
    ???????      yKF23243 2010-4-9
*/
UINT32 Itest_Auto_Reclaim(CHAR Fun0,CHAR Fun1,CHAR PATH)
{

#if(YES == Test_Auto_Dump)

    UINT32 loop;
    UINT32 uwsave;
    UINT32 uwRet;
    char * pstr;
    UINT32 uwCDAindex;


#if (OS_HARDWARE_PLATFORM == OS_DSP170)
    uwCDAindex = 0;
#elif (OS_HARDWARE_PLATFORM == OS_RISC170)
    uwCDAindex = 1;
#elif ((OS_HARDWARE_PLATFORM == OS_RISC220)||(OS_HARDWARE_PLATFORM == OS_DSP220))
    uwCDAindex = 2;
#elif (OS_HARDWARE_PLATFORM == OS_HACCC)
    uwCDAindex = 3;
#else
    uwCDAindex = 4;
#endif

    uwsave = __SRE_IntLock();

    SRE_CdaInfoGet(astCDAPtInfo);

    if((astCDAPtInfo[0].uwAddr)&&(astCDAPtInfo[0].uwSize))
    {

        acFilePath[6]  = Fun0;
        acFilePath[7]  = Fun1;
        acFilePath[13] = SRE_GetCoreID() - SRE_GetMasterCore()+'0';
        acFilePath[14] = PATH;
        acFilePath[16] = 's';

        strcpy(&acFilePath[16],"stackpool.txt");
        acFilePath[29] = '\0';
        uwRet = Itest_MemInfoReStore(acFilePath, (VOID*)astCDAPtInfo[0].uwAddr, astCDAPtInfo[0].uwSize);
        ICUNIT_GOTO_EQUAL(uwRet, MemFileReStore_SUCCESS,uwRet,EXIT);
    }

    if(1)
    {
        acFilePath[6]  = Fun0;
        acFilePath[7]  = Fun1;
        acFilePath[13] = SRE_GetCoreID() - SRE_GetMasterCore()+'0';
        acFilePath[14] = PATH;
        acFilePath[16] = 'P';

        strcpy(&acFilePath[16],"PriMem.txt");
      acFilePath[26] = '\0';
        uwRet = Itest_MemInfoReStore(acFilePath, (VOID*)g_astITCDAinfo[uwCDAindex].uwMemStartAddr, g_astITCDAinfo[uwCDAindex].uwMemInfolen);
        ICUNIT_GOTO_EQUAL(uwRet, MemFileReStore_SUCCESS,uwRet, EXIT);
    }


    if((OS_TRACE_INCLUDE == YES)&&(OS_TRACE_AREA_ADDR != NULL))
    {
        acFilePath[6]  = Fun0;
        acFilePath[7]  = Fun1;
        acFilePath[13] = SRE_GetCoreID() - SRE_GetMasterCore()+'0';
        acFilePath[14] = PATH;
        acFilePath[16] = 'T';

        strcpy(&acFilePath[16],"Trace.txt");
      acFilePath[25] = '\0';
        uwRet = Itest_MemInfoReStore(acFilePath, (VOID*)OS_TRACE_AREA_ADDR, OS_TRACE_AREA_SIZE);
        ICUNIT_GOTO_EQUAL(uwRet, MemFileReStore_SUCCESS,uwRet, EXIT);

    }

    strcpy(acFilePath,"d:\\FUN00\\cda00A\\pool");
    for(loop = 1;loop <=m_ucMaxPtNum;loop++)
    {
       if((astCDAPtInfo[loop].uwAddr)&&(astCDAPtInfo[loop].uwSize))
       {
           acFilePath[6]  = Fun0;
           acFilePath[7]  = Fun1;
           acFilePath[13] = SRE_GetCoreID() - SRE_GetMasterCore()+'0';
           acFilePath[14] = PATH;

           sprintf( acTemp_pool, "%d.txt", loop - 1);
           strcat(acFilePath,acTemp_pool);

           uwRet = Itest_MemInfoReStore(acFilePath, (VOID*)astCDAPtInfo[loop].uwAddr, astCDAPtInfo[loop].uwSize);
           ICUNIT_GOTO_EQUAL(uwRet, MemFileReStore_SUCCESS,uwRet, EXIT);
           acFilePath[20] = '\0';
       }
    }
EXIT:
    __SRE_IntRestore(uwsave);

    return MemFileReStore_SUCCESS;
#endif
    return 0;
}
#if 0
UINT32 Itest_Auto_Dump(char *case_name,char *watch_point)
{
    UINT32 index = 0;
    UINT32 loop;
    UINT32 uwsave;
    UINT32 uwRet;
    char   pstr[64];
    char   file_path[128];
    UINT32 uwCDAindex;
    char   *pl_mem = "PriMem.txt";

    if(NULL == case_name)
    {
        return 1;//not SRE_OK
    }

    //???????‘\0’
    for(loop=0;loop<64;loop++)
    {
        pstr[loop] = '\0';
    }

    if (OS_HARDWARE_PLATFORM == OS_DSP170)
    {
    uwCDAindex = 0;
    if(OS_SD6108 == OS_CPU_TYPE)
    {
        File_name="08_DSP@";
    }
    else
    {
        File_name="81_DSP@";
    }
    }

    else if (OS_HARDWARE_PLATFORM == OS_RISC170)
    {
        uwCDAindex = 1;
        if(OS_SD6108 == OS_CPU_TYPE)
    {
        File_name="08_CPU@";
    }
    else
    {
        File_name="81_CPU@";
    }
    }

    else if (OS_HARDWARE_PLATFORM == OS_RISC220)
    {
    uwCDAindex = 2;
        File_name="82_CPU@";
    }

    else if (OS_HARDWARE_PLATFORM == OS_DSP220)
    {
        uwCDAindex = 2;
        File_name="82_DSP@";
    }

    else if (OS_HARDWARE_PLATFORM == OS_HACCC)
    {
        uwCDAindex = 3;
        File_name="82_HACCC@";
    }

    else
    {
        uwCDAindex = 4;
    }

    uwsave = __SRE_IntLock();
    SRE_CdaInfoGet(astCDAPtInfo);
    strcpy(pstr,File_name);
    index = strlen(pstr);
    if(SRE_GetCoreID()<10)
    {
       *(pstr+index) = '$';
       *(pstr+index+1) = SRE_GetCoreID()+'0';
    }
    else if(SRE_GetCoreID()<99)
    {
        *(pstr+index)   = '$';
        *(pstr+index+1) = SRE_GetCoreID()/10+'0';
        *(pstr+index+2) = SRE_GetCoreID()%10+'0';
    }
    else//????100,??
    {
        uart_printf("Function: Itest_Auto_Dump->Core ID is to large!!\n");
        return 1;
    }
    index = strlen(pstr);
    *(pstr+index) = '@';
    strcat(pstr,case_name);
    index = strlen(pstr);
    *(pstr+index) = '@';
    strcat(pstr,watch_point);
    index = strlen(pstr);
    *(pstr+index) = '@';
    //CDA???????????
    for(loop = 1;loop <=m_ucMaxPtNum;loop++)
    {
       if((astCDAPtInfo[loop].uwAddr)&&(astCDAPtInfo[loop].uwSize))
       {
           if(loop<=10)
           {

               sprintf(acPool_Temp, "Pool%d.txt", loop - 1);

               //??????:acFilePath+{??@??@?????@}+{???.txt}
               strcpy(file_path,acDumpPath); //??:acFilePath
               strcat(file_path,pstr);       //??:{??@??@?????@}
               strcat(file_path,acPool_Temp);//??:{???.txt}

               uwRet = Itest_MemInfoReStore(file_path, (VOID*)astCDAPtInfo[loop].uwAddr, astCDAPtInfo[loop].uwSize);
               uart_printf("astCDAPtInfo[loop].uwAddr is 0x%x\n",astCDAPtInfo[loop].uwAddr);
               ICUNIT_GOTO_EQUAL(uwRet, MemFileReStore_SUCCESS,uwRet, EXIT);
               //???????
               for(index = 0;index<96;index++)
               {
                   file_path[index] = 0;
               }
           }
           else
           {
               uart_printf("Function: Itest_Auto_Dump->m_ucMaxPtNum is to large!!\n");
               return 1;
           }
       }
    }
      //??????????
      //??????:{F:\\CDA_Result\\}+{??@??@?????@}+{???.txt}
      strcpy(file_path,acDumpPath);           //??:{X:\\CDA_Result\\}
      strcat(file_path,pstr);                 //??:{??@??@?????@}
      strcat(file_path,pl_mem);               //??:{"PriMem.txt".txt}

      uwRet = Itest_MemInfoReStore(file_path, (VOID*)g_astITCDAinfo[uwCDAindex].uwMemStartAddr, g_astITCDAinfo[uwCDAindex].uwMemInfolen);
      ICUNIT_GOTO_EQUAL(uwRet, MemFileReStore_SUCCESS,uwRet, EXIT);

      //??????????
      //??????:{F:\\CDA_Result\\}+{??@??@?????@}+{???.txt}
      //strcpy(file_path,acDumpPath);           //??:{X:\\CDA_Result\\}
      //strcat(file_path,pstr);                 //??:{??@??@?????@}
     // strcat(file_path,"Trace.txt");               //??:{"Trace.txt"}
      //if((OS_TRACE_INCLUDE == YES)&&(OS_TRACE_AREA_ADDR != NULL))
      //{
      //     uwRet = Itest_MemInfoReStore(file_path, (VOID*)OS_TRACE_AREA_ADDR, OS_TRACE_AREA_SIZE);
      //     ICUNIT_GOTO_EQUAL(uwRet, MemFileReStore_SUCCESS,uwRet, EXIT);
      //}

EXIT:
    __SRE_IntRestore(uwsave);
    return MemFileReStore_SUCCESS;
}
#endif

/*************************************************************************
*????:UINT32 Itest_Auto_Rule(char *case_name,char *watch_point,char *rule)
*????:CDA???,??????
*????:????(case_name), ???(watch_point),????(*rule)
*????:?
*????:add by 00221499
*************************************************************************/
UINT32 Itest_Auto_Rule(char *case_name,char *watch_point,char *rule)
{
    UINT32  uwRet;
    UINT32  index;
    char    file_name[96];
    FILE    *fp = NULL;
    for(index=0;index<96;index++)
    {
          file_name[index]=0;
    }

    strcat(file_name,acDumpPath);

    if (OS_HARDWARE_PLATFORM == OS_DSP170)
        if(OS_SD6108 == OS_CPU_TYPE)
    {
        strcat(file_name,"08_DSP@");
    }
    else
    {
        strcat(file_name,"81_DSP@");
    }

    else if (OS_HARDWARE_PLATFORM == OS_RISC170)
        if(OS_SD6108 == OS_CPU_TYPE)
    {
        strcat(file_name,"08_CPU@");
    }
    else
    {
        strcat(file_name,"81_CPU@");
    }

    else if (OS_HARDWARE_PLATFORM == OS_RISC220)
        strcat(file_name,"82_CPU@");
    else if (OS_HARDWARE_PLATFORM == OS_DSP220)
        strcat(file_name,"82_DSP@");
    else
        strcat(file_name,"82_HACCC@");

    index = strlen(file_name);
    //???
    if(SRE_GetCoreID()<10)
    {
       *(file_name+index) = '$';
       *(file_name+index+1) = SRE_GetCoreID()+'0';
       *(file_name+index+2) = '@';
    }
    else if(SRE_GetCoreID()<99)
    {
        *(file_name+index)   = '$';
        *(file_name+index+1) = SRE_GetCoreID()/10+'0';
        *(file_name+index+2) = SRE_GetCoreID()%10+'0';
        *(file_name+index+3) = '@';
    }
    else//????100,??
    {
        //uart_printf("Function: Itest_Auto_Dump->Core ID is to large!!\n");
        return 1;
    }
    //?????
    strcat(file_name,case_name);
    index = strlen(file_name);
    *(file_name+index) = '@';
    //????
    strcat(file_name,watch_point);
    index = strlen(file_name);
    *(file_name+index) = '@';
    //?rule.txt
    strcat(file_name,"rule.txt");
    index = strlen(file_name);

    fp = fopen(file_name, "a+");
    if(NULL == fp)
    {
        //uart_printf("Function Itest_Auto_Rule make file error!!\n");
        return 1;
    }
    fprintf(fp, "%s\n", rule);
    fclose(fp);
    return 0;
}


/*********************************************************************************************************/

/*???????*/
#if(YES == OS_INCLUDE_TSKMON)
VOID It_TaskStackMonitor(TSKMON_INFO_S* pstInfo)
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INFO_S stTaskInfo;

    uwTaskID = pstInfo->uwTaskPID;

    uwRet = SRE_TaskInfoGet(uwTaskID, &stTaskInfo);
    if(SRE_OK != uwRet)
    {
        uart_printf("\n*********************************TaskStack is Covered!!************************************\n");
        uart_printf("\n TaskID: 0x%x TaskName: %s 's stack is broken !\n", pstInfo->uwTaskPID, stTaskInfo.acName);
        uart_printf("\n*********************************TaskStack is Covered!!************************************\n");

    }
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    return ;
}
#endif


UINT32 TS_SRE_MsgRecv(UINT32 uwTimeout, UINT32 *puwMsgID, UINT32 *puwSenderPID)
{
    UINT32 uwRet;
    MSG_HANDLE_T uwMsgHdl;
    UINT32 uwMsgID;

    uwRet = SRE_MsgQRecv(&uwMsgHdl, &uwMsgID, puwSenderPID, 0, uwTimeout);
    if(0 != uwRet)
    {
        return TS_MSG_RECEIVE_ERR;
    }

    if(puwMsgID != NULL)
    {
        *puwMsgID = uwMsgID;
    }
    return (UINT32)uwMsgHdl;
}
#if 0
#define OS_BOX_REGION_NAME_LEN       32                 /*?????????? */
#define OS_BOX_INITNUM               -1                 /*?????ID???   */
#define OS_BOX_INIT_REGION(pstRegion) \
{\
    pstRegion->pacRegionName[0]   = '\0';          \
    pstRegion->pStartAddr         = NULL;          \
    pstRegion->uwRegionSize       = 0;             \
    pstRegion->uwBoxRegionId      = (UINT32)OS_BOX_INITNUM;   \
    pstRegion->uwCurrentSeg       = 0;             \
    pstRegion->uwSegmentLen       = 0;             \
    pstRegion->uwSegmentNum       = 0;             \
    pstRegion->pstRegionSegment   = NULL;          \
}

/*????????????*/
typedef struct tagBoxRecordStru
{
    UINT32      uwMagicNo;           /*magic NO                      */
    UINT32      uwRecordSize;        /*reocrd head + reocrd data     */
    UINT32      uwEventID;           /*record event id               */
    UINT32      uwMainLen;           /*Event main data length        */
    UINT32      uwExtraLen;          /*Event extensive data length   */
    VOID      * pNextRecord;         /*Next record addr              */
} OS_BOX_RECORD_S;

/*??????????*/
typedef struct tagBoxSegmentStru
{
    UINT32            uwMagicNo;     /*magic NO                 */
    UINT32            uwRecordNum;   /*the record num           */
    OS_BOX_RECORD_S * pstHeadRecord; /*the first record         */
    OS_BOX_RECORD_S * pstTailRecord; /*the last record          */
} OS_BOX_SEGMENT_S;

/*???????????*/
typedef struct tagBoxRegionStru
{
    UINT32      uwMagicNo;                              /*magic NO                 */
    CHAR        pacRegionName[OS_BOX_REGION_NAME_LEN];  /*Region name              */
    VOID*       pStartAddr;                             /*Region data start addr   */
    UINT32      uwRegionSize;                           /*regionn size             */
    UINT32      uwCurrentSeg;                           /*Current Segment num      */
    UINT32      uwSegmentLen;                           /*the region Segment len   */
    UINT32      uwSegmentNum;                           /*the region Segment num   */
    UINT32      uwBoxRegionId;                          /*Region id                */
    OS_BOX_SEGMENT_S * pstRegionSegment;                /*?????????????*/
} OS_BOX_REGION_S;

/*???????????*/
typedef struct tagBoxAreaStru
{
    UINT32     uwMagicNo;                   /* magic NO             */
    UINT32     uwByteOrder;                 /* Byte order           */
    UINT32     uwRegionNum;                 /* Region number        */
    UINT32     uwSerialInitTimes;           /* SerialInit times     */
    UINT32     uwBoxLevel;                  /* box level            */
    UINT32     uwBoxLength;                 /* box length           */
    VOID     * pBoxStartAddr;               /* box start addr       */
    VOID     * pBoxEndAddr;                 /* box end addr be user */
    OS_BOX_REGION_S stRegionHead[1];      /*first region heard */
} OS_BOX_AREA_S;

extern OS_BOX_AREA_S      * g_pstBoxArea;       /*??????????    */

/*****************************************************************************
Description : ???????--????,????????????????,??
Input
Output      :
Return      : SRE_OK on success
              OS_FAIL on fail
*****************************************************************************/
UINT32 IT_BoxDelete(CHAR  *pcBoxName)
{
    UINT32   uwIndex;
    UINTPTR  uvIntSave;
    OS_BOX_REGION_S    * pstRegion;
    OS_BOX_AREA_S      * pstArea;

    if (OS_FAIL == osFindRegion(pcBoxName,&uwIndex))
    {
        return OS_FAIL;
    }

    uvIntSave = __SRE_IntLock();

    pstArea   = g_pstBoxArea;
    pstRegion = &(pstArea->stRegionHead[uwIndex]);

    memset(pstRegion->pStartAddr, g_pstBoxArea->pBoxEndAddr - pstRegion->pStartAddr, 0);  //???????

    g_pstBoxArea->pBoxEndAddr = pstRegion->pStartAddr;   //?????????

    OS_BOX_INIT_REGION(pstRegion);     //??????????

    (VOID)__SRE_IntRestore(uvIntSave);
    return SRE_OK;
}
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /*_OSTEST_INC*/
/**
 * History:
 * 2010-8-30 z00133009: Create this file.
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
