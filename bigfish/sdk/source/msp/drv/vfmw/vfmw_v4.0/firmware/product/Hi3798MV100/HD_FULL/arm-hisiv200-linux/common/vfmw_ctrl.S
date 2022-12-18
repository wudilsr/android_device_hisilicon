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
	.file	"vfmw_ctrl.c"
@ GNU C (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) version 4.4.1 (arm-hisiv200-linux-gnueabi)
@	compiled by GNU C version 4.1.1 20061011 (Red Hat 4.1.1-30), GMP version 4.3.1, MPFR version 2.4.2.
@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
@ options passed:  -nostdinc
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include
@ -Iarch/arm/include/generated
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include
@ -Iinclude
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/uapi
@ -Iarch/arm/include/generated/uapi
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/uapi
@ -Iinclude/generated/uapi
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0
@ -Idrivers/msp/vfmw/vfmw_v4.0
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/mach-hi3798mx/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/drv/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/scene/stb
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/common
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/osal/linux_kernel
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/common/softlib
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/common/syntax
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/driver/HiSCDV200
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/product/Hi3798MV100
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/common_test/vdecko
@ -imultilib armv7a_soft -iprefix
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/
@ -isysroot /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../target
@ -D__KERNEL__ -D__LINUX_ARM_ARCH__=7 -Uarm -DCHIP_TYPE_hi3796mv100
@ -DSDK_VERSION=HiSTBAndroidV600R001C00SPC062_v2015072619 -DHI_MCE_SUPPORT
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
@ -DKBUILD_BASENAME=KBUILD_STR(vfmw_ctrl)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/vfmw/vfmw_v4.0/firmware/common/.vfmw_ctrl.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/common/vfmw_ctrl.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/vfmw/vfmw_v4.0/firmware/common/vfmw_ctrl.o -O2 -Wall -Wundef
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
	.global	VCTRL_GetFrameInterface
	.type	VCTRL_GetFrameInterface, %function
VCTRL_GetFrameInterface:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	ldr	r0, [r3, r0, asl #2]	@ D.50296, s_pstVfmwChan
	cmp	r0, #0	@ D.50296,
	addne	r0, r0, #172	@ D.50299, D.50296,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetFrameInterface, .-VCTRL_GetFrameInterface
	.align	2
	.global	VCTRL_GetSyntaxCtx
	.type	VCTRL_GetSyntaxCtx, %function
VCTRL_GetSyntaxCtx:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	ldr	r0, [r3, r0, asl #2]	@ D.50345, s_pstVfmwChan
	cmp	r0, #0	@ D.50345,
	addne	r0, r0, #250880	@ D.50348, D.50345,
	addne	r0, r0, #696	@ D.50348, D.50348,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetSyntaxCtx, .-VCTRL_GetSyntaxCtx
	.align	2
	.global	VCTRL_GetImageInterface
	.type	VCTRL_GetImageInterface, %function
VCTRL_GetImageInterface:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	ldr	r0, [r3, r0, asl #2]	@ D.50406, s_pstVfmwChan
	cmp	r0, #0	@ D.50406,
	addne	r0, r0, #160	@ D.50409, D.50406,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetImageInterface, .-VCTRL_GetImageInterface
	.align	2
	.global	VCTRL_GetChanCtxSize
	.type	VCTRL_GetChanCtxSize, %function
VCTRL_GetChanCtxSize:
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
	cmp	r0, #26	@ eCapLevel,
	movweq	r3, #:lower16:11613560	@ tmp135,
	movwne	r3, #:lower16:4780696	@ tmp136,
	movteq	r3, #:upper16:11613560	@ tmp135,
	movtne	r3, #:upper16:4780696	@ tmp136,
	str	r3, [r1, #0]	@ tmp136,* s32ChanCtxSize
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetChanCtxSize, .-VCTRL_GetChanCtxSize
	.align	2
	.global	VCTRL_CmpConfigParameter
	.type	VCTRL_CmpConfigParameter, %function
VCTRL_CmpConfigParameter:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp139,
	movt	r3, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r3, [r3, r0, asl #2]	@ D.51266, s_pstVfmwChan
	ldr	r2, [r3, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, #19	@ <variable>.eVidStd,
	bne	.L24	@,
.L18:
	mvn	r0, #0	@ D.51319,
	ldmfd	sp, {fp, sp, pc}	@
.L24:
	ldr	r2, [r3, #48]	@ D.51271, <variable>.stChanCfg.eVidStd
	ldr	r0, [r1, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, r0	@ D.51271, <variable>.eVidStd
	bne	.L18	@,
	ldr	ip, [r3, #64]	@ <variable>.stChanCfg.s32ChanErrThr, <variable>.stChanCfg.s32ChanErrThr
	ldr	r0, [r1, #16]	@ <variable>.s32ChanErrThr, <variable>.s32ChanErrThr
	cmp	ip, r0	@ <variable>.stChanCfg.s32ChanErrThr, <variable>.s32ChanErrThr
	bne	.L18	@,
	ldr	ip, [r3, #60]	@ <variable>.stChanCfg.s32ChanPriority, <variable>.stChanCfg.s32ChanPriority
	ldr	r0, [r1, #12]	@ <variable>.s32ChanPriority, <variable>.s32ChanPriority
	cmp	ip, r0	@ <variable>.stChanCfg.s32ChanPriority, <variable>.s32ChanPriority
	bne	.L18	@,
	ldr	ip, [r3, #68]	@ <variable>.stChanCfg.s32ChanStrmOFThr, <variable>.stChanCfg.s32ChanStrmOFThr
	ldr	r0, [r1, #20]	@ <variable>.s32ChanStrmOFThr, <variable>.s32ChanStrmOFThr
	cmp	ip, r0	@ <variable>.stChanCfg.s32ChanStrmOFThr, <variable>.s32ChanStrmOFThr
	bne	.L18	@,
	ldr	ip, [r3, #72]	@ <variable>.stChanCfg.s32DecMode, <variable>.stChanCfg.s32DecMode
	ldr	r0, [r1, #24]	@ <variable>.s32DecMode, <variable>.s32DecMode
	cmp	ip, r0	@ <variable>.stChanCfg.s32DecMode, <variable>.s32DecMode
	bne	.L18	@,
	ldr	ip, [r3, #76]	@ <variable>.stChanCfg.s32DecOrderOutput, <variable>.stChanCfg.s32DecOrderOutput
	ldr	r0, [r1, #28]	@ <variable>.s32DecOrderOutput, <variable>.s32DecOrderOutput
	cmp	ip, r0	@ <variable>.stChanCfg.s32DecOrderOutput, <variable>.s32DecOrderOutput
	bne	.L18	@,
	ldr	ip, [r3, #84]	@ <variable>.stChanCfg.s32DnrDispOutEnable, <variable>.stChanCfg.s32DnrDispOutEnable
	ldr	r0, [r1, #36]	@ <variable>.s32DnrDispOutEnable, <variable>.s32DnrDispOutEnable
	cmp	ip, r0	@ <variable>.stChanCfg.s32DnrDispOutEnable, <variable>.s32DnrDispOutEnable
	bne	.L18	@,
	ldr	ip, [r3, #80]	@ <variable>.stChanCfg.s32DnrTfEnable, <variable>.stChanCfg.s32DnrTfEnable
	ldr	r0, [r1, #32]	@ <variable>.s32DnrTfEnable, <variable>.s32DnrTfEnable
	cmp	ip, r0	@ <variable>.stChanCfg.s32DnrTfEnable, <variable>.s32DnrTfEnable
	bne	.L18	@,
	ldr	ip, [r3, #100]	@ <variable>.stChanCfg.s32VcmpEn, <variable>.stChanCfg.s32VcmpEn
	ldr	r0, [r1, #52]	@ <variable>.s32VcmpEn, <variable>.s32VcmpEn
	cmp	ip, r0	@ <variable>.stChanCfg.s32VcmpEn, <variable>.s32VcmpEn
	bne	.L18	@,
	ldr	ip, [r3, #112]	@ <variable>.stChanCfg.s32VcmpWmEndLine, <variable>.stChanCfg.s32VcmpWmEndLine
	ldr	r0, [r1, #64]	@ <variable>.s32VcmpWmEndLine, <variable>.s32VcmpWmEndLine
	cmp	ip, r0	@ <variable>.stChanCfg.s32VcmpWmEndLine, <variable>.s32VcmpWmEndLine
	bne	.L18	@,
	ldr	ip, [r3, #108]	@ <variable>.stChanCfg.s32VcmpWmStartLine, <variable>.stChanCfg.s32VcmpWmStartLine
	ldr	r0, [r1, #60]	@ <variable>.s32VcmpWmStartLine, <variable>.s32VcmpWmStartLine
	cmp	ip, r0	@ <variable>.stChanCfg.s32VcmpWmStartLine, <variable>.s32VcmpWmStartLine
	bne	.L18	@,
	ldr	ip, [r3, #104]	@ <variable>.stChanCfg.s32WmEn, <variable>.stChanCfg.s32WmEn
	ldr	r0, [r1, #56]	@ <variable>.s32WmEn, <variable>.s32WmEn
	cmp	ip, r0	@ <variable>.stChanCfg.s32WmEn, <variable>.s32WmEn
	bne	.L18	@,
	ldr	ip, [r3, #116]	@ <variable>.stChanCfg.s32SupportAllP, <variable>.stChanCfg.s32SupportAllP
	ldr	r0, [r1, #68]	@ <variable>.s32SupportAllP, <variable>.s32SupportAllP
	cmp	ip, r0	@ <variable>.stChanCfg.s32SupportAllP, <variable>.s32SupportAllP
	bne	.L18	@,
	cmp	r2, #1	@ D.51271,
	beq	.L25	@,
	sub	r0, r2, #10	@ tmp170, D.51271,
	cmp	r0, #2	@ tmp170,
	bhi	.L20	@,
	ldr	r2, [r3, #52]	@ <variable>.stChanCfg.StdExt.Vp6Ext.bReversed, <variable>.stChanCfg.StdExt.Vp6Ext.bReversed
	ldr	ip, [r1, #4]	@ <variable>.StdExt.Vp6Ext.bReversed, <variable>.StdExt.Vp6Ext.bReversed
	cmp	r2, ip	@ <variable>.stChanCfg.StdExt.Vp6Ext.bReversed, <variable>.StdExt.Vp6Ext.bReversed
	bne	.L18	@,
.L20:
	mov	r0, #0	@ D.51319,
	ldmfd	sp, {fp, sp, pc}	@
.L25:
	ldr	r0, [r3, #52]	@ <variable>.stChanCfg.StdExt.Vc1Ext.IsAdvProfile, <variable>.stChanCfg.StdExt.Vc1Ext.IsAdvProfile
	ldr	r2, [r1, #4]	@ <variable>.StdExt.Vc1Ext.IsAdvProfile, <variable>.StdExt.Vc1Ext.IsAdvProfile
	cmp	r0, r2	@ <variable>.stChanCfg.StdExt.Vc1Ext.IsAdvProfile, <variable>.StdExt.Vc1Ext.IsAdvProfile
	bne	.L18	@,
	ldr	ip, [r3, #56]	@ <variable>.stChanCfg.StdExt.Vc1Ext.CodecVersion, <variable>.stChanCfg.StdExt.Vc1Ext.CodecVersion
	ldr	r3, [r1, #8]	@ <variable>.StdExt.Vc1Ext.CodecVersion, <variable>.StdExt.Vc1Ext.CodecVersion
	cmp	ip, r3	@ <variable>.stChanCfg.StdExt.Vc1Ext.CodecVersion, <variable>.StdExt.Vc1Ext.CodecVersion
	beq	.L20	@,
	b	.L18	@
	.fnend
	.size	VCTRL_CmpConfigParameter, .-VCTRL_CmpConfigParameter
	.align	2
	.global	VCTRL_IsChanSegEnough
	.type	VCTRL_IsChanSegEnough, %function
VCTRL_IsChanSegEnough:
	.fnstart
.LFB1597:
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
	movw	r1, #:lower16:.LANCHOR0	@ tmp136,
	movt	r1, #:upper16:.LANCHOR0	@ tmp136,
	ldr	r3, [r1, r0, asl #2]	@ tmp137, s_pstVfmwChan
	ldr	r0, [r3, #332]	@ <variable>.s32NoStreamFlag, <variable>.s32NoStreamFlag
	subs	r0, r0, #1	@, <variable>.s32NoStreamFlag,
	movne	r0, #1	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_IsChanSegEnough, .-VCTRL_IsChanSegEnough
	.align	2
	.global	VCTRL_IsChanActive
	.type	VCTRL_IsChanActive, %function
VCTRL_IsChanActive:
	.fnstart
.LFB1598:
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
	cmp	r0, #15	@ ChanID,
	bls	.L32	@,
.L29:
	mvn	r0, #0	@ D.52521,
	ldmfd	sp, {fp, sp, pc}	@
.L32:
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	ldr	r3, [r3, r0, asl #2]	@ D.52520, s_pstVfmwChan
	cmp	r3, #0	@ D.52520,
	beq	.L29	@,
	ldr	r2, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r2, #0	@ <variable>.s32IsOpen,
	beq	.L29	@,
	ldr	r1, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r1, #0	@ <variable>.s32IsRun,
	beq	.L29	@,
	ldr	ip, [r3, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	ip, #0	@ <variable>.s32Priority,
	beq	.L29	@,
	ldr	r3, [r3, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #19	@ <variable>.eVidStd,
	movne	r0, #0	@ D.52521,
	ldmnefd	sp, {fp, sp, pc}	@
	b	.L29	@
	.fnend
	.size	VCTRL_IsChanActive, .-VCTRL_IsChanActive
	.align	2
	.global	VCTRL_GetChanMemSizeByResolution
	.type	VCTRL_GetChanMemSizeByResolution, %function
VCTRL_GetChanMemSizeByResolution:
	.fnstart
.LFB1606:
	@ args = 0, pretend = 0, frame = 944
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #968
	sub	sp, sp, #968	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	ip, #:lower16:g_vdm_hal_fun_ptr	@ tmp141,
	movt	ip, #:upper16:g_vdm_hal_fun_ptr	@ tmp141,
	mov	r5, r2	@ VdmMemSize, VdmMemSize
	mov	r4, r3	@ ScdMemSize, ScdMemSize
	ldr	ip, [ip, #48]	@ D.52904, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	cmp	ip, #0	@ D.52904,
	beq	.L34	@,
	mov	r2, r0	@, MaxWidth
	mov	r3, r1	@, MaxHeight
	mov	r0, #6	@ tmp142,
	mov	r1, #16	@ tmp143,
	str	r0, [sp, #0]	@ tmp142,
	mov	lr, #0	@ tmp144,
	str	r1, [sp, #4]	@ tmp143,
	mvn	r0, #0	@ tmp145,
	sub	r1, fp, #960	@ tmp147,,
	str	r0, [sp, #12]	@ tmp145,
	str	r1, [sp, #16]	@ tmp147,
	mov	r0, #1	@,
	str	lr, [sp, #8]	@ tmp144,
	mvn	r1, #-2147483648	@,
	blx	ip	@ D.52904
	cmp	r0, #0	@ ret
	bne	.L34	@,
	ldr	r2, [fp, #-956]	@ MemArrange.TotalMemUsed, MemArrange.TotalMemUsed
	mov	r3, #2129920	@ tmp149,
	str	r2, [r5, #0]	@ MemArrange.TotalMemUsed,* VdmMemSize
	str	r3, [r4, #0]	@ tmp149,* ScdMemSize
	str	r2, [r5, #4]	@ MemArrange.TotalMemUsed,
	str	r3, [r4, #4]	@ tmp149,
	str	r2, [r5, #8]	@ MemArrange.TotalMemUsed,
	str	r3, [r4, #8]	@ tmp149,
.L35:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L34:
	mvn	r0, #0	@ D.52917,
	b	.L35	@
	.fnend
	.size	VCTRL_GetChanMemSizeByResolution, .-VCTRL_GetChanMemSizeByResolution
	.align	2
	.global	VCTRL_GetChanIDByCtx
	.type	VCTRL_GetChanIDByCtx, %function
VCTRL_GetChanIDByCtx:
	.fnstart
.LFB1612:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp201,
	movt	r3, #:upper16:.LANCHOR0	@ tmp201,
	ldr	r2, [r3, #0]	@ temp.1142, s_pstVfmwChan
	cmp	r2, #0	@ temp.1142,
	beq	.L38	@,
	add	r1, r2, #250880	@ tmp153, temp.1142,
	add	r2, r1, #704	@ tmp153, tmp153,
	cmp	r2, r0	@ tmp153, pCtx
	moveq	r0, #0	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L38:
	ldr	r2, [r3, #4]	@ temp.1144, s_pstVfmwChan
	cmp	r2, #0	@ temp.1144,
	beq	.L40	@,
	add	r2, r2, #250880	@ tmp156, temp.1144,
	add	ip, r2, #704	@ tmp156, tmp156,
	cmp	ip, r0	@ tmp156, pCtx
	moveq	r0, #1	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L40:
	ldr	r2, [r3, #8]	@ temp.1146, s_pstVfmwChan
	cmp	r2, #0	@ temp.1146,
	beq	.L41	@,
	add	ip, r2, #250880	@ tmp159, temp.1146,
	add	r1, ip, #704	@ tmp159, tmp159,
	cmp	r1, r0	@ tmp159, pCtx
	moveq	r0, #2	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L41:
	ldr	r2, [r3, #12]	@ temp.1148, s_pstVfmwChan
	cmp	r2, #0	@ temp.1148,
	beq	.L42	@,
	add	r1, r2, #250880	@ tmp162, temp.1148,
	add	r2, r1, #704	@ tmp162, tmp162,
	cmp	r2, r0	@ tmp162, pCtx
	moveq	r0, #3	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L42:
	ldr	r2, [r3, #16]	@ temp.1150, s_pstVfmwChan
	cmp	r2, #0	@ temp.1150,
	beq	.L43	@,
	add	r2, r2, #250880	@ tmp165, temp.1150,
	add	ip, r2, #704	@ tmp165, tmp165,
	cmp	ip, r0	@ tmp165, pCtx
	moveq	r0, #4	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L43:
	ldr	r2, [r3, #20]	@ temp.1152, s_pstVfmwChan
	cmp	r2, #0	@ temp.1152,
	beq	.L44	@,
	add	ip, r2, #250880	@ tmp168, temp.1152,
	add	r1, ip, #704	@ tmp168, tmp168,
	cmp	r1, r0	@ tmp168, pCtx
	moveq	r0, #5	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L44:
	ldr	r2, [r3, #24]	@ temp.1154, s_pstVfmwChan
	cmp	r2, #0	@ temp.1154,
	beq	.L45	@,
	add	r1, r2, #250880	@ tmp171, temp.1154,
	add	r2, r1, #704	@ tmp171, tmp171,
	cmp	r2, r0	@ tmp171, pCtx
	moveq	r0, #6	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L45:
	ldr	r2, [r3, #28]	@ temp.1156, s_pstVfmwChan
	cmp	r2, #0	@ temp.1156,
	beq	.L46	@,
	add	r2, r2, #250880	@ tmp174, temp.1156,
	add	ip, r2, #704	@ tmp174, tmp174,
	cmp	ip, r0	@ tmp174, pCtx
	moveq	r0, #7	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L46:
	ldr	r2, [r3, #32]	@ temp.1158, s_pstVfmwChan
	cmp	r2, #0	@ temp.1158,
	beq	.L47	@,
	add	ip, r2, #250880	@ tmp177, temp.1158,
	add	r1, ip, #704	@ tmp177, tmp177,
	cmp	r1, r0	@ tmp177, pCtx
	moveq	r0, #8	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L47:
	ldr	r2, [r3, #36]	@ temp.1160, s_pstVfmwChan
	cmp	r2, #0	@ temp.1160,
	beq	.L48	@,
	add	r1, r2, #250880	@ tmp180, temp.1160,
	add	r2, r1, #704	@ tmp180, tmp180,
	cmp	r2, r0	@ tmp180, pCtx
	moveq	r0, #9	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L48:
	ldr	r2, [r3, #40]	@ temp.1162, s_pstVfmwChan
	cmp	r2, #0	@ temp.1162,
	beq	.L49	@,
	add	r2, r2, #250880	@ tmp183, temp.1162,
	add	ip, r2, #704	@ tmp183, tmp183,
	cmp	ip, r0	@ tmp183, pCtx
	moveq	r0, #10	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L49:
	ldr	r2, [r3, #44]	@ temp.1164, s_pstVfmwChan
	cmp	r2, #0	@ temp.1164,
	beq	.L50	@,
	add	ip, r2, #250880	@ tmp186, temp.1164,
	add	r1, ip, #704	@ tmp186, tmp186,
	cmp	r1, r0	@ tmp186, pCtx
	moveq	r0, #11	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L50:
	ldr	r2, [r3, #48]	@ temp.1166, s_pstVfmwChan
	cmp	r2, #0	@ temp.1166,
	beq	.L51	@,
	add	r1, r2, #250880	@ tmp189, temp.1166,
	add	r2, r1, #704	@ tmp189, tmp189,
	cmp	r2, r0	@ tmp189, pCtx
	moveq	r0, #12	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L51:
	ldr	r2, [r3, #52]	@ temp.1168, s_pstVfmwChan
	cmp	r2, #0	@ temp.1168,
	beq	.L52	@,
	add	r2, r2, #250880	@ tmp192, temp.1168,
	add	ip, r2, #704	@ tmp192, tmp192,
	cmp	ip, r0	@ tmp192, pCtx
	moveq	r0, #13	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L52:
	ldr	r2, [r3, #56]	@ temp.1170, s_pstVfmwChan
	cmp	r2, #0	@ temp.1170,
	beq	.L53	@,
	add	ip, r2, #250880	@ tmp195, temp.1170,
	add	r1, ip, #704	@ tmp195, tmp195,
	cmp	r1, r0	@ tmp195, pCtx
	moveq	r0, #14	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L53:
	ldr	r3, [r3, #60]	@ D.53459, s_pstVfmwChan
	cmp	r3, #0	@ D.53459,
	beq	.L54	@,
	add	r2, r3, #250880	@ tmp198, D.53459,
	add	r3, r2, #704	@ tmp198, tmp198,
	cmp	r3, r0	@ tmp198, pCtx
	moveq	r0, #15	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L54:
	mvn	r0, #0	@ i,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetChanIDByCtx, .-VCTRL_GetChanIDByCtx
	.align	2
	.global	VCTRL_GetChanIDByMemAddr
	.type	VCTRL_GetChanIDByMemAddr, %function
VCTRL_GetChanIDByMemAddr:
	.fnstart
.LFB1613:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp265,
	movt	r3, #:upper16:.LANCHOR0	@ tmp265,
	ldr	r2, [r3, #0]	@ temp.1196, s_pstVfmwChan
	cmp	r2, #0	@ temp.1196,
	beq	.L57	@,
	ldr	r1, [r2, #224]	@ temp.1198, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1198
	bge	.L58	@,
.L60:
	ldr	r1, [r2, #240]	@ temp.1197, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1197
	blt	.L57	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp185, temp.1197, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp185
	blt	.L106	@,
.L57:
	ldr	r2, [r3, #4]	@ temp.1203, s_pstVfmwChan
	cmp	r2, #0	@ temp.1203,
	beq	.L61	@,
	ldr	r1, [r2, #224]	@ temp.1204, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1204
	bge	.L62	@,
.L63:
	ldr	r1, [r2, #240]	@ temp.1205, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1205
	blt	.L61	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp190, temp.1205, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp190
	blt	.L108	@,
.L61:
	ldr	r2, [r3, #8]	@ temp.1210, s_pstVfmwChan
	cmp	r2, #0	@ temp.1210,
	beq	.L64	@,
	ldr	r1, [r2, #224]	@ temp.1211, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1211
	bge	.L65	@,
.L66:
	ldr	r1, [r2, #240]	@ temp.1212, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1212
	blt	.L64	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp195, temp.1212, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp195
	blt	.L121	@,
.L64:
	ldr	r2, [r3, #12]	@ temp.1217, s_pstVfmwChan
	cmp	r2, #0	@ temp.1217,
	beq	.L67	@,
	ldr	r1, [r2, #224]	@ temp.1218, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1218
	bge	.L68	@,
.L69:
	ldr	r1, [r2, #240]	@ temp.1219, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1219
	blt	.L67	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp200, temp.1219, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp200
	blt	.L120	@,
.L67:
	ldr	r2, [r3, #16]	@ temp.1224, s_pstVfmwChan
	cmp	r2, #0	@ temp.1224,
	beq	.L70	@,
	ldr	r1, [r2, #224]	@ temp.1225, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1225
	bge	.L71	@,
.L72:
	ldr	r1, [r2, #240]	@ temp.1226, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1226
	blt	.L70	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp205, temp.1226, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp205
	blt	.L119	@,
.L70:
	ldr	r2, [r3, #20]	@ temp.1231, s_pstVfmwChan
	cmp	r2, #0	@ temp.1231,
	beq	.L73	@,
	ldr	r1, [r2, #224]	@ temp.1232, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1232
	bge	.L74	@,
.L75:
	ldr	r1, [r2, #240]	@ temp.1233, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1233
	blt	.L73	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp210, temp.1233, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp210
	blt	.L118	@,
.L73:
	ldr	r2, [r3, #24]	@ temp.1238, s_pstVfmwChan
	cmp	r2, #0	@ temp.1238,
	beq	.L76	@,
	ldr	r1, [r2, #224]	@ temp.1239, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1239
	bge	.L77	@,
.L78:
	ldr	r1, [r2, #240]	@ temp.1240, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1240
	blt	.L76	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp215, temp.1240, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp215
	blt	.L117	@,
.L76:
	ldr	r2, [r3, #28]	@ temp.1245, s_pstVfmwChan
	cmp	r2, #0	@ temp.1245,
	beq	.L79	@,
	ldr	r1, [r2, #224]	@ temp.1246, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1246
	bge	.L80	@,
.L81:
	ldr	r1, [r2, #240]	@ temp.1247, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1247
	blt	.L79	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp220, temp.1247, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp220
	blt	.L116	@,
.L79:
	ldr	r2, [r3, #32]	@ temp.1252, s_pstVfmwChan
	cmp	r2, #0	@ temp.1252,
	beq	.L82	@,
	ldr	r1, [r2, #224]	@ temp.1253, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1253
	bge	.L83	@,
.L84:
	ldr	r1, [r2, #240]	@ temp.1254, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1254
	blt	.L82	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp225, temp.1254, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp225
	blt	.L115	@,
.L82:
	ldr	r2, [r3, #36]	@ temp.1259, s_pstVfmwChan
	cmp	r2, #0	@ temp.1259,
	beq	.L85	@,
	ldr	r1, [r2, #224]	@ temp.1260, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1260
	bge	.L86	@,
.L87:
	ldr	r1, [r2, #240]	@ temp.1261, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1261
	blt	.L85	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp230, temp.1261, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp230
	blt	.L114	@,
.L85:
	ldr	r2, [r3, #40]	@ temp.1266, s_pstVfmwChan
	cmp	r2, #0	@ temp.1266,
	beq	.L88	@,
	ldr	r1, [r2, #224]	@ temp.1267, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1267
	bge	.L89	@,
.L90:
	ldr	r1, [r2, #240]	@ temp.1268, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1268
	blt	.L88	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp235, temp.1268, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp235
	blt	.L113	@,
.L88:
	ldr	r2, [r3, #44]	@ temp.1273, s_pstVfmwChan
	cmp	r2, #0	@ temp.1273,
	beq	.L91	@,
	ldr	r1, [r2, #224]	@ temp.1274, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1274
	bge	.L92	@,
.L93:
	ldr	r1, [r2, #240]	@ temp.1275, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1275
	blt	.L91	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp240, temp.1275, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp240
	blt	.L112	@,
.L91:
	ldr	r2, [r3, #48]	@ temp.1280, s_pstVfmwChan
	cmp	r2, #0	@ temp.1280,
	beq	.L94	@,
	ldr	r1, [r2, #224]	@ temp.1281, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1281
	bge	.L95	@,
.L96:
	ldr	r1, [r2, #240]	@ temp.1282, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1282
	blt	.L94	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp245, temp.1282, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp245
	blt	.L111	@,
.L94:
	ldr	r2, [r3, #52]	@ temp.1287, s_pstVfmwChan
	cmp	r2, #0	@ temp.1287,
	beq	.L97	@,
	ldr	r1, [r2, #224]	@ temp.1288, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1288
	bge	.L98	@,
.L99:
	ldr	r1, [r2, #240]	@ temp.1289, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1289
	blt	.L97	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp250, temp.1289, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp250
	blt	.L110	@,
.L97:
	ldr	r2, [r3, #56]	@ temp.1294, s_pstVfmwChan
	cmp	r2, #0	@ temp.1294,
	beq	.L100	@,
	ldr	r1, [r2, #224]	@ temp.1295, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1295
	bge	.L101	@,
.L102:
	ldr	r1, [r2, #240]	@ temp.1296, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1296
	blt	.L100	@,
	ldr	r2, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp255, temp.1296, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp255
	blt	.L109	@,
.L100:
	ldr	r3, [r3, #60]	@ D.53475, s_pstVfmwChan
	cmp	r3, #0	@ D.53475,
	beq	.L103	@,
	ldr	r2, [r3, #224]	@ D.53478, <variable>.stChanMem_vdh.PhyAddr
	cmp	r2, r0	@ D.53478, PhyAddr
	bgt	.L104	@,
	ldr	r1, [r3, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r2, r2, r1	@ tmp260, D.53478, <variable>.stChanMem_vdh.Length
	cmp	r0, r2	@ PhyAddr, tmp260
	blt	.L107	@,
.L104:
	ldr	r2, [r3, #240]	@ D.53486, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r2	@ PhyAddr, D.53486
	blt	.L103	@,
	ldr	r3, [r3, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	ip, r2, r3	@ tmp262, D.53486, <variable>.stChanMem_scd.Length
	cmp	r0, ip	@ PhyAddr, tmp262
	blt	.L107	@,
.L103:
	mvn	r0, #0	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L58:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp187, temp.1198, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp187
	bge	.L60	@,
.L106:
	mov	r0, #0	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L62:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp192, temp.1204, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp192
	bge	.L63	@,
.L108:
	mov	r0, #1	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L65:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp197, temp.1211, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp197
	bge	.L66	@,
.L121:
	mov	r0, #2	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L68:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp202, temp.1218, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp202
	bge	.L69	@,
.L120:
	mov	r0, #3	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L71:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp207, temp.1225, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp207
	bge	.L72	@,
.L119:
	mov	r0, #4	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L74:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp212, temp.1232, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp212
	bge	.L75	@,
.L118:
	mov	r0, #5	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L77:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp217, temp.1239, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp217
	bge	.L78	@,
.L117:
	mov	r0, #6	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L80:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp222, temp.1246, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp222
	bge	.L81	@,
.L116:
	mov	r0, #7	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L83:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp227, temp.1253, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp227
	bge	.L84	@,
.L115:
	mov	r0, #8	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L86:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp232, temp.1260, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp232
	bge	.L87	@,
.L114:
	mov	r0, #9	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L89:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp237, temp.1267, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp237
	bge	.L90	@,
.L113:
	mov	r0, #10	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L92:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp242, temp.1274, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp242
	bge	.L93	@,
.L112:
	mov	r0, #11	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L95:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp247, temp.1281, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp247
	bge	.L96	@,
.L111:
	mov	r0, #12	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L98:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp252, temp.1288, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp252
	bge	.L99	@,
.L110:
	mov	r0, #13	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L101:
	ldr	ip, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp257, temp.1295, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp257
	bge	.L102	@,
.L109:
	mov	r0, #14	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L107:
	mov	r0, #15	@ i,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetChanIDByMemAddr, .-VCTRL_GetChanIDByMemAddr
	.align	2
	.global	VCTRL_GetChanVoQue
	.type	VCTRL_GetChanVoQue, %function
VCTRL_GetChanVoQue:
	.fnstart
.LFB1615:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	ldr	r3, [r3, r0, asl #2]	@ D.53702, s_pstVfmwChan
	cmp	r3, #0	@ D.53702,
	beq	.L123	@,
	ldr	r2, [r3, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, #18	@ <variable>.eVidStd,
	ldrls	pc, [pc, r2, asl #2]	@ <variable>.eVidStd
	b	.L123	@
.L138:
	.word	.L137
	.word	.L125
	.word	.L126
	.word	.L127
	.word	.L128
	.word	.L129
	.word	.L130
	.word	.L123
	.word	.L131
	.word	.L132
	.word	.L133
	.word	.L133
	.word	.L133
	.word	.L134
	.word	.L128
	.word	.L135
	.word	.L136
	.word	.L123
	.word	.L137
.L137:
	add	r0, r3, #250880	@ pstVoQue, D.53702,
	add	r0, r0, #712	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L123:
	mov	r0, #0	@ pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L126:
	add	ip, r3, #270336	@ pstVoQue, D.53702,
	add	r0, ip, #3856	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L127:
	add	r1, r3, #331776	@ pstVoQue, D.53702,
	add	r0, r1, #320	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L128:
	movw	r1, #:lower16:277448	@ pstVoQue,
	movt	r1, #:upper16:277448	@ pstVoQue,
	add	r0, r3, r1	@ pstVoQue, D.53702, pstVoQue
	ldmfd	sp, {fp, sp, pc}	@
.L129:
	add	ip, r3, #282624	@ pstVoQue, D.53702,
	add	r0, ip, #2768	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L125:
	add	r2, r3, #364544	@ pstVoQue, D.53702,
	add	r0, r2, #1056	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L136:
	add	r0, r3, #2375680	@ pstVoQue, D.53702,
	add	r0, r0, #8640	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L134:
	add	ip, r3, #259072	@ pstVoQue, D.53702,
	add	r0, ip, #680	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L135:
	add	r2, r3, #251904	@ pstVoQue, D.53702,
	add	r0, r2, #264	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L130:
	movw	r2, #:lower16:267672	@ pstVoQue,
	movt	r2, #:upper16:267672	@ pstVoQue,
	add	r0, r3, r2	@ pstVoQue, D.53702, pstVoQue
	ldmfd	sp, {fp, sp, pc}	@
.L131:
	movw	r0, #:lower16:297720	@ pstVoQue,
	movt	r0, #:upper16:297720	@ pstVoQue,
	add	r0, r3, r0	@ pstVoQue, D.53702, pstVoQue
	ldmfd	sp, {fp, sp, pc}	@
.L132:
	movw	r1, #:lower16:297704	@ pstVoQue,
	movt	r1, #:upper16:297704	@ pstVoQue,
	add	r0, r3, r1	@ pstVoQue, D.53702, pstVoQue
	ldmfd	sp, {fp, sp, pc}	@
.L133:
	movw	r0, #:lower16:264232	@ pstVoQue,
	movt	r0, #:upper16:264232	@ pstVoQue,
	add	r0, r3, r0	@ pstVoQue, D.53702, pstVoQue
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetChanVoQue, .-VCTRL_GetChanVoQue
	.align	2
	.global	str2val
	.type	str2val, %function
str2val:
	.fnstart
.LFB1649:
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
	ldrb	r3, [r0, #0]	@ zero_extendqisi2	@ tmp173,* str
	cmp	r3, #48	@ tmp173,
	beq	.L184	@,
.L142:
	mov	r4, #10	@ weight,
	mov	r5, #0	@ i,
.L143:
	add	r0, r0, r5	@ ivtmp.1351, str, i
	mov	ip, #0	@ dat,
	ldrb	r3, [r0, #0]	@ zero_extendqisi2	@ D.55048,* ivtmp.1351
	cmp	r3, #31	@ D.55048,
	bls	.L144	@,
	cmp	r4, #16	@ weight,
	beq	.L173	@,
.L154:
	sub	ip, r3, #48	@ tmp194, D.55048,
	uxtb	r3, ip	@ tmp195, tmp194
	cmp	r3, #9	@ tmp195,
	bhi	.L174	@,
.L175:
	mov	r2, #1	@ tmp185,
	cmp	r2, #0	@ tmp185,
	add	r0, r0, r2	@ ivtmp.1351, ivtmp.1351,
	add	r5, r5, r2	@ i, i,
	beq	.L151	@,
	ldrb	r3, [r0, #0]	@ zero_extendqisi2	@ D.55048,* ivtmp.1351
	cmp	r3, #31	@ D.55048,
	bls	.L144	@,
	cmp	r4, #16	@ weight,
	beq	.L177	@,
.L159:
	sub	r3, r3, #48	@ tmp199, D.55048,
	uxtb	r2, r3	@ tmp200, tmp199
	cmp	r2, #9	@ tmp200,
	bhi	.L174	@,
.L178:
	add	r5, r5, #1	@ i, i,
	add	r0, r0, #1	@ ivtmp.1351, ivtmp.1351,
	cmp	r5, #9	@ i,
	mla	ip, r4, ip, r3	@ dat, weight, dat, d
	bls	.L151	@,
.L144:
	mov	r0, #0	@ D.55068,
	str	ip, [r1, #0]	@ dat,* data
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L146:
	cmp	r3, #64	@ D.55048,
	bhi	.L147	@,
.L145:
	sub	r3, r3, #48	@ tmp181, D.55048,
	uxtb	r2, r3	@ tmp182, tmp181
	cmp	r2, #9	@ tmp182,
	bhi	.L174	@,
.L148:
	ldrb	r2, [r0, #1]	@ zero_extendqisi2	@ D.55048,
	add	r5, r5, #1	@ tmp186, i,
	mla	ip, r4, ip, r3	@ dat, weight, dat, d
	cmp	r2, #31	@ D.55048,
	add	r0, r0, #1	@ tmp187, ivtmp.1351,
	bls	.L144	@,
	cmp	r4, #16	@ weight,
	beq	.L180	@,
.L165:
	sub	r2, r2, #48	@ tmp203, D.55048,
	uxtb	r3, r2	@ tmp204, tmp203
	cmp	r3, #9	@ tmp204,
	bhi	.L174	@,
.L181:
	add	r5, r5, #1	@ i, tmp186,
	add	r0, r0, #1	@ ivtmp.1351, tmp187,
	cmp	r5, #9	@ i,
	mla	ip, r4, ip, r2	@ dat, weight, dat, d
	bhi	.L144	@,
.L151:
	ldrb	r3, [r0, #0]	@ zero_extendqisi2	@ D.55048,* ivtmp.1351
	cmp	r3, #31	@ D.55048,
	bls	.L144	@,
	cmp	r4, #16	@ weight,
	bne	.L145	@,
	cmp	r3, #96	@ D.55048,
	bls	.L146	@,
	cmp	r3, #102	@ D.55048,
	subls	r3, r3, #87	@ d, D.55048,
	bls	.L148	@,
.L147:
	cmp	r3, #70	@ D.55048,
	subls	r3, r3, #55	@ d, D.55048,
	bls	.L148	@,
	b	.L145	@
.L180:
	cmp	r2, #96	@ D.55048,
	bls	.L167	@,
	cmp	r2, #102	@ D.55048,
	bhi	.L168	@,
	sub	r2, r2, #87	@ d, D.55048,
	b	.L181	@
.L167:
	cmp	r2, #64	@ D.55048,
	bls	.L165	@,
.L168:
	cmp	r2, #70	@ D.55048,
	subls	r2, r2, #55	@ d, D.55048,
	bls	.L181	@,
	b	.L165	@
.L184:
	ldrb	r2, [r0, #1]	@ zero_extendqisi2	@ D.55042,
	cmp	r2, #120	@ D.55042,
	cmpne	r2, #88	@, D.55042,
	moveq	r4, #16	@ weight,
	moveq	r5, #2	@ i,
	beq	.L143	@,
	b	.L142	@
.L173:
	cmp	r3, #96	@ D.55048,
	bls	.L156	@,
	cmp	r3, #102	@ D.55048,
	bhi	.L157	@,
	sub	ip, r3, #87	@ d, D.55048,
	b	.L175	@
.L156:
	cmp	r3, #64	@ D.55048,
	bls	.L154	@,
.L157:
	cmp	r3, #70	@ D.55048,
	subls	ip, r3, #55	@ d, D.55048,
	bls	.L175	@,
	b	.L154	@
.L177:
	cmp	r3, #96	@ D.55048,
	bls	.L161	@,
	cmp	r3, #102	@ D.55048,
	bhi	.L162	@,
	sub	r3, r3, #87	@ d, D.55048,
	b	.L178	@
.L161:
	cmp	r3, #64	@ D.55048,
	bls	.L159	@,
.L162:
	cmp	r3, #70	@ D.55048,
	subls	r3, r3, #55	@ d, D.55048,
	bhi	.L159	@,
	add	r5, r5, #1	@ i, i,
	add	r0, r0, #1	@ ivtmp.1351, ivtmp.1351,
	cmp	r5, #9	@ i,
	mla	ip, r4, ip, r3	@ dat, weight, dat, d
	bls	.L151	@,
	b	.L144	@
.L174:
	mvn	r0, #0	@ D.55068,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	str2val, .-str2val
	.align	2
	.type	vfmw_proc_write, %function
vfmw_proc_write:
	.fnstart
.LFB1652:
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
	ldr	ip, [r0, #128]	@ <variable>.private_data, <variable>.private_data
	ldr	ip, [ip, #72]	@ <variable>.private, <variable>.private
	ldr	ip, [ip, #20]	@ D.55245, <variable>.write
	cmp	ip, #0	@ D.55245,
	mvneq	r0, #37	@ D.55248,
	ldmeqfd	sp, {fp, sp, pc}	@
	blx	ip	@ D.55245
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	vfmw_proc_write, .-vfmw_proc_write
	.align	2
	.global	VCTRL_SetChanFsPartitionState
	.type	VCTRL_SetChanFsPartitionState, %function
VCTRL_SetChanFsPartitionState:
	.fnstart
.LFB1660:
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
	movw	ip, #:lower16:.LANCHOR0	@ tmp135,
	movt	ip, #:upper16:.LANCHOR0	@ tmp135,
	movw	r3, #:lower16:249248	@ tmp138,
	movt	r3, #:upper16:249248	@ tmp138,
	ldr	r2, [ip, r0, asl #2]	@ tmp136, s_pstVfmwChan
	str	r1, [r2, r3]	@ state, <variable>.FspInst.eFspPartitionState
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_SetChanFsPartitionState, .-VCTRL_SetChanFsPartitionState
	.align	2
	.global	VCTRL_GetCurChanFsSize
	.type	VCTRL_GetCurChanFsSize, %function
VCTRL_GetCurChanFsSize:
	.fnstart
.LFB1661:
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
	movw	r1, #:lower16:.LANCHOR0	@ tmp136,
	movt	r1, #:upper16:.LANCHOR0	@ tmp136,
	movw	r3, #:lower16:249256	@ tmp140,
	movt	r3, #:upper16:249256	@ tmp140,
	ldr	r2, [r1, r0, asl #2]	@ tmp137, s_pstVfmwChan
	ldr	r0, [r2, r3]	@, <variable>.s32CurFsSize
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetCurChanFsSize, .-VCTRL_GetCurChanFsSize
	.align	2
	.global	VCTRL_SetFsParamToChan
	.type	VCTRL_SetFsParamToChan, %function
VCTRL_SetFsParamToChan:
	.fnstart
.LFB1666:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp135,
	movt	r3, #:upper16:.LANCHOR0	@ tmp135,
	ldr	r5, [r1, #8]	@ <variable>.Length, <variable>.Length
	movw	ip, #:lower16:249264	@ tmp158,
	movt	ip, #:upper16:249264	@ tmp158,
	ldr	r4, [r3, r0, asl #2]	@ tmp136, s_pstVfmwChan
	movw	r2, #:lower16:249276	@ tmp159,
	movt	r2, #:upper16:249276	@ tmp159,
	str	r5, [r4, #280]	@ <variable>.Length, <variable>.s32VdmChanMemSize
	ldr	r4, [r3, r0, asl #2]	@ tmp139, s_pstVfmwChan
	ldr	r5, [r1, #0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	r5, [r4, #276]	@ <variable>.PhyAddr, <variable>.s32VdmChanMemAddr
	ldr	r4, [r3, r0, asl #2]	@ tmp142, s_pstVfmwChan
	ldr	r5, [r1, #0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	r5, [r4, #224]	@ <variable>.PhyAddr, <variable>.stChanMem_vdh.PhyAddr
	ldr	r4, [r3, r0, asl #2]	@ tmp145, s_pstVfmwChan
	ldr	r5, [r1, #4]	@ <variable>.VirAddr, <variable>.VirAddr
	str	r5, [r4, #220]	@ <variable>.VirAddr, <variable>.stChanMem_vdh.VirAddr
	ldr	r4, [r3, r0, asl #2]	@ tmp148, s_pstVfmwChan
	ldr	r5, [r1, #8]	@ <variable>.Length, <variable>.Length
	str	r5, [r4, #228]	@ <variable>.Length, <variable>.stChanMem_vdh.Length
	ldr	r4, [r3, r0, asl #2]	@ tmp151, s_pstVfmwChan
	ldr	r5, [r1, #12]	@ <variable>.FrameNum, <variable>.FrameNum
	str	r5, [r4, ip]	@ <variable>.FrameNum, <variable>.s32NeededFrameNum
	ldr	r3, [r3, r0, asl #2]	@ tmp155, s_pstVfmwChan
	ldr	r1, [r1, #16]	@ <variable>.NeedMMZ, <variable>.NeedMMZ
	str	r1, [r3, r2]	@ <variable>.NeedMMZ, <variable>.s32NeedMMZ
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	VCTRL_SetFsParamToChan, .-VCTRL_SetFsParamToChan
	.align	2
	.global	VCTRL_GetImageHeight
	.type	VCTRL_GetImageHeight, %function
VCTRL_GetImageHeight:
	.fnstart
.LFB1669:
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
	movw	r2, #:lower16:.LANCHOR0	@ tmp139,
	movt	r2, #:upper16:.LANCHOR0	@ tmp139,
	movw	r3, #:lower16:251576	@ tmp140,
	movt	r3, #:upper16:251576	@ tmp140,
	ldr	r0, [r2, r0, asl #2]	@ D.56027, s_pstVfmwChan
	ldr	r3, [r0, r3]	@ <variable>.stSynCtx.eVidStd, <variable>.stSynCtx.eVidStd
	cmp	r3, #2	@ <variable>.stSynCtx.eVidStd,
	beq	.L198	@,
	cmp	r3, #16	@ <variable>.stSynCtx.eVidStd,
	beq	.L199	@,
	cmp	r3, #0	@ <variable>.stSynCtx.eVidStd,
	movne	r0, #0	@ uImageHeight,
	ldmnefd	sp, {fp, sp, pc}	@
	add	r1, r0, #250880	@, D.56027,
	add	r0, r1, #704	@,,
	bl	H264DEC_GetImageHeight	@
	ldmfd	sp, {fp, sp, pc}	@
.L199:
	add	ip, r0, #250880	@, D.56027,
	add	r0, ip, #704	@,,
	bl	HEVCDEC_GetImageHeight	@
	ldmfd	sp, {fp, sp, pc}	@
.L198:
	add	r0, r0, #250880	@, D.56027,
	add	r0, r0, #704	@,,
	bl	MPEG4DEC_GetImageHeight	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetImageHeight, .-VCTRL_GetImageHeight
	.align	2
	.global	VCTRL_GetImageWidth
	.type	VCTRL_GetImageWidth, %function
VCTRL_GetImageWidth:
	.fnstart
.LFB1668:
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
	movw	r2, #:lower16:.LANCHOR0	@ tmp139,
	movt	r2, #:upper16:.LANCHOR0	@ tmp139,
	movw	r3, #:lower16:251576	@ tmp140,
	movt	r3, #:upper16:251576	@ tmp140,
	ldr	r0, [r2, r0, asl #2]	@ D.56008, s_pstVfmwChan
	ldr	r3, [r0, r3]	@ <variable>.stSynCtx.eVidStd, <variable>.stSynCtx.eVidStd
	cmp	r3, #2	@ <variable>.stSynCtx.eVidStd,
	beq	.L205	@,
	cmp	r3, #16	@ <variable>.stSynCtx.eVidStd,
	beq	.L206	@,
	cmp	r3, #0	@ <variable>.stSynCtx.eVidStd,
	movne	r0, #0	@ uImageWidth,
	ldmnefd	sp, {fp, sp, pc}	@
	add	r1, r0, #250880	@, D.56008,
	add	r0, r1, #704	@,,
	bl	H264DEC_GetImageWidth	@
	ldmfd	sp, {fp, sp, pc}	@
.L206:
	add	ip, r0, #250880	@, D.56008,
	add	r0, ip, #704	@,,
	bl	HEVCDEC_GetImageWidth	@
	ldmfd	sp, {fp, sp, pc}	@
.L205:
	add	r0, r0, #250880	@, D.56008,
	add	r0, r0, #704	@,,
	bl	MPEG4DEC_GetImageWidth	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetImageWidth, .-VCTRL_GetImageWidth
	.align	2
	.global	VCTRL_CloseHardware
	.type	VCTRL_CloseHardware, %function
VCTRL_CloseHardware:
	.fnstart
.LFB1659:
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
	mov	r2, #0	@ ivtmp.1534,
	movw	r6, #:lower16:.LANCHOR0	@ tmp239,
	movt	r6, #:upper16:.LANCHOR0	@ tmp239,
	mov	r5, r2	@ dsp_need_flag, ivtmp.1534
	mov	r4, r2	@ bpd_need_flag, ivtmp.1534
	mov	r0, r2	@ vdm_need_flag, ivtmp.1534
.L217:
	ldr	r3, [r6, r2]	@ D.55509, s_pstVfmwChan
	cmp	r3, #0	@ D.55509,
	beq	.L210	@,
	cmp	r0, #0	@ vdm_need_flag,
	ldr	r1, [r3, #544]	@ eVidStd, <variable>.eVidStd
	bne	.L211	@,
	ldr	ip, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #1	@ <variable>.s32IsOpen,
	beq	.L225	@,
.L211:
	eor	ip, r4, #1	@ tmp216, bpd_need_flag,
	cmp	r1, #1	@ eVidStd,
	movne	ip, #0	@, tmp221
	andeq	ip, ip, #1	@,, tmp221, tmp216
	cmp	ip, #0	@ tmp221,
	beq	.L213	@,
	ldr	ip, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #1	@ <variable>.s32IsOpen,
	movne	r4, #0	@ bpd_need_flag,
	beq	.L226	@,
.L215:
	mov	ip, #0	@ ScdLowdlyEnable,
.L216:
	cmp	r5, #0	@ dsp_need_flag,
	bne	.L210	@,
	cmp	r1, #6	@ eVidStd,
	cmpne	ip, #1	@, ScdLowdlyEnable,
	bne	.L210	@,
	ldr	r1, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r1, #1	@ <variable>.s32IsOpen,
	beq	.L227	@,
.L210:
	add	r2, r2, #4	@ ivtmp.1534, ivtmp.1534,
	cmp	r2, #64	@ ivtmp.1534,
	bne	.L217	@,
	cmp	r0, #0	@ vdm_need_flag,
	bne	.L218	@,
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp234,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp234,
	ldr	r3, [r3, #4]	@ D.55570, g_vdm_hal_fun_ptr.pfun_VDMDRV_CloseHardware
	cmp	r3, #0	@ D.55570,
	beq	.L228	@,
	blx	r3	@ D.55570
.L218:
	cmp	r5, #0	@ dsp_need_flag,
	bne	.L220	@,
	movw	r0, #:lower16:g_vdm_hal_fun_ptr	@ tmp236,
	movt	r0, #:upper16:g_vdm_hal_fun_ptr	@ tmp236,
	ldr	r3, [r0, #12]	@ D.55579, g_vdm_hal_fun_ptr.pfun_DSPDRV_CloseHardware
	cmp	r3, #0	@ D.55579,
	beq	.L229	@,
	mov	r0, r5	@, dsp_need_flag
	blx	r3	@ D.55579
.L220:
	cmp	r4, #0	@ bpd_need_flag,
	ldmnefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	movw	r2, #:lower16:g_vdm_hal_fun_ptr	@ tmp238,
	movt	r2, #:upper16:g_vdm_hal_fun_ptr	@ tmp238,
	ldr	r3, [r2, #28]	@ D.55586, g_vdm_hal_fun_ptr.pfun_BPDDRV_CloseHardware
	cmp	r3, #0	@ D.55586,
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	blx	r3	@ D.55586
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L226:
	ldr	r4, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r4, #1	@ <variable>.s32IsRun,
	movne	r4, #0	@, bpd_need_flag
	moveq	r4, #1	@, bpd_need_flag
	b	.L215	@
.L213:
	cmp	r1, #0	@ eVidStd,
	ldreq	ip, [r3, #1260]	@ ScdLowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	beq	.L216	@,
	b	.L215	@
.L225:
	ldr	ip, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	ip, #1	@ <variable>.s32IsRun,
	bne	.L211	@,
	cmp	r1, #5	@ eVidStd,
	cmpne	r1, #3	@, eVidStd,
	bhi	.L230	@,
.L212:
	mov	r0, #1	@ vdm_need_flag,
	b	.L211	@
.L227:
	ldr	r5, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r5, #1	@ <variable>.s32IsRun,
	movne	r5, #0	@, dsp_need_flag,
	b	.L210	@
.L230:
	cmp	r1, #6	@ eVidStd,
	cmpne	r1, #8	@, eVidStd,
	beq	.L212	@,
	cmp	r1, #9	@ eVidStd,
	cmpne	r1, #10	@, eVidStd,
	beq	.L212	@,
	cmp	r1, #11	@ eVidStd,
	cmpne	r1, #12	@, eVidStd,
	beq	.L212	@,
	cmp	r1, #13	@ eVidStd,
	cmpne	r1, #15	@, eVidStd,
	beq	.L212	@,
	cmp	r1, #16	@ eVidStd,
	movne	r0, #0	@, vdm_need_flag
	moveq	r0, #1	@, vdm_need_flag
	b	.L211	@
.L228:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #10243	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L218	@
.L229:
	mov	r0, r5	@, dsp_need_flag
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #10254	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L220	@
	.fnend
	.size	VCTRL_CloseHardware, .-VCTRL_CloseHardware
	.align	2
	.global	VCTRL_OpenHardware
	.type	VCTRL_OpenHardware, %function
VCTRL_OpenHardware:
	.fnstart
.LFB1658:
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
	cmp	r0, #15	@ ChanID,
	mov	r5, r0	@ ChanID, ChanID
	bhi	.L330	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp585,
	movt	r4, #:upper16:.LANCHOR0	@ tmp585,
	ldr	r0, [r4, r0, asl #2]	@ D.55419, s_pstVfmwChan
	cmp	r0, #0	@ D.55419,
	beq	.L331	@,
	ldr	r3, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r3, #1	@ <variable>.s32IsOpen,
	bne	.L235	@,
	ldr	r3, [r0, #544]	@ D.55427, <variable>.eVidStd
	cmp	r3, #19	@ D.55427,
	beq	.L235	@,
	cmp	r3, #7	@ D.55427,
	cmpne	r3, #4	@, D.55427,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r3, #14	@ D.55427,
	cmpne	r3, #18	@, D.55427,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	ldr	r3, [r4, #0]	@ D.56191, s_pstVfmwChan
	cmp	r3, #0	@ D.56191,
	beq	.L237	@,
	ldr	r2, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r2, #0	@ <variable>.s32IsOpen,
	beq	.L237	@,
	ldr	r0, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L237	@,
	ldr	r1, [r3, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L237	@,
	ldr	r3, [r3, #544]	@ temp.1580, <variable>.eVidStd
	cmp	r3, #19	@ temp.1580,
	beq	.L237	@,
	cmp	r3, #4	@ temp.1580,
	cmpne	r3, #7	@, temp.1580,
	beq	.L237	@,
	cmp	r3, #14	@ temp.1580,
	beq	.L237	@,
	subs	r3, r3, #18	@ activeChanNum, temp.1580,
	movne	r3, #1	@ activeChanNum
	b	.L238	@
.L235:
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #10080	@,
	movt	r1, #:upper16:.LC3	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L330:
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #10068	@,
	movt	r1, #:upper16:.LC1	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L237:
	mov	r3, #0	@ activeChanNum,
.L238:
	ldr	r2, [r4, #4]	@ temp.1571, s_pstVfmwChan
	cmp	r2, #0	@ temp.1571,
	beq	.L239	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L239	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L239	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L239	@,
	ldr	r2, [r2, #544]	@ D.56186, <variable>.eVidStd
	cmp	r2, #19	@ D.56186,
	beq	.L239	@,
	cmp	r2, #4	@ D.56186,
	cmpne	r2, #7	@, D.56186,
	beq	.L239	@,
	cmp	r2, #14	@ D.56186,
	beq	.L239	@,
	cmp	r2, #18	@ D.56186,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L239:
	ldr	r2, [r4, #8]	@ temp.1593, s_pstVfmwChan
	cmp	r2, #0	@ temp.1593,
	beq	.L240	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L240	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L240	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L240	@,
	ldr	r2, [r2, #544]	@ temp.1597, <variable>.eVidStd
	cmp	r2, #19	@ temp.1597,
	beq	.L240	@,
	cmp	r2, #4	@ temp.1597,
	cmpne	r2, #7	@, temp.1597,
	beq	.L240	@,
	cmp	r2, #14	@ temp.1597,
	beq	.L240	@,
	cmp	r2, #18	@ temp.1597,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L240:
	ldr	r2, [r4, #12]	@ temp.1601, s_pstVfmwChan
	cmp	r2, #0	@ temp.1601,
	beq	.L241	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L241	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L241	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L241	@,
	ldr	r2, [r2, #544]	@ temp.1605, <variable>.eVidStd
	cmp	r2, #19	@ temp.1605,
	beq	.L241	@,
	cmp	r2, #4	@ temp.1605,
	cmpne	r2, #7	@, temp.1605,
	beq	.L241	@,
	cmp	r2, #14	@ temp.1605,
	beq	.L241	@,
	cmp	r2, #18	@ temp.1605,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L241:
	ldr	r2, [r4, #16]	@ temp.1609, s_pstVfmwChan
	cmp	r2, #0	@ temp.1609,
	beq	.L242	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L242	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L242	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L242	@,
	ldr	r2, [r2, #544]	@ temp.1613, <variable>.eVidStd
	cmp	r2, #19	@ temp.1613,
	beq	.L242	@,
	cmp	r2, #4	@ temp.1613,
	cmpne	r2, #7	@, temp.1613,
	beq	.L242	@,
	cmp	r2, #14	@ temp.1613,
	beq	.L242	@,
	cmp	r2, #18	@ temp.1613,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L242:
	ldr	r2, [r4, #20]	@ temp.1617, s_pstVfmwChan
	cmp	r2, #0	@ temp.1617,
	beq	.L243	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L243	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L243	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L243	@,
	ldr	r2, [r2, #544]	@ temp.1621, <variable>.eVidStd
	cmp	r2, #19	@ temp.1621,
	beq	.L243	@,
	cmp	r2, #4	@ temp.1621,
	cmpne	r2, #7	@, temp.1621,
	beq	.L243	@,
	cmp	r2, #14	@ temp.1621,
	beq	.L243	@,
	cmp	r2, #18	@ temp.1621,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L243:
	ldr	r2, [r4, #24]	@ temp.1625, s_pstVfmwChan
	cmp	r2, #0	@ temp.1625,
	beq	.L244	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L244	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L244	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L244	@,
	ldr	r2, [r2, #544]	@ temp.1629, <variable>.eVidStd
	cmp	r2, #19	@ temp.1629,
	beq	.L244	@,
	cmp	r2, #4	@ temp.1629,
	cmpne	r2, #7	@, temp.1629,
	beq	.L244	@,
	cmp	r2, #14	@ temp.1629,
	beq	.L244	@,
	cmp	r2, #18	@ temp.1629,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L244:
	ldr	r2, [r4, #28]	@ temp.1633, s_pstVfmwChan
	cmp	r2, #0	@ temp.1633,
	beq	.L245	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L245	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L245	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L245	@,
	ldr	r2, [r2, #544]	@ temp.1637, <variable>.eVidStd
	cmp	r2, #19	@ temp.1637,
	beq	.L245	@,
	cmp	r2, #4	@ temp.1637,
	cmpne	r2, #7	@, temp.1637,
	beq	.L245	@,
	cmp	r2, #14	@ temp.1637,
	beq	.L245	@,
	cmp	r2, #18	@ temp.1637,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L245:
	ldr	r2, [r4, #32]	@ temp.1641, s_pstVfmwChan
	cmp	r2, #0	@ temp.1641,
	beq	.L246	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L246	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L246	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L246	@,
	ldr	r2, [r2, #544]	@ temp.1645, <variable>.eVidStd
	cmp	r2, #19	@ temp.1645,
	beq	.L246	@,
	cmp	r2, #4	@ temp.1645,
	cmpne	r2, #7	@, temp.1645,
	beq	.L246	@,
	cmp	r2, #14	@ temp.1645,
	beq	.L246	@,
	cmp	r2, #18	@ temp.1645,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L246:
	ldr	r2, [r4, #36]	@ temp.1649, s_pstVfmwChan
	cmp	r2, #0	@ temp.1649,
	beq	.L247	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L247	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L247	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L247	@,
	ldr	r2, [r2, #544]	@ temp.1653, <variable>.eVidStd
	cmp	r2, #19	@ temp.1653,
	beq	.L247	@,
	cmp	r2, #4	@ temp.1653,
	cmpne	r2, #7	@, temp.1653,
	beq	.L247	@,
	cmp	r2, #14	@ temp.1653,
	beq	.L247	@,
	cmp	r2, #18	@ temp.1653,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L247:
	ldr	r2, [r4, #40]	@ temp.1657, s_pstVfmwChan
	cmp	r2, #0	@ temp.1657,
	beq	.L248	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L248	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L248	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L248	@,
	ldr	r2, [r2, #544]	@ temp.1661, <variable>.eVidStd
	cmp	r2, #19	@ temp.1661,
	beq	.L248	@,
	cmp	r2, #4	@ temp.1661,
	cmpne	r2, #7	@, temp.1661,
	beq	.L248	@,
	cmp	r2, #14	@ temp.1661,
	beq	.L248	@,
	cmp	r2, #18	@ temp.1661,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L248:
	ldr	r2, [r4, #44]	@ temp.1665, s_pstVfmwChan
	cmp	r2, #0	@ temp.1665,
	beq	.L249	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L249	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L249	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L249	@,
	ldr	r2, [r2, #544]	@ temp.1669, <variable>.eVidStd
	cmp	r2, #19	@ temp.1669,
	beq	.L249	@,
	cmp	r2, #4	@ temp.1669,
	cmpne	r2, #7	@, temp.1669,
	beq	.L249	@,
	cmp	r2, #14	@ temp.1669,
	beq	.L249	@,
	cmp	r2, #18	@ temp.1669,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L249:
	ldr	r2, [r4, #48]	@ temp.1673, s_pstVfmwChan
	cmp	r2, #0	@ temp.1673,
	beq	.L250	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L250	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L250	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L250	@,
	ldr	r2, [r2, #544]	@ temp.1677, <variable>.eVidStd
	cmp	r2, #19	@ temp.1677,
	beq	.L250	@,
	cmp	r2, #4	@ temp.1677,
	cmpne	r2, #7	@, temp.1677,
	beq	.L250	@,
	cmp	r2, #14	@ temp.1677,
	beq	.L250	@,
	cmp	r2, #18	@ temp.1677,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L250:
	ldr	r2, [r4, #52]	@ temp.1682, s_pstVfmwChan
	cmp	r2, #0	@ temp.1682,
	beq	.L251	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L251	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L251	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L251	@,
	ldr	r2, [r2, #544]	@ temp.1686, <variable>.eVidStd
	cmp	r2, #19	@ temp.1686,
	beq	.L251	@,
	cmp	r2, #4	@ temp.1686,
	cmpne	r2, #7	@, temp.1686,
	beq	.L251	@,
	cmp	r2, #14	@ temp.1686,
	beq	.L251	@,
	cmp	r2, #18	@ temp.1686,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L251:
	ldr	r2, [r4, #56]	@ temp.1690, s_pstVfmwChan
	cmp	r2, #0	@ temp.1690,
	beq	.L252	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	beq	.L252	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L252	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L252	@,
	ldr	r2, [r2, #544]	@ temp.1694, <variable>.eVidStd
	cmp	r2, #19	@ temp.1694,
	beq	.L252	@,
	cmp	r2, #4	@ temp.1694,
	cmpne	r2, #7	@, temp.1694,
	beq	.L252	@,
	cmp	r2, #14	@ temp.1694,
	beq	.L252	@,
	cmp	r2, #18	@ temp.1694,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
.L252:
	ldr	r2, [r4, #60]	@ temp.1584, s_pstVfmwChan
	cmp	r2, #0	@ temp.1584,
	beq	.L253	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	ip, #0	@ <variable>.s32IsOpen,
	bne	.L332	@,
.L253:
	cmp	r3, #1	@ activeChanNum,
	movwne	r2, #:lower16:g_pstRegCrg	@ tmp584,
	movtne	r2, #:upper16:g_pstRegCrg	@ tmp584,
	beq	.L333	@,
.L255:
	ldr	r3, [r4, #0]	@ temp.1698, s_pstVfmwChan
	cmp	r3, #0	@ temp.1698,
	beq	.L260	@,
	ldr	r1, [r3, #544]	@ eVidStd.1699, <variable>.eVidStd
	cmp	r1, #0	@ eVidStd.1699,
	beq	.L259	@,
	mov	r3, #0	@ prephitmp.1700,
.L261:
	cmp	r1, #6	@ eVidStd.1699,
	orreq	r3, r3, #1	@,, dsp_need_flag, prephitmp.1700
.L260:
	ldr	r1, [r4, #4]	@ temp.1704, s_pstVfmwChan
	cmp	r1, #0	@ temp.1704,
	beq	.L262	@,
	ldr	r0, [r1, #544]	@ eVidStd.1705, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1705,
	beq	.L263	@,
	mov	r1, #0	@ prephitmp.1706,
.L265:
	cmp	r0, #6	@ eVidStd.1705,
	orreq	r1, r1, #1	@,, tmp440, prephitmp.1706
	cmp	r1, #0	@ tmp440,
	movne	r3, #1	@ dsp_need_flag,
.L262:
	ldr	r1, [r4, #8]	@ temp.1710, s_pstVfmwChan
	cmp	r1, #0	@ temp.1710,
	beq	.L266	@,
	ldr	r0, [r1, #544]	@ eVidStd.1711, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1711,
	beq	.L267	@,
	mov	r1, #0	@ prephitmp.1712,
.L269:
	cmp	r0, #6	@ eVidStd.1711,
	orreq	r1, r1, #1	@,, tmp449, prephitmp.1712
	cmp	r1, #0	@ tmp449,
	movne	r3, #1	@ dsp_need_flag,
.L266:
	ldr	r1, [r4, #12]	@ temp.1716, s_pstVfmwChan
	cmp	r1, #0	@ temp.1716,
	beq	.L270	@,
	ldr	r0, [r1, #544]	@ eVidStd.1717, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1717,
	beq	.L271	@,
	mov	r1, #0	@ prephitmp.1718,
.L273:
	cmp	r0, #6	@ eVidStd.1717,
	orreq	r1, r1, #1	@,, tmp458, prephitmp.1718
	cmp	r1, #0	@ tmp458,
	movne	r3, #1	@ dsp_need_flag,
.L270:
	ldr	r1, [r4, #16]	@ temp.1722, s_pstVfmwChan
	cmp	r1, #0	@ temp.1722,
	beq	.L274	@,
	ldr	r0, [r1, #544]	@ eVidStd.1723, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1723,
	beq	.L275	@,
	mov	r1, #0	@ prephitmp.1724,
.L277:
	cmp	r0, #6	@ eVidStd.1723,
	orreq	r1, r1, #1	@,, tmp467, prephitmp.1724
	cmp	r1, #0	@ tmp467,
	movne	r3, #1	@ dsp_need_flag,
.L274:
	ldr	r1, [r4, #20]	@ temp.1728, s_pstVfmwChan
	cmp	r1, #0	@ temp.1728,
	beq	.L278	@,
	ldr	r0, [r1, #544]	@ eVidStd.1729, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1729,
	beq	.L279	@,
	mov	r1, #0	@ prephitmp.1730,
.L281:
	cmp	r0, #6	@ eVidStd.1729,
	orreq	r1, r1, #1	@,, tmp476, prephitmp.1730
	cmp	r1, #0	@ tmp476,
	movne	r3, #1	@ dsp_need_flag,
.L278:
	ldr	r1, [r4, #24]	@ temp.1734, s_pstVfmwChan
	cmp	r1, #0	@ temp.1734,
	beq	.L282	@,
	ldr	r0, [r1, #544]	@ eVidStd.1735, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1735,
	beq	.L283	@,
	mov	r1, #0	@ prephitmp.1736,
.L285:
	cmp	r0, #6	@ eVidStd.1735,
	orreq	r1, r1, #1	@,, tmp485, prephitmp.1736
	cmp	r1, #0	@ tmp485,
	movne	r3, #1	@ dsp_need_flag,
.L282:
	ldr	r1, [r4, #28]	@ temp.1740, s_pstVfmwChan
	cmp	r1, #0	@ temp.1740,
	beq	.L286	@,
	ldr	r0, [r1, #544]	@ eVidStd.1741, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1741,
	beq	.L287	@,
	mov	r1, #0	@ prephitmp.1742,
.L289:
	cmp	r0, #6	@ eVidStd.1741,
	orreq	r1, r1, #1	@,, tmp494, prephitmp.1742
	cmp	r1, #0	@ tmp494,
	movne	r3, #1	@ dsp_need_flag,
.L286:
	ldr	r1, [r4, #32]	@ temp.1746, s_pstVfmwChan
	cmp	r1, #0	@ temp.1746,
	beq	.L290	@,
	ldr	r0, [r1, #544]	@ eVidStd.1747, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1747,
	beq	.L291	@,
	mov	r1, #0	@ prephitmp.1748,
.L293:
	cmp	r0, #6	@ eVidStd.1747,
	orreq	r1, r1, #1	@,, tmp503, prephitmp.1748
	cmp	r1, #0	@ tmp503,
	movne	r3, #1	@ dsp_need_flag,
.L290:
	ldr	r1, [r4, #36]	@ temp.1752, s_pstVfmwChan
	cmp	r1, #0	@ temp.1752,
	beq	.L294	@,
	ldr	r0, [r1, #544]	@ eVidStd.1753, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1753,
	beq	.L295	@,
	mov	r1, #0	@ prephitmp.1754,
.L297:
	cmp	r0, #6	@ eVidStd.1753,
	orreq	r1, r1, #1	@,, tmp512, prephitmp.1754
	cmp	r1, #0	@ tmp512,
	movne	r3, #1	@ dsp_need_flag,
.L294:
	ldr	r1, [r4, #40]	@ temp.1758, s_pstVfmwChan
	cmp	r1, #0	@ temp.1758,
	beq	.L298	@,
	ldr	r0, [r1, #544]	@ eVidStd.1759, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1759,
	beq	.L299	@,
	mov	r1, #0	@ prephitmp.1760,
.L301:
	cmp	r0, #6	@ eVidStd.1759,
	orreq	r1, r1, #1	@,, tmp521, prephitmp.1760
	cmp	r1, #0	@ tmp521,
	movne	r3, #1	@ dsp_need_flag,
.L298:
	ldr	r1, [r4, #44]	@ temp.1764, s_pstVfmwChan
	cmp	r1, #0	@ temp.1764,
	beq	.L302	@,
	ldr	r0, [r1, #544]	@ eVidStd.1765, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1765,
	beq	.L303	@,
	mov	r1, #0	@ prephitmp.1766,
.L305:
	cmp	r0, #6	@ eVidStd.1765,
	orreq	r1, r1, #1	@,, tmp530, prephitmp.1766
	cmp	r1, #0	@ tmp530,
	movne	r3, #1	@ dsp_need_flag,
.L302:
	ldr	r1, [r4, #48]	@ temp.1770, s_pstVfmwChan
	cmp	r1, #0	@ temp.1770,
	beq	.L306	@,
	ldr	r0, [r1, #544]	@ eVidStd.1771, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1771,
	beq	.L307	@,
	mov	r1, #0	@ prephitmp.1772,
.L309:
	cmp	r0, #6	@ eVidStd.1771,
	orreq	r1, r1, #1	@,, tmp539, prephitmp.1772
	cmp	r1, #0	@ tmp539,
	movne	r3, #1	@ dsp_need_flag,
.L306:
	ldr	r1, [r4, #52]	@ temp.1776, s_pstVfmwChan
	cmp	r1, #0	@ temp.1776,
	beq	.L310	@,
	ldr	r0, [r1, #544]	@ eVidStd.1777, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1777,
	beq	.L311	@,
	mov	r1, #0	@ prephitmp.1778,
.L313:
	cmp	r0, #6	@ eVidStd.1777,
	orreq	r1, r1, #1	@,, tmp548, prephitmp.1778
	cmp	r1, #0	@ tmp548,
	movne	r3, #1	@ dsp_need_flag,
.L310:
	ldr	r1, [r4, #56]	@ temp.1782, s_pstVfmwChan
	cmp	r1, #0	@ temp.1782,
	beq	.L314	@,
	ldr	r0, [r1, #544]	@ eVidStd.1783, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd.1783,
	beq	.L315	@,
	mov	r1, #0	@ prephitmp.1784,
.L317:
	cmp	r0, #6	@ eVidStd.1783,
	orreq	r1, r1, #1	@,, tmp557, prephitmp.1784
	cmp	r1, #0	@ tmp557,
	movne	r3, #1	@ dsp_need_flag,
.L314:
	ldr	r1, [r4, #60]	@ D.55442, s_pstVfmwChan
	cmp	r1, #0	@ D.55442,
	beq	.L318	@,
	ldr	r0, [r1, #544]	@ eVidStd, <variable>.eVidStd
	cmp	r0, #0	@ eVidStd,
	movne	r1, #0	@ prephitmp.1558,
	bne	.L320	@,
	ldr	r1, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1558
	moveq	r1, #1	@, prephitmp.1558
.L320:
	cmp	r0, #6	@ eVidStd,
	movne	r0, r1	@, tmp569, prephitmp.1558
	orreq	r0, r1, #1	@,, tmp569, prephitmp.1558
	cmp	r0, #0	@ tmp569,
	beq	.L318	@,
	ldr	r2, [r2, #0]	@ g_pstRegCrg.1578, g_pstRegCrg
	ldr	r3, [r2, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
.L325:
	orr	r3, r3, #2	@ u32TmpValue, u32TmpValue,
	b	.L323	@
.L318:
	ldr	r2, [r2, #0]	@ g_pstRegCrg.1578, g_pstRegCrg
	cmp	r3, #1	@ dsp_need_flag,
	ldr	r3, [r2, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	bfcne	r3, #1, #1	@ u32TmpValue,,
	beq	.L325	@,
.L323:
	str	r3, [r2, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r3, [r4, r5, asl #2]	@ tmp573, s_pstVfmwChan
	ldr	r2, [r3, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, #1	@ <variable>.eVidStd,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	movw	ip, #:lower16:g_vdm_hal_fun_ptr	@ tmp575,
	movt	ip, #:upper16:g_vdm_hal_fun_ptr	@ tmp575,
	ldr	r3, [ip, #24]	@ D.55483, g_vdm_hal_fun_ptr.pfun_BPDDRV_OpenHardware
	cmp	r3, #0	@ D.55483,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	blx	r3	@ D.55483
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L259:
	ldr	r3, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r3, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r3, #0	@, prephitmp.1700
	moveq	r3, #1	@, prephitmp.1700
	b	.L261	@
.L263:
	ldr	r1, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1706
	moveq	r1, #1	@, prephitmp.1706
	b	.L265	@
.L267:
	ldr	ip, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	ip, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1712
	moveq	r1, #1	@, prephitmp.1712
	b	.L269	@
.L271:
	ldr	r1, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1718
	moveq	r1, #1	@, prephitmp.1718
	b	.L273	@
.L275:
	ldr	ip, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	ip, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1724
	moveq	r1, #1	@, prephitmp.1724
	b	.L277	@
.L279:
	ldr	r1, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1730
	moveq	r1, #1	@, prephitmp.1730
	b	.L281	@
.L283:
	ldr	ip, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	ip, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1736
	moveq	r1, #1	@, prephitmp.1736
	b	.L285	@
.L287:
	ldr	r1, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1742
	moveq	r1, #1	@, prephitmp.1742
	b	.L289	@
.L291:
	ldr	ip, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	ip, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1748
	moveq	r1, #1	@, prephitmp.1748
	b	.L293	@
.L295:
	ldr	r1, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1754
	moveq	r1, #1	@, prephitmp.1754
	b	.L297	@
.L299:
	ldr	ip, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	ip, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1760
	moveq	r1, #1	@, prephitmp.1760
	b	.L301	@
.L303:
	ldr	r1, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1766
	moveq	r1, #1	@, prephitmp.1766
	b	.L305	@
.L307:
	ldr	ip, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	ip, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1772
	moveq	r1, #1	@, prephitmp.1772
	b	.L309	@
.L311:
	ldr	r1, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1778
	moveq	r1, #1	@, prephitmp.1778
	b	.L313	@
.L315:
	ldr	ip, [r1, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	ip, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.1784
	moveq	r1, #1	@, prephitmp.1784
	b	.L317	@
.L332:
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L253	@,
	ldr	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ <variable>.s32Priority,
	beq	.L253	@,
	ldr	r2, [r2, #544]	@ temp.1588, <variable>.eVidStd
	cmp	r2, #19	@ temp.1588,
	beq	.L253	@,
	cmp	r2, #4	@ temp.1588,
	cmpne	r2, #7	@, temp.1588,
	beq	.L253	@,
	cmp	r2, #14	@ temp.1588,
	beq	.L253	@,
	cmp	r2, #18	@ temp.1588,
	addne	r3, r3, #1	@ activeChanNum, activeChanNum,
	b	.L253	@
.L333:
	movw	lr, #:lower16:g_vdm_hal_fun_ptr	@ tmp422,
	movt	lr, #:upper16:g_vdm_hal_fun_ptr	@ tmp422,
	ldr	r3, [lr, #0]	@ D.55456, g_vdm_hal_fun_ptr.pfun_VDMDRV_OpenHardware
	cmp	r3, #0	@ D.55456,
	beq	.L334	@,
	mov	r0, #0	@,
	blx	r3	@ D.55456
.L257:
	movw	r2, #:lower16:g_pstRegCrg	@ tmp584,
	movt	r2, #:upper16:g_pstRegCrg	@ tmp584,
	mov	ip, #25	@ tmp425,
	ldr	r1, [r2, #0]	@ g_pstRegCrg.886, g_pstRegCrg
	ldr	lr, [r1, #120]	@ D.55462, <variable>.PERI_CRG30.u32
	bfi	lr, ip, #12, #5	@ u32TmpValue, tmp425,,
	bfc	lr, #17, #1	@ u32TmpValue,,
	str	lr, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r3, [r2, #0]	@ g_pstRegCrg.1573, g_pstRegCrg
	ldr	r0, [r3, #120]	@ D.55464, <variable>.PERI_CRG30.u32
	orr	ip, r0, #131072	@ u32TmpValue, D.55464,
	str	ip, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	b	.L255	@
.L331:
	movw	r1, #:lower16:.LC2	@,
	movw	r2, #10074	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L334:
	mov	r0, r3	@, D.55456
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #10116	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L257	@
	.fnend
	.size	VCTRL_OpenHardware, .-VCTRL_OpenHardware
	.align	2
	.global	Get_YuvFormat
	.type	Get_YuvFormat, %function
Get_YuvFormat:
	.fnstart
.LFB1657:
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
	cmp	r1, #6	@ enFmt,
	ldrls	pc, [pc, r1, asl #2]	@ enFmt
	b	.L336	@
.L344:
	.word	.L337
	.word	.L338
	.word	.L339
	.word	.L340
	.word	.L341
	.word	.L342
	.word	.L343
.L343:
	cmp	r0, #1	@ SemiPlanarFlag,
	movne	r0, #7	@, eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L336:
	mov	r3, r1	@, enFmt
	movw	r2, #10046	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC4	@,
	movt	r1, #:upper16:.LC4	@,
	bl	dprint_vfmw	@
	mov	r0, #13	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L337:
	cmp	r0, #1	@ SemiPlanarFlag,
	movne	r0, #6	@ eYuvFormat,
	moveq	r0, #0	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L338:
	cmp	r0, #1	@ SemiPlanarFlag,
	moveq	r0, #2	@ eYuvFormat,
	movne	r0, #8	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L339:
	cmp	r0, #1	@ SemiPlanarFlag,
	moveq	r0, #4	@ eYuvFormat,
	movne	r0, #10	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L340:
	cmp	r0, #1	@ SemiPlanarFlag,
	moveq	r0, #3	@ eYuvFormat,
	movne	r0, #9	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L341:
	cmp	r0, #1	@ SemiPlanarFlag,
	moveq	r0, #5	@ eYuvFormat,
	movne	r0, #11	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L342:
	cmp	r0, #1	@ SemiPlanarFlag,
	moveq	r0, #13	@ eYuvFormat,
	movne	r0, #12	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	Get_YuvFormat, .-Get_YuvFormat
	.align	2
	.global	VCTRL_SetLastFrameState
	.type	VCTRL_SetLastFrameState, %function
VCTRL_SetLastFrameState:
	.fnstart
.LFB1631:
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
	cmp	r0, #15	@ ChanID,
	bhi	.L358	@,
	movw	r2, #:lower16:.LANCHOR0	@ tmp138,
	movt	r2, #:upper16:.LANCHOR0	@ tmp138,
	ldr	r3, [r2, r0, asl #2]	@ D.54338, s_pstVfmwChan
	cmp	r3, #0	@ D.54338,
	strne	r1, [r3, #340]	@ eState, <variable>.eLastFrameState
	ldmfd	sp, {fp, sp, pc}	@
.L358:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #8393	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_SetLastFrameState, .-VCTRL_SetLastFrameState
	.align	2
	.global	VCTRL_ReportLastFrame
	.type	VCTRL_ReportLastFrame, %function
VCTRL_ReportLastFrame:
	.fnstart
.LFB1632:
	@ args = 0, pretend = 0, frame = 8
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
	cmp	r1, #1	@ Value,
	mov	r5, r1	@ Value, Value
	movw	r4, #:lower16:.LANCHOR0	@ tmp145,
	movwls	r3, #:lower16:.LANCHOR1	@ tmp138,
	movtls	r3, #:upper16:.LANCHOR1	@ tmp138,
	movt	r4, #:upper16:.LANCHOR0	@ tmp145,
	movhi	r1, #4	@ eState,
	ldrls	r1, [r3, r5, asl #2]	@ eState, CSWTCH.924
	mov	r6, r0	@ ChanID, ChanID
	bl	VCTRL_SetLastFrameState	@
	ldr	ip, [r4, #64]	@ g_event_report.791, g_event_report
	cmp	ip, #0	@ g_event_report.791,
	beq	.L362	@,
	sub	r2, fp, #28	@ tmp140,,
	mov	r0, r6	@, ChanID
	mov	r1, #115	@,
	mov	r3, #4	@,
	str	r5, [r2, #-4]!	@ Value, para
	blx	ip	@ g_event_report.791
.L362:
	ldr	r3, [r4, r6, asl #2]	@ tmp143, s_pstVfmwChan
	mov	r2, r5	@, Value
	movw	r1, #:lower16:.LC7	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC7	@,
	ldr	r3, [r3, #340]	@, <variable>.eLastFrameState
	bl	dprint_vfmw	@
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	.fnend
	.size	VCTRL_ReportLastFrame, .-VCTRL_ReportLastFrame
	.align	2
	.global	VCTRL_SvdecLastFrame
	.type	VCTRL_SvdecLastFrame, %function
VCTRL_SvdecLastFrame:
	.fnstart
.LFB1634:
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
	add	r1, r1, #2	@, LastFrameID,
	bl	VCTRL_ReportLastFrame	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_SvdecLastFrame, .-VCTRL_SvdecLastFrame
	.align	2
	.global	VCTRL_SetLastFrameIdPlus2
	.type	VCTRL_SetLastFrameIdPlus2, %function
VCTRL_SetLastFrameIdPlus2:
	.fnstart
.LFB1630:
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
	cmp	r0, #15	@ ChanID,
	bhi	.L370	@,
	movw	r2, #:lower16:.LANCHOR0	@ tmp138,
	movt	r2, #:upper16:.LANCHOR0	@ tmp138,
	ldr	r3, [r2, r0, asl #2]	@ D.54326, s_pstVfmwChan
	cmp	r3, #0	@ D.54326,
	strne	r1, [r3, #336]	@ Value, <variable>.s32LastFrameIdPlus2
	ldmfd	sp, {fp, sp, pc}	@
.L370:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #8381	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_SetLastFrameIdPlus2, .-VCTRL_SetLastFrameIdPlus2
	.align	2
	.global	VCTRL_GetLastFrameIdPlus2
	.type	VCTRL_GetLastFrameIdPlus2, %function
VCTRL_GetLastFrameIdPlus2:
	.fnstart
.LFB1629:
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
	cmp	r0, #15	@ ChanID,
	bhi	.L376	@,
	movw	r1, #:lower16:.LANCHOR0	@ tmp139,
	movt	r1, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r3, [r1, r0, asl #2]	@ D.54314, s_pstVfmwChan
	cmp	r3, #0	@ D.54314,
	mvneq	r0, #0	@ D.54312,
	ldrne	r0, [r3, #336]	@ D.54312, <variable>.s32LastFrameIdPlus2
	ldmfd	sp, {fp, sp, pc}	@
.L376:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #8369	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.54312,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetLastFrameIdPlus2, .-VCTRL_GetLastFrameIdPlus2
	.align	2
	.global	VCTRL_SetVdecExtra
	.type	VCTRL_SetVdecExtra, %function
VCTRL_SetVdecExtra:
	.fnstart
.LFB1620:
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
	add	r4, r0, #4992	@ tmp138, new_extra_ref,
	add	r3, r4, #8	@ tmp138, tmp138,
	movw	r2, #10000	@ tmp140,
	movw	r4, #:lower16:.LANCHOR0	@ tmp158,
	cmp	r3, r2	@ tmp138, tmp140
	movt	r4, #:upper16:.LANCHOR0	@ tmp158,
	mov	r5, r1	@ new_extra_disp, new_extra_disp
	str	r0, [r4, #68]	@ new_extra_ref, extra_ref
	bhi	.L381	@,
.L378:
	add	r2, r5, #4992	@ tmp148, new_extra_disp,
	movw	ip, #5000	@ tmp143,
	add	r1, r2, #8	@ tmp148, tmp148,
	cmp	r0, ip	@ new_extra_ref, tmp143
	movge	r0, ip	@ iftmp.689, tmp143
	movw	r6, #:lower16:-5000	@ tmp145,
	movt	r6, #:upper16:-5000	@ tmp145,
	cmp	r0, r6	@ iftmp.689, tmp145
	strge	r0, [r4, #68]	@, iftmp.689, extra_ref
	strlt	r6, [r4, #68]	@, tmp145, extra_ref
	movw	r0, #10000	@ tmp150,
	cmp	r1, r0	@ tmp148, tmp150
	movw	r6, #:lower16:.LANCHOR0	@ tmp144,
	str	r5, [r4, #72]	@ new_extra_disp, extra_disp
	movt	r6, #:upper16:.LANCHOR0	@ tmp144,
	bhi	.L382	@,
.L379:
	movw	r0, #5000	@ tmp153,
	movw	r3, #:lower16:-5000	@ tmp155,
	cmp	r5, r0	@ new_extra_disp, tmp153
	movge	r5, r0	@ iftmp.1952, tmp153
	movt	r3, #:upper16:-5000	@ tmp155,
	cmp	r5, r3	@ iftmp.1952, tmp155
	strge	r5, [r4, #72]	@, iftmp.1952, extra_disp
	strlt	r3, [r4, #72]	@, tmp155, extra_disp
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L381:
	mov	r2, r0	@, new_extra_ref
	movw	r1, #:lower16:.LC8	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC8	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #68]	@ new_extra_ref, extra_ref
	b	.L378	@
.L382:
	mov	r2, r5	@, new_extra_disp
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC9	@,
	movt	r1, #:upper16:.LC9	@,
	bl	dprint_vfmw	@
	ldr	r5, [r6, #72]	@ new_extra_disp, extra_disp
	b	.L379	@
	.fnend
	.size	VCTRL_SetVdecExtra, .-VCTRL_SetVdecExtra
	.align	2
	.global	VCTRL_GetChanCapLevel
	.type	VCTRL_GetChanCapLevel, %function
VCTRL_GetChanCapLevel:
	.fnstart
.LFB1619:
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
	cmp	r0, #15	@ ChanID,
	bhi	.L388	@,
	movw	r1, #:lower16:.LANCHOR0	@ tmp139,
	movt	r1, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r3, [r1, r0, asl #2]	@ D.53774, s_pstVfmwChan
	cmp	r3, #0	@ D.53774,
	moveq	r0, #33	@ D.53772,
	ldrne	r0, [r3, #40]	@ D.53772, <variable>.eChanCapLevel
	ldmfd	sp, {fp, sp, pc}	@
.L388:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7480	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53772,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetChanCapLevel, .-VCTRL_GetChanCapLevel
	.align	2
	.global	VCTRL_GetChanHeight
	.type	VCTRL_GetChanHeight, %function
VCTRL_GetChanHeight:
	.fnstart
.LFB1618:
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
	cmp	r0, #15	@ ChanID,
	bhi	.L394	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp139,
	movt	r3, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r0, [r3, r0, asl #2]	@ D.53762, s_pstVfmwChan
	cmp	r0, #0	@ D.53762,
	beq	.L395	@,
	ldr	r0, [r0, #1300]	@ D.53760, <variable>.stSynExtraData.stChanOption.s32MaxHeight
	ldmfd	sp, {fp, sp, pc}	@
.L394:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7472	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53760,
	ldmfd	sp, {fp, sp, pc}	@
.L395:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7473	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53760,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetChanHeight, .-VCTRL_GetChanHeight
	.align	2
	.global	VCTRL_GetChanWidth
	.type	VCTRL_GetChanWidth, %function
VCTRL_GetChanWidth:
	.fnstart
.LFB1617:
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
	cmp	r0, #15	@ ChanID,
	bhi	.L401	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp139,
	movt	r3, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r0, [r3, r0, asl #2]	@ D.53750, s_pstVfmwChan
	cmp	r0, #0	@ D.53750,
	beq	.L402	@,
	ldr	r0, [r0, #1296]	@ D.53748, <variable>.stSynExtraData.stChanOption.s32MaxWidth
	ldmfd	sp, {fp, sp, pc}	@
.L401:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7464	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53748,
	ldmfd	sp, {fp, sp, pc}	@
.L402:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7465	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53748,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetChanWidth, .-VCTRL_GetChanWidth
	.align	2
	.global	GetNextDecodeMode
	.type	GetNextDecodeMode, %function
GetNextDecodeMode:
	.fnstart
.LFB1610:
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
	movw	r7, #:lower16:1431655766	@ tmp146,
	mov	ip, r2, asl #1	@ tmp143, Threshould,
	movt	r7, #:upper16:1431655766	@ tmp146,
	mov	r4, r2	@ Threshould, Threshould
	add	r6, r2, #7	@ tmp140, Threshould,
	smull	r2, r3, r7, ip	@, tmp145, tmp146, tmp143
	cmp	r4, #0	@ Threshould,
	mov	r5, r0	@ CurMode, CurMode
	mov	r7, r1	@ StreamAmount, StreamAmount
	movge	r6, r4	@ Threshould, Threshould
	mov	r0, #30	@,
	mov	r6, r6, asr #3	@ tmp141, Threshould,
	movw	r1, #:lower16:.LC11	@,
	movt	r1, #:upper16:.LC11	@,
	str	r4, [sp, #0]	@ Threshould,
	mov	r2, r6	@, tmp141
	sub	r3, r3, ip, asr #31	@, tmp145, tmp143,
	str	r7, [sp, #4]	@ StreamAmount,
	bl	dprint_vfmw	@
	cmp	r5, #3	@ CurMode,
	beq	.L410	@,
	cmp	r4, r7	@ Threshould, StreamAmount
	blt	.L407	@,
.L409:
	mov	r4, r5	@ NextMode, CurMode
.L406:
	mov	r2, r5	@, CurMode
	mov	r3, r4	@, NextMode
	mov	r0, #30	@,
	movw	r1, #:lower16:.LC14	@,
	movt	r1, #:upper16:.LC14	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, NextMode
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L407:
	movw	r1, #:lower16:.LC13	@,
	mov	r0, #30	@,
	movt	r1, #:upper16:.LC13	@,
	mov	r4, #3	@ NextMode,
	bl	dprint_vfmw	@
	b	.L406	@
.L410:
	cmp	r6, r7	@ tmp141, StreamAmount
	ble	.L409	@,
	movw	r1, #:lower16:.LC12	@,
	mov	r0, #30	@,
	movt	r1, #:upper16:.LC12	@,
	mov	r4, #0	@ NextMode,
	bl	dprint_vfmw	@
	b	.L406	@
	.fnend
	.size	GetNextDecodeMode, .-GetNextDecodeMode
	.align	2
	.global	VCTRL_GetChanMemSize
	.type	VCTRL_GetChanMemSize, %function
VCTRL_GetChanMemSize:
	.fnstart
.LFB1607:
	@ args = 0, pretend = 0, frame = 968
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #1004
	sub	sp, sp, #1004	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	sl, r0, asl #3	@ tmp317, eCapLevel,
	rsb	r8, r0, sl	@ tmp169, eCapLevel, tmp317
	sub	r3, r0, #18	@ D.56202, eCapLevel,
	movw	r6, #:lower16:CapItem	@ tmp316,
	movt	r6, #:upper16:CapItem	@ tmp316,
	cmp	r3, #7	@ D.56202,
	add	r4, r6, r8, asl #2	@, tmp171, tmp316, tmp169,
	str	r2, [fp, #-996]	@ ScdMemSize, %sfp
	mov	r5, r0	@ eCapLevel, eCapLevel
	movwls	r2, #:lower16:.LANCHOR1	@ tmp197,
	ldr	r8, [r4, #12]	@ TempMinFrame, CapItem
	movtls	r2, #:upper16:.LANCHOR1	@ tmp197,
	ldr	r0, [r4, #20]	@, CapItem
	ldr	ip, [r4, #8]	@ TempPmv, CapItem
	addls	r3, r2, r3, asl #2	@, tmp200, tmp197, D.56202,
	ldr	r9, [r4, #16]	@ TempMiddleFrame, CapItem
	movw	r4, #:lower16:.LANCHOR0	@ tmp318,
	movt	r4, #:upper16:.LANCHOR0	@ tmp318,
	str	r1, [fp, #-992]	@ VdmMemSize, %sfp
	ldrls	r3, [r3, #8]	@ MinDnrFspNum, CSWTCH.927
	sub	r2, r8, #2	@ tmp202, TempMinFrame,
	ldr	r1, [r4, #68]	@ extra_ref, extra_ref
	movhi	r3, #6	@ MinDnrFspNum,
	rsb	r3, r3, r2	@ s32MaxRefFrameNum, MinDnrFspNum, tmp202
	str	r0, [fp, #-1008]	@, %sfp
	cmp	r1, #0	@ extra_ref,
	movlt	r2, #0	@ tmp206,
	strlt	r2, [r4, #68]	@ tmp206, extra_ref
	cmp	r3, #15	@ s32MaxRefFrameNum,
	movgt	r7, #0	@ extra_ref_tmp,
	bgt	.L416	@,
	ldr	r7, [r4, #68]	@ extra_ref_tmp, extra_ref
	add	r2, r3, r7	@ D.52956, s32MaxRefFrameNum, extra_ref_tmp
	cmp	r2, #16	@ D.52956,
	addgt	r7, r7, #16	@ D.52959, extra_ref_tmp,
	rsbgt	r7, r2, r7	@ extra_ref_tmp, D.52956, D.52959
.L416:
	add	r3, r7, ip	@ TempPmv.2074, extra_ref_tmp, TempPmv
	ldr	r1, [r4, #72]	@, extra_disp
	cmp	r3, #0	@ TempPmv.2074,
	str	r1, [fp, #-1000]	@, %sfp
	ble	.L432	@,
	cmp	r3, #17	@ TempPmv.2074,
	movge	r3, #17	@ TempPmv.2074,
	str	r3, [fp, #-1004]	@ TempPmv.2074, %sfp
.L418:
	cmp	r5, #23	@ eCapLevel,
	bhi	.L419	@,
	ldr	ip, [fp, #-1000]	@, %sfp
	add	r3, r7, ip	@ D.52962, extra_ref_tmp,
	add	r2, r3, r8	@ TempMinFrame.2071, D.52962, TempMinFrame
	add	r1, r3, r9	@ TempMiddleFrame.2072, D.52962, TempMiddleFrame
	cmp	r2, #0	@ TempMinFrame.2071,
	cmpgt	r1, #0	@, TempMiddleFrame.2072,
	ble	.L420	@,
	ldr	r0, [fp, #-1008]	@, %sfp
	add	lr, r3, r0	@ TempFluentFrame.2073, D.52962,
	cmp	lr, #0	@ TempFluentFrame.2073,
	strgt	lr, [fp, #-1012]	@ TempFluentFrame.2073, %sfp
	strgt	r1, [fp, #-1000]	@ TempMiddleFrame.2072, %sfp
	movgt	r8, r2	@ nMinFrame, TempMinFrame.2071
	ble	.L420	@,
.L422:
	movw	r7, #:lower16:g_vdm_hal_fun_ptr	@ tmp219,
	movt	r7, #:upper16:g_vdm_hal_fun_ptr	@ tmp219,
	ldr	ip, [r7, #48]	@ D.52980, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	cmp	ip, #0	@ D.52980,
	beq	.L425	@,
.L433:
	rsb	r5, r5, sl	@ tmp223, eCapLevel, tmp317
	ldr	sl, [fp, #-1004]	@, %sfp
	str	r8, [sp, #4]	@ nMinFrame,
	add	r8, r5, #1	@ tmp231, tmp223,
	mov	r9, #0	@ tmp233,
	mov	r0, #1	@,
	str	sl, [sp, #0]	@,
	mvn	r1, #-2147483648	@,
	ldr	r3, [r6, r8, asl #2]	@ tmp232, CapItem
	mvn	sl, #0	@ tmp234,
	ldr	r2, [r6, r5, asl #2]	@ tmp226, CapItem
	movw	r4, #:lower16:CapItem	@ tmp220,
	str	r9, [sp, #8]	@ tmp233,
	sub	r9, fp, #984	@ tmp236,,
	str	sl, [sp, #12]	@ tmp234,
	movt	r4, #:upper16:CapItem	@ tmp220,
	str	r9, [sp, #16]	@ tmp236,
	add	r6, r6, r5, asl #2	@, tmp225, tmp316, tmp223,
	blx	ip	@ D.52980
	subs	r3, r0, #0	@ ret,
	bne	.L425	@,
	ldr	r2, [fp, #-980]	@ MemArrange.TotalMemUsed, MemArrange.TotalMemUsed
	ldr	lr, [fp, #-992]	@, %sfp
	add	r1, r2, #47616	@ tmp238, MemArrange.TotalMemUsed,
	add	ip, r1, #16	@ tmp238, tmp238,
	str	ip, [lr, #0]	@ tmp238,
	ldr	r1, [fp, #-996]	@, %sfp
	ldr	r0, [r6, #24]	@ tmp248, CapItem
	add	r2, r0, #32768	@ tmp249, tmp248,
	str	r2, [r1, #0]	@ tmp249,
	ldr	ip, [r7, #48]	@ temp.2076, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	cmp	ip, #0	@ temp.2076,
	beq	.L427	@,
	ldr	lr, [r4, r8, asl #2]	@ tmp264, CapItem
	mov	r0, #1	@,
	ldr	r2, [fp, #-1000]	@, %sfp
	mvn	r1, #-2147483648	@,
	str	r3, [sp, #8]	@ ret,
	ldr	r3, [fp, #-1004]	@, %sfp
	str	r2, [sp, #4]	@,
	ldr	r2, [r4, r5, asl #2]	@, CapItem
	str	r3, [sp, #0]	@,
	mov	r3, lr	@, tmp264
	str	sl, [sp, #12]	@ tmp234,
	str	r9, [sp, #16]	@ tmp236,
	blx	ip	@ temp.2076
	subs	lr, r0, #0	@ ret.2079,
	bne	.L427	@,
	ldr	ip, [fp, #-980]	@ MemArrange.TotalMemUsed, MemArrange.TotalMemUsed
	ldr	r2, [fp, #-992]	@, %sfp
	add	r0, ip, #47616	@ tmp270, MemArrange.TotalMemUsed,
	add	r3, r0, #16	@ tmp270, tmp270,
	str	r3, [r2, #4]	@ tmp270,
	ldr	r0, [fp, #-996]	@, %sfp
	ldr	r1, [r6, #24]	@ tmp280, CapItem
	add	ip, r1, #32768	@ tmp281, tmp280,
	str	ip, [r0, #4]	@ tmp281,
	ldr	ip, [r7, #48]	@ temp.2083, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	cmp	ip, #0	@ temp.2083,
	beq	.L429	@,
	ldr	r3, [r4, r8, asl #2]	@ tmp296, CapItem
	mov	r0, #1	@,
	ldr	r2, [r4, r5, asl #2]	@ tmp290, CapItem
	mvn	r1, #-2147483648	@,
	ldr	r4, [fp, #-1004]	@, %sfp
	str	lr, [sp, #8]	@ ret.2079,
	str	sl, [sp, #12]	@ tmp234,
	str	r4, [sp, #0]	@,
	ldr	r4, [fp, #-1012]	@, %sfp
	str	r9, [sp, #16]	@ tmp236,
	str	r4, [sp, #4]	@,
	blx	ip	@ temp.2083
	cmp	r0, #0	@ ret.2086
	bne	.L429	@,
	ldr	r1, [fp, #-980]	@ MemArrange.TotalMemUsed, MemArrange.TotalMemUsed
	ldr	ip, [fp, #-992]	@, %sfp
	add	lr, r1, #47616	@ tmp302, MemArrange.TotalMemUsed,
	add	r2, lr, #16	@ tmp302, tmp302,
	str	r2, [ip, #8]	@ tmp302,
	ldr	lr, [fp, #-996]	@, %sfp
	ldr	r3, [r6, #24]	@ tmp312, CapItem
	add	r1, r3, #32768	@ tmp313, tmp312,
	str	r1, [lr, #8]	@ tmp313,
	b	.L424	@
.L419:
	cmp	r5, #32	@ eCapLevel,
	bls	.L423	@,
.L431:
	mvn	r0, #0	@ D.52998,
.L424:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L420:
	ldr	ip, [r4, #72]	@ extra_disp.2075, extra_disp
	mov	r3, r7	@, extra_ref_tmp
	ldr	lr, [fp, #-1008]	@, %sfp
	mov	r0, #32	@,
	str	r7, [sp, #8]	@ extra_ref_tmp,
	movw	r1, #:lower16:.LC16	@,
	str	r7, [sp, #20]	@ extra_ref_tmp,
	movw	r7, #:lower16:g_vdm_hal_fun_ptr	@ tmp219,
	movt	r7, #:upper16:g_vdm_hal_fun_ptr	@ tmp219,
	movt	r1, #:upper16:.LC16	@,
	mov	r2, r8	@, TempMinFrame
	str	ip, [sp, #24]	@ extra_disp.2075,
	str	ip, [sp, #0]	@ extra_disp.2075,
	mov	r4, lr	@,
	str	ip, [sp, #12]	@ extra_disp.2075,
	str	lr, [fp, #-1012]	@, %sfp
	str	r9, [fp, #-1000]	@ TempMiddleFrame, %sfp
	str	r9, [sp, #4]	@ TempMiddleFrame,
	str	lr, [sp, #16]	@ tmp4,
	bl	dprint_vfmw	@
	ldr	ip, [r7, #48]	@ D.52980, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	cmp	ip, #0	@ D.52980,
	bne	.L433	@,
.L425:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC17	@,
	movw	r2, #6181	@,
	movt	r1, #:upper16:.LC17	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52998,
	b	.L424	@
.L423:
	ldr	r7, [fp, #-1008]	@, %sfp
	str	r9, [fp, #-1000]	@ TempMiddleFrame, %sfp
	str	r7, [fp, #-1012]	@, %sfp
	b	.L422	@
.L432:
	mov	r2, ip	@, TempPmv
	movw	r1, #:lower16:.LC15	@,
	mov	r3, r7	@, extra_ref_tmp
	movt	r1, #:upper16:.LC15	@,
	mov	r0, #32	@,
	cmp	ip, #17	@ TempPmv,
	movge	ip, #17	@ TempPmv,
	str	ip, [fp, #-1004]	@ TempPmv, %sfp
	bl	dprint_vfmw	@
	b	.L418	@
.L427:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC17	@,
	movw	r2, #6200	@,
	movt	r1, #:upper16:.LC17	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52998,
	b	.L424	@
.L429:
	movw	r1, #:lower16:.LC17	@,
	movw	r2, #6219	@,
	movt	r1, #:upper16:.LC17	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	b	.L431	@
	.fnend
	.size	VCTRL_GetChanMemSize, .-VCTRL_GetChanMemSize
	.align	2
	.global	VCTRL_GetChanMemSizeWithOption
	.type	VCTRL_GetChanMemSizeWithOption, %function
VCTRL_GetChanMemSizeWithOption:
	.fnstart
.LFB1605:
	@ args = 0, pretend = 0, frame = 944
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #972
	sub	sp, sp, #972	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	ip, #:lower16:4780696	@ tmp242,
	cmp	r0, #26	@ eCapLevel,
	movt	ip, #:upper16:4780696	@ tmp242,
	movw	sl, #:lower16:11613560	@ tmp241,
	movt	sl, #:upper16:11613560	@ tmp241,
	movne	sl, ip	@ s32ChanCtxSize, tmp242
	cmp	r3, #2	@ flag,
	mov	r7, r0	@ eCapLevel, eCapLevel
	mov	r8, r3	@ flag, flag
	mov	r4, r1	@ pChanOption, pChanOption
	mov	r5, r2	@ pDetailMemSize, pDetailMemSize
	beq	.L437	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp165,
	movt	r3, #:upper16:.LANCHOR0	@ tmp165,
	ldr	ip, [r1, #64]	@ D.52779, <variable>.s32DisplayFrameNum
	ldr	r9, [r3, #72]	@ extra_disp.643, extra_disp
	ldr	r2, [r1, #36]	@ D.52777, <variable>.s32MaxRefFrameNum
	ldr	r3, [r3, #68]	@ extra_ref.642, extra_ref
	add	r6, r9, ip	@ TempDispNum, extra_disp.643, D.52779
	add	r1, r3, r2	@ TempRefNum, extra_ref.642, D.52777
	orrs	r0, r6, r1	@, TempDispNum, TempRefNum
	bmi	.L465	@,
	cmp	r1, #16	@ TempRefNum,
	strle	r1, [r4, #36]	@ TempRefNum, <variable>.s32MaxRefFrameNum
	strle	r6, [r4, #64]	@ TempDispNum, <variable>.s32DisplayFrameNum
	bgt	.L466	@,
.L441:
	rsbs	r8, r8, #1	@ tmp185, flag
	movcc	r8, #0	@ tmp185
	cmp	r7, #25	@ eCapLevel,
	moveq	r8, #0	@, tmp185,
	cmp	r8, #0	@ tmp185,
	bne	.L467	@,
.L437:
	ldr	r3, [r4, #4]	@ D.52798, <variable>.Purpose
	cmp	r3, #2	@ D.52798,
	bhi	.L468	@,
	bne	.L443	@,
	ldr	r3, [r4, #68]	@ D.52806, <variable>.s32SlotWidth
	cmp	r3, #0	@ D.52806,
	beq	.L444	@,
	ldr	r2, [r4, #72]	@ D.52808, <variable>.s32SlotHeight
	cmp	r2, #0	@ D.52808,
	beq	.L444	@,
	mul	r3, r2, r3	@ tmp189, D.52808, D.52806
	ldr	r1, [r4, #64]	@ <variable>.s32DisplayFrameNum, <variable>.s32DisplayFrameNum
	mov	r0, #0	@ tmp194,
	stmib	r5, {r0, sl}	@ phole stm
	mov	ip, r3, asl #1	@ tmp190, tmp189,
	mla	r2, r1, ip, ip	@ tmp193, <variable>.s32DisplayFrameNum, tmp190, tmp190
	str	r2, [r5, #0]	@ tmp193, <variable>.VdhDetailMem
.L439:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L466:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC19	@,
	movt	r1, #:upper16:.LC19	@,
	bl	dprint_vfmw	@
	mov	r0, #16	@ tmp178,
	str	r6, [r4, #64]	@ TempDispNum, <variable>.s32DisplayFrameNum
	str	r0, [r4, #36]	@ tmp178, <variable>.s32MaxRefFrameNum
	b	.L441	@
.L443:
	cmp	r3, #1	@ D.52798,
	mvnne	r0, #0	@ D.52787,
	bne	.L439	@
.L446:
	ldr	r0, [r4, #36]	@ temp.2117, <variable>.s32MaxRefFrameNum
	cmp	r0, #0	@ temp.2117,
	blt	.L447	@,
	ldr	r2, [r4, #12]	@ D.52821, <variable>.s32MaxWidth
	cmp	r2, #31	@ D.52821,
	ble	.L447	@,
	ldr	r3, [r4, #16]	@ D.52823, <variable>.s32MaxHeight
	cmp	r3, #31	@ D.52823,
	ble	.L447	@,
	ldr	ip, [r4, #60]	@ <variable>.s32SCDBufSize, <variable>.s32SCDBufSize
	cmp	ip, #262144	@ <variable>.s32SCDBufSize,
	blt	.L447	@,
	ldr	r1, [r4, #48]	@ D.52827, <variable>.s32SupportH264
	cmp	r1, #1	@ D.52827,
	beq	.L469	@,
	cmp	r1, #2	@ D.52827,
	beq	.L470	@,
.L449:
	ldr	r6, [r4, #44]	@ <variable>.s32SupportBFrame, <variable>.s32SupportBFrame
	cmp	r6, #0	@ <variable>.s32SupportBFrame,
	moveq	lr, #1	@ PmvNum,
	beq	.L451	@,
	add	lr, r0, #1	@ PmvNum.2121, temp.2117,
	cmp	lr, #17	@ PmvNum.2121,
	movge	lr, #17	@ PmvNum,
.L451:
	movw	r1, #:lower16:g_vdm_hal_fun_ptr	@ tmp206,
	movt	r1, #:upper16:g_vdm_hal_fun_ptr	@ tmp206,
	sub	r6, r7, #27	@ D.52845, eCapLevel,
	ldr	r8, [r4, #64]	@ temp.2122, <variable>.s32DisplayFrameNum
	cmp	r6, #6	@ D.52845,
	ldr	ip, [r1, #48]	@ D.52850, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	mvncc	r1, #1	@, eFlag,
	mvncs	r1, #0	@, eFlag,
	cmp	ip, #0	@ D.52850,
	beq	.L454	@,
	add	r0, r0, r8	@ tmp207, temp.2117, temp.2122
	str	lr, [sp, #0]	@ PmvNum,
	str	r1, [sp, #12]	@ eFlag,
	sub	lr, fp, #984	@ tmp211,,
	add	r1, r0, #2	@ tmp208, tmp207,
	str	lr, [sp, #16]	@ tmp211,
	str	r1, [sp, #4]	@ tmp208,
	mov	r0, #0	@ tmp209,
	mvn	r1, #-2147483648	@,
	str	r0, [sp, #8]	@ tmp209,
	mov	r0, #1	@,
	blx	ip	@ D.52850
	cmp	r0, #0	@,
	bne	.L454	@,
	ldr	ip, [fp, #-980]	@ MemArrange.TotalMemUsed, MemArrange.TotalMemUsed
	add	r3, ip, #16	@ D.52858, MemArrange.TotalMemUsed,
	str	r3, [r5, #0]	@ D.52858, <variable>.VdhDetailMem
	ldr	r2, [r4, #132]	@ <variable>.u32DynamicFrameStoreAllocEn, <variable>.u32DynamicFrameStoreAllocEn
	cmp	r2, #1	@ <variable>.u32DynamicFrameStoreAllocEn,
	addne	r3, r3, #47616	@ tmp214, D.52858,
	strne	r3, [r5, #0]	@ tmp214, <variable>.VdhDetailMem
	ldreq	r3, [r4, #60]	@ <variable>.s32SCDBufSize, <variable>.s32SCDBufSize
	ldrne	r3, [r4, #60]	@ <variable>.s32SCDBufSize, <variable>.s32SCDBufSize
	addeq	r3, r3, #79872	@ tmp219, <variable>.s32SCDBufSize,
	str	sl, [r5, #8]	@ s32ChanCtxSize, <variable>.ChanCtxDetailMem
	addne	r3, r3, #32768	@ tmp216, <variable>.s32SCDBufSize,
	addeq	r3, r3, #528	@ tmp219, tmp219,
	str	r3, [r5, #4]	@ tmp219, <variable>.ScdDetailMem
	ldr	r3, [r4, #48]	@ <variable>.s32SupportH264, <variable>.s32SupportH264
	cmp	r3, #0	@ <variable>.s32SupportH264,
	beq	.L458	@,
	ldr	lr, [r4, #20]	@ <variable>.s32MaxSliceNum, <variable>.s32MaxSliceNum
	movw	r1, #4060	@ tmp222,
	ldr	r0, [r4, #28]	@ D.52875, <variable>.s32MaxSpsNum
	mov	r3, #4000	@ tmp224,
	ldr	r2, [r4, #32]	@ D.52878, <variable>.s32MaxPpsNum
	mov	ip, #2208	@ tmp227,
	mul	r1, r1, lr	@ D.52874, tmp222, <variable>.s32MaxSliceNum
	mla	lr, r3, r0, r1	@ tmp225, tmp224, D.52875, D.52874
	mla	r3, ip, r2, lr	@ TempAddMem, tmp227, D.52878, tmp225
	cmp	r3, #0	@ TempAddMem,
	movcc	r3, #0	@ TempAddMem,
	cmp	r7, #26	@ eCapLevel,
	beq	.L471	@,
.L458:
	cmp	r6, #5	@ D.52845,
	bhi	.L459	@,
	movw	lr, #:lower16:1718176	@ tmp234,
	movt	lr, #:upper16:1718176	@ tmp234,
	cmp	r3, lr	@ TempAddMem, tmp234
	movcc	r3, lr	@ TempAddMem, tmp234
.L459:
	add	r3, r3, sl	@ tmp235, TempAddMem, s32ChanCtxSize
	mov	r0, #0	@ D.52787,
	str	r3, [r5, #8]	@ tmp235, <variable>.ChanCtxDetailMem
	b	.L439	@
.L444:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC22	@,
	movt	r1, #:upper16:.LC22	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52787,
	b	.L439	@
.L467:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC20	@,
	movt	r1, #:upper16:.LC20	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52787,
	b	.L439	@
.L468:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC21	@,
	movt	r1, #:upper16:.LC21	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52787,
	b	.L439	@
.L465:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC18	@,
	movt	r1, #:upper16:.LC18	@,
	str	ip, [sp, #0]	@ D.52779,
	str	r9, [sp, #4]	@ extra_disp.643,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52787,
	b	.L439	@
.L469:
	ldr	r1, [r4, #20]	@ <variable>.s32MaxSliceNum, <variable>.s32MaxSliceNum
	cmp	r1, #0	@ <variable>.s32MaxSliceNum,
	ble	.L447	@,
.L463:
	ldr	ip, [r4, #28]	@ <variable>.s32MaxSpsNum, <variable>.s32MaxSpsNum
	cmp	ip, #0	@ <variable>.s32MaxSpsNum,
	ble	.L447	@,
	ldr	r1, [r4, #32]	@ <variable>.s32MaxPpsNum, <variable>.s32MaxPpsNum
	cmp	r1, #0	@ <variable>.s32MaxPpsNum,
	bgt	.L449	@,
.L447:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC23	@,
	movt	r1, #:upper16:.LC23	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52787,
	b	.L439	@
.L470:
	ldr	ip, [r4, #20]	@ <variable>.s32MaxSliceNum, <variable>.s32MaxSliceNum
	cmp	ip, #0	@ <variable>.s32MaxSliceNum,
	ble	.L447	@,
	ldr	r1, [r4, #24]	@ <variable>.s32MaxVpsNum, <variable>.s32MaxVpsNum
	cmp	r1, #0	@ <variable>.s32MaxVpsNum,
	bgt	.L463	@,
	b	.L447	@
.L471:
	movw	ip, #3992	@ tmp229,
	mla	r1, ip, r0, r1	@ tmp230, tmp229, D.52875, D.52874
	mov	r0, #2240	@ tmp232,
	mla	r2, r0, r2, r1	@ tmp233, tmp232, D.52878, tmp230
	cmp	r3, r2	@ TempAddMem, tmp233
	movcc	r3, r2	@ TempAddMem, tmp233
	b	.L458	@
.L454:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC24	@,
	movw	r2, #5950	@,
	movt	r1, #:upper16:.LC24	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52787,
	b	.L439	@
	.fnend
	.size	VCTRL_GetChanMemSizeWithOption, .-VCTRL_GetChanMemSizeWithOption
	.align	2
	.global	VCTRL_ConfigFFFBSpeed
	.type	VCTRL_ConfigFFFBSpeed, %function
VCTRL_ConfigFFFBSpeed:
	.fnstart
.LFB1594:
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
	cmp	r0, #15	@ ChanID,
	bhi	.L479	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r3, [r3, r0, asl #2]	@ D.52444, s_pstVfmwChan
	cmp	r3, #0	@ D.52444,
	beq	.L480	@,
	ldr	r2, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r2, #1	@ <variable>.s32IsOpen,
	bne	.L481	@,
	cmp	r1, #0	@ pArgs,
	beq	.L482	@,
	ldr	ip, [r1, #0]	@ tmp148,* pArgs
	mov	r0, #0	@ D.52442,
	str	ip, [r3, #1244]	@ tmp148, <variable>.stSynExtraData.s32FastForwardBackwardSpeed
	ldmfd	sp, {fp, sp, pc}	@
.L481:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #5012	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC26	@,
	movt	r3, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52442,
	ldmfd	sp, {fp, sp, pc}	@
.L479:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #5010	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52442,
	ldmfd	sp, {fp, sp, pc}	@
.L480:
	mov	r0, r3	@, D.52444
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #5011	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC25	@,
	movt	r3, #:upper16:.LC25	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52442,
	ldmfd	sp, {fp, sp, pc}	@
.L482:
	mov	r0, r1	@, pArgs
	movw	r2, #5013	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC27	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52442,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_ConfigFFFBSpeed, .-VCTRL_ConfigFFFBSpeed
	.align	2
	.global	VCTRL_GetChanMemInfo
	.type	VCTRL_GetChanMemInfo, %function
VCTRL_GetChanMemInfo:
	.fnstart
.LFB1589:
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
	cmp	r0, #15	@ ChanId,
	bhi	.L489	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp141,
	movt	r3, #:upper16:.LANCHOR0	@ tmp141,
	ldr	r0, [r3, r0, asl #2]	@ D.52209, s_pstVfmwChan
	cmp	r0, #0	@ D.52209,
	beq	.L490	@,
	cmp	r1, #0	@ pstMemRec,
	bne	.L491	@,
.L487:
	mvn	r0, #0	@ D.52207,
	ldmfd	sp, {fp, sp, pc}	@
.L490:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4627	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52207,
	ldmfd	sp, {fp, sp, pc}	@
.L491:
	ldr	r2, [r0, #196]	@ <variable>.s32OneChanMem, <variable>.s32OneChanMem
	cmp	r2, #1	@ <variable>.s32OneChanMem,
	bne	.L487	@,
	ldr	r3, [r0, #204]	@ D.52221, <variable>.stChanMem.VirAddr
	ldr	ip, [r0, #212]	@ <variable>.stChanMem.Length, <variable>.stChanMem.Length
	ldr	r2, [r0, #208]	@ <variable>.stChanMem.PhyAddr, <variable>.stChanMem.PhyAddr
	cmp	r3, #0	@ D.52221,
	str	r3, [r1, #4]	@ D.52221, <variable>.VirAddr
	str	ip, [r1, #12]	@ <variable>.stChanMem.Length, <variable>.Length
	movne	r0, #0	@ D.52207,
	str	r2, [r1, #8]	@ <variable>.stChanMem.PhyAddr, <variable>.PhyAddr
	ldmnefd	sp, {fp, sp, pc}	@
	b	.L487	@
.L489:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4626	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC28	@,
	movt	r3, #:upper16:.LC28	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52207,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetChanMemInfo, .-VCTRL_GetChanMemInfo
	.align	2
	.global	VCTRL_GetVidStd
	.type	VCTRL_GetVidStd, %function
VCTRL_GetVidStd:
	.fnstart
.LFB1586:
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
	cmp	r0, #15	@ ChanId,
	bhi	.L493	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	ldr	r3, [r3, r0, asl #2]	@ D.52107, s_pstVfmwChan
	cmp	r3, #0	@ D.52107,
	beq	.L493	@,
	ldr	r2, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r2, #1	@ <variable>.s32IsOpen,
	beq	.L496	@,
	mov	r3, r0	@, ChanId
	movw	r1, #:lower16:.LC30	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC30	@,
	movw	r2, #4447	@,
	bl	dprint_vfmw	@
	mov	r0, #19	@ D.52109,
	ldmfd	sp, {fp, sp, pc}	@
.L493:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC29	@,
	movw	r2, #4440	@,
	movt	r1, #:upper16:.LC29	@,
	bl	dprint_vfmw	@
	mov	r0, #19	@ D.52109,
	ldmfd	sp, {fp, sp, pc}	@
.L496:
	ldr	r0, [r3, #544]	@ D.52109, <variable>.eVidStd
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetVidStd, .-VCTRL_GetVidStd
	.align	2
	.global	VCTRL_CheckChanWH
	.type	VCTRL_CheckChanWH, %function
VCTRL_CheckChanWH:
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
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r2, #:lower16:g_chipID	@ tmp144,
	movt	r2, #:upper16:g_chipID	@ tmp144,
	movw	r3, #:lower16:.LANCHOR0	@ tmp143,
	movt	r3, #:upper16:.LANCHOR0	@ tmp143,
	ldr	ip, [r2, #0]	@ g_chipID.528, g_chipID
	ldr	r3, [r3, r0, asl #2]	@ D.51357, s_pstVfmwChan
	cmp	ip, #12	@ g_chipID.528,
	ldr	r0, [r3, #1300]	@ ChanMaxHeight, <variable>.stSynExtraData.stChanOption.s32MaxHeight
	ldr	r3, [r3, #1296]	@ ChanMaxWidth, <variable>.stSynExtraData.stChanOption.s32MaxWidth
	bgt	.L502	@,
	cmp	ip, #5	@ g_chipID.528,
	blt	.L509	@,
.L501:
	movw	r2, #:lower16:g_ChipMaxWidth	@ tmp152,
	movt	r2, #:upper16:g_ChipMaxWidth	@ tmp152,
	ldr	r2, [r2, #0]	@ g_ChipMaxWidth.2225, g_ChipMaxWidth
	cmp	r3, r2	@ ChanMaxWidth, g_ChipMaxWidth.2225
	ble	.L510	@,
	ldr	r3, [r1, #0]	@ D.51371, <variable>.eVidStd
	cmp	r3, #13	@ D.51371,
	cmpne	r3, #0	@, D.51371,
	beq	.L504	@,
.L515:
	cmp	r3, #15	@ D.51371,
	beq	.L504	@,
	cmp	r3, #18	@ D.51371,
	bne	.L511	@,
.L504:
	mov	r0, #0	@ ret,
	b	.L505	@
.L502:
	cmp	ip, #51	@ g_chipID.528,
	bge	.L512	@,
.L499:
	mov	r2, ip	@, g_chipID.528
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
.L505:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L509:
	cmp	ip, #0	@ g_chipID.528,
	blt	.L499	@,
	movw	r2, #:lower16:g_ChipMaxWidth	@ tmp146,
	movt	r2, #:upper16:g_ChipMaxWidth	@ tmp146,
	ldr	r2, [r2, #0]	@ g_ChipMaxWidth, g_ChipMaxWidth
	cmp	r3, r2	@ ChanMaxWidth, g_ChipMaxWidth
	ble	.L513	@,
	ldr	r0, [r1, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r0, #18	@ <variable>.eVidStd,
	beq	.L504	@,
.L514:
	mov	r2, ip	@, g_chipID.528
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC31	@,
	movt	r1, #:upper16:.LC31	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L505	@
.L512:
	cmp	ip, #52	@ g_chipID.528,
	ble	.L501	@,
	sub	r2, ip, #100	@ tmp145, g_chipID.528,
	cmp	r2, #1	@ tmp145,
	bhi	.L499	@,
	b	.L501	@
.L513:
	movw	r2, #:lower16:g_ChipMaxHeight	@ tmp148,
	movt	r2, #:upper16:g_ChipMaxHeight	@ tmp148,
	ldr	r3, [r2, #0]	@ g_ChipMaxHeight, g_ChipMaxHeight
	cmp	r0, r3	@ ChanMaxHeight, g_ChipMaxHeight
	ble	.L504	@,
	ldr	r0, [r1, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r0, #18	@ <variable>.eVidStd,
	beq	.L504	@,
	b	.L514	@
.L510:
	movw	r3, #:lower16:g_ChipMaxHeight	@ tmp153,
	movt	r3, #:upper16:g_ChipMaxHeight	@ tmp153,
	ldr	r3, [r3, #0]	@ g_ChipMaxHeight, g_ChipMaxHeight
	cmp	r0, r3	@ ChanMaxHeight, g_ChipMaxHeight
	ble	.L504	@,
	ldr	r3, [r1, #0]	@ D.51371, <variable>.eVidStd
	cmp	r3, #13	@ D.51371,
	cmpne	r3, #0	@, D.51371,
	bne	.L515	@,
	b	.L504	@
.L511:
	movw	r1, #:lower16:g_ChipMaxHeight	@ tmp163,
	movt	r1, #:upper16:g_ChipMaxHeight	@ tmp163,
	mov	r0, #0	@,
	ldr	r3, [r1, #0]	@ g_ChipMaxHeight, g_ChipMaxHeight
	movw	r1, #:lower16:.LC32	@,
	movt	r1, #:upper16:.LC32	@,
	str	ip, [sp, #0]	@ g_chipID.528,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L505	@
	.fnend
	.size	VCTRL_CheckChanWH, .-VCTRL_CheckChanWH
	.align	2
	.global	RefreshDecCore
	.type	RefreshDecCore, %function
RefreshDecCore:
	.fnstart
.LFB1575:
	@ args = 0, pretend = 0, frame = 8
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp167,
	movt	r4, #:upper16:.LANCHOR0	@ tmp167,
	mov	r5, r0	@ ChanID, ChanID
	ldr	r3, [r4, r0, asl #2]	@ D.51235, s_pstVfmwChan
	ldr	r2, [r3, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	ip, [r3, #1488]	@ eOldDecCore, <variable>.eDecCore
	cmp	r2, #4	@ <variable>.eVidStd,
	moveq	r2, #1	@ tmp148,
	streq	r2, [r3, #1488]	@ tmp148, <variable>.eDecCore
	beq	.L520	@,
	cmp	r2, #14	@ <variable>.eVidStd,
	movne	r2, #0	@ tmp150,
	strne	r2, [r3, #1488]	@ tmp150, <variable>.eDecCore
	moveq	r2, #2	@ tmp149,
	streq	r2, [r3, #1488]	@ tmp149, <variable>.eDecCore
.L520:
	ldr	r0, [r4, r5, asl #2]	@ prephitmp.2244, s_pstVfmwChan
	movw	r6, #:lower16:.LANCHOR0	@ tmp151,
	movt	r6, #:upper16:.LANCHOR0	@ tmp151,
	ldr	r2, [r0, #1488]	@ prephitmp.2246, <variable>.eDecCore
	cmp	r2, ip	@ prephitmp.2246, eOldDecCore
	beq	.L521	@,
	sub	ip, ip, #1	@ tmp152, eOldDecCore,
	cmp	ip, #4	@ tmp152,
	bhi	.L522	@,
	ldr	r3, [r6, #80]	@ D.51244, g_SdecFunc.pfun_iMediaSoftDEC_Destroy
	cmp	r3, #0	@ D.51244,
	beq	.L522	@,
	add	r0, r0, #250880	@, prephitmp.2244,
	str	r1, [fp, #-32]	@,
	add	r0, r0, #704	@,,
	blx	r3	@ D.51244
	ldr	r0, [r6, r5, asl #2]	@ prephitmp.2244, s_pstVfmwChan
	ldr	r1, [fp, #-32]	@,
	ldr	r2, [r0, #1488]	@ prephitmp.2246, <variable>.eDecCore
.L522:
	sub	r3, r2, #1	@ tmp157, prephitmp.2246,
	cmp	r3, #4	@ tmp157,
	bhi	.L521	@,
	ldr	ip, [r0, #40]	@ <variable>.eChanCapLevel, <variable>.eChanCapLevel
	movw	lr, #:lower16:251596	@ tmp158,
	movt	lr, #:upper16:251596	@ tmp158,
	movw	r2, #:lower16:.LANCHOR0	@ tmp160,
	movt	r2, #:upper16:.LANCHOR0	@ tmp160,
	str	ip, [r0, lr]	@ <variable>.eChanCapLevel, <variable>.stSynCtx.unSyntax.stiMediaSoftCtx.eChanCapLevel
	ldr	r3, [r4, #76]	@ D.51256, g_SdecFunc.pfun_iMediaSoftDEC_Create
	cmp	r3, #0	@ D.51256,
	beq	.L523	@,
	ldr	r2, [r2, r5, asl #2]	@ temp.2257, s_pstVfmwChan
	add	r0, r2, #250880	@, temp.2257,
	add	r0, r0, #704	@,,
	ldr	r2, [r2, #544]	@, <variable>.eVidStd
	blx	r3	@ D.51256
	cmp	r0, #0	@,
	bne	.L523	@,
.L521:
	mov	r0, #0	@ D.51260,
.L524:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L523:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC34	@,
	movt	r1, #:upper16:.LC34	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51260,
	b	.L524	@
	.fnend
	.size	RefreshDecCore, .-RefreshDecCore
	.align	2
	.global	VCTRL_GetSendStreamAgainFlag
	.type	VCTRL_GetSendStreamAgainFlag, %function
VCTRL_GetSendStreamAgainFlag:
	.fnstart
.LFB1552:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	ldr	r0, [r3, r0, asl #2]	@ D.50258, s_pstVfmwChan
	cmp	r0, #0	@ D.50258,
	beq	.L531	@,
	movw	r1, #:lower16:249284	@ tmp140,
	movt	r1, #:upper16:249284	@ tmp140,
	ldr	r0, [r0, r1]	@ D.50262, <variable>.s32SendStreamAgainFlag
	ldmfd	sp, {fp, sp, pc}	@
.L531:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1062	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50262,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetSendStreamAgainFlag, .-VCTRL_GetSendStreamAgainFlag
	.align	2
	.global	VCTRL_SetSendStreamAgainFlag
	.type	VCTRL_SetSendStreamAgainFlag, %function
VCTRL_SetSendStreamAgainFlag:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp138,
	movt	r3, #:upper16:.LANCHOR0	@ tmp138,
	ldr	r2, [r3, r0, asl #2]	@ D.50249, s_pstVfmwChan
	cmp	r2, #0	@ D.50249,
	beq	.L536	@,
	movw	ip, #:lower16:249284	@ tmp141,
	movt	ip, #:upper16:249284	@ tmp141,
	mov	r0, #0	@ D.50253,
	str	r1, [r2, ip]	@ flag, <variable>.s32SendStreamAgainFlag
	ldmfd	sp, {fp, sp, pc}	@
.L536:
	mov	r0, r2	@, D.50249
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1055	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50253,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_SetSendStreamAgainFlag, .-VCTRL_SetSendStreamAgainFlag
	.align	2
	.global	VCTRL_SetCallBack
	.type	VCTRL_SetCallBack, %function
VCTRL_SetCallBack:
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
	cmp	r1, #0	@ event_report
	beq	.L545	@,
	cmp	r0, #0	@ eType,
	movweq	r3, #:lower16:.LANCHOR0	@ tmp139,
	movteq	r3, #:upper16:.LANCHOR0	@ tmp139,
	streq	r1, [r3, #288]	@ event_report, s_VfmwCTrl.event_report_vdec
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #1	@ eType,
	beq	.L546	@,
	mov	r3, r0	@, eType
	ldr	r2, .L547	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC36	@,
	movt	r1, #:upper16:.LC36	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50118,
	ldmfd	sp, {fp, sp, pc}	@
.L546:
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	mov	r0, #0	@ D.50118,
	str	r1, [r3, #292]	@ event_report, s_VfmwCTrl.event_report_omxvdec
	ldmfd	sp, {fp, sp, pc}	@
.L545:
	mov	r0, r1	@, event_report
	movw	r2, #770	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC35	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC35	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50118,
	ldmfd	sp, {fp, sp, pc}	@
.L548:
	.align	2
.L547:
	.word	.LANCHOR1+40
	.fnend
	.size	VCTRL_SetCallBack, .-VCTRL_SetCallBack
	.align	2
	.global	VCTRL_EventReport
	.type	VCTRL_EventReport, %function
VCTRL_EventReport:
	.fnstart
.LFB1544:
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
	cmp	r0, #15	@ InstID,
	mov	lr, r3	@ len, len
	bhi	.L560	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp145,
	movt	r4, #:upper16:.LANCHOR0	@ tmp145,
	ldr	r3, [r4, r0, asl #2]	@ D.50087, s_pstVfmwChan
	cmp	r3, #0	@ D.50087,
	beq	.L561	@,
	ldr	r3, [r3, #36]	@ eType, <variable>.eAdapterType
	cmp	r3, #0	@ eType,
	beq	.L554	@,
	cmp	r3, #1	@ eType,
	beq	.L562	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC40	@,
	ldr	r2, .L564	@,
	movt	r1, #:upper16:.LC40	@,
	str	lr, [sp, #0]	@ len,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
.L551:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L554:
	ldr	r3, [r4, #288]	@ D.50090, s_VfmwCTrl.event_report_vdec
	cmp	r3, #0	@ D.50090,
	beq	.L563	@,
.L557:
	blx	r3	@ D.50096
	b	.L551	@
.L562:
	ldr	r3, [r4, #292]	@ D.50096, s_VfmwCTrl.event_report_omxvdec
	cmp	r3, #0	@ D.50096,
	bne	.L557	@,
	mov	r0, r3	@, D.50096
	movw	r1, #:lower16:.LC39	@,
	movt	r1, #:upper16:.LC39	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L551	@
.L563:
	mov	r0, r3	@, D.50090
	movw	r1, #:lower16:.LC38	@,
	movt	r1, #:upper16:.LC38	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L551	@
.L560:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #734	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC37	@,
	movt	r3, #:upper16:.LC37	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L551	@
.L561:
	mov	r0, r3	@, D.50087
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #735	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L551	@
.L565:
	.align	2
.L564:
	.word	.LANCHOR1+60
	.fnend
	.size	VCTRL_EventReport, .-VCTRL_EventReport
	.align	2
	.global	VCTRL_SetMoreGapEnable
	.type	VCTRL_SetMoreGapEnable, %function
VCTRL_SetMoreGapEnable:
	.fnstart
.LFB1543:
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
	cmp	r0, #15	@ ChanID,
	bhi	.L573	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r3, [r3, r0, asl #2]	@ D.50058, s_pstVfmwChan
	cmp	r3, #0	@ D.50058,
	beq	.L574	@,
	ldr	r2, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r2, #1	@ <variable>.s32IsOpen,
	bne	.L575	@,
	cmp	r1, #1	@ MoreGapEnable,
	strls	r1, [r3, #1240]	@ MoreGapEnable, <variable>.stSynExtraData.s32MoreGapEnable
	movhi	r2, #0	@ tmp146,
	movls	r0, #0	@ D.50056,
	mvnhi	r0, #0	@ D.50056,
	strhi	r2, [r3, #1240]	@ tmp146, <variable>.stSynExtraData.s32MoreGapEnable
	ldmfd	sp, {fp, sp, pc}	@
.L575:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #714	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC41	@,
	movt	r3, #:upper16:.LC41	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50056,
	ldmfd	sp, {fp, sp, pc}	@
.L573:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	mov	r2, #712	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50056,
	ldmfd	sp, {fp, sp, pc}	@
.L574:
	mov	r0, r3	@, D.50058
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #713	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50056,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_SetMoreGapEnable, .-VCTRL_SetMoreGapEnable
	.align	2
	.global	VCTRL_RegisterSoftDecoder
	.type	VCTRL_RegisterSoftDecoder, %function
VCTRL_RegisterSoftDecoder:
	.fnstart
.LFB1528:
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
	ldr	r3, [r0, #0]	@ <variable>.pfun_iMediaSoftDEC_Create, <variable>.pfun_iMediaSoftDEC_Create
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_Create,
	beq	.L586	@,
	ldr	r3, [r0, #4]	@ <variable>.pfun_iMediaSoftDEC_Destroy, <variable>.pfun_iMediaSoftDEC_Destroy
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_Destroy,
	beq	.L587	@,
	ldr	r3, [r0, #8]	@ <variable>.pfun_iMediaSoftDEC_Init, <variable>.pfun_iMediaSoftDEC_Init
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_Init,
	beq	.L588	@,
	ldr	r3, [r0, #12]	@ <variable>.pfun_iMediaSoftDEC_Decode, <variable>.pfun_iMediaSoftDEC_Decode
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_Decode,
	beq	.L589	@,
	ldr	r3, [r0, #16]	@ <variable>.pfun_iMediaSoftDEC_RecycleImage, <variable>.pfun_iMediaSoftDEC_RecycleImage
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_RecycleImage,
	beq	.L590	@,
	ldr	r3, [r0, #20]	@ <variable>.pfun_iMediaSoftDEC_GetRemainImg, <variable>.pfun_iMediaSoftDEC_GetRemainImg
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_GetRemainImg,
	beq	.L591	@,
	ldr	r3, [r0, #24]	@ <variable>.pfun_iMediaSoftDEC_GetImageBuffer, <variable>.pfun_iMediaSoftDEC_GetImageBuffer
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_GetImageBuffer,
	beq	.L592	@,
	mov	r4, r0	@ pstSdecFunc, pstSdecFunc
	ldr	ip, .L593	@ tmp158,
	ldmia	r4!, {r0, r1, r2, r3}	@ pstSdecFunc,,,,
	mov	r5, #0	@ D.49771,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp158,,,,
	ldmia	r4, {r0, r1, r2}	@ pstSdecFunc,,,
	stmia	ip, {r0, r1, r2}	@ tmp161,,,
.L578:
	mov	r0, r5	@, D.49771
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L586:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_Create
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC43	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC43	@,
	mvn	r5, #0	@ D.49771,
	bl	dprint_vfmw	@
	b	.L578	@
.L591:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_GetRemainImg
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC48	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC48	@,
	mvn	r5, #0	@ D.49771,
	bl	dprint_vfmw	@
	b	.L578	@
.L590:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_RecycleImage
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC47	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC47	@,
	mvn	r5, #0	@ D.49771,
	bl	dprint_vfmw	@
	b	.L578	@
.L589:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_Decode
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC46	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC46	@,
	mvn	r5, #0	@ D.49771,
	bl	dprint_vfmw	@
	b	.L578	@
.L588:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_Init
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC45	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC45	@,
	mvn	r5, #0	@ D.49771,
	bl	dprint_vfmw	@
	b	.L578	@
.L587:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_Destroy
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC44	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC44	@,
	mvn	r5, #0	@ D.49771,
	bl	dprint_vfmw	@
	b	.L578	@
.L592:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_GetImageBuffer
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC49	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC49	@,
	mvn	r5, #0	@ D.49771,
	bl	dprint_vfmw	@
	b	.L578	@
.L594:
	.align	2
.L593:
	.word	.LANCHOR0+76
	.fnend
	.size	VCTRL_RegisterSoftDecoder, .-VCTRL_RegisterSoftDecoder
	.align	2
	.global	VCTRL_ConfigPVRInfo
	.type	VCTRL_ConfigPVRInfo, %function
VCTRL_ConfigPVRInfo:
	.fnstart
.LFB1595:
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
	cmp	r0, #15	@ ChanID,
	bhi	.L602	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	ip, [r3, r0, asl #2]	@ D.52463, s_pstVfmwChan
	cmp	ip, #0	@ D.52463,
	beq	.L603	@,
	ldr	r0, [ip, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r0, #1	@ <variable>.s32IsOpen,
	bne	.L604	@,
	cmp	r1, #0	@ pArgs,
	beq	.L605	@,
	mov	r4, r1	@ pArgs, pArgs
	add	ip, ip, #1264	@ tmp148, D.52463,
	ldmia	r4!, {r0, r1, r2, r3}	@ pArgs,,,,
	mov	r5, #0	@ D.52461,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp148,,,,
	ldr	r2, [r4, #0]	@ tmp151,* pArgs
	str	r2, [ip, #0]	@ tmp151, <variable>.stSynExtraData.stPvrInfo
.L597:
	mov	r0, r5	@, D.52461
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L604:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #5025	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC26	@,
	movt	r3, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ D.52461,
	b	.L597	@
.L602:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #5023	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ D.52461,
	b	.L597	@
.L605:
	mov	r0, r1	@, pArgs
	movw	r2, #5026	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC27	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ D.52461,
	b	.L597	@
.L603:
	mov	r0, ip	@, D.52463
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #5024	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC25	@,
	movt	r3, #:upper16:.LC25	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ D.52461,
	b	.L597	@
	.fnend
	.size	VCTRL_ConfigPVRInfo, .-VCTRL_ConfigPVRInfo
	.align	2
	.global	VCTRL_GetChanCfg
	.type	VCTRL_GetChanCfg, %function
VCTRL_GetChanCfg:
	.fnstart
.LFB1574:
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
	cmp	r0, #15	@ ChanID,
	bhi	.L612	@,
	cmp	r1, #0	@ pstCfg,
	beq	.L613	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp142,
	movt	r3, #:upper16:.LANCHOR0	@ tmp142,
	ldr	r3, [r3, r0, asl #2]	@ D.51221, s_pstVfmwChan
	cmp	r3, #0	@ D.51221,
	beq	.L614	@,
	mov	r0, r1	@, pstCfg
	mov	r2, #100	@,
	add	r1, r3, #48	@, D.51221,
	bl	memcpy	@
	mov	r0, #0	@ D.51217,
	ldmfd	sp, {fp, sp, pc}	@
.L612:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2878	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51217,
	ldmfd	sp, {fp, sp, pc}	@
.L614:
	mov	r0, r3	@, D.51221
	movw	r1, #:lower16:.LC5	@,
	mov	r2, #2880	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51217,
	ldmfd	sp, {fp, sp, pc}	@
.L613:
	mov	r0, r1	@, pstCfg
	movw	r2, #2879	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC50	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC50	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51217,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetChanCfg, .-VCTRL_GetChanCfg
	.align	2
	.global	VCTRL_SetDiscardPicParam
	.type	VCTRL_SetDiscardPicParam, %function
VCTRL_SetDiscardPicParam:
	.fnstart
.LFB1557:
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
	cmp	r0, #15	@ ChanID,
	mov	ip, r0	@ ChanID, ChanID
	bhi	.L622	@,
	cmp	r1, #0	@ pArgs,
	beq	.L623	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp143,
	movt	r3, #:upper16:.LANCHOR0	@ tmp143,
	ldr	r2, [r3, r0, asl #2]	@ D.50332, s_pstVfmwChan
	cmp	r2, #0	@ D.50332,
	beq	.L624	@,
	ldmia	r1, {r0, r1}	@ pArgs,,
	add	r2, r2, #1440	@ tmp146, D.50332,
	add	r2, r2, #8	@ tmp146, tmp146,
	stmia	r2, {r0, r1}	@ tmp146,,
	ldr	r3, [r3, ip, asl #2]	@ temp.2483, s_pstVfmwChan
	ldr	r0, [r3, #1448]	@ <variable>.stSynExtraData.stDisParams.s32Mode, <variable>.stSynExtraData.stDisParams.s32Mode
	sub	r2, r0, #1	@ tmp151, <variable>.stSynExtraData.stDisParams.s32Mode,
	mov	r0, #0	@ D.50328,
	cmp	r2, #1	@ tmp151,
	strhi	r0, [r3, #1448]	@ tmp153, <variable>.stSynExtraData.stDisParams.s32Mode
	ldmfd	sp, {fp, sp, pc}	@
.L622:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1140	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50328,
	ldmfd	sp, {fp, sp, pc}	@
.L624:
	mov	r0, r2	@, D.50332
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1142	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50328,
	ldmfd	sp, {fp, sp, pc}	@
.L623:
	mov	r0, r1	@, pArgs
	movw	r2, #1141	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50328,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_SetDiscardPicParam, .-VCTRL_SetDiscardPicParam
	.align	2
	.global	VCTRL_SetFrameInterface
	.type	VCTRL_SetFrameInterface, %function
VCTRL_SetFrameInterface:
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
	cmp	r1, #0	@ pstFrameIntf
	beq	.L630	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r3, [r3, r0, asl #2]	@ D.50288, s_pstVfmwChan
	cmp	r3, #0	@ D.50288,
	beq	.L631	@,
	ldmia	r1, {r0, r1, r2}	@ pstFrameIntf,,,
	add	r3, r3, #172	@ tmp143, D.50288,
	mov	ip, #0	@ D.50286,
	stmia	r3, {r0, r1, r2}	@ tmp143,,,
.L627:
	mov	r0, ip	@, D.50286
	ldmfd	sp, {fp, sp, pc}	@
.L631:
	mov	r0, r3	@, D.50288
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1090	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	ip, #0	@ D.50286,
	b	.L627	@
.L630:
	mov	r0, r1	@, pstFrameIntf
	movw	r2, #1089	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	mvn	ip, #0	@ D.50286,
	b	.L627	@
	.fnend
	.size	VCTRL_SetFrameInterface, .-VCTRL_SetFrameInterface
	.align	2
	.global	VCTRL_SetStreamInterface
	.type	VCTRL_SetStreamInterface, %function
VCTRL_SetStreamInterface:
	.fnstart
.LFB1550:
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
	subs	r6, r1, #0	@ pstStreamParam, pstStreamParam
	mov	r5, r0	@ ChanID, ChanID
	beq	.L637	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp140,
	movt	r4, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r0, [r4, r0, asl #2]	@ D.50237, s_pstVfmwChan
	cmp	r0, #0	@ D.50237,
	beq	.L638	@,
	add	r5, r5, r5, asl #1	@, tmp152, ChanID, ChanID,
	mov	r2, #12	@,
	add	r4, r4, #312	@ tmp149, tmp140,
	add	r0, r0, #148	@, D.50237,
	bl	memcpy	@
	mov	r1, r6	@, pstStreamParam
	add	r0, r4, r5, asl #2	@,, tmp149, tmp152,
	mov	r2, #12	@,
	bl	memcpy	@
	mov	r0, #0	@ D.50235,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L638:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1046	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50235,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L637:
	mov	r0, r6	@, pstStreamParam
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1045	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC53	@,
	movt	r3, #:upper16:.LC53	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50235,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VCTRL_SetStreamInterface, .-VCTRL_SetStreamInterface
	.align	2
	.global	DBG_WriteBigTileYuv
	.type	DBG_WriteBigTileYuv, %function
DBG_WriteBigTileYuv:
	.fnstart
.LFB1667:
	@ args = 32, pretend = 0, frame = 40
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
	cmp	r0, #0	@
	mov	r5, r1	@ Yaddress, Yaddress
	str	r0, [fp, #-64]	@, %sfp
	str	r2, [fp, #-76]	@ Caddress, %sfp
	mov	r4, r3	@ Width, Width
	ldr	r6, [fp, #8]	@ PicStructure, PicStructure
	beq	.L676	@,
	ldr	ip, [fp, #20]	@, LeftOffset
	ldr	r1, [fp, #4]	@, Height
	ldr	r0, [fp, #28]	@, TopOffset
	rsb	r2, ip, r3	@ tmp211,, Width
	ldr	r3, [fp, #32]	@ BottomOffset, BottomOffset
	mov	ip, r4, lsr #1	@, Width,
	rsb	r8, r0, r1	@ tmp212,,
	ldr	lr, [fp, #24]	@ RightOffset, RightOffset
	rsb	r8, r3, r8	@, BottomOffset, tmp212
	mov	r0, #32	@,
	rsb	r2, lr, r2	@, RightOffset, tmp211
	movw	r1, #:lower16:.LC54	@,
	mov	r3, r8	@,
	movt	r1, #:upper16:.LC54	@,
	str	r2, [fp, #-72]	@, %sfp
	str	r8, [fp, #-60]	@, %sfp
	str	ip, [fp, #-68]	@, %sfp
	bl	dprint_vfmw	@
	ldr	r0, [fp, #4]	@, Height
	cmp	r6, #0	@ PicStructure,
	cmpne	r6, #3	@, PicStructure,
	mov	r1, r0, lsr #1	@,,
	str	r1, [fp, #-56]	@, %sfp
	bne	.L641	@,
	ldr	sl, [fp, #4]	@, Height
	cmp	sl, #0	@,
	movweq	r6, #:lower16:.LANCHOR0	@ tmp334,
	movteq	r6, #:upper16:.LANCHOR0	@ tmp334,
	beq	.L642	@,
	movw	r6, #:lower16:.LANCHOR0	@ tmp334,
	movt	r6, #:upper16:.LANCHOR0	@ tmp334,
	mov	r8, r5	@ Yaddress, Yaddress
	mov	r9, r4	@ Width, Width
	mov	sl, #0	@ ivtmp.2654,
	str	sl, [fp, #-48]	@ ivtmp.2654, %sfp
.L643:
	cmp	r9, #0	@ Width,
	beq	.L645	@,
	ldr	r1, [fp, #-48]	@, %sfp
	sub	r4, r9, #1	@ tmp373, Width,
	ldr	r2, [fp, #12]	@, Stride
	ubfx	r5, r4, #8, #1	@ tmp374, tmp373,,
	and	lr, r1, #15	@ pretmp.2751,,
	ldr	ip, [r6, #504]	@ pY, pY
	mov	r0, r1, lsr #4	@ pretmp.2754,,
	mul	r7, r2, r0	@ tmp234,, pretmp.2754
	mov	r2, #256	@,
	mla	r7, lr, r2, r7	@ pretmp.2596, pretmp.2751,, tmp234
	add	r0, sl, ip	@, ivtmp.2654, pY
	mov	r4, r2	@ j,
	add	r1, r8, r7	@, Yaddress, pretmp.2596
	bl	memcpy	@
	cmp	r9, r4	@ Width, j
	bls	.L645	@,
	cmp	r5, #0	@ tmp374,
	beq	.L644	@,
	ldr	r5, [r6, #504]	@ pY, pY
	add	ip, sl, r4	@ tmp515, ivtmp.2654, j
	add	lr, r7, #4096	@ tmp520, pretmp.2596,
	mov	r2, r4	@, j
	add	r0, ip, r5	@, tmp515, pY
	add	r1, r8, lr	@, Yaddress, tmp520
	bl	memcpy	@
	mov	r4, #512	@ j,
	cmp	r9, r4	@ Width, j
	bls	.L645	@,
.L644:
	mov	r1, r4, lsr #8	@ tmp225, j,
	ldr	r2, [r6, #504]	@ pY, pY
	add	r5, r4, #256	@ tmp375, j,
	add	ip, sl, r4	@ tmp222, ivtmp.2654, j
	add	lr, r7, r1, asl #12	@, tmp227, pretmp.2596, tmp225,
	add	r0, ip, r2	@, tmp222, pY
	add	r1, r8, lr	@, Yaddress, tmp227
	mov	r2, #256	@,
	mov	r4, r5, lsr #8	@ tmp400, tmp375,
	bl	memcpy	@
	ldr	r3, [r6, #504]	@ pY, pY
	add	r0, sl, r5	@ tmp397, ivtmp.2654, tmp375
	add	r2, r7, r4, asl #12	@, tmp402, pretmp.2596, tmp400,
	add	r4, r5, #256	@ j, tmp375,
	add	r1, r8, r2	@, Yaddress, tmp402
	add	r0, r0, r3	@, tmp397, pY
	mov	r2, #256	@,
	bl	memcpy	@
	cmp	r9, r4	@ Width, j
	bhi	.L644	@,
.L645:
	ldr	r3, [fp, #-48]	@, %sfp
	add	sl, sl, r9	@ ivtmp.2654, ivtmp.2654, Width
	ldr	r5, [fp, #4]	@, Height
	add	r0, r3, #1	@,,
	str	r0, [fp, #-48]	@, %sfp
	cmp	r5, r0	@,
	bhi	.L643	@,
	mov	r4, r9	@ Width, Width
.L642:
	ldr	r3, [fp, #-60]	@, %sfp
	ldr	ip, [fp, #4]	@, Height
	ldr	r5, [fp, #-72]	@, %sfp
	cmp	r3, ip	@,
	cmpeq	r5, r4	@,, Width
	movne	sl, #0	@,
	moveq	sl, #1	@,
	str	sl, [fp, #-80]	@, %sfp
	beq	.L770	@,
	ldr	r2, [fp, #-60]	@, %sfp
	ldr	r0, [r6, #504]	@ pY.2693, pY
	cmp	r2, #0	@,
	beq	.L649	@,
	ldr	r1, [fp, #28]	@, TopOffset
	sub	r7, r2, #1	@ tmp367,,
	ldr	r8, [fp, #20]	@, LeftOffset
	ldr	r2, [fp, #-64]	@, %sfp
	mla	sl, r4, r1, r8	@ tmp245, Width,,
	ldr	r1, [fp, #-72]	@, %sfp
	and	r8, r7, #1	@ tmp369, tmp367,
	mov	r7, #1	@ i.2694,
	add	r0, r0, sl	@ pPicAddr, pY.2693, tmp245
	add	r5, r0, r4	@ pPicAddr, pPicAddr, Width
	bl	klib_fwrite	@
	ldr	r2, [fp, #-60]	@, %sfp
	cmp	r2, r7	@,
	bls	.L649	@,
	cmp	r8, #0	@ tmp369,
	beq	.L758	@,
	mov	r0, r5	@, pPicAddr
	ldr	r1, [fp, #-72]	@, %sfp
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r7, #2	@ i.2694,
	bl	klib_fwrite	@
	ldr	sl, [fp, #-60]	@, %sfp
	add	r5, r5, r4	@ pPicAddr, pPicAddr, Width
	cmp	sl, r7	@, i.2694
	bls	.L649	@,
.L758:
	mov	r0, r5	@ pPicAddr, pPicAddr
	ldr	r8, [fp, #-72]	@ disp_width, %sfp
	ldr	sl, [fp, #-64]	@ fpYuv, %sfp
	mov	r9, r6	@ tmp334, tmp334
	ldr	r5, [fp, #-60]	@ disp_height, %sfp
.L650:
	add	r6, r0, r4	@ pPicAddr, pPicAddr, Width
	add	r3, r7, #1	@ tmp370, i.2694,
	mov	r1, r8	@, disp_width
	mov	r2, sl	@, fpYuv
	add	r7, r3, #1	@ i.2694, tmp370,
	bl	klib_fwrite	@
	mov	r0, r6	@, pPicAddr
	mov	r1, r8	@, disp_width
	mov	r2, sl	@, fpYuv
	bl	klib_fwrite	@
	cmp	r5, r7	@ disp_height, i.2694
	add	r0, r6, r4	@ pPicAddr, pPicAddr, Width
	bhi	.L650	@,
	mov	r6, r9	@ tmp334, tmp334
.L649:
	ldr	lr, [fp, #-56]	@, %sfp
	cmp	lr, #0	@,
	beq	.L647	@,
	ldr	r0, [fp, #12]	@, Stride
	mov	r9, r4	@ Width, Width
	ldr	sl, [fp, #-76]	@ Caddress, %sfp
	mov	r8, #0	@ ivtmp.2642,
	str	r8, [fp, #-48]	@ i.2700, %sfp
	mov	ip, r0, lsr #1	@,,
	str	ip, [fp, #-52]	@, %sfp
.L648:
	cmp	r9, #0	@ Width,
	beq	.L652	@,
	ldr	r1, [fp, #-48]	@, %sfp
	sub	ip, r9, #1	@ tmp364, Width,
	ldr	lr, [fp, #-52]	@, %sfp
	mov	r2, #256	@,
	and	r0, r1, #7	@ pretmp.2749,,
	ldr	r3, [r6, #504]	@ pY, pY
	mov	r4, r1, lsr #3	@ pretmp.2593,,
	ubfx	r5, ip, #8, #1	@ tmp365, tmp364,,
	mov	r7, r0, asl #8	@ tmp259, pretmp.2749,
	add	r0, r8, r3	@, ivtmp.2642, pY
	mla	r7, lr, r4, r7	@ pretmp.2594,, pretmp.2593, tmp259
	mov	r4, r2	@ j.2699,
	add	r1, sl, r7	@, Caddress, pretmp.2594
	bl	memcpy	@
	cmp	r9, r4	@ Width, j.2699
	bls	.L652	@,
	cmp	r5, #0	@ tmp365,
	beq	.L651	@,
	ldr	r3, [r6, #504]	@ pY, pY
	add	r1, r8, r4	@ tmp508, ivtmp.2642, j.2699
	add	r5, r7, #2048	@ tmp513, pretmp.2594,
	mov	r2, r4	@, j.2699
	add	r0, r1, r3	@, tmp508, pY
	add	r1, sl, r5	@, Caddress, tmp513
	bl	memcpy	@
	mov	r4, #512	@ j.2699,
	cmp	r9, r4	@ Width, j.2699
	bls	.L652	@,
.L651:
	mov	r1, r4, lsr #8	@ tmp250, j.2699,
	ldr	r3, [r6, #504]	@ pY, pY
	add	r5, r4, #256	@ tmp366, j.2699,
	add	ip, r8, r4	@ tmp247, ivtmp.2642, j.2699
	add	lr, r7, r1, asl #11	@, tmp252, pretmp.2594, tmp250,
	add	r0, ip, r3	@, tmp247, pY
	add	r1, sl, lr	@, Caddress, tmp252
	mov	r2, #256	@,
	mov	r4, r5, lsr #8	@ tmp420, tmp366,
	bl	memcpy	@
	ldr	r2, [r6, #504]	@ pY, pY
	add	r0, r8, r5	@ tmp417, ivtmp.2642, tmp366
	add	ip, r7, r4, asl #11	@, tmp422, pretmp.2594, tmp420,
	add	r4, r5, #256	@ j.2699, tmp366,
	add	r0, r0, r2	@, tmp417, pY
	add	r1, sl, ip	@, Caddress, tmp422
	mov	r2, #256	@,
	bl	memcpy	@
	cmp	r9, r4	@ Width, j.2699
	bhi	.L651	@,
.L652:
	ldr	r5, [fp, #-48]	@, %sfp
	add	r8, r8, r9	@ ivtmp.2642, ivtmp.2642, Width
	ldr	r2, [fp, #-56]	@, %sfp
	add	r0, r5, #1	@,,
	str	r0, [fp, #-48]	@, %sfp
	cmp	r2, r0	@,
	bhi	.L648	@,
	mov	r4, r9	@ Width, Width
.L647:
	ldr	sl, [fp, #16]	@, chroma_idc
	movw	r5, #:lower16:.LANCHOR0	@ tmp260,
	movt	r5, #:upper16:.LANCHOR0	@ tmp260,
	cmp	sl, #1	@,
	ldr	sl, [r6, #504]	@ tmp, pY
	beq	.L771	@,
	ldr	r1, [fp, #16]	@, chroma_idc
	cmp	r1, #0	@,
	beq	.L772	@,
.L654:
	ldr	r2, [fp, #-80]	@, %sfp
	cmp	r2, #0	@,
	bne	.L773	@,
	ldr	r9, [fp, #-60]	@, %sfp
	ldr	r3, [r6, #512]	@ pUl.2706, pUl
	movs	r8, r9, lsr #1	@ disp_chroma_height,,
	ldr	r9, [r6, #508]	@ pVl.2707, pVl
	beq	.L676	@,
	ldr	r4, [fp, #28]	@, TopOffset
	sub	r6, r8, #1	@ tmp353, disp_chroma_height,
	ldr	r0, [fp, #20]	@, LeftOffset
	ldr	sl, [fp, #-72]	@, %sfp
	ldr	lr, [fp, #-68]	@, %sfp
	mov	r5, r4, lsr #1	@ tmp279,,
	mov	r7, r0, lsr #1	@ tmp281,,
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r4, sl, lsr #1	@ pretmp.2590,,
	mla	sl, lr, r5, r7	@ D.55963,, tmp279, tmp281
	mov	r1, r4	@, pretmp.2590
	and	r7, r6, #1	@ tmp355, tmp353,
	mov	r6, #1	@ i.2708,
	add	r0, r3, sl	@ pCbPicAddr, pUl.2706, D.55963
	add	r5, r0, lr	@ pCbPicAddr, pCbPicAddr,
	bl	klib_fwrite	@
	cmp	r8, r6	@ disp_chroma_height,
	bls	.L741	@,
	cmp	r7, #0	@ tmp355,
	beq	.L752	@,
	mov	r0, r5	@, pCbPicAddr
	mov	r1, r4	@, pretmp.2590
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r6, #2	@ i.2708,
	bl	klib_fwrite	@
	ldr	r7, [fp, #-68]	@, %sfp
	cmp	r8, r6	@ disp_chroma_height, i.2708
	add	r5, r5, r7	@ pCbPicAddr, pCbPicAddr,
	bls	.L741	@,
.L752:
	str	r9, [fp, #-48]	@ pVl.2707, %sfp
	mov	r0, r5	@ pCbPicAddr, pCbPicAddr
	ldr	r9, [fp, #-68]	@ chrom_width, %sfp
	mov	r5, sl	@ D.55963, D.55963
	ldr	sl, [fp, #-64]	@ fpYuv, %sfp
.L659:
	add	r7, r0, r9	@ pCbPicAddr, pCbPicAddr, chrom_width
	add	r3, r6, #1	@ tmp356, i.2708,
	mov	r1, r4	@, pretmp.2590
	mov	r2, sl	@, fpYuv
	add	r6, r3, #1	@ i.2708, tmp356,
	bl	klib_fwrite	@
	mov	r0, r7	@, pCbPicAddr
	mov	r1, r4	@, pretmp.2590
	mov	r2, sl	@, fpYuv
	bl	klib_fwrite	@
	cmp	r8, r6	@ disp_chroma_height, i.2708
	add	r0, r7, r9	@ pCbPicAddr, pCbPicAddr, chrom_width
	bhi	.L659	@,
	ldr	r9, [fp, #-48]	@ pVl.2707, %sfp
	mov	sl, r5	@ D.55963, D.55963
.L741:
	add	r6, r9, sl	@ pCrPicAddr, pVl.2707, D.55963
	sub	ip, r8, #1	@ tmp349, disp_chroma_height,
	mov	r1, r4	@, pretmp.2590
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r0, r6	@, pCrPicAddr
	and	r7, ip, #1	@ tmp351, tmp349,
	bl	klib_fwrite	@
	ldr	r1, [fp, #-68]	@, %sfp
	cmp	r8, #1	@ disp_chroma_height,
	add	r5, r6, r1	@ pCrPicAddr, pCrPicAddr,
	mov	r6, #1	@ i.2703,
	bls	.L676	@,
	cmp	r7, #0	@ tmp351,
	beq	.L750	@,
	mov	r0, r5	@, pCrPicAddr
	mov	r1, r4	@, pretmp.2590
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r6, #2	@ i.2703,
	bl	klib_fwrite	@
	ldr	r0, [fp, #-68]	@, %sfp
	cmp	r8, r6	@ disp_chroma_height, i.2703
	add	r5, r5, r0	@ pCrPicAddr, pCrPicAddr,
	bls	.L676	@,
.L750:
	ldr	r9, [fp, #-68]	@ chrom_width, %sfp
	mov	r0, r5	@ pCrPicAddr, pCrPicAddr
	ldr	sl, [fp, #-64]	@ fpYuv, %sfp
.L660:
	add	r7, r0, r9	@ pCrPicAddr, pCrPicAddr, chrom_width
	add	lr, r6, #1	@ tmp352, i.2703,
	mov	r1, r4	@, pretmp.2590
	mov	r2, sl	@, fpYuv
	add	r6, lr, #1	@ i.2703, tmp352,
	bl	klib_fwrite	@
	mov	r0, r7	@, pCrPicAddr
	mov	r1, r4	@, pretmp.2590
	mov	r2, sl	@, fpYuv
	bl	klib_fwrite	@
	cmp	r8, r6	@ disp_chroma_height, i.2703
	add	r0, r7, r9	@ pCrPicAddr, pCrPicAddr, chrom_width
	bhi	.L660	@,
.L676:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L641:
	ldr	r2, [fp, #4]	@, Height
	subs	r6, r6, #1	@, PicStructure,
	movne	r6, #1	@
	str	r6, [fp, #-60]	@, %sfp
	cmp	r2, r6	@,
	movwls	r6, #:lower16:.LANCHOR0	@ tmp454,
	movtls	r6, #:upper16:.LANCHOR0	@ tmp454,
	bls	.L661	@,
	ldr	r9, [fp, #-60]	@, %sfp
	movw	r6, #:lower16:.LANCHOR0	@ tmp454,
	movt	r6, #:upper16:.LANCHOR0	@ tmp454,
	mov	sl, r5	@ Yaddress, Yaddress
	str	r9, [fp, #-48]	@, %sfp
	mov	r9, r4	@ Width, Width
.L662:
	cmp	r9, #0	@ Width,
	beq	.L664	@,
	ldr	r2, [fp, #-48]	@, %sfp
	sub	r5, r9, #1	@ tmp393, Width,
	ldr	ip, [fp, #12]	@, Stride
	ubfx	r5, r5, #8, #1	@ tmp394, tmp393,,
	and	r1, r2, #15	@ pretmp.2748,,
	ldr	lr, [r6, #504]	@ pY, pY
	mov	r7, r2, lsr #4	@ pretmp.2741,,
	mov	r8, r2, lsr #1	@ pretmp.2743,,
	mov	r2, #256	@,
	mul	r4, ip, r7	@ tmp296,, pretmp.2741
	mla	r7, r1, r2, r4	@ pretmp.2586, pretmp.2748,, tmp296
	mov	r4, r2	@ j.2716,
	mul	r8, r9, r8	@ pretmp.2742, Width, pretmp.2743
	add	r1, sl, r7	@, Yaddress, pretmp.2586
	add	r0, r8, lr	@, pretmp.2742, pY
	bl	memcpy	@
	cmp	r9, r4	@ Width, j.2716
	bls	.L664	@,
	cmp	r5, #0	@ tmp394,
	beq	.L663	@,
	ldr	lr, [r6, #504]	@ pY, pY
	add	r0, r4, r8	@ tmp534, j.2716, pretmp.2742
	add	ip, r7, #4096	@ tmp539, pretmp.2586,
	mov	r2, r4	@, j.2716
	add	r0, r0, lr	@, tmp534, pY
	add	r1, sl, ip	@, Yaddress, tmp539
	bl	memcpy	@
	mov	r4, #512	@ j.2716,
	cmp	r9, r4	@ Width, j.2716
	bls	.L664	@,
.L663:
	mov	r1, r4, lsr #8	@ tmp287, j.2716,
	ldr	r2, [r6, #504]	@ pY, pY
	add	r5, r4, #256	@ tmp395, j.2716,
	add	lr, r4, r8	@ tmp284, j.2716, pretmp.2742
	add	ip, r7, r1, asl #12	@, tmp289, pretmp.2586, tmp287,
	add	r0, lr, r2	@, tmp284, pY
	add	r1, sl, ip	@, Yaddress, tmp289
	mov	r2, #256	@,
	mov	r4, r5, lsr #8	@ tmp459, tmp395,
	bl	memcpy	@
	ldr	r3, [r6, #504]	@ pY, pY
	add	r0, r5, r8	@ tmp456, tmp395, pretmp.2742
	add	r1, r7, r4, asl #12	@, tmp461, pretmp.2586, tmp459,
	mov	r2, #256	@,
	add	r4, r5, #256	@ j.2716, tmp395,
	add	r0, r0, r3	@, tmp456, pY
	add	r1, sl, r1	@, Yaddress, tmp461
	bl	memcpy	@
	cmp	r9, r4	@ Width, j.2716
	bhi	.L663	@,
.L664:
	ldr	r3, [fp, #-48]	@, %sfp
	ldr	r7, [fp, #4]	@, Height
	add	r0, r3, #2	@,,
	str	r0, [fp, #-48]	@, %sfp
	cmp	r7, r0	@,
	bhi	.L662	@,
	mov	r4, r9	@ Width, Width
.L661:
	ldr	lr, [fp, #4]	@, Height
	ldr	r0, [r6, #504]	@, pY
	ldr	r2, [fp, #-64]	@, %sfp
	mul	r3, r4, lr	@ tmp299, Width,
	mov	r1, r3, lsr #1	@, tmp299,
	bl	klib_fwrite	@
	ldr	r0, [fp, #-56]	@, %sfp
	cmp	r0, #0	@,
	beq	.L665	@,
	ldr	r1, [fp, #12]	@, Stride
	mov	r8, #0	@ ivtmp.2683,
	ldr	sl, [fp, #-76]	@ Caddress, %sfp
	str	r8, [fp, #-48]	@ i.2727, %sfp
	mov	r9, r1, lsr #1	@,,
	str	r9, [fp, #-52]	@, %sfp
	mov	r9, r4	@ Width, Width
.L666:
	cmp	r9, #0	@ Width,
	beq	.L668	@,
	ldr	r7, [fp, #-48]	@, %sfp
	mov	r2, #256	@,
	ldr	ip, [fp, #-52]	@, %sfp
	sub	r5, r9, #1	@ tmp388, Width,
	and	r1, r7, #7	@ pretmp.2758,,
	ldr	r4, [r6, #504]	@ pY, pY
	mov	r0, r7, lsr #3	@ pretmp.2755,,
	ubfx	r5, r5, #8, #1	@ tmp389, tmp388,,
	mul	lr, ip, r0	@ tmp314,, pretmp.2755
	add	r0, r8, r4	@, ivtmp.2683, pY
	mla	r7, r1, r2, lr	@ pretmp.2584, pretmp.2758,, tmp314
	mov	r4, r2	@ j.2726,
	add	r1, sl, r7	@, Caddress, pretmp.2584
	bl	memcpy	@
	cmp	r9, r4	@ Width, j.2726
	bls	.L668	@,
	cmp	r5, #0	@ tmp389,
	beq	.L667	@,
	ldr	r3, [r6, #504]	@ pY, pY
	add	r1, r8, r4	@ tmp527, ivtmp.2683, j.2726
	add	lr, r7, #2048	@ tmp532, pretmp.2584,
	mov	r2, r4	@, j.2726
	add	r0, r1, r3	@, tmp527, pY
	add	r1, sl, lr	@, Caddress, tmp532
	bl	memcpy	@
	mov	r4, #512	@ j.2726,
	cmp	r9, r4	@ Width, j.2726
	bls	.L668	@,
.L667:
	mov	r1, r4, lsr #8	@ tmp305, j.2726,
	ldr	ip, [r6, #504]	@ pY, pY
	add	r5, r4, #256	@ tmp390, j.2726,
	add	r0, r8, r4	@ tmp302, ivtmp.2683, j.2726
	add	lr, r7, r1, asl #11	@, tmp307, pretmp.2584, tmp305,
	add	r0, r0, ip	@, tmp302, pY
	add	r1, sl, lr	@, Caddress, tmp307
	mov	r2, #256	@,
	mov	r4, r5, lsr #8	@ tmp475, tmp390,
	bl	memcpy	@
	ldr	r3, [r6, #504]	@ pY, pY
	add	r2, r8, r5	@ tmp472, ivtmp.2683, tmp390
	add	ip, r7, r4, asl #11	@, tmp477, pretmp.2584, tmp475,
	add	r4, r5, #256	@ j.2726, tmp390,
	add	r0, r2, r3	@, tmp472, pY
	add	r1, sl, ip	@, Caddress, tmp477
	mov	r2, #256	@,
	bl	memcpy	@
	cmp	r9, r4	@ Width, j.2726
	bhi	.L667	@,
.L668:
	ldr	r3, [fp, #-48]	@, %sfp
	add	r8, r8, r9	@ ivtmp.2683, ivtmp.2683, Width
	ldr	r2, [fp, #-56]	@, %sfp
	add	r7, r3, #1	@,,
	str	r7, [fp, #-48]	@, %sfp
	cmp	r2, r7	@,
	bhi	.L666	@,
	mov	r4, r9	@ Width, Width
.L665:
	ldr	r2, [fp, #16]	@, chroma_idc
	ldr	r7, [r6, #504]	@ pY.2728, pY
	cmp	r2, #1	@,
	beq	.L774	@,
	ldr	r4, [fp, #16]	@, chroma_idc
	cmp	r4, #0	@,
	bne	.L670	@,
	ldr	r2, [fp, #-56]	@, %sfp
	ldr	r3, [fp, #-60]	@, %sfp
	cmp	r2, r3	@,
	bls	.L674	@,
	ldr	r1, [fp, #-56]	@, %sfp
	add	r3, r3, #2	@ i.2709,,
	ldr	ip, [fp, #-60]	@, %sfp
	cmp	r1, r3	@, i.2709
	mvn	r0, ip	@ tmp382,
	add	lr, r0, r1	@ tmp383, tmp382,
	ubfx	r2, lr, #1, #1	@ tmp384, tmp383,,
	bls	.L674	@,
	cmp	r2, #0	@ tmp384,
	beq	.L764	@,
	ldr	r2, [fp, #-56]	@, %sfp
	add	r3, r3, #2	@ i.2709, i.2709,
	cmp	r2, r3	@, i.2709
	bls	.L674	@,
.L764:
	ldr	r2, [fp, #-56]	@ chrom_height, %sfp
.L679:
	add	r3, r3, #4	@ i.2709, i.2709,
	cmp	r2, r3	@ chrom_height, i.2709
	bhi	.L679	@,
.L674:
	mov	r1, #128	@,
	mov	r2, #1048576	@,
	ldr	r0, [r6, #508]	@, pVl
	bl	memset	@
	ldr	r0, [r6, #512]	@, pUl
	mov	r1, #128	@,
	mov	r2, #1048576	@,
	bl	memset	@
.L670:
	ldr	r2, [fp, #-68]	@, %sfp
	ldr	r3, [fp, #-56]	@, %sfp
	ldr	r0, [r6, #512]	@, pUl
	mul	r4, r2, r3	@ tmp329,,
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r4, r4, lsr #1	@ D.55997, tmp329,
.L769:
	mov	r1, r4	@, D.55997
	bl	klib_fwrite	@
	ldr	r0, [r6, #508]	@, pVl
	mov	r1, r4	@, D.55997
	ldr	r2, [fp, #-64]	@, %sfp
	bl	klib_fwrite	@
	b	.L676	@
.L770:
	mul	r1, r4, ip	@, Width,
	ldr	r0, [r6, #504]	@, pY
	ldr	r2, [fp, #-64]	@, %sfp
	bl	klib_fwrite	@
	b	.L649	@
.L771:
	ldr	r2, [fp, #-56]	@, %sfp
	cmp	r2, #0	@,
	beq	.L654	@,
	ldr	r5, [fp, #-68]	@ chrom_width, %sfp
	mov	r1, #0	@ ivtmp.2634,
	mov	r9, r1	@ i.2702, ivtmp.2634
	str	r4, [fp, #-48]	@ Width, %sfp
.L655:
	cmp	r5, #0	@ chrom_width,
	beq	.L657	@,
	ldrb	r0, [sl, #0]	@ zero_extendqisi2	@ tmp443,* tmp
	mov	r2, #1	@ j.2701,
	ldr	lr, [r6, #508]	@ pVl, pVl
	cmp	r5, r2	@ chrom_width, j.2701
	sub	r4, r5, #1	@ tmp357, chrom_width,
	add	r3, sl, #2	@ ivtmp.2621, tmp,
	and	r4, r4, r2	@ tmp359, tmp357,
	strb	r0, [lr, r1]	@ tmp443,* ivtmp.2634
	ldr	r0, [r6, #512]	@ pUl, pUl
	ldrb	ip, [sl, #1]	@ zero_extendqisi2	@ tmp445,
	strb	ip, [r0, r1]	@ tmp445,* ivtmp.2634
	bls	.L657	@,
	cmp	r4, #0	@ tmp359,
	beq	.L656	@,
	ldrb	r4, [r3, #0]	@ zero_extendqisi2	@ tmp505,* ivtmp.2621
	add	lr, r1, r2	@ D.55931, ivtmp.2634, j.2701
	ldr	r0, [r6, #508]	@ pVl, pVl
	mov	r2, #2	@ j.2701,
	cmp	r5, r2	@ chrom_width, j.2701
	strb	r4, [r0, lr]	@ tmp505,* D.55931
	ldrb	r4, [r3, #1]	@ zero_extendqisi2	@ tmp507,
	add	r3, r3, r2	@ ivtmp.2621, ivtmp.2621,
	ldr	ip, [r6, #512]	@ pUl, pUl
	strb	r4, [ip, lr]	@ tmp507,* D.55931
	bls	.L657	@,
.L656:
	ldrb	r8, [r3, #0]	@ zero_extendqisi2	@ tmp263,* ivtmp.2621
	add	ip, r1, r2	@ D.55931, ivtmp.2634, j.2701
	ldr	r4, [r6, #508]	@ pVl, pVl
	add	r2, r2, #1	@ tmp360, j.2701,
	add	lr, r1, r2	@ D.55931, ivtmp.2634, tmp360
	add	r0, r3, #2	@ tmp361, ivtmp.2621,
	add	r2, r2, #1	@ j.2701, tmp360,
	strb	r8, [r4, ip]	@ tmp263,* D.55931
	cmp	r5, r2	@ chrom_width, j.2701
	ldrb	r8, [r3, #1]	@ zero_extendqisi2	@ tmp267,
	ldr	r7, [r6, #512]	@ pUl, pUl
	strb	r8, [r7, ip]	@ tmp267,* D.55931
	ldrb	r7, [r3, #2]	@ zero_extendqisi2	@ tmp436,
	add	r3, r0, #2	@ ivtmp.2621, tmp361,
	ldr	r4, [r6, #508]	@ pVl, pVl
	strb	r7, [r4, lr]	@ tmp436,* D.55931
	ldr	r4, [r6, #512]	@ pUl, pUl
	ldrb	ip, [r0, #1]	@ zero_extendqisi2	@ tmp438,
	strb	ip, [r4, lr]	@ tmp438,* D.55931
	bhi	.L656	@,
.L657:
	ldr	r3, [fp, #-56]	@, %sfp
	add	r9, r9, #1	@ i.2702, i.2702,
	add	r1, r1, r5	@ ivtmp.2634, ivtmp.2634, chrom_width
	cmp	r3, r9	@, i.2702
	bls	.L654	@,
	ldr	lr, [fp, #-48]	@, %sfp
	add	sl, sl, lr	@ tmp, tmp,
	b	.L655	@
.L774:
	ldr	r3, [fp, #-56]	@, %sfp
	cmp	r3, #0	@,
	beq	.L670	@,
	ldr	r8, [fp, #-60]	@, %sfp
	mov	sl, r4, asl #1	@ pretmp.2581, Width,
	mla	r7, r4, r8, r7	@ tmp.2729, Width,, pY.2728
	ldr	r4, [fp, #-68]	@ chrom_width, %sfp
	mov	r8, #0	@ i.2736,
.L671:
	cmp	r4, #0	@ chrom_width,
	beq	.L673	@,
	mov	r3, r8, lsr #1	@ pretmp.2747, i.2736,
	ldr	r1, [r6, #508]	@ pVl, pVl
	ldrb	r0, [r7, #0]	@ zero_extendqisi2	@ tmp498,* tmp.2729
	mov	r2, #1	@ j.2735,
	mul	lr, r4, r3	@ pretmp.2744, chrom_width, pretmp.2747
	cmp	r4, r2	@ chrom_width, j.2735
	sub	ip, r4, #1	@ tmp376, chrom_width,
	add	r3, r7, #2	@ ivtmp.2658, tmp.2729,
	and	ip, ip, r2	@ tmp378, tmp376,
	strb	r0, [r1, lr]	@ tmp498,* pretmp.2744
	ldr	r1, [r6, #512]	@ pUl, pUl
	ldrb	r0, [r7, #1]	@ zero_extendqisi2	@ tmp500,
	strb	r0, [r1, lr]	@ tmp500,* pretmp.2744
	bls	.L673	@,
	cmp	ip, #0	@ tmp378,
	beq	.L672	@,
	ldrb	ip, [r3, #0]	@ zero_extendqisi2	@ tmp524,* ivtmp.2658
	add	r1, r2, lr	@ D.55979, j.2735, pretmp.2744
	ldr	r0, [r6, #508]	@ pVl, pVl
	mov	r2, #2	@ j.2735,
	cmp	r4, r2	@ chrom_width, j.2735
	strb	ip, [r0, r1]	@ tmp524,* D.55979
	ldrb	ip, [r3, #1]	@ zero_extendqisi2	@ tmp526,
	add	r3, r3, r2	@ ivtmp.2658, ivtmp.2658,
	ldr	r0, [r6, #512]	@ pUl, pUl
	strb	ip, [r0, r1]	@ tmp526,* D.55979
	bls	.L673	@,
.L672:
	ldrb	r9, [r3, #0]	@ zero_extendqisi2	@ tmp319,* ivtmp.2658
	add	ip, r2, lr	@ D.55979, j.2735, pretmp.2744
	ldr	r5, [r6, #508]	@ pVl, pVl
	add	r2, r2, #1	@ tmp379, j.2735,
	add	r1, r2, lr	@ D.55979, tmp379, pretmp.2744
	add	r0, r3, #2	@ tmp380, ivtmp.2658,
	add	r2, r2, #1	@ j.2735, tmp379,
	strb	r9, [r5, ip]	@ tmp319,* D.55979
	cmp	r4, r2	@ chrom_width, j.2735
	ldrb	r9, [r3, #1]	@ zero_extendqisi2	@ tmp323,
	ldr	r5, [r6, #512]	@ pUl, pUl
	strb	r9, [r5, ip]	@ tmp323,* D.55979
	ldrb	r5, [r3, #2]	@ zero_extendqisi2	@ tmp491,
	add	r3, r0, #2	@ ivtmp.2658, tmp380,
	ldr	ip, [r6, #508]	@ pVl, pVl
	strb	r5, [ip, r1]	@ tmp491,* D.55979
	ldr	ip, [r6, #512]	@ pUl, pUl
	ldrb	r0, [r0, #1]	@ zero_extendqisi2	@ tmp493,
	strb	r0, [ip, r1]	@ tmp493,* D.55979
	bhi	.L672	@,
.L673:
	ldr	lr, [fp, #-56]	@, %sfp
	add	r8, r8, #2	@ i.2736, i.2736,
	cmp	lr, r8	@, i.2736
	bls	.L670	@,
	add	r7, r7, sl	@ tmp.2729, tmp.2729, pretmp.2581
	b	.L671	@
.L772:
	mov	r1, #128	@,
	mov	r2, #1048576	@,
	ldr	r0, [r5, #508]	@, pVl
	bl	memset	@
	ldr	r0, [r5, #512]	@, pUl
	mov	r1, #128	@,
	mov	r2, #1048576	@,
	bl	memset	@
	b	.L654	@
.L773:
	ldr	r3, [fp, #-68]	@, %sfp
	ldr	ip, [fp, #-56]	@, %sfp
	ldr	r2, [fp, #-64]	@, %sfp
	ldr	r0, [r6, #512]	@, pUl
	mul	r4, r3, ip	@ D.55958,,
	b	.L769	@
	.fnend
	.size	DBG_WriteBigTileYuv, .-DBG_WriteBigTileYuv
	.align	2
	.global	VCTRL_GetDecParam
	.type	VCTRL_GetDecParam, %function
VCTRL_GetDecParam:
	.fnstart
.LFB1587:
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
	cmp	r0, #15	@ ChanId,
	bhi	.L776	@,
	movw	r2, #:lower16:.LANCHOR0	@ tmp159,
	movt	r2, #:upper16:.LANCHOR0	@ tmp159,
	ldr	r5, [r2, r0, asl #2]	@ D.52142, s_pstVfmwChan
	cmp	r5, #0	@ D.52142,
	beq	.L776	@,
	ldr	r3, [r5, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r3, #1	@ <variable>.s32IsOpen,
	beq	.L797	@,
.L779:
	mov	r4, #0	@ pDecParam,
.L778:
	mov	r0, r4	@, pDecParam
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L776:
	mov	r3, r0	@, ChanId
	movw	r2, #4464	@,
	mov	r4, #0	@ pDecParam,
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC55	@,
	movt	r1, #:upper16:.LC55	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, pDecParam
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L797:
	ldr	r0, [r5, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #1	@ <variable>.s32IsRun,
	bne	.L779	@,
	ldr	r1, [r5, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r1, #16	@ <variable>.eVidStd,
	ldrls	pc, [pc, r1, asl #2]	@ <variable>.eVidStd
	b	.L779	@
.L793:
	.word	.L781
	.word	.L796
	.word	.L783
	.word	.L796
	.word	.L779
	.word	.L796
	.word	.L796
	.word	.L779
	.word	.L796
	.word	.L796
	.word	.L789
	.word	.L789
	.word	.L789
	.word	.L796
	.word	.L779
	.word	.L791
	.word	.L792
.L789:
	ldr	r4, [r2, #516]	@ g_VdmCharacter, g_VdmCharacter
	tst	r4, #1	@ g_VdmCharacter,
	beq	.L779	@,
.L796:
	movw	r0, #:lower16:251588	@ tmp156,
	movt	r0, #:upper16:251588	@ tmp156,
	ldr	r4, [r5, r0]	@ pDecParam,
.L794:
	cmp	r4, #0	@ pDecParam,
	beq	.L778	@,
	bl	OSAL_GetTimeInMs	@
	str	r0, [r5, #44]	@, <variable>.u32timeLastDecParamReady
	b	.L778	@
.L781:
	movw	r2, #:lower16:251944	@ tmp143,
	movt	r2, #:upper16:251944	@ tmp143,
	ldr	r4, [r5, r2]	@ pDecParam,
	b	.L794	@
.L792:
	movw	ip, #:lower16:2211776	@ tmp144,
	movt	ip, #:upper16:2211776	@ tmp144,
	ldr	r4, [r5, ip]	@ pDecParam,
	b	.L794	@
.L791:
	movw	r1, #:lower16:251812	@ tmp157,
	movt	r1, #:upper16:251812	@ tmp157,
	ldr	r4, [r5, r1]	@ pDecParam,
	b	.L794	@
.L783:
	movw	r3, #:lower16:252620	@ tmp146,
	movt	r3, #:upper16:252620	@ tmp146,
	ldr	r4, [r5, r3]	@ pDecParam,
	b	.L794	@
	.fnend
	.size	VCTRL_GetDecParam, .-VCTRL_GetDecParam
	.align	2
	.global	VCTRL_ChanDecparamInValidFlag
	.type	VCTRL_ChanDecparamInValidFlag, %function
VCTRL_ChanDecparamInValidFlag:
	.fnstart
.LFB1588:
	@ args = 0, pretend = 0, frame = 8
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
	cmp	r0, #15	@ ChanId,
	mov	r2, r0	@ ChanId, ChanId
	bhi	.L799	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp144,
	movt	r4, #:upper16:.LANCHOR0	@ tmp144,
	ldr	r3, [r4, r0, asl #2]	@ D.52169, s_pstVfmwChan
	cmp	r3, #0	@ D.52169,
	beq	.L799	@,
	ldr	r1, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r1, #1	@ <variable>.s32IsOpen,
	bne	.L802	@,
	ldr	r5, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r5, #1	@ <variable>.s32IsRun,
	beq	.L803	@,
.L802:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC56	@,
	movt	r1, #:upper16:.LC56	@,
	bl	dprint_vfmw	@
	mov	r3, #0	@ D.52171,
.L801:
	mov	r0, r3	@, D.52171
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L799:
	mov	r3, r2	@, ChanId
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC55	@,
	movw	r2, #4574	@,
	movt	r1, #:upper16:.LC55	@,
	bl	dprint_vfmw	@
	mov	r3, #0	@ D.52171,
	b	.L801	@
.L803:
	str	r0, [fp, #-32]	@ tmp2,
	bl	VCTRL_GetDecParam	@
	ldr	r2, [fp, #-32]	@,
	subs	r6, r0, #0	@ pDecParam,
	beq	.L809	@,
	ldr	r0, [r4, r2, asl #2]	@ tmp154, s_pstVfmwChan
	mov	ip, #0	@ tmp155,
	mov	r3, ip	@ D.52171, tmp155
	str	ip, [r0, #344]	@ tmp155, <variable>.s32CountNoDecparamFlag
	ldr	r2, [r4, r2, asl #2]	@ tmp157, s_pstVfmwChan
	str	ip, [r2, #348]	@ tmp155, <variable>.u32NoDecparamStartTime
	b	.L801	@
.L809:
	ldr	r3, [r4, r2, asl #2]	@ temp.2805, s_pstVfmwChan
	ldr	r7, [r3, #344]	@ <variable>.s32CountNoDecparamFlag, <variable>.s32CountNoDecparamFlag
	cmp	r7, #0	@ <variable>.s32CountNoDecparamFlag,
	beq	.L810	@,
	str	r2, [fp, #-32]	@,
	bl	OSAL_GetTimeInMs	@
	ldr	r2, [fp, #-32]	@,
	ldr	r3, [r4, r2, asl #2]	@ temp.2809, s_pstVfmwChan
	ldr	r1, [r3, #348]	@ D.52192, <variable>.u32NoDecparamStartTime
	cmp	r0, r1	@ tmp, D.52192
	bls	.L806	@,
	rsb	lr, r1, r0	@ tmp160, D.52192, tmp
	cmp	lr, #40	@ tmp160,
	movls	r3, r6	@ D.52171, pDecParam
	bls	.L801	@,
.L806:
	str	r6, [r3, #344]	@ pDecParam, <variable>.s32CountNoDecparamFlag
	mov	r3, r5	@ D.52171, <variable>.s32IsRun
	ldr	r1, [r4, r2, asl #2]	@ tmp167, s_pstVfmwChan
	str	r6, [r1, #348]	@ pDecParam, <variable>.u32NoDecparamStartTime
	b	.L801	@
.L810:
	str	r5, [r3, #344]	@ <variable>.s32IsRun, <variable>.s32CountNoDecparamFlag
	ldr	r4, [r4, r2, asl #2]	@ temp.2806, s_pstVfmwChan
	bl	OSAL_GetTimeInMs	@
	mov	r3, r7	@ D.52171, <variable>.s32CountNoDecparamFlag
	str	r0, [r4, #348]	@, <variable>.u32NoDecparamStartTime
	b	.L801	@
	.fnend
	.size	VCTRL_ChanDecparamInValidFlag, .-VCTRL_ChanDecparamInValidFlag
	.align	2
	.global	VCTRL_StartTask
	.type	VCTRL_StartTask, %function
VCTRL_StartTask:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp145,
	movt	r4, #:upper16:.LANCHOR0	@ tmp145,
	ldr	r3, [r4, #104]	@ s_VfmwCTrl.s32IsVCTRLOpen, s_VfmwCTrl.s32IsVCTRLOpen
	cmp	r3, #1	@ s_VfmwCTrl.s32IsVCTRLOpen,
	mvnne	r0, #0	@ ret,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	mov	r5, #0	@ i,
	str	r3, [r4, #144]	@ s_VfmwCTrl.s32IsVCTRLOpen, s_VfmwCTrl.eTaskCommand
	b	.L816	@
.L814:
	bl	msleep	@
	ldr	r1, [r4, #140]	@ s_VfmwCTrl.eTaskState, s_VfmwCTrl.eTaskState
	mov	r0, #10	@,
	cmp	r1, #2	@ s_VfmwCTrl.eTaskState,
	beq	.L821	@,
	bl	msleep	@
	cmp	r5, #50	@ i,
	beq	.L823	@,
.L816:
	ldr	r3, [r4, #140]	@ s_VfmwCTrl.eTaskState, s_VfmwCTrl.eTaskState
	add	r5, r5, #1	@ tmp147, i,
	mov	r0, #10	@,
	add	r5, r5, #1	@ i, tmp147,
	cmp	r3, #2	@ s_VfmwCTrl.eTaskState,
	bne	.L814	@,
.L821:
	mov	r2, #0	@ tmp143,
	mov	r0, #0	@ ret,
	str	r2, [r4, #144]	@ tmp143, s_VfmwCTrl.eTaskCommand
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L823:
	mov	r2, #0	@ tmp143,
	mvn	r0, #0	@ ret,
	str	r2, [r4, #144]	@ tmp143, s_VfmwCTrl.eTaskCommand
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	VCTRL_StartTask, .-VCTRL_StartTask
	.align	2
	.global	VCTRL_StopTask
	.type	VCTRL_StopTask, %function
VCTRL_StopTask:
	.fnstart
.LFB1547:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp145,
	movt	r4, #:upper16:.LANCHOR0	@ tmp145,
	ldr	r3, [r4, #104]	@ s_VfmwCTrl.s32IsVCTRLOpen, s_VfmwCTrl.s32IsVCTRLOpen
	cmp	r3, #1	@ s_VfmwCTrl.s32IsVCTRLOpen,
	mvnne	r0, #0	@ ret,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	mov	r0, #2	@ tmp139,
	mov	r5, #0	@ i,
	str	r0, [r4, #144]	@ tmp139, s_VfmwCTrl.eTaskCommand
	b	.L829	@
.L827:
	bl	msleep	@
	ldr	r2, [r4, #140]	@ s_VfmwCTrl.eTaskState, s_VfmwCTrl.eTaskState
	mov	r0, #10	@,
	cmp	r2, #1	@ s_VfmwCTrl.eTaskState,
	beq	.L834	@,
	bl	msleep	@
	cmp	r5, #50	@ i,
	beq	.L836	@,
.L829:
	ldr	r1, [r4, #140]	@ s_VfmwCTrl.eTaskState, s_VfmwCTrl.eTaskState
	add	r5, r5, #1	@ tmp147, i,
	mov	r0, #10	@,
	add	r5, r5, #1	@ i, tmp147,
	cmp	r1, #1	@ s_VfmwCTrl.eTaskState,
	bne	.L827	@,
.L834:
	mov	ip, #0	@ tmp143,
	mov	r0, #0	@ ret,
	str	ip, [r4, #144]	@ tmp143, s_VfmwCTrl.eTaskCommand
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L836:
	mov	ip, #0	@ tmp143,
	mvn	r0, #0	@ ret,
	str	ip, [r4, #144]	@ tmp143, s_VfmwCTrl.eTaskCommand
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	VCTRL_StopTask, .-VCTRL_StopTask
	.align	2
	.global	VCTRT_SetChanCtrlState
	.type	VCTRT_SetChanCtrlState, %function
VCTRT_SetChanCtrlState:
	.fnstart
.LFB1662:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp137,
	movt	r4, #:upper16:.LANCHOR0	@ tmp137,
	mov	r5, r0	@ ChanID, ChanID
	add	r0, r4, #520	@, tmp137,
	mov	r6, r1	@ ChanCtrlState, ChanCtrlState
	bl	OSAL_SpinLockIRQ	@
	cmp	r6, #1	@ ChanCtrlState,
	beq	.L840	@,
	bcs	.L846	@,
	mov	r3, #0	@ tmp144,
	add	r4, r4, r5, asl #2	@, tmp142, tmp137, ChanID,
	mov	r6, r3	@ ret, tmp144
	str	r3, [r4, #532]	@ tmp144, s_ChanControlState
.L842:
	ldr	r0, .L848	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r6	@, ret
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L846:
	cmp	r6, #2	@ ChanCtrlState,
	beq	.L841	@,
	mov	r6, #0	@ ret,
.L847:
	ldr	r0, .L848	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r6	@, ret
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L841:
	add	r4, r4, r5, asl #2	@, tmp160, tmp137, ChanID,
	ldr	r1, [r4, #532]	@ tmp162, s_ChanControlState
	cmp	r1, #1	@ tmp162,
	beq	.L843	@,
	str	r6, [r4, #532]	@ ChanCtrlState, s_ChanControlState
	mov	r6, #0	@ ret,
	b	.L847	@
.L840:
	add	r4, r4, r5, asl #2	@, tmp148, tmp137, ChanID,
	ldr	r0, [r4, #532]	@ tmp150, s_ChanControlState
	cmp	r0, #0	@ tmp150,
	streq	r6, [r4, #532]	@ ChanCtrlState, s_ChanControlState
	moveq	r6, r0	@ ret, tmp150
	beq	.L842	@,
.L843:
	mvn	r6, #0	@ ret,
	ldr	r0, .L848	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r6	@, ret
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L849:
	.align	2
.L848:
	.word	.LANCHOR0+520
	.fnend
	.size	VCTRT_SetChanCtrlState, .-VCTRT_SetChanCtrlState
	.align	2
	.global	vfmw_proc_destroy
	.type	vfmw_proc_destroy, %function
vfmw_proc_destroy:
	.fnstart
.LFB1654:
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
	ldr	r4, .L860	@ ivtmp.2926,
	mov	r5, r0	@ proc_name, proc_name
	add	r7, r4, #768	@ D.58345, ivtmp.2926,
	b	.L853	@
.L851:
	add	r4, r4, #24	@ ivtmp.2926, ivtmp.2926,
	mov	r1, r4	@, ivtmp.2926
	bl	strncmp	@
	subs	r6, r0, #0	@ tmp143,
	beq	.L858	@,
	add	r4, r4, #24	@ ivtmp.2926, ivtmp.2926,
	cmp	r4, r7	@ ivtmp.2926, D.58345
	beq	.L859	@,
.L853:
	mov	r2, #16	@,
	mov	r1, r4	@, ivtmp.2926
	mov	r0, r5	@, proc_name
	bl	strncmp	@
	mov	r2, #16	@,
	subs	r6, r0, #0	@ tmp143,
	mov	r0, r5	@, proc_name
	bne	.L851	@,
.L858:
	mov	r0, r5	@, proc_name
	mov	r1, r6	@, tmp143
	bl	remove_proc_entry	@
	mov	r0, r4	@, ivtmp.2926
	mov	r1, #16	@,
	bl	__memzero	@
	str	r6, [r4, #20]	@ tmp143, <variable>.write
	str	r6, [r4, #16]	@ tmp143, <variable>.read
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L859:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L861:
	.align	2
.L860:
	.word	.LANCHOR0+596
	.fnend
	.size	vfmw_proc_destroy, .-vfmw_proc_destroy
	.align	2
	.global	vfmw_proc_exit
	.type	vfmw_proc_exit, %function
vfmw_proc_exit:
	.fnstart
.LFB1656:
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
	movw	r5, #:lower16:.LC57	@ tmp134,
	sub	r4, fp, #44	@ tmp133,,
	movt	r5, #:upper16:.LC57	@ tmp134,
	mov	r3, #0	@,
	mov	r1, #16	@,
	mov	r2, r5	@, tmp134
	mov	r0, r4	@, tmp133
	mov	r6, r3	@ tmp135,
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #1	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #2	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #3	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #4	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #5	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #6	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #7	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #8	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #9	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #10	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #11	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #12	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #13	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #14	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	mov	r2, r5	@, tmp134
	mov	r1, #16	@,
	mov	r3, #15	@,
	mov	r0, r4	@, tmp133
	bl	snprintf	@
	mov	r0, r4	@, tmp133
	strb	r6, [fp, #-29]	@ tmp135, name
	bl	vfmw_proc_destroy	@
	movw	r0, #:lower16:.LC58	@,
	movt	r0, #:upper16:.LC58	@,
	bl	vfmw_proc_destroy	@
	movw	r0, #:lower16:.LC59	@,
	movt	r0, #:upper16:.LC59	@,
	bl	vfmw_proc_destroy	@
	movw	r0, #:lower16:.LC60	@,
	movt	r0, #:upper16:.LC60	@,
	bl	vfmw_proc_destroy	@
	movw	r0, #:lower16:.LC61	@,
	movt	r0, #:upper16:.LC61	@,
	bl	vfmw_proc_destroy	@
	movw	r0, #:lower16:.LC62	@,
	movt	r0, #:upper16:.LC62	@,
	bl	vfmw_proc_destroy	@
	movw	r0, #:lower16:.LC63	@,
	movt	r0, #:upper16:.LC63	@,
	bl	vfmw_proc_destroy	@
	movw	r0, #:lower16:.LC64	@,
	movt	r0, #:upper16:.LC64	@,
	bl	vfmw_proc_destroy	@
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	.fnend
	.size	vfmw_proc_exit, .-vfmw_proc_exit
	.align	2
	.global	ChanCtx_Init
	.type	ChanCtx_Init, %function
ChanCtx_Init:
	.fnstart
.LFB1532:
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
	movw	r4, #:lower16:g_ChanCtx	@ tmp133,
	movt	r4, #:upper16:g_ChanCtx	@ tmp133,
	mov	r1, #192	@,
	mov	r0, r4	@, tmp133
	bl	__memzero	@
	mvn	r3, #0	@ tmp135,
	str	r3, [r4, #124]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #64]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #68]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #72]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #76]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #80]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #84]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #88]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #92]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #96]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #100]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #104]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #108]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #112]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #116]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	str	r3, [r4, #120]	@ tmp135, g_ChanCtx.ChanIdTabByPrior
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	ChanCtx_Init, .-ChanCtx_Init
	.align	2
	.global	VCTRL_UnRegisterSoftDecoder
	.type	VCTRL_UnRegisterSoftDecoder, %function
VCTRL_UnRegisterSoftDecoder:
	.fnstart
.LFB1529:
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
	ldr	r0, .L868	@,
	mov	r1, #28	@,
	bl	__memzero	@
	ldmfd	sp, {fp, sp, pc}	@
.L869:
	.align	2
.L868:
	.word	.LANCHOR0+76
	.fnend
	.size	VCTRL_UnRegisterSoftDecoder, .-VCTRL_UnRegisterSoftDecoder
	.align	2
	.global	vfmw_proc_create
	.type	vfmw_proc_create, %function
vfmw_proc_create:
	.fnstart
.LFB1653:
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
	ldr	r3, .L885	@ tmp161,
	mov	sl, r2	@ write, write
	mov	r7, r0	@ proc_name, proc_name
	mov	r8, r1	@ read, read
	mov	r5, #0	@ i,
	mov	r2, r3	@ ivtmp.3033, tmp161
	b	.L874	@
.L871:
	ldr	r2, [r1, #16]	@ <variable>.read, <variable>.read
	add	r5, r5, #1	@ i, i,
	cmp	r2, #0	@ <variable>.read,
	mov	r2, r5	@ tmp162, i
	beq	.L883	@,
.L878:
	add	r5, r2, #1	@ i, tmp162,
	add	r2, r1, #24	@ ivtmp.3033, tmp163,
	cmp	r5, #32	@ i,
	beq	.L872	@,
.L874:
	ldr	r0, [r2, #16]	@ <variable>.read, <variable>.read
	add	r1, r2, #24	@ tmp163, ivtmp.3033,
	cmp	r0, #0	@ <variable>.read,
	bne	.L871	@,
	ldr	r6, [r2, #20]	@ <variable>.write, <variable>.write
	cmp	r6, #0	@ <variable>.write,
	bne	.L871	@,
.L882:
	add	r4, r5, r5, asl #1	@, tmp153, i, i,
	mov	r1, r7	@, proc_name
	mov	r2, #16	@,
	add	r4, r3, r4, asl #3	@, proc, tmp161, tmp153,
	mov	r0, r4	@, proc
	bl	strncpy	@
	cmp	r5, #31	@ i,
	strb	r6, [r4, #15]	@ <variable>.write, <variable>.proc_name
	str	r8, [r4, #16]	@ read, <variable>.read
	str	sl, [r4, #20]	@ write, <variable>.write
	bls	.L884	@,
.L872:
	mvn	r0, #0	@ D.55275,
.L875:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L883:
	ldr	r6, [r1, #20]	@ <variable>.write, <variable>.write
	cmp	r6, #0	@ <variable>.write,
	bne	.L878	@,
	b	.L882	@
.L884:
	mov	r0, r7	@, proc_name
	mov	r1, #420	@,
	mov	r2, #0	@,
	ldr	r3, .L885+4	@,
	str	r4, [sp, #0]	@ proc,
	bl	proc_create_data	@
	cmp	r0, #0	@,
	movne	r0, #0	@ D.55275,
	bne	.L875	@,
	b	.L872	@
.L886:
	.align	2
.L885:
	.word	.LANCHOR0+596
	.word	.LANCHOR1+80
	.fnend
	.size	vfmw_proc_create, .-vfmw_proc_create
	.align	2
	.global	vfmw_proc_init
	.type	vfmw_proc_init, %function
vfmw_proc_init:
	.fnstart
.LFB1655:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #16
	sub	sp, sp, #16	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	sub	r4, fp, #36	@ tmp294,,
	mov	r1, #16	@,
	mov	r3, #0	@,
	movw	r2, #:lower16:.LC57	@,
	mov	r0, r4	@, tmp294
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	mov	r3, #0	@ tmp160,
	strb	r3, [fp, #-21]	@ tmp160, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3065,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #1	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3065, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3066,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #2	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3066, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3067,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #3	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3067, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3068,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #4	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3068, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3069,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #5	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3069, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3070,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #6	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3070, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3071,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #7	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3071, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3072,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #8	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3072, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3073,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #9	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3073, name
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #10	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	mov	r5, #0	@ tmp230,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ tmp230, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3075,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #11	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3075, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3076,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #12	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3076, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3077,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #13	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3077, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3078,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #14	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_info	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_info	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3078, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3079,
	bne	.L888	@,
	mov	r1, #16	@,
	mov	r3, #15	@,
	mov	r0, r4	@, tmp294
	movw	r2, #:lower16:.LC57	@,
	movt	r2, #:upper16:.LC57	@,
	bl	snprintf	@
	mov	r0, r4	@, tmp294
	movw	r1, #:lower16:vfmw_read_proc_priv	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r1, #:upper16:vfmw_read_proc_priv	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	strb	r5, [fp, #-21]	@ ret.3079, name
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L888	@,
	movw	r0, #:lower16:.LC58	@,
	movw	r1, #:lower16:vfmw_read_proc	@,
	movt	r0, #:upper16:.LC58	@,
	movt	r1, #:upper16:vfmw_read_proc	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	beq	.L891	@,
.L888:
	mvn	r0, #0	@ D.55319,
.L889:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L891:
	movw	r0, #:lower16:.LC59	@,
	movw	r1, #:lower16:vfmw_read_proc_dbg	@,
	movt	r0, #:upper16:.LC59	@,
	movt	r1, #:upper16:vfmw_read_proc_dbg	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L888	@,
	movw	r0, #:lower16:.LC60	@,
	movw	r1, #:lower16:vfmw_read_proc_prn	@,
	movt	r0, #:upper16:.LC60	@,
	movt	r1, #:upper16:vfmw_read_proc_prn	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L888	@,
	movw	r0, #:lower16:.LC61	@,
	movw	r1, #:lower16:vfmw_read_proc_scd	@,
	movt	r0, #:upper16:.LC61	@,
	movt	r1, #:upper16:vfmw_read_proc_scd	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L888	@,
	movw	r0, #:lower16:.LC62	@,
	movw	r1, #:lower16:vfmw_read_proc_dec	@,
	movt	r0, #:upper16:.LC62	@,
	movt	r1, #:upper16:vfmw_read_proc_dec	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L888	@,
	movw	r0, #:lower16:.LC63	@,
	movw	r1, #:lower16:vfmw_read_proc_lwd	@,
	movt	r0, #:upper16:.LC63	@,
	movt	r1, #:upper16:vfmw_read_proc_lwd	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L888	@,
	movw	r0, #:lower16:.LC64	@,
	movw	r1, #:lower16:vfmw_read_proc_chn	@,
	movt	r0, #:upper16:.LC64	@,
	movt	r1, #:upper16:vfmw_read_proc_chn	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@ ret.3064
	beq	.L889	@,
	b	.L888	@
	.fnend
	.size	vfmw_proc_init, .-vfmw_proc_init
	.align	2
	.type	vfmw_proc_open, %function
vfmw_proc_open:
	.fnstart
.LFB1651:
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
	mov	r4, r1	@ file, file
	bl	PDE_DATA	@
	subs	r2, r0, #0	@ D.55227,
	bne	.L896	@,
.L893:
	mvn	r0, #37	@ D.55230,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L896:
	ldr	r1, [r2, #16]	@ D.55231, <variable>.read
	cmp	r1, #0	@ D.55231,
	beq	.L893	@,
	mov	r0, r4	@, file
	bl	single_open	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	vfmw_proc_open, .-vfmw_proc_open
	.align	2
	.global	vfmw_read_proc_lwd
	.type	vfmw_read_proc_lwd, %function
vfmw_read_proc_lwd:
	.fnstart
.LFB1648:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	movw	r7, #:lower16:g_stLowdlyInfo	@ tmp143,
	movw	r4, #:lower16:.LC66	@ tmp145,
	movt	r7, #:upper16:g_stLowdlyInfo	@ tmp143,
	ldr	r8, [r3, #1364]	@ g_CurProcChan, g_CurProcChan
	movt	r4, #:upper16:.LC66	@ tmp145,
	mov	r5, r0	@ p, p
	movw	r1, #:lower16:.LC65	@,
	movt	r1, #:upper16:.LC65	@,
	rsb	r8, r8, r8, asl #3	@, tmp141, g_CurProcChan, g_CurProcChan,
	bl	seq_printf	@
	mov	r1, r4	@, tmp145
	mov	r0, r5	@, p
	add	r6, r7, r8, asl #3	@, pLwd, tmp143, tmp141,
	ldr	r3, [r7, r8, asl #3]	@, <variable>.lowdly_enable
	movw	r2, #:lower16:.LC67	@,
	movt	r2, #:upper16:.LC67	@,
	bl	seq_printf	@
	mov	r1, r4	@, tmp145
	ldr	r3, [r6, #4]	@, <variable>.chan_id
	mov	r0, r5	@, p
	movw	r2, #:lower16:.LC68	@,
	movt	r2, #:upper16:.LC68	@,
	bl	seq_printf	@
	mov	r1, r4	@, tmp145
	ldr	r3, [r6, #20]	@, <variable>.scd_count
	mov	r0, r5	@, p
	movw	r2, #:lower16:.LC69	@,
	movt	r2, #:upper16:.LC69	@,
	bl	seq_printf	@
	mov	r1, r4	@, tmp145
	ldr	r3, [r6, #32]	@, <variable>.vdh_count
	mov	r0, r5	@, p
	movw	r2, #:lower16:.LC70	@,
	movt	r2, #:upper16:.LC70	@,
	bl	seq_printf	@
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	mov	r0, #0	@,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	.fnend
	.size	vfmw_read_proc_lwd, .-vfmw_read_proc_lwd
	.align	2
	.global	vfmw_read_proc_chn
	.type	vfmw_read_proc_chn, %function
vfmw_read_proc_chn:
	.fnstart
.LFB1646:
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
	movw	r1, #:lower16:.LC72	@,
	mov	r4, r0	@ p, p
	movt	r1, #:upper16:.LC72	@,
	movw	r6, #:lower16:g_ChanCtx	@ tmp155,
	movt	r6, #:upper16:g_ChanCtx	@ tmp155,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC73	@,
	movt	r1, #:upper16:.LC73	@,
	bl	seq_printf	@
	ldr	r2, [r6, #128]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, r2, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	ip, [r6, #132]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, ip, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r3, [r6, #136]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, r3, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #140]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, r2, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	ip, [r6, #144]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, ip, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r3, [r6, #148]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, r3, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #152]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, r2, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	ip, [r6, #156]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, ip, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r3, [r6, #160]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, r3, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #164]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, r2, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	ip, [r6, #168]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, ip, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r3, [r6, #172]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, r3, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #176]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, r2, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	ip, [r6, #180]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, ip, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r3, [r6, #184]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, r3, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #188]	@ g_ChanCtx.ChanDecByVdhPlusOne, g_ChanCtx.ChanDecByVdhPlusOne
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	sub	r2, r2, #1	@, g_ChanCtx.ChanDecByVdhPlusOne,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC75	@,
	movt	r1, #:upper16:.LC75	@,
	bl	seq_printf	@
	ldr	r2, [r6, #64]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	movw	r5, #:lower16:.LANCHOR0	@ tmp403,
	bl	seq_printf	@
	ldr	r2, [r6, #68]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	movt	r5, #:upper16:.LANCHOR0	@ tmp403,
	bl	seq_printf	@
	ldr	r2, [r6, #72]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #76]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #80]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #84]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #88]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #92]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #96]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #100]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #104]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #108]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #112]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #116]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #120]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #124]	@, g_ChanCtx.ChanIdTabByPrior
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC76	@,
	movt	r1, #:upper16:.LC76	@,
	bl	seq_printf	@
	ldr	r2, [r6, #0]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #4]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #8]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #12]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #16]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #20]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #24]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #28]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #32]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #36]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #40]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #44]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #48]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #52]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #56]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	ldr	r2, [r6, #60]	@, g_ChanCtx.PriorByChanId
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC77	@,
	movt	r1, #:upper16:.LC77	@,
	bl	seq_printf	@
	ldr	r0, [r5, #0]	@ temp.3215, s_pstVfmwChan
	cmp	r0, #0	@ temp.3215,
	beq	.L900	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L900:
	ldr	r0, [r5, #4]	@ temp.3219, s_pstVfmwChan
	cmp	r0, #0	@ temp.3219,
	beq	.L901	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L901:
	ldr	r0, [r5, #8]	@ temp.3223, s_pstVfmwChan
	cmp	r0, #0	@ temp.3223,
	beq	.L902	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L902:
	ldr	r0, [r5, #12]	@ temp.3227, s_pstVfmwChan
	cmp	r0, #0	@ temp.3227,
	beq	.L903	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L903:
	ldr	r0, [r5, #16]	@ temp.3231, s_pstVfmwChan
	cmp	r0, #0	@ temp.3231,
	beq	.L904	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L904:
	ldr	r0, [r5, #20]	@ temp.3235, s_pstVfmwChan
	cmp	r0, #0	@ temp.3235,
	beq	.L905	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L905:
	ldr	r0, [r5, #24]	@ temp.3239, s_pstVfmwChan
	cmp	r0, #0	@ temp.3239,
	beq	.L906	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L906:
	ldr	r0, [r5, #28]	@ temp.3243, s_pstVfmwChan
	cmp	r0, #0	@ temp.3243,
	beq	.L907	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L907:
	ldr	r0, [r5, #32]	@ temp.3247, s_pstVfmwChan
	cmp	r0, #0	@ temp.3247,
	beq	.L908	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L908:
	ldr	r0, [r5, #36]	@ temp.3251, s_pstVfmwChan
	cmp	r0, #0	@ temp.3251,
	beq	.L909	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L909:
	ldr	r0, [r5, #40]	@ temp.3255, s_pstVfmwChan
	cmp	r0, #0	@ temp.3255,
	beq	.L910	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L910:
	ldr	r0, [r5, #44]	@ temp.3259, s_pstVfmwChan
	cmp	r0, #0	@ temp.3259,
	beq	.L911	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L911:
	ldr	r0, [r5, #48]	@ temp.3263, s_pstVfmwChan
	cmp	r0, #0	@ temp.3263,
	beq	.L912	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L912:
	ldr	r0, [r5, #52]	@ temp.3267, s_pstVfmwChan
	cmp	r0, #0	@ temp.3267,
	beq	.L913	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L913:
	ldr	r0, [r5, #56]	@ temp.3271, s_pstVfmwChan
	cmp	r0, #0	@ temp.3271,
	beq	.L914	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L914:
	ldr	r0, [r5, #60]	@ D.54813, s_pstVfmwChan
	cmp	r0, #0	@ D.54813,
	beq	.L915	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L915:
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	mov	r0, #0	@,
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	.fnend
	.size	vfmw_read_proc_chn, .-vfmw_read_proc_chn
	.align	2
	.global	vfmw_read_proc_prn
	.type	vfmw_read_proc_prn, %function
vfmw_read_proc_prn:
	.fnstart
.LFB1644:
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
	movw	r6, #:lower16:.LC80	@ tmp137,
	movt	r6, #:upper16:.LC80	@ tmp137,
	mov	r4, r0	@ p, p
	movw	r1, #:lower16:.LC79	@,
	movt	r1, #:upper16:.LC79	@,
	bl	seq_printf	@
	mov	r1, r6	@, tmp137
	mov	r0, r4	@, p
	movw	r5, #:lower16:.LC90	@ tmp149,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC81	@,
	movt	r1, #:upper16:.LC81	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC82	@,
	movt	r1, #:upper16:.LC82	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC83	@,
	movt	r1, #:upper16:.LC83	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC84	@,
	movt	r1, #:upper16:.LC84	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC85	@,
	movt	r1, #:upper16:.LC85	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC86	@,
	movt	r1, #:upper16:.LC86	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC87	@,
	movt	r1, #:upper16:.LC87	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC88	@,
	movt	r1, #:upper16:.LC88	@,
	bl	seq_printf	@
	mov	r1, r6	@, tmp137
	mov	r0, r4	@, p
	movt	r5, #:upper16:.LC90	@ tmp149,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC89	@,
	movt	r1, #:upper16:.LC89	@,
	bl	seq_printf	@
	mov	r1, r6	@, tmp137
	mov	r0, r4	@, p
	bl	seq_printf	@
	mov	r1, r5	@, tmp149
	mov	r0, r4	@, p
	bl	seq_printf	@
	mov	r1, r5	@, tmp149
	mov	r0, r4	@, p
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC91	@,
	movt	r1, #:upper16:.LC91	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC92	@,
	movt	r1, #:upper16:.LC92	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC93	@,
	movt	r1, #:upper16:.LC93	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC94	@,
	movt	r1, #:upper16:.LC94	@,
	bl	seq_printf	@
	mov	r1, r6	@, tmp137
	mov	r0, r4	@, p
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC95	@,
	movt	r1, #:upper16:.LC95	@,
	bl	seq_printf	@
	mov	r1, r6	@, tmp137
	mov	r0, r4	@, p
	bl	seq_printf	@
	mov	r1, r5	@, tmp149
	mov	r0, r4	@, p
	bl	seq_printf	@
	mov	r1, r5	@, tmp149
	mov	r0, r4	@, p
	bl	seq_printf	@
	mov	r1, r5	@, tmp149
	mov	r0, r4	@, p
	bl	seq_printf	@
	mov	r1, r5	@, tmp149
	mov	r0, r4	@, p
	bl	seq_printf	@
	mov	r1, r5	@, tmp149
	mov	r0, r4	@, p
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC96	@,
	movt	r1, #:upper16:.LC96	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	mov	r1, r6	@, tmp137
	bl	seq_printf	@
	mov	r0, #0	@,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	vfmw_read_proc_prn, .-vfmw_read_proc_prn
	.align	2
	.global	vfmw_read_proc_dbg
	.type	vfmw_read_proc_dbg, %function
vfmw_read_proc_dbg:
	.fnstart
.LFB1643:
	@ args = 0, pretend = 0, frame = 0
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
	movw	r6, #:lower16:.LC98	@ tmp137,
	movw	r5, #:lower16:TracerPhyAddr	@ tmp139,
	movt	r6, #:upper16:.LC98	@ tmp137,
	movt	r5, #:upper16:TracerPhyAddr	@ tmp139,
	mov	r4, r0	@ p, p
	movw	r1, #:lower16:.LC97	@,
	movt	r1, #:upper16:.LC97	@,
	bl	seq_printf	@
	mov	r1, r6	@, tmp137
	ldr	r3, [r5, #0]	@, TracerPhyAddr
	mov	r0, r4	@, p
	movw	r2, #:lower16:.LC99	@,
	movt	r2, #:upper16:.LC99	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC100	@,
	movw	r2, #:lower16:.LC101	@,
	movt	r1, #:upper16:.LC100	@,
	movt	r2, #:upper16:.LC101	@,
	movw	r3, #:lower16:.LANCHOR2	@,
	movt	r3, #:upper16:.LANCHOR2	@,
	bl	seq_printf	@
	movw	ip, #:lower16:g_PrintEnable	@ tmp146,
	movt	ip, #:upper16:g_PrintEnable	@ tmp146,
	mov	r1, r6	@, tmp137
	mov	r0, r4	@, p
	movw	r2, #:lower16:.LC102	@,
	ldr	r3, [ip, #0]	@, g_PrintEnable
	movt	r2, #:upper16:.LC102	@,
	bl	seq_printf	@
	movw	r3, #:lower16:g_TraceCtrl	@ tmp150,
	movt	r3, #:upper16:g_TraceCtrl	@ tmp150,
	mov	r1, r6	@, tmp137
	mov	r0, r4	@, p
	movw	r2, #:lower16:.LC103	@,
	ldr	r3, [r3, #0]	@, g_TraceCtrl
	movt	r2, #:upper16:.LC103	@,
	bl	seq_printf	@
	movw	r5, #:lower16:.LC104	@ tmp152,
	movw	r2, #:lower16:g_TraceBsPeriod	@ tmp154,
	movt	r5, #:upper16:.LC104	@ tmp152,
	movt	r2, #:upper16:g_TraceBsPeriod	@ tmp154,
	mov	r0, r4	@, p
	mov	r1, r5	@, tmp152
	movw	r6, #:lower16:.LC80	@ tmp164,
	ldr	r3, [r2, #0]	@, g_TraceBsPeriod
	movw	r2, #:lower16:.LC105	@,
	movt	r2, #:upper16:.LC105	@,
	movt	r6, #:upper16:.LC80	@ tmp164,
	bl	seq_printf	@
	movw	ip, #:lower16:g_TraceFramePeriod	@ tmp158,
	movt	ip, #:upper16:g_TraceFramePeriod	@ tmp158,
	mov	r1, r5	@, tmp152
	mov	r0, r4	@, p
	movw	r2, #:lower16:.LC106	@,
	ldr	r3, [ip, #0]	@, g_TraceFramePeriod
	movt	r2, #:upper16:.LC106	@,
	bl	seq_printf	@
	movw	r3, #:lower16:g_TraceImgPeriod	@ tmp162,
	movt	r3, #:upper16:g_TraceImgPeriod	@ tmp162,
	mov	r1, r5	@, tmp152
	mov	r0, r4	@, p
	movw	r2, #:lower16:.LC107	@,
	ldr	r3, [r3, #0]	@, g_TraceImgPeriod
	movt	r2, #:upper16:.LC107	@,
	bl	seq_printf	@
	mov	r1, r6	@, tmp164
	mov	r0, r4	@, p
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC108	@,
	movt	r1, #:upper16:.LC108	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC109	@,
	movt	r1, #:upper16:.LC109	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC110	@,
	movt	r1, #:upper16:.LC110	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC111	@,
	movt	r1, #:upper16:.LC111	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC112	@,
	movt	r1, #:upper16:.LC112	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC113	@,
	movt	r1, #:upper16:.LC113	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC114	@,
	movt	r1, #:upper16:.LC114	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC115	@,
	movt	r1, #:upper16:.LC115	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC116	@,
	movt	r1, #:upper16:.LC116	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC117	@,
	movt	r1, #:upper16:.LC117	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC118	@,
	movt	r1, #:upper16:.LC118	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC119	@,
	movt	r1, #:upper16:.LC119	@,
	bl	seq_printf	@
	movw	ip, #:lower16:.LC121	@ tmp178,
	movt	ip, #:upper16:.LC121	@ tmp178,
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC120	@,
	movt	r1, #:upper16:.LC120	@,
	mov	r2, ip	@, tmp178
	mov	r3, ip	@, tmp2
	str	ip, [sp, #0]	@ tmp178,
	str	ip, [sp, #4]	@ tmp178,
	str	ip, [sp, #8]	@ tmp178,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC122	@,
	movt	r1, #:upper16:.LC122	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC123	@,
	movt	r1, #:upper16:.LC123	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC124	@,
	movt	r1, #:upper16:.LC124	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC125	@,
	movt	r1, #:upper16:.LC125	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC126	@,
	movt	r1, #:upper16:.LC126	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC127	@,
	movt	r1, #:upper16:.LC127	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC128	@,
	movt	r1, #:upper16:.LC128	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC129	@,
	movt	r1, #:upper16:.LC129	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC130	@,
	movt	r1, #:upper16:.LC130	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC131	@,
	movt	r1, #:upper16:.LC131	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC132	@,
	movt	r1, #:upper16:.LC132	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC133	@,
	movt	r1, #:upper16:.LC133	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC134	@,
	movt	r1, #:upper16:.LC134	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC135	@,
	movt	r1, #:upper16:.LC135	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC136	@,
	movt	r1, #:upper16:.LC136	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC137	@,
	movt	r1, #:upper16:.LC137	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC138	@,
	movt	r1, #:upper16:.LC138	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC139	@,
	movt	r1, #:upper16:.LC139	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC140	@,
	movt	r1, #:upper16:.LC140	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	mov	r1, r6	@, tmp164
	bl	seq_printf	@
	mov	r0, #0	@,
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	.fnend
	.size	vfmw_read_proc_dbg, .-vfmw_read_proc_dbg
	.align	2
	.global	vfmw_read_proc
	.type	vfmw_read_proc, %function
vfmw_read_proc:
	.fnstart
.LFB1642:
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
	movw	r4, #:lower16:.LC142	@ tmp137,
	movt	r4, #:upper16:.LC142	@ tmp137,
	mov	r6, r0	@ p, p
	movw	r1, #:lower16:.LC141	@,
	movw	r5, #:lower16:.LANCHOR0	@ tmp142,
	movt	r1, #:upper16:.LC141	@,
	movt	r5, #:upper16:.LANCHOR0	@ tmp142,
	bl	seq_printf	@
	mov	r1, r4	@, tmp137
	mov	r0, r6	@, p
	movw	r3, #:lower16:2015071001	@ tmp139,
	movw	r2, #:lower16:.LC143	@,
	movt	r3, #:upper16:2015071001	@,
	movt	r2, #:upper16:.LC143	@,
	bl	seq_printf	@
	ldr	r3, [r5, #68]	@, extra_ref
	mov	r1, r4	@, tmp137
	mov	r0, r6	@, p
	movw	r2, #:lower16:.LC144	@,
	movt	r2, #:upper16:.LC144	@,
	bl	seq_printf	@
	mov	r1, r4	@, tmp137
	ldr	r3, [r5, #72]	@, extra_disp
	mov	r0, r6	@, p
	movw	r2, #:lower16:.LC145	@,
	movt	r2, #:upper16:.LC145	@,
	bl	seq_printf	@
	mov	r1, r4	@, tmp137
	ldr	r3, [r5, #1368]	@, extra_cmd
	mov	r0, r6	@, p
	movw	r2, #:lower16:.LC146	@,
	movt	r2, #:upper16:.LC146	@,
	bl	seq_printf	@
	movw	r3, #:lower16:USE_FF_APT_EN	@ tmp154,
	movt	r3, #:upper16:USE_FF_APT_EN	@ tmp154,
	mov	r1, r4	@, tmp137
	mov	r0, r6	@, p
	movw	r2, #:lower16:.LC147	@,
	ldr	r3, [r3, #0]	@, USE_FF_APT_EN
	movt	r2, #:upper16:.LC147	@,
	bl	seq_printf	@
	mov	r0, r6	@, p
	mov	r1, r4	@, tmp137
	ldr	r3, [r5, #1372]	@, g_ResetCreateNewSave
	movw	r2, #:lower16:.LC148	@,
	movt	r2, #:upper16:.LC148	@,
	bl	seq_printf	@
	mov	r0, #0	@,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	vfmw_read_proc, .-vfmw_read_proc
	.align	2
	.global	vfmw_read_proc_priv
	.type	vfmw_read_proc_priv, %function
vfmw_read_proc_priv:
	.fnstart
.LFB1641:
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
	movw	r1, #:lower16:.LC149	@,
	mov	r4, r0	@ p, p
	movt	r1, #:upper16:.LC149	@,
	bl	seq_printf	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp274,
	mov	r0, r4	@, p
	movt	r5, #:upper16:.LANCHOR0	@ tmp274,
	movw	r1, #:lower16:.LC150	@,
	movw	r2, #:lower16:.LC151	@,
	movt	r1, #:upper16:.LC150	@,
	movt	r2, #:upper16:.LC151	@,
	movw	r3, #:lower16:2015071001	@,
	movt	r3, #:upper16:2015071001	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC152	@,
	movt	r1, #:upper16:.LC152	@,
	bl	seq_printf	@
	ldr	ip, [r5, #1388]	@ D.54688, <variable>.u32VaVdmLoad
	movw	r6, #:lower16:-858993459	@ tmp164,
	movt	r6, #:upper16:-858993459	@ tmp164,
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC153	@,
	umull	r2, r3, r6, ip	@, tmp163, tmp164, D.54688
	movt	r1, #:upper16:.LC153	@,
	movw	r2, #:lower16:.LC154	@,
	movt	r2, #:upper16:.LC154	@,
	mov	r3, r3, lsr #3	@ tmp162, tmp163,
	add	lr, r3, r3, asl #2	@, tmp170, tmp162, tmp162,
	sub	ip, ip, lr, asl #1	@ tmp172, D.54688, tmp170,
	str	ip, [sp, #0]	@ tmp172,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC155	@,
	movt	r1, #:upper16:.LC155	@,
	bl	seq_printf	@
	ldr	ip, [r5, #1452]	@ D.54696, <variable>.u32SaScdLoad
	mov	r2, #0	@,
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC156	@,
	movt	r1, #:upper16:.LC156	@,
	umull	lr, r3, r6, ip	@, tmp177, tmp164, D.54696
	mov	r3, r3, lsr #3	@ tmp176, tmp177,
	add	lr, r3, r3, asl #2	@, tmp184, tmp176, tmp176,
	sub	ip, ip, lr, asl #1	@ tmp186, D.54696, tmp184,
	str	ip, [sp, #0]	@ tmp186,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC157	@,
	movt	r1, #:upper16:.LC157	@,
	bl	seq_printf	@
	movw	r3, #:lower16:g_DspDrvState	@ tmp189,
	movt	r3, #:upper16:g_DspDrvState	@ tmp189,
	mov	r2, #0	@,
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC158	@,
	ldr	r3, [r3, #0]	@, g_DspDrvState
	movt	r1, #:upper16:.LC158	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC159	@,
	movt	r1, #:upper16:.LC159	@,
	bl	seq_printf	@
	ldr	r3, [r5, #0]	@ pChan, s_pstVfmwChan
	cmp	r3, #0	@ pChan,
	beq	.L924	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192364	@ tmp194,
	movt	r2, #:upper16:192364	@ tmp194,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #0	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L924:
	ldr	r3, [r5, #4]	@ pChan.3373, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3373,
	beq	.L925	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192364	@ tmp199,
	movt	r0, #:upper16:192364	@ tmp199,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #1	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L925:
	ldr	r3, [r5, #8]	@ pChan.3376, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3376,
	beq	.L926	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192364	@ tmp204,
	movt	r2, #:upper16:192364	@ tmp204,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #2	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L926:
	ldr	r3, [r5, #12]	@ pChan.3379, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3379,
	beq	.L927	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192364	@ tmp209,
	movt	r0, #:upper16:192364	@ tmp209,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #3	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L927:
	ldr	r3, [r5, #16]	@ pChan.3382, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3382,
	beq	.L928	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192364	@ tmp214,
	movt	r2, #:upper16:192364	@ tmp214,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #4	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L928:
	ldr	r3, [r5, #20]	@ pChan.3385, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3385,
	beq	.L929	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192364	@ tmp219,
	movt	r0, #:upper16:192364	@ tmp219,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #5	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L929:
	ldr	r3, [r5, #24]	@ pChan.3388, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3388,
	beq	.L930	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192364	@ tmp224,
	movt	r2, #:upper16:192364	@ tmp224,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #6	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L930:
	ldr	r3, [r5, #28]	@ pChan.3391, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3391,
	beq	.L931	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192364	@ tmp229,
	movt	r0, #:upper16:192364	@ tmp229,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #7	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L931:
	ldr	r3, [r5, #32]	@ pChan.3394, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3394,
	beq	.L932	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192364	@ tmp234,
	movt	r2, #:upper16:192364	@ tmp234,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #8	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L932:
	ldr	r3, [r5, #36]	@ pChan.3397, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3397,
	beq	.L933	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192364	@ tmp239,
	movt	r0, #:upper16:192364	@ tmp239,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #9	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L933:
	ldr	r3, [r5, #40]	@ pChan.3400, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3400,
	beq	.L934	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192364	@ tmp244,
	movt	r2, #:upper16:192364	@ tmp244,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #10	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L934:
	ldr	r3, [r5, #44]	@ pChan.3403, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3403,
	beq	.L935	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192364	@ tmp249,
	movt	r0, #:upper16:192364	@ tmp249,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #11	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L935:
	ldr	r3, [r5, #48]	@ pChan.3406, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3406,
	beq	.L936	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192364	@ tmp254,
	movt	r2, #:upper16:192364	@ tmp254,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #12	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L936:
	ldr	r3, [r5, #52]	@ pChan.3409, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3409,
	beq	.L937	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192364	@ tmp259,
	movt	r0, #:upper16:192364	@ tmp259,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #13	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L937:
	ldr	r3, [r5, #56]	@ pChan.3412, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3412,
	beq	.L938	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192364	@ tmp264,
	movt	r2, #:upper16:192364	@ tmp264,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #14	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L938:
	ldr	r3, [r5, #60]	@ pChan.3370, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3370,
	beq	.L939	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192364	@ tmp269,
	movt	r0, #:upper16:192364	@ tmp269,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #15	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L939:
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	mov	r0, #0	@,
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	.fnend
	.size	vfmw_read_proc_priv, .-vfmw_read_proc_priv
	.align	2
	.global	VCTRL_GetStreamSize
	.type	VCTRL_GetStreamSize, %function
VCTRL_GetStreamSize:
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
	cmp	r0, #15	@ ChanID,
	bhi	.L947	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r0, [r3, r0, asl #2]	@ D.50312, s_pstVfmwChan
	cmp	r0, #0	@ D.50312,
	beq	.L948	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r2, #1	@ <variable>.s32IsOpen,
	bne	.L949	@,
	add	r0, r0, #99328	@, D.50312,
	add	r0, r0, #696	@,,
	bl	GetSegStreamSize	@
	ldmfd	sp, {fp, sp, pc}	@
.L949:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1128	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC162	@,
	movt	r3, #:upper16:.LC162	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	ldmfd	sp, {fp, sp, pc}	@
.L947:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1126	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	ldmfd	sp, {fp, sp, pc}	@
.L948:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1127	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC161	@,
	movt	r3, #:upper16:.LC161	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetStreamSize, .-VCTRL_GetStreamSize
	.global	__aeabi_idiv
	.align	2
	.global	vfmw_read_proc_info
	.type	vfmw_read_proc_info, %function
vfmw_read_proc_info:
	.fnstart
.LFB1640:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #28
	sub	sp, sp, #28	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r1, #:lower16:g_pSmIISBase	@ tmp163,
	movt	r1, #:upper16:g_pSmIISBase	@ tmp163,
	movw	r5, #:lower16:.LANCHOR0	@ tmp262,
	movt	r5, #:upper16:.LANCHOR0	@ tmp262,
	movw	r3, #:lower16:s_pFspInst	@ tmp161,
	ldr	r2, [r1, #0]	@ g_pSmIISBase, g_pSmIISBase
	movt	r3, #:upper16:s_pFspInst	@ tmp161,
	ldr	sl, [r5, #1364]	@ chanID, g_CurProcChan
	mov	r4, r0	@ p, p
	ldr	r8, [r2, #40]	@ pInst, <variable>.pSmInstArray
	ldr	r7, [r3, sl, asl #2]	@ pFsp, s_pFspInst
	cmp	r8, #0	@ pInst,
	beq	.L951	@,
	movw	ip, #:lower16:190872	@ tmp164,
	movt	ip, #:upper16:190872	@ tmp164,
	ldr	r0, [r8, ip]	@ <variable>.Mode, <variable>.Mode
	cmp	r0, #0	@ <variable>.Mode,
	bne	.L981	@,
.L951:
	mov	r0, #0	@,
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L981:
	add	r6, r8, #200	@ D.54618, pInst,
	sub	r1, fp, #52	@,,
	mov	r0, r6	@, D.54618
	bl	GetRawStreamSize	@
	cmp	r0, #0	@,
	bne	.L982	@,
.L952:
	mov	r0, r6	@, D.54618
	sub	r1, fp, #48	@,,
	bl	GetRawStreamNum	@
	cmp	r0, #0	@,
	bne	.L983	@,
.L953:
	add	r6, r8, #98304	@ D.54626, pInst,
	sub	r1, fp, #60	@,,
	add	r6, r6, #224	@ D.54626, D.54626,
	mov	r0, r6	@, D.54626
	bl	GetSegStreamSize	@
	cmp	r0, #0	@,
	bne	.L984	@,
.L954:
	mov	r0, r6	@, D.54626
	sub	r1, fp, #56	@,,
	bl	GetSegStreamNum	@
	cmp	r0, #0	@,
	bne	.L985	@,
.L955:
	movw	lr, #:lower16:190716	@ tmp183,
	movt	lr, #:upper16:190716	@ tmp183,
	ldr	r8, [r8, lr]	@ BufSize, <variable>.StreamSegArray.SegBufSize
	cmp	r8, #0	@ BufSize,
	moveq	r9, r8	@ s32percent, BufSize
	bne	.L986	@,
.L957:
	mov	r2, sl	@, chanID
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC164	@,
	movt	r1, #:upper16:.LC164	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC150	@,
	movw	r2, #:lower16:.LC151	@,
	movt	r1, #:upper16:.LC150	@,
	movt	r2, #:upper16:.LC151	@,
	movw	r3, #:lower16:2015071001	@,
	movt	r3, #:upper16:2015071001	@,
	bl	seq_printf	@
	mov	r3, sl	@, chanID
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC150	@,
	movw	r2, #:lower16:.LC165	@,
	movt	r1, #:upper16:.LC150	@,
	movt	r2, #:upper16:.LC165	@,
	movw	r6, #:lower16:-858993459	@ tmp214,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC166	@,
	movt	r1, #:upper16:.LC166	@,
	bl	seq_printf	@
	ldr	ip, [fp, #-48]	@ RawNum, RawNum
	ldr	r3, [fp, #-52]	@, RawSize
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC167	@,
	movw	r2, #:lower16:.LC168	@,
	movt	r1, #:upper16:.LC167	@,
	movt	r2, #:upper16:.LC168	@,
	str	ip, [sp, #0]	@ RawNum,
	bl	seq_printf	@
	ldr	ip, [fp, #-56]	@ SegNum, SegNum
	mov	r0, r4	@, p
	ldr	r3, [fp, #-60]	@, SegSize
	movw	r1, #:lower16:.LC167	@,
	movw	r2, #:lower16:.LC169	@,
	movt	r1, #:upper16:.LC167	@,
	movt	r2, #:upper16:.LC169	@,
	str	ip, [sp, #0]	@ SegNum,
	bl	seq_printf	@
	ldr	ip, [fp, #-60]	@ SegSize, SegSize
	mov	r3, r8	@, BufSize
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC170	@,
	movw	r2, #:lower16:.LC171	@,
	movt	r1, #:upper16:.LC170	@,
	movt	r2, #:upper16:.LC171	@,
	str	ip, [sp, #0]	@ SegSize,
	movt	r6, #:upper16:-858993459	@ tmp214,
	str	r9, [sp, #4]	@ s32percent,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC172	@,
	movt	r1, #:upper16:.LC172	@,
	bl	seq_printf	@
	ldr	lr, [r5, #1388]	@ D.54643, <variable>.u32VaVdmLoad
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC153	@,
	movw	r2, #:lower16:.LC154	@,
	movt	r1, #:upper16:.LC153	@,
	umull	ip, r3, r6, lr	@, tmp213, tmp214, D.54643
	movt	r2, #:upper16:.LC154	@,
	mov	r3, r3, lsr #3	@ tmp212, tmp213,
	add	ip, r3, r3, asl #2	@, tmp220, tmp212, tmp212,
	sub	ip, lr, ip, asl #1	@ tmp222, D.54643, tmp220,
	str	ip, [sp, #0]	@ tmp222,
	bl	seq_printf	@
	ldr	ip, [r7, #72]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stInstCfg.s32DecFsHeight
	ldr	r3, [r7, #68]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stInstCfg.s32DecFsWidth
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC173	@,
	movw	r2, #:lower16:.LC174	@,
	movt	r1, #:upper16:.LC173	@,
	movt	r2, #:upper16:.LC174	@,
	str	ip, [sp, #0]	@ <variable>.stInstCfg.s32DecFsHeight,
	bl	seq_printf	@
	ldr	ip, [r7, #88]	@ <variable>.stInstCfg.s32DispFsHeight, <variable>.stInstCfg.s32DispFsHeight
	mov	r0, r4	@, p
	ldr	r3, [r7, #84]	@ <variable>.stInstCfg.s32DispFsWidth, <variable>.stInstCfg.s32DispFsWidth
	movw	r1, #:lower16:.LC173	@,
	movw	r2, #:lower16:.LC175	@,
	movt	r1, #:upper16:.LC173	@,
	movt	r2, #:upper16:.LC175	@,
	str	ip, [sp, #0]	@ <variable>.stInstCfg.s32DispFsHeight,
	bl	seq_printf	@
	ldr	ip, [r5, #1468]	@ D.54655, <variable>.u32FrFrameRate
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC176	@,
	movw	r2, #:lower16:.LC177	@,
	movt	r1, #:upper16:.LC176	@,
	umull	lr, r3, r6, ip	@, tmp235, tmp214, D.54655
	movt	r2, #:upper16:.LC177	@,
	mov	r3, r3, lsr #3	@ tmp234, tmp235,
	add	r6, r3, r3, asl #2	@, tmp242, tmp234, tmp234,
	sub	ip, ip, r6, asl #1	@ tmp244, D.54655, tmp242,
	str	ip, [sp, #0]	@ tmp244,
	bl	seq_printf	@
	ldrb	ip, [r7, #10]	@ zero_extendqisi2	@ D.54664, <variable>.s32DecFsNum
	sxtb	r6, ip	@ D.54665, D.54664
	cmp	r6, #0	@ D.54665,
	movle	r5, #0	@ usedFrameNum,
	ble	.L959	@,
	add	r3, r7, #34816	@ ivtmp.3466, pFsp,
	rsb	r0, r6, r6, asl #4	@, tmp249, D.54665, D.54665,
	mov	r5, #0	@ usedFrameNum,
	ldrsb	r1, [r3, #158]!	@ <variable>.DispState, <variable>.DispState
	mov	lr, r0, asl #2	@ D.58889, tmp249,
	sub	r2, lr, #60	@ tmp266, D.58889,
	cmp	r1, #3	@ <variable>.DispState,
	ubfx	r1, r2, #2, #1	@ tmp270, tmp266,,
	beq	.L967	@,
	ldrsb	r2, [r3, #-2]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	r2, #1	@ <variable>.IsDecRef,
	beq	.L967	@,
.L968:
	mov	r2, #60	@ ivtmp.3467,
	cmp	r2, lr	@ ivtmp.3467, D.58889
	add	r3, r3, r2	@ ivtmp.3466, ivtmp.3466,
	beq	.L959	@,
	cmp	r1, #0	@ tmp270,
	beq	.L962	@,
	ldrsb	r1, [r3, #0]	@ <variable>.DispState, <variable>.DispState
	cmp	r1, #3	@ <variable>.DispState,
	beq	.L970	@,
	ldrsb	r0, [r3, #-2]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	r0, #1	@ <variable>.IsDecRef,
	beq	.L970	@,
	add	r2, r2, #60	@ ivtmp.3467, ivtmp.3467,
	add	r3, r3, #60	@ ivtmp.3466, ivtmp.3466,
	cmp	r2, lr	@ ivtmp.3467, D.58889
	bne	.L962	@,
.L959:
	cmp	ip, #0	@ D.54664,
	bne	.L987	@,
.L964:
	mov	r3, r6	@, D.54665
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC170	@,
	movw	r2, #:lower16:.LC178	@,
	movt	r1, #:upper16:.LC170	@,
	movt	r2, #:upper16:.LC178	@,
	stmia	sp, {r5, ip}	@ phole stm
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC179	@,
	movt	r1, #:upper16:.LC179	@,
	bl	seq_printf	@
	b	.L951	@
.L988:
	ldrsb	r0, [r3, #-2]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	r0, #1	@ <variable>.IsDecRef,
	beq	.L960	@,
	ldrsb	r3, [r3, #60]	@ <variable>.DispState, <variable>.DispState
	cmp	r3, #3	@ <variable>.DispState,
	beq	.L974	@,
.L979:
	ldrsb	r3, [r1, #-2]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	r3, #1	@ <variable>.IsDecRef,
	beq	.L974	@,
.L975:
	add	r2, r2, #60	@ ivtmp.3467, tmp272,
	add	r3, r1, #60	@ ivtmp.3466, tmp271,
	cmp	r2, lr	@ ivtmp.3467, D.58889
	beq	.L959	@,
.L962:
	ldrsb	r0, [r3, #0]	@ <variable>.DispState, <variable>.DispState
	add	r2, r2, #60	@ tmp272, ivtmp.3467,
	add	r1, r3, #60	@ tmp271, ivtmp.3466,
	cmp	r0, #3	@ <variable>.DispState,
	bne	.L988	@,
.L960:
	ldrsb	r3, [r3, #60]	@ <variable>.DispState, <variable>.DispState
	add	r5, r5, #1	@ usedFrameNum, usedFrameNum,
	cmp	r3, #3	@ <variable>.DispState,
	bne	.L979	@,
.L974:
	add	r5, r5, #1	@ usedFrameNum, usedFrameNum,
	b	.L975	@
.L987:
	mov	lr, #100	@ tmp254,
	mov	r1, r6	@, D.54665
	mul	r0, lr, r5	@, tmp254, usedFrameNum
	bl	__aeabi_idiv	@
	mov	ip, r0	@ s32percent.3470,
	b	.L964	@
.L986:
	ldr	r3, [fp, #-60]	@ SegSize, SegSize
	mov	r9, #100	@ tmp186,
	mov	r1, r8	@, BufSize
	mul	r0, r9, r3	@, tmp186, SegSize
	bl	__aeabi_idiv	@
	mov	r9, r0	@ s32percent,
	b	.L957	@
.L967:
	mov	r5, #1	@ usedFrameNum,
	b	.L968	@
.L970:
	add	r2, r2, #60	@ ivtmp.3467, ivtmp.3467,
	add	r5, r5, #1	@ usedFrameNum, usedFrameNum,
	cmp	r2, lr	@ ivtmp.3467, D.58889
	add	r3, r3, #60	@ ivtmp.3466, ivtmp.3466,
	bne	.L962	@,
	b	.L959	@
.L985:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L989	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #8807	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	b	.L955	@
.L984:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L989	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #8802	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	b	.L954	@
.L983:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L989	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #8797	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	b	.L953	@
.L982:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L989	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #8792	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	b	.L952	@
.L990:
	.align	2
.L989:
	.word	.LANCHOR1+188
	.fnend
	.size	vfmw_read_proc_info, .-vfmw_read_proc_info
	.align	2
	.global	VCTRL_OutputLastFrame
	.type	VCTRL_OutputLastFrame, %function
VCTRL_OutputLastFrame:
	.fnstart
.LFB1633:
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
	movw	r1, #:lower16:.LANCHOR0	@ tmp137,
	movt	r1, #:upper16:.LANCHOR0	@ tmp137,
	mov	r5, r0	@ ChanId, ChanId
	movw	r2, #:lower16:251576	@ tmp138,
	movt	r2, #:upper16:251576	@ tmp138,
	ldr	r0, [r1, r0, asl #2]	@ D.54402, s_pstVfmwChan
	ldr	r3, [r0, r2]	@ <variable>.stSynCtx.eVidStd, <variable>.stSynCtx.eVidStd
	cmp	r3, #16	@ <variable>.stSynCtx.eVidStd,
	ldrls	pc, [pc, r3, asl #2]	@ <variable>.stSynCtx.eVidStd
	b	.L992	@
.L1005:
	.word	.L993
	.word	.L994
	.word	.L995
	.word	.L996
	.word	.L992
	.word	.L997
	.word	.L998
	.word	.L992
	.word	.L999
	.word	.L1000
	.word	.L1001
	.word	.L1001
	.word	.L1001
	.word	.L1002
	.word	.L992
	.word	.L1003
	.word	.L1004
.L1004:
	add	lr, r0, #250880	@, D.54402,
	add	r0, lr, #704	@,,
	bl	HEVCDEC_GetRemainImg	@
	mov	r4, r0	@ ret,
.L1006:
	cmn	r4, #1	@ ret,
	beq	.L1008	@,
	cmp	r4, #0	@ ret,
	bne	.L1016	@,
	mov	r0, r5	@, ChanId
	mov	r1, r4	@, ret
	bl	VCTRL_ReportLastFrame	@
	movw	r1, #:lower16:.LC181	@,
	mov	r0, #2	@,
	movt	r1, #:upper16:.LC181	@,
	bl	dprint_vfmw	@
.L1010:
	mov	r0, r4	@, ret
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L992:
	mvn	r4, #0	@ ret,
.L1008:
	mov	r0, r5	@, ChanId
	mov	r1, #1	@,
	bl	VCTRL_ReportLastFrame	@
	movw	r1, #:lower16:.LC180	@,
	mov	r0, #2	@,
	movt	r1, #:upper16:.LC180	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, ret
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L993:
	add	ip, r0, #250880	@, D.54402,
	add	r0, ip, #704	@,,
	bl	H264DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L1006	@
.L994:
	add	r4, r0, #250880	@, D.54402,
	add	r0, r4, #704	@,,
	bl	VC1DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L1006	@
.L995:
	add	r4, r0, #250880	@, D.54402,
	add	r0, r4, #704	@,,
	bl	MPEG4DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L1006	@
.L996:
	add	r0, r0, #250880	@, D.54402,
	add	r0, r0, #704	@,,
	bl	MPEG2DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L1006	@
.L997:
	add	r0, r0, #250880	@, D.54402,
	add	r0, r0, #704	@,,
	bl	DIVX3DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L1006	@
.L998:
	add	r3, r0, #250880	@, D.54402,
	add	r0, r3, #704	@,,
	bl	AVSDEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L1006	@
.L999:
	add	r2, r0, #250880	@, D.54402,
	add	r0, r2, #704	@,,
	bl	REAL8DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L1006	@
.L1000:
	add	r1, r0, #250880	@, D.54402,
	add	r0, r1, #704	@,,
	bl	REAL9DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L1006	@
.L1001:
	add	ip, r0, #250880	@, D.54402,
	add	r0, ip, #704	@,,
	bl	VP6DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L1006	@
.L1002:
	add	lr, r0, #250880	@, D.54402,
	add	r0, lr, #704	@,,
	bl	VP8DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L1006	@
.L1003:
	add	r3, r0, #250880	@, D.54402,
	add	r0, r3, #704	@,,
	bl	MVC_DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L1006	@
.L1016:
	movw	r2, #:lower16:g_chipID	@ tmp166,
	movt	r2, #:upper16:g_chipID	@ tmp166,
	ldr	r3, [r2, #0]	@ g_chipID, g_chipID
	cmp	r3, #12	@ g_chipID,
	bgt	.L1013	@,
	cmp	r3, #8	@ g_chipID,
	bge	.L1012	@,
	cmp	r3, #0	@ g_chipID,
	blt	.L1010	@,
	cmp	r3, #5	@ g_chipID,
	bgt	.L1017	@,
	mov	r0, r5	@, ChanId
	mov	r1, r4	@, ret
	bl	VCTRL_ReportLastFrame	@
	sub	r2, r4, #2	@, ret,
	movw	r1, #:lower16:.LC182	@,
	mov	r0, #2	@,
	movt	r1, #:upper16:.LC182	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, ret
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1013:
	cmp	r3, #51	@ g_chipID,
	blt	.L1010	@,
	cmp	r3, #52	@ g_chipID,
	bgt	.L1018	@,
.L1012:
	mov	r0, r5	@, ChanId
	mov	r1, r4	@, ret
	bl	VCTRL_ReportLastFrame	@
	sub	r2, r4, #2	@, ret,
	movw	r1, #:lower16:.LC182	@,
	mov	r0, #2	@,
	movt	r1, #:upper16:.LC182	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, ret
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1018:
	sub	r1, r3, #100	@ tmp168, g_chipID,
	cmp	r1, #1	@ tmp168,
	bhi	.L1010	@,
	b	.L1012	@
.L1017:
	cmp	r3, #6	@ g_chipID,
	bne	.L1010	@,
	b	.L1012	@
	.fnend
	.size	VCTRL_OutputLastFrame, .-VCTRL_OutputLastFrame
	.align	2
	.global	VCTRL_RlsAllFrameNode
	.type	VCTRL_RlsAllFrameNode, %function
VCTRL_RlsAllFrameNode:
	.fnstart
.LFB1563:
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
	mov	r8, #0	@ i,
	movw	r5, #:lower16:.LANCHOR0	@ tmp199,
	mov	r6, r0	@ ChanID, ChanID
	movt	r5, #:upper16:.LANCHOR0	@ tmp199,
	mov	r0, r8	@ s32Ret, i
	b	.L1022	@
.L1021:
	add	r2, r9, r8	@ tmp166, tmp203, i
	mov	r8, r2, asl #2	@ tmp167, tmp166,
	add	r1, r8, sl	@ tmp168, tmp167, D.50498
	add	r0, r1, #248832	@ tmp177, tmp168,
	add	lr, r0, #456	@ tmp177, tmp177,
	add	sl, r0, #464	@ tmp169, tmp169,
	ldr	r1, [lr, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldmia	sl, {r0, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
	ldr	r3, [r5, r6, asl #2]	@ tmp188, s_pstVfmwChan
	mvn	r1, #0	@,
	add	ip, r8, r3	@ tmp194, tmp167, tmp188
	add	r2, ip, #248832	@ tmp195, tmp194,
	add	r8, r2, #472	@ tmp195, tmp195,
	strb	r1, [r8, #0]	@, <variable>.u8BufferNodeState
.L1020:
	ldr	r8, [r5, r6, asl #2]	@ D.50498, s_pstVfmwChan
	add	r1, r7, r4	@ tmp213, tmp212, tmp208
	add	r2, r8, r1, asl #2	@, tmp215, D.50498, tmp213,
	add	r3, r2, #248832	@ tmp216, tmp215,
	add	ip, r3, #472	@ tmp216, tmp216,
	ldrb	r3, [ip, #0]	@ zero_extendqisi2	@ D.50500, <variable>.u8BufferNodeState
	cmp	r3, #255	@ D.50500,
	beq	.L1026	@,
	cmp	r3, #1	@ D.50500,
	beq	.L1030	@,
.L1027:
	add	r2, r7, r4	@ tmp219, tmp212, tmp208
	mov	r7, r2, asl #2	@ tmp220, tmp219,
	add	r8, r7, r8	@ tmp221, tmp220, D.50498
	add	r3, r8, #248832	@ tmp225, tmp221,
	mvn	r8, #0	@,
	add	lr, r3, #464	@ tmp222, tmp222,
	add	r0, r3, #456	@ tmp225, tmp225,
	ldr	r2, [lr, #4]	@, <variable>.stFrameBuffer.Length
	ldr	r1, [r0, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldr	r0, [lr, #0]	@, <variable>.stFrameBuffer.PhyAddr
	bl	MEM_DelMemRecord	@
	ldr	ip, [r5, r6, asl #2]	@ tmp228, s_pstVfmwChan
	add	r2, r7, ip	@ tmp230, tmp220, tmp228
	add	r7, r2, #248832	@ tmp231, tmp230,
	add	r7, r7, #472	@ tmp231, tmp231,
	strb	r8, [r7, #0]	@, <variable>.u8BufferNodeState
.L1026:
	add	r8, r4, #1	@ i, tmp208,
	cmp	r8, #64	@ i,
	beq	.L1032	@,
.L1022:
	mov	r9, r8, asl #2	@ tmp203, i,
	ldr	sl, [r5, r6, asl #2]	@ D.50498, s_pstVfmwChan
	add	r2, r9, r8	@ tmp143, tmp203, i
	add	r4, r8, #1	@ tmp208, i,
	add	r2, sl, r2, asl #2	@, tmp145, D.50498, tmp143,
	mov	r7, r4, asl #2	@ tmp212, tmp208,
	add	r1, r2, #248832	@ tmp146, tmp145,
	add	r3, r1, #472	@ tmp146, tmp146,
	ldrb	r3, [r3, #0]	@ zero_extendqisi2	@ D.50500, <variable>.u8BufferNodeState
	cmp	r3, #255	@ D.50500,
	beq	.L1020	@,
	cmp	r3, #1	@ D.50500,
	bne	.L1021	@,
	add	r0, r2, #248832	@ tmp161, tmp145,
	add	ip, r0, #456	@ tmp161, tmp161,
	add	lr, r0, #464	@ tmp153, tmp153,
	ldr	r1, [ip, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldr	r0, [lr, #0]	@, <variable>.stFrameBuffer.PhyAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1021	@
.L1030:
	add	r0, r2, #248832	@ tmp235, tmp215,
	add	ip, r0, #456	@ tmp235, tmp235,
	add	lr, r0, #464	@ tmp233, tmp233,
	ldr	r1, [ip, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldr	r0, [lr, #0]	@, <variable>.stFrameBuffer.PhyAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1027	@
.L1032:
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	.fnend
	.size	VCTRL_RlsAllFrameNode, .-VCTRL_RlsAllFrameNode
	.align	2
	.type	VCTRL_AllocMemPre, %function
VCTRL_AllocMemPre:
	.fnstart
.LFB1663:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #28
	sub	sp, sp, #28	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r8, #:lower16:.LANCHOR0	@ tmp249,
	movt	r8, #:upper16:.LANCHOR0	@ tmp249,
	mov	r5, r1	@ s32FrmNum, s32FrmNum
	movw	r3, #:lower16:249256	@ tmp150,
	movt	r3, #:upper16:249256	@ tmp150,
	ldr	r2, [r8, r0, asl #2]	@ prephitmp.3558, s_pstVfmwChan
	mov	r4, r0	@ ChanID, ChanID
	ldr	r1, [r2, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	str	r1, [fp, #-52]	@, %sfp
	ldr	ip, [r2, #220]	@, <variable>.stChanMem_vdh.VirAddr
	cmp	ip, #0	@,
	cmpne	r1, #0	@,,
	str	ip, [fp, #-48]	@, %sfp
	ldr	r9, [r2, r3]	@ s32FrameSize, <variable>.s32CurFsSize
	beq	.L1034	@,
	cmp	r5, #63	@ s32FrmNum,
	bgt	.L1034	@,
	mov	sl, #0	@ ivtmp.3584,
	str	sl, [fp, #-56]	@ ivtmp.3584, %sfp
	mov	r7, sl	@ s32AllocedFrameNum, ivtmp.3584
	mov	r6, sl	@ i, ivtmp.3584
	b	.L1039	@
.L1035:
	cmp	r5, r7	@ s32FrmNum, s32AllocedFrameNum
	ble	.L1037	@,
	add	r6, r6, #1	@ i, i,
	add	ip, sl, r9	@ ivtmp.3584, ivtmp.3584, s32FrameSize
	cmp	r6, #64	@ i,
	mov	sl, r6	@ tmp252, i
	beq	.L1052	@,
.L1038:
	add	r1, r6, r6, asl #2	@, tmp259, tmp252, tmp252,
	ldr	r0, [r8, r4, asl #2]	@ prephitmp.3558, s_pstVfmwChan
	cmp	r7, r5	@ s32AllocedFrameNum, s32FrmNum
	movge	r3, #0	@, prephitmp.3560
	movlt	r3, #1	@, prephitmp.3560
	mov	r1, r1, asl #2	@ tmp260, tmp259,
	add	r0, r1, r0	@ tmp261, tmp260, prephitmp.3558
	add	r2, r0, #248832	@ tmp262, tmp261,
	add	r2, r2, #472	@ tmp262, tmp262,
	ldrb	r2, [r2, #0]	@ zero_extendqisi2	@ <variable>.u8BufferNodeState, <variable>.u8BufferNodeState
	cmp	r2, #255	@ <variable>.u8BufferNodeState,
	movne	r2, #0	@, tmp267
	andeq	r2, r3, #1	@,, tmp267, prephitmp.3560
	cmp	r2, #0	@ tmp267,
	bne	.L1053	@,
	cmp	r5, r7	@ s32FrmNum, s32AllocedFrameNum
	ble	.L1037	@,
.L1048:
	add	r6, sl, #1	@ i, tmp252,
	ldr	r0, [r8, r4, asl #2]	@ prephitmp.3558, s_pstVfmwChan
	cmp	r7, r5	@ s32AllocedFrameNum, s32FrmNum
	movge	r3, #0	@, prephitmp.3560
	movlt	r3, #1	@, prephitmp.3560
	add	ip, ip, r9	@ ivtmp.3584, ivtmp.3584, s32FrameSize
	add	r1, r6, r6, asl #2	@, tmp294, i, i,
	mov	r1, r1, asl #2	@ tmp295, tmp294,
	add	r0, r1, r0	@ tmp296, tmp295, prephitmp.3558
	add	r2, r0, #248832	@ tmp297, tmp296,
	add	r2, r2, #472	@ tmp297, tmp297,
	ldrb	r2, [r2, #0]	@ zero_extendqisi2	@ <variable>.u8BufferNodeState, <variable>.u8BufferNodeState
	cmp	r2, #255	@ <variable>.u8BufferNodeState,
	movne	r2, #0	@, tmp302
	andeq	r2, r3, #1	@,, tmp302, prephitmp.3560
	cmp	r2, #0	@ tmp302,
	bne	.L1049	@,
	cmp	r5, r7	@ s32FrmNum, s32AllocedFrameNum
	ble	.L1037	@,
.L1050:
	ldr	r2, [r8, r4, asl #2]	@ prephitmp.3558, s_pstVfmwChan
	add	r6, sl, #2	@ i, tmp252,
	add	sl, ip, r9	@ ivtmp.3584, ivtmp.3584, s32FrameSize
.L1039:
	add	r0, r6, r6, asl #2	@, tmp163, i, i,
	cmp	r7, r5	@ s32AllocedFrameNum, s32FrmNum
	movge	r3, #0	@, prephitmp.3560
	movlt	r3, #1	@, prephitmp.3560
	mov	r0, r0, asl #2	@ tmp164, tmp163,
	add	r2, r0, r2	@ tmp165, tmp164, prephitmp.3558
	add	ip, r2, #248832	@ tmp166, tmp165,
	add	r1, ip, #472	@ tmp166, tmp166,
	ldrb	ip, [r1, #0]	@ zero_extendqisi2	@ <variable>.u8BufferNodeState, <variable>.u8BufferNodeState
	cmp	ip, #255	@ <variable>.u8BufferNodeState,
	movne	r1, #0	@, tmp172
	andeq	r1, r3, #1	@,, tmp172, prephitmp.3560
	cmp	r1, #0	@ tmp172,
	beq	.L1035	@,
	add	ip, r2, #248832	@ tmp179, tmp165,
	ldr	lr, [fp, #-52]	@, %sfp
	add	r2, ip, #464	@ tmp179, tmp179,
	ldr	r1, [fp, #-48]	@, %sfp
	add	r3, sl, lr	@ tmp180, ivtmp.3584,
	add	r6, r6, #1	@ i, i,
	str	r3, [r2, #0]	@ tmp180, <variable>.stFrameBuffer.PhyAddr
	add	lr, sl, r1	@ tmp190, ivtmp.3584,
	ldr	ip, [r8, r4, asl #2]	@ tmp182, s_pstVfmwChan
	add	r7, r7, #1	@ s32AllocedFrameNum, s32AllocedFrameNum,
	add	r1, r0, ip	@ tmp188, tmp164, tmp182
	add	r2, r1, #248832	@ tmp189, tmp188,
	add	r3, r2, #456	@ tmp189, tmp189,
	str	lr, [r3, #4]	@ tmp190, <variable>.stFrameBuffer.VirAddr
	ldr	ip, [r8, r4, asl #2]	@ tmp192, s_pstVfmwChan
	add	r1, r0, ip	@ tmp198, tmp164, tmp192
	add	r2, r1, #248832	@ tmp199, tmp198,
	add	r3, r2, #464	@ tmp199, tmp199,
	mov	r2, #0	@,
	str	r9, [r3, #4]	@ s32FrameSize, <variable>.stFrameBuffer.Length
	ldr	lr, [r8, r4, asl #2]	@ tmp201, s_pstVfmwChan
	add	ip, r0, lr	@ tmp207, tmp164, tmp201
	add	r1, ip, #248832	@ tmp208, tmp207,
	add	r3, r1, #472	@ tmp208, tmp208,
	strb	r2, [r3, #0]	@, <variable>.u8BufferNodeState
	ldr	lr, [r8, r4, asl #2]	@ temp.3590, s_pstVfmwChan
	add	ip, r0, lr	@ tmp217, tmp164, temp.3590
	add	r2, ip, #248832	@ tmp226, tmp217,
	add	lr, r2, #464	@ tmp218, tmp218,
	add	r3, r2, #456	@ tmp226, tmp226,
	ldmia	lr, {r0, r2}	@ phole ldm
	ldr	r1, [r3, #4]	@, <variable>.stFrameBuffer.VirAddr
	bl	MEM_AddMemRecord	@
	cmp	r6, #64	@ i,
	add	ip, sl, r9	@ ivtmp.3584, ivtmp.3584, s32FrameSize
	mov	sl, r6	@ tmp252, i
	str	r0, [fp, #-56]	@, %sfp
	bne	.L1038	@,
.L1052:
	cmp	r7, r5	@ s32AllocedFrameNum, s32FrmNum
	movge	r3, #0	@, prephitmp.3560
	movlt	r3, #1	@, prephitmp.3560
.L1037:
	cmp	r6, #64	@ i,
	movne	r3, #0	@, tmp244
	andeq	r3, r3, #1	@,, tmp244, prephitmp.3560
	cmp	r3, #0	@ tmp244,
	bne	.L1054	@,
.L1040:
	ldr	r0, [fp, #-56]	@, %sfp
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1053:
	ldr	r2, [fp, #-52]	@, %sfp
	add	r6, r0, #248832	@ tmp268, tmp261,
	ldr	lr, [fp, #-48]	@, %sfp
	add	r7, r7, #1	@ s32AllocedFrameNum, s32AllocedFrameNum,
	add	r3, ip, r2	@ tmp269, ivtmp.3584,
	add	r2, r6, #464	@ tmp268, tmp268,
	add	r6, ip, lr	@ tmp273, ivtmp.3584,
	str	r3, [r2, #0]	@ tmp269, <variable>.stFrameBuffer.PhyAddr
	ldr	r0, [r8, r4, asl #2]	@ tmp270, s_pstVfmwChan
	add	r2, r1, r0	@ tmp271, tmp260, tmp270
	add	lr, r2, #248832	@ tmp272, tmp271,
	add	r3, lr, #456	@ tmp272, tmp272,
	str	r6, [r3, #4]	@ tmp273, <variable>.stFrameBuffer.VirAddr
	ldr	r0, [r8, r4, asl #2]	@ tmp274, s_pstVfmwChan
	add	r2, r1, r0	@ tmp275, tmp260, tmp274
	add	lr, r2, #248832	@ tmp276, tmp275,
	add	r6, lr, #464	@ tmp276, tmp276,
	str	r9, [r6, #4]	@ s32FrameSize, <variable>.stFrameBuffer.Length
	mov	r6, #0	@,
	ldr	r3, [r8, r4, asl #2]	@ tmp277, s_pstVfmwChan
	add	r0, r1, r3	@ tmp278, tmp260, tmp277
	add	r2, r0, #248832	@ tmp279, tmp278,
	add	lr, r2, #472	@ tmp279, tmp279,
	strb	r6, [lr, #0]	@, <variable>.u8BufferNodeState
	ldr	r3, [r8, r4, asl #2]	@ temp.3590, s_pstVfmwChan
	add	r1, r1, r3	@ tmp282, tmp260, temp.3590
	add	r2, r1, #248832	@ tmp285, tmp282,
	add	lr, r2, #456	@ tmp285, tmp285,
	add	r6, r2, #464	@ tmp283, tmp283,
	ldr	r1, [lr, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldmia	r6, {r0, r2}	@ phole ldm
	str	ip, [fp, #-60]	@,
	bl	MEM_AddMemRecord	@
	ldr	ip, [fp, #-60]	@,
	str	r0, [fp, #-56]	@, %sfp
	b	.L1048	@
.L1049:
	ldr	r2, [fp, #-52]	@, %sfp
	add	r6, r0, #248832	@ tmp303, tmp296,
	ldr	lr, [fp, #-48]	@, %sfp
	add	r7, r7, #1	@ s32AllocedFrameNum, s32AllocedFrameNum,
	add	r3, ip, r2	@ tmp304, ivtmp.3584,
	add	r2, r6, #464	@ tmp303, tmp303,
	add	r6, ip, lr	@ tmp308, ivtmp.3584,
	str	r3, [r2, #0]	@ tmp304, <variable>.stFrameBuffer.PhyAddr
	ldr	r0, [r8, r4, asl #2]	@ tmp305, s_pstVfmwChan
	add	r2, r1, r0	@ tmp306, tmp295, tmp305
	add	lr, r2, #248832	@ tmp307, tmp306,
	add	r3, lr, #456	@ tmp307, tmp307,
	str	r6, [r3, #4]	@ tmp308, <variable>.stFrameBuffer.VirAddr
	ldr	r0, [r8, r4, asl #2]	@ tmp309, s_pstVfmwChan
	add	r2, r1, r0	@ tmp310, tmp295, tmp309
	add	r6, r2, #248832	@ tmp311, tmp310,
	add	lr, r6, #464	@ tmp311, tmp311,
	str	r9, [lr, #4]	@ s32FrameSize, <variable>.stFrameBuffer.Length
	mov	lr, #0	@,
	ldr	r3, [r8, r4, asl #2]	@ tmp312, s_pstVfmwChan
	add	r0, r1, r3	@ tmp313, tmp295, tmp312
	add	r2, r0, #248832	@ tmp314, tmp313,
	add	r6, r2, #472	@ tmp314, tmp314,
	strb	lr, [r6, #0]	@, <variable>.u8BufferNodeState
	ldr	r3, [r8, r4, asl #2]	@ temp.3590, s_pstVfmwChan
	add	r0, r1, r3	@ tmp317, tmp295, temp.3590
	add	r6, r0, #248832	@ tmp320, tmp317,
	add	r3, r6, #464	@ tmp318, tmp318,
	add	lr, r6, #456	@ tmp320, tmp320,
	ldr	r2, [r3, #4]	@, <variable>.stFrameBuffer.Length
	ldr	r1, [lr, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldr	r0, [r3, #0]	@, <variable>.stFrameBuffer.PhyAddr
	str	ip, [fp, #-60]	@,
	bl	MEM_AddMemRecord	@
	ldr	ip, [fp, #-60]	@,
	str	r0, [fp, #-56]	@, %sfp
	b	.L1050	@
.L1034:
	ldr	r3, [fp, #-48]	@, %sfp
	mov	r0, #31	@,
	ldr	r2, [fp, #-52]	@, %sfp
	movw	r1, #:lower16:.LC183	@,
	movt	r1, #:upper16:.LC183	@,
	str	r5, [sp, #0]	@ s32FrmNum,
	bl	dprint_vfmw	@
	mvn	r3, #0	@,
	str	r3, [fp, #-56]	@, %sfp
	b	.L1040	@
.L1054:
	mov	r2, r5	@, s32FrmNum
	mov	r3, r7	@, s32AllocedFrameNum
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC184	@,
	movt	r1, #:upper16:.LC184	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, ChanID
	bl	VCTRL_RlsAllFrameNode	@
	cmp	r0, #0	@,
	mvneq	r2, #0	@,
	streq	r2, [fp, #-56]	@, %sfp
	beq	.L1040	@,
	mov	r2, r4	@, ChanID
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC185	@,
	movt	r1, #:upper16:.LC185	@,
	bl	dprint_vfmw	@
	mvn	ip, #0	@,
	str	ip, [fp, #-56]	@, %sfp
	b	.L1040	@
	.fnend
	.size	VCTRL_AllocMemPre, .-VCTRL_AllocMemPre
	.align	2
	.type	VCTRL_AllocMemMMZ, %function
VCTRL_AllocMemMMZ:
	.fnstart
.LFB1664:
	@ args = 0, pretend = 0, frame = 32
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
	movw	r5, #:lower16:.LANCHOR0	@ tmp218,
	movt	r5, #:upper16:.LANCHOR0	@ tmp218,
	str	r1, [fp, #-60]	@ s32FrmNum, %sfp
	mov	r6, r0	@ ChanID, ChanID
	movw	r8, #:lower16:249256	@ tmp147,
	ldr	r7, [r5, r0, asl #2]	@ prephitmp.3613, s_pstVfmwChan
	mov	r0, #0	@,
	str	r0, [fp, #-52]	@, %sfp
	movt	r8, #:upper16:249256	@ tmp147,
	mov	r4, r0	@ s32Times,
	mov	sl, r0	@ i, s32Times
	ldr	r2, [r7, #1420]	@ <variable>.stSynExtraData.stChanOption.s32DelayTime, <variable>.stSynExtraData.stChanOption.s32DelayTime
	ldr	r9, [r7, r8]	@ s32FrameSize, <variable>.s32CurFsSize
	mov	r8, r0	@ tmp227, s32Ret
	str	r4, [fp, #-72]	@ s32Times, %sfp
	add	r1, r2, r2, lsr #31	@, tmp150, <variable>.stSynExtraData.stChanOption.s32DelayTime, <variable>.stSynExtraData.stChanOption.s32DelayTime,
	mov	r3, r1, asr #1	@, tmp150,
	str	r3, [fp, #-48]	@, %sfp
	b	.L1062	@
.L1056:
	ldr	r3, [fp, #-60]	@, %sfp
	ldr	r1, [fp, #-52]	@, %sfp
	cmp	r3, r1	@,
	ble	.L1061	@,
	add	sl, sl, #1	@ i, i,
	cmp	sl, #64	@ i,
	beq	.L1059	@,
.L1069:
	ldr	r7, [r5, r6, asl #2]	@ prephitmp.3613, s_pstVfmwChan
.L1062:
	mov	ip, sl, asl #2	@, i,
	str	ip, [fp, #-56]	@, %sfp
	add	r2, ip, sl	@ tmp157,, i
	ldr	ip, [fp, #-52]	@, %sfp
	mov	r2, r2, asl #2	@ tmp158, tmp157,
	add	r1, r2, r7	@ tmp159, tmp158, prephitmp.3613
	add	r3, r1, #248832	@ tmp160, tmp159,
	ldr	r1, [fp, #-60]	@, %sfp
	add	r4, r3, #472	@ tmp160, tmp160,
	ldrb	r3, [r4, #0]	@ zero_extendqisi2	@ <variable>.u8BufferNodeState, <variable>.u8BufferNodeState
	cmp	ip, r1	@,
	movge	r4, #0	@,
	movlt	r4, #1	@,
	cmp	r3, #255	@ <variable>.u8BufferNodeState,
	movne	r4, #0	@,,
	cmp	r4, #0	@ tmp166,
	beq	.L1056	@,
	add	r3, r2, #248832	@ tmp171, tmp158,
	mov	r1, r8	@, tmp227
	add	lr, r3, #456	@ tmp171, tmp171,
	movw	r0, #:lower16:.LC186	@,
	add	r7, r7, lr	@ MEM_RECORD, prephitmp.3613, tmp171
	movt	r0, #:upper16:.LC186	@,
	mov	r2, r9	@, s32FrameSize
	str	r8, [sp, #0]	@ tmp227,
	mov	r3, r7	@, MEM_RECORD
	str	lr, [fp, #-68]	@,
	bl	MEM_AllocMemBlock	@
	ldr	r1, [fp, #-48]	@, %sfp
	ldr	r3, [fp, #-72]	@, %sfp
	ldr	ip, [fp, #-68]	@,
	cmp	r0, #0	@ s32Ret,
	cmpne	r1, r3	@,,
	ble	.L1057	@,
	str	sl, [fp, #-64]	@ i, %sfp
	mov	r4, r3	@ s32Times,
	mov	sl, ip	@ tmp223, tmp223
.L1065:
	mov	r0, #2	@,
	add	r4, r4, #1	@ s32Times, s32Times,
	bl	msleep	@
	ldr	r7, [r5, r6, asl #2]	@ tmp188, s_pstVfmwChan
	mov	r2, r9	@, s32FrameSize
	movw	r0, #:lower16:.LC186	@,
	add	r7, sl, r7	@ MEM_RECORD, tmp223, tmp188
	movt	r0, #:upper16:.LC186	@,
	mov	r1, r8	@, tmp227
	str	r8, [sp, #0]	@ tmp227,
	mov	r3, r7	@, MEM_RECORD
	bl	MEM_AllocMemBlock	@
	ldr	r2, [fp, #-48]	@, %sfp
	cmp	r0, #0	@ s32Ret,
	cmpne	r2, r4	@,, s32Times
	bgt	.L1065	@,
	ldr	sl, [fp, #-64]	@ i, %sfp
	str	r4, [fp, #-72]	@ s32Times, %sfp
.L1057:
	cmp	r0, #0	@ s32Ret,
	bne	.L1059	@,
	ldr	lr, [fp, #-52]	@, %sfp
	ldr	r2, [r7, #12]	@, <variable>.Length
	add	r0, lr, #1	@,,
	str	r0, [fp, #-52]	@, %sfp
	ldr	r1, [r7, #4]	@, <variable>.VirAddr
	ldr	r0, [r7, #8]	@, <variable>.PhyAddr
	bl	MEM_AddMemRecord	@
	ldr	ip, [fp, #-56]	@, %sfp
	ldr	r3, [r5, r6, asl #2]	@ tmp201, s_pstVfmwChan
	add	r2, ip, sl	@ tmp205,, i
	add	sl, sl, #1	@ i, i,
	cmp	sl, #64	@ i,
	add	r1, r3, r2, asl #2	@, tmp207, tmp201, tmp205,
	add	r4, r1, #248832	@ tmp208, tmp207,
	add	ip, r4, #472	@ tmp208, tmp208,
	mov	r4, #1	@,
	strb	r4, [ip, #0]	@, <variable>.u8BufferNodeState
	bne	.L1069	@,
.L1059:
	ldr	r2, [fp, #-60]	@, %sfp
	ldr	r3, [fp, #-52]	@, %sfp
	cmp	r2, r3	@,
	bgt	.L1070	@,
.L1061:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1070:
	ldr	r4, [fp, #-60]	@, %sfp
	mov	r2, r6	@, ChanID
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC187	@,
	movt	r1, #:upper16:.LC187	@,
	stmia	sp, {r4, sl}	@ phole stm
	bl	dprint_vfmw	@
	mov	r0, r6	@, ChanID
	bl	VCTRL_RlsAllFrameNode	@
	cmp	r0, #0	@,
	mvneq	r0, #0	@ s32Ret,
	beq	.L1061	@
.L1063:
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC188	@,
	movt	r1, #:upper16:.LC188	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ s32Ret,
	b	.L1061	@
	.fnend
	.size	VCTRL_AllocMemMMZ, .-VCTRL_AllocMemMMZ
	.align	2
	.global	VCTRL_RequestChanMem
	.type	VCTRL_RequestChanMem, %function
VCTRL_RequestChanMem:
	.fnstart
.LFB1665:
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
	movw	r5, #:lower16:.LANCHOR0	@ tmp210,
	movt	r5, #:upper16:.LANCHOR0	@ tmp210,
	movw	r2, #:lower16:249256	@ tmp154,
	movt	r2, #:upper16:249256	@ tmp154,
	movw	ip, #:lower16:249264	@ tmp153,
	ldr	r3, [r5, r0, asl #2]	@ D.55734, s_pstVfmwChan
	movt	ip, #:upper16:249264	@ tmp153,
	mov	r6, r0	@ ChanID, ChanID
	ldr	r1, [r3, r2]	@ s32FrameSize, <variable>.s32CurFsSize
	ldr	r7, [r3, ip]	@ s32NeededFrmNum, <variable>.s32NeededFrameNum
	cmp	r1, #0	@ s32FrameSize,
	ldr	r2, [r3, #280]	@ s32PreAllocSize, <variable>.s32VdmChanMemSize
	ble	.L1081	@,
	ldr	r4, [r3, #276]	@ <variable>.s32VdmChanMemAddr, <variable>.s32VdmChanMemAddr
	cmp	r4, #0	@ <variable>.s32VdmChanMemAddr,
	cmpne	r2, #0	@, s32PreAllocSize,
	bgt	.L1082	@,
	movw	r4, #:lower16:249276	@ tmp197,
	movt	r4, #:upper16:249276	@ tmp197,
	ldr	r3, [r3, r4]	@ temp.3673, <variable>.s32NeedMMZ
	cmp	r3, #1	@ temp.3673,
	bne	.L1079	@,
	mov	r1, r7	@, s32NeededFrmNum
	bl	VCTRL_AllocMemMMZ	@
	ldr	r8, [r5, r6, asl #2]	@ temp.3674, s_pstVfmwChan
	mov	r4, r0	@ s32Ret,
	bl	OSAL_GetTimeInMs	@
	movw	ip, #:lower16:251524	@ tmp199,
	movt	ip, #:upper16:251524	@ tmp199,
	movw	r3, #:lower16:249272	@ tmp202,
	cmp	r4, #0	@ s32Ret,
	movt	r3, #:upper16:249272	@ tmp202,
	str	r0, [r8, ip]	@, <variable>.stDynamicFSTimestamp.u32MMZEndTime
	ldr	r1, [r5, r6, asl #2]	@ tmp201, s_pstVfmwChan
	str	r7, [r1, r3]	@ s32NeededFrmNum, <variable>.s32MMZFrmNum
	bne	.L1083	@,
.L1073:
	mov	r0, r4	@, s32Ret
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1082:
	mov	r0, r2	@, s32PreAllocSize
	bl	__aeabi_idiv	@
	cmp	r7, r0	@ s32NeededFrmNum, tmp166
	mov	r8, r0	@ tmp166,
	bgt	.L1084	@,
.L1075:
	mov	r1, r7	@, s32NeededFrmNum
	mov	r0, r6	@, ChanID
	bl	VCTRL_AllocMemPre	@
	ldr	r8, [r5, r6, asl #2]	@ temp.3670, s_pstVfmwChan
	mov	r4, r0	@ s32Ret,
	bl	OSAL_GetTimeInMs	@
	movw	r2, #:lower16:251520	@ tmp190,
	movt	r2, #:upper16:251520	@ tmp190,
	movw	ip, #:lower16:249268	@ tmp193,
	cmp	r4, #0	@ s32Ret,
	movt	ip, #:upper16:249268	@ tmp193,
	str	r0, [r8, r2]	@, <variable>.stDynamicFSTimestamp.u32PreEndTime
	ldr	r0, [r5, r6, asl #2]	@ tmp192, s_pstVfmwChan
	str	r7, [r0, ip]	@ s32NeededFrmNum, <variable>.s32PreAllocFrmNum
	beq	.L1073	@,
	movw	r1, #:lower16:.LC192	@,
	ldr	r2, .L1086	@,
	movt	r1, #:upper16:.LC192	@,
	movw	r3, #10491	@,
	mov	r0, #31	@,
	bl	dprint_vfmw	@
	b	.L1073	@
.L1084:
	rsb	sl, r0, r7	@ s32MMZFrmNum, tmp166, s32NeededFrmNum
	cmp	sl, #0	@ s32MMZFrmNum,
	ble	.L1075	@,
	mov	r1, r0	@, tmp166
	mov	r0, r6	@, ChanID
	bl	VCTRL_AllocMemPre	@
	ldr	r7, [r5, r6, asl #2]	@ temp.3665, s_pstVfmwChan
	mov	r4, r0	@ s32Ret,
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:251520	@ tmp168,
	movt	r1, #:upper16:251520	@ tmp168,
	movw	r3, #:lower16:249268	@ tmp171,
	cmp	r4, #0	@ s32Ret,
	movt	r3, #:upper16:249268	@ tmp171,
	str	r0, [r7, r1]	@, <variable>.stDynamicFSTimestamp.u32PreEndTime
	ldr	r0, [r5, r6, asl #2]	@ tmp170, s_pstVfmwChan
	str	r8, [r0, r3]	@ tmp166, <variable>.s32PreAllocFrmNum
	bne	.L1076	@,
	ldr	ip, [r5, r6, asl #2]	@ tmp173, s_pstVfmwChan
	movw	lr, #:lower16:249276	@ tmp174,
	movt	lr, #:upper16:249276	@ tmp174,
	ldr	r3, [ip, lr]	@ D.55755, <variable>.s32NeedMMZ
	cmp	r3, #1	@ D.55755,
	bne	.L1077	@,
	mov	r0, r6	@, ChanID
	mov	r1, sl	@, s32MMZFrmNum
	bl	VCTRL_AllocMemMMZ	@
	subs	r4, r0, #0	@ s32Ret,
	bne	.L1085	@,
	ldr	r7, [r5, r6, asl #2]	@ temp.3668, s_pstVfmwChan
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:251524	@ tmp179,
	movt	r1, #:upper16:251524	@ tmp179,
	movw	r3, #:lower16:249272	@ tmp182,
	movt	r3, #:upper16:249272	@ tmp182,
	str	r0, [r7, r1]	@, <variable>.stDynamicFSTimestamp.u32MMZEndTime
	mov	r0, r4	@, s32Ret
	ldr	r2, [r5, r6, asl #2]	@ tmp181, s_pstVfmwChan
	str	sl, [r2, r3]	@ s32MMZFrmNum, <variable>.s32MMZFrmNum
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1083:
	ldr	r2, .L1086	@,
	movw	r3, #10504	@,
	movw	r1, #:lower16:.LC190	@,
	mov	r0, #31	@,
	movt	r1, #:upper16:.LC190	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, s32Ret
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1076:
	ldr	r2, .L1086	@,
	movw	r3, #10481	@,
	movw	r1, #:lower16:.LC192	@,
	mov	r0, #31	@,
	movt	r1, #:upper16:.LC192	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, s32Ret
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1079:
	movw	r1, #:lower16:.LC193	@,
	ldr	r2, .L1086	@,
	movt	r1, #:upper16:.LC193	@,
	mov	r0, #31	@,
	mvn	r4, #0	@ s32Ret,
	bl	dprint_vfmw	@
	b	.L1073	@
.L1077:
	movw	r1, #:lower16:.LC191	@,
	ldr	r2, .L1086	@,
	movt	r1, #:upper16:.LC191	@,
	mov	r0, #31	@,
	mvn	r4, #0	@ s32Ret,
	bl	dprint_vfmw	@
	b	.L1073	@
.L1085:
	movw	r1, #:lower16:.LC190	@,
	ldr	r2, .L1086	@,
	movt	r1, #:upper16:.LC190	@,
	movw	r3, #10467	@,
	mov	r0, #31	@,
	mvn	r4, #0	@ s32Ret,
	bl	dprint_vfmw	@
	b	.L1073	@
.L1081:
	mov	r2, r1	@, s32FrameSize
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC189	@,
	movt	r1, #:upper16:.LC189	@,
	bl	dprint_vfmw	@
	mvn	r4, #0	@ s32Ret,
	b	.L1073	@
.L1087:
	.align	2
.L1086:
	.word	.LANCHOR1+208
	.fnend
	.size	VCTRL_RequestChanMem, .-VCTRL_RequestChanMem
	.align	2
	.global	VCTRL_EnableAllInt
	.type	VCTRL_EnableAllInt, %function
VCTRL_EnableAllInt:
	.fnstart
.LFB1624:
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
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp134,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp134,
	ldr	r3, [r3, #76]	@ D.53906, g_vdm_hal_fun_ptr.pfun_VDMHAL_EnableInt
	cmp	r3, #0	@ D.53906,
	beq	.L1092	@,
	mov	r0, #0	@,
	blx	r3	@ D.53906
	mov	r0, #0	@,
	bl	SCDDRV_EnableInt	@
	ldmfd	sp, {fp, sp, pc}	@
.L1092:
	mov	r0, r3	@, D.53906
	movw	r2, #7726	@,
	movw	r1, #:lower16:.LC0	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@,
	bl	SCDDRV_EnableInt	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_EnableAllInt, .-VCTRL_EnableAllInt
	.align	2
	.global	VCTRL_MaskAllInt
	.type	VCTRL_MaskAllInt, %function
VCTRL_MaskAllInt:
	.fnstart
.LFB1623:
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
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp134,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp134,
	ldr	r3, [r3, #72]	@ D.53891, g_vdm_hal_fun_ptr.pfun_VDMHAL_MaskInt
	cmp	r3, #0	@ D.53891,
	beq	.L1097	@,
	mov	r0, #0	@,
	blx	r3	@ D.53891
	mov	r0, #0	@,
	bl	SCDDRV_MaskInt	@
	ldmfd	sp, {fp, sp, pc}	@
.L1097:
	mov	r0, r3	@, D.53891
	movw	r2, #7691	@,
	movw	r1, #:lower16:.LC0	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@,
	bl	SCDDRV_MaskInt	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_MaskAllInt, .-VCTRL_MaskAllInt
	.align	2
	.global	VCTRL_GetChanImgNum
	.type	VCTRL_GetChanImgNum, %function
VCTRL_GetChanImgNum:
	.fnstart
.LFB1616:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp140,
	movt	r4, #:upper16:.LANCHOR0	@ tmp140,
	mov	r5, r0	@ ChanID, ChanID
	mov	r6, r1	@ pRefImgNum, pRefImgNum
	mov	r7, r2	@ pReadImgNum, pReadImgNum
	ldr	ip, [r4, r0, asl #2]	@ tmp141, s_pstVfmwChan
	mov	r8, r3	@ pNewImgNum, pNewImgNum
	cmp	ip, #0	@ tmp141,
	beq	.L1106	@,
	bl	VCTRL_GetChanVoQue	@
	subs	r3, r0, #0	@ pstVoQue,
	streq	r3, [r8, #0]	@ pstVoQue,* pNewImgNum
	streq	r3, [r7, #0]	@ pstVoQue,* pReadImgNum
	streq	r3, [r6, #0]	@ pstVoQue,* pRefImgNum
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	mov	r2, r8	@, pNewImgNum
	mov	r1, r7	@, pReadImgNum
	bl	GetQueueImgNum	@
	ldr	r2, [r4, r5, asl #2]	@ temp.3746, s_pstVfmwChan
	ldr	r3, [r2, #544]	@ D.53722, <variable>.eVidStd
	cmp	r3, #0	@ D.53722,
	beq	.L1107	@,
	cmp	r3, #16	@ D.53722,
	beq	.L1108	@,
	cmp	r3, #15	@ D.53722,
	movweq	r3, #:lower16:11374600	@ tmp149,
	movteq	r3, #:upper16:11374600	@ tmp149,
	movne	r3, #2	@ tmp151,
	ldreq	r3, [r2, r3]	@ <variable>.stSynCtx.unSyntax.stMvcCtx.DPB.size,
	str	r3, [r6, #0]	@ tmp151,* pRefImgNum
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L1107:
	movw	r1, #:lower16:278216	@ tmp145,
	movt	r1, #:upper16:278216	@ tmp145,
	ldr	r0, [r2, r1]	@ <variable>.stSynCtx.unSyntax.stH264Ctx.DPB.size,
	str	r0, [r6, #0]	@ <variable>.stSynCtx.unSyntax.stH264Ctx.DPB.size,* pRefImgNum
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L1106:
	mov	r0, ip	@, tmp141
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7418	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L1108:
	movw	lr, #:lower16:2211952	@ tmp147,
	movt	lr, #:upper16:2211952	@ tmp147,
	ldr	ip, [r2, lr]	@ <variable>.stSynCtx.unSyntax.stHevcCtx.DPB.size,
	str	ip, [r6, #0]	@ <variable>.stSynCtx.unSyntax.stHevcCtx.DPB.size,* pRefImgNum
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetChanImgNum, .-VCTRL_GetChanImgNum
	.align	2
	.global	VCTRL_GetChanState
	.type	VCTRL_GetChanState, %function
VCTRL_GetChanState:
	.fnstart
.LFB1559:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #68
	sub	sp, sp, #68	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ ChanID,
	mov	r5, r0	@ ChanID, ChanID
	mov	r4, r1	@ pstChanState, pstChanState
	bhi	.L1129	@,
	cmp	r1, #0	@ pstChanState,
	beq	.L1116	@,
	movw	r6, #:lower16:.LANCHOR0	@ tmp203,
	movt	r6, #:upper16:.LANCHOR0	@ tmp203,
	mov	r0, r1	@, pstChanState
	mov	r1, #108	@,
	mov	r7, #0	@ tmp144,
	str	r7, [fp, #-40]	@ tmp144, RefNum
	str	r7, [fp, #-44]	@ tmp144, ReadNum
	str	r7, [fp, #-48]	@ tmp144, NewNum
	bl	__memzero	@
	ldr	r1, [r6, r5, asl #2]	@ D.50380, s_pstVfmwChan
	cmp	r1, r7	@ D.50380,
	beq	.L1116	@,
	add	r1, r1, #1104	@, D.50380,
	mov	r0, r4	@, pstChanState
	add	r1, r1, #12	@,,
	mov	r2, #108	@,
	bl	memcpy	@
	ldr	r0, [r6, r5, asl #2]	@ temp.3781, s_pstVfmwChan
	movw	r3, #:lower16:206402	@ tmp155,
	movt	r3, #:upper16:206402	@ tmp155,
	ldrsb	lr, [r0, r3]	@ temp.3780, <variable>.FspInst.s32DecFsNum
	cmp	lr, r7	@ temp.3780,
	ble	.L1113	@,
	movw	r1, #:lower16:241366	@ tmp163,
	movt	r1, #:upper16:241366	@ tmp163,
	add	r3, r0, r1	@ tmp163, temp.3781, tmp163
	rsb	lr, lr, lr, asl #4	@, tmp160, temp.3780, temp.3780,
	ldrsb	r2, [r3, #0]	@ <variable>.DispState, <variable>.DispState
	mov	lr, lr, asl #2	@ D.59210, tmp160,
	sub	ip, lr, #60	@ tmp209, D.59210,
	cmp	r2, #3	@ <variable>.DispState,
	ubfx	r2, ip, #2, #1	@ tmp213, tmp209,,
	beq	.L1130	@,
.L1118:
	mov	r3, #60	@ ivtmp.3776,
	cmp	r3, lr	@ ivtmp.3776, D.59210
	beq	.L1113	@,
	cmp	r2, #0	@ tmp213,
	beq	.L1115	@,
	movw	ip, #:lower16:241426	@ tmp228,
	movt	ip, #:upper16:241426	@ tmp228,
	add	r1, r0, ip	@ tmp228, temp.3781, tmp228
	add	r3, r3, #60	@ ivtmp.3776, ivtmp.3776,
	ldrsb	r2, [r1, #0]	@ <variable>.DispState, <variable>.DispState
	cmp	r2, #3	@ <variable>.DispState,
	addeq	r7, r7, #1	@ s32DecodedFrameNum, s32DecodedFrameNum,
	cmp	r3, lr	@ ivtmp.3776, D.59210
	bne	.L1115	@,
	b	.L1113	@
.L1123:
	add	r3, r1, #60	@ ivtmp.3776, tmp214,
	cmp	r3, lr	@ ivtmp.3776, D.59210
	beq	.L1113	@,
.L1115:
	movw	r2, #:lower16:241366	@ tmp219,
	movt	r2, #:upper16:241366	@ tmp219,
	add	r1, r3, #60	@ tmp214, ivtmp.3776,
	add	r8, r0, r3	@ tmp217, temp.3781, ivtmp.3776
	add	ip, r0, r1	@ tmp222, temp.3781, tmp214
	mov	r3, r2	@ tmp224, tmp219
	add	r2, r8, r2	@ tmp219, tmp217, tmp219
	add	r3, ip, r3	@ tmp224, tmp222, tmp224
	ldrsb	r2, [r2, #0]	@ <variable>.DispState, <variable>.DispState
	ldrsb	ip, [r3, #0]	@ <variable>.DispState, <variable>.DispState
	cmp	r2, #3	@ <variable>.DispState,
	addeq	r7, r7, #1	@ s32DecodedFrameNum, s32DecodedFrameNum,
	cmp	ip, #3	@ <variable>.DispState,
	bne	.L1123	@,
	add	r3, r1, #60	@ ivtmp.3776, tmp214,
	add	r7, r7, #1	@ s32DecodedFrameNum, s32DecodedFrameNum,
	cmp	r3, lr	@ ivtmp.3776, D.59210
	bne	.L1115	@,
.L1113:
	str	r7, [r4, #92]	@ prephitmp.3761, <variable>.wait_disp_frame_num
	movw	ip, #:lower16:206402	@ tmp168,
	ldr	lr, [r6, r5, asl #2]	@ tmp167, s_pstVfmwChan
	movt	ip, #:upper16:206402	@ tmp168,
	sub	r2, fp, #44	@,,
	sub	r3, fp, #48	@,,
	mov	r0, r5	@, ChanID
	sub	r1, fp, #40	@,,
	ldrsb	ip, [lr, ip]	@ <variable>.FspInst.s32DecFsNum, <variable>.FspInst.s32DecFsNum
	str	ip, [r4, #100]	@ <variable>.FspInst.s32DecFsNum, <variable>.total_disp_frame_num
	bl	VCTRL_GetChanImgNum	@
	mov	r1, #300	@ tmp179,
	mla	r3, r1, r5, r6	@ tmp180, tmp179, ChanID, tmp203
	ldr	ip, [fp, #-48]	@ NewNum, NewNum
	ldr	r2, [fp, #-44]	@ ReadNum, ReadNum
	sub	r1, fp, #96	@,,
	mov	r0, r5	@, ChanID
	add	r2, ip, r2	@ tmp175, NewNum, ReadNum
	str	r2, [r4, #56]	@ tmp175, <variable>.decoded_1d_frame_num
	ldr	ip, [r3, #1480]	@ <variable>.u32IsFieldFlag, <variable>.u32IsFieldFlag
	str	ip, [r4, #104]	@ <variable>.u32IsFieldFlag, <variable>.is_field_flg
	ldr	r2, [r3, #1468]	@ <variable>.u32FrFrameRate, <variable>.u32FrFrameRate
	str	r2, [r4, #24]	@ <variable>.u32FrFrameRate, <variable>.frame_rate
	bl	SM_GetInfo	@
	ldr	r3, [fp, #-88]	@ SmInstInfo.SegNum, SmInstInfo.SegNum
	ldr	ip, [fp, #-80]	@ SmInstInfo.TotalSegSize, SmInstInfo.TotalSegSize
	sub	r1, fp, #72	@,,
	mov	r0, r5	@, ChanID
	str	r3, [r4, #64]	@ SmInstInfo.SegNum, <variable>.buffered_stream_num
	str	ip, [r4, #60]	@ SmInstInfo.TotalSegSize, <variable>.buffered_stream_size
	bl	SM_GetInfo	@
	ldr	r0, [fp, #-52]	@ ScdInstInfo.numReadSegFail, ScdInstInfo.numReadSegFail
	movw	r3, #:lower16:267448	@ tmp198,
	movt	r3, #:upper16:267448	@ tmp198,
	cmp	r0, #10	@ ScdInstInfo.numReadSegFail,
	movle	r2, #0	@, tmp195
	movgt	r2, #1	@, tmp195
	str	r2, [r4, #88]	@ tmp195, <variable>.stream_not_enough
	ldr	ip, [r6, r5, asl #2]	@ tmp197, s_pstVfmwChan
	ldrb	r1, [ip, r3]	@ zero_extendqisi2	@ tmp200,
	and	r0, r1, #1	@ tmp202, tmp200,
	str	r0, [r4, #96]	@ tmp202, <variable>.mpeg4_shorthead
.L1116:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1129:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1185	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC194	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC194	@,
	bl	dprint_vfmw	@
	b	.L1116	@
.L1130:
	mov	r7, #1	@ s32DecodedFrameNum,
	b	.L1118	@
	.fnend
	.size	VCTRL_GetChanState, .-VCTRL_GetChanState
	.align	2
	.global	CloseDrivers
	.type	CloseDrivers, %function
CloseDrivers:
	.fnstart
.LFB1609:
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
	ldr	r5, [r0, #12]	@ Length, <variable>.Length
	mov	r4, r0	@ pstDrvMem, pstDrvMem
	ldr	r7, [r0, #8]	@ PhyAddr, <variable>.PhyAddr
	cmp	r5, #0	@ Length,
	ldr	r6, [r0, #4]	@ VirAddr, <variable>.VirAddr
	beq	.L1132	@,
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp157,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp157,
	ldr	r3, [r3, #44]	@ D.53293, g_vdm_hal_fun_ptr.pfun_VDMHAL_CloseHAL
	cmp	r3, #0	@ D.53293,
	beq	.L1133	@,
	mov	r0, #0	@,
	blx	r3	@ D.53293
.L1134:
	ldr	r1, [r4, #4]	@, <variable>.VirAddr
	ldr	r0, [r4, #8]	@, <variable>.PhyAddr
	bl	MEM_ReleaseMemBlock	@
	mov	r0, r4	@, pstDrvMem
	mov	r1, #16	@,
	bl	__memzero	@
.L1132:
	mov	r0, r7	@, PhyAddr
	mov	r1, r6	@, VirAddr
	mov	r2, r5	@, Length
	bl	MEM_DelMemRecord	@
	ldr	r6, [r4, #28]	@ Length.3809, <variable>.Length
	ldr	r5, [r4, #24]	@ PhyAddr.3807, <variable>.PhyAddr
	cmp	r6, #0	@ Length.3809,
	ldr	r7, [r4, #20]	@ VirAddr.3808, <variable>.VirAddr
	bne	.L1144	@,
.L1135:
	mov	r1, r7	@, VirAddr.3808
	mov	r2, r6	@, Length.3809
	mov	r0, r5	@, PhyAddr.3807
	bl	MEM_DelMemRecord	@
	bl	SM_InstInit	@
	ldr	r5, [r4, #60]	@ Length.3816, <variable>.Length
	ldr	r7, [r4, #56]	@ PhyAddr.3814, <variable>.PhyAddr
	cmp	r5, #0	@ Length.3816,
	ldr	r6, [r4, #52]	@ VirAddr.3815, <variable>.VirAddr
	bne	.L1145	@,
.L1136:
	mov	r0, r7	@, PhyAddr.3814
	mov	r1, r6	@, VirAddr.3815
	mov	r2, r5	@, Length.3816
	bl	MEM_DelMemRecord	@
	ldr	r5, [r4, #108]	@ Length.3821, <variable>.stBpdReg.Length
	ldr	r7, [r4, #104]	@ PhyAddr.3819, <variable>.stBpdReg.PhyAddr
	cmp	r5, #0	@ Length.3821,
	ldr	r6, [r4, #100]	@ VirAddr.3820, <variable>.stBpdReg.VirAddr
	bne	.L1146	@,
.L1137:
	mov	r0, r7	@, PhyAddr.3819
	mov	r1, r6	@, VirAddr.3820
	mov	r2, r5	@, Length.3821
	bl	MEM_DelMemRecord	@
	ldr	r5, [r4, #92]	@ Length.3826, <variable>.Length
	ldr	r7, [r4, #88]	@ PhyAddr.3824, <variable>.PhyAddr
	cmp	r5, #0	@ Length.3826,
	ldr	r6, [r4, #84]	@ VirAddr.3825, <variable>.VirAddr
	bne	.L1147	@,
.L1138:
	mov	r0, r7	@, PhyAddr.3824
	mov	r1, r6	@, VirAddr.3825
	mov	r2, r5	@, Length.3826
	bl	MEM_DelMemRecord	@
	ldr	r5, [r4, #76]	@ Length.3831, <variable>.stFodReg.Length
	ldr	r7, [r4, #72]	@ PhyAddr.3829, <variable>.stFodReg.PhyAddr
	cmp	r5, #0	@ Length.3831,
	ldr	r6, [r4, #68]	@ VirAddr.3830, <variable>.stFodReg.VirAddr
	bne	.L1148	@,
.L1139:
	mov	r0, r7	@, PhyAddr.3829
	mov	r1, r6	@, VirAddr.3830
	mov	r2, r5	@, Length.3831
	bl	MEM_DelMemRecord	@
	ldr	r5, [r4, #124]	@ Length.3836, <variable>.stSystemReg.Length
	ldr	r7, [r4, #120]	@ PhyAddr.3834, <variable>.stSystemReg.PhyAddr
	cmp	r5, #0	@ Length.3836,
	ldr	r6, [r4, #116]	@ VirAddr.3835, <variable>.stSystemReg.VirAddr
	bne	.L1149	@,
.L1140:
	movw	r4, #:lower16:.LANCHOR0	@ tmp178,
	movt	r4, #:upper16:.LANCHOR0	@ tmp178,
	mov	r0, r7	@, PhyAddr.3834
	mov	r1, r6	@, VirAddr.3835
	mov	r2, r5	@, Length.3836
	bl	MEM_DelMemRecord	@
	ldr	r0, [r4, #296]	@ s_VfmwCTrl.stIrqRecord.VdhIrq, s_VfmwCTrl.stIrqRecord.VdhIrq
	cmp	r0, #1	@ s_VfmwCTrl.stIrqRecord.VdhIrq,
	beq	.L1150	@,
.L1141:
	ldr	r2, [r4, #300]	@ s_VfmwCTrl.stIrqRecord.ScdIrq, s_VfmwCTrl.stIrqRecord.ScdIrq
	movw	r4, #:lower16:.LANCHOR0	@ tmp173,
	movt	r4, #:upper16:.LANCHOR0	@ tmp173,
	cmp	r2, #1	@ s_VfmwCTrl.stIrqRecord.ScdIrq,
	beq	.L1151	@,
	mov	r0, #0	@,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L1144:
	mov	r0, #0	@,
	bl	SM_CloseSCDDrv	@
	ldr	r0, [r4, #24]	@, <variable>.PhyAddr
	ldr	r1, [r4, #20]	@, <variable>.VirAddr
	bl	MEM_ReleaseMemBlock	@
	add	r0, r4, #16	@, pstDrvMem,
	mov	r1, #16	@,
	bl	__memzero	@
	b	.L1135	@
.L1146:
	mov	r0, r7	@, PhyAddr.3819
	mov	r1, r6	@, VirAddr.3820
	bl	MEM_UnmapRegisterAddr	@
	add	r0, r4, #96	@, pstDrvMem,
	mov	r1, #16	@,
	bl	__memzero	@
	b	.L1137	@
.L1145:
	mov	r0, r7	@, PhyAddr.3814
	mov	r1, r6	@, VirAddr.3815
	bl	MEM_UnmapRegisterAddr	@
	add	r0, r4, #48	@, pstDrvMem,
	mov	r1, #16	@,
	bl	__memzero	@
	b	.L1136	@
.L1149:
	mov	r0, r7	@, PhyAddr.3834
	mov	r1, r6	@, VirAddr.3835
	bl	MEM_UnmapRegisterAddr	@
	add	r0, r4, #112	@, pstDrvMem,
	mov	r1, #16	@,
	bl	__memzero	@
	b	.L1140	@
.L1148:
	mov	r0, r7	@, PhyAddr.3829
	mov	r1, r6	@, VirAddr.3830
	bl	MEM_UnmapRegisterAddr	@
	add	r0, r4, #64	@, pstDrvMem,
	mov	r1, #16	@,
	bl	__memzero	@
	b	.L1139	@
.L1147:
	mov	r0, r7	@, PhyAddr.3824
	mov	r1, r6	@, VirAddr.3825
	bl	MEM_UnmapRegisterAddr	@
	add	r0, r4, #80	@, pstDrvMem,
	mov	r1, #16	@,
	bl	__memzero	@
	b	.L1138	@
.L1133:
	mov	r0, r3	@, D.53293
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #6636	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L1134	@
.L1151:
	mov	r0, #136	@,
	mov	r1, #0	@,
	bl	free_irq	@
	mov	ip, #0	@ tmp176,
	mov	r0, #0	@,
	str	ip, [r4, #300]	@ tmp176, s_VfmwCTrl.stIrqRecord.ScdIrq
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L1150:
	mov	r1, #0	@,
	mov	r0, #127	@,
	bl	free_irq	@
	mov	r1, #0	@ tmp172,
	str	r1, [r4, #296]	@ tmp172, s_VfmwCTrl.stIrqRecord.VdhIrq
	b	.L1141	@
	.fnend
	.size	CloseDrivers, .-CloseDrivers
	.align	2
	.global	OpenDrivers
	.type	OpenDrivers, %function
OpenDrivers:
	.fnstart
.LFB1608:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #44
	sub	sp, sp, #44	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	add	r5, r0, #48	@ pstMem, pstDrvMem,
	mov	r4, r0	@ pstDrvMem, pstDrvMem
	mov	r1, #4096	@,
	movw	r0, #:lower16:-121438208	@,
	mov	r2, r5	@, pstMem
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_MapRegisterAddr	@
	cmp	r0, #0	@,
	bne	.L1153	@,
	add	r6, r4, #96	@ pstMem.3862, pstDrvMem,
	ldr	r1, [r4, #52]	@, <variable>.VirAddr
	ldr	r2, [r4, #60]	@, <variable>.Length
	ldr	r0, [r4, #56]	@, <variable>.PhyAddr
	bl	MEM_AddMemRecord	@
	movw	r0, #:lower16:-121241600	@,
	mov	r1, #4096	@,
	movt	r0, #:upper16:-121241600	@,
	mov	r2, r6	@, pstMem.3862
	bl	MEM_MapRegisterAddr	@
	cmp	r0, #0	@,
	bne	.L1173	@,
	movw	r5, #:lower16:g_vdm_hal_fun_ptr	@ tmp161,
	movt	r5, #:upper16:g_vdm_hal_fun_ptr	@ tmp161,
	ldr	r3, [r5, #24]	@ D.53127, g_vdm_hal_fun_ptr.pfun_BPDDRV_OpenHardware
	cmp	r3, #0	@ D.53127,
	beq	.L1173	@,
	blx	r3	@ D.53127
	cmp	r0, #0	@,
	bne	.L1173	@,
	add	r7, r4, #80	@ pstMem.3866, pstDrvMem,
	ldr	r1, [r4, #100]	@, <variable>.stBpdReg.VirAddr
	ldr	r2, [r4, #108]	@, <variable>.stBpdReg.Length
	ldr	r0, [r4, #104]	@, <variable>.stBpdReg.PhyAddr
	bl	MEM_AddMemRecord	@
	movw	r0, #:lower16:-121389056	@,
	mov	r1, #4096	@,
	movt	r0, #:upper16:-121389056	@,
	mov	r2, r7	@, pstMem.3866
	bl	MEM_MapRegisterAddr	@
	subs	r6, r0, #0	@ D.53162,
	bne	.L1177	@,
	sub	r8, fp, #68	@ tmp201,,
	ldr	r1, [r4, #84]	@, <variable>.VirAddr
	ldr	r2, [r4, #92]	@, <variable>.Length
	ldr	r0, [r4, #88]	@, <variable>.PhyAddr
	bl	MEM_AddMemRecord	@
	mov	r3, r6	@, D.53162
	mov	r0, r8	@, tmp201
	mov	r1, #20	@,
	movw	r2, #:lower16:.LC195	@,
	movt	r2, #:upper16:.LC195	@,
	bl	snprintf	@
	ldr	r3, [r5, #36]	@ D.53173, g_vdm_hal_fun_ptr.pfun_VDMHAL_GetHalMemSize
	cmp	r3, #0	@ D.53173,
	beq	.L1177	@,
	blx	r3	@ D.53173
	subs	r2, r0, #0	@ Size,
	ble	.L1177	@,
	mov	r1, r6	@, D.53162
	mov	r0, r8	@, tmp201
	mov	r3, r4	@, pstDrvMem
	str	r6, [sp, #0]	@ D.53162,
	bl	MEM_AllocMemBlock	@
	subs	r7, r0, #0	@ D.53186,
	bne	.L1164	@,
	sub	r6, fp, #48	@ tmp176,,
	ldr	r2, [r4, #12]	@, <variable>.Length
	ldr	r1, [r4, #4]	@, <variable>.VirAddr
	ldr	r0, [r4, #8]	@, <variable>.PhyAddr
	bl	MEM_AddMemRecord	@
	mov	r1, #12	@,
	mov	r0, r6	@, tmp176
	bl	__memzero	@
	ldr	r3, [r5, #40]	@ D.53196, g_vdm_hal_fun_ptr.pfun_VDMHAL_OpenHAL
	ldr	r1, [r4, #8]	@ <variable>.PhyAddr, <variable>.PhyAddr
	ldr	r2, [r4, #12]	@ <variable>.Length, <variable>.Length
	cmp	r3, #0	@ D.53196,
	str	r7, [fp, #-40]	@ D.53186, VDMOpenParam.VdhId
	str	r1, [fp, #-48]	@ <variable>.PhyAddr, VDMOpenParam.MemBaseAddr
	str	r2, [fp, #-44]	@ <variable>.Length, VDMOpenParam.Size
	beq	.L1164	@,
	mov	r0, r6	@, tmp176
	blx	r3	@ D.53196
	cmp	r0, #0	@,
	bne	.L1164	@,
	mov	r0, #0	@,
	add	r7, r4, #16	@ pstMem.3876, pstDrvMem,
	bl	VDMDRV_Init	@
	mov	r1, #20	@,
	mov	r3, #0	@,
	mov	r0, r8	@, tmp201
	movw	r2, #:lower16:.LC196	@,
	movt	r2, #:upper16:.LC196	@,
	bl	snprintf	@
	mov	ip, #0	@ tmp184,
	mov	r0, r8	@, tmp201
	mov	r1, ip	@, tmp184
	mov	r2, #716800	@,
	mov	r3, r7	@, pstMem.3876
	str	ip, [sp, #0]	@ tmp184,
	bl	MEM_AllocMemBlock	@
	subs	r5, r0, #0	@ D.53211,
	bne	.L1177	@,
	ldr	r1, [r4, #20]	@, <variable>.VirAddr
	ldr	r2, [r4, #28]	@, <variable>.Length
	ldr	r0, [r4, #24]	@, <variable>.PhyAddr
	bl	MEM_AddMemRecord	@
	mov	r2, r5	@, D.53211
	ldr	r0, [r4, #24]	@, <variable>.PhyAddr
	ldr	r1, [r4, #28]	@, <variable>.Length
	bl	SM_OpenSCDDrv	@
	subs	r5, r0, #0	@ D.53214,
	bne	.L1177	@,
	bl	SM_InstInit	@
	mov	r2, r5	@, D.53214
	mov	r0, #127	@,
	movw	r1, #:lower16:VCTRL_Isr_0	@,
	mov	r3, #32	@,
	movt	r1, #:upper16:VCTRL_Isr_0	@,
	str	r5, [sp, #4]	@ D.53214,
	movw	ip, #:lower16:.LC197	@ tmp191,
	movt	ip, #:upper16:.LC197	@ tmp191,
	str	ip, [sp, #0]	@ tmp191,
	bl	request_threaded_irq	@
	subs	ip, r0, #0	@ D.56222,
	bne	.L1177	@,
	movw	r5, #:lower16:.LANCHOR0	@ tmp193,
	movt	r5, #:upper16:.LANCHOR0	@ tmp193,
	str	ip, [sp, #4]	@ D.56222,
	mov	r6, #1	@ tmp194,
	mov	r2, ip	@, D.56222
	str	r6, [r5, #296]	@ tmp194, s_VfmwCTrl.stIrqRecord.VdhIrq
	mov	r0, #136	@,
	movw	r1, #:lower16:VCTRL_Scd_Isr	@,
	mov	r3, #32	@,
	movt	r1, #:upper16:VCTRL_Scd_Isr	@,
	movw	lr, #:lower16:.LC198	@ tmp196,
	movt	lr, #:upper16:.LC198	@ tmp196,
	str	lr, [sp, #0]	@ tmp196,
	bl	request_threaded_irq	@
	cmp	r0, #0	@ D.56229
	streq	r6, [r5, #300]	@ tmp194, s_VfmwCTrl.stIrqRecord.ScdIrq
	bne	.L1177	@,
.L1156:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1173:
	mov	r0, r6	@, pstMem.3862
.L1178:
	mov	r1, #16	@,
	bl	__memzero	@
	mov	r0, r4	@, pstDrvMem
	bl	CloseDrivers	@
	mvn	r0, #0	@ D.53109,
	b	.L1156	@
.L1177:
	mov	r0, r7	@, pstMem.3876
	b	.L1178	@
.L1164:
	mov	r1, #16	@,
	mov	r0, r4	@, pstDrvMem
	bl	__memzero	@
	mov	r0, r4	@, pstDrvMem
	bl	CloseDrivers	@
	mvn	r0, #0	@ D.53109,
	b	.L1156	@
.L1153:
	mov	r0, r5	@, pstMem
	b	.L1178	@
	.fnend
	.size	OpenDrivers, .-OpenDrivers
	.align	2
	.global	VCTRL_GetUsrdecFrame
	.type	VCTRL_GetUsrdecFrame, %function
VCTRL_GetUsrdecFrame:
	.fnstart
.LFB1602:
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
	movw	r5, #:lower16:.LANCHOR0	@ tmp144,
	movt	r5, #:upper16:.LANCHOR0	@ tmp144,
	mov	r6, r0	@ ChanID, ChanID
	mov	r7, r1	@ pMem, pMem
	ldr	r3, [r5, r0, asl #2]	@ D.52650, s_pstVfmwChan
	cmp	r3, #0	@ D.52650,
	beq	.L1189	@,
	ldr	r8, [r3, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r8, #18	@ <variable>.eVidStd,
	bne	.L1190	@,
	ldr	r3, [r3, #484]	@ <variable>.s32UsrdecFrameNum, <variable>.s32UsrdecFrameNum
	cmp	r3, #2	@ <variable>.s32UsrdecFrameNum,
	ble	.L1191	@,
	bl	FSP_IsNewFsAvalible	@
	cmp	r0, #1	@ D.52663,
	bne	.L1192	@,
	mov	r1, r0	@, D.52663
	mov	r0, r6	@, ChanID
	bl	FSP_NewLogicFs	@
	subs	sl, r0, #0	@ id,
	blt	.L1193	@,
	mov	r1, sl	@, id
	mov	r0, r6	@, ChanID
	bl	FSP_GetLogicFs	@
	mov	r2, sl	@, id
	movw	r1, #:lower16:.LC203	@,
	movt	r1, #:upper16:.LC203	@,
	mov	r4, r0	@ pLf,
	mov	r0, r8	@, <variable>.eVidStd
	bl	dprint_vfmw	@
	cmp	r4, #0	@ pLf,
	beq	.L1194	@,
	ldr	r2, [r4, #520]	@ D.52678, <variable>.pstDecodeFs
	cmp	r2, #0	@ D.52678,
	beq	.L1187	@,
	ldr	r3, [r4, #524]	@ D.52680, <variable>.pstDispOutFs
	cmp	r3, #0	@ D.52680,
	beq	.L1187	@,
	ldr	ip, [r4, #528]	@ D.52682, <variable>.pstTfOutFs
	cmp	ip, #0	@ D.52682,
	beq	.L1187	@,
	ldr	lr, [ip, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	mov	r0, r8	@, <variable>.eVidStd
	ldr	r2, [r2, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	movw	r1, #:lower16:.LC205	@,
	ldr	r3, [r3, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	movt	r1, #:upper16:.LC205	@,
	str	lr, [sp, #0]	@ <variable>.PhyAddr,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #520]	@ <variable>.pstDecodeFs, <variable>.pstDecodeFs
	mov	r0, #0	@ D.52654,
	ldr	ip, [r3, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	ip, [r7, #0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	ldr	r2, [r5, r6, asl #2]	@ tmp162, s_pstVfmwChan
	ldr	r1, [r2, #480]	@ <variable>.s32UsrdecFrameSize, <variable>.s32UsrdecFrameSize
	str	r1, [r7, #8]	@ <variable>.s32UsrdecFrameSize, <variable>.Length
.L1181:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L1192:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC201	@,
	movt	r1, #:upper16:.LC201	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52654,
	b	.L1181	@
.L1190:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC199	@,
	movt	r1, #:upper16:.LC199	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52654,
	b	.L1181	@
.L1191:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC200	@,
	movt	r1, #:upper16:.LC200	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52654,
	b	.L1181	@
.L1187:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC206	@,
	movt	r1, #:upper16:.LC206	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52654,
	b	.L1181	@
.L1193:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC202	@,
	movt	r1, #:upper16:.LC202	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52654,
	b	.L1181	@
.L1189:
	mov	r0, r3	@, D.52650
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #5365	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52654,
	b	.L1181	@
.L1194:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC204	@,
	movw	r2, #5396	@,
	movt	r1, #:upper16:.LC204	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52654,
	b	.L1181	@
	.fnend
	.size	VCTRL_GetUsrdecFrame, .-VCTRL_GetUsrdecFrame
	.align	2
	.global	VDH_PutUsrdecFrame
	.type	VDH_PutUsrdecFrame, %function
VDH_PutUsrdecFrame:
	.fnstart
.LFB1601:
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
	mov	r8, r1	@ pstUsrdecFrame, pstUsrdecFrame
	ldr	r1, [r1, #28]	@, <variable>.s32LumaPhyAddr
	mov	r7, r0	@ ChanID, ChanID
	bl	FSP_GetLogicIdByPhyAddr	@
	cmn	r0, #1	@ PicBufID,
	mov	r5, r0	@ PicBufID,
	beq	.L1204	@,
	ldr	r3, [r8, #4]	@ <variable>.s32IsFrameValid, <variable>.s32IsFrameValid
	cmp	r3, #1	@ <variable>.s32IsFrameValid,
	beq	.L1198	@,
	mov	r0, r7	@, ChanID
	mov	r1, r5	@, PicBufID
	mov	r2, #0	@,
	bl	FSP_ClearLogicFs	@
	mov	r0, #0	@ D.52581,
.L1197:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L1198:
	ldr	r0, [r8, #36]	@, <variable>.s32CbPhyAddr
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@,
	beq	.L1205	@,
.L1199:
	mov	r0, r7	@, ChanID
	mov	r1, r5	@, PicBufID
	bl	FSP_GetFsImagePtr	@
	subs	r4, r0, #0	@ pLogic,
	beq	.L1206	@,
	str	r5, [r4, #196]	@ PicBufID, <variable>.image_id
	mov	r6, #0	@ tmp166,
	ldrd	r0, [r8, #8]	@ <variable>.Pts, pstUsrdecFrame,
	mov	sl, #1	@ tmp165,
	strd	r0, [r4]	@ <variable>.Pts, <variable>.SrcPts
	ldrd	r2, [r8, #8]	@ <variable>.Pts, pstUsrdecFrame,
	strd	r2, [r4, #8]	@ <variable>.Pts, pLogic,
	ldrd	r0, [r8, #8]	@ <variable>.Pts, pstUsrdecFrame,
	strd	r0, [r4, #16]	@ <variable>.Pts, pLogic,
	ldrd	r2, [r8, #8]	@ <variable>.Pts, pstUsrdecFrame,
	str	sl, [r4, #68]	@ tmp165, <variable>.DispEnableFlag
	str	r6, [r4, #72]	@ tmp166, <variable>.DispFrameDistance
	strd	r2, [r4, #24]	@ <variable>.Pts, pLogic,
	str	r6, [r4, #76]	@ tmp166, <variable>.DistanceBeforeFirstFrame
	str	r6, [r4, #80]	@ tmp166, <variable>.GopNum
	ldr	r1, [r8, #28]	@ temp.3943, <variable>.s32LumaPhyAddr
	str	r1, [r4, #88]	@ temp.3943, <variable>.top_luma_phy_addr
	mov	r0, r1	@, temp.3943
	str	r1, [r4, #120]	@ temp.3943, <variable>.luma_2d_phy_addr
	str	r1, [r4, #104]	@ temp.3943, <variable>.luma_phy_addr
	ldr	lr, [r8, #36]	@ temp.3944, <variable>.s32CbPhyAddr
	str	lr, [r4, #108]	@ temp.3944, <variable>.chrom_phy_addr
	str	lr, [r4, #92]	@ temp.3944, <variable>.top_chrom_phy_addr
	str	lr, [r4, #124]	@ temp.3944, <variable>.chrom_2d_phy_addr
	bl	MEM_Phy2Vir	@
	str	r0, [r4, #32]	@ D.52604, <variable>.luma_vir_addr
	str	r0, [r4, #48]	@ D.52604, <variable>.luma_2d_vir_addr
	ldr	r0, [r4, #92]	@, <variable>.top_chrom_phy_addr
	bl	MEM_Phy2Vir	@
	ldr	ip, [r4, #88]	@ <variable>.top_luma_phy_addr, <variable>.top_luma_phy_addr
	str	r0, [r4, #36]	@ D.52607, <variable>.chrom_vir_addr
	str	r0, [r4, #52]	@ D.52607, <variable>.chrom_2d_vir_addr
	ldr	r3, [r8, #32]	@ <variable>.s32LumaStride, <variable>.s32LumaStride
	ldr	r0, [r4, #92]	@ <variable>.top_chrom_phy_addr, <variable>.top_chrom_phy_addr
	add	r2, r3, ip	@ tmp172, <variable>.s32LumaStride, <variable>.top_luma_phy_addr
	str	r2, [r4, #96]	@ tmp172, <variable>.btm_luma_phy_addr
	ldr	r1, [r8, #32]	@ <variable>.s32LumaStride, <variable>.s32LumaStride
	str	r6, [r4, #148]	@ tmp166, <variable>.is_fld_save
	add	r3, r1, r0	@ tmp175, <variable>.s32LumaStride, <variable>.top_chrom_phy_addr
	str	r3, [r4, #100]	@ tmp175, <variable>.btm_chrom_phy_addr
	ldr	ip, [r8, #20]	@ <variable>.s32YWidth, <variable>.s32YWidth
	str	ip, [r4, #164]	@ <variable>.s32YWidth, <variable>.image_width
	ldr	r2, [r8, #24]	@ <variable>.s32YHeight, <variable>.s32YHeight
	str	r2, [r4, #168]	@ <variable>.s32YHeight, <variable>.image_height
	movw	r2, #11296	@ tmp185,
	ldr	r0, [r8, #20]	@ temp.3948, <variable>.s32YWidth
	str	r0, [r4, #172]	@ temp.3948, <variable>.disp_width
	mov	r1, r0, lsr sl	@ tmp179, temp.3948,
	ldr	r3, [r8, #24]	@ temp.3950, <variable>.s32YHeight
	str	r1, [r4, #180]	@ tmp179, <variable>.disp_center_x
	str	r3, [r4, #176]	@ temp.3950, <variable>.disp_height
	mov	ip, r3, lsr sl	@ tmp180, temp.3950,
	str	ip, [r4, #184]	@ tmp180, <variable>.disp_center_y
	ldr	r0, [r8, #32]	@ <variable>.s32LumaStride, <variable>.s32LumaStride
	str	r2, [r4, #160]	@ tmp185, <variable>.format
	str	r6, [r4, #188]	@ tmp166, <variable>.frame_rate
	str	r0, [r4, #192]	@ <variable>.s32LumaStride, <variable>.image_stride
	str	r6, [r4, #200]	@ tmp166, <variable>.error_level
	str	sl, [r4, #228]	@ tmp165, <variable>.chroma_idc
	str	r6, [r4, #276]	@ tmp166, <variable>.line_num_phy_addr
	str	r6, [r4, #56]	@ tmp166, <variable>.line_num_vir_addr
	ldr	r0, [r8, #16]	@, <variable>.s32IsSemiPlanar
	ldr	r1, [r8, #0]	@, <variable>.enFmt
	bl	Get_YuvFormat	@
	cmp	r0, #13	@ eYuvFormat,
	mov	r2, r0	@ eYuvFormat,
	beq	.L1207	@,
	str	r0, [r4, #476]	@ eYuvFormat, <variable>.BTLInfo.YUVFormat
	mov	r2, sl	@, tmp165
	ldr	ip, [r8, #44]	@ <variable>.s32ChromStride, <variable>.s32ChromStride
	mov	sl, #18	@ tmp194,
	mov	r0, r7	@, ChanID
	mov	r1, r5	@, PicBufID
	str	ip, [r4, #452]	@ <variable>.s32ChromStride, <variable>.BTLInfo.u32CStride
	ldr	r3, [r8, #48]	@ <variable>.s32ChromCrStride, <variable>.s32ChromCrStride
	str	r3, [r4, #448]	@ <variable>.s32ChromCrStride, <variable>.BTLInfo.u32CrStride
	ldr	lr, [r8, #40]	@ <variable>.s32CrPhyAddr, <variable>.s32CrPhyAddr
	str	sl, [r4, #384]	@ tmp194, <variable>.ImageDnr.video_standard
	str	lr, [r4, #456]	@ <variable>.s32CrPhyAddr, <variable>.BTLInfo.u32CrAddr
	bl	FSP_SetDisplay	@
	movw	ip, #:lower16:.LANCHOR0	@ tmp195,
	movt	ip, #:upper16:.LANCHOR0	@ tmp195,
	str	r4, [sp, #0]	@ pLogic,
	mov	r1, sl	@, tmp194
	mov	r0, r7	@, ChanID
	ldr	r2, [ip, r7, asl #2]	@ D.52635, s_pstVfmwChan
	add	ip, r2, #250880	@, D.52635,
	add	r2, ip, #704	@, tmp3,
	add	r3, ip, #712	@,,
	bl	InsertImgToVoQueue	@
	cmp	r0, #1	@,
	moveq	r0, r6	@ D.52581, tmp166
	beq	.L1197	@,
	mov	r0, r7	@, ChanID
	ldr	r1, [r4, #212]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	mov	r0, r7	@, ChanID
	ldr	r1, [r4, #216]	@, <variable>.p_usrdat
	str	r6, [r4, #212]	@ tmp166, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	mov	r0, r7	@, ChanID
	str	r6, [r4, #216]	@ tmp166, <variable>.p_usrdat
	mov	r1, r5	@, PicBufID
	mov	r2, r6	@, tmp166
	bl	FSP_SetDisplay	@
	mvn	r0, #0	@ D.52581,
	b	.L1197	@
.L1205:
	ldr	r1, [r8, #4]	@ <variable>.s32IsFrameValid, <variable>.s32IsFrameValid
	cmp	r1, #1	@ <variable>.s32IsFrameValid,
	bne	.L1199	@,
	ldr	r2, [r8, #36]	@, <variable>.s32CbPhyAddr
	movw	r1, #:lower16:.LC208	@,
	movt	r1, #:upper16:.LC208	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52581,
	b	.L1197	@
.L1204:
	ldr	r2, [r8, #28]	@, <variable>.s32LumaPhyAddr
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC207	@,
	movt	r1, #:upper16:.LC207	@,
	bl	dprint_vfmw	@
	mov	r0, r5	@ D.52581, PicBufID
	b	.L1197	@
.L1207:
	mov	r0, sl	@, tmp165
	movw	r1, #:lower16:.LC210	@,
	movt	r1, #:upper16:.LC210	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52581,
	b	.L1197	@
.L1206:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC209	@,
	movw	r2, #5199	@,
	movt	r1, #:upper16:.LC209	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52581,
	b	.L1197	@
	.fnend
	.size	VDH_PutUsrdecFrame, .-VDH_PutUsrdecFrame
	.align	2
	.global	VCTRL_PutUsrdecFrame
	.type	VCTRL_PutUsrdecFrame, %function
VCTRL_PutUsrdecFrame:
	.fnstart
.LFB1603:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	mov	r6, r0	@ ChanID, ChanID
	mov	ip, r1	@ pUsrdecFrame, pUsrdecFrame
	ldr	lr, [r3, r0, asl #2]	@ D.52695, s_pstVfmwChan
	cmp	lr, #0	@ D.52695,
	beq	.L1215	@,
	cmp	r1, #0	@ pUsrdecFrame,
	beq	.L1216	@,
	ldr	r2, [lr, #544]	@ D.52702, <variable>.eVidStd
	cmp	r2, #18	@ D.52702,
	bne	.L1217	@,
	mov	r4, r1	@ pUsrdecFrame, pUsrdecFrame
	add	lr, lr, #488	@ tmp146, D.52695,
	ldmia	r4!, {r0, r1, r2, r3}	@ pUsrdecFrame,,,,
	mov	r5, lr	@ tmp147, tmp146
	stmia	r5!, {r0, r1, r2, r3}	@ tmp147,,,,
	mov	lr, r5	@ tmp152, tmp147
	ldmia	r4!, {r0, r1, r2, r3}	@ pUsrdecFrame,,,,
	stmia	lr!, {r0, r1, r2, r3}	@ tmp152,,,,
	ldmia	r4!, {r0, r1, r2, r3}	@ pUsrdecFrame,,,,
	stmia	lr!, {r0, r1, r2, r3}	@ tmp152,,,,
	ldmia	r4, {r0, r1}	@ pUsrdecFrame,,
	stmia	lr, {r0, r1}	@ tmp154,,
	mov	r0, r6	@, ChanID
	mov	r1, ip	@, pUsrdecFrame
	bl	VDH_PutUsrdecFrame	@
	cmp	r0, #0	@ D.52707
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC213	@,
	movt	r1, #:upper16:.LC213	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52699,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1217:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC212	@,
	movt	r1, #:upper16:.LC212	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52699,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1216:
	mov	r0, r1	@, pUsrdecFrame
	movw	r2, #5448	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC211	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC211	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52699,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1215:
	mov	r0, lr	@, D.52695
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #5447	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52699,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VCTRL_PutUsrdecFrame, .-VCTRL_PutUsrdecFrame
	.align	2
	.global	USERDEC_RecycleImage
	.type	USERDEC_RecycleImage, %function
USERDEC_RecycleImage:
	.fnstart
.LFB1600:
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
	subs	r4, r0, #0	@ pCtx, pCtx
	mov	r5, r1	@ ImgID, ImgID
	mvneq	r0, #1	@ D.52560,
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	ldr	r0, [r4, #360]	@, <variable>.ChanID
	mov	r2, #0	@,
	bl	FSP_SetDisplay	@
	mov	r1, r5	@, ImgID
	ldr	r0, [r4, #360]	@, <variable>.ChanID
	bl	FSP_GetFsImagePtr	@
	subs	r5, r0, #0	@ pImg,
	moveq	r0, #1	@ D.52560,
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	ldr	r0, [r4, #360]	@, <variable>.ChanID
	mov	r6, #0	@ tmp143,
	ldr	r1, [r5, #212]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	str	r6, [r5, #212]	@ tmp143, <variable>.p_usrdat
	ldr	r1, [r5, #216]	@, <variable>.p_usrdat
	ldr	r0, [r4, #360]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	mov	r0, #1	@ D.52560,
	str	r6, [r5, #216]	@ tmp143, <variable>.p_usrdat
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	USERDEC_RecycleImage, .-USERDEC_RecycleImage
	.align	2
	.global	USERDEC_Init
	.type	USERDEC_Init, %function
USERDEC_Init:
	.fnstart
.LFB1599:
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
	ldr	r6, [r0, #352]	@ D.52539, <variable>.ImageQue.ResetMagicWord
	mov	r4, r0	@ pCtx, pCtx
	mov	r5, r1	@ pstExtraData, pstExtraData
	mov	r1, #368	@,
	bl	__memzero	@
	add	r0, r4, #8	@, pCtx,
	str	r6, [r4, #352]	@ D.52539, <variable>.ImageQue.ResetMagicWord
	bl	ResetVoQueue	@
	movw	r3, #:lower16:.LANCHOR0	@ tmp207,
	movt	r3, #:upper16:.LANCHOR0	@ tmp207,
	str	r5, [r4, #0]	@ pstExtraData, <variable>.pstExtraData
	ldr	r2, [r3, #0]	@ temp.4030, s_pstVfmwChan
	cmp	r2, #0	@ temp.4030,
	beq	.L1224	@,
	add	r0, r2, #250880	@ tmp157, temp.4030,
	add	r2, r0, #704	@ tmp157, tmp157,
	cmp	r4, r2	@ pCtx, tmp157
	moveq	r3, #0	@ i,
	beq	.L1225	@,
.L1224:
	ldr	r2, [r3, #4]	@ temp.4032, s_pstVfmwChan
	cmp	r2, #0	@ temp.4032,
	beq	.L1226	@,
	add	ip, r2, #250880	@ tmp160, temp.4032,
	add	r1, ip, #704	@ tmp160, tmp160,
	cmp	r4, r1	@ pCtx, tmp160
	moveq	r3, #1	@ i,
	beq	.L1225	@,
.L1226:
	ldr	r2, [r3, #8]	@ temp.4034, s_pstVfmwChan
	cmp	r2, #0	@ temp.4034,
	beq	.L1227	@,
	add	r2, r2, #250880	@ tmp163, temp.4034,
	add	lr, r2, #704	@ tmp163, tmp163,
	cmp	r4, lr	@ pCtx, tmp163
	moveq	r3, #2	@ i,
	beq	.L1225	@,
.L1227:
	ldr	r2, [r3, #12]	@ temp.4036, s_pstVfmwChan
	cmp	r2, #0	@ temp.4036,
	beq	.L1228	@,
	add	r1, r2, #250880	@ tmp166, temp.4036,
	add	r0, r1, #704	@ tmp166, tmp166,
	cmp	r4, r0	@ pCtx, tmp166
	moveq	r3, #3	@ i,
	beq	.L1225	@,
.L1228:
	ldr	r2, [r3, #16]	@ temp.4038, s_pstVfmwChan
	cmp	r2, #0	@ temp.4038,
	beq	.L1229	@,
	add	lr, r2, #250880	@ tmp169, temp.4038,
	add	ip, lr, #704	@ tmp169, tmp169,
	cmp	r4, ip	@ pCtx, tmp169
	moveq	r3, #4	@ i,
	beq	.L1225	@,
.L1229:
	ldr	r2, [r3, #20]	@ temp.4040, s_pstVfmwChan
	cmp	r2, #0	@ temp.4040,
	beq	.L1230	@,
	add	r0, r2, #250880	@ tmp172, temp.4040,
	add	r2, r0, #704	@ tmp172, tmp172,
	cmp	r4, r2	@ pCtx, tmp172
	moveq	r3, #5	@ i,
	beq	.L1225	@,
.L1230:
	ldr	r2, [r3, #24]	@ temp.4042, s_pstVfmwChan
	cmp	r2, #0	@ temp.4042,
	beq	.L1231	@,
	add	ip, r2, #250880	@ tmp175, temp.4042,
	add	r1, ip, #704	@ tmp175, tmp175,
	cmp	r4, r1	@ pCtx, tmp175
	moveq	r3, #6	@ i,
	beq	.L1225	@,
.L1231:
	ldr	r2, [r3, #28]	@ temp.4044, s_pstVfmwChan
	cmp	r2, #0	@ temp.4044,
	beq	.L1232	@,
	add	r2, r2, #250880	@ tmp178, temp.4044,
	add	lr, r2, #704	@ tmp178, tmp178,
	cmp	r4, lr	@ pCtx, tmp178
	moveq	r3, #7	@ i,
	beq	.L1225	@,
.L1232:
	ldr	r2, [r3, #32]	@ temp.4046, s_pstVfmwChan
	cmp	r2, #0	@ temp.4046,
	beq	.L1233	@,
	add	r1, r2, #250880	@ tmp181, temp.4046,
	add	r0, r1, #704	@ tmp181, tmp181,
	cmp	r4, r0	@ pCtx, tmp181
	moveq	r3, #8	@ i,
	beq	.L1225	@,
.L1233:
	ldr	r2, [r3, #36]	@ temp.4048, s_pstVfmwChan
	cmp	r2, #0	@ temp.4048,
	beq	.L1234	@,
	add	lr, r2, #250880	@ tmp184, temp.4048,
	add	ip, lr, #704	@ tmp184, tmp184,
	cmp	r4, ip	@ pCtx, tmp184
	moveq	r3, #9	@ i,
	beq	.L1225	@,
.L1234:
	ldr	r2, [r3, #40]	@ temp.4050, s_pstVfmwChan
	cmp	r2, #0	@ temp.4050,
	beq	.L1235	@,
	add	r0, r2, #250880	@ tmp187, temp.4050,
	add	r2, r0, #704	@ tmp187, tmp187,
	cmp	r4, r2	@ pCtx, tmp187
	moveq	r3, #10	@ i,
	beq	.L1225	@,
.L1235:
	ldr	r2, [r3, #44]	@ temp.4052, s_pstVfmwChan
	cmp	r2, #0	@ temp.4052,
	beq	.L1236	@,
	add	ip, r2, #250880	@ tmp190, temp.4052,
	add	r1, ip, #704	@ tmp190, tmp190,
	cmp	r4, r1	@ pCtx, tmp190
	moveq	r3, #11	@ i,
	beq	.L1225	@,
.L1236:
	ldr	r2, [r3, #48]	@ temp.4054, s_pstVfmwChan
	cmp	r2, #0	@ temp.4054,
	beq	.L1237	@,
	add	r2, r2, #250880	@ tmp193, temp.4054,
	add	lr, r2, #704	@ tmp193, tmp193,
	cmp	r4, lr	@ pCtx, tmp193
	moveq	r3, #12	@ i,
	beq	.L1225	@,
.L1237:
	ldr	r2, [r3, #52]	@ temp.4056, s_pstVfmwChan
	cmp	r2, #0	@ temp.4056,
	beq	.L1238	@,
	add	r1, r2, #250880	@ tmp196, temp.4056,
	add	r0, r1, #704	@ tmp196, tmp196,
	cmp	r4, r0	@ pCtx, tmp196
	moveq	r3, #13	@ i,
	beq	.L1225	@,
.L1238:
	ldr	r2, [r3, #56]	@ temp.4058, s_pstVfmwChan
	cmp	r2, #0	@ temp.4058,
	beq	.L1239	@,
	add	lr, r2, #250880	@ tmp199, temp.4058,
	add	ip, lr, #704	@ tmp199, tmp199,
	cmp	r4, ip	@ pCtx, tmp199
	moveq	r3, #14	@ i,
	beq	.L1225	@,
.L1239:
	ldr	r3, [r3, #60]	@ D.56235, s_pstVfmwChan
	cmp	r3, #0	@ D.56235,
	beq	.L1240	@,
	add	r2, r3, #250880	@ tmp202, D.56235,
	add	r3, r2, #704	@ tmp202, tmp202,
	cmp	r4, r3	@ pCtx, tmp202
	beq	.L1241	@,
.L1240:
	mvn	r0, #0	@ tmp204,
	movw	r1, #:lower16:.LC214	@,
	str	r0, [r4, #360]	@ tmp204, <variable>.ChanID
	movt	r1, #:upper16:.LC214	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	mvn	r0, #19	@ D.52552,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1241:
	mov	r3, #15	@ i,
.L1225:
	mov	r0, #1	@ D.52552,
	str	r3, [r4, #360]	@ i, <variable>.ChanID
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	USERDEC_Init, .-USERDEC_Init
	.align	2
	.global	InitSyntaxCtx
	.type	InitSyntaxCtx, %function
InitSyntaxCtx:
	.fnstart
.LFB1604:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp184,
	movt	r3, #:upper16:.LANCHOR0	@ tmp184,
	ldr	r1, [r3, r0, asl #2]	@ D.52734, s_pstVfmwChan
	cmp	r1, #0	@ D.52734,
	beq	.L1263	@,
	ldr	r2, [r1, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, #18	@ <variable>.eVidStd,
	ldrls	pc, [pc, r2, asl #2]	@ <variable>.eVidStd
	b	.L1262	@
.L1261:
	.word	.L1247
	.word	.L1248
	.word	.L1249
	.word	.L1250
	.word	.L1251
	.word	.L1252
	.word	.L1253
	.word	.L1262
	.word	.L1254
	.word	.L1255
	.word	.L1256
	.word	.L1256
	.word	.L1256
	.word	.L1257
	.word	.L1251
	.word	.L1258
	.word	.L1259
	.word	.L1262
	.word	.L1260
.L1260:
	add	lr, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, lr, #704	@,,
	bl	USERDEC_Init	@
.L1262:
	ldmfd	sp, {fp, sp, pc}	@
.L1247:
	add	ip, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, ip, #704	@,,
	bl	H264DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1248:
	add	lr, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, lr, #704	@,,
	bl	VC1DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1249:
	add	r3, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, r3, #704	@,,
	bl	MPEG4DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1250:
	add	r0, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, r0, #704	@,,
	bl	MPEG2DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1251:
	ldr	r3, [r3, #84]	@ D.52751, g_SdecFunc.pfun_iMediaSoftDEC_Init
	cmp	r3, #0	@ D.52751,
	ldmeqfd	sp, {fp, sp, pc}	@
	add	r0, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, r0, #704	@,,
	blx	r3	@ D.52751
	ldmfd	sp, {fp, sp, pc}	@
.L1252:
	add	ip, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, ip, #704	@,,
	bl	DIVX3DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1253:
	add	r2, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, r2, #704	@,,
	bl	AVSDEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1254:
	add	r0, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, r0, #704	@,,
	bl	REAL8DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1255:
	add	r3, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, r3, #704	@,,
	bl	REAL9DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1256:
	add	r2, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, r2, #704	@,,
	bl	VP6DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1257:
	add	r3, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, r3, #704	@,,
	bl	VP8DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1258:
	add	ip, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, ip, #704	@,,
	bl	MVC_DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1259:
	add	lr, r1, #250880	@, D.52734,
	add	r1, r1, #552	@, D.52734,
	add	r0, lr, #704	@,,
	bl	HEVCDEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1263:
	mov	r0, r1	@, D.52734
	movw	r2, #5475	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	InitSyntaxCtx, .-InitSyntaxCtx
	.align	2
	.global	VCTRL_GetImageBuffer
	.type	VCTRL_GetImageBuffer, %function
VCTRL_GetImageBuffer:
	.fnstart
.LFB1593:
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
	cmp	r0, #15	@ ChanId,
	bhi	.L1285	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp174,
	movt	r3, #:upper16:.LANCHOR0	@ tmp174,
	ldr	r0, [r3, r0, asl #2]	@ D.52398, s_pstVfmwChan
	cmp	r0, #0	@ D.52398,
	beq	.L1286	@,
	ldr	r2, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r2, #1	@ <variable>.s32IsRun,
	bne	.L1287	@,
	ldr	r1, [r0, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r1, #16	@ <variable>.eVidStd,
	ldrls	pc, [pc, r1, asl #2]	@ <variable>.eVidStd
	b	.L1269	@
.L1283:
	.word	.L1270
	.word	.L1271
	.word	.L1272
	.word	.L1273
	.word	.L1274
	.word	.L1275
	.word	.L1276
	.word	.L1269
	.word	.L1277
	.word	.L1278
	.word	.L1279
	.word	.L1279
	.word	.L1279
	.word	.L1280
	.word	.L1274
	.word	.L1281
	.word	.L1282
.L1279:
	ldr	r2, [r3, #516]	@ g_VdmCharacter, g_VdmCharacter
	tst	r2, #1	@ g_VdmCharacter,
	bne	.L1288	@,
.L1274:
	mov	r0, #1	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
.L1275:
	add	r3, r0, #250880	@, D.52398,
	add	r0, r3, #704	@,,
	bl	DIVX3DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1276:
	add	r2, r0, #250880	@, D.52398,
	add	r0, r2, #704	@,,
	bl	AVSDEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1277:
	add	r1, r0, #250880	@, D.52398,
	add	r0, r1, #704	@,,
	bl	REAL8DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1278:
	add	r0, r0, #250880	@, D.52398,
	add	r0, r0, #704	@,,
	bl	REAL9DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1280:
	add	r1, r0, #250880	@, D.52398,
	add	r0, r1, #704	@,,
	bl	VP8DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1281:
	add	r0, r0, #250880	@, D.52398,
	add	r0, r0, #704	@,,
	bl	MVC_DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1282:
	add	r3, r0, #250880	@, D.52398,
	add	r0, r3, #704	@,,
	bl	HEVCDEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1269:
	mov	r0, #0	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
.L1270:
	add	r0, r0, #250880	@, D.52398,
	add	r0, r0, #704	@,,
	bl	H264DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1271:
	add	ip, r0, #250880	@, D.52398,
	add	r0, ip, #704	@,,
	bl	VC1DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1272:
	add	lr, r0, #250880	@, D.52398,
	add	r0, lr, #704	@,,
	bl	MPEG4DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1273:
	add	ip, r0, #250880	@, D.52398,
	add	r0, ip, #704	@,,
	bl	MPEG2DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1288:
	add	lr, r0, #250880	@, D.52398,
	add	r0, lr, #704	@,,
	bl	VP6DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1287:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4916	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC216	@,
	movt	r3, #:upper16:.LC216	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
.L1285:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4914	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC28	@,
	movt	r3, #:upper16:.LC28	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
.L1286:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4915	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC215	@,
	movt	r3, #:upper16:.LC215	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_GetImageBuffer, .-VCTRL_GetImageBuffer
	.align	2
	.global	DecChanSyntax
	.type	DecChanSyntax, %function
DecChanSyntax:
	.fnstart
.LFB1614:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #60
	sub	sp, sp, #60	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ ChanID,
	mov	r4, r0	@ ChanID, ChanID
	bhi	.L1328	@,
	movw	r5, #:lower16:.LANCHOR0	@ tmp413,
	movt	r5, #:upper16:.LANCHOR0	@ tmp413,
	ldr	r0, [r5, r0, asl #2]	@ D.53512, s_pstVfmwChan
	cmp	r0, #0	@ D.53512,
	beq	.L1329	@,
	ldr	sl, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	sl, #1	@ <variable>.s32IsRun,
	bne	.L1330	@,
	ldr	r6, [r0, #28]	@ <variable>.s32StopSyntax, <variable>.s32StopSyntax
	cmp	r6, #0	@ <variable>.s32StopSyntax,
	bne	.L1331	@,
	str	r6, [r0, #332]	@ <variable>.s32StopSyntax, <variable>.s32NoStreamFlag
	mov	r0, r4, asl #2	@, ChanID,
	str	r0, [fp, #-88]	@, %sfp
	bl	OSAL_GetTimeInMs	@
	ldr	r3, [fp, #-88]	@, %sfp
	movw	r7, #:lower16:.LANCHOR3	@ tmp414,
	movt	r7, #:upper16:.LANCHOR3	@ tmp414,
	movw	r1, #:lower16:g_TraceBsPeriod	@ tmp189,
	add	ip, r3, r7	@ tmp185,, tmp414
	movt	r1, #:upper16:g_TraceBsPeriod	@ tmp189,
	ldr	r2, [ip, #-1924]	@ tmp188, last_rec_pos_time
	ldr	r3, [r1, #0]	@ g_TraceBsPeriod, g_TraceBsPeriod
	rsb	r1, r2, r0	@ tmp187, tmp188, currtime
	ldr	r2, [r5, r4, asl #2]	@ tmp197, s_pstVfmwChan
	cmp	r1, r3	@ tmp187, g_TraceBsPeriod
	strhi	r0, [ip, #-1924]	@ currtime, last_rec_pos_time
	movw	r3, #:lower16:.LANCHOR0	@ tmp196,
	movt	r3, #:upper16:.LANCHOR0	@ tmp196,
	ldr	r2, [r2, #544]	@ D.53531, <variable>.eVidStd
	movls	sl, r6	@ rec_pos_print_flag, <variable>.s32StopSyntax
	sub	r1, r2, #10	@ tmp198, D.53531,
	cmp	r1, #2	@ tmp198,
	bls	.L1332	@,
	cmp	r2, #14	@ D.53531,
	beq	.L1299	@,
	cmp	r2, #4	@ D.53531,
	bne	.L1298	@,
.L1299:
	mov	r0, r4	@, ChanID
	bl	VCTRL_GetImageBuffer	@
	cmp	r0, #1	@,
	bne	.L1333	@,
	ldr	r6, [r5, r4, asl #2]	@ temp.4168, s_pstVfmwChan
	ldr	r2, [r6, #1416]	@ D.53556, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r2, #0	@ D.53556,
	beq	.L1303	@,
	cmp	r2, #1	@ D.53556,
	beq	.L1334	@,
	movw	lr, #:lower16:249248	@ tmp408,
	movt	lr, #:upper16:249248	@ tmp408,
	ldr	r3, [r6, lr]	@ prephitmp.4151, <variable>.FspInst.eFspPartitionState
.L1323:
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC227	@,
	movt	r1, #:upper16:.LC227	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53510,
.L1291:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1332:
	ldr	lr, [r3, #516]	@ g_VdmCharacter, g_VdmCharacter
	tst	lr, #1	@ g_VdmCharacter,
	beq	.L1299	@,
.L1298:
	cmp	r2, #18	@ D.53531,
	beq	.L1299	@,
	mov	r0, r4	@, ChanID
	bl	VCTRL_GetDecParam	@
	cmp	r0, #0	@,
	beq	.L1299	@,
	cmp	sl, #1	@ rec_pos_print_flag,
	beq	.L1300	@,
	mvn	r0, #1	@ D.53510,
	b	.L1291	@
.L1303:
	ldrb	r2, [r6, #689]	@ zero_extendqisi2	@ <variable>.stSynExtraData.stSegPacket.IsCurrSegWaitDec, <variable>.stSynExtraData.stSegPacket.IsCurrSegWaitDec
	cmp	r2, #0	@ <variable>.stSynExtraData.stSegPacket.IsCurrSegWaitDec,
	bne	.L1306	@,
	ldr	r1, [r6, #1456]	@ <variable>.stSynExtraData.s32WaitFsFlag, <variable>.stSynExtraData.s32WaitFsFlag
	cmp	r1, #0	@ <variable>.stSynExtraData.s32WaitFsFlag,
	beq	.L1335	@,
.L1306:
	mov	r0, #720	@ tmp221,
	mov	ip, #736	@ tmp223,
	ldrd	r8, [r6, r0]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.Pts, temp.4168, tmp221
	movw	r1, #:lower16:.LC221	@,
	ldrd	r2, [r6, ip]	@, temp.4168, tmp223
	movt	r1, #:upper16:.LC221	@,
	mov	r0, #29	@,
	strd	r2, [sp]	@,
	mov	r2, r8	@, <variable>.stSynExtraData.stSegPacket.CurrSeg.Pts
	mov	r3, r9	@, <variable>.stSynExtraData.stSegPacket.CurrSeg.Pts
	bl	dprint_vfmw	@
	ldr	r0, [r5, r4, asl #2]	@ prephitmp.4149, s_pstVfmwChan
	ldr	r1, [r0, #48]	@ D.53583, <variable>.stChanCfg.eVidStd
	cmp	r1, #1	@ D.53583,
	beq	.L1336	@,
	sub	ip, r1, #2	@ tmp235, D.53583,
	cmp	r1, #6	@ D.53583,
	cmpne	ip, #1	@, tmp235,
	bls	.L1310	@,
.L1309:
	mov	r3, #720	@ tmp336,
	mvn	r8, #0	@,
	ldrd	r2, [r3, r6]	@ temp.4171, tmp336, temp.4168
	mvn	r9, #0	@,
	cmp	r3, r9	@ temp.4171,
	cmpeq	r2, r8	@ temp.4171,
	movne	r1, #608	@ tmp338,
	strned	r2, [r0, r1]	@ temp.4171, prephitmp.4149, tmp338
	ldrne	r0, [r5, r4, asl #2]	@ prephitmp.4149, s_pstVfmwChan
.L1318:
	mov	r1, #736	@ tmp341,
	mov	r3, #624	@ tmp340,
	ldrd	r8, [r6, r1]	@, temp.4168, tmp341
	mov	r2, #640	@ tmp345,
	ldr	lr, [r6, #752]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag, <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag
	movw	r1, #:lower16:.LC224	@,
	movt	r1, #:upper16:.LC224	@,
	strd	r8, [r0, r3]	@, prephitmp.4149, tmp340
	mov	r0, #744	@ tmp346,
	ldr	ip, [r5, r4, asl #2]	@ tmp344, s_pstVfmwChan
	ldrd	r8, [r6, r0]	@, temp.4168, tmp346
	mov	r0, #29	@,
	strd	r8, [ip, r2]	@, tmp344, tmp345
	ldr	ip, [r5, r4, asl #2]	@ tmp349, s_pstVfmwChan
	ldr	r9, [r6, #756]	@, <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance
	ldr	r2, [r6, #764]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum, <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum
	str	lr, [ip, #656]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag, <variable>.stSynExtraData.DispEnableFlag
	ldr	ip, [r5, r4, asl #2]	@ tmp352, s_pstVfmwChan
	ldr	lr, [r6, #760]	@, <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame
	str	r9, [ip, #660]	@, <variable>.stSynExtraData.DispFrameDistance
	ldr	ip, [r5, r4, asl #2]	@ tmp355, s_pstVfmwChan
	str	lr, [ip, #664]	@, <variable>.stSynExtraData.DistanceBeforeFirstFrame
	mov	ip, #608	@ tmp362,
	ldr	r9, [r5, r4, asl #2]	@ tmp358, s_pstVfmwChan
	str	r2, [r9, #680]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum, <variable>.stSynExtraData.GopNum
	ldr	lr, [r5, r4, asl #2]	@ temp.4178, s_pstVfmwChan
	add	r2, lr, ip	@, temp.4178, tmp362
	ldrd	r8, [lr, r3]	@, temp.4178, tmp340
	ldrd	r2, [r2]	@ <variable>.stSynExtraData.pts,
	strd	r8, [sp]	@,
	bl	dprint_vfmw	@
.L1317:
	mov	r0, #3	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	beq	.L1319	@,
	cmp	sl, #1	@ rec_pos_print_flag,
	beq	.L1337	@,
.L1319:
	ldr	lr, [r5, r4, asl #2]	@ temp.4220, s_pstVfmwChan
	add	r0, r6, #688	@, temp.4168,
	movw	r6, #:lower16:.LANCHOR0	@ tmp370,
	movt	r6, #:upper16:.LANCHOR0	@ tmp370,
	add	ip, lr, #250880	@, temp.4220,
	add	r2, ip, #704	@,,
	ldr	r1, [lr, #544]	@, <variable>.eVidStd
	bl	DecodeStream	@
	ldr	r0, [r5, r4, asl #2]	@ temp.4222, s_pstVfmwChan
	ldr	r2, [r0, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, #16	@ <variable>.eVidStd,
	beq	.L1338	@,
.L1320:
	mov	r0, #4	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	bne	.L1339	@,
.L1322:
	mov	r0, #0	@ D.53510,
	b	.L1291	@
.L1336:
	movw	r3, #:lower16:251584	@ tmp227,
	movt	r3, #:upper16:251584	@ tmp227,
	ldr	lr, [r0, r3]	@ <variable>.stSynCtx.unSyntax.stVc1Ctx.pstExtraData, <variable>.stSynCtx.unSyntax.stVc1Ctx.pstExtraData
	ldrb	r2, [lr, #556]	@ zero_extendqisi2	@ <variable>.StdExt.Vc1Ext.IsAdvProfile, <variable>.StdExt.Vc1Ext.IsAdvProfile
	cmp	r2, #1	@ <variable>.StdExt.Vc1Ext.IsAdvProfile,
	bne	.L1309	@,
.L1310:
	add	r0, r0, #1104	@, prephitmp.4149,
	add	r2, r6, #696	@, temp.4168,
	bl	IsNewpicSeg	@
	cmp	r0, #0	@,
	beq	.L1340	@,
.L1311:
	ldr	r3, [r5, r4, asl #2]	@ temp.4169, s_pstVfmwChan
	ldr	r1, [r3, #48]	@ <variable>.stChanCfg.eVidStd, <variable>.stChanCfg.eVidStd
	cmp	r1, #3	@ <variable>.stChanCfg.eVidStd,
	beq	.L1315	@,
.L1314:
	mov	r9, #720	@ tmp307,
	mvn	r8, #0	@,
	ldrd	r0, [r6, r9]	@ temp.4206, temp.4168, tmp307
	mvn	r9, #0	@,
	cmp	r1, r9	@ temp.4206,
	cmpeq	r0, r8	@ temp.4206,
	movne	ip, #616	@ tmp309,
	strned	r0, [r3, ip]	@ temp.4206, temp.4169, tmp309
.L1316:
	mov	r8, #736	@ tmp313,
	ldr	ip, [r5, r4, asl #2]	@ tmp311, s_pstVfmwChan
	ldrd	r0, [r6, r8]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.Usertag, temp.4168, tmp313
	mov	r2, #744	@ tmp318,
	mov	r3, #632	@ tmp312,
	ldrd	r8, [r6, r2]	@, temp.4168, tmp318
	mov	lr, #648	@ tmp317,
	strd	r0, [ip, r3]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.Usertag, tmp311, tmp312
	ldr	r2, [r5, r4, asl #2]	@ tmp316, s_pstVfmwChan
	ldr	ip, [r6, #752]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag, <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag
	ldr	r0, [r6, #756]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance, <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance
	strd	r8, [r2, lr]	@, tmp316, tmp317
	ldr	r3, [r5, r4, asl #2]	@ tmp321, s_pstVfmwChan
	ldr	lr, [r6, #760]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame, <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame
	ldr	r2, [r6, #764]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum, <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum
	str	ip, [r3, #668]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag, <variable>.stSynExtraData.NextDispEnableFlag
	ldr	ip, [r5, r4, asl #2]	@ tmp324, s_pstVfmwChan
	str	r0, [ip, #672]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance, <variable>.stSynExtraData.NextDispFrameDistance
	ldr	r0, [r5, r4, asl #2]	@ tmp327, s_pstVfmwChan
	str	lr, [r0, #676]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame, <variable>.stSynExtraData.NextDistanceBeforeFirstFrame
	ldr	r3, [r5, r4, asl #2]	@ tmp330, s_pstVfmwChan
	str	r2, [r3, #684]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum, <variable>.stSynExtraData.NextGopNum
	ldr	r3, [r5, r4, asl #2]	@ temp.4169, s_pstVfmwChan
.L1315:
	mov	r0, #624	@ tmp334,
	add	r2, r3, r0	@, temp.4169, tmp334
	movw	r1, #:lower16:.LC223	@,
	mov	r0, #29	@,
	ldrd	r2, [r2]	@,
	movt	r1, #:upper16:.LC223	@,
	bl	dprint_vfmw	@
	b	.L1317	@
.L1339:
	bl	OSAL_GetTimeInMs	@
	ldr	r9, [fp, #-88]	@, %sfp
	movw	r2, #:lower16:g_TraceFramePeriod	@ tmp396,
	movt	r2, #:upper16:g_TraceFramePeriod	@ tmp396,
	add	r7, r9, r7	@ tmp392,, tmp414
	ldr	r1, [r7, #-1860]	@ tmp395, last_rec_pos_decparam_time
	mov	r3, r0	@ currtime.4227,
	ldr	r0, [r2, #0]	@ g_TraceFramePeriod, g_TraceFramePeriod
	rsb	ip, r1, r3	@ tmp394, tmp395, currtime.4227
	cmp	ip, r0	@ tmp394, g_TraceFramePeriod
	bls	.L1322	@,
	mov	r0, r4	@, ChanID
	str	r3, [r7, #-1860]	@ currtime.4227, last_rec_pos_decparam_time
	bl	VCTRL_GetDecParam	@
	cmp	r0, #0	@,
	beq	.L1322	@,
	mov	r3, r4, asl #24	@ tmp405, ChanID,
	ldr	r0, .L1344	@,
	add	r2, r3, #262144	@, tmp405,
	movw	r1, #7297	@,
	bl	DBG_AddTrace	@
	mov	r0, #0	@ D.53510,
	b	.L1291	@
.L1340:
	ldr	r3, [r5, r4, asl #2]	@ prephitmp.4145, s_pstVfmwChan
	movw	r2, #:lower16:.LANCHOR0	@ tmp245,
	movt	r2, #:upper16:.LANCHOR0	@ tmp245,
	ldr	r8, [r3, #48]	@ <variable>.stChanCfg.eVidStd, <variable>.stChanCfg.eVidStd
	cmp	r8, #3	@ <variable>.stChanCfg.eVidStd,
	beq	.L1341	@,
	mov	r1, #616	@ tmp251,
	mvn	r8, #0	@,
	ldrd	r0, [r1, r3]	@ temp.4181, tmp251, prephitmp.4145
	mvn	r9, #0	@,
	cmp	r1, r9	@ temp.4181,
	cmpeq	r0, r8	@ temp.4181,
	movne	r9, #608	@ tmp253,
	strned	r0, [r3, r9]	@ temp.4181, prephitmp.4145, tmp253
	ldrne	r3, [r2, r4, asl #2]	@ prephitmp.4145, s_pstVfmwChan
.L1313:
	mov	r9, #616	@,
	mvn	r0, #0	@ tmp256,
	mvn	r1, #0	@,
	strd	r0, [r3, r9]	@ tmp256, prephitmp.4145,
	ldr	lr, [r5, r4, asl #2]	@ temp.4183, s_pstVfmwChan
	mov	ip, #632	@ tmp259,
	mov	r8, #624	@ tmp258,
	mov	r0, #29	@,
	movw	r1, #:lower16:.LC222	@,
	movt	r1, #:upper16:.LC222	@,
	ldrd	r2, [lr, ip]	@, temp.4183, tmp259
	movw	r9, #:lower16:.LANCHOR0	@ tmp257,
	movt	r9, #:upper16:.LANCHOR0	@ tmp257,
	strd	r2, [lr, r8]	@, temp.4183, tmp258
	mov	r3, #648	@,
	ldr	lr, [r5, r4, asl #2]	@ temp.4184, s_pstVfmwChan
	mov	r8, #640	@ tmp262,
	ldrd	r2, [r3, lr]	@,, temp.4184
	strd	r2, [lr, r8]	@, temp.4184, tmp262
	ldr	r3, [r5, r4, asl #2]	@ temp.4185, s_pstVfmwChan
	ldr	lr, [r3, #668]	@ <variable>.stSynExtraData.NextDispEnableFlag, <variable>.stSynExtraData.NextDispEnableFlag
	str	lr, [r3, #656]	@ <variable>.stSynExtraData.NextDispEnableFlag, <variable>.stSynExtraData.DispEnableFlag
	ldr	r2, [r5, r4, asl #2]	@ temp.4186, s_pstVfmwChan
	ldr	r8, [r2, #672]	@ <variable>.stSynExtraData.NextDispFrameDistance, <variable>.stSynExtraData.NextDispFrameDistance
	str	r8, [r2, #660]	@ <variable>.stSynExtraData.NextDispFrameDistance, <variable>.stSynExtraData.DispFrameDistance
	ldr	r3, [r5, r4, asl #2]	@ temp.4187, s_pstVfmwChan
	ldr	lr, [r3, #676]	@ <variable>.stSynExtraData.NextDistanceBeforeFirstFrame, <variable>.stSynExtraData.NextDistanceBeforeFirstFrame
	str	lr, [r3, #664]	@ <variable>.stSynExtraData.NextDistanceBeforeFirstFrame, <variable>.stSynExtraData.DistanceBeforeFirstFrame
	mov	r3, #608	@ tmp276,
	ldr	r2, [r5, r4, asl #2]	@ temp.4188, s_pstVfmwChan
	ldr	r8, [r2, #684]	@ <variable>.stSynExtraData.NextGopNum, <variable>.stSynExtraData.NextGopNum
	str	r8, [r2, #680]	@ <variable>.stSynExtraData.NextGopNum, <variable>.stSynExtraData.GopNum
	ldr	lr, [r5, r4, asl #2]	@ tmp275, s_pstVfmwChan
	add	r2, lr, r3	@, tmp275, tmp276
	ldrd	r2, [r2]	@,
	str	ip, [fp, #-80]	@,
	bl	dprint_vfmw	@
	ldr	r3, [r5, r4, asl #2]	@ temp.4169, s_pstVfmwChan
	ldr	ip, [fp, #-80]	@,
	ldr	r2, [r3, #48]	@ <variable>.stChanCfg.eVidStd, <variable>.stChanCfg.eVidStd
	cmp	r2, #3	@ <variable>.stChanCfg.eVidStd,
	bne	.L1314	@,
	mov	r8, #720	@ tmp281,
	mov	lr, #736	@ tmp286,
	ldrd	r0, [r6, r8]	@, temp.4168, tmp281
	mov	r2, #744	@ tmp291,
	mov	r8, #616	@,
	strd	r0, [fp, #-76]	@,,
	ldrd	r0, [r6, lr]	@, temp.4168, tmp286
	strd	r0, [fp, #-52]	@,,
	ldrd	r0, [r6, r2]	@, temp.4168, tmp291
	strd	r0, [fp, #-60]	@,,
	ldrd	r0, [fp, #-76]	@,,
	ldr	lr, [r6, #756]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance, <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance
	strd	r0, [r3, r8]	@, temp.4169,
	ldrd	r0, [fp, #-52]	@,,
	ldr	r3, [r9, r4, asl #2]	@ tmp284, s_pstVfmwChan
	ldr	r8, [r6, #752]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag, <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag
	strd	r0, [r3, ip]	@, tmp284, tmp259
	mov	ip, #648	@,
	ldr	r0, [r9, r4, asl #2]	@ tmp289, s_pstVfmwChan
	ldrd	r2, [fp, #-60]	@,,
	ldr	r1, [r6, #760]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame, <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame
	strd	r2, [r0, ip]	@, tmp289,
	ldr	r0, [r9, r4, asl #2]	@ tmp294, s_pstVfmwChan
	str	r8, [r0, #668]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag, <variable>.stSynExtraData.NextDispEnableFlag
	ldr	r2, [r9, r4, asl #2]	@ tmp297, s_pstVfmwChan
	ldr	r0, [r6, #764]	@, <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum
	str	lr, [r2, #672]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance, <variable>.stSynExtraData.NextDispFrameDistance
	ldr	ip, [r9, r4, asl #2]	@ tmp300, s_pstVfmwChan
	str	r1, [ip, #676]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame, <variable>.stSynExtraData.NextDistanceBeforeFirstFrame
	ldr	r1, [r9, r4, asl #2]	@ tmp303, s_pstVfmwChan
	str	r0, [r1, #684]	@, <variable>.stSynExtraData.NextGopNum
	b	.L1311	@
.L1335:
	mov	r0, r4	@, ChanID
	add	r1, r6, #696	@, temp.4168,
	bl	SM_ReadStreamSeg	@
	cmp	r0, #0	@,
	beq	.L1306	@,
	cmp	sl, #1	@ rec_pos_print_flag,
	beq	.L1342	@,
.L1307:
	ldr	r3, [r5, r4, asl #2]	@ tmp218, s_pstVfmwChan
	mov	lr, #1	@ tmp219,
	mvn	r0, #3	@ D.53510,
	str	lr, [r3, #332]	@ tmp219, <variable>.s32NoStreamFlag
	b	.L1291	@
.L1338:
	ldr	r1, [r0, #1480]	@ <variable>.stSynExtraData.s32IsHevcMain10, <variable>.stSynExtraData.s32IsHevcMain10
	cmp	r1, #1	@ <variable>.stSynExtraData.s32IsHevcMain10,
	beq	.L1320	@,
	add	r0, r0, #250880	@, temp.4222,
	add	r0, r0, #704	@,,
	bl	IsMain10Profile	@
	cmp	r0, #0	@ D.53653
	bne	.L1343	@,
	ldr	lr, [r6, r4, asl #2]	@ tmp387, s_pstVfmwChan
	str	r0, [lr, #1480]	@ D.53653, <variable>.stSynExtraData.s32IsHevcMain10
	b	.L1320	@
.L1334:
	movw	ip, #:lower16:249248	@ tmp205,
	movt	ip, #:upper16:249248	@ tmp205,
	ldr	r3, [r6, ip]	@ prephitmp.4151, <variable>.FspInst.eFspPartitionState
	cmp	r3, #0	@ prephitmp.4151,
	cmpne	r3, #2	@, prephitmp.4151,
	beq	.L1303	@,
	cmp	r3, #1	@ prephitmp.4151,
	bne	.L1323	@,
	movw	r1, #:lower16:.LC226	@,
	mov	r0, #31	@,
	movt	r1, #:upper16:.LC226	@,
	bl	dprint_vfmw	@
.L1327:
	mvn	r0, #2	@ D.53510,
	b	.L1291	@
.L1333:
	cmp	sl, #1	@ rec_pos_print_flag,
	bne	.L1327	@,
	mov	r2, r4	@, ChanID
	mov	r0, #23	@,
	movw	r1, #:lower16:.LC219	@,
	movt	r1, #:upper16:.LC219	@,
	bl	dprint_vfmw	@
	mvn	r0, #2	@ D.53510,
	b	.L1291	@
.L1343:
	mov	r3, r4	@, ChanID
	ldr	r2, .L1344	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC225	@,
	movt	r1, #:upper16:.LC225	@,
	bl	dprint_vfmw	@
	ldr	r3, [r6, r4, asl #2]	@ tmp384, s_pstVfmwChan
	mov	r2, #1	@ tmp385,
	str	r2, [r3, #1480]	@ tmp385, <variable>.stSynExtraData.s32IsHevcMain10
	bl	VDMDRV_AddMatchMode	@
	b	.L1320	@
.L1300:
	mov	r2, r4	@, ChanID
	mov	r0, #23	@,
	movw	r1, #:lower16:.LC218	@,
	movt	r1, #:upper16:.LC218	@,
	bl	dprint_vfmw	@
	mvn	r0, #1	@ D.53510,
	b	.L1291	@
.L1330:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7076	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC216	@,
	movt	r3, #:upper16:.LC216	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53510,
	b	.L1291	@
.L1331:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7077	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC217	@,
	movt	r3, #:upper16:.LC217	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53510,
	b	.L1291	@
.L1341:
	mov	r0, #616	@ tmp248,
	mov	r1, #608	@ tmp247,
	ldrd	r8, [r3, r0]	@, prephitmp.4145, tmp248
	strd	r8, [r3, r1]	@, prephitmp.4145, tmp247
	ldr	r3, [r2, r4, asl #2]	@ prephitmp.4145, s_pstVfmwChan
	b	.L1313	@
.L1337:
	mov	r3, r4, asl #24	@ tmp368, ChanID,
	ldr	r0, .L1344	@,
	add	r2, r3, #196608	@, tmp368,
	movw	r1, #7264	@,
	bl	DBG_AddTrace	@
	b	.L1319	@
.L1328:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7074	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53510,
	b	.L1291	@
.L1342:
	movw	r1, #:lower16:.LC220	@,
	mov	r2, r4	@, ChanID
	movt	r1, #:upper16:.LC220	@,
	mov	r0, #23	@,
	bl	dprint_vfmw	@
	b	.L1307	@
.L1329:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7075	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC215	@,
	movt	r3, #:upper16:.LC215	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53510,
	b	.L1291	@
.L1345:
	.align	2
.L1344:
	.word	.LANCHOR1+232
	.fnend
	.size	DecChanSyntax, .-DecChanSyntax
	.align	2
	.global	DecSyntax
	.type	DecSyntax, %function
DecSyntax:
	.fnstart
.LFB1611:
	@ args = 0, pretend = 0, frame = 32
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
	movw	r6, #:lower16:.LANCHOR0	@ tmp302,
	movt	r6, #:upper16:.LANCHOR0	@ tmp302,
	movw	r4, #:lower16:.LANCHOR3	@ tmp304,
	movt	r4, #:upper16:.LANCHOR3	@ tmp304,
	ldr	r9, [r6, #0]	@ temp.4277, s_pstVfmwChan
	ldr	r8, [r6, #4]	@ temp.4279, s_pstVfmwChan
	cmp	r9, #0	@ temp.4277,
	ldr	r7, [r6, #8]	@ D.53404, s_pstVfmwChan
	ldr	r2, [r6, #12]	@ temp.4281, s_pstVfmwChan
	ldrne	r9, [r9, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r8, #0	@ temp.4279,
	ldr	r1, [r6, #16]	@ temp.4283, s_pstVfmwChan
	ldr	r0, [r6, #20]	@ temp.4285, s_pstVfmwChan
	str	r9, [r4, #-1796]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r8, [r8, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r7, #0	@ D.53404,
	ldr	r3, [r6, #24]	@ temp.4287, s_pstVfmwChan
	ldr	ip, [r6, #28]	@ temp.4289, s_pstVfmwChan
	str	r8, [r4, #-1792]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r7, [r7, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r2, #0	@ temp.4281,
	ldr	sl, [r6, #32]	@ temp.4291, s_pstVfmwChan
	ldr	r9, [r6, #36]	@ temp.4293, s_pstVfmwChan
	str	r7, [r4, #-1788]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r2, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ temp.4283,
	ldr	r8, [r6, #40]	@ temp.4295, s_pstVfmwChan
	ldr	r7, [r6, #44]	@ temp.4297, s_pstVfmwChan
	str	r2, [r4, #-1784]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r0, #0	@ temp.4285,
	str	r1, [r4, #-1780]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r0, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r3, #0	@ temp.4287,
	str	r0, [r4, #-1776]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r3, [r3, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	ip, #0	@ temp.4289,
	str	r3, [r4, #-1772]	@ <variable>.s32Priority, ChanPriTab
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	sl, #0	@ temp.4291,
	str	ip, [r4, #-1768]	@ <variable>.s32Priority, ChanPriTab
	ldrne	sl, [sl, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r9, #0	@ temp.4293,
	str	sl, [r4, #-1764]	@ <variable>.s32Priority, ChanPriTab
	movw	sl, #:lower16:.LANCHOR0	@ tmp311,
	ldrne	r9, [r9, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r8, #0	@ temp.4295,
	movt	sl, #:upper16:.LANCHOR0	@ tmp311,
	str	r9, [r4, #-1760]	@ <variable>.s32Priority, ChanPriTab
	sub	r9, fp, #68	@ tmp312,,
	ldrne	r8, [r8, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r7, #0	@ temp.4297,
	str	r8, [r4, #-1756]	@ <variable>.s32Priority, ChanPriTab
	mvn	r8, #0	@ ret,
	ldrne	r7, [r7, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	str	r7, [r4, #-1752]	@ <variable>.s32Priority, ChanPriTab
	mov	r7, #0	@ MaxPriChan.4306,
	ldr	r2, [r6, #48]	@ temp.4299, s_pstVfmwChan
	ldr	r1, [r6, #52]	@ temp.4301, s_pstVfmwChan
	cmp	r2, #0	@ temp.4299,
	ldr	r0, [r6, #56]	@ temp.4303, s_pstVfmwChan
	ldr	r3, [r6, #60]	@ temp.4267, s_pstVfmwChan
	ldrne	r2, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ temp.4301,
	str	r2, [r4, #-1748]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r0, #0	@ temp.4303,
	str	r1, [r4, #-1744]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r0, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r3, #0	@ temp.4267,
	str	r0, [r4, #-1740]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r3, [r3, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	str	r3, [r4, #-1736]	@ temp.4267, ChanPriTab
.L1407:
	ldr	r3, [r4, #-1796]	@ MaxPri, ChanPriTab
	ldr	r2, [r4, #-1792]	@ MaxPri.4305, ChanPriTab
	ldr	r1, [r4, #-1788]	@ MaxPri.4307, ChanPriTab
	cmp	r3, r2	@ MaxPri, MaxPri.4305
	ldr	r0, [r4, #-1784]	@ MaxPri.4308, ChanPriTab
	ldr	ip, [r4, #-1780]	@ MaxPri.4309, ChanPriTab
	movlt	r3, r2	@ MaxPri, MaxPri.4305
	movlt	r5, #1	@ MaxPriChan.4306,
	movge	r5, #0	@ MaxPriChan.4306,
	cmp	r3, r1	@ MaxPri, MaxPri.4307
	ldr	r2, [r4, #-1776]	@ MaxPri.4310, ChanPriTab
	movlt	r3, r1	@ MaxPri, MaxPri.4307
	movlt	r5, #2	@ MaxPriChan.4306,
	cmp	r3, r0	@ MaxPri, MaxPri.4308
	ldr	r1, [r4, #-1772]	@ MaxPri.4311, ChanPriTab
	movlt	r3, r0	@ MaxPri, MaxPri.4308
	movlt	r5, #3	@ MaxPriChan.4306,
	cmp	r3, ip	@ MaxPri, MaxPri.4309
	ldr	r0, [r4, #-1768]	@ MaxPri.4312, ChanPriTab
	movlt	r3, ip	@ MaxPri, MaxPri.4309
	movlt	r5, #4	@ MaxPriChan.4306,
	cmp	r3, r2	@ MaxPri, MaxPri.4310
	ldr	ip, [r4, #-1764]	@ MaxPri.4313, ChanPriTab
	movlt	r3, r2	@ MaxPri, MaxPri.4310
	movlt	r5, #5	@ MaxPriChan.4306,
	cmp	r3, r1	@ MaxPri, MaxPri.4311
	ldr	r2, [r4, #-1760]	@ MaxPri.4314, ChanPriTab
	movlt	r3, r1	@ MaxPri, MaxPri.4311
	movlt	r5, #6	@ MaxPriChan.4306,
	cmp	r3, r0	@ MaxPri, MaxPri.4312
	ldr	r1, [r4, #-1756]	@ MaxPri.4315, ChanPriTab
	movlt	r3, r0	@ MaxPri, MaxPri.4312
	movlt	r5, #7	@ MaxPriChan.4306,
	cmp	r3, ip	@ MaxPri, MaxPri.4313
	ldr	r0, [r4, #-1752]	@ MaxPri.4316, ChanPriTab
	movlt	r3, ip	@ MaxPri, MaxPri.4313
	movlt	r5, #8	@ MaxPriChan.4306,
	cmp	r3, r2	@ MaxPri, MaxPri.4314
	ldr	ip, [r4, #-1748]	@ MaxPri.4317, ChanPriTab
	movlt	r3, r2	@ MaxPri, MaxPri.4314
	movlt	r5, #9	@ MaxPriChan.4306,
	cmp	r3, r1	@ MaxPri, MaxPri.4315
	ldr	r2, [r4, #-1744]	@ MaxPri.4318, ChanPriTab
	movlt	r3, r1	@ MaxPri, MaxPri.4315
	movlt	r5, #10	@ MaxPriChan.4306,
	cmp	r3, r0	@ MaxPri, MaxPri.4316
	ldr	r1, [r4, #-1740]	@ MaxPri.4319, ChanPriTab
	movlt	r3, r0	@ MaxPri, MaxPri.4316
	movlt	r5, #11	@ MaxPriChan.4306,
	cmp	r3, ip	@ MaxPri, MaxPri.4317
	ldr	r0, [r4, #-1736]	@ MaxPri.4320, ChanPriTab
	movlt	r3, ip	@ MaxPri, MaxPri.4317
	movlt	r5, #12	@ MaxPriChan.4306,
	cmp	r3, r2	@ MaxPri, MaxPri.4318
	movlt	r3, r2	@ MaxPri, MaxPri.4318
	movlt	r5, #13	@ MaxPriChan.4306,
	cmp	r3, r1	@ MaxPri, MaxPri.4319
	movlt	r5, #14	@ MaxPriChan.4306,
	movlt	r3, r1	@ MaxPri, MaxPri.4319
	cmp	r3, r0	@ MaxPri, MaxPri.4320
	movlt	r5, #15	@ MaxPriChan.4306,
	movlt	r3, r0	@ MaxPri, MaxPri.4320
	add	ip, r4, r5, asl #2	@, tmp278, tmp304, MaxPriChan.4306,
	cmp	r3, #0	@ MaxPri,
	add	r2, r5, #1	@ s_VfmwCTrl__s32ThisChanIDPlus1s_VfmwCTrl.4258, MaxPriChan.4306,
	str	r7, [ip, #-1796]	@ MaxPriChan.4306, ChanPriTab
	ble	.L1395	@,
	ldr	r3, [r6, r5, asl #2]	@ D.53415, s_pstVfmwChan
	cmp	r3, #0	@ D.53415,
	beq	.L1407	@,
	str	r2, [sl, #156]	@ s_VfmwCTrl__s32ThisChanIDPlus1s_VfmwCTrl.4258, s_VfmwCTrl.s32ThisChanIDPlus1
	ldr	ip, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	ip, #1	@ <variable>.s32IsRun,
	bne	.L1407	@,
	ldr	lr, [r3, #68]	@ <variable>.stChanCfg.s32ChanStrmOFThr, <variable>.stChanCfg.s32ChanStrmOFThr
	cmp	lr, #0	@ <variable>.stChanCfg.s32ChanStrmOFThr,
	ble	.L1397	@,
	ldr	r8, [r3, #72]	@ <variable>.stChanCfg.s32DecMode, <variable>.stChanCfg.s32DecMode
	cmp	r8, #0	@ <variable>.stChanCfg.s32DecMode,
	beq	.L1423	@,
.L1397:
	mov	r3, #0	@ i,
.L1402:
	mov	r0, r5	@, MaxPriChan.4306
	str	r3, [fp, #-72]	@,
	bl	DecChanSyntax	@
	ldr	r3, [fp, #-72]	@,
	cmn	r0, #1	@ ret,
	mov	r8, r0	@ ret,
	beq	.L1424	@,
	cmp	r0, #0	@ ret,
	bne	.L1407	@,
	add	r3, r3, #1	@ i, i,
	cmp	r3, #200	@ i,
	beq	.L1407	@,
	b	.L1402	@
.L1395:
	str	r7, [r6, #156]	@ MaxPriChan.4306, s_VfmwCTrl.s32ThisChanIDPlus1
.L1401:
	mov	r0, r8	@, ret
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1423:
	mov	r0, r5	@, MaxPriChan.4306
	mov	r1, r9	@, tmp312
	bl	SM_GetInfo	@
	cmp	r0, #0	@,
	beq	.L1398	@,
	mov	r0, r9	@, tmp312
	mov	r1, #24	@,
	bl	__memzero	@
.L1398:
	ldr	r8, [r6, r5, asl #2]	@ temp.4268, s_pstVfmwChan
	ldr	r1, [fp, #-56]	@, stScdInstInfo.TotalRawSize
	ldr	r0, [r8, #560]	@, <variable>.stSynExtraData.s32DecMode
	ldr	r2, [r8, #68]	@, <variable>.stChanCfg.s32ChanStrmOFThr
	bl	GetNextDecodeMode	@
	str	r0, [r8, #560]	@, <variable>.stSynExtraData.s32DecMode
	ldr	r3, [r6, r5, asl #2]	@ temp.4270, s_pstVfmwChan
	ldr	r0, [r3, #560]	@ <variable>.stSynExtraData.s32DecMode, <variable>.stSynExtraData.s32DecMode
	cmp	r0, #0	@ <variable>.stSynExtraData.s32DecMode,
	strne	r7, [r3, #556]	@ MaxPriChan.4306, <variable>.stSynExtraData.s32OutErrThr
	ldreq	r0, [r3, #64]	@ <variable>.stChanCfg.s32ChanErrThr, <variable>.stChanCfg.s32ChanErrThr
	ldrne	r3, [sl, r5, asl #2]	@ tmp293, s_pstVfmwChan
	streq	r0, [r3, #556]	@ <variable>.stChanCfg.s32ChanErrThr, <variable>.stSynExtraData.s32OutErrThr
	ldreq	r3, [sl, r5, asl #2]	@ temp.4273, s_pstVfmwChan
	strne	r7, [r3, #552]	@ MaxPriChan.4306, <variable>.stSynExtraData.s32RefErrThr
	ldreq	r0, [r3, #64]	@ <variable>.stChanCfg.s32ChanErrThr, <variable>.stChanCfg.s32ChanErrThr
	streq	r0, [r3, #552]	@ <variable>.stChanCfg.s32ChanErrThr, <variable>.stSynExtraData.s32RefErrThr
	b	.L1397	@
.L1424:
	ldr	ip, [r6, #64]	@ g_event_report.662, g_event_report
	cmp	ip, #0	@ g_event_report.662,
	beq	.L1401	@,
	mov	r2, #0	@,
	mov	r0, r5	@, MaxPriChan.4306
	mov	r1, #102	@,
	mov	r3, r2	@,
	blx	ip	@ g_event_report.662
	b	.L1401	@
	.fnend
	.size	DecSyntax, .-DecSyntax
	.align	2
	.global	VCTRL_IsChanDecable
	.type	VCTRL_IsChanDecable, %function
VCTRL_IsChanDecable:
	.fnstart
.LFB1596:
	@ args = 0, pretend = 0, frame = 24
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp149,
	movt	r4, #:upper16:.LANCHOR0	@ tmp149,
	mov	r5, r0	@ ChanID, ChanID
	ldr	r3, [r4, r0, asl #2]	@ tmp140, s_pstVfmwChan
	cmp	r3, #0	@ tmp140,
	beq	.L1428	@,
	sub	r1, fp, #44	@,,
	bl	SM_GetInfo	@
	cmp	r0, #0	@,
	bne	.L1428	@,
	ldr	r0, [fp, #-36]	@ SmInstInfo.SegNum, SmInstInfo.SegNum
	cmp	r0, #16	@ SmInstInfo.SegNum,
	bgt	.L1429	@,
	ldr	r1, [fp, #-28]	@ SmInstInfo.TotalSegSize, SmInstInfo.TotalSegSize
	cmp	r1, #524288	@ SmInstInfo.TotalSegSize,
	bgt	.L1429	@,
.L1428:
	mvn	r0, #0	@ ret,
.L1427:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1429:
	mov	r0, r5	@, ChanID
	bl	VCTRL_GetImageBuffer	@
	cmp	r0, #1	@,
	bne	.L1428	@,
	bl	OSAL_GetTimeInMs	@
	ldr	r3, [r4, r5, asl #2]	@ tmp146, s_pstVfmwChan
	ldr	ip, [r3, #44]	@ <variable>.u32timeLastDecParamReady, <variable>.u32timeLastDecParamReady
	rsb	r2, ip, r0	@ tmp147, <variable>.u32timeLastDecParamReady,
	cmp	r2, #50	@ tmp147,
	movls	r0, #0	@ ret,
	bls	.L1427	@,
	b	.L1428	@
	.fnend
	.size	VCTRL_IsChanDecable, .-VCTRL_IsChanDecable
	.align	2
	.global	VCTRL_FlushDecoder
	.type	VCTRL_FlushDecoder, %function
VCTRL_FlushDecoder:
	.fnstart
.LFB1592:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp184,
	movt	r4, #:upper16:.LANCHOR0	@ tmp184,
	mov	r5, r0	@ ChanID, ChanID
	ldr	r0, [r4, r0, asl #2]	@ D.52338, s_pstVfmwChan
	cmp	r0, #0	@ D.52338,
	beq	.L1451	@,
	movw	r1, #:lower16:251576	@ tmp143,
	movt	r1, #:upper16:251576	@ tmp143,
	ldr	r3, [r0, r1]	@ <variable>.stSynCtx.eVidStd, <variable>.stSynCtx.eVidStd
	cmp	r3, #16	@ <variable>.stSynCtx.eVidStd,
	ldrls	pc, [pc, r3, asl #2]	@ <variable>.stSynCtx.eVidStd
	b	.L1435	@
.L1448:
	.word	.L1436
	.word	.L1437
	.word	.L1438
	.word	.L1439
	.word	.L1435
	.word	.L1440
	.word	.L1441
	.word	.L1435
	.word	.L1442
	.word	.L1443
	.word	.L1444
	.word	.L1444
	.word	.L1444
	.word	.L1445
	.word	.L1435
	.word	.L1446
	.word	.L1447
.L1436:
	add	lr, r0, #250880	@, D.52338,
	add	r0, lr, #704	@,,
	bl	H264_FlushDecoder	@
	bl	VDMDRV_WakeUpVdm	@
	bl	VDMDRV_WakeUpVdm	@
	ldr	r3, [r4, r5, asl #2]	@ tmp154, s_pstVfmwChan
	add	ip, r3, #250880	@, tmp154,
	add	r0, ip, #704	@,,
	bl	FlushDPB	@
	cmp	r0, #0	@,
	bne	.L1452	@,
.L1435:
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1437:
	add	r2, r0, #250880	@, D.52338,
	add	r0, r2, #704	@,,
	bl	VC1DEC_GetRemainImg	@
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1438:
	add	r2, r0, #250880	@, D.52338,
	add	r0, r2, #704	@,,
	bl	MPEG4DEC_GetRemainImg	@
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1439:
	add	r0, r0, #250880	@, D.52338,
	add	r0, r0, #704	@,,
	bl	MPEG2DEC_GetRemainImg	@
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1440:
	add	r1, r0, #250880	@, D.52338,
	add	r0, r1, #704	@,,
	bl	DIVX3DEC_GetRemainImg	@
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1441:
	add	r3, r0, #250880	@, D.52338,
	add	r0, r3, #704	@,,
	bl	AVSDEC_GetRemainImg	@
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1442:
	add	lr, r0, #250880	@, D.52338,
	add	r0, lr, #704	@,,
	bl	REAL8DEC_GetRemainImg	@
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1443:
	add	r0, r0, #250880	@, D.52338,
	add	r0, r0, #704	@,,
	bl	REAL9DEC_GetRemainImg	@
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1444:
	add	ip, r0, #250880	@, D.52338,
	add	r0, ip, #704	@,,
	bl	VP6DEC_GetRemainImg	@
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1445:
	add	r3, r0, #250880	@, D.52338,
	add	r0, r3, #704	@,,
	bl	VP8DEC_GetRemainImg	@
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1446:
	add	ip, r0, #250880	@, D.52338,
	add	r0, ip, #704	@,,
	bl	MVC_FlushDecoder	@
	bl	VDMDRV_WakeUpVdm	@
	bl	VDMDRV_WakeUpVdm	@
	ldr	r2, [r4, r5, asl #2]	@ tmp165, s_pstVfmwChan
	mvn	r1, #0	@,
	add	r0, r2, #250880	@, tmp165,
	add	r0, r0, #704	@,,
	bl	MVC_FlushDPB	@
	cmp	r0, #0	@,
	beq	.L1435	@,
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC230	@,
	ldr	r2, .L1454	@,
	movt	r1, #:upper16:.LC230	@,
	movw	r3, #4861	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1447:
	add	r1, r0, #250880	@, D.52338,
	add	r0, r1, #704	@,,
	bl	HEVC_FlushOutputFrmFromDPB	@
	cmp	r0, #0	@,
	bne	.L1453	@,
.L1449:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC229	@,
	movt	r1, #:upper16:.LC229	@,
	bl	dprint_vfmw	@
	bl	VDMDRV_WakeUpVdm	@
	bl	VDMDRV_WakeUpVdm	@
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1453:
	movw	r1, #:lower16:.LC228	@,
	movw	r2, #4847	@,
	movt	r1, #:upper16:.LC228	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	b	.L1449	@
.L1452:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC228	@,
	movw	r2, #4839	@,
	movt	r1, #:upper16:.LC228	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1451:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4818	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52342,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1455:
	.align	2
.L1454:
	.word	.LANCHOR1+248
	.fnend
	.size	VCTRL_FlushDecoder, .-VCTRL_FlushDecoder
	.align	2
	.global	VCTRL_PostProc
	.type	VCTRL_PostProc, %function
VCTRL_PostProc:
	.fnstart
.LFB1590:
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #12
	sub	sp, sp, #12	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r4, #:lower16:.LANCHOR0	@ tmp274,
	movt	r4, #:upper16:.LANCHOR0	@ tmp274,
	mov	r5, r0	@ ChanId, ChanId
	ldr	ip, [fp, #4]	@ VdhId, VdhId
	ldr	r0, [r4, r0, asl #2]	@ D.52252, s_pstVfmwChan
	cmp	r0, #0	@ D.52252,
	beq	.L1490	@,
	ldr	r7, [r0, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	r6, [r0, #1256]	@ ModuleLowlyEnable, <variable>.stSynExtraData.s32ModuleLowlyEnable
	cmp	r7, #16	@ <variable>.eVidStd,
	ldrls	pc, [pc, r7, asl #2]	@ <variable>.eVidStd
	b	.L1479	@
.L1471:
	.word	.L1459
	.word	.L1460
	.word	.L1461
	.word	.L1462
	.word	.L1479
	.word	.L1463
	.word	.L1464
	.word	.L1479
	.word	.L1465
	.word	.L1466
	.word	.L1467
	.word	.L1467
	.word	.L1467
	.word	.L1468
	.word	.L1479
	.word	.L1469
	.word	.L1470
.L1459:
	add	r2, r0, #250880	@, D.52252,
	str	ip, [sp, #4]	@ VdhId,
	add	r0, r2, #704	@,,
	mov	r2, #1	@,
	str	r6, [sp, #0]	@ ModuleLowlyEnable,
	bl	H264DEC_VDMPostProc	@
	ldr	r0, [r4, r5, asl #2]	@ tmp152, s_pstVfmwChan
	movw	r7, #:lower16:265144	@ tmp153,
	movt	r7, #:upper16:265144	@ tmp153,
	movw	r8, #:lower16:.LANCHOR0	@ tmp151,
	movt	r8, #:upper16:.LANCHOR0	@ tmp151,
	ldrb	r3, [r0, r7]	@ zero_extendqisi2	@ <variable>.stSynCtx.unSyntax.stH264Ctx.IsStreamEndFlag, <variable>.stSynCtx.unSyntax.stH264Ctx.IsStreamEndFlag
	cmp	r3, #1	@ <variable>.stSynCtx.unSyntax.stH264Ctx.IsStreamEndFlag,
	beq	.L1491	@,
.L1472:
	cmp	r6, #1	@ ModuleLowlyEnable,
	beq	.L1479	@,
	ldr	r0, [r4, r5, asl #2]	@ tmp161, s_pstVfmwChan
	movw	r3, #:lower16:251944	@ tmp162,
	movt	r3, #:upper16:251944	@ tmp162,
	mov	lr, #0	@ tmp163,
	str	lr, [r0, r3]	@ tmp163,
.L1479:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1470:
	add	r7, r0, #250880	@, D.52252,
	mov	r2, #1	@,
	add	r0, r7, #704	@,,
	stmia	sp, {r6, ip}	@ phole stm
	bl	HEVCDEC_VDMPostProc	@
	ldr	r1, [r4, r5, asl #2]	@ tmp167, s_pstVfmwChan
	movw	r7, #:lower16:251590	@ tmp168,
	movt	r7, #:upper16:251590	@ tmp168,
	movw	r8, #:lower16:.LANCHOR0	@ tmp166,
	movt	r8, #:upper16:.LANCHOR0	@ tmp166,
	ldrb	r2, [r1, r7]	@ zero_extendqisi2	@ <variable>.stSynCtx.unSyntax.stHevcCtx.IsStreamEndFlag, <variable>.stSynCtx.unSyntax.stHevcCtx.IsStreamEndFlag
	cmp	r2, #1	@ <variable>.stSynCtx.unSyntax.stHevcCtx.IsStreamEndFlag,
	beq	.L1492	@,
.L1473:
	cmp	r6, #1	@ ModuleLowlyEnable,
	beq	.L1479	@,
	ldr	r2, [r4, r5, asl #2]	@ tmp176, s_pstVfmwChan
	movw	r3, #:lower16:2211776	@ tmp177,
	movt	r3, #:upper16:2211776	@ tmp177,
	mov	lr, #0	@ tmp178,
	str	lr, [r2, r3]	@ tmp178,
	b	.L1479	@
.L1460:
	add	r2, r0, #250880	@, D.52252,
	movw	r6, #:lower16:329839	@ tmp239,
	add	r0, r2, #704	@,,
	movt	r6, #:upper16:329839	@ tmp239,
	bl	VC1DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ prephitmp.4438, s_pstVfmwChan
.L1489:
	ldrb	lr, [r2, r6]	@ zero_extendqisi2	@ <variable>.stSynCtx.unSyntax.stVc1Ctx.CodecInfo.IsStreamEndFlag,
	movw	r4, #:lower16:.LANCHOR0	@ tmp238,
	movt	r4, #:upper16:.LANCHOR0	@ tmp238,
	cmp	lr, #1	@ <variable>.stSynCtx.unSyntax.stVc1Ctx.CodecInfo.IsStreamEndFlag,
	beq	.L1493	@,
.L1483:
	movw	r0, #:lower16:251588	@ tmp234,
	movt	r0, #:upper16:251588	@ tmp234,
	mov	r1, #0	@ tmp235,
	str	r1, [r2, r0]	@ tmp235,
	b	.L1479	@
.L1461:
	add	ip, r0, #250880	@, D.52252,
	mov	r2, r3	@, pLumaInfo
	add	r0, ip, #704	@,,
	movw	r6, #:lower16:.LANCHOR0	@ tmp194,
	bl	MPEG4DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ prephitmp.4432, s_pstVfmwChan
	movw	r4, #:lower16:308392	@ tmp195,
	movt	r4, #:upper16:308392	@ tmp195,
	movt	r6, #:upper16:.LANCHOR0	@ tmp194,
	ldrb	r1, [r2, r4]	@ zero_extendqisi2	@ <variable>.stSynCtx.unSyntax.stMpeg4Ctx.IsStreamEndFlag, <variable>.stSynCtx.unSyntax.stMpeg4Ctx.IsStreamEndFlag
	cmp	r1, #1	@ <variable>.stSynCtx.unSyntax.stMpeg4Ctx.IsStreamEndFlag,
	beq	.L1494	@,
.L1475:
	movw	r3, #:lower16:252620	@ tmp203,
	movt	r3, #:upper16:252620	@ tmp203,
	mov	lr, #0	@ tmp204,
	str	lr, [r2, r3]	@ tmp204,
	b	.L1479	@
.L1462:
	add	r6, r0, #250880	@, D.52252,
	add	r0, r6, #704	@,,
	movw	r6, #:lower16:366274	@ tmp182,
	bl	MPEG2DEC_VDMPostProc	@
	movt	r6, #:upper16:366274	@ tmp182,
	ldr	r2, [r4, r5, asl #2]	@ prephitmp.4429, s_pstVfmwChan
	b	.L1489	@
.L1463:
	add	ip, r0, #250880	@, D.52252,
	add	r0, ip, #704	@,,
	bl	DIVX3DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ tmp233, s_pstVfmwChan
	b	.L1483	@
.L1464:
	add	r6, r0, #250880	@, D.52252,
	add	r0, r6, #704	@,,
	movw	r6, #:lower16:268708	@ tmp208,
	bl	AVSDEC_VDMPostProc	@
	movt	r6, #:upper16:268708	@ tmp208,
	ldr	r2, [r4, r5, asl #2]	@ prephitmp.4435, s_pstVfmwChan
	b	.L1489	@
.L1465:
	add	lr, r0, #250880	@, D.52252,
	add	r0, lr, #704	@,,
	bl	REAL8DEC_VDMPostProc	@
	ldr	ip, [r4, r5, asl #2]	@ tmp221, s_pstVfmwChan
	movw	r0, #:lower16:251588	@ tmp222,
	movt	r0, #:upper16:251588	@ tmp222,
	mov	r1, #0	@ tmp223,
	str	r1, [ip, r0]	@ tmp223,
	b	.L1479	@
.L1466:
	add	r3, r0, #250880	@, D.52252,
	add	r0, r3, #704	@,,
	bl	REAL9DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ tmp233, s_pstVfmwChan
	b	.L1483	@
.L1467:
	add	r0, r0, #250880	@, D.52252,
	add	r0, r0, #704	@,,
	bl	VP6DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ tmp233, s_pstVfmwChan
	b	.L1483	@
.L1468:
	add	r2, r0, #250880	@, D.52252,
	add	r0, r2, #704	@,,
	bl	VP8DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ tmp233, s_pstVfmwChan
	b	.L1483	@
.L1469:
	add	r6, r0, #250880	@, D.52252,
	mov	r2, #1	@,
	add	r0, r6, #704	@,,
	movw	r6, #:lower16:.LANCHOR0	@ tmp263,
	bl	MVC_DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ prephitmp.4399, s_pstVfmwChan
	movw	r4, #:lower16:251585	@ tmp264,
	movt	r4, #:upper16:251585	@ tmp264,
	movt	r6, #:upper16:.LANCHOR0	@ tmp263,
	ldrb	r1, [r2, r4]	@ zero_extendqisi2	@ <variable>.stSynCtx.unSyntax.stMvcCtx.IsStreamEndFlag, <variable>.stSynCtx.unSyntax.stMvcCtx.IsStreamEndFlag
	cmp	r1, #1	@ <variable>.stSynCtx.unSyntax.stMvcCtx.IsStreamEndFlag,
	beq	.L1495	@,
.L1478:
	movw	r0, #:lower16:251812	@ tmp272,
	movt	r0, #:upper16:251812	@ tmp272,
	mov	lr, #0	@ tmp273,
	str	lr, [r2, r0]	@ tmp273,
	b	.L1479	@
.L1490:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4655	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	b	.L1479	@
.L1493:
	mov	r0, r5	@, ChanId
	bl	VCTRL_OutputLastFrame	@
	ldr	r3, [r4, r5, asl #2]	@ tmp242, s_pstVfmwChan
	mov	ip, #0	@ tmp244,
	strb	ip, [r3, r6]	@ tmp244,
	ldr	r2, [r4, r5, asl #2]	@ prephitmp.4438, s_pstVfmwChan
	b	.L1483	@
.L1494:
	mov	r0, r5	@, ChanId
	bl	VCTRL_OutputLastFrame	@
	ldr	r2, [r6, r5, asl #2]	@ tmp198, s_pstVfmwChan
	mov	r0, #0	@ tmp200,
	strb	r0, [r2, r4]	@ tmp200, <variable>.stSynCtx.unSyntax.stMpeg4Ctx.IsStreamEndFlag
	ldr	r2, [r6, r5, asl #2]	@ prephitmp.4432, s_pstVfmwChan
	b	.L1475	@
.L1495:
	mov	r0, r5	@, ChanId
	bl	VCTRL_OutputLastFrame	@
	ldr	r3, [r6, r5, asl #2]	@ tmp267, s_pstVfmwChan
	mov	ip, #0	@ tmp269,
	strb	ip, [r3, r4]	@ tmp269, <variable>.stSynCtx.unSyntax.stMvcCtx.IsStreamEndFlag
	ldr	r2, [r6, r5, asl #2]	@ prephitmp.4399, s_pstVfmwChan
	b	.L1478	@
.L1491:
	mov	r0, r5	@, ChanId
	bl	VCTRL_OutputLastFrame	@
	ldr	ip, [r8, r5, asl #2]	@ tmp156, s_pstVfmwChan
	mov	r1, #0	@ tmp158,
	strb	r1, [ip, r7]	@ tmp158, <variable>.stSynCtx.unSyntax.stH264Ctx.IsStreamEndFlag
	b	.L1472	@
.L1492:
	mov	r0, r5	@, ChanId
	bl	VCTRL_OutputLastFrame	@
	ldr	r0, [r8, r5, asl #2]	@ tmp171, s_pstVfmwChan
	mov	ip, #0	@ tmp173,
	strb	ip, [r0, r7]	@ tmp173, <variable>.stSynCtx.unSyntax.stHevcCtx.IsStreamEndFlag
	b	.L1473	@
	.fnend
	.size	VCTRL_PostProc, .-VCTRL_PostProc
	.align	2
	.global	VCTRL_VdmPostProc
	.type	VCTRL_VdmPostProc, %function
VCTRL_VdmPostProc:
	.fnstart
.LFB1591:
	@ args = 4, pretend = 0, frame = 0
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
	cmp	r0, #15	@ ChanId,
	mov	r4, r0	@ ChanId, ChanId
	mov	r7, r1	@ ErrRatio, ErrRatio
	mov	r6, r2	@ Mb0QpInCurrPic, Mb0QpInCurrPic
	mov	r5, r3	@ pLumaInfo, pLumaInfo
	bhi	.L1502	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp142,
	movt	r3, #:upper16:.LANCHOR0	@ tmp142,
	ldr	r3, [r3, r0, asl #2]	@ D.52308, s_pstVfmwChan
	cmp	r3, #0	@ D.52308,
	beq	.L1503	@,
	ldr	r1, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r1, #1	@ <variable>.s32IsRun,
	beq	.L1500	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC216	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r2, #4804	@,
	movt	r3, #:upper16:.LC216	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
.L1501:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1500:
	bl	VCTRL_GetDecParam	@
	cmp	r0, #0	@,
	beq	.L1501	@,
	ldr	ip, [fp, #4]	@ VdhId, VdhId
	mov	r0, r4	@, ChanId
	mov	r1, r7	@, ErrRatio
	mov	r2, r6	@, Mb0QpInCurrPic
	mov	r3, r5	@, pLumaInfo
	str	ip, [sp, #0]	@ VdhId,
	bl	VCTRL_PostProc	@
	b	.L1501	@
.L1502:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4802	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC28	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC28	@,
	bl	dprint_vfmw	@
	b	.L1501	@
.L1503:
	mov	r0, r3	@, D.52308
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4803	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC215	@,
	movt	r3, #:upper16:.LC215	@,
	bl	dprint_vfmw	@
	b	.L1501	@
	.fnend
	.size	VCTRL_VdmPostProc, .-VCTRL_VdmPostProc
	.align	2
	.global	VCTRL_ExtAccPostProcess
	.type	VCTRL_ExtAccPostProcess, %function
VCTRL_ExtAccPostProcess:
	.fnstart
.LFB1621:
	@ args = 0, pretend = 0, frame = 136
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #148
	sub	sp, sp, #148	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	ldr	r4, .L1506	@ tmp138,
	sub	r7, fp, #172	@ tmp136,,
	ldr	r5, .L1506+4	@ tmp140,
	mov	r6, r0	@ ChanID, ChanID
	mov	r8, r1	@ ErrorRatio, ErrorRatio
	mov	r0, r7	@, tmp136
	mov	r1, #136	@,
	bl	__memzero	@
	mov	r0, r4	@, tmp138
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r5	@, tmp140
	bl	OSAL_SpinLockIRQ	@
	mov	ip, #0	@ tmp143,
	mov	r1, r8	@, ErrorRatio
	mov	r2, ip	@, tmp143
	mov	r3, r7	@, tmp136
	mov	r0, r6	@, ChanID
	str	ip, [sp, #0]	@ tmp143,
	bl	VCTRL_VdmPostProc	@
	mov	r0, r6	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	mov	r0, r5	@, tmp140
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r4	@, tmp138
	bl	OSAL_SpinUnLockIRQ	@
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1507:
	.align	2
.L1506:
	.word	.LANCHOR0+520
	.word	.LANCHOR3-1732
	.fnend
	.size	VCTRL_ExtAccPostProcess, .-VCTRL_ExtAccPostProcess
	.align	2
	.global	VCTRL_ReleaseChanImage
	.type	VCTRL_ReleaseChanImage, %function
VCTRL_ReleaseChanImage:
	.fnstart
.LFB1585:
	@ args = 0, pretend = 0, frame = 504
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #504
	sub	sp, sp, #504	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ ChanID,
	mov	r4, r0	@ ChanID, ChanID
	mov	r6, r1	@ pImage, pImage
	bhi	.L1522	@,
	movw	r5, #:lower16:.LANCHOR0	@ tmp145,
	movt	r5, #:upper16:.LANCHOR0	@ tmp145,
	ldr	r0, [r5, r0, asl #2]	@ D.52053, s_pstVfmwChan
	cmp	r0, #0	@ D.52053,
	beq	.L1523	@,
	ldr	r3, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r3, #1	@ <variable>.s32IsOpen,
	bne	.L1524	@,
	cmp	r1, #0	@ pImage,
	beq	.L1525	@,
	mov	r2, r4	@, ChanID
	ldr	r3, [r1, #196]	@, <variable>.image_id
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC232	@,
	movt	r1, #:upper16:.LC232	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, [r5, r4, asl #2]	@ temp.4517, s_pstVfmwChan
	cmp	r0, #0	@ temp.4517,
	movweq	r1, #:lower16:.LC233	@,
	movweq	r2, #4361	@,
	movteq	r1, #:upper16:.LC233	@,
	beq	.L1521	@,
	ldr	r1, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r1, #1	@ <variable>.s32IsOpen,
	bne	.L1526	@,
	add	r0, r0, #250880	@, temp.4517,
	mov	r1, r6	@, pImage
	add	r0, r0, #696	@,,
	bl	SYNTAX_ReleaseImage	@
	ldr	r3, [r6, #252]	@ D.52071, <variable>.image_id_1
	cmn	r3, #1	@ D.52071,
	mov	r7, r0	@ ret,
	beq	.L1516	@,
	ldr	r7, [r5, r4, asl #2]	@ tmp167, s_pstVfmwChan
	sub	r1, fp, #532	@,,
	str	r3, [fp, #-336]	@ D.52071, Image_1.image_id
	add	r2, r7, #250880	@, tmp167,
	add	r0, r2, #696	@,,
	bl	SYNTAX_ReleaseImage	@
	mov	r7, r0	@ ret,
.L1516:
	mov	r0, #13	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	bne	.L1527	@,
.L1517:
	cmp	r7, #1	@ ret,
	beq	.L1528	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC235	@,
	ldr	r2, .L1529	@,
	movt	r1, #:upper16:.LC235	@,
	bl	dprint_vfmw	@
	mvn	r4, #0	@ ret.4513,
.L1519:
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinUnLockIRQ	@
.L1510:
	mov	r0, r4	@, ret.4513
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1527:
	bl	OSAL_GetTimeInMs	@
	movw	r3, #:lower16:.LANCHOR3	@ tmp170,
	movt	r3, #:upper16:.LANCHOR3	@ tmp170,
	movw	r2, #:lower16:g_TraceImgPeriod	@ tmp177,
	add	r3, r3, r4, asl #2	@, tmp173, tmp170, ChanID,
	movt	r2, #:upper16:g_TraceImgPeriod	@ tmp177,
	ldr	r1, [r3, #-1720]	@ tmp176, last_rec_pos_time
	mov	ip, r0	@ currtime,
	ldr	r0, [r2, #0]	@ g_TraceImgPeriod, g_TraceImgPeriod
	rsb	r1, r1, ip	@ tmp175, tmp176, currtime
	cmp	r1, r0	@ tmp175, g_TraceImgPeriod
	bls	.L1517	@,
	mov	r4, r4, asl #24	@ tmp186, ChanID,
	ldr	r0, .L1529	@,
	add	r2, r4, #851968	@ tmp187, tmp186,
	movw	r1, #4398	@,
	cmp	r7, #1	@ ret,
	addeq	r2, r2, #1	@,,, tmp187
	str	ip, [r3, #-1720]	@ currtime, last_rec_pos_time
	bl	DBG_AddTrace	@
	b	.L1517	@
.L1528:
	mov	r4, #0	@ ret.4513,
	b	.L1519	@
.L1526:
	movw	r1, #:lower16:.LC234	@,
	movt	r1, #:upper16:.LC234	@,
	movw	r2, #4367	@,
	mov	r0, #0	@,
.L1521:
	bl	dprint_vfmw	@
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	mvn	r4, #0	@ ret.4513,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L1510	@
.L1524:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4353	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC215	@,
	movt	r3, #:upper16:.LC215	@,
	bl	dprint_vfmw	@
	mvn	r4, #0	@ ret.4513,
	b	.L1510	@
.L1522:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4351	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r4, #0	@ ret.4513,
	b	.L1510	@
.L1525:
	mov	r0, r1	@, pImage
	movw	r2, #4354	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC231	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC231	@,
	bl	dprint_vfmw	@
	mvn	r4, #0	@ ret.4513,
	b	.L1510	@
.L1523:
	movw	r1, #:lower16:.LC5	@,
	mov	r2, #4352	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	mvn	r4, #0	@ ret.4513,
	bl	dprint_vfmw	@
	b	.L1510	@
.L1530:
	.align	2
.L1529:
	.word	.LANCHOR1+268
	.fnend
	.size	VCTRL_ReleaseChanImage, .-VCTRL_ReleaseChanImage
	.align	2
	.global	VCTRL_GetChanImage
	.type	VCTRL_GetChanImage, %function
VCTRL_GetChanImage:
	.fnstart
.LFB1584:
	@ args = 0, pretend = 0, frame = 512
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #548
	sub	sp, sp, #548	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r5, r0	@ ChanID, ChanID
	mov	r4, r1	@ pImage, pImage
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC236	@,
	mov	r2, r5	@, ChanID
	movt	r1, #:upper16:.LC236	@,
	bl	dprint_vfmw	@
	cmp	r5, #15	@ ChanID,
	bhi	.L1555	@,
	movw	r6, #:lower16:.LANCHOR0	@ tmp327,
	movt	r6, #:upper16:.LANCHOR0	@ tmp327,
	ldr	r0, [r6, r5, asl #2]	@ D.51930, s_pstVfmwChan
	cmp	r0, #0	@ D.51930,
	beq	.L1556	@,
	ldr	r3, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r3, #1	@ <variable>.s32IsOpen,
	bne	.L1557	@,
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, [r6, r5, asl #2]	@ temp.4560, s_pstVfmwChan
	cmp	r0, #0	@ temp.4560,
	movweq	r1, #:lower16:.LC233	@,
	movweq	r2, #4145	@,
	movteq	r1, #:upper16:.LC233	@,
	beq	.L1554	@,
	ldr	r1, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r1, #1	@ <variable>.s32IsOpen,
	bne	.L1558	@,
	add	r0, r0, #250880	@, temp.4560,
	mov	r1, r4	@, pImage
	add	r0, r0, #696	@,,
	bl	SYNTAX_ReceiveImage	@
	cmp	r0, #1	@ ret,
	movne	r3, #0	@, D.51944
	moveq	r3, #1	@, D.51944
	mov	r7, r0	@ ret,
	cmp	r4, #0	@ pImage,
	moveq	r2, #0	@, tmp170
	andne	r2, r3, #1	@,, tmp170, D.51944
	cmp	r2, #0	@ tmp170,
	bne	.L1559	@,
	cmp	r3, #0	@ D.51944,
	bne	.L1539	@,
.L1541:
	mov	r0, #12	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	bne	.L1560	@,
.L1549:
	cmp	r7, #1	@ ret,
	mvnne	r7, #0	@ ret,
	beq	.L1561	@,
.L1551:
	ldr	ip, [r6, r5, asl #2]	@ tmp319, s_pstVfmwChan
	movw	lr, #:lower16:267668	@ tmp320,
	movt	lr, #:upper16:267668	@ tmp320,
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	ldrb	r3, [ip, lr]	@ zero_extendqisi2	@ <variable>.stSynCtx.unSyntax.stAvsCtx.SyntaxNew.bAvsPlus, <variable>.stSynCtx.unSyntax.stAvsCtx.SyntaxNew.bAvsPlus
	strb	r3, [r4, #480]	@ <variable>.stSynCtx.unSyntax.stAvsCtx.SyntaxNew.bAvsPlus, <variable>.optm_inf.bAvsPlus
	bl	OSAL_SpinUnLockIRQ	@
.L1533:
	mov	r0, r7	@, ret
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1559:
	movw	r3, #:lower16:.LANCHOR3	@ tmp171,
	movt	r3, #:upper16:.LANCHOR3	@ tmp171,
	add	r8, r3, r5, asl #2	@, tmp174, tmp171, ChanID,
	ldr	r0, [r8, #-1656]	@ D.51949, vfmw_save_yuv_file
	cmp	r0, #0	@ D.51949,
	beq	.L1539	@,
	ldr	r7, [r4, #160]	@ <variable>.format, <variable>.format
	ldr	lr, [r3, #-1528]	@ save_yuv_with_crop, save_yuv_with_crop
	tst	r7, #28	@ <variable>.format,
	movne	ip, #0	@, tmp179
	moveq	ip, #1	@, tmp179
	cmp	lr, #0	@ save_yuv_with_crop,
	beq	.L1540	@,
	ldr	lr, [r4, #352]	@, <variable>.bottom_offset
	ldr	r9, [r4, #348]	@ <variable>.top_offset, <variable>.top_offset
	ldr	r1, [r4, #32]	@ <variable>.luma_vir_addr, <variable>.luma_vir_addr
	ldr	r2, [r4, #36]	@ <variable>.chrom_vir_addr, <variable>.chrom_vir_addr
	ldr	r3, [r4, #164]	@ <variable>.image_width, <variable>.image_width
	ldr	r7, [r4, #192]	@ <variable>.image_stride, <variable>.image_stride
	ldr	r8, [r4, #340]	@ <variable>.left_offset, <variable>.left_offset
	ldr	sl, [r4, #344]	@ <variable>.right_offset, <variable>.right_offset
	str	lr, [fp, #-552]	@, %sfp
	ldr	lr, [r4, #168]	@, <variable>.image_height
	str	r9, [sp, #24]	@ <variable>.top_offset,
	ldr	r9, [fp, #-552]	@, %sfp
	str	lr, [sp, #0]	@,
	mov	lr, #0	@ tmp186,
	str	r7, [sp, #8]	@ <variable>.image_stride,
	str	lr, [sp, #4]	@ tmp186,
	str	ip, [sp, #12]	@ tmp179,
	str	r8, [sp, #16]	@ <variable>.left_offset,
	str	sl, [sp, #20]	@ <variable>.right_offset,
	str	r9, [sp, #28]	@,
	bl	DBG_WriteBigTileYuv	@
.L1539:
	ldr	ip, [r4, #256]	@ <variable>.is_3D, <variable>.is_3D
	mvn	r8, #0	@ tmp202,
	str	r8, [r4, #252]	@ tmp202, <variable>.image_id_1
	cmp	ip, #1	@ <variable>.is_3D,
	movne	r7, #1	@ ret,
	bne	.L1541	@,
.L1563:
	ldr	sl, [r4, #244]	@ <variable>.last_frame, <variable>.last_frame
	cmp	sl, #0	@ <variable>.last_frame,
	beq	.L1562	@,
	add	sl, r4, #420	@ tmp285, pImage,
	ldr	r9, [r4, #92]	@, <variable>.top_chrom_phy_addr
	add	lr, r4, #280	@ tmp284, pImage,
	mov	r7, ip	@ ret, <variable>.is_3D
	ldmia	sl!, {r0, r1, r2, r3}	@ tmp287,,,,
	str	r9, [r4, #264]	@, <variable>.top_chrom_phy_addr_1
	ldr	r9, [r4, #88]	@, <variable>.top_luma_phy_addr
	str	r9, [r4, #260]	@, <variable>.top_luma_phy_addr_1
	mov	r9, lr	@ tmp286, tmp284
	mov	lr, sl	@ tmp341, tmp287
	stmia	r9!, {r0, r1, r2, r3}	@ tmp286,,,,
	mov	sl, r9	@ tmp342, tmp286
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp341,,,,
	stmia	sl!, {r0, r1, r2, r3}	@ tmp342,,,,
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp343,,,,
	stmia	sl!, {r0, r1, r2, r3}	@ tmp342,,,,
	ldmia	lr, {r0, r1, r2}	@ tmp343,,,
	stmia	sl, {r0, r1, r2}	@ tmp344,,,
	mov	r1, #3	@ tmp289,
	str	r8, [r4, #252]	@ tmp202, <variable>.image_id_1
	str	r1, [r4, #364]	@ tmp289, <variable>.eFramePackingType
	str	ip, [r4, #244]	@ <variable>.is_3D, <variable>.last_frame
	b	.L1541	@
.L1560:
	bl	OSAL_GetTimeInMs	@
	movw	r3, #:lower16:.LANCHOR3	@ tmp291,
	movt	r3, #:upper16:.LANCHOR3	@ tmp291,
	add	r3, r3, r5, asl #2	@, tmp294, tmp291, ChanID,
	ldr	r1, [r3, #-1524]	@ tmp297, last_rec_pos_time
	mov	ip, r0	@ currtime,
	movw	r0, #:lower16:g_TraceImgPeriod	@ tmp298,
	movt	r0, #:upper16:g_TraceImgPeriod	@ tmp298,
	ldr	r2, [r0, #0]	@ g_TraceImgPeriod, g_TraceImgPeriod
	rsb	r0, r1, ip	@ tmp296, tmp297, currtime
	cmp	r0, r2	@ tmp296, g_TraceImgPeriod
	bls	.L1549	@,
	mov	lr, r5, asl #24	@ tmp307, ChanID,
	ldr	r0, .L1568	@,
	add	r2, lr, #786432	@ tmp308, tmp307,
	movw	r1, #4311	@,
	cmp	r7, #1	@ ret,
	addeq	r2, r2, #1	@,,, tmp308
	str	ip, [r3, #-1524]	@ currtime, last_rec_pos_time
	bl	DBG_AddTrace	@
	b	.L1549	@
.L1561:
	mov	r2, #0	@,
	mov	r0, r5	@, ChanID
	mov	r1, #12	@,
	mov	r7, r2	@ ret,
	bl	DBG_CountTimeInfo	@
	ldr	r0, [r6, r5, asl #2]	@ tmp313, s_pstVfmwChan
	ldr	r1, [r4, #160]	@ <variable>.format, <variable>.format
	str	r1, [r0, #324]	@ <variable>.format, <variable>.stRecentImgformat
	ldr	r2, [r6, r5, asl #2]	@ tmp316, s_pstVfmwChan
	ldr	ip, [r4, #364]	@ <variable>.eFramePackingType, <variable>.eFramePackingType
	str	ip, [r2, #328]	@ <variable>.eFramePackingType, <variable>.stRecentImgPackingType
	b	.L1551	@
.L1540:
	ldr	r7, [r4, #168]	@ <variable>.image_height, <variable>.image_height
	ldr	r8, [r4, #192]	@ <variable>.image_stride, <variable>.image_stride
	ldr	r1, [r4, #32]	@ <variable>.luma_vir_addr, <variable>.luma_vir_addr
	ldr	r2, [r4, #36]	@ <variable>.chrom_vir_addr, <variable>.chrom_vir_addr
	ldr	r3, [r4, #164]	@ <variable>.image_width, <variable>.image_width
	str	ip, [sp, #12]	@ tmp179,
	str	r7, [sp, #0]	@ <variable>.image_height,
	str	r8, [sp, #8]	@ <variable>.image_stride,
	mvn	r8, #0	@ tmp202,
	str	lr, [sp, #28]	@ save_yuv_with_crop,
	str	lr, [sp, #4]	@ save_yuv_with_crop,
	str	lr, [sp, #16]	@ save_yuv_with_crop,
	str	lr, [sp, #20]	@ save_yuv_with_crop,
	str	lr, [sp, #24]	@ save_yuv_with_crop,
	bl	DBG_WriteBigTileYuv	@
	ldr	ip, [r4, #256]	@ <variable>.is_3D, <variable>.is_3D
	str	r8, [r4, #252]	@ tmp202, <variable>.image_id_1
	cmp	ip, #1	@ <variable>.is_3D,
	movne	r7, #1	@ ret,
	bne	.L1541	@,
	b	.L1563	@
.L1557:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4138	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC215	@,
	movt	r3, #:upper16:.LC215	@,
	bl	dprint_vfmw	@
	mvn	r7, #0	@ ret,
	b	.L1533	@
.L1558:
	movw	r1, #:lower16:.LC234	@,
	movt	r1, #:upper16:.LC234	@,
	movw	r2, #4151	@,
	mov	r0, #0	@,
.L1554:
	bl	dprint_vfmw	@
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	mvn	r7, #0	@ ret,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L1533	@
.L1562:
	ldr	r3, [r6, r5, asl #2]	@ tmp208, s_pstVfmwChan
	sub	sl, fp, #548	@ tmp209,,
	movw	r9, #:lower16:.LANCHOR0	@ tmp205,
	movt	r9, #:upper16:.LANCHOR0	@ tmp205,
	add	ip, r3, #250880	@, tmp208,
	mov	r1, sl	@, tmp209
	add	r0, ip, #696	@,,
	bl	SYNTAX_ReceiveImage	@
	cmp	r0, #1	@ ret,
	mov	r7, r0	@ ret,
	bne	.L1564	@,
	ldr	r3, [r4, #248]	@ D.51980, <variable>.view_id
	ldr	r0, [fp, #-300]	@ D.51981, Image_1.view_id
	cmp	r3, r0	@ D.51980, D.51981
	blt	.L1565	@,
	bgt	.L1566	@,
	cmp	r3, #0	@ D.51980,
	bne	.L1547	@,
	ldr	r0, [r9, r5, asl #2]	@ tmp242, s_pstVfmwChan
	add	lr, r0, #250880	@, tmp242,
	add	r0, lr, #696	@,,
	bl	SYNTAX_ReturnImage	@
	ldr	r2, [r9, r5, asl #2]	@ tmp246, s_pstVfmwChan
	mov	r1, r4	@, pImage
	add	ip, r2, #250880	@, tmp246,
	add	r0, ip, #696	@,,
	bl	SYNTAX_ReleaseImage	@
	mov	r0, r7	@, ret
	movw	r1, #:lower16:.LC238	@,
	ldr	r2, .L1568	@,
	movt	r1, #:upper16:.LC238	@,
	ldr	r3, [r4, #248]	@, <variable>.view_id
	mvn	r7, #1	@ ret,
	bl	dprint_vfmw	@
	b	.L1541	@
.L1555:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4134	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r7, #0	@ ret,
	b	.L1533	@
.L1564:
	ldr	r2, [r9, r5, asl #2]	@ tmp214, s_pstVfmwChan
	add	r1, r2, #250880	@, tmp214,
	add	r0, r1, #696	@,,
	bl	SYNTAX_ReturnImage	@
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L1533	@
.L1565:
	ldr	r8, [fp, #-456]	@ Image_1.top_chrom_phy_addr, Image_1.top_chrom_phy_addr
	sub	lr, fp, #128	@ tmp221,,
	add	ip, r4, #280	@ tmp220, pImage,
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp329,,,,
	str	r8, [r4, #264]	@ Image_1.top_chrom_phy_addr, <variable>.top_chrom_phy_addr_1
	ldr	r8, [fp, #-460]	@ Image_1.top_luma_phy_addr, Image_1.top_luma_phy_addr
	str	r8, [r4, #260]	@ Image_1.top_luma_phy_addr, <variable>.top_luma_phy_addr_1
	ldr	r8, [fp, #-452]	@ Image_1.btm_luma_phy_addr, Image_1.btm_luma_phy_addr
	str	r8, [r4, #268]	@ Image_1.btm_luma_phy_addr, <variable>.btm_luma_phy_addr_1
	ldr	r8, [fp, #-448]	@ Image_1.btm_chrom_phy_addr, Image_1.btm_chrom_phy_addr
	str	r8, [r4, #272]	@ Image_1.btm_chrom_phy_addr, <variable>.btm_chrom_phy_addr_1
	mov	r8, ip	@ tmp330, tmp220
	stmia	r8!, {r0, r1, r2, r3}	@ tmp330,,,,
	mov	ip, r8	@ tmp332, tmp330
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp331,,,,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp332,,,,
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp333,,,,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp332,,,,
	ldmia	lr, {r0, r1, r2}	@ tmp333,,,
	stmia	ip, {r0, r1, r2}	@ tmp334,,,
	ldr	r3, [fp, #-304]	@ Image_1.last_frame, Image_1.last_frame
	ldr	lr, [fp, #-352]	@ Image_1.image_id, Image_1.image_id
	mov	ip, #3	@ tmp223,
	cmp	r3, #0	@ Image_1.last_frame,
	str	ip, [r4, #364]	@ tmp223, <variable>.eFramePackingType
	str	lr, [r4, #252]	@ Image_1.image_id, <variable>.image_id_1
	strne	r7, [r4, #244]	@ ret, <variable>.last_frame
	b	.L1541	@
.L1547:
	ldr	ip, [r9, r5, asl #2]	@ tmp254, s_pstVfmwChan
	mov	r1, r4	@, pImage
	add	r3, ip, #250880	@, tmp254,
	add	r0, r3, #696	@,,
	bl	SYNTAX_ReleaseImage	@
	ldr	r1, [fp, #-304]	@ Image_1.last_frame, Image_1.last_frame
	cmp	r1, #0	@ Image_1.last_frame,
	beq	.L1567	@,
	ldr	r3, [r4, #248]	@, <variable>.view_id
	mov	r0, r7	@, ret
	ldr	r2, .L1568	@,
	movw	r1, #:lower16:.LC239	@,
	movt	r1, #:upper16:.LC239	@,
	bl	dprint_vfmw	@
	mov	r1, sl	@, tmp209
	mov	r2, #504	@,
	mov	r0, r4	@, pImage
	bl	memcpy	@
	sub	lr, fp, #128	@ tmp278,,
	ldr	sl, [fp, #-456]	@ Image_1.top_chrom_phy_addr, Image_1.top_chrom_phy_addr
	add	ip, r4, #280	@ tmp277, pImage,
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp335,,,,
	str	sl, [r4, #264]	@ Image_1.top_chrom_phy_addr, <variable>.top_chrom_phy_addr_1
	ldr	sl, [fp, #-460]	@ Image_1.top_luma_phy_addr, Image_1.top_luma_phy_addr
	str	sl, [r4, #260]	@ Image_1.top_luma_phy_addr, <variable>.top_luma_phy_addr_1
	mov	sl, ip	@ tmp336, tmp277
	mov	ip, lr	@ tmp337, tmp335
	stmia	sl!, {r0, r1, r2, r3}	@ tmp336,,,,
	mov	lr, sl	@ tmp338, tmp336
	ldmia	ip!, {r0, r1, r2, r3}	@ tmp337,,,,
	stmia	lr!, {r0, r1, r2, r3}	@ tmp338,,,,
	ldmia	ip!, {r0, r1, r2, r3}	@ tmp339,,,,
	stmia	lr!, {r0, r1, r2, r3}	@ tmp338,,,,
	ldmia	ip, {r0, r1, r2}	@ tmp339,,,
	stmia	lr, {r0, r1, r2}	@ tmp340,,,
	mov	r0, #3	@ tmp280,
	str	r8, [r4, #252]	@ tmp202, <variable>.image_id_1
	str	r0, [r4, #364]	@ tmp280, <variable>.eFramePackingType
	str	r7, [r4, #244]	@ ret, <variable>.last_frame
	b	.L1541	@
.L1566:
	ldr	r3, [r9, r5, asl #2]	@ tmp229, s_pstVfmwChan
	add	r1, r3, #250880	@, tmp229,
	add	r0, r1, #696	@,,
	bl	SYNTAX_ReturnImage	@
	ldr	r0, [r9, r5, asl #2]	@ tmp233, s_pstVfmwChan
	mov	r1, r4	@, pImage
	add	r2, r0, #250880	@, tmp233,
	add	r0, r2, #696	@,,
	bl	SYNTAX_ReleaseImage	@
	mov	r0, r7	@, ret
	ldr	r7, [fp, #-300]	@ Image_1.view_id, Image_1.view_id
	movw	r1, #:lower16:.LC237	@,
	ldr	r3, [r4, #248]	@ <variable>.view_id, <variable>.view_id
	movt	r1, #:upper16:.LC237	@,
	ldr	r2, .L1568	@,
	str	r7, [sp, #0]	@ Image_1.view_id,
	bl	dprint_vfmw	@
	mvn	r7, #1	@ ret,
	b	.L1541	@
.L1556:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4135	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	mvn	r7, #0	@ ret,
	bl	dprint_vfmw	@
	b	.L1533	@
.L1567:
	ldr	lr, [r9, r5, asl #2]	@ tmp259, s_pstVfmwChan
	mov	r1, sl	@, tmp209
	add	r2, lr, #250880	@, tmp259,
	add	r0, r2, #696	@,,
	bl	SYNTAX_ReleaseImage	@
	mov	r0, r7	@, ret
	movw	r1, #:lower16:.LC239	@,
	ldr	r2, .L1568	@,
	movt	r1, #:upper16:.LC239	@,
	ldr	r3, [r4, #248]	@, <variable>.view_id
	mvn	r7, #1	@ ret,
	bl	dprint_vfmw	@
	b	.L1541	@
.L1569:
	.align	2
.L1568:
	.word	.LANCHOR1+292
	.fnend
	.size	VCTRL_GetChanImage, .-VCTRL_GetChanImage
	.align	2
	.global	VCTRL_ReleaseStream
	.type	VCTRL_ReleaseStream, %function
VCTRL_ReleaseStream:
	.fnstart
.LFB1582:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	ldr	r3, [r3, r0, asl #2]	@ tmp138, s_pstVfmwChan
	cmp	r3, #0	@ tmp138,
	beq	.L1575	@,
	bl	SM_Reset	@
	cmp	r0, #0	@ ret
	mvnne	r0, #0	@, D.51843,
	ldmfd	sp, {fp, sp, pc}	@
.L1575:
	mov	r0, r3	@, tmp138
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4013	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51843,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_ReleaseStream, .-VCTRL_ReleaseStream
	.align	2
	.global	VCTRL_LoadDspCode
	.type	VCTRL_LoadDspCode, %function
VCTRL_LoadDspCode:
	.fnstart
.LFB1580:
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
	movw	r5, #:lower16:.LANCHOR0	@ tmp516,
	movt	r5, #:upper16:.LANCHOR0	@ tmp516,
	movw	r6, #:lower16:.LANCHOR3	@ tmp517,
	movt	r6, #:upper16:.LANCHOR3	@ tmp517,
	mov	r4, r0	@ ChanID, ChanID
	ldr	r2, [r5, r0, asl #2]	@ D.51715, s_pstVfmwChan
	ldr	ip, [r6, #-1460]	@ eDSPState, g_DSPState
	ldr	r3, [r2, #544]	@ D.51716, <variable>.eVidStd
	cmp	r3, #0	@ D.51716,
	movne	r2, #0	@ ScdLowdlyEnable,
	ldreq	r2, [r2, #1260]	@ ScdLowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1456]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1452]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1448]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1444]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1440]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1436]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1432]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1428]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1424]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1420]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1416]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1412]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1408]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1404]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	ldr	ip, [r6, #-1400]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1579	@,
	cmp	r2, #1	@ ScdLowdlyEnable,
	movne	sl, #0	@, D.51726
	moveq	sl, #1	@, D.51726
	mov	r8, #1	@ prephitmp.4661,
.L1583:
	movw	r7, #:lower16:g_vdm_hal_fun_ptr	@ tmp515,
	movt	r7, #:upper16:g_vdm_hal_fun_ptr	@ tmp515,
	ldr	r3, [r7, #0]	@ D.51735, g_vdm_hal_fun_ptr.pfun_VDMDRV_OpenHardware
	cmp	r3, #0	@ D.51735,
	beq	.L1660	@,
	mov	r0, #0	@,
	blx	r3	@ D.51735
.L1587:
	ldr	r3, [r7, #8]	@ D.51740, g_vdm_hal_fun_ptr.pfun_DSPDRV_OpenHardware
	cmp	r3, #0	@ D.51740,
	beq	.L1588	@,
	mov	r0, #0	@,
	blx	r3	@ D.51740
.L1589:
	ands	r1, r8, sl	@ tmp234, prephitmp.4661, D.51726
	beq	.L1590	@,
	ldr	r2, [r5, r4, asl #2]	@ tmp236, s_pstVfmwChan
	add	r6, r6, r4, asl #2	@, tmp241, tmp517, ChanID,
	mov	r1, #0	@,
	ldr	r0, [r2, #544]	@, <variable>.eVidStd
	bl	WriteHexFile	@
	mov	r3, #1	@ tmp243,
	str	r3, [r6, #-1460]	@ tmp243, g_DSPState
.L1591:
	ldr	r3, [r5, #0]	@ temp.4669, s_pstVfmwChan
	cmp	r3, #0	@ temp.4669,
	cmpne	r4, #0	@, ChanID,
	movne	r0, #0	@, tmp265
	moveq	r0, #1	@, tmp265
	moveq	r0, #0	@ dsp_need_flag,
	beq	.L1594	@,
	ldr	r2, [r3, #544]	@ eVidStd.4673, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4673,
	bne	.L1595	@,
	ldr	lr, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	lr, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r0, #0	@, prephitmp.4674
	moveq	r0, #1	@, prephitmp.4674
.L1595:
	cmp	r2, #6	@ eVidStd.4673,
	orreq	r0, r0, #1	@,, dsp_need_flag, prephitmp.4674
.L1594:
	ldr	r3, [r5, #4]	@ temp.4678, s_pstVfmwChan
	cmp	r3, #0	@ temp.4678,
	cmpne	r4, #1	@, ChanID,
	movne	r1, #0	@, tmp279
	moveq	r1, #1	@, tmp279
	beq	.L1596	@,
	ldr	r2, [r3, #544]	@ eVidStd.4682, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4682,
	bne	.L1599	@,
	ldr	ip, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	ip, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4683
	moveq	r1, #1	@, prephitmp.4683
.L1599:
	cmp	r2, #6	@ eVidStd.4682,
	movne	r3, r1	@, tmp284, prephitmp.4683
	orreq	r3, r1, #1	@,, tmp284, prephitmp.4683
	cmp	r3, #0	@ tmp284,
	movne	r0, #1	@ dsp_need_flag,
.L1596:
	ldr	r3, [r5, #8]	@ temp.4687, s_pstVfmwChan
	cmp	r3, #0	@ temp.4687,
	cmpne	r4, #2	@, ChanID,
	movne	r1, #0	@, tmp295
	moveq	r1, #1	@, tmp295
	beq	.L1600	@,
	ldr	r2, [r3, #544]	@ eVidStd.4691, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4691,
	bne	.L1603	@,
	ldr	r1, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4692
	moveq	r1, #1	@, prephitmp.4692
.L1603:
	cmp	r2, #6	@ eVidStd.4691,
	movne	r2, r1	@, tmp300, prephitmp.4692
	orreq	r2, r1, #1	@,, tmp300, prephitmp.4692
	cmp	r2, #0	@ tmp300,
	movne	r0, #1	@ dsp_need_flag,
.L1600:
	ldr	r3, [r5, #12]	@ temp.4696, s_pstVfmwChan
	cmp	r4, #3	@ ChanID,
	cmpne	r3, #0	@, temp.4696,
	movne	r1, #0	@, tmp311
	moveq	r1, #1	@, tmp311
	beq	.L1604	@,
	ldr	r2, [r3, #544]	@ eVidStd.4700, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4700,
	bne	.L1607	@,
	ldr	ip, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	ip, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4701
	moveq	r1, #1	@, prephitmp.4701
.L1607:
	cmp	r2, #6	@ eVidStd.4700,
	movne	lr, r1	@, tmp316, prephitmp.4701
	orreq	lr, r1, #1	@,, tmp316, prephitmp.4701
	cmp	lr, #0	@ tmp316,
	movne	r0, #1	@ dsp_need_flag,
.L1604:
	ldr	r3, [r5, #16]	@ temp.4705, s_pstVfmwChan
	cmp	r4, #4	@ ChanID,
	cmpne	r3, #0	@, temp.4705,
	movne	r1, #0	@, tmp327
	moveq	r1, #1	@, tmp327
	beq	.L1608	@,
	ldr	r2, [r3, #544]	@ eVidStd.4709, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4709,
	bne	.L1611	@,
	ldr	r1, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4710
	moveq	r1, #1	@, prephitmp.4710
.L1611:
	cmp	r2, #6	@ eVidStd.4709,
	movne	r3, r1	@, tmp332, prephitmp.4710
	orreq	r3, r1, #1	@,, tmp332, prephitmp.4710
	cmp	r3, #0	@ tmp332,
	movne	r0, #1	@ dsp_need_flag,
.L1608:
	ldr	r3, [r5, #20]	@ temp.4714, s_pstVfmwChan
	cmp	r4, #5	@ ChanID,
	cmpne	r3, #0	@, temp.4714,
	movne	r1, #0	@, tmp343
	moveq	r1, #1	@, tmp343
	beq	.L1612	@,
	ldr	r2, [r3, #544]	@ eVidStd.4718, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4718,
	bne	.L1615	@,
	ldr	lr, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	lr, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4719
	moveq	r1, #1	@, prephitmp.4719
.L1615:
	cmp	r2, #6	@ eVidStd.4718,
	movne	r2, r1	@, tmp348, prephitmp.4719
	orreq	r2, r1, #1	@,, tmp348, prephitmp.4719
	cmp	r2, #0	@ tmp348,
	movne	r0, #1	@ dsp_need_flag,
.L1612:
	ldr	r3, [r5, #24]	@ temp.4723, s_pstVfmwChan
	cmp	r4, #6	@ ChanID,
	cmpne	r3, #0	@, temp.4723,
	movne	r1, #0	@, tmp359
	moveq	r1, #1	@, tmp359
	beq	.L1616	@,
	ldr	r2, [r3, #544]	@ eVidStd.4727, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4727,
	bne	.L1619	@,
	ldr	r1, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4728
	moveq	r1, #1	@, prephitmp.4728
.L1619:
	cmp	r2, #6	@ eVidStd.4727,
	movne	ip, r1	@, tmp364, prephitmp.4728
	orreq	ip, r1, #1	@,, tmp364, prephitmp.4728
	cmp	ip, #0	@ tmp364,
	movne	r0, #1	@ dsp_need_flag,
.L1616:
	ldr	r3, [r5, #28]	@ temp.4732, s_pstVfmwChan
	cmp	r4, #7	@ ChanID,
	cmpne	r3, #0	@, temp.4732,
	movne	r1, #0	@, tmp375
	moveq	r1, #1	@, tmp375
	beq	.L1620	@,
	ldr	r2, [r3, #544]	@ eVidStd.4736, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4736,
	bne	.L1623	@,
	ldr	lr, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	lr, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4737
	moveq	r1, #1	@, prephitmp.4737
.L1623:
	cmp	r2, #6	@ eVidStd.4736,
	movne	r3, r1	@, tmp380, prephitmp.4737
	orreq	r3, r1, #1	@,, tmp380, prephitmp.4737
	cmp	r3, #0	@ tmp380,
	movne	r0, #1	@ dsp_need_flag,
.L1620:
	ldr	r3, [r5, #32]	@ temp.4741, s_pstVfmwChan
	cmp	r4, #8	@ ChanID,
	cmpne	r3, #0	@, temp.4741,
	movne	r1, #0	@, tmp391
	moveq	r1, #1	@, tmp391
	beq	.L1624	@,
	ldr	r2, [r3, #544]	@ eVidStd.4745, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4745,
	bne	.L1627	@,
	ldr	ip, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	ip, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4746
	moveq	r1, #1	@, prephitmp.4746
.L1627:
	cmp	r2, #6	@ eVidStd.4745,
	movne	r2, r1	@, tmp396, prephitmp.4746
	orreq	r2, r1, #1	@,, tmp396, prephitmp.4746
	cmp	r2, #0	@ tmp396,
	movne	r0, #1	@ dsp_need_flag,
.L1624:
	ldr	r3, [r5, #36]	@ temp.4750, s_pstVfmwChan
	cmp	r4, #9	@ ChanID,
	cmpne	r3, #0	@, temp.4750,
	movne	r1, #0	@, tmp407
	moveq	r1, #1	@, tmp407
	beq	.L1628	@,
	ldr	r2, [r3, #544]	@ eVidStd.4754, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4754,
	bne	.L1631	@,
	ldr	r1, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4755
	moveq	r1, #1	@, prephitmp.4755
.L1631:
	cmp	r2, #6	@ eVidStd.4754,
	movne	r3, r1	@, tmp412, prephitmp.4755
	orreq	r3, r1, #1	@,, tmp412, prephitmp.4755
	cmp	r3, #0	@ tmp412,
	movne	r0, #1	@ dsp_need_flag,
.L1628:
	ldr	r3, [r5, #40]	@ temp.4759, s_pstVfmwChan
	cmp	r4, #10	@ ChanID,
	cmpne	r3, #0	@, temp.4759,
	movne	r1, #0	@, tmp423
	moveq	r1, #1	@, tmp423
	beq	.L1632	@,
	ldr	r2, [r3, #544]	@ eVidStd.4763, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4763,
	bne	.L1635	@,
	ldr	ip, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	ip, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4764
	moveq	r1, #1	@, prephitmp.4764
.L1635:
	cmp	r2, #6	@ eVidStd.4763,
	movne	lr, r1	@, tmp428, prephitmp.4764
	orreq	lr, r1, #1	@,, tmp428, prephitmp.4764
	cmp	lr, #0	@ tmp428,
	movne	r0, #1	@ dsp_need_flag,
.L1632:
	ldr	r3, [r5, #44]	@ temp.4768, s_pstVfmwChan
	cmp	r4, #11	@ ChanID,
	cmpne	r3, #0	@, temp.4768,
	movne	r1, #0	@, tmp439
	moveq	r1, #1	@, tmp439
	beq	.L1636	@,
	ldr	r2, [r3, #544]	@ eVidStd.4772, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4772,
	bne	.L1639	@,
	ldr	r1, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4773
	moveq	r1, #1	@, prephitmp.4773
.L1639:
	cmp	r2, #6	@ eVidStd.4772,
	movne	r2, r1	@, tmp444, prephitmp.4773
	orreq	r2, r1, #1	@,, tmp444, prephitmp.4773
	cmp	r2, #0	@ tmp444,
	movne	r0, #1	@ dsp_need_flag,
.L1636:
	ldr	r3, [r5, #48]	@ temp.4777, s_pstVfmwChan
	cmp	r4, #12	@ ChanID,
	cmpne	r3, #0	@, temp.4777,
	movne	r1, #0	@, tmp455
	moveq	r1, #1	@, tmp455
	beq	.L1640	@,
	ldr	r2, [r3, #544]	@ eVidStd.4781, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4781,
	bne	.L1643	@,
	ldr	lr, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	lr, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4782
	moveq	r1, #1	@, prephitmp.4782
.L1643:
	cmp	r2, #6	@ eVidStd.4781,
	movne	r3, r1	@, tmp460, prephitmp.4782
	orreq	r3, r1, #1	@,, tmp460, prephitmp.4782
	cmp	r3, #0	@ tmp460,
	movne	r0, #1	@ dsp_need_flag,
.L1640:
	ldr	r3, [r5, #52]	@ temp.4786, s_pstVfmwChan
	cmp	r4, #13	@ ChanID,
	cmpne	r3, #0	@, temp.4786,
	movne	r1, #0	@, tmp471
	moveq	r1, #1	@, tmp471
	beq	.L1644	@,
	ldr	r2, [r3, #544]	@ eVidStd.4790, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4790,
	bne	.L1647	@,
	ldr	r1, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r1, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4791
	moveq	r1, #1	@, prephitmp.4791
.L1647:
	cmp	r2, #6	@ eVidStd.4790,
	movne	ip, r1	@, tmp476, prephitmp.4791
	orreq	ip, r1, #1	@,, tmp476, prephitmp.4791
	cmp	ip, #0	@ tmp476,
	movne	r0, #1	@ dsp_need_flag,
.L1644:
	ldr	r3, [r5, #56]	@ temp.4795, s_pstVfmwChan
	cmp	r4, #14	@ ChanID,
	cmpne	r3, #0	@, temp.4795,
	movne	r1, #0	@, tmp487
	moveq	r1, #1	@, tmp487
	beq	.L1648	@,
	ldr	r2, [r3, #544]	@ eVidStd.4799, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd.4799,
	bne	.L1651	@,
	ldr	lr, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	lr, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r1, #0	@, prephitmp.4800
	moveq	r1, #1	@, prephitmp.4800
.L1651:
	cmp	r2, #6	@ eVidStd.4799,
	movne	r2, r1	@, tmp492, prephitmp.4800
	orreq	r2, r1, #1	@,, tmp492, prephitmp.4800
	cmp	r2, #0	@ tmp492,
	movne	r0, #1	@ dsp_need_flag,
.L1648:
	ldr	r3, [r5, #60]	@ D.51754, s_pstVfmwChan
	cmp	r4, #15	@ ChanID,
	cmpne	r3, #0	@, D.51754,
	movne	r4, #0	@, tmp503
	moveq	r4, #1	@, tmp503
	beq	.L1652	@,
	ldr	r2, [r3, #544]	@ eVidStd, <variable>.eVidStd
	cmp	r2, #0	@ eVidStd,
	bne	.L1654	@,
	ldr	r4, [r3, #1260]	@ <variable>.stSynExtraData.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	cmp	r4, #1	@ <variable>.stSynExtraData.s32LowdlyEnable,
	movne	r4, #0	@, prephitmp.4645
	moveq	r4, #1	@, prephitmp.4645
.L1654:
	cmp	r2, #6	@ eVidStd,
	movne	r3, r4	@, tmp511, prephitmp.4645
	orreq	r3, r4, #1	@,, tmp511, prephitmp.4645
	cmp	r3, #0	@ tmp511,
	bne	.L1655	@,
.L1652:
	cmp	r0, #0	@ dsp_need_flag,
	bne	.L1655	@,
	ldr	r3, [r7, #12]	@ D.51771, g_vdm_hal_fun_ptr.pfun_DSPDRV_CloseHardware
	cmp	r3, #0	@ D.51771,
	beq	.L1661	@,
	blx	r3	@ D.51771
.L1655:
	bl	VCTRL_CloseHardware	@
	mov	r0, #0	@ ret,
.L1586:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L1579:
	cmp	r2, #1	@ ScdLowdlyEnable,
	movne	sl, #0	@, D.51726
	moveq	sl, #1	@, D.51726
	cmp	ip, #2	@ eDSPState,
	cmpeq	r2, #1	@, ScdLowdlyEnable,
	beq	.L1581	@,
	cmp	ip, #1	@ eDSPState,
	cmpeq	r3, #6	@, D.51716,
	movne	r8, #0	@, tmp226
	moveq	r8, #1	@, tmp226
	bne	.L1583	@,
.L1581:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC240	@,
	movt	r1, #:upper16:.LC240	@,
	str	ip, [sp, #0]	@ eDSPState,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L1586	@
.L1590:
	ldr	ip, [r5, r4, asl #2]	@ tmp245, s_pstVfmwChan
	ldr	r0, [ip, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r0, #6	@ <variable>.eVidStd,
	movne	r8, #0	@, tmp251
	andeq	r8, r8, #1	@,, tmp251, prephitmp.4661
	cmp	r8, #0	@ tmp251,
	beq	.L1591	@,
	add	r6, r6, r4, asl #2	@, tmp255, tmp517, ChanID,
	mov	r0, #6	@,
	bl	WriteHexFile	@
	mov	r1, #2	@ tmp257,
	str	r1, [r6, #-1460]	@ tmp257, g_DSPState
	b	.L1591	@
.L1588:
	mov	r0, r3	@, D.51740
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #3783	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L1589	@
.L1660:
	mov	r0, r3	@, D.51735
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #3782	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L1587	@
.L1661:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #3836	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L1655	@
	.fnend
	.size	VCTRL_LoadDspCode, .-VCTRL_LoadDspCode
	.align	2
	.global	VCTRL_SeekPts
	.type	VCTRL_SeekPts, %function
VCTRL_SeekPts:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r2, [r3, r0, asl #2]	@ D.51668, s_pstVfmwChan
	cmp	r2, #0	@ D.51668,
	beq	.L1669	@,
	ldr	r2, [r2, #544]	@ D.51676, <variable>.eVidStd
	sub	ip, r2, #10	@ tmp143, D.51676,
	cmp	ip, #2	@ tmp143,
	bls	.L1670	@,
	cmp	r2, #4	@ D.51676,
	bne	.L1671	@,
.L1666:
	mvn	r0, #0	@ D.51672,
	ldmfd	sp, {fp, sp, pc}	@
.L1670:
	ldr	r3, [r3, #516]	@ g_VdmCharacter, g_VdmCharacter
	tst	r3, #1	@ g_VdmCharacter,
	beq	.L1666	@,
.L1667:
	bl	SM_SeekPts	@
	cmp	r0, #0	@ ret
	ldmeqfd	sp, {fp, sp, pc}	@
	b	.L1666	@
.L1671:
	cmp	r2, #14	@ D.51676,
	beq	.L1666	@,
	b	.L1667	@
.L1669:
	mov	r0, r2	@, D.51668
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #3577	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51672,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_SeekPts, .-VCTRL_SeekPts
	.align	2
	.global	VCTRL_StopChan
	.type	VCTRL_StopChan, %function
VCTRL_StopChan:
	.fnstart
.LFB1573:
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
	cmp	r0, #15	@ ChanID,
	mov	r5, r0	@ ChanID, ChanID
	bhi	.L1678	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp140,
	movt	r4, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r3, [r4, r0, asl #2]	@ D.51200, s_pstVfmwChan
	cmp	r3, #0	@ D.51200,
	beq	.L1679	@,
	ldr	r2, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r2, #1	@ <variable>.s32IsOpen,
	beq	.L1680	@,
.L1676:
	mvn	r0, #0	@ D.51198,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1679:
	mov	r0, r3	@, D.51200
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2830	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC241	@,
	movt	r3, #:upper16:.LC241	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51198,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1678:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2829	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51198,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1680:
	str	r2, [r3, #28]	@ <variable>.s32IsOpen, <variable>.s32StopSyntax
	mov	r2, #0	@ tmp147,
	ldr	r3, [r4, r0, asl #2]	@ tmp146, s_pstVfmwChan
	str	r2, [r3, #16]	@ tmp147, <variable>.s32IsRun
	bl	SM_Stop	@
	subs	r6, r0, #0	@ s32Ret,
	bne	.L1676	@,
	mov	r1, r6	@, s32Ret
	mov	r0, r5	@, ChanID
	bl	DeleteRawPacketInBuffer	@
	mov	r0, r5	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	ldr	r0, [r4, r5, asl #2]	@ tmp149, s_pstVfmwChan
	str	r6, [r0, #28]	@ s32Ret, <variable>.s32StopSyntax
	bl	VCTRL_CloseHardware	@
	mov	r0, r6	@ D.51198, s32Ret
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VCTRL_StopChan, .-VCTRL_StopChan
	.align	2
	.global	VCTRL_StopChanWithCheck
	.type	VCTRL_StopChanWithCheck, %function
VCTRL_StopChanWithCheck:
	.fnstart
.LFB1572:
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
	mov	r5, #0	@ i,
	mov	r6, r0	@ ChanID, ChanID
	b	.L1683	@
.L1688:
	bl	msleep	@
	ldr	r0, .L1689	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	bl	VCTRL_StopChan	@
	mov	r4, r0	@ ret,
	bl	VCTRL_EnableAllInt	@
	ldr	r0, .L1689	@,
	bl	OSAL_SpinUnLockIRQ	@
	cmp	r4, #0	@ ret,
	mov	r0, #10	@,
	beq	.L1682	@,
	bl	msleep	@
	cmp	r5, #50	@ i,
	beq	.L1682	@,
.L1683:
	ldr	r0, .L1689	@,
	add	r5, r5, #1	@ tmp146, i,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	bl	VCTRL_StopChan	@
	add	r5, r5, #1	@ i, tmp146,
	mov	r4, r0	@ ret,
	bl	VCTRL_EnableAllInt	@
	ldr	r0, .L1689	@,
	bl	OSAL_SpinUnLockIRQ	@
	cmp	r4, #0	@ ret,
	mov	r0, #10	@,
	bne	.L1688	@,
.L1682:
	mov	r0, r4	@, ret
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1690:
	.align	2
.L1689:
	.word	.LANCHOR0+520
	.fnend
	.size	VCTRL_StopChanWithCheck, .-VCTRL_StopChanWithCheck
	.align	2
	.global	VCTRL_StartChan
	.type	VCTRL_StartChan, %function
VCTRL_StartChan:
	.fnstart
.LFB1570:
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
	cmp	r0, #15	@ ChanID,
	mov	r5, r0	@ ChanID, ChanID
	bhi	.L1731	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp326,
	movt	r4, #:upper16:.LANCHOR0	@ tmp326,
	ldr	r3, [r4, r0, asl #2]	@ D.51124, s_pstVfmwChan
	cmp	r3, #0	@ D.51124,
	beq	.L1732	@,
	ldr	r6, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r6, #1	@ <variable>.s32IsOpen,
	bne	.L1733	@,
	ldr	r3, [r3, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #19	@ <variable>.eVidStd,
	beq	.L1734	@,
	bl	SM_Start	@
	ldr	r2, [r4, r5, asl #2]	@ tmp167, s_pstVfmwChan
	mov	ip, #0	@ tmp171,
	str	r6, [r2, #16]	@ <variable>.s32IsOpen, <variable>.s32IsRun
	ldr	r3, [r4, r5, asl #2]	@ tmp170, s_pstVfmwChan
	str	ip, [r3, #28]	@ tmp171, <variable>.s32StopSyntax
	ldr	r1, [r4, r5, asl #2]	@ tmp173, s_pstVfmwChan
	str	r6, [r1, #20]	@ <variable>.s32IsOpen, <variable>.s32IsInit
	ldr	r3, [r4, r5, asl #2]	@ temp.4912, s_pstVfmwChan
	ldr	r2, [r3, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r2, #0	@ <variable>.s32Priority,
	bne	.L1697	@,
	str	r6, [r3, #24]	@ <variable>.s32IsOpen, <variable>.s32Priority
	ldr	r1, [r4, #0]	@ temp.4914, s_pstVfmwChan
	cmp	r1, #0	@ temp.4914,
	beq	.L1735	@,
	ldr	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r3, #:lower16:.LANCHOR3	@ tmp327,
	movt	r3, #:upper16:.LANCHOR3	@ tmp327,
	movw	r2, #:lower16:g_ChanCtx	@ tmp328,
	movt	r2, #:upper16:g_ChanCtx	@ tmp328,
	str	r0, [r3, #-1396]	@ <variable>.s32Priority, PrioArray
	ldr	lr, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	str	lr, [r2, #0]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
.L1699:
	ldr	lr, [r4, #4]	@ temp.4917, s_pstVfmwChan
	ldr	ip, [r4, #8]	@ temp.4920, s_pstVfmwChan
	cmp	lr, #0	@ temp.4917,
	ldr	r1, [r4, #12]	@ temp.4923, s_pstVfmwChan
	streq	lr, [r3, #-1392]	@ temp.4917, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #4]	@ temp.4917, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-1392]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #4]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.4920,
	streq	ip, [r3, #-1388]	@ temp.4920, PrioArray
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r2, #8]	@ temp.4920, g_ChanCtx.PriorByChanId
	ldr	lr, [r4, #16]	@ temp.4926, s_pstVfmwChan
	strne	r0, [r3, #-1388]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #8]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.4923,
	streq	r1, [r3, #-1384]	@ temp.4923, PrioArray
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r2, #12]	@ temp.4923, g_ChanCtx.PriorByChanId
	ldr	ip, [r4, #20]	@ temp.4929, s_pstVfmwChan
	strne	r0, [r3, #-1384]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #12]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.4926,
	streq	lr, [r3, #-1380]	@ temp.4926, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #16]	@ temp.4926, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-1380]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #16]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.4929,
	streq	ip, [r3, #-1376]	@ temp.4929, PrioArray
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r2, #20]	@ temp.4929, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-1376]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #20]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	r1, [r4, #24]	@ temp.4932, s_pstVfmwChan
	ldr	lr, [r4, #28]	@ temp.4935, s_pstVfmwChan
	cmp	r1, #0	@ temp.4932,
	ldr	ip, [r4, #32]	@ temp.4938, s_pstVfmwChan
	streq	r1, [r3, #-1372]	@ temp.4932, PrioArray
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r2, #24]	@ temp.4932, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-1372]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #24]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.4935,
	streq	lr, [r3, #-1368]	@ temp.4935, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #28]	@ temp.4935, g_ChanCtx.PriorByChanId
	ldr	r1, [r4, #36]	@ temp.4941, s_pstVfmwChan
	strne	r0, [r3, #-1368]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #28]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.4938,
	streq	ip, [r3, #-1364]	@ temp.4938, PrioArray
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r2, #32]	@ temp.4938, g_ChanCtx.PriorByChanId
	ldr	lr, [r4, #40]	@ temp.4944, s_pstVfmwChan
	strne	r0, [r3, #-1364]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #32]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.4941,
	streq	r1, [r3, #-1360]	@ temp.4941, PrioArray
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r2, #36]	@ temp.4941, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-1360]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #36]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.4944,
	streq	lr, [r3, #-1356]	@ temp.4944, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #40]	@ temp.4944, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-1356]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #40]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	ip, [r4, #44]	@ temp.4947, s_pstVfmwChan
	ldr	r1, [r4, #48]	@ temp.4950, s_pstVfmwChan
	cmp	ip, #0	@ temp.4947,
	ldr	lr, [r4, #52]	@ temp.4953, s_pstVfmwChan
	streq	ip, [r2, #44]	@ temp.4947, g_ChanCtx.PriorByChanId
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r3, #-1352]	@ temp.4947, PrioArray
	strne	r0, [r3, #-1352]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #44]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.4950,
	streq	r1, [r2, #48]	@ temp.4950, g_ChanCtx.PriorByChanId
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r3, #-1348]	@ temp.4950, PrioArray
	ldr	ip, [r4, #56]	@ temp.4956, s_pstVfmwChan
	strne	r0, [r3, #-1348]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #48]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.4953,
	streq	lr, [r2, #52]	@ temp.4953, g_ChanCtx.PriorByChanId
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r3, #-1344]	@ temp.4953, PrioArray
	ldr	r1, [r4, #60]	@ D.51137, s_pstVfmwChan
	strne	r0, [r3, #-1344]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #52]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.4956,
	streq	ip, [r2, #56]	@ temp.4956, g_ChanCtx.PriorByChanId
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r3, #-1340]	@ temp.4956, PrioArray
	strne	r0, [r3, #-1340]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #56]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ D.51137,
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r0, [r3, #-1336]	@ <variable>.s32Priority, PrioArray
	ldrne	r3, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	ldr	r0, .L1736	@,
	strne	r3, [r2, #60]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	streq	r1, [r2, #60]	@ D.51137, g_ChanCtx.PriorByChanId
	streq	r1, [r3, #-1336]	@ D.51137, PrioArray
	bl	VDMDRV_SetPriority	@
	mov	r0, r5	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
.L1697:
	mov	r0, r5	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	mov	r0, r5	@, ChanID
	bl	VCTRL_OpenHardware	@
	mov	r0, #0	@ D.51122,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1735:
	movw	r3, #:lower16:.LANCHOR3	@ tmp327,
	movw	r2, #:lower16:g_ChanCtx	@ tmp328,
	movt	r3, #:upper16:.LANCHOR3	@ tmp327,
	movt	r2, #:upper16:g_ChanCtx	@ tmp328,
	str	r1, [r3, #-1396]	@ temp.4914, PrioArray
	str	r1, [r2, #0]	@ temp.4914, g_ChanCtx.PriorByChanId
	b	.L1699	@
.L1733:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2662	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC26	@,
	movt	r3, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51122,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1731:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2660	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51122,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1734:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2663	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC242	@,
	movt	r3, #:upper16:.LC242	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51122,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1732:
	mov	r0, r3	@, D.51124
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2661	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC161	@,
	movt	r3, #:upper16:.LC161	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51122,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1737:
	.align	2
.L1736:
	.word	.LANCHOR3-1396
	.fnend
	.size	VCTRL_StartChan, .-VCTRL_StartChan
	.align	2
	.global	VCTRL_FreeChanResource
	.type	VCTRL_FreeChanResource, %function
VCTRL_FreeChanResource:
	.fnstart
.LFB1564:
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
	ldr	r3, [r1, #104]	@ <variable>.u32DynamicAllocEn, <variable>.u32DynamicAllocEn
	mov	r6, r1	@ pstChan, pstChan
	cmp	r3, #1	@ <variable>.u32DynamicAllocEn,
	beq	.L1739	@,
	ldr	r0, [r1, #24]	@, <variable>.stChanMem_vdh.PhyAddr
	ldr	r2, [r6, #28]	@, <variable>.stChanMem_vdh.Length
	ldr	r1, [r1, #20]	@, <variable>.stChanMem_vdh.VirAddr
	bl	MEM_DelMemRecord	@
.L1740:
	ldr	r2, [r6, #44]	@ D.50546, <variable>.stChanMem_scd.Length
	cmp	r2, #0	@ D.50546,
	bne	.L1761	@,
	ldr	ip, [r6, #80]	@ <variable>.s32SelfAllocChanMem_vdh, <variable>.s32SelfAllocChanMem_vdh
	cmp	ip, #1	@ <variable>.s32SelfAllocChanMem_vdh,
	beq	.L1762	@,
.L1746:
	ldr	lr, [r6, #28]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	cmp	lr, #0	@ <variable>.stChanMem_vdh.Length,
	bne	.L1763	@,
.L1747:
	ldr	r1, [r6, #84]	@ <variable>.s32SelfAllocChanMem_scd, <variable>.s32SelfAllocChanMem_scd
	cmp	r1, #1	@ <variable>.s32SelfAllocChanMem_scd,
	beq	.L1764	@,
.L1748:
	ldr	r2, [r6, #44]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	cmp	r2, #0	@ <variable>.stChanMem_scd.Length,
	bne	.L1765	@,
.L1749:
	ldr	lr, [r6, #88]	@ <variable>.s32SelfAllocChanMem_ctx, <variable>.s32SelfAllocChanMem_ctx
	cmp	lr, #1	@ <variable>.s32SelfAllocChanMem_ctx,
	beq	.L1766	@,
.L1750:
	ldr	r0, [r6, #52]	@, <variable>.stChanMem_ctx.VirAddr
	bl	KernelMunmap	@
.L1751:
	ldr	r1, [r6, #52]	@, <variable>.stChanMem_ctx.VirAddr
	ldr	r2, [r6, #60]	@, <variable>.stChanMem_ctx.Length
	ldr	r0, [r6, #56]	@, <variable>.stChanMem_ctx.PhyAddr
	bl	MEM_DelMemRecord	@
	add	r0, r6, #64	@, pstChan,
	bl	SM_DeletDSPCtxMem	@
	mov	r0, #0	@,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L1765:
	ldrsb	ip, [r6, #32]	@ <variable>.stChanMem_scd.IsCached, <variable>.stChanMem_scd.IsCached
	cmp	ip, #1	@ <variable>.stChanMem_scd.IsCached,
	bne	.L1749	@,
	ldr	r0, [r6, #36]	@, <variable>.stChanMem_scd.VirAddr
	bl	KernelMunmap	@
	ldr	r0, [r6, #40]	@, <variable>.stChanMem_scd.PhyAddr
	ldr	r1, [r6, #44]	@, <variable>.stChanMem_scd.Length
	bl	KernelMmap	@
	mov	r3, #0	@ tmp187,
	strb	r3, [r6, #32]	@ tmp187, <variable>.stChanMem_scd.IsCached
	b	.L1749	@
.L1763:
	ldrsb	r3, [r6, #16]	@ <variable>.stChanMem_vdh.IsCached, <variable>.stChanMem_vdh.IsCached
	cmp	r3, #1	@ <variable>.stChanMem_vdh.IsCached,
	bne	.L1747	@,
	ldr	r0, [r6, #20]	@, <variable>.stChanMem_vdh.VirAddr
	bl	KernelMunmap	@
	ldr	r0, [r6, #24]	@, <variable>.stChanMem_vdh.PhyAddr
	ldr	r1, [r6, #28]	@, <variable>.stChanMem_vdh.Length
	bl	KernelMmap	@
	mov	r0, #0	@ tmp178,
	strb	r0, [r6, #16]	@ tmp178, <variable>.stChanMem_vdh.IsCached
	b	.L1747	@
.L1739:
	mov	r4, #0	@ ivtmp.4996,
	mvn	r7, #0	@ tmp197,
	b	.L1744	@
.L1743:
	ldr	r1, [r6, #108]	@ <variable>.pstChanFrmBuf, <variable>.pstChanFrmBuf
	add	r0, r1, r4	@ tmp165, <variable>.pstChanFrmBuf, ivtmp.4996
	strb	r7, [r0, #16]	@ tmp197, <variable>.u8BufferNodeState
.L1741:
	ldr	r2, [r6, #108]	@ <variable>.pstChanFrmBuf, <variable>.pstChanFrmBuf
	add	r4, r4, #20	@ tmp202, ivtmp.4996,
	add	r5, r4, r2	@ D.50531, tmp202, <variable>.pstChanFrmBuf
	ldrb	r3, [r5, #16]	@ zero_extendqisi2	@ D.50532, <variable>.u8BufferNodeState
	cmp	r3, #255	@ D.50532,
	beq	.L1754	@,
	cmp	r3, #1	@ D.50532,
	beq	.L1759	@,
.L1755:
	ldr	r0, [r5, #8]	@, <variable>.stFrameBuffer.PhyAddr
	ldr	r1, [r5, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldr	r2, [r5, #12]	@, <variable>.stFrameBuffer.Length
	bl	MEM_DelMemRecord	@
	cmp	r0, #0	@,
	bne	.L1760	@,
.L1756:
	ldr	r1, [r6, #108]	@ <variable>.pstChanFrmBuf, <variable>.pstChanFrmBuf
	add	r0, r1, r4	@ tmp212, <variable>.pstChanFrmBuf, tmp202
	strb	r7, [r0, #16]	@ tmp197, <variable>.u8BufferNodeState
.L1754:
	add	r4, r4, #20	@ ivtmp.4996, tmp202,
	cmp	r4, #1280	@ ivtmp.4996,
	beq	.L1740	@,
.L1744:
	ldr	r5, [r6, #108]	@ <variable>.pstChanFrmBuf, <variable>.pstChanFrmBuf
	add	r5, r4, r5	@ D.50531, ivtmp.4996, <variable>.pstChanFrmBuf
	ldrb	r3, [r5, #16]	@ zero_extendqisi2	@ D.50532, <variable>.u8BufferNodeState
	cmp	r3, #255	@ D.50532,
	beq	.L1741	@,
	cmp	r3, #1	@ D.50532,
	beq	.L1767	@,
.L1742:
	ldr	r0, [r5, #8]	@, <variable>.stFrameBuffer.PhyAddr
	ldr	r1, [r5, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldr	r2, [r5, #12]	@, <variable>.stFrameBuffer.Length
	bl	MEM_DelMemRecord	@
	cmp	r0, #0	@,
	beq	.L1743	@,
	ldr	r2, [r5, #8]	@, <variable>.stFrameBuffer.PhyAddr
	movw	r1, #:lower16:.LC244	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC244	@,
	bl	dprint_vfmw	@
	b	.L1743	@
.L1760:
	ldr	r2, [r5, #8]	@, <variable>.stFrameBuffer.PhyAddr
	movw	r1, #:lower16:.LC244	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC244	@,
	bl	dprint_vfmw	@
	b	.L1756	@
.L1767:
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC243	@,
	movt	r1, #:upper16:.LC243	@,
	bl	dprint_vfmw	@
	ldr	r0, [r5, #8]	@, <variable>.stFrameBuffer.PhyAddr
	ldr	r1, [r5, #4]	@, <variable>.stFrameBuffer.VirAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1742	@
.L1759:
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC243	@,
	movt	r1, #:upper16:.LC243	@,
	bl	dprint_vfmw	@
	ldr	r0, [r5, #8]	@, <variable>.stFrameBuffer.PhyAddr
	ldr	r1, [r5, #4]	@, <variable>.stFrameBuffer.VirAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1755	@
.L1766:
	ldr	r0, [r6, #56]	@ D.50581, <variable>.stChanMem_ctx.PhyAddr
	cmp	r0, #0	@ D.50581,
	beq	.L1750	@,
	ldr	r1, [r6, #52]	@, <variable>.stChanMem_ctx.VirAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1751	@
.L1761:
	ldr	r0, [r6, #40]	@, <variable>.stChanMem_scd.PhyAddr
	ldr	r1, [r6, #36]	@, <variable>.stChanMem_scd.VirAddr
	bl	MEM_DelMemRecord	@
	ldr	ip, [r6, #80]	@ <variable>.s32SelfAllocChanMem_vdh, <variable>.s32SelfAllocChanMem_vdh
	cmp	ip, #1	@ <variable>.s32SelfAllocChanMem_vdh,
	bne	.L1746	@,
.L1762:
	ldr	r0, [r6, #24]	@ temp.5002, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, #0	@ temp.5002,
	beq	.L1746	@,
	ldr	r1, [r6, #20]	@, <variable>.stChanMem_vdh.VirAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1747	@
.L1764:
	ldr	r0, [r6, #40]	@ temp.5009, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, #0	@ temp.5009,
	beq	.L1748	@,
	ldr	r1, [r6, #36]	@, <variable>.stChanMem_scd.VirAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1749	@
	.fnend
	.size	VCTRL_FreeChanResource, .-VCTRL_FreeChanResource
	.align	2
	.global	VCTRL_UnInstallChan
	.type	VCTRL_UnInstallChan, %function
VCTRL_UnInstallChan:
	.fnstart
.LFB1562:
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
	mov	r4, r0	@ ChanID, ChanID
	bl	FSP_DisableInstance	@
	mov	r0, r4	@, ChanID
	bl	CloseUsdPool_WithMem	@
	mov	r0, #0	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	VCTRL_UnInstallChan, .-VCTRL_UnInstallChan
	.align	2
	.global	VCTRL_PartitionMemForStdUser
	.type	VCTRL_PartitionMemForStdUser, %function
VCTRL_PartitionMemForStdUser:
	.fnstart
.LFB1561:
	@ args = 4, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #52
	sub	sp, sp, #52	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r7, r2	@ MaxHeight, MaxHeight
	movw	r2, #:lower16:.LANCHOR0	@ tmp151,
	cmp	r1, #31	@ MaxWidth,
	cmpgt	r7, #31	@, MaxHeight,
	movt	r2, #:upper16:.LANCHOR0	@ tmp151,
	mov	r5, r1	@ MaxWidth, MaxWidth
	mov	r6, r0	@ ChanID, ChanID
	movgt	r1, #0	@, tmp158
	movle	r1, #1	@, tmp158
	ldr	r4, [r2, r0, asl #2]	@ pstChan, s_pstVfmwChan
	mov	sl, r3	@ MemAddr, MemAddr
	ldr	r2, [fp, #4]	@ MemSize, MemSize
	ble	.L1786	@,
	cmp	r3, #0	@ MemAddr,
	cmpne	r2, #0	@, MemSize,
	movne	r8, #0	@, tmp166
	moveq	r8, #1	@, tmp166
	beq	.L1787	@,
	sub	r9, fp, #84	@ tmp168,,
	mov	r1, #36	@,
	str	r2, [fp, #-88]	@,
	mov	r0, r9	@, tmp168
	bl	__memzero	@
	mov	r1, r9	@, tmp168
	mov	r0, r6	@, ChanID
	str	r5, [fp, #-56]	@ MaxWidth, FspInstCfg.s32DispFsWidth
	str	r5, [fp, #-72]	@ MaxWidth, FspInstCfg.s32DecFsWidth
	mov	r3, #1	@,
	str	r7, [fp, #-52]	@ MaxHeight, FspInstCfg.s32DispFsHeight
	strb	r8, [fp, #-84]	@ tmp166, FspInstCfg.s32DispLoopEnable
	strb	r8, [fp, #-82]	@ tmp166, FspInstCfg.s32RprEnable
	str	r7, [fp, #-68]	@ MaxHeight, FspInstCfg.s32DecFsHeight
	strb	r8, [fp, #-79]	@ tmp166, FspInstCfg.s32ExpectedDecFsNum
	strb	r8, [fp, #-77]	@ tmp166, FspInstCfg.s32ExpectedDispFsNum
	strb	r8, [fp, #-76]	@ tmp166, FspInstCfg.s32ExpectedPmvNum
	strb	r3, [fp, #-80]	@, FspInstCfg.s32UserDec
	bl	FSP_ConfigInstance	@
	ldr	r2, [fp, #-88]	@,
	subs	r5, r0, #0	@ D.50455,
	bne	.L1774	@,
	mov	r1, sl	@, MemAddr
	mov	r0, r6	@, ChanID
	sub	r3, fp, #48	@,,
	bl	FSP_PartitionFsMemory	@
	subs	r7, r0, #0	@ Ret,
	bne	.L1788	@,
	movw	r5, #:lower16:.LANCHOR3	@ tmp184,
	movt	r5, #:upper16:.LANCHOR3	@ tmp184,
	mov	r0, r6	@, ChanID
	ldr	r1, .L1790	@,
	bl	FSP_GetInstInfo	@
	ldrb	r1, [r5, #-1331]	@ zero_extendqisi2	@, FspInstInfo.s32DecFsNum
	sxtb	r0, r1	@ D.50465, FspInstInfo.s32DecFsNum
	cmp	r0, #16	@ D.50465,
	movge	r0, #16	@ D.50465,
	str	r0, [r4, #484]	@ D.50465, <variable>.s32UsrdecFrameNum
	cmp	r0, #2	@ D.50465,
	ble	.L1789	@,
	ldr	ip, [r5, #2516]	@ FspInstInfo.s32DecFsSize, FspInstInfo.s32DecFsSize
	add	r0, r4, #416	@, pstChan,
	mov	r1, #64	@,
	str	ip, [r4, #480]	@ FspInstInfo.s32DecFsSize, <variable>.s32UsrdecFrameSize
	bl	__memzero	@
	add	r0, r4, #352	@, pstChan,
	mov	r1, #64	@,
	bl	__memzero	@
	ldr	r5, [r4, #484]	@ D.50464, <variable>.s32UsrdecFrameNum
	cmp	r5, #0	@ D.50464,
	ble	.L1777	@,
	ldr	r3, .L1790	@ ivtmp.5070,
	mov	r2, #1	@ i,
	cmp	r2, r5	@ i, D.50464
	sub	r0, r5, #1	@ tmp203, D.50464,
	and	ip, r0, r2	@ tmp205, tmp203,
	add	r1, r4, #4	@ ivtmp.5073, pstChan,
	ldr	lr, [r3, #20]	@ <variable>.PhyAddr, <variable>.PhyAddr
	ldr	r3, .L1790+4	@ ivtmp.5070,
	str	lr, [r4, #416]	@ <variable>.PhyAddr, <variable>.s32UsrdecFramePhyAddr
	bge	.L1777	@,
	cmp	ip, #0	@ tmp205,
	beq	.L1778	@,
	ldr	lr, [r3, #20]	@ <variable>.PhyAddr, <variable>.PhyAddr
	mov	r2, #2	@ i,
	cmp	r2, r5	@ i, D.50464
	ldr	r3, .L1790+8	@ ivtmp.5070,
	str	lr, [r1, #416]	@ <variable>.PhyAddr, <variable>.s32UsrdecFramePhyAddr
	add	r1, r1, #4	@ ivtmp.5073, ivtmp.5073,
	bge	.L1777	@,
.L1778:
	ldr	r0, [r3, #20]	@ <variable>.PhyAddr, <variable>.PhyAddr
	add	r2, r2, #2	@ i, i,
	add	lr, r1, #4	@ tmp208, ivtmp.5073,
	cmp	r2, r5	@ i, D.50464
	str	r0, [r1, #416]	@ <variable>.PhyAddr, <variable>.s32UsrdecFramePhyAddr
	add	r1, lr, #4	@ ivtmp.5073, tmp208,
	ldr	ip, [r3, #80]	@ <variable>.PhyAddr, <variable>.PhyAddr
	add	r3, r3, #120	@ ivtmp.5070, ivtmp.5070,
	str	ip, [lr, #416]	@ <variable>.PhyAddr, <variable>.s32UsrdecFramePhyAddr
	blt	.L1778	@,
.L1777:
	mov	r0, #0	@ D.50443,
.L1772:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1787:
	mov	r0, r1	@, tmp158
	movw	r1, #:lower16:.LC246	@,
	movt	r1, #:upper16:.LC246	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50443,
	b	.L1772	@
.L1774:
	mov	r0, r8	@, tmp166
	movw	r1, #:lower16:.LC249	@,
	movt	r1, #:upper16:.LC249	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50443,
	b	.L1772	@
.L1788:
	mov	r0, r5	@, D.50455
	movw	r1, #:lower16:.LC247	@,
	movt	r1, #:upper16:.LC247	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50443,
	b	.L1772	@
.L1789:
	mov	r0, r7	@, Ret
	movw	r1, #:lower16:.LC248	@,
	ldr	r2, .L1790+12	@,
	movt	r1, #:upper16:.LC248	@,
	movw	r3, #1367	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50443,
	b	.L1772	@
.L1786:
	mov	r2, r5	@, MaxWidth
	mov	r3, r7	@, MaxHeight
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC245	@,
	movt	r1, #:upper16:.LC245	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50443,
	b	.L1772	@
.L1791:
	.align	2
.L1790:
	.word	.LANCHOR3-1332
	.word	.LANCHOR3-1272
	.word	.LANCHOR3-1212
	.word	.LANCHOR1+312
	.fnend
	.size	VCTRL_PartitionMemForStdUser, .-VCTRL_PartitionMemForStdUser
	.align	2
	.global	VCTRL_GetStreamInterface
	.type	VCTRL_GetStreamInterface, %function
VCTRL_GetStreamInterface:
	.fnstart
.LFB1553:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp138,
	movt	r3, #:upper16:.LANCHOR0	@ tmp138,
	mov	r5, r0	@ ChanID, ChanID
	ldr	r4, [r3, r0, asl #2]	@ D.50267, s_pstVfmwChan
	cmp	r4, #0	@ D.50267,
	beq	.L1794	@,
	add	r4, r4, #148	@ D.50270, D.50267,
	add	r0, r0, r0, asl #1	@, tmp143, ChanID, ChanID,
	add	r3, r3, #312	@ tmp140, tmp138,
	mov	r2, #12	@,
	add	r0, r3, r0, asl #2	@,, tmp140, tmp143,
	mov	r1, r4	@, D.50270
	bl	memcmp	@
	cmp	r0, #0	@,
	bne	.L1796	@,
.L1794:
	mov	r0, r4	@, D.50270
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1796:
	mov	r3, r5	@, ChanID
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC250	@,
	movw	r2, #1077	@,
	movt	r1, #:upper16:.LC250	@,
	mov	r4, r0	@ D.50270,
	bl	dprint_vfmw	@
	b	.L1794	@
	.fnend
	.size	VCTRL_GetStreamInterface, .-VCTRL_GetStreamInterface
	.align	2
	.global	VCTRL_OpenVfmw
	.type	VCTRL_OpenVfmw, %function
VCTRL_OpenVfmw:
	.fnstart
.LFB1546:
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
	sub	r5, fp, #48	@ tmp305,,
	movw	r4, #:lower16:.LANCHOR0	@ tmp303,
	movt	r4, #:upper16:.LANCHOR0	@ tmp303,
	mov	r1, #8	@,
	mov	r0, r5	@, tmp305
	bl	__memzero	@
	ldr	r8, [r4, #104]	@ s_VfmwCTrl.s32IsVCTRLOpen, s_VfmwCTrl.s32IsVCTRLOpen
	cmp	r8, #0	@ s_VfmwCTrl.s32IsVCTRLOpen,
	beq	.L1821	@,
.L1798:
	mvn	r0, #0	@ D.50144,
.L1819:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L1821:
	movw	r6, #:lower16:.LANCHOR3	@ tmp304,
	movw	r7, #:lower16:saved_command_line	@ tmp302,
	movt	r6, #:upper16:.LANCHOR3	@ tmp304,
	movt	r7, #:upper16:saved_command_line	@ tmp302,
	add	r1, r6, #2512	@, tmp304,
	mov	r2, #1024	@,
	add	r0, r1, #8	@,,
	ldr	r1, [r7, #0]	@, saved_command_line
	str	r8, [fp, #-40]	@ s_VfmwCTrl.s32IsVCTRLOpen, p
	bl	strlcpy	@
	add	r0, r6, #2512	@, tmp304,
	movw	r1, #:lower16:.LC251	@,
	add	r0, r0, #8	@,,
	movt	r1, #:upper16:.LC251	@,
	bl	strstr	@
	cmp	r0, #0	@ tmp173,
	str	r0, [fp, #-40]	@ tmp173, p
	beq	.L1799	@,
	sub	sl, fp, #40	@ p.704,,
	movw	r1, #:lower16:.LC252	@,
	movt	r1, #:upper16:.LC252	@,
	mov	r0, sl	@, p.704
	bl	strsep	@
	subs	r3, r0, #0	@ D.60559,
	beq	.L1804	@,
	mov	r0, sl	@, p.704
	movw	r1, #:lower16:.LC121	@,
	movt	r1, #:upper16:.LC121	@,
	bl	strsep	@
	cmp	r0, #0	@,
	beq	.L1822	@,
	mov	r1, r8	@, s_VfmwCTrl.s32IsVCTRLOpen
	mov	r2, r8	@, tmp1
	bl	simple_strtol	@
	str	r0, [r4, #68]	@ prephitmp.5172, extra_ref
.L1803:
	add	r8, r0, #4992	@ tmp184, prephitmp.5172,
	movw	r2, #10000	@ tmp186,
	add	r3, r8, #8	@ tmp184, tmp184,
	cmp	r3, r2	@ tmp184, tmp186
	bhi	.L1805	@,
	movw	ip, #5000	@ tmp187,
	movw	sl, #:lower16:-5000	@ tmp188,
	cmp	r0, ip	@ prephitmp.5172, tmp187
	movge	r0, ip	@ pretmp.5169, tmp187
	movt	sl, #:upper16:-5000	@ tmp188,
	cmp	r0, sl	@ pretmp.5169, tmp188
	movge	r3, r0	@ prephitmp.5171, pretmp.5169
	movlt	r3, sl	@ prephitmp.5171, tmp188
.L1804:
	str	r3, [r4, #68]	@ prephitmp.5171, extra_ref
.L1802:
	ldr	r1, [r7, #0]	@, saved_command_line
	mov	r2, #1024	@,
	ldr	r0, .L1825	@,
	mov	r8, #0	@ tmp194,
	str	r8, [fp, #-40]	@ tmp194, p
	bl	strlcpy	@
	ldr	r0, .L1825	@,
	movw	r1, #:lower16:.LC254	@,
	movt	r1, #:upper16:.LC254	@,
	bl	strstr	@
	cmp	r0, r8	@ tmp198,
	str	r0, [fp, #-40]	@ tmp198, p
	beq	.L1806	@,
	sub	sl, fp, #40	@ p.715,,
	movw	r1, #:lower16:.LC252	@,
	movt	r1, #:upper16:.LC252	@,
	mov	r0, sl	@, p.715
	bl	strsep	@
	subs	r3, r0, #0	@ D.60579,
	beq	.L1811	@,
	mov	r0, sl	@, p.715
	movw	r1, #:lower16:.LC121	@,
	movt	r1, #:upper16:.LC121	@,
	bl	strsep	@
	cmp	r0, r8	@,
	beq	.L1823	@,
	mov	r1, r8	@, tmp194
	mov	r2, r8	@, tmp1
	bl	simple_strtol	@
	str	r0, [r4, #72]	@ prephitmp.5167, extra_disp
.L1810:
	add	sl, r0, #4992	@ tmp209, prephitmp.5167,
	movw	lr, #10000	@ tmp211,
	add	r8, sl, #8	@ tmp209, tmp209,
	cmp	r8, lr	@ tmp209, tmp211
	bhi	.L1812	@,
	movw	r2, #5000	@ tmp212,
	movw	ip, #:lower16:-5000	@ tmp213,
	cmp	r0, r2	@ prephitmp.5167, tmp212
	movge	r0, r2	@ pretmp.5139, tmp212
	movt	ip, #:upper16:-5000	@ tmp213,
	cmp	r0, ip	@ pretmp.5139, tmp213
	movge	r3, r0	@ prephitmp.5140, pretmp.5139
	movlt	r3, ip	@ prephitmp.5140, tmp213
.L1811:
	str	r3, [r4, #72]	@ prephitmp.5140, extra_disp
.L1809:
	ldr	r8, [r4, #1368]	@ extra_cmd.721, extra_cmd
	mov	lr, #0	@ tmp219,
	movw	sl, #:lower16:.LANCHOR0	@ tmp220,
	str	lr, [fp, #-40]	@ tmp219, p
	cmp	r8, lr	@ extra_cmd.721,
	movt	sl, #:upper16:.LANCHOR0	@ tmp220,
	beq	.L1813	@,
	movw	r0, #:lower16:.LANCHOR2	@ tmp225,
	movt	r0, #:upper16:.LANCHOR2	@ tmp225,
	ubfx	r3, r8, #3, #1	@ tmp238, extra_cmd.721,,
	and	r2, r8, #1	@ tmp223, extra_cmd.721,
	ubfx	ip, r8, #1, #1	@ tmp228, extra_cmd.721,,
	strb	r3, [r6, #3546]	@ tmp238, g_apple_airplay_mirrorinig_flag
	ubfx	r8, r8, #2, #1	@ tmp233, extra_cmd.721,,
	strb	r2, [r6, #3544]	@ tmp223, g_allow_B_before_P
	strb	ip, [r0, #64]	@ tmp228, g_not_direct_8x8_inference_flag
	strb	r8, [r6, #3545]	@ tmp233, g_not_allow_H264FullPictureRepair_flag
.L1814:
	movw	r6, #:lower16:.LANCHOR0	@ tmp271,
	movt	r6, #:upper16:.LANCHOR0	@ tmp271,
	mov	r1, #208	@,
	add	r0, r6, #104	@, tmp271,
	bl	__memzero	@
	mov	r0, r6	@, tmp271
	mov	r1, #64	@,
	bl	__memzero	@
	mov	r0, r5	@, tmp305
	movw	r2, #:lower16:VCTRL_EventReport	@ tmp275,
	movt	r2, #:upper16:VCTRL_EventReport	@ tmp275,
	str	r2, [r4, #64]	@ tmp275, g_event_report
	mov	ip, #134217728	@ tmp276,
	mov	r1, #75497472	@ tmp277,
	str	ip, [fp, #-48]	@ tmp276, MemInit.MemBaseAddr
	str	r1, [fp, #-44]	@ tmp277, MemInit.MemSize
	bl	MEM_InitMemManager	@
	bl	FSP_Init	@
	bl	ChanCtx_Init	@
	ldr	r0, .L1825+4	@,
	mov	r1, #64	@,
	bl	__memzero	@
	add	r0, r6, #160	@, tmp271,
	bl	OpenDrivers	@
	cmp	r0, #0	@,
	bne	.L1798	@,
	bl	DBG_CreateTracer	@
	mov	r1, #1	@,
	ldr	r0, .L1825+8	@,
	bl	OSAL_InitEvent	@
	add	r0, r6, #148	@, tmp271,
	movw	r1, #:lower16:.LC257	@,
	movw	r2, #:lower16:VFMW_CTRL_thread_proc	@,
	movt	r1, #:upper16:.LC257	@,
	movt	r2, #:upper16:VFMW_CTRL_thread_proc	@,
	bl	OSAL_CreateTask	@
	subs	r4, r0, #0	@ D.50164,
	bne	.L1818	@,
	add	r0, r6, #148	@, tmp271,
	bl	OSAL_WakeupTask	@
	mov	r3, #1	@ tmp297,
	mov	r0, r4	@ D.50144, D.50164
	str	r3, [r6, #104]	@ tmp297, s_VfmwCTrl.s32IsVCTRLOpen
	b	.L1819	@
.L1813:
	ldr	r1, [r7, #0]	@, saved_command_line
	mov	r2, #1024	@,
	ldr	r0, .L1825	@,
	bl	strlcpy	@
	ldr	r0, .L1825	@,
	movw	r1, #:lower16:.LC256	@,
	movt	r1, #:upper16:.LC256	@,
	bl	strstr	@
	cmp	r0, #0	@ tmp243,
	str	r0, [fp, #-40]	@ tmp243, p
	beq	.L1814	@,
	sub	r7, fp, #40	@ p.731,,
	movw	r1, #:lower16:.LC252	@,
	movt	r1, #:upper16:.LC252	@,
	mov	r0, r7	@, p.731
	bl	strsep	@
	cmp	r0, #0	@,
	ldreq	r0, [sl, #1368]	@ prephitmp.5138, extra_cmd
	beq	.L1816	@,
	mov	r0, r7	@, p.731
	movw	r1, #:lower16:.LC121	@,
	movt	r1, #:upper16:.LC121	@,
	bl	strsep	@
	cmp	r0, #0	@,
	beq	.L1824	@,
	mov	r1, r8	@, extra_cmd.721
	mov	r2, r8	@, tmp1
	bl	simple_strtol	@
	str	r0, [sl, #1368]	@ prephitmp.5138, extra_cmd
.L1816:
	movw	ip, #:lower16:.LANCHOR2	@ tmp256,
	movt	ip, #:upper16:.LANCHOR2	@ tmp256,
	ubfx	r3, r0, #3, #1	@ tmp269, prephitmp.5138,,
	and	r2, r0, #1	@ tmp254, prephitmp.5138,
	ubfx	lr, r0, #1, #1	@ tmp259, prephitmp.5138,,
	ubfx	r1, r0, #2, #1	@ tmp264, prephitmp.5138,,
	strb	r3, [r6, #3546]	@ tmp269, g_apple_airplay_mirrorinig_flag
	strb	r2, [r6, #3544]	@ tmp254, g_allow_B_before_P
	strb	lr, [ip, #64]	@ tmp259, g_not_direct_8x8_inference_flag
	strb	r1, [r6, #3545]	@ tmp264, g_not_allow_H264FullPictureRepair_flag
	b	.L1814	@
.L1806:
	ldr	r0, [r4, #72]	@ prephitmp.5167, extra_disp
	b	.L1810	@
.L1799:
	ldr	r0, [r4, #68]	@ prephitmp.5172, extra_ref
	b	.L1803	@
.L1805:
	mov	r2, r0	@, prephitmp.5172
	movw	r1, #:lower16:.LC253	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC253	@,
	bl	dprint_vfmw	@
	ldr	r1, [r4, #68]	@ pretmp.5168, extra_ref
	movw	r3, #5000	@ tmp191,
	movw	r0, #:lower16:-5000	@ tmp192,
	cmp	r1, r3	@ pretmp.5168, tmp191
	movlt	r2, r1	@ prephitmp.5171, pretmp.5168
	movge	r2, r3	@ prephitmp.5171, tmp191
	movt	r0, #:upper16:-5000	@ tmp192,
	cmp	r2, r0	@ prephitmp.5171, tmp192
	movge	r3, r2	@ prephitmp.5171, prephitmp.5171
	movlt	r3, r0	@ prephitmp.5171, tmp192
	b	.L1804	@
.L1812:
	mov	r2, r0	@, prephitmp.5167
	movw	r1, #:lower16:.LC255	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC255	@,
	bl	dprint_vfmw	@
	ldr	r1, [r4, #72]	@ pretmp.5152, extra_disp
	movw	r3, #5000	@ tmp216,
	movw	r0, #:lower16:-5000	@ tmp217,
	cmp	r1, r3	@ pretmp.5152, tmp216
	movlt	r8, r1	@ prephitmp.5140, pretmp.5152
	movge	r8, r3	@ prephitmp.5140, tmp216
	movt	r0, #:upper16:-5000	@ tmp217,
	cmp	r8, r0	@ prephitmp.5140, tmp217
	movge	r3, r8	@ prephitmp.5140, prephitmp.5140
	movlt	r3, r0	@ prephitmp.5140, tmp217
	b	.L1811	@
.L1822:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L1825+12	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #7767	@,
	add	r0, r0, #22	@,,
	bl	dprint_vfmw	@
	b	.L1802	@
.L1823:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L1825+16	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #7802	@,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	b	.L1809	@
.L1824:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L1825+20	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #7848	@,
	add	r0, r0, #22	@,,
	bl	dprint_vfmw	@
	b	.L1814	@
.L1818:
	add	r0, r6, #160	@, tmp271,
	bl	CloseDrivers	@
	mvn	r0, #0	@ D.50144,
	b	.L1819	@
.L1826:
	.align	2
.L1825:
	.word	.LANCHOR3+2520
	.word	.LANCHOR3-1460
	.word	.LANCHOR3+3548
	.word	.LANCHOR1+344
	.word	.LANCHOR1+364
	.word	.LANCHOR1+384
	.fnend
	.size	VCTRL_OpenVfmw, .-VCTRL_OpenVfmw
	.align	2
	.global	VCTRL_ExtraWakeUpThread
	.type	VCTRL_ExtraWakeUpThread, %function
VCTRL_ExtraWakeUpThread:
	.fnstart
.LFB1542:
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
	ldr	r0, .L1829	@,
	bl	OSAL_GiveEvent	@
	ldmfd	sp, {fp, sp, pc}	@
.L1830:
	.align	2
.L1829:
	.word	.LANCHOR3+3548
	.fnend
	.size	VCTRL_ExtraWakeUpThread, .-VCTRL_ExtraWakeUpThread
	.align	2
	.global	VCTRL_ExtAccGetDecParam
	.type	VCTRL_ExtAccGetDecParam, %function
VCTRL_ExtAccGetDecParam:
	.fnstart
.LFB1622:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #28
	sub	sp, sp, #28	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r4, #:lower16:.LANCHOR0	@ tmp241,
	movt	r4, #:upper16:.LANCHOR0	@ tmp241,
	mov	r6, r0	@ pDecParamInfo, pDecParamInfo
	add	r0, r4, #520	@, tmp241,
	movw	r7, #:lower16:.LANCHOR3	@ tmp242,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, .L1879	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r8, [r6, #0]	@ D.53828, <variable>.ChanID
	movt	r7, #:upper16:.LANCHOR3	@ tmp242,
	cmn	r8, #1	@ D.53828,
	beq	.L1870	@,
	cmp	r8, #15	@ D.53828,
	bls	.L1871	@,
.L1842:
	mov	r3, r8	@, D.53828
	ldr	r2, .L1879+4	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC261	@,
	movt	r1, #:upper16:.LC261	@,
	bl	dprint_vfmw	@
	mov	r3, #0	@ tmp188,
	str	r3, [r6, #8]	@ tmp188, <variable>.pDecParam
.L1833:
	ldr	r0, .L1879	@,
	bl	OSAL_SpinUnLockIRQ	@
	ldr	r0, .L1879+8	@,
	bl	OSAL_SpinUnLockIRQ	@
	mvn	r0, #0	@ D.53863,
.L1840:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1871:
	ldr	r3, [r4, r8, asl #2]	@ D.56253, s_pstVfmwChan
	cmp	r3, #0	@ D.56253,
	beq	.L1842	@,
	ldr	r1, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r1, #0	@ <variable>.s32IsOpen,
	beq	.L1842	@,
	ldr	r0, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L1842	@,
	ldr	r2, [r3, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r2, #0	@ <variable>.s32Priority,
	beq	.L1842	@,
	ldr	ip, [r3, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	ip, #19	@ <variable>.eVidStd,
	beq	.L1842	@,
	mov	r0, r8	@, D.53828
	bl	VDMDRV_IsChanDec	@
	cmp	r0, #1	@,
	beq	.L1872	@,
	mov	r0, r8	@, D.53828
	bl	VCTRL_GetDecParam	@
	subs	r5, r0, #0	@ pDecParam.5245,
	beq	.L1873	@,
	ldr	r3, [r4, r8, asl #2]	@ temp.5247, s_pstVfmwChan
	cmp	r3, #0	@ temp.5247,
	beq	.L1874	@,
	str	r8, [fp, #-56]	@ D.53828, DecParamInfo.ChanID
	sub	r0, fp, #56	@,,
	ldr	lr, [r3, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	ip, [r7, #3564]	@ AcceleratorCharacter, AcceleratorCharacter
	str	r5, [fp, #-48]	@ pDecParam.5245, DecParamInfo.pDecParam
	str	lr, [fp, #-52]	@ <variable>.eVidStd, DecParamInfo.VidStd
	blx	ip	@ AcceleratorCharacter
	cmp	r0, #1	@,
	bne	.L1846	@,
	mov	r0, r8	@, D.53828
.L1868:
	ldr	ip, [fp, #-56]	@ DecParamInfo.ChanID, DecParamInfo.ChanID
	mov	r1, #4	@,
	ldr	r3, [fp, #-52]	@ DecParamInfo.VidStd, DecParamInfo.VidStd
	ldr	r2, [fp, #-48]	@ DecParamInfo.pDecParam, DecParamInfo.pDecParam
	str	ip, [r6, #0]	@ DecParamInfo.ChanID, <variable>.ChanID
	str	r3, [r6, #4]	@ DecParamInfo.VidStd, <variable>.VidStd
	str	r2, [r6, #8]	@ DecParamInfo.pDecParam, <variable>.pDecParam
	bl	VDMDRV_SetChanIsDec	@
	ldr	r0, .L1879	@,
	bl	OSAL_SpinUnLockIRQ	@
	ldr	r0, .L1879+8	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, #0	@ D.53863,
	b	.L1840	@
.L1870:
	movw	r5, #:lower16:g_ChanCtx	@ ivtmp.5242,
	movt	r5, #:upper16:g_ChanCtx	@ ivtmp.5242,
	add	r8, r5, #64	@ D.60762, ivtmp.5242,
	sub	r9, fp, #56	@ tmp248,,
	mov	sl, r4	@ tmp247, tmp241
.L1841:
	ldr	r3, [r5, #64]	@ D.53834,
	cmp	r3, #0	@ D.53834,
	blt	.L1833	@,
	cmp	r3, #15	@ D.53834,
	bhi	.L1834	@,
	ldr	r2, [r4, r3, asl #2]	@ D.56244, s_pstVfmwChan
	cmp	r2, #0	@ D.56244,
	beq	.L1834	@,
	ldr	r1, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r1, #0	@ <variable>.s32IsOpen,
	beq	.L1834	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	bne	.L1875	@,
.L1834:
	movw	r1, #:lower16:.LC258	@,
	ldr	r2, .L1879+4	@,
	movt	r1, #:upper16:.LC258	@,
	mov	r0, #1	@,
	bl	dprint_vfmw	@
.L1836:
	add	r5, r5, #4	@ tmp253, ivtmp.5242,
	ldr	r3, [r5, #64]	@ D.53834,
	cmp	r3, #0	@ D.53834,
	blt	.L1833	@,
	cmp	r3, #15	@ D.53834,
	bls	.L1863	@,
.L1853:
	movw	r1, #:lower16:.LC258	@,
	ldr	r2, .L1879+4	@,
	movt	r1, #:upper16:.LC258	@,
	mov	r0, #1	@,
	bl	dprint_vfmw	@
.L1864:
	add	r5, r5, #4	@ ivtmp.5242, tmp253,
	cmp	r5, r8	@ ivtmp.5242, D.60762
	bne	.L1841	@,
	b	.L1833	@
.L1863:
	ldr	r2, [r4, r3, asl #2]	@ D.56244, s_pstVfmwChan
	cmp	r2, #0	@ D.56244,
	beq	.L1853	@,
	ldr	r0, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r0, #0	@ <variable>.s32IsOpen,
	beq	.L1853	@,
	ldr	lr, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	lr, #0	@ <variable>.s32IsRun,
	beq	.L1853	@,
	ldr	ip, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	ip, #0	@ <variable>.s32Priority,
	beq	.L1853	@,
	ldr	r2, [r2, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, #19	@ <variable>.eVidStd,
	beq	.L1853	@,
	mov	r0, r3	@, D.53834
	str	r3, [fp, #-64]	@,
	bl	VDMDRV_IsChanDec	@
	ldr	r3, [fp, #-64]	@,
	cmp	r0, #1	@,
	beq	.L1855	@,
	mov	r0, r3	@, D.53834
	bl	VCTRL_GetDecParam	@
	ldr	r3, [fp, #-64]	@,
	subs	r2, r0, #0	@ pDecParam,
	beq	.L1865	@,
	ldr	r1, [sl, r3, asl #2]	@ D.53853, s_pstVfmwChan
	cmp	r1, #0	@ D.53853,
	beq	.L1866	@,
	str	r3, [fp, #-56]	@ D.53834, DecParamInfo.ChanID
	mov	r0, r9	@, tmp248
	ldr	r1, [r1, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	r3, [r7, #3564]	@ AcceleratorCharacter, AcceleratorCharacter
	str	r2, [fp, #-48]	@ pDecParam, DecParamInfo.pDecParam
	str	r1, [fp, #-52]	@ <variable>.eVidStd, DecParamInfo.VidStd
	blx	r3	@ AcceleratorCharacter
	ldr	r3, [fp, #-64]	@,
	cmp	r0, #1	@,
	beq	.L1867	@,
	mov	r0, #0	@,
	str	r0, [r6, #8]	@, <variable>.pDecParam
	b	.L1864	@
.L1875:
	ldr	ip, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	ip, #0	@ <variable>.s32Priority,
	beq	.L1834	@,
	ldr	r2, [r2, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, #19	@ <variable>.eVidStd,
	beq	.L1834	@,
	mov	r0, r3	@, D.53834
	str	r3, [fp, #-64]	@,
	bl	VDMDRV_IsChanDec	@
	ldr	r3, [fp, #-64]	@,
	cmp	r0, #1	@,
	beq	.L1876	@,
	mov	r0, r3	@, D.53834
	str	r3, [fp, #-64]	@,
	bl	VCTRL_GetDecParam	@
	ldr	r3, [fp, #-64]	@,
	subs	r2, r0, #0	@ pDecParam,
	beq	.L1877	@,
	ldr	r1, [sl, r3, asl #2]	@ D.53853, s_pstVfmwChan
	cmp	r1, #0	@ D.53853,
	beq	.L1878	@,
	str	r3, [fp, #-56]	@ D.53834, DecParamInfo.ChanID
	mov	r0, r9	@, tmp248
	ldr	lr, [r1, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	ip, [r7, #3564]	@ AcceleratorCharacter, AcceleratorCharacter
	str	r3, [fp, #-64]	@,
	str	r2, [fp, #-48]	@ pDecParam, DecParamInfo.pDecParam
	str	lr, [fp, #-52]	@ <variable>.eVidStd, DecParamInfo.VidStd
	blx	ip	@ AcceleratorCharacter
	ldr	r3, [fp, #-64]	@,
	cmp	r0, #1	@,
	beq	.L1867	@,
	mov	r3, #0	@,
	str	r3, [r6, #8]	@, <variable>.pDecParam
	b	.L1836	@
.L1878:
	movw	r1, #:lower16:.LC55	@,
	movw	r2, #7581	@,
	movt	r1, #:upper16:.LC55	@,
	mov	r0, #1	@,
	bl	dprint_vfmw	@
	b	.L1836	@
.L1866:
	movw	r1, #:lower16:.LC55	@,
	movw	r2, #7581	@,
	movt	r1, #:upper16:.LC55	@,
	mov	r0, #1	@,
	bl	dprint_vfmw	@
	b	.L1864	@
.L1876:
	mov	r2, r3	@, D.53834
	movw	r1, #:lower16:.LC259	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC259	@,
	bl	dprint_vfmw	@
	b	.L1836	@
.L1855:
	mov	r2, r3	@, D.53834
	movw	r1, #:lower16:.LC259	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC259	@,
	bl	dprint_vfmw	@
	b	.L1864	@
.L1846:
	mov	r1, #0	@ tmp228,
	str	r1, [r6, #8]	@ tmp228, <variable>.pDecParam
	b	.L1833	@
.L1867:
	mov	r0, r3	@, D.53834
	b	.L1868	@
.L1877:
	mov	r2, r3	@, D.53834
	movw	r1, #:lower16:.LC260	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC260	@,
	bl	dprint_vfmw	@
	b	.L1836	@
.L1865:
	mov	r2, r3	@, D.53834
	movw	r1, #:lower16:.LC260	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC260	@,
	bl	dprint_vfmw	@
	b	.L1864	@
.L1874:
	mov	r3, r8	@, D.53828
	movw	r2, #7642	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC55	@,
	movt	r1, #:upper16:.LC55	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ tmp210,
	str	r0, [r6, #8]	@ tmp210, <variable>.pDecParam
	b	.L1833	@
.L1872:
	mov	r2, r8	@, D.53828
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC259	@,
	movt	r1, #:upper16:.LC259	@,
	bl	dprint_vfmw	@
	mov	r1, #0	@ tmp195,
	str	r1, [r6, #8]	@ tmp195, <variable>.pDecParam
.L1869:
	ldr	r0, .L1879	@,
	bl	OSAL_SpinUnLockIRQ	@
	add	r0, r4, #520	@, tmp241,
	bl	OSAL_SpinUnLockIRQ	@
	mvn	r0, #0	@ D.53863,
	b	.L1840	@
.L1873:
	bl	VCTRL_ExtraWakeUpThread	@
	mov	r2, r8	@, D.53828
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC260	@,
	movt	r1, #:upper16:.LC260	@,
	bl	dprint_vfmw	@
	str	r5, [r6, #8]	@ pDecParam.5245, <variable>.pDecParam
	b	.L1869	@
.L1880:
	.align	2
.L1879:
	.word	.LANCHOR3-1732
	.word	.LANCHOR1+400
	.word	.LANCHOR0+520
	.fnend
	.size	VCTRL_ExtAccGetDecParam, .-VCTRL_ExtAccGetDecParam
	.align	2
	.global	VCTRL_InformVdmFree
	.type	VCTRL_InformVdmFree, %function
VCTRL_InformVdmFree:
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
	movw	r4, #:lower16:.LANCHOR3	@ tmp143,
	bl	OSAL_GetTimeInMs	@
	movt	r4, #:upper16:.LANCHOR3	@ tmp143,
	ldr	r3, [r4, #3568]	@ LastEventTime.461, LastEventTime
	cmp	r0, r3	@ CurTime, LastEventTime.461
	mov	r5, r0	@ CurTime,
	strls	r0, [r4, #3568]	@ CurTime, LastEventTime
	bhi	.L1886	@,
.L1883:
	ldr	r0, .L1887	@,
	bl	OSAL_GiveEvent	@
	str	r5, [r4, #3568]	@ CurTime, LastEventTime
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1886:
	rsb	r3, r3, r0	@ tmp137, LastEventTime.461, CurTime
	cmp	r3, #9	@ tmp137,
	ldmlsfd	sp, {r4, r5, fp, sp, pc}	@
	b	.L1883	@
.L1888:
	.align	2
.L1887:
	.word	.LANCHOR3+3548
	.fnend
	.size	VCTRL_InformVdmFree, .-VCTRL_InformVdmFree
	.align	2
	.global	VCTRL_Scd_Isr_2
	.type	VCTRL_Scd_Isr_2, %function
VCTRL_Scd_Isr_2:
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
	mov	r0, #2	@,
	bl	SM_SCDIntServeProc	@
	mov	r0, #1	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_Scd_Isr_2, .-VCTRL_Scd_Isr_2
	.align	2
	.global	VCTRL_Scd_Isr_1
	.type	VCTRL_Scd_Isr_1, %function
VCTRL_Scd_Isr_1:
	.fnstart
.LFB1539:
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
	mov	r0, #1	@,
	bl	SM_SCDIntServeProc	@
	mov	r0, #1	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_Scd_Isr_1, .-VCTRL_Scd_Isr_1
	.align	2
	.global	VCTRL_Scd_Isr
	.type	VCTRL_Scd_Isr, %function
VCTRL_Scd_Isr:
	.fnstart
.LFB1538:
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
	bl	SM_SCDIntServeProc	@
	mov	r0, #1	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_Scd_Isr, .-VCTRL_Scd_Isr
	.align	2
	.global	VCTRL_Isr_2
	.type	VCTRL_Isr_2, %function
VCTRL_Isr_2:
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
	mov	r0, #2	@,
	bl	VDMDRV_VdmIntServProc	@
	mov	r0, #1	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_Isr_2, .-VCTRL_Isr_2
	.align	2
	.global	VCTRL_Isr_1
	.type	VCTRL_Isr_1, %function
VCTRL_Isr_1:
	.fnstart
.LFB1536:
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
	mov	r0, #1	@,
	bl	VDMDRV_VdmIntServProc	@
	mov	r0, #1	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_Isr_1, .-VCTRL_Isr_1
	.align	2
	.global	VCTRL_Isr_0
	.type	VCTRL_Isr_0, %function
VCTRL_Isr_0:
	.fnstart
.LFB1535:
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
	bl	VDMDRV_VdmIntServProc	@
	mov	r0, #1	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_Isr_0, .-VCTRL_Isr_0
	.align	2
	.global	VCTRL_Resume
	.type	VCTRL_Resume, %function
VCTRL_Resume:
	.fnstart
.LFB1531:
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
	bl	OSAL_GetTimeInMs	@
	mov	r4, r0	@ EntrTime,
	mov	r0, #0	@,
	bl	SCDDRV_ExitSleep	@
	mov	r0, #0	@,
	bl	VDMDRV_ExitSleep	@
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp138,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp138,
	ldr	r3, [r3, #24]	@ D.49909, g_vdm_hal_fun_ptr.pfun_BPDDRV_OpenHardware
	cmp	r3, #0	@ D.49909,
	beq	.L1902	@,
	blx	r3	@ D.49909
.L1902:
	bl	VCTRL_StartTask	@
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:.LC262	@,
	movt	r1, #:upper16:.LC262	@,
	cmp	r4, r0	@ EntrTime, CurTime
	rsbls	r2, r4, r0	@ iftmp.453, EntrTime, CurTime
	mvnhi	r4, r4	@ tmp139, EntrTime
	addhi	r2, r0, r4	@ iftmp.453, CurTime, tmp139
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	VCTRL_Resume, .-VCTRL_Resume
	.align	2
	.global	VCTRL_Suspend
	.type	VCTRL_Suspend, %function
VCTRL_Suspend:
	.fnstart
.LFB1530:
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
	bl	OSAL_GetTimeInMs	@
	mov	r4, r0	@ EntrTime,
	bl	VDM_ResetClock	@
	mov	r0, #0	@,
	bl	SCDDRV_PrepareSleep	@
	mov	r0, #0	@,
	bl	VDMDRV_PrepareSleep	@
	bl	OSAL_GetTimeInMs	@
	mov	r9, r0	@ BeginTime,
	mov	r0, #0	@,
	bl	SCDDRV_GetSleepStage	@
	cmp	r0, #2	@,
	movne	r6, #0	@, isScdSleep
	moveq	r6, #1	@, isScdSleep
	mov	r0, #0	@,
	bl	VDMDRV_GetSleepStage	@
	cmp	r0, #2	@,
	movne	r5, #0	@, isVdmSleep
	moveq	r5, #1	@, isVdmSleep
	tst	r5, r6	@ isVdmSleep, isScdSleep
	bne	.L1911	@,
	mov	r0, #10	@,
	bl	msleep	@
	cmp	r6, #1	@ isScdSleep,
	cmpeq	r5, #1	@, isVdmSleep,
	movne	r8, #1	@ SleepCount,
	beq	.L1911	@,
.L1916:
	mov	r0, #0	@,
	add	sl, r8, #1	@ tmp174, SleepCount,
	bl	SCDDRV_GetSleepStage	@
	cmp	r0, #2	@,
	mov	r0, #0	@,
	moveq	r6, #1	@ isScdSleep,
	bl	VDMDRV_GetSleepStage	@
	cmp	r0, #2	@,
	mov	r0, #10	@,
	moveq	r5, #1	@ isVdmSleep,
	and	r7, r5, r6	@ tmp182, isVdmSleep, isScdSleep
	uxtb	r7, r7	@ tmp183, tmp182
	cmp	r7, #0	@ tmp183,
	bne	.L1911	@,
	cmp	r8, #31	@ SleepCount,
	add	r8, sl, #1	@ SleepCount, tmp174,
	beq	.L1929	@,
	bl	msleep	@
	cmp	r6, #1	@ isScdSleep,
	cmpeq	r5, #1	@, isVdmSleep,
	mov	r0, r7	@, tmp183
	beq	.L1911	@,
	bl	SCDDRV_GetSleepStage	@
	cmp	r0, #2	@,
	mov	r0, r7	@, tmp183
	moveq	r6, #1	@ isScdSleep,
	bl	VDMDRV_GetSleepStage	@
	cmp	r0, #2	@,
	mov	r0, #10	@,
	moveq	r5, #1	@ isVdmSleep,
	and	r3, r5, r6	@ tmp189, isVdmSleep, isScdSleep
	tst	r3, #255	@ tmp189
	bne	.L1911	@,
	bl	msleep	@
	cmp	r6, #1	@ isScdSleep,
	cmpeq	r5, #1	@, isVdmSleep,
	bne	.L1916	@,
.L1911:
	movw	r5, #:lower16:g_vdm_hal_fun_ptr	@ tmp171,
	movt	r5, #:upper16:g_vdm_hal_fun_ptr	@ tmp171,
	ldr	r3, [r5, #20]	@ D.49873, g_vdm_hal_fun_ptr.pfun_SCDDRV_CloseHardware
	cmp	r3, #0	@ D.49873,
	beq	.L1917	@,
	mov	r0, #0	@,
	blx	r3	@ D.49873
.L1918:
	ldr	r3, [r5, #28]	@ D.49879, g_vdm_hal_fun_ptr.pfun_BPDDRV_CloseHardware
	cmp	r3, #0	@ D.49879,
	beq	.L1919	@,
	blx	r3	@ D.49879
.L1919:
	ldr	r3, [r5, #4]	@ D.49884, g_vdm_hal_fun_ptr.pfun_VDMDRV_CloseHardware
	cmp	r3, #0	@ D.49884,
	beq	.L1920	@,
	mov	r0, #0	@,
	blx	r3	@ D.49884
.L1921:
	bl	VCTRL_StopTask	@
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:.LC266	@,
	movt	r1, #:upper16:.LC266	@,
	cmp	r4, r0	@ EntrTime, CurTime.5469
	rsbls	r2, r4, r0	@ iftmp.449, EntrTime, CurTime.5469
	mvnhi	r2, r4	@ tmp169, EntrTime
	addhi	r2, r0, r2	@ iftmp.449, CurTime.5469, tmp169
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1917:
	mov	r0, r3	@, D.49873
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #385	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L1918	@
.L1920:
	mov	r0, r3	@, D.49884
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #390	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L1921	@
.L1929:
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:.LC263	@,
	mov	r3, r6	@, isScdSleep
	movt	r1, #:upper16:.LC263	@,
	str	r5, [sp, #0]	@ isVdmSleep,
	cmp	r9, r0	@ BeginTime, CurTime
	rsbls	r2, r9, r0	@ iftmp.446, BeginTime, CurTime
	mvnhi	r2, r9	@ tmp153, BeginTime
	addhi	r2, r0, r2	@ iftmp.446, CurTime, tmp153
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	cmp	r6, #1	@ isScdSleep,
	beq	.L1915	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC264	@,
	mov	r2, r0	@,
	movt	r1, #:upper16:.LC264	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@,
	bl	SCDDRV_ForceSleep	@
.L1915:
	cmp	r5, #1	@ isVdmSleep,
	beq	.L1911	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC265	@,
	mov	r2, r0	@,
	movt	r1, #:upper16:.LC265	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@,
	bl	VDMDRV_ForceSleep	@
	b	.L1911	@
	.fnend
	.size	VCTRL_Suspend, .-VCTRL_Suspend
	.align	2
	.global	VCTRL_SetDbgOption
	.type	VCTRL_SetDbgOption, %function
VCTRL_SetDbgOption:
	.fnstart
.LFB1628:
	@ args = 0, pretend = 0, frame = 400
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #412
	sub	sp, sp, #412	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r1, #0	@ p_args
	bne	.L2005	@,
.L1931:
	mvn	r0, #1	@ D.54110,
.L1978:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L2005:
	cmp	r0, #516	@ opt,
	ldr	r4, [r1, #0]	@ dat,* p_args
	beq	.L1947	@,
	bhi	.L1967	@,
	cmp	r0, #8	@ opt,
	beq	.L1933	@,
	bhi	.L1968	@,
	cmp	r0, #3	@ opt,
	beq	.L1933	@,
	bhi	.L1969	@,
	cmp	r0, #1	@ opt,
	beq	.L1933	@,
	bls	.L2006	@,
	bic	r5, r4, #-16777216	@ Thr, dat,
	mov	r4, r4, lsr #24	@ ChanID, dat,
	sub	r6, fp, #144	@ tmp483,,
	mov	r0, #32	@,
	mov	r2, r4	@, ChanID
	mov	r3, r5	@, Thr
	movw	r1, #:lower16:.LC267	@,
	movt	r1, #:upper16:.LC267	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp483
	bl	VCTRL_GetChanCfg	@
	cmp	r0, #0	@,
	beq	.L2007	@,
.L1933:
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1967:
	cmp	r0, #1280	@ opt,
	beq	.L1957	@,
	bhi	.L1973	@,
	movw	r3, #898	@ tmp196,
	cmp	r0, r3	@ opt, tmp196
	beq	.L2003	@,
	bhi	.L1974	@,
	movw	r1, #769	@ tmp198,
	cmp	r0, r1	@ opt, tmp198
	beq	.L1949	@,
	bhi	.L1975	@,
	cmp	r0, #768	@ opt,
	bne	.L1931	@,
	bl	VCTRL_Suspend	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1957:
	movw	r3, #:lower16:g_TraceCtrl	@ tmp440,
	movt	r3, #:upper16:g_TraceCtrl	@ tmp440,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC305	@,
	str	r4, [r3, #0]	@ dat,
	movt	r1, #:upper16:.LC305	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L2007:
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp483
	str	r5, [fp, #-128]	@ Thr, ChanCfg.s32ChanErrThr
	bl	VCTRL_ConfigChan	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1968:
	movw	r3, #257	@ tmp190,
	cmp	r0, r3	@ opt, tmp190
	beq	.L1942	@,
	bhi	.L1970	@,
	cmp	r0, #12	@ opt,
	beq	.L1939	@,
	bhi	.L1971	@,
	cmp	r0, #11	@ opt,
	bne	.L1931	@,
	cmp	r4, #1	@ dat,
	bls	.L2008	@,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC273	@,
	movt	r1, #:upper16:.LC273	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1973:
	movw	r2, #1537	@ tmp204,
	cmp	r0, r2	@ opt, tmp204
	beq	.L1962	@,
	bhi	.L1977	@,
	movw	ip, #1282	@ tmp206,
	cmp	r0, ip	@ opt, tmp206
	beq	.L1959	@,
	bcc	.L1958	@,
	movw	r3, #1283	@ tmp208,
	cmp	r0, r3	@ opt, tmp208
	beq	.L1960	@,
	cmp	r0, #1536	@ opt,
	bne	.L1931	@,
	cmp	r4, #15	@ dat,
	bhi	.L2002	@,
	movw	r0, #:lower16:.LANCHOR0	@ tmp449,
	movt	r0, #:upper16:.LANCHOR0	@ tmp449,
	mov	r5, #1	@ tmp451,
	mov	r2, r4	@, dat
	ldr	ip, [r0, r4, asl #2]	@ tmp450, s_pstVfmwChan
	movw	r1, #:lower16:.LC310	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC310	@,
	str	r5, [ip, #1256]	@ tmp451, <variable>.stSynExtraData.s32ModuleLowlyEnable
	bl	dprint_vfmw	@
	mov	r0, r5	@ D.54110, tmp451
	b	.L1978	@
.L1974:
	cmp	r0, #1024	@ opt,
	beq	.L1954	@,
	bhi	.L1976	@,
	movw	ip, #899	@ tmp201,
	cmp	r0, ip	@ opt, tmp201
	bne	.L1931	@,
	mov	r0, r4	@, dat
	bl	VCTRL_StopChan	@
	mov	r2, r4	@, dat
	movw	r1, #:lower16:.LC299	@,
	movt	r1, #:upper16:.LC299	@,
	mov	r3, r0	@ ret.5531,
	mov	r0, #32	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, dat
	bl	VCTRL_ResetChan	@
	movw	r1, #:lower16:.LC300	@,
	mov	r2, r4	@, dat
	movt	r1, #:upper16:.LC300	@,
	mov	r3, r0	@ ret.5533,
	mov	r0, #32	@,
	bl	dprint_vfmw	@
.L2003:
	mov	r0, r4	@, dat
	bl	VCTRL_StartChan	@
	mov	r2, r4	@, dat
	movw	r1, #:lower16:.LC301	@,
	movt	r1, #:upper16:.LC301	@,
	mov	r3, r0	@ ret.5535,
	mov	r0, #32	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1969:
	cmp	r0, #5	@ opt,
	beq	.L1936	@,
	bcc	.L1935	@,
	cmp	r0, #6	@ opt,
	beq	.L1933	@,
	cmp	r0, #7	@ opt,
	bne	.L1931	@,
	bic	r5, r4, #-16777216	@ Thr, dat,
	mov	r4, r4, lsr #24	@ ChanID, dat,
	sub	r6, fp, #444	@ tmp227,,
	mov	r0, #32	@,
	mov	r2, r4	@, ChanID
	mov	r3, r5	@, Thr
	movw	r1, #:lower16:.LC271	@,
	movt	r1, #:upper16:.LC271	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp227
	bl	VCTRL_GetChanCfg	@
	cmp	r0, #0	@,
	bne	.L1933	@,
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp227
	str	r5, [fp, #-424]	@ Thr, ChanCfg.s32ChanStrmOFThr
	bl	VCTRL_ConfigChan	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1970:
	movw	r1, #513	@ tmp192,
	cmp	r0, r1	@ opt, tmp192
	beq	.L1944	@,
	bhi	.L1972	@,
	cmp	r0, #512	@ opt,
	bne	.L1931	@,
	cmp	r4, #15	@ dat,
	bhi	.L1933	@,
	movw	r5, #:lower16:.LANCHOR3	@ tmp245,
	movt	r5, #:upper16:.LANCHOR3	@ tmp245,
	add	r6, r5, r4, asl #2	@, tmp248, tmp245, dat,
	ldr	r7, [r6, #3572]	@ tmp250, vfmw_save_str_file
	cmp	r7, #0	@ tmp250,
	beq	.L2009	@,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC282	@,
	movt	r1, #:upper16:.LC282	@,
	bl	dprint_vfmw	@
	ldr	r0, [r6, #3572]	@, vfmw_save_str_file
	bl	klib_fclose	@
	mov	r0, #0	@ tmp278,
	str	r0, [r6, #3572]	@ tmp278, vfmw_save_str_file
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1977:
	movw	r1, #1539	@ tmp209,
	cmp	r0, r1	@ opt, tmp209
	beq	.L1964	@,
	bcc	.L1963	@,
	movw	r2, #1540	@ tmp211,
	cmp	r0, r2	@ opt, tmp211
	beq	.L1965	@,
	movw	ip, #1541	@ tmp212,
	cmp	r0, ip	@ opt, tmp212
	bne	.L1931	@,
	movw	lr, #:lower16:.LANCHOR3	@ tmp480,
	movt	lr, #:upper16:.LANCHOR3	@ tmp480,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC311	@,
	str	r4, [lr, #3876]	@ dat, g_SCDID
	movt	r1, #:upper16:.LC311	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L2002:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC309	@,
	movt	r1, #:upper16:.LC309	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1942:
	movw	r6, #:lower16:g_PrintEnable	@ tmp241,
	movt	r6, #:upper16:g_PrintEnable	@ tmp241,
	mov	r0, r4	@, dat
	mov	r2, #67108864	@ tmp243,
	ldr	r4, [r6, #0]	@ TmpPrintEnable, g_PrintEnable
	mov	r1, #1	@,
	str	r2, [r6, #0]	@ tmp243, g_PrintEnable
	bl	PrintScdRawState	@
	mov	r0, #1	@ D.54110,
	str	r4, [r6, #0]	@ TmpPrintEnable, g_PrintEnable
	b	.L1978	@
.L1962:
	cmp	r4, #15	@ dat,
	bhi	.L2002	@,
	movw	r1, #:lower16:.LANCHOR0	@ tmp454,
	movt	r1, #:upper16:.LANCHOR0	@ tmp454,
	mov	ip, #0	@ tmp456,
	mov	r2, r4	@, dat
	ldr	lr, [r1, r4, asl #2]	@ tmp455, s_pstVfmwChan
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC310	@,
	movt	r1, #:upper16:.LC310	@,
	str	ip, [lr, #1256]	@ tmp456, <variable>.stSynExtraData.s32ModuleLowlyEnable
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1960:
	movw	r3, #:lower16:g_TraceImgPeriod	@ tmp446,
	movt	r3, #:upper16:g_TraceImgPeriod	@ tmp446,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC308	@,
	str	r4, [r3, #0]	@ dat,
	movt	r1, #:upper16:.LC308	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1965:
	add	r4, r4, r4, asl #1	@, tmp474, dat, dat,
	movw	r1, #:lower16:s_SmIIS	@ tmp470,
	movt	r1, #:upper16:s_SmIIS	@ tmp470,
	mov	r2, #0	@ tmp479,
	add	ip, r1, r4, asl #4	@, tmp476, tmp470, tmp474,
	mov	r0, #1	@ D.54110,
	ldr	r3, [ip, #40]	@ <variable>.pSmInstArray, <variable>.pSmInstArray
	str	r2, [r3, #88]	@ tmp479, <variable>.Config.ScdLowdlyEnable
	b	.L1978	@
.L1963:
	movw	r3, #:lower16:g_TunnelLineNumber	@ tmp458,
	movt	r3, #:upper16:g_TunnelLineNumber	@ tmp458,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC310	@,
	str	r4, [r3, #0]	@ dat,
	movt	r1, #:upper16:.LC310	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1964:
	add	r4, r4, r4, asl #1	@, tmp464, dat, dat,
	movw	r0, #:lower16:s_SmIIS	@ tmp460,
	movt	r0, #:upper16:s_SmIIS	@ tmp460,
	mov	r2, #1	@ tmp469,
	add	r1, r0, r4, asl #4	@, tmp466, tmp460, tmp464,
	mov	r0, r2	@ D.54110, tmp469
	ldr	ip, [r1, #40]	@ <variable>.pSmInstArray, <variable>.pSmInstArray
	str	r2, [ip, #88]	@ tmp469, <variable>.Config.ScdLowdlyEnable
	b	.L1978	@
.L2006:
	movw	r3, #:lower16:g_PrintEnable	@ tmp213,
	movt	r3, #:upper16:g_PrintEnable	@ tmp213,
	mov	r0, #1	@ D.54110,
	str	r4, [r3, #0]	@ dat, g_PrintEnable
	b	.L1978	@
.L1947:
#APP
@ 182 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/asm/memory.h" 1
	@ __pv_stub
1:	sub	r5, r4, #-2130706432	@ ptr, dat,
	.pushsection .pv_table,"a"
	.long	1b
	.popsection

@ 0 "" 2
	cmp	r5, #0	@ ptr,
	ldmib	r1, {r7, r8}	@ phole ldm
	beq	.L2004	@,
	sub	r6, fp, #144	@ tmp487,,
	mov	r1, #50	@,
	movw	r2, #:lower16:.LC297	@,
	movw	r3, #:lower16:.LANCHOR2	@,
	movt	r2, #:upper16:.LC297	@,
	movt	r3, #:upper16:.LANCHOR2	@,
	mov	r0, r6	@, tmp487
	str	r4, [sp, #0]	@ dat,
	bl	snprintf	@
	mov	r0, r6	@, tmp487
	mov	r1, #66	@,
	mov	r2, #0	@,
	bl	klib_fopen	@
	subs	r4, r0, #0	@ fp,
	beq	.L1995	@,
	movw	lr, #:lower16:g_vdm_hal_fun_ptr	@ tmp420,
	movt	lr, #:upper16:g_vdm_hal_fun_ptr	@ tmp420,
	ldr	ip, [lr, #116]	@ D.54263, g_vdm_hal_fun_ptr.pfun_VDMHAL_Write1DYuv
	cmp	ip, #0	@ D.54263,
	beq	.L1996	@,
	mov	r1, #1	@ tmp421,
	mov	r2, r7	@, D.54253
	str	r1, [sp, #0]	@ tmp421,
	mov	r3, r8	@, D.54255
	mov	r1, r5	@, ptr
	blx	ip	@ D.54263
.L1997:
	mov	r0, r4	@, fp
	bl	klib_fclose	@
	movw	r1, #:lower16:.LC298	@,
	mov	r2, r6	@, tmp487
	movt	r1, #:upper16:.LC298	@,
	mov	r0, #32	@,
	bl	dprint_vfmw	@
.L1994:
	mov	r0, r5	@, ptr
	bl	__arm_iounmap	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1939:
	cmp	r4, #1	@ dat,
	bls	.L2010	@,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC275	@,
	movt	r1, #:upper16:.LC275	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1935:
	and	r5, r4, #3	@ DecOrderOutput, dat,
	mov	r4, r4, lsr #24	@ ChanID, dat,
	sub	r6, fp, #244	@ tmp485,,
	mov	r0, #32	@,
	mov	r2, r4	@, ChanID
	mov	r3, r5	@, DecOrderOutput
	movw	r1, #:lower16:.LC268	@,
	movt	r1, #:upper16:.LC268	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp485
	bl	VCTRL_GetChanCfg	@
	cmp	r0, #0	@,
	bne	.L1933	@,
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp485
	str	r5, [fp, #-216]	@ DecOrderOutput, ChanCfg.s32DecOrderOutput
	bl	VCTRL_ConfigChan	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1949:
	bl	VCTRL_Resume	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1944:
	cmp	r4, #15	@ dat,
	bhi	.L1933	@,
	movw	r5, #:lower16:.LANCHOR3	@ tmp486,
	mov	r6, r4, asl #2	@ tmp484, dat,
	movt	r5, #:upper16:.LANCHOR3	@ tmp486,
	add	r3, r6, r5	@ tmp282, tmp484, tmp486
	ldr	r1, [r3, #3708]	@ tmp284, vfmw_save_seg_file
	cmp	r1, #0	@ tmp284,
	beq	.L2011	@,
	add	r5, r6, r5	@ tmp304, tmp484, tmp486
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC286	@,
	movt	r1, #:upper16:.LC286	@,
	bl	dprint_vfmw	@
	ldr	r0, [r5, #3708]	@, vfmw_save_seg_file
	bl	klib_fclose	@
	mov	r2, #0	@ tmp312,
	mov	r0, #1	@ D.54110,
	str	r2, [r5, #3708]	@ tmp312, vfmw_save_seg_file
	b	.L1978	@
.L1958:
	movw	ip, #:lower16:g_TraceBsPeriod	@ tmp442,
	movt	ip, #:upper16:g_TraceBsPeriod	@ tmp442,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC306	@,
	str	r4, [ip, #0]	@ dat,
	movt	r1, #:upper16:.LC306	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1954:
	movw	r3, #:lower16:.LANCHOR3	@ tmp434,
	movt	r3, #:upper16:.LANCHOR3	@ tmp434,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC302	@,
	str	r4, [r3, #3864]	@ dat, g_SleepTime
	movt	r1, #:upper16:.LC302	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1959:
	movw	lr, #:lower16:g_TraceFramePeriod	@ tmp444,
	movt	lr, #:upper16:g_TraceFramePeriod	@ tmp444,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC307	@,
	str	r4, [lr, #0]	@ dat,
	movt	r1, #:upper16:.LC307	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1936:
	and	r5, r4, #7	@ Mode, dat,
	mov	r4, r4, lsr #24	@ ChanID, dat,
	sub	r6, fp, #344	@ tmp221,,
	mov	r0, #32	@,
	mov	r2, r4	@, ChanID
	mov	r3, r5	@, Mode
	movw	r1, #:lower16:.LC269	@,
	movt	r1, #:upper16:.LC269	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp221
	bl	VCTRL_GetChanCfg	@
	cmp	r0, #0	@,
	bne	.L1979	@,
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp221
	str	r5, [fp, #-320]	@ Mode, ChanCfg.s32DecMode
	bl	VCTRL_ConfigChan	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1975:
	cmp	r0, #896	@ opt,
	beq	.L1950	@,
	movw	r2, #897	@ tmp200,
	cmp	r0, r2	@ opt, tmp200
	bne	.L1931	@,
	mov	r0, r4	@, dat
	bl	VCTRL_ResetChan	@
	mov	r2, r4	@, dat
	movw	r1, #:lower16:.LC300	@,
	movt	r1, #:upper16:.LC300	@,
	mov	r3, r0	@ ret.5527,
	mov	r0, #32	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1950:
	mov	r0, r4	@, dat
	bl	VCTRL_StopChan	@
	mov	r2, r4	@, dat
	movw	r1, #:lower16:.LC299	@,
	movt	r1, #:upper16:.LC299	@,
	mov	r3, r0	@ ret,
	mov	r0, #32	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1976:
	movw	r3, #1025	@ tmp202,
	cmp	r0, r3	@ opt, tmp202
	beq	.L1955	@,
	movw	r1, #1026	@ tmp203,
	cmp	r0, r1	@ opt, tmp203
	bne	.L1931	@,
	movw	lr, #:lower16:.LANCHOR3	@ tmp438,
	movt	lr, #:upper16:.LANCHOR3	@ tmp438,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC304	@,
	str	r4, [lr, #3872]	@ dat, g_StopDec
	movt	r1, #:upper16:.LC304	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1955:
	movw	ip, #:lower16:.LANCHOR3	@ tmp436,
	movt	ip, #:upper16:.LANCHOR3	@ tmp436,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC303	@,
	str	r4, [ip, #3868]	@ dat, g_DnrSleepTime
	movt	r1, #:upper16:.LC303	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1972:
	movw	r2, #514	@ tmp194,
	cmp	r0, r2	@ opt, tmp194
	beq	.L1945	@,
	movw	ip, #515	@ tmp195,
	cmp	r0, ip	@ opt, tmp195
	bne	.L1931	@,
#APP
@ 182 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/asm/memory.h" 1
	@ __pv_stub
1:	sub	r5, r4, #-2130706432	@ ptr, dat,
	.pushsection .pv_table,"a"
	.long	1b
	.popsection

@ 0 "" 2
	cmp	r5, #0	@ ptr,
	beq	.L2004	@,
	sub	r6, fp, #144	@ tmp407,,
	mov	r1, #50	@,
	movw	r2, #:lower16:.LC294	@,
	movw	r3, #:lower16:.LANCHOR2	@,
	movt	r2, #:upper16:.LC294	@,
	movt	r3, #:upper16:.LANCHOR2	@,
	mov	r0, r6	@, tmp407
	str	r4, [sp, #0]	@ dat,
	bl	snprintf	@
	mov	r0, r6	@, tmp407
	mov	r1, #66	@,
	mov	r2, #0	@,
	bl	klib_fopen	@
	subs	r4, r0, #0	@ fp,
	beq	.L1995	@,
	mov	r2, r4	@, fp
	mov	r1, #3145728	@,
	mov	r0, r5	@, ptr
	bl	klib_fwrite	@
	mov	r0, r4	@, fp
	bl	klib_fclose	@
	mov	r2, r6	@, tmp407
	movw	r1, #:lower16:.LC295	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC295	@,
	bl	dprint_vfmw	@
	b	.L1994	@
.L1945:
	cmp	r4, #15	@ dat,
	bhi	.L1933	@,
	movw	r5, #:lower16:.LANCHOR3	@ tmp313,
	movt	r5, #:upper16:.LANCHOR3	@ tmp313,
	add	r7, r5, r4, asl #2	@, tmp316, tmp313, dat,
	sub	r8, r7, #1648	@ tmp317, tmp316,
	ldr	r6, [r7, #-1656]	@ tmp318, vfmw_save_yuv_file
	sub	r8, r8, #8	@ tmp317, tmp317,
	cmp	r6, #0	@ tmp318,
	beq	.L2012	@,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC292	@,
	movt	r1, #:upper16:.LC292	@,
	bl	dprint_vfmw	@
	ldr	r0, [r7, #-1656]	@, vfmw_save_yuv_file
	bl	klib_fclose	@
	ldr	r0, [r5, #3856]	@ temp.5515, MemRecord_YUV.PhyAddr
	movw	r3, #:lower16:.LANCHOR0	@ tmp388,
	movw	r1, #:lower16:.LANCHOR2	@ tmp394,
	movt	r3, #:upper16:.LANCHOR0	@ tmp388,
	movt	r1, #:upper16:.LANCHOR2	@ tmp394,
	cmp	r0, #0	@ temp.5515,
	mov	r2, #0	@ tmp387,
	mvn	ip, #0	@ tmp395,
	str	r2, [r7, #-1656]	@ tmp387, vfmw_save_yuv_file
	str	ip, [r1, #68]	@ tmp395, save_yuv_chan_num
	str	r2, [r3, #504]	@ tmp387, pY
	str	r2, [r5, #-1528]	@ tmp387, save_yuv_with_crop
	str	r2, [r3, #508]	@ tmp387, pVl
	str	r2, [r3, #512]	@ tmp387, pUl
	beq	.L1933	@,
	ldr	r1, [r5, #3852]	@, MemRecord_YUV.VirAddr
	bl	MEM_ReleaseMemBlock	@
	ldr	r2, [r5, #3860]	@, MemRecord_YUV.Length
	ldr	r1, [r5, #3852]	@, MemRecord_YUV.VirAddr
	ldr	r0, [r5, #3856]	@, MemRecord_YUV.PhyAddr
	bl	MEM_DelMemRecord	@
	ldr	r0, .L2013	@,
	mov	r1, #16	@,
	bl	__memzero	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1971:
	cmp	r0, #13	@ opt,
	beq	.L1940	@,
	cmp	r0, #256	@ opt,
	bne	.L1931	@,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC278	@,
	movt	r1, #:upper16:.LC278	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, dat
	bl	DBG_PrintTracer	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1940:
	cmp	r4, #16	@ dat,
	bls	.L1982	@,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC276	@,
	movt	r1, #:upper16:.LC276	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1979:
	mov	r2, r4	@, ChanID
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC270	@,
	movt	r1, #:upper16:.LC270	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1982:
	movw	r3, #:lower16:.LANCHOR0	@ tmp238,
	movt	r3, #:upper16:.LANCHOR0	@ tmp238,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC277	@,
	str	r4, [r3, #1364]	@ dat, g_CurProcChan
	movt	r1, #:upper16:.LC277	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L2004:
	mov	r2, r4	@, dat
	movw	r1, #:lower16:.LC293	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC293	@,
	bl	dprint_vfmw	@
	b	.L1994	@
.L2008:
	movw	lr, #:lower16:USE_FF_APT_EN	@ tmp231,
	movt	lr, #:upper16:USE_FF_APT_EN	@ tmp231,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC272	@,
	str	r4, [lr, #0]	@ dat,
	movt	r1, #:upper16:.LC272	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L2010:
	movw	ip, #:lower16:.LANCHOR0	@ tmp234,
	movt	ip, #:upper16:.LANCHOR0	@ tmp234,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC274	@,
	str	r4, [ip, #1372]	@ dat, g_ResetCreateNewSave
	movt	r1, #:upper16:.LC274	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1995:
	mov	r2, r6	@, tmp487
	movw	r1, #:lower16:.LC296	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC296	@,
	bl	dprint_vfmw	@
	b	.L1994	@
.L1996:
	mov	r0, ip	@, D.54263
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #8247	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L1997	@
.L2012:
	ldr	ip, [r5, #3844]	@ save_file_cnt.755, save_file_cnt
	sub	r9, fp, #444	@ str.752,,
	movw	sl, #:lower16:.LANCHOR2	@ tmp323,
	movt	sl, #:upper16:.LANCHOR2	@ tmp323,
	add	lr, ip, #1	@ tmp321, save_file_cnt.755,
	mov	r1, #100	@,
	str	ip, [sp, #0]	@ save_file_cnt.755,
	mov	r3, sl	@, tmp323
	str	lr, [r5, #3844]	@ tmp321, save_file_cnt
	mov	r0, r9	@, str.752
	movw	r2, #:lower16:.LC287	@,
	movt	r2, #:upper16:.LC287	@,
	bl	snprintf	@
	mov	r0, r9	@, str.752
	movw	r1, #578	@,
	mov	r2, r6	@, tmp318
	bl	klib_fopen	@
	cmp	r0, #0	@ D.54197,
	str	r0, [r7, #-1656]	@ D.54197, vfmw_save_yuv_file
	beq	.L1988	@,
	ldr	r0, .L2013	@,
	mov	r1, #16	@,
	bl	__memzero	@
	movw	r0, #:lower16:.LC288	@,
	mov	r1, r6	@, tmp318
	movt	r0, #:upper16:.LC288	@,
	mov	r2, #14155776	@,
	ldr	r3, .L2013	@,
	str	r6, [sp, #0]	@ tmp318,
	bl	MEM_AllocMemBlock	@
	subs	r7, r0, #0	@ D.54210,
	beq	.L1989	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC289	@,
	movt	r1, #:upper16:.LC289	@,
	bl	dprint_vfmw	@
	ldr	r0, [r8, #0]	@, vfmw_save_yuv_file
	bl	klib_fclose	@
	movw	r1, #:lower16:.LANCHOR0	@ tmp350,
	movt	r1, #:upper16:.LANCHOR0	@ tmp350,
	mvn	r0, #0	@ tmp357,
	str	r6, [r5, #-1528]	@ tmp318, save_yuv_with_crop
	str	r0, [sl, #68]	@ tmp357, save_yuv_chan_num
	mov	r0, #1	@ D.54110,
	str	r6, [r8, #0]	@ tmp318, vfmw_save_yuv_file
	str	r6, [r1, #504]	@ tmp318, pY
	str	r6, [r1, #508]	@ tmp318, pVl
	str	r6, [r1, #512]	@ tmp318, pUl
	b	.L1978	@
.L2011:
	ldr	ip, [r5, #3836]	@ save_file_cnt.749, save_file_cnt
	sub	r7, fp, #144	@ str.746,,
	mov	r1, #50	@,
	movw	r2, #:lower16:.LC283	@,
	add	lr, ip, #1	@ tmp287, save_file_cnt.749,
	movt	r2, #:upper16:.LC283	@,
	str	ip, [sp, #0]	@ save_file_cnt.749,
	mov	r0, r7	@, str.746
	str	lr, [r5, #3836]	@ tmp287, save_file_cnt
	movw	r3, #:lower16:.LANCHOR2	@,
	movt	r3, #:upper16:.LANCHOR2	@,
	add	r6, r6, r5	@ tmp293, tmp484, tmp486
	bl	snprintf	@
	mov	r0, r7	@, str.746
	mov	r1, #66	@,
	mov	r2, #0	@,
	bl	klib_fopen	@
	str	r4, [r5, #3840]	@ dat, save_seg_chan_num
	cmp	r0, #0	@ D.54179,
	str	r0, [r6, #3708]	@ D.54179, vfmw_save_seg_file
	beq	.L1986	@,
	mov	r2, r7	@, str.746
	mov	r3, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC284	@,
	movt	r1, #:upper16:.LC284	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L2009:
	ldr	ip, [r5, #3700]	@ save_file_cnt.743, save_file_cnt
	sub	r8, fp, #144	@ str.739,,
	mov	r1, #50	@,
	movw	r2, #:lower16:.LC279	@,
	add	lr, ip, #1	@ tmp253, save_file_cnt.743,
	movt	r2, #:upper16:.LC279	@,
	str	ip, [sp, #0]	@ save_file_cnt.743,
	mov	r0, r8	@, str.739
	str	lr, [r5, #3700]	@ tmp253, save_file_cnt
	movw	r3, #:lower16:.LANCHOR2	@,
	movt	r3, #:upper16:.LANCHOR2	@,
	bl	snprintf	@
	mov	r0, r8	@, str.739
	mov	r2, r7	@, tmp250
	mov	r1, #66	@,
	bl	klib_fopen	@
	str	r4, [r5, #3704]	@ dat, save_str_chan_num
	cmp	r0, #0	@ D.54161,
	str	r0, [r6, #3572]	@ D.54161, vfmw_save_str_file
	beq	.L1984	@,
	mov	r2, r8	@, str.739
	mov	r3, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC280	@,
	movt	r1, #:upper16:.LC280	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1989:
	ldr	r1, [r5, #3852]	@, MemRecord_YUV.VirAddr
	and	r4, r4, #3	@ save_yuv_with_crop.764, dat,
	ldr	r2, [r5, #3860]	@, MemRecord_YUV.Length
	ldr	r0, [r5, #3856]	@, MemRecord_YUV.PhyAddr
	bl	MEM_AddMemRecord	@
	ldr	lr, [r5, #3852]	@ pY.759, MemRecord_YUV.VirAddr
	movw	ip, #:lower16:.LANCHOR0	@ tmp364,
	movt	ip, #:upper16:.LANCHOR0	@ tmp364,
	str	r4, [r5, #-1528]	@ save_yuv_with_crop.764, save_yuv_with_crop
	add	r6, lr, #11796480	@ tmp367, pY.759,
	mov	r2, r9	@, str.752
	str	r6, [ip, #508]	@ tmp367, pVl
	mov	r3, r7	@, D.54210
	str	r4, [sp, #0]	@ save_yuv_with_crop.764,
	mov	r0, #32	@,
	add	r4, lr, #9437184	@ pUl.761, pY.759,
	movw	r1, #:lower16:.LC290	@,
	str	r4, [ip, #512]	@ pUl.761, pUl
	movt	r1, #:upper16:.LC290	@,
	str	lr, [ip, #504]	@ pY.759, pY
	str	r7, [sl, #68]	@ D.54210, save_yuv_chan_num
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1986:
	mov	r2, r7	@, str.746
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC285	@,
	movt	r1, #:upper16:.LC285	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1988:
	mov	r2, r9	@, str.752
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC291	@,
	movt	r1, #:upper16:.LC291	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L1984:
	mov	r2, r8	@, str.739
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC281	@,
	movt	r1, #:upper16:.LC281	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.54110,
	b	.L1978	@
.L2014:
	.align	2
.L2013:
	.word	.LANCHOR3+3848
	.fnend
	.size	VCTRL_SetDbgOption, .-VCTRL_SetDbgOption
	.align	2
	.global	vfmw_write_proc
	.type	vfmw_write_proc, %function
vfmw_write_proc:
	.fnstart
.LFB1650:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #48
	sub	sp, sp, #48	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r2, #255	@ count,
	mov	r3, #0	@ tmp164,
	mov	r4, r2	@ count, count
	mov	r7, r1	@ buffer, buffer
	str	r3, [fp, #-32]	@ tmp164, dat1
	str	r3, [fp, #-44]	@ tmp164, dat4
	str	r3, [fp, #-40]	@ tmp164, dat3
	str	r3, [fp, #-36]	@ tmp164, dat2
	bhi	.L2186	@,
	movw	r6, #:lower16:.LANCHOR3	@ tmp169,
	movt	r6, #:upper16:.LANCHOR3	@ tmp169,
	add	r5, r6, #3872	@ tmp339, tmp169,
	mov	r1, #256	@,
	add	r5, r5, #8	@ tmp339, tmp339,
	mov	r0, r5	@, tmp339
	bl	__memzero	@
	mov	r2, sp	@,
	bic	ip, r2, #8128	@ tmp172,,
	bic	r1, ip, #63	@ tmp172, tmp172,
	ldr	r0, [r1, #8]	@ <variable>.addr_limit, <variable>.addr_limit
#APP
@ 434 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/asm/uaccess.h" 1
	adds r2, r7, r4; sbcccs r2, r2, r0; movcc r0, #0	@ roksum, buffer, count, flag
@ 0 "" 2
	cmp	r0, #0	@ flag,
	beq	.L2187	@,
	cmp	r4, #0	@ count,
	streqb	r4, [r6, #3880]	@ count, cmd
	bne	.L2188	@,
.L2183:
	movw	r7, #:lower16:.LANCHOR4	@ tmp336,
	movt	r7, #:upper16:.LANCHOR4	@ tmp336,
	mov	r6, r4	@ i, count
	mov	r3, r4	@ j, count
.L2023:
	add	r3, r3, r7	@ tmp201, j, tmp336
	mov	lr, #0	@ tmp203,
	ldr	r0, .L2195	@,
	sub	r1, fp, #32	@,,
	strb	lr, [r3, #-4048]	@ tmp203, str
	bl	str2val	@
	subs	r3, r0, #0	@ D.55139,
	bne	.L2055	@,
	cmp	r4, r6	@ count, i
	bls	.L2031	@,
	add	r2, r5, r6	@ ivtmp.5595, tmp339, i
	mvn	r1, r6	@ tmp362, i
	add	r0, r1, r4	@ tmp361, tmp362, count
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5619, cmd
	and	r0, r0, #1	@ tmp363, tmp361,
	cmp	r1, #32	@ prephitmp.5619,
	beq	.L2113	@,
	movhi	r3, #1	@ j.5600,
	strhib	r1, [r7, #-4048]	@ prephitmp.5619, str
.L2113:
	add	r6, r6, #1	@ i, i,
	add	r2, r2, #1	@ ivtmp.5595, ivtmp.5595,
	cmp	r6, r4	@ i, count
	bcs	.L2031	@,
	cmp	r0, #0	@ tmp363,
	beq	.L2036	@,
	cmp	r3, #0	@ j.5600,
	bne	.L2189	@,
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5619, cmd
	cmp	r1, #32	@ prephitmp.5619,
	beq	.L2117	@,
.L2175:
	cmp	r1, #32	@ prephitmp.5619,
	addhi	r0, r3, r7	@ tmp422, j.5600, tmp336
	addhi	r3, r3, #1	@ j.5600, j.5600,
	strhib	r1, [r0, #-4048]	@ prephitmp.5619, str
	cmp	r3, #0	@ j.5600,
	beq	.L2117	@,
	cmp	r1, #32	@ prephitmp.5619,
	beq	.L2031	@,
.L2117:
	add	r6, r6, #1	@ i, i,
	add	r2, r2, #1	@ ivtmp.5595, ivtmp.5595,
	cmp	r6, r4	@ i, count
	bcc	.L2036	@,
	b	.L2031	@
.L2120:
	ldrb	r2, [r2, #1]	@ zero_extendqisi2	@ prephitmp.5619, cmd
	cmp	r2, #32	@ prephitmp.5619,
	beq	.L2122	@,
.L2177:
	cmp	r2, #32	@ prephitmp.5619,
	addhi	ip, r3, r7	@ tmp426, j.5600, tmp336
	addhi	r3, r3, #1	@ j.5600, j.5600,
	strhib	r2, [ip, #-4048]	@ prephitmp.5619, str
	cmp	r3, #0	@ j.5600,
	beq	.L2122	@,
	cmp	r2, #32	@ prephitmp.5619,
	beq	.L2031	@,
.L2122:
	add	r6, r0, #1	@ i, tmp365,
	add	r2, r1, #1	@ ivtmp.5595, tmp364,
	cmp	r6, r4	@ i, count
	bcs	.L2031	@,
.L2036:
	cmp	r3, #0	@ j.5600,
	ldrneb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5619, cmd
	bne	.L2033	@,
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5619, cmd
	cmp	r1, #32	@ prephitmp.5619,
	beq	.L2034	@,
.L2033:
	cmp	r1, #32	@ prephitmp.5619,
	addhi	r0, r3, r7	@ tmp218, j.5600, tmp336
	addhi	r3, r3, #1	@ j.5600, j.5600,
	strhib	r1, [r0, #-4048]	@ prephitmp.5619, str
	cmp	r3, #0	@ j.5600,
	beq	.L2034	@,
	cmp	r1, #32	@ prephitmp.5619,
	beq	.L2031	@,
.L2034:
	add	r6, r6, #1	@ i, i,
	cmp	r3, #0	@ j.5600,
	add	r1, r2, #1	@ tmp364, ivtmp.5595,
	mov	r0, r6	@ tmp365, i
	beq	.L2120	@,
	ldrb	r2, [r2, #1]	@ zero_extendqisi2	@ prephitmp.5619, cmd
	b	.L2177	@
.L2031:
	add	r2, r3, r7	@ tmp223, j.5600, tmp336
	mov	ip, #0	@ tmp225,
	ldr	r0, .L2195	@,
	sub	r1, fp, #36	@,,
	strb	ip, [r2, #-4048]	@ tmp225, str
	bl	str2val	@
	subs	r3, r0, #0	@ D.55152,
	bne	.L2055	@,
	ldr	r2, [fp, #-32]	@ prephitmp.5567, dat1
	sub	lr, r2, #512	@ tmp235, prephitmp.5567,
	cmp	lr, #255	@ tmp235,
	bhi	.L2038	@,
	cmp	r2, #516	@ prephitmp.5567,
	beq	.L2190	@,
.L2039:
	cmp	r4, r6	@ count, i
	movls	r3, #0	@ j.5603,
	bls	.L2057	@,
	add	r5, r5, r6	@ ivtmp.5583, tmp339, i
	mvn	r3, r6	@ tmp347, i
	add	r1, r3, r4	@ tmp346, tmp347, count
	mov	r3, #0	@ j.5603,
	ldrb	r2, [r5, #0]	@ zero_extendqisi2	@ prephitmp.5608, cmd
	and	r1, r1, #1	@ tmp348, tmp346,
	cmp	r2, #32	@ prephitmp.5608,
	beq	.L2074	@,
	movhi	r3, #1	@ j.5603,
	strhib	r2, [r7, #-4048]	@ prephitmp.5608, str
.L2074:
	add	r6, r6, #1	@ i, i,
	add	r5, r5, #1	@ ivtmp.5583, ivtmp.5583,
	cmp	r4, r6	@ count, i
	bls	.L2057	@,
	cmp	r1, #0	@ tmp348,
	beq	.L2062	@,
	cmp	r3, #0	@ j.5603,
	bne	.L2191	@,
	ldrb	r2, [r5, #0]	@ zero_extendqisi2	@ prephitmp.5608, cmd
	cmp	r2, #32	@ prephitmp.5608,
	beq	.L2078	@,
.L2160:
	cmp	r2, #32	@ prephitmp.5608,
	addhi	r1, r3, r7	@ tmp386, j.5603, tmp336
	addhi	r3, r3, #1	@ j.5603, j.5603,
	strhib	r2, [r1, #-4048]	@ prephitmp.5608, str
	cmp	r3, #0	@ j.5603,
	beq	.L2078	@,
	cmp	r2, #32	@ prephitmp.5608,
	bls	.L2057	@,
.L2078:
	add	r6, r6, #1	@ i, i,
	add	r5, r5, #1	@ ivtmp.5583, ivtmp.5583,
	cmp	r4, r6	@ count, i
	bhi	.L2062	@,
	b	.L2057	@
.L2081:
	ldrb	r2, [r5, #1]	@ zero_extendqisi2	@ prephitmp.5608, cmd
	cmp	r2, #32	@ prephitmp.5608,
	beq	.L2083	@,
.L2162:
	cmp	r2, #32	@ prephitmp.5608,
	addhi	r0, r3, r7	@ tmp390, j.5603, tmp336
	addhi	r3, r3, #1	@ j.5603, j.5603,
	strhib	r2, [r0, #-4048]	@ prephitmp.5608, str
	cmp	r3, #0	@ j.5603,
	beq	.L2083	@,
	cmp	r2, #32	@ prephitmp.5608,
	bls	.L2057	@,
.L2083:
	add	r6, r6, #1	@ i, tmp349,
	add	r5, r1, #1	@ ivtmp.5583, tmp350,
	cmp	r4, r6	@ count, i
	bls	.L2057	@,
.L2062:
	cmp	r3, #0	@ j.5603,
	ldrneb	r2, [r5, #0]	@ zero_extendqisi2	@ prephitmp.5608, cmd
	bne	.L2059	@,
	ldrb	r2, [r5, #0]	@ zero_extendqisi2	@ prephitmp.5608, cmd
	cmp	r2, #32	@ prephitmp.5608,
	beq	.L2060	@,
.L2059:
	cmp	r2, #32	@ prephitmp.5608,
	addhi	r1, r3, r7	@ tmp286, j.5603, tmp336
	addhi	r3, r3, #1	@ j.5603, j.5603,
	strhib	r2, [r1, #-4048]	@ prephitmp.5608, str
	cmp	r3, #0	@ j.5603,
	beq	.L2060	@,
	cmp	r2, #32	@ prephitmp.5608,
	bls	.L2057	@,
.L2060:
	cmp	r3, #0	@ j.5603,
	add	r6, r6, #1	@ tmp349, i,
	add	r1, r5, #1	@ tmp350, ivtmp.5583,
	beq	.L2081	@,
	ldrb	r2, [r5, #1]	@ zero_extendqisi2	@ prephitmp.5608, cmd
	b	.L2162	@
.L2057:
	add	r0, r3, r7	@ tmp291, j.5603, tmp336
	mov	r1, #0	@ tmp293,
	movw	r2, #:lower16:.LANCHOR4	@ tmp289,
	movt	r2, #:upper16:.LANCHOR4	@ tmp289,
	strb	r1, [r0, #-4048]	@ tmp293, str
	ldrb	lr, [r7, #-4048]	@ zero_extendqisi2	@ str, str
	cmp	lr, #47	@ str,
	bne	.L2184	@,
	cmp	r3, #0	@ j.5603,
	beq	.L2064	@,
	sub	r3, r3, #1	@ D.55199, j.5603,
	mov	r0, #32	@,
	add	r5, r3, r2	@ tmp299, D.55199, tmp289
	ldr	r2, .L2195	@,
	ldrb	ip, [r5, #-4048]	@ zero_extendqisi2	@ tmp301, str
	cmp	ip, #47	@ tmp301,
	streqb	r1, [r5, #-4048]	@ tmp293, str
	movw	r5, #:lower16:.LANCHOR2	@ tmp312,
	movt	r5, #:upper16:.LANCHOR2	@ tmp312,
	movw	r1, #:lower16:.LC315	@,
	movt	r1, #:upper16:.LC315	@,
	bl	dprint_vfmw	@
	mov	r2, #64	@,
	mov	r0, r5	@, tmp312
	ldr	r1, .L2195	@,
	bl	strncpy	@
	mov	r2, #0	@ tmp317,
	strb	r2, [r5, #63]	@ tmp317, s_VfmwSavePath
.L2184:
	ldr	r2, [fp, #-32]	@ prephitmp.5567, dat1
.L2038:
	ldr	r3, [fp, #-36]	@, dat2
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC317	@,
	movt	r1, #:upper16:.LC317	@,
	bl	dprint_vfmw	@
	ldr	r3, [fp, #-36]	@ dat2, dat2
	ldr	ip, [fp, #-40]	@ dat3, dat3
	sub	r1, fp, #76	@,,
	ldr	r2, [fp, #-44]	@ dat4, dat4
	ldr	r0, [fp, #-32]	@, dat1
	str	r3, [fp, #-76]	@ dat2, args
	str	ip, [fp, #-72]	@ dat3, args
	str	r2, [fp, #-68]	@ dat4, args
	bl	VCTRL_SetDbgOption	@
	mov	r0, r4	@ D.55115, count
.L2017:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2189:
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5619, cmd
	b	.L2175	@
.L2191:
	ldrb	r2, [r5, #0]	@ zero_extendqisi2	@ prephitmp.5608, cmd
	b	.L2160	@
.L2187:
	mov	r1, r7	@, buffer
	mov	r0, r5	@, tmp339
	mov	r2, r4	@, count
	bl	__copy_from_user	@
	subs	r3, r0, #0	@ count.5615,
	bne	.L2019	@,
	add	r6, r4, r6	@ tmp184, count, tmp169
	cmp	r4, #0	@ count,
	strb	r3, [r6, #3880]	@ count.5615, cmd
	beq	.L2183	@,
	ldrb	r2, [r5, #0]	@ zero_extendqisi2	@ prephitmp.5569, cmd
	sub	r7, r4, #1	@ tmp366, count,
	and	r1, r7, #1	@ tmp368, tmp366,
	movw	r7, #:lower16:.LANCHOR4	@ tmp336,
	cmp	r2, #32	@ prephitmp.5569,
	movt	r7, #:upper16:.LANCHOR4	@ tmp336,
	beq	.L2126	@,
	movhi	r3, #1	@ j,
	strhib	r2, [r7, #-4048]	@ prephitmp.5569, str
.L2126:
	mov	r6, #1	@ i,
	cmp	r4, r6	@ count, i
	bls	.L2023	@,
	cmp	r1, #0	@ tmp368,
	beq	.L2028	@,
	cmp	r3, #0	@ j,
	bne	.L2192	@,
	ldrb	r2, [r5, r6]	@ zero_extendqisi2	@ prephitmp.5569, cmd
	cmp	r2, #32	@ prephitmp.5569,
	beq	.L2130	@,
.L2180:
	cmp	r2, #32	@ prephitmp.5569,
	addhi	r1, r3, r7	@ tmp434, j, tmp336
	addhi	r3, r3, #1	@ j, j,
	strhib	r2, [r1, #-4048]	@ prephitmp.5569, str
	cmp	r3, #0	@ j,
	beq	.L2130	@,
	cmp	r2, #32	@ prephitmp.5569,
	beq	.L2023	@,
.L2130:
	add	r6, r6, #1	@ i, i,
	cmp	r4, r6	@ count, i
	bhi	.L2028	@,
	b	.L2023	@
.L2133:
	ldrb	r2, [r5, r6]	@ zero_extendqisi2	@ prephitmp.5569, cmd
	cmp	r2, #32	@ prephitmp.5569,
	beq	.L2135	@,
.L2182:
	cmp	r2, #32	@ prephitmp.5569,
	addhi	r0, r3, r7	@ tmp438, j, tmp336
	addhi	r3, r3, #1	@ j, j,
	strhib	r2, [r0, #-4048]	@ prephitmp.5569, str
	cmp	r3, #0	@ j,
	beq	.L2135	@,
	cmp	r2, #32	@ prephitmp.5569,
	beq	.L2023	@,
.L2135:
	add	r6, r1, #1	@ i, tmp369,
	cmp	r4, r6	@ count, i
	bls	.L2023	@,
.L2028:
	cmp	r3, #0	@ j,
	ldrneb	r2, [r5, r6]	@ zero_extendqisi2	@ prephitmp.5569, cmd
	bne	.L2025	@,
	ldrb	r2, [r5, r6]	@ zero_extendqisi2	@ prephitmp.5569, cmd
	cmp	r2, #32	@ prephitmp.5569,
	beq	.L2026	@,
.L2025:
	cmp	r2, #32	@ prephitmp.5569,
	addhi	r1, r3, r7	@ tmp196, j, tmp336
	addhi	r3, r3, #1	@ j, j,
	strhib	r2, [r1, #-4048]	@ prephitmp.5569, str
	cmp	r3, #0	@ j,
	beq	.L2026	@,
	cmp	r2, #32	@ prephitmp.5569,
	beq	.L2023	@,
.L2026:
	add	r6, r6, #1	@ i, i,
	cmp	r3, #0	@ j,
	mov	r1, r6	@ tmp369, i
	beq	.L2133	@,
	ldrb	r2, [r5, r6]	@ zero_extendqisi2	@ prephitmp.5569, cmd
	b	.L2182	@
.L2192:
	ldrb	r2, [r5, r6]	@ zero_extendqisi2	@ prephitmp.5569, cmd
	b	.L2180	@
.L2188:
	mov	r0, r5	@, tmp339
	mov	r1, r4	@, count
	bl	__memzero	@
.L2019:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC313	@,
	movt	r1, #:upper16:.LC313	@,
	bl	dprint_vfmw	@
	mvn	r0, #4	@ D.55115,
	b	.L2017	@
.L2190:
	cmp	r4, r6	@ count, i
	bls	.L2041	@,
	add	r2, r5, r6	@ ivtmp.5591, tmp339, i
	mvn	r1, r6	@ tmp357, i
	add	r0, r1, r4	@ tmp356, tmp357, count
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5605, cmd
	and	r0, r0, #1	@ tmp358, tmp356,
	cmp	r1, #32	@ prephitmp.5605,
	beq	.L2100	@,
	movhi	r3, #1	@ j.5601,
	strhib	r1, [r7, #-4048]	@ prephitmp.5605, str
.L2100:
	add	r6, r6, #1	@ i, i,
	add	r2, r2, #1	@ ivtmp.5591, ivtmp.5591,
	cmp	r4, r6	@ count, i
	bls	.L2041	@,
	cmp	r0, #0	@ tmp358,
	beq	.L2046	@,
	cmp	r3, #0	@ j.5601,
	bne	.L2193	@,
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5605, cmd
	cmp	r1, #32	@ prephitmp.5605,
	beq	.L2104	@,
.L2170:
	cmp	r1, #32	@ prephitmp.5605,
	addhi	r0, r3, r7	@ tmp410, j.5601, tmp336
	addhi	r3, r3, #1	@ j.5601, j.5601,
	strhib	r1, [r0, #-4048]	@ prephitmp.5605, str
	cmp	r3, #0	@ j.5601,
	beq	.L2104	@,
	cmp	r1, #32	@ prephitmp.5605,
	bls	.L2041	@,
.L2104:
	add	r6, r6, #1	@ i, i,
	add	r2, r2, #1	@ ivtmp.5591, ivtmp.5591,
	cmp	r4, r6	@ count, i
	bhi	.L2046	@,
	b	.L2041	@
.L2107:
	ldrb	r2, [r2, #1]	@ zero_extendqisi2	@ prephitmp.5605, cmd
	cmp	r2, #32	@ prephitmp.5605,
	beq	.L2109	@,
.L2172:
	cmp	r2, #32	@ prephitmp.5605,
	addhi	ip, r3, r7	@ tmp414, j.5601, tmp336
	addhi	r3, r3, #1	@ j.5601, j.5601,
	strhib	r2, [ip, #-4048]	@ prephitmp.5605, str
	cmp	r3, #0	@ j.5601,
	beq	.L2109	@,
	cmp	r2, #32	@ prephitmp.5605,
	bls	.L2041	@,
.L2109:
	add	r6, r0, #1	@ i, tmp359,
	add	r2, r1, #1	@ ivtmp.5591, tmp360,
	cmp	r4, r6	@ count, i
	bls	.L2041	@,
.L2046:
	cmp	r3, #0	@ j.5601,
	ldrneb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5605, cmd
	bne	.L2043	@,
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5605, cmd
	cmp	r1, #32	@ prephitmp.5605,
	beq	.L2044	@,
.L2043:
	cmp	r1, #32	@ prephitmp.5605,
	addhi	r0, r3, r7	@ tmp242, j.5601, tmp336
	addhi	r3, r3, #1	@ j.5601, j.5601,
	strhib	r1, [r0, #-4048]	@ prephitmp.5605, str
	cmp	r3, #0	@ j.5601,
	beq	.L2044	@,
	cmp	r1, #32	@ prephitmp.5605,
	bls	.L2041	@,
.L2044:
	add	r6, r6, #1	@ i, i,
	cmp	r3, #0	@ j.5601,
	add	r1, r2, #1	@ tmp360, ivtmp.5591,
	mov	r0, r6	@ tmp359, i
	beq	.L2107	@,
	ldrb	r2, [r2, #1]	@ zero_extendqisi2	@ prephitmp.5605, cmd
	b	.L2172	@
.L2041:
	add	r3, r3, r7	@ tmp247, j.5601, tmp336
	mov	ip, #0	@ tmp249,
	ldr	r0, .L2195	@,
	sub	r1, fp, #40	@,,
	strb	ip, [r3, #-4048]	@ tmp249, str
	bl	str2val	@
	subs	r3, r0, #0	@ D.55170,
	bne	.L2055	@,
	cmp	r4, r6	@ count, i
	bls	.L2049	@,
	add	r2, r5, r6	@ ivtmp.5587, tmp339, i
	mvn	r0, r6	@ tmp352, i
	add	lr, r0, r4	@ tmp351, tmp352, count
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5618, cmd
	and	r0, lr, #1	@ tmp353, tmp351,
	cmp	r1, #32	@ prephitmp.5618,
	beq	.L2087	@,
	movhi	r3, #1	@ j.5602,
	strhib	r1, [r7, #-4048]	@ prephitmp.5618, str
.L2087:
	add	r6, r6, #1	@ i, i,
	add	r2, r2, #1	@ ivtmp.5587, ivtmp.5587,
	cmp	r4, r6	@ count, i
	bls	.L2049	@,
	cmp	r0, #0	@ tmp353,
	beq	.L2054	@,
	cmp	r3, #0	@ j.5602,
	bne	.L2194	@,
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5618, cmd
	cmp	r1, #32	@ prephitmp.5618,
	beq	.L2091	@,
.L2165:
	cmp	r1, #32	@ prephitmp.5618,
	addhi	r0, r3, r7	@ tmp398, j.5602, tmp336
	addhi	r3, r3, #1	@ j.5602, j.5602,
	strhib	r1, [r0, #-4048]	@ prephitmp.5618, str
	cmp	r3, #0	@ j.5602,
	beq	.L2091	@,
	cmp	r1, #32	@ prephitmp.5618,
	bls	.L2049	@,
.L2091:
	add	r6, r6, #1	@ i, i,
	add	r2, r2, #1	@ ivtmp.5587, ivtmp.5587,
	cmp	r4, r6	@ count, i
	bhi	.L2054	@,
	b	.L2049	@
.L2094:
	ldrb	r2, [r2, #1]	@ zero_extendqisi2	@ prephitmp.5618, cmd
	cmp	r2, #32	@ prephitmp.5618,
	beq	.L2096	@,
.L2167:
	cmp	r2, #32	@ prephitmp.5618,
	addhi	ip, r3, r7	@ tmp402, j.5602, tmp336
	addhi	r3, r3, #1	@ j.5602, j.5602,
	strhib	r2, [ip, #-4048]	@ prephitmp.5618, str
	cmp	r3, #0	@ j.5602,
	beq	.L2096	@,
	cmp	r2, #32	@ prephitmp.5618,
	bls	.L2049	@,
.L2096:
	add	r6, r0, #1	@ i, tmp354,
	add	r2, r1, #1	@ ivtmp.5587, tmp355,
	cmp	r4, r6	@ count, i
	bls	.L2049	@,
.L2054:
	cmp	r3, #0	@ j.5602,
	ldrneb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5618, cmd
	bne	.L2051	@,
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5618, cmd
	cmp	r1, #32	@ prephitmp.5618,
	beq	.L2052	@,
.L2051:
	cmp	r1, #32	@ prephitmp.5618,
	addhi	r0, r3, r7	@ tmp264, j.5602, tmp336
	addhi	r3, r3, #1	@ j.5602, j.5602,
	strhib	r1, [r0, #-4048]	@ prephitmp.5618, str
	cmp	r3, #0	@ j.5602,
	beq	.L2052	@,
	cmp	r1, #32	@ prephitmp.5618,
	bls	.L2049	@,
.L2052:
	add	r6, r6, #1	@ i, i,
	cmp	r3, #0	@ j.5602,
	add	r1, r2, #1	@ tmp355, ivtmp.5587,
	mov	r0, r6	@ tmp354, i
	beq	.L2094	@,
	ldrb	r2, [r2, #1]	@ zero_extendqisi2	@ prephitmp.5618, cmd
	b	.L2167	@
.L2049:
	add	ip, r3, r7	@ tmp269, j.5602, tmp336
	mov	r2, #0	@ tmp271,
	ldr	r0, .L2195	@,
	sub	r1, fp, #44	@,,
	strb	r2, [ip, #-4048]	@ tmp271, str
	bl	str2val	@
	cmp	r0, #0	@,
	beq	.L2039	@,
.L2055:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC314	@,
	ldr	r2, .L2195+4	@,
	movt	r1, #:upper16:.LC314	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.55115,
	b	.L2017	@
.L2193:
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5605, cmd
	b	.L2170	@
.L2194:
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5618, cmd
	b	.L2165	@
.L2186:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC312	@,
	movt	r1, #:upper16:.LC312	@,
	bl	dprint_vfmw	@
	mvn	r0, #4	@ D.55115,
	b	.L2017	@
.L2064:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC316	@,
	ldr	r2, .L2195+8	@,
	movt	r1, #:upper16:.LC316	@,
	movw	r3, #9742	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.55115,
	b	.L2017	@
.L2196:
	.align	2
.L2195:
	.word	.LANCHOR4-4048
	.word	.LANCHOR3+3880
	.word	.LANCHOR1+424
	.fnend
	.size	vfmw_write_proc, .-vfmw_write_proc
	.align	2
	.global	VCTRL_ResetChan
	.type	VCTRL_ResetChan, %function
VCTRL_ResetChan:
	.fnstart
.LFB1583:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r5, #:lower16:.LANCHOR0	@ tmp208,
	movt	r5, #:upper16:.LANCHOR0	@ tmp208,
	mov	r4, r0	@ ChanID, ChanID
	ldr	r3, [r5, r0, asl #2]	@ D.51864, s_pstVfmwChan
	cmp	r3, #0	@ D.51864,
	beq	.L2207	@,
	ldr	r7, [r3, #16]	@ ChanIsRun, <variable>.s32IsRun
	bl	VCTRL_StopChan	@
	ldr	r3, [r5, r4, asl #2]	@ tmp145, s_pstVfmwChan
	mov	r6, #0	@ tmp146,
	add	r1, r5, #1456	@ tmp151, tmp208,
	mov	r0, #300	@ tmp154,
	add	r2, r1, #4	@ tmp151, tmp151,
	mov	r1, r0	@, tmp154
	str	r6, [r3, #344]	@ tmp146, <variable>.s32CountNoDecparamFlag
	ldr	ip, [r5, r4, asl #2]	@ tmp148, s_pstVfmwChan
	mla	r0, r0, r4, r2	@, tmp154, ChanID, tmp151
	str	r6, [ip, #348]	@ tmp146, <variable>.u32NoDecparamStartTime
	bl	__memzero	@
	mov	r1, r6	@, tmp146
	mov	r0, r4	@, ChanID
	bl	VCTRL_SetSendStreamAgainFlag	@
	mov	r1, #896	@,
	movw	r0, #:lower16:g_stLowdlyInfo	@,
	movt	r0, #:upper16:g_stLowdlyInfo	@,
	bl	__memzero	@
	ldr	r9, [r5, r4, asl #2]	@ tmp158, s_pstVfmwChan
	mov	r0, r4	@, ChanID
	str	r6, [r9, #1248]	@ tmp146, <variable>.stSynExtraData.s32KeepSPSPPS
	mvn	r9, #0	@,
	bl	InitSyntaxCtx	@
	ldr	r8, [r5, r4, asl #2]	@ tmp162, s_pstVfmwChan
	mov	r1, #416	@,
	add	r0, r8, #688	@, tmp162,
	mvn	r8, #0	@ tmp166,
	bl	__memzero	@
	ldr	r2, [r5, r4, asl #2]	@ tmp164, s_pstVfmwChan
	mov	r3, #608	@ tmp165,
	mov	r0, #616	@ tmp169,
	movw	r1, #:lower16:251556	@ tmp176,
	movt	r1, #:upper16:251556	@ tmp176,
	strd	r8, [r2, r3]	@ tmp166, tmp164, tmp165
	movw	r2, #:lower16:251548	@ tmp180,
	ldr	ip, [r5, r4, asl #2]	@ tmp168, s_pstVfmwChan
	movt	r2, #:upper16:251548	@ tmp180,
	movw	r3, #:lower16:251552	@ tmp184,
	movt	r3, #:upper16:251552	@ tmp184,
	strd	r8, [ip, r0]	@ tmp166, tmp168, tmp169
	ldr	r0, [r5, r4, asl #2]	@ tmp172, s_pstVfmwChan
	str	r6, [r0, #1104]	@ tmp146, <variable>.stSynExtraData.s32NewPicSegDetector
	ldr	ip, [r5, r4, asl #2]	@ tmp175, s_pstVfmwChan
	str	r6, [ip, r1]	@ tmp146, <variable>.s32FindStartCodeCnt
	ldr	r0, [r5, r4, asl #2]	@ tmp179, s_pstVfmwChan
	str	r6, [r0, r2]	@ tmp146, <variable>.s32H264Score
	mov	r0, r4	@, ChanID
	ldr	ip, [r5, r4, asl #2]	@ tmp183, s_pstVfmwChan
	str	r6, [ip, r3]	@ tmp146, <variable>.s32Mpeg2Score
	ldr	r1, [r5, r4, asl #2]	@ temp.5655, s_pstVfmwChan
	ldr	r2, [r1, #1416]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r2, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	streq	r6, [r1, #1456]	@ tmp146, <variable>.stSynExtraData.s32WaitFsFlag
	bl	FSP_SwitchNotify	@
	ldr	r0, [r5, r4, asl #2]	@ tmp190, s_pstVfmwChan
	ldr	r3, [r0, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #18	@ <variable>.eVidStd,
	beq	.L2201	@,
	mov	r0, r4	@, ChanID
	bl	FSP_ResetInstance	@
.L2202:
	mov	r0, r4	@, ChanID
	bl	InitUsdPool	@
	mov	r0, r4	@, ChanID
	bl	SM_Reset	@
	ldr	ip, [r5, #1372]	@ g_ResetCreateNewSave, g_ResetCreateNewSave
	cmp	ip, #0	@ g_ResetCreateNewSave,
	beq	.L2203	@,
	movw	r5, #:lower16:.LANCHOR3	@ tmp194,
	movt	r5, #:upper16:.LANCHOR3	@ tmp194,
	add	r5, r5, r4, asl #2	@, tmp197, tmp194, ChanID,
	str	r4, [fp, #-40]	@ ChanID, data
	ldr	lr, [r5, #3572]	@ tmp199, vfmw_save_str_file
	cmp	lr, #0	@ tmp199,
	beq	.L2204	@,
	sub	r6, fp, #40	@ data.567,,
	mov	r0, #512	@,
	mov	r1, r6	@, data.567
	bl	VCTRL_SetDbgOption	@
	ldr	r0, [r5, #3572]	@ tmp205, vfmw_save_str_file
	cmp	r0, #0	@ tmp205,
	beq	.L2204	@,
	mov	r1, r6	@, data.567
	mov	r0, #512	@,
	bl	VCTRL_SetDbgOption	@
.L2204:
	movw	r1, #:lower16:.LC318	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC318	@,
	bl	dprint_vfmw	@
.L2203:
	cmp	r7, #0	@ ChanIsRun,
	bne	.L2208	@,
.L2205:
	mov	r0, r4	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	mov	r0, #0	@ D.51868,
.L2199:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2208:
	mov	r0, r4	@, ChanID
	bl	VCTRL_StartChan	@
	b	.L2205	@
.L2201:
	mov	r0, r4	@, ChanID
	bl	FSP_EmptyInstance	@
	b	.L2202	@
.L2207:
	mov	r0, r3	@, D.51864
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4026	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51868,
	b	.L2199	@
	.fnend
	.size	VCTRL_ResetChan, .-VCTRL_ResetChan
	.align	2
	.global	VCTRL_ConfigChan
	.type	VCTRL_ConfigChan, %function
VCTRL_ConfigChan:
	.fnstart
.LFB1578:
	@ args = 0, pretend = 0, frame = 192
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #204
	sub	sp, sp, #204	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ ChanID,
	mov	r6, #0	@ tmp212,
	mov	r5, r0	@ ChanID, ChanID
	str	r6, [fp, #-52]	@ tmp212, s32supportFlag
	mov	r8, r1	@ pstCfg, pstCfg
	bhi	.L2308	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp668,
	movt	r4, #:upper16:.LANCHOR0	@ tmp668,
	ldr	r3, [r4, r0, asl #2]	@ D.51424, s_pstVfmwChan
	cmp	r3, #0	@ D.51424,
	beq	.L2309	@,
	ldr	r3, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r3, #1	@ <variable>.s32IsOpen,
	bne	.L2310	@,
	bl	VCTRL_CheckChanWH	@
	cmp	r0, #0	@,
	bne	.L2311	@,
	movw	r6, #:lower16:.LANCHOR4	@ tmp670,
	movt	r6, #:upper16:.LANCHOR4	@ tmp670,
	sub	r0, r6, #3792	@, tmp670,
	bl	GetVdecCapability	@
	ldr	r2, [r8, #0]	@ prephitmp.5677, <variable>.eVidStd
	sub	r3, r6, #3792	@ ivtmp.5704, tmp670,
	sub	ip, r6, #3664	@ D.61249, tmp670,
	b	.L2217	@
.L2215:
	cmp	r1, r2	@ D.51435, prephitmp.5677
	beq	.L2216	@,
	ldr	r1, [r0, #20]	@ D.51435, Capability.SupportedStd
	cmp	r1, #18	@ D.51435,
	bhi	.L2303	@,
	cmp	r1, r2	@ D.51435, prephitmp.5677
	beq	.L2216	@,
	cmp	r3, ip	@ ivtmp.5704, D.61249
	beq	.L2216	@,
.L2217:
	ldr	r1, [r3, #20]	@ D.51435, Capability.SupportedStd
	add	r0, r3, #4	@ tmp675, ivtmp.5704,
	add	r3, r0, #4	@ ivtmp.5704, tmp675,
	cmp	r1, #18	@ D.51435,
	bls	.L2215	@,
.L2303:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC320	@,
	movt	r1, #:upper16:.LC320	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
.L2211:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L2216:
	cmp	r2, #8	@ prephitmp.5677,
	beq	.L2312	@,
.L2218:
	cmp	r2, #9	@ prephitmp.5677,
	beq	.L2313	@,
.L2220:
	mov	r0, r5	@, ChanID
	mov	r1, r8	@, pstCfg
	bl	VCTRL_CmpConfigParameter	@
	subs	r7, r0, #0	@ D.51451,
	beq	.L2314	@,
	ldr	r2, [r8, #76]	@ <variable>.s32IsOmxPath, <variable>.s32IsOmxPath
	cmp	r2, #0	@ <variable>.s32IsOmxPath,
	bne	.L2222	@,
	ldr	r3, [r8, #0]	@ D.51439, <variable>.eVidStd
	sub	r7, r3, #10	@ tmp234, D.51439,
	cmp	r7, #2	@ tmp234,
	bls	.L2315	@,
	cmp	r3, #4	@ D.51439,
	beq	.L2224	@,
.L2225:
	ldr	r7, [r4, r5, asl #2]	@ prephitmp.5679, s_pstVfmwChan
	cmp	r3, #14	@ D.51439,
	movne	r1, #0	@, prephitmp.5809
	moveq	r1, #1	@, prephitmp.5809
	movw	r3, #:lower16:.LANCHOR0	@ tmp240,
	movt	r3, #:upper16:.LANCHOR0	@ tmp240,
	ldr	r2, [r7, #48]	@ D.51474, <variable>.stChanCfg.eVidStd
	sub	sl, r2, #10	@ tmp241, D.51474,
	cmp	sl, #2	@ tmp241,
	bhi	.L2227	@,
.L2322:
	ldr	ip, [r3, #516]	@ g_VdmCharacter, g_VdmCharacter
	tst	ip, #1	@ g_VdmCharacter,
	beq	.L2228	@,
.L2229:
	cmp	r2, #14	@ D.51474,
	movne	r2, #0	@, prephitmp.5684
	moveq	r2, #1	@, prephitmp.5684
	cmp	r2, r1	@ prephitmp.5684, prephitmp.5809
	beq	.L2231	@,
.L2323:
	ldr	lr, [r7, #196]	@ <variable>.s32OneChanMem, <variable>.s32OneChanMem
	cmp	lr, #0	@ <variable>.s32OneChanMem,
	bne	.L2232	@,
	ldr	r0, .L2329	@,
	bl	OSAL_SpinUnLockIRQ	@
	ldr	r3, [r7, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	cmp	r3, #0	@ <variable>.stChanMem_scd.Length,
	bne	.L2316	@,
.L2233:
	ldr	r0, [r7, #220]	@, <variable>.stChanMem_vdh.VirAddr
	bl	KernelMunmap	@
	ldr	r3, [r8, #0]	@ temp.5717, <variable>.eVidStd
	sub	r0, r3, #10	@ tmp256, temp.5717,
	cmp	r0, #2	@ tmp256,
	bhi	.L2234	@,
	ldr	r1, [r4, #516]	@ g_VdmCharacter, g_VdmCharacter
	tst	r1, #1	@ g_VdmCharacter,
	beq	.L2235	@,
.L2236:
	ldr	r1, [r7, #228]	@, <variable>.stChanMem_vdh.Length
	mov	sl, #0	@ tmp269,
	ldr	r0, [r7, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	KernelMmap	@
	ldr	r1, [r7, #244]	@ temp.5722, <variable>.stChanMem_scd.Length
	strb	sl, [r7, #216]	@ tmp269, <variable>.stChanMem_vdh.IsCached
	cmp	r1, sl	@ temp.5722,
	mov	r9, r0	@ pVir_vdh,
	bne	.L2317	@,
.L2237:
	mov	r2, #0	@,
	str	r2, [fp, #-224]	@, %sfp
.L2238:
	movw	sl, #:lower16:.LANCHOR0	@ tmp273,
	movt	sl, #:upper16:.LANCHOR0	@ tmp273,
	add	r0, sl, #520	@, tmp273,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, [r4, r5, asl #2]	@ tmp276, s_pstVfmwChan
	cmp	r0, #0	@ tmp276,
	beq	.L2318	@,
	cmp	r9, #0	@ pVir_vdh,
	beq	.L2240	@,
	ldr	lr, [r7, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	ldr	r3, [fp, #-224]	@, %sfp
	rsbs	ip, r3, #1	@,
	movcc	ip, #0	@
	cmp	lr, #0	@ <variable>.stChanMem_scd.Length,
	moveq	ip, #0	@,,
	cmp	ip, #0	@ tmp288,
	bne	.L2240	@,
	ldr	r0, [r7, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	ldr	r1, [r7, #220]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r2, [r7, #228]	@, <variable>.stChanMem_vdh.Length
	str	ip, [fp, #-232]	@ tmp3,
	bl	MEM_DelMemRecord	@
	ldr	r3, [fp, #-232]	@,
	cmp	r0, #0	@
	str	r0, [fp, #-228]	@, %sfp
	bne	.L2319	@,
	str	r9, [r7, #220]	@ pVir_vdh, <variable>.stChanMem_vdh.VirAddr
	mov	r1, r9	@, pVir_vdh
	ldr	r0, [r7, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	ldr	r2, [r7, #228]	@, <variable>.stChanMem_vdh.Length
	bl	MEM_AddMemRecord	@
	subs	r9, r0, #0	@ D.51529,
	bne	.L2320	@,
	ldr	r2, [r7, #244]	@ temp.5745, <variable>.stChanMem_scd.Length
	cmp	r2, #0	@ temp.5745,
	beq	.L2304	@,
	ldr	r0, [r7, #240]	@, <variable>.stChanMem_scd.PhyAddr
	ldr	r1, [r7, #236]	@, <variable>.stChanMem_scd.VirAddr
	bl	MEM_DelMemRecord	@
	subs	r3, r0, #0	@ D.51534,
	bne	.L2321	@,
	ldr	r0, [fp, #-224]	@, %sfp
	ldr	r2, [r7, #244]	@, <variable>.stChanMem_scd.Length
	str	r0, [r7, #236]	@, <variable>.stChanMem_scd.VirAddr
	ldr	r1, [fp, #-224]	@, %sfp
	ldr	r0, [r7, #240]	@, <variable>.stChanMem_scd.PhyAddr
	str	r3, [fp, #-232]	@,
	bl	MEM_AddMemRecord	@
	ldr	r3, [fp, #-232]	@,
	cmp	r0, #0	@,
	beq	.L2304	@,
	ldr	r2, [r7, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	mov	r0, r3	@, D.51534
	movw	r1, #:lower16:.LC324	@,
	movt	r1, #:upper16:.LC324	@,
	str	r2, [sp, #0]	@ <variable>.stChanMem_scd.Length,
	ldr	r3, [r7, #236]	@, <variable>.stChanMem_scd.VirAddr
	ldr	r2, [r7, #240]	@, <variable>.stChanMem_scd.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2315:
	ldr	r9, [r4, #516]	@ g_VdmCharacter, g_VdmCharacter
	tst	r9, #1	@ g_VdmCharacter,
	bne	.L2225	@,
.L2224:
	ldr	r7, [r4, r5, asl #2]	@ prephitmp.5679, s_pstVfmwChan
	movw	r3, #:lower16:.LANCHOR0	@ tmp240,
	mov	r1, #1	@ prephitmp.5809,
	movt	r3, #:upper16:.LANCHOR0	@ tmp240,
	ldr	r2, [r7, #48]	@ D.51474, <variable>.stChanCfg.eVidStd
	sub	sl, r2, #10	@ tmp241, D.51474,
	cmp	sl, #2	@ tmp241,
	bls	.L2322	@,
.L2227:
	cmp	r2, #4	@ D.51474,
	bne	.L2229	@,
.L2228:
	mov	r2, #1	@ prephitmp.5684,
	cmp	r2, r1	@ prephitmp.5684, prephitmp.5809
	bne	.L2323	@,
.L2231:
	add	r0, r7, #48	@, prephitmp.5679,
	mov	r2, #100	@,
	mov	r1, r8	@, pstCfg
	sub	r7, fp, #220	@ tmp669,,
	bl	memcpy	@
	ldr	r9, [r4, r5, asl #2]	@ tmp373, s_pstVfmwChan
	ldr	r2, [r8, #12]	@ <variable>.s32ChanPriority, <variable>.s32ChanPriority
	mov	r1, #152	@,
	mov	r0, r7	@, tmp669
	str	r2, [r9, #24]	@ <variable>.s32ChanPriority, <variable>.s32Priority
	ldr	ip, [r8, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	sl, [r4, r5, asl #2]	@ tmp376, s_pstVfmwChan
	str	ip, [sl, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	r3, [r4, r5, asl #2]	@ tmp379, s_pstVfmwChan
	ldr	r9, [r8, #88]	@ <variable>.s32ExtraFrameStoreNum, <variable>.s32ExtraFrameStoreNum
	str	r9, [r3, #1424]	@ <variable>.s32ExtraFrameStoreNum, <variable>.stSynExtraData.stChanOption.s32ExtraFrameStoreNum
	bl	__memzero	@
	ldr	sl, [r4, r5, asl #2]	@ tmp383, s_pstVfmwChan
	ldr	r2, [sl, #292]	@ <variable>.s32ScdChanMemAddr, <variable>.s32ScdChanMemAddr
	str	r2, [fp, #-208]	@ <variable>.s32ScdChanMemAddr, ScdInstCfg.BufPhyAddr
	ldr	r0, [sl, #292]	@, <variable>.s32ScdChanMemAddr
	mvn	sl, #0	@ tmp396,
	bl	MEM_Phy2Vir	@
	ldr	lr, [r4, r5, asl #2]	@ tmp389, s_pstVfmwChan
	ldr	r9, [r8, #76]	@ <variable>.s32IsOmxPath, <variable>.s32IsOmxPath
	mov	r1, #0	@ tmp395,
	ldr	r2, [r8, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	movw	r3, #:lower16:-121389056	@ tmp394,
	ldr	ip, [r8, #12]	@ <variable>.s32ChanPriority, <variable>.s32ChanPriority
	cmp	r9, #1	@ <variable>.s32IsOmxPath,
	movt	r3, #:upper16:-121389056	@ tmp394,
	str	r0, [fp, #-220]	@, ScdInstCfg.pBufVirAddr
	ldr	r0, [lr, #304]	@ <variable>.s32ScdChanMemSize, <variable>.s32ScdChanMemSize
	str	r3, [fp, #-200]	@ tmp394, ScdInstCfg.RegPhyBaseAddr
	str	r2, [fp, #-212]	@ <variable>.eVidStd, ScdInstCfg.VidStd
	strb	ip, [fp, #-216]	@ <variable>.s32ChanPriority, ScdInstCfg.Priority
	sub	ip, fp, #196	@ tmp402,,
	str	sl, [fp, #-188]	@ tmp396, ScdInstCfg.LastRawDisContinueCount
	str	r0, [fp, #-204]	@ <variable>.s32ScdChanMemSize, ScdInstCfg.BufSize
	str	r1, [fp, #-184]	@ tmp395, ScdInstCfg.DisContinueRawPacketFlag
	ldreq	r0, [r8, #80]	@ <variable>.s32MaxRawPacketNum, <variable>.s32MaxRawPacketNum
	ldreq	sl, [r8, #84]	@ <variable>.s32MaxRawPacketSize, <variable>.s32MaxRawPacketSize
	streq	r9, [fp, #-176]	@ <variable>.s32IsOmxPath, ScdInstCfg.IsOmxPath
	sub	r9, fp, #48	@ tmp405,,
	streq	r0, [fp, #-76]	@ <variable>.s32MaxRawPacketNum, ScdInstCfg.MaxRawPacketNum
	streq	sl, [fp, #-72]	@ <variable>.s32MaxRawPacketSize, ScdInstCfg.MaxRawPacketSize
	cmp	r2, #0	@ <variable>.eVidStd,
	add	sl, r8, #4	@ tmp673, pstCfg,
	ldreq	r2, [r8, #48]	@ iftmp.547, <variable>.s32LowdlyEnable
	movne	r2, #0	@ iftmp.547,
	str	r2, [fp, #-180]	@ iftmp.547, ScdInstCfg.ScdLowdlyEnable
	ldmia	sl, {r0, r1}	@ tmp673,,
	stmia	ip, {r0, r1}	@ tmp402,,
	mov	r1, r7	@, tmp669
	mov	r0, r5	@, ChanID
	bl	SM_Config	@
	mov	r0, r9	@, tmp405
	mov	r1, #1	@,
	bl	__memzero	@
	ldr	r3, [r8, #76]	@ <variable>.s32IsOmxPath, <variable>.s32IsOmxPath
	cmp	r3, #1	@ <variable>.s32IsOmxPath,
	beq	.L2324	@,
.L2261:
	ldr	r3, [r4, r5, asl #2]	@ temp.5825, s_pstVfmwChan
	mov	ip, #0	@ tmp456,
	movw	lr, #:lower16:251576	@ tmp471,
	movt	lr, #:upper16:251576	@ tmp471,
	movw	r7, #:lower16:.LANCHOR0	@ tmp410,
	movt	r7, #:upper16:.LANCHOR0	@ tmp410,
	ldr	r1, [r3, #256]	@ <variable>.stChanMem_ctx.PhyAddr, <variable>.stChanMem_ctx.PhyAddr
	str	r1, [r3, #1228]	@ <variable>.stChanMem_ctx.PhyAddr, <variable>.stSynExtraData.s32ContextMemAddr
	ldr	r2, [r4, r5, asl #2]	@ temp.5826, s_pstVfmwChan
	ldr	r0, [r2, #260]	@ <variable>.stChanMem_ctx.Length, <variable>.stChanMem_ctx.Length
	str	r0, [r2, #1232]	@ <variable>.stChanMem_ctx.Length, <variable>.stSynExtraData.s32ContextMemSize
	ldr	r3, [r4, r5, asl #2]	@ temp.5827, s_pstVfmwChan
	ldr	r1, [r3, #276]	@ <variable>.s32VdmChanMemAddr, <variable>.s32VdmChanMemAddr
	str	r1, [r3, #576]	@ <variable>.s32VdmChanMemAddr, <variable>.stSynExtraData.s32SyntaxMemAddr
	ldr	r2, [r4, r5, asl #2]	@ temp.5828, s_pstVfmwChan
	ldr	r0, [r2, #280]	@ <variable>.s32VdmChanMemSize, <variable>.s32VdmChanMemSize
	str	r0, [r2, #580]	@ <variable>.s32VdmChanMemSize, <variable>.stSynExtraData.s32SyntaxMemSize
	ldr	r3, [r4, r5, asl #2]	@ temp.5829, s_pstVfmwChan
	ldr	r1, [r3, #308]	@ <variable>.s32BpdChanMemAddr, <variable>.s32BpdChanMemAddr
	str	r1, [r3, #588]	@ <variable>.s32BpdChanMemAddr, <variable>.stSynExtraData.s32BpdMemAddr
	ldr	r2, [r4, r5, asl #2]	@ temp.5830, s_pstVfmwChan
	ldr	r0, [r2, #312]	@ <variable>.s32BpdChanMemSize, <variable>.s32BpdChanMemSize
	str	r0, [r2, #592]	@ <variable>.s32BpdChanMemSize, <variable>.stSynExtraData.s32BpdMemSize
	ldr	r3, [r4, r5, asl #2]	@ temp.5831, s_pstVfmwChan
	ldr	r1, [r3, #316]	@ <variable>.s32Vp8SegIdChanMemAddr, <variable>.s32Vp8SegIdChanMemAddr
	str	r1, [r3, #596]	@ <variable>.s32Vp8SegIdChanMemAddr, <variable>.stSynExtraData.s32Vp8SegIdMemAddr
	ldr	r2, [r4, r5, asl #2]	@ temp.5832, s_pstVfmwChan
	ldr	r0, [r2, #320]	@ <variable>.s32Vp8SegIdChanMemSize, <variable>.s32Vp8SegIdChanMemSize
	str	r0, [r2, #600]	@ <variable>.s32Vp8SegIdChanMemSize, <variable>.stSynExtraData.s32Vp8SegIdMemSize
	ldr	r3, [r4, r5, asl #2]	@ tmp427, s_pstVfmwChan
	ldr	r1, [r8, #16]	@ <variable>.s32ChanErrThr, <variable>.s32ChanErrThr
	str	r1, [r3, #556]	@ <variable>.s32ChanErrThr, <variable>.stSynExtraData.s32OutErrThr
	ldr	r2, [r4, r5, asl #2]	@ tmp430, s_pstVfmwChan
	ldr	r0, [r8, #16]	@ <variable>.s32ChanErrThr, <variable>.s32ChanErrThr
	str	r0, [r2, #552]	@ <variable>.s32ChanErrThr, <variable>.stSynExtraData.s32RefErrThr
	ldr	r3, [r4, r5, asl #2]	@ tmp433, s_pstVfmwChan
	ldr	r1, [r8, #24]	@ <variable>.s32DecMode, <variable>.s32DecMode
	str	r1, [r3, #560]	@ <variable>.s32DecMode, <variable>.stSynExtraData.s32DecMode
	ldr	r2, [r4, r5, asl #2]	@ tmp436, s_pstVfmwChan
	ldr	r0, [r8, #28]	@ <variable>.s32DecOrderOutput, <variable>.s32DecOrderOutput
	str	r0, [r2, #564]	@ <variable>.s32DecOrderOutput, <variable>.stSynExtraData.s32DecOrderOutput
	ldr	r3, [r4, r5, asl #2]	@ tmp439, s_pstVfmwChan
	ldr	r1, [r8, #32]	@ <variable>.s32DnrTfEnable, <variable>.s32DnrTfEnable
	str	r1, [r3, #568]	@ <variable>.s32DnrTfEnable, <variable>.stSynExtraData.s32DnrTfEnable
	ldr	r2, [r4, r5, asl #2]	@ tmp442, s_pstVfmwChan
	ldr	r0, [r8, #52]	@ <variable>.s32VcmpEn, <variable>.s32VcmpEn
	str	r0, [r2, #1236]	@ <variable>.s32VcmpEn, <variable>.stSynExtraData.s32Compress_en
	ldr	r3, [r4, r5, asl #2]	@ tmp445, s_pstVfmwChan
	ldr	r1, [r8, #68]	@ <variable>.s32SupportAllP, <variable>.s32SupportAllP
	cmp	r1, #1	@ <variable>.s32SupportAllP,
	movne	r2, #0	@, tmp447
	moveq	r2, #1	@, tmp447
	str	r2, [r3, #1252]	@ tmp447, <variable>.stSynExtraData.s32SupportAllP
	ldr	r0, [r4, r5, asl #2]	@ tmp449, s_pstVfmwChan
	ldr	r1, [r8, #72]	@ <variable>.s32ModuleLowlyEnable, <variable>.s32ModuleLowlyEnable
	str	r1, [r0, #1256]	@ <variable>.s32ModuleLowlyEnable, <variable>.stSynExtraData.s32ModuleLowlyEnable
	ldr	r3, [r4, r5, asl #2]	@ tmp452, s_pstVfmwChan
	ldr	r2, [r8, #48]	@ <variable>.s32LowdlyEnable, <variable>.s32LowdlyEnable
	str	r2, [r3, #1260]	@ <variable>.s32LowdlyEnable, <variable>.stSynExtraData.s32LowdlyEnable
	ldr	r0, [r4, r5, asl #2]	@ tmp455, s_pstVfmwChan
	str	ip, [r0, #1456]	@ tmp456, <variable>.stSynExtraData.s32WaitFsFlag
	ldr	r1, [r4, r5, asl #2]	@ tmp458, s_pstVfmwChan
	str	ip, [r1, #1476]	@ tmp456, <variable>.stSynExtraData.s32Is4k60fps
	ldr	r3, [r4, r5, asl #2]	@ tmp462, s_pstVfmwChan
	ldmia	sl, {r0, r1}	@ tmp673,,
	add	r2, r3, #1104	@ tmp461, tmp462,
	add	r3, r2, #4	@ tmp461, tmp461,
	stmia	r3, {r0, r1}	@ tmp461,,
	ldr	r0, [r4, r5, asl #2]	@ tmp468, s_pstVfmwChan
	str	ip, [r0, #572]	@ tmp456, <variable>.stSynExtraData.s32DnrDispOutEnable
	ldr	r0, [r4, r5, asl #2]	@ prephitmp.5793, s_pstVfmwChan
	ldr	r3, [r0, lr]	@ prephitmp.5681, <variable>.stSynCtx.eVidStd
	ldr	r1, [r0, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, r1	@ prephitmp.5681, <variable>.eVidStd
	beq	.L2262	@,
	mov	r0, r5	@, ChanID
	bl	VCTRL_ResetChan	@
	ldr	ip, [r8, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	r0, [r7, r5, asl #2]	@ prephitmp.5793, s_pstVfmwChan
	cmp	ip, #18	@ <variable>.eVidStd,
	bne	.L2305	@,
	ldr	r2, [r0, #1288]	@ <variable>.stSynExtraData.stChanOption.Purpose, <variable>.stSynExtraData.stChanOption.Purpose
	ldr	lr, [r0, #300]	@ <variable>.s32SdecMemSize, <variable>.s32SdecMemSize
	cmp	r2, #2	@ <variable>.stSynExtraData.stChanOption.Purpose,
	ldr	r3, [r0, #296]	@ <variable>.s32SdecMemAddr, <variable>.s32SdecMemAddr
	ldrne	r1, [r0, #1296]	@ MaxWidth, <variable>.stSynExtraData.stChanOption.s32MaxWidth
	ldrne	r2, [r0, #1300]	@ MaxHeight, <variable>.stSynExtraData.stChanOption.s32MaxHeight
	ldreq	r1, [r0, #1352]	@ MaxWidth, <variable>.stSynExtraData.stChanOption.s32SlotWidth
	ldreq	r2, [r0, #1356]	@ MaxHeight, <variable>.stSynExtraData.stChanOption.s32SlotHeight
	mov	r0, r5	@, ChanID
	str	lr, [sp, #0]	@ <variable>.s32SdecMemSize,
	bl	VCTRL_PartitionMemForStdUser	@
	cmp	r0, #0	@,
	bne	.L2266	@,
	ldr	r0, [r4, r5, asl #2]	@ prephitmp.5793, s_pstVfmwChan
.L2305:
	ldr	r3, [r0, #544]	@ prephitmp.5681, <variable>.eVidStd
.L2262:
	movw	lr, #:lower16:251576	@ tmp480,
	movt	lr, #:upper16:251576	@ tmp480,
	movw	r7, #:lower16:.LANCHOR0	@ tmp481,
	movt	r7, #:upper16:.LANCHOR0	@ tmp481,
	str	r3, [r0, lr]	@ prephitmp.5681, <variable>.stSynCtx.eVidStd
	ldr	r0, [r4, r5, asl #2]	@ tmp482, s_pstVfmwChan
	ldr	r1, [r0, #296]	@ temp.5849, <variable>.s32SdecMemAddr
	mov	r0, r1	@, temp.5849
	str	r1, [fp, #-68]	@ temp.5849, stMem.PhyAddr
	bl	MEM_Phy2Vir	@
	ldr	ip, [r4, r5, asl #2]	@ tmp484, s_pstVfmwChan
	sub	r1, fp, #68	@,,
	str	r0, [fp, #-64]	@, stMem.VirAddr
	mov	r0, r5	@, ChanID
	ldr	r3, [ip, #300]	@ <variable>.s32SdecMemSize, <variable>.s32SdecMemSize
	str	r3, [fp, #-60]	@ <variable>.s32SdecMemSize, stMem.Length
	bl	RefreshDecCore	@
	cmp	r0, #0	@,
	bne	.L2219	@,
	ldr	lr, [r7, #0]	@ temp.5711, s_pstVfmwChan
	ldr	r0, [r4, #4]	@ temp.5715, s_pstVfmwChan
	cmp	lr, #0	@ temp.5711,
	ldr	ip, [r4, #8]	@ temp.5856, s_pstVfmwChan
	streq	lr, [r6, #-3644]	@ temp.5711, PrioArray
	ldrne	r1, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movweq	r3, #:lower16:g_ChanCtx	@ tmp674,
	movwne	r3, #:lower16:g_ChanCtx	@ tmp674,
	movteq	r3, #:upper16:g_ChanCtx	@ tmp674,
	movtne	r3, #:upper16:g_ChanCtx	@ tmp674,
	ldr	r2, [r4, #12]	@ temp.5860, s_pstVfmwChan
	strne	r1, [r6, #-3644]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r0, #0	@ temp.5715,
	streq	r0, [r3, #4]	@ temp.5715, g_ChanCtx.PriorByChanId
	streq	r0, [r6, #-3640]	@ temp.5715, PrioArray
	str	lr, [r3, #0]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldrne	r1, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	ldr	lr, [r4, #16]	@ temp.5864, s_pstVfmwChan
	strne	r1, [r6, #-3640]	@ <variable>.s32Priority, PrioArray
	ldrne	r0, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r0, [r3, #4]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5856,
	streq	ip, [r3, #8]	@ temp.5856, g_ChanCtx.PriorByChanId
	ldrne	r1, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r6, #-3636]	@ temp.5856, PrioArray
	strne	r1, [r6, #-3636]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r3, #8]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r2, #0	@ temp.5860,
	streq	r2, [r3, #12]	@ temp.5860, g_ChanCtx.PriorByChanId
	ldrne	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r2, [r6, #-3632]	@ temp.5860, PrioArray
	strne	r1, [r6, #-3632]	@ <variable>.s32Priority, PrioArray
	ldrne	r2, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r2, [r3, #12]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5864,
	streq	lr, [r3, #16]	@ temp.5864, g_ChanCtx.PriorByChanId
	ldrne	r1, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r6, #-3628]	@ temp.5864, PrioArray
	strne	r1, [r6, #-3628]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r3, #16]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	r0, [r4, #20]	@ temp.5868, s_pstVfmwChan
	ldr	ip, [r4, #24]	@ temp.5872, s_pstVfmwChan
	cmp	r0, #0	@ temp.5868,
	ldr	r2, [r4, #28]	@ temp.5876, s_pstVfmwChan
	streq	r0, [r3, #20]	@ temp.5868, g_ChanCtx.PriorByChanId
	ldrne	r1, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r0, [r6, #-3624]	@ temp.5868, PrioArray
	ldr	lr, [r4, #32]	@ temp.5880, s_pstVfmwChan
	strne	r1, [r6, #-3624]	@ <variable>.s32Priority, PrioArray
	ldrne	r0, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r0, [r3, #20]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5872,
	streq	ip, [r3, #24]	@ temp.5872, g_ChanCtx.PriorByChanId
	ldrne	r1, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r6, #-3620]	@ temp.5872, PrioArray
	ldr	r0, [r4, #36]	@ temp.5884, s_pstVfmwChan
	strne	r1, [r6, #-3620]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r3, #24]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r2, #0	@ temp.5876,
	streq	r2, [r3, #28]	@ temp.5876, g_ChanCtx.PriorByChanId
	ldrne	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r2, [r6, #-3616]	@ temp.5876, PrioArray
	strne	r1, [r6, #-3616]	@ <variable>.s32Priority, PrioArray
	ldrne	r2, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r2, [r3, #28]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5880,
	streq	lr, [r3, #32]	@ temp.5880, g_ChanCtx.PriorByChanId
	ldrne	r1, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r6, #-3612]	@ temp.5880, PrioArray
	strne	r1, [r6, #-3612]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r3, #32]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r0, #0	@ temp.5884,
	streq	r0, [r3, #36]	@ temp.5884, g_ChanCtx.PriorByChanId
	ldrne	r1, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r0, [r6, #-3608]	@ temp.5884, PrioArray
	strne	r1, [r6, #-3608]	@ <variable>.s32Priority, PrioArray
	ldrne	r0, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r0, [r3, #36]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	ip, [r4, #40]	@ temp.5888, s_pstVfmwChan
	ldr	r2, [r4, #44]	@ temp.5892, s_pstVfmwChan
	cmp	ip, #0	@ temp.5888,
	ldr	lr, [r4, #48]	@ temp.5896, s_pstVfmwChan
	streq	ip, [r3, #40]	@ temp.5888, g_ChanCtx.PriorByChanId
	ldrne	r1, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r6, #-3604]	@ temp.5888, PrioArray
	ldr	r0, [r4, #52]	@ temp.5900, s_pstVfmwChan
	strne	r1, [r6, #-3604]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r3, #40]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r2, #0	@ temp.5892,
	streq	r2, [r3, #44]	@ temp.5892, g_ChanCtx.PriorByChanId
	ldrne	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r2, [r6, #-3600]	@ temp.5892, PrioArray
	ldr	ip, [r4, #56]	@ temp.5904, s_pstVfmwChan
	strne	r1, [r6, #-3600]	@ <variable>.s32Priority, PrioArray
	ldrne	r2, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r2, [r3, #44]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5896,
	streq	lr, [r3, #48]	@ temp.5896, g_ChanCtx.PriorByChanId
	ldrne	r1, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r6, #-3596]	@ temp.5896, PrioArray
	strne	r1, [r6, #-3596]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r3, #48]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r0, #0	@ temp.5900,
	streq	r0, [r3, #52]	@ temp.5900, g_ChanCtx.PriorByChanId
	ldrne	r1, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r0, [r6, #-3592]	@ temp.5900, PrioArray
	strne	r1, [r6, #-3592]	@ <variable>.s32Priority, PrioArray
	ldrne	r0, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r0, [r3, #52]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5904,
	streq	ip, [r3, #56]	@ temp.5904, g_ChanCtx.PriorByChanId
	ldrne	r1, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r6, #-3588]	@ temp.5904, PrioArray
	ldr	r0, .L2329+4	@,
	strne	r1, [r6, #-3588]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r3, #56]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	r2, [r4, #60]	@ temp.5852, s_pstVfmwChan
	cmp	r2, #0	@ temp.5852,
	streq	r2, [r3, #60]	@ temp.5852, g_ChanCtx.PriorByChanId
	ldrne	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r2, [r6, #-3584]	@ temp.5852, PrioArray
	strne	r1, [r6, #-3584]	@ <variable>.s32Priority, PrioArray
	ldrne	r2, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r2, [r3, #60]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	bl	VDMDRV_SetPriority	@
	mov	r0, r5	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	mov	r0, #0	@ D.51422,
	b	.L2211	@
.L2314:
	movw	r1, #:lower16:.LC321	@,
	movt	r1, #:upper16:.LC321	@,
	bl	dprint_vfmw	@
	mov	r0, r7	@ D.51422, D.51451
	b	.L2211	@
.L2222:
	ldr	r7, [r4, r5, asl #2]	@ prephitmp.5679, s_pstVfmwChan
	b	.L2231	@
.L2313:
	sub	r0, fp, #52	@,,
	bl	REAL9DEC_Support	@
	ldr	r1, [fp, #-52]	@ s32supportFlag, s32supportFlag
	cmp	r1, #0	@ s32supportFlag,
	bne	.L2220	@,
.L2219:
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2266:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC326	@,
	movt	r1, #:upper16:.LC326	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2310:
	mov	r0, r6	@, tmp212
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #3105	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC41	@,
	movt	r3, #:upper16:.LC41	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2232:
	movw	sl, #:lower16:.LANCHOR0	@ tmp309,
	movt	sl, #:upper16:.LANCHOR0	@ tmp309,
	add	r0, sl, #520	@, tmp309,
	bl	OSAL_SpinUnLockIRQ	@
	ldr	r0, [r7, #204]	@, <variable>.stChanMem.VirAddr
	bl	KernelMunmap	@
	ldr	r3, [r8, #0]	@ temp.5758, <variable>.eVidStd
	sub	r9, r3, #10	@ tmp312, temp.5758,
	cmp	r9, #2	@ tmp312,
	bhi	.L2247	@,
	ldr	r1, [sl, #516]	@ g_VdmCharacter, g_VdmCharacter
	tst	r1, #1	@ g_VdmCharacter,
	beq	.L2248	@,
.L2249:
	ldr	r0, [r7, #208]	@, <variable>.stChanMem.PhyAddr
	ldr	r1, [r7, #212]	@, <variable>.stChanMem.Length
	bl	KernelMmap	@
	mov	r9, r0	@ pVir,
.L2250:
	movw	sl, #:lower16:.LANCHOR0	@ tmp320,
	movt	sl, #:upper16:.LANCHOR0	@ tmp320,
	add	r0, sl, #520	@, tmp320,
	bl	OSAL_SpinLockIRQ	@
	ldr	r3, [r4, r5, asl #2]	@ temp.5768, s_pstVfmwChan
	cmp	r3, #0	@ temp.5768,
	beq	.L2325	@,
	cmp	r9, #0	@ pVir,
	beq	.L2326	@,
	ldr	r2, [r3, #244]	@, <variable>.stChanMem_scd.Length
	ldr	r0, [r3, #240]	@, <variable>.stChanMem_scd.PhyAddr
	ldr	r1, [r3, #236]	@, <variable>.stChanMem_scd.VirAddr
	bl	MEM_DelMemRecord	@
	cmp	r0, #0	@
	str	r0, [fp, #-224]	@, %sfp
	ldrne	r2, [sl, r5, asl #2]	@ temp.5771, s_pstVfmwChan
	movne	r0, #0	@,
	bne	.L2307	@,
	ldr	r3, [sl, r5, asl #2]	@ temp.5775, s_pstVfmwChan
	ldr	r2, [r3, #228]	@, <variable>.stChanMem_vdh.Length
	ldr	r0, [r3, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	ldr	r1, [r3, #220]	@, <variable>.stChanMem_vdh.VirAddr
	bl	MEM_DelMemRecord	@
	cmp	r0, #0	@
	str	r0, [fp, #-228]	@, %sfp
	ldrne	r2, [sl, r5, asl #2]	@ temp.5777, s_pstVfmwChan
	ldrne	r0, [fp, #-224]	@, %sfp
	bne	.L2306	@,
	str	r9, [r7, #204]	@ pVir, <variable>.stChanMem.VirAddr
	mov	r1, r9	@, pVir
	ldr	lr, [sl, r5, asl #2]	@ tmp342, s_pstVfmwChan
	ldr	r0, [r7, #208]	@, <variable>.stChanMem.PhyAddr
	ldr	r2, [r7, #212]	@, <variable>.stChanMem.Length
	str	r9, [lr, #236]	@ pVir, <variable>.stChanMem_scd.VirAddr
	ldr	ip, [sl, r5, asl #2]	@ temp.5782, s_pstVfmwChan
	ldr	r3, [ip, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	lr, r9, r3	@ tmp345, pVir, <variable>.stChanMem_scd.Length
	str	lr, [ip, #220]	@ tmp345, <variable>.stChanMem_vdh.VirAddr
	bl	MEM_AddMemRecord	@
	subs	r9, r0, #0	@ D.51576,
	bne	.L2327	@,
	ldr	r7, [sl, r5, asl #2]	@ temp.5791, s_pstVfmwChan
	ldr	r2, [r7, #244]	@, <variable>.stChanMem_scd.Length
	ldr	r0, [r7, #240]	@, <variable>.stChanMem_scd.PhyAddr
	ldr	r1, [r7, #236]	@, <variable>.stChanMem_scd.VirAddr
	bl	MEM_AddMemRecord	@
	subs	r7, r0, #0	@ D.51579,
	bne	.L2328	@,
	ldr	r3, [sl, r5, asl #2]	@ temp.5801, s_pstVfmwChan
	ldr	r2, [r3, #228]	@, <variable>.stChanMem_vdh.Length
	ldr	r0, [r3, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	ldr	r1, [r3, #220]	@, <variable>.stChanMem_vdh.VirAddr
	bl	MEM_AddMemRecord	@
	cmp	r0, #0	@,
	bne	.L2257	@,
.L2304:
	ldr	r7, [sl, r5, asl #2]	@ prephitmp.5679, s_pstVfmwChan
	b	.L2231	@
.L2324:
	mov	r1, r9	@, tmp405
	mov	r0, r5	@, ChanID
	strb	r3, [fp, #-48]	@ <variable>.s32IsOmxPath, FspInstCfg.s8LowBufEnable
	bl	FSP_ConfigAttribute	@
	b	.L2261	@
.L2247:
	cmp	r3, #4	@ temp.5758,
	beq	.L2248	@,
	cmp	r3, #14	@ temp.5758,
	bne	.L2249	@,
.L2248:
	ldr	r0, [r7, #208]	@, <variable>.stChanMem.PhyAddr
	ldr	r1, [r7, #212]	@, <variable>.stChanMem.Length
	bl	KernelMmapCache	@
	mov	r9, r0	@ pVir,
	b	.L2250	@
.L2234:
	cmp	r3, #4	@ temp.5717,
	beq	.L2235	@,
	cmp	r3, #14	@ temp.5717,
	bne	.L2236	@,
.L2235:
	ldr	r1, [r7, #228]	@, <variable>.stChanMem_vdh.Length
	mov	sl, #1	@ tmp262,
	ldr	r0, [r7, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	KernelMmapCache	@
	ldr	r1, [r7, #244]	@ temp.5727, <variable>.stChanMem_scd.Length
	strb	sl, [r7, #216]	@ tmp262, <variable>.stChanMem_vdh.IsCached
	cmp	r1, #0	@ temp.5727,
	mov	r9, r0	@ pVir_vdh,
	beq	.L2237	@,
	ldr	r0, [r7, #240]	@, <variable>.stChanMem_scd.PhyAddr
	bl	KernelMmapCache	@
	str	r0, [fp, #-224]	@, %sfp
	strb	sl, [r7, #232]	@ tmp262, <variable>.stChanMem_scd.IsCached
	b	.L2238	@
.L2257:
	ldr	r2, [sl, r5, asl #2]	@ temp.5806, s_pstVfmwChan
	mov	r0, r7	@, D.51579
.L2306:
	ldr	lr, [r2, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	movw	r1, #:lower16:.LC324	@,
	movt	r1, #:upper16:.LC324	@,
	str	lr, [sp, #0]	@ <variable>.stChanMem_vdh.Length,
	ldr	r3, [r2, #220]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r2, [r2, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2311:
	mov	r0, r6	@, tmp212
	movw	r1, #:lower16:.LC319	@,
	movt	r1, #:upper16:.LC319	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2316:
	ldr	r0, [r7, #236]	@, <variable>.stChanMem_scd.VirAddr
	bl	KernelMunmap	@
	b	.L2233	@
.L2308:
	mov	r0, r6	@, tmp212
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #3103	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2240:
	mov	r2, r5	@, ChanID
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC323	@,
	movt	r1, #:upper16:.LC323	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2317:
	ldr	r0, [r7, #240]	@, <variable>.stChanMem_scd.PhyAddr
	bl	KernelMmap	@
	str	r0, [fp, #-224]	@, %sfp
	strb	sl, [r7, #232]	@ tmp269, <variable>.stChanMem_scd.IsCached
	b	.L2238	@
.L2328:
	ldr	r2, [sl, r5, asl #2]	@ temp.5797, s_pstVfmwChan
	mov	r0, r9	@, D.51576
.L2307:
	ldr	ip, [r2, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	movw	r1, #:lower16:.LC324	@,
	movt	r1, #:upper16:.LC324	@,
	str	ip, [sp, #0]	@ <variable>.stChanMem_scd.Length,
	ldr	r3, [r2, #236]	@, <variable>.stChanMem_scd.VirAddr
	ldr	r2, [r2, #240]	@, <variable>.stChanMem_scd.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2312:
	sub	r0, fp, #52	@,,
	bl	REAL8DEC_Support	@
	ldr	r0, [fp, #-52]	@ s32supportFlag, s32supportFlag
	cmp	r0, #0	@ s32supportFlag,
	beq	.L2219	@,
	ldr	r2, [r8, #0]	@ prephitmp.5677, <variable>.eVidStd
	b	.L2218	@
.L2309:
	mov	r0, r3	@, D.51424
	movw	r1, #:lower16:.LC5	@,
	mov	r2, #3104	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2319:
	ldr	r2, [r7, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	mov	r0, r3	@, tmp288
	movw	r1, #:lower16:.LC324	@,
	movt	r1, #:upper16:.LC324	@,
	str	r2, [sp, #0]	@ <variable>.stChanMem_vdh.Length,
	ldr	r3, [r7, #220]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r2, [r7, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2327:
	ldr	r2, [r7, #212]	@ <variable>.stChanMem.Length, <variable>.stChanMem.Length
	movw	r1, #:lower16:.LC324	@,
	ldr	r0, [fp, #-228]	@, %sfp
	movt	r1, #:upper16:.LC324	@,
	str	r2, [sp, #0]	@ <variable>.stChanMem.Length,
	ldr	r3, [r7, #204]	@, <variable>.stChanMem.VirAddr
	ldr	r2, [r7, #208]	@, <variable>.stChanMem.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2320:
	ldr	ip, [r7, #228]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	movw	r1, #:lower16:.LC324	@,
	ldr	r0, [fp, #-228]	@, %sfp
	movt	r1, #:upper16:.LC324	@,
	str	ip, [sp, #0]	@ <variable>.stChanMem_vdh.Length,
	ldr	r3, [r7, #220]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r2, [r7, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2321:
	ldr	lr, [r7, #244]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	mov	r0, r9	@, D.51529
	movw	r1, #:lower16:.LC324	@,
	movt	r1, #:upper16:.LC324	@,
	str	lr, [sp, #0]	@ <variable>.stChanMem_scd.Length,
	ldr	r3, [r7, #236]	@, <variable>.stChanMem_scd.VirAddr
	ldr	r2, [r7, #240]	@, <variable>.stChanMem_scd.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2326:
	mov	r0, r9	@, pVir
	mov	r2, r5	@, ChanID
	movw	r1, #:lower16:.LC325	@,
	movt	r1, #:upper16:.LC325	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2318:
	movw	r1, #:lower16:.LC322	@,
	ldr	r2, .L2329+8	@,
	movt	r1, #:upper16:.LC322	@,
	movw	r3, #3199	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2325:
	mov	r0, r3	@, temp.5768
	movw	r1, #:lower16:.LC322	@,
	ldr	r2, .L2329+8	@,
	movt	r1, #:upper16:.LC322	@,
	movw	r3, #3268	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51422,
	b	.L2211	@
.L2330:
	.align	2
.L2329:
	.word	.LANCHOR0+520
	.word	.LANCHOR4-3644
	.word	.LANCHOR1+440
	.fnend
	.size	VCTRL_ConfigChan, .-VCTRL_ConfigChan
	.align	2
	.global	VCTRL_StartChanWithOption
	.type	VCTRL_StartChanWithOption, %function
VCTRL_StartChanWithOption:
	.fnstart
.LFB1571:
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
	cmp	r0, #15	@ ChanID,
	mov	r5, r0	@ ChanID, ChanID
	mov	r7, r1	@ pChanMemVdh, pChanMemVdh
	bhi	.L2371	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp342,
	movt	r4, #:upper16:.LANCHOR0	@ tmp342,
	ldr	r3, [r4, r0, asl #2]	@ D.51157, s_pstVfmwChan
	cmp	r3, #0	@ D.51157,
	beq	.L2372	@,
	ldr	r6, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r6, #1	@ <variable>.s32IsOpen,
	bne	.L2373	@,
	ldr	r3, [r3, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #19	@ <variable>.eVidStd,
	beq	.L2374	@,
	bl	VCTRL_ResetChan	@
	ldr	r3, [r4, r5, asl #2]	@ temp.5936, s_pstVfmwChan
	ldr	r2, [r3, #228]	@, <variable>.stChanMem_vdh.Length
	ldr	r1, [r3, #220]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r0, [r3, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	MEM_DelMemRecord	@
	ldmia	r7, {r0, r1, r2, r3}	@ pChanMemVdh,,,,
	ldr	ip, [r4, r5, asl #2]	@ tmp175, s_pstVfmwChan
	add	ip, ip, #216	@ tmp174, tmp175,
	stmia	ip, {r0, r1, r2, r3}	@ tmp174,,,,
	ldr	ip, [r4, r5, asl #2]	@ temp.5938, s_pstVfmwChan
	ldr	r2, [ip, #228]	@, <variable>.stChanMem_vdh.Length
	ldr	r1, [ip, #220]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r0, [ip, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	MEM_AddMemRecord	@
	mov	r0, r5	@, ChanID
	bl	SM_Start	@
	ldr	r2, [r4, r5, asl #2]	@ tmp183, s_pstVfmwChan
	mov	ip, #0	@ tmp187,
	str	r6, [r2, #16]	@ <variable>.s32IsOpen, <variable>.s32IsRun
	ldr	r3, [r4, r5, asl #2]	@ tmp186, s_pstVfmwChan
	str	ip, [r3, #28]	@ tmp187, <variable>.s32StopSyntax
	ldr	r1, [r4, r5, asl #2]	@ tmp189, s_pstVfmwChan
	str	r6, [r1, #20]	@ <variable>.s32IsOpen, <variable>.s32IsInit
	ldr	r3, [r4, r5, asl #2]	@ temp.5945, s_pstVfmwChan
	ldr	r2, [r3, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r2, #0	@ <variable>.s32Priority,
	bne	.L2337	@,
	str	r6, [r3, #24]	@ <variable>.s32IsOpen, <variable>.s32Priority
	ldr	r1, [r4, #0]	@ D.51174, s_pstVfmwChan
	cmp	r1, #0	@ D.51174,
	beq	.L2375	@,
	ldr	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r3, #:lower16:.LANCHOR4	@ tmp343,
	movt	r3, #:upper16:.LANCHOR4	@ tmp343,
	movw	r2, #:lower16:g_ChanCtx	@ tmp344,
	movt	r2, #:upper16:g_ChanCtx	@ tmp344,
	str	r0, [r3, #-3580]	@ <variable>.s32Priority, PrioArray
	ldr	lr, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	str	lr, [r2, #0]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
.L2339:
	ldr	lr, [r4, #4]	@ temp.5950, s_pstVfmwChan
	ldr	ip, [r4, #8]	@ temp.5953, s_pstVfmwChan
	cmp	lr, #0	@ temp.5950,
	ldr	r1, [r4, #12]	@ temp.5956, s_pstVfmwChan
	streq	lr, [r3, #-3576]	@ temp.5950, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #4]	@ temp.5950, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-3576]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #4]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5953,
	streq	ip, [r3, #-3572]	@ temp.5953, PrioArray
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r2, #8]	@ temp.5953, g_ChanCtx.PriorByChanId
	ldr	lr, [r4, #16]	@ temp.5959, s_pstVfmwChan
	strne	r0, [r3, #-3572]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #8]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.5956,
	streq	r1, [r3, #-3568]	@ temp.5956, PrioArray
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r2, #12]	@ temp.5956, g_ChanCtx.PriorByChanId
	ldr	ip, [r4, #20]	@ temp.5962, s_pstVfmwChan
	strne	r0, [r3, #-3568]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #12]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5959,
	streq	lr, [r3, #-3564]	@ temp.5959, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #16]	@ temp.5959, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-3564]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #16]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5962,
	streq	ip, [r3, #-3560]	@ temp.5962, PrioArray
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r2, #20]	@ temp.5962, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-3560]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #20]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	r1, [r4, #24]	@ temp.5965, s_pstVfmwChan
	ldr	lr, [r4, #28]	@ temp.5968, s_pstVfmwChan
	cmp	r1, #0	@ temp.5965,
	ldr	ip, [r4, #32]	@ temp.5971, s_pstVfmwChan
	streq	r1, [r3, #-3556]	@ temp.5965, PrioArray
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r2, #24]	@ temp.5965, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-3556]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #24]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5968,
	streq	lr, [r3, #-3552]	@ temp.5968, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #28]	@ temp.5968, g_ChanCtx.PriorByChanId
	ldr	r1, [r4, #36]	@ temp.5974, s_pstVfmwChan
	strne	r0, [r3, #-3552]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #28]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5971,
	streq	ip, [r3, #-3548]	@ temp.5971, PrioArray
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r2, #32]	@ temp.5971, g_ChanCtx.PriorByChanId
	ldr	lr, [r4, #40]	@ temp.5977, s_pstVfmwChan
	strne	r0, [r3, #-3548]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #32]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.5974,
	streq	r1, [r3, #-3544]	@ temp.5974, PrioArray
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r2, #36]	@ temp.5974, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-3544]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #36]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5977,
	streq	lr, [r3, #-3540]	@ temp.5977, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #40]	@ temp.5977, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-3540]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #40]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	ip, [r4, #44]	@ temp.5980, s_pstVfmwChan
	ldr	r1, [r4, #48]	@ temp.5983, s_pstVfmwChan
	cmp	ip, #0	@ temp.5980,
	ldr	lr, [r4, #52]	@ temp.5986, s_pstVfmwChan
	streq	ip, [r2, #44]	@ temp.5980, g_ChanCtx.PriorByChanId
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r3, #-3536]	@ temp.5980, PrioArray
	strne	r0, [r3, #-3536]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #44]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.5983,
	streq	r1, [r2, #48]	@ temp.5983, g_ChanCtx.PriorByChanId
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r3, #-3532]	@ temp.5983, PrioArray
	ldr	ip, [r4, #56]	@ temp.5989, s_pstVfmwChan
	strne	r0, [r3, #-3532]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #48]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5986,
	streq	lr, [r2, #52]	@ temp.5986, g_ChanCtx.PriorByChanId
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r3, #-3528]	@ temp.5986, PrioArray
	ldr	r1, [r4, #60]	@ temp.5946, s_pstVfmwChan
	strne	r0, [r3, #-3528]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #52]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5989,
	streq	ip, [r2, #56]	@ temp.5989, g_ChanCtx.PriorByChanId
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r3, #-3524]	@ temp.5989, PrioArray
	strne	r0, [r3, #-3524]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #56]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.5946,
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r0, [r3, #-3520]	@ <variable>.s32Priority, PrioArray
	ldrne	r3, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	ldr	r0, .L2376	@,
	strne	r3, [r2, #60]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	streq	r1, [r2, #60]	@ temp.5946, g_ChanCtx.PriorByChanId
	streq	r1, [r3, #-3520]	@ temp.5946, PrioArray
	bl	VDMDRV_SetPriority	@
	mov	r0, r5	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
.L2337:
	mov	r0, r5	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	mov	r0, r5	@, ChanID
	bl	VCTRL_OpenHardware	@
	mov	r0, #0	@ D.51155,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L2375:
	movw	r3, #:lower16:.LANCHOR4	@ tmp343,
	movw	r2, #:lower16:g_ChanCtx	@ tmp344,
	movt	r3, #:upper16:.LANCHOR4	@ tmp343,
	movt	r2, #:upper16:g_ChanCtx	@ tmp344,
	str	r1, [r3, #-3580]	@ D.51174, PrioArray
	str	r1, [r2, #0]	@ D.51174, g_ChanCtx.PriorByChanId
	b	.L2339	@
.L2373:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2732	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC26	@,
	movt	r3, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51155,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L2371:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2730	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51155,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L2374:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2733	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC242	@,
	movt	r3, #:upper16:.LC242	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51155,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L2372:
	mov	r0, r3	@, D.51157
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2731	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC161	@,
	movt	r3, #:upper16:.LC161	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51155,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L2377:
	.align	2
.L2376:
	.word	.LANCHOR4-3580
	.fnend
	.size	VCTRL_StartChanWithOption, .-VCTRL_StartChanWithOption
	.align	2
	.global	VCTRL_DestroyChanWithOption
	.type	VCTRL_DestroyChanWithOption, %function
VCTRL_DestroyChanWithOption:
	.fnstart
.LFB1569:
	@ args = 0, pretend = 0, frame = 136
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #140
	sub	sp, sp, #140	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r5, #:lower16:.LANCHOR0	@ tmp223,
	movt	r5, #:upper16:.LANCHOR0	@ tmp223,
	mov	r4, r0	@ ChanID, ChanID
	add	r0, r5, #520	@, tmp223,
	bl	OSAL_SpinLockIRQ	@
	cmp	r4, #15	@ ChanID,
	bhi	.L2387	@,
	ldr	r6, [r5, r4, asl #2]	@ D.51086, s_pstVfmwChan
	cmp	r6, #0	@ D.51086,
	beq	.L2388	@,
	ldr	r3, [r6, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r3, #1	@ <variable>.s32IsOpen,
	bne	.L2389	@,
	movw	lr, #:lower16:g_FrameRate	@ tmp157,
	movw	r1, #:lower16:g_LastFrameRate	@ tmp159,
	movt	lr, #:upper16:g_FrameRate	@ tmp157,
	movt	r1, #:upper16:g_LastFrameRate	@ tmp159,
	movw	r7, #:lower16:g_LowDelaySeqIndex	@ tmp161,
	movt	r7, #:upper16:g_LowDelaySeqIndex	@ tmp161,
	mov	ip, #30	@ tmp158,
	mov	r2, #0	@ tmp162,
	str	ip, [r1, r4, asl #2]	@ tmp158, g_LastFrameRate
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	str	r2, [r7, r4, asl #2]	@ tmp162, g_LowDelaySeqIndex
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	str	ip, [lr, r4, asl #2]	@ tmp158, g_FrameRate
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r4	@, ChanID
	bl	VCTRL_StopChan	@
	subs	r7, r0, #0	@ ret,
	bne	.L2390	@,
	mov	r0, r4	@, ChanID
	movw	r9, #:lower16:.LANCHOR3	@ tmp168,
	movt	r9, #:upper16:.LANCHOR3	@ tmp168,
	bl	SCDDRV_ResetSCD	@
	add	r8, r9, r4, asl #2	@, tmp171, tmp168, ChanID,
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r4	@, ChanID
	bl	VCTRL_ResetChan	@
	bl	VDMDRV_ParamInit	@
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	str	r7, [r8, #-1460]	@ ret, g_DSPState
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, [r6, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r0, #4	@ <variable>.eVidStd,
	beq	.L2391	@,
.L2384:
	mov	r0, r4	@, ChanID
	sub	r8, fp, #140	@,,
	bl	VCTRL_UnInstallChan	@
	ldr	r3, [r5, r4, asl #2]	@ temp.6017, s_pstVfmwChan
	str	r8, [fp, #-168]	@, %sfp
	movw	r6, #:lower16:s_SmIIS	@ tmp194,
	add	ip, r3, #232	@, temp.6017,
	movt	r6, #:upper16:s_SmIIS	@ tmp194,
	ldr	r0, [r3, #272]	@ <variable>.s32SelfAllocChanMem_ctx, <variable>.s32SelfAllocChanMem_ctx
	add	r2, r3, #200	@ tmp187, temp.6017,
	str	ip, [fp, #-160]	@, %sfp
	add	ip, r4, r4, asl #1	@, tmp197, ChanID, ChanID,
	add	r9, r3, #248832	@ tmp185, temp.6017,
	add	r8, r3, #248	@ tmp189, temp.6017,
	str	r0, [fp, #-68]	@ <variable>.s32SelfAllocChanMem_ctx, ChanMem.s32SelfAllocChanMem_ctx
	add	ip, r6, ip, asl #4	@, tmp199, tmp194, tmp197,
	ldr	lr, [r3, #264]	@ <variable>.s32SelfAllocChanMem_vdh, <variable>.s32SelfAllocChanMem_vdh
	add	r6, r3, #148	@, temp.6017,
	sub	r0, fp, #124	@,,
	str	r6, [fp, #-164]	@, %sfp
	str	r0, [fp, #-172]	@, %sfp
	sub	r6, fp, #64	@,,
	str	lr, [fp, #-76]	@ <variable>.s32SelfAllocChanMem_vdh, ChanMem.s32SelfAllocChanMem_vdh
	sub	r0, fp, #92	@,,
	str	r6, [fp, #-180]	@, %sfp
	add	r1, r9, #456	@ tmp185, tmp185,
	str	r0, [fp, #-176]	@, %sfp
	add	r9, r3, #216	@ tmp191, temp.6017,
	ldr	r0, [r3, #268]	@ <variable>.s32SelfAllocChanMem_scd, <variable>.s32SelfAllocChanMem_scd
	sub	r7, fp, #156	@ tmp186,,
	sub	sl, fp, #108	@ tmp188,,
	mov	r6, #0	@ tmp212,
	movw	lr, #:lower16:s_pFspInst	@ tmp213,
	movt	lr, #:upper16:s_pFspInst	@ tmp213,
	str	r0, [fp, #-72]	@ <variable>.s32SelfAllocChanMem_scd, ChanMem.s32SelfAllocChanMem_scd
	ldr	r0, [r3, #1416]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	str	r1, [fp, #-48]	@ tmp185, ChanMem.pstChanFrmBuf
	str	r0, [fp, #-52]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, ChanMem.u32DynamicAllocEn
	ldmia	r2, {r0, r1, r2, r3}	@ tmp187,,,,
	stmia	r7, {r0, r1, r2, r3}	@ tmp186,,,,
	ldmia	r8, {r0, r1, r2, r3}	@ tmp189,,,,
	ldr	r8, [fp, #-168]	@, %sfp
	stmia	sl, {r0, r1, r2, r3}	@ tmp188,,,,
	ldmia	r9, {r0, r1, r2, r3}	@ tmp191,,,,
	stmia	r8, {r0, r1, r2, r3}	@,,,,
	ldr	r8, [fp, #-160]	@, %sfp
	ldmia	r8, {r0, r1, r2, r3}	@,,,,
	ldr	r8, [fp, #-172]	@, %sfp
	stmia	r8, {r0, r1, r2, r3}	@,,,,
	ldr	r8, [fp, #-176]	@, %sfp
	ldmia	ip, {r0, r1, r2, r3}	@ tmp199,,,,
	stmia	r8, {r0, r1, r2, r3}	@,,,,
	ldr	r3, [fp, #-164]	@, %sfp
	ldmia	r3, {r0, r1, r2}	@,,,
	str	r6, [ip, #40]	@ tmp212, <variable>.pSmInstArray
	ldr	r8, [fp, #-180]	@, %sfp
	str	r6, [lr, r4, asl #2]	@ tmp212, s_pFspInst
	str	r6, [r5, r4, asl #2]	@ tmp212, s_pstVfmwChan
	stmia	r8, {r0, r1, r2}	@,,,
	mov	r0, r4	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	mov	r0, r4	@, ChanID
	bl	VDMDRV_ResetVDH	@
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinUnLockIRQ	@
	bl	VCTRL_EnableAllInt	@
	ldr	r0, .L2392	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r4	@, ChanID
	mov	r1, r7	@, tmp186
	bl	VCTRL_FreeChanResource	@
	mov	r0, r6	@ D.51084, tmp212
.L2380:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L2391:
	ldr	r3, [r5, #80]	@ D.51099, g_SdecFunc.pfun_iMediaSoftDEC_Destroy
	cmp	r3, #0	@ D.51099,
	beq	.L2384	@,
	add	sl, r6, #250880	@, D.51086,
	add	r0, sl, #704	@,,
	blx	r3	@ D.51099
	b	.L2384	@
.L2389:
	movw	r1, #:lower16:.LC327	@,
	movw	r3, #:lower16:.LC329	@,
	movt	r1, #:upper16:.LC327	@,
	movt	r3, #:upper16:.LC329	@,
	movw	r2, #2514	@,
	mov	r0, #0	@,
.L2386:
	bl	dprint_vfmw	@
	bl	VCTRL_EnableAllInt	@
	add	r0, r5, #520	@, tmp223,
	bl	OSAL_SpinUnLockIRQ	@
	mvn	r0, #0	@ D.51084,
	b	.L2380	@
.L2390:
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinUnLockIRQ	@
	add	r0, r5, #520	@, tmp223,
	bl	OSAL_SpinUnLockIRQ	@
	mvn	r0, #0	@ D.51084,
	b	.L2380	@
.L2387:
	movw	r1, #:lower16:.LC327	@,
	movw	r3, #:lower16:.LC6	@,
	mov	r2, #2496	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC327	@,
	movt	r3, #:upper16:.LC6	@,
	b	.L2386	@
.L2388:
	movw	r1, #:lower16:.LC327	@,
	movw	r3, #:lower16:.LC328	@,
	mov	r0, r6	@, D.51086
	movw	r2, #2503	@,
	movt	r1, #:upper16:.LC327	@,
	movt	r3, #:upper16:.LC328	@,
	b	.L2386	@
.L2393:
	.align	2
.L2392:
	.word	.LANCHOR0+520
	.fnend
	.size	VCTRL_DestroyChanWithOption, .-VCTRL_DestroyChanWithOption
	.align	2
	.global	VCTRL_DestroyChan
	.type	VCTRL_DestroyChan, %function
VCTRL_DestroyChan:
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
	bl	VCTRL_DestroyChanWithOption	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_DestroyChan, .-VCTRL_DestroyChan
	.align	2
	.global	VCTRL_CloseVfmw
	.type	VCTRL_CloseVfmw, %function
VCTRL_CloseVfmw:
	.fnstart
.LFB1549:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp185,
	movt	r4, #:upper16:.LANCHOR0	@ tmp185,
	ldr	r3, [r4, #104]	@ s_VfmwCTrl.s32IsVCTRLOpen, s_VfmwCTrl.s32IsVCTRLOpen
	cmp	r3, #1	@ s_VfmwCTrl.s32IsVCTRLOpen,
	mvnne	r0, #0	@ D.50215,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	ldr	r0, [r4, #0]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r0, #0	@ s_pstVfmwChan,
	beq	.L2399	@,
	mov	r0, #0	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2399:
	ldr	r1, [r4, #4]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r1, #0	@ s_pstVfmwChan,
	beq	.L2400	@,
	mov	r0, #1	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2400:
	ldr	r2, [r4, #8]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r2, #0	@ s_pstVfmwChan,
	beq	.L2401	@,
	mov	r0, #2	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2401:
	ldr	r5, [r4, #12]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r5, #0	@ s_pstVfmwChan,
	beq	.L2402	@,
	mov	r0, #3	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2402:
	ldr	ip, [r4, #16]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	ip, #0	@ s_pstVfmwChan,
	beq	.L2403	@,
	mov	r0, #4	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2403:
	ldr	lr, [r4, #20]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	lr, #0	@ s_pstVfmwChan,
	beq	.L2404	@,
	mov	r0, #5	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2404:
	ldr	r3, [r4, #24]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	beq	.L2405	@,
	mov	r0, #6	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2405:
	ldr	r0, [r4, #28]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r0, #0	@ s_pstVfmwChan,
	beq	.L2406	@,
	mov	r0, #7	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2406:
	ldr	r1, [r4, #32]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r1, #0	@ s_pstVfmwChan,
	beq	.L2407	@,
	mov	r0, #8	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2407:
	ldr	r2, [r4, #36]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r2, #0	@ s_pstVfmwChan,
	beq	.L2408	@,
	mov	r0, #9	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2408:
	ldr	r5, [r4, #40]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r5, #0	@ s_pstVfmwChan,
	beq	.L2409	@,
	mov	r0, #10	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2409:
	ldr	ip, [r4, #44]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	ip, #0	@ s_pstVfmwChan,
	beq	.L2410	@,
	mov	r0, #11	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2410:
	ldr	lr, [r4, #48]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	lr, #0	@ s_pstVfmwChan,
	beq	.L2411	@,
	mov	r0, #12	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2411:
	ldr	r3, [r4, #52]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	beq	.L2412	@,
	mov	r0, #13	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2412:
	ldr	r0, [r4, #56]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r0, #0	@ s_pstVfmwChan,
	beq	.L2413	@,
	mov	r0, #14	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2413:
	ldr	r1, [r4, #60]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r1, #0	@ s_pstVfmwChan,
	beq	.L2414	@,
	mov	r0, #15	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2414:
	bl	FSP_Exit	@
	mov	r5, #0	@ i,
	mov	r2, #3	@ tmp171,
	str	r2, [r4, #144]	@ tmp171, s_VfmwCTrl.eTaskCommand
	b	.L2416	@
.L2421:
	bl	msleep	@
	ldr	r3, [r4, #140]	@ s_VfmwCTrl.eTaskState, s_VfmwCTrl.eTaskState
	mov	r0, #10	@,
	cmp	r3, #0	@ s_VfmwCTrl.eTaskState,
	beq	.L2415	@,
	bl	msleep	@
	cmp	r5, #50	@ i,
	beq	.L2415	@,
.L2416:
	ldr	ip, [r4, #140]	@ s_VfmwCTrl.eTaskState, s_VfmwCTrl.eTaskState
	add	r5, r5, #1	@ tmp187, i,
	mov	r0, #10	@,
	add	r5, r5, #1	@ i, tmp187,
	cmp	ip, #0	@ s_VfmwCTrl.eTaskState,
	bne	.L2421	@,
.L2415:
	mov	r1, #64	@,
	ldr	r0, .L2422	@,
	mov	r5, #0	@ tmp175,
	str	r5, [r4, #144]	@ tmp175, s_VfmwCTrl.eTaskCommand
	bl	__memzero	@
	ldr	r0, .L2422+4	@,
	bl	CloseDrivers	@
	bl	DBG_DestroyTracer	@
	mov	r0, r5	@ D.50215, tmp175
	str	r5, [r4, #104]	@ tmp175, s_VfmwCTrl.s32IsVCTRLOpen
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L2423:
	.align	2
.L2422:
	.word	.LANCHOR3-1460
	.word	.LANCHOR0+160
	.fnend
	.size	VCTRL_CloseVfmw, .-VCTRL_CloseVfmw
	.align	2
	.global	VCTRL_CreateChanWithOption
	.type	VCTRL_CreateChanWithOption, %function
VCTRL_CreateChanWithOption:
	.fnstart
.LFB1567:
	@ args = 0, pretend = 0, frame = 248
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #260
	sub	sp, sp, #260	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	sub	r7, fp, #72	@ tmp718,,
	sub	sl, fp, #88	@ tmp717,,
	mov	r5, r0	@ eCapLevel, eCapLevel
	mov	r4, r1	@ pChanOption, pChanOption
	mov	r0, r7	@, tmp718
	mov	r1, #16	@,
	sub	r6, fp, #104	@ tmp716,,
	mov	r8, r2	@ flag, flag
	str	r3, [fp, #-264]	@ OneChanMemFlag, %sfp
	bl	__memzero	@
	sub	r0, fp, #232	@,,
	mov	r1, #16	@,
	str	r0, [fp, #-272]	@, %sfp
	mov	r0, sl	@, tmp717
	bl	__memzero	@
	mov	r0, r6	@, tmp716
	mov	r1, #16	@,
	bl	__memzero	@
	sub	r0, fp, #232	@,,
	mov	r1, #112	@,
	bl	__memzero	@
	rsbs	r0, r8, #1	@ tmp192, flag
	movcc	r0, #0	@ tmp192
	cmp	r5, #25	@ eCapLevel,
	movw	r1, #:lower16:4780696	@ tmp732,
	movt	r1, #:upper16:4780696	@ tmp732,
	movw	r2, #:lower16:11613560	@ tmp731,
	moveq	r0, #0	@, tmp192,
	cmp	r5, #26	@ eCapLevel,
	movt	r2, #:upper16:11613560	@ tmp731,
	movw	r3, #:lower16:.LANCHOR4	@ tmp185,
	movne	r2, r1	@ tmp731, tmp732
	movt	r3, #:upper16:.LANCHOR4	@ tmp185,
	cmp	r0, #0	@ tmp192,
	str	r2, [fp, #-252]	@ tmp731, %sfp
	str	r4, [r3, #-3516]	@ pChanOption, pOption
	bne	.L2515	@,
	ldr	r3, [r4, #4]	@ D.50795, <variable>.Purpose
	cmp	r3, #2	@ D.50795,
	bhi	.L2516	@,
	beq	.L2517	@,
	cmp	r3, #1	@ D.50795,
	beq	.L2518	@,
.L2432:
	ldr	lr, [r4, #132]	@ <variable>.u32DynamicFrameStoreAllocEn, <variable>.u32DynamicFrameStoreAllocEn
	mov	r3, r8	@, flag
	mov	r0, r5	@, eCapLevel
	mov	r1, r4	@, pChanOption
	cmp	lr, #1	@ <variable>.u32DynamicFrameStoreAllocEn,
	sub	r2, fp, #56	@,,
	movhi	lr, #0	@ tmp212,
	strhi	lr, [r4, #132]	@ tmp212, <variable>.u32DynamicFrameStoreAllocEn
	bl	VCTRL_GetChanMemSizeWithOption	@
	subs	ip, r0, #0	@ D.50836,
	bne	.L2519	@,
	ldr	r3, [r4, #8]	@ D.50840, <variable>.MemAllocMode
	cmp	r3, #1	@ D.50840,
	beq	.L2520	@,
	cmp	r3, #2	@ D.50840,
	beq	.L2521	@,
	cmp	r3, #3	@ D.50840,
	bne	.L2454	@,
	ldr	lr, [r4, #120]	@ <variable>.MemDetail.ChanMemCtx.VirAddr, <variable>.MemDetail.ChanMemCtx.VirAddr
	cmp	lr, #0	@ <variable>.MemDetail.ChanMemCtx.VirAddr,
	beq	.L2455	@,
	ldr	r2, [r4, #124]	@ <variable>.MemDetail.ChanMemCtx.Length, <variable>.MemDetail.ChanMemCtx.Length
	cmp	r2, #0	@ <variable>.MemDetail.ChanMemCtx.Length,
	bne	.L2456	@,
.L2455:
	movw	r0, #:lower16:.LC335	@,
	mov	r1, #0	@,
	movt	r0, #:upper16:.LC335	@,
	sub	r3, fp, #120	@,,
	ldr	r2, [fp, #-48]	@, DetailMemSize.ChanCtxDetailMem
	mov	r6, #1	@ tmp284,
	str	r6, [sp, #0]	@ tmp284,
	bl	MEM_AllocMemBlock	@
	cmp	r0, #0	@,
	bne	.L2522	@,
	ldr	r1, [fp, #-116]	@, MemRecord.VirAddr
	ldr	r0, [fp, #-112]	@, MemRecord.PhyAddr
	ldr	r2, [fp, #-108]	@, MemRecord.Length
	str	r6, [fp, #-256]	@ tmp284, %sfp
	bl	MEM_AddMemRecord	@
	ldr	r0, [fp, #-112]	@ MemRecord.PhyAddr, MemRecord.PhyAddr
	ldr	r3, [fp, #-116]	@ MemRecord.VirAddr, MemRecord.VirAddr
	ldr	r1, [fp, #-108]	@ MemRecord.Length, MemRecord.Length
	str	r0, [fp, #-104]	@ MemRecord.PhyAddr, ChanMemCtx.PhyAddr
	str	r3, [fp, #-100]	@ MemRecord.VirAddr, ChanMemCtx.VirAddr
	str	r1, [fp, #-96]	@ MemRecord.Length, ChanMemCtx.Length
.L2458:
	ldr	ip, [r4, #88]	@ <variable>.MemDetail.ChanMemVdh.VirAddr, <variable>.MemDetail.ChanMemVdh.VirAddr
	cmp	ip, #0	@ <variable>.MemDetail.ChanMemVdh.VirAddr,
	beq	.L2460	@,
	ldr	r1, [r4, #92]	@ <variable>.MemDetail.ChanMemVdh.Length, <variable>.MemDetail.ChanMemVdh.Length
	cmp	r1, #0	@ <variable>.MemDetail.ChanMemVdh.Length,
	beq	.L2460	@,
	add	r3, r4, #84	@ tmp319, pChanOption,
	ldr	lr, [r4, #132]	@ <variable>.u32DynamicFrameStoreAllocEn, <variable>.u32DynamicFrameStoreAllocEn
	ldmia	r3, {r0, r1, r2, r3}	@ tmp319,,,,
	cmp	lr, #1	@ <variable>.u32DynamicFrameStoreAllocEn,
	stmia	r7, {r0, r1, r2, r3}	@ tmp718,,,,
	beq	.L2466	@,
	ldr	r2, [fp, #-64]	@ prephitmp.6186, ChanMemVDH.Length
	ldr	ip, [fp, #-56]	@ prephitmp.6187, DetailMemSize.VdhDetailMem
	cmp	r2, ip	@ prephitmp.6186, prephitmp.6187
	blt	.L2523	@,
.L2467:
	ldr	r0, [fp, #-72]	@, ChanMemVDH.PhyAddr
	mov	ip, #0	@,
	ldr	r1, [fp, #-68]	@, ChanMemVDH.VirAddr
	str	ip, [fp, #-240]	@, %sfp
	bl	MEM_AddMemRecord	@
.L2465:
	ldr	r0, [r4, #104]	@ <variable>.MemDetail.ChanMemScd.VirAddr, <variable>.MemDetail.ChanMemScd.VirAddr
	cmp	r0, #0	@ <variable>.MemDetail.ChanMemScd.VirAddr,
	beq	.L2469	@,
	ldr	r2, [r4, #108]	@ <variable>.MemDetail.ChanMemScd.Length, <variable>.MemDetail.ChanMemScd.Length
	cmp	r2, #0	@ <variable>.MemDetail.ChanMemScd.Length,
	beq	.L2469	@,
	add	r7, r4, #100	@ tmp344, pChanOption,
	ldr	ip, [r4, #4]	@ temp.6211, <variable>.Purpose
	ldmia	r7, {r0, r1, r2, r3}	@ tmp344,,,,
	cmp	ip, #2	@ temp.6211,
	stmia	sl, {r0, r1, r2, r3}	@ tmp717,,,,
	beq	.L2475	@,
	ldr	r1, [fp, #-84]	@ temp.6212, ChanMemScd.VirAddr
	cmp	r1, #0	@ temp.6212,
	beq	.L2476	@,
	ldr	r2, [fp, #-80]	@ prephitmp.6104, ChanMemScd.Length
	ldr	r3, [fp, #-52]	@ DetailMemSize.ScdDetailMem, DetailMemSize.ScdDetailMem
	cmp	r2, r3	@ prephitmp.6104, DetailMemSize.ScdDetailMem
	bge	.L2477	@,
.L2476:
	cmp	ip, #1	@ temp.6211,
	ldrne	r2, [fp, #-80]	@ prephitmp.6104, ChanMemScd.Length
	beq	.L2524	@,
.L2477:
	ldr	r0, [fp, #-88]	@, ChanMemScd.PhyAddr
	mov	r8, #0	@,
	str	r8, [fp, #-260]	@, %sfp
	bl	MEM_AddMemRecord	@
.L2445:
	movw	r7, #:lower16:.LANCHOR0	@ tmp720,
	movt	r7, #:upper16:.LANCHOR0	@ tmp720,
	add	r0, r7, #520	@, tmp720,
	bl	OSAL_SpinLockIRQ	@
	bl	VCTRL_MaskAllInt	@
	ldr	r3, [r7, #0]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	beq	.L2514	@,
	ldr	r1, [r7, #4]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r1, #0	@ s_pstVfmwChan,
	moveq	lr, #1	@,
	streq	lr, [fp, #-244]	@, %sfp
	moveq	r6, lr	@ ChanID.6359,
	beq	.L2482	@,
	ldr	ip, [r7, #8]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	ip, #0	@ s_pstVfmwChan,
	moveq	r0, #2	@,
	streq	r0, [fp, #-244]	@, %sfp
	moveq	r6, r0	@ ChanID.6359,
	beq	.L2482	@,
	ldr	r3, [r7, #12]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	moveq	r1, #3	@,
	streq	r1, [fp, #-244]	@, %sfp
	moveq	r6, r1	@ ChanID.6359,
	beq	.L2482	@,
	ldr	r2, [r7, #16]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r2, #0	@ s_pstVfmwChan,
	moveq	r2, #4	@,
	streq	r2, [fp, #-244]	@, %sfp
	moveq	r6, r2	@ ChanID.6359,
	beq	.L2482	@,
	ldr	ip, [r7, #20]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	ip, #0	@ s_pstVfmwChan,
	addeq	ip, ip, #5	@,,
	streq	ip, [fp, #-244]	@, %sfp
	moveq	r6, ip	@ ChanID.6359,
	beq	.L2482	@,
	ldr	r3, [r7, #24]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	moveq	r8, #6	@,
	streq	r8, [fp, #-244]	@, %sfp
	moveq	r6, r8	@ ChanID.6359,
	beq	.L2482	@,
	ldr	ip, [r7, #28]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	ip, #0	@ s_pstVfmwChan,
	moveq	r9, #7	@,
	streq	r9, [fp, #-244]	@, %sfp
	moveq	r6, r9	@ ChanID.6359,
	beq	.L2482	@,
	ldr	r9, [r7, #32]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r9, #0	@ s_pstVfmwChan,
	moveq	ip, #8	@,
	streq	ip, [fp, #-244]	@, %sfp
	moveq	r6, ip	@ ChanID.6359,
	beq	.L2482	@,
	ldr	r3, [r7, #36]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	moveq	lr, #9	@,
	streq	lr, [fp, #-244]	@, %sfp
	moveq	r6, lr	@ ChanID.6359,
	beq	.L2482	@,
	ldr	lr, [r7, #40]	@ s_pstVfmwChan, s_pstVfmwChan
	movw	r6, #:lower16:.LANCHOR0	@ tmp372,
	movt	r6, #:upper16:.LANCHOR0	@ tmp372,
	cmp	lr, #0	@ s_pstVfmwChan,
	moveq	r0, #10	@,
	streq	r0, [fp, #-244]	@, %sfp
	moveq	r6, r0	@ ChanID.6359,
	beq	.L2482	@,
	ldr	r0, [r6, #44]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r0, #0	@ s_pstVfmwChan,
	moveq	r1, #11	@,
	streq	r1, [fp, #-244]	@, %sfp
	moveq	r6, r1	@ ChanID.6359,
	beq	.L2482	@,
	ldr	r1, [r6, #48]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r1, #0	@ s_pstVfmwChan,
	moveq	r2, #12	@,
	streq	r2, [fp, #-244]	@, %sfp
	moveq	r6, r2	@ ChanID.6359,
	beq	.L2482	@,
	ldr	r3, [r6, #52]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	beq	.L2525	@,
	ldr	r2, [r6, #56]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r2, #0	@ s_pstVfmwChan,
	moveq	r8, #14	@,
	streq	r8, [fp, #-244]	@, %sfp
	moveq	r6, r8	@ ChanID.6359,
	beq	.L2482	@,
	ldr	ip, [r6, #60]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	ip, #0	@ s_pstVfmwChan,
	beq	.L2497	@,
	mov	r2, #16	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC347	@,
	movt	r1, #:upper16:.LC347	@,
	bl	dprint_vfmw	@
	mvn	r9, #0	@,
	str	r9, [fp, #-244]	@, %sfp
	bl	VCTRL_EnableAllInt	@
	add	r0, r6, #520	@, tmp372,
	bl	OSAL_SpinUnLockIRQ	@
.L2428:
	ldr	r0, [fp, #-244]	@, %sfp
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L2518:
	ldr	r1, [r4, #36]	@ <variable>.s32MaxRefFrameNum, <variable>.s32MaxRefFrameNum
	cmp	r1, #0	@ <variable>.s32MaxRefFrameNum,
	blt	.L2433	@,
	ldr	r0, [r4, #12]	@ <variable>.s32MaxWidth, <variable>.s32MaxWidth
	cmp	r0, #31	@ <variable>.s32MaxWidth,
	ble	.L2433	@,
	ldr	ip, [r4, #16]	@ <variable>.s32MaxHeight, <variable>.s32MaxHeight
	cmp	ip, #31	@ <variable>.s32MaxHeight,
	ble	.L2433	@,
	ldr	lr, [r4, #60]	@ <variable>.s32SCDBufSize, <variable>.s32SCDBufSize
	cmp	lr, #262144	@ <variable>.s32SCDBufSize,
	blt	.L2433	@,
	ldr	r3, [r4, #48]	@ D.50820, <variable>.s32SupportH264
	cmp	r3, #1	@ D.50820,
	beq	.L2526	@,
	cmp	r3, #2	@ D.50820,
	bne	.L2432	@,
	ldr	r2, [r4, #20]	@ <variable>.s32MaxSliceNum, <variable>.s32MaxSliceNum
	cmp	r2, #0	@ <variable>.s32MaxSliceNum,
	ble	.L2433	@,
	ldr	r1, [r4, #24]	@ <variable>.s32MaxVpsNum, <variable>.s32MaxVpsNum
	cmp	r1, #0	@ <variable>.s32MaxVpsNum,
	ble	.L2433	@,
.L2512:
	ldr	r0, [r4, #28]	@ <variable>.s32MaxSpsNum, <variable>.s32MaxSpsNum
	cmp	r0, #0	@ <variable>.s32MaxSpsNum,
	ble	.L2433	@,
	ldr	ip, [r4, #32]	@ <variable>.s32MaxPpsNum, <variable>.s32MaxPpsNum
	cmp	ip, #0	@ <variable>.s32MaxPpsNum,
	bgt	.L2432	@,
.L2433:
	movw	r1, #:lower16:.LC23	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC23	@,
	mvn	r7, #0	@,
	str	r7, [fp, #-244]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2428	@
.L2456:
	add	r3, r4, #116	@ tmp294, pChanOption,
	ldr	lr, [fp, #-48]	@ DetailMemSize.ChanCtxDetailMem, DetailMemSize.ChanCtxDetailMem
	ldmia	r3, {r0, r1, r2, r3}	@ tmp294,,,,
	stmia	r6, {r0, r1, r2, r3}	@ tmp716,,,,
	ldr	r2, [fp, #-96]	@ temp.6173, ChanMemCtx.Length
	cmp	r2, lr	@ temp.6173, DetailMemSize.ChanCtxDetailMem
	blt	.L2527	@,
	ldr	r0, [fp, #-104]	@, ChanMemCtx.PhyAddr
	ldr	r1, [fp, #-100]	@, ChanMemCtx.VirAddr
	str	ip, [fp, #-256]	@ D.50836, %sfp
	bl	MEM_AddMemRecord	@
	b	.L2458	@
.L2460:
	ldr	r0, [r4, #132]	@ <variable>.u32DynamicFrameStoreAllocEn, <variable>.u32DynamicFrameStoreAllocEn
	cmp	r0, #1	@ <variable>.u32DynamicFrameStoreAllocEn,
	beq	.L2462	@,
	mov	lr, #0	@ tmp306,
	movw	r0, #:lower16:.LC337	@,
	mov	r1, lr	@, tmp306
	movt	r0, #:upper16:.LC337	@,
	sub	r3, fp, #120	@,,
	ldr	r2, [fp, #-56]	@, DetailMemSize.VdhDetailMem
	str	lr, [sp, #0]	@ tmp306,
	bl	MEM_AllocMemBlock	@
	cmp	r0, #0	@,
	bne	.L2528	@,
	ldr	r2, [fp, #-108]	@, MemRecord.Length
	mov	r7, #1	@,
	ldr	r0, [fp, #-112]	@, MemRecord.PhyAddr
	ldr	r1, [fp, #-116]	@, MemRecord.VirAddr
	str	r7, [fp, #-240]	@, %sfp
	bl	MEM_AddMemRecord	@
	ldr	ip, [fp, #-112]	@ MemRecord.PhyAddr, MemRecord.PhyAddr
	ldr	r2, [fp, #-116]	@ MemRecord.VirAddr, MemRecord.VirAddr
	ldr	r3, [fp, #-108]	@ MemRecord.Length, MemRecord.Length
	str	ip, [fp, #-72]	@ MemRecord.PhyAddr, ChanMemVDH.PhyAddr
	str	r2, [fp, #-68]	@ MemRecord.VirAddr, ChanMemVDH.VirAddr
	str	r3, [fp, #-64]	@ MemRecord.Length, ChanMemVDH.Length
	b	.L2465	@
.L2517:
	ldr	r3, [r4, #68]	@ <variable>.s32SlotWidth, <variable>.s32SlotWidth
	cmp	r3, #0	@ <variable>.s32SlotWidth,
	beq	.L2431	@,
	ldr	r2, [r4, #72]	@ <variable>.s32SlotHeight, <variable>.s32SlotHeight
	cmp	r2, #0	@ <variable>.s32SlotHeight,
	bne	.L2432	@,
.L2431:
	movw	r1, #:lower16:.LC22	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC22	@,
	mvn	r5, #0	@,
	str	r5, [fp, #-244]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2428	@
.L2520:
	add	r3, r4, #84	@ tmp217, pChanOption,
	add	lr, r4, #100	@ tmp219, pChanOption,
	add	ip, r4, #116	@ tmp221, pChanOption,
	ldmia	r3, {r0, r1, r2, r3}	@ tmp217,,,,
	stmia	r7, {r0, r1, r2, r3}	@ tmp718,,,,
	ldmia	lr, {r0, r1, r2, r3}	@ tmp219,,,,
	stmia	sl, {r0, r1, r2, r3}	@ tmp717,,,,
	ldmia	ip, {r0, r1, r2, r3}	@ tmp221,,,,
	stmia	r6, {r0, r1, r2, r3}	@ tmp716,,,,
	ldr	r3, [fp, #-100]	@ ChanMemCtx.VirAddr, ChanMemCtx.VirAddr
	cmp	r3, #0	@ ChanMemCtx.VirAddr,
	beq	.L2438	@,
	ldr	r1, [fp, #-48]	@ DetailMemSize.ChanCtxDetailMem, DetailMemSize.ChanCtxDetailMem
	ldr	r2, [fp, #-96]	@ ChanMemCtx.Length, ChanMemCtx.Length
	cmp	r2, r1	@ ChanMemCtx.Length, DetailMemSize.ChanCtxDetailMem
	blt	.L2438	@,
	ldr	r0, [fp, #-84]	@ ChanMemScd.VirAddr, ChanMemScd.VirAddr
	cmp	r0, #0	@ ChanMemScd.VirAddr,
	beq	.L2440	@,
	ldr	lr, [fp, #-52]	@ DetailMemSize.ScdDetailMem, DetailMemSize.ScdDetailMem
	ldr	ip, [fp, #-80]	@ ChanMemScd.Length, ChanMemScd.Length
	cmp	ip, lr	@ ChanMemScd.Length, DetailMemSize.ScdDetailMem
	blt	.L2440	@,
.L2441:
	ldr	r1, [fp, #-68]	@ D.50861, ChanMemVDH.VirAddr
	cmp	r1, #0	@ D.50861,
	beq	.L2442	@,
	ldr	r2, [fp, #-64]	@ D.50863, ChanMemVDH.Length
	ldr	r0, [fp, #-56]	@ DetailMemSize.VdhDetailMem, DetailMemSize.VdhDetailMem
	cmp	r2, r0	@ D.50863, DetailMemSize.VdhDetailMem
	blt	.L2442	@,
	ldr	r0, [fp, #-72]	@, ChanMemVDH.PhyAddr
	bl	MEM_AddMemRecord	@
	sub	r0, fp, #104
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_AddMemRecord	@
	ldr	r7, [r4, #4]	@ <variable>.Purpose, <variable>.Purpose
	cmp	r7, #2	@ <variable>.Purpose,
	beq	.L2529	@,
	ldr	r0, [fp, #-88]	@, ChanMemScd.PhyAddr
	mov	lr, #0	@,
	ldr	r1, [fp, #-84]	@, ChanMemScd.VirAddr
	mov	ip, #0	@,
	ldr	r2, [fp, #-80]	@, ChanMemScd.Length
	str	lr, [fp, #-256]	@, %sfp
	str	lr, [fp, #-260]	@, %sfp
	str	ip, [fp, #-240]	@, %sfp
	bl	MEM_AddMemRecord	@
	b	.L2445	@
.L2462:
	mov	r1, #0	@ tmp315,
	str	r1, [fp, #-72]	@ tmp315, ChanMemVDH.PhyAddr
	str	r1, [fp, #-68]	@ tmp315, ChanMemVDH.VirAddr
	str	r1, [fp, #-240]	@ tmp315, %sfp
	str	r1, [fp, #-64]	@ tmp315, ChanMemVDH.Length
	b	.L2465	@
.L2440:
	ldr	r0, [r4, #4]	@ <variable>.Purpose, <variable>.Purpose
	cmp	r0, #1	@ <variable>.Purpose,
	bne	.L2441	@,
	movw	r1, #:lower16:.LC333	@,
	movw	r2, #1880	@,
	movt	r1, #:upper16:.LC333	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@,
	str	r3, [fp, #-244]	@, %sfp
	b	.L2428	@
.L2529:
	mov	r1, #0	@,
	str	r1, [fp, #-256]	@, %sfp
	str	r1, [fp, #-260]	@, %sfp
	str	r1, [fp, #-240]	@, %sfp
	b	.L2445	@
.L2526:
	ldr	r3, [r4, #20]	@ <variable>.s32MaxSliceNum, <variable>.s32MaxSliceNum
	cmp	r3, #0	@ <variable>.s32MaxSliceNum,
	bgt	.L2512	@,
	b	.L2433	@
.L2497:
	mov	r8, #15	@,
	str	r8, [fp, #-244]	@, %sfp
	mov	r6, r8	@ ChanID.6359,
.L2482:
	ldr	lr, [fp, #-252]	@, %sfp
	movw	r9, #:lower16:g_FrameRate	@ tmp387,
	ldr	r0, [fp, #-100]	@ prephitmp.6122, ChanMemCtx.VirAddr
	movt	r9, #:upper16:g_FrameRate	@ tmp387,
	sub	r1, lr, #207872	@ __n,,
	movw	r3, #:lower16:g_LastFrameRate	@ tmp389,
	sub	r1, r1, #8	@ __n, __n,
	movt	r3, #:upper16:g_LastFrameRate	@ tmp389,
	cmp	r1, #0	@ __n,
	mov	sl, #30	@ tmp388,
	movw	r8, #:lower16:.LANCHOR0	@ tmp391,
	str	r0, [r7, r6, asl #2]	@ prephitmp.6122, s_pstVfmwChan
	str	sl, [r3, r6, asl #2]	@ tmp388, g_LastFrameRate
	movt	r8, #:upper16:.LANCHOR0	@ tmp391,
	str	sl, [r9, r6, asl #2]	@ tmp388, g_FrameRate
	beq	.L2498	@,
	bl	__memzero	@
	ldr	r2, [fp, #-244]	@, %sfp
	ldr	r0, [r8, r2, asl #2]	@ prephitmp.6122, s_pstVfmwChan
.L2498:
	add	r9, r0, #1280	@, prephitmp.6122,
	mov	r1, r4	@, pChanOption
	add	r0, r9, #4	@,,
	mov	r2, #164	@,
	bl	memcpy	@
	ldr	r3, [r7, r6, asl #2]	@ tmp401, s_pstVfmwChan
	ldr	ip, [fp, #-252]	@, %sfp
	movw	r8, #:lower16:s_SmIIS	@,
	movt	r8, #:upper16:s_SmIIS	@,
	mov	r9, #0	@ tmp408,
	add	r0, r6, r6, asl #1	@, tmp429, ChanID.6359, ChanID.6359,
	mov	r1, #19	@ tmp416,
	str	ip, [r3, #1224]	@, <variable>.stSynExtraData.s32BasicCtxSize
	movw	r2, #:lower16:251576	@ tmp419,
	ldr	sl, [r7, r6, asl #2]	@ tmp403, s_pstVfmwChan
	add	lr, r8, r0, asl #4	@, tmp431,, tmp429,
	str	r8, [fp, #-248]	@, %sfp
	movt	r2, #:upper16:251576	@ tmp419,
	movw	r3, #:lower16:s_pFspInst	@ tmp435,
	movt	r3, #:upper16:s_pFspInst	@ tmp435,
	str	r5, [sl, #40]	@ eCapLevel, <variable>.eChanCapLevel
	mov	r0, r6	@, ChanID.6359
	ldr	ip, [r7, r6, asl #2]	@ tmp405, s_pstVfmwChan
	mvn	sl, #0	@ tmp727,
	str	r9, [fp, #-292]	@ tmp408, %sfp
	str	r5, [ip, #584]	@ eCapLevel, <variable>.stSynExtraData.eCapLevel
	ldr	r5, [r7, r6, asl #2]	@ tmp407, s_pstVfmwChan
	str	r9, [r5, #1240]	@ tmp408, <variable>.stSynExtraData.s32MoreGapEnable
	ldr	r8, [r7, r6, asl #2]	@ tmp410, s_pstVfmwChan
	str	r6, [r8, #8]	@ ChanID.6359, <variable>.s32ChanID
	ldr	r5, [r4, #0]	@ <variable>.eAdapterType, <variable>.eAdapterType
	ldr	ip, [r7, r6, asl #2]	@ tmp412, s_pstVfmwChan
	str	r5, [ip, #36]	@ <variable>.eAdapterType, <variable>.eAdapterType
	ldr	r8, [r7, r6, asl #2]	@ tmp415, s_pstVfmwChan
	str	r1, [r8, #544]	@ tmp416, <variable>.eVidStd
	ldr	r5, [r7, r6, asl #2]	@ tmp418, s_pstVfmwChan
	str	r1, [r5, r2]	@ tmp416, <variable>.stSynCtx.eVidStd
	ldr	ip, [r7, r6, asl #2]	@ tmp422, s_pstVfmwChan
	str	r9, [ip, #32]	@ tmp408, <variable>.MatchVdhIdPlus1
	ldr	r1, [r7, r6, asl #2]	@ temp.6261, s_pstVfmwChan
	add	r5, r1, #205824	@ tmp437, temp.6261,
	add	r2, r1, #1488	@ tmp433, temp.6261,
	add	r8, r2, #8	@ tmp433, tmp433,
	add	ip, r5, #568	@ tmp437, tmp437,
	str	r8, [lr, #40]	@ tmp433, <variable>.pSmInstArray
	movw	r5, #:lower16:251540	@,
	str	ip, [r3, r6, asl #2]	@ tmp437, s_pFspInst
	movt	r5, #:upper16:251540	@,
	bl	VCTRL_ResetChan	@
	ldr	r2, [fp, #-240]	@, %sfp
	ldr	r1, [r7, r6, asl #2]	@ tmp439, s_pstVfmwChan
	movw	lr, #:lower16:249256	@ tmp446,
	movt	lr, #:upper16:249256	@ tmp446,
	movw	ip, #:lower16:249260	@ tmp450,
	movt	ip, #:upper16:249260	@ tmp450,
	movw	r0, #:lower16:249268	@ tmp454,
	str	r2, [r1, #264]	@, <variable>.s32SelfAllocChanMem_vdh
	movt	r0, #:upper16:249268	@ tmp454,
	ldr	r3, [r7, r6, asl #2]	@ tmp441, s_pstVfmwChan
	movw	r1, #:lower16:249272	@ tmp458,
	ldr	r8, [fp, #-260]	@, %sfp
	movt	r1, #:upper16:249272	@ tmp458,
	movw	r2, #:lower16:249264	@ tmp462,
	movt	r2, #:upper16:249264	@ tmp462,
	str	r8, [r3, #268]	@, <variable>.s32SelfAllocChanMem_scd
	movw	r3, #:lower16:249280	@ tmp466,
	str	r5, [fp, #-240]	@, %sfp
	movt	r3, #:upper16:249280	@ tmp466,
	ldr	r5, [fp, #-256]	@, %sfp
	ldr	r8, [r7, r6, asl #2]	@, s_pstVfmwChan
	str	r5, [r8, #272]	@, <variable>.s32SelfAllocChanMem_ctx
	ldr	r5, [r7, r6, asl #2]	@ tmp445, s_pstVfmwChan
	str	r9, [r5, lr]	@ tmp408, <variable>.s32CurFsSize
	ldr	r8, [r7, r6, asl #2]	@ tmp449, s_pstVfmwChan
	str	r9, [r8, ip]	@ tmp408, <variable>.s32RefNum
	ldr	r5, [r7, r6, asl #2]	@ tmp453, s_pstVfmwChan
	str	r9, [r5, r0]	@ tmp408, <variable>.s32PreAllocFrmNum
	ldr	lr, [r7, r6, asl #2]	@ tmp457, s_pstVfmwChan
	str	r9, [lr, r1]	@ tmp408, <variable>.s32MMZFrmNum
	ldr	r1, [r7, r6, asl #2]	@ tmp461, s_pstVfmwChan
	str	r9, [r1, r2]	@ tmp408, <variable>.s32NeededFrameNum
	ldr	r8, [r7, r6, asl #2]	@ tmp465, s_pstVfmwChan
	str	r9, [r8, r3]	@ tmp408, <variable>.s32RefNumChanged
	ldr	ip, [fp, #-240]	@, %sfp
	ldr	r0, [r7, r6, asl #2]	@ tmp469, s_pstVfmwChan
	ldr	r5, [r4, #132]	@ <variable>.u32DynamicFrameStoreAllocEn, <variable>.u32DynamicFrameStoreAllocEn
	str	r5, [r0, ip]	@ <variable>.u32DynamicFrameStoreAllocEn, <variable>.u32DynamicFrameStoreAllocEn
	ldr	r8, [fp, #-292]	@ u32i, %sfp
.L2499:
	add	r2, r8, r8, asl #2	@, tmp477, u32i, u32i,
	ldr	ip, [r7, r6, asl #2]	@ tmp473, s_pstVfmwChan
	add	r5, r8, #1	@ tmp730, u32i,
	mov	r1, #16	@,
	mov	r3, r2, asl #2	@ tmp478, tmp477,
	add	r8, r5, #1	@ u32i, tmp730,
	add	lr, r3, ip	@ tmp479, tmp478, tmp473
	add	r0, r3, #248832	@ tmp488, tmp478,
	add	r9, lr, #248832	@ tmp480, tmp479,
	add	ip, r0, #456	@ tmp488, tmp488,
	add	r2, r9, #472	@ tmp480, tmp480,
	movw	r9, #:lower16:.LANCHOR0	@ tmp734,
	movt	r9, #:upper16:.LANCHOR0	@ tmp734,
	strb	sl, [r2, #0]	@ tmp727, <variable>.u8BufferNodeState
	ldr	lr, [r7, r6, asl #2]	@ tmp491, s_pstVfmwChan
	add	r0, ip, lr	@, tmp488, tmp491
	bl	__memzero	@
	add	r3, r5, r5, asl #2	@, tmp738, tmp730, tmp730,
	ldr	r0, [r7, r6, asl #2]	@ tmp735, s_pstVfmwChan
	mov	r1, #16	@,
	mov	r5, r3, asl #2	@ tmp739, tmp738,
	add	r2, r5, r0	@ tmp740, tmp739, tmp735
	add	ip, r5, #248832	@ tmp744, tmp739,
	add	r3, r2, #248832	@ tmp741, tmp740,
	add	r5, ip, #456	@ tmp744, tmp744,
	add	r0, r3, #472	@ tmp741, tmp741,
	strb	sl, [r0, #0]	@ tmp727, <variable>.u8BufferNodeState
	ldr	r2, [r7, r6, asl #2]	@ tmp745, s_pstVfmwChan
	add	r0, r5, r2	@, tmp744, tmp745
	bl	__memzero	@
	cmp	r8, #64	@ u32i,
	bne	.L2499	@,
	ldr	ip, [r9, r6, asl #2]	@ tmp495, s_pstVfmwChan
	mov	r1, #948	@,
	add	r5, r9, r6, asl #2	@, tmp503, tmp734, ChanID.6359,
	mov	r8, #0	@ tmp505,
	add	lr, ip, #249856	@, tmp495,
	add	r0, lr, #712	@,,
	bl	__memzero	@
	ldr	r3, [r9, r6, asl #2]	@ tmp499, s_pstVfmwChan
	mov	r1, #24	@,
	add	r0, r3, #250880	@, tmp499,
	add	r0, r0, #636	@,,
	bl	__memzero	@
	str	r8, [r5, #532]	@ tmp505, s_ChanControlState
	ldr	r1, [r4, #8]	@ <variable>.MemAllocMode, <variable>.MemAllocMode
	cmp	r1, #3	@ <variable>.MemAllocMode,
	beq	.L2530	@,
	ldr	r2, [fp, #-244]	@, %sfp
	ldr	r3, [r9, r2, asl #2]	@ prephitmp.6100, s_pstVfmwChan
.L2501:
	mov	r1, #0	@ tmp533,
	str	r1, [r3, #196]	@ tmp533, <variable>.s32OneChanMem
.L2502:
	ldr	r0, [r7, r6, asl #2]	@ tmp535, s_pstVfmwChan
	movw	lr, #:lower16:249248	@ tmp569,
	ldr	r2, [fp, #-72]	@ ChanMemVDH.PhyAddr, ChanMemVDH.PhyAddr
	movt	lr, #:upper16:249248	@ tmp569,
	mov	r1, #0	@ tmp570,
	movw	r3, #:lower16:.LANCHOR0	@ tmp534,
	movt	r3, #:upper16:.LANCHOR0	@ tmp534,
	str	r2, [r0, #224]	@ ChanMemVDH.PhyAddr, <variable>.stChanMem_vdh.PhyAddr
	ldr	ip, [fp, #-68]	@ ChanMemVDH.VirAddr, ChanMemVDH.VirAddr
	ldr	r5, [r7, r6, asl #2]	@ tmp538, s_pstVfmwChan
	str	ip, [r5, #220]	@ ChanMemVDH.VirAddr, <variable>.stChanMem_vdh.VirAddr
	ldr	r8, [fp, #-64]	@ ChanMemVDH.Length, ChanMemVDH.Length
	ldr	r2, [r7, r6, asl #2]	@ tmp541, s_pstVfmwChan
	str	r8, [r2, #228]	@ ChanMemVDH.Length, <variable>.stChanMem_vdh.Length
	ldr	r0, [fp, #-88]	@ ChanMemScd.PhyAddr, ChanMemScd.PhyAddr
	ldr	r5, [r7, r6, asl #2]	@ tmp544, s_pstVfmwChan
	str	r0, [r5, #240]	@ ChanMemScd.PhyAddr, <variable>.stChanMem_scd.PhyAddr
	ldr	ip, [fp, #-84]	@ ChanMemScd.VirAddr, ChanMemScd.VirAddr
	ldr	r8, [r7, r6, asl #2]	@ tmp547, s_pstVfmwChan
	str	ip, [r8, #236]	@ ChanMemScd.VirAddr, <variable>.stChanMem_scd.VirAddr
	ldr	r2, [fp, #-80]	@ ChanMemScd.Length, ChanMemScd.Length
	ldr	r0, [r7, r6, asl #2]	@ tmp550, s_pstVfmwChan
	str	r2, [r0, #244]	@ ChanMemScd.Length, <variable>.stChanMem_scd.Length
	ldr	r5, [fp, #-104]	@ ChanMemCtx.PhyAddr, ChanMemCtx.PhyAddr
	ldr	r8, [r7, r6, asl #2]	@ tmp553, s_pstVfmwChan
	str	r5, [r8, #256]	@ ChanMemCtx.PhyAddr, <variable>.stChanMem_ctx.PhyAddr
	ldr	ip, [fp, #-100]	@ ChanMemCtx.VirAddr, ChanMemCtx.VirAddr
	ldr	r2, [r7, r6, asl #2]	@ tmp556, s_pstVfmwChan
	str	ip, [r2, #252]	@ ChanMemCtx.VirAddr, <variable>.stChanMem_ctx.VirAddr
	ldr	r0, [fp, #-96]	@ ChanMemCtx.Length, ChanMemCtx.Length
	ldr	r5, [r7, r6, asl #2]	@ tmp559, s_pstVfmwChan
	str	r0, [r5, #260]	@ ChanMemCtx.Length, <variable>.stChanMem_ctx.Length
	ldr	r8, [fp, #-72]	@ ChanMemVDH.PhyAddr, ChanMemVDH.PhyAddr
	ldr	r2, [r7, r6, asl #2]	@ tmp562, s_pstVfmwChan
	str	r8, [r2, #296]	@ ChanMemVDH.PhyAddr, <variable>.s32SdecMemAddr
	ldr	ip, [fp, #-64]	@ ChanMemVDH.Length, ChanMemVDH.Length
	ldr	r0, [r7, r6, asl #2]	@ tmp565, s_pstVfmwChan
	str	ip, [r0, #300]	@ ChanMemVDH.Length, <variable>.s32SdecMemSize
	ldr	r5, [r7, r6, asl #2]	@ tmp568, s_pstVfmwChan
	str	r1, [r5, lr]	@ tmp570, <variable>.FspInst.eFspPartitionState
	ldr	r2, [r7, r6, asl #2]	@ temp.6311, s_pstVfmwChan
	ldr	r8, [r2, #1416]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r8, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	beq	.L2503	@,
	ldr	r5, [fp, #-72]	@ ChanMemVDH.PhyAddr, ChanMemVDH.PhyAddr
	ldr	r1, [r2, #288]	@ <variable>.s32OffLineDNRMemSize, <variable>.s32OffLineDNRMemSize
	ldr	r8, [r2, #4]	@ <variable>.s32BtlMemSize, <variable>.s32BtlMemSize
	add	r0, r1, r5	@ tmp573, <variable>.s32OffLineDNRMemSize, ChanMemVDH.PhyAddr
	add	lr, r0, r8	@ tmp577, tmp573, <variable>.s32BtlMemSize
	str	lr, [r2, #276]	@ tmp577, <variable>.s32VdmChanMemAddr
	ldr	lr, [r3, r6, asl #2]	@ temp.6314, s_pstVfmwChan
	ldr	ip, [fp, #-64]	@ ChanMemVDH.Length, ChanMemVDH.Length
	ldr	r1, [lr, #288]	@ <variable>.s32OffLineDNRMemSize, <variable>.s32OffLineDNRMemSize
	ldr	r8, [lr, #4]	@ <variable>.s32BtlMemSize, <variable>.s32BtlMemSize
	rsb	r5, r1, ip	@ tmp579, <variable>.s32OffLineDNRMemSize, ChanMemVDH.Length
	rsb	r2, r8, r5	@ tmp582, <variable>.s32BtlMemSize, tmp579
	sub	r0, r2, #16	@ tmp584, tmp582,
	str	r0, [lr, #280]	@ tmp584, <variable>.s32VdmChanMemSize
	ldr	ip, [r3, r6, asl #2]	@ temp.6317, s_pstVfmwChan
	ldr	r1, [ip, #280]	@ <variable>.s32VdmChanMemSize, <variable>.s32VdmChanMemSize
	sub	r5, r1, #14848	@ tmp588, <variable>.s32VdmChanMemSize,
	str	r5, [ip, #280]	@ tmp588, <variable>.s32VdmChanMemSize
	ldr	r2, [r3, r6, asl #2]	@ temp.6318, s_pstVfmwChan
	ldr	r8, [r2, #280]	@ <variable>.s32VdmChanMemSize, <variable>.s32VdmChanMemSize
	sub	lr, r8, #32768	@ tmp592, <variable>.s32VdmChanMemSize,
	str	lr, [r2, #280]	@ tmp592, <variable>.s32VdmChanMemSize
	ldr	r8, [r3, r6, asl #2]	@ temp.6320, s_pstVfmwChan
	ldr	r0, [r8, #276]	@ <variable>.s32VdmChanMemAddr, <variable>.s32VdmChanMemAddr
	ldr	r1, [r8, #280]	@ <variable>.s32VdmChanMemSize, <variable>.s32VdmChanMemSize
	add	ip, r0, r1	@ tmp594, <variable>.s32VdmChanMemAddr, <variable>.s32VdmChanMemSize
	mov	r1, #14848	@ tmp601,
	add	r5, ip, #15	@ tmp597, tmp594,
	bic	lr, r5, #15	@ tmp598, tmp597,
	str	lr, [r8, #308]	@ tmp598, <variable>.s32BpdChanMemAddr
	ldr	r2, [r3, r6, asl #2]	@ tmp600, s_pstVfmwChan
	str	r1, [r2, #312]	@ tmp601, <variable>.s32BpdChanMemSize
	ldr	r2, [r3, r6, asl #2]	@ temp.6323, s_pstVfmwChan
	ldr	ip, [r2, #276]	@ <variable>.s32VdmChanMemAddr, <variable>.s32VdmChanMemAddr
	ldr	r0, [r2, #280]	@ <variable>.s32VdmChanMemSize, <variable>.s32VdmChanMemSize
	ldr	lr, [r2, #312]	@ <variable>.s32BpdChanMemSize, <variable>.s32BpdChanMemSize
	add	r5, ip, r0	@ tmp603, <variable>.s32VdmChanMemAddr, <variable>.s32VdmChanMemSize
	add	r8, r5, #15	@ tmp606, tmp603,
	mov	r5, #32768	@ tmp612,
	add	r1, r8, lr	@ tmp607, tmp606, <variable>.s32BpdChanMemSize
	bic	r0, r1, #15	@ tmp609, tmp607,
	str	r0, [r2, #316]	@ tmp609, <variable>.s32Vp8SegIdChanMemAddr
	ldr	ip, [r3, r6, asl #2]	@ tmp611, s_pstVfmwChan
	str	r5, [ip, #320]	@ tmp612, <variable>.s32Vp8SegIdChanMemSize
	ldr	lr, [fp, #-88]	@ ChanMemScd.PhyAddr, ChanMemScd.PhyAddr
	ldr	r8, [r3, r6, asl #2]	@ tmp614, s_pstVfmwChan
	str	lr, [r8, #292]	@ ChanMemScd.PhyAddr, <variable>.s32ScdChanMemAddr
	ldr	r1, [fp, #-80]	@ ChanMemScd.Length, ChanMemScd.Length
	ldr	r3, [r3, r6, asl #2]	@ tmp617, s_pstVfmwChan
	str	r1, [r3, #304]	@ ChanMemScd.Length, <variable>.s32ScdChanMemSize
.L2504:
	ldr	r5, [r7, r6, asl #2]	@ tmp659, s_pstVfmwChan
	movw	r8, #:lower16:206392	@ tmp666,
	movt	r8, #:upper16:206392	@ tmp666,
	movw	r3, #:lower16:192352	@ tmp670,
	movt	r3, #:upper16:192352	@ tmp670,
	mov	r0, r6	@, ChanID.6359
	str	r6, [r5, #8]	@ ChanID.6359, <variable>.s32ChanID
	movw	r5, #:lower16:.LANCHOR0	@ tmp658,
	ldr	ip, [r7, r6, asl #2]	@ tmp661, s_pstVfmwChan
	movt	r5, #:upper16:.LANCHOR0	@ tmp658,
	str	r6, [ip, #184]	@ ChanID.6359, <variable>.s32SCDInstID
	ldr	r2, [r7, r6, asl #2]	@ tmp663, s_pstVfmwChan
	str	r6, [r2, #188]	@ ChanID.6359, <variable>.s32VDMInstID
	ldr	lr, [r7, r6, asl #2]	@ tmp665, s_pstVfmwChan
	strb	r6, [lr, r8]	@ ChanID.6359, <variable>.FspInst.s32InstID
	ldr	r1, [r7, r6, asl #2]	@ tmp669, s_pstVfmwChan
	str	r6, [r1, r3]	@ ChanID.6359, <variable>.SmInstArray.InstID
	bl	FSP_EnableInstance	@
	cmp	r0, #0	@,
	bne	.L2531	@,
	mov	r0, r6	@, ChanID.6359
	mov	r7, #1	@ tmp680,
	bl	SM_ClearInst	@
	ldr	r2, [r5, r6, asl #2]	@ tmp673, s_pstVfmwChan
	ldr	r8, [fp, #-252]	@, %sfp
	mov	r0, r6	@, ChanID.6359
	ldr	r1, [r2, #252]	@ <variable>.stChanMem_ctx.VirAddr, <variable>.stChanMem_ctx.VirAddr
	sub	ip, r8, #205824	@ tmp674,,
	sub	r3, ip, #8	@ tmp674, tmp674,
	add	r1, r3, r1	@, tmp674, <variable>.stChanMem_ctx.VirAddr
	bl	OpenUsdPool_WithMem	@
	ldr	ip, [r5, r6, asl #2]	@ tmp679, s_pstVfmwChan
	mov	r0, r6	@, ChanID.6359
	str	r7, [ip, #12]	@ tmp680, <variable>.s32IsOpen
	bl	VDMDRV_ClearChanIsDec	@
	bl	VCTRL_EnableAllInt	@
	bl	VDMDRV_ParamInit	@
	add	r0, r5, #520	@, tmp658,
	bl	OSAL_SpinUnLockIRQ	@
	str	r7, [r4, #52]	@ tmp680, <variable>.s32ScdLowdlyEnable
	mov	r0, r6	@, ChanID.6359
	bl	SM_AllocDSPCtxMem	@
	b	.L2428	@
.L2469:
	ldr	r1, [r4, #4]	@ <variable>.Purpose, <variable>.Purpose
	cmp	r1, #2	@ <variable>.Purpose,
	beq	.L2471	@,
	mov	lr, #0	@ tmp331,
	movw	r0, #:lower16:.LC339	@,
	mov	r1, lr	@, tmp331
	movt	r0, #:upper16:.LC339	@,
	sub	r3, fp, #120	@,,
	ldr	r2, [fp, #-52]	@, DetailMemSize.ScdDetailMem
	str	lr, [sp, #0]	@ tmp331,
	bl	MEM_AllocMemBlock	@
	cmp	r0, #0	@,
	bne	.L2532	@,
	ldr	r0, [fp, #-112]	@, MemRecord.PhyAddr
	mov	r7, #1	@,
	ldr	r1, [fp, #-116]	@, MemRecord.VirAddr
	str	r7, [fp, #-260]	@, %sfp
.L2513:
	ldr	r2, [fp, #-108]	@, MemRecord.Length
	bl	MEM_AddMemRecord	@
	ldr	r3, [fp, #-112]	@ MemRecord.PhyAddr, MemRecord.PhyAddr
	ldr	r1, [fp, #-116]	@ MemRecord.VirAddr, MemRecord.VirAddr
	ldr	r2, [fp, #-108]	@ MemRecord.Length, MemRecord.Length
	str	r3, [fp, #-88]	@ MemRecord.PhyAddr, ChanMemScd.PhyAddr
	str	r1, [fp, #-84]	@ MemRecord.VirAddr, ChanMemScd.VirAddr
	str	r2, [fp, #-80]	@ MemRecord.Length, ChanMemScd.Length
	b	.L2445	@
.L2503:
	str	r1, [r2, #276]	@ tmp570, <variable>.s32VdmChanMemAddr
	ldr	ip, [r3, r6, asl #2]	@ tmp621, s_pstVfmwChan
	str	r1, [ip, #280]	@ tmp570, <variable>.s32VdmChanMemSize
	ldr	r0, [fp, #-88]	@ ChanMemScd.PhyAddr, ChanMemScd.PhyAddr
	ldr	r2, [r3, r6, asl #2]	@ tmp624, s_pstVfmwChan
	str	r0, [r2, #292]	@ ChanMemScd.PhyAddr, <variable>.s32ScdChanMemAddr
	ldr	r8, [r3, r6, asl #2]	@ tmp627, s_pstVfmwChan
	ldr	r5, [fp, #-80]	@ ChanMemScd.Length, ChanMemScd.Length
	sub	lr, r5, #16	@ tmp629, ChanMemScd.Length,
	str	lr, [r8, #304]	@ tmp629, <variable>.s32ScdChanMemSize
	ldr	ip, [r3, r6, asl #2]	@ temp.6337, s_pstVfmwChan
	ldr	r1, [ip, #304]	@ <variable>.s32ScdChanMemSize, <variable>.s32ScdChanMemSize
	sub	r0, r1, #14848	@ tmp633, <variable>.s32ScdChanMemSize,
	str	r0, [ip, #304]	@ tmp633, <variable>.s32ScdChanMemSize
	ldr	r5, [r3, r6, asl #2]	@ temp.6338, s_pstVfmwChan
	ldr	r2, [r5, #304]	@ <variable>.s32ScdChanMemSize, <variable>.s32ScdChanMemSize
	sub	r8, r2, #32768	@ tmp637, <variable>.s32ScdChanMemSize,
	str	r8, [r5, #304]	@ tmp637, <variable>.s32ScdChanMemSize
	ldr	r2, [r3, r6, asl #2]	@ temp.6340, s_pstVfmwChan
	ldr	lr, [r2, #292]	@ <variable>.s32ScdChanMemAddr, <variable>.s32ScdChanMemAddr
	ldr	ip, [r2, #304]	@ <variable>.s32ScdChanMemSize, <variable>.s32ScdChanMemSize
	add	r1, lr, ip	@ tmp639, <variable>.s32ScdChanMemAddr, <variable>.s32ScdChanMemSize
	mov	lr, #14848	@ tmp646,
	add	r0, r1, #15	@ tmp642, tmp639,
	bic	r5, r0, #15	@ tmp643, tmp642,
	str	r5, [r2, #308]	@ tmp643, <variable>.s32BpdChanMemAddr
	ldr	r8, [r3, r6, asl #2]	@ tmp645, s_pstVfmwChan
	str	lr, [r8, #312]	@ tmp646, <variable>.s32BpdChanMemSize
	ldr	lr, [r3, r6, asl #2]	@ temp.6343, s_pstVfmwChan
	ldr	ip, [lr, #292]	@ <variable>.s32ScdChanMemAddr, <variable>.s32ScdChanMemAddr
	ldr	r2, [lr, #304]	@ <variable>.s32ScdChanMemSize, <variable>.s32ScdChanMemSize
	ldr	r5, [lr, #312]	@ <variable>.s32BpdChanMemSize, <variable>.s32BpdChanMemSize
	add	r1, ip, r2	@ tmp648, <variable>.s32ScdChanMemAddr, <variable>.s32ScdChanMemSize
	mov	r2, #32768	@ tmp657,
	add	r0, r1, #15	@ tmp651, tmp648,
	add	r8, r0, r5	@ tmp652, tmp651, <variable>.s32BpdChanMemSize
	bic	ip, r8, #15	@ tmp654, tmp652,
	str	ip, [lr, #316]	@ tmp654, <variable>.s32Vp8SegIdChanMemAddr
	ldr	r3, [r3, r6, asl #2]	@ tmp656, s_pstVfmwChan
	str	r2, [r3, #320]	@ tmp657, <variable>.s32Vp8SegIdChanMemSize
	b	.L2504	@
.L2530:
	ldr	r3, [r9, r6, asl #2]	@ prephitmp.6100, s_pstVfmwChan
	ldr	r2, [r3, #272]	@ <variable>.s32SelfAllocChanMem_ctx, <variable>.s32SelfAllocChanMem_ctx
	cmp	r2, #1	@ <variable>.s32SelfAllocChanMem_ctx,
	bne	.L2501	@,
	ldr	r1, [r3, #264]	@ <variable>.s32SelfAllocChanMem_vdh, <variable>.s32SelfAllocChanMem_vdh
	cmp	r1, #0	@ <variable>.s32SelfAllocChanMem_vdh,
	bne	.L2501	@,
	ldr	r8, [r3, #268]	@ <variable>.s32SelfAllocChanMem_scd, <variable>.s32SelfAllocChanMem_scd
	cmp	r8, #0	@ <variable>.s32SelfAllocChanMem_scd,
	bne	.L2501	@,
	ldr	r1, [fp, #-88]	@ temp.6278, ChanMemScd.PhyAddr
	ldr	ip, [fp, #-80]	@ ChanMemScd.Length, ChanMemScd.Length
	ldr	r5, [fp, #-72]	@ ChanMemVDH.PhyAddr, ChanMemVDH.PhyAddr
	ldr	lr, [fp, #-264]	@, %sfp
	add	r0, r1, ip	@ tmp513, temp.6278, ChanMemScd.Length
	cmp	lr, #1	@,
	cmpeq	r0, r5	@, tmp513, ChanMemVDH.PhyAddr
	bne	.L2501	@,
	str	r1, [r3, #208]	@ temp.6278, <variable>.stChanMem.PhyAddr
	ldr	lr, [fp, #-84]	@ ChanMemScd.VirAddr, ChanMemScd.VirAddr
	ldr	ip, [r9, r6, asl #2]	@ tmp522, s_pstVfmwChan
	str	lr, [ip, #204]	@ ChanMemScd.VirAddr, <variable>.stChanMem.VirAddr
	ldr	r8, [r9, r6, asl #2]	@ tmp525, s_pstVfmwChan
	ldr	r5, [fp, #-80]	@ ChanMemScd.Length, ChanMemScd.Length
	ldr	r0, [fp, #-64]	@ ChanMemVDH.Length, ChanMemVDH.Length
	add	r1, r0, r5	@ tmp528, ChanMemVDH.Length, ChanMemScd.Length
	str	r1, [r8, #212]	@ tmp528, <variable>.stChanMem.Length
	ldr	r3, [r9, r6, asl #2]	@ tmp530, s_pstVfmwChan
	str	r2, [r3, #196]	@ <variable>.s32SelfAllocChanMem_ctx, <variable>.s32OneChanMem
	b	.L2502	@
.L2471:
	ldr	ip, [fp, #-72]	@ ChanMemVDH.PhyAddr, ChanMemVDH.PhyAddr
	mov	r0, #0	@ tmp342,
	ldr	lr, [fp, #-68]	@ ChanMemVDH.VirAddr, ChanMemVDH.VirAddr
	str	r0, [fp, #-260]	@ tmp342, %sfp
	str	r0, [fp, #-80]	@ tmp342, ChanMemScd.Length
	str	ip, [fp, #-88]	@ ChanMemVDH.PhyAddr, ChanMemScd.PhyAddr
	str	lr, [fp, #-84]	@ ChanMemVDH.VirAddr, ChanMemScd.VirAddr
	b	.L2445	@
.L2521:
	sub	r8, fp, #120	@ tmp715,,
	mov	r1, ip	@, D.50836
	movw	r0, #:lower16:.LC335	@,
	ldr	r2, [fp, #-48]	@, DetailMemSize.ChanCtxDetailMem
	movt	r0, #:upper16:.LC335	@,
	mov	r3, r8	@, tmp715
	mov	r7, #1	@ tmp247,
	str	r7, [sp, #0]	@ tmp247,
	bl	MEM_AllocMemBlock	@
	subs	r6, r0, #0	@ D.50875,
	bne	.L2533	@,
	ldr	r1, [fp, #-116]	@, MemRecord.VirAddr
	ldr	r2, [fp, #-108]	@, MemRecord.Length
	ldr	r0, [fp, #-112]	@, MemRecord.PhyAddr
	bl	MEM_AddMemRecord	@
	ldr	r1, [r4, #132]	@ <variable>.u32DynamicFrameStoreAllocEn, <variable>.u32DynamicFrameStoreAllocEn
	ldr	r2, [fp, #-112]	@ MemRecord.PhyAddr, MemRecord.PhyAddr
	ldr	r0, [fp, #-116]	@ MemRecord.VirAddr, MemRecord.VirAddr
	cmp	r1, #1	@ <variable>.u32DynamicFrameStoreAllocEn,
	ldr	r3, [fp, #-108]	@ MemRecord.Length, MemRecord.Length
	str	r2, [fp, #-104]	@ MemRecord.PhyAddr, ChanMemCtx.PhyAddr
	str	r0, [fp, #-100]	@ MemRecord.VirAddr, ChanMemCtx.VirAddr
	str	r3, [fp, #-96]	@ MemRecord.Length, ChanMemCtx.Length
	beq	.L2448	@,
	mov	r1, r6	@, D.50875
	movw	r0, #:lower16:.LC337	@,
	ldr	r2, [fp, #-56]	@, DetailMemSize.VdhDetailMem
	movt	r0, #:upper16:.LC337	@,
	mov	r3, r8	@, tmp715
	str	r6, [sp, #0]	@ D.50875,
	bl	MEM_AllocMemBlock	@
	cmp	r0, #0	@,
	bne	.L2534	@,
	ldr	r0, [fp, #-112]	@, MemRecord.PhyAddr
	ldr	r1, [fp, #-116]	@, MemRecord.VirAddr
	ldr	r2, [fp, #-108]	@, MemRecord.Length
	str	r7, [fp, #-240]	@ tmp247, %sfp
	bl	MEM_AddMemRecord	@
	ldr	r0, [fp, #-112]	@ MemRecord.PhyAddr, MemRecord.PhyAddr
	ldr	r3, [fp, #-116]	@ MemRecord.VirAddr, MemRecord.VirAddr
	ldr	ip, [fp, #-108]	@ MemRecord.Length, MemRecord.Length
	str	r0, [fp, #-72]	@ MemRecord.PhyAddr, ChanMemVDH.PhyAddr
	str	r3, [fp, #-68]	@ MemRecord.VirAddr, ChanMemVDH.VirAddr
	str	ip, [fp, #-64]	@ MemRecord.Length, ChanMemVDH.Length
.L2450:
	ldr	lr, [r4, #4]	@ <variable>.Purpose, <variable>.Purpose
	cmp	lr, #2	@ <variable>.Purpose,
	bne	.L2535	@,
	ldr	r1, [fp, #-72]	@ ChanMemVDH.PhyAddr, ChanMemVDH.PhyAddr
	mov	r0, #0	@ tmp278,
	ldr	r2, [fp, #-68]	@ ChanMemVDH.VirAddr, ChanMemVDH.VirAddr
	mov	r3, #1	@,
	str	r0, [fp, #-260]	@ tmp278, %sfp
	str	r0, [fp, #-80]	@ tmp278, ChanMemScd.Length
	str	r3, [fp, #-256]	@, %sfp
	str	r1, [fp, #-88]	@ ChanMemVDH.PhyAddr, ChanMemScd.PhyAddr
	str	r2, [fp, #-84]	@ ChanMemVDH.VirAddr, ChanMemScd.VirAddr
	b	.L2445	@
.L2475:
	mov	r2, #0	@,
	str	r2, [fp, #-260]	@, %sfp
	b	.L2445	@
.L2525:
	add	r3, r3, #13	@,,
.L2514:
	str	r3, [fp, #-244]	@, %sfp
	mov	r6, r3	@ ChanID.6359,
	b	.L2482	@
.L2448:
	str	r6, [fp, #-240]	@ D.50875, %sfp
	str	r6, [fp, #-72]	@ D.50875, ChanMemVDH.PhyAddr
	str	r6, [fp, #-68]	@ D.50875, ChanMemVDH.VirAddr
	str	r6, [fp, #-64]	@ D.50875, ChanMemVDH.Length
	b	.L2450	@
.L2466:
	ldr	r2, [fp, #-64]	@ prephitmp.6186, ChanMemVDH.Length
	b	.L2467	@
.L2535:
	mov	ip, #0	@ tmp270,
	mov	r3, r8	@, tmp715
	mov	r1, ip	@, tmp270
	movw	r0, #:lower16:.LC339	@,
	ldr	r2, [fp, #-52]	@, DetailMemSize.ScdDetailMem
	movt	r0, #:upper16:.LC339	@,
	str	ip, [sp, #0]	@ tmp270,
	bl	MEM_AllocMemBlock	@
	cmp	r0, #0	@,
	bne	.L2536	@,
	mov	r7, #1	@,
	ldr	r0, [fp, #-112]	@, MemRecord.PhyAddr
	str	r7, [fp, #-256]	@, %sfp
	ldr	r1, [fp, #-116]	@, MemRecord.VirAddr
	str	r7, [fp, #-260]	@, %sfp
	b	.L2513	@
.L2531:
.L2506:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC348	@,
	movt	r1, #:upper16:.LC348	@,
	mvn	lr, #0	@,
	str	lr, [fp, #-244]	@, %sfp
	bl	dprint_vfmw	@
	mov	r0, r6	@, ChanID.6359
	sub	r8, fp, #216	@,,
	bl	VCTRL_UnInstallChan	@
	ldr	r3, [r5, r6, asl #2]	@ temp.6354, s_pstVfmwChan
	str	r8, [fp, #-288]	@, %sfp
	sub	r7, fp, #200	@,,
	ldr	r9, [fp, #-248]	@, %sfp
	add	sl, r3, #148	@, temp.6354,
	ldr	r0, [r3, #272]	@ <variable>.s32SelfAllocChanMem_ctx, <variable>.s32SelfAllocChanMem_ctx
	add	r2, r3, #200	@ tmp691, temp.6354,
	str	r7, [fp, #-276]	@, %sfp
	add	r4, r3, #248832	@ tmp689, temp.6354,
	add	r1, r4, #456	@ tmp689, tmp689,
	add	ip, r3, #248	@ tmp693, temp.6354,
	str	r0, [fp, #-144]	@ <variable>.s32SelfAllocChanMem_ctx, ChanMem.s32SelfAllocChanMem_ctx
	mov	r0, #48	@ tmp700,
	ldr	r7, [r3, #264]	@ <variable>.s32SelfAllocChanMem_vdh, <variable>.s32SelfAllocChanMem_vdh
	add	r4, r3, #216	@ tmp695, temp.6354,
	str	sl, [fp, #-240]	@, %sfp
	add	r8, r3, #232	@ tmp697, temp.6354,
	mla	sl, r0, r6, r9	@ tmp701, tmp700, ChanID.6359,
	str	r7, [fp, #-152]	@ <variable>.s32SelfAllocChanMem_vdh, ChanMem.s32SelfAllocChanMem_vdh
	sub	r7, fp, #140	@,,
	str	r7, [fp, #-280]	@, %sfp
	ldr	r0, [r3, #268]	@ <variable>.s32SelfAllocChanMem_scd, <variable>.s32SelfAllocChanMem_scd
	sub	lr, fp, #184	@ tmp692,,
	str	r1, [fp, #-124]	@ tmp689, ChanMem.pstChanFrmBuf
	sub	r9, fp, #168	@ tmp702,,
	ldr	r7, [fp, #-272]	@, %sfp
	str	r0, [fp, #-148]	@ <variable>.s32SelfAllocChanMem_scd, ChanMem.s32SelfAllocChanMem_scd
	ldmia	r2, {r0, r1, r2, r3}	@ tmp691,,,,
	stmia	r7, {r0, r1, r2, r3}	@,,,,
	mov	r7, #0	@ tmp707,
	ldmia	ip, {r0, r1, r2, r3}	@ tmp693,,,,
	ldr	ip, [fp, #-288]	@, %sfp
	stmia	lr, {r0, r1, r2, r3}	@ tmp692,,,,
	ldmia	r4, {r0, r1, r2, r3}	@ tmp695,,,,
	stmia	ip, {r0, r1, r2, r3}	@,,,,
	ldr	lr, [fp, #-276]	@, %sfp
	ldmia	r8, {r0, r1, r2, r3}	@ tmp697,,,,
	stmia	lr, {r0, r1, r2, r3}	@,,,,
	ldmia	sl, {r0, r1, r2, r3}	@ tmp701,,,,
	stmia	r9, {r0, r1, r2, r3}	@ tmp702,,,,
	ldr	r3, [fp, #-240]	@, %sfp
	ldmia	r3, {r0, r1, r2}	@,,,
	str	r7, [r5, r6, asl #2]	@ tmp707, s_pstVfmwChan
	ldr	r7, [fp, #-280]	@, %sfp
	stmia	r7, {r0, r1, r2}	@,,,
	mov	r0, r6	@, ChanID.6359
	bl	VDMDRV_ClearChanIsDec	@
	bl	VCTRL_EnableAllInt	@
	add	r0, r5, #520	@, tmp658,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r6	@, ChanID.6359
	sub	r1, fp, #232	@,,
	bl	VCTRL_FreeChanResource	@
	b	.L2428	@
.L2442:
	movw	r2, #1886	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC334	@,
	movt	r1, #:upper16:.LC334	@,
	bl	dprint_vfmw	@
	mvn	r2, #0	@,
	str	r2, [fp, #-244]	@, %sfp
	b	.L2428	@
.L2454:
	movw	r1, #:lower16:.LC346	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC346	@,
	mvn	r9, #0	@,
	str	r9, [fp, #-244]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2428	@
.L2528:
	ldr	r5, [fp, #-256]	@, %sfp
	cmp	r5, #1	@,
	bne	.L2464	@,
	ldr	r0, [fp, #-104]	@, ChanMemCtx.PhyAddr
	ldr	r1, [fp, #-100]	@, ChanMemCtx.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #104
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
.L2464:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC343	@,
	movw	r2, #2011	@,
	movt	r1, #:upper16:.LC343	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@,
	str	r5, [fp, #-244]	@, %sfp
	b	.L2428	@
.L2532:
	ldr	r3, [fp, #-256]	@, %sfp
	cmp	r3, #1	@,
	beq	.L2537	@,
.L2473:
	ldr	ip, [fp, #-240]	@, %sfp
	cmp	ip, #1	@,
	bne	.L2474	@,
	ldr	r0, [fp, #-72]	@, ChanMemVDH.PhyAddr
	ldr	r1, [fp, #-68]	@, ChanMemVDH.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #72
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
.L2474:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC345	@,
	movw	r2, #2073	@,
	movt	r1, #:upper16:.LC345	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@,
	str	r0, [fp, #-244]	@, %sfp
	b	.L2428	@
.L2515:
	movw	r1, #:lower16:.LC330	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC330	@,
	mvn	ip, #0	@,
	str	ip, [fp, #-244]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2428	@
.L2519:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC331	@,
	movw	r2, #1863	@,
	movt	r1, #:upper16:.LC331	@,
	bl	dprint_vfmw	@
	mvn	r8, #0	@,
	str	r8, [fp, #-244]	@, %sfp
	b	.L2428	@
.L2516:
	movw	r1, #:lower16:.LC21	@,
	movt	r1, #:upper16:.LC21	@,
	mvn	lr, #0	@,
	str	lr, [fp, #-244]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2428	@
.L2522:
	mov	r0, r6	@, tmp284
	movw	r1, #:lower16:.LC341	@,
	movw	r2, #1976	@,
	movt	r1, #:upper16:.LC341	@,
	bl	dprint_vfmw	@
	mvn	ip, #0	@,
	str	ip, [fp, #-244]	@, %sfp
	b	.L2428	@
.L2523:
	ldr	r8, [fp, #-256]	@, %sfp
	cmp	r8, #1	@,
	beq	.L2538	@,
.L2468:
	mov	r3, r2	@, prephitmp.6186
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC344	@,
	movw	r2, #2043	@,
	movt	r1, #:upper16:.LC344	@,
	str	ip, [sp, #0]	@ prephitmp.6187,
	mvn	r9, #0	@,
	bl	dprint_vfmw	@
	str	r9, [fp, #-244]	@, %sfp
	b	.L2428	@
.L2438:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC332	@,
	movw	r2, #1875	@,
	movt	r1, #:upper16:.LC332	@,
	bl	dprint_vfmw	@
	mvn	r9, #0	@,
	str	r9, [fp, #-244]	@, %sfp
	b	.L2428	@
.L2527:
	movw	r2, #1990	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC342	@,
	movt	r1, #:upper16:.LC342	@,
	bl	dprint_vfmw	@
	mvn	r2, #0	@,
	str	r2, [fp, #-244]	@, %sfp
	b	.L2428	@
.L2533:
	mov	r0, r7	@, tmp247
	movw	r1, #:lower16:.LC336	@,
	movw	r2, #1902	@,
	movt	r1, #:upper16:.LC336	@,
	ldr	r3, [fp, #-48]	@, DetailMemSize.ChanCtxDetailMem
	mvn	r5, #0	@,
	str	r5, [fp, #-244]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2428	@
.L2537:
	ldr	r0, [fp, #-104]	@, ChanMemCtx.PhyAddr
	ldr	r1, [fp, #-100]	@, ChanMemCtx.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #104
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
	b	.L2473	@
.L2524:
	ldr	r5, [fp, #-256]	@, %sfp
	cmp	r5, #1	@,
	bne	.L2479	@,
	ldr	r0, [fp, #-104]	@, ChanMemCtx.PhyAddr
	ldr	r1, [fp, #-100]	@, ChanMemCtx.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #104
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
.L2479:
	ldr	r5, [fp, #-240]	@, %sfp
	cmp	r5, #1	@,
	bne	.L2480	@,
	ldr	r0, [fp, #-72]	@, ChanMemVDH.PhyAddr
	ldr	r1, [fp, #-68]	@, ChanMemVDH.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #72
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
.L2480:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC333	@,
	movw	r2, #2115	@,
	movt	r1, #:upper16:.LC333	@,
	bl	dprint_vfmw	@
	mvn	r7, #0	@,
	str	r7, [fp, #-244]	@, %sfp
	b	.L2428	@
.L2538:
	ldr	r0, [fp, #-104]	@, ChanMemCtx.PhyAddr
	ldr	r1, [fp, #-100]	@, ChanMemCtx.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #104
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
	ldr	r2, [fp, #-64]	@ prephitmp.6186, ChanMemVDH.Length
	ldr	ip, [fp, #-56]	@ prephitmp.6187, DetailMemSize.VdhDetailMem
	b	.L2468	@
.L2536:
	ldr	r0, [fp, #-104]	@, ChanMemCtx.PhyAddr
	ldr	r1, [fp, #-100]	@, ChanMemCtx.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #104
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
	ldr	r9, [fp, #-240]	@, %sfp
	cmp	r9, #1	@,
	bne	.L2453	@,
	ldr	r0, [fp, #-72]	@, ChanMemVDH.PhyAddr
	ldr	r1, [fp, #-68]	@, ChanMemVDH.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #72
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
.L2453:
	movw	r1, #:lower16:.LC340	@,
	movw	r2, #1953	@,
	movt	r1, #:upper16:.LC340	@,
	ldr	r3, [fp, #-52]	@, DetailMemSize.ScdDetailMem
	mov	r0, #1	@,
	mvn	lr, #0	@,
	str	lr, [fp, #-244]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2428	@
.L2534:
	ldr	r0, [fp, #-104]	@, ChanMemCtx.PhyAddr
	mvn	r8, #0	@,
	ldr	r1, [fp, #-100]	@, ChanMemCtx.VirAddr
	str	r8, [fp, #-244]	@, %sfp
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #104
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
	mov	r0, r7	@, tmp247
	movw	r1, #:lower16:.LC338	@,
	mov	r2, #1920	@,
	movt	r1, #:upper16:.LC338	@,
	ldr	r3, [fp, #-56]	@, DetailMemSize.VdhDetailMem
	bl	dprint_vfmw	@
	b	.L2428	@
	.fnend
	.size	VCTRL_CreateChanWithOption, .-VCTRL_CreateChanWithOption
	.align	2
	.global	VCTRL_CreateChan
	.type	VCTRL_CreateChan, %function
VCTRL_CreateChan:
	.fnstart
.LFB1566:
	@ args = 0, pretend = 0, frame = 232
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
	cmp	r0, #32	@ eCapLevel,
	mov	r4, r0	@ eCapLevel, eCapLevel
	mov	r8, r1	@ pChanMem, pChanMem
	bhi	.L2554	@,
	sub	r6, fp, #264	@ tmp240,,
	sub	r5, fp, #84	@ tmp241,,
	mov	r1, #164	@,
	sub	r7, fp, #100	@ tmp237,,
	mov	r0, r6	@, tmp240
	bl	__memzero	@
	mov	r0, r5	@, tmp241
	mov	r1, #16	@,
	bl	__memzero	@
	mov	r0, r7	@, tmp237
	mov	r1, #16	@,
	bl	__memzero	@
	mov	r2, r4, asl #3	@ tmp239, eCapLevel,
	rsb	r1, r4, r2	@ tmp155, eCapLevel, tmp239
	movw	r3, #:lower16:CapItem	@ tmp238,
	movt	r3, #:upper16:CapItem	@ tmp238,
	sub	r0, r4, #18	@ D.56288, eCapLevel,
	cmp	r0, #7	@ D.56288,
	add	ip, r1, #1	@ tmp163, tmp155,
	ldr	r1, [r3, r1, asl #2]	@ tmp158, CapItem
	mov	lr, #1	@ tmp150,
	str	lr, [fp, #-260]	@ tmp150, stChanOption.Purpose
	mov	lr, #2	@ tmp151,
	str	lr, [fp, #-256]	@ tmp151, stChanOption.MemAllocMode
	mov	lr, #32	@ tmp166,
	str	lr, [fp, #-236]	@ tmp166, stChanOption.s32MaxSpsNum
	mov	lr, #256	@ tmp167,
	str	lr, [fp, #-232]	@ tmp167, stChanOption.s32MaxPpsNum
	movwls	lr, #:lower16:.LANCHOR1	@ tmp168,
	movtls	lr, #:upper16:.LANCHOR1	@ tmp168,
	str	r1, [fp, #-252]	@ tmp158, stChanOption.s32MaxWidth
	addls	r0, lr, r0, asl #2	@, tmp171, tmp168, D.56288,
	mov	r1, #136	@ tmp165,
	str	r1, [fp, #-244]	@ tmp165, stChanOption.s32MaxSliceNum
	rsb	r1, r4, r2	@ tmp177, eCapLevel, tmp239
	ldrls	lr, [r0, #460]	@ MinDispFspNum, CSWTCH.930
	movhi	lr, #6	@ MinDispFspNum,
	add	r0, r3, r1, asl #2	@, tmp179, tmp238, tmp177,
	ldr	ip, [r3, ip, asl #2]	@ tmp164, CapItem
	ldr	r1, [r0, #12]	@ D.50676, CapItem
	rsb	r0, r4, r2	@ tmp191, eCapLevel, tmp239
	str	ip, [fp, #-248]	@ tmp164, stChanOption.s32MaxHeight
	addls	ip, lr, #2	@ prephitmp.6390, MinDispFspNum,
	add	r3, r3, r0, asl #2	@, tmp193, tmp238, tmp191,
	movhi	ip, #8	@ prephitmp.6390,
	cmp	r1, ip	@ D.50676, prephitmp.6390
	mov	r2, #1	@ tmp184,
	subgt	r1, r1, #2	@ tmp182, D.50676,
	ldr	r3, [r3, #24]	@ tmp195, CapItem
	movle	r1, #1	@ tmp181,
	rsbgt	r1, lr, r1	@ tmp183, MinDispFspNum, tmp182
	cmp	r4, #24	@ eCapLevel,
	str	r1, [fp, #-228]	@ tmp183, stChanOption.s32MaxRefFrameNum
	str	lr, [fp, #-200]	@ MinDispFspNum, stChanOption.s32DisplayFrameNum
	mov	r1, #0	@ tmp196,
	str	r2, [fp, #-220]	@ tmp184, stChanOption.s32SupportBFrame
	str	r2, [fp, #-216]	@ tmp184, stChanOption.s32SupportH264
	str	r2, [fp, #-208]	@ tmp184, stChanOption.s32ReRangeEn
	str	r1, [fp, #-196]	@ tmp196, stChanOption.s32SlotWidth
	str	r3, [fp, #-204]	@ tmp195, stChanOption.s32SCDBufSize
	str	r1, [fp, #-192]	@ tmp196, stChanOption.s32SlotHeight
	streq	r1, [fp, #-228]	@ tmp196, stChanOption.s32MaxRefFrameNum
	streq	r2, [fp, #-200]	@ tmp184, stChanOption.s32DisplayFrameNum
	beq	.L2547	@,
	cmp	r4, #26	@ eCapLevel,
	beq	.L2555	@,
	cmp	r4, #18	@ eCapLevel,
	moveq	r3, #4	@ tmp202,
	streq	r3, [fp, #-228]	@ tmp202, stChanOption.s32MaxRefFrameNum
	moveq	r3, #2	@ tmp203,
	streq	r3, [fp, #-200]	@ tmp203, stChanOption.s32DisplayFrameNum
.L2547:
	mov	r0, r4	@, eCapLevel
	sub	r1, fp, #56	@,,
	sub	r2, fp, #68	@,,
	bl	VCTRL_GetChanMemSize	@
	cmp	r0, #0	@,
	bne	.L2556	@,
	cmp	r8, #0	@ pChanMem,
	beq	.L2550	@,
	ldr	r3, [r8, #8]	@ D.50696, <variable>.Length
	cmp	r3, #0	@ D.50696,
	beq	.L2550	@,
	ldr	ip, [r8, #0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	cmp	ip, #0	@ <variable>.PhyAddr,
	beq	.L2551	@,
	ldr	sl, [r8, #4]	@ <variable>.VirAddr, <variable>.VirAddr
	cmp	sl, #0	@ <variable>.VirAddr,
	beq	.L2551	@,
	ldr	lr, [fp, #-56]	@ VdmChanMemSize, VdmChanMemSize
	ldr	r1, [fp, #-68]	@ ScdChanMemSize, ScdChanMemSize
	add	r0, r1, lr	@ tmp209, ScdChanMemSize, VdmChanMemSize
	cmp	r3, r0	@ D.50696, tmp209
	blt	.L2551	@,
	ldr	lr, [fp, #-64]	@ D.50709, ScdChanMemSize
	sub	r8, fp, #180	@,,
	str	ip, [fp, #-100]	@ <variable>.PhyAddr, scd_MemRecord.PhyAddr
	sub	r9, fp, #164	@ tmp221,,
	str	r8, [fp, #-272]	@, %sfp
	rsb	r8, lr, r3	@ tmp220, D.50709, D.50696
	str	lr, [fp, #-92]	@ D.50709, scd_MemRecord.Length
	add	ip, ip, lr	@ tmp216, <variable>.PhyAddr, D.50709
	str	sl, [fp, #-96]	@ <variable>.VirAddr, scd_MemRecord.VirAddr
	add	lr, sl, lr	@ tmp218, <variable>.VirAddr, D.50709
	ldmia	r7, {r0, r1, r2, r3}	@ tmp237,,,,
	str	ip, [fp, #-84]	@ tmp216, vdh_MemRecord.PhyAddr
	str	lr, [fp, #-80]	@ tmp218, vdh_MemRecord.VirAddr
	mov	ip, #3	@ tmp212,
	str	r8, [fp, #-76]	@ tmp220, vdh_MemRecord.Length
	ldr	lr, [fp, #-272]	@, %sfp
	stmia	r9, {r0, r1, r2, r3}	@ tmp221,,,,
	str	ip, [fp, #-256]	@ tmp212, stChanOption.MemAllocMode
	ldmia	r5, {r0, r1, r2, r3}	@ tmp241,,,,
	mov	ip, #1	@ OneChanMemFlag,
	stmia	lr, {r0, r1, r2, r3}	@,,,,
	b	.L2552	@
.L2550:
	mov	ip, #0	@ OneChanMemFlag,
.L2552:
	mov	r0, r4	@, eCapLevel
	mov	r1, r6	@, tmp240
	mov	r3, ip	@, OneChanMemFlag
	mov	r2, #1	@,
	bl	VCTRL_CreateChanWithOption	@
	orr	r0, r0, r0, asr #31	@ D.50657,
.L2541:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L2555:
	mov	r2, #16	@ tmp200,
	mov	r3, #6	@ tmp201,
	str	r2, [fp, #-228]	@ tmp200, stChanOption.s32MaxRefFrameNum
	str	r3, [fp, #-200]	@ tmp201, stChanOption.s32DisplayFrameNum
	b	.L2547	@
.L2554:
	mov	r2, r0	@, eCapLevel
	movw	r1, #:lower16:.LC349	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC349	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50657,
	b	.L2541	@
.L2551:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC351	@,
	movt	r1, #:upper16:.LC351	@,
	bl	dprint_vfmw	@
	ldr	ip, [r8, #8]	@ <variable>.Length, <variable>.Length
	ldr	r2, [r8, #0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	mov	r0, #1	@,
	ldr	r3, [r8, #4]	@ <variable>.VirAddr, <variable>.VirAddr
	movw	r1, #:lower16:.LC352	@,
	movt	r1, #:upper16:.LC352	@,
	str	ip, [sp, #0]	@ <variable>.Length,
	bl	dprint_vfmw	@
	ldr	r3, [fp, #-56]	@ VdmChanMemSize, VdmChanMemSize
	ldr	r2, [fp, #-68]	@ ScdChanMemSize, ScdChanMemSize
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC353	@,
	movt	r1, #:upper16:.LC353	@,
	add	r2, r2, r3	@, ScdChanMemSize, VdmChanMemSize
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50657,
	b	.L2541	@
.L2556:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC350	@,
	movt	r1, #:upper16:.LC350	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50657,
	b	.L2541	@
	.fnend
	.size	VCTRL_CreateChan, .-VCTRL_CreateChan
	.align	2
	.global	VCTRL_RunProcess
	.type	VCTRL_RunProcess, %function
VCTRL_RunProcess:
	.fnstart
.LFB1534:
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
	movw	r5, #:lower16:.LANCHOR3	@ tmp207,
	movt	r5, #:upper16:.LANCHOR3	@ tmp207,
	movw	r4, #:lower16:.LANCHOR0	@ tmp206,
	movt	r4, #:upper16:.LANCHOR0	@ tmp206,
	mov	r3, #100	@ tmp186,
	ldr	r0, [r5, #3864]	@ g_SleepTime.455, g_SleepTime
	str	r3, [r4, #152]	@ tmp186, s_VfmwCTrl.s32ThreadPos
	cmp	r0, #0	@ g_SleepTime.455,
	ble	.L2558	@,
	bl	msleep	@
.L2558:
	ldr	r0, .L2630	@,
	bl	OSAL_SpinLockIRQ	@
	bl	SM_Wakeup	@
	ldr	r0, [r5, #3872]	@ g_StopDec, g_StopDec
	mov	r2, #101	@ tmp191,
	str	r2, [r4, #152]	@ tmp191, s_VfmwCTrl.s32ThreadPos
	cmp	r0, #0	@ g_StopDec,
	movne	r5, #0	@ ret,
	beq	.L2612	@,
.L2560:
	mov	r6, #102	@ tmp195,
	str	r6, [r4, #152]	@ tmp195, s_VfmwCTrl.s32ThreadPos
	bl	VDMDRV_WakeUpVdm	@
	mov	r0, #0	@,
	bl	SCDDRV_EnableInt	@
	movw	r1, #:lower16:g_vdm_hal_fun_ptr	@ tmp196,
	movt	r1, #:upper16:g_vdm_hal_fun_ptr	@ tmp196,
	ldr	r3, [r1, #76]	@ D.49988, g_vdm_hal_fun_ptr.pfun_VDMHAL_EnableInt
	cmp	r3, #0	@ D.49988,
	beq	.L2613	@,
	mov	r0, #0	@,
	blx	r3	@ D.49988
.L2564:
	mov	r0, #0	@,
	mov	r1, r0	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #1	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #2	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #3	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #4	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #5	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #6	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #7	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #8	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #9	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #10	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #11	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #12	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #13	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #14	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r1, #0	@,
	mov	r0, #15	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r0, #0	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2614	@,
.L2563:
	mov	r0, #1	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@ temp.6441,
	mov	r6, r0	@ temp.6441,
	beq	.L2615	@,
.L2567:
	mov	r0, #2	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2616	@,
.L2570:
	mov	r0, #3	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2617	@,
.L2573:
	mov	r0, #4	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2618	@,
.L2576:
	mov	r0, #5	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2619	@,
.L2579:
	mov	r0, #6	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2620	@,
.L2582:
	mov	r0, #7	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2621	@,
.L2585:
	mov	r0, #8	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2622	@,
.L2588:
	mov	r0, #9	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2623	@,
.L2591:
	mov	r0, #10	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2624	@,
.L2594:
	mov	r0, #11	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2625	@,
.L2597:
	mov	r0, #12	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2626	@,
.L2600:
	mov	r0, #13	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2627	@,
.L2603:
	mov	r0, #14	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2628	@,
.L2606:
	mov	r0, #15	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2629	@,
.L2609:
	ldr	r0, .L2630	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r1, #10	@,
	ldr	r0, .L2630+4	@,
	mov	ip, #105	@ tmp201,
	str	ip, [r4, #152]	@ tmp201, s_VfmwCTrl.s32ThreadPos
	bl	OSAL_WaitEvent	@
	mov	r0, r5	@, ret
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L2612:
	bl	DecSyntax	@
	mov	r5, r0	@ ret,
	b	.L2560	@
.L2613:
	mov	r0, r3	@, D.49988
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #578	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L2564	@
.L2621:
	mov	r0, #7	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6460,
	mov	r0, #7	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2587	@,
	cmp	r6, #1	@ tmp.6460,
	bne	.L2585	@,
.L2587:
	mov	r1, #3	@,
	mov	r0, #7	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #7	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #7	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2585	@
.L2622:
	mov	r0, #8	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6463,
	mov	r0, #8	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2590	@,
	cmp	r6, #1	@ tmp.6463,
	bne	.L2588	@,
.L2590:
	mov	r1, #3	@,
	mov	r0, #8	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #8	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #8	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2588	@
.L2623:
	mov	r0, #9	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6466,
	mov	r0, #9	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2593	@,
	cmp	r6, #1	@ tmp.6466,
	bne	.L2591	@,
.L2593:
	mov	r1, #3	@,
	mov	r0, #9	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #9	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #9	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2591	@
.L2624:
	mov	r0, #10	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6469,
	mov	r0, #10	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2596	@,
	cmp	r6, #1	@ tmp.6469,
	bne	.L2594	@,
.L2596:
	mov	r1, #3	@,
	mov	r0, #10	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #10	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #10	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2594	@
.L2625:
	mov	r0, #11	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6472,
	mov	r0, #11	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2599	@,
	cmp	r6, #1	@ tmp.6472,
	bne	.L2597	@,
.L2599:
	mov	r1, #3	@,
	mov	r0, #11	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #11	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #11	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2597	@
.L2626:
	mov	r0, #12	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6475,
	mov	r0, #12	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2602	@,
	cmp	r6, #1	@ tmp.6475,
	bne	.L2600	@,
.L2602:
	mov	r1, #3	@,
	mov	r0, #12	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #12	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #12	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2600	@
.L2627:
	mov	r0, #13	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6478,
	mov	r0, #13	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2605	@,
	cmp	r6, #1	@ tmp.6478,
	bne	.L2603	@,
.L2605:
	mov	r1, #3	@,
	mov	r0, #13	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #13	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #13	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2603	@
.L2628:
	mov	r0, #14	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6481,
	mov	r0, #14	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2608	@,
	cmp	r6, #1	@ tmp.6481,
	bne	.L2606	@,
.L2608:
	mov	r1, #3	@,
	mov	r0, #14	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #14	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #14	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2606	@
.L2617:
	mov	r0, #3	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6448,
	mov	r0, #3	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2575	@,
	cmp	r6, #1	@ tmp.6448,
	bne	.L2573	@,
.L2575:
	mov	r0, #3	@,
	mov	r1, r0	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #3	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #3	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2573	@
.L2618:
	mov	r0, #4	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6451,
	mov	r0, #4	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2578	@,
	cmp	r6, #1	@ tmp.6451,
	bne	.L2576	@,
.L2578:
	mov	r1, #3	@,
	mov	r0, #4	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #4	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #4	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2576	@
.L2619:
	mov	r0, #5	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6454,
	mov	r0, #5	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2581	@,
	cmp	r6, #1	@ tmp.6454,
	bne	.L2579	@,
.L2581:
	mov	r1, #3	@,
	mov	r0, #5	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #5	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #5	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2579	@
.L2620:
	mov	r0, #6	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6457,
	mov	r0, #6	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2584	@,
	cmp	r6, #1	@ tmp.6457,
	bne	.L2582	@,
.L2584:
	mov	r1, #3	@,
	mov	r0, #6	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #6	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #6	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2582	@
.L2615:
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r7, r0	@ tmp.6442,
	mov	r0, r6	@, temp.6441
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2569	@,
	cmp	r7, #1	@ tmp.6442,
	bne	.L2567	@,
.L2569:
	mov	r1, #3	@,
	mov	r0, #1	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #1	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #1	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2567	@
.L2616:
	mov	r0, #2	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6445,
	mov	r0, #2	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2572	@,
	cmp	r6, #1	@ tmp.6445,
	bne	.L2570	@,
.L2572:
	mov	r1, #3	@,
	mov	r0, #2	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #2	@,
	bl	VCTRL_ResetChan	@
	mov	r0, #2	@,
	mov	r1, r0	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2570	@
.L2614:
	mov	r0, #0	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6439,
	mov	r0, #0	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2566	@,
	cmp	r6, #1	@ tmp.6439,
	bne	.L2563	@,
.L2566:
	mov	r1, #3	@,
	mov	r0, #0	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #0	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #0	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2563	@
.L2629:
	mov	r0, #15	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp,
	mov	r0, #15	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2610	@,
	cmp	r6, #1	@ tmp,
	bne	.L2609	@,
.L2610:
	mov	r1, #3	@,
	mov	r0, #15	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #15	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #15	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2609	@
.L2631:
	.align	2
.L2630:
	.word	.LANCHOR0+520
	.word	.LANCHOR3+3548
	.fnend
	.size	VCTRL_RunProcess, .-VCTRL_RunProcess
	.align	2
	.global	VFMW_CTRL_thread_proc
	.type	VFMW_CTRL_thread_proc, %function
VFMW_CTRL_thread_proc:
	.fnstart
.LFB1533:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
.L2633:
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r4, #:lower16:.LANCHOR0	@ tmp167,
	movt	r4, #:upper16:.LANCHOR0	@ tmp167,
	mov	r6, #0	@ tmp176,
	mov	r8, #1	@ tmp177,
	mov	r7, #5	@ tmp181,
.L2638:
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC354	@,
	movt	r1, #:upper16:.LC354	@,
	str	r6, [r4, #152]	@ tmp176, s_VfmwCTrl.s32ThreadPos
	bl	dprint_vfmw	@
	ldr	r3, [r4, #144]	@ temp.6510, s_VfmwCTrl.eTaskCommand
	mov	r5, #2	@ tmp144,
	str	r5, [r4, #140]	@ tmp144, s_VfmwCTrl.eTaskState
	cmp	r3, r5	@ temp.6510,
	bne	.L2637	@,
	b	.L2634	@
.L2644:
	str	r5, [r4, #152]	@ tmp172, s_VfmwCTrl.s32ThreadPos
	bl	VCTRL_RunProcess	@
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC355	@,
	movt	r1, #:upper16:.LC355	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #144]	@ D.49949, s_VfmwCTrl.eTaskCommand
	cmp	r3, #2	@ D.49949,
	beq	.L2634	@,
.L2637:
	cmp	r3, #3	@ D.49949,
	bne	.L2644	@,
.L2635:
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC358	@,
	movt	r1, #:upper16:.LC358	@,
	mov	r2, #6	@ tmp162,
	str	r2, [r4, #152]	@ tmp162, s_VfmwCTrl.s32ThreadPos
	bl	dprint_vfmw	@
	mov	r0, #0	@ tmp165,
	str	r0, [r4, #140]	@ tmp165, s_VfmwCTrl.eTaskState
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L2634:
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC356	@,
	movt	r1, #:upper16:.LC356	@,
	mov	r3, #4	@ tmp154,
	str	r3, [r4, #152]	@ tmp154, s_VfmwCTrl.s32ThreadPos
	bl	dprint_vfmw	@
	str	r8, [r4, #140]	@ tmp177, s_VfmwCTrl.eTaskState
.L2639:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC357	@,
	movt	r1, #:upper16:.LC357	@,
	str	r7, [r4, #152]	@ tmp181, s_VfmwCTrl.s32ThreadPos
	bl	dprint_vfmw	@
	ldr	r3, [r4, #144]	@ temp.6507, s_VfmwCTrl.eTaskCommand
	cmp	r3, #1	@ temp.6507,
	beq	.L2638	@,
	cmp	r3, #3	@ temp.6507,
	mov	r0, #10	@,
	beq	.L2635	@,
	bl	msleep	@
	b	.L2639	@
	.fnend
	.size	VFMW_CTRL_thread_proc, .-VFMW_CTRL_thread_proc
	.align	2
	.global	VCTRL_ResetChanWithOption
	.type	VCTRL_ResetChanWithOption, %function
VCTRL_ResetChanWithOption:
	.fnstart
.LFB1581:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #12
	sub	sp, sp, #12	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r5, #:lower16:.LANCHOR0	@ tmp203,
	movt	r5, #:upper16:.LANCHOR0	@ tmp203,
	mov	r4, r0	@ ChanID, ChanID
	mov	r7, r1	@ pOption, pOption
	ldr	r3, [r5, r0, asl #2]	@ D.51788, s_pstVfmwChan
	cmp	r3, #0	@ D.51788,
	beq	.L2657	@,
	ldr	r2, [r1, #0]	@ <variable>.s32KeepBS, <variable>.s32KeepBS
	cmp	r2, #1	@ <variable>.s32KeepBS,
	bhi	.L2658	@,
	ldr	r8, [r3, #16]	@ ChanIsRun, <variable>.s32IsRun
	bl	VCTRL_StopChan	@
	ldr	r3, [r5, r4, asl #2]	@ tmp149, s_pstVfmwChan
	mov	r6, #0	@ tmp150,
	add	r1, r5, #1456	@ tmp155, tmp203,
	mov	r0, #300	@ tmp158,
	add	ip, r1, #4	@ tmp155, tmp155,
	mov	r1, r0	@, tmp158
	str	r6, [r3, #344]	@ tmp150, <variable>.s32CountNoDecparamFlag
	ldr	r3, [r5, r4, asl #2]	@ tmp152, s_pstVfmwChan
	mla	r0, r0, r4, ip	@, tmp158, ChanID, tmp155
	str	r6, [r3, #348]	@ tmp150, <variable>.u32NoDecparamStartTime
	bl	__memzero	@
	mov	r1, r6	@, tmp150
	mov	r0, r4	@, ChanID
	bl	VCTRL_SetSendStreamAgainFlag	@
	ldr	ip, [r7, #4]	@ <variable>.s32KeepSPSPPS, <variable>.s32KeepSPSPPS
	ldr	r2, [r5, r4, asl #2]	@ tmp161, s_pstVfmwChan
	mov	r0, r4	@, ChanID
	str	ip, [r2, #1248]	@ <variable>.s32KeepSPSPPS, <variable>.stSynExtraData.s32KeepSPSPPS
	bl	InitSyntaxCtx	@
	ldr	r3, [r5, r4, asl #2]	@ temp.6540, s_pstVfmwChan
	add	r1, r3, #250880	@, temp.6540,
	ldr	r0, [r3, #544]	@, <variable>.eVidStd
	add	r1, r1, #704	@,,
	bl	ReleaseCurPic	@
	ldr	r2, [r5, r4, asl #2]	@ tmp169, s_pstVfmwChan
	mov	r1, #416	@,
	add	r0, r2, #688	@, tmp169,
	bl	__memzero	@
	ldr	ip, [r5, r4, asl #2]	@ tmp171, s_pstVfmwChan
	mov	r0, #608	@ tmp172,
	mvn	r3, #0	@,
	mvn	r2, #0	@ tmp173,
	mov	r1, #616	@ tmp176,
	strd	r2, [ip, r0]	@ tmp173, tmp171, tmp172
	ldr	r0, [r5, r4, asl #2]	@ tmp175, s_pstVfmwChan
	strd	r2, [r0, r1]	@ tmp173, tmp175, tmp176
	ldr	ip, [r5, r4, asl #2]	@ tmp179, s_pstVfmwChan
	str	r6, [ip, #1104]	@ tmp150, <variable>.stSynExtraData.s32NewPicSegDetector
	ldr	r0, [r5, r4, asl #2]	@ prephitmp.6526, s_pstVfmwChan
	ldr	r1, [r0, #1416]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r1, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	streq	r6, [r0, #1456]	@ tmp150, <variable>.stSynExtraData.s32WaitFsFlag
	ldreq	r0, [r5, r4, asl #2]	@ prephitmp.6526, s_pstVfmwChan
	ldr	r3, [r0, #544]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #18	@ <variable>.eVidStd,
	beq	.L2650	@,
	mov	r0, r4	@, ChanID
	bl	FSP_ResetInstance	@
.L2651:
	mov	r0, r4	@, ChanID
	bl	InitUsdPool	@
	ldr	r2, [r7, #0]	@ <variable>.s32KeepBS, <variable>.s32KeepBS
	cmp	r2, #0	@ <variable>.s32KeepBS,
	beq	.L2659	@,
.L2652:
	ldr	lr, [r5, #1372]	@ g_ResetCreateNewSave, g_ResetCreateNewSave
	cmp	lr, #0	@ g_ResetCreateNewSave,
	beq	.L2653	@,
	movw	r5, #:lower16:.LANCHOR3	@ tmp189,
	movt	r5, #:upper16:.LANCHOR3	@ tmp189,
	add	r5, r5, r4, asl #2	@, tmp192, tmp189, ChanID,
	str	r4, [fp, #-40]	@ ChanID, data
	ldr	r0, [r5, #3572]	@ tmp194, vfmw_save_str_file
	cmp	r0, #0	@ tmp194,
	beq	.L2654	@,
	sub	r6, fp, #40	@ data.559,,
	mov	r0, #512	@,
	mov	r1, r6	@, data.559
	bl	VCTRL_SetDbgOption	@
	ldr	ip, [r5, #3572]	@ tmp200, vfmw_save_str_file
	cmp	ip, #0	@ tmp200,
	beq	.L2654	@,
	mov	r1, r6	@, data.559
	mov	r0, #512	@,
	bl	VCTRL_SetDbgOption	@
.L2654:
	movw	r1, #:lower16:.LC318	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC318	@,
	bl	dprint_vfmw	@
.L2653:
	cmp	r8, #0	@ ChanIsRun,
	bne	.L2660	@,
.L2655:
	mov	r0, r4	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	mov	r0, #0	@ D.51792,
.L2647:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2659:
	mov	r0, r4	@, ChanID
	bl	SM_Reset	@
	b	.L2652	@
.L2660:
	mov	r0, r4	@, ChanID
	bl	VCTRL_StartChan	@
	b	.L2655	@
.L2650:
	mov	r0, r4	@, ChanID
	bl	FSP_EmptyInstance	@
	b	.L2651	@
.L2658:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC359	@,
	movw	r2, #3915	@,
	movt	r1, #:upper16:.LC359	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51792,
	b	.L2647	@
.L2657:
	mov	r0, r3	@, D.51788
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #3911	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.51792,
	b	.L2647	@
	.fnend
	.size	VCTRL_ResetChanWithOption, .-VCTRL_ResetChanWithOption
	.align	2
	.global	VID_EofState_Enum2Str
	.type	VID_EofState_Enum2Str, %function
VID_EofState_Enum2Str:
	.fnstart
.LFB1639:
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
	mov	r4, r1	@ strState, strState
	cmp	r0, #4	@ eState,
	ldrls	pc, [pc, r0, asl #2]	@ eState
	b	.L2662	@
.L2668:
	.word	.L2663
	.word	.L2664
	.word	.L2665
	.word	.L2666
	.word	.L2667
.L2667:
	mov	r0, r1	@, strState
	mov	r2, #7	@,
	movw	r1, #:lower16:.LC364	@,
	movt	r1, #:upper16:.LC364	@,
	bl	memcpy	@
	mov	ip, #0	@ tmp168,
	strb	ip, [r4, #7]	@ tmp168,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2662:
	mov	r3, #0	@ tmp170,
	strb	r3, [r1, #0]	@ tmp170,* strState
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2663:
	mov	r0, r1	@, strState
	mov	r2, #5	@,
	movw	r1, #:lower16:.LC360	@,
	movt	r1, #:upper16:.LC360	@,
	bl	memcpy	@
	mov	r3, #0	@ tmp140,
	strb	r3, [r4, #5]	@ tmp140,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2664:
	mov	r0, r1	@, strState
	mov	r2, #8	@,
	movw	r1, #:lower16:.LC361	@,
	movt	r1, #:upper16:.LC361	@,
	bl	memcpy	@
	mov	r0, #0	@ tmp147,
	strb	r0, [r4, #8]	@ tmp147,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2665:
	mov	r0, r1	@, strState
	mov	r2, #7	@,
	movw	r1, #:lower16:.LC362	@,
	movt	r1, #:upper16:.LC362	@,
	bl	memcpy	@
	mov	r1, #0	@ tmp154,
	strb	r1, [r4, #7]	@ tmp154,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2666:
	mov	r0, r1	@, strState
	mov	r2, #7	@,
	movw	r1, #:lower16:.LC363	@,
	movt	r1, #:upper16:.LC363	@,
	bl	memcpy	@
	mov	r2, #0	@ tmp161,
	strb	r2, [r4, #7]	@ tmp161,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	VID_EofState_Enum2Str, .-VID_EofState_Enum2Str
	.align	2
	.global	VID_STD_Enum2Str
	.type	VID_STD_Enum2Str, %function
VID_STD_Enum2Str:
	.fnstart
.LFB1638:
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
	mov	r4, r1	@ strVidStd, strVidStd
	cmp	r0, #19	@ eVidStd,
	ldrls	pc, [pc, r0, asl #2]	@ eVidStd
	b	.L2672	@
.L2693:
	.word	.L2673
	.word	.L2674
	.word	.L2675
	.word	.L2676
	.word	.L2677
	.word	.L2678
	.word	.L2679
	.word	.L2680
	.word	.L2681
	.word	.L2682
	.word	.L2683
	.word	.L2684
	.word	.L2685
	.word	.L2686
	.word	.L2687
	.word	.L2688
	.word	.L2689
	.word	.L2690
	.word	.L2691
	.word	.L2692
.L2692:
	mov	r0, r1	@, strVidStd
	mov	r2, #8	@,
	movw	r1, #:lower16:.LC384	@,
	movt	r1, #:upper16:.LC384	@,
	bl	memcpy	@
	mov	ip, #0	@ tmp273,
	strb	ip, [r4, #8]	@ tmp273,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2691:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC383	@,
	movt	r1, #:upper16:.LC383	@,
	bl	memcpy	@
	mov	r2, #0	@ tmp266,
	strb	r2, [r4, #4]	@ tmp266,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2690:
	mov	r0, r1	@, strVidStd
	mov	r2, #3	@,
	movw	r1, #:lower16:.LC382	@,
	movt	r1, #:upper16:.LC382	@,
	bl	memcpy	@
	mov	r1, #0	@ tmp259,
	strb	r1, [r4, #3]	@ tmp259,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2689:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC381	@,
	movt	r1, #:upper16:.LC381	@,
	bl	memcpy	@
	mov	r0, #0	@ tmp252,
	strb	r0, [r4, #4]	@ tmp252,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2688:
	mov	r0, r1	@, strVidStd
	mov	r2, #3	@,
	movw	r1, #:lower16:.LC380	@,
	movt	r1, #:upper16:.LC380	@,
	bl	memcpy	@
	mov	r3, #0	@ tmp245,
	strb	r3, [r4, #3]	@ tmp245,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2687:
	mov	r0, r1	@, strVidStd
	mov	r2, #8	@,
	movw	r1, #:lower16:.LC379	@,
	movt	r1, #:upper16:.LC379	@,
	bl	memcpy	@
	mov	ip, #0	@ tmp238,
	strb	ip, [r4, #8]	@ tmp238,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2686:
	mov	r0, r1	@, strVidStd
	mov	r2, #3	@,
	movw	r1, #:lower16:.LC378	@,
	movt	r1, #:upper16:.LC378	@,
	bl	memcpy	@
	mov	r2, #0	@ tmp231,
	strb	r2, [r4, #3]	@ tmp231,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2685:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC377	@,
	movt	r1, #:upper16:.LC377	@,
	bl	memcpy	@
	mov	r1, #0	@ tmp224,
	strb	r1, [r4, #4]	@ tmp224,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2684:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC376	@,
	movt	r1, #:upper16:.LC376	@,
	bl	memcpy	@
	mov	r0, #0	@ tmp217,
	strb	r0, [r4, #4]	@ tmp217,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2683:
	mov	r0, r1	@, strVidStd
	mov	r2, #3	@,
	movw	r1, #:lower16:.LC375	@,
	movt	r1, #:upper16:.LC375	@,
	bl	memcpy	@
	mov	r3, #0	@ tmp210,
	strb	r3, [r4, #3]	@ tmp210,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2682:
	mov	r0, r1	@, strVidStd
	mov	r2, #5	@,
	movw	r1, #:lower16:.LC374	@,
	movt	r1, #:upper16:.LC374	@,
	bl	memcpy	@
	mov	ip, #0	@ tmp203,
	strb	ip, [r4, #5]	@ tmp203,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2681:
	mov	r0, r1	@, strVidStd
	mov	r2, #5	@,
	movw	r1, #:lower16:.LC373	@,
	movt	r1, #:upper16:.LC373	@,
	bl	memcpy	@
	mov	r2, #0	@ tmp196,
	strb	r2, [r4, #5]	@ tmp196,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2680:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC372	@,
	movt	r1, #:upper16:.LC372	@,
	bl	memcpy	@
	mov	r1, #0	@ tmp189,
	strb	r1, [r4, #4]	@ tmp189,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2679:
	mov	r0, r1	@, strVidStd
	mov	r2, #3	@,
	movw	r1, #:lower16:.LC371	@,
	movt	r1, #:upper16:.LC371	@,
	bl	memcpy	@
	mov	r0, #0	@ tmp182,
	strb	r0, [r4, #3]	@ tmp182,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2678:
	mov	r0, r1	@, strVidStd
	mov	r2, #5	@,
	movw	r1, #:lower16:.LC370	@,
	movt	r1, #:upper16:.LC370	@,
	bl	memcpy	@
	mov	r3, #0	@ tmp175,
	strb	r3, [r4, #5]	@ tmp175,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2677:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC369	@,
	movt	r1, #:upper16:.LC369	@,
	bl	memcpy	@
	mov	ip, #0	@ tmp168,
	strb	ip, [r4, #4]	@ tmp168,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2676:
	mov	r0, r1	@, strVidStd
	mov	r2, #5	@,
	movw	r1, #:lower16:.LC368	@,
	movt	r1, #:upper16:.LC368	@,
	bl	memcpy	@
	mov	r2, #0	@ tmp161,
	strb	r2, [r4, #5]	@ tmp161,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2675:
	mov	r0, r1	@, strVidStd
	mov	r2, #5	@,
	movw	r1, #:lower16:.LC367	@,
	movt	r1, #:upper16:.LC367	@,
	bl	memcpy	@
	mov	r1, #0	@ tmp154,
	strb	r1, [r4, #5]	@ tmp154,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2674:
	mov	r0, r1	@, strVidStd
	mov	r2, #3	@,
	movw	r1, #:lower16:.LC366	@,
	movt	r1, #:upper16:.LC366	@,
	bl	memcpy	@
	mov	r0, #0	@ tmp147,
	strb	r0, [r4, #3]	@ tmp147,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2673:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC365	@,
	movt	r1, #:upper16:.LC365	@,
	bl	memcpy	@
	mov	r3, #0	@ tmp140,
	strb	r3, [r4, #4]	@ tmp140,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2672:
	mov	r3, #0	@ tmp275,
	strb	r3, [r1, #0]	@ tmp275,* strVidStd
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	VID_STD_Enum2Str, .-VID_STD_Enum2Str
	.align	2
	.global	vfmw_read_proc_scd
	.type	vfmw_read_proc_scd, %function
vfmw_read_proc_scd:
	.fnstart
.LFB1645:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #40
	sub	sp, sp, #40	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r7, #:lower16:g_pScdDrvParamBase	@ tmp145,
	movt	r7, #:upper16:g_pScdDrvParamBase	@ tmp145,
	mov	r4, r0	@ p, p
	movw	r1, #:lower16:.LC385	@,
	movt	r1, #:upper16:.LC385	@,
	ldr	r5, [r7, #0]	@ pScdDrvParam, g_pScdDrvParamBase
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC386	@,
	movt	r1, #:upper16:.LC66	@,
	ldr	r3, [r5, #76]	@, <variable>.IsScdDrvOpen
	movt	r2, #:upper16:.LC386	@,
	bl	seq_printf	@
	ldr	r3, [r5, #84]	@, <variable>.SCDState
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC387	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC387	@,
	bl	seq_printf	@
	ldr	r3, [r5, #80]	@, <variable>.ThisInstID
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC388	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC388	@,
	bl	seq_printf	@
	ldr	r3, [r5, #88]	@, <variable>.LastProcessTime
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC389	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC389	@,
	bl	seq_printf	@
	ldr	r3, [r5, #0]	@, <variable>.ScdDrvMem.HwMemAddr
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC391	@,
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC391	@,
	bl	seq_printf	@
	ldr	r3, [r5, #4]	@, <variable>.ScdDrvMem.HwMemSize
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC392	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC392	@,
	bl	seq_printf	@
	ldr	r3, [r5, #8]	@, <variable>.ScdDrvMem.DownMsgMemAddr
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC393	@,
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC393	@,
	bl	seq_printf	@
	ldr	r3, [r5, #20]	@, <variable>.ScdDrvMem.UpMsgMemAddr
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC394	@,
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC394	@,
	bl	seq_printf	@
	movw	r0, #:lower16:g_pSmIISBase	@ tmp173,
	movt	r0, #:upper16:g_pSmIISBase	@ tmp173,
	movw	r3, #:lower16:.LANCHOR0	@ tmp171,
	movt	r3, #:upper16:.LANCHOR0	@ tmp171,
	ldr	r2, [r0, #0]	@ g_pSmIISBase, g_pSmIISBase
	ldr	r7, [r3, #1364]	@ i, g_CurProcChan
	ldr	r5, [r2, #40]	@ pInst, <variable>.pSmInstArray
	cmp	r5, #0	@ pInst,
	beq	.L2697	@,
	movw	ip, #:lower16:190872	@ tmp174,
	movt	ip, #:upper16:190872	@ tmp174,
	ldr	r1, [r5, ip]	@ <variable>.Mode, <variable>.Mode
	cmp	r1, #0	@ <variable>.Mode,
	bne	.L2703	@,
.L2697:
	mov	r0, #0	@,
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2703:
	add	r6, r5, #200	@ D.54761, pInst,
	sub	r1, fp, #36	@,,
	mov	r0, r6	@, D.54761
	bl	GetRawStreamSize	@
	cmp	r0, #0	@,
	bne	.L2704	@,
	mov	r0, r6	@, D.54761
	sub	r1, fp, #32	@,,
	bl	GetRawStreamNum	@
	cmp	r0, #0	@,
	bne	.L2705	@,
.L2699:
	add	r6, r5, #98304	@ D.54769, pInst,
	sub	r1, fp, #44	@,,
	add	r6, r6, #224	@ D.54769, D.54769,
	mov	r0, r6	@, D.54769
	bl	GetSegStreamSize	@
	cmp	r0, #0	@,
	bne	.L2706	@,
.L2700:
	mov	r0, r6	@, D.54769
	sub	r1, fp, #40	@,,
	bl	GetSegStreamNum	@
	cmp	r0, #0	@,
	bne	.L2707	@,
.L2701:
	sub	r6, fp, #64	@ tmp194,,
	ldr	r0, [r5, #56]	@, <variable>.Config.VidStd
	mov	r1, r6	@, tmp194
	bl	VID_STD_Enum2Str	@
	mov	r2, r7	@, i
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC395	@,
	movt	r1, #:upper16:.LC395	@,
	bl	seq_printf	@
	movw	ip, #:lower16:190872	@ tmp198,
	movt	ip, #:upper16:190872	@ tmp198,
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC396	@,
	ldr	r3, [r5, ip]	@, <variable>.Mode
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC396	@,
	bl	seq_printf	@
	mov	r3, r6	@, tmp194
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC397	@,
	movw	r2, #:lower16:.LC398	@,
	movt	r1, #:upper16:.LC397	@,
	movt	r2, #:upper16:.LC398	@,
	bl	seq_printf	@
	ldrsb	r3, [r5, #1]	@, <variable>.IsCounting
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC399	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC399	@,
	bl	seq_printf	@
	ldr	r3, [r5, #92]	@, <variable>.Config.IsOmxPath
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC400	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC400	@,
	bl	seq_printf	@
	ldr	r3, [r5, #60]	@, <variable>.Config.BufPhyAddr
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC401	@,
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC401	@,
	bl	seq_printf	@
	ldr	r3, [r5, #64]	@, <variable>.Config.BufSize
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC402	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC402	@,
	bl	seq_printf	@
	movw	r3, #:lower16:204752	@ tmp217,
	movt	r3, #:upper16:204752	@ tmp217,
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC403	@,
	ldr	r3, [r5, r3]	@, <variable>.u32RawSizeCount
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC403	@,
	bl	seq_printf	@
	movw	r2, #:lower16:204756	@ tmp221,
	movt	r2, #:upper16:204756	@ tmp221,
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movt	r1, #:upper16:.LC66	@,
	ldr	r3, [r5, r2]	@, <variable>.u32RawNumCount
	movw	r2, #:lower16:.LC404	@,
	movt	r2, #:upper16:.LC404	@,
	bl	seq_printf	@
	ldr	r3, [fp, #-36]	@, RawSize
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC405	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC405	@,
	bl	seq_printf	@
	ldr	r3, [fp, #-32]	@, RawNum
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC406	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC406	@,
	bl	seq_printf	@
	ldr	r3, [fp, #-44]	@, SegSize
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC407	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC407	@,
	bl	seq_printf	@
	ldr	r3, [fp, #-40]	@, SegNum
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC408	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC408	@,
	bl	seq_printf	@
	movw	ip, #:lower16:190720	@ tmp237,
	movt	ip, #:upper16:190720	@ tmp237,
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC409	@,
	ldr	r3, [r5, ip]	@, <variable>.StreamSegArray.SegBufReadAddr
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC409	@,
	bl	seq_printf	@
	movw	r3, #:lower16:190724	@ tmp241,
	movt	r3, #:upper16:190724	@ tmp241,
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC410	@,
	ldr	r3, [r5, r3]	@, <variable>.StreamSegArray.SegBufWriteAddr
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC410	@,
	bl	seq_printf	@
	movw	r2, #:lower16:204736	@ tmp245,
	movt	r2, #:upper16:204736	@ tmp245,
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC411	@,
	movt	r1, #:upper16:.LC411	@,
	ldr	r3, [r5, r2]	@, <variable>.BitRate
	movw	r2, #:lower16:.LC412	@,
	movt	r2, #:upper16:.LC412	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	b	.L2697	@
.L2704:
	ldr	r2, .L2708	@,
	movw	r3, #9111	@,
	movw	r1, #:lower16:.LC163	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC163	@,
	bl	dprint_vfmw	@
	mov	r0, r6	@, D.54761
	sub	r1, fp, #32	@,,
	bl	GetRawStreamNum	@
	cmp	r0, #0	@,
	beq	.L2699	@,
.L2705:
	add	r6, r5, #98304	@ D.54769, pInst,
	ldr	r2, .L2708	@,
	add	r6, r6, #224	@ D.54769, D.54769,
	movw	r3, #9116	@,
	movw	r1, #:lower16:.LC163	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC163	@,
	bl	dprint_vfmw	@
	sub	r1, fp, #44	@,,
	mov	r0, r6	@, D.54769
	bl	GetSegStreamSize	@
	cmp	r0, #0	@,
	beq	.L2700	@,
.L2706:
	ldr	r2, .L2708	@,
	movw	r3, #9121	@,
	movw	r1, #:lower16:.LC163	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC163	@,
	bl	dprint_vfmw	@
	mov	r0, r6	@, D.54769
	sub	r1, fp, #40	@,,
	bl	GetSegStreamNum	@
	cmp	r0, #0	@,
	beq	.L2701	@,
.L2707:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L2708	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #9126	@,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	b	.L2701	@
.L2709:
	.align	2
.L2708:
	.word	.LANCHOR1+492
	.fnend
	.size	vfmw_read_proc_scd, .-vfmw_read_proc_scd
	.global	__aeabi_uidiv
	.align	2
	.global	vfmw_read_proc_dec
	.type	vfmw_read_proc_dec, %function
vfmw_read_proc_dec:
	.fnstart
.LFB1647:
	@ args = 0, pretend = 0, frame = 88
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #116
	sub	sp, sp, #116	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r9, #:lower16:.LANCHOR0	@ tmp493,
	movt	r9, #:upper16:.LANCHOR0	@ tmp493,
	movw	r1, #:lower16:.LC413	@,
	movt	r1, #:upper16:.LC413	@,
	mov	r4, #0	@ tmp165,
	ldr	r2, [r9, #1364]	@, g_CurProcChan
	movw	r6, #16718	@ tmp164,
	str	r4, [fp, #-64]	@ tmp165, szAttach
	mov	r5, r0	@ p, p
	str	r6, [fp, #-68]	@ tmp164, szAttach
	str	r4, [fp, #-60]	@ tmp165, szAttach
	bl	seq_printf	@
	ldr	r6, [r9, #1364]	@ i, g_CurProcChan
	movw	r3, #:lower16:s_pFspInst	@ tmp172,
	movt	r3, #:upper16:s_pFspInst	@ tmp172,
	str	r4, [fp, #-48]	@ tmp165, RefNum
	ldr	r8, [r3, r6, asl #2]	@ pFsp, s_pFspInst
	cmp	r8, r4	@ pFsp,
	beq	.L2711	@,
	ldr	sl, [r9, r6, asl #2]	@ pChan, s_pstVfmwChan
	cmp	sl, r4	@ pChan,
	beq	.L2711	@,
	movw	r7, #:lower16:g_ChanCtx	@ tmp176,
	add	r2, r6, #32	@ tmp177, i,
	movt	r7, #:upper16:g_ChanCtx	@ tmp176,
	str	r4, [fp, #-56]	@ tmp165, NewNum
	str	r4, [fp, #-52]	@ tmp165, ReadNum
	ldr	r1, [r7, r2, asl #2]	@ tmp178, g_ChanCtx.ChanDecByVdhPlusOne
	subs	r0, r1, #1	@, tmp178,
	str	r0, [fp, #-116]	@, %sfp
	bmi	.L2740	@,
	ldr	r1, [fp, #-116]	@, %sfp
	movw	r4, #:lower16:g_VdmExtParam	@ tmp186,
	movt	r4, #:upper16:g_VdmExtParam	@ tmp186,
	mov	r2, #140	@ tmp189,
	mla	r7, r2, r1, r4	@ tmp190, tmp189,, tmp186
	ldr	r0, [r7, #4]	@ <variable>.VdmAttachStr.VdmAttachMode, <variable>.VdmAttachStr.VdmAttachMode
	cmp	r0, #0	@ <variable>.VdmAttachStr.VdmAttachMode,
	beq	.L2741	@,
	movw	r2, #:lower16:.LC416	@ tmp200,
	movt	r2, #:upper16:.LC416	@ tmp200,
	sub	r1, fp, #68	@,,
	str	r1, [fp, #-112]	@, %sfp
	ldmia	r2, {r0, r1}	@ tmp200,,
	mov	r4, r1, lsr #16	@ tmp203,,
	strb	r4, [fp, #-62]	@ tmp203, szAttach
	str	r0, [fp, #-68]	@, szAttach
	strh	r1, [fp, #-64]	@ movhi	@, szAttach
.L2713:
	sub	r2, fp, #52	@,,
	sub	r1, fp, #48	@,,
	sub	r3, fp, #56	@,,
	mov	r0, r6	@, i
	bl	VCTRL_GetChanImgNum	@
	mov	r0, r6	@, i
	bl	VCTRL_GetChanVoQue	@
	sub	r7, fp, #88	@ tmp209,,
	sub	r4, fp, #108	@ tmp211,,
	cmp	r0, #0	@ pstDecQue
	streq	r0, [fp, #-120]	@ pstDecQue, %sfp
	streq	r0, [fp, #-124]	@ pstDecQue, %sfp
	ldrneh	r1, [r0, #8]	@, <variable>.tail
	streq	r0, [fp, #-128]	@ pstDecQue, %sfp
	strne	r1, [fp, #-120]	@, %sfp
	mov	r1, r7	@, tmp209
	ldrneh	r2, [r0, #4]	@, <variable>.history
	strne	r2, [fp, #-128]	@, %sfp
	ldrneh	r0, [r0, #6]	@, <variable>.head
	strne	r0, [fp, #-124]	@, %sfp
	ldr	r0, [sl, #544]	@, <variable>.eVidStd
	bl	VID_STD_Enum2Str	@
	ldr	r0, [sl, #340]	@, <variable>.eLastFrameState
	mov	r1, r4	@, tmp211
	bl	VID_EofState_Enum2Str	@
	ldr	ip, [fp, #-112]	@, %sfp
	ldr	r3, [fp, #-116]	@, %sfp
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC417	@,
	movw	r2, #:lower16:.LC418	@,
	movt	r1, #:upper16:.LC417	@,
	movt	r2, #:upper16:.LC418	@,
	str	ip, [sp, #0]	@,
	bl	seq_printf	@
	ldr	r3, [sl, #12]	@, <variable>.s32IsOpen
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC419	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC419	@,
	bl	seq_printf	@
	ldr	r3, [sl, #16]	@, <variable>.s32IsRun
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC420	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC420	@,
	bl	seq_printf	@
	ldr	r3, [sl, #24]	@, <variable>.s32Priority
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC421	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC421	@,
	bl	seq_printf	@
	mov	r3, r7	@, tmp209
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC397	@,
	movw	r2, #:lower16:.LC422	@,
	movt	r1, #:upper16:.LC397	@,
	movt	r2, #:upper16:.LC422	@,
	bl	seq_printf	@
	ldr	r3, [sl, #40]	@, <variable>.eChanCapLevel
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC423	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC423	@,
	bl	seq_printf	@
	mov	r3, r4	@, tmp211
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC397	@,
	movw	r2, #:lower16:.LC424	@,
	movt	r1, #:upper16:.LC397	@,
	movt	r2, #:upper16:.LC424	@,
	bl	seq_printf	@
	ldr	r3, [sl, #124]	@, <variable>.stChanCfg.s32IsOmxPath
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC425	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC425	@,
	bl	seq_printf	@
	ldr	r3, [sl, #72]	@, <variable>.stChanCfg.s32DecMode
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC426	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC426	@,
	bl	seq_printf	@
	ldr	r3, [sl, #76]	@, <variable>.stChanCfg.s32DecOrderOutput
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC427	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC427	@,
	bl	seq_printf	@
	ldr	r3, [sl, #64]	@, <variable>.stChanCfg.s32ChanErrThr
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC428	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC428	@,
	bl	seq_printf	@
	ldr	r3, [sl, #68]	@, <variable>.stChanCfg.s32ChanStrmOFThr
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC429	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC429	@,
	bl	seq_printf	@
	ldr	r3, [sl, #544]	@ temp.6670, <variable>.eVidStd
	cmp	r3, #1	@ temp.6670,
	beq	.L2742	@,
	sub	r0, r3, #10	@ tmp258, temp.6670,
	cmp	r0, #2	@ tmp258,
	bls	.L2743	@,
	cmp	r3, #2	@ temp.6670,
	beq	.L2744	@,
	cmp	r3, #18	@ temp.6670,
	beq	.L2745	@,
.L2718:
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	ldr	r3, [sl, #224]	@, <variable>.stChanMem_vdh.PhyAddr
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC437	@,
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC437	@,
	bl	seq_printf	@
	ldr	r3, [sl, #228]	@, <variable>.stChanMem_vdh.Length
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC438	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC438	@,
	bl	seq_printf	@
	ldr	r3, [sl, #240]	@, <variable>.stChanMem_scd.PhyAddr
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC439	@,
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC439	@,
	bl	seq_printf	@
	ldr	r3, [sl, #244]	@, <variable>.stChanMem_scd.Length
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC440	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC440	@,
	bl	seq_printf	@
	ldr	r3, [sl, #256]	@, <variable>.stChanMem_ctx.PhyAddr
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC441	@,
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC441	@,
	bl	seq_printf	@
	ldr	r3, [sl, #260]	@, <variable>.stChanMem_ctx.Length
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC442	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC442	@,
	bl	seq_printf	@
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	ldr	r7, [fp, #-52]	@ ReadNum, ReadNum
	ldr	ip, [fp, #-56]	@ NewNum, NewNum
	mov	r0, r5	@, p
	ldr	r3, [fp, #-48]	@, RefNum
	movw	r1, #:lower16:.LC443	@,
	movw	r2, #:lower16:.LC444	@,
	movt	r1, #:upper16:.LC443	@,
	movt	r2, #:upper16:.LC444	@,
	stmia	sp, {r7, ip}	@ phole stm
	bl	seq_printf	@
	ldr	ip, [fp, #-120]	@, %sfp
	mov	r0, r5	@, p
	ldr	r7, [fp, #-124]	@, %sfp
	movw	r1, #:lower16:.LC445	@,
	ldr	r3, [fp, #-128]	@, %sfp
	movt	r1, #:upper16:.LC445	@,
	movw	r2, #:lower16:.LC446	@,
	movt	r2, #:upper16:.LC446	@,
	stmia	sp, {r7, ip}	@ phole stm
	bl	seq_printf	@
	ldr	r3, [sl, #560]	@, <variable>.stSynExtraData.s32DecMode
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC447	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC447	@,
	bl	seq_printf	@
	ldr	r3, [sl, #564]	@, <variable>.stSynExtraData.s32DecOrderOutput
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC448	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC448	@,
	bl	seq_printf	@
	ldr	r3, [sl, #324]	@, <variable>.stRecentImgformat
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC449	@,
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC449	@,
	bl	seq_printf	@
	ldr	r3, [sl, #328]	@, <variable>.stRecentImgPackingType
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC450	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC450	@,
	bl	seq_printf	@
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC451	@,
	movt	r1, #:upper16:.LC451	@,
	bl	seq_printf	@
	ldr	r3, [r8, #68]	@, <variable>.stInstCfg.s32DecFsWidth
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC452	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC452	@,
	bl	seq_printf	@
	ldr	r3, [r8, #72]	@, <variable>.stInstCfg.s32DecFsHeight
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC453	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC453	@,
	bl	seq_printf	@
	ldr	r3, [r8, #84]	@, <variable>.stInstCfg.s32DispFsWidth
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC454	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC454	@,
	bl	seq_printf	@
	ldr	r3, [r8, #88]	@, <variable>.stInstCfg.s32DispFsHeight
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC455	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC455	@,
	bl	seq_printf	@
	ldrsb	r3, [r8, #61]	@, <variable>.stInstCfg.s32ExpectedDecFsNum
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC456	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC456	@,
	bl	seq_printf	@
	ldrsb	r3, [r8, #9]	@, <variable>.s8TotalValidFsNum
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC457	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC457	@,
	bl	seq_printf	@
	ldrsb	r3, [r8, #13]	@, <variable>.s32PmvNum
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC458	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC458	@,
	bl	seq_printf	@
	ldrb	r3, [r8, #56]	@ zero_extendqisi2	@ D.54939, <variable>.stInstCfg.s32DispLoopEnable
	cmp	r3, #0	@ D.54939,
	bne	.L2746	@,
.L2721:
	ldrsb	r3, [r8, #10]	@, <variable>.s32DecFsNum
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC464	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC464	@,
	bl	seq_printf	@
	ldrsb	r3, [r8, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	cmp	r3, #0	@ <variable>.s32DecFsNum,
	addgt	r4, r8, #34816	@ ivtmp.6660, pFsp,
	movgt	r6, #0	@ j.6676,
	addgt	r4, r4, #156	@ ivtmp.6660, ivtmp.6660,
	ble	.L2726	@,
.L2727:
	ldrsb	r2, [r4, #0]	@, <variable>.IsDecRef
	mov	r0, r5	@, p
	ldrsb	r3, [r4, #2]	@, <variable>.DispState
	movw	r1, #:lower16:.LC463	@,
	movt	r1, #:upper16:.LC463	@,
	add	r6, r6, #1	@ j.6676, j.6676,
	bl	seq_printf	@
	ldrsb	r2, [r8, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	add	r4, r4, #60	@ ivtmp.6660, ivtmp.6660,
	cmp	r2, r6	@ <variable>.s32DecFsNum, j.6676
	ble	.L2726	@,
	tst	r6, #15	@ j.6676,
	bne	.L2727	@,
	movw	r1, #:lower16:.LC71	@,
	mov	r0, r5	@, p
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	b	.L2727	@
.L2750:
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	ldr	r4, [sl, #1416]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r4, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	beq	.L2747	@,
.L2734:
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	movw	r6, #:lower16:-858993459	@ tmp433,
	bl	seq_printf	@
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC475	@,
	movt	r1, #:upper16:.LC475	@,
	bl	seq_printf	@
	ldr	r1, [r9, #1468]	@ <variable>.u32FrFrameRate, <variable>.u32FrFrameRate
	movt	r6, #:upper16:-858993459	@ tmp433,
	movw	r2, #:lower16:.LANCHOR0	@ tmp429,
	movt	r2, #:upper16:.LANCHOR0	@ tmp429,
	umull	r0, r3, r6, r1	@, tmp432, tmp433, <variable>.u32FrFrameRate
	ldr	r6, [r9, #1388]	@ D.54987, <variable>.u32VaVdmLoad
	movs	r7, r3, lsr #3	@ VdhFps, tmp432,
	beq	.L2735	@,
	ldr	r4, [r8, #68]	@ temp.6679, <variable>.stInstCfg.s32DecFsWidth
	add	sl, r4, #15	@ tmp434, temp.6679,
	cmp	sl, #30	@ tmp434,
	bls	.L2735	@,
	ldr	r8, [r8, #72]	@ temp.6680, <variable>.stInstCfg.s32DecFsHeight
	add	r3, r8, #15	@ tmp435, temp.6680,
	cmp	r3, #30	@ tmp435,
	bhi	.L2748	@,
.L2735:
	mov	r8, #0	@ VdhCycle,
.L2736:
	movw	r4, #:lower16:-858993459	@ tmp463,
	movt	r4, #:upper16:-858993459	@ tmp463,
	mov	r3, #0	@,
	mov	r0, r5	@, p
	umull	r1, lr, r4, r6	@, tmp462, tmp463, D.54987
	movw	r2, #:lower16:.LC477	@,
	movw	r1, #:lower16:.LC476	@,
	movt	r2, #:upper16:.LC477	@,
	movt	r1, #:upper16:.LC476	@,
	mov	ip, lr, lsr #3	@ tmp461, tmp462,
	str	ip, [sp, #0]	@ tmp461,
	add	lr, ip, ip, asl #2	@, tmp469, tmp461, tmp461,
	sub	ip, r6, lr, asl #1	@ tmp471, D.54987, tmp469,
	str	ip, [sp, #4]	@ tmp471,
	bl	seq_printf	@
	ldr	ip, [r9, #1468]	@ <variable>.u32FrFrameRate, <variable>.u32FrFrameRate
	mov	r3, r7	@, VdhFps
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC478	@,
	movt	r1, #:upper16:.LC478	@,
	umull	r2, lr, r4, ip	@, tmp477, tmp463, <variable>.u32FrFrameRate
	movw	r2, #:lower16:.LC479	@,
	movt	r2, #:upper16:.LC479	@,
	mov	r4, #0	@ tmp484,
	str	r4, [sp, #4]	@ tmp484,
	mov	lr, lr, lsr #3	@ tmp475, tmp477,
	add	lr, lr, lr, asl #2	@, tmp481, tmp475, tmp475,
	sub	ip, ip, lr, asl #1	@ tmp483, <variable>.u32FrFrameRate, tmp481,
	str	ip, [sp, #0]	@ tmp483,
	bl	seq_printf	@
	mov	r0, r5	@, p
	mov	r3, r8	@, VdhCycle
	movw	r1, #:lower16:.LC480	@,
	movw	r2, #:lower16:.LC481	@,
	movt	r1, #:upper16:.LC480	@,
	movt	r2, #:upper16:.LC481	@,
	bl	seq_printf	@
	movw	r1, #:lower16:.LC71	@,
	mov	r0, r5	@, p
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
.L2711:
	mov	r0, #0	@,
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L2741:
	movw	r7, #:lower16:.LC415	@ tmp194,
	movt	r7, #:upper16:.LC415	@ tmp194,
	sub	r0, fp, #68	@,,
	str	r0, [fp, #-112]	@, %sfp
	ldmia	r7, {r0, r1, r2}	@ tmp194,,,
	ldr	lr, [fp, #-112]	@, %sfp
	mov	r3, r2, lsr #16	@ tmp197,,
	strb	r3, [fp, #-58]	@ tmp197, szAttach
	stmia	lr!, {r0, r1}	@,,
	strh	r2, [lr, #0]	@ movhi	@, szAttach
	b	.L2713	@
.L2726:
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	mov	r4, r8	@ ivtmp.6656, pFsp
	bl	seq_printf	@
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC465	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC465	@,
	mov	r3, #64	@,
	mov	r7, #1	@ ivtmp.6653,
	bl	seq_printf	@
	mov	r6, #0	@ ivtmp.6652,
	b	.L2730	@
.L2751:
	tst	r6, #15	@ ivtmp.6652,
	beq	.L2749	@,
.L2732:
	ldrsb	r2, [r4, #96]	@, <variable>.s32IsRef
	mov	r0, r5	@, p
	ldrsb	r3, [r4, #97]	@, <variable>.s32DispState
	movw	r1, #:lower16:.LC463	@,
	movt	r1, #:upper16:.LC463	@,
	bl	seq_printf	@
	cmp	r7, #63	@ ivtmp.6653,
	bgt	.L2750	@,
.L2733:
	add	r6, r6, #1	@ ivtmp.6652, ivtmp.6652,
	add	r7, r7, #1	@ ivtmp.6653, ivtmp.6653,
	add	r4, r4, #544	@ ivtmp.6656, ivtmp.6656,
.L2730:
	cmp	r6, #0	@ ivtmp.6652,
	movw	r1, #:lower16:.LC463	@,
	mov	r0, r5	@, p
	movt	r1, #:upper16:.LC463	@,
	bne	.L2751	@,
	ldrsb	r2, [r4, #96]	@, <variable>.s32IsRef
	ldrsb	r3, [r4, #97]	@, <variable>.s32DispState
	bl	seq_printf	@
	b	.L2733	@
.L2749:
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	b	.L2732	@
.L2746:
	sxtb	r3, r3	@, D.54939
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC459	@,
	movw	r2, #:lower16:.LC460	@,
	movt	r1, #:upper16:.LC459	@,
	movt	r2, #:upper16:.LC460	@,
	bl	seq_printf	@
	ldrsb	r3, [r8, #63]	@, <variable>.stInstCfg.s32ExpectedDispFsNum
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC461	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC461	@,
	bl	seq_printf	@
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC459	@,
	movw	r2, #:lower16:.LC462	@,
	movt	r1, #:upper16:.LC459	@,
	movt	r2, #:upper16:.LC462	@,
	ldrsb	r3, [r8, #11]	@, <variable>.s32DispFsNum
	bl	seq_printf	@
	ldrsb	r1, [r8, #11]	@ <variable>.s32DispFsNum, <variable>.s32DispFsNum
	cmp	r1, #0	@ <variable>.s32DispFsNum,
	addgt	r4, r8, #38656	@ ivtmp.6666, pFsp,
	movgt	r6, #0	@ j,
	addgt	r4, r4, #156	@ ivtmp.6666, ivtmp.6666,
	ble	.L2722	@,
.L2723:
	ldrsb	r2, [r4, #0]	@, <variable>.IsDecRef
	mov	r0, r5	@, p
	ldrsb	r3, [r4, #2]	@, <variable>.DispState
	movw	r1, #:lower16:.LC463	@,
	movt	r1, #:upper16:.LC463	@,
	add	r6, r6, #1	@ j, j,
	bl	seq_printf	@
	ldrsb	r0, [r8, #11]	@ <variable>.s32DispFsNum, <variable>.s32DispFsNum
	add	r4, r4, #60	@ ivtmp.6666, ivtmp.6666,
	cmp	r0, r6	@ <variable>.s32DispFsNum, j
	ble	.L2722	@,
	tst	r6, #15	@ j,
	bne	.L2723	@,
	movw	r1, #:lower16:.LC71	@,
	mov	r0, r5	@, p
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	b	.L2723	@
.L2722:
	movw	r1, #:lower16:.LC71	@,
	mov	r0, r5	@, p
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	b	.L2721	@
.L2743:
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC432	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC432	@,
	ldr	r3, [sl, #52]	@, <variable>.stChanCfg.StdExt.Vp6Ext.bReversed
	bl	seq_printf	@
	b	.L2718	@
.L2748:
	ldr	ip, [r2, #1432]	@ <variable>.u32VaVdmKiloCycle, <variable>.u32VaVdmKiloCycle
	mov	lr, #1000	@ tmp439,
	mov	r1, r7	@, VdhFps
	str	r3, [fp, #-132]	@,
	mul	r0, lr, ip	@, tmp439, <variable>.u32VaVdmKiloCycle
	bl	__aeabi_uidiv	@
	cmp	r4, #0	@ temp.6679,
	movlt	r4, sl	@ temp.6679, tmp434
	mov	r1, r4, asr #4	@, temp.6679,
	bl	__aeabi_uidiv	@
	ldr	r2, [fp, #-132]	@,
	cmp	r8, #0	@ temp.6680,
	movlt	r8, r2	@ temp.6680, tmp435
	mov	r1, r8, asr #4	@, temp.6680,
	bl	__aeabi_uidiv	@
	mov	r8, r0	@ VdhCycle,
	b	.L2736	@
.L2747:
	movw	r4, #:lower16:249256	@ tmp399,
	movt	r4, #:upper16:249256	@ tmp399,
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC466	@,
	movw	r7, #:lower16:.LANCHOR4	@ tmp403,
	movt	r1, #:upper16:.LC466	@,
	movt	r7, #:upper16:.LANCHOR4	@ tmp403,
	bl	seq_printf	@
	ldr	r3, [sl, r4]	@, <variable>.s32CurFsSize
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC467	@,
	movw	r2, #:lower16:.LC468	@,
	movt	r1, #:upper16:.LC467	@,
	movt	r2, #:upper16:.LC468	@,
	bl	seq_printf	@
	ldr	r3, [r7, #-3512]	@, g_u32DFSMaxAllocTime
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC467	@,
	movw	r2, #:lower16:.LC469	@,
	movt	r1, #:upper16:.LC467	@,
	movt	r2, #:upper16:.LC469	@,
	movw	r7, #:lower16:249264	@ tmp423,
	bl	seq_printf	@
	movw	ip, #:lower16:249260	@ tmp407,
	movt	ip, #:upper16:249260	@ tmp407,
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC467	@,
	movw	r2, #:lower16:.LC470	@,
	ldr	r3, [sl, ip]	@, <variable>.s32RefNum
	movt	r1, #:upper16:.LC467	@,
	movt	r2, #:upper16:.LC470	@,
	movt	r7, #:upper16:249264	@ tmp423,
	bl	seq_printf	@
	movw	r2, #:lower16:251528	@ tmp413,
	movt	r2, #:upper16:251528	@ tmp413,
	movw	r3, #:lower16:249268	@ tmp411,
	movt	r3, #:upper16:249268	@ tmp411,
	mov	r0, r5	@, p
	ldr	r6, [sl, r2]	@ <variable>.stDynamicFSTimestamp.u32PreAllocTime, <variable>.stDynamicFSTimestamp.u32PreAllocTime
	movw	r1, #:lower16:.LC471	@,
	ldr	r3, [sl, r3]	@ <variable>.s32PreAllocFrmNum, <variable>.s32PreAllocFrmNum
	movt	r1, #:upper16:.LC471	@,
	movw	r2, #:lower16:.LC472	@,
	movt	r2, #:upper16:.LC472	@,
	str	r6, [sp, #0]	@ <variable>.stDynamicFSTimestamp.u32PreAllocTime,
	bl	seq_printf	@
	movw	r1, #:lower16:251532	@ tmp419,
	movt	r1, #:upper16:251532	@ tmp419,
	movw	r0, #:lower16:249272	@ tmp417,
	movt	r0, #:upper16:249272	@ tmp417,
	ldr	r4, [sl, r1]	@ <variable>.stDynamicFSTimestamp.u32MMZAllocTime, <variable>.stDynamicFSTimestamp.u32MMZAllocTime
	movw	r2, #:lower16:.LC473	@,
	ldr	r3, [sl, r0]	@ <variable>.s32MMZFrmNum, <variable>.s32MMZFrmNum
	movt	r2, #:upper16:.LC473	@,
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC471	@,
	movt	r1, #:upper16:.LC471	@,
	str	r4, [sp, #0]	@ <variable>.stDynamicFSTimestamp.u32MMZAllocTime,
	bl	seq_printf	@
	movw	ip, #:lower16:251536	@ tmp425,
	movt	ip, #:upper16:251536	@ tmp425,
	ldr	r3, [sl, r7]	@ <variable>.s32NeededFrameNum, <variable>.s32NeededFrameNum
	movw	r1, #:lower16:.LC471	@,
	movw	r2, #:lower16:.LC474	@,
	ldr	r6, [sl, ip]	@ <variable>.stDynamicFSTimestamp.u32AllTime, <variable>.stDynamicFSTimestamp.u32AllTime
	movt	r1, #:upper16:.LC471	@,
	movt	r2, #:upper16:.LC474	@,
	mov	r0, r5	@, p
	str	r6, [sp, #0]	@ <variable>.stDynamicFSTimestamp.u32AllTime,
	bl	seq_printf	@
	b	.L2734	@
.L2742:
	movw	lr, #:lower16:USE_FF_APT_EN	@ tmp250,
	movt	lr, #:upper16:USE_FF_APT_EN	@ tmp250,
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	ldr	r3, [lr, #0]	@, USE_FF_APT_EN
	movt	r1, #:upper16:.LC66	@,
	movw	r2, #:lower16:.LC147	@,
	movt	r2, #:upper16:.LC147	@,
	bl	seq_printf	@
	ldr	r3, [sl, #52]	@, <variable>.stChanCfg.StdExt.Vc1Ext.IsAdvProfile
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC430	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC430	@,
	bl	seq_printf	@
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC431	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC431	@,
	ldr	r3, [sl, #56]	@, <variable>.stChanCfg.StdExt.Vc1Ext.CodecVersion
	bl	seq_printf	@
	b	.L2718	@
.L2740:
	movw	lr, #:lower16:.LC414	@ tmp180,
	movt	lr, #:upper16:.LC414	@ tmp180,
	sub	r3, fp, #68	@,,
	str	r3, [fp, #-112]	@, %sfp
	ldr	r4, [lr, #0]	@ tmp183,
	mov	ip, r4, lsr #16	@ tmp184, tmp183,
	strh	r4, [fp, #-68]	@ movhi	@ tmp183, szAttach
	strb	ip, [fp, #-66]	@ tmp184, szAttach
	b	.L2713	@
.L2744:
	mov	r4, #300	@ tmp267,
	mov	r0, r5	@, p
	mla	r4, r4, r6, r9	@ tmp268, tmp267, i, tmp493
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC433	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC433	@,
	ldr	r3, [r4, #1472]	@, <variable>.u32SkipFind
	bl	seq_printf	@
	ldr	r3, [r4, #1476]	@, <variable>.u32SkipDiscard
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC434	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC434	@,
	bl	seq_printf	@
	movw	r2, #:lower16:267448	@ tmp282,
	movt	r2, #:upper16:267448	@ tmp282,
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movt	r1, #:upper16:.LC66	@,
	ldrb	r3, [sl, r2]	@ zero_extendqisi2	@ tmp284,
	movw	r2, #:lower16:.LC435	@,
	movt	r2, #:upper16:.LC435	@,
	and	r3, r3, #1	@, tmp284,
	bl	seq_printf	@
	b	.L2718	@
.L2745:
	ldr	lr, [sl, #512]	@ <variable>.stRecentUsrdecFrame.s32YHeight, <variable>.stRecentUsrdecFrame.s32YHeight
	mov	ip, #496	@ tmp293,
	ldr	r2, [sl, #488]	@ <variable>.stRecentUsrdecFrame.enFmt, <variable>.stRecentUsrdecFrame.enFmt
	movw	r1, #:lower16:.LC436	@,
	ldr	r3, [sl, #508]	@ <variable>.stRecentUsrdecFrame.s32YWidth, <variable>.stRecentUsrdecFrame.s32YWidth
	movt	r1, #:upper16:.LC436	@,
	str	lr, [sp, #0]	@ <variable>.stRecentUsrdecFrame.s32YHeight,
	mov	r0, r5	@, p
	ldr	r7, [sl, #520]	@ <variable>.stRecentUsrdecFrame.s32LumaStride, <variable>.stRecentUsrdecFrame.s32LumaStride
	str	r7, [sp, #4]	@ <variable>.stRecentUsrdecFrame.s32LumaStride,
	ldr	r6, [sl, #532]	@ <variable>.stRecentUsrdecFrame.s32ChromStride, <variable>.stRecentUsrdecFrame.s32ChromStride
	str	r6, [sp, #8]	@ <variable>.stRecentUsrdecFrame.s32ChromStride,
	ldrd	r6, [sl, ip]	@ <variable>.stRecentUsrdecFrame.Pts, pChan, tmp293
	strd	r6, [sp, #16]	@ <variable>.stRecentUsrdecFrame.Pts,,
	bl	seq_printf	@
	b	.L2718	@
	.fnend
	.size	vfmw_read_proc_dec, .-vfmw_read_proc_dec
	.global	g_DSPState
	.global	g_SCDID
	.global	g_SdecFunc
	.global	s_pstVfmwChan
	.global	extra_ref
	.global	extra_disp
	.global	extra_cmd
	.global	g_allow_B_before_P
	.global	g_not_direct_8x8_inference_flag
	.global	g_not_allow_H264FullPictureRepair_flag
	.global	g_apple_airplay_mirrorinig_flag
	.global	vfmw_save_str_file
	.global	save_str_chan_num
	.global	vfmw_save_seg_file
	.global	save_seg_chan_num
	.global	vfmw_save_yuv_file
	.global	save_yuv_chan_num
	.global	save_yuv_with_crop
	.global	g_ResetCreateNewSave
	.global	g_CurProcChan
	.global	g_VdmCharacter
	.global	g_u32DFSMaxAllocTime
	.global	g_SleepTime
	.global	g_DnrSleepTime
	.global	g_StopDec
	.global	g_VdecIrqHandle
	.global	g_DnrIrqHandle
	.global	g_event_report
	.global	g_VfmwChanStat
	.global	g_VfmwGlobalStat
	.global	g_eVdmVersion
	.global	AcceleratorCharacter
	.global	g_TaskLock
	.global	g_IntEvent
	.global	g_ActivateLock
	.global	pOption
	.global	pY
	.global	pUl
	.global	pVl
	.global	MemRecord_YUV
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	CSWTCH.924, %object
	.size	CSWTCH.924, 8
CSWTCH.924:
	.word	2
	.word	3
	.type	CSWTCH.927, %object
	.size	CSWTCH.927, 32
CSWTCH.927:
	.word	3
	.word	3
	.word	3
	.word	3
	.word	3
	.word	1
	.word	1
	.word	1
	.type	__func__.50114, %object
	.size	__func__.50114, 18
__func__.50114:
	.ascii	"VCTRL_SetCallBack\000"
	.space	2
	.type	__func__.50080, %object
	.size	__func__.50080, 18
__func__.50080:
	.ascii	"VCTRL_EventReport\000"
	.space	2
	.type	vfmw_proc_fops, %object
	.size	vfmw_proc_fops, 108
vfmw_proc_fops:
@ owner:
	.word	0
@ llseek:
	.word	seq_lseek
@ read:
	.word	seq_read
@ write:
	.word	vfmw_proc_write
@ open:
	.space	28
	.word	vfmw_proc_open
@ release:
	.space	4
	.word	single_release
	.space	52
	.type	__func__.54608, %object
	.size	__func__.54608, 20
__func__.54608:
	.ascii	"vfmw_read_proc_info\000"
	.type	__func__.55732, %object
	.size	__func__.55732, 21
__func__.55732:
	.ascii	"VCTRL_RequestChanMem\000"
	.space	3
	.type	__func__.53505, %object
	.size	__func__.53505, 14
__func__.53505:
	.ascii	"DecChanSyntax\000"
	.space	2
	.type	__func__.52326, %object
	.size	__func__.52326, 19
__func__.52326:
	.ascii	"VCTRL_FlushDecoder\000"
	.space	1
	.type	__func__.52046, %object
	.size	__func__.52046, 23
__func__.52046:
	.ascii	"VCTRL_ReleaseChanImage\000"
	.space	1
	.type	__func__.51915, %object
	.size	__func__.51915, 19
__func__.51915:
	.ascii	"VCTRL_GetChanImage\000"
	.space	1
	.type	__func__.50426, %object
	.size	__func__.50426, 29
__func__.50426:
	.ascii	"VCTRL_PartitionMemForStdUser\000"
	.space	3
	.type	__func__.53917, %object
	.size	__func__.53917, 18
__func__.53917:
	.ascii	"GetExtraRefFrmNum\000"
	.space	2
	.type	__func__.53953, %object
	.size	__func__.53953, 19
__func__.53953:
	.ascii	"GetExtraDispFrmNum\000"
	.space	1
	.type	__func__.53989, %object
	.size	__func__.53989, 16
__func__.53989:
	.ascii	"GetExtraCtrlCmd\000"
	.type	__func__.53824, %object
	.size	__func__.53824, 24
__func__.53824:
	.ascii	"VCTRL_ExtAccGetDecParam\000"
	.type	__func__.55108, %object
	.size	__func__.55108, 16
__func__.55108:
	.ascii	"vfmw_write_proc\000"
	.type	__func__.51406, %object
	.size	__func__.51406, 17
__func__.51406:
	.ascii	"VCTRL_ConfigChan\000"
	.space	3
	.type	CSWTCH.930, %object
	.size	CSWTCH.930, 32
CSWTCH.930:
	.word	3
	.word	3
	.word	3
	.word	3
	.word	3
	.word	1
	.word	1
	.word	1
	.type	__func__.54747, %object
	.size	__func__.54747, 19
__func__.54747:
	.ascii	"vfmw_read_proc_scd\000"
	.space	1
	.type	__param_str_extra_cmd, %object
	.size	__param_str_extra_cmd, 18
__param_str_extra_cmd:
	.ascii	"hi_vfmw.extra_cmd\000"
	.space	2
	.type	__param_str_extra_disp, %object
	.size	__param_str_extra_disp, 19
__param_str_extra_disp:
	.ascii	"hi_vfmw.extra_disp\000"
	.space	1
	.type	__param_str_extra_ref, %object
	.size	__param_str_extra_ref, 18
__param_str_extra_ref:
	.ascii	"hi_vfmw.extra_ref\000"
	.section	___ksymtab+VCTRL_SetDbgOption,"a",%progbits
	.align	2
	.type	__ksymtab_VCTRL_SetDbgOption, %object
	.size	__ksymtab_VCTRL_SetDbgOption, 8
__ksymtab_VCTRL_SetDbgOption:
@ value:
	.word	VCTRL_SetDbgOption
@ name:
	.word	__kstrtab_VCTRL_SetDbgOption
	.section	__ksymtab_strings,"a",%progbits
	.type	__kstrtab_VCTRL_SetDbgOption, %object
	.size	__kstrtab_VCTRL_SetDbgOption, 19
__kstrtab_VCTRL_SetDbgOption:
	.ascii	"VCTRL_SetDbgOption\000"
	.data
	.align	2
.LANCHOR2 = . + 0
	.type	s_VfmwSavePath, %object
	.size	s_VfmwSavePath, 64
s_VfmwSavePath:
	.byte	47
	.byte	109
	.byte	110
	.byte	116
	.byte	0
	.space	59
	.type	g_not_direct_8x8_inference_flag, %object
	.size	g_not_direct_8x8_inference_flag, 1
g_not_direct_8x8_inference_flag:
	.byte	1
	.space	3
	.type	save_yuv_chan_num, %object
	.size	save_yuv_chan_num, 4
save_yuv_chan_num:
	.word	-1
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000"
	.space	1
.LC1:
	.ascii	"L:%d ChanID out of range\012\000"
	.space	2
.LC2:
	.ascii	"L:%d This Chan has not been created!!!\012\000"
.LC3:
	.ascii	"L:%d WARNING: vidio std not setted!\012\000"
	.space	3
.LC4:
	.ascii	"line %d can not know YuvFormat = %d\012\000"
	.space	3
.LC5:
	.ascii	"vfmw_ctrl.c,L%d: %s\012\000"
	.space	3
.LC6:
	.ascii	"ChanID out of range\000"
.LC7:
	.ascii	"Report Last Frame, Value=%d, LastFrameState=%d\012\000"
.LC8:
	.ascii	"SetVdecExtra ERROR: extra_ref = %d is out of [ -500"
	.ascii	"0, 5000 ]!\012\000"
	.space	1
.LC9:
	.ascii	"SetVdecExtra ERROR: extra_disp = %d is out of [ -50"
	.ascii	"00, 5000 ]!\012\000"
.LC10:
	.ascii	"Chan inactive\000"
	.space	2
.LC11:
	.ascii	"(safe,warn,danger) :amount = %d,%d,%d,%d\012\000"
	.space	2
.LC12:
	.ascii	"strm_ctrl: I->IPB\012\000"
	.space	1
.LC13:
	.ascii	"strm_ctrl: IPB->I\012\000"
	.space	1
.LC14:
	.ascii	"(CurrMode,NextMode) = %d,%d\012\000"
	.space	3
.LC15:
	.ascii	"ERROR: (nPmv(%d) + extra_ref(%d)) <= 0\012\000"
.LC16:
	.ascii	"ERROR: TempMinFrame(%d + %d + %d), TempMiddleFrame("
	.ascii	"%d + %d + %d), TempFluentFrame(%d + %d + %d)\012\000"
	.space	3
.LC17:
	.ascii	"VCTRL_GetChanMemSize L%d: arrange return failure\012"
	.ascii	"\000"
	.space	2
.LC18:
	.ascii	"ERROR: s32MaxRefFrameNum(%d), extra_ref(%d), s32Dis"
	.ascii	"playFrameNum(%d), extra_disp(%d)\012\000"
	.space	3
.LC19:
	.ascii	"ERROR: (MaxRefFrameNum(%d) + extra_ref(%d)) > 16\012"
	.ascii	"\000"
	.space	2
.LC20:
	.ascii	"VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_BY_OPTION is desig"
	.ascii	"ned for CAP_LEVEL_USER_DEFINE_WITH_OPTION, please c"
	.ascii	"hange channel's capability or use VDEC_CID_GET_CHAN"
	.ascii	"_MEMSIZE.\012\000"
.LC21:
	.ascii	"VDEC_CID_CREATE_CHAN_WITH_OPTION the purpose of cre"
	.ascii	"ating the channel is not clear.\012\000"
.LC22:
	.ascii	"s32SlotWidth or s32SlotHeight is 0.\012\000"
	.space	3
.LC23:
	.ascii	"CAP_LEVEL_USER_DEFINE_WITH_OPTION option is illegal"
	.ascii	".\012\000"
	.space	2
.LC24:
	.ascii	"VCTRL_GetChanMemSizeByOption L%d: arrange return fa"
	.ascii	"ilure\012\000"
	.space	2
.LC25:
	.ascii	"chan not create\000"
.LC26:
	.ascii	"can NOT start a not-opened Chan\000"
.LC27:
	.ascii	"NULL == pArgs\000"
	.space	2
.LC28:
	.ascii	"ChanId out of range\000"
.LC29:
	.ascii	"vfmw_ctrl.c, line %d: ChanID out of range\012\000"
	.space	1
.LC30:
	.ascii	"vfmw_ctrl.c, line %d: Chan %d is not open or not ru"
	.ascii	"nning\012\000"
	.space	2
.LC31:
	.ascii	"Chip(id: %d) not support beyond 2032x2032 when Std "
	.ascii	"!= USER.\012\000"
	.space	3
.LC32:
	.ascii	"Chip(id: %d) not support beyond %dx%d when Std != H"
	.ascii	"264/VP8/MVC/USER.\012\000"
	.space	2
.LC33:
	.ascii	"Unknow Chip ID: %d\012\000"
.LC34:
	.ascii	"create soft-decoder fail!\012\000"
	.space	1
.LC35:
	.ascii	"event_report null!\000"
	.space	1
.LC36:
	.ascii	"%s Unkown Adapter Type: %d\012\000"
.LC37:
	.ascii	"InstID out of range\000"
.LC38:
	.ascii	"s_VfmwCTrl.event_report_vdec = NULL\012\000"
	.space	3
.LC39:
	.ascii	"s_VfmwCTrl.event_report_omxvdec = NULL\012\000"
.LC40:
	.ascii	"%s Unkown Adapter Type: %d, Len: %d\012\000"
	.space	3
.LC41:
	.ascii	"can NOT config a not-opened Chan\000"
	.space	3
.LC42:
	.ascii	"register soft decoder fail: '%s' can not be NULL\012"
	.ascii	"\000"
	.space	2
.LC43:
	.ascii	"pfun_iMediaSoftDEC_Create\000"
	.space	2
.LC44:
	.ascii	"pfun_iMediaSoftDEC_Destroy\000"
	.space	1
.LC45:
	.ascii	"pfun_iMediaSoftDEC_Init\000"
.LC46:
	.ascii	"pfun_iMediaSoftDEC_Decode\000"
	.space	2
.LC47:
	.ascii	"pfun_iMediaSoftDEC_RecycleImage\000"
.LC48:
	.ascii	"pfun_iMediaSoftDEC_GetRemainImg\000"
.LC49:
	.ascii	"pfun_iMediaSoftDEC_GetImageBuffer\000"
	.space	2
.LC50:
	.ascii	"pstCfg is null\000"
	.space	1
.LC51:
	.ascii	"pArgs is null\000"
	.space	2
.LC52:
	.ascii	"pstStreamIntf is NULL\000"
	.space	2
.LC53:
	.ascii	"pstStreamParam is NULL\000"
	.space	1
.LC54:
	.ascii	"VFMW: WriteBigTileYuv %dx%d...\012\000"
.LC55:
	.ascii	"vfmw_ctrl.c, line %d: ChanID out of range is %d\012"
	.ascii	"\000"
	.space	3
.LC56:
	.ascii	"Chan %d is not open or not running\012\000"
.LC57:
	.ascii	"vfmw%02d\000"
	.space	3
.LC58:
	.ascii	"vfmw\000"
	.space	3
.LC59:
	.ascii	"vfmw_dbg\000"
	.space	3
.LC60:
	.ascii	"vfmw_prn\000"
	.space	3
.LC61:
	.ascii	"vfmw_scd\000"
	.space	3
.LC62:
	.ascii	"vfmw_dec\000"
	.space	3
.LC63:
	.ascii	"vfmw_lwd\000"
	.space	3
.LC64:
	.ascii	"vfmw_chn\000"
	.space	3
.LC65:
	.ascii	"=============== lowdly info ================\012\000"
	.space	2
.LC66:
	.ascii	"%-25s :%d\012\000"
	.space	1
.LC67:
	.ascii	"LowdlyEnable\000"
	.space	3
.LC68:
	.ascii	"ChanID\000"
	.space	1
.LC69:
	.ascii	"ScdCount\000"
	.space	3
.LC70:
	.ascii	"VdhCount\000"
	.space	3
.LC71:
	.ascii	"\012\000"
	.space	2
.LC72:
	.ascii	"=============== chn info =========================="
	.ascii	"====\012\000"
	.space	3
.LC73:
	.ascii	"=============== chn by vdh ========================"
	.ascii	"====\012\000"
	.space	3
.LC74:
	.ascii	"%d \000"
.LC75:
	.ascii	"=============== chanid by prior ==================="
	.ascii	"====\012\000"
	.space	3
.LC76:
	.ascii	"=============== chan prior ========================"
	.ascii	"====\012\000"
	.space	3
.LC77:
	.ascii	"=============== chan isopen isrun ================="
	.ascii	"====\012\000"
	.space	3
.LC78:
	.ascii	"%d %d %d\012\000"
	.space	2
.LC79:
	.ascii	"'print_enable_word' definition, from bit31 to bit0:"
	.ascii	"\012\000"
	.space	3
.LC80:
	.ascii	"---------------------------------------------------"
	.ascii	"------------\012\000"
	.space	3
.LC81:
	.ascii	"<not used>  DEC_MODE    PTS         DNR\012\000"
	.space	3
.LC82:
	.ascii	"FOD         SCD_INFO    SCD_STREAM  SCD_REGMSG\012\000"
.LC83:
	.ascii	"BLOCK       DBG         SE          SEI\012\000"
	.space	3
.LC84:
	.ascii	"SLICE       PIC         SEQ         MARK_MMCO\012\000"
	.space	1
.LC85:
	.ascii	"POC         DPB         REF         QUEUE\012\000"
	.space	1
.LC86:
	.ascii	"IMAGE       STR_BODY    STR_TAIL    STR_HEAD\012\000"
	.space	2
.LC87:
	.ascii	"STREAM      UPMSG       RPMSG       DNMSG\012\000"
	.space	1
.LC88:
	.ascii	"VDMREG      CTRL        ERROR       FATAL\012\000"
	.space	1
.LC89:
	.ascii	"'vfmw_state' definition, from bit31 to bit0:\012\000"
	.space	2
.LC90:
	.ascii	"<not used>       <not used>       <not used>    <no"
	.ascii	"t used>\012\000"
.LC91:
	.ascii	"<not used>       <not used>       <VO_REL_IMG>  <VO"
	.ascii	"_RCV_IMG>\012\000"
	.space	2
.LC92:
	.ascii	"<2D_TO_QUEUE>    <DNR_INTERRUPT>  <DNR_START>   <1D"
	.ascii	"_TO_QUEUE>\012\000"
	.space	1
.LC93:
	.ascii	"<VDH_REPAIR>     <VDH_INTERRUPT>  <VDH_START>   <GE"
	.ascii	"NERATE_DECPARAM>\012\000"
	.space	3
.LC94:
	.ascii	"<DECSYNTAX_SEG>  <SCD_INTERRUPT>  <SCD_START>   <RC"
	.ascii	"V_RAW>\012\000"
	.space	1
.LC95:
	.ascii	"'extra_cmd' definition, from bit31 to bit0:\012\000"
	.space	3
.LC96:
	.ascii	"<not used>       <not used>      <direct 8x8>   <B "
	.ascii	"before P>\012\000"
	.space	2
.LC97:
	.ascii	"------------------------debug options--------------"
	.ascii	"------------\012\000"
	.space	3
.LC98:
	.ascii	"%-27s :%#x\012\000"
.LC99:
	.ascii	"tracer address\000"
	.space	1
.LC100:
	.ascii	"%-27s :%s\012\000"
	.space	1
.LC101:
	.ascii	"path to save debug data\000"
.LC102:
	.ascii	"print enable word\000"
	.space	2
.LC103:
	.ascii	"vfmw_state enable word\000"
	.space	1
.LC104:
	.ascii	"%-27s :%d\012\000"
	.space	1
.LC105:
	.ascii	"bitstream control period\000"
	.space	3
.LC106:
	.ascii	"frame control period\000"
	.space	3
.LC107:
	.ascii	"rcv/rls img control period\000"
	.space	1
.LC108:
	.ascii	"you can perform vfmw debug with such commond:\012\000"
	.space	1
.LC109:
	.ascii	"echo [arg1] [arg2] > /proc/vfmw\012\012\000"
	.space	2
.LC110:
	.ascii	"debug action                    arg1       arg2\012"
	.ascii	"\000"
	.space	3
.LC111:
	.ascii	"------------------------------  --------  ---------"
	.ascii	"------------\012\000"
	.space	3
.LC112:
	.ascii	"set print enable                0x0       print_ena"
	.ascii	"ble_word\012\000"
	.space	3
.LC113:
	.ascii	"set err_thr                     0x2       (chan_id<"
	.ascii	"<24)|err_thr\012\000"
	.space	3
.LC114:
	.ascii	"set dec order output            0x4       (chan_id<"
	.ascii	"<24)|dec_order_output_enable\012\000"
	.space	3
.LC115:
	.ascii	"set dec_mode(0/1/2=IPB/IP/I)    0x5       (chan_id<"
	.ascii	"<24)|dec_mode\012\000"
	.space	2
.LC116:
	.ascii	"set discard_before_dec_thr      0x7       (chan_id<"
	.ascii	"<24)|stream_size_thr\012\000"
	.space	3
.LC117:
	.ascii	"set postprocess options         0xa       (dc<<8)|("
	.ascii	"db<<4)|dr, 0000=auto,0001=on,0010=off\012\000"
	.space	2
.LC118:
	.ascii	"set frame/adaptive storage      0xb       0:frame o"
	.ascii	"nly, 1:adaptive\012\000"
.LC119:
	.ascii	"pay attention to the channel    0xd       channel n"
	.ascii	"umber\012\000"
	.space	2
.LC120:
	.ascii	"channel vcmp config             0xe       chanId: a"
	.ascii	"rg2>>27,\012%42smirror_en: (arg2>>26)&1,\012%42svcm"
	.ascii	"p_en: (arg2>>25)&1,\012%42swm_en: (arg2>>24)&1,\012"
	.ascii	"%42swm_start: (arg2>>12)&0xfff,\012%42swm_end: (arg"
	.ascii	"2)&0xfff\012\000"
	.space	1
.LC121:
	.ascii	" \000"
	.space	2
.LC122:
	.ascii	"print tracer                    0x100     tracer ad"
	.ascii	"dress. do not care if vfmw still running\012\000"
	.space	3
.LC123:
	.ascii	"start/stop raw stream saving    0x200     chan_id\012"
	.ascii	"\000"
	.space	1
.LC124:
	.ascii	"start/stop stream seg saving    0x201     chan_id\012"
	.ascii	"\000"
	.space	1
.LC125:
	.ascii	"start/stop 2D yuv saving        0x202     (chan_id<"
	.ascii	"<24)|crop_enable\012\000"
	.space	3
.LC126:
	.ascii	"save a single 2D frame          0x203     frame phy"
	.ascii	" addr\012\000"
	.space	2
.LC127:
	.ascii	"save a single 1D frame          0x204     frame phy"
	.ascii	" addr width height=(height+PicStructure)\012\000"
	.space	3
.LC128:
	.ascii	"set dec_task_schedule_delay     0x400     schedual_"
	.ascii	"delay_time(ms)\012\000"
	.space	1
.LC129:
	.ascii	"set dnr_active_interval         0x401     dnr_activ"
	.ascii	"e_interval(ms)\012\000"
	.space	1
.LC130:
	.ascii	"stop/start syntax dec           0x402     do not ca"
	.ascii	"re\012\000"
	.space	1
.LC131:
	.ascii	"set trace controller            0x500     vfmw_stat"
	.ascii	"e_word in /proc/vfmw_prn\012\000"
	.space	3
.LC132:
	.ascii	"set bitstream control period    0x501     period (m"
	.ascii	"s)\012\000"
	.space	1
.LC133:
	.ascii	"set frame control period        0x502     period (m"
	.ascii	"s)\012\000"
	.space	1
.LC134:
	.ascii	"set rcv/rls img control period  0x503     period (m"
	.ascii	"s)\012\000"
	.space	1
.LC135:
	.ascii	"set no stream report period     0x504     period (m"
	.ascii	"s)\012\000"
	.space	1
.LC136:
	.ascii	"set module lowdelay start       0x600     channel n"
	.ascii	"umber\012\000"
	.space	2
.LC137:
	.ascii	"set module lowdelay stop        0x601     channel n"
	.ascii	"umber\012\000"
	.space	2
.LC138:
	.ascii	"set tunnel line number          0x602     channel n"
	.ascii	"umber\012\000"
	.space	2
.LC139:
	.ascii	"set scd lowdelay start          0x603     channel n"
	.ascii	"umber\012\000"
	.space	2
.LC140:
	.ascii	"set scd lowdelay stop           0x604     channel n"
	.ascii	"umber\012\000"
	.space	2
.LC141:
	.ascii	"=============== vfmw info =============\012\000"
	.space	3
.LC142:
	.ascii	"%-35s :%d\012\000"
	.space	1
.LC143:
	.ascii	"version num\000"
.LC144:
	.ascii	"extra_ref\000"
	.space	2
.LC145:
	.ascii	"extra_disp\000"
	.space	1
.LC146:
	.ascii	"extra_cmd\000"
	.space	2
.LC147:
	.ascii	"USE_FF_APT_EN\000"
	.space	2
.LC148:
	.ascii	"ResetCreateNewSave\000"
	.space	1
.LC149:
	.ascii	"============================= vfmw PrivInfo ======="
	.ascii	"=======================\012\000"
.LC150:
	.ascii	"%-45s :%d\012\000"
	.space	1
.LC151:
	.ascii	"VersionNum\000"
	.space	1
.LC152:
	.ascii	"----------------------------- vdh  info -----------"
	.ascii	"-----------------\012\000"
	.space	2
.LC153:
	.ascii	"%-45s :%d.%d%%\012\000"
.LC154:
	.ascii	"VDH 0 load\000"
	.space	1
.LC155:
	.ascii	"----------------------------- scd  info -----------"
	.ascii	"-----------------\012\000"
	.space	2
.LC156:
	.ascii	"SCD %d load             :%d.%d%%\012\000"
	.space	2
.LC157:
	.ascii	"----------------------------- dsp  info -----------"
	.ascii	"-----------------\012\000"
	.space	2
.LC158:
	.ascii	"DSP %d state             :%d\012\000"
	.space	2
.LC159:
	.ascii	"----------------------------- chan  info ----------"
	.ascii	"------------------\012\000"
	.space	1
.LC160:
	.ascii	"chanId[%d]-->MatchScdIdPlus1 [%d]    MatchVdhIdPlus"
	.ascii	"1 [%d]\012\000"
	.space	1
.LC161:
	.ascii	"This Chan has not been created!!!\000"
	.space	2
.LC162:
	.ascii	"can NOT get a not-opened Chan's information of bits"
	.ascii	"tream\000"
	.space	3
.LC163:
	.ascii	"fuction return value is null,%s %d unknow error!!\012"
	.ascii	"\000"
	.space	1
.LC164:
	.ascii	"============================= vfmw%02d info ======="
	.ascii	"=======================\012\000"
.LC165:
	.ascii	"VfmwID\000"
	.space	1
.LC166:
	.ascii	"----------------------------- scd stream info -----"
	.ascii	"----------------------\012\000"
	.space	1
.LC167:
	.ascii	"%-45s :%d/%d\012\000"
	.space	2
.LC168:
	.ascii	"RawStream(Size/Num)\000"
.LC169:
	.ascii	"SCDSegStream(Size/Num)\000"
	.space	1
.LC170:
	.ascii	"%-45s :%d/%d/%d%%\012\000"
	.space	1
.LC171:
	.ascii	"SCDSegBuffer(Total/Use/Percent)\000"
.LC172:
	.ascii	"----------------------------- vdh frame info ------"
	.ascii	"----------------------\012\000"
	.space	1
.LC173:
	.ascii	"%-45s :%d*%d\012\000"
	.space	2
.LC174:
	.ascii	"Decode(Width*Height)\000"
	.space	3
.LC175:
	.ascii	"Display(Width*Height)\000"
	.space	2
.LC176:
	.ascii	"%-45s :%d.%d fps\012\000"
	.space	2
.LC177:
	.ascii	"FrameRate\000"
	.space	2
.LC178:
	.ascii	"VDHFrameBuffer(Total/Use/Percent)\000"
	.space	2
.LC179:
	.ascii	"==================================================="
	.ascii	"========================\012\000"
	.space	3
.LC180:
	.ascii	"Last frame output failed!\012\000"
	.space	1
.LC181:
	.ascii	"Last frame output successed!\012\000"
	.space	2
.LC182:
	.ascii	"Last frame already output, image id: %d!\012\000"
	.space	2
.LC183:
	.ascii	"DFS, Wrong! Phyaddr:0x%x, Viraddr:0x%x, frm_num: 0x"
	.ascii	"%x\012\000"
	.space	1
.LC184:
	.ascii	"DFS, Not enough Frame node,rls all node, FrmNum:%d,"
	.ascii	" AllocedFrameNum: %d\012\000"
	.space	3
.LC185:
	.ascii	"DFS, Rls Fail, chanid: %d\012\000"
	.space	1
.LC186:
	.ascii	"VFMW_FRM_BUF\000"
	.space	3
.LC187:
	.ascii	"DFS, Not enough resource, ChanID: %d, AllocedFrmNum"
	.ascii	": %d, FrmNum: %d, i: %d\012\000"
.LC188:
	.ascii	"DFS, Rls Frame Node Fail!\012\000"
	.space	1
.LC189:
	.ascii	"DFS, framsize wrong! framesize: 0x%x\012\000"
	.space	2
.LC190:
	.ascii	"%s, %d, AllocMemMMZ fail!\012\000"
	.space	1
.LC191:
	.ascii	"%s,can not use mmz. NeedMMZ: %d\012\000"
	.space	3
.LC192:
	.ascii	"%s, %d, AllocMemPre fail!\012\000"
	.space	1
.LC193:
	.ascii	"%s,can't use mmz. NeedMMZ: %d\012\000"
	.space	1
.LC194:
	.ascii	"ChanID out of range!\000"
	.space	3
.LC195:
	.ascii	"VFMW_Hal_%d\000"
.LC196:
	.ascii	"VFMW_ScdMsg_%d\000"
	.space	1
.LC197:
	.ascii	"hi_vdec_vdh_irq\000"
.LC198:
	.ascii	"hi_vdec_scd_irq\000"
.LC199:
	.ascii	"VCTRL_GetUsrdecFrame but VFMW_USER != s_pstVfmwChan"
	.ascii	"[ChanID]->eVidStd!\012\000"
	.space	1
.LC200:
	.ascii	"VCTRL_GetUsrdecFrame but s_pstVfmwChan[ChanID]->s32"
	.ascii	"UsrdecFrameNum < MIN_USERDEC_FRAME_NUM!\012\000"
.LC201:
	.ascii	"VCTRL_GetUsrdecFrame but FSP_IsNewFsAvalible(ChanID"
	.ascii	") != 1!\012\000"
.LC202:
	.ascii	"get frame store fail!\012\000"
	.space	1
.LC203:
	.ascii	"get image buffer ok: LogicFsID = %d\012\000"
	.space	3
.LC204:
	.ascii	"line: %d, pLf is NULL!\012\000"
.LC205:
	.ascii	"decode %p, disp %p, tf %p\012\000"
	.space	1
.LC206:
	.ascii	"VCTRL_GetUsrdecFrame get LogicFs fail!\012\000"
.LC207:
	.ascii	"userdec frame(phy=%#x) address error!\012\000"
	.space	1
.LC208:
	.ascii	"can not map vir addr for usrdat frame(cbphy=%#x)\012"
	.ascii	"\000"
	.space	2
.LC209:
	.ascii	"line: %d, pLogic is Null!\012\000"
	.space	1
.LC210:
	.ascii	"eYuvFormat %d is not support!!\012\000"
.LC211:
	.ascii	"pUsrdecFrame == NULL\000"
	.space	3
.LC212:
	.ascii	"VCTRL_PutUsrdecFrame: VidStd is %d\012\000"
.LC213:
	.ascii	"VCTRL_PutUsrdecFrame return err\012\000"
	.space	3
.LC214:
	.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000"
.LC215:
	.ascii	"This channel is not opened\000"
	.space	1
.LC216:
	.ascii	"This channel is not running\000"
.LC217:
	.ascii	"Syntax is stopped from This channel\000"
.LC218:
	.ascii	"[%d] vdm busy\012\000"
	.space	1
.LC219:
	.ascii	"[%d] no frame\012\000"
	.space	1
.LC220:
	.ascii	"[%d] no stream\012\000"
.LC221:
	.ascii	"seg_pts: %lld, seg_usertag = %lld\012\000"
	.space	1
.LC222:
	.ascii	"pic_pts: %lld\012\000"
	.space	1
.LC223:
	.ascii	"pic_usertag: %lld\012\000"
	.space	1
.LC224:
	.ascii	"pic_pts: %lld pic_usertag = %lld\012\000"
	.space	2
.LC225:
	.ascii	"%s:ChanId %d this hevc file is 10bit!!!\012\000"
	.space	3
.LC226:
	.ascii	"DFS, Wait Partition\012\000"
	.space	3
.LC227:
	.ascii	"DFS, Partition fail, u32DynamicFrameStoreAllocEn: %"
	.ascii	"d, eFspPartitionState: %d\012\000"
	.space	2
.LC228:
	.ascii	"line: %d Flush DPB failed!\012\000"
.LC229:
	.ascii	"VCTRL_FlushDecoder\012\000"
.LC230:
	.ascii	"fuction return value is null,%s %d MVC_OK != MVC_Fl"
	.ascii	"ushDPB!!\012\000"
	.space	3
.LC231:
	.ascii	"pImage is NULL\000"
	.space	1
.LC232:
	.ascii	"call VCTRL_ReleaseChanImage, ChanID, ImgID = %d,%d\012"
	.ascii	"\000"
.LC233:
	.ascii	"vdm_ctrl.c,L%d: Chan inactive\012\000"
	.space	1
.LC234:
	.ascii	"vdm_ctrl.c,L%d: This channel is not opened\012\000"
.LC235:
	.ascii	"%s call SYNTAX_ReleaseImage failed\012\000"
.LC236:
	.ascii	"call VCTRL_GetChanImage, ChanID = %d,\012\000"
	.space	1
.LC237:
	.ascii	"%s: view_0 id(%d) > view_1 id(%d), error!\012\000"
	.space	1
.LC238:
	.ascii	"%s: continuous view0 id(%d)!\012\000"
	.space	2
.LC239:
	.ascii	"%s: continuous view1 id(%d)!\012\000"
	.space	2
.LC240:
	.ascii	"WARNNING: ScdLowdlyEnable = %d, VidStd = %d, eDSPSt"
	.ascii	"ate = %d AVS(+) and LOWDLY  cannot supported in the"
	.ascii	" same time!!!\012\000"
	.space	3
.LC241:
	.ascii	"This Chan has not been created or has been destroye"
	.ascii	"d !\000"
	.space	1
.LC242:
	.ascii	"WARNING: vidio std not setted!\000"
	.space	1
.LC243:
	.ascii	"DFS, rls MMZ Node\012\000"
	.space	1
.LC244:
	.ascii	"DelMemRecord 0x%x failed!\012\000"
	.space	1
.LC245:
	.ascii	"image size abnormal(%dx%d)\012\000"
.LC246:
	.ascii	"no mem to arrange for soft dec\012\000"
.LC247:
	.ascii	"partition fs memory fail!\012\000"
	.space	1
.LC248:
	.ascii	"%s: L%d : vdm chan memory is too small to support u"
	.ascii	"ser decoder\012\000"
.LC249:
	.ascii	"FSP_ConfigInstance fail!\012\000"
	.space	2
.LC250:
	.ascii	"L: %d, Stream Interface Error!!, ChanID: %d\000"
.LC251:
	.ascii	"extra_ref=\000"
	.space	1
.LC252:
	.ascii	"=\000"
	.space	2
.LC253:
	.ascii	"ERROR: extra_ref = %d is out of [ -5000, 5000 ]!\012"
	.ascii	"\000"
	.space	2
.LC254:
	.ascii	"extra_disp=\000"
.LC255:
	.ascii	"ERROR: extra_disp = %d is out of [ -5000, 5000 ]!\012"
	.ascii	"\000"
	.space	1
.LC256:
	.ascii	"extra_cmd=\000"
	.space	1
.LC257:
	.ascii	"HI_VFMW_VideoDecode\000"
.LC258:
	.ascii	"%s 1 The channel %d is not active\012\000"
	.space	1
.LC259:
	.ascii	"The channel %d is deced\012\000"
	.space	3
.LC260:
	.ascii	"The pDecParam of channel %d is NULL\012\000"
	.space	3
.LC261:
	.ascii	"%s 2 The channel %d is not active\012\000"
	.space	1
.LC262:
	.ascii	"Vfmw resume totally take %d ms\012\000"
.LC263:
	.ascii	"Wait sleep time out %d ms (isScdSleep=%d, isVdmSlee"
	.ascii	"p=%d)!\012\000"
	.space	1
.LC264:
	.ascii	"Force scd %d sleep.\012\000"
	.space	3
.LC265:
	.ascii	"Force vdm %d sleep.\012\000"
	.space	3
.LC266:
	.ascii	"Vfmw suspend totally take %d ms\012\000"
	.space	3
.LC267:
	.ascii	"chan %d: new ChanErrThr = %d\012\000"
	.space	2
.LC268:
	.ascii	"chan %d: new DecOrderOutput = %d\012\000"
	.space	2
.LC269:
	.ascii	"chan %d: new DecMode = %d\012\000"
	.space	1
.LC270:
	.ascii	"chan %d: GetChanCfg failed!\012\000"
	.space	3
.LC271:
	.ascii	"chan %d: new StrmOFThr = %d\012\000"
	.space	3
.LC272:
	.ascii	"USE_FF_APT_EN = %d\012\000"
.LC273:
	.ascii	"USE_FF_APT_EN can NOT be set to %d, must be 0 or 1\012"
	.ascii	"\000"
.LC274:
	.ascii	"ResetCreateNewSave = %d\012\000"
	.space	3
.LC275:
	.ascii	"ResetCreateNewSave can NOT be set to %d, must be 0 "
	.ascii	"or 1\012\000"
	.space	3
.LC276:
	.ascii	"NO SUCH CHANNEL : %d\012\000"
	.space	2
.LC277:
	.ascii	"Pay attention to  CHANNEL : %d\012\000"
.LC278:
	.ascii	"print memory tracer...\012\000"
.LC279:
	.ascii	"%s/vfmw_raw_save_%d.dat\000"
.LC280:
	.ascii	"OK create file '%s' for channel %d raw stream save\012"
	.ascii	"\000"
.LC281:
	.ascii	"failed create file '%s' for raw stream save!\012\000"
	.space	2
.LC282:
	.ascii	">>>> close raw stream saving >>>>\012\000"
	.space	1
.LC283:
	.ascii	"%s/vfmw_seg_save_%d.dat\000"
.LC284:
	.ascii	"OK create file '%s' for channel %d seg stream save\012"
	.ascii	"\000"
.LC285:
	.ascii	"failed create file '%s' for seg stream save!\012\000"
	.space	2
.LC286:
	.ascii	">>>> close seg stream saving >>>>\012\000"
	.space	1
.LC287:
	.ascii	"%s/vfmw_yuv_save_%d.yuv\000"
.LC288:
	.ascii	"VFMW_BigTile1d_YUV\000"
	.space	1
.LC289:
	.ascii	"Failed Alloc VFMW_BigTile1d_YUV for yuv save!\012\000"
	.space	1
.LC290:
	.ascii	"OK create file '%s' for chan %d yuv save.(crop %d)\012"
	.ascii	"\000"
.LC291:
	.ascii	"failed create file '%s' for yuv save!\012\000"
	.space	1
.LC292:
	.ascii	"OK close yuv save.\012\000"
.LC293:
	.ascii	"address '0x%x' is not valid!\012\000"
	.space	2
.LC294:
	.ascii	"%s/2d_0x%x.yuv\000"
	.space	1
.LC295:
	.ascii	"2d image has been saved to '%s'\012\000"
	.space	3
.LC296:
	.ascii	"open file '%s' fail!\012\000"
	.space	2
.LC297:
	.ascii	"%s/1d_0x%x.yuv\000"
	.space	1
.LC298:
	.ascii	"1d image has been saved to '%s'\012\000"
	.space	3
.LC299:
	.ascii	"stop chan %d: VCTRL_StopChan return %d\012\000"
.LC300:
	.ascii	"reset chan %d: VCTRL_ResetChan return %d\012\000"
	.space	2
.LC301:
	.ascii	"start chan %d: VCTRL_StartChan return %d\012\000"
	.space	2
.LC302:
	.ascii	"------ dec task delay %d ms ------\012\000"
.LC303:
	.ascii	"------ dnr active per %d ms ------\012\000"
.LC304:
	.ascii	"------ dec stop = %d ------\012\000"
	.space	3
.LC305:
	.ascii	"------ g_TraceCtrl = %x ------\012\000"
.LC306:
	.ascii	"------ g_TraceBsPeriod = %x ------\012\000"
.LC307:
	.ascii	"------ g_TraceFramePeriod = %x ------\012\000"
	.space	1
.LC308:
	.ascii	"------ g_TraceImgPeriod = %x ------\012\000"
	.space	3
.LC309:
	.ascii	"The channel number is to Large.\012\000"
	.space	3
.LC310:
	.ascii	"------ s_pstVfmwChan[%d]->stSynExtraData.s32ModuleL"
	.ascii	"owlyEnable = 1 ------\012\000"
	.space	2
.LC311:
	.ascii	"------ Set SCD[%d] to work  ------\012\000"
.LC312:
	.ascii	"MMZ: your parameter string is too long!\012\000"
	.space	3
.LC313:
	.ascii	"MMZ: copy_from_user failed!\012\000"
	.space	3
.LC314:
	.ascii	"error echo cmd '%s'!\012\000"
	.space	2
.LC315:
	.ascii	"******* vfmw save path: %s ********\012\000"
	.space	3
.LC316:
	.ascii	"%s %d j < 1!!\012\000"
	.space	1
.LC317:
	.ascii	"\012vfmw debug: arg1=%#x, arg2=%#x\012\000"
	.space	3
.LC318:
	.ascii	"---------------------------------------------------"
	.ascii	"----------------------\012\000"
	.space	1
.LC319:
	.ascii	"VCTRL_CheckChanWH return err.\012\000"
	.space	1
.LC320:
	.ascii	"VFMW didn't support std %d.\012\000"
	.space	3
.LC321:
	.ascii	"VCTRL_ConfigChan with same config paramater.\012\000"
	.space	2
.LC322:
	.ascii	"%s %d: s_pstVfmwChan has been destroyed!!\012\000"
	.space	1
.LC323:
	.ascii	"====== Fatal Error0: can NOT re-map vir address for"
	.ascii	" channel %d ======\012\000"
	.space	1
.LC324:
	.ascii	"fatal error: can not del mem record(phy=0x%x,vir=%p"
	.ascii	",len=%d)\012\000"
	.space	3
.LC325:
	.ascii	"====== Fatal Error1: can NOT re-map vir address for"
	.ascii	" channel %d ======\012\000"
	.space	1
.LC326:
	.ascii	"can NOT VCTRL_PartitionMemForStdUser\012\000"
	.space	2
.LC327:
	.ascii	"vdm_ctrl.c,L%d: %s\012\000"
.LC328:
	.ascii	"This Chan has not been created or has been destroye"
	.ascii	"d !!!\000"
	.space	3
.LC329:
	.ascii	"can NOT stop a not-opened Chan\000"
	.space	1
.LC330:
	.ascii	"VDEC_CID_CREATE_CHAN_WITH_OPTION is designed for CA"
	.ascii	"P_LEVEL_USER_DEFINE_WITH_OPTION, please change chan"
	.ascii	"nel's capability.\012\000"
	.space	3
.LC331:
	.ascii	"line %d VCTRL_GetChanMemSizeWithOption failed!\012\000"
.LC332:
	.ascii	"L: %d : sdk can NOT alloc buffer for channel contex"
	.ascii	"t\012\000"
	.space	2
.LC333:
	.ascii	"L: %d : can NOT alloc buffer for SCD\012\000"
	.space	2
.LC334:
	.ascii	"L: %d : can NOT alloc buffer for VDH\012\000"
	.space	2
.LC335:
	.ascii	"VFMW_Chan_Ctx\000"
	.space	2
.LC336:
	.ascii	"L: %d : we can NOT alloc buffer for channel context"
	.ascii	", size = %d\012\000"
.LC337:
	.ascii	"VFMW_Chan_Vdh\000"
	.space	2
.LC338:
	.ascii	"L: %d : can NOT alloc buffer for channel vdh, size "
	.ascii	"= %d\012\000"
	.space	3
.LC339:
	.ascii	"VFMW_Chan_Scd\000"
	.space	2
.LC340:
	.ascii	"L: %d : can NOT alloc buffer for channel scd, size "
	.ascii	"= %d\012\000"
	.space	3
.LC341:
	.ascii	"L: %d : part we can NOT alloc buffer for channel co"
	.ascii	"ntext\012\000"
	.space	2
.LC342:
	.ascii	"L: %d : can NOT alloc buffer for channel context\012"
	.ascii	"\000"
	.space	2
.LC343:
	.ascii	"L: %d : can NOT alloc buffer for channel vdh\012\000"
	.space	2
.LC344:
	.ascii	"L: %d : can NOT alloc buffer for channel vdh, %#x <"
	.ascii	" %#x\012\000"
	.space	3
.LC345:
	.ascii	"L: %d : can NOT alloc buffer for channel scd\012\000"
	.space	2
.LC346:
	.ascii	"mem alloc mode is not supportted\012\000"
	.space	2
.LC347:
	.ascii	"vfmw have max(%d) channels opened, can NOT crerate "
	.ascii	"more channels\012\000"
	.space	2
.LC348:
	.ascii	"can NOT enable FSP instance\012\000"
	.space	3
.LC349:
	.ascii	"VCTRL_CreateChan eCapLevel = %d error! Try to use V"
	.ascii	"CTRL_CreateChanWithOption(CAP_LEVEL_USER_DEFINE_WIT"
	.ascii	"H_OPTION, ...)\012\000"
	.space	2
.LC350:
	.ascii	"VCTRL_GetChanMemSize ERROR\012\000"
.LC351:
	.ascii	"channel memory have been allocated outside, but the"
	.ascii	" mem-info is not correct!\012\000"
	.space	2
.LC352:
	.ascii	"mem-info(phy, vir, size) = (%#x, %p, %d)\012\000"
	.space	2
.LC353:
	.ascii	"this channel totally need %d bytes memory\012\000"
	.space	1
.LC354:
	.ascii	"Thread running...\012\000"
	.space	1
.LC355:
	.ascii	"thread running...\012\000"
	.space	1
.LC356:
	.ascii	"Thread stopped!\012\000"
	.space	3
.LC357:
	.ascii	"thread stopped...\012\000"
	.space	1
.LC358:
	.ascii	"Thread killed!\012\000"
.LC359:
	.ascii	"vdm_ctrl.c,L%d: pOption->s32KeepBS error\012\000"
	.space	2
.LC360:
	.ascii	"BLANK\000"
	.space	2
.LC361:
	.ascii	"RECEIVED\000"
	.space	3
.LC362:
	.ascii	"SUCCESS\000"
.LC363:
	.ascii	"FAILURE\000"
.LC364:
	.ascii	"FRAMEID\000"
.LC365:
	.ascii	"H264\000"
	.space	3
.LC366:
	.ascii	"VC1\000"
.LC367:
	.ascii	"MPEG4\000"
	.space	2
.LC368:
	.ascii	"MPEG2\000"
	.space	2
.LC369:
	.ascii	"H263\000"
	.space	3
.LC370:
	.ascii	"DIVX3\000"
	.space	2
.LC371:
	.ascii	"AVS\000"
.LC372:
	.ascii	"JPEG\000"
	.space	3
.LC373:
	.ascii	"REAL8\000"
	.space	2
.LC374:
	.ascii	"REAL9\000"
	.space	2
.LC375:
	.ascii	"VP6\000"
.LC376:
	.ascii	"VP6F\000"
	.space	3
.LC377:
	.ascii	"VP6A\000"
	.space	3
.LC378:
	.ascii	"VP8\000"
.LC379:
	.ascii	"SORENSON\000"
	.space	3
.LC380:
	.ascii	"MVC\000"
.LC381:
	.ascii	"HEVC\000"
	.space	3
.LC382:
	.ascii	"RAW\000"
.LC383:
	.ascii	"USER\000"
	.space	3
.LC384:
	.ascii	"RESERVED\000"
	.space	3
.LC385:
	.ascii	"=============== scd info =========================="
	.ascii	"====\012\000"
	.space	3
.LC386:
	.ascii	"IsScdDrvOpen\000"
	.space	3
.LC387:
	.ascii	"SCDState\000"
	.space	3
.LC388:
	.ascii	"ThisInstID\000"
	.space	1
.LC389:
	.ascii	"LastProcessTime\000"
.LC390:
	.ascii	"%-25s :%#x\012\000"
.LC391:
	.ascii	"HwMemAddr\000"
	.space	2
.LC392:
	.ascii	"HwMemSize\000"
	.space	2
.LC393:
	.ascii	"DownMsgMemAddr\000"
	.space	1
.LC394:
	.ascii	"UpMsgMemAddr\000"
	.space	3
.LC395:
	.ascii	"--------------- inst[%d] -------------\012\000"
.LC396:
	.ascii	"Mode\000"
	.space	3
.LC397:
	.ascii	"%-25s :%s\012\000"
	.space	1
.LC398:
	.ascii	"cfg VidStd\000"
	.space	1
.LC399:
	.ascii	"is wait seg ext\000"
.LC400:
	.ascii	"is_omx_path\000"
.LC401:
	.ascii	"cfg BufPhyAddr\000"
	.space	1
.LC402:
	.ascii	"cfg BufSize\000"
.LC403:
	.ascii	"raw size count\000"
	.space	1
.LC404:
	.ascii	"raw num count\000"
	.space	2
.LC405:
	.ascii	"raw Total size\000"
	.space	1
.LC406:
	.ascii	"raw Total num\000"
	.space	2
.LC407:
	.ascii	"seg Total size\000"
	.space	1
.LC408:
	.ascii	"seg Total num\000"
	.space	2
.LC409:
	.ascii	"seg read_addr\000"
	.space	2
.LC410:
	.ascii	"seg write_addr\000"
	.space	1
.LC411:
	.ascii	"%-25s :%d Kbps\012\000"
.LC412:
	.ascii	"actual bitrate\000"
	.space	1
.LC413:
	.ascii	"\012============== DEC INFO Chan [%d] ============="
	.ascii	"=\012\000"
	.space	1
.LC414:
	.ascii	"NA\000"
	.space	1
.LC415:
	.ascii	"Non_Attach\000"
	.space	1
.LC416:
	.ascii	"Attach\000"
	.space	1
.LC417:
	.ascii	"%-25s :%d(%s)\012\000"
	.space	1
.LC418:
	.ascii	"Dec by VDH\000"
	.space	1
.LC419:
	.ascii	"IsOpen\000"
	.space	1
.LC420:
	.ascii	"IsRun\000"
	.space	2
.LC421:
	.ascii	"Priority\000"
	.space	3
.LC422:
	.ascii	"eVidStd\000"
.LC423:
	.ascii	"ChanCapLevel\000"
	.space	3
.LC424:
	.ascii	"LastFrameState\000"
	.space	1
.LC425:
	.ascii	"IsOmxPath\000"
	.space	2
.LC426:
	.ascii	"DecMode\000"
.LC427:
	.ascii	"DecOrderOutput\000"
	.space	1
.LC428:
	.ascii	"ErrorThred\000"
	.space	1
.LC429:
	.ascii	"StreamThred\000"
.LC430:
	.ascii	"StdExt AP\000"
	.space	2
.LC431:
	.ascii	"StdExt CodecVer\000"
.LC432:
	.ascii	"StdExt Reversed\000"
.LC433:
	.ascii	"Skip Frame Found\000"
	.space	3
.LC434:
	.ascii	"Skip Frame Discarded\000"
	.space	3
.LC435:
	.ascii	"Is Short Headed\000"
.LC436:
	.ascii	"Recent UsrdecFrame: enFmt=%d,w=%d,h=%d,Ystride=%d,C"
	.ascii	"stride=%d,PTS=%lld\012\000"
	.space	1
.LC437:
	.ascii	"ChanMem VDH Mem Phy\000"
.LC438:
	.ascii	"ChanMem VDH Mem Size\000"
	.space	3
.LC439:
	.ascii	"ChanMem SCD Mem Phy\000"
.LC440:
	.ascii	"ChanMem SCD Mem Size\000"
	.space	3
.LC441:
	.ascii	"ChanMem CTX Mem Phy\000"
.LC442:
	.ascii	"ChanMem CTX Mem Size\000"
	.space	3
.LC443:
	.ascii	"%-25s :%d,%d,%d\012\000"
	.space	3
.LC444:
	.ascii	"Ref,Read,New\000"
	.space	3
.LC445:
	.ascii	"%-25s :(%d,%d,%d)\012\000"
	.space	1
.LC446:
	.ascii	"VoQue Detail\000"
	.space	3
.LC447:
	.ascii	"Actual DecMode\000"
	.space	1
.LC448:
	.ascii	"Actual DecOrderOutput\000"
	.space	2
.LC449:
	.ascii	"Image Format\000"
	.space	3
.LC450:
	.ascii	"Frame Packing Type\000"
	.space	1
.LC451:
	.ascii	"------------------- FSP INFO ------------------\012"
	.ascii	"\000"
	.space	3
.LC452:
	.ascii	"FSP DecFsWidth\000"
	.space	1
.LC453:
	.ascii	"FSP DecFsHeight\000"
.LC454:
	.ascii	"FSP DispFsWidth\000"
.LC455:
	.ascii	"FSP DispFsHeight\000"
	.space	3
.LC456:
	.ascii	"FSP ExpectedDecFsNum\000"
	.space	3
.LC457:
	.ascii	"FSP TotalValidFSNum\000"
.LC458:
	.ascii	"FSP ActualPmvNum\000"
	.space	3
.LC459:
	.ascii	"\012%-25s :%d\012\000"
.LC460:
	.ascii	"FSP DispLoopEnable\000"
	.space	1
.LC461:
	.ascii	"FSP ExpectedDispFsNum\000"
	.space	2
.LC462:
	.ascii	"FSP s32DispFsNum\000"
	.space	3
.LC463:
	.ascii	"%d%d \000"
	.space	2
.LC464:
	.ascii	"FSP ActualDecFsNum\000"
	.space	1
.LC465:
	.ascii	"FSP LogicFsNum\000"
	.space	1
.LC466:
	.ascii	"---------------Dynamic Frame Store---------------\012"
	.ascii	"\000"
	.space	1
.LC467:
	.ascii	"%-40s : %d\012\000"
.LC468:
	.ascii	"Frame Size(byte)\000"
	.space	3
.LC469:
	.ascii	"Max Time(ms)\000"
	.space	3
.LC470:
	.ascii	"Reference Frame Number\000"
	.space	1
.LC471:
	.ascii	"%-40s : %d/%d\012\000"
	.space	1
.LC472:
	.ascii	"Pre-alloced Frame Number/Time(ms)\000"
	.space	2
.LC473:
	.ascii	"Dynamic alloced Frame Number/Time(ms)\000"
	.space	2
.LC474:
	.ascii	"All Frame Number/Time(ms)\000"
	.space	2
.LC475:
	.ascii	"------------------- VDH INFO ------------------\012"
	.ascii	"\000"
	.space	3
.LC476:
	.ascii	"%s%-21d :%d.%d%%\012\000"
	.space	2
.LC477:
	.ascii	"VDH \000"
	.space	3
.LC478:
	.ascii	"%-25s :%d.%d fps(Chan %d)\012\000"
	.space	1
.LC479:
	.ascii	"Frame Rate\000"
	.space	1
.LC480:
	.ascii	"%-25s :%d/mb\012\000"
	.space	2
.LC481:
	.ascii	"Cycle State\000"
	.section	__param,"a",%progbits
	.align	2
	.type	__param_extra_cmd, %object
	.size	__param_extra_cmd, 16
__param_extra_cmd:
@ name:
	.word	__param_str_extra_cmd
@ ops:
	.word	param_ops_int
@ perm:
	.short	0
@ level:
	.short	-1
@ <anonymous>:
@ arg:
	.word	extra_cmd
	.type	__param_extra_disp, %object
	.size	__param_extra_disp, 16
__param_extra_disp:
@ name:
	.word	__param_str_extra_disp
@ ops:
	.word	param_ops_int
@ perm:
	.short	0
@ level:
	.short	-1
@ <anonymous>:
@ arg:
	.word	extra_disp
	.type	__param_extra_ref, %object
	.size	__param_extra_ref, 16
__param_extra_ref:
@ name:
	.word	__param_str_extra_ref
@ ops:
	.word	param_ops_int
@ perm:
	.short	0
@ level:
	.short	-1
@ <anonymous>:
@ arg:
	.word	extra_ref
	.bss
	.align	2
.LANCHOR0 = . + 0
.LANCHOR3 = . + 8184
.LANCHOR4 = . + 16368
	.type	s_pstVfmwChan, %object
	.size	s_pstVfmwChan, 64
s_pstVfmwChan:
	.space	64
	.type	g_event_report, %object
	.size	g_event_report, 4
g_event_report:
	.space	4
	.type	extra_ref, %object
	.size	extra_ref, 4
extra_ref:
	.space	4
	.type	extra_disp, %object
	.size	extra_disp, 4
extra_disp:
	.space	4
	.type	g_SdecFunc, %object
	.size	g_SdecFunc, 28
g_SdecFunc:
	.space	28
	.type	s_VfmwCTrl, %object
	.size	s_VfmwCTrl, 208
s_VfmwCTrl:
	.space	208
	.type	s_StreamIntf, %object
	.size	s_StreamIntf, 192
s_StreamIntf:
	.space	192
	.type	pY, %object
	.size	pY, 4
pY:
	.space	4
	.type	pVl, %object
	.size	pVl, 4
pVl:
	.space	4
	.type	pUl, %object
	.size	pUl, 4
pUl:
	.space	4
	.type	g_VdmCharacter, %object
	.size	g_VdmCharacter, 4
g_VdmCharacter:
	.space	4
	.type	g_TaskLock, %object
	.size	g_TaskLock, 12
g_TaskLock:
	.space	12
	.type	s_ChanControlState, %object
	.size	s_ChanControlState, 64
s_ChanControlState:
	.space	64
	.type	vfmw_proc, %object
	.size	vfmw_proc, 768
vfmw_proc:
	.space	768
	.type	g_CurProcChan, %object
	.size	g_CurProcChan, 4
g_CurProcChan:
	.space	4
	.type	extra_cmd, %object
	.size	extra_cmd, 4
extra_cmd:
	.space	4
	.type	g_ResetCreateNewSave, %object
	.size	g_ResetCreateNewSave, 4
g_ResetCreateNewSave:
	.space	4
	.type	g_VfmwGlobalStat, %object
	.size	g_VfmwGlobalStat, 84
g_VfmwGlobalStat:
	.space	84
	.type	g_VfmwChanStat, %object
	.size	g_VfmwChanStat, 4800
g_VfmwChanStat:
	.space	4800
	.type	last_rec_pos_time.53499, %object
	.size	last_rec_pos_time.53499, 64
last_rec_pos_time.53499:
	.space	64
	.type	last_rec_pos_decparam_time.53500, %object
	.size	last_rec_pos_decparam_time.53500, 64
last_rec_pos_decparam_time.53500:
	.space	64
	.type	ChanPriTab.53383, %object
	.size	ChanPriTab.53383, 64
ChanPriTab.53383:
	.space	64
	.type	g_ActivateLock, %object
	.size	g_ActivateLock, 12
g_ActivateLock:
	.space	12
	.type	last_rec_pos_time.52043, %object
	.size	last_rec_pos_time.52043, 64
last_rec_pos_time.52043:
	.space	64
	.type	vfmw_save_yuv_file, %object
	.size	vfmw_save_yuv_file, 128
vfmw_save_yuv_file:
	.space	128
	.type	save_yuv_with_crop, %object
	.size	save_yuv_with_crop, 4
save_yuv_with_crop:
	.space	4
	.type	last_rec_pos_time.51920, %object
	.size	last_rec_pos_time.51920, 64
last_rec_pos_time.51920:
	.space	64
	.type	g_DSPState, %object
	.size	g_DSPState, 64
g_DSPState:
	.space	64
	.type	PrioArray.51114, %object
	.size	PrioArray.51114, 64
PrioArray.51114:
	.space	64
	.type	FspInstInfo.50419, %object
	.size	FspInstInfo.50419, 3852
FspInstInfo.50419:
	.space	3852
	.type	cmdline, %object
	.size	cmdline, 1024
cmdline:
	.space	1024
	.type	g_allow_B_before_P, %object
	.size	g_allow_B_before_P, 1
g_allow_B_before_P:
	.space	1
	.type	g_not_allow_H264FullPictureRepair_flag, %object
	.size	g_not_allow_H264FullPictureRepair_flag, 1
g_not_allow_H264FullPictureRepair_flag:
	.space	1
	.type	g_apple_airplay_mirrorinig_flag, %object
	.size	g_apple_airplay_mirrorinig_flag, 1
g_apple_airplay_mirrorinig_flag:
	.space	1
	.space	1
	.type	g_IntEvent, %object
	.size	g_IntEvent, 16
g_IntEvent:
	.space	16
	.type	AcceleratorCharacter, %object
	.size	AcceleratorCharacter, 4
AcceleratorCharacter:
	.space	4
	.type	LastEventTime.50035, %object
	.size	LastEventTime.50035, 4
LastEventTime.50035:
	.space	4
	.type	vfmw_save_str_file, %object
	.size	vfmw_save_str_file, 128
vfmw_save_str_file:
	.space	128
	.type	save_file_cnt.54063, %object
	.size	save_file_cnt.54063, 4
save_file_cnt.54063:
	.space	4
	.type	save_str_chan_num, %object
	.size	save_str_chan_num, 4
save_str_chan_num:
	.space	4
	.type	vfmw_save_seg_file, %object
	.size	vfmw_save_seg_file, 128
vfmw_save_seg_file:
	.space	128
	.type	save_file_cnt.54066, %object
	.size	save_file_cnt.54066, 4
save_file_cnt.54066:
	.space	4
	.type	save_seg_chan_num, %object
	.size	save_seg_chan_num, 4
save_seg_chan_num:
	.space	4
	.type	save_file_cnt.54071, %object
	.size	save_file_cnt.54071, 4
save_file_cnt.54071:
	.space	4
	.type	MemRecord_YUV, %object
	.size	MemRecord_YUV, 16
MemRecord_YUV:
	.space	16
	.type	g_SleepTime, %object
	.size	g_SleepTime, 4
g_SleepTime:
	.space	4
	.type	g_DnrSleepTime, %object
	.size	g_DnrSleepTime, 4
g_DnrSleepTime:
	.space	4
	.type	g_StopDec, %object
	.size	g_StopDec, 4
g_StopDec:
	.space	4
	.type	g_SCDID, %object
	.size	g_SCDID, 4
g_SCDID:
	.space	4
	.type	cmd.55076, %object
	.size	cmd.55076, 256
cmd.55076:
	.space	256
	.type	str.55077, %object
	.size	str.55077, 256
str.55077:
	.space	256
	.type	Capability.51392, %object
	.size	Capability.51392, 148
Capability.51392:
	.space	148
	.type	PrioArray.51391, %object
	.size	PrioArray.51391, 64
PrioArray.51391:
	.space	64
	.type	PrioArray.51147, %object
	.size	PrioArray.51147, 64
PrioArray.51147:
	.space	64
	.type	pOption, %object
	.size	pOption, 4
pOption:
	.space	4
	.type	g_u32DFSMaxAllocTime, %object
	.size	g_u32DFSMaxAllocTime, 4
g_u32DFSMaxAllocTime:
	.space	4
	.type	g_VdecIrqHandle, %object
	.size	g_VdecIrqHandle, 4
g_VdecIrqHandle:
	.space	4
	.type	g_DnrIrqHandle, %object
	.size	g_DnrIrqHandle, 4
g_DnrIrqHandle:
	.space	4
	.type	g_eVdmVersion, %object
	.size	g_eVdmVersion, 4
g_eVdmVersion:
	.space	4
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
