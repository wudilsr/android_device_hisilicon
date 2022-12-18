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
	.file	"syntax.c"
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
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0
@ -Idrivers/msp/vfmw/vfmw_v4.0
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/mach-hi3798mx/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/drv/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/scene/stb
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/common
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/osal/linux_kernel
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/common/softlib
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/common/syntax
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/driver/HiSCDV200
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/product/Hi3798MV100
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/common_test/vdecko
@ -imultilib armv7a_soft -iprefix
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/
@ -isysroot /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../target
@ -D__KERNEL__ -D__LINUX_ARM_ARCH__=7 -Uarm -DCHIP_TYPE_hi3796mv100
@ -DSDK_VERSION=HiSTBAndroidV600R001C00SPC060_v2015040918 -DHI_MCE_SUPPORT
@ -DHI_GPIOI2C_SUPPORT -DHI_LOG_SUPPORT=1 -DHI_LOG_LEVEL=4
@ -DHI_PROC_SUPPORT=1 -DHI_HDMI_SUPPORT_1_4 -DHI_KEYLED_SUPPORT
@ -DHI_HDCP_SUPPORT -DHI_SCI_SUPPORT -DHI_PVR_SUPPORT -DHI_VI_SUPPORT
@ -DHI_VENC_SUPPORT -DHI_AENC_SUPPORT -DHI_PQ_V3_0 -DENV_ARMLINUX_KERNEL
@ -DDNR_DISABLE -DSCD_MP4_SLICE_ENABLE -DSUPPORT_JPEG_444
@ -DVFMW_EXTRA_TYPE_DEFINE -DPRODUCT_STB -D__VFMW_REGISTER_ISR__
@ -DQ_MATRIX_FIXED -DVFMW_VDH_V300R001_SUPPORT -DCFG_SCD_TIME_OUT=2000
@ -DCFG_VDH_TIME_OUT=500 -DVFMW_H264_SUPPORT -DVFMW_HEVC_SUPPORT
@ -DVFMW_MVC_SUPPORT -DVFMW_MPEG2_SUPPORT -DVFMW_MPEG4_SUPPORT
@ -DVFMW_AVS_SUPPORT -DVFMW_VC1_SUPPORT -DVFMW_BPD_H_SUPPORT
@ -DVFMW_REAL8_SUPPORT -DVFMW_REAL9_SUPPORT -DVFMW_VP6_SUPPORT
@ -DVFMW_VP8_SUPPORT -DVFMW_DIVX3_SUPPORT -DVFMW_H263_SUPPORT
@ -DVFMW_JPEG_SUPPORT -DVFMW_RAW_SUPPORT -DVFMW_USER_SUPPORT
@ -DCFG_MAX_CHAN_NUM=16 -DVFMW_DPRINT_SUPPORT -DVFMW_SCD_LOWDLY_SUPPORT
@ -DVFMW_AVSPLUS_SUPPORT -DVFMW_MODULE_LOWDLY_SUPPORT
@ -DVFMW_SYSTEM_REG_DISABLE -DHI_VDEC_SVDEC_BUILTIN -DKBUILD_STR(s)=#s
@ -DKBUILD_BASENAME=KBUILD_STR(syntax) -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw)
@ -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/vfmw/vfmw_v4.0/firmware/common/syntax/.syntax.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/common/syntax/syntax.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/vfmw/vfmw_v4.0/firmware/common/syntax/syntax.o -O2 -Wall
@ -Wundef -Wstrict-prototypes -Wno-trigraphs
@ -Werror-implicit-function-declaration -Wno-format-security
@ -Wframe-larger-than=1024 -Wdeclaration-after-statement -Wno-pointer-sign
@ -p -fno-strict-aliasing -fno-common -fno-delete-null-pointer-checks
@ -fno-dwarf2-cfi-asm -funwind-tables -fno-stack-protector
@ -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-strict-overflow
@ -fconserve-stack -fno-pic -fverbose-asm
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
	.global	ProduceTimeStamp
	.type	ProduceTimeStamp, %function
ProduceTimeStamp:
	.fnstart
