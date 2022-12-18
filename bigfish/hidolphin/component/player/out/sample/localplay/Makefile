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
            -I$(SAMPLE_DIR)/common

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)

#CFG_HI_KEYLED_SUPPORT
export CHARSET_SUPPORT = 1
ifndef CFG_HI_ADVCA_FUNCTION
export DRM_SUPPORT = 1
endif

ifdef CHARSET_SUPPORT
CFLAGS += -DCHARSET_SUPPORT
endif

ifdef DRM_SUPPORT
CFLAGS += -DDRM_SUPPORT
DRM_FILES   = localplay_drm.c
PLAYER_LIBS = -lHiDrmEngine
endif

LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) $(PLAYER_LIBS) -Wl,--end-group

LIB_FILE := ./libprivateprotocol.so
IMG_FILE = sample_localplay

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(IMG_FILE) $(LIB_FILE)

all: $(IMG_FILE)
$(IMG_FILE): sample_localplay.c play_m3u9.c $(DRM_FILES) $(COMMON_FILES)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBPATH) $(LIB)

$(LIB_FILE): test_protocol.c
	@$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

clean:
	-@rm -f $(IMG_FILE)
	-@rm -f $(LIB_FILE)

