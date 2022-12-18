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
	.file	"pq_hal_dbdr.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_hal_dbdr)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/hal/hi3798mv100/.pq_hal_dbdr.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_dbdr.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_dbdr.o -O2 -Wall -Wundef
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
	.global	PQ_HAL_EnableDB
	.type	PQ_HAL_EnableDB, %function
PQ_HAL_EnableDB:
	.fnstart
.LFB656:
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
	.size	PQ_HAL_EnableDB, .-PQ_HAL_EnableDB
	.align	2
	.global	PQ_HAL_EnableDRDemo
	.type	PQ_HAL_EnableDRDemo, %function
PQ_HAL_EnableDRDemo:
	.fnstart
.LFB658:
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
	mov	r4, r1	@ bDRDemoOnOff, bDRDemoOnOff
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	beq	.L8	@,
	ldrb	r2, [r3, #447]	@ zero_extendqisi2	@,
	mov	r0, #0	@ D.23273,
	bfi	r2, r4, #0, #1	@ tmp140, bDRDemoOnOff,,
	strb	r2, [r3, #447]	@ tmp140,
.L5:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L8:
	mov	r0, #1	@,
	mov	r1, #41	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	mov	r3, #143	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	movw	ip, #:lower16:.LC0	@ tmp139,
	movt	ip, #:upper16:.LC0	@ tmp139,
	str	ip, [sp, #0]	@ tmp139,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.23273,
	b	.L5	@
	.fnend
	.size	PQ_HAL_EnableDRDemo, .-PQ_HAL_EnableDRDemo
	.align	2
	.global	PQ_HAL_EnableDR
	.type	PQ_HAL_EnableDR, %function
PQ_HAL_EnableDR:
	.fnstart
.LFB657:
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
	mov	r4, r1	@ bDROnOff, bDROnOff
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	beq	.L13	@,
	ldrb	r2, [r3, #1]	@ zero_extendqisi2	@,
	mov	r0, #0	@ D.23261,
	bfi	r2, r4, #3, #1	@ tmp141, bDROnOff,,
	strb	r2, [r3, #1]	@ tmp141,
.L11:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L13:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L14	@,
	mov	r3, #119	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.23261,
	b	.L11	@
.L15:
	.align	2
.L14:
	.word	.LANCHOR0+20
	.fnend
	.size	PQ_HAL_EnableDR, .-PQ_HAL_EnableDR
	.align	2
	.global	PQ_HAL_SetDnrParamRegister
	.type	PQ_HAL_SetDnrParamRegister, %function
PQ_HAL_SetDnrParamRegister:
	.fnstart
.LFB655:
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
	subs	r4, r1, #0	@ pstDnrPara, pstDnrPara
	beq	.L22	@,
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	beq	.L23	@,
	ldr	r1, [r4, #0]	@ <variable>.stPqDnrCtrl.u32Dr_en, <variable>.stPqDnrCtrl.u32Dr_en
	mov	r0, #0	@ D.23238,
	ldrb	r2, [r3, #1]	@ zero_extendqisi2	@,
	ldrb	lr, [r3, #447]	@ zero_extendqisi2	@,
	bfi	r2, r1, #3, #1	@ tmp145, <variable>.stPqDnrCtrl.u32Dr_en,,
	strb	r2, [r3, #1]	@ tmp145,
	ldr	ip, [r4, #4]	@ <variable>.stPqDnrCtrl.u32Dr_Demo_en, <variable>.stPqDnrCtrl.u32Dr_Demo_en
	ldrb	r2, [r3, #442]	@ zero_extendqisi2	@,
	bfi	lr, ip, #0, #1	@ tmp148, <variable>.stPqDnrCtrl.u32Dr_Demo_en,,
	strb	lr, [r3, #447]	@ tmp148,
	ldr	r1, [r4, #76]	@ <variable>.stPqDnrDrFilter.u32Dr_thr_maxsimilarpixdiff, <variable>.stPqDnrDrFilter.u32Dr_thr_maxsimilarpixdiff
	ldrb	lr, [r3, #443]	@ zero_extendqisi2	@,
	bfi	r2, r1, #0, #5	@ tmp151, <variable>.stPqDnrDrFilter.u32Dr_thr_maxsimilarpixdiff,,
	strb	r2, [r3, #442]	@ tmp151,
	ldr	ip, [r4, #72]	@ <variable>.stPqDnrDrFilter.u32Dr_thr_flat3x3zone, <variable>.stPqDnrDrFilter.u32Dr_thr_flat3x3zone
	ldrb	r2, [r3, #444]	@ zero_extendqisi2	@,
	bfi	lr, ip, #0, #5	@ tmp154, <variable>.stPqDnrDrFilter.u32Dr_thr_flat3x3zone,,
	strb	lr, [r3, #443]	@ tmp154,
	ldr	r1, [r4, #84]	@ <variable>.stPqDnrDrFilter.u32Dr_alphascale, <variable>.stPqDnrDrFilter.u32Dr_alphascale
	ldrb	lr, [r3, #446]	@ zero_extendqisi2	@,
	bfi	r2, r1, #0, #5	@ tmp157, <variable>.stPqDnrDrFilter.u32Dr_alphascale,,
	strb	r2, [r3, #444]	@ tmp157,
	ldr	ip, [r4, #80]	@ <variable>.stPqDnrDrFilter.u32Dr_betascale, <variable>.stPqDnrDrFilter.u32Dr_betascale
	ldrb	r2, [r3, #460]	@ zero_extendqisi2	@,
	bfi	lr, ip, #0, #5	@ tmp160, <variable>.stPqDnrDrFilter.u32Dr_betascale,,
	strb	lr, [r3, #446]	@ tmp160,
	ldr	r1, [r4, #100]	@ <variable>.stPqDnrInfo.u32thr_intl_colcnt, <variable>.stPqDnrInfo.u32thr_intl_colcnt
	bfi	r2, r1, #0, #4	@ tmp163, <variable>.stPqDnrInfo.u32thr_intl_colcnt,,
	strb	r2, [r3, #460]	@ tmp163,
	ldr	ip, [r4, #96]	@ <variable>.stPqDnrInfo.u32thr_intl_cnt, <variable>.stPqDnrInfo.u32thr_intl_cnt
	uxtb	lr, r2	@ tmp166, tmp163
	bfi	lr, ip, #4, #4	@ tmp166, <variable>.stPqDnrInfo.u32thr_intl_cnt,,
	strb	lr, [r3, #460]	@ tmp166,
	ldr	r1, [r4, #92]	@ <variable>.stPqDnrInfo.u32thd_maxgrad, <variable>.stPqDnrInfo.u32thd_maxgrad
	strb	r1, [r3, #461]	@ <variable>.stPqDnrInfo.u32thd_maxgrad, <variable>.VPSS_DNR_INFO.bits.thdmaxgrad
	ldr	r2, [r4, #88]	@ <variable>.stPqDnrInfo.u32thd_cntrst8, <variable>.stPqDnrInfo.u32thd_cntrst8
	strb	r2, [r3, #462]	@ <variable>.stPqDnrInfo.u32thd_cntrst8, <variable>.VPSS_DNR_INFO.bits.thdcntrst8
.L18:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L22:
	ldr	r2, .L24	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	mov	r3, #72	@,
.L21:
	movw	ip, #:lower16:.LC0	@ tmp143,
	movt	ip, #:upper16:.LC0	@ tmp143,
	str	ip, [sp, #0]	@ tmp143,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.23238,
	b	.L18	@
.L23:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L24	@,
	mov	r3, #74	@,
	b	.L21	@
.L25:
	.align	2
.L24:
	.word	.LANCHOR0+36
	.fnend
	.size	PQ_HAL_SetDnrParamRegister, .-PQ_HAL_SetDnrParamRegister
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.23269, %object
	.size	__func__.23269, 20
__func__.23269:
	.ascii	"PQ_HAL_EnableDRDemo\000"
	.type	__func__.23257, %object
	.size	__func__.23257, 16
__func__.23257:
	.ascii	"PQ_HAL_EnableDR\000"
	.type	__func__.23235, %object
	.size	__func__.23235, 27
__func__.23235:
	.ascii	"PQ_HAL_SetDnrParamRegister\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"pointer is NULL!\012\000"
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
