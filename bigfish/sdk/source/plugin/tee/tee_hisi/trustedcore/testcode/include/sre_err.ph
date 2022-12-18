/**
 * @file sre_err.ph
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：错误处理内部头文件。 \n
 */

#ifndef _SRE_ERR_PH
#define _SRE_ERR_PH

#include "sre_err.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


//防止literal与代码都配置在L1时，CDA工具检测时出现两个同值的魔术字,CDA工具端检测的魔术字为0xa53ce169
#define OS_CDA_MAGIC_WORD           0xa53ce168
#define OS_CDA_VERSION              0x00010700

//异常解析时，用于区分SD6108/SD6181与SD6182
#define OS_CDA_CPU_TYPE_0881        0x10101010
#define OS_CDA_CPU_TYPE_82          0x20202020

/* 用户错误处理的结构体 */
typedef struct tagUserErrFunc_S
{
    SRE_ERRORHANDLE_FUNC  pfnHook;  /* 用户钩子函数 */
} USER_ERR_FUNC_S;

#define OS_ERR_RECORD_N        3   //表示保留二进制低n位，计算OS_ERR_RECORD_NUM用，OS_ERR_RECORD_NUM为2的n次方+1

#define OS_ERR_RECORD_NUM      ((1 << OS_ERR_RECORD_N) + 1) //2的n次方+1，目前n取3，NUM为9，第一次错误固定记录，后面8个循环记录。

/*上报的错误信息结构体*/
typedef struct tagErrInfo_S
{
    UINT32    uwTickCnt;
    UINT32    uwErrorNo;
} ERR_INFO_S;

/**
 * @ingroup SRE_cda
 * CDA内存信息结构体,注意同步更新测试代码中的结构体TST_CDA_INFO_S
 */
typedef struct tagCdaInfo
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
    UINT16 usSemNum;                            /**< 核内信号量个数                         */
    UINT16 usMcSemNum;                          /**< 核间信号量个数                         */
    UINT16 usTaskMaxNum;                        /**< 系统支持的最大任务个数                 */
    UINT16 usSwiMaxNum;                         /**< 系统支持的最大软中断个数               */
    UINT16 usSwtmrMaxNum;                       /**< 软件定时器最大个数                     */
    UINT16 usHwtmrMaxNum;                       /**< 硬件定时器最大个数                     */
    UINT32 uwTickPerSecond;                     /**< 每秒钟TICK数                           */
    UINT32 uwSwtmrStartAddr;                    /**< 内存中软件定时器控制块起始地址         */
    UINT32 uwHwtmrCBAddr;                       /**< 硬件定时器控制块地址                   */
    UINT32 uwBWPManageInfoAddr;                 /**< 断点管理信息起始地址                   */
    UINT32 uwCpProFlag;                         /**< 矢量寄存器功能是否打开标志             */
    UINT32 uwRecordIndex;                       /**< 系统记录错误信息索引号                 */
    ERR_INFO_S astErrInfo[OS_ERR_RECORD_NUM];   /**< 系统记录错误信息                       */
    UINT8  ucExcFlag;                           /**< 系统发生异常时记录的异常标志位         */
    UINT8  ucCoreID;                            /**< 当前运行核号                           */
    UINT8  ucPlatform;                          /**< 芯片类型                               */
    UINT8  ucCPUID;                             /**< CPU型号                                */
    UINT16 usOptPtNum;                          /**< os缺省创建了几个分区                   */
    UINT16 usMaxPtNum;                          /**< 当前实际创建分区总个数                 */
    UINT32 uwExcBufAddr;                        /**< 异常信息首地址                         */
    UINT32 uwMsgmNorProfStartAddr;              /**< MSGM正常队列profiling缓冲区首地址      */
    UINT16 usMsgmProfQPortMsgNum[3];            /**< MSGM每个QPORT profiling实际消息数      */
    UINT8  ucMsgmProfQPort0Type;                /**< MSGM 0号QPORT OS或用户类型消息标志     */
    UINT8  ucPreserved;                         /**< 预留字节                               */
    UINT16 usLHwSemNum;                         /**< HWSEM 局部硬件信号量个数               */
    UINT16 usGHwSemNum;                         /**< HWSEM 全局硬件信号量个数               */
    UINT32 uwHwSemStartAddr;                    /**< HWSEM 控制块起始地址                   */
    UINT32 uwHwiFormAddr;                       /**< 硬中断处理函数数组的首地址             */
    UINT32 uwHwiModeFormAddr;                   /**< 硬中断工作模式数组的首地址             */
    UINT32 uwHwiDefault;                        /**< 硬中断默认处理函数的地址               */
    UINT32 uwUniFlagAddr;                       /**< UniDSP系统状态地址                     */
    UINT32 uwTaskLockAddr;                      /**< 任务锁的地址                           */
    UINT32 uwIntCountAddr;                      /**< Hwi中断嵌套计数的地址                  */
    UINT32 uwExcNestCntAddr;                    /**< 异常嵌套计数的地址                     */
    UINT32 uwTskModInfoAddr;                    /**< 任务模块注册信息首地址                 */
    UINT32 uwTraceModAddr;                      /**< 系统跟踪模块起始地址                   */
    UINT32 uwHuntBufAddr;                       /**< HUNT模块起始地址                       */
    UINT32 uwSysStackBottom;                    /**< 系统栈栈底地址                         */
    UINT32 uwSysStackTop;                       /**< 系统栈栈顶地址                         */
    UINT32 uwHwiNestAddr;                       /**< 存储硬中断嵌套关系的地址               */
    UINT32 uwExcRegsAddr;                       /**< 保存异常上下文地址                     */
    UINT32 uwOsVerAddr;                         /**< OS版本号首地址                         */
    UINT32 uwCdaVersion;                        /**< CDA版本号                              */
    CDA_PT_INFO_S astPtInfo[1];                 /**< 各内存分区信息                         */
} CDA_INFO_S;

#define OS_ERR_MAGIC_WORD           0xa1b2c3f8

#define OS_REPORT_ERROR(uwErrNo)  \
    do \
    { \
        (VOID)SRE_ErrHandle("os_unspecific_file", OS_ERR_MAGIC_WORD, uwErrNo, 0, NULL); \
    } while (0)

#define OS_REPORT_ERROR_P2(uwErrLine, uwErrNo)  \
    do \
    { \
        (VOID)SRE_ErrHandle("os_unspecific_file", uwErrLine, uwErrNo, 0, NULL); \
    } while (0)

#define OS_RETURN_ERROR(uwErrNo) \
    do \
    {\
        (VOID)SRE_ErrHandle("os_unspecific_file", OS_ERR_MAGIC_WORD, uwErrNo, 0, NULL); \
        \
        return uwErrNo; \
    } while (0)

#define OS_RETURN_ERROR_P2(uwErrLine, uwErrNo) \
    do \
    {\
        (VOID)SRE_ErrHandle("os_unspecific_file", uwErrLine, uwErrNo, 0, NULL); \
        \
        return uwErrNo; \
    }while(0)

#define OS_GOTO_ERR_HANDLER(uwErrorNo) \
    do \
    { \
        uwErrNo    = uwErrorNo; \
        uwErrLine  = OS_ERR_MAGIC_WORD; \
        goto ErrHandler; \
    }while(0)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_ERR_PH */

/*
 * History: \n
 * 2009-3-13, l00133294, Create this file. \n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
