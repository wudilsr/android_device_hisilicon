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
CFLAGS += -I$(SDK_INC_DIR)		\
	  -I$(SAMPLE_DIR)/common

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

image = sample_cipher sample_rng sample_multicipher sample_hash sample_cbcmac sample_anticopy sample_rsa_enc sample_rsa_sign
#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:$(image)

sample_cipher: sample_cipher.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_rng: sample_rng.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_multicipher: sample_multicipher.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_hash: sample_hash.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)
	
sample_cbcmac: sample_cbcmac.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_anticopy: sample_anticopy.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_rsa_enc: sample_rsa_enc.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_rsa_sign: sample_rsa_sign.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)
	
clean:
	-@rm -f $(image)

install:

uninstall:

