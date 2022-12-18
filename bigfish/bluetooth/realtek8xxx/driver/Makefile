LD_CFLAGS += -D__linux__
EXTRA_CFLAGS=-fno-pic

#obj-y += bt_usb.o

obj-m += rtk_btusb.o

bt_usb-objs += \
	rtk_btusb.o


KDIR    := $(ANDROID_PRODUCT_OUT)/obj/KERNEL_OBJ
#KDIR    :=  /home/zhaomenglei/work/android4.4/spc055_8723/out/target/product/Hi3798MV100/obj/KERNEL_OBJ
#KVER ?= 3.1.10


PWD := $(shell pwd)
CURFOLDER ?= $(pwd)

EXTRA_CFLAGS += -I$(CURFOLDER)/include -D__linux__

bt_usb:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	mkdir -p $(ANDROID_PRODUCT_OUT)/system/lib/modules
	cp -fv $(PWD)/rtk_btusb.ko $(ANDROID_PRODUCT_OUT)/system/lib/modules/btusb.ko
	make clean


clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	$(RM) Module.markers
	$(RM) modules.order
