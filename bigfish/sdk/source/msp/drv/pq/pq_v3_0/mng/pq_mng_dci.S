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
	.file	"pq_mng_dci.c"
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
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0
@ -Idrivers/msp/pq/pq_v3_0
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/mach-hi3798mx/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/api/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/drv/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/api/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/api/pq/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/api/higo/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/pq/pq_v3_0/mng
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/pq/pq_v3_0/hal/hi3798mv100
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/pq/pq_v3_0/hal/common
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/pq/pq_v3_0
@ -imultilib armv7a_soft -iprefix
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/
@ -isysroot /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../target
@ -D__KERNEL__ -D__LINUX_ARM_ARCH__=7 -Uarm -DCHIP_TYPE_hi3796mv100
@ -DSDK_VERSION=HiSTBAndroidV600R001C00SPC060_v2015040918 -DHI_MCE_SUPPORT
@ -DHI_GPIOI2C_SUPPORT -DHI_LOG_SUPPORT=1 -DHI_LOG_LEVEL=4
@ -DHI_PROC_SUPPORT=1 -DHI_HDMI_SUPPORT_1_4 -DHI_KEYLED_SUPPORT
@ -DHI_HDCP_SUPPORT -DHI_SCI_SUPPORT -DHI_PVR_SUPPORT -DHI_VI_SUPPORT
@ -DHI_VENC_SUPPORT -DHI_AENC_SUPPORT -DHI_PQ_V3_0 -DKBUILD_STR(s)=#s
@ -DKBUILD_BASENAME=KBUILD_STR(pq_mng_dci)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/mng/.pq_mng_dci.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/mng/pq_mng_dci.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/mng/pq_mng_dci.o -O2 -Wall -Wundef
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
	.global	PQ_MNG_GetDCIEnable
	.type	PQ_MNG_GetDCIEnable, %function
PQ_MNG_GetDCIEnable:
	.fnstart
