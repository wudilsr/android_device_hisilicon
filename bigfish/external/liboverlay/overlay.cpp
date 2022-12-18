#include <overlay.h>
#include <cutils/log.h>
#include <cutils/properties.h>
#include <utils/StopWatch.h>
#include <utils/KeyedVector.h>
#include <sys/mman.h>
#include <sync/sw_sync.h>
#include <ui/Fence.h>
#include <pthread.h>

#include <hi_type.h>
#include <hi_mpi_win.h>
#include <hi_unf_video.h>
#include <hi_unf_disp.h>
#include <gralloc_priv.h>

#include "DisplayClient.h"

#define LOG_TAG "OverLay"
#define LOG_NDEBUG 1
#define ALIGN_UP(a, b) (((a) + (typeof(a))(b) - 1) & (~((typeof(a))(b)-1)))
#define ALIGN_DOWN(a, b) ((a) & (~((typeof(a))(b)-(typeof(a))1)))

using namespace android;

enum VDH {
    VDH0 = 0,
    VDH1,
    VDH2,
    VDH3,
    VDH_BUTT,
};

typedef struct window_freeze_ctx
{
    int     frameIndex;
    buffer_handle_t handle;
} window_freeze_ctx;

typedef struct index
{
    int     windowIndex;
    int     frameIndex;
} index_t;

typedef struct frame
{
    int frame_buf_fd;
    int frame_buf_addr;
    int metadata_buf_fd;
    int metadata_buf_addr;
    int metadata_buf_size;
    int width;
    int height;
    int stride;
    int is_sec;
} frame_t;

typedef unsigned long addr_t;

typedef struct window
{
    int                     fd;
    unsigned int            frameIndex;

#ifdef SW_FENCE
    unsigned int            lastFrameIndex;
    int                     sync_timeline_fd;
    int                     fence_fd;
#endif
    HI_S32                  s32Reset;
    HI_U32                  u32RepeatCnt;
    pthread_mutex_t         mutex;
    HI_HANDLE               hWindow;
    HI_DRV_VIDEO_FRAME_S    curFrame;
    overlay_rect_t          last_position;
    HI_MPI_WIN_RATIO_PARA_S stRatio;
    HI_S32                  s32Cvrs;
    HI_S32                  s32EnableCvrs;
    KeyedVector<addr_t, sp<Fence> > mFenceMap;
    Vector<window_freeze_ctx>      mFreezeCtxs;

//    HI_DRV_DISP_ZORDER_E    enZFlag; /*z-order of this window*/
//    HI_DRV_ROT_ANGLE_E      enRotation; /*transform*/
} window_t;

struct hi_overlay_dev
{
    struct overlay_device_t device;
    window_t    window[VDH_BUTT];
    KeyedVector<addr_t, index_t > bufferIndexMap;
    pthread_mutex_t         mutex;
};

static struct hi_overlay_dev s_OverlayDev;
static struct overlay_device_t *mOdev = NULL;
static alloc_device_t *s_AllocDev = NULL;
static const int kDisplayNum = 3;
//------------------------------------------------------------------------------
static int ov_set_position(window_t* w, overlay_rect_t displayFrame);
//------------------------------------------------------------------------------
/**
 * free the frame if current frame is not in range [frameIndex, frameIndex+kDisplayNum]
 */
static inline bool canRelease(int releaseFrameIdx, int curFrameIdx)
{
    if (releaseFrameIdx > 0 && curFrameIdx > 0 &&
            (curFrameIdx >= releaseFrameIdx) &&
            (curFrameIdx < releaseFrameIdx + kDisplayNum)) {
        return false;
    }
    return true;
}

static inline void delIndex(struct hi_overlay_dev * ov, private_handle_t* handle)
{
    addr_t addr = handle->ion_phy_addr;
    int i;
    (void)pthread_mutex_lock(&ov->mutex);
    i = ov->bufferIndexMap.indexOfKey(addr);

    if (i < 0) {
        (void)pthread_mutex_unlock(&ov->mutex);
        return;
    }
    ov->bufferIndexMap.removeItem(addr);
    (void)pthread_mutex_unlock(&ov->mutex);
}

static inline index_t getIndex(struct hi_overlay_dev * ov, private_handle_t* handle)
{
    int i;
    const static index_t invalid = {-1, -1};
    index_t ret;
    (void)pthread_mutex_lock(&ov->mutex);
    i = ov->bufferIndexMap.indexOfKey(handle->ion_phy_addr);
    if (i < 0) {
        ALOGE("invalid buffer 0x%lx", handle->ion_phy_addr);
        (void)pthread_mutex_unlock(&ov->mutex);
        return invalid;
    }
    ret = ov->bufferIndexMap.valueAt(i);
    (void)pthread_mutex_unlock(&ov->mutex);
    return ret;
}

