#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "hi_type.h"

#include "hi_unf_subt.h"
#include "subtitle_debug.h"
#include "subtitle_data.h"
#include "subtitle_parse.h"
#include "scte_subt_data.h"
#include "scte_subt_display.h"
#include "scte_subt_parse.h"

static const HI_CHAR s_szSUBTVersion[] __attribute__((used)) = "SDK_VERSION:["\
                            MKMARCOTOSTR(SDK_VERSION)"] Build Time:["\
                            __DATE__", "__TIME__"]";

typedef struct tagSUBT_LOCAL_PARAM_S
{
    HI_HANDLE hDataParse;
    HI_HANDLE hDataRecv[SUBT_ITEM_MAX_NUM];

    HI_HANDLE hScteParse;
    HI_HANDLE hScteData;
    HI_HANDLE hScteDisplay;

    pthread_mutex_t stSubtMutex;

    HI_UNF_SUBT_ITEM_S astItems[SUBT_ITEM_MAX_NUM]; /* all items of subtitle */
    HI_U8  u8SubtItemNum;            /* the total item number */
    HI_UNF_SUBT_CALLBACK_FN pfnCallback;
    HI_U32 u32UserData;
    HI_UNF_SUBT_ITEM_S  stOutputItem;

    HI_UNF_SUBT_DATA_TYPE_E enDataType;
}SUBT_LOCAL_PARAM_S;

static HI_HANDLE s_ahSubt[SUBT_INSTANCE_MAX_NUM];
static HI_BOOL   s_bSubtInit = HI_FALSE;

#define CheckInit() if (HI_FALSE == s_bSubtInit) { \
        HI_ERR_SUBT("Not Init\n"); \
        return HI_FAILURE; \
    }

#define CheckHandle(pstParam) do { \
        for (i = 0; i < SUBT_INSTANCE_MAX_NUM; i++) { \
            if (s_ahSubt[i] == (HI_HANDLE)pstParam) { \
                break; \
            } \
        } \
        if (i >= SUBT_INSTANCE_MAX_NUM) { \
            HI_ERR_SUBT("handle invalid!\n"); \
            return HI_FAILURE; \
        } \
    } while (0)


static HI_S32 HI_UNF_SUBT_Callback(HI_U32 u32UserData, HI_VOID *pstDisplayDate);

static HI_HANDLE FindDataRecv(HI_HANDLE hSubt, HI_U32 u32SubtPID, HI_U16 u16PageID, HI_U16 u16AncillaryID)
{
    SUBT_LOCAL_PARAM_S* pstParam = (SUBT_LOCAL_PARAM_S*)hSubt;
    HI_U8  i = 0;

    if (!u32SubtPID)
    {
        return SUBT_INVALID_HANDLE;
    }

    for (i = 0; i < pstParam->u8SubtItemNum; i++)
    {
        if (pstParam->astItems[i].u32SubtPID == u32SubtPID
            && pstParam->astItems[i].u16PageID == u16PageID
            && pstParam->astItems[i].u16AncillaryID == u16AncillaryID)
        {
            return pstParam->hDataRecv[i];
        }
    }

    return SUBT_INVALID_HANDLE;
}


HI_S32 HI_UNF_SUBT_Init(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_FALSE == s_bSubtInit)
    {
        s32Ret = SUBT_DataParse_Init();
        s32Ret |= SUBT_DataRecv_Init();
        s32Ret |= SCTE_SUBT_Data_Init();
        s32Ret |= SCTE_SUBT_Parse_Init();
        s32Ret |= SCTE_SUBT_Display_Init();
        memset(s_ahSubt, 0, sizeof(s_ahSubt));
        s_bSubtInit = HI_TRUE;
    }

    return s32Ret;
}

