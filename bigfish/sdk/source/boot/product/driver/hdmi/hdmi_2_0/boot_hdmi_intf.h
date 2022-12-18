
#ifndef __BOOT_HDMI_INTF_H__
#define __BOOT_HDMI_INTF_H__
#include "hi_type.h"
#include <uboot.h>
#include "hdmi_hal.h"
#include "drv_hdmi_common.h"

#undef offsetof
#define offsetof(__type, __member) ((unsigned int) &((__type *)0)->__member)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#undef container_of
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

typedef struct 
{
    HI_U32             u32HdmiDevId;
    HDMI_TMDS_MODE_E   enTmdsMode;
    HDMI_ATTR_S        stAttr;
    HDMI_INFOFRAME_S   stInfoFrame;
    HDMI_HAL_S*        pstHdmiHal;
}HDMI_DEVICE_S;

#endif//__BOOT_HDMI_INTF_H__