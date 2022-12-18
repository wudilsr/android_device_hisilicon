#include <linux/uaccess.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/random.h>
#include <linux/wakelock.h>
#include <linux/suspend.h>
#include <linux/notifier.h>
#include <linux/delay.h>
#include "rootagent_api.h"
#include "rootagent_common.h"

#ifndef CONFIG_HUAWEI_ROOT_SCAN_DUMMY_API
#include "hw_rscan_interface.h"
#else
#include "rscan_dummy.h"
#endif

//#define BENCHMARK

#define REPEATNUM  3
#define SCAN_CYCLE 1*10*1000   /* 10 seconds */
#define ROOTAGENT_VERSION "rootagent-v0.03"

static void do_work(struct work_struct *unused);
static DECLARE_WORK(teeagent_work, do_work);
static struct workqueue_struct *teeagent_workqueue;

static struct timer_list teeagent_timer;

#define PM_SUSPEND  0x1
#define PM_RESUME 0x0
static int antiroot_sr_flag = PM_RESUME; //0 for resume successful 1 for suspend

module_param_named(debug_mask, antiroot_debug_mask, uint, S_IWUSR | S_IRUGO);

#define DEBUG_ROOTAGENT
#ifdef DEBUG_ROOTAGENT

void dump_hex(unsigned char* hex, uint32_t len)
{
	if (NULL == hex) {
		("Bad expected parameter.\n");
		return;
	}
	uint32_t i;

	for (i = 0; i < (len - len%16); i += 16) {
		antiroot_debug(ROOTAGENT_DEBUG_DUMPHEX,
				"     %02x %02x %02x %02x   %02x %02x %02x %02x"
				"   %02x %02x %02x %02x   %02x %02x %02x %02x  \n",
				hex[i + 0], hex[i + 1], hex[i + 2], hex[i + 3],
				hex[i + 4], hex[i + 5], hex[i + 6], hex[i + 7],
				hex[i + 8], hex[i + 9], hex[i + 10], hex[i + 11],
				hex[i + 12], hex[i + 13], hex[i + 14], hex[i + 15]);
	}

	for (i = (len - len%16); i < len; i++)
		antiroot_debug(ROOTAGENT_DEBUG_DUMPHEX,
				"     hex[%d] = %02x\n", i, hex[i]);
}
#else
void dump_hex(unsigned char* hex, uint32_t len) {};
#endif




static int req_challenge (RAGENT_CHALLENGE *chal){

	TEEC_Result teer;
	if (0) {
		struct timeval tv;
		chal->cpuload = prandom_u32() % 101;
		chal->battery = prandom_u32() % 101;
		chal->charging = prandom_u32() % 2;
		do_gettimeofday(&tv);
		chal->time = tv.tv_sec;
		chal->timezone = prandom_u32() % (24 * 60) - 12 * 60;
	} else {
		struct rscan_status status;
		if (rscan_get_status(&status)) {
			antiroot_warning("rscan_get_status failed\n");
			return -1;
		}
		chal->cpuload = status.cpuload;
		chal->battery = status.battery;
		chal->charging = status.charging;
		chal->time = status.time;
		chal->timezone = status.timezone;
	}

	if ((teer = request_challenge(chal)) != TEEC_SUCCESS) {
		antiroot_warning("request_challenge failed 0x%x\n", teer);
		return -1;
	}
	return 0;
}