HI_S32 HI_UNF_SUBT_DeInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_TRUE == s_bSubtInit)
    {
        HI_U8 i = 0;

        s32Ret = SUBT_DataParse_DeInit();
        s32Ret |= SUBT_DataRecv_DeInit();
        s32Ret |= SCTE_SUBT_Data_DeInit();
        s32Ret |= SCTE_SUBT_Parse_DeInit();
        s32Ret |= SCTE_SUBT_Display_DeInit();

        for (i = 0; i < SUBT_INSTANCE_MAX_NUM; i++)
        {
            if (s_ahSubt[i])
            {
                s32Ret |= HI_UNF_SUBT_Destroy(s_ahSubt[i]);
            }
        }
        memset(s_ahSubt, 0, sizeof(s_ahSubt));
        s_bSubtInit = HI_FALSE;
    }

    return s32Ret;
}


HI_S32 HI_UNF_SUBT_Create(HI_UNF_SUBT_PARAM_S *pstSubtParam, HI_HANDLE *phSubt)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U16 u16PageID = 0;
    HI_U16 u16AncillaryID = 0;
    HI_U8  i = 0;
    SUBT_LOCAL_PARAM_S* pstParam = HI_NULL;

    if (HI_NULL == phSubt || HI_NULL == pstSubtParam)
    {
        HI_ERR_SUBT("params invalid\n");

        return HI_FAILURE;
    }

    CheckInit();

    *phSubt = 0;

    if (pstSubtParam->u8SubtItemNum > SUBT_ITEM_MAX_NUM)
    {
        HI_ERR_SUBT("item num > %d\n", SUBT_ITEM_MAX_NUM);

        return HI_FAILURE;
    }

    pstParam = (SUBT_LOCAL_PARAM_S*)malloc(sizeof(SUBT_LOCAL_PARAM_S));
    if (HI_NULL == pstParam)
    {
        HI_ERR_SUBT("malloc failure...\n");

        return HI_FAILURE;
    }

    memset(pstParam, 0, sizeof(SUBT_LOCAL_PARAM_S));
    pstParam->pfnCallback = pstSubtParam->pfnCallback;
    pstParam->u32UserData = pstSubtParam->u32UserData;
    if (pthread_mutex_init(&pstParam->stSubtMutex, HI_NULL))
    {
        free((void*)pstParam);
        return HI_FAILURE;        
    }

    switch(pstSubtParam->enDataType)
    {
        case HI_UNF_SUBT_SCTE:
            pstParam->enDataType = HI_UNF_SUBT_SCTE;
            s32Ret = SCTE_SUBT_Display_Create(HI_UNF_SUBT_Callback, (HI_U32)pstParam, &pstParam->hScteDisplay);
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_SUBT("failed to SCTE_SUBT_Display_Create\n");

                goto ERROR;
            }

            s32Ret = SCTE_SUBT_Parse_Create(pstParam->hScteDisplay, &pstParam->hScteParse);
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_SUBT("failed to SCTE_SUBT_Parse_Create\n");

                goto ERROR;
            }

            s32Ret = SCTE_SUBT_Data_Create(pstParam->hScteParse, &pstParam->hScteData);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_SUBT("failed to SCTE_SUBT_Data_Create\n");

                goto ERROR;
            }

            HI_INFO_SUBT("success with handle:0x%08x!\n", *phSubt);

            break;
        case HI_UNF_SUBT_DVB:
        default:
            pstParam->enDataType = HI_UNF_SUBT_DVB;
            memcpy(pstParam->astItems, pstSubtParam->astItems, sizeof(HI_UNF_SUBT_ITEM_S)*SUBT_ITEM_MAX_NUM);
            pstParam->u8SubtItemNum = pstSubtParam->u8SubtItemNum;

            s32Ret = SUBT_DataParse_Create(&pstParam->hDataParse);
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_SUBT("failed to SUBT_DataParse_Create\n");

                goto ERROR;
            }
            s32Ret |= SUBT_DataParse_Update(pstParam->hDataParse, HI_UNF_SUBT_Callback, (HI_U32)pstParam);
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_SUBT("failed to SUBT_DataParse_Update\n");

                goto ERROR;
            }

            for (i = 0; i < pstParam->u8SubtItemNum; i++)
            {
                u16PageID = pstParam->astItems[i].u16PageID;
                u16AncillaryID = pstParam->astItems[i].u16AncillaryID;
                s32Ret |= SUBT_DataRecv_Create(u16PageID, u16AncillaryID, &pstParam->hDataRecv[i]);
            }
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_SUBT("failed to SUBT_DataRecv_Create\n");

                goto ERROR;
            }

            HI_INFO_SUBT("success with handle:0x%08x!\n", *phSubt);

            break;
    }

    for (i = 0; i < SUBT_INSTANCE_MAX_NUM; i++)
    {
        if (0 == s_ahSubt[i])
        {
            s_ahSubt[i] = (HI_HANDLE)pstParam;
            break;
        }
    }
    if (i >= SUBT_INSTANCE_MAX_NUM)
    {
        HI_ERR_SUBT("instance num > %d\n", SUBT_INSTANCE_MAX_NUM);

        goto ERROR;
    }

    *phSubt = (HI_HANDLE)pstParam;
    return HI_SUCCESS;


