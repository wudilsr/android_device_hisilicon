/******************************************************************************
 *    Secure OS loading module
 *    Copyright (c) 2013-2023 by Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By LYJ.
 *
******************************************************************************/
#include <common.h>
#include <linux/err.h>

#define TRUSTEDCORE_MAGIC "TRSTCORE"
#define TRUSTEDCORE_MAGIC_SIZE 8

extern void  execute_init_secure_kernel(ulong addr);

struct secure_img_header_t {
	unsigned char magic[TRUSTEDCORE_MAGIC_SIZE];
	u32 header_size;      //Header size
	u32 kernel_load_addr; //RTOSCK load address
	u32 kernel_size;      //RTOSCK size
	u32 task_num;         //TASK_NUM
	u32 task_total_size;
};

extern void dcache_enable(uint32_t unused);
extern void dcache_disable(void);

/*************************************************************
* Description:Start Secure OS
* param kloadaddr - Secure OS entry address
* return
**************************************************************/
void boot_secure_kernel(u32 kloadaddr)
{
	printf("Loading Secure OS ...\n");
	//dcache_disable();
	void (*secure_entry)(void) = (void(*)(void))(kloadaddr);
	secure_entry();
	printf("Back to boot\n");
}

void copy_secure_kernel_and_internal_task(struct secure_img_header_t* imgheader)
{
	char *dst_ptr = (char *)(imgheader->kernel_load_addr);
	char *src_ptr = (char *)((char *)imgheader + imgheader->header_size);
	//dcache_enable(0);
	/* Copy secure os image to executed address */
	memmove(dst_ptr, src_ptr, imgheader->kernel_size);
	printf("   move secure os image from src addr: 0x%X to dst addr:0x%X size:%u KB\n",
		(u32)src_ptr, (u32)dst_ptr, imgheader->kernel_size / 1024);

	/* Move internal tasks to their loacation, remove kernel */
	dst_ptr  = (char *)((char *)imgheader + imgheader->header_size);
	src_ptr += imgheader->kernel_size;

	memmove(dst_ptr, src_ptr, imgheader->task_total_size);
	printf("   move internal tasks from src addr: 0x%X to dst addr:0x%X size:%u KB\n",
		(u32)src_ptr, (u32)dst_ptr, imgheader->task_total_size / 1024);

        //dcache_disable();
}

/*************************************************************
* Description:execute secure os
* param addr -- Secure OS image address
* return
**************************************************************/
void  execute_init_secure_kernel(ulong addr)
{
	struct secure_img_header_t* imgheader;

	imgheader = (struct secure_img_header_t*)addr;

	printf("## Secure OS Image:\n");
	printf("   Header Size: 0x%X (%u KB)\n", imgheader->header_size, imgheader->header_size / 1024);
	printf("   Kernel Load Addresss: 0x%X\n", imgheader->kernel_load_addr);
	printf("   Kernel Size: 0x%x (%u KB)\n", imgheader->kernel_size, imgheader->kernel_size / 1024);
	printf("   Task Number: %d\n", imgheader->task_num);
	printf("   Task Total Size: 0x%X (%u KB)\n", imgheader->task_total_size, imgheader->task_total_size / 1024);

	copy_secure_kernel_and_internal_task(imgheader);
	boot_secure_kernel(imgheader->kernel_load_addr);

}

int is_trustedcore_img(char *buf)
{

	struct secure_img_header_t *hdr = (struct secure_img_header_t *)buf;
	if (memcmp(hdr->magic, TRUSTEDCORE_MAGIC, TRUSTEDCORE_MAGIC_SIZE))
		return 0;

	return 1;
}

int do_load_secure_os(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong    addr;
	int      rc = 0;

	if (argc < 2) {
		cmd_usage(cmdtp);
		return -EINVAL;
	}

	addr = simple_strtoul(argv[1], NULL, 16);
	printf ("## Starting Secure OS at 0x%08lX ...\n", addr);

	execute_init_secure_kernel(addr);
	printf ("## Succeed to load Secure OS\n");
	return rc;
}

U_BOOT_CMD(
		   loadsos, CONFIG_SYS_MAXARGS, 1,	do_load_secure_os,
		   "load secure os at address <addr>",
		   "  addr \n    - start secure os at address 'addr'\n"
		   );
