#the kernel path:
# LINUX := /v5/4.4-master/out/target/product/Hi3716CV200/obj/KERNEL_OBJ
LINUX         := ?
ARCH          := arm
CROSS_COMPILE := arm-hisiv200-linux-

EXTRA_CFLAGS := -g
obj-m   += create.o
create-objs :=  create_enforce.o

default:
	make -C $(LINUX) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) SUBDIRS=$(shell pwd) modules
clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions
	rm -f Module.markers
	rm -f Module.symvers
	rm -f modules.order
	rm -f ./src/*.o
	rm -f ./src/.*.o.cmd
	rm -f ./src/gki/*.o
	rm -f ./src/gki/.*.o.cmd
