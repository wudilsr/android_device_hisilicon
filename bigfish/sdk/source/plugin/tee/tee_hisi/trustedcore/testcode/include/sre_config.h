/**
* @file sre_config.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：UniDSP配置头文件，裁剪开关和配置项。 \n
*/

#ifndef _SRE_CONFIG_H
#define _SRE_CONFIG_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/****************************** 配置系统基本信息 ****************************/
#define OS_SYS_CLOCK                                    361000000               // 芯片主频
#define OS_SYS_CORE_RUN_NUM                             1               // 实际运行的核数,单位：个
#define OS_SYS_CORE_MAX_NUM                             1               // 最大支持的核数,单位：个
#define OS_SYS_CORE_START                               0               // 运行UniDSP多核系统的核号起点
#define OS_SYS_CORE_MASTER                              0               // 主核ID
#define OS_SYS_CORE_SMP_MASK                            0x0
#define OS_SYS_REBOOT_HOOK                              NULL            // 用户挂接的单板复位函数
#define OS_PERI_ERR_HDL_CORE                            12              // 外设异常接管核ID，只对82有效

/****************************** 配置定时器模块 ******************************/
#define OS_INCLUDE_HW_TIMER                             YES             // 硬件定时器模块裁剪开关

/****************************** 配置Tick中断模块 ****************************/
#define OS_INCLUDE_TICK                                 NO             // Tick中断模块裁剪开关
#define OS_TICK_PER_SECOND                              5000            // Tick中断时间单隔

/****************************** 配置软中断模块 ******************************/
#define OS_INCLUDE_SWI                                  YES             // 软中断模块裁剪开关
#define OS_INCLUDE_MCSWI                                NO             // 核间软中断裁剪开关
#define OS_SWI_MAX_SUPPORT_NUM                         16              // 最大支持的软中断个数,最大可配置值为125

/****************************** 配置任务模块 ********************************/
#define OS_INCLUDE_TASK                                 YES             // 任务模块裁剪开关
#define OS_TSK_MAX_SUPPORT_NUM                          8               // 最大支持的任务数
#define OS_TSK_DEFAULT_STACK_SIZE                       0x400           // 缺省的任务栈大小
#define OS_TSK_IDLE_STACK_SIZE                          0x400           // IDLE任务栈的大小
#define OS_TSK_STACK_AREA_START_ADDR                    NULL            // 任务栈区间起始地址。
#define OS_TSK_STACK_AREA_SIZE                          1024               // 任务栈区间大小
#define OS_TSK_IDLE_HOOK                                NULL            // IDLE任务或软中断的注册钩子

/****************************** 配置任务监控模块 ***************************/
#define OS_INCLUDE_TSKMON                               NO              // 任务(栈)监控模块裁剪开关
#define OS_TSKMON_OVERRUN                               NO              // 任务撑死检测裁剪开关
#define OS_TSKMON_OVERRUN_THRESHOLD                     20              // 任务撑死阀值
#define OS_TSKMON_DOMODE                                NO              // 任务死循环处理方式
#define OS_TSKMON_STARVATION                            NO              // 任务饿死检测裁剪开关
#define OS_TSKMON_STARVATION_THRESHOLD                  400             // 任务饿死阀值

/****************************** 配置任务栈越界检测模块 *********************/
#define OS_INCLUDE_TSKSTACKMON                          NO              // 任务栈越界检测裁剪开关

/****************************** 配置异常管理模块 ***************************/
#define OS_INCLUDE_EXCEPTION                            NO             // 异常模块裁剪开关
#define OS_EXC_STACK_SIZE                               512             // 保存的任务栈大小
#define OS_EXC_PROC_HOOK                                NULL            // 异常信息记录后，复位前调用
#define OS_DOUBLE_EXC_STACK_START                       NULL            // DoubleException堆栈起始地址

