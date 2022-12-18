#include <linux/device.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/types.h>
#include <linux/miscdevice.h>

unsigned long get_dram_size(void);

static ssize_t ddr_read(struct file *filp, char __user *buf,
                size_t count, loff_t *f_pos)
{
	unsigned long s;
	
	s = (get_dram_size() >> 20);
	if(copy_to_user(buf, &s, sizeof(s)))
		return -1;
	
	printk("Total ddr size :%lu MByte!\n", s);
	
	return sizeof(s); 
}

static struct file_operations ddr_fops =
{
        .owner  = THIS_MODULE,
        .read   = ddr_read,
};

static struct miscdevice ddr_misc = {
        .minor = MISC_DYNAMIC_MINOR,
        .name = "ddr_detect",
        .fops = &ddr_fops,
};
static int ddr_detect_init(void)
{
	if(misc_register(&ddr_misc))
		return -1;
	return 0;
}
static void ddr_detect_exit(void)
{
	misc_deregister(&ddr_misc);
}
module_init(ddr_detect_init);
module_exit(ddr_detect_exit);
MODULE_LICENSE("GPL");
