/**
 \file
 \brief subtitle output
 \author Shenzhen Hisilicon Co., Ltd.
 \version 1.0
 \author
 \date 2010-04-07
 */

#include <pthread.h>
#include "so_queue.h"
#include "hi_unf_so.h"

#define SO_NORMAL_MAX_DISPLAY_TIME        (10 * 1000)  /**< 10s */
#define SO_NORMAL_MIN_DISPLAY_TIME        (2 * 1000)  /**< ss */
#define SO_PLAY_TIME_JUMP_JUDGE           (5 * 1000)  /**< 5s */
#define SO_TRHEAD_SLEEP_TIME          (10)
#define SO_TIME_OFFSET                (10)
#define SO_QUEUE_RESET_CHECK_TIME     (100)
#define SO_QUEUE_MAX_CLEAR_NODE_NUM   (512)
#define SO_SEND_OFFSET                (20)  /**< 20ms */

#define SO_CALLBACK_LOCK()    \
    do{\
        int ret = pthread_mutex_lock(&pstMember->stMutex);\
        if(ret != 0){\
            printf("SO call pthread_mutex_lock(stMutex) failure,ret = 0x%x\n",ret);\
        }\
    }while(0)

#define SO_CALLBACK_UNLOCK()   \
    do{\
        int ret = pthread_mutex_unlock(&pstMember->stMutex);\
        if(ret != 0){\
            printf("SO call pthread_mutex_unlock(stMutex) failure, ret = 0x%x\n",ret);\
        }\
    }while(0)

#define SO_QUEUE_RESET_LOCK()  \
    do{\
        int ret = pthread_mutex_lock(&pstMember->stQueueResetMutex);\
        if(ret != 0){\
            printf("SO call pthread_mutex_lock(stQueueResetMutex) failure,ret = 0x%x\n",ret);\
        }\
    }while(0)

#define SO_QUEUE_RESET_UNLOCK()  \
    do{\
        int ret = pthread_mutex_unlock(&pstMember->stQueueResetMutex);\
        if(ret != 0){\
            printf("SO call pthread_mutex_unlock(stQueueResetMutex) failure, ret = 0x%x\n",ret);\
        }\
    }while(0)

static HI_BOOL s_bSoInit = HI_FALSE;

typedef struct tagSO_CLEAR_NODE_S
{
    HI_UNF_SO_CLEAR_PARAM_S stClearParam;
    HI_U32 u32Duration;
    HI_S64 s64NodePts;
} SO_CLEAR_NODE_S;

/************************ Structure Definition **************************/
/** so module members */
typedef struct tagSO_MEMBER_S
{
    HI_UNF_SO_GETPTS_FN  pfnGetPts;    /**< get local time */
    HI_UNF_SO_ONDRAW_FN  pfnOnDraw;    /**< draw subtitle */
    HI_UNF_SO_ONCLEAR_FN pfnOnClear;   /**< clear subtitle, called after pfnOnDraw */
    HI_HANDLE hSurface;                /**< surface for subtitle output */
    HI_BOOL   bThreadExit;             /**< flag of so exit */
    HI_BOOL   bQueueReset;             /**< reset subtitle queue */
    HI_S64    s64ResetPts;             /**< reset subtitle queue by pts */
    HI_U32    u32PtsUserData;          /**< user data of pfnGetPts */
    HI_U32    u32DrawUserData;         /**< user data of pfnOnDraw and pfnOnClear */
    HI_U32    u32Font;                 /**< font of subtitle output */
    HI_S64    s64PtsOffset;
    HI_U32    u32Color;                /**< color of subtitle output */
    HI_U32    x, y;                    /**< position of subtitle output */
    SO_QUEUE_HANDLE queuehdl;          /**< subtitle queue handle */
    pthread_t hTaskId;                 /**< main task handle */
    pthread_mutex_t stMutex;           /**< main task mutex */
    pthread_mutex_t stQueueResetMutex; /**< mutex of bQueueReset */
    pthread_attr_t  struAttr;          /**< main task attribute */
    HI_U32 u32ReadIndx;                /**< read pos of node list */
    HI_U32 u32WriteIndx;               /**< write pos of node list */
    HI_S64 s64LastPts;                 /**< Last subt frame pts */
    HI_U32 u32IntervalMs;           /**< subtitle max interval time*/
    SO_CLEAR_NODE_S astClearNodeList[SO_QUEUE_MAX_CLEAR_NODE_NUM];
} SO_MEMBER_S;