static inline void setIndex(struct hi_overlay_dev * ov, private_handle_t* handle, int winIdx, int frameIdx)
{
    addr_t addr = handle->ion_phy_addr;
    index_t index;
    int i;

    index.windowIndex = winIdx;
    index.frameIndex = frameIdx;
    (void)pthread_mutex_lock(&ov->mutex);
    i = ov->bufferIndexMap.indexOfKey(addr);

    if (i < 0) {
        ov->bufferIndexMap.add(addr, index);
    } else {
        ov->bufferIndexMap.replaceValueFor(addr, index);
    }
    (void)pthread_mutex_unlock(&ov->mutex);
    ALOGV("set buffer 0x%lx win index %d", addr, winIdx);
}

static inline void ov_clear_win(window_t* w)
{
    memset(&w->curFrame, 0, sizeof(w->curFrame));
    memset(&w->last_position, 0, sizeof(w->last_position));
    memset(&w->stRatio, 0, sizeof(w->stRatio));
    w->frameIndex = 0;
    w->hWindow = 0;
    w->mFenceMap.clear();
    w->mFreezeCtxs.clear();
    pthread_mutex_destroy(&w->mutex);
}

static inline int ov_lock_win(window_t* w)
{
    if (pthread_mutex_lock(&w->mutex)) {
        return -1;
    }
    return 0;
}

static inline int ov_unlock_win(window_t* w)
{
    if (pthread_mutex_unlock(&w->mutex)) {
        return -1;
    }
    return 0;
}

static int ov_add_fence(window_t* w, addr_t addr, int fenceFd)
{
    w->mFenceMap.add(addr, new Fence(dup(fenceFd)));
    return 0;
}

static int ov_check_fence(window_t* w, addr_t addr)
{
    int index = w->mFenceMap.indexOfKey(addr);
    sp<Fence> fence;
    if (index < 0) {
        ALOGE("could not found 0x%lx 's fence", addr);
        goto failed;
    }

    fence = w->mFenceMap.valueAt(index);
    if (fence->waitForever("ov check fence")) {
        ALOGE("wait buffer 0x%lx 's fence failed", addr);
        goto failed;
    }

    w->mFenceMap.removeItem(addr);
    return 0;
failed:
    return -1;
}

static inline void ov_release_freezeframe(window_t* w)
{
    addr_t addr;
    int i = 0;
    Vector<window_freeze_ctx>& ctxs = w->mFreezeCtxs;
    private_handle_t *hnd;

    while (ctxs.size()) {
        if (canRelease(ctxs[i].frameIndex, w->curFrame.u32FrameIndex)) {
            hnd = (private_handle_t*)ctxs[i].handle;
            addr = hnd->ion_phy_addr;
            ov_unlock_win(w);
            if (s_AllocDev && s_AllocDev->free(s_AllocDev, hnd)) {
                ALOGE("release freeze frame 0x%lx failed", addr);
                ov_lock_win(w);
                return;
            }
            ov_lock_win(w);
            ctxs.removeAt(i);
            ALOGD("free capture frame 0x%lx done", addr);
        } else {
            break;
        }
    }

}

static inline int rect_isequal(overlay_rect_t* rhs, overlay_rect_t* lhs)
{
    if (rhs->bottom != lhs->bottom ||
            rhs->left != lhs->left ||
            rhs->right != lhs->right ||
            rhs->top != lhs->top)
    {
        return 0;
    }
    return 1;
}

