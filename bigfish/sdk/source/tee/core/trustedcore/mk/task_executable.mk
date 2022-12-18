LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_SUFFIX :=
LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_CFLAGS += -fno-omit-frame-pointer
#LOCAL_CFLAGS += -fstack-protector --param ssp-buffer-size=4 -Wstack-protector
LOCAL_CFLAGS += -fstack-protector-all -Wstack-protector
ifeq ($(strip $(LPAE_SUPPORT)), 1)
    TRUSTEDCORE_LOCAL_CFLAGS += -DARM_PAE
    TRUSTEDCORE_LOCAL_ASFLAGS += -DARM_PAE
endif

#modify by l00202565
TA_CC := arm-eabi-gcc
TA_LD := arm-eabi-ld
TA_OBJCOPY := arm-eabi-objcopy
LOCAL_CC := $(TA_CC)

include $(BUILD_SYSTEM)/binary.mk

$(LOCAL_BUILT_MODULE) : PRIVATE_ELF_FILE := $(intermediates)/$(PRIVATE_MODULE).elf
$(LOCAL_BUILT_MODULE) : PRIVATE_LIBS := `$(TA_CC) -mthumb-interwork -print-libgcc-file-name`
ifneq ($(strip $(TARGET_GCC_VERSION)),)
ifeq ($(filter 4.6 4.6.%, $(TARGET_GCC_VERSION)),)
LOCAL_CFLAGS += -mno-unaligned-access
endif
endif
$(all_objects) : PRIVATE_TARGET_PROJECT_INCLUDES :=
$(all_objects) : PRIVATE_TARGET_C_INCLUDES :=
$(all_objects) : PRIVATE_TARGET_GLOBAL_CFLAGS :=
$(all_objects) : PRIVATE_TARGET_GLOBAL_CPPFLAGS :=

$(LOCAL_BUILT_MODULE): $(all_objects) $(all_libraries)
	@$(mkdir -p $(dir $@)
	@echo "target Linking: $(PRIVATE_MODULE)"
	$(hide) $(TA_LD) \
		$(addprefix --script ,$(PRIVATE_LINK_SCRIPT)) \
		$(PRIVATE_RAW_EXECUTABLE_LDFLAGS) \
		-T $(TA_LINK_SCRIPT) \
		-o $(PRIVATE_ELF_FILE) \
		$(PRIVATE_ALL_OBJECTS) \
		--start-group $(PRIVATE_ALL_STATIC_LIBRARIES) --end-group \
		$(PRIVATE_LIBS)
	$(hide) $(TA_OBJCOPY) -O binary $(PRIVATE_ELF_FILE) $@
