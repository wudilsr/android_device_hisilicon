#ifndef _PANEL_SELF
#define _PANEL_SELF
#include "hi_drv_ir.h"
#include "hi_module.h"

typedef struct key_stu{
    unsigned keyid ;
    unsigned status ;
}KEY_STU;

#define KPC_EV_KEY_PRESS          (0x1)   // release
#define KPC_EV_KEY_RELEASE        (0x0)   // press

#define KEY_STATUS_DOWN           (0x0)   /**<Pressed*/
#define KEY_STATUS_HOLD           (0x1)   /**<Hold*/
#define KEY_STATUS_UP             (0x2)   /**<Released*/

#endif
