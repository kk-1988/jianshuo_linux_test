
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
    gFile = kzalloc();

}

void __exit hello_exit(void)
{
    cdev_dev(gDev);
    unregister_chrdev_region(devNum, subDevNum);
    return;
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");