static int ov_create_win(window_t* w)
{
    HI_S32 ret;
    DisplayClient dispClient;
    int resolution = 1080;
    int aspectRate = 0;
    char buffer[PROP_VALUE_MAX];

    /*check window has created*/
    if (w->hWindow) {
        return 0;
    }

    if (HI_MPI_WIN_Init() != HI_SUCCESS) {
        ALOGE("init window failed");
        return -1;;
    }

    pthread_mutex_init(&w->mutex, NULL);

    HI_DRV_WIN_ATTR_S winAttr;
    memset(&winAttr, 0, sizeof(winAttr));
    winAttr.enDisp = HI_DRV_DISPLAY_1;
    winAttr.enARCvrs = HI_DRV_ASP_RAT_MODE_FULL;

    if (HI_MPI_WIN_Create(&winAttr, &w->hWindow) != HI_SUCCESS) {
        ALOGE("create window failed");
        goto failed;
    }

    if (HI_MPI_WIN_SetEnable(w->hWindow, HI_TRUE) != HI_SUCCESS) {
        ALOGE("enable window failed");
        goto failed;
    }

#ifdef SW_FENCE
    w->sync_timeline_fd = sw_sync_timeline_create();
    if (w->sync_timeline_fd < 0) {
        ALOGE("create sync time line failed");
    }
#endif
    //init attr for aspect rate convertion
    memset(buffer, 0, PROP_VALUE_MAX);
    property_get("persist.sys.resolution", buffer, "1080");
    resolution = atoi(buffer);
    if(resolution == 1080) {
        w->stRatio.stScreen.s32Width = 1920;
        w->stRatio.stScreen.s32Height = 1080;
    } else {
        w->stRatio.stScreen.s32Width = 1280;
        w->stRatio.stScreen.s32Height = 720;
    }
    w->stRatio.stScreen.s32X = 0;
    w->stRatio.stScreen.s32Y = 0;

    w->s32Cvrs = dispClient.GetAspectCvrs();
    w->stRatio.eAspMode = (HI_DRV_ASP_RAT_MODE_E)w->s32Cvrs;

    aspectRate = dispClient.GetAspectRatio();
    switch (aspectRate)
    {
    case HI_UNF_DISP_ASPECT_RATIO_AUTO:
        w->stRatio.DeviceHeight = w->stRatio.stScreen.s32Height;
        w->stRatio.DeviceWidth = w->stRatio.stScreen.s32Width;
        break;
    case HI_UNF_DISP_ASPECT_RATIO_4TO3:
        w->stRatio.DeviceHeight = 3;
        w->stRatio.DeviceWidth = 4;
        break;
    case HI_UNF_DISP_ASPECT_RATIO_16TO9:
        w->stRatio.DeviceHeight = 9;
        w->stRatio.DeviceWidth = 16;
        break;
    case HI_UNF_DISP_ASPECT_RATIO_221TO1:
        w->stRatio.DeviceHeight = 100;
        w->stRatio.DeviceWidth = 221;
        break;
    default:
        w->stRatio.DeviceHeight = 0;
        w->stRatio.DeviceWidth = 0;
        ALOGE("unexpected unf disp aspect ratio:%d", aspectRate);
        break;
    }

    memset(buffer, 0, PROP_VALUE_MAX);
    property_get("ro.product.target", buffer, "ott");
#if 0 //4k stream, 4K/1080 output display wrong
    if((!strncmp(buffer, "shcmcc", 6))
        || (!strncmp(buffer, "telecom", 7))
        || (!strncmp(buffer, "unicom", 6)))
    {
        w->s32EnableCvrs = 1;
    }
    else
    {
        w->s32EnableCvrs = 0;
    }
#else
    w->s32EnableCvrs = 0;
#endif
    property_get("overlay.cvrs", buffer, "0");
    if (strncmp(buffer, "1", 1) == 0)
    {
        w->s32EnableCvrs = 1;
    }

    ALOGD("Create window:0x%x, cvrs:%d, enable cvrs:%d",
            w->hWindow, w->s32Cvrs, w->s32EnableCvrs);
    return 0;
failed:
    ALOGE("create vo failed!");
    if (w->hWindow) {
        HI_MPI_WIN_Destroy(w->hWindow);
        w->hWindow = 0;
    }
    return -1;
}

