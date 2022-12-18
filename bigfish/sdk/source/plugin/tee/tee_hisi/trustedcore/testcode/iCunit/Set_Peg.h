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

#define COMPOSE_PID(coreid, handle)   ((((UINT32)(coreid))<<8) + ((UINT8)(handle))) /* ��coreid��handle���PID,UIPC��ʹ�øýӿ� */

#define OS_ERR_RECORD_NUM      9   //1+8����һ�δ���̶���¼������8��ѭ����¼��

/*�ϱ��Ĵ�����Ϣ�ṹ��*/
typedef struct tagErrInfo_PEG_S
{
    UINT32    uwTickCnt;
    UINT32    uwErrorNo;
} ERR_INFO_PEG_S;

/**
 * @ingroup SRE_cda
 * ������CDA�ڴ���Ϣ�ṹ��, ע����Դ��Ľṹ��CDA_INFO_S����һ��
 */
typedef struct tagTestCdaInfo
{
    UINT32 uwMagicWord;                         /**< CDA�ṹ��Ϣħ����                      */
    UINT32 uwTCBStartAddr;                      /**< �ڴ���������ƿ���ʼ��ַ               */
    UINT32 uwSCBStartAddr;                      /**< �ڴ������жϿ��ƿ���ʼ��ַ             */
    UINT32 uwMailBufAddr;                       /**< ���仺�����ʼ��ַ                     */
    UINT32 uwMsgStartAddr;                      /**< ������Ϣ�ڵ�������ʼ��ַ               */
    UINT32 uwMcMsgStartAddr;                    /**< �˼���Ϣ�ڵ�������ʼ��ַ               */
    UINT32 uwSemStartAddr;                      /**< �����ź����ڵ�������ʼ��ַ             */
    UINT32 uwMcSemStartAddr;                    /**< �˼��ź����ڵ�������ʼ��ַ             */
    UINT32 uwMsgNum;                            /**< ������Ϣ����                           */
//  UINT32 uwMcMsgNum;                          /**< �˼���Ϣ����                           */
    UINT16 uwSemNum;                            /**< �����ź�������                         */
    UINT16 uwMcSemNum;                          /**< �˼��ź�������                         */
    UINT16 uwTaskMaxNum;                        /**< ϵͳ֧�ֵ�����������                 */
    UINT16 uwSwiMaxNum;                         /**< ϵͳ֧�ֵ�������жϸ���               */
    UINT32 uwRecordIndex;                       /**< ϵͳ��¼������Ϣ������                 */
    ERR_INFO_PEG_S astErrInfo[OS_ERR_RECORD_NUM]; /**< ϵͳ��¼������Ϣ                     */
    UINT8  uwExcFlag;                           /**< ϵͳ�����쳣ʱ��¼���쳣��־λ         */
    UINT8  uwCoreID;                            /**< ��ǰ���к˺�                           */
    UINT8  uwPlatform;                          /**< оƬ����                               */
    UINT8  uwCPUID;                             /**< CPU�ͺ�                                */
    UINT16 ucOptPtNum;                          /**< osȱʡ�����˼�������                   */
    UINT16 ucMaxPtNum;                          /**< ��ǰʵ�ʴ��������ܸ���                 */
    UINT32 uwExcBufAddr;                        /**< �쳣��Ϣ�׵�ַ                         */
    UINT32 uwMsgmNorProfStartAddr;              /**< MSGM��������profiling�������׵�ַ      */
    UINT16 usMsgmProfQPortMsgNum[4];            /**< MSGMÿ��QPORT profilingʵ����Ϣ��      */
    UINT32 uwHwiFormAddr;                       /**< Ӳ�жϴ�����������׵�ַ             */
    UINT32 uwHwiDefault;                        /**< Ӳ�ж�Ĭ�ϴ������ĵ�ַ               */
    UINT32 uwUniFlagAddr;                       /**< UniDSPϵͳ״̬��ַ                     */
    UINT32 uwTaskLockAddr;                      /**< �������ĵ�ַ                           */
    UINT32 uwIntCountAddr;                      /**< Hwi�ж�Ƕ�׼����ĵ�ַ                  */
    UINT32 uwExcNestCntAddr;                    /**<�쳣Ƕ�׼����ĵ�ַ                      */
    UINT32 uwTskModInfoAddr;                    /**< ����ģ��ע����Ϣ�׵�ַ                 */
    UINT32 uwTraceModAddr;                      /**< ϵͳ����ģ����ʼ��ַ                   */
    UINT32 uwHuntBufAddr;                       /**< HUNTģ����ʼ��ַ                       */
    UINT32 uwSysStackBottom;                    /**< ϵͳջջ�׵�ַ                         */
    UINT32 uwSysStackTop;                       /**< ϵͳջջ����ַ                         */
    UINT32 uwHwiNestAddr;                       /**< �洢Ӳ�ж�Ƕ�׹�ϵ�ĵ�ַ               */
#if((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170)|| (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220))
    UINT32 uwIpcHuntNodeAddr;                   /**< ʵ�������׵�ַ                       */
    UINT32 uwIpcLaPcbExAddr;                    /**< ����ʵ�����ƿ���׵�ַ                 */
    UINT32 uwIpcRmtPcbExAddr;                   /**< Զ��Ӱ��ʵ�����ƿ���׵�ַ             */
    UINT32 uwIpcConnArrayAddr;                  /**< CM����·���������׵�ַ*/
    UINT32 uwIpcConnExtArrayAddr;               /**< CM����·��չ�������ݵ��׵�ַ           */
    UINT32 uwIpcLinxStartAddr;                  /**< ��·���ƿ���׵�ַ                     */
    UINT32 uwLmPidMaxNumAddr;                   /**< ϵͳ֧�ֵ����ʵ����                   */
    UINT32 uwLmHuntPendAddr;                    /**< Hunt�����߳����������׵�ַ             */
#endif
    UINT32 uwOsVerAddr;                         /**< OS�汾���׵�ַ                         */
    UINT32 uwCdaVersion;                        /**< CDA�汾��                              */
    CDA_PT_INFO_S astPtInfo[1];                 /**< ���ڴ������Ϣ                         */
} TST_CDA_INFO_S;


