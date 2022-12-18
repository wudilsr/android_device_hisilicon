#ifndef _ANDROID_HI_MEDIA_DEFINE_H_
#define _ANDROID_HI_MEDIA_DEFINE_H_

//log
#define LOGE ALOGE
#define LOGV ALOGV
#define LOGW ALOGW
#define LOGI ALOGI
#define LOGD ALOGD

//3d
#define DP_STRATEGY_ADAPT_MASK      0x0001
#define DP_STRATEGY_2D_MASK         0x0002
#define DP_STRATEGY_3D_MASK         0x0004
#define DP_STRATEGY_24FPS_MASK      0x0008

#define OUTPUT_MODE_3D              1
#define OUTPUT_MODE_2D              0
#define HIMEDIA_DMX_PORTID          3
#define HIMEDIA_DMX_ID              0

//audio
#define HIMEDIA_DEFAULT_MIXWEIGHT   100
#define HIMEDIA_DEFAULT_SNDPORT     0

#define HIMEDIA_VIRTUAL_SCREEN_W 1280
#define HIMEDIA_VIRTUAL_SCREEN_H 720

#define HIMEDIA_DEFAULT_OUTPUT_X    0
#define HIMEDIA_DEFAULT_OUTPUT_Y    0
#define HIMEDIA_DEFAULT_OUTPUT_W    HIMEDIA_VIRTUAL_SCREEN_W
#define HIMEDIA_DEFAULT_OUTPUT_H    HIMEDIA_VIRTUAL_SCREEN_H
#define HIMEDIA_ASPECTRATIO_WIDTH_MAX 3840
#define HIMEDIA_ASPECTRATIO_HEIGHT_MAX 3840

//video mode
#define HIMEDIAPLAYER_CURVE_DEFAUL  1
#define HIMEDIAPLAYER_RATIO_DEFAUL  1

#define SEPARATE_SYMBOL_OFFSET "::offset="
#define SEPARATE_SYMBOL_LENGTH "::length="
#define SEPARATE_SYMBOL_FD      "::fd="

//window z order define
typedef enum hiMEDIAPLAYER_ZORDER_E
{
    HI_MEDIAPLAYER_ZORDER_MOVETOP = 0,  /**<Move to the top*/ /**<CNcomment:  移到最顶部 */
    HI_MEDIAPLAYER_ZORDER_MOVEUP,       /**<Move up*/ /**<CNcomment:  向上移到 */
    HI_MEDIAPLAYER_ZORDER_MOVEBOTTOM,   /**<Move to the bottom*/ /**<CNcomment:  移到最底部 */
    HI_MEDIAPLAYER_ZORDER_MOVEDOWN,     /**<Move down*/ /**<CNcomment:  向下移到 */
    HI_MEDIAPLAYER_ZORDER_BUTT
} HI_MEDIAPLAYER_ZORDER_E;

#define HIMEDIA_MEMCPY(ptrdst, ptrsrc, size) \
  do \
  { \
    if (NULL != (ptrdst) && NULL != (ptrsrc)) \
    { \
      memcpy((ptrdst), (ptrsrc), (size)); \
    } \
  } while (0)

#define HIMEDIA_FREE(ptr) \
  do \
  { \
    if ((ptr)) \
    { \
      free((ptr)); \
      (ptr) = NULL; \
    } \
  } while (0)

#define HIMEDIA_DOFUNC_RET( func ) \
  do { \
    int ret = 0; \
    ret = func; \
    if(ret != NO_ERROR) \
    { \
    return ret; \
    }; \
  } while(0)

#define HIMEDIA_DOHIMEDIAFUNC_RET( func ) \
  do { \
      int ret = 0; \
      ret = func; \
      if(ret != NO_ERROR) \
      { \
          return UNKNOWN_ERROR; \
      }; \
  } while(0)

#define HIMEDIA_DOHIPLAYERFUNC_RET( func ) \
  do { \
      int ret = 0; \
      ret = func; \
      if(ret != HI_SUCCESS) \
      { \
          return UNKNOWN_ERROR; \
      }; \
  } while(0)

#define HIMEDIA_NULL_VERIFY( ptr ) \
  do { \
    if (NULL == ptr) \
    { \
    LOGE("NULL point"); \
    return UNKNOWN_ERROR; \
    } \
  } while(0)

namespace android
{
    enum ANDROID_ERROR_EXTRA
    {
        MEDIA_ERROR_UNSUPPORTED = -1010,
    };

    enum Hi_PLAYER_TYPE
    {
        HI_TYPE_PLAYER   = 0,
        HI_TYPE_BDPLAYER = 1,
    };

    enum Types
    {
        STRING_VAL = 1,
        INTEGER_VAL,
        BOOLEAN_VAL,
        LONG_VAL,
        DOUBLE_VAL,
        DATE_VAL,
        BYTE_ARRAY_VAL,
    };

    enum HIPLAYER_ENUM
    {
        MEDIA_FAST_FORWORD_COMPLETE = 20,
        MEDIA_FAST_BACKWORD_COMPLETE = 21,

        MEDIA_INFO_PREPARE_PROGRESS = 710,
        // Audio play fail
        MEDIA_INFO_AUDIO_FAIL = 1000,
        // Video play fail
        MEDIA_INFO_VIDEO_FAIL = 1001,
        // network erro/unknown
        MEDIA_INFO_NETWORK  = 1002,
        // time out
        MEDIA_INFO_TIMEOUT  =  1003,
        // media not support
        MEDIA_INFO_NOT_SUPPORT  =  1004,
        //net-player buffer is empty
        MEDIA_INFO_BUFFER_EMPTY  = 1005,
        //net-player buffer is starting
        MEDIA_INFO_BUFFER_START  =  1006,
        // net-player buffer is enough
        MEDIA_INFO_BUFFER_ENOUGH  =  1007,
        // net-player buffer is full
        MEDIA_INFO_BUFFER_FULL  =  1008,
        // net-player buffer download finish
        MEDIA_INFO_BUFFER_DOWNLOAD_FIN  = 1009,
        // The Fist frame time
        MEDIA_INFO_FIRST_FRAME_TIME = 1010,
        // stream 3D mode
        MEDIA_INFO_STREM_3D_MODE = 1011,
        // I frame error
        MEDIA_INFO_STREM_IFRAME_ERROR = 1012,
        // stream norm switch
        MEDIA_INFO_STREM_NORM_SWITCH = 1013,

        //hiplayer Video INFO string,set only
        KEY_PARAMETER_VIDEO_POSITION_INFO = 6009,
    };

    template<typename T> class SortedVector;
}
#endif
