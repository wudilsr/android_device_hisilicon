 /**
* @file osTest.c
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：测试文件。
*/

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <stdarg.h>
#include "sre_base.h"
#include "osTest.inc"
#include "osTest.h"
#include "iCunit.h"
#include "sre_mem.h"
#include "sre_config.h"
#include "sre_sys.h"
#include "sre_buildef.h"
#include "sre_exc.h"
#include "sre_msg.h"
#include "sre_secure_timer.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if(YES == OS_INCLUDE_TSKMON)
/*任务栈监控钩子函数*/
extern void It_TaskStackMonitor(TSKMON_INFO_S* pstInfo);
#endif

extern UINT8 m_aucMemRegionBox[OS_SYS_CORE_RUN_NUM][OS_BOX_SPACE_LENGTH];
extern UINT8 m_aucMemRegion02[OS_MEM_DYNAMIC_PT_SIZE];
//extern UINT8 m_aucMemRegion03[OS_MEM_MCDYNAMIC_PT_SIZE];
//extern UINT8 m_aucStaMemRegion_hc3[0x500];
extern UINT32  g_vuwUniFlag;
extern VOID ItSuite_SRE_TickHook();
//extern UINT32 SRE_MsgSendStub(MSG_HANDLE_T uwMsgHandle, UINT32 uwMsgID, MSG_PID_T uwDstPID, UINT8 ucDstQID);
//extern UINT32 SRE_NohookMsgQRecvStub(MSG_HANDLE_T * puwMsgHandle, UINT32 * puwMsgID, MSG_PID_T * puwSenderPID, UINT8 ucRecvQID, UINT32 uwTimeout);

#define OS_MEM_PT5   5

extern void serial_putc (const char c);
extern void serial_puts (const char *s);
extern void console_init();
extern VOID ostesttastSwitch();
extern VOID ostestFiqInt(VOID);
//extern VOID osTestTCB(TSK_CB_S *pstTcb);
extern VOID osTestTCB(UINT32 uwMode);
extern VOID osprintf_secure(VOID);
extern VOID osprintf_fail(VOID);
extern VOID osprintf_passT1(VOID);
extern VOID osprintf_passT2(VOID);
extern VOID osprintf_passexit(VOID);
extern VOID osprintf_s_to_n(VOID);
extern VOID osprintf_n_to_s(VOID);
extern VOID start_tz();
//extern void GIC_SPI_init_restore(void );
//extern UINT32 g_uwTestSwitchFIQ;
//extern void uart_printf(const char *fmt, ...);
//extern UINT32 SRE_GetRunningTaskID(VOID);
/*
void uart_printf(const char *fmt, ...)
{
    char buf[128];
    va_list arglist;

    memset(buf, 0, sizeof(buf));
    va_start(arglist, fmt);
    vsnprintf(buf, sizeof(buf), fmt, arglist);
    va_end(arglist);

    serial_puts(buf);
}*/


/*gbdsp fpga验证环境初始化DDR*/
#if(OS_CPU_TYPE == OS_GBDSP)
#define DDRC_BASE_ADDR (0x76400000)
#if 0
UINT32 uwDDR_init()
{
    UINT32 gogo,i;


    REG32(DDRC_BASE_ADDR+0x360) = 0x7;
    REG32(DDRC_BASE_ADDR+0x004) = 0x0;


    for (i=0;i<=0x800;i++)
    {
    }
    REG32(DDRC_BASE_ADDR+0x014) = 0x32;
    REG32(DDRC_BASE_ADDR+0x018) = 0x00;


    REG32(DDRC_BASE_ADDR+0x01C) = 0x70000510;
    //REG32(DDRC_BASE_ADDR+0x0)   = 0x0000000a;
    REG32(DDRC_BASE_ADDR+0x020) = 0x00000008;
    REG32(DDRC_BASE_ADDR+0x02C) = 0x00000021;
    REG32(DDRC_BASE_ADDR+0x050) = 0x31110302;
    REG32(DDRC_BASE_ADDR+0x054) = 0xC8321304;
    REG32(DDRC_BASE_ADDR+0x058) = 0x321040ff;
    REG32(DDRC_BASE_ADDR+0x05C) = 0xffdff4f4;
    REG32(DDRC_BASE_ADDR+0x0AC) = 0x0F100103;
    REG32(DDRC_BASE_ADDR+0x0f4) = 0x00000001;
    REG32(DDRC_BASE_ADDR+0x008) = 0x00000001;


    gogo = REG32(DDRC_BASE_ADDR + 0x08);
    uart_printf("read 0x08 value is %x\n",gogo);
    gogo = REG32(DDRC_BASE_ADDR + 0xD4);
    uart_printf("read 0xD4 value is %x\n",gogo);    //此处返回0xf00就是正确的值。

    return gogo;
}
#endif
#endif

