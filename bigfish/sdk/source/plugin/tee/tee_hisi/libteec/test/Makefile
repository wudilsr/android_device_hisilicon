#by fangjian00208632 2015-03-13


###########################################################
# platform definition
###########################################################
MAKE      =make
AR        =$(CROSS_COMPILE)ar
LD        =$(CROSS_COMPILE)ld
CC        =$(CROSS_COMPILE)gcc
CPP       =$(CROSS_COMPILE)g++
RM        =rm -f
COPY      =cp
ROOT      =$(shell pwd)

LDPATH    =$(ROOT)/../bin
OUT       =$(ROOT)/../bin
CFLAGS    = -static -I$(ROOT)/../inc \
            -I$(ROOT)/../sec_mmz/inc \
            -I$(ROOT)/../../trustedcore/include/HS_API

LDFLAGS   = -L$(LDPATH) -lteec

ALL_EXE += \
		tee_test_invoke \
		tee_test_login \
		tee_test_loginread \
		tee_test_loginwrite1 \
		tee_test_loginwrite \
		tee_test_mem \
		tee_test_random \
		tee_test_sess \
		tee_test_storage \
		tee_test_time \
		tee_test_ut \
		test_hello \
		sec_mmz_dbg \
		test_cipher \
		internal_test_client

ALL_EXE_TARGET = $(foreach VAR,$(ALL_EXE),$(addprefix $(OUT)/,$(VAR)))

.PHONY : all clean

all:$(ALL_EXE_TARGET)
	@echo "$(ALL_EXE)"
	@echo "Make Successfull!"

install: all
	$(COPY) $(ALL_EXE_TARGET) $(BIN_DIR)

uninstall:
	$(RM) $(addprefix $(BIN_DIR)/, $(ALL_EXE))

$(ALL_EXE_TARGET) : $(OUT)/% : $(ROOT)/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	$(RM) $(addprefix $(OUT)/, $(ALL_EXE))
	@echo "clean Successfull!"
