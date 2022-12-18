/*
 *
 *
 *
 *
 *
 *
 */
#ifdef __cplusplus
extern "C" {
#endif

#include "hi_type.h"

typedef enum hiDASH_INVOKE_ID_E
{
    //TODO: + HI_FORMAT_ID_XXX
    HI_DASH_INVOKE_READ             = 200,
    HI_DASH_INVOKE_GET_BANDWIDTH,
    HI_DASH_INVOKE_SET_ID,
    HI_DASH_INVOKE_GET_ID,
    HI_DASH_INVOKE_GET_VIDEO_RATING,
    HI_DASH_INVOKE_GET_AUDIO_RATING,
    HI_DASH_INVOKE_GET_SUBTITLE_RATING,
    HI_DASH_INVOKE_SET_ERRORCODECB,
    HI_DASH_INVOKE_SET_LOG_LEVEL,
    HI_DASH_INVOKE_PRE_CLOSE_FILE,
    HI_DASH_INVOKE_SET_PLAYREADY_EXTRADATA,
    HI_DASH_INVOKE_BUTT,
}HI_DASH_INVOKE_ID_E;

typedef struct{
    HI_S32 s32VidIndex;
    HI_S32 s32AudIndex;
    HI_S32 s32SubIndex;
}HI_DASH_STREAM_INFO_S;

#ifdef __cplusplus
}
#endif
