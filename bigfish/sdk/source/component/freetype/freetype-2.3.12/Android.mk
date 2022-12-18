# this is now the default FreeType build for Android
#
LOCAL_PATH:= $(call my-dir)

#===============static lib
include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_MODULE := libfreetype
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

#LOCAL_MODULE_TAGS := optional
#LOCAL_CFLAGS := $(CFG_HI_CFLAGS)
#LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES:= \
	src/base/ftbbox.c \
	src/base/ftbitmap.c \
	src/base/ftfstype.c \
	src/base/ftglyph.c \
	src/base/ftlcdfil.c \
	src/base/ftstroke.c \
	src/base/fttype1.c \
	src/base/ftxf86.c \
	src/base/ftbase.c \
	src/base/ftsystem.c \
	src/base/ftinit.c \
	src/base/ftgasp.c \
	src/raster/raster.c \
	src/sfnt/sfnt.c \
	src/smooth/smooth.c \
	src/autofit/autofit.c \
	src/truetype/truetype.c \
	src/cff/cff.c \
	src/psnames/psnames.c \
	src/pshinter/pshinter.c \
	src/gzip/ftgzip.c \
    src/cache/ftcache.c \
    src/pcf/pcf.c \
    src/pfr/pfr.c \
    src/bdf/bdf.c \
    src/type1/type1.c \
    src/type42/type42.c \
    src/winfonts/winfnt.c \
    src/cid/type1cid.c \
    src/lzw/ftlzw.c \
    src/psaux/psaux.c 
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/cache))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/pcf))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/pfr))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/bdf))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/type1))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/type42))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/winfonts))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/lzw))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/gzip))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/cid))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/psaux))

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/builds \
	$(LOCAL_PATH)/include

LOCAL_CFLAGS += -W -Wall
LOCAL_CFLAGS += -fPIC -DPIC
LOCAL_CFLAGS += "-DDARWIN_NO_CARBON"
LOCAL_CFLAGS += "-DFT2_BUILD_LIBRARY"

# the following is for testing only, and should not be used in final builds
# of the product
#LOCAL_CFLAGS += "-DTT_CONFIG_OPTION_BYTECODE_INTERPRETER"

LOCAL_CFLAGS += -O2

include $(BUILD_STATIC_LIBRARY)

#============share lib
include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_MODULE := libfreetype
#ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

#LOCAL_MODULE_TAGS := optional
#LOCAL_CFLAGS := $(CFG_HI_CFLAGS)
#LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES:= \
        src/base/ftbbox.c \
        src/base/ftbitmap.c \
        src/base/ftfstype.c \
        src/base/ftglyph.c \
        src/base/ftlcdfil.c \
        src/base/ftstroke.c \
        src/base/fttype1.c \
        src/base/ftxf86.c \
        src/base/ftbase.c \
        src/base/ftsystem.c \
        src/base/ftinit.c \
        src/base/ftgasp.c \
        src/raster/raster.c \
        src/sfnt/sfnt.c \
        src/smooth/smooth.c \
        src/autofit/autofit.c \
        src/truetype/truetype.c \
        src/cff/cff.c \
        src/psnames/psnames.c \
        src/pshinter/pshinter.c \
        src/gzip/ftgzip.c \
    src/cache/ftcache.c \
    src/pcf/pcf.c \
    src/pfr/pfr.c \
    src/bdf/bdf.c \
    src/type1/type1.c \
    src/type42/type42.c \
    src/winfonts/winfnt.c \
    src/cid/type1cid.c \
    src/lzw/ftlzw.c \
    src/psaux/psaux.c
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/cache))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/pcf))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/pfr))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/bdf))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/type1))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/type42))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/winfonts))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/lzw))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/gzip))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/cid))
#LOCAL_SRC_FILES += $(sort $(call all-c-files-under, src/psaux))

LOCAL_C_INCLUDES += \
        $(LOCAL_PATH)/builds \
        $(LOCAL_PATH)/include

LOCAL_CFLAGS += -W -Wall
LOCAL_CFLAGS += -fPIC -DPIC
LOCAL_CFLAGS += "-DDARWIN_NO_CARBON"
LOCAL_CFLAGS += "-DFT2_BUILD_LIBRARY"

LOCAL_CFLAGS += -O2

include $(BUILD_SHARED_LIBRARY)