static int ov_display_frame(window_t* w, frame_t* frame, int* releaseFence)
{
    HI_UNF_VIDEO_FRAME_INFO_S* pstFrame = NULL;
    HI_DRV_VIDEO_FRAME_S* pstDrvFrame = NULL;
    HI_DRV_VIDEO_PRIVATE_S* priv = NULL;
    HI_U32 u32Stride = (HI_U32)frame->stride;
    int fence_fd = -1;
    int inc = 0;
    int height = frame->height;
    int width = frame->width;
    int addr = frame->frame_buf_addr;
    char bufferKey[PROP_NAME_MAX];
    char bufferVal[PROPERTY_VALUE_MAX];
//    HI_DRV_WIN_PLAY_INFO_S stWinInfo;

    if ((HI_U32)frame->frame_buf_addr == w->curFrame.stBufAddr[0].u32PhyAddr_Y)
    {
        return 0;
    }
    w->frameIndex++;

#ifdef SW_FENCE

    if (w->curFrame.u32FrameIndex != w->frameIndex) {
        fence_fd = sw_sync_fence_create(w->sync_timeline_fd, "win0100", w->frameIndex);
        if (fence_fd < 0) {
            ALOGE("create sw sync fence failed");
            return -1;
        }
        ALOGD("window display frame index:%d, addr:0x%lx, fence:%d", w->frameIndex, addr, fence_fd);
    }
#endif

    memset(&w->curFrame, 0, sizeof(w->curFrame));

    priv = (HI_DRV_VIDEO_PRIVATE_S*)w->curFrame.u32Priv;
    w->u32RepeatCnt = 1;
    w->curFrame.ePixFormat = HI_DRV_PIX_FMT_NV21;//yuv420sp
    w->curFrame.stBufAddr[0].u32PhyAddr_Y = addr;
    w->curFrame.stBufAddr[0].u32Stride_Y = u32Stride;
    w->curFrame.stBufAddr[0].u32PhyAddr_C = addr + height * u32Stride;
    w->curFrame.stBufAddr[0].u32Stride_C = u32Stride;
    w->curFrame.u32FrameRate = 60 * 100;//surface flinger refresh rate
    w->curFrame.u32FrameIndex = w->frameIndex;
    w->curFrame.enFieldMode = HI_DRV_FIELD_ALL;
    priv->eColorSpace = HI_DRV_CS_BT601_YUV_LIMITED;
    priv->eOriginField = HI_DRV_FIELD_ALL;
    priv->u32PrivBufPhyAddr = frame->metadata_buf_addr + frame->metadata_buf_size / 2;

    if (frame->frame_buf_fd != -1) {
        pstFrame = (HI_UNF_VIDEO_FRAME_INFO_S*)mmap(NULL, frame->metadata_buf_size,
                PROT_READ | PROT_WRITE, MAP_SHARED, frame->metadata_buf_fd, 0);
    }

    if (pstFrame)
    {
        static HI_DRV_FIELD_MODE_E s_fieldMode[] = {
                [HI_UNF_VIDEO_FIELD_ALL] = HI_DRV_FIELD_ALL,
                [HI_UNF_VIDEO_FIELD_TOP] = HI_DRV_FIELD_TOP,
                [HI_UNF_VIDEO_FIELD_BOTTOM] = HI_DRV_FIELD_BOTTOM
        };
        pstDrvFrame = (HI_DRV_VIDEO_FRAME_S*)((char*)pstFrame + frame->metadata_buf_size / 2);
        //w/h changed, reset aspect ratio
        if (w->curFrame.u32Height && (
                w->curFrame.u32Height != pstDrvFrame->u32Height ||
                w->curFrame.u32Width != pstDrvFrame->u32Width))
        {
            w->stRatio.SrcImgH = frame->height;
            w->stRatio.SrcImgW = frame->width;
            w->stRatio.stInWnd.s32X = 0;
            w->stRatio.stInWnd.s32Y = 0;
            w->stRatio.stInWnd.s32Height = pstDrvFrame->u32Height;
            w->stRatio.stInWnd.s32Width = pstDrvFrame->u32Width;
            w->stRatio.AspectHeight = pstFrame->u32AspectHeight;
            w->stRatio.AspectWidth = pstFrame->u32AspectWidth;
            if (ov_set_position(w, w->last_position)) {
                ALOGE("reset overlay position failed");
            }
        }

        w->curFrame.u32Height = pstDrvFrame->u32Height;
        w->curFrame.u32Width = pstDrvFrame->u32Width;
        w->curFrame.u32AspectHeight = pstFrame->u32AspectHeight;
        w->curFrame.u32AspectWidth = pstFrame->u32AspectWidth;
        w->curFrame.u32FrameRate = pstFrame->stFrameRate.u32fpsInteger * 100
                                + pstFrame->stFrameRate.u32fpsDecimal / 10;
        w->curFrame.enFieldMode = s_fieldMode[pstFrame->enFieldMode];
        w->u32RepeatCnt = pstFrame->u32Private[0];//FRC repeat count
        priv->eOriginField = s_fieldMode[pstFrame->enFieldMode];

        if (0 != munmap((void *)pstFrame, frame->metadata_buf_size))
        {
            ALOGE("Failed to munmap metadata buffer");
        }
    }
    else {
        w->curFrame.u32Height = height;
        w->curFrame.u32Width = width;
    }

#if 0
    snprintf(bufferKey, sizeof(bufferKey) - 1, "media.0x%lx", addr);
    if (property_get(bufferKey, bufferVal, "")) {
        int ps = 0, cs = 0, of = 0;
        if (sscanf(bufferVal, "PS:%d,CS:%d,OF:%d", &ps, &cs, &of) == 3) {
            ALOGD("prop key:%s, val:%s", bufferKey, bufferVal);
            w->curFrame.bProgressive = (HI_BOOL)ps;
            priv->eColorSpace = (HI_DRV_COLOR_SPACE_E)cs;
            priv->eOriginField = (HI_DRV_FIELD_MODE_E)of;
        }
    }
#endif
    while (w->u32RepeatCnt > 1) {
        if (HI_MPI_WIN_QueueSyncFrame(w->hWindow, &w->curFrame, (HI_U32*)&fence_fd) != HI_SUCCESS) {
            ALOGE("queue frame failed");
            return -1;
        }
        w->curFrame.u32FrameIndex = w->frameIndex++;
        close(fence_fd);
        fence_fd = -1;
        w->u32RepeatCnt--;
    }

    if (HI_MPI_WIN_QueueSyncFrame(w->hWindow, &w->curFrame, (HI_U32*)&fence_fd) != HI_SUCCESS) {
        ALOGE("queue frame failed");
#ifdef SW_FENCE
        if (fence_fd != -1) {
            close(fence_fd);
        }
#endif
        return -1;
    }
#ifdef SW_FENCE
    HI_DRV_VIDEO_FRAME_S stLastFrame;
    memset(&stLastFrame, 0, sizeof(stLastFrame));

    if (HI_MPI_WIN_GetLatestFrameInfo(w->hWindow, &stLastFrame) == HI_SUCCESS) {
        stLastFrame.u32FrameIndex = stLastFrame.u32FrameIndex > 0 ? stLastFrame.u32FrameIndex - 1 : 0;
        inc = stLastFrame.u32FrameIndex - w->lastFrameIndex;
        ALOGD("frame info, cur:%d, vo last:%d, overlay last:%d",
                w->curFrame.u32FrameIndex, stLastFrame.u32FrameIndex, w->lastFrameIndex);
        w->lastFrameIndex = stLastFrame.u32FrameIndex;
    }

    if (inc > 1) {
        ALOGD("increase time line:%d", inc);
        sw_sync_timeline_inc(w->sync_timeline_fd, inc);
    }
#endif
    ALOGV("overlay queue frame, handle:0x%lx, index:%d, fence:%d", addr, w->frameIndex, fence_fd);
    *releaseFence = fence_fd;
    ov_add_fence(w, addr, fence_fd);

    /*do not free last freeze frame avoid waiting fence too long*/
    if (w->mFreezeCtxs.size()) {
        ov_release_freezeframe(w);
    }
    w->s32Reset = 0;
    return 0;
}

