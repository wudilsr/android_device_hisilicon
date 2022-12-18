#!/bin/bash

#by fangjian00208632 2015-03-13



#!/bin/bash

DEBUG=0
#DEBUG=1

ROOT=.
KERNEL_TEXT_BASE=$1
IMG_RELEASE_PATH=${ROOT}/release
IMG_OUT_PATH=$2
KERNEL_PATH=${IMG_OUT_PATH}/rtosck.img
DST_PATH=${IMG_OUT_PATH}/trustedcore.img



TASK1_NAME=globaltask.img
TASK1_UUID="00000000000000000000000000000000"

TASK2_NAME=task_teetest.elf
TASK2_UUID="03030303030303030303030303030303"

TASK3_NAME=task_echo.elf
TASK3_UUID="01010101010101010101010101010101"

TASK4_NAME=task_QA_TZService.elf
TASK4_UUID="04040404040404040404040404040404"

TASK5_NAME=task_storage.elf
TASK5_UUID="02020202020202020202020202020202"
TASK6_NAME=demo_task.elf
#TASK6_UUID="8877b77989977a4aa2beb60155eef5f3"
TASK6_UUID="ffffffff000000000000000000000003"
TASK7_NAME=demo_task1.elf
TASK7_UUID="8877b77989977a4aa2beb60155eef5f4"
TASK8_NAME=demo_task2.elf
TASK8_UUID="8877b77989977a4aa2beb60155eef5f5"
TASK9_NAME=demo_task3.elf
TASK9_UUID="8877b77989977a4aa2beb60155eef5f6"
TASK10_NAME=demo_task4.elf
TASK10_UUID="8877b77989977a4aa2beb60155eef5f7"
TASK11_NAME=demo_task5.elf
TASK11_UUID="8877b77989977a4aa2beb60155eef5f8"
TASK12_NAME=demo_task6.elf
TASK12_UUID="8877b77989977a4aa2beb60155eef5f9"
TASK13_NAME=demo_task7.elf
TASK13_UUID="8877b77989977a4aa2beb60155eef5fa"
TASK14_NAME=demo_task8.elf
TASK14_UUID="8877b77989977a4aa2beb60155eef5fb"
TASK15_NAME=demo_task9.elf
TASK15_UUID="8877b77989977a4aa2beb60155eef5fc"

TASK1_PATH=${IMG_OUT_PATH}/${TASK1_NAME}
TASK2_PATH=${IMG_RELEASE_PATH}/internal_tasks/${TASK2_NAME}
TASK3_PATH=${IMG_RELEASE_PATH}/internal_tasks/${TASK3_NAME}
TASK5_PATH=${IMG_RELEASE_PATH}/internal_tasks/${TASK5_NAME}
TASK4_PATH=${IMG_OUT_PATH}/${TASK4_NAME}
TASK6_PATH=${IMG_OUT_PATH}/${TASK6_NAME}
TASK7_PATH=${IMG_OUT_PATH}/${TASK7_NAME}
TASK8_PATH=${IMG_OUT_PATH}/${TASK8_NAME}
TASK9_PATH=${IMG_OUT_PATH}/${TASK9_NAME}
TASK10_PATH=${IMG_OUT_PATH}/${TASK10_NAME}
TASK11_PATH=${IMG_OUT_PATH}/${TASK11_NAME}
TASK12_PATH=${IMG_OUT_PATH}/${TASK12_NAME}
TASK13_PATH=${IMG_OUT_PATH}/${TASK13_NAME}
TASK14_PATH=${IMG_OUT_PATH}/${TASK14_NAME}
TASK15_PATH=${IMG_OUT_PATH}/${TASK15_NAME}
#Add new internal task here:

TASK_LIST="${TASK1_PATH},${TASK1_NAME%.*},${TASK1_UUID},0x1000
${TASK2_PATH},${TASK2_NAME%.*},${TASK2_UUID},0x1000 \
${TASK3_PATH},${TASK3_NAME%.*},${TASK3_UUID},0x1000 \
${TASK4_PATH},${TASK4_NAME%.*},${TASK4_UUID},0x1000 \
${TASK5_PATH},${TASK5_NAME%.*},${TASK5_UUID},0x1000 \
${TASK6_PATH},${TASK6_NAME%.*},${TASK6_UUID},0x1000 \
${TASK7_PATH},${TASK7_NAME%.*},${TASK7_UUID},0x1000 \
${TASK8_PATH},${TASK8_NAME%.*},${TASK8_UUID},0x1000 \
${TASK9_PATH},${TASK9_NAME%.*},${TASK9_UUID},0x1000 \
${TASK10_PATH},${TASK10_NAME%.*},${TASK10_UUID},0x1000 \
${TASK11_PATH},${TASK11_NAME%.*},${TASK11_UUID},0x1000 \
${TASK12_PATH},${TASK12_NAME%.*},${TASK12_UUID},0x1000 \
${TASK13_PATH},${TASK13_NAME%.*},${TASK13_UUID},0x1000 \
${TASK14_PATH},${TASK14_NAME%.*},${TASK14_UUID},0x1000 \
${TASK15_PATH},${TASK15_NAME%.*},${TASK15_UUID},0x1000 \
"


echo "1. get globaltask.got size"
if [ $DEBUG -gt 0 ];then
    TASK1_ELF=${IMG_OUT_PATH}/${TASK1_NAME}.elf
else
    TASK1_ELF=${IMG_OUT_PATH}/${TASK1_NAME}.elf
fi

GOT_SIZE=$(size -A -x ${TASK1_ELF}| awk '{if ($1==".rel.dyn") {print $2}}')
echo "GOT_SIZE=${GOT_SIZE}"

echo "2. generate header"
${ROOT}/header.py ${DST_PATH} ${KERNEL_PATH} \
${KERNEL_TEXT_BASE} ${GOT_SIZE} \
${TASK_LIST}