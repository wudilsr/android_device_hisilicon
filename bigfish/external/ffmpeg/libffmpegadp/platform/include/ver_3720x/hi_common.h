/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_common.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/15
  Description   : Common apis for hisilicon system.
  History       :
  1.Date        : 2010/01/25
    Author      : jianglei
    Modification: Created file

*******************************************************************************/

#ifndef __HI_COMMON_H__
#define __HI_COMMON_H__

#include <hi_type.h>
#include <hi_debug.h>
#include <hi_struct.h>
#include <hi_reg.h>



/******************************* API declaration *****************************/
/** \addtogroup      H_1_1_1 */
/** @{ */  /** <!-- 【Common API. CNcomment: 通用API函数】 */

/**Defines the exit mode of FastPlay.*/
/**CNcomment: 定义FastPlay 退出模式枚举 */
typedef enum
{
    HI_UNF_PREAV_NULL = 0x000, /**<Direct exit mode (default)*/ /**< CNcomment: 默认方式,直接关闭 */
    HI_UNF_PREAV_STEP1= 0X038, /**<Gradual exit mode (step 1)*/ /**< CNcomment: 逐步关闭模式，Step1 */
    HI_UNF_PREAV_STEP2,        /**<Gradual exit mode (step 2)*/ /**< CNcomment: 逐步关闭模式，Step2 */
    HI_UNF_PREAV_STEP3,        /**<Gradual exit mode (step 3)*/ /**< CNcomment: 逐步关闭模式，Step3 */
    HI_UNF_PREAV_STEP4,        /**<Gradual exit mode (step 4)*/ /**< CNcomment: 逐步关闭模式，Step4 */
    HI_UNF_PREAV_BUTT
}HI_UNF_PREAV_E;

typedef struct
{
    HI_UNF_PREAV_E enOption;   /**<Enumeration of the exit mode of FastPlay*/ /**< CNcomment: FastPlay退出模式枚举 */
    unsigned int StepParam1;   /**<Parameter 1 of the gradual exit mode*/ /**< CNcomment: 逐步关闭模式的参数1 */
    unsigned int StepParam2;   /**<Parameter 2 of the gradual exit mode*/ /**< CNcomment: 逐步关闭模式的参数2 */
}HI_SYS_PREAV_PARAM_S;

#ifdef MMZ_V2_SUPPORT
#define SHM_WRAPPER_BY_MMZ         1
#if SHM_WRAPPER_BY_MMZ
#define SHM_COMMON_SIZE               4096
#define MAX_SHM_WRAPPER               10
#define FLFAG_SHM_WRAP_NULL        0
#define FLFAG_SHM_WRAP_USED       0x55
#define SHM_COM_HEADER_FLAG       0x5A5AA5A5  //0xA5A55A5A

typedef struct _shm_info {
      int                      pid;
      int                      shmid;
      unsigned int        shm_phy;
      int                      shm_size;
      int                      flag;
      int                      shm_cpid;       /* pid of creator */
      int                      shm_lpid;        /* pid of last shmop */
      int                      shm_nattch;	/* number of current attaches */
}shm_info;

typedef struct _shm_com_info {
      unsigned int        info_flag;
      shm_info            sShmInfo[MAX_SHM_WRAPPER];
}shm_com_info;
#endif
#endif

#ifndef __KERNEL__
#include <time.h>