static int ov_set_position(window_t* w, overlay_rect_t displayFrame)
{
    HI_DRV_WIN_ATTR_S attr;
    HI_RECT_S stRect;

    if (rect_isequal(&w->last_position, &displayFrame)) {
        return 0;
    }

    memset(&attr, 0, sizeof(attr));

    if (HI_MPI_WIN_GetAttr(w->hWindow, &attr) != HI_SUCCESS) {
        ALOGE("get window 0x%x attr failed", w->hWindow);
        return -1;
    }
    ALOGD("get attr,x:%d, y:%d, w:%d,h:%d",
            attr.stOutRect.s32X,
            attr.stOutRect.s32Y,
            attr.stOutRect.s32Height,
            attr.stOutRect.s32Width);
    attr.stOutRect.s32X     = displayFrame.left;
    attr.stOutRect.s32Y     = displayFrame.top;
    attr.stOutRect.s32Height     = displayFrame.bottom - displayFrame.top;
    attr.stOutRect.s32Width     = displayFrame.right - displayFrame.left;

    w->stRatio.stOutWnd.s32X = attr.stOutRect.s32X;
    w->stRatio.stOutWnd.s32Y = attr.stOutRect.s32Y;
    w->stRatio.stOutWnd.s32Height = attr.stOutRect.s32Height;
    w->stRatio.stOutWnd.s32Width = attr.stOutRect.s32Width;

    if (w->s32EnableCvrs && attr.stOutRect.s32Height == w->stRatio.stScreen.s32Height
            && attr.stOutRect.s32Width == w->stRatio.stScreen.s32Width) {
        if (HI_SUCCESS == HI_MPI_WIN_CalAspectRegion(w->stRatio, &stRect)) {
            attr.stOutRect.s32X += stRect.s32X;
            attr.stOutRect.s32Y += stRect.s32Y;
            attr.stOutRect.s32Height = stRect.s32Height;
            attr.stOutRect.s32Width = stRect.s32Width;
            ALOGD("window ration, AspectWidth:%d, AspectHeight:%d, "
                    "InWndH:%d, InwndW:%d, imgH:%d, imgW:%d,"
                    "x:%d,y:%d,w:%d,h:%d, cvrs:%d",
                    w->stRatio.AspectWidth,
                    w->stRatio.AspectHeight,
                    w->stRatio.stInWnd.s32Height,
                    w->stRatio.stInWnd.s32Width,
                    w->stRatio.SrcImgH,
                    w->stRatio.SrcImgW,
                    stRect.s32X, stRect.s32Y,
                    stRect.s32Height, stRect.s32Width, attr.enARCvrs);
        }
    }

    if (attr.stOutRect.s32X % 2 == 0) {
        attr.stOutRect.s32Width = ALIGN_UP(attr.stOutRect.s32Width, 2);
    } else {
        attr.stOutRect.s32Width = ALIGN_UP(attr.stOutRect.s32Width + 1, 2);
    }

    if (attr.stOutRect.s32Y % 4 == 0) {
        attr.stOutRect.s32Height = ALIGN_UP(attr.stOutRect.s32Height, 4);
    } else {
        attr.stOutRect.s32Height = ALIGN_UP(attr.stOutRect.s32Height + 3, 4);
    }

    attr.stOutRect.s32X = ALIGN_DOWN(attr.stOutRect.s32X, 2);
    attr.stOutRect.s32Y = ALIGN_DOWN(attr.stOutRect.s32Y, 4);

    ALOGD("window position, x:%d, y:%d, w:%d, h:%d",
            attr.stOutRect.s32X,
            attr.stOutRect.s32Y,
            attr.stOutRect.s32Width,
            attr.stOutRect.s32Height);
    if (HI_MPI_WIN_SetAttr(w->hWindow, &attr) != HI_SUCCESS) {
        ALOGE("set window 0x%x attr failed", w->hWindow);
        return -1;
    }
    w->last_position = displayFrame;
    return 0;
}

