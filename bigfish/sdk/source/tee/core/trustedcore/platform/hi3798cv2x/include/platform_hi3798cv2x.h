#ifndef __PLATFORM_HI3798CV2X_H__
#define __PLATFORM_HI3798CV2X_H__

#include "sys_hi3798cv2x.h"
#include "rtc_hi3798cv2x.h"
#include "serial_hi3798cv2x.h"
#include "timer_hi3798cv2x.h"
//#include "gic_seattle.h"
/*store tee log to DUMP_MEM_START
* Total 500k:480k for tee log and 20k for secure page table
*/
#define DUMP_MEM_SIZE (480*1024)
#define DUMP_SECURE_PAGE_TABLE_SIZE (20*1024)
#define DUMP_MEM_START ((DUMP_DDR+5*1024))
#define DUMP_MEM_RESERVE_SIZE  (156)     /* for trustedcore info, for example version */
#define DUMP_MEM_STRUCT_SIZE    (64)     /* for record the real write addr or write ring-buffer times */
#endif /*__PLATFORM_HI3798CV2X_H__ */
