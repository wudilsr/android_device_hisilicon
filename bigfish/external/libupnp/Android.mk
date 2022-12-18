#Chip:
#Env:UPNP
#y00163442

LOCAL_PATH:= $(call my-dir)

#****************************************************************
# module1:threadutil
#****************************************************************
include $(CLEAR_VARS)

OPTFLAGS= -I.. -W -Wall  -D_REENTRANT -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -O3 -D__ANDRIOD_LINUX

LOCAL_CFLAGS :=  $(OPTFLAGS)
#***** if advance CA the open this option (BEGIN)******
#LOCAL_CFLAGS += -DHI_ADVCA_FUNCTION_RELEASE
#***** if advance CA the open this option (END)******
LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := \
                threadutil/src/FreeList.c \
                threadutil/src/LinkedList.c \
                threadutil/src/ThreadPool.c \
                threadutil/src/TimerThread.c \
                upnp/src/api/upnpdebug.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/threadutil/inc \
                    $(LOCAL_PATH)/upnp/inc \
                    $(LOCAL_PATH)/ixml/inc \
                    $(LOCAL_PATH)/ixml/src/inc \
                    $(LOCAL_PATH)/upnp/src/inc
LOCAL_SHARED_LIBRARIES := libutils libcutils

LOCAL_MODULE := libthreadutil
ifeq "4.4" "$(findstring 4.4,$(PLATFORM_VERSION))"
    ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_32_BIT_ONLY := true
LOCAL_PRELINK_MODULE := false
#LOCAL_NO_DEFAULT_COMPILER_FLAGS := true

LOCAL_COPY_HEADERS_TO := upnp
LOCAL_COPY_HEADERS :=     threadutil/inc/FreeList.h \
                        threadutil/inc/ithread.h \
                        threadutil/inc/LinkedList.h \
                        threadutil/inc/TimerThread.h \
                        threadutil/inc/ThreadPool.h

#ifeq ($(BUILD_DLNA_VPP),true)
include $(BUILD_SHARED_LIBRARY)
#endif

#****************************************************************
# module2:ixml
#****************************************************************
include $(CLEAR_VARS)

OPTFLAGS= -I.. -W -Wall  -D_REENTRANT -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -O3 -D__ANDRIOD_LINUX

LOCAL_CFLAGS :=  $(OPTFLAGS)
#***** if advance CA the open this option (BEGIN)******
#LOCAL_CFLAGS += -DHI_ADVCA_FUNCTION_RELEASE
#***** if advance CA the open this option (END)******
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := \
            ixml/src/ixml.c \
            ixml/src/node.c \
            ixml/src/ixmlparser.c \
            ixml/src/ixmlmembuf.c \
            ixml/src/nodeList.c \
            ixml/src/element.c \
            ixml/src/attr.c \
            ixml/src/document.c \
            ixml/src/namedNodeMap.c \
            ixml/src/ixmldebug.c\
            ixml/src/inc/ixmlmembuf.h \
            ixml/src/inc/ixmlparser.h

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ixml/inc \
                    $(LOCAL_PATH)/ixml/src/inc    \
                    $(LOCAL_PATH)/upnp/inc

LOCAL_SHARED_LIBRARIES := libutils
LOCAL_MODULE := libixml
ifeq "4.4" "$(findstring 4.4,$(PLATFORM_VERSION))"
    ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_32_BIT_ONLY := true
LOCAL_PRELINK_MODULE := false
#LOCAL_NO_DEFAULT_COMPILER_FLAGS := true

LOCAL_COPY_HEADERS_TO := upnp
LOCAL_COPY_HEADERS := ixml/inc/ixml.h

#ifeq ($(BUILD_DLNA_VPP),true)
include $(BUILD_SHARED_LIBRARY)
#endif

#****************************************************************
# module3:upnp
#****************************************************************
include $(CLEAR_VARS)

OPTFLAGS= -I.. -W -Wall  -D_REENTRANT -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -O3 -D__ANDRIOD_LINUX

LOCAL_CFLAGS :=  $(OPTFLAGS)

#***** if advance CA the open this option (BEGIN)******
#LOCAL_CFLAGS += -DHI_ADVCA_FUNCTION_RELEASE
#***** if advance CA the open this option (END)******
LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES := $(LOCAL_PATH)/upnp/inc \
                    $(LOCAL_PATH)/upnp/src/inc \
                    $(LOCAL_PATH)/ixml/inc \
                    $(LOCAL_PATH)/threadutil/inc \
                    $(LOCAL_PATH)/


