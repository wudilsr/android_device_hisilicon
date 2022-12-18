/**
* @file osTets.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：测试文件的头文件。 \n
*/

#ifndef _OSTEST_H
#define _OSTEST_H

#include "sre_base.h"
#include "sre_task.h"
#include "sre_swi.h"
#include "iCunit.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define UT_SIMULATE YES                         /*TI平台仿真or单板测试控制开关*/
#define UT_SWI_PRIORITY   7                     /*测试用软中断优先级*/

/*测试任务的相关配置*/
#define UT_TEST_TSK_PRIO                        25
#define UT_TEST_TSK_NAME                        "TestTask"

#define OS_MEM_DEFAULT_LCDYN_PT     3               /*测试用私有pool分区号*/
#define OS_MEM_DEFAULT_MCDYN_PT     4               /*测试用共享pool分区号*/
#define OS_MEM_PT5   5
//#define OS_MEM_DYNAMIC_PT_SIZE     0x1000           /*测试用私有pool分区大小*/
//#define OS_MEM_MCDYNAMIC_PT_SIZE   0x2000           /*测试用共享pool分区大小*/

#define UT_MEM_PTNO                   7
#define TEST_MEM_POOL_PT8             8
#define TEST_MEM_POOL_PT9             9
#define TEST_MEM_POOL_PT10            10
#define TEST_MEM_POOL_PT13            13
#define UT_MCMEM_PTNO                 11
#define UT_MCPOOLMEM_PTNO             14
#define UT_POOLMEM_PTNO               6
#define UT_LCDYNPLMEM_PTNO            12
#define UT_SRE_MCDYN_FSC_MEM_PTN0     16
#define UT_SRE_MCDYN_FSC_MEM_PTN1     17
#define UT_SRE_MCDYN_FSC_MEM_PTN2     18
#define UT_SRE_MCDYN_FSC_MEM_PTN3     19
#define UT_SRE_MCPOOL_MEM_PTN4        15
#define UT_HWI_EVENT_0 7
#define UT_HWI_EVENT_1 7
#define UT_HWI_PRIO_0 0xa0
#if 0
/*不同平台多核用例核号配置*/
#if((OS_CPU_TYPE == OS_SD6181)&& (OS_HARDWARE_PLATFORM == OS_DSP170))        //81dsp
#define TEST_RUN_CORE1     4
#define TEST_RUN_CORE2     5
#define TEST_RUN_CORE3     6
#define TEST_RUN_CORE4     7
#define TEST_RUN_CORE5     8
#define TEST_RUN_CORE6     9
#elif((OS_CPU_TYPE == OS_SD6181)&& (OS_HARDWARE_PLATFORM == OS_RISC170))     //81cpu
#define TEST_RUN_CORE1     0
#define TEST_RUN_CORE2     1
#define TEST_RUN_CORE3     2
#define TEST_RUN_CORE4     3
#define TEST_RUN_CORE5     0xFF
#define TEST_RUN_CORE6     0xFF
#elif((OS_CPU_TYPE == OS_SD6108)&& (OS_HARDWARE_PLATFORM == OS_DSP170))      //08dsp
#define TEST_RUN_CORE1     5
#define TEST_RUN_CORE2     6
#define TEST_RUN_CORE3     7
#define TEST_RUN_CORE4     8
#define TEST_RUN_CORE5     9
#define TEST_RUN_CORE6     10
#elif((OS_CPU_TYPE == OS_SD6108)&& (OS_HARDWARE_PLATFORM == OS_RISC170))     //08cpu
#define TEST_RUN_CORE1     0
#define TEST_RUN_CORE2     1
#define TEST_RUN_CORE3     2
#define TEST_RUN_CORE4     3
#define TEST_RUN_CORE5     4
#define TEST_RUN_CORE6     0xFF
#elif((OS_CPU_TYPE == OS_SD6182)&& (OS_HARDWARE_PLATFORM == OS_DSP220))      //82dsp
#define TEST_RUN_CORE1     0
#define TEST_RUN_CORE2     1
#define TEST_RUN_CORE3     2
#define TEST_RUN_CORE4     3
#define TEST_RUN_CORE5     4
#define TEST_RUN_CORE6     5
#elif((OS_CPU_TYPE == OS_SD6182)&& (OS_HARDWARE_PLATFORM == OS_RISC220))     //82CPU
#define TEST_RUN_CORE1     12
#define TEST_RUN_CORE2     13
#define TEST_RUN_CORE3     14
#define TEST_RUN_CORE4     15
#define TEST_RUN_CORE5     16
#define TEST_RUN_CORE6     17
#else((OS_CPU_TYPE == OS_SD6182)&& (OS_HARDWARE_PLATFORM == OS_DSP220))      //82HACC
#define TEST_RUN_CORE1     10
#define TEST_RUN_CORE2     11
#define TEST_RUN_CORE3     0xFF
#define TEST_RUN_CORE4     0xFF
#define TEST_RUN_CORE5     0xFF
#define TEST_RUN_CORE6     0xFF
#endif
#endif


