OBJ_DIR := $(CURDIR)
COMMON_OBJ_DIR := $(SAMPLE_DIR)/common

vpath %.c $(SAMPLE_DIR)/common

HI_SAMPLE_IMAGES := $(addprefix $(OBJ_DIR)/,$(SAMPLE_IMAGES))
HI_COMMON_OBJS := $(addprefix $(COMMON_OBJ_DIR)/,$(COMMON_OBJS))

FLOAT_OPTIONS := -mfloat-abi=softfp -mfpu=vfpv3-d16

CFLAGS  +=  $(CFG_HI_SAMPLE_CFLAGS)

CFLAGS  += -I$(HI_INCLUDE_DIR) -I$(SAMPLE_DIR)/common

HI_LIB_PATHS :=  -L$(STATIC_LIB_DIR)  -L$(EXTERN_LIB_DIR) -L$(SHARED_LIB_DIR) $(LIB_PATHS)

HI_DEPEND_LIBS := -Wl,--start-group $(SYS_LIBS) $(DEPEND_LIBS) -Wl,--end-group

TARGETS := $(if $(HI_SAMPLE_IMAGES),$(HI_SAMPLE_IMAGES),$(HI_COMMON_OBJS))

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean prepare

all: $(TARGETS)

clean:

$(HI_SAMPLE_IMAGES) : % : $(HI_COMMON_OBJS) $(addprefix $(OBJ_DIR)/,$(LOCAL_OBJS)) %.o
	$(AT)$(CFG_HI_TOOLCHAINS_NAME)-gcc -o $@ $^ $(HI_LIB_PATHS) $(HI_DEPEND_LIBS)

$(COMMON_OBJ_DIR)/%.o : $(COMMON_OBJ_DIR)/%.c
	$(AT)$(CFG_HI_TOOLCHAINS_NAME)-gcc $(CFLAGS) $(FLOAT_OPTIONS) -o $@ -c $^

$(OBJ_DIR)/%.o : %.c
	$(AT)$(CFG_HI_TOOLCHAINS_NAME)-gcc $(CFLAGS) $(FLOAT_OPTIONS) -o $@ -c $^
