	.arch armv7-a
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 18, 4
	.file	"aflt_main.c"
@ GNU C (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) version 4.4.1 (arm-hisiv200-linux-gnueabi)
@	compiled by GNU C version 4.1.1 20061011 (Red Hat 4.1.1-30), GMP version 4.3.1, MPFR version 2.4.2.
@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
@ options passed:  -nostdinc
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include
@ -Iarch/arm/include/generated
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include
@ -Iinclude
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/uapi
@ -Iarch/arm/include/generated/uapi
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/uapi
@ -Iinclude/generated/uapi
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/adsp/adsp_v1_1
@ -Idrivers/msp/adsp/adsp_v1_1
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/mach-hi3798mx/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/api/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/drv/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/api/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/component/ha_codec/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/component/ha_effect/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/include/comp
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/aoe/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/aflt/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/aoe/src/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/component/codec/iapcm_dec
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/component/codec/iamp3_dec
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/component/effect/base_effect
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1
@ -imultilib armv7a_soft -iprefix
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/
@ -isysroot /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../target
@ -D__KERNEL__ -D__LINUX_ARM_ARCH__=7 -Uarm -DCHIP_TYPE_hi3796mv100
@ -DSDK_VERSION=HiSTBAndroidV600R001C00SPC060_v2015040918 -DHI_MCE_SUPPORT
@ -DHI_GPIOI2C_SUPPORT -DHI_LOG_SUPPORT=1 -DHI_LOG_LEVEL=4
@ -DHI_PROC_SUPPORT=1 -DHI_HDMI_SUPPORT_1_4 -DHI_KEYLED_SUPPORT
@ -DHI_HDCP_SUPPORT -DHI_SCI_SUPPORT -DHI_PVR_SUPPORT -DHI_VI_SUPPORT
@ -DHI_VENC_SUPPORT -DHI_AENC_SUPPORT -DHI_PQ_V3_0
@ -DHI_SND_AOE_SWSIMULATE_SUPPORT -DHI_SND_AFLT_SWSIMULATE_SUPPORT
@ -DINTERLEAVED_OUTPUT -DPCM_DECODER_SUPPORT -DBASE_EFFECT_SUPPORT
@ -DHI_SND_TIMER_CAST -DKBUILD_STR(s)=#s
@ -DKBUILD_BASENAME=KBUILD_STR(aflt_main)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_adsp) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/adsp/adsp_v1_1/./hifi/aflt/src/.aflt_main.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/adsp/adsp_v1_1/./hifi/aflt/src/aflt_main.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/adsp/adsp_v1_1/./hifi/aflt/src/aflt_main.o -O2 -Wall -Wundef
@ -Wstrict-prototypes -Wno-trigraphs -Werror-implicit-function-declaration
@ -Wno-format-security -Wframe-larger-than=1024
@ -Wdeclaration-after-statement -Wno-pointer-sign -p -fno-strict-aliasing
@ -fno-common -fno-delete-null-pointer-checks -fno-dwarf2-cfi-asm
@ -funwind-tables -fno-stack-protector -fno-omit-frame-pointer
@ -fno-optimize-sibling-calls -fno-strict-overflow -fconserve-stack
@ -fverbose-asm
@ options enabled:  -falign-loops -fargument-alias -fauto-inc-dec
@ -fbranch-count-reg -fcaller-saves -fcprop-registers -fcrossjumping
@ -fcse-follow-jumps -fdefer-pop -fearly-inlining
@ -feliminate-unused-debug-types -fexpensive-optimizations
@ -fforward-propagate -ffunction-cse -fgcse -fgcse-lm
@ -fguess-branch-probability -fident -fif-conversion -fif-conversion2
@ -findirect-inlining -finline -finline-functions-called-once
@ -finline-small-functions -fipa-cp -fipa-pure-const -fipa-reference
@ -fira-share-save-slots -fira-share-spill-slots -fivopts
@ -fkeep-static-consts -fleading-underscore -fmath-errno -fmerge-constants
@ -fmerge-debug-strings -fmove-loop-invariants -foptimize-register-move
@ -fpeephole -fpeephole2 -fprofile -fpromote-loop-indices
@ -freg-struct-return -fregmove -frename-registers -freorder-blocks
@ -freorder-functions -frerun-cse-after-loop -fsched-interblock
@ -fsched-spec -fsched-stalled-insns-dep -fschedule-insns -fschedule-insns2
@ -fsection-anchors -fsigned-zeros -fsplit-ivs-in-unroller
@ -fsplit-wide-types -fthread-jumps -ftoplevel-reorder -ftrapping-math
@ -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-copy-prop
@ -ftree-copyrename -ftree-cselim -ftree-dce -ftree-dominator-opts
@ -ftree-dse -ftree-fre -ftree-loop-im -ftree-loop-ivcanon
@ -ftree-loop-optimize -ftree-parallelize-loops= -ftree-pre -ftree-reassoc
@ -ftree-scev-cprop -ftree-sink -ftree-sra -ftree-switch-conversion
@ -ftree-ter -ftree-vect-loop-version -ftree-vrp -funit-at-a-time
@ -funroll-loops -funwind-tables -fverbose-asm -fweb
@ -fzero-initialized-in-bss -mapcs-frame -mglibc -mlittle-endian