static HI_S32 SO_DrawSubtitle(const HI_UNF_SO_SUBTITLE_INFO_S *pstInfo)
{
    return HI_SUCCESS;
}

static HI_S32 SO_GetNodeClearInfo(const SO_INFO_S *pstInfo, HI_UNF_SO_CLEAR_PARAM_S *pstClearParam)
{
    if (HI_UNF_SUBTITLE_BITMAP == pstInfo->eType)
    {
        pstClearParam->x = pstInfo->unSubtitleParam.stGfx.x;
        pstClearParam->y = pstInfo->unSubtitleParam.stGfx.y;
        pstClearParam->w = pstInfo->unSubtitleParam.stGfx.w;
        pstClearParam->h = pstInfo->unSubtitleParam.stGfx.h;
    }
    else if (HI_UNF_SUBTITLE_TEXT == pstInfo->eType)
    {
        pstClearParam->x = pstInfo->unSubtitleParam.stText.x;
        pstClearParam->y = pstInfo->unSubtitleParam.stText.y;
        pstClearParam->w = pstInfo->unSubtitleParam.stText.w;
        pstClearParam->h = pstInfo->unSubtitleParam.stText.h;
    }
    else if (HI_UNF_SUBTITLE_ASS == pstInfo->eType)
    {
        pstClearParam->x = 0;
        pstClearParam->y = 0;
        pstClearParam->w = 0;
        pstClearParam->h = 0;
    }
    else
    {
        pstClearParam->x = 0;
        pstClearParam->y = 0;
        pstClearParam->w = 0;
        pstClearParam->h = 0;
    }

    return HI_SUCCESS;
}