ERROR:
    if (pstParam)
    {
        (HI_VOID)pthread_mutex_destroy(&pstParam->stSubtMutex);
        for (i = 0; i < pstParam->u8SubtItemNum; i++)
        {
            if (pstParam->hDataRecv[i])
            {
                s32Ret = SUBT_DataRecv_Destroy(pstParam->hDataRecv[i]);
            }
        }

        if (pstParam->hDataParse)
        {
            s32Ret = SUBT_DataParse_Destroy(pstParam->hDataParse);
        }

        if (pstParam->hScteData)
        {
            s32Ret = SCTE_SUBT_Data_Destroy(pstParam->hScteData);
        }
        if (pstParam->hScteParse)
        {
            s32Ret = SCTE_SUBT_Parse_Destroy(pstParam->hScteParse);
        }
        if (pstParam->hScteDisplay)
        {
            s32Ret = SCTE_SUBT_Display_Destroy(pstParam->hScteDisplay);
        }

        free((void*)pstParam);
    }

    *phSubt = 0;

    return HI_FAILURE;
}

HI_S32 HI_UNF_SUBT_Destroy(HI_HANDLE hSubt)
{
    HI_S32 s32Ret = HI_SUCCESS;
    SUBT_LOCAL_PARAM_S* pstParam = (SUBT_LOCAL_PARAM_S*)hSubt;
    HI_U8 i = 0;

    if (SUBT_INVALID_HANDLE == hSubt)
    {
        HI_ERR_SUBT("param invalid!\n");

        return HI_FAILURE;
    }

    CheckInit();
    CheckHandle(pstParam);

    for (i = 0; i < SUBT_INSTANCE_MAX_NUM; i++)
    {
        if (s_ahSubt[i] == (HI_HANDLE)pstParam)
        {
            s_ahSubt[i] = 0;
            break;
        }
    }

    for (i = 0; i < pstParam->u8SubtItemNum; i++)
    {
        if (pstParam->hDataRecv[i])
        {
            s32Ret |= SUBT_DataRecv_Destroy(pstParam->hDataRecv[i]);
            pstParam->hDataRecv[i] = 0;
        }
    }

    if (pstParam->hDataParse)
    {
        s32Ret |= SUBT_DataParse_Destroy(pstParam->hDataParse);
        pstParam->hDataParse = 0;
    }

    if (pstParam->hScteData)
    {
        s32Ret = SCTE_SUBT_Data_Destroy(pstParam->hScteData);
        pstParam->hScteData = 0;
    }

    if (pstParam->hScteParse)
    {
        s32Ret |= SCTE_SUBT_Parse_Destroy(pstParam->hScteParse);
        pstParam->hScteParse = 0;
    }

    if (pstParam->hScteDisplay)
    {
        s32Ret |= SCTE_SUBT_Display_Destroy(pstParam->hScteDisplay);
        pstParam->hScteDisplay = 0;
    }

    if (s32Ret != HI_SUCCESS)
    {
        HI_WARN_SUBT("failed to SUBT_DataParse_Destroy...\n");
    }

    (HI_VOID)pthread_mutex_destroy(&pstParam->stSubtMutex);

    free((void*)pstParam);

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SUBT_SwitchContent(HI_HANDLE hSubt, HI_UNF_SUBT_ITEM_S *pstSubtItem)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 i = 0;

    SUBT_LOCAL_PARAM_S* pstParam = (SUBT_LOCAL_PARAM_S*)hSubt;

    if (SUBT_INVALID_HANDLE == hSubt || HI_NULL == pstSubtItem)
    {
        HI_ERR_SUBT("param invalid!\n");

        return HI_FAILURE;
    }

    if(HI_UNF_SUBT_DVB != pstParam->enDataType)
    {
        return HI_SUCCESS;
    }

    CheckInit();
    CheckHandle(pstParam);

    pthread_mutex_lock(&pstParam->stSubtMutex);

    s32Ret = SUBT_DataParse_Reset(pstParam->hDataParse, HI_TRUE);

    if (pstParam->stOutputItem.u32SubtPID != pstSubtItem->u32SubtPID
        || pstParam->stOutputItem.u16PageID != pstSubtItem->u16PageID
        || pstParam->stOutputItem.u16AncillaryID != pstSubtItem->u16AncillaryID)
    {

        HI_HANDLE hDataRecv = FindDataRecv(hSubt, pstParam->stOutputItem.u32SubtPID, pstParam->stOutputItem.u16PageID,
                                    pstParam->stOutputItem.u16AncillaryID);
        if (hDataRecv != SUBT_INVALID_HANDLE)
        {
            s32Ret |= SUBT_DataRecv_UnbindParsing(hDataRecv);
        }


        hDataRecv = FindDataRecv(hSubt, pstSubtItem->u32SubtPID, pstSubtItem->u16PageID, pstSubtItem->u16AncillaryID);
        if (SUBT_INVALID_HANDLE != hDataRecv)
        {
            s32Ret |= SUBT_DataRecv_BindParsing(hDataRecv, pstParam->hDataParse);
            s32Ret |= SUBT_DataRecv_Redo(hDataRecv);
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_SUBT("failed to SUBT_DataRecv_BindParsing\n");
                pthread_mutex_unlock(&pstParam->stSubtMutex);
                return HI_FAILURE;
            }
        }
        else
        {
            HI_ERR_SUBT("subtitle item invalid!\n");
            pthread_mutex_unlock(&pstParam->stSubtMutex);
            return HI_FAILURE;
        }

        pstParam->stOutputItem = *pstSubtItem;

    }

    pthread_mutex_unlock(&pstParam->stSubtMutex);

    return s32Ret;
}