static int ov_reset_win(window_t* w)
{
    if (!w->hWindow || w->s32Reset) {
        return -1;
    }
    ALOGD("reset window 0x%x", w->hWindow);
    HI_DRV_WIN_SWITCH_E eResetType = HI_DRV_WIN_SWITCH_BLACK;
    HI_BOOL bEnable = HI_FALSE;

    /* release all buffer in window */
    if (HI_MPI_WIN_Reset(w->hWindow, eResetType) != HI_SUCCESS) {
        ALOGE("reset window 0x%x failed", w->hWindow);
        return 0;
    }

    memset(&w->curFrame, 0, sizeof(w->curFrame));
    w->s32Reset = 1;
    return 0;
}

static int ov_freeze_buffer(window_t* w, buffer_handle_t handle, int frameIdx)
{
    window_freeze_ctx ctx;
    if (!s_AllocDev) {
        ALOGE("Do not set alloc dev, can not freeze frame");
        return -1;
    }
    ctx.handle = handle;
    ctx.frameIndex = frameIdx;
    w->mFreezeCtxs.add(ctx);
    return 0;
}

static void ov_destroy_win(window_t* w)
{
    if (!w->hWindow) {
        return;
    }

    if (HI_MPI_WIN_SetEnable(w->hWindow, HI_FALSE) != HI_SUCCESS) {
        ALOGE("disable window failed");
    }

    if (w->mFreezeCtxs.size() > 0) {
        ov_reset_win(w);
        ov_release_freezeframe(w);
    }

    if (HI_MPI_WIN_Destroy(w->hWindow) != HI_SUCCESS) {
        ALOGE("destroy window failed");
    }
#ifdef SW_FENCE
    close(w->sync_timeline_fd);
#endif

    ALOGD("Destroy window:0x%x", w->hWindow);
    ov_clear_win(w);
}

//------------------------------------------------------------------------------
int checkBuffer(struct overlay_device_t const* module,
        buffer_handle_t handle)
{
    struct hi_overlay_dev * ov = (struct hi_overlay_dev *)module;
    char name[256];
    private_handle_t *hnd = (private_handle_t *)handle;
    snprintf(name, sizeof(name), "Check buffer 0x%lx", hnd->ion_phy_addr);
    StopWatch stopWath(name);
    index_t index = getIndex(ov, hnd);
    int winIdx;
    int frameIdx;

    if (index.windowIndex < 0) {
        ALOGE("CheckBuffer, invalid buffer addr:0x%lx", hnd->ion_phy_addr);
        return -1;
    }

    winIdx = index.windowIndex;
    frameIdx = index.frameIndex;

    if (!ov->window[winIdx].hWindow) {
        ALOGD("window for buffer 0x%lx did not open", hnd->ion_phy_addr);
        return 0;
    }

    ov_lock_win(ov->window + winIdx);

    if (!canRelease(frameIdx, ov->window[winIdx].curFrame.u32FrameIndex))
    {
        ALOGD("buffer 0x%lx may be displaying, do not free", hnd->ion_phy_addr);

        if (ov_freeze_buffer(ov->window + winIdx, handle, frameIdx) < 0) {
            ALOGE("Freeze current buffer 0x%lx failed", hnd->ion_phy_addr);
            goto failed;
        }
        ov_unlock_win(ov->window + winIdx);
        return 1;//tell caller this buffer is in use, do not free
    }

    if (ov_check_fence(ov->window + winIdx, hnd->ion_phy_addr)) {
        ALOGE("check window by buffer 0x%lx's fence failed", hnd->ion_phy_addr);
        goto failed;
    }

    ALOGD("check buffer 0x%lx ok, frame index:%d, cur frame:%d ",
            hnd->ion_phy_addr, frameIdx,
            ov->window[winIdx].curFrame.u32FrameIndex);
    ov_unlock_win(ov->window + winIdx);

    delIndex(ov, hnd);

    return 0;
failed:
    ov_unlock_win(ov->window + winIdx);
    return -1;
}