VOID ostesttastSwitch(VOID)
{
	uart_printf("g_vuwUniFlag = %0x\n", g_vuwUniFlag);
	uart_printf("step into task first switch \n");
}

VOID ostestFiqInt(VOID)
{
	uart_printf("step into Fiq interrupt!\n");
}

VOID ostestIrqInt(VOID)
{
	uart_printf("step into irq interrupt!\n");
}

VOID ostestReservedVector(VOID)
{
	uart_printf("step into Reserved Vector!\n");
}

VOID ostestDataAbort(VOID)
{
	uart_printf("step into data abort!\n");
}

VOID ostestPrefetchAbort(VOID)
{
	uart_printf("step into Prefetch abort!\n");
}

VOID ostestSwiVector(VOID)
{
	uart_printf("step into Swi Vector:!\n");
}

VOID ostestUndefInstrVector(VOID)
{
	uart_printf("step into UndefInstrVector:!\n");
}

VOID ostestResetVector(VOID)
{
	uart_printf("step into ResetVector:!\n");
}


#if 0
VOID osTestTCB(TSK_CB_S *pstTcb)
{
	uart_printf("TaskId = %d\n", pstTcb->uwTaskPID);
	uart_printf("entry = %0x\n", pstTcb->pfnTaskEntry);
}
#endif

#if 1
VOID osTestTCB(UINT32 uwMode)
{
	uart_printf("TaskId = %d\n", uwMode);
	uart_printf("entry = %0x\n", uwMode);
}
#endif

VOID osuart_printf_secure(VOID)
{
	uart_printf("uart_printf_secure\n");
}

VOID osuart_printf_monitor_fiqHandler(VOID)
{
	uart_printf("######osuart_printf_monitor_fiqHandler\n");
}

VOID osuart_printf_fail(VOID)
{
	uart_printf("uart_printf_fail\n");
}

VOID osuart_printf_passT1(VOID)
{
#if 0

	for (; ;)
	{
		if (g_uwTestSwitchFIQ == 1)
		{
			uart_printf("FIQ execute finished!!!!!!\n");
			break;
		}
		uart_printf("g_uwTestSwitchFIQ = %d\n", g_uwTestSwitchFIQ);
	}

	uart_printf("exit from execute FIQ!!!!!!\n");

	GIC_SPI_init_restore();
#endif

	uart_printf("RTOSck: SMC passT1!!!!!!\n");
}

VOID osuart_printf_passT2(VOID)
{
      #if 0
	if (g_uwTestSwitchFIQ == 0)
	{

		for (; ;)
		{
			if (g_uwTestSwitchFIQ == 1)
			{
				uart_printf("FIQ execute finished!!!!!!\n");
				break;
			}
			uart_printf("g_uwTestSwitchFIQ = %d\n", g_uwTestSwitchFIQ);
		}

		uart_printf("exit from execute FIQ!!!!!!\n");

		//GIC_SPI_init_restore();
	}

	uart_printf("RTOSck: SMC passT2!!!!!!\n");
      #endif
}

VOID osuart_printf_passexit(VOID)
{
	uart_printf("passExit\n");
}

VOID osuart_printf_s_to_n(VOID)
{
	uart_printf("uart_printf_s_to_n\n");
}

VOID osuart_printf_n_to_s(VOID)
{
	uart_printf("uart_printf_n_to_s\n");
}

