
obj-$(CONFIG_HIPCIE) += hipcie.o

hipcie-objs	:= pcie.o drv_i2c.o

ifeq ($(CONFIG_PCI_DEBUG),y)
	        EXTRA_CFLAGS += -DDEBUG
endif