HI_S32 HI_UNF_SUBT_Reset(HI_HANDLE hSubt)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U8  i = 0;
    SUBT_LOCAL_PARAM_S* pstParam = (SUBT_LOCAL_PARAM_S*)hSubt;

    if (SUBT_INVALID_HANDLE == hSubt)
    {
        HI_ERR_SUBT("param invalid!\n");

        return HI_FAILURE;
    }

    CheckInit();
    CheckHandle(pstParam);

    pthread_mutex_lock(&pstParam->stSubtMutex);
    switch(pstParam->enDataType)
    {
        case HI_UNF_SUBT_DVB:

            s32Ret = SUBT_DataParse_Reset(pstParam->hDataParse, HI_TRUE);
            for (i = 0; i < pstParam->u8SubtItemNum; i++)
            {
                s32Ret |= SUBT_DataRecv_Reset(pstParam->hDataRecv[i], HI_TRUE);
                if (s32Ret != HI_SUCCESS)
                {
                    HI_WARN_SUBT("failed to call SUBT_DataRecv_Reset, result is %d...!\n", s32Ret);
                }
            }
            break;
        case HI_UNF_SUBT_SCTE:
            s32Ret = SCTE_SUBT_Data_Reset(pstParam->hScteData);
            if(HI_SUCCESS != s32Ret)
            {
                HI_WARN_SUBT("reset data failed!\n");
            }
            break;
        default:
            break;
    }
    pthread_mutex_unlock(&pstParam->stSubtMutex);

    return s32Ret;
}