/**
 * main purpose:
 * 1.open/close overlay channel according buffer usage
 */
int prepareOverlayLayers(struct overlay_device_t const* module,
        int num, overlay_layer_t* layers)
{
    struct hi_overlay_dev * ov = (struct hi_overlay_dev *)module;
    int i;
    private_handle_t *hnd = NULL;

    if (!layers) {
        ALOGE("invalid overlay layers");
        return -1;
    }

    if (num < 0 || num >= VDH_BUTT) {
        ALOGE("unsupported overlay layers:%d", num);
        return -1;
    }

    for (i = 0; i < num; i++) {
        hnd = (private_handle_t*)layers[i].handle;
        setIndex(ov, hnd, i, 0);
        if (!ov->window[i].hWindow) {
            ov_create_win(ov->window+i);
        }
        else if (!layers[i].visible) {
            ov_lock_win(ov->window + i);
            ov_reset_win(ov->window + i);
            ov_unlock_win(ov->window + i);
        }
    }

    for (i = num; i < VDH_BUTT; i++) {
        ov_destroy_win(ov->window+i);
    }
    return 0;
}

int queueBuffer(struct overlay_device_t const* module,
        buffer_handle_t handle, int* releaseFence)
{
    struct hi_overlay_dev * ov = (struct hi_overlay_dev *)module;
    private_handle_t *hnd = (private_handle_t *)handle;
    index_t idx = getIndex(ov, hnd);
    int index = idx.windowIndex;
    frame_t frame;

    if (index < 0) {
        ALOGE("Queue, invalid buffer addr:0x%lx", hnd->ion_phy_addr);
        return -1;
    }
    frame.frame_buf_fd = hnd->share_fd;
    frame.metadata_buf_fd = hnd->metadata_fd;
    frame.frame_buf_addr = hnd->ion_phy_addr;
    frame.metadata_buf_addr = hnd->ion_metadata_phy_addr;
    frame.metadata_buf_size = hnd->ion_metadata_size;
    frame.height = hnd->height;
    frame.width = hnd->width;
    frame.stride = hnd->stride;

    ov_lock_win(ov->window + index);
    if (ov_display_frame(ov->window + index, &frame, releaseFence) < 0) {
        ALOGE("Queue, buffer 0x%lx failed", hnd->ion_phy_addr);
        return -1;
    }
    idx.frameIndex = (int)ov->window[index].curFrame.u32FrameIndex;
    ov_unlock_win(ov->window + index);

    setIndex(ov, hnd, index, idx.frameIndex);
   return 0;
}

void setCrop(struct overlay_device_t const* module,
        buffer_handle_t handle,
        overlay_rect_t sourceCrop)
{
    /**
     * get VO fd from handle,
     * set vo scale, aspect rate etc.
     * vo current does not support this function.
     * HI_MPI_VO_SetWindowRatio -- not implemented
     */
}

