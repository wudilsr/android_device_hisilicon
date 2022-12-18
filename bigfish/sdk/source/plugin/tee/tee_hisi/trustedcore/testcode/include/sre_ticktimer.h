

#ifndef __TIMER_FRAME_WORK_
#define __TIMER_FRAME_WORK_

#include "sre_base.h"
#include "sre_list.ph"

#define NSECS_PER_SEC   1000000000L
/*Seconds will be set to maximum value and the number of nanoseconds
 * will be zero */
#define TIMEVAL_MAX     (((INT64)~((UINT64)1 << 63)) & (~((UINT64)0xFFFFFFFF)))
#define MAX_NUM_OF_TIMERS 2

    /*The timer event is Inactive*/
#define    TIMER_STATE_INACTIVE     0x00
    /* The timer event is active and is waiting for expiration*/
#define    TIMER_STATE_ACTIVE       0x01
    /*The timer is expired and is waiting on the callback list to be executed*/
#define    TIMER_STATE_PENDING      0x02
    /* The timer event is currently being executed */
#define    TIMER_STATE_EXECUTING    0x04

/**
 * @brief
 *  Structure to represent the time
 *  in High resolution format( Resolution in Nano seconds)
 */
typedef union {
    INT64 tval64;
    struct
    {
        INT32 nsec, sec;
    }tval;
}timeval_t;

/**
* @brief
*/
enum timer_callback_mode {
    /* The handler function should be run in softirq*/
    TIMER_CALLBACK_SOFTIRQ,
    /* The handler function should be run in hardirq context itself*/
    TIMER_CALLBACK_HARDIRQ,
    /* The handler function should be executed in hardirq and it should not
     * restart the timer*/
    TIMER_CALLBACK_HARDIRQ_NORESTART
};

/**
* @brief
*/
enum timer_cbfn_return_value{
    TIMER_RESTART,
    TIMER_NORESTART
};



/**
* @brief
*/
struct timer_clock_info {
    struct timer_cpu_info* cpu_info;
    int    clock_id;
    //struct spinlock spin_lock;
    LIST_OBJECT_S active;
    timeval_t   clock_period;
    timeval_t   timer_period;
    int shift;
    UINT32 mult;
};

/**
* @brief
*/
struct timer_cpu_info{
        struct timer_clock_info clock_info[MAX_NUM_OF_TIMERS];
        timeval_t expires_next;
        LIST_OBJECT_S pending_routines;
        UINT32 num_events;
        int free_run_clock_id;
        int tick_timer_id;
};

extern struct timer_cpu_info g_timer_cpu_info;

/**
* @brief
*/
typedef struct stTimerEvent {
    LIST_OBJECT_S node;
    LIST_OBJECT_S callback_entry;

    timeval_t   expires;
    struct timer_clock_info* clk_info;
    int (*handler)(void* );
    int state;
    int callback_mode;
    void* data;
}timer_event;

/**
 * @brief
 * The elements of this structure are useful
 * for implementing the sw_timer
 */
typedef struct stSwtmrinfo{

    timeval_t sw_timestamp;
    UINT64 abs_cycles_count;
    UINT64 cycles_count_old;
    UINT64 cycles_count_new;

    timeval_t timer_period;
    timeval_t clock_period;
}stSwtmrinfo;

typedef UINT32 (*sw_timer_event_handler) (timer_event*);

/**
 * @ingroup sre_timer
 * SRE_timer错误码: 指针参数为空。
 *
 * 值: 0x02002e01
 *
 * 解决方案: 查看入参指针是否为空
 */
#define OS_ERRNO_TIMER_INPUT_PTR_NULL                           SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x01)

/**
 * @ingroup sre_timer
 * SRE_timer错误码: 定时器回调函数为空。
 *
 * 值: 0x02002e02
 *
 * 解决方案: 查看定时器回调函数是否为空
 */
#define OS_ERRNO_TIMER_PROC_FUNC_NULL                           SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x02)

/**
 * @ingroup sre_timer
 * SRE_timer错误码: 定时器句柄非法。
 *
 * 值: 0x02002e03
 *
 * 解决方案: 检查输入的定时器句柄是否正确。
 */
#define OS_ERRNO_TIMER_HANDLE_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x03)

/**
 * @ingroup sre_timer
 * SRE_timer错误码: 定时器定时时间参数非法。
 *
 * 值: 0x02002e04
 *
 * 解决方案: 定时器定时时间参数非法。
 */
#define OS_ERRNO_TIMER_INTERVAL_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x04)

/**
 * @ingroup sre_timer
 * SRE_timer错误码: 定时器工作模式参数非法。
 *
 * 值: 0x02002e05
 *
 * 解决方案: 查看定时器工作模式参数是否正确，参照工作模式配置枚举定义#TIMER_MODE_E。
 */
#define OS_ERRNO_TIMER_MODE_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x05)

/**
 * @ingroup sre_timer
 * SRE_timer错误码: 定时器类型参数非法。
 *
 * 值: 0x02002e06
 *
 * 解决方案: 查看定时器类型参数是否正确，参照类型配置枚举定义#TIMER_TYPE_E。
 */
#define OS_ERRNO_TIMER_CREATE_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x06)

/**
 * @ingroup sre_timer
 * SRE_timer错误码: 定时器类型参数非法。
 *
 * 值: 0x02002e06
 *
 * 解决方案: 查看定时器类型参数是否正确，参照类型配置枚举定义#TIMER_TYPE_E。
 */
#define OS_ERRNO_DELAY_MSEC_VALUE_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x07)

/**
 * @ingroup sre_timer
 * SRE_timer错误码: 定时器类型参数非法。
 *
 * 值: 0x02002e06
 *
 * 解决方案: 查看定时器类型参数是否正确，参照类型配置枚举定义#TIMER_TYPE_E。
 */
#define OS_ERRNO_DELAY_SEC_VALUE_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_TIMER, 0x08)


timer_event* SRE_TimerEventCreate(sw_timer_event_handler handler, void* priv_data);
INT32 SRE_TimerEventDestroy(timer_event* pstTevent);
UINT32 SRE_TimerEventStart(timer_event *pstTevent, timeval_t *time);
VOID SRE_FreeRunningCntrIntr(VOID);
UINT64 SRE_ReadTimestamp(VOID);
VOID SRE_TimerInterrupt(VOID);
VOID SRE_InitSwTimer(VOID);
VOID SRE_TimerEventStop(timer_event* pstTevent);

#endif