HI_S32 HI_UNF_SUBT_Update(HI_HANDLE hSubt, HI_UNF_SUBT_PARAM_S *pstSubtParam)
{
    HI_U8  i = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U16 u16PageID = 0;
    HI_U16 u16AncillaryID = 0;
    SUBT_LOCAL_PARAM_S* pstParam = (SUBT_LOCAL_PARAM_S*)hSubt;

    if (SUBT_INVALID_HANDLE == hSubt || HI_NULL == pstSubtParam)
    {
        HI_ERR_SUBT("params invalid\n");

        return HI_FAILURE;
    }

    CheckInit();
    CheckHandle(pstParam);

    if (pstSubtParam->u8SubtItemNum > SUBT_ITEM_MAX_NUM)
    {
        HI_ERR_SUBT("pstSubtParam item num > %d\n", SUBT_ITEM_MAX_NUM);

        return HI_FAILURE;
    }

    if (pstParam->u8SubtItemNum > SUBT_ITEM_MAX_NUM)
    {
        HI_ERR_SUBT("pstParam item num > %d\n", SUBT_ITEM_MAX_NUM);

        return HI_FAILURE;
    }

    if(HI_UNF_SUBT_DVB != pstParam->enDataType)
    {
        return HI_SUCCESS;
    }

    pthread_mutex_lock(&pstParam->stSubtMutex);

    HI_HANDLE hDataRecv = FindDataRecv(hSubt, pstParam->stOutputItem.u32SubtPID, pstParam->stOutputItem.u16PageID,
                                    pstParam->stOutputItem.u16AncillaryID);
    if (hDataRecv != SUBT_INVALID_HANDLE)
    {
        s32Ret |= SUBT_DataRecv_UnbindParsing(hDataRecv);
    }
    memset(&pstParam->stOutputItem, 0, sizeof(pstParam->stOutputItem));

    if (pstParam->u8SubtItemNum >= pstSubtParam->u8SubtItemNum)
    {
        for (i = pstSubtParam->u8SubtItemNum; i < pstParam->u8SubtItemNum; i++)
        {
            if (pstParam->hDataRecv[i])
            {
                s32Ret |= SUBT_DataRecv_Destroy(pstParam->hDataRecv[i]);
                pstParam->hDataRecv[i] = 0;
            }
        }
    }
    else
    {
        for (i = pstParam->u8SubtItemNum; i < pstSubtParam->u8SubtItemNum; i++)
        {
            s32Ret |= SUBT_DataRecv_Create(0, 0, &pstParam->hDataRecv[i]);
        }
        if (s32Ret != HI_SUCCESS)
        {
            HI_WARN_SUBT("failed to SUBT_DataRecv_Create\n");
        }
    }

    memcpy(pstParam->astItems, pstSubtParam->astItems, sizeof(HI_UNF_SUBT_ITEM_S)*SUBT_ITEM_MAX_NUM);
    pstParam->u8SubtItemNum = pstSubtParam->u8SubtItemNum;
    pstParam->pfnCallback = pstSubtParam->pfnCallback;
    pstParam->u32UserData = pstSubtParam->u32UserData;

    for (i = 0; i < pstParam->u8SubtItemNum; i++)
    {
        u16PageID = pstParam->astItems[i].u16PageID;
        u16AncillaryID = pstParam->astItems[i].u16AncillaryID;

        s32Ret |= SUBT_DataRecv_Updata(pstParam->hDataRecv[i], u16PageID, u16AncillaryID);
        if (s32Ret != HI_SUCCESS)
        {
            HI_WARN_SUBT("failed to SUBT_DataRecv_Updata\n");
        }
    }

    pthread_mutex_unlock(&pstParam->stSubtMutex);

    return HI_SUCCESS;
}