/*********************************************************************************
** Description: 在以base为起始地址偏移为offset的位写入一个位变量,其他位保持不变
** param:    base:        基地址
**               offset:      地址偏移
**               set:          set == 0 清除该位。否则把该位置为1。
**********************************************************************************/
OS_SEC_TEXT_MINOR UINT32 bit_write_by_offset_base_test(UINT32 *base,UINT32 offset, UINT32 set)
{
    UINT32  bitmap =0;
    UINT32  newwordvalue = 0;
    UINT32  *newwordbase = NULL;

    if((UINT32)base & 0x03){
        return OS_FAIL;
    }

    bitmap = 1 << (offset % 32);
    //bitmap = OS_BYTE_ORDER_SWAP32(bitmap);

    newwordbase = base  + offset / 32;

    newwordvalue = *newwordbase;

    uart_printf("pending bit: = 0x%x\n", newwordvalue);

    #if 0
    if (set)
    {
        newwordvalue |= bitmap;
    }
    else
    {
        newwordvalue &= (~bitmap);
    }

    *newwordbase = newwordvalue;
    #endif
    return SRE_OK;
}

/*****************************************************************************
 Description : 清除单个硬中断的Pending位
 Input       : uwHwiNum   --- 硬中断号
 Output      : None
 Return      : 成功时返回OS_SUCCESS，失败时返回错误码
 *****************************************************************************/
OS_SEC_TEXT UINT32 SRE_HwiPendingBit_test(HWI_HANDLE_T uwHwiNum)
{
    UINTPTR uvIntSave;
    UINT32 *puwHwiClearPendingBase;

    if (uwHwiNum >= 192)
    {
        RETURN_ERROR(OS_ERRNO_HWI_NUM_INVALID);
    }

    uvIntSave = __SRE_IntLock();

    puwHwiClearPendingBase = ( UINT32 *)(GIC_ID_PHY_BASE + GICD_PENDINGCLEAR);
    bit_write_by_offset_base_test(puwHwiClearPendingBase, uwHwiNum, 1);

    __SRE_IntRestore(uvIntSave);

    return SRE_OK;
}

VOID TestTaskEntry(VOID)
{
      UINT32 uwSCR, uwCpsSave;
      UINT32 uwRet;
      UINT32 uwTimerValue = 0;
      UINT32 *global_task_base;

#if 0
      __asm__ __volatile__( "MRC  p15, 0, %0, c1, c1, 0"
           :"=r"(uwSCR));

      uart_printf("uwSCR = 0x%x\n", uwSCR);

    __asm__ __volatile__("MRS   %0, cpsr\n"
        :"=r"(uwCpsSave) );

        uart_printf("uwSCR = 0x%x\n", uwCpsSave);
#endif
	iCunitInit();

    uart_printf("sleep 30s, then start the it cases\n\n");
    //SRE_SwSleep(10);
    //SRE_SwMsleep(1);
    uart_printf("###################################\nAha , bored Testing begin ...... \n###################################\n");
#if 0
	ItSuite_FSCMem();
	ItSuite_FSCMem_Rt();
	ItSuite_UniPrivPoolMem();
	ItSuite_SRETask();
	ItSuite_sreMsg();
	ItSuite_SreFsem();
	ItSuite_sreSem();
	ItSuite_SreSwi();
#endif
        //UT_uni_cachemmu();
        UT_uni_hwi();
        UT_SRE_err();
        UT_SRE_Hunt();
#if 1
        UT_sre_fsem();
        UT_SRE_sem();

#endif
#if 1
        UT_SRE_Mem();
        UT_SRE_Mem_Init();
        UT_SRE_Mem_Minor();
#endif

#if 1
        UT_SRE_FscMem();
        UT_SRE_FscMem_Init();
        UT_SRE_DynPoolMem();
        UT_SRE_DynPoolMem_Init();
#endif

#if 1
        UT_sre_msg();
        UT_sre_msg_init();
        UT_sre_msg_minor();
#endif

#if 1
        UT_sre_swi();
        UT_sre_swi_init();
        UT_sre_swi_minor();
        UT_sre_task();
        UT_sre_task_init();
        UT_sre_task_minor();
#endif

#if 1
        UT_uni_timer();
#endif


	uart_printf("###################################\nOh Yeah, finished !!\n###################################\n");
#if 1
       for (; ;)
	{
		;
	}
#endif
#if 0
	for (; ;)
	{
		if (g_uwTestSwitchFIQ == 1)
		{
			uart_printf("FIQ execute finished!!!!!!\n");
			break;
		}
		uart_printf("g_uwTestSwitchFIQ = %d\n", g_uwTestSwitchFIQ);
	}


    uart_printf("exit from execute FIQ!!!!!!\n");

	//GIC_SPI_init_restore();
#endif


#if 0
    for (; ;)
    {
        //SRE_HwiPendingBit_test(FREE_RUNNING_FIQ_NUMBLER)
#if 0
        SRE_IntLock();
        uwTimerValue = SRE_SecureReadTimer(FREE_RUNNING_TIMER_BASE, 0);
        uart_printf("uwTimerValue = 0x%x\n", uwTimerValue);
        SRE_IntUnLock();

        __asm__ __volatile__("MRS   %0, cpsr\n"
        :"=r"(uwCpsSave) );

        uart_printf("uwSCR = 0x%x\n", uwCpsSave);
#endif
        ;
        //uart_printf("******endless loop !\n");
    }
#endif

    __asm__ __volatile__("MRS   %0, cpsr\n"
    :"=r"(uwCpsSave) );

    uart_printf("********after excute the it cases, the task's cpsr is = 0x%x\n", uwCpsSave);

    __SRE_TaskLock();

    osTaskInit();

    __SRE_TaskUnlock();

#if 0

    uart_printf("******start tz !\n");
    start_tz();


    uart_printf("******come back TZ !\n");
    while(1)
    {
        ;
    }
#endif
}


