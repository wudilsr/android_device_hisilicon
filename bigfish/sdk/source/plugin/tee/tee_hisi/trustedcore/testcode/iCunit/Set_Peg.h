#ifndef _SET_PEG_H
#define _SET_PEG_H

#include "sre_base.h"
#include "sre_typedef.h"
#include "sre_task.h"
#include "sre_err.h"
#include "sre_exc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#if ((OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC170)|| (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220))
#define OS_EMBED_ASM                    __asm__ __volatile__
#define OS_FLG_HWI_ACTIVE               0x0001
extern  UINT32 g_uwExcPC;
#endif

#define EXC_CSTK_DEAPTH             10
#ifdef COMPOSE_PID
#undef COMPOSE_PID
#endif

#define COMPOSE_PID(coreid, handle)   ((((UINT32)(coreid))<<8) + ((UINT8)(handle))) /* 将coreid与handle组成PID,UIPC不使用该接口 */

#define OS_ERR_RECORD_NUM      9   //1+8，第一次错误固定记录，后面8个循环记录。

/*上报的错误信息结构体*/
typedef struct tagErrInfo_PEG_S
{
    UINT32    uwTickCnt;
    UINT32    uwErrorNo;
} ERR_INFO_PEG_S;

/**
 * @ingroup SRE_cda
 * 测试用CDA内存信息结构体, 注意与源码的结构体CDA_INFO_S保持一致
 */
typedef struct tagTestCdaInfo
{
    UINT32 uwMagicWord;                         /**< CDA结构信息魔术字                      */
    UINT32 uwTCBStartAddr;                      /**< 内存中任务控制块起始地址               */
    UINT32 uwSCBStartAddr;                      /**< 内存中软中断控制块起始地址             */
    UINT32 uwMailBufAddr;                       /**< 邮箱缓存块起始地址                     */
    UINT32 uwMsgStartAddr;                      /**< 核内消息节点链表起始地址               */
    UINT32 uwMcMsgStartAddr;                    /**< 核间消息节点链表起始地址               */
    UINT32 uwSemStartAddr;                      /**< 核内信号量节点链表起始地址             */
    UINT32 uwMcSemStartAddr;                    /**< 核间信号量节点链表起始地址             */
    UINT32 uwMsgNum;                            /**< 核内消息个数                           */
//  UINT32 uwMcMsgNum;                          /**< 核间消息个数                           */
    UINT16 uwSemNum;                            /**< 核内信号量个数                         */
    UINT16 uwMcSemNum;                          /**< 核间信号量个数                         */
    UINT16 uwTaskMaxNum;                        /**< 系统支持的最大任务个数                 */
    UINT16 uwSwiMaxNum;                         /**< 系统支持的最大软中断个数               */
    UINT32 uwRecordIndex;                       /**< 系统记录错误信息索引号                 */
    ERR_INFO_PEG_S astErrInfo[OS_ERR_RECORD_NUM]; /**< 系统记录错误信息                     */
    UINT8  uwExcFlag;                           /**< 系统发生异常时记录的异常标志位         */
    UINT8  uwCoreID;                            /**< 当前运行核号                           */
    UINT8  uwPlatform;                          /**< 芯片类型                               */
    UINT8  uwCPUID;                             /**< CPU型号                                */
    UINT16 ucOptPtNum;                          /**< os缺省创建了几个分区                   */
    UINT16 ucMaxPtNum;                          /**< 当前实际创建分区总个数                 */
    UINT32 uwExcBufAddr;                        /**< 异常信息首地址                         */
    UINT32 uwMsgmNorProfStartAddr;              /**< MSGM正常队列profiling缓冲区首地址      */
    UINT16 usMsgmProfQPortMsgNum[4];            /**< MSGM每个QPORT profiling实际消息数      */
    UINT32 uwHwiFormAddr;                       /**< 硬中断处理函数数组的首地址             */
    UINT32 uwHwiDefault;                        /**< 硬中断默认处理函数的地址               */
    UINT32 uwUniFlagAddr;                       /**< UniDSP系统状态地址                     */
    UINT32 uwTaskLockAddr;                      /**< 任务锁的地址                           */
    UINT32 uwIntCountAddr;                      /**< Hwi中断嵌套计数的地址                  */
    UINT32 uwExcNestCntAddr;                    /**<异常嵌套计数的地址                      */
    UINT32 uwTskModInfoAddr;                    /**< 任务模块注册信息首地址                 */
    UINT32 uwTraceModAddr;                      /**< 系统跟踪模块起始地址                   */
    UINT32 uwHuntBufAddr;                       /**< HUNT模块起始地址                       */
    UINT32 uwSysStackBottom;                    /**< 系统栈栈底地址                         */
    UINT32 uwSysStackTop;                       /**< 系统栈栈顶地址                         */
    UINT32 uwHwiNestAddr;                       /**< 存储硬中断嵌套关系的地址               */
#if((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170)|| (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220))
    UINT32 uwIpcHuntNodeAddr;                   /**< 实例结点的首地址                       */
    UINT32 uwIpcLaPcbExAddr;                    /**< 本地实例控制块的首地址                 */
    UINT32 uwIpcRmtPcbExAddr;                   /**< 远端影子实例控制块的首地址             */
    UINT32 uwIpcConnArrayAddr;                  /**< CM层链路控制数据首地址*/
    UINT32 uwIpcConnExtArrayAddr;               /**< CM层链路扩展控制数据的首地址           */
    UINT32 uwIpcLinxStartAddr;                  /**< 链路控制块的首地址                     */
    UINT32 uwLmPidMaxNumAddr;                   /**< 系统支持的最大实例数                   */
    UINT32 uwLmHuntPendAddr;                    /**< Hunt过程线程请求链表首地址             */
#endif
    UINT32 uwOsVerAddr;                         /**< OS版本号首地址                         */
    UINT32 uwCdaVersion;                        /**< CDA版本号                              */
    CDA_PT_INFO_S astPtInfo[1];                 /**< 各内存分区信息                         */
} TST_CDA_INFO_S;