HI_S32 HI_UNF_SUBT_InjectData(HI_HANDLE hSubt, HI_U32 u32SubtPID, HI_U8* pu8Data, HI_U32 u32DataSize)
{
    HI_U8 i = 0;
    HI_S32 s32Ret = HI_FAILURE;
    SUBT_LOCAL_PARAM_S* pstParam = (SUBT_LOCAL_PARAM_S*)hSubt;

    if (SUBT_INVALID_HANDLE == hSubt || HI_NULL == pu8Data || 0 == u32DataSize)
    {
        HI_ERR_SUBT("param invalid!\n");

        return HI_FAILURE;
    }

    CheckInit();
    CheckHandle(pstParam);

    pthread_mutex_lock(&pstParam->stSubtMutex);

    switch(pstParam->enDataType)
    {
        case HI_UNF_SUBT_DVB:
            for (i = 0; i < pstParam->u8SubtItemNum; i++)
            {
                if (pstParam->astItems[i].u32SubtPID == u32SubtPID)
                {
                    if (pstParam->hDataRecv[i])
                    {
                        s32Ret = SUBT_DataRecv_Inject(pstParam->hDataRecv[i], pu8Data, u32DataSize);
                        if (s32Ret != HI_SUCCESS)
                        {
                            HI_ERR_SUBT("failed to SUBT_DataRecv_Inject\n");
                        }
                    }
                }
            }
            break;
        case HI_UNF_SUBT_SCTE:
            s32Ret = SCTE_SUBT_Data_Inject(pstParam->hScteData, pu8Data, u32DataSize);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_SUBT("failed to SCTE_SUBT_Data_Inject\n");
            }
            break;
        default:
            break;
    }

    pthread_mutex_unlock(&pstParam->stSubtMutex);

    return s32Ret;
}

