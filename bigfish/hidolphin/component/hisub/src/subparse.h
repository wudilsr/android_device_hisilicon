/**
 \file
 \brief 字幕解析内部头文件
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
    HI_U8*                pu8OrgData; //原始数据
    HI_U32                u32OrgBufLen;
    HI_U32                u32OrgDataLen;
    HI_SVR_SUB_DATA_S*    pstNodeBuf;//输出字幕节点数据
    HI_U32                u32NodeBufNum;
    HI_U32                u32NodeDataNum;
    HI_SVR_SUB_KeyVP*     pstKeyVPBuf;//键值对数据
    HI_U32                u32VPBufNum;
    HI_U32                u32VPDataNum;
} HI_SUB_PROTOCL_BUFF;

typedef HI_S32 (*HI_SUB_PRASE_FN)(HI_VOID* pstProtocl,HI_S64 s64PtsAjustTimeMs);

typedef struct hiSUB_PROTOCOL_S
{
    pthread_mutex_t       stSubMutex;//TODO:保持放在第一位定义，SUB_Parse_Destroy中的用法限制
    HI_U32                u32UseFlag;
    HI_SVR_SUB_TYPE_E     eSubType;
    HI_SVR_SUB_READ_FN    pfnReadCb;//在调用解析函数前先将数据读包buffer里面
    HI_SVR_SUB_SEEK_FN    pfnSeekCb;
    HI_SUB_PRASE_FN       pfnParseCb; //解析函数
    HI_HANDLE             hTransCode;
    HI_SUB_PROTOCL_BUFF   stBuff;
    HI_U32                u32QuitFlag;
    HI_S32                s32PtsAdjustValue;
    HI_U32                u32UserData;
    HI_U32                u32ParseData0;//下面三个参数可用于保存解析过程数据
    HI_U32                u32ParseData1;
    HI_U32                u32ParseData2;
} HI_SUB_PROTOCOL_S;


/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

/*
输入：无
输出：无
返回：HI_SUCCESS-成功， HI_FAILURE-失败。
描述：字幕解析模块初始化。
 */
HI_S32 SUB_Parse_Init(HI_VOID);

/*
输入：无
输出：无
返回：HI_SUCCESS-成功， HI_FAILURE-失败。
描述：字幕解析模块去初始化。*/
HI_S32 SUB_Parse_DeInit(HI_VOID);

/*
输入：字幕信息，参考数据结构
输出：字幕handle
返回：HI_SUCCESS-成功， HI_FAILURE-失败。
描述：创建字幕实例接口。*/
HI_S32 SUB_Parse_Create(HI_SVR_SUB_PARAM_S *pstSubParam, HI_HANDLE *phSub);

/*
输入：字幕handle
输出：无
返回：HI_SUCCESS-成功， HI_FAILURE-失败。
描述：创建字幕实例接口。
 */
HI_S32 SUB_Parse_Destroy(HI_HANDLE hSub);

/*
输入：hSub:字幕handle
输入：pData：需要送入的buffer地址
输出：u32DataLen：需要送入的数据长度
返回：HI_SUCCESS-成功， HI_FAILURE-失败。
描述：发送字幕数据，如果在创建的时候指定了读取数据的回调，则该接口无效。
*/
HI_S32 SUB_Parse_SendData(HI_HANDLE hSub, HI_U8* pData,HI_U32 u32DataLen);

/*
输入：hSub:字幕handle
输出：无
返回：HI_SUCCESS-成功， HI_FAILURE-失败。
描述：复位字幕模块时的操作，状态切换时需要调用该接口。
 */
HI_S32 SUB_Parse_Reset(HI_HANDLE hSub);

/*
输入：hSub:字幕handle
输入：u32PtsAjustTimeMs:pts调整时间
输出：pstSubNode：指向字幕信息指针
输出：pu32NodeSize：返回字幕节点的个数
返回：HI_SUCCESS-成功， HI_FAILURE-失败。
描述：该函数主要实现下面功能：
1.通过协议注册的读取函数读取字幕数据；
2.通过转码模块对数据进行转码；
3.调用协议解析函数进行解析。
 */
HI_S32 SUB_Parse_ReadSubNodes(HI_HANDLE hSub, HI_S64 s64PtsAjustTimeMs, HI_SVR_SUB_DATA_S** pstSubNode,HI_U32* pu32NodeNum,HI_SVR_SUB_KeyVP** pstSubKeyVpBuf,
                               HI_U32* pu32KeyVpNum);

/*
输入：hSub:字幕handle
返回：HI_SUCCESS-成功， HI_FAILURE-失败。
描述：调用该函数后快速退出。
 */
HI_S32 SUB_Parse_QuickQuitRequest(HI_HANDLE hSub);

#ifdef __cplusplus
}
#endif
#endif /* __SUBPARSE_H__ */