/**
\brief Initializes the system. CNcomment: 系统初始化
\attention \n
You must call this API to initialize the system before using the APIs of all modules.
Though you can call other APIs successfully before calling this API, the subsequent operations may fail.
CNcomment: 在使用所有模块的接口之前都需要先调用此接口对系统进行初始化\n
在调用这个接口之前调用其他接口，不会返回失败，但是不保证执行的正确性
\param N/A CNcomment: 无
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_SYS_Init(HI_VOID);

/**
\brief Deinitializes the system. CNcomment: 系统去初始化
\attention \n
If all modules are not used, you need to call this API to deinitialize the system.
CNcomment: 所有模块都不再使用后调用此接口去初始化
\param N/A CNcomment: 无
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_SYS_DeInit(HI_VOID);

/**
\brief Gets ready for the audio/video graphic operations. CNcomment: 系统音视频图形操作前准备工作
\attention \n
If there is the startup screen or startup program, you can call this API as required to release related resources. This ensures seamless switch.
For example, the application releases the resources used by the startup screen by default after starting a graphics layer. If you call a video interface without starting any graphics layer, you are recommended to call this API.
This API can be called repeatedly. It is recommended that you call this API immediately after calling HI_SYS_Init.
CNcomment: 如果存在开机画面或开机节目的情况下，由用户根据实际情况在具体时机调用，释放相关资源，以达到无缝切换的效果
例如：正常情况下，应用程序打开图层后会默认完成开机画面所使用资源的释放;但是如果用户不进行图层打开操作而直接进行视频播放接口的调用，建议使用该接口；
建议 HI_SYS_Init 后立即调用，支持多次调用
\param[in]  pstPreParm CNcomment: 退出模式和参数结构体指针
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_SYS_PreAV(HI_SYS_PREAV_PARAM_S *pstPreParm);

/**
\brief Obtains the compiled time of a version. CNcomment: 获取版本的编译时间
\attention \n
The compiled time is the time during which the common module is made again.
CNcomment: 时间为进行common模块重新make的时间
\param[out] ptm Pointer to the compiled time of a version (output). CNcomment: 指针类型，输出版本编译的时间。
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_SYS_GetBuildTime(struct tm * ptm);

/**
\brief Obtains current play time. CNcomment:  获取当前使用播放时间
\attention \n
Use second as time count. CNcomment: 时间单位:秒
\param[out] pu32Playtime Pointer type, output current used time. CNcomment: 指针类型，输出当前消费时间。
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_SYS_GetPlayTime(HI_U32 *pu32Playtime);

/**
\brief Obtains the version number. CNcomment: 获取版本号
\attention \n
N/A CNcomment: 无
\param[out] pstVersion Pointer to the version number (output). CNcomment: 指针类型，输出版本号。
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_SYS_GetVersion(HI_SYS_VERSION_S *pstVersion);


/**
\brief Obtains the chip attributes. CNcomment: 获取芯片属性
\attention \n
N/A CNcomment: 无
\param[out] pstChipAttr Pointer to the chip attributes(output). CNcomment: 指针类型，输出芯片属性
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/

#ifndef MMZ_V2_SUPPORT
HI_S32 HI_SYS_GetChipAttr(HI_SYS_CHIP_ATTR_S *pstChipAttr);
#endif
/**
\brief Performs global system configuration. CNcomment: 设置系统的全局配置
\attention \n
N/A CNcomment: 无
\param[in] pstSysConf Pointer to the address for system configuration CNcomment: 指针类型，系统配置指针地址。
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_SYS_SetConf(const HI_SYS_CONF_S *pstSysConf);

/**
\brief Obtains global system configuration. CNcomment: 获取系统的全局配置
\attention \n
N/A CNcomment: 无
\param[out] pstSysConf Pointer to the system configuration (output). CNcomment: 指针类型，输出系统配置。
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_SYS_GetConf(HI_SYS_CONF_S *pstSysConf);

/**
\brief Sets the debugging information level of a module. CNcomment: 设置模块的调试信息级别
\attention \n
N/A CNcomment: 无
\param[in] enModId Debugging ID of a module CNcomment: 模块的调试ID。
\param[in] enLogLevel Debugging information level of a module CNcomment: 模块的调试信息级别。
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
无
*/
HI_S32 HI_SYS_SetLogLevel(HI_DEBUG_MOD_ID_E enModId,  HI_LOG_LEVEL_E enLogLevel);


/**
\brief Writes to a register or a memory. CNcomment:  写寄存器或内存
\attention \n
N/A CNcomment: 无
\param[in] u32RegAddr Physical address of a register or a memory CNcomment: 寄存器或内存的物理地址。
\param[in] u32Value Value of a register CNcomment:  寄存器的值。
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_SYS_WriteRegister(HI_U32 u32RegAddr, HI_U32 u32Value);

/**
\brief Reads a register or a memory. CNcomment: 读寄存器或内存
\attention \n
N/A CNcomment: 无
\param[in] u32RegAddr Physical address of a register or a memory CNcomment: 寄存器或内存的物理地址。
\param[out] pu32Value Pointer to the register value (output) CNcomment:  指针类型，输出寄存器的值。
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_SYS_ReadRegister(HI_U32 u32RegAddr, HI_U32 *pu32Value);


/**
\brief Applies for a media memory zone (MMZ) and maps the user-state address.
CNcomment:  申请mmz内存，并映射用户态地址
\attention \n
N/A CNcomment: 无
\param[in/out] pBuf Structure of the buffer information. Bufname and bufsize are inputs, and the physical address and user-state virtual address are outputs.
                    CNcomment: buffer信息结构，bufname和bufsize作为输入,物理地址和用户态虚拟地址作为输出
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_MMZ_Malloc(HI_MMZ_BUF_S *pBuf);

/**
\brief Unmaps the user-state address and releases the MMZ. CNcomment: 解除用户态地址的映射，并释放mmz内存
\attention \n
Ensure that the lengths of the transferred physical address and user-state virtual address are correct.
CNcomment: 保证传入的物理地址、用户态虚拟地址和长度正确
\param[in] pBuf Structure of the buffer information CNcomment: buffer信息结构
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_MMZ_Free(HI_MMZ_BUF_S *pBuf);

/**
\brief pplies for an MMZ with a specified name and obtains its physical address. CNcomment: 指定mmz的名字申请mmz内存，返回物理地址
\attention \n
N/A CNcomment: 无
\param[in] size Buffer size CNcomment: buffer大小
\param[in] align Alignment mode CNcomment: 对齐方式
\param[in] mmz_name Name of an MMZ in the buffer. If the MMZ name is set to NULL, an MMZ is anonymously applied for. CNcomment: buffer分区的名字，传入NULL匿名申请
\param[in] mmb_name Buffer name CNcomment: buffer块的名字
\retval ::NULL The application fails. CNcomment: 申请失败
\retval Physical address CNcomment: 物理地址
\see \n
N/A CNcomment: 无
*/
HI_VOID *HI_MMZ_New(HI_U32 size , HI_U32 align, HI_CHAR *mmz_name, HI_CHAR *mmb_name);

