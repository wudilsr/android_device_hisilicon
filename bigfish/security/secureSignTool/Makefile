#CUR_DIR:=$(PWD)
CUR_DIR:=.
POLARSSL:=polarssl-0.14.0

CFG_INC := -I${CUR_DIR}/src
CFG_INC += -I${CUR_DIR}
CFG_INC += -I${CUR_DIR}/openssl-1.0.1g/include/
CFG_LIB += -L${CUR_DIR}/openssl-1.0.1g -lcrypto
CFG_LIB += -L${CUR_DIR}/libs -lBootSign_x86

PRERE += ${CUR_DIR}/src/crypto.c
PRERE += ${CUR_DIR}/src/sign_non_boot_image.c
#PRERE += ${CUR_DIR}/libs/signprocess.c
PRERE += ${CUR_DIR}/src/sha2.c
PRERE += ${CUR_DIR}/src/adapter.c
PRERE += ${CUR_DIR}/secureSignTool.c
CFLAG += -static -Wall

CC := gcc

SRC = $(wildcard *.c)
APP = $(basename $(SRC))

$(APP): $(PRERE)
	$(MAKE) -C libs
	$(MAKE) -C openssl-1.0.1g
	$(CC) -o $@ $^ $(CFG_INC) $(CFG_LIB)

clean:
	-@rm -rf $(APP)
	$(MAKE) -C libs clean
	$(MAKE) -C openssl-1.0.1g clean
