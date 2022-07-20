#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/slab.h>

#define BUFFER_MAX  (10)
#define OK          (0)
#define ERROR       (-1)

struct cdev *gDev;
struct file_operations *gFile;
dev_t devNum;
unsigned int subDevNum = 1;
int reg_major = 232;
int reg_minor  = 0;
char buffer[BUFFER_MAX];
struct semaphore sema;
int open_count = 0;

int hello_open(struct inode *p, struct file *f)
{
    open_count++;
    printk(KERN_EMERG"hello open\n");

    return 0;
}

int hello_close(struct inode *p, struct file *filp)
{
    open_count--;
    printk(KERN_EMERG"hello close\n");
    return 0;
}

ssize_t hello_write(struct file *f, const char __user *u, size_t s,  loff_t *l)
{
    printk(KERN_EMERG"hello write\n");
    return 0;
}

ssize_t hello_read(struct file *f, char __user *u, size_t s, loff_t *l)
{
    printk(KERN_EMERG"hello read\n");
    return 0;
}

int hello_init(void)
{
    devNum = MKDEV(reg_major, reg_minor);
    if(OK == register_chrdev_region(devNum, subDevNum, "helloworld")){
        printk(KERN_EMERG"register_chrdev_region ok\n");
    }else {
        printk(KERN_EMERG"register_chrdev_region error\n");
        return ERROR;
    }
    printk(KERN_EMERG"hello driver init\n");
    gDev = kzalloc(sizeof(struct cdev), GFP_KERNEL);
    gFile = kzalloc(sizeof(struct file_operations), GFP_KERNEL);
    gFile->open = hello_open;
    //gFile->release = hello_close;
    gFile->write = hello_write;
    gFile->read = hello_read;
    cdev_init(gDev, gFile);
    cdev_add(gDev, devNum, 3);

    return 0;
}

void __exit hello_exit(void)
{
    cdev_del(gDev);
    unregister_chrdev_region(devNum, subDevNum);
    return;
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