/*****************************************************************************
 Description: CI集成测试用临终遗言钩子函数与内存转储函数
 Input      :
 Return     :
*****************************************************************************/
VOID CItest_MemInfoStore(const char * pacMemFilePath, VOID * uwMemStartAddr, UINT32 uwMemInfolen)
{
/*
    FILE * pstFile;
    if ((NULL == pacMemFilePath)||(0 == uwMemInfolen)||(NULL == uwMemStartAddr))
    {
         uart_printf("input param Err!\n");
         return;
    }
    pstFile = fopen(pacMemFilePath, "wb");
    if (NULL == pstFile)
    {
        uart_printf("File open Err!\n");
        return;
    }
    fwrite(uwMemStartAddr, sizeof(char), uwMemInfolen, pstFile);

    fclose(pstFile);
*/
    return;
}
VOID CITestLastWordsHook( VOID)
{
    char CITestExcInfo[32] =  "c:\\PriMem_";
    char CITestExcInfo1[32] = "c:\\BoxInfo_";
    char CITestTemp[6];
#if (OS_HARDWARE_PLATFORM == OS_DSP170)
    VOID * MemStartAddr = (VOID *)0x01000000;
    UINT32 MemInfolen =   0x80000;
#elif (OS_HARDWARE_PLATFORM == OS_RISC170)
    VOID * MemStartAddr = (VOID *)0x01000000;
    UINT32 MemInfolen =   0x20000;
#elif (OS_HARDWARE_PLATFORM == OS_DSP220)
    VOID * MemStartAddr = (VOID *)0x08000000;
    UINT32 MemInfolen =   0x80000;
#elif (OS_HARDWARE_PLATFORM == OS_RISC220)
    VOID * MemStartAddr = (VOID *)0x08000000;
    UINT32 MemInfolen =   0x80000;
#elif (OS_HARDWARE_PLATFORM == OS_HACCC)
    VOID * MemStartAddr = (VOID *)0x08000000;
    UINT32 MemInfolen =   0x80000;
#endif
    //sprintf(CITestTemp, "%d.txt", SRE_GetCoreID());
    snprintf(CITestTemp, 10, "%d.txt", SRE_GetCoreID());

    strcat(CITestExcInfo, CITestTemp);
    strcat(CITestExcInfo1, CITestTemp);

    //CItest_MemInfoStore(CITestExcInfo, MemStartAddr, MemInfolen);//转储L1内存信息
#if (OS_INCLUDE_BOX == YES)
    //CItest_MemInfoStore(CITestExcInfo1, &m_aucMemRegionBox[IT_DengCoreIndex][0], OS_BOX_SPACE_LENGTH);//转储黑匣子空间信息
#endif
    return;
}

/*****************************************************************************
 Description: 测试任务入口处理函数
 Input      :
 Return     :
*****************************************************************************/

