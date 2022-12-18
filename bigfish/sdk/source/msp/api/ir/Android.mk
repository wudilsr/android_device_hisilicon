IR_DIR := ir

ifeq ($(CFG_HI_IR_TYPE_STD), y)
LOCAL_SRC_FILES += $(IR_DIR)/unf_ir_std.c
endif

ifeq ($(CFG_HI_IR_TYPE_S2), y)
LOCAL_SRC_FILES += $(IR_DIR)/unf_ir.c
endif

ifeq ($(CFG_HI_IR_TYPE_LIRC), y)
LOCAL_SRC_FILES += $(IR_DIR)/unf_ir_lirc.c
endif