@ Compiler executable checksum: fa59e0bd179ef45b3a3c3e6f3383fdac

	.text
	.align	2
	.global	AFLT_GetThreadStatus
	.type	AFLT_GetThreadStatus, %function
AFLT_GetThreadStatus:
	.fnstart
.LFB871:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {fp, ip, lr, pc}	@,
	.pad #4
	.save {fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r3, #:lower16:.LANCHOR0	@ tmp135,
	movt	r3, #:upper16:.LANCHOR0	@ tmp135,
	ldr	r0, [r3, #0]	@, g_enAfltTaskStatus
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	AFLT_GetThreadStatus, .-AFLT_GetThreadStatus
	.align	2
	.global	AFLT_Process
	.type	AFLT_Process, %function
AFLT_Process:
	.fnstart
.LFB868:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r4, #:lower16:.LANCHOR0	@ tmp144,
	movt	r4, #:upper16:.LANCHOR0	@ tmp144,
	ldr	r3, [r4, #4]	@ g_u32AfltId.290, g_u32AfltId
	cmp	r3, #7	@ g_u32AfltId.290,
	movhi	r5, #0	@ enAfltTask,
	bhi	.L5	@,
	mov	r5, #0	@ enAfltTask,
.L7:
	mov	r0, r3	@, g_u32AfltId.290
	bl	AFLTProcChn	@
	ldr	r3, [r4, #4]	@ g_u32AfltId.241, g_u32AfltId
	add	r3, r3, #1	@ g_u32AfltId.290, g_u32AfltId.241,
	str	r3, [r4, #4]	@ g_u32AfltId.290, g_u32AfltId
	cmp	r0, #1	@,
	moveq	r5, #1	@ enAfltTask,
	cmp	r3, #7	@ g_u32AfltId.290,
	bls	.L7	@,
.L5:
	mov	r1, #0	@ tmp142,
	mov	r0, r5	@, enAfltTask
	str	r1, [r4, #4]	@ tmp142, g_u32AfltId
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	AFLT_Process, .-AFLT_Process
	.align	2
	.global	AFLT_ProcThread_Sw
	.type	AFLT_ProcThread_Sw, %function
AFLT_ProcThread_Sw:
	.fnstart
.LFB870:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {fp, ip, lr, pc}	@,
	.pad #4
	.save {fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r0, #:lower16:.LANCHOR0	@ tmp133,
	movt	r0, #:upper16:.LANCHOR0	@ tmp133,
	ldr	r3, [r0, #8]	@ g_u32AfltInitFlag, g_u32AfltInitFlag
	cmp	r3, #0	@ g_u32AfltInitFlag,
	ldmeqfd	sp, {fp, sp, pc}	@
	bl	AFLT_Process	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	AFLT_ProcThread_Sw, .-AFLT_ProcThread_Sw
	.align	2
	.global	AFLT_ProcThread
	.type	AFLT_ProcThread, %function
AFLT_ProcThread:
	.fnstart
.LFB869:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r3, r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r4, #:lower16:.LANCHOR0	@ tmp134,
	movt	r4, #:upper16:.LANCHOR0	@ tmp134,
	mov	r2, #0	@ tmp135,
	ldr	r3, [r4, #8]	@ g_u32AfltInitFlag, g_u32AfltInitFlag
	str	r2, [r4, #0]	@ tmp135, g_enAfltTaskStatus
	cmp	r3, r2	@ g_u32AfltInitFlag,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	bl	AFLT_Process	@
	str	r0, [r4, #0]	@, g_enAfltTaskStatus
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	AFLT_ProcThread, .-AFLT_ProcThread
	.align	2
	.global	AFLT_DeInit
	.type	AFLT_DeInit, %function
AFLT_DeInit:
	.fnstart
.LFB867:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r3, r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r4, #:lower16:.LANCHOR0	@ tmp134,
	movt	r4, #:upper16:.LANCHOR0	@ tmp134,
	ldr	r3, [r4, #8]	@ g_u32AfltInitFlag, g_u32AfltInitFlag
	cmp	r3, #0	@ g_u32AfltInitFlag,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	mov	r0, #0	@,
	bl	AFLTChnDeInit	@
	mov	r0, #1	@,
	bl	AFLTChnDeInit	@
	mov	r0, #2	@,
	bl	AFLTChnDeInit	@
	mov	r0, #3	@,
	bl	AFLTChnDeInit	@
	mov	r0, #4	@,
	bl	AFLTChnDeInit	@
	mov	r0, #5	@,
	bl	AFLTChnDeInit	@
	mov	r0, #6	@,
	bl	AFLTChnDeInit	@
	mov	r0, #7	@,
	bl	AFLTChnDeInit	@
	ldr	r0, [r4, #12]	@ g_u32AfltRegMapAddr.239, g_u32AfltRegMapAddr
	mov	r1, #0	@ tmp137,
	str	r1, [r4, #8]	@ tmp137, g_u32AfltInitFlag
	cmp	r0, r1	@ g_u32AfltRegMapAddr.239,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	bl	__arm_iounmap	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	AFLT_DeInit, .-AFLT_DeInit
	.align	2
	.global	AFLT_Init
	.type	AFLT_Init, %function
AFLT_Init:
	.fnstart
.LFB866:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r4, #:lower16:.LANCHOR0	@ tmp135,
	movt	r4, #:upper16:.LANCHOR0	@ tmp135,
	ldr	r5, [r4, #8]	@ g_u32AfltInitFlag, g_u32AfltInitFlag
	cmp	r5, #0	@ g_u32AfltInitFlag,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	mov	r2, r5	@, g_u32AfltInitFlag
	mov	r1, #1536	@,
	movw	r0, #:lower16:-43008	@,
	movt	r0, #:upper16:-43008	@,
	bl	__arm_ioremap	@
	mov	r1, #1536	@,
	str	r0, [r4, #12]	@, g_u32AfltRegMapAddr
	bl	__memzero	@
	ldr	r1, [r4, #12]	@ g_u32AfltRegMapAddr, g_u32AfltRegMapAddr
	mov	r0, r5	@, g_u32AfltInitFlag
	add	r5, r1, #32	@ u32AfltChnRegBase, g_u32AfltRegMapAddr,
	mov	r1, r5	@, u32AfltChnRegBase
	bl	AFLTChnInit	@
	mov	r0, #1	@,
	mov	r1, r5	@, u32AfltChnRegBase
	bl	AFLTChnInit	@
	mov	r0, #2	@,
	mov	r1, r5	@, u32AfltChnRegBase
	bl	AFLTChnInit	@
	mov	r0, #3	@,
	mov	r1, r5	@, u32AfltChnRegBase
	bl	AFLTChnInit	@
	mov	r0, #4	@,
	mov	r1, r5	@, u32AfltChnRegBase
	bl	AFLTChnInit	@
	mov	r0, #5	@,
	mov	r1, r5	@, u32AfltChnRegBase
	bl	AFLTChnInit	@
	mov	r0, #6	@,
	mov	r1, r5	@, u32AfltChnRegBase
	bl	AFLTChnInit	@
	mov	r1, r5	@, u32AfltChnRegBase
	mov	r0, #7	@,
	bl	AFLTChnInit	@
	mov	r3, #1	@ tmp142,
	str	r3, [r4, #8]	@ tmp142, g_u32AfltInitFlag
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	AFLT_Init, .-AFLT_Init
	.align	2
	.global	AFLT_ProcFrame
	.type	AFLT_ProcFrame, %function
AFLT_ProcFrame:
	.fnstart
.LFB865:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {fp, ip, lr, pc}	@,
	.pad #4
	.save {fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	bl	AFLTProcFrame	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	AFLT_ProcFrame, .-AFLT_ProcFrame
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_enAfltTaskStatus, %object
	.size	g_enAfltTaskStatus, 4
g_enAfltTaskStatus:
	.space	4
	.type	g_u32AfltId, %object
	.size	g_u32AfltId, 4
g_u32AfltId:
	.space	4
	.type	g_u32AfltInitFlag, %object
	.size	g_u32AfltInitFlag, 4
g_u32AfltInitFlag:
	.space	4
	.type	g_u32AfltRegMapAddr, %object
	.size	g_u32AfltRegMapAddr, 4
g_u32AfltRegMapAddr:
	.space	4
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
