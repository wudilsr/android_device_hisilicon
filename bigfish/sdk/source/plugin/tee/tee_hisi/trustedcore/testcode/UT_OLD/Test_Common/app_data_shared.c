#include "sre_config.h"
#include "sre_buildef.h"
#include "app_data_common.h"
#include "sre_sem.h"
#include "sre_msg.h"
#include "sre_mem.h"
#include "sre_hunt.ph"
#include "osTest.h"

OS_SEC_BSS_SHARED UINT8 m_aucUtMcmemRegion[0x00005000] ;               /* 共享动态Pool内存单元测试使用分区   */
OS_SEC_DATA_SHARED THREADINFO_S    *g_pstGlobalThreadInfo = NULL;


/************************************     此处定义共享不可cache全局变量****************************************/
//OS_SEC_DATA_SHARED volatile UINT32 g_aucMcRet[20] = {0};

OS_SEC_BSS_SHARED  UINT32 g_uwTiggerFlag;
OS_SEC_BSS_SHARED UINT32 g_uwMcSwiPID;
OS_SEC_BSS_SHARED UINT32 auwMcSwiFlag[OS_SYS_CORE_MAX_NUM];
//OS_SEC_BSS_SHARED UINT8 m_aucMemRegion01[OS_MEM_MCSTA_FSC_PT_SIZE]; /* 共享静态FSC内存分区(缺省) */
//OS_SEC_DATA_SHARED UINT32 m_auwShellSamMemRegion[2];                 //热点函数默认空间

OS_SEC_BSS SEM_HANDLE_T         uwSemHandle; /*私有信号量句柄*/
//OS_SEC_BSS_SHARED MCSEM_HANDLE_T       uwMcSemHandle; /*核间信号量句柄*/
//OS_SEC_BSS_SHARED MCSEM_HANDLE_T uwMcSemHandleS[16];

#if 0
OS_SEC_BSS_SHARED UINT8 m_aucMCStaFscTest1[0x2000];
OS_SEC_BSS_SHARED UINT8 m_aucMCStaFscTest2[0x100];
OS_SEC_BSS_SHARED UINT8 m_aucMCDynFscTest1[0x6000];                         //大小不可减小，会导致ItSuite_FSCMem_Rt用例跑不过
OS_SEC_BSS_SHARED UINT8 m_aucMCDynFscTest2[0x100];
OS_SEC_BSS_SHARED UINT8 m_aucFscMemTest_shared[0x100];
OS_SEC_BSS_SHARED UINT32 g_vuwMCSTATestPhase;
#endif

#if 0
//#if (OS_INCLUDE_BOX == YES)
//#if(OS_HARDWARE_PLATFORM == OS_DSP220)
OS_SEC_DATA_SHARED UINT8 m_aucMemRegionBox[OS_SYS_CORE_RUN_NUM][OS_BOX_SPACE_LENGTH]  __attribute__((aligned(128) ));/*modify by w00164922*/        /* 黑匣子空间             */
//#elif((OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC170)||(OS_HARDWARE_PLATFORM == OS_RISC220)||(OS_HARDWARE_PLATFORM == OS_HACCC))
OS_SEC_DATA_SHARED UINT8 m_aucMemRegionBox[OS_SYS_CORE_RUN_NUM][OS_BOX_SPACE_LENGTH]  __attribute__((aligned(64) ));
//#endif
//#endif
//#if (OS_TRACE_INCLUDE == YES)
OS_SEC_DATA_SHARED UINT8 m_aucTraceRegion[OS_SYS_CORE_RUN_NUM][OS_TRACE_AREA_SIZE]  __attribute__((aligned(64) ));
//#endif


OS_SEC_DATA_SHARED VOID * uwpPoolAddr[30];
OS_SEC_DATA_SHARED VOID * uwpAddr[3];
OS_SEC_BSS_SHARED UINT32 g_testHwSemCheck[OS_SYS_CORE_MAX_NUM];
OS_SEC_DATA_SHARED UINT32 m_wait1, m_wait2;//IPC核间通信功能测试，核间同步验证参数
OS_SEC_BSS UINT8 m_aucMemRegion04[OS_TSK_STACK_AREA_SIZE];
#endif

