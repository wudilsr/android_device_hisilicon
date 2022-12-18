/**
 * @file sre_err.ph
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * �������������ڲ�ͷ�ļ��� \n
 */

#ifndef _SRE_ERR_PH
#define _SRE_ERR_PH

#include "sre_err.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


//��ֹliteral����붼������L1ʱ��CDA���߼��ʱ��������ֵͬ��ħ����,CDA���߶˼���ħ����Ϊ0xa53ce169
#define OS_CDA_MAGIC_WORD           0xa53ce168
#define OS_CDA_VERSION              0x00010700

//�쳣����ʱ����������SD6108/SD6181��SD6182
#define OS_CDA_CPU_TYPE_0881        0x10101010
#define OS_CDA_CPU_TYPE_82          0x20202020

/* �û�������Ľṹ�� */
typedef struct tagUserErrFunc_S
{
    SRE_ERRORHANDLE_FUNC  pfnHook;  /* �û����Ӻ��� */
} USER_ERR_FUNC_S;

#define OS_ERR_RECORD_N        3   //��ʾ���������Ƶ�nλ������OS_ERR_RECORD_NUM�ã�OS_ERR_RECORD_NUMΪ2��n�η�+1

#define OS_ERR_RECORD_NUM      ((1 << OS_ERR_RECORD_N) + 1) //2��n�η�+1��Ŀǰnȡ3��NUMΪ9����һ�δ���̶���¼������8��ѭ����¼��

/*�ϱ��Ĵ�����Ϣ�ṹ��*/
typedef struct tagErrInfo_S
{
    UINT32    uwTickCnt;
    UINT32    uwErrorNo;
} ERR_INFO_S;

/**
 * @ingroup SRE_cda
 * CDA�ڴ���Ϣ�ṹ��,ע��ͬ�����²��Դ����еĽṹ��TST_CDA_INFO_S
 */
typedef struct tagCdaInfo
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
    UINT16 usSemNum;                            /**< �����ź�������                         */
    UINT16 usMcSemNum;                          /**< �˼��ź�������                         */
    UINT16 usTaskMaxNum;                        /**< ϵͳ֧�ֵ�����������                 */
    UINT16 usSwiMaxNum;                         /**< ϵͳ֧�ֵ�������жϸ���               */
    UINT16 usSwtmrMaxNum;                       /**< �����ʱ��������                     */
    UINT16 usHwtmrMaxNum;                       /**< Ӳ����ʱ��������                     */
    UINT32 uwTickPerSecond;                     /**< ÿ����TICK��                           */
    UINT32 uwSwtmrStartAddr;                    /**< �ڴ��������ʱ�����ƿ���ʼ��ַ         */
    UINT32 uwHwtmrCBAddr;                       /**< Ӳ����ʱ�����ƿ��ַ                   */
    UINT32 uwBWPManageInfoAddr;                 /**< �ϵ������Ϣ��ʼ��ַ                   */
    UINT32 uwCpProFlag;                         /**< ʸ���Ĵ��������Ƿ�򿪱�־             */
    UINT32 uwRecordIndex;                       /**< ϵͳ��¼������Ϣ������                 */
    ERR_INFO_S astErrInfo[OS_ERR_RECORD_NUM];   /**< ϵͳ��¼������Ϣ                       */
    UINT8  ucExcFlag;                           /**< ϵͳ�����쳣ʱ��¼���쳣��־λ         */
    UINT8  ucCoreID;                            /**< ��ǰ���к˺�                           */
    UINT8  ucPlatform;                          /**< оƬ����                               */
    UINT8  ucCPUID;                             /**< CPU�ͺ�                                */
    UINT16 usOptPtNum;                          /**< osȱʡ�����˼�������                   */
    UINT16 usMaxPtNum;                          /**< ��ǰʵ�ʴ��������ܸ���                 */
    UINT32 uwExcBufAddr;                        /**< �쳣��Ϣ�׵�ַ                         */
    UINT32 uwMsgmNorProfStartAddr;              /**< MSGM��������profiling�������׵�ַ      */
    UINT16 usMsgmProfQPortMsgNum[3];            /**< MSGMÿ��QPORT profilingʵ����Ϣ��      */
    UINT8  ucMsgmProfQPort0Type;                /**< MSGM 0��QPORT OS���û�������Ϣ��־     */
    UINT8  ucPreserved;                         /**< Ԥ���ֽ�                               */
    UINT16 usLHwSemNum;                         /**< HWSEM �ֲ�Ӳ���ź�������               */
    UINT16 usGHwSemNum;                         /**< HWSEM ȫ��Ӳ���ź�������               */
    UINT32 uwHwSemStartAddr;                    /**< HWSEM ���ƿ���ʼ��ַ                   */
    UINT32 uwHwiFormAddr;                       /**< Ӳ�жϴ�����������׵�ַ             */
    UINT32 uwHwiModeFormAddr;                   /**< Ӳ�жϹ���ģʽ������׵�ַ             */
    UINT32 uwHwiDefault;                        /**< Ӳ�ж�Ĭ�ϴ������ĵ�ַ               */
    UINT32 uwUniFlagAddr;                       /**< UniDSPϵͳ״̬��ַ                     */
    UINT32 uwTaskLockAddr;                      /**< �������ĵ�ַ                           */
    UINT32 uwIntCountAddr;                      /**< Hwi�ж�Ƕ�׼����ĵ�ַ                  */
    UINT32 uwExcNestCntAddr;                    /**< �쳣Ƕ�׼����ĵ�ַ                     */
    UINT32 uwTskModInfoAddr;                    /**< ����ģ��ע����Ϣ�׵�ַ                 */
    UINT32 uwTraceModAddr;                      /**< ϵͳ����ģ����ʼ��ַ                   */
    UINT32 uwHuntBufAddr;                       /**< HUNTģ����ʼ��ַ                       */
    UINT32 uwSysStackBottom;                    /**< ϵͳջջ�׵�ַ                         */
    UINT32 uwSysStackTop;                       /**< ϵͳջջ����ַ                         */
    UINT32 uwHwiNestAddr;                       /**< �洢Ӳ�ж�Ƕ�׹�ϵ�ĵ�ַ               */
    UINT32 uwExcRegsAddr;                       /**< �����쳣�����ĵ�ַ                     */
    UINT32 uwOsVerAddr;                         /**< OS�汾���׵�ַ                         */
    UINT32 uwCdaVersion;                        /**< CDA�汾��                              */
    CDA_PT_INFO_S astPtInfo[1];                 /**< ���ڴ������Ϣ                         */
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
