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
	.file	"pq_mng_acm.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_mng_acm)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/mng/.pq_mng_acm.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/mng/pq_mng_acm.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/mng/pq_mng_acm.o -O2 -Wall -Wundef
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
	.global	PQ_MNG_GetColorGainLevel
	.type	PQ_MNG_GetColorGainLevel, %function
PQ_MNG_GetColorGainLevel:
	.fnstart
.LFB1394:
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
	ldr	r3, [r1, #0]	@ sg_u32ColorLevel, sg_u32ColorLevel
	str	r3, [r0, #0]	@ sg_u32ColorLevel,* pu32ColorLevel
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_GetColorGainLevel, .-PQ_MNG_GetColorGainLevel
	.align	2
	.global	PQ_MNG_GetFleshToneLevel
	.type	PQ_MNG_GetFleshToneLevel, %function
PQ_MNG_GetFleshToneLevel:
	.fnstart
.LFB1396:
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
	ldr	r3, [r1, #4]	@ sg_enFleshLevel, sg_enFleshLevel
	str	r3, [r0, #0]	@ sg_enFleshLevel,* pu32FleshToneLevel
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_GetFleshToneLevel, .-PQ_MNG_GetFleshToneLevel
	.align	2
	.global	PQ_MNG_GetSixBaseColorLevel
	.type	PQ_MNG_GetSixBaseColorLevel, %function
PQ_MNG_GetSixBaseColorLevel:
	.fnstart
.LFB1402:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp135,
	movt	r3, #:upper16:.LANCHOR0	@ tmp135,
	mov	r2, r0	@ pstSixBaseColorOffset, pstSixBaseColorOffset
	mov	r0, #0	@,
	ldr	r6, [r3, #28]	@ sg_stSixbaseColorOffset.u32YellowOffset, sg_stSixbaseColorOffset.u32YellowOffset
	ldr	r5, [r3, #8]	@ sg_stSixbaseColorOffset.u32RedOffset, sg_stSixbaseColorOffset.u32RedOffset
	ldr	r4, [r3, #12]	@ sg_stSixbaseColorOffset.u32GreenOffset, sg_stSixbaseColorOffset.u32GreenOffset
	ldr	ip, [r3, #16]	@ sg_stSixbaseColorOffset.u32BlueOffset, sg_stSixbaseColorOffset.u32BlueOffset
	ldr	r1, [r3, #20]	@ sg_stSixbaseColorOffset.u32CyanOffset, sg_stSixbaseColorOffset.u32CyanOffset
	ldr	r3, [r3, #24]	@ sg_stSixbaseColorOffset.u32MagentaOffset, sg_stSixbaseColorOffset.u32MagentaOffset
	str	r6, [r2, #20]	@ sg_stSixbaseColorOffset.u32YellowOffset, <variable>.u32YellowOffset
	str	r5, [r2, #0]	@ sg_stSixbaseColorOffset.u32RedOffset, <variable>.u32RedOffset
	stmib	r2, {r4, ip}	@ phole stm
	str	r1, [r2, #12]	@ sg_stSixbaseColorOffset.u32CyanOffset, <variable>.u32CyanOffset
	str	r3, [r2, #16]	@ sg_stSixbaseColorOffset.u32MagentaOffset, <variable>.u32MagentaOffset
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_GetSixBaseColorLevel, .-PQ_MNG_GetSixBaseColorLevel
	.align	2
	.global	PQ_MNG_GetColorEnhanceMode
	.type	PQ_MNG_GetColorEnhanceMode, %function
PQ_MNG_GetColorEnhanceMode:
	.fnstart
.LFB1404:
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
	movw	r1, #:lower16:.LANCHOR1	@ tmp135,
	movt	r1, #:upper16:.LANCHOR1	@ tmp135,
	ldr	r3, [r1, #0]	@ sg_enColorSpecModeType, sg_enColorSpecModeType
	str	r3, [r0, #0]	@ sg_enColorSpecModeType,* pu32ColorEnhanceMode
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_GetColorEnhanceMode, .-PQ_MNG_GetColorEnhanceMode
	.align	2
	.global	PQ_MNG_EnableColorEnhance
	.type	PQ_MNG_EnableColorEnhance, %function
PQ_MNG_EnableColorEnhance:
	.fnstart
.LFB1407:
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
	cmp	r0, #1	@ bOnOff,
	beq	.L14	@,
	mov	r0, #0	@,
	bl	PQ_HAL_DisableACM	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.L14:
	mov	r0, #0	@,
	bl	PQ_HAL_EnableACM	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_EnableColorEnhance, .-PQ_MNG_EnableColorEnhance
	.align	2
	.global	PQ_MNG_ColorDemoMode
	.type	PQ_MNG_ColorDemoMode, %function
PQ_MNG_ColorDemoMode:
	.fnstart
.LFB1406:
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
	bl	PQ_HAL_ACMDemoMode	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_ColorDemoMode, .-PQ_MNG_ColorDemoMode
	.align	2
	.type	PQ_MNG_FindAcmGain, %function
PQ_MNG_FindAcmGain:
	.fnstart
.LFB1397:
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
	ldr	ip, [ip, #4]	@ sg_pstPqParam.442, sg_pstPqParam
	cmp	ip, #0	@ sg_pstPqParam.442,
	beq	.L29	@,
	add	r5, ip, #37888	@ ivtmp.646, sg_pstPqParam.442,
	movw	r4, #:lower16:-120831580	@ tmp214,
	add	ip, r5, #244	@ ivtmp.646, ivtmp.646,
	movt	r4, #:upper16:-120831580	@ tmp214,
	mov	r8, #0	@ i,
.L21:
	ldr	r6, [ip, #-12]	@ <variable>.u32RegAddr, <variable>.u32RegAddr
	ldr	r5, [ip, #0]	@ u32Value, <variable>.u32Value
	cmp	r6, r4	@ <variable>.u32RegAddr, tmp214
	ldrb	r7, [ip, #-7]	@ zero_extendqisi2	@ u8Msb, <variable>.u8Msb
	ldrb	r6, [ip, #-8]	@ zero_extendqisi2	@ u8Lsb, <variable>.u8Lsb
	ldrb	sl, [ip, #-6]	@ zero_extendqisi2	@ u8SourceMode, <variable>.u8SourceMode
	bne	.L20	@,
	cmp	r6, r1	@ u8Lsb, u8GainLsb
	bne	.L20	@,
	cmp	r7, r2	@ u8Msb, uGain8Msb
	bne	.L20	@,
	cmp	sl, r3	@ u8SourceMode, u32InMode
	bne	.L20	@,
.L27:
	str	r5, [r0, #0]	@ u32Value,* pu32Value
	mov	r0, #0	@ D.35648,
.L19:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L20:
	add	r6, ip, #16	@ tmp216, ivtmp.646,
	ldr	r5, [ip, #16]	@ u32Value, <variable>.u32Value
	add	r8, r8, #1	@ tmp215, i,
	ldr	sl, [r6, #-12]	@ <variable>.u32RegAddr, <variable>.u32RegAddr
	ldrb	r7, [r6, #-8]	@ zero_extendqisi2	@ u8Lsb, <variable>.u8Lsb
	cmp	sl, r4	@ <variable>.u32RegAddr, tmp214
	ldrb	ip, [r6, #-7]	@ zero_extendqisi2	@ u8Msb, <variable>.u8Msb
	ldrb	sl, [r6, #-6]	@ zero_extendqisi2	@ u8SourceMode, <variable>.u8SourceMode
	bne	.L24	@,
	cmp	r7, r1	@ u8Lsb, u8GainLsb
	bne	.L24	@,
	cmp	ip, r2	@ u8Msb, uGain8Msb
	bne	.L24	@,
	cmp	sl, r3	@ u8SourceMode, u32InMode
	beq	.L27	@,
.L24:
	add	r8, r8, #1	@ i, tmp215,
	add	ip, r6, #16	@ ivtmp.646, tmp216,
	cmp	r8, #2048	@ i,
	bne	.L21	@,
	mvn	r0, #0	@ D.35648,
	b	.L19	@
.L29:
	mov	r0, #1	@,
	mov	r1, #41	@,
	movw	r2, #:lower16:.LANCHOR2	@,
	movw	r3, #271	@,
	movt	r2, #:upper16:.LANCHOR2	@,
	movw	lr, #:lower16:.LC0	@ tmp208,
	movt	lr, #:upper16:.LC0	@ tmp208,
	str	lr, [sp, #0]	@ tmp208,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35648,
	b	.L19	@
	.fnend
	.size	PQ_MNG_FindAcmGain, .-PQ_MNG_FindAcmGain
	.align	2
	.type	PQ_MNG_GetAcmGain, %function
PQ_MNG_GetAcmGain:
	.fnstart
.LFB1398:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #0	@ pu32Luma,
	mov	r4, r1	@ pu32Hue, pu32Hue
	mov	r5, r2	@ pu32Sat, pu32Sat
	mov	r7, r3	@ u32InMode, u32InMode
	beq	.L37	@,
	cmp	r1, #0	@ pu32Hue,
	beq	.L38	@,
	cmp	r2, #0	@ pu32Sat,
	beq	.L39	@,
	mov	r1, #20	@,
	mov	r2, #29	@,
	bl	PQ_MNG_FindAcmGain	@
	mov	r1, #10	@,
	mov	r2, #19	@,
	mov	r3, r7	@, u32InMode
	mov	r6, r0	@ s32Ret.674,
	mov	r0, r4	@, pu32Hue
	bl	PQ_MNG_FindAcmGain	@
	mov	r3, r7	@, u32InMode
	mov	r1, #0	@,
	mov	r2, #9	@,
	orr	r6, r0, r6	@ s32Ret.675,, s32Ret.674
	mov	r0, r5	@, pu32Sat
	bl	PQ_MNG_FindAcmGain	@
	orr	r0, r6, r0	@ s32Ret, s32Ret.675,
.L32:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L39:
	ldr	r2, .L40	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	movw	r3, #315	@,
.L36:
	movw	ip, #:lower16:.LC0	@ tmp148,
	movt	ip, #:upper16:.LC0	@ tmp148,
	str	ip, [sp, #0]	@ tmp148,
	bl	HI_LogOut	@
	mvn	r0, #0	@ s32Ret,
	b	.L32	@
.L38:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L40	@,
	movw	r3, #314	@,
	b	.L36	@
.L37:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L40	@,
	movw	r3, #313	@,
	b	.L36	@
.L41:
	.align	2
.L40:
	.word	.LANCHOR2+20
	.fnend
	.size	PQ_MNG_GetAcmGain, .-PQ_MNG_GetAcmGain
	.align	2
	.global	PQ_MNG_SetColorSatGain
	.type	PQ_MNG_SetColorSatGain, %function
PQ_MNG_SetColorSatGain:
	.fnstart
.LFB1401:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #36
	sub	sp, sp, #36	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #0	@
	str	r0, [fp, #-48]	@, %sfp
	beq	.L43	@,
	movw	r5, #:lower16:1374389535	@ tmp223,
	sub	r6, r3, #50	@ tmp222, s32Sat,
	movt	r5, #:upper16:1374389535	@ tmp223,
	mov	r0, #0	@,
	str	r0, [fp, #-52]	@, %sfp
.L44:
	ldr	r4, [fp, #-52]	@, %sfp
	movw	r8, #406	@,
	mov	r7, #0	@ j,
	mul	r9, r8, r4	@ tmp214,,
	mov	r8, r7	@ k, j
.L50:
	mov	r0, #58	@,
	cmp	r8, r2	@ k, s32HueEnd
	movgt	sl, #0	@, tmp247
	movle	sl, #1	@, tmp247
	mla	r3, r0, r7, r9	@ tmp205,, j, tmp214
	cmp	r8, r1	@ k, s32HueStart
	ldr	ip, [fp, #-48]	@, %sfp
	movlt	sl, #0	@, tmp247,
	cmp	sl, #0	@ tmp247,
	add	r4, r3, #4048	@ tmp206, tmp205,
	add	r0, r4, #8	@ tmp206, tmp206,
	add	r3, ip, r0	@ tmp208,, tmp206
	add	ip, r3, #4	@ ivtmp.709, tmp208,
	beq	.L53	@,
	ldrsh	sl, [r3, #4]	@ tmp249, <variable>.as16Sat
	mul	r0, sl, r6	@ tmp250, tmp249, tmp222
	smull	sl, r4, r5, r0	@, tmp252, tmp223, tmp250
	mov	r0, r0, asr #31	@ tmp254, tmp250,
	rsb	sl, r0, r4, asr #4	@, tmp255, tmp254, tmp252,
	strh	sl, [r3, #4]	@ movhi	@ tmp255, <variable>.as16Sat
.L53:
	mov	r3, #0	@ tmp231,
	cmp	r3, r3	@ tmp231,
	add	r0, ip, #2	@ ivtmp.709, ivtmp.709,
	mov	r3, #1	@ k,
	beq	.L65	@,
	cmp	r3, r2	@ k, s32HueEnd
	movgt	r4, #0	@, tmp260
	movle	r4, #1	@, tmp260
	cmp	r3, r1	@ k, s32HueStart
	movlt	r4, #0	@, tmp260,
	cmp	r4, #0	@ tmp260,
	beq	.L55	@,
	ldrsh	sl, [ip, #2]	@ tmp262, <variable>.as16Sat
	mul	r4, sl, r6	@, tmp262, tmp222
	str	r4, [fp, #-64]	@, %sfp
	smull	sl, r4, r5, r4	@,, tmp223,
	ldr	sl, [fp, #-64]	@, %sfp
	str	r4, [fp, #-56]	@, %sfp
	mov	r4, sl, asr #31	@ tmp267,,
	ldr	sl, [fp, #-56]	@, %sfp
	rsb	r4, r4, sl, asr #4	@, tmp268, tmp267,,
	strh	r4, [ip, #2]	@ movhi	@ tmp268, <variable>.as16Sat
.L55:
	add	r3, r3, #1	@ k, k,
	add	r0, r0, #2	@ ivtmp.709, ivtmp.709,
	cmp	r3, #29	@ k,
	beq	.L63	@,
.L65:
	str	r7, [fp, #-56]	@ j, %sfp
.L47:
	cmp	r3, r2	@ k, s32HueEnd
	movgt	r4, #0	@,
	movle	r4, #1	@,
	cmp	r3, r1	@ k, s32HueStart
	add	ip, r3, #1	@ tmp232, k,
	movlt	r4, #0	@,,
	cmp	r4, #0	@ tmp192,
	add	r4, r0, #2	@ tmp233, ivtmp.709,
	beq	.L46	@,
	ldrsh	sl, [r0, #0]	@ tmp194, <variable>.as16Sat
	mul	r3, sl, r6	@ tmp195, tmp194, tmp222
	smull	sl, r7, r5, r3	@, tmp197, tmp223, tmp195
	mov	r3, r3, asr #31	@ tmp200, tmp195,
	rsb	sl, r3, r7, asr #4	@, tmp196, tmp200, tmp197,
	strh	sl, [r0, #0]	@ movhi	@ tmp196, <variable>.as16Sat
.L46:
	cmp	ip, r2	@ tmp232, s32HueEnd
	movgt	r7, #0	@, tmp240
	movle	r7, #1	@, tmp240
	cmp	ip, r1	@ tmp232, s32HueStart
	movlt	r7, #0	@, tmp240,
	cmp	r7, #0	@ tmp240,
	beq	.L58	@,
	ldrsh	sl, [r0, #2]	@ tmp270, <variable>.as16Sat
	mul	r3, sl, r6	@ tmp271, tmp270, tmp222
	smull	sl, r7, r5, r3	@, tmp273, tmp223, tmp271
	mov	sl, r3, asr #31	@ tmp275, tmp271,
	rsb	r3, sl, r7, asr #4	@, tmp276, tmp275, tmp273,
	strh	r3, [r0, #2]	@ movhi	@ tmp276, <variable>.as16Sat
.L58:
	add	r3, ip, #1	@ k, tmp232,
	add	r0, r4, #2	@ ivtmp.709, tmp233,
	cmp	r3, #29	@ k,
	bne	.L47	@,
	ldr	r7, [fp, #-56]	@ j, %sfp
.L63:
	add	r7, r7, #1	@ j, j,
	cmp	r7, #7	@ j,
	bne	.L50	@,
	ldr	ip, [fp, #-52]	@, %sfp
	add	sl, ip, #1	@,,
	str	sl, [fp, #-52]	@, %sfp
	cmp	sl, #5	@,
	bne	.L44	@,
	mov	r0, #0	@ D.35784,
.L45:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L43:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L66	@,
	movw	r3, #478	@,
	movw	ip, #:lower16:.LC1	@ tmp185,
	movt	ip, #:upper16:.LC1	@ tmp185,
	str	ip, [sp, #0]	@ tmp185,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35784,
	b	.L45	@
.L67:
	.align	2
.L66:
	.word	.LANCHOR2+40
	.fnend
	.size	PQ_MNG_SetColorSatGain, .-PQ_MNG_SetColorSatGain
	.align	2
	.global	PQ_MNG_SetColorEnhanceMode
	.type	PQ_MNG_SetColorEnhanceMode, %function
PQ_MNG_SetColorEnhanceMode:
	.fnstart
.LFB1405:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #28
	sub	sp, sp, #28	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #3	@ enColorSpecMode,
	mov	r3, #0	@ tmp144,
	mov	r5, r0	@ enColorSpecMode, enColorSpecMode
	mov	r6, r1	@ u32SourceMode, u32SourceMode
	str	r3, [fp, #-48]	@ tmp144, u32BinSat
	str	r3, [fp, #-40]	@ tmp144, u32BinLuma
	str	r3, [fp, #-44]	@ tmp144, u32BinHue
	bhi	.L82	@,
	movw	r4, #:lower16:.LANCHOR1	@ tmp246,
	movt	r4, #:upper16:.LANCHOR1	@ tmp246,
	ldr	r0, [r4, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	cmp	r0, #0	@ sg_pstAcmCoef,
	beq	.L83	@,
	movw	r8, #:lower16:kmalloc_caches	@ tmp156,
	movt	r8, #:upper16:kmalloc_caches	@ tmp156,
	mov	r1, #32	@,
	movw	r2, #6090	@,
	ldr	r0, [r8, #52]	@, kmalloc_caches
	bl	kmem_cache_alloc_trace	@
	subs	r8, r0, #0	@ pstColorParam,
	beq	.L84	@,
	cmp	r5, #2	@ enColorSpecMode,
	beq	.L75	@,
	cmp	r5, #3	@ enColorSpecMode,
	beq	.L76	@,
	ldr	r1, [r4, #8]	@, sg_pstAcmCoef
	cmp	r5, #1	@ enColorSpecMode,
	movw	r2, #6090	@,
	addeq	r1, r1, #6080	@, sg_pstAcmCoef,
	addeq	r1, r1, #10	@,,
	bl	memcpy	@
.L77:
	mov	r3, r6	@, u32SourceMode
	sub	r1, fp, #44	@,,
	sub	r2, fp, #48	@,,
	sub	r0, fp, #40	@,,
	bl	PQ_MNG_GetAcmGain	@
	add	r2, r6, r6, asl #1	@, tmp203, u32SourceMode, u32SourceMode,
	cmn	r0, #1	@,
	movw	r0, #:lower16:.LANCHOR0	@ tmp199,
	movt	r0, #:upper16:.LANCHOR0	@ tmp199,
	moveq	r3, #112	@ tmp196,
	ldrne	lr, [fp, #-40]	@ prephitmp.753, u32BinLuma
	ldrne	r7, [fp, #-44]	@ prephitmp.752, u32BinHue
	moveq	ip, r3	@ prephitmp.736, tmp196
	ldrne	ip, [fp, #-48]	@ prephitmp.736, u32BinSat
	add	r6, r0, r2, asl #4	@, tmp205, tmp199, tmp203,
	moveq	r7, ip	@ prephitmp.752, prephitmp.736
	moveq	lr, ip	@ prephitmp.753, prephitmp.736
	streq	r3, [fp, #-40]	@ tmp196, u32BinLuma
	mov	r1, lr	@, prephitmp.753
	streq	r3, [fp, #-44]	@ tmp196, u32BinHue
	mov	r2, r7	@, prephitmp.752
	streq	r3, [fp, #-48]	@ tmp196, u32BinSat
	mov	r0, #0	@,
	str	ip, [r6, #64]	@ prephitmp.736, sg_u32ColorGain
	mov	r3, ip	@, prephitmp.736
	str	lr, [r6, #56]	@ prephitmp.753, sg_u32ColorGain
	str	r7, [r6, #60]	@ prephitmp.752, sg_u32ColorGain
	bl	PQ_HAL_SetACMGain	@
	mov	r0, r8	@, pstColorParam
	bl	PQ_HAL_SetACMParam	@
	cmn	r0, #1	@ s32Ret.751,
	mov	r6, r0	@ s32Ret.751,
	beq	.L85	@,
	mov	r0, r8	@, pstColorParam
	bl	kfree	@
	mov	r0, #0	@ D.35923,
	str	r5, [r4, #0]	@ enColorSpecMode, sg_enColorSpecModeType
.L70:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L76:
	ldr	ip, [r4, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	movw	r2, #6090	@,
	add	lr, ip, #18176	@, sg_pstAcmCoef,
	add	r1, lr, #94	@,,
	bl	memcpy	@
	b	.L77	@
.L75:
	ldr	r3, [r4, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	movw	r2, #6090	@,
	add	r1, r3, #12160	@, sg_pstAcmCoef,
	add	r1, r1, #20	@,,
	bl	memcpy	@
	b	.L77	@
.L85:
	mov	r0, r8	@, pstColorParam
	bl	kfree	@
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L86	@,
	movw	r3, #698	@,
	movw	ip, #:lower16:.LC4	@ tmp243,
	movt	ip, #:upper16:.LC4	@ tmp243,
	str	ip, [sp, #0]	@ tmp243,
	bl	HI_LogOut	@
	mov	r0, r6	@ D.35923, s32Ret.751
	b	.L70	@
.L83:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L86	@,
	movw	r3, #647	@,
	movw	lr, #:lower16:.LC0	@ tmp155,
	movt	lr, #:upper16:.LC0	@ tmp155,
	str	lr, [sp, #0]	@ tmp155,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35923,
	b	.L70	@
.L82:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L86	@,
	movw	r3, #643	@,
	str	r5, [sp, #4]	@ enColorSpecMode,
	movw	ip, #:lower16:.LC2	@ tmp150,
	movt	ip, #:upper16:.LC2	@ tmp150,
	str	ip, [sp, #0]	@ tmp150,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35923,
	b	.L70	@
.L84:
	ldr	lr, .L86	@ tmp159,
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	mov	r3, #652	@,
	movw	ip, #:lower16:.LC3	@ tmp160,
	movt	ip, #:upper16:.LC3	@ tmp160,
	mov	r2, lr	@, tmp159
	stmia	sp, {ip, lr}	@ phole stm
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35923,
	b	.L70	@
.L87:
	.align	2
.L86:
	.word	.LANCHOR2+64
	.fnend
	.size	PQ_MNG_SetColorEnhanceMode, .-PQ_MNG_SetColorEnhanceMode
	.align	2
	.global	PQ_MNG_SetSixBaseColorLevel
	.type	PQ_MNG_SetSixBaseColorLevel, %function
PQ_MNG_SetSixBaseColorLevel:
	.fnstart
.LFB1403:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #28
	sub	sp, sp, #28	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r8, #:lower16:.LANCHOR1	@ tmp160,
	movt	r8, #:upper16:.LANCHOR1	@ tmp160,
	ldr	r3, [r0, #20]	@ <variable>.u32YellowOffset, <variable>.u32YellowOffset
	ldr	r5, [r0, #0]	@ <variable>.u32RedOffset, <variable>.u32RedOffset
	mov	r7, r1	@ u32SourceMode, u32SourceMode
	ldr	r6, [r8, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	movw	r4, #:lower16:.LANCHOR0	@ tmp247,
	ldr	lr, [r0, #4]	@ <variable>.u32GreenOffset, <variable>.u32GreenOffset
	movt	r4, #:upper16:.LANCHOR0	@ tmp247,
	ldr	ip, [r0, #8]	@ <variable>.u32BlueOffset, <variable>.u32BlueOffset
	cmp	r6, #0	@ sg_pstAcmCoef,
	ldr	r1, [r0, #12]	@ <variable>.u32CyanOffset, <variable>.u32CyanOffset
	mov	r6, #0	@ tmp145,
	ldr	r2, [r0, #16]	@ <variable>.u32MagentaOffset, <variable>.u32MagentaOffset
	str	r5, [r4, #8]	@ <variable>.u32RedOffset, sg_stSixbaseColorOffset.u32RedOffset
	str	lr, [r4, #12]	@ <variable>.u32GreenOffset, sg_stSixbaseColorOffset.u32GreenOffset
	str	ip, [r4, #16]	@ <variable>.u32BlueOffset, sg_stSixbaseColorOffset.u32BlueOffset
	str	r1, [r4, #20]	@ <variable>.u32CyanOffset, sg_stSixbaseColorOffset.u32CyanOffset
	str	r2, [r4, #24]	@ <variable>.u32MagentaOffset, sg_stSixbaseColorOffset.u32MagentaOffset
	str	r3, [r4, #28]	@ <variable>.u32YellowOffset, sg_stSixbaseColorOffset.u32YellowOffset
	str	r6, [fp, #-40]	@ tmp145, u32BinLuma
	str	r6, [fp, #-44]	@ tmp145, u32BinHue
	str	r6, [fp, #-48]	@ tmp145, u32BinSat
	beq	.L96	@,
	movw	r5, #:lower16:kmalloc_caches	@ tmp165,
	movt	r5, #:upper16:kmalloc_caches	@ tmp165,
	mov	r1, #32	@,
	movw	r2, #6090	@,
	ldr	r0, [r5, #52]	@, kmalloc_caches
	bl	kmem_cache_alloc_trace	@
	subs	r5, r0, #0	@ pstColorParam,
	beq	.L97	@,
	ldr	r1, [r8, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	movw	r2, #6090	@,
	add	r3, r1, #30208	@, sg_pstAcmCoef,
	add	r1, r3, #242	@,,
	bl	memcpy	@
	ldr	r3, [r4, #8]	@, sg_stSixbaseColorOffset.u32RedOffset
	mov	r1, #3	@,
	mov	r2, #11	@,
	mov	r0, r5	@, pstColorParam
	bl	PQ_MNG_SetColorSatGain	@
	ldr	r3, [r4, #12]	@, sg_stSixbaseColorOffset.u32GreenOffset
	mov	r2, #23	@,
	mov	r1, #21	@,
	mov	r0, r5	@, pstColorParam
	bl	PQ_MNG_SetColorSatGain	@
	mov	r1, r6	@, tmp145
	ldr	r3, [r4, #16]	@, sg_stSixbaseColorOffset.u32BlueOffset
	mov	r2, #1	@,
	mov	r0, r5	@, pstColorParam
	bl	PQ_MNG_SetColorSatGain	@
	ldr	r3, [r4, #16]	@, sg_stSixbaseColorOffset.u32BlueOffset
	mov	r1, #26	@,
	mov	r2, #28	@,
	mov	r0, r5	@, pstColorParam
	bl	PQ_MNG_SetColorSatGain	@
	ldr	r3, [r4, #20]	@, sg_stSixbaseColorOffset.u32CyanOffset
	mov	r1, #24	@,
	mov	r2, #26	@,
	mov	r0, r5	@, pstColorParam
	bl	PQ_MNG_SetColorSatGain	@
	ldr	r3, [r4, #24]	@, sg_stSixbaseColorOffset.u32MagentaOffset
	mov	r1, #2	@,
	mov	r2, #3	@,
	mov	r0, r5	@, pstColorParam
	bl	PQ_MNG_SetColorSatGain	@
	ldr	r3, [r4, #28]	@, sg_stSixbaseColorOffset.u32YellowOffset
	mov	r1, #14	@,
	mov	r2, #20	@,
	mov	r0, r5	@, pstColorParam
	bl	PQ_MNG_SetColorSatGain	@
	mov	r3, r7	@, u32SourceMode
	sub	r1, fp, #44	@,,
	sub	r2, fp, #48	@,,
	sub	r0, fp, #40	@,,
	add	r7, r7, r7, asl #1	@, tmp205, u32SourceMode, u32SourceMode,
	bl	PQ_MNG_GetAcmGain	@
	add	r4, r4, r7, asl #4	@, tmp207, tmp247, tmp205,
	cmn	r0, #1	@,
	mov	r0, #0	@,
	moveq	r3, #112	@ tmp198,
	ldrne	lr, [fp, #-40]	@ prephitmp.783, u32BinLuma
	ldrne	r6, [fp, #-44]	@ prephitmp.768, u32BinHue
	moveq	ip, r3	@ prephitmp.780, tmp198
	ldrne	ip, [fp, #-48]	@ prephitmp.780, u32BinSat
	moveq	r6, ip	@ prephitmp.768, prephitmp.780
	moveq	lr, ip	@ prephitmp.783, prephitmp.780
	streq	r3, [fp, #-40]	@ tmp198, u32BinLuma
	streq	r3, [fp, #-44]	@ tmp198, u32BinHue
	mov	r1, lr	@, prephitmp.783
	streq	r3, [fp, #-48]	@ tmp198, u32BinSat
	mov	r2, r6	@, prephitmp.768
	str	ip, [r4, #64]	@ prephitmp.780, sg_u32ColorGain
	mov	r3, ip	@, prephitmp.780
	str	lr, [r4, #56]	@ prephitmp.783, sg_u32ColorGain
	str	r6, [r4, #60]	@ prephitmp.768, sg_u32ColorGain
	bl	PQ_HAL_SetACMGain	@
	mov	r0, r5	@, pstColorParam
	bl	PQ_HAL_SetACMParam	@
	cmn	r0, #1	@ s32Ret.784,
	mov	r4, r0	@ s32Ret.784,
	beq	.L98	@,
	mov	r0, r5	@, pstColorParam
	bl	kfree	@
	mov	r0, #0	@ D.35831,
.L90:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L98:
	mov	r0, r5	@, pstColorParam
	bl	kfree	@
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L99	@,
	mov	r3, #596	@,
	movw	ip, #:lower16:.LC5	@ tmp245,
	movt	ip, #:upper16:.LC5	@ tmp245,
	str	ip, [sp, #0]	@ tmp245,
	bl	HI_LogOut	@
	mov	r0, r4	@ D.35831, s32Ret.784
	b	.L90	@
.L96:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L99	@,
	mov	r3, #552	@,
	movw	ip, #:lower16:.LC0	@ tmp164,
	movt	ip, #:upper16:.LC0	@ tmp164,
	str	ip, [sp, #0]	@ tmp164,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35831,
	b	.L90	@
.L97:
	ldr	lr, .L99	@ tmp168,
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	movw	r3, #557	@,
	movw	ip, #:lower16:.LC3	@ tmp170,
	movt	ip, #:upper16:.LC3	@ tmp170,
	mov	r2, lr	@, tmp168
	stmia	sp, {ip, lr}	@ phole stm
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35831,
	b	.L90	@
.L100:
	.align	2
.L99:
	.word	.LANCHOR2+92
	.fnend
	.size	PQ_MNG_SetSixBaseColorLevel, .-PQ_MNG_SetSixBaseColorLevel
	.align	2
	.global	PQ_MNG_SetFleshToneLevel
	.type	PQ_MNG_SetFleshToneLevel, %function
PQ_MNG_SetFleshToneLevel:
	.fnstart
.LFB1400:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #24
	sub	sp, sp, #24	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #3	@ enGainLevel,
	mov	r4, #0	@ tmp147,
	mov	r6, r0	@ enGainLevel, enGainLevel
	mov	r5, r1	@ u32SourceMode, u32SourceMode
	str	r4, [fp, #-32]	@ tmp147, u32BinLuma
	str	r4, [fp, #-36]	@ tmp147, u32BinHue
	str	r4, [fp, #-40]	@ tmp147, u32BinSat
	bhi	.L121	@,
	cmp	r1, #3	@ u32SourceMode,
	bhi	.L122	@,
.L104:
	movw	r4, #:lower16:.LANCHOR1	@ tmp157,
	movt	r4, #:upper16:.LANCHOR1	@ tmp157,
	ldr	r3, [r4, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	cmp	r3, #0	@ sg_pstAcmCoef,
	beq	.L123	@,
	movw	r7, #:lower16:kmalloc_caches	@ tmp162,
	movt	r7, #:upper16:kmalloc_caches	@ tmp162,
	mov	r1, #32	@,
	movw	r2, #6090	@,
	ldr	r0, [r7, #52]	@, kmalloc_caches
	bl	kmem_cache_alloc_trace	@
	subs	r7, r0, #0	@ pstColorParam,
	beq	.L124	@,
	ldr	lr, [r4, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	movw	r2, #6090	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp347,
	movt	r4, #:upper16:.LANCHOR0	@ tmp347,
	add	r1, lr, #24320	@, sg_pstAcmCoef,
	add	r1, r1, #40	@,,
	bl	memcpy	@
	mov	r3, r5	@, u32SourceMode
	sub	r1, fp, #36	@,,
	sub	r2, fp, #40	@,,
	sub	r0, fp, #32	@,,
	bl	PQ_MNG_GetAcmGain	@
	mov	r2, r5, asl #1	@ tmp346, u32SourceMode,
	cmn	r0, #1	@,
	moveq	r3, #112	@ tmp181,
	streq	r3, [fp, #-32]	@ tmp181, u32BinLuma
	moveq	r1, r3	@ prephitmp.813, tmp181
	streq	r3, [fp, #-36]	@ tmp181, u32BinHue
	streq	r3, [fp, #-40]	@ tmp181, u32BinSat
	add	r3, r2, r5	@ tmp188, tmp346, u32SourceMode
	ldrne	ip, [fp, #-32]	@ prephitmp.811, u32BinLuma
	moveq	r0, r1	@ prephitmp.799, prephitmp.813
	ldrne	r0, [fp, #-36]	@ prephitmp.799, u32BinHue
	add	r3, r4, r3, asl #4	@, tmp190, tmp347, tmp188,
	ldrne	r1, [fp, #-40]	@ prephitmp.813, u32BinSat
	moveq	ip, r1	@ prephitmp.811, prephitmp.813
	cmp	r5, #2	@ u32SourceMode,
	str	ip, [r3, #56]	@ prephitmp.811, sg_u32ColorGain
	str	r0, [r3, #60]	@ prephitmp.799, sg_u32ColorGain
	str	r1, [r3, #64]	@ prephitmp.813, sg_u32ColorGain
	beq	.L111	@,
	cmp	r5, #3	@ u32SourceMode,
	beq	.L112	@,
	cmp	r5, #1	@ u32SourceMode,
	ldrne	r1, [r4, #56]	@ sg_u32ColorGain, sg_u32ColorGain
	ldrne	r3, [r4, #64]	@ sg_u32ColorGain, sg_u32ColorGain
	ldreq	r1, [r4, #104]	@ sg_u32ColorGain, sg_u32ColorGain
	subne	r1, r1, #20	@ tmp211, sg_u32ColorGain,
	ldreq	r3, [r4, #124]	@ sg_u32ColorGain, sg_u32ColorGain
	subne	r3, r3, #20	@ tmp215, sg_u32ColorGain,
	subeq	r1, r1, #16	@ tmp219, sg_u32ColorGain,
	strne	r1, [r4, #44]	@ tmp211, sg_u32ColorGain
	subeq	r3, r3, #16	@ tmp223, sg_u32ColorGain,
	streq	r1, [r4, #92]	@ tmp219, sg_u32ColorGain
	str	r3, [r4, #76]	@ tmp223, sg_u32ColorGain
.L113:
	cmp	r6, #2	@ enGainLevel,
	beq	.L116	@,
.L126:
	cmp	r6, #3	@ enGainLevel,
	beq	.L117	@,
	add	r5, r2, r5	@ tmp244, tmp346, u32SourceMode
	cmp	r6, #1	@ enGainLevel,
	add	r3, r4, r5, asl #4	@, tmp265, tmp347, tmp244,
	movne	r2, r3	@ tmp246, tmp265
	moveq	r5, r3	@ tmp274, tmp283
	movne	r5, r2	@ tmp255, tmp246
	ldrne	r1, [r2, #32]	@ u32GainLuma, sg_u32ColorGain
	ldreq	r2, [r3, #48]	@ u32GainHue, sg_u32ColorGain
	ldrne	r2, [r5, #36]	@ u32GainHue, sg_u32ColorGain
	ldrne	r3, [r3, #40]	@ u32GainSat, sg_u32ColorGain
	ldreq	r3, [r5, #52]	@ u32GainSat, sg_u32ColorGain
	ldreq	r1, [r5, #44]	@ u32GainLuma, sg_u32ColorGain
.L118:
	mov	r0, #0	@,
	bl	PQ_HAL_SetACMGain	@
	mov	r0, r7	@, pstColorParam
	bl	PQ_HAL_SetACMParam	@
	cmn	r0, #1	@ s32Ret.812,
	mov	r5, r0	@ s32Ret.812,
	beq	.L125	@,
	mov	r0, r7	@, pstColorParam
	bl	kfree	@
	mov	r0, #0	@ D.35731,
	str	r6, [r4, #4]	@ enGainLevel, sg_enFleshLevel
.L103:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L122:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L127	@,
	movw	r3, #391	@,
	str	r5, [sp, #4]	@ u32SourceMode,
	movw	r5, #:lower16:.LC7	@ tmp156,
	movt	r5, #:upper16:.LC7	@ tmp156,
	str	r5, [sp, #0]	@ tmp156,
	bl	HI_LogOut	@
	mov	r5, r4	@ u32SourceMode, tmp147
	b	.L104	@
.L112:
	ldr	r1, [r4, #200]	@ sg_u32ColorGain, sg_u32ColorGain
	cmp	r6, #2	@ enGainLevel,
	ldr	r0, [r4, #208]	@ sg_u32ColorGain, sg_u32ColorGain
	sub	r1, r1, #30	@ tmp235, sg_u32ColorGain,
	str	r1, [r4, #188]	@ tmp235, sg_u32ColorGain
	add	lr, r0, #30	@ tmp239, sg_u32ColorGain,
	str	lr, [r4, #220]	@ tmp239, sg_u32ColorGain
	bne	.L126	@,
.L116:
	add	ip, r2, r5	@ tmp297, tmp346, u32SourceMode
	add	r2, r4, ip, asl #4	@, tmp299, tmp347, tmp297,
	add	r1, r2, #56
	ldmia	r1, {r1, r2, r3}	@ phole ldm
	b	.L118	@
.L111:
	ldr	r3, [r4, #152]	@ sg_u32ColorGain, sg_u32ColorGain
	ldr	ip, [r4, #160]	@ sg_u32ColorGain, sg_u32ColorGain
	sub	r1, r3, #20	@ tmp227, sg_u32ColorGain,
	str	r1, [r4, #140]	@ tmp227, sg_u32ColorGain
	sub	r0, ip, #20	@ tmp231, sg_u32ColorGain,
	str	r0, [r4, #172]	@ tmp231, sg_u32ColorGain
	b	.L113	@
.L117:
	add	r3, r2, r5	@ tmp321, tmp346, u32SourceMode
	add	lr, r4, r3, asl #4	@, tmp323, tmp347, tmp321,
	add	r1, lr, #68
	ldmia	r1, {r1, r2, r3}	@ phole ldm
	b	.L118	@
.L125:
	mov	r0, r7	@, pstColorParam
	bl	kfree	@
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L127	@,
	mov	r3, #452	@,
	movw	ip, #:lower16:.LC8	@ tmp343,
	movt	ip, #:upper16:.LC8	@ tmp343,
	str	ip, [sp, #0]	@ tmp343,
	bl	HI_LogOut	@
	mov	r0, r5	@ D.35731, s32Ret.812
	b	.L103	@
.L123:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L127	@,
	movw	r3, #395	@,
	movw	lr, #:lower16:.LC0	@ tmp161,
	movt	lr, #:upper16:.LC0	@ tmp161,
	str	lr, [sp, #0]	@ tmp161,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35731,
	b	.L103	@
.L121:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L127	@,
	movw	r3, #386	@,
	str	r6, [sp, #4]	@ enGainLevel,
	movw	ip, #:lower16:.LC6	@ tmp153,
	movt	ip, #:upper16:.LC6	@ tmp153,
	str	ip, [sp, #0]	@ tmp153,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35731,
	b	.L103	@
.L124:
	ldr	lr, .L127	@ tmp165,
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	movw	r3, #399	@,
	movw	ip, #:lower16:.LC3	@ tmp167,
	movt	ip, #:upper16:.LC3	@ tmp167,
	mov	r2, lr	@, tmp165
	stmia	sp, {ip, lr}	@ phole stm
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35731,
	b	.L103	@
.L128:
	.align	2
.L127:
	.word	.LANCHOR2+120
	.fnend
	.size	PQ_MNG_SetFleshToneLevel, .-PQ_MNG_SetFleshToneLevel
	.align	2
	.global	PQ_MNG_SetColorGainLevel
	.type	PQ_MNG_SetColorGainLevel, %function
PQ_MNG_SetColorGainLevel:
	.fnstart
.LFB1395:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #24
	sub	sp, sp, #24	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #255	@ u32GainLevel,
	mov	r4, #0	@ tmp136,
	mov	r5, r0	@ u32GainLevel, u32GainLevel
	str	r4, [fp, #-24]	@ tmp136, u32Gainluma
	str	r4, [fp, #-28]	@ tmp136, u32Gainhue
	str	r4, [fp, #-32]	@ tmp136, u32GainSat
	bhi	.L133	@,
	mov	r1, #1	@,
	mov	r0, r4	@, tmp136
	bl	PQ_HAL_SetACMStretch	@
	mov	r0, r4	@, tmp136
	mov	r1, #1	@,
	bl	PQ_HAL_SetACMClipRange	@
	mov	r0, r4	@, tmp136
	mov	r1, r4	@, tmp136
	bl	PQ_HAL_SetACMCbcrThd	@
	mov	r0, r4	@, tmp136
	sub	r1, fp, #24	@,,
	sub	r2, fp, #28	@,,
	sub	r3, fp, #32	@,,
	bl	PQ_HAL_GetACMGain	@
	add	r3, r5, r5, asl #1	@,, u32GainLevel, u32GainLevel,
	mov	r0, r4	@, tmp136
	ldr	r1, [fp, #-24]	@, u32Gainluma
	ldr	r2, [fp, #-28]	@, u32Gainhue
	bl	PQ_HAL_SetACMGain	@
	mov	r0, r4	@, tmp136
	bl	PQ_HAL_EnableACM	@
	movw	r3, #:lower16:.LANCHOR0	@ tmp150,
	movt	r3, #:upper16:.LANCHOR0	@ tmp150,
	mov	r0, r4	@ D.35619, tmp136
	str	r5, [r3, #0]	@ u32GainLevel, sg_u32ColorLevel
.L131:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L133:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L134	@,
	mov	r3, #222	@,
	str	r5, [sp, #4]	@ u32GainLevel,
	movw	ip, #:lower16:.LC9	@ tmp141,
	movt	ip, #:upper16:.LC9	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35619,
	b	.L131	@
.L135:
	.align	2
.L134:
	.word	.LANCHOR2+148
	.fnend
	.size	PQ_MNG_SetColorGainLevel, .-PQ_MNG_SetColorGainLevel
	.align	2
	.global	PQ_MNG_InitColor
	.type	PQ_MNG_InitColor, %function
PQ_MNG_InitColor:
	.fnstart
.LFB1393:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r6, #:lower16:.LANCHOR1	@ tmp370,
	movt	r6, #:upper16:.LANCHOR1	@ tmp370,
	mov	r4, r1	@ bDefault, bDefault
	ldr	r3, [r6, #12]	@ sg_bColorInitial, sg_bColorInitial
	cmp	r3, #1	@ sg_bColorInitial,
	beq	.L146	@,
	cmp	r0, #0	@ pstPqParam,
	beq	.L147	@,
	add	r1, r0, #1568	@ tmp147, pstPqParam,
	str	r0, [r6, #4]	@ pstPqParam, sg_pstPqParam
	add	r0, r1, #12	@ tmp147, tmp147,
	str	r0, [r6, #8]	@ tmp147, sg_pstAcmCoef
	bl	PQ_HAL_InitACM	@
	cmp	r4, #1	@ bDefault,
	movwne	r5, #:lower16:.LANCHOR3	@ tmp371,
	movtne	r5, #:upper16:.LANCHOR3	@ tmp371,
	beq	.L148	@,
.L140:
	ldr	r0, [r5, #-1864]	@, u32DefaultEn
	movw	r4, #:lower16:.LANCHOR3	@ tmp333,
	bl	PQ_MNG_EnableColorEnhance	@
	ldr	r0, [r6, #16]	@, u32DefaultDbgEn
	bl	PQ_MNG_ColorDemoMode	@
	ldr	r1, [r5, #-1860]	@, u32DefaultStretch
	mov	r0, #0	@,
	movt	r4, #:upper16:.LANCHOR3	@ tmp333,
	bl	PQ_HAL_SetACMStretch	@
	ldr	r1, [r5, #-1856]	@, u32DefaultCliprange
	mov	r0, #0	@,
	movw	r5, #:lower16:.LANCHOR1	@ tmp335,
	bl	PQ_HAL_SetACMClipRange	@
	ldr	r1, [r6, #20]	@, u32DefaultCliporwrap
	mov	r0, #0	@,
	movt	r5, #:upper16:.LANCHOR1	@ tmp335,
	bl	PQ_HAL_SetACMCliporWrap	@
	ldr	r1, [r6, #24]	@, u32DefaultCbcrthr
	movw	r6, #:lower16:kmalloc_caches	@ tmp345,
	movt	r6, #:upper16:kmalloc_caches	@ tmp345,
	mov	r0, #0	@,
	bl	PQ_HAL_SetACMCbcrThd	@
	ldr	r0, [r6, #52]	@, kmalloc_caches
	mov	r1, #208	@,
	movw	r2, #6090	@,
	bl	kmem_cache_alloc_trace	@
	subs	r6, r0, #0	@ D.36472,
	beq	.L149	@,
	ldr	r1, [r5, #8]	@, sg_pstAcmCoef
	movw	r2, #6090	@,
	bl	memcpy	@
	mov	r0, r6	@, D.36472
	bl	PQ_HAL_SetACMParam	@
	cmn	r0, #1	@ s32Ret,
	mov	r7, r0	@ s32Ret,
	beq	.L150	@,
	mov	r0, #0	@,
	ldr	r2, [r4, #-1848]	@, u32DefaultHueGain
	ldr	r3, [r4, #-1844]	@, u32DefaultSatGain
	ldr	r1, [r4, #-1852]	@, u32DefaultLumaGain
	bl	PQ_HAL_SetACMGain	@
	mov	r2, #1	@ tmp368,
	mov	r0, r6	@, D.36472
	str	r2, [r5, #12]	@ tmp368, sg_bColorInitial
	bl	kfree	@
.L146:
	mov	r0, #0	@ D.35555,
.L138:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L148:
	ldr	r1, .L151	@,
	movw	r2, #2030	@,
	ldr	r0, [r6, #8]	@, sg_pstAcmCoef
	movw	r5, #:lower16:.LANCHOR3	@ tmp371,
	bl	memcpy	@
	ldr	r3, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151+4	@,
	movw	r2, #2030	@,
	add	r4, r3, #2016	@, sg_pstAcmCoef,
	movt	r5, #:upper16:.LANCHOR3	@ tmp371,
	add	r0, r4, #14	@,,
	bl	memcpy	@
	ldr	r0, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151+8	@,
	movw	r2, #2030	@,
	add	ip, r0, #4048	@, sg_pstAcmCoef,
	add	r0, ip, #12	@,,
	bl	memcpy	@
	ldr	r3, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151	@,
	movw	r2, #2030	@,
	add	r4, r3, #6080	@, sg_pstAcmCoef,
	add	r0, r4, #10	@,,
	bl	memcpy	@
	ldr	r0, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151+4	@,
	movw	r2, #2030	@,
	add	ip, r0, #8064	@, sg_pstAcmCoef,
	add	r0, ip, #56	@,,
	bl	memcpy	@
	ldr	r3, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151+8	@,
	movw	r2, #2030	@,
	add	r4, r3, #10112	@, sg_pstAcmCoef,
	add	r0, r4, #38	@,,
	bl	memcpy	@
	ldr	r0, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151	@,
	movw	r2, #2030	@,
	add	ip, r0, #12160	@, sg_pstAcmCoef,
	add	r0, ip, #20	@,,
	bl	memcpy	@
	ldr	r3, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151+4	@,
	movw	r2, #2030	@,
	add	r4, r3, #14208	@, sg_pstAcmCoef,
	add	r0, r4, #2	@,,
	bl	memcpy	@
	ldr	r0, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151+8	@,
	movw	r2, #2030	@,
	add	ip, r0, #16192	@, sg_pstAcmCoef,
	add	r0, ip, #48	@,,
	bl	memcpy	@
	ldr	r3, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151	@,
	movw	r2, #2030	@,
	add	r4, r3, #18176	@, sg_pstAcmCoef,
	add	r0, r4, #94	@,,
	bl	memcpy	@
	ldr	r0, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151+4	@,
	movw	r2, #2030	@,
	add	ip, r0, #20224	@, sg_pstAcmCoef,
	add	r0, ip, #76	@,,
	bl	memcpy	@
	ldr	r3, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151+8	@,
	movw	r2, #2030	@,
	add	r4, r3, #22272	@, sg_pstAcmCoef,
	add	r0, r4, #58	@,,
	bl	memcpy	@
	ldr	r0, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151	@,
	movw	r2, #2030	@,
	add	ip, r0, #24320	@, sg_pstAcmCoef,
	add	r0, ip, #40	@,,
	bl	memcpy	@
	ldr	r3, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151+4	@,
	movw	r2, #2030	@,
	add	r4, r3, #26368	@, sg_pstAcmCoef,
	add	r0, r4, #22	@,,
	bl	memcpy	@
	ldr	r0, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151+8	@,
	movw	r2, #2030	@,
	add	ip, r0, #28416	@, sg_pstAcmCoef,
	add	r0, ip, #4	@,,
	bl	memcpy	@
	ldr	r3, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151	@,
	movw	r2, #2030	@,
	add	r4, r3, #30208	@, sg_pstAcmCoef,
	add	r0, r4, #242	@,,
	bl	memcpy	@
	ldr	r0, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151+4	@,
	movw	r2, #2030	@,
	add	ip, r0, #32256	@, sg_pstAcmCoef,
	add	r0, ip, #224	@,,
	bl	memcpy	@
	ldr	r3, [r6, #8]	@ sg_pstAcmCoef, sg_pstAcmCoef
	ldr	r1, .L151+8	@,
	movw	r2, #2030	@,
	add	r4, r3, #34304	@, sg_pstAcmCoef,
	add	r0, r4, #206	@,,
	bl	memcpy	@
	b	.L140	@
.L150:
	mov	r0, r6	@, D.36472
	bl	kfree	@
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L151+12	@,
	mov	r3, #176	@,
	movw	ip, #:lower16:.LC5	@ tmp360,
	movt	ip, #:upper16:.LC5	@ tmp360,
	str	ip, [sp, #0]	@ tmp360,
	bl	HI_LogOut	@
	mov	r0, r7	@ D.35555, s32Ret
	b	.L138	@
.L147:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L151+12	@,
	mov	r3, #121	@,
	movw	ip, #:lower16:.LC0	@ tmp144,
	movt	ip, #:upper16:.LC0	@ tmp144,
	str	ip, [sp, #0]	@ tmp144,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35555,
	b	.L138	@
.L149:
	ldr	lr, .L151+12	@ tmp348,
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	mov	r3, #166	@,
	movw	ip, #:lower16:.LC10	@ tmp349,
	movt	ip, #:upper16:.LC10	@ tmp349,
	mov	r2, lr	@, tmp348
	stmia	sp, {ip, lr}	@ phole stm
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35555,
	b	.L138	@
.L152:
	.align	2
.L151:
	.word	.LANCHOR0+224
	.word	.LANCHOR0+2256
	.word	.LANCHOR3-3896
	.word	.LANCHOR2+176
	.fnend
	.size	PQ_MNG_InitColor, .-PQ_MNG_InitColor
	.align	2
	.global	PQ_MNG_DeInitColor
	.type	PQ_MNG_DeInitColor, %function
PQ_MNG_DeInitColor:
	.fnstart
.LFB1392:
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
	movw	r4, #:lower16:.LANCHOR1	@ tmp134,
	movt	r4, #:upper16:.LANCHOR1	@ tmp134,
	ldr	r3, [r4, #12]	@ sg_bColorInitial, sg_bColorInitial
	cmp	r3, #0	@ sg_bColorInitial,
	beq	.L154	@,
	bl	PQ_HAL_DeInitACM	@
	mov	r0, #0	@ tmp137,
	str	r0, [r4, #12]	@ tmp137, sg_bColorInitial
	str	r0, [r4, #8]	@ tmp137, sg_pstAcmCoef
.L154:
	mov	r0, #0	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_DeInitColor, .-PQ_MNG_DeInitColor
	.global	s16HueLut
	.global	s16SatLut
	.global	s16LumaLut
	.global	u32DefaultHueGain
	.global	u32DefaultSatGain
	.global	u32DefaultLumaGain
	.global	u32DefaultEn
	.global	u32DefaultDbgEn
	.global	u32DefaultStretch
	.global	u32DefaultCliprange
	.global	u32DefaultCliporwrap
	.global	u32DefaultCbcrthr
	.section	.rodata
	.align	2
.LANCHOR2 = . + 0
	.type	__func__.35640, %object
	.size	__func__.35640, 19
__func__.35640:
	.ascii	"PQ_MNG_FindAcmGain\000"
	.space	1
	.type	__func__.35670, %object
	.size	__func__.35670, 18
__func__.35670:
	.ascii	"PQ_MNG_GetAcmGain\000"
	.space	2
	.type	__func__.35769, %object
	.size	__func__.35769, 23
__func__.35769:
	.ascii	"PQ_MNG_SetColorSatGain\000"
	.space	1
	.type	__func__.35911, %object
	.size	__func__.35911, 27
__func__.35911:
	.ascii	"PQ_MNG_SetColorEnhanceMode\000"
	.space	1
	.type	__func__.35821, %object
	.size	__func__.35821, 28
__func__.35821:
	.ascii	"PQ_MNG_SetSixBaseColorLevel\000"
	.type	__func__.35719, %object
	.size	__func__.35719, 25
__func__.35719:
	.ascii	"PQ_MNG_SetFleshToneLevel\000"
	.space	3
	.type	__func__.35613, %object
	.size	__func__.35613, 25
__func__.35613:
	.ascii	"PQ_MNG_SetColorGainLevel\000"
	.space	3
	.type	__func__.35551, %object
	.size	__func__.35551, 17
__func__.35551:
	.ascii	"PQ_MNG_InitColor\000"
	.data
	.align	2
.LANCHOR0 = . + 0
.LANCHOR3 = . + 8184
	.type	sg_u32ColorLevel, %object
	.size	sg_u32ColorLevel, 4
sg_u32ColorLevel:
	.word	128
	.type	sg_enFleshLevel, %object
	.size	sg_enFleshLevel, 4
sg_enFleshLevel:
	.word	2
	.type	sg_stSixbaseColorOffset, %object
	.size	sg_stSixbaseColorOffset, 24
sg_stSixbaseColorOffset:
@ u32RedOffset:
	.word	50
@ u32GreenOffset:
	.word	50
@ u32BlueOffset:
	.word	50
@ u32CyanOffset:
	.word	50
@ u32MagentaOffset:
	.word	50
@ u32YellowOffset:
	.word	50
	.type	sg_u32ColorGain, %object
	.size	sg_u32ColorGain, 192
sg_u32ColorGain:
	.word	0
	.word	0
	.word	0
	.word	100
	.word	100
	.word	100
	.word	120
	.word	120
	.word	120
	.word	140
	.word	140
	.word	140
	.word	0
	.word	0
	.word	0
	.word	96
	.word	96
	.word	96
	.word	112
	.word	112
	.word	112
	.word	128
	.word	128
	.word	128
	.word	0
	.word	0
	.word	0
	.word	108
	.word	108
	.word	108
	.word	128
	.word	128
	.word	128
	.word	148
	.word	148
	.word	148
	.word	0
	.word	0
	.word	0
	.word	112
	.word	112
	.word	112
	.word	142
	.word	142
	.word	142
	.word	172
	.word	172
	.word	172
	.type	s16LumaLut, %object
	.size	s16LumaLut, 2030
s16LumaLut:
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
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	-13
	.short	-16
	.short	-15
	.short	-13
	.short	-8
	.short	-6
	.short	-4
	.short	-3
	.short	-3
	.short	0
	.short	9
	.short	13
	.short	9
	.short	-2
	.short	-4
	.short	-4
	.short	-3
	.short	-3
	.short	-4
	.short	-7
	.short	-13
	.short	-7
	.short	-4
	.short	-4
	.short	-5
	.short	-8
	.short	-12
	.short	-18
	.short	-13
	.short	-27
	.short	-32
	.short	-31
	.short	-27
	.short	-17
	.short	-12
	.short	-9
	.short	-7
	.short	-6
	.short	-1
	.short	18
	.short	27
	.short	18
	.short	-4
	.short	-8
	.short	-8
	.short	-7
	.short	-7
	.short	-8
	.short	-14
	.short	-27
	.short	-14
	.short	-8
	.short	-8
	.short	-10
	.short	-16
	.short	-25
	.short	-37
	.short	-27
	.short	-35
	.short	-41
	.short	-39
	.short	-34
	.short	-22
	.short	-15
	.short	-11
	.short	-9
	.short	-7
	.short	-2
	.short	23
	.short	34
	.short	23
	.short	-5
	.short	-11
	.short	-10
	.short	-9
	.short	-8
	.short	-11
	.short	-18
	.short	-34
	.short	-18
	.short	-11
	.short	-10
	.short	-13
	.short	-21
	.short	-31
	.short	-46
	.short	-35
	.short	-41
	.short	-48
	.short	-46
	.short	-40
	.short	-26
	.short	-18
	.short	-13
	.short	-11
	.short	-9
	.short	-2
	.short	27
	.short	40
	.short	27
	.short	-6
	.short	-13
	.short	-12
	.short	-11
	.short	-10
	.short	-13
	.short	-22
	.short	-40
	.short	-22
	.short	-13
	.short	-12
	.short	-15
	.short	-25
	.short	-38
	.short	-55
	.short	-41
	.short	-48
	.short	-57
	.short	-55
	.short	-47
	.short	-31
	.short	-21
	.short	-16
	.short	-13
	.short	-10
	.short	-3
	.short	32
	.short	47
	.short	32
	.short	-7
	.short	-15
	.short	-14
	.short	-13
	.short	-12
	.short	-15
	.short	-25
	.short	-47
	.short	-25
	.short	-15
	.short	-14
	.short	-18
	.short	-29
	.short	-44
	.short	-65
	.short	-48
	.short	-55
	.short	-65
	.short	-62
	.short	-54
	.short	-35
	.short	-24
	.short	-18
	.short	-15
	.short	-12
	.short	-3
	.short	36
	.short	53
	.short	36
	.short	-8
	.short	-17
	.short	-16
	.short	-15
	.short	-14
	.short	-17
	.short	-29
	.short	-54
	.short	-29
	.short	-17
	.short	-16
	.short	-21
	.short	-33
	.short	-50
	.short	-74
	.short	-55
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
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	-13
	.short	-16
	.short	-15
	.short	-13
	.short	-8
	.short	-6
	.short	-4
	.short	-3
	.short	-3
	.short	0
	.short	9
	.short	13
	.short	9
	.short	-2
	.short	-4
	.short	-4
	.short	-3
	.short	-3
	.short	-4
	.short	-7
	.short	-13
	.short	-7
	.short	-4
	.short	-4
	.short	-5
	.short	-8
	.short	-12
	.short	-18
	.short	-13
	.short	-27
	.short	-32
	.short	-31
	.short	-27
	.short	-17
	.short	-12
	.short	-9
	.short	-7
	.short	-6
	.short	-1
	.short	18
	.short	27
	.short	18
	.short	-4
	.short	-8
	.short	-8
	.short	-7
	.short	-7
	.short	-8
	.short	-14
	.short	-27
	.short	-14
	.short	-8
	.short	-8
	.short	-10
	.short	-16
	.short	-25
	.short	-37
	.short	-27
	.short	-35
	.short	-41
	.short	-39
	.short	-34
	.short	-22
	.short	-15
	.short	-11
	.short	-9
	.short	-7
	.short	-2
	.short	23
	.short	34
	.short	23
	.short	-5
	.short	-11
	.short	-10
	.short	-9
	.short	-8
	.short	-11
	.short	-18
	.short	-34
	.short	-18
	.short	-11
	.short	-10
	.short	-13
	.short	-21
	.short	-31
	.short	-46
	.short	-35
	.short	-41
	.short	-48
	.short	-46
	.short	-40
	.short	-26
	.short	-18
	.short	-13
	.short	-11
	.short	-9
	.short	-2
	.short	27
	.short	40
	.short	27
	.short	-6
	.short	-13
	.short	-12
	.short	-11
	.short	-10
	.short	-13
	.short	-22
	.short	-40
	.short	-22
	.short	-13
	.short	-12
	.short	-15
	.short	-25
	.short	-38
	.short	-55
	.short	-41
	.short	-48
	.short	-57
	.short	-55
	.short	-47
	.short	-31
	.short	-21
	.short	-16
	.short	-13
	.short	-10
	.short	-3
	.short	32
	.short	47
	.short	32
	.short	-7
	.short	-15
	.short	-14
	.short	-13
	.short	-12
	.short	-15
	.short	-25
	.short	-47
	.short	-25
	.short	-15
	.short	-14
	.short	-18
	.short	-29
	.short	-44
	.short	-65
	.short	-48
	.short	-55
	.short	-65
	.short	-62
	.short	-54
	.short	-35
	.short	-24
	.short	-18
	.short	-15
	.short	-12
	.short	-3
	.short	36
	.short	53
	.short	36
	.short	-8
	.short	-17
	.short	-16
	.short	-15
	.short	-14
	.short	-17
	.short	-29
	.short	-54
	.short	-29
	.short	-17
	.short	-16
	.short	-21
	.short	-33
	.short	-50
	.short	-74
	.short	-55
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
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	-13
	.short	-16
	.short	-15
	.short	-13
	.short	-8
	.short	-6
	.short	-4
	.short	-3
	.short	-3
	.short	0
	.short	9
	.short	13
	.short	9
	.short	-2
	.short	-4
	.short	-4
	.short	-3
	.short	-3
	.short	-4
	.short	-7
	.short	-13
	.short	-7
	.short	-4
	.short	-4
	.short	-5
	.short	-8
	.short	-12
	.short	-18
	.short	-13
	.short	-27
	.short	-32
	.short	-31
	.short	-27
	.short	-17
	.short	-12
	.short	-9
	.short	-7
	.short	-6
	.short	-1
	.short	18
	.short	27
	.short	18
	.short	-4
	.short	-8
	.short	-8
	.short	-7
	.short	-7
	.short	-8
	.short	-14
	.short	-27
	.short	-14
	.short	-8
	.short	-8
	.short	-10
	.short	-16
	.short	-25
	.short	-37
	.short	-27
	.short	-35
	.short	-41
	.short	-39
	.short	-34
	.short	-22
	.short	-15
	.short	-11
	.short	-9
	.short	-7
	.short	-2
	.short	23
	.short	34
	.short	23
	.short	-5
	.short	-11
	.short	-10
	.short	-9
	.short	-8
	.short	-11
	.short	-18
	.short	-34
	.short	-18
	.short	-11
	.short	-10
	.short	-13
	.short	-21
	.short	-31
	.short	-46
	.short	-35
	.short	-41
	.short	-48
	.short	-46
	.short	-40
	.short	-26
	.short	-18
	.short	-13
	.short	-11
	.short	-9
	.short	-2
	.short	27
	.short	40
	.short	27
	.short	-6
	.short	-13
	.short	-12
	.short	-11
	.short	-10
	.short	-13
	.short	-22
	.short	-40
	.short	-22
	.short	-13
	.short	-12
	.short	-15
	.short	-25
	.short	-38
	.short	-55
	.short	-41
	.short	-48
	.short	-57
	.short	-55
	.short	-47
	.short	-31
	.short	-21
	.short	-16
	.short	-13
	.short	-10
	.short	-3
	.short	32
	.short	47
	.short	32
	.short	-7
	.short	-15
	.short	-14
	.short	-13
	.short	-12
	.short	-15
	.short	-25
	.short	-47
	.short	-25
	.short	-15
	.short	-14
	.short	-18
	.short	-29
	.short	-44
	.short	-65
	.short	-48
	.short	-55
	.short	-65
	.short	-62
	.short	-54
	.short	-35
	.short	-24
	.short	-18
	.short	-15
	.short	-12
	.short	-3
	.short	36
	.short	53
	.short	36
	.short	-8
	.short	-17
	.short	-16
	.short	-15
	.short	-14
	.short	-17
	.short	-29
	.short	-54
	.short	-29
	.short	-17
	.short	-16
	.short	-21
	.short	-33
	.short	-50
	.short	-74
	.short	-55
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
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	-13
	.short	-16
	.short	-15
	.short	-13
	.short	-8
	.short	-6
	.short	-4
	.short	-3
	.short	-3
	.short	0
	.short	9
	.short	13
	.short	9
	.short	-2
	.short	-4
	.short	-4
	.short	-3
	.short	-3
	.short	-4
	.short	-7
	.short	-13
	.short	-7
	.short	-4
	.short	-4
	.short	-5
	.short	-8
	.short	-12
	.short	-18
	.short	-13
	.short	-27
	.short	-32
	.short	-31
	.short	-27
	.short	-17
	.short	-12
	.short	-9
	.short	-7
	.short	-6
	.short	-1
	.short	18
	.short	27
	.short	18
	.short	-4
	.short	-8
	.short	-8
	.short	-7
	.short	-7
	.short	-8
	.short	-14
	.short	-27
	.short	-14
	.short	-8
	.short	-8
	.short	-10
	.short	-16
	.short	-25
	.short	-37
	.short	-27
	.short	-35
	.short	-41
	.short	-39
	.short	-34
	.short	-22
	.short	-15
	.short	-11
	.short	-9
	.short	-7
	.short	-2
	.short	23
	.short	34
	.short	23
	.short	-5
	.short	-11
	.short	-10
	.short	-9
	.short	-8
	.short	-11
	.short	-18
	.short	-34
	.short	-18
	.short	-11
	.short	-10
	.short	-13
	.short	-21
	.short	-31
	.short	-46
	.short	-35
	.short	-41
	.short	-48
	.short	-46
	.short	-40
	.short	-26
	.short	-18
	.short	-13
	.short	-11
	.short	-9
	.short	-2
	.short	27
	.short	40
	.short	27
	.short	-6
	.short	-13
	.short	-12
	.short	-11
	.short	-10
	.short	-13
	.short	-22
	.short	-40
	.short	-22
	.short	-13
	.short	-12
	.short	-15
	.short	-25
	.short	-38
	.short	-55
	.short	-41
	.short	-48
	.short	-57
	.short	-55
	.short	-47
	.short	-31
	.short	-21
	.short	-16
	.short	-13
	.short	-10
	.short	-3
	.short	32
	.short	47
	.short	32
	.short	-7
	.short	-15
	.short	-14
	.short	-13
	.short	-12
	.short	-15
	.short	-25
	.short	-47
	.short	-25
	.short	-15
	.short	-14
	.short	-18
	.short	-29
	.short	-44
	.short	-65
	.short	-48
	.short	-55
	.short	-65
	.short	-62
	.short	-54
	.short	-35
	.short	-24
	.short	-18
	.short	-15
	.short	-12
	.short	-3
	.short	36
	.short	53
	.short	36
	.short	-8
	.short	-17
	.short	-16
	.short	-15
	.short	-14
	.short	-17
	.short	-29
	.short	-54
	.short	-29
	.short	-17
	.short	-16
	.short	-21
	.short	-33
	.short	-50
	.short	-74
	.short	-55
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
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	-13
	.short	-16
	.short	-15
	.short	-13
	.short	-8
	.short	-6
	.short	-4
	.short	-3
	.short	-3
	.short	0
	.short	9
	.short	13
	.short	9
	.short	-2
	.short	-4
	.short	-4
	.short	-3
	.short	-3
	.short	-4
	.short	-7
	.short	-13
	.short	-7
	.short	-4
	.short	-4
	.short	-5
	.short	-8
	.short	-12
	.short	-18
	.short	-13
	.short	-27
	.short	-32
	.short	-31
	.short	-27
	.short	-17
	.short	-12
	.short	-9
	.short	-7
	.short	-6
	.short	-1
	.short	18
	.short	27
	.short	18
	.short	-4
	.short	-8
	.short	-8
	.short	-7
	.short	-7
	.short	-8
	.short	-14
	.short	-27
	.short	-14
	.short	-8
	.short	-8
	.short	-10
	.short	-16
	.short	-25
	.short	-37
	.short	-27
	.short	-35
	.short	-41
	.short	-39
	.short	-34
	.short	-22
	.short	-15
	.short	-11
	.short	-9
	.short	-7
	.short	-2
	.short	23
	.short	34
	.short	23
	.short	-5
	.short	-11
	.short	-10
	.short	-9
	.short	-8
	.short	-11
	.short	-18
	.short	-34
	.short	-18
	.short	-11
	.short	-10
	.short	-13
	.short	-21
	.short	-31
	.short	-46
	.short	-35
	.short	-41
	.short	-48
	.short	-46
	.short	-40
	.short	-26
	.short	-18
	.short	-13
	.short	-11
	.short	-9
	.short	-2
	.short	27
	.short	40
	.short	27
	.short	-6
	.short	-13
	.short	-12
	.short	-11
	.short	-10
	.short	-13
	.short	-22
	.short	-40
	.short	-22
	.short	-13
	.short	-12
	.short	-15
	.short	-25
	.short	-38
	.short	-55
	.short	-41
	.short	-48
	.short	-57
	.short	-55
	.short	-47
	.short	-31
	.short	-21
	.short	-16
	.short	-13
	.short	-10
	.short	-3
	.short	32
	.short	47
	.short	32
	.short	-7
	.short	-15
	.short	-14
	.short	-13
	.short	-12
	.short	-15
	.short	-25
	.short	-47
	.short	-25
	.short	-15
	.short	-14
	.short	-18
	.short	-29
	.short	-44
	.short	-65
	.short	-48
	.short	-55
	.short	-65
	.short	-62
	.short	-54
	.short	-35
	.short	-24
	.short	-18
	.short	-15
	.short	-12
	.short	-3
	.short	36
	.short	53
	.short	36
	.short	-8
	.short	-17
	.short	-16
	.short	-15
	.short	-14
	.short	-17
	.short	-29
	.short	-54
	.short	-29
	.short	-17
	.short	-16
	.short	-21
	.short	-33
	.short	-50
	.short	-74
	.short	-55
	.space	2
	.type	s16HueLut, %object
	.size	s16HueLut, 2030
s16HueLut:
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.short	16
	.short	15
	.short	12
	.short	6
	.short	-2
	.short	-3
	.short	-3
	.short	-4
	.short	-3
	.short	-2
	.short	5
	.short	8
	.short	3
	.short	-9
	.short	-17
	.short	-19
	.short	-17
	.short	-15
	.short	-13
	.short	-8
	.short	-1
	.short	17
	.short	21
	.short	9
	.short	0
	.short	-5
	.short	-5
	.short	0
	.short	16
	.space	2
	.type	s16SatLut, %object
	.size	s16SatLut, 2030
s16SatLut:
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
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	6
	.short	5
	.short	4
	.short	3
	.short	2
	.short	2
	.short	2
	.short	2
	.short	2
	.short	3
	.short	4
	.short	4
	.short	4
	.short	3
	.short	3
	.short	3
	.short	2
	.short	3
	.short	3
	.short	4
	.short	5
	.short	6
	.short	5
	.short	5
	.short	4
	.short	4
	.short	4
	.short	5
	.short	6
	.short	10
	.short	8
	.short	6
	.short	5
	.short	4
	.short	3
	.short	3
	.short	3
	.short	4
	.short	5
	.short	6
	.short	7
	.short	7
	.short	6
	.short	5
	.short	5
	.short	4
	.short	4
	.short	5
	.short	6
	.short	8
	.short	10
	.short	9
	.short	8
	.short	7
	.short	7
	.short	7
	.short	8
	.short	10
	.short	13
	.short	10
	.short	8
	.short	6
	.short	5
	.short	4
	.short	4
	.short	4
	.short	5
	.short	7
	.short	8
	.short	9
	.short	9
	.short	8
	.short	6
	.short	6
	.short	5
	.short	6
	.short	7
	.short	8
	.short	10
	.short	13
	.short	12
	.short	10
	.short	9
	.short	9
	.short	10
	.short	11
	.short	13
	.short	15
	.short	12
	.short	9
	.short	7
	.short	5
	.short	5
	.short	4
	.short	5
	.short	6
	.short	8
	.short	10
	.short	11
	.short	10
	.short	9
	.short	7
	.short	7
	.short	6
	.short	7
	.short	8
	.short	9
	.short	12
	.short	15
	.short	13
	.short	12
	.short	11
	.short	11
	.short	11
	.short	12
	.short	15
	.short	16
	.short	13
	.short	10
	.short	8
	.short	6
	.short	5
	.short	5
	.short	5
	.short	6
	.short	9
	.short	10
	.short	12
	.short	11
	.short	10
	.short	8
	.short	7
	.short	7
	.short	7
	.short	8
	.short	10
	.short	13
	.short	16
	.short	14
	.short	13
	.short	12
	.short	11
	.short	12
	.short	13
	.short	16
	.short	17
	.short	13
	.short	10
	.short	8
	.short	6
	.short	5
	.short	5
	.short	6
	.short	7
	.short	9
	.short	11
	.short	12
	.short	12
	.short	10
	.short	8
	.short	8
	.short	7
	.short	7
	.short	9
	.short	10
	.short	13
	.short	17
	.short	15
	.short	13
	.short	12
	.short	12
	.short	12
	.short	14
	.short	17
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
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	38
	.short	30
	.short	24
	.short	19
	.short	14
	.short	12
	.short	11
	.short	13
	.short	15
	.short	20
	.short	24
	.short	28
	.short	26
	.short	23
	.short	19
	.short	17
	.short	16
	.short	17
	.short	22
	.short	28
	.short	35
	.short	44
	.short	39
	.short	30
	.short	28
	.short	27
	.short	28
	.short	31
	.short	38
	.short	65
	.short	52
	.short	41
	.short	32
	.short	23
	.short	20
	.short	19
	.short	21
	.short	26
	.short	34
	.short	42
	.short	47
	.short	45
	.short	39
	.short	32
	.short	29
	.short	27
	.short	28
	.short	38
	.short	47
	.short	60
	.short	75
	.short	67
	.short	51
	.short	47
	.short	46
	.short	48
	.short	54
	.short	65
	.short	84
	.short	67
	.short	53
	.short	42
	.short	30
	.short	26
	.short	24
	.short	28
	.short	33
	.short	45
	.short	54
	.short	61
	.short	59
	.short	50
	.short	42
	.short	38
	.short	35
	.short	37
	.short	50
	.short	62
	.short	78
	.short	97
	.short	87
	.short	66
	.short	61
	.short	59
	.short	63
	.short	70
	.short	84
	.short	97
	.short	78
	.short	61
	.short	48
	.short	35
	.short	30
	.short	28
	.short	32
	.short	39
	.short	51
	.short	63
	.short	71
	.short	68
	.short	58
	.short	49
	.short	44
	.short	41
	.short	43
	.short	57
	.short	71
	.short	90
	.short	112
	.short	100
	.short	76
	.short	71
	.short	68
	.short	73
	.short	81
	.short	97
	.short	105
	.short	84
	.short	66
	.short	52
	.short	38
	.short	32
	.short	30
	.short	35
	.short	42
	.short	55
	.short	67
	.short	76
	.short	73
	.short	62
	.short	52
	.short	47
	.short	44
	.short	46
	.short	62
	.short	77
	.short	97
	.short	121
	.short	108
	.short	82
	.short	76
	.short	74
	.short	78
	.short	87
	.short	105
	.short	108
	.short	86
	.short	68
	.short	53
	.short	39
	.short	33
	.short	31
	.short	36
	.short	43
	.short	57
	.short	70
	.short	79
	.short	75
	.short	64
	.short	54
	.short	49
	.short	46
	.short	47
	.short	64
	.short	79
	.short	100
	.short	125
	.short	111
	.short	85
	.short	79
	.short	76
	.short	81
	.short	90
	.short	108
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
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	49
	.short	40
	.short	31
	.short	24
	.short	18
	.short	15
	.short	14
	.short	16
	.short	20
	.short	26
	.short	32
	.short	36
	.short	35
	.short	29
	.short	25
	.short	22
	.short	21
	.short	22
	.short	29
	.short	35
	.short	44
	.short	55
	.short	49
	.short	39
	.short	36
	.short	35
	.short	37
	.short	41
	.short	49
	.short	85
	.short	68
	.short	53
	.short	42
	.short	31
	.short	26
	.short	24
	.short	28
	.short	34
	.short	45
	.short	55
	.short	62
	.short	59
	.short	50
	.short	42
	.short	38
	.short	36
	.short	37
	.short	50
	.short	61
	.short	76
	.short	95
	.short	84
	.short	66
	.short	62
	.short	60
	.short	63
	.short	70
	.short	85
	.short	110
	.short	88
	.short	69
	.short	54
	.short	40
	.short	34
	.short	32
	.short	36
	.short	44
	.short	58
	.short	71
	.short	80
	.short	77
	.short	66
	.short	55
	.short	50
	.short	46
	.short	48
	.short	65
	.short	79
	.short	99
	.short	123
	.short	110
	.short	86
	.short	80
	.short	78
	.short	82
	.short	91
	.short	110
	.short	127
	.short	102
	.short	80
	.short	63
	.short	46
	.short	39
	.short	37
	.short	42
	.short	50
	.short	67
	.short	82
	.short	93
	.short	89
	.short	76
	.short	63
	.short	57
	.short	54
	.short	56
	.short	75
	.short	91
	.short	114
	.short	142
	.short	127
	.short	99
	.short	93
	.short	90
	.short	95
	.short	106
	.short	127
	.short	137
	.short	110
	.short	86
	.short	68
	.short	49
	.short	42
	.short	40
	.short	45
	.short	54
	.short	73
	.short	88
	.short	100
	.short	96
	.short	82
	.short	68
	.short	62
	.short	58
	.short	60
	.short	81
	.short	98
	.short	123
	.short	153
	.short	136
	.short	107
	.short	100
	.short	96
	.short	102
	.short	114
	.short	137
	.short	141
	.short	113
	.short	88
	.short	70
	.short	51
	.short	43
	.short	41
	.short	47
	.short	56
	.short	75
	.short	91
	.short	103
	.short	99
	.short	84
	.short	71
	.short	64
	.short	60
	.short	62
	.short	83
	.short	101
	.short	126
	.short	158
	.short	141
	.short	111
	.short	103
	.short	99
	.short	105
	.short	117
	.short	141
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
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	55
	.short	44
	.short	35
	.short	27
	.short	20
	.short	17
	.short	16
	.short	18
	.short	22
	.short	29
	.short	36
	.short	40
	.short	39
	.short	33
	.short	28
	.short	25
	.short	23
	.short	24
	.short	30
	.short	36
	.short	47
	.short	58
	.short	52
	.short	43
	.short	40
	.short	39
	.short	41
	.short	46
	.short	55
	.short	95
	.short	76
	.short	59
	.short	47
	.short	34
	.short	29
	.short	27
	.short	31
	.short	38
	.short	50
	.short	61
	.short	69
	.short	66
	.short	56
	.short	47
	.short	43
	.short	40
	.short	42
	.short	51
	.short	62
	.short	80
	.short	100
	.short	89
	.short	74
	.short	69
	.short	67
	.short	71
	.short	79
	.short	95
	.short	123
	.short	99
	.short	77
	.short	61
	.short	44
	.short	38
	.short	36
	.short	41
	.short	49
	.short	65
	.short	79
	.short	90
	.short	86
	.short	73
	.short	62
	.short	56
	.short	52
	.short	54
	.short	66
	.short	81
	.short	104
	.short	129
	.short	115
	.short	96
	.short	90
	.short	87
	.short	92
	.short	102
	.short	123
	.short	142
	.short	114
	.short	89
	.short	70
	.short	51
	.short	44
	.short	41
	.short	47
	.short	56
	.short	75
	.short	91
	.short	103
	.short	99
	.short	85
	.short	71
	.short	64
	.short	60
	.short	62
	.short	77
	.short	94
	.short	120
	.short	149
	.short	133
	.short	111
	.short	103
	.short	100
	.short	106
	.short	118
	.short	142
	.short	153
	.short	123
	.short	96
	.short	76
	.short	55
	.short	47
	.short	44
	.short	51
	.short	61
	.short	81
	.short	99
	.short	112
	.short	107
	.short	91
	.short	76
	.short	69
	.short	65
	.short	67
	.short	82
	.short	101
	.short	129
	.short	161
	.short	144
	.short	120
	.short	112
	.short	108
	.short	114
	.short	127
	.short	153
	.short	158
	.short	126
	.short	99
	.short	78
	.short	57
	.short	48
	.short	46
	.short	52
	.short	63
	.short	84
	.short	102
	.short	115
	.short	110
	.short	94
	.short	79
	.short	71
	.short	67
	.short	69
	.short	85
	.short	104
	.short	133
	.short	166
	.short	148
	.short	124
	.short	115
	.short	111
	.short	118
	.short	131
	.short	158
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
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	58
	.short	47
	.short	36
	.short	29
	.short	21
	.short	18
	.short	17
	.short	19
	.short	23
	.short	31
	.short	37
	.short	42
	.short	41
	.short	35
	.short	29
	.short	26
	.short	25
	.short	26
	.short	30
	.short	36
	.short	47
	.short	58
	.short	52
	.short	46
	.short	42
	.short	41
	.short	43
	.short	48
	.short	58
	.short	100
	.short	80
	.short	62
	.short	49
	.short	36
	.short	31
	.short	29
	.short	33
	.short	40
	.short	53
	.short	64
	.short	73
	.short	70
	.short	59
	.short	50
	.short	45
	.short	42
	.short	44
	.short	51
	.short	62
	.short	80
	.short	100
	.short	89
	.short	78
	.short	73
	.short	70
	.short	74
	.short	83
	.short	100
	.short	129
	.short	104
	.short	81
	.short	64
	.short	47
	.short	40
	.short	37
	.short	43
	.short	51
	.short	69
	.short	83
	.short	94
	.short	90
	.short	77
	.short	65
	.short	58
	.short	55
	.short	57
	.short	66
	.short	81
	.short	104
	.short	129
	.short	115
	.short	101
	.short	94
	.short	91
	.short	97
	.short	108
	.short	129
	.short	149
	.short	120
	.short	94
	.short	74
	.short	54
	.short	46
	.short	43
	.short	50
	.short	59
	.short	79
	.short	96
	.short	109
	.short	104
	.short	89
	.short	75
	.short	68
	.short	63
	.short	66
	.short	77
	.short	94
	.short	120
	.short	149
	.short	133
	.short	117
	.short	109
	.short	105
	.short	112
	.short	124
	.short	149
	.short	161
	.short	129
	.short	101
	.short	80
	.short	58
	.short	49
	.short	47
	.short	53
	.short	64
	.short	85
	.short	104
	.short	117
	.short	113
	.short	96
	.short	81
	.short	73
	.short	68
	.short	71
	.short	82
	.short	101
	.short	129
	.short	161
	.short	144
	.short	126
	.short	117
	.short	113
	.short	120
	.short	134
	.short	161
	.short	166
	.short	133
	.short	104
	.short	82
	.short	60
	.short	51
	.short	48
	.short	55
	.short	66
	.short	88
	.short	107
	.short	121
	.short	116
	.short	99
	.short	83
	.short	75
	.short	70
	.short	73
	.short	85
	.short	104
	.short	133
	.short	166
	.short	148
	.short	130
	.short	121
	.short	117
	.short	124
	.short	138
	.short	166
	.space	2
	.type	u32DefaultEn, %object
	.size	u32DefaultEn, 4
u32DefaultEn:
	.word	1
	.type	u32DefaultStretch, %object
	.size	u32DefaultStretch, 4
u32DefaultStretch:
	.word	1
	.type	u32DefaultCliprange, %object
	.size	u32DefaultCliprange, 4
u32DefaultCliprange:
	.word	1
	.type	u32DefaultLumaGain, %object
	.size	u32DefaultLumaGain, 4
u32DefaultLumaGain:
	.word	112
	.type	u32DefaultHueGain, %object
	.size	u32DefaultHueGain, 4
u32DefaultHueGain:
	.word	112
	.type	u32DefaultSatGain, %object
	.size	u32DefaultSatGain, 4
u32DefaultSatGain:
	.word	112
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"pointer is NULL!\012\000"
	.space	2
.LC1:
	.ascii	"pstColorParam is NULL!\012\000"
.LC2:
	.ascii	"[%d]Color Enhance Mode Set error!\012\000"
	.space	1
.LC3:
	.ascii	"%s:pstColorParam is Null poniter!\012\000"
	.space	1
.LC4:
	.ascii	"PQ_MNG_SetColorEnhanceMode failure\012\000"
.LC5:
	.ascii	"PQ_HAL_SetACMParam failure\012\000"
.LC6:
	.ascii	"[%d]Flesh tone level range error!\012\000"
	.space	1
.LC7:
	.ascii	"[%d]Source mode unknown!\012\000"
	.space	2
.LC8:
	.ascii	"PQ_MNG_SetFleshToneLevel failure\012\000"
	.space	2
.LC9:
	.ascii	"%d:ColorGainLevel is over range!\012\000"
	.space	2
.LC10:
	.ascii	"%s:pstAcmModeRecmd is Null poniter!\012\000"
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	sg_enColorSpecModeType, %object
	.size	sg_enColorSpecModeType, 4
sg_enColorSpecModeType:
	.space	4
	.type	sg_pstPqParam, %object
	.size	sg_pstPqParam, 4
sg_pstPqParam:
	.space	4
	.type	sg_pstAcmCoef, %object
	.size	sg_pstAcmCoef, 4
sg_pstAcmCoef:
	.space	4
	.type	sg_bColorInitial, %object
	.size	sg_bColorInitial, 4
sg_bColorInitial:
	.space	4
	.type	u32DefaultDbgEn, %object
	.size	u32DefaultDbgEn, 4
u32DefaultDbgEn:
	.space	4
	.type	u32DefaultCliporwrap, %object
	.size	u32DefaultCliporwrap, 4
u32DefaultCliporwrap:
	.space	4
	.type	u32DefaultCbcrthr, %object
	.size	u32DefaultCbcrthr, 4
u32DefaultCbcrthr:
	.space	4
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
