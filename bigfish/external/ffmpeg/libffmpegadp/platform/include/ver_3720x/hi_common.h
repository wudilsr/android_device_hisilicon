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
/** @{ */  /** <!-- ��Common API. CNcomment: ͨ��API������ */

/**Defines the exit mode of FastPlay.*/
/**CNcomment: ����FastPlay �˳�ģʽö�� */
typedef enum
{
    HI_UNF_PREAV_NULL = 0x000, /**<Direct exit mode (default)*/ /**< CNcomment: Ĭ�Ϸ�ʽ,ֱ�ӹر� */
    HI_UNF_PREAV_STEP1= 0X038, /**<Gradual exit mode (step 1)*/ /**< CNcomment: �𲽹ر�ģʽ��Step1 */
    HI_UNF_PREAV_STEP2,        /**<Gradual exit mode (step 2)*/ /**< CNcomment: �𲽹ر�ģʽ��Step2 */
    HI_UNF_PREAV_STEP3,        /**<Gradual exit mode (step 3)*/ /**< CNcomment: �𲽹ر�ģʽ��Step3 */
    HI_UNF_PREAV_STEP4,        /**<Gradual exit mode (step 4)*/ /**< CNcomment: �𲽹ر�ģʽ��Step4 */
    HI_UNF_PREAV_BUTT
}HI_UNF_PREAV_E;

