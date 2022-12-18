SRCS := \
	mDNSCore/DNSCommon.c \
	mDNSCore/DNSDigest.c \
	mDNSCore/mDNS.c \
	mDNSCore/uDNS.c \
	mDNSHisi/hisidns.c \
	mDNSPosix/mDNSPosix.c \
	mDNSPosix/mDNSUNP.c \
	mDNSShared/GenLinkedList.c \
	mDNSShared/PlatformCommon.c \
	mDNSShared/mDNSDebug.c

OBJS := $(SRCS:.c=.o)

CROSS_COMPILE := arm-hisiv200-linux-
CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar
CFLAGS := -D_GNU_SOURCE -DNOT_HAVE_SA_LEN -DUSES_NETLINK -DHAVE_LINUX -DTARGET_OS_LINUX -fno-strict-aliasing -DMDNS_DEBUGMSGS=0 -DMDNS_ONLYSYSTEMTASK=1 -O0 -UNDEBUG -fPIC

LIB: $(OBJS)
	$(AR) -r $(LIB) $^

LIB := libbonjour.a
ALL: $(LIB) $(OBJS)


$(OBJS):%.o:%.c
	$(CC) $(CFLAGS) -ImDNSCore -ImDNSShared -ImDNSHisi -ImDNSPosix -o $@ -c $<

.PHONY: clean
clean: $(OBJS) $(LIB)
	rm -rf $^
