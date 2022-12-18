/*
 *  create the  /sys/fs/selinux/enforce
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/seq_file.h>
#include <linux/debugobjects.h>
#include <linux/list.h>
#include <asm/atomic.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/writeback.h>
#include <linux/sysctl.h>
#include <linux/gfp.h>

unsigned int enforce_stat = 1;

static ssize_t auto_enforce_show(struct kobject *kobj,
    struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%u\n", enforce_stat);
}

static ssize_t auto_enforce_store(struct kobject *kobj,
    struct kobj_attribute *attr,
    const char *buf, size_t n)
{
    int ret;
    unsigned long enforce_bit;
    ret = sscanf(buf, "%lu", &enforce_bit);
    if ((ret == 1) && ((enforce_bit == 1) || (enforce_bit == 0))){
        enforce_stat = enforce_bit;
        return n;
    }
    return -EINVAL;
}

static struct kobj_attribute auto_enforce_attr =
__ATTR(enforce, 0644, auto_enforce_show, auto_enforce_store);


static struct kobject *selinux_kobj;

static int __init enforce_init(void)
{
    int error;
    printk("create enforce\n");
    selinux_kobj = kobject_create_and_add("selinux", fs_kobj);
    if (!selinux_kobj)
        return -ENOMEM;
    error = sysfs_create_file(selinux_kobj, &auto_enforce_attr.attr);
    return 0;
}

module_init(enforce_init);

static void __exit enforce_exit(void)
{

    sysfs_remove_file(selinux_kobj, &auto_enforce_attr.attr);
    kobject_del(selinux_kobj);
    printk("remove enforce\n");
}

module_exit(enforce_exit);

MODULE_LICENSE("GPL");