libupnp_la_SOURCES = \
    upnp/src/inc/config.h \
    upnp/src/inc/client_table.h \
    upnp/src/inc/gena.h \
    upnp/src/inc/gena_ctrlpt.h \
    upnp/src/inc/gena_device.h \
    upnp/src/inc/global.h \
    upnp/src/inc/gmtdate.h \
    upnp/src/inc/inet_pton.h \
    upnp/src/inc/httpparser.h \
    upnp/src/inc/httpreadwrite.h \
    upnp/src/inc/md5.h \
    upnp/src/inc/membuffer.h \
    upnp/src/inc/miniserver.h \
    upnp/src/inc/netall.h \
    upnp/src/inc/parsetools.h \
    upnp/src/inc/server.h \
    upnp/src/inc/service_table.h \
    upnp/src/inc/soaplib.h \
    upnp/src/inc/sock.h \
    upnp/src/inc/statcodes.h \
    upnp/src/inc/statuscodes.h \
    upnp/src/inc/strintmap.h \
    upnp/src/inc/ssdplib.h \
    upnp/src/inc/sysdep.h \
    upnp/src/inc/unixutil.h \
    upnp/src/inc/upnp_timeout.h \
    upnp/src/inc/upnpapi.h \
    upnp/src/inc/upnputil.h \
    upnp/src/inc/uri.h \
    upnp/src/inc/urlconfig.h \
    upnp/src/inc/VirtualDir.h \
    upnp/src/inc/uuid.h \
    upnp/src/inc/webserver.h \
    upnp/inc/UpnpString.h \
    upnp/inc/ifc_utils.h

# ssdp
libupnp_la_SOURCES += \
    upnp/src/ssdp/ssdp_device.c \
    upnp/src/ssdp/ssdp_ctrlpt.c \
    upnp/src/ssdp/ssdp_server.c

# soap
libupnp_la_SOURCES += \
    upnp/src/soap/soap_device.c \
    upnp/src/soap/soap_ctrlpt.c \
    upnp/src/soap/soap_common.c

# genlib
libupnp_la_SOURCES += \
    upnp/src/genlib/miniserver/miniserver.c \
    upnp/src/genlib/service_table/service_table.c \
    upnp/src/genlib/util/membuffer.c \
    upnp/src/genlib/util/strintmap.c \
    upnp/src/genlib/util/upnp_timeout.c \
    upnp/src/genlib/util/util.c \
    upnp/src/genlib/client_table/client_table.c \
    upnp/src/genlib/net/sock.c \
    upnp/src/genlib/net/http/httpparser.c \
    upnp/src/genlib/net/http/httpreadwrite.c \
    upnp/src/genlib/net/http/statcodes.c \
    upnp/src/genlib/net/http/webserver.c \
    upnp/src/genlib/net/http/parsetools.c \
    upnp/src/genlib/net/uri/uri.c

# gena
libupnp_la_SOURCES += \
    upnp/src/gena/gena_device.c \
    upnp/src/gena/gena_ctrlpt.c \
    upnp/src/gena/gena_callback2.c

# api
libupnp_la_SOURCES += upnp/src/api/upnpapi.c
libupnp_la_SOURCES += upnp/src/api/upnptools.c
libupnp_la_SOURCES += upnp/src/api/upnpdebug.c
libupnp_la_SOURCES += upnp/src/api/UpnpString.c

# uuid
libupnp_la_SOURCES += \
    upnp/src/uuid/md5.c \
    upnp/src/uuid/sysdep.c \
    upnp/src/uuid/uuid.c


# urlconfig
libupnp_la_SOURCES += upnp/src/urlconfig/urlconfig.c

LOCAL_SHARED_LIBRARIES := libixml libthreadutil libutils libcutils libnetutils


LOCAL_SRC_FILES := $(libupnp_la_SOURCES)

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libupnp
ifeq "4.4" "$(findstring 4.4,$(PLATFORM_VERSION))"
    ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_32_BIT_ONLY := true
LOCAL_COPY_HEADERS_TO := upnp
LOCAL_COPY_HEADERS := \
    upnp/inc/upnp.h \
    upnp/inc/upnpdebug.h \
    upnp/inc/upnpconfig.h \
     upnp/inc/upnptools.h
#ifeq ($(BUILD_DLNA_VPP),true)
include $(BUILD_SHARED_LIBRARY)
#endif
