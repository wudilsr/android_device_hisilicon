
#ifndef GRALLOC_HISILICON_ADP_H_
#define GRALLOC_HISILICON_ADP_H_


#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#include <cutils/log.h>
#include <cutils/atomic.h>
#include <hardware/hardware.h>
#include <hardware/gralloc.h>

#include "alloc_device.h"
#include "gralloc_priv.h"
#include "gralloc_helper.h"
#include "framebuffer_device.h"

#include <linux/ion.h>
#include <ion/ion.h>

#include <cutils/properties.h>
#include <stdlib.h>

/*#define GRALLOC_USE_CMA*/

#ifdef OVERLAY
#include "overlay.h"
#endif

#include "hi_math.h"

#define RESOLUTION_FB_1080P_WIDTH   1920
#define RESOLUTION_FB_1080P_HEIGHT  1080
#define RESOLUTION_FB_720P_WIDTH    1280
#define RESOLUTION_FB_720P_HEIGHT   720

#define GRALLOC_ALIGN_YUV( value ) HI_SYS_GET_STRIDE( value )

#if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
#define GRALLOC_ALIGN_RGB( value ) HI_SYS_GET_STRIDE( value )
#else
#define GRALLOC_ALIGN_RGB( value ) GRALLOC_ALIGN( value, 64 )
#endif

int pri_hisi_ion_get_heapid(alloc_device_t *dev, size_t size, int usage, buffer_handle_t *pHandle);

int pri_hisi_device_layerbuffer_alloc(alloc_device_t *dev, size_t size, int usage, buffer_handle_t *pHandle, \
								private_module_t *m, ion_user_handle_t ion_hnd, private_handle_t *hnd);

int pri_hisi_device_framebuffer_alloc(alloc_device_t *dev, size_t size, int usage, buffer_handle_t *pHandle, \
										private_handle_t *hnd, void *vaddr, private_module_t *m);

int pri_hisi_device_free(alloc_device_t *dev, buffer_handle_t handle, private_handle_t const *hnd);

int pri_hisi_device_open(hw_module_t const *module, const char *name, hw_device_t **device, alloc_device_t *dev);

int pri_hisi_device_close(struct hw_device_t *device);

int pri_hisi_init_framebuffer(struct private_module_t *module, struct fb_var_screeninfo *info);

int pri_hisi_set_framebuffer_dpi(struct private_module_t *module, struct fb_var_screeninfo *info);

int pri_hisi_framebuffer_device_open(hw_module_t const *module, const char *name, hw_device_t **device);


#endif