#ifdef MMZ_V2_SUPPORT
HI_VOID *HI_MMZ_New_Share(HI_U32 size , HI_U32 align, HI_CHAR *mmz_name, HI_CHAR *mmb_name);

HI_VOID *HI_MMZ_New_Shm_Com(HI_U32 size , HI_U32 align, HI_CHAR *mmz_name, HI_CHAR *mmb_name);

HI_S32 HI_MMZ_Get_Shm_Com(HI_U32 *phyaddr, HI_U32 *size);

HI_S32 HI_MMZ_Force_Delete(HI_U32 phys_addr);

HI_S32 HI_MMZ_Flush_Dirty(HI_U32 phys_addr, HI_U32 virt_addr, HI_U32 size);

HI_S32 HI_MMZ_open(HI_VOID);

HI_S32 HI_MMZ_close(HI_VOID);

#endif
/**
\brief Releases an MMZ based on its physical address. CNcomment: 通过物理地址释放mmz内存
\attention \n
N/A CNcomment: 无
\param[in] phys_addr Physical address of a buffer CNcomment: buffer物理地址
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_MMZ_Delete(HI_U32 phys_addr);

/**
\brief Maps the physical address of an MMZ applied for to a user-state virtual address. You can determine whether to cache the address.
CNcomment: 将mmz申请的物理地址映射成用户态虚拟地址，可以指定是否cached
\attention \n
N/A CNcomment: 无
\param[in] phys_addr Physical address of a buffer CNcomment: buffer物理地址
\param[in] cached Whether to cache the address. 0: no; 1: yes CNcomment: 是否使用cache，0不使用，1使用
\retval ::NULL The application fails. CNcomment: 申请失败
\retval User-state virtual address CNcomment: 用户态虚地址
\see \n
N/A CNcomment: 无
*/
HI_VOID *HI_MMZ_Map(HI_U32 phys_addr, HI_U32 cached);

/**
\brief Unmaps the user-state address of an MMZ. CNcomment: 解除mmz内存用户态地址的映射
\attention \n
N/A CNcomment: 无
\param[in] phys_addr Physical address of a buffer CNcomment: buffer物理地址
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_MMZ_Unmap(HI_U32 phys_addr);


/**
\brief Flushes D-cache to the cached MMZ. CNcomment: 对于cached类型MMZ，刷Dcache到内存
\attention \n
If the value 0 is transferred, all D-caches are refreshed; otherwise, only the transferred memory is refreshed.
CNcomment: 如果传入0，则刷新所有的Dcache；否则只刷传入的那块内存
\param[in] phys_addr Physical address of a buffer CNcomment: buffer物理地址
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_MMZ_Flush(HI_U32 phys_addr);


/**
\brief Maps a physical address to a user-state virtual address. CNcomment: 将物理地址映射成用户态虚拟地址
\attention \n
N/A CNcomment: 无
\param[in] u32PhyAddr Physical address of a buffer CNcomment: buffer物理地址
\param[in] u32Size Buffer size CNcomment: buffer的大小
\retval ::NULL The application fails. CNcomment: 申请失败
\retval User-state virtual address CNcomment: 用户态虚地址
\see \n
N/A CNcomment: 无
*/
HI_VOID *HI_MEM_Map(HI_U32 u32PhyAddr, HI_U32 u32Size);


/**
\brief Unmaps a user-state address. CNcomment: 解除用户态地址的映射
\attention \n
N/A CNcomment: 无
\param[in] pAddrMapped User-state virtual address of a buffer. CNcomment: buffer的用户态虚地址
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_MEM_Unmap(HI_VOID *pAddrMapped);

/**
\brief Obtains the physical address and size based on the virtual address. CNcomment: 根据虚拟地址获取物理地址，以及大小
\attention \n
N/A CNcomment: 无
\param[in] pVir User-state virtual address CNcomment: 用户态虚地址
\param[out] pu32Phyaddr Physical address  CNcomment: 物理地址
\param[out] pu32Size Size CNcomment: 大小
\retval ::HI_SUCCESS Success CNcomment: 成功
\retval ::HI_FAILURE Calling this API fails. CNcomment: API系统调用失败
\see \n
N/A CNcomment: 无
*/
HI_S32 HI_MMZ_GetPhyaddr(HI_VOID * pVir, HI_U32 *pu32Phyaddr, HI_U32 *pu32Size);


/** @} */  /** <!-- ==== Structure Definition end ==== */

#endif
#endif /* __HI_COMMON_H__ */
