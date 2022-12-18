LIB_FILE := $(PLAYER_LIB_DIR)/libhiplayer_utils.a
SO_LIB_FILE := $(PLAYER_LIB_DIR)/libhiplayer_utils.so

CFLAGS += -fPIC

COMMONOBJS +=$(patsubst %.c,%.o,$(wildcard *.c))
COMMONOBJS :=$(filter-out svr_log_android.%,$(COMMONOBJS))
COMMONOBJS :=$(filter-out svr_sys_android.%,$(COMMONOBJS))

all: commonobj install

commonobj: $(COMMONOBJS)
install: commonobj
	$(AR) -r $(LIB_FILE) $(COMMONOBJS)
	$(CC) $(CFLAGS) -shared -o $(SO_LIB_FILE) $(COMMONOBJS)
clean:
	find . -type f \
		\( -name '*.bak' \
		-o -name '*.o'  \) -print \
		| xargs rm -f
