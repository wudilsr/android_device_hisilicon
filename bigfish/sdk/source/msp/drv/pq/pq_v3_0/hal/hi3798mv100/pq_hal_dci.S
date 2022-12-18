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
	.file	"pq_hal_dci.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_hal_dci)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/hal/hi3798mv100/.pq_hal_dci.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_dci.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_dci.o -O2 -Wall -Wundef
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
	.global	PQ_HAL_GetDCIParam
	.type	PQ_HAL_GetDCIParam, %function
PQ_HAL_GetDCIParam:
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
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_HAL_GetDCIParam, .-PQ_HAL_GetDCIParam
	.align	2
	.global	PQ_HAL_GetDCIlevel
	.type	PQ_HAL_GetDCIlevel, %function
PQ_HAL_GetDCIlevel:
	.fnstart
.LFB1401:
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
	bls	.L4	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	movw	r3, #573	@,
	movw	ip, #:lower16:.LC0	@ tmp141,
	movt	ip, #:upper16:.LC0	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
.L6:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4:
	str	r1, [fp, #-24]	@,
	str	r2, [fp, #-28]	@,
	str	r3, [fp, #-32]	@,
	bl	PQ_HAL_GetVdpReg	@
	add	ip, r0, #16640	@ tmp143,,
	add	r3, ip, #44	@ tmp143, tmp143,
	add	r0, r3, r4, asl #11	@,, tmp143, u32ChId,
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-24]	@,
	mov	r4, r0, lsr #26	@ tmp147, D.36058,
	strh	r4, [r1, #0]	@ movhi	@ tmp147,* pu16Gain0
	ldr	r2, [fp, #-28]	@,
	ubfx	ip, r0, #14, #6	@ tmp151, D.36058,,
	ubfx	r0, r0, #20, #6	@ tmp149, D.36058,,
	strh	r0, [r2, #0]	@ movhi	@ tmp149,* pu16Gain1
	ldr	r3, [fp, #-32]	@,
	strh	ip, [r3, #0]	@ movhi	@ tmp151,* pu16Gain2
	b	.L6	@
	.fnend
	.size	PQ_HAL_GetDCIlevel, .-PQ_HAL_GetDCIlevel
	.align	2
	.global	PQ_HAL_GetDCIWgtLut
	.type	PQ_HAL_GetDCIWgtLut, %function
PQ_HAL_GetDCIWgtLut:
	.fnstart
.LFB1405:
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
	subs	r4, r0, #0	@ pstDciCoef, pstDciCoef
	beq	.L12	@,
	ldr	r1, .L13	@,
	mov	r2, #66	@,
	bl	memcpy	@
	mov	r2, #66	@,
	ldr	r1, .L13+4	@,
	add	r0, r4, r2	@, pstDciCoef,
	bl	memcpy	@
	ldr	r1, .L13+8	@,
	mov	r2, #66	@,
	add	r0, r4, #132	@, pstDciCoef,
	bl	memcpy	@
	mov	r0, #0	@,
	add	r3, r4, #202	@, pstDciCoef,
	add	r1, r4, #198	@, pstDciCoef,
	add	r2, r4, #200	@, pstDciCoef,
	bl	PQ_HAL_GetDCIlevel	@
	mov	r0, #0	@ D.36143,
.L10:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L12:
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	ldr	r2, .L13+12	@,
	movw	r3, #699	@,
	movw	ip, #:lower16:.LC1	@ tmp139,
	movt	ip, #:upper16:.LC1	@ tmp139,
	str	ip, [sp, #0]	@ tmp139,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.36143,
	b	.L10	@
.L14:
	.align	2
.L13:
	.word	.LANCHOR1+320
	.word	.LANCHOR1+386
	.word	.LANCHOR1+452
	.word	.LANCHOR0+20
	.fnend
	.size	PQ_HAL_GetDCIWgtLut, .-PQ_HAL_GetDCIWgtLut
	.align	2
	.global	PQ_HAL_GetDCIEnable
	.type	PQ_HAL_GetDCIEnable, %function
PQ_HAL_GetDCIEnable:
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
	bls	.L16	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L19	@,
	mov	r3, #516	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
.L18:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L16:
	str	r1, [fp, #-24]	@,
	bl	PQ_HAL_GetVdpReg	@
	add	r2, r0, #16640	@ tmp142,,
	add	r0, r2, r4, asl #11	@,, tmp142, u32ChId,
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-24]	@,
	mov	r0, r0, lsr #31	@ tmp145,,
	str	r0, [r1, #0]	@ tmp145,* bOnOff
	b	.L18	@
.L20:
	.align	2
.L19:
	.word	.LANCHOR0+40
	.fnend
	.size	PQ_HAL_GetDCIEnable, .-PQ_HAL_GetDCIEnable
	.align	2
	.global	PQ_HAL_SetDCIWindow
	.type	PQ_HAL_SetDCIWindow, %function
PQ_HAL_SetDCIWindow:
	.fnstart
.LFB1403:
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #12
	sub	sp, sp, #12	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #1	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	mov	r5, r1	@ u16HStar, u16HStar
	mov	r6, r2	@ u16HEnd, u16HEnd
	mov	r7, r3	@ u16VStar, u16VStar
	ldrh	r8, [fp, #4]	@ u16VEnd, u16VEnd
	bls	.L22	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L25	@,
	movw	r3, #635	@,
	movw	ip, #:lower16:.LC0	@ tmp150,
	movt	ip, #:upper16:.LC0	@ tmp150,
	str	ip, [sp, #0]	@ tmp150,
	bl	HI_LogOut	@
.L24:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L22:
	bl	PQ_HAL_GetVdpReg	@
	mov	r4, r4, asl #11	@ D.36111, u32ChId,
	add	sl, r0, #16640	@ tmp152,,
	add	r9, sl, #4	@ tmp151, tmp152,
	add	sl, sl, #8	@ tmp153, tmp152,
	add	r9, r4, r9	@ D.36112, D.36111, tmp151
	add	r4, r4, sl	@ D.36119, D.36111, tmp153
	mov	r0, r9	@, D.36112
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ VP0_DCIHPOS,
	bfi	r1, r5, #20, #12	@ VP0_DCIHPOS, u16HStar,,
	bfi	r1, r6, #8, #12	@ VP0_DCIHPOS, u16HEnd,,
	mov	r0, r9	@, D.36112
	bl	PQ_HAL_RegWrite	@
	mov	r0, r4	@, D.36119
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ VP0_DCIVPOS,
	bfi	r1, r7, #20, #12	@ VP0_DCIVPOS, u16VStar,,
	mov	r0, r4	@, D.36119
	bfi	r1, r8, #8, #12	@ VP0_DCIVPOS, u16VEnd,,
	bl	PQ_HAL_RegWrite	@
	movw	r3, #:lower16:.LANCHOR1	@ tmp155,
	movt	r3, #:upper16:.LANCHOR1	@ tmp155,
	mov	ip, #520	@ tmp156,
	movw	r1, #526	@ tmp162,
	movw	r0, #522	@ tmp158,
	mov	r2, #524	@ tmp160,
	strh	r5, [r3, ip]	@ movhi	@ u16HStar, sg_stDciWindow.u16Hstart
	strh	r8, [r3, r1]	@ movhi	@ u16VEnd, sg_stDciWindow.u16Vend
	strh	r6, [r3, r0]	@ movhi	@ u16HEnd, sg_stDciWindow.u16Hend
	strh	r7, [r3, r2]	@ movhi	@ u16VStar, sg_stDciWindow.u16Vstart
	b	.L24	@
.L26:
	.align	2
.L25:
	.word	.LANCHOR0+60
	.fnend
	.size	PQ_HAL_SetDCIWindow, .-PQ_HAL_SetDCIWindow
	.align	2
	.global	PQ_HAL_SetDCIlevel
	.type	PQ_HAL_SetDCIlevel, %function
PQ_HAL_SetDCIlevel:
	.fnstart
.LFB1402:
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
	bls	.L28	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L31	@,
	movw	r3, #603	@,
	movw	ip, #:lower16:.LC0	@ tmp143,
	movt	ip, #:upper16:.LC0	@ tmp143,
	str	ip, [sp, #0]	@ tmp143,
	bl	HI_LogOut	@
.L30:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L28:
	str	r1, [fp, #-24]	@,
	str	r2, [fp, #-28]	@,
	str	r3, [fp, #-32]	@,
	bl	PQ_HAL_GetVdpReg	@
	add	ip, r0, #16640	@ tmp145,,
	add	r0, ip, #44	@ tmp145, tmp145,
	add	r4, r0, r4, asl #11	@, D.36083, tmp145, u32ChId,
	mov	r0, r4	@, D.36083
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-24]	@,
	ldr	r2, [fp, #-28]	@,
	ldr	r3, [fp, #-32]	@,
	mov	ip, r0	@ VP0_DCIGLBGAIN,
	bfi	ip, r1, #26, #6	@ VP0_DCIGLBGAIN, u16Gain0,,
	bfi	ip, r2, #20, #6	@ VP0_DCIGLBGAIN, u16Gain1,,
	mov	r0, r4	@, D.36083
	bfi	ip, r3, #14, #6	@ VP0_DCIGLBGAIN, u16Gain2,,
	mov	r1, ip	@, VP0_DCIGLBGAIN
	bl	PQ_HAL_RegWrite	@
	b	.L30	@
.L32:
	.align	2
.L31:
	.word	.LANCHOR0+80
	.fnend
	.size	PQ_HAL_SetDCIlevel, .-PQ_HAL_SetDCIlevel
	.align	2
	.global	PQ_HAL_EnableDCI
	.type	PQ_HAL_EnableDCI, %function
PQ_HAL_EnableDCI:
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
	bls	.L34	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L37	@,
	mov	r3, #544	@,
	movw	ip, #:lower16:.LC0	@ tmp141,
	movt	ip, #:upper16:.LC0	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
.L36:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L34:
	str	r1, [fp, #-24]	@,
	bl	PQ_HAL_GetVdpReg	@
	add	r0, r0, #16640	@ tmp143,,
	add	r4, r0, r4, asl #11	@, D.36034, tmp143, u32ChId,
	mov	r0, r4	@, D.36034
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-24]	@,
	mov	r3, r0	@ VP0_DCICTRL,
	bfi	r3, r1, #31, #1	@ VP0_DCICTRL, bOnOff,,
	mov	r0, r4	@, D.36034
	mov	r1, r3	@, VP0_DCICTRL
	bl	PQ_HAL_RegWrite	@
	b	.L36	@
.L38:
	.align	2
.L37:
	.word	.LANCHOR0+100
	.fnend
	.size	PQ_HAL_EnableDCI, .-PQ_HAL_EnableDCI
	.align	2
	.global	PQ_HAL_DCIDemoMode
	.type	PQ_HAL_DCIDemoMode, %function
PQ_HAL_DCIDemoMode:
	.fnstart
.LFB1398:
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
	bls	.L40	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L43	@,
	movw	r3, #486	@,
	movw	ip, #:lower16:.LC0	@ tmp141,
	movt	ip, #:upper16:.LC0	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
.L42:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L40:
	str	r1, [fp, #-24]	@,
	bl	PQ_HAL_GetVdpReg	@
	add	r0, r0, #16640	@ tmp143,,
	add	r4, r0, r4, asl #11	@, D.35993, tmp143, u32ChId,
	mov	r0, r4	@, D.35993
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-24]	@,
	mov	r3, r0	@ VP0_DCICTRL,
	bfi	r3, r1, #30, #1	@ VP0_DCICTRL, bOnOff,,
	mov	r0, r4	@, D.35993
	mov	r1, r3	@, VP0_DCICTRL
	bl	PQ_HAL_RegWrite	@
	b	.L42	@
.L44:
	.align	2
.L43:
	.word	.LANCHOR0+120
	.fnend
	.size	PQ_HAL_DCIDemoMode, .-PQ_HAL_DCIDemoMode
	.align	2
	.global	PQ_HAL_SetDCIParam
	.type	PQ_HAL_SetDCIParam, %function
PQ_HAL_SetDCIParam:
	.fnstart
.LFB1397:
	@ args = 0, pretend = 0, frame = 88
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #100
	sub	sp, sp, #100	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #1	@ u32ChId,
	mov	r5, r0	@ u32ChId, u32ChId
	mov	r4, r1	@ pstdciPara, pstdciPara
	bls	.L46	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L49	@,
	mov	r3, #242	@,
	movw	ip, #:lower16:.LC0	@ tmp250,
	movt	ip, #:upper16:.LC0	@ tmp250,
	str	ip, [sp, #0]	@ tmp250,
	bl	HI_LogOut	@
.L48:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L46:
	bl	PQ_HAL_GetVdpReg	@
	mov	r5, r5, asl #11	@ D.35523, u32ChId,
	add	r6, r0, #16640	@ tmp251,,
	add	sl, r5, r6	@ D.35524, D.35523, tmp251
	mov	r0, sl	@, D.35524
	bl	PQ_HAL_RegRead	@
	ldrb	r8, [r4, #5]	@ zero_extendqisi2	@ <variable>.u8DCIHistState, <variable>.u8DCIHistState
	ldrb	r3, [r4, #6]	@ zero_extendqisi2	@ <variable>.u8DCISwCfgEn, <variable>.u8DCISwCfgEn
	ldrb	r9, [r4, #7]	@ zero_extendqisi2	@ <variable>.u8DCIHistLpfEn, <variable>.u8DCIHistLpfEn
	ldrb	ip, [r4, #8]	@ zero_extendqisi2	@ <variable>.u8DCIShiftCtrl, <variable>.u8DCIShiftCtrl
	ldrb	r7, [r4, #9]	@ zero_extendqisi2	@ <variable>.u8DCIOutRange, <variable>.u8DCIOutRange
	ldrb	r2, [r4, #11]	@ zero_extendqisi2	@ <variable>.u8DCICbCrStaEn, <variable>.u8DCICbCrStaEn
	mov	r1, r0	@ VP0_DCICTRL,
	bfi	r1, r8, #17, #1	@ VP0_DCICTRL, <variable>.u8DCIHistState,,
	bfi	r1, r3, #18, #1	@ VP0_DCICTRL, <variable>.u8DCISwCfgEn,,
	mov	r0, sl	@, D.35524
	bfi	r1, r9, #19, #1	@ VP0_DCICTRL, <variable>.u8DCIHistLpfEn,,
	ldrb	sl, [r4, #10]	@ zero_extendqisi2	@ <variable>.u8DCIInRange, <variable>.u8DCIInRange
	bfi	r1, ip, #20, #2	@ VP0_DCICTRL, <variable>.u8DCIShiftCtrl,,
	ldrb	r8, [r4, #12]	@ zero_extendqisi2	@ <variable>.u8DCICbCrCmpEn, <variable>.u8DCICbCrCmpEn
	bfi	r1, r7, #22, #1	@ VP0_DCICTRL, <variable>.u8DCIOutRange,,
	ldrb	r9, [r4, #15]	@ zero_extendqisi2	@ <variable>.u8DCIManAdj, <variable>.u8DCIManAdj
	bfi	r1, sl, #23, #1	@ VP0_DCICTRL, <variable>.u8DCIInRange,,
	ldrb	r3, [r4, #14]	@ zero_extendqisi2	@ <variable>.u8DCIManAdj, <variable>.u8DCIManAdj
	bfi	r1, r2, #24, #1	@ VP0_DCICTRL, <variable>.u8DCICbCrStaEn,,
	ldrb	ip, [r4, #13]	@ zero_extendqisi2	@ <variable>.u8DCIManAdj, <variable>.u8DCIManAdj
	bfi	r1, r8, #25, #1	@ VP0_DCICTRL, <variable>.u8DCICbCrCmpEn,,
	ldrb	r7, [r4, #16]	@ zero_extendqisi2	@ <variable>.u8DCISceneFlg, <variable>.u8DCISceneFlg
	bfi	r1, r9, #26, #1	@ VP0_DCICTRL, <variable>.u8DCIManAdj,,
	ldrb	sl, [r4, #18]	@ zero_extendqisi2	@ <variable>.u8DCIDbgEn, <variable>.u8DCIDbgEn
	bfi	r1, r3, #27, #1	@ VP0_DCICTRL, <variable>.u8DCIManAdj,,
	ldrb	r8, [r4, #19]	@ zero_extendqisi2	@ <variable>.u8DCIEn, <variable>.u8DCIEn
	bfi	r1, ip, #28, #1	@ VP0_DCICTRL, <variable>.u8DCIManAdj,,
	bfi	r1, r7, #29, #1	@ VP0_DCICTRL, <variable>.u8DCISceneFlg,,
	bfi	r1, sl, #30, #1	@ VP0_DCICTRL, <variable>.u8DCIDbgEn,,
	bfi	r1, r8, #31, #1	@ VP0_DCICTRL, <variable>.u8DCIEn,,
	bl	PQ_HAL_RegWrite	@
	add	r2, r6, #4	@ tmp294, tmp251,
	add	r9, r5, r2	@ D.35557, D.35523, tmp294
	mov	r0, r9	@, D.35557
	bl	PQ_HAL_RegRead	@
	ldrh	ip, [r4, #22]	@ <variable>.u16DCIHStart, <variable>.u16DCIHStart
	ldrh	r3, [r4, #20]	@ <variable>.u16DCIHEnd, <variable>.u16DCIHEnd
	mov	r1, r0	@ VP0_DCIHPOS,
	bfi	r1, ip, #20, #12	@ VP0_DCIHPOS, <variable>.u16DCIHStart,,
	bfi	r1, r3, #8, #12	@ VP0_DCIHPOS, <variable>.u16DCIHEnd,,
	mov	r0, r9	@, D.35557
	bl	PQ_HAL_RegWrite	@
	add	r1, r6, #8	@ tmp302, tmp251,
	add	r7, r5, r1	@ D.35566, D.35523, tmp302
	mov	r0, r7	@, D.35566
	bl	PQ_HAL_RegRead	@
	ldrh	sl, [r4, #26]	@ <variable>.u16DCIVStart, <variable>.u16DCIVStart
	ldrh	r8, [r4, #24]	@ <variable>.u16DCIVEnd, <variable>.u16DCIVEnd
	mov	r1, r0	@ VP0_DCIVPOS,
	bfi	r1, sl, #20, #12	@ VP0_DCIVPOS, <variable>.u16DCIVStart,,
	bfi	r1, r8, #8, #12	@ VP0_DCIVPOS, <variable>.u16DCIVEnd,,
	mov	r0, r7	@, D.35566
	bl	PQ_HAL_RegWrite	@
	add	r0, r6, #12	@ tmp310, tmp251,
	add	r9, r5, r0	@ D.35575, D.35523, tmp310
	add	r7, r6, #16	@ tmp321, tmp251,
	add	sl, r5, r7	@ D.35586, D.35523, tmp321
	mov	r0, r9	@, D.35575
	bl	PQ_HAL_RegRead	@
	ldrb	r2, [r4, #30]	@ zero_extendqisi2	@ <variable>.s8DCICbCrStaY, <variable>.s8DCICbCrStaY
	ldrb	ip, [r4, #29]	@ zero_extendqisi2	@ <variable>.s8DCICbCrStaCb, <variable>.s8DCICbCrStaCb
	ldrb	r3, [r4, #28]	@ zero_extendqisi2	@ <variable>.s8DCICbCrStaCr, <variable>.s8DCICbCrStaCr
	mov	r1, r0	@ VP0_DCIHISBLD,
	bfi	r1, r2, #24, #8	@ VP0_DCIHISBLD, <variable>.s8DCICbCrStaY,,
	bfi	r1, ip, #16, #8	@ VP0_DCIHISBLD, <variable>.s8DCICbCrStaCb,,
	mov	r0, r9	@, D.35575
	bfi	r1, r3, #8, #8	@ VP0_DCIHISBLD, <variable>.s8DCICbCrStaCr,,
	bl	PQ_HAL_RegWrite	@
	mov	r0, sl	@, D.35586
	bl	PQ_HAL_RegRead	@
	ldrh	r8, [r4, #32]	@ <variable>.s16DCICbCrStaOft, <variable>.s16DCICbCrStaOft
	mov	r1, r0	@ VP0_DCIHISOFT,
	mov	r0, sl	@, D.35586
	bfi	r1, r8, #23, #9	@ VP0_DCIHISOFT, <variable>.s16DCICbCrStaOft,,
	bl	PQ_HAL_RegWrite	@
	add	r1, r6, #20	@ tmp326, tmp251,
	add	r9, r5, r1	@ D.35594, D.35523, tmp326
	mov	r0, r9	@, D.35594
	bl	PQ_HAL_RegRead	@
	ldrb	r2, [r4, #34]	@ zero_extendqisi2	@ <variable>.u8DCIHistCorTh, <variable>.u8DCIHistCorTh
	ldrb	ip, [r4, #35]	@ zero_extendqisi2	@ <variable>.u8DCIHistCorTh, <variable>.u8DCIHistCorTh
	ldrb	r3, [r4, #36]	@ zero_extendqisi2	@ <variable>.u8DCIHistCorTh, <variable>.u8DCIHistCorTh
	mov	r1, r0	@ VP0_DCIHISCOR,
	bfi	r1, r2, #24, #8	@ VP0_DCIHISCOR, <variable>.u8DCIHistCorTh,,
	bfi	r1, ip, #16, #8	@ VP0_DCIHISCOR, <variable>.u8DCIHistCorTh,,
	mov	r0, r9	@, D.35594
	bfi	r1, r3, #8, #8	@ VP0_DCIHISCOR, <variable>.u8DCIHistCorTh,,
	bl	PQ_HAL_RegWrite	@
	add	r0, r6, #24	@ tmp337, tmp251,
	add	r7, r5, r0	@ D.35602, D.35523, tmp337
	mov	r0, r7	@, D.35602
	bl	PQ_HAL_RegRead	@
	ldrb	sl, [r4, #39]	@ zero_extendqisi2	@ <variable>.u8DCIMetrAbld, <variable>.u8DCIMetrAbld
	ldrb	r8, [r4, #40]	@ zero_extendqisi2	@ <variable>.u8DCIMetrAbld, <variable>.u8DCIMetrAbld
	ldrb	r9, [r4, #41]	@ zero_extendqisi2	@ <variable>.u8DCIMetrAbld, <variable>.u8DCIMetrAbld
	ldrb	r2, [r4, #38]	@ zero_extendqisi2	@ <variable>.u8DCIHistAbld, <variable>.u8DCIHistAbld
	ldrb	ip, [r4, #37]	@ zero_extendqisi2	@ <variable>.u8DCIOrgAbld, <variable>.u8DCIOrgAbld
	mov	r1, r0	@ VP0_DCIMERBLD,
	bfi	r1, sl, #26, #6	@ VP0_DCIMERBLD, <variable>.u8DCIMetrAbld,,
	bfi	r1, r8, #20, #6	@ VP0_DCIMERBLD, <variable>.u8DCIMetrAbld,,
	mov	r0, r7	@, D.35602
	bfi	r1, r9, #14, #6	@ VP0_DCIMERBLD, <variable>.u8DCIMetrAbld,,
	add	r9, r6, #32	@ tmp365, tmp251,
	bfi	r1, r2, #8, #6	@ VP0_DCIMERBLD, <variable>.u8DCIHistAbld,,
	bfi	r1, ip, #2, #6	@ VP0_DCIMERBLD, <variable>.u8DCIOrgAbld,,
	bl	PQ_HAL_RegWrite	@
	add	r1, r6, #28	@ tmp354, tmp251,
	add	r7, r5, r1	@ D.35617, D.35523, tmp354
	mov	r0, r7	@, D.35617
	bl	PQ_HAL_RegRead	@
	ldrb	r3, [r4, #42]	@ zero_extendqisi2	@ <variable>.u8DCIManAdjWgt, <variable>.u8DCIManAdjWgt
	ldrb	sl, [r4, #43]	@ zero_extendqisi2	@ <variable>.u8DCIManAdjWgt, <variable>.u8DCIManAdjWgt
	ldrb	r8, [r4, #44]	@ zero_extendqisi2	@ <variable>.u8DCIManAdjWgt, <variable>.u8DCIManAdjWgt
	mov	r1, r0	@ VP0_DCIADJWGT,
	bfi	r1, r3, #24, #8	@ VP0_DCIADJWGT, <variable>.u8DCIManAdjWgt,,
	mov	r0, r7	@, D.35617
	bfi	r1, sl, #16, #8	@ VP0_DCIADJWGT, <variable>.u8DCIManAdjWgt,,
	add	r7, r5, r9	@ D.35625, D.35523, tmp365
	bfi	r1, r8, #8, #8	@ VP0_DCIADJWGT, <variable>.u8DCIManAdjWgt,,
	bl	PQ_HAL_RegWrite	@
	mov	r0, r7	@, D.35625
	bl	PQ_HAL_RegRead	@
	ldrb	r2, [r4, #48]	@ zero_extendqisi2	@ <variable>.u8DCIWgtClipLow, <variable>.u8DCIWgtClipLow
	ldrb	ip, [r4, #45]	@ zero_extendqisi2	@ <variable>.u8DCIWgtClipHigh, <variable>.u8DCIWgtClipHigh
	mov	r1, r0	@ VP0_DCICLIP0,
	bfi	r1, r2, #24, #8	@ VP0_DCICLIP0, <variable>.u8DCIWgtClipLow,,
	bfi	r1, ip, #16, #8	@ VP0_DCICLIP0, <variable>.u8DCIWgtClipHigh,,
	mov	r0, r7	@, D.35625
	bl	PQ_HAL_RegWrite	@
	add	r0, r6, #36	@ tmp373, tmp251,
	add	sl, r5, r0	@ D.35632, D.35523, tmp373
	mov	r0, sl	@, D.35632
	bl	PQ_HAL_RegRead	@
	ldrb	r3, [r4, #49]	@ zero_extendqisi2	@ <variable>.u8DCIWgtClipLow, <variable>.u8DCIWgtClipLow
	ldrb	r8, [r4, #46]	@ zero_extendqisi2	@ <variable>.u8DCIWgtClipHigh, <variable>.u8DCIWgtClipHigh
	mov	r1, r0	@ VP0_DCICLIP1,
	bfi	r1, r3, #24, #8	@ VP0_DCICLIP1, <variable>.u8DCIWgtClipLow,,
	mov	r0, sl	@, D.35632
	bfi	r1, r8, #16, #8	@ VP0_DCICLIP1, <variable>.u8DCIWgtClipHigh,,
	bl	PQ_HAL_RegWrite	@
	add	r1, r6, #40	@ tmp381, tmp251,
	add	r9, r5, r1	@ D.35639, D.35523, tmp381
	mov	r0, r9	@, D.35639
	bl	PQ_HAL_RegRead	@
	ldrb	r2, [r4, #50]	@ zero_extendqisi2	@ <variable>.u8DCIWgtClipLow, <variable>.u8DCIWgtClipLow
	ldrb	r7, [r4, #47]	@ zero_extendqisi2	@ <variable>.u8DCIWgtClipHigh, <variable>.u8DCIWgtClipHigh
	mov	r1, r0	@ VP0_DCICLIP2,
	bfi	r1, r2, #24, #8	@ VP0_DCICLIP2, <variable>.u8DCIWgtClipLow,,
	bfi	r1, r7, #16, #8	@ VP0_DCICLIP2, <variable>.u8DCIWgtClipHigh,,
	mov	r0, r9	@, D.35639
	bl	PQ_HAL_RegWrite	@
	add	ip, r6, #44	@ tmp389, tmp251,
	add	sl, r5, ip	@ D.35646, D.35523, tmp389
	mov	r0, sl	@, D.35646
	bl	PQ_HAL_RegRead	@
	ldrb	r3, [r4, #51]	@ zero_extendqisi2	@ <variable>.u8DCIGlbGain, <variable>.u8DCIGlbGain
	ldrb	r8, [r4, #52]	@ zero_extendqisi2	@ <variable>.u8DCIGlbGain, <variable>.u8DCIGlbGain
	ldrb	r9, [r4, #53]	@ zero_extendqisi2	@ <variable>.u8DCIGlbGain, <variable>.u8DCIGlbGain
	mov	r1, r0	@ VP0_DCIGLBGAIN,
	bfi	r1, r3, #26, #6	@ VP0_DCIGLBGAIN, <variable>.u8DCIGlbGain,,
	bfi	r1, r8, #20, #6	@ VP0_DCIGLBGAIN, <variable>.u8DCIGlbGain,,
	mov	r0, sl	@, D.35646
	bfi	r1, r9, #14, #6	@ VP0_DCIGLBGAIN, <variable>.u8DCIGlbGain,,
	bl	PQ_HAL_RegWrite	@
	add	r0, r6, #48	@ tmp400, tmp251,
	add	r8, r5, r0	@ D.35657, D.35523, tmp400
	mov	r0, r8	@, D.35657
	bl	PQ_HAL_RegRead	@
	add	r1, r6, #52	@ tmp402, tmp251,
	add	r7, r5, r1	@ D.35661, D.35523, tmp402
	mov	r9, r0	@ VP0_DCIPOSTHR0,
	mov	r0, r7	@, D.35661
	bl	PQ_HAL_RegRead	@
	ldrb	r2, [r4, #59]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosTh, <variable>.u8DCIGainPosTh
	ldrb	sl, [r4, #55]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosTh, <variable>.u8DCIGainPosTh
	ldrb	ip, [r4, #56]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosTh, <variable>.u8DCIGainPosTh
	bfi	r9, sl, #24, #8	@ VP0_DCIPOSTHR0, <variable>.u8DCIGainPosTh,,
	ldrb	sl, [r4, #58]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosTh, <variable>.u8DCIGainPosTh
	bfi	r9, ip, #16, #8	@ VP0_DCIPOSTHR0, <variable>.u8DCIGainPosTh,,
	ldrb	r3, [r4, #61]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosTh, <variable>.u8DCIGainPosTh
	mov	r1, r0	@ VP0_DCIPOSTHR1,
	bfi	r1, r2, #24, #8	@ VP0_DCIPOSTHR1, <variable>.u8DCIGainPosTh,,
	ldrb	r2, [r4, #57]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosTh, <variable>.u8DCIGainPosTh
	mov	r0, r7	@, D.35661
	ldrb	r7, [r4, #60]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosTh, <variable>.u8DCIGainPosTh
	bfi	r9, r2, #8, #8	@ VP0_DCIPOSTHR0, <variable>.u8DCIGainPosTh,,
	bfi	r9, sl, #0, #8	@ VP0_DCIPOSTHR0, <variable>.u8DCIGainPosTh,,
	bfi	r1, r7, #16, #8	@ VP0_DCIPOSTHR1, <variable>.u8DCIGainPosTh,,
	bfi	r1, r3, #8, #8	@ VP0_DCIPOSTHR1, <variable>.u8DCIGainPosTh,,
	add	r7, r6, #56	@ tmp425, tmp251,
	bl	PQ_HAL_RegWrite	@
	mov	r1, r9	@, VP0_DCIPOSTHR0
	add	r9, r5, r7	@ D.35674, D.35523, tmp425
	mov	r0, r8	@, D.35657
	bl	PQ_HAL_RegWrite	@
	mov	r0, r9	@, D.35674
	bl	PQ_HAL_RegRead	@
	mov	sl, r0	@ VP0_DCIPOSGAIN0,
	add	r0, r6, #60	@ tmp427, tmp251,
	add	r8, r5, r0	@ D.35678, D.35523, tmp427
	mov	r0, r8	@, D.35678
	bl	PQ_HAL_RegRead	@
	ldrb	r1, [r4, #63]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosCbCr, <variable>.u8DCIGainPosCbCr
	ldrb	r2, [r4, #64]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosCbCr, <variable>.u8DCIGainPosCbCr
	ldrb	r3, [r4, #65]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosCbCr, <variable>.u8DCIGainPosCbCr
	bfi	sl, r1, #28, #4	@ VP0_DCIPOSGAIN0, <variable>.u8DCIGainPosCbCr,,
	ldrb	ip, [r4, #66]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosCbCr, <variable>.u8DCIGainPosCbCr
	bfi	sl, r2, #24, #4	@ VP0_DCIPOSGAIN0, <variable>.u8DCIGainPosCbCr,,
	bfi	sl, r3, #20, #4	@ VP0_DCIPOSGAIN0, <variable>.u8DCIGainPosCbCr,,
	ldrb	r1, [r4, #68]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosCbCr, <variable>.u8DCIGainPosCbCr
	bfi	sl, ip, #16, #4	@ VP0_DCIPOSGAIN0, <variable>.u8DCIGainPosCbCr,,
	ldrb	r3, [r4, #69]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosCbCr, <variable>.u8DCIGainPosCbCr
	ldrb	r2, [r4, #70]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosCbCr, <variable>.u8DCIGainPosCbCr
	ldrb	ip, [r4, #71]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosCbCr, <variable>.u8DCIGainPosCbCr
	mov	r7, r0	@ VP0_DCIPOSGAIN1,
	mov	r0, r9	@, D.35674
	ldrb	r9, [r4, #67]	@ zero_extendqisi2	@ <variable>.u8DCIGainPosCbCr, <variable>.u8DCIGainPosCbCr
	bfi	r7, ip, #28, #4	@ VP0_DCIPOSGAIN1, <variable>.u8DCIGainPosCbCr,,
	bfi	sl, r9, #12, #4	@ VP0_DCIPOSGAIN0, <variable>.u8DCIGainPosCbCr,,
	add	r9, r6, #64	@ tmp456, tmp251,
	bfi	sl, r1, #8, #4	@ VP0_DCIPOSGAIN0, <variable>.u8DCIGainPosCbCr,,
	bfi	sl, r3, #4, #4	@ VP0_DCIPOSGAIN0, <variable>.u8DCIGainPosCbCr,,
	bfi	sl, r2, #0, #4	@ VP0_DCIPOSGAIN0, <variable>.u8DCIGainPosCbCr,,
	mov	r1, sl	@, VP0_DCIPOSGAIN0
	add	sl, r6, #68	@ tmp458, tmp251,
	bl	PQ_HAL_RegWrite	@
	mov	r1, r7	@, VP0_DCIPOSGAIN1
	add	r7, r5, r9	@ D.35702, D.35523, tmp456
	mov	r0, r8	@, D.35678
	bl	PQ_HAL_RegWrite	@
	str	r7, [fp, #-108]	@,
	mov	r0, r7	@, D.35702
	add	r9, r5, sl	@ D.35706, D.35523, tmp458
	bl	PQ_HAL_RegRead	@
	mov	r8, r0	@ VP0_DCIPOSSLP0,
	mov	r0, r9	@, D.35706
	str	r8, [fp, #-112]	@,
	bl	PQ_HAL_RegRead	@
	mov	r7, r0	@ VP0_DCIPOSSLP1,
	add	r0, r6, #72	@ tmp460, tmp251,
	add	sl, r5, r0	@ D.35710, D.35523, tmp460
	mov	r0, sl	@, D.35710
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-108]	@,
	ldrh	r2, [r4, #72]	@ <variable>.s16DCIGainPosSlp, <variable>.s16DCIGainPosSlp
	ldrh	r3, [r4, #74]	@ <variable>.s16DCIGainPosSlp, <variable>.s16DCIGainPosSlp
	ldrh	ip, [r4, #76]	@ <variable>.s16DCIGainPosSlp, <variable>.s16DCIGainPosSlp
	mov	r8, r0	@ VP0_DCIPOSSLP2,
	mov	r0, r1	@, D.35702
	ldr	r1, [fp, #-112]	@,
	bfi	r1, r2, #22, #10	@ VP0_DCIPOSSLP0, <variable>.s16DCIGainPosSlp,,
	ldrh	r2, [r4, #78]	@ <variable>.s16DCIGainPosSlp, <variable>.s16DCIGainPosSlp
	bfi	r1, r3, #12, #10	@ VP0_DCIPOSSLP0, <variable>.s16DCIGainPosSlp,,
	ldrh	r3, [r4, #80]	@ <variable>.s16DCIGainPosSlp, <variable>.s16DCIGainPosSlp
	bfi	r1, ip, #2, #10	@ VP0_DCIPOSSLP0, <variable>.s16DCIGainPosSlp,,
	bfi	r7, r2, #22, #10	@ VP0_DCIPOSSLP1, <variable>.s16DCIGainPosSlp,,
	ldrh	ip, [r4, #82]	@ <variable>.s16DCIGainPosSlp, <variable>.s16DCIGainPosSlp
	bfi	r7, r3, #12, #10	@ VP0_DCIPOSSLP1, <variable>.s16DCIGainPosSlp,,
	ldrh	r2, [r4, #84]	@ <variable>.s16DCIGainPosSlp, <variable>.s16DCIGainPosSlp
	ldrh	r3, [r4, #86]	@ <variable>.s16DCIGainPosSlp, <variable>.s16DCIGainPosSlp
	bfi	r7, ip, #2, #10	@ VP0_DCIPOSSLP1, <variable>.s16DCIGainPosSlp,,
	bfi	r8, r2, #22, #10	@ VP0_DCIPOSSLP2, <variable>.s16DCIGainPosSlp,,
	bfi	r8, r3, #12, #10	@ VP0_DCIPOSSLP2, <variable>.s16DCIGainPosSlp,,
	bl	PQ_HAL_RegWrite	@
	mov	r0, r9	@, D.35706
	mov	r1, r7	@, VP0_DCIPOSSLP1
	bl	PQ_HAL_RegWrite	@
	mov	r1, r8	@, VP0_DCIPOSSLP2
	mov	r0, sl	@, D.35710
	bl	PQ_HAL_RegWrite	@
	add	r0, r6, #76	@ tmp486, tmp251,
	add	r8, r5, r0	@ D.35741, D.35523, tmp486
	mov	r0, r8	@, D.35741
	bl	PQ_HAL_RegRead	@
	add	r1, r6, #80	@ tmp488, tmp251,
	add	r7, r5, r1	@ D.35745, D.35523, tmp488
	mov	r9, r0	@ VP0_DCINEGTHR0,
	mov	r0, r7	@, D.35745
	bl	PQ_HAL_RegRead	@
	ldrb	r2, [r4, #93]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegTh, <variable>.u8DCIGainNegTh
	ldrb	sl, [r4, #89]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegTh, <variable>.u8DCIGainNegTh
	ldrb	ip, [r4, #90]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegTh, <variable>.u8DCIGainNegTh
	bfi	r9, sl, #24, #8	@ VP0_DCINEGTHR0, <variable>.u8DCIGainNegTh,,
	ldrb	sl, [r4, #92]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegTh, <variable>.u8DCIGainNegTh
	bfi	r9, ip, #16, #8	@ VP0_DCINEGTHR0, <variable>.u8DCIGainNegTh,,
	ldrb	r3, [r4, #95]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegTh, <variable>.u8DCIGainNegTh
	mov	r1, r0	@ VP0_DCINEGTHR1,
	bfi	r1, r2, #24, #8	@ VP0_DCINEGTHR1, <variable>.u8DCIGainNegTh,,
	ldrb	r2, [r4, #91]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegTh, <variable>.u8DCIGainNegTh
	mov	r0, r7	@, D.35745
	ldrb	r7, [r4, #94]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegTh, <variable>.u8DCIGainNegTh
	bfi	r9, r2, #8, #8	@ VP0_DCINEGTHR0, <variable>.u8DCIGainNegTh,,
	bfi	r9, sl, #0, #8	@ VP0_DCINEGTHR0, <variable>.u8DCIGainNegTh,,
	bfi	r1, r7, #16, #8	@ VP0_DCINEGTHR1, <variable>.u8DCIGainNegTh,,
	bfi	r1, r3, #8, #8	@ VP0_DCINEGTHR1, <variable>.u8DCIGainNegTh,,
	add	r7, r6, #84	@ tmp511, tmp251,
	bl	PQ_HAL_RegWrite	@
	mov	r1, r9	@, VP0_DCINEGTHR0
	add	r9, r5, r7	@ D.35758, D.35523, tmp511
	mov	r0, r8	@, D.35741
	bl	PQ_HAL_RegWrite	@
	mov	r0, r9	@, D.35758
	bl	PQ_HAL_RegRead	@
	mov	sl, r0	@ VP0_DCINEGGAIN0,
	add	r0, r6, #88	@ tmp513, tmp251,
	add	r8, r5, r0	@ D.35762, D.35523, tmp513
	mov	r0, r8	@, D.35762
	bl	PQ_HAL_RegRead	@
	ldrb	r1, [r4, #97]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegCbCr, <variable>.u8DCIGainNegCbCr
	ldrb	r2, [r4, #98]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegCbCr, <variable>.u8DCIGainNegCbCr
	ldrb	r3, [r4, #99]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegCbCr, <variable>.u8DCIGainNegCbCr
	bfi	sl, r1, #28, #4	@ VP0_DCINEGGAIN0, <variable>.u8DCIGainNegCbCr,,
	ldrb	ip, [r4, #100]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegCbCr, <variable>.u8DCIGainNegCbCr
	bfi	sl, r2, #24, #4	@ VP0_DCINEGGAIN0, <variable>.u8DCIGainNegCbCr,,
	bfi	sl, r3, #20, #4	@ VP0_DCINEGGAIN0, <variable>.u8DCIGainNegCbCr,,
	ldrb	r1, [r4, #102]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegCbCr, <variable>.u8DCIGainNegCbCr
	bfi	sl, ip, #16, #4	@ VP0_DCINEGGAIN0, <variable>.u8DCIGainNegCbCr,,
	ldrb	r3, [r4, #103]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegCbCr, <variable>.u8DCIGainNegCbCr
	ldrb	r2, [r4, #104]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegCbCr, <variable>.u8DCIGainNegCbCr
	ldrb	ip, [r4, #105]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegCbCr, <variable>.u8DCIGainNegCbCr
	mov	r7, r0	@ VP0_DCINEGGAIN1,
	mov	r0, r9	@, D.35758
	ldrb	r9, [r4, #101]	@ zero_extendqisi2	@ <variable>.u8DCIGainNegCbCr, <variable>.u8DCIGainNegCbCr
	bfi	r7, ip, #28, #4	@ VP0_DCINEGGAIN1, <variable>.u8DCIGainNegCbCr,,
	bfi	sl, r9, #12, #4	@ VP0_DCINEGGAIN0, <variable>.u8DCIGainNegCbCr,,
	add	r9, r6, #92	@ tmp542, tmp251,
	bfi	sl, r1, #8, #4	@ VP0_DCINEGGAIN0, <variable>.u8DCIGainNegCbCr,,
	bfi	sl, r3, #4, #4	@ VP0_DCINEGGAIN0, <variable>.u8DCIGainNegCbCr,,
	bfi	sl, r2, #0, #4	@ VP0_DCINEGGAIN0, <variable>.u8DCIGainNegCbCr,,
	mov	r1, sl	@, VP0_DCINEGGAIN0
	add	sl, r6, #96	@ tmp544, tmp251,
	bl	PQ_HAL_RegWrite	@
	mov	r1, r7	@, VP0_DCINEGGAIN1
	add	r7, r5, r9	@ D.35786, D.35523, tmp542
	mov	r0, r8	@, D.35762
	bl	PQ_HAL_RegWrite	@
	str	r7, [fp, #-108]	@,
	mov	r0, r7	@, D.35786
	add	r9, r5, sl	@ D.35790, D.35523, tmp544
	bl	PQ_HAL_RegRead	@
	mov	r8, r0	@ VP0_DCINEGSLP0,
	mov	r0, r9	@, D.35790
	str	r8, [fp, #-112]	@,
	bl	PQ_HAL_RegRead	@
	mov	r7, r0	@ VP0_DCINEGSLP1,
	add	r0, r6, #100	@ tmp546, tmp251,
	add	sl, r5, r0	@ D.35794, D.35523, tmp546
	mov	r0, sl	@, D.35794
	bl	PQ_HAL_RegRead	@
	ldr	r1, [fp, #-108]	@,
	ldrh	r2, [r4, #106]	@ <variable>.s16DCIGainNegSlp, <variable>.s16DCIGainNegSlp
	ldrh	r3, [r4, #108]	@ <variable>.s16DCIGainNegSlp, <variable>.s16DCIGainNegSlp
	ldrh	ip, [r4, #110]	@ <variable>.s16DCIGainNegSlp, <variable>.s16DCIGainNegSlp
	mov	r8, r0	@ VP0_DCINEGSLP2,
	mov	r0, r1	@, D.35786
	ldr	r1, [fp, #-112]	@,
	bfi	r1, r2, #22, #10	@ VP0_DCINEGSLP0, <variable>.s16DCIGainNegSlp,,
	ldrh	r2, [r4, #112]	@ <variable>.s16DCIGainNegSlp, <variable>.s16DCIGainNegSlp
	bfi	r1, r3, #12, #10	@ VP0_DCINEGSLP0, <variable>.s16DCIGainNegSlp,,
	ldrh	r3, [r4, #114]	@ <variable>.s16DCIGainNegSlp, <variable>.s16DCIGainNegSlp
	bfi	r1, ip, #2, #10	@ VP0_DCINEGSLP0, <variable>.s16DCIGainNegSlp,,
	bfi	r7, r2, #22, #10	@ VP0_DCINEGSLP1, <variable>.s16DCIGainNegSlp,,
	ldrh	ip, [r4, #116]	@ <variable>.s16DCIGainNegSlp, <variable>.s16DCIGainNegSlp
	bfi	r7, r3, #12, #10	@ VP0_DCINEGSLP1, <variable>.s16DCIGainNegSlp,,
	ldrh	r2, [r4, #118]	@ <variable>.s16DCIGainNegSlp, <variable>.s16DCIGainNegSlp
	ldrh	r3, [r4, #120]	@ <variable>.s16DCIGainNegSlp, <variable>.s16DCIGainNegSlp
	bfi	r7, ip, #2, #10	@ VP0_DCINEGSLP1, <variable>.s16DCIGainNegSlp,,
	bfi	r8, r2, #22, #10	@ VP0_DCINEGSLP2, <variable>.s16DCIGainNegSlp,,
	bfi	r8, r3, #12, #10	@ VP0_DCINEGSLP2, <variable>.s16DCIGainNegSlp,,
	bl	PQ_HAL_RegWrite	@
	mov	r0, r9	@, D.35790
	mov	r1, r7	@, VP0_DCINEGSLP1
	bl	PQ_HAL_RegWrite	@
	mov	r1, r8	@, VP0_DCINEGSLP2
	mov	r0, sl	@, D.35794
	bl	PQ_HAL_RegWrite	@
	add	ip, r6, #104	@ tmp572, tmp251,
	add	r7, r5, ip	@, D.35523, tmp572
	str	r7, [fp, #-48]	@, %sfp
	mov	r0, r7	@,
	bl	PQ_HAL_RegRead	@
	mov	r9, r0	@ VP0_DCIADJSW0,
	add	r0, r6, #108	@ tmp574, tmp251,
	add	r1, r5, r0	@, D.35523, tmp574
	str	r9, [fp, #-112]	@,
	str	r1, [fp, #-100]	@, %sfp
	mov	r0, r1	@,
	bl	PQ_HAL_RegRead	@
	add	r2, r6, #112	@ tmp576, tmp251,
	add	sl, r5, r2	@, D.35523, tmp576
	str	sl, [fp, #-96]	@, %sfp
	mov	r9, r0	@ VP0_DCIADJSW1,
	mov	r0, sl	@,
	bl	PQ_HAL_RegRead	@
	add	r3, r6, #116	@ tmp578, tmp251,
	add	r8, r5, r3	@, D.35523, tmp578
	str	r8, [fp, #-92]	@, %sfp
	mov	sl, r0	@ VP0_DCIADJSW2,
	mov	r0, r8	@,
	bl	PQ_HAL_RegRead	@
	add	ip, r6, #120	@ tmp580, tmp251,
	add	r7, r5, ip	@, D.35523, tmp580
	str	r7, [fp, #-88]	@, %sfp
	mov	r8, r0	@ VP0_DCIADJSW3,
	mov	r0, r7	@,
	bl	PQ_HAL_RegRead	@
	mov	r7, r0	@ VP0_DCIADJSW4,
	add	r0, r6, #124	@ tmp582, tmp251,
	add	r1, r5, r0	@, D.35523, tmp582
	str	r1, [fp, #-84]	@, %sfp
	mov	r0, r1	@,
	bl	PQ_HAL_RegRead	@
	add	r2, r6, #128	@ tmp584, tmp251,
	add	r3, r5, r2	@, D.35523, tmp584
	str	r3, [fp, #-80]	@, %sfp
	mov	ip, r0	@ VP0_DCIADJSW5,
	mov	r0, r3	@,
	str	ip, [fp, #-108]	@,
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ VP0_DCIADJSW6,
	add	r0, r6, #132	@ tmp586, tmp251,
	add	r0, r5, r0	@, D.35523, tmp586
	str	r1, [fp, #-116]	@,
	str	r0, [fp, #-76]	@, %sfp
	bl	PQ_HAL_RegRead	@
	add	r2, r6, #136	@ tmp588, tmp251,
	mov	r3, r0	@ VP0_DCIADJSW7,
	add	r0, r5, r2	@, D.35523, tmp588
	str	r3, [fp, #-120]	@,
	str	r0, [fp, #-72]	@, %sfp
	bl	PQ_HAL_RegRead	@
	add	ip, r6, #140	@ tmp590, tmp251,
	str	r0, [fp, #-52]	@, %sfp
	add	r0, r5, ip	@, D.35523, tmp590
	str	r0, [fp, #-68]	@, %sfp
	bl	PQ_HAL_RegRead	@
	str	r0, [fp, #-56]	@, %sfp
	add	r0, r6, #144	@ tmp592, tmp251,
	add	r1, r5, r0	@, D.35523, tmp592
	str	r1, [fp, #-64]	@, %sfp
	mov	r0, r1	@,
	bl	PQ_HAL_RegRead	@
	ldrh	lr, [r4, #126]	@, <variable>.s16DCIAdjSw
	ldrh	r2, [r4, #122]	@ <variable>.s16DCIAdjSw, <variable>.s16DCIAdjSw
	ldrh	r3, [r4, #124]	@ <variable>.s16DCIAdjSw, <variable>.s16DCIAdjSw
	str	lr, [fp, #-60]	@, %sfp
	ldrh	r6, [r4, #128]	@, <variable>.s16DCIAdjSw
	ldr	r1, [fp, #-112]	@,
	ldr	ip, [fp, #-60]	@, %sfp
	bfi	r1, r2, #22, #10	@ VP0_DCIADJSW0, <variable>.s16DCIAdjSw,,
	bfi	r1, r3, #12, #10	@ VP0_DCIADJSW0, <variable>.s16DCIAdjSw,,
	bfi	r1, ip, #2, #10	@ VP0_DCIADJSW0,,,
	mov	r5, r0	@ VP0_DCIADJSW10,
	ldr	r0, [fp, #-48]	@, %sfp
	str	r6, [fp, #-48]	@, %sfp
	ldrh	r2, [r4, #134]	@, <variable>.s16DCIAdjSw
	ldrh	r3, [r4, #130]	@ <variable>.s16DCIAdjSw, <variable>.s16DCIAdjSw
	ldr	lr, [fp, #-48]	@, %sfp
	str	r2, [fp, #-60]	@, %sfp
	ldrh	r6, [r4, #140]	@, <variable>.s16DCIAdjSw
	bfi	r9, lr, #22, #10	@ VP0_DCIADJSW1,,,
	ldr	ip, [fp, #-60]	@, %sfp
	bfi	r9, r3, #12, #10	@ VP0_DCIADJSW1, <variable>.s16DCIAdjSw,,
	str	r6, [fp, #-48]	@, %sfp
	bfi	sl, ip, #22, #10	@ VP0_DCIADJSW2,,,
	ldrh	r2, [r4, #152]	@, <variable>.s16DCIAdjSw
	ldrh	r3, [r4, #146]	@ <variable>.s16DCIAdjSw, <variable>.s16DCIAdjSw
	ldr	lr, [fp, #-48]	@, %sfp
	str	r2, [fp, #-60]	@, %sfp
	bfi	r7, r3, #22, #10	@ VP0_DCIADJSW4, <variable>.s16DCIAdjSw,,
	ldrh	r6, [r4, #158]	@, <variable>.s16DCIAdjSw
	bfi	r8, lr, #22, #10	@ VP0_DCIADJSW3,,,
	ldr	ip, [fp, #-60]	@, %sfp
	ldr	r3, [fp, #-108]	@,
	str	r6, [fp, #-48]	@, %sfp
	ldrh	r2, [r4, #170]	@, <variable>.s16DCIAdjSw
	bfi	r3, ip, #22, #10	@ VP0_DCIADJSW5,,,
	ldrh	r6, [r4, #164]	@ <variable>.s16DCIAdjSw, <variable>.s16DCIAdjSw
	ldr	lr, [fp, #-48]	@, %sfp
	str	r2, [fp, #-60]	@, %sfp
	ldrh	ip, [r4, #176]	@, <variable>.s16DCIAdjSw
	ldr	r2, [fp, #-116]	@,
	str	ip, [fp, #-48]	@, %sfp
	bfi	r2, lr, #22, #10	@ VP0_DCIADJSW6,,,
	ldrh	lr, [r4, #182]	@, <variable>.s16DCIAdjSw
	ldr	ip, [fp, #-120]	@,
	str	lr, [fp, #-104]	@, %sfp
	bfi	ip, r6, #22, #10	@ VP0_DCIADJSW7, <variable>.s16DCIAdjSw,,
	ldr	lr, [fp, #-52]	@, %sfp
	ldr	r6, [fp, #-60]	@, %sfp
	bfi	lr, r6, #22, #10	@,,,
	str	lr, [fp, #-52]	@, %sfp
	ldrh	r6, [r4, #132]	@, <variable>.s16DCIAdjSw
	ldr	lr, [fp, #-48]	@, %sfp
	str	r6, [fp, #-60]	@, %sfp
	ldr	r6, [fp, #-56]	@, %sfp
	bfi	r6, lr, #22, #10	@,,,
	str	r6, [fp, #-56]	@, %sfp
	ldrh	lr, [r4, #136]	@, <variable>.s16DCIAdjSw
	ldr	r6, [fp, #-104]	@, %sfp
	str	lr, [fp, #-48]	@, %sfp
	bfi	r5, r6, #22, #10	@ VP0_DCIADJSW10,,,
	ldr	lr, [fp, #-60]	@, %sfp
	ldrh	r6, [r4, #142]	@ <variable>.s16DCIAdjSw, <variable>.s16DCIAdjSw
	bfi	r9, lr, #2, #10	@ VP0_DCIADJSW1,,,
	ldrh	lr, [r4, #148]	@, <variable>.s16DCIAdjSw
	bfi	r8, r6, #12, #10	@ VP0_DCIADJSW3, <variable>.s16DCIAdjSw,,
	str	lr, [fp, #-60]	@, %sfp
	ldr	lr, [fp, #-48]	@, %sfp
	bfi	sl, lr, #12, #10	@ VP0_DCIADJSW2,,,
	ldrh	lr, [r4, #154]	@, <variable>.s16DCIAdjSw
	str	lr, [fp, #-48]	@, %sfp
	ldr	lr, [fp, #-60]	@, %sfp
	ldrh	r6, [r4, #160]	@ <variable>.s16DCIAdjSw, <variable>.s16DCIAdjSw
	bfi	r7, lr, #12, #10	@ VP0_DCIADJSW4,,,
	ldrh	lr, [r4, #166]	@, <variable>.s16DCIAdjSw
	bfi	r2, r6, #12, #10	@ VP0_DCIADJSW6, <variable>.s16DCIAdjSw,,
	str	lr, [fp, #-60]	@, %sfp
	ldr	lr, [fp, #-48]	@, %sfp
	ldr	r6, [fp, #-60]	@, %sfp
	bfi	r3, lr, #12, #10	@ VP0_DCIADJSW5,,,
	ldrh	lr, [r4, #172]	@, <variable>.s16DCIAdjSw
	bfi	ip, r6, #12, #10	@ VP0_DCIADJSW7,,,
	str	lr, [fp, #-48]	@, %sfp
	ldrh	lr, [r4, #178]	@, <variable>.s16DCIAdjSw
	ldr	r6, [fp, #-48]	@, %sfp
	str	lr, [fp, #-128]	@, %sfp
	ldrh	lr, [r4, #184]	@, <variable>.s16DCIAdjSw
	str	lr, [fp, #-60]	@, %sfp
	ldr	lr, [fp, #-52]	@, %sfp
	bfi	lr, r6, #12, #10	@,,,
	str	lr, [fp, #-52]	@, %sfp
	ldrh	r6, [r4, #186]	@, <variable>.s16DCIAdjSw
	str	r6, [fp, #-104]	@, %sfp
	ldr	r6, [fp, #-56]	@, %sfp
	ldr	lr, [fp, #-128]	@, %sfp
	bfi	r6, lr, #12, #10	@,,,
	ldr	lr, [fp, #-60]	@, %sfp
	str	r6, [fp, #-56]	@, %sfp
	bfi	r5, lr, #12, #10	@ VP0_DCIADJSW10,,,
	ldrh	lr, [r4, #144]	@, <variable>.s16DCIAdjSw
	ldrh	r6, [r4, #138]	@ <variable>.s16DCIAdjSw, <variable>.s16DCIAdjSw
	str	lr, [fp, #-48]	@, %sfp
	bfi	sl, r6, #2, #10	@ VP0_DCIADJSW2, <variable>.s16DCIAdjSw,,
	ldrh	lr, [r4, #150]	@, <variable>.s16DCIAdjSw
	ldr	r6, [fp, #-48]	@, %sfp
	str	lr, [fp, #-60]	@, %sfp
	bfi	r8, r6, #2, #10	@ VP0_DCIADJSW3,,,
	ldrh	lr, [r4, #156]	@, <variable>.s16DCIAdjSw
	str	lr, [fp, #-128]	@, %sfp
	ldr	lr, [fp, #-60]	@, %sfp
	ldrh	r6, [r4, #162]	@ <variable>.s16DCIAdjSw, <variable>.s16DCIAdjSw
	bfi	r7, lr, #2, #10	@ VP0_DCIADJSW4,,,
	ldrh	lr, [r4, #168]	@, <variable>.s16DCIAdjSw
	bfi	r2, r6, #2, #10	@ VP0_DCIADJSW6, <variable>.s16DCIAdjSw,,
	str	lr, [fp, #-48]	@, %sfp
	ldr	lr, [fp, #-128]	@, %sfp
	ldr	r6, [fp, #-48]	@, %sfp
	bfi	r3, lr, #2, #10	@ VP0_DCIADJSW5,,,
	ldrh	lr, [r4, #174]	@, <variable>.s16DCIAdjSw
	bfi	ip, r6, #2, #10	@ VP0_DCIADJSW7,,,
	ldr	r6, [fp, #-52]	@, %sfp
	str	lr, [fp, #-60]	@, %sfp
	ldrh	lr, [r4, #180]	@ <variable>.s16DCIAdjSw, <variable>.s16DCIAdjSw
	ldr	r4, [fp, #-60]	@, %sfp
	str	r2, [fp, #-116]	@,
	bfi	r6, r4, #2, #10	@,,,
	ldr	r4, [fp, #-56]	@, %sfp
	str	r3, [fp, #-108]	@,
	bfi	r4, lr, #2, #10	@, <variable>.s16DCIAdjSw,,
	str	ip, [fp, #-120]	@,
	str	r6, [fp, #-52]	@, %sfp
	str	r4, [fp, #-56]	@, %sfp
	ldr	r6, [fp, #-104]	@, %sfp
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [fp, #-100]	@, %sfp
	mov	r1, r9	@, VP0_DCIADJSW1
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [fp, #-96]	@, %sfp
	mov	r1, sl	@, VP0_DCIADJSW2
	bfi	r5, r6, #2, #10	@ VP0_DCIADJSW10,,,
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [fp, #-92]	@, %sfp
	mov	r1, r8	@, VP0_DCIADJSW3
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [fp, #-88]	@, %sfp
	mov	r1, r7	@, VP0_DCIADJSW4
	bl	PQ_HAL_RegWrite	@
	ldr	ip, [fp, #-108]	@,
	ldr	r0, [fp, #-84]	@, %sfp
	mov	r1, ip	@, VP0_DCIADJSW5
	bl	PQ_HAL_RegWrite	@
	ldr	r3, [fp, #-116]	@,
	ldr	r0, [fp, #-80]	@, %sfp
	mov	r1, r3	@, VP0_DCIADJSW6
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [fp, #-120]	@,
	ldr	r0, [fp, #-76]	@, %sfp
	mov	r1, r2	@, VP0_DCIADJSW7
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [fp, #-72]	@, %sfp
	ldr	r1, [fp, #-52]	@, %sfp
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [fp, #-68]	@, %sfp
	ldr	r1, [fp, #-56]	@, %sfp
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [fp, #-64]	@, %sfp
	mov	r1, r5	@, VP0_DCIADJSW10
	bl	PQ_HAL_RegWrite	@
	b	.L48	@
.L50:
	.align	2
.L49:
	.word	.LANCHOR0+140
	.fnend
	.size	PQ_HAL_SetDCIParam, .-PQ_HAL_SetDCIParam
	.align	2
	.global	PQ_HAL_UpdateDCICoef
	.type	PQ_HAL_UpdateDCICoef, %function
PQ_HAL_UpdateDCICoef:
	.fnstart
.LFB1393:
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
	bls	.L52	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L55	@,
	mov	r3, #69	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
.L54:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L52:
	bl	PQ_HAL_GetVdpReg	@
	add	r1, r0, #16384	@ tmp142,,
	add	r0, r1, #24	@ tmp142, tmp142,
	add	r4, r0, r4, asl #11	@, D.35425, tmp142, u32ChId,
	mov	r0, r4	@, D.35425
	bl	PQ_HAL_RegRead	@
	orr	r1, r0, #2	@ VP0_PARAUP,,
	mov	r0, r4	@, D.35425
	bl	PQ_HAL_RegWrite	@
	b	.L54	@
.L56:
	.align	2
.L55:
	.word	.LANCHOR0+160
	.fnend
	.size	PQ_HAL_UpdateDCICoef, .-PQ_HAL_UpdateDCICoef
	.global	__aeabi_uidiv
	.align	2
	.global	PQ_HAL_GetDCIHistgram
	.type	PQ_HAL_GetDCIHistgram, %function
PQ_HAL_GetDCIHistgram:
	.fnstart
.LFB1407:
	@ args = 0, pretend = 0, frame = 8
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
	subs	r7, r0, #0	@ pstDciHist, pstDciHist
	mov	r4, #0	@ tmp178,
	str	r4, [fp, #-40]	@ tmp178, u32TempValue
	beq	.L65	@,
	bl	PQ_HAL_GetVdpReg	@
	mov	r6, #524	@ tmp187,
	add	r5, r0, #1088	@ D.36192,,
	mov	r0, r5	@, D.36192
	bl	PQ_HAL_RegRead	@
	orr	r1, r0, #2	@ VP0_PARARD,,
	mov	r0, r5	@, D.36192
	bl	PQ_HAL_RegWrite	@
	movw	r3, #:lower16:.LANCHOR1	@ tmp183,
	movt	r3, #:upper16:.LANCHOR1	@ tmp183,
	movw	r1, #526	@ tmp184,
	mov	r2, #520	@ tmp194,
	movw	ip, #522	@ tmp191,
	ldrh	r0, [r3, r1]	@ sg_stDciWindow.u16Vend, sg_stDciWindow.u16Vend
	ldrh	r2, [r3, r2]	@ sg_stDciWindow.u16Hstart, sg_stDciWindow.u16Hstart
	ldrh	r1, [r3, r6]	@ sg_stDciWindow.u16Vstart, sg_stDciWindow.u16Vstart
	ldrh	r6, [r3, ip]	@ sg_stDciWindow.u16Hend, sg_stDciWindow.u16Hend
	rsb	r3, r1, r0	@ tmp189, sg_stDciWindow.u16Vstart, sg_stDciWindow.u16Vend
	rsb	r6, r2, r6	@ tmp196, sg_stDciWindow.u16Hstart, sg_stDciWindow.u16Hend
	mul	r6, r6, r3	@ u32WinSize, tmp196, tmp189
	cmp	r6, #0	@ u32WinSize,
	subne	r8, fp, #40	@ tmp209,,
	beq	.L66	@,
.L61:
	mov	r2, r8	@, tmp209
	mov	r0, #0	@,
	movw	r1, #:lower16:-120847360	@,
	movt	r1, #:upper16:-120847360	@,
	bl	PQ_HAL_ReadRegister	@
	ldr	r3, [fp, #-40]	@ u32TempValue, u32TempValue
	mov	r1, r6	@, u32WinSize
	add	r5, r4, #4	@ tmp213, ivtmp.719,
	mov	r0, r3, asl #8	@, u32TempValue,
	bl	__aeabi_uidiv	@
	mov	r2, r8	@, tmp209
	movw	r1, #:lower16:-120847360	@,
	movt	r1, #:upper16:-120847360	@,
	str	r0, [r7, r4]	@, <variable>.s32HistGram
	mov	r0, #0	@,
	bl	PQ_HAL_ReadRegister	@
	ldr	r0, [fp, #-40]	@ u32TempValue, u32TempValue
	mov	r1, r6	@, u32WinSize
	add	r4, r5, #4	@ ivtmp.719, tmp213,
	mov	r0, r0, asl #8	@, u32TempValue,
	bl	__aeabi_uidiv	@
	cmp	r4, #128	@ ivtmp.719,
	str	r0, [r7, r5]	@, <variable>.s32HistGram
	bne	.L61	@,
	bl	PQ_HAL_GetVdpReg	@
	add	r4, r0, #1088	@ temp.724,,
	mov	r0, r4	@, temp.724
	bl	PQ_HAL_RegRead	@
	mov	ip, r0	@ VP0_PARARD,
	mov	r0, r4	@, temp.724
	bic	r1, ip, #2	@, VP0_PARARD,
	bl	PQ_HAL_RegWrite	@
	mov	r0, #0	@ D.36189,
.L59:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L65:
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	ldr	r2, .L67	@,
	mov	r3, #764	@,
	movw	ip, #:lower16:.LC2	@ tmp181,
	movt	ip, #:upper16:.LC2	@ tmp181,
	str	ip, [sp, #0]	@ tmp181,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.36189,
	b	.L59	@
.L66:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L67	@,
	movw	r3, #777	@,
	movw	lr, #:lower16:.LC3	@ tmp200,
	movt	lr, #:upper16:.LC3	@ tmp200,
	str	lr, [sp, #0]	@ tmp200,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.36189,
	b	.L59	@
.L68:
	.align	2
.L67:
	.word	.LANCHOR0+184
	.fnend
	.size	PQ_HAL_GetDCIHistgram, .-PQ_HAL_GetDCIHistgram
	.align	2
	.global	PQ_HAL_DCIDeinit
	.type	PQ_HAL_DCIDeinit, %function
PQ_HAL_DCIDeinit:
	.fnstart
.LFB1395:
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
	ldr	r3, [r4, #528]	@ sg_bDciInitFlag, sg_bDciInitFlag
	cmp	r3, #0	@ sg_bDciInitFlag,
	beq	.L70	@,
	add	r0, r4, #532	@, tmp134,
	bl	HI_DRV_MMZ_UnmapAndRelease	@
	mov	r0, #0	@ tmp139,
	str	r0, [r4, #528]	@ tmp139, sg_bDciInitFlag
.L70:
	mov	r0, #0	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	PQ_HAL_DCIDeinit, .-PQ_HAL_DCIDeinit
	.align	2
	.global	PQ_HAL_DCIInit
	.type	PQ_HAL_DCIInit, %function
PQ_HAL_DCIInit:
	.fnstart
.LFB1394:
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
	movw	r4, #:lower16:.LANCHOR1	@ tmp136,
	movt	r4, #:upper16:.LANCHOR1	@ tmp136,
	ldr	r3, [r4, #528]	@ sg_bDciInitFlag, sg_bDciInitFlag
	cmp	r3, #1	@ sg_bDciInitFlag,
	moveq	r0, #0	@ D.35442,
	beq	.L74	@,
	add	r5, r4, #532	@ tmp139, tmp136,
	mov	r1, #12	@,
	mov	r0, r5	@, tmp139
	bl	__memzero	@
	mov	r1, #0	@,
	movw	r0, #:lower16:.LC4	@,
	mov	r2, #320	@,
	movt	r0, #:upper16:.LC4	@,
	mov	r3, r1	@,
	str	r5, [sp, #0]	@ tmp139,
	bl	HI_DRV_MMZ_AllocAndMap	@
	subs	r5, r0, #0	@ s32Ret,
	bne	.L77	@,
	ldr	r0, [r4, #532]	@, sg_stDciBuf.u32StartVirAddr
	mov	r1, #320	@,
	bl	__memzero	@
	mov	r0, r5	@ D.35442, s32Ret
	mov	r1, #1	@ tmp149,
	str	r1, [r4, #528]	@ tmp149, sg_bDciInitFlag
.L74:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L77:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L78	@,
	mov	r3, #138	@,
	movw	ip, #:lower16:.LC5	@ tmp145,
	movt	ip, #:upper16:.LC5	@ tmp145,
	str	ip, [sp, #0]	@ tmp145,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35442,
	b	.L74	@
.L79:
	.align	2
.L78:
	.word	.LANCHOR0+208
	.fnend
	.size	PQ_HAL_DCIInit, .-PQ_HAL_DCIInit
	.align	2
	.global	PQ_HAL_SetDCILut
	.type	PQ_HAL_SetDCILut, %function
PQ_HAL_SetDCILut:
	.fnstart
.LFB1406:
	@ args = 0, pretend = 0, frame = 336
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #348
	sub	sp, sp, #348	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	sub	r6, fp, #364	@ tmp210,,
	mov	r4, r0	@ pstDciLut, pstDciLut
	mov	r1, #0	@,
	mov	r2, #320	@,
	mov	r0, r6	@, tmp210
	bl	memset	@
	cmp	r4, #0	@ pstDciLut,
	beq	.L90	@,
	movw	r2, #:lower16:.LANCHOR1	@,
	movt	r2, #:upper16:.LANCHOR1	@,
	str	r2, [fp, #-372]	@, %sfp
	mov	r1, r4	@, pstDciLut
	mov	r2, #520	@,
	ldr	r0, [fp, #-372]	@, %sfp
	bl	memcpy	@
	ldr	r5, [fp, #-372]	@ ivtmp.944, %sfp
	mov	ip, #0	@ ivtmp.905,
	mov	r4, #5	@ tmp458,
.L83:
	ldr	r7, [fp, #-372]	@ D.37324, %sfp
	mov	r1, #0	@,
	mov	r2, r6	@, ivtmp.907
	mov	r3, r1	@,
	add	sl, r6, #4	@ D.36994, ivtmp.907,
	add	r8, r6, #8	@ D.37013, ivtmp.907,
	ldrsh	r0, [r7, ip]!	@ tmp225, sg_stDciLut.s16HistCoef0
	add	r9, r6, #12	@ D.37032, ivtmp.907,
	str	ip, [fp, #-376]	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldr	ip, [fp, #-376]	@,
	mov	r2, r6	@, ivtmp.907
	ldrsh	r0, [r5, #2]	@ tmp227, sg_stDciLut.s16HistCoef0
	mov	r1, #0	@,
	mov	r3, r4	@, tmp458
	add	ip, ip, #16	@ ivtmp.905, ivtmp.905,
	str	r4, [sp, #0]	@ tmp458,
	str	ip, [fp, #-376]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #64]	@ tmp229, sg_stDciLut.s16HistCoef1
	mov	r2, r6	@, ivtmp.907
	mov	r1, #0	@,
	mov	r3, #10	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #66]	@ tmp231, sg_stDciLut.s16HistCoef1
	mov	r2, r6	@, ivtmp.907
	mov	r1, #0	@,
	mov	r3, #15	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #128]	@ tmp233, sg_stDciLut.s16HistCoef2
	mov	r2, r6	@, ivtmp.907
	mov	r1, #0	@,
	mov	r3, #20	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r7, #130]	@ tmp236, sg_stDciLut.s16HistCoef2
	mov	r2, r6	@, ivtmp.907
	mov	r1, #0	@,
	mov	r3, #25	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #4]	@ tmp238, sg_stDciLut.s16HistCoef0
	mov	r2, r6	@, ivtmp.907
	mov	r1, #0	@,
	mov	r3, #30	@,
	mov	lr, #2	@,
	str	lr, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #4]	@ tmp240, sg_stDciLut.s16HistCoef0
	mov	r2, sl	@, D.36994
	mov	r1, #2	@,
	mov	r3, #0	@,
	mov	ip, #3	@,
	str	ip, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #6]	@ tmp242, sg_stDciLut.s16HistCoef0
	mov	r2, sl	@, D.36994
	mov	r1, #0	@,
	mov	r3, #3	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #68]	@ tmp244, sg_stDciLut.s16HistCoef1
	mov	r2, sl	@, D.36994
	mov	r1, #0	@,
	mov	r3, #8	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #70]	@ tmp246, sg_stDciLut.s16HistCoef1
	mov	r2, sl	@, D.36994
	mov	r1, #0	@,
	mov	r3, #13	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r7, #132]	@ tmp248, sg_stDciLut.s16HistCoef2
	mov	r2, sl	@, D.36994
	mov	r1, #0	@,
	mov	r3, #18	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r7, #134]	@ tmp250, sg_stDciLut.s16HistCoef2
	mov	r2, sl	@, D.36994
	mov	r1, #0	@,
	mov	r3, #23	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #8]	@ tmp252, sg_stDciLut.s16HistCoef0
	mov	r2, sl	@, D.36994
	mov	r1, #0	@,
	mov	r3, #28	@,
	mov	lr, #4	@,
	str	lr, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #8]	@ tmp254, sg_stDciLut.s16HistCoef0
	mov	r2, r8	@, D.37013
	mov	r1, #4	@,
	mov	r3, #0	@,
	mov	ip, #1	@,
	str	ip, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #10]	@ tmp256, sg_stDciLut.s16HistCoef0
	mov	r2, r8	@, D.37013
	mov	r1, #0	@,
	mov	r3, #1	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #72]	@ tmp258, sg_stDciLut.s16HistCoef1
	mov	r2, r8	@, D.37013
	mov	r1, #0	@,
	mov	r3, #6	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #74]	@ tmp260, sg_stDciLut.s16HistCoef1
	mov	r2, r8	@, D.37013
	mov	r1, #0	@,
	mov	r3, #11	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r7, #136]	@ tmp262, sg_stDciLut.s16HistCoef2
	mov	r2, r8	@, D.37013
	mov	r1, #0	@,
	mov	r3, #16	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r7, #138]	@ tmp264, sg_stDciLut.s16HistCoef2
	mov	r2, r8	@, D.37013
	mov	r1, #0	@,
	mov	r3, #21	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #12]	@ tmp266, sg_stDciLut.s16HistCoef0
	mov	r2, r8	@, D.37013
	mov	r1, #0	@,
	mov	r3, #26	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #14]	@ tmp268, sg_stDciLut.s16HistCoef0
	mov	r2, r8	@, D.37013
	mov	r1, #0	@,
	mov	r3, #31	@,
	mov	sl, #1	@,
	str	sl, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #14]	@ tmp270, sg_stDciLut.s16HistCoef0
	mov	r1, #1	@,
	mov	r2, r9	@, D.37032
	mov	r3, #0	@,
	mov	r8, #4	@,
	str	r8, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #76]	@ tmp272, sg_stDciLut.s16HistCoef1
	mov	r1, #0	@,
	mov	r2, r9	@, D.37032
	mov	r3, #4	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r5, #78]	@ tmp274, sg_stDciLut.s16HistCoef1
	mov	r1, #0	@,
	mov	r2, r9	@, D.37032
	mov	r3, #9	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r7, #140]	@ tmp276, sg_stDciLut.s16HistCoef2
	mov	r1, #0	@,
	mov	r2, r9	@, D.37032
	mov	r3, #14	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r7, #142]	@ tmp278, sg_stDciLut.s16HistCoef2
	mov	r1, #0	@,
	mov	r2, r9	@, D.37032
	mov	r3, #19	@,
	str	r4, [sp, #0]	@ tmp458,
	bl	PQ_HAL_CopyU32ByBit	@
	mov	r0, #0	@,
	mov	r2, r9	@, D.37032
	mov	r1, r0	@,
	mov	r3, #24	@,
	mov	lr, #8	@,
	str	lr, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldr	ip, [fp, #-376]	@,
	add	r6, r6, #16	@ ivtmp.907, ivtmp.907,
	add	r5, r5, #16	@ ivtmp.944, ivtmp.944,
	cmp	ip, #64	@ ivtmp.905,
	bne	.L83	@,
	ldr	r4, .L91	@ ivtmp.880,
	sub	r6, fp, #300	@ ivtmp.883,,
	mov	r8, #8	@ tmp452,
	mov	sl, #4	@ tmp454,
	mov	r5, #12	@ tmp450,
.L84:
	mov	r1, #0	@,
	ldrsh	r0, [r4, #0]	@ tmp284, sg_stDciLut.s16YDivCoef
	mov	r2, r6	@, ivtmp.883
	mov	r3, r1	@,
	add	lr, r6, #8	@, ivtmp.883,
	add	r7, r6, #4	@ D.37060, ivtmp.883,
	str	lr, [fp, #-368]	@, %sfp
	add	r9, r6, #12	@ D.37085, ivtmp.883,
	str	r5, [sp, #0]	@ tmp450,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #2]	@ tmp286, sg_stDciLut.s16YDivCoef
	mov	r2, r6	@, ivtmp.883
	mov	r1, #0	@,
	mov	r3, r5	@, tmp450
	str	r5, [sp, #0]	@ tmp450,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #4]	@ tmp288, sg_stDciLut.s16YDivCoef
	mov	r2, r6	@, ivtmp.883
	mov	r1, #0	@,
	mov	r3, #24	@,
	str	r8, [sp, #0]	@ tmp452,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #4]	@ tmp290, sg_stDciLut.s16YDivCoef
	mov	r1, r8	@, tmp452
	mov	r2, r7	@, D.37060
	mov	r3, #0	@,
	str	sl, [sp, #0]	@ tmp454,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #6]	@ tmp292, sg_stDciLut.s16YDivCoef
	mov	r1, #0	@,
	mov	r2, r7	@, D.37060
	mov	r3, sl	@, tmp454
	str	r5, [sp, #0]	@ tmp450,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #8]	@ tmp294, sg_stDciLut.s16YDivCoef
	mov	r1, #0	@,
	mov	r2, r7	@, D.37060
	mov	r3, #16	@,
	str	r5, [sp, #0]	@ tmp450,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #10]	@ tmp296, sg_stDciLut.s16YDivCoef
	mov	r2, r7	@, D.37060
	mov	r1, #0	@,
	mov	r3, #28	@,
	str	sl, [sp, #0]	@ tmp454,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #10]	@ tmp298, sg_stDciLut.s16YDivCoef
	mov	r1, sl	@, tmp454
	ldr	r2, [fp, #-368]	@, %sfp
	mov	r3, #0	@,
	str	r8, [sp, #0]	@ tmp452,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #12]	@ tmp300, sg_stDciLut.s16YDivCoef
	mov	r1, #0	@,
	ldr	r2, [fp, #-368]	@, %sfp
	mov	r3, r8	@, tmp452
	str	r5, [sp, #0]	@ tmp450,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #14]	@ tmp302, sg_stDciLut.s16YDivCoef
	mov	r1, #0	@,
	ldr	r2, [fp, #-368]	@, %sfp
	mov	r3, #20	@,
	str	r5, [sp, #0]	@ tmp450,
	bl	PQ_HAL_CopyU32ByBit	@
	mov	r1, #0	@,
	ldrsh	r0, [r4, #16]	@ tmp304, sg_stDciLut.s16YDivCoef
	mov	r3, r1	@,
	mov	r2, r9	@, D.37085
	str	r5, [sp, #0]	@ tmp450,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #18]	@ tmp306, sg_stDciLut.s16YDivCoef
	mov	r1, #0	@,
	mov	r2, r9	@, D.37085
	mov	r3, r5	@, tmp450
	str	r5, [sp, #0]	@ tmp450,
	bl	PQ_HAL_CopyU32ByBit	@
	mov	r0, #0	@,
	mov	r2, r9	@, D.37085
	mov	r1, r0	@,
	mov	r3, #24	@,
	str	r8, [sp, #0]	@ tmp452,
	bl	PQ_HAL_CopyU32ByBit	@
	ldr	r0, .L91+4	@,
	add	r4, r4, #20	@ ivtmp.880, ivtmp.880,
	add	r6, r6, #16	@ ivtmp.883, ivtmp.883,
	cmp	r4, r0	@ ivtmp.880,
	bne	.L84	@,
	ldr	r1, [fp, #-372]	@, %sfp
	sub	r7, fp, #364	@ tmp312,,
	add	r4, r7, #160	@ tmp314, tmp312,
	mov	r3, #312	@ tmp310,
	movw	r9, #314	@ tmp317,
	mov	r6, #316	@ tmp324,
	ldrsh	r0, [r1, r3]	@ sg_stDciLut.s16YDivCoef, sg_stDciLut.s16YDivCoef
	mov	r1, #0	@,
	mov	r3, r1	@,
	mov	r2, r4	@, tmp314
	str	r5, [sp, #0]	@ tmp450,
	bl	PQ_HAL_CopyU32ByBit	@
	ldr	ip, [fp, #-372]	@, %sfp
	mov	r2, r4	@, tmp314
	mov	r3, r5	@, tmp450
	mov	r1, #0	@,
	ldrsh	r0, [ip, r9]	@ sg_stDciLut.s16YDivCoef, sg_stDciLut.s16YDivCoef
	add	r9, r7, #164	@ tmp335, tmp312,
	str	r5, [sp, #0]	@ tmp450,
	bl	PQ_HAL_CopyU32ByBit	@
	ldr	lr, [fp, #-372]	@, %sfp
	mov	r2, r4	@, tmp314
	mov	r1, #0	@,
	mov	r3, #24	@,
	ldr	r4, .L91+8	@ ivtmp.860,
	ldrsh	r0, [lr, r6]	@ sg_stDciLut.s16YDivCoef, sg_stDciLut.s16YDivCoef
	str	r8, [sp, #0]	@ tmp452,
	bl	PQ_HAL_CopyU32ByBit	@
	ldr	r2, [fp, #-372]	@, %sfp
	mov	r1, r8	@, tmp452
	mov	r3, #0	@,
	mov	r8, #32	@,
	ldrsh	r0, [r2, r6]	@ sg_stDciLut.s16YDivCoef, sg_stDciLut.s16YDivCoef
	mov	r2, r9	@, tmp335
	str	sl, [sp, #0]	@ tmp454,
	bl	PQ_HAL_CopyU32ByBit	@
	ldr	r1, [fp, #-372]	@, %sfp
	movw	r3, #318	@ tmp338,
	mov	r2, r9	@, tmp335
	add	r6, r7, #176	@ ivtmp.857, tmp312,
	ldrsh	r0, [r1, r3]	@ sg_stDciLut.s16YDivCoef, sg_stDciLut.s16YDivCoef
	mov	r1, #0	@,
	mov	r3, sl	@, tmp454
	str	r5, [sp, #0]	@ tmp450,
	bl	PQ_HAL_CopyU32ByBit	@
	mov	ip, #16	@ tmp347,
	mov	r0, #0	@,
	mov	r3, ip	@, tmp347
	mov	r2, r9	@, tmp335
	mov	r1, r0	@,
	str	ip, [sp, #0]	@ tmp347,
	bl	PQ_HAL_CopyU32ByBit	@
	mov	r0, #0	@,
	add	r2, r7, #168	@, tmp312,
	mov	r1, r0	@,
	mov	r3, r0	@,
	str	r8, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	mov	r0, #0	@,
	add	r2, r7, #172	@, tmp312,
	mov	r1, r0	@,
	mov	r3, r0	@,
	mov	r5, #32	@,
	str	r5, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	mov	r9, sl	@ tmp448, tmp454
	mov	r5, #10	@ tmp442,
.L85:
	mov	r1, #0	@,
	ldrsh	r0, [r4, #-66]	@ tmp361, sg_stDciLut.s16WgtCoef0
	mov	r2, r6	@, ivtmp.857
	mov	r3, r1	@,
	str	r5, [sp, #0]	@ tmp442,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #0]	@ tmp363, sg_stDciLut.s16WgtCoef1
	mov	r2, r6	@, ivtmp.857
	mov	r1, #0	@,
	mov	r3, r5	@, tmp442
	add	r7, r6, #4	@ D.37117, ivtmp.857,
	str	r5, [sp, #0]	@ tmp442,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #66]	@ tmp365, sg_stDciLut.s16WgtCoef2
	mov	r2, r6	@, ivtmp.857
	mov	r1, #0	@,
	mov	r3, #20	@,
	str	r5, [sp, #0]	@ tmp442,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #-64]	@ tmp367, sg_stDciLut.s16WgtCoef0
	mov	r2, r6	@, ivtmp.857
	mov	r1, #0	@,
	mov	r3, #30	@,
	mov	lr, #2	@,
	str	lr, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #-64]	@ tmp369, sg_stDciLut.s16WgtCoef0
	mov	r2, r7	@, D.37117
	mov	r1, #2	@,
	mov	r3, #0	@,
	mov	ip, #8	@,
	str	ip, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #2]	@ tmp371, sg_stDciLut.s16WgtCoef1
	mov	r2, r7	@, D.37117
	mov	r1, #0	@,
	mov	r3, #8	@,
	add	r8, r6, #8	@ D.37129, ivtmp.857,
	str	r5, [sp, #0]	@ tmp442,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #68]	@ tmp373, sg_stDciLut.s16WgtCoef2
	mov	r2, r7	@, D.37117
	mov	r1, #0	@,
	mov	r3, #18	@,
	str	r5, [sp, #0]	@ tmp442,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #-62]	@ tmp375, sg_stDciLut.s16WgtCoef0
	mov	r2, r7	@, D.37117
	mov	r1, #0	@,
	mov	r3, #28	@,
	str	r9, [sp, #0]	@ tmp448,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #-62]	@ tmp377, sg_stDciLut.s16WgtCoef0
	mov	r1, r9	@, tmp448
	mov	r2, r8	@, D.37129
	mov	r3, #0	@,
	mov	lr, #6	@,
	str	lr, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #4]	@ tmp379, sg_stDciLut.s16WgtCoef1
	mov	r1, #0	@,
	mov	r2, r8	@, D.37129
	mov	r3, #6	@,
	add	sl, r6, #12	@ D.37138, ivtmp.857,
	str	r5, [sp, #0]	@ tmp442,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #70]	@ tmp381, sg_stDciLut.s16WgtCoef2
	mov	r1, #0	@,
	mov	r2, r8	@, D.37129
	mov	r3, #16	@,
	str	r5, [sp, #0]	@ tmp442,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #-60]	@ tmp383, sg_stDciLut.s16WgtCoef0
	mov	r2, r8	@, D.37129
	mov	r1, #0	@,
	mov	r3, #26	@,
	mov	ip, #6	@,
	str	ip, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #-60]	@ tmp385, sg_stDciLut.s16WgtCoef0
	mov	r1, #6	@,
	mov	r2, sl	@, D.37138
	mov	r3, #0	@,
	str	r9, [sp, #0]	@ tmp448,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #6]	@ tmp387, sg_stDciLut.s16WgtCoef1
	mov	r1, #0	@,
	mov	r2, sl	@, D.37138
	mov	r3, r9	@, tmp448
	str	r5, [sp, #0]	@ tmp442,
	bl	PQ_HAL_CopyU32ByBit	@
	ldrsh	r0, [r4, #72]	@ tmp389, sg_stDciLut.s16WgtCoef2
	mov	r1, #0	@,
	mov	r2, sl	@, D.37138
	mov	r3, #14	@,
	str	r5, [sp, #0]	@ tmp442,
	bl	PQ_HAL_CopyU32ByBit	@
	mov	r0, #0	@,
	mov	r1, r0	@,
	mov	r2, sl	@, D.37138
	mov	r3, #24	@,
	mov	r7, #8	@,
	str	r7, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	ldr	r0, .L91+12	@,
	add	r4, r4, #8	@ ivtmp.860, ivtmp.860,
	add	r6, r6, #16	@ ivtmp.857, ivtmp.857,
	cmp	r4, r0	@ ivtmp.860,
	bne	.L85	@,
	ldr	r7, [fp, #-372]	@, %sfp
	sub	r4, fp, #364	@ tmp395,,
	mov	r6, #384	@ tmp393,
	mov	r1, #0	@,
	mov	r3, r1	@,
	ldrsh	r0, [r7, r6]	@ sg_stDciLut.s16WgtCoef0, sg_stDciLut.s16WgtCoef0
	add	r6, r4, #304	@ tmp397, tmp395,
	str	r5, [sp, #0]	@ tmp442,
	mov	r7, #32	@ tmp420,
	mov	r2, r6	@, tmp397
	bl	PQ_HAL_CopyU32ByBit	@
	ldr	lr, [fp, #-372]	@, %sfp
	movw	r2, #450	@ tmp400,
	mov	r3, r5	@, tmp442
	mov	r1, #0	@,
	ldrsh	r0, [lr, r2]	@ sg_stDciLut.s16WgtCoef1, sg_stDciLut.s16WgtCoef1
	mov	r2, r6	@, tmp397
	str	r5, [sp, #0]	@ tmp442,
	bl	PQ_HAL_CopyU32ByBit	@
	ldr	r1, [fp, #-372]	@, %sfp
	mov	r3, #516	@ tmp407,
	mov	r2, r6	@, tmp397
	ldrsh	r0, [r1, r3]	@ sg_stDciLut.s16WgtCoef2, sg_stDciLut.s16WgtCoef2
	mov	r1, #0	@,
	mov	r3, #20	@,
	str	r5, [sp, #0]	@ tmp442,
	bl	PQ_HAL_CopyU32ByBit	@
	mov	r0, #0	@,
	mov	r1, r0	@,
	mov	r2, r6	@, tmp397
	mov	r3, #30	@,
	mov	ip, #2	@,
	str	ip, [sp, #0]	@,
	bl	PQ_HAL_CopyU32ByBit	@
	mov	r0, #0	@,
	add	r2, r4, #308	@, tmp395,
	mov	r1, r0	@,
	mov	r3, r0	@,
	str	r7, [sp, #0]	@ tmp420,
	bl	PQ_HAL_CopyU32ByBit	@
	mov	r0, #0	@,
	add	r2, r4, #312	@, tmp395,
	mov	r1, r0	@,
	mov	r3, r0	@,
	str	r7, [sp, #0]	@ tmp420,
	bl	PQ_HAL_CopyU32ByBit	@
	mov	r0, #0	@,
	add	r2, r4, #316	@, tmp395,
	mov	r3, r0	@,
	mov	r1, r0	@,
	str	r7, [sp, #0]	@ tmp420,
	bl	PQ_HAL_CopyU32ByBit	@
	ldr	r5, [fp, #-372]	@, %sfp
	mov	r1, r4	@, tmp395
	mov	r2, #320	@,
	ldr	r0, [r5, #532]	@, sg_stDciBuf.u32StartVirAddr
	bl	memcpy	@
	ldr	r4, [fp, #-372]	@, %sfp
	ldr	r5, [r4, #536]	@ D.36169, sg_stDciBuf.u32StartPhyAddr
	bl	PQ_HAL_GetVdpReg	@
	add	r2, r0, #16384	@ D.36443,,
	add	r4, r2, #16	@ D.36443, D.36443,
	mov	r0, r4	@, D.36443
	bl	PQ_HAL_RegRead	@
	mov	r0, r4	@, D.36443
	mov	r1, r5	@, D.36169
	bl	PQ_HAL_RegWrite	@
	mov	r0, #0	@,
	bl	PQ_HAL_UpdateDCICoef	@
	mov	r0, #0	@ D.36164,
.L82:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L90:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L91+16	@,
	mov	r3, #728	@,
	movw	ip, #:lower16:.LC6	@ tmp216,
	movt	ip, #:upper16:.LC6	@ tmp216,
	str	ip, [sp, #0]	@ tmp216,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.36164,
	b	.L82	@
.L92:
	.align	2
.L91:
	.word	.LANCHOR1+192
	.word	.LANCHOR1+312
	.word	.LANCHOR1+386
	.word	.LANCHOR1+450
	.word	.LANCHOR0+224
	.fnend
	.size	PQ_HAL_SetDCILut, .-PQ_HAL_SetDCILut
	.align	2
	.global	PQ_HAL_SetDCIWgtLut
	.type	PQ_HAL_SetDCIWgtLut, %function
PQ_HAL_SetDCIWgtLut:
	.fnstart
.LFB1404:
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
	subs	r4, r0, #0	@ pstDciCoef, pstDciCoef
	beq	.L97	@,
	mov	r1, r4	@, pstDciCoef
	mov	r2, #66	@,
	ldr	r0, .L98	@,
	bl	memcpy	@
	add	r1, r4, #66	@, pstDciCoef,
	mov	r2, #66	@,
	ldr	r0, .L98+4	@,
	bl	memcpy	@
	add	r1, r4, #132	@, pstDciCoef,
	mov	r2, #66	@,
	ldr	r0, .L98+8	@,
	bl	memcpy	@
	movw	r0, #:lower16:.LANCHOR1	@,
	movt	r0, #:upper16:.LANCHOR1	@,
	bl	PQ_HAL_SetDCILut	@
	mov	r0, #0	@ D.36133,
.L95:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L97:
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	ldr	r2, .L98+12	@,
	mov	r3, #672	@,
	movw	ip, #:lower16:.LC1	@ tmp138,
	movt	ip, #:upper16:.LC1	@ tmp138,
	str	ip, [sp, #0]	@ tmp138,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.36133,
	b	.L95	@
.L99:
	.align	2
.L98:
	.word	.LANCHOR1+320
	.word	.LANCHOR1+386
	.word	.LANCHOR1+452
	.word	.LANCHOR0+244
	.fnend
	.size	PQ_HAL_SetDCIWgtLut, .-PQ_HAL_SetDCIWgtLut
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.36047, %object
	.size	__func__.36047, 19
__func__.36047:
	.ascii	"PQ_HAL_GetDCIlevel\000"
	.space	1
	.type	__func__.36137, %object
	.size	__func__.36137, 20
__func__.36137:
	.ascii	"PQ_HAL_GetDCIWgtLut\000"
	.type	__func__.36004, %object
	.size	__func__.36004, 20
__func__.36004:
	.ascii	"PQ_HAL_GetDCIEnable\000"
	.type	__func__.36102, %object
	.size	__func__.36102, 20
__func__.36102:
	.ascii	"PQ_HAL_SetDCIWindow\000"
	.type	__func__.36073, %object
	.size	__func__.36073, 19
__func__.36073:
	.ascii	"PQ_HAL_SetDCIlevel\000"
	.space	1
	.type	__func__.36024, %object
	.size	__func__.36024, 17
__func__.36024:
	.ascii	"PQ_HAL_EnableDCI\000"
	.space	3
	.type	__func__.35983, %object
	.size	__func__.35983, 19
__func__.35983:
	.ascii	"PQ_HAL_DCIDemoMode\000"
	.space	1
	.type	__func__.35514, %object
	.size	__func__.35514, 19
__func__.35514:
	.ascii	"PQ_HAL_SetDCIParam\000"
	.space	1
	.type	__func__.35415, %object
	.size	__func__.35415, 21
__func__.35415:
	.ascii	"PQ_HAL_UpdateDCICoef\000"
	.space	3
	.type	__func__.36180, %object
	.size	__func__.36180, 22
__func__.36180:
	.ascii	"PQ_HAL_GetDCIHistgram\000"
	.space	2
	.type	__func__.35435, %object
	.size	__func__.35435, 15
__func__.35435:
	.ascii	"PQ_HAL_DCIInit\000"
	.space	1
	.type	__func__.36158, %object
	.size	__func__.36158, 17
__func__.36158:
	.ascii	"PQ_HAL_SetDCILut\000"
	.space	3
	.type	__func__.36127, %object
	.size	__func__.36127, 20
__func__.36127:
	.ascii	"PQ_HAL_SetDCIWgtLut\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"select wrong VP layer id\012\000"
	.space	2
.LC1:
	.ascii	"pstDciCoef is null point! \012\000"
.LC2:
	.ascii	"pstDciHist is null point! \012\000"
.LC3:
	.ascii	"DCI window is wrong settingt! \012\000"
.LC4:
	.ascii	"PQ_dci\000"
	.space	1
.LC5:
	.ascii	"PQ_dci memory allocated failed!\012\000"
	.space	3
.LC6:
	.ascii	"pstDciLut is null point! \012\000"
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	sg_stDciLut, %object
	.size	sg_stDciLut, 520
sg_stDciLut:
	.space	520
	.type	sg_stDciWindow, %object
	.size	sg_stDciWindow, 8
sg_stDciWindow:
	.space	8
	.type	sg_bDciInitFlag, %object
	.size	sg_bDciInitFlag, 4
sg_bDciInitFlag:
	.space	4
	.type	sg_stDciBuf, %object
	.size	sg_stDciBuf, 12
sg_stDciBuf:
	.space	12
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
