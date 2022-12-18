SRC = $(wildcard *.cpp)
OTHERSRC=$(COMMON_FILES)
OTHERSRC += ../../common/egl/src/hi_egl.c         \
            ../../common/egl/src/egl_native.c   \
            ../../common/texture/src/hi_texture.c \
            ../../common/key/src/hi_engine_key.c  \
	    ../../common/key/src/hi_input_dfb.c   \
	    ../../common/key/src/hi_ir_remote.c

LOCALLIB=-lEGL -lGLESv2
APP=sphere
all:$(APP)


OBJ=$(patsubst %.cpp,%.o,$(SRC))
$(OBJ): %.o: %.cpp 
	$(CXX) -c  $^ -o $@ $(CFG_INC) $(LIBPATH) $(LIB) $(LOCALLIB)

OBJ2=$(patsubst %.c,%.o,$(OTHERSRC))
	
$(OBJ2): %.o: %.c 
	$(CC) -c $^ -o $@ $(CFG_INC) $(LIBPATH) $(LIB) $(LOCALLIB)

$(APP):$(OBJ2) $(OBJ) 
	$(CXX) -o $@ $^ $(CFG_INC) $(LIBPATH) $(LIB) $(LOCALLIB)


clean:
	-@rm -f $(APP)
	-@rm -f $(OBJ)
	-@rm -f $(OBJ2)