void setPosition(struct overlay_device_t const* module,
        buffer_handle_t handle,
        overlay_rect_t displayFrame)
{
   private_handle_t *hnd = (private_handle_t *)handle;
   struct hi_overlay_dev * ov = (struct hi_overlay_dev *)module;
   index_t idx = getIndex(ov, hnd);
   int index = idx.windowIndex;
   HI_UNF_VIDEO_FRAME_INFO_S* pstFrame = NULL;
   HI_DRV_VIDEO_FRAME_S* pstDrvFrame = NULL;

   if (index < 0) {
       ALOGE("SetPos, invalid buffer addr:0x%lx", hnd->ion_phy_addr);
       return;
   }

   if (hnd->metadata_fd != -1) {
       pstFrame = (HI_UNF_VIDEO_FRAME_INFO_S*)mmap(NULL, hnd->ion_metadata_size,
               PROT_READ | PROT_WRITE, MAP_SHARED, hnd->metadata_fd, 0);
       pstDrvFrame = (HI_DRV_VIDEO_FRAME_S*)((char*)pstFrame + hnd->ion_metadata_size / 2);

   }
   ov_lock_win(ov->window + index);

   ov->window[index].stRatio.SrcImgH = hnd->height;
   ov->window[index].stRatio.SrcImgW = hnd->width;
   ov->window[index].stRatio.stInWnd.s32X = 0;
   ov->window[index].stRatio.stInWnd.s32Y = 0;

   if (pstFrame) {
       ov->window[index].stRatio.stInWnd.s32Height = pstDrvFrame->u32Height;
       ov->window[index].stRatio.stInWnd.s32Width = pstDrvFrame->u32Width;
       ov->window[index].stRatio.AspectHeight = pstFrame->u32AspectHeight;
       ov->window[index].stRatio.AspectWidth = pstFrame->u32AspectWidth;
   }

   if (ov_set_position(ov->window + index, displayFrame)) {
       ALOGE("Set overlay position failed, buffer:0x%lx", hnd->ion_phy_addr);
   }
   ov_unlock_win(ov->window + index);

   if (pstFrame) {
       if (0 != munmap((void *)pstFrame, hnd->ion_metadata_size))
       {
           ALOGE("Failed to munmap metadata buffer");
       }
   }
   return;
}

void setTransform(struct overlay_device_t const* module,
        buffer_handle_t handle,
        uint32_t transform)
{
    /**
     * ioctl(g_VoDevFd, CMD_WIN_SET_ROTATION, &VoWinRotation)
     * ioctl(g_VoDevFd, CMD_WIN_SET_FLIP, &VoWinFlip)
     */
}

int perform(struct overlay_device_t const* module,
        int operation, ... )
{
    struct hi_overlay_dev * ov = (struct hi_overlay_dev *)module;
    va_list args;

    va_start(args, operation);

    va_end(args);
    return 0;
}

int ovdev_close(struct hw_device_t* device)
{
    struct hi_overlay_dev *ovdev = (struct hi_overlay_dev *)device;
    int i;
    for (i = 0; i < VDH_BUTT; i++) {
        ov_destroy_win(ovdev->window + i);
    }
    ovdev->bufferIndexMap.clear();
    free(device);
    return 0;
}

static int overlay_open(const hw_module_t* module, const char* name,
                     hw_device_t** device)
{
    struct hi_overlay_dev *ovdev;

    int ret;

    if (strcmp(name, OVERLAY_HARDWARE_INTERFACE) != 0)
        return -EINVAL;

//    ovdev = (struct hi_overlay_dev *)calloc(1, sizeof(struct hi_overlay_dev));
//    if (!ovdev)
//        return -ENOMEM;
    ovdev = &s_OverlayDev;

    ovdev->device.common.tag = HARDWARE_DEVICE_TAG;
    ovdev->device.common.version = 0;
    ovdev->device.common.module = (struct hw_module_t *) module;
    ovdev->device.common.close  = ovdev_close;

    ovdev->device.checkBuffer   = checkBuffer;
    ovdev->device.prepareOverlayLayers= prepareOverlayLayers;
    ovdev->device.queueBuffer   = queueBuffer;

    ovdev->device.setCrop       = setCrop;
    ovdev->device.setPosition   = setPosition;
    ovdev->device.setTransform  = setTransform;
    ovdev->device.setBlending   = NULL;
    ovdev->device.perform       = perform;
    ovdev->mutex                = PTHREAD_MUTEX_INITIALIZER;
    mOdev = &ovdev->device;
    *device = &ovdev->device.common;
    return 0;
}

static struct hw_module_methods_t hal_module_methods = {
    open: overlay_open,
};

overlay_module_t HAL_MODULE_INFO_SYM = {
    common: {
        tag: HARDWARE_MODULE_TAG,
        version_major: 1,
        version_minor: 0,
        id: OVERLAY_HARDWARE_MODULE_ID,
        name: "Default Overlay HW HAL",
        author: "HiSilicon Technologies Co., Ltd.",
        methods: &hal_module_methods,
    }
};

void overlay_set_alloc_dev(void *dev)
{
    s_AllocDev = (alloc_device_t*)dev;
}

overlay_device_t* overlay_singleton()
{
    if (mOdev) {
        return mOdev;
    }
    hw_device_t* dev = NULL;
    overlay_open(NULL, OVERLAY_HARDWARE_INTERFACE, &dev);
    return mOdev;
}
