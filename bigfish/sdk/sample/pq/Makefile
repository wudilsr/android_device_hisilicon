#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../..
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
COMMON_DIR=$(SDK_DIR)/source/common

CFLAGS += $(CFG_HI_SAMPLE_CFLAGS)

INCLUDE =   -I$(SDK_INC_DIR)        \
            -I$(SAMPLE_DIR)/common
LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

APP = sample_pq

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3718cv100 hi3719cv100 hi3718mv100 hi3719mv100),)
OBJS := sample_pq_v1.o  
else
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100 hi3798mv100 hi3796mv100 hi3798cv200_a hi3716mv410 hi3716mv420),)
OBJS := sample_pq_v2.o  
endif
endif


#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall


all:$(APP)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

$(APP): $(OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f *.o
	-$(AT)rm -f $(APP)

install:

uninstall:
