#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef WITH_K3V3_PLATFORM
#include "k3v3/include/platform_k3v3.h"
#endif

#ifdef WITH_K3V3PLUS_PLATFORM
#include "seattle/include/platform_seattle.h"
#endif

#ifdef WITH_V8R2_PLATFORM
#include "portland/include/platform_portland.h"
#endif

#ifdef WITH_KIRIN_PLATFORM
#include "kirin/include/platform_kirin.h"
#endif

#ifdef WITH_HI3798MX_PLATFORM
#include "hi3798mx/include/platform_hi3798mx.h"
#endif

#ifdef WITH_HI3798CV2X_PLATFORM
#include "hi3798cv2x/include/platform_hi3798cv2x.h"
#endif

#ifdef WITH_HI3751VX_PLATFORM
#include "hi3751vx/include/platform_hi3751vx.h"
#endif

#ifdef WITH_BALONG_V722_PLATFORM
#include "balong/include/platform_balong.h"
#endif

#endif /*__PLATFORM_H__ */