#define TEST_RUN_CORE1     OS_SYS_CORE_MASTER
#define TEST_RUN_CORE2     OS_SYS_CORE_MASTER+1
#define TEST_RUN_CORE3     OS_SYS_CORE_MASTER+2
#define TEST_RUN_CORE4     OS_SYS_CORE_MASTER+3
#define TEST_RUN_CORE5     0xFF
#define TEST_RUN_CORE6     0xFF


#define IT_SIMULATE YES                         /*TI平台仿真or单板测试控制开关*/
#define IT_SWI_PRIORITY   7                     /*测试用软中断优先级*/


#define OS_MEM_DEFAULT_LCDYN_PT     3               /*测试用私有page分区号*/
#define OS_MEM_DEFAULT_MCDYN_PT     4          /*测试用共享pool分区号*/
#define OS_MEM_DYNAMIC_PT_SIZE     0x1000         /*测试用私有page分区大小*/
#define OS_MEM_MCDYNAMIC_PT_SIZE   0x10           /*测试用共享pool分区大小*/


#define SRE_MSG_DATA(uwMsgHandle) (VOID*)uwMsgHandle
#define TS_MSG_RECEIVE_ERR 0xFFFFFFFF
extern UINT32 TS_SRE_MsgRecv(UINT32 uwTimeout, UINT32 *puwType, UINT32 *puwSenderPID);
extern VOID WriteVector(UINT8 *uwParam);
extern VOID ReadVector(UINT8 *uwParam);
extern UINT32 g_uwTiggerFlag;
extern UINT32 g_uwTestTaskQnum;
extern UINT32 IT_BoxDelete(CHAR  *pcBoxName);

#define IT_MyCoreIndex  (SRE_GetCoreID() - SRE_GetMasterCore())   /*核序号*/


#if (OS_HARDWARE_PLATFORM == OS_SC3400)
#define OS_SYNC_MEMORY() asm(" syncm")
#else
#define OS_SYNC_MEMORY()
#endif


/*为保证用例兼容，默认IT_HWI_EVENT_0 优先级高于IT_HWI_EVENT_1，再增加平台时注意*/


#if(OS_HARDWARE_PLATFORM == OS_DSP170)
#define IT_HWI_EVENT_0 11
#define IT_HWI_EVENT_1 7
#define IT_HWI_PRIO_0 6
#define IT_HWI_PRIO_1 5
#elif((OS_HARDWARE_PLATFORM == OS_CORTEX_A9) || (OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
#define IT_HWI_EVENT_0 7
#define IT_HWI_EVENT_1 7
#define IT_HWI_PRIO_0 6
#define IT_HWI_PRIO_1 5
#endif

#define IT_HWI_SECURE_MODE 0
#define IT_HWI_NOT_SECURE_MODE 1

typedef union
{
    int b1;
    char b2;
    int b3;
    int b4;
    short b5;
    int b6;
    int b7;
    long b8;
    int b9;
}union_b;
typedef struct
{
    int a1;
    int a2;
    int a3;
    int a4;
    int a5;
    int a6;
    int a7;
    int a8;
    int a9;
    int a10;
    union_b a11;
    int a12;
}struct_a;
typedef union
{
    int             siVal;
    char            scVal;
    short           ssVal;
    unsigned long   ulVal;
}union_a;



extern TSK_HANDLE_T g_TestTskHandle;    /* 测试任务句柄 */
extern VOID TEST_HwiTrigger(UINT32 uwEvtNum);       /*如果是TI平台，此函数只能用于仿真环境上的硬中断触发*/
extern UINT32 Itest_MemInfoReStore(const char * pacMemFilePath, VOID * uwMemStartAddr, UINT32 uwMemInfolen);

extern UINT32 osTestInit(void);
extern UINT32 iCunitInit(void);
extern UINT32 iCunitPrintReport(void);
extern UINT32 iCunitSaveReport(char *iCunitReportName);
extern UINT32 test_delay(UINT64 Cycle);
extern UINT32 test_delay_tick(UINT32 uwtick) ;
extern UINT32 Test_SwTimerGroupDelete(void);
extern UINT32 Itest_Auto_Dump(char *case_name,char *watch_point);
extern UINT32 Itest_Auto_Rule(char *case_name,char *watch_point,char *rule);
extern VOID TEST_MemPtDelete(UINT8 ucPtNo);
extern VOID CITestLastWordsHook(VOID);
extern VOID ItSuite_SreCache(VOID);
extern VOID ItSuite_sreMsg2(VOID);