static HI_S32 SO_GetNodePts(const SO_INFO_S *pstInfo, HI_S64 *ps64Pts, HI_U32 *pu32Duration)
{
    if (HI_UNF_SUBTITLE_BITMAP == pstInfo->eType)
    {
        *ps64Pts = pstInfo->unSubtitleParam.stGfx.s64Pts;
        *pu32Duration = pstInfo->unSubtitleParam.stGfx.u32Duration;
    }
    else if (HI_UNF_SUBTITLE_TEXT == pstInfo->eType)
    {
        *ps64Pts = pstInfo->unSubtitleParam.stText.s64Pts;
        *pu32Duration = pstInfo->unSubtitleParam.stText.u32Duration;
    }
    else if (HI_UNF_SUBTITLE_ASS == pstInfo->eType)
    {
        *ps64Pts = pstInfo->unSubtitleParam.stAss.s64Pts;
        *pu32Duration = pstInfo->unSubtitleParam.stAss.u32Duration;
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 SO_InsertToClearList(SO_MEMBER_S *pstMember, const SO_INFO_S *pstSoInfo, HI_S64 s64NodePts, HI_U32 u32Duration)
{
    HI_U32 u32NodeNum = 0;

    if (pstMember->u32WriteIndx < SO_QUEUE_MAX_CLEAR_NODE_NUM)
    {
        pstMember->astClearNodeList[pstMember->u32WriteIndx].s64NodePts  = s64NodePts;
        pstMember->astClearNodeList[pstMember->u32WriteIndx].u32Duration = u32Duration;
        (HI_VOID)SO_GetNodeClearInfo(pstSoInfo, &pstMember->astClearNodeList[pstMember->u32WriteIndx].stClearParam);
        pstMember->u32WriteIndx++;
    }
    else
    {
        if (pstMember->u32ReadIndx < pstMember->u32WriteIndx)
        {
            u32NodeNum = pstMember->u32WriteIndx - pstMember->u32ReadIndx;

            SO_MEMMOVE(&pstMember->astClearNodeList[0], &pstMember->astClearNodeList[pstMember->u32ReadIndx], u32NodeNum);
            pstMember->u32ReadIndx  = 0;
            pstMember->u32WriteIndx = pstMember->u32ReadIndx + u32NodeNum;
        }
        else
        {
            pstMember->u32ReadIndx  = 0;
            pstMember->u32WriteIndx = 0;
            SO_MEMSET(pstMember->astClearNodeList, 0, sizeof(SO_CLEAR_NODE_S) * SO_QUEUE_MAX_CLEAR_NODE_NUM);
        }

        pstMember->astClearNodeList[pstMember->u32WriteIndx].s64NodePts  = s64NodePts;
        pstMember->astClearNodeList[pstMember->u32WriteIndx].u32Duration = u32Duration;
        (HI_VOID)SO_GetNodeClearInfo(pstSoInfo, &pstMember->astClearNodeList[pstMember->u32WriteIndx].stClearParam);
        pstMember->u32WriteIndx++;
    }

    return HI_SUCCESS;
}

static HI_S32 SO_ClearNode(SO_MEMBER_S *pstMember, HI_UNF_SO_GETPTS_FN pfnGetPts, HI_UNF_SO_ONCLEAR_FN pfnOnClear)
{
    HI_S64 s64NodePts = 0, s64CurPts = 0;
    HI_U32 u32Duration = 0;

    if (NULL == pfnGetPts || NULL == pfnOnClear)
    {
        return HI_FAILURE;
    }

    if (pstMember->u32WriteIndx > pstMember->u32ReadIndx)
    {
        u32Duration = pstMember->astClearNodeList[pstMember->u32ReadIndx].u32Duration;
        s64NodePts  = pstMember->astClearNodeList[pstMember->u32ReadIndx].s64NodePts;

        (HI_VOID)pfnGetPts(pstMember->u32PtsUserData, &s64CurPts);

        if (HI_UNF_SO_NO_PTS != (HI_U32)s64CurPts
            && ((s64CurPts - s64NodePts) >= (u32Duration - SO_TIME_OFFSET) || u32Duration < SO_TIME_OFFSET))
        {
            // clear this subtitle
            // l00192899 add current time in stClearParam,check it while clear pgs sub.
            pstMember->astClearNodeList[pstMember->u32ReadIndx].stClearParam.s64ClearTime = s64CurPts;
            pstMember->astClearNodeList[pstMember->u32ReadIndx].stClearParam.s64NodePts = s64NodePts;
            pstMember->astClearNodeList[pstMember->u32ReadIndx].stClearParam.u32Duration = u32Duration;
            if (NULL != pfnOnClear)
            {
                (HI_VOID)pfnOnClear(pstMember->u32DrawUserData,
                    (HI_VOID*)&pstMember->astClearNodeList[pstMember->u32ReadIndx].stClearParam);
            }

            pstMember->u32ReadIndx++;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 SO_SyncOutput(SO_MEMBER_S *pstMember, HI_UNF_SO_GETPTS_FN pfnGetPts,
                                   HI_UNF_SO_ONDRAW_FN  pfnOnDraw,
                                   HI_UNF_SO_ONCLEAR_FN pfnOnClear,
                                   const SO_INFO_S *pstSoInfo)
{
    HI_S32  s32Ret = 0;
    HI_S64  s64CurPts = 0, s64NodePts = 0, s64CurNodePts = 0;
    HI_S64  s64MaxPts = 0, s64MinPts = 0;
    HI_U32  u32Duration = 0, u32NodeDuration = 0;

    HI_BOOL bDirectOut = HI_FALSE;
    HI_BOOL bClearSub = HI_TRUE;

    SO_INFO_S stNextSubInfo;

    for (;;)
    {
        if (HI_TRUE == pstMember->bThreadExit || HI_TRUE == pstMember->bQueueReset)
        {
            //pstMember->bQueueReset = HI_FALSE;
            return HI_SUCCESS;
        }
        (HI_VOID)SO_ClearNode(pstMember, pfnGetPts, pstMember->pfnOnClear);
        (HI_VOID)pfnGetPts(pstMember->u32PtsUserData, &s64CurPts);
        (HI_VOID)SO_GetNodePts(pstSoInfo, &s64CurNodePts, &u32NodeDuration);

        s64CurNodePts += pstMember->s64PtsOffset;

        /* CurPts less than LastPts, need to reset SO */
        if (((s64CurPts + SO_PLAY_TIME_JUMP_JUDGE) < pstMember->s64LastPts) && (HI_UNF_SO_NO_PTS != s64CurPts))
        {
            pstMember->bQueueReset = HI_TRUE;
            pstMember->s64LastPts = 0;
            return HI_SUCCESS;
        }
        pstMember->s64LastPts = s64CurPts;

        /* local time is invalid, do not output subtitle */

        if (HI_UNF_SO_NO_PTS == (HI_U32)s64CurPts)
        {
            SO_SLEEP(SO_TIME_OFFSET);
            continue;
        }
        /*the subtitle display pts and video pts interval is too large,direct output*/
        /*app set interval time*/
        if(0 != pstMember->u32IntervalMs)
        {
            s64MaxPts = s64CurNodePts + pstMember->u32IntervalMs;
            s64MinPts = s64CurNodePts - pstMember->u32IntervalMs;

            if((s64CurPts <= s64MinPts) || (s64CurPts >= s64MaxPts))
            {
                bDirectOut = HI_TRUE;
                break;
            }
        }

        if ((s64CurPts < s64CurNodePts) && (s64CurNodePts - s64CurPts > SO_SEND_OFFSET))
        {
            /* pts of subtitle is larger than local time */

            SO_SLEEP(SO_TIME_OFFSET);
            continue;
        }
        else
        {
            break;
        }
    }

    /* pts of subtitle is less than or equal to local time */
    //bClearSub = HI_TRUE;
    if (0 != u32NodeDuration)
    {
        /* local time is larger than (pts + duration), skip this subtitle */
        if(bDirectOut == HI_FALSE)
        {
            SO_RETURN((s64CurPts > s64CurNodePts + u32NodeDuration), HI_SUCCESS, NULL);
        }

        u32Duration = (HI_U32)((s64CurNodePts + u32NodeDuration) - s64CurPts);
        u32Duration = u32Duration > u32NodeDuration ? u32NodeDuration : u32Duration;
    }
    else
    {
        /* this subtitle has no duration, get pts of next subtitle in queue */
        SO_MEMSET(&stNextSubInfo, 0, sizeof(stNextSubInfo));
        s32Ret = SO_QueueGetNodeInfoNotDel(pstMember->queuehdl, &stNextSubInfo);

        if (HI_SUCCESS != s32Ret)
        {
            /* dufault duration */
            u32Duration = SO_NORMAL_MIN_DISPLAY_TIME;
        }
        else
        {
            (HI_VOID)SO_GetNodePts(&stNextSubInfo, &s64NodePts, &u32NodeDuration);
            s64NodePts += pstMember->s64PtsOffset;

            /* local time is larger than this subtitle, skip last subtitle */
            if(bDirectOut == HI_FALSE)
            {
                SO_RETURN((s64CurPts + SO_TIME_OFFSET >= s64NodePts), HI_SUCCESS, NULL);
            }
            u32Duration = (HI_U32)(s64NodePts - s64CurPts - SO_TIME_OFFSET);
            u32Duration = u32Duration > SO_NORMAL_MAX_DISPLAY_TIME ? SO_NORMAL_MAX_DISPLAY_TIME : u32Duration;
            if (HI_UNF_SUBTITLE_BITMAP == pstSoInfo->eType && u32Duration < SO_NORMAL_MAX_DISPLAY_TIME)
            {
                bClearSub = HI_FALSE;
            }
        }
    }

#if 0
    /* clear last subtitle */

    if (NULL != pfnOnClear)
    {
        (HI_VOID)pfnOnClear(pstMember->u32DrawUserData);
    }
#endif

    if (HI_UNF_SUBTITLE_BITMAP == pstSoInfo->eType && HI_UNF_SO_DISP_MSG_ERASE == pstSoInfo->unSubtitleParam.stGfx.enMsgType)
    {
        pstMember->u32ReadIndx = 0;
        pstMember->u32WriteIndx = 0;
        SO_MEMSET(pstMember->astClearNodeList, 0, sizeof(SO_CLEAR_NODE_S) * SO_QUEUE_MAX_CLEAR_NODE_NUM);

        /* if reset clear list, insert a empty node */

        stNextSubInfo.eType = HI_UNF_SUBTITLE_BUTT;
        SO_InsertToClearList(pstMember, &stNextSubInfo, 0, SO_TIME_OFFSET);
    }

    if (HI_UNF_SUBTITLE_BITMAP == pstSoInfo->eType && HI_UNF_SO_DISP_MSG_NORM == pstSoInfo->unSubtitleParam.stGfx.enMsgType)
    {
        /* if no pix data in normal display message, just need to clear OSD only */
        if (0 == pstSoInfo->unSubtitleParam.stGfx.x &&
            0 == pstSoInfo->unSubtitleParam.stGfx.y &&
            0 == pstSoInfo->unSubtitleParam.stGfx.w &&
            0 == pstSoInfo->unSubtitleParam.stGfx.h )
        {
            pstMember->u32ReadIndx = 0;
            pstMember->u32WriteIndx = 0;
            SO_MEMSET(pstMember->astClearNodeList, 0, sizeof(SO_CLEAR_NODE_S) * SO_QUEUE_MAX_CLEAR_NODE_NUM);

            /* if reset clear list, insert a empty node */

            stNextSubInfo.eType = HI_UNF_SUBTITLE_BUTT;
            SO_InsertToClearList(pstMember, &stNextSubInfo, 0, SO_TIME_OFFSET);
            (HI_VOID)SO_ClearNode(pstMember, pfnGetPts, pstMember->pfnOnClear);

            return HI_SUCCESS;
        }
    }
    (HI_VOID)SO_ClearNode(pstMember, pfnGetPts, pstMember->pfnOnClear);

    if (NULL != pfnOnDraw)
    {
        /* use pfnOnDraw first */

        (HI_VOID)pfnOnDraw(pstMember->u32DrawUserData, pstSoInfo, NULL);
    }
    else
    {
        /* not support */

        (HI_VOID)SO_DrawSubtitle(pstSoInfo);
    }

    /* insert node into clear list */

    if (bClearSub)
    {
        SO_InsertToClearList(pstMember, pstSoInfo, /*s64CurNodePts*/s64CurPts, u32Duration);
    }

#if 0
    /* clear node from list */
    if (pstMember->u32WriteIndx > pstMember->u32ReadIndx)
    {
        u32Duration = pstMember->astClearNodeList[pstMember->u32ReadIndx].u32Duration;
        s64NodePts  = pstMember->astClearNodeList[pstMember->u32ReadIndx].s64NodePts;

        (HI_VOID)pfnGetPts(pstMember->u32PtsUserData, &s64CurPts);

        if (HI_UNF_SO_NO_PTS != (HI_U32)s64CurPts
            && (s64CurPts - s64NodePts >= u32Duration - SO_TIME_OFFSET || u32Duration < SO_TIME_OFFSET))
        {
            /* clear this subtitle */

            if (NULL != pfnOnClear)
            {
                (HI_VOID)pfnOnClear(pstMember->u32DrawUserData,
                    (HI_VOID*)&pstMember->astClearNodeList[pstMember->u32ReadIndx].stClearPos);
            }

            pstMember->u32ReadIndx++;
        }
    }
#endif
#if 0
    /* clear node from list */
    s32DisTotalTime = 0;

    while ((u32Duration >= SO_TIME_OFFSET) && ((HI_U32)s32DisTotalTime < (u32Duration - SO_TIME_OFFSET)))
    {
        if (HI_TRUE == pstMember->bThreadExit || HI_TRUE == pstMember->bQueueReset)
        {
            //pstMember->bQueueReset = HI_FALSE;
            break;
        }

        /* check the time of outputting next subtitle */

        (HI_VOID)pfnGetPts(pstMember->u32PtsUserData, &s64CurPts);
        s32Ret = SO_QueueGetNodeInfoNotDel(pstMember->queuehdl, &stNextSubInfo);
        (HI_VOID)SO_GetNodePts(&stNextSubInfo, &s64NodePts, &u32NodeDuration);
        s64NodePts += pstMember->s64PtsOffset;

        if ((HI_SUCCESS == s32Ret) && (s64NodePts - s64CurPts <= SO_TIME_OFFSET))
        {
            break;
        }

        SO_SLEEP(SO_TIME_OFFSET);
        s32DisTotalTime += SO_TIME_OFFSET;
    }

    if (NULL != pfnOnClear)
    {
        (HI_VOID)pfnOnClear(pstMember->u32DrawUserData);
    }
#endif

    return HI_SUCCESS;
}

static HI_VOID* SO_ThreadMainFunction(HI_VOID *pArg)
{
    HI_S32  s32Ret = HI_SUCCESS;
    HI_UNF_SO_GETPTS_FN  pfnGetPts = NULL;
    HI_UNF_SO_ONDRAW_FN  pfnOnDraw = NULL;
    HI_UNF_SO_ONCLEAR_FN pfnOnClear = NULL;

    SO_INFO_S stSubInfo;
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)pArg;

    if (NULL == pstMember)
    {
        return NULL;
    }

    for (;;)
    {
        if (HI_TRUE == pstMember->bThreadExit)
        {
            break;
        }

        SO_QUEUE_RESET_LOCK();

        if (HI_TRUE == pstMember->bQueueReset)
        {
            if (pstMember->s64ResetPts)
            {
                (HI_VOID)SO_QueueReset_ByPts(pstMember->queuehdl, pstMember->s64ResetPts);
                pstMember->s64ResetPts = 0;
            }
            else
            {
                (HI_VOID)SO_QueueReset(pstMember->queuehdl);
            }
            pstMember->bQueueReset = HI_FALSE;
            pstMember->u32ReadIndx = 0;
            pstMember->u32WriteIndx = 0;
            SO_MEMSET(pstMember->astClearNodeList, 0, sizeof(SO_CLEAR_NODE_S) * SO_QUEUE_MAX_CLEAR_NODE_NUM);

            /* if reset clear list, insert a empty node */

            stSubInfo.eType = HI_UNF_SUBTITLE_BUTT;
            SO_InsertToClearList(pstMember, &stSubInfo, 0, SO_TIME_OFFSET);
        }

        SO_QUEUE_RESET_UNLOCK();

        SO_CALLBACK_LOCK();
        pfnGetPts  = pstMember->pfnGetPts;
        pfnOnDraw  = pstMember->pfnOnDraw;
        pfnOnClear = pstMember->pfnOnClear;
        SO_CALLBACK_UNLOCK();
        (HI_VOID)SO_ClearNode(pstMember, pfnGetPts, pfnOnClear);

        SO_MEMSET(&stSubInfo, 0, sizeof(stSubInfo));
        s32Ret = SO_QueueGet(pstMember->queuehdl, &stSubInfo);

        if (HI_SUCCESS != s32Ret)
        {
            SO_SLEEP(SO_TRHEAD_SLEEP_TIME);
            continue;
        }

        /* if not set pfnGetPts, skip all subtitle */

        if (NULL == pfnGetPts)
        {
            (HI_VOID)SO_QueueFree(pstMember->queuehdl, &stSubInfo);
            SO_SLEEP(SO_TRHEAD_SLEEP_TIME);
            continue;
        }

        SO_QUEUE_RESET_LOCK();
        (HI_VOID)SO_SyncOutput(pstMember, pfnGetPts, pfnOnDraw, pfnOnClear, &stSubInfo);
        (HI_VOID)SO_QueueFree(pstMember->queuehdl, &stSubInfo);
        SO_QUEUE_RESET_UNLOCK();
    }

    return NULL;
}

HI_S32 HI_UNF_SO_Init(HI_VOID)
{
    if (HI_TRUE == s_bSoInit)
    {
        return HI_SUCCESS;
    }

    s_bSoInit = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SO_DeInit(HI_VOID)
{
    if (HI_FALSE == s_bSoInit)
    {
        return HI_SUCCESS;
    }

    s_bSoInit = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SO_Create(HI_HANDLE *phdl)
{
    HI_S32 s32Ret = 0;
    SO_MEMBER_S *pstMember = NULL;

    SO_RETURN(HI_FALSE == s_bSoInit, HI_FAILURE, "");
    SO_RETURN(NULL == phdl, HI_FAILURE, "");

    pstMember = (SO_MEMBER_S*)SO_MALLOC(sizeof(SO_MEMBER_S));
    SO_RETURN(NULL == pstMember, HI_FAILURE, "");

    SO_MEMSET(pstMember, 0, sizeof(SO_MEMBER_S));

    /* create the subtitle queue */

    s32Ret = SO_QueueInit(HI_UNF_SO_MAX_BUFFER_SIZE, HI_UNF_SO_MAX_NODE_NUM, &pstMember->queuehdl);
    SO_CALL_RETURN(HI_SUCCESS != s32Ret, SO_FREE(pstMember), HI_FAILURE);

    pstMember->bThreadExit = HI_FALSE;
    pstMember->bQueueReset = HI_FALSE;
    pstMember->s64ResetPts = 0;
    pstMember->s64PtsOffset = 0;
    pstMember->u32ReadIndx  = 0;
    pstMember->u32WriteIndx = 0;
    pstMember->u32IntervalMs = 0;

    (HI_VOID)pthread_mutex_init(&pstMember->stQueueResetMutex, NULL);
    (HI_VOID)pthread_mutex_init(&pstMember->stMutex, NULL);
    (HI_VOID)pthread_attr_init(&pstMember->struAttr);

    /* create the main task */

    s32Ret = pthread_create(&pstMember->hTaskId, &pstMember->struAttr,
                            SO_ThreadMainFunction, (HI_VOID*)pstMember);

    if (HI_SUCCESS != s32Ret)
    {
        (HI_VOID)SO_QueueDeinit(pstMember->queuehdl);
        pthread_attr_destroy(&pstMember->struAttr);
        pthread_mutex_destroy(&pstMember->stMutex);
        pthread_mutex_destroy(&pstMember->stQueueResetMutex);
        SO_FREE(pstMember);
        return HI_FAILURE;
    }

    *phdl = (HI_HANDLE)pstMember;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SO_Destroy(HI_HANDLE handle)
{
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;

    SO_RETURN(NULL == pstMember, HI_FAILURE, "");

    pstMember->bQueueReset = HI_TRUE;
    pstMember->bThreadExit = HI_TRUE;
    pthread_join(pstMember->hTaskId, NULL);

    pthread_attr_destroy(&pstMember->struAttr);
    pthread_mutex_destroy(&pstMember->stMutex);
    pthread_mutex_destroy(&pstMember->stQueueResetMutex);

    (HI_VOID)SO_QueueDeinit(pstMember->queuehdl);
    SO_FREE(pstMember);

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SO_RegGetPtsCb(HI_HANDLE handle, HI_UNF_SO_GETPTS_FN pfnCallback, HI_U32 u32UserData)
{
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;

    SO_RETURN((NULL == pstMember || NULL == pfnCallback), HI_FAILURE, "");

    SO_CALLBACK_LOCK();
    pstMember->pfnGetPts      = pfnCallback;
    pstMember->u32PtsUserData = u32UserData;
    SO_CALLBACK_UNLOCK();;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SO_RegOnDrawCb(HI_HANDLE handle, HI_UNF_SO_ONDRAW_FN pfnOnDraw,
                                          HI_UNF_SO_ONCLEAR_FN pfnOnClear, HI_U32 u32UserData)
{
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;

    SO_RETURN((NULL == pstMember || NULL == pfnOnDraw), HI_FAILURE, "");

    SO_CALLBACK_LOCK();
    pstMember->pfnOnDraw       = pfnOnDraw;
    pstMember->pfnOnClear      = pfnOnClear;
    pstMember->u32DrawUserData = u32UserData;
    SO_CALLBACK_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SO_SetDrawSurface(HI_HANDLE handle, HI_HANDLE hSurfaceHandle)
{
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;

    SO_RETURN((NULL == pstMember || 0 == hSurfaceHandle), HI_FAILURE, "");

    SO_CALLBACK_LOCK();
    pstMember->hSurface = hSurfaceHandle;
    SO_CALLBACK_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SO_SetFont(HI_HANDLE handle, HI_HANDLE hFont)
{
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;

    SO_RETURN(NULL == pstMember, HI_FAILURE, "");

    pstMember->u32Font = (HI_HANDLE)hFont;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SO_SetOffset(HI_HANDLE handle, HI_S64 s64OffsetMs)
{
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;

    SO_RETURN(NULL == pstMember, HI_FAILURE, "");

    pstMember->s64PtsOffset = s64OffsetMs;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SO_SetColor(HI_HANDLE handle, HI_U32 u32Color)
{
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;

    SO_RETURN(NULL == pstMember, HI_FAILURE, "");

    pstMember->u32Color = u32Color;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SO_SetPos(HI_HANDLE handle, HI_U32 u32x, HI_U32 u32y)
{
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;

    SO_RETURN(NULL == pstMember, HI_FAILURE, "");

    pstMember->x = u32x;
    pstMember->y = u32y;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SO_GetSubNumInBuff(HI_HANDLE handle, HI_U32 *pu32SubNum)
{
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;

    SO_RETURN(NULL == pstMember || NULL == pu32SubNum, HI_FAILURE, "");

    *pu32SubNum = SO_QueueNum(pstMember->queuehdl);

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SO_ResetSubBuf(HI_HANDLE handle)
{
    HI_S32 s32Ret = 0;
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;
    HI_U32 i = 0;

    SO_RETURN(NULL == pstMember, HI_FAILURE, "");

    //SO_QUEUE_RESET_LOCK();
    pstMember->bQueueReset = HI_TRUE;
    pstMember->s64LastPts = 0;
    //SO_QUEUE_RESET_UNLOCK();

    while (i < SO_QUEUE_RESET_CHECK_TIME)
    {
        if (HI_FALSE == pstMember->bQueueReset)
        {
            break;
        }

        i++;
        SO_SLEEP(SO_TIME_OFFSET);
    }

    return s32Ret;
}

HI_S32 HI_UNF_SO_ResetSubBuf_ByPts(HI_HANDLE handle, HI_S64 s64Pts)
{
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;

    SO_RETURN(NULL == pstMember, HI_FAILURE, "");

    pstMember->s64ResetPts = s64Pts;
    return HI_UNF_SO_ResetSubBuf(handle);
}

HI_S32 HI_UNF_SO_SendData(HI_HANDLE handle, const HI_UNF_SO_SUBTITLE_INFO_S *pstSubInfo, HI_U32 u32TimeOut)
{
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;

    SO_RETURN((NULL == pstMember || NULL == pstSubInfo), HI_FAILURE, "");

    return SO_QueuePut(pstMember->queuehdl, (const SO_INFO_S*)pstSubInfo);
}

HI_S32 HI_UNF_SO_SetMaxInterval(HI_HANDLE handle, HI_U32 u32IntervalMs )
{
    SO_MEMBER_S *pstMember = (SO_MEMBER_S*)handle;

    SO_RETURN(NULL == pstMember, HI_FAILURE, "");

    pstMember->u32IntervalMs = u32IntervalMs;

    return HI_SUCCESS;
}