.LFB1532:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r2, #18	@ eVidStd,
	ldrd	r4, [r1, #8]	@ ThisFramePts, p_image,
	beq	.L2	@,
	mov	r3, #328	@ tmp140,
	mov	r8, r4	@ tmp141, ThisFramePts
	ldrd	r6, [r0, r3]	@ D.38630, pstVoQue, tmp140
	mov	r9, r5	@, ThisFramePts
	subs	r8, r8, r6	@ tmp141, tmp141, D.38630
	sbc	r9, r9, r7	@ tmp141, tmp141, D.38630
	cmp	r9, #0	@ tmp141,
	cmpeq	r8, #5	@ tmp141,
	bhi	.L3	@,
	mvn	r8, #0	@ tmp142,
	mvn	r9, #0	@,
	cmp	r7, r9	@ D.38630, tmp142
	cmpeq	r6, r8	@ D.38630, tmp142
	beq	.L3	@,
	sub	r3, r2, #8	@ tmp146, eVidStd,
	cmp	r3, #1	@ tmp146,
	movhi	r1, r9	@ InferedPTS,
	movhi	r0, r8	@ InferedPTS, tmp154
	ldmhifd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L5:
	mvn	r4, #0	@ tmp147,
	mvn	r5, #0	@,
	mov	r0, r4	@ InferedPTS, tmp155
	strd	r4, [r1]	@ tmp147, <variable>.SrcPts
	mov	r1, r5	@ InferedPTS,
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L3:
	sub	r2, r2, #8	@ tmp143, eVidStd,
	cmp	r2, #1	@ tmp143,
	bls	.L9	@,
.L2:
	mov	r1, r5	@ InferedPTS,
	mov	r0, r4	@ InferedPTS, tmp156
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L9:
	ldr	ip, [r1, #160]	@ <variable>.format, <variable>.format
	and	r0, ip, #3	@ tmp144, <variable>.format,
	cmp	r0, #2	@ tmp144,
	bne	.L2	@,
	b	.L5	@
	.fnend
	.size	ProduceTimeStamp, .-ProduceTimeStamp
	.align	2
	.global	GetQueueImgNum
	.type	GetQueueImgNum, %function
GetQueueImgNum:
	.fnstart
.LFB1534:
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
	ldrh	r3, [r0, #6]	@ D.38808, <variable>.head
	ldrh	ip, [r0, #4]	@ D.38809, <variable>.history
	ldrh	r0, [r0, #8]	@ D.38817, <variable>.tail
	cmp	r3, ip	@ D.38808, D.38809
	addcc	r4, r3, #64	@ tmp142, D.38808,
	rsbcs	ip, ip, r3	@ ReadNum, D.38809, D.38808
	rsbcc	ip, ip, r4	@ ReadNum, D.38809, tmp142
	cmp	r3, r0	@ D.38808, D.38817
	addhi	r0, r0, #64	@ tmp143, D.38817,
	str	ip, [r1, #0]	@ ReadNum,* pReadImgNum
	rsb	r3, r3, r0	@ NewNum, D.38808, tmp143
	str	r3, [r2, #0]	@ NewNum,* pNewImgNum
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	GetQueueImgNum, .-GetQueueImgNum
	.align	2
	.global	OpenUsdPool_WithMem
	.type	OpenUsdPool_WithMem, %function
OpenUsdPool_WithMem:
	.fnstart
.LFB1545:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp172,
	movt	r3, #:upper16:.LANCHOR0	@ tmp172,
	ldr	ip, [r3, r0, asl #2]	@ D.40095, pstVdecUsdPool
	cmp	ip, #0	@ D.40095,
	beq	.L24	@,
.L18:
	mov	r1, #0	@ tmp174,
	mov	r3, ip	@ ivtmp.648, D.40095
	mov	r2, r1	@ i, tmp174
	mov	r0, r1	@ tmp178, i
	str	r1, [ip, #0]	@ tmp174, <variable>.s32AccessIdx
.L20:
	add	r2, r2, #2	@ i, i,
	add	ip, r3, #1072	@ tmp180, ivtmp.648,
	cmp	r2, #192	@ i,
	str	r0, [r3, #1044]	@ tmp178, <variable>.from
	str	r0, [r3, #1040]	@ tmp178, <variable>.dnr_used_flag
	add	r3, r3, #2144	@ ivtmp.648, ivtmp.648,
	str	r0, [ip, #1040]	@ tmp178, <variable>.dnr_used_flag
	str	r0, [ip, #1044]	@ tmp178, <variable>.from
	bne	.L20	@,
	ldmfd	sp, {fp, sp, pc}	@
.L24:
	cmp	r1, #0	@ D.40095,
	str	r1, [r3, r0, asl #2]	@ D.40095, pstVdecUsdPool
	mov	ip, r1	@ D.40095, Viraddr
	mvneq	r0, #0	@ ret,
	ldmeqfd	sp, {fp, sp, pc}	@
	b	.L18	@
	.fnend
	.size	OpenUsdPool_WithMem, .-OpenUsdPool_WithMem
	.align	2
	.global	CloseUsdPool_WithMem
	.type	CloseUsdPool_WithMem, %function
CloseUsdPool_WithMem:
	.fnstart
.LFB1546:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp134,
	movt	r3, #:upper16:.LANCHOR0	@ tmp134,
	ldr	r2, [r3, r0, asl #2]	@ tmp135, pstVdecUsdPool
	cmp	r2, #0	@ tmp135,
	movne	r2, #0	@ tmp137,
	strne	r2, [r3, r0, asl #2]	@ tmp137, pstVdecUsdPool
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	CloseUsdPool_WithMem, .-CloseUsdPool_WithMem
	.align	2
	.global	InitUsdPool
	.type	InitUsdPool, %function
InitUsdPool:
	.fnstart
.LFB1547:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp139,
	movt	r3, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r1, [r3, r0, asl #2]	@ D.39923, pstVdecUsdPool
	cmp	r1, #0	@ D.39923,
	mvneq	r0, #0	@ D.39927,
	ldmeqfd	sp, {fp, sp, pc}	@
	mov	r0, #0	@ tmp140,
	mov	r3, r1	@ ivtmp.705, D.39923
	mov	r2, r0	@ i, tmp140
	str	r0, [r1, #0]	@ tmp140, <variable>.s32AccessIdx
.L31:
	add	r2, r2, #2	@ i, i,
	add	r1, r3, #1072	@ tmp145, ivtmp.705,
	cmp	r2, #192	@ i,
	str	r0, [r3, #1044]	@ tmp144, <variable>.from
	str	r0, [r3, #1040]	@ tmp144, <variable>.dnr_used_flag
	add	r3, r3, #2144	@ ivtmp.705, ivtmp.705,
	str	r0, [r1, #1040]	@ tmp144, <variable>.dnr_used_flag
	str	r0, [r1, #1044]	@ tmp144, <variable>.from
	bne	.L31	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	InitUsdPool, .-InitUsdPool
	.align	2
	.global	GetUsd
	.type	GetUsd, %function
GetUsd:
	.fnstart
.LFB1548:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp141,
	movt	r3, #:upper16:.LANCHOR0	@ tmp141,
	ldr	r0, [r3, r0, asl #2]	@ D.39938, pstVdecUsdPool
	cmp	r0, #0	@ D.39938,
	bne	.L46	@,
.L36:
	mov	r0, #0	@ pstUsrDat,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L46:
	mov	r2, r0	@ ivtmp.738, D.39938
	mov	r3, #0	@ i,
	b	.L39	@
.L37:
	ldr	r2, [r1, #1044]	@ <variable>.from, <variable>.from
	add	r3, r3, #1	@ i, i,
	cmp	r2, #0	@ <variable>.from,
	mov	ip, r3	@ tmp203, i
	bne	.L42	@,
	ldr	r2, [r1, #1040]	@ <variable>.dnr_used_flag, <variable>.dnr_used_flag
	cmp	r2, #0	@ <variable>.dnr_used_flag,
	beq	.L45	@,
.L42:
	add	r3, ip, #1	@ i, tmp203,
	add	r2, r1, #1072	@ ivtmp.738, tmp204,
	cmp	r3, #192	@ i,
	beq	.L36	@,
.L39:
	ldr	ip, [r2, #1044]	@ <variable>.from, <variable>.from
	add	r1, r2, #1072	@ tmp204, ivtmp.738,
	cmp	ip, #0	@ <variable>.from,
	bne	.L37	@,
	ldr	r2, [r2, #1040]	@ <variable>.dnr_used_flag, <variable>.dnr_used_flag
	cmp	r2, #0	@ <variable>.dnr_used_flag,
	bne	.L37	@,
.L45:
	mov	r1, #1072	@ tmp150,
	mov	r5, #134	@ tmp145,
	mla	ip, r3, r1, r1	@ tmp179, i, tmp150, tmp150
	mul	r4, r5, r3	@ tmp144, tmp145, i
	mla	r3, r1, r3, r0	@ tmp151, tmp150, i, D.39938
	add	r5, ip, r0	@ tmp181, tmp179, D.39938
	add	r4, r4, #1	@ tmp146, tmp144,
	movw	r1, #1064	@ tmp154,
	strb	r2, [ip, r0]	@ <variable>.dnr_used_flag, <variable>.IsRegistered
	strh	r2, [r5, #4]	@ movhi	@ <variable>.dnr_used_flag, <variable>.itu_t_t35_provider_code
	add	r0, r0, r4, asl #3	@, pstUsrDat, D.39938, tmp146,
	strb	r2, [r5, #1]	@ <variable>.dnr_used_flag, <variable>.itu_t_t35_country_code
	mov	r4, #0	@ tmp159,
	strb	r2, [r5, #2]	@ <variable>.dnr_used_flag, <variable>.itu_t_t35_country_code_extension_byte
	mov	r5, #0	@,
	str	r2, [r3, #1048]	@ <variable>.dnr_used_flag, <variable>.seq_cnt
	strd	r4, [r3, r1]	@ tmp159, tmp151, tmp154
	str	r2, [r3, #1040]	@ <variable>.dnr_used_flag, <variable>.dnr_used_flag
	str	r2, [r3, #1056]	@ <variable>.dnr_used_flag, <variable>.data_size
	str	r2, [r3, #1052]	@ <variable>.dnr_used_flag, <variable>.seq_img_cnt
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	GetUsd, .-GetUsd
	.align	2
	.global	FreeUsdByDec
	.type	FreeUsdByDec, %function
FreeUsdByDec:
	.fnstart
.LFB1549:
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
	cmp	r1, #0	@ pUsrdat
	movne	r3, #0	@ tmp135,
	strne	r3, [r1, #1036]	@ tmp135, <variable>.from
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FreeUsdByDec, .-FreeUsdByDec
	.align	2
	.global	MarkUsdByDnr
	.type	MarkUsdByDnr, %function
MarkUsdByDnr:
	.fnstart
.LFB1550:
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
	cmp	r1, #0	@ pUsrdat
	movne	r3, #1	@ tmp135,
	strne	r3, [r1, #1032]	@ tmp135, <variable>.dnr_used_flag
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	MarkUsdByDnr, .-MarkUsdByDnr
	.align	2
	.global	UnMarkUsdByDnr
	.type	UnMarkUsdByDnr, %function
UnMarkUsdByDnr:
	.fnstart
.LFB1551:
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
	cmp	r1, #0	@ pUsrdat
	movne	r3, #0	@ tmp135,
	strne	r3, [r1, #1032]	@ tmp135, <variable>.dnr_used_flag
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	UnMarkUsdByDnr, .-UnMarkUsdByDnr
	.align	2
	.global	GetVoLastImageID
	.type	GetVoLastImageID, %function
GetVoLastImageID:
	.fnstart
.LFB1555:
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
	ldr	r0, [r0, #296]	@ D.40029, <variable>.SideInfo.LastImageIdPlus2
	cmp	r0, #1	@ D.40029,
	mvnls	r0, #0	@,,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	GetVoLastImageID, .-GetVoLastImageID
	.align	2
	.global	IsMain10Profile
	.type	IsMain10Profile, %function
IsMain10Profile:
	.fnstart
.LFB1556:
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
	movw	r3, #:lower16:4321048	@ tmp140,
	movt	r3, #:upper16:4321048	@ tmp140,
	ldr	r2, [r0, r3]	@ D.40039, <variable>.general_profile_idc
	cmp	r2, #1	@ D.40039,
	beq	.L60	@,
	movw	ip, #:lower16:4321052	@ tmp141,
	movt	ip, #:upper16:4321052	@ tmp141,
	ldr	r1, [r0, ip]	@ <variable>.general_profile_compatibility_flag_1, <variable>.general_profile_compatibility_flag_1
	cmp	r1, #1	@ <variable>.general_profile_compatibility_flag_1,
	beq	.L60	@,
	cmp	r2, #2	@ D.40039,
	beq	.L67	@,
	movw	r3, #:lower16:4321056	@ tmp143,
	movt	r3, #:upper16:4321056	@ tmp143,
	ldr	r2, [r0, r3]	@ <variable>.general_profile_compatibility_flag_2, <variable>.general_profile_compatibility_flag_2
	cmp	r2, #1	@ <variable>.general_profile_compatibility_flag_2,
	movne	r3, #0	@, flag.859
	moveq	r3, #1	@, flag.859
	mov	r0, r3	@ flag.860, flag.859
	orr	r0, r0, r3	@ flag, flag.860, flag.859
	ldmfd	sp, {fp, sp, pc}	@
.L60:
	mov	r0, #0	@ flag,
	ldmfd	sp, {fp, sp, pc}	@
.L67:
	movw	r1, #:lower16:4321056	@ tmp147,
	movt	r1, #:upper16:4321056	@ tmp147,
	mov	r3, #1	@ flag.859,
	ldr	r0, [r0, r1]	@ <variable>.general_profile_compatibility_flag_2, <variable>.general_profile_compatibility_flag_2
	cmp	r0, r3	@ <variable>.general_profile_compatibility_flag_2,
	movne	r0, #0	@, flag.860
	moveq	r0, #1	@, flag.860
	orr	r0, r0, r3	@ flag, flag.860, flag.859
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	IsMain10Profile, .-IsMain10Profile
	.align	2
	.global	SetAspectRatio
	.type	SetAspectRatio, %function
SetAspectRatio:
	.fnstart
.LFB1554:
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
	mov	r3, r0	@ pImg, pImg
	cmp	r1, #5	@ Code,
	ldrls	pc, [pc, r1, asl #2]	@ Code
	b	.L69	@
.L76:
	.word	.L70
	.word	.L71
	.word	.L72
	.word	.L73
	.word	.L74
	.word	.L75
.L75:
	mov	ip, #0	@ tmp145,
	mov	r1, #2	@ tmp146,
	str	ip, [r0, #60]	@ tmp145, <variable>.u32AspectWidth
	str	r1, [r0, #64]	@ tmp146, <variable>.u32AspectHeight
	ldmfd	sp, {fp, sp, pc}	@
.L69:
	mov	r2, r1	@, Code
	mov	lr, #0	@ tmp147,
	mov	r0, #1	@ tmp148,
	str	lr, [r3, #60]	@ tmp147, <variable>.u32AspectWidth
	str	r0, [r3, #64]	@ tmp148, <variable>.u32AspectHeight
	movw	r1, #:lower16:.LC0	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L70:
	mov	r0, #0	@ tmp135,
	mov	r2, #1	@ tmp136,
	str	r0, [r3, #60]	@ tmp135, <variable>.u32AspectWidth
	str	r2, [r3, #64]	@ tmp136, <variable>.u32AspectHeight
	ldmfd	sp, {fp, sp, pc}	@
.L71:
	mov	ip, #4	@ tmp137,
	mov	r1, #3	@ tmp138,
	str	ip, [r0, #60]	@ tmp137, <variable>.u32AspectWidth
	str	r1, [r0, #64]	@ tmp138, <variable>.u32AspectHeight
	ldmfd	sp, {fp, sp, pc}	@
.L72:
	mov	r0, #16	@ tmp139,
	mov	r2, #9	@ tmp140,
	str	r0, [r3, #60]	@ tmp139, <variable>.u32AspectWidth
	str	r2, [r3, #64]	@ tmp140, <variable>.u32AspectHeight
	ldmfd	sp, {fp, sp, pc}	@
.L73:
	mov	ip, #221	@ tmp141,
	mov	r1, #100	@ tmp142,
	str	ip, [r0, #60]	@ tmp141, <variable>.u32AspectWidth
	str	r1, [r0, #64]	@ tmp142, <variable>.u32AspectHeight
	ldmfd	sp, {fp, sp, pc}	@
.L74:
	mov	r0, #235	@ tmp143,
	mov	r2, #100	@ tmp144,
	str	r0, [r3, #60]	@ tmp143, <variable>.u32AspectWidth
	str	r2, [r3, #64]	@ tmp144, <variable>.u32AspectHeight
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SetAspectRatio, .-SetAspectRatio
	.align	2
	.global	IsVoQueueEmpty
	.type	IsVoQueueEmpty, %function
IsVoQueueEmpty:
	.fnstart
.LFB1553:
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
	subs	r4, r0, #0	@ pstVoQue, pstVoQue
	beq	.L84	@,
	ldrh	r2, [r4, #6]	@ D.40002, <variable>.head
	ldrh	r3, [r4, #8]	@ <variable>.tail, <variable>.tail
	cmp	r3, r2	@ <variable>.tail, D.40002
	movne	r0, #0	@ D.40001,
	ldmnefd	sp, {r3, r4, fp, sp, pc}	@
	ldrh	r0, [r4, #4]	@ <variable>.history, <variable>.history
	cmp	r0, r3	@ <variable>.history, <variable>.tail
	movne	r0, #0	@, D.40001
	moveq	r0, #1	@, D.40001
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L84:
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LANCHOR1	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LANCHOR1	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ D.40001, pstVoQue
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	IsVoQueueEmpty, .-IsVoQueueEmpty
	.align	2
	.global	IsImageInVoQueue
	.type	IsImageInVoQueue, %function
IsImageInVoQueue:
	.fnstart
.LFB1552:
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
	cmp	r1, #0	@ p_image
	beq	.L94	@,
	ldrh	r3, [r0, #4]	@ i, <variable>.history
	ldrh	r4, [r0, #8]	@ D.39984, <variable>.tail
	and	r3, r3, #63	@ i.930, i,
	cmp	r4, r3	@ D.39984, i.930
	bne	.L92	@,
	b	.L88	@
.L89:
	cmp	r3, r4	@ i.930, D.39984
	beq	.L88	@,
.L92:
	add	r2, r0, r3, asl #2	@, tmp146, pstVoQue, i.930,
	add	ip, r3, #1	@ i.931, i.930,
	and	r3, ip, #63	@ i.930, i.931,
	ldr	r2, [r2, #12]	@ D.39987, <variable>.image_ptr
	cmp	r2, #0	@ D.39987,
	beq	.L89	@,
	ldr	ip, [r2, #196]	@ <variable>.image_id, <variable>.image_id
	ldr	r2, [r1, #196]	@ <variable>.image_id, <variable>.image_id
	cmp	ip, r2	@ <variable>.image_id, <variable>.image_id
	bne	.L89	@,
	mov	r0, #0	@ D.39981,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L88:
	mvn	r0, #0	@ D.39981,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L94:
	mov	r0, r1	@, p_image
	movw	r1, #:lower16:.LC2	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39981,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	IsImageInVoQueue, .-IsImageInVoQueue
	.align	2
	.global	PrintVoQueue
	.type	PrintVoQueue, %function
PrintVoQueue:
	.fnstart
.LFB1529:
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
	mov	r4, r0	@ pstVoQue, pstVoQue
	ldrh	ip, [r4, #8]	@ <variable>.tail, <variable>.tail
	movw	r1, #:lower16:.LC3	@,
	ldrh	r3, [r0, #4]	@ <variable>.history, <variable>.history
	movt	r1, #:upper16:.LC3	@,
	ldrh	r2, [r0, #6]	@ <variable>.head, <variable>.head
	mov	r0, #1	@,
	str	ip, [sp, #0]	@ <variable>.tail,
	bl	dprint_vfmw	@
	ldrh	r5, [r4, #4]	@ i, <variable>.history
	ldrh	r3, [r4, #8]	@ <variable>.tail, <variable>.tail
	and	r5, r5, #63	@ i.962, i,
	cmp	r3, r5	@ <variable>.tail, i.962
	bne	.L101	@,
	b	.L97	@
.L98:
	add	r2, r4, r5, asl #2	@, tmp149, pstVoQue, i.962,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC5	@,
	movt	r1, #:upper16:.LC5	@,
	ldr	lr, [r2, #12]	@ tmp146, <variable>.image_ptr
	ldr	r2, [lr, #196]	@, <variable>.image_id
	bl	dprint_vfmw	@
	add	r1, r5, #1	@ i.961, i.962,
	ldrh	r0, [r4, #8]	@ <variable>.tail, <variable>.tail
	and	r5, r1, #63	@ i.962, i.961,
	cmp	r0, r5	@ <variable>.tail, i.962
	beq	.L97	@,
.L101:
	tst	r5, #7	@ i.962,
	bne	.L98	@,
	movw	r1, #:lower16:.LC4	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC4	@,
	bl	dprint_vfmw	@
	b	.L98	@
.L97:
	movw	r1, #:lower16:.LC4	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC4	@,
	bl	dprint_vfmw	@
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
	.fnend
	.size	PrintVoQueue, .-PrintVoQueue
	.align	2
	.global	InitVoQueue
	.type	InitVoQueue, %function
InitVoQueue:
	.fnstart
.LFB1528:
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
	movw	r1, #:lower16:.LC6	@,
	mov	r4, r0	@ pstVoQue, pstVoQue
	movt	r1, #:upper16:.LC6	@,
	mov	r0, #12	@,
	bl	dprint_vfmw	@
	mov	r2, #0	@ tmp139,
	mvn	r3, #0	@ tmp147,
	mov	r0, #64	@ movhi	@,
	str	r2, [r4, #316]	@ tmp139, <variable>.SideInfo.SeqImgCnt
	strh	r0, [r4, #0]	@ movhi	@, <variable>.max_queue_size
	mov	r0, #1	@,
	strh	r2, [r4, #2]	@ movhi	@ tmp139, <variable>.queue_size
	str	r3, [r4, #280]	@ tmp147, <variable>.SideInfo.OldSeqCnt
	strh	r2, [r4, #4]	@ movhi	@ tmp139, <variable>.history
	strh	r2, [r4, #6]	@ movhi	@ tmp139, <variable>.head
	strh	r2, [r4, #8]	@ movhi	@ tmp139, <variable>.tail
	str	r2, [r4, #344]	@ tmp139, <variable>.ResetMagicWord
	str	r3, [r4, #272]	@ tmp147, <variable>.SideInfo.OldAspectRatio
	str	r3, [r4, #292]	@ tmp147, <variable>.SideInfo.OldDispCenter
	str	r3, [r4, #288]	@ tmp147, <variable>.SideInfo.OldDispSize
	str	r3, [r4, #284]	@ tmp147, <variable>.SideInfo.OldFrameRate
	str	r3, [r4, #276]	@ tmp147, <variable>.SideInfo.OldScanType
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	InitVoQueue, .-InitVoQueue
	.align	2
	.global	CloseUsdPool
	.type	CloseUsdPool, %function
CloseUsdPool:
	.fnstart
.LFB1544:
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
	mov	r5, r0	@ ChanID, ChanID
	ldr	r0, [r4, r0, asl #2]	@ D.39892, pstVdecUsdPool
	cmp	r0, #0	@ D.39892,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	bl	OSAL_FreeVirMem	@
	mov	r3, #0	@ tmp137,
	str	r3, [r4, r5, asl #2]	@ tmp137, pstVdecUsdPool
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	CloseUsdPool, .-CloseUsdPool
	.align	2
	.global	OpenUsdPool
	.type	OpenUsdPool, %function
OpenUsdPool:
	.fnstart
.LFB1543:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp140,
	movt	r4, #:upper16:.LANCHOR0	@ tmp140,
	mov	r5, r0	@ ChanID, ChanID
	ldr	r0, [r4, r0, asl #2]	@ D.40101, pstVdecUsdPool
	cmp	r0, #0	@ D.40101,
	beq	.L115	@,
.L109:
	mov	r1, #0	@ tmp143,
	mov	r3, r0	@ ivtmp.1043, D.40101
	str	r1, [r0, #0]	@ tmp143, <variable>.s32AccessIdx
	mov	r2, r1	@ i, tmp143
	mov	r0, r1	@ tmp147, i
.L111:
	add	r2, r2, #2	@ i, i,
	add	ip, r3, #1072	@ tmp149, ivtmp.1043,
	cmp	r2, #192	@ i,
	str	r0, [r3, #1044]	@ tmp147, <variable>.from
	str	r0, [r3, #1040]	@ tmp147, <variable>.dnr_used_flag
	add	r3, r3, #2144	@ ivtmp.1043, ivtmp.1043,
	str	r0, [ip, #1040]	@ tmp147, <variable>.dnr_used_flag
	str	r0, [ip, #1044]	@ tmp147, <variable>.from
	bne	.L111	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L115:
	movw	r0, #:lower16:205832	@,
	movt	r0, #:upper16:205832	@,
	bl	OSAL_AllocVirMem	@
	cmp	r0, #0	@ D.40101,
	str	r0, [r4, r5, asl #2]	@ D.40101, pstVdecUsdPool
	mvneq	r0, #0	@ ret,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	b	.L109	@
	.fnend
	.size	OpenUsdPool, .-OpenUsdPool
	.align	2
	.global	IsNewpicSeg
	.type	IsNewpicSeg, %function
IsNewpicSeg:
	.fnstart
.LFB1542:
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
	cmp	r1, #2	@ VidStd,
	ldr	r4, [r2, #0]	@ pu8, <variable>.VirAddr
	beq	.L151	@,
.L117:
	ldrb	r2, [r4, #0]	@ zero_extendqisi2	@ D.39796,* pu8
	cmp	r2, #0	@ D.39796,
	bne	.L152	@,
	ldrb	r3, [r4, #1]	@ zero_extendqisi2	@ prephitmp.1061,
	cmp	r3, #0	@ prephitmp.1061,
	ldrneb	ip, [r4, #2]	@ zero_extendqisi2	@ prephitmp.1065,
	bne	.L120	@,
	ldrb	ip, [r4, #2]	@ zero_extendqisi2	@ prephitmp.1065,
	cmp	ip, #1	@ prephitmp.1065,
	beq	.L122	@,
.L120:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	str	ip, [sp, #0]	@ prephitmp.1065,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
.L123:
	mov	r0, r3	@, ret
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L151:
	ldrb	r3, [r2, #72]	@ zero_extendqisi2	@ tmp156,
	tst	r3, #1	@ tmp156,
	movne	r3, #1	@ IsShortHead,
	beq	.L117	@,
.L118:
	ldrb	r2, [r4, #3]	@ zero_extendqisi2	@ tmp213,
	add	ip, r2, #75	@ tmp171, tmp213,
	uxtb	r1, ip	@ tmp173, tmp171
	cmp	r2, #179	@ tmp213,
	cmpne	r1, #1	@, tmp173,
	bls	.L137	@,
	cmp	r2, #176	@ tmp213,
	beq	.L137	@,
	cmp	r2, #254	@ tmp213,
	beq	.L137	@,
	cmp	r2, #47	@ tmp213,
	bls	.L137	@,
.L138:
	cmp	r3, #1	@ IsShortHead,
	mvnne	r3, #0	@ ret,
	beq	.L139	@,
.L140:
	cmp	r2, #182	@ tmp213,
	bne	.L123	@,
.L148:
	mov	r2, #0	@ tmp211,
.L149:
	str	r2, [r0, #0]	@ tmp211,* pNewPicDetector
	b	.L123	@
.L122:
	cmp	r1, #16	@ VidStd,
	ldrls	pc, [pc, r1, asl #2]	@ VidStd
	b	.L124	@
.L132:
	.word	.L125
	.word	.L126
	.word	.L127
	.word	.L128
	.word	.L124
	.word	.L124
	.word	.L129
	.word	.L124
	.word	.L124
	.word	.L124
	.word	.L124
	.word	.L124
	.word	.L124
	.word	.L124
	.word	.L124
	.word	.L130
	.word	.L131
.L125:
	mov	r1, r4	@, pu8
	bl	H264_IsNewPicNal	@
	cmp	r0, #0	@,
	beq	.L133	@,
.L124:
	mvn	r3, #0	@ ret,
	b	.L123	@
.L131:
	mov	r1, r4	@, pu8
	bl	HEVC_IsNewPicNal	@
	cmp	r0, #0	@,
	bne	.L124	@,
.L133:
	mov	r3, #0	@ ret,
	b	.L123	@
.L130:
	mov	r1, r4	@, pu8
	bl	MVC_IsNewPicNal	@
	cmp	r0, #0	@,
	bne	.L124	@,
	mov	r3, #0	@ ret,
	b	.L123	@
.L129:
	ldrb	r2, [r4, #3]	@ zero_extendqisi2	@ tmp215,
	cmp	r2, #176	@ tmp215,
	cmpne	r2, #179	@, tmp215,
	beq	.L141	@,
	cmp	r2, #182	@ tmp215,
	beq	.L141	@,
	cmp	r2, #183	@ tmp215,
	beq	.L141	@,
.L142:
	mvn	r3, #0	@ ret,
.L143:
	cmp	r2, #179	@ tmp215,
	cmpne	r2, #182	@, tmp215,
	bne	.L123	@,
	mov	r2, #0	@ tmp211,
	b	.L149	@
.L128:
	ldrb	r2, [r4, #3]	@ zero_extendqisi2	@ prephitmp.1080,
	cmp	r2, #0	@ prephitmp.1080,
	cmpne	r2, #179	@, prephitmp.1080,
	beq	.L134	@,
	cmp	r2, #184	@ prephitmp.1080,
	beq	.L134	@,
	cmp	r2, #183	@ prephitmp.1080,
	bne	.L124	@,
.L134:
	ldr	r3, [r0, #0]	@ tmp168,* pNewPicDetector
	cmp	r3, #0	@ tmp168,
	moveq	r2, #1	@ tmp169,
	streq	r2, [r0, #0]	@ tmp169,* pNewPicDetector
	ldreqb	r2, [r4, #3]	@ zero_extendqisi2	@ prephitmp.1080,
	mvnne	r3, #0	@ ret,
	cmp	r2, #0	@ prephitmp.1080,
	streq	r2, [r0, #0]	@ tmp211,* pNewPicDetector
	b	.L123	@
.L126:
	ldrb	r2, [r4, #3]	@ zero_extendqisi2	@ tmp216,
	cmp	r2, #10	@ tmp216,
	cmpne	r2, #12	@, tmp216,
	beq	.L144	@,
	cmp	r2, #13	@ tmp216,
	beq	.L144	@,
	cmp	r2, #14	@ tmp216,
	beq	.L144	@,
	cmp	r2, #15	@ tmp216,
	bne	.L124	@,
.L144:
	ldr	r3, [r0, #0]	@ tmp208,* pNewPicDetector
	cmp	r3, #0	@ tmp208,
	moveq	r2, #1	@ tmp209,
	streq	r2, [r0, #0]	@ tmp209,* pNewPicDetector
	ldreqb	r2, [r4, #3]	@ zero_extendqisi2	@ tmp216,
	mvnne	r3, #0	@ ret,
	cmp	r2, #13	@ tmp216,
	bne	.L123	@,
	b	.L148	@
.L127:
	mov	r3, #0	@ IsShortHead,
	b	.L118	@
.L141:
	ldr	r3, [r0, #0]	@ tmp191,* pNewPicDetector
	cmp	r3, #0	@ tmp191,
	bne	.L142	@,
	mov	r2, #1	@ tmp192,
	str	r2, [r0, #0]	@ tmp192,* pNewPicDetector
	ldrb	r2, [r4, #3]	@ zero_extendqisi2	@ tmp215,
	b	.L143	@
.L137:
	ldr	r1, [r0, #0]	@ tmp180,* pNewPicDetector
	cmp	r1, #0	@ tmp180,
	bne	.L138	@,
.L139:
	mov	r3, #1	@ tmp181,
	str	r3, [r0, #0]	@ tmp181,* pNewPicDetector
	mov	r3, #0	@ ret,
	ldrb	r2, [r4, #3]	@ zero_extendqisi2	@ tmp213,
	b	.L140	@
.L152:
	ldrb	ip, [r4, #2]	@ zero_extendqisi2	@ prephitmp.1065,
	ldrb	r3, [r4, #1]	@ zero_extendqisi2	@ prephitmp.1061,
	b	.L120	@
	.fnend
	.size	IsNewpicSeg, .-IsNewpicSeg
	.align	2
	.global	ReleasePacket
	.type	ReleasePacket, %function
ReleasePacket:
	.fnstart
.LFB1540:
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
	mov	r4, r1	@ pCtx, pCtx
	cmp	r0, #16	@ VidStd,
	ldrls	pc, [pc, r0, asl #2]	@ VidStd
	b	.L154	@
.L163:
	.word	.L171
	.word	.L171
	.word	.L156
	.word	.L171
	.word	.L154
	.word	.L157
	.word	.L158
	.word	.L154
	.word	.L159
	.word	.L160
	.word	.L161
	.word	.L161
	.word	.L161
	.word	.L162
	.word	.L154
	.word	.L171
	.word	.L171
.L154:
	mov	r2, r0	@, VidStd
	movw	r1, #:lower16:.LC11	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC11	@,
	bl	dprint_vfmw	@
.L171:
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L160:
	ldr	r5, [r1, #0]	@ D.39628, <variable>.pstExtraData
	ldrb	lr, [r5, #229]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	lr, #1	@ <variable>.IsLastSeg,
	beq	.L172	@,
.L170:
	add	r0, r5, #224	@, D.39659,
	mov	r1, #160	@,
	bl	__memzero	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L162:
	ldr	r5, [r1, #0]	@ D.39648, <variable>.pstExtraData
	movw	ip, #8520	@ tmp175,
	ldr	r0, [r1, ip]	@, <variable>.ChanID
	ldr	r1, [r5, #240]	@, <variable>.StreamID
	bl	SM_ReleaseStreamSeg	@
	ldrb	r1, [r5, #229]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r1, #1	@ <variable>.IsLastSeg,
	beq	.L170	@,
	movw	r1, #:lower16:.LC9	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC9	@,
	bl	dprint_vfmw	@
	b	.L170	@
.L156:
	movw	r0, #22060	@ tmp147,
	ldr	r5, [r1, r0]	@ D.39599, <variable>.pstExtraData
	ldrb	r3, [r5, #229]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r3, #1	@ <variable>.IsLastSeg,
	beq	.L173	@,
	movw	r6, #22960	@ tmp152,
	ldr	r1, [r5, #240]	@, <variable>.StreamID
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	bl	SM_ReleaseStreamSeg	@
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	ldr	r1, [r5, #320]	@, <variable>.StreamID
	bl	SM_ReleaseStreamSeg	@
	b	.L170	@
.L161:
	ldr	r5, [r1, #0]	@ D.39659, <variable>.pstExtraData
	movw	lr, #13000	@ tmp181,
	ldr	r0, [r1, lr]	@, <variable>.ChanID
	ldr	r1, [r5, #240]	@, <variable>.StreamID
	bl	SM_ReleaseStreamSeg	@
	ldrb	r3, [r5, #229]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r3, #1	@ <variable>.IsLastSeg,
	beq	.L170	@,
	movw	r1, #:lower16:.LC10	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	b	.L170	@
.L157:
	ldr	r5, [r1, #0]	@ D.39638, <variable>.pstExtraData
	ldrb	r0, [r5, #229]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r0, #1	@ <variable>.IsLastSeg,
	bne	.L170	@,
	movw	r2, #:lower16:66944	@ tmp171,
	movt	r2, #:upper16:66944	@ tmp171,
	ldr	r1, [r5, #240]	@, <variable>.StreamID
	ldr	r0, [r4, r2]	@,
	bl	SM_ReleaseStreamSeg	@
	b	.L170	@
.L158:
	movw	r1, #:lower16:.LC8	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC8	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L159:
	ldr	r5, [r1, #0]	@ D.39618, <variable>.pstExtraData
	ldrb	r1, [r5, #229]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r1, #1	@ <variable>.IsLastSeg,
	bne	.L170	@,
	movw	ip, #:lower16:79272	@ tmp161,
	movt	ip, #:upper16:79272	@ tmp161,
	ldr	r1, [r5, #240]	@, <variable>.StreamID
	ldr	r0, [r4, ip]	@,
	bl	SM_ReleaseStreamSeg	@
	b	.L170	@
.L173:
	movw	r2, #22960	@ tmp149,
	ldr	r1, [r5, #240]	@, <variable>.StreamID
	ldr	r0, [r4, r2]	@,
	bl	SM_ReleaseStreamSeg	@
	b	.L170	@
.L172:
	movw	r3, #:lower16:79256	@ tmp166,
	movt	r3, #:upper16:79256	@ tmp166,
	ldr	r1, [r5, #240]	@, <variable>.StreamID
	ldr	r0, [r4, r3]	@,
	bl	SM_ReleaseStreamSeg	@
	b	.L170	@
	.fnend
	.size	ReleasePacket, .-ReleasePacket
	.align	2
	.global	ReleaseCurPic
	.type	ReleaseCurPic, %function
ReleaseCurPic:
	.fnstart
.LFB1541:
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
	mov	r4, r1	@ pCtx, pCtx
	cmp	r0, #16	@ VidStd,
	ldrls	pc, [pc, r0, asl #2]	@ VidStd
	b	.L175	@
.L188:
	.word	.L176
	.word	.L177
	.word	.L178
	.word	.L179
	.word	.L175
	.word	.L180
	.word	.L181
	.word	.L175
	.word	.L182
	.word	.L183
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L185
	.word	.L175
	.word	.L186
	.word	.L187
.L187:
	mov	r0, r1	@, pCtx
	bl	HEVC_ClearCurrPic	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L175:
	mov	r2, r0	@, VidStd
	movw	r1, #:lower16:.LC11	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC11	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L176:
	mov	r0, r1	@, pCtx
	bl	H264_ClearCurrPic	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L177:
	movw	r3, #:lower16:114320	@ tmp164,
	movt	r3, #:upper16:114320	@ tmp164,
	add	r2, r1, #77824	@, pCtx,
	add	r0, r2, #424	@,,
	ldr	r1, [r1, r3]	@, <variable>.ChanID
	bl	VC1_ClearCurPic	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L178:
	mov	r0, r1	@, pCtx
	bl	MP4_ClearCurPic	@
	mov	r0, r4	@, pCtx
	bl	MP4_Clean_HeadPacket	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L179:
	mov	r0, r1	@, pCtx
	bl	MP2_ClearCurPic	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L180:
	ldr	r5, [r1, #0]	@ D.39735, <variable>.pstExtraData
	ldrb	r1, [r5, #229]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r1, #1	@ <variable>.IsLastSeg,
	beq	.L196	@,
.L194:
	add	r0, r5, #224	@, D.39759,
	mov	r1, #160	@,
	bl	__memzero	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L181:
	mov	r0, r1	@, pCtx
	bl	AVS_ClearCurPic	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L182:
	ldr	r5, [r1, #0]	@ D.39713, <variable>.pstExtraData
	ldrb	r3, [r5, #229]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r3, #1	@ <variable>.IsLastSeg,
	bne	.L194	@,
	movw	r2, #:lower16:79272	@ tmp148,
	movt	r2, #:upper16:79272	@ tmp148,
	ldr	r1, [r5, #240]	@, <variable>.StreamID
	ldr	r0, [r4, r2]	@,
	bl	SM_ReleaseStreamSeg	@
	b	.L194	@
.L183:
	ldr	r5, [r1, #0]	@ D.39725, <variable>.pstExtraData
	ldrb	r0, [r5, #229]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r0, #1	@ <variable>.IsLastSeg,
	bne	.L194	@,
	movw	ip, #:lower16:79256	@ tmp153,
	movt	ip, #:upper16:79256	@ tmp153,
	ldr	r1, [r5, #240]	@, <variable>.StreamID
	ldr	r0, [r4, ip]	@,
	bl	SM_ReleaseStreamSeg	@
	b	.L194	@
.L184:
	ldr	r5, [r1, #0]	@ D.39759, <variable>.pstExtraData
	movw	lr, #13000	@ tmp172,
	ldr	r0, [r1, lr]	@, <variable>.ChanID
	ldr	r1, [r5, #240]	@, <variable>.StreamID
	bl	SM_ReleaseStreamSeg	@
	ldrb	r1, [r5, #229]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r1, #1	@ <variable>.IsLastSeg,
	beq	.L194	@,
	movw	r1, #:lower16:.LC10	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	b	.L194	@
.L185:
	ldr	r5, [r1, #0]	@ D.39748, <variable>.pstExtraData
	movw	ip, #8520	@ tmp166,
	ldr	r0, [r1, ip]	@, <variable>.ChanID
	ldr	r1, [r5, #240]	@, <variable>.StreamID
	bl	SM_ReleaseStreamSeg	@
	ldrb	r0, [r5, #229]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r0, #1	@ <variable>.IsLastSeg,
	beq	.L194	@,
	movw	r1, #:lower16:.LC9	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC9	@,
	bl	dprint_vfmw	@
	b	.L194	@
.L186:
	mov	r0, r1	@, pCtx
	bl	MVC_ClearCurrPic	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L196:
	movw	lr, #:lower16:66944	@ tmp158,
	movt	lr, #:upper16:66944	@ tmp158,
	ldr	r1, [r5, #240]	@, <variable>.StreamID
	ldr	r0, [r4, lr]	@,
	bl	SM_ReleaseStreamSeg	@
	b	.L194	@
	.fnend
	.size	ReleaseCurPic, .-ReleaseCurPic
	.align	2
	.global	SegMan
	.type	SegMan, %function
SegMan:
	.fnstart
.LFB1539:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	subs	r4, r1, #0	@ pSegMan, pSegMan
	mov	r6, r0	@ ChanID, ChanID
	beq	.L198	@,
	ldr	r3, [r4, #8]	@ <variable>.CurrSeg.VirAddr, <variable>.CurrSeg.VirAddr
	cmp	r3, #0	@ <variable>.CurrSeg.VirAddr,
	beq	.L198	@,
	movw	r3, #:lower16:s_pstVfmwChan	@ tmp230,
	movt	r3, #:upper16:s_pstVfmwChan	@ tmp230,
	ldr	r2, [r3, r0, asl #2]	@ D.39476, s_pstVfmwChan
	ldr	r1, [r2, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r1, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	beq	.L211	@,
.L201:
	ldrb	r5, [r4, #13]	@ zero_extendqisi2	@ D.39485, <variable>.CurrSeg.IsLastSeg
	mov	r2, #0	@ tmp159,
	strb	r2, [r4, #408]	@ tmp159, <variable>.u32SCDWrapAround
	cmp	r5, #1	@ D.39485,
	beq	.L212	@,
	cmp	r5, #0	@ D.39485,
	beq	.L213	@,
.L204:
	mvn	r0, #0	@ ret,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L213:
	add	r8, r4, #88	@ temp.1179, pSegMan,
	add	r7, r4, #168	@ __p, pSegMan,
	add	r1, r4, #8	@, pSegMan,
	mov	r2, #80	@,
	mov	r0, r8	@, temp.1179
	bl	memcpy	@
	mov	r1, #80	@,
	mov	r0, r7	@, __p
	bl	__memzero	@
	ldrb	r1, [r4, #2]	@ zero_extendqisi2	@ <variable>.ConvolutionPacketNum, <variable>.ConvolutionPacketNum
	add	r3, r1, #1	@ tmp176, <variable>.ConvolutionPacketNum,
	uxtb	ip, r3	@ D.39503, tmp176
	strb	ip, [r4, #2]	@ D.39503, <variable>.ConvolutionPacketNum
	cmp	ip, #1	@ D.39503,
	bls	.L204	@,
	ldr	r1, [r4, #104]	@, <variable>.StreamID
	mov	r0, r6	@, ChanID
	bl	SM_ReleaseStreamSeg	@
	ldr	r1, [r4, #184]	@, <variable>.StreamID
	mov	r0, r6	@, ChanID
	bl	SM_ReleaseStreamSeg	@
	mov	r0, r8	@, temp.1179
	mov	r1, #80	@,
	bl	__memzero	@
	mov	r0, r7	@, __p
	mov	r1, #80	@,
	bl	__memzero	@
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC13	@,
	movt	r1, #:upper16:.LC13	@,
	bl	dprint_vfmw	@
	movw	r2, #:lower16:g_event_report	@ tmp181,
	movt	r2, #:upper16:g_event_report	@ tmp181,
	ldr	ip, [r2, #0]	@ g_event_report.525, g_event_report
	cmp	ip, #0	@ g_event_report.525,
	beq	.L205	@,
	mov	r2, r5	@, D.39485
	mov	r0, r6	@, ChanID
	mov	r1, #113	@,
	mov	r3, r5	@, tmp2
	blx	ip	@ g_event_report.525
.L205:
	mov	lr, #0	@ tmp182,
	mvn	r0, #0	@ ret,
	strb	lr, [r4, #2]	@ tmp182, <variable>.ConvolutionPacketNum
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L211:
	ldr	r2, [r2, #1924]	@ <variable>.stSynExtraData.s32WaitFsFlag, <variable>.stSynExtraData.s32WaitFsFlag
	cmp	r2, #1	@ <variable>.stSynExtraData.s32WaitFsFlag,
	bne	.L201	@,
	ldrb	r0, [r4, #408]	@ zero_extendqisi2	@ <variable>.u32SCDWrapAround, <variable>.u32SCDWrapAround
	cmp	r0, #1	@ <variable>.u32SCDWrapAround,
	bne	.L201	@,
	add	r0, r4, #88	@, pSegMan,
	add	r1, r4, #248	@, pSegMan,
	mov	r2, #160	@,
	bl	memcpy	@
	mov	r0, #0	@ tmp157,
	strb	r0, [r4, #408]	@ tmp157, <variable>.u32SCDWrapAround
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L212:
	ldrb	r5, [r4, #2]	@ zero_extendqisi2	@ D.39487, <variable>.ConvolutionPacketNum
	cmp	r5, r2	@ D.39487,
	beq	.L214	@,
	cmp	r5, #1	@ D.39487,
	bne	.L204	@,
	ldr	r1, [r3, r6, asl #2]	@ tmp185, s_pstVfmwChan
	movw	ip, #:lower16:1047552	@ tmp232,
	ldr	r0, [r4, #100]	@ <variable>.LenInByte, <variable>.LenInByte
	movt	ip, #:upper16:1047552	@ tmp232,
	ldr	r3, [r1, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #6	@ <variable>.eVidStd,
	movne	ip, #1024	@ s32MinBottomSegLen,
	cmp	ip, r0	@ s32MinBottomSegLen, <variable>.LenInByte
	ble	.L208	@,
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC14	@,
	movt	r1, #:upper16:.LC14	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #100]	@ D.39535, <variable>.LenInByte
	ldr	r0, [r4, #8]	@ <variable>.CurrSeg.VirAddr, <variable>.CurrSeg.VirAddr
	ldr	r1, [r4, #88]	@, <variable>.VirAddr
	mov	r2, r3	@, D.39535
	rsb	r0, r3, r0	@, D.39535, <variable>.CurrSeg.VirAddr
	bl	memcpy	@
	ldr	r3, [r4, #100]	@ <variable>.LenInByte, <variable>.LenInByte
	ldr	r1, [r4, #8]	@ <variable>.CurrSeg.VirAddr, <variable>.CurrSeg.VirAddr
	mov	r0, r6	@, ChanID
	ldr	r2, [r4, #16]	@ <variable>.CurrSeg.PhyAddr, <variable>.CurrSeg.PhyAddr
	ldr	ip, [r4, #20]	@ <variable>.CurrSeg.LenInByte, <variable>.CurrSeg.LenInByte
	rsb	r1, r3, r1	@ tmp200, <variable>.LenInByte, <variable>.CurrSeg.VirAddr
	rsb	r2, r3, r2	@ tmp203, <variable>.LenInByte, <variable>.CurrSeg.PhyAddr
	strb	r5, [r4, #93]	@ D.39487, <variable>.IsLastSeg
	add	r3, r3, ip	@ tmp206, <variable>.LenInByte, <variable>.CurrSeg.LenInByte
	str	r1, [r4, #88]	@ tmp200, <variable>.VirAddr
	str	r2, [r4, #96]	@ tmp203, <variable>.PhyAddr
	ldr	r1, [r4, #104]	@, <variable>.StreamID
	str	r3, [r4, #100]	@ tmp206, <variable>.LenInByte
	bl	SM_ReleaseStreamSeg	@
	ldr	r5, [r4, #24]	@ <variable>.CurrSeg.StreamID, <variable>.CurrSeg.StreamID
	add	r0, r4, #168	@, pSegMan,
	mov	r1, #80	@,
	str	r5, [r4, #104]	@ <variable>.CurrSeg.StreamID, <variable>.StreamID
	bl	__memzero	@
.L209:
	mov	r5, #0	@ tmp221,
	mov	lr, #1	@ tmp223,
	add	r1, r4, #88	@, pSegMan,
	strb	r5, [r4, #2]	@ tmp221, <variable>.ConvolutionPacketNum
	strb	lr, [r4, #408]	@ tmp223, <variable>.u32SCDWrapAround
	add	r0, r4, #248	@, pSegMan,
	mov	r2, #160	@,
	bl	memcpy	@
	mov	r0, r5	@ ret, tmp221
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L214:
	add	r1, r4, #8	@, pSegMan,
	mov	r2, #80	@,
	add	r0, r4, #88	@, pSegMan,
	bl	memcpy	@
	add	r0, r4, #168	@, pSegMan,
	mov	r1, #80	@,
	bl	__memzero	@
	strb	r5, [r4, #2]	@ D.39487, <variable>.ConvolutionPacketNum
	mov	r0, r5	@ ret, D.39487
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L208:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC15	@,
	movt	r1, #:upper16:.LC15	@,
	bl	dprint_vfmw	@
	add	r0, r4, #168	@, pSegMan,
	add	r1, r4, #8	@, pSegMan,
	mov	r2, #80	@,
	bl	memcpy	@
	b	.L209	@
.L198:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC12	@,
	movt	r1, #:upper16:.LC12	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	.fnend
	.size	SegMan, .-SegMan
	.align	2
	.global	DecodeStream
	.type	DecodeStream, %function
DecodeStream:
	.fnstart
.LFB1538:
	@ args = 0, pretend = 0, frame = 96
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #96
	sub	sp, sp, #96	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r4, r0	@ pSegMan, pSegMan
	mov	r5, r2	@ pstCtx, pstCtx
	cmp	r1, #16	@ VideoStandard,
	ldrls	pc, [pc, r1, asl #2]	@ VideoStandard
	b	.L263	@
.L230:
	.word	.L217
	.word	.L218
	.word	.L219
	.word	.L220
	.word	.L221
	.word	.L222
	.word	.L223
	.word	.L263
	.word	.L224
	.word	.L225
	.word	.L226
	.word	.L226
	.word	.L226
	.word	.L227
	.word	.L221
	.word	.L228
	.word	.L229
.L218:
	ldrb	r2, [r0, #13]	@ zero_extendqisi2	@, <variable>.CurrSeg.IsLastSeg
	movw	r1, #:lower16:.LC16	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC16	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #16]	@, <variable>.CurrSeg.PhyAddr
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC17	@,
	movt	r1, #:upper16:.LC17	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #20]	@, <variable>.CurrSeg.LenInByte
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC18	@,
	movt	r1, #:upper16:.LC18	@,
	bl	dprint_vfmw	@
	ldr	r3, [r5, #0]	@ D.39197, <variable>.pstExtraData
	ldr	r2, [r3, #556]	@ D.39198, <variable>.StdExt.Vc1Ext.IsAdvProfile
	cmp	r2, #1	@ D.39198,
	bhi	.L276	@,
	ldr	r0, [r3, #560]	@ <variable>.StdExt.Vc1Ext.CodecVersion, <variable>.StdExt.Vc1Ext.CodecVersion
	cmp	r0, #8	@ <variable>.StdExt.Vc1Ext.CodecVersion,
	bgt	.L277	@,
	movw	lr, #:lower16:81344	@ tmp267,
	movt	lr, #:upper16:81344	@ tmp267,
	uxtb	r2, r2	@ D.39207, D.39198
	movw	ip, #:lower16:81346	@ tmp269,
	strb	r2, [r5, lr]	@ D.39207, <variable>.CodecInfo.PreParseInfo.IsAdvProfile
	movt	ip, #:upper16:81346	@ tmp269,
	ldr	r3, [r3, #560]	@ <variable>.StdExt.Vc1Ext.CodecVersion, <variable>.StdExt.Vc1Ext.CodecVersion
	cmp	r2, #1	@ D.39207,
	strb	r3, [r5, ip]	@ <variable>.StdExt.Vc1Ext.CodecVersion, <variable>.CodecInfo.PreParseInfo.CodecVersion
	beq	.L278	@,
	ldrb	r0, [r4, #14]	@ zero_extendqisi2	@ <variable>.CurrSeg.IsStreamEnd, <variable>.CurrSeg.IsStreamEnd
	cmp	r0, #1	@ <variable>.CurrSeg.IsStreamEnd,
	movweq	r6, #:lower16:114320	@ tmp290,
	movteq	r6, #:upper16:114320	@ tmp290,
	beq	.L264	@,
	add	r6, r4, #88	@ D.39244, pSegMan,
	add	r1, r4, #8	@, pSegMan,
	mov	r2, #80	@,
	mov	r0, r6	@, D.39244
	bl	memcpy	@
	add	r0, r4, #168	@, pSegMan,
	mov	r1, #80	@,
	bl	__memzero	@
	ldr	r3, [r4, #100]	@ <variable>.LenInByte, <variable>.LenInByte
	cmp	r3, #15	@ <variable>.LenInByte,
	bgt	.L244	@,
	movw	r6, #:lower16:114320	@ tmp303,
	movw	r1, #:lower16:.LC21	@,
	movt	r6, #:upper16:114320	@ tmp303,
	movt	r1, #:upper16:.LC21	@,
	mov	r0, #0	@,
.L270:
	bl	dprint_vfmw	@
	ldr	r1, [r4, #104]	@, <variable>.StreamID
	ldr	r0, [r5, r6]	@, <variable>.ChanID
	bl	SM_ReleaseStreamSeg	@
	movw	r1, #:lower16:g_event_report	@ tmp322,
	movt	r1, #:upper16:g_event_report	@ tmp322,
	ldr	ip, [r1, #0]	@ g_event_report.1256, g_event_report
	cmp	ip, #0	@ g_event_report.1256,
	beq	.L263	@,
	mov	r2, #0	@,
	ldr	r0, [r5, r6]	@,
	mov	r1, #113	@,
	mov	r3, r2	@,
	blx	ip	@ g_event_report.1256
.L263:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L229:
	ldrb	r3, [r4, #15]	@ zero_extendqisi2	@ <variable>.CurrSeg.DspCheckPicOverFlag, <variable>.CurrSeg.DspCheckPicOverFlag
	sub	r1, fp, #100	@,,
	ldrd	r8, [r0, #32]	@ <variable>.CurrSeg.Pts, pSegMan,
	mov	r0, r2	@, pstCtx
	ldr	r7, [r4, #8]	@ <variable>.CurrSeg.VirAddr, <variable>.CurrSeg.VirAddr
	ldr	r6, [r4, #16]	@ <variable>.CurrSeg.PhyAddr, <variable>.CurrSeg.PhyAddr
	ldr	lr, [r4, #20]	@ <variable>.CurrSeg.LenInByte, <variable>.CurrSeg.LenInByte
	ldrb	ip, [r4, #13]	@ zero_extendqisi2	@ <variable>.CurrSeg.IsLastSeg, <variable>.CurrSeg.IsLastSeg
	ldr	r2, [r4, #24]	@ <variable>.CurrSeg.StreamID, <variable>.CurrSeg.StreamID
	strb	r3, [fp, #-99]	@ <variable>.CurrSeg.DspCheckPicOverFlag, HevcPack.pack_is_pic_over_flag
	strd	r8, [fp, #-76]	@ <variable>.CurrSeg.Pts,,
	str	r7, [fp, #-96]	@ <variable>.CurrSeg.VirAddr, HevcPack.p_stream
	str	r6, [fp, #-92]	@ <variable>.CurrSeg.PhyAddr, HevcPack.strm_phy_addr
	str	lr, [fp, #-88]	@ <variable>.CurrSeg.LenInByte, HevcPack.stream_len
	strb	ip, [fp, #-100]	@ <variable>.CurrSeg.IsLastSeg, HevcPack.last_pack_in_nal
	str	r2, [fp, #-84]	@ <variable>.CurrSeg.StreamID, HevcPack.StreamID
	bl	HEVCDEC_DecodePacket	@
	cmn	r0, #2	@,
	moveq	r3, #1	@ tmp231,
	movne	r3, #0	@ tmp233,
	strb	r3, [r4, #1]	@ tmp233, <variable>.IsCurrSegWaitDec
	movw	r3, #:lower16:1960192	@ tmp235,
	movt	r3, #:upper16:1960192	@ tmp235,
	ldr	r4, [r5, r3]	@ <variable>.pHevcDecParam, <variable>.pHevcDecParam
	cmp	r4, #0	@ <variable>.pHevcDecParam,
	bne	.L263	@,
	ldrb	r0, [r5, #6]	@ zero_extendqisi2	@ <variable>.IsStreamEndFlag, <variable>.IsStreamEndFlag
	cmp	r0, #1	@ <variable>.IsStreamEndFlag,
	bne	.L263	@,
	ldr	r0, [r5, #236]	@, <variable>.ChanID
	bl	VCTRL_OutputLastFrame	@
	strb	r4, [r5, #6]	@ <variable>.pHevcDecParam, <variable>.IsStreamEndFlag
	b	.L263	@
.L217:
	ldrb	r3, [r4, #15]	@ zero_extendqisi2	@ <variable>.CurrSeg.DspCheckPicOverFlag, <variable>.CurrSeg.DspCheckPicOverFlag
	sub	r1, fp, #68	@,,
	ldrd	r8, [r0, #32]	@ <variable>.CurrSeg.Pts, pSegMan,
	mov	r0, r2	@, pstCtx
	ldr	r7, [r4, #8]	@ <variable>.CurrSeg.VirAddr, <variable>.CurrSeg.VirAddr
	ldr	r6, [r4, #16]	@ <variable>.CurrSeg.PhyAddr, <variable>.CurrSeg.PhyAddr
	ldr	lr, [r4, #20]	@ <variable>.CurrSeg.LenInByte, <variable>.CurrSeg.LenInByte
	ldrb	ip, [r4, #13]	@ zero_extendqisi2	@ <variable>.CurrSeg.IsLastSeg, <variable>.CurrSeg.IsLastSeg
	ldr	r2, [r4, #24]	@ <variable>.CurrSeg.StreamID, <variable>.CurrSeg.StreamID
	strb	r3, [fp, #-67]	@ <variable>.CurrSeg.DspCheckPicOverFlag, H264Pack.pack_is_pic_over_flag
	strd	r8, [fp, #-44]	@ <variable>.CurrSeg.Pts,,
	str	r7, [fp, #-64]	@ <variable>.CurrSeg.VirAddr, H264Pack.p_stream
	str	r6, [fp, #-60]	@ <variable>.CurrSeg.PhyAddr, H264Pack.strm_phy_addr
	str	lr, [fp, #-56]	@ <variable>.CurrSeg.LenInByte, H264Pack.stream_len
	strb	ip, [fp, #-68]	@ <variable>.CurrSeg.IsLastSeg, H264Pack.last_pack_in_nal
	str	r2, [fp, #-52]	@ <variable>.CurrSeg.StreamID, H264Pack.StreamID
	bl	H264DEC_DecodePacket	@
	cmn	r0, #2	@,
	moveq	r3, #1	@ tmp209,
	movne	r3, #0	@ tmp211,
	strb	r3, [r4, #1]	@ tmp211, <variable>.IsCurrSegWaitDec
	ldr	r4, [r5, #360]	@ <variable>.pH264DecParam, <variable>.pH264DecParam
	cmp	r4, #0	@ <variable>.pH264DecParam,
	bne	.L263	@,
	movw	r6, #13560	@ tmp214,
	ldrb	r0, [r5, r6]	@ zero_extendqisi2	@ <variable>.IsStreamEndFlag, <variable>.IsStreamEndFlag
	cmp	r0, #1	@ <variable>.IsStreamEndFlag,
	bne	.L263	@,
	movw	r1, #57224	@ tmp216,
	ldr	r0, [r5, r1]	@,
	bl	VCTRL_OutputLastFrame	@
	strb	r4, [r5, r6]	@ <variable>.pH264DecParam,
	b	.L263	@
.L219:
	movw	lr, #22960	@ tmp348,
	mov	r0, r2	@, pstCtx
	ldr	r6, [r2, lr]	@ ChanID.1265, <variable>.ChanID
	bl	MP4_GetPacketState	@
	cmp	r0, #3	@,
	beq	.L279	@,
.L250:
	movw	lr, #22960	@ tmp354,
	mov	r1, r4	@, pSegMan
	ldr	r0, [r5, lr]	@, <variable>.ChanID
	bl	SegMan	@
	cmp	r0, #0	@,
	beq	.L280	@,
.L252:
	ldr	r4, [r5, #1036]	@ <variable>.pMp4DecParam, <variable>.pMp4DecParam
	cmp	r4, #0	@ <variable>.pMp4DecParam,
	bne	.L263	@,
	movw	r6, #56296	@ tmp358,
	ldrb	r0, [r5, r6]	@ zero_extendqisi2	@ <variable>.IsStreamEndFlag, <variable>.IsStreamEndFlag
	cmp	r0, #1	@ <variable>.IsStreamEndFlag,
	bne	.L263	@,
	movw	ip, #22960	@ tmp360,
	ldr	r0, [r5, ip]	@,
	bl	VCTRL_OutputLastFrame	@
	strb	r4, [r5, r6]	@ <variable>.pMp4DecParam,
	b	.L263	@
.L220:
	movw	r3, #:lower16:113648	@ tmp325,
	movt	r3, #:upper16:113648	@ tmp325,
	mov	r0, r2	@, pstCtx
	ldr	r6, [r2, r3]	@ ChanID.1258, <variable>.ChanID
	bl	MP2_GetPacketState	@
	cmp	r0, #2	@,
	beq	.L281	@,
.L246:
	movw	ip, #:lower16:113648	@ tmp331,
	movt	ip, #:upper16:113648	@ tmp331,
	mov	r1, r4	@, pSegMan
	ldr	r0, [r5, ip]	@, <variable>.ChanID
	bl	SegMan	@
	subs	r6, r0, #0	@ ret.1262,
	beq	.L282	@,
.L248:
	ldr	r4, [r5, #4]	@ <variable>.pMp2DecParam, <variable>.pMp2DecParam
	cmp	r4, #0	@ <variable>.pMp2DecParam,
	bne	.L263	@,
	movw	r6, #:lower16:113666	@ tmp341,
	movt	r6, #:upper16:113666	@ tmp341,
	ldrb	r0, [r5, r6]	@ zero_extendqisi2	@ <variable>.IsStreamEndFlag, <variable>.IsStreamEndFlag
	cmp	r0, #1	@ <variable>.IsStreamEndFlag,
	bne	.L263	@,
	movw	r2, #:lower16:113648	@ tmp343,
	movt	r2, #:upper16:113648	@ tmp343,
	ldr	r0, [r5, r2]	@,
	bl	VCTRL_OutputLastFrame	@
	strb	r4, [r5, r6]	@ <variable>.pMp2DecParam,
	b	.L263	@
.L221:
	add	r6, r0, #88	@ tmp479, pSegMan,
	mov	lr, #1	@ tmp477,
	add	r1, r0, #8	@, pSegMan,
	strb	lr, [r0, #1]	@ tmp477, <variable>.IsCurrSegWaitDec
	mov	r2, #80	@,
	mov	r0, r6	@, tmp479
	bl	memcpy	@
	movw	r3, #:lower16:g_SdecFunc	@ tmp485,
	movt	r3, #:upper16:g_SdecFunc	@ tmp485,
	ldr	r3, [r3, #12]	@ D.39437, g_SdecFunc.pfun_iMediaSoftDEC_Decode
	cmp	r3, #0	@ D.39437,
	beq	.L262	@,
	mov	r1, r6	@, tmp479
	mov	r0, r5	@, pstCtx
	blx	r3	@ D.39437
	cmn	r0, #2	@,
	beq	.L263	@,
.L262:
	ldr	r0, [r5, #0]	@, <variable>.ChanID
	ldr	r1, [r4, #24]	@, <variable>.CurrSeg.StreamID
	bl	SM_ReleaseStreamSeg	@
	mov	r2, #0	@ tmp489,
	strb	r2, [r4, #1]	@ tmp489, <variable>.IsCurrSegWaitDec
	b	.L263	@
.L222:
	ldrb	lr, [r0, #14]	@ zero_extendqisi2	@ <variable>.CurrSeg.IsStreamEnd, <variable>.CurrSeg.IsStreamEnd
	cmp	lr, #1	@ <variable>.CurrSeg.IsStreamEnd,
	movweq	r6, #:lower16:66944	@ tmp421,
	movteq	r6, #:upper16:66944	@ tmp421,
	beq	.L264	@,
	add	r6, r0, #88	@ temp.1304, pSegMan,
	mov	r2, #80	@,
	add	r1, r0, #8	@, pSegMan,
	mov	r0, r6	@, temp.1304
	bl	memcpy	@
	add	r0, r4, #168	@, pSegMan,
	mov	r1, #80	@,
	bl	__memzero	@
	mov	r0, r5	@, pstCtx
	mov	r1, r6	@, temp.1304
	bl	DIVX3DEC_Decode	@
	ldr	r8, [r5, #4]	@ <variable>.pDivx3DecParam, <variable>.pDivx3DecParam
	cmp	r8, #0	@ <variable>.pDivx3DecParam,
	bne	.L263	@,
	movw	r7, #:lower16:66944	@ tmp433,
	movt	r7, #:upper16:66944	@ tmp433,
.L272:
	mov	r0, r6	@, temp.1304
	mov	r1, #160	@,
	bl	__memzero	@
	ldr	r1, [r4, #24]	@, <variable>.CurrSeg.StreamID
	ldr	r0, [r5, r7]	@,
	bl	SM_ReleaseStreamSeg	@
	movw	r2, #:lower16:g_event_report	@ tmp436,
	movt	r2, #:upper16:g_event_report	@ tmp436,
	ldr	ip, [r2, #0]	@ g_event_report.1310, g_event_report
	cmp	ip, #0	@ g_event_report.1310,
	beq	.L263	@,
	mov	r2, r8	@, <variable>.pDivx3DecParam
	ldr	r0, [r5, r7]	@,
	mov	r1, #113	@,
	mov	r3, r8	@, tmp2
	blx	ip	@ g_event_report.1310
	b	.L263	@
.L223:
	movw	r1, #16600	@ tmp365,
	mov	r0, r2	@, pstCtx
	ldr	r6, [r2, r1]	@ ChanID.1272, <variable>.ChanID
	bl	AVS_GetPacketState	@
	cmp	r0, #0	@,
	bne	.L253	@,
	movw	r3, #:lower16:s_pstVfmwChan	@ tmp366,
	movt	r3, #:upper16:s_pstVfmwChan	@ tmp366,
	ldr	r3, [r3, r6, asl #2]	@ temp.1273, s_pstVfmwChan
	ldr	r2, [r3, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r2, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	bne	.L254	@,
	ldr	lr, [r3, #1924]	@ <variable>.stSynExtraData.s32WaitFsFlag, <variable>.stSynExtraData.s32WaitFsFlag
	cmp	lr, #0	@ <variable>.stSynExtraData.s32WaitFsFlag,
	bne	.L253	@,
.L254:
	add	ip, r5, #16384	@, pstCtx,
	mov	r0, r5	@, pstCtx
	add	r1, ip, #56	@,,
	bl	AVSDEC_Decode	@
.L253:
	movw	r2, #16600	@ tmp371,
	mov	r1, r4	@, pSegMan
	ldr	r0, [r5, r2]	@, <variable>.ChanID
	bl	SegMan	@
	cmp	r0, #0	@,
	beq	.L283	@,
.L255:
	ldr	r4, [r5, #4]	@ <variable>.pAvsDecParam, <variable>.pAvsDecParam
	cmp	r4, #0	@ <variable>.pAvsDecParam,
	bne	.L263	@,
	movw	r6, #17116	@ tmp375,
	ldrb	r0, [r5, r6]	@ zero_extendqisi2	@ <variable>.IsStreamEndFlag, <variable>.IsStreamEndFlag
	cmp	r0, #1	@ <variable>.IsStreamEndFlag,
	bne	.L263	@,
	movw	r1, #16600	@ tmp377,
	ldr	r0, [r5, r1]	@,
	bl	VCTRL_OutputLastFrame	@
	strb	r4, [r5, r6]	@ <variable>.pAvsDecParam,
	b	.L263	@
.L224:
	ldrb	r6, [r0, #14]	@ zero_extendqisi2	@ <variable>.CurrSeg.IsStreamEnd, <variable>.CurrSeg.IsStreamEnd
	cmp	r6, #1	@ <variable>.CurrSeg.IsStreamEnd,
	beq	.L284	@,
	add	r6, r0, #88	@ temp.1282, pSegMan,
	mov	r2, #80	@,
	add	r1, r0, #8	@, pSegMan,
	mov	r0, r6	@, temp.1282
	bl	memcpy	@
	add	r0, r4, #168	@, pSegMan,
	mov	r1, #80	@,
	bl	__memzero	@
	mov	r0, r5	@, pstCtx
	mov	r1, r6	@, temp.1282
	bl	REAL8DEC_Decode	@
	ldr	r8, [r5, #4]	@ <variable>.pRv8DecParam, <variable>.pRv8DecParam
	cmp	r8, #0	@ <variable>.pRv8DecParam,
	movweq	r7, #:lower16:79272	@ tmp395,
	movteq	r7, #:upper16:79272	@ tmp395,
	bne	.L263	@,
	b	.L272	@
.L225:
	ldrb	r3, [r0, #14]	@ zero_extendqisi2	@ <variable>.CurrSeg.IsStreamEnd, <variable>.CurrSeg.IsStreamEnd
	cmp	r3, #1	@ <variable>.CurrSeg.IsStreamEnd,
	movweq	r6, #:lower16:79256	@ tmp402,
	movteq	r6, #:upper16:79256	@ tmp402,
	beq	.L264	@,
	add	r6, r0, #88	@ temp.1293, pSegMan,
	mov	r2, #80	@,
	add	r1, r0, #8	@, pSegMan,
	mov	r0, r6	@, temp.1293
	bl	memcpy	@
	add	r0, r4, #168	@, pSegMan,
	mov	r1, #80	@,
	bl	__memzero	@
	mov	r0, r5	@, pstCtx
	mov	r1, r6	@, temp.1293
	bl	REAL9DEC_Decode	@
	ldr	r8, [r5, #4]	@ <variable>.pRv9DecParam, <variable>.pRv9DecParam
	cmp	r8, #0	@ <variable>.pRv9DecParam,
	movweq	r7, #:lower16:79256	@ tmp414,
	movteq	r7, #:upper16:79256	@ tmp414,
	bne	.L263	@,
	b	.L272	@
.L226:
	ldrb	r0, [r0, #14]	@ zero_extendqisi2	@ <variable>.CurrSeg.IsStreamEnd, <variable>.CurrSeg.IsStreamEnd
	cmp	r0, #1	@ <variable>.CurrSeg.IsStreamEnd,
	movweq	r6, #13000	@ tmp459,
	beq	.L264	@,
	add	r6, r4, #88	@ temp.1326, pSegMan,
	mov	r2, #80	@,
	add	r1, r4, #8	@, pSegMan,
	mov	r0, r6	@, temp.1326
	bl	memcpy	@
	add	r0, r4, #168	@, pSegMan,
	mov	r1, #80	@,
	bl	__memzero	@
	mov	r0, r5	@, pstCtx
	mov	r1, r6	@, temp.1326
	bl	VP6DEC_Decode	@
	ldr	r7, [r5, #4]	@ <variable>.pVp6DecParam, <variable>.pVp6DecParam
	cmp	r7, #0	@ <variable>.pVp6DecParam,
	bne	.L263	@,
	mov	r0, r6	@, temp.1326
	mov	r1, #160	@,
	movw	r6, #13000	@ tmp471,
.L275:
	bl	__memzero	@
	ldr	r1, [r4, #24]	@, <variable>.CurrSeg.StreamID
	ldr	r0, [r5, r6]	@,
	bl	SM_ReleaseStreamSeg	@
	movw	r1, #:lower16:g_event_report	@ tmp474,
	movt	r1, #:upper16:g_event_report	@ tmp474,
	ldr	ip, [r1, #0]	@ g_event_report.1332, g_event_report
	cmp	ip, #0	@ g_event_report.1332,
	beq	.L263	@,
	mov	r2, r7	@, <variable>.pVp6DecParam
	ldr	r0, [r5, r6]	@,
	mov	r1, #113	@,
	mov	r3, r7	@, tmp2
	blx	ip	@ g_event_report.1332
	b	.L263	@
.L227:
	ldrb	ip, [r0, #14]	@ zero_extendqisi2	@ <variable>.CurrSeg.IsStreamEnd, <variable>.CurrSeg.IsStreamEnd
	cmp	ip, #1	@ <variable>.CurrSeg.IsStreamEnd,
	movweq	r6, #8520	@ tmp440,
	beq	.L264	@,
	add	r6, r0, #88	@ temp.1315, pSegMan,
	mov	r2, #80	@,
	add	r1, r0, #8	@, pSegMan,
	mov	r0, r6	@, temp.1315
	bl	memcpy	@
	add	r0, r4, #168	@, pSegMan,
	mov	r1, #80	@,
	bl	__memzero	@
	mov	r1, r6	@, temp.1315
	mov	r0, r5	@, pstCtx
	bl	VP8DEC_Decode	@
	ldr	r7, [r5, #4]	@ <variable>.pVp8DecParam, <variable>.pVp8DecParam
	cmp	r7, #0	@ <variable>.pVp8DecParam,
	moveq	r0, r6	@, temp.1315
	moveq	r1, #160	@,
	movweq	r6, #8520	@ tmp452,
	bne	.L263	@,
	b	.L275	@
.L228:
	ldr	r3, [r4, #24]	@ <variable>.CurrSeg.StreamID, <variable>.CurrSeg.StreamID
	sub	r1, fp, #132	@,,
	ldrd	r8, [r0, #32]	@ <variable>.CurrSeg.Pts, pSegMan,
	mov	r0, r2	@, pstCtx
	ldr	r6, [r4, #8]	@ <variable>.CurrSeg.VirAddr, <variable>.CurrSeg.VirAddr
	ldr	lr, [r4, #16]	@ <variable>.CurrSeg.PhyAddr, <variable>.CurrSeg.PhyAddr
	ldr	ip, [r4, #20]	@ <variable>.CurrSeg.LenInByte, <variable>.CurrSeg.LenInByte
	ldrb	r2, [r4, #13]	@ zero_extendqisi2	@ <variable>.CurrSeg.IsLastSeg, <variable>.CurrSeg.IsLastSeg
	str	r3, [fp, #-116]	@ <variable>.CurrSeg.StreamID, MvcPack.StreamID
	strd	r8, [fp, #-108]	@ <variable>.CurrSeg.Pts,,
	str	r6, [fp, #-128]	@ <variable>.CurrSeg.VirAddr, MvcPack.p_stream
	str	lr, [fp, #-124]	@ <variable>.CurrSeg.PhyAddr, MvcPack.strm_phy_addr
	str	ip, [fp, #-120]	@ <variable>.CurrSeg.LenInByte, MvcPack.stream_len
	strb	r2, [fp, #-132]	@ <variable>.CurrSeg.IsLastSeg, MvcPack.last_pack_in_nal
	bl	MVC_DEC_DecodePacket	@
	cmn	r0, #2	@,
	moveq	r3, #1	@ tmp249,
	movne	r3, #0	@ tmp251,
	strb	r3, [r4, #1]	@ tmp251, <variable>.IsCurrSegWaitDec
	ldr	r4, [r5, #228]	@ <variable>.pMvcDecParam, <variable>.pMvcDecParam
	cmp	r4, #0	@ <variable>.pMvcDecParam,
	bne	.L263	@,
	ldrb	r1, [r5, #1]	@ zero_extendqisi2	@ <variable>.IsStreamEndFlag, <variable>.IsStreamEndFlag
	cmp	r1, #1	@ <variable>.IsStreamEndFlag,
	bne	.L263	@,
	ldr	r0, [r5, #120]	@, <variable>.ChanID
	bl	VCTRL_OutputLastFrame	@
	strb	r4, [r5, #1]	@ <variable>.pMvcDecParam, <variable>.IsStreamEndFlag
	b	.L263	@
.L284:
	movw	r6, #:lower16:79272	@ tmp383,
	movt	r6, #:upper16:79272	@ tmp383,
.L264:
	ldr	r0, [r5, r6]	@,
	bl	VCTRL_OutputLastFrame	@
	ldr	r0, [r5, r6]	@,
	ldr	r1, [r4, #24]	@, <variable>.CurrSeg.StreamID
	bl	SM_ReleaseStreamSeg	@
	b	.L263	@
.L276:
	movw	r1, #:lower16:.LC19	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC19	@,
	bl	dprint_vfmw	@
	b	.L263	@
.L283:
	add	r1, r4, #88	@, pSegMan,
	mov	r0, r5	@, pstCtx
	bl	AVSDEC_Decode	@
	b	.L255	@
.L282:
	add	r1, r4, #88	@, pSegMan,
	mov	r0, r5	@, pstCtx
	bl	MPEG2DEC_Decode	@
	movw	r3, #:lower16:113665	@ tmp334,
	movt	r3, #:upper16:113665	@ tmp334,
	ldrb	r1, [r5, r3]	@ zero_extendqisi2	@ <variable>.IsWaitToReRange, <variable>.IsWaitToReRange
	cmp	r1, #1	@ <variable>.IsWaitToReRange,
	strneb	r6, [r4, #1]	@ ret.1262, <variable>.IsCurrSegWaitDec
	streqb	r1, [r4, #1]	@ <variable>.IsWaitToReRange, <variable>.IsCurrSegWaitDec
	b	.L248	@
.L280:
	add	r1, r4, #88	@, pSegMan,
	mov	r0, r5	@, pstCtx
	bl	MPEG4DEC_Decode	@
	b	.L252	@
.L281:
	movw	r0, #:lower16:s_pstVfmwChan	@ tmp326,
	movt	r0, #:upper16:s_pstVfmwChan	@ tmp326,
	ldr	r3, [r0, r6, asl #2]	@ temp.1259, s_pstVfmwChan
	ldr	r6, [r3, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r6, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	bne	.L247	@,
	ldr	r2, [r3, #1924]	@ <variable>.stSynExtraData.s32WaitFsFlag, <variable>.stSynExtraData.s32WaitFsFlag
	cmp	r2, #0	@ <variable>.stSynExtraData.s32WaitFsFlag,
	bne	.L246	@,
.L247:
	add	lr, r5, #78848	@, pstCtx,
	mov	r0, r5	@, pstCtx
	add	r1, lr, #608	@,,
	bl	MPEG2DEC_Decode	@
	b	.L246	@
.L279:
	movw	r1, #:lower16:s_pstVfmwChan	@ tmp349,
	movt	r1, #:upper16:s_pstVfmwChan	@ tmp349,
	ldr	r3, [r1, r6, asl #2]	@ temp.1266, s_pstVfmwChan
	ldr	ip, [r3, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	ip, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	bne	.L251	@,
	ldr	r3, [r3, #1924]	@ <variable>.stSynExtraData.s32WaitFsFlag, <variable>.stSynExtraData.s32WaitFsFlag
	cmp	r3, #0	@ <variable>.stSynExtraData.s32WaitFsFlag,
	bne	.L250	@,
.L251:
	add	r2, r5, #15680	@, pstCtx,
	mov	r0, r5	@, pstCtx
	add	r1, r2, #24	@,,
	bl	MPEG4DEC_Decode	@
	b	.L250	@
.L244:
	add	r2, r5, #80896	@, pstCtx,
	ldr	r0, [r4, #88]	@, <variable>.VirAddr
	add	r2, r2, #448	@,,
	mov	r1, #16	@,
	bl	Vc1SMPSeqHdr	@
	cmp	r0, #0	@,
	beq	.L285	@,
	movw	r6, #:lower16:114320	@ tmp319,
	movw	r1, #:lower16:.LC22	@,
	movt	r6, #:upper16:114320	@ tmp319,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC22	@,
	b	.L270	@
.L277:
	movw	r1, #:lower16:.LC20	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC20	@,
	bl	dprint_vfmw	@
	b	.L263	@
.L278:
	movw	r1, #:lower16:114320	@ tmp274,
	movt	r1, #:upper16:114320	@ tmp274,
	mov	r0, r5	@, pstCtx
	ldr	r6, [r5, r1]	@ ChanID, <variable>.ChanID
	bl	VC1_GetPacketState	@
	cmp	r0, #2	@,
	beq	.L286	@,
.L240:
	movw	lr, #:lower16:114320	@ tmp280,
	movt	lr, #:upper16:114320	@ tmp280,
	mov	r1, r4	@, pSegMan
	ldr	r0, [r5, lr]	@, <variable>.ChanID
	bl	SegMan	@
	cmp	r0, #0	@,
	beq	.L287	@,
.L242:
	ldr	r4, [r5, #4]	@ <variable>.pVc1DecParam, <variable>.pVc1DecParam
	cmp	r4, #0	@ <variable>.pVc1DecParam,
	bne	.L263	@,
	movw	r6, #:lower16:78255	@ tmp283,
	movt	r6, #:upper16:78255	@ tmp283,
	ldrb	r1, [r5, r6]	@ zero_extendqisi2	@ <variable>.CodecInfo.IsStreamEndFlag, <variable>.CodecInfo.IsStreamEndFlag
	cmp	r1, #1	@ <variable>.CodecInfo.IsStreamEndFlag,
	bne	.L263	@,
	movw	ip, #:lower16:114320	@ tmp285,
	movt	ip, #:upper16:114320	@ tmp285,
	ldr	r0, [r5, ip]	@,
	bl	VCTRL_OutputLastFrame	@
	strb	r4, [r5, r6]	@ <variable>.pVc1DecParam,
	b	.L263	@
.L285:
	ldr	ip, [r4, #100]	@ <variable>.LenInByte, <variable>.LenInByte
	mov	r1, r6	@, D.39244
	ldr	r2, [r4, #88]	@ <variable>.VirAddr, <variable>.VirAddr
	mov	r0, r5	@, pstCtx
	ldr	r3, [r4, #96]	@ <variable>.PhyAddr, <variable>.PhyAddr
	sub	lr, ip, #16	@ tmp313, <variable>.LenInByte,
	add	ip, r2, #16	@ tmp315, <variable>.VirAddr,
	str	lr, [r4, #100]	@ tmp313, <variable>.LenInByte
	str	ip, [r4, #88]	@ tmp315, <variable>.VirAddr
	add	lr, r3, #16	@ tmp317, <variable>.PhyAddr,
	str	lr, [r4, #96]	@ tmp317, <variable>.PhyAddr
	bl	VC1DEC_Decode	@
	mov	r0, r6	@, D.39244
	mov	r1, #160	@,
	bl	__memzero	@
	b	.L263	@
.L287:
	add	r4, r4, #88	@ D.39228, pSegMan,
	mov	r0, r5	@, pstCtx
	mov	r1, r4	@, D.39228
	bl	VC1DEC_Decode	@
	mov	r0, r4	@, D.39228
	mov	r1, #160	@,
	bl	__memzero	@
	b	.L242	@
.L286:
	movw	ip, #:lower16:s_pstVfmwChan	@ tmp275,
	movt	ip, #:upper16:s_pstVfmwChan	@ tmp275,
	ldr	r3, [ip, r6, asl #2]	@ D.39218, s_pstVfmwChan
	ldr	r0, [r3, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r0, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	bne	.L241	@,
	ldr	r3, [r3, #1924]	@ <variable>.stSynExtraData.s32WaitFsFlag, <variable>.stSynExtraData.s32WaitFsFlag
	cmp	r3, #0	@ <variable>.stSynExtraData.s32WaitFsFlag,
	bne	.L240	@,
.L241:
	add	r2, r5, #77824	@, pstCtx,
	mov	r0, r5	@, pstCtx
	add	r1, r2, #264	@,,
	bl	VC1DEC_Decode	@
	b	.L240	@
	.fnend
	.size	DecodeStream, .-DecodeStream
	.align	2
	.global	SYNTAX_ReturnImage
	.type	SYNTAX_ReturnImage, %function
SYNTAX_ReturnImage:
	.fnstart
.LFB1537:
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
	ldr	r3, [r0, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #18	@ <variable>.eVidStd,
	ldrls	pc, [pc, r3, asl #2]	@ <variable>.eVidStd
	b	.L289	@
.L304:
	.word	.L303
	.word	.L291
	.word	.L292
	.word	.L293
	.word	.L294
	.word	.L295
	.word	.L296
	.word	.L289
	.word	.L297
	.word	.L298
	.word	.L299
	.word	.L299
	.word	.L299
	.word	.L300
	.word	.L294
	.word	.L301
	.word	.L302
	.word	.L289
	.word	.L303
.L303:
	add	r4, r0, #16	@ pstVoQue, pSynCtx,
.L306:
	ldr	r0, .L308	@,
	bl	OSAL_SpinLockIRQ	@
	ldrh	r2, [r4, #6]	@ <variable>.head, <variable>.head
	ldr	r0, .L308	@,
	sub	r1, r2, #1	@ tmp153, <variable>.head,
	and	r3, r1, #63	@ tmp155, tmp153,
	strh	r3, [r4, #6]	@ movhi	@ tmp155, <variable>.head
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, #1	@ D.39076,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L291:
	add	lr, r0, #113664	@ pstVoQue, pSynCtx,
	add	r4, lr, #312	@ pstVoQue, pstVoQue,
	b	.L306	@
.L292:
	add	r2, r0, #22528	@ pstVoQue, pSynCtx,
	add	r4, r2, #88	@ pstVoQue, pstVoQue,
	b	.L306	@
.L293:
	add	r1, r0, #79872	@ pstVoQue, pSynCtx,
	add	r4, r1, #136	@ pstVoQue, pstVoQue,
	b	.L306	@
.L294:
	add	lr, r0, #25344	@ pstVoQue, pSynCtx,
	add	r4, lr, #144	@ pstVoQue, pstVoQue,
	b	.L306	@
.L295:
	add	r1, r0, #33280	@ pstVoQue, pSynCtx,
	add	r4, r1, #24	@ pstVoQue, pstVoQue,
	b	.L306	@
.L296:
	add	ip, r0, #16064	@ pstVoQue, pSynCtx,
	add	r4, ip, #24	@ pstVoQue, pstVoQue,
	b	.L306	@
.L297:
	add	r3, r0, #45568	@ pstVoQue, pSynCtx,
	add	r4, r3, #64	@ pstVoQue, pstVoQue,
	b	.L306	@
.L298:
	add	r4, r0, #45568	@ pstVoQue, pSynCtx,
	add	r4, r4, #48	@ pstVoQue, pstVoQue,
	b	.L306	@
.L299:
	add	ip, r0, #12608	@ pstVoQue, pSynCtx,
	add	r4, ip, #48	@ pstVoQue, pstVoQue,
	b	.L306	@
.L300:
	add	r2, r0, #8128	@ pstVoQue, pSynCtx,
	add	r4, r2, #48	@ pstVoQue, pstVoQue,
	b	.L306	@
.L301:
	add	r4, r0, #592	@ pstVoQue, pSynCtx,
	b	.L306	@
.L302:
	add	r4, r0, #2129920	@ pstVoQue, pSynCtx,
	add	r4, r4, #2816	@ pstVoQue, pstVoQue,
	b	.L306	@
.L289:
	mvn	r0, #1	@ D.39076,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L309:
	.align	2
.L308:
	.word	.LANCHOR0+64
	.fnend
	.size	SYNTAX_ReturnImage, .-SYNTAX_ReturnImage
	.align	2
	.global	SYNTAX_ReceiveImage
	.type	SYNTAX_ReceiveImage, %function
SYNTAX_ReceiveImage:
	.fnstart
.LFB1535:
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
	cmp	r0, #0	@ pSynCtx,
	cmpne	r1, #0	@, p_image,
	mov	r4, r1	@ p_image, p_image
	bne	.L332	@,
.L311:
	mvn	r5, #1	@ ret,
.L330:
	mov	r0, r5	@, ret
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L332:
	ldr	r3, [r0, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #18	@ <variable>.eVidStd,
	ldrls	pc, [pc, r3, asl #2]	@ <variable>.eVidStd
	b	.L311	@
.L326:
	.word	.L325
	.word	.L313
	.word	.L314
	.word	.L315
	.word	.L316
	.word	.L317
	.word	.L318
	.word	.L311
	.word	.L319
	.word	.L320
	.word	.L321
	.word	.L321
	.word	.L321
	.word	.L322
	.word	.L316
	.word	.L323
	.word	.L324
	.word	.L311
	.word	.L325
.L325:
	add	r6, r0, #16	@ pstVoQue, pSynCtx,
.L327:
	ldr	r0, .L333	@,
	bl	OSAL_SpinLockIRQ	@
	ldrh	r3, [r6, #6]	@ D.38855, <variable>.head
	ldrh	r0, [r6, #8]	@ <variable>.tail, <variable>.tail
	cmp	r0, r3	@ <variable>.tail, D.38855
	mvneq	r5, #2	@ ret,
	beq	.L329	@,
	add	lr, r6, r3, asl #2	@, tmp164, pstVoQue, D.38855,
	mov	r2, #496	@,
	mov	r0, r4	@, p_image
	mov	r5, #1	@ ret,
	ldr	r1, [lr, #12]	@, <variable>.image_ptr
	bl	memcpy	@
	ldrh	ip, [r6, #8]	@ <variable>.tail, <variable>.tail
	ldrh	r2, [r6, #4]	@ <variable>.history, <variable>.history
	mov	r0, #12	@,
	ldrh	r3, [r6, #6]	@ <variable>.head, <variable>.head
	movw	r1, #:lower16:.LC23	@,
	str	ip, [sp, #0]	@ <variable>.tail,
	movt	r1, #:upper16:.LC23	@,
	ldr	ip, [r4, #196]	@ <variable>.image_id, <variable>.image_id
	str	ip, [sp, #4]	@ <variable>.image_id,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #196]	@ <variable>.image_id, <variable>.image_id
	ldr	r0, [r6, #344]	@ <variable>.ResetMagicWord, <variable>.ResetMagicWord
	add	ip, r3, r0	@ tmp178, <variable>.image_id, <variable>.ResetMagicWord
	str	ip, [r4, #196]	@ tmp178, <variable>.image_id
	ldrh	r2, [r6, #6]	@ <variable>.head, <variable>.head
	add	r1, r2, r5	@ tmp181, <variable>.head,
	and	r3, r1, #63	@ tmp183, tmp181,
	strh	r3, [r6, #6]	@ movhi	@ tmp183, <variable>.head
.L329:
	ldr	r0, .L333	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L330	@
.L324:
	add	r6, r0, #2129920	@ pstVoQue, pSynCtx,
	add	r6, r6, #2816	@ pstVoQue, pstVoQue,
	b	.L327	@
.L323:
	add	r6, r0, #592	@ pstVoQue, pSynCtx,
	b	.L327	@
.L322:
	add	r2, r0, #8128	@ pstVoQue, pSynCtx,
	add	r6, r2, #48	@ pstVoQue, pstVoQue,
	b	.L327	@
.L321:
	add	ip, r0, #12608	@ pstVoQue, pSynCtx,
	add	r6, ip, #48	@ pstVoQue, pstVoQue,
	b	.L327	@
.L320:
	add	r6, r0, #45568	@ pstVoQue, pSynCtx,
	add	r6, r6, #48	@ pstVoQue, pstVoQue,
	b	.L327	@
.L319:
	add	r3, r0, #45568	@ pstVoQue, pSynCtx,
	add	r6, r3, #64	@ pstVoQue, pstVoQue,
	b	.L327	@
.L318:
	add	ip, r0, #16064	@ pstVoQue, pSynCtx,
	add	r6, ip, #24	@ pstVoQue, pstVoQue,
	b	.L327	@
.L317:
	add	r1, r0, #33280	@ pstVoQue, pSynCtx,
	add	r6, r1, #24	@ pstVoQue, pstVoQue,
	b	.L327	@
.L316:
	add	lr, r0, #25344	@ pstVoQue, pSynCtx,
	add	r6, lr, #144	@ pstVoQue, pstVoQue,
	b	.L327	@
.L315:
	add	r1, r0, #79872	@ pstVoQue, pSynCtx,
	add	r6, r1, #136	@ pstVoQue, pstVoQue,
	b	.L327	@
.L314:
	add	r2, r0, #22528	@ pstVoQue, pSynCtx,
	add	r6, r2, #88	@ pstVoQue, pstVoQue,
	b	.L327	@
.L313:
	add	lr, r0, #113664	@ pstVoQue, pSynCtx,
	add	r6, lr, #312	@ pstVoQue, pstVoQue,
	b	.L327	@
.L334:
	.align	2
.L333:
	.word	.LANCHOR0+64
	.fnend
	.size	SYNTAX_ReceiveImage, .-SYNTAX_ReceiveImage
	.align	2
	.global	ResetVoQueue
	.type	ResetVoQueue, %function
ResetVoQueue:
	.fnstart
.LFB1530:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #12
	sub	sp, sp, #12	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r4, r0	@ pstVoQue, pstVoQue
	ldr	r0, .L341	@,
	bl	OSAL_SpinLockIRQ	@
	ldrh	r2, [r4, #6]	@ D.38561, <variable>.head
	ldrh	r3, [r4, #4]	@ D.38562, <variable>.history
	cmp	r2, r3	@ D.38561, D.38562
	ldrneh	ip, [r4, #8]	@ prephitmp.1404, <variable>.tail
	beq	.L340	@,
.L337:
	movw	r1, #:lower16:.LC24	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC24	@,
	str	ip, [sp, #0]	@ prephitmp.1404,
	bl	dprint_vfmw	@
.L338:
	ldr	r7, [r4, #344]	@ <variable>.ResetMagicWord, <variable>.ResetMagicWord
	mov	r0, #328	@ tmp159,
	mov	r1, #336	@ tmp162,
	mov	r3, #0	@ tmp143,
	mvn	r2, #0	@ tmp152,
	add	r6, r7, #100	@ tmp151, <variable>.ResetMagicWord,
	mov	ip, #64	@ movhi	@,
	str	r6, [r4, #344]	@ tmp151, <variable>.ResetMagicWord
	mvn	r7, #0	@,
	mvn	r6, #0	@ tmp160,
	strh	ip, [r4, #0]	@ movhi	@, <variable>.max_queue_size
	strd	r6, [r4, r0]	@ tmp160, pstVoQue, tmp159
	mov	r6, #0	@ tmp163,
	mov	r7, #0	@,
	str	r3, [r4, #324]	@ tmp143, <variable>.SideInfo.PrevNumFramesBtwPTS
	strh	r3, [r4, #2]	@ movhi	@ tmp143, <variable>.queue_size
	str	r2, [r4, #280]	@ tmp152, <variable>.SideInfo.OldSeqCnt
	strd	r6, [r4, r1]	@ tmp163, pstVoQue, tmp162
	strh	r3, [r4, #4]	@ movhi	@ tmp143, <variable>.history
	strh	r3, [r4, #6]	@ movhi	@ tmp143, <variable>.head
	strh	r3, [r4, #8]	@ movhi	@ tmp143, <variable>.tail
	str	r2, [r4, #272]	@ tmp152, <variable>.SideInfo.OldAspectRatio
	str	r2, [r4, #292]	@ tmp152, <variable>.SideInfo.OldDispCenter
	str	r2, [r4, #288]	@ tmp152, <variable>.SideInfo.OldDispSize
	str	r2, [r4, #284]	@ tmp152, <variable>.SideInfo.OldFrameRate
	str	r2, [r4, #276]	@ tmp152, <variable>.SideInfo.OldScanType
	str	r3, [r4, #316]	@ tmp143, <variable>.SideInfo.SeqImgCnt
	ldr	r0, .L341	@,
	bl	OSAL_SpinUnLockIRQ	@
	sub	sp, fp, #24
	ldmfd	sp, {r4, r6, r7, fp, sp, pc}
.L340:
	ldrh	ip, [r4, #8]	@ prephitmp.1404, <variable>.tail
	cmp	r2, ip	@ D.38561, prephitmp.1404
	bne	.L337	@,
	b	.L338	@
.L342:
	.align	2
.L341:
	.word	.LANCHOR0+64
	.fnend
	.size	ResetVoQueue, .-ResetVoQueue
	.align	2
	.global	SYNTAX_ReleaseImage
	.type	SYNTAX_ReleaseImage, %function
SYNTAX_ReleaseImage:
	.fnstart
.LFB1536:
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
	subs	r4, r1, #0	@ p_image, p_image
	mov	r5, r0	@ pSynCtx, pSynCtx
	beq	.L407	@,
	ldr	r3, [r0, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #18	@ <variable>.eVidStd,
	ldrls	pc, [pc, r3, asl #2]	@ <variable>.eVidStd
	b	.L346	@
.L361:
	.word	.L360
	.word	.L348
	.word	.L349
	.word	.L350
	.word	.L351
	.word	.L352
	.word	.L353
	.word	.L346
	.word	.L354
	.word	.L355
	.word	.L356
	.word	.L356
	.word	.L356
	.word	.L357
	.word	.L351
	.word	.L358
	.word	.L359
	.word	.L346
	.word	.L360
.L360:
	add	r7, r0, #16	@ pstVoQue, pSynCtx,
.L362:
	ldr	r0, .L409	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r2, [r4, #196]	@ <variable>.image_id, <variable>.image_id
	ldr	ip, [r7, #344]	@ <variable>.ResetMagicWord, <variable>.ResetMagicWord
	rsb	r2, ip, r2	@ prephitmp.1431, <variable>.ResetMagicWord, <variable>.image_id
	str	r2, [r4, #196]	@ prephitmp.1431, <variable>.image_id
	ldrh	r6, [r7, #4]	@ i.1443, <variable>.history
	ldrh	r3, [r7, #6]	@ <variable>.head, <variable>.head
	and	r6, r6, #63	@ i, i.1443,
	cmp	r3, r6	@ <variable>.head, i
	bne	.L393	@,
	b	.L390	@
.L367:
	add	r6, r6, #1	@ i.1469, i,
	and	r6, r6, #63	@ i, i.1469,
	cmp	r3, r6	@ <variable>.head, i
	beq	.L408	@,
.L393:
	add	r8, r6, #2	@ tmp219, i,
	add	lr, r7, r8, asl #2	@, tmp177, pstVoQue, tmp219,
	ldr	r2, [lr, #4]	@ D.38937, <variable>.image_ptr
	cmp	r2, #0	@ D.38937,
	beq	.L365	@,
	ldr	r1, [r2, #196]	@ <variable>.image_id, <variable>.image_id
	ldr	r0, [r4, #196]	@ <variable>.image_id, <variable>.image_id
	cmp	r0, r1	@ <variable>.image_id, <variable>.image_id
	bne	.L367	@,
	mov	sl, #1	@ SameImageFlag,
.L368:
	ldrh	lr, [r7, #4]	@ temp.1445, <variable>.history
	b	.L391	@
.L371:
	mov	r6, r2	@ i, j
.L391:
	cmp	r6, #0	@ i,
	sub	r2, r6, #1	@ j, i,
	add	r0, r7, r8, asl #2	@, tmp185, pstVoQue, tmp219,
	moveq	r2, #63	@ j,
	add	r1, r2, #2	@ tmp187, j,
	cmp	lr, r6	@ temp.1445, i
	add	ip, r7, r1, asl #2	@, tmp190, pstVoQue, tmp187,
	mov	r8, r1	@ tmp219, tmp187
	ldr	r1, [ip, #4]	@ tmp192, <variable>.image_ptr
	str	r1, [r0, #4]	@ tmp192, <variable>.image_ptr
	bne	.L371	@,
	cmp	sl, #1	@ SameImageFlag,
	add	lr, lr, #1	@ tmp193, temp.1445,
	and	r2, lr, #63	@ D.38930, tmp193,
	strh	r2, [r7, #4]	@ movhi	@ D.38930, <variable>.history
	bne	.L367	@,
	ldrh	lr, [r7, #8]	@ <variable>.tail, <variable>.tail
	mov	r0, #12	@,
	movw	r1, #:lower16:.LC28	@,
	movt	r1, #:upper16:.LC28	@,
	str	lr, [sp, #0]	@ <variable>.tail,
	ldr	ip, [r4, #196]	@ <variable>.image_id, <variable>.image_id
	str	ip, [sp, #4]	@ <variable>.image_id,
	bl	dprint_vfmw	@
	ldr	r3, [r5, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #18	@ <variable>.eVidStd,
	ldrls	pc, [pc, r3, asl #2]	@ <variable>.eVidStd
	b	.L372	@
.L387:
	.word	.L373
	.word	.L374
	.word	.L375
	.word	.L376
	.word	.L377
	.word	.L378
	.word	.L379
	.word	.L372
	.word	.L380
	.word	.L381
	.word	.L382
	.word	.L382
	.word	.L382
	.word	.L383
	.word	.L377
	.word	.L384
	.word	.L385
	.word	.L372
	.word	.L386
.L348:
	add	r6, r0, #113664	@ pstVoQue, pSynCtx,
	add	r7, r6, #312	@ pstVoQue, pstVoQue,
	b	.L362	@
.L349:
	add	r1, r0, #22528	@ pstVoQue, pSynCtx,
	add	r7, r1, #88	@ pstVoQue, pstVoQue,
	b	.L362	@
.L350:
	add	r0, r0, #79872	@ pstVoQue, pSynCtx,
	add	r7, r0, #136	@ pstVoQue, pstVoQue,
	b	.L362	@
.L351:
	add	r1, r0, #25344	@ pstVoQue, pSynCtx,
	add	r7, r1, #144	@ pstVoQue, pstVoQue,
	b	.L362	@
.L352:
	add	r3, r0, #33280	@ pstVoQue, pSynCtx,
	add	r7, r3, #24	@ pstVoQue, pstVoQue,
	b	.L362	@
.L353:
	add	r2, r0, #16064	@ pstVoQue, pSynCtx,
	add	r7, r2, #24	@ pstVoQue, pstVoQue,
	b	.L362	@
.L354:
	add	ip, r0, #45568	@ pstVoQue, pSynCtx,
	add	r7, ip, #64	@ pstVoQue, pstVoQue,
	b	.L362	@
.L355:
	add	lr, r0, #45568	@ pstVoQue, pSynCtx,
	add	r7, lr, #48	@ pstVoQue, pstVoQue,
	b	.L362	@
.L356:
	add	r0, r0, #12608	@ pstVoQue, pSynCtx,
	add	r7, r0, #48	@ pstVoQue, pstVoQue,
	b	.L362	@
.L357:
	add	r7, r0, #8128	@ pstVoQue, pSynCtx,
	add	r7, r7, #48	@ pstVoQue, pstVoQue,
	b	.L362	@
.L358:
	add	r7, r0, #592	@ pstVoQue, pSynCtx,
	b	.L362	@
.L359:
	add	r7, r0, #2129920	@ pstVoQue, pSynCtx,
	add	r7, r7, #2816	@ pstVoQue, pstVoQue,
	b	.L362	@
.L346:
	mvn	r4, #1	@ ret,
.L345:
	mov	r0, r4	@, ret
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L365:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC27	@,
	mov	r2, r6	@, i
	movt	r1, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	mov	sl, #2	@ SameImageFlag,
	ldrh	r3, [r7, #6]	@ <variable>.head, <variable>.head
	b	.L368	@
.L408:
	ldr	r2, [r4, #196]	@ prephitmp.1431, <variable>.image_id
.L390:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC26	@,
	movt	r1, #:upper16:.LC26	@,
	mvn	r4, #1	@ ret,
	bl	dprint_vfmw	@
.L364:
	ldr	r0, .L409	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L345	@
.L407:
	mov	r0, r4	@, p_image
	movw	r1, #:lower16:.LC25	@,
	movt	r1, #:upper16:.LC25	@,
	mvn	r4, #1	@ ret,
	bl	dprint_vfmw	@
	b	.L345	@
.L386:
	ldr	r1, [r4, #196]	@, <variable>.image_id
	add	r0, r5, #8	@, pSynCtx,
	bl	USERDEC_RecycleImage	@
	cmp	r0, #1	@ ret,
	mov	r4, r0	@ ret,
	beq	.L364	@,
.L389:
	mvn	r4, #19	@ ret,
	b	.L364	@
.L385:
	add	r0, r5, #8	@, pSynCtx,
	ldr	r1, [r4, #196]	@, <variable>.image_id
	bl	HEVC_DECRecycleImage	@
	cmp	r0, #0	@,
	bne	.L389	@,
	mov	r4, #1	@ ret,
	b	.L364	@
.L384:
	add	r0, r5, #8	@, pSynCtx,
	ldr	r1, [r4, #196]	@, <variable>.image_id
	bl	MVC_DEC_RecycleImage	@
	cmp	r0, #0	@,
	bne	.L389	@,
	mov	r4, #1	@ ret,
	b	.L364	@
.L383:
	ldr	r1, [r4, #196]	@, <variable>.image_id
	add	r0, r5, #8	@, pSynCtx,
	bl	VP8DEC_RecycleImage	@
	cmp	r0, #1	@ ret,
	mov	r4, r0	@ ret,
	mvnne	r4, #19	@ ret,
	b	.L364	@
.L382:
	ldr	r1, [r4, #196]	@, <variable>.image_id
	add	r0, r5, #8	@, pSynCtx,
	bl	VP6DEC_RecycleImage	@
	cmp	r0, #1	@ ret,
	mov	r4, r0	@ ret,
	mvnne	r4, #19	@ ret,
	b	.L364	@
.L381:
	ldr	r1, [r4, #196]	@, <variable>.image_id
	add	r0, r5, #8	@, pSynCtx,
	bl	REAL9DEC_RecycleImage	@
	cmp	r0, #1	@ ret,
	mov	r4, r0	@ ret,
	mvnne	r4, #19	@ ret,
	b	.L364	@
.L380:
	ldr	r1, [r4, #196]	@, <variable>.image_id
	add	r0, r5, #8	@, pSynCtx,
	bl	REAL8DEC_RecycleImage	@
	cmp	r0, #1	@ ret,
	mov	r4, r0	@ ret,
	mvnne	r4, #19	@ ret,
	b	.L364	@
.L379:
	ldr	r1, [r4, #196]	@, <variable>.image_id
	add	r0, r5, #8	@, pSynCtx,
	bl	AVSDEC_RecycleImage	@
	cmp	r0, #1	@ ret,
	mov	r4, r0	@ ret,
	mvnne	r4, #19	@ ret,
	b	.L364	@
.L378:
	ldr	r1, [r4, #196]	@, <variable>.image_id
	add	r0, r5, #8	@, pSynCtx,
	bl	DIVX3DEC_RecycleImage	@
	cmp	r0, #1	@ ret,
	mov	r4, r0	@ ret,
	mvnne	r4, #19	@ ret,
	b	.L364	@
.L377:
	movw	r2, #:lower16:g_SdecFunc	@ tmp211,
	movt	r2, #:upper16:g_SdecFunc	@ tmp211,
	ldr	r3, [r2, #16]	@ D.39036, g_SdecFunc.pfun_iMediaSoftDEC_RecycleImage
	cmp	r3, #0	@ D.39036,
	beq	.L389	@,
	add	r0, r5, #8	@, pSynCtx,
	ldr	r1, [r4, #196]	@, <variable>.image_id
	blx	r3	@ D.39036
	cmp	r0, #0	@,
	bne	.L389	@,
	mov	r4, #1	@ ret,
	b	.L364	@
.L376:
	ldr	r1, [r4, #196]	@, <variable>.image_id
	add	r0, r5, #8	@, pSynCtx,
	bl	MPEG2DEC_RecycleImage	@
	cmp	r0, #1	@ ret,
	mov	r4, r0	@ ret,
	mvnne	r4, #19	@ ret,
	b	.L364	@
.L375:
	ldr	r1, [r4, #196]	@, <variable>.image_id
	add	r0, r5, #8	@, pSynCtx,
	bl	MPEG4DEC_RecycleImage	@
	cmp	r0, #1	@ ret,
	mov	r4, r0	@ ret,
	mvnne	r4, #19	@ ret,
	b	.L364	@
.L374:
	ldr	r1, [r4, #196]	@, <variable>.image_id
	add	r0, r5, #8	@, pSynCtx,
	bl	VC1DEC_RecycleImage	@
	cmp	r0, #1	@ ret,
	mov	r4, r0	@ ret,
	mvnne	r4, #19	@ ret,
	b	.L364	@
.L373:
	add	r0, r5, #8	@, pSynCtx,
	ldr	r1, [r4, #196]	@, <variable>.image_id
	bl	H264DEC_RecycleImage	@
	cmp	r0, #0	@,
	bne	.L389	@,
	mov	r4, #1	@ ret,
	b	.L364	@
.L372:
	mvn	r4, #1	@ ret,
	b	.L364	@
.L410:
	.align	2
.L409:
	.word	.LANCHOR0+64
	.fnend
	.size	SYNTAX_ReleaseImage, .-SYNTAX_ReleaseImage
	.align	2
	.global	ReturnImageToSyntax
	.type	ReturnImageToSyntax, %function
ReturnImageToSyntax:
	.fnstart
.LFB1531:
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
	cmp	r0, #18	@ eVidStd,
	ldrls	pc, [pc, r0, asl #2]	@ eVidStd
	b	.L428	@
.L427:
	.word	.L413
	.word	.L414
	.word	.L415
	.word	.L416
	.word	.L417
	.word	.L418
	.word	.L419
	.word	.L428
	.word	.L420
	.word	.L421
	.word	.L422
	.word	.L422
	.word	.L422
	.word	.L423
	.word	.L417
	.word	.L424
	.word	.L425
	.word	.L428
	.word	.L426
.L426:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	USERDEC_RecycleImage	@
.L428:
	ldmfd	sp, {fp, sp, pc}	@
.L413:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	H264DEC_RecycleImage	@
	ldmfd	sp, {fp, sp, pc}	@
.L414:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	VC1DEC_RecycleImage	@
	ldmfd	sp, {fp, sp, pc}	@
.L415:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	MPEG4DEC_RecycleImage	@
	ldmfd	sp, {fp, sp, pc}	@
.L416:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	MPEG2DEC_RecycleImage	@
	ldmfd	sp, {fp, sp, pc}	@
.L417:
	movw	r3, #:lower16:g_SdecFunc	@ tmp150,
	movt	r3, #:upper16:g_SdecFunc	@ tmp150,
	ldr	r3, [r3, #16]	@ D.38609, g_SdecFunc.pfun_iMediaSoftDEC_RecycleImage
	cmp	r3, #0	@ D.38609,
	ldmeqfd	sp, {fp, sp, pc}	@
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	blx	r3	@ D.38609
	ldmfd	sp, {fp, sp, pc}	@
.L418:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	DIVX3DEC_RecycleImage	@
	ldmfd	sp, {fp, sp, pc}	@
.L419:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	AVSDEC_RecycleImage	@
	ldmfd	sp, {fp, sp, pc}	@
.L420:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	REAL8DEC_RecycleImage	@
	ldmfd	sp, {fp, sp, pc}	@
.L421:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	REAL9DEC_RecycleImage	@
	ldmfd	sp, {fp, sp, pc}	@
.L422:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	VP6DEC_RecycleImage	@
	ldmfd	sp, {fp, sp, pc}	@
.L423:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	VP8DEC_RecycleImage	@
	ldmfd	sp, {fp, sp, pc}	@
.L424:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	MVC_DEC_RecycleImage	@
	ldmfd	sp, {fp, sp, pc}	@
.L425:
	mov	r0, r1	@, pCtx
	ldr	r1, [r2, #196]	@, <variable>.image_id
	bl	HEVC_DECRecycleImage	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	ReturnImageToSyntax, .-ReturnImageToSyntax
	.global	__aeabi_uidiv
	.align	2
	.global	InsertImgToVoQueue
	.type	InsertImgToVoQueue, %function
InsertImgToVoQueue:
	.fnstart
.LFB1533:
	@ args = 4, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #44
	sub	sp, sp, #44	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	ldr	r4, [fp, #4]	@ p_image, p_image
	str	r0, [fp, #-56]	@ ChanID, %sfp
	mov	sl, r1	@ eVidStd, eVidStd
	cmp	r4, #0	@ p_image,
	mov	r9, r2	@ pCtx, pCtx
	mov	r5, r3	@ pstVoQue, pstVoQue
	beq	.L464	@,
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC29	@,
	movw	r6, #:lower16:.LANCHOR0	@ tmp316,
	movt	r1, #:upper16:.LC29	@,
	movt	r6, #:upper16:.LANCHOR0	@ tmp316,
	bl	dprint_vfmw	@
	add	r0, r6, #64	@, tmp316,
	bl	OSAL_SpinLockIRQ	@
	ldrh	r7, [r5, #4]	@ i, <variable>.history
	ldrh	r1, [r5, #8]	@ <variable>.tail, <variable>.tail
	and	r7, r7, #63	@ i.1544, i,
	cmp	r1, r7	@ <variable>.tail, i.1544
	beq	.L432	@,
	mov	r8, #1000	@ tmp325,
	b	.L459	@
.L433:
	add	ip, r7, #1	@ i.1543, i.1544,
	and	r7, ip, #63	@ i.1544, i.1543,
	cmp	r1, r7	@ <variable>.tail, i.1544
	beq	.L432	@,
.L459:
	add	r0, r5, r7, asl #2	@, tmp175, pstVoQue, i.1544,
	ldr	r3, [r4, #196]	@ <variable>.image_id, <variable>.image_id
	ldr	r2, [r0, #12]	@ tmp172, <variable>.image_ptr
	ldr	r2, [r2, #196]	@ D.38676, <variable>.image_id
	cmp	r2, r3	@ D.38676, <variable>.image_id
	bne	.L433	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC30	@,
	movt	r1, #:upper16:.LC30	@,
	bl	dprint_vfmw	@
	str	r8, [r4, #200]	@ tmp325, <variable>.error_level
	add	ip, r7, #1	@ i.1543, i.1544,
	ldrh	r1, [r5, #8]	@ <variable>.tail, <variable>.tail
	and	r7, ip, #63	@ i.1544, i.1543,
	cmp	r1, r7	@ <variable>.tail, i.1544
	bne	.L459	@,
.L432:
	ldr	r2, [r4, #200]	@ D.38683, <variable>.error_level
	cmp	r2, #100	@ D.38683,
	bhi	.L465	@,
	ldr	r3, [r4, #164]	@ prephitmp.1532, <variable>.image_width
	cmp	r3, #31	@ prephitmp.1532,
	ldrls	ip, [r4, #168]	@ prephitmp.1579, <variable>.image_height
	bhi	.L466	@,
.L436:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC31	@,
	movt	r1, #:upper16:.LC31	@,
	str	ip, [sp, #0]	@ prephitmp.1579,
	bl	dprint_vfmw	@
	ldr	r1, [r4, #200]	@ <variable>.error_level, <variable>.error_level
	cmp	r1, #1000	@ <variable>.error_level,
	beq	.L439	@,
	mov	r0, sl	@, eVidStd
	mov	r1, r9	@, pCtx
	mov	r2, r4	@, p_image
	bl	ReturnImageToSyntax	@
.L439:
	ldr	r0, .L470	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, #1	@ D.38668,
.L431:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L466:
	ldr	ip, [r4, #168]	@ prephitmp.1579, <variable>.image_height
	cmp	ip, #31	@ prephitmp.1579,
	bls	.L436	@,
	ldrd	r8, [r4, #8]	@ <variable>.PTS, p_image,
	mov	r2, sl	@, eVidStd
	mov	r0, r5	@, pstVoQue
	mov	r1, r4	@, p_image
	strd	r8, [r4]	@ <variable>.PTS, <variable>.SrcPts
	bl	ProduceTimeStamp	@
	ldrd	r2, [r4, #16]	@, p_image,
	strd	r2, [fp, #-68]	@,,
	ldrd	r2, [r4]	@, <variable>.SrcPts
	mov	r8, r0	@ D.38692,
	mov	r9, r1	@ D.38692,
	strd	r8, [r4, #8]	@ D.38692, p_image,
	mov	r0, #29	@,
	strd	r8, [sp]	@ D.38692,
	movw	r1, #:lower16:.LC32	@,
	ldrd	r8, [fp, #-68]	@,,
	movt	r1, #:upper16:.LC32	@,
	strd	r8, [sp, #8]	@,,
	bl	dprint_vfmw	@
	ldr	r7, [r4, #172]	@ <variable>.disp_width, <variable>.disp_width
	cmp	r7, #0	@ <variable>.disp_width,
	beq	.L442	@,
	ldr	r8, [r4, #176]	@ <variable>.disp_height, <variable>.disp_height
	cmp	r8, #0	@ <variable>.disp_height,
	bne	.L467	@,
.L442:
	ldr	r3, [r4, #164]	@ <variable>.image_width, <variable>.image_width
	ldr	r0, [r4, #168]	@ <variable>.image_height, <variable>.image_height
	mov	lr, r3, lsr #1	@ tmp205, <variable>.image_width,
	str	r3, [r4, #172]	@ <variable>.image_width, <variable>.disp_width
	mov	sl, r0, lsr #1	@ tmp207, <variable>.image_height,
	str	r0, [r4, #176]	@ <variable>.image_height, <variable>.disp_height
	str	lr, [r4, #180]	@ tmp205, <variable>.disp_center_x
	str	sl, [r4, #184]	@ tmp207, <variable>.disp_center_y
.L443:
	str	r3, [r5, #300]	@ <variable>.image_width, <variable>.SideInfo.ImageWidth
	ldr	ip, [r4, #168]	@ <variable>.image_height, <variable>.image_height
	ldr	r8, [r5, #280]	@ <variable>.SideInfo.OldSeqCnt, <variable>.SideInfo.OldSeqCnt
	str	ip, [r5, #304]	@ <variable>.image_height, <variable>.SideInfo.ImageHeight
	ldr	r1, [r4, #160]	@ <variable>.format, <variable>.format
	ubfx	lr, r1, #5, #3	@ tmp214, <variable>.format,,
	str	lr, [r5, #308]	@ tmp214, <variable>.SideInfo.VideoFormat
	ldr	r3, [r4, #160]	@ <variable>.format, <variable>.format
	str	r3, [r5, #312]	@ <variable>.format, <variable>.SideInfo.ImageFormat
	ldr	ip, [r4, #180]	@ <variable>.disp_center_x, <variable>.disp_center_x
	ldrh	r2, [r4, #184]	@ tmp223, <variable>.disp_center_y
	ldr	r7, [r4, #160]	@ temp.1552, <variable>.format
	ldr	lr, [r4, #204]	@ D.38723, <variable>.seq_cnt
	orr	r1, r2, ip, asl #16	@,, tmp223, <variable>.disp_center_x,
	ldr	sl, [r4, #176]	@ <variable>.disp_height, <variable>.disp_height
	ldrh	r0, [r4, #172]	@ tmp218, <variable>.disp_width
	cmp	lr, r8	@ D.38723, <variable>.SideInfo.OldSeqCnt
	str	r1, [fp, #-68]	@, %sfp
	ubfx	r8, r7, #8, #2	@ ScanType, temp.1552,,
	ldr	r3, [r5, #316]	@ D.38727, <variable>.SideInfo.SeqImgCnt
	ubfx	r7, r7, #14, #3	@ AspectRatio, temp.1552,,
	strne	lr, [r5, #320]	@ D.38723, <variable>.SideInfo.SeqCnt
	orr	sl, r0, sl, asl #16	@, dsize, tmp218, <variable>.disp_height,
	add	ip, r3, #1	@ tmp229, D.38727,
	str	r3, [r4, #208]	@ D.38727, <variable>.seq_img_cnt
	ldr	r3, [r5, #272]	@ D.38729, <variable>.SideInfo.OldAspectRatio
	str	ip, [r5, #316]	@ tmp229, <variable>.SideInfo.SeqImgCnt
	cmp	r3, r7	@ D.38729, AspectRatio
	movweq	r9, #:lower16:g_event_report	@ tmp318,
	movteq	r9, #:upper16:g_event_report	@ tmp318,
	beq	.L445	@,
	movw	r9, #:lower16:g_event_report	@ tmp318,
	movt	r9, #:upper16:g_event_report	@ tmp318,
	ldr	ip, [r9, #0]	@ g_event_report.459, g_event_report
	cmp	ip, #0	@ g_event_report.459,
	beq	.L446	@,
	strb	r3, [fp, #-52]	@ D.38729, para
	mov	r1, #7	@,
	ldr	r0, [fp, #-56]	@, %sfp
	sub	r2, fp, #52	@,,
	strb	r7, [fp, #-51]	@ AspectRatio, para
	mov	r3, #2	@,
	blx	ip	@ g_event_report.459
.L446:
	str	r7, [r5, #272]	@ AspectRatio, <variable>.SideInfo.OldAspectRatio
.L445:
	ldr	r2, [r5, #276]	@ <variable>.SideInfo.OldScanType, <variable>.SideInfo.OldScanType
	cmp	r2, r8	@ <variable>.SideInfo.OldScanType, ScanType
	beq	.L447	@,
	ldr	ip, [r9, #0]	@ g_event_report.1556, g_event_report
	cmp	ip, #0	@ g_event_report.1556,
	beq	.L448	@,
	sub	r2, fp, #44	@ tmp237,,
	ldr	r0, [fp, #-56]	@, %sfp
	mov	r1, #4	@,
	mov	r3, #1	@,
	strb	r8, [r2, #-8]!	@ ScanType, para
	blx	ip	@ g_event_report.1556
.L448:
	str	r8, [r5, #276]	@ ScanType, <variable>.SideInfo.OldScanType
.L447:
	ldr	r7, [r5, #288]	@ <variable>.SideInfo.OldDispSize, <variable>.SideInfo.OldDispSize
	cmp	r7, sl	@ <variable>.SideInfo.OldDispSize, dsize
	beq	.L468	@,
.L449:
	str	sl, [r5, #288]	@ dsize, <variable>.SideInfo.OldDispSize
	ldr	sl, [fp, #-68]	@, %sfp
	str	sl, [r5, #292]	@, <variable>.SideInfo.OldDispCenter
	ldr	ip, [r9, #0]	@ g_event_report.1557, g_event_report
	cmp	ip, #0	@ g_event_report.1557,
	beq	.L450	@,
	ldrh	r2, [r4, #172]	@, <variable>.disp_width
	ldr	r0, [fp, #-56]	@, %sfp
	strh	r2, [fp, #-52]	@ movhi	@, para
	sub	r2, fp, #52	@,,
	ldrh	r1, [r4, #176]	@, <variable>.disp_height
	strh	r1, [fp, #-50]	@ movhi	@, para
	mov	r1, #1	@,
	ldrh	lr, [r4, #180]	@, <variable>.disp_center_x
	strh	lr, [fp, #-48]	@ movhi	@, para
	ldrh	r3, [r4, #184]	@, <variable>.disp_center_y
	strh	r3, [fp, #-46]	@ movhi	@, para
	mov	r3, #8	@,
	blx	ip	@ g_event_report.1557
.L450:
	ldr	sl, [r4, #104]	@ <variable>.luma_phy_addr, <variable>.luma_phy_addr
	mov	r0, #12	@,
	ldr	r3, [r4, #108]	@ <variable>.chrom_phy_addr, <variable>.chrom_phy_addr
	movw	r1, #:lower16:.LC33	@,
	ldr	r2, [r4, #192]	@ <variable>.image_stride, <variable>.image_stride
	movt	r1, #:upper16:.LC33	@,
	str	sl, [r4, #88]	@ <variable>.luma_phy_addr, <variable>.top_luma_phy_addr
	str	r3, [r4, #92]	@ <variable>.chrom_phy_addr, <variable>.top_chrom_phy_addr
	add	r8, r2, r3	@ tmp256, <variable>.image_stride, <variable>.chrom_phy_addr
	add	r7, r2, sl	@ tmp252, <variable>.image_stride, <variable>.luma_phy_addr
	str	r8, [r4, #100]	@ tmp256, <variable>.btm_chrom_phy_addr
	str	r7, [r4, #96]	@ tmp252, <variable>.btm_luma_phy_addr
	movw	sl, #:lower16:g_VfmwChanStat	@ tmp248,
	ldrh	ip, [r5, #8]	@ <variable>.tail, <variable>.tail
	movt	sl, #:upper16:g_VfmwChanStat	@ tmp248,
	ldr	lr, [r4, #196]	@ <variable>.image_id, <variable>.image_id
	movw	r7, #:lower16:g_LowDelaySeqIndex	@ tmp276,
	ldr	r8, [fp, #-56]	@, %sfp
	movt	r7, #:upper16:g_LowDelaySeqIndex	@ tmp276,
	ldrh	r2, [r5, #4]	@ <variable>.history, <variable>.history
	ldrh	r3, [r5, #6]	@ <variable>.head, <variable>.head
	str	ip, [sp, #0]	@ <variable>.tail,
	mov	ip, #300	@ tmp247,
	str	lr, [sp, #4]	@ <variable>.image_id,
	mul	lr, ip, r8	@, tmp247,
	str	lr, [fp, #-68]	@, %sfp
	bl	dprint_vfmw	@
	ldrh	r3, [r5, #8]	@ <variable>.tail, <variable>.tail
	mov	r1, #5	@,
	ldr	r0, [fp, #-56]	@, %sfp
	add	r2, r3, #1	@ tmp270, <variable>.tail,
	add	ip, r5, r3, asl #2	@, tmp266, pstVoQue, <variable>.tail,
	and	r8, r2, #63	@ tmp272, tmp270,
	strh	r8, [r5, #8]	@ movhi	@ tmp272, <variable>.tail
	ldr	r2, [fp, #-68]	@, %sfp
	str	r4, [ip, #12]	@ p_image, <variable>.image_ptr
	ldr	r3, [r4, #148]	@ <variable>.is_fld_save, <variable>.is_fld_save
	add	r8, sl, r2	@ pVfmwChanStat, tmp248,
	str	r3, [r8, #20]	@ <variable>.is_fld_save, <variable>.u32IsFieldFlag
	ldr	lr, [r4, #196]	@ <variable>.image_id, <variable>.image_id
	add	r2, lr, #2	@ tmp275, <variable>.image_id,
	str	r2, [r5, #296]	@ tmp275, <variable>.SideInfo.LastImageIdPlus2
	ldr	ip, [fp, #-56]	@, %sfp
	ldr	r2, [r7, ip, asl #2]	@, g_LowDelaySeqIndex
	bl	VDEC_Lowdelay_Event_Time	@
	ldr	lr, [fp, #-56]	@, %sfp
	ldr	r0, .L470	@,
	ldr	r3, [r7, lr, asl #2]	@ tmp280, g_LowDelaySeqIndex
	add	ip, r3, #1	@ tmp281, tmp280,
	str	ip, [r7, lr, asl #2]	@ tmp281, g_LowDelaySeqIndex
	bl	OSAL_SpinUnLockIRQ	@
	ldr	ip, [r9, #0]	@ g_event_report.1574, g_event_report
	cmp	ip, #0	@ g_event_report.1574,
	beq	.L451	@,
	mov	r2, r4	@, p_image
	ldr	r0, [fp, #-56]	@, %sfp
	mov	r1, #5	@,
	mov	r3, #496	@,
	blx	ip	@ g_event_report.1574
.L451:
	mov	r0, #8	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	bne	.L469	@,
.L452:
	ldr	r0, [r8, #4]	@ <variable>.u32FrImgNum, <variable>.u32FrImgNum
	add	r4, r0, #1	@ tmp305, <variable>.u32FrImgNum,
	str	r4, [r8, #4]	@ tmp305, <variable>.u32FrImgNum
	bl	OSAL_GetTimeInMs	@
	ldr	r1, [fp, #-68]	@, %sfp
	ldr	r3, [sl, r1]	@ <variable>.u32FrBeginTime, <variable>.u32FrBeginTime
	rsb	r1, r3, r0	@ Period, <variable>.u32FrBeginTime, CurTime.1575
	mov	r4, r0	@ CurTime.1575,
	cmp	r1, #1000	@ Period,
	movcc	r0, #1	@ D.38668,
	bcc	.L431	@,
	ldr	r3, [r8, #4]	@ temp.1576, <variable>.u32FrImgNum
	cmp	r3, #0	@ temp.1576,
	beq	.L454	@,
	movw	ip, #10000	@ tmp309,
	mul	r0, ip, r3	@, tmp309, temp.1576
	bl	__aeabi_uidiv	@
	str	r0, [r8, #8]	@, <variable>.u32FrFrameRate
.L454:
	ldr	lr, [fp, #-68]	@, %sfp
	mov	r2, #0	@ tmp313,
	mov	r0, #1	@ D.38668,
	str	r2, [r8, #4]	@ tmp313, <variable>.u32FrImgNum
	str	r4, [sl, lr]	@ CurTime.1575, <variable>.u32FrBeginTime
	b	.L431	@
.L465:
	ldr	r3, [r4, #164]	@ prephitmp.1532, <variable>.image_width
	ldr	ip, [r4, #168]	@ prephitmp.1579, <variable>.image_height
	b	.L436	@
.L467:
	cmp	sl, #15	@ eVidStd,
	cmpne	sl, #0	@, eVidStd,
	beq	.L463	@,
	cmp	sl, #16	@ eVidStd,
	bne	.L442	@,
.L463:
	ldr	r3, [r4, #164]	@ <variable>.image_width, <variable>.image_width
	b	.L443	@
.L469:
	bl	OSAL_GetTimeInMs	@
	ldr	r2, [fp, #-56]	@, %sfp
	movw	ip, #:lower16:g_TraceFramePeriod	@ tmp292,
	movt	ip, #:upper16:g_TraceFramePeriod	@ tmp292,
	add	r6, r6, r2, asl #2	@, tmp288, tmp316,,
	ldr	r1, [r6, #76]	@ tmp291, last_rec_pos_time
	mov	r3, r0	@ CurTime,
	ldr	r0, [ip, #0]	@ g_TraceFramePeriod, g_TraceFramePeriod
	rsb	r4, r1, r3	@ tmp290, tmp291, CurTime
	cmp	r4, r0	@ tmp290, g_TraceFramePeriod
	bls	.L452	@,
	ldr	r9, [fp, #-56]	@, %sfp
	movw	r1, #527	@,
	ldr	r0, .L470+4	@,
	str	r3, [r6, #76]	@ CurTime, last_rec_pos_time
	mov	lr, r9, asl #24	@ tmp302,,
	add	r2, lr, #524288	@, tmp302,
	bl	DBG_AddTrace	@
	b	.L452	@
.L468:
	ldr	r0, [r5, #292]	@ <variable>.SideInfo.OldDispCenter, <variable>.SideInfo.OldDispCenter
	ldr	r8, [fp, #-68]	@, %sfp
	cmp	r0, r8	@ <variable>.SideInfo.OldDispCenter,
	bne	.L449	@,
	b	.L450	@
.L464:
	mov	r0, r4	@, p_image
	movw	r1, #:lower16:.LC2	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #1	@ D.38668,
	b	.L431	@
.L471:
	.align	2
.L470:
	.word	.LANCHOR0+64
	.word	.LANCHOR1+16
	.fnend
	.size	InsertImgToVoQueue, .-InsertImgToVoQueue
	.global	g_DnrEnable
	.global	pstVdecUsdPool
	.global	g_SpinLock
	.global	g_SpinLockIrq_Destroy
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.39997, %object
	.size	__func__.39997, 15
__func__.39997:
	.ascii	"IsVoQueueEmpty\000"
	.space	1
	.type	__func__.38662, %object
	.size	__func__.38662, 19
__func__.38662:
	.ascii	"InsertImgToVoQueue\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"WARNNING: aspect ration (%d) is not expected!\012\000"
	.space	1
.LC1:
	.ascii	"%s pstVoQue NULL\012\000"
	.space	2
.LC2:
	.ascii	"image point NULL\012\000"
	.space	2
.LC3:
	.ascii	"VoQueue state: head(%d) history(%d) tail(%d)\000"
	.space	3
.LC4:
	.ascii	"\012\000"
	.space	2
.LC5:
	.ascii	"%d \000"
.LC6:
	.ascii	"Initializing VO queue\012\000"
	.space	1
.LC7:
	.ascii	"pu8[0] = %x,pu8[1] = %x, pu8[2] = %x\012\000"
	.space	2
.LC8:
	.ascii	"release segbuf together!\012\000"
	.space	2
.LC9:
	.ascii	"ERROR: VFMW_VP8 one packet stream, but IsLastSeg =="
	.ascii	" 0\012\000"
	.space	1
.LC10:
	.ascii	"ERROR: VFMW_VP6 one packet stream, but IsLastSeg =="
	.ascii	" 0\012\000"
	.space	1
.LC11:
	.ascii	"VidStd=%d Error!\012\000"
	.space	2
.LC12:
	.ascii	"pSegMan error!\012\000"
.LC13:
	.ascii	"More than two packet!!!ERROR!!!\012\000"
	.space	3
.LC14:
	.ascii	"*****************copy packets tobe one*************"
	.ascii	"****\012\000"
	.space	3
.LC15:
	.ascii	"*****************two packet*****************\012\000"
	.space	2
.LC16:
	.ascii	"pSegMan->CurrSeg.IsLastSeg=%d\012\000"
	.space	1
.LC17:
	.ascii	"pSegMan->CurrSeg.PhyAddr=%#x\012\000"
	.space	2
.LC18:
	.ascii	"pSegMan->CurrSeg.LenInByte=%#x\012\000"
.LC19:
	.ascii	"ERROR: Wrong PreParseInfo about Vc1 IsAdvProfile!\012"
	.ascii	"\000"
	.space	1
.LC20:
	.ascii	"ERROR: Wrong PreParseInfo about Vc1 CodecVersion!\012"
	.ascii	"\000"
	.space	1
.LC21:
	.ascii	"LENTH ERROR: VC1 S/MP BS is wrong!\012\000"
.LC22:
	.ascii	"SYNTAX ERROR: VC1 S/MP BS is wrong!\012\000"
	.space	3
.LC23:
	.ascii	"Queue=(%02d,%02d,%02d) - F%d\012\000"
	.space	2
.LC24:
	.ascii	"ResetVoQueue but queue not empty: head(%d) history("
	.ascii	"%d) tail(%d)\012\000"
	.space	3
.LC25:
	.ascii	"SYNTAX_ReleaseImage p_image is null\012\000"
	.space	3
.LC26:
	.ascii	"Image %d not found in vo queue.\012\000"
	.space	3
.LC27:
	.ascii	"image[%d] null\012\000"
.LC28:
	.ascii	"Queue=(%02d,%02d,%02d) x F%d\012\000"
	.space	2
.LC29:
	.ascii	"call InsertVOQueue\012\000"
.LC30:
	.ascii	"FATAL: p_image(id=%d) has already in the VoQueue!\012"
	.ascii	"\000"
	.space	1
.LC31:
	.ascii	"error=%d,W=%d,H=%d,not acceptable!\012\000"
.LC32:
	.ascii	"out_pts: %lld -> %lld Usertag %lld\012\000"
.LC33:
	.ascii	"Queue=(%02d,%02d,%02d) + F%d\012\000"
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	pstVdecUsdPool, %object
	.size	pstVdecUsdPool, 64
pstVdecUsdPool:
	.space	64
	.type	g_SpinLock, %object
	.size	g_SpinLock, 12
g_SpinLock:
	.space	12
	.type	last_rec_pos_time.38654, %object
	.size	last_rec_pos_time.38654, 64
last_rec_pos_time.38654:
	.space	64
	.type	g_DnrEnable, %object
	.size	g_DnrEnable, 4
g_DnrEnable:
	.space	4
	.type	g_SpinLockIrq_Destroy, %object
	.size	g_SpinLockIrq_Destroy, 12
g_SpinLockIrq_Destroy:
	.space	12
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