/* 此处放多平台公用的IT测试用例   */
extern VOID ItSuite_UniSwTmr(void);
extern VOID ItSuite_UniMemDbg(void);
extern VOID ItSuite_UniTask(void);
extern VOID ItSuite_UniTask2(void);
extern VOID ItSuite_UniTaskHook(void);
extern VOID ItSuite_UniTrace(void);
extern VOID ItSuite_SreSwiMc(void);
extern VOID ItSuite_SreSwi(void);
extern VOID ItSuite_UniSwi(void);
extern VOID ItSuite_UniSwi2(void);
extern void ItSuite_UniSwi3(void);
extern VOID ItSuite_UniHwTmr(VOID);
extern VOID ItSuite_UniHwi(VOID);
extern VOID ItSuite_UniLastWord();
extern VOID ItSuite_UniFastSwitch();
extern VOID ItSuite_UniSwTmr();
extern VOID ItSuite_UniSys();
extern VOID ItSuite_FSCMem();
extern VOID ItSuite_FSCMem_Rt();
extern VOID ItSuite_UniPrivPoolMem();
extern VOID ItSuite_UniSharPoolMem();
extern VOID ItSuite_UniMcSem_mc();
extern VOID ItSuite_UniCpup();
extern VOID ItSuite_UniHwi_Dsp170();
extern VOID ItSuite_UniHwsem_6181();
extern VOID ItSuite_UniHwTmr_dsp170();
extern VOID ItSuite_VecSetCpy();
extern VOID ItSuite_UniHwsem();
extern VOID ItSuite_UniHwSemEx(void);
extern VOID ItSuite_UniLHwsem();
extern VOID ItSuite_UniVecReg();
extern void ItSuite_SreHunt(void);
extern void ItSuite_SreHunt_Mc(void);
extern void ItSuite_SreBox(void);
extern void ItSuite_SreBoxTool(void);
extern void ItSuite_UniCda_Mc();
extern void ItSuite_UniCda();
extern void ItSuite_UniCda2();
extern void ItSuite_UniErr();
extern void ItSuite_UniTrace_2();
extern void ItSuite_UniCstkGet(void);
extern void ItSuite_UniExc(void);
extern void ItSuite_UniTaskEx(void);
extern void ItSuite_UniMsg2(void);
extern void ItSuite_MemMinor();
extern void ItSuite_UniSem(void);
extern void ItSuite_UniMsg(void);
extern void ItSuite_UniFsem(void);
extern void ItSuite_Unithread(void);
extern void ItSuite_UniTaskMon(VOID);
extern VOID ItSuite_UniMemStat(void);
extern VOID ItSuite_UniMsg_Mc(void);
extern void ItSuite_UniTask(void);
extern VOID ItSuite_sysstack();
extern VOID ItSuite_UniHwi_Combine0801();
extern VOID ItSuite_UniHwi_Dsp170();
extern VOID ItSuite_UniHwTmr_dsp170();
extern void ItSuite_UniTask(void);
extern void ItSuite_SreHunt();
extern void It_Suite_SreErr();
//by Deng
extern void ItSuite_uniSemPendListGet();
extern void ItSuite_uniMcSemPendListGet();
extern void ItSuite_VecSetCpy();
extern VOID ItSuite_UniHwi();
extern VOID ItSuite_UniHwi_risc170();
//by Deng - end
extern VOID ItSuite_SRECpup(VOID);
extern VOID ItSuite_SreTick(VOID);
extern VOID ItSuite_SreSys(VOID);
extern VOID ItSuite_sreExc(VOID);
extern VOID ItSuite_McMsgLeakMon();

#if((OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC170)|| (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220))
extern VOID ItSuite_UniHwi_Combine0881(void);
extern VOID ItSuite_UniHwTmr_risc170(void);
#endif

#if((OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220)||(OS_HARDWARE_PLATFORM == OS_HACCC))
extern VOID ItSuite_SreVecCpy(void);
#endif

#if((OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC170))
extern VOID ItSuite_UniPatch_Mc();
#endif

extern VOID ItSuite_srehook();
extern VOID ItSuite_sremsg();
extern VOID ItSuite_sreSem();
extern VOID ItSuite_sretime();
extern VOID ItSuite_srefsem();
extern VOID ItSuite_SreMem();
extern void ItSuite_SRETask();
extern VOID ItSuite_sretask();
extern VOID ItSuite_SRE_Hwi_Combine();
extern VOID ItSuite_SRE_Hwi();
extern VOID ItSuite_SRE_HwTmr();
extern VOID ItSuite_SreFastSwitch();

extern VOID UT_SRE_Hunt();
extern VOID UT_SRE_err();
extern VOID UT_SRE_DynPoolMem();
extern VOID UT_SRE_DynPoolMem_Init();
extern VOID UT_SRE_FscMem();
extern VOID UT_SRE_FscMem_Init();
extern VOID UT_SRE_Mem();
extern VOID UT_SRE_Mem_Init();
extern VOID UT_SRE_Mem_Minor();
extern VOID UT_sre_fsem();
extern VOID UT_SRE_Hwi();
extern VOID UT_sre_msg();
extern VOID UT_sre_msg_init();
extern VOID UT_sre_msg_minor();
extern VOID UT_SRE_sem();
extern VOID UT_sre_swi();
extern VOID UT_sre_swi_init();
extern VOID UT_sre_swi_minor();
extern VOID UT_sre_task();
extern VOID UT_sre_task_init();
extern VOID UT_sre_task_minor();

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /*_OSTEST_H*/
/**
 * History:
 * 2010-8-30 z00133009: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
