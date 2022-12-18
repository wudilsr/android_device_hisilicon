/******************************************************************************
 *  Copyright (C) 2014 Hisilicon Technologies CO.,LTD.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Create By Cai Zhiyong 2014.12.22
 *
******************************************************************************/
#define pr_fmt(fmt) "capable: " fmt

#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/security.h>
#include <linux/uidgid.h>
#include <linux/cred.h>
#include <linux/sched.h>
#include <linux/user_namespace.h>
#include <linux/init_task.h>
#include <linux/syscalls.h>
#include <linux/vmalloc.h>
#include <linux/kernel.h>
#include <linux/slab.h>

#include "rsa.h"
#include "bignum.h"

struct cap_info {
	char comm[TASK_COMM_LEN];
	pid_t pid;
#define MAX_RAND_VALUE         20
	char randval[MAX_RAND_VALUE];
	u64 jiffies;
};

#define MAX_CAP         8

struct cap_ctrl {
	struct mutex mutex;
	struct cap_info cap[MAX_CAP];
};

static struct cap_ctrl *capctrl = NULL;

#define SZ_KEY         256

/******************************************************************************/
void hicap_vfree(void *ptr)
{
	vfree(ptr);
}

void *hicap_vmalloc(unsigned int size)
{
	return vmalloc(size);
}

static struct cap_info *__new_cap(struct cap_ctrl *ctrl)
{
	int ix;
	struct cap_info *info;

	for (ix = 0; ix < MAX_CAP; ix++) {
		info = &ctrl->cap[ix];

		if (info->jiffies == 0 ||
		    time_after64(get_jiffies_64(), info->jiffies + 40 *HZ))
			return info;
	}

	return NULL;
}
/******************************************************************************/

static void __free_cap(struct cap_ctrl *ctrl, struct cap_info *info)
{
	if (!info)
		return;

	info->jiffies = 0;
}
/******************************************************************************/

static struct cap_info *__find_cap(struct cap_ctrl *ctrl)
{
	int ix;
	struct cap_info *info;

	for (ix = 0; ix < MAX_CAP; ix++) {
		info = &ctrl->cap[ix];

		if (info->jiffies != 0 &&
		    info->pid == current->pid &&
		    !strncmp(info->comm, current->comm, TASK_COMM_LEN) &&
		    time_before64(get_jiffies_64(), info->jiffies + 40 *HZ))
			return info;
	}

	return NULL;
}
/******************************************************************************/

static int setcap_full(void)
{
	struct cred *new;

	new = prepare_creds();
	if (!new)
		return -ENOMEM;

	new->cap_effective = CAP_FULL_SET;
	new->cap_permitted = CAP_FULL_SET;
	new->cap_inheritable = CAP_FULL_SET;

	return commit_creds(new);
}
/******************************************************************************/

static long cap_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret = -ENOTTY;
	struct cap_info *info = NULL;

	mutex_lock(&capctrl->mutex);

	if (cmd == 0x100) {
		char buf[MAX_RAND_VALUE];

		get_random_bytes(buf, MAX_RAND_VALUE);

		if (copy_to_user((char __user *)arg, buf, MAX_RAND_VALUE)) {
			ret = -EFAULT;
			goto fail;
		}

		info = __new_cap(capctrl);
		if (!info) {
			ret = -ENOMEM;
			goto fail;
		}

		info->jiffies = get_jiffies_64();

		strncpy(info->comm, current->comm, TASK_COMM_LEN);

		info->pid = current->pid;

		memcpy(info->randval, buf, MAX_RAND_VALUE);

		ret = 0;

	} else if (cmd == 0x101) {
		rsa_context rsa;
		unsigned char *rsa_signtext;

		rsa_signtext = vmalloc(SZ_KEY);
		if (!rsa_signtext) {
			ret = -ENOMEM;
			goto fail;
		}

		if (hicap_rsa_init(&rsa, RSA_PKCS_V15, 0)) {
			ret = -ENOMEM;
			goto verify_fail;
		}
		rsa.len = SZ_KEY;

		if (copy_from_user(rsa_signtext, (char __user *)arg, SZ_KEY)) {
			ret = -EFAULT;
			goto verify_fail;
		}

		info = __find_cap(capctrl);
		if (!info) {
			ret = -ENOMEM;
			goto verify_fail;
		}

		hicap_rsa_set_pubkey(&rsa);

		if (hicap_rsa_check_pubkey(&rsa)) {
			pr_err("public key fail.\n");
			goto verify_fail;
		}

		if (hicap_rsa_pkcs1_verify(&rsa, RSA_PUBLIC, SIG_RSA_SHA1,
			MAX_RAND_VALUE, info->randval, rsa_signtext)) {
			ret = -EFAULT;
			goto verify_fail;
		}

		ret = setcap_full();

verify_fail:
		__free_cap(capctrl, info);
		hicap_rsa_free(&rsa);
		vfree(rsa_signtext);
	}

fail:
	mutex_unlock(&capctrl->mutex);

	return ret;
}
/******************************************************************************/

static struct file_operations cap_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl  = cap_ioctl,
	.compat_ioctl    = cap_ioctl,
};
/******************************************************************************/

static struct miscdevice cap_miscdev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "capable",
	.fops = &cap_fops,
	.mode = 0644,
};
/******************************************************************************/

static int __init capdev_init(void)
{
	int ret;

	capctrl = vmalloc(sizeof(struct cap_ctrl));
	if (!capctrl) {
		pr_err("out of memory.\n");
		return -ENOMEM;
	}
	memset(capctrl, 0, sizeof(struct cap_ctrl));

	ret = misc_register(&cap_miscdev);
	if (ret) {
		pr_err("unable to register driver capable.\n");
		goto fail;
	}

	mutex_init(&capctrl->mutex);

	return 0;
fail:
	vfree(capctrl);
	return ret;
}
module_init(capdev_init);
/******************************************************************************/

static void __exit capdev_exit(void)
{
	misc_deregister(&cap_miscdev);
	vfree(capctrl);
}
module_exit(capdev_exit);
/******************************************************************************/

MODULE_DESCRIPTION("capable driver 1.0");
MODULE_AUTHOR("Caizhiyong");
MODULE_LICENSE("Commercial product");
