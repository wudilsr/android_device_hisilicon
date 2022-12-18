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
 * init multi ram disk
******************************************************************************/
#define pr_fmt(fmt) "initmrd: " fmt

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/syscalls.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/memblock.h>

#define MRD_NAME      "hisi.mrd"

struct ramdisk {
	ulong start;
	ulong size;

#define RD_STATUS_INVALID            0x00
#define RD_STATUS_SETUP              0x01
#define RD_STATUS_RESERVE            0x02
#define RD_STATUS_VFS                0x03
	int status;
};

static struct ramdisk ramdisks[CONFIG_BLK_DEV_RAM_COUNT] = {{0}};

/*
 * initmrd=3,0x10000000,0x50000000
 */
static int __init early_initmrd(char *p)
{
	unsigned int index;
	struct ramdisk *rd;
	char *endp;

	index = memparse(p, &endp);
	if (*endp != ',')
		return 0;

	if (index >= CONFIG_BLK_DEV_RAM_COUNT) {
		pr_notice("index %d out of range, CONFIG_BLK_DEV_RAM_COUNT is %d.\n", index, CONFIG_BLK_DEV_RAM_COUNT);
		return 0;
	}

	rd = &ramdisks[index];

	rd->start = memparse(endp + 1, &endp);
	if (*endp != ',')
		return 0;

	rd->size = memparse(endp + 1, NULL);

	if (rd->size)
		rd->status = RD_STATUS_SETUP;

	return 0;
}
early_param("initmrd", early_initmrd);
/*****************************************************************************/

static int __init reserve_one_ramdisk(int index, struct ramdisk *rd)
{
	if (!memblock_is_region_memory(rd->start, rd->size)) {
		pr_err("0x%08lx+0x%08lx is not a memory region, disabling initmrd:%d\n",
		       rd->start, rd->size, index);
		goto fail;
	}

	if (memblock_is_region_reserved(rd->start, rd->size)) {
		pr_err("0x%08lx+0x%08lx overlaps in-use memory region, disabling initmrd:%d\n",
		       rd->start, rd->size, index);
		goto fail;
	}

	memblock_reserve(rd->start, rd->size);

	rd->status = RD_STATUS_RESERVE;
	rd->start = __phys_to_virt(rd->start);

	return 0;
fail:
	rd->status = RD_STATUS_INVALID;

	return -1;
}
/*****************************************************************************/

void __init initmrd_reserve_memory(void)
{
	int ix;
	struct ramdisk *rd;

	for (ix = 0; ix < CONFIG_BLK_DEV_RAM_COUNT; ix++) {
		rd = &ramdisks[ix];
		if (rd->status == RD_STATUS_SETUP)
			reserve_one_ramdisk(ix, rd);
	}
}
/******************************************************************************/

static void __init move_one_vfs(int index, struct ramdisk *rd)
{
	int fd;
	char name[16];

	snprintf(name, sizeof(name), "/%s%d", MRD_NAME, index);
	fd = sys_open(name, O_WRONLY|O_CREAT, 0700);
	if (fd < 0) {
		pr_err("open %s failed.\n", name);
		goto fail;
	}

	sys_write(fd, (char *)rd->start, rd->size);
	sys_close(fd);

	rd->status = RD_STATUS_VFS;

fail:
	free_reserved_area(rd->start, rd->start + rd->size, 0, name);
}
/******************************************************************************/

static int __init move_all_vfs(void)
{
	int ix;
	struct ramdisk *rd;

	for (ix = 0; ix < CONFIG_BLK_DEV_RAM_COUNT; ix++) {
		rd = &ramdisks[ix];

		if (rd->status == RD_STATUS_RESERVE)
			move_one_vfs(ix, rd);
	}

	return 0;
}
rootfs_initcall(move_all_vfs);
/******************************************************************************/

static int __init create_ramdisk(char *name, int n)
{
	sys_unlink(name);
	return sys_mknod(name, S_IFBLK|0600, new_encode_dev(MKDEV(RAMDISK_MAJOR, n)));
}
/******************************************************************************/

static int __init init_one_ramdisk(int index)
{
	int ret;
	char *buf;
	char name_in[16];
	int fd_in, fd_out;
	int sz_in, sz_out;
	ulong remainder;
	ulong devsize = ~0UL;

	ret = create_ramdisk("/dev/ram", index);
	if (ret) {
		pr_err("create ramdisk /dev/ram device %d failed.\n", index);
		return ret;
	}

	snprintf(name_in, sizeof(name_in), "/%s%d", MRD_NAME, index);
	fd_in = sys_open(name_in, O_RDONLY, 0);
	if (fd_in < 0) {
		pr_err("open %s failed.\n", name_in);
		ret = -1;
		goto in_fail;
	}

	fd_out = sys_open("/dev/ram", O_RDWR, 0);
	if (fd_out < 0) {
		pr_err("open /dev/ram failed.\n");
		ret = -1;
		goto out_fail;
	}

	if (!sys_ioctl(fd_out, BLKGETSIZE, (ulong)&devsize))
		devsize = devsize >> (BLOCK_SIZE_BITS - 9);

	buf = kmalloc(BLOCK_SIZE, GFP_KERNEL);
	if (!buf) {
		pr_err("could not allocate buffer\n");
		ret = -1;
		goto malloc_fail;
	}

	remainder = devsize;
	do {
		sz_in = sys_read(fd_in, buf, BLOCK_SIZE);
		if (sz_in <= 0) {
			if (sz_in)
				pr_err("read %s fail.\n", name_in);
			break;
		}

		if (!--remainder) {
			pr_err("/dev/ram%d out of size, CONFIG_BLK_DEV_RAM_SIZE is %luK.\n", index, devsize);
			break;
		}

		sz_out = sys_write(fd_out, buf, sz_in);
		if (sz_out != sz_in) {
			pr_err("write fail");
			break;
		}
	} while (sz_in == BLOCK_SIZE);

	kfree(buf);
	ret = 0;

malloc_fail:
	sys_close(fd_out);
out_fail:
	sys_close(fd_in);
in_fail:
	sys_unlink("/dev/ram");
	sys_unlink(name_in);
	return ret;
}
/******************************************************************************/

static int __init init_ramdisk(void)
{
	int ix;
	struct ramdisk *rd;

	for (ix = 0; ix < CONFIG_BLK_DEV_RAM_COUNT; ix++) {
		rd = &ramdisks[ix];
		if (rd->status == RD_STATUS_VFS)
			init_one_ramdisk(ix);
	}
	return 0;
}
late_initcall(init_ramdisk);