#if ((OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC170)|| (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
#define GET_PS_A1   \
do{                 \
    OS_EMBED_ASM("  rsr    %0, ps; rsync" : "=a" (uwPS) ); \
    OS_EMBED_ASM("  mov    %0, a1" : "=a" (uwA1) );        \
}while(0)

/*
 *异常时记录的ipc邮箱信息，注意与源码中的结构体IPC_STATUS_S保持一致
 */
typedef struct tagTstIpcStatus
{
    UINT32 vuwSrc;
    UINT32 vuwData[2];
}TST_IPC_STATUS_S;

/*
 *用户可以看到异常信息
 *
 *异常信息结构体，注意与源码中的结构体EXC_INFO_S保持一致
 */
typedef struct tagTstExcInfo
{
    CHAR                acOSVer[40];                         /* OS版本号       */
    CHAR                acAppVer[40];                        /* 产品版本号     */
    CHAR                acTaskName[OS_TSK_NAME_LEN];         /* 任务名         */
    CHAR                acSwiName[OS_TSK_NAME_LEN];          /* 软中断名       */
    UINT16              usByteOrder;                         /* 字节序         */
    UINT16              usCpuType;                           /* CPU类型        */
    UINT32              uwCpuID;                             /* CPU ID         */
    CPU_TICK            stCpuTick;                           /* CPU Tick       */
    UINT32              uwTaskID;                            /* 任务PID        */
    UINT32              uwSwiID;                             /* 软中断PID      */
    EXC_REGS_S          stRegInfo;                           /* 寄存器信息     */
    UINT32              uwThread;                            /* 异常前的线程类型 */
    CSTK_FRAME_INFO_S   astStackLayer[EXC_CSTK_DEAPTH];      /* 调用栈解析结果 */
    UINT32              uwBasicMagic;                        /* EXC_VALID      */
    UINT32              uwState;                             /* 异常状态标志位 */
    TST_IPC_STATUS_S    auwIpcStatus[8];                     /* ipc邮箱状态，每个核只有8个mailbox*/
    UINT32              uwStackBegin;                        /* 异常前栈内容起始地址       */
    UINT32              uwStackSize;                         /* 保存的异常前的栈大小*/
    UINT8               aucStackContent[4];                  /* 异常前的栈内容*/
} TST_EXC_INFO_S;
#endif

