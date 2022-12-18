# armeabi/armeabi-v7a

_ABI ?= $(ABI)
ABI := $(strip $(_ABI))
_FPU ?= $(FPU)
FPU := $(strip $(_FPU))
_TUNE ?= $(TUNE)
TUNE := $(strip $(_TUNE))
##for emulator
BUILD_FOR_EMULATOR := 0
BUILD_FOR_XOOM := 0
BUILD_FOR_A9 := 1
ifeq ($(BUILD_FOR_EMULATOR),1)
else
ifeq ($(BUILD_FOR_XOOM),1)
ifeq ($(ABI),)
    ABI := armeabi-v7a
endif
ifeq ($(FPU),)
    FPU := vfp
endif
ifeq ($(TUNE),)
    TUNE := cortex-a9
endif
else
ifeq ($(ABI),)
    ABI := armeabi-v7a
endif
ifeq ($(FPU),)
    FPU := neon
endif
ifeq ($(TUNE),)
ifeq ($(BUILD_FOR_A9),1)
TUNE := cortex-a9
else
    TUNE := cortex-a8
endif
endif
endif
APP_ABI := $(ABI)

ifeq ($(NDK_DEBUG),1)
APP_OPTIM := debug
OPT_CFLAGS :=
else
APP_OPTIM := release
ifeq ($(BUILD_FOR_XOOM),1)
OPT_CFLAGS := -O3
else
OPT_CFLAGS := -O3 -mlong-calls -fstrict-aliasing -fprefetch-loop-arrays -ffast-math
endif
endif

ifeq ($(APP_ABI),armeabi-v7a)
    ifeq ($(FPU),neon)
        OPT_CFLAGS += -DHAVE_NEON=1 -mfpu=neon -mtune=$(TUNE) -ftree-vectorize -mvectorize-with-neon-quad
        BUILD_WITH_NEON := 1
    else
        OPT_CFLAGS += -mfpu=$(FPU) -mtune=$(TUNE) -mfloat-abi=softfp -DHAVE_NEON=1
        BUILD_WITH_NEON := 1
    endif
else
    OPT_CFLAGS += -march=armv6j -mtune=arm1136j-s -msoft-float
    BUILD_WITH_NEON := 0
endif
endif
OPT_CPPFLAGS := $(OPT_CLFAGS)

APP_CFLAGS := $(APP_CFLAGS) $(OPT_CFLAGS)
APP_CPPFLAGS := $(APP_CPPFLAGS) $(OPT_CPPFLAGS)
APP_PLATFORM := android-14