#if 0
//#if((VOS_HARDWARE_PLATFORM_PATCH == SC3400)||(VOS_HARDWARE_PLATFORM_PATCH == Xtensa) \
 //   || (VOS_HARDWARE_PLATFORM_PATCH == PAT_DSP170)||(VOS_HARDWARE_PLATFORM_PATCH == PAT_RISC170))//多核补丁LSI与Xtensa公用
OS_SEC_DATA_SHARED UINT8 m_ucMcPatchNum ;            /*补丁单个复位计数*/
OS_SEC_DATA_SHARED UINT8 m_ucResetCoreID;            /*复位核ID*/
OS_SEC_DATA_SHARED UINT32 m_ucMcPatchOPCoreID ;      /*操作核ID*/
volatile OS_SEC_DATA_SHARED UINT32 m_ulMCPatchSTSpinLock;    /* 锁 */
OS_SEC_DATA_SHARED UINT32 uwPatchCodeLenO[3];                /*补丁代码段长度*/
OS_SEC_DATA_SHARED UINT32 uwPatchSDataLenO[3];               /*补丁共享数据段段长度*/
OS_SEC_DATA_SHARED UINT32 uwPatchDataLenO[3];                /*补丁私有数据段长度*/
OS_SEC_DATA_SHARED UINT32 g_uwPatchDepOnTable[20];           /* which HP depend on */
OS_SEC_DATA_SHARED UINT32 g_uwPatchDepTables[20];            /* depend on which */
//#endif
#endif

//#ifdef CI_TEST
UINT32 g_MutileCoreSync = 0;
//#endif  /* CI_TEST */

OS_SEC_DATA_SHARED UINT32 g_irqno = 0;
OS_SEC_DATA_SHARED UINT32 g_Testspin[32] = {0};

OS_SEC_DATA_SHARED volatile UINT32 g_uwNum[OS_SYS_CORE_MAX_NUM] = {0};
OS_SEC_DATA_SHARED UINT32 m_uwMcMsgCount[OS_SYS_CORE_MAX_NUM];
OS_SEC_DATA_SHARED UINT32 auwITestMcTskID[OS_SYS_CORE_MAX_NUM];

OS_SEC_BSS_SHARED UINT32 g_ITestCheckMc;
OS_SEC_BSS_SHARED UINT32 g_auwITestCheckMc[OS_SYS_CORE_MAX_NUM];                   /*测试用辅助共享数组变量*/
OS_SEC_BSS_SHARED MSG_HANDLE_T g_uwMsgHandle, g_uwMsgHandle1, g_uwMsgHandle2;      //共享全局消息体指针
OS_SEC_BSS_SHARED OS_MEM_PT_STATE g_stMemPtState1, g_stMemPtState2;
UINT32 g_coreresetcount;
//MCSEM_HANDLE_T McSemHandle,McSemHandle0;
UINT32 uwTaskPID0,uwTaskPID1;

#if 0
OS_SEC_DATA_SHARED volatile UINT64 g_testTickCountA = 0;
OS_SEC_DATA_SHARED volatile UINT64 g_testMonitorCountA = 0;
OS_SEC_DATA_SHARED volatile UINT64 g_testTickCountB = 0;
OS_SEC_DATA_SHARED volatile UINT64 g_testMonitorCountB = 0;
OS_SEC_DATA_SHARED UINT32 g_uwShellSingleStep;

OS_SEC_DATA_SHARED UINT8 OS_GET_CLUSTER[17] = {0,0,0,0,0,1,1,1,1,1,2,2,3,3,3,3,3};
OS_SEC_BSS_SHARED UINT32 g_testMsgmDDRShare;
OS_SEC_BSS_SHARED UINT32 auwDataBss[4] __attribute__((aligned(16)));
OS_SEC_BSS_SHARED UINT32 auwDatatoHacBss[4] __attribute__((aligned(16)));