static int send_response (const RAGENT_CHALLENGE *chal){

	dynamic_result_t scan;
	int op_mask = 0;
	RAGENT_RESPONSE resp;
    RAGENT_ROOTPROC root_proc;
	TEEC_Result teer;
	int id_count;
    int opid;

	for (id_count = 0; id_count < CHALLENGE_MAX_LENGTH && chal->challengeid[id_count]; id_count ++){
		opid = chal->challengeid[id_count];
		antiroot_debug(ROOTAGENT_DEBUG_AGENT, "gen_response opid=%d\n", opid);
		if (opid <= 0 || opid >= RAOPID_MAXID){
			antiroot_warning("gen_response invalid OPID %d\n", opid);
			return 1;
		}
		switch (opid){
			case RAOPID_KCODE:           op_mask |= D_RSOPID_KCODE; break;
			case RAOPID_SYSCALL:         op_mask |= D_RSOPID_SYS_CALL; break;
			case RAOPID_RPROCS:          op_mask |= D_RSOPID_RRPOCS; break;
			case RAOPID_SELINUX_STATUS:  op_mask |= D_RSOPID_SE_STATUS; break;
			case RAOPID_SELINUX_HOOK:    op_mask |= D_RSOPID_SE_HOOKS; break;
			case RAOPID_HIDDENTHREAD:    op_mask |= D_RSOPID_HID_PROC; break;
			case RAOPID_NOOP: break;
			default:
				antiroot_warning("gen_response invalid OPID %d\n", opid);
				return 1;
		}
	}

	if (op_mask != 0)
		rscan_dynamic_raw(op_mask, &scan);

    memset(&resp, 0x0, sizeof(RAGENT_RESPONSE));
    memset(&root_proc, 0x0, sizeof(RAGENT_ROOTPROC));
	for (id_count = 0; id_count < CHALLENGE_MAX_LENGTH && chal->challengeid[id_count]; id_count ++) {
		switch (chal->challengeid[id_count]) {
			case RAOPID_KCODE: memcpy(resp.runtime_white_list.kcodes, scan.kcode, SHA1_DIGEST_SIZE); break;
			case RAOPID_SYSCALL: memcpy(resp.runtime_white_list.syscalls, scan.syscalls, SHA1_DIGEST_SIZE); break;
			case RAOPID_RPROCS:
				root_proc.length = strlen(scan.rprocs);
				root_proc.procid = scan.rprocs;
				break;
			case RAOPID_SELINUX_STATUS: resp.runtime_white_list.selinux = scan.seenforcing != 1; break;
			case RAOPID_SELINUX_HOOK: memcpy(resp.runtime_white_list.sehooks, scan.sehooks, SHA1_DIGEST_SIZE); break;
			case RAOPID_HIDDENTHREAD: resp.proc_integrated = scan.hidproc; break;
			case RAOPID_NOOP: resp.noop = 0; break;
			default: break;
		}
	}

	if ((teer = feedback_response(&resp, &root_proc)) != TEEC_SUCCESS) {
		antiroot_warning("feedback_response failed 0x%x\n", teer);
		return 1;
	}
	return 0;
}

static int system_sr_notify(struct notifier_block *nb,
    unsigned long pm_event, void *unused)
{
    switch (pm_event) {
    case PM_SUSPEND_PREPARE:
        antiroot_sr_flag = PM_SUSPEND;
        antiroot_warning("system is suspending.\n");
        break;
    case PM_POST_SUSPEND:
        antiroot_sr_flag = PM_RESUME;
        antiroot_warning("system resume successful.\n");
        break;
    default:
        break;
    }
    return 0;
}

static struct notifier_block system_sr_notifier = {
    .notifier_call = system_sr_notify,
};
static void do_work(struct work_struct *unused)
{
    struct wake_lock wakelock;
	RAGENT_CHALLENGE chal;
    int repeat = REPEATNUM;

    wake_lock_init(&wakelock, WAKE_LOCK_SUSPEND, "rootscan");
    wake_lock(&wakelock);
    while(antiroot_sr_flag){
        antiroot_warning("system is suspend now, try later!\n");
        msleep(50);
    }

    memset(&chal, 0x0, sizeof(RAGENT_CHALLENGE));
    antiroot_info("do_work begin!\n");
    do{
        if (!req_challenge(&chal)){
			if(send_response(&chal)){
#if 0
				root_monitor_finalize();
				del_timer_sync(&teeagent_timer);
				destroy_workqueue(teeagent_workqueue);
				teeagent_workqueue = NULL;
				unregister_pm_notifier(&system_sr_notifier);
#endif
			}
			break;
		}
    }while(--repeat);
    antiroot_info("do_work end!\n");
out:
    wake_unlock(&wakelock);
    wake_lock_destroy(&wakelock);
}


static void teeagent_timer_func (unsigned long unused){

    antiroot_info("timer_callback begin!\n");
	mod_timer(&teeagent_timer, jiffies + msecs_to_jiffies(SCAN_CYCLE));

#ifdef CONFIG_HUAWEI_ROOT_SCAN_DUMMY_API
	if (CA_DISABLE == get_rootagent_enable())
		return;
#endif

	if (queue_work(teeagent_workqueue, &teeagent_work) == 0) {
		antiroot_error("Timer add work queue failed\n");
	}
    antiroot_error("Timer interrupt call back, end!\n");
	return;
}

