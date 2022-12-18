/*
    ??óDè???±?á?
*/



#include "osTest.h"
#include "sre_swi.h"
#include "sre_sem.h"
#include "sre_task.h"
#include "sre_config.h"
#include "sre_buildef.h"
#include "app_data_common.h"
#include "sre_sem.h"

TEST_SEC_BSS UINT8 m_aucUtDynplmemRegion[0x00001500] ;       /* 私有动态pool内存单元测试使用分区   */
TEST_SEC_BSS UINT8 m_aucUtStmemRegion[UT_STATMEM_SIZE];       //私有静态内存单元测试使用分区
TEST_SEC_BSS UINT8 m_aucFscMemRegion_hc1[0x11000];

//OS_SEC_BSS UINT8 m_aucDoubleExcStackRegion[OS_DOUBLE_EXC_STACK_SIZE];   // DoubleException堆栈
//OS_SEC_BSS UINT8 m_aucMemRegion00[OS_MEM_FSC_PT_SIZE] ;   /* 私有静态内存分区(缺省) */
TEST_SEC_BSS UINT8 m_aucMemRegion02[OS_MEM_DYNAMIC_PT_SIZE] ;  /* 私有动态pool式内存分区   */
//OS_SEC_BSS UINT8 m_aucDoubleExcStackRegion[OS_DOUBLE_EXC_STACK_SIZE];   // DoubleException堆栈
TEST_SEC_BSS UINT8 m_aucStaMemRegion_hc[0x2800];
TEST_SEC_BSS TSK_HANDLE_T g_TestTskHandle;                     /*总测试任务线程PID*/
TEST_SEC_BSS UINT32 g_uwTestTaskQnum;


TEST_SEC_BSS volatile UINT32  g_ITestCheckLc;                             //私有全局测试用辅助变量
#if 0
OS_SEC_BSS SWI_HANDLE_T     g_TestSwiHandle;                            //总测试软中断线程PID
OS_SEC_BSS SWI_HANDLE_T     g_TestCpupSwiHandle;                        //软中断框架下Cpup使用测试软中断线程PID
OS_SEC_BSS UINT32           g_uwHwSemExcFlag;                           //HwSem异常用例自动化时需要的判断标志位
OS_SEC_BSS SEM_HANDLE_T     g_TestSemHandle;                            //全局测试用例核内信号量句柄
OS_SEC_BSS_SHARED UINT8 m_aucStaMemRegion_hc3[0x5000];
OS_SEC_BSS_SHARED UINT8 m_aucStaMemRegion_hc4[0x1200];

#ifndef CI_SIM_PAT_TEST
OS_SEC_BSS_SHARED UINT8 m_aucFscMemTest1[0x10800];
OS_SEC_BSS_SHARED UINT8 m_aucFscMemTest2[0x100];
#endif
#endif
TEST_SEC_BSS UINT8 m_aucStaMemRegion_hc4[0x2000];
TEST_SEC_BSS UINT8 m_aucFscMemTest1[0x1000];
TEST_SEC_BSS UINT8 m_aucFscMemTest2[0x1000];
TEST_SEC_BSS UINT8 m_aucFscMemTest3[0x1000];
TEST_SEC_BSS UINT8 m_aucFscMemTest_shared[0x100];
#if 0
//放在两个bank的可以提高性能
#if (OS_HARDWARE_PLATFORM == OS_DSP170)
#define IT_SEC_DATA_BK2         __attribute__((section(".os.data.bk2")))
#else
#define IT_SEC_DATA_BK2
#endif
/*协处理器异常测试用*/
OS_SEC_DATA     __attribute__ ((aligned (64), common)) UINT8 taskOnebuf1[404]={0};
IT_SEC_DATA_BK2 __attribute__ ((aligned (64), common)) UINT8 taskOneBuf2[404]={0};
OS_SEC_DATA     __attribute__ ((aligned (64), common)) UINT8 taskTwobuf1[404]={0};
IT_SEC_DATA_BK2 __attribute__ ((aligned (64), common)) UINT8 taskTwoBuf2[404]={0};
OS_SEC_DATA     __attribute__ ((aligned (64), common)) UINT8 taskThreebuf1[404]={0};
IT_SEC_DATA_BK2 __attribute__ ((aligned (64), common)) UINT8 taskThreebuf2[404]={0};
/****end***协处理器异常测试用*/



#if((VOS_HARDWARE_PLATFORM_PATCH == PAT_SC3400)||(VOS_HARDWARE_PLATFORM_PATCH == PAT_SD6155) \
    || ((VOS_HARDWARE_PLATFORM_PATCH == PAT_DSP170) || (VOS_HARDWARE_PLATFORM_PATCH == PAT_RISC170) ))
UINT8 *g_Itestpbuffer = NULL;
long int g_ulItestSize;
unsigned long int g_ulItestPatchFileLength; //补丁文件长度
TSK_HANDLE_T SynIdleTaskID;
TSK_HANDLE_T ItestTaskID;
TSK_HANDLE_T PatchSynMsgTaskID;
UINT32 g_McPatchTest_while;
UINT32 g_McPatchTest_for;
UINT32 g_error;
UINT32 g_localdatatest;
struct_a g_stra,g_strb;
union_a  g_unPatUnion;
struct_a *g_pstra = &g_stra;
int *g_array[10][2];
UINT32 g_memalloc;
UINT32 g_memfree;
UINT32 g_callCount=0;
#pragma align m_aucStaMemRegion_hc  32
#pragma align m_aucStaMemRegion_hc2 32
#pragma align m_aucStaMemRegion_hc3 32
#pragma align m_aucStaMemRegion_hc4 32
#pragma align m_aucMemRegion00 32
#pragma align m_aucMemRegion02 32
#pragma align g_TestTskHandle 32
#pragma align g_ITestCheckLc 32
#endif /*OS_SC3400*/
#endif

SWI_HANDLE_T g_TestSwiHandle;                     /*总测试软中断线程PID*/
SWI_HANDLE_T g_TestCpupSwiHandle;                 /*软中断框架下Cpup使用测试软中断线程PID*/
UINT32 g_uwHwSemExcFlag;                          //HwSem异常用例自动化时需要的判断标志位
SEM_HANDLE_T g_TestSemHandle;                    //全局测试用例核内信号量句柄

#if 0
/*核间信号量测试用 */
OS_SEC_DATA MCSEM_HANDLE_T uwMcSemHandles[OS_MCSEM_MAX_SUPPORT_NUM];
OS_SEC_DATA volatile SEM_HANDLE_T uwSemHandles[OS_SEM_MAX_SUPPORT_NUM];
/****end***核间信号量测试用*/


/*硬件定时器测试用*/
OS_SEC_DATA volatile UINT32 m_testHwTmrValue;
OS_SEC_DATA volatile UINT32 g_testCoreReboot;
OS_SEC_DATA volatile UINT32 g_testHwTmrValueA;
OS_SEC_DATA volatile UINT32 g_testHwTmrValueB;
OS_SEC_DATA volatile UINT32 g_testHwiValue;
OS_SEC_DATA volatile UINT32 g_testSwiValue;
OS_SEC_DATA volatile UINT32 g_testTaskValue;
OS_SEC_DATA volatile UINT64 m_uwHwtmrInterval[100];
OS_SEC_DATA volatile UINT64 g_uwTimeEnd;
OS_SEC_DATA UINT64 m_testTickCount;
OS_SEC_DATA UINT64 m_testMonitorCount;

/****end***硬件定时器测试用*/
#endif