/*创建测试用默认分区-私有page和共享pool*/
UINT32 It_MemInit(void)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA stPtInfo;

    stPtInfo.enArith    = MEM_ARITH_FSC;
    stPtInfo.pPtAddr    = &m_aucMemRegion02[0];
    stPtInfo.uwPtSize   = OS_MEM_DYNAMIC_PT_SIZE;
    stPtInfo.ausSliceSize[0] = 32;
    stPtInfo.ausSliceSize[1] = 48;
    stPtInfo.ausSliceSize[2] = 64;
    stPtInfo.ausSliceSize[3] = 128;
    stPtInfo.ausSliceSize[4] = 256;
    stPtInfo.ausSliceSize[5] = 512;
    stPtInfo.ausSliceSize[6] = 1024;
    stPtInfo.ausSliceSize[7] = 2048;

    uwRet = SRE_MemPtCreate(&stPtInfo, OS_MEM_DEFAULT_LCDYN_PT);
    if(SRE_OK != uwRet)
    {
        return uwRet;
    }
#if 0
    stPtInfo.enArith   = MEM_ARITH_MCDYNFSC  ;
    stPtInfo.pPtAddr   = &m_aucMemRegion03[0];
    stPtInfo.uwPtSize  = OS_MEM_MCDYNAMIC_PT_SIZE;
    stPtInfo.ausSliceSize[0] = 16 ;
    stPtInfo.ausSliceSize[1] = 32 ;
    stPtInfo.ausSliceSize[2] = 64 ;
    stPtInfo.ausSliceSize[3] = 128 ;
    stPtInfo.ausSliceSize[4] = 256 ;
    stPtInfo.ausSliceSize[5] = 512 ;
    stPtInfo.ausSliceSize[6] = 1024 ;
    stPtInfo.ausSliceSize[7] = 2048 ;
    stPtInfo.bCachable = TRUE;
    uwRet = SRE_MemPtCreate(&stPtInfo,OS_MEM_DEFAULT_MCDYN_PT);
    if(SRE_OK != uwRet)
    {
        return uwRet;
    }



    stPtInfo.enArith   = MEM_ARITH_POOL  ;
    stPtInfo.pPtAddr   = &m_aucStaMemRegion_hc3[0];
    stPtInfo.uwPtSize  = 0x500;
    stPtInfo.ausSliceSize[0] = 16 ;
    stPtInfo.ausSliceSize[1] = 32 ;
    stPtInfo.ausSliceSize[2] = 64 ;
    stPtInfo.ausSliceSize[3] = 128 ;
    stPtInfo.ausSliceSize[4] = 256 ;
    stPtInfo.ausSliceSize[5] = 512 ;
    stPtInfo.ausSliceSize[6] = 1024 ;//{2,4,8,16,32,64,128,256};
    stPtInfo.ausSliceSize[7] = 2048 ;

    uwRet = SRE_MemPtCreate(&stPtInfo,OS_MEM_PT5);
    if(SRE_OK != uwRet)
    {
        return uwRet;
    }
	#endif

    //SRE_WaitForAllCores();
    return SRE_OK;
}

/* 任务创建等操作入口 */
UINT32 osTestInit(void)
{
    UINT32 uwRet = SRE_OK;
    TSK_INIT_PARAM_S os_task_init_param;

    char *str;

    uart_printf("osTestInit MemInit start\n");

    uwRet = It_MemInit();
    if(SRE_OK != uwRet)
    {
        uart_printf("It_MemInit excute error!\n");
        return uwRet;
    }

    //SRE_TaskLock();

    uart_printf("osTestInit MemInit successfully\n");

    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)TestTaskEntry;
    os_task_init_param.uwStackSize  = 0x1000;
    os_task_init_param.usTaskPrio = 25;
    os_task_init_param.pcName = "TestTask";
    os_task_init_param.uwPrivateData = 0;
    os_task_init_param.usQNum = 8;
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;

    uart_printf("Ut Test PartNo = %d\n", os_task_init_param.uwUsrSpacePartNo);

    uwRet = SRE_TaskCreate(&g_TestTskHandle, &os_task_init_param);
    if(SRE_OK != uwRet)
    {
        return uwRet;
    }

    uart_printf("*****************************g_TestTskHandle = %d\n", g_TestTskHandle);

    //SRE_TaskUnlock();

    #if(YES == OS_INCLUDE_TSKMON)
        /* 注册任务栈监控钩子函数 */
        uwRet = SRE_TskMonHookReg(It_TaskStackMonitor);
        if(SRE_OK != uwRet)
        {
            return uwRet;
        }
    #endif

   return uwRet;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * History:
 * 2010-08-30 z00133009: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
