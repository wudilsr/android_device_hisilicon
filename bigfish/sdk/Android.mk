LOCAL_PATH := $(call my-dir)

ifeq ($(strip $(BUILDIN_HISI_EXT)),true)

driver_modules :=         \
	source/common/api \
	source/msp/api    \
	source/rootfs     \
	tools/windows     \
	source/component  \
	pub/image         \
	prebuilts         \
	sample

include $(call all-named-subdir-makefiles,$(driver_modules))

endif # BUILDIN_HISI_EXT
