HIDOLPHIN_DIR := ../..
SRCS1 := \
    src/Array.cpp \
    src/Boolean.cpp \
    src/Data.cpp \
    src/Date.cpp \
    src/Dictionary.cpp \
    src/Integer.cpp \
    src/Node.cpp \
    src/Real.cpp \
    src/String.cpp \
    src/Structure.cpp

SRCS2 := \
    src/base64.c \
    src/bplist.c \
    src/bytearray.c \
    src/hashtable.c \
    src/plist.c \
    src/ptrarray.c \
    src/xplist.c \
    libcnary/list.c \
    libcnary/node.c \
    libcnary/node_list.c \
    libcnary/node_iterator.c \
    plutil/plutil.c

OBJS1 := $(SRCS1:.cpp=.o)
OBJS2 := $(SRCS2:.c=.o)

CROSS_COMPILE := arm-hisiv200-linux-
CCPP := $(CROSS_COMPILE)g++
CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar

CFLAGS := -U__VFP_FP__ -fPIC

LIB := libplist.a
ALL: $(LIB)

$(LIB): $(OBJS1) $(OBJS2)
	$(AR) -r $(LIB) $^

.cpp.o:
	$(CCPP) $(CFLAGS) -Iinclude -o $@ -c $<

.c.o:
	$(CC) $(CFLAGS) -Iinclude -Ilibcnary/include -I$(HIDOLPHIN_DIR)/external/libxml2/include -o $@ -c $<

.PHONY: clean
clean: $(OBJS1) $(OBJS2) $(LIB)
	rm -rf $^
