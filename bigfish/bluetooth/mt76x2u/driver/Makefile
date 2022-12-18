CHIPSET = mt7632 mt7662

DIR = $(shell pwd)

EXTRA_CFLAGS := -DMT7632 -DMT7662 -g

#LINUX_SRC_MODULE = /lib/modules/$(shell uname -r)/kernel/drivers/bluetooth/
LINUX_SRC_MODULE := $(ANDROID_PRODUCT_OUT)/obj/KERNEL_OBJ

PWD     := $(shell pwd)

MOD_NAME = btmtk_usb

export CHIPSET DIR


obj-m += $(MOD_NAME).o

all: fw
	make -C $(LINUX_SRC_MODULE) M=$(PWD) modules
	mkdir -p $(ANDROID_PRODUCT_OUT)/system/lib/modules
	mkdir -p $(ANDROID_PRODUCT_OUT)/system/etc/firmware
	cp -fv $(PWD)/btmtk_usb.ko $(ANDROID_PRODUCT_OUT)/system/lib/modules/btusb.ko
	cp -fv $(PWD)/mcu/bin/mt7662_patch_e3_hdr.bin  $(ANDROID_PRODUCT_OUT)/system/etc/firmware/mt7662_patch_e3_hdr.bin
	make clean

fw:
	gcc -g bin2h.c -o bin2h
	./bin2h

#install:
#	make INSTALL_MOD_DIR=kernel/drivers/bluetooth -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules_install

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f *.o bin2h
	rm -rf ./mcu/include/*.h
	rm -rf ./mt7662_rom_patch.h

PHONY += all fw install clean
.PHONY: $(PHONY)

