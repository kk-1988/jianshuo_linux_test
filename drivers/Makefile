ifneq ($(KERNELRELEASE), )
obj-m := helloDev.o
else
PWD := $(shell pwd)
KDIR := /lib/modules/`uname -r`/build
all:
	make -C $(KDIR) M=$(PWD)
clean:
	rm -rf *.o *.ko *.mod.c *.symvers *.c~ *~
endif