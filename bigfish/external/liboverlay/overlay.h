/* CopyRight
 *
 */
#ifndef OVERLAY_H
#define OVERLAY_H

#include <hardware/hardware.h>
#include <system/window.h>

/**
 * The id of this module
 */
#define OVERLAY_HARDWARE_MODULE_ID "overlay"

/**
 * Name of the device to open
 */
#define OVERLAY_HARDWARE_INTERFACE   "overlay_interface"

/**
 * Max supported overlay channels
 * just 1 video channel supported yet.
 */
#define OVERLAY_MAX_CHANNEL (1)

/**
 *  transform value for
 */
enum {
    /* flip source image horizontally */
    OV_TRANSFORM_FLIP_H = HAL_TRANSFORM_FLIP_H,
    /* flip source image vertically */
    OV_TRANSFORM_FLIP_V = HAL_TRANSFORM_FLIP_V,
    /* rotate source image 90 degrees clock-wise */
    OV_TRANSFORM_ROT_90 = HAL_TRANSFORM_ROT_90,
    /* rotate source image 180 degrees */
    OV_TRANSFORM_ROT_180 = HAL_TRANSFORM_ROT_180,
    /* rotate source image 270 degrees clock-wise */
    OV_TRANSFORM_ROT_270 = HAL_TRANSFORM_ROT_270,
};

enum {
    /* Reset window, if parameter is 0, repeat last frame, else if 1, black frame*/
    OV_PERFORM_RESET = 0,
    OV_PERFORM_BUTT,
};

typedef struct overlay_rect {
    int left;
    int top;
    int right;
    int bottom;
} overlay_rect_t;

typedef struct overlay_region {
    size_t numRects;
    overlay_rect_t const* rects;
} overlay_region_t;

typedef struct overlay_layer {
    buffer_handle_t handle;
    int visible;
} overlay_layer_t;

/**
 * Every hardware module must have a data structure named HAL_MODULE_INFO_SYM
 * and the fields of this data structure must begin with hw_module_t
 * followed by module specific information.
 */
struct overlay_module_t {
    struct hw_module_t common;
};

struct overlay_device_t {
    struct hw_device_t common;

    /**
     * Interfaces used in gralloc
     */

    /**
     * unregister a buffer handle from overlay device.
     */
    int (*checkBuffer)(struct overlay_device_t const* module,
            buffer_handle_t handle);

    /**
     * Interfaces used in HWC
     */

    /**
     * prepare overlay layers
     */
    int (*prepareOverlayLayers)(struct overlay_device_t const* module,
            int num, overlay_layer_t* layers);

    /**
     * queue a buffer handle to overlay device for displaying.
     */
    int (*queueBuffer)(struct overlay_device_t const* module,
            buffer_handle_t handle, int* releaseFence);

    /**
     * area of the source to consider, the origin is the top-left corner of
     * the buffer.
     */
    void (*setCrop)(struct overlay_device_t const* module,
            buffer_handle_t handle,
            overlay_rect_t sourceCrop);

    void (*setPosition)(struct overlay_device_t const* module,
            buffer_handle_t handle,
            overlay_rect_t displayFrame);

    void (*setTransform)(struct overlay_device_t const* module,
            buffer_handle_t handle,
            uint32_t transform);

    void (*setBlending)(struct overlay_device_t const* module,
            buffer_handle_t handle,
            uint32_t blending);

    /* reserved for future use */
    int (*perform)(struct overlay_device_t const* module,
            int operation, ... );
};

static inline int overlay_open(const struct hw_module_t* module,
        overlay_device_t** device) {
    return module->methods->open(module,
            OVERLAY_HARDWARE_INTERFACE, (struct hw_device_t**)device);
}

static inline int overlay_close(overlay_device_t* device) {
    return device->common.close(&device->common);
}

void overlay_set_alloc_dev(void *dev);

overlay_device_t* overlay_singleton();
#endif