#if ((OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC170)|| (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
#define GET_PS_A1   \
do{                 \
    OS_EMBED_ASM("  rsr    %0, ps; rsync" : "=a" (uwPS) ); \
    OS_EMBED_ASM("  mov    %0, a1" : "=a" (uwA1) );        \
}while(0)

/*
 *�쳣ʱ��¼��ipc������Ϣ��ע����Դ���еĽṹ��IPC_STATUS_S����һ��
 */
typedef struct tagTstIpcStatus
{
    UINT32 vuwSrc;
    UINT32 vuwData[2];
}TST_IPC_STATUS_S;

/*
 *�û����Կ����쳣��Ϣ
 *
 *�쳣��Ϣ�ṹ�壬ע����Դ���еĽṹ��EXC_INFO_S����һ��
 */
typedef struct tagTstExcInfo
{
    CHAR                acOSVer[40];                         /* OS�汾��       */
    CHAR                acAppVer[40];                        /* ��Ʒ�汾��     */
    CHAR                acTaskName[OS_TSK_NAME_LEN];         /* ������         */
    CHAR                acSwiName[OS_TSK_NAME_LEN];          /* ���ж���       */
    UINT16              usByteOrder;                         /* �ֽ���         */
    UINT16              usCpuType;                           /* CPU����        */
    UINT32              uwCpuID;                             /* CPU ID         */
    CPU_TICK            stCpuTick;                           /* CPU Tick       */
    UINT32              uwTaskID;                            /* ����PID        */
    UINT32              uwSwiID;                             /* ���ж�PID      */
    EXC_REGS_S          stRegInfo;                           /* �Ĵ�����Ϣ     */
    UINT32              uwThread;                            /* �쳣ǰ���߳����� */
    CSTK_FRAME_INFO_S   astStackLayer[EXC_CSTK_DEAPTH];      /* ����ջ������� */
    UINT32              uwBasicMagic;                        /* EXC_VALID      */
    UINT32              uwState;                             /* �쳣״̬��־λ */
    TST_IPC_STATUS_S    auwIpcStatus[8];                     /* ipc����״̬��ÿ����ֻ��8��mailbox*/
    UINT32              uwStackBegin;                        /* �쳣ǰջ������ʼ��ַ       */
    UINT32              uwStackSize;                         /* ������쳣ǰ��ջ��С*/
    UINT8               aucStackContent[4];                  /* �쳣ǰ��ջ����*/
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
    UINT8  uJmpP1;                      /* ����ͷ����jumpָ����       */
    UINT8  uJmpP2;
    UINT8  uJmpP3;
    UINT8  ucReserved;                  /* ������                       */
    UINT32 ulNewAddr;                   /* ����º�����ַ               */
    UINT8  uL32rP1;                     /* ��ȡ����������ַ��ָ����     */
    UINT8  uL32rP2;
    UINT8  uL32rP3;
    UINT8  uJmpXp1;                     /* ��ת������������ַ��ָ����   */
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


