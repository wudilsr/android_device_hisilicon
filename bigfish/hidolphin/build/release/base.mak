#=============HI_SDK_DIR=================================================================
HI_SDK_DIR=${CFG_SDK_PATH}/pub

ifeq (${CFG_CHIP_TYPE},hi3716c)
SDK_INCLUDE=${HI_SDK_DIR}/include
SDK_LIB=${HI_SDK_DIR}/lib
CFG_HI_CFLAGS += -DDISEQC_SUPPORT
ifeq ($(CFG_TOOLCHAINS_NAME), gcc-4.4.1-vfp_glibc)
CFG_HI_TOOLCHAINS_NAME = arm-hisiv200-linux
CFG_HI_CHIP_TYPE = hi3716
export CFG_HI_TOOLCHAINS_NAME CFG_HI_CHIP_TYPE
endif

endif

ifeq (${CFG_HI_CHIP_TYPE},hi3712)
SDK_INCLUDE=${HI_SDK_DIR}/include
SDK_EXTERN_LIB=${HI_SDK_DIR}/lib/extern
SDK_STATIC_LIB=${HI_SDK_DIR}/lib/static
SDK_SHARE_LIB=${HI_SDK_DIR}/lib/share
SDK_LIB+=-L${SDK_EXTERN_LIB}
SDK_LIB+=-L${SDK_STATIC_LIB}
SDK_LIB+=-L${SDK_SHARE_LIB}
endif

#=============TOOL CHAINS==================================================================
AR=${CFG_HI_TOOLCHAINS_NAME}-ar
AS=${CFG_HI_TOOLCHAINS_NAME}-as
LD=${CFG_HI_TOOLCHAINS_NAME}-ld
CPP=${CFG_HI_TOOLCHAINS_NAME}-cpp
CC=${CFG_HI_TOOLCHAINS_NAME}-gcc
CXX=${CFG_HI_TOOLCHAINS_NAME}-g++
NM=${CFG_HI_TOOLCHAINS_NAME}-nm
STRIP=${CFG_HI_TOOLCHAINS_NAME}-strip
OBJCOPY=${CFG_HI_TOOLCHAINS_NAME}-objcopy
OBJDUMP=${CFG_HI_TOOLCHAINS_NAME}-objdump

export HI_SDK_DIR AR AS LD CPP CC NM STRIP OBJCOPY OBJDUMP CXX

#==============LIB COMPILE OPTIONS=========================================================
ifeq (${CFG_HI_TOOLCHAINS_NAME},arm-hismall-linux)
    CFG_HI_CFLAGS+=-march=armv5te -mtune=arm926ej-s
endif
ifeq (${CFG_HI_TOOLCHAINS_NAME},arm-hisiv110-linux)
    CFG_HI_CFLAGS+=-march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16
endif
ifeq (${CFG_HI_TOOLCHAINS_NAME},arm-hisiv200-linux)
    CFG_HI_CFLAGS+=-march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16
endif

CFG_HI_CFLAGS+=-I/$(SDK_INCLUDE)
CFG_HI_CXXFLAGS := -I/$(SDK_INCLUDE)
CFG_HI_CFLAGS+=$(CFG_HI_BOARD_CONFIGS)
CFG_HI_CXXFLAGS+=$(CFG_HI_BOARD_CONFIGS)
CFG_HI_CFLAGS+= -I${MSP_UNF_INCLUDE} -I${MSP_API_INCLUDE} -I${MSP_DRV_INCLUDE} -I${COMMON_UNF_INCLUDE} -I${COMMON_API_INCLUDE} -I${COMMON_DRV_INCLUDE}
export CFG_HI_CFLAGS SDK_LIB SDK_INCLUDE CFG_HI_CXXFLAGS
