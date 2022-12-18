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
	.file	"aoe_engine.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(aoe_engine)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_adsp) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/adsp/adsp_v1_1/./hifi/aoe/src/engine/.aoe_engine.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/adsp/adsp_v1_1/./hifi/aoe/src/engine/aoe_engine.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/adsp/adsp_v1_1/./hifi/aoe/src/engine/aoe_engine.o -O2 -Wall
@ -Wundef -Wstrict-prototypes -Wno-trigraphs
@ -Werror-implicit-function-declaration -Wno-format-security
@ -Wframe-larger-than=1024 -Wdeclaration-after-statement -Wno-pointer-sign
@ -p -fno-strict-aliasing -fno-common -fno-delete-null-pointer-checks
@ -fno-dwarf2-cfi-asm -funwind-tables -fno-stack-protector
@ -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-strict-overflow
@ -fconserve-stack -fverbose-asm
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
	.global	ENGINE_GetChnCmd
	.type	ENGINE_GetChnCmd, %function
ENGINE_GetChnCmd:
	.fnstart
.LFB857:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r3, [r3, r0, asl #2]	@ pEneReg, g_stEneRm.hwEneReg
	ldr	r2, [r3, #4]	@ D.15232,
	tst	r2, #8	@ D.15232,
	movne	r0, #2	@ eNewCmd,
	bne	.L3	@,
	ldr	r0, [r3, #4]	@ tmp142,
	ands	r0, r0, #3	@ D.15236, tmp142,
	beq	.L3	@,
	cmp	r0, #1	@ D.15236,
	beq	.L3	@,
	ldr	r2, [r3, #4]	@ tmp144,
	mov	ip, #4	@ tmp145,
	mov	r0, #2	@ eNewCmd,
	bfi	r2, ip, #4, #4	@ tmp144, tmp145,,
	str	r2, [r3, #4]	@ tmp144,
	ldr	r2, [r3, #4]	@ tmp146,
	orr	ip, r2, #8	@ tmp149, tmp146,
	str	ip, [r3, #4]	@ tmp149,
.L3:
	str	r0, [r1, #0]	@ eNewCmd,* newcmd
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	ENGINE_GetChnCmd, .-ENGINE_GetChnCmd
	.align	2
	.global	ENGINEAckCmd
	.type	ENGINEAckCmd, %function
ENGINEAckCmd:
	.fnstart
.LFB858:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp138,
	movt	r3, #:upper16:.LANCHOR0	@ tmp138,
	ldr	r3, [r3, r0, asl #2]	@ pEneReg, g_stEneRm.hwEneReg
	ldr	r2, [r3, #4]	@ D.15245,
	tst	r2, #8	@ D.15245,
	ldmnefd	sp, {fp, sp, pc}	@
	ldr	ip, [r3, #4]	@ tmp142,
	bfi	ip, r1, #4, #4	@ tmp142, Ack,,
	str	ip, [r3, #4]	@ tmp142,
	ldr	r1, [r3, #4]	@ tmp143,
	orr	r0, r1, #8	@ tmp145, tmp143,
	str	r0, [r3, #4]	@ tmp145,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	ENGINEAckCmd, .-ENGINEAckCmd
	.align	2
	.global	ENGINEProcChnStopCmd
	.type	ENGINEProcChnStopCmd, %function
ENGINEProcChnStopCmd:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp146,
	add	r2, r0, #6	@ tmp138, Id,
	movt	r3, #:upper16:.LANCHOR0	@ tmp146,
	ldr	r2, [r3, r2, asl #2]	@ state, g_stEneRm.hEne
	cmp	r2, #0	@ state,
	ldmeqfd	sp, {fp, sp, pc}	@
	ldr	r1, [r2, #76]	@ <variable>.CurStatus, <variable>.CurStatus
	cmp	r1, #1	@ <variable>.CurStatus,
	moveq	r1, #0	@ tmp140,
	streq	r1, [r2, #76]	@ tmp140, <variable>.CurStatus
	ldr	r3, [r3, r0, asl #2]	@ pEneReg, g_stEneRm.hwEneReg
	ldr	r0, [r3, #4]	@ D.15914,
	ands	r2, r0, #8	@ tmp142, D.15914,
	ldmnefd	sp, {fp, sp, pc}	@
	ldr	r0, [r3, #4]	@ tmp143,
	bfi	r0, r2, #4, #4	@ tmp143, tmp142,,
	str	r0, [r3, #4]	@ tmp143,
	ldr	r2, [r3, #4]	@ tmp144,
	orr	ip, r2, #8	@ tmp147, tmp144,
	str	ip, [r3, #4]	@ tmp147,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	ENGINEProcChnStopCmd, .-ENGINEProcChnStopCmd
	.align	2
	.global	ENGINEUpdateChnAefState
	.type	ENGINEUpdateChnAefState, %function
ENGINEUpdateChnAefState:
	.fnstart
.LFB876:
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
	str	r1, [r0, #56]	@ AefFlag, <variable>.AefMask
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	ENGINEUpdateChnAefState, .-ENGINEUpdateChnAefState
	.align	2
	.global	ENGINEGetCunrStatus
	.type	ENGINEGetCunrStatus, %function
ENGINEGetCunrStatus:
	.fnstart
.LFB877:
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
	movw	r1, #:lower16:.LANCHOR0	@ tmp137,
	add	r0, r0, #6	@ tmp138, Id,
	movt	r1, #:upper16:.LANCHOR0	@ tmp137,
	ldr	r3, [r1, r0, asl #2]	@ state, g_stEneRm.hEne
	cmp	r3, #0	@ state,
	moveq	r0, #2	@ D.15828,
	ldrne	r0, [r3, #76]	@ D.15828, <variable>.CurStatus
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	ENGINEGetCunrStatus, .-ENGINEGetCunrStatus
	.align	2
	.global	ENGINESwResetReg
	.type	ENGINESwResetReg, %function
ENGINESwResetReg:
	.fnstart
.LFB879:
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
	mov	r1, #32	@,
	mov	r4, r0	@ pEneReg, pEneReg
	bl	__memzero	@
	ldr	r1, [r4, #4]	@ tmp134,
	mov	r2, #1	@ tmp137,
	orr	r0, r1, #8	@ tmp138, tmp134,
	str	r0, [r4, #4]	@ tmp138,
	ldr	r3, [r4, #4]	@ tmp136,
	bfi	r3, r2, #0, #2	@ tmp136, tmp137,,
	str	r3, [r4, #4]	@ tmp136,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	ENGINESwResetReg, .-ENGINESwResetReg
	.align	2
	.global	ENGINE_Init
	.type	ENGINE_Init, %function
ENGINE_Init:
	.fnstart
.LFB881:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r3, r4, r5, r6, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, r5, r6, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r4, #:lower16:.LANCHOR0	@ tmp140,
	movt	r4, #:upper16:.LANCHOR0	@ tmp140,
	mov	r6, r0	@ u32EngineRegBase, u32EngineRegBase
	mov	r5, #0	@ tmp142,
	str	r0, [r4, #0]	@ u32EngineRegBase, g_stEneRm.hwEneReg
	bl	ENGINESwResetReg	@
	add	r0, r6, #32	@ temp.426, u32EngineRegBase,
	str	r5, [r4, #24]	@ tmp142, g_stEneRm.hEne
	str	r0, [r4, #4]	@ temp.426, g_stEneRm.hwEneReg
	bl	ENGINESwResetReg	@
	add	r2, r6, #64	@ temp.428, u32EngineRegBase,
	str	r5, [r4, #28]	@ tmp142, g_stEneRm.hEne
	str	r2, [r4, #8]	@ temp.428, g_stEneRm.hwEneReg
	mov	r0, r2	@, temp.428
	bl	ENGINESwResetReg	@
	add	r1, r6, #96	@ temp.430, u32EngineRegBase,
	str	r5, [r4, #32]	@ tmp142, g_stEneRm.hEne
	mov	r0, r1	@, temp.430
	str	r1, [r4, #12]	@ temp.430, g_stEneRm.hwEneReg
	bl	ENGINESwResetReg	@
	add	r3, r6, #128	@ temp.432, u32EngineRegBase,
	add	r6, r6, #160	@ D.15874, u32EngineRegBase,
	str	r3, [r4, #16]	@ temp.432, g_stEneRm.hwEneReg
	mov	r0, r3	@, temp.432
	str	r5, [r4, #36]	@ tmp142, g_stEneRm.hEne
	bl	ENGINESwResetReg	@
	mov	r0, r6	@, D.15874
	str	r5, [r4, #40]	@ tmp142, g_stEneRm.hEne
	str	r6, [r4, #20]	@ D.15874, g_stEneRm.hwEneReg
	bl	ENGINESwResetReg	@
	str	r5, [r4, #44]	@ tmp142, g_stEneRm.hEne
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	ENGINE_Init, .-ENGINE_Init
	.align	2
	.global	ENGINEUpdateChnAopState
	.type	ENGINEUpdateChnAopState, %function
ENGINEUpdateChnAopState:
	.fnstart
.LFB875:
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #76
	sub	sp, sp, #76	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	ldr	r2, [r0, #0]	@, <variable>.stAttr.u32BitPerSample
	tst	r1, #1	@ AopFlag,
	mov	r4, r1	@ AopFlag, AopFlag
	mov	r5, r0	@ state, state
	str	r2, [fp, #-108]	@, %sfp
	ldr	r3, [r0, #72]	@, <variable>.SamplePerFrame
	str	r3, [fp, #-104]	@, %sfp
	bne	.L95	@,
.L28:
	mov	r6, #0	@ AopBufFreeFlag,
	mov	r7, r6	@ AopNeedUnifyMask, AopBufFreeFlag
	mov	sl, r6	@ AopNoneUnifyMask, AopBufFreeFlag
	mov	r9, r6	@ AopHiPriorityFlag, AopBufFreeFlag
	mov	r8, r6	@ AopLoPriorityFlag, AopBufFreeFlag
.L32:
	tst	r4, #2	@ AopFlag,
	bne	.L96	@,
.L35:
	tst	r4, #4	@ AopFlag,
	bne	.L97	@,
.L42:
	tst	r4, #8	@ AopFlag,
	bne	.L98	@,
.L49:
	tst	r4, #16	@ AopFlag,
	bne	.L99	@,
.L56:
	tst	r4, #32	@ AopFlag,
	bne	.L100	@,
.L63:
	tst	r4, #64	@ AopFlag,
	bne	.L101	@,
.L70:
	tst	r4, #128	@ AopFlag,
	bne	.L102	@,
.L77:
	str	r6, [r5, #52]	@ AopBufFreeFlag, <variable>.AopBufFreeFlag
	str	r4, [r5, #32]	@ AopFlag, <variable>.AopMask
	str	r9, [r5, #36]	@ AopHiPriorityFlag, <variable>.AopHiPriorityMask
	str	r8, [r5, #40]	@ AopLoPriorityFlag, <variable>.AopLoPriorityMask
	str	sl, [r5, #44]	@ AopNoneUnifyMask, <variable>.AopNoneUnifyMask
	str	r7, [r5, #48]	@ AopNeedUnifyMask, <variable>.AopNeedUnifyMask
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L95:
	mov	r0, #0	@,
	sub	r1, fp, #64	@,,
	bl	AOP_GetChnStatus	@
	ldr	r6, [fp, #-64]	@ status.CurnStatus, status.CurnStatus
	cmp	r6, #1	@ status.CurnStatus,
	bne	.L28	@,
	ldr	r7, [fp, #-52]	@ status.uFrameSize, status.uFrameSize
	mov	r0, #0	@,
	ldr	sl, [fp, #-104]	@, %sfp
	sub	r1, fp, #100	@,,
	ldr	r9, [fp, #-60]	@ status.Priority, status.Priority
	ldr	r3, [fp, #-56]	@ status.u32BitPerSample, status.u32BitPerSample
	mul	ip, r7, sl	@ blocksize.469, status.uFrameSize,
	cmp	r9, #1	@ status.Priority,
	ldr	lr, [fp, #-108]	@, %sfp
	movne	r9, r0	@, AopHiPriorityFlag,
	moveq	r8, #0	@, AopLoPriorityFlag
	movne	r8, #1	@, AopLoPriorityFlag
	cmp	r3, lr	@ status.u32BitPerSample,
	str	ip, [fp, #-112]	@,
	movne	sl, #0	@, AopNoneUnifyMask
	moveq	sl, #1	@, AopNoneUnifyMask
	moveq	r7, #0	@, AopNeedUnifyMask
	movne	r7, #1	@, AopNeedUnifyMask
	bl	AOP_QueryRbfInfo	@
	ldr	r0, [fp, #-72]	@ stRbfOut.u32TotalFreeSize, stRbfOut.u32TotalFreeSize
	ldr	r3, [fp, #-112]	@,
	cmp	r3, r0	@ blocksize.469, stRbfOut.u32TotalFreeSize
	bcs	.L31	@,
	ldr	r0, [fp, #-80]	@ stRbfOut.u32TotalDataSize, stRbfOut.u32TotalDataSize
	ldr	r2, [fp, #-68]	@ stRbfOut.u32LatencySize, stRbfOut.u32LatencySize
	add	r1, r3, r0	@ tmp158, blocksize.469, stRbfOut.u32TotalDataSize
	cmp	r1, r2	@ tmp158, stRbfOut.u32LatencySize
	bhi	.L31	@,
	cmp	r3, #0	@ blocksize.469,
	bne	.L32	@,
.L31:
	mov	r6, #0	@ AopBufFreeFlag,
	b	.L32	@
.L102:
	mov	r0, #7	@,
	sub	r1, fp, #64	@,,
	bl	AOP_GetChnStatus	@
	ldr	ip, [fp, #-64]	@ status.CurnStatus, status.CurnStatus
	cmp	ip, #1	@ status.CurnStatus,
	bne	.L77	@,
	ldr	lr, [fp, #-52]	@ status.uFrameSize, status.uFrameSize
	ldr	r2, [fp, #-104]	@, %sfp
	ldr	r1, [fp, #-60]	@ status.Priority, status.Priority
	ldr	r0, [fp, #-108]	@, %sfp
	mul	r3, lr, r2	@ blocksize, status.uFrameSize,
	ldr	ip, [fp, #-56]	@ status.u32BitPerSample, status.u32BitPerSample
	cmp	r1, #1	@ status.Priority,
	sub	r1, fp, #100	@,,
	orreq	r9, r9, #128	@ AopHiPriorityFlag, AopHiPriorityFlag,
	orrne	r8, r8, #128	@ AopLoPriorityFlag, AopLoPriorityFlag,
	cmp	ip, r0	@ status.u32BitPerSample,
	mov	r0, #7	@,
	orreq	sl, sl, #128	@ AopNoneUnifyMask, AopNoneUnifyMask,
	orrne	r7, r7, #128	@ AopNeedUnifyMask, AopNeedUnifyMask,
	str	r3, [fp, #-112]	@,
	bl	AOP_QueryRbfInfo	@
	ldr	r1, [fp, #-72]	@ stRbfOut.u32TotalFreeSize, stRbfOut.u32TotalFreeSize
	ldr	r3, [fp, #-112]	@,
	cmp	r3, r1	@ blocksize, stRbfOut.u32TotalFreeSize
	bcs	.L77	@,
	ldr	r0, [fp, #-80]	@ stRbfOut.u32TotalDataSize, stRbfOut.u32TotalDataSize
	ldr	r2, [fp, #-68]	@ stRbfOut.u32LatencySize, stRbfOut.u32LatencySize
	add	lr, r3, r0	@ tmp235, blocksize, stRbfOut.u32TotalDataSize
	cmp	lr, r2	@ tmp235, stRbfOut.u32LatencySize
	bhi	.L77	@,
	cmp	r3, #0	@ blocksize,
	orrne	r6, r6, #128	@ AopBufFreeFlag, AopBufFreeFlag,
	b	.L77	@
.L101:
	mov	r0, #6	@,
	sub	r1, fp, #64	@,,
	bl	AOP_GetChnStatus	@
	ldr	ip, [fp, #-64]	@ status.CurnStatus, status.CurnStatus
	cmp	ip, #1	@ status.CurnStatus,
	bne	.L70	@,
	ldr	r3, [fp, #-60]	@ status.Priority, status.Priority
	cmp	r3, #1	@ status.Priority,
	orrne	r8, r8, #64	@ AopLoPriorityFlag, AopLoPriorityFlag,
	beq	.L103	@,
.L76:
	ldr	r0, [fp, #-56]	@ status.u32BitPerSample, status.u32BitPerSample
	ldr	lr, [fp, #-108]	@, %sfp
	cmp	r0, lr	@ status.u32BitPerSample,
	orrne	r7, r7, #64	@ AopNeedUnifyMask, AopNeedUnifyMask,
	beq	.L104	@,
.L75:
	ldr	r3, [fp, #-52]	@ status.uFrameSize, status.uFrameSize
	mov	r0, #6	@,
	ldr	lr, [fp, #-104]	@, %sfp
	sub	r1, fp, #100	@,,
	mul	ip, r3, lr	@ blocksize.529, status.uFrameSize,
	str	ip, [fp, #-112]	@,
	bl	AOP_QueryRbfInfo	@
	ldr	r2, [fp, #-72]	@ stRbfOut.u32TotalFreeSize, stRbfOut.u32TotalFreeSize
	ldr	r3, [fp, #-112]	@,
	cmp	r3, r2	@ blocksize.529, stRbfOut.u32TotalFreeSize
	bcs	.L70	@,
	ldr	r2, [fp, #-80]	@ stRbfOut.u32TotalDataSize, stRbfOut.u32TotalDataSize
	ldr	r0, [fp, #-68]	@ stRbfOut.u32LatencySize, stRbfOut.u32LatencySize
	add	r1, r3, r2	@ tmp224, blocksize.529, stRbfOut.u32TotalDataSize
	cmp	r1, r0	@ tmp224, stRbfOut.u32LatencySize
	bhi	.L70	@,
	cmp	r3, #0	@ blocksize.529,
	orrne	r6, r6, #64	@ AopBufFreeFlag, AopBufFreeFlag,
	b	.L70	@
.L100:
	mov	r0, #5	@,
	sub	r1, fp, #64	@,,
	bl	AOP_GetChnStatus	@
	ldr	ip, [fp, #-64]	@ status.CurnStatus, status.CurnStatus
	cmp	ip, #1	@ status.CurnStatus,
	bne	.L63	@,
	ldr	r3, [fp, #-60]	@ status.Priority, status.Priority
	cmp	r3, #1	@ status.Priority,
	orrne	r8, r8, #32	@ AopLoPriorityFlag, AopLoPriorityFlag,
	beq	.L105	@,
.L69:
	ldr	r1, [fp, #-56]	@ status.u32BitPerSample, status.u32BitPerSample
	ldr	lr, [fp, #-108]	@, %sfp
	cmp	r1, lr	@ status.u32BitPerSample,
	orrne	r7, r7, #32	@ AopNeedUnifyMask, AopNeedUnifyMask,
	beq	.L106	@,
.L68:
	ldr	r3, [fp, #-52]	@ status.uFrameSize, status.uFrameSize
	mov	r0, #5	@,
	ldr	lr, [fp, #-104]	@, %sfp
	sub	r1, fp, #100	@,,
	mul	ip, r3, lr	@ blocksize.519, status.uFrameSize,
	str	ip, [fp, #-112]	@,
	bl	AOP_QueryRbfInfo	@
	ldr	r2, [fp, #-72]	@ stRbfOut.u32TotalFreeSize, stRbfOut.u32TotalFreeSize
	ldr	r3, [fp, #-112]	@,
	cmp	r3, r2	@ blocksize.519, stRbfOut.u32TotalFreeSize
	bcs	.L63	@,
	ldr	r1, [fp, #-80]	@ stRbfOut.u32TotalDataSize, stRbfOut.u32TotalDataSize
	ldr	r2, [fp, #-68]	@ stRbfOut.u32LatencySize, stRbfOut.u32LatencySize
	add	r0, r3, r1	@ tmp213, blocksize.519, stRbfOut.u32TotalDataSize
	cmp	r0, r2	@ tmp213, stRbfOut.u32LatencySize
	bhi	.L63	@,
	cmp	r3, #0	@ blocksize.519,
	orrne	r6, r6, #32	@ AopBufFreeFlag, AopBufFreeFlag,
	b	.L63	@
.L99:
	mov	r0, #4	@,
	sub	r1, fp, #64	@,,
	bl	AOP_GetChnStatus	@
	ldr	r3, [fp, #-64]	@ status.CurnStatus, status.CurnStatus
	cmp	r3, #1	@ status.CurnStatus,
	bne	.L56	@,
	ldr	lr, [fp, #-60]	@ status.Priority, status.Priority
	cmp	lr, #1	@ status.Priority,
	orrne	r8, r8, #16	@ AopLoPriorityFlag, AopLoPriorityFlag,
	beq	.L107	@,
.L62:
	ldr	r1, [fp, #-56]	@ status.u32BitPerSample, status.u32BitPerSample
	ldr	r2, [fp, #-108]	@, %sfp
	cmp	r1, r2	@ status.u32BitPerSample,
	orrne	r7, r7, #16	@ AopNeedUnifyMask, AopNeedUnifyMask,
	beq	.L108	@,
.L61:
	ldr	r3, [fp, #-52]	@ status.uFrameSize, status.uFrameSize
	mov	r0, #4	@,
	ldr	lr, [fp, #-104]	@, %sfp
	sub	r1, fp, #100	@,,
	mul	ip, r3, lr	@ blocksize.509, status.uFrameSize,
	str	ip, [fp, #-112]	@,
	bl	AOP_QueryRbfInfo	@
	ldr	r0, [fp, #-72]	@ stRbfOut.u32TotalFreeSize, stRbfOut.u32TotalFreeSize
	ldr	r3, [fp, #-112]	@,
	cmp	r3, r0	@ blocksize.509, stRbfOut.u32TotalFreeSize
	bcs	.L56	@,
	ldr	r0, [fp, #-80]	@ stRbfOut.u32TotalDataSize, stRbfOut.u32TotalDataSize
	ldr	r2, [fp, #-68]	@ stRbfOut.u32LatencySize, stRbfOut.u32LatencySize
	add	r1, r3, r0	@ tmp202, blocksize.509, stRbfOut.u32TotalDataSize
	cmp	r1, r2	@ tmp202, stRbfOut.u32LatencySize
	bhi	.L56	@,
	cmp	r3, #0	@ blocksize.509,
	orrne	r6, r6, #16	@ AopBufFreeFlag, AopBufFreeFlag,
	b	.L56	@
.L98:
	mov	r0, #3	@,
	sub	r1, fp, #64	@,,
	bl	AOP_GetChnStatus	@
	ldr	ip, [fp, #-64]	@ status.CurnStatus, status.CurnStatus
	cmp	ip, #1	@ status.CurnStatus,
	bne	.L49	@,
	ldr	lr, [fp, #-60]	@ status.Priority, status.Priority
	cmp	lr, #1	@ status.Priority,
	orrne	r8, r8, #8	@ AopLoPriorityFlag, AopLoPriorityFlag,
	beq	.L109	@,
.L55:
	ldr	r3, [fp, #-56]	@ status.u32BitPerSample, status.u32BitPerSample
	ldr	r1, [fp, #-108]	@, %sfp
	cmp	r3, r1	@ status.u32BitPerSample,
	orrne	r7, r7, #8	@ AopNeedUnifyMask, AopNeedUnifyMask,
	beq	.L110	@,
.L54:
	ldr	lr, [fp, #-52]	@ status.uFrameSize, status.uFrameSize
	mov	r0, #3	@,
	ldr	r2, [fp, #-104]	@, %sfp
	sub	r1, fp, #100	@,,
	mul	ip, lr, r2	@ blocksize.499, status.uFrameSize,
	str	ip, [fp, #-112]	@,
	bl	AOP_QueryRbfInfo	@
	ldr	r0, [fp, #-72]	@ stRbfOut.u32TotalFreeSize, stRbfOut.u32TotalFreeSize
	ldr	r3, [fp, #-112]	@,
	cmp	r3, r0	@ blocksize.499, stRbfOut.u32TotalFreeSize
	bcs	.L49	@,
	ldr	ip, [fp, #-80]	@ stRbfOut.u32TotalDataSize, stRbfOut.u32TotalDataSize
	ldr	r0, [fp, #-68]	@ stRbfOut.u32LatencySize, stRbfOut.u32LatencySize
	add	r1, r3, ip	@ tmp191, blocksize.499, stRbfOut.u32TotalDataSize
	cmp	r1, r0	@ tmp191, stRbfOut.u32LatencySize
	bhi	.L49	@,
	cmp	r3, #0	@ blocksize.499,
	orrne	r6, r6, #8	@ AopBufFreeFlag, AopBufFreeFlag,
	b	.L49	@
.L97:
	mov	r0, #2	@,
	sub	r1, fp, #64	@,,
	bl	AOP_GetChnStatus	@
	ldr	ip, [fp, #-64]	@ status.CurnStatus, status.CurnStatus
	cmp	ip, #1	@ status.CurnStatus,
	bne	.L42	@,
	ldr	lr, [fp, #-60]	@ status.Priority, status.Priority
	cmp	lr, #1	@ status.Priority,
	orrne	r8, r8, #4	@ AopLoPriorityFlag, AopLoPriorityFlag,
	beq	.L111	@,
.L48:
	ldr	r3, [fp, #-56]	@ status.u32BitPerSample, status.u32BitPerSample
	ldr	r0, [fp, #-108]	@, %sfp
	cmp	r3, r0	@ status.u32BitPerSample,
	orrne	r7, r7, #4	@ AopNeedUnifyMask, AopNeedUnifyMask,
	beq	.L112	@,
.L47:
	ldr	r3, [fp, #-104]	@, %sfp
	mov	r0, #2	@,
	ldr	lr, [fp, #-52]	@ status.uFrameSize, status.uFrameSize
	sub	r1, fp, #100	@,,
	mul	ip, lr, r3	@ blocksize.489, status.uFrameSize,
	str	ip, [fp, #-112]	@,
	bl	AOP_QueryRbfInfo	@
	ldr	r2, [fp, #-72]	@ stRbfOut.u32TotalFreeSize, stRbfOut.u32TotalFreeSize
	ldr	r3, [fp, #-112]	@,
	cmp	r3, r2	@ blocksize.489, stRbfOut.u32TotalFreeSize
	bcs	.L42	@,
	ldr	r2, [fp, #-80]	@ stRbfOut.u32TotalDataSize, stRbfOut.u32TotalDataSize
	ldr	r0, [fp, #-68]	@ stRbfOut.u32LatencySize, stRbfOut.u32LatencySize
	add	r1, r3, r2	@ tmp180, blocksize.489, stRbfOut.u32TotalDataSize
	cmp	r1, r0	@ tmp180, stRbfOut.u32LatencySize
	bhi	.L42	@,
	cmp	r3, #0	@ blocksize.489,
	orrne	r6, r6, #4	@ AopBufFreeFlag, AopBufFreeFlag,
	b	.L42	@
.L96:
	mov	r0, #1	@,
	sub	r1, fp, #64	@,,
	bl	AOP_GetChnStatus	@
	ldr	ip, [fp, #-64]	@ status.CurnStatus, status.CurnStatus
	cmp	ip, #1	@ status.CurnStatus,
	bne	.L35	@,
	ldr	lr, [fp, #-60]	@ status.Priority, status.Priority
	cmp	lr, #1	@ status.Priority,
	orrne	r8, r8, #2	@ AopLoPriorityFlag, AopLoPriorityFlag,
	beq	.L113	@,
.L41:
	ldr	r3, [fp, #-56]	@ status.u32BitPerSample, status.u32BitPerSample
	ldr	r1, [fp, #-108]	@, %sfp
	cmp	r3, r1	@ status.u32BitPerSample,
	orrne	r7, r7, #2	@ AopNeedUnifyMask, AopNeedUnifyMask,
	beq	.L114	@,
.L40:
	ldr	r3, [fp, #-104]	@, %sfp
	mov	r0, #1	@,
	ldr	lr, [fp, #-52]	@ status.uFrameSize, status.uFrameSize
	sub	r1, fp, #100	@,,
	mul	ip, lr, r3	@ blocksize.479, status.uFrameSize,
	str	ip, [fp, #-112]	@,
	bl	AOP_QueryRbfInfo	@
	ldr	r2, [fp, #-72]	@ stRbfOut.u32TotalFreeSize, stRbfOut.u32TotalFreeSize
	ldr	r3, [fp, #-112]	@,
	cmp	r3, r2	@ blocksize.479, stRbfOut.u32TotalFreeSize
	bcs	.L35	@,
	ldr	r1, [fp, #-80]	@ stRbfOut.u32TotalDataSize, stRbfOut.u32TotalDataSize
	ldr	r2, [fp, #-68]	@ stRbfOut.u32LatencySize, stRbfOut.u32LatencySize
	add	r0, r3, r1	@ tmp169, blocksize.479, stRbfOut.u32TotalDataSize
	cmp	r0, r2	@ tmp169, stRbfOut.u32LatencySize
	bhi	.L35	@,
	cmp	r3, #0	@ blocksize.479,
	orrne	r6, r6, #2	@ AopBufFreeFlag, AopBufFreeFlag,
	b	.L35	@
.L104:
	orr	sl, sl, #64	@ AopNoneUnifyMask, AopNoneUnifyMask,
	b	.L75	@
.L103:
	orr	r9, r9, #64	@ AopHiPriorityFlag, AopHiPriorityFlag,
	b	.L76	@
.L106:
	orr	sl, sl, #32	@ AopNoneUnifyMask, AopNoneUnifyMask,
	b	.L68	@
.L105:
	orr	r9, r9, #32	@ AopHiPriorityFlag, AopHiPriorityFlag,
	b	.L69	@
.L112:
	orr	sl, sl, #4	@ AopNoneUnifyMask, AopNoneUnifyMask,
	b	.L47	@
.L111:
	orr	r9, r9, #4	@ AopHiPriorityFlag, AopHiPriorityFlag,
	b	.L48	@
.L114:
	orr	sl, sl, #2	@ AopNoneUnifyMask, AopNoneUnifyMask,
	b	.L40	@
.L113:
	orr	r9, r9, #2	@ AopHiPriorityFlag, AopHiPriorityFlag,
	b	.L41	@
.L108:
	orr	sl, sl, #16	@ AopNoneUnifyMask, AopNoneUnifyMask,
	b	.L61	@
.L107:
	orr	r9, r9, #16	@ AopHiPriorityFlag, AopHiPriorityFlag,
	b	.L62	@
.L110:
	orr	sl, sl, #8	@ AopNoneUnifyMask, AopNoneUnifyMask,
	b	.L54	@
.L109:
	orr	r9, r9, #8	@ AopHiPriorityFlag, AopHiPriorityFlag,
	b	.L55	@
	.fnend
	.size	ENGINEUpdateChnAopState, .-ENGINEUpdateChnAopState
	.align	2
	.global	ENGINEUpdateChnAipState
	.type	ENGINEUpdateChnAipState, %function
ENGINEUpdateChnAipState:
	.fnstart
.LFB874:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #48
	sub	sp, sp, #48	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	tst	r1, #1	@ AipFlag,
	mov	r4, r1	@ AipFlag, AipFlag
	mov	r5, r0	@ state, state
	bne	.L171	@,
.L116:
	mov	r6, #0	@ AipBufDataFlag,
	mov	r8, r6	@ AipHiPriorityFlag, AipBufDataFlag
	mov	r7, r6	@ AipLoPriorityFlag, AipBufDataFlag
.L119:
	tst	r4, #2	@ AipFlag,
	bne	.L172	@,
.L123:
	tst	r4, #4	@ AipFlag,
	bne	.L173	@,
.L129:
	tst	r4, #8	@ AipFlag,
	bne	.L174	@,
.L135:
	tst	r4, #16	@ AipFlag,
	bne	.L175	@,
.L141:
	tst	r4, #32	@ AipFlag,
	bne	.L176	@,
.L147:
	tst	r4, #64	@ AipFlag,
	bne	.L177	@,
.L153:
	tst	r4, #128	@ AipFlag,
	bne	.L178	@,
.L159:
	str	r6, [r5, #28]	@ AipBufDataFlag, <variable>.AipBufDataFlag
	str	r4, [r5, #16]	@ AipFlag, <variable>.AipMask
	str	r8, [r5, #20]	@ AipHiPriorityFlag, <variable>.AipHiPriorityMask
	str	r7, [r5, #24]	@ AipLoPriorityFlag, <variable>.AipLoPriorityMask
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L171:
	mov	r0, #0	@,
	sub	r1, fp, #44	@,,
	bl	AIP_GetChnStatus	@
	ldr	r6, [fp, #-44]	@ status.CurnStatus, status.CurnStatus
	cmp	r6, #1	@ status.CurnStatus,
	beq	.L117	@,
	mov	r0, #0	@,
	sub	r1, fp, #80	@,,
	ldr	r6, [r5, #64]	@ blocksize.568, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	r3, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	r6, r3	@ blocksize.568, stRbfIn.u32TotalDataSize
	bcs	.L116	@,
	cmp	r6, #0	@ blocksize.568,
	beq	.L116	@,
	ldr	r6, [fp, #-40]	@ status.Priority, status.Priority
	cmp	r6, #1	@ status.Priority,
	movne	r6, #1	@ AipBufDataFlag,
	movne	r8, #0	@ AipHiPriorityFlag,
	movne	r7, r6	@ AipLoPriorityFlag, AipBufDataFlag
	moveq	r7, #0	@ AipLoPriorityFlag,
	moveq	r8, r6	@ AipHiPriorityFlag, AipBufDataFlag
	b	.L119	@
.L178:
	mov	r0, #7	@,
	sub	r1, fp, #44	@,,
	bl	AIP_GetChnStatus	@
	ldr	r3, [fp, #-44]	@ status.CurnStatus, status.CurnStatus
	cmp	r3, #1	@ status.CurnStatus,
	beq	.L179	@,
	sub	r1, fp, #80	@,,
	mov	r0, #7	@,
	ldr	sl, [r5, #64]	@ blocksize, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	r1, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r1	@ blocksize, stRbfIn.u32TotalDataSize
	bcs	.L159	@,
	cmp	sl, #0	@ blocksize,
	beq	.L159	@,
	ldr	lr, [fp, #-40]	@ status.Priority, status.Priority
	orr	r6, r6, #128	@ AipBufDataFlag, AipBufDataFlag,
	cmp	lr, #1	@ status.Priority,
	orreq	r8, r8, #128	@ AipHiPriorityFlag, AipHiPriorityFlag,
	orrne	r7, r7, #128	@ AipLoPriorityFlag, AipLoPriorityFlag,
	b	.L159	@
.L177:
	mov	r0, #6	@,
	sub	r1, fp, #44	@,,
	bl	AIP_GetChnStatus	@
	ldr	sl, [fp, #-44]	@ status.CurnStatus, status.CurnStatus
	cmp	sl, #1	@ status.CurnStatus,
	beq	.L154	@,
	sub	r1, fp, #80	@,,
	mov	r0, #6	@,
	ldr	sl, [r5, #64]	@ blocksize.616, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	r1, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r1	@ blocksize.616, stRbfIn.u32TotalDataSize
	bcs	.L153	@,
	cmp	sl, #0	@ blocksize.616,
	beq	.L153	@,
	ldr	lr, [fp, #-40]	@ status.Priority, status.Priority
	orr	r6, r6, #64	@ AipBufDataFlag, AipBufDataFlag,
	cmp	lr, #1	@ status.Priority,
	orrne	r7, r7, #64	@ AipLoPriorityFlag, AipLoPriorityFlag,
	orreq	r8, r8, #64	@ AipHiPriorityFlag, AipHiPriorityFlag,
	b	.L153	@
.L176:
	sub	r1, fp, #44	@,,
	mov	r0, #5	@,
	bl	AIP_GetChnStatus	@
	ldr	r1, [fp, #-44]	@ status.CurnStatus, status.CurnStatus
	cmp	r1, #1	@ status.CurnStatus,
	beq	.L148	@,
	mov	r0, #5	@,
	sub	r1, fp, #80	@,,
	ldr	sl, [r5, #64]	@ blocksize.608, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	r2, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r2	@ blocksize.608, stRbfIn.u32TotalDataSize
	bcs	.L147	@,
	cmp	sl, #0	@ blocksize.608,
	beq	.L147	@,
	ldr	ip, [fp, #-40]	@ status.Priority, status.Priority
	orr	r6, r6, #32	@ AipBufDataFlag, AipBufDataFlag,
	cmp	ip, #1	@ status.Priority,
	orrne	r7, r7, #32	@ AipLoPriorityFlag, AipLoPriorityFlag,
	orreq	r8, r8, #32	@ AipHiPriorityFlag, AipHiPriorityFlag,
	b	.L147	@
.L175:
	mov	r0, #4	@,
	sub	r1, fp, #44	@,,
	bl	AIP_GetChnStatus	@
	ldr	ip, [fp, #-44]	@ status.CurnStatus, status.CurnStatus
	cmp	ip, #1	@ status.CurnStatus,
	beq	.L142	@,
	mov	r0, #4	@,
	sub	r1, fp, #80	@,,
	ldr	sl, [r5, #64]	@ blocksize.600, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	r3, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r3	@ blocksize.600, stRbfIn.u32TotalDataSize
	bcs	.L141	@,
	cmp	sl, #0	@ blocksize.600,
	beq	.L141	@,
	ldr	lr, [fp, #-40]	@ status.Priority, status.Priority
	orr	r6, r6, #16	@ AipBufDataFlag, AipBufDataFlag,
	cmp	lr, #1	@ status.Priority,
	orrne	r7, r7, #16	@ AipLoPriorityFlag, AipLoPriorityFlag,
	orreq	r8, r8, #16	@ AipHiPriorityFlag, AipHiPriorityFlag,
	b	.L141	@
.L174:
	mov	r0, #3	@,
	sub	r1, fp, #44	@,,
	bl	AIP_GetChnStatus	@
	ldr	sl, [fp, #-44]	@ status.CurnStatus, status.CurnStatus
	cmp	sl, #1	@ status.CurnStatus,
	beq	.L136	@,
	mov	r0, #3	@,
	sub	r1, fp, #80	@,,
	ldr	sl, [r5, #64]	@ blocksize.592, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	r3, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r3	@ blocksize.592, stRbfIn.u32TotalDataSize
	bcs	.L135	@,
	cmp	sl, #0	@ blocksize.592,
	beq	.L135	@,
	ldr	r0, [fp, #-40]	@ status.Priority, status.Priority
	orr	r6, r6, #8	@ AipBufDataFlag, AipBufDataFlag,
	cmp	r0, #1	@ status.Priority,
	orrne	r7, r7, #8	@ AipLoPriorityFlag, AipLoPriorityFlag,
	orreq	r8, r8, #8	@ AipHiPriorityFlag, AipHiPriorityFlag,
	b	.L135	@
.L173:
	mov	r0, #2	@,
	sub	r1, fp, #44	@,,
	bl	AIP_GetChnStatus	@
	ldr	r0, [fp, #-44]	@ status.CurnStatus, status.CurnStatus
	cmp	r0, #1	@ status.CurnStatus,
	beq	.L130	@,
	sub	r1, fp, #80	@,,
	mov	r0, #2	@,
	ldr	sl, [r5, #64]	@ blocksize.584, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	r1, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r1	@ blocksize.584, stRbfIn.u32TotalDataSize
	bcs	.L129	@,
	cmp	sl, #0	@ blocksize.584,
	beq	.L129	@,
	ldr	lr, [fp, #-40]	@ status.Priority, status.Priority
	orr	r6, r6, #4	@ AipBufDataFlag, AipBufDataFlag,
	cmp	lr, #1	@ status.Priority,
	orrne	r7, r7, #4	@ AipLoPriorityFlag, AipLoPriorityFlag,
	orreq	r8, r8, #4	@ AipHiPriorityFlag, AipHiPriorityFlag,
	b	.L129	@
.L172:
	sub	r1, fp, #44	@,,
	mov	r0, #1	@,
	bl	AIP_GetChnStatus	@
	ldr	r1, [fp, #-44]	@ status.CurnStatus, status.CurnStatus
	cmp	r1, #1	@ status.CurnStatus,
	beq	.L124	@,
	mov	r0, #1	@,
	sub	r1, fp, #80	@,,
	ldr	sl, [r5, #64]	@ blocksize.576, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	r2, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r2	@ blocksize.576, stRbfIn.u32TotalDataSize
	bcs	.L123	@,
	cmp	sl, #0	@ blocksize.576,
	beq	.L123	@,
	ldr	ip, [fp, #-40]	@ status.Priority, status.Priority
	orr	r6, r6, #2	@ AipBufDataFlag, AipBufDataFlag,
	cmp	ip, #1	@ status.Priority,
	orrne	r7, r7, #2	@ AipLoPriorityFlag, AipLoPriorityFlag,
	orreq	r8, r8, #2	@ AipHiPriorityFlag, AipHiPriorityFlag,
	b	.L123	@
.L179:
	ldr	sl, [fp, #-40]	@ status.Priority, status.Priority
	mov	r0, #7	@,
	sub	r1, fp, #80	@,,
	cmp	sl, #1	@ status.Priority,
	ldr	sl, [r5, #64]	@ blocksize, <variable>.BlockSize
	orreq	r8, r8, #128	@ AipHiPriorityFlag, AipHiPriorityFlag,
	orrne	r7, r7, #128	@ AipLoPriorityFlag, AipLoPriorityFlag,
	bl	AIP_QueryFiFoInfo	@
	ldr	r0, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r0	@ blocksize, stRbfIn.u32TotalDataSize
	bcs	.L159	@,
	cmp	sl, #0	@ blocksize,
	orrne	r6, r6, #128	@ AipBufDataFlag, AipBufDataFlag,
	b	.L159	@
.L117:
	ldr	r8, [fp, #-40]	@ status.Priority, status.Priority
	mov	r0, #0	@,
	sub	r1, fp, #80	@,,
	ldr	sl, [r5, #64]	@ blocksize.572, <variable>.BlockSize
	cmp	r8, #1	@ status.Priority,
	movne	r8, r0	@, AipHiPriorityFlag,
	moveq	r7, #0	@, AipLoPriorityFlag
	movne	r7, #1	@, AipLoPriorityFlag
	bl	AIP_QueryFiFoInfo	@
	ldr	r0, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r0	@ blocksize.572, stRbfIn.u32TotalDataSize
	bcs	.L121	@,
	cmp	sl, #0	@ blocksize.572,
	bne	.L119	@,
.L121:
	mov	r6, #0	@ AipBufDataFlag,
	b	.L119	@
.L148:
	ldr	r3, [fp, #-40]	@ status.Priority, status.Priority
	cmp	r3, #1	@ status.Priority,
	orrne	r7, r7, #32	@ AipLoPriorityFlag, AipLoPriorityFlag,
	beq	.L180	@,
.L152:
	mov	r0, #5	@,
	sub	r1, fp, #80	@,,
	ldr	sl, [r5, #64]	@ blocksize.612, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	r0, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r0	@ blocksize.612, stRbfIn.u32TotalDataSize
	bcs	.L147	@,
	cmp	sl, #0	@ blocksize.612,
	orrne	r6, r6, #32	@ AipBufDataFlag, AipBufDataFlag,
	b	.L147	@
.L154:
	ldr	r2, [fp, #-40]	@ status.Priority, status.Priority
	cmp	r2, #1	@ status.Priority,
	orrne	r7, r7, #64	@ AipLoPriorityFlag, AipLoPriorityFlag,
	beq	.L181	@,
.L158:
	mov	r0, #6	@,
	sub	r1, fp, #80	@,,
	ldr	sl, [r5, #64]	@ blocksize.620, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	ip, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, ip	@ blocksize.620, stRbfIn.u32TotalDataSize
	bcs	.L153	@,
	cmp	sl, #0	@ blocksize.620,
	orrne	r6, r6, #64	@ AipBufDataFlag, AipBufDataFlag,
	b	.L153	@
.L136:
	ldr	r1, [fp, #-40]	@ status.Priority, status.Priority
	cmp	r1, #1	@ status.Priority,
	orrne	r7, r7, #8	@ AipLoPriorityFlag, AipLoPriorityFlag,
	beq	.L182	@,
.L140:
	mov	r0, #3	@,
	sub	r1, fp, #80	@,,
	ldr	sl, [r5, #64]	@ blocksize.596, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	r2, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r2	@ blocksize.596, stRbfIn.u32TotalDataSize
	bcs	.L135	@,
	cmp	sl, #0	@ blocksize.596,
	orrne	r6, r6, #8	@ AipBufDataFlag, AipBufDataFlag,
	b	.L135	@
.L142:
	ldr	sl, [fp, #-40]	@ status.Priority, status.Priority
	cmp	sl, #1	@ status.Priority,
	orrne	r7, r7, #16	@ AipLoPriorityFlag, AipLoPriorityFlag,
	beq	.L183	@,
.L146:
	mov	r0, #4	@,
	sub	r1, fp, #80	@,,
	ldr	sl, [r5, #64]	@ blocksize.604, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	r0, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r0	@ blocksize.604, stRbfIn.u32TotalDataSize
	bcs	.L141	@,
	cmp	sl, #0	@ blocksize.604,
	orrne	r6, r6, #16	@ AipBufDataFlag, AipBufDataFlag,
	b	.L141	@
.L124:
	ldr	sl, [fp, #-40]	@ status.Priority, status.Priority
	cmp	sl, #1	@ status.Priority,
	orrne	r7, r7, #2	@ AipLoPriorityFlag, AipLoPriorityFlag,
	beq	.L184	@,
.L128:
	mov	r0, #1	@,
	sub	r1, fp, #80	@,,
	ldr	sl, [r5, #64]	@ blocksize.580, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	r3, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, r3	@ blocksize.580, stRbfIn.u32TotalDataSize
	bcs	.L123	@,
	cmp	sl, #0	@ blocksize.580,
	orrne	r6, r6, #2	@ AipBufDataFlag, AipBufDataFlag,
	b	.L123	@
.L130:
	ldr	r2, [fp, #-40]	@ status.Priority, status.Priority
	cmp	r2, #1	@ status.Priority,
	orrne	r7, r7, #4	@ AipLoPriorityFlag, AipLoPriorityFlag,
	beq	.L185	@,
.L134:
	mov	r0, #2	@,
	sub	r1, fp, #80	@,,
	ldr	sl, [r5, #64]	@ blocksize.588, <variable>.BlockSize
	bl	AIP_QueryFiFoInfo	@
	ldr	ip, [fp, #-60]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	cmp	sl, ip	@ blocksize.588, stRbfIn.u32TotalDataSize
	bcs	.L129	@,
	cmp	sl, #0	@ blocksize.588,
	orrne	r6, r6, #4	@ AipBufDataFlag, AipBufDataFlag,
	b	.L129	@
.L180:
	orr	r8, r8, #32	@ AipHiPriorityFlag, AipHiPriorityFlag,
	b	.L152	@
.L185:
	orr	r8, r8, #4	@ AipHiPriorityFlag, AipHiPriorityFlag,
	b	.L134	@
.L184:
	orr	r8, r8, #2	@ AipHiPriorityFlag, AipHiPriorityFlag,
	b	.L128	@
.L183:
	orr	r8, r8, #16	@ AipHiPriorityFlag, AipHiPriorityFlag,
	b	.L146	@
.L182:
	orr	r8, r8, #8	@ AipHiPriorityFlag, AipHiPriorityFlag,
	b	.L140	@
.L181:
	orr	r8, r8, #64	@ AipHiPriorityFlag, AipHiPriorityFlag,
	b	.L158	@
	.fnend
	.size	ENGINEUpdateChnAipState, .-ENGINEUpdateChnAipState
	.align	2
	.type	ENGINEOutFrame, %function
ENGINEOutFrame:
	.fnstart
.LFB867:
	@ args = 0, pretend = 0, frame = 240
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #244
	sub	sp, sp, #244	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r7, r0	@ state, state
	ldr	r0, [r0, #12]	@ <variable>.stAttr.u32DataFormat, <variable>.stAttr.u32DataFormat
	mov	sl, r1	@ pstFrame, pstFrame
	cmp	r0, #0	@ <variable>.stAttr.u32DataFormat,
	bne	.L187	@,
	ldr	r3, [r7, #56]	@ <variable>.AefMask, <variable>.AefMask
	cmp	r3, #0	@ <variable>.AefMask,
	beq	.L187	@,
	sub	r4, fp, #72	@ tmp200,,
	mov	r1, r4	@, tmp200
	bl	AOP_GetChnStatus	@
	ldr	r0, [fp, #-56]	@ AopStatus.bBypass, AopStatus.bBypass
	cmp	r0, #1	@ AopStatus.bBypass,
	beq	.L188	@,
	mov	r1, r4	@, tmp200
	mov	r0, #1	@,
	bl	AOP_GetChnStatus	@
	ldr	r1, [fp, #-56]	@ AopStatus.bBypass, AopStatus.bBypass
	cmp	r1, #1	@ AopStatus.bBypass,
	beq	.L188	@,
	mov	r0, #2	@,
	mov	r1, r4	@, tmp200
	bl	AOP_GetChnStatus	@
	ldr	r2, [fp, #-56]	@ AopStatus.bBypass, AopStatus.bBypass
	cmp	r2, #1	@ AopStatus.bBypass,
	beq	.L188	@,
	mov	r0, #3	@,
	mov	r1, r4	@, tmp200
	bl	AOP_GetChnStatus	@
	ldr	r5, [fp, #-56]	@ AopStatus.bBypass, AopStatus.bBypass
	cmp	r5, #1	@ AopStatus.bBypass,
	beq	.L188	@,
	mov	r0, #4	@,
	mov	r1, r4	@, tmp200
	bl	AOP_GetChnStatus	@
	ldr	r6, [fp, #-56]	@ AopStatus.bBypass, AopStatus.bBypass
	cmp	r6, #1	@ AopStatus.bBypass,
	beq	.L188	@,
	mov	r0, #5	@,
	mov	r1, r4	@, tmp200
	bl	AOP_GetChnStatus	@
	ldr	r8, [fp, #-56]	@ AopStatus.bBypass, AopStatus.bBypass
	cmp	r8, #1	@ AopStatus.bBypass,
	beq	.L188	@,
	mov	r0, #6	@,
	mov	r1, r4	@, tmp200
	bl	AOP_GetChnStatus	@
	ldr	r9, [fp, #-56]	@ AopStatus.bBypass, AopStatus.bBypass
	cmp	r9, #1	@ AopStatus.bBypass,
	beq	.L188	@,
	mov	r1, r4	@, tmp200
	mov	r0, #7	@,
	bl	AOP_GetChnStatus	@
	ldr	r4, [fp, #-56]	@ AopStatus.bBypass, AopStatus.bBypass
	cmp	r4, #1	@ AopStatus.bBypass,
	beq	.L188	@,
.L189:
	ldr	r3, [r7, #56]	@ <variable>.AefMask, <variable>.AefMask
	tst	r3, #1	@ <variable>.AefMask,
	bne	.L219	@,
.L190:
	tst	r3, #2	@ <variable>.AefMask,
	bne	.L220	@,
.L191:
	tst	r3, #4	@ <variable>.AefMask,
	bne	.L221	@,
.L192:
	tst	r3, #8	@ <variable>.AefMask,
	bne	.L222	@,
.L193:
	tst	r3, #16	@ <variable>.AefMask,
	bne	.L223	@,
.L194:
	tst	r3, #32	@ <variable>.AefMask,
	bne	.L224	@,
.L195:
	tst	r3, #64	@ <variable>.AefMask,
	bne	.L225	@,
.L196:
	tst	r3, #128	@ <variable>.AefMask,
	beq	.L187	@,
	mov	r9, sl	@ pstFrame.691, pstFrame
	sub	r6, fp, #220	@ tmp275,,
	ldmia	r9!, {r0, r1, r2, r3}	@ pstFrame.691,,,,
	mov	r5, r6	@ tmp354, tmp275
	stmia	r5!, {r0, r1, r2, r3}	@ tmp354,,,,
	ldmia	r9, {r0, r1, r2, r3}	@ pstFrame.691,,,,
	stmia	r5, {r0, r1, r2, r3}	@ tmp354,,,,
	bl	AOE_GetWKBuf	@
	mov	r1, sl	@, pstFrame
	mov	r2, r6	@, tmp275
	str	r0, [fp, #-220]	@, stTmpFrame.pDataBuf
	mov	r0, #7	@,
	bl	AFLT_ProcFrame	@
	ldmia	r6!, {r0, r1, r2, r3}	@ tmp279,,,,
	mov	ip, sl	@, pstFrame
	stmia	ip!, {r0, r1, r2, r3}	@,,,,
	ldmia	r5, {r0, r1, r2, r3}	@ tmp354,,,,
	stmia	r9, {r0, r1, r2, r3}	@ pstFrame.691,,,,
.L187:
	ldr	r6, [r7, #36]	@ prephitmp.644, <variable>.AopHiPriorityMask
	mov	r9, #0	@ ivtmp.686,
	ldr	r3, [r7, #40]	@ <variable>.AopLoPriorityMask, <variable>.AopLoPriorityMask
	mov	r8, r7	@ state, state
	sub	r2, fp, #124	@,,
	sub	r1, fp, #188	@,,
	sub	r0, fp, #156	@,,
	str	r2, [fp, #-276]	@, %sfp
	str	r1, [fp, #-280]	@, %sfp
	str	r0, [fp, #-272]	@, %sfp
	str	r6, [fp, #-52]	@ prephitmp.644, PriorityMaskTab
	str	r3, [fp, #-48]	@ <variable>.AopLoPriorityMask, PriorityMaskTab
.L212:
	mov	r4, #0	@ Aop,
	mov	r7, #1	@ tmp331,
	b	.L210	@
.L197:
	add	r4, r4, #1	@ Aop, Aop,
	cmp	r4, #8	@ Aop,
	beq	.L226	@,
.L210:
	mov	r5, r7, asl r4	@ D.15537, tmp331,
	tst	r5, r6	@ D.15537, prephitmp.644
	beq	.L197	@,
	mov	r0, r4	@, Aop
	bl	AOP_WriteBuffProcTryCnt	@
	mov	r0, r4	@, Aop
	bl	AOP_CheckIsCast	@
	cmp	r0, #0	@,
	bne	.L198	@,
.L216:
	ldr	r3, [r8, #52]	@ prephitmp.649, <variable>.AopBufFreeFlag
.L199:
	tst	r3, r5	@ prephitmp.649, D.15537
	bne	.L200	@,
	add	r4, r4, #1	@ Aop, Aop,
	cmp	r4, #8	@ Aop,
	bne	.L210	@,
.L226:
	add	r9, r9, #4	@ ivtmp.686, ivtmp.686,
	cmp	r9, #8	@ ivtmp.686,
	beq	.L213	@,
	sub	r7, fp, #52	@ tmp328,,
	ldr	r6, [r7, r9]	@ prephitmp.644, PriorityMaskTab
	b	.L212	@
.L198:
	sub	r0, fp, #156	@,,
	mov	r1, #32	@,
	bl	__memzero	@
	mov	lr, sl	@ pstFrame, pstFrame
	ldmia	lr!, {r0, r1, r2, r3}	@ pstFrame,,,,
	ldr	ip, [fp, #-272]	@ tmp284, %sfp
	stmia	ip!, {r0, r1, r2, r3}	@ tmp284,,,,
	ldmia	lr, {r0, r1, r2, r3}	@ pstFrame,,,,
	stmia	ip, {r0, r1, r2, r3}	@ tmp284,,,,
	bl	AOE_GetWKBuf	@
	str	r0, [fp, #-156]	@, stCastBakFrame.pDataBuf
	bl	AOE_ReleaseWKBuf	@
	ldr	r2, [sl, #8]	@, <variable>.u32DataBytes
	ldr	r1, [sl, #0]	@, <variable>.pDataBuf
	ldr	r0, [fp, #-156]	@, stCastBakFrame.pDataBuf
	bl	memcpy	@
	mov	r0, r4	@, Aop
	sub	r1, fp, #156	@,,
	bl	AOP_MutePcmData	@
	mov	r0, r4	@, Aop
	sub	r1, fp, #156	@,,
	bl	AOP_GainPcmData	@
	ldr	ip, [r8, #52]	@ <variable>.AopBufFreeFlag, <variable>.AopBufFreeFlag
	tst	r5, ip	@ D.15537, <variable>.AopBufFreeFlag
	beq	.L227	@,
.L200:
	mov	r0, r4	@, Aop
	bl	AOP_WriteBuffProcOKCnt	@
	mov	r0, r4	@, Aop
	sub	r1, fp, #72	@,,
	bl	AOP_GetChnStatus	@
	ldr	r2, [r8, #44]	@ <variable>.AopNoneUnifyMask, <variable>.AopNoneUnifyMask
	tst	r5, r2	@ D.15537, <variable>.AopNoneUnifyMask
	beq	.L204	@,
	mov	r0, r4	@, Aop
	bl	AOP_CheckIsCast	@
	cmp	r0, #0	@,
	bne	.L228	@,
	ldr	lr, [r8, #56]	@ <variable>.AefMask, <variable>.AefMask
	cmp	lr, #0	@ <variable>.AefMask,
	beq	.L206	@,
	ldr	r1, [fp, #-56]	@ AopStatus.bBypass, AopStatus.bBypass
	cmp	r1, #1	@ AopStatus.bBypass,
	beq	.L229	@,
.L206:
	mov	r0, r4	@, Aop
	ldr	r1, [sl, #0]	@, <variable>.pDataBuf
	ldr	r2, [sl, #8]	@, <variable>.u32DataBytes
	bl	AOP_WriteRbfData	@
	b	.L197	@
.L213:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L204:
	mov	r0, r4	@, Aop
	bl	AOP_CheckIsCast	@
	cmp	r0, #0	@,
	ldrne	lr, [fp, #-272]	@ tmp355, %sfp
	bne	.L217	@,
	ldr	r0, [r8, #56]	@ <variable>.AefMask, <variable>.AefMask
	cmp	r0, #0	@ <variable>.AefMask,
	beq	.L209	@,
	ldr	ip, [fp, #-56]	@ AopStatus.bBypass, AopStatus.bBypass
	cmp	ip, #1	@ AopStatus.bBypass,
	ldreq	lr, [fp, #-280]	@ tmp356, %sfp
	beq	.L217	@,
.L209:
	mov	lr, sl	@ pstFrame, pstFrame
.L217:
	ldmia	lr!, {r0, r1, r2, r3}	@ pstFrame,,,,
	ldr	ip, [fp, #-276]	@ tmp322, %sfp
	stmia	ip!, {r0, r1, r2, r3}	@ tmp322,,,,
	ldmia	lr, {r0, r1, r2, r3}	@ pstFrame,,,,
	stmia	ip, {r0, r1, r2, r3}	@ tmp322,,,,
	bl	AOE_GetWKBuf	@
	sub	r2, fp, #124	@,,
	mov	r1, r0	@ D.15587,
	ldr	r0, [fp, #-64]	@, AopStatus.u32BitPerSample
	bl	UTIL_UnifyBitDepthPcmData	@
	ldr	r1, [fp, #-124]	@, stUnfFrame.pDataBuf
	ldr	r2, [fp, #-116]	@, stUnfFrame.u32DataBytes
	mov	r0, r4	@, Aop
	bl	AOP_WriteRbfData	@
	bl	AOE_ReleaseWKBuf	@
	b	.L197	@
.L227:
	ldr	lr, [r8, #72]	@ SourceSamplePerFrame, <variable>.SamplePerFrame
	mov	r0, r4	@, Aop
	sub	r1, fp, #92	@,,
	str	lr, [fp, #-264]	@,
	bl	AOP_GetChnStatus	@
	ldr	ip, [fp, #-264]	@,
	mov	r0, r4	@, Aop
	ldr	r2, [fp, #-80]	@ status.uFrameSize, status.uFrameSize
	sub	r1, fp, #256	@,,
	mul	r3, r2, ip	@ blocksize, status.uFrameSize, SourceSamplePerFrame
	str	r3, [fp, #-264]	@,
	bl	AOP_QueryRbfInfo	@
	ldr	r0, [fp, #-228]	@ stRbfOut.u32TotalFreeSize, stRbfOut.u32TotalFreeSize
	ldr	r3, [fp, #-264]	@,
	cmp	r3, r0	@ blocksize, stRbfOut.u32TotalFreeSize
	bcs	.L216	@,
	ldr	ip, [fp, #-236]	@ stRbfOut.u32TotalDataSize, stRbfOut.u32TotalDataSize
	ldr	r0, [fp, #-224]	@ stRbfOut.u32LatencySize, stRbfOut.u32LatencySize
	add	r1, r3, ip	@ tmp300, blocksize, stRbfOut.u32TotalDataSize
	cmp	r1, r0	@ tmp300, stRbfOut.u32LatencySize
	bhi	.L216	@,
	cmp	r3, #0	@ blocksize,
	beq	.L216	@,
	ldr	r3, [r8, #52]	@ <variable>.AopBufFreeFlag, <variable>.AopBufFreeFlag
	orr	r3, r5, r3	@ prephitmp.649, D.15537, <variable>.AopBufFreeFlag
	str	r3, [r8, #52]	@ prephitmp.649, <variable>.AopBufFreeFlag
	b	.L199	@
.L228:
	mov	r0, r4	@, Aop
	ldr	r1, [fp, #-156]	@, stCastBakFrame.pDataBuf
	ldr	r2, [fp, #-148]	@, stCastBakFrame.u32DataBytes
	bl	AOP_WriteRbfData	@
	b	.L197	@
.L188:
	sub	r5, fp, #188	@ tmp216,,
	mov	r1, #32	@,
	mov	r0, r5	@, tmp216
	bl	__memzero	@
	mov	lr, sl	@ pstFrame, pstFrame
	ldmia	lr!, {r0, r1, r2, r3}	@ pstFrame,,,,
	mov	ip, r5	@ tmp217, tmp216
	stmia	ip!, {r0, r1, r2, r3}	@ tmp217,,,,
	ldmia	lr, {r0, r1, r2, r3}	@ pstFrame,,,,
	stmia	ip, {r0, r1, r2, r3}	@ tmp217,,,,
	bl	AOE_GetBakBuf	@
	ldr	r1, [sl, #0]	@, <variable>.pDataBuf
	ldr	r2, [sl, #8]	@, <variable>.u32DataBytes
	str	r0, [fp, #-188]	@, stBakFrame.pDataBuf
	bl	memcpy	@
	b	.L189	@
.L225:
	mov	r9, sl	@ pstFrame.743, pstFrame
	sub	r8, fp, #220	@ tmp268,,
	ldmia	r9!, {r0, r1, r2, r3}	@ pstFrame.743,,,,
	mov	r6, r8	@ tmp353, tmp268
	mov	r4, sl	@, pstFrame
	stmia	r6!, {r0, r1, r2, r3}	@ tmp353,,,,
	ldmia	r9, {r0, r1, r2, r3}	@ pstFrame.743,,,,
	stmia	r6, {r0, r1, r2, r3}	@ tmp353,,,,
	bl	AOE_GetWKBuf	@
	mov	r1, sl	@, pstFrame
	mov	r2, r8	@, tmp268
	str	r0, [fp, #-220]	@, stTmpFrame.pDataBuf
	mov	r0, #6	@,
	bl	AFLT_ProcFrame	@
	ldmia	r8!, {r0, r1, r2, r3}	@ tmp272,,,,
	stmia	r4!, {r0, r1, r2, r3}	@,,,,
	ldmia	r6, {r0, r1, r2, r3}	@ tmp353,,,,
	stmia	r9, {r0, r1, r2, r3}	@ pstFrame.743,,,,
	ldr	r3, [r7, #56]	@ <variable>.AefMask, <variable>.AefMask
	b	.L196	@
.L224:
	mov	r6, sl	@ pstFrame.738, pstFrame
	sub	r5, fp, #220	@ tmp261,,
	ldmia	r6!, {r0, r1, r2, r3}	@ pstFrame.738,,,,
	mov	r8, r5	@ tmp352, tmp261
	stmia	r8!, {r0, r1, r2, r3}	@ tmp352,,,,
	ldmia	r6, {r0, r1, r2, r3}	@ pstFrame.738,,,,
	stmia	r8, {r0, r1, r2, r3}	@ tmp352,,,,
	bl	AOE_GetWKBuf	@
	mov	r1, sl	@, pstFrame
	mov	r2, r5	@, tmp261
	str	r0, [fp, #-220]	@, stTmpFrame.pDataBuf
	mov	r0, #5	@,
	bl	AFLT_ProcFrame	@
	ldmia	r5!, {r0, r1, r2, r3}	@ tmp265,,,,
	mov	ip, sl	@, pstFrame
	stmia	ip!, {r0, r1, r2, r3}	@,,,,
	ldmia	r8, {r0, r1, r2, r3}	@ tmp352,,,,
	stmia	r6, {r0, r1, r2, r3}	@ pstFrame.738,,,,
	ldr	r3, [r7, #56]	@ <variable>.AefMask, <variable>.AefMask
	b	.L195	@
.L223:
	mov	r8, sl	@ pstFrame.733, pstFrame
	sub	r9, fp, #220	@ tmp254,,
	ldmia	r8!, {r0, r1, r2, r3}	@ pstFrame.733,,,,
	mov	r5, r9	@ tmp351, tmp254
	mov	r4, sl	@, pstFrame
	stmia	r5!, {r0, r1, r2, r3}	@ tmp351,,,,
	ldmia	r8, {r0, r1, r2, r3}	@ pstFrame.733,,,,
	stmia	r5, {r0, r1, r2, r3}	@ tmp351,,,,
	bl	AOE_GetWKBuf	@
	mov	r1, sl	@, pstFrame
	mov	r2, r9	@, tmp254
	str	r0, [fp, #-220]	@, stTmpFrame.pDataBuf
	mov	r0, #4	@,
	bl	AFLT_ProcFrame	@
	ldmia	r9!, {r0, r1, r2, r3}	@ tmp258,,,,
	stmia	r4!, {r0, r1, r2, r3}	@,,,,
	ldmia	r5, {r0, r1, r2, r3}	@ tmp351,,,,
	stmia	r8, {r0, r1, r2, r3}	@ pstFrame.733,,,,
	ldr	r3, [r7, #56]	@ <variable>.AefMask, <variable>.AefMask
	b	.L194	@
.L222:
	mov	r8, sl	@ pstFrame.728, pstFrame
	sub	r6, fp, #220	@ tmp247,,
	ldmia	r8!, {r0, r1, r2, r3}	@ pstFrame.728,,,,
	mov	r9, r6	@ tmp350, tmp247
	stmia	r9!, {r0, r1, r2, r3}	@ tmp350,,,,
	ldmia	r8, {r0, r1, r2, r3}	@ pstFrame.728,,,,
	stmia	r9, {r0, r1, r2, r3}	@ tmp350,,,,
	bl	AOE_GetWKBuf	@
	mov	r1, sl	@, pstFrame
	mov	r2, r6	@, tmp247
	str	r0, [fp, #-220]	@, stTmpFrame.pDataBuf
	mov	r0, #3	@,
	bl	AFLT_ProcFrame	@
	ldmia	r6!, {r0, r1, r2, r3}	@ tmp251,,,,
	mov	ip, sl	@, pstFrame
	stmia	ip!, {r0, r1, r2, r3}	@,,,,
	ldmia	r9, {r0, r1, r2, r3}	@ tmp350,,,,
	stmia	r8, {r0, r1, r2, r3}	@ pstFrame.728,,,,
	ldr	r3, [r7, #56]	@ <variable>.AefMask, <variable>.AefMask
	b	.L193	@
.L221:
	mov	r9, sl	@ pstFrame.723, pstFrame
	sub	r5, fp, #220	@ tmp240,,
	ldmia	r9!, {r0, r1, r2, r3}	@ pstFrame.723,,,,
	mov	r6, r5	@ tmp349, tmp240
	mov	r4, sl	@, pstFrame
	stmia	r6!, {r0, r1, r2, r3}	@ tmp349,,,,
	ldmia	r9, {r0, r1, r2, r3}	@ pstFrame.723,,,,
	stmia	r6, {r0, r1, r2, r3}	@ tmp349,,,,
	bl	AOE_GetWKBuf	@
	mov	r1, sl	@, pstFrame
	mov	r2, r5	@, tmp240
	str	r0, [fp, #-220]	@, stTmpFrame.pDataBuf
	mov	r0, #2	@,
	bl	AFLT_ProcFrame	@
	ldmia	r5!, {r0, r1, r2, r3}	@ tmp244,,,,
	stmia	r4!, {r0, r1, r2, r3}	@,,,,
	ldmia	r6, {r0, r1, r2, r3}	@ tmp349,,,,
	stmia	r9, {r0, r1, r2, r3}	@ pstFrame.723,,,,
	ldr	r3, [r7, #56]	@ <variable>.AefMask, <variable>.AefMask
	b	.L192	@
.L220:
	mov	r6, sl	@ pstFrame.718, pstFrame
	sub	r8, fp, #220	@ tmp233,,
	ldmia	r6!, {r0, r1, r2, r3}	@ pstFrame.718,,,,
	mov	r5, r8	@ tmp348, tmp233
	stmia	r5!, {r0, r1, r2, r3}	@ tmp348,,,,
	ldmia	r6, {r0, r1, r2, r3}	@ pstFrame.718,,,,
	stmia	r5, {r0, r1, r2, r3}	@ tmp348,,,,
	bl	AOE_GetWKBuf	@
	mov	r1, sl	@, pstFrame
	mov	r2, r8	@, tmp233
	str	r0, [fp, #-220]	@, stTmpFrame.pDataBuf
	mov	r0, #1	@,
	bl	AFLT_ProcFrame	@
	ldmia	r8!, {r0, r1, r2, r3}	@ tmp237,,,,
	mov	ip, sl	@, pstFrame
	stmia	ip!, {r0, r1, r2, r3}	@,,,,
	ldmia	r5, {r0, r1, r2, r3}	@ tmp348,,,,
	stmia	r6, {r0, r1, r2, r3}	@ pstFrame.718,,,,
	ldr	r3, [r7, #56]	@ <variable>.AefMask, <variable>.AefMask
	b	.L191	@
.L219:
	mov	r6, sl	@ pstFrame.713, pstFrame
	sub	r4, fp, #220	@ tmp226,,
	ldmia	r6!, {r0, r1, r2, r3}	@ pstFrame.713,,,,
	mov	r8, r4	@ tmp347, tmp226
	mov	r9, sl	@, pstFrame
	stmia	r8!, {r0, r1, r2, r3}	@ tmp347,,,,
	ldmia	r6, {r0, r1, r2, r3}	@ pstFrame.713,,,,
	stmia	r8, {r0, r1, r2, r3}	@ tmp347,,,,
	bl	AOE_GetWKBuf	@
	mov	r1, sl	@, pstFrame
	mov	r2, r4	@, tmp226
	str	r0, [fp, #-220]	@, stTmpFrame.pDataBuf
	mov	r0, #0	@,
	bl	AFLT_ProcFrame	@
	ldmia	r4!, {r0, r1, r2, r3}	@ tmp230,,,,
	stmia	r9!, {r0, r1, r2, r3}	@,,,,
	ldmia	r8, {r0, r1, r2, r3}	@ tmp347,,,,
	stmia	r6, {r0, r1, r2, r3}	@ pstFrame.713,,,,
	ldr	r3, [r7, #56]	@ <variable>.AefMask, <variable>.AefMask
	b	.L190	@
.L229:
	mov	r0, r4	@, Aop
	ldr	r1, [fp, #-188]	@, stBakFrame.pDataBuf
	ldr	r2, [fp, #-180]	@, stBakFrame.u32DataBytes
	bl	AOP_WriteRbfData	@
	b	.L197	@
	.fnend
	.size	ENGINEOutFrame, .-ENGINEOutFrame
	.global	__aeabi_uidiv
	.align	2
	.global	ENGINEProcChnData
	.type	ENGINEProcChnData, %function
ENGINEProcChnData:
	.fnstart
.LFB870:
	@ args = 0, pretend = 0, frame = 88
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #92
	sub	sp, sp, #92	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r4, r0	@ state, state
	mov	r2, #34	@,
	ldr	r1, [r4, #60]	@, <variable>.EngineId
	mov	r0, #2	@,
	bl	TRACE_AOE_FSM	@
	ldr	r2, [r4, #52]	@ BufFreeFlag, <variable>.AopBufFreeFlag
	ldr	r3, [r4, #36]	@ D.15978, <variable>.AopHiPriorityMask
	cmp	r2, #0	@ BufFreeFlag,
	ldr	r1, [r4, #40]	@ D.15977, <variable>.AopLoPriorityMask
	beq	.L330	@,
	cmp	r3, #0	@ D.15978,
	moveq	r0, r3	@ Flag, D.15978
	bne	.L358	@,
.L233:
	cmp	r1, #0	@ D.15977,
	beq	.L244	@,
	tst	r1, #1	@ D.15977,
	beq	.L245	@,
	tst	r2, #1	@ BufFreeFlag,
	beq	.L246	@,
	orr	r0, r0, #2	@ Flag, Flag,
.L245:
	tst	r1, #2	@ D.15977,
	beq	.L247	@,
	tst	r2, #2	@ BufFreeFlag,
	beq	.L246	@,
	orr	r0, r0, #2	@ Flag, Flag,
.L247:
	tst	r1, #4	@ D.15977,
	beq	.L248	@,
	tst	r2, #4	@ BufFreeFlag,
	beq	.L246	@,
	orr	r0, r0, #2	@ Flag, Flag,
.L248:
	tst	r1, #8	@ D.15977,
	beq	.L249	@,
	tst	r2, #8	@ BufFreeFlag,
	beq	.L246	@,
	orr	r0, r0, #2	@ Flag, Flag,
.L249:
	tst	r1, #16	@ D.15977,
	beq	.L250	@,
	tst	r2, #16	@ BufFreeFlag,
	beq	.L246	@,
	orr	r0, r0, #2	@ Flag, Flag,
.L250:
	tst	r1, #32	@ D.15977,
	beq	.L251	@,
	tst	r2, #32	@ BufFreeFlag,
	beq	.L246	@,
	orr	r0, r0, #2	@ Flag, Flag,
.L251:
	tst	r1, #64	@ D.15977,
	beq	.L252	@,
	tst	r2, #64	@ BufFreeFlag,
	beq	.L246	@,
	orr	r0, r0, #2	@ Flag, Flag,
.L252:
	tst	r1, #128	@ D.15977,
	beq	.L244	@,
	tst	r2, #128	@ BufFreeFlag,
	orrne	r0, r0, #2	@ Flag, Flag,
	beq	.L246	@,
.L244:
	cmp	r3, #0	@ D.15978,
	beq	.L253	@,
	tst	r0, #1	@ Flag,
	beq	.L330	@,
.L254:
	ldr	r2, [r4, #20]	@ D.16001, <variable>.AipHiPriorityMask
	ldr	r0, [r4, #24]	@ D.16000, <variable>.AipLoPriorityMask
	cmp	r2, #0	@ D.16001,
	ldr	r3, [r4, #28]	@ BufFreeFlag, <variable>.AipBufDataFlag
	beq	.L255	@,
	cmp	r0, #0	@ D.16000,
	beq	.L255	@,
	ands	r1, r2, #1	@ tmp201, D.16001,
	beq	.L257	@,
	ands	r1, r3, #1	@ tmp202, BufFreeFlag,
	beq	.L260	@,
	mov	r1, #1	@ Flag,
.L257:
	tst	r2, #2	@ D.16001,
	beq	.L259	@,
	tst	r3, #2	@ BufFreeFlag,
	beq	.L260	@,
	mov	r1, #1	@ Flag,
.L259:
	tst	r2, #4	@ D.16001,
	beq	.L261	@,
	tst	r3, #4	@ BufFreeFlag,
	beq	.L260	@,
	mov	r1, #1	@ Flag,
.L261:
	tst	r2, #8	@ D.16001,
	beq	.L262	@,
	tst	r3, #8	@ BufFreeFlag,
	beq	.L260	@,
	mov	r1, #1	@ Flag,
.L262:
	tst	r2, #16	@ D.16001,
	beq	.L263	@,
	tst	r3, #16	@ BufFreeFlag,
	beq	.L260	@,
	mov	r1, #1	@ Flag,
.L263:
	tst	r2, #32	@ D.16001,
	beq	.L264	@,
	tst	r3, #32	@ BufFreeFlag,
	beq	.L260	@,
	mov	r1, #1	@ Flag,
.L264:
	tst	r2, #64	@ D.16001,
	beq	.L265	@,
	tst	r3, #64	@ BufFreeFlag,
	beq	.L260	@,
	mov	r1, #1	@ Flag,
.L265:
	tst	r2, #128	@ D.16001,
	beq	.L266	@,
	tst	r3, #128	@ BufFreeFlag,
	movne	r1, #1	@ Flag,
	beq	.L260	@,
.L266:
	tst	r0, #1	@ D.16000,
	beq	.L267	@,
	tst	r3, #1	@ BufFreeFlag,
	beq	.L268	@,
	orr	r1, r1, #2	@ Flag, Flag,
.L267:
	tst	r0, #2	@ D.16000,
	beq	.L269	@,
	tst	r3, #2	@ BufFreeFlag,
	beq	.L268	@,
	orr	r1, r1, #2	@ Flag, Flag,
.L269:
	tst	r0, #4	@ D.16000,
	beq	.L270	@,
	tst	r3, #4	@ BufFreeFlag,
	beq	.L268	@,
	orr	r1, r1, #2	@ Flag, Flag,
.L270:
	tst	r0, #8	@ D.16000,
	beq	.L271	@,
	tst	r3, #8	@ BufFreeFlag,
	beq	.L268	@,
	orr	r1, r1, #2	@ Flag, Flag,
.L271:
	tst	r0, #16	@ D.16000,
	beq	.L272	@,
	tst	r3, #16	@ BufFreeFlag,
	beq	.L268	@,
	orr	r1, r1, #2	@ Flag, Flag,
.L272:
	tst	r0, #32	@ D.16000,
	beq	.L273	@,
	tst	r3, #32	@ BufFreeFlag,
	beq	.L268	@,
	orr	r1, r1, #2	@ Flag, Flag,
.L273:
	tst	r0, #64	@ D.16000,
	beq	.L274	@,
	tst	r3, #64	@ BufFreeFlag,
	beq	.L268	@,
	orr	r1, r1, #2	@ Flag, Flag,
.L274:
	tst	r0, #128	@ D.16000,
	beq	.L275	@,
	tst	r3, #128	@ BufFreeFlag,
	orrne	r1, r1, #2	@ Flag, Flag,
	beq	.L268	@,
.L275:
	tst	r1, #1	@ Flag,
	bne	.L276	@,
.L330:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L358:
	ands	r0, r3, #1	@ tmp167, D.15978,
	beq	.L235	@,
	ands	r0, r2, #1	@ tmp168, BufFreeFlag,
	beq	.L238	@,
	mov	r0, #1	@ Flag,
.L235:
	tst	r3, #2	@ D.15978,
	beq	.L237	@,
	tst	r2, #2	@ BufFreeFlag,
	beq	.L238	@,
	mov	r0, #1	@ Flag,
.L237:
	tst	r3, #4	@ D.15978,
	beq	.L239	@,
	tst	r2, #4	@ BufFreeFlag,
	beq	.L238	@,
	mov	r0, #1	@ Flag,
.L239:
	tst	r3, #8	@ D.15978,
	beq	.L240	@,
	tst	r2, #8	@ BufFreeFlag,
	beq	.L238	@,
	mov	r0, #1	@ Flag,
.L240:
	tst	r3, #16	@ D.15978,
	beq	.L241	@,
	tst	r2, #16	@ BufFreeFlag,
	beq	.L238	@,
	mov	r0, #1	@ Flag,
.L241:
	tst	r3, #32	@ D.15978,
	beq	.L242	@,
	tst	r2, #32	@ BufFreeFlag,
	beq	.L238	@,
	mov	r0, #1	@ Flag,
.L242:
	tst	r3, #64	@ D.15978,
	beq	.L243	@,
	tst	r2, #64	@ BufFreeFlag,
	beq	.L238	@,
	mov	r0, #1	@ Flag,
.L243:
	tst	r3, #128	@ D.15978,
	beq	.L233	@,
	tst	r2, #128	@ BufFreeFlag,
	movne	r0, #1	@ Flag,
	bne	.L233	@,
.L238:
	bic	r0, r0, #1	@ Flag, Flag,
	b	.L233	@
.L253:
	cmp	r1, #0	@ D.15977,
	beq	.L330	@,
	tst	r0, #2	@ Flag,
	bne	.L254	@,
	b	.L330	@
.L255:
	cmp	r3, #0	@ BufFreeFlag,
	beq	.L330	@,
.L276:
	bl	AOE_FlushWKBuf	@
	mov	r2, #35	@,
	mov	r0, #2	@,
	ldr	r1, [r4, #60]	@, <variable>.EngineId
	bl	TRACE_AOE_FSM	@
	mov	r1, #32	@,
	sub	r0, fp, #84	@,,
	ldr	r9, [r4, #4]	@ Ch, <variable>.stAttr.u32Channels
	ldr	sl, [r4, #0]	@ BitDepth, <variable>.stAttr.u32BitPerSample
	bl	__memzero	@
	bl	AOE_GetWKBuf	@
	mov	r7, r0	@ pDataBuf,
	bl	AOE_GetWKBufSize	@
	subs	r1, r0, #0	@ __n,
	beq	.L277	@,
	mov	r0, r7	@, pDataBuf
	bl	__memzero	@
.L277:
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	tst	r3, #1	@ <variable>.AipMask,
	bne	.L359	@,
.L278:
	mov	r5, #0	@ u32UnderFlag,
	mov	r6, r5	@ MixCnt, u32UnderFlag
.L280:
	tst	r3, #2	@ <variable>.AipMask,
	bne	.L360	@,
.L284:
	tst	r3, #4	@ <variable>.AipMask,
	bne	.L361	@,
.L289:
	tst	r3, #8	@ <variable>.AipMask,
	bne	.L362	@,
.L294:
	tst	r3, #16	@ <variable>.AipMask,
	bne	.L363	@,
.L299:
	tst	r3, #32	@ <variable>.AipMask,
	bne	.L364	@,
.L304:
	tst	r3, #64	@ <variable>.AipMask,
	bne	.L365	@,
.L309:
	tst	r3, #128	@ <variable>.AipMask,
	bne	.L366	@,
.L314:
	cmp	r6, #0	@ MixCnt,
	ldreq	r3, [fp, #-72]	@ prephitmp.777, stFrame.u32SamplesPerFrame
	beq	.L319	@,
	tst	r5, #1	@ u32UnderFlag,
	bne	.L367	@,
.L320:
	tst	r5, #2	@ u32UnderFlag,
	bne	.L368	@,
.L321:
	tst	r5, #4	@ u32UnderFlag,
	bne	.L369	@,
.L322:
	tst	r5, #8	@ u32UnderFlag,
	bne	.L370	@,
.L323:
	tst	r5, #16	@ u32UnderFlag,
	bne	.L371	@,
.L324:
	tst	r5, #32	@ u32UnderFlag,
	bne	.L372	@,
.L325:
	tst	r5, #64	@ u32UnderFlag,
	bne	.L373	@,
.L326:
	tst	r5, #128	@ u32UnderFlag,
	bne	.L374	@,
.L327:
	ldr	lr, [r4, #64]	@ <variable>.BlockSize, <variable>.BlockSize
	ldr	r3, [r4, #72]	@ prephitmp.777, <variable>.SamplePerFrame
	ldmia	r4, {r0, ip}	@ phole ldm
	ldr	r1, [r4, #8]	@ <variable>.stAttr.u32SampleRate, <variable>.stAttr.u32SampleRate
	ldr	r2, [r4, #12]	@ <variable>.stAttr.u32DataFormat, <variable>.stAttr.u32DataFormat
	str	r7, [fp, #-84]	@ pDataBuf, stFrame.pDataBuf
	str	lr, [fp, #-76]	@ <variable>.BlockSize, stFrame.u32DataBytes
	str	ip, [fp, #-64]	@ <variable>.stAttr.u32Channels, stFrame.u32Channels
	str	r0, [fp, #-68]	@ <variable>.stAttr.u32BitPerSample, stFrame.u32BitPerSample
	str	r1, [fp, #-60]	@ <variable>.stAttr.u32SampleRate, stFrame.u32SampleRate
	str	r2, [fp, #-56]	@ <variable>.stAttr.u32DataFormat, stFrame.u32DataFormat
	str	r3, [fp, #-72]	@ prephitmp.777, stFrame.u32SamplesPerFrame
.L319:
	cmp	r3, #0	@ prephitmp.777,
	bne	.L375	@,
	bl	AOE_FlushWKBuf	@
	b	.L330	@
.L375:
	mov	r2, #36	@,
	ldr	r1, [r4, #60]	@, <variable>.EngineId
	mov	r0, #2	@,
	bl	TRACE_AOE_FSM	@
	mov	r0, r4	@, state
	sub	r1, fp, #84	@,,
	bl	ENGINEOutFrame	@
	ldr	r1, [r4, #60]	@, <variable>.EngineId
	mov	r0, #2	@,
	mov	r2, #32	@,
	bl	TRACE_AOE_FSM	@
	bl	AOE_FlushWKBuf	@
	b	.L330	@
.L366:
	mov	r0, #7	@,
	sub	r1, fp, #120	@,,
	bl	AIP_QueryFiFoInfo	@
	ldr	r0, [r4, #64]	@ D.16601, <variable>.BlockSize
	ldr	r2, [fp, #-100]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	ldr	ip, [fp, #-104]	@ TailBytes, stRbfIn.u32ContiguousDataSize
	cmp	r2, r0	@ stRbfIn.u32TotalDataSize, D.16601
	bls	.L315	@,
	cmp	ip, r0	@ TailBytes, D.16601
	bcs	.L316	@,
	ldr	lr, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	add	r3, r7, ip	@, pDataBuf, TailBytes
	ldr	r8, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	mov	r0, ip	@, TailBytes
	str	r3, [fp, #-128]	@, %sfp
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, r8, lr	@ tmp464, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	str	ip, [fp, #-132]	@,
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp464
	mul	r2, r9, r0	@ tmp471, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	ldr	ip, [fp, #-132]	@,
	ldr	r0, [r4, #64]	@ <variable>.BlockSize, <variable>.BlockSize
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	rsb	r0, ip, r0	@, TailBytes, <variable>.BlockSize
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	ldr	r1, [fp, #-120]	@, stRbfIn.u32BasePtr
	mul	r2, r9, r0	@ tmp480, Ch,
	ldr	r0, [fp, #-128]	@, %sfp
	bl	UTIL_MixerPro	@
.L317:
	mov	r0, #7	@,
	ldr	r1, [r4, #64]	@, <variable>.BlockSize
	bl	AIP_ReadFiFoComplete	@
	add	r6, r6, #1	@ MixCnt, MixCnt,
	b	.L314	@
.L359:
	mov	r0, #0	@,
	sub	r1, fp, #120	@,,
	bl	AIP_QueryFiFoInfo	@
	ldr	r0, [r4, #64]	@ temp.862, <variable>.BlockSize
	ldr	r3, [fp, #-100]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	ldr	r6, [fp, #-104]	@ TailBytes.860, stRbfIn.u32ContiguousDataSize
	cmp	r3, r0	@ stRbfIn.u32TotalDataSize, temp.862
	bls	.L376	@,
	cmp	r6, r0	@ TailBytes.860, temp.862
	bcs	.L377	@,
	ldr	lr, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	mov	r0, r6	@, TailBytes.860
	ldr	ip, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	add	r8, r7, r6	@ tmp259, pDataBuf, TailBytes.860
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r5, ip, lr	@ tmp251, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r5	@, tmp251
	mul	r2, r9, r0	@ tmp258, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	ldr	r0, [r4, #64]	@ <variable>.BlockSize, <variable>.BlockSize
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	rsb	r0, r6, r0	@, TailBytes.860, <variable>.BlockSize
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	ldr	r1, [fp, #-120]	@, stRbfIn.u32BasePtr
	mul	r2, r9, r0	@ tmp267, Ch,
	mov	r0, r8	@, tmp259
	bl	UTIL_MixerPro	@
.L283:
	mov	r0, #0	@,
	ldr	r1, [r4, #64]	@, <variable>.BlockSize
	bl	AIP_ReadFiFoComplete	@
	mov	r5, #0	@ u32UnderFlag,
	mov	r6, #1	@ MixCnt,
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	b	.L280	@
.L361:
	mov	r0, #2	@,
	sub	r1, fp, #120	@,,
	bl	AIP_QueryFiFoInfo	@
	ldr	r0, [r4, #64]	@ temp.921, <variable>.BlockSize
	ldr	r2, [fp, #-100]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	ldr	ip, [fp, #-104]	@ TailBytes.919, stRbfIn.u32ContiguousDataSize
	cmp	r2, r0	@ stRbfIn.u32TotalDataSize, temp.921
	bls	.L378	@,
	cmp	ip, r0	@ TailBytes.919, temp.921
	bcs	.L379	@,
	ldr	r3, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	add	r1, r7, ip	@, pDataBuf, TailBytes.919
	ldr	lr, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	mov	r0, ip	@, TailBytes.919
	str	r1, [fp, #-128]	@, %sfp
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, lr, r3	@ tmp315, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	str	ip, [fp, #-132]	@,
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp315
	mul	r2, r9, r0	@ tmp322, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	ldr	r3, [r4, #64]	@ <variable>.BlockSize, <variable>.BlockSize
	ldr	r2, [fp, #-132]	@,
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	rsb	r0, r2, r3	@, TailBytes.919, <variable>.BlockSize
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	ldr	r1, [fp, #-120]	@, stRbfIn.u32BasePtr
	mul	r2, r9, r0	@ tmp331, Ch,
	ldr	r0, [fp, #-128]	@, %sfp
	bl	UTIL_MixerPro	@
.L293:
	mov	r0, #2	@,
	ldr	r1, [r4, #64]	@, <variable>.BlockSize
	bl	AIP_ReadFiFoComplete	@
	add	r6, r6, #1	@ MixCnt, MixCnt,
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	b	.L289	@
.L360:
	mov	r0, #1	@,
	sub	r1, fp, #120	@,,
	bl	AIP_QueryFiFoInfo	@
	ldr	r0, [r4, #64]	@ temp.891, <variable>.BlockSize
	ldr	r1, [fp, #-100]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	ldr	ip, [fp, #-104]	@ TailBytes.889, stRbfIn.u32ContiguousDataSize
	cmp	r1, r0	@ stRbfIn.u32TotalDataSize, temp.891
	bls	.L380	@,
	cmp	ip, r0	@ TailBytes.889, temp.891
	bcs	.L381	@,
	ldr	r3, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	add	r1, r7, ip	@, pDataBuf, TailBytes.889
	ldr	lr, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	mov	r0, ip	@, TailBytes.889
	str	r1, [fp, #-128]	@, %sfp
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, lr, r3	@ tmp283, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	str	ip, [fp, #-132]	@,
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp283
	mul	r2, r9, r0	@ tmp290, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	ldr	ip, [fp, #-132]	@,
	ldr	r0, [r4, #64]	@ <variable>.BlockSize, <variable>.BlockSize
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	rsb	r0, ip, r0	@, TailBytes.889, <variable>.BlockSize
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	ldr	r1, [fp, #-120]	@, stRbfIn.u32BasePtr
	mul	r2, r9, r0	@ tmp299, Ch,
	ldr	r0, [fp, #-128]	@, %sfp
	bl	UTIL_MixerPro	@
.L288:
	mov	r0, #1	@,
	ldr	r1, [r4, #64]	@, <variable>.BlockSize
	bl	AIP_ReadFiFoComplete	@
	add	r6, r6, #1	@ MixCnt, MixCnt,
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	b	.L284	@
.L365:
	mov	r0, #6	@,
	sub	r1, fp, #120	@,,
	bl	AIP_QueryFiFoInfo	@
	ldr	r0, [r4, #64]	@ temp.1044, <variable>.BlockSize
	ldr	r2, [fp, #-100]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	ldr	ip, [fp, #-104]	@ TailBytes.1042, stRbfIn.u32ContiguousDataSize
	cmp	r2, r0	@ stRbfIn.u32TotalDataSize, temp.1044
	bls	.L382	@,
	cmp	ip, r0	@ TailBytes.1042, temp.1044
	bcs	.L383	@,
	ldr	r3, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	add	r1, r7, ip	@, pDataBuf, TailBytes.1042
	ldr	lr, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	mov	r0, ip	@, TailBytes.1042
	str	r1, [fp, #-128]	@, %sfp
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, lr, r3	@ tmp443, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	str	ip, [fp, #-132]	@,
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp443
	mul	r2, r9, r0	@ tmp450, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	ldr	r3, [r4, #64]	@ <variable>.BlockSize, <variable>.BlockSize
	ldr	r2, [fp, #-132]	@,
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	rsb	r0, r2, r3	@, TailBytes.1042, <variable>.BlockSize
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	ldr	r1, [fp, #-120]	@, stRbfIn.u32BasePtr
	mul	r2, r9, r0	@ tmp459, Ch,
	ldr	r0, [fp, #-128]	@, %sfp
	bl	UTIL_MixerPro	@
.L313:
	mov	r0, #6	@,
	ldr	r1, [r4, #64]	@, <variable>.BlockSize
	bl	AIP_ReadFiFoComplete	@
	add	r6, r6, #1	@ MixCnt, MixCnt,
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	b	.L309	@
.L364:
	mov	r0, #5	@,
	sub	r1, fp, #120	@,,
	bl	AIP_QueryFiFoInfo	@
	ldr	r0, [r4, #64]	@ temp.1013, <variable>.BlockSize
	ldr	r2, [fp, #-100]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	ldr	ip, [fp, #-104]	@ TailBytes.1011, stRbfIn.u32ContiguousDataSize
	cmp	r2, r0	@ stRbfIn.u32TotalDataSize, temp.1013
	bls	.L384	@,
	cmp	ip, r0	@ TailBytes.1011, temp.1013
	bcs	.L385	@,
	ldr	r3, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	add	r1, r7, ip	@, pDataBuf, TailBytes.1011
	ldr	lr, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	mov	r0, ip	@, TailBytes.1011
	str	r1, [fp, #-128]	@, %sfp
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, lr, r3	@ tmp411, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	str	ip, [fp, #-132]	@,
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp411
	mul	r2, r9, r0	@ tmp418, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	ldr	r3, [r4, #64]	@ <variable>.BlockSize, <variable>.BlockSize
	ldr	r2, [fp, #-132]	@,
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	rsb	r0, r2, r3	@, TailBytes.1011, <variable>.BlockSize
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	ldr	r1, [fp, #-120]	@, stRbfIn.u32BasePtr
	mul	r2, r9, r0	@ tmp427, Ch,
	ldr	r0, [fp, #-128]	@, %sfp
	bl	UTIL_MixerPro	@
.L308:
	mov	r0, #5	@,
	ldr	r1, [r4, #64]	@, <variable>.BlockSize
	bl	AIP_ReadFiFoComplete	@
	add	r6, r6, #1	@ MixCnt, MixCnt,
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	b	.L304	@
.L363:
	mov	r0, #4	@,
	sub	r1, fp, #120	@,,
	bl	AIP_QueryFiFoInfo	@
	ldr	r0, [r4, #64]	@ temp.982, <variable>.BlockSize
	ldr	r2, [fp, #-100]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	ldr	ip, [fp, #-104]	@ TailBytes.980, stRbfIn.u32ContiguousDataSize
	cmp	r2, r0	@ stRbfIn.u32TotalDataSize, temp.982
	bls	.L386	@,
	cmp	ip, r0	@ TailBytes.980, temp.982
	bcs	.L387	@,
	ldr	r3, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	add	r1, r7, ip	@, pDataBuf, TailBytes.980
	ldr	lr, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	mov	r0, ip	@, TailBytes.980
	str	r1, [fp, #-128]	@, %sfp
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, lr, r3	@ tmp379, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	str	ip, [fp, #-132]	@,
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp379
	mul	r2, r9, r0	@ tmp386, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	ldr	r3, [r4, #64]	@ <variable>.BlockSize, <variable>.BlockSize
	ldr	r2, [fp, #-132]	@,
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	rsb	r0, r2, r3	@, TailBytes.980, <variable>.BlockSize
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	ldr	r1, [fp, #-120]	@, stRbfIn.u32BasePtr
	mul	r2, r9, r0	@ tmp395, Ch,
	ldr	r0, [fp, #-128]	@, %sfp
	bl	UTIL_MixerPro	@
.L303:
	mov	r0, #4	@,
	ldr	r1, [r4, #64]	@, <variable>.BlockSize
	bl	AIP_ReadFiFoComplete	@
	add	r6, r6, #1	@ MixCnt, MixCnt,
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	b	.L299	@
.L362:
	mov	r0, #3	@,
	sub	r1, fp, #120	@,,
	bl	AIP_QueryFiFoInfo	@
	ldr	r0, [r4, #64]	@ temp.951, <variable>.BlockSize
	ldr	r2, [fp, #-100]	@ stRbfIn.u32TotalDataSize, stRbfIn.u32TotalDataSize
	ldr	ip, [fp, #-104]	@ TailBytes.949, stRbfIn.u32ContiguousDataSize
	cmp	r2, r0	@ stRbfIn.u32TotalDataSize, temp.951
	bls	.L388	@,
	cmp	ip, r0	@ TailBytes.949, temp.951
	bcs	.L389	@,
	ldr	r3, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	add	r1, r7, ip	@, pDataBuf, TailBytes.949
	ldr	lr, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	mov	r0, ip	@, TailBytes.949
	str	r1, [fp, #-128]	@, %sfp
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, lr, r3	@ tmp347, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	str	ip, [fp, #-132]	@,
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp347
	mul	r2, r9, r0	@ tmp354, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	ldr	r3, [r4, #64]	@ <variable>.BlockSize, <variable>.BlockSize
	ldr	r2, [fp, #-132]	@,
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	rsb	r0, r2, r3	@, TailBytes.949, <variable>.BlockSize
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	ldr	r1, [fp, #-120]	@, stRbfIn.u32BasePtr
	mul	r2, r9, r0	@ tmp363, Ch,
	ldr	r0, [fp, #-128]	@, %sfp
	bl	UTIL_MixerPro	@
.L298:
	mov	r0, #3	@,
	ldr	r1, [r4, #64]	@, <variable>.BlockSize
	bl	AIP_ReadFiFoComplete	@
	add	r6, r6, #1	@ MixCnt, MixCnt,
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	b	.L294	@
.L315:
	mov	r0, #7	@,
	sub	r1, fp, #52	@,,
	bl	AIP_GetChnStatus	@
	ldr	r3, [fp, #-52]	@ stChnStatus.CurnStatus, stChnStatus.CurnStatus
	cmp	r3, #1	@ stChnStatus.CurnStatus,
	orreq	r5, r5, #128	@ u32UnderFlag, u32UnderFlag,
	b	.L314	@
.L382:
	mov	r0, #6	@,
	sub	r1, fp, #52	@,,
	bl	AIP_GetChnStatus	@
	ldr	r0, [fp, #-52]	@ stChnStatus.CurnStatus, stChnStatus.CurnStatus
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	cmp	r0, #1	@ stChnStatus.CurnStatus,
	orreq	r5, r5, #64	@ u32UnderFlag, u32UnderFlag,
	b	.L309	@
.L380:
	mov	r0, #1	@,
	sub	r1, fp, #52	@,,
	bl	AIP_GetChnStatus	@
	ldr	r3, [fp, #-52]	@ stChnStatus.CurnStatus, stChnStatus.CurnStatus
	cmp	r3, #1	@ stChnStatus.CurnStatus,
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	orreq	r5, r5, #2	@ u32UnderFlag, u32UnderFlag,
	b	.L284	@
.L378:
	mov	r0, #2	@,
	sub	r1, fp, #52	@,,
	bl	AIP_GetChnStatus	@
	ldr	r0, [fp, #-52]	@ stChnStatus.CurnStatus, stChnStatus.CurnStatus
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	cmp	r0, #1	@ stChnStatus.CurnStatus,
	orreq	r5, r5, #4	@ u32UnderFlag, u32UnderFlag,
	b	.L289	@
.L376:
	mov	r0, #0	@,
	sub	r1, fp, #52	@,,
	bl	AIP_GetChnStatus	@
	ldr	r5, [fp, #-52]	@ stChnStatus.CurnStatus, stChnStatus.CurnStatus
	cmp	r5, #1	@ stChnStatus.CurnStatus,
	ldrne	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	bne	.L278	@,
	mov	r6, #0	@ MixCnt,
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	b	.L280	@
.L384:
	mov	r0, #5	@,
	sub	r1, fp, #52	@,,
	bl	AIP_GetChnStatus	@
	ldr	r0, [fp, #-52]	@ stChnStatus.CurnStatus, stChnStatus.CurnStatus
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	cmp	r0, #1	@ stChnStatus.CurnStatus,
	orreq	r5, r5, #32	@ u32UnderFlag, u32UnderFlag,
	b	.L304	@
.L386:
	mov	r0, #4	@,
	sub	r1, fp, #52	@,,
	bl	AIP_GetChnStatus	@
	ldr	r0, [fp, #-52]	@ stChnStatus.CurnStatus, stChnStatus.CurnStatus
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	cmp	r0, #1	@ stChnStatus.CurnStatus,
	orreq	r5, r5, #16	@ u32UnderFlag, u32UnderFlag,
	b	.L299	@
.L388:
	mov	r0, #3	@,
	sub	r1, fp, #52	@,,
	bl	AIP_GetChnStatus	@
	ldr	r0, [fp, #-52]	@ stChnStatus.CurnStatus, stChnStatus.CurnStatus
	ldr	r3, [r4, #16]	@ <variable>.AipMask, <variable>.AipMask
	cmp	r0, #1	@ stChnStatus.CurnStatus,
	orreq	r5, r5, #8	@ u32UnderFlag, u32UnderFlag,
	b	.L294	@
.L246:
	bic	r0, r0, #2	@ Flag, Flag,
	b	.L244	@
.L260:
	bic	r1, r1, #1	@ Flag, Flag,
	b	.L266	@
.L367:
	mov	r0, #0	@,
	bl	AIP_UnderFlowCalc	@
	b	.L320	@
.L369:
	mov	r0, #2	@,
	bl	AIP_UnderFlowCalc	@
	b	.L322	@
.L368:
	mov	r0, #1	@,
	bl	AIP_UnderFlowCalc	@
	b	.L321	@
.L374:
	mov	r0, #7	@,
	bl	AIP_UnderFlowCalc	@
	b	.L327	@
.L373:
	mov	r0, #6	@,
	bl	AIP_UnderFlowCalc	@
	b	.L326	@
.L372:
	mov	r0, #5	@,
	bl	AIP_UnderFlowCalc	@
	b	.L325	@
.L371:
	mov	r0, #4	@,
	bl	AIP_UnderFlowCalc	@
	b	.L324	@
.L370:
	mov	r0, #3	@,
	bl	AIP_UnderFlowCalc	@
	b	.L323	@
.L379:
	ldr	ip, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	ldr	r8, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, r8, ip	@ tmp307, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp307
	mul	r2, r9, r0	@ tmp314, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	b	.L293	@
.L381:
	ldr	r2, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	ldr	r8, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, r8, r2	@ tmp275, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp275
	mul	r2, r9, r0	@ tmp282, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	b	.L288	@
.L385:
	ldr	ip, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	ldr	r8, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, r8, ip	@ tmp403, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp403
	mul	r2, r9, r0	@ tmp410, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	b	.L308	@
.L387:
	ldr	ip, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	ldr	r8, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, r8, ip	@ tmp371, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp371
	mul	r2, r9, r0	@ tmp378, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	b	.L303	@
.L316:
	ldr	r2, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	ldr	ip, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, r2, ip	@ tmp481, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp481
	mul	r2, r9, r0	@ tmp488, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	b	.L317	@
.L377:
	ldr	r2, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	ldr	r6, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r5, r2, r6	@ tmp243, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r5	@, tmp243
	mul	r2, r9, r0	@ tmp250, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	b	.L283	@
.L383:
	ldr	ip, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	ldr	r8, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, r8, ip	@ tmp435, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp435
	mul	r2, r9, r0	@ tmp442, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	b	.L313	@
.L389:
	ldr	ip, [fp, #-116]	@ stRbfIn.u32ReadPtr, stRbfIn.u32ReadPtr
	ldr	r8, [fp, #-120]	@ stRbfIn.u32BasePtr, stRbfIn.u32BasePtr
	ldr	r1, [r4, #68]	@, <variable>.FrameSize
	add	r8, r8, ip	@ tmp339, stRbfIn.u32BasePtr, stRbfIn.u32ReadPtr
	bl	__aeabi_uidiv	@
	mov	r3, sl	@, BitDepth
	mov	r1, r8	@, tmp339
	mul	r2, r9, r0	@ tmp346, Ch,
	mov	r0, r7	@, pDataBuf
	bl	UTIL_MixerPro	@
	b	.L298	@
.L268:
	bic	r1, r1, #2	@ Flag, Flag,
	b	.L275	@
	.fnend
	.size	ENGINEProcChnData, .-ENGINEProcChnData
	.align	2
	.global	ENGINEDestroyChn
	.type	ENGINEDestroyChn, %function
ENGINEDestroyChn:
	.fnstart
.LFB862:
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
	subs	r1, r0, #0	@ inst, inst
	ldmeqfd	sp, {fp, sp, pc}	@
	mov	r0, #17	@,
	bl	HI_ADSP_FREE	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	ENGINEDestroyChn, .-ENGINEDestroyChn
	.align	2
	.global	ENGINE_DeInit
	.type	ENGINE_DeInit, %function
ENGINE_DeInit:
	.fnstart
.LFB882:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp133,
	movt	r4, #:upper16:.LANCHOR0	@ tmp133,
	mov	r5, #0	@ tmp136,
	ldr	r0, [r4, #24]	@, g_stEneRm.hEne
	bl	ENGINEDestroyChn	@
	ldr	r0, [r4, #28]	@, g_stEneRm.hEne
	str	r5, [r4, #24]	@ tmp136, g_stEneRm.hEne
	bl	ENGINEDestroyChn	@
	ldr	r0, [r4, #32]	@, g_stEneRm.hEne
	str	r5, [r4, #28]	@ tmp136, g_stEneRm.hEne
	bl	ENGINEDestroyChn	@
	ldr	r0, [r4, #36]	@, g_stEneRm.hEne
	str	r5, [r4, #32]	@ tmp136, g_stEneRm.hEne
	bl	ENGINEDestroyChn	@
	ldr	r0, [r4, #40]	@, g_stEneRm.hEne
	str	r5, [r4, #36]	@ tmp136, g_stEneRm.hEne
	bl	ENGINEDestroyChn	@
	ldr	r0, [r4, #44]	@, g_stEneRm.hEne
	str	r5, [r4, #40]	@ tmp136, g_stEneRm.hEne
	bl	ENGINEDestroyChn	@
	str	r5, [r4, #44]	@ tmp136, g_stEneRm.hEne
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	ENGINE_DeInit, .-ENGINE_DeInit
	.align	2
	.global	ENGINECreateChn
	.type	ENGINECreateChn, %function
ENGINECreateChn:
	.fnstart
.LFB861:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #20
	sub	sp, sp, #20	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r3, #:lower16:.LANCHOR0	@ tmp152,
	movt	r3, #:upper16:.LANCHOR0	@ tmp152,
	sub	r6, fp, #44	@ tmp153,,
	mov	r1, #16	@,
	mov	r5, r0	@ Id, Id
	ldr	r4, [r3, r0, asl #2]	@ pEneReg, g_stEneRm.hwEneReg
	mov	r0, r6	@, tmp153
	bl	__memzero	@
	mov	r0, r6	@, tmp153
	ldr	r1, [r4, #0]	@ tmp154,* pEneReg
	and	r1, r1, #3	@, tmp154,
	bl	AOE_REG_ReadBitDepth	@
	cmp	r0, #0	@,
	beq	.L406	@,
.L396:
	mov	r6, #0	@ D.15324,
.L401:
	mov	r0, r6	@, D.15324
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L406:
	ldr	r2, [r4, #0]	@ tmp157,* pEneReg
	add	r0, r6, #4	@, tmp153,
	ubfx	r1, r2, #2, #2	@, tmp157,,
	bl	AOE_REG_ReadChannel	@
	cmp	r0, #0	@,
	bne	.L396	@,
	ldr	ip, [r4, #0]	@ tmp161,* pEneReg
	add	r0, r6, #8	@, tmp153,
	ubfx	r1, ip, #4, #4	@, tmp161,,
	bl	AOE_REG_ReadSampelRate	@
	cmp	r0, #0	@,
	bne	.L396	@,
	ldr	lr, [r4, #0]	@ tmp165,* pEneReg
	add	r0, r6, #12	@, tmp153,
	ubfx	r1, lr, #8, #2	@, tmp165,,
	bl	AOE_REG_ReadDataFormat	@
	cmp	r0, #0	@,
	bne	.L396	@,
	mov	r0, #17	@,
	mov	r1, #80	@,
	bl	HI_ADSP_MALLOC	@
	subs	r4, r0, #0	@ state,
	beq	.L396	@,
	mov	r1, #80	@,
	bl	__memzero	@
	ldmia	r6, {r0, r1, r2, r3}	@ tmp153,,,,
	mov	ip, r0	@ <variable>.stAttr.u32BitPerSample,
	stmia	r4, {r0, r1, r2, r3}	@ state,,,,
	mov	r0, r1	@,
	mov	r1, ip	@, <variable>.stAttr.u32BitPerSample
	bl	UTIL_CalcFrameSize	@
	ldr	r3, [r4, #8]	@ <variable>.stAttr.u32SampleRate, <variable>.stAttr.u32SampleRate
	movw	ip, #:lower16:274877907	@ tmp178,
	movt	ip, #:upper16:274877907	@ tmp178,
	add	r6, r3, r3, asl #2	@, tmp176, <variable>.stAttr.u32SampleRate, <variable>.stAttr.u32SampleRate,
	umull	r3, r2, ip, r6	@, tmp177, tmp178, tmp176
	mov	r1, r2, lsr #6	@ samples, tmp177,
	tst	r1, #255	@ samples
	movne	r1, r2, lsr #14	@ tmp180, tmp177,
	addne	r1, r1, #1	@ D.16010, tmp180,
	movne	r1, r1, asl #8	@ samples, D.16010,
	tst	r1, #3	@ samples,
	addne	r1, r1, #3	@ tmp182, samples,
	bicne	r1, r1, #3	@ samples, tmp182,
	mul	r6, r0, r1	@ tmp183, framesize, samples
	ldr	r0, [r4, #4]	@, <variable>.stAttr.u32Channels
	ldr	r1, [r4, #0]	@, <variable>.stAttr.u32BitPerSample
	str	r6, [r4, #64]	@ tmp183, <variable>.BlockSize
	bl	UTIL_CalcFrameSize	@
	cmp	r0, #0	@ D.15337,
	mov	r6, r0	@ D.15337,
	str	r0, [r4, #68]	@ D.15337, <variable>.FrameSize
	beq	.L400	@,
	mov	r1, r0	@, D.15337
	ldr	r0, [r4, #64]	@, <variable>.BlockSize
	bl	__aeabi_uidiv	@
	mov	r6, r4	@ D.15324, state
	mov	r1, #1	@ tmp189,
	str	r5, [r4, #60]	@ Id, <variable>.EngineId
	str	r1, [r4, #76]	@ tmp189, <variable>.CurStatus
	str	r0, [r4, #72]	@, <variable>.SamplePerFrame
	b	.L401	@
.L400:
	mov	r1, r4	@, state
	mov	r0, #17	@,
	bl	HI_ADSP_FREE	@
	b	.L401	@
	.fnend
	.size	ENGINECreateChn, .-ENGINECreateChn
	.align	2
	.global	ENGINEProcChnStartCmd
	.type	ENGINEProcChnStartCmd, %function
ENGINEProcChnStartCmd:
	.fnstart
.LFB872:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r3, r4, r5, r6, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, r5, r6, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r4, #:lower16:.LANCHOR0	@ tmp170,
	add	r6, r0, #6	@ tmp145, Id,
	movt	r4, #:upper16:.LANCHOR0	@ tmp170,
	mov	r5, r0	@ Id, Id
	ldr	r3, [r4, r6, asl #2]	@ state, g_stEneRm.hEne
	cmp	r3, #0	@ state,
	beq	.L418	@,
	ldr	r2, [r3, #76]	@ <variable>.CurStatus, <variable>.CurStatus
	cmp	r2, #0	@ <variable>.CurStatus,
	beq	.L419	@,
.L412:
	mov	r0, #1	@ tmp164,
	str	r0, [r3, #76]	@ tmp164, <variable>.CurStatus
.L411:
	ldr	r3, [r4, r5, asl #2]	@ pEneReg, g_stEneRm.hwEneReg
	ldr	r1, [r3, #4]	@ D.16037,
	ands	r2, r1, #8	@ tmp166, D.16037,
	ldmnefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	ldr	r0, [r3, #4]	@ tmp167,
	bfi	r0, r2, #4, #4	@ tmp167, tmp166,,
	str	r0, [r3, #4]	@ tmp167,
	ldr	r2, [r3, #4]	@ tmp168,
	orr	ip, r2, #8	@ tmp173, tmp168,
	str	ip, [r3, #4]	@ tmp173,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L419:
	mov	r0, r3	@, state
	bl	ENGINEDestroyChn	@
	mov	r0, r5	@, Id
	bl	ENGINECreateChn	@
	cmp	r0, #0	@ D.15727,
	str	r0, [r4, r6, asl #2]	@ D.15727, g_stEneRm.hEne
	movne	r3, r0	@ state, D.15727
	bne	.L412	@,
.L417:
	ldr	r3, [r4, r5, asl #2]	@ pEneReg, g_stEneRm.hwEneReg
	ldr	r0, [r3, #4]	@ D.16030,
	tst	r0, #8	@ D.16030,
	ldmnefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	ldr	lr, [r3, #4]	@ tmp160,
	mov	r2, #3	@ tmp161,
	bfi	lr, r2, #4, #4	@ tmp160, tmp161,,
	str	lr, [r3, #4]	@ tmp160,
	ldr	ip, [r3, #4]	@ tmp162,
	orr	r1, ip, #8	@ tmp172, tmp162,
	str	r1, [r3, #4]	@ tmp172,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L418:
	bl	ENGINECreateChn	@
	cmp	r0, #0	@ D.15720,
	str	r0, [r4, r6, asl #2]	@ D.15720, g_stEneRm.hEne
	movne	r3, #1	@ tmp154,
	strne	r3, [r0, #76]	@ tmp154, <variable>.CurStatus
	bne	.L411	@,
	b	.L417	@
	.fnend
	.size	ENGINEProcChnStartCmd, .-ENGINEProcChnStartCmd
	.align	2
	.global	ENGINEProcChnCmd
	.type	ENGINEProcChnCmd, %function
ENGINEProcChnCmd:
	.fnstart
.LFB873:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp139,
	movt	r3, #:upper16:.LANCHOR0	@ tmp139,
	mov	ip, r0	@ Id, Id
	ldr	r2, [r3, r0, asl #2]	@ pEneReg, g_stEneRm.hwEneReg
	ldr	r1, [r2, #4]	@ D.16046,
	ands	r1, r1, #8	@ tmp140, D.16046,
	ldmnefd	sp, {r3, r4, fp, sp, pc}	@
	ldr	r4, [r2, #4]	@ tmp141,
	ands	r4, r4, #3	@ D.16044, tmp141,
	bne	.L427	@,
	bl	ENGINEProcChnStartCmd	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L427:
	cmp	r4, #1	@ D.16044,
	beq	.L424	@,
	ldr	ip, [r2, #4]	@ tmp143,
	mov	r1, #4	@ tmp144,
	bfi	ip, r1, #4, #4	@ tmp143, tmp144,,
	str	ip, [r2, #4]	@ tmp143,
	ldr	r0, [r2, #4]	@ tmp145,
	orr	r3, r0, #8	@ tmp156, tmp145,
	str	r3, [r2, #4]	@ tmp156,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L424:
	add	r0, r0, #6	@ tmp148, Id,
	ldr	r0, [r3, r0, asl #2]	@ state, g_stEneRm.hEne
	cmp	r0, #0	@ state,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	ldr	r4, [r0, #76]	@ <variable>.CurStatus, <variable>.CurStatus
	cmp	r4, #1	@ <variable>.CurStatus,
	streq	r1, [r0, #76]	@ tmp140, <variable>.CurStatus
	ldreq	r2, [r3, ip, asl #2]	@ pEneReg, g_stEneRm.hwEneReg
	ldr	r3, [r2, #4]	@ D.16055,
	ands	r3, r3, #8	@ tmp152, D.16055,
	ldmnefd	sp, {r3, r4, fp, sp, pc}	@
	ldr	r0, [r2, #4]	@ tmp153,
	bfi	r0, r3, #4, #4	@ tmp153, tmp152,,
	str	r0, [r2, #4]	@ tmp153,
	ldr	r1, [r2, #4]	@ tmp154,
	orr	ip, r1, #8	@ tmp157, tmp154,
	str	ip, [r2, #4]	@ tmp157,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	ENGINEProcChnCmd, .-ENGINEProcChnCmd
	.align	2
	.global	ENGINEProcChn
	.type	ENGINEProcChn, %function
ENGINEProcChn:
	.fnstart
.LFB878:
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
	mov	r2, #33	@,
	mov	r4, r0	@ Id, Id
	mov	r1, r0	@, Id
	mov	r0, #2	@,
	bl	TRACE_AOE_FSM	@
	mov	r0, r4	@, Id
	bl	ENGINEProcChnCmd	@
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	add	r2, r4, #6	@ tmp141, Id,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r5, [r3, r2, asl #2]	@ state, g_stEneRm.hEne
	cmp	r5, #0	@ state,
	beq	.L429	@,
	ldr	r0, [r5, #76]	@ <variable>.CurStatus, <variable>.CurStatus
	cmp	r0, #1	@ <variable>.CurStatus,
	beq	.L431	@,
.L429:
	mov	r0, #0	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L431:
	ldr	r4, [r3, r4, asl #2]	@ pEneReg, g_stEneRm.hwEneReg
	mov	r0, r5	@, state
	ldrh	r1, [r4, #12]	@ <variable>.ENGINE_ROU_DST.bits.aop_buf_ena, <variable>.ENGINE_ROU_DST.bits.aop_buf_ena
	bl	ENGINEUpdateChnAopState	@
	ldrh	r1, [r4, #8]	@ <variable>.ENGINE_MIX_SRC.bits.aip_fifo_ena, <variable>.ENGINE_MIX_SRC.bits.aip_fifo_ena
	mov	r0, r5	@, state
	bl	ENGINEUpdateChnAipState	@
	ldrh	r3, [r4, #28]	@ <variable>.ENGINE_ATT_AEF.bits.aef_att_ena, <variable>.ENGINE_ATT_AEF.bits.aef_att_ena
	mov	r0, r5	@, state
	str	r3, [r5, #56]	@ <variable>.ENGINE_ATT_AEF.bits.aef_att_ena, <variable>.AefMask
	bl	ENGINEProcChnData	@
	mov	r0, #0	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	ENGINEProcChn, .-ENGINEProcChn
	.align	2
	.global	ENGINE_Process
	.type	ENGINE_Process, %function
ENGINE_Process:
	.fnstart
.LFB880:
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
	mov	r0, #0	@,
	bl	ENGINEProcChn	@
	mov	r0, #1	@,
	bl	ENGINEProcChn	@
	mov	r0, #2	@,
	bl	ENGINEProcChn	@
	mov	r0, #3	@,
	bl	ENGINEProcChn	@
	mov	r0, #4	@,
	bl	ENGINEProcChn	@
	mov	r0, #5	@,
	bl	ENGINEProcChn	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	ENGINE_Process, .-ENGINE_Process
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_stEneRm, %object
	.size	g_stEneRm, 48
g_stEneRm:
	.space	48
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
