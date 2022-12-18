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
	.file	"pq_hal_sharpen.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_hal_sharpen)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/hal/hi3798mv100/.pq_hal_sharpen.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_sharpen.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_sharpen.o -O2 -Wall -Wundef
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
	.global	PQ_HAL_EnableLTIDemo
	.type	PQ_HAL_EnableLTIDemo, %function
PQ_HAL_EnableLTIDemo:
	.fnstart
.LFB1399:
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
	mov	r4, r1	@ bOnOff, bOnOff
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	beq	.L6	@,
	ldrb	r2, [r3, #387]	@ zero_extendqisi2	@,
	mov	r0, #0	@ D.35507,
	bfi	r2, r4, #6, #1	@ tmp140, bOnOff,,
	strb	r2, [r3, #387]	@ tmp140,
.L3:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L6:
	mov	r0, #1	@,
	mov	r1, #41	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	mov	r3, #243	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	movw	ip, #:lower16:.LC0	@ tmp139,
	movt	ip, #:upper16:.LC0	@ tmp139,
	str	ip, [sp, #0]	@ tmp139,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35507,
	b	.L3	@
	.fnend
	.size	PQ_HAL_EnableLTIDemo, .-PQ_HAL_EnableLTIDemo
	.align	2
	.global	PQ_HAL_EnableCTIDemo
	.type	PQ_HAL_EnableCTIDemo, %function
PQ_HAL_EnableCTIDemo:
	.fnstart
.LFB1398:
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
	mov	r4, r1	@ bOnOff, bOnOff
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	beq	.L11	@,
	ldrb	r2, [r3, #407]	@ zero_extendqisi2	@,
	mov	r0, #0	@ D.35495,
	bfi	r2, r4, #6, #1	@ tmp141, bOnOff,,
	strb	r2, [r3, #407]	@ tmp141,
.L9:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L11:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L12	@,
	mov	r3, #222	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35495,
	b	.L9	@
.L13:
	.align	2
.L12:
	.word	.LANCHOR0+24
	.fnend
	.size	PQ_HAL_EnableCTIDemo, .-PQ_HAL_EnableCTIDemo
	.align	2
	.global	PQ_HAL_SetSharpStrReg
	.type	PQ_HAL_SetSharpStrReg, %function
PQ_HAL_SetSharpStrReg:
	.fnstart
.LFB1397:
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
	mov	r4, r1	@ s32ShpStr, s32ShpStr
	mov	r5, r2	@ pstSharpGainRatio, pstSharpGainRatio
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	beq	.L18	@,
	ldr	r7, [r5, #0]	@ <variable>.u32HD_Lgain_ratio, <variable>.u32HD_Lgain_ratio
	movw	lr, #386	@ tmp147,
	ldrh	r6, [r3, lr]	@,
	movw	r2, #406	@ tmp154,
	ldrh	r1, [r3, r2]	@,
	mov	r0, #0	@ D.35472,
	mul	ip, r7, r4	@ tmp143, <variable>.u32HD_Lgain_ratio, s32ShpStr
	add	r7, ip, #64	@ tmp145, tmp143,
	mov	r7, r7, lsr #7	@ tmp146, tmp145,
	bfi	r6, r7, #0, #12	@ tmp148, tmp146,,
	strh	r6, [r3, lr]	@ movhi	@ tmp148,
	ldr	ip, [r5, #4]	@ <variable>.u32HD_Cgain_ratio, <variable>.u32HD_Cgain_ratio
	mul	lr, ip, r4	@ tmp150, <variable>.u32HD_Cgain_ratio, s32ShpStr
	add	r4, lr, #64	@ tmp152, tmp150,
	mov	r4, r4, lsr #7	@ tmp153, tmp152,
	bfi	r1, r4, #0, #12	@ tmp155, tmp153,,
	strh	r1, [r3, r2]	@ movhi	@ tmp155,
.L16:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L18:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L19	@,
	mov	r3, #198	@,
	movw	ip, #:lower16:.LC0	@ tmp142,
	movt	ip, #:upper16:.LC0	@ tmp142,
	str	ip, [sp, #0]	@ tmp142,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35472,
	b	.L16	@
.L20:
	.align	2
.L19:
	.word	.LANCHOR0+48
	.fnend
	.size	PQ_HAL_SetSharpStrReg, .-PQ_HAL_SetSharpStrReg
	.align	2
	.global	PQ_HAL_EnableCTI
	.type	PQ_HAL_EnableCTI, %function
PQ_HAL_EnableCTI:
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
	mov	r4, r1	@ u8Enable, u8Enable
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	beq	.L25	@,
	ldrb	r2, [r3, #407]	@ zero_extendqisi2	@,
	mov	r0, #0	@ D.35459,
	bfi	r2, r4, #7, #1	@ tmp141, u8Enable,,
	strb	r2, [r3, #407]	@ tmp141,
.L23:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L25:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L26	@,
	mov	r3, #174	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35459,
	b	.L23	@
.L27:
	.align	2
.L26:
	.word	.LANCHOR0+72
	.fnend
	.size	PQ_HAL_EnableCTI, .-PQ_HAL_EnableCTI
	.align	2
	.global	PQ_HAL_EnableLTI
	.type	PQ_HAL_EnableLTI, %function
PQ_HAL_EnableLTI:
	.fnstart
.LFB1395:
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
	mov	r4, r1	@ u8Enable, u8Enable
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	beq	.L32	@,
	ldrb	r2, [r3, #387]	@ zero_extendqisi2	@,
	mov	r0, #0	@ D.35448,
	bfi	r2, r4, #7, #1	@ tmp141, u8Enable,,
	strb	r2, [r3, #387]	@ tmp141,
.L30:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L32:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L33	@,
	mov	r3, #152	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35448,
	b	.L30	@
.L34:
	.align	2
.L33:
	.word	.LANCHOR0+92
	.fnend
	.size	PQ_HAL_EnableLTI, .-PQ_HAL_EnableLTI
	.align	2
	.global	PQ_HAL_GetCTIEnable
	.type	PQ_HAL_GetCTIEnable, %function
PQ_HAL_GetCTIEnable:
	.fnstart
.LFB1394:
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
	mov	r4, r1	@ pu8Enable, pu8Enable
	bl	PQ_HAL_GetVpssReg	@
	cmp	r0, #0	@ pstVpssVirReg
	beq	.L39	@,
	ldrb	r1, [r0, #407]	@ zero_extendqisi2	@ tmp142,
	mov	r0, #0	@ D.35436,
	ubfx	r3, r1, #7, #1	@ tmp143, tmp142,,
	strb	r3, [r4, #0]	@ tmp143,* pu8Enable
.L37:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L39:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L40	@,
	mov	r3, #130	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35436,
	b	.L37	@
.L41:
	.align	2
.L40:
	.word	.LANCHOR0+112
	.fnend
	.size	PQ_HAL_GetCTIEnable, .-PQ_HAL_GetCTIEnable
	.align	2
	.global	PQ_HAL_GetLTIEnable
	.type	PQ_HAL_GetLTIEnable, %function
PQ_HAL_GetLTIEnable:
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
	mov	r4, r1	@ pu8Enable, pu8Enable
	bl	PQ_HAL_GetVpssReg	@
	cmp	r0, #0	@ pstVpssVirReg
	beq	.L46	@,
	ldrb	r1, [r0, #387]	@ zero_extendqisi2	@ tmp142,
	mov	r0, #0	@ D.35424,
	ubfx	r3, r1, #7, #1	@ tmp143, tmp142,,
	strb	r3, [r4, #0]	@ tmp143,* pu8Enable
.L44:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L46:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L47	@,
	mov	r3, #109	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35424,
	b	.L44	@
.L48:
	.align	2
.L47:
	.word	.LANCHOR0+132
	.fnend
	.size	PQ_HAL_GetLTIEnable, .-PQ_HAL_GetLTIEnable
	.align	2
	.global	PQ_HAL_SetSharpRegist
	.type	PQ_HAL_SetSharpRegist, %function
PQ_HAL_SetSharpRegist:
	.fnstart
.LFB1392:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r1	@ pstSharpPara, pstSharpPara
	bl	PQ_HAL_GetVpssReg	@
	cmp	r0, #0	@ pstVpssVirReg
	beq	.L53	@,
	ldr	r9, [r4, #36]	@ <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef4, <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef4
	movw	r7, #386	@ tmp146,
	mov	lr, #392	@ tmp164,
	ldrh	r5, [r0, r7]	@,
	ldrh	r6, [r0, lr]	@,
	movw	ip, #394	@ tmp170,
	strb	r9, [r0, #384]	@ <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef4, <variable>.VPSS_VHD_LTI_CTRL.bits.lhpass_coef4
	movw	r1, #406	@ tmp186,
	ldr	sl, [r4, #16]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lmixing_ratio, <variable>.stSharpHdData.stPqSharpLuma.u32Lmixing_ratio
	mov	r2, #412	@ tmp202,
	movw	r3, #414	@ tmp208,
	mov	r9, #0	@ D.35348,
	strb	sl, [r0, #385]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lmixing_ratio, <variable>.VPSS_VHD_LTI_CTRL.bits.lmixing_ratio
	ldr	sl, [r4, #12]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lgain_ratio, <variable>.stSharpHdData.stPqSharpLuma.u32Lgain_ratio
	bfi	r5, sl, #0, #12	@ tmp147, <variable>.stSharpHdData.stPqSharpLuma.u32Lgain_ratio,,
	strh	r5, [r0, r7]	@ movhi	@ tmp147,
	ldr	r8, [r4, #4]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lti_demo_en, <variable>.stSharpHdData.stPqSharpLuma.u32Lti_demo_en
	ldrb	r5, [r0, #387]	@ zero_extendqisi2	@,
	bfi	r5, r8, #6, #1	@ tmp150, <variable>.stSharpHdData.stPqSharpLuma.u32Lti_demo_en,,
	strb	r5, [r0, #387]	@ tmp150,
	ldr	r8, [r4, #0]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lti_en, <variable>.stSharpHdData.stPqSharpLuma.u32Lti_en
	uxtb	r7, r5	@ tmp153, tmp150
	bfi	r7, r8, #7, #1	@ tmp153, <variable>.stSharpHdData.stPqSharpLuma.u32Lti_en,,
	strb	r7, [r0, #387]	@ tmp153,
	ldr	r5, [r4, #20]	@ <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef0, <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef0
	strb	r5, [r0, #388]	@ <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef0, <variable>.VPSS_VHD_LHPASS_COEF.bits.lhpass_coef0
	ldr	r7, [r4, #24]	@ <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef1, <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef1
	strb	r7, [r0, #389]	@ <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef1, <variable>.VPSS_VHD_LHPASS_COEF.bits.lhpass_coef1
	ldr	r5, [r4, #28]	@ <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef2, <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef2
	strb	r5, [r0, #390]	@ <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef2, <variable>.VPSS_VHD_LHPASS_COEF.bits.lhpass_coef2
	ldr	r7, [r4, #32]	@ <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef3, <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef3
	strb	r7, [r0, #391]	@ <variable>.stSharpHdData.stPqSharpLuma.s32Lhpass_coef3, <variable>.VPSS_VHD_LHPASS_COEF.bits.lhpass_coef3
	ldr	r7, [r4, #48]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lover_swing, <variable>.stSharpHdData.stPqSharpLuma.u32Lover_swing
	bfi	r6, r7, #0, #10	@ tmp165, <variable>.stSharpHdData.stPqSharpLuma.u32Lover_swing,,
	strh	r6, [r0, lr]	@ movhi	@ tmp165,
	ldr	r5, [r4, #44]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lunder_swing, <variable>.stSharpHdData.stPqSharpLuma.u32Lunder_swing
	ldr	lr, [r0, #392]	@ tmp168,
	bfi	lr, r5, #10, #10	@ tmp168, <variable>.stSharpHdData.stPqSharpLuma.u32Lunder_swing,,
	str	lr, [r0, #392]	@ tmp168,
	ldr	r6, [r4, #40]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lcoring_thd, <variable>.stSharpHdData.stPqSharpLuma.u32Lcoring_thd
	mov	lr, #396	@ tmp173,
	ldrh	r5, [r0, ip]	@,
	bfi	r5, r6, #4, #12	@ tmp171, <variable>.stSharpHdData.stPqSharpLuma.u32Lcoring_thd,,
	strh	r5, [r0, ip]	@ movhi	@ tmp171,
	ldrh	r6, [r4, #52]	@, <variable>.stSharpHdData.stPqSharpLuma.u32Lhfreq_thd0
	movw	ip, #398	@ tmp175,
	strh	r6, [r0, lr]	@ movhi	@, <variable>.VPSS_VHD_LHFREQ_THD.bits.lhfreq_thd0
	ldrh	r5, [r4, #56]	@, <variable>.stSharpHdData.stPqSharpLuma.u32Lhfreq_thd1
	strh	r5, [r0, ip]	@ movhi	@, <variable>.VPSS_VHD_LHFREQ_THD.bits.lhfreq_thd1
	ldr	lr, [r4, #60]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lgain_coef0, <variable>.stSharpHdData.stPqSharpLuma.u32Lgain_coef0
	strb	lr, [r0, #400]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lgain_coef0, <variable>.VPSS_VHD_LGAIN_COEF.bits.lgain_coef0
	ldr	r6, [r4, #64]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lgain_coef1, <variable>.stSharpHdData.stPqSharpLuma.u32Lgain_coef1
	ldrh	ip, [r0, r1]	@,
	ldrh	lr, [r0, r2]	@,
	strb	r6, [r0, #401]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lgain_coef1, <variable>.VPSS_VHD_LGAIN_COEF.bits.lgain_coef1
	ldr	r5, [r4, #68]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lgain_coef2, <variable>.stSharpHdData.stPqSharpLuma.u32Lgain_coef2
	strb	r5, [r0, #402]	@ <variable>.stSharpHdData.stPqSharpLuma.u32Lgain_coef2, <variable>.VPSS_VHD_LGAIN_COEF.bits.lgain_coef2
	ldr	r6, [r4, #84]	@ <variable>.stSharpHdData.stPqSharpChroma.u32Cmixing_ratio, <variable>.stSharpHdData.stPqSharpChroma.u32Cmixing_ratio
	strb	r6, [r0, #405]	@ <variable>.stSharpHdData.stPqSharpChroma.u32Cmixing_ratio, <variable>.VPSS_VHD_CTI_CTRL.bits.cmixing_ratio
	ldr	r6, [r4, #80]	@ <variable>.stSharpHdData.stPqSharpChroma.u32Cgain_ratio, <variable>.stSharpHdData.stPqSharpChroma.u32Cgain_ratio
	bfi	ip, r6, #0, #12	@ tmp187, <variable>.stSharpHdData.stPqSharpChroma.u32Cgain_ratio,,
	strh	ip, [r0, r1]	@ movhi	@ tmp187,
	ldr	r5, [r4, #76]	@ <variable>.stSharpHdData.stPqSharpChroma.u32Cti_demo_en, <variable>.stSharpHdData.stPqSharpChroma.u32Cti_demo_en
	ldrb	ip, [r0, #407]	@ zero_extendqisi2	@,
	bfi	ip, r5, #6, #1	@ tmp190, <variable>.stSharpHdData.stPqSharpChroma.u32Cti_demo_en,,
	strb	ip, [r0, #407]	@ tmp190,
	ldr	r5, [r4, #72]	@ <variable>.stSharpHdData.stPqSharpChroma.u32Cti_en, <variable>.stSharpHdData.stPqSharpChroma.u32Cti_en
	uxtb	r1, ip	@ tmp193, tmp190
	bfi	r1, r5, #7, #1	@ tmp193, <variable>.stSharpHdData.stPqSharpChroma.u32Cti_en,,
	strb	r1, [r0, #407]	@ tmp193,
	ldr	ip, [r4, #88]	@ <variable>.stSharpHdData.stPqSharpChroma.s32Chpass_coef0, <variable>.stSharpHdData.stPqSharpChroma.s32Chpass_coef0
	strb	ip, [r0, #408]	@ <variable>.stSharpHdData.stPqSharpChroma.s32Chpass_coef0, <variable>.VPSS_VHD_CHPASS_COEF.bits.chpass_coef0
	ldr	r1, [r4, #92]	@ <variable>.stSharpHdData.stPqSharpChroma.s32Chpass_coef1, <variable>.stSharpHdData.stPqSharpChroma.s32Chpass_coef1
	strb	r1, [r0, #409]	@ <variable>.stSharpHdData.stPqSharpChroma.s32Chpass_coef1, <variable>.VPSS_VHD_CHPASS_COEF.bits.chpass_coef1
	ldr	ip, [r4, #96]	@ <variable>.stSharpHdData.stPqSharpChroma.s32Chpass_coef2, <variable>.stSharpHdData.stPqSharpChroma.s32Chpass_coef2
	strb	ip, [r0, #410]	@ <variable>.stSharpHdData.stPqSharpChroma.s32Chpass_coef2, <variable>.VPSS_VHD_CHPASS_COEF.bits.chpass_coef2
	ldr	r1, [r4, #108]	@ <variable>.stSharpHdData.stPqSharpChroma.u32Cover_swing, <variable>.stSharpHdData.stPqSharpChroma.u32Cover_swing
	bfi	lr, r1, #0, #10	@ tmp203, <variable>.stSharpHdData.stPqSharpChroma.u32Cover_swing,,
	strh	lr, [r0, r2]	@ movhi	@ tmp203,
	ldr	ip, [r4, #104]	@ <variable>.stSharpHdData.stPqSharpChroma.u32Cunder_swing, <variable>.stSharpHdData.stPqSharpChroma.u32Cunder_swing
	ldr	lr, [r0, #412]	@ tmp206,
	bfi	lr, ip, #10, #10	@ tmp206, <variable>.stSharpHdData.stPqSharpChroma.u32Cunder_swing,,
	str	lr, [r0, #412]	@ tmp206,
	ldr	r1, [r4, #100]	@ <variable>.stSharpHdData.stPqSharpChroma.u32Ccoring_thd, <variable>.stSharpHdData.stPqSharpChroma.u32Ccoring_thd
	ldrh	r2, [r0, r3]	@,
	bfi	r2, r1, #4, #12	@ tmp209, <variable>.stSharpHdData.stPqSharpChroma.u32Ccoring_thd,,
	strh	r2, [r0, r3]	@ movhi	@ tmp209,
.L51:
	mov	r0, r9	@, D.35348
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L53:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L54	@,
	mov	r3, #42	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	mvn	r9, #0	@ D.35348,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	b	.L51	@
.L55:
	.align	2
.L54:
	.word	.LANCHOR0+152
	.fnend
	.size	PQ_HAL_SetSharpRegist, .-PQ_HAL_SetSharpRegist
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.35503, %object
	.size	__func__.35503, 21
__func__.35503:
	.ascii	"PQ_HAL_EnableLTIDemo\000"
	.space	3
	.type	__func__.35491, %object
	.size	__func__.35491, 21
__func__.35491:
	.ascii	"PQ_HAL_EnableCTIDemo\000"
	.space	3
	.type	__func__.35468, %object
	.size	__func__.35468, 22
__func__.35468:
	.ascii	"PQ_HAL_SetSharpStrReg\000"
	.space	2
	.type	__func__.35455, %object
	.size	__func__.35455, 17
__func__.35455:
	.ascii	"PQ_HAL_EnableCTI\000"
	.space	3
	.type	__func__.35444, %object
	.size	__func__.35444, 17
__func__.35444:
	.ascii	"PQ_HAL_EnableLTI\000"
	.space	3
	.type	__func__.35432, %object
	.size	__func__.35432, 20
__func__.35432:
	.ascii	"PQ_HAL_GetCTIEnable\000"
	.type	__func__.35420, %object
	.size	__func__.35420, 20
__func__.35420:
	.ascii	"PQ_HAL_GetLTIEnable\000"
	.type	__func__.35344, %object
	.size	__func__.35344, 22
__func__.35344:
	.ascii	"PQ_HAL_SetSharpRegist\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"pointer is NULL!\012\000"
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
