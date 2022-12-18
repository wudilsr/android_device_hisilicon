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
	.file	"pq_hal_acm.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_hal_acm)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/hal/hi3798mv100/.pq_hal_acm.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_acm.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_acm.o -O2 -Wall -Wundef
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
	.global	PQ_HAL_GetACMEnableFlag
	.type	PQ_HAL_GetACMEnableFlag, %function
PQ_HAL_GetACMEnableFlag:
	.fnstart
.LFB1398:
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
	ldr	r3, [r1, #0]	@ sg_bACMEnableFlag, sg_bACMEnableFlag
	str	r3, [r0, #0]	@ sg_bACMEnableFlag,* bOnOff
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_HAL_GetACMEnableFlag, .-PQ_HAL_GetACMEnableFlag
	.align	2
	.global	PQ_HAL_SetACMHueTbl
	.type	PQ_HAL_SetACMHueTbl, %function
PQ_HAL_SetACMHueTbl:
	.fnstart
.LFB1412:
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
	subs	r1, r0, #0	@ pstColorData, pstColorData
	beq	.L8	@,
	movw	r3, #:lower16:.LANCHOR2	@ tmp139,
	movt	r3, #:upper16:.LANCHOR2	@ tmp139,
	movw	r2, #2030	@,
	ldr	lr, [r3, #0]	@ sg_pstAcmLut, sg_pstAcmLut
	add	r0, lr, #2016	@, sg_pstAcmLut,
	add	r0, r0, #14	@,,
	bl	memcpy	@
	mov	r0, #0	@ D.35832,
.L5:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L8:
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	movw	r2, #:lower16:.LANCHOR1	@,
	movw	r3, #510	@,
	movt	r2, #:upper16:.LANCHOR1	@,
	movw	ip, #:lower16:.LC0	@ tmp138,
	movt	ip, #:upper16:.LC0	@ tmp138,
	str	ip, [sp, #0]	@ tmp138,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35832,
	b	.L5	@
	.fnend
	.size	PQ_HAL_SetACMHueTbl, .-PQ_HAL_SetACMHueTbl
	.align	2
	.global	PQ_HAL_SetACMLumaTbl
	.type	PQ_HAL_SetACMLumaTbl, %function
PQ_HAL_SetACMLumaTbl:
	.fnstart
.LFB1411:
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
	subs	r1, r0, #0	@ pstColorData, pstColorData
	beq	.L13	@,
	movw	r3, #:lower16:.LANCHOR2	@ tmp140,
	movt	r3, #:upper16:.LANCHOR2	@ tmp140,
	movw	r2, #2030	@,
	ldr	r0, [r3, #0]	@, sg_pstAcmLut
	bl	memcpy	@
	mov	r0, #0	@ D.35820,
.L11:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L13:
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	ldr	r2, .L14	@,
	movw	r3, #498	@,
	movw	ip, #:lower16:.LC0	@ tmp139,
	movt	ip, #:upper16:.LC0	@ tmp139,
	str	ip, [sp, #0]	@ tmp139,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35820,
	b	.L11	@
.L15:
	.align	2
.L14:
	.word	.LANCHOR1+20
	.fnend
	.size	PQ_HAL_SetACMLumaTbl, .-PQ_HAL_SetACMLumaTbl
	.align	2
	.global	PQ_HAL_GetACMSatTbl
	.type	PQ_HAL_GetACMSatTbl, %function
PQ_HAL_GetACMSatTbl:
	.fnstart
.LFB1410:
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
	cmp	r0, #0	@ pstColorData,
	beq	.L20	@,
	movw	r3, #:lower16:.LANCHOR2	@ tmp140,
	movt	r3, #:upper16:.LANCHOR2	@ tmp140,
	movw	r2, #2030	@,
	ldr	lr, [r3, #0]	@ sg_pstAcmLut, sg_pstAcmLut
	add	r1, lr, #4048	@, sg_pstAcmLut,
	add	r1, r1, #12	@,,
	bl	memcpy	@
	mov	r0, #0	@ D.35808,
.L18:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L20:
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	ldr	r2, .L21	@,
	movw	r3, #486	@,
	movw	ip, #:lower16:.LC0	@ tmp139,
	movt	ip, #:upper16:.LC0	@ tmp139,
	str	ip, [sp, #0]	@ tmp139,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35808,
	b	.L18	@
.L22:
	.align	2
.L21:
	.word	.LANCHOR1+44
	.fnend
	.size	PQ_HAL_GetACMSatTbl, .-PQ_HAL_GetACMSatTbl
	.align	2
	.global	PQ_HAL_GetACMHueTbl
	.type	PQ_HAL_GetACMHueTbl, %function
PQ_HAL_GetACMHueTbl:
	.fnstart
.LFB1409:
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
	cmp	r0, #0	@ pstColorData,
	beq	.L27	@,
	movw	r3, #:lower16:.LANCHOR2	@ tmp140,
	movt	r3, #:upper16:.LANCHOR2	@ tmp140,
	movw	r2, #2030	@,
	ldr	lr, [r3, #0]	@ sg_pstAcmLut, sg_pstAcmLut
	add	r1, lr, #2016	@, sg_pstAcmLut,
	add	r1, r1, #14	@,,
	bl	memcpy	@
	mov	r0, #0	@ D.35796,
.L25:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L27:
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	ldr	r2, .L28	@,
	movw	r3, #474	@,
	movw	ip, #:lower16:.LC0	@ tmp139,
	movt	ip, #:upper16:.LC0	@ tmp139,
	str	ip, [sp, #0]	@ tmp139,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35796,
	b	.L25	@
.L29:
	.align	2
.L28:
	.word	.LANCHOR1+64
	.fnend
	.size	PQ_HAL_GetACMHueTbl, .-PQ_HAL_GetACMHueTbl
	.align	2
	.global	PQ_HAL_GetACMLumaTbl
	.type	PQ_HAL_GetACMLumaTbl, %function
PQ_HAL_GetACMLumaTbl:
	.fnstart
.LFB1408:
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
	cmp	r0, #0	@ pstColorData,
	beq	.L34	@,
	movw	r3, #:lower16:.LANCHOR2	@ tmp140,
	movt	r3, #:upper16:.LANCHOR2	@ tmp140,
	movw	r2, #2030	@,
	ldr	r1, [r3, #0]	@, sg_pstAcmLut
	bl	memcpy	@
	mov	r0, #0	@ D.35784,
.L32:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L34:
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	ldr	r2, .L35	@,
	movw	r3, #461	@,
	movw	ip, #:lower16:.LC0	@ tmp139,
	movt	ip, #:upper16:.LC0	@ tmp139,
	str	ip, [sp, #0]	@ tmp139,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35784,
	b	.L32	@
.L36:
	.align	2
.L35:
	.word	.LANCHOR1+84
	.fnend
	.size	PQ_HAL_GetACMLumaTbl, .-PQ_HAL_GetACMLumaTbl
	.align	2
	.global	PQ_HAL_GetACMParam
	.type	PQ_HAL_GetACMParam, %function
PQ_HAL_GetACMParam:
	.fnstart
.LFB1395:
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
	movw	r3, #:lower16:.LANCHOR2	@ tmp137,
	movt	r3, #:upper16:.LANCHOR2	@ tmp137,
	ldr	r1, [r3, #0]	@ sg_pstAcmLut.428, sg_pstAcmLut
	cmp	r1, #0	@ sg_pstAcmLut.428,
	beq	.L41	@,
	movw	r2, #6090	@,
	bl	memcpy	@
	mov	r0, #0	@ D.35539,
.L39:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L41:
	mov	r0, #1	@,
	add	r1, r1, #41	@,,
	ldr	r2, .L42	@,
	mov	r3, #183	@,
	movw	ip, #:lower16:.LC1	@ tmp140,
	movt	ip, #:upper16:.LC1	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35539,
	b	.L39	@
.L43:
	.align	2
.L42:
	.word	.LANCHOR1+108
	.fnend
	.size	PQ_HAL_GetACMParam, .-PQ_HAL_GetACMParam
	.align	2
	.global	PQ_HAL_GetACMGain
	.type	PQ_HAL_GetACMGain, %function
PQ_HAL_GetACMGain:
	.fnstart
.LFB1405:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #28
	sub	sp, sp, #28	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #1	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	bls	.L45	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L48	@,
	movw	r3, #405	@,
	movw	ip, #:lower16:.LC2	@ tmp142,
	movt	ip, #:upper16:.LC2	@ tmp142,
	str	ip, [sp, #0]	@ tmp142,
	bl	HI_LogOut	@
.L47:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L45:
	str	r1, [fp, #-24]	@,
	str	r2, [fp, #-28]	@,
	str	r3, [fp, #-32]	@,
	bl	PQ_HAL_GetVdpReg	@
	add	ip, r0, #16640	@ tmp144,,
	add	r0, ip, #164	@ tmp144, tmp144,
	add	r0, r0, r4, asl #11	@,, tmp144, u32ChId,
	bl	PQ_HAL_RegRead	@
	ldr	r3, [fp, #-24]	@,
	ubfx	r4, r0, #20, #10	@ tmp148, D.35731,,
	str	r4, [r3, #0]	@ tmp148,* pu32Luma
	ldr	r2, [fp, #-28]	@,
	ubfx	r1, r0, #10, #10	@ tmp150, D.35731,,
	mov	ip, r0, asl #22	@ tmp152, D.35731,
	str	r1, [r2, #0]	@ tmp150,* pu32Hue
	mov	r0, ip, lsr #22	@ tmp152, tmp152,
	ldr	r3, [fp, #-32]	@,
	str	r0, [r3, #0]	@ tmp152,* pu32Sat
	b	.L47	@
.L49:
	.align	2
.L48:
	.word	.LANCHOR1+128
	.fnend
	.size	PQ_HAL_GetACMGain, .-PQ_HAL_GetACMGain
	.align	2
	.global	PQ_HAL_UpdatACMCoef
	.type	PQ_HAL_UpdatACMCoef, %function
PQ_HAL_UpdatACMCoef:
	.fnstart
.LFB1407:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #12
	sub	sp, sp, #12	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #1	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	bls	.L51	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L54	@,
	mov	r3, #444	@,
	movw	ip, #:lower16:.LC2	@ tmp140,
	movt	ip, #:upper16:.LC2	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
.L53:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L51:
	bl	PQ_HAL_GetVdpReg	@
	add	r1, r0, #16384	@ tmp142,,
	add	r0, r1, #24	@ tmp142, tmp142,
	add	r4, r0, r4, asl #11	@, D.35772, tmp142, u32ChId,
	mov	r0, r4	@, D.35772
	bl	PQ_HAL_RegRead	@
	orr	r1, r0, #1	@ VP0_PARAUP,,
	mov	r0, r4	@, D.35772
	bl	PQ_HAL_RegWrite	@
	b	.L53	@
.L55:
	.align	2
.L54:
	.word	.LANCHOR1+148
	.fnend
	.size	PQ_HAL_UpdatACMCoef, .-PQ_HAL_UpdatACMCoef
	.align	2
	.global	PQ_HAL_SetACMGain
	.type	PQ_HAL_SetACMGain, %function
PQ_HAL_SetACMGain:
	.fnstart
.LFB1404:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #28
	sub	sp, sp, #28	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #1	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	bls	.L57	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L60	@,
	mov	r3, #384	@,
	movw	ip, #:lower16:.LC2	@ tmp143,
	movt	ip, #:upper16:.LC2	@ tmp143,
	str	ip, [sp, #0]	@ tmp143,
	bl	HI_LogOut	@
.L59:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L57:
	str	r1, [fp, #-24]	@,
	str	r2, [fp, #-28]	@,
	str	r3, [fp, #-32]	@,
	bl	PQ_HAL_GetVdpReg	@
	add	ip, r0, #16640	@ tmp145,,
	add	r0, ip, #164	@ tmp145, tmp145,
	add	r4, r0, r4, asl #11	@, D.35703, tmp145, u32ChId,
	mov	r0, r4	@, D.35703
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-24]	@,
	ldr	r2, [fp, #-28]	@,
	ldr	r3, [fp, #-32]	@,
	mov	ip, r0	@ VP0_ACM_ADJ,
	bfi	ip, r1, #20, #10	@ VP0_ACM_ADJ, u32Luma,,
	bfi	ip, r2, #10, #10	@ VP0_ACM_ADJ, u32Hue,,
	mov	r0, r4	@, D.35703
	bfi	ip, r3, #0, #10	@ VP0_ACM_ADJ, u32Sat,,
	mov	r1, ip	@, VP0_ACM_ADJ
	bl	PQ_HAL_RegWrite	@
	b	.L59	@
.L61:
	.align	2
.L60:
	.word	.LANCHOR1+168
	.fnend
	.size	PQ_HAL_SetACMGain, .-PQ_HAL_SetACMGain
	.align	2
	.global	PQ_HAL_SetACMCliporWrap
	.type	PQ_HAL_SetACMCliporWrap, %function
PQ_HAL_SetACMCliporWrap:
	.fnstart
.LFB1403:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #20
	sub	sp, sp, #20	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #1	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	bls	.L63	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L66	@,
	movw	r3, #365	@,
	movw	ip, #:lower16:.LC2	@ tmp141,
	movt	ip, #:upper16:.LC2	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
.L65:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L63:
	str	r1, [fp, #-24]	@,
	bl	PQ_HAL_GetVdpReg	@
	add	r2, r0, #16640	@ tmp143,,
	add	r0, r2, #160	@ tmp143, tmp143,
	add	r4, r0, r4, asl #11	@, D.35680, tmp143, u32ChId,
	mov	r0, r4	@, D.35680
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-24]	@,
	mov	r3, r0	@ VP0_ACM_CTRL,
	bfi	r3, r1, #27, #1	@ VP0_ACM_CTRL, u32Data,,
	mov	r0, r4	@, D.35680
	mov	r1, r3	@, VP0_ACM_CTRL
	bl	PQ_HAL_RegWrite	@
	b	.L65	@
.L67:
	.align	2
.L66:
	.word	.LANCHOR1+188
	.fnend
	.size	PQ_HAL_SetACMCliporWrap, .-PQ_HAL_SetACMCliporWrap
	.align	2
	.global	PQ_HAL_SetACMClipRange
	.type	PQ_HAL_SetACMClipRange, %function
PQ_HAL_SetACMClipRange:
	.fnstart
.LFB1402:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #20
	sub	sp, sp, #20	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #1	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	bls	.L69	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L72	@,
	movw	r3, #346	@,
	movw	ip, #:lower16:.LC2	@ tmp141,
	movt	ip, #:upper16:.LC2	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
.L71:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L69:
	str	r1, [fp, #-24]	@,
	bl	PQ_HAL_GetVdpReg	@
	add	r2, r0, #16640	@ tmp143,,
	add	r0, r2, #160	@ tmp143, tmp143,
	add	r4, r0, r4, asl #11	@, D.35659, tmp143, u32ChId,
	mov	r0, r4	@, D.35659
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-24]	@,
	mov	r3, r0	@ VP0_ACM_CTRL,
	bfi	r3, r1, #28, #1	@ VP0_ACM_CTRL, u32Data,,
	mov	r0, r4	@, D.35659
	mov	r1, r3	@, VP0_ACM_CTRL
	bl	PQ_HAL_RegWrite	@
	b	.L71	@
.L73:
	.align	2
.L72:
	.word	.LANCHOR1+212
	.fnend
	.size	PQ_HAL_SetACMClipRange, .-PQ_HAL_SetACMClipRange
	.align	2
	.global	PQ_HAL_SetACMStretch
	.type	PQ_HAL_SetACMStretch, %function
PQ_HAL_SetACMStretch:
	.fnstart
.LFB1401:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #20
	sub	sp, sp, #20	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #1	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	bls	.L75	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L78	@,
	movw	r3, #327	@,
	movw	ip, #:lower16:.LC2	@ tmp141,
	movt	ip, #:upper16:.LC2	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
.L77:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L75:
	str	r1, [fp, #-24]	@,
	bl	PQ_HAL_GetVdpReg	@
	add	r2, r0, #16640	@ tmp143,,
	add	r0, r2, #160	@ tmp143, tmp143,
	add	r4, r0, r4, asl #11	@, D.35638, tmp143, u32ChId,
	mov	r0, r4	@, D.35638
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-24]	@,
	mov	r3, r0	@ VP0_ACM_CTRL,
	bfi	r3, r1, #29, #1	@ VP0_ACM_CTRL, u32Data,,
	mov	r0, r4	@, D.35638
	mov	r1, r3	@, VP0_ACM_CTRL
	bl	PQ_HAL_RegWrite	@
	b	.L77	@
.L79:
	.align	2
.L78:
	.word	.LANCHOR1+236
	.fnend
	.size	PQ_HAL_SetACMStretch, .-PQ_HAL_SetACMStretch
	.align	2
	.global	PQ_HAL_SetACMCbcrThd
	.type	PQ_HAL_SetACMCbcrThd, %function
PQ_HAL_SetACMCbcrThd:
	.fnstart
.LFB1400:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #20
	sub	sp, sp, #20	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #1	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	bls	.L81	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L84	@,
	mov	r3, #308	@,
	movw	ip, #:lower16:.LC2	@ tmp141,
	movt	ip, #:upper16:.LC2	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
.L83:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L81:
	str	r1, [fp, #-24]	@,
	bl	PQ_HAL_GetVdpReg	@
	add	r2, r0, #16640	@ tmp143,,
	add	r0, r2, #160	@ tmp143, tmp143,
	add	r4, r0, r4, asl #11	@, D.35618, tmp143, u32ChId,
	mov	r0, r4	@, D.35618
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-24]	@,
	mov	r3, r0	@ VP0_ACM_CTRL,
	bfi	r3, r1, #0, #8	@ VP0_ACM_CTRL, u32Data,,
	mov	r0, r4	@, D.35618
	mov	r1, r3	@, VP0_ACM_CTRL
	bl	PQ_HAL_RegWrite	@
	b	.L83	@
.L85:
	.align	2
.L84:
	.word	.LANCHOR1+260
	.fnend
	.size	PQ_HAL_SetACMCbcrThd, .-PQ_HAL_SetACMCbcrThd
	.align	2
	.global	PQ_HAL_ACMDemoMode
	.type	PQ_HAL_ACMDemoMode, %function
PQ_HAL_ACMDemoMode:
	.fnstart
.LFB1399:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #20
	sub	sp, sp, #20	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #1	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	bls	.L87	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L90	@,
	movw	r3, #289	@,
	movw	ip, #:lower16:.LC2	@ tmp141,
	movt	ip, #:upper16:.LC2	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
.L89:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L87:
	str	r1, [fp, #-24]	@,
	bl	PQ_HAL_GetVdpReg	@
	add	r2, r0, #16640	@ tmp143,,
	add	r0, r2, #160	@ tmp143, tmp143,
	add	r4, r0, r4, asl #11	@, D.35597, tmp143, u32ChId,
	mov	r0, r4	@, D.35597
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-24]	@,
	mov	r3, r0	@ VP0_ACM_CTRL,
	bfi	r3, r1, #30, #1	@ VP0_ACM_CTRL, bOnOff,,
	mov	r0, r4	@, D.35597
	mov	r1, r3	@, VP0_ACM_CTRL
	bl	PQ_HAL_RegWrite	@
	b	.L89	@
.L91:
	.align	2
.L90:
	.word	.LANCHOR1+284
	.fnend
	.size	PQ_HAL_ACMDemoMode, .-PQ_HAL_ACMDemoMode
	.align	2
	.global	PQ_HAL_DisableACM
	.type	PQ_HAL_DisableACM, %function
PQ_HAL_DisableACM:
	.fnstart
.LFB1397:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #12
	sub	sp, sp, #12	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #1	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	bls	.L93	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L96	@,
	mov	r3, #240	@,
	movw	ip, #:lower16:.LC2	@ tmp140,
	movt	ip, #:upper16:.LC2	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
.L95:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L93:
	bl	PQ_HAL_GetVdpReg	@
	add	ip, r0, #16640	@ tmp142,,
	add	r0, ip, #160	@ tmp142, tmp142,
	add	r4, r0, r4, asl #11	@, D.35573, tmp142, u32ChId,
	mov	r0, r4	@, D.35573
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ VP0_ACM_CTRL,
	mov	r0, r4	@, D.35573
	bic	r1, r1, #-2147483648	@, VP0_ACM_CTRL,
	bl	PQ_HAL_RegWrite	@
	movw	r3, #:lower16:.LANCHOR0	@ tmp144,
	movt	r3, #:upper16:.LANCHOR0	@ tmp144,
	mov	r2, #0	@ tmp145,
	str	r2, [r3, #0]	@ tmp145, sg_bACMEnableFlag
	b	.L95	@
.L97:
	.align	2
.L96:
	.word	.LANCHOR1+304
	.fnend
	.size	PQ_HAL_DisableACM, .-PQ_HAL_DisableACM
	.align	2
	.global	PQ_HAL_EnableACM
	.type	PQ_HAL_EnableACM, %function
PQ_HAL_EnableACM:
	.fnstart
.LFB1396:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #12
	sub	sp, sp, #12	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #1	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	bls	.L99	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L102	@,
	mov	r3, #209	@,
	movw	ip, #:lower16:.LC2	@ tmp140,
	movt	ip, #:upper16:.LC2	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
.L101:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L99:
	bl	PQ_HAL_GetVdpReg	@
	add	r1, r0, #16640	@ tmp142,,
	add	r0, r1, #160	@ tmp142, tmp142,
	add	r4, r0, r4, asl #11	@, D.35555, tmp142, u32ChId,
	mov	r0, r4	@, D.35555
	bl	PQ_HAL_RegRead	@
	orr	r1, r0, #-2147483648	@ VP0_ACM_CTRL,,
	mov	r0, r4	@, D.35555
	bl	PQ_HAL_RegWrite	@
	movw	r3, #:lower16:.LANCHOR0	@ tmp145,
	movt	r3, #:upper16:.LANCHOR0	@ tmp145,
	mov	r2, #1	@ tmp146,
	str	r2, [r3, #0]	@ tmp146, sg_bACMEnableFlag
	b	.L101	@
.L103:
	.align	2
.L102:
	.word	.LANCHOR1+324
	.fnend
	.size	PQ_HAL_EnableACM, .-PQ_HAL_EnableACM
	.align	2
	.global	PQ_HAL_SetACMParam
	.type	PQ_HAL_SetACMParam, %function
PQ_HAL_SetACMParam:
	.fnstart
.LFB1394:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #20
	sub	sp, sp, #20	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	subs	sl, r0, #0	@ pstColorData, pstColorData
	beq	.L114	@,
	movw	r4, #:lower16:kmalloc_caches	@ tmp152,
	movt	r4, #:upper16:kmalloc_caches	@ tmp152,
	mov	r1, #32	@,
	movw	r2, #4084	@,
	ldr	r0, [r4, #48]	@, kmalloc_caches
	bl	kmem_cache_alloc_trace	@
	subs	r8, r0, #0	@ D.36036,
	beq	.L115	@,
	mov	r1, #32	@,
	movw	r2, #4060	@,
	ldr	r0, [r4, #48]	@, kmalloc_caches
	bl	kmem_cache_alloc_trace	@
	mov	r1, #32	@,
	movw	r2, #4060	@,
	mov	r6, r0	@ D.36137,
	ldr	r0, [r4, #48]	@, kmalloc_caches
	bl	kmem_cache_alloc_trace	@
	mov	r1, #32	@,
	movw	r2, #4060	@,
	mov	r5, r0	@ D.36238,
	ldr	r0, [r4, #48]	@, kmalloc_caches
	bl	kmem_cache_alloc_trace	@
	cmp	r6, #0	@ D.36137,
	cmpne	r5, #0	@, D.36238,
	movne	r3, #0	@,
	moveq	r3, #1	@,
	str	r3, [fp, #-48]	@, %sfp
	mov	r7, r0	@ D.36339,
	beq	.L108	@,
	cmp	r0, #0	@ D.36339,
	beq	.L108	@,
	movw	r4, #:lower16:.LANCHOR2	@ tmp173,
	movt	r4, #:upper16:.LANCHOR2	@ tmp173,
	mov	r1, sl	@, pstColorData
	movw	r2, #2030	@,
	ldr	r0, [r4, #0]	@, sg_pstAcmLut
	add	lr, sl, #2016	@ tmp183, pstColorData,
	str	lr, [fp, #-52]	@,
	bl	memcpy	@
	ldr	r2, [fp, #-52]	@,
	add	r9, sl, #4048	@ tmp193, pstColorData,
	ldr	r0, [r4, #0]	@ sg_pstAcmLut, sg_pstAcmLut
	add	r9, r9, #12	@ tmp193, tmp193,
	add	ip, r2, #14	@ tmp183, tmp183,
	movw	r2, #2030	@,
	add	r1, r0, #2016	@, sg_pstAcmLut,
	str	ip, [fp, #-52]	@,
	add	r0, r1, #14	@,,
	mov	r1, ip	@, tmp183
	bl	memcpy	@
	ldr	r3, [r4, #0]	@ sg_pstAcmLut, sg_pstAcmLut
	movw	r2, #2030	@,
	mov	r1, r9	@, tmp193
	add	r0, r3, #4048	@, sg_pstAcmLut,
	add	r0, r0, #12	@,,
	bl	memcpy	@
	mov	r0, r8	@, D.36036
	movw	r1, #4084	@,
	bl	__memzero	@
	mov	r0, r6	@, D.36137
	movw	r1, #4060	@,
	bl	__memzero	@
	mov	r0, r5	@, D.36238
	movw	r1, #4060	@,
	bl	__memzero	@
	mov	r0, r7	@, D.36339
	movw	r1, #4060	@,
	bl	__memzero	@
	mov	r0, sl	@, pstColorData
	mov	r1, r6	@, D.36137
	bl	PQ_HAL_Split_Table	@
	mov	r1, r7	@, D.36339
	mov	r0, r9	@, tmp193
	bl	PQ_HAL_Split_Table	@
	ldr	r1, [fp, #-52]	@,
	mov	r0, r1	@, tmp183
	mov	r1, r5	@, D.36238
	bl	PQ_HAL_Split_Table	@
	mov	r3, r8	@, D.36036
	mov	r1, r7	@, D.36339
	mov	r2, r5	@, D.36238
	mov	r0, r6	@, D.36137
	bl	PQ_HAL_AcmCoefConvert	@
	ldr	r2, [r8, #0]	@, <variable>.u32Size
	add	r1, r8, #4	@, D.36036,
	ldr	r0, [r4, #4]	@, sg_stACMBuffer.u32StartVirAddr
	bl	memcpy	@
	ldr	sl, [r4, #8]	@ D.35528, sg_stACMBuffer.u32StartPhyAddr
	bl	PQ_HAL_GetVdpReg	@
	add	r4, r0, #16384	@ D.36435,,
	add	r4, r4, #20	@ D.36435, D.36435,
	mov	r0, r4	@, D.36435
	bl	PQ_HAL_RegRead	@
	mov	r1, sl	@, D.35528
	mov	r0, r4	@, D.36435
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [fp, #-48]	@, %sfp
	bl	PQ_HAL_UpdatACMCoef	@
	mov	r0, r8	@, D.36036
	bl	kfree	@
	mov	r0, r6	@, D.36137
	bl	kfree	@
	mov	r0, r5	@, D.36238
	bl	kfree	@
	mov	r0, r7	@, D.36339
	bl	kfree	@
	ldr	r0, [fp, #-48]	@ D.35470, %sfp
.L106:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L108:
	cmp	r6, #0	@ D.36137,
	beq	.L110	@,
	mov	r0, r6	@, D.36137
	bl	kfree	@
.L110:
	cmp	r5, #0	@ D.36238,
	beq	.L111	@,
	mov	r0, r5	@, D.36238
	bl	kfree	@
.L111:
	cmp	r7, #0	@ D.36339,
	beq	.L112	@,
	mov	r0, r7	@, D.36339
	bl	kfree	@
.L112:
	mov	r0, r8	@, D.36036
	bl	kfree	@
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L116	@,
	mov	r3, #137	@,
	movw	ip, #:lower16:.LC5	@ tmp172,
	movt	ip, #:upper16:.LC5	@ tmp172,
	str	ip, [sp, #0]	@ tmp172,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35470,
	b	.L106	@
.L114:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L116	@,
	mov	r3, #108	@,
	movw	ip, #:lower16:.LC3	@ tmp151,
	movt	ip, #:upper16:.LC3	@ tmp151,
	str	ip, [sp, #0]	@ tmp151,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35470,
	b	.L106	@
.L115:
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	ldr	r2, .L116	@,
	mov	r3, #113	@,
	movw	lr, #:lower16:.LC4	@ tmp156,
	movt	lr, #:upper16:.LC4	@ tmp156,
	str	lr, [sp, #0]	@ tmp156,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35470,
	b	.L106	@
.L117:
	.align	2
.L116:
	.word	.LANCHOR1+344
	.fnend
	.size	PQ_HAL_SetACMParam, .-PQ_HAL_SetACMParam
	.align	2
	.global	PQ_HAL_SetACMSatTbl
	.type	PQ_HAL_SetACMSatTbl, %function
PQ_HAL_SetACMSatTbl:
	.fnstart
.LFB1413:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #12
	sub	sp, sp, #12	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	subs	r1, r0, #0	@ pstColorData, pstColorData
	beq	.L122	@,
	movw	r4, #:lower16:.LANCHOR2	@ tmp140,
	movt	r4, #:upper16:.LANCHOR2	@ tmp140,
	movw	r2, #2030	@,
	ldr	r3, [r4, #0]	@ sg_pstAcmLut, sg_pstAcmLut
	add	r0, r3, #4048	@, sg_pstAcmLut,
	add	r0, r0, #12	@,,
	bl	memcpy	@
	ldr	r0, [r4, #0]	@, sg_pstAcmLut
	bl	PQ_HAL_SetACMParam	@
.L120:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L122:
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	ldr	r2, .L123	@,
	movw	r3, #522	@,
	movw	ip, #:lower16:.LC0	@ tmp139,
	movt	ip, #:upper16:.LC0	@ tmp139,
	str	ip, [sp, #0]	@ tmp139,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35844,
	b	.L120	@
.L124:
	.align	2
.L123:
	.word	.LANCHOR1+364
	.fnend
	.size	PQ_HAL_SetACMSatTbl, .-PQ_HAL_SetACMSatTbl
	.align	2
	.global	PQ_HAL_InitACM
	.type	PQ_HAL_InitACM, %function
PQ_HAL_InitACM:
	.fnstart
.LFB1393:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #12
	sub	sp, sp, #12	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r4, #:lower16:.LANCHOR2	@ tmp138,
	movt	r4, #:upper16:.LANCHOR2	@ tmp138,
	mov	r1, #12	@,
	add	r5, r4, #4	@ tmp139, tmp138,
	mov	r0, r5	@, tmp139
	bl	__memzero	@
	mov	r1, #0	@,
	movw	r0, #:lower16:.LC6	@,
	mov	r2, #4080	@,
	movt	r0, #:upper16:.LC6	@,
	mov	r3, r1	@,
	str	r5, [sp, #0]	@ tmp139,
	bl	HI_DRV_MMZ_AllocAndMap	@
	subs	r6, r0, #0	@ s32Ret,
	bne	.L130	@,
	ldr	r0, [r4, #4]	@, sg_stACMBuffer.u32StartVirAddr
	mov	r1, #4080	@,
	bl	__memzero	@
	movw	ip, #:lower16:kmalloc_caches	@ tmp148,
	movt	ip, #:upper16:kmalloc_caches	@ tmp148,
	mov	r1, #208	@,
	movw	r2, #6090	@,
	ldr	r0, [ip, #52]	@, kmalloc_caches
	bl	kmem_cache_alloc_trace	@
	cmp	r0, #0	@ D.36451,
	str	r0, [r4, #0]	@ D.36451, sg_pstAcmLut
	beq	.L131	@,
	movw	r1, #6090	@,
	bl	__memzero	@
	mov	r0, r6	@ D.35429, s32Ret
.L127:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L131:
	mov	r1, #41	@,
	ldr	r2, .L132	@,
	mov	r3, #81	@,
	mov	r0, #1	@,
	movw	lr, #:lower16:.LC8	@ tmp153,
	movt	lr, #:upper16:.LC8	@ tmp153,
	str	lr, [sp, #0]	@ tmp153,
	bl	HI_LogOut	@
	mov	r0, r5	@, tmp139
	bl	HI_DRV_MMZ_UnmapAndRelease	@
	mvn	r0, #0	@ D.35429,
	b	.L127	@
.L130:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L132	@,
	mov	r3, #72	@,
	movw	ip, #:lower16:.LC7	@ tmp145,
	movt	ip, #:upper16:.LC7	@ tmp145,
	str	ip, [sp, #0]	@ tmp145,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35429,
	b	.L127	@
.L133:
	.align	2
.L132:
	.word	.LANCHOR1+384
	.fnend
	.size	PQ_HAL_InitACM, .-PQ_HAL_InitACM
	.align	2
	.global	PQ_HAL_DeInitACM
	.type	PQ_HAL_DeInitACM, %function
PQ_HAL_DeInitACM:
	.fnstart
.LFB1392:
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
	movw	r4, #:lower16:.LANCHOR2	@ tmp139,
	movt	r4, #:upper16:.LANCHOR2	@ tmp139,
	movw	r3, #:lower16:.LANCHOR0	@ tmp134,
	movt	r3, #:upper16:.LANCHOR0	@ tmp134,
	mov	r5, #0	@ tmp135,
	ldr	r0, [r4], #4	@, sg_pstAcmLut
	str	r5, [r3, #0]	@ tmp135, sg_bACMEnableFlag
	bl	kfree	@
	mov	r0, r4	@, tmp139
	bl	HI_DRV_MMZ_UnmapAndRelease	@
	mov	r0, r5	@, tmp135
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	PQ_HAL_DeInitACM, .-PQ_HAL_DeInitACM
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.35826, %object
	.size	__func__.35826, 20
__func__.35826:
	.ascii	"PQ_HAL_SetACMHueTbl\000"
	.type	__func__.35814, %object
	.size	__func__.35814, 21
__func__.35814:
	.ascii	"PQ_HAL_SetACMLumaTbl\000"
	.space	3
	.type	__func__.35802, %object
	.size	__func__.35802, 20
__func__.35802:
	.ascii	"PQ_HAL_GetACMSatTbl\000"
	.type	__func__.35790, %object
	.size	__func__.35790, 20
__func__.35790:
	.ascii	"PQ_HAL_GetACMHueTbl\000"
	.type	__func__.35778, %object
	.size	__func__.35778, 21
__func__.35778:
	.ascii	"PQ_HAL_GetACMLumaTbl\000"
	.space	3
	.type	__func__.35532, %object
	.size	__func__.35532, 19
__func__.35532:
	.ascii	"PQ_HAL_GetACMParam\000"
	.space	1
	.type	__func__.35720, %object
	.size	__func__.35720, 18
__func__.35720:
	.ascii	"PQ_HAL_GetACMGain\000"
	.space	2
	.type	__func__.35762, %object
	.size	__func__.35762, 20
__func__.35762:
	.ascii	"PQ_HAL_UpdatACMCoef\000"
	.type	__func__.35693, %object
	.size	__func__.35693, 18
__func__.35693:
	.ascii	"PQ_HAL_SetACMGain\000"
	.space	2
	.type	__func__.35670, %object
	.size	__func__.35670, 24
__func__.35670:
	.ascii	"PQ_HAL_SetACMCliporWrap\000"
	.type	__func__.35649, %object
	.size	__func__.35649, 23
__func__.35649:
	.ascii	"PQ_HAL_SetACMClipRange\000"
	.space	1
	.type	__func__.35628, %object
	.size	__func__.35628, 21
__func__.35628:
	.ascii	"PQ_HAL_SetACMStretch\000"
	.space	3
	.type	__func__.35608, %object
	.size	__func__.35608, 21
__func__.35608:
	.ascii	"PQ_HAL_SetACMCbcrThd\000"
	.space	3
	.type	__func__.35587, %object
	.size	__func__.35587, 19
__func__.35587:
	.ascii	"PQ_HAL_ACMDemoMode\000"
	.space	1
	.type	__func__.35563, %object
	.size	__func__.35563, 18
__func__.35563:
	.ascii	"PQ_HAL_DisableACM\000"
	.space	2
	.type	__func__.35545, %object
	.size	__func__.35545, 17
__func__.35545:
	.ascii	"PQ_HAL_EnableACM\000"
	.space	3
	.type	__func__.35455, %object
	.size	__func__.35455, 19
__func__.35455:
	.ascii	"PQ_HAL_SetACMParam\000"
	.space	1
	.type	__func__.35838, %object
	.size	__func__.35838, 20
__func__.35838:
	.ascii	"PQ_HAL_SetACMSatTbl\000"
	.type	__func__.35411, %object
	.size	__func__.35411, 15
__func__.35411:
	.ascii	"PQ_HAL_InitACM\000"
	.data
	.align	2
.LANCHOR0 = . + 0
	.type	sg_bACMEnableFlag, %object
	.size	sg_bACMEnableFlag, 4
sg_bACMEnableFlag:
	.word	1
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"pstColorData is NULL!\012\000"
	.space	1
.LC1:
	.ascii	"sg_pstAcmLut is NULL!\012\000"
	.space	1
.LC2:
	.ascii	"Error,Select Wrong CHANNEL ID\012\000"
	.space	1
.LC3:
	.ascii	"pointer is NULL!\012\000"
	.space	2
.LC4:
	.ascii	"pAcmBitArray is invaild!\012\000"
	.space	2
.LC5:
	.ascii	"SplitTable is invaild!\012\000"
.LC6:
	.ascii	"PQ_ACM\000"
	.space	1
.LC7:
	.ascii	"PQ_ACM memory allocated failed!\012\000"
	.space	3
.LC8:
	.ascii	"sg_pstAcmLut can not malloc!\012\000"
	.bss
	.align	2
.LANCHOR2 = . + 0
	.type	sg_pstAcmLut, %object
	.size	sg_pstAcmLut, 4
sg_pstAcmLut:
	.space	4
	.type	sg_stACMBuffer, %object
	.size	sg_stACMBuffer, 12
sg_stACMBuffer:
	.space	12
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
