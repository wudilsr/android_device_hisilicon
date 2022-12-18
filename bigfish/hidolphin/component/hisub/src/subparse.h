/**
 \file
 \brief ��Ļ�����ڲ�ͷ�ļ�
 \copyright Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version draft
 \author l00167705
 \date 2013-9-2
 */

#ifndef __SUBPARSE_H__
#define __SUBPARSE_H__

/* add include here */
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include "hi_svr_subparse.h"

#ifdef __cplusplus
extern "C" {
#endif


/***************************** Macro Definition ******************************/
#define DEFAULT_ORG_BUF_LEN (16*1024)
#define DEFAULT_KEY_VP_NUM  (256)
#define DEFAULT_NODE_NUM    (256)

#define HI_ERR_SUB printf

/*************************** Structure Definition ****************************/

typedef struct hiSUB_PROTOCL_BUFF_S
{
    HI_U8*                pu8OrgData; //ԭʼ����
    HI_U32                u32OrgBufLen;
    HI_U32                u32OrgDataLen;
    HI_SVR_SUB_DATA_S*    pstNodeBuf;//�����Ļ�ڵ�����
    HI_U32                u32NodeBufNum;
    HI_U32                u32NodeDataNum;
    HI_SVR_SUB_KeyVP*     pstKeyVPBuf;//��ֵ������
    HI_U32                u32VPBufNum;
    HI_U32                u32VPDataNum;
} HI_SUB_PROTOCL_BUFF;

typedef HI_S32 (*HI_SUB_PRASE_FN)(HI_VOID* pstProtocl,HI_S64 s64PtsAjustTimeMs);

typedef struct hiSUB_PROTOCOL_S
{
    pthread_mutex_t       stSubMutex;//TODO:���ַ��ڵ�һλ���壬SUB_Parse_Destroy�е��÷�����
    HI_U32                u32UseFlag;
    HI_SVR_SUB_TYPE_E     eSubType;
    HI_SVR_SUB_READ_FN    pfnReadCb;//�ڵ��ý�������ǰ�Ƚ����ݶ���buffer����
    HI_SVR_SUB_SEEK_FN    pfnSeekCb;
    HI_SUB_PRASE_FN       pfnParseCb; //��������
    HI_HANDLE             hTransCode;
    HI_SUB_PROTOCL_BUFF   stBuff;
    HI_U32                u32QuitFlag;
    HI_S32                s32PtsAdjustValue;
    HI_U32                u32UserData;
    HI_U32                u32ParseData0;//�����������������ڱ��������������
    HI_U32                u32ParseData1;
    HI_U32                u32ParseData2;
} HI_SUB_PROTOCOL_S;


/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

/*
���룺��
�������
���أ�HI_SUCCESS-�ɹ��� HI_FAILURE-ʧ�ܡ�
��������Ļ����ģ���ʼ����
 */
HI_S32 SUB_Parse_Init(HI_VOID);

/*
���룺��
�������
���أ�HI_SUCCESS-�ɹ��� HI_FAILURE-ʧ�ܡ�
��������Ļ����ģ��ȥ��ʼ����*/
HI_S32 SUB_Parse_DeInit(HI_VOID);

/*
���룺��Ļ��Ϣ���ο����ݽṹ
�������Ļhandle
���أ�HI_SUCCESS-�ɹ��� HI_FAILURE-ʧ�ܡ�
������������Ļʵ���ӿڡ�*/
HI_S32 SUB_Parse_Create(HI_SVR_SUB_PARAM_S *pstSubParam, HI_HANDLE *phSub);

/*
���룺��Ļhandle
�������
���أ�HI_SUCCESS-�ɹ��� HI_FAILURE-ʧ�ܡ�
������������Ļʵ���ӿڡ�
 */
HI_S32 SUB_Parse_Destroy(HI_HANDLE hSub);

/*
���룺hSub:��Ļhandle
���룺pData����Ҫ�����buffer��ַ
�����u32DataLen����Ҫ��������ݳ���
���أ�HI_SUCCESS-�ɹ��� HI_FAILURE-ʧ�ܡ�
������������Ļ���ݣ�����ڴ�����ʱ��ָ���˶�ȡ���ݵĻص�����ýӿ���Ч��
*/
HI_S32 SUB_Parse_SendData(HI_HANDLE hSub, HI_U8* pData,HI_U32 u32DataLen);

/*
���룺hSub:��Ļhandle
�������
���أ�HI_SUCCESS-�ɹ��� HI_FAILURE-ʧ�ܡ�
��������λ��Ļģ��ʱ�Ĳ�����״̬�л�ʱ��Ҫ���øýӿڡ�
 */
HI_S32 SUB_Parse_Reset(HI_HANDLE hSub);

/*
���룺hSub:��Ļhandle
���룺u32PtsAjustTimeMs:pts����ʱ��
�����pstSubNode��ָ����Ļ��Ϣָ��
�����pu32NodeSize��������Ļ�ڵ�ĸ���
���أ�HI_SUCCESS-�ɹ��� HI_FAILURE-ʧ�ܡ�
�������ú�����Ҫʵ�����湦�ܣ�
1.ͨ��Э��ע��Ķ�ȡ������ȡ��Ļ���ݣ�
2.ͨ��ת��ģ������ݽ���ת�룻
3.����Э������������н�����
 */
HI_S32 SUB_Parse_ReadSubNodes(HI_HANDLE hSub, HI_S64 s64PtsAjustTimeMs, HI_SVR_SUB_DATA_S** pstSubNode,HI_U32* pu32NodeNum,HI_SVR_SUB_KeyVP** pstSubKeyVpBuf,
                               HI_U32* pu32KeyVpNum);

/*
���룺hSub:��Ļhandle
���أ�HI_SUCCESS-�ɹ��� HI_FAILURE-ʧ�ܡ�
���������øú���������˳���
 */
HI_S32 SUB_Parse_QuickQuitRequest(HI_HANDLE hSub);

#ifdef __cplusplus
}
#endif
#endif /* __SUBPARSE_H__ */
