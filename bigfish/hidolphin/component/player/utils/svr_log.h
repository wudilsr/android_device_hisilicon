/*
 * svr_log.h
 *
 *  Created on: 2014Äê9ÔÂ18ÈÕ
 *      Author: z00187490
 */

#ifndef SVR_LOG_H_
#define SVR_LOG_H_

#include <hi_type.h>
#include <hi_svr_utils.h>

#define MAX_BUFFER_SZ (1024)

HI_BOOL check_update_log(const HI_CHAR* log, HI_S32 len);

HI_S32 get_last_repeat_cnt();

HI_VOID platform_write(const HI_CHAR* tag, HI_S32 level,
        HI_CHAR* fmt, va_list var);

#endif /* SVR_LOG_H_ */
