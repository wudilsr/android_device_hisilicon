/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfv2bO4a86Ra1cP5w/R608AW9MyvBFsCSDo8GzQMC4Jhtu/zShyENpjFzntvB+
qu9VLVDaDMuS6PPqlo/q4C86qlJ4Ce7RYbMClRRlhckoADodW/5taKKoOMM9DMu+LRQgxNJz
qdKdbJ+LZ9l4R4sV6hc0IN4G2XbJ871vdjivGyc+oJcqv/6X6xTK1rkQB8tc/g==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
 #include <asm/unistd.h>

#include <linux/module.h>
//#include <linux/config.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/fcntl.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/workqueue.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#if 1
#include <linux/semaphore.h>
#else
#include <asm/semaphore.h>
#endif
#include <linux/wait.h>
#include <asm/uaccess.h>
#include <asm/system.h>
#include <asm/io.h>

struct file *kfile_open(const char *filename, int flags, int mode)
{
    struct file *filp = filp_open(filename, flags, mode);
    return (IS_ERR(filp)) ? NULL : filp;
}

void kfile_close(struct file *filp)
{
    if (filp)
        filp_close(filp, NULL);
}

int kfile_read(char *buf, unsigned int len, struct file *filp)
{
    int readlen;
    mm_segment_t oldfs;

    if (filp == NULL)
        return -ENOENT;

    if (filp->f_op->read == NULL)
        return -ENOSYS;

    if (((filp->f_flags & O_ACCMODE) & (O_RDONLY | O_RDWR)) != 0)
        return -EACCES;

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    readlen = filp->f_op->read(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);

    return readlen;
}

int kfile_write(char *buf, int len, struct file *filp)
{
    int writelen;
    mm_segment_t oldfs;

    if (NULL == buf)
    {
        //printk("kfile_write: buf = NULL!\n");
        return -ENOENT;
    }

    if (filp == NULL)
        return -ENOENT;

    if (filp->f_op->write == NULL)
        return -ENOSYS;

    if (((filp->f_flags & O_ACCMODE) & (O_WRONLY | O_RDWR)) == 0)
        return -EACCES;

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    writelen = filp->f_op->write(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);

    return writelen;
}

int kfile_seek(loff_t offset, int origin, struct file *filp)
{
    int seeklen;
    mm_segment_t oldfs;

    if (filp == NULL)
        return -ENOENT;

    if (filp->f_op->llseek == NULL)
        return -ENOSYS;

    if (((filp->f_flags & O_ACCMODE) & (O_RDONLY | O_RDWR)) != 0)
        return -EACCES;

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    seeklen = filp->f_op->llseek(filp, offset, origin);
    set_fs(oldfs);

    return seeklen;
}


void dump(unsigned char data[], int len)
{
    int i;
    for(i=0; i<len; i++)
    {
        //printk("%02x ", data[i]);
    }
    //printk("\n");
}