static HI_S32 HI_UNF_SUBT_Callback(HI_U32 u32UserData, HI_VOID *pstDisplayDate)
{
    HI_U8 i = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    SUBT_LOCAL_PARAM_S *pstParam = (SUBT_LOCAL_PARAM_S*)u32UserData;
    HI_UNF_SUBT_DATA_S stSubtData;

    if (pstParam == HI_NULL ||pstDisplayDate == HI_NULL)
    {
        HI_ERR_SUBT("parameter is invalid...\n");

        return HI_FAILURE;
    }

    CheckHandle(pstParam);

    memset(&stSubtData, 0, sizeof(HI_UNF_SUBT_DATA_S));

    switch(pstParam->enDataType)
    {
    case HI_UNF_SUBT_DVB:
        {
            SUBT_Display_ITEM_S *pstDisplayItem = (SUBT_Display_ITEM_S *)pstDisplayDate;

            switch(pstDisplayItem->u8DataType)
            {
                case SUBT_OBJ_TYPE_BITMAP:
                    stSubtData.enDataType = HI_UNF_SUBT_TYPE_BITMAP;
                    break;
                case SUBT_OBJ_TYPE_CHARACTER:
                case SUBT_OBJ_TYPE_STRING:
                    stSubtData.enDataType = HI_UNF_SUBT_TYPE_TEXT;
                    break;
                default:
                    stSubtData.enDataType = HI_UNF_SUBT_TYPE_BUTT;
                    break;
            }

            stSubtData.u32x = pstDisplayItem->u16XPos;
            stSubtData.u32y = pstDisplayItem->u16YPos;
            stSubtData.u32w = pstDisplayItem->u16Width;
            stSubtData.u32h = pstDisplayItem->u16Heigth;
            stSubtData.u32PTS = pstDisplayItem->u32PTS;
            stSubtData.u32Duration = pstDisplayItem->u32Timeout;

            stSubtData.u32BitWidth = pstDisplayItem->u8BitDepth;
            stSubtData.u32PaletteItem = pstDisplayItem->u16PaletteItem;

            stSubtData.pvPalette = pstDisplayItem->pvRegionClut;
            stSubtData.u32DataLen = pstDisplayItem->u32RegionDataSize;
            stSubtData.pu8SubtData = pstDisplayItem->pu8ShowData;
            stSubtData.enPageState = (HI_UNF_SUBT_PAGE_STATE_E)(pstDisplayItem->enPageState);
            stSubtData.u32DisplayWidth = pstDisplayItem->u16DisplayWidth;
            stSubtData.u32DisplayHeight = pstDisplayItem->u16DisplayHeight;
        }
        break;

    case HI_UNF_SUBT_SCTE:
        {
            SCTE_SUBT_DISPALY_PARAM_S *pstDisplayParam = (SCTE_SUBT_DISPALY_PARAM_S *)pstDisplayDate;;

            stSubtData.enDataType = HI_UNF_SUBT_TYPE_BITMAP;
            stSubtData.u32x = pstDisplayParam->u32x;
            stSubtData.u32y = pstDisplayParam->u32y;
            stSubtData.u32w = pstDisplayParam->u32w;
            stSubtData.u32h = pstDisplayParam->u32h;

            stSubtData.u32PTS = pstDisplayParam->u32PTS;
            stSubtData.u32Duration = pstDisplayParam->u32Duration;

            stSubtData.u32DataLen  = pstDisplayParam->u32DataLen;
            stSubtData.pu8SubtData = pstDisplayParam->pu8SubtData;

            stSubtData.u32BitWidth = pstDisplayParam->u32BitWidth;
            stSubtData.u32PaletteItem = 0;
            stSubtData.pvPalette = HI_NULL;

            if(SCTE_SUBT_DISP_NORMAL == pstDisplayParam->enDISP)
            {
                stSubtData.enPageState = HI_UNF_SUBT_PAGE_NORMAL_CASE;
            }
            else
            {
                stSubtData.enPageState = HI_UNF_SUBT_PAGE_ACQUISITION_POINT;
            }
            stSubtData.u32DisplayWidth = pstDisplayParam->u32DisplayWidth;
            stSubtData.u32DisplayHeight = pstDisplayParam->u32DisplayHeight;
        }
        break;

    default:
        break;
    }

    if (pstParam->pfnCallback)
    {
        s32Ret = pstParam->pfnCallback(pstParam->u32UserData, &stSubtData);
        if (HI_SUCCESS != s32Ret)
        {
            HI_WARN_SUBT("failed to callback funcion\n");
        }
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_SUBT_RegGetPtsCb(HI_HANDLE hSubt, HI_UNF_SUBT_GETPTS_FN pfnGetPts, HI_U32 u32UserData)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 i = 0;

    SUBT_LOCAL_PARAM_S* pstParam = (SUBT_LOCAL_PARAM_S*)hSubt;

    if (SUBT_INVALID_HANDLE == hSubt || HI_NULL == pfnGetPts)
    {
        HI_ERR_SUBT("param invalid!\n");

        return HI_FAILURE;
    }

    if (HI_UNF_SUBT_SCTE != pstParam->enDataType)
    {
        return HI_SUCCESS;
    }

    CheckInit();
    CheckHandle(pstParam);

    s32Ret = SCTE_SUBT_Parse_RegGetPtsCb(pstParam->hScteParse, pfnGetPts, u32UserData);

    return s32Ret;
}