/****************************** 配置CPU占用率及CPU告警模块 *****************/
#define OS_INCLUDE_CPUP                                 NO              // CPU占用率模块裁剪开关
#define OS_CPUP_SAMPLE_RECORD_NUM                       10              // CPU采样样本的最大个数
#define OS_CPUP_SAMPLE_INTERVAL                         10              // 采样时间间隔(单位tick)
#define OS_CPUP_WARN                                    NO              // CPU占用率告警裁剪开关
#define OS_CPUP_SHORT_WARN                              80              // CPU占用率告警阈值(百分比)
#define OS_CPUP_SHORT_RESUME                            75              // CPU占用率告警恢复阈值(百分比)

/****************************** 配置黑匣子模块 *****************************/
#define OS_INCLUDE_BOX                                  NO             // 黑匣子模块裁剪开关
#define OS_BOX_SPACE_START_ADDR                         &m_aucMemRegionBox[0][0]            // 黑匣子空间起始地址
#define OS_BOX_SPACE_LENGTH                             0xB400          // 黑匣子空间长度
#define OS_BOX_REGION_INIT_NUM                          40              // 黑匣子单元最大个数
#define OS_BOX_CLEANALL                                 NO             // 重启后清空黑匣子空间

/****************************** 配置内存管理模块 ***************************/
#define OS_MEM_MAX_PT_NUM                               20              // 可以创建分区的最大数量，最大可以配置20个分区

#define OS_MEM_ALGORITHM_MCDYNFSC                       NO             // 支持共享动态FSC内存算法
#define OS_MEM_ALGORITHM_POOL                           YES             // 支持私有Pool内存算法
#define OS_MEM_ALGORITHM_MCPOOL                         NO             // 支持共享Pool内存算法

#define OS_MEM_FSC_PT_ADDR                              &m_aucMemRegion00[0]            // 私有FSC内存分区起始地址
#ifdef STB_CIPHER_DRIVER
#define OS_MEM_FSC_PT_SIZE                              0x00020000               // 私有FSC内存分区大小
#else
#define OS_MEM_FSC_PT_SIZE                              0x00008000               // 私有FSC内存分区大小
#endif

/****************************** 配置信号量管理模块 **************************/
#define OS_INCLUDE_SEM                                  YES              // 信号量模块裁剪开关
#define OS_SEM_MAX_SUPPORT_NUM                          8               // 最大支持的信号量数

/****************************** 配置核间信号量模块 **************************/
#define OS_INCLUDE_MCSEM                                NO              // 核间信号量模块裁剪开关
#define OS_MCSEM_MAX_SUPPORT_NUM                        10               // 最大支持的核间信号量数

/****************************** 配置核间快速信号量 ***************************/
#define OS_INCLUDE_MCFSEM                               NO              // 核间快速信号模块裁剪开关

/****************************** 配置消息管理模块 *****************************/
#define OS_INCLUDE_MSG                                  YES              // 消息模块裁剪开关
#define OS_INCLUDE_MCMSG                                NO              // 核间消息模块裁剪开关
#define OS_MSG_MAX_SUPPORT_NUM                          8               // 最大支持的消息结点个数

/****************************** 配置多核通信模块 *****************************/
#define OS_INCLUDE_SYNC                                 NO             // 核间同步功能剪裁开关

/****************************** 配置硬件信号量模块 ***************************/
#define OS_HWSEM_GLOBE_NUM                              0               // 全局硬件信号量个数，存在配置限制说明，请参见手册。
#define OS_HWSEM_LOCAL_NUM                              0               // 局部硬件信号量个数(每个簇内的个数)，存在配置限制说明，请参见手册。

/****************************** 配置系统跟踪模块 *****************************/
#define OS_TRACE_INCLUDE                                NO              // 系统跟踪模块剪裁开关，若配置为YES且使能了硬中断/软中断/任务的系统跟踪，将会降低系统调度的性能
#define OS_TRACE_AREA_ADDR                              NULL            // 系统跟踪空间起始地址, 按16字节对齐
#define OS_TRACE_AREA_SIZE                              0x410           // 系统跟踪空间大小,含控制头(16字节),扣除控制头大小应为2的N次幂且不小于16
#define OS_TRACE_STUB_NUM                               10              // 最大允许同时监控软中断总数

/****************************** 配置驱动模块 ********************************/
#define  OS_INCLUDE_DEVICE                              NO

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_CONFIG_H */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

