SRCS := \
    lib/chunk-info.cpp \
    lib/chunk.cpp \
    lib/container-chunk.cpp \
    lib/content-codes.cpp \
    lib/integer-chunk.cpp \
    lib/string-chunk.cpp \
    lib/version-chunk.cpp \
    lib/cxa_bad_cast.cpp

OBJS := $(SRCS:.cpp=.o)

CROSS_COMPILE := arm-hisiv200-linux-
CC := $(CROSS_COMPILE)g++
AR := $(CROSS_COMPILE)ar
CFLAGS := -fPIC -frtti

LIB: $(OBJS)
	$(AR) -r $(LIB) $^

LIB := libdaap.a
ALL: $(LIB) $(OBJS)


$(OBJS):%.o:%.cpp
	$(CC) $(CFLAGS) -Iinclude -o $@ -c $<

.PHONY: clean
clean: $(OBJS) $(LIB)
	rm -rf $^
