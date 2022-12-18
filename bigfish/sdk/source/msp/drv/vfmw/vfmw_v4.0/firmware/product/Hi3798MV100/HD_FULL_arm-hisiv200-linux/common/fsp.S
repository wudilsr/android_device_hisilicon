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
	.file	"fsp.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(fsp) -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw)
@ -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/vfmw/vfmw_v4.0/firmware/common/.fsp.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/common/fsp.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/vfmw/vfmw_v4.0/firmware/common/fsp.o -O2 -Wall -Wundef
@ -Wstrict-prototypes -Wno-trigraphs -Werror-implicit-function-declaration
@ -Wno-format-security -Wframe-larger-than=1024
@ -Wdeclaration-after-statement -Wno-pointer-sign -p -fno-strict-aliasing
@ -fno-common -fno-delete-null-pointer-checks -fno-dwarf2-cfi-asm
@ -funwind-tables -fno-stack-protector -fno-omit-frame-pointer
@ -fno-optimize-sibling-calls -fno-strict-overflow -fconserve-stack
@ -fno-pic -fverbose-asm
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
	.global	FSP_GetUsedBufferNum
	.type	FSP_GetUsedBufferNum, %function
FSP_GetUsedBufferNum:
	.fnstart
.LFB1543:
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
	movw	r2, #:lower16:s_pstVfmwChan	@ tmp172,
	movt	r2, #:upper16:s_pstVfmwChan	@ tmp172,
	movw	r3, #:lower16:206858	@ tmp173,
	movt	r3, #:upper16:206858	@ tmp173,
	ldr	ip, [r2, r0, asl #2]	@ D.38741, s_pstVfmwChan
	ldrsb	r6, [ip, r3]	@ D.38746, <variable>.FspInst.s32DecFsNum
	cmp	r6, #0	@ D.38746,
	movle	r0, #0	@ s32UsedFrameNum,
	ldmlefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	movw	r0, #:lower16:241310	@ tmp181,
	movt	r0, #:upper16:241310	@ tmp181,
	add	r3, ip, r0	@ tmp181, D.38741, tmp181
	rsb	r6, r6, r6, asl #4	@, tmp178, D.38746, D.38746,
	mov	r0, #0	@ s32UsedFrameNum,
	ldrsb	r2, [r3, #0]	@ <variable>.DispState, <variable>.DispState
	mov	r6, r6, asl #2	@ D.40372, tmp178,
	sub	r1, r6, #60	@ tmp189, D.40372,
	cmp	r2, #3	@ <variable>.DispState,
	ubfx	r2, r1, #2, #1	@ tmp193, tmp189,,
	beq	.L19	@,
	mov	r3, #60	@ ivtmp.610,
	cmp	r3, r6	@ ivtmp.610, D.40372
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L21:
	cmp	r2, #0	@ tmp193,
	beq	.L5	@,
	movw	r1, #:lower16:241370	@ tmp208,
	movt	r1, #:upper16:241370	@ tmp208,
	add	r2, ip, r1	@ tmp208, D.38741, tmp208
	add	r3, r3, #60	@ ivtmp.610, ivtmp.610,
	ldrsb	r1, [r2, #0]	@ <variable>.DispState, <variable>.DispState
	cmp	r1, #3	@ <variable>.DispState,
	addeq	r0, r0, #1	@ s32UsedFrameNum, s32UsedFrameNum,
	cmp	r3, r6	@ ivtmp.610, D.40372
	bne	.L5	@,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L13:
	add	r3, r1, #60	@ ivtmp.610, tmp194,
	cmp	r3, r6	@ ivtmp.610, D.40372
	beq	.L20	@,
.L5:
	movw	r2, #:lower16:241310	@ tmp199,
	movt	r2, #:upper16:241310	@ tmp199,
	add	r5, ip, r3	@ tmp197, D.38741, ivtmp.610
	add	r1, r3, #60	@ tmp194, ivtmp.610,
	mov	r3, r2	@ tmp204, tmp199
	add	r2, r5, r2	@ tmp199, tmp197, tmp199
	add	r4, ip, r1	@ tmp202, D.38741, tmp194
	ldrsb	r2, [r2, #0]	@ <variable>.DispState, <variable>.DispState
	add	r3, r4, r3	@ tmp204, tmp202, tmp204
	cmp	r2, #3	@ <variable>.DispState,
	ldrsb	r2, [r3, #0]	@ <variable>.DispState, <variable>.DispState
	addeq	r0, r0, #1	@ s32UsedFrameNum, s32UsedFrameNum,
	cmp	r2, #3	@ <variable>.DispState,
	bne	.L13	@,
	add	r3, r1, #60	@ ivtmp.610, tmp194,
	add	r0, r0, #1	@ s32UsedFrameNum, s32UsedFrameNum,
	cmp	r3, r6	@ ivtmp.610, D.40372
	bne	.L5	@,
.L20:
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L19:
	mov	r3, #60	@ ivtmp.610,
	cmp	r3, r6	@ ivtmp.610, D.40372
	mov	r0, #1	@ s32UsedFrameNum,
	bne	.L21	@,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	FSP_GetUsedBufferNum, .-FSP_GetUsedBufferNum
	.align	2
	.global	FindLeastTickPhyFs
	.type	FindLeastTickPhyFs, %function
FindLeastTickPhyFs:
	.fnstart
.LFB1551:
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
	cmp	r1, #0	@ PhyNum
	movle	r5, #0	@ LeastFsID,
	ble	.L26	@,
	tst	r1, #1	@ PhyNum,
	mov	r5, #0	@ LeastFsID,
	mvn	ip, #0	@ LeastTick.649,
	mov	r2, r5	@ i, LeastFsID
	bne	.L27	@,
	ldr	r3, [r0, #56]	@ LeastTick, <variable>.u32Tick
	add	r0, r0, #60	@ pstPhyFs, pstPhyFs,
	mov	r2, #1	@ i,
	add	r4, r0, #60	@ tmp172, pstPhyFs,
	cmn	r3, #1	@ LeastTick,
	movcs	r3, ip	@, LeastTick, LeastTick.649
	mov	ip, r3	@ LeastTick.649, LeastTick
	ldr	r3, [r0, #56]	@ LeastTick, <variable>.u32Tick
	cmp	r3, ip	@ LeastTick, LeastTick.649
	movcc	r5, r2	@ LeastFsID, i
	add	r2, r2, #1	@ tmp171, i,
	movcs	r3, ip	@ LeastTick, LeastTick.649
	cmp	r2, r1	@ tmp171, PhyNum
	beq	.L26	@,
.L39:
	ldr	ip, [r4, #56]	@ LeastTick, <variable>.u32Tick
	cmp	ip, r3	@ LeastTick, LeastTick
	movcs	ip, r3	@ LeastTick, LeastTick
	movcc	r5, r2	@ LeastFsID, tmp171
.L38:
	add	r2, r2, #1	@ i, tmp171,
	add	r0, r4, #60	@ pstPhyFs, tmp172,
.L27:
	ldr	r3, [r0, #56]	@ LeastTick, <variable>.u32Tick
	add	r4, r0, #60	@ tmp172, pstPhyFs,
	cmp	r3, ip	@ LeastTick, LeastTick.649
	movcc	r5, r2	@ LeastFsID, i
	add	r2, r2, #1	@ tmp171, i,
	movcs	r3, ip	@ LeastTick, LeastTick.649
	cmp	r2, r1	@ tmp171, PhyNum
	bne	.L39	@,
.L26:
	mov	r0, r5	@, LeastFsID
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	FindLeastTickPhyFs, .-FindLeastTickPhyFs
	.align	2
	.global	FSP_GetLogicFs
	.type	FSP_GetLogicFs, %function
FSP_GetLogicFs:
	.fnstart
.LFB1562:
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
	cmp	r1, #63	@ LogicFrameID,
	cmpls	r0, #15	@, InstID,
	bls	.L44	@,
.L41:
	mov	r0, #0	@ pstLogicFs,
	ldmfd	sp, {fp, sp, pc}	@
.L44:
	movw	r3, #:lower16:.LANCHOR0	@ tmp146,
	movt	r3, #:upper16:.LANCHOR0	@ tmp146,
	ldr	r3, [r3, r0, asl #2]	@ D.39767, s_pFspInst
	cmp	r3, #0	@ D.39767,
	beq	.L41	@,
	mov	r2, #536	@ tmp148,
	mla	r0, r2, r1, r3	@ pstLogicFs, tmp148, LogicFrameID, D.39767
	add	r0, r0, #96	@ pstLogicFs, pstLogicFs,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetLogicFs, .-FSP_GetLogicFs
	.align	2
	.global	FSP_GetFsImagePtr
	.type	FSP_GetFsImagePtr, %function
FSP_GetFsImagePtr:
	.fnstart
.LFB1563:
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
	cmp	r1, #63	@ LogicFrameID,
	cmpls	r0, #15	@, InstID,
	bls	.L49	@,
.L46:
	mov	r0, #0	@ D.39791,
	ldmfd	sp, {fp, sp, pc}	@
.L49:
	movw	r3, #:lower16:.LANCHOR0	@ tmp146,
	movt	r3, #:upper16:.LANCHOR0	@ tmp146,
	ldr	r3, [r3, r0, asl #2]	@ D.39786, s_pFspInst
	cmp	r3, #0	@ D.39786,
	beq	.L46	@,
	mov	r2, #536	@ tmp148,
	mla	r0, r2, r1, r3	@ D.39791, tmp148, LogicFrameID, D.39786
	add	r0, r0, #104	@ D.39791, D.39791,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetFsImagePtr, .-FSP_GetFsImagePtr
	.align	2
	.global	FSP_GetDecPhyFs
	.type	FSP_GetDecPhyFs, %function
FSP_GetDecPhyFs:
	.fnstart
.LFB1564:
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
	cmp	r1, #63	@ LogicFrameID,
	cmpls	r0, #15	@, InstID,
	bls	.L54	@,
.L51:
	mov	r0, #0	@ D.39810,
	ldmfd	sp, {fp, sp, pc}	@
.L54:
	movw	r3, #:lower16:.LANCHOR0	@ tmp146,
	movt	r3, #:upper16:.LANCHOR0	@ tmp146,
	ldr	r3, [r3, r0, asl #2]	@ D.39805, s_pFspInst
	cmp	r3, #0	@ D.39805,
	beq	.L51	@,
	mov	r2, #536	@ tmp149,
	mla	r1, r2, r1, r3	@ tmp150, tmp149, LogicFrameID, D.39805
	ldr	r0, [r1, #608]	@ D.39810, <variable>.pstDecodeFs
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetDecPhyFs, .-FSP_GetDecPhyFs
	.align	2
	.global	FSP_GetDispPhyFs
	.type	FSP_GetDispPhyFs, %function
FSP_GetDispPhyFs:
	.fnstart
.LFB1565:
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
	cmp	r1, #63	@ LogicFrameID,
	cmpls	r0, #15	@, InstID,
	bls	.L59	@,
.L56:
	mov	r0, #0	@ D.39829,
	ldmfd	sp, {fp, sp, pc}	@
.L59:
	movw	r3, #:lower16:.LANCHOR0	@ tmp146,
	movt	r3, #:upper16:.LANCHOR0	@ tmp146,
	ldr	r3, [r3, r0, asl #2]	@ D.39824, s_pFspInst
	cmp	r3, #0	@ D.39824,
	beq	.L56	@,
	mov	r2, #536	@ tmp149,
	mla	r1, r2, r1, r3	@ tmp150, tmp149, LogicFrameID, D.39824
	ldr	r0, [r1, #612]	@ D.39829, <variable>.pstDispOutFs
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetDispPhyFs, .-FSP_GetDispPhyFs
	.align	2
	.global	FSP_GetPmvAddr
	.type	FSP_GetPmvAddr, %function
FSP_GetPmvAddr:
	.fnstart
.LFB1566:
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
	cmp	r1, #63	@ LogicFrameID,
	cmpls	r0, #15	@, InstID,
	bhi	.L61	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp146,
	movt	r3, #:upper16:.LANCHOR0	@ tmp146,
	ldr	r3, [r3, r0, asl #2]	@ D.39843, s_pFspInst
	cmp	r3, #0	@ D.39843,
	beq	.L61	@,
	mov	r2, #536	@ tmp149,
	mla	r1, r2, r1, r3	@ tmp150, tmp149, LogicFrameID, D.39843
	ldr	r0, [r1, #620]	@ D.39848, <variable>.PmvAddr
	ldmfd	sp, {fp, sp, pc}	@
.L61:
	mov	r0, #0	@ D.39848,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetPmvAddr, .-FSP_GetPmvAddr
	.align	2
	.global	FSP_IsFsInVO
	.type	FSP_IsFsInVO, %function
FSP_IsFsInVO:
	.fnstart
.LFB1574:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp187,
	movt	r3, #:upper16:.LANCHOR0	@ tmp187,
	ldr	r4, [r3, r0, asl #2]	@ pstInst, s_pFspInst
	cmp	r4, #0	@ pstInst,
	beq	.L66	@,
	add	r0, r0, r0, asl #5	@, tmp148, InstID, InstID,
	add	r2, r3, r0, asl #3	@, tmp150, tmp187, tmp148,
	add	r2, r2, #64	@ tmp151, tmp150,
	ldrsh	ip, [r2, #2]	@ D.40084, <variable>.history
	cmn	ip, #1	@ D.40084,
	beq	.L66	@,
	ldrh	r2, [r2, #4]	@ i.789, <variable>.head
	cmp	r2, ip	@ i.789, D.40084
	beq	.L66	@,
	ldr	r4, [r4, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r4, #1	@ <variable>.eFspInstState,
	beq	.L75	@,
.L66:
	mov	r0, #0	@ ret,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L75:
	and	r2, r2, #63	@ i, i.789,
	cmp	ip, r2	@ D.40084, i
	beq	.L66	@,
	mov	r4, r0, asl #1	@ tmp166, tmp148,
	add	r0, r4, r2	@ tmp167, tmp166, i
	add	r0, r3, r0, asl #2	@, tmp171, tmp187, tmp167,
	ldr	r0, [r0, #72]	@ tmp173, <variable>.Addr
	cmp	r0, r1	@ tmp173, DecPhyAddr
	bne	.L73	@,
	b	.L67	@
.L74:
	ldr	r0, [r0, #72]	@ tmp185, <variable>.Addr
	cmp	r0, r1	@ tmp185, DecPhyAddr
	beq	.L67	@,
.L73:
	add	r2, r2, #1	@ i.791, i,
	and	r2, r2, #63	@ i, i.791,
	add	r0, r4, r2	@ tmp179, tmp190, i
	cmp	ip, r2	@ D.40084, i
	add	r0, r3, r0, asl #2	@, tmp183, tmp187, tmp179,
	bne	.L74	@,
	b	.L66	@
.L67:
	mov	r0, #1	@ ret,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	FSP_IsFsInVO, .-FSP_IsFsInVO
	.align	2
	.global	FSP_GetNullLogicFs
	.type	FSP_GetNullLogicFs, %function
FSP_GetNullLogicFs:
	.fnstart
.LFB1576:
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
	movw	r2, #:lower16:.LANCHOR0	@ tmp143,
	movt	r2, #:upper16:.LANCHOR0	@ tmp143,
	mov	r3, #63	@ i,
	ldr	r2, [r2, r0, asl #2]	@ pstInst, s_pFspInst
	add	r1, r2, #33792	@ ivtmp.825, pstInst,
	add	r1, r1, #73	@ ivtmp.825, ivtmp.825,
	b	.L79	@
.L87:
	ldrb	ip, [r1, #-536]	@ zero_extendqisi2	@ <variable>.s32DispState, <variable>.s32DispState
	sub	r3, r3, #1	@ i, i,
	sub	r1, r1, #1072	@ ivtmp.825, ivtmp.825,
	cmp	ip, #0	@ <variable>.s32DispState,
	beq	.L78	@,
	subs	r3, r3, #1	@ i, i,
	bcc	.L86	@,
.L79:
	ldrsb	r0, [r1, #0]	@ <variable>.s32DispState, <variable>.s32DispState
	cmp	r0, #0	@ <variable>.s32DispState,
	bne	.L87	@,
.L78:
	mov	ip, #536	@ tmp149,
	mov	r0, r3	@, ret_id
	mla	r2, ip, r3, r2	@ tmp150, tmp149, ret_id, pstInst
	mov	r3, #0	@ tmp152,
	add	r1, r2, #608	@ tmp151, tmp150,
	str	r3, [r2, #608]	@ tmp152, <variable>.pstDecodeFs
	str	r3, [r1, #4]	@ tmp152, <variable>.pstDispOutFs
	ldmfd	sp, {fp, sp, pc}	@
.L86:
	mov	r3, #0	@ ret_id,
	b	.L78	@
	.fnend
	.size	FSP_GetNullLogicFs, .-FSP_GetNullLogicFs
	.align	2
	.global	FSP_GetTotalValidFsNum
	.type	FSP_GetTotalValidFsNum, %function
FSP_GetTotalValidFsNum:
	.fnstart
.LFB1579:
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
	cmp	r0, #15	@ InstID,
	bhi	.L93	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp139,
	movt	r3, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r0, [r3, r0, asl #2]	@ D.40201, s_pFspInst
	cmp	r0, #0	@ D.40201,
	beq	.L94	@,
	ldrsb	r0, [r0, #9]	@ D.40199, <variable>.s8TotalValidFsNum
	ldmfd	sp, {fp, sp, pc}	@
.L93:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #3141	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40199,
	ldmfd	sp, {fp, sp, pc}	@
.L94:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #3142	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40199,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetTotalValidFsNum, .-FSP_GetTotalValidFsNum
	.align	2
	.global	FSP_GetFspType
	.type	FSP_GetFspType, %function
FSP_GetFspType:
	.fnstart
.LFB1578:
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
	cmp	r0, #15	@ InstID,
	bhi	.L101	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp139,
	movt	r3, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r0, [r3, r0, asl #2]	@ D.40186, s_pFspInst
	cmp	r0, #0	@ D.40186,
	beq	.L102	@,
	ldr	r1, [r0, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r1, #1	@ <variable>.eFspInstState,
	moveq	r0, #0	@, D.40184,
	mvnne	r0, #0	@, D.40184,
	ldmfd	sp, {fp, sp, pc}	@
.L101:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #3117	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40184,
	ldmfd	sp, {fp, sp, pc}	@
.L102:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #3118	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40184,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetFspType, .-FSP_GetFspType
	.align	2
	.global	FSP_SwitchNotify
	.type	FSP_SwitchNotify, %function
FSP_SwitchNotify:
	.fnstart
.LFB1577:
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
	cmp	r0, #15	@ InstID,
	ldmlsfd	sp, {fp, sp, pc}	@
	movw	r1, #:lower16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r3, #:upper16:.LC1	@,
	mov	r2, #3088	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_SwitchNotify, .-FSP_SwitchNotify
	.align	2
	.global	FSP_ProcFspQue
	.type	FSP_ProcFspQue, %function
FSP_ProcFspQue:
	.fnstart
.LFB1575:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r1, #0	@ p_image
	beq	.L125	@,
	cmp	r2, #1	@ Flag,
	bhi	.L126	@,
	beq	.L127	@,
	mov	r9, r0, asl #5	@ tmp307, InstID,
	movw	ip, #:lower16:.LANCHOR0	@ tmp309,
	add	r4, r9, r0	@ tmp195, tmp307, InstID
	movt	ip, #:upper16:.LANCHOR0	@ tmp309,
	add	r8, ip, r4, asl #3	@, tmp197, tmp309, tmp195,
	add	r8, r8, #64	@ tmp198, tmp197,
	ldrh	r2, [r8, #4]	@ prephitmp.919, <variable>.head
	ldrh	r5, [r8, #6]	@ <variable>.tail, <variable>.tail
	and	r3, r2, #63	@ i.935, prephitmp.919,
	cmp	r5, r3	@ <variable>.tail, i.935
	beq	.L111	@,
	mov	r4, r4, asl #1	@ tmp317, tmp195,
.L121:
	add	r2, r4, r3	@ tmp213, tmp317, i.935
	ldr	r5, [r1, #88]	@ <variable>.top_luma_phy_addr, <variable>.top_luma_phy_addr
	add	r2, ip, r2, asl #2	@, tmp217, tmp309, tmp213,
	ldr	r2, [r2, #72]	@ D.40128, <variable>.Addr
	cmp	r5, r2	@ <variable>.top_luma_phy_addr, D.40128
	moveq	sl, #1	@ SameImageFlag,
	beq	.L123	@,
	cmp	r2, #0	@ D.40128,
	addne	r3, r3, #1	@ i.934, i.935,
	bne	.L114	@,
	mov	sl, #2	@ SameImageFlag,
	b	.L123	@
.L128:
	mov	r3, r2	@ i.935, j
.L123:
	cmp	r3, #0	@ i.935,
	sub	r2, r3, #1	@ j, i.935,
	add	r5, r4, r3	@ tmp225, tmp317, i.935
	ldrh	r7, [r8, #4]	@ D.40124, <variable>.head
	moveq	r2, #63	@ j,
	add	r6, r4, r2	@ tmp236, tmp317, j
	add	r5, ip, r5, asl #2	@, tmp229, tmp309, tmp225,
	cmp	r7, r3	@ D.40124, i.935
	add	r6, ip, r6, asl #2	@, tmp240, tmp309, tmp236,
	ldr	r6, [r6, #72]	@ tmp242, <variable>.Addr
	str	r6, [r5, #72]	@ tmp242, <variable>.Addr
	bne	.L128	@,
	cmp	sl, #1	@ SameImageFlag,
	add	r3, r3, #1	@ i.934, i.935,
	and	r2, r3, #63	@ prephitmp.919, i.934,
	strh	r2, [r8, #4]	@ movhi	@ prephitmp.919, <variable>.head
	beq	.L111	@,
.L114:
	ldrh	r2, [r8, #6]	@ <variable>.tail, <variable>.tail
	and	r3, r3, #63	@ i.935, i.934,
	cmp	r2, r3	@ <variable>.tail, i.935
	bne	.L121	@,
	ldrh	r2, [r8, #4]	@ prephitmp.919, <variable>.head
.L111:
	add	r0, r9, r0	@ tmp282, tmp307, InstID
	add	ip, ip, r0, asl #3	@, tmp284, tmp309, tmp282,
	add	r3, ip, #64	@ tmp285, tmp284,
	ldrsh	r1, [r3, #2]	@ <variable>.history, <variable>.history
	cmp	r2, r1	@ prephitmp.919, <variable>.history
	mvneq	r2, #0	@ movhi	@,
	streqh	r2, [r3, #2]	@ movhi	@, <variable>.history
	moveq	r3, #0	@ tmp295,
	streqb	r3, [ip, #64]	@ tmp295, <variable>.SwitchFlag
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L126:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2962	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC4	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC4	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L127:
	add	r0, r0, r0, asl #5	@, tmp154, InstID, InstID,
	movw	r3, #:lower16:.LANCHOR0	@ tmp149,
	movt	r3, #:upper16:.LANCHOR0	@ tmp149,
	ldr	ip, [r1, #88]	@ <variable>.top_luma_phy_addr, <variable>.top_luma_phy_addr
	add	r2, r3, r0, asl #3	@, tmp156, tmp149, tmp154,
	add	r2, r2, #64	@ tmp157, tmp156,
	ldrh	r1, [r2, #6]	@ <variable>.tail, <variable>.tail
	add	r0, r1, r0, asl #1	@, tmp163, <variable>.tail, tmp154,
	add	r1, r1, #1	@ tmp188, <variable>.tail,
	and	r1, r1, #63	@ tmp190, tmp188,
	strh	r1, [r2, #6]	@ movhi	@ tmp190, <variable>.tail
	add	r3, r3, r0, asl #2	@, tmp167, tmp149, tmp163,
	str	ip, [r3, #72]	@ <variable>.top_luma_phy_addr, <variable>.Addr
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L125:
	mov	r0, r1	@, p_image
	movw	r2, #2961	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r3, #:lower16:.LC3	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r3, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	.fnend
	.size	FSP_ProcFspQue, .-FSP_ProcFspQue
	.align	2
	.global	FSP_SetQueSwitchFlag
	.type	FSP_SetQueSwitchFlag, %function
FSP_SetQueSwitchFlag:
	.fnstart
.LFB1573:
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
	cmp	r0, #15	@ InstID,
	bhi	.L133	@,
	add	r0, r0, r0, asl #5	@, tmp140, InstID, InstID,
	movw	r1, #:lower16:.LANCHOR0	@ tmp136,
	movt	r1, #:upper16:.LANCHOR0	@ tmp136,
	mov	r2, #1	@ tmp144,
	add	r3, r1, r0, asl #3	@, tmp142, tmp136, tmp140,
	strb	r2, [r3, #64]	@ tmp144, <variable>.SwitchFlag
	ldmfd	sp, {fp, sp, pc}	@
.L133:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2836	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_SetQueSwitchFlag, .-FSP_SetQueSwitchFlag
	.align	2
	.global	FSP_GetQueSwitchFlag
	.type	FSP_GetQueSwitchFlag, %function
FSP_GetQueSwitchFlag:
	.fnstart
.LFB1572:
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
	cmp	r0, #15	@ InstID,
	bhi	.L138	@,
	add	r0, r0, r0, asl #5	@, tmp142, InstID, InstID,
	movw	r1, #:lower16:.LANCHOR0	@ tmp138,
	movt	r1, #:upper16:.LANCHOR0	@ tmp138,
	add	r3, r1, r0, asl #3	@, tmp144, tmp138, tmp142,
	ldrb	r0, [r3, #64]	@ zero_extendqisi2	@ D.40059, <variable>.SwitchFlag
	ldmfd	sp, {fp, sp, pc}	@
.L138:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2826	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mov	r0, #255	@ D.40059,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetQueSwitchFlag, .-FSP_GetQueSwitchFlag
	.align	2
	.global	FSP_PrintContext
	.type	FSP_PrintContext, %function
FSP_PrintContext:
	.fnstart
.LFB1571:
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
	cmp	r0, #15	@ InstID,
	bhi	.L162	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp151,
	movt	r3, #:upper16:.LANCHOR0	@ tmp151,
	ldr	r5, [r3, r0, asl #2]	@ D.39984, s_pFspInst
	cmp	r5, #0	@ D.39984,
	beq	.L163	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movt	r1, #:upper16:.LC5	@,
	mov	r8, r5	@ ivtmp.1029, D.39984
	bl	dprint_vfmw	@
	ldr	r3, [r5, #4]	@, <variable>.eFspInstState
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC6	@,
	movw	r2, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC6	@,
	movt	r2, #:upper16:.LC7	@,
	mov	r6, r5	@ ivtmp.1063, D.39984
	bl	dprint_vfmw	@
	ldr	r3, [r5, #68]	@, <variable>.stInstCfg.s32DecFsWidth
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC6	@,
	movw	r2, #:lower16:.LC8	@,
	movt	r1, #:upper16:.LC6	@,
	movt	r2, #:upper16:.LC8	@,
	mov	r7, #1	@ ivtmp.1026,
	bl	dprint_vfmw	@
	mov	r0, #0	@,
	mov	r4, r0	@ ivtmp.1025,
	ldr	r3, [r5, #72]	@, <variable>.stInstCfg.s32DecFsHeight
	movw	r1, #:lower16:.LC6	@,
	movw	r2, #:lower16:.LC9	@,
	movt	r1, #:upper16:.LC6	@,
	movt	r2, #:upper16:.LC9	@,
	bl	dprint_vfmw	@
	ldr	r3, [r5, #84]	@, <variable>.stInstCfg.s32DispFsWidth
	mov	r0, r4	@, ivtmp.1025
	movw	r1, #:lower16:.LC6	@,
	movw	r2, #:lower16:.LC10	@,
	movt	r1, #:upper16:.LC6	@,
	movt	r2, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	ldr	r3, [r5, #88]	@, <variable>.stInstCfg.s32DispFsHeight
	mov	r0, r4	@, ivtmp.1025
	movw	r1, #:lower16:.LC6	@,
	movw	r2, #:lower16:.LC11	@,
	movt	r1, #:upper16:.LC6	@,
	movt	r2, #:upper16:.LC11	@,
	bl	dprint_vfmw	@
	ldrsb	r3, [r5, #61]	@, <variable>.stInstCfg.s32ExpectedDecFsNum
	mov	r0, r4	@, ivtmp.1025
	movw	r1, #:lower16:.LC6	@,
	movw	r2, #:lower16:.LC12	@,
	movt	r1, #:upper16:.LC6	@,
	movt	r2, #:upper16:.LC12	@,
	bl	dprint_vfmw	@
	ldrsb	r3, [r5, #63]	@, <variable>.stInstCfg.s32ExpectedDispFsNum
	mov	r0, r4	@, ivtmp.1025
	movw	r1, #:lower16:.LC6	@,
	movw	r2, #:lower16:.LC13	@,
	movt	r1, #:upper16:.LC6	@,
	movt	r2, #:upper16:.LC13	@,
	bl	dprint_vfmw	@
	ldrsb	r3, [r5, #64]	@, <variable>.stInstCfg.s32ExpectedPmvNum
	mov	r0, r4	@, ivtmp.1025
	movw	r1, #:lower16:.LC6	@,
	movw	r2, #:lower16:.LC14	@,
	movt	r1, #:upper16:.LC6	@,
	movt	r2, #:upper16:.LC14	@,
	bl	dprint_vfmw	@
	ldrsb	r3, [r5, #10]	@, <variable>.s32DecFsNum
	mov	r0, r4	@, ivtmp.1025
	movw	r1, #:lower16:.LC6	@,
	movw	r2, #:lower16:.LC15	@,
	movt	r1, #:upper16:.LC6	@,
	movt	r2, #:upper16:.LC15	@,
	bl	dprint_vfmw	@
	ldrsb	r3, [r5, #11]	@, <variable>.s32DispFsNum
	mov	r0, r4	@, ivtmp.1025
	movw	r1, #:lower16:.LC6	@,
	movw	r2, #:lower16:.LC16	@,
	movt	r1, #:upper16:.LC6	@,
	movt	r2, #:upper16:.LC16	@,
	bl	dprint_vfmw	@
	ldrsb	r3, [r5, #13]	@, <variable>.s32PmvNum
	mov	r0, r4	@, ivtmp.1025
	movw	r1, #:lower16:.LC6	@,
	movw	r2, #:lower16:.LC17	@,
	movt	r1, #:upper16:.LC6	@,
	movt	r2, #:upper16:.LC17	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, ivtmp.1025
	movw	r1, #:lower16:.LC18	@,
	mov	r2, #64	@,
	movt	r1, #:upper16:.LC18	@,
	bl	dprint_vfmw	@
	b	.L143	@
.L166:
	ands	r0, r4, #7	@ tmp179, ivtmp.1025,
	beq	.L164	@,
	ldrsb	r2, [r6, #96]	@, <variable>.s32IsRef
	mov	r0, #0	@,
	ldrsb	r3, [r6, #97]	@, <variable>.s32DispState
	movw	r1, #:lower16:.LC19	@,
	movt	r1, #:upper16:.LC19	@,
	bl	dprint_vfmw	@
	cmp	r7, #63	@ ivtmp.1026,
	bgt	.L165	@,
.L146:
	add	r4, r4, #1	@ ivtmp.1025, ivtmp.1025,
	add	r7, r7, #1	@ ivtmp.1026, ivtmp.1026,
	add	r6, r6, #536	@ ivtmp.1063, ivtmp.1063,
.L143:
	cmp	r4, #0	@ ivtmp.1025,
	movw	r1, #:lower16:.LC19	@,
	mov	r0, r4	@, ivtmp.1025
	movt	r1, #:upper16:.LC19	@,
	bne	.L166	@,
	ldrsb	r2, [r6, #96]	@, <variable>.s32IsRef
	ldrsb	r3, [r6, #97]	@, <variable>.s32DispState
	bl	dprint_vfmw	@
	b	.L146	@
.L164:
	movw	r1, #:lower16:.LC20	@,
	movt	r1, #:upper16:.LC20	@,
	bl	dprint_vfmw	@
	ldrsb	r2, [r6, #96]	@, <variable>.s32IsRef
	mov	r0, #0	@,
	ldrsb	r3, [r6, #97]	@, <variable>.s32DispState
	movw	r1, #:lower16:.LC19	@,
	movt	r1, #:upper16:.LC19	@,
	bl	dprint_vfmw	@
	cmp	r7, #63	@ ivtmp.1026,
	ble	.L146	@,
.L165:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC21	@,
	ldrsb	r2, [r5, #10]	@, <variable>.s32DecFsNum
	movt	r1, #:upper16:.LC21	@,
	bl	dprint_vfmw	@
	ldrsb	r0, [r5, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	cmp	r0, #0	@ <variable>.s32DecFsNum,
	movgt	r4, #0	@ i,
	ble	.L147	@,
.L161:
	rsb	r3, r4, r4, asl #4	@, tmp191, i, i,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC19	@,
	movt	r1, #:upper16:.LC19	@,
	add	lr, r5, r3, asl #2	@, tmp193, D.39984, tmp191,
	add	r4, r4, #1	@ i, i,
	add	ip, lr, #34304	@ tmp194, tmp193,
	add	r2, ip, #152	@ tmp194, tmp194,
	ldrsb	r3, [r2, #6]	@, <variable>.DispState
	ldrsb	r2, [r2, #4]	@, <variable>.IsDecRef
	bl	dprint_vfmw	@
	ldrsb	r1, [r5, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	cmp	r1, r4	@ <variable>.s32DecFsNum, i
	ble	.L147	@,
	ands	r0, r4, #7	@ tmp186, i,
	bne	.L161	@,
	movw	r1, #:lower16:.LC20	@,
	movt	r1, #:upper16:.LC20	@,
	bl	dprint_vfmw	@
	b	.L161	@
.L147:
	ldrsb	r2, [r5, #11]	@, <variable>.s32DispFsNum
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC22	@,
	movt	r1, #:upper16:.LC22	@,
	bl	dprint_vfmw	@
	ldrsb	r0, [r5, #11]	@ <variable>.s32DispFsNum, <variable>.s32DispFsNum
	cmp	r0, #0	@ <variable>.s32DispFsNum,
	movgt	r2, #0	@ i.1062,
	movgt	r4, r2	@ i.1050, i.1062
	ble	.L151	@,
.L152:
	rsb	r3, r2, r2, asl #4	@, tmp213, i.1062, i.1062,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC19	@,
	movt	r1, #:upper16:.LC19	@,
	add	lr, r5, r3, asl #2	@, tmp215, D.39984, tmp213,
	add	r4, r4, #1	@ i.1050, i.1050,
	add	ip, lr, #38144	@ tmp216, tmp215,
	add	r2, ip, #152	@ tmp216, tmp216,
	ldrsb	r3, [r2, #6]	@, <variable>.DispState
	ldrsb	r2, [r2, #4]	@, <variable>.IsDecRef
	bl	dprint_vfmw	@
	ldrsb	r1, [r5, #11]	@ <variable>.s32DispFsNum, <variable>.s32DispFsNum
	cmp	r1, r4	@ <variable>.s32DispFsNum, i.1050
	ble	.L151	@,
	ands	r0, r4, #7	@ tmp208, i.1050,
	movne	r2, r4	@ i.1062, i.1050
	bne	.L152	@
.L167:
	movw	r1, #:lower16:.LC20	@,
	movt	r1, #:upper16:.LC20	@,
	bl	dprint_vfmw	@
	mov	r2, r4	@ i.1062, i.1050
	b	.L152	@
.L151:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC23	@,
	ldrsb	r2, [r5, #13]	@, <variable>.s32PmvNum
	movt	r1, #:upper16:.LC23	@,
	bl	dprint_vfmw	@
	ldrsb	r0, [r5, #13]	@ <variable>.s32PmvNum, <variable>.s32PmvNum
	cmp	r0, #0	@ <variable>.s32PmvNum,
	movgt	r4, #0	@ i.1056,
	ble	.L155	@,
.L156:
	ldrsb	r2, [r8, #14]	@, <variable>.IsPmvInUse
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC24	@,
	movt	r1, #:upper16:.LC24	@,
	bl	dprint_vfmw	@
	ldrsb	r1, [r5, #13]	@ <variable>.s32PmvNum, <variable>.s32PmvNum
	add	r4, r4, #1	@ i.1056, i.1056,
	add	r8, r8, #1	@ ivtmp.1029, ivtmp.1029,
	cmp	r1, r4	@ <variable>.s32PmvNum, i.1056
	ble	.L155	@,
	ands	r0, r4, #15	@ tmp230, i.1056,
	bne	.L156	@,
	movw	r1, #:lower16:.LC20	@,
	movt	r1, #:upper16:.LC20	@,
	bl	dprint_vfmw	@
	b	.L156	@
.L155:
	movw	r1, #:lower16:.LC25	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC25	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L162:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2669	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L163:
	mov	r0, r5	@, D.39984
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2670	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	.fnend
	.size	FSP_PrintContext, .-FSP_PrintContext
	.align	2
	.global	FSP_GetLogicIdByPhyAddr
	.type	FSP_GetLogicIdByPhyAddr, %function
FSP_GetLogicIdByPhyAddr:
	.fnstart
.LFB1570:
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
	cmp	r0, #15	@ InstID,
	bhi	.L180	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp142,
	movt	r3, #:upper16:.LANCHOR0	@ tmp142,
	ldr	r3, [r3, r0, asl #2]	@ D.39949, s_pFspInst
	cmp	r3, #0	@ D.39949,
	movne	r0, #0	@ i,
	beq	.L181	@,
.L173:
	ldr	r2, [r3, #608]	@ D.39953, <variable>.pstDecodeFs
	add	ip, r3, #536	@ tmp148, ivtmp.1097,
	cmp	r2, #0	@ D.39953,
	beq	.L172	@,
	ldr	r2, [r2, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	cmp	r2, r1	@ <variable>.PhyAddr, PhyAddr
	ldmeqfd	sp, {fp, sp, pc}	@
.L172:
	ldr	r3, [r3, #1144]	@ D.39953, <variable>.pstDecodeFs
	add	r0, r0, #1	@ i, i,
	cmp	r3, #0	@ D.39953,
	mov	r2, r0	@ tmp147, i
	beq	.L176	@,
	ldr	r3, [r3, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	cmp	r3, r1	@ <variable>.PhyAddr, PhyAddr
	ldmeqfd	sp, {fp, sp, pc}	@
.L176:
	add	r0, r2, #1	@ i, tmp147,
	add	r3, ip, #536	@ ivtmp.1097, tmp148,
	cmp	r0, #64	@ i,
	bne	.L173	@,
	mvn	r0, #0	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L181:
	mov	r0, r3	@, D.39949
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2615	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L180:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2614	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ i,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetLogicIdByPhyAddr, .-FSP_GetLogicIdByPhyAddr
	.align	2
	.global	FSP_GetPmvAddrTab
	.type	FSP_GetPmvAddrTab, %function
FSP_GetPmvAddrTab:
	.fnstart
.LFB1568:
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
	cmp	r0, #15	@ InstID,
	bhi	.L191	@,
	cmp	r2, #0	@ PmvAddrTab,
	beq	.L192	@,
	cmp	r1, #0	@ PmvNum,
	beq	.L193	@,
	movw	ip, #:lower16:.LANCHOR0	@ tmp146,
	movt	ip, #:upper16:.LANCHOR0	@ tmp146,
	ldr	r3, [ip, r0, asl #2]	@ tmp147, s_pFspInst
	cmp	r3, #0	@ tmp147,
	beq	.L194	@,
	mov	r3, #0	@ tmp150,
	str	r3, [r1, #0]	@ tmp150,* PmvNum
	ldr	ip, [ip, r0, asl #2]	@ pstInst, s_pFspInst
	ldrsb	r0, [ip, #13]	@ <variable>.s32PmvNum, <variable>.s32PmvNum
	str	r0, [r1, #0]	@ <variable>.s32PmvNum,* PmvNum
	ldrsb	r1, [ip, #13]	@ <variable>.s32PmvNum, <variable>.s32PmvNum
	cmp	r1, r3	@ <variable>.s32PmvNum,
	ldmlefd	sp, {fp, sp, pc}	@
	mov	r1, r3	@ i, ivtmp.1127
.L188:
	add	r0, ip, r3	@ tmp154, pstInst, ivtmp.1127
	add	r1, r1, #1	@ i, i,
	add	r0, r0, #42240	@ tmp156, tmp154,
	ldr	r0, [r0, #24]	@ tmp157, <variable>.PmvAddr
	str	r0, [r2, r3]	@ tmp157,* ivtmp.1127
	add	r3, r3, #4	@ ivtmp.1127, ivtmp.1127,
	ldrsb	r0, [ip, #13]	@ <variable>.s32PmvNum, <variable>.s32PmvNum
	cmp	r0, r1	@ <variable>.s32PmvNum, i
	bgt	.L188	@,
	ldmfd	sp, {fp, sp, pc}	@
.L191:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2531	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L192:
	mov	r0, r2	@, PmvAddrTab
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2532	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC26	@,
	movt	r3, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L193:
	mov	r0, r1	@, PmvNum
	movw	r2, #2533	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r3, #:lower16:.LC27	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r3, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L194:
	mov	r0, r3	@, tmp147
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2534	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetPmvAddrTab, .-FSP_GetPmvAddrTab
	.align	2
	.global	FSP_GetDecFsAddrTab
	.type	FSP_GetDecFsAddrTab, %function
FSP_GetDecFsAddrTab:
	.fnstart
.LFB1567:
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
	cmp	r0, #15	@ InstID,
	bhi	.L204	@,
	cmp	r2, #0	@ DecFsAddrTab,
	beq	.L205	@,
	cmp	r1, #0	@ DecFsNum,
	beq	.L206	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp153,
	movt	r4, #:upper16:.LANCHOR0	@ tmp153,
	ldr	ip, [r4, r0, asl #2]	@ tmp154, s_pFspInst
	cmp	ip, #0	@ tmp154,
	beq	.L207	@,
	mov	ip, #0	@ tmp158,
	str	ip, [r1, #0]	@ tmp158,* DecFsNum
	ldr	r5, [r4, r0, asl #2]	@ tmp160, s_pFspInst
	ldrsb	r5, [r5, #10]	@ D.39873, <variable>.s32DecFsNum
	cmp	r5, ip	@ D.39873,
	str	r5, [r1, #0]	@ D.39873,* DecFsNum
	ldr	r0, [r4, r0, asl #2]	@ temp.1173, s_pFspInst
	ldmlefd	sp, {r4, r5, fp, sp, pc}	@
	add	r0, r0, #34304	@ ivtmp.1162, temp.1173,
	mov	r4, ip	@ i, ivtmp.1166
	add	r0, r0, #168	@ ivtmp.1162, ivtmp.1162,
.L201:
	ldr	r5, [r0, #0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	add	r4, r4, #1	@ i, i,
	str	r5, [r2, ip]	@ <variable>.PhyAddr,* ivtmp.1166
	ldr	r5, [r0, #4]	@ <variable>.LineNumAddr, <variable>.LineNumAddr
	add	r0, r0, #60	@ ivtmp.1162, ivtmp.1162,
	str	r5, [r3, ip]	@ <variable>.LineNumAddr,* ivtmp.1166
	add	ip, ip, #4	@ ivtmp.1166, ivtmp.1166,
	ldr	r5, [r1, #0]	@ tmp165,* DecFsNum
	cmp	r5, r4	@ tmp165, i
	bgt	.L201	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L204:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2467	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L205:
	mov	r0, r2	@, DecFsAddrTab
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2468	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC28	@,
	movt	r3, #:upper16:.LC28	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L207:
	mov	r0, ip	@, tmp154
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2470	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L206:
	mov	r0, r1	@, DecFsNum
	movw	r2, #2469	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r3, #:lower16:.LC29	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r3, #:upper16:.LC29	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	FSP_GetDecFsAddrTab, .-FSP_GetDecFsAddrTab
	.align	2
	.global	FSP_GetStoreType
	.type	FSP_GetStoreType, %function
FSP_GetStoreType:
	.fnstart
.LFB1560:
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
	cmp	r0, #15	@ InstID,
	bhi	.L215	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp141,
	movt	r3, #:upper16:.LANCHOR0	@ tmp141,
	ldr	r0, [r3, r0, asl #2]	@ D.39714, s_pFspInst
	cmp	r0, #0	@ D.39714,
	beq	.L216	@,
	cmp	r1, #0	@ ePhyFsType,
	bne	.L212	@,
	ldrsb	r1, [r0, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	cmp	r1, r2	@ <variable>.s32DecFsNum, PhyFsID
	ble	.L213	@,
	rsb	r3, r2, r2, asl #4	@, tmp148, PhyFsID, PhyFsID,
	add	ip, r0, r3, asl #2	@, tmp150, D.39714, tmp148,
	add	r2, ip, #34304	@ tmp151, tmp150,
	add	r0, r2, #160	@ tmp151, tmp151,
	ldr	r0, [r0, #4]	@ eStoreType, <variable>.eStoreType
	ldmfd	sp, {fp, sp, pc}	@
.L212:
	cmp	r1, #1	@ ePhyFsType,
	beq	.L217	@,
.L213:
	mov	r0, #2	@ eStoreType,
	ldmfd	sp, {fp, sp, pc}	@
.L215:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2226	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ eStoreType,
	ldmfd	sp, {fp, sp, pc}	@
.L216:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2227	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ eStoreType,
	ldmfd	sp, {fp, sp, pc}	@
.L217:
	ldrsb	r1, [r0, #11]	@ <variable>.s32DispFsNum, <variable>.s32DispFsNum
	cmp	r2, r1	@ PhyFsID, <variable>.s32DispFsNum
	bge	.L213	@,
	rsb	r3, r2, r2, asl #4	@, tmp156, PhyFsID, PhyFsID,
	add	ip, r0, r3, asl #2	@, tmp158, D.39714, tmp156,
	add	r2, ip, #38144	@ tmp159, tmp158,
	add	r0, r2, #160	@ tmp159, tmp159,
	ldr	r0, [r0, #4]	@ eStoreType, <variable>.eStoreType
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetStoreType, .-FSP_GetStoreType
	.align	2
	.global	FSP_SetStoreType
	.type	FSP_SetStoreType, %function
FSP_SetStoreType:
	.fnstart
.LFB1559:
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
	cmp	r0, #15	@ InstID,
	bhi	.L225	@,
	movw	ip, #:lower16:.LANCHOR0	@ tmp142,
	movt	ip, #:upper16:.LANCHOR0	@ tmp142,
	ldr	ip, [ip, r0, asl #2]	@ D.39684, s_pFspInst
	cmp	ip, #0	@ D.39684,
	beq	.L226	@,
	cmp	r1, #0	@ ePhyFsType,
	bne	.L222	@,
	ldrsb	r0, [ip, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	cmp	r0, r2	@ <variable>.s32DecFsNum, PhyFsID
	ble	.L223	@,
	rsb	r2, r2, r2, asl #4	@, tmp149, PhyFsID, PhyFsID,
	mov	r0, r1	@ Ret, ePhyFsType
	add	ip, ip, r2, asl #2	@, tmp151, D.39684, tmp149,
	add	r2, ip, #34304	@ tmp152, tmp151,
	add	r1, r2, #160	@ tmp152, tmp152,
	str	r3, [r1, #4]	@ eStoreType, <variable>.eStoreType
	ldmfd	sp, {fp, sp, pc}	@
.L222:
	cmp	r1, #1	@ ePhyFsType,
	beq	.L227	@,
.L223:
	mvn	r0, #0	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
.L227:
	ldrsb	r0, [ip, #11]	@ <variable>.s32DispFsNum, <variable>.s32DispFsNum
	cmp	r2, r0	@ PhyFsID, <variable>.s32DispFsNum
	bge	.L223	@,
	rsb	r2, r2, r2, asl #4	@, tmp157, PhyFsID, PhyFsID,
	mov	r0, #0	@ Ret,
	add	r1, ip, r2, asl #2	@, tmp159, D.39684, tmp157,
	add	ip, r1, #38144	@ tmp160, tmp159,
	add	r1, ip, #160	@ tmp160, tmp160,
	str	r3, [r1, #4]	@ eStoreType, <variable>.eStoreType
	ldmfd	sp, {fp, sp, pc}	@
.L225:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2154	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
.L226:
	mov	r0, ip	@, D.39684
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2155	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_SetStoreType, .-FSP_SetStoreType
	.align	2
	.global	FSP_GetDisplay
	.type	FSP_GetDisplay, %function
FSP_GetDisplay:
	.fnstart
.LFB1558:
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
	ldr	r0, [r3, r0, asl #2]	@ D.39661, s_pFspInst
	cmp	r0, #0	@ D.39661,
	beq	.L232	@,
	mov	r2, #536	@ tmp143,
	mla	r1, r2, r1, r0	@ tmp144, tmp143, LogicFrameID, D.39661
	ldrsb	r0, [r1, #97]	@ D.39665, <variable>.s32DispState
	ldmfd	sp, {fp, sp, pc}	@
.L232:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2127	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39665,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetDisplay, .-FSP_GetDisplay
	.align	2
	.global	FSP_GetRef
	.type	FSP_GetRef, %function
FSP_GetRef:
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
	cmp	r0, #15	@ InstID,
	bhi	.L239	@,
	cmp	r1, #63	@ LogicFrameID,
	bhi	.L240	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp143,
	movt	r3, #:upper16:.LANCHOR0	@ tmp143,
	ldr	r0, [r3, r0, asl #2]	@ D.39594, s_pFspInst
	cmp	r0, #0	@ D.39594,
	beq	.L241	@,
	mov	r2, #536	@ tmp148,
	mla	r1, r2, r1, r0	@ tmp149, tmp148, LogicFrameID, D.39594
	ldrsb	r0, [r1, #96]	@ D.39589, <variable>.s32IsRef
	ldmfd	sp, {fp, sp, pc}	@
.L239:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2021	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC30	@,
	movt	r3, #:upper16:.LC30	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39589,
	ldmfd	sp, {fp, sp, pc}	@
.L240:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2022	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC31	@,
	movt	r3, #:upper16:.LC31	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39589,
	ldmfd	sp, {fp, sp, pc}	@
.L241:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2023	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC32	@,
	movt	r3, #:upper16:.LC32	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39589,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetRef, .-FSP_GetRef
	.align	2
	.global	FSP_SetRef
	.type	FSP_SetRef, %function
FSP_SetRef:
	.fnstart
.LFB1555:
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
	cmp	r0, #15	@ InstID,
	mov	r4, r1	@ LogicFrameID, LogicFrameID
	mov	r6, r2	@ IsRef, IsRef
	bhi	.L257	@,
	cmp	r1, #63	@ LogicFrameID,
	bhi	.L258	@,
	movw	r1, #:lower16:.LANCHOR0	@ tmp149,
	movt	r1, #:upper16:.LANCHOR0	@ tmp149,
	ldr	r5, [r1, r0, asl #2]	@ D.39511, s_pFspInst
	cmp	r5, #0	@ D.39511,
	beq	.L259	@,
	mov	r7, #536	@ tmp154,
	uxtb	r8, r2	@ D.39519, IsRef
	mla	r7, r7, r4, r5	@ tmp155, tmp154, LogicFrameID, D.39511
	ldrsb	r3, [r7, #98]	@ <variable>.IsDummyFs, <variable>.IsDummyFs
	strb	r8, [r7, #96]	@ D.39519, <variable>.s32IsRef
	cmp	r3, #0	@ <variable>.IsDummyFs,
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	ldr	r3, [r7, #608]	@ prephitmp.1286, <variable>.pstDecodeFs
	cmp	r3, #0	@ prephitmp.1286,
	beq	.L247	@,
	ldr	ip, [r3, #56]	@ <variable>.u32Tick, <variable>.u32Tick
	ldr	r1, [r7, #600]	@ <variable>.u32Tick, <variable>.u32Tick
	cmp	ip, r1	@ <variable>.u32Tick, <variable>.u32Tick
	beq	.L260	@,
.L247:
	mov	r0, #536	@ tmp194,
	mla	r3, r0, r4, r5	@ tmp195, tmp194, LogicFrameID, D.39511
	ldrb	r2, [r3, #100]	@ zero_extendqisi2	@ D.39539, <variable>.PmvIdc
	cmp	r2, #19	@ D.39539,
	bhi	.L250	@,
	cmp	r6, #1	@ IsRef,
	beq	.L261	@,
	cmp	r6, #0	@ IsRef,
	bne	.L252	@,
	add	r1, r3, #600	@ tmp220, tmp195,
	ldr	r0, [r1, #4]	@ <variable>.eLfsPmvState, <variable>.eLfsPmvState
	cmp	r0, #2	@ <variable>.eLfsPmvState,
	beq	.L262	@,
.L253:
	mov	r2, #536	@ tmp244,
	mla	r3, r2, r4, r5	@ tmp245, tmp244, LogicFrameID, D.39511
	ldr	r3, [r3, #612]	@ D.39562, <variable>.pstDispOutFs
	cmp	r3, #0	@ D.39562,
	beq	.L254	@,
	ldrsb	r1, [r3, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	r1, #1	@ <variable>.DispState,
	beq	.L263	@,
.L255:
	mov	r2, #536	@ tmp257,
	ldr	r0, [r3, #56]	@ <variable>.u32Tick, <variable>.u32Tick
	mla	r2, r2, r4, r5	@ tmp258, tmp257, LogicFrameID, D.39511
	ldr	r1, [r2, #600]	@ <variable>.u32Tick, <variable>.u32Tick
	cmp	r0, r1	@ <variable>.u32Tick, <variable>.u32Tick
	beq	.L264	@,
.L254:
	cmp	r6, #0	@ IsRef,
	moveq	r3, #536	@ tmp274,
	mlaeq	r4, r3, r4, r5	@ tmp275, tmp274, LogicFrameID, D.39511
	streq	r6, [r4, #608]	@ IsRef, <variable>.pstDecodeFs
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L257:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1875	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L261:
	add	r3, r3, #600	@ tmp202, tmp195,
	ldr	ip, [r3, #4]	@ <variable>.eLfsPmvState, <variable>.eLfsPmvState
	cmp	ip, #1	@ <variable>.eLfsPmvState,
	beq	.L265	@,
.L252:
	mov	r3, #536	@ tmp252,
	mla	ip, r3, r4, r5	@ tmp253, tmp252, LogicFrameID, D.39511
	ldr	r3, [ip, #612]	@ D.39562, <variable>.pstDispOutFs
	cmp	r3, #0	@ D.39562,
	bne	.L255	@,
	b	.L254	@
.L258:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1876	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC33	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L250:
	sxtb	r2, r2	@, D.39539
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC35	@,
	movt	r1, #:upper16:.LC35	@,
	bl	dprint_vfmw	@
	cmp	r6, #0	@ IsRef,
	beq	.L253	@,
	b	.L252	@
.L260:
	ldrsb	r1, [r3, #0]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	r1, r2	@ <variable>.IsDecRef, IsRef
	beq	.L248	@,
	movw	ip, #:lower16:.LANCHOR1	@ tmp177,
	movt	ip, #:upper16:.LANCHOR1	@ tmp177,
	ldr	r1, [ip, #-3896]	@ g_IsFrameIntfValid, g_IsFrameIntfValid
	cmp	r1, #0	@ g_IsFrameIntfValid,
	beq	.L248	@,
	ldr	ip, [ip, #-3880]	@ D.40267, g_FspFrameIntf.SetFrameRef
	ldr	r1, [r3, #12]	@ D.39537, <variable>.PhyAddr
	cmp	ip, #0	@ D.40267,
	beq	.L266	@,
	blx	ip	@ D.40267
	ldr	r3, [r7, #608]	@ prephitmp.1286, <variable>.pstDecodeFs
.L248:
	strb	r8, [r3, #0]	@ D.39519, <variable>.IsDecRef
	b	.L247	@
.L264:
	cmp	r6, #1	@ IsRef,
	bne	.L254	@,
	ldrsb	ip, [r3, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	ip, #1	@ <variable>.DispState,
	moveq	ip, #2	@ tmp263,
	streqb	ip, [r3, #2]	@ tmp263, <variable>.DispState
	streqb	ip, [r2, #97]	@ tmp263, <variable>.s32DispState
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L263:
	mov	r0, #0	@ tmp248,
	strb	r0, [r3, #2]	@ tmp248, <variable>.DispState
	b	.L252	@
.L262:
	sxtab	ip, r5, r2	@ tmp224, D.39511, D.39539
	strb	r6, [ip, #14]	@ IsRef, <variable>.IsPmvInUse
	str	r6, [r3, #620]	@ IsRef, <variable>.PmvAddr
	str	r6, [r1, #4]	@ IsRef, <variable>.eLfsPmvState
	b	.L253	@
.L259:
	mov	r0, r5	@, D.39511
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1877	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L265:
	sxtab	r1, r5, r2	@ tmp206, D.39511, D.39539
	mov	r2, #2	@ tmp215,
	strb	r6, [r1, #14]	@ IsRef, <variable>.IsPmvInUse
	str	r2, [r3, #4]	@ tmp215, <variable>.eLfsPmvState
	b	.L252	@
.L266:
	mov	r0, ip	@, D.40267
	movw	r1, #:lower16:.LC34	@,
	movt	r1, #:upper16:.LC34	@,
	bl	dprint_vfmw	@
	ldr	r3, [r7, #608]	@ prephitmp.1286, <variable>.pstDecodeFs
	strb	r8, [r3, #0]	@ D.39519, <variable>.IsDecRef
	b	.L247	@
	.fnend
	.size	FSP_SetRef, .-FSP_SetRef
	.align	2
	.global	FSP_RemovePmv
	.type	FSP_RemovePmv, %function
FSP_RemovePmv:
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
	cmp	r0, #15	@ InstID,
	bhi	.L274	@,
	cmp	r1, #63	@ LogicFrameID,
	bhi	.L275	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp142,
	movt	r3, #:upper16:.LANCHOR0	@ tmp142,
	ldr	r0, [r3, r0, asl #2]	@ D.39482, s_pFspInst
	cmp	r0, #0	@ D.39482,
	beq	.L276	@,
	mov	r2, #536	@ tmp147,
	mla	r3, r2, r1, r0	@ tmp148, tmp147, LogicFrameID, D.39482
	ldr	r2, [r3, #604]	@ <variable>.eLfsPmvState, <variable>.eLfsPmvState
	cmp	r2, #2	@ <variable>.eLfsPmvState,
	ldmnefd	sp, {fp, sp, pc}	@
	ldrb	ip, [r3, #100]	@ zero_extendqisi2	@ D.39490, <variable>.PmvIdc
	mov	r3, #536	@ tmp165,
	cmp	ip, #19	@ D.39490,
	sxtabls	ip, r0, ip	@ tmp159, D.39482, D.39490
	addls	ip, ip, #8	@ tmp160, tmp159,
	movls	r2, #0	@ tmp161,
	strlsb	r2, [ip, #6]	@ tmp161, <variable>.IsPmvInUse
	mla	ip, r3, r1, r0	@ tmp166, tmp165, LogicFrameID, D.39482
	mov	r0, #0	@ tmp168,
	add	r1, ip, #600	@ tmp167, tmp166,
	str	r0, [r1, #4]	@ tmp168, <variable>.eLfsPmvState
	ldmfd	sp, {fp, sp, pc}	@
.L274:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1828	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L275:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1829	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC33	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L276:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1830	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_RemovePmv, .-FSP_RemovePmv
	.align	2
	.global	FSP_FirstFsCheck
	.type	FSP_FirstFsCheck, %function
FSP_FirstFsCheck:
	.fnstart
.LFB1552:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r3, #:lower16:.LANCHOR0	@ tmp185,
	movt	r3, #:upper16:.LANCHOR0	@ tmp185,
	ldr	ip, [r3, r0, asl #2]	@ D.39189, s_pFspInst
	cmp	ip, #0	@ D.39189,
	beq	.L286	@,
	add	r0, r0, r0, asl #5	@, tmp153, InstID, InstID,
	add	r2, r3, r0, asl #3	@, tmp155, tmp185, tmp153,
	add	r2, r2, #64	@ tmp156, tmp155,
	ldrsh	r4, [r2, #2]	@ D.39196, <variable>.history
	cmn	r4, #1	@ D.39196,
	beq	.L280	@,
	ldrh	r2, [r2, #4]	@ i, <variable>.head
	cmp	r2, r4	@ i, D.39196
	beq	.L280	@,
	ldr	r5, [ip, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	movw	r6, #34532	@ tmp166,
	ldr	r7, [ip, r6]	@ <variable>.PhyAddr, <variable>.PhyAddr
	cmp	r5, #1	@ <variable>.eFspInstState,
	movw	r5, #34472	@ tmp167,
	ldr	r6, [ip, r5]	@ <variable>.PhyAddr, <variable>.PhyAddr
	ldr	r5, [ip, #52]	@ PreSlotLen, <variable>.stPreInfo.s32PreDecSlotLen
	rsb	r7, r6, r7	@ SlotLen, <variable>.PhyAddr, <variable>.PhyAddr
	beq	.L287	@,
.L281:
	mov	r0, #0	@ ret,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L280:
	mov	r0, #0	@ ret,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L287:
	and	r2, r2, #63	@ i.1354, i,
	cmp	r4, r2	@ D.39196, i.1354
	beq	.L281	@,
	mov	r6, r0, asl #1	@ tmp188, tmp153,
	add	r7, r1, r7	@ tmp189, DecPhyAddr, SlotLen
.L285:
	add	r0, r6, r2	@ tmp176, tmp188, i.1354
	add	r2, r2, #1	@ i.1355, i.1354,
	and	r2, r2, #63	@ i.1354, i.1355,
	add	ip, r3, r0, asl #2	@, tmp180, tmp185, tmp176,
	ldr	ip, [ip, #72]	@ D.39208, <variable>.Addr
	add	r0, ip, r5	@ tmp182, D.39208, PreSlotLen
	cmp	r0, r1	@ tmp182, DecPhyAddr
	blt	.L282	@,
	cmp	ip, r7	@ D.39208, tmp189
	ble	.L288	@,
.L282:
	cmp	r4, r2	@ D.39196, i.1354
	bne	.L285	@,
	mov	r0, #0	@ ret,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L288:
	mov	r0, #1	@ ret,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L286:
	mov	r0, ip	@, D.39189
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1435	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	FSP_FirstFsCheck, .-FSP_FirstFsCheck
	.align	2
	.global	FSP_GetDecodePmvTable
	.type	FSP_GetDecodePmvTable, %function
FSP_GetDecodePmvTable:
	.fnstart
.LFB1548:
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
	cmp	r0, #15	@ InstID,
	bhi	.L298	@,
	cmp	r1, #0	@ PhyAddr,
	beq	.L299	@,
	cmp	r2, #0	@ pPmvNum,
	beq	.L300	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp145,
	movt	r3, #:upper16:.LANCHOR0	@ tmp145,
	ldr	r0, [r3, r0, asl #2]	@ D.39062, s_pFspInst
	cmp	r0, #0	@ D.39062,
	beq	.L301	@,
	ldrsb	ip, [r0, #13]	@ <variable>.s32PmvNum, <variable>.s32PmvNum
	str	ip, [r2, #0]	@ <variable>.s32PmvNum,* pPmvNum
	ldrsb	r2, [r0, #13]	@ <variable>.s32PmvNum, <variable>.s32PmvNum
	cmp	r2, #0	@ <variable>.s32PmvNum,
	ldmlefd	sp, {fp, sp, pc}	@
	mov	r3, #0	@ ivtmp.1384,
	mov	r2, r3	@ i, ivtmp.1384
.L295:
	add	ip, r0, r3	@ tmp150, D.39062, ivtmp.1384
	add	r2, r2, #1	@ i, i,
	add	ip, ip, #42240	@ tmp152, tmp150,
	ldr	ip, [ip, #24]	@ tmp153, <variable>.PmvAddr
	str	ip, [r1, r3]	@ tmp153,* ivtmp.1384
	add	r3, r3, #4	@ ivtmp.1384, ivtmp.1384,
	ldrsb	ip, [r0, #13]	@ <variable>.s32PmvNum, <variable>.s32PmvNum
	cmp	ip, r2	@ <variable>.s32PmvNum, i
	bgt	.L295	@,
	ldmfd	sp, {fp, sp, pc}	@
.L298:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1048	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L299:
	mov	r0, r1	@, PhyAddr
	movw	r2, #1049	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r3, #:lower16:.LC36	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r3, #:upper16:.LC36	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L300:
	mov	r0, r2	@, pPmvNum
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1050	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC37	@,
	movt	r3, #:upper16:.LC37	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L301:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1051	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetDecodePmvTable, .-FSP_GetDecodePmvTable
	.align	2
	.global	FSP_GetDecodeFrameTable
	.type	FSP_GetDecodeFrameTable, %function
FSP_GetDecodeFrameTable:
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
	cmp	r0, #15	@ InstID,
	bhi	.L311	@,
	cmp	r1, #0	@ PhyAddr,
	beq	.L312	@,
	cmp	r2, #0	@ pFsNum,
	beq	.L313	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp147,
	movt	r3, #:upper16:.LANCHOR0	@ tmp147,
	ldr	r0, [r3, r0, asl #2]	@ D.39032, s_pFspInst
	cmp	r0, #0	@ D.39032,
	beq	.L314	@,
	ldrsb	ip, [r0, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	str	ip, [r2, #0]	@ <variable>.s32DecFsNum,* pFsNum
	ldrsb	r2, [r0, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	cmp	r2, #0	@ <variable>.s32DecFsNum,
	ldmlefd	sp, {fp, sp, pc}	@
	add	r2, r0, #34304	@ ivtmp.1419, D.39032,
	mov	r3, #0	@ i,
	add	r2, r2, #168	@ ivtmp.1419, ivtmp.1419,
.L308:
	ldr	ip, [r2], #60	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	ip, [r1, r3, asl #2]	@ <variable>.PhyAddr,* PhyAddr
	add	r3, r3, #1	@ i, i,
	ldrsb	ip, [r0, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	cmp	ip, r3	@ <variable>.s32DecFsNum, i
	bgt	.L308	@,
	ldmfd	sp, {fp, sp, pc}	@
.L311:
	movw	r1, #:lower16:.LC0	@,
	mov	r2, #992	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L312:
	mov	r0, r1	@, PhyAddr
	movw	r2, #993	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r3, #:lower16:.LC36	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r3, #:upper16:.LC36	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L314:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #995	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L313:
	mov	r0, r2	@, pFsNum
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #994	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC37	@,
	movt	r3, #:upper16:.LC37	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_GetDecodeFrameTable, .-FSP_GetDecodeFrameTable
	.align	2
	.global	FSP_DisableInstance
	.type	FSP_DisableInstance, %function
FSP_DisableInstance:
	.fnstart
.LFB1540:
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
	cmp	r0, #15	@ InstID,
	bhi	.L320	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	ldr	r0, [r3, r0, asl #2]	@ D.38644, s_pFspInst
	cmp	r0, #0	@ D.38644,
	beq	.L321	@,
	ldr	r1, [r0, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r1, #1	@ <variable>.eFspInstState,
	moveq	r1, #0	@ tmp141,
	streq	r1, [r0, #4]	@ tmp141, <variable>.eFspInstState
	ldmfd	sp, {fp, sp, pc}	@
.L320:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #319	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L321:
	movw	r1, #:lower16:.LC0	@,
	mov	r2, #320	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_DisableInstance, .-FSP_DisableInstance
	.align	2
	.global	FSP_Exit
	.type	FSP_Exit, %function
FSP_Exit:
	.fnstart
.LFB1536:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp181,
	movt	r4, #:upper16:.LANCHOR0	@ tmp181,
	ldr	r3, [r4, #0]	@ temp.1478, s_pFspInst
	cmp	r3, #0	@ temp.1478,
	beq	.L323	@,
	ldr	r3, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r3, #0	@ <variable>.eFspInstState,
	bne	.L340	@,
.L323:
	ldr	r3, [r4, #4]	@ temp.1480, s_pFspInst
	cmp	r3, #0	@ temp.1480,
	beq	.L324	@,
	ldr	r0, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r0, #0	@ <variable>.eFspInstState,
	bne	.L341	@,
.L324:
	ldr	r3, [r4, #8]	@ temp.1482, s_pFspInst
	cmp	r3, #0	@ temp.1482,
	beq	.L325	@,
	ldr	r1, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r1, #0	@ <variable>.eFspInstState,
	bne	.L342	@,
.L325:
	ldr	r3, [r4, #12]	@ temp.1484, s_pFspInst
	cmp	r3, #0	@ temp.1484,
	beq	.L326	@,
	ldr	r2, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r2, #0	@ <variable>.eFspInstState,
	bne	.L343	@,
.L326:
	ldr	r3, [r4, #16]	@ temp.1486, s_pFspInst
	cmp	r3, #0	@ temp.1486,
	beq	.L327	@,
	ldr	ip, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	ip, #0	@ <variable>.eFspInstState,
	bne	.L344	@,
.L327:
	ldr	r3, [r4, #20]	@ temp.1488, s_pFspInst
	cmp	r3, #0	@ temp.1488,
	beq	.L328	@,
	ldr	r3, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r3, #0	@ <variable>.eFspInstState,
	bne	.L345	@,
.L328:
	ldr	r3, [r4, #24]	@ temp.1490, s_pFspInst
	cmp	r3, #0	@ temp.1490,
	beq	.L329	@,
	ldr	r0, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r0, #0	@ <variable>.eFspInstState,
	bne	.L346	@,
.L329:
	ldr	r3, [r4, #28]	@ temp.1492, s_pFspInst
	cmp	r3, #0	@ temp.1492,
	beq	.L330	@,
	ldr	r1, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r1, #0	@ <variable>.eFspInstState,
	bne	.L347	@,
.L330:
	ldr	r3, [r4, #32]	@ temp.1494, s_pFspInst
	cmp	r3, #0	@ temp.1494,
	beq	.L331	@,
	ldr	r2, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r2, #0	@ <variable>.eFspInstState,
	bne	.L348	@,
.L331:
	ldr	r3, [r4, #36]	@ temp.1496, s_pFspInst
	cmp	r3, #0	@ temp.1496,
	beq	.L332	@,
	ldr	ip, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	ip, #0	@ <variable>.eFspInstState,
	bne	.L349	@,
.L332:
	ldr	r3, [r4, #40]	@ temp.1498, s_pFspInst
	cmp	r3, #0	@ temp.1498,
	beq	.L333	@,
	ldr	r3, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r3, #0	@ <variable>.eFspInstState,
	bne	.L350	@,
.L333:
	ldr	r3, [r4, #44]	@ temp.1500, s_pFspInst
	cmp	r3, #0	@ temp.1500,
	beq	.L334	@,
	ldr	r0, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r0, #0	@ <variable>.eFspInstState,
	bne	.L351	@,
.L334:
	ldr	r3, [r4, #48]	@ temp.1502, s_pFspInst
	cmp	r3, #0	@ temp.1502,
	beq	.L335	@,
	ldr	r1, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r1, #0	@ <variable>.eFspInstState,
	bne	.L352	@,
.L335:
	ldr	r3, [r4, #52]	@ temp.1504, s_pFspInst
	cmp	r3, #0	@ temp.1504,
	beq	.L336	@,
	ldr	r2, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r2, #0	@ <variable>.eFspInstState,
	bne	.L353	@,
.L336:
	ldr	r3, [r4, #56]	@ temp.1506, s_pFspInst
	cmp	r3, #0	@ temp.1506,
	beq	.L337	@,
	ldr	ip, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	ip, #0	@ <variable>.eFspInstState,
	bne	.L354	@,
.L337:
	ldr	r3, [r4, #60]	@ D.38568, s_pFspInst
	cmp	r3, #0	@ D.38568,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
.L355:
	ldr	r3, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r3, #0	@ <variable>.eFspInstState,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	mov	r0, #15	@,
	bl	FSP_DisableInstance	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L354:
	mov	r0, #14	@,
	bl	FSP_DisableInstance	@
	ldr	r3, [r4, #60]	@ D.38568, s_pFspInst
	cmp	r3, #0	@ D.38568,
	bne	.L355	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L353:
	mov	r0, #13	@,
	bl	FSP_DisableInstance	@
	b	.L336	@
.L352:
	mov	r0, #12	@,
	bl	FSP_DisableInstance	@
	b	.L335	@
.L351:
	mov	r0, #11	@,
	bl	FSP_DisableInstance	@
	b	.L334	@
.L350:
	mov	r0, #10	@,
	bl	FSP_DisableInstance	@
	b	.L333	@
.L349:
	mov	r0, #9	@,
	bl	FSP_DisableInstance	@
	b	.L332	@
.L348:
	mov	r0, #8	@,
	bl	FSP_DisableInstance	@
	b	.L331	@
.L347:
	mov	r0, #7	@,
	bl	FSP_DisableInstance	@
	b	.L330	@
.L346:
	mov	r0, #6	@,
	bl	FSP_DisableInstance	@
	b	.L329	@
.L345:
	mov	r0, #5	@,
	bl	FSP_DisableInstance	@
	b	.L328	@
.L344:
	mov	r0, #4	@,
	bl	FSP_DisableInstance	@
	b	.L327	@
.L343:
	mov	r0, #3	@,
	bl	FSP_DisableInstance	@
	b	.L326	@
.L342:
	mov	r0, #2	@,
	bl	FSP_DisableInstance	@
	b	.L325	@
.L341:
	mov	r0, #1	@,
	bl	FSP_DisableInstance	@
	b	.L324	@
.L340:
	mov	r0, #0	@,
	bl	FSP_DisableInstance	@
	b	.L323	@
	.fnend
	.size	FSP_Exit, .-FSP_Exit
	.align	2
	.global	FSP_ConfigAttribute
	.type	FSP_ConfigAttribute, %function
FSP_ConfigAttribute:
	.fnstart
.LFB1537:
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
	cmp	r0, #15	@ InstID,
	bhi	.L361	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r3, [r3, r0, asl #2]	@ D.38585, s_pFspInst
	ldr	r2, [r3, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r2, #1	@ <variable>.eFspInstState,
	bne	.L362	@,
	ldrb	ip, [r1, #0]	@ zero_extendqisi2	@ <variable>.s8LowBufEnable, <variable>.s8LowBufEnable
	mov	r0, #0	@ D.38583,
	strb	ip, [r3, #1]	@ <variable>.s8LowBufEnable, <variable>.s8LowBufEnable
	ldmfd	sp, {fp, sp, pc}	@
.L362:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	mov	r2, #254	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC38	@,
	movt	r3, #:upper16:.LC38	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38583,
	ldmfd	sp, {fp, sp, pc}	@
.L361:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	mov	r2, #253	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38583,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FSP_ConfigAttribute, .-FSP_ConfigAttribute
	.align	2
	.global	FSP_UdateInfo
	.type	FSP_UdateInfo, %function
FSP_UdateInfo:
	.fnstart
.LFB1528:
	@ args = 0, pretend = 0, frame = 944
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #968
	sub	sp, sp, #968	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ InstID,
	mov	r5, r1	@ Width, Width
	mov	r4, r2	@ Height, Height
	bhi	.L372	@,
	movw	r2, #:lower16:g_vdm_hal_fun_ptr	@ tmp153,
	movt	r2, #:upper16:g_vdm_hal_fun_ptr	@ tmp153,
	movw	r3, #:lower16:.LANCHOR0	@ tmp152,
	movt	r3, #:upper16:.LANCHOR0	@ tmp152,
	ldr	ip, [r2, #36]	@ D.38461, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	ldr	r6, [r3, r0, asl #2]	@ pstInst, s_pFspInst
	cmp	ip, #0	@ D.38461,
	beq	.L366	@,
	mov	r1, #10	@ tmp154,
	str	r0, [sp, #12]	@ InstID,
	str	r1, [sp, #4]	@ tmp154,
	mov	lr, #0	@ tmp156,
	sub	r0, fp, #968	@ tmp158,,
	str	r1, [sp, #0]	@ tmp154,
	str	r0, [sp, #16]	@ tmp158,
	mvn	r1, #-2147483648	@,
	str	lr, [sp, #8]	@ tmp156,
	mov	r0, #1024	@,
	mov	r2, r5	@, Width
	mov	r3, r4	@, Height
	blx	ip	@ D.38461
	cmp	r0, #0	@,
	bne	.L366	@,
	add	ip, r6, #38144	@ ivtmp.1570, pstInst,
	add	r7, r6, #34304	@ ivtmp.1562, pstInst,
	add	r2, ip, #176	@ ivtmp.1570, ivtmp.1570,
	add	r3, r7, #176	@ ivtmp.1562, ivtmp.1562,
	mov	ip, r2	@ D.41350, ivtmp.1570
.L368:
	ldr	r7, [fp, #-968]	@ MemArrange.VahbStride, MemArrange.VahbStride
	add	r0, r3, #60	@ tmp194, ivtmp.1562,
	str	r5, [r3, #16]	@ Width, <variable>.FsWidth
	add	r1, r2, #60	@ tmp195, ivtmp.1570,
	str	r4, [r3, #20]	@ Height, <variable>.FsHeight
	str	r7, [r3, #0]	@ MemArrange.VahbStride, <variable>.Stride
	ldr	lr, [fp, #-432]	@ MemArrange.ChromOffset, MemArrange.ChromOffset
	str	lr, [r3, #24]	@ MemArrange.ChromOffset, <variable>.ChromOffset
	ldr	r7, [fp, #-428]	@ MemArrange.LumaPixelOffset, MemArrange.LumaPixelOffset
	str	r7, [r3, #28]	@ MemArrange.LumaPixelOffset, <variable>.LumaPixelOffset
	ldr	lr, [fp, #-424]	@ MemArrange.ChromaPixelOffset, MemArrange.ChromaPixelOffset
	str	lr, [r3, #32]	@ MemArrange.ChromaPixelOffset, <variable>.ChromaPixelOffset
	ldr	r7, [fp, #-968]	@ MemArrange.VahbStride, MemArrange.VahbStride
	str	r5, [r2, #16]	@ Width, <variable>.FsWidth
	str	r4, [r2, #20]	@ Height, <variable>.FsHeight
	str	r7, [r2, #0]	@ MemArrange.VahbStride, <variable>.Stride
	ldr	lr, [fp, #-432]	@ MemArrange.ChromOffset, MemArrange.ChromOffset
	str	lr, [r2, #24]	@ MemArrange.ChromOffset, <variable>.ChromOffset
	ldr	r7, [fp, #-428]	@ MemArrange.LumaPixelOffset, MemArrange.LumaPixelOffset
	str	r7, [r2, #28]	@ MemArrange.LumaPixelOffset, <variable>.LumaPixelOffset
	ldr	lr, [fp, #-424]	@ MemArrange.ChromaPixelOffset, MemArrange.ChromaPixelOffset
	str	lr, [r2, #32]	@ MemArrange.ChromaPixelOffset, <variable>.ChromaPixelOffset
	ldr	r7, [fp, #-968]	@ MemArrange.VahbStride, MemArrange.VahbStride
	str	r5, [r0, #16]	@ Width, <variable>.FsWidth
	str	r4, [r0, #20]	@ Height, <variable>.FsHeight
	str	r7, [r3, #60]	@ MemArrange.VahbStride, <variable>.Stride
	add	r3, r3, #120	@ ivtmp.1562, ivtmp.1562,
	ldr	lr, [fp, #-432]	@ MemArrange.ChromOffset, MemArrange.ChromOffset
	cmp	r3, ip	@ ivtmp.1562, D.41350
	str	lr, [r0, #24]	@ MemArrange.ChromOffset, <variable>.ChromOffset
	ldr	r7, [fp, #-428]	@ MemArrange.LumaPixelOffset, MemArrange.LumaPixelOffset
	str	r7, [r0, #28]	@ MemArrange.LumaPixelOffset, <variable>.LumaPixelOffset
	ldr	r7, [fp, #-424]	@ MemArrange.ChromaPixelOffset, MemArrange.ChromaPixelOffset
	str	r7, [r0, #32]	@ MemArrange.ChromaPixelOffset, <variable>.ChromaPixelOffset
	ldr	lr, [fp, #-968]	@ MemArrange.VahbStride, MemArrange.VahbStride
	str	r5, [r1, #16]	@ Width, <variable>.FsWidth
	str	lr, [r2, #60]	@ MemArrange.VahbStride, <variable>.Stride
	add	r2, r2, #120	@ ivtmp.1570, ivtmp.1570,
	str	r4, [r1, #20]	@ Height, <variable>.FsHeight
	ldr	r0, [fp, #-432]	@ MemArrange.ChromOffset, MemArrange.ChromOffset
	str	r0, [r1, #24]	@ MemArrange.ChromOffset, <variable>.ChromOffset
	ldr	lr, [fp, #-428]	@ MemArrange.LumaPixelOffset, MemArrange.LumaPixelOffset
	str	lr, [r1, #28]	@ MemArrange.LumaPixelOffset, <variable>.LumaPixelOffset
	ldr	r0, [fp, #-424]	@ MemArrange.ChromaPixelOffset, MemArrange.ChromaPixelOffset
	str	r0, [r1, #32]	@ MemArrange.ChromaPixelOffset, <variable>.ChromaPixelOffset
	bne	.L368	@,
	ldr	lr, [fp, #-968]	@ MemArrange.VahbStride, MemArrange.VahbStride
	movw	r2, #42176	@ tmp173,
	movw	r3, #42160	@ tmp171,
	movw	r1, #42180	@ tmp174,
	str	r5, [r6, r2]	@ Width, <variable>.FsWidth
	movw	ip, #42184	@ tmp175,
	str	lr, [r6, r3]	@ MemArrange.VahbStride, <variable>.Stride
	movw	r2, #42188	@ tmp177,
	str	r4, [r6, r1]	@ Height, <variable>.FsHeight
	movw	r3, #42192	@ tmp179,
	ldr	r0, [fp, #-432]	@ MemArrange.ChromOffset, MemArrange.ChromOffset
	str	r0, [r6, ip]	@ MemArrange.ChromOffset, <variable>.ChromOffset
	movw	ip, #42260	@ tmp181,
	ldr	lr, [fp, #-428]	@ MemArrange.LumaPixelOffset, MemArrange.LumaPixelOffset
	mov	r0, #0	@ D.38458,
	str	lr, [r6, r2]	@ MemArrange.LumaPixelOffset, <variable>.LumaPixelOffset
	movw	lr, #34436	@ tmp185,
	ldr	r1, [fp, #-424]	@ MemArrange.ChromaPixelOffset, MemArrange.ChromaPixelOffset
	str	r1, [r6, r3]	@ MemArrange.ChromaPixelOffset, <variable>.ChromaPixelOffset
	movw	r1, #34440	@ tmp186,
	ldr	r2, [fp, #-36]	@ MemArrange.HafPmvOffset, MemArrange.HafPmvOffset
	movw	r3, #34420	@ tmp183,
	str	r2, [r6, ip]	@ MemArrange.HafPmvOffset, <variable>.s32HalfPmvOffset
	movw	r2, #34444	@ tmp187,
	ldr	ip, [fp, #-968]	@ MemArrange.VahbStride, MemArrange.VahbStride
	str	r4, [r6, r1]	@ Height, <variable>.stDummyPhyFs.FsHeight
	movw	r1, #34448	@ tmp189,
	str	r5, [r6, lr]	@ Width, <variable>.stDummyPhyFs.FsWidth
	str	ip, [r6, r3]	@ MemArrange.VahbStride, <variable>.stDummyPhyFs.Stride
	movw	r3, #34452	@ tmp191,
	ldr	lr, [fp, #-432]	@ MemArrange.ChromOffset, MemArrange.ChromOffset
	str	lr, [r6, r2]	@ MemArrange.ChromOffset, <variable>.stDummyPhyFs.ChromOffset
	ldr	ip, [fp, #-428]	@ MemArrange.LumaPixelOffset, MemArrange.LumaPixelOffset
	str	ip, [r6, r1]	@ MemArrange.LumaPixelOffset, <variable>.stDummyPhyFs.LumaPixelOffset
	ldr	r2, [fp, #-424]	@ MemArrange.ChromaPixelOffset, MemArrange.ChromaPixelOffset
	str	r2, [r6, r3]	@ MemArrange.ChromaPixelOffset, <variable>.stDummyPhyFs.ChromaPixelOffset
.L365:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L372:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	mov	r2, #92	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38458,
	b	.L365	@
.L366:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC39	@,
	movt	r1, #:upper16:.LC39	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38458,
	b	.L365	@
	.fnend
	.size	FSP_UdateInfo, .-FSP_UdateInfo
	.align	2
	.global	FSP_GetInstInfo
	.type	FSP_GetInstInfo, %function
FSP_GetInstInfo:
	.fnstart
.LFB1569:
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
	movw	r2, #:lower16:.LANCHOR0	@ tmp136,
	movt	r2, #:upper16:.LANCHOR0	@ tmp136,
	mov	r3, r1	@ pFspInstInfo, pFspInstInfo
	ldr	ip, [r2, r0, asl #2]	@ D.39919, s_pFspInst
	cmp	ip, #0	@ D.39919,
	beq	.L377	@,
	ldrb	r4, [ip, #10]	@ zero_extendqisi2	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	movw	lr, #34532	@ tmp141,
	mov	r0, r1	@ tmp154, pFspInstInfo
	add	r1, ip, #34304	@, D.39919,
	mov	r2, #3840	@,
	add	r1, r1, #156	@,,
	strb	r4, [r3, #1]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	ldr	r4, [ip, lr]	@ <variable>.PhyAddr, <variable>.PhyAddr
	movw	lr, #34472	@ tmp142,
	ldr	lr, [ip, lr]	@ <variable>.PhyAddr, <variable>.PhyAddr
	rsb	lr, lr, r4	@ tmp145, <variable>.PhyAddr, <variable>.PhyAddr
	str	lr, [r3, #3848]	@ tmp145, <variable>.s32DecFsSize
	ldrb	lr, [ip, #11]	@ zero_extendqisi2	@ <variable>.s32DispFsNum, <variable>.s32DispFsNum
	strb	lr, [r3, #2]	@ <variable>.s32DispFsNum, <variable>.s32DispFsNum
	ldrb	lr, [ip, #12]	@ zero_extendqisi2	@ <variable>.s32TfFsNum, <variable>.s32TfFsNum
	strb	lr, [r3, #3]	@ <variable>.s32TfFsNum, <variable>.s32TfFsNum
	ldrb	lr, [ip, #0]	@ zero_extendqisi2	@ <variable>.s32InstID, <variable>.s32InstID
	strb	lr, [r3, #4]	@ <variable>.s32InstID, <variable>.s32InstID
	ldrb	r3, [ip, #13]	@ zero_extendqisi2	@ <variable>.s32PmvNum, <variable>.s32PmvNum
	strb	r3, [r0], #8	@ <variable>.s32PmvNum, <variable>.s32PmvNum
	bl	memcpy	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L377:
	mov	r0, ip	@, D.39919
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2566	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	FSP_GetInstInfo, .-FSP_GetInstInfo
	.align	2
	.global	FSP_SetDisplay
	.type	FSP_SetDisplay, %function
FSP_SetDisplay:
	.fnstart
.LFB1557:
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
	cmp	r0, #15	@ InstID,
	mov	r4, r0	@ InstID, InstID
	mov	r5, r1	@ LogicFrameID, LogicFrameID
	mov	r8, r2	@ IsWaitDisp, IsWaitDisp
	bhi	.L393	@,
	cmp	r1, #63	@ LogicFrameID,
	bhi	.L394	@,
	movw	r6, #:lower16:.LANCHOR0	@ tmp151,
	movt	r6, #:upper16:.LANCHOR0	@ tmp151,
	ldr	r0, [r6, r0, asl #2]	@ tmp152, s_pFspInst
	cmp	r0, #0	@ tmp152,
	beq	.L395	@,
	ldr	r0, .L399	@,
	rsbs	r7, r2, #1	@ D.39622, IsWaitDisp
	movcc	r7, #0	@ D.39622
	bl	OSAL_SpinLockIRQ	@
	ldr	r6, [r6, r4, asl #2]	@ pstInst, s_pFspInst
	mov	r2, #536	@ tmp163,
	movw	r3, #:lower16:.LANCHOR1	@ tmp155,
	movt	r3, #:upper16:.LANCHOR1	@ tmp155,
	mla	r2, r2, r5, r6	@ tmp164, tmp163, LogicFrameID, pstInst
	add	r1, r2, #96	@ tmp165, tmp164,
	ldrsb	r0, [r1, #2]	@ <variable>.IsDummyFs, <variable>.IsDummyFs
	cmp	r0, #0	@ <variable>.IsDummyFs,
	cmpeq	r8, #0	@, IsWaitDisp,
	beq	.L396	@,
	cmp	r7, #0	@ D.39622,
	moveq	r3, #3	@ iftmp.522,
	bne	.L384	@,
.L386:
	mov	lr, #536	@ tmp189,
	mla	r5, lr, r5, r6	@ tmp190, tmp189, LogicFrameID, pstInst
	add	r1, r5, #96	@ tmp191, tmp190,
	ldrsb	r0, [r1, #2]	@ <variable>.IsDummyFs, <variable>.IsDummyFs
	strb	r3, [r1, #1]	@ iftmp.522, <variable>.s32DispState
	cmp	r0, #0	@ <variable>.IsDummyFs,
	bne	.L391	@,
	add	lr, r5, #608	@ tmp203, tmp190,
	ldr	ip, [lr, #4]	@ temp.1639, <variable>.pstDispOutFs
	cmp	ip, #0	@ temp.1639,
	beq	.L391	@,
	ldr	r2, [r5, #600]	@ D.39645, <variable>.u32Tick
	ldr	r3, [ip, #56]	@ D.39644, <variable>.u32Tick
	cmp	r3, r2	@ D.39644, D.39645
	bne	.L397	@,
	cmp	r7, #0	@ D.39622,
	strneb	r0, [r1, #1]	@ <variable>.IsDummyFs, <variable>.s32DispState
	strneb	r0, [ip, #2]	@ <variable>.IsDummyFs, <variable>.DispState
	moveq	r3, #3	@ tmp242,
	strne	r0, [lr, #4]	@ <variable>.IsDummyFs, <variable>.pstDispOutFs
	streqb	r3, [r1, #1]	@ tmp242, <variable>.s32DispState
	streqb	r3, [ip, #2]	@ tmp242, <variable>.DispState
.L391:
	ldr	r0, .L399	@,
	bl	OSAL_SpinUnLockIRQ	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L396:
	ldr	r2, [r2, #612]	@ D.39626, <variable>.pstDispOutFs
	cmp	r2, #0	@ D.39626,
	beq	.L384	@,
	ldrsb	r1, [r1, #1]	@ <variable>.s32DispState, <variable>.s32DispState
	cmp	r1, #0	@ <variable>.s32DispState,
	beq	.L384	@,
	ldr	ip, [r3, #-3896]	@ g_IsFrameIntfValid, g_IsFrameIntfValid
	cmp	ip, #0	@ g_IsFrameIntfValid,
	beq	.L384	@,
	ldr	r3, [r3, #-3884]	@ D.40276, g_FspFrameIntf.ReleaseFrame
	ldr	r1, [r2, #12]	@ D.39635, <variable>.PhyAddr
	cmp	r3, #0	@ D.40276,
	beq	.L398	@,
	mov	r0, r4	@, InstID
	blx	r3	@ D.40276
.L384:
	mov	r3, #0	@ iftmp.522,
	b	.L386	@
.L393:
	movw	r1, #:lower16:.LC0	@,
	mov	r2, #2048	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L394:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2049	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC33	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L397:
	movw	r1, #:lower16:.LC41	@,
	movt	r1, #:upper16:.LC41	@,
	bl	dprint_vfmw	@
	ldr	r0, .L399	@,
	bl	OSAL_SpinUnLockIRQ	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L395:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #2050	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L398:
	mov	r0, r3	@, D.40276
	movw	r1, #:lower16:.LC40	@,
	movt	r1, #:upper16:.LC40	@,
	bl	dprint_vfmw	@
	mov	r3, #0	@ iftmp.522,
	b	.L386	@
.L400:
	.align	2
.L399:
	.word	.LANCHOR1-3876
	.fnend
	.size	FSP_SetDisplay, .-FSP_SetDisplay
	.align	2
	.global	FSP_ClearLogicFs
	.type	FSP_ClearLogicFs, %function
FSP_ClearLogicFs:
	.fnstart
.LFB1561:
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
	cmp	r1, #63	@ LogicFrameID,
	cmpls	r0, #15	@, InstID,
	mov	r4, r0	@ InstID, InstID
	mov	r6, r1	@ LogicFrameID, LogicFrameID
	ldmhifd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp144,
	movt	r5, #:upper16:.LANCHOR0	@ tmp144,
	ldr	r3, [r5, r0, asl #2]	@ tmp145, s_pFspInst
	cmp	r3, #0	@ tmp145,
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	mov	r2, #0	@,
	bl	FSP_SetRef	@
	ldr	ip, [r5, r4, asl #2]	@ tmp147, s_pFspInst
	mov	r2, #536	@ tmp150,
	mla	r1, r2, r6, ip	@ tmp151, tmp150, LogicFrameID, tmp147
	ldrsb	r0, [r1, #97]	@ <variable>.s32DispState, <variable>.s32DispState
	cmp	r0, #3	@ <variable>.s32DispState,
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	mov	r0, r4	@, InstID
	mov	r1, r6	@, LogicFrameID
	mov	r2, #0	@,
	bl	FSP_SetDisplay	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	FSP_ClearLogicFs, .-FSP_ClearLogicFs
	.align	2
	.global	FSP_IsFsLeak
	.type	FSP_IsFsLeak, %function
FSP_IsFsLeak:
	.fnstart
.LFB1550:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #28
	sub	sp, sp, #28	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r3, #:lower16:.LANCHOR0	@ tmp143,
	movt	r3, #:upper16:.LANCHOR0	@ tmp143,
	mov	r5, r0	@ InstID, InstID
	ldr	r2, [r3, r0, asl #2]	@ pstInst, s_pFspInst
	cmp	r2, #0	@ pstInst,
	beq	.L424	@,
	ldrsb	r4, [r2, #10]	@ TotalFsNum, <variable>.s32DecFsNum
	cmp	r4, #0	@ TotalFsNum,
	ble	.L407	@,
	add	r2, r2, #34304	@ ivtmp.1690, pstInst,
	mov	r3, #0	@ i,
	sub	ip, r4, #1	@ tmp159, TotalFsNum,
	ldrsb	r1, [r2, #156]!	@ <variable>.IsDecRef, <variable>.IsDecRef
	and	r0, ip, #1	@ tmp161, tmp159,
	cmp	r1, r3	@ <variable>.IsDecRef,
	beq	.L425	@,
.L414:
	mov	r3, #1	@ i,
	cmp	r4, r3	@ TotalFsNum, i
	add	r2, r2, #60	@ ivtmp.1690, ivtmp.1690,
	ble	.L407	@,
	cmp	r0, #0	@ tmp161,
	beq	.L410	@,
	ldrsb	r0, [r2, #0]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	r0, #0	@ <variable>.IsDecRef,
	bne	.L416	@,
	ldrsb	r1, [r2, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	r1, #0	@ <variable>.DispState,
	beq	.L409	@,
.L416:
	add	r3, r3, #1	@ i, i,
	add	r2, r2, #60	@ ivtmp.1690, ivtmp.1690,
	cmp	r4, r3	@ TotalFsNum, i
	ble	.L407	@,
.L410:
	ldrsb	r0, [r2, #0]	@ <variable>.IsDecRef, <variable>.IsDecRef
	add	r1, r2, #60	@ tmp163, ivtmp.1690,
	cmp	r0, #0	@ <variable>.IsDecRef,
	bne	.L408	@,
	ldrsb	ip, [r2, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	ip, #0	@ <variable>.DispState,
	beq	.L409	@,
.L408:
	ldrsb	r2, [r2, #60]	@ <variable>.IsDecRef, <variable>.IsDecRef
	add	r3, r3, #1	@ i, i,
	cmp	r2, #0	@ <variable>.IsDecRef,
	mov	r2, r3	@ tmp162, i
	bne	.L419	@,
	ldrsb	ip, [r1, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	ip, #0	@ <variable>.DispState,
	beq	.L409	@,
.L419:
	add	r3, r2, #1	@ i, tmp162,
	add	r2, r1, #60	@ ivtmp.1690, tmp163,
	cmp	r4, r3	@ TotalFsNum, i
	bgt	.L410	@,
.L407:
	sub	r1, fp, #28	@ tmp151,,
	mov	r6, #0	@ tmp148,
	mov	r0, r5	@, InstID
	sub	r2, fp, #40	@,,
	str	r6, [r1, #-4]!	@ tmp148, RefNum
	sub	r3, fp, #36	@,,
	str	r6, [fp, #-36]	@ tmp148, NewNum
	str	r6, [fp, #-40]	@ tmp148, ReadNum
	bl	VCTRL_GetChanImgNum	@
	ldr	r2, [fp, #-32]	@ RefNum.495, RefNum
	ldr	r3, [fp, #-40]	@ ReadNum.494, ReadNum
	ldr	ip, [fp, #-36]	@ NewNum.493, NewNum
	add	r1, r2, r3	@ tmp154, RefNum.495, ReadNum.494
	add	r0, r1, #2	@ tmp155, tmp154,
	add	r1, r0, ip	@ tmp156, tmp155, NewNum.493
	cmp	r4, r1	@ TotalFsNum, tmp156
	bgt	.L426	@,
.L411:
	mov	r0, #0	@ D.39143,
.L406:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L425:
	ldrsb	ip, [r2, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	ip, #0	@ <variable>.DispState,
	bne	.L414	@,
.L409:
	cmp	r4, r3	@ TotalFsNum, i
	bgt	.L411	@,
	b	.L407	@
.L426:
	mov	r0, r6	@, tmp148
	movw	r1, #:lower16:.LC43	@,
	movt	r1, #:upper16:.LC43	@,
	str	ip, [sp, #0]	@ NewNum.493,
	str	r4, [sp, #4]	@ TotalFsNum,
	bl	dprint_vfmw	@
	mov	r0, r5	@, InstID
	bl	FSP_PrintContext	@
	mov	r0, #1	@ D.39143,
	b	.L406	@
.L424:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC42	@,
	movt	r1, #:upper16:.LC42	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39143,
	b	.L406	@
	.fnend
	.size	FSP_IsFsLeak, .-FSP_IsFsLeak
	.align	2
	.global	FSP_IsNewFsAvalible
	.type	FSP_IsNewFsAvalible, %function
FSP_IsNewFsAvalible:
	.fnstart
.LFB1549:
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
	cmp	r0, #15	@ InstID,
	mov	r6, r0	@ InstID, InstID
	bhi	.L451	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp146,
	movt	r3, #:upper16:.LANCHOR0	@ tmp146,
	ldr	r5, [r3, r0, asl #2]	@ D.39095, s_pFspInst
	cmp	r5, #0	@ D.39095,
	beq	.L452	@,
	movw	r3, #:lower16:.LANCHOR1	@ tmp150,
	movt	r3, #:upper16:.LANCHOR1	@ tmp150,
	ldr	r2, [r3, #-3896]	@ g_IsFrameIntfValid, g_IsFrameIntfValid
	cmp	r2, #0	@ g_IsFrameIntfValid,
	beq	.L431	@,
	ldr	r4, [r3, #-3892]	@ D.40284, g_FspFrameIntf.IsFrameAvalible
	cmp	r4, #0	@ D.40284,
	beq	.L453	@,
	blx	r4	@ D.40284
	cmp	r0, #0	@,
	bne	.L433	@,
.L431:
	ldrb	r0, [r5, #10]	@ zero_extendqisi2	@ D.39104, <variable>.s32DecFsNum
	cmp	r0, #0	@ D.39104,
	beq	.L434	@,
	sxtb	r0, r0	@ D.39113, D.39104
	cmp	r0, #0	@ D.39113,
	ble	.L435	@,
	add	r5, r5, #34304	@ ivtmp.1719, D.39095,
	sub	r3, r0, #1	@ tmp158, D.39113,
	and	r1, r3, #1	@ tmp160, tmp158,
	mov	r3, #0	@ i,
	ldrsb	ip, [r5, #156]!	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	ip, r3	@ <variable>.IsDecRef,
	bne	.L441	@,
	ldrsb	r2, [r5, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	r2, #0	@ <variable>.DispState,
	beq	.L437	@,
.L441:
	mov	r3, #1	@ i,
	cmp	r3, r0	@ i, D.39113
	add	r5, r5, #60	@ ivtmp.1719, ivtmp.1719,
	bge	.L435	@,
	cmp	r1, #0	@ tmp160,
	beq	.L438	@,
	ldrsb	ip, [r5, #0]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	ip, #0	@ <variable>.IsDecRef,
	bne	.L443	@,
	ldrsb	r1, [r5, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	r1, #0	@ <variable>.DispState,
	beq	.L437	@,
.L443:
	add	r3, r3, #1	@ i, i,
	add	r5, r5, #60	@ ivtmp.1719, ivtmp.1719,
	cmp	r3, r0	@ i, D.39113
	bge	.L435	@,
.L438:
	ldrsb	r1, [r5, #0]	@ <variable>.IsDecRef, <variable>.IsDecRef
	add	r2, r5, #60	@ tmp162, ivtmp.1719,
	cmp	r1, #0	@ <variable>.IsDecRef,
	bne	.L436	@,
	ldrsb	ip, [r5, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	ip, #0	@ <variable>.DispState,
	beq	.L437	@,
.L436:
	ldrsb	r1, [r5, #60]	@ <variable>.IsDecRef, <variable>.IsDecRef
	add	r3, r3, #1	@ i, i,
	cmp	r1, #0	@ <variable>.IsDecRef,
	mov	r1, r3	@ tmp161, i
	bne	.L446	@,
	ldrsb	ip, [r2, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	ip, #0	@ <variable>.DispState,
	beq	.L437	@,
.L446:
	add	r3, r1, #1	@ i, tmp161,
	add	r5, r2, #60	@ ivtmp.1719, tmp162,
	cmp	r3, r0	@ i, D.39113
	blt	.L438	@,
.L435:
	mov	r0, r6	@, InstID
	bl	FSP_IsFsLeak	@
	cmp	r0, #0	@,
	mvnne	r0, #0	@ D.39093,
	ldmnefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L433:
	mov	r0, #0	@ D.39093,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L437:
	cmp	r3, r0	@ i, D.39113
	bge	.L435	@,
.L434:
	mov	r0, #1	@ D.39093,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L453:
	mov	r0, r4	@, D.40284
	movw	r1, #:lower16:.LC34	@,
	movt	r1, #:upper16:.LC34	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ D.39093, D.40284
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L451:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1092	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39093,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L452:
	mov	r0, r5	@, D.39095
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1093	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39093,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	FSP_IsNewFsAvalible, .-FSP_IsNewFsAvalible
	.align	2
	.global	FSP_EmptyInstance
	.type	FSP_EmptyInstance, %function
FSP_EmptyInstance:
	.fnstart
.LFB1542:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ InstID,
	mov	sl, r0	@ InstID, InstID
	bhi	.L482	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp155,
	movt	r3, #:upper16:.LANCHOR0	@ tmp155,
	ldr	r8, [r3, r0, asl #2]	@ D.38704, s_pFspInst
	cmp	r8, #0	@ D.38704,
	beq	.L483	@,
	add	r0, r8, #96	@, D.38704,
	mov	r1, #34304	@,
	bl	__memzero	@
	ldrsb	r0, [r8, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	cmp	r0, #0	@ <variable>.s32DecFsNum,
	ble	.L458	@,
	movw	r7, #:lower16:.LANCHOR1	@ tmp191,
	movt	r7, #:upper16:.LANCHOR1	@ tmp191,
	add	r4, r8, #34304	@ ivtmp.1766, D.38704,
	mov	r5, #0	@ i,
	add	r4, r4, #212	@ ivtmp.1766, ivtmp.1766,
	mov	r9, r7	@ tmp192, tmp191
	mov	r6, r5	@ tmp194, i
	b	.L463	@
.L461:
	mov	r0, sl	@, InstID
	mov	r2, #0	@,
	blx	r3	@ D.40295
.L460:
	ldrsb	r1, [r4, #-54]	@ <variable>.DispState, <variable>.DispState
	cmp	r1, #0	@ <variable>.DispState,
	beq	.L459	@,
	ldr	r3, [r7, #-3884]	@ D.40301, g_FspFrameIntf.ReleaseFrame
	ldr	r1, [r4, #-44]	@ temp.1768, <variable>.PhyAddr
	cmp	r3, #0	@ D.40301,
	beq	.L484	@,
	mov	r0, sl	@, InstID
	blx	r3	@ D.40301
.L459:
	strb	r6, [r4, #-56]	@ tmp194, <variable>.IsDecRef
	add	r5, r5, #1	@ i, i,
	strb	r6, [r4, #-54]	@ tmp194, <variable>.DispState
	str	r6, [r4], #60	@ tmp194, <variable>.u32Tick
	ldrsb	lr, [r8, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	cmp	lr, r5	@ <variable>.s32DecFsNum, i
	ble	.L458	@,
.L463:
	ldr	r1, [r4, #-44]	@ D.38713, <variable>.PhyAddr
	cmp	r1, #0	@ D.38713,
	beq	.L459	@,
	ldr	r2, [r7, #-3896]	@ g_IsFrameIntfValid, g_IsFrameIntfValid
	cmp	r2, #0	@ g_IsFrameIntfValid,
	beq	.L459	@,
	ldrsb	ip, [r4, #-56]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	ip, #0	@ <variable>.IsDecRef,
	beq	.L460	@,
	ldr	r3, [r9, #-3880]	@ D.40295, g_FspFrameIntf.SetFrameRef
	cmp	r3, #0	@ D.40295,
	bne	.L461	@,
	mov	r0, r3	@, D.40295
	movw	r1, #:lower16:.LC34	@,
	movt	r1, #:upper16:.LC34	@,
	bl	dprint_vfmw	@
	b	.L460	@
.L484:
	mov	r0, r3	@, D.40301
	movw	r1, #:lower16:.LC40	@,
	movt	r1, #:upper16:.LC40	@,
	add	r5, r5, #1	@ i, i,
	bl	dprint_vfmw	@
	strb	r6, [r4, #-56]	@ tmp194, <variable>.IsDecRef
	strb	r6, [r4, #-54]	@ tmp194, <variable>.DispState
	str	r6, [r4], #60	@ tmp194, <variable>.u32Tick
	ldrsb	lr, [r8, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	cmp	lr, r5	@ <variable>.s32DecFsNum, i
	bgt	.L463	@,
.L458:
	ldrsb	ip, [r8, #11]	@ D.38728, <variable>.s32DispFsNum
	cmp	ip, #0	@ D.38728,
	ble	.L464	@,
	add	r4, r8, #38144	@ tmp177, D.38704,
	cmp	ip, #1	@ D.38728,
	add	r1, r4, #212	@ ivtmp.1758, tmp177,
	sub	r3, ip, #1	@ tmp201, D.38728,
	and	r5, r3, #1	@ tmp203, tmp201,
	mov	r0, #1	@ i.1770,
	mov	r3, #0	@ tmp190,
	add	r2, r4, #272	@ ivtmp.1758, tmp177,
	str	r3, [r1, #0]	@ tmp190, <variable>.u32Tick
	strb	r3, [r1, #-56]	@ tmp190, <variable>.IsDecRef
	strb	r3, [r1, #-54]	@ tmp190, <variable>.DispState
	ble	.L464	@,
	cmp	r5, #0	@ tmp203,
	beq	.L465	@,
	mov	r0, #2	@ i.1770,
	cmp	ip, r0	@ D.38728, i.1770
	str	r3, [r2, #0]	@ tmp190, <variable>.u32Tick
	strb	r3, [r2, #-56]	@ tmp190, <variable>.IsDecRef
	strb	r3, [r2, #-54]	@ tmp190, <variable>.DispState
	add	r2, r4, #332	@ ivtmp.1758, tmp177,
	ble	.L464	@,
.L465:
	add	r0, r0, #2	@ i.1770, i.1770,
	mov	lr, r2	@ tmp204, ivtmp.1758
	cmp	ip, r0	@ D.38728, i.1770
	str	r3, [lr], #60	@ tmp190, <variable>.u32Tick
	strb	r3, [r2, #-56]	@ tmp190, <variable>.IsDecRef
	strb	r3, [r2, #-54]	@ tmp190, <variable>.DispState
	str	r3, [r2, #60]	@ tmp190, <variable>.u32Tick
	add	r2, r2, #120	@ ivtmp.1758, ivtmp.1758,
	strb	r3, [lr, #-54]	@ tmp190, <variable>.DispState
	strb	r3, [lr, #-56]	@ tmp190, <variable>.IsDecRef
	bgt	.L465	@,
.L464:
	ldrsb	ip, [r8, #13]	@ D.38730, <variable>.s32PmvNum
	cmp	ip, #0	@ D.38730,
	ble	.L466	@,
	cmp	ip, #1	@ D.38730,
	sub	r0, ip, #1	@ tmp196, D.38730,
	and	r1, r0, #1	@ tmp198, tmp196,
	mov	r2, #1	@ i.1771,
	mov	r0, #0	@ tmp189,
	add	r3, r8, r2	@ ivtmp.1751, D.38704,
	strb	r0, [r8, #14]	@ tmp189, <variable>.IsPmvInUse
	ble	.L466	@,
	cmp	r1, #0	@ tmp198,
	beq	.L467	@,
	mov	r2, #2	@ i.1771,
	cmp	ip, r2	@ D.38730, i.1771
	strb	r0, [r3, #14]	@ tmp189, <variable>.IsPmvInUse
	add	r3, r3, #1	@ ivtmp.1751, ivtmp.1751,
	ble	.L466	@,
.L467:
	add	r2, r2, #2	@ i.1771, i.1771,
	add	r1, r3, #1	@ tmp200, ivtmp.1751,
	cmp	ip, r2	@ D.38730, i.1771
	strb	r0, [r3, #14]	@ tmp189, <variable>.IsPmvInUse
	strb	r0, [r1, #14]	@ tmp189, <variable>.IsPmvInUse
	add	r3, r1, #1	@ ivtmp.1751, tmp200,
	bgt	.L467	@,
.L466:
	mov	r0, #0	@ tmp186,
	str	r0, [r8, #36]	@ tmp186, <variable>.u32InstTick
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L482:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	mov	r2, #424	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38702,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L483:
	mov	r0, r8	@, D.38704
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #425	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38702,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	.fnend
	.size	FSP_EmptyInstance, .-FSP_EmptyInstance
	.align	2
	.global	FSP_EnableInstance
	.type	FSP_EnableInstance, %function
FSP_EnableInstance:
	.fnstart
.LFB1539:
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
	cmp	r0, #15	@ InstID,
	bhi	.L491	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp139,
	movt	r3, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r4, [r3, r0, asl #2]	@ D.38624, s_pFspInst
	cmp	r4, #0	@ D.38624,
	beq	.L492	@,
	ldr	r5, [r4, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r5, #0	@ <variable>.eFspInstState,
	mvnne	r0, #0	@ D.38622,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	mov	r0, r4	@, D.38624
	movw	r1, #42352	@,
	bl	__memzero	@
	movw	r2, #42344	@ tmp144,
	mov	r1, #1	@ tmp143,
	mov	r0, r5	@ D.38622, <variable>.eFspInstState
	str	r5, [r4, r2]	@ <variable>.eFspInstState, <variable>.eFspPartitionState
	str	r1, [r4, #4]	@ tmp143, <variable>.eFspInstState
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L492:
	mov	r0, r4	@, D.38624
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #299	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38622,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L491:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #298	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38622,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	FSP_EnableInstance, .-FSP_EnableInstance
	.align	2
	.global	FSP_ClearContext
	.type	FSP_ClearContext, %function
FSP_ClearContext:
	.fnstart
.LFB1538:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #16
	sub	sp, sp, #16	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	subs	r4, r0, #0	@ pFspInst, pFspInst
	beq	.L497	@,
	add	r5, r4, #40	@ tmp142, pFspInst,
	ldrb	r8, [r4, #0]	@ zero_extendqisi2	@ s8TmpInstID, <variable>.s32InstID
	ldrb	sl, [r4, #1]	@ zero_extendqisi2	@ s8TmpLowBufEnable, <variable>.s8LowBufEnable
	sub	r6, fp, #52	@ tmp141,,
	ldmia	r5, {r0, r1, r2, r3}	@ tmp142,,,,
	ldr	r7, [r4, #4]	@ eTmpFspInstState, <variable>.eFspInstState
	stmia	r6, {r0, r1, r2, r3}	@ tmp141,,,,
	mov	r0, r4	@, pFspInst
	movw	r1, #42352	@,
	bl	__memzero	@
	str	r7, [r4, #4]	@ eTmpFspInstState, <variable>.eFspInstState
	strb	r8, [r4, #0]	@ s8TmpInstID, <variable>.s32InstID
	mov	ip, #0	@ D.38603,
	strb	sl, [r4, #1]	@ s8TmpLowBufEnable, <variable>.s8LowBufEnable
	ldmia	r6, {r0, r1, r2, r3}	@ tmp141,,,,
	stmia	r5, {r0, r1, r2, r3}	@ tmp142,,,,
.L495:
	mov	r0, ip	@, D.38603
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L497:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #274	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC44	@,
	movt	r3, #:upper16:.LC44	@,
	bl	dprint_vfmw	@
	mvn	ip, #0	@ D.38603,
	b	.L495	@
	.fnend
	.size	FSP_ClearContext, .-FSP_ClearContext
	.align	2
	.global	FSP_ConfigInstance
	.type	FSP_ConfigInstance, %function
FSP_ConfigInstance:
	.fnstart
.LFB1545:
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
	cmp	r0, #15	@ InstID,
	mov	r6, r1	@ pstFspInstCfg, pstFspInstCfg
	bhi	.L505	@,
	cmp	r1, #0	@ pstFspInstCfg,
	beq	.L506	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp143,
	movt	r3, #:upper16:.LANCHOR0	@ tmp143,
	ldr	r2, [r3, r0, asl #2]	@ D.38791, s_pFspInst
	cmp	r2, #0	@ D.38791,
	beq	.L502	@,
	ldr	r2, [r2, #4]	@ <variable>.eFspInstState, <variable>.eFspInstState
	cmp	r2, #1	@ <variable>.eFspInstState,
	bne	.L502	@,
	mov	r5, #0	@ tmp147,
	strb	r5, [r1, #0]	@ tmp147, <variable>.s32DispLoopEnable
	ldr	r4, [r3, r0, asl #2]	@ pstInst, s_pFspInst
	mov	r0, r4	@, pstInst
	add	r4, r4, #56	@ tmp150, pstInst,
	bl	FSP_ClearContext	@
	ldmia	r6!, {r0, r1, r2, r3}	@ pstFspInstCfg,,,,
	mov	ip, r4	@ tmp151, tmp150
	stmia	ip!, {r0, r1, r2, r3}	@ tmp151,,,,
	ldmia	r6!, {r0, r1, r2, r3}	@ pstFspInstCfg,,,,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp151,,,,
	ldr	r0, [r6, #0]	@ tmp153,* pstFspInstCfg
	str	r0, [ip, #0]	@ tmp153, <variable>.stInstCfg
.L500:
	mov	r0, r5	@, D.38785
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L502:
	movw	r2, #599	@,
	mvn	r5, #0	@ D.38785,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r3, #:lower16:.LC46	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r3, #:upper16:.LC46	@,
	bl	dprint_vfmw	@
	mov	r0, r5	@, D.38785
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L505:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #594	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ D.38785,
	b	.L500	@
.L506:
	mov	r0, r1	@, pstFspInstCfg
	movw	r2, #595	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r3, #:lower16:.LC45	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r3, #:upper16:.LC45	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ D.38785,
	b	.L500	@
	.fnend
	.size	FSP_ConfigInstance, .-FSP_ConfigInstance
	.align	2
	.global	FSP_ResetInstance
	.type	FSP_ResetInstance, %function
FSP_ResetInstance:
	.fnstart
.LFB1541:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ InstID,
	mov	r7, r0	@ InstID, InstID
	bhi	.L528	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp148,
	movt	r3, #:upper16:.LANCHOR0	@ tmp148,
	ldr	sl, [r3, r0, asl #2]	@ D.38664, s_pFspInst
	cmp	sl, #0	@ D.38664,
	beq	.L529	@,
	movw	r6, #:lower16:.LANCHOR1	@ tmp163,
	movt	r6, #:upper16:.LANCHOR1	@ tmp163,
	add	r4, sl, #34304	@ ivtmp.1875, D.38664,
	mov	r5, #0	@ i,
	add	r4, r4, #168	@ ivtmp.1875, ivtmp.1875,
	mov	r8, r6	@ tmp164, tmp163
	b	.L515	@
.L513:
	mov	r0, r7	@, InstID
	mov	r2, #0	@,
	blx	r3	@ D.40312
.L512:
	ldrsb	r1, [r4, #-10]	@ <variable>.DispState, <variable>.DispState
	cmp	r1, #0	@ <variable>.DispState,
	beq	.L511	@,
	ldr	r3, [r6, #-3884]	@ D.40318, g_FspFrameIntf.ReleaseFrame
	ldr	r1, [r4, #0]	@ temp.1881, <variable>.PhyAddr
	cmp	r3, #0	@ D.40318,
	beq	.L530	@,
	mov	r0, r7	@, InstID
	blx	r3	@ D.40318
.L511:
	ldr	r1, [r4, #60]	@ D.38668, <variable>.PhyAddr
	add	r5, r5, #1	@ tmp168, i,
	add	r4, r4, #60	@ tmp169, ivtmp.1875,
	cmp	r1, #0	@ D.38668,
	beq	.L518	@,
	ldr	ip, [r6, #-3896]	@ g_IsFrameIntfValid, g_IsFrameIntfValid
	cmp	ip, #0	@ g_IsFrameIntfValid,
	beq	.L518	@,
	ldrsb	lr, [r4, #-12]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	lr, #0	@ <variable>.IsDecRef,
	beq	.L519	@,
	ldr	r3, [r8, #-3880]	@ D.40312, g_FspFrameIntf.SetFrameRef
	cmp	r3, #0	@ D.40312,
	beq	.L526	@,
	mov	r0, r7	@, InstID
	mov	r2, #0	@,
	blx	r3	@ D.40312
.L519:
	ldrsb	r3, [r4, #-10]	@ <variable>.DispState, <variable>.DispState
	cmp	r3, #0	@ <variable>.DispState,
	beq	.L518	@,
	ldr	r3, [r6, #-3884]	@ D.40318, g_FspFrameIntf.ReleaseFrame
	ldr	r1, [r4, #0]	@ temp.1881, <variable>.PhyAddr
	cmp	r3, #0	@ D.40318,
	beq	.L525	@,
	mov	r0, r7	@, InstID
	blx	r3	@ D.40318
.L518:
	add	r5, r5, #1	@ i, tmp168,
	add	r4, r4, #60	@ ivtmp.1875, tmp169,
	cmp	r5, #64	@ i,
	beq	.L531	@,
.L515:
	ldr	r1, [r4, #0]	@ D.38668, <variable>.PhyAddr
	cmp	r1, #0	@ D.38668,
	beq	.L511	@,
	ldr	r0, [r6, #-3896]	@ g_IsFrameIntfValid, g_IsFrameIntfValid
	cmp	r0, #0	@ g_IsFrameIntfValid,
	beq	.L511	@,
	ldrsb	r2, [r4, #-12]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	r2, #0	@ <variable>.IsDecRef,
	beq	.L512	@,
	ldr	r3, [r8, #-3880]	@ D.40312, g_FspFrameIntf.SetFrameRef
	cmp	r3, #0	@ D.40312,
	bne	.L513	@,
	mov	r0, r3	@, D.40312
	movw	r1, #:lower16:.LC34	@,
	movt	r1, #:upper16:.LC34	@,
	bl	dprint_vfmw	@
	b	.L512	@
.L531:
	mov	r0, sl	@, D.38664
	bl	FSP_ClearContext	@
	mov	r0, #0	@ D.38662,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L530:
	mov	r0, r3	@, D.40318
	movw	r1, #:lower16:.LC40	@,
	movt	r1, #:upper16:.LC40	@,
	bl	dprint_vfmw	@
	b	.L511	@
.L526:
	mov	r0, r3	@, D.40312
	movw	r1, #:lower16:.LC34	@,
	movt	r1, #:upper16:.LC34	@,
	bl	dprint_vfmw	@
	b	.L519	@
.L525:
	mov	r0, r3	@, D.40318
	movw	r1, #:lower16:.LC40	@,
	movt	r1, #:upper16:.LC40	@,
	bl	dprint_vfmw	@
	b	.L518	@
.L528:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #346	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38662,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L529:
	mov	r0, sl	@, D.38664
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #347	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38662,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	.fnend
	.size	FSP_ResetInstance, .-FSP_ResetInstance
	.align	2
	.global	FSP_Init
	.type	FSP_Init, %function
FSP_Init:
	.fnstart
.LFB1535:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp133,
	movt	r4, #:upper16:.LANCHOR0	@ tmp133,
	mov	r1, #64	@,
	mov	r0, r4	@, tmp133
	bl	__memzero	@
	add	r0, r4, #64	@, tmp133,
	mov	r1, #4224	@,
	bl	__memzero	@
	movw	ip, #4026	@ tmp196,
	mvn	r3, #0	@ tmp138,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #330	@ tmp140,
	movw	r2, #:lower16:.LANCHOR1	@ tmp199,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #594	@ tmp144,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #858	@ tmp148,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #1122	@ tmp152,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #1386	@ tmp156,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #1650	@ tmp160,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #1914	@ tmp164,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #2178	@ tmp168,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #2442	@ tmp172,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #2706	@ tmp176,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #2970	@ tmp180,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #3234	@ tmp184,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movt	r2, #:upper16:.LANCHOR1	@ tmp199,
	movw	ip, #3498	@ tmp188,
	sub	r0, r2, #3888	@, tmp199,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	movw	ip, #3762	@ tmp192,
	strh	r3, [r4, ip]	@ movhi	@ tmp138, <variable>.history
	sub	r0, r0, #4	@,,
	mov	ip, #0	@ tmp200,
	mov	r1, #16	@,
	str	ip, [r2, #-3896]	@ tmp200, g_IsFrameIntfValid
	strh	r3, [r4, #66]	@ movhi	@ tmp138, <variable>.history
	bl	__memzero	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	FSP_Init, .-FSP_Init
	.align	2
	.global	FSP_NewLogicFs
	.type	FSP_NewLogicFs, %function
FSP_NewLogicFs:
	.fnstart
.LFB1553:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #68
	sub	sp, sp, #68	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ InstID,
	mov	r8, r0	@ InstID, InstID
	mov	r6, r1	@ NeedPhyFs, NeedPhyFs
	bhi	.L642	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp200,
	movt	r4, #:upper16:.LANCHOR0	@ tmp200,
	ldr	r0, [r4, r0, asl #2]	@ tmp201, s_pFspInst
	cmp	r0, #0	@ tmp201,
	beq	.L643	@,
	ldr	r0, .L649	@,
	movw	sl, #:lower16:.LANCHOR1	@ tmp790,
	bl	OSAL_SpinLockIRQ	@
	ldr	r5, [r4, r8, asl #2]	@ pstInst, s_pFspInst
	movt	sl, #:upper16:.LANCHOR1	@ tmp790,
	mov	r4, #0	@ i.2021,
	mov	r3, r5	@ ivtmp.2050, pstInst
	b	.L541	@
.L538:
	ldrsb	lr, [r2, #96]	@ <variable>.s32IsRef, <variable>.s32IsRef
	add	r4, r4, #1	@ i.2021, i.2021,
	cmp	lr, #0	@ <variable>.s32IsRef,
	mov	r3, r4	@ tmp820, i.2021
	bne	.L611	@,
	ldrsb	r7, [r2, #97]	@ <variable>.s32DispState, <variable>.s32DispState
	cmp	r7, #0	@ <variable>.s32DispState,
	beq	.L631	@,
.L611:
	add	r4, r3, #1	@ i.2021, tmp820,
	add	r3, r2, #536	@ ivtmp.2050, tmp821,
	cmp	r4, #64	@ i.2021,
	beq	.L539	@,
.L541:
	ldrsb	r1, [r3, #96]	@ <variable>.s32IsRef, <variable>.s32IsRef
	add	r2, r3, #536	@ tmp821, ivtmp.2050,
	cmp	r1, #0	@ <variable>.s32IsRef,
	bne	.L538	@,
	ldrsb	r7, [r3, #97]	@ <variable>.s32DispState, <variable>.s32DispState
	cmp	r7, #0	@ <variable>.s32DispState,
	bne	.L538	@,
.L631:
	mov	ip, #536	@ tmp213,
	mul	r3, ip, r4	@ tmp212, tmp213, i.2021
	add	r0, r3, #96	@ tmp226, tmp212,
	add	r3, r3, r5	@ tmp214, tmp212, pstInst
	add	r2, r5, r0	@ tmp227, pstInst, tmp226
	add	r1, r3, #96	@ tmp215, tmp214,
	cmp	r2, #0	@ tmp227,
	strb	r4, [r1, #3]	@ i.2021, <variable>.s32LogicFsID
	strb	r7, [r1, #2]	@ <variable>.s32DispState, <variable>.IsDummyFs
	beq	.L539	@,
	add	ip, r3, #608	@ tmp236, tmp214,
	add	r0, r3, #616	@ tmp248, tmp214,
	cmp	r6, #0	@ NeedPhyFs,
	str	r7, [r3, #608]	@ <variable>.s32DispState, <variable>.pstDecodeFs
	str	r7, [ip, #4]	@ <variable>.s32DispState, <variable>.pstDispOutFs
	str	r7, [r3, #616]	@ <variable>.s32DispState, <variable>.pstTfOutFs
	str	r7, [r0, #4]	@ <variable>.s32DispState, <variable>.PmvAddr
	beq	.L542	@,
	ldrsb	r0, [r5, #10]	@ temp.2054, <variable>.s32DecFsNum
	cmp	r0, #0	@ temp.2054,
	ble	.L544	@,
	add	r3, r5, #34304	@ ivtmp.1983, pstInst,
	sub	r2, r0, #1	@ tmp815, temp.2054,
	and	r1, r2, #1	@ tmp817, tmp815,
	ldrsb	ip, [r3, #156]!	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	ip, #0	@ <variable>.IsDecRef,
	bne	.L604	@,
	ldrsb	ip, [r3, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	ip, #0	@ <variable>.DispState,
	beq	.L629	@,
.L604:
	mov	r7, #1	@ i.2026,
	cmp	r7, r0	@ i.2026, temp.2054
	add	r3, r3, #60	@ ivtmp.1983, ivtmp.1983,
	bge	.L630	@,
	cmp	r1, #0	@ tmp817,
	beq	.L547	@,
	ldrsb	lr, [r3, #0]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	lr, #0	@ <variable>.IsDecRef,
	bne	.L606	@,
	ldrsb	r1, [r3, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	r1, #0	@ <variable>.DispState,
	beq	.L629	@,
.L606:
	add	r7, r7, #1	@ i.2026, i.2026,
	add	r3, r3, #60	@ ivtmp.1983, ivtmp.1983,
	cmp	r7, r0	@ i.2026, temp.2054
	bge	.L630	@,
.L547:
	ldrsb	r1, [r3, #0]	@ <variable>.IsDecRef, <variable>.IsDecRef
	add	r2, r3, #60	@ tmp819, ivtmp.1983,
	cmp	r1, #0	@ <variable>.IsDecRef,
	bne	.L546	@,
	ldrsb	lr, [r3, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	lr, #0	@ <variable>.DispState,
	beq	.L629	@,
.L546:
	ldrsb	lr, [r3, #60]	@ <variable>.IsDecRef, <variable>.IsDecRef
	add	r7, r7, #1	@ i.2026, i.2026,
	cmp	lr, #0	@ <variable>.IsDecRef,
	mov	r3, r7	@ tmp818, i.2026
	bne	.L609	@,
	ldrsb	ip, [r2, #2]	@ <variable>.DispState, <variable>.DispState
	cmp	ip, #0	@ <variable>.DispState,
	beq	.L629	@,
.L609:
	add	r7, r3, #1	@ i.2026, tmp818,
	add	r3, r2, #60	@ ivtmp.1983, tmp819,
	cmp	r7, r0	@ i.2026, temp.2054
	blt	.L547	@,
.L630:
	mov	r7, #536	@ tmp317,
	mla	r3, r7, r4, r5	@ tmp318, tmp317, i.2021, pstInst
	ldr	r7, [r3, #608]	@ prephitmp.1927, <variable>.pstDecodeFs
.L544:
	cmp	r7, #0	@ prephitmp.1927,
	beq	.L644	@,
.L548:
	mov	r1, #536	@ tmp350,
	add	r6, r5, #41984	@ tmp353, pstInst,
	mla	lr, r1, r4, r5	@ tmp351, tmp350, i.2021, pstInst
	add	r3, r6, #156	@ tmp353, tmp353,
	str	r3, [lr, #616]	@ tmp353, <variable>.pstTfOutFs
	ldrsb	ip, [r5, #13]	@ temp.2004, <variable>.s32PmvNum
	cmp	ip, #0	@ temp.2004,
	ble	.L558	@,
	ldrsb	r3, [r5, #14]	@ <variable>.IsPmvInUse, <variable>.IsPmvInUse
	mov	lr, ip	@ D.39327, temp.2004
	cmp	r3, #0	@ <variable>.IsPmvInUse,
	moveq	r0, r3	@ prephitmp.1930, <variable>.IsPmvInUse
	beq	.L560	@,
	tst	ip, #1	@ temp.2004,
	mov	r2, r5	@ ivtmp.2047, pstInst
	mov	r3, #0	@ i.2006,
	bne	.L561	@,
	ldrb	r1, [r5, #15]	@ zero_extendqisi2	@ D.39322, <variable>.IsPmvInUse
	mov	r3, #1	@ i.2006,
	add	r2, r5, r3	@ ivtmp.2047, pstInst,
	cmp	r1, #0	@ D.39322,
	bne	.L561	@,
.L626:
	uxtb	r0, r3	@ prephitmp.1930, i.2006
.L560:
	mov	r2, #536	@ tmp359,
	add	ip, r3, #10560	@ tmp368, i.2006,
	mla	r2, r2, r4, r5	@ tmp360, tmp359, i.2021, pstInst
	add	r1, ip, #6	@ tmp368, tmp368,
	movw	lr, #42260	@ tmp376,
	strb	r0, [r2, #100]	@ prephitmp.1930, <variable>.PmvIdc
	ldr	r6, [r5, r1, asl #2]	@ tmp370, <variable>.PmvAddr
	str	r6, [r2, #620]	@ tmp370, <variable>.PmvAddr
	ldr	ip, [r5, lr]	@ <variable>.s32HalfPmvOffset, <variable>.s32HalfPmvOffset
	str	ip, [r2, #624]	@ <variable>.s32HalfPmvOffset, <variable>.HalfPmvOffset
	ldrsb	lr, [r5, #13]	@ D.39327, <variable>.s32PmvNum
	cmp	lr, r3	@ D.39327, i.2006
	ble	.L562	@,
.L558:
	ldrsb	r1, [r5, #56]	@ <variable>.stInstCfg.s32DispLoopEnable, <variable>.stInstCfg.s32DispLoopEnable
	cmp	r1, #0	@ <variable>.stInstCfg.s32DispLoopEnable,
	beq	.L566	@,
.L645:
	ldrsb	r6, [r5, #11]	@ D.39346, <variable>.s32DispFsNum
	cmp	r6, #0	@ D.39346,
	ble	.L641	@,
	add	r0, r5, #38144	@ tmp408, pstInst,
	cmn	r0, #156	@ tmp408,
	beq	.L569	@,
	movw	lr, #38300	@ tmp409,
	ldr	r2, [r5, lr]	@ tmp411,
	bic	r3, r2, #-16777216	@ tmp410, tmp411,
	cmp	r3, #0	@ tmp410,
	beq	.L569	@,
	tst	r6, #1	@ D.39346,
	add	r1, r0, #216	@ ivtmp.1952, tmp408,
	mov	r2, #0	@ i,
	bne	.L573	@,
	cmp	r1, #0	@ ivtmp.1952,
	mov	r2, #1	@ i,
	mov	r3, r2	@ i.1999, i
	beq	.L572	@,
	add	lr, r5, #38144	@ tmp845, pstInst,
	add	r1, r0, #276	@ ivtmp.1952, tmp408,
	add	ip, lr, #212	@ tmp845, tmp845,
	ldr	lr, [ip, #4]	@ tmp846,
	bic	r0, lr, #-16777216	@ tmp847, tmp846,
	cmp	r0, #0	@ tmp847,
	bne	.L573	@,
.L572:
	mov	r2, #536	@ tmp441,
	rsb	r6, r3, r3, asl #4	@, tmp434, i.1999, i.1999,
	mla	r1, r2, r4, r5	@ tmp442, tmp441, i.2021, pstInst
	add	lr, r5, r6, asl #2	@, tmp438, pstInst, tmp434,
	add	r3, lr, #38144	@ prephitmp.2005, tmp438,
	add	r6, r3, #156	@ prephitmp.2005, prephitmp.2005,
	str	r6, [r1, #612]	@ prephitmp.2005, <variable>.pstDispOutFs
	b	.L568	@
.L542:
	add	lr, r5, #34304	@ D.39284, pstInst,
	movw	sl, #42264	@ tmp282,
	add	r2, lr, #96	@ D.39284, D.39284,
	str	r2, [r3, #616]	@ D.39284, <variable>.pstTfOutFs
	str	r2, [ip, #4]	@ D.39284, <variable>.pstDispOutFs
	mov	r8, #1	@ tmp298,
	str	r2, [r3, #608]	@ D.39284, <variable>.pstDecodeFs
	ldr	r9, [r5, sl]	@ <variable>.PmvAddr, <variable>.PmvAddr
	str	r9, [r0, #4]	@ <variable>.PmvAddr, <variable>.PmvAddr
	ldrb	r7, [r5, #13]	@ zero_extendqisi2	@ <variable>.s32PmvNum, <variable>.s32PmvNum
	strb	r8, [r1, #2]	@ tmp298, <variable>.IsDummyFs
	sub	r6, r7, #1	@ tmp291, <variable>.s32PmvNum,
	strb	r6, [r1, #4]	@ tmp291, <variable>.PmvIdc
.L545:
	mov	r6, #536	@ tmp504,
	mov	r3, #1	@ tmp507,
	mul	sl, r6, r4	@ tmp503, tmp504, i.2021
	mov	r1, #496	@,
	add	r6, sl, r5	@ tmp505, tmp503, pstInst
	add	r9, sl, #104	@ tmp565, tmp503,
	add	ip, r6, #608	@ tmp513, tmp505,
	add	r7, r6, #96	@ tmp506, tmp505,
	add	r8, r6, #152	@, tmp505,
	add	r0, r5, r9	@, pstInst, tmp565
	ldr	lr, [ip, #4]	@ <variable>.pstDispOutFs, <variable>.pstDispOutFs
	add	r2, r6, #136	@ tmp612, tmp505,
	strb	r3, [r7, #1]	@ tmp507, <variable>.s32DispState
	add	r9, r6, #208	@ tmp600, tmp505,
	str	r8, [fp, #-88]	@, %sfp
	add	sl, r6, #224	@ tmp653, tmp505,
	strb	r3, [lr, #2]	@ tmp507, <variable>.DispState
	add	lr, r6, #144	@, tmp505,
	str	lr, [fp, #-92]	@, %sfp
	add	r8, r6, #216	@ tmp681, tmp505,
	str	r3, [r6, #604]	@ tmp507, <variable>.eLfsPmvState
	ldr	r4, [r6, #608]	@ <variable>.pstDecodeFs, <variable>.pstDecodeFs
	ldr	r3, [r5, #36]	@ D.39378, <variable>.u32InstTick
	str	r3, [r6, #600]	@ D.39378, <variable>.u32Tick
	str	r3, [r4, #56]	@ D.39378, <variable>.u32Tick
	ldr	lr, [ip, #4]	@ <variable>.pstDispOutFs, <variable>.pstDispOutFs
	ldr	r4, [r6, #600]	@ <variable>.u32Tick, <variable>.u32Tick
	str	r4, [lr, #56]	@ <variable>.u32Tick, <variable>.u32Tick
	ldr	r3, [r5, #36]	@ <variable>.u32InstTick, <variable>.u32InstTick
	add	r4, r3, #1	@ tmp547, <variable>.u32InstTick,
	str	r4, [r5, #36]	@ tmp547, <variable>.u32InstTick
	ldr	lr, [r6, #616]	@ pstTfFs, <variable>.pstTfOutFs
	ldr	r4, [r6, #608]	@ pstDecFs, <variable>.pstDecodeFs
	ldr	r5, [ip, #4]	@ pstDispFs, <variable>.pstDispOutFs
	str	lr, [fp, #-96]	@,
	str	r2, [fp, #-100]	@,
	bl	__memzero	@
	ldrsb	r1, [r7, #3]	@ <variable>.s32LogicFsID, <variable>.s32LogicFsID
	str	r1, [r6, #300]	@ <variable>.s32LogicFsID, <variable>.stDispImg.image_id
	ldr	r2, [r4, #36]	@ <variable>.FsWidth, <variable>.FsWidth
	str	r2, [r6, #268]	@ <variable>.FsWidth, <variable>.stDispImg.image_width
	ldr	r3, [r4, #40]	@ <variable>.FsHeight, <variable>.FsHeight
	str	r3, [r6, #272]	@ <variable>.FsHeight, <variable>.stDispImg.image_height
	ldr	r0, [r5, #20]	@ <variable>.Stride, <variable>.Stride
	str	r0, [r6, #296]	@ <variable>.Stride, <variable>.stDispImg.image_stride
	ldr	r1, [r4, #12]	@ D.39394, <variable>.PhyAddr
	str	r1, [r6, #208]	@ D.39394, <variable>.stDispImg.luma_phy_addr
	mov	r0, r1	@, D.39394
	ldr	ip, [r4, #44]	@ <variable>.ChromOffset, <variable>.ChromOffset
	add	r2, ip, r1	@ tmp607, <variable>.ChromOffset, D.39394
	str	r2, [r9, #4]	@ tmp607, <variable>.stDispImg.chrom_phy_addr
	bl	MEM_Phy2Vir	@
	str	r0, [r6, #136]	@, <variable>.stDispImg.luma_vir_addr
	ldr	r0, [r9, #4]	@, <variable>.stDispImg.chrom_phy_addr
	bl	MEM_Phy2Vir	@
	ldr	r3, [fp, #-100]	@,
	str	r0, [r3, #4]	@, <variable>.stDispImg.chrom_vir_addr
	ldr	ip, [r5, #12]	@ D.39407, <variable>.PhyAddr
	str	ip, [r6, #192]	@ D.39407, <variable>.stDispImg.top_luma_phy_addr
	ldr	r1, [r5, #44]	@ <variable>.ChromOffset, <variable>.ChromOffset
	add	r3, ip, r1	@ D.39410, D.39407, <variable>.ChromOffset
	str	r3, [r6, #196]	@ D.39410, <variable>.stDispImg.top_chrom_phy_addr
	ldr	r0, [r5, #20]	@ <variable>.Stride, <variable>.Stride
	add	r2, r0, ip	@ tmp641, <variable>.Stride, D.39407
	str	r2, [r6, #200]	@ tmp641, <variable>.stDispImg.btm_luma_phy_addr
	ldr	ip, [r5, #20]	@ <variable>.Stride, <variable>.Stride
	add	r0, r3, ip	@ tmp648, D.39410, <variable>.Stride
	str	r0, [r6, #204]	@ tmp648, <variable>.stDispImg.btm_chrom_phy_addr
	ldr	r2, [r5, #12]	@ temp.2029, <variable>.PhyAddr
	str	r2, [r6, #224]	@ temp.2029, <variable>.stDispImg.luma_2d_phy_addr
	mov	r0, r2	@, temp.2029
	ldr	r1, [r5, #44]	@ <variable>.ChromOffset, <variable>.ChromOffset
	add	ip, r1, r2	@ tmp660, <variable>.ChromOffset, temp.2029
	str	ip, [sl, #4]	@ tmp660, <variable>.stDispImg.chrom_2d_phy_addr
	bl	MEM_Phy2Vir	@
	str	r0, [r6, #152]	@, <variable>.stDispImg.luma_2d_vir_addr
	ldr	r0, [sl, #4]	@, <variable>.stDispImg.chrom_2d_phy_addr
	bl	MEM_Phy2Vir	@
	ldr	r3, [fp, #-88]	@, %sfp
	str	r0, [r3, #4]	@, <variable>.stDispImg.chrom_2d_vir_addr
	ldr	r0, [fp, #-96]	@,
	ldr	r1, [r0, #12]	@ D.39425, <variable>.PhyAddr
	str	r1, [r6, #216]	@ D.39425, <variable>.stDispImg.luma_tf_phy_addr
	mov	r0, r1	@, D.39425
	ldr	r2, [r4, #44]	@ <variable>.ChromOffset, <variable>.ChromOffset
	add	ip, r2, r1	@ tmp688, <variable>.ChromOffset, D.39425
	str	ip, [r8, #4]	@ tmp688, <variable>.stDispImg.chrom_tf_phy_addr
	bl	MEM_Phy2Vir	@
	str	r0, [r6, #144]	@, <variable>.stDispImg.luma_tf_vir_addr
	ldr	r0, [r8, #4]	@, <variable>.stDispImg.chrom_tf_phy_addr
	bl	MEM_Phy2Vir	@
	ldr	lr, [fp, #-92]	@, %sfp
	ldr	r2, [r6, #208]	@ <variable>.stDispImg.luma_phy_addr, <variable>.stDispImg.luma_phy_addr
	ldr	ip, [r6, #136]	@ <variable>.stDispImg.luma_vir_addr, <variable>.stDispImg.luma_vir_addr
	str	r0, [lr, #4]	@, <variable>.stDispImg.chrom_tf_vir_addr
	ldr	r3, [r4, #24]	@ <variable>.Stride_2bit, <variable>.Stride_2bit
	str	r3, [r6, #248]	@ <variable>.Stride_2bit, <variable>.stDispImg.image_stride_2bit
	ldr	r1, [r4, #28]	@ <variable>.LumaOffset_2bit, <variable>.LumaOffset_2bit
	add	lr, r1, r2	@ tmp723, <variable>.LumaOffset_2bit, <variable>.stDispImg.luma_phy_addr
	str	lr, [r6, #236]	@ tmp723, <variable>.stDispImg.luma_2bit_phy_addr
	ldr	r0, [r4, #28]	@ <variable>.LumaOffset_2bit, <variable>.LumaOffset_2bit
	ldr	r3, [r4, #32]	@ <variable>.ChromOffset_2bit, <variable>.ChromOffset_2bit
	add	r1, r0, r3	@ tmp729, <variable>.LumaOffset_2bit, <variable>.ChromOffset_2bit
	add	lr, r1, r2	@ tmp738, tmp729, <variable>.stDispImg.luma_phy_addr
	str	lr, [r6, #244]	@ tmp738, <variable>.stDispImg.chrom_2bit_phy_addr
	ldr	r3, [r4, #28]	@ <variable>.LumaOffset_2bit, <variable>.LumaOffset_2bit
	add	r2, ip, r3	@ tmp751, <variable>.stDispImg.luma_vir_addr, <variable>.LumaOffset_2bit
	str	r2, [r6, #232]	@ tmp751, <variable>.stDispImg.luma_2bit_vir_addr
	ldr	r1, [r4, #32]	@ <variable>.ChromOffset_2bit, <variable>.ChromOffset_2bit
	ldr	r0, [r4, #28]	@ <variable>.LumaOffset_2bit, <variable>.LumaOffset_2bit
	add	lr, r1, r0	@ tmp762, <variable>.ChromOffset_2bit, <variable>.LumaOffset_2bit
	add	r3, ip, lr	@ tmp766, <variable>.stDispImg.luma_vir_addr, tmp762
	str	r3, [r6, #240]	@ tmp766, <variable>.stDispImg.chrom_2bit_vir_addr
	ldr	ip, [r4, #16]	@ <variable>.LineNumAddr, <variable>.LineNumAddr
	str	ip, [r6, #380]	@ <variable>.LineNumAddr, <variable>.stDispImg.line_num_phy_addr
	ldr	r0, [r4, #16]	@, <variable>.LineNumAddr
	bl	MEM_Phy2Vir	@
	str	r0, [r6, #160]	@, <variable>.stDispImg.line_num_vir_addr
	ldr	r0, .L649	@,
	bl	OSAL_SpinUnLockIRQ	@
	ldrsb	r0, [r7, #3]	@ D.39263, <variable>.s32LogicFsID
.L536:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L563:
	ldrb	r0, [r2, #15]	@ zero_extendqisi2	@ D.39322, <variable>.IsPmvInUse
	add	r2, r1, #1	@ ivtmp.2047, tmp809,
	cmp	r0, #0	@ D.39322,
	beq	.L626	@,
	ldrb	r6, [r1, #15]	@ zero_extendqisi2	@ D.39322, <variable>.IsPmvInUse
	add	r3, r3, #1	@ i.2006, i.2006,
	cmp	r6, #0	@ D.39322,
	beq	.L626	@,
.L561:
	add	r3, r3, #1	@ i.2006, i.2006,
	add	r1, r2, #1	@ tmp809, ivtmp.2047,
	cmp	r3, ip	@ i.2006, temp.2004
	blt	.L563	@,
.L562:
	cmp	lr, #0	@ D.39327,
	ble	.L564	@,
	ldrsb	ip, [r5, #13]	@ temp.2009, <variable>.s32PmvNum
	mov	r2, #1	@ i.2010,
	mov	r0, #0	@ tmp792,
	strb	r0, [r5, #14]	@ tmp792, <variable>.IsPmvInUse
	cmp	ip, r2	@ temp.2009,
	sub	r3, ip, #1	@ tmp800, temp.2009,
	and	r1, r3, r2	@ tmp802, tmp800,
	add	r3, r5, r2	@ ivtmp.1994, pstInst,
	ble	.L564	@,
	cmp	r1, #0	@ tmp802,
	beq	.L565	@,
	mov	r2, #2	@ i.2010,
	cmp	ip, r2	@ temp.2009, i.2010
	strb	r0, [r3, #14]	@ tmp792, <variable>.IsPmvInUse
	add	r3, r3, #1	@ ivtmp.1994, ivtmp.1994,
	ble	.L564	@,
.L565:
	add	r2, r2, #2	@ i.2010, i.2010,
	add	lr, r3, #1	@ tmp804, ivtmp.1994,
	cmp	ip, r2	@ temp.2009, i.2010
	strb	r0, [r3, #14]	@ tmp792, <variable>.IsPmvInUse
	strb	r0, [lr, #14]	@ tmp792, <variable>.IsPmvInUse
	add	r3, lr, #1	@ ivtmp.1994, tmp804,
	bgt	.L565	@,
.L564:
	mov	r0, #536	@ tmp382,
	movw	lr, #42264	@ tmp392,
	mla	r3, r0, r4, r5	@ tmp383, tmp382, i.2021, pstInst
	mov	r6, #0	@ tmp385,
	mov	r0, r6	@, tmp385
	movw	r1, #:lower16:.LC50	@,
	movt	r1, #:upper16:.LC50	@,
	add	ip, r3, #96	@ tmp384, tmp383,
	strb	r6, [ip, #4]	@ tmp385, <variable>.PmvIdc
	movw	ip, #42260	@ tmp399,
	ldr	r2, [r5, lr]	@ <variable>.PmvAddr, <variable>.PmvAddr
	str	r2, [r3, #620]	@ <variable>.PmvAddr, <variable>.PmvAddr
	ldr	r6, [r5, ip]	@ <variable>.s32HalfPmvOffset, <variable>.s32HalfPmvOffset
	str	r6, [r3, #624]	@ <variable>.s32HalfPmvOffset, <variable>.HalfPmvOffset
	bl	dprint_vfmw	@
	ldrsb	r1, [r5, #56]	@ <variable>.stInstCfg.s32DispLoopEnable, <variable>.stInstCfg.s32DispLoopEnable
	cmp	r1, #0	@ <variable>.stInstCfg.s32DispLoopEnable,
	bne	.L645	@,
.L566:
	mov	r0, #536	@ tmp414,
	mla	ip, r0, r4, r5	@ tmp415, tmp414, i.2021, pstInst
	ldr	r6, [ip, #608]	@ <variable>.pstDecodeFs, <variable>.pstDecodeFs
	str	r6, [ip, #612]	@ <variable>.pstDecodeFs, <variable>.pstDispOutFs
.L571:
	mov	r0, r8	@, InstID
	bl	VCTRL_GetImageWidth	@
	mov	r6, r0	@ uImage_width,
	mov	r0, r8	@, InstID
	bl	VCTRL_GetImageHeight	@
	ldr	r1, [sl, #-3896]	@ g_IsFrameIntfValid, g_IsFrameIntfValid
	movw	r2, #:lower16:.LANCHOR1	@ tmp470,
	movt	r2, #:upper16:.LANCHOR1	@ tmp470,
	cmp	r1, #0	@ g_IsFrameIntfValid,
	mov	r3, r0	@ uImage_height,
	beq	.L545	@,
	ldr	ip, [r2, #-3888]	@ D.40338, g_FspFrameIntf.AllocFrame
	cmp	ip, #0	@ D.40338,
	beq	.L646	@,
	mov	r0, r8	@, InstID
	mov	r2, r6	@, uImage_width
	sub	r1, fp, #84	@,,
	blx	ip	@ D.40338
	cmp	r0, #0	@,
	bne	.L577	@,
	ldr	r6, [fp, #-84]	@ D.39370, stInfo.stFrameInfo.PhyAddr
	cmp	r6, #0	@ D.39370,
	beq	.L647	@,
	mov	r2, #536	@ tmp485,
	mla	sl, r2, r4, r5	@ tmp486, tmp485, i.2021, pstInst
	ldr	r0, [sl, #608]	@ <variable>.pstDecodeFs, <variable>.pstDecodeFs
	str	r6, [r0, #12]	@ D.39370, <variable>.PhyAddr
	ldrsb	lr, [sl, #100]	@ <variable>.PmvIdc, <variable>.PmvIdc
	ldr	r8, [fp, #-68]	@ D.39374, stInfo.stPmvInfo.PhyAddr
	add	r7, lr, #10560	@ tmp500, <variable>.PmvIdc,
	add	r9, r7, #6	@ tmp500, tmp500,
	str	r8, [sl, #620]	@ D.39374, <variable>.PmvAddr
	str	r8, [r5, r9, asl #2]	@ D.39374, <variable>.PmvAddr
	b	.L545	@
.L574:
	rsb	ip, r2, r2, asl #4	@, tmp849, i, i,
	cmp	r1, #0	@ ivtmp.1952,
	add	r0, r5, r0, asl #2	@, tmp428, pstInst, tmp426,
	add	r1, r1, #120	@ ivtmp.1952, ivtmp.1952,
	add	ip, r5, ip, asl #2	@, tmp851, pstInst, tmp849,
	add	r0, r0, #38144	@ tmp429, tmp428,
	add	ip, ip, #38144	@ tmp852, tmp851,
	add	r0, r0, #152	@ tmp429, tmp429,
	add	ip, ip, #152	@ tmp852, tmp852,
	beq	.L572	@,
	ldr	r0, [r0, #4]	@ tmp431,
	bic	r0, r0, #-16777216	@ tmp430, tmp431,
	cmp	r0, #0	@ tmp430,
	beq	.L572	@,
	cmp	lr, #0	@ tmp798,
	mov	r3, r2	@ i.1999, i
	beq	.L572	@,
	ldr	lr, [ip, #4]	@ tmp853,
	bic	r0, lr, #-16777216	@ tmp854, tmp853,
	cmp	r0, #0	@ tmp854,
	beq	.L572	@,
.L573:
	add	r3, r2, #1	@ tmp799, i,
	add	lr, r1, #60	@ tmp798, ivtmp.1952,
	cmp	r6, r3	@ D.39346, tmp799
	add	r2, r3, #1	@ i, i.1999,
	rsb	r0, r3, r3, asl #4	@, tmp426, i.1999, i.1999,
	bgt	.L574	@,
.L641:
	mov	r0, #536	@ tmp446,
	mla	ip, r0, r4, r5	@ tmp447, tmp446, i.2021, pstInst
	ldr	r6, [ip, #612]	@ prephitmp.2005, <variable>.pstDispOutFs
.L568:
	cmp	r6, #0	@ prephitmp.2005,
	bne	.L571	@,
	mov	r0, r6	@, prephitmp.2005
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	sub	r1, fp, #44	@ tmp453,,
	mov	r0, r8	@, InstID
	sub	r2, fp, #56	@,,
	str	r6, [r1, #-4]!	@ prephitmp.2005, RefNum
	sub	r3, fp, #52	@,,
	str	r6, [fp, #-52]	@ prephitmp.2005, NewNum
	str	r6, [fp, #-56]	@ prephitmp.2005, ReadNum
	bl	VCTRL_GetChanImgNum	@
	ldr	r3, [fp, #-56]	@ ReadNum, ReadNum
	ldr	r2, [fp, #-48]	@ RefNum, RefNum
	ldr	ip, [fp, #-52]	@ NewNum, NewNum
	add	r0, r2, r3	@ tmp456, RefNum, ReadNum
	ldrsb	r3, [r5, #11]	@ <variable>.s32DispFsNum, <variable>.s32DispFsNum
	add	r1, r0, #2	@ tmp459, tmp456,
	add	r2, r1, ip	@ tmp460, tmp459, NewNum
	cmp	r2, r3	@ tmp460, <variable>.s32DispFsNum
	bge	.L575	@,
	mov	r0, r6	@, prephitmp.2005
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	ldr	r3, [fp, #-52]	@ NewNum, NewNum
	mov	r0, r6	@, prephitmp.2005
	movw	r1, #:lower16:.LC53	@,
	ldr	r2, [fp, #-48]	@, RefNum
	movt	r1, #:upper16:.LC53	@,
	str	r3, [sp, #0]	@ NewNum,
	ldrsb	ip, [r5, #11]	@ <variable>.s32DispFsNum, <variable>.s32DispFsNum
	ldr	r3, [fp, #-56]	@, ReadNum
	str	ip, [sp, #4]	@ <variable>.s32DispFsNum,
	bl	dprint_vfmw	@
	mov	r0, r8	@, InstID
	bl	FSP_PrintContext	@
.L575:
	ldr	r0, .L649	@,
	bl	OSAL_SpinUnLockIRQ	@
	mvn	r0, #0	@ D.39263,
	b	.L536	@
.L629:
	mov	r1, #536	@ tmp312,
	rsb	r2, r7, r7, asl #4	@, tmp305, i.2026, i.2026,
	mla	r3, r1, r4, r5	@ tmp313, tmp312, i.2021, pstInst
	add	ip, r5, r2, asl #2	@, tmp309, pstInst, tmp305,
	add	r7, ip, #34304	@ prephitmp.1927, tmp309,
	add	r7, r7, #156	@ prephitmp.1927, prephitmp.1927,
	str	r7, [r3, #608]	@ prephitmp.1927, <variable>.pstDecodeFs
	b	.L544	@
.L646:
	movw	r1, #:lower16:.LC34	@,
	mov	r0, ip	@, D.40338
	movt	r1, #:upper16:.LC34	@,
	bl	dprint_vfmw	@
.L577:
	ldr	r0, .L649	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC54	@,
	movt	r1, #:upper16:.LC54	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39263,
	b	.L536	@
.L644:
	mov	r0, r7	@, prephitmp.1927
	movw	r1, #:lower16:.LC48	@,
	movw	r2, #:lower16:.LANCHOR2	@,
	movt	r1, #:upper16:.LC48	@,
	movt	r2, #:upper16:.LANCHOR2	@,
	bl	dprint_vfmw	@
	ldrsb	r0, [r5, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	cmp	r0, #0	@ <variable>.s32DecFsNum,
	ble	.L549	@,
	add	r6, r5, #34304	@ ivtmp.1977, pstInst,
	add	r6, r6, #156	@ ivtmp.1977, ivtmp.1977,
.L550:
	ldrsb	r2, [r6, #0]	@, <variable>.IsDecRef
	mov	r0, #0	@,
	ldrsb	r3, [r6, #2]	@, <variable>.DispState
	movw	r1, #:lower16:.LC19	@,
	movt	r1, #:upper16:.LC19	@,
	add	r7, r7, #1	@ i.2002, i.2002,
	bl	dprint_vfmw	@
	ldrsb	ip, [r5, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	add	r6, r6, #60	@ ivtmp.1977, ivtmp.1977,
	cmp	ip, r7	@ <variable>.s32DecFsNum, i.2002
	bgt	.L550	@,
.L549:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC20	@,
	movt	r1, #:upper16:.LC20	@,
	bl	dprint_vfmw	@
	ldrsb	r2, [r5, #9]	@ <variable>.s8TotalValidFsNum, <variable>.s8TotalValidFsNum
	cmp	r2, #0	@ <variable>.s8TotalValidFsNum,
	ble	.L551	@,
	ldrsb	lr, [r5, #10]	@ D.39315, <variable>.s32DecFsNum
	add	r1, r5, #34304	@ pstPhyFs, pstInst,
	add	r3, r1, #156	@ pstPhyFs, pstPhyFs,
	cmp	lr, #0	@ D.39315,
	movle	ip, #0	@ prephitmp.1932,
	ble	.L553	@,
	tst	lr, #1	@ D.39315,
	mov	ip, #0	@ i.1997,
	mov	r0, ip	@ i.2045, i.1997
	mvn	r1, #0	@ LeastTick.2051,
	bne	.L557	@,
	ldr	r2, [r3, #56]	@ LeastTick, <variable>.u32Tick
	mov	r0, #1	@ i.2045,
	add	r3, r3, #60	@ pstPhyFs, pstPhyFs,
	cmn	r2, #1	@ LeastTick,
	movcs	r2, r1	@, LeastTick, LeastTick.2051
	mov	r1, r2	@ LeastTick.2051, LeastTick
	b	.L557	@
.L648:
	ldr	r1, [r6, #56]	@ LeastTick, <variable>.u32Tick
	cmp	r1, r2	@ LeastTick, LeastTick
	movcs	r1, r2	@ LeastTick, LeastTick
	movcc	ip, r3	@ i.1997, tmp813
.L628:
	add	r0, r3, #1	@ i.2045, tmp813,
	add	r3, r6, #60	@ pstPhyFs, tmp814,
.L557:
	ldr	r2, [r3, #56]	@ LeastTick, <variable>.u32Tick
	add	r6, r3, #60	@ tmp814, pstPhyFs,
	add	r3, r0, #1	@ tmp813, i.2045,
	cmp	r2, r1	@ LeastTick, LeastTick.2051
	movcc	ip, r0	@ i.1997, i.2045
	movcs	r2, r1	@ LeastTick, LeastTick.2051
	cmp	lr, r3	@ D.39315, tmp813
	bgt	.L648	@,
.L553:
	mov	r2, #536	@ tmp332,
	rsb	ip, ip, ip, asl #4	@, tmp337, prephitmp.1932, prephitmp.1932,
	mla	lr, r2, r4, r5	@ tmp333, tmp332, i.2021, pstInst
	add	r1, r5, ip, asl #2	@, tmp341, pstInst, tmp337,
	add	r6, r1, #34304	@ tmp342, tmp341,
	add	r3, r6, #156	@ tmp342, tmp342,
	str	r3, [lr, #608]	@ tmp342, <variable>.pstDecodeFs
	b	.L548	@
.L642:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1496	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39263,
	b	.L536	@
.L569:
	mov	r3, #0	@ i.1999,
	b	.L572	@
.L643:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #1497	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39263,
	b	.L536	@
.L647:
	ldr	r0, .L649	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r6	@, D.39370
	movw	r1, #:lower16:.LC55	@,
	movt	r1, #:upper16:.LC55	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39263,
	b	.L536	@
.L539:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC47	@,
	movt	r1, #:upper16:.LC47	@,
	bl	dprint_vfmw	@
	ldr	r0, .L649	@,
	bl	OSAL_SpinUnLockIRQ	@
	mvn	r0, #0	@ D.39263,
	b	.L536	@
.L551:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC49	@,
	movw	r2, #:lower16:.LANCHOR2	@,
	movt	r1, #:upper16:.LC49	@,
	movt	r2, #:upper16:.LANCHOR2	@,
	bl	dprint_vfmw	@
	ldr	r0, .L649	@,
	bl	OSAL_SpinUnLockIRQ	@
	mvn	r0, #0	@ D.39263,
	b	.L536	@
.L650:
	.align	2
.L649:
	.word	.LANCHOR1-3876
	.fnend
	.size	FSP_NewLogicFs, .-FSP_NewLogicFs
	.align	2
	.global	FSP_PartitionFsMemory
	.type	FSP_PartitionFsMemory, %function
FSP_PartitionFsMemory:
	.fnstart
.LFB1546:
	@ args = 0, pretend = 0, frame = 968
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #996
	sub	sp, sp, #996	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r5, r0	@ InstID, InstID
	str	r1, [fp, #-992]	@ MemPhyAddr, %sfp
	sub	r0, fp, #984	@,,
	mov	r1, #940	@,
	mov	r9, r2	@ MemSize, MemSize
	str	r3, [fp, #-1000]	@ UsedMemSize, %sfp
	bl	__memzero	@
	cmp	r5, #15	@ InstID,
	bhi	.L717	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp198,
	movt	r3, #:upper16:.LANCHOR0	@ tmp198,
	ldr	r4, [r3, r5, asl #2]	@ D.38835, s_pFspInst
	cmp	r4, #0	@ D.38835,
	beq	.L718	@,
	mov	r0, r5	@, InstID
	bl	VCTRL_GetChanCapLevel	@
	cmp	r0, #32	@ eChanCapLevel,
	bls	.L719	@,
.L655:
	ldrsb	r3, [r4, #60]	@ <variable>.stInstCfg.s32UserDec, <variable>.stInstCfg.s32UserDec
	cmp	r3, #1	@ <variable>.stInstCfg.s32UserDec,
	bne	.L720	@,
	ldr	r3, [r4, #88]	@ D.38862, <variable>.stInstCfg.s32DispFsHeight
	cmp	r3, #0	@ D.38862,
	bne	.L659	@,
.L723:
	ldrb	r6, [r4, #56]	@ zero_extendqisi2	@, <variable>.stInstCfg.s32DispLoopEnable
	str	r6, [fp, #-996]	@, %sfp
.L660:
	movw	r6, #:lower16:s_pstVfmwChan	@ tmp627,
	movt	r6, #:upper16:s_pstVfmwChan	@ tmp627,
	ldrb	sl, [r4, #61]	@ zero_extendqisi2	@ D.38869, <variable>.stInstCfg.s32ExpectedDecFsNum
	ldr	r2, [r6, r5, asl #2]	@ D.38876, s_pstVfmwChan
	ldr	ip, [r2, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	ip, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	beq	.L721	@,
.L663:
	movw	r3, #:lower16:249204	@ tmp257,
	movt	r3, #:upper16:249204	@ tmp257,
	sxtb	sl, sl	@ D.38870, D.38869
	movw	r7, #:lower16:249224	@ tmp259,
	ldr	r0, [r2, r3]	@ <variable>.s32RefNum, <variable>.s32RefNum
	movt	r7, #:upper16:249224	@ tmp259,
	movw	lr, #:lower16:g_vdm_hal_fun_ptr	@ tmp267,
	movt	lr, #:upper16:g_vdm_hal_fun_ptr	@ tmp267,
	cmp	sl, r0	@ D.38870, <variable>.s32RefNum
	movne	r1, #1	@ tmp260,
	moveq	r1, #0	@ tmp262,
	str	r1, [r2, r7]	@ tmp262, <variable>.s32RefNumChanged
	movw	r2, #:lower16:249204	@ tmp265,
	ldrsb	r8, [r4, #61]	@ <variable>.stInstCfg.s32ExpectedDecFsNum, <variable>.stInstCfg.s32ExpectedDecFsNum
	movt	r2, #:upper16:249204	@ tmp265,
	ldr	r1, [r6, r5, asl #2]	@ tmp264, s_pstVfmwChan
	movw	r7, #:lower16:s_pstVfmwChan	@ tmp263,
	movt	r7, #:upper16:s_pstVfmwChan	@ tmp263,
	str	r8, [r1, r2]	@ <variable>.stInstCfg.s32ExpectedDecFsNum, <variable>.s32RefNum
	ldr	r8, [lr, #36]	@ D.38888, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	cmp	r8, #0	@ D.38888,
	beq	.L667	@,
	ldrsb	ip, [r4, #64]	@ <variable>.stInstCfg.s32ExpectedPmvNum, <variable>.stInstCfg.s32ExpectedPmvNum
	mov	lr, #40	@ tmp271,
	ldr	r2, [r4, #68]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stInstCfg.s32DecFsWidth
	mov	r1, r9	@, MemSize
	ldr	r3, [r4, #72]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stInstCfg.s32DecFsHeight
	str	ip, [sp, #0]	@ <variable>.stInstCfg.s32ExpectedPmvNum,
	sub	ip, fp, #984	@ tmp274,,
	str	lr, [sp, #4]	@ tmp271,
	ldrsb	lr, [r4, #60]	@ <variable>.stInstCfg.s32UserDec, <variable>.stInstCfg.s32UserDec
	ldr	r0, [fp, #-992]	@, %sfp
	str	ip, [sp, #16]	@ tmp274,
	str	r5, [sp, #12]	@ InstID,
	str	lr, [sp, #8]	@ <variable>.stInstCfg.s32UserDec,
	blx	r8	@ D.38888
	cmp	r0, #2	@ Ret,
	mov	r8, r0	@ Ret,
	bne	.L722	@,
	ldr	ip, [fp, #-436]	@ MemArrange.ValidFrameNum, MemArrange.ValidFrameNum
	mov	r1, #1	@ tmp285,
	strb	ip, [r4, #9]	@ MemArrange.ValidFrameNum, <variable>.s8TotalValidFsNum
	ldr	r3, [r7, r5, asl #2]	@ tmp284, s_pstVfmwChan
	str	r1, [r3, #1924]	@ tmp285, <variable>.stSynExtraData.s32WaitFsFlag
.L653:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L719:
	rsb	r2, r0, r0, asl #3	@, tmp209, eChanCapLevel, eChanCapLevel,
	movw	lr, #:lower16:CapItem	@ tmp206,
	add	r6, r2, #1	@ tmp210, tmp209,
	movt	lr, #:upper16:CapItem	@ tmp206,
	ldr	r1, [r4, #72]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stInstCfg.s32DecFsHeight
	ldr	ip, [lr, r2, asl #2]	@ tmp219, CapItem
	ldr	r3, [lr, r6, asl #2]	@ tmp218, CapItem
	ldr	r2, [r4, #68]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stInstCfg.s32DecFsWidth
	mul	lr, ip, r3	@ tmp217, tmp219, tmp218
	mul	r2, r2, r1	@ tmp203, <variable>.stInstCfg.s32DecFsWidth, <variable>.stInstCfg.s32DecFsHeight
	cmp	r0, #25	@ eChanCapLevel,
	cmpne	r2, lr	@, tmp203, tmp217
	bgt	.L655	@,
	ldr	r3, [r4, #88]	@ D.38862, <variable>.stInstCfg.s32DispFsHeight
	cmp	r3, #0	@ D.38862,
	beq	.L723	@,
.L659:
	ldr	r2, [r4, #84]	@ D.38864, <variable>.stInstCfg.s32DispFsWidth
	cmp	r2, #0	@ D.38864,
	bne	.L661	@,
	movw	r6, #:lower16:s_pstVfmwChan	@ tmp627,
	movt	r6, #:upper16:s_pstVfmwChan	@ tmp627,
	ldrb	r1, [r4, #56]	@ zero_extendqisi2	@, <variable>.stInstCfg.s32DispLoopEnable
	ldr	r2, [r6, r5, asl #2]	@ D.38876, s_pstVfmwChan
	str	r1, [fp, #-996]	@, %sfp
	ldr	ip, [r2, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	ldrb	sl, [r4, #61]	@ zero_extendqisi2	@ D.38869, <variable>.stInstCfg.s32ExpectedDecFsNum
	cmp	ip, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	bne	.L663	@,
.L721:
	movw	r3, #:lower16:249192	@ tmp249,
	movt	r3, #:upper16:249192	@ tmp249,
	ldr	r1, [r2, r3]	@ D.38879, <variable>.FspInst.eFspPartitionState
	cmp	r1, #0	@ D.38879,
	cmpne	r1, #2	@, D.38879,
	movne	r0, #0	@, tmp256
	moveq	r0, #1	@, tmp256
	beq	.L663	@,
	cmp	r1, #1	@ D.38879,
	beq	.L653	@,
	strb	r0, [r4, #9]	@ tmp256, <variable>.s8TotalValidFsNum
	movw	r1, #:lower16:.LC58	@,
	ldr	r2, [r6, r5, asl #2]	@ tmp279, s_pstVfmwChan
	mov	r0, #31	@,
	movt	r1, #:upper16:.LC58	@,
	ldr	r2, [r2, r3]	@, <variable>.FspInst.eFspPartitionState
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38833,
	b	.L653	@
.L667:
	mvn	r8, #0	@ Ret,
.L671:
	mov	lr, #0	@ tmp316,
	strb	lr, [r4, #9]	@ tmp316, <variable>.s8TotalValidFsNum
	ldr	ip, [r6, r5, asl #2]	@ tmp319, s_pstVfmwChan
	mov	r0, lr	@, tmp316
	mov	r2, r8	@, Ret
	movw	r1, #:lower16:.LC60	@,
	movt	r1, #:upper16:.LC60	@,
	str	lr, [ip, #1924]	@ tmp316, <variable>.stSynExtraData.s32WaitFsFlag
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38833,
	b	.L653	@
.L661:
	ldrb	lr, [r4, #56]	@ zero_extendqisi2	@, <variable>.stInstCfg.s32DispLoopEnable
	cmp	lr, #0	@,
	str	lr, [fp, #-996]	@, %sfp
	beq	.L660	@,
	ldr	r1, [r4, #72]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stInstCfg.s32DecFsHeight
	cmp	r3, r1	@ D.38862, <variable>.stInstCfg.s32DecFsHeight
	beq	.L724	@,
	mvn	r0, #0	@ D.38833,
	b	.L653	@
.L722:
	cmp	r0, #0	@ Ret,
	bne	.L671	@,
	ldr	r1, [fp, #-436]	@ MemArrange.ValidFrameNum, MemArrange.ValidFrameNum
	strb	r1, [r4, #9]	@ MemArrange.ValidFrameNum, <variable>.s8TotalValidFsNum
	ldr	r2, [r7, r5, asl #2]	@ tmp289, s_pstVfmwChan
	str	r0, [r2, #1924]	@ Ret, <variable>.stSynExtraData.s32WaitFsFlag
	ldr	lr, [r7, r5, asl #2]	@ tmp292, s_pstVfmwChan
	ldr	r0, [lr, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r0, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	beq	.L725	@,
.L672:
	ldr	r0, [fp, #-996]	@, %sfp
	movw	r1, #:lower16:.LC59	@,
	movt	r1, #:upper16:.LC59	@,
	sxtb	r3, r0	@ prephitmp.2074,
	mov	r0, #31	@,
	add	sl, sl, r3, asl #2	@, MinFsNum, D.38870, prephitmp.2074,
	bl	dprint_vfmw	@
	ldr	ip, [fp, #-436]	@ temp.2241, MemArrange.ValidFrameNum
	cmp	sl, ip	@ MinFsNum, temp.2241
	bgt	.L726	@,
	ldrsb	sl, [r4, #56]	@ <variable>.stInstCfg.s32DispLoopEnable, <variable>.stInstCfg.s32DispLoopEnable
	mov	r9, #0	@ tmp322,
	strb	r9, [r4, #12]	@ tmp322, <variable>.s32TfFsNum
	cmp	sl, r9	@ <variable>.stInstCfg.s32DispLoopEnable,
	strb	r9, [r4, #11]	@ tmp322, <variable>.s32DispFsNum
	bne	.L679	@,
	ldrsb	r8, [r4, #1]	@ <variable>.s8LowBufEnable, <variable>.s8LowBufEnable
	cmp	r8, #0	@ <variable>.s8LowBufEnable,
	beq	.L680	@,
	ldr	r7, [r6, r5, asl #2]	@ tmp329, s_pstVfmwChan
	ldr	r5, [r7, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r5, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	beq	.L680	@,
	ldrsb	r1, [r4, #61]	@ <variable>.stInstCfg.s32ExpectedDecFsNum, <variable>.stInstCfg.s32ExpectedDecFsNum
	ldr	r2, [fp, #-436]	@ MemArrange.ValidFrameNum, MemArrange.ValidFrameNum
	add	r6, r1, #4	@ tmp331, <variable>.stInstCfg.s32ExpectedDecFsNum,
	cmp	r6, r2	@ tmp331, MemArrange.ValidFrameNum
	movge	r6, r2	@ tmp645, MemArrange.ValidFrameNum
	uxtb	sl, r6	@ prephitmp.2247, tmp645
	strb	sl, [r4, #10]	@ prephitmp.2247, <variable>.s32DecFsNum
.L681:
	add	ip, r4, #34304	@, D.38835,
	mov	r0, #0	@ ivtmp.2175,
	add	lr, ip, #180	@,,
	str	ip, [fp, #-992]	@, %sfp
	add	r8, ip, #160	@ ivtmp.2173,,
	add	r7, ip, #168	@ ivtmp.2185,,
	add	r6, ip, #176	@ ivtmp.2191,,
	str	lr, [fp, #-996]	@, %sfp
	mov	r9, lr	@ ivtmp.2323,
	sub	r5, fp, #984	@ ivtmp.2322,,
	mov	r1, r0	@ i.2260, ivtmp.2175
	mov	ip, r0	@ tmp640, ivtmp.2175
	b	.L682	@
.L728:
	str	r1, [r8, #0]	@ i.2260, <variable>.PhyFsID
	ldr	lr, [r5, #8]	@ tmp345, MemArrange.FrameAddr
	str	lr, [r7, #0]	@ tmp345, <variable>.PhyAddr
	ldr	r2, [r5, #264]	@ tmp348, MemArrange.LineNumAddr
	str	r2, [r3, #172]	@ tmp348, <variable>.LineNumAddr
	ldr	lr, [fp, #-984]	@ MemArrange.VahbStride, MemArrange.VahbStride
	str	lr, [r6, #0]	@ MemArrange.VahbStride, <variable>.Stride
	ldr	r2, [fp, #-464]	@ MemArrange.VahbStride_2bit, MemArrange.VahbStride_2bit
	str	r2, [r9, #0]	@ MemArrange.VahbStride_2bit, <variable>.Stride_2bit
	ldr	lr, [fp, #-456]	@ MemArrange.LumaOffset_2bit, MemArrange.LumaOffset_2bit
	str	lr, [r3, #184]	@ MemArrange.LumaOffset_2bit, <variable>.LumaOffset_2bit
	ldr	r2, [fp, #-452]	@ MemArrange.ChromOffset_2bit, MemArrange.ChromOffset_2bit
	str	r2, [r3, #188]	@ MemArrange.ChromOffset_2bit, <variable>.ChromOffset_2bit
	ldr	lr, [r4, #68]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stInstCfg.s32DecFsWidth
	str	lr, [r3, #192]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.FsWidth
	ldr	r2, [r4, #72]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stInstCfg.s32DecFsHeight
	str	r2, [r3, #196]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.FsHeight
	ldr	lr, [fp, #-448]	@ MemArrange.ChromOffset, MemArrange.ChromOffset
	str	lr, [r3, #200]	@ MemArrange.ChromOffset, <variable>.ChromOffset
	ldr	r2, [fp, #-444]	@ MemArrange.LumaPixelOffset, MemArrange.LumaPixelOffset
	str	r2, [r3, #204]	@ MemArrange.LumaPixelOffset, <variable>.LumaPixelOffset
	ldr	lr, [fp, #-440]	@ MemArrange.ChromaPixelOffset, MemArrange.ChromaPixelOffset
	strb	ip, [r3, #158]	@ tmp640, <variable>.DispState
	strb	ip, [r3, #156]	@ tmp640, <variable>.IsDecRef
	str	lr, [r3, #208]	@ MemArrange.ChromaPixelOffset, <variable>.ChromaPixelOffset
	strb	ip, [r3, #157]	@ tmp640, <variable>.IsTfRef
.L684:
	add	r1, r1, #1	@ i.2260, i.2260,
	add	r8, r8, #60	@ ivtmp.2173, ivtmp.2173,
	cmp	r1, #64	@ i.2260,
	add	r0, r0, #60	@ ivtmp.2175, ivtmp.2175,
	add	r5, r5, #4	@ ivtmp.2322, ivtmp.2322,
	add	r7, r7, #60	@ ivtmp.2185, ivtmp.2185,
	add	r6, r6, #60	@ ivtmp.2191, ivtmp.2191,
	add	r9, r9, #60	@ ivtmp.2323, ivtmp.2323,
	beq	.L727	@,
	ldrb	sl, [r4, #10]	@ zero_extendqisi2	@ prephitmp.2247, <variable>.s32DecFsNum
.L682:
	add	r2, r4, r0	@ D.42050, D.38835, ivtmp.2175
	sxtb	sl, sl	@ prephitmp.2247, prephitmp.2247
	add	r3, r2, #34304	@ tmp347, D.42050,
	cmp	sl, r1	@ prephitmp.2247, i.2260
	mov	r2, r3	@ tmp389, tmp347
	bgt	.L728	@,
	str	ip, [r8, #0]	@ tmp640, <variable>.PhyFsID
	ldr	lr, [fp, #-976]	@ MemArrange.FrameAddr, MemArrange.FrameAddr
	str	lr, [r7, #0]	@ MemArrange.FrameAddr, <variable>.PhyAddr
	ldr	r3, [fp, #-984]	@ MemArrange.VahbStride, MemArrange.VahbStride
	str	r3, [r6, #0]	@ MemArrange.VahbStride, <variable>.Stride
	ldr	lr, [fp, #-464]	@ MemArrange.VahbStride_2bit, MemArrange.VahbStride_2bit
	str	lr, [r9, #0]	@ MemArrange.VahbStride_2bit, <variable>.Stride_2bit
	ldr	r3, [fp, #-456]	@ MemArrange.LumaOffset_2bit, MemArrange.LumaOffset_2bit
	str	r3, [r2, #184]	@ MemArrange.LumaOffset_2bit, <variable>.LumaOffset_2bit
	ldr	lr, [fp, #-452]	@ MemArrange.ChromOffset_2bit, MemArrange.ChromOffset_2bit
	str	lr, [r2, #188]	@ MemArrange.ChromOffset_2bit, <variable>.ChromOffset_2bit
	ldr	r3, [r4, #68]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stInstCfg.s32DecFsWidth
	str	r3, [r2, #192]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.FsWidth
	ldr	lr, [r4, #72]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stInstCfg.s32DecFsHeight
	str	lr, [r2, #196]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.FsHeight
	ldr	r3, [fp, #-448]	@ MemArrange.ChromOffset, MemArrange.ChromOffset
	str	r3, [r2, #200]	@ MemArrange.ChromOffset, <variable>.ChromOffset
	ldr	lr, [fp, #-444]	@ MemArrange.LumaPixelOffset, MemArrange.LumaPixelOffset
	str	lr, [r2, #204]	@ MemArrange.LumaPixelOffset, <variable>.LumaPixelOffset
	ldr	r3, [fp, #-440]	@ MemArrange.ChromaPixelOffset, MemArrange.ChromaPixelOffset
	strb	ip, [r2, #158]	@ tmp640, <variable>.DispState
	strb	ip, [r2, #156]	@ tmp640, <variable>.IsDecRef
	str	r3, [r2, #208]	@ MemArrange.ChromaPixelOffset, <variable>.ChromaPixelOffset
	strb	ip, [r2, #157]	@ tmp640, <variable>.IsTfRef
	b	.L684	@
.L727:
	ldrsb	r2, [r4, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	movw	ip, #42144	@ tmp423,
	mov	r1, #0	@ tmp424,
	mov	r9, #1	@ tmp421,
	str	r1, [r4, ip]	@ tmp424, <variable>.PhyFsID
	movw	r3, #42152	@ tmp425,
	strb	r9, [r4, #12]	@ tmp421, <variable>.s32TfFsNum
	sub	r9, fp, #44	@,,
	add	r6, r9, r2, asl #2	@, tmp430,, <variable>.s32DecFsNum,
	ldr	ip, [r4, #72]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stInstCfg.s32DecFsHeight
	movw	lr, #42160	@ tmp433,
	ldr	r5, [r6, #-932]	@ tmp432, MemArrange.FrameAddr
	ldr	r6, [r4, #68]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stInstCfg.s32DecFsWidth
	str	r5, [r4, r3]	@ tmp432, <variable>.PhyAddr
	ldr	r0, [fp, #-984]	@ MemArrange.VahbStride, MemArrange.VahbStride
	ldrsb	r3, [r4, #56]	@ <variable>.stInstCfg.s32DispLoopEnable, <variable>.stInstCfg.s32DispLoopEnable
	str	r0, [r4, lr]	@ MemArrange.VahbStride, <variable>.Stride
	movw	r0, #34484	@ tmp435,
	ldr	r5, [fp, #-464]	@ MemArrange.VahbStride_2bit, MemArrange.VahbStride_2bit
	cmp	r3, r1	@ <variable>.stInstCfg.s32DispLoopEnable,
	str	r5, [r4, r0]	@ MemArrange.VahbStride_2bit, <variable>.Stride_2bit
	movw	r0, #34488	@ tmp437,
	ldr	lr, [fp, #-456]	@ MemArrange.LumaOffset_2bit, MemArrange.LumaOffset_2bit
	movw	r5, #42176	@ tmp441,
	str	lr, [r4, r0]	@ MemArrange.LumaOffset_2bit, <variable>.LumaOffset_2bit
	ldr	lr, [fp, #-452]	@ MemArrange.ChromOffset_2bit, MemArrange.ChromOffset_2bit
	str	r6, [r4, r5]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.FsWidth
	movw	r5, #42180	@ tmp443,
	str	ip, [r4, r5]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.FsHeight
	movw	ip, #34492	@ tmp439,
	str	lr, [r4, ip]	@ MemArrange.ChromOffset_2bit, <variable>.ChromOffset_2bit
	movw	lr, #42184	@ tmp445,
	ldr	r0, [fp, #-448]	@ MemArrange.ChromOffset, MemArrange.ChromOffset
	str	r0, [r4, lr]	@ MemArrange.ChromOffset, <variable>.ChromOffset
	movw	r0, #42188	@ tmp447,
	ldr	ip, [fp, #-444]	@ MemArrange.LumaPixelOffset, MemArrange.LumaPixelOffset
	movw	lr, #42140	@ tmp451,
	str	ip, [r4, r0]	@ MemArrange.LumaPixelOffset, <variable>.LumaPixelOffset
	movw	r0, #42141	@ tmp454,
	ldr	ip, [fp, #-440]	@ MemArrange.ChromaPixelOffset, MemArrange.ChromaPixelOffset
	strb	r1, [r4, lr]	@ tmp424, <variable>.IsDecRef
	movw	lr, #42192	@ tmp449,
	strb	r1, [r4, r0]	@ tmp424, <variable>.IsTfRef
	movw	r0, #42142	@ tmp457,
	str	ip, [r4, lr]	@ MemArrange.ChromaPixelOffset, <variable>.ChromaPixelOffset
	strb	r1, [r4, r0]	@ tmp424, <variable>.DispState
	bne	.L686	@,
	mov	r2, r3	@ prephitmp.2079, <variable>.stInstCfg.s32DispLoopEnable
	strb	r3, [r4, #11]	@ <variable>.stInstCfg.s32DispLoopEnable, <variable>.s32DispFsNum
.L688:
	ldr	r7, [fp, #-992]	@, %sfp
	add	r1, r4, #38144	@ tmp463, D.38835,
	mov	ip, #0	@ ivtmp.2133,
	add	sl, r1, #176	@ ivtmp.2139, tmp463,
	add	r8, r7, #184	@ ivtmp.2143,,
	add	r6, r1, #168	@ ivtmp.2137, tmp463,
	add	r7, r1, #160	@ ivtmp.2131, tmp463,
	mov	r3, ip	@ i, ivtmp.2133
	mov	r5, ip	@ tmp638, ivtmp.2133
	ldr	r0, [fp, #-996]	@ ivtmp.2193, %sfp
	str	r2, [fp, #-1008]	@ prephitmp.2079, %sfp
	b	.L687	@
.L730:
	str	r3, [r7, #0]	@ i, <variable>.PhyFsID
	ldrsb	r2, [r4, #12]	@ <variable>.s32TfFsNum, <variable>.s32TfFsNum
	ldrsb	r9, [r4, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	add	lr, r3, r2	@ tmp483, i, <variable>.s32TfFsNum
	add	r2, lr, r9	@ tmp484, tmp483, <variable>.s32DecFsNum
	sub	r9, fp, #44	@,,
	add	lr, r9, r2, asl #2	@, tmp488,, tmp484,
	ldr	r9, [lr, #-932]	@ tmp490, MemArrange.FrameAddr
	str	r9, [r6, #0]	@ tmp490, <variable>.PhyAddr
	ldr	r2, [fp, #-984]	@ MemArrange.VahbStride, MemArrange.VahbStride
	str	r2, [sl, #0]	@ MemArrange.VahbStride, <variable>.Stride
	ldr	lr, [fp, #-464]	@ MemArrange.VahbStride_2bit, MemArrange.VahbStride_2bit
	str	lr, [r0, #0]	@ MemArrange.VahbStride_2bit, <variable>.Stride_2bit
	ldr	r9, [fp, #-456]	@ MemArrange.LumaOffset_2bit, MemArrange.LumaOffset_2bit
	str	r9, [r8, #0]	@ MemArrange.LumaOffset_2bit, <variable>.LumaOffset_2bit
	ldr	r2, [fp, #-452]	@ MemArrange.ChromOffset_2bit, MemArrange.ChromOffset_2bit
	ldr	r9, [fp, #-992]	@, %sfp
	str	r2, [r9, #188]	@ MemArrange.ChromOffset_2bit, <variable>.ChromOffset_2bit
	ldr	lr, [r4, #84]	@ <variable>.stInstCfg.s32DispFsWidth, <variable>.stInstCfg.s32DispFsWidth
	str	lr, [r1, #192]	@ <variable>.stInstCfg.s32DispFsWidth, <variable>.FsWidth
	ldr	r2, [r4, #88]	@ <variable>.stInstCfg.s32DispFsHeight, <variable>.stInstCfg.s32DispFsHeight
	str	r2, [r1, #196]	@ <variable>.stInstCfg.s32DispFsHeight, <variable>.FsHeight
	ldr	lr, [fp, #-448]	@ MemArrange.ChromOffset, MemArrange.ChromOffset
	str	lr, [r1, #200]	@ MemArrange.ChromOffset, <variable>.ChromOffset
	ldr	r2, [fp, #-444]	@ MemArrange.LumaPixelOffset, MemArrange.LumaPixelOffset
	str	r2, [r1, #204]	@ MemArrange.LumaPixelOffset, <variable>.LumaPixelOffset
	ldr	lr, [fp, #-440]	@ MemArrange.ChromaPixelOffset, MemArrange.ChromaPixelOffset
	strb	r5, [r1, #158]	@ tmp638, <variable>.DispState
	strb	r5, [r1, #156]	@ tmp638, <variable>.IsDecRef
	str	lr, [r1, #208]	@ MemArrange.ChromaPixelOffset, <variable>.ChromaPixelOffset
	strb	r5, [r1, #157]	@ tmp638, <variable>.IsTfRef
.L690:
	add	r3, r3, #1	@ i, i,
	add	r7, r7, #60	@ ivtmp.2131, ivtmp.2131,
	cmp	r3, #64	@ i,
	add	ip, ip, #60	@ ivtmp.2133, ivtmp.2133,
	add	r6, r6, #60	@ ivtmp.2137, ivtmp.2137,
	add	sl, sl, #60	@ ivtmp.2139, ivtmp.2139,
	add	r0, r0, #60	@ ivtmp.2193, ivtmp.2193,
	add	r8, r8, #60	@ ivtmp.2143, ivtmp.2143,
	beq	.L729	@,
	ldrsb	r9, [r4, #11]	@, <variable>.s32DispFsNum
	str	r9, [fp, #-1008]	@, %sfp
.L687:
	ldr	lr, [fp, #-1008]	@, %sfp
	add	r1, r4, ip	@ D.41958, D.38835, ivtmp.2133
	add	r2, r1, #34304	@, D.41958,
	add	r1, r1, #38144	@ tmp498, D.41958,
	cmp	r3, lr	@ i,
	str	r2, [fp, #-992]	@, %sfp
	str	r2, [fp, #-996]	@, %sfp
	mov	r2, r1	@ tmp541, tmp498
	blt	.L730	@,
	str	r5, [r7, #0]	@ tmp638, <variable>.PhyFsID
	ldrsb	r9, [r4, #12]	@ <variable>.s32TfFsNum, <variable>.s32TfFsNum
	ldrsb	r1, [r4, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	add	lr, r9, r1	@ tmp527, <variable>.s32TfFsNum, <variable>.s32DecFsNum
	sub	r9, fp, #44	@,,
	add	r1, r9, lr, asl #2	@, tmp531,, tmp527,
	ldr	r9, [r1, #-932]	@ tmp533, MemArrange.FrameAddr
	str	r9, [r6, #0]	@ tmp533, <variable>.PhyAddr
	ldr	lr, [fp, #-984]	@ MemArrange.VahbStride, MemArrange.VahbStride
	str	lr, [sl, #0]	@ MemArrange.VahbStride, <variable>.Stride
	ldr	r1, [fp, #-464]	@ MemArrange.VahbStride_2bit, MemArrange.VahbStride_2bit
	str	r1, [r0, #0]	@ MemArrange.VahbStride_2bit, <variable>.Stride_2bit
	ldr	r9, [fp, #-456]	@ MemArrange.LumaOffset_2bit, MemArrange.LumaOffset_2bit
	str	r9, [r8, #0]	@ MemArrange.LumaOffset_2bit, <variable>.LumaOffset_2bit
	ldr	lr, [fp, #-452]	@ MemArrange.ChromOffset_2bit, MemArrange.ChromOffset_2bit
	ldr	r9, [fp, #-996]	@, %sfp
	str	lr, [r9, #188]	@ MemArrange.ChromOffset_2bit, <variable>.ChromOffset_2bit
	ldr	r1, [r4, #84]	@ <variable>.stInstCfg.s32DispFsWidth, <variable>.stInstCfg.s32DispFsWidth
	str	r1, [r2, #192]	@ <variable>.stInstCfg.s32DispFsWidth, <variable>.FsWidth
	ldr	lr, [r4, #88]	@ <variable>.stInstCfg.s32DispFsHeight, <variable>.stInstCfg.s32DispFsHeight
	str	lr, [r2, #196]	@ <variable>.stInstCfg.s32DispFsHeight, <variable>.FsHeight
	ldr	r1, [fp, #-448]	@ MemArrange.ChromOffset, MemArrange.ChromOffset
	str	r1, [r2, #200]	@ MemArrange.ChromOffset, <variable>.ChromOffset
	ldr	lr, [fp, #-444]	@ MemArrange.LumaPixelOffset, MemArrange.LumaPixelOffset
	str	lr, [r2, #204]	@ MemArrange.LumaPixelOffset, <variable>.LumaPixelOffset
	ldr	r1, [fp, #-440]	@ MemArrange.ChromaPixelOffset, MemArrange.ChromaPixelOffset
	strb	r5, [r2, #158]	@ tmp638, <variable>.DispState
	strb	r5, [r2, #156]	@ tmp638, <variable>.IsDecRef
	str	r1, [r2, #208]	@ MemArrange.ChromaPixelOffset, <variable>.ChromaPixelOffset
	strb	r5, [r2, #157]	@ tmp638, <variable>.IsTfRef
	b	.L690	@
.L729:
	ldr	r0, [fp, #-48]	@ MemArrange.ValidPMVNum, MemArrange.ValidPMVNum
	add	ip, r4, #42240	@ ivtmp.2113, D.38835,
	add	r1, ip, #24	@ ivtmp.2113, ivtmp.2113,
	mov	r3, #1	@ i.2304,
	cmp	r0, #20	@ MemArrange.ValidPMVNum,
	movge	r0, #20	@ tmp567,
	mov	ip, #0	@ tmp637,
	uxtb	r5, r0	@ prephitmp.2221, tmp567
	strb	r5, [r4, #13]	@ prephitmp.2221, <variable>.s32PmvNum
	ldr	r2, [fp, #-172]	@ tmp662, MemArrange.PMVAddr
	sub	r5, fp, #984	@,,
	add	r0, r5, #4	@ ivtmp.2183,,
	strb	ip, [r4, #14]	@ tmp637, <variable>.IsPmvInUse
	ldrb	r5, [r4, #13]	@ zero_extendqisi2	@ prephitmp.2221, <variable>.s32PmvNum
	str	r2, [r1, #0]	@ tmp662, <variable>.PmvAddr
	add	r1, r1, #4	@ ivtmp.2113, ivtmp.2113,
	add	r2, r4, r3	@ ivtmp.2119, D.38835,
	b	.L695	@
.L731:
	ldr	r5, [r0, #812]	@ tmp666, MemArrange.PMVAddr
	strb	ip, [r2, #14]	@ tmp637, <variable>.IsPmvInUse
	str	r5, [r1, #0]	@ tmp666, <variable>.PmvAddr
.L713:
	ldrb	r5, [r4, #13]	@ zero_extendqisi2	@ prephitmp.2221, <variable>.s32PmvNum
	add	r3, r3, #1	@ i.2304, tmp641,
	add	r0, r0, #4	@ ivtmp.2183, tmp642,
	add	r1, r1, #4	@ ivtmp.2113, tmp643,
	add	r2, r2, #1	@ ivtmp.2119, tmp644,
.L695:
	sxtb	lr, r5	@ prephitmp.2221, prephitmp.2221
	cmp	lr, r3	@ prephitmp.2221, i.2304
	add	r3, r3, #1	@ tmp641, i.2304,
	ldrgt	lr, [r0, #812]	@ tmp572, MemArrange.PMVAddr
	add	r0, r0, #4	@ tmp642, ivtmp.2183,
	ldrle	lr, [fp, #-172]	@ MemArrange.PMVAddr, MemArrange.PMVAddr
	cmp	r3, #20	@ tmp641,
	strb	ip, [r2, #14]	@ tmp637, <variable>.IsPmvInUse
	add	r2, r2, #1	@ tmp644, ivtmp.2119,
	str	lr, [r1, #0]	@ MemArrange.PMVAddr, <variable>.PmvAddr
	add	r1, r1, #4	@ tmp643, ivtmp.2113,
	beq	.L694	@,
	ldrsb	r5, [r4, #13]	@ prephitmp.2221, <variable>.s32PmvNum
	cmp	r5, r3	@ prephitmp.2221, tmp641
	bgt	.L731	@,
	ldr	lr, [fp, #-172]	@ MemArrange.PMVAddr, MemArrange.PMVAddr
	strb	ip, [r2, #14]	@ tmp637, <variable>.IsPmvInUse
	str	lr, [r1, #0]	@ MemArrange.PMVAddr, <variable>.PmvAddr
	b	.L713	@
.L694:
	movw	r5, #34472	@ tmp583,
	ldr	r0, [fp, #-52]	@ MemArrange.HafPmvOffset, MemArrange.HafPmvOffset
	ldr	r1, [r4, r5]	@ <variable>.PhyAddr, <variable>.PhyAddr
	movw	r3, #42260	@ tmp578,
	movw	lr, #34412	@ tmp582,
	movw	r2, #34404	@ tmp580,
	str	r0, [r4, r3]	@ MemArrange.HafPmvOffset, <variable>.s32HalfPmvOffset
	mov	r3, #0	@ tmp581,
	str	r1, [r4, lr]	@ <variable>.PhyAddr, <variable>.stDummyPhyFs.PhyAddr
	movw	r5, #34420	@ tmp585,
	str	r3, [r4, r2]	@ tmp581, <variable>.stDummyPhyFs.PhyFsID
	movw	r0, #34424	@ tmp587,
	ldr	ip, [fp, #-984]	@ MemArrange.VahbStride, MemArrange.VahbStride
	ldr	r2, [r4, #68]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stInstCfg.s32DecFsWidth
	ldr	lr, [r4, #40]	@ <variable>.stPreInfo.s32PreWidth, <variable>.stPreInfo.s32PreWidth
	str	ip, [r4, r5]	@ MemArrange.VahbStride, <variable>.stDummyPhyFs.Stride
	ldr	r5, [fp, #-464]	@ MemArrange.VahbStride_2bit, MemArrange.VahbStride_2bit
	cmp	r2, lr	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stPreInfo.s32PreWidth
	ldr	r1, [r4, #72]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stInstCfg.s32DecFsHeight
	movw	lr, #34436	@ tmp593,
	str	r5, [r4, r0]	@ MemArrange.VahbStride_2bit, <variable>.stDummyPhyFs.Stride_2bit
	movw	r0, #34428	@ tmp589,
	ldr	ip, [fp, #-456]	@ MemArrange.LumaOffset_2bit, MemArrange.LumaOffset_2bit
	str	ip, [r4, r0]	@ MemArrange.LumaOffset_2bit, <variable>.stDummyPhyFs.LumaOffset_2bit
	movw	r0, #34440	@ tmp595,
	ldr	ip, [fp, #-452]	@ MemArrange.ChromOffset_2bit, MemArrange.ChromOffset_2bit
	str	r2, [r4, lr]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stDummyPhyFs.FsWidth
	movw	lr, #34432	@ tmp591,
	str	r1, [r4, r0]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stDummyPhyFs.FsHeight
	str	ip, [r4, lr]	@ MemArrange.ChromOffset_2bit, <variable>.stDummyPhyFs.ChromOffset_2bit
	movw	lr, #34444	@ tmp597,
	ldr	r0, [fp, #-448]	@ MemArrange.ChromOffset, MemArrange.ChromOffset
	str	r0, [r4, lr]	@ MemArrange.ChromOffset, <variable>.stDummyPhyFs.ChromOffset
	movw	r0, #34448	@ tmp599,
	ldr	ip, [fp, #-444]	@ MemArrange.LumaPixelOffset, MemArrange.LumaPixelOffset
	movw	lr, #34402	@ tmp609,
	str	ip, [r4, r0]	@ MemArrange.LumaPixelOffset, <variable>.stDummyPhyFs.LumaPixelOffset
	movw	r0, #34400	@ tmp603,
	ldr	ip, [fp, #-440]	@ MemArrange.ChromaPixelOffset, MemArrange.ChromaPixelOffset
	strb	r3, [r4, lr]	@ tmp581, <variable>.stDummyPhyFs.DispState
	movw	lr, #34452	@ tmp601,
	strb	r3, [r4, r0]	@ tmp581, <variable>.stDummyPhyFs.IsDecRef
	movw	r0, #34401	@ tmp606,
	str	ip, [r4, lr]	@ MemArrange.ChromaPixelOffset, <variable>.stDummyPhyFs.ChromaPixelOffset
	strb	r3, [r4, r0]	@ tmp581, <variable>.stDummyPhyFs.IsTfRef
	beq	.L710	@,
.L714:
	ldrsb	r3, [r4, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
.L696:
	movw	r0, #34532	@ tmp619,
	movw	lr, #34472	@ tmp620,
	ldr	ip, [r4, r0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	ldr	r0, [r4, lr]	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	r2, [r4, #40]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stPreInfo.s32PreWidth
	str	r1, [r4, #44]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stPreInfo.s32PreHeight
	rsb	r2, r0, ip	@ tmp623, <variable>.PhyAddr, <variable>.PhyAddr
	str	r3, [r4, #48]	@ <variable>.s32DecFsNum, <variable>.stPreInfo.s32PreDecNum
	str	r2, [r4, #52]	@ tmp623, <variable>.stPreInfo.s32PreDecSlotLen
.L697:
	ldr	r3, [fp, #-980]	@ MemArrange.TotalMemUsed, MemArrange.TotalMemUsed
	mov	r0, #0	@ D.38833,
	ldr	r1, [fp, #-1000]	@, %sfp
	str	r3, [r1, #0]	@ MemArrange.TotalMemUsed,
	b	.L653	@
.L710:
	ldr	ip, [r4, #44]	@ <variable>.stPreInfo.s32PreHeight, <variable>.stPreInfo.s32PreHeight
	cmp	r1, ip	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stPreInfo.s32PreHeight
	bne	.L714	@,
	ldrsb	r3, [r4, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	ldr	lr, [r4, #48]	@ <variable>.stPreInfo.s32PreDecNum, <variable>.stPreInfo.s32PreDecNum
	cmp	r3, lr	@ <variable>.s32DecFsNum, <variable>.stPreInfo.s32PreDecNum
	bne	.L696	@,
	b	.L697	@
.L686:
	ldr	r3, [fp, #-436]	@ MemArrange.ValidFrameNum, MemArrange.ValidFrameNum
	ldrsb	ip, [r4, #63]	@ <variable>.stInstCfg.s32ExpectedDispFsNum, <variable>.stInstCfg.s32ExpectedDispFsNum
	sub	r0, r3, #1	@ tmp468, MemArrange.ValidFrameNum,
	rsb	lr, r2, r0	@ tmp467, <variable>.s32DecFsNum, tmp468
	cmp	lr, #25	@ tmp467,
	movge	lr, #25	@ tmp646,
	uxtb	r2, lr	@ prephitmp.2079, tmp646
	strb	r2, [r4, #11]	@ prephitmp.2079, <variable>.s32DispFsNum
	sxtb	r2, r2	@ prephitmp.2079, prephitmp.2079
	cmp	ip, r2	@ <variable>.stInstCfg.s32ExpectedDispFsNum, prephitmp.2079
	ble	.L688	@,
	strb	r1, [r4, #9]	@ tmp424, <variable>.s8TotalValidFsNum
	mov	r0, r1	@, tmp424
	ldrsb	r3, [r4, #61]	@ <variable>.stInstCfg.s32ExpectedDecFsNum, <variable>.stInstCfg.s32ExpectedDecFsNum
	movw	r1, #:lower16:.LC61	@,
	movt	r1, #:upper16:.LC61	@,
	str	ip, [sp, #0]	@ <variable>.stInstCfg.s32ExpectedDispFsNum,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38833,
	b	.L653	@
.L679:
	ldrb	sl, [r4, #61]	@ zero_extendqisi2	@ prephitmp.2247, <variable>.stInstCfg.s32ExpectedDecFsNum
	strb	sl, [r4, #10]	@ prephitmp.2247, <variable>.s32DecFsNum
	b	.L681	@
.L680:
	ldr	r3, [fp, #-436]	@ MemArrange.ValidFrameNum, MemArrange.ValidFrameNum
	cmp	r3, #40	@ MemArrange.ValidFrameNum,
	movge	r3, #40	@ tmp335,
	uxtb	sl, r3	@ prephitmp.2247, tmp335
	strb	sl, [r4, #10]	@ prephitmp.2247, <variable>.s32DecFsNum
	b	.L681	@
.L720:
	cmp	r0, #32	@ eChanCapLevel,
	bhi	.L732	@,
	rsb	lr, r0, r0, asl #3	@, tmp231, eChanCapLevel, eChanCapLevel,
	movw	r3, #:lower16:CapItem	@ tmp228,
	add	ip, lr, #1	@ tmp239, tmp231,
	movt	r3, #:upper16:CapItem	@ tmp228,
	mov	r2, r0	@, eChanCapLevel
	movw	r1, #:lower16:.LC57	@,
	ldr	ip, [r3, ip, asl #2]	@ tmp240, CapItem
	movt	r1, #:upper16:.LC57	@,
	ldr	r3, [r3, lr, asl #2]	@ tmp234, CapItem
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ tmp240,
	ldr	lr, [r4, #68]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stInstCfg.s32DecFsWidth
	str	lr, [sp, #4]	@ <variable>.stInstCfg.s32DecFsWidth,
	ldr	ip, [r4, #72]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stInstCfg.s32DecFsHeight
	str	ip, [sp, #8]	@ <variable>.stInstCfg.s32DecFsHeight,
	bl	dprint_vfmw	@
.L658:
	mov	r0, #0	@ tmp243,
	strb	r0, [r4, #9]	@ tmp243, <variable>.s8TotalValidFsNum
	mvn	r0, #0	@ D.38833,
	b	.L653	@
.L725:
	bl	OSAL_GetTimeInMs	@
	ldr	ip, [r7, r5, asl #2]	@ temp.2235, s_pstVfmwChan
	movw	r3, #:lower16:251460	@ tmp296,
	movt	r3, #:upper16:251460	@ tmp296,
	movw	r1, #:lower16:251480	@ tmp295,
	movt	r1, #:upper16:251480	@ tmp295,
	ldr	lr, [ip, r3]	@ <variable>.stDynamicFSTimestamp.u32StartTime, <variable>.stDynamicFSTimestamp.u32StartTime
	movw	r2, #:lower16:251464	@ tmp300,
	movt	r2, #:upper16:251464	@ tmp300,
	rsb	r0, lr, r0	@ tmp298, <variable>.stDynamicFSTimestamp.u32StartTime,
	str	r0, [ip, r1]	@ tmp298, <variable>.stDynamicFSTimestamp.u32AllTime
	ldr	r1, [r7, r5, asl #2]	@ temp.2236, s_pstVfmwChan
	movw	lr, #:lower16:251472	@ tmp302,
	movt	lr, #:upper16:251472	@ tmp302,
	ldr	ip, [r1, r2]	@ D.38912, <variable>.stDynamicFSTimestamp.u32PreEndTime
	movw	r2, #:lower16:251468	@ tmp304,
	ldr	r3, [r1, r3]	@ temp.2237, <variable>.stDynamicFSTimestamp.u32StartTime
	movt	r2, #:upper16:251468	@ tmp304,
	cmp	ip, r3	@ D.38912, temp.2237
	rsbcs	r8, r3, ip	@ iftmp.475, temp.2237, D.38912
	str	r8, [r1, lr]	@ iftmp.475, <variable>.stDynamicFSTimestamp.u32PreAllocTime
	ldr	r1, [r6, r5, asl #2]	@ temp.2238, s_pstVfmwChan
	movw	ip, #:lower16:251460	@ tmp305,
	movt	ip, #:upper16:251460	@ tmp305,
	ldr	lr, [r1, r2]	@ D.38917, <variable>.stDynamicFSTimestamp.u32MMZEndTime
	movw	r2, #:lower16:251480	@ tmp309,
	ldr	r3, [r1, ip]	@ temp.2239, <variable>.stDynamicFSTimestamp.u32StartTime
	movw	ip, #:lower16:251476	@ tmp306,
	movt	ip, #:upper16:251476	@ tmp306,
	movt	r2, #:upper16:251480	@ tmp309,
	cmp	lr, r3	@ D.38917, temp.2239
	rsbcs	r0, r3, lr	@ iftmp.476, temp.2239, D.38917
	movw	r3, #:lower16:g_u32DFSMaxAllocTime	@ tmp310,
	movcc	r0, #0	@ iftmp.476,
	str	r0, [r1, ip]	@ iftmp.476, <variable>.stDynamicFSTimestamp.u32MMZAllocTime
	ldr	r0, [r6, r5, asl #2]	@ tmp308, s_pstVfmwChan
	movt	r3, #:upper16:g_u32DFSMaxAllocTime	@ tmp310,
	ldr	lr, [r3, #0]	@ g_u32DFSMaxAllocTime, g_u32DFSMaxAllocTime
	ldr	ip, [r0, r2]	@ g_u32DFSMaxAllocTime.478, <variable>.stDynamicFSTimestamp.u32AllTime
	cmp	ip, lr	@ g_u32DFSMaxAllocTime.478, g_u32DFSMaxAllocTime
	strhi	ip, [r3, #0]	@ g_u32DFSMaxAllocTime.478, g_u32DFSMaxAllocTime
	b	.L672	@
.L732:
	mov	r2, r0	@, eChanCapLevel
	movw	r1, #:lower16:.LC56	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC56	@,
	bl	dprint_vfmw	@
	b	.L658	@
.L717:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #651	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38833,
	b	.L653	@
.L718:
	mov	r0, r4	@, D.38835
	movw	r1, #:lower16:.LC0	@,
	mov	r2, #652	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38833,
	b	.L653	@
.L726:
	mov	r0, #0	@,
	mov	r3, sl	@, MinFsNum
	movw	r1, #:lower16:.LC62	@,
	mov	r2, r0	@,
	movt	r1, #:upper16:.LC62	@,
	str	ip, [sp, #0]	@ temp.2241,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38833,
	b	.L653	@
.L724:
	ldr	r3, [r4, #68]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stInstCfg.s32DecFsWidth
	cmp	r2, r3	@ D.38864, <variable>.stInstCfg.s32DecFsWidth
	beq	.L660	@,
	mvn	r0, #0	@ D.38833,
	b	.L653	@
	.fnend
	.size	FSP_PartitionFsMemory, .-FSP_PartitionFsMemory
	.align	2
	.global	FSP_ClearNotInVoQueue
	.type	FSP_ClearNotInVoQueue, %function
FSP_ClearNotInVoQueue:
	.fnstart
.LFB1544:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ InstID,
	mov	r8, r0	@ InstID, InstID
	mov	r9, r1	@ pstVoQue, pstVoQue
	bhi	.L746	@,
	cmp	r1, #0	@ pstVoQue,
	beq	.L747	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp147,
	movt	r3, #:upper16:.LANCHOR0	@ tmp147,
	ldr	sl, [r3, r0, asl #2]	@ D.38767, s_pFspInst
	cmp	sl, #0	@ D.38767,
	movne	r5, sl	@ ivtmp.2357, D.38767
	movne	r4, #0	@ i,
	bne	.L739	@,
	b	.L751	@
.L738:
	mov	r0, r8	@, InstID
	ldr	r1, [r6, #300]	@, <variable>.stDispImg.image_id
	mov	r2, #0	@,
	mov	r4, #536	@,
	bl	FSP_SetRef	@
	mla	r2, r4, r7, sl	@ tmp167,, tmp159, D.38767
	mov	r0, r9	@, pstVoQue
	add	r1, r2, #104	@, tmp167,
	bl	IsImageInVoQueue	@
	cmp	r0, #0	@,
	bne	.L749	@,
	add	r4, r7, #1	@ i, tmp159,
	add	r5, r6, #536	@ ivtmp.2357, tmp160,
	cmp	r4, #64	@ i,
	beq	.L750	@,
.L739:
	ldr	r1, [r5, #300]	@, <variable>.stDispImg.image_id
	mov	r2, #0	@,
	mov	r0, r8	@, InstID
	add	r6, r5, #536	@ tmp160, ivtmp.2357,
	bl	FSP_SetRef	@
	mov	r0, #536	@,
	mla	r1, r0, r4, sl	@ tmp154,, i, D.38767
	mov	r0, r9	@, pstVoQue
	add	r7, r4, #1	@ tmp159, i,
	add	r1, r1, #104	@, tmp154,
	bl	IsImageInVoQueue	@
	cmp	r0, #0	@,
	beq	.L738	@,
	ldr	r1, [r5, #300]	@, <variable>.stDispImg.image_id
	mov	r0, r8	@, InstID
	mov	r2, #0	@,
	bl	FSP_SetDisplay	@
	b	.L738	@
.L749:
	mov	r2, #0	@,
	mov	r0, r8	@, InstID
	ldr	r1, [r6, #300]	@, <variable>.stDispImg.image_id
	add	r4, r7, #1	@ i, tmp159,
	bl	FSP_SetDisplay	@
	cmp	r4, #64	@ i,
	add	r5, r6, #536	@ ivtmp.2357, tmp160,
	bne	.L739	@,
.L750:
	mov	r0, #0	@ D.38763,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L746:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #546	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38763,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L751:
	mov	r0, sl	@, D.38767
	movw	r1, #:lower16:.LC0	@,
	mov	r2, #548	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38763,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L747:
	mov	r0, r1	@, pstVoQue
	movw	r2, #547	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r3, #:lower16:.LC63	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r3, #:upper16:.LC63	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38763,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	.fnend
	.size	FSP_ClearNotInVoQueue, .-FSP_ClearNotInVoQueue
	.global	s_pFspInst
	.global	s_FspVoQue
	.global	g_SpinLock_fsp
	.section	.rodata
	.align	2
.LANCHOR2 = . + 0
	.type	__func__.39239, %object
	.size	__func__.39239, 15
__func__.39239:
	.ascii	"FSP_NewLogicFs\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"fsp.c,L%d: %s\012\000"
	.space	1
.LC1:
	.ascii	"InstID out of range\000"
.LC2:
	.ascii	"fsp is not inited\000"
	.space	2
.LC3:
	.ascii	"p_image NULL\000"
	.space	3
.LC4:
	.ascii	"Flag Invalid\000"
	.space	3
.LC5:
	.ascii	"FSP CONTEXT:\012\000"
	.space	2
.LC6:
	.ascii	"%-35s :%d\012\000"
	.space	1
.LC7:
	.ascii	"FspInstState\000"
	.space	3
.LC8:
	.ascii	"DecFsWidth\000"
	.space	1
.LC9:
	.ascii	"DecFsHeight\000"
.LC10:
	.ascii	"DispFsWidth\000"
.LC11:
	.ascii	"DispFsHeight\000"
	.space	3
.LC12:
	.ascii	"ExpectedDecFsNum\000"
	.space	3
.LC13:
	.ascii	"ExpectedDispFsNum\000"
	.space	2
.LC14:
	.ascii	"ExpectedPmvNum\000"
	.space	1
.LC15:
	.ascii	"DecFsNum\000"
	.space	3
.LC16:
	.ascii	"DispFsNum\000"
	.space	2
.LC17:
	.ascii	"PmvNum\000"
	.space	1
.LC18:
	.ascii	"logic fs: %d\012\000"
	.space	2
.LC19:
	.ascii	"%d%d \000"
	.space	2
.LC20:
	.ascii	"\012\000"
	.space	2
.LC21:
	.ascii	"\012dec fs: %d\012\000"
	.space	3
.LC22:
	.ascii	"\012disp fs: %d\012\000"
	.space	2
.LC23:
	.ascii	"\012pmv: %d\012\000"
	.space	2
.LC24:
	.ascii	"%d \000"
.LC25:
	.ascii	"\012\012\000"
	.space	1
.LC26:
	.ascii	"PmvAddrTab is NULL\012\000"
.LC27:
	.ascii	"PmvNum is NULL\012\000"
.LC28:
	.ascii	"DecFsAddrTab is NULL\012\000"
	.space	2
.LC29:
	.ascii	"DecFsNum is NULL\012\000"
	.space	2
.LC30:
	.ascii	"FSP_GetRef: InstID out of range\000"
.LC31:
	.ascii	"FSP_GetRef: LogicFrameID out of range\000"
	.space	2
.LC32:
	.ascii	"FSP_GetRef: Fsp is not inited\000"
	.space	2
.LC33:
	.ascii	"LogicFrameID out of range\000"
	.space	2
.LC34:
	.ascii	"%s : AllocFrame func null\012\000"
	.space	1
.LC35:
	.ascii	"fsp.c, line %d: pstLogicFs->PmvIdc out of range(=%d"
	.ascii	")\012\000"
	.space	2
.LC36:
	.ascii	"PhyAddr is NULL\012\000"
	.space	3
.LC37:
	.ascii	"pFsNum is NULL\012\000"
.LC38:
	.ascii	"fsp instance not in used\000"
	.space	3
.LC39:
	.ascii	"FSP_UdateInfo ArrangeMem failed!\012\000"
	.space	2
.LC40:
	.ascii	"%s : RleaseFrame func null\012\000"
.LC41:
	.ascii	"FSP_SetDisplay: LogicTick=%d, DispTick=%d!\012\000"
.LC42:
	.ascii	"FSP_IsFsLeak: fsp is not inited \012\000"
	.space	2
.LC43:
	.ascii	"No free fs: ref=%d,read=%d,new=%d,total=%d\012\000"
.LC44:
	.ascii	"pFspInst = NULL\000"
.LC45:
	.ascii	"pstFspInstCfg = NULL\000"
	.space	3
.LC46:
	.ascii	"This inst is not active\000"
.LC47:
	.ascii	"no logic frame store!!!\012\000"
	.space	3
.LC48:
	.ascii	"%s no decode phy fs\012\000"
	.space	3
.LC49:
	.ascii	"%s Not partition yet!\012\000"
	.space	1
.LC50:
	.ascii	"no pmv memory\012\000"
	.space	1
.LC51:
	.ascii	"no display phy fs\012\000"
	.space	1
.LC52:
	.ascii	"can not find disp fs\012\000"
	.space	2
.LC53:
	.ascii	"RefNum,ReadNum,NewNum,Total = %d,%d,%d,%d\012\000"
	.space	1
.LC54:
	.ascii	"FSP_AllocFrame failed\012\000"
	.space	1
.LC55:
	.ascii	"invalid stFrameInfo PhyAddr\012\000"
	.space	3
.LC56:
	.ascii	"eChanCapLevel = %d is not expected!\012\000"
	.space	3
.LC57:
	.ascii	"decode channel CapLevel is %d(w=%d,h=%d), this stre"
	.ascii	"am (w=%d,h=%d) can NOT be decoded!\012\000"
	.space	1
.LC58:
	.ascii	"DFS, Wrong Partition State. State: 0x%x\012\000"
	.space	3
.LC59:
	.ascii	"DFS, Mem Element Fill Successed! Ready to Decode!\012"
	.ascii	"\000"
	.space	1
.LC60:
	.ascii	"Fsp arrange failed, return %d\012\000"
	.space	1
.LC61:
	.ascii	"disp fs(=%d) less than expected(=%d+%d)!\012\000"
	.space	2
.LC62:
	.ascii	"arrange ret %d, min = %d, actual = %d\012\000"
	.space	1
.LC63:
	.ascii	"pstVoQue is NULL\000"
	.bss
	.align	2
.LANCHOR0 = . + 0
.LANCHOR1 = . + 8184
	.type	s_pFspInst, %object
	.size	s_pFspInst, 64
s_pFspInst:
	.space	64
	.type	s_FspVoQue, %object
	.size	s_FspVoQue, 4224
s_FspVoQue:
	.space	4224
	.type	g_IsFrameIntfValid, %object
	.size	g_IsFrameIntfValid, 4
g_IsFrameIntfValid:
	.space	4
	.type	g_FspFrameIntf, %object
	.size	g_FspFrameIntf, 16
g_FspFrameIntf:
	.space	16
	.type	g_SpinLock_fsp, %object
	.size	g_SpinLock_fsp, 12
g_SpinLock_fsp:
	.space	12
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