static int rscan_get_baseline(dynamic_result_t *base) {
	int ret = 0;
	if (base) {
		ret = load_rproc_whitelist(base->rprocs, MAX_RPROC_SIZE);
		if(ret)
			return ret;
		rscan_dynamic_raw(D_RSOPID_KCODE | D_RSOPID_SYS_CALL |
				D_RSOPID_SE_HOOKS, base);
		base->seenforcing = 0;
		return ret;
	}
	return -1;
}

static int tee_init(void)
{
	TEEC_Result teer;
	RAGENT_CONFIG config;
	RAGENT_ROOTPROC root_proc;
	dynamic_result_t boot_scan;

	if(0 != rscan_get_baseline(&boot_scan)) {
		antiroot_error("rscan_get_baseline failed.\n");
		return -1;
	}

	if ((teer = root_monitor_tee_init()) != TEEC_SUCCESS) {
		antiroot_error("root_monitor_tee_init failed %d\n", teer);
		return -1;
	}

	memcpy(config.white_list.kcodes, boot_scan.kcode, KERNEL_CODE_LENGTH_SHA);
	memcpy(config.white_list.syscalls, boot_scan.syscalls, SYSTEM_CALL_LENGTH_SHA);
	config.white_list.selinux = 0;
	memcpy(config.white_list.sehooks, boot_scan.sehooks, SELINUX_HOOKS_LENGTH_SHA);
	get_random_bytes(&config.cipher_key.cha_req_key, CHALLENGE_REQ_KEY_LENGTH);
	get_random_bytes(&config.cipher_key.cha_key, CHALLENGE_KEY_LENGTH);
	root_proc.length = strlen(boot_scan.rprocs);
	antiroot_debug(ROOTAGENT_DEBUG_AGENT,
			"proc length %d\n",root_proc.length);
	root_proc.procid = (uint8_t*)(boot_scan.rprocs);
	if ((teer = setting_config(&config, &root_proc)) != TEEC_SUCCESS) {
		antiroot_warning("setting_config failed %d\n", teer);
		root_monitor_finalize();
		return -1;
	}

	return 0;
}

#ifdef CONFIG_HUAWEI_ROOT_SCAN_DUMMY_API
static int dummy_init_once = 0;
int dummy_tee_init(void)
{
	if (0 == dummy_init_once) {
		dummy_init_once = 1;
		antiroot_debug(ROOTAGENT_DEBUG_AGENT,
				"dummy_tee_init enter now.\n");
		tee_init();
	} else {
		antiroot_debug(ROOTAGENT_DEBUG_AGENT,
				"dummy_tee_init done before, do nothing now.\n");
	}
	return 0;
}
#endif

static __init int tee_rootscan_init(void)
{
    int ret;

#ifdef CONFIG_HUAWEI_ROOT_SCAN_DUMMY_API
	antiroot_debug(ROOTAGENT_DEBUG_AGENT,
			"tee_rootscan_init versin: %s.\n", ROOTAGENT_VERSION);
	rscan_dummy_init();
#endif

	 teeagent_workqueue = create_singlethread_workqueue("antiroot-ca");
    if(!teeagent_workqueue){
        antiroot_error("fail to create queue.\n");
        return -1;
    }

    ret = register_pm_notifier(&system_sr_notifier);
    if (ret) {
        antiroot_error("fail to register system_sr_notifier.\n");
		destroy_workqueue(teeagent_workqueue);
		return -1;
    }

#ifndef CONFIG_HUAWEI_ROOT_SCAN_DUMMY_API
	ret = tee_init();
	if (ret) {
		antiroot_error("tee_init() failed. ret = %d.\n");
		unregister_pm_notifier(&system_sr_notifier);
		destroy_workqueue(teeagent_workqueue);
		return -1;
	}
#endif

	teeagent_timer.function = teeagent_timer_func;
	teeagent_timer.data = 0;
	init_timer(&teeagent_timer);
	mod_timer(&teeagent_timer, jiffies + msecs_to_jiffies(SCAN_CYCLE));

	return 0;
}

void tee_rootscan_exit(void)
{
	del_timer_sync(&teeagent_timer);
	destroy_workqueue(teeagent_workqueue);
	teeagent_workqueue = NULL;
    unregister_pm_notifier(&system_sr_notifier);
#ifdef CONFIG_HUAWEI_ROOT_SCAN_DUMMY_API
	rscan_dummy_exit();
#endif
}

module_init(tee_rootscan_init);
module_exit(tee_rootscan_exit);