OS_SEC_DATA_SHARED UINT32 auwSwiPID_L[OS_SYS_CORE_MAX_NUM] = {0};
OS_SEC_DATA_SHARED UINT32 auwSwiPID_H[OS_SYS_CORE_MAX_NUM] = {0};
OS_SEC_DATA_SHARED UINT32 uwSwiPID_L = 0;
OS_SEC_DATA_SHARED UINT32 uwSwiPID_H = 0;
OS_SEC_DATA_SHARED UINT32 auwMemSrcBuf1[100] __attribute__((aligned(64) ));  //src buffer
OS_SEC_DATA_SHARED UINT32 auwMemDstBuf1[100] __attribute__((aligned(64) ));  //dst buffer
#endif

#if 0
OS_SEC_BSS_SHARED UINT8 g_acPatchFileBuffer[0x8000];        //定义大数组解决补丁缓冲区太小，制作的补丁加载不上去的问题
//OS_SEC_DATA_SHARED UINT8  m_ucMcPatchPt[PATCH_SHARE_NC_PT_SIZE];
//OS_SEC_DATA_SHARED PATCH_STATE  penPatchStateO[3];           //补丁状态
OS_SEC_DATA_SHARED volatile UINT32 g_uwMcPatIdleCoreNum;  //多核补丁测试用
OS_SEC_DATA_SHARED UINT32 g_uwMcPatchSynTag;              // core 0 modify the value
OS_SEC_BSS_SHARED UINT8 g_acPatchFileBuffer_toSmall[0x10];   //定义过小的补丁缓冲区，验证当补丁缓冲区过小时会有什么问题
OS_SEC_BSS_SHARED UINT8 g_acPatchFileBuffer[0x8000];         //定义大数组解决补丁缓冲区太小，制作的补丁加载不上去的问题
OS_SEC_BSS_SHARED UINT32 g_testDDRShare;
OS_SEC_BSS_SHARED UINT8 g_usTestEndFlag;
OS_SEC_BSS_SHARED SWI_HANDLE_T g_puwSwiID[OS_SWI_MAX_SUPPORT_NUM];
#endif

/*************************************     以下定义共享可cache全局变量********************************************/



//OS_SEC_BSS_SHARED UINT8 m_aucMemRegion03[OS_MEM_MCDYNAMIC_PT_SIZE] ;   /* 共享动态Pool内存分区*/
#if 0
OS_SEC_DATA_SHARED  UINT8 m_aucStaMemRegion_hc6[0x2800];
OS_SEC_DATA_SHARED  UINT8 m_aucStaMemRegion_hc9[0x2800];/*modifby by w00164922*/

OS_SEC_DATA_SHARED  UINT8 m_aucFscMemTest3[0x100];
OS_SEC_DATA_SHARED  UINT8 m_aucMCStaFscTest3[0x100];
OS_SEC_DATA_SHARED  UINT8 m_aucMCDynFscTest3[0x100];

/* 核间信号量和定时器测试用 */
OS_SEC_DATA_SHARED UINT32 McSemHandles[OS_SYS_CORE_MAX_NUM];
OS_SEC_DATA_SHARED volatile UINT32 uwOver1;
OS_SEC_DATA_SHARED TSK_HANDLE_T s_uwTaskHd2[OS_SYS_CORE_MAX_NUM];
OS_SEC_DATA_SHARED UINT64 g_testTickCount;
OS_SEC_DATA_SHARED UINT32 g_testMonitorCount;

/* The End--核间信号量和定时器测试用 */
#endif

///*__attribute__((section(".os.cache.shared.data1")))*/  OS_SEC_DATA_SHARED      UINT32 g_uwDDRExcCache[8] = {0};//DDR 自定义区域 0x5FFFFFF0 - 0x60000010
OS_SEC_DATA_SHARED      UINT32 g_uwDDRExcCache[8] = {0};//DDR 自定义区域 0x5FFFFFF0 - 0x60000010

//OS_SEC_BSS_SHARED_CACHE UINT32 g_uwPatchSharedParam;
#if 0
OS_SEC_DATA_SHARED UINT32 auwSwiPID_L[OS_SYS_CORE_MAX_NUM] = {0};
OS_SEC_DATA_SHARED UINT32 auwSwiPID_H[OS_SYS_CORE_MAX_NUM] = {0};
OS_SEC_DATA_SHARED UINT32 uwSwiPID_L = 0;
OS_SEC_DATA_SHARED UINT32 uwSwiPID_H = 0;
#endif