#if(OS_HARDWARE_PLATFORM == OS_SC3400)
typedef struct tagStPegJMP
{
    UINT16 pat1 : 3;
    UINT16 a1   : 2;
    UINT16 A1   : 3;
    UINT16 pat2 : 8;
    UINT16 A2   : 13;
    UINT16 pat3 : 3;
    UINT16 a2   : 14;
    UINT16 pat4 : 2;
}SETPEG_JMP_ST;

typedef struct tagSETPEG_OFFSET
{
    UINT16 A2   : 13;
    UINT16 A1   : 3;
    UINT16 a2   : 14;
    UINT16 a1   : 2;
}SETPEG_JMP_OFFSET_ST;
#elif(OS_HARDWARE_PLATFORM == OS_SC3850)
typedef struct tagStPegJMP
{
    UINT16 pat2 : 8;
    UINT16 A1   : 3;
    UINT16 a1   : 2;
    UINT16 pat1 : 3;

    UINT16 pat3 : 3;
    UINT16 A2   : 13;

    UINT16 pat4 : 2;
    UINT16 a2   : 14;
}SETPEG_JMP_ST;

typedef struct tagSETPEG_OFFSET
{
    UINT32 a1   : 2;
    UINT32 a2   : 14;
    UINT32 A1   : 3;
    UINT32 A2   : 13;
}SETPEG_JMP_OFFSET_ST;
#elif(OS_HARDWARE_PLATFORM == OS_C64XPLUS)
typedef struct tagStPegJMP
{
    UINT32 auwInc[10];
}SETPEG_JMP_ST;
#elif ((OS_HARDWARE_PLATFORM == OS_XTENSA2) || (OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC170)\
		||(OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220)\
		||(OS_HARDWARE_PLATFORM == OS_HACCC))

typedef struct tagStPegJMP
{
    UINT8  uJmpP1;                      /* 函数头填充的jump指令域       */
    UINT8  uJmpP2;
    UINT8  uJmpP3;
    UINT8  ucReserved;                  /* 保留字                       */
    UINT32 ulNewAddr;                   /* 存放新函数地址               */
    UINT8  uL32rP1;                     /* 读取补丁函数地址的指令域     */
    UINT8  uL32rP2;
    UINT8  uL32rP3;
    UINT8  uJmpXp1;                     /* 跳转到补丁函数地址的指令域   */
    UINT8  uJmpXp2;
    UINT8  uJmpXp3;
    UINT8  uNopN1;                      /* nop                          */
    UINT8  uNopN2;                      /* nop                          */
}SETPEG_JMP_ST;
#elif (OS_HARDWARE_PLATFORM == OS_CORTEX_A9)
typedef struct tagStPegJMP
{
	UINT32 reserved;
}SETPEG_JMP_ST;
#endif

extern UINT32 ExcInfoCheckHook(UINT32 uwPC, UINT32 uwA1, UINT32 uwThreadType, UINT32 uwExcType);

typedef UINT32 (*REBOOT_HOOK)(UINT32 uwPara1, UINT32 uwPara2, UINT32 uwPara3, UINT32 uwPara4);

extern UINT32 TEST_RebootHookAdd(REBOOT_HOOK pfnHook, UINT32 uwPara1, UINT32 uwPara2, UINT32 uwPara3, UINT32 uwPara4);

extern UINT32 SET_PEG(VOID *pOldFunc, VOID *pNewFunc, SETPEG_JMP_ST *pstIncSave);

extern UINT32 CLEAN_PEG(VOID *pOldFunc, SETPEG_JMP_ST stIncSave);

extern UINT32 SRE_ErrHandle_Stub(CHAR *pcFileName,
                                UINT32 uwLineNo,
                                UINT32 uwErrorNo,
                                UINT32 uwParaLen,
                                VOID  *pPara );

extern VOID osSpinOnHwSemInt_Stub(UINT16 usHwSemId);
extern VOID osSpinOnHwSemInt(UINT16 usHwSemId);
extern VOID SRE_HwSemPend_Stub(UINT16 usHwSemId);
extern VOID SRE_HwSemPost_Stub(UINT16 usHwSemId);
extern UINT32 SRE_HwSemIrqPend_Stub(UINT16 usHwSemId);
extern VOID SRE_HwSemIrqPost_Stub(UINT16 usHwSemId, UINT32 uwIntSave);
extern VOID SRE_Reboot_Stub(VOID);
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SET_PEG_H */