.LFB847:
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
	movw	r1, #:lower16:.LANCHOR0	@ tmp135,
	movt	r1, #:upper16:.LANCHOR0	@ tmp135,
	ldr	r3, [r1, #0]	@ bDciEn, bDciEn
	str	r3, [r0, #0]	@ bDciEn,* pu32OnOff
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_GetDCIEnable, .-PQ_MNG_GetDCIEnable
	.align	2
	.global	PQ_MNG_GetDCILevelGain
	.type	PQ_MNG_GetDCILevelGain, %function
PQ_MNG_GetDCILevelGain:
	.fnstart
.LFB852:
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
	movw	r1, #:lower16:.LANCHOR0	@ tmp135,
	movt	r1, #:upper16:.LANCHOR0	@ tmp135,
	ldr	r3, [r1, #4]	@ sg_u32DCILevel, sg_u32DCILevel
	str	r3, [r0, #0]	@ sg_u32DCILevel,* pu32DCILevelGain
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_GetDCILevelGain, .-PQ_MNG_GetDCILevelGain
	.align	2
	.global	PQ_MNG_UpdateDCIWin
	.type	PQ_MNG_UpdateDCIWin, %function
PQ_MNG_UpdateDCIWin:
	.fnstart
.LFB854:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {fp, ip, lr, pc}	@,
	.pad #4
	.save {fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	lr, r0	@ pstWin, pstWin
	ldrh	ip, [lr, #6]	@ <variable>.u16VEnd, <variable>.u16VEnd
	mov	r0, #0	@,
	ldrh	r1, [lr, #0]	@ <variable>.u16HStar, <variable>.u16HStar
	ldrh	r2, [lr, #2]	@ <variable>.u16HEnd, <variable>.u16HEnd
	ldrh	r3, [lr, #4]	@ <variable>.u16VStar, <variable>.u16VStar
	str	ip, [sp, #0]	@ <variable>.u16VEnd,
	bl	PQ_HAL_SetDCIWindow	@
	mov	r0, #0	@,
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
	.fnend
	.size	PQ_MNG_UpdateDCIWin, .-PQ_MNG_UpdateDCIWin
	.align	2
	.type	PQ_MNG_FindDciGain, %function
PQ_MNG_FindDciGain:
	.fnstart
.LFB849:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	ip, #:lower16:.LANCHOR1	@ tmp206,
	movt	ip, #:upper16:.LANCHOR1	@ tmp206,
	ldr	ip, [ip, #0]	@ sg_pstPqParam.322, sg_pstPqParam
	cmp	ip, #0	@ sg_pstPqParam.322,
	beq	.L20	@,
	add	r5, ip, #37888	@ ivtmp.445, sg_pstPqParam.322,
	movw	r4, #:lower16:-120831700	@ tmp214,
	add	ip, r5, #244	@ ivtmp.445, ivtmp.445,
	movt	r4, #:upper16:-120831700	@ tmp214,
	mov	r8, #0	@ i,
.L11:
	ldr	r6, [ip, #-12]	@ <variable>.u32RegAddr, <variable>.u32RegAddr
	ldr	r5, [ip, #0]	@ u32Value, <variable>.u32Value
	cmp	r6, r4	@ <variable>.u32RegAddr, tmp214
	ldrb	r7, [ip, #-7]	@ zero_extendqisi2	@ u8Msb, <variable>.u8Msb
	ldrb	r6, [ip, #-8]	@ zero_extendqisi2	@ u8Lsb, <variable>.u8Lsb
	ldrb	sl, [ip, #-6]	@ zero_extendqisi2	@ u8SourceMode, <variable>.u8SourceMode
	bne	.L10	@,
	cmp	r6, r1	@ u8Lsb, u8GainLsb
	bne	.L10	@,
	cmp	r7, r2	@ u8Msb, uGain8Msb
	bne	.L10	@,
	cmp	sl, r3	@ u8SourceMode, u32InMode
	bne	.L10	@,
.L17:
	str	r5, [r0, #0]	@ u32Value,* pu32Value
	mov	r0, #0	@ D.26843,
.L9:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L10:
	add	r6, ip, #16	@ tmp216, ivtmp.445,
	ldr	r5, [ip, #16]	@ u32Value, <variable>.u32Value
	add	r8, r8, #1	@ tmp215, i,
	ldr	sl, [r6, #-12]	@ <variable>.u32RegAddr, <variable>.u32RegAddr
	ldrb	r7, [r6, #-8]	@ zero_extendqisi2	@ u8Lsb, <variable>.u8Lsb
	cmp	sl, r4	@ <variable>.u32RegAddr, tmp214
	ldrb	ip, [r6, #-7]	@ zero_extendqisi2	@ u8Msb, <variable>.u8Msb
	ldrb	sl, [r6, #-6]	@ zero_extendqisi2	@ u8SourceMode, <variable>.u8SourceMode
	bne	.L14	@,
	cmp	r7, r1	@ u8Lsb, u8GainLsb
	bne	.L14	@,
	cmp	ip, r2	@ u8Msb, uGain8Msb
	bne	.L14	@,
	cmp	sl, r3	@ u8SourceMode, u32InMode
	beq	.L17	@,
.L14:
	add	r8, r8, #1	@ i, tmp215,
	add	ip, r6, #16	@ ivtmp.445, tmp216,
	cmp	r8, #2048	@ i,
	bne	.L11	@,
	mvn	r0, #0	@ D.26843,
	b	.L9	@
.L20:
	mov	r0, #1	@,
	mov	r1, #41	@,
	movw	r2, #:lower16:.LANCHOR2	@,
	movw	r3, #369	@,
	movt	r2, #:upper16:.LANCHOR2	@,
	movw	lr, #:lower16:.LC0	@ tmp208,
	movt	lr, #:upper16:.LC0	@ tmp208,
	str	lr, [sp, #0]	@ tmp208,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26843,
	b	.L9	@
	.fnend
	.size	PQ_MNG_FindDciGain, .-PQ_MNG_FindDciGain
	.align	2
	.global	PQ_MNG_DCIDemoMode
	.type	PQ_MNG_DCIDemoMode, %function
PQ_MNG_DCIDemoMode:
	.fnstart
.LFB853:
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
	mov	r1, r0	@ bOnOff, bOnOff
	mov	r0, #0	@,
	bl	PQ_HAL_DCIDemoMode	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_DCIDemoMode, .-PQ_MNG_DCIDemoMode
	.align	2
	.global	PQ_MNG_SetDCILevelGain
	.type	PQ_MNG_SetDCILevelGain, %function
PQ_MNG_SetDCILevelGain:
	.fnstart
.LFB851:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #20
	sub	sp, sp, #20	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r1, #3	@ u32SourceMode,
	sub	r3, fp, #36	@ tmp155,,
	movw	r5, #:lower16:.LANCHOR0	@ tmp332,
	movt	r5, #:upper16:.LANCHOR0	@ tmp332,
	movls	r4, r1	@ u32SourceMode, u32SourceMode
	movhi	r4, #0	@ u32SourceMode,
	mov	ip, #0	@ tmp152,
	mov	r7, r0	@ u32DCILevelGain, u32DCILevelGain
	str	ip, [r3, #-4]!	@ tmp152, u32BinGain0
	mov	r1, #26	@,
	mov	r0, r3	@, tmp155
	mov	r2, #31	@,
	mov	r3, r4	@, u32SourceMode
	str	r7, [r5, #4]	@ u32DCILevelGain, sg_u32DCILevel
	str	ip, [fp, #-48]	@ tmp152, u32BinGain2
	str	ip, [fp, #-44]	@ tmp152, u32BinGain1
	bl	PQ_MNG_FindDciGain	@
	mov	r1, #20	@,
	mov	r2, #25	@,
	mov	r3, r4	@, u32SourceMode
	mov	r8, r0	@ s32Ret,
	sub	r0, fp, #44	@,,
	bl	PQ_MNG_FindDciGain	@
	mov	r2, #19	@,
	mov	r3, r4	@, u32SourceMode
	mov	r1, #14	@,
	mov	r6, r0	@ D.27150,
	sub	r0, fp, #48	@,,
	bl	PQ_MNG_FindDciGain	@
	orr	r6, r6, r8	@ tmp158, D.27150, s32Ret
	orr	r6, r6, r0	@ tmp159, tmp158,
	mov	r0, r4, asl #1	@ tmp333, u32SourceMode,
	cmn	r6, #1	@ tmp159,
	moveq	r2, #42	@ tmp160,
	streq	r2, [fp, #-40]	@ tmp160, u32BinGain0
	moveq	r3, r2	@ prephitmp.495, tmp160
	streq	r2, [fp, #-44]	@ tmp160, u32BinGain1
	streq	r2, [fp, #-48]	@ tmp160, u32BinGain2
	add	r2, r0, r4	@ tmp167, tmp333, u32SourceMode
	ldrne	lr, [fp, #-40]	@ prephitmp.487, u32BinGain0
	moveq	ip, r3	@ prephitmp.491, prephitmp.495
	ldrne	ip, [fp, #-44]	@ prephitmp.491, u32BinGain1
	add	r1, r5, r2, asl #2	@, tmp178, tmp332, tmp167,
	ldrne	r3, [fp, #-48]	@ prephitmp.495, u32BinGain2
	moveq	lr, r3	@ prephitmp.487, prephitmp.495
	cmp	r4, #2	@ u32SourceMode,
	str	lr, [r1, #8]	@ prephitmp.487, sg_s32DCILevelGain
	str	ip, [r1, #12]	@ prephitmp.491, sg_s32DCILevelGain
	str	r3, [r1, #16]	@ prephitmp.495, sg_s32DCILevelGain
	beq	.L29	@,
	cmp	r4, #3	@ u32SourceMode,
	beq	.L30	@,
	cmp	r4, #1	@ u32SourceMode,
	beq	.L28	@,
.L29:
	cmp	r7, #50	@ u32DCILevelGain,
	bls	.L34	@,
	add	lr, r7, r7, asl #2	@, tmp249, u32DCILevelGain, u32DCILevelGain,
	movw	r2, #:lower16:1374389535	@ tmp255,
	movt	r2, #:upper16:1374389535	@ tmp255,
	rsb	ip, lr, lr, asl #3	@, tmp251, tmp249, tmp249,
	sub	r1, ip, #1696	@ tmp252, tmp251,
	sub	r7, r1, #4	@ tmp252, tmp252,
	smull	r1, lr, r2, r7	@, tmp254, tmp255, tmp252
	mov	r7, r7, asr #31	@ tmp257, tmp252,
	rsb	r2, r7, lr, asr #5	@, s32GainOffset0, tmp257, tmp254,
	mov	ip, r2	@ s32GainOffset2, s32GainOffset0
.L32:
	add	r1, r0, r4	@ tmp313, tmp333, u32SourceMode
	add	lr, r5, r1, asl #2	@, tmp315, tmp332, tmp313,
	ldr	r1, [lr, #8]	@ tmp317, sg_s32DCILevelGain
	adds	r1, r2, r1	@ D.26945, s32GainOffset0, tmp317
	movmi	r1, #0	@ prephitmp.497,
	bmi	.L37	@,
	cmp	r1, #63	@ D.26945,
	movge	r1, #63	@ tmp318,
	uxtb	r1, r1	@ prephitmp.497, tmp318
.L37:
	add	r4, r0, r4	@ tmp322, tmp333, u32SourceMode
	add	r5, r5, r4, asl #2	@, tmp326, tmp332, tmp322,
	ldr	r0, [r5, #12]	@ tmp328, sg_s32DCILevelGain
	adds	r2, r2, r0	@ D.26952, s32GainOffset0, tmp328
	movmi	r2, #0	@ prephitmp.527,
	bmi	.L39	@,
	cmp	r2, #63	@ D.26952,
	movge	r2, #63	@ tmp329,
	uxtb	r2, r2	@ prephitmp.527, tmp329
.L39:
	adds	r3, ip, r3	@ D.26959, s32GainOffset2, prephitmp.495
	movmi	r3, #0	@ prephitmp.526,
	bmi	.L41	@,
	cmp	r3, #63	@ D.26959,
	movge	r3, #63	@ tmp330,
	uxtb	r3, r3	@ prephitmp.526, tmp330
.L41:
	mov	r0, #0	@,
	bl	PQ_HAL_SetDCIlevel	@
	mov	r0, #0	@,
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L28:
	cmp	r7, #50	@ u32DCILevelGain,
	bhi	.L46	@,
	add	lr, r7, r7, asl #2	@, tmp238, u32DCILevelGain, u32DCILevelGain,
	mov	r2, #50	@ tmp229,
	mul	ip, r2, r7	@ tmp228, tmp229, u32DCILevelGain
	rsb	r1, lr, lr, asl #3	@, tmp240, tmp238, tmp238,
	sub	r8, r1, #1696	@ tmp241, tmp240,
	movw	r1, #:lower16:1374389535	@ tmp233,
	sub	lr, r8, #4	@ tmp241, tmp241,
	movt	r1, #:upper16:1374389535	@ tmp233,
	sub	r6, ip, #2448	@ tmp230, tmp228,
	sub	r7, r6, #2	@ tmp230, tmp230,
	mov	r8, lr, asr #31	@ tmp246, tmp241,
.L44:
	smull	r2, ip, r1, lr	@, tmp243, tmp233, tmp241
	mov	r6, r7, asr #31	@ tmp235, tmp230,
	smull	lr, r2, r1, r7	@, tmp232, tmp233, tmp230
	rsb	ip, r8, ip, asr #5	@, s32GainOffset2, tmp246, tmp243,
	rsb	r2, r6, r2, asr #5	@, s32GainOffset0, tmp235, tmp232,
	b	.L32	@
.L34:
	add	ip, r7, r7, asl #6	@, tmp260, u32DCILevelGain, u32DCILevelGain,
	movw	r1, #:lower16:1374389535	@ tmp264,
	sub	r7, ip, #3200	@ tmp261, tmp260,
	movt	r1, #:upper16:1374389535	@ tmp264,
	smull	ip, r2, r1, r7	@, tmp263, tmp264, tmp261
	mov	r7, r7, asr #31	@ tmp266, tmp261,
	rsb	r2, r7, r2, asr #5	@, s32GainOffset0, tmp266, tmp263,
	mov	ip, r2	@ s32GainOffset2, s32GainOffset0
	b	.L32	@
.L30:
	cmp	r7, #50	@ u32DCILevelGain,
	bls	.L35	@,
	add	r7, r7, r7, asl #2	@, tmp269, u32DCILevelGain, u32DCILevelGain,
	movw	ip, #:lower16:1374389535	@ tmp275,
	movt	ip, #:upper16:1374389535	@ tmp275,
	rsb	r1, r7, r7, asl #3	@, tmp282, tmp269, tmp269,
	add	r2, r7, r7, asl #2	@, tmp271, tmp269, tmp269,
	sub	lr, r1, #1696	@ tmp283, tmp282,
	sub	r7, r2, #1200	@ tmp272, tmp271,
	sub	r1, lr, #4	@ tmp283, tmp283,
	smull	lr, r2, ip, r7	@, tmp274, tmp275, tmp272
	mov	r7, r7, asr #31	@ tmp277, tmp272,
	smull	lr, ip, ip, r1	@, tmp285, tmp275, tmp283
	mov	lr, r1, asr #31	@ tmp288, tmp283,
	rsb	r2, r7, r2, asr #5	@, s32GainOffset0, tmp277, tmp274,
	rsb	ip, lr, ip, asr #5	@, s32GainOffset2, tmp288, tmp285,
	b	.L32	@
.L35:
	add	ip, r7, r7, asl #2	@, tmp291, u32DCILevelGain, u32DCILevelGain,
	add	r7, r7, r7, asl #6	@, tmp302, u32DCILevelGain, u32DCILevelGain,
	sub	r6, r7, #3200	@ tmp303, tmp302,
	movw	r1, #:lower16:1374389535	@ tmp297,
	rsb	r8, ip, ip, asl #4	@, tmp293, tmp291, tmp291,
	movt	r1, #:upper16:1374389535	@ tmp297,
	sub	r2, r8, #3696	@ tmp294, tmp293,
	mov	r8, r6, asr #31	@ tmp308, tmp303,
	sub	lr, r2, #4	@ tmp294, tmp294,
	smull	r2, ip, r1, r6	@, tmp305, tmp297, tmp303
	mov	r6, lr, asr #31	@ tmp299, tmp294,
	smull	r7, r2, r1, lr	@, tmp296, tmp297, tmp294
	rsb	ip, r8, ip, asr #5	@, s32GainOffset2, tmp308, tmp305,
	rsb	r2, r6, r2, asr #5	@, s32GainOffset0, tmp299, tmp296,
	b	.L32	@
.L46:
	rsb	r2, r7, r7, asl #3	@, tmp210, u32DCILevelGain, u32DCILevelGain,
	add	lr, r7, r7, asl #6	@, tmp221, u32DCILevelGain, u32DCILevelGain,
	sub	lr, lr, #3200	@ tmp222, tmp221,
	movw	r1, #:lower16:1374389535	@ tmp216,
	rsb	r8, r7, r2, asl #3	@, tmp212, u32DCILevelGain, tmp210,
	movt	r1, #:upper16:1374389535	@ tmp216,
	sub	r7, r8, #2688	@ tmp213, tmp212,
	mov	r8, lr, asr #31	@ tmp227, tmp222,
	sub	r7, r7, #12	@ tmp213, tmp213,
	b	.L44	@
	.fnend
	.size	PQ_MNG_SetDCILevelGain, .-PQ_MNG_SetDCILevelGain
	.align	2
	.global	PQ_MNG_EnableDCI
	.type	PQ_MNG_EnableDCI, %function
PQ_MNG_EnableDCI:
	.fnstart
.LFB848:
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
	mov	r4, r0	@ bOnOff, bOnOff
	mov	r1, r4	@, bOnOff
	mov	r0, #0	@,
	bl	PQ_HAL_EnableDCI	@
	movw	r3, #:lower16:.LANCHOR0	@ tmp135,
	movt	r3, #:upper16:.LANCHOR0	@ tmp135,
	mov	r0, #0	@,
	str	r4, [r3, #0]	@ bOnOff, bDciEn
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_EnableDCI, .-PQ_MNG_EnableDCI
	.align	2
	.global	PQ_MNG_DeinitDCI
	.type	PQ_MNG_DeinitDCI, %function
PQ_MNG_DeinitDCI:
	.fnstart
.LFB846:
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
	bl	PQ_HAL_DCIDeinit	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_DeinitDCI, .-PQ_MNG_DeinitDCI
	.align	2
	.global	PQ_MNG_DCILUTInit
	.type	PQ_MNG_DCILUTInit, %function
PQ_MNG_DCILUTInit:
	.fnstart
.LFB844:
	@ args = 0, pretend = 0, frame = 528
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #540
	sub	sp, sp, #540	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	subs	r6, r0, #0	@ pstPqParam, pstPqParam
	str	r1, [fp, #-568]	@ bDefault, %sfp
	beq	.L58	@,
	sub	r5, fp, #564	@ tmp142,,
	movw	r3, #:lower16:.LANCHOR1	@ tmp141,
	movt	r3, #:upper16:.LANCHOR1	@ tmp141,
	mov	r1, #520	@,
	mov	r0, r5	@, tmp142
	movw	r4, #:lower16:.LANCHOR0	@ tmp238,
	str	r6, [r3, #0]	@ pstPqParam, sg_pstPqParam
	movt	r4, #:upper16:.LANCHOR0	@ tmp238,
	bl	__memzero	@
	add	ip, r4, #56	@ tmp147, tmp238,
	mov	lr, r5	@ tmp145, tmp142
	add	r7, r4, #120	@ tmp151, tmp238,
	ldmia	ip!, {r0, r1, r2, r3}	@ tmp240,,,,
	sub	r8, fp, #500	@ tmp149,,
	add	sl, r4, #184	@ tmp155, tmp238,
	sub	r9, fp, #436	@ tmp153,,
	mov	r5, ip	@ tmp241, tmp240
	stmia	lr!, {r0, r1, r2, r3}	@ tmp145,,,,
	mov	ip, lr	@ tmp242, tmp145
	ldmia	r5!, {r0, r1, r2, r3}	@ tmp241,,,,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp242,,,,
	mov	lr, ip	@ tmp244, tmp242
	ldmia	r5!, {r0, r1, r2, r3}	@ tmp243,,,,
	mov	ip, r8	@ tmp246, tmp149
	stmia	lr!, {r0, r1, r2, r3}	@ tmp244,,,,
	ldmia	r5, {r0, r1, r2, r3}	@ tmp243,,,,
	stmia	lr, {r0, r1, r2, r3}	@ tmp244,,,,
	ldmia	r7!, {r0, r1, r2, r3}	@ tmp245,,,,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp246,,,,
	mov	r5, ip	@ tmp248, tmp246
	ldmia	r7!, {r0, r1, r2, r3}	@ tmp247,,,,
	mov	ip, r9	@ tmp252, tmp153
	stmia	r5!, {r0, r1, r2, r3}	@ tmp248,,,,
	mov	lr, r5	@ tmp250, tmp248
	ldmia	r7!, {r0, r1, r2, r3}	@ tmp249,,,,
	stmia	lr!, {r0, r1, r2, r3}	@ tmp250,,,,
	ldmia	r7, {r0, r1, r2, r3}	@ tmp249,,,,
	stmia	lr, {r0, r1, r2, r3}	@ tmp250,,,,
	ldmia	sl!, {r0, r1, r2, r3}	@ tmp251,,,,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp252,,,,
	mov	r5, ip	@ tmp254, tmp252
	ldmia	sl!, {r0, r1, r2, r3}	@ tmp253,,,,
	stmia	r5!, {r0, r1, r2, r3}	@ tmp254,,,,
	mov	lr, r5	@ tmp256, tmp254
	ldmia	sl!, {r0, r1, r2, r3}	@ tmp255,,,,
	stmia	lr!, {r0, r1, r2, r3}	@ tmp256,,,,
	ldmia	sl, {r0, r1, r2, r3}	@ tmp255,,,,
	stmia	lr, {r0, r1, r2, r3}	@ tmp256,,,,
	mov	r2, #128	@,
	sub	r0, fp, #372	@,,
	add	r1, r4, #248	@, tmp238,
	bl	memcpy	@
	ldr	r2, [fp, #-568]	@, %sfp
	cmp	r2, #1	@,
	beq	.L59	@,
	add	r1, r6, #1376	@, pstPqParam,
	mov	r2, #66	@,
	sub	r0, fp, #244	@,,
	bl	memcpy	@
	add	ip, r6, #1440	@, pstPqParam,
	add	r1, ip, #2	@,,
	mov	r2, #66	@,
	sub	r0, fp, #178	@,,
	bl	memcpy	@
	add	r2, r6, #1504	@, pstPqParam,
	add	r1, r2, #4	@,,
	sub	r0, fp, #112	@,,
	mov	r2, #66	@,
	bl	memcpy	@
.L55:
	sub	r0, fp, #564	@,,
	bl	PQ_HAL_SetDCILut	@
	subs	r5, r0, #0	@ s32Ret,
	bne	.L60	@,
	ldrh	r3, [r4, #40]	@, sg_s32DCILevelGain
	ldrh	r1, [r4, #32]	@, sg_s32DCILevelGain
	ldrh	r2, [r4, #36]	@, sg_s32DCILevelGain
	bl	PQ_HAL_SetDCIlevel	@
	mov	r0, r5	@ D.26763, s32Ret
.L53:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L59:
	add	r1, r4, #376	@, tmp238,
	mov	r2, #66	@,
	sub	r0, fp, #244	@,,
	bl	memcpy	@
	add	r1, r4, #444	@, tmp238,
	mov	r2, #66	@,
	sub	r0, fp, #178	@,,
	bl	memcpy	@
	add	r1, r4, #512	@, tmp238,
	mov	r2, #66	@,
	sub	r0, fp, #112	@,,
	bl	memcpy	@
	add	r1, r4, #376	@, tmp238,
	mov	r2, #66	@,
	add	r0, r6, #1376	@, pstPqParam,
	bl	memcpy	@
	add	r1, r6, #1440	@, pstPqParam,
	add	r0, r1, #2	@,,
	mov	r2, #66	@,
	add	r1, r4, #444	@, tmp238,
	bl	memcpy	@
	add	r0, r6, #1504	@, pstPqParam,
	add	r1, r4, #512	@, tmp238,
	mov	r2, #66	@,
	add	r0, r0, #4	@,,
	bl	memcpy	@
	ldrh	r5, [r4, #32]	@, sg_s32DCILevelGain
	movw	r3, #1574	@ tmp200,
	movw	ip, #1576	@ tmp203,
	movw	r1, #1578	@ tmp206,
	strh	r5, [r6, r3]	@ movhi	@, <variable>.stPQCoef.stDciCoef.stPqDciLut.u16Gain0
	ldrh	r2, [r4, #36]	@, sg_s32DCILevelGain
	strh	r2, [r6, ip]	@ movhi	@, <variable>.stPQCoef.stDciCoef.stPqDciLut.u16Gain1
	ldrh	r0, [r4, #40]	@, sg_s32DCILevelGain
	strh	r0, [r6, r1]	@ movhi	@, <variable>.stPQCoef.stDciCoef.stPqDciLut.u16Gain2
	b	.L55	@
.L58:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L61	@,
	mov	r3, #219	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26763,
	b	.L53	@
.L60:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L61	@,
	mov	r3, #253	@,
	movw	lr, #:lower16:.LC1	@ tmp227,
	movt	lr, #:upper16:.LC1	@ tmp227,
	str	lr, [sp, #0]	@ tmp227,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26763,
	b	.L53	@
.L62:
	.align	2
.L61:
	.word	.LANCHOR2+20
	.fnend
	.size	PQ_MNG_DCILUTInit, .-PQ_MNG_DCILUTInit
	.global	__aeabi_idiv
	.align	2
	.global	PQ_MNG_DCIParaInit
	.type	PQ_MNG_DCIParaInit, %function
PQ_MNG_DCIParaInit:
	.fnstart
.LFB843:
	@ args = 0, pretend = 0, frame = 192
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #196
	sub	sp, sp, #196	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r8, #10	@ tmp251,
	sub	r0, fp, #236	@,,
	mov	r1, #192	@,
	bl	__memzero	@
	mov	r1, r8	@, tmp251
	mov	r0, #512	@,
	mov	r4, #0	@ tmp135,
	mov	r2, #2	@ tmp141,
	mov	ip, #1	@ tmp139,
	mov	r7, #50	@ tmp195,
	mov	lr, #70	@ tmp199,
	mvn	r6, #0	@ tmp201,
	mov	r5, #25	@ tmp358,
	mov	sl, #18	@ tmp189,
	strb	r2, [fp, #-228]	@ tmp141, stDciPara.u8DCIShiftCtrl
	strb	ip, [fp, #-229]	@ tmp139, stDciPara.u8DCIHistLpfEn
	movw	r9, #1919	@,
	strb	ip, [fp, #-227]	@ tmp139, stDciPara.u8DCIOutRange
	mvn	r3, #37	@ movhi	@,
	strb	ip, [fp, #-226]	@ tmp139, stDciPara.u8DCIInRange
	strb	ip, [fp, #-224]	@ tmp139, stDciPara.u8DCICbCrCmpEn
	strb	sl, [fp, #-195]	@ tmp189, stDciPara.u8DCIMetrAbld
	strb	ip, [fp, #-220]	@ tmp139, stDciPara.u8DCISceneFlg
	strh	r9, [fp, #-216]	@ movhi	@, stDciPara.u16DCIHEnd
	movw	r9, #1079	@,
	strb	sl, [fp, #-197]	@ tmp189, stDciPara.u8DCIMetrAbld
	strh	r9, [fp, #-212]	@ movhi	@, stDciPara.u16DCIVEnd
	mov	r9, #64	@,
	strb	sl, [fp, #-196]	@ tmp189, stDciPara.u8DCIMetrAbld
	mov	sl, #60	@,
	strb	r9, [fp, #-206]	@, stDciPara.s8DCICbCrStaY
	mov	r9, #17	@,
	strb	r7, [fp, #-194]	@ tmp195, stDciPara.u8DCIManAdjWgt
	strb	r9, [fp, #-199]	@, stDciPara.u8DCIOrgAbld
	mov	r9, #16	@,
	strb	sl, [fp, #-193]	@, stDciPara.u8DCIManAdjWgt
	strb	r9, [fp, #-198]	@, stDciPara.u8DCIHistAbld
	mov	r9, #40	@,
	strb	lr, [fp, #-192]	@ tmp199, stDciPara.u8DCIManAdjWgt
	strb	r4, [fp, #-232]	@ tmp135, stDciPara.u8DCIStateCtrl
	strb	r4, [fp, #-230]	@ tmp135, stDciPara.u8DCISwCfgEn
	strb	r4, [fp, #-208]	@ tmp165, stDciPara.s8DCICbCrStaCr
	strb	r4, [fp, #-207]	@ tmp165, stDciPara.s8DCICbCrStaCb
	strb	r4, [fp, #-202]	@ tmp165, stDciPara.u8DCIHistCorTh
	strb	r4, [fp, #-201]	@ tmp165, stDciPara.u8DCIHistCorTh
	strb	r4, [fp, #-200]	@ tmp165, stDciPara.u8DCIHistCorTh
	strb	r4, [fp, #-225]	@ tmp135, stDciPara.u8DCICbCrStaEn
	strb	r4, [fp, #-223]	@ tmp135, stDciPara.u8DCIManAdj
	strb	r4, [fp, #-222]	@ tmp135, stDciPara.u8DCIManAdj
	strb	r4, [fp, #-221]	@ tmp135, stDciPara.u8DCIManAdj
	strb	r4, [fp, #-218]	@ tmp135, stDciPara.u8DCIDbgEn
	strb	r4, [fp, #-217]	@ tmp135, stDciPara.u8DCIEn
	strh	r4, [fp, #-214]	@ movhi	@ tmp135, stDciPara.u16DCIHStart
	strh	r4, [fp, #-210]	@ movhi	@ tmp135, stDciPara.u16DCIVStart
	strh	r4, [fp, #-204]	@ movhi	@ tmp135, stDciPara.s16DCICbCrStaOft
	strb	r6, [fp, #-191]	@ tmp201, stDciPara.u8DCIWgtClipHigh
	strb	r9, [fp, #-179]	@, stDciPara.u8DCIGainPosTh
	strb	sl, [fp, #-177]	@, stDciPara.u8DCIGainPosTh
	mov	sl, #115	@ tmp233,
	strb	r7, [fp, #-146]	@ tmp195, stDciPara.u8DCIGainNegTh
	strb	sl, [fp, #-175]	@ tmp233, stDciPara.u8DCIGainPosTh
	mov	sl, #4	@ tmp241,
	strb	r6, [fp, #-190]	@ tmp201, stDciPara.u8DCIWgtClipHigh
	strb	sl, [fp, #-171]	@ tmp241, stDciPara.u8DCIGainPosCbCr
	mov	sl, #6	@ tmp243,
	strb	r6, [fp, #-189]	@ tmp201, stDciPara.u8DCIWgtClipHigh
	strb	sl, [fp, #-170]	@ tmp243, stDciPara.u8DCIGainPosCbCr
	mov	sl, #7	@ tmp245,
	strb	r7, [fp, #-185]	@ tmp195, stDciPara.u8DCIGlbGain
	strb	sl, [fp, #-169]	@ tmp245, stDciPara.u8DCIGainPosCbCr
	mov	sl, #9	@ tmp249,
	strb	r7, [fp, #-184]	@ tmp195, stDciPara.u8DCIGlbGain
	strb	sl, [fp, #-167]	@ tmp249, stDciPara.u8DCIGainPosCbCr
	mov	sl, #30	@,
	strb	r9, [fp, #-183]	@, stDciPara.u8DCIGlbGain
	mov	r9, #20	@,
	strb	sl, [fp, #-147]	@, stDciPara.u8DCIGainNegTh
	mov	sl, #90	@ tmp263,
	strb	r7, [fp, #-178]	@ tmp195, stDciPara.u8DCIGainPosTh
	mov	r7, #8	@,
	strb	sl, [fp, #-144]	@ tmp263, stDciPara.u8DCIGainNegTh
	mvn	sl, #125	@ tmp265,
	strb	lr, [fp, #-176]	@ tmp199, stDciPara.u8DCIGainPosTh
	strb	sl, [fp, #-143]	@ tmp265, stDciPara.u8DCIGainNegTh
	mvn	sl, #105	@ tmp267,
	strb	r6, [fp, #-174]	@ tmp201, stDciPara.u8DCIGainPosTh
	strb	sl, [fp, #-142]	@ tmp267, stDciPara.u8DCIGainNegTh
	mov	sl, #30	@,
	strb	r2, [fp, #-172]	@ tmp141, stDciPara.u8DCIGainPosCbCr
	strb	sl, [fp, #-180]	@, stDciPara.u8DCIGainPosTh
	mvn	sl, #85	@ tmp269,
	strb	r7, [fp, #-168]	@, stDciPara.u8DCIGainPosCbCr
	mvn	r7, #15	@ movhi	@,
	strb	lr, [fp, #-145]	@ tmp199, stDciPara.u8DCIGainNegTh
	strb	r9, [fp, #-181]	@, stDciPara.u8DCIGainPosTh
	mvn	r9, #40	@ movhi	@,
	strb	r4, [fp, #-188]	@ tmp165, stDciPara.u8DCIWgtClipLow
	strb	r4, [fp, #-187]	@ tmp165, stDciPara.u8DCIWgtClipLow
	strb	r4, [fp, #-186]	@ tmp165, stDciPara.u8DCIWgtClipLow
	strb	r4, [fp, #-182]	@ tmp165, stDciPara.u8DCIGainPosTh
	strb	r4, [fp, #-173]	@ tmp165, stDciPara.u8DCIGainPosCbCr
	strb	r8, [fp, #-166]	@ tmp251, stDciPara.u8DCIGainPosCbCr
	strb	r8, [fp, #-165]	@ tmp251, stDciPara.u8DCIGainPosCbCr
	strb	r4, [fp, #-148]	@ tmp165, stDciPara.u8DCIGainNegTh
	strb	sl, [fp, #-141]	@ tmp269, stDciPara.u8DCIGainNegTh
	mvn	sl, #48	@ movhi	@,
	strh	r7, [fp, #-108]	@ movhi	@, stDciPara.s16DCIAdjSw
	mvn	r7, #44	@ movhi	@,
	strb	r6, [fp, #-140]	@ tmp201, stDciPara.u8DCIGainNegTh
	mvn	r6, #29	@ movhi	@,
	strh	r9, [fp, #-104]	@ movhi	@, stDciPara.s16DCIAdjSw
	mvn	r9, #11	@ movhi	@,
	strh	r6, [fp, #-106]	@ movhi	@, stDciPara.s16DCIAdjSw
	mvn	r6, #31	@ movhi	@,
	strb	ip, [fp, #-138]	@ tmp139, stDciPara.u8DCIGainNegCbCr
	mvn	ip, #25	@ movhi	@,
	strh	sl, [fp, #-102]	@ movhi	@, stDciPara.s16DCIAdjSw
	mvn	sl, #5	@ movhi	@,
	strb	r2, [fp, #-131]	@ tmp141, stDciPara.u8DCIGainNegCbCr
	strh	r7, [fp, #-100]	@ movhi	@, stDciPara.s16DCIAdjSw
	mov	r7, #13	@ movhi	@,
	strh	lr, [fp, #-70]	@ movhi	@ tmp199, stDciPara.s16DCIAdjSw
	strh	r3, [fp, #-98]	@ movhi	@, stDciPara.s16DCIAdjSw
	mov	r3, #28	@ movhi	@,
	strb	r2, [fp, #-137]	@ tmp141, stDciPara.u8DCIGainNegCbCr
	strh	r6, [fp, #-96]	@ movhi	@, stDciPara.s16DCIAdjSw
	mov	r6, #38	@ movhi	@,
	strb	r2, [fp, #-136]	@ tmp141, stDciPara.u8DCIGainNegCbCr
	strh	ip, [fp, #-94]	@ movhi	@, stDciPara.s16DCIAdjSw
	mov	ip, #62	@ movhi	@,
	strb	r2, [fp, #-135]	@ tmp141, stDciPara.u8DCIGainNegCbCr
	strh	ip, [fp, #-80]	@ movhi	@, stDciPara.s16DCIAdjSw
	strh	r9, [fp, #-92]	@ movhi	@, stDciPara.s16DCIAdjSw
	mov	r9, #69	@ movhi	@,
	strb	r2, [fp, #-134]	@ tmp141, stDciPara.u8DCIGainNegCbCr
	strh	sl, [fp, #-90]	@ movhi	@, stDciPara.s16DCIAdjSw
	mov	sl, #72	@ movhi	@,
	strb	r2, [fp, #-133]	@ tmp141, stDciPara.u8DCIGainNegCbCr
	strh	r7, [fp, #-88]	@ movhi	@, stDciPara.s16DCIAdjSw
	mov	r7, #73	@ movhi	@,
	strb	r2, [fp, #-132]	@ tmp141, stDciPara.u8DCIGainNegCbCr
	mov	r2, #66	@ movhi	@,
	strh	r3, [fp, #-86]	@ movhi	@, stDciPara.s16DCIAdjSw
	mov	r3, #44	@ movhi	@,
	strh	lr, [fp, #-76]	@ movhi	@ tmp199, stDciPara.s16DCIAdjSw
	mov	lr, #53	@ movhi	@,
	strh	r6, [fp, #-84]	@ movhi	@, stDciPara.s16DCIAdjSw
	mov	r6, #34	@ movhi	@,
	strh	lr, [fp, #-82]	@ movhi	@, stDciPara.s16DCIAdjSw
	strh	r9, [fp, #-78]	@ movhi	@, stDciPara.s16DCIAdjSw
	mov	r9, #58	@ movhi	@,
	strh	sl, [fp, #-74]	@ movhi	@, stDciPara.s16DCIAdjSw
	mov	sl, #52	@ movhi	@,
	strh	r7, [fp, #-72]	@ movhi	@, stDciPara.s16DCIAdjSw
	mov	r7, #8	@ movhi	@,
	strb	r4, [fp, #-139]	@ tmp165, stDciPara.u8DCIGainNegCbCr
	strh	r4, [fp, #-114]	@ movhi	@ tmp135, stDciPara.s16DCIAdjSw
	strh	r4, [fp, #-112]	@ movhi	@ tmp135, stDciPara.s16DCIAdjSw
	strh	r4, [fp, #-110]	@ movhi	@ tmp135, stDciPara.s16DCIAdjSw
	strh	r2, [fp, #-68]	@ movhi	@, stDciPara.s16DCIAdjSw
	strh	r3, [fp, #-62]	@ movhi	@, stDciPara.s16DCIAdjSw
	strh	r6, [fp, #-60]	@ movhi	@, stDciPara.s16DCIAdjSw
	strh	r7, [fp, #-130]	@ movhi	@, stDciPara.s16DCIGainNegSlp
	strh	r9, [fp, #-66]	@ movhi	@, stDciPara.s16DCIAdjSw
	strh	sl, [fp, #-64]	@ movhi	@, stDciPara.s16DCIAdjSw
	strh	r8, [fp, #-58]	@ movhi	@ tmp251, stDciPara.s16DCIAdjSw
	strh	r4, [fp, #-56]	@ movhi	@ tmp135, stDciPara.s16DCIAdjSw
	strh	r4, [fp, #-54]	@ movhi	@ tmp135, stDciPara.s16DCIAdjSw
	strh	r4, [fp, #-52]	@ movhi	@ tmp135, stDciPara.s16DCIAdjSw
	strh	r4, [fp, #-50]	@ movhi	@ tmp135, stDciPara.s16DCIAdjSw
	strh	r5, [fp, #-164]	@ movhi	@ tmp358, stDciPara.s16DCIGainPosSlp
	bl	__aeabi_idiv	@
	mov	r1, #20	@,
	mov	r6, r0	@ tmp380,
	mov	r0, #256	@,
	strh	r6, [fp, #-162]	@ movhi	@ tmp380, stDciPara.s16DCIGainPosSlp
	bl	__aeabi_idiv	@
	mov	r1, #45	@,
	strh	r6, [fp, #-160]	@ movhi	@ tmp380, stDciPara.s16DCIGainPosSlp
	strh	r5, [fp, #-154]	@ movhi	@ tmp358, stDciPara.s16DCIGainPosSlp
	strh	r4, [fp, #-126]	@ movhi	@ tmp135, stDciPara.s16DCIGainNegSlp
	strh	r5, [fp, #-158]	@ movhi	@ tmp358, stDciPara.s16DCIGainPosSlp
	strh	r4, [fp, #-124]	@ movhi	@ tmp135, stDciPara.s16DCIGainNegSlp
	strh	r5, [fp, #-156]	@ movhi	@ tmp358, stDciPara.s16DCIGainPosSlp
	strh	r4, [fp, #-122]	@ movhi	@ tmp135, stDciPara.s16DCIGainNegSlp
	strh	r4, [fp, #-120]	@ movhi	@ tmp135, stDciPara.s16DCIGainNegSlp
	strh	r0, [fp, #-128]	@ movhi	@, stDciPara.s16DCIGainNegSlp
	mov	r0, #256	@,
	bl	__aeabi_idiv	@
	sub	r1, fp, #236	@,,
	strh	r4, [fp, #-118]	@ movhi	@ tmp135, stDciPara.s16DCIGainNegSlp
	strh	r4, [fp, #-150]	@ movhi	@ tmp135, stDciPara.s16DCIGainPosSlp
	strh	r4, [fp, #-116]	@ movhi	@ tmp135, stDciPara.s16DCIGainNegSlp
	strh	r0, [fp, #-152]	@ movhi	@, stDciPara.s16DCIGainPosSlp
	mov	r0, r4	@, tmp135
	bl	PQ_HAL_SetDCIParam	@
	mov	r0, r4	@, tmp135
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
	.fnend
	.size	PQ_MNG_DCIParaInit, .-PQ_MNG_DCIParaInit
	.align	2
	.global	PQ_MNG_InitDCI
	.type	PQ_MNG_InitDCI, %function
PQ_MNG_InitDCI:
	.fnstart
.LFB845:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r4, r0	@ pstPqParam, pstPqParam
	mov	r5, r1	@ bDefault, bDefault
	bl	PQ_HAL_DCIInit	@
	cmp	r0, #0	@,
	bne	.L71	@,
	bl	PQ_MNG_DCIParaInit	@
	cmp	r0, #0	@,
	bne	.L72	@,
	mov	r0, r4	@, pstPqParam
	mov	r1, r5	@, bDefault
	bl	PQ_MNG_DCILUTInit	@
	cmp	r0, #0	@ s32Ret.834
	bne	.L73	@,
.L67:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L71:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L74	@,
	mov	r3, #280	@,
	movw	ip, #:lower16:.LC2	@ tmp142,
	movt	ip, #:upper16:.LC2	@ tmp142,
	str	ip, [sp, #0]	@ tmp142,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26799,
	b	.L67	@
.L72:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L74	@,
	movw	r3, #287	@,
	movw	lr, #:lower16:.LC3	@ tmp145,
	movt	lr, #:upper16:.LC3	@ tmp145,
	str	lr, [sp, #0]	@ tmp145,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26799,
	b	.L67	@
.L73:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L74	@,
	movw	r3, #294	@,
	movw	ip, #:lower16:.LC4	@ tmp149,
	movt	ip, #:upper16:.LC4	@ tmp149,
	str	ip, [sp, #0]	@ tmp149,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26799,
	b	.L67	@
.L75:
	.align	2
.L74:
	.word	.LANCHOR2+40
	.fnend
	.size	PQ_MNG_InitDCI, .-PQ_MNG_InitDCI
	.global	HistCoef0
	.global	HistCoef1
	.global	HistCoef2
	.global	WgtCoef0
	.global	WgtCoef1
	.global	WgtCoef2
	.global	YdivCoef
	.section	.rodata
	.align	2
.LANCHOR2 = . + 0
	.type	__func__.26835, %object
	.size	__func__.26835, 19
__func__.26835:
	.ascii	"PQ_MNG_FindDciGain\000"
	.space	1
	.type	__func__.26757, %object
	.size	__func__.26757, 18
__func__.26757:
	.ascii	"PQ_MNG_DCILUTInit\000"
	.space	2
	.type	__func__.26792, %object
	.size	__func__.26792, 15
__func__.26792:
	.ascii	"PQ_MNG_InitDCI\000"
	.data
	.align	2
.LANCHOR0 = . + 0
	.type	bDciEn, %object
	.size	bDciEn, 4
bDciEn:
	.word	1
	.type	sg_u32DCILevel, %object
	.size	sg_u32DCILevel, 4
sg_u32DCILevel:
	.word	50
	.type	sg_s32DCILevelGain, %object
	.size	sg_s32DCILevelGain, 48
sg_s32DCILevelGain:
	.word	38
	.word	38
	.word	38
	.word	32
	.word	32
	.word	32
	.word	38
	.word	38
	.word	38
	.word	42
	.word	42
	.word	42
	.type	HistCoef0, %object
	.size	HistCoef0, 64
HistCoef0:
	.short	17
	.short	16
	.short	15
	.short	14
	.short	13
	.short	11
	.short	9
	.short	7
	.short	4
	.short	2
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	HistCoef1, %object
	.size	HistCoef1, 64
HistCoef1:
	.short	0
	.short	0
	.short	0
	.short	0
	.short	1
	.short	2
	.short	3
	.short	4
	.short	6
	.short	8
	.short	9
	.short	10
	.short	11
	.short	12
	.short	13
	.short	14
	.short	15
	.short	16
	.short	16
	.short	15
	.short	14
	.short	13
	.short	12
	.short	11
	.short	10
	.short	9
	.short	8
	.short	7
	.short	6
	.short	5
	.short	4
	.short	3
	.type	HistCoef2, %object
	.size	HistCoef2, 64
HistCoef2:
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	1
	.short	1
	.short	2
	.short	3
	.short	4
	.short	6
	.short	8
	.short	9
	.short	10
	.short	12
	.short	13
	.short	14
	.short	14
	.short	15
	.short	15
	.short	15
	.type	YdivCoef, %object
	.size	YdivCoef, 128
YdivCoef:
	.short	1
	.short	4096
	.short	2048
	.short	1365
	.short	1024
	.short	819
	.short	682
	.short	585
	.short	512
	.short	455
	.short	409
	.short	372
	.short	341
	.short	315
	.short	292
	.short	273
	.short	256
	.short	240
	.short	227
	.short	215
	.short	204
	.short	195
	.short	186
	.short	178
	.short	170
	.short	163
	.short	157
	.short	151
	.short	146
	.short	141
	.short	136
	.short	132
	.short	128
	.short	124
	.short	120
	.short	117
	.short	113
	.short	110
	.short	107
	.short	105
	.short	102
	.short	99
	.short	97
	.short	95
	.short	93
	.short	91
	.short	89
	.short	87
	.short	85
	.short	83
	.short	81
	.short	80
	.short	78
	.short	77
	.short	75
	.short	74
	.short	73
	.short	71
	.short	70
	.short	69
	.short	68
	.short	67
	.short	66
	.short	65
	.type	WgtCoef0, %object
	.size	WgtCoef0, 66
WgtCoef0:
	.short	0
	.short	0
	.short	3
	.short	7
	.short	12
	.short	19
	.short	30
	.short	45
	.short	61
	.short	81
	.short	100
	.short	112
	.short	118
	.short	122
	.short	123
	.short	123
	.short	121
	.short	119
	.short	115
	.short	110
	.short	103
	.short	94
	.short	82
	.short	66
	.short	49
	.short	35
	.short	23
	.short	12
	.short	8
	.short	5
	.short	3
	.short	2
	.short	0
	.space	2
	.type	WgtCoef1, %object
	.size	WgtCoef1, 66
WgtCoef1:
	.short	0
	.short	-6
	.short	-13
	.short	-23
	.short	-32
	.short	-38
	.short	-41
	.short	-41
	.short	-39
	.short	-36
	.short	-30
	.short	-20
	.short	0
	.short	13
	.short	28
	.short	39
	.short	46
	.short	51
	.short	52
	.short	54
	.short	54
	.short	52
	.short	49
	.short	43
	.short	39
	.short	33
	.short	25
	.short	14
	.short	2
	.short	0
	.short	0
	.short	0
	.short	0
	.space	2
	.type	WgtCoef2, %object
	.size	WgtCoef2, 66
WgtCoef2:
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	-6
	.short	-15
	.short	-21
	.short	-25
	.short	-32
	.short	-38
	.short	-42
	.short	-42
	.short	-43
	.short	-43
	.short	-47
	.short	-48
	.short	-51
	.short	-50
	.short	-49
	.short	-46
	.short	-42
	.short	-39
	.short	-36
	.short	-30
	.short	-24
	.short	-18
	.short	-10
	.short	-4
	.short	0
	.short	0
	.short	0
	.short	0
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"pointer is NULL!\012\000"
	.space	2
.LC1:
	.ascii	"PQ_HAL_SetDCILut error! \012\000"
	.space	2
.LC2:
	.ascii	"PQ_HAL_DCIInit error! \012\000"
.LC3:
	.ascii	"PQ_MNG_DCIParaInit error! \012\000"
.LC4:
	.ascii	"PQ_MNG_DCILUTInit error! \012\000"
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	sg_pstPqParam, %object
	.size	sg_pstPqParam, 4
sg_pstPqParam:
	.space	4
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
