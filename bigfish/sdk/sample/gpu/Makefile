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
CFLAGS += $(CFG_HI_SAMPLE_CFLAGS)


CFLAGS +=   -I$(SDK_INC_DIR) \
            -I$(SAMPLE_DIR)/common \
            -I$(SAMPLE_DIR)/gpu/src/common/inc \
            -I$(SAMPLE_DIR)/gpu/src/common/egl/inc \
            -I$(SAMPLE_DIR)/gpu/src/common/key/inc \
            -I$(SAMPLE_DIR)/gpu/src/common/texture/inc
ifeq ($(CFG_HI_GPU_MALI400_SUPPORT), y)
DEP_LIBS += $(HI_LIBS) -lMali
endif
ifeq ($(CFG_HI_GPU_MALI450_SUPPORT), y)
DEP_LIBS += $(HI_LIBS) -lMali
endif
ifeq ($(CFG_HI_GPU_MALI700_SUPPORT), y)
DEP_LIBS += $(HI_LIBS) -lmali -lm
endif



LIBPATH += -L$(SHARED_LIB_DIR)

ifdef CFG_HI_STATIC_LIB_ONLY
LIBPATH += -L$(STATIC_LIB_DIR)
endif

LIB = -Wl,--start-group $(SYS_LIBS) $(DEP_LIBS) -Wl,--end-group

CXX = ${CFG_HI_TOOLCHAINS_NAME}-c++
ifeq ($(CFG_HI_EGL_TYPE), fb)
CC+= -DHI3D_DEBUG -DLINUX -DEGL_API_FB 
CXX+= -DHI3D_DEBUG -DLINUX -DEGL_API_FB
ifeq ($(CFG_HI_GPU_MALI700_SUPPORT), y)
CC+= -DEGL_FBDEV
CXX+= -DEGL_FBDEV
endif
endif


CFG_INC = $(CFLAGS)

export  LIB LIBPATH CFG_INC COMMON_FILES CXX CC
all:
ifeq ($(CFG_HI_GPU), y)
	@$(AT)make -C src/es11/coverflow
	@$(AT)make -C src/es11/coverflow_vertical
	@$(AT)make -C src/es11/cylinder
	@$(AT)mkdir -p ./exe/es11
	@$(AT)mkdir -p ./exe/es11/coverflow_res
	@$(AT)mkdir -p ./exe/es11/cylinder_res
	@$(AT)mv src/es11/coverflow/coverflow ./exe/es11
	@$(AT)cp src/es11/coverflow/coverflow_res/* ./exe/es11/coverflow_res -rf
	@$(AT)mv src/es11/coverflow_vertical/coverflow_vertical ./exe/es11
	@$(AT)mv src/es11/cylinder/cylinder ./exe/es11
	@$(AT)cp src/es11/cylinder/cylinder_res/* ./exe/es11/cylinder_res -rf
	
	$(AT)find . -name "*.o" | xargs rm -rf
	$(AT)find . -name "Thumbs.db" | xargs rm -rf
endif

clean:
ifeq ($(CFG_HI_GPU), y)


	@$(AT)make -C src/es11/coverflow clean
	@$(AT)make -C src/es11/coverflow_vertical clean
	@$(AT)make -C src/es11/cylinder clean

	$(AT)rm ./exe -rf
endif

install:

uninstall:

