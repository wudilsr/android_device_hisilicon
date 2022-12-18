/*
 * FileName:      root_monitor_common.h
 * Author:        z00321956
 * Description:   root monitor common
 * Version:       0.0.1
 * Date:          2016-04-01
 */

#ifndef _ROOT_COMMON_H_
#define _ROOT_COMMON_H_

#include <linux/module.h>
#include <linux/sched.h>
#include "teek_client_type.h"

#define ROOTAGENT_TAG "rootagent-ca"

enum {
	ROOTAGENT_DEBUG_ERROR				= 1U << 0,
	ROOTAGENT_DEBUG_AGENT				= 1U << 1,
	ROOTAGENT_DEBUG_API					= 1U << 2,
	ROOTAGENT_DEBUG_CRYPTO				= 1U << 3,
	ROOTAGENT_DEBUG_MEM					= 1U << 4,
	ROOTAGENT_DEBUG_DUMPHEX				= 1U << 5,
	ROOTAGENT_DEBUG_DUMMY				= 1U << 6,
	DEBUG_NEED_2_DELETE                 = 1U << 7,
};

static uint32_t antiroot_debug_mask = ROOTAGENT_DEBUG_ERROR
		| ROOTAGENT_DEBUG_API   | ROOTAGENT_DEBUG_MEM
		| ROOTAGENT_DEBUG_AGENT | ROOTAGENT_DEBUG_DUMPHEX
		| ROOTAGENT_DEBUG_DUMMY | DEBUG_NEED_2_DELETE;

#define AR_Debug(fmt, args...) pr_info("(%s:%s:%d) " fmt, \
		ROOTAGENT_TAG, __func__, __LINE__, ## args)

#define antiroot_debug(mask, x...) \
	do { \
		if (antiroot_debug_mask & mask) \
		AR_Debug(x); \
	} while (0)

#define antiroot_error(fmt, args...) printk(KERN_ERR "%s: %s: " fmt "\n", \
         ROOTAGENT_TAG, __func__, ## args)

#define antiroot_warning(fmt, args...) printk(KERN_WARNING "%s: %s: " fmt "\n", \
         ROOTAGENT_TAG, __func__, ## args)

#define antiroot_info(fmt, args...) printk(KERN_INFO "%s: %s: " fmt "\n", \
        ROOTAGENT_TAG, __func__, ## args)

void dump_hex(unsigned char* hex, uint32_t len);


#define MAGIC 0x53525748
#define VERSION 1

#define KERNEL_CODE_LENGTH_SHA 20
#define SYSTEM_CALL_LENGTH_SHA 20
#define SELINUX_HOOKS_LENGTH_SHA 20
#define CHALLENGE_MAX_LENGTH 15

#define CHALLENGE_KEY_LENGTH		32
#define CHALLENGE_REQ_KEY_LENGTH	CHALLENGE_KEY_LENGTH
#define RESPONSE_COUNTER_LENGTH		CHALLENGE_KEY_LENGTH
#define CHALLENGE_NOUNCE_LENGTH		CHALLENGE_KEY_LENGTH

#define IV_SIZE 16
#define ANTIROOT_SRC_LEN 4000
#define ANTIROOT_DST_LEN             (IV_LENGTH + ANTIROOT_SRC_LEN)

/**
 * @ingroup root agent cmd
 *
 * @brief: root agent command id.
 *
 */
enum ROOTAGENT_CMD {
	ROOTAGENT_CONFIG_ID = 0x01,      /** set the white information */
	ROOTAGENT_CHALLENGE_ID = 0x02,   /** request a challenge */
	ROOTAGENT_RESPONSE_ID = 0x03      /** return the scanning result */
};

enum ROOTAGENT_OPID {
    RAOPID_TERM = 0,
    RAOPID_KCODE,
    RAOPID_SYSCALL,
    RAOPID_RPROCS,
    RAOPID_SELINUX_STATUS,
    RAOPID_SELINUX_HOOK,
    RAOPID_SELINUX_POLICY,
    RAOPID_HIDDENTHREAD,
    RAOPID_FRAMEWORK,
    RAOPID_SYSAPP,
    RAOPID_CPULOAD,
    RAOPID_BATTERY,
    RAOPID_CHARGING,
    RAOPID_TIME,
    RAOPID_NOOP,
    RAOPID_MAXID
};

typedef enum {
    RA_ERROR_PH_ROOT   = 0xFFFF9110,
    RA_ERROR_PH_LOCK   = 0xFFFF9119,
}ROOTAGENT_ERROR;

/** communication with TEE-OS start */

typedef struct {
   uint8_t kcodes[KERNEL_CODE_LENGTH_SHA];           /** kernel code SHA1 */
   uint8_t syscalls[SYSTEM_CALL_LENGTH_SHA];         /** system call table SHA1 */
   uint32_t selinux;                                 /** SE-Linux state */
   uint8_t sehooks[SELINUX_HOOKS_LENGTH_SHA];         /** struct security_operations SHA1 */
   uint32_t proclength;
} RAGENT_WHITE_LIST;

typedef struct {
   uint8_t cha_req_key[CHALLENGE_REQ_KEY_LENGTH];     /** 16 byte aes key cipher challenge request  */
   uint8_t cha_key[CHALLENGE_KEY_LENGTH];             /** 16 byte aes key cipher challenge  */
} RAGENT_CIPHER_KEY;

typedef struct {
   RAGENT_CIPHER_KEY cipher_key;                      /** cipher key */
   RAGENT_WHITE_LIST white_list;                      /** white listi */
} RAGENT_CONFIG;

/**
 * @ingroup  RAGENT_CHALLENGE
 *
 * @brief: challenge information
 *
 */
typedef struct {
	uint32_t cpuload;                  /** CPU Usage 0~100 */
	uint32_t battery;                /** remaining battery 0~100 */
	uint32_t charging;              /** Charging or not 0~1 */
	uint32_t time;        /** Current time in UNIX Epoch time. same as the time() systemcall */
    uint32_t timezone;    /** Timezone in minutes. see tz_minuteswest in gettimeofday(). e.g. Beijing +8 is -480 */
    uint8_t nounce[CHALLENGE_NOUNCE_LENGTH]; /** nounce as key for responce */
    uint32_t challengeid[CHALLENGE_MAX_LENGTH]; /** challenge association */
} RAGENT_CHALLENGE;

typedef struct {
  RAGENT_WHITE_LIST runtime_white_list;  /** white information in runtime */
  uint32_t proc_integrated;      /** integrated of process chain  */
  uint32_t noop;                 /** Heartbeat */
} RAGENT_RESPONSE;

/**
 * @ingroup  TEE_RM_CONTENT
 *
 * @brief: specific content
 *
 */
typedef union {
    RAGENT_CONFIG config;       /** white information */
    RAGENT_CHALLENGE challenge; /** challenge generated by TEE */
    RAGENT_RESPONSE response;   /** response (the result of scanning) */
}RAGENT_CONTENT;

/**
 * @ingroup  TEE_RM_COMMAND
 *
 * @brief: root monitor command information.
 *
 */
typedef struct {
    uint32_t magic;          /** scanner identify */
    uint32_t version;        /** version */
	uint32_t interface;      /** interface type, corresponding to content*/
	RAGENT_CONTENT content;  /** specific content(configuration, challenge, response), depend on interface */
}RAGENT_COMMAND;

/** communication with TEE-OS end */

/**
 * @ingroup  TEE_RM_ROOTPROC
 *
 * @brief: root process list
 *
 */
typedef struct {
   uint32_t length;
   uint8_t* procid;
} RAGENT_ROOTPROC;
#endif
