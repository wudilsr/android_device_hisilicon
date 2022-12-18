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

ifeq ($(CFG_HI_GPU_MALI400_SUPPORT), y)
CFLAGS +=   -I$(SDK_INC_DIR) \
            -I$(SAMPLE_DIR)/common \
            -I$(SAMPLE_DIR)/gpu/mali400/common/inc \
            -I$(SAMPLE_DIR)/gpu/mali400/common/egl/inc \
            -I$(SAMPLE_DIR)/gpu/mali400/common/key/inc \
            -I$(SAMPLE_DIR)/gpu/mali400/common/texture/inc
DEP_LIBS += $(HI_LIBS) -lMali
endif
ifeq ($(CFG_HI_GPU_MALI450_SUPPORT), y)
CFLAGS +=   -I$(SDK_INC_DIR) \
            -I$(SAMPLE_DIR)/common \
            -I$(SAMPLE_DIR)/gpu/mali400/common/inc \
            -I$(SAMPLE_DIR)/gpu/mali400/common/egl/inc \
            -I$(SAMPLE_DIR)/gpu/mali400/common/key/inc \
            -I$(SAMPLE_DIR)/gpu/mali400/common/texture/inc
DEP_LIBS += $(HI_LIBS) -lMali
endif
ifeq ($(CFG_HI_GPU_MALI700_SUPPORT), y)
target= mali700
CFLAGS +=   -I$(SDK_INC_DIR) \
	    -I$(SAMPLE_DIR)/common \
	    -I$(SAMPLE_DIR)/gpu/mali700/common/ \
	    -I$(SAMPLE_DIR)/gpu/mali700/common/inc \
	    -I$(SAMPLE_DIR)/gpu/mali700/common/egl/inc \
	    -I$(SAMPLE_DIR)/gpu/mali700/common/key/inc \
            -I$(SAMPLE_DIR)/gpu/mali700/common/texture/inc \
            -I$(SAMPLE_DIR)/gpu/mali700/common/platform 
DEP_LIBS += $(HI_LIBS) -lmali -lm
endif



LIBPATH += -L$(SHARED_LIB_DIR)

ifdef CFG_HI_STATIC_LIB_ONLY
LIBPATH += -L$(STATIC_LIB_DIR)
endif

LIB = -Wl,--start-group $(SYS_LIBS) $(DEP_LIBS) -Wl,--end-group

CXX = ${CFG_HI_TOOLCHAINS_NAME}-c++
ifeq ($(CFG_HI_EGL_TYPE), fb)
CC+= -DHI3D_DEBUG -DLINUX -DEGL_API_FB -DEGL_FBDEV
CXX+= -DHI3D_DEBUG -DLINUX -DEGL_API_FB -DEGL_FBDEV
endif


CFG_INC = $(CFLAGS)

export  LIB LIBPATH CFG_INC COMMON_FILES CXX CC
all:
ifeq ($(CFG_HI_GPU), y)

ifeq ($(CFG_HI_GPU_MALI400_SUPPORT), y)
	@$(AT)make -C mali400/es11/coverflow
	@$(AT)make -C mali400/es11/coverflow_vertical
	@$(AT)make -C mali400/es11/cylinder
	@$(AT)mkdir -p ./exe/es11
	@$(AT)mkdir -p ./exe/es11/coverflow_res
	@$(AT)mkdir -p ./exe/es11/cylinder_res
	@$(AT)mv mali400/es11/coverflow/coverflow ./exe/es11
	@$(AT)cp mali400/es11/coverflow/coverflow_res/* ./exe/es11/coverflow_res -rf
	@$(AT)mv mali400/es11/coverflow_vertical/coverflow_vertical ./exe/es11
	@$(AT)mv mali400/es11/cylinder/cylinder ./exe/es11
	@$(AT)cp mali400/es11/cylinder/cylinder_res/* ./exe/es11/cylinder_res -rf
endif
ifeq ($(CFG_HI_GPU_MALI450_SUPPORT), y)
	@$(AT)make -C mali400/es11/coverflow
	@$(AT)make -C mali400/es11/coverflow_vertical
	@$(AT)make -C mali400/es11/cylinder
	@$(AT)mkdir -p ./exe/es11
	@$(AT)mkdir -p ./exe/es11/coverflow_res
	@$(AT)mkdir -p ./exe/es11/cylinder_res
	@$(AT)mv mali400/es11/coverflow/coverflow ./exe/es11
	@$(AT)cp mali400/es11/coverflow/coverflow_res/* ./exe/es11/coverflow_res -rf
	@$(AT)mv mali400/es11/coverflow_vertical/coverflow_vertical ./exe/es11
	@$(AT)mv mali400/es11/cylinder/cylinder ./exe/es11
	@$(AT)cp mali400/es11/cylinder/cylinder_res/* ./exe/es11/cylinder_res -rf
endif
ifeq ($(CFG_HI_GPU_MALI700_SUPPORT), y)	
	@$(AT)make -C mali700/es11/tutorial
	@$(AT)make -C mali700/es11/texture
#	@$(AT)make -C mali700/es20/Hello_Triangle
	@$(AT)make -C mali700/es20/sphere
	@$(AT)mkdir -p ./exe/es11
	@$(AT)mkdir -p ./exe/es20	
	@$(AT)mkdir -p ./exe/es20/sphere_res
	@$(AT)mv mali700/es11/tutorial/tutorial ./exe/es11/
	@$(AT)mv mali700/es11/texture/texture ./exe/es11/
#	@$(AT)mv mali700/es20/Hello_Triangle/Hello_Triangle ./exe/es20/
	@$(AT)mv mali700/es20/sphere/sphere ./exe/es20/
	@$(AT)cp mali700/es20/sphere/sphere_res/* ./exe/es20/sphere_res
endif

	$(AT)find . -name "*.o" | xargs rm -rf
	$(AT)find . -name "Thumbs.db" | xargs rm -rf
endif

clean:
ifeq ($(CFG_HI_GPU), y)

ifeq ($(CFG_HI_GPU_MALI400_SUPPORT), y)
	@$(AT)make -C mali400/es11/coverflow clean
	@$(AT)make -C mali400/es11/coverflow_vertical clean
	@$(AT)make -C mali400/es11/cylinder clean
endif
ifeq ($(CFG_HI_GPU_MALI450_SUPPORT), y)
	@$(AT)make -C mali400/es11/coverflow clean
	@$(AT)make -C mali400/es11/coverflow_vertical clean
	@$(AT)make -C mali400/es11/cylinder clean
endif
ifeq ($(CFG_HI_GPU_MALI700_SUPPORT), y)	
	@$(AT)make -C mali700/es11/tutorial clean
	@$(AT)make -C mali700/es11/texture clean
	@$(AT)make -C mali700/es20/Hello_Triangle clean
	@$(AT)make -C mali700/es20/sphere clean
endif

	$(AT)rm ./exe -rf
endif

install:

uninstall:

