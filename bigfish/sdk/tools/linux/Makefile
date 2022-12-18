#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#TOOL_OBJS := toolchains  utils   kconfig 
TOOL_OBJS := utils  kconfig
#----------------------------------------------
ifneq ($(obj),)
CUR_OBJS=$(obj)
else
CUR_OBJS=$(TOOL_OBJS)  
endif
#----------------------------------------------
PHONY := all clean install uninstall
all: 
	@$(if $(CUR_OBJS), \
		$(foreach  tmp, $(CUR_OBJS), \
			printf "Creating %s ...\\n"  $(tmp); \
			make -C $(tmp); ) \
		)	

clean:
	@$(if $(CUR_OBJS), \
		$(foreach  tmp, $(CUR_OBJS), \
			printf "Cleaning %s ...\\n"  $(tmp); \
			make -C $(tmp) clean; ) \
		)	
install:
	@$(if $(CUR_OBJS), \
		$(foreach  tmp, $(CUR_OBJS), \
			printf "Installing %s ...\\n"  $(tmp); \
			make -C $(tmp) install; ) \
		)	
uninstall:
	@$(if $(CUR_OBJS), \
		$(foreach  tmp, $(CUR_OBJS), \
			printf "Uninstalling %s ...\\n"  $(tmp); \
			make -C $(tmp) uninstall; ) \
		)	
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