typedef struct
{
    HI_UNF_PREAV_E enOption;   /**<Enumeration of the exit mode of FastPlay*/ /**< CNcomment: FastPlay�˳�ģʽö�� */
    unsigned int StepParam1;   /**<Parameter 1 of the gradual exit mode*/ /**< CNcomment: �𲽹ر�ģʽ�Ĳ���1 */
    unsigned int StepParam2;   /**<Parameter 2 of the gradual exit mode*/ /**< CNcomment: �𲽹ر�ģʽ�Ĳ���2 */
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
\brief Initializes the system. CNcomment: ϵͳ��ʼ��
\attention \n
You must call this API to initialize the system before using the APIs of all modules.
Though you can call other APIs successfully before calling this API, the subsequent operations may fail.
CNcomment: ��ʹ������ģ��Ľӿ�֮ǰ����Ҫ�ȵ��ô˽ӿڶ�ϵͳ���г�ʼ��\n
�ڵ�������ӿ�֮ǰ���������ӿڣ����᷵��ʧ�ܣ����ǲ���ִ֤�е���ȷ��
\param N/A CNcomment: ��
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_SYS_Init(HI_VOID);

/**
\brief Deinitializes the system. CNcomment: ϵͳȥ��ʼ��
\attention \n
If all modules are not used, you need to call this API to deinitialize the system.
CNcomment: ����ģ�鶼����ʹ�ú���ô˽ӿ�ȥ��ʼ��
\param N/A CNcomment: ��
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_SYS_DeInit(HI_VOID);

/**
\brief Gets ready for the audio/video graphic operations. CNcomment: ϵͳ����Ƶͼ�β���ǰ׼������
\attention \n
If there is the startup screen or startup program, you can call this API as required to release related resources. This ensures seamless switch.
For example, the application releases the resources used by the startup screen by default after starting a graphics layer. If you call a video interface without starting any graphics layer, you are recommended to call this API.
This API can be called repeatedly. It is recommended that you call this API immediately after calling HI_SYS_Init.
CNcomment: ������ڿ�������򿪻���Ŀ������£����û�����ʵ������ھ���ʱ�����ã��ͷ������Դ���Դﵽ�޷��л���Ч��
���磺��������£�Ӧ�ó����ͼ����Ĭ����ɿ���������ʹ����Դ���ͷ�;��������û�������ͼ��򿪲�����ֱ�ӽ�����Ƶ���Žӿڵĵ��ã�����ʹ�øýӿڣ�
���� HI_SYS_Init ���������ã�֧�ֶ�ε���
\param[in]  pstPreParm CNcomment: �˳�ģʽ�Ͳ����ṹ��ָ��
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_SYS_PreAV(HI_SYS_PREAV_PARAM_S *pstPreParm);

/**
\brief Obtains the compiled time of a version. CNcomment: ��ȡ�汾�ı���ʱ��
\attention \n
The compiled time is the time during which the common module is made again.
CNcomment: ʱ��Ϊ����commonģ������make��ʱ��
\param[out] ptm Pointer to the compiled time of a version (output). CNcomment: ָ�����ͣ�����汾�����ʱ�䡣
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_SYS_GetBuildTime(struct tm * ptm);

/**
\brief Obtains current play time. CNcomment:  ��ȡ��ǰʹ�ò���ʱ��
\attention \n
Use second as time count. CNcomment: ʱ�䵥λ:��
\param[out] pu32Playtime Pointer type, output current used time. CNcomment: ָ�����ͣ������ǰ����ʱ�䡣
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_SYS_GetPlayTime(HI_U32 *pu32Playtime);

/**
\brief Obtains the version number. CNcomment: ��ȡ�汾��
\attention \n
N/A CNcomment: ��
\param[out] pstVersion Pointer to the version number (output). CNcomment: ָ�����ͣ�����汾�š�
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_SYS_GetVersion(HI_SYS_VERSION_S *pstVersion);


/**
\brief Obtains the chip attributes. CNcomment: ��ȡоƬ����
\attention \n
N/A CNcomment: ��
\param[out] pstChipAttr Pointer to the chip attributes(output). CNcomment: ָ�����ͣ����оƬ����
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/

#ifndef MMZ_V2_SUPPORT
HI_S32 HI_SYS_GetChipAttr(HI_SYS_CHIP_ATTR_S *pstChipAttr);
#endif
/**
\brief Performs global system configuration. CNcomment: ����ϵͳ��ȫ������
\attention \n
N/A CNcomment: ��
\param[in] pstSysConf Pointer to the address for system configuration CNcomment: ָ�����ͣ�ϵͳ����ָ���ַ��
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_SYS_SetConf(const HI_SYS_CONF_S *pstSysConf);

/**
\brief Obtains global system configuration. CNcomment: ��ȡϵͳ��ȫ������
\attention \n
N/A CNcomment: ��
\param[out] pstSysConf Pointer to the system configuration (output). CNcomment: ָ�����ͣ����ϵͳ���á�
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_SYS_GetConf(HI_SYS_CONF_S *pstSysConf);

/**
\brief Sets the debugging information level of a module. CNcomment: ����ģ��ĵ�����Ϣ����
\attention \n
N/A CNcomment: ��
\param[in] enModId Debugging ID of a module CNcomment: ģ��ĵ���ID��
\param[in] enLogLevel Debugging information level of a module CNcomment: ģ��ĵ�����Ϣ����
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_SYS_SetLogLevel(HI_DEBUG_MOD_ID_E enModId,  HI_LOG_LEVEL_E enLogLevel);


/**
\brief Writes to a register or a memory. CNcomment:  д�Ĵ������ڴ�
\attention \n
N/A CNcomment: ��
\param[in] u32RegAddr Physical address of a register or a memory CNcomment: �Ĵ������ڴ�������ַ��
\param[in] u32Value Value of a register CNcomment:  �Ĵ�����ֵ��
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_SYS_WriteRegister(HI_U32 u32RegAddr, HI_U32 u32Value);

/**
\brief Reads a register or a memory. CNcomment: ���Ĵ������ڴ�
\attention \n
N/A CNcomment: ��
\param[in] u32RegAddr Physical address of a register or a memory CNcomment: �Ĵ������ڴ�������ַ��
\param[out] pu32Value Pointer to the register value (output) CNcomment:  ָ�����ͣ�����Ĵ�����ֵ��
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_SYS_ReadRegister(HI_U32 u32RegAddr, HI_U32 *pu32Value);


/**
\brief Applies for a media memory zone (MMZ) and maps the user-state address.
CNcomment:  ����mmz�ڴ棬��ӳ���û�̬��ַ
\attention \n
N/A CNcomment: ��
\param[in/out] pBuf Structure of the buffer information. Bufname and bufsize are inputs, and the physical address and user-state virtual address are outputs.
                    CNcomment: buffer��Ϣ�ṹ��bufname��bufsize��Ϊ����,�����ַ���û�̬�����ַ��Ϊ���
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_MMZ_Malloc(HI_MMZ_BUF_S *pBuf);

/**
\brief Unmaps the user-state address and releases the MMZ. CNcomment: ����û�̬��ַ��ӳ�䣬���ͷ�mmz�ڴ�
\attention \n
Ensure that the lengths of the transferred physical address and user-state virtual address are correct.
CNcomment: ��֤����������ַ���û�̬�����ַ�ͳ�����ȷ
\param[in] pBuf Structure of the buffer information CNcomment: buffer��Ϣ�ṹ
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_MMZ_Free(HI_MMZ_BUF_S *pBuf);

/**
\brief pplies for an MMZ with a specified name and obtains its physical address. CNcomment: ָ��mmz����������mmz�ڴ棬���������ַ
\attention \n
N/A CNcomment: ��
\param[in] size Buffer size CNcomment: buffer��С
\param[in] align Alignment mode CNcomment: ���뷽ʽ
\param[in] mmz_name Name of an MMZ in the buffer. If the MMZ name is set to NULL, an MMZ is anonymously applied for. CNcomment: buffer���������֣�����NULL��������
\param[in] mmb_name Buffer name CNcomment: buffer�������
\retval ::NULL The application fails. CNcomment: ����ʧ��
\retval Physical address CNcomment: �����ַ
\see \n
N/A CNcomment: ��
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
\brief Releases an MMZ based on its physical address. CNcomment: ͨ�������ַ�ͷ�mmz�ڴ�
\attention \n
N/A CNcomment: ��
\param[in] phys_addr Physical address of a buffer CNcomment: buffer�����ַ
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_MMZ_Delete(HI_U32 phys_addr);

/**
\brief Maps the physical address of an MMZ applied for to a user-state virtual address. You can determine whether to cache the address.
CNcomment: ��mmz����������ַӳ����û�̬�����ַ������ָ���Ƿ�cached
\attention \n
N/A CNcomment: ��
\param[in] phys_addr Physical address of a buffer CNcomment: buffer�����ַ
\param[in] cached Whether to cache the address. 0: no; 1: yes CNcomment: �Ƿ�ʹ��cache��0��ʹ�ã�1ʹ��
\retval ::NULL The application fails. CNcomment: ����ʧ��
\retval User-state virtual address CNcomment: �û�̬���ַ
\see \n
N/A CNcomment: ��
*/
HI_VOID *HI_MMZ_Map(HI_U32 phys_addr, HI_U32 cached);

/**
\brief Unmaps the user-state address of an MMZ. CNcomment: ���mmz�ڴ��û�̬��ַ��ӳ��
\attention \n
N/A CNcomment: ��
\param[in] phys_addr Physical address of a buffer CNcomment: buffer�����ַ
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_MMZ_Unmap(HI_U32 phys_addr);


/**
\brief Flushes D-cache to the cached MMZ. CNcomment: ����cached����MMZ��ˢDcache���ڴ�
\attention \n
If the value 0 is transferred, all D-caches are refreshed; otherwise, only the transferred memory is refreshed.
CNcomment: �������0����ˢ�����е�Dcache������ֻˢ������ǿ��ڴ�
\param[in] phys_addr Physical address of a buffer CNcomment: buffer�����ַ
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_MMZ_Flush(HI_U32 phys_addr);


/**
\brief Maps a physical address to a user-state virtual address. CNcomment: �������ַӳ����û�̬�����ַ
\attention \n
N/A CNcomment: ��
\param[in] u32PhyAddr Physical address of a buffer CNcomment: buffer�����ַ
\param[in] u32Size Buffer size CNcomment: buffer�Ĵ�С
\retval ::NULL The application fails. CNcomment: ����ʧ��
\retval User-state virtual address CNcomment: �û�̬���ַ
\see \n
N/A CNcomment: ��
*/
HI_VOID *HI_MEM_Map(HI_U32 u32PhyAddr, HI_U32 u32Size);


/**
\brief Unmaps a user-state address. CNcomment: ����û�̬��ַ��ӳ��
\attention \n
N/A CNcomment: ��
\param[in] pAddrMapped User-state virtual address of a buffer. CNcomment: buffer���û�̬���ַ
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_MEM_Unmap(HI_VOID *pAddrMapped);

/**
\brief Obtains the physical address and size based on the virtual address. CNcomment: ���������ַ��ȡ�����ַ���Լ���С
\attention \n
N/A CNcomment: ��
\param[in] pVir User-state virtual address CNcomment: �û�̬���ַ
\param[out] pu32Phyaddr Physical address  CNcomment: �����ַ
\param[out] pu32Size Size CNcomment: ��С
\retval ::HI_SUCCESS Success CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails. CNcomment: APIϵͳ����ʧ��
\see \n
N/A CNcomment: ��
*/
HI_S32 HI_MMZ_GetPhyaddr(HI_VOID * pVir, HI_U32 *pu32Phyaddr, HI_U32 *pu32Size);


/** @} */  /** <!-- ==== Structure Definition end ==== */

#endif
#endif /* __HI_COMMON_H__ */
