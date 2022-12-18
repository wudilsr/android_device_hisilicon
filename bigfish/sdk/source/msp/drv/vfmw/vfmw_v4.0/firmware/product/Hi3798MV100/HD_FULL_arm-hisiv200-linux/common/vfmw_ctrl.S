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
@ -DKBUILD_BASENAME=KBUILD_STR(vfmw_ctrl)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/vfmw/vfmw_v4.0/firmware/common/.vfmw_ctrl.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/common/vfmw_ctrl.c
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
	ldr	r0, [r3, r0, asl #2]	@ D.39224, s_pstVfmwChan
	cmp	r0, #0	@ D.39224,
	addne	r0, r0, #164	@ D.39227, D.39224,
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
	ldr	r0, [r3, r0, asl #2]	@ D.39273, s_pstVfmwChan
	cmp	r0, #0	@ D.39273,
	addne	r0, r0, #250880	@ D.39276, D.39273,
	addne	r0, r0, #608	@ D.39276, D.39276,
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
	ldr	r0, [r3, r0, asl #2]	@ D.39334, s_pstVfmwChan
	cmp	r0, #0	@ D.39334,
	addne	r0, r0, #152	@ D.39337, D.39334,
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
	movweq	r3, #:lower16:11613104	@ tmp135,
	movwne	r3, #:lower16:4780440	@ tmp136,
	movteq	r3, #:upper16:11613104	@ tmp135,
	movtne	r3, #:upper16:4780440	@ tmp136,
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
	ldr	r3, [r3, r0, asl #2]	@ D.40196, s_pstVfmwChan
	ldr	r2, [r3, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, #19	@ <variable>.eVidStd,
	bne	.L24	@,
.L18:
	mvn	r0, #0	@ D.40249,
	ldmfd	sp, {fp, sp, pc}	@
.L24:
	ldr	r2, [r3, #48]	@ D.40201, <variable>.stChanCfg.eVidStd
	ldr	r0, [r1, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, r0	@ D.40201, <variable>.eVidStd
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
	cmp	r2, #1	@ D.40201,
	beq	.L25	@,
	sub	r0, r2, #10	@ tmp170, D.40201,
	cmp	r0, #2	@ tmp170,
	bhi	.L20	@,
	ldr	r2, [r3, #52]	@ <variable>.stChanCfg.StdExt.Vp6Ext.bReversed, <variable>.stChanCfg.StdExt.Vp6Ext.bReversed
	ldr	ip, [r1, #4]	@ <variable>.StdExt.Vp6Ext.bReversed, <variable>.StdExt.Vp6Ext.bReversed
	cmp	r2, ip	@ <variable>.stChanCfg.StdExt.Vp6Ext.bReversed, <variable>.StdExt.Vp6Ext.bReversed
	bne	.L18	@,
.L20:
	mov	r0, #0	@ D.40249,
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
	ldr	r0, [r3, #816]	@ <variable>.s32NoStreamFlag, <variable>.s32NoStreamFlag
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
	mvn	r0, #0	@ D.41415,
	ldmfd	sp, {fp, sp, pc}	@
.L32:
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	ldr	r3, [r3, r0, asl #2]	@ D.41414, s_pstVfmwChan
	cmp	r3, #0	@ D.41414,
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
	ldr	r3, [r3, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #19	@ <variable>.eVidStd,
	movne	r0, #0	@ D.41415,
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
	ldr	ip, [ip, #36]	@ D.41796, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	cmp	ip, #0	@ D.41796,
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
	blx	ip	@ D.41796
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
	mvn	r0, #0	@ D.41809,
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
	ldr	r2, [r3, #0]	@ temp.1134, s_pstVfmwChan
	cmp	r2, #0	@ temp.1134,
	beq	.L38	@,
	add	r1, r2, #250880	@ tmp153, temp.1134,
	add	r2, r1, #616	@ tmp153, tmp153,
	cmp	r2, r0	@ tmp153, pCtx
	moveq	r0, #0	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L38:
	ldr	r2, [r3, #4]	@ temp.1136, s_pstVfmwChan
	cmp	r2, #0	@ temp.1136,
	beq	.L40	@,
	add	r2, r2, #250880	@ tmp156, temp.1136,
	add	ip, r2, #616	@ tmp156, tmp156,
	cmp	ip, r0	@ tmp156, pCtx
	moveq	r0, #1	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L40:
	ldr	r2, [r3, #8]	@ temp.1138, s_pstVfmwChan
	cmp	r2, #0	@ temp.1138,
	beq	.L41	@,
	add	ip, r2, #250880	@ tmp159, temp.1138,
	add	r1, ip, #616	@ tmp159, tmp159,
	cmp	r1, r0	@ tmp159, pCtx
	moveq	r0, #2	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L41:
	ldr	r2, [r3, #12]	@ temp.1140, s_pstVfmwChan
	cmp	r2, #0	@ temp.1140,
	beq	.L42	@,
	add	r1, r2, #250880	@ tmp162, temp.1140,
	add	r2, r1, #616	@ tmp162, tmp162,
	cmp	r2, r0	@ tmp162, pCtx
	moveq	r0, #3	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L42:
	ldr	r2, [r3, #16]	@ temp.1142, s_pstVfmwChan
	cmp	r2, #0	@ temp.1142,
	beq	.L43	@,
	add	r2, r2, #250880	@ tmp165, temp.1142,
	add	ip, r2, #616	@ tmp165, tmp165,
	cmp	ip, r0	@ tmp165, pCtx
	moveq	r0, #4	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L43:
	ldr	r2, [r3, #20]	@ temp.1144, s_pstVfmwChan
	cmp	r2, #0	@ temp.1144,
	beq	.L44	@,
	add	ip, r2, #250880	@ tmp168, temp.1144,
	add	r1, ip, #616	@ tmp168, tmp168,
	cmp	r1, r0	@ tmp168, pCtx
	moveq	r0, #5	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L44:
	ldr	r2, [r3, #24]	@ temp.1146, s_pstVfmwChan
	cmp	r2, #0	@ temp.1146,
	beq	.L45	@,
	add	r1, r2, #250880	@ tmp171, temp.1146,
	add	r2, r1, #616	@ tmp171, tmp171,
	cmp	r2, r0	@ tmp171, pCtx
	moveq	r0, #6	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L45:
	ldr	r2, [r3, #28]	@ temp.1148, s_pstVfmwChan
	cmp	r2, #0	@ temp.1148,
	beq	.L46	@,
	add	r2, r2, #250880	@ tmp174, temp.1148,
	add	ip, r2, #616	@ tmp174, tmp174,
	cmp	ip, r0	@ tmp174, pCtx
	moveq	r0, #7	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L46:
	ldr	r2, [r3, #32]	@ temp.1150, s_pstVfmwChan
	cmp	r2, #0	@ temp.1150,
	beq	.L47	@,
	add	ip, r2, #250880	@ tmp177, temp.1150,
	add	r1, ip, #616	@ tmp177, tmp177,
	cmp	r1, r0	@ tmp177, pCtx
	moveq	r0, #8	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L47:
	ldr	r2, [r3, #36]	@ temp.1152, s_pstVfmwChan
	cmp	r2, #0	@ temp.1152,
	beq	.L48	@,
	add	r1, r2, #250880	@ tmp180, temp.1152,
	add	r2, r1, #616	@ tmp180, tmp180,
	cmp	r2, r0	@ tmp180, pCtx
	moveq	r0, #9	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L48:
	ldr	r2, [r3, #40]	@ temp.1154, s_pstVfmwChan
	cmp	r2, #0	@ temp.1154,
	beq	.L49	@,
	add	r2, r2, #250880	@ tmp183, temp.1154,
	add	ip, r2, #616	@ tmp183, tmp183,
	cmp	ip, r0	@ tmp183, pCtx
	moveq	r0, #10	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L49:
	ldr	r2, [r3, #44]	@ temp.1156, s_pstVfmwChan
	cmp	r2, #0	@ temp.1156,
	beq	.L50	@,
	add	ip, r2, #250880	@ tmp186, temp.1156,
	add	r1, ip, #616	@ tmp186, tmp186,
	cmp	r1, r0	@ tmp186, pCtx
	moveq	r0, #11	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L50:
	ldr	r2, [r3, #48]	@ temp.1158, s_pstVfmwChan
	cmp	r2, #0	@ temp.1158,
	beq	.L51	@,
	add	r1, r2, #250880	@ tmp189, temp.1158,
	add	r2, r1, #616	@ tmp189, tmp189,
	cmp	r2, r0	@ tmp189, pCtx
	moveq	r0, #12	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L51:
	ldr	r2, [r3, #52]	@ temp.1160, s_pstVfmwChan
	cmp	r2, #0	@ temp.1160,
	beq	.L52	@,
	add	r2, r2, #250880	@ tmp192, temp.1160,
	add	ip, r2, #616	@ tmp192, tmp192,
	cmp	ip, r0	@ tmp192, pCtx
	moveq	r0, #13	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L52:
	ldr	r2, [r3, #56]	@ temp.1162, s_pstVfmwChan
	cmp	r2, #0	@ temp.1162,
	beq	.L53	@,
	add	ip, r2, #250880	@ tmp195, temp.1162,
	add	r1, ip, #616	@ tmp195, tmp195,
	cmp	r1, r0	@ tmp195, pCtx
	moveq	r0, #14	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L53:
	ldr	r3, [r3, #60]	@ D.42352, s_pstVfmwChan
	cmp	r3, #0	@ D.42352,
	beq	.L54	@,
	add	r2, r3, #250880	@ tmp198, D.42352,
	add	r3, r2, #616	@ tmp198, tmp198,
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
	ldr	r2, [r3, #0]	@ temp.1188, s_pstVfmwChan
	cmp	r2, #0	@ temp.1188,
	beq	.L57	@,
	ldr	r1, [r2, #216]	@ temp.1190, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1190
	bge	.L58	@,
.L60:
	ldr	r1, [r2, #232]	@ temp.1189, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1189
	blt	.L57	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp185, temp.1189, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp185
	blt	.L106	@,
.L57:
	ldr	r2, [r3, #4]	@ temp.1195, s_pstVfmwChan
	cmp	r2, #0	@ temp.1195,
	beq	.L61	@,
	ldr	r1, [r2, #216]	@ temp.1196, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1196
	bge	.L62	@,
.L63:
	ldr	r1, [r2, #232]	@ temp.1197, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1197
	blt	.L61	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp190, temp.1197, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp190
	blt	.L108	@,
.L61:
	ldr	r2, [r3, #8]	@ temp.1202, s_pstVfmwChan
	cmp	r2, #0	@ temp.1202,
	beq	.L64	@,
	ldr	r1, [r2, #216]	@ temp.1203, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1203
	bge	.L65	@,
.L66:
	ldr	r1, [r2, #232]	@ temp.1204, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1204
	blt	.L64	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp195, temp.1204, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp195
	blt	.L121	@,
.L64:
	ldr	r2, [r3, #12]	@ temp.1209, s_pstVfmwChan
	cmp	r2, #0	@ temp.1209,
	beq	.L67	@,
	ldr	r1, [r2, #216]	@ temp.1210, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1210
	bge	.L68	@,
.L69:
	ldr	r1, [r2, #232]	@ temp.1211, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1211
	blt	.L67	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp200, temp.1211, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp200
	blt	.L120	@,
.L67:
	ldr	r2, [r3, #16]	@ temp.1216, s_pstVfmwChan
	cmp	r2, #0	@ temp.1216,
	beq	.L70	@,
	ldr	r1, [r2, #216]	@ temp.1217, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1217
	bge	.L71	@,
.L72:
	ldr	r1, [r2, #232]	@ temp.1218, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1218
	blt	.L70	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp205, temp.1218, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp205
	blt	.L119	@,
.L70:
	ldr	r2, [r3, #20]	@ temp.1223, s_pstVfmwChan
	cmp	r2, #0	@ temp.1223,
	beq	.L73	@,
	ldr	r1, [r2, #216]	@ temp.1224, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1224
	bge	.L74	@,
.L75:
	ldr	r1, [r2, #232]	@ temp.1225, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1225
	blt	.L73	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp210, temp.1225, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp210
	blt	.L118	@,
.L73:
	ldr	r2, [r3, #24]	@ temp.1230, s_pstVfmwChan
	cmp	r2, #0	@ temp.1230,
	beq	.L76	@,
	ldr	r1, [r2, #216]	@ temp.1231, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1231
	bge	.L77	@,
.L78:
	ldr	r1, [r2, #232]	@ temp.1232, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1232
	blt	.L76	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp215, temp.1232, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp215
	blt	.L117	@,
.L76:
	ldr	r2, [r3, #28]	@ temp.1237, s_pstVfmwChan
	cmp	r2, #0	@ temp.1237,
	beq	.L79	@,
	ldr	r1, [r2, #216]	@ temp.1238, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1238
	bge	.L80	@,
.L81:
	ldr	r1, [r2, #232]	@ temp.1239, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1239
	blt	.L79	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp220, temp.1239, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp220
	blt	.L116	@,
.L79:
	ldr	r2, [r3, #32]	@ temp.1244, s_pstVfmwChan
	cmp	r2, #0	@ temp.1244,
	beq	.L82	@,
	ldr	r1, [r2, #216]	@ temp.1245, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1245
	bge	.L83	@,
.L84:
	ldr	r1, [r2, #232]	@ temp.1246, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1246
	blt	.L82	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp225, temp.1246, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp225
	blt	.L115	@,
.L82:
	ldr	r2, [r3, #36]	@ temp.1251, s_pstVfmwChan
	cmp	r2, #0	@ temp.1251,
	beq	.L85	@,
	ldr	r1, [r2, #216]	@ temp.1252, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1252
	bge	.L86	@,
.L87:
	ldr	r1, [r2, #232]	@ temp.1253, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1253
	blt	.L85	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp230, temp.1253, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp230
	blt	.L114	@,
.L85:
	ldr	r2, [r3, #40]	@ temp.1258, s_pstVfmwChan
	cmp	r2, #0	@ temp.1258,
	beq	.L88	@,
	ldr	r1, [r2, #216]	@ temp.1259, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1259
	bge	.L89	@,
.L90:
	ldr	r1, [r2, #232]	@ temp.1260, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1260
	blt	.L88	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp235, temp.1260, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp235
	blt	.L113	@,
.L88:
	ldr	r2, [r3, #44]	@ temp.1265, s_pstVfmwChan
	cmp	r2, #0	@ temp.1265,
	beq	.L91	@,
	ldr	r1, [r2, #216]	@ temp.1266, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1266
	bge	.L92	@,
.L93:
	ldr	r1, [r2, #232]	@ temp.1267, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1267
	blt	.L91	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp240, temp.1267, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp240
	blt	.L112	@,
.L91:
	ldr	r2, [r3, #48]	@ temp.1272, s_pstVfmwChan
	cmp	r2, #0	@ temp.1272,
	beq	.L94	@,
	ldr	r1, [r2, #216]	@ temp.1273, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1273
	bge	.L95	@,
.L96:
	ldr	r1, [r2, #232]	@ temp.1274, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1274
	blt	.L94	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp245, temp.1274, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp245
	blt	.L111	@,
.L94:
	ldr	r2, [r3, #52]	@ temp.1279, s_pstVfmwChan
	cmp	r2, #0	@ temp.1279,
	beq	.L97	@,
	ldr	r1, [r2, #216]	@ temp.1280, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1280
	bge	.L98	@,
.L99:
	ldr	r1, [r2, #232]	@ temp.1281, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1281
	blt	.L97	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp250, temp.1281, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp250
	blt	.L110	@,
.L97:
	ldr	r2, [r3, #56]	@ temp.1286, s_pstVfmwChan
	cmp	r2, #0	@ temp.1286,
	beq	.L100	@,
	ldr	r1, [r2, #216]	@ temp.1287, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1287
	bge	.L101	@,
.L102:
	ldr	r1, [r2, #232]	@ temp.1288, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r1	@ PhyAddr, temp.1288
	blt	.L100	@,
	ldr	r2, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r1, r1, r2	@ tmp255, temp.1288, <variable>.stChanMem_scd.Length
	cmp	r0, r1	@ PhyAddr, tmp255
	blt	.L109	@,
.L100:
	ldr	r3, [r3, #60]	@ D.42368, s_pstVfmwChan
	cmp	r3, #0	@ D.42368,
	beq	.L103	@,
	ldr	r2, [r3, #216]	@ D.42371, <variable>.stChanMem_vdh.PhyAddr
	cmp	r2, r0	@ D.42371, PhyAddr
	bgt	.L104	@,
	ldr	r1, [r3, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r2, r2, r1	@ tmp260, D.42371, <variable>.stChanMem_vdh.Length
	cmp	r0, r2	@ PhyAddr, tmp260
	blt	.L107	@,
.L104:
	ldr	r2, [r3, #232]	@ D.42379, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, r2	@ PhyAddr, D.42379
	blt	.L103	@,
	ldr	r3, [r3, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	ip, r2, r3	@ tmp262, D.42379, <variable>.stChanMem_scd.Length
	cmp	r0, ip	@ PhyAddr, tmp262
	blt	.L107	@,
.L103:
	mvn	r0, #0	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L58:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp187, temp.1190, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp187
	bge	.L60	@,
.L106:
	mov	r0, #0	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L62:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp192, temp.1196, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp192
	bge	.L63	@,
.L108:
	mov	r0, #1	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L65:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp197, temp.1203, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp197
	bge	.L66	@,
.L121:
	mov	r0, #2	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L68:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp202, temp.1210, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp202
	bge	.L69	@,
.L120:
	mov	r0, #3	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L71:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp207, temp.1217, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp207
	bge	.L72	@,
.L119:
	mov	r0, #4	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L74:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp212, temp.1224, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp212
	bge	.L75	@,
.L118:
	mov	r0, #5	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L77:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp217, temp.1231, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp217
	bge	.L78	@,
.L117:
	mov	r0, #6	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L80:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp222, temp.1238, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp222
	bge	.L81	@,
.L116:
	mov	r0, #7	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L83:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp227, temp.1245, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp227
	bge	.L84	@,
.L115:
	mov	r0, #8	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L86:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp232, temp.1252, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp232
	bge	.L87	@,
.L114:
	mov	r0, #9	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L89:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp237, temp.1259, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp237
	bge	.L90	@,
.L113:
	mov	r0, #10	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L92:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp242, temp.1266, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp242
	bge	.L93	@,
.L112:
	mov	r0, #11	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L95:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp247, temp.1273, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp247
	bge	.L96	@,
.L111:
	mov	r0, #12	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L98:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp252, temp.1280, <variable>.stChanMem_vdh.Length
	cmp	r0, r1	@ PhyAddr, tmp252
	bge	.L99	@,
.L110:
	mov	r0, #13	@ i,
	ldmfd	sp, {fp, sp, pc}	@
.L101:
	ldr	ip, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	add	r1, r1, ip	@ tmp257, temp.1287, <variable>.stChanMem_vdh.Length
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
	ldr	r3, [r3, r0, asl #2]	@ D.42591, s_pstVfmwChan
	cmp	r3, #0	@ D.42591,
	beq	.L123	@,
	ldr	r2, [r3, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
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
	add	r0, r3, #250880	@ pstVoQue, D.42591,
	add	r0, r0, #624	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L123:
	mov	r0, #0	@ pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L126:
	movw	ip, #:lower16:274104	@ pstVoQue,
	movt	ip, #:upper16:274104	@ pstVoQue,
	add	r0, r3, ip	@ pstVoQue, D.42591, pstVoQue
	ldmfd	sp, {fp, sp, pc}	@
.L127:
	movw	r1, #:lower16:331496	@ pstVoQue,
	movt	r1, #:upper16:331496	@ pstVoQue,
	add	r0, r3, r1	@ pstVoQue, D.42591, pstVoQue
	ldmfd	sp, {fp, sp, pc}	@
.L128:
	add	r1, r3, #274432	@ pstVoQue, D.42591,
	add	r0, r1, #2544	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L129:
	movw	ip, #:lower16:284792	@ pstVoQue,
	movt	ip, #:upper16:284792	@ pstVoQue,
	add	r0, r3, ip	@ pstVoQue, D.42591, pstVoQue
	ldmfd	sp, {fp, sp, pc}	@
.L125:
	add	r2, r3, #364544	@ pstVoQue, D.42591,
	add	r0, r2, #920	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L136:
	movw	r0, #:lower16:2384224	@ pstVoQue,
	movt	r0, #:upper16:2384224	@ pstVoQue,
	add	r0, r3, r0	@ pstVoQue, D.42591, pstVoQue
	ldmfd	sp, {fp, sp, pc}	@
.L134:
	add	ip, r3, #259072	@ pstVoQue, D.42591,
	add	r0, ip, #592	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L135:
	add	r2, r3, #251904	@ pstVoQue, D.42591,
	add	r0, r2, #176	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L130:
	movw	r2, #:lower16:267576	@ pstVoQue,
	movt	r2, #:upper16:267576	@ pstVoQue,
	add	r0, r3, r2	@ pstVoQue, D.42591, pstVoQue
	ldmfd	sp, {fp, sp, pc}	@
.L131:
	add	r0, r3, #294912	@ pstVoQue, D.42591,
	add	r0, r0, #2208	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L132:
	add	r1, r3, #294912	@ pstVoQue, D.42591,
	add	r0, r1, #2192	@ pstVoQue, pstVoQue,
	ldmfd	sp, {fp, sp, pc}	@
.L133:
	add	r0, r3, #262144	@ pstVoQue, D.42591,
	add	r0, r0, #2000	@ pstVoQue, pstVoQue,
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
	add	r0, r0, r5	@ ivtmp.1343, str, i
	mov	ip, #0	@ dat,
	ldrb	r3, [r0, #0]	@ zero_extendqisi2	@ D.43935,* ivtmp.1343
	cmp	r3, #31	@ D.43935,
	bls	.L144	@,
	cmp	r4, #16	@ weight,
	beq	.L173	@,
.L154:
	sub	ip, r3, #48	@ tmp194, D.43935,
	uxtb	r3, ip	@ tmp195, tmp194
	cmp	r3, #9	@ tmp195,
	bhi	.L174	@,
.L175:
	mov	r2, #1	@ tmp185,
	cmp	r2, #0	@ tmp185,
	add	r0, r0, r2	@ ivtmp.1343, ivtmp.1343,
	add	r5, r5, r2	@ i, i,
	beq	.L151	@,
	ldrb	r3, [r0, #0]	@ zero_extendqisi2	@ D.43935,* ivtmp.1343
	cmp	r3, #31	@ D.43935,
	bls	.L144	@,
	cmp	r4, #16	@ weight,
	beq	.L177	@,
.L159:
	sub	r3, r3, #48	@ tmp199, D.43935,
	uxtb	r2, r3	@ tmp200, tmp199
	cmp	r2, #9	@ tmp200,
	bhi	.L174	@,
.L178:
	add	r5, r5, #1	@ i, i,
	add	r0, r0, #1	@ ivtmp.1343, ivtmp.1343,
	cmp	r5, #9	@ i,
	mla	ip, r4, ip, r3	@ dat, weight, dat, d
	bls	.L151	@,
.L144:
	mov	r0, #0	@ D.43955,
	str	ip, [r1, #0]	@ dat,* data
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L146:
	cmp	r3, #64	@ D.43935,
	bhi	.L147	@,
.L145:
	sub	r3, r3, #48	@ tmp181, D.43935,
	uxtb	r2, r3	@ tmp182, tmp181
	cmp	r2, #9	@ tmp182,
	bhi	.L174	@,
.L148:
	ldrb	r2, [r0, #1]	@ zero_extendqisi2	@ D.43935,
	add	r5, r5, #1	@ tmp186, i,
	mla	ip, r4, ip, r3	@ dat, weight, dat, d
	cmp	r2, #31	@ D.43935,
	add	r0, r0, #1	@ tmp187, ivtmp.1343,
	bls	.L144	@,
	cmp	r4, #16	@ weight,
	beq	.L180	@,
.L165:
	sub	r2, r2, #48	@ tmp203, D.43935,
	uxtb	r3, r2	@ tmp204, tmp203
	cmp	r3, #9	@ tmp204,
	bhi	.L174	@,
.L181:
	add	r5, r5, #1	@ i, tmp186,
	add	r0, r0, #1	@ ivtmp.1343, tmp187,
	cmp	r5, #9	@ i,
	mla	ip, r4, ip, r2	@ dat, weight, dat, d
	bhi	.L144	@,
.L151:
	ldrb	r3, [r0, #0]	@ zero_extendqisi2	@ D.43935,* ivtmp.1343
	cmp	r3, #31	@ D.43935,
	bls	.L144	@,
	cmp	r4, #16	@ weight,
	bne	.L145	@,
	cmp	r3, #96	@ D.43935,
	bls	.L146	@,
	cmp	r3, #102	@ D.43935,
	subls	r3, r3, #87	@ d, D.43935,
	bls	.L148	@,
.L147:
	cmp	r3, #70	@ D.43935,
	subls	r3, r3, #55	@ d, D.43935,
	bls	.L148	@,
	b	.L145	@
.L180:
	cmp	r2, #96	@ D.43935,
	bls	.L167	@,
	cmp	r2, #102	@ D.43935,
	bhi	.L168	@,
	sub	r2, r2, #87	@ d, D.43935,
	b	.L181	@
.L167:
	cmp	r2, #64	@ D.43935,
	bls	.L165	@,
.L168:
	cmp	r2, #70	@ D.43935,
	subls	r2, r2, #55	@ d, D.43935,
	bls	.L181	@,
	b	.L165	@
.L184:
	ldrb	r2, [r0, #1]	@ zero_extendqisi2	@ D.43929,
	cmp	r2, #120	@ D.43929,
	cmpne	r2, #88	@, D.43929,
	moveq	r4, #16	@ weight,
	moveq	r5, #2	@ i,
	beq	.L143	@,
	b	.L142	@
.L173:
	cmp	r3, #96	@ D.43935,
	bls	.L156	@,
	cmp	r3, #102	@ D.43935,
	bhi	.L157	@,
	sub	ip, r3, #87	@ d, D.43935,
	b	.L175	@
.L156:
	cmp	r3, #64	@ D.43935,
	bls	.L154	@,
.L157:
	cmp	r3, #70	@ D.43935,
	subls	ip, r3, #55	@ d, D.43935,
	bls	.L175	@,
	b	.L154	@
.L177:
	cmp	r3, #96	@ D.43935,
	bls	.L161	@,
	cmp	r3, #102	@ D.43935,
	bhi	.L162	@,
	sub	r3, r3, #87	@ d, D.43935,
	b	.L178	@
.L161:
	cmp	r3, #64	@ D.43935,
	bls	.L159	@,
.L162:
	cmp	r3, #70	@ D.43935,
	subls	r3, r3, #55	@ d, D.43935,
	bhi	.L159	@,
	add	r5, r5, #1	@ i, i,
	add	r0, r0, #1	@ ivtmp.1343, ivtmp.1343,
	cmp	r5, #9	@ i,
	mla	ip, r4, ip, r3	@ dat, weight, dat, d
	bls	.L151	@,
	b	.L144	@
.L174:
	mvn	r0, #0	@ D.43955,
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
	ldr	ip, [ip, #20]	@ D.44132, <variable>.write
	cmp	ip, #0	@ D.44132,
	mvneq	r0, #37	@ D.44135,
	ldmeqfd	sp, {fp, sp, pc}	@
	blx	ip	@ D.44132
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
	movw	r3, #:lower16:249192	@ tmp138,
	movt	r3, #:upper16:249192	@ tmp138,
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
	movw	r3, #:lower16:249200	@ tmp140,
	movt	r3, #:upper16:249200	@ tmp140,
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
	movw	ip, #:lower16:249208	@ tmp158,
	movt	ip, #:upper16:249208	@ tmp158,
	ldr	r4, [r3, r0, asl #2]	@ tmp136, s_pstVfmwChan
	movw	r2, #:lower16:249220	@ tmp159,
	movt	r2, #:upper16:249220	@ tmp159,
	str	r5, [r4, #272]	@ <variable>.Length, <variable>.s32VdmChanMemSize
	ldr	r4, [r3, r0, asl #2]	@ tmp139, s_pstVfmwChan
	ldr	r5, [r1, #0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	r5, [r4, #268]	@ <variable>.PhyAddr, <variable>.s32VdmChanMemAddr
	ldr	r4, [r3, r0, asl #2]	@ tmp142, s_pstVfmwChan
	ldr	r5, [r1, #0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	r5, [r4, #216]	@ <variable>.PhyAddr, <variable>.stChanMem_vdh.PhyAddr
	ldr	r4, [r3, r0, asl #2]	@ tmp145, s_pstVfmwChan
	ldr	r5, [r1, #4]	@ <variable>.VirAddr, <variable>.VirAddr
	str	r5, [r4, #212]	@ <variable>.VirAddr, <variable>.stChanMem_vdh.VirAddr
	ldr	r4, [r3, r0, asl #2]	@ tmp148, s_pstVfmwChan
	ldr	r5, [r1, #8]	@ <variable>.Length, <variable>.Length
	str	r5, [r4, #220]	@ <variable>.Length, <variable>.stChanMem_vdh.Length
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
	movw	r3, #:lower16:251488	@ tmp140,
	movt	r3, #:upper16:251488	@ tmp140,
	ldr	r0, [r2, r0, asl #2]	@ D.44807, s_pstVfmwChan
	ldr	r3, [r0, r3]	@ <variable>.stSynCtx.eVidStd, <variable>.stSynCtx.eVidStd
	cmp	r3, #2	@ <variable>.stSynCtx.eVidStd,
	beq	.L198	@,
	cmp	r3, #16	@ <variable>.stSynCtx.eVidStd,
	beq	.L199	@,
	cmp	r3, #0	@ <variable>.stSynCtx.eVidStd,
	movne	r0, #0	@ uImageHeight,
	ldmnefd	sp, {fp, sp, pc}	@
	add	r1, r0, #250880	@, D.44807,
	add	r0, r1, #616	@,,
	bl	H264DEC_GetImageHeight	@
	ldmfd	sp, {fp, sp, pc}	@
.L199:
	add	ip, r0, #250880	@, D.44807,
	add	r0, ip, #616	@,,
	bl	HEVCDEC_GetImageHeight	@
	ldmfd	sp, {fp, sp, pc}	@
.L198:
	add	r0, r0, #250880	@, D.44807,
	add	r0, r0, #616	@,,
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
	movw	r3, #:lower16:251488	@ tmp140,
	movt	r3, #:upper16:251488	@ tmp140,
	ldr	r0, [r2, r0, asl #2]	@ D.44788, s_pstVfmwChan
	ldr	r3, [r0, r3]	@ <variable>.stSynCtx.eVidStd, <variable>.stSynCtx.eVidStd
	cmp	r3, #2	@ <variable>.stSynCtx.eVidStd,
	beq	.L205	@,
	cmp	r3, #16	@ <variable>.stSynCtx.eVidStd,
	beq	.L206	@,
	cmp	r3, #0	@ <variable>.stSynCtx.eVidStd,
	movne	r0, #0	@ uImageWidth,
	ldmnefd	sp, {fp, sp, pc}	@
	add	r1, r0, #250880	@, D.44788,
	add	r0, r1, #616	@,,
	bl	H264DEC_GetImageWidth	@
	ldmfd	sp, {fp, sp, pc}	@
.L206:
	add	ip, r0, #250880	@, D.44788,
	add	r0, ip, #616	@,,
	bl	HEVCDEC_GetImageWidth	@
	ldmfd	sp, {fp, sp, pc}	@
.L205:
	add	r0, r0, #250880	@, D.44788,
	add	r0, r0, #616	@,,
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
	stmfd	sp!, {fp, ip, lr, pc}	@,
	.pad #4
	.save {fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r3, #:lower16:.LANCHOR0	@ tmp776,
	movt	r3, #:upper16:.LANCHOR0	@ tmp776,
	ldr	r2, [r3, #0]	@ temp.1521, s_pstVfmwChan
	cmp	r2, #0	@ temp.1521,
	beq	.L210	@,
	ldr	r1, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1522, <variable>.eVidStd
	cmp	r1, #1	@ <variable>.s32IsOpen,
	beq	.L229	@,
.L210:
	ldr	r2, [r3, #4]	@ temp.1538, s_pstVfmwChan
	cmp	r2, #0	@ temp.1538,
	beq	.L212	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1539, <variable>.eVidStd
	cmp	ip, #1	@ <variable>.s32IsOpen,
	beq	.L230	@,
.L212:
	ldr	r2, [r3, #8]	@ temp.1557, s_pstVfmwChan
	cmp	r2, #0	@ temp.1557,
	beq	.L213	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1558, <variable>.eVidStd
	cmp	ip, #1	@ <variable>.s32IsOpen,
	beq	.L231	@,
.L213:
	ldr	r2, [r3, #12]	@ temp.1576, s_pstVfmwChan
	cmp	r2, #0	@ temp.1576,
	beq	.L214	@,
	ldr	r1, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1577, <variable>.eVidStd
	cmp	r1, #1	@ <variable>.s32IsOpen,
	beq	.L232	@,
.L214:
	ldr	r2, [r3, #16]	@ temp.1595, s_pstVfmwChan
	cmp	r2, #0	@ temp.1595,
	beq	.L215	@,
	ldr	r1, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1596, <variable>.eVidStd
	cmp	r1, #1	@ <variable>.s32IsOpen,
	beq	.L233	@,
.L215:
	ldr	r2, [r3, #20]	@ temp.1614, s_pstVfmwChan
	cmp	r2, #0	@ temp.1614,
	beq	.L216	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1615, <variable>.eVidStd
	cmp	ip, #1	@ <variable>.s32IsOpen,
	beq	.L234	@,
.L216:
	ldr	r2, [r3, #24]	@ temp.1633, s_pstVfmwChan
	cmp	r2, #0	@ temp.1633,
	beq	.L217	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1634, <variable>.eVidStd
	cmp	ip, #1	@ <variable>.s32IsOpen,
	beq	.L235	@,
.L217:
	ldr	r2, [r3, #28]	@ temp.1652, s_pstVfmwChan
	cmp	r2, #0	@ temp.1652,
	beq	.L218	@,
	ldr	r1, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1653, <variable>.eVidStd
	cmp	r1, #1	@ <variable>.s32IsOpen,
	beq	.L236	@,
.L218:
	ldr	r2, [r3, #32]	@ temp.1671, s_pstVfmwChan
	cmp	r2, #0	@ temp.1671,
	beq	.L219	@,
	ldr	r1, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1672, <variable>.eVidStd
	cmp	r1, #1	@ <variable>.s32IsOpen,
	beq	.L237	@,
.L219:
	ldr	r2, [r3, #36]	@ temp.1690, s_pstVfmwChan
	cmp	r2, #0	@ temp.1690,
	beq	.L220	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1691, <variable>.eVidStd
	cmp	ip, #1	@ <variable>.s32IsOpen,
	beq	.L238	@,
.L220:
	ldr	r2, [r3, #40]	@ temp.1709, s_pstVfmwChan
	cmp	r2, #0	@ temp.1709,
	beq	.L221	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1710, <variable>.eVidStd
	cmp	ip, #1	@ <variable>.s32IsOpen,
	beq	.L239	@,
.L221:
	ldr	r2, [r3, #44]	@ temp.1728, s_pstVfmwChan
	cmp	r2, #0	@ temp.1728,
	beq	.L222	@,
	ldr	r1, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1729, <variable>.eVidStd
	cmp	r1, #1	@ <variable>.s32IsOpen,
	beq	.L240	@,
.L222:
	ldr	r2, [r3, #48]	@ temp.1747, s_pstVfmwChan
	cmp	r2, #0	@ temp.1747,
	beq	.L223	@,
	ldr	r1, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1748, <variable>.eVidStd
	cmp	r1, #1	@ <variable>.s32IsOpen,
	beq	.L241	@,
.L223:
	ldr	r2, [r3, #52]	@ temp.1766, s_pstVfmwChan
	cmp	r2, #0	@ temp.1766,
	beq	.L224	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1767, <variable>.eVidStd
	cmp	ip, #1	@ <variable>.s32IsOpen,
	beq	.L242	@,
.L224:
	ldr	r2, [r3, #56]	@ temp.1785, s_pstVfmwChan
	cmp	r2, #0	@ temp.1785,
	beq	.L225	@,
	ldr	ip, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r0, [r2, #1032]	@ eVidStd.1786, <variable>.eVidStd
	cmp	ip, #1	@ <variable>.s32IsOpen,
	beq	.L243	@,
.L225:
	ldr	r3, [r3, #60]	@ D.44333, s_pstVfmwChan
	cmp	r3, #0	@ D.44333,
	beq	.L226	@,
	ldr	r0, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	ldr	r1, [r3, #1032]	@ eVidStd, <variable>.eVidStd
	cmp	r0, #1	@ <variable>.s32IsOpen,
	beq	.L244	@,
.L226:
	movw	lr, #:lower16:g_vdm_hal_fun_ptr	@ tmp774,
	movt	lr, #:upper16:g_vdm_hal_fun_ptr	@ tmp774,
	ldr	r3, [lr, #4]	@ D.44365, g_vdm_hal_fun_ptr.pfun_VDMDRV_CloseHardware
	cmp	r3, #0	@ D.44365,
	beq	.L245	@,
	mov	r0, #0	@,
	blx	r3	@ D.44365
	ldmfd	sp, {fp, sp, pc}	@
.L229:
	ldr	r2, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r2, #1	@ <variable>.s32IsRun,
	bne	.L210	@,
	cmp	r0, #5	@ eVidStd.1522,
	cmpne	r0, #3	@, eVidStd.1522,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1522,
	cmpne	r0, #8	@, eVidStd.1522,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1522,
	cmpne	r0, #10	@, eVidStd.1522,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1522,
	cmpne	r0, #12	@, eVidStd.1522,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1522,
	cmpne	r0, #15	@, eVidStd.1522,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1522,
	bne	.L210	@,
	ldmfd	sp, {fp, sp, pc}	@
.L230:
	ldr	r1, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r1, #1	@ <variable>.s32IsRun,
	bne	.L212	@,
	cmp	r0, #5	@ eVidStd.1539,
	cmpne	r0, #3	@, eVidStd.1539,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1539,
	cmpne	r0, #8	@, eVidStd.1539,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1539,
	cmpne	r0, #10	@, eVidStd.1539,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1539,
	cmpne	r0, #12	@, eVidStd.1539,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1539,
	cmpne	r0, #15	@, eVidStd.1539,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1539,
	bne	.L212	@,
	ldmfd	sp, {fp, sp, pc}	@
.L231:
	ldr	r2, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r2, #1	@ <variable>.s32IsRun,
	bne	.L213	@,
	cmp	r0, #5	@ eVidStd.1558,
	cmpne	r0, #3	@, eVidStd.1558,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1558,
	cmpne	r0, #8	@, eVidStd.1558,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1558,
	cmpne	r0, #10	@, eVidStd.1558,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1558,
	cmpne	r0, #12	@, eVidStd.1558,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1558,
	cmpne	r0, #15	@, eVidStd.1558,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1558,
	bne	.L213	@,
	ldmfd	sp, {fp, sp, pc}	@
.L232:
	ldr	ip, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	ip, #1	@ <variable>.s32IsRun,
	bne	.L214	@,
	cmp	r0, #5	@ eVidStd.1577,
	cmpne	r0, #3	@, eVidStd.1577,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1577,
	cmpne	r0, #8	@, eVidStd.1577,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1577,
	cmpne	r0, #10	@, eVidStd.1577,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1577,
	cmpne	r0, #12	@, eVidStd.1577,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1577,
	cmpne	r0, #15	@, eVidStd.1577,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1577,
	bne	.L214	@,
	ldmfd	sp, {fp, sp, pc}	@
.L233:
	ldr	r2, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r2, #1	@ <variable>.s32IsRun,
	bne	.L215	@,
	cmp	r0, #5	@ eVidStd.1596,
	cmpne	r0, #3	@, eVidStd.1596,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1596,
	cmpne	r0, #8	@, eVidStd.1596,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1596,
	cmpne	r0, #10	@, eVidStd.1596,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1596,
	cmpne	r0, #12	@, eVidStd.1596,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1596,
	cmpne	r0, #15	@, eVidStd.1596,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1596,
	bne	.L215	@,
	ldmfd	sp, {fp, sp, pc}	@
.L234:
	ldr	r1, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r1, #1	@ <variable>.s32IsRun,
	bne	.L216	@,
	cmp	r0, #5	@ eVidStd.1615,
	cmpne	r0, #3	@, eVidStd.1615,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1615,
	cmpne	r0, #8	@, eVidStd.1615,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1615,
	cmpne	r0, #10	@, eVidStd.1615,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1615,
	cmpne	r0, #12	@, eVidStd.1615,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1615,
	cmpne	r0, #15	@, eVidStd.1615,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1615,
	bne	.L216	@,
	ldmfd	sp, {fp, sp, pc}	@
.L235:
	ldr	r2, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r2, #1	@ <variable>.s32IsRun,
	bne	.L217	@,
	cmp	r0, #5	@ eVidStd.1634,
	cmpne	r0, #3	@, eVidStd.1634,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1634,
	cmpne	r0, #8	@, eVidStd.1634,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1634,
	cmpne	r0, #10	@, eVidStd.1634,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1634,
	cmpne	r0, #12	@, eVidStd.1634,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1634,
	cmpne	r0, #15	@, eVidStd.1634,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1634,
	bne	.L217	@,
	ldmfd	sp, {fp, sp, pc}	@
.L236:
	ldr	ip, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	ip, #1	@ <variable>.s32IsRun,
	bne	.L218	@,
	cmp	r0, #5	@ eVidStd.1653,
	cmpne	r0, #3	@, eVidStd.1653,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1653,
	cmpne	r0, #8	@, eVidStd.1653,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1653,
	cmpne	r0, #10	@, eVidStd.1653,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1653,
	cmpne	r0, #12	@, eVidStd.1653,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1653,
	cmpne	r0, #15	@, eVidStd.1653,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1653,
	bne	.L218	@,
	ldmfd	sp, {fp, sp, pc}	@
.L237:
	ldr	r2, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r2, #1	@ <variable>.s32IsRun,
	bne	.L219	@,
	cmp	r0, #5	@ eVidStd.1672,
	cmpne	r0, #3	@, eVidStd.1672,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1672,
	cmpne	r0, #8	@, eVidStd.1672,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1672,
	cmpne	r0, #10	@, eVidStd.1672,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1672,
	cmpne	r0, #12	@, eVidStd.1672,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1672,
	cmpne	r0, #15	@, eVidStd.1672,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1672,
	bne	.L219	@,
	ldmfd	sp, {fp, sp, pc}	@
.L238:
	ldr	r1, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r1, #1	@ <variable>.s32IsRun,
	bne	.L220	@,
	cmp	r0, #5	@ eVidStd.1691,
	cmpne	r0, #3	@, eVidStd.1691,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1691,
	cmpne	r0, #8	@, eVidStd.1691,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1691,
	cmpne	r0, #10	@, eVidStd.1691,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1691,
	cmpne	r0, #12	@, eVidStd.1691,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1691,
	cmpne	r0, #15	@, eVidStd.1691,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1691,
	bne	.L220	@,
	ldmfd	sp, {fp, sp, pc}	@
.L239:
	ldr	r2, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r2, #1	@ <variable>.s32IsRun,
	bne	.L221	@,
	cmp	r0, #5	@ eVidStd.1710,
	cmpne	r0, #3	@, eVidStd.1710,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1710,
	cmpne	r0, #8	@, eVidStd.1710,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1710,
	cmpne	r0, #10	@, eVidStd.1710,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1710,
	cmpne	r0, #12	@, eVidStd.1710,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1710,
	cmpne	r0, #15	@, eVidStd.1710,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1710,
	bne	.L221	@,
	ldmfd	sp, {fp, sp, pc}	@
.L240:
	ldr	ip, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	ip, #1	@ <variable>.s32IsRun,
	bne	.L222	@,
	cmp	r0, #5	@ eVidStd.1729,
	cmpne	r0, #3	@, eVidStd.1729,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1729,
	cmpne	r0, #8	@, eVidStd.1729,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1729,
	cmpne	r0, #10	@, eVidStd.1729,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1729,
	cmpne	r0, #12	@, eVidStd.1729,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1729,
	cmpne	r0, #15	@, eVidStd.1729,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1729,
	bne	.L222	@,
	ldmfd	sp, {fp, sp, pc}	@
.L241:
	ldr	r2, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r2, #1	@ <variable>.s32IsRun,
	bne	.L223	@,
	cmp	r0, #5	@ eVidStd.1748,
	cmpne	r0, #3	@, eVidStd.1748,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1748,
	cmpne	r0, #8	@, eVidStd.1748,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1748,
	cmpne	r0, #10	@, eVidStd.1748,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1748,
	cmpne	r0, #12	@, eVidStd.1748,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1748,
	cmpne	r0, #15	@, eVidStd.1748,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1748,
	bne	.L223	@,
	ldmfd	sp, {fp, sp, pc}	@
.L242:
	ldr	r1, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r1, #1	@ <variable>.s32IsRun,
	bne	.L224	@,
	cmp	r0, #5	@ eVidStd.1767,
	cmpne	r0, #3	@, eVidStd.1767,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1767,
	cmpne	r0, #8	@, eVidStd.1767,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1767,
	cmpne	r0, #10	@, eVidStd.1767,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1767,
	cmpne	r0, #12	@, eVidStd.1767,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1767,
	cmpne	r0, #15	@, eVidStd.1767,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1767,
	bne	.L224	@,
	ldmfd	sp, {fp, sp, pc}	@
.L243:
	ldr	r2, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r2, #1	@ <variable>.s32IsRun,
	bne	.L225	@,
	cmp	r0, #5	@ eVidStd.1786,
	cmpne	r0, #3	@, eVidStd.1786,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r0, #6	@ eVidStd.1786,
	cmpne	r0, #8	@, eVidStd.1786,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #9	@ eVidStd.1786,
	cmpne	r0, #10	@, eVidStd.1786,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #11	@ eVidStd.1786,
	cmpne	r0, #12	@, eVidStd.1786,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #13	@ eVidStd.1786,
	cmpne	r0, #15	@, eVidStd.1786,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #16	@ eVidStd.1786,
	bne	.L225	@,
	ldmfd	sp, {fp, sp, pc}	@
.L244:
	ldr	r3, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r3, #1	@ <variable>.s32IsRun,
	bne	.L226	@,
	cmp	r1, #5	@ eVidStd,
	cmpne	r1, #3	@, eVidStd,
	ldmlsfd	sp, {fp, sp, pc}	@
	cmp	r1, #6	@ eVidStd,
	cmpne	r1, #8	@, eVidStd,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r1, #9	@ eVidStd,
	cmpne	r1, #10	@, eVidStd,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r1, #11	@ eVidStd,
	cmpne	r1, #12	@, eVidStd,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r1, #13	@ eVidStd,
	cmpne	r1, #15	@, eVidStd,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r1, #16	@ eVidStd,
	bne	.L226	@,
	ldmfd	sp, {fp, sp, pc}	@
.L245:
	mov	r0, r3	@, D.44365
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #10015	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
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
	stmfd	sp!, {fp, ip, lr, pc}	@,
	.pad #4
	.save {fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ ChanID,
	bhi	.L254	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp138,
	movt	r3, #:upper16:.LANCHOR0	@ tmp138,
	ldr	r0, [r3, r0, asl #2]	@ D.44295, s_pstVfmwChan
	cmp	r0, #0	@ D.44295,
	beq	.L255	@,
	ldr	r1, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r1, #1	@ <variable>.s32IsOpen,
	bne	.L250	@,
	ldr	r0, [r0, #1032]	@ D.44303, <variable>.eVidStd
	cmp	r0, #19	@ D.44303,
	beq	.L250	@,
	cmp	r0, #7	@ D.44303,
	cmpne	r0, #4	@, D.44303,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #14	@ D.44303,
	cmpne	r0, #18	@, D.44303,
	movne	r0, #0	@, tmp155
	moveq	r0, #1	@, tmp155
	ldmeqfd	sp, {fp, sp, pc}	@
	movw	r2, #:lower16:g_vdm_hal_fun_ptr	@ tmp156,
	movt	r2, #:upper16:g_vdm_hal_fun_ptr	@ tmp156,
	ldr	r3, [r2, #0]	@ D.44314, g_vdm_hal_fun_ptr.pfun_VDMDRV_OpenHardware
	cmp	r3, #0	@ D.44314,
	beq	.L256	@,
	blx	r3	@ D.44314
	ldmfd	sp, {fp, sp, pc}	@
.L250:
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #9959	@,
	movt	r1, #:upper16:.LC3	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L254:
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #9947	@,
	movt	r1, #:upper16:.LC1	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L255:
	movw	r1, #:lower16:.LC2	@,
	movw	r2, #9953	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
.L256:
	mov	r0, r3	@, D.44314
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #9975	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
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
	b	.L258	@
.L266:
	.word	.L259
	.word	.L260
	.word	.L261
	.word	.L262
	.word	.L263
	.word	.L264
	.word	.L265
.L265:
	cmp	r0, #1	@ SemiPlanarFlag,
	movne	r0, #7	@, eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L258:
	mov	r3, r1	@, enFmt
	movw	r2, #9929	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC4	@,
	movt	r1, #:upper16:.LC4	@,
	bl	dprint_vfmw	@
	mov	r0, #13	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L259:
	cmp	r0, #1	@ SemiPlanarFlag,
	movne	r0, #6	@ eYuvFormat,
	moveq	r0, #0	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L260:
	cmp	r0, #1	@ SemiPlanarFlag,
	moveq	r0, #2	@ eYuvFormat,
	movne	r0, #8	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L261:
	cmp	r0, #1	@ SemiPlanarFlag,
	moveq	r0, #4	@ eYuvFormat,
	movne	r0, #10	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L262:
	cmp	r0, #1	@ SemiPlanarFlag,
	moveq	r0, #3	@ eYuvFormat,
	movne	r0, #9	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L263:
	cmp	r0, #1	@ SemiPlanarFlag,
	moveq	r0, #5	@ eYuvFormat,
	movne	r0, #11	@ eYuvFormat,
	ldmfd	sp, {fp, sp, pc}	@
.L264:
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
	bhi	.L280	@,
	movw	r2, #:lower16:.LANCHOR0	@ tmp138,
	movt	r2, #:upper16:.LANCHOR0	@ tmp138,
	ldr	r3, [r2, r0, asl #2]	@ D.43227, s_pstVfmwChan
	cmp	r3, #0	@ D.43227,
	strne	r1, [r3, #824]	@ eState, <variable>.eLastFrameState
	ldmfd	sp, {fp, sp, pc}	@
.L280:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #8278	@,
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
	ldrls	r1, [r3, r5, asl #2]	@ eState, CSWTCH.916
	mov	r6, r0	@ ChanID, ChanID
	bl	VCTRL_SetLastFrameState	@
	ldr	ip, [r4, #64]	@ g_event_report.789, g_event_report
	cmp	ip, #0	@ g_event_report.789,
	beq	.L284	@,
	sub	r2, fp, #28	@ tmp140,,
	mov	r0, r6	@, ChanID
	mov	r1, #115	@,
	mov	r3, #4	@,
	str	r5, [r2, #-4]!	@ Value, para
	blx	ip	@ g_event_report.789
.L284:
	ldr	r3, [r4, r6, asl #2]	@ tmp143, s_pstVfmwChan
	mov	r2, r5	@, Value
	movw	r1, #:lower16:.LC7	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC7	@,
	ldr	r3, [r3, #824]	@, <variable>.eLastFrameState
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
	bhi	.L292	@,
	movw	r2, #:lower16:.LANCHOR0	@ tmp138,
	movt	r2, #:upper16:.LANCHOR0	@ tmp138,
	ldr	r3, [r2, r0, asl #2]	@ D.43215, s_pstVfmwChan
	cmp	r3, #0	@ D.43215,
	strne	r1, [r3, #820]	@ Value, <variable>.s32LastFrameIdPlus2
	ldmfd	sp, {fp, sp, pc}	@
.L292:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #8266	@,
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
	bhi	.L298	@,
	movw	r1, #:lower16:.LANCHOR0	@ tmp139,
	movt	r1, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r3, [r1, r0, asl #2]	@ D.43203, s_pstVfmwChan
	cmp	r3, #0	@ D.43203,
	mvneq	r0, #0	@ D.43201,
	ldrne	r0, [r3, #820]	@ D.43201, <variable>.s32LastFrameIdPlus2
	ldmfd	sp, {fp, sp, pc}	@
.L298:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #8254	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.43201,
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
	bhi	.L303	@,
.L300:
	add	r2, r5, #4992	@ tmp148, new_extra_disp,
	movw	ip, #5000	@ tmp143,
	add	r1, r2, #8	@ tmp148, tmp148,
	cmp	r0, ip	@ new_extra_ref, tmp143
	movge	r0, ip	@ iftmp.687, tmp143
	movw	r6, #:lower16:-5000	@ tmp145,
	movt	r6, #:upper16:-5000	@ tmp145,
	cmp	r0, r6	@ iftmp.687, tmp145
	strge	r0, [r4, #68]	@, iftmp.687, extra_ref
	strlt	r6, [r4, #68]	@, tmp145, extra_ref
	movw	r0, #10000	@ tmp150,
	cmp	r1, r0	@ tmp148, tmp150
	movw	r6, #:lower16:.LANCHOR0	@ tmp144,
	str	r5, [r4, #72]	@ new_extra_disp, extra_disp
	movt	r6, #:upper16:.LANCHOR0	@ tmp144,
	bhi	.L304	@,
.L301:
	movw	r0, #5000	@ tmp153,
	movw	r3, #:lower16:-5000	@ tmp155,
	cmp	r5, r0	@ new_extra_disp, tmp153
	movge	r5, r0	@ iftmp.1991, tmp153
	movt	r3, #:upper16:-5000	@ tmp155,
	cmp	r5, r3	@ iftmp.1991, tmp155
	strge	r5, [r4, #72]	@, iftmp.1991, extra_disp
	strlt	r3, [r4, #72]	@, tmp155, extra_disp
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L303:
	mov	r2, r0	@, new_extra_ref
	movw	r1, #:lower16:.LC8	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC8	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #68]	@ new_extra_ref, extra_ref
	b	.L300	@
.L304:
	mov	r2, r5	@, new_extra_disp
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC9	@,
	movt	r1, #:upper16:.LC9	@,
	bl	dprint_vfmw	@
	ldr	r5, [r6, #72]	@ new_extra_disp, extra_disp
	b	.L301	@
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
	bhi	.L310	@,
	movw	r1, #:lower16:.LANCHOR0	@ tmp139,
	movt	r1, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r3, [r1, r0, asl #2]	@ D.42663, s_pstVfmwChan
	cmp	r3, #0	@ D.42663,
	moveq	r0, #33	@ D.42661,
	ldrne	r0, [r3, #40]	@ D.42661, <variable>.eChanCapLevel
	ldmfd	sp, {fp, sp, pc}	@
.L310:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7365	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.42661,
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
	bhi	.L316	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp139,
	movt	r3, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r0, [r3, r0, asl #2]	@ D.42651, s_pstVfmwChan
	cmp	r0, #0	@ D.42651,
	beq	.L317	@,
	ldr	r0, [r0, #1784]	@ D.42649, <variable>.stSynExtraData.stChanOption.s32MaxHeight
	ldmfd	sp, {fp, sp, pc}	@
.L316:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7357	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.42649,
	ldmfd	sp, {fp, sp, pc}	@
.L317:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7358	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.42649,
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
	bhi	.L323	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp139,
	movt	r3, #:upper16:.LANCHOR0	@ tmp139,
	ldr	r0, [r3, r0, asl #2]	@ D.42639, s_pstVfmwChan
	cmp	r0, #0	@ D.42639,
	beq	.L324	@,
	ldr	r0, [r0, #1780]	@ D.42637, <variable>.stSynExtraData.stChanOption.s32MaxWidth
	ldmfd	sp, {fp, sp, pc}	@
.L323:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7349	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.42637,
	ldmfd	sp, {fp, sp, pc}	@
.L324:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7350	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.42637,
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
	beq	.L332	@,
	cmp	r4, r7	@ Threshould, StreamAmount
	blt	.L329	@,
.L331:
	mov	r4, r5	@ NextMode, CurMode
.L328:
	mov	r2, r5	@, CurMode
	mov	r3, r4	@, NextMode
	mov	r0, #30	@,
	movw	r1, #:lower16:.LC14	@,
	movt	r1, #:upper16:.LC14	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, NextMode
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L329:
	movw	r1, #:lower16:.LC13	@,
	mov	r0, #30	@,
	movt	r1, #:upper16:.LC13	@,
	mov	r4, #3	@ NextMode,
	bl	dprint_vfmw	@
	b	.L328	@
.L332:
	cmp	r6, r7	@ tmp141, StreamAmount
	ble	.L331	@,
	movw	r1, #:lower16:.LC12	@,
	mov	r0, #30	@,
	movt	r1, #:upper16:.LC12	@,
	mov	r4, #0	@ NextMode,
	bl	dprint_vfmw	@
	b	.L328	@
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
	sub	r3, r0, #18	@ D.44973, eCapLevel,
	movw	r6, #:lower16:CapItem	@ tmp316,
	movt	r6, #:upper16:CapItem	@ tmp316,
	cmp	r3, #7	@ D.44973,
	add	r4, r6, r8, asl #2	@, tmp171, tmp316, tmp169,
	str	r2, [fp, #-996]	@ ScdMemSize, %sfp
	mov	r5, r0	@ eCapLevel, eCapLevel
	movwls	r2, #:lower16:.LANCHOR1	@ tmp197,
	ldr	r8, [r4, #12]	@ TempMinFrame, CapItem
	movtls	r2, #:upper16:.LANCHOR1	@ tmp197,
	ldr	r0, [r4, #20]	@, CapItem
	ldr	ip, [r4, #8]	@ TempPmv, CapItem
	addls	r3, r2, r3, asl #2	@, tmp200, tmp197, D.44973,
	ldr	r9, [r4, #16]	@ TempMiddleFrame, CapItem
	movw	r4, #:lower16:.LANCHOR0	@ tmp318,
	movt	r4, #:upper16:.LANCHOR0	@ tmp318,
	str	r1, [fp, #-992]	@ VdmMemSize, %sfp
	ldrls	r3, [r3, #8]	@ MinDnrFspNum, CSWTCH.919
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
	bgt	.L338	@,
	ldr	r7, [r4, #68]	@ extra_ref_tmp, extra_ref
	add	r2, r3, r7	@ D.41848, s32MaxRefFrameNum, extra_ref_tmp
	cmp	r2, #16	@ D.41848,
	addgt	r7, r7, #16	@ D.41851, extra_ref_tmp,
	rsbgt	r7, r2, r7	@ extra_ref_tmp, D.41848, D.41851
.L338:
	add	r3, r7, ip	@ TempPmv.2113, extra_ref_tmp, TempPmv
	ldr	r1, [r4, #72]	@, extra_disp
	cmp	r3, #0	@ TempPmv.2113,
	str	r1, [fp, #-1000]	@, %sfp
	ble	.L354	@,
	cmp	r3, #17	@ TempPmv.2113,
	movge	r3, #17	@ TempPmv.2113,
	str	r3, [fp, #-1004]	@ TempPmv.2113, %sfp
.L340:
	cmp	r5, #23	@ eCapLevel,
	bhi	.L341	@,
	ldr	ip, [fp, #-1000]	@, %sfp
	add	r3, r7, ip	@ D.41854, extra_ref_tmp,
	add	r2, r3, r8	@ TempMinFrame.2110, D.41854, TempMinFrame
	add	r1, r3, r9	@ TempMiddleFrame.2111, D.41854, TempMiddleFrame
	cmp	r2, #0	@ TempMinFrame.2110,
	cmpgt	r1, #0	@, TempMiddleFrame.2111,
	ble	.L342	@,
	ldr	r0, [fp, #-1008]	@, %sfp
	add	lr, r3, r0	@ TempFluentFrame.2112, D.41854,
	cmp	lr, #0	@ TempFluentFrame.2112,
	strgt	lr, [fp, #-1012]	@ TempFluentFrame.2112, %sfp
	strgt	r1, [fp, #-1000]	@ TempMiddleFrame.2111, %sfp
	movgt	r8, r2	@ nMinFrame, TempMinFrame.2110
	ble	.L342	@,
.L344:
	movw	r7, #:lower16:g_vdm_hal_fun_ptr	@ tmp219,
	movt	r7, #:upper16:g_vdm_hal_fun_ptr	@ tmp219,
	ldr	ip, [r7, #36]	@ D.41872, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	cmp	ip, #0	@ D.41872,
	beq	.L347	@,
.L355:
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
	blx	ip	@ D.41872
	subs	r3, r0, #0	@ ret,
	bne	.L347	@,
	ldr	r2, [fp, #-980]	@ MemArrange.TotalMemUsed, MemArrange.TotalMemUsed
	ldr	lr, [fp, #-992]	@, %sfp
	add	r1, r2, #47616	@ tmp238, MemArrange.TotalMemUsed,
	add	ip, r1, #16	@ tmp238, tmp238,
	str	ip, [lr, #0]	@ tmp238,
	ldr	r1, [fp, #-996]	@, %sfp
	ldr	r0, [r6, #24]	@ tmp248, CapItem
	add	r2, r0, #32768	@ tmp249, tmp248,
	str	r2, [r1, #0]	@ tmp249,
	ldr	ip, [r7, #36]	@ temp.2115, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	cmp	ip, #0	@ temp.2115,
	beq	.L349	@,
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
	blx	ip	@ temp.2115
	subs	lr, r0, #0	@ ret.2118,
	bne	.L349	@,
	ldr	ip, [fp, #-980]	@ MemArrange.TotalMemUsed, MemArrange.TotalMemUsed
	ldr	r2, [fp, #-992]	@, %sfp
	add	r0, ip, #47616	@ tmp270, MemArrange.TotalMemUsed,
	add	r3, r0, #16	@ tmp270, tmp270,
	str	r3, [r2, #4]	@ tmp270,
	ldr	r0, [fp, #-996]	@, %sfp
	ldr	r1, [r6, #24]	@ tmp280, CapItem
	add	ip, r1, #32768	@ tmp281, tmp280,
	str	ip, [r0, #4]	@ tmp281,
	ldr	ip, [r7, #36]	@ temp.2122, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	cmp	ip, #0	@ temp.2122,
	beq	.L351	@,
	ldr	r3, [r4, r8, asl #2]	@ tmp296, CapItem
	mov	r0, #1	@,
	ldr	r2, [r4, r5, asl #2]	@ tmp290, CapItem
	mvn	r1, #-2147483648	@,
	ldr	r4, [fp, #-1004]	@, %sfp
	str	lr, [sp, #8]	@ ret.2118,
	str	sl, [sp, #12]	@ tmp234,
	str	r4, [sp, #0]	@,
	ldr	r4, [fp, #-1012]	@, %sfp
	str	r9, [sp, #16]	@ tmp236,
	str	r4, [sp, #4]	@,
	blx	ip	@ temp.2122
	cmp	r0, #0	@ ret.2125
	bne	.L351	@,
	ldr	r1, [fp, #-980]	@ MemArrange.TotalMemUsed, MemArrange.TotalMemUsed
	ldr	ip, [fp, #-992]	@, %sfp
	add	lr, r1, #47616	@ tmp302, MemArrange.TotalMemUsed,
	add	r2, lr, #16	@ tmp302, tmp302,
	str	r2, [ip, #8]	@ tmp302,
	ldr	lr, [fp, #-996]	@, %sfp
	ldr	r3, [r6, #24]	@ tmp312, CapItem
	add	r1, r3, #32768	@ tmp313, tmp312,
	str	r1, [lr, #8]	@ tmp313,
	b	.L346	@
.L341:
	cmp	r5, #32	@ eCapLevel,
	bls	.L345	@,
.L353:
	mvn	r0, #0	@ D.41890,
.L346:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L342:
	ldr	ip, [r4, #72]	@ extra_disp.2114, extra_disp
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
	str	ip, [sp, #24]	@ extra_disp.2114,
	str	ip, [sp, #0]	@ extra_disp.2114,
	mov	r4, lr	@,
	str	ip, [sp, #12]	@ extra_disp.2114,
	str	lr, [fp, #-1012]	@, %sfp
	str	r9, [fp, #-1000]	@ TempMiddleFrame, %sfp
	str	r9, [sp, #4]	@ TempMiddleFrame,
	str	lr, [sp, #16]	@ tmp4,
	bl	dprint_vfmw	@
	ldr	ip, [r7, #36]	@ D.41872, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	cmp	ip, #0	@ D.41872,
	bne	.L355	@,
.L347:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC17	@,
	movw	r2, #6115	@,
	movt	r1, #:upper16:.LC17	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41890,
	b	.L346	@
.L345:
	ldr	r7, [fp, #-1008]	@, %sfp
	str	r9, [fp, #-1000]	@ TempMiddleFrame, %sfp
	str	r7, [fp, #-1012]	@, %sfp
	b	.L344	@
.L354:
	mov	r2, ip	@, TempPmv
	movw	r1, #:lower16:.LC15	@,
	mov	r3, r7	@, extra_ref_tmp
	movt	r1, #:upper16:.LC15	@,
	mov	r0, #32	@,
	cmp	ip, #17	@ TempPmv,
	movge	ip, #17	@ TempPmv,
	str	ip, [fp, #-1004]	@ TempPmv, %sfp
	bl	dprint_vfmw	@
	b	.L340	@
.L349:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC17	@,
	movw	r2, #6134	@,
	movt	r1, #:upper16:.LC17	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41890,
	b	.L346	@
.L351:
	movw	r1, #:lower16:.LC17	@,
	movw	r2, #6153	@,
	movt	r1, #:upper16:.LC17	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	b	.L353	@
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
	movw	ip, #:lower16:4780440	@ tmp242,
	cmp	r0, #26	@ eCapLevel,
	movt	ip, #:upper16:4780440	@ tmp242,
	movw	sl, #:lower16:11613104	@ tmp241,
	movt	sl, #:upper16:11613104	@ tmp241,
	movne	sl, ip	@ s32ChanCtxSize, tmp242
	cmp	r3, #2	@ flag,
	mov	r7, r0	@ eCapLevel, eCapLevel
	mov	r8, r3	@ flag, flag
	mov	r4, r1	@ pChanOption, pChanOption
	mov	r5, r2	@ pDetailMemSize, pDetailMemSize
	beq	.L359	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp165,
	movt	r3, #:upper16:.LANCHOR0	@ tmp165,
	ldr	ip, [r1, #64]	@ D.41671, <variable>.s32DisplayFrameNum
	ldr	r9, [r3, #72]	@ extra_disp.641, extra_disp
	ldr	r2, [r1, #36]	@ D.41669, <variable>.s32MaxRefFrameNum
	ldr	r3, [r3, #68]	@ extra_ref.640, extra_ref
	add	r6, r9, ip	@ TempDispNum, extra_disp.641, D.41671
	add	r1, r3, r2	@ TempRefNum, extra_ref.640, D.41669
	orrs	r0, r6, r1	@, TempDispNum, TempRefNum
	bmi	.L387	@,
	cmp	r1, #16	@ TempRefNum,
	strle	r1, [r4, #36]	@ TempRefNum, <variable>.s32MaxRefFrameNum
	strle	r6, [r4, #64]	@ TempDispNum, <variable>.s32DisplayFrameNum
	bgt	.L388	@,
.L363:
	rsbs	r8, r8, #1	@ tmp185, flag
	movcc	r8, #0	@ tmp185
	cmp	r7, #25	@ eCapLevel,
	moveq	r8, #0	@, tmp185,
	cmp	r8, #0	@ tmp185,
	bne	.L389	@,
.L359:
	ldr	r3, [r4, #4]	@ D.41690, <variable>.Purpose
	cmp	r3, #2	@ D.41690,
	bhi	.L390	@,
	bne	.L365	@,
	ldr	r3, [r4, #68]	@ D.41698, <variable>.s32SlotWidth
	cmp	r3, #0	@ D.41698,
	beq	.L366	@,
	ldr	r2, [r4, #72]	@ D.41700, <variable>.s32SlotHeight
	cmp	r2, #0	@ D.41700,
	beq	.L366	@,
	mul	r3, r2, r3	@ tmp189, D.41700, D.41698
	ldr	r1, [r4, #64]	@ <variable>.s32DisplayFrameNum, <variable>.s32DisplayFrameNum
	mov	r0, #0	@ tmp194,
	stmib	r5, {r0, sl}	@ phole stm
	mov	ip, r3, asl #1	@ tmp190, tmp189,
	mla	r2, r1, ip, ip	@ tmp193, <variable>.s32DisplayFrameNum, tmp190, tmp190
	str	r2, [r5, #0]	@ tmp193, <variable>.VdhDetailMem
.L361:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L388:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC19	@,
	movt	r1, #:upper16:.LC19	@,
	bl	dprint_vfmw	@
	mov	r0, #16	@ tmp178,
	str	r6, [r4, #64]	@ TempDispNum, <variable>.s32DisplayFrameNum
	str	r0, [r4, #36]	@ tmp178, <variable>.s32MaxRefFrameNum
	b	.L363	@
.L365:
	cmp	r3, #1	@ D.41690,
	mvnne	r0, #0	@ D.41679,
	bne	.L361	@
.L368:
	ldr	r0, [r4, #36]	@ temp.2156, <variable>.s32MaxRefFrameNum
	cmp	r0, #0	@ temp.2156,
	blt	.L369	@,
	ldr	r2, [r4, #12]	@ D.41713, <variable>.s32MaxWidth
	cmp	r2, #31	@ D.41713,
	ble	.L369	@,
	ldr	r3, [r4, #16]	@ D.41715, <variable>.s32MaxHeight
	cmp	r3, #31	@ D.41715,
	ble	.L369	@,
	ldr	ip, [r4, #60]	@ <variable>.s32SCDBufSize, <variable>.s32SCDBufSize
	cmp	ip, #262144	@ <variable>.s32SCDBufSize,
	blt	.L369	@,
	ldr	r1, [r4, #48]	@ D.41719, <variable>.s32SupportH264
	cmp	r1, #1	@ D.41719,
	beq	.L391	@,
	cmp	r1, #2	@ D.41719,
	beq	.L392	@,
.L371:
	ldr	r6, [r4, #44]	@ <variable>.s32SupportBFrame, <variable>.s32SupportBFrame
	cmp	r6, #0	@ <variable>.s32SupportBFrame,
	moveq	lr, #1	@ PmvNum,
	beq	.L373	@,
	add	lr, r0, #1	@ PmvNum.2160, temp.2156,
	cmp	lr, #17	@ PmvNum.2160,
	movge	lr, #17	@ PmvNum,
.L373:
	movw	r1, #:lower16:g_vdm_hal_fun_ptr	@ tmp206,
	movt	r1, #:upper16:g_vdm_hal_fun_ptr	@ tmp206,
	sub	r6, r7, #27	@ D.41737, eCapLevel,
	ldr	r8, [r4, #64]	@ temp.2161, <variable>.s32DisplayFrameNum
	cmp	r6, #6	@ D.41737,
	ldr	ip, [r1, #36]	@ D.41742, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	mvncc	r1, #1	@, eFlag,
	mvncs	r1, #0	@, eFlag,
	cmp	ip, #0	@ D.41742,
	beq	.L376	@,
	add	r0, r0, r8	@ tmp207, temp.2156, temp.2161
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
	blx	ip	@ D.41742
	cmp	r0, #0	@,
	bne	.L376	@,
	ldr	ip, [fp, #-980]	@ MemArrange.TotalMemUsed, MemArrange.TotalMemUsed
	add	r3, ip, #16	@ D.41750, MemArrange.TotalMemUsed,
	str	r3, [r5, #0]	@ D.41750, <variable>.VdhDetailMem
	ldr	r2, [r4, #120]	@ <variable>.u32DynamicFrameStoreAllocEn, <variable>.u32DynamicFrameStoreAllocEn
	cmp	r2, #1	@ <variable>.u32DynamicFrameStoreAllocEn,
	addne	r3, r3, #47616	@ tmp214, D.41750,
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
	beq	.L380	@,
	ldr	lr, [r4, #20]	@ <variable>.s32MaxSliceNum, <variable>.s32MaxSliceNum
	movw	r1, #4060	@ tmp222,
	ldr	r0, [r4, #28]	@ D.41767, <variable>.s32MaxSpsNum
	mov	r3, #4000	@ tmp224,
	ldr	r2, [r4, #32]	@ D.41770, <variable>.s32MaxPpsNum
	mov	ip, #2208	@ tmp227,
	mul	r1, r1, lr	@ D.41766, tmp222, <variable>.s32MaxSliceNum
	mla	lr, r3, r0, r1	@ tmp225, tmp224, D.41767, D.41766
	mla	r3, ip, r2, lr	@ TempAddMem, tmp227, D.41770, tmp225
	cmp	r3, #0	@ TempAddMem,
	movcc	r3, #0	@ TempAddMem,
	cmp	r7, #26	@ eCapLevel,
	beq	.L393	@,
.L380:
	cmp	r6, #5	@ D.41737,
	bhi	.L381	@,
	movw	lr, #:lower16:1718176	@ tmp234,
	movt	lr, #:upper16:1718176	@ tmp234,
	cmp	r3, lr	@ TempAddMem, tmp234
	movcc	r3, lr	@ TempAddMem, tmp234
.L381:
	add	r3, r3, sl	@ tmp235, TempAddMem, s32ChanCtxSize
	mov	r0, #0	@ D.41679,
	str	r3, [r5, #8]	@ tmp235, <variable>.ChanCtxDetailMem
	b	.L361	@
.L366:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC22	@,
	movt	r1, #:upper16:.LC22	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41679,
	b	.L361	@
.L389:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC20	@,
	movt	r1, #:upper16:.LC20	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41679,
	b	.L361	@
.L390:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC21	@,
	movt	r1, #:upper16:.LC21	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41679,
	b	.L361	@
.L387:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC18	@,
	movt	r1, #:upper16:.LC18	@,
	str	ip, [sp, #0]	@ D.41671,
	str	r9, [sp, #4]	@ extra_disp.641,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41679,
	b	.L361	@
.L391:
	ldr	r1, [r4, #20]	@ <variable>.s32MaxSliceNum, <variable>.s32MaxSliceNum
	cmp	r1, #0	@ <variable>.s32MaxSliceNum,
	ble	.L369	@,
.L385:
	ldr	ip, [r4, #28]	@ <variable>.s32MaxSpsNum, <variable>.s32MaxSpsNum
	cmp	ip, #0	@ <variable>.s32MaxSpsNum,
	ble	.L369	@,
	ldr	r1, [r4, #32]	@ <variable>.s32MaxPpsNum, <variable>.s32MaxPpsNum
	cmp	r1, #0	@ <variable>.s32MaxPpsNum,
	bgt	.L371	@,
.L369:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC23	@,
	movt	r1, #:upper16:.LC23	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41679,
	b	.L361	@
.L392:
	ldr	ip, [r4, #20]	@ <variable>.s32MaxSliceNum, <variable>.s32MaxSliceNum
	cmp	ip, #0	@ <variable>.s32MaxSliceNum,
	ble	.L369	@,
	ldr	r1, [r4, #24]	@ <variable>.s32MaxVpsNum, <variable>.s32MaxVpsNum
	cmp	r1, #0	@ <variable>.s32MaxVpsNum,
	bgt	.L385	@,
	b	.L369	@
.L393:
	movw	ip, #3992	@ tmp229,
	mla	r1, ip, r0, r1	@ tmp230, tmp229, D.41767, D.41766
	mov	r0, #2240	@ tmp232,
	mla	r2, r0, r2, r1	@ tmp233, tmp232, D.41770, tmp230
	cmp	r3, r2	@ TempAddMem, tmp233
	movcc	r3, r2	@ TempAddMem, tmp233
	b	.L380	@
.L376:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC24	@,
	movw	r2, #5884	@,
	movt	r1, #:upper16:.LC24	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41679,
	b	.L361	@
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
	bhi	.L401	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r3, [r3, r0, asl #2]	@ D.41338, s_pstVfmwChan
	cmp	r3, #0	@ D.41338,
	beq	.L402	@,
	ldr	r2, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r2, #1	@ <variable>.s32IsOpen,
	bne	.L403	@,
	cmp	r1, #0	@ pArgs,
	beq	.L404	@,
	ldr	ip, [r1, #0]	@ tmp148,* pArgs
	mov	r0, #0	@ D.41336,
	str	ip, [r3, #1732]	@ tmp148, <variable>.stSynExtraData.s32FastForwardBackwardSpeed
	ldmfd	sp, {fp, sp, pc}	@
.L403:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4951	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC26	@,
	movt	r3, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41336,
	ldmfd	sp, {fp, sp, pc}	@
.L401:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4949	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41336,
	ldmfd	sp, {fp, sp, pc}	@
.L402:
	mov	r0, r3	@, D.41338
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4950	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC25	@,
	movt	r3, #:upper16:.LC25	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41336,
	ldmfd	sp, {fp, sp, pc}	@
.L404:
	mov	r0, r1	@, pArgs
	movw	r2, #4952	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC27	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41336,
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
	bhi	.L411	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp141,
	movt	r3, #:upper16:.LANCHOR0	@ tmp141,
	ldr	r0, [r3, r0, asl #2]	@ D.41103, s_pstVfmwChan
	cmp	r0, #0	@ D.41103,
	beq	.L412	@,
	cmp	r1, #0	@ pstMemRec,
	bne	.L413	@,
.L409:
	mvn	r0, #0	@ D.41101,
	ldmfd	sp, {fp, sp, pc}	@
.L412:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4566	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41101,
	ldmfd	sp, {fp, sp, pc}	@
.L413:
	ldr	r2, [r0, #188]	@ <variable>.s32OneChanMem, <variable>.s32OneChanMem
	cmp	r2, #1	@ <variable>.s32OneChanMem,
	bne	.L409	@,
	ldr	r3, [r0, #196]	@ D.41115, <variable>.stChanMem.VirAddr
	ldr	ip, [r0, #204]	@ <variable>.stChanMem.Length, <variable>.stChanMem.Length
	ldr	r2, [r0, #200]	@ <variable>.stChanMem.PhyAddr, <variable>.stChanMem.PhyAddr
	cmp	r3, #0	@ D.41115,
	str	r3, [r1, #4]	@ D.41115, <variable>.VirAddr
	str	ip, [r1, #12]	@ <variable>.stChanMem.Length, <variable>.Length
	movne	r0, #0	@ D.41101,
	str	r2, [r1, #8]	@ <variable>.stChanMem.PhyAddr, <variable>.PhyAddr
	ldmnefd	sp, {fp, sp, pc}	@
	b	.L409	@
.L411:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4565	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC28	@,
	movt	r3, #:upper16:.LC28	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41101,
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
	bhi	.L415	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	ldr	r3, [r3, r0, asl #2]	@ D.41001, s_pstVfmwChan
	cmp	r3, #0	@ D.41001,
	beq	.L415	@,
	ldr	r2, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r2, #1	@ <variable>.s32IsOpen,
	beq	.L418	@,
	mov	r3, r0	@, ChanId
	movw	r1, #:lower16:.LC30	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC30	@,
	movw	r2, #4386	@,
	bl	dprint_vfmw	@
	mov	r0, #19	@ D.41003,
	ldmfd	sp, {fp, sp, pc}	@
.L415:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC29	@,
	movw	r2, #4379	@,
	movt	r1, #:upper16:.LC29	@,
	bl	dprint_vfmw	@
	mov	r0, #19	@ D.41003,
	ldmfd	sp, {fp, sp, pc}	@
.L418:
	ldr	r0, [r3, #1032]	@ D.41003, <variable>.eVidStd
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
	ldr	ip, [r2, #0]	@ g_chipID.526, g_chipID
	ldr	r3, [r3, r0, asl #2]	@ D.40286, s_pstVfmwChan
	cmp	ip, #11	@ g_chipID.526,
	ldr	r0, [r3, #1784]	@ ChanMaxHeight, <variable>.stSynExtraData.stChanOption.s32MaxHeight
	ldr	r3, [r3, #1780]	@ ChanMaxWidth, <variable>.stSynExtraData.stChanOption.s32MaxWidth
	bgt	.L424	@,
	cmp	ip, #5	@ g_chipID.526,
	blt	.L431	@,
.L423:
	movw	r2, #:lower16:g_ChipMaxWidth	@ tmp152,
	movt	r2, #:upper16:g_ChipMaxWidth	@ tmp152,
	ldr	r2, [r2, #0]	@ g_ChipMaxWidth.2264, g_ChipMaxWidth
	cmp	r3, r2	@ ChanMaxWidth, g_ChipMaxWidth.2264
	ble	.L432	@,
	ldr	r3, [r1, #0]	@ D.40300, <variable>.eVidStd
	cmp	r3, #13	@ D.40300,
	cmpne	r3, #0	@, D.40300,
	beq	.L426	@,
.L437:
	cmp	r3, #15	@ D.40300,
	beq	.L426	@,
	cmp	r3, #18	@ D.40300,
	bne	.L433	@,
.L426:
	mov	r0, #0	@ ret,
	b	.L427	@
.L424:
	cmp	ip, #51	@ g_chipID.526,
	bge	.L434	@,
.L421:
	mov	r2, ip	@, g_chipID.526
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
.L427:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L431:
	cmp	ip, #0	@ g_chipID.526,
	blt	.L421	@,
	movw	r2, #:lower16:g_ChipMaxWidth	@ tmp146,
	movt	r2, #:upper16:g_ChipMaxWidth	@ tmp146,
	ldr	r2, [r2, #0]	@ g_ChipMaxWidth, g_ChipMaxWidth
	cmp	r3, r2	@ ChanMaxWidth, g_ChipMaxWidth
	ble	.L435	@,
	ldr	r0, [r1, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r0, #18	@ <variable>.eVidStd,
	beq	.L426	@,
.L436:
	mov	r2, ip	@, g_chipID.526
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC31	@,
	movt	r1, #:upper16:.LC31	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L427	@
.L434:
	cmp	ip, #52	@ g_chipID.526,
	ble	.L423	@,
	sub	r2, ip, #100	@ tmp145, g_chipID.526,
	cmp	r2, #1	@ tmp145,
	bhi	.L421	@,
	b	.L423	@
.L435:
	movw	r2, #:lower16:g_ChipMaxHeight	@ tmp148,
	movt	r2, #:upper16:g_ChipMaxHeight	@ tmp148,
	ldr	r3, [r2, #0]	@ g_ChipMaxHeight, g_ChipMaxHeight
	cmp	r0, r3	@ ChanMaxHeight, g_ChipMaxHeight
	ble	.L426	@,
	ldr	r0, [r1, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r0, #18	@ <variable>.eVidStd,
	beq	.L426	@,
	b	.L436	@
.L432:
	movw	r3, #:lower16:g_ChipMaxHeight	@ tmp153,
	movt	r3, #:upper16:g_ChipMaxHeight	@ tmp153,
	ldr	r3, [r3, #0]	@ g_ChipMaxHeight, g_ChipMaxHeight
	cmp	r0, r3	@ ChanMaxHeight, g_ChipMaxHeight
	ble	.L426	@,
	ldr	r3, [r1, #0]	@ D.40300, <variable>.eVidStd
	cmp	r3, #13	@ D.40300,
	cmpne	r3, #0	@, D.40300,
	bne	.L437	@,
	b	.L426	@
.L433:
	movw	r1, #:lower16:g_ChipMaxHeight	@ tmp163,
	movt	r1, #:upper16:g_ChipMaxHeight	@ tmp163,
	mov	r0, #0	@,
	ldr	r3, [r1, #0]	@ g_ChipMaxHeight, g_ChipMaxHeight
	movw	r1, #:lower16:.LC32	@,
	movt	r1, #:upper16:.LC32	@,
	str	ip, [sp, #0]	@ g_chipID.526,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L427	@
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
	ldr	r3, [r4, r0, asl #2]	@ D.40165, s_pstVfmwChan
	ldr	r2, [r3, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	ip, [r3, #1944]	@ eOldDecCore, <variable>.eDecCore
	cmp	r2, #4	@ <variable>.eVidStd,
	moveq	r2, #1	@ tmp148,
	streq	r2, [r3, #1944]	@ tmp148, <variable>.eDecCore
	beq	.L442	@,
	cmp	r2, #14	@ <variable>.eVidStd,
	movne	r2, #0	@ tmp150,
	strne	r2, [r3, #1944]	@ tmp150, <variable>.eDecCore
	moveq	r2, #2	@ tmp149,
	streq	r2, [r3, #1944]	@ tmp149, <variable>.eDecCore
.L442:
	ldr	r0, [r4, r5, asl #2]	@ prephitmp.2283, s_pstVfmwChan
	movw	r6, #:lower16:.LANCHOR0	@ tmp151,
	movt	r6, #:upper16:.LANCHOR0	@ tmp151,
	ldr	r2, [r0, #1944]	@ prephitmp.2285, <variable>.eDecCore
	cmp	r2, ip	@ prephitmp.2285, eOldDecCore
	beq	.L443	@,
	sub	ip, ip, #1	@ tmp152, eOldDecCore,
	cmp	ip, #4	@ tmp152,
	bhi	.L444	@,
	ldr	r3, [r6, #80]	@ D.40174, g_SdecFunc.pfun_iMediaSoftDEC_Destroy
	cmp	r3, #0	@ D.40174,
	beq	.L444	@,
	add	r0, r0, #250880	@, prephitmp.2283,
	str	r1, [fp, #-32]	@,
	add	r0, r0, #616	@,,
	blx	r3	@ D.40174
	ldr	r0, [r6, r5, asl #2]	@ prephitmp.2283, s_pstVfmwChan
	ldr	r1, [fp, #-32]	@,
	ldr	r2, [r0, #1944]	@ prephitmp.2285, <variable>.eDecCore
.L444:
	sub	r3, r2, #1	@ tmp157, prephitmp.2285,
	cmp	r3, #4	@ tmp157,
	bhi	.L443	@,
	ldr	ip, [r0, #40]	@ <variable>.eChanCapLevel, <variable>.eChanCapLevel
	movw	lr, #:lower16:251508	@ tmp158,
	movt	lr, #:upper16:251508	@ tmp158,
	movw	r2, #:lower16:.LANCHOR0	@ tmp160,
	movt	r2, #:upper16:.LANCHOR0	@ tmp160,
	str	ip, [r0, lr]	@ <variable>.eChanCapLevel, <variable>.stSynCtx.unSyntax.stiMediaSoftCtx.eChanCapLevel
	ldr	r3, [r4, #76]	@ D.40186, g_SdecFunc.pfun_iMediaSoftDEC_Create
	cmp	r3, #0	@ D.40186,
	beq	.L445	@,
	ldr	r2, [r2, r5, asl #2]	@ temp.2296, s_pstVfmwChan
	add	r0, r2, #250880	@, temp.2296,
	add	r0, r0, #616	@,,
	ldr	r2, [r2, #1032]	@, <variable>.eVidStd
	blx	r3	@ D.40186
	cmp	r0, #0	@,
	bne	.L445	@,
.L443:
	mov	r0, #0	@ D.40190,
.L446:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L445:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC34	@,
	movt	r1, #:upper16:.LC34	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40190,
	b	.L446	@
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
	ldr	r0, [r3, r0, asl #2]	@ D.39186, s_pstVfmwChan
	cmp	r0, #0	@ D.39186,
	beq	.L453	@,
	movw	r1, #:lower16:249228	@ tmp140,
	movt	r1, #:upper16:249228	@ tmp140,
	ldr	r0, [r0, r1]	@ D.39190, <variable>.s32SendStreamAgainFlag
	ldmfd	sp, {fp, sp, pc}	@
.L453:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1044	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39190,
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
	ldr	r2, [r3, r0, asl #2]	@ D.39177, s_pstVfmwChan
	cmp	r2, #0	@ D.39177,
	beq	.L458	@,
	movw	ip, #:lower16:249228	@ tmp141,
	movt	ip, #:upper16:249228	@ tmp141,
	mov	r0, #0	@ D.39181,
	str	r1, [r2, ip]	@ flag, <variable>.s32SendStreamAgainFlag
	ldmfd	sp, {fp, sp, pc}	@
.L458:
	mov	r0, r2	@, D.39177
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1037	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39181,
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
	beq	.L467	@,
	cmp	r0, #0	@ eType,
	movweq	r3, #:lower16:.LANCHOR0	@ tmp139,
	movteq	r3, #:upper16:.LANCHOR0	@ tmp139,
	streq	r1, [r3, #288]	@ event_report, s_VfmwCTrl.event_report_vdec
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r0, #1	@ eType,
	beq	.L468	@,
	mov	r3, r0	@, eType
	ldr	r2, .L469	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC36	@,
	movt	r1, #:upper16:.LC36	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39046,
	ldmfd	sp, {fp, sp, pc}	@
.L468:
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	mov	r0, #0	@ D.39046,
	str	r1, [r3, #292]	@ event_report, s_VfmwCTrl.event_report_omxvdec
	ldmfd	sp, {fp, sp, pc}	@
.L467:
	mov	r0, r1	@, event_report
	mov	r2, #752	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC35	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC35	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39046,
	ldmfd	sp, {fp, sp, pc}	@
.L470:
	.align	2
.L469:
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
	bhi	.L482	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp145,
	movt	r4, #:upper16:.LANCHOR0	@ tmp145,
	ldr	r3, [r4, r0, asl #2]	@ D.39015, s_pstVfmwChan
	cmp	r3, #0	@ D.39015,
	beq	.L483	@,
	ldr	r3, [r3, #36]	@ eType, <variable>.eAdapterType
	cmp	r3, #0	@ eType,
	beq	.L476	@,
	cmp	r3, #1	@ eType,
	beq	.L484	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC40	@,
	ldr	r2, .L486	@,
	movt	r1, #:upper16:.LC40	@,
	str	lr, [sp, #0]	@ len,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
.L473:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L476:
	ldr	r3, [r4, #288]	@ D.39018, s_VfmwCTrl.event_report_vdec
	cmp	r3, #0	@ D.39018,
	beq	.L485	@,
.L479:
	blx	r3	@ D.39024
	b	.L473	@
.L484:
	ldr	r3, [r4, #292]	@ D.39024, s_VfmwCTrl.event_report_omxvdec
	cmp	r3, #0	@ D.39024,
	bne	.L479	@,
	mov	r0, r3	@, D.39024
	movw	r1, #:lower16:.LC39	@,
	movt	r1, #:upper16:.LC39	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L473	@
.L485:
	mov	r0, r3	@, D.39018
	movw	r1, #:lower16:.LC38	@,
	movt	r1, #:upper16:.LC38	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L473	@
.L482:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	mov	r2, #716	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC37	@,
	movt	r3, #:upper16:.LC37	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L473	@
.L483:
	mov	r0, r3	@, D.39015
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #717	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	b	.L473	@
.L487:
	.align	2
.L486:
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
	bhi	.L495	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r3, [r3, r0, asl #2]	@ D.38986, s_pstVfmwChan
	cmp	r3, #0	@ D.38986,
	beq	.L496	@,
	ldr	r2, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r2, #1	@ <variable>.s32IsOpen,
	bne	.L497	@,
	cmp	r1, #1	@ MoreGapEnable,
	strls	r1, [r3, #1728]	@ MoreGapEnable, <variable>.stSynExtraData.s32MoreGapEnable
	movhi	r2, #0	@ tmp146,
	movls	r0, #0	@ D.38984,
	mvnhi	r0, #0	@ D.38984,
	strhi	r2, [r3, #1728]	@ tmp146, <variable>.stSynExtraData.s32MoreGapEnable
	ldmfd	sp, {fp, sp, pc}	@
.L497:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	mov	r2, #696	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC41	@,
	movt	r3, #:upper16:.LC41	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38984,
	ldmfd	sp, {fp, sp, pc}	@
.L495:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #694	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38984,
	ldmfd	sp, {fp, sp, pc}	@
.L496:
	mov	r0, r3	@, D.38986
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #695	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38984,
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
	beq	.L508	@,
	ldr	r3, [r0, #4]	@ <variable>.pfun_iMediaSoftDEC_Destroy, <variable>.pfun_iMediaSoftDEC_Destroy
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_Destroy,
	beq	.L509	@,
	ldr	r3, [r0, #8]	@ <variable>.pfun_iMediaSoftDEC_Init, <variable>.pfun_iMediaSoftDEC_Init
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_Init,
	beq	.L510	@,
	ldr	r3, [r0, #12]	@ <variable>.pfun_iMediaSoftDEC_Decode, <variable>.pfun_iMediaSoftDEC_Decode
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_Decode,
	beq	.L511	@,
	ldr	r3, [r0, #16]	@ <variable>.pfun_iMediaSoftDEC_RecycleImage, <variable>.pfun_iMediaSoftDEC_RecycleImage
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_RecycleImage,
	beq	.L512	@,
	ldr	r3, [r0, #20]	@ <variable>.pfun_iMediaSoftDEC_GetRemainImg, <variable>.pfun_iMediaSoftDEC_GetRemainImg
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_GetRemainImg,
	beq	.L513	@,
	ldr	r3, [r0, #24]	@ <variable>.pfun_iMediaSoftDEC_GetImageBuffer, <variable>.pfun_iMediaSoftDEC_GetImageBuffer
	cmp	r3, #0	@ <variable>.pfun_iMediaSoftDEC_GetImageBuffer,
	beq	.L514	@,
	mov	r4, r0	@ pstSdecFunc, pstSdecFunc
	ldr	ip, .L515	@ tmp158,
	ldmia	r4!, {r0, r1, r2, r3}	@ pstSdecFunc,,,,
	mov	r5, #0	@ D.38711,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp158,,,,
	ldmia	r4, {r0, r1, r2}	@ pstSdecFunc,,,
	stmia	ip, {r0, r1, r2}	@ tmp161,,,
.L500:
	mov	r0, r5	@, D.38711
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L508:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_Create
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC43	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC43	@,
	mvn	r5, #0	@ D.38711,
	bl	dprint_vfmw	@
	b	.L500	@
.L513:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_GetRemainImg
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC48	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC48	@,
	mvn	r5, #0	@ D.38711,
	bl	dprint_vfmw	@
	b	.L500	@
.L512:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_RecycleImage
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC47	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC47	@,
	mvn	r5, #0	@ D.38711,
	bl	dprint_vfmw	@
	b	.L500	@
.L511:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_Decode
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC46	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC46	@,
	mvn	r5, #0	@ D.38711,
	bl	dprint_vfmw	@
	b	.L500	@
.L510:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_Init
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC45	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC45	@,
	mvn	r5, #0	@ D.38711,
	bl	dprint_vfmw	@
	b	.L500	@
.L509:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_Destroy
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC44	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC44	@,
	mvn	r5, #0	@ D.38711,
	bl	dprint_vfmw	@
	b	.L500	@
.L514:
	mov	r0, r3	@, <variable>.pfun_iMediaSoftDEC_GetImageBuffer
	movw	r1, #:lower16:.LC42	@,
	movw	r2, #:lower16:.LC49	@,
	movt	r1, #:upper16:.LC42	@,
	movt	r2, #:upper16:.LC49	@,
	mvn	r5, #0	@ D.38711,
	bl	dprint_vfmw	@
	b	.L500	@
.L516:
	.align	2
.L515:
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
	bhi	.L524	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	ip, [r3, r0, asl #2]	@ D.41357, s_pstVfmwChan
	cmp	ip, #0	@ D.41357,
	beq	.L525	@,
	ldr	r0, [ip, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r0, #1	@ <variable>.s32IsOpen,
	bne	.L526	@,
	cmp	r1, #0	@ pArgs,
	beq	.L527	@,
	mov	r4, r1	@ pArgs, pArgs
	add	r5, ip, #1744	@ tmp148, D.41357,
	ldmia	r4!, {r0, r1, r2, r3}	@ pArgs,,,,
	add	ip, r5, #4	@ tmp148, tmp148,
	mov	r5, #0	@ D.41355,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp148,,,,
	ldr	r2, [r4, #0]	@ tmp152,* pArgs
	str	r2, [ip, #0]	@ tmp152, <variable>.stSynExtraData.stPvrInfo
.L519:
	mov	r0, r5	@, D.41355
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L526:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4964	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC26	@,
	movt	r3, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ D.41355,
	b	.L519	@
.L524:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4962	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ D.41355,
	b	.L519	@
.L527:
	mov	r0, r1	@, pArgs
	movw	r2, #4965	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC27	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ D.41355,
	b	.L519	@
.L525:
	mov	r0, ip	@, D.41357
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4963	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC25	@,
	movt	r3, #:upper16:.LC25	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ D.41355,
	b	.L519	@
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
	bhi	.L534	@,
	cmp	r1, #0	@ pstCfg,
	beq	.L535	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp142,
	movt	r3, #:upper16:.LANCHOR0	@ tmp142,
	ldr	r3, [r3, r0, asl #2]	@ D.40151, s_pstVfmwChan
	cmp	r3, #0	@ D.40151,
	beq	.L536	@,
	mov	r0, r1	@, pstCfg
	mov	r2, #92	@,
	add	r1, r3, #48	@, D.40151,
	bl	memcpy	@
	mov	r0, #0	@ D.40147,
	ldmfd	sp, {fp, sp, pc}	@
.L534:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2844	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40147,
	ldmfd	sp, {fp, sp, pc}	@
.L536:
	mov	r0, r3	@, D.40151
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2846	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40147,
	ldmfd	sp, {fp, sp, pc}	@
.L535:
	mov	r0, r1	@, pstCfg
	movw	r2, #2845	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC50	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC50	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40147,
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
	bhi	.L544	@,
	cmp	r1, #0	@ pArgs,
	beq	.L545	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp143,
	movt	r3, #:upper16:.LANCHOR0	@ tmp143,
	ldr	r2, [r3, r0, asl #2]	@ D.39260, s_pstVfmwChan
	cmp	r2, #0	@ D.39260,
	beq	.L546	@,
	ldmia	r1, {r0, r1}	@ pArgs,,
	add	r2, r2, #1904	@ tmp146, D.39260,
	add	r2, r2, #12	@ tmp146, tmp146,
	stmia	r2, {r0, r1}	@ tmp146,,
	ldr	r3, [r3, ip, asl #2]	@ temp.2522, s_pstVfmwChan
	ldr	r0, [r3, #1916]	@ <variable>.stSynExtraData.stDisParams.s32Mode, <variable>.stSynExtraData.stDisParams.s32Mode
	sub	r2, r0, #1	@ tmp151, <variable>.stSynExtraData.stDisParams.s32Mode,
	mov	r0, #0	@ D.39256,
	cmp	r2, #1	@ tmp151,
	strhi	r0, [r3, #1916]	@ tmp153, <variable>.stSynExtraData.stDisParams.s32Mode
	ldmfd	sp, {fp, sp, pc}	@
.L544:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1122	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39256,
	ldmfd	sp, {fp, sp, pc}	@
.L546:
	mov	r0, r2	@, D.39260
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1124	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39256,
	ldmfd	sp, {fp, sp, pc}	@
.L545:
	mov	r0, r1	@, pArgs
	movw	r2, #1123	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39256,
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
	beq	.L552	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r3, [r3, r0, asl #2]	@ D.39216, s_pstVfmwChan
	cmp	r3, #0	@ D.39216,
	beq	.L553	@,
	ldmia	r1, {r0, r1, r2}	@ pstFrameIntf,,,
	add	r3, r3, #164	@ tmp143, D.39216,
	mov	ip, #0	@ D.39214,
	stmia	r3, {r0, r1, r2}	@ tmp143,,,
.L549:
	mov	r0, ip	@, D.39214
	ldmfd	sp, {fp, sp, pc}	@
.L553:
	mov	r0, r3	@, D.39216
	movw	r1, #:lower16:.LC5	@,
	mov	r2, #1072	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	ip, #0	@ D.39214,
	b	.L549	@
.L552:
	mov	r0, r1	@, pstFrameIntf
	movw	r2, #1071	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	mvn	ip, #0	@ D.39214,
	b	.L549	@
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
	beq	.L559	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp140,
	movt	r4, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r0, [r4, r0, asl #2]	@ D.39165, s_pstVfmwChan
	cmp	r0, #0	@ D.39165,
	beq	.L560	@,
	add	r5, r5, r5, asl #1	@, tmp152, ChanID, ChanID,
	mov	r2, #12	@,
	add	r4, r4, #296	@ tmp149, tmp140,
	add	r0, r0, #140	@, D.39165,
	bl	memcpy	@
	mov	r1, r6	@, pstStreamParam
	add	r0, r4, r5, asl #2	@,, tmp149, tmp152,
	mov	r2, #12	@,
	bl	memcpy	@
	mov	r0, #0	@ D.39163,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L560:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1028	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39163,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L559:
	mov	r0, r6	@, pstStreamParam
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1027	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC53	@,
	movt	r3, #:upper16:.LC53	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39163,
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
	beq	.L598	@,
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
	bne	.L563	@,
	ldr	sl, [fp, #4]	@, Height
	cmp	sl, #0	@,
	movweq	r6, #:lower16:.LANCHOR0	@ tmp334,
	movteq	r6, #:upper16:.LANCHOR0	@ tmp334,
	beq	.L564	@,
	movw	r6, #:lower16:.LANCHOR0	@ tmp334,
	movt	r6, #:upper16:.LANCHOR0	@ tmp334,
	mov	r8, r5	@ Yaddress, Yaddress
	mov	r9, r4	@ Width, Width
	mov	sl, #0	@ ivtmp.2693,
	str	sl, [fp, #-48]	@ ivtmp.2693, %sfp
.L565:
	cmp	r9, #0	@ Width,
	beq	.L567	@,
	ldr	r1, [fp, #-48]	@, %sfp
	sub	r4, r9, #1	@ tmp373, Width,
	ldr	r2, [fp, #12]	@, Stride
	ubfx	r5, r4, #8, #1	@ tmp374, tmp373,,
	and	lr, r1, #15	@ pretmp.2790,,
	ldr	ip, [r6, #488]	@ pY, pY
	mov	r0, r1, lsr #4	@ pretmp.2793,,
	mul	r7, r2, r0	@ tmp234,, pretmp.2793
	mov	r2, #256	@,
	mla	r7, lr, r2, r7	@ pretmp.2635, pretmp.2790,, tmp234
	add	r0, sl, ip	@, ivtmp.2693, pY
	mov	r4, r2	@ j,
	add	r1, r8, r7	@, Yaddress, pretmp.2635
	bl	memcpy	@
	cmp	r9, r4	@ Width, j
	bls	.L567	@,
	cmp	r5, #0	@ tmp374,
	beq	.L566	@,
	ldr	r5, [r6, #488]	@ pY, pY
	add	ip, sl, r4	@ tmp515, ivtmp.2693, j
	add	lr, r7, #4096	@ tmp520, pretmp.2635,
	mov	r2, r4	@, j
	add	r0, ip, r5	@, tmp515, pY
	add	r1, r8, lr	@, Yaddress, tmp520
	bl	memcpy	@
	mov	r4, #512	@ j,
	cmp	r9, r4	@ Width, j
	bls	.L567	@,
.L566:
	mov	r1, r4, lsr #8	@ tmp225, j,
	ldr	r2, [r6, #488]	@ pY, pY
	add	r5, r4, #256	@ tmp375, j,
	add	ip, sl, r4	@ tmp222, ivtmp.2693, j
	add	lr, r7, r1, asl #12	@, tmp227, pretmp.2635, tmp225,
	add	r0, ip, r2	@, tmp222, pY
	add	r1, r8, lr	@, Yaddress, tmp227
	mov	r2, #256	@,
	mov	r4, r5, lsr #8	@ tmp400, tmp375,
	bl	memcpy	@
	ldr	r3, [r6, #488]	@ pY, pY
	add	r0, sl, r5	@ tmp397, ivtmp.2693, tmp375
	add	r2, r7, r4, asl #12	@, tmp402, pretmp.2635, tmp400,
	add	r4, r5, #256	@ j, tmp375,
	add	r1, r8, r2	@, Yaddress, tmp402
	add	r0, r0, r3	@, tmp397, pY
	mov	r2, #256	@,
	bl	memcpy	@
	cmp	r9, r4	@ Width, j
	bhi	.L566	@,
.L567:
	ldr	r3, [fp, #-48]	@, %sfp
	add	sl, sl, r9	@ ivtmp.2693, ivtmp.2693, Width
	ldr	r5, [fp, #4]	@, Height
	add	r0, r3, #1	@,,
	str	r0, [fp, #-48]	@, %sfp
	cmp	r5, r0	@,
	bhi	.L565	@,
	mov	r4, r9	@ Width, Width
.L564:
	ldr	r3, [fp, #-60]	@, %sfp
	ldr	ip, [fp, #4]	@, Height
	ldr	r5, [fp, #-72]	@, %sfp
	cmp	r3, ip	@,
	cmpeq	r5, r4	@,, Width
	movne	sl, #0	@,
	moveq	sl, #1	@,
	str	sl, [fp, #-80]	@, %sfp
	beq	.L692	@,
	ldr	r2, [fp, #-60]	@, %sfp
	ldr	r0, [r6, #488]	@ pY.2732, pY
	cmp	r2, #0	@,
	beq	.L571	@,
	ldr	r1, [fp, #28]	@, TopOffset
	sub	r7, r2, #1	@ tmp367,,
	ldr	r8, [fp, #20]	@, LeftOffset
	ldr	r2, [fp, #-64]	@, %sfp
	mla	sl, r4, r1, r8	@ tmp245, Width,,
	ldr	r1, [fp, #-72]	@, %sfp
	and	r8, r7, #1	@ tmp369, tmp367,
	mov	r7, #1	@ i.2733,
	add	r0, r0, sl	@ pPicAddr, pY.2732, tmp245
	add	r5, r0, r4	@ pPicAddr, pPicAddr, Width
	bl	klib_fwrite	@
	ldr	r2, [fp, #-60]	@, %sfp
	cmp	r2, r7	@,
	bls	.L571	@,
	cmp	r8, #0	@ tmp369,
	beq	.L680	@,
	mov	r0, r5	@, pPicAddr
	ldr	r1, [fp, #-72]	@, %sfp
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r7, #2	@ i.2733,
	bl	klib_fwrite	@
	ldr	sl, [fp, #-60]	@, %sfp
	add	r5, r5, r4	@ pPicAddr, pPicAddr, Width
	cmp	sl, r7	@, i.2733
	bls	.L571	@,
.L680:
	mov	r0, r5	@ pPicAddr, pPicAddr
	ldr	r8, [fp, #-72]	@ disp_width, %sfp
	ldr	sl, [fp, #-64]	@ fpYuv, %sfp
	mov	r9, r6	@ tmp334, tmp334
	ldr	r5, [fp, #-60]	@ disp_height, %sfp
.L572:
	add	r6, r0, r4	@ pPicAddr, pPicAddr, Width
	add	r3, r7, #1	@ tmp370, i.2733,
	mov	r1, r8	@, disp_width
	mov	r2, sl	@, fpYuv
	add	r7, r3, #1	@ i.2733, tmp370,
	bl	klib_fwrite	@
	mov	r0, r6	@, pPicAddr
	mov	r1, r8	@, disp_width
	mov	r2, sl	@, fpYuv
	bl	klib_fwrite	@
	cmp	r5, r7	@ disp_height, i.2733
	add	r0, r6, r4	@ pPicAddr, pPicAddr, Width
	bhi	.L572	@,
	mov	r6, r9	@ tmp334, tmp334
.L571:
	ldr	lr, [fp, #-56]	@, %sfp
	cmp	lr, #0	@,
	beq	.L569	@,
	ldr	r0, [fp, #12]	@, Stride
	mov	r9, r4	@ Width, Width
	ldr	sl, [fp, #-76]	@ Caddress, %sfp
	mov	r8, #0	@ ivtmp.2681,
	str	r8, [fp, #-48]	@ i.2739, %sfp
	mov	ip, r0, lsr #1	@,,
	str	ip, [fp, #-52]	@, %sfp
.L570:
	cmp	r9, #0	@ Width,
	beq	.L574	@,
	ldr	r1, [fp, #-48]	@, %sfp
	sub	ip, r9, #1	@ tmp364, Width,
	ldr	lr, [fp, #-52]	@, %sfp
	mov	r2, #256	@,
	and	r0, r1, #7	@ pretmp.2788,,
	ldr	r3, [r6, #488]	@ pY, pY
	mov	r4, r1, lsr #3	@ pretmp.2632,,
	ubfx	r5, ip, #8, #1	@ tmp365, tmp364,,
	mov	r7, r0, asl #8	@ tmp259, pretmp.2788,
	add	r0, r8, r3	@, ivtmp.2681, pY
	mla	r7, lr, r4, r7	@ pretmp.2633,, pretmp.2632, tmp259
	mov	r4, r2	@ j.2738,
	add	r1, sl, r7	@, Caddress, pretmp.2633
	bl	memcpy	@
	cmp	r9, r4	@ Width, j.2738
	bls	.L574	@,
	cmp	r5, #0	@ tmp365,
	beq	.L573	@,
	ldr	r3, [r6, #488]	@ pY, pY
	add	r1, r8, r4	@ tmp508, ivtmp.2681, j.2738
	add	r5, r7, #2048	@ tmp513, pretmp.2633,
	mov	r2, r4	@, j.2738
	add	r0, r1, r3	@, tmp508, pY
	add	r1, sl, r5	@, Caddress, tmp513
	bl	memcpy	@
	mov	r4, #512	@ j.2738,
	cmp	r9, r4	@ Width, j.2738
	bls	.L574	@,
.L573:
	mov	r1, r4, lsr #8	@ tmp250, j.2738,
	ldr	r3, [r6, #488]	@ pY, pY
	add	r5, r4, #256	@ tmp366, j.2738,
	add	ip, r8, r4	@ tmp247, ivtmp.2681, j.2738
	add	lr, r7, r1, asl #11	@, tmp252, pretmp.2633, tmp250,
	add	r0, ip, r3	@, tmp247, pY
	add	r1, sl, lr	@, Caddress, tmp252
	mov	r2, #256	@,
	mov	r4, r5, lsr #8	@ tmp420, tmp366,
	bl	memcpy	@
	ldr	r2, [r6, #488]	@ pY, pY
	add	r0, r8, r5	@ tmp417, ivtmp.2681, tmp366
	add	ip, r7, r4, asl #11	@, tmp422, pretmp.2633, tmp420,
	add	r4, r5, #256	@ j.2738, tmp366,
	add	r0, r0, r2	@, tmp417, pY
	add	r1, sl, ip	@, Caddress, tmp422
	mov	r2, #256	@,
	bl	memcpy	@
	cmp	r9, r4	@ Width, j.2738
	bhi	.L573	@,
.L574:
	ldr	r5, [fp, #-48]	@, %sfp
	add	r8, r8, r9	@ ivtmp.2681, ivtmp.2681, Width
	ldr	r2, [fp, #-56]	@, %sfp
	add	r0, r5, #1	@,,
	str	r0, [fp, #-48]	@, %sfp
	cmp	r2, r0	@,
	bhi	.L570	@,
	mov	r4, r9	@ Width, Width
.L569:
	ldr	sl, [fp, #16]	@, chroma_idc
	movw	r5, #:lower16:.LANCHOR0	@ tmp260,
	movt	r5, #:upper16:.LANCHOR0	@ tmp260,
	cmp	sl, #1	@,
	ldr	sl, [r6, #488]	@ tmp, pY
	beq	.L693	@,
	ldr	r1, [fp, #16]	@, chroma_idc
	cmp	r1, #0	@,
	beq	.L694	@,
.L576:
	ldr	r2, [fp, #-80]	@, %sfp
	cmp	r2, #0	@,
	bne	.L695	@,
	ldr	r9, [fp, #-60]	@, %sfp
	ldr	r3, [r6, #496]	@ pUl.2745, pUl
	movs	r8, r9, lsr #1	@ disp_chroma_height,,
	ldr	r9, [r6, #492]	@ pVl.2746, pVl
	beq	.L598	@,
	ldr	r4, [fp, #28]	@, TopOffset
	sub	r6, r8, #1	@ tmp353, disp_chroma_height,
	ldr	r0, [fp, #20]	@, LeftOffset
	ldr	sl, [fp, #-72]	@, %sfp
	ldr	lr, [fp, #-68]	@, %sfp
	mov	r5, r4, lsr #1	@ tmp279,,
	mov	r7, r0, lsr #1	@ tmp281,,
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r4, sl, lsr #1	@ pretmp.2629,,
	mla	sl, lr, r5, r7	@ D.44742,, tmp279, tmp281
	mov	r1, r4	@, pretmp.2629
	and	r7, r6, #1	@ tmp355, tmp353,
	mov	r6, #1	@ i.2747,
	add	r0, r3, sl	@ pCbPicAddr, pUl.2745, D.44742
	add	r5, r0, lr	@ pCbPicAddr, pCbPicAddr,
	bl	klib_fwrite	@
	cmp	r8, r6	@ disp_chroma_height,
	bls	.L663	@,
	cmp	r7, #0	@ tmp355,
	beq	.L674	@,
	mov	r0, r5	@, pCbPicAddr
	mov	r1, r4	@, pretmp.2629
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r6, #2	@ i.2747,
	bl	klib_fwrite	@
	ldr	r7, [fp, #-68]	@, %sfp
	cmp	r8, r6	@ disp_chroma_height, i.2747
	add	r5, r5, r7	@ pCbPicAddr, pCbPicAddr,
	bls	.L663	@,
.L674:
	str	r9, [fp, #-48]	@ pVl.2746, %sfp
	mov	r0, r5	@ pCbPicAddr, pCbPicAddr
	ldr	r9, [fp, #-68]	@ chrom_width, %sfp
	mov	r5, sl	@ D.44742, D.44742
	ldr	sl, [fp, #-64]	@ fpYuv, %sfp
.L581:
	add	r7, r0, r9	@ pCbPicAddr, pCbPicAddr, chrom_width
	add	r3, r6, #1	@ tmp356, i.2747,
	mov	r1, r4	@, pretmp.2629
	mov	r2, sl	@, fpYuv
	add	r6, r3, #1	@ i.2747, tmp356,
	bl	klib_fwrite	@
	mov	r0, r7	@, pCbPicAddr
	mov	r1, r4	@, pretmp.2629
	mov	r2, sl	@, fpYuv
	bl	klib_fwrite	@
	cmp	r8, r6	@ disp_chroma_height, i.2747
	add	r0, r7, r9	@ pCbPicAddr, pCbPicAddr, chrom_width
	bhi	.L581	@,
	ldr	r9, [fp, #-48]	@ pVl.2746, %sfp
	mov	sl, r5	@ D.44742, D.44742
.L663:
	add	r6, r9, sl	@ pCrPicAddr, pVl.2746, D.44742
	sub	ip, r8, #1	@ tmp349, disp_chroma_height,
	mov	r1, r4	@, pretmp.2629
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r0, r6	@, pCrPicAddr
	and	r7, ip, #1	@ tmp351, tmp349,
	bl	klib_fwrite	@
	ldr	r1, [fp, #-68]	@, %sfp
	cmp	r8, #1	@ disp_chroma_height,
	add	r5, r6, r1	@ pCrPicAddr, pCrPicAddr,
	mov	r6, #1	@ i.2742,
	bls	.L598	@,
	cmp	r7, #0	@ tmp351,
	beq	.L672	@,
	mov	r0, r5	@, pCrPicAddr
	mov	r1, r4	@, pretmp.2629
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r6, #2	@ i.2742,
	bl	klib_fwrite	@
	ldr	r0, [fp, #-68]	@, %sfp
	cmp	r8, r6	@ disp_chroma_height, i.2742
	add	r5, r5, r0	@ pCrPicAddr, pCrPicAddr,
	bls	.L598	@,
.L672:
	ldr	r9, [fp, #-68]	@ chrom_width, %sfp
	mov	r0, r5	@ pCrPicAddr, pCrPicAddr
	ldr	sl, [fp, #-64]	@ fpYuv, %sfp
.L582:
	add	r7, r0, r9	@ pCrPicAddr, pCrPicAddr, chrom_width
	add	lr, r6, #1	@ tmp352, i.2742,
	mov	r1, r4	@, pretmp.2629
	mov	r2, sl	@, fpYuv
	add	r6, lr, #1	@ i.2742, tmp352,
	bl	klib_fwrite	@
	mov	r0, r7	@, pCrPicAddr
	mov	r1, r4	@, pretmp.2629
	mov	r2, sl	@, fpYuv
	bl	klib_fwrite	@
	cmp	r8, r6	@ disp_chroma_height, i.2742
	add	r0, r7, r9	@ pCrPicAddr, pCrPicAddr, chrom_width
	bhi	.L582	@,
.L598:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L563:
	ldr	r2, [fp, #4]	@, Height
	subs	r6, r6, #1	@, PicStructure,
	movne	r6, #1	@
	str	r6, [fp, #-60]	@, %sfp
	cmp	r2, r6	@,
	movwls	r6, #:lower16:.LANCHOR0	@ tmp454,
	movtls	r6, #:upper16:.LANCHOR0	@ tmp454,
	bls	.L583	@,
	ldr	r9, [fp, #-60]	@, %sfp
	movw	r6, #:lower16:.LANCHOR0	@ tmp454,
	movt	r6, #:upper16:.LANCHOR0	@ tmp454,
	mov	sl, r5	@ Yaddress, Yaddress
	str	r9, [fp, #-48]	@, %sfp
	mov	r9, r4	@ Width, Width
.L584:
	cmp	r9, #0	@ Width,
	beq	.L586	@,
	ldr	r2, [fp, #-48]	@, %sfp
	sub	r5, r9, #1	@ tmp393, Width,
	ldr	ip, [fp, #12]	@, Stride
	ubfx	r5, r5, #8, #1	@ tmp394, tmp393,,
	and	r1, r2, #15	@ pretmp.2787,,
	ldr	lr, [r6, #488]	@ pY, pY
	mov	r7, r2, lsr #4	@ pretmp.2780,,
	mov	r8, r2, lsr #1	@ pretmp.2782,,
	mov	r2, #256	@,
	mul	r4, ip, r7	@ tmp296,, pretmp.2780
	mla	r7, r1, r2, r4	@ pretmp.2625, pretmp.2787,, tmp296
	mov	r4, r2	@ j.2755,
	mul	r8, r9, r8	@ pretmp.2781, Width, pretmp.2782
	add	r1, sl, r7	@, Yaddress, pretmp.2625
	add	r0, r8, lr	@, pretmp.2781, pY
	bl	memcpy	@
	cmp	r9, r4	@ Width, j.2755
	bls	.L586	@,
	cmp	r5, #0	@ tmp394,
	beq	.L585	@,
	ldr	lr, [r6, #488]	@ pY, pY
	add	r0, r4, r8	@ tmp534, j.2755, pretmp.2781
	add	ip, r7, #4096	@ tmp539, pretmp.2625,
	mov	r2, r4	@, j.2755
	add	r0, r0, lr	@, tmp534, pY
	add	r1, sl, ip	@, Yaddress, tmp539
	bl	memcpy	@
	mov	r4, #512	@ j.2755,
	cmp	r9, r4	@ Width, j.2755
	bls	.L586	@,
.L585:
	mov	r1, r4, lsr #8	@ tmp287, j.2755,
	ldr	r2, [r6, #488]	@ pY, pY
	add	r5, r4, #256	@ tmp395, j.2755,
	add	lr, r4, r8	@ tmp284, j.2755, pretmp.2781
	add	ip, r7, r1, asl #12	@, tmp289, pretmp.2625, tmp287,
	add	r0, lr, r2	@, tmp284, pY
	add	r1, sl, ip	@, Yaddress, tmp289
	mov	r2, #256	@,
	mov	r4, r5, lsr #8	@ tmp459, tmp395,
	bl	memcpy	@
	ldr	r3, [r6, #488]	@ pY, pY
	add	r0, r5, r8	@ tmp456, tmp395, pretmp.2781
	add	r1, r7, r4, asl #12	@, tmp461, pretmp.2625, tmp459,
	mov	r2, #256	@,
	add	r4, r5, #256	@ j.2755, tmp395,
	add	r0, r0, r3	@, tmp456, pY
	add	r1, sl, r1	@, Yaddress, tmp461
	bl	memcpy	@
	cmp	r9, r4	@ Width, j.2755
	bhi	.L585	@,
.L586:
	ldr	r3, [fp, #-48]	@, %sfp
	ldr	r7, [fp, #4]	@, Height
	add	r0, r3, #2	@,,
	str	r0, [fp, #-48]	@, %sfp
	cmp	r7, r0	@,
	bhi	.L584	@,
	mov	r4, r9	@ Width, Width
.L583:
	ldr	lr, [fp, #4]	@, Height
	ldr	r0, [r6, #488]	@, pY
	ldr	r2, [fp, #-64]	@, %sfp
	mul	r3, r4, lr	@ tmp299, Width,
	mov	r1, r3, lsr #1	@, tmp299,
	bl	klib_fwrite	@
	ldr	r0, [fp, #-56]	@, %sfp
	cmp	r0, #0	@,
	beq	.L587	@,
	ldr	r1, [fp, #12]	@, Stride
	mov	r8, #0	@ ivtmp.2722,
	ldr	sl, [fp, #-76]	@ Caddress, %sfp
	str	r8, [fp, #-48]	@ i.2766, %sfp
	mov	r9, r1, lsr #1	@,,
	str	r9, [fp, #-52]	@, %sfp
	mov	r9, r4	@ Width, Width
.L588:
	cmp	r9, #0	@ Width,
	beq	.L590	@,
	ldr	r7, [fp, #-48]	@, %sfp
	mov	r2, #256	@,
	ldr	ip, [fp, #-52]	@, %sfp
	sub	r5, r9, #1	@ tmp388, Width,
	and	r1, r7, #7	@ pretmp.2797,,
	ldr	r4, [r6, #488]	@ pY, pY
	mov	r0, r7, lsr #3	@ pretmp.2794,,
	ubfx	r5, r5, #8, #1	@ tmp389, tmp388,,
	mul	lr, ip, r0	@ tmp314,, pretmp.2794
	add	r0, r8, r4	@, ivtmp.2722, pY
	mla	r7, r1, r2, lr	@ pretmp.2623, pretmp.2797,, tmp314
	mov	r4, r2	@ j.2765,
	add	r1, sl, r7	@, Caddress, pretmp.2623
	bl	memcpy	@
	cmp	r9, r4	@ Width, j.2765
	bls	.L590	@,
	cmp	r5, #0	@ tmp389,
	beq	.L589	@,
	ldr	r3, [r6, #488]	@ pY, pY
	add	r1, r8, r4	@ tmp527, ivtmp.2722, j.2765
	add	lr, r7, #2048	@ tmp532, pretmp.2623,
	mov	r2, r4	@, j.2765
	add	r0, r1, r3	@, tmp527, pY
	add	r1, sl, lr	@, Caddress, tmp532
	bl	memcpy	@
	mov	r4, #512	@ j.2765,
	cmp	r9, r4	@ Width, j.2765
	bls	.L590	@,
.L589:
	mov	r1, r4, lsr #8	@ tmp305, j.2765,
	ldr	ip, [r6, #488]	@ pY, pY
	add	r5, r4, #256	@ tmp390, j.2765,
	add	r0, r8, r4	@ tmp302, ivtmp.2722, j.2765
	add	lr, r7, r1, asl #11	@, tmp307, pretmp.2623, tmp305,
	add	r0, r0, ip	@, tmp302, pY
	add	r1, sl, lr	@, Caddress, tmp307
	mov	r2, #256	@,
	mov	r4, r5, lsr #8	@ tmp475, tmp390,
	bl	memcpy	@
	ldr	r3, [r6, #488]	@ pY, pY
	add	r2, r8, r5	@ tmp472, ivtmp.2722, tmp390
	add	ip, r7, r4, asl #11	@, tmp477, pretmp.2623, tmp475,
	add	r4, r5, #256	@ j.2765, tmp390,
	add	r0, r2, r3	@, tmp472, pY
	add	r1, sl, ip	@, Caddress, tmp477
	mov	r2, #256	@,
	bl	memcpy	@
	cmp	r9, r4	@ Width, j.2765
	bhi	.L589	@,
.L590:
	ldr	r3, [fp, #-48]	@, %sfp
	add	r8, r8, r9	@ ivtmp.2722, ivtmp.2722, Width
	ldr	r2, [fp, #-56]	@, %sfp
	add	r7, r3, #1	@,,
	str	r7, [fp, #-48]	@, %sfp
	cmp	r2, r7	@,
	bhi	.L588	@,
	mov	r4, r9	@ Width, Width
.L587:
	ldr	r2, [fp, #16]	@, chroma_idc
	ldr	r7, [r6, #488]	@ pY.2767, pY
	cmp	r2, #1	@,
	beq	.L696	@,
	ldr	r4, [fp, #16]	@, chroma_idc
	cmp	r4, #0	@,
	bne	.L592	@,
	ldr	r2, [fp, #-56]	@, %sfp
	ldr	r3, [fp, #-60]	@, %sfp
	cmp	r2, r3	@,
	bls	.L596	@,
	ldr	r1, [fp, #-56]	@, %sfp
	add	r3, r3, #2	@ i.2748,,
	ldr	ip, [fp, #-60]	@, %sfp
	cmp	r1, r3	@, i.2748
	mvn	r0, ip	@ tmp382,
	add	lr, r0, r1	@ tmp383, tmp382,
	ubfx	r2, lr, #1, #1	@ tmp384, tmp383,,
	bls	.L596	@,
	cmp	r2, #0	@ tmp384,
	beq	.L686	@,
	ldr	r2, [fp, #-56]	@, %sfp
	add	r3, r3, #2	@ i.2748, i.2748,
	cmp	r2, r3	@, i.2748
	bls	.L596	@,
.L686:
	ldr	r2, [fp, #-56]	@ chrom_height, %sfp
.L601:
	add	r3, r3, #4	@ i.2748, i.2748,
	cmp	r2, r3	@ chrom_height, i.2748
	bhi	.L601	@,
.L596:
	mov	r1, #128	@,
	mov	r2, #1048576	@,
	ldr	r0, [r6, #492]	@, pVl
	bl	memset	@
	ldr	r0, [r6, #496]	@, pUl
	mov	r1, #128	@,
	mov	r2, #1048576	@,
	bl	memset	@
.L592:
	ldr	r2, [fp, #-68]	@, %sfp
	ldr	r3, [fp, #-56]	@, %sfp
	ldr	r0, [r6, #496]	@, pUl
	mul	r4, r2, r3	@ tmp329,,
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r4, r4, lsr #1	@ D.44777, tmp329,
.L691:
	mov	r1, r4	@, D.44777
	bl	klib_fwrite	@
	ldr	r0, [r6, #492]	@, pVl
	mov	r1, r4	@, D.44777
	ldr	r2, [fp, #-64]	@, %sfp
	bl	klib_fwrite	@
	b	.L598	@
.L692:
	mul	r1, r4, ip	@, Width,
	ldr	r0, [r6, #488]	@, pY
	ldr	r2, [fp, #-64]	@, %sfp
	bl	klib_fwrite	@
	b	.L571	@
.L693:
	ldr	r2, [fp, #-56]	@, %sfp
	cmp	r2, #0	@,
	beq	.L576	@,
	ldr	r5, [fp, #-68]	@ chrom_width, %sfp
	mov	r1, #0	@ ivtmp.2673,
	mov	r9, r1	@ i.2741, ivtmp.2673
	str	r4, [fp, #-48]	@ Width, %sfp
.L577:
	cmp	r5, #0	@ chrom_width,
	beq	.L579	@,
	ldrb	r0, [sl, #0]	@ zero_extendqisi2	@ tmp443,* tmp
	mov	r2, #1	@ j.2740,
	ldr	lr, [r6, #492]	@ pVl, pVl
	cmp	r5, r2	@ chrom_width, j.2740
	sub	r4, r5, #1	@ tmp357, chrom_width,
	add	r3, sl, #2	@ ivtmp.2660, tmp,
	and	r4, r4, r2	@ tmp359, tmp357,
	strb	r0, [lr, r1]	@ tmp443,* ivtmp.2673
	ldr	r0, [r6, #496]	@ pUl, pUl
	ldrb	ip, [sl, #1]	@ zero_extendqisi2	@ tmp445,
	strb	ip, [r0, r1]	@ tmp445,* ivtmp.2673
	bls	.L579	@,
	cmp	r4, #0	@ tmp359,
	beq	.L578	@,
	ldrb	r4, [r3, #0]	@ zero_extendqisi2	@ tmp505,* ivtmp.2660
	add	lr, r1, r2	@ D.44710, ivtmp.2673, j.2740
	ldr	r0, [r6, #492]	@ pVl, pVl
	mov	r2, #2	@ j.2740,
	cmp	r5, r2	@ chrom_width, j.2740
	strb	r4, [r0, lr]	@ tmp505,* D.44710
	ldrb	r4, [r3, #1]	@ zero_extendqisi2	@ tmp507,
	add	r3, r3, r2	@ ivtmp.2660, ivtmp.2660,
	ldr	ip, [r6, #496]	@ pUl, pUl
	strb	r4, [ip, lr]	@ tmp507,* D.44710
	bls	.L579	@,
.L578:
	ldrb	r8, [r3, #0]	@ zero_extendqisi2	@ tmp263,* ivtmp.2660
	add	ip, r1, r2	@ D.44710, ivtmp.2673, j.2740
	ldr	r4, [r6, #492]	@ pVl, pVl
	add	r2, r2, #1	@ tmp360, j.2740,
	add	lr, r1, r2	@ D.44710, ivtmp.2673, tmp360
	add	r0, r3, #2	@ tmp361, ivtmp.2660,
	add	r2, r2, #1	@ j.2740, tmp360,
	strb	r8, [r4, ip]	@ tmp263,* D.44710
	cmp	r5, r2	@ chrom_width, j.2740
	ldrb	r8, [r3, #1]	@ zero_extendqisi2	@ tmp267,
	ldr	r7, [r6, #496]	@ pUl, pUl
	strb	r8, [r7, ip]	@ tmp267,* D.44710
	ldrb	r7, [r3, #2]	@ zero_extendqisi2	@ tmp436,
	add	r3, r0, #2	@ ivtmp.2660, tmp361,
	ldr	r4, [r6, #492]	@ pVl, pVl
	strb	r7, [r4, lr]	@ tmp436,* D.44710
	ldr	r4, [r6, #496]	@ pUl, pUl
	ldrb	ip, [r0, #1]	@ zero_extendqisi2	@ tmp438,
	strb	ip, [r4, lr]	@ tmp438,* D.44710
	bhi	.L578	@,
.L579:
	ldr	r3, [fp, #-56]	@, %sfp
	add	r9, r9, #1	@ i.2741, i.2741,
	add	r1, r1, r5	@ ivtmp.2673, ivtmp.2673, chrom_width
	cmp	r3, r9	@, i.2741
	bls	.L576	@,
	ldr	lr, [fp, #-48]	@, %sfp
	add	sl, sl, lr	@ tmp, tmp,
	b	.L577	@
.L696:
	ldr	r3, [fp, #-56]	@, %sfp
	cmp	r3, #0	@,
	beq	.L592	@,
	ldr	r8, [fp, #-60]	@, %sfp
	mov	sl, r4, asl #1	@ pretmp.2620, Width,
	mla	r7, r4, r8, r7	@ tmp.2768, Width,, pY.2767
	ldr	r4, [fp, #-68]	@ chrom_width, %sfp
	mov	r8, #0	@ i.2775,
.L593:
	cmp	r4, #0	@ chrom_width,
	beq	.L595	@,
	mov	r3, r8, lsr #1	@ pretmp.2786, i.2775,
	ldr	r1, [r6, #492]	@ pVl, pVl
	ldrb	r0, [r7, #0]	@ zero_extendqisi2	@ tmp498,* tmp.2768
	mov	r2, #1	@ j.2774,
	mul	lr, r4, r3	@ pretmp.2783, chrom_width, pretmp.2786
	cmp	r4, r2	@ chrom_width, j.2774
	sub	ip, r4, #1	@ tmp376, chrom_width,
	add	r3, r7, #2	@ ivtmp.2697, tmp.2768,
	and	ip, ip, r2	@ tmp378, tmp376,
	strb	r0, [r1, lr]	@ tmp498,* pretmp.2783
	ldr	r1, [r6, #496]	@ pUl, pUl
	ldrb	r0, [r7, #1]	@ zero_extendqisi2	@ tmp500,
	strb	r0, [r1, lr]	@ tmp500,* pretmp.2783
	bls	.L595	@,
	cmp	ip, #0	@ tmp378,
	beq	.L594	@,
	ldrb	ip, [r3, #0]	@ zero_extendqisi2	@ tmp524,* ivtmp.2697
	add	r1, r2, lr	@ D.44758, j.2774, pretmp.2783
	ldr	r0, [r6, #492]	@ pVl, pVl
	mov	r2, #2	@ j.2774,
	cmp	r4, r2	@ chrom_width, j.2774
	strb	ip, [r0, r1]	@ tmp524,* D.44758
	ldrb	ip, [r3, #1]	@ zero_extendqisi2	@ tmp526,
	add	r3, r3, r2	@ ivtmp.2697, ivtmp.2697,
	ldr	r0, [r6, #496]	@ pUl, pUl
	strb	ip, [r0, r1]	@ tmp526,* D.44758
	bls	.L595	@,
.L594:
	ldrb	r9, [r3, #0]	@ zero_extendqisi2	@ tmp319,* ivtmp.2697
	add	ip, r2, lr	@ D.44758, j.2774, pretmp.2783
	ldr	r5, [r6, #492]	@ pVl, pVl
	add	r2, r2, #1	@ tmp379, j.2774,
	add	r1, r2, lr	@ D.44758, tmp379, pretmp.2783
	add	r0, r3, #2	@ tmp380, ivtmp.2697,
	add	r2, r2, #1	@ j.2774, tmp379,
	strb	r9, [r5, ip]	@ tmp319,* D.44758
	cmp	r4, r2	@ chrom_width, j.2774
	ldrb	r9, [r3, #1]	@ zero_extendqisi2	@ tmp323,
	ldr	r5, [r6, #496]	@ pUl, pUl
	strb	r9, [r5, ip]	@ tmp323,* D.44758
	ldrb	r5, [r3, #2]	@ zero_extendqisi2	@ tmp491,
	add	r3, r0, #2	@ ivtmp.2697, tmp380,
	ldr	ip, [r6, #492]	@ pVl, pVl
	strb	r5, [ip, r1]	@ tmp491,* D.44758
	ldr	ip, [r6, #496]	@ pUl, pUl
	ldrb	r0, [r0, #1]	@ zero_extendqisi2	@ tmp493,
	strb	r0, [ip, r1]	@ tmp493,* D.44758
	bhi	.L594	@,
.L595:
	ldr	lr, [fp, #-56]	@, %sfp
	add	r8, r8, #2	@ i.2775, i.2775,
	cmp	lr, r8	@, i.2775
	bls	.L592	@,
	add	r7, r7, sl	@ tmp.2768, tmp.2768, pretmp.2620
	b	.L593	@
.L694:
	mov	r1, #128	@,
	mov	r2, #1048576	@,
	ldr	r0, [r5, #492]	@, pVl
	bl	memset	@
	ldr	r0, [r5, #496]	@, pUl
	mov	r1, #128	@,
	mov	r2, #1048576	@,
	bl	memset	@
	b	.L576	@
.L695:
	ldr	r3, [fp, #-68]	@, %sfp
	ldr	ip, [fp, #-56]	@, %sfp
	ldr	r2, [fp, #-64]	@, %sfp
	ldr	r0, [r6, #496]	@, pUl
	mul	r4, r3, ip	@ D.44737,,
	b	.L691	@
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
	bhi	.L698	@,
	movw	r2, #:lower16:.LANCHOR0	@ tmp159,
	movt	r2, #:upper16:.LANCHOR0	@ tmp159,
	ldr	r5, [r2, r0, asl #2]	@ D.41036, s_pstVfmwChan
	cmp	r5, #0	@ D.41036,
	beq	.L698	@,
	ldr	r3, [r5, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r3, #1	@ <variable>.s32IsOpen,
	beq	.L719	@,
.L701:
	mov	r4, #0	@ pDecParam,
.L700:
	mov	r0, r4	@, pDecParam
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L698:
	mov	r3, r0	@, ChanId
	movw	r2, #4403	@,
	mov	r4, #0	@ pDecParam,
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC55	@,
	movt	r1, #:upper16:.LC55	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, pDecParam
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L719:
	ldr	r0, [r5, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #1	@ <variable>.s32IsRun,
	bne	.L701	@,
	ldr	r1, [r5, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r1, #16	@ <variable>.eVidStd,
	ldrls	pc, [pc, r1, asl #2]	@ <variable>.eVidStd
	b	.L701	@
.L715:
	.word	.L703
	.word	.L718
	.word	.L705
	.word	.L718
	.word	.L701
	.word	.L718
	.word	.L718
	.word	.L701
	.word	.L718
	.word	.L718
	.word	.L711
	.word	.L711
	.word	.L711
	.word	.L718
	.word	.L701
	.word	.L713
	.word	.L714
.L711:
	ldr	r4, [r2, #500]	@ g_VdmCharacter, g_VdmCharacter
	tst	r4, #1	@ g_VdmCharacter,
	beq	.L701	@,
.L718:
	movw	r0, #:lower16:251500	@ tmp156,
	movt	r0, #:upper16:251500	@ tmp156,
	ldr	r4, [r5, r0]	@ pDecParam,
.L716:
	cmp	r4, #0	@ pDecParam,
	beq	.L700	@,
	bl	OSAL_GetTimeInMs	@
	str	r0, [r5, #44]	@, <variable>.u32timeLastDecParamReady
	b	.L700	@
.L703:
	movw	r2, #:lower16:251856	@ tmp143,
	movt	r2, #:upper16:251856	@ tmp143,
	ldr	r4, [r5, r2]	@ pDecParam,
	b	.L716	@
.L714:
	movw	ip, #:lower16:2211688	@ tmp144,
	movt	ip, #:upper16:2211688	@ tmp144,
	ldr	r4, [r5, ip]	@ pDecParam,
	b	.L716	@
.L713:
	movw	r1, #:lower16:251724	@ tmp157,
	movt	r1, #:upper16:251724	@ tmp157,
	ldr	r4, [r5, r1]	@ pDecParam,
	b	.L716	@
.L705:
	movw	r3, #:lower16:252532	@ tmp146,
	movt	r3, #:upper16:252532	@ tmp146,
	ldr	r4, [r5, r3]	@ pDecParam,
	b	.L716	@
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
	bhi	.L721	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp144,
	movt	r4, #:upper16:.LANCHOR0	@ tmp144,
	ldr	r3, [r4, r0, asl #2]	@ D.41063, s_pstVfmwChan
	cmp	r3, #0	@ D.41063,
	beq	.L721	@,
	ldr	r1, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r1, #1	@ <variable>.s32IsOpen,
	bne	.L724	@,
	ldr	r5, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r5, #1	@ <variable>.s32IsRun,
	beq	.L725	@,
.L724:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC56	@,
	movt	r1, #:upper16:.LC56	@,
	bl	dprint_vfmw	@
	mov	r3, #0	@ D.41065,
.L723:
	mov	r0, r3	@, D.41065
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L721:
	mov	r3, r2	@, ChanId
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC55	@,
	movw	r2, #4513	@,
	movt	r1, #:upper16:.LC55	@,
	bl	dprint_vfmw	@
	mov	r3, #0	@ D.41065,
	b	.L723	@
.L725:
	str	r0, [fp, #-32]	@ tmp2,
	bl	VCTRL_GetDecParam	@
	ldr	r2, [fp, #-32]	@,
	subs	r6, r0, #0	@ pDecParam,
	beq	.L731	@,
	ldr	r0, [r4, r2, asl #2]	@ tmp154, s_pstVfmwChan
	mov	ip, #0	@ tmp155,
	mov	r3, ip	@ D.41065, tmp155
	str	ip, [r0, #828]	@ tmp155, <variable>.s32CountNoDecparamFlag
	ldr	r2, [r4, r2, asl #2]	@ tmp157, s_pstVfmwChan
	str	ip, [r2, #832]	@ tmp155, <variable>.u32NoDecparamStartTime
	b	.L723	@
.L731:
	ldr	r3, [r4, r2, asl #2]	@ temp.2844, s_pstVfmwChan
	ldr	r7, [r3, #828]	@ <variable>.s32CountNoDecparamFlag, <variable>.s32CountNoDecparamFlag
	cmp	r7, #0	@ <variable>.s32CountNoDecparamFlag,
	beq	.L732	@,
	str	r2, [fp, #-32]	@,
	bl	OSAL_GetTimeInMs	@
	ldr	r2, [fp, #-32]	@,
	ldr	r3, [r4, r2, asl #2]	@ temp.2848, s_pstVfmwChan
	ldr	r1, [r3, #832]	@ D.41086, <variable>.u32NoDecparamStartTime
	cmp	r0, r1	@ tmp, D.41086
	bls	.L728	@,
	rsb	lr, r1, r0	@ tmp160, D.41086, tmp
	cmp	lr, #40	@ tmp160,
	movls	r3, r6	@ D.41065, pDecParam
	bls	.L723	@,
.L728:
	str	r6, [r3, #828]	@ pDecParam, <variable>.s32CountNoDecparamFlag
	mov	r3, r5	@ D.41065, <variable>.s32IsRun
	ldr	r1, [r4, r2, asl #2]	@ tmp167, s_pstVfmwChan
	str	r6, [r1, #832]	@ pDecParam, <variable>.u32NoDecparamStartTime
	b	.L723	@
.L732:
	str	r5, [r3, #828]	@ <variable>.s32IsRun, <variable>.s32CountNoDecparamFlag
	ldr	r4, [r4, r2, asl #2]	@ temp.2845, s_pstVfmwChan
	bl	OSAL_GetTimeInMs	@
	mov	r3, r7	@ D.41065, <variable>.s32CountNoDecparamFlag
	str	r0, [r4, #832]	@, <variable>.u32NoDecparamStartTime
	b	.L723	@
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
	b	.L738	@
.L736:
	bl	msleep	@
	ldr	r1, [r4, #140]	@ s_VfmwCTrl.eTaskState, s_VfmwCTrl.eTaskState
	mov	r0, #10	@,
	cmp	r1, #2	@ s_VfmwCTrl.eTaskState,
	beq	.L743	@,
	bl	msleep	@
	cmp	r5, #50	@ i,
	beq	.L745	@,
.L738:
	ldr	r3, [r4, #140]	@ s_VfmwCTrl.eTaskState, s_VfmwCTrl.eTaskState
	add	r5, r5, #1	@ tmp147, i,
	mov	r0, #10	@,
	add	r5, r5, #1	@ i, tmp147,
	cmp	r3, #2	@ s_VfmwCTrl.eTaskState,
	bne	.L736	@,
.L743:
	mov	r2, #0	@ tmp143,
	mov	r0, #0	@ ret,
	str	r2, [r4, #144]	@ tmp143, s_VfmwCTrl.eTaskCommand
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L745:
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
	b	.L751	@
.L749:
	bl	msleep	@
	ldr	r2, [r4, #140]	@ s_VfmwCTrl.eTaskState, s_VfmwCTrl.eTaskState
	mov	r0, #10	@,
	cmp	r2, #1	@ s_VfmwCTrl.eTaskState,
	beq	.L756	@,
	bl	msleep	@
	cmp	r5, #50	@ i,
	beq	.L758	@,
.L751:
	ldr	r1, [r4, #140]	@ s_VfmwCTrl.eTaskState, s_VfmwCTrl.eTaskState
	add	r5, r5, #1	@ tmp147, i,
	mov	r0, #10	@,
	add	r5, r5, #1	@ i, tmp147,
	cmp	r1, #1	@ s_VfmwCTrl.eTaskState,
	bne	.L749	@,
.L756:
	mov	ip, #0	@ tmp143,
	mov	r0, #0	@ ret,
	str	ip, [r4, #144]	@ tmp143, s_VfmwCTrl.eTaskCommand
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L758:
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
	add	r0, r4, #504	@, tmp137,
	mov	r6, r1	@ ChanCtrlState, ChanCtrlState
	bl	OSAL_SpinLockIRQ	@
	cmp	r6, #1	@ ChanCtrlState,
	beq	.L762	@,
	bcs	.L768	@,
	mov	r3, #0	@ tmp144,
	add	r4, r4, r5, asl #2	@, tmp142, tmp137, ChanID,
	mov	r6, r3	@ ret, tmp144
	str	r3, [r4, #516]	@ tmp144, s_ChanControlState
.L764:
	ldr	r0, .L770	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r6	@, ret
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L768:
	cmp	r6, #2	@ ChanCtrlState,
	beq	.L763	@,
	mov	r6, #0	@ ret,
.L769:
	ldr	r0, .L770	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r6	@, ret
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L763:
	add	r4, r4, r5, asl #2	@, tmp160, tmp137, ChanID,
	ldr	r1, [r4, #516]	@ tmp162, s_ChanControlState
	cmp	r1, #1	@ tmp162,
	beq	.L765	@,
	str	r6, [r4, #516]	@ ChanCtrlState, s_ChanControlState
	mov	r6, #0	@ ret,
	b	.L769	@
.L762:
	add	r4, r4, r5, asl #2	@, tmp148, tmp137, ChanID,
	ldr	r0, [r4, #516]	@ tmp150, s_ChanControlState
	cmp	r0, #0	@ tmp150,
	streq	r6, [r4, #516]	@ ChanCtrlState, s_ChanControlState
	moveq	r6, r0	@ ret, tmp150
	beq	.L764	@,
.L765:
	mvn	r6, #0	@ ret,
	ldr	r0, .L770	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r6	@, ret
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L771:
	.align	2
.L770:
	.word	.LANCHOR0+504
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
	ldr	r4, .L782	@ ivtmp.2965,
	mov	r5, r0	@ proc_name, proc_name
	add	r7, r4, #768	@ D.47158, ivtmp.2965,
	b	.L775	@
.L773:
	add	r4, r4, #24	@ ivtmp.2965, ivtmp.2965,
	mov	r1, r4	@, ivtmp.2965
	bl	strncmp	@
	subs	r6, r0, #0	@ tmp143,
	beq	.L780	@,
	add	r4, r4, #24	@ ivtmp.2965, ivtmp.2965,
	cmp	r4, r7	@ ivtmp.2965, D.47158
	beq	.L781	@,
.L775:
	mov	r2, #16	@,
	mov	r1, r4	@, ivtmp.2965
	mov	r0, r5	@, proc_name
	bl	strncmp	@
	mov	r2, #16	@,
	subs	r6, r0, #0	@ tmp143,
	mov	r0, r5	@, proc_name
	bne	.L773	@,
.L780:
	mov	r0, r5	@, proc_name
	mov	r1, r6	@, tmp143
	bl	remove_proc_entry	@
	mov	r0, r4	@, ivtmp.2965
	mov	r1, #16	@,
	bl	__memzero	@
	str	r6, [r4, #20]	@ tmp143, <variable>.write
	str	r6, [r4, #16]	@ tmp143, <variable>.read
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L781:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L783:
	.align	2
.L782:
	.word	.LANCHOR0+580
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
	ldr	r0, .L790	@,
	mov	r1, #28	@,
	bl	__memzero	@
	ldmfd	sp, {fp, sp, pc}	@
.L791:
	.align	2
.L790:
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
	ldr	r3, .L807	@ tmp187,
	mov	sl, r2	@ write, write
	mov	r7, r0	@ proc_name, proc_name
	mov	r8, r1	@ read, read
	mov	r5, #0	@ i,
	mov	r2, r3	@ ivtmp.3072, tmp187
	b	.L796	@
.L793:
	ldr	r2, [r1, #16]	@ <variable>.read, <variable>.read
	add	r5, r5, #1	@ i, i,
	cmp	r2, #0	@ <variable>.read,
	mov	r2, r5	@ tmp189, i
	beq	.L805	@,
.L800:
	add	r5, r2, #1	@ i, tmp189,
	add	r2, r1, #24	@ ivtmp.3072, tmp190,
	cmp	r5, #32	@ i,
	beq	.L794	@,
.L796:
	ldr	r0, [r2, #16]	@ <variable>.read, <variable>.read
	add	r1, r2, #24	@ tmp190, ivtmp.3072,
	cmp	r0, #0	@ <variable>.read,
	bne	.L793	@,
	ldr	r6, [r2, #20]	@ <variable>.write, <variable>.write
	cmp	r6, #0	@ <variable>.write,
	bne	.L793	@,
.L804:
	add	r4, r5, r5, asl #1	@, tmp180, i, i,
	mov	r1, r7	@, proc_name
	mov	r2, #16	@,
	add	r4, r3, r4, asl #3	@, proc, tmp187, tmp180,
	mov	r0, r4	@, proc
	bl	strncpy	@
	cmp	r5, #31	@ i,
	strb	r6, [r4, #15]	@ <variable>.write, <variable>.proc_name
	str	r8, [r4, #16]	@ read, <variable>.read
	str	sl, [r4, #20]	@ write, <variable>.write
	bls	.L806	@,
.L794:
	mvn	r0, #0	@ D.44162,
.L797:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L805:
	ldr	r6, [r1, #20]	@ <variable>.write, <variable>.write
	cmp	r6, #0	@ <variable>.write,
	bne	.L800	@,
	b	.L804	@
.L806:
	mov	r0, r7	@, proc_name
	mov	r1, #420	@,
	mov	r2, #0	@,
	ldr	r3, .L807+4	@,
	str	r4, [sp, #0]	@ proc,
	bl	proc_create_data	@
	cmp	r0, #0	@,
	movne	r0, #0	@ D.44162,
	bne	.L797	@,
	b	.L794	@
.L808:
	.align	2
.L807:
	.word	.LANCHOR0+580
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
	subs	r5, r0, #0	@ ret.3104,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3104, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3105,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3105, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3106,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3106, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3107,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3107, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3108,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3108, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3109,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3109, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3110,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3110, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3111,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3111, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3112,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3112, name
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L810	@,
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
	subs	r5, r0, #0	@ ret.3114,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3114, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3115,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3115, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3116,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3116, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3117,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3117, name
	bl	vfmw_proc_create	@
	subs	r5, r0, #0	@ ret.3118,
	bne	.L810	@,
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
	strb	r5, [fp, #-21]	@ ret.3118, name
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L810	@,
	movw	r0, #:lower16:.LC58	@,
	movw	r1, #:lower16:vfmw_read_proc	@,
	movt	r0, #:upper16:.LC58	@,
	movt	r1, #:upper16:vfmw_read_proc	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	beq	.L813	@,
.L810:
	mvn	r0, #0	@ D.44206,
.L811:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L813:
	movw	r0, #:lower16:.LC59	@,
	movw	r1, #:lower16:vfmw_read_proc_dbg	@,
	movt	r0, #:upper16:.LC59	@,
	movt	r1, #:upper16:vfmw_read_proc_dbg	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L810	@,
	movw	r0, #:lower16:.LC60	@,
	movw	r1, #:lower16:vfmw_read_proc_prn	@,
	movt	r0, #:upper16:.LC60	@,
	movt	r1, #:upper16:vfmw_read_proc_prn	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L810	@,
	movw	r0, #:lower16:.LC61	@,
	movw	r1, #:lower16:vfmw_read_proc_scd	@,
	movt	r0, #:upper16:.LC61	@,
	movt	r1, #:upper16:vfmw_read_proc_scd	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L810	@,
	movw	r0, #:lower16:.LC62	@,
	movw	r1, #:lower16:vfmw_read_proc_dec	@,
	movt	r0, #:upper16:.LC62	@,
	movt	r1, #:upper16:vfmw_read_proc_dec	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L810	@,
	movw	r0, #:lower16:.LC63	@,
	movw	r1, #:lower16:vfmw_read_proc_lwd	@,
	movt	r0, #:upper16:.LC63	@,
	movt	r1, #:upper16:vfmw_read_proc_lwd	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@,
	bne	.L810	@,
	movw	r0, #:lower16:.LC64	@,
	movw	r1, #:lower16:vfmw_read_proc_chn	@,
	movt	r0, #:upper16:.LC64	@,
	movt	r1, #:upper16:vfmw_read_proc_chn	@,
	movw	r2, #:lower16:vfmw_write_proc	@,
	movt	r2, #:upper16:vfmw_write_proc	@,
	bl	vfmw_proc_create	@
	cmp	r0, #0	@ ret.3103
	beq	.L811	@,
	b	.L810	@
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
	subs	r2, r0, #0	@ D.44114,
	bne	.L818	@,
.L815:
	mvn	r0, #37	@ D.44117,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L818:
	ldr	r1, [r2, #16]	@ D.44118, <variable>.read
	cmp	r1, #0	@ D.44118,
	beq	.L815	@,
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
	ldr	r8, [r3, #1348]	@ g_CurProcChan, g_CurProcChan
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
	ldr	r0, [r5, #0]	@ temp.3254, s_pstVfmwChan
	cmp	r0, #0	@ temp.3254,
	beq	.L822	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L822:
	ldr	r0, [r5, #4]	@ temp.3258, s_pstVfmwChan
	cmp	r0, #0	@ temp.3258,
	beq	.L823	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L823:
	ldr	r0, [r5, #8]	@ temp.3262, s_pstVfmwChan
	cmp	r0, #0	@ temp.3262,
	beq	.L824	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L824:
	ldr	r0, [r5, #12]	@ temp.3266, s_pstVfmwChan
	cmp	r0, #0	@ temp.3266,
	beq	.L825	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L825:
	ldr	r0, [r5, #16]	@ temp.3270, s_pstVfmwChan
	cmp	r0, #0	@ temp.3270,
	beq	.L826	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L826:
	ldr	r0, [r5, #20]	@ temp.3274, s_pstVfmwChan
	cmp	r0, #0	@ temp.3274,
	beq	.L827	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L827:
	ldr	r0, [r5, #24]	@ temp.3278, s_pstVfmwChan
	cmp	r0, #0	@ temp.3278,
	beq	.L828	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L828:
	ldr	r0, [r5, #28]	@ temp.3282, s_pstVfmwChan
	cmp	r0, #0	@ temp.3282,
	beq	.L829	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L829:
	ldr	r0, [r5, #32]	@ temp.3286, s_pstVfmwChan
	cmp	r0, #0	@ temp.3286,
	beq	.L830	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L830:
	ldr	r0, [r5, #36]	@ temp.3290, s_pstVfmwChan
	cmp	r0, #0	@ temp.3290,
	beq	.L831	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L831:
	ldr	r0, [r5, #40]	@ temp.3294, s_pstVfmwChan
	cmp	r0, #0	@ temp.3294,
	beq	.L832	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L832:
	ldr	r0, [r5, #44]	@ temp.3298, s_pstVfmwChan
	cmp	r0, #0	@ temp.3298,
	beq	.L833	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L833:
	ldr	r0, [r5, #48]	@ temp.3302, s_pstVfmwChan
	cmp	r0, #0	@ temp.3302,
	beq	.L834	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L834:
	ldr	r0, [r5, #52]	@ temp.3306, s_pstVfmwChan
	cmp	r0, #0	@ temp.3306,
	beq	.L835	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L835:
	ldr	r0, [r5, #56]	@ temp.3310, s_pstVfmwChan
	cmp	r0, #0	@ temp.3310,
	beq	.L836	@,
	ldr	lr, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L836:
	ldr	r0, [r5, #60]	@ D.43700, s_pstVfmwChan
	cmp	r0, #0	@ D.43700,
	beq	.L837	@,
	ldr	ip, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r1, #:lower16:.LC78	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	movt	r1, #:upper16:.LC78	@,
	ldr	r3, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	mov	r0, r4	@, p
	str	ip, [sp, #0]	@ <variable>.s32Priority,
	bl	seq_printf	@
.L837:
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
	movw	r3, #:lower16:2015032000	@ tmp139,
	movw	r2, #:lower16:.LC143	@,
	movt	r3, #:upper16:2015032000	@,
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
	ldr	r3, [r5, #1352]	@, extra_cmd
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
	ldr	r3, [r5, #1356]	@, g_ResetCreateNewSave
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
	movw	r3, #:lower16:2015032000	@,
	movt	r3, #:upper16:2015032000	@,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC152	@,
	movt	r1, #:upper16:.LC152	@,
	bl	seq_printf	@
	ldr	ip, [r5, #1372]	@ D.43575, <variable>.u32VaVdmLoad
	movw	r6, #:lower16:-858993459	@ tmp164,
	movt	r6, #:upper16:-858993459	@ tmp164,
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC153	@,
	umull	r2, r3, r6, ip	@, tmp163, tmp164, D.43575
	movt	r1, #:upper16:.LC153	@,
	movw	r2, #:lower16:.LC154	@,
	movt	r2, #:upper16:.LC154	@,
	mov	r3, r3, lsr #3	@ tmp162, tmp163,
	add	lr, r3, r3, asl #2	@, tmp170, tmp162, tmp162,
	sub	ip, ip, lr, asl #1	@ tmp172, D.43575, tmp170,
	str	ip, [sp, #0]	@ tmp172,
	bl	seq_printf	@
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC155	@,
	movt	r1, #:upper16:.LC155	@,
	bl	seq_printf	@
	ldr	ip, [r5, #1436]	@ D.43583, <variable>.u32SaScdLoad
	mov	r2, #0	@,
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC156	@,
	movt	r1, #:upper16:.LC156	@,
	umull	lr, r3, r6, ip	@, tmp177, tmp164, D.43583
	mov	r3, r3, lsr #3	@ tmp176, tmp177,
	add	lr, r3, r3, asl #2	@, tmp184, tmp176, tmp176,
	sub	ip, ip, lr, asl #1	@ tmp186, D.43583, tmp184,
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
	beq	.L846	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192820	@ tmp194,
	movt	r2, #:upper16:192820	@ tmp194,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #0	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L846:
	ldr	r3, [r5, #4]	@ pChan.3412, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3412,
	beq	.L847	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192820	@ tmp199,
	movt	r0, #:upper16:192820	@ tmp199,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #1	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L847:
	ldr	r3, [r5, #8]	@ pChan.3415, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3415,
	beq	.L848	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192820	@ tmp204,
	movt	r2, #:upper16:192820	@ tmp204,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #2	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L848:
	ldr	r3, [r5, #12]	@ pChan.3418, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3418,
	beq	.L849	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192820	@ tmp209,
	movt	r0, #:upper16:192820	@ tmp209,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #3	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L849:
	ldr	r3, [r5, #16]	@ pChan.3421, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3421,
	beq	.L850	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192820	@ tmp214,
	movt	r2, #:upper16:192820	@ tmp214,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #4	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L850:
	ldr	r3, [r5, #20]	@ pChan.3424, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3424,
	beq	.L851	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192820	@ tmp219,
	movt	r0, #:upper16:192820	@ tmp219,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #5	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L851:
	ldr	r3, [r5, #24]	@ pChan.3427, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3427,
	beq	.L852	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192820	@ tmp224,
	movt	r2, #:upper16:192820	@ tmp224,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #6	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L852:
	ldr	r3, [r5, #28]	@ pChan.3430, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3430,
	beq	.L853	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192820	@ tmp229,
	movt	r0, #:upper16:192820	@ tmp229,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #7	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L853:
	ldr	r3, [r5, #32]	@ pChan.3433, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3433,
	beq	.L854	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192820	@ tmp234,
	movt	r2, #:upper16:192820	@ tmp234,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #8	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L854:
	ldr	r3, [r5, #36]	@ pChan.3436, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3436,
	beq	.L855	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192820	@ tmp239,
	movt	r0, #:upper16:192820	@ tmp239,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #9	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L855:
	ldr	r3, [r5, #40]	@ pChan.3439, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3439,
	beq	.L856	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192820	@ tmp244,
	movt	r2, #:upper16:192820	@ tmp244,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #10	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L856:
	ldr	r3, [r5, #44]	@ pChan.3442, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3442,
	beq	.L857	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192820	@ tmp249,
	movt	r0, #:upper16:192820	@ tmp249,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #11	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L857:
	ldr	r3, [r5, #48]	@ pChan.3445, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3445,
	beq	.L858	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192820	@ tmp254,
	movt	r2, #:upper16:192820	@ tmp254,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #12	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L858:
	ldr	r3, [r5, #52]	@ pChan.3448, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3448,
	beq	.L859	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192820	@ tmp259,
	movt	r0, #:upper16:192820	@ tmp259,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #13	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L859:
	ldr	r3, [r5, #56]	@ pChan.3451, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3451,
	beq	.L860	@,
	ldr	ip, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r2, #:lower16:192820	@ tmp264,
	movt	r2, #:upper16:192820	@ tmp264,
	movw	r1, #:lower16:.LC160	@,
	mov	r0, r4	@, p
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r2]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r2, #14	@,
	str	ip, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L860:
	ldr	r3, [r5, #60]	@ pChan.3409, s_pstVfmwChan
	cmp	r3, #0	@ pChan.3409,
	beq	.L861	@,
	ldr	lr, [r3, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	movw	r0, #:lower16:192820	@ tmp269,
	movt	r0, #:upper16:192820	@ tmp269,
	movw	r1, #:lower16:.LC160	@,
	mov	r2, #15	@,
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [r3, r0]	@ <variable>.SmInstArray.MatchScdIdPlus1, <variable>.SmInstArray.MatchScdIdPlus1
	mov	r0, r4	@, p
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	seq_printf	@
.L861:
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
	bhi	.L869	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r0, [r3, r0, asl #2]	@ D.39240, s_pstVfmwChan
	cmp	r0, #0	@ D.39240,
	beq	.L870	@,
	ldr	r2, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r2, #1	@ <variable>.s32IsOpen,
	bne	.L871	@,
	add	r0, r0, #100352	@, D.39240,
	add	r0, r0, #128	@,,
	bl	GetSegStreamSize	@
	ldmfd	sp, {fp, sp, pc}	@
.L871:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1110	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC162	@,
	movt	r3, #:upper16:.LC162	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	ldmfd	sp, {fp, sp, pc}	@
.L869:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1108	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ ret,
	ldmfd	sp, {fp, sp, pc}	@
.L870:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1109	@,
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
	ldr	sl, [r5, #1348]	@ chanID, g_CurProcChan
	mov	r4, r0	@ p, p
	ldr	r8, [r2, #40]	@ pInst, <variable>.pSmInstArray
	ldr	r7, [r3, sl, asl #2]	@ pFsp, s_pFspInst
	cmp	r8, #0	@ pInst,
	beq	.L873	@,
	movw	ip, #:lower16:190872	@ tmp164,
	movt	ip, #:upper16:190872	@ tmp164,
	ldr	r0, [r8, ip]	@ <variable>.Mode, <variable>.Mode
	cmp	r0, #0	@ <variable>.Mode,
	bne	.L903	@,
.L873:
	mov	r0, #0	@,
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L903:
	add	r6, r8, #200	@ D.43505, pInst,
	sub	r1, fp, #52	@,,
	mov	r0, r6	@, D.43505
	bl	GetRawStreamSize	@
	cmp	r0, #0	@,
	bne	.L904	@,
.L874:
	mov	r0, r6	@, D.43505
	sub	r1, fp, #48	@,,
	bl	GetRawStreamNum	@
	cmp	r0, #0	@,
	bne	.L905	@,
.L875:
	add	r6, r8, #98304	@ D.43513, pInst,
	sub	r1, fp, #60	@,,
	add	r6, r6, #224	@ D.43513, D.43513,
	mov	r0, r6	@, D.43513
	bl	GetSegStreamSize	@
	cmp	r0, #0	@,
	bne	.L906	@,
.L876:
	mov	r0, r6	@, D.43513
	sub	r1, fp, #56	@,,
	bl	GetSegStreamNum	@
	cmp	r0, #0	@,
	bne	.L907	@,
.L877:
	movw	lr, #:lower16:190716	@ tmp183,
	movt	lr, #:upper16:190716	@ tmp183,
	ldr	r8, [r8, lr]	@ BufSize, <variable>.StreamSegArray.SegBufSize
	cmp	r8, #0	@ BufSize,
	moveq	r9, r8	@ s32percent, BufSize
	bne	.L908	@,
.L879:
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
	movw	r3, #:lower16:2015032000	@,
	movt	r3, #:upper16:2015032000	@,
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
	ldr	lr, [r5, #1372]	@ D.43530, <variable>.u32VaVdmLoad
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC153	@,
	movw	r2, #:lower16:.LC154	@,
	movt	r1, #:upper16:.LC153	@,
	umull	ip, r3, r6, lr	@, tmp213, tmp214, D.43530
	movt	r2, #:upper16:.LC154	@,
	mov	r3, r3, lsr #3	@ tmp212, tmp213,
	add	ip, r3, r3, asl #2	@, tmp220, tmp212, tmp212,
	sub	ip, lr, ip, asl #1	@ tmp222, D.43530, tmp220,
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
	ldr	ip, [r5, #1452]	@ D.43542, <variable>.u32FrFrameRate
	mov	r0, r4	@, p
	movw	r1, #:lower16:.LC176	@,
	movw	r2, #:lower16:.LC177	@,
	movt	r1, #:upper16:.LC176	@,
	umull	lr, r3, r6, ip	@, tmp235, tmp214, D.43542
	movt	r2, #:upper16:.LC177	@,
	mov	r3, r3, lsr #3	@ tmp234, tmp235,
	add	r6, r3, r3, asl #2	@, tmp242, tmp234, tmp234,
	sub	ip, ip, r6, asl #1	@ tmp244, D.43542, tmp242,
	str	ip, [sp, #0]	@ tmp244,
	bl	seq_printf	@
	ldrb	ip, [r7, #10]	@ zero_extendqisi2	@ D.43551, <variable>.s32DecFsNum
	sxtb	r6, ip	@ D.43552, D.43551
	cmp	r6, #0	@ D.43552,
	movle	r5, #0	@ usedFrameNum,
	ble	.L881	@,
	add	r3, r7, #34304	@ ivtmp.3505, pFsp,
	rsb	r0, r6, r6, asl #4	@, tmp249, D.43552, D.43552,
	mov	r5, #0	@ usedFrameNum,
	ldrsb	r1, [r3, #158]!	@ <variable>.DispState, <variable>.DispState
	mov	lr, r0, asl #2	@ D.47702, tmp249,
	sub	r2, lr, #60	@ tmp266, D.47702,
	cmp	r1, #3	@ <variable>.DispState,
	ubfx	r1, r2, #2, #1	@ tmp270, tmp266,,
	beq	.L889	@,
	ldrsb	r2, [r3, #-2]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	r2, #1	@ <variable>.IsDecRef,
	beq	.L889	@,
.L890:
	mov	r2, #60	@ ivtmp.3506,
	cmp	r2, lr	@ ivtmp.3506, D.47702
	add	r3, r3, r2	@ ivtmp.3505, ivtmp.3505,
	beq	.L881	@,
	cmp	r1, #0	@ tmp270,
	beq	.L884	@,
	ldrsb	r1, [r3, #0]	@ <variable>.DispState, <variable>.DispState
	cmp	r1, #3	@ <variable>.DispState,
	beq	.L892	@,
	ldrsb	r0, [r3, #-2]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	r0, #1	@ <variable>.IsDecRef,
	beq	.L892	@,
	add	r2, r2, #60	@ ivtmp.3506, ivtmp.3506,
	add	r3, r3, #60	@ ivtmp.3505, ivtmp.3505,
	cmp	r2, lr	@ ivtmp.3506, D.47702
	bne	.L884	@,
.L881:
	cmp	ip, #0	@ D.43551,
	bne	.L909	@,
.L886:
	mov	r3, r6	@, D.43552
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
	b	.L873	@
.L910:
	ldrsb	r0, [r3, #-2]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	r0, #1	@ <variable>.IsDecRef,
	beq	.L882	@,
	ldrsb	r3, [r3, #60]	@ <variable>.DispState, <variable>.DispState
	cmp	r3, #3	@ <variable>.DispState,
	beq	.L896	@,
.L901:
	ldrsb	r3, [r1, #-2]	@ <variable>.IsDecRef, <variable>.IsDecRef
	cmp	r3, #1	@ <variable>.IsDecRef,
	beq	.L896	@,
.L897:
	add	r2, r2, #60	@ ivtmp.3506, tmp272,
	add	r3, r1, #60	@ ivtmp.3505, tmp271,
	cmp	r2, lr	@ ivtmp.3506, D.47702
	beq	.L881	@,
.L884:
	ldrsb	r0, [r3, #0]	@ <variable>.DispState, <variable>.DispState
	add	r2, r2, #60	@ tmp272, ivtmp.3506,
	add	r1, r3, #60	@ tmp271, ivtmp.3505,
	cmp	r0, #3	@ <variable>.DispState,
	bne	.L910	@,
.L882:
	ldrsb	r3, [r3, #60]	@ <variable>.DispState, <variable>.DispState
	add	r5, r5, #1	@ usedFrameNum, usedFrameNum,
	cmp	r3, #3	@ <variable>.DispState,
	bne	.L901	@,
.L896:
	add	r5, r5, #1	@ usedFrameNum, usedFrameNum,
	b	.L897	@
.L909:
	mov	lr, #100	@ tmp254,
	mov	r1, r6	@, D.43552
	mul	r0, lr, r5	@, tmp254, usedFrameNum
	bl	__aeabi_idiv	@
	mov	ip, r0	@ s32percent.3509,
	b	.L886	@
.L908:
	ldr	r3, [fp, #-60]	@ SegSize, SegSize
	mov	r9, #100	@ tmp186,
	mov	r1, r8	@, BufSize
	mul	r0, r9, r3	@, tmp186, SegSize
	bl	__aeabi_idiv	@
	mov	r9, r0	@ s32percent,
	b	.L879	@
.L889:
	mov	r5, #1	@ usedFrameNum,
	b	.L890	@
.L892:
	add	r2, r2, #60	@ ivtmp.3506, ivtmp.3506,
	add	r5, r5, #1	@ usedFrameNum, usedFrameNum,
	cmp	r2, lr	@ ivtmp.3506, D.47702
	add	r3, r3, #60	@ ivtmp.3505, ivtmp.3505,
	bne	.L884	@,
	b	.L881	@
.L907:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L911	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #8691	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	b	.L877	@
.L906:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L911	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #8686	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	b	.L876	@
.L905:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L911	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #8681	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	b	.L875	@
.L904:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L911	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #8676	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	b	.L874	@
.L912:
	.align	2
.L911:
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
	movw	r2, #:lower16:251488	@ tmp138,
	movt	r2, #:upper16:251488	@ tmp138,
	ldr	r0, [r1, r0, asl #2]	@ D.43289, s_pstVfmwChan
	ldr	r3, [r0, r2]	@ <variable>.stSynCtx.eVidStd, <variable>.stSynCtx.eVidStd
	cmp	r3, #16	@ <variable>.stSynCtx.eVidStd,
	ldrls	pc, [pc, r3, asl #2]	@ <variable>.stSynCtx.eVidStd
	b	.L914	@
.L927:
	.word	.L915
	.word	.L916
	.word	.L917
	.word	.L918
	.word	.L914
	.word	.L919
	.word	.L920
	.word	.L914
	.word	.L921
	.word	.L922
	.word	.L923
	.word	.L923
	.word	.L923
	.word	.L924
	.word	.L914
	.word	.L925
	.word	.L926
.L926:
	add	lr, r0, #250880	@, D.43289,
	add	r0, lr, #616	@,,
	bl	HEVCDEC_GetRemainImg	@
	mov	r4, r0	@ ret,
.L928:
	cmn	r4, #1	@ ret,
	beq	.L930	@,
	cmp	r4, #0	@ ret,
	bne	.L938	@,
	mov	r0, r5	@, ChanId
	mov	r1, r4	@, ret
	bl	VCTRL_ReportLastFrame	@
	movw	r1, #:lower16:.LC181	@,
	mov	r0, #2	@,
	movt	r1, #:upper16:.LC181	@,
	bl	dprint_vfmw	@
.L932:
	mov	r0, r4	@, ret
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L914:
	mvn	r4, #0	@ ret,
.L930:
	mov	r0, r5	@, ChanId
	mov	r1, #1	@,
	bl	VCTRL_ReportLastFrame	@
	movw	r1, #:lower16:.LC180	@,
	mov	r0, #2	@,
	movt	r1, #:upper16:.LC180	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, ret
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L915:
	add	ip, r0, #250880	@, D.43289,
	add	r0, ip, #616	@,,
	bl	H264DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L928	@
.L916:
	add	r4, r0, #250880	@, D.43289,
	add	r0, r4, #616	@,,
	bl	VC1DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L928	@
.L917:
	add	r4, r0, #250880	@, D.43289,
	add	r0, r4, #616	@,,
	bl	MPEG4DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L928	@
.L918:
	add	r0, r0, #250880	@, D.43289,
	add	r0, r0, #616	@,,
	bl	MPEG2DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L928	@
.L919:
	add	r0, r0, #250880	@, D.43289,
	add	r0, r0, #616	@,,
	bl	DIVX3DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L928	@
.L920:
	add	r3, r0, #250880	@, D.43289,
	add	r0, r3, #616	@,,
	bl	AVSDEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L928	@
.L921:
	add	r2, r0, #250880	@, D.43289,
	add	r0, r2, #616	@,,
	bl	REAL8DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L928	@
.L922:
	add	r1, r0, #250880	@, D.43289,
	add	r0, r1, #616	@,,
	bl	REAL9DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L928	@
.L923:
	add	ip, r0, #250880	@, D.43289,
	add	r0, ip, #616	@,,
	bl	VP6DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L928	@
.L924:
	add	lr, r0, #250880	@, D.43289,
	add	r0, lr, #616	@,,
	bl	VP8DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L928	@
.L925:
	add	r3, r0, #250880	@, D.43289,
	add	r0, r3, #616	@,,
	bl	MVC_DEC_GetRemainImg	@
	mov	r4, r0	@ ret,
	b	.L928	@
.L938:
	movw	r2, #:lower16:g_chipID	@ tmp166,
	movt	r2, #:upper16:g_chipID	@ tmp166,
	ldr	r3, [r2, #0]	@ g_chipID, g_chipID
	cmp	r3, #10	@ g_chipID,
	bgt	.L935	@,
	cmp	r3, #8	@ g_chipID,
	bge	.L934	@,
	cmp	r3, #0	@ g_chipID,
	blt	.L932	@,
	cmp	r3, #5	@ g_chipID,
	bgt	.L939	@,
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
.L935:
	cmp	r3, #51	@ g_chipID,
	blt	.L932	@,
	cmp	r3, #52	@ g_chipID,
	bgt	.L940	@,
.L934:
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
.L940:
	sub	r1, r3, #100	@ tmp168, g_chipID,
	cmp	r1, #1	@ tmp168,
	bhi	.L932	@,
	b	.L934	@
.L939:
	cmp	r3, #6	@ g_chipID,
	bne	.L932	@,
	b	.L934	@
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
	b	.L944	@
.L943:
	add	r2, r9, r8	@ tmp166, tmp203, i
	mov	r8, r2, asl #2	@ tmp167, tmp166,
	add	r1, r8, sl	@ tmp168, tmp167, D.39426
	add	r0, r1, #248832	@ tmp177, tmp168,
	add	lr, r0, #400	@ tmp177, tmp177,
	add	sl, r0, #408	@ tmp169, tmp169,
	ldr	r1, [lr, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldmia	sl, {r0, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
	ldr	r3, [r5, r6, asl #2]	@ tmp188, s_pstVfmwChan
	mvn	r1, #0	@,
	add	ip, r8, r3	@ tmp194, tmp167, tmp188
	add	r2, ip, #248832	@ tmp195, tmp194,
	add	r8, r2, #416	@ tmp195, tmp195,
	strb	r1, [r8, #0]	@, <variable>.u8BufferNodeState
.L942:
	ldr	r8, [r5, r6, asl #2]	@ D.39426, s_pstVfmwChan
	add	r1, r7, r4	@ tmp213, tmp212, tmp208
	add	r2, r8, r1, asl #2	@, tmp215, D.39426, tmp213,
	add	r3, r2, #248832	@ tmp216, tmp215,
	add	ip, r3, #416	@ tmp216, tmp216,
	ldrb	r3, [ip, #0]	@ zero_extendqisi2	@ D.39428, <variable>.u8BufferNodeState
	cmp	r3, #255	@ D.39428,
	beq	.L948	@,
	cmp	r3, #1	@ D.39428,
	beq	.L952	@,
.L949:
	add	r2, r7, r4	@ tmp219, tmp212, tmp208
	mov	r7, r2, asl #2	@ tmp220, tmp219,
	add	r8, r7, r8	@ tmp221, tmp220, D.39426
	add	r3, r8, #248832	@ tmp225, tmp221,
	mvn	r8, #0	@,
	add	lr, r3, #408	@ tmp222, tmp222,
	add	r0, r3, #400	@ tmp225, tmp225,
	ldr	r2, [lr, #4]	@, <variable>.stFrameBuffer.Length
	ldr	r1, [r0, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldr	r0, [lr, #0]	@, <variable>.stFrameBuffer.PhyAddr
	bl	MEM_DelMemRecord	@
	ldr	ip, [r5, r6, asl #2]	@ tmp228, s_pstVfmwChan
	add	r2, r7, ip	@ tmp230, tmp220, tmp228
	add	r7, r2, #248832	@ tmp231, tmp230,
	add	r7, r7, #416	@ tmp231, tmp231,
	strb	r8, [r7, #0]	@, <variable>.u8BufferNodeState
.L948:
	add	r8, r4, #1	@ i, tmp208,
	cmp	r8, #64	@ i,
	beq	.L954	@,
.L944:
	mov	r9, r8, asl #2	@ tmp203, i,
	ldr	sl, [r5, r6, asl #2]	@ D.39426, s_pstVfmwChan
	add	r2, r9, r8	@ tmp143, tmp203, i
	add	r4, r8, #1	@ tmp208, i,
	add	r2, sl, r2, asl #2	@, tmp145, D.39426, tmp143,
	mov	r7, r4, asl #2	@ tmp212, tmp208,
	add	r1, r2, #248832	@ tmp146, tmp145,
	add	r3, r1, #416	@ tmp146, tmp146,
	ldrb	r3, [r3, #0]	@ zero_extendqisi2	@ D.39428, <variable>.u8BufferNodeState
	cmp	r3, #255	@ D.39428,
	beq	.L942	@,
	cmp	r3, #1	@ D.39428,
	bne	.L943	@,
	add	r0, r2, #248832	@ tmp161, tmp145,
	add	ip, r0, #400	@ tmp161, tmp161,
	add	lr, r0, #408	@ tmp153, tmp153,
	ldr	r1, [ip, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldr	r0, [lr, #0]	@, <variable>.stFrameBuffer.PhyAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L943	@
.L952:
	add	r0, r2, #248832	@ tmp235, tmp215,
	add	ip, r0, #400	@ tmp235, tmp235,
	add	lr, r0, #408	@ tmp233, tmp233,
	ldr	r1, [ip, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldr	r0, [lr, #0]	@, <variable>.stFrameBuffer.PhyAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L949	@
.L954:
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
	movw	r3, #:lower16:249200	@ tmp150,
	movt	r3, #:upper16:249200	@ tmp150,
	ldr	r2, [r8, r0, asl #2]	@ prephitmp.3597, s_pstVfmwChan
	mov	r4, r0	@ ChanID, ChanID
	ldr	r1, [r2, #216]	@, <variable>.stChanMem_vdh.PhyAddr
	str	r1, [fp, #-52]	@, %sfp
	ldr	ip, [r2, #212]	@, <variable>.stChanMem_vdh.VirAddr
	cmp	ip, #0	@,
	cmpne	r1, #0	@,,
	str	ip, [fp, #-48]	@, %sfp
	ldr	r9, [r2, r3]	@ s32FrameSize, <variable>.s32CurFsSize
	beq	.L956	@,
	cmp	r5, #63	@ s32FrmNum,
	bgt	.L956	@,
	mov	sl, #0	@ ivtmp.3623,
	str	sl, [fp, #-56]	@ ivtmp.3623, %sfp
	mov	r6, sl	@ i, ivtmp.3623
	mov	r7, sl	@ s32AllocedFrameNum, ivtmp.3623
	b	.L961	@
.L957:
	cmp	r5, r7	@ s32FrmNum, s32AllocedFrameNum
	ble	.L959	@,
	add	r6, r6, #1	@ i, i,
	add	ip, sl, r9	@ ivtmp.3623, ivtmp.3623, s32FrameSize
	cmp	r6, #64	@ i,
	mov	sl, r6	@ tmp252, i
	beq	.L974	@,
.L960:
	add	r1, r6, r6, asl #2	@, tmp259, tmp252, tmp252,
	ldr	r0, [r8, r4, asl #2]	@ prephitmp.3597, s_pstVfmwChan
	cmp	r7, r5	@ s32AllocedFrameNum, s32FrmNum
	movge	r3, #0	@, prephitmp.3599
	movlt	r3, #1	@, prephitmp.3599
	mov	r1, r1, asl #2	@ tmp260, tmp259,
	add	r0, r1, r0	@ tmp261, tmp260, prephitmp.3597
	add	r2, r0, #248832	@ tmp262, tmp261,
	add	r2, r2, #416	@ tmp262, tmp262,
	ldrb	r2, [r2, #0]	@ zero_extendqisi2	@ <variable>.u8BufferNodeState, <variable>.u8BufferNodeState
	cmp	r2, #255	@ <variable>.u8BufferNodeState,
	movne	r2, #0	@, tmp267
	andeq	r2, r3, #1	@,, tmp267, prephitmp.3599
	cmp	r2, #0	@ tmp267,
	bne	.L975	@,
	cmp	r5, r7	@ s32FrmNum, s32AllocedFrameNum
	ble	.L959	@,
.L970:
	add	r6, sl, #1	@ i, tmp252,
	ldr	r0, [r8, r4, asl #2]	@ prephitmp.3597, s_pstVfmwChan
	cmp	r7, r5	@ s32AllocedFrameNum, s32FrmNum
	movge	r3, #0	@, prephitmp.3599
	movlt	r3, #1	@, prephitmp.3599
	add	ip, ip, r9	@ ivtmp.3623, ivtmp.3623, s32FrameSize
	add	r1, r6, r6, asl #2	@, tmp294, i, i,
	mov	r1, r1, asl #2	@ tmp295, tmp294,
	add	r0, r1, r0	@ tmp296, tmp295, prephitmp.3597
	add	r2, r0, #248832	@ tmp297, tmp296,
	add	r2, r2, #416	@ tmp297, tmp297,
	ldrb	r2, [r2, #0]	@ zero_extendqisi2	@ <variable>.u8BufferNodeState, <variable>.u8BufferNodeState
	cmp	r2, #255	@ <variable>.u8BufferNodeState,
	movne	r2, #0	@, tmp302
	andeq	r2, r3, #1	@,, tmp302, prephitmp.3599
	cmp	r2, #0	@ tmp302,
	bne	.L971	@,
	cmp	r5, r7	@ s32FrmNum, s32AllocedFrameNum
	ble	.L959	@,
.L972:
	ldr	r2, [r8, r4, asl #2]	@ prephitmp.3597, s_pstVfmwChan
	add	r6, sl, #2	@ i, tmp252,
	add	sl, ip, r9	@ ivtmp.3623, ivtmp.3623, s32FrameSize
.L961:
	add	r0, r6, r6, asl #2	@, tmp163, i, i,
	cmp	r7, r5	@ s32AllocedFrameNum, s32FrmNum
	movge	r3, #0	@, prephitmp.3599
	movlt	r3, #1	@, prephitmp.3599
	mov	r0, r0, asl #2	@ tmp164, tmp163,
	add	r2, r0, r2	@ tmp165, tmp164, prephitmp.3597
	add	ip, r2, #248832	@ tmp166, tmp165,
	add	r1, ip, #416	@ tmp166, tmp166,
	ldrb	ip, [r1, #0]	@ zero_extendqisi2	@ <variable>.u8BufferNodeState, <variable>.u8BufferNodeState
	cmp	ip, #255	@ <variable>.u8BufferNodeState,
	movne	r1, #0	@, tmp172
	andeq	r1, r3, #1	@,, tmp172, prephitmp.3599
	cmp	r1, #0	@ tmp172,
	beq	.L957	@,
	add	ip, r2, #248832	@ tmp179, tmp165,
	ldr	lr, [fp, #-52]	@, %sfp
	add	r2, ip, #408	@ tmp179, tmp179,
	ldr	r1, [fp, #-48]	@, %sfp
	add	r3, sl, lr	@ tmp180, ivtmp.3623,
	add	r6, r6, #1	@ i, i,
	str	r3, [r2, #0]	@ tmp180, <variable>.stFrameBuffer.PhyAddr
	add	lr, sl, r1	@ tmp190, ivtmp.3623,
	ldr	ip, [r8, r4, asl #2]	@ tmp182, s_pstVfmwChan
	add	r7, r7, #1	@ s32AllocedFrameNum, s32AllocedFrameNum,
	add	r1, r0, ip	@ tmp188, tmp164, tmp182
	add	r2, r1, #248832	@ tmp189, tmp188,
	add	r3, r2, #400	@ tmp189, tmp189,
	str	lr, [r3, #4]	@ tmp190, <variable>.stFrameBuffer.VirAddr
	ldr	ip, [r8, r4, asl #2]	@ tmp192, s_pstVfmwChan
	add	r1, r0, ip	@ tmp198, tmp164, tmp192
	add	r2, r1, #248832	@ tmp199, tmp198,
	add	r3, r2, #408	@ tmp199, tmp199,
	mov	r2, #0	@,
	str	r9, [r3, #4]	@ s32FrameSize, <variable>.stFrameBuffer.Length
	ldr	lr, [r8, r4, asl #2]	@ tmp201, s_pstVfmwChan
	add	ip, r0, lr	@ tmp207, tmp164, tmp201
	add	r1, ip, #248832	@ tmp208, tmp207,
	add	r3, r1, #416	@ tmp208, tmp208,
	strb	r2, [r3, #0]	@, <variable>.u8BufferNodeState
	ldr	lr, [r8, r4, asl #2]	@ temp.3629, s_pstVfmwChan
	add	ip, r0, lr	@ tmp217, tmp164, temp.3629
	add	r2, ip, #248832	@ tmp226, tmp217,
	add	lr, r2, #408	@ tmp218, tmp218,
	add	r3, r2, #400	@ tmp226, tmp226,
	ldmia	lr, {r0, r2}	@ phole ldm
	ldr	r1, [r3, #4]	@, <variable>.stFrameBuffer.VirAddr
	bl	MEM_AddMemRecord	@
	cmp	r6, #64	@ i,
	add	ip, sl, r9	@ ivtmp.3623, ivtmp.3623, s32FrameSize
	mov	sl, r6	@ tmp252, i
	str	r0, [fp, #-56]	@, %sfp
	bne	.L960	@,
.L974:
	cmp	r7, r5	@ s32AllocedFrameNum, s32FrmNum
	movge	r3, #0	@, prephitmp.3599
	movlt	r3, #1	@, prephitmp.3599
.L959:
	cmp	r6, #64	@ i,
	movne	r3, #0	@, tmp244
	andeq	r3, r3, #1	@,, tmp244, prephitmp.3599
	cmp	r3, #0	@ tmp244,
	bne	.L976	@,
.L962:
	ldr	r0, [fp, #-56]	@, %sfp
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L975:
	ldr	r2, [fp, #-52]	@, %sfp
	add	r6, r0, #248832	@ tmp268, tmp261,
	ldr	lr, [fp, #-48]	@, %sfp
	add	r7, r7, #1	@ s32AllocedFrameNum, s32AllocedFrameNum,
	add	r3, ip, r2	@ tmp269, ivtmp.3623,
	add	r2, r6, #408	@ tmp268, tmp268,
	add	r6, ip, lr	@ tmp273, ivtmp.3623,
	str	r3, [r2, #0]	@ tmp269, <variable>.stFrameBuffer.PhyAddr
	ldr	r0, [r8, r4, asl #2]	@ tmp270, s_pstVfmwChan
	add	r2, r1, r0	@ tmp271, tmp260, tmp270
	add	lr, r2, #248832	@ tmp272, tmp271,
	add	r3, lr, #400	@ tmp272, tmp272,
	str	r6, [r3, #4]	@ tmp273, <variable>.stFrameBuffer.VirAddr
	ldr	r0, [r8, r4, asl #2]	@ tmp274, s_pstVfmwChan
	add	r2, r1, r0	@ tmp275, tmp260, tmp274
	add	lr, r2, #248832	@ tmp276, tmp275,
	add	r6, lr, #408	@ tmp276, tmp276,
	str	r9, [r6, #4]	@ s32FrameSize, <variable>.stFrameBuffer.Length
	mov	r6, #0	@,
	ldr	r3, [r8, r4, asl #2]	@ tmp277, s_pstVfmwChan
	add	r0, r1, r3	@ tmp278, tmp260, tmp277
	add	r2, r0, #248832	@ tmp279, tmp278,
	add	lr, r2, #416	@ tmp279, tmp279,
	strb	r6, [lr, #0]	@, <variable>.u8BufferNodeState
	ldr	r3, [r8, r4, asl #2]	@ temp.3629, s_pstVfmwChan
	add	r1, r1, r3	@ tmp282, tmp260, temp.3629
	add	r2, r1, #248832	@ tmp285, tmp282,
	add	lr, r2, #400	@ tmp285, tmp285,
	add	r6, r2, #408	@ tmp283, tmp283,
	ldr	r1, [lr, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldmia	r6, {r0, r2}	@ phole ldm
	str	ip, [fp, #-60]	@,
	bl	MEM_AddMemRecord	@
	ldr	ip, [fp, #-60]	@,
	str	r0, [fp, #-56]	@, %sfp
	b	.L970	@
.L971:
	ldr	r2, [fp, #-52]	@, %sfp
	add	r6, r0, #248832	@ tmp303, tmp296,
	ldr	lr, [fp, #-48]	@, %sfp
	add	r7, r7, #1	@ s32AllocedFrameNum, s32AllocedFrameNum,
	add	r3, ip, r2	@ tmp304, ivtmp.3623,
	add	r2, r6, #408	@ tmp303, tmp303,
	add	r6, ip, lr	@ tmp308, ivtmp.3623,
	str	r3, [r2, #0]	@ tmp304, <variable>.stFrameBuffer.PhyAddr
	ldr	r0, [r8, r4, asl #2]	@ tmp305, s_pstVfmwChan
	add	r2, r1, r0	@ tmp306, tmp295, tmp305
	add	lr, r2, #248832	@ tmp307, tmp306,
	add	r3, lr, #400	@ tmp307, tmp307,
	str	r6, [r3, #4]	@ tmp308, <variable>.stFrameBuffer.VirAddr
	ldr	r0, [r8, r4, asl #2]	@ tmp309, s_pstVfmwChan
	add	r2, r1, r0	@ tmp310, tmp295, tmp309
	add	r6, r2, #248832	@ tmp311, tmp310,
	add	lr, r6, #408	@ tmp311, tmp311,
	str	r9, [lr, #4]	@ s32FrameSize, <variable>.stFrameBuffer.Length
	mov	lr, #0	@,
	ldr	r3, [r8, r4, asl #2]	@ tmp312, s_pstVfmwChan
	add	r0, r1, r3	@ tmp313, tmp295, tmp312
	add	r2, r0, #248832	@ tmp314, tmp313,
	add	r6, r2, #416	@ tmp314, tmp314,
	strb	lr, [r6, #0]	@, <variable>.u8BufferNodeState
	ldr	r3, [r8, r4, asl #2]	@ temp.3629, s_pstVfmwChan
	add	r0, r1, r3	@ tmp317, tmp295, temp.3629
	add	r6, r0, #248832	@ tmp320, tmp317,
	add	r3, r6, #408	@ tmp318, tmp318,
	add	lr, r6, #400	@ tmp320, tmp320,
	ldr	r2, [r3, #4]	@, <variable>.stFrameBuffer.Length
	ldr	r1, [lr, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldr	r0, [r3, #0]	@, <variable>.stFrameBuffer.PhyAddr
	str	ip, [fp, #-60]	@,
	bl	MEM_AddMemRecord	@
	ldr	ip, [fp, #-60]	@,
	str	r0, [fp, #-56]	@, %sfp
	b	.L972	@
.L956:
	ldr	r3, [fp, #-48]	@, %sfp
	mov	r0, #31	@,
	ldr	r2, [fp, #-52]	@, %sfp
	movw	r1, #:lower16:.LC183	@,
	movt	r1, #:upper16:.LC183	@,
	str	r5, [sp, #0]	@ s32FrmNum,
	bl	dprint_vfmw	@
	mvn	r3, #0	@,
	str	r3, [fp, #-56]	@, %sfp
	b	.L962	@
.L976:
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
	beq	.L962	@,
	mov	r2, r4	@, ChanID
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC185	@,
	movt	r1, #:upper16:.LC185	@,
	bl	dprint_vfmw	@
	mvn	ip, #0	@,
	str	ip, [fp, #-56]	@, %sfp
	b	.L962	@
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
	movw	r8, #:lower16:249200	@ tmp147,
	ldr	r7, [r5, r0, asl #2]	@ prephitmp.3652, s_pstVfmwChan
	mov	r0, #0	@,
	str	r0, [fp, #-52]	@, %sfp
	movt	r8, #:upper16:249200	@ tmp147,
	mov	r4, r0	@ s32Times,
	mov	sl, r0	@ i, s32Times
	ldr	r2, [r7, #1892]	@ <variable>.stSynExtraData.stChanOption.s32DelayTime, <variable>.stSynExtraData.stChanOption.s32DelayTime
	ldr	r9, [r7, r8]	@ s32FrameSize, <variable>.s32CurFsSize
	mov	r8, r0	@ tmp227, s32Ret
	str	r4, [fp, #-72]	@ s32Times, %sfp
	add	r1, r2, r2, lsr #31	@, tmp150, <variable>.stSynExtraData.stChanOption.s32DelayTime, <variable>.stSynExtraData.stChanOption.s32DelayTime,
	mov	r3, r1, asr #1	@, tmp150,
	str	r3, [fp, #-48]	@, %sfp
	b	.L984	@
.L978:
	ldr	r3, [fp, #-60]	@, %sfp
	ldr	r1, [fp, #-52]	@, %sfp
	cmp	r3, r1	@,
	ble	.L983	@,
	add	sl, sl, #1	@ i, i,
	cmp	sl, #64	@ i,
	beq	.L981	@,
.L991:
	ldr	r7, [r5, r6, asl #2]	@ prephitmp.3652, s_pstVfmwChan
.L984:
	mov	ip, sl, asl #2	@, i,
	str	ip, [fp, #-56]	@, %sfp
	add	r2, ip, sl	@ tmp157,, i
	ldr	ip, [fp, #-52]	@, %sfp
	mov	r2, r2, asl #2	@ tmp158, tmp157,
	add	r1, r2, r7	@ tmp159, tmp158, prephitmp.3652
	add	r3, r1, #248832	@ tmp160, tmp159,
	ldr	r1, [fp, #-60]	@, %sfp
	add	r4, r3, #416	@ tmp160, tmp160,
	ldrb	r3, [r4, #0]	@ zero_extendqisi2	@ <variable>.u8BufferNodeState, <variable>.u8BufferNodeState
	cmp	ip, r1	@,
	movge	r4, #0	@,
	movlt	r4, #1	@,
	cmp	r3, #255	@ <variable>.u8BufferNodeState,
	movne	r4, #0	@,,
	cmp	r4, #0	@ tmp166,
	beq	.L978	@,
	add	r3, r2, #248832	@ tmp171, tmp158,
	mov	r1, r8	@, tmp227
	add	lr, r3, #400	@ tmp171, tmp171,
	movw	r0, #:lower16:.LC186	@,
	add	r7, r7, lr	@ MEM_RECORD, prephitmp.3652, tmp171
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
	ble	.L979	@,
	str	sl, [fp, #-64]	@ i, %sfp
	mov	r4, r3	@ s32Times,
	mov	sl, ip	@ tmp223, tmp223
.L987:
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
	bgt	.L987	@,
	ldr	sl, [fp, #-64]	@ i, %sfp
	str	r4, [fp, #-72]	@ s32Times, %sfp
.L979:
	cmp	r0, #0	@ s32Ret,
	bne	.L981	@,
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
	add	ip, r4, #416	@ tmp208, tmp208,
	mov	r4, #1	@,
	strb	r4, [ip, #0]	@, <variable>.u8BufferNodeState
	bne	.L991	@,
.L981:
	ldr	r2, [fp, #-60]	@, %sfp
	ldr	r3, [fp, #-52]	@, %sfp
	cmp	r2, r3	@,
	bgt	.L992	@,
.L983:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L992:
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
	beq	.L983	@
.L985:
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC188	@,
	movt	r1, #:upper16:.LC188	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ s32Ret,
	b	.L983	@
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
	movw	r2, #:lower16:249200	@ tmp154,
	movt	r2, #:upper16:249200	@ tmp154,
	movw	ip, #:lower16:249208	@ tmp153,
	ldr	r3, [r5, r0, asl #2]	@ D.44513, s_pstVfmwChan
	movt	ip, #:upper16:249208	@ tmp153,
	mov	r6, r0	@ ChanID, ChanID
	ldr	r1, [r3, r2]	@ s32FrameSize, <variable>.s32CurFsSize
	ldr	r7, [r3, ip]	@ s32NeededFrmNum, <variable>.s32NeededFrameNum
	cmp	r1, #0	@ s32FrameSize,
	ldr	r2, [r3, #272]	@ s32PreAllocSize, <variable>.s32VdmChanMemSize
	ble	.L1003	@,
	ldr	r4, [r3, #268]	@ <variable>.s32VdmChanMemAddr, <variable>.s32VdmChanMemAddr
	cmp	r4, #0	@ <variable>.s32VdmChanMemAddr,
	cmpne	r2, #0	@, s32PreAllocSize,
	bgt	.L1004	@,
	movw	r4, #:lower16:249220	@ tmp197,
	movt	r4, #:upper16:249220	@ tmp197,
	ldr	r3, [r3, r4]	@ temp.3712, <variable>.s32NeedMMZ
	cmp	r3, #1	@ temp.3712,
	bne	.L1001	@,
	mov	r1, r7	@, s32NeededFrmNum
	bl	VCTRL_AllocMemMMZ	@
	ldr	r8, [r5, r6, asl #2]	@ temp.3713, s_pstVfmwChan
	mov	r4, r0	@ s32Ret,
	bl	OSAL_GetTimeInMs	@
	movw	ip, #:lower16:251468	@ tmp199,
	movt	ip, #:upper16:251468	@ tmp199,
	movw	r3, #:lower16:249216	@ tmp202,
	cmp	r4, #0	@ s32Ret,
	movt	r3, #:upper16:249216	@ tmp202,
	str	r0, [r8, ip]	@, <variable>.stDynamicFSTimestamp.u32MMZEndTime
	ldr	r1, [r5, r6, asl #2]	@ tmp201, s_pstVfmwChan
	str	r7, [r1, r3]	@ s32NeededFrmNum, <variable>.s32MMZFrmNum
	bne	.L1005	@,
.L995:
	mov	r0, r4	@, s32Ret
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1004:
	mov	r0, r2	@, s32PreAllocSize
	bl	__aeabi_idiv	@
	cmp	r7, r0	@ s32NeededFrmNum, tmp166
	mov	r8, r0	@ tmp166,
	bgt	.L1006	@,
.L997:
	mov	r1, r7	@, s32NeededFrmNum
	mov	r0, r6	@, ChanID
	bl	VCTRL_AllocMemPre	@
	ldr	r8, [r5, r6, asl #2]	@ temp.3709, s_pstVfmwChan
	mov	r4, r0	@ s32Ret,
	bl	OSAL_GetTimeInMs	@
	movw	r2, #:lower16:251464	@ tmp190,
	movt	r2, #:upper16:251464	@ tmp190,
	movw	ip, #:lower16:249212	@ tmp193,
	cmp	r4, #0	@ s32Ret,
	movt	ip, #:upper16:249212	@ tmp193,
	str	r0, [r8, r2]	@, <variable>.stDynamicFSTimestamp.u32PreEndTime
	ldr	r0, [r5, r6, asl #2]	@ tmp192, s_pstVfmwChan
	str	r7, [r0, ip]	@ s32NeededFrmNum, <variable>.s32PreAllocFrmNum
	beq	.L995	@,
	movw	r1, #:lower16:.LC192	@,
	ldr	r2, .L1008	@,
	movt	r1, #:upper16:.LC192	@,
	movw	r3, #10246	@,
	mov	r0, #31	@,
	bl	dprint_vfmw	@
	b	.L995	@
.L1006:
	rsb	sl, r0, r7	@ s32MMZFrmNum, tmp166, s32NeededFrmNum
	cmp	sl, #0	@ s32MMZFrmNum,
	ble	.L997	@,
	mov	r1, r0	@, tmp166
	mov	r0, r6	@, ChanID
	bl	VCTRL_AllocMemPre	@
	ldr	r7, [r5, r6, asl #2]	@ temp.3704, s_pstVfmwChan
	mov	r4, r0	@ s32Ret,
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:251464	@ tmp168,
	movt	r1, #:upper16:251464	@ tmp168,
	movw	r3, #:lower16:249212	@ tmp171,
	cmp	r4, #0	@ s32Ret,
	movt	r3, #:upper16:249212	@ tmp171,
	str	r0, [r7, r1]	@, <variable>.stDynamicFSTimestamp.u32PreEndTime
	ldr	r0, [r5, r6, asl #2]	@ tmp170, s_pstVfmwChan
	str	r8, [r0, r3]	@ tmp166, <variable>.s32PreAllocFrmNum
	bne	.L998	@,
	ldr	ip, [r5, r6, asl #2]	@ tmp173, s_pstVfmwChan
	movw	lr, #:lower16:249220	@ tmp174,
	movt	lr, #:upper16:249220	@ tmp174,
	ldr	r3, [ip, lr]	@ D.44534, <variable>.s32NeedMMZ
	cmp	r3, #1	@ D.44534,
	bne	.L999	@,
	mov	r0, r6	@, ChanID
	mov	r1, sl	@, s32MMZFrmNum
	bl	VCTRL_AllocMemMMZ	@
	subs	r4, r0, #0	@ s32Ret,
	bne	.L1007	@,
	ldr	r7, [r5, r6, asl #2]	@ temp.3707, s_pstVfmwChan
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:251468	@ tmp179,
	movt	r1, #:upper16:251468	@ tmp179,
	movw	r3, #:lower16:249216	@ tmp182,
	movt	r3, #:upper16:249216	@ tmp182,
	str	r0, [r7, r1]	@, <variable>.stDynamicFSTimestamp.u32MMZEndTime
	mov	r0, r4	@, s32Ret
	ldr	r2, [r5, r6, asl #2]	@ tmp181, s_pstVfmwChan
	str	sl, [r2, r3]	@ s32MMZFrmNum, <variable>.s32MMZFrmNum
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1005:
	ldr	r2, .L1008	@,
	movw	r3, #10259	@,
	movw	r1, #:lower16:.LC190	@,
	mov	r0, #31	@,
	movt	r1, #:upper16:.LC190	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, s32Ret
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L998:
	ldr	r2, .L1008	@,
	movw	r3, #10236	@,
	movw	r1, #:lower16:.LC192	@,
	mov	r0, #31	@,
	movt	r1, #:upper16:.LC192	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, s32Ret
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1001:
	movw	r1, #:lower16:.LC193	@,
	ldr	r2, .L1008	@,
	movt	r1, #:upper16:.LC193	@,
	mov	r0, #31	@,
	mvn	r4, #0	@ s32Ret,
	bl	dprint_vfmw	@
	b	.L995	@
.L999:
	movw	r1, #:lower16:.LC191	@,
	ldr	r2, .L1008	@,
	movt	r1, #:upper16:.LC191	@,
	mov	r0, #31	@,
	mvn	r4, #0	@ s32Ret,
	bl	dprint_vfmw	@
	b	.L995	@
.L1007:
	movw	r1, #:lower16:.LC190	@,
	ldr	r2, .L1008	@,
	movt	r1, #:upper16:.LC190	@,
	movw	r3, #10222	@,
	mov	r0, #31	@,
	mvn	r4, #0	@ s32Ret,
	bl	dprint_vfmw	@
	b	.L995	@
.L1003:
	mov	r2, r1	@, s32FrameSize
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC189	@,
	movt	r1, #:upper16:.LC189	@,
	bl	dprint_vfmw	@
	mvn	r4, #0	@ s32Ret,
	b	.L995	@
.L1009:
	.align	2
.L1008:
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
	ldr	r3, [r3, #60]	@ D.42795, g_vdm_hal_fun_ptr.pfun_VDMHAL_EnableInt
	cmp	r3, #0	@ D.42795,
	beq	.L1014	@,
	mov	r0, #0	@,
	blx	r3	@ D.42795
	mov	r0, #0	@,
	bl	SCDDRV_EnableInt	@
	ldmfd	sp, {fp, sp, pc}	@
.L1014:
	mov	r0, r3	@, D.42795
	movw	r2, #7611	@,
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
	ldr	r3, [r3, #56]	@ D.42780, g_vdm_hal_fun_ptr.pfun_VDMHAL_MaskInt
	cmp	r3, #0	@ D.42780,
	beq	.L1019	@,
	mov	r0, #0	@,
	blx	r3	@ D.42780
	mov	r0, #0	@,
	bl	SCDDRV_MaskInt	@
	ldmfd	sp, {fp, sp, pc}	@
.L1019:
	mov	r0, r3	@, D.42780
	movw	r2, #7576	@,
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
	beq	.L1028	@,
	bl	VCTRL_GetChanVoQue	@
	subs	r3, r0, #0	@ pstVoQue,
	streq	r3, [r8, #0]	@ pstVoQue,* pNewImgNum
	streq	r3, [r7, #0]	@ pstVoQue,* pReadImgNum
	streq	r3, [r6, #0]	@ pstVoQue,* pRefImgNum
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	mov	r2, r8	@, pNewImgNum
	mov	r1, r7	@, pReadImgNum
	bl	GetQueueImgNum	@
	ldr	r2, [r4, r5, asl #2]	@ temp.3785, s_pstVfmwChan
	ldr	r3, [r2, #1032]	@ D.42611, <variable>.eVidStd
	cmp	r3, #0	@ D.42611,
	beq	.L1029	@,
	cmp	r3, #16	@ D.42611,
	beq	.L1030	@,
	cmp	r3, #15	@ D.42611,
	movweq	r3, #:lower16:11374480	@ tmp149,
	movteq	r3, #:upper16:11374480	@ tmp149,
	movne	r3, #2	@ tmp151,
	ldreq	r3, [r2, r3]	@ <variable>.stSynCtx.unSyntax.stMvcCtx.DPB.size,
	str	r3, [r6, #0]	@ tmp151,* pRefImgNum
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L1029:
	movw	r1, #:lower16:278128	@ tmp145,
	movt	r1, #:upper16:278128	@ tmp145,
	ldr	r0, [r2, r1]	@ <variable>.stSynCtx.unSyntax.stH264Ctx.DPB.size,
	str	r0, [r6, #0]	@ <variable>.stSynCtx.unSyntax.stH264Ctx.DPB.size,* pRefImgNum
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L1028:
	mov	r0, ip	@, tmp141
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #7303	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L1030:
	movw	lr, #:lower16:2211864	@ tmp147,
	movt	lr, #:upper16:2211864	@ tmp147,
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
	bhi	.L1051	@,
	cmp	r1, #0	@ pstChanState,
	beq	.L1038	@,
	movw	r6, #:lower16:.LANCHOR0	@ tmp205,
	movt	r6, #:upper16:.LANCHOR0	@ tmp205,
	mov	r0, r1	@, pstChanState
	mov	r1, #108	@,
	mov	r7, #0	@ tmp144,
	str	r7, [fp, #-40]	@ tmp144, RefNum
	str	r7, [fp, #-44]	@ tmp144, ReadNum
	str	r7, [fp, #-48]	@ tmp144, NewNum
	bl	__memzero	@
	ldr	r1, [r6, r5, asl #2]	@ D.39308, s_pstVfmwChan
	cmp	r1, r7	@ D.39308,
	beq	.L1038	@,
	add	r1, r1, #1600	@, D.39308,
	mov	r0, r4	@, pstChanState
	add	r1, r1, #4	@,,
	mov	r2, #108	@,
	bl	memcpy	@
	ldr	r0, [r6, r5, asl #2]	@ temp.3820, s_pstVfmwChan
	movw	r3, #:lower16:206858	@ tmp155,
	movt	r3, #:upper16:206858	@ tmp155,
	ldrsb	lr, [r0, r3]	@ temp.3819, <variable>.FspInst.s32DecFsNum
	cmp	lr, r7	@ temp.3819,
	ble	.L1035	@,
	movw	r1, #:lower16:241310	@ tmp163,
	movt	r1, #:upper16:241310	@ tmp163,
	add	r3, r0, r1	@ tmp163, temp.3820, tmp163
	rsb	lr, lr, lr, asl #4	@, tmp160, temp.3819, temp.3819,
	ldrsb	r2, [r3, #0]	@ <variable>.DispState, <variable>.DispState
	mov	lr, lr, asl #2	@ D.48023, tmp160,
	sub	ip, lr, #60	@ tmp209, D.48023,
	cmp	r2, #3	@ <variable>.DispState,
	ubfx	r2, ip, #2, #1	@ tmp213, tmp209,,
	beq	.L1052	@,
.L1040:
	mov	r3, #60	@ ivtmp.3815,
	cmp	r3, lr	@ ivtmp.3815, D.48023
	beq	.L1035	@,
	cmp	r2, #0	@ tmp213,
	beq	.L1037	@,
	movw	ip, #:lower16:241370	@ tmp228,
	movt	ip, #:upper16:241370	@ tmp228,
	add	r1, r0, ip	@ tmp228, temp.3820, tmp228
	add	r3, r3, #60	@ ivtmp.3815, ivtmp.3815,
	ldrsb	r2, [r1, #0]	@ <variable>.DispState, <variable>.DispState
	cmp	r2, #3	@ <variable>.DispState,
	addeq	r7, r7, #1	@ s32DecodedFrameNum, s32DecodedFrameNum,
	cmp	r3, lr	@ ivtmp.3815, D.48023
	bne	.L1037	@,
	b	.L1035	@
.L1045:
	add	r3, r1, #60	@ ivtmp.3815, tmp214,
	cmp	r3, lr	@ ivtmp.3815, D.48023
	beq	.L1035	@,
.L1037:
	movw	r2, #:lower16:241310	@ tmp219,
	movt	r2, #:upper16:241310	@ tmp219,
	add	r1, r3, #60	@ tmp214, ivtmp.3815,
	add	r8, r0, r3	@ tmp217, temp.3820, ivtmp.3815
	add	ip, r0, r1	@ tmp222, temp.3820, tmp214
	mov	r3, r2	@ tmp224, tmp219
	add	r2, r8, r2	@ tmp219, tmp217, tmp219
	add	r3, ip, r3	@ tmp224, tmp222, tmp224
	ldrsb	r2, [r2, #0]	@ <variable>.DispState, <variable>.DispState
	ldrsb	ip, [r3, #0]	@ <variable>.DispState, <variable>.DispState
	cmp	r2, #3	@ <variable>.DispState,
	addeq	r7, r7, #1	@ s32DecodedFrameNum, s32DecodedFrameNum,
	cmp	ip, #3	@ <variable>.DispState,
	bne	.L1045	@,
	add	r3, r1, #60	@ ivtmp.3815, tmp214,
	add	r7, r7, #1	@ s32DecodedFrameNum, s32DecodedFrameNum,
	cmp	r3, lr	@ ivtmp.3815, D.48023
	bne	.L1037	@,
.L1035:
	str	r7, [r4, #92]	@ prephitmp.3800, <variable>.wait_disp_frame_num
	movw	ip, #:lower16:206858	@ tmp168,
	ldr	lr, [r6, r5, asl #2]	@ tmp167, s_pstVfmwChan
	movt	ip, #:upper16:206858	@ tmp168,
	sub	r2, fp, #44	@,,
	sub	r3, fp, #48	@,,
	mov	r0, r5	@, ChanID
	sub	r1, fp, #40	@,,
	ldrsb	ip, [lr, ip]	@ <variable>.FspInst.s32DecFsNum, <variable>.FspInst.s32DecFsNum
	str	ip, [r4, #100]	@ <variable>.FspInst.s32DecFsNum, <variable>.total_disp_frame_num
	bl	VCTRL_GetChanImgNum	@
	mov	r1, #300	@ tmp179,
	mla	r3, r1, r5, r6	@ tmp180, tmp179, ChanID, tmp205
	ldr	ip, [fp, #-48]	@ NewNum, NewNum
	ldr	r2, [fp, #-44]	@ ReadNum, ReadNum
	sub	r1, fp, #96	@,,
	mov	r0, r5	@, ChanID
	add	r2, ip, r2	@ tmp175, NewNum, ReadNum
	str	r2, [r4, #56]	@ tmp175, <variable>.decoded_1d_frame_num
	ldr	ip, [r3, #1464]	@ <variable>.u32IsFieldFlag, <variable>.u32IsFieldFlag
	str	ip, [r4, #104]	@ <variable>.u32IsFieldFlag, <variable>.is_field_flg
	ldr	r2, [r3, #1452]	@ <variable>.u32FrFrameRate, <variable>.u32FrFrameRate
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
	movw	r3, #:lower16:267360	@ tmp198,
	movt	r3, #:upper16:267360	@ tmp198,
	cmp	r0, #10	@ ScdInstInfo.numReadSegFail,
	movle	r2, #0	@, tmp195
	movgt	r2, #1	@, tmp195
	str	r2, [r4, #88]	@ tmp195, <variable>.stream_not_enough
	ldr	ip, [r6, r5, asl #2]	@ tmp197, s_pstVfmwChan
	ldrb	r1, [ip, r3]	@ zero_extendqisi2	@ tmp200,
	and	r0, r1, #1	@ tmp202, tmp200,
	str	r0, [r4, #96]	@ tmp202, <variable>.mpeg4_shorthead
.L1038:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1051:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #1167	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC194	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC194	@,
	bl	dprint_vfmw	@
	b	.L1038	@
.L1052:
	mov	r7, #1	@ s32DecodedFrameNum,
	b	.L1040	@
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
	beq	.L1054	@,
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp157,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp157,
	ldr	r3, [r3, #32]	@ D.42192, g_vdm_hal_fun_ptr.pfun_VDMHAL_CloseHAL
	cmp	r3, #0	@ D.42192,
	beq	.L1055	@,
	mov	r0, #0	@,
	blx	r3	@ D.42192
.L1056:
	ldr	r1, [r4, #4]	@, <variable>.VirAddr
	ldr	r0, [r4, #8]	@, <variable>.PhyAddr
	bl	MEM_ReleaseMemBlock	@
	mov	r0, r4	@, pstDrvMem
	mov	r1, #16	@,
	bl	__memzero	@
.L1054:
	mov	r0, r7	@, PhyAddr
	mov	r1, r6	@, VirAddr
	mov	r2, r5	@, Length
	bl	MEM_DelMemRecord	@
	ldr	r6, [r4, #28]	@ Length.3848, <variable>.Length
	ldr	r5, [r4, #24]	@ PhyAddr.3846, <variable>.PhyAddr
	cmp	r6, #0	@ Length.3848,
	ldr	r7, [r4, #20]	@ VirAddr.3847, <variable>.VirAddr
	bne	.L1064	@,
.L1057:
	mov	r1, r7	@, VirAddr.3847
	mov	r2, r6	@, Length.3848
	mov	r0, r5	@, PhyAddr.3846
	bl	MEM_DelMemRecord	@
	bl	SM_InstInit	@
	ldr	r5, [r4, #60]	@ Length.3855, <variable>.Length
	ldr	r7, [r4, #56]	@ PhyAddr.3853, <variable>.PhyAddr
	cmp	r5, #0	@ Length.3855,
	ldr	r6, [r4, #52]	@ VirAddr.3854, <variable>.VirAddr
	bne	.L1065	@,
.L1058:
	mov	r0, r7	@, PhyAddr.3853
	mov	r1, r6	@, VirAddr.3854
	mov	r2, r5	@, Length.3855
	bl	MEM_DelMemRecord	@
	ldr	r5, [r4, #108]	@ Length.3860, <variable>.stBpdReg.Length
	ldr	r7, [r4, #104]	@ PhyAddr.3858, <variable>.stBpdReg.PhyAddr
	cmp	r5, #0	@ Length.3860,
	ldr	r6, [r4, #100]	@ VirAddr.3859, <variable>.stBpdReg.VirAddr
	bne	.L1066	@,
.L1059:
	mov	r0, r7	@, PhyAddr.3858
	mov	r1, r6	@, VirAddr.3859
	mov	r2, r5	@, Length.3860
	bl	MEM_DelMemRecord	@
	ldr	r5, [r4, #92]	@ Length.3865, <variable>.Length
	ldr	r7, [r4, #88]	@ PhyAddr.3863, <variable>.PhyAddr
	cmp	r5, #0	@ Length.3865,
	ldr	r6, [r4, #84]	@ VirAddr.3864, <variable>.VirAddr
	bne	.L1067	@,
.L1060:
	mov	r0, r7	@, PhyAddr.3863
	mov	r1, r6	@, VirAddr.3864
	mov	r2, r5	@, Length.3865
	bl	MEM_DelMemRecord	@
	ldr	r5, [r4, #76]	@ Length.3870, <variable>.stFodReg.Length
	ldr	r7, [r4, #72]	@ PhyAddr.3868, <variable>.stFodReg.PhyAddr
	cmp	r5, #0	@ Length.3870,
	ldr	r6, [r4, #68]	@ VirAddr.3869, <variable>.stFodReg.VirAddr
	bne	.L1068	@,
.L1061:
	mov	r0, r7	@, PhyAddr.3868
	mov	r1, r6	@, VirAddr.3869
	mov	r2, r5	@, Length.3870
	bl	MEM_DelMemRecord	@
	ldr	r7, [r4, #124]	@ Length.3875, <variable>.stSystemReg.Length
	ldr	r5, [r4, #120]	@ PhyAddr.3873, <variable>.stSystemReg.PhyAddr
	cmp	r7, #0	@ Length.3875,
	ldr	r6, [r4, #116]	@ VirAddr.3874, <variable>.stSystemReg.VirAddr
	beq	.L1062	@,
	mov	r0, r5	@, PhyAddr.3873
	mov	r1, r6	@, VirAddr.3874
	bl	MEM_UnmapRegisterAddr	@
	add	r0, r4, #112	@, pstDrvMem,
	mov	r1, #16	@,
	bl	__memzero	@
.L1062:
	mov	r2, r7	@, Length.3875
	mov	r1, r6	@, VirAddr.3874
	mov	r0, r5	@, PhyAddr.3873
	bl	MEM_DelMemRecord	@
	mov	r0, #127	@,
	mov	r1, #0	@,
	bl	free_irq	@
	mov	r0, #136	@,
	mov	r1, #0	@,
	bl	free_irq	@
	mov	r0, #0	@,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L1068:
	mov	r0, r7	@, PhyAddr.3868
	mov	r1, r6	@, VirAddr.3869
	bl	MEM_UnmapRegisterAddr	@
	add	r0, r4, #64	@, pstDrvMem,
	mov	r1, #16	@,
	bl	__memzero	@
	b	.L1061	@
.L1067:
	mov	r0, r7	@, PhyAddr.3863
	mov	r1, r6	@, VirAddr.3864
	bl	MEM_UnmapRegisterAddr	@
	add	r0, r4, #80	@, pstDrvMem,
	mov	r1, #16	@,
	bl	__memzero	@
	b	.L1060	@
.L1066:
	mov	r0, r7	@, PhyAddr.3858
	mov	r1, r6	@, VirAddr.3859
	bl	MEM_UnmapRegisterAddr	@
	add	r0, r4, #96	@, pstDrvMem,
	mov	r1, #16	@,
	bl	__memzero	@
	b	.L1059	@
.L1065:
	mov	r0, r7	@, PhyAddr.3853
	mov	r1, r6	@, VirAddr.3854
	bl	MEM_UnmapRegisterAddr	@
	add	r0, r4, #48	@, pstDrvMem,
	mov	r1, #16	@,
	bl	__memzero	@
	b	.L1058	@
.L1064:
	mov	r0, #0	@,
	bl	SM_CloseSCDDrv	@
	ldr	r0, [r4, #24]	@, <variable>.PhyAddr
	ldr	r1, [r4, #20]	@, <variable>.VirAddr
	bl	MEM_ReleaseMemBlock	@
	add	r0, r4, #16	@, pstDrvMem,
	mov	r1, #16	@,
	bl	__memzero	@
	b	.L1057	@
.L1055:
	mov	r0, r3	@, D.42192
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #6564	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L1056	@
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
	bne	.L1093	@,
	add	r6, r4, #96	@ pstMem.3901, pstDrvMem,
	ldr	r1, [r4, #52]	@, <variable>.VirAddr
	ldr	r2, [r4, #60]	@, <variable>.Length
	ldr	r0, [r4, #56]	@, <variable>.PhyAddr
	bl	MEM_AddMemRecord	@
	movw	r0, #:lower16:-121241600	@,
	mov	r1, #4096	@,
	movt	r0, #:upper16:-121241600	@,
	mov	r2, r6	@, pstMem.3901
	bl	MEM_MapRegisterAddr	@
	cmp	r0, #0	@,
	bne	.L1090	@,
	movw	r5, #:lower16:g_vdm_hal_fun_ptr	@ tmp161,
	movt	r5, #:upper16:g_vdm_hal_fun_ptr	@ tmp161,
	ldr	r3, [r5, #16]	@ D.42032, g_vdm_hal_fun_ptr.pfun_BPDDRV_OpenHardware
	cmp	r3, #0	@ D.42032,
	beq	.L1090	@,
	blx	r3	@ D.42032
	cmp	r0, #0	@,
	bne	.L1090	@,
	add	r8, r4, #80	@ pstMem.3905, pstDrvMem,
	ldr	r1, [r4, #100]	@, <variable>.stBpdReg.VirAddr
	ldr	r2, [r4, #108]	@, <variable>.stBpdReg.Length
	ldr	r0, [r4, #104]	@, <variable>.stBpdReg.PhyAddr
	bl	MEM_AddMemRecord	@
	movw	r0, #:lower16:-121389056	@,
	mov	r1, #4096	@,
	movt	r0, #:upper16:-121389056	@,
	mov	r2, r8	@, pstMem.3905
	bl	MEM_MapRegisterAddr	@
	subs	r6, r0, #0	@ D.42061,
	bne	.L1079	@,
	sub	r7, fp, #68	@ tmp197,,
	ldr	r1, [r4, #84]	@, <variable>.VirAddr
	ldr	r2, [r4, #92]	@, <variable>.Length
	ldr	r0, [r4, #88]	@, <variable>.PhyAddr
	bl	MEM_AddMemRecord	@
	mov	r3, r6	@, D.42061
	mov	r0, r7	@, tmp197
	mov	r1, #20	@,
	movw	r2, #:lower16:.LC195	@,
	movt	r2, #:upper16:.LC195	@,
	bl	snprintf	@
	ldr	r3, [r5, #24]	@ D.42072, g_vdm_hal_fun_ptr.pfun_VDMHAL_GetHalMemSize
	cmp	r3, #0	@ D.42072,
	beq	.L1079	@,
	blx	r3	@ D.42072
	subs	r2, r0, #0	@ Size,
	ble	.L1079	@,
	mov	r1, r6	@, D.42061
	mov	r0, r7	@, tmp197
	mov	r3, r4	@, pstDrvMem
	str	r6, [sp, #0]	@ D.42061,
	bl	MEM_AllocMemBlock	@
	subs	r8, r0, #0	@ D.42085,
	bne	.L1081	@,
	sub	r6, fp, #48	@ tmp176,,
	ldr	r2, [r4, #12]	@, <variable>.Length
	ldr	r1, [r4, #4]	@, <variable>.VirAddr
	ldr	r0, [r4, #8]	@, <variable>.PhyAddr
	bl	MEM_AddMemRecord	@
	mov	r1, #12	@,
	mov	r0, r6	@, tmp176
	bl	__memzero	@
	ldr	r3, [r5, #28]	@ D.42095, g_vdm_hal_fun_ptr.pfun_VDMHAL_OpenHAL
	ldr	r1, [r4, #8]	@ <variable>.PhyAddr, <variable>.PhyAddr
	ldr	r2, [r4, #12]	@ <variable>.Length, <variable>.Length
	cmp	r3, #0	@ D.42095,
	str	r8, [fp, #-40]	@ D.42085, VDMOpenParam.VdhId
	str	r1, [fp, #-48]	@ <variable>.PhyAddr, VDMOpenParam.MemBaseAddr
	str	r2, [fp, #-44]	@ <variable>.Length, VDMOpenParam.Size
	beq	.L1081	@,
	mov	r0, r6	@, tmp176
	blx	r3	@ D.42095
	cmp	r0, #0	@,
	bne	.L1081	@,
	mov	r0, #0	@,
	add	r5, r4, #16	@ pstMem.3915, pstDrvMem,
	bl	VDMDRV_Init	@
	mov	r1, #20	@,
	mov	r3, #0	@,
	mov	r0, r7	@, tmp197
	movw	r2, #:lower16:.LC196	@,
	movt	r2, #:upper16:.LC196	@,
	bl	snprintf	@
	mov	ip, #0	@ tmp184,
	mov	r0, r7	@, tmp197
	mov	r1, ip	@, tmp184
	mov	r2, #716800	@,
	mov	r3, r5	@, pstMem.3915
	str	ip, [sp, #0]	@ tmp184,
	bl	MEM_AllocMemBlock	@
	subs	r6, r0, #0	@ D.42110,
	bne	.L1093	@,
	ldr	r1, [r4, #20]	@, <variable>.VirAddr
	ldr	r2, [r4, #28]	@, <variable>.Length
	ldr	r0, [r4, #24]	@, <variable>.PhyAddr
	bl	MEM_AddMemRecord	@
	mov	r2, r6	@, D.42110
	ldr	r0, [r4, #24]	@, <variable>.PhyAddr
	ldr	r1, [r4, #28]	@, <variable>.Length
	bl	SM_OpenSCDDrv	@
	subs	r6, r0, #0	@ D.42113,
	bne	.L1093	@,
	bl	SM_InstInit	@
	mov	r2, r6	@, D.42113
	mov	r0, #127	@,
	movw	r1, #:lower16:VCTRL_Isr_0	@,
	mov	r3, #32	@,
	movt	r1, #:upper16:VCTRL_Isr_0	@,
	str	r6, [sp, #4]	@ D.42113,
	movw	ip, #:lower16:.LC197	@ tmp191,
	movt	ip, #:upper16:.LC197	@ tmp191,
	str	ip, [sp, #0]	@ tmp191,
	bl	request_threaded_irq	@
	subs	ip, r0, #0	@ D.44993,
	bne	.L1093	@,
	mov	r2, ip	@, D.44993
	mov	r0, #136	@,
	movw	r1, #:lower16:VCTRL_Scd_Isr	@,
	mov	r3, #32	@,
	movt	r1, #:upper16:VCTRL_Scd_Isr	@,
	str	ip, [sp, #4]	@ D.44993,
	movw	lr, #:lower16:.LC198	@ tmp194,
	movt	lr, #:upper16:.LC198	@ tmp194,
	str	lr, [sp, #0]	@ tmp194,
	bl	request_threaded_irq	@
	cmp	r0, #0	@ D.45000
	bne	.L1093	@,
.L1073:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1090:
	mov	r0, r6	@, pstMem.3901
.L1094:
	mov	r1, #16	@,
	bl	__memzero	@
	mov	r0, r4	@, pstDrvMem
	bl	CloseDrivers	@
	mvn	r0, #0	@ D.42005,
	b	.L1073	@
.L1079:
	mov	r0, r8	@, pstMem.3905
	b	.L1094	@
.L1093:
	mov	r0, r5	@, pstMem.3915
	b	.L1094	@
.L1081:
	mov	r1, #16	@,
	mov	r0, r4	@, pstDrvMem
	bl	__memzero	@
	mov	r0, r4	@, pstDrvMem
	bl	CloseDrivers	@
	mvn	r0, #0	@ D.42005,
	b	.L1073	@
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
	ldr	r3, [r5, r0, asl #2]	@ D.41542, s_pstVfmwChan
	cmp	r3, #0	@ D.41542,
	beq	.L1105	@,
	ldr	r8, [r3, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r8, #18	@ <variable>.eVidStd,
	bne	.L1106	@,
	ldr	r3, [r3, #968]	@ <variable>.s32UsrdecFrameNum, <variable>.s32UsrdecFrameNum
	cmp	r3, #2	@ <variable>.s32UsrdecFrameNum,
	ble	.L1107	@,
	bl	FSP_IsNewFsAvalible	@
	cmp	r0, #1	@ D.41555,
	bne	.L1108	@,
	mov	r1, r0	@, D.41555
	mov	r0, r6	@, ChanID
	bl	FSP_NewLogicFs	@
	subs	sl, r0, #0	@ id,
	blt	.L1109	@,
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
	beq	.L1110	@,
	ldr	r2, [r4, #512]	@ D.41570, <variable>.pstDecodeFs
	cmp	r2, #0	@ D.41570,
	beq	.L1103	@,
	ldr	r3, [r4, #516]	@ D.41572, <variable>.pstDispOutFs
	cmp	r3, #0	@ D.41572,
	beq	.L1103	@,
	ldr	ip, [r4, #520]	@ D.41574, <variable>.pstTfOutFs
	cmp	ip, #0	@ D.41574,
	beq	.L1103	@,
	ldr	lr, [ip, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	mov	r0, r8	@, <variable>.eVidStd
	ldr	r2, [r2, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	movw	r1, #:lower16:.LC205	@,
	ldr	r3, [r3, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	movt	r1, #:upper16:.LC205	@,
	str	lr, [sp, #0]	@ <variable>.PhyAddr,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #512]	@ <variable>.pstDecodeFs, <variable>.pstDecodeFs
	mov	r0, #0	@ D.41546,
	ldr	ip, [r3, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	ip, [r7, #0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	ldr	r2, [r5, r6, asl #2]	@ tmp162, s_pstVfmwChan
	ldr	r1, [r2, #964]	@ <variable>.s32UsrdecFrameSize, <variable>.s32UsrdecFrameSize
	str	r1, [r7, #8]	@ <variable>.s32UsrdecFrameSize, <variable>.Length
.L1097:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L1108:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC201	@,
	movt	r1, #:upper16:.LC201	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41546,
	b	.L1097	@
.L1106:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC199	@,
	movt	r1, #:upper16:.LC199	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41546,
	b	.L1097	@
.L1107:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC200	@,
	movt	r1, #:upper16:.LC200	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41546,
	b	.L1097	@
.L1103:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC206	@,
	movt	r1, #:upper16:.LC206	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41546,
	b	.L1097	@
.L1109:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC202	@,
	movt	r1, #:upper16:.LC202	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41546,
	b	.L1097	@
.L1105:
	mov	r0, r3	@, D.41542
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #5299	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41546,
	b	.L1097	@
.L1110:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC204	@,
	movw	r2, #5330	@,
	movt	r1, #:upper16:.LC204	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41546,
	b	.L1097	@
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
	beq	.L1120	@,
	ldr	r3, [r8, #4]	@ <variable>.s32IsFrameValid, <variable>.s32IsFrameValid
	cmp	r3, #1	@ <variable>.s32IsFrameValid,
	beq	.L1114	@,
	mov	r0, r7	@, ChanID
	mov	r1, r5	@, PicBufID
	mov	r2, #0	@,
	bl	FSP_ClearLogicFs	@
	mov	r0, #0	@ D.41473,
.L1113:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L1114:
	ldr	r0, [r8, #36]	@, <variable>.s32CbPhyAddr
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@,
	beq	.L1121	@,
.L1115:
	mov	r0, r7	@, ChanID
	mov	r1, r5	@, PicBufID
	bl	FSP_GetFsImagePtr	@
	subs	r4, r0, #0	@ pLogic,
	beq	.L1122	@,
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
	ldr	r1, [r8, #28]	@ temp.3982, <variable>.s32LumaPhyAddr
	str	r1, [r4, #88]	@ temp.3982, <variable>.top_luma_phy_addr
	mov	r0, r1	@, temp.3982
	str	r1, [r4, #120]	@ temp.3982, <variable>.luma_2d_phy_addr
	str	r1, [r4, #104]	@ temp.3982, <variable>.luma_phy_addr
	ldr	lr, [r8, #36]	@ temp.3983, <variable>.s32CbPhyAddr
	str	lr, [r4, #108]	@ temp.3983, <variable>.chrom_phy_addr
	str	lr, [r4, #92]	@ temp.3983, <variable>.top_chrom_phy_addr
	str	lr, [r4, #124]	@ temp.3983, <variable>.chrom_2d_phy_addr
	bl	MEM_Phy2Vir	@
	str	r0, [r4, #32]	@ D.41496, <variable>.luma_vir_addr
	str	r0, [r4, #48]	@ D.41496, <variable>.luma_2d_vir_addr
	ldr	r0, [r4, #92]	@, <variable>.top_chrom_phy_addr
	bl	MEM_Phy2Vir	@
	ldr	ip, [r4, #88]	@ <variable>.top_luma_phy_addr, <variable>.top_luma_phy_addr
	str	r0, [r4, #36]	@ D.41499, <variable>.chrom_vir_addr
	str	r0, [r4, #52]	@ D.41499, <variable>.chrom_2d_vir_addr
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
	ldr	r0, [r8, #20]	@ temp.3987, <variable>.s32YWidth
	str	r0, [r4, #172]	@ temp.3987, <variable>.disp_width
	mov	r1, r0, lsr sl	@ tmp179, temp.3987,
	ldr	r3, [r8, #24]	@ temp.3989, <variable>.s32YHeight
	str	r1, [r4, #180]	@ tmp179, <variable>.disp_center_x
	str	r3, [r4, #176]	@ temp.3989, <variable>.disp_height
	mov	ip, r3, lsr sl	@ tmp180, temp.3989,
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
	beq	.L1123	@,
	str	r0, [r4, #472]	@ eYuvFormat, <variable>.BTLInfo.YUVFormat
	mov	r2, sl	@, tmp165
	ldr	ip, [r8, #44]	@ <variable>.s32ChromStride, <variable>.s32ChromStride
	mov	sl, #18	@ tmp194,
	mov	r0, r7	@, ChanID
	mov	r1, r5	@, PicBufID
	str	ip, [r4, #448]	@ <variable>.s32ChromStride, <variable>.BTLInfo.u32CStride
	ldr	r3, [r8, #48]	@ <variable>.s32ChromCrStride, <variable>.s32ChromCrStride
	str	r3, [r4, #444]	@ <variable>.s32ChromCrStride, <variable>.BTLInfo.u32CrStride
	ldr	lr, [r8, #40]	@ <variable>.s32CrPhyAddr, <variable>.s32CrPhyAddr
	str	sl, [r4, #380]	@ tmp194, <variable>.ImageDnr.video_standard
	str	lr, [r4, #452]	@ <variable>.s32CrPhyAddr, <variable>.BTLInfo.u32CrAddr
	bl	FSP_SetDisplay	@
	movw	ip, #:lower16:.LANCHOR0	@ tmp195,
	movt	ip, #:upper16:.LANCHOR0	@ tmp195,
	str	r4, [sp, #0]	@ pLogic,
	mov	r1, sl	@, tmp194
	mov	r0, r7	@, ChanID
	ldr	r2, [ip, r7, asl #2]	@ D.41527, s_pstVfmwChan
	add	ip, r2, #250880	@, D.41527,
	add	r2, ip, #616	@, tmp3,
	add	r3, ip, #624	@,,
	bl	InsertImgToVoQueue	@
	cmp	r0, #1	@,
	moveq	r0, r6	@ D.41473, tmp166
	beq	.L1113	@,
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
	mvn	r0, #0	@ D.41473,
	b	.L1113	@
.L1121:
	ldr	r1, [r8, #4]	@ <variable>.s32IsFrameValid, <variable>.s32IsFrameValid
	cmp	r1, #1	@ <variable>.s32IsFrameValid,
	bne	.L1115	@,
	ldr	r2, [r8, #36]	@, <variable>.s32CbPhyAddr
	movw	r1, #:lower16:.LC208	@,
	movt	r1, #:upper16:.LC208	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41473,
	b	.L1113	@
.L1120:
	ldr	r2, [r8, #28]	@, <variable>.s32LumaPhyAddr
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC207	@,
	movt	r1, #:upper16:.LC207	@,
	bl	dprint_vfmw	@
	mov	r0, r5	@ D.41473, PicBufID
	b	.L1113	@
.L1123:
	mov	r0, sl	@, tmp165
	movw	r1, #:lower16:.LC210	@,
	movt	r1, #:upper16:.LC210	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41473,
	b	.L1113	@
.L1122:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC209	@,
	movw	r2, #5133	@,
	movt	r1, #:upper16:.LC209	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41473,
	b	.L1113	@
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
	ldr	lr, [r3, r0, asl #2]	@ D.41587, s_pstVfmwChan
	cmp	lr, #0	@ D.41587,
	beq	.L1131	@,
	cmp	r1, #0	@ pUsrdecFrame,
	beq	.L1132	@,
	ldr	r2, [lr, #1032]	@ D.41594, <variable>.eVidStd
	cmp	r2, #18	@ D.41594,
	bne	.L1133	@,
	mov	r4, r1	@ pUsrdecFrame, pUsrdecFrame
	add	lr, lr, #976	@ tmp146, D.41587,
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
	cmp	r0, #0	@ D.41599
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC213	@,
	movt	r1, #:upper16:.LC213	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41591,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1133:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC212	@,
	movt	r1, #:upper16:.LC212	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41591,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1132:
	mov	r0, r1	@, pUsrdecFrame
	movw	r2, #5382	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC211	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC211	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41591,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1131:
	mov	r0, lr	@, D.41587
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #5381	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41591,
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
	mov	r2, #0	@,
	mov	r5, r1	@ ImgID, ImgID
	mov	r4, r0	@ pCtx, pCtx
	ldr	r0, [r0, #360]	@, <variable>.ChanID
	bl	FSP_SetDisplay	@
	mov	r1, r5	@, ImgID
	ldr	r0, [r4, #360]	@, <variable>.ChanID
	bl	FSP_GetFsImagePtr	@
	subs	r5, r0, #0	@ pImg,
	beq	.L1135	@,
	ldr	r0, [r4, #360]	@, <variable>.ChanID
	mov	r6, #0	@ tmp142,
	ldr	r1, [r5, #212]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	str	r6, [r5, #212]	@ tmp142, <variable>.p_usrdat
	ldr	r1, [r5, #216]	@, <variable>.p_usrdat
	ldr	r0, [r4, #360]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	str	r6, [r5, #216]	@ tmp142, <variable>.p_usrdat
.L1135:
	mov	r0, #1	@,
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
	ldr	r6, [r0, #352]	@ D.41433, <variable>.ImageQue.ResetMagicWord
	mov	r4, r0	@ pCtx, pCtx
	mov	r5, r1	@ pstExtraData, pstExtraData
	mov	r1, #368	@,
	bl	__memzero	@
	add	r0, r4, #8	@, pCtx,
	str	r6, [r4, #352]	@ D.41433, <variable>.ImageQue.ResetMagicWord
	bl	ResetVoQueue	@
	movw	r3, #:lower16:.LANCHOR0	@ tmp207,
	movt	r3, #:upper16:.LANCHOR0	@ tmp207,
	str	r5, [r4, #0]	@ pstExtraData, <variable>.pstExtraData
	ldr	r2, [r3, #0]	@ temp.4069, s_pstVfmwChan
	cmp	r2, #0	@ temp.4069,
	beq	.L1138	@,
	add	r0, r2, #250880	@ tmp157, temp.4069,
	add	r2, r0, #616	@ tmp157, tmp157,
	cmp	r4, r2	@ pCtx, tmp157
	moveq	r3, #0	@ i,
	beq	.L1139	@,
.L1138:
	ldr	r2, [r3, #4]	@ temp.4071, s_pstVfmwChan
	cmp	r2, #0	@ temp.4071,
	beq	.L1140	@,
	add	ip, r2, #250880	@ tmp160, temp.4071,
	add	r1, ip, #616	@ tmp160, tmp160,
	cmp	r4, r1	@ pCtx, tmp160
	moveq	r3, #1	@ i,
	beq	.L1139	@,
.L1140:
	ldr	r2, [r3, #8]	@ temp.4073, s_pstVfmwChan
	cmp	r2, #0	@ temp.4073,
	beq	.L1141	@,
	add	r2, r2, #250880	@ tmp163, temp.4073,
	add	lr, r2, #616	@ tmp163, tmp163,
	cmp	r4, lr	@ pCtx, tmp163
	moveq	r3, #2	@ i,
	beq	.L1139	@,
.L1141:
	ldr	r2, [r3, #12]	@ temp.4075, s_pstVfmwChan
	cmp	r2, #0	@ temp.4075,
	beq	.L1142	@,
	add	r1, r2, #250880	@ tmp166, temp.4075,
	add	r0, r1, #616	@ tmp166, tmp166,
	cmp	r4, r0	@ pCtx, tmp166
	moveq	r3, #3	@ i,
	beq	.L1139	@,
.L1142:
	ldr	r2, [r3, #16]	@ temp.4077, s_pstVfmwChan
	cmp	r2, #0	@ temp.4077,
	beq	.L1143	@,
	add	lr, r2, #250880	@ tmp169, temp.4077,
	add	ip, lr, #616	@ tmp169, tmp169,
	cmp	r4, ip	@ pCtx, tmp169
	moveq	r3, #4	@ i,
	beq	.L1139	@,
.L1143:
	ldr	r2, [r3, #20]	@ temp.4079, s_pstVfmwChan
	cmp	r2, #0	@ temp.4079,
	beq	.L1144	@,
	add	r0, r2, #250880	@ tmp172, temp.4079,
	add	r2, r0, #616	@ tmp172, tmp172,
	cmp	r4, r2	@ pCtx, tmp172
	moveq	r3, #5	@ i,
	beq	.L1139	@,
.L1144:
	ldr	r2, [r3, #24]	@ temp.4081, s_pstVfmwChan
	cmp	r2, #0	@ temp.4081,
	beq	.L1145	@,
	add	ip, r2, #250880	@ tmp175, temp.4081,
	add	r1, ip, #616	@ tmp175, tmp175,
	cmp	r4, r1	@ pCtx, tmp175
	moveq	r3, #6	@ i,
	beq	.L1139	@,
.L1145:
	ldr	r2, [r3, #28]	@ temp.4083, s_pstVfmwChan
	cmp	r2, #0	@ temp.4083,
	beq	.L1146	@,
	add	r2, r2, #250880	@ tmp178, temp.4083,
	add	lr, r2, #616	@ tmp178, tmp178,
	cmp	r4, lr	@ pCtx, tmp178
	moveq	r3, #7	@ i,
	beq	.L1139	@,
.L1146:
	ldr	r2, [r3, #32]	@ temp.4085, s_pstVfmwChan
	cmp	r2, #0	@ temp.4085,
	beq	.L1147	@,
	add	r1, r2, #250880	@ tmp181, temp.4085,
	add	r0, r1, #616	@ tmp181, tmp181,
	cmp	r4, r0	@ pCtx, tmp181
	moveq	r3, #8	@ i,
	beq	.L1139	@,
.L1147:
	ldr	r2, [r3, #36]	@ temp.4087, s_pstVfmwChan
	cmp	r2, #0	@ temp.4087,
	beq	.L1148	@,
	add	lr, r2, #250880	@ tmp184, temp.4087,
	add	ip, lr, #616	@ tmp184, tmp184,
	cmp	r4, ip	@ pCtx, tmp184
	moveq	r3, #9	@ i,
	beq	.L1139	@,
.L1148:
	ldr	r2, [r3, #40]	@ temp.4089, s_pstVfmwChan
	cmp	r2, #0	@ temp.4089,
	beq	.L1149	@,
	add	r0, r2, #250880	@ tmp187, temp.4089,
	add	r2, r0, #616	@ tmp187, tmp187,
	cmp	r4, r2	@ pCtx, tmp187
	moveq	r3, #10	@ i,
	beq	.L1139	@,
.L1149:
	ldr	r2, [r3, #44]	@ temp.4091, s_pstVfmwChan
	cmp	r2, #0	@ temp.4091,
	beq	.L1150	@,
	add	ip, r2, #250880	@ tmp190, temp.4091,
	add	r1, ip, #616	@ tmp190, tmp190,
	cmp	r4, r1	@ pCtx, tmp190
	moveq	r3, #11	@ i,
	beq	.L1139	@,
.L1150:
	ldr	r2, [r3, #48]	@ temp.4093, s_pstVfmwChan
	cmp	r2, #0	@ temp.4093,
	beq	.L1151	@,
	add	r2, r2, #250880	@ tmp193, temp.4093,
	add	lr, r2, #616	@ tmp193, tmp193,
	cmp	r4, lr	@ pCtx, tmp193
	moveq	r3, #12	@ i,
	beq	.L1139	@,
.L1151:
	ldr	r2, [r3, #52]	@ temp.4095, s_pstVfmwChan
	cmp	r2, #0	@ temp.4095,
	beq	.L1152	@,
	add	r1, r2, #250880	@ tmp196, temp.4095,
	add	r0, r1, #616	@ tmp196, tmp196,
	cmp	r4, r0	@ pCtx, tmp196
	moveq	r3, #13	@ i,
	beq	.L1139	@,
.L1152:
	ldr	r2, [r3, #56]	@ temp.4097, s_pstVfmwChan
	cmp	r2, #0	@ temp.4097,
	beq	.L1153	@,
	add	lr, r2, #250880	@ tmp199, temp.4097,
	add	ip, lr, #616	@ tmp199, tmp199,
	cmp	r4, ip	@ pCtx, tmp199
	moveq	r3, #14	@ i,
	beq	.L1139	@,
.L1153:
	ldr	r3, [r3, #60]	@ D.45008, s_pstVfmwChan
	cmp	r3, #0	@ D.45008,
	beq	.L1154	@,
	add	r2, r3, #250880	@ tmp202, D.45008,
	add	r3, r2, #616	@ tmp202, tmp202,
	cmp	r4, r3	@ pCtx, tmp202
	beq	.L1155	@,
.L1154:
	mvn	r0, #0	@ tmp204,
	movw	r1, #:lower16:.LC214	@,
	str	r0, [r4, #360]	@ tmp204, <variable>.ChanID
	movt	r1, #:upper16:.LC214	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	mvn	r0, #19	@ D.41446,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1155:
	mov	r3, #15	@ i,
.L1139:
	mov	r0, #1	@ D.41446,
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
	ldr	r1, [r3, r0, asl #2]	@ D.41626, s_pstVfmwChan
	cmp	r1, #0	@ D.41626,
	beq	.L1177	@,
	ldr	r2, [r1, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, #18	@ <variable>.eVidStd,
	ldrls	pc, [pc, r2, asl #2]	@ <variable>.eVidStd
	b	.L1176	@
.L1175:
	.word	.L1161
	.word	.L1162
	.word	.L1163
	.word	.L1164
	.word	.L1165
	.word	.L1166
	.word	.L1167
	.word	.L1176
	.word	.L1168
	.word	.L1169
	.word	.L1170
	.word	.L1170
	.word	.L1170
	.word	.L1171
	.word	.L1165
	.word	.L1172
	.word	.L1173
	.word	.L1176
	.word	.L1174
.L1174:
	add	lr, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, lr, #616	@,,
	bl	USERDEC_Init	@
.L1176:
	ldmfd	sp, {fp, sp, pc}	@
.L1161:
	add	ip, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, ip, #616	@,,
	bl	H264DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1162:
	add	lr, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, lr, #616	@,,
	bl	VC1DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1163:
	add	r3, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, r3, #616	@,,
	bl	MPEG4DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1164:
	add	r0, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, r0, #616	@,,
	bl	MPEG2DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1165:
	ldr	r3, [r3, #84]	@ D.41643, g_SdecFunc.pfun_iMediaSoftDEC_Init
	cmp	r3, #0	@ D.41643,
	ldmeqfd	sp, {fp, sp, pc}	@
	add	r0, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, r0, #616	@,,
	blx	r3	@ D.41643
	ldmfd	sp, {fp, sp, pc}	@
.L1166:
	add	ip, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, ip, #616	@,,
	bl	DIVX3DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1167:
	add	r2, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, r2, #616	@,,
	bl	AVSDEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1168:
	add	r0, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, r0, #616	@,,
	bl	REAL8DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1169:
	add	r3, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, r3, #616	@,,
	bl	REAL9DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1170:
	add	r2, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, r2, #616	@,,
	bl	VP6DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1171:
	add	r3, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, r3, #616	@,,
	bl	VP8DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1172:
	add	ip, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, ip, #616	@,,
	bl	MVC_DEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1173:
	add	lr, r1, #250880	@, D.41626,
	add	r1, r1, #1040	@, D.41626,
	add	r0, lr, #616	@,,
	bl	HEVCDEC_Init	@
	ldmfd	sp, {fp, sp, pc}	@
.L1177:
	mov	r0, r1	@, D.41626
	movw	r2, #5409	@,
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
	bhi	.L1199	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp174,
	movt	r3, #:upper16:.LANCHOR0	@ tmp174,
	ldr	r0, [r3, r0, asl #2]	@ D.41292, s_pstVfmwChan
	cmp	r0, #0	@ D.41292,
	beq	.L1200	@,
	ldr	r2, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r2, #1	@ <variable>.s32IsRun,
	bne	.L1201	@,
	ldr	r1, [r0, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r1, #16	@ <variable>.eVidStd,
	ldrls	pc, [pc, r1, asl #2]	@ <variable>.eVidStd
	b	.L1183	@
.L1197:
	.word	.L1184
	.word	.L1185
	.word	.L1186
	.word	.L1187
	.word	.L1188
	.word	.L1189
	.word	.L1190
	.word	.L1183
	.word	.L1191
	.word	.L1192
	.word	.L1193
	.word	.L1193
	.word	.L1193
	.word	.L1194
	.word	.L1188
	.word	.L1195
	.word	.L1196
.L1193:
	ldr	r2, [r3, #500]	@ g_VdmCharacter, g_VdmCharacter
	tst	r2, #1	@ g_VdmCharacter,
	bne	.L1202	@,
.L1188:
	mov	r0, #1	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
.L1189:
	add	r3, r0, #250880	@, D.41292,
	add	r0, r3, #616	@,,
	bl	DIVX3DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1190:
	add	r2, r0, #250880	@, D.41292,
	add	r0, r2, #616	@,,
	bl	AVSDEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1191:
	add	r1, r0, #250880	@, D.41292,
	add	r0, r1, #616	@,,
	bl	REAL8DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1192:
	add	r0, r0, #250880	@, D.41292,
	add	r0, r0, #616	@,,
	bl	REAL9DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1194:
	add	r1, r0, #250880	@, D.41292,
	add	r0, r1, #616	@,,
	bl	VP8DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1195:
	add	r0, r0, #250880	@, D.41292,
	add	r0, r0, #616	@,,
	bl	MVC_DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1196:
	add	r3, r0, #250880	@, D.41292,
	add	r0, r3, #616	@,,
	bl	HEVCDEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1183:
	mov	r0, #0	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
.L1184:
	add	r0, r0, #250880	@, D.41292,
	add	r0, r0, #616	@,,
	bl	H264DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1185:
	add	ip, r0, #250880	@, D.41292,
	add	r0, ip, #616	@,,
	bl	VC1DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1186:
	add	lr, r0, #250880	@, D.41292,
	add	r0, lr, #616	@,,
	bl	MPEG4DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1187:
	add	ip, r0, #250880	@, D.41292,
	add	r0, ip, #616	@,,
	bl	MPEG2DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1202:
	add	lr, r0, #250880	@, D.41292,
	add	r0, lr, #616	@,,
	bl	VP6DEC_GetImageBuffer	@
	ldmfd	sp, {fp, sp, pc}	@
.L1201:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4855	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC216	@,
	movt	r3, #:upper16:.LC216	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
.L1199:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4853	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC28	@,
	movt	r3, #:upper16:.LC28	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
.L1200:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4854	@,
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
	bhi	.L1242	@,
	movw	r5, #:lower16:.LANCHOR0	@ tmp411,
	movt	r5, #:upper16:.LANCHOR0	@ tmp411,
	ldr	r0, [r5, r0, asl #2]	@ D.42405, s_pstVfmwChan
	cmp	r0, #0	@ D.42405,
	beq	.L1243	@,
	ldr	sl, [r0, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	sl, #1	@ <variable>.s32IsRun,
	bne	.L1244	@,
	ldr	r6, [r0, #28]	@ <variable>.s32StopSyntax, <variable>.s32StopSyntax
	cmp	r6, #0	@ <variable>.s32StopSyntax,
	bne	.L1245	@,
	str	r6, [r0, #816]	@ <variable>.s32StopSyntax, <variable>.s32NoStreamFlag
	mov	r0, r4, asl #2	@, ChanID,
	str	r0, [fp, #-88]	@, %sfp
	bl	OSAL_GetTimeInMs	@
	ldr	r3, [fp, #-88]	@, %sfp
	movw	r7, #:lower16:.LANCHOR3	@ tmp412,
	movt	r7, #:upper16:.LANCHOR3	@ tmp412,
	movw	r1, #:lower16:g_TraceBsPeriod	@ tmp189,
	add	ip, r3, r7	@ tmp185,, tmp412
	movt	r1, #:upper16:g_TraceBsPeriod	@ tmp189,
	ldr	r2, [ip, #-1940]	@ tmp188, last_rec_pos_time
	ldr	r3, [r1, #0]	@ g_TraceBsPeriod, g_TraceBsPeriod
	rsb	r1, r2, r0	@ tmp187, tmp188, currtime
	ldr	r2, [r5, r4, asl #2]	@ tmp197, s_pstVfmwChan
	cmp	r1, r3	@ tmp187, g_TraceBsPeriod
	strhi	r0, [ip, #-1940]	@ currtime, last_rec_pos_time
	movw	r3, #:lower16:.LANCHOR0	@ tmp196,
	movt	r3, #:upper16:.LANCHOR0	@ tmp196,
	ldr	r2, [r2, #1032]	@ D.42424, <variable>.eVidStd
	movls	sl, r6	@ rec_pos_print_flag, <variable>.s32StopSyntax
	sub	r1, r2, #10	@ tmp198, D.42424,
	cmp	r1, #2	@ tmp198,
	bls	.L1246	@,
	cmp	r2, #14	@ D.42424,
	beq	.L1213	@,
	cmp	r2, #4	@ D.42424,
	bne	.L1212	@,
.L1213:
	mov	r0, r4	@, ChanID
	bl	VCTRL_GetImageBuffer	@
	cmp	r0, #1	@,
	bne	.L1247	@,
	ldr	r6, [r5, r4, asl #2]	@ temp.4207, s_pstVfmwChan
	ldr	r2, [r6, #1888]	@ D.42449, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r2, #0	@ D.42449,
	beq	.L1217	@,
	cmp	r2, #1	@ D.42449,
	beq	.L1248	@,
	movw	lr, #:lower16:249192	@ tmp406,
	movt	lr, #:upper16:249192	@ tmp406,
	ldr	r3, [r6, lr]	@ prephitmp.4190, <variable>.FspInst.eFspPartitionState
.L1237:
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC226	@,
	movt	r1, #:upper16:.LC226	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.42403,
.L1205:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1246:
	ldr	lr, [r3, #500]	@ g_VdmCharacter, g_VdmCharacter
	tst	lr, #1	@ g_VdmCharacter,
	beq	.L1213	@,
.L1212:
	cmp	r2, #18	@ D.42424,
	beq	.L1213	@,
	mov	r0, r4	@, ChanID
	bl	VCTRL_GetDecParam	@
	cmp	r0, #0	@,
	beq	.L1213	@,
	cmp	sl, #1	@ rec_pos_print_flag,
	beq	.L1214	@,
	mvn	r0, #1	@ D.42403,
	b	.L1205	@
.L1217:
	ldrb	r2, [r6, #1177]	@ zero_extendqisi2	@ <variable>.stSynExtraData.stSegPacket.IsCurrSegWaitDec, <variable>.stSynExtraData.stSegPacket.IsCurrSegWaitDec
	cmp	r2, #0	@ <variable>.stSynExtraData.stSegPacket.IsCurrSegWaitDec,
	bne	.L1220	@,
	ldr	r1, [r6, #1924]	@ <variable>.stSynExtraData.s32WaitFsFlag, <variable>.stSynExtraData.s32WaitFsFlag
	cmp	r1, #0	@ <variable>.stSynExtraData.s32WaitFsFlag,
	beq	.L1249	@,
.L1220:
	movw	r0, #1208	@ tmp221,
	movw	ip, #1224	@ tmp223,
	ldrd	r8, [r6, r0]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.Pts, temp.4207, tmp221
	movw	r1, #:lower16:.LC221	@,
	ldrd	r2, [r6, ip]	@, temp.4207, tmp223
	movt	r1, #:upper16:.LC221	@,
	mov	r0, #29	@,
	strd	r2, [sp]	@,
	mov	r2, r8	@, <variable>.stSynExtraData.stSegPacket.CurrSeg.Pts
	mov	r3, r9	@, <variable>.stSynExtraData.stSegPacket.CurrSeg.Pts
	bl	dprint_vfmw	@
	ldr	r0, [r5, r4, asl #2]	@ prephitmp.4188, s_pstVfmwChan
	ldr	r1, [r0, #48]	@ D.42476, <variable>.stChanCfg.eVidStd
	cmp	r1, #1	@ D.42476,
	beq	.L1250	@,
	sub	ip, r1, #2	@ tmp235, D.42476,
	cmp	r1, #6	@ D.42476,
	cmpne	ip, #1	@, tmp235,
	bls	.L1224	@,
.L1223:
	movw	r3, #1208	@ tmp337,
	mvn	r8, #0	@,
	ldrd	r2, [r3, r6]	@ temp.4210, tmp337, temp.4207
	mvn	r9, #0	@,
	cmp	r3, r9	@ temp.4210,
	cmpeq	r2, r8	@ temp.4210,
	movwne	r1, #1096	@ tmp339,
	strned	r2, [r0, r1]	@ temp.4210, prephitmp.4188, tmp339
	ldrne	r0, [r5, r4, asl #2]	@ prephitmp.4188, s_pstVfmwChan
.L1232:
	movw	r1, #1224	@ tmp342,
	movw	r3, #1112	@ tmp341,
	ldrd	r8, [r6, r1]	@, temp.4207, tmp342
	movw	r2, #1128	@ tmp346,
	ldr	lr, [r6, #1240]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag, <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag
	movw	r1, #:lower16:.LC224	@,
	movt	r1, #:upper16:.LC224	@,
	strd	r8, [r0, r3]	@, prephitmp.4188, tmp341
	mov	r0, #1232	@ tmp347,
	ldr	ip, [r5, r4, asl #2]	@ tmp345, s_pstVfmwChan
	ldrd	r8, [r6, r0]	@, temp.4207, tmp347
	mov	r0, #29	@,
	strd	r8, [ip, r2]	@, tmp345, tmp346
	ldr	ip, [r5, r4, asl #2]	@ tmp350, s_pstVfmwChan
	ldr	r9, [r6, #1244]	@, <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance
	ldr	r2, [r6, #1252]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum, <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum
	str	lr, [ip, #1144]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag, <variable>.stSynExtraData.DispEnableFlag
	ldr	ip, [r5, r4, asl #2]	@ tmp353, s_pstVfmwChan
	ldr	lr, [r6, #1248]	@, <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame
	str	r9, [ip, #1148]	@, <variable>.stSynExtraData.DispFrameDistance
	ldr	ip, [r5, r4, asl #2]	@ tmp356, s_pstVfmwChan
	str	lr, [ip, #1152]	@, <variable>.stSynExtraData.DistanceBeforeFirstFrame
	movw	ip, #1096	@ tmp363,
	ldr	r9, [r5, r4, asl #2]	@ tmp359, s_pstVfmwChan
	str	r2, [r9, #1168]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum, <variable>.stSynExtraData.GopNum
	ldr	lr, [r5, r4, asl #2]	@ temp.4217, s_pstVfmwChan
	add	r2, lr, ip	@, temp.4217, tmp363
	ldrd	r8, [lr, r3]	@, temp.4217, tmp341
	ldrd	r2, [r2]	@ <variable>.stSynExtraData.pts,
	strd	r8, [sp]	@,
	bl	dprint_vfmw	@
.L1231:
	mov	r0, #3	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	beq	.L1233	@,
	cmp	sl, #1	@ rec_pos_print_flag,
	beq	.L1251	@,
.L1233:
	ldr	lr, [r5, r4, asl #2]	@ temp.4259, s_pstVfmwChan
	add	r0, r6, #1168	@, temp.4207,
	add	r0, r0, #8	@,,
	movw	r6, #:lower16:.LANCHOR0	@ tmp371,
	add	ip, lr, #250880	@, temp.4259,
	movt	r6, #:upper16:.LANCHOR0	@ tmp371,
	add	r2, ip, #616	@,,
	ldr	r1, [lr, #1032]	@, <variable>.eVidStd
	bl	DecodeStream	@
	ldr	r0, [r5, r4, asl #2]	@ temp.4261, s_pstVfmwChan
	ldr	r2, [r0, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, #16	@ <variable>.eVidStd,
	beq	.L1252	@,
.L1234:
	mov	r0, #4	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	bne	.L1253	@,
.L1236:
	mov	r0, #0	@ D.42403,
	b	.L1205	@
.L1250:
	movw	r3, #:lower16:251496	@ tmp227,
	movt	r3, #:upper16:251496	@ tmp227,
	ldr	lr, [r0, r3]	@ <variable>.stSynCtx.unSyntax.stVc1Ctx.pstExtraData, <variable>.stSynCtx.unSyntax.stVc1Ctx.pstExtraData
	ldrb	r2, [lr, #556]	@ zero_extendqisi2	@ <variable>.StdExt.Vc1Ext.IsAdvProfile, <variable>.StdExt.Vc1Ext.IsAdvProfile
	cmp	r2, #1	@ <variable>.StdExt.Vc1Ext.IsAdvProfile,
	bne	.L1223	@,
.L1224:
	add	r0, r0, #1584	@, prephitmp.4188,
	add	r2, r6, #1184	@, temp.4207,
	add	r0, r0, #8	@,,
	bl	IsNewpicSeg	@
	cmp	r0, #0	@,
	beq	.L1254	@,
.L1225:
	ldr	r3, [r5, r4, asl #2]	@ temp.4208, s_pstVfmwChan
	ldr	r1, [r3, #48]	@ <variable>.stChanCfg.eVidStd, <variable>.stChanCfg.eVidStd
	cmp	r1, #3	@ <variable>.stChanCfg.eVidStd,
	beq	.L1229	@,
.L1228:
	movw	r9, #1208	@ tmp308,
	mvn	r8, #0	@,
	ldrd	r0, [r6, r9]	@ temp.4245, temp.4207, tmp308
	mvn	r9, #0	@,
	cmp	r1, r9	@ temp.4245,
	cmpeq	r0, r8	@ temp.4245,
	movne	ip, #1104	@ tmp310,
	strned	r0, [r3, ip]	@ temp.4245, temp.4208, tmp310
.L1230:
	movw	r8, #1224	@ tmp314,
	ldr	ip, [r5, r4, asl #2]	@ tmp312, s_pstVfmwChan
	ldrd	r0, [r6, r8]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.Usertag, temp.4207, tmp314
	mov	r2, #1232	@ tmp319,
	mov	r3, #1120	@ tmp313,
	ldrd	r8, [r6, r2]	@, temp.4207, tmp319
	mov	lr, #1136	@ tmp318,
	strd	r0, [ip, r3]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.Usertag, tmp312, tmp313
	ldr	r2, [r5, r4, asl #2]	@ tmp317, s_pstVfmwChan
	ldr	ip, [r6, #1240]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag, <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag
	ldr	r0, [r6, #1244]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance, <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance
	strd	r8, [r2, lr]	@, tmp317, tmp318
	ldr	r3, [r5, r4, asl #2]	@ tmp322, s_pstVfmwChan
	ldr	lr, [r6, #1248]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame, <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame
	ldr	r2, [r6, #1252]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum, <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum
	str	ip, [r3, #1156]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag, <variable>.stSynExtraData.NextDispEnableFlag
	ldr	ip, [r5, r4, asl #2]	@ tmp325, s_pstVfmwChan
	str	r0, [ip, #1160]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance, <variable>.stSynExtraData.NextDispFrameDistance
	ldr	r0, [r5, r4, asl #2]	@ tmp328, s_pstVfmwChan
	str	lr, [r0, #1164]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame, <variable>.stSynExtraData.NextDistanceBeforeFirstFrame
	ldr	r3, [r5, r4, asl #2]	@ tmp331, s_pstVfmwChan
	str	r2, [r3, #1172]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum, <variable>.stSynExtraData.NextGopNum
	ldr	r3, [r5, r4, asl #2]	@ temp.4208, s_pstVfmwChan
.L1229:
	movw	r0, #1112	@ tmp335,
	add	r2, r3, r0	@, temp.4208, tmp335
	movw	r1, #:lower16:.LC223	@,
	mov	r0, #29	@,
	ldrd	r2, [r2]	@,
	movt	r1, #:upper16:.LC223	@,
	bl	dprint_vfmw	@
	b	.L1231	@
.L1253:
	bl	OSAL_GetTimeInMs	@
	ldr	r9, [fp, #-88]	@, %sfp
	movw	r2, #:lower16:g_TraceFramePeriod	@ tmp394,
	movt	r2, #:upper16:g_TraceFramePeriod	@ tmp394,
	add	r7, r9, r7	@ tmp390,, tmp412
	ldr	r1, [r7, #-1876]	@ tmp393, last_rec_pos_decparam_time
	mov	r3, r0	@ currtime.4266,
	ldr	r0, [r2, #0]	@ g_TraceFramePeriod, g_TraceFramePeriod
	rsb	ip, r1, r3	@ tmp392, tmp393, currtime.4266
	cmp	ip, r0	@ tmp392, g_TraceFramePeriod
	bls	.L1236	@,
	mov	r0, r4	@, ChanID
	str	r3, [r7, #-1876]	@ currtime.4266, last_rec_pos_decparam_time
	bl	VCTRL_GetDecParam	@
	cmp	r0, #0	@,
	beq	.L1236	@,
	mov	r3, r4, asl #24	@ tmp403, ChanID,
	ldr	r0, .L1258	@,
	add	r2, r3, #262144	@, tmp403,
	movw	r1, #7182	@,
	bl	DBG_AddTrace	@
	mov	r0, #0	@ D.42403,
	b	.L1205	@
.L1254:
	ldr	r3, [r5, r4, asl #2]	@ prephitmp.4184, s_pstVfmwChan
	movw	r2, #:lower16:.LANCHOR0	@ tmp246,
	movt	r2, #:upper16:.LANCHOR0	@ tmp246,
	ldr	r8, [r3, #48]	@ <variable>.stChanCfg.eVidStd, <variable>.stChanCfg.eVidStd
	cmp	r8, #3	@ <variable>.stChanCfg.eVidStd,
	beq	.L1255	@,
	mov	r1, #1104	@ tmp252,
	mvn	r8, #0	@,
	ldrd	r0, [r1, r3]	@ temp.4221, tmp252, prephitmp.4184
	mvn	r9, #0	@,
	cmp	r1, r9	@ temp.4221,
	cmpeq	r0, r8	@ temp.4221,
	movwne	r9, #1096	@ tmp254,
	strned	r0, [r3, r9]	@ temp.4221, prephitmp.4184, tmp254
	ldrne	r3, [r2, r4, asl #2]	@ prephitmp.4184, s_pstVfmwChan
.L1227:
	mov	r9, #1104	@,
	mvn	r0, #0	@ tmp257,
	mvn	r1, #0	@,
	strd	r0, [r3, r9]	@ tmp257, prephitmp.4184,
	ldr	lr, [r5, r4, asl #2]	@ temp.4222, s_pstVfmwChan
	mov	ip, #1120	@ tmp260,
	movw	r8, #1112	@ tmp259,
	mov	r0, #29	@,
	movw	r1, #:lower16:.LC222	@,
	movt	r1, #:upper16:.LC222	@,
	ldrd	r2, [lr, ip]	@, temp.4222, tmp260
	movw	r9, #:lower16:.LANCHOR0	@ tmp258,
	movt	r9, #:upper16:.LANCHOR0	@ tmp258,
	strd	r2, [lr, r8]	@, temp.4222, tmp259
	mov	r3, #1136	@,
	ldr	lr, [r5, r4, asl #2]	@ temp.4223, s_pstVfmwChan
	movw	r8, #1128	@ tmp263,
	ldrd	r2, [r3, lr]	@,, temp.4223
	strd	r2, [lr, r8]	@, temp.4223, tmp263
	ldr	r3, [r5, r4, asl #2]	@ temp.4224, s_pstVfmwChan
	ldr	r8, [r3, #1156]	@ <variable>.stSynExtraData.NextDispEnableFlag, <variable>.stSynExtraData.NextDispEnableFlag
	str	r8, [r3, #1144]	@ <variable>.stSynExtraData.NextDispEnableFlag, <variable>.stSynExtraData.DispEnableFlag
	ldr	r2, [r5, r4, asl #2]	@ temp.4225, s_pstVfmwChan
	ldr	lr, [r2, #1160]	@ <variable>.stSynExtraData.NextDispFrameDistance, <variable>.stSynExtraData.NextDispFrameDistance
	str	lr, [r2, #1148]	@ <variable>.stSynExtraData.NextDispFrameDistance, <variable>.stSynExtraData.DispFrameDistance
	ldr	r3, [r5, r4, asl #2]	@ temp.4226, s_pstVfmwChan
	ldr	r8, [r3, #1164]	@ <variable>.stSynExtraData.NextDistanceBeforeFirstFrame, <variable>.stSynExtraData.NextDistanceBeforeFirstFrame
	str	r8, [r3, #1152]	@ <variable>.stSynExtraData.NextDistanceBeforeFirstFrame, <variable>.stSynExtraData.DistanceBeforeFirstFrame
	movw	r3, #1096	@ tmp277,
	ldr	r2, [r5, r4, asl #2]	@ temp.4227, s_pstVfmwChan
	ldr	lr, [r2, #1172]	@ <variable>.stSynExtraData.NextGopNum, <variable>.stSynExtraData.NextGopNum
	str	lr, [r2, #1168]	@ <variable>.stSynExtraData.NextGopNum, <variable>.stSynExtraData.GopNum
	ldr	r8, [r5, r4, asl #2]	@ tmp276, s_pstVfmwChan
	add	r2, r8, r3	@, tmp276, tmp277
	ldrd	r2, [r2]	@,
	str	ip, [fp, #-80]	@,
	bl	dprint_vfmw	@
	ldr	r3, [r5, r4, asl #2]	@ temp.4208, s_pstVfmwChan
	ldr	ip, [fp, #-80]	@,
	ldr	r2, [r3, #48]	@ <variable>.stChanCfg.eVidStd, <variable>.stChanCfg.eVidStd
	cmp	r2, #3	@ <variable>.stChanCfg.eVidStd,
	bne	.L1228	@,
	movw	r8, #1208	@ tmp282,
	movw	lr, #1224	@ tmp287,
	ldrd	r0, [r6, r8]	@, temp.4207, tmp282
	mov	r2, #1232	@ tmp292,
	mov	r8, #1104	@,
	strd	r0, [fp, #-76]	@,,
	ldrd	r0, [r6, lr]	@, temp.4207, tmp287
	strd	r0, [fp, #-52]	@,,
	ldrd	r0, [r6, r2]	@, temp.4207, tmp292
	strd	r0, [fp, #-60]	@,,
	ldrd	r0, [fp, #-76]	@,,
	ldr	lr, [r6, #1244]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance, <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance
	strd	r0, [r3, r8]	@, temp.4208,
	ldrd	r0, [fp, #-52]	@,,
	ldr	r3, [r9, r4, asl #2]	@ tmp285, s_pstVfmwChan
	ldr	r8, [r6, #1240]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag, <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag
	strd	r0, [r3, ip]	@, tmp285, tmp260
	mov	ip, #1136	@,
	ldr	r0, [r9, r4, asl #2]	@ tmp290, s_pstVfmwChan
	ldrd	r2, [fp, #-60]	@,,
	ldr	r1, [r6, #1248]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame, <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame
	strd	r2, [r0, ip]	@, tmp290,
	ldr	r0, [r9, r4, asl #2]	@ tmp295, s_pstVfmwChan
	str	r8, [r0, #1156]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispEnableFlag, <variable>.stSynExtraData.NextDispEnableFlag
	ldr	r2, [r9, r4, asl #2]	@ tmp298, s_pstVfmwChan
	str	lr, [r2, #1160]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DispFrameDistance, <variable>.stSynExtraData.NextDispFrameDistance
	ldr	ip, [r9, r4, asl #2]	@ tmp301, s_pstVfmwChan
	str	r1, [ip, #1164]	@ <variable>.stSynExtraData.stSegPacket.CurrSeg.DistanceBeforeFirstFrame, <variable>.stSynExtraData.NextDistanceBeforeFirstFrame
	ldr	r1, [r6, #1252]	@, <variable>.stSynExtraData.stSegPacket.CurrSeg.GopNum
	ldr	r0, [r9, r4, asl #2]	@ tmp304, s_pstVfmwChan
	str	r1, [r0, #1172]	@, <variable>.stSynExtraData.NextGopNum
	b	.L1225	@
.L1249:
	mov	r0, r4	@, ChanID
	add	r1, r6, #1184	@, temp.4207,
	bl	SM_ReadStreamSeg	@
	cmp	r0, #0	@,
	beq	.L1220	@,
	cmp	sl, #1	@ rec_pos_print_flag,
	beq	.L1256	@,
.L1221:
	ldr	r3, [r5, r4, asl #2]	@ tmp218, s_pstVfmwChan
	mov	lr, #1	@ tmp219,
	mvn	r0, #3	@ D.42403,
	str	lr, [r3, #816]	@ tmp219, <variable>.s32NoStreamFlag
	b	.L1205	@
.L1248:
	movw	ip, #:lower16:249192	@ tmp205,
	movt	ip, #:upper16:249192	@ tmp205,
	ldr	r3, [r6, ip]	@ prephitmp.4190, <variable>.FspInst.eFspPartitionState
	cmp	r3, #0	@ prephitmp.4190,
	cmpne	r3, #2	@, prephitmp.4190,
	beq	.L1217	@,
	cmp	r3, #1	@ prephitmp.4190,
	bne	.L1237	@,
	movw	r1, #:lower16:.LC225	@,
	mov	r0, #31	@,
	movt	r1, #:upper16:.LC225	@,
	bl	dprint_vfmw	@
.L1241:
	mvn	r0, #2	@ D.42403,
	b	.L1205	@
.L1247:
	cmp	sl, #1	@ rec_pos_print_flag,
	bne	.L1241	@,
	mov	r2, r4	@, ChanID
	mov	r0, #23	@,
	movw	r1, #:lower16:.LC219	@,
	movt	r1, #:upper16:.LC219	@,
	bl	dprint_vfmw	@
	mvn	r0, #2	@ D.42403,
	b	.L1205	@
.L1252:
	add	r1, r0, #250880	@, temp.4261,
	add	r0, r1, #616	@,,
	bl	IsMain10Profile	@
	cmp	r0, #0	@ D.42543
	ldreq	lr, [r6, r4, asl #2]	@ tmp385, s_pstVfmwChan
	streq	r0, [lr, #1940]	@ D.42543, <variable>.stSynExtraData.s32IsHevcMain10
	beq	.L1234	@
.L1257:
	ldr	r3, [r6, r4, asl #2]	@ tmp382, s_pstVfmwChan
	mov	r2, #1	@ tmp383,
	str	r2, [r3, #1940]	@ tmp383, <variable>.stSynExtraData.s32IsHevcMain10
	bl	VDMDRV_AddMatchMode	@
	b	.L1234	@
.L1214:
	mov	r2, r4	@, ChanID
	mov	r0, #23	@,
	movw	r1, #:lower16:.LC218	@,
	movt	r1, #:upper16:.LC218	@,
	bl	dprint_vfmw	@
	mvn	r0, #1	@ D.42403,
	b	.L1205	@
.L1244:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #6963	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC216	@,
	movt	r3, #:upper16:.LC216	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.42403,
	b	.L1205	@
.L1245:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #6964	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC217	@,
	movt	r3, #:upper16:.LC217	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.42403,
	b	.L1205	@
.L1255:
	mov	lr, #1104	@ tmp249,
	movw	r1, #1096	@ tmp248,
	ldrd	r8, [r3, lr]	@, prephitmp.4184, tmp249
	strd	r8, [r3, r1]	@, prephitmp.4184, tmp248
	ldr	r3, [r2, r4, asl #2]	@ prephitmp.4184, s_pstVfmwChan
	b	.L1227	@
.L1251:
	mov	r3, r4, asl #24	@ tmp369, ChanID,
	ldr	r0, .L1258	@,
	add	r2, r3, #196608	@, tmp369,
	movw	r1, #7151	@,
	bl	DBG_AddTrace	@
	b	.L1233	@
.L1242:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #6961	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.42403,
	b	.L1205	@
.L1256:
	movw	r1, #:lower16:.LC220	@,
	mov	r2, r4	@, ChanID
	movt	r1, #:upper16:.LC220	@,
	mov	r0, #23	@,
	bl	dprint_vfmw	@
	b	.L1221	@
.L1243:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #6962	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC215	@,
	movt	r3, #:upper16:.LC215	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.42403,
	b	.L1205	@
.L1259:
	.align	2
.L1258:
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
	movw	r4, #:lower16:.LANCHOR3	@ tmp303,
	movt	r4, #:upper16:.LANCHOR3	@ tmp303,
	ldr	r9, [r6, #0]	@ temp.4316, s_pstVfmwChan
	ldr	r8, [r6, #4]	@ temp.4318, s_pstVfmwChan
	cmp	r9, #0	@ temp.4316,
	ldr	r7, [r6, #8]	@ D.42297, s_pstVfmwChan
	ldr	r2, [r6, #12]	@ temp.4320, s_pstVfmwChan
	ldrne	r9, [r9, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r8, #0	@ temp.4318,
	ldr	r1, [r6, #16]	@ temp.4322, s_pstVfmwChan
	ldr	r0, [r6, #20]	@ temp.4324, s_pstVfmwChan
	str	r9, [r4, #-1812]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r8, [r8, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r7, #0	@ D.42297,
	ldr	r3, [r6, #24]	@ temp.4326, s_pstVfmwChan
	ldr	ip, [r6, #28]	@ temp.4328, s_pstVfmwChan
	str	r8, [r4, #-1808]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r7, [r7, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r2, #0	@ temp.4320,
	ldr	sl, [r6, #32]	@ temp.4330, s_pstVfmwChan
	ldr	r9, [r6, #36]	@ temp.4332, s_pstVfmwChan
	str	r7, [r4, #-1804]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r2, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ temp.4322,
	ldr	r8, [r6, #40]	@ temp.4334, s_pstVfmwChan
	ldr	r7, [r6, #44]	@ temp.4336, s_pstVfmwChan
	str	r2, [r4, #-1800]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r0, #0	@ temp.4324,
	str	r1, [r4, #-1796]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r0, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r3, #0	@ temp.4326,
	str	r0, [r4, #-1792]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r3, [r3, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	ip, #0	@ temp.4328,
	str	r3, [r4, #-1788]	@ <variable>.s32Priority, ChanPriTab
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	sl, #0	@ temp.4330,
	str	ip, [r4, #-1784]	@ <variable>.s32Priority, ChanPriTab
	ldrne	sl, [sl, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r9, #0	@ temp.4332,
	str	sl, [r4, #-1780]	@ <variable>.s32Priority, ChanPriTab
	movw	sl, #:lower16:.LANCHOR0	@ tmp311,
	ldrne	r9, [r9, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r8, #0	@ temp.4334,
	movt	sl, #:upper16:.LANCHOR0	@ tmp311,
	str	r9, [r4, #-1776]	@ <variable>.s32Priority, ChanPriTab
	sub	r9, fp, #68	@ tmp312,,
	ldrne	r8, [r8, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r7, #0	@ temp.4336,
	str	r8, [r4, #-1772]	@ <variable>.s32Priority, ChanPriTab
	mvn	r8, #0	@ ret,
	ldrne	r7, [r7, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	str	r7, [r4, #-1768]	@ <variable>.s32Priority, ChanPriTab
	mov	r7, #0	@ MaxPriChan.4345,
	ldr	r2, [r6, #48]	@ temp.4338, s_pstVfmwChan
	ldr	r1, [r6, #52]	@ temp.4340, s_pstVfmwChan
	cmp	r2, #0	@ temp.4338,
	ldr	r0, [r6, #56]	@ temp.4342, s_pstVfmwChan
	ldr	r3, [r6, #60]	@ temp.4306, s_pstVfmwChan
	ldrne	r2, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r1, #0	@ temp.4340,
	str	r2, [r4, #-1764]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r0, #0	@ temp.4342,
	str	r1, [r4, #-1760]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r0, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r3, #0	@ temp.4306,
	str	r0, [r4, #-1756]	@ <variable>.s32Priority, ChanPriTab
	ldrne	r3, [r3, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	str	r3, [r4, #-1752]	@ temp.4306, ChanPriTab
.L1321:
	ldr	r3, [r4, #-1812]	@ MaxPri, ChanPriTab
	ldr	r2, [r4, #-1808]	@ MaxPri.4344, ChanPriTab
	ldr	r1, [r4, #-1804]	@ MaxPri.4346, ChanPriTab
	cmp	r3, r2	@ MaxPri, MaxPri.4344
	ldr	r0, [r4, #-1800]	@ MaxPri.4347, ChanPriTab
	ldr	ip, [r4, #-1796]	@ MaxPri.4348, ChanPriTab
	movlt	r3, r2	@ MaxPri, MaxPri.4344
	movlt	r5, #1	@ MaxPriChan.4345,
	movge	r5, #0	@ MaxPriChan.4345,
	cmp	r3, r1	@ MaxPri, MaxPri.4346
	ldr	r2, [r4, #-1792]	@ MaxPri.4349, ChanPriTab
	movlt	r3, r1	@ MaxPri, MaxPri.4346
	movlt	r5, #2	@ MaxPriChan.4345,
	cmp	r3, r0	@ MaxPri, MaxPri.4347
	ldr	r1, [r4, #-1788]	@ MaxPri.4350, ChanPriTab
	movlt	r3, r0	@ MaxPri, MaxPri.4347
	movlt	r5, #3	@ MaxPriChan.4345,
	cmp	r3, ip	@ MaxPri, MaxPri.4348
	ldr	r0, [r4, #-1784]	@ MaxPri.4351, ChanPriTab
	movlt	r3, ip	@ MaxPri, MaxPri.4348
	movlt	r5, #4	@ MaxPriChan.4345,
	cmp	r3, r2	@ MaxPri, MaxPri.4349
	ldr	ip, [r4, #-1780]	@ MaxPri.4352, ChanPriTab
	movlt	r3, r2	@ MaxPri, MaxPri.4349
	movlt	r5, #5	@ MaxPriChan.4345,
	cmp	r3, r1	@ MaxPri, MaxPri.4350
	ldr	r2, [r4, #-1776]	@ MaxPri.4353, ChanPriTab
	movlt	r3, r1	@ MaxPri, MaxPri.4350
	movlt	r5, #6	@ MaxPriChan.4345,
	cmp	r3, r0	@ MaxPri, MaxPri.4351
	ldr	r1, [r4, #-1772]	@ MaxPri.4354, ChanPriTab
	movlt	r3, r0	@ MaxPri, MaxPri.4351
	movlt	r5, #7	@ MaxPriChan.4345,
	cmp	r3, ip	@ MaxPri, MaxPri.4352
	ldr	r0, [r4, #-1768]	@ MaxPri.4355, ChanPriTab
	movlt	r3, ip	@ MaxPri, MaxPri.4352
	movlt	r5, #8	@ MaxPriChan.4345,
	cmp	r3, r2	@ MaxPri, MaxPri.4353
	ldr	ip, [r4, #-1764]	@ MaxPri.4356, ChanPriTab
	movlt	r3, r2	@ MaxPri, MaxPri.4353
	movlt	r5, #9	@ MaxPriChan.4345,
	cmp	r3, r1	@ MaxPri, MaxPri.4354
	ldr	r2, [r4, #-1760]	@ MaxPri.4357, ChanPriTab
	movlt	r3, r1	@ MaxPri, MaxPri.4354
	movlt	r5, #10	@ MaxPriChan.4345,
	cmp	r3, r0	@ MaxPri, MaxPri.4355
	ldr	r1, [r4, #-1756]	@ MaxPri.4358, ChanPriTab
	movlt	r3, r0	@ MaxPri, MaxPri.4355
	movlt	r5, #11	@ MaxPriChan.4345,
	cmp	r3, ip	@ MaxPri, MaxPri.4356
	ldr	r0, [r4, #-1752]	@ MaxPri.4359, ChanPriTab
	movlt	r3, ip	@ MaxPri, MaxPri.4356
	movlt	r5, #12	@ MaxPriChan.4345,
	cmp	r3, r2	@ MaxPri, MaxPri.4357
	movlt	r3, r2	@ MaxPri, MaxPri.4357
	movlt	r5, #13	@ MaxPriChan.4345,
	cmp	r3, r1	@ MaxPri, MaxPri.4358
	movlt	r5, #14	@ MaxPriChan.4345,
	movlt	r3, r1	@ MaxPri, MaxPri.4358
	cmp	r3, r0	@ MaxPri, MaxPri.4359
	movlt	r5, #15	@ MaxPriChan.4345,
	movlt	r3, r0	@ MaxPri, MaxPri.4359
	add	ip, r4, r5, asl #2	@, tmp278, tmp303, MaxPriChan.4345,
	cmp	r3, #0	@ MaxPri,
	add	r2, r5, #1	@ s_VfmwCTrl__s32ThisChanIDPlus1s_VfmwCTrl.4297, MaxPriChan.4345,
	str	r7, [ip, #-1812]	@ MaxPriChan.4345, ChanPriTab
	ble	.L1309	@,
	ldr	r3, [r6, r5, asl #2]	@ D.42308, s_pstVfmwChan
	cmp	r3, #0	@ D.42308,
	beq	.L1321	@,
	str	r2, [sl, #156]	@ s_VfmwCTrl__s32ThisChanIDPlus1s_VfmwCTrl.4297, s_VfmwCTrl.s32ThisChanIDPlus1
	ldr	ip, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	ip, #1	@ <variable>.s32IsRun,
	bne	.L1321	@,
	ldr	lr, [r3, #68]	@ <variable>.stChanCfg.s32ChanStrmOFThr, <variable>.stChanCfg.s32ChanStrmOFThr
	cmp	lr, #0	@ <variable>.stChanCfg.s32ChanStrmOFThr,
	ble	.L1311	@,
	ldr	r8, [r3, #72]	@ <variable>.stChanCfg.s32DecMode, <variable>.stChanCfg.s32DecMode
	cmp	r8, #0	@ <variable>.stChanCfg.s32DecMode,
	beq	.L1337	@,
.L1311:
	mov	r3, #0	@ i,
.L1316:
	mov	r0, r5	@, MaxPriChan.4345
	str	r3, [fp, #-72]	@,
	bl	DecChanSyntax	@
	ldr	r3, [fp, #-72]	@,
	cmn	r0, #1	@ ret,
	mov	r8, r0	@ ret,
	beq	.L1338	@,
	cmp	r0, #0	@ ret,
	bne	.L1321	@,
	add	r3, r3, #1	@ i, i,
	cmp	r3, #200	@ i,
	beq	.L1321	@,
	b	.L1316	@
.L1309:
	str	r7, [r6, #156]	@ MaxPriChan.4345, s_VfmwCTrl.s32ThisChanIDPlus1
.L1315:
	mov	r0, r8	@, ret
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1337:
	mov	r0, r5	@, MaxPriChan.4345
	mov	r1, r9	@, tmp312
	bl	SM_GetInfo	@
	cmp	r0, #0	@,
	beq	.L1312	@,
	mov	r0, r9	@, tmp312
	mov	r1, #24	@,
	bl	__memzero	@
.L1312:
	ldr	r8, [r6, r5, asl #2]	@ temp.4307, s_pstVfmwChan
	ldr	r1, [fp, #-56]	@, stScdInstInfo.TotalRawSize
	ldr	r0, [r8, #1048]	@, <variable>.stSynExtraData.s32DecMode
	ldr	r2, [r8, #68]	@, <variable>.stChanCfg.s32ChanStrmOFThr
	bl	GetNextDecodeMode	@
	str	r0, [r8, #1048]	@, <variable>.stSynExtraData.s32DecMode
	ldr	r3, [r6, r5, asl #2]	@ temp.4309, s_pstVfmwChan
	ldr	r0, [r3, #1048]	@ <variable>.stSynExtraData.s32DecMode, <variable>.stSynExtraData.s32DecMode
	cmp	r0, #0	@ <variable>.stSynExtraData.s32DecMode,
	strne	r7, [r3, #1044]	@ MaxPriChan.4345, <variable>.stSynExtraData.s32OutErrThr
	ldreq	r0, [r3, #64]	@ <variable>.stChanCfg.s32ChanErrThr, <variable>.stChanCfg.s32ChanErrThr
	ldrne	r3, [sl, r5, asl #2]	@ tmp293, s_pstVfmwChan
	streq	r0, [r3, #1044]	@ <variable>.stChanCfg.s32ChanErrThr, <variable>.stSynExtraData.s32OutErrThr
	ldreq	r3, [sl, r5, asl #2]	@ temp.4312, s_pstVfmwChan
	strne	r7, [r3, #1040]	@ MaxPriChan.4345, <variable>.stSynExtraData.s32RefErrThr
	ldreq	r0, [r3, #64]	@ <variable>.stChanCfg.s32ChanErrThr, <variable>.stChanCfg.s32ChanErrThr
	streq	r0, [r3, #1040]	@ <variable>.stChanCfg.s32ChanErrThr, <variable>.stSynExtraData.s32RefErrThr
	b	.L1311	@
.L1338:
	ldr	ip, [r6, #64]	@ g_event_report.660, g_event_report
	cmp	ip, #0	@ g_event_report.660,
	beq	.L1315	@,
	mov	r2, #0	@,
	mov	r0, r5	@, MaxPriChan.4345
	mov	r1, #102	@,
	mov	r3, r2	@,
	blx	ip	@ g_event_report.660
	b	.L1315	@
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
	beq	.L1342	@,
	sub	r1, fp, #44	@,,
	bl	SM_GetInfo	@
	cmp	r0, #0	@,
	bne	.L1342	@,
	ldr	r0, [fp, #-36]	@ SmInstInfo.SegNum, SmInstInfo.SegNum
	cmp	r0, #16	@ SmInstInfo.SegNum,
	bgt	.L1343	@,
	ldr	r1, [fp, #-28]	@ SmInstInfo.TotalSegSize, SmInstInfo.TotalSegSize
	cmp	r1, #524288	@ SmInstInfo.TotalSegSize,
	bgt	.L1343	@,
.L1342:
	mvn	r0, #0	@ ret,
.L1341:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1343:
	mov	r0, r5	@, ChanID
	bl	VCTRL_GetImageBuffer	@
	cmp	r0, #1	@,
	bne	.L1342	@,
	bl	OSAL_GetTimeInMs	@
	ldr	r3, [r4, r5, asl #2]	@ tmp146, s_pstVfmwChan
	ldr	ip, [r3, #44]	@ <variable>.u32timeLastDecParamReady, <variable>.u32timeLastDecParamReady
	rsb	r2, ip, r0	@ tmp147, <variable>.u32timeLastDecParamReady,
	cmp	r2, #50	@ tmp147,
	movls	r0, #0	@ ret,
	bls	.L1341	@,
	b	.L1342	@
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
	ldr	r0, [r4, r0, asl #2]	@ D.41232, s_pstVfmwChan
	cmp	r0, #0	@ D.41232,
	beq	.L1365	@,
	movw	r1, #:lower16:251488	@ tmp143,
	movt	r1, #:upper16:251488	@ tmp143,
	ldr	r3, [r0, r1]	@ <variable>.stSynCtx.eVidStd, <variable>.stSynCtx.eVidStd
	cmp	r3, #16	@ <variable>.stSynCtx.eVidStd,
	ldrls	pc, [pc, r3, asl #2]	@ <variable>.stSynCtx.eVidStd
	b	.L1349	@
.L1362:
	.word	.L1350
	.word	.L1351
	.word	.L1352
	.word	.L1353
	.word	.L1349
	.word	.L1354
	.word	.L1355
	.word	.L1349
	.word	.L1356
	.word	.L1357
	.word	.L1358
	.word	.L1358
	.word	.L1358
	.word	.L1359
	.word	.L1349
	.word	.L1360
	.word	.L1361
.L1350:
	add	lr, r0, #250880	@, D.41232,
	add	r0, lr, #616	@,,
	bl	H264_FlushDecoder	@
	bl	VDMDRV_WakeUpVdm	@
	bl	VDMDRV_WakeUpVdm	@
	ldr	r3, [r4, r5, asl #2]	@ tmp154, s_pstVfmwChan
	add	ip, r3, #250880	@, tmp154,
	add	r0, ip, #616	@,,
	bl	FlushDPB	@
	cmp	r0, #0	@,
	bne	.L1366	@,
.L1349:
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1351:
	add	r2, r0, #250880	@, D.41232,
	add	r0, r2, #616	@,,
	bl	VC1DEC_GetRemainImg	@
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1352:
	add	r2, r0, #250880	@, D.41232,
	add	r0, r2, #616	@,,
	bl	MPEG4DEC_GetRemainImg	@
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1353:
	add	r0, r0, #250880	@, D.41232,
	add	r0, r0, #616	@,,
	bl	MPEG2DEC_GetRemainImg	@
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1354:
	add	r1, r0, #250880	@, D.41232,
	add	r0, r1, #616	@,,
	bl	DIVX3DEC_GetRemainImg	@
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1355:
	add	r3, r0, #250880	@, D.41232,
	add	r0, r3, #616	@,,
	bl	AVSDEC_GetRemainImg	@
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1356:
	add	lr, r0, #250880	@, D.41232,
	add	r0, lr, #616	@,,
	bl	REAL8DEC_GetRemainImg	@
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1357:
	add	r0, r0, #250880	@, D.41232,
	add	r0, r0, #616	@,,
	bl	REAL9DEC_GetRemainImg	@
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1358:
	add	ip, r0, #250880	@, D.41232,
	add	r0, ip, #616	@,,
	bl	VP6DEC_GetRemainImg	@
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1359:
	add	r3, r0, #250880	@, D.41232,
	add	r0, r3, #616	@,,
	bl	VP8DEC_GetRemainImg	@
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1360:
	add	ip, r0, #250880	@, D.41232,
	add	r0, ip, #616	@,,
	bl	MVC_FlushDecoder	@
	bl	VDMDRV_WakeUpVdm	@
	bl	VDMDRV_WakeUpVdm	@
	ldr	r2, [r4, r5, asl #2]	@ tmp165, s_pstVfmwChan
	mvn	r1, #0	@,
	add	r0, r2, #250880	@, tmp165,
	add	r0, r0, #616	@,,
	bl	MVC_FlushDPB	@
	cmp	r0, #0	@,
	beq	.L1349	@,
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC229	@,
	ldr	r2, .L1368	@,
	movt	r1, #:upper16:.LC229	@,
	mov	r3, #4800	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1361:
	add	r1, r0, #250880	@, D.41232,
	add	r0, r1, #616	@,,
	bl	HEVC_FlushOutputFrmFromDPB	@
	cmp	r0, #0	@,
	bne	.L1367	@,
.L1363:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC228	@,
	movt	r1, #:upper16:.LC228	@,
	bl	dprint_vfmw	@
	bl	VDMDRV_WakeUpVdm	@
	bl	VDMDRV_WakeUpVdm	@
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1367:
	movw	r1, #:lower16:.LC227	@,
	movw	r2, #4786	@,
	movt	r1, #:upper16:.LC227	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	b	.L1363	@
.L1366:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC227	@,
	movw	r2, #4778	@,
	movt	r1, #:upper16:.LC227	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1365:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4757	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.41236,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1369:
	.align	2
.L1368:
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
	ldr	r0, [r4, r0, asl #2]	@ D.41146, s_pstVfmwChan
	cmp	r0, #0	@ D.41146,
	beq	.L1404	@,
	ldr	r7, [r0, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	r6, [r0, #1744]	@ ModuleLowlyEnable, <variable>.stSynExtraData.s32ModuleLowlyEnable
	cmp	r7, #16	@ <variable>.eVidStd,
	ldrls	pc, [pc, r7, asl #2]	@ <variable>.eVidStd
	b	.L1393	@
.L1385:
	.word	.L1373
	.word	.L1374
	.word	.L1375
	.word	.L1376
	.word	.L1393
	.word	.L1377
	.word	.L1378
	.word	.L1393
	.word	.L1379
	.word	.L1380
	.word	.L1381
	.word	.L1381
	.word	.L1381
	.word	.L1382
	.word	.L1393
	.word	.L1383
	.word	.L1384
.L1373:
	add	r2, r0, #250880	@, D.41146,
	str	ip, [sp, #4]	@ VdhId,
	add	r0, r2, #616	@,,
	mov	r2, #1	@,
	str	r6, [sp, #0]	@ ModuleLowlyEnable,
	bl	H264DEC_VDMPostProc	@
	ldr	r0, [r4, r5, asl #2]	@ tmp152, s_pstVfmwChan
	movw	r7, #:lower16:265056	@ tmp153,
	movt	r7, #:upper16:265056	@ tmp153,
	movw	r8, #:lower16:.LANCHOR0	@ tmp151,
	movt	r8, #:upper16:.LANCHOR0	@ tmp151,
	ldrb	r3, [r0, r7]	@ zero_extendqisi2	@ <variable>.stSynCtx.unSyntax.stH264Ctx.IsStreamEndFlag, <variable>.stSynCtx.unSyntax.stH264Ctx.IsStreamEndFlag
	cmp	r3, #1	@ <variable>.stSynCtx.unSyntax.stH264Ctx.IsStreamEndFlag,
	beq	.L1405	@,
.L1386:
	cmp	r6, #1	@ ModuleLowlyEnable,
	beq	.L1393	@,
	ldr	r0, [r4, r5, asl #2]	@ tmp161, s_pstVfmwChan
	movw	r3, #:lower16:251856	@ tmp162,
	movt	r3, #:upper16:251856	@ tmp162,
	mov	lr, #0	@ tmp163,
	str	lr, [r0, r3]	@ tmp163,
.L1393:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1384:
	add	r7, r0, #250880	@, D.41146,
	mov	r2, #1	@,
	add	r0, r7, #616	@,,
	stmia	sp, {r6, ip}	@ phole stm
	bl	HEVCDEC_VDMPostProc	@
	ldr	r1, [r4, r5, asl #2]	@ tmp167, s_pstVfmwChan
	movw	r7, #:lower16:251502	@ tmp168,
	movt	r7, #:upper16:251502	@ tmp168,
	movw	r8, #:lower16:.LANCHOR0	@ tmp166,
	movt	r8, #:upper16:.LANCHOR0	@ tmp166,
	ldrb	r2, [r1, r7]	@ zero_extendqisi2	@ <variable>.stSynCtx.unSyntax.stHevcCtx.IsStreamEndFlag, <variable>.stSynCtx.unSyntax.stHevcCtx.IsStreamEndFlag
	cmp	r2, #1	@ <variable>.stSynCtx.unSyntax.stHevcCtx.IsStreamEndFlag,
	beq	.L1406	@,
.L1387:
	cmp	r6, #1	@ ModuleLowlyEnable,
	beq	.L1393	@,
	ldr	r2, [r4, r5, asl #2]	@ tmp176, s_pstVfmwChan
	movw	r3, #:lower16:2211688	@ tmp177,
	movt	r3, #:upper16:2211688	@ tmp177,
	mov	lr, #0	@ tmp178,
	str	lr, [r2, r3]	@ tmp178,
	b	.L1393	@
.L1374:
	add	r2, r0, #250880	@, D.41146,
	movw	r6, #:lower16:329751	@ tmp239,
	add	r0, r2, #616	@,,
	movt	r6, #:upper16:329751	@ tmp239,
	bl	VC1DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ prephitmp.4477, s_pstVfmwChan
.L1403:
	ldrb	lr, [r2, r6]	@ zero_extendqisi2	@ <variable>.stSynCtx.unSyntax.stVc1Ctx.CodecInfo.IsStreamEndFlag,
	movw	r4, #:lower16:.LANCHOR0	@ tmp238,
	movt	r4, #:upper16:.LANCHOR0	@ tmp238,
	cmp	lr, #1	@ <variable>.stSynCtx.unSyntax.stVc1Ctx.CodecInfo.IsStreamEndFlag,
	beq	.L1407	@,
.L1397:
	movw	r0, #:lower16:251500	@ tmp234,
	movt	r0, #:upper16:251500	@ tmp234,
	mov	r1, #0	@ tmp235,
	str	r1, [r2, r0]	@ tmp235,
	b	.L1393	@
.L1375:
	add	ip, r0, #250880	@, D.41146,
	mov	r2, r3	@, pLumaInfo
	add	r0, ip, #616	@,,
	movw	r6, #:lower16:.LANCHOR0	@ tmp194,
	bl	MPEG4DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ prephitmp.4471, s_pstVfmwChan
	movw	r4, #:lower16:307792	@ tmp195,
	movt	r4, #:upper16:307792	@ tmp195,
	movt	r6, #:upper16:.LANCHOR0	@ tmp194,
	ldrb	r1, [r2, r4]	@ zero_extendqisi2	@ <variable>.stSynCtx.unSyntax.stMpeg4Ctx.IsStreamEndFlag, <variable>.stSynCtx.unSyntax.stMpeg4Ctx.IsStreamEndFlag
	cmp	r1, #1	@ <variable>.stSynCtx.unSyntax.stMpeg4Ctx.IsStreamEndFlag,
	beq	.L1408	@,
.L1389:
	movw	r3, #:lower16:252532	@ tmp203,
	movt	r3, #:upper16:252532	@ tmp203,
	mov	lr, #0	@ tmp204,
	str	lr, [r2, r3]	@ tmp204,
	b	.L1393	@
.L1376:
	add	r6, r0, #250880	@, D.41146,
	add	r0, r6, #616	@,,
	movw	r6, #:lower16:365162	@ tmp182,
	bl	MPEG2DEC_VDMPostProc	@
	movt	r6, #:upper16:365162	@ tmp182,
	ldr	r2, [r4, r5, asl #2]	@ prephitmp.4468, s_pstVfmwChan
	b	.L1403	@
.L1377:
	add	ip, r0, #250880	@, D.41146,
	add	r0, ip, #616	@,,
	bl	DIVX3DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ tmp233, s_pstVfmwChan
	b	.L1397	@
.L1378:
	add	r6, r0, #250880	@, D.41146,
	add	r0, r6, #616	@,,
	movw	r6, #:lower16:268612	@ tmp208,
	bl	AVSDEC_VDMPostProc	@
	movt	r6, #:upper16:268612	@ tmp208,
	ldr	r2, [r4, r5, asl #2]	@ prephitmp.4474, s_pstVfmwChan
	b	.L1403	@
.L1379:
	add	lr, r0, #250880	@, D.41146,
	add	r0, lr, #616	@,,
	bl	REAL8DEC_VDMPostProc	@
	ldr	ip, [r4, r5, asl #2]	@ tmp221, s_pstVfmwChan
	movw	r0, #:lower16:251500	@ tmp222,
	movt	r0, #:upper16:251500	@ tmp222,
	mov	r1, #0	@ tmp223,
	str	r1, [ip, r0]	@ tmp223,
	b	.L1393	@
.L1380:
	add	r3, r0, #250880	@, D.41146,
	add	r0, r3, #616	@,,
	bl	REAL9DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ tmp233, s_pstVfmwChan
	b	.L1397	@
.L1381:
	add	r0, r0, #250880	@, D.41146,
	add	r0, r0, #616	@,,
	bl	VP6DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ tmp233, s_pstVfmwChan
	b	.L1397	@
.L1382:
	add	r2, r0, #250880	@, D.41146,
	add	r0, r2, #616	@,,
	bl	VP8DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ tmp233, s_pstVfmwChan
	b	.L1397	@
.L1383:
	add	r6, r0, #250880	@, D.41146,
	mov	r2, #1	@,
	add	r0, r6, #616	@,,
	movw	r6, #:lower16:.LANCHOR0	@ tmp263,
	bl	MVC_DEC_VDMPostProc	@
	ldr	r2, [r4, r5, asl #2]	@ prephitmp.4438, s_pstVfmwChan
	movw	r4, #:lower16:251497	@ tmp264,
	movt	r4, #:upper16:251497	@ tmp264,
	movt	r6, #:upper16:.LANCHOR0	@ tmp263,
	ldrb	r1, [r2, r4]	@ zero_extendqisi2	@ <variable>.stSynCtx.unSyntax.stMvcCtx.IsStreamEndFlag, <variable>.stSynCtx.unSyntax.stMvcCtx.IsStreamEndFlag
	cmp	r1, #1	@ <variable>.stSynCtx.unSyntax.stMvcCtx.IsStreamEndFlag,
	beq	.L1409	@,
.L1392:
	movw	r0, #:lower16:251724	@ tmp272,
	movt	r0, #:upper16:251724	@ tmp272,
	mov	lr, #0	@ tmp273,
	str	lr, [r2, r0]	@ tmp273,
	b	.L1393	@
.L1404:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4594	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	b	.L1393	@
.L1407:
	mov	r0, r5	@, ChanId
	bl	VCTRL_OutputLastFrame	@
	ldr	r3, [r4, r5, asl #2]	@ tmp242, s_pstVfmwChan
	mov	ip, #0	@ tmp244,
	strb	ip, [r3, r6]	@ tmp244,
	ldr	r2, [r4, r5, asl #2]	@ prephitmp.4477, s_pstVfmwChan
	b	.L1397	@
.L1408:
	mov	r0, r5	@, ChanId
	bl	VCTRL_OutputLastFrame	@
	ldr	r2, [r6, r5, asl #2]	@ tmp198, s_pstVfmwChan
	mov	r0, #0	@ tmp200,
	strb	r0, [r2, r4]	@ tmp200, <variable>.stSynCtx.unSyntax.stMpeg4Ctx.IsStreamEndFlag
	ldr	r2, [r6, r5, asl #2]	@ prephitmp.4471, s_pstVfmwChan
	b	.L1389	@
.L1409:
	mov	r0, r5	@, ChanId
	bl	VCTRL_OutputLastFrame	@
	ldr	r3, [r6, r5, asl #2]	@ tmp267, s_pstVfmwChan
	mov	ip, #0	@ tmp269,
	strb	ip, [r3, r4]	@ tmp269, <variable>.stSynCtx.unSyntax.stMvcCtx.IsStreamEndFlag
	ldr	r2, [r6, r5, asl #2]	@ prephitmp.4438, s_pstVfmwChan
	b	.L1392	@
.L1405:
	mov	r0, r5	@, ChanId
	bl	VCTRL_OutputLastFrame	@
	ldr	ip, [r8, r5, asl #2]	@ tmp156, s_pstVfmwChan
	mov	r1, #0	@ tmp158,
	strb	r1, [ip, r7]	@ tmp158, <variable>.stSynCtx.unSyntax.stH264Ctx.IsStreamEndFlag
	b	.L1386	@
.L1406:
	mov	r0, r5	@, ChanId
	bl	VCTRL_OutputLastFrame	@
	ldr	r0, [r8, r5, asl #2]	@ tmp171, s_pstVfmwChan
	mov	ip, #0	@ tmp173,
	strb	ip, [r0, r7]	@ tmp173, <variable>.stSynCtx.unSyntax.stHevcCtx.IsStreamEndFlag
	b	.L1387	@
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
	bhi	.L1416	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp142,
	movt	r3, #:upper16:.LANCHOR0	@ tmp142,
	ldr	r3, [r3, r0, asl #2]	@ D.41202, s_pstVfmwChan
	cmp	r3, #0	@ D.41202,
	beq	.L1417	@,
	ldr	r1, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r1, #1	@ <variable>.s32IsRun,
	beq	.L1414	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC216	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r2, #4743	@,
	movt	r3, #:upper16:.LC216	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
.L1415:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1414:
	bl	VCTRL_GetDecParam	@
	cmp	r0, #0	@,
	beq	.L1415	@,
	ldr	ip, [fp, #4]	@ VdhId, VdhId
	mov	r0, r4	@, ChanId
	mov	r1, r7	@, ErrRatio
	mov	r2, r6	@, Mb0QpInCurrPic
	mov	r3, r5	@, pLumaInfo
	str	ip, [sp, #0]	@ VdhId,
	bl	VCTRL_PostProc	@
	b	.L1415	@
.L1416:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4741	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC28	@,
	mov	r0, #0	@,
	movt	r3, #:upper16:.LC28	@,
	bl	dprint_vfmw	@
	b	.L1415	@
.L1417:
	mov	r0, r3	@, D.41202
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4742	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC215	@,
	movt	r3, #:upper16:.LC215	@,
	bl	dprint_vfmw	@
	b	.L1415	@
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
	ldr	r4, .L1420	@ tmp138,
	sub	r7, fp, #172	@ tmp136,,
	ldr	r5, .L1420+4	@ tmp140,
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
.L1421:
	.align	2
.L1420:
	.word	.LANCHOR0+504
	.word	.LANCHOR3-1748
	.fnend
	.size	VCTRL_ExtAccPostProcess, .-VCTRL_ExtAccPostProcess
	.align	2
	.global	VCTRL_ReleaseChanImage
	.type	VCTRL_ReleaseChanImage, %function
VCTRL_ReleaseChanImage:
	.fnstart
.LFB1585:
	@ args = 0, pretend = 0, frame = 496
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #496
	sub	sp, sp, #496	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ ChanID,
	mov	r4, r0	@ ChanID, ChanID
	mov	r6, r1	@ pImage, pImage
	bhi	.L1436	@,
	movw	r5, #:lower16:.LANCHOR0	@ tmp145,
	movt	r5, #:upper16:.LANCHOR0	@ tmp145,
	ldr	r0, [r5, r0, asl #2]	@ D.40947, s_pstVfmwChan
	cmp	r0, #0	@ D.40947,
	beq	.L1437	@,
	ldr	r3, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r3, #1	@ <variable>.s32IsOpen,
	bne	.L1438	@,
	cmp	r1, #0	@ pImage,
	beq	.L1439	@,
	mov	r2, r4	@, ChanID
	ldr	r3, [r1, #196]	@, <variable>.image_id
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC231	@,
	movt	r1, #:upper16:.LC231	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, [r5, r4, asl #2]	@ temp.4556, s_pstVfmwChan
	cmp	r0, #0	@ temp.4556,
	movweq	r1, #:lower16:.LC232	@,
	movweq	r2, #4300	@,
	movteq	r1, #:upper16:.LC232	@,
	beq	.L1435	@,
	ldr	r1, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r1, #1	@ <variable>.s32IsOpen,
	bne	.L1440	@,
	add	r0, r0, #250880	@, temp.4556,
	mov	r1, r6	@, pImage
	add	r0, r0, #608	@,,
	bl	SYNTAX_ReleaseImage	@
	ldr	r3, [r6, #252]	@ D.40965, <variable>.image_id_1
	cmn	r3, #1	@ D.40965,
	mov	r7, r0	@ ret,
	beq	.L1430	@,
	ldr	r7, [r5, r4, asl #2]	@ tmp167, s_pstVfmwChan
	sub	r1, fp, #524	@,,
	str	r3, [fp, #-328]	@ D.40965, Image_1.image_id
	add	r2, r7, #250880	@, tmp167,
	add	r0, r2, #608	@,,
	bl	SYNTAX_ReleaseImage	@
	mov	r7, r0	@ ret,
.L1430:
	mov	r0, #13	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	bne	.L1441	@,
.L1431:
	cmp	r7, #1	@ ret,
	beq	.L1442	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC234	@,
	ldr	r2, .L1443	@,
	movt	r1, #:upper16:.LC234	@,
	bl	dprint_vfmw	@
	mvn	r4, #0	@ ret.4552,
.L1433:
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinUnLockIRQ	@
.L1424:
	mov	r0, r4	@, ret.4552
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1441:
	bl	OSAL_GetTimeInMs	@
	movw	r3, #:lower16:.LANCHOR3	@ tmp170,
	movt	r3, #:upper16:.LANCHOR3	@ tmp170,
	movw	r2, #:lower16:g_TraceImgPeriod	@ tmp177,
	add	r3, r3, r4, asl #2	@, tmp173, tmp170, ChanID,
	movt	r2, #:upper16:g_TraceImgPeriod	@ tmp177,
	ldr	r1, [r3, #-1736]	@ tmp176, last_rec_pos_time
	mov	ip, r0	@ currtime,
	ldr	r0, [r2, #0]	@ g_TraceImgPeriod, g_TraceImgPeriod
	rsb	r1, r1, ip	@ tmp175, tmp176, currtime
	cmp	r1, r0	@ tmp175, g_TraceImgPeriod
	bls	.L1431	@,
	mov	r4, r4, asl #24	@ tmp186, ChanID,
	ldr	r0, .L1443	@,
	add	r2, r4, #851968	@ tmp187, tmp186,
	movw	r1, #4337	@,
	cmp	r7, #1	@ ret,
	addeq	r2, r2, #1	@,,, tmp187
	str	ip, [r3, #-1736]	@ currtime, last_rec_pos_time
	bl	DBG_AddTrace	@
	b	.L1431	@
.L1442:
	mov	r4, #0	@ ret.4552,
	b	.L1433	@
.L1440:
	movw	r1, #:lower16:.LC233	@,
	movt	r1, #:upper16:.LC233	@,
	movw	r2, #4306	@,
	mov	r0, #0	@,
.L1435:
	bl	dprint_vfmw	@
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	mvn	r4, #0	@ ret.4552,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L1424	@
.L1438:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4292	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC215	@,
	movt	r3, #:upper16:.LC215	@,
	bl	dprint_vfmw	@
	mvn	r4, #0	@ ret.4552,
	b	.L1424	@
.L1436:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4290	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r4, #0	@ ret.4552,
	b	.L1424	@
.L1439:
	mov	r0, r1	@, pImage
	movw	r2, #4293	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r3, #:lower16:.LC230	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r3, #:upper16:.LC230	@,
	bl	dprint_vfmw	@
	mvn	r4, #0	@ ret.4552,
	b	.L1424	@
.L1437:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4291	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	mvn	r4, #0	@ ret.4552,
	bl	dprint_vfmw	@
	b	.L1424	@
.L1444:
	.align	2
.L1443:
	.word	.LANCHOR1+268
	.fnend
	.size	VCTRL_ReleaseChanImage, .-VCTRL_ReleaseChanImage
	.align	2
	.global	VCTRL_GetChanImage
	.type	VCTRL_GetChanImage, %function
VCTRL_GetChanImage:
	.fnstart
.LFB1584:
	@ args = 0, pretend = 0, frame = 504
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
	mov	r5, r0	@ ChanID, ChanID
	mov	r4, r1	@ pImage, pImage
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC235	@,
	mov	r2, r5	@, ChanID
	movt	r1, #:upper16:.LC235	@,
	bl	dprint_vfmw	@
	cmp	r5, #15	@ ChanID,
	bhi	.L1469	@,
	movw	r6, #:lower16:.LANCHOR0	@ tmp323,
	movt	r6, #:upper16:.LANCHOR0	@ tmp323,
	ldr	r0, [r6, r5, asl #2]	@ D.40825, s_pstVfmwChan
	cmp	r0, #0	@ D.40825,
	beq	.L1470	@,
	ldr	r3, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r3, #1	@ <variable>.s32IsOpen,
	bne	.L1471	@,
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, [r6, r5, asl #2]	@ temp.4598, s_pstVfmwChan
	cmp	r0, #0	@ temp.4598,
	movweq	r1, #:lower16:.LC232	@,
	movweq	r2, #4087	@,
	movteq	r1, #:upper16:.LC232	@,
	beq	.L1468	@,
	ldr	r1, [r0, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r1, #1	@ <variable>.s32IsOpen,
	bne	.L1472	@,
	add	r0, r0, #250880	@, temp.4598,
	mov	r1, r4	@, pImage
	add	r0, r0, #608	@,,
	bl	SYNTAX_ReceiveImage	@
	cmp	r0, #1	@ ret,
	movne	r3, #0	@, D.40839
	moveq	r3, #1	@, D.40839
	mov	r7, r0	@ ret,
	cmp	r4, #0	@ pImage,
	moveq	r2, #0	@, tmp170
	andne	r2, r3, #1	@,, tmp170, D.40839
	cmp	r2, #0	@ tmp170,
	bne	.L1473	@,
	cmp	r3, #0	@ D.40839,
	bne	.L1453	@,
.L1455:
	mov	r0, #12	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	bne	.L1474	@,
.L1463:
	cmp	r7, #1	@ ret,
	mvnne	r7, #0	@ ret,
	beq	.L1475	@,
.L1465:
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinUnLockIRQ	@
.L1447:
	mov	r0, r7	@, ret
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1473:
	movw	r3, #:lower16:.LANCHOR3	@ tmp171,
	movt	r3, #:upper16:.LANCHOR3	@ tmp171,
	add	r8, r3, r5, asl #2	@, tmp174, tmp171, ChanID,
	ldr	r0, [r8, #-1672]	@ D.40844, vfmw_save_yuv_file
	cmp	r0, #0	@ D.40844,
	beq	.L1453	@,
	ldr	r7, [r4, #160]	@ <variable>.format, <variable>.format
	ldr	lr, [r3, #-1544]	@ save_yuv_with_crop, save_yuv_with_crop
	tst	r7, #28	@ <variable>.format,
	movne	ip, #0	@, tmp179
	moveq	ip, #1	@, tmp179
	cmp	lr, #0	@ save_yuv_with_crop,
	beq	.L1454	@,
	ldr	lr, [r4, #352]	@, <variable>.bottom_offset
	ldr	r9, [r4, #348]	@ <variable>.top_offset, <variable>.top_offset
	ldr	r1, [r4, #32]	@ <variable>.luma_vir_addr, <variable>.luma_vir_addr
	ldr	r2, [r4, #36]	@ <variable>.chrom_vir_addr, <variable>.chrom_vir_addr
	ldr	r3, [r4, #164]	@ <variable>.image_width, <variable>.image_width
	ldr	r7, [r4, #192]	@ <variable>.image_stride, <variable>.image_stride
	ldr	r8, [r4, #340]	@ <variable>.left_offset, <variable>.left_offset
	ldr	sl, [r4, #344]	@ <variable>.right_offset, <variable>.right_offset
	str	lr, [fp, #-544]	@, %sfp
	ldr	lr, [r4, #168]	@, <variable>.image_height
	str	r9, [sp, #24]	@ <variable>.top_offset,
	ldr	r9, [fp, #-544]	@, %sfp
	str	lr, [sp, #0]	@,
	mov	lr, #0	@ tmp186,
	str	r7, [sp, #8]	@ <variable>.image_stride,
	str	lr, [sp, #4]	@ tmp186,
	str	ip, [sp, #12]	@ tmp179,
	str	r8, [sp, #16]	@ <variable>.left_offset,
	str	sl, [sp, #20]	@ <variable>.right_offset,
	str	r9, [sp, #28]	@,
	bl	DBG_WriteBigTileYuv	@
.L1453:
	ldr	ip, [r4, #256]	@ <variable>.is_3D, <variable>.is_3D
	mvn	r8, #0	@ tmp202,
	str	r8, [r4, #252]	@ tmp202, <variable>.image_id_1
	cmp	ip, #1	@ <variable>.is_3D,
	movne	r7, #1	@ ret,
	bne	.L1455	@,
.L1477:
	ldr	sl, [r4, #244]	@ <variable>.last_frame, <variable>.last_frame
	cmp	sl, #0	@ <variable>.last_frame,
	beq	.L1476	@,
	add	sl, r4, #416	@ tmp285, pImage,
	ldr	r9, [r4, #92]	@, <variable>.top_chrom_phy_addr
	add	lr, r4, #280	@ tmp284, pImage,
	mov	r7, ip	@ ret, <variable>.is_3D
	ldmia	sl!, {r0, r1, r2, r3}	@ tmp287,,,,
	str	r9, [r4, #264]	@, <variable>.top_chrom_phy_addr_1
	ldr	r9, [r4, #88]	@, <variable>.top_luma_phy_addr
	str	r9, [r4, #260]	@, <variable>.top_luma_phy_addr_1
	mov	r9, lr	@ tmp286, tmp284
	mov	lr, sl	@ tmp337, tmp287
	stmia	r9!, {r0, r1, r2, r3}	@ tmp286,,,,
	mov	sl, r9	@ tmp338, tmp286
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp337,,,,
	stmia	sl!, {r0, r1, r2, r3}	@ tmp338,,,,
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp339,,,,
	stmia	sl!, {r0, r1, r2, r3}	@ tmp338,,,,
	ldmia	lr, {r0, r1, r2}	@ tmp339,,,
	stmia	sl, {r0, r1, r2}	@ tmp340,,,
	mov	r1, #3	@ tmp289,
	str	r8, [r4, #252]	@ tmp202, <variable>.image_id_1
	str	r1, [r4, #360]	@ tmp289, <variable>.eFramePackingType
	str	ip, [r4, #244]	@ <variable>.is_3D, <variable>.last_frame
	b	.L1455	@
.L1474:
	bl	OSAL_GetTimeInMs	@
	movw	r3, #:lower16:.LANCHOR3	@ tmp291,
	movt	r3, #:upper16:.LANCHOR3	@ tmp291,
	add	r3, r3, r5, asl #2	@, tmp294, tmp291, ChanID,
	ldr	r1, [r3, #-1540]	@ tmp297, last_rec_pos_time
	mov	ip, r0	@ currtime,
	movw	r0, #:lower16:g_TraceImgPeriod	@ tmp298,
	movt	r0, #:upper16:g_TraceImgPeriod	@ tmp298,
	ldr	r2, [r0, #0]	@ g_TraceImgPeriod, g_TraceImgPeriod
	rsb	r0, r1, ip	@ tmp296, tmp297, currtime
	cmp	r0, r2	@ tmp296, g_TraceImgPeriod
	bls	.L1463	@,
	mov	lr, r5, asl #24	@ tmp307, ChanID,
	ldr	r0, .L1482	@,
	add	r2, lr, #786432	@ tmp308, tmp307,
	movw	r1, #4253	@,
	cmp	r7, #1	@ ret,
	addeq	r2, r2, #1	@,,, tmp308
	str	ip, [r3, #-1540]	@ currtime, last_rec_pos_time
	bl	DBG_AddTrace	@
	b	.L1463	@
.L1475:
	mov	r0, r5	@, ChanID
	mov	r2, #0	@,
	mov	r1, #12	@,
	mov	r7, r2	@ ret,
	bl	DBG_CountTimeInfo	@
	ldr	ip, [r6, r5, asl #2]	@ tmp314, s_pstVfmwChan
	mov	r1, r4	@, pImage
	mov	r2, #496	@,
	add	r0, ip, #320	@, tmp314,
	bl	memcpy	@
	b	.L1465	@
.L1454:
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
	bne	.L1455	@,
	b	.L1477	@
.L1471:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	mov	r2, #4080	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC215	@,
	movt	r3, #:upper16:.LC215	@,
	bl	dprint_vfmw	@
	mvn	r7, #0	@ ret,
	b	.L1447	@
.L1472:
	movw	r1, #:lower16:.LC233	@,
	movt	r1, #:upper16:.LC233	@,
	movw	r2, #4093	@,
	mov	r0, #0	@,
.L1468:
	bl	dprint_vfmw	@
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	mvn	r7, #0	@ ret,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L1447	@
.L1476:
	ldr	r3, [r6, r5, asl #2]	@ tmp208, s_pstVfmwChan
	sub	sl, fp, #540	@ tmp209,,
	movw	r9, #:lower16:.LANCHOR0	@ tmp205,
	movt	r9, #:upper16:.LANCHOR0	@ tmp205,
	add	ip, r3, #250880	@, tmp208,
	mov	r1, sl	@, tmp209
	add	r0, ip, #608	@,,
	bl	SYNTAX_ReceiveImage	@
	cmp	r0, #1	@ ret,
	mov	r7, r0	@ ret,
	bne	.L1478	@,
	ldr	r3, [r4, #248]	@ D.40875, <variable>.view_id
	ldr	r0, [fp, #-292]	@ D.40876, Image_1.view_id
	cmp	r3, r0	@ D.40875, D.40876
	blt	.L1479	@,
	bgt	.L1480	@,
	cmp	r3, #0	@ D.40875,
	bne	.L1461	@,
	ldr	r0, [r9, r5, asl #2]	@ tmp242, s_pstVfmwChan
	add	lr, r0, #250880	@, tmp242,
	add	r0, lr, #608	@,,
	bl	SYNTAX_ReturnImage	@
	ldr	r2, [r9, r5, asl #2]	@ tmp246, s_pstVfmwChan
	mov	r1, r4	@, pImage
	add	ip, r2, #250880	@, tmp246,
	add	r0, ip, #608	@,,
	bl	SYNTAX_ReleaseImage	@
	mov	r0, r7	@, ret
	movw	r1, #:lower16:.LC237	@,
	ldr	r2, .L1482	@,
	movt	r1, #:upper16:.LC237	@,
	ldr	r3, [r4, #248]	@, <variable>.view_id
	mvn	r7, #1	@ ret,
	bl	dprint_vfmw	@
	b	.L1455	@
.L1469:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4076	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r7, #0	@ ret,
	b	.L1447	@
.L1478:
	ldr	r2, [r9, r5, asl #2]	@ tmp214, s_pstVfmwChan
	add	r1, r2, #250880	@, tmp214,
	add	r0, r1, #608	@,,
	bl	SYNTAX_ReturnImage	@
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L1447	@
.L1479:
	ldr	r8, [fp, #-448]	@ Image_1.top_chrom_phy_addr, Image_1.top_chrom_phy_addr
	sub	lr, fp, #124	@ tmp221,,
	add	ip, r4, #280	@ tmp220, pImage,
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp325,,,,
	str	r8, [r4, #264]	@ Image_1.top_chrom_phy_addr, <variable>.top_chrom_phy_addr_1
	ldr	r8, [fp, #-452]	@ Image_1.top_luma_phy_addr, Image_1.top_luma_phy_addr
	str	r8, [r4, #260]	@ Image_1.top_luma_phy_addr, <variable>.top_luma_phy_addr_1
	ldr	r8, [fp, #-444]	@ Image_1.btm_luma_phy_addr, Image_1.btm_luma_phy_addr
	str	r8, [r4, #268]	@ Image_1.btm_luma_phy_addr, <variable>.btm_luma_phy_addr_1
	ldr	r8, [fp, #-440]	@ Image_1.btm_chrom_phy_addr, Image_1.btm_chrom_phy_addr
	str	r8, [r4, #272]	@ Image_1.btm_chrom_phy_addr, <variable>.btm_chrom_phy_addr_1
	mov	r8, ip	@ tmp326, tmp220
	stmia	r8!, {r0, r1, r2, r3}	@ tmp326,,,,
	mov	ip, r8	@ tmp328, tmp326
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp327,,,,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp328,,,,
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp329,,,,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp328,,,,
	ldmia	lr, {r0, r1, r2}	@ tmp329,,,
	stmia	ip, {r0, r1, r2}	@ tmp330,,,
	ldr	r3, [fp, #-296]	@ Image_1.last_frame, Image_1.last_frame
	ldr	lr, [fp, #-344]	@ Image_1.image_id, Image_1.image_id
	mov	ip, #3	@ tmp223,
	cmp	r3, #0	@ Image_1.last_frame,
	str	ip, [r4, #360]	@ tmp223, <variable>.eFramePackingType
	str	lr, [r4, #252]	@ Image_1.image_id, <variable>.image_id_1
	strne	r7, [r4, #244]	@ ret, <variable>.last_frame
	b	.L1455	@
.L1461:
	ldr	ip, [r9, r5, asl #2]	@ tmp254, s_pstVfmwChan
	mov	r1, r4	@, pImage
	add	r3, ip, #250880	@, tmp254,
	add	r0, r3, #608	@,,
	bl	SYNTAX_ReleaseImage	@
	ldr	r1, [fp, #-296]	@ Image_1.last_frame, Image_1.last_frame
	cmp	r1, #0	@ Image_1.last_frame,
	beq	.L1481	@,
	ldr	r3, [r4, #248]	@, <variable>.view_id
	mov	r0, r7	@, ret
	ldr	r2, .L1482	@,
	movw	r1, #:lower16:.LC238	@,
	movt	r1, #:upper16:.LC238	@,
	bl	dprint_vfmw	@
	mov	r1, sl	@, tmp209
	mov	r2, #496	@,
	mov	r0, r4	@, pImage
	bl	memcpy	@
	sub	lr, fp, #124	@ tmp278,,
	ldr	sl, [fp, #-448]	@ Image_1.top_chrom_phy_addr, Image_1.top_chrom_phy_addr
	add	ip, r4, #280	@ tmp277, pImage,
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp331,,,,
	str	sl, [r4, #264]	@ Image_1.top_chrom_phy_addr, <variable>.top_chrom_phy_addr_1
	ldr	sl, [fp, #-452]	@ Image_1.top_luma_phy_addr, Image_1.top_luma_phy_addr
	str	sl, [r4, #260]	@ Image_1.top_luma_phy_addr, <variable>.top_luma_phy_addr_1
	mov	sl, ip	@ tmp332, tmp277
	mov	ip, lr	@ tmp333, tmp331
	stmia	sl!, {r0, r1, r2, r3}	@ tmp332,,,,
	mov	lr, sl	@ tmp334, tmp332
	ldmia	ip!, {r0, r1, r2, r3}	@ tmp333,,,,
	stmia	lr!, {r0, r1, r2, r3}	@ tmp334,,,,
	ldmia	ip!, {r0, r1, r2, r3}	@ tmp335,,,,
	stmia	lr!, {r0, r1, r2, r3}	@ tmp334,,,,
	ldmia	ip, {r0, r1, r2}	@ tmp335,,,
	stmia	lr, {r0, r1, r2}	@ tmp336,,,
	mov	r0, #3	@ tmp280,
	str	r8, [r4, #252]	@ tmp202, <variable>.image_id_1
	str	r0, [r4, #360]	@ tmp280, <variable>.eFramePackingType
	str	r7, [r4, #244]	@ ret, <variable>.last_frame
	b	.L1455	@
.L1480:
	ldr	r3, [r9, r5, asl #2]	@ tmp229, s_pstVfmwChan
	add	r1, r3, #250880	@, tmp229,
	add	r0, r1, #608	@,,
	bl	SYNTAX_ReturnImage	@
	ldr	r0, [r9, r5, asl #2]	@ tmp233, s_pstVfmwChan
	mov	r1, r4	@, pImage
	add	r2, r0, #250880	@, tmp233,
	add	r0, r2, #608	@,,
	bl	SYNTAX_ReleaseImage	@
	mov	r0, r7	@, ret
	ldr	r7, [fp, #-292]	@ Image_1.view_id, Image_1.view_id
	movw	r1, #:lower16:.LC236	@,
	ldr	r3, [r4, #248]	@ <variable>.view_id, <variable>.view_id
	movt	r1, #:upper16:.LC236	@,
	ldr	r2, .L1482	@,
	str	r7, [sp, #0]	@ Image_1.view_id,
	bl	dprint_vfmw	@
	mvn	r7, #1	@ ret,
	b	.L1455	@
.L1470:
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #4077	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	mvn	r7, #0	@ ret,
	bl	dprint_vfmw	@
	b	.L1447	@
.L1481:
	ldr	lr, [r9, r5, asl #2]	@ tmp259, s_pstVfmwChan
	mov	r1, sl	@, tmp209
	add	r2, lr, #250880	@, tmp259,
	add	r0, r2, #608	@,,
	bl	SYNTAX_ReleaseImage	@
	mov	r0, r7	@, ret
	movw	r1, #:lower16:.LC238	@,
	ldr	r2, .L1482	@,
	movt	r1, #:upper16:.LC238	@,
	ldr	r3, [r4, #248]	@, <variable>.view_id
	mvn	r7, #1	@ ret,
	bl	dprint_vfmw	@
	b	.L1455	@
.L1483:
	.align	2
.L1482:
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
	beq	.L1489	@,
	bl	SM_Reset	@
	cmp	r0, #0	@ ret
	mvnne	r0, #0	@, D.40738,
	ldmfd	sp, {fp, sp, pc}	@
.L1489:
	mov	r0, r3	@, tmp138
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #3957	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40738,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VCTRL_ReleaseStream, .-VCTRL_ReleaseStream
	.align	2
	.global	VCTRL_LoadDspCode
	.type	VCTRL_LoadDspCode, %function
VCTRL_LoadDspCode:
	.fnstart
.LFB1580:
	@ args = 0, pretend = 0, frame = 96
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #108
	sub	sp, sp, #108	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	sub	r4, fp, #120	@ tmp140,,
	mov	r5, r0	@ ChanID, ChanID
	mov	r1, #92	@,
	mov	r0, r4	@, tmp140
	bl	__memzero	@
	mov	r0, r5	@, ChanID
	mov	r1, r4	@, tmp140
	bl	VCTRL_GetChanCfg	@
	subs	r6, r0, #0	@ ret,
	bne	.L1504	@,
	ldr	r0, [fp, #-120]	@ D.40642, stCfgInfo.eVidStd
	movw	r3, #:lower16:.LANCHOR3	@ tmp197,
	movt	r3, #:upper16:.LANCHOR3	@ tmp197,
	cmp	r0, #0	@ D.40642,
	ldr	ip, [r3, #-1476]	@ eDSPState, g_DSPState
	movne	r2, r6	@ ScdLowdlyEnable, ret
	ldreq	r2, [fp, #-72]	@ ScdLowdlyEnable, stCfgInfo.s32LowdlyEnable
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1472]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1468]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1464]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1460]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1456]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1452]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1448]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1444]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1440]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1436]	@ eDSPState, g_DSPState
	mov	r4, r3	@ tmp153, tmp197
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1432]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1428]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1424]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1420]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	ldr	ip, [r3, #-1416]	@ eDSPState, g_DSPState
	cmp	ip, #0	@ eDSPState,
	bne	.L1495	@,
	cmp	r2, #1	@ ScdLowdlyEnable,
	movne	r1, #0	@, tmp172
	moveq	r1, #1	@, tmp172
	cmp	r0, #6	@ D.40642,
	movne	r3, #0	@, temp.4682
	moveq	r3, #1	@, temp.4682
	cmp	r1, #0	@ tmp172,
	beq	.L1505	@,
	add	r4, r4, r5, asl #2	@, tmp184, tmp153, ChanID,
	mov	r1, ip	@, eDSPState
	bl	WriteHexFile	@
	mov	r3, #1	@ tmp186,
	str	r3, [r4, #-1476]	@ tmp186, g_DSPState
.L1492:
	mov	r0, r6	@, ret
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1495:
	cmp	ip, #2	@ eDSPState,
	cmpeq	r2, #1	@, ScdLowdlyEnable,
	beq	.L1497	@,
	cmp	ip, #1	@ eDSPState,
	cmpeq	r0, #6	@, D.40642,
	bne	.L1492	@,
.L1497:
	mov	r3, r0	@, D.40642
	movw	r1, #:lower16:.LC240	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC240	@,
	str	ip, [sp, #0]	@ eDSPState,
	mvn	r6, #0	@ ret,
	bl	dprint_vfmw	@
	b	.L1492	@
.L1505:
	cmp	r3, #0	@ temp.4682,
	beq	.L1492	@,
	add	r4, r4, r5, asl #2	@, tmp193, tmp153, ChanID,
	mov	r0, #6	@,
	bl	WriteHexFile	@
	mov	r0, #2	@ tmp195,
	str	r0, [r4, #-1476]	@ tmp195, g_DSPState
	b	.L1492	@
.L1504:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC239	@,
	movw	r2, #3576	@,
	movt	r1, #:upper16:.LC239	@,
	bl	dprint_vfmw	@
	mvn	r6, #0	@ ret,
	b	.L1492	@
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
	ldr	r2, [r3, r0, asl #2]	@ D.40594, s_pstVfmwChan
	cmp	r2, #0	@ D.40594,
	beq	.L1513	@,
	ldr	r2, [r2, #1032]	@ D.40602, <variable>.eVidStd
	sub	ip, r2, #10	@ tmp143, D.40602,
	cmp	ip, #2	@ tmp143,
	bls	.L1514	@,
	cmp	r2, #4	@ D.40602,
	bne	.L1515	@,
.L1510:
	mvn	r0, #0	@ D.40598,
	ldmfd	sp, {fp, sp, pc}	@
.L1514:
	ldr	r3, [r3, #500]	@ g_VdmCharacter, g_VdmCharacter
	tst	r3, #1	@ g_VdmCharacter,
	beq	.L1510	@,
.L1511:
	bl	SM_SeekPts	@
	cmp	r0, #0	@ ret
	ldmeqfd	sp, {fp, sp, pc}	@
	b	.L1510	@
.L1515:
	cmp	r2, #14	@ D.40602,
	beq	.L1510	@,
	b	.L1511	@
.L1513:
	mov	r0, r2	@, D.40594
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #3538	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40598,
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
	bhi	.L1522	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp140,
	movt	r4, #:upper16:.LANCHOR0	@ tmp140,
	ldr	r3, [r4, r0, asl #2]	@ D.40130, s_pstVfmwChan
	cmp	r3, #0	@ D.40130,
	beq	.L1523	@,
	ldr	r2, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r2, #1	@ <variable>.s32IsOpen,
	beq	.L1524	@,
.L1520:
	mvn	r0, #0	@ D.40128,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1523:
	mov	r0, r3	@, D.40130
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2795	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC241	@,
	movt	r3, #:upper16:.LC241	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40128,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1522:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2794	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40128,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1524:
	str	r2, [r3, #28]	@ <variable>.s32IsOpen, <variable>.s32StopSyntax
	mov	r2, #0	@ tmp147,
	ldr	r3, [r4, r0, asl #2]	@ tmp146, s_pstVfmwChan
	str	r2, [r3, #16]	@ tmp147, <variable>.s32IsRun
	bl	SM_Stop	@
	subs	r6, r0, #0	@ s32Ret,
	bne	.L1520	@,
	mov	r1, r6	@, s32Ret
	mov	r0, r5	@, ChanID
	bl	DeleteRawPacketInBuffer	@
	mov	r0, r5	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	ldr	r1, [r4, r5, asl #2]	@ tmp149, s_pstVfmwChan
	mov	r0, r6	@ D.40128, s32Ret
	str	r6, [r1, #28]	@ s32Ret, <variable>.s32StopSyntax
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
	b	.L1527	@
.L1532:
	bl	msleep	@
	ldr	r0, .L1533	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	bl	VCTRL_StopChan	@
	mov	r4, r0	@ ret,
	bl	VCTRL_EnableAllInt	@
	ldr	r0, .L1533	@,
	bl	OSAL_SpinUnLockIRQ	@
	cmp	r4, #0	@ ret,
	mov	r0, #10	@,
	beq	.L1526	@,
	bl	msleep	@
	cmp	r5, #50	@ i,
	beq	.L1526	@,
.L1527:
	ldr	r0, .L1533	@,
	add	r5, r5, #1	@ tmp146, i,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	bl	VCTRL_StopChan	@
	add	r5, r5, #1	@ i, tmp146,
	mov	r4, r0	@ ret,
	bl	VCTRL_EnableAllInt	@
	ldr	r0, .L1533	@,
	bl	OSAL_SpinUnLockIRQ	@
	cmp	r4, #0	@ ret,
	mov	r0, #10	@,
	bne	.L1532	@,
.L1526:
	mov	r0, r4	@, ret
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1534:
	.align	2
.L1533:
	.word	.LANCHOR0+504
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
	bhi	.L1575	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp327,
	movt	r4, #:upper16:.LANCHOR0	@ tmp327,
	ldr	r3, [r4, r0, asl #2]	@ D.40054, s_pstVfmwChan
	cmp	r3, #0	@ D.40054,
	beq	.L1576	@,
	ldr	r6, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r6, #1	@ <variable>.s32IsOpen,
	bne	.L1577	@,
	ldr	r3, [r3, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #19	@ <variable>.eVidStd,
	beq	.L1578	@,
	bl	SM_Start	@
	ldr	r2, [r4, r5, asl #2]	@ tmp167, s_pstVfmwChan
	mov	ip, #0	@ tmp171,
	str	r6, [r2, #16]	@ <variable>.s32IsOpen, <variable>.s32IsRun
	ldr	r3, [r4, r5, asl #2]	@ tmp170, s_pstVfmwChan
	str	ip, [r3, #28]	@ tmp171, <variable>.s32StopSyntax
	ldr	r1, [r4, r5, asl #2]	@ tmp173, s_pstVfmwChan
	str	r6, [r1, #20]	@ <variable>.s32IsOpen, <variable>.s32IsInit
	ldr	r3, [r4, r5, asl #2]	@ temp.4792, s_pstVfmwChan
	ldr	r2, [r3, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r2, #0	@ <variable>.s32Priority,
	bne	.L1541	@,
	str	r6, [r3, #24]	@ <variable>.s32IsOpen, <variable>.s32Priority
	ldr	r1, [r4, #0]	@ temp.4794, s_pstVfmwChan
	cmp	r1, #0	@ temp.4794,
	beq	.L1579	@,
	ldr	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r3, #:lower16:.LANCHOR3	@ tmp328,
	movt	r3, #:upper16:.LANCHOR3	@ tmp328,
	movw	r2, #:lower16:g_ChanCtx	@ tmp326,
	movt	r2, #:upper16:g_ChanCtx	@ tmp326,
	str	r0, [r3, #-1412]	@ <variable>.s32Priority, PrioArray
	ldr	lr, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	str	lr, [r2, #0]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
.L1543:
	ldr	lr, [r4, #4]	@ temp.4797, s_pstVfmwChan
	ldr	ip, [r4, #8]	@ temp.4800, s_pstVfmwChan
	cmp	lr, #0	@ temp.4797,
	ldr	r1, [r4, #12]	@ temp.4803, s_pstVfmwChan
	streq	lr, [r3, #-1408]	@ temp.4797, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #4]	@ temp.4797, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-1408]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #4]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.4800,
	streq	ip, [r3, #-1404]	@ temp.4800, PrioArray
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r2, #8]	@ temp.4800, g_ChanCtx.PriorByChanId
	ldr	lr, [r4, #16]	@ temp.4806, s_pstVfmwChan
	strne	r0, [r3, #-1404]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #8]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.4803,
	streq	r1, [r3, #-1400]	@ temp.4803, PrioArray
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r2, #12]	@ temp.4803, g_ChanCtx.PriorByChanId
	ldr	ip, [r4, #20]	@ temp.4809, s_pstVfmwChan
	strne	r0, [r3, #-1400]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #12]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.4806,
	streq	lr, [r3, #-1396]	@ temp.4806, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #16]	@ temp.4806, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-1396]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #16]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.4809,
	streq	ip, [r3, #-1392]	@ temp.4809, PrioArray
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r2, #20]	@ temp.4809, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-1392]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #20]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	r1, [r4, #24]	@ temp.4812, s_pstVfmwChan
	ldr	lr, [r4, #28]	@ temp.4815, s_pstVfmwChan
	cmp	r1, #0	@ temp.4812,
	ldr	ip, [r4, #32]	@ temp.4818, s_pstVfmwChan
	streq	r1, [r3, #-1388]	@ temp.4812, PrioArray
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r2, #24]	@ temp.4812, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-1388]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #24]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.4815,
	streq	lr, [r3, #-1384]	@ temp.4815, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #28]	@ temp.4815, g_ChanCtx.PriorByChanId
	ldr	r1, [r4, #36]	@ temp.4821, s_pstVfmwChan
	strne	r0, [r3, #-1384]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #28]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.4818,
	streq	ip, [r3, #-1380]	@ temp.4818, PrioArray
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r2, #32]	@ temp.4818, g_ChanCtx.PriorByChanId
	ldr	lr, [r4, #40]	@ temp.4824, s_pstVfmwChan
	strne	r0, [r3, #-1380]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #32]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.4821,
	streq	r1, [r3, #-1376]	@ temp.4821, PrioArray
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r2, #36]	@ temp.4821, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-1376]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #36]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.4824,
	streq	lr, [r3, #-1372]	@ temp.4824, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #40]	@ temp.4824, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-1372]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #40]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	ip, [r4, #44]	@ temp.4827, s_pstVfmwChan
	ldr	r1, [r4, #48]	@ temp.4830, s_pstVfmwChan
	cmp	ip, #0	@ temp.4827,
	ldr	lr, [r4, #52]	@ temp.4833, s_pstVfmwChan
	streq	ip, [r2, #44]	@ temp.4827, g_ChanCtx.PriorByChanId
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r3, #-1368]	@ temp.4827, PrioArray
	strne	r0, [r3, #-1368]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #44]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.4830,
	streq	r1, [r2, #48]	@ temp.4830, g_ChanCtx.PriorByChanId
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r3, #-1364]	@ temp.4830, PrioArray
	ldr	ip, [r4, #56]	@ temp.4836, s_pstVfmwChan
	strne	r0, [r3, #-1364]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #48]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.4833,
	streq	lr, [r2, #52]	@ temp.4833, g_ChanCtx.PriorByChanId
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r3, #-1360]	@ temp.4833, PrioArray
	ldr	r1, [r4, #60]	@ D.40067, s_pstVfmwChan
	strne	r0, [r3, #-1360]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #52]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.4836,
	streq	ip, [r2, #56]	@ temp.4836, g_ChanCtx.PriorByChanId
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r3, #-1356]	@ temp.4836, PrioArray
	strne	r0, [r3, #-1356]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #56]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ D.40067,
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r0, [r3, #-1352]	@ <variable>.s32Priority, PrioArray
	ldrne	r3, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	ldr	r0, .L1580	@,
	strne	r3, [r2, #60]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	streq	r1, [r2, #60]	@ D.40067, g_ChanCtx.PriorByChanId
	streq	r1, [r3, #-1352]	@ D.40067, PrioArray
	bl	VDMDRV_SetPriority	@
	mov	r0, r5	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
.L1541:
	mov	r0, r5	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	mov	r0, #0	@ D.40052,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1579:
	movw	r3, #:lower16:.LANCHOR3	@ tmp328,
	movw	r2, #:lower16:g_ChanCtx	@ tmp326,
	movt	r3, #:upper16:.LANCHOR3	@ tmp328,
	movt	r2, #:upper16:g_ChanCtx	@ tmp326,
	str	r1, [r3, #-1412]	@ temp.4794, PrioArray
	str	r1, [r2, #0]	@ temp.4794, g_ChanCtx.PriorByChanId
	b	.L1543	@
.L1577:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	mov	r2, #2624	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC26	@,
	movt	r3, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40052,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1575:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2622	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40052,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1578:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2625	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC242	@,
	movt	r3, #:upper16:.LC242	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40052,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1576:
	mov	r0, r3	@, D.40054
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2623	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC161	@,
	movt	r3, #:upper16:.LC161	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40052,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1581:
	.align	2
.L1580:
	.word	.LANCHOR3-1412
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
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	ldr	r3, [r1, #64]	@ <variable>.s32SelfAllocChanMem_vdh, <variable>.s32SelfAllocChanMem_vdh
	mov	r6, r1	@ pstChan, pstChan
	mov	r8, r0	@ ChanID, ChanID
	cmp	r3, #1	@ <variable>.s32SelfAllocChanMem_vdh,
	beq	.L1605	@,
.L1583:
	ldr	r0, [r6, #28]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	cmp	r0, #0	@ <variable>.stChanMem_vdh.Length,
	bne	.L1606	@,
.L1584:
	ldr	ip, [r6, #68]	@ <variable>.s32SelfAllocChanMem_scd, <variable>.s32SelfAllocChanMem_scd
	cmp	ip, #1	@ <variable>.s32SelfAllocChanMem_scd,
	beq	.L1607	@,
.L1585:
	ldr	lr, [r6, #44]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	cmp	lr, #0	@ <variable>.stChanMem_scd.Length,
	bne	.L1608	@,
.L1586:
	ldr	r1, [r6, #88]	@ <variable>.u32DynamicAllocEn, <variable>.u32DynamicAllocEn
	cmp	r1, #1	@ <variable>.u32DynamicAllocEn,
	beq	.L1587	@,
	ldr	r0, [r6, #24]	@, <variable>.stChanMem_vdh.PhyAddr
	ldr	r1, [r6, #20]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r2, [r6, #28]	@, <variable>.stChanMem_vdh.Length
	bl	MEM_DelMemRecord	@
.L1588:
	ldr	r2, [r6, #44]	@ temp.4893, <variable>.stChanMem_scd.Length
	cmp	r2, #0	@ temp.4893,
	bne	.L1609	@,
.L1593:
	ldr	r3, [r6, #72]	@ <variable>.s32SelfAllocChanMem_ctx, <variable>.s32SelfAllocChanMem_ctx
	cmp	r3, #1	@ <variable>.s32SelfAllocChanMem_ctx,
	beq	.L1610	@,
.L1594:
	ldr	r0, [r6, #52]	@, <variable>.stChanMem_ctx.VirAddr
	bl	KernelMunmap	@
.L1595:
	ldr	r2, [r6, #60]	@, <variable>.stChanMem_ctx.Length
	ldr	r1, [r6, #52]	@, <variable>.stChanMem_ctx.VirAddr
	ldr	r0, [r6, #56]	@, <variable>.stChanMem_ctx.PhyAddr
	bl	MEM_DelMemRecord	@
	mov	r0, r8	@, ChanID
	bl	SM_DeletDSPCtxMem	@
	mov	r0, #0	@,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L1608:
	ldrsb	r3, [r6, #32]	@ <variable>.stChanMem_scd.IsCached, <variable>.stChanMem_scd.IsCached
	cmp	r3, #1	@ <variable>.stChanMem_scd.IsCached,
	bne	.L1586	@,
	ldr	r0, [r6, #36]	@, <variable>.stChanMem_scd.VirAddr
	bl	KernelMunmap	@
	ldr	r0, [r6, #40]	@, <variable>.stChanMem_scd.PhyAddr
	ldr	r1, [r6, #44]	@, <variable>.stChanMem_scd.Length
	bl	KernelMmap	@
	mov	r0, #0	@ tmp166,
	strb	r0, [r6, #32]	@ tmp166, <variable>.stChanMem_scd.IsCached
	b	.L1586	@
.L1606:
	ldrsb	r1, [r6, #16]	@ <variable>.stChanMem_vdh.IsCached, <variable>.stChanMem_vdh.IsCached
	cmp	r1, #1	@ <variable>.stChanMem_vdh.IsCached,
	bne	.L1584	@,
	ldr	r0, [r6, #20]	@, <variable>.stChanMem_vdh.VirAddr
	bl	KernelMunmap	@
	ldr	r0, [r6, #24]	@, <variable>.stChanMem_vdh.PhyAddr
	ldr	r1, [r6, #28]	@, <variable>.stChanMem_vdh.Length
	bl	KernelMmap	@
	mov	r2, #0	@ tmp157,
	strb	r2, [r6, #16]	@ tmp157, <variable>.stChanMem_vdh.IsCached
	b	.L1584	@
.L1610:
	ldr	r0, [r6, #56]	@ D.39509, <variable>.stChanMem_ctx.PhyAddr
	cmp	r0, #0	@ D.39509,
	beq	.L1594	@,
	ldr	r1, [r6, #52]	@, <variable>.stChanMem_ctx.VirAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1595	@
.L1587:
	mov	r4, #0	@ ivtmp.4876,
	mvn	r7, #0	@ tmp196,
	b	.L1592	@
.L1591:
	ldr	ip, [r6, #92]	@ <variable>.pstChanFrmBuf, <variable>.pstChanFrmBuf
	add	r2, ip, r4	@ tmp183, <variable>.pstChanFrmBuf, ivtmp.4876
	strb	r7, [r2, #16]	@ tmp196, <variable>.u8BufferNodeState
.L1589:
	ldr	lr, [r6, #92]	@ <variable>.pstChanFrmBuf, <variable>.pstChanFrmBuf
	add	r4, r4, #20	@ tmp201, ivtmp.4876,
	add	r5, r4, lr	@ D.39488, tmp201, <variable>.pstChanFrmBuf
	ldrb	r3, [r5, #16]	@ zero_extendqisi2	@ D.39489, <variable>.u8BufferNodeState
	cmp	r3, #255	@ D.39489,
	beq	.L1598	@,
	cmp	r3, #1	@ D.39489,
	beq	.L1603	@,
.L1599:
	ldr	r0, [r5, #8]	@, <variable>.stFrameBuffer.PhyAddr
	ldr	r1, [r5, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldr	r2, [r5, #12]	@, <variable>.stFrameBuffer.Length
	bl	MEM_DelMemRecord	@
	cmp	r0, #0	@,
	bne	.L1604	@,
.L1600:
	ldr	r1, [r6, #92]	@ <variable>.pstChanFrmBuf, <variable>.pstChanFrmBuf
	add	r0, r1, r4	@ tmp211, <variable>.pstChanFrmBuf, tmp201
	strb	r7, [r0, #16]	@ tmp196, <variable>.u8BufferNodeState
.L1598:
	add	r4, r4, #20	@ ivtmp.4876, tmp201,
	cmp	r4, #1280	@ ivtmp.4876,
	beq	.L1588	@,
.L1592:
	ldr	r5, [r6, #92]	@ <variable>.pstChanFrmBuf, <variable>.pstChanFrmBuf
	add	r5, r4, r5	@ D.39488, ivtmp.4876, <variable>.pstChanFrmBuf
	ldrb	r3, [r5, #16]	@ zero_extendqisi2	@ D.39489, <variable>.u8BufferNodeState
	cmp	r3, #255	@ D.39489,
	beq	.L1589	@,
	cmp	r3, #1	@ D.39489,
	beq	.L1611	@,
.L1590:
	ldr	r0, [r5, #8]	@, <variable>.stFrameBuffer.PhyAddr
	ldr	r1, [r5, #4]	@, <variable>.stFrameBuffer.VirAddr
	ldr	r2, [r5, #12]	@, <variable>.stFrameBuffer.Length
	bl	MEM_DelMemRecord	@
	cmp	r0, #0	@,
	beq	.L1591	@,
	ldr	r2, [r5, #8]	@, <variable>.stFrameBuffer.PhyAddr
	movw	r1, #:lower16:.LC244	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC244	@,
	bl	dprint_vfmw	@
	b	.L1591	@
.L1604:
	ldr	r2, [r5, #8]	@, <variable>.stFrameBuffer.PhyAddr
	movw	r1, #:lower16:.LC244	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC244	@,
	bl	dprint_vfmw	@
	b	.L1600	@
.L1603:
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC243	@,
	movt	r1, #:upper16:.LC243	@,
	bl	dprint_vfmw	@
	ldr	r0, [r5, #8]	@, <variable>.stFrameBuffer.PhyAddr
	ldr	r1, [r5, #4]	@, <variable>.stFrameBuffer.VirAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1599	@
.L1611:
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC243	@,
	movt	r1, #:upper16:.LC243	@,
	bl	dprint_vfmw	@
	ldr	r0, [r5, #8]	@, <variable>.stFrameBuffer.PhyAddr
	ldr	r1, [r5, #4]	@, <variable>.stFrameBuffer.VirAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1590	@
.L1609:
	ldr	r0, [r6, #40]	@, <variable>.stChanMem_scd.PhyAddr
	ldr	r1, [r6, #36]	@, <variable>.stChanMem_scd.VirAddr
	bl	MEM_DelMemRecord	@
	b	.L1593	@
.L1607:
	ldr	r0, [r6, #40]	@ D.39469, <variable>.stChanMem_scd.PhyAddr
	cmp	r0, #0	@ D.39469,
	beq	.L1585	@,
	ldr	r1, [r6, #36]	@, <variable>.stChanMem_scd.VirAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1586	@
.L1605:
	ldr	r0, [r1, #24]	@ D.39453, <variable>.stChanMem_vdh.PhyAddr
	cmp	r0, #0	@ D.39453,
	beq	.L1583	@,
	ldr	r1, [r1, #20]	@, <variable>.stChanMem_vdh.VirAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1584	@
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
	movw	r2, #:lower16:.LANCHOR0	@ tmp152,
	cmp	r1, #31	@ MaxWidth,
	cmpgt	r7, #31	@, MaxHeight,
	movt	r2, #:upper16:.LANCHOR0	@ tmp152,
	mov	r5, r1	@ MaxWidth, MaxWidth
	mov	r6, r0	@ ChanID, ChanID
	movgt	r1, #0	@, tmp159
	movle	r1, #1	@, tmp159
	ldr	r4, [r2, r0, asl #2]	@ pstChan, s_pstVfmwChan
	mov	sl, r3	@ MemAddr, MemAddr
	ldr	r2, [fp, #4]	@ MemSize, MemSize
	ble	.L1630	@,
	cmp	r3, #0	@ MemAddr,
	cmpne	r2, #0	@, MemSize,
	movne	r8, #0	@, tmp167
	moveq	r8, #1	@, tmp167
	beq	.L1631	@,
	sub	r9, fp, #84	@ tmp169,,
	mov	r1, #36	@,
	str	r2, [fp, #-88]	@,
	mov	r0, r9	@, tmp169
	bl	__memzero	@
	mov	r1, r9	@, tmp169
	mov	r0, r6	@, ChanID
	str	r5, [fp, #-56]	@ MaxWidth, FspInstCfg.s32DispFsWidth
	str	r5, [fp, #-72]	@ MaxWidth, FspInstCfg.s32DecFsWidth
	mov	r3, #1	@,
	str	r7, [fp, #-52]	@ MaxHeight, FspInstCfg.s32DispFsHeight
	strb	r8, [fp, #-84]	@ tmp167, FspInstCfg.s32DispLoopEnable
	strb	r8, [fp, #-82]	@ tmp167, FspInstCfg.s32RprEnable
	str	r7, [fp, #-68]	@ MaxHeight, FspInstCfg.s32DecFsHeight
	strb	r8, [fp, #-79]	@ tmp167, FspInstCfg.s32ExpectedDecFsNum
	strb	r8, [fp, #-77]	@ tmp167, FspInstCfg.s32ExpectedDispFsNum
	strb	r8, [fp, #-76]	@ tmp167, FspInstCfg.s32ExpectedPmvNum
	strb	r3, [fp, #-80]	@, FspInstCfg.s32UserDec
	bl	FSP_ConfigInstance	@
	ldr	r2, [fp, #-88]	@,
	subs	r5, r0, #0	@ D.39383,
	bne	.L1618	@,
	mov	r1, sl	@, MemAddr
	mov	r0, r6	@, ChanID
	sub	r3, fp, #48	@,,
	bl	FSP_PartitionFsMemory	@
	subs	r7, r0, #0	@ Ret,
	bne	.L1632	@,
	movw	r5, #:lower16:.LANCHOR3	@ tmp185,
	movt	r5, #:upper16:.LANCHOR3	@ tmp185,
	mov	r0, r6	@, ChanID
	ldr	r1, .L1634	@,
	bl	FSP_GetInstInfo	@
	ldrb	r1, [r5, #-1347]	@ zero_extendqisi2	@, FspInstInfo.s32DecFsNum
	sxtb	r0, r1	@ D.39393, FspInstInfo.s32DecFsNum
	cmp	r0, #16	@ D.39393,
	movge	r0, #16	@ D.39393,
	str	r0, [r4, #968]	@ D.39393, <variable>.s32UsrdecFrameNum
	cmp	r0, #2	@ D.39393,
	ble	.L1633	@,
	ldr	ip, [r5, #2500]	@ FspInstInfo.s32DecFsSize, FspInstInfo.s32DecFsSize
	add	r0, r4, #900	@, pstChan,
	mov	r1, #64	@,
	str	ip, [r4, #964]	@ FspInstInfo.s32DecFsSize, <variable>.s32UsrdecFrameSize
	bl	__memzero	@
	add	r0, r4, #836	@, pstChan,
	mov	r1, #64	@,
	bl	__memzero	@
	ldr	r5, [r4, #968]	@ D.39392, <variable>.s32UsrdecFrameNum
	cmp	r5, #0	@ D.39392,
	ble	.L1621	@,
	ldr	r3, .L1634	@ ivtmp.4950,
	mov	r2, #1	@ i,
	cmp	r2, r5	@ i, D.39392
	sub	r0, r5, #1	@ tmp204, D.39392,
	and	ip, r0, r2	@ tmp206, tmp204,
	add	r1, r4, #4	@ ivtmp.4953, pstChan,
	ldr	lr, [r3, #20]	@ <variable>.PhyAddr, <variable>.PhyAddr
	ldr	r3, .L1634+4	@ ivtmp.4950,
	str	lr, [r4, #900]	@ <variable>.PhyAddr, <variable>.s32UsrdecFramePhyAddr
	bge	.L1621	@,
	cmp	ip, #0	@ tmp206,
	beq	.L1622	@,
	ldr	lr, [r3, #20]	@ <variable>.PhyAddr, <variable>.PhyAddr
	mov	r2, #2	@ i,
	cmp	r2, r5	@ i, D.39392
	ldr	r3, .L1634+8	@ ivtmp.4950,
	str	lr, [r1, #900]	@ <variable>.PhyAddr, <variable>.s32UsrdecFramePhyAddr
	add	r1, r1, #4	@ ivtmp.4953, ivtmp.4953,
	bge	.L1621	@,
.L1622:
	ldr	r0, [r3, #20]	@ <variable>.PhyAddr, <variable>.PhyAddr
	add	r2, r2, #2	@ i, i,
	add	lr, r1, #4	@ tmp209, ivtmp.4953,
	cmp	r2, r5	@ i, D.39392
	str	r0, [r1, #900]	@ <variable>.PhyAddr, <variable>.s32UsrdecFramePhyAddr
	add	r1, lr, #4	@ ivtmp.4953, tmp209,
	ldr	ip, [r3, #80]	@ <variable>.PhyAddr, <variable>.PhyAddr
	add	r3, r3, #120	@ ivtmp.4950, ivtmp.4950,
	str	ip, [lr, #900]	@ <variable>.PhyAddr, <variable>.s32UsrdecFramePhyAddr
	blt	.L1622	@,
.L1621:
	mov	r0, #0	@ D.39371,
.L1616:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1631:
	mov	r0, r1	@, tmp159
	movw	r1, #:lower16:.LC246	@,
	movt	r1, #:upper16:.LC246	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39371,
	b	.L1616	@
.L1618:
	mov	r0, r8	@, tmp167
	movw	r1, #:lower16:.LC249	@,
	movt	r1, #:upper16:.LC249	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39371,
	b	.L1616	@
.L1632:
	mov	r0, r5	@, D.39383
	movw	r1, #:lower16:.LC247	@,
	movt	r1, #:upper16:.LC247	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39371,
	b	.L1616	@
.L1633:
	mov	r0, r7	@, Ret
	movw	r1, #:lower16:.LC248	@,
	ldr	r2, .L1634+12	@,
	movt	r1, #:upper16:.LC248	@,
	movw	r3, #1349	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39371,
	b	.L1616	@
.L1630:
	mov	r2, r5	@, MaxWidth
	mov	r3, r7	@, MaxHeight
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC245	@,
	movt	r1, #:upper16:.LC245	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39371,
	b	.L1616	@
.L1635:
	.align	2
.L1634:
	.word	.LANCHOR3-1348
	.word	.LANCHOR3-1288
	.word	.LANCHOR3-1228
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
	ldr	r4, [r3, r0, asl #2]	@ D.39195, s_pstVfmwChan
	cmp	r4, #0	@ D.39195,
	beq	.L1638	@,
	add	r4, r4, #140	@ D.39198, D.39195,
	add	r0, r0, r0, asl #1	@, tmp143, ChanID, ChanID,
	add	r3, r3, #296	@ tmp140, tmp138,
	mov	r2, #12	@,
	add	r0, r3, r0, asl #2	@,, tmp140, tmp143,
	mov	r1, r4	@, D.39198
	bl	memcmp	@
	cmp	r0, #0	@,
	bne	.L1640	@,
.L1638:
	mov	r0, r4	@, D.39198
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1640:
	mov	r3, r5	@, ChanID
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC250	@,
	movw	r2, #1059	@,
	movt	r1, #:upper16:.LC250	@,
	mov	r4, r0	@ D.39198,
	bl	dprint_vfmw	@
	b	.L1638	@
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
	beq	.L1665	@,
.L1642:
	mvn	r0, #0	@ D.39072,
.L1663:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L1665:
	movw	r6, #:lower16:.LANCHOR3	@ tmp304,
	movw	r7, #:lower16:saved_command_line	@ tmp302,
	movt	r6, #:upper16:.LANCHOR3	@ tmp304,
	movt	r7, #:upper16:saved_command_line	@ tmp302,
	add	r1, r6, #2496	@, tmp304,
	mov	r2, #1024	@,
	add	r0, r1, #8	@,,
	ldr	r1, [r7, #0]	@, saved_command_line
	str	r8, [fp, #-40]	@ s_VfmwCTrl.s32IsVCTRLOpen, p
	bl	strlcpy	@
	add	r0, r6, #2496	@, tmp304,
	movw	r1, #:lower16:.LC251	@,
	add	r0, r0, #8	@,,
	movt	r1, #:upper16:.LC251	@,
	bl	strstr	@
	cmp	r0, #0	@ tmp173,
	str	r0, [fp, #-40]	@ tmp173, p
	beq	.L1643	@,
	sub	sl, fp, #40	@ p.702,,
	movw	r1, #:lower16:.LC252	@,
	movt	r1, #:upper16:.LC252	@,
	mov	r0, sl	@, p.702
	bl	strsep	@
	subs	r3, r0, #0	@ D.49217,
	beq	.L1648	@,
	mov	r0, sl	@, p.702
	movw	r1, #:lower16:.LC121	@,
	movt	r1, #:upper16:.LC121	@,
	bl	strsep	@
	cmp	r0, #0	@,
	beq	.L1666	@,
	mov	r1, r8	@, s_VfmwCTrl.s32IsVCTRLOpen
	mov	r2, r8	@, tmp1
	bl	simple_strtol	@
	str	r0, [r4, #68]	@ prephitmp.5052, extra_ref
.L1647:
	add	r8, r0, #4992	@ tmp184, prephitmp.5052,
	movw	r2, #10000	@ tmp186,
	add	r3, r8, #8	@ tmp184, tmp184,
	cmp	r3, r2	@ tmp184, tmp186
	bhi	.L1649	@,
	movw	ip, #5000	@ tmp187,
	movw	sl, #:lower16:-5000	@ tmp188,
	cmp	r0, ip	@ prephitmp.5052, tmp187
	movge	r0, ip	@ pretmp.5049, tmp187
	movt	sl, #:upper16:-5000	@ tmp188,
	cmp	r0, sl	@ pretmp.5049, tmp188
	movge	r3, r0	@ prephitmp.5051, pretmp.5049
	movlt	r3, sl	@ prephitmp.5051, tmp188
.L1648:
	str	r3, [r4, #68]	@ prephitmp.5051, extra_ref
.L1646:
	ldr	r1, [r7, #0]	@, saved_command_line
	mov	r2, #1024	@,
	ldr	r0, .L1669	@,
	mov	r8, #0	@ tmp194,
	str	r8, [fp, #-40]	@ tmp194, p
	bl	strlcpy	@
	ldr	r0, .L1669	@,
	movw	r1, #:lower16:.LC254	@,
	movt	r1, #:upper16:.LC254	@,
	bl	strstr	@
	cmp	r0, r8	@ tmp198,
	str	r0, [fp, #-40]	@ tmp198, p
	beq	.L1650	@,
	sub	sl, fp, #40	@ p.713,,
	movw	r1, #:lower16:.LC252	@,
	movt	r1, #:upper16:.LC252	@,
	mov	r0, sl	@, p.713
	bl	strsep	@
	subs	r3, r0, #0	@ D.49237,
	beq	.L1655	@,
	mov	r0, sl	@, p.713
	movw	r1, #:lower16:.LC121	@,
	movt	r1, #:upper16:.LC121	@,
	bl	strsep	@
	cmp	r0, r8	@,
	beq	.L1667	@,
	mov	r1, r8	@, tmp194
	mov	r2, r8	@, tmp1
	bl	simple_strtol	@
	str	r0, [r4, #72]	@ prephitmp.5047, extra_disp
.L1654:
	add	sl, r0, #4992	@ tmp209, prephitmp.5047,
	movw	lr, #10000	@ tmp211,
	add	r8, sl, #8	@ tmp209, tmp209,
	cmp	r8, lr	@ tmp209, tmp211
	bhi	.L1656	@,
	movw	r2, #5000	@ tmp212,
	movw	ip, #:lower16:-5000	@ tmp213,
	cmp	r0, r2	@ prephitmp.5047, tmp212
	movge	r0, r2	@ pretmp.5019, tmp212
	movt	ip, #:upper16:-5000	@ tmp213,
	cmp	r0, ip	@ pretmp.5019, tmp213
	movge	r3, r0	@ prephitmp.5020, pretmp.5019
	movlt	r3, ip	@ prephitmp.5020, tmp213
.L1655:
	str	r3, [r4, #72]	@ prephitmp.5020, extra_disp
.L1653:
	ldr	r8, [r4, #1352]	@ extra_cmd.719, extra_cmd
	mov	lr, #0	@ tmp219,
	movw	sl, #:lower16:.LANCHOR0	@ tmp220,
	str	lr, [fp, #-40]	@ tmp219, p
	cmp	r8, lr	@ extra_cmd.719,
	movt	sl, #:upper16:.LANCHOR0	@ tmp220,
	beq	.L1657	@,
	movw	r0, #:lower16:.LANCHOR2	@ tmp225,
	movt	r0, #:upper16:.LANCHOR2	@ tmp225,
	ubfx	r3, r8, #3, #1	@ tmp238, extra_cmd.719,,
	and	r2, r8, #1	@ tmp223, extra_cmd.719,
	ubfx	ip, r8, #1, #1	@ tmp228, extra_cmd.719,,
	strb	r3, [r6, #3530]	@ tmp238, g_apple_airplay_mirrorinig_flag
	ubfx	r8, r8, #2, #1	@ tmp233, extra_cmd.719,,
	strb	r2, [r6, #3528]	@ tmp223, g_allow_B_before_P
	strb	ip, [r0, #64]	@ tmp228, g_not_direct_8x8_inference_flag
	strb	r8, [r6, #3529]	@ tmp233, g_not_allow_H264FullPictureRepair_flag
.L1658:
	movw	r6, #:lower16:.LANCHOR0	@ tmp271,
	movt	r6, #:upper16:.LANCHOR0	@ tmp271,
	mov	r1, #192	@,
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
	ldr	r0, .L1669+4	@,
	mov	r1, #64	@,
	bl	__memzero	@
	add	r0, r6, #160	@, tmp271,
	bl	OpenDrivers	@
	cmp	r0, #0	@,
	bne	.L1642	@,
	bl	DBG_CreateTracer	@
	mov	r1, #1	@,
	ldr	r0, .L1669+8	@,
	bl	OSAL_InitEvent	@
	add	r0, r6, #148	@, tmp271,
	movw	r1, #:lower16:.LC257	@,
	movw	r2, #:lower16:VFMW_CTRL_thread_proc	@,
	movt	r1, #:upper16:.LC257	@,
	movt	r2, #:upper16:VFMW_CTRL_thread_proc	@,
	bl	OSAL_CreateTask	@
	subs	r4, r0, #0	@ D.39092,
	bne	.L1662	@,
	add	r0, r6, #148	@, tmp271,
	bl	OSAL_WakeupTask	@
	mov	r3, #1	@ tmp297,
	mov	r0, r4	@ D.39072, D.39092
	str	r3, [r6, #104]	@ tmp297, s_VfmwCTrl.s32IsVCTRLOpen
	b	.L1663	@
.L1657:
	ldr	r1, [r7, #0]	@, saved_command_line
	mov	r2, #1024	@,
	ldr	r0, .L1669	@,
	bl	strlcpy	@
	ldr	r0, .L1669	@,
	movw	r1, #:lower16:.LC256	@,
	movt	r1, #:upper16:.LC256	@,
	bl	strstr	@
	cmp	r0, #0	@ tmp243,
	str	r0, [fp, #-40]	@ tmp243, p
	beq	.L1658	@,
	sub	r7, fp, #40	@ p.729,,
	movw	r1, #:lower16:.LC252	@,
	movt	r1, #:upper16:.LC252	@,
	mov	r0, r7	@, p.729
	bl	strsep	@
	cmp	r0, #0	@,
	ldreq	r0, [sl, #1352]	@ prephitmp.5018, extra_cmd
	beq	.L1660	@,
	mov	r0, r7	@, p.729
	movw	r1, #:lower16:.LC121	@,
	movt	r1, #:upper16:.LC121	@,
	bl	strsep	@
	cmp	r0, #0	@,
	beq	.L1668	@,
	mov	r1, r8	@, extra_cmd.719
	mov	r2, r8	@, tmp1
	bl	simple_strtol	@
	str	r0, [sl, #1352]	@ prephitmp.5018, extra_cmd
.L1660:
	movw	ip, #:lower16:.LANCHOR2	@ tmp256,
	movt	ip, #:upper16:.LANCHOR2	@ tmp256,
	ubfx	r3, r0, #3, #1	@ tmp269, prephitmp.5018,,
	and	r2, r0, #1	@ tmp254, prephitmp.5018,
	ubfx	lr, r0, #1, #1	@ tmp259, prephitmp.5018,,
	ubfx	r1, r0, #2, #1	@ tmp264, prephitmp.5018,,
	strb	r3, [r6, #3530]	@ tmp269, g_apple_airplay_mirrorinig_flag
	strb	r2, [r6, #3528]	@ tmp254, g_allow_B_before_P
	strb	lr, [ip, #64]	@ tmp259, g_not_direct_8x8_inference_flag
	strb	r1, [r6, #3529]	@ tmp264, g_not_allow_H264FullPictureRepair_flag
	b	.L1658	@
.L1650:
	ldr	r0, [r4, #72]	@ prephitmp.5047, extra_disp
	b	.L1654	@
.L1643:
	ldr	r0, [r4, #68]	@ prephitmp.5052, extra_ref
	b	.L1647	@
.L1649:
	mov	r2, r0	@, prephitmp.5052
	movw	r1, #:lower16:.LC253	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC253	@,
	bl	dprint_vfmw	@
	ldr	r1, [r4, #68]	@ pretmp.5048, extra_ref
	movw	r3, #5000	@ tmp191,
	movw	r0, #:lower16:-5000	@ tmp192,
	cmp	r1, r3	@ pretmp.5048, tmp191
	movlt	r2, r1	@ prephitmp.5051, pretmp.5048
	movge	r2, r3	@ prephitmp.5051, tmp191
	movt	r0, #:upper16:-5000	@ tmp192,
	cmp	r2, r0	@ prephitmp.5051, tmp192
	movge	r3, r2	@ prephitmp.5051, prephitmp.5051
	movlt	r3, r0	@ prephitmp.5051, tmp192
	b	.L1648	@
.L1656:
	mov	r2, r0	@, prephitmp.5047
	movw	r1, #:lower16:.LC255	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC255	@,
	bl	dprint_vfmw	@
	ldr	r1, [r4, #72]	@ pretmp.5032, extra_disp
	movw	r3, #5000	@ tmp216,
	movw	r0, #:lower16:-5000	@ tmp217,
	cmp	r1, r3	@ pretmp.5032, tmp216
	movlt	r8, r1	@ prephitmp.5020, pretmp.5032
	movge	r8, r3	@ prephitmp.5020, tmp216
	movt	r0, #:upper16:-5000	@ tmp217,
	cmp	r8, r0	@ prephitmp.5020, tmp217
	movge	r3, r8	@ prephitmp.5020, prephitmp.5020
	movlt	r3, r0	@ prephitmp.5020, tmp217
	b	.L1655	@
.L1666:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L1669+12	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #7652	@,
	add	r0, r0, #22	@,,
	bl	dprint_vfmw	@
	b	.L1646	@
.L1667:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L1669+16	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #7687	@,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	b	.L1653	@
.L1668:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L1669+20	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #7733	@,
	add	r0, r0, #22	@,,
	bl	dprint_vfmw	@
	b	.L1658	@
.L1662:
	add	r0, r6, #160	@, tmp271,
	bl	CloseDrivers	@
	mvn	r0, #0	@ D.39072,
	b	.L1663	@
.L1670:
	.align	2
.L1669:
	.word	.LANCHOR3+2504
	.word	.LANCHOR3-1476
	.word	.LANCHOR3+3532
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
	ldr	r0, .L1673	@,
	bl	OSAL_GiveEvent	@
	ldmfd	sp, {fp, sp, pc}	@
.L1674:
	.align	2
.L1673:
	.word	.LANCHOR3+3532
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp245,
	movt	r4, #:upper16:.LANCHOR0	@ tmp245,
	mov	r6, r0	@ pDecParamInfo, pDecParamInfo
	add	r0, r4, #504	@, tmp245,
	movw	r7, #:lower16:.LANCHOR3	@ tmp246,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, .L1723	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r8, [r6, #0]	@ D.42717, <variable>.ChanID
	movt	r7, #:upper16:.LANCHOR3	@ tmp246,
	cmn	r8, #1	@ D.42717,
	beq	.L1714	@,
	cmp	r8, #15	@ D.42717,
	bls	.L1715	@,
.L1686:
	mov	r3, r8	@, D.42717
	ldr	r2, .L1723+4	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC261	@,
	movt	r1, #:upper16:.LC261	@,
	bl	dprint_vfmw	@
	mov	r3, #0	@ tmp192,
	str	r3, [r6, #8]	@ tmp192, <variable>.pDecParam
.L1677:
	ldr	r0, .L1723	@,
	bl	OSAL_SpinUnLockIRQ	@
	ldr	r0, .L1723+8	@,
	bl	OSAL_SpinUnLockIRQ	@
	mvn	r0, #0	@ D.42752,
.L1684:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1715:
	ldr	r3, [r4, r8, asl #2]	@ D.45026, s_pstVfmwChan
	cmp	r3, #0	@ D.45026,
	beq	.L1686	@,
	ldr	r1, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r1, #0	@ <variable>.s32IsOpen,
	beq	.L1686	@,
	ldr	r0, [r3, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	beq	.L1686	@,
	ldr	r2, [r3, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r2, #0	@ <variable>.s32Priority,
	beq	.L1686	@,
	ldr	ip, [r3, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	ip, #19	@ <variable>.eVidStd,
	beq	.L1686	@,
	mov	r0, r8	@, D.42717
	bl	VDMDRV_IsChanDec	@
	cmp	r0, #1	@,
	beq	.L1716	@,
	mov	r0, r8	@, D.42717
	bl	VCTRL_GetDecParam	@
	subs	r5, r0, #0	@ pDecParam.5125,
	beq	.L1717	@,
	ldr	r3, [r4, r8, asl #2]	@ temp.5127, s_pstVfmwChan
	cmp	r3, #0	@ temp.5127,
	beq	.L1718	@,
	str	r8, [fp, #-56]	@ D.42717, DecParamInfo.ChanID
	sub	r0, fp, #56	@,,
	ldr	lr, [r3, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	ip, [r7, #3548]	@ AcceleratorCharacter, AcceleratorCharacter
	str	r5, [fp, #-48]	@ pDecParam.5125, DecParamInfo.pDecParam
	str	lr, [fp, #-52]	@ <variable>.eVidStd, DecParamInfo.VidStd
	blx	ip	@ AcceleratorCharacter
	cmp	r0, #1	@,
	bne	.L1690	@,
	mov	r0, r8	@, D.42717
.L1712:
	ldr	ip, [fp, #-56]	@ DecParamInfo.ChanID, DecParamInfo.ChanID
	mov	r1, #4	@,
	ldr	r3, [fp, #-52]	@ DecParamInfo.VidStd, DecParamInfo.VidStd
	ldr	r2, [fp, #-48]	@ DecParamInfo.pDecParam, DecParamInfo.pDecParam
	str	ip, [r6, #0]	@ DecParamInfo.ChanID, <variable>.ChanID
	str	r3, [r6, #4]	@ DecParamInfo.VidStd, <variable>.VidStd
	str	r2, [r6, #8]	@ DecParamInfo.pDecParam, <variable>.pDecParam
	bl	VDMDRV_SetChanIsDec	@
	ldr	r0, .L1723	@,
	bl	OSAL_SpinUnLockIRQ	@
	ldr	r0, .L1723+8	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, #0	@ D.42752,
	b	.L1684	@
.L1714:
	movw	r5, #:lower16:g_ChanCtx	@ ivtmp.5122,
	movt	r5, #:upper16:g_ChanCtx	@ ivtmp.5122,
	add	r8, r5, #64	@ D.49420, ivtmp.5122,
	sub	r9, fp, #56	@ tmp252,,
	mov	sl, r4	@ tmp251, tmp245
.L1685:
	ldr	r3, [r5, #64]	@ D.42723,
	cmp	r3, #0	@ D.42723,
	blt	.L1677	@,
	cmp	r3, #15	@ D.42723,
	bhi	.L1678	@,
	ldr	r2, [r4, r3, asl #2]	@ D.45017, s_pstVfmwChan
	cmp	r2, #0	@ D.45017,
	beq	.L1678	@,
	ldr	r1, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r1, #0	@ <variable>.s32IsOpen,
	beq	.L1678	@,
	ldr	r0, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	r0, #0	@ <variable>.s32IsRun,
	bne	.L1719	@,
.L1678:
	movw	r1, #:lower16:.LC258	@,
	ldr	r2, .L1723+4	@,
	movt	r1, #:upper16:.LC258	@,
	mov	r0, #1	@,
	bl	dprint_vfmw	@
.L1680:
	add	r5, r5, #4	@ tmp257, ivtmp.5122,
	ldr	r3, [r5, #64]	@ D.42723,
	cmp	r3, #0	@ D.42723,
	blt	.L1677	@,
	cmp	r3, #15	@ D.42723,
	bls	.L1707	@,
.L1697:
	movw	r1, #:lower16:.LC258	@,
	ldr	r2, .L1723+4	@,
	movt	r1, #:upper16:.LC258	@,
	mov	r0, #1	@,
	bl	dprint_vfmw	@
.L1708:
	add	r5, r5, #4	@ ivtmp.5122, tmp257,
	cmp	r5, r8	@ ivtmp.5122, D.49420
	bne	.L1685	@,
	b	.L1677	@
.L1707:
	ldr	r2, [r4, r3, asl #2]	@ D.45017, s_pstVfmwChan
	cmp	r2, #0	@ D.45017,
	beq	.L1697	@,
	ldr	r0, [r2, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r0, #0	@ <variable>.s32IsOpen,
	beq	.L1697	@,
	ldr	lr, [r2, #16]	@ <variable>.s32IsRun, <variable>.s32IsRun
	cmp	lr, #0	@ <variable>.s32IsRun,
	beq	.L1697	@,
	ldr	ip, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	ip, #0	@ <variable>.s32Priority,
	beq	.L1697	@,
	ldr	r2, [r2, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, #19	@ <variable>.eVidStd,
	beq	.L1697	@,
	mov	r0, r3	@, D.42723
	str	r3, [fp, #-64]	@,
	bl	VDMDRV_IsChanDec	@
	ldr	r3, [fp, #-64]	@,
	cmp	r0, #1	@,
	beq	.L1699	@,
	mov	r0, r3	@, D.42723
	bl	VCTRL_GetDecParam	@
	ldr	r3, [fp, #-64]	@,
	subs	r2, r0, #0	@ pDecParam,
	beq	.L1709	@,
	ldr	r1, [sl, r3, asl #2]	@ D.42742, s_pstVfmwChan
	cmp	r1, #0	@ D.42742,
	beq	.L1710	@,
	str	r3, [fp, #-56]	@ D.42723, DecParamInfo.ChanID
	mov	r0, r9	@, tmp252
	ldr	r1, [r1, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	r3, [r7, #3548]	@ AcceleratorCharacter, AcceleratorCharacter
	str	r2, [fp, #-48]	@ pDecParam, DecParamInfo.pDecParam
	str	r1, [fp, #-52]	@ <variable>.eVidStd, DecParamInfo.VidStd
	blx	r3	@ AcceleratorCharacter
	ldr	r3, [fp, #-64]	@,
	cmp	r0, #1	@,
	beq	.L1711	@,
	mov	r0, #0	@,
	str	r0, [r6, #8]	@, <variable>.pDecParam
	b	.L1708	@
.L1719:
	ldr	ip, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	ip, #0	@ <variable>.s32Priority,
	beq	.L1678	@,
	ldr	r2, [r2, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r2, #19	@ <variable>.eVidStd,
	beq	.L1678	@,
	mov	r0, r3	@, D.42723
	str	r3, [fp, #-64]	@,
	bl	VDMDRV_IsChanDec	@
	ldr	r3, [fp, #-64]	@,
	cmp	r0, #1	@,
	beq	.L1720	@,
	mov	r0, r3	@, D.42723
	str	r3, [fp, #-64]	@,
	bl	VCTRL_GetDecParam	@
	ldr	r3, [fp, #-64]	@,
	subs	r2, r0, #0	@ pDecParam,
	beq	.L1721	@,
	ldr	r1, [sl, r3, asl #2]	@ D.42742, s_pstVfmwChan
	cmp	r1, #0	@ D.42742,
	beq	.L1722	@,
	str	r3, [fp, #-56]	@ D.42723, DecParamInfo.ChanID
	mov	r0, r9	@, tmp252
	ldr	lr, [r1, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	ip, [r7, #3548]	@ AcceleratorCharacter, AcceleratorCharacter
	str	r3, [fp, #-64]	@,
	str	r2, [fp, #-48]	@ pDecParam, DecParamInfo.pDecParam
	str	lr, [fp, #-52]	@ <variable>.eVidStd, DecParamInfo.VidStd
	blx	ip	@ AcceleratorCharacter
	ldr	r3, [fp, #-64]	@,
	cmp	r0, #1	@,
	beq	.L1711	@,
	mov	r3, #0	@,
	str	r3, [r6, #8]	@, <variable>.pDecParam
	b	.L1680	@
.L1722:
	movw	r1, #:lower16:.LC55	@,
	movw	r2, #7466	@,
	movt	r1, #:upper16:.LC55	@,
	mov	r0, #1	@,
	bl	dprint_vfmw	@
	b	.L1680	@
.L1710:
	movw	r1, #:lower16:.LC55	@,
	movw	r2, #7466	@,
	movt	r1, #:upper16:.LC55	@,
	mov	r0, #1	@,
	bl	dprint_vfmw	@
	b	.L1708	@
.L1720:
	mov	r2, r3	@, D.42723
	movw	r1, #:lower16:.LC259	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC259	@,
	bl	dprint_vfmw	@
	b	.L1680	@
.L1699:
	mov	r2, r3	@, D.42723
	movw	r1, #:lower16:.LC259	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC259	@,
	bl	dprint_vfmw	@
	b	.L1708	@
.L1690:
	mov	r1, #0	@ tmp232,
	str	r1, [r6, #8]	@ tmp232, <variable>.pDecParam
	b	.L1677	@
.L1711:
	mov	r0, r3	@, D.42723
	b	.L1712	@
.L1721:
	mov	r2, r3	@, D.42723
	movw	r1, #:lower16:.LC260	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC260	@,
	bl	dprint_vfmw	@
	b	.L1680	@
.L1709:
	mov	r2, r3	@, D.42723
	movw	r1, #:lower16:.LC260	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC260	@,
	bl	dprint_vfmw	@
	b	.L1708	@
.L1718:
	mov	r3, r8	@, D.42717
	movw	r2, #7527	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC55	@,
	movt	r1, #:upper16:.LC55	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ tmp214,
	str	r0, [r6, #8]	@ tmp214, <variable>.pDecParam
	b	.L1677	@
.L1716:
	mov	r2, r8	@, D.42717
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC259	@,
	movt	r1, #:upper16:.LC259	@,
	bl	dprint_vfmw	@
	mov	r1, #0	@ tmp199,
	str	r1, [r6, #8]	@ tmp199, <variable>.pDecParam
.L1713:
	ldr	r0, .L1723	@,
	bl	OSAL_SpinUnLockIRQ	@
	add	r0, r4, #504	@, tmp245,
	bl	OSAL_SpinUnLockIRQ	@
	mvn	r0, #0	@ D.42752,
	b	.L1684	@
.L1717:
	bl	VCTRL_ExtraWakeUpThread	@
	mov	r2, r8	@, D.42717
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC260	@,
	movt	r1, #:upper16:.LC260	@,
	bl	dprint_vfmw	@
	str	r5, [r6, #8]	@ pDecParam.5125, <variable>.pDecParam
	b	.L1713	@
.L1724:
	.align	2
.L1723:
	.word	.LANCHOR3-1748
	.word	.LANCHOR1+400
	.word	.LANCHOR0+504
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
	ldr	r3, [r4, #3552]	@ LastEventTime.459, LastEventTime
	cmp	r0, r3	@ CurTime, LastEventTime.459
	mov	r5, r0	@ CurTime,
	strls	r0, [r4, #3552]	@ CurTime, LastEventTime
	bhi	.L1730	@,
.L1727:
	ldr	r0, .L1731	@,
	bl	OSAL_GiveEvent	@
	str	r5, [r4, #3552]	@ CurTime, LastEventTime
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L1730:
	rsb	r3, r3, r0	@ tmp137, LastEventTime.459, CurTime
	cmp	r3, #9	@ tmp137,
	ldmlsfd	sp, {r4, r5, fp, sp, pc}	@
	b	.L1727	@
.L1732:
	.align	2
.L1731:
	.word	.LANCHOR3+3532
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
	bl	VCTRL_StartTask	@
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:.LC262	@,
	movt	r1, #:upper16:.LC262	@,
	cmp	r4, r0	@ EntrTime, CurTime
	rsbls	r2, r4, r0	@ iftmp.451, EntrTime, CurTime
	mvnhi	r4, r4	@ tmp136, EntrTime
	addhi	r2, r4, r0	@ iftmp.451, tmp136, CurTime
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
	bne	.L1754	@,
	mov	r0, #10	@,
	bl	msleep	@
	cmp	r6, #1	@ isScdSleep,
	cmpeq	r5, #1	@, isVdmSleep,
	movne	r8, #1	@ SleepCount,
	beq	.L1754	@,
.L1759:
	mov	r0, #0	@,
	add	sl, r8, #1	@ tmp171, SleepCount,
	bl	SCDDRV_GetSleepStage	@
	cmp	r0, #2	@,
	mov	r0, #0	@,
	moveq	r6, #1	@ isScdSleep,
	bl	VDMDRV_GetSleepStage	@
	cmp	r0, #2	@,
	mov	r0, #10	@,
	moveq	r5, #1	@ isVdmSleep,
	and	r7, r5, r6	@ tmp179, isVdmSleep, isScdSleep
	uxtb	r7, r7	@ tmp180, tmp179
	cmp	r7, #0	@ tmp180,
	bne	.L1754	@,
	cmp	r8, #31	@ SleepCount,
	add	r8, sl, #1	@ SleepCount, tmp171,
	beq	.L1771	@,
	bl	msleep	@
	cmp	r6, #1	@ isScdSleep,
	cmpeq	r5, #1	@, isVdmSleep,
	mov	r0, r7	@, tmp180
	beq	.L1754	@,
	bl	SCDDRV_GetSleepStage	@
	cmp	r0, #2	@,
	mov	r0, r7	@, tmp180
	moveq	r6, #1	@ isScdSleep,
	bl	VDMDRV_GetSleepStage	@
	cmp	r0, #2	@,
	mov	r0, #10	@,
	moveq	r5, #1	@ isVdmSleep,
	and	r3, r5, r6	@ tmp186, isVdmSleep, isScdSleep
	tst	r3, #255	@ tmp186
	bne	.L1754	@,
	bl	msleep	@
	cmp	r6, #1	@ isScdSleep,
	cmpeq	r5, #1	@, isVdmSleep,
	bne	.L1759	@,
.L1754:
	movw	r5, #:lower16:g_vdm_hal_fun_ptr	@ tmp168,
	movt	r5, #:upper16:g_vdm_hal_fun_ptr	@ tmp168,
	ldr	r3, [r5, #12]	@ D.38813, g_vdm_hal_fun_ptr.pfun_SCDDRV_CloseHardware
	cmp	r3, #0	@ D.38813,
	beq	.L1760	@,
	mov	r0, #0	@,
	blx	r3	@ D.38813
	ldr	r3, [r5, #4]	@ D.38818, g_vdm_hal_fun_ptr.pfun_VDMDRV_CloseHardware
	cmp	r3, #0	@ D.38818,
	beq	.L1762	@,
.L1772:
	mov	r0, #0	@,
	blx	r3	@ D.38818
.L1763:
	bl	VCTRL_StopTask	@
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:.LC266	@,
	movt	r1, #:upper16:.LC266	@,
	cmp	r4, r0	@ EntrTime, CurTime.5349
	rsbls	r2, r4, r0	@ iftmp.448, EntrTime, CurTime.5349
	mvnhi	r2, r4	@ tmp166, EntrTime
	addhi	r2, r0, r2	@ iftmp.448, CurTime.5349, tmp166
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1760:
	mov	r0, r3	@, D.38813
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #369	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	ldr	r3, [r5, #4]	@ D.38818, g_vdm_hal_fun_ptr.pfun_VDMDRV_CloseHardware
	cmp	r3, #0	@ D.38818,
	bne	.L1772	@,
.L1762:
	mov	r0, r3	@, D.38818
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #373	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L1763	@
.L1771:
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:.LC263	@,
	mov	r3, r6	@, isScdSleep
	movt	r1, #:upper16:.LC263	@,
	str	r5, [sp, #0]	@ isVdmSleep,
	cmp	r9, r0	@ BeginTime, CurTime
	rsbls	r2, r9, r0	@ iftmp.446, BeginTime, CurTime
	mvnhi	r2, r9	@ tmp151, BeginTime
	addhi	r2, r0, r2	@ iftmp.446, CurTime, tmp151
	mov	r0, #0	@,
	bl	dprint_vfmw	@
	cmp	r6, #1	@ isScdSleep,
	beq	.L1758	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC264	@,
	mov	r2, r0	@,
	movt	r1, #:upper16:.LC264	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@,
	bl	SCDDRV_ForceSleep	@
.L1758:
	cmp	r5, #1	@ isVdmSleep,
	beq	.L1754	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC265	@,
	mov	r2, r0	@,
	movt	r1, #:upper16:.LC265	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@,
	bl	VDMDRV_ForceSleep	@
	b	.L1754	@
	.fnend
	.size	VCTRL_Suspend, .-VCTRL_Suspend
	.align	2
	.global	VCTRL_SetDbgOption
	.type	VCTRL_SetDbgOption, %function
VCTRL_SetDbgOption:
	.fnstart
.LFB1628:
	@ args = 0, pretend = 0, frame = 376
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #388
	sub	sp, sp, #388	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r1, #0	@ p_args
	bne	.L1848	@,
.L1774:
	mvn	r0, #1	@ D.42999,
.L1821:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1848:
	cmp	r0, #516	@ opt,
	ldr	r4, [r1, #0]	@ dat,* p_args
	beq	.L1790	@,
	bhi	.L1810	@,
	cmp	r0, #8	@ opt,
	beq	.L1776	@,
	bhi	.L1811	@,
	cmp	r0, #3	@ opt,
	beq	.L1776	@,
	bhi	.L1812	@,
	cmp	r0, #1	@ opt,
	beq	.L1776	@,
	bls	.L1849	@,
	bic	r5, r4, #-16777216	@ Thr, dat,
	mov	r4, r4, lsr #24	@ ChanID, dat,
	sub	r6, fp, #136	@ tmp483,,
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
	beq	.L1850	@,
.L1776:
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1810:
	cmp	r0, #1280	@ opt,
	beq	.L1800	@,
	bhi	.L1816	@,
	movw	r3, #898	@ tmp196,
	cmp	r0, r3	@ opt, tmp196
	beq	.L1846	@,
	bhi	.L1817	@,
	movw	r1, #769	@ tmp198,
	cmp	r0, r1	@ opt, tmp198
	beq	.L1792	@,
	bhi	.L1818	@,
	cmp	r0, #768	@ opt,
	bne	.L1774	@,
	bl	VCTRL_Suspend	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1800:
	movw	r3, #:lower16:g_TraceCtrl	@ tmp440,
	movt	r3, #:upper16:g_TraceCtrl	@ tmp440,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC305	@,
	str	r4, [r3, #0]	@ dat,
	movt	r1, #:upper16:.LC305	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1850:
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp483
	str	r5, [fp, #-120]	@ Thr, ChanCfg.s32ChanErrThr
	bl	VCTRL_ConfigChan	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1811:
	movw	r3, #257	@ tmp190,
	cmp	r0, r3	@ opt, tmp190
	beq	.L1785	@,
	bhi	.L1813	@,
	cmp	r0, #12	@ opt,
	beq	.L1782	@,
	bhi	.L1814	@,
	cmp	r0, #11	@ opt,
	bne	.L1774	@,
	cmp	r4, #1	@ dat,
	bls	.L1851	@,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC273	@,
	movt	r1, #:upper16:.LC273	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1816:
	movw	r2, #1537	@ tmp204,
	cmp	r0, r2	@ opt, tmp204
	beq	.L1805	@,
	bhi	.L1820	@,
	movw	ip, #1282	@ tmp206,
	cmp	r0, ip	@ opt, tmp206
	beq	.L1802	@,
	bcc	.L1801	@,
	movw	r3, #1283	@ tmp208,
	cmp	r0, r3	@ opt, tmp208
	beq	.L1803	@,
	cmp	r0, #1536	@ opt,
	bne	.L1774	@,
	cmp	r4, #15	@ dat,
	bhi	.L1845	@,
	movw	r0, #:lower16:.LANCHOR0	@ tmp449,
	movt	r0, #:upper16:.LANCHOR0	@ tmp449,
	mov	r5, #1	@ tmp451,
	mov	r2, r4	@, dat
	ldr	ip, [r0, r4, asl #2]	@ tmp450, s_pstVfmwChan
	movw	r1, #:lower16:.LC310	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC310	@,
	str	r5, [ip, #1744]	@ tmp451, <variable>.stSynExtraData.s32ModuleLowlyEnable
	bl	dprint_vfmw	@
	mov	r0, r5	@ D.42999, tmp451
	b	.L1821	@
.L1817:
	cmp	r0, #1024	@ opt,
	beq	.L1797	@,
	bhi	.L1819	@,
	movw	ip, #899	@ tmp201,
	cmp	r0, ip	@ opt, tmp201
	bne	.L1774	@,
	mov	r0, r4	@, dat
	bl	VCTRL_StopChan	@
	mov	r2, r4	@, dat
	movw	r1, #:lower16:.LC299	@,
	movt	r1, #:upper16:.LC299	@,
	mov	r3, r0	@ ret.5411,
	mov	r0, #32	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, dat
	bl	VCTRL_ResetChan	@
	movw	r1, #:lower16:.LC300	@,
	mov	r2, r4	@, dat
	movt	r1, #:upper16:.LC300	@,
	mov	r3, r0	@ ret.5413,
	mov	r0, #32	@,
	bl	dprint_vfmw	@
.L1846:
	mov	r0, r4	@, dat
	bl	VCTRL_StartChan	@
	mov	r2, r4	@, dat
	movw	r1, #:lower16:.LC301	@,
	movt	r1, #:upper16:.LC301	@,
	mov	r3, r0	@ ret.5415,
	mov	r0, #32	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1812:
	cmp	r0, #5	@ opt,
	beq	.L1779	@,
	bcc	.L1778	@,
	cmp	r0, #6	@ opt,
	beq	.L1776	@,
	cmp	r0, #7	@ opt,
	bne	.L1774	@,
	bic	r5, r4, #-16777216	@ Thr, dat,
	mov	r4, r4, lsr #24	@ ChanID, dat,
	sub	r6, fp, #420	@ tmp227,,
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
	bne	.L1776	@,
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp227
	str	r5, [fp, #-400]	@ Thr, ChanCfg.s32ChanStrmOFThr
	bl	VCTRL_ConfigChan	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1813:
	movw	r1, #513	@ tmp192,
	cmp	r0, r1	@ opt, tmp192
	beq	.L1787	@,
	bhi	.L1815	@,
	cmp	r0, #512	@ opt,
	bne	.L1774	@,
	cmp	r4, #15	@ dat,
	bhi	.L1776	@,
	movw	r5, #:lower16:.LANCHOR3	@ tmp245,
	movt	r5, #:upper16:.LANCHOR3	@ tmp245,
	add	r6, r5, r4, asl #2	@, tmp248, tmp245, dat,
	ldr	r7, [r6, #3556]	@ tmp250, vfmw_save_str_file
	cmp	r7, #0	@ tmp250,
	beq	.L1852	@,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC282	@,
	movt	r1, #:upper16:.LC282	@,
	bl	dprint_vfmw	@
	ldr	r0, [r6, #3556]	@, vfmw_save_str_file
	bl	klib_fclose	@
	mov	r0, #0	@ tmp278,
	str	r0, [r6, #3556]	@ tmp278, vfmw_save_str_file
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1820:
	movw	r1, #1539	@ tmp209,
	cmp	r0, r1	@ opt, tmp209
	beq	.L1807	@,
	bcc	.L1806	@,
	movw	r2, #1540	@ tmp211,
	cmp	r0, r2	@ opt, tmp211
	beq	.L1808	@,
	movw	ip, #1541	@ tmp212,
	cmp	r0, ip	@ opt, tmp212
	bne	.L1774	@,
	movw	lr, #:lower16:.LANCHOR3	@ tmp480,
	movt	lr, #:upper16:.LANCHOR3	@ tmp480,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC311	@,
	str	r4, [lr, #3860]	@ dat, g_SCDID
	movt	r1, #:upper16:.LC311	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1845:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC309	@,
	movt	r1, #:upper16:.LC309	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1785:
	movw	r6, #:lower16:g_PrintEnable	@ tmp241,
	movt	r6, #:upper16:g_PrintEnable	@ tmp241,
	mov	r0, r4	@, dat
	mov	r2, #67108864	@ tmp243,
	ldr	r4, [r6, #0]	@ TmpPrintEnable, g_PrintEnable
	mov	r1, #1	@,
	str	r2, [r6, #0]	@ tmp243, g_PrintEnable
	bl	PrintScdRawState	@
	mov	r0, #1	@ D.42999,
	str	r4, [r6, #0]	@ TmpPrintEnable, g_PrintEnable
	b	.L1821	@
.L1805:
	cmp	r4, #15	@ dat,
	bhi	.L1845	@,
	movw	r1, #:lower16:.LANCHOR0	@ tmp454,
	movt	r1, #:upper16:.LANCHOR0	@ tmp454,
	mov	ip, #0	@ tmp456,
	mov	r2, r4	@, dat
	ldr	lr, [r1, r4, asl #2]	@ tmp455, s_pstVfmwChan
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC310	@,
	movt	r1, #:upper16:.LC310	@,
	str	ip, [lr, #1744]	@ tmp456, <variable>.stSynExtraData.s32ModuleLowlyEnable
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1803:
	movw	r3, #:lower16:g_TraceImgPeriod	@ tmp446,
	movt	r3, #:upper16:g_TraceImgPeriod	@ tmp446,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC308	@,
	str	r4, [r3, #0]	@ dat,
	movt	r1, #:upper16:.LC308	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1808:
	add	r4, r4, r4, asl #1	@, tmp474, dat, dat,
	movw	r1, #:lower16:s_SmIIS	@ tmp470,
	movt	r1, #:upper16:s_SmIIS	@ tmp470,
	mov	r2, #0	@ tmp479,
	add	ip, r1, r4, asl #4	@, tmp476, tmp470, tmp474,
	mov	r0, #1	@ D.42999,
	ldr	r3, [ip, #40]	@ <variable>.pSmInstArray, <variable>.pSmInstArray
	str	r2, [r3, #88]	@ tmp479, <variable>.Config.ScdLowdlyEnable
	b	.L1821	@
.L1806:
	movw	r3, #:lower16:g_TunnelLineNumber	@ tmp458,
	movt	r3, #:upper16:g_TunnelLineNumber	@ tmp458,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC310	@,
	str	r4, [r3, #0]	@ dat,
	movt	r1, #:upper16:.LC310	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1807:
	add	r4, r4, r4, asl #1	@, tmp464, dat, dat,
	movw	r0, #:lower16:s_SmIIS	@ tmp460,
	movt	r0, #:upper16:s_SmIIS	@ tmp460,
	mov	r2, #1	@ tmp469,
	add	r1, r0, r4, asl #4	@, tmp466, tmp460, tmp464,
	mov	r0, r2	@ D.42999, tmp469
	ldr	ip, [r1, #40]	@ <variable>.pSmInstArray, <variable>.pSmInstArray
	str	r2, [ip, #88]	@ tmp469, <variable>.Config.ScdLowdlyEnable
	b	.L1821	@
.L1849:
	movw	r3, #:lower16:g_PrintEnable	@ tmp213,
	movt	r3, #:upper16:g_PrintEnable	@ tmp213,
	mov	r0, #1	@ D.42999,
	str	r4, [r3, #0]	@ dat, g_PrintEnable
	b	.L1821	@
.L1790:
#APP
@ 182 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/asm/memory.h" 1
	@ __pv_stub
1:	sub	r5, r4, #-2130706432	@ ptr, dat,
	.pushsection .pv_table,"a"
	.long	1b
	.popsection

@ 0 "" 2
	cmp	r5, #0	@ ptr,
	ldmib	r1, {r7, r8}	@ phole ldm
	beq	.L1847	@,
	sub	r6, fp, #136	@ tmp487,,
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
	beq	.L1838	@,
	movw	lr, #:lower16:g_vdm_hal_fun_ptr	@ tmp420,
	movt	lr, #:upper16:g_vdm_hal_fun_ptr	@ tmp420,
	ldr	ip, [lr, #100]	@ D.43152, g_vdm_hal_fun_ptr.pfun_VDMHAL_Write1DYuv
	cmp	ip, #0	@ D.43152,
	beq	.L1839	@,
	mov	r1, #1	@ tmp421,
	mov	r2, r7	@, D.43142
	str	r1, [sp, #0]	@ tmp421,
	mov	r3, r8	@, D.43144
	mov	r1, r5	@, ptr
	blx	ip	@ D.43152
.L1840:
	mov	r0, r4	@, fp
	bl	klib_fclose	@
	movw	r1, #:lower16:.LC298	@,
	mov	r2, r6	@, tmp487
	movt	r1, #:upper16:.LC298	@,
	mov	r0, #32	@,
	bl	dprint_vfmw	@
.L1837:
	mov	r0, r5	@, ptr
	bl	__arm_iounmap	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1782:
	cmp	r4, #1	@ dat,
	bls	.L1853	@,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC275	@,
	movt	r1, #:upper16:.LC275	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1778:
	and	r5, r4, #3	@ DecOrderOutput, dat,
	mov	r4, r4, lsr #24	@ ChanID, dat,
	sub	r6, fp, #228	@ tmp486,,
	mov	r0, #32	@,
	mov	r2, r4	@, ChanID
	mov	r3, r5	@, DecOrderOutput
	movw	r1, #:lower16:.LC268	@,
	movt	r1, #:upper16:.LC268	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp486
	bl	VCTRL_GetChanCfg	@
	cmp	r0, #0	@,
	bne	.L1776	@,
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp486
	str	r5, [fp, #-200]	@ DecOrderOutput, ChanCfg.s32DecOrderOutput
	bl	VCTRL_ConfigChan	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1792:
	bl	VCTRL_Resume	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1787:
	cmp	r4, #15	@ dat,
	bhi	.L1776	@,
	movw	r5, #:lower16:.LANCHOR3	@ tmp485,
	mov	r6, r4, asl #2	@ tmp484, dat,
	movt	r5, #:upper16:.LANCHOR3	@ tmp485,
	add	r3, r6, r5	@ tmp282, tmp484, tmp485
	ldr	r1, [r3, #3692]	@ tmp284, vfmw_save_seg_file
	cmp	r1, #0	@ tmp284,
	beq	.L1854	@,
	add	r5, r6, r5	@ tmp304, tmp484, tmp485
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC286	@,
	movt	r1, #:upper16:.LC286	@,
	bl	dprint_vfmw	@
	ldr	r0, [r5, #3692]	@, vfmw_save_seg_file
	bl	klib_fclose	@
	mov	r2, #0	@ tmp312,
	mov	r0, #1	@ D.42999,
	str	r2, [r5, #3692]	@ tmp312, vfmw_save_seg_file
	b	.L1821	@
.L1801:
	movw	ip, #:lower16:g_TraceBsPeriod	@ tmp442,
	movt	ip, #:upper16:g_TraceBsPeriod	@ tmp442,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC306	@,
	str	r4, [ip, #0]	@ dat,
	movt	r1, #:upper16:.LC306	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1797:
	movw	r3, #:lower16:.LANCHOR3	@ tmp434,
	movt	r3, #:upper16:.LANCHOR3	@ tmp434,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC302	@,
	str	r4, [r3, #3848]	@ dat, g_SleepTime
	movt	r1, #:upper16:.LC302	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1802:
	movw	lr, #:lower16:g_TraceFramePeriod	@ tmp444,
	movt	lr, #:upper16:g_TraceFramePeriod	@ tmp444,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC307	@,
	str	r4, [lr, #0]	@ dat,
	movt	r1, #:upper16:.LC307	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1779:
	and	r5, r4, #7	@ Mode, dat,
	mov	r4, r4, lsr #24	@ ChanID, dat,
	sub	r6, fp, #320	@ tmp221,,
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
	bne	.L1822	@,
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp221
	str	r5, [fp, #-296]	@ Mode, ChanCfg.s32DecMode
	bl	VCTRL_ConfigChan	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1818:
	cmp	r0, #896	@ opt,
	beq	.L1793	@,
	movw	r2, #897	@ tmp200,
	cmp	r0, r2	@ opt, tmp200
	bne	.L1774	@,
	mov	r0, r4	@, dat
	bl	VCTRL_ResetChan	@
	mov	r2, r4	@, dat
	movw	r1, #:lower16:.LC300	@,
	movt	r1, #:upper16:.LC300	@,
	mov	r3, r0	@ ret.5407,
	mov	r0, #32	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1793:
	mov	r0, r4	@, dat
	bl	VCTRL_StopChan	@
	mov	r2, r4	@, dat
	movw	r1, #:lower16:.LC299	@,
	movt	r1, #:upper16:.LC299	@,
	mov	r3, r0	@ ret,
	mov	r0, #32	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1819:
	movw	r3, #1025	@ tmp202,
	cmp	r0, r3	@ opt, tmp202
	beq	.L1798	@,
	movw	r1, #1026	@ tmp203,
	cmp	r0, r1	@ opt, tmp203
	bne	.L1774	@,
	movw	lr, #:lower16:.LANCHOR3	@ tmp438,
	movt	lr, #:upper16:.LANCHOR3	@ tmp438,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC304	@,
	str	r4, [lr, #3856]	@ dat, g_StopDec
	movt	r1, #:upper16:.LC304	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1798:
	movw	ip, #:lower16:.LANCHOR3	@ tmp436,
	movt	ip, #:upper16:.LANCHOR3	@ tmp436,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC303	@,
	str	r4, [ip, #3852]	@ dat, g_DnrSleepTime
	movt	r1, #:upper16:.LC303	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1815:
	movw	r2, #514	@ tmp194,
	cmp	r0, r2	@ opt, tmp194
	beq	.L1788	@,
	movw	ip, #515	@ tmp195,
	cmp	r0, ip	@ opt, tmp195
	bne	.L1774	@,
#APP
@ 182 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/asm/memory.h" 1
	@ __pv_stub
1:	sub	r5, r4, #-2130706432	@ ptr, dat,
	.pushsection .pv_table,"a"
	.long	1b
	.popsection

@ 0 "" 2
	cmp	r5, #0	@ ptr,
	beq	.L1847	@,
	sub	r6, fp, #136	@ tmp407,,
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
	beq	.L1838	@,
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
	b	.L1837	@
.L1788:
	cmp	r4, #15	@ dat,
	bhi	.L1776	@,
	movw	r5, #:lower16:.LANCHOR3	@ tmp313,
	movt	r5, #:upper16:.LANCHOR3	@ tmp313,
	add	r7, r5, r4, asl #2	@, tmp316, tmp313, dat,
	sub	r8, r7, #1664	@ tmp317, tmp316,
	ldr	r6, [r7, #-1672]	@ tmp318, vfmw_save_yuv_file
	sub	r8, r8, #8	@ tmp317, tmp317,
	cmp	r6, #0	@ tmp318,
	beq	.L1855	@,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC292	@,
	movt	r1, #:upper16:.LC292	@,
	bl	dprint_vfmw	@
	ldr	r0, [r7, #-1672]	@, vfmw_save_yuv_file
	bl	klib_fclose	@
	ldr	r0, [r5, #3840]	@ temp.5395, MemRecord_YUV.PhyAddr
	movw	r3, #:lower16:.LANCHOR0	@ tmp388,
	movw	r1, #:lower16:.LANCHOR2	@ tmp394,
	movt	r3, #:upper16:.LANCHOR0	@ tmp388,
	movt	r1, #:upper16:.LANCHOR2	@ tmp394,
	cmp	r0, #0	@ temp.5395,
	mov	r2, #0	@ tmp387,
	mvn	ip, #0	@ tmp395,
	str	r2, [r7, #-1672]	@ tmp387, vfmw_save_yuv_file
	str	ip, [r1, #68]	@ tmp395, save_yuv_chan_num
	str	r2, [r3, #488]	@ tmp387, pY
	str	r2, [r5, #-1544]	@ tmp387, save_yuv_with_crop
	str	r2, [r3, #492]	@ tmp387, pVl
	str	r2, [r3, #496]	@ tmp387, pUl
	beq	.L1776	@,
	ldr	r1, [r5, #3836]	@, MemRecord_YUV.VirAddr
	bl	MEM_ReleaseMemBlock	@
	ldr	r2, [r5, #3844]	@, MemRecord_YUV.Length
	ldr	r1, [r5, #3836]	@, MemRecord_YUV.VirAddr
	ldr	r0, [r5, #3840]	@, MemRecord_YUV.PhyAddr
	bl	MEM_DelMemRecord	@
	ldr	r0, .L1856	@,
	mov	r1, #16	@,
	bl	__memzero	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1814:
	cmp	r0, #13	@ opt,
	beq	.L1783	@,
	cmp	r0, #256	@ opt,
	bne	.L1774	@,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC278	@,
	movt	r1, #:upper16:.LC278	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, dat
	bl	DBG_PrintTracer	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1783:
	cmp	r4, #16	@ dat,
	bls	.L1825	@,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC276	@,
	movt	r1, #:upper16:.LC276	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1822:
	mov	r2, r4	@, ChanID
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC270	@,
	movt	r1, #:upper16:.LC270	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1825:
	movw	r3, #:lower16:.LANCHOR0	@ tmp238,
	movt	r3, #:upper16:.LANCHOR0	@ tmp238,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC277	@,
	str	r4, [r3, #1348]	@ dat, g_CurProcChan
	movt	r1, #:upper16:.LC277	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1847:
	mov	r2, r4	@, dat
	movw	r1, #:lower16:.LC293	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC293	@,
	bl	dprint_vfmw	@
	b	.L1837	@
.L1851:
	movw	lr, #:lower16:USE_FF_APT_EN	@ tmp231,
	movt	lr, #:upper16:USE_FF_APT_EN	@ tmp231,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC272	@,
	str	r4, [lr, #0]	@ dat,
	movt	r1, #:upper16:.LC272	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1853:
	movw	ip, #:lower16:.LANCHOR0	@ tmp234,
	movt	ip, #:upper16:.LANCHOR0	@ tmp234,
	mov	r2, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC274	@,
	str	r4, [ip, #1356]	@ dat, g_ResetCreateNewSave
	movt	r1, #:upper16:.LC274	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1838:
	mov	r2, r6	@, tmp487
	movw	r1, #:lower16:.LC296	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC296	@,
	bl	dprint_vfmw	@
	b	.L1837	@
.L1839:
	mov	r0, ip	@, D.43152
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #8132	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L1840	@
.L1855:
	ldr	ip, [r5, #3828]	@ save_file_cnt.753, save_file_cnt
	sub	r9, fp, #420	@ str.750,,
	movw	sl, #:lower16:.LANCHOR2	@ tmp323,
	movt	sl, #:upper16:.LANCHOR2	@ tmp323,
	add	lr, ip, #1	@ tmp321, save_file_cnt.753,
	mov	r1, #100	@,
	str	ip, [sp, #0]	@ save_file_cnt.753,
	mov	r3, sl	@, tmp323
	str	lr, [r5, #3828]	@ tmp321, save_file_cnt
	mov	r0, r9	@, str.750
	movw	r2, #:lower16:.LC287	@,
	movt	r2, #:upper16:.LC287	@,
	bl	snprintf	@
	mov	r0, r9	@, str.750
	movw	r1, #578	@,
	mov	r2, r6	@, tmp318
	bl	klib_fopen	@
	cmp	r0, #0	@ D.43086,
	str	r0, [r7, #-1672]	@ D.43086, vfmw_save_yuv_file
	beq	.L1831	@,
	ldr	r0, .L1856	@,
	mov	r1, #16	@,
	bl	__memzero	@
	movw	r0, #:lower16:.LC288	@,
	mov	r1, r6	@, tmp318
	movt	r0, #:upper16:.LC288	@,
	mov	r2, #14155776	@,
	ldr	r3, .L1856	@,
	str	r6, [sp, #0]	@ tmp318,
	bl	MEM_AllocMemBlock	@
	subs	r7, r0, #0	@ D.43099,
	beq	.L1832	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC289	@,
	movt	r1, #:upper16:.LC289	@,
	bl	dprint_vfmw	@
	ldr	r0, [r8, #0]	@, vfmw_save_yuv_file
	bl	klib_fclose	@
	movw	r1, #:lower16:.LANCHOR0	@ tmp350,
	movt	r1, #:upper16:.LANCHOR0	@ tmp350,
	mvn	r0, #0	@ tmp357,
	str	r6, [r5, #-1544]	@ tmp318, save_yuv_with_crop
	str	r0, [sl, #68]	@ tmp357, save_yuv_chan_num
	mov	r0, #1	@ D.42999,
	str	r6, [r8, #0]	@ tmp318, vfmw_save_yuv_file
	str	r6, [r1, #488]	@ tmp318, pY
	str	r6, [r1, #492]	@ tmp318, pVl
	str	r6, [r1, #496]	@ tmp318, pUl
	b	.L1821	@
.L1854:
	ldr	ip, [r5, #3820]	@ save_file_cnt.747, save_file_cnt
	sub	r7, fp, #136	@ str.744,,
	mov	r1, #50	@,
	movw	r2, #:lower16:.LC283	@,
	add	lr, ip, #1	@ tmp287, save_file_cnt.747,
	movt	r2, #:upper16:.LC283	@,
	str	ip, [sp, #0]	@ save_file_cnt.747,
	mov	r0, r7	@, str.744
	str	lr, [r5, #3820]	@ tmp287, save_file_cnt
	movw	r3, #:lower16:.LANCHOR2	@,
	movt	r3, #:upper16:.LANCHOR2	@,
	add	r6, r6, r5	@ tmp293, tmp484, tmp485
	bl	snprintf	@
	mov	r0, r7	@, str.744
	mov	r1, #66	@,
	mov	r2, #0	@,
	bl	klib_fopen	@
	str	r4, [r5, #3824]	@ dat, save_seg_chan_num
	cmp	r0, #0	@ D.43068,
	str	r0, [r6, #3692]	@ D.43068, vfmw_save_seg_file
	beq	.L1829	@,
	mov	r2, r7	@, str.744
	mov	r3, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC284	@,
	movt	r1, #:upper16:.LC284	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1852:
	ldr	ip, [r5, #3684]	@ save_file_cnt.741, save_file_cnt
	sub	r8, fp, #136	@ str.737,,
	mov	r1, #50	@,
	movw	r2, #:lower16:.LC279	@,
	add	lr, ip, #1	@ tmp253, save_file_cnt.741,
	movt	r2, #:upper16:.LC279	@,
	str	ip, [sp, #0]	@ save_file_cnt.741,
	mov	r0, r8	@, str.737
	str	lr, [r5, #3684]	@ tmp253, save_file_cnt
	movw	r3, #:lower16:.LANCHOR2	@,
	movt	r3, #:upper16:.LANCHOR2	@,
	bl	snprintf	@
	mov	r0, r8	@, str.737
	mov	r2, r7	@, tmp250
	mov	r1, #66	@,
	bl	klib_fopen	@
	str	r4, [r5, #3688]	@ dat, save_str_chan_num
	cmp	r0, #0	@ D.43050,
	str	r0, [r6, #3556]	@ D.43050, vfmw_save_str_file
	beq	.L1827	@,
	mov	r2, r8	@, str.737
	mov	r3, r4	@, dat
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC280	@,
	movt	r1, #:upper16:.LC280	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1832:
	ldr	r1, [r5, #3836]	@, MemRecord_YUV.VirAddr
	and	r4, r4, #3	@ save_yuv_with_crop.762, dat,
	ldr	r2, [r5, #3844]	@, MemRecord_YUV.Length
	ldr	r0, [r5, #3840]	@, MemRecord_YUV.PhyAddr
	bl	MEM_AddMemRecord	@
	ldr	lr, [r5, #3836]	@ pY.757, MemRecord_YUV.VirAddr
	movw	ip, #:lower16:.LANCHOR0	@ tmp364,
	movt	ip, #:upper16:.LANCHOR0	@ tmp364,
	str	r4, [r5, #-1544]	@ save_yuv_with_crop.762, save_yuv_with_crop
	add	r6, lr, #11796480	@ tmp367, pY.757,
	mov	r2, r9	@, str.750
	str	r6, [ip, #492]	@ tmp367, pVl
	mov	r3, r7	@, D.43099
	str	r4, [sp, #0]	@ save_yuv_with_crop.762,
	mov	r0, #32	@,
	add	r4, lr, #9437184	@ pUl.759, pY.757,
	movw	r1, #:lower16:.LC290	@,
	str	r4, [ip, #496]	@ pUl.759, pUl
	movt	r1, #:upper16:.LC290	@,
	str	lr, [ip, #488]	@ pY.757, pY
	str	r7, [sl, #68]	@ D.43099, save_yuv_chan_num
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1829:
	mov	r2, r7	@, str.744
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC285	@,
	movt	r1, #:upper16:.LC285	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1831:
	mov	r2, r9	@, str.750
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC291	@,
	movt	r1, #:upper16:.LC291	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1827:
	mov	r2, r8	@, str.737
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC281	@,
	movt	r1, #:upper16:.LC281	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.42999,
	b	.L1821	@
.L1857:
	.align	2
.L1856:
	.word	.LANCHOR3+3832
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
	bhi	.L2029	@,
	movw	r6, #:lower16:.LANCHOR3	@ tmp169,
	movt	r6, #:upper16:.LANCHOR3	@ tmp169,
	add	r5, r6, #3856	@ tmp339, tmp169,
	mov	r1, #256	@,
	add	r5, r5, #8	@ tmp339, tmp339,
	mov	r0, r5	@, tmp339
	bl	__memzero	@
	mov	r2, sp	@,
	bic	ip, r2, #8128	@ tmp172,,
	bic	r1, ip, #63	@ tmp172, tmp172,
	ldr	r0, [r1, #8]	@ <variable>.addr_limit, <variable>.addr_limit
#APP
@ 434 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/asm/uaccess.h" 1
	adds r2, r7, r4; sbcccs r2, r2, r0; movcc r0, #0	@ roksum, buffer, count, flag
@ 0 "" 2
	cmp	r0, #0	@ flag,
	beq	.L2030	@,
	cmp	r4, #0	@ count,
	streqb	r4, [r6, #3864]	@ count, cmd
	bne	.L2031	@,
.L2026:
	movw	r7, #:lower16:.LANCHOR4	@ tmp338,
	movt	r7, #:upper16:.LANCHOR4	@ tmp338,
	mov	r6, r4	@ i, count
	mov	r3, r4	@ j, count
.L1866:
	add	r3, r3, r7	@ tmp201, j, tmp338
	mov	lr, #0	@ tmp203,
	ldr	r0, .L2038	@,
	sub	r1, fp, #32	@,,
	strb	lr, [r3, #-4064]	@ tmp203, str
	bl	str2val	@
	subs	r3, r0, #0	@ D.44026,
	bne	.L1898	@,
	cmp	r4, r6	@ count, i
	bls	.L1874	@,
	add	r2, r5, r6	@ ivtmp.5475, tmp339, i
	mvn	r1, r6	@ tmp362, i
	add	r0, r1, r4	@ tmp361, tmp362, count
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5499, cmd
	and	r0, r0, #1	@ tmp363, tmp361,
	cmp	r1, #32	@ prephitmp.5499,
	beq	.L1956	@,
	movhi	r3, #1	@ j.5480,
	strhib	r1, [r7, #-4064]	@ prephitmp.5499, str
.L1956:
	add	r6, r6, #1	@ i, i,
	add	r2, r2, #1	@ ivtmp.5475, ivtmp.5475,
	cmp	r6, r4	@ i, count
	bcs	.L1874	@,
	cmp	r0, #0	@ tmp363,
	beq	.L1879	@,
	cmp	r3, #0	@ j.5480,
	bne	.L2032	@,
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5499, cmd
	cmp	r1, #32	@ prephitmp.5499,
	beq	.L1960	@,
.L2018:
	cmp	r1, #32	@ prephitmp.5499,
	addhi	r0, r3, r7	@ tmp422, j.5480, tmp338
	addhi	r3, r3, #1	@ j.5480, j.5480,
	strhib	r1, [r0, #-4064]	@ prephitmp.5499, str
	cmp	r3, #0	@ j.5480,
	beq	.L1960	@,
	cmp	r1, #32	@ prephitmp.5499,
	beq	.L1874	@,
.L1960:
	add	r6, r6, #1	@ i, i,
	add	r2, r2, #1	@ ivtmp.5475, ivtmp.5475,
	cmp	r6, r4	@ i, count
	bcc	.L1879	@,
	b	.L1874	@
.L1963:
	ldrb	r2, [r2, #1]	@ zero_extendqisi2	@ prephitmp.5499, cmd
	cmp	r2, #32	@ prephitmp.5499,
	beq	.L1965	@,
.L2020:
	cmp	r2, #32	@ prephitmp.5499,
	addhi	ip, r3, r7	@ tmp426, j.5480, tmp338
	addhi	r3, r3, #1	@ j.5480, j.5480,
	strhib	r2, [ip, #-4064]	@ prephitmp.5499, str
	cmp	r3, #0	@ j.5480,
	beq	.L1965	@,
	cmp	r2, #32	@ prephitmp.5499,
	beq	.L1874	@,
.L1965:
	add	r6, r0, #1	@ i, tmp365,
	add	r2, r1, #1	@ ivtmp.5475, tmp364,
	cmp	r6, r4	@ i, count
	bcs	.L1874	@,
.L1879:
	cmp	r3, #0	@ j.5480,
	ldrneb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5499, cmd
	bne	.L1876	@,
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5499, cmd
	cmp	r1, #32	@ prephitmp.5499,
	beq	.L1877	@,
.L1876:
	cmp	r1, #32	@ prephitmp.5499,
	addhi	r0, r3, r7	@ tmp218, j.5480, tmp338
	addhi	r3, r3, #1	@ j.5480, j.5480,
	strhib	r1, [r0, #-4064]	@ prephitmp.5499, str
	cmp	r3, #0	@ j.5480,
	beq	.L1877	@,
	cmp	r1, #32	@ prephitmp.5499,
	beq	.L1874	@,
.L1877:
	add	r6, r6, #1	@ i, i,
	cmp	r3, #0	@ j.5480,
	add	r1, r2, #1	@ tmp364, ivtmp.5475,
	mov	r0, r6	@ tmp365, i
	beq	.L1963	@,
	ldrb	r2, [r2, #1]	@ zero_extendqisi2	@ prephitmp.5499, cmd
	b	.L2020	@
.L1874:
	add	r2, r3, r7	@ tmp223, j.5480, tmp338
	mov	ip, #0	@ tmp225,
	ldr	r0, .L2038	@,
	sub	r1, fp, #36	@,,
	strb	ip, [r2, #-4064]	@ tmp225, str
	bl	str2val	@
	subs	r3, r0, #0	@ D.44039,
	bne	.L1898	@,
	ldr	r2, [fp, #-32]	@ prephitmp.5447, dat1
	sub	lr, r2, #512	@ tmp235, prephitmp.5447,
	cmp	lr, #255	@ tmp235,
	bhi	.L1881	@,
	cmp	r2, #516	@ prephitmp.5447,
	beq	.L2033	@,
.L1882:
	cmp	r4, r6	@ count, i
	movls	r3, #0	@ j.5483,
	bls	.L1900	@,
	add	r5, r5, r6	@ ivtmp.5463, tmp339, i
	mvn	r3, r6	@ tmp347, i
	add	r1, r3, r4	@ tmp346, tmp347, count
	mov	r3, #0	@ j.5483,
	ldrb	r2, [r5, #0]	@ zero_extendqisi2	@ prephitmp.5488, cmd
	and	r1, r1, #1	@ tmp348, tmp346,
	cmp	r2, #32	@ prephitmp.5488,
	beq	.L1917	@,
	movhi	r3, #1	@ j.5483,
	strhib	r2, [r7, #-4064]	@ prephitmp.5488, str
.L1917:
	add	r6, r6, #1	@ i, i,
	add	r5, r5, #1	@ ivtmp.5463, ivtmp.5463,
	cmp	r4, r6	@ count, i
	bls	.L1900	@,
	cmp	r1, #0	@ tmp348,
	beq	.L1905	@,
	cmp	r3, #0	@ j.5483,
	bne	.L2034	@,
	ldrb	r2, [r5, #0]	@ zero_extendqisi2	@ prephitmp.5488, cmd
	cmp	r2, #32	@ prephitmp.5488,
	beq	.L1921	@,
.L2003:
	cmp	r2, #32	@ prephitmp.5488,
	addhi	r1, r3, r7	@ tmp386, j.5483, tmp338
	addhi	r3, r3, #1	@ j.5483, j.5483,
	strhib	r2, [r1, #-4064]	@ prephitmp.5488, str
	cmp	r3, #0	@ j.5483,
	beq	.L1921	@,
	cmp	r2, #32	@ prephitmp.5488,
	bls	.L1900	@,
.L1921:
	add	r6, r6, #1	@ i, i,
	add	r5, r5, #1	@ ivtmp.5463, ivtmp.5463,
	cmp	r4, r6	@ count, i
	bhi	.L1905	@,
	b	.L1900	@
.L1924:
	ldrb	r2, [r5, #1]	@ zero_extendqisi2	@ prephitmp.5488, cmd
	cmp	r2, #32	@ prephitmp.5488,
	beq	.L1926	@,
.L2005:
	cmp	r2, #32	@ prephitmp.5488,
	addhi	r0, r3, r7	@ tmp390, j.5483, tmp338
	addhi	r3, r3, #1	@ j.5483, j.5483,
	strhib	r2, [r0, #-4064]	@ prephitmp.5488, str
	cmp	r3, #0	@ j.5483,
	beq	.L1926	@,
	cmp	r2, #32	@ prephitmp.5488,
	bls	.L1900	@,
.L1926:
	add	r6, r6, #1	@ i, tmp349,
	add	r5, r1, #1	@ ivtmp.5463, tmp350,
	cmp	r4, r6	@ count, i
	bls	.L1900	@,
.L1905:
	cmp	r3, #0	@ j.5483,
	ldrneb	r2, [r5, #0]	@ zero_extendqisi2	@ prephitmp.5488, cmd
	bne	.L1902	@,
	ldrb	r2, [r5, #0]	@ zero_extendqisi2	@ prephitmp.5488, cmd
	cmp	r2, #32	@ prephitmp.5488,
	beq	.L1903	@,
.L1902:
	cmp	r2, #32	@ prephitmp.5488,
	addhi	r1, r3, r7	@ tmp286, j.5483, tmp338
	addhi	r3, r3, #1	@ j.5483, j.5483,
	strhib	r2, [r1, #-4064]	@ prephitmp.5488, str
	cmp	r3, #0	@ j.5483,
	beq	.L1903	@,
	cmp	r2, #32	@ prephitmp.5488,
	bls	.L1900	@,
.L1903:
	cmp	r3, #0	@ j.5483,
	add	r6, r6, #1	@ tmp349, i,
	add	r1, r5, #1	@ tmp350, ivtmp.5463,
	beq	.L1924	@,
	ldrb	r2, [r5, #1]	@ zero_extendqisi2	@ prephitmp.5488, cmd
	b	.L2005	@
.L1900:
	add	r0, r3, r7	@ tmp291, j.5483, tmp338
	mov	r1, #0	@ tmp293,
	movw	r2, #:lower16:.LANCHOR4	@ tmp289,
	movt	r2, #:upper16:.LANCHOR4	@ tmp289,
	strb	r1, [r0, #-4064]	@ tmp293, str
	ldrb	lr, [r7, #-4064]	@ zero_extendqisi2	@ str, str
	cmp	lr, #47	@ str,
	bne	.L2027	@,
	cmp	r3, #0	@ j.5483,
	beq	.L1907	@,
	sub	r3, r3, #1	@ D.44086, j.5483,
	mov	r0, #32	@,
	add	r5, r3, r2	@ tmp299, D.44086, tmp289
	ldr	r2, .L2038	@,
	ldrb	ip, [r5, #-4064]	@ zero_extendqisi2	@ tmp301, str
	cmp	ip, #47	@ tmp301,
	streqb	r1, [r5, #-4064]	@ tmp293, str
	movw	r5, #:lower16:.LANCHOR2	@ tmp312,
	movt	r5, #:upper16:.LANCHOR2	@ tmp312,
	movw	r1, #:lower16:.LC315	@,
	movt	r1, #:upper16:.LC315	@,
	bl	dprint_vfmw	@
	mov	r2, #64	@,
	mov	r0, r5	@, tmp312
	ldr	r1, .L2038	@,
	bl	strncpy	@
	mov	r2, #0	@ tmp317,
	strb	r2, [r5, #63]	@ tmp317, s_VfmwSavePath
.L2027:
	ldr	r2, [fp, #-32]	@ prephitmp.5447, dat1
.L1881:
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
	mov	r0, r4	@ D.44002, count
.L1860:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2032:
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5499, cmd
	b	.L2018	@
.L2034:
	ldrb	r2, [r5, #0]	@ zero_extendqisi2	@ prephitmp.5488, cmd
	b	.L2003	@
.L2030:
	mov	r1, r7	@, buffer
	mov	r0, r5	@, tmp339
	mov	r2, r4	@, count
	bl	__copy_from_user	@
	subs	r3, r0, #0	@ count.5495,
	bne	.L1862	@,
	add	r6, r4, r6	@ tmp184, count, tmp169
	cmp	r4, #0	@ count,
	strb	r3, [r6, #3864]	@ count.5495, cmd
	beq	.L2026	@,
	ldrb	r2, [r5, #0]	@ zero_extendqisi2	@ prephitmp.5449, cmd
	sub	r7, r4, #1	@ tmp366, count,
	and	r1, r7, #1	@ tmp368, tmp366,
	movw	r7, #:lower16:.LANCHOR4	@ tmp338,
	cmp	r2, #32	@ prephitmp.5449,
	movt	r7, #:upper16:.LANCHOR4	@ tmp338,
	beq	.L1969	@,
	movhi	r3, #1	@ j,
	strhib	r2, [r7, #-4064]	@ prephitmp.5449, str
.L1969:
	mov	r6, #1	@ i,
	cmp	r4, r6	@ count, i
	bls	.L1866	@,
	cmp	r1, #0	@ tmp368,
	beq	.L1871	@,
	cmp	r3, #0	@ j,
	bne	.L2035	@,
	ldrb	r2, [r5, r6]	@ zero_extendqisi2	@ prephitmp.5449, cmd
	cmp	r2, #32	@ prephitmp.5449,
	beq	.L1973	@,
.L2023:
	cmp	r2, #32	@ prephitmp.5449,
	addhi	r1, r3, r7	@ tmp434, j, tmp338
	addhi	r3, r3, #1	@ j, j,
	strhib	r2, [r1, #-4064]	@ prephitmp.5449, str
	cmp	r3, #0	@ j,
	beq	.L1973	@,
	cmp	r2, #32	@ prephitmp.5449,
	beq	.L1866	@,
.L1973:
	add	r6, r6, #1	@ i, i,
	cmp	r4, r6	@ count, i
	bhi	.L1871	@,
	b	.L1866	@
.L1976:
	ldrb	r2, [r5, r6]	@ zero_extendqisi2	@ prephitmp.5449, cmd
	cmp	r2, #32	@ prephitmp.5449,
	beq	.L1978	@,
.L2025:
	cmp	r2, #32	@ prephitmp.5449,
	addhi	r0, r3, r7	@ tmp438, j, tmp338
	addhi	r3, r3, #1	@ j, j,
	strhib	r2, [r0, #-4064]	@ prephitmp.5449, str
	cmp	r3, #0	@ j,
	beq	.L1978	@,
	cmp	r2, #32	@ prephitmp.5449,
	beq	.L1866	@,
.L1978:
	add	r6, r1, #1	@ i, tmp369,
	cmp	r4, r6	@ count, i
	bls	.L1866	@,
.L1871:
	cmp	r3, #0	@ j,
	ldrneb	r2, [r5, r6]	@ zero_extendqisi2	@ prephitmp.5449, cmd
	bne	.L1868	@,
	ldrb	r2, [r5, r6]	@ zero_extendqisi2	@ prephitmp.5449, cmd
	cmp	r2, #32	@ prephitmp.5449,
	beq	.L1869	@,
.L1868:
	cmp	r2, #32	@ prephitmp.5449,
	addhi	r1, r3, r7	@ tmp196, j, tmp338
	addhi	r3, r3, #1	@ j, j,
	strhib	r2, [r1, #-4064]	@ prephitmp.5449, str
	cmp	r3, #0	@ j,
	beq	.L1869	@,
	cmp	r2, #32	@ prephitmp.5449,
	beq	.L1866	@,
.L1869:
	add	r6, r6, #1	@ i, i,
	cmp	r3, #0	@ j,
	mov	r1, r6	@ tmp369, i
	beq	.L1976	@,
	ldrb	r2, [r5, r6]	@ zero_extendqisi2	@ prephitmp.5449, cmd
	b	.L2025	@
.L2035:
	ldrb	r2, [r5, r6]	@ zero_extendqisi2	@ prephitmp.5449, cmd
	b	.L2023	@
.L2031:
	mov	r0, r5	@, tmp339
	mov	r1, r4	@, count
	bl	__memzero	@
.L1862:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC313	@,
	movt	r1, #:upper16:.LC313	@,
	bl	dprint_vfmw	@
	mvn	r0, #4	@ D.44002,
	b	.L1860	@
.L2033:
	cmp	r4, r6	@ count, i
	bls	.L1884	@,
	add	r2, r5, r6	@ ivtmp.5471, tmp339, i
	mvn	r1, r6	@ tmp357, i
	add	r0, r1, r4	@ tmp356, tmp357, count
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5485, cmd
	and	r0, r0, #1	@ tmp358, tmp356,
	cmp	r1, #32	@ prephitmp.5485,
	beq	.L1943	@,
	movhi	r3, #1	@ j.5481,
	strhib	r1, [r7, #-4064]	@ prephitmp.5485, str
.L1943:
	add	r6, r6, #1	@ i, i,
	add	r2, r2, #1	@ ivtmp.5471, ivtmp.5471,
	cmp	r4, r6	@ count, i
	bls	.L1884	@,
	cmp	r0, #0	@ tmp358,
	beq	.L1889	@,
	cmp	r3, #0	@ j.5481,
	bne	.L2036	@,
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5485, cmd
	cmp	r1, #32	@ prephitmp.5485,
	beq	.L1947	@,
.L2013:
	cmp	r1, #32	@ prephitmp.5485,
	addhi	r0, r3, r7	@ tmp410, j.5481, tmp338
	addhi	r3, r3, #1	@ j.5481, j.5481,
	strhib	r1, [r0, #-4064]	@ prephitmp.5485, str
	cmp	r3, #0	@ j.5481,
	beq	.L1947	@,
	cmp	r1, #32	@ prephitmp.5485,
	bls	.L1884	@,
.L1947:
	add	r6, r6, #1	@ i, i,
	add	r2, r2, #1	@ ivtmp.5471, ivtmp.5471,
	cmp	r4, r6	@ count, i
	bhi	.L1889	@,
	b	.L1884	@
.L1950:
	ldrb	r2, [r2, #1]	@ zero_extendqisi2	@ prephitmp.5485, cmd
	cmp	r2, #32	@ prephitmp.5485,
	beq	.L1952	@,
.L2015:
	cmp	r2, #32	@ prephitmp.5485,
	addhi	ip, r3, r7	@ tmp414, j.5481, tmp338
	addhi	r3, r3, #1	@ j.5481, j.5481,
	strhib	r2, [ip, #-4064]	@ prephitmp.5485, str
	cmp	r3, #0	@ j.5481,
	beq	.L1952	@,
	cmp	r2, #32	@ prephitmp.5485,
	bls	.L1884	@,
.L1952:
	add	r6, r0, #1	@ i, tmp359,
	add	r2, r1, #1	@ ivtmp.5471, tmp360,
	cmp	r4, r6	@ count, i
	bls	.L1884	@,
.L1889:
	cmp	r3, #0	@ j.5481,
	ldrneb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5485, cmd
	bne	.L1886	@,
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5485, cmd
	cmp	r1, #32	@ prephitmp.5485,
	beq	.L1887	@,
.L1886:
	cmp	r1, #32	@ prephitmp.5485,
	addhi	r0, r3, r7	@ tmp242, j.5481, tmp338
	addhi	r3, r3, #1	@ j.5481, j.5481,
	strhib	r1, [r0, #-4064]	@ prephitmp.5485, str
	cmp	r3, #0	@ j.5481,
	beq	.L1887	@,
	cmp	r1, #32	@ prephitmp.5485,
	bls	.L1884	@,
.L1887:
	add	r6, r6, #1	@ i, i,
	cmp	r3, #0	@ j.5481,
	add	r1, r2, #1	@ tmp360, ivtmp.5471,
	mov	r0, r6	@ tmp359, i
	beq	.L1950	@,
	ldrb	r2, [r2, #1]	@ zero_extendqisi2	@ prephitmp.5485, cmd
	b	.L2015	@
.L1884:
	add	r3, r3, r7	@ tmp247, j.5481, tmp338
	mov	ip, #0	@ tmp249,
	ldr	r0, .L2038	@,
	sub	r1, fp, #40	@,,
	strb	ip, [r3, #-4064]	@ tmp249, str
	bl	str2val	@
	subs	r3, r0, #0	@ D.44057,
	bne	.L1898	@,
	cmp	r4, r6	@ count, i
	bls	.L1892	@,
	add	r2, r5, r6	@ ivtmp.5467, tmp339, i
	mvn	r0, r6	@ tmp352, i
	add	lr, r0, r4	@ tmp351, tmp352, count
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5498, cmd
	and	r0, lr, #1	@ tmp353, tmp351,
	cmp	r1, #32	@ prephitmp.5498,
	beq	.L1930	@,
	movhi	r3, #1	@ j.5482,
	strhib	r1, [r7, #-4064]	@ prephitmp.5498, str
.L1930:
	add	r6, r6, #1	@ i, i,
	add	r2, r2, #1	@ ivtmp.5467, ivtmp.5467,
	cmp	r4, r6	@ count, i
	bls	.L1892	@,
	cmp	r0, #0	@ tmp353,
	beq	.L1897	@,
	cmp	r3, #0	@ j.5482,
	bne	.L2037	@,
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5498, cmd
	cmp	r1, #32	@ prephitmp.5498,
	beq	.L1934	@,
.L2008:
	cmp	r1, #32	@ prephitmp.5498,
	addhi	r0, r3, r7	@ tmp398, j.5482, tmp338
	addhi	r3, r3, #1	@ j.5482, j.5482,
	strhib	r1, [r0, #-4064]	@ prephitmp.5498, str
	cmp	r3, #0	@ j.5482,
	beq	.L1934	@,
	cmp	r1, #32	@ prephitmp.5498,
	bls	.L1892	@,
.L1934:
	add	r6, r6, #1	@ i, i,
	add	r2, r2, #1	@ ivtmp.5467, ivtmp.5467,
	cmp	r4, r6	@ count, i
	bhi	.L1897	@,
	b	.L1892	@
.L1937:
	ldrb	r2, [r2, #1]	@ zero_extendqisi2	@ prephitmp.5498, cmd
	cmp	r2, #32	@ prephitmp.5498,
	beq	.L1939	@,
.L2010:
	cmp	r2, #32	@ prephitmp.5498,
	addhi	ip, r3, r7	@ tmp402, j.5482, tmp338
	addhi	r3, r3, #1	@ j.5482, j.5482,
	strhib	r2, [ip, #-4064]	@ prephitmp.5498, str
	cmp	r3, #0	@ j.5482,
	beq	.L1939	@,
	cmp	r2, #32	@ prephitmp.5498,
	bls	.L1892	@,
.L1939:
	add	r6, r0, #1	@ i, tmp354,
	add	r2, r1, #1	@ ivtmp.5467, tmp355,
	cmp	r4, r6	@ count, i
	bls	.L1892	@,
.L1897:
	cmp	r3, #0	@ j.5482,
	ldrneb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5498, cmd
	bne	.L1894	@,
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5498, cmd
	cmp	r1, #32	@ prephitmp.5498,
	beq	.L1895	@,
.L1894:
	cmp	r1, #32	@ prephitmp.5498,
	addhi	r0, r3, r7	@ tmp264, j.5482, tmp338
	addhi	r3, r3, #1	@ j.5482, j.5482,
	strhib	r1, [r0, #-4064]	@ prephitmp.5498, str
	cmp	r3, #0	@ j.5482,
	beq	.L1895	@,
	cmp	r1, #32	@ prephitmp.5498,
	bls	.L1892	@,
.L1895:
	add	r6, r6, #1	@ i, i,
	cmp	r3, #0	@ j.5482,
	add	r1, r2, #1	@ tmp355, ivtmp.5467,
	mov	r0, r6	@ tmp354, i
	beq	.L1937	@,
	ldrb	r2, [r2, #1]	@ zero_extendqisi2	@ prephitmp.5498, cmd
	b	.L2010	@
.L1892:
	add	ip, r3, r7	@ tmp269, j.5482, tmp338
	mov	r2, #0	@ tmp271,
	ldr	r0, .L2038	@,
	sub	r1, fp, #44	@,,
	strb	r2, [ip, #-4064]	@ tmp271, str
	bl	str2val	@
	cmp	r0, #0	@,
	beq	.L1882	@,
.L1898:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC314	@,
	ldr	r2, .L2038+4	@,
	movt	r1, #:upper16:.LC314	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.44002,
	b	.L1860	@
.L2036:
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5485, cmd
	b	.L2013	@
.L2037:
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@ prephitmp.5498, cmd
	b	.L2008	@
.L2029:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC312	@,
	movt	r1, #:upper16:.LC312	@,
	bl	dprint_vfmw	@
	mvn	r0, #4	@ D.44002,
	b	.L1860	@
.L1907:
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC316	@,
	ldr	r2, .L2038+8	@,
	movt	r1, #:upper16:.LC316	@,
	movw	r3, #9625	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.44002,
	b	.L1860	@
.L2039:
	.align	2
.L2038:
	.word	.LANCHOR4-4064
	.word	.LANCHOR3+3864
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r5, #:lower16:.LANCHOR0	@ tmp197,
	movt	r5, #:upper16:.LANCHOR0	@ tmp197,
	mov	r4, r0	@ ChanID, ChanID
	ldr	r3, [r5, r0, asl #2]	@ D.40759, s_pstVfmwChan
	cmp	r3, #0	@ D.40759,
	beq	.L2050	@,
	ldr	r7, [r3, #16]	@ ChanIsRun, <variable>.s32IsRun
	bl	VCTRL_StopChan	@
	ldr	r3, [r5, r4, asl #2]	@ tmp145, s_pstVfmwChan
	mov	r6, #0	@ tmp146,
	add	r1, r5, #1440	@ tmp151, tmp197,
	mov	r0, #300	@ tmp154,
	add	r2, r1, #4	@ tmp151, tmp151,
	mov	r1, r0	@, tmp154
	str	r6, [r3, #828]	@ tmp146, <variable>.s32CountNoDecparamFlag
	ldr	ip, [r5, r4, asl #2]	@ tmp148, s_pstVfmwChan
	mla	r0, r0, r4, r2	@, tmp154, ChanID, tmp151
	str	r6, [ip, #832]	@ tmp146, <variable>.u32NoDecparamStartTime
	bl	__memzero	@
	mov	r1, r6	@, tmp146
	mov	r0, r4	@, ChanID
	bl	VCTRL_SetSendStreamAgainFlag	@
	mov	r1, #896	@,
	movw	r0, #:lower16:g_stLowdlyInfo	@,
	movt	r0, #:upper16:g_stLowdlyInfo	@,
	bl	__memzero	@
	ldr	r1, [r5, r4, asl #2]	@ tmp158, s_pstVfmwChan
	mov	r0, r4	@, ChanID
	str	r6, [r1, #1736]	@ tmp146, <variable>.stSynExtraData.s32KeepSPSPPS
	bl	InitSyntaxCtx	@
	ldr	r2, [r5, r4, asl #2]	@ tmp162, s_pstVfmwChan
	mov	r1, #416	@,
	add	r3, r2, #1168	@, tmp162,
	add	r0, r3, #8	@,,
	bl	__memzero	@
	ldr	ip, [r5, r4, asl #2]	@ tmp165, s_pstVfmwChan
	movw	r0, #1096	@ tmp166,
	mvn	r3, #0	@,
	mvn	r2, #0	@ tmp167,
	mov	r1, #1104	@ tmp170,
	strd	r2, [ip, r0]	@ tmp167, tmp165, tmp166
	ldr	r0, [r5, r4, asl #2]	@ tmp169, s_pstVfmwChan
	strd	r2, [r0, r1]	@ tmp167, tmp169, tmp170
	mov	r0, r4	@, ChanID
	ldr	ip, [r5, r4, asl #2]	@ tmp173, s_pstVfmwChan
	str	r6, [ip, #1592]	@ tmp146, <variable>.stSynExtraData.s32NewPicSegDetector
	ldr	r1, [r5, r4, asl #2]	@ temp.5532, s_pstVfmwChan
	ldr	r2, [r1, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r2, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	streq	r6, [r1, #1924]	@ tmp146, <variable>.stSynExtraData.s32WaitFsFlag
	bl	FSP_SwitchNotify	@
	ldr	r0, [r5, r4, asl #2]	@ tmp179, s_pstVfmwChan
	ldr	r3, [r0, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #18	@ <variable>.eVidStd,
	beq	.L2044	@,
	mov	r0, r4	@, ChanID
	bl	FSP_ResetInstance	@
.L2045:
	mov	r0, r4	@, ChanID
	bl	InitUsdPool	@
	mov	r0, r4	@, ChanID
	bl	SM_Reset	@
	ldr	ip, [r5, #1356]	@ g_ResetCreateNewSave, g_ResetCreateNewSave
	cmp	ip, #0	@ g_ResetCreateNewSave,
	beq	.L2046	@,
	movw	r5, #:lower16:.LANCHOR3	@ tmp183,
	movt	r5, #:upper16:.LANCHOR3	@ tmp183,
	add	r5, r5, r4, asl #2	@, tmp186, tmp183, ChanID,
	str	r4, [fp, #-32]	@ ChanID, data
	ldr	lr, [r5, #3556]	@ tmp188, vfmw_save_str_file
	cmp	lr, #0	@ tmp188,
	beq	.L2047	@,
	sub	r6, fp, #32	@ data.565,,
	mov	r0, #512	@,
	mov	r1, r6	@, data.565
	bl	VCTRL_SetDbgOption	@
	ldr	r0, [r5, #3556]	@ tmp194, vfmw_save_str_file
	cmp	r0, #0	@ tmp194,
	beq	.L2047	@,
	mov	r1, r6	@, data.565
	mov	r0, #512	@,
	bl	VCTRL_SetDbgOption	@
.L2047:
	movw	r1, #:lower16:.LC318	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC318	@,
	bl	dprint_vfmw	@
.L2046:
	cmp	r7, #0	@ ChanIsRun,
	bne	.L2051	@,
.L2048:
	mov	r0, r4	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	mov	r0, #0	@ D.40763,
.L2042:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2051:
	mov	r0, r4	@, ChanID
	bl	VCTRL_StartChan	@
	b	.L2048	@
.L2044:
	mov	r0, r4	@, ChanID
	bl	FSP_EmptyInstance	@
	b	.L2045	@
.L2050:
	mov	r0, r3	@, D.40759
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #3970	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40763,
	b	.L2042	@
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
	bhi	.L2151	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp666,
	movt	r4, #:upper16:.LANCHOR0	@ tmp666,
	ldr	r3, [r4, r0, asl #2]	@ D.40353, s_pstVfmwChan
	cmp	r3, #0	@ D.40353,
	beq	.L2152	@,
	ldr	r3, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r3, #1	@ <variable>.s32IsOpen,
	bne	.L2153	@,
	bl	VCTRL_CheckChanWH	@
	cmp	r0, #0	@,
	bne	.L2154	@,
	movw	r6, #:lower16:.LANCHOR4	@ tmp668,
	movt	r6, #:upper16:.LANCHOR4	@ tmp668,
	sub	r0, r6, #3808	@, tmp668,
	bl	GetVdecCapability	@
	ldr	r2, [r8, #0]	@ prephitmp.5554, <variable>.eVidStd
	sub	r3, r6, #3808	@ ivtmp.5581, tmp668,
	sub	ip, r6, #3680	@ D.49904, tmp668,
	b	.L2060	@
.L2058:
	cmp	r1, r2	@ D.40364, prephitmp.5554
	beq	.L2059	@,
	ldr	r1, [r0, #20]	@ D.40364, Capability.SupportedStd
	cmp	r1, #18	@ D.40364,
	bhi	.L2145	@,
	cmp	r1, r2	@ D.40364, prephitmp.5554
	beq	.L2059	@,
	cmp	r3, ip	@ ivtmp.5581, D.49904
	beq	.L2059	@,
.L2060:
	ldr	r1, [r3, #20]	@ D.40364, Capability.SupportedStd
	add	r0, r3, #4	@ tmp672, ivtmp.5581,
	add	r3, r0, #4	@ ivtmp.5581, tmp672,
	cmp	r1, #18	@ D.40364,
	bls	.L2058	@,
.L2145:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC320	@,
	movt	r1, #:upper16:.LC320	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
.L2054:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L2059:
	cmp	r2, #8	@ prephitmp.5554,
	beq	.L2155	@,
.L2061:
	cmp	r2, #9	@ prephitmp.5554,
	beq	.L2156	@,
.L2063:
	mov	r0, r5	@, ChanID
	mov	r1, r8	@, pstCfg
	bl	VCTRL_CmpConfigParameter	@
	subs	r7, r0, #0	@ D.40380,
	beq	.L2157	@,
	ldr	r3, [r8, #0]	@ D.40368, <variable>.eVidStd
	sub	r2, r3, #10	@ tmp234, D.40368,
	cmp	r2, #2	@ tmp234,
	bhi	.L2065	@,
	ldr	r7, [r4, #500]	@ g_VdmCharacter, g_VdmCharacter
	tst	r7, #1	@ g_VdmCharacter,
	beq	.L2066	@,
.L2067:
	cmp	r3, #14	@ D.40368,
	movne	r0, #0	@, prephitmp.5556
	moveq	r0, #1	@, prephitmp.5556
.L2068:
	ldr	r7, [r4, r5, asl #2]	@ prephitmp.5558, s_pstVfmwChan
	movw	r3, #:lower16:.LANCHOR0	@ tmp240,
	movt	r3, #:upper16:.LANCHOR0	@ tmp240,
	ldr	r2, [r7, #48]	@ D.40400, <variable>.stChanCfg.eVidStd
	sub	r9, r2, #10	@ tmp241, D.40400,
	cmp	r9, #2	@ tmp241,
	bhi	.L2069	@,
	ldr	sl, [r3, #500]	@ g_VdmCharacter, g_VdmCharacter
	tst	sl, #1	@ g_VdmCharacter,
	beq	.L2070	@,
.L2071:
	cmp	r2, #14	@ D.40400,
	movne	r2, #0	@, prephitmp.5659
	moveq	r2, #1	@, prephitmp.5659
.L2072:
	cmp	r2, r0	@ prephitmp.5659, prephitmp.5556
	beq	.L2073	@,
	ldr	ip, [r7, #188]	@ <variable>.s32OneChanMem, <variable>.s32OneChanMem
	cmp	ip, #0	@ <variable>.s32OneChanMem,
	bne	.L2074	@,
	ldr	r0, .L2168	@,
	bl	OSAL_SpinUnLockIRQ	@
	ldr	r3, [r7, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	cmp	r3, #0	@ <variable>.stChanMem_scd.Length,
	bne	.L2158	@,
.L2075:
	ldr	r0, [r7, #212]	@, <variable>.stChanMem_vdh.VirAddr
	bl	KernelMunmap	@
	ldr	r3, [r8, #0]	@ temp.5594, <variable>.eVidStd
	sub	r0, r3, #10	@ tmp256, temp.5594,
	cmp	r0, #2	@ tmp256,
	bhi	.L2076	@,
	ldr	lr, [r4, #500]	@ g_VdmCharacter, g_VdmCharacter
	tst	lr, #1	@ g_VdmCharacter,
	bne	.L2078	@,
.L2077:
	ldr	r1, [r7, #220]	@, <variable>.stChanMem_vdh.Length
	mov	sl, #1	@ tmp262,
	ldr	r0, [r7, #216]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	KernelMmapCache	@
	ldr	r1, [r7, #236]	@ temp.5605, <variable>.stChanMem_scd.Length
	strb	sl, [r7, #208]	@ tmp262, <variable>.stChanMem_vdh.IsCached
	cmp	r1, #0	@ temp.5605,
	mov	r9, r0	@ pVir_vdh,
	bne	.L2159	@,
.L2079:
	mov	r1, #0	@,
	str	r1, [fp, #-224]	@, %sfp
.L2080:
	movw	sl, #:lower16:.LANCHOR0	@ tmp274,
	movt	sl, #:upper16:.LANCHOR0	@ tmp274,
	add	r0, sl, #504	@, tmp274,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, [r4, r5, asl #2]	@ tmp277, s_pstVfmwChan
	cmp	r0, #0	@ tmp277,
	beq	.L2160	@,
	cmp	r9, #0	@ pVir_vdh,
	beq	.L2082	@,
	ldr	r3, [fp, #-224]	@, %sfp
	ldr	ip, [r7, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	rsbs	r2, r3, #1	@,
	movcc	r2, #0	@
	cmp	ip, #0	@ <variable>.stChanMem_scd.Length,
	moveq	r2, #0	@,,
	cmp	r2, #0	@ tmp289,
	mov	r3, r2	@ tmp289,
	bne	.L2082	@,
	ldr	r0, [r7, #216]	@, <variable>.stChanMem_vdh.PhyAddr
	ldr	r1, [r7, #212]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r2, [r7, #220]	@, <variable>.stChanMem_vdh.Length
	str	r3, [fp, #-232]	@,
	bl	MEM_DelMemRecord	@
	ldr	r3, [fp, #-232]	@,
	cmp	r0, #0	@
	str	r0, [fp, #-228]	@, %sfp
	bne	.L2161	@,
	str	r9, [r7, #212]	@ pVir_vdh, <variable>.stChanMem_vdh.VirAddr
	mov	r1, r9	@, pVir_vdh
	ldr	r0, [r7, #216]	@, <variable>.stChanMem_vdh.PhyAddr
	ldr	r2, [r7, #220]	@, <variable>.stChanMem_vdh.Length
	bl	MEM_AddMemRecord	@
	subs	r9, r0, #0	@ D.40455,
	bne	.L2162	@,
	ldr	r2, [r7, #236]	@ temp.5623, <variable>.stChanMem_scd.Length
	cmp	r2, #0	@ temp.5623,
	bne	.L2086	@,
.L2146:
	ldr	r7, [sl, r5, asl #2]	@ prephitmp.5558, s_pstVfmwChan
.L2073:
	add	r0, r7, #48	@, prephitmp.5558,
	mov	r2, #92	@,
	mov	r1, r8	@, pstCfg
	sub	r7, fp, #220	@ tmp667,,
	bl	memcpy	@
	ldr	r9, [r4, r5, asl #2]	@ tmp373, s_pstVfmwChan
	ldr	r2, [r8, #12]	@ <variable>.s32ChanPriority, <variable>.s32ChanPriority
	mov	r1, #152	@,
	mov	r0, r7	@, tmp667
	str	r2, [r9, #24]	@ <variable>.s32ChanPriority, <variable>.s32Priority
	ldr	ip, [r8, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	sl, [r4, r5, asl #2]	@ tmp376, s_pstVfmwChan
	str	ip, [sl, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	r3, [r4, r5, asl #2]	@ tmp379, s_pstVfmwChan
	ldr	r9, [r8, #88]	@ <variable>.s32ExtraFrameStoreNum, <variable>.s32ExtraFrameStoreNum
	str	r9, [r3, #1896]	@ <variable>.s32ExtraFrameStoreNum, <variable>.stSynExtraData.stChanOption.s32ExtraFrameStoreNum
	bl	__memzero	@
	ldr	sl, [r4, r5, asl #2]	@ tmp383, s_pstVfmwChan
	ldr	r2, [sl, #284]	@ <variable>.s32ScdChanMemAddr, <variable>.s32ScdChanMemAddr
	str	r2, [fp, #-208]	@ <variable>.s32ScdChanMemAddr, ScdInstCfg.BufPhyAddr
	ldr	r0, [sl, #284]	@, <variable>.s32ScdChanMemAddr
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
	ldr	r0, [lr, #296]	@ <variable>.s32ScdChanMemSize, <variable>.s32ScdChanMemSize
	sub	lr, fp, #196	@ tmp402,,
	str	r3, [fp, #-200]	@ tmp394, ScdInstCfg.RegPhyBaseAddr
	str	r2, [fp, #-212]	@ <variable>.eVidStd, ScdInstCfg.VidStd
	strb	ip, [fp, #-216]	@ <variable>.s32ChanPriority, ScdInstCfg.Priority
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
	add	sl, r8, #4	@ tmp670, pstCfg,
	ldreq	r2, [r8, #48]	@ iftmp.545, <variable>.s32LowdlyEnable
	movne	r2, #0	@ iftmp.545,
	str	r2, [fp, #-180]	@ iftmp.545, ScdInstCfg.ScdLowdlyEnable
	ldmia	sl, {r0, r1}	@ tmp670,,
	stmia	lr, {r0, r1}	@ tmp402,,
	mov	r1, r7	@, tmp667
	mov	r0, r5	@, ChanID
	bl	SM_Config	@
	mov	r0, r9	@, tmp405
	mov	r1, #1	@,
	bl	__memzero	@
	ldr	r3, [r8, #76]	@ <variable>.s32IsOmxPath, <variable>.s32IsOmxPath
	cmp	r3, #1	@ <variable>.s32IsOmxPath,
	beq	.L2163	@,
.L2103:
	ldr	r2, [r4, r5, asl #2]	@ temp.5701, s_pstVfmwChan
	mov	ip, #0	@ tmp453,
	movw	lr, #:lower16:251488	@ tmp468,
	movt	lr, #:upper16:251488	@ tmp468,
	movw	r7, #:lower16:.LANCHOR0	@ tmp410,
	movt	r7, #:upper16:.LANCHOR0	@ tmp410,
	ldr	r0, [r2, #248]	@ <variable>.stChanMem_ctx.PhyAddr, <variable>.stChanMem_ctx.PhyAddr
	str	r0, [r2, #1716]	@ <variable>.stChanMem_ctx.PhyAddr, <variable>.stSynExtraData.s32ContextMemAddr
	ldr	r3, [r4, r5, asl #2]	@ temp.5702, s_pstVfmwChan
	ldr	r1, [r3, #252]	@ <variable>.stChanMem_ctx.Length, <variable>.stChanMem_ctx.Length
	str	r1, [r3, #1720]	@ <variable>.stChanMem_ctx.Length, <variable>.stSynExtraData.s32ContextMemSize
	ldr	r2, [r4, r5, asl #2]	@ temp.5703, s_pstVfmwChan
	ldr	r0, [r2, #268]	@ <variable>.s32VdmChanMemAddr, <variable>.s32VdmChanMemAddr
	str	r0, [r2, #1064]	@ <variable>.s32VdmChanMemAddr, <variable>.stSynExtraData.s32SyntaxMemAddr
	ldr	r3, [r4, r5, asl #2]	@ temp.5704, s_pstVfmwChan
	ldr	r1, [r3, #272]	@ <variable>.s32VdmChanMemSize, <variable>.s32VdmChanMemSize
	str	r1, [r3, #1068]	@ <variable>.s32VdmChanMemSize, <variable>.stSynExtraData.s32SyntaxMemSize
	ldr	r2, [r4, r5, asl #2]	@ temp.5705, s_pstVfmwChan
	ldr	r0, [r2, #300]	@ <variable>.s32BpdChanMemAddr, <variable>.s32BpdChanMemAddr
	str	r0, [r2, #1076]	@ <variable>.s32BpdChanMemAddr, <variable>.stSynExtraData.s32BpdMemAddr
	ldr	r3, [r4, r5, asl #2]	@ temp.5706, s_pstVfmwChan
	ldr	r1, [r3, #304]	@ <variable>.s32BpdChanMemSize, <variable>.s32BpdChanMemSize
	str	r1, [r3, #1080]	@ <variable>.s32BpdChanMemSize, <variable>.stSynExtraData.s32BpdMemSize
	ldr	r2, [r4, r5, asl #2]	@ temp.5707, s_pstVfmwChan
	ldr	r0, [r2, #308]	@ <variable>.s32Vp8SegIdChanMemAddr, <variable>.s32Vp8SegIdChanMemAddr
	str	r0, [r2, #1084]	@ <variable>.s32Vp8SegIdChanMemAddr, <variable>.stSynExtraData.s32Vp8SegIdMemAddr
	ldr	r3, [r4, r5, asl #2]	@ temp.5708, s_pstVfmwChan
	ldr	r1, [r3, #312]	@ <variable>.s32Vp8SegIdChanMemSize, <variable>.s32Vp8SegIdChanMemSize
	str	r1, [r3, #1088]	@ <variable>.s32Vp8SegIdChanMemSize, <variable>.stSynExtraData.s32Vp8SegIdMemSize
	ldr	r2, [r4, r5, asl #2]	@ tmp427, s_pstVfmwChan
	ldr	r0, [r8, #16]	@ <variable>.s32ChanErrThr, <variable>.s32ChanErrThr
	str	r0, [r2, #1044]	@ <variable>.s32ChanErrThr, <variable>.stSynExtraData.s32OutErrThr
	ldr	r3, [r4, r5, asl #2]	@ tmp430, s_pstVfmwChan
	ldr	r1, [r8, #16]	@ <variable>.s32ChanErrThr, <variable>.s32ChanErrThr
	str	r1, [r3, #1040]	@ <variable>.s32ChanErrThr, <variable>.stSynExtraData.s32RefErrThr
	ldr	r2, [r4, r5, asl #2]	@ tmp433, s_pstVfmwChan
	ldr	r0, [r8, #24]	@ <variable>.s32DecMode, <variable>.s32DecMode
	str	r0, [r2, #1048]	@ <variable>.s32DecMode, <variable>.stSynExtraData.s32DecMode
	ldr	r3, [r4, r5, asl #2]	@ tmp436, s_pstVfmwChan
	ldr	r1, [r8, #28]	@ <variable>.s32DecOrderOutput, <variable>.s32DecOrderOutput
	str	r1, [r3, #1052]	@ <variable>.s32DecOrderOutput, <variable>.stSynExtraData.s32DecOrderOutput
	ldr	r2, [r4, r5, asl #2]	@ tmp439, s_pstVfmwChan
	ldr	r0, [r8, #32]	@ <variable>.s32DnrTfEnable, <variable>.s32DnrTfEnable
	str	r0, [r2, #1056]	@ <variable>.s32DnrTfEnable, <variable>.stSynExtraData.s32DnrTfEnable
	ldr	r3, [r4, r5, asl #2]	@ tmp442, s_pstVfmwChan
	ldr	r1, [r8, #52]	@ <variable>.s32VcmpEn, <variable>.s32VcmpEn
	str	r1, [r3, #1724]	@ <variable>.s32VcmpEn, <variable>.stSynExtraData.s32Compress_en
	ldr	r0, [r4, r5, asl #2]	@ tmp445, s_pstVfmwChan
	ldr	r2, [r8, #68]	@ <variable>.s32SupportAllP, <variable>.s32SupportAllP
	cmp	r2, #1	@ <variable>.s32SupportAllP,
	movne	r1, #0	@, tmp447
	moveq	r1, #1	@, tmp447
	str	r1, [r0, #1740]	@ tmp447, <variable>.stSynExtraData.s32SupportAllP
	ldr	r3, [r4, r5, asl #2]	@ tmp449, s_pstVfmwChan
	ldr	r2, [r8, #72]	@ <variable>.s32ModuleLowlyEnable, <variable>.s32ModuleLowlyEnable
	str	r2, [r3, #1744]	@ <variable>.s32ModuleLowlyEnable, <variable>.stSynExtraData.s32ModuleLowlyEnable
	ldr	r0, [r4, r5, asl #2]	@ tmp452, s_pstVfmwChan
	str	ip, [r0, #1924]	@ tmp453, <variable>.stSynExtraData.s32WaitFsFlag
	ldr	r1, [r4, r5, asl #2]	@ tmp455, s_pstVfmwChan
	str	ip, [r1, #1936]	@ tmp453, <variable>.stSynExtraData.s32Is4k60fps
	ldr	r3, [r4, r5, asl #2]	@ tmp459, s_pstVfmwChan
	ldmia	sl, {r0, r1}	@ tmp670,,
	add	r2, r3, #1584	@ tmp458, tmp459,
	add	r3, r2, #12	@ tmp458, tmp458,
	stmia	r3, {r0, r1}	@ tmp458,,
	ldr	r0, [r4, r5, asl #2]	@ tmp465, s_pstVfmwChan
	str	ip, [r0, #1060]	@ tmp453, <variable>.stSynExtraData.s32DnrDispOutEnable
	ldr	r0, [r4, r5, asl #2]	@ prephitmp.5681, s_pstVfmwChan
	ldr	r3, [r0, lr]	@ prephitmp.5560, <variable>.stSynCtx.eVidStd
	ldr	r1, [r0, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, r1	@ prephitmp.5560, <variable>.eVidStd
	beq	.L2104	@,
	mov	r0, r5	@, ChanID
	bl	VCTRL_ResetChan	@
	ldr	ip, [r8, #0]	@ <variable>.eVidStd, <variable>.eVidStd
	ldr	r0, [r7, r5, asl #2]	@ prephitmp.5681, s_pstVfmwChan
	cmp	ip, #18	@ <variable>.eVidStd,
	bne	.L2147	@,
	ldr	r1, [r0, #1772]	@ <variable>.stSynExtraData.stChanOption.Purpose, <variable>.stSynExtraData.stChanOption.Purpose
	ldr	lr, [r0, #292]	@ <variable>.s32SdecMemSize, <variable>.s32SdecMemSize
	cmp	r1, #2	@ <variable>.stSynExtraData.stChanOption.Purpose,
	ldr	r3, [r0, #288]	@ <variable>.s32SdecMemAddr, <variable>.s32SdecMemAddr
	ldrne	r1, [r0, #1780]	@ MaxWidth, <variable>.stSynExtraData.stChanOption.s32MaxWidth
	ldrne	r2, [r0, #1784]	@ MaxHeight, <variable>.stSynExtraData.stChanOption.s32MaxHeight
	ldreq	r1, [r0, #1836]	@ MaxWidth, <variable>.stSynExtraData.stChanOption.s32SlotWidth
	ldreq	r2, [r0, #1840]	@ MaxHeight, <variable>.stSynExtraData.stChanOption.s32SlotHeight
	mov	r0, r5	@, ChanID
	str	lr, [sp, #0]	@ <variable>.s32SdecMemSize,
	bl	VCTRL_PartitionMemForStdUser	@
	cmp	r0, #0	@,
	bne	.L2108	@,
	ldr	r0, [r4, r5, asl #2]	@ prephitmp.5681, s_pstVfmwChan
.L2147:
	ldr	r3, [r0, #1032]	@ prephitmp.5560, <variable>.eVidStd
.L2104:
	movw	lr, #:lower16:251488	@ tmp477,
	movt	lr, #:upper16:251488	@ tmp477,
	movw	r7, #:lower16:.LANCHOR0	@ tmp478,
	movt	r7, #:upper16:.LANCHOR0	@ tmp478,
	str	r3, [r0, lr]	@ prephitmp.5560, <variable>.stSynCtx.eVidStd
	ldr	r0, [r4, r5, asl #2]	@ tmp479, s_pstVfmwChan
	ldr	ip, [r0, #288]	@ temp.5724, <variable>.s32SdecMemAddr
	mov	r0, ip	@, temp.5724
	str	ip, [fp, #-64]	@ temp.5724, stMem.PhyAddr
	bl	MEM_Phy2Vir	@
	ldr	r2, [r4, r5, asl #2]	@ tmp481, s_pstVfmwChan
	sub	r1, fp, #64	@,,
	str	r0, [fp, #-60]	@, stMem.VirAddr
	mov	r0, r5	@, ChanID
	ldr	r3, [r2, #292]	@ <variable>.s32SdecMemSize, <variable>.s32SdecMemSize
	str	r3, [fp, #-56]	@ <variable>.s32SdecMemSize, stMem.Length
	bl	RefreshDecCore	@
	cmp	r0, #0	@,
	bne	.L2062	@,
	ldr	lr, [r7, #0]	@ D.40583, s_pstVfmwChan
	ldr	r0, [r4, #4]	@ temp.5599, s_pstVfmwChan
	cmp	lr, #0	@ D.40583,
	ldr	ip, [r4, #8]	@ temp.5731, s_pstVfmwChan
	streq	lr, [r6, #-3660]	@ D.40583, PrioArray
	ldrne	r1, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movweq	r3, #:lower16:g_ChanCtx	@ tmp671,
	movwne	r3, #:lower16:g_ChanCtx	@ tmp671,
	movteq	r3, #:upper16:g_ChanCtx	@ tmp671,
	movtne	r3, #:upper16:g_ChanCtx	@ tmp671,
	ldr	r2, [r4, #12]	@ temp.5735, s_pstVfmwChan
	strne	r1, [r6, #-3660]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r0, #0	@ temp.5599,
	streq	r0, [r3, #4]	@ temp.5599, g_ChanCtx.PriorByChanId
	streq	r0, [r6, #-3656]	@ temp.5599, PrioArray
	str	lr, [r3, #0]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldrne	r1, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	ldr	lr, [r4, #16]	@ temp.5739, s_pstVfmwChan
	strne	r1, [r6, #-3656]	@ <variable>.s32Priority, PrioArray
	ldrne	r0, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r0, [r3, #4]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5731,
	streq	ip, [r3, #8]	@ temp.5731, g_ChanCtx.PriorByChanId
	ldrne	r1, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r6, #-3652]	@ temp.5731, PrioArray
	strne	r1, [r6, #-3652]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r3, #8]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r2, #0	@ temp.5735,
	streq	r2, [r3, #12]	@ temp.5735, g_ChanCtx.PriorByChanId
	ldrne	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r2, [r6, #-3648]	@ temp.5735, PrioArray
	strne	r1, [r6, #-3648]	@ <variable>.s32Priority, PrioArray
	ldrne	r2, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r2, [r3, #12]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5739,
	streq	lr, [r3, #16]	@ temp.5739, g_ChanCtx.PriorByChanId
	ldrne	r1, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r6, #-3644]	@ temp.5739, PrioArray
	strne	r1, [r6, #-3644]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r3, #16]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	r0, [r4, #20]	@ temp.5743, s_pstVfmwChan
	ldr	ip, [r4, #24]	@ temp.5747, s_pstVfmwChan
	cmp	r0, #0	@ temp.5743,
	ldr	r2, [r4, #28]	@ temp.5751, s_pstVfmwChan
	streq	r0, [r3, #20]	@ temp.5743, g_ChanCtx.PriorByChanId
	ldrne	r1, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r0, [r6, #-3640]	@ temp.5743, PrioArray
	ldr	lr, [r4, #32]	@ temp.5755, s_pstVfmwChan
	strne	r1, [r6, #-3640]	@ <variable>.s32Priority, PrioArray
	ldrne	r0, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r0, [r3, #20]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5747,
	streq	ip, [r3, #24]	@ temp.5747, g_ChanCtx.PriorByChanId
	ldrne	r1, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r6, #-3636]	@ temp.5747, PrioArray
	ldr	r0, [r4, #36]	@ temp.5759, s_pstVfmwChan
	strne	r1, [r6, #-3636]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r3, #24]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r2, #0	@ temp.5751,
	streq	r2, [r3, #28]	@ temp.5751, g_ChanCtx.PriorByChanId
	ldrne	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r2, [r6, #-3632]	@ temp.5751, PrioArray
	strne	r1, [r6, #-3632]	@ <variable>.s32Priority, PrioArray
	ldrne	r2, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r2, [r3, #28]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5755,
	streq	lr, [r3, #32]	@ temp.5755, g_ChanCtx.PriorByChanId
	ldrne	r1, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r6, #-3628]	@ temp.5755, PrioArray
	strne	r1, [r6, #-3628]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r3, #32]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r0, #0	@ temp.5759,
	streq	r0, [r3, #36]	@ temp.5759, g_ChanCtx.PriorByChanId
	ldrne	r1, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r0, [r6, #-3624]	@ temp.5759, PrioArray
	strne	r1, [r6, #-3624]	@ <variable>.s32Priority, PrioArray
	ldrne	r0, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r0, [r3, #36]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	ip, [r4, #40]	@ temp.5763, s_pstVfmwChan
	ldr	r2, [r4, #44]	@ temp.5767, s_pstVfmwChan
	cmp	ip, #0	@ temp.5763,
	ldr	lr, [r4, #48]	@ temp.5771, s_pstVfmwChan
	streq	ip, [r3, #40]	@ temp.5763, g_ChanCtx.PriorByChanId
	ldrne	r1, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r6, #-3620]	@ temp.5763, PrioArray
	ldr	r0, [r4, #52]	@ temp.5775, s_pstVfmwChan
	strne	r1, [r6, #-3620]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r3, #40]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r2, #0	@ temp.5767,
	streq	r2, [r3, #44]	@ temp.5767, g_ChanCtx.PriorByChanId
	ldrne	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r2, [r6, #-3616]	@ temp.5767, PrioArray
	ldr	ip, [r4, #56]	@ temp.5779, s_pstVfmwChan
	strne	r1, [r6, #-3616]	@ <variable>.s32Priority, PrioArray
	ldrne	r2, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r2, [r3, #44]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5771,
	streq	lr, [r3, #48]	@ temp.5771, g_ChanCtx.PriorByChanId
	ldrne	r1, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r6, #-3612]	@ temp.5771, PrioArray
	strne	r1, [r6, #-3612]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r3, #48]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r0, #0	@ temp.5775,
	streq	r0, [r3, #52]	@ temp.5775, g_ChanCtx.PriorByChanId
	ldrne	r1, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r0, [r6, #-3608]	@ temp.5775, PrioArray
	strne	r1, [r6, #-3608]	@ <variable>.s32Priority, PrioArray
	ldrne	r0, [r0, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r0, [r3, #52]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5779,
	streq	ip, [r3, #56]	@ temp.5779, g_ChanCtx.PriorByChanId
	ldrne	r1, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r6, #-3604]	@ temp.5779, PrioArray
	ldr	r0, .L2168+4	@,
	strne	r1, [r6, #-3604]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r3, #56]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	r2, [r4, #60]	@ temp.5727, s_pstVfmwChan
	cmp	r2, #0	@ temp.5727,
	streq	r2, [r3, #60]	@ temp.5727, g_ChanCtx.PriorByChanId
	ldrne	r1, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r2, [r6, #-3600]	@ temp.5727, PrioArray
	strne	r1, [r6, #-3600]	@ <variable>.s32Priority, PrioArray
	ldrne	r2, [r2, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r2, [r3, #60]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	bl	VDMDRV_SetPriority	@
	mov	r0, r5	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	mov	r0, #0	@ D.40351,
	b	.L2054	@
.L2069:
	cmp	r2, #4	@ D.40400,
	bne	.L2071	@,
.L2070:
	mov	r2, #1	@ prephitmp.5659,
	b	.L2072	@
.L2065:
	cmp	r3, #4	@ D.40368,
	bne	.L2067	@,
.L2066:
	mov	r0, #1	@ prephitmp.5556,
	b	.L2068	@
.L2074:
	movw	sl, #:lower16:.LANCHOR0	@ tmp310,
	movt	sl, #:upper16:.LANCHOR0	@ tmp310,
	add	r0, sl, #504	@, tmp310,
	bl	OSAL_SpinUnLockIRQ	@
	ldr	r0, [r7, #196]	@, <variable>.stChanMem.VirAddr
	bl	KernelMunmap	@
	ldr	r3, [r8, #0]	@ temp.5636, <variable>.eVidStd
	sub	r9, r3, #10	@ tmp313, temp.5636,
	cmp	r9, #2	@ tmp313,
	bhi	.L2089	@,
	ldr	r1, [sl, #500]	@ g_VdmCharacter, g_VdmCharacter
	tst	r1, #1	@ g_VdmCharacter,
	bne	.L2091	@,
.L2090:
	ldr	r0, [r7, #200]	@, <variable>.stChanMem.PhyAddr
	ldr	r1, [r7, #204]	@, <variable>.stChanMem.Length
	bl	KernelMmapCache	@
	mov	r9, r0	@ pVir,
.L2092:
	movw	sl, #:lower16:.LANCHOR0	@ tmp321,
	movt	sl, #:upper16:.LANCHOR0	@ tmp321,
	add	r0, sl, #504	@, tmp321,
	bl	OSAL_SpinLockIRQ	@
	ldr	r3, [r4, r5, asl #2]	@ temp.5645, s_pstVfmwChan
	cmp	r3, #0	@ temp.5645,
	beq	.L2164	@,
	cmp	r9, #0	@ pVir,
	beq	.L2165	@,
	ldr	r2, [r3, #236]	@, <variable>.stChanMem_scd.Length
	ldr	r0, [r3, #232]	@, <variable>.stChanMem_scd.PhyAddr
	ldr	r1, [r3, #228]	@, <variable>.stChanMem_scd.VirAddr
	bl	MEM_DelMemRecord	@
	cmp	r0, #0	@
	str	r0, [fp, #-224]	@, %sfp
	ldrne	r2, [sl, r5, asl #2]	@ temp.5648, s_pstVfmwChan
	movne	r0, #0	@,
	bne	.L2149	@,
	ldr	ip, [sl, r5, asl #2]	@ temp.5652, s_pstVfmwChan
	ldr	r2, [ip, #220]	@, <variable>.stChanMem_vdh.Length
	ldr	r0, [ip, #216]	@, <variable>.stChanMem_vdh.PhyAddr
	ldr	r1, [ip, #212]	@, <variable>.stChanMem_vdh.VirAddr
	bl	MEM_DelMemRecord	@
	cmp	r0, #0	@
	str	r0, [fp, #-228]	@, %sfp
	ldrne	r2, [sl, r5, asl #2]	@ temp.5654, s_pstVfmwChan
	ldrne	r0, [fp, #-224]	@, %sfp
	bne	.L2148	@,
	str	r9, [r7, #196]	@ pVir, <variable>.stChanMem.VirAddr
	mov	r1, r9	@, pVir
	ldr	r3, [sl, r5, asl #2]	@ tmp343, s_pstVfmwChan
	ldr	r0, [r7, #200]	@, <variable>.stChanMem.PhyAddr
	ldr	r2, [r7, #204]	@, <variable>.stChanMem.Length
	str	r9, [r3, #228]	@ pVir, <variable>.stChanMem_scd.VirAddr
	ldr	lr, [sl, r5, asl #2]	@ temp.5660, s_pstVfmwChan
	ldr	ip, [lr, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	add	r3, r9, ip	@ tmp346, pVir, <variable>.stChanMem_scd.Length
	str	r3, [lr, #212]	@ tmp346, <variable>.stChanMem_vdh.VirAddr
	bl	MEM_AddMemRecord	@
	subs	r9, r0, #0	@ D.40502,
	bne	.L2166	@,
	ldr	r7, [sl, r5, asl #2]	@ temp.5669, s_pstVfmwChan
	ldr	r2, [r7, #236]	@, <variable>.stChanMem_scd.Length
	ldr	r0, [r7, #232]	@, <variable>.stChanMem_scd.PhyAddr
	ldr	r1, [r7, #228]	@, <variable>.stChanMem_scd.VirAddr
	bl	MEM_AddMemRecord	@
	subs	r7, r0, #0	@ D.40505,
	bne	.L2167	@,
	ldr	ip, [sl, r5, asl #2]	@ temp.5678, s_pstVfmwChan
	ldr	r2, [ip, #220]	@, <variable>.stChanMem_vdh.Length
	ldr	r0, [ip, #216]	@, <variable>.stChanMem_vdh.PhyAddr
	ldr	r1, [ip, #212]	@, <variable>.stChanMem_vdh.VirAddr
	bl	MEM_AddMemRecord	@
	cmp	r0, #0	@,
	beq	.L2146	@,
	ldr	r2, [sl, r5, asl #2]	@ temp.5684, s_pstVfmwChan
	mov	r0, r7	@, D.40505
.L2148:
	ldr	r3, [r2, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	movw	r1, #:lower16:.LC324	@,
	movt	r1, #:upper16:.LC324	@,
	str	r3, [sp, #0]	@ <variable>.stChanMem_vdh.Length,
	ldr	r3, [r2, #212]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r2, [r2, #216]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2157:
	movw	r1, #:lower16:.LC321	@,
	movt	r1, #:upper16:.LC321	@,
	bl	dprint_vfmw	@
	mov	r0, r7	@ D.40351, D.40380
	b	.L2054	@
.L2156:
	sub	r0, fp, #52	@,,
	bl	REAL9DEC_Support	@
	ldr	r1, [fp, #-52]	@ s32supportFlag, s32supportFlag
	cmp	r1, #0	@ s32supportFlag,
	bne	.L2063	@,
.L2062:
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2108:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC326	@,
	movt	r1, #:upper16:.LC326	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2153:
	mov	r0, r6	@, tmp212
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #3070	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC41	@,
	movt	r3, #:upper16:.LC41	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2076:
	cmp	r3, #4	@ temp.5594,
	beq	.L2077	@,
	cmp	r3, #14	@ temp.5594,
	beq	.L2077	@,
.L2078:
	ldr	r1, [r7, #220]	@, <variable>.stChanMem_vdh.Length
	mov	sl, #0	@ tmp269,
	ldr	r0, [r7, #216]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	KernelMmap	@
	ldr	r1, [r7, #236]	@ temp.5600, <variable>.stChanMem_scd.Length
	strb	sl, [r7, #208]	@ tmp269, <variable>.stChanMem_vdh.IsCached
	cmp	r1, sl	@ temp.5600,
	mov	r9, r0	@ pVir_vdh,
	beq	.L2079	@,
	ldr	r0, [r7, #232]	@, <variable>.stChanMem_scd.PhyAddr
	bl	KernelMmap	@
	str	r0, [fp, #-224]	@, %sfp
	strb	sl, [r7, #224]	@ tmp269, <variable>.stChanMem_scd.IsCached
	b	.L2080	@
.L2089:
	cmp	r3, #4	@ temp.5636,
	beq	.L2090	@,
	cmp	r3, #14	@ temp.5636,
	beq	.L2090	@,
.L2091:
	ldr	r0, [r7, #200]	@, <variable>.stChanMem.PhyAddr
	ldr	r1, [r7, #204]	@, <variable>.stChanMem.Length
	bl	KernelMmap	@
	mov	r9, r0	@ pVir,
	b	.L2092	@
.L2163:
	mov	r1, r9	@, tmp405
	mov	r0, r5	@, ChanID
	strb	r3, [fp, #-48]	@ <variable>.s32IsOmxPath, FspInstCfg.s8LowBufEnable
	bl	FSP_ConfigAttribute	@
	b	.L2103	@
.L2086:
	ldr	r0, [r7, #232]	@, <variable>.stChanMem_scd.PhyAddr
	ldr	r1, [r7, #228]	@, <variable>.stChanMem_scd.VirAddr
	bl	MEM_DelMemRecord	@
	cmp	r0, #0	@
	str	r0, [fp, #-228]	@, %sfp
	movne	r0, r9	@, D.40455
	ldrne	r3, [r7, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	bne	.L2150	@,
	ldr	r0, [fp, #-224]	@, %sfp
	ldr	r2, [r7, #236]	@, <variable>.stChanMem_scd.Length
	str	r0, [r7, #228]	@, <variable>.stChanMem_scd.VirAddr
	ldr	r1, [fp, #-224]	@, %sfp
	ldr	r0, [r7, #232]	@, <variable>.stChanMem_scd.PhyAddr
	bl	MEM_AddMemRecord	@
	cmp	r0, #0	@,
	beq	.L2146	@,
	ldr	r3, [r7, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	ldr	r0, [fp, #-228]	@, %sfp
.L2150:
	str	r3, [sp, #0]	@ <variable>.stChanMem_scd.Length,
	movw	r1, #:lower16:.LC324	@,
	ldr	r3, [r7, #228]	@, <variable>.stChanMem_scd.VirAddr
	movt	r1, #:upper16:.LC324	@,
	ldr	r2, [r7, #232]	@, <variable>.stChanMem_scd.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2158:
	ldr	r0, [r7, #228]	@, <variable>.stChanMem_scd.VirAddr
	bl	KernelMunmap	@
	b	.L2075	@
.L2154:
	mov	r0, r6	@, tmp212
	movw	r1, #:lower16:.LC319	@,
	movt	r1, #:upper16:.LC319	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2159:
	ldr	r0, [r7, #232]	@, <variable>.stChanMem_scd.PhyAddr
	bl	KernelMmapCache	@
	str	r0, [fp, #-224]	@, %sfp
	strb	sl, [r7, #224]	@ tmp262, <variable>.stChanMem_scd.IsCached
	b	.L2080	@
.L2151:
	mov	r0, r6	@, tmp212
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #3068	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2082:
	mov	r2, r5	@, ChanID
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC323	@,
	movt	r1, #:upper16:.LC323	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2167:
	ldr	r2, [sl, r5, asl #2]	@ temp.5674, s_pstVfmwChan
	mov	r0, r9	@, D.40502
.L2149:
	ldr	lr, [r2, #236]	@ <variable>.stChanMem_scd.Length, <variable>.stChanMem_scd.Length
	movw	r1, #:lower16:.LC324	@,
	movt	r1, #:upper16:.LC324	@,
	str	lr, [sp, #0]	@ <variable>.stChanMem_scd.Length,
	ldr	r3, [r2, #228]	@, <variable>.stChanMem_scd.VirAddr
	ldr	r2, [r2, #232]	@, <variable>.stChanMem_scd.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2161:
	ldr	lr, [r7, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	mov	r0, r3	@, tmp289
	movw	r1, #:lower16:.LC324	@,
	movt	r1, #:upper16:.LC324	@,
	str	lr, [sp, #0]	@ <variable>.stChanMem_vdh.Length,
	ldr	r3, [r7, #212]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r2, [r7, #216]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2166:
	ldr	r2, [r7, #204]	@ <variable>.stChanMem.Length, <variable>.stChanMem.Length
	movw	r1, #:lower16:.LC324	@,
	ldr	r0, [fp, #-228]	@, %sfp
	movt	r1, #:upper16:.LC324	@,
	str	r2, [sp, #0]	@ <variable>.stChanMem.Length,
	ldr	r3, [r7, #196]	@, <variable>.stChanMem.VirAddr
	ldr	r2, [r7, #200]	@, <variable>.stChanMem.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2155:
	sub	r0, fp, #52	@,,
	bl	REAL8DEC_Support	@
	ldr	r0, [fp, #-52]	@ s32supportFlag, s32supportFlag
	cmp	r0, #0	@ s32supportFlag,
	beq	.L2062	@,
	ldr	r2, [r8, #0]	@ prephitmp.5554, <variable>.eVidStd
	b	.L2061	@
.L2152:
	mov	r0, r3	@, D.40353
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #3069	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2162:
	ldr	r2, [r7, #220]	@ <variable>.stChanMem_vdh.Length, <variable>.stChanMem_vdh.Length
	movw	r1, #:lower16:.LC324	@,
	ldr	r0, [fp, #-228]	@, %sfp
	movt	r1, #:upper16:.LC324	@,
	str	r2, [sp, #0]	@ <variable>.stChanMem_vdh.Length,
	ldr	r3, [r7, #212]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r2, [r7, #216]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2165:
	mov	r0, r9	@, pVir
	mov	r2, r5	@, ChanID
	movw	r1, #:lower16:.LC325	@,
	movt	r1, #:upper16:.LC325	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2160:
	movw	r1, #:lower16:.LC322	@,
	ldr	r2, .L2168+8	@,
	movt	r1, #:upper16:.LC322	@,
	movw	r3, #3162	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2164:
	mov	r0, r3	@, temp.5645
	movw	r1, #:lower16:.LC322	@,
	ldr	r2, .L2168+8	@,
	movt	r1, #:upper16:.LC322	@,
	movw	r3, #3231	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40351,
	b	.L2054	@
.L2169:
	.align	2
.L2168:
	.word	.LANCHOR0+504
	.word	.LANCHOR4-3660
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
	bhi	.L2210	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp342,
	movt	r4, #:upper16:.LANCHOR0	@ tmp342,
	ldr	r3, [r4, r0, asl #2]	@ D.40087, s_pstVfmwChan
	cmp	r3, #0	@ D.40087,
	beq	.L2211	@,
	ldr	r6, [r3, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r6, #1	@ <variable>.s32IsOpen,
	bne	.L2212	@,
	ldr	r3, [r3, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #19	@ <variable>.eVidStd,
	beq	.L2213	@,
	bl	VCTRL_ResetChan	@
	ldr	r3, [r4, r5, asl #2]	@ temp.5811, s_pstVfmwChan
	ldr	r2, [r3, #220]	@, <variable>.stChanMem_vdh.Length
	ldr	r1, [r3, #212]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r0, [r3, #216]	@, <variable>.stChanMem_vdh.PhyAddr
	bl	MEM_DelMemRecord	@
	ldmia	r7, {r0, r1, r2, r3}	@ pChanMemVdh,,,,
	ldr	ip, [r4, r5, asl #2]	@ tmp175, s_pstVfmwChan
	add	ip, ip, #208	@ tmp174, tmp175,
	stmia	ip, {r0, r1, r2, r3}	@ tmp174,,,,
	ldr	ip, [r4, r5, asl #2]	@ temp.5813, s_pstVfmwChan
	ldr	r2, [ip, #220]	@, <variable>.stChanMem_vdh.Length
	ldr	r1, [ip, #212]	@, <variable>.stChanMem_vdh.VirAddr
	ldr	r0, [ip, #216]	@, <variable>.stChanMem_vdh.PhyAddr
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
	ldr	r3, [r4, r5, asl #2]	@ temp.5820, s_pstVfmwChan
	ldr	r2, [r3, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	cmp	r2, #0	@ <variable>.s32Priority,
	bne	.L2176	@,
	str	r6, [r3, #24]	@ <variable>.s32IsOpen, <variable>.s32Priority
	ldr	r1, [r4, #0]	@ D.40104, s_pstVfmwChan
	cmp	r1, #0	@ D.40104,
	beq	.L2214	@,
	ldr	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	movw	r3, #:lower16:.LANCHOR4	@ tmp343,
	movt	r3, #:upper16:.LANCHOR4	@ tmp343,
	movw	r2, #:lower16:g_ChanCtx	@ tmp344,
	movt	r2, #:upper16:g_ChanCtx	@ tmp344,
	str	r0, [r3, #-3596]	@ <variable>.s32Priority, PrioArray
	ldr	lr, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	str	lr, [r2, #0]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
.L2178:
	ldr	lr, [r4, #4]	@ temp.5825, s_pstVfmwChan
	ldr	ip, [r4, #8]	@ temp.5828, s_pstVfmwChan
	cmp	lr, #0	@ temp.5825,
	ldr	r1, [r4, #12]	@ temp.5831, s_pstVfmwChan
	streq	lr, [r3, #-3592]	@ temp.5825, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #4]	@ temp.5825, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-3592]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #4]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5828,
	streq	ip, [r3, #-3588]	@ temp.5828, PrioArray
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r2, #8]	@ temp.5828, g_ChanCtx.PriorByChanId
	ldr	lr, [r4, #16]	@ temp.5834, s_pstVfmwChan
	strne	r0, [r3, #-3588]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #8]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.5831,
	streq	r1, [r3, #-3584]	@ temp.5831, PrioArray
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r2, #12]	@ temp.5831, g_ChanCtx.PriorByChanId
	ldr	ip, [r4, #20]	@ temp.5837, s_pstVfmwChan
	strne	r0, [r3, #-3584]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #12]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5834,
	streq	lr, [r3, #-3580]	@ temp.5834, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #16]	@ temp.5834, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-3580]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #16]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5837,
	streq	ip, [r3, #-3576]	@ temp.5837, PrioArray
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r2, #20]	@ temp.5837, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-3576]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #20]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	r1, [r4, #24]	@ temp.5840, s_pstVfmwChan
	ldr	lr, [r4, #28]	@ temp.5843, s_pstVfmwChan
	cmp	r1, #0	@ temp.5840,
	ldr	ip, [r4, #32]	@ temp.5846, s_pstVfmwChan
	streq	r1, [r3, #-3572]	@ temp.5840, PrioArray
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r2, #24]	@ temp.5840, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-3572]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #24]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5843,
	streq	lr, [r3, #-3568]	@ temp.5843, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #28]	@ temp.5843, g_ChanCtx.PriorByChanId
	ldr	r1, [r4, #36]	@ temp.5849, s_pstVfmwChan
	strne	r0, [r3, #-3568]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #28]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5846,
	streq	ip, [r3, #-3564]	@ temp.5846, PrioArray
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r2, #32]	@ temp.5846, g_ChanCtx.PriorByChanId
	ldr	lr, [r4, #40]	@ temp.5852, s_pstVfmwChan
	strne	r0, [r3, #-3564]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #32]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.5849,
	streq	r1, [r3, #-3560]	@ temp.5849, PrioArray
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r2, #36]	@ temp.5849, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-3560]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #36]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5852,
	streq	lr, [r3, #-3556]	@ temp.5852, PrioArray
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r2, #40]	@ temp.5852, g_ChanCtx.PriorByChanId
	strne	r0, [r3, #-3556]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #40]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	ldr	ip, [r4, #44]	@ temp.5855, s_pstVfmwChan
	ldr	r1, [r4, #48]	@ temp.5858, s_pstVfmwChan
	cmp	ip, #0	@ temp.5855,
	ldr	lr, [r4, #52]	@ temp.5861, s_pstVfmwChan
	streq	ip, [r2, #44]	@ temp.5855, g_ChanCtx.PriorByChanId
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r3, #-3552]	@ temp.5855, PrioArray
	strne	r0, [r3, #-3552]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #44]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.5858,
	streq	r1, [r2, #48]	@ temp.5858, g_ChanCtx.PriorByChanId
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	r1, [r3, #-3548]	@ temp.5858, PrioArray
	ldr	ip, [r4, #56]	@ temp.5864, s_pstVfmwChan
	strne	r0, [r3, #-3548]	@ <variable>.s32Priority, PrioArray
	ldrne	r1, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r1, [r2, #48]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	lr, #0	@ temp.5861,
	streq	lr, [r2, #52]	@ temp.5861, g_ChanCtx.PriorByChanId
	ldrne	r0, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	lr, [r3, #-3544]	@ temp.5861, PrioArray
	ldr	r1, [r4, #60]	@ temp.5821, s_pstVfmwChan
	strne	r0, [r3, #-3544]	@ <variable>.s32Priority, PrioArray
	ldrne	lr, [lr, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	lr, [r2, #52]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	ip, #0	@ temp.5864,
	streq	ip, [r2, #56]	@ temp.5864, g_ChanCtx.PriorByChanId
	ldrne	r0, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	streq	ip, [r3, #-3540]	@ temp.5864, PrioArray
	strne	r0, [r3, #-3540]	@ <variable>.s32Priority, PrioArray
	ldrne	ip, [ip, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	ip, [r2, #56]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	cmp	r1, #0	@ temp.5821,
	ldrne	r0, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	strne	r0, [r3, #-3536]	@ <variable>.s32Priority, PrioArray
	ldrne	r3, [r1, #24]	@ <variable>.s32Priority, <variable>.s32Priority
	ldr	r0, .L2215	@,
	strne	r3, [r2, #60]	@ <variable>.s32Priority, g_ChanCtx.PriorByChanId
	streq	r1, [r2, #60]	@ temp.5821, g_ChanCtx.PriorByChanId
	streq	r1, [r3, #-3536]	@ temp.5821, PrioArray
	bl	VDMDRV_SetPriority	@
	mov	r0, r5	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
.L2176:
	mov	r0, r5	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	mov	r0, #0	@ D.40085,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L2214:
	movw	r3, #:lower16:.LANCHOR4	@ tmp343,
	movw	r2, #:lower16:g_ChanCtx	@ tmp344,
	movt	r3, #:upper16:.LANCHOR4	@ tmp343,
	movt	r2, #:upper16:g_ChanCtx	@ tmp344,
	str	r1, [r3, #-3596]	@ D.40104, PrioArray
	str	r1, [r2, #0]	@ D.40104, g_ChanCtx.PriorByChanId
	b	.L2178	@
.L2212:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2696	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC26	@,
	movt	r3, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40085,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L2210:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2694	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC6	@,
	movt	r3, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40085,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L2213:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2697	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC242	@,
	movt	r3, #:upper16:.LC242	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40085,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L2211:
	mov	r0, r3	@, D.40087
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #2695	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC161	@,
	movt	r3, #:upper16:.LC161	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40085,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L2216:
	.align	2
.L2215:
	.word	.LANCHOR4-3596
	.fnend
	.size	VCTRL_StartChanWithOption, .-VCTRL_StartChanWithOption
	.align	2
	.global	VCTRL_DestroyChanWithOption
	.type	VCTRL_DestroyChanWithOption, %function
VCTRL_DestroyChanWithOption:
	.fnstart
.LFB1569:
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #132
	sub	sp, sp, #132	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r5, #:lower16:.LANCHOR0	@ tmp217,
	movt	r5, #:upper16:.LANCHOR0	@ tmp217,
	mov	r4, r0	@ ChanID, ChanID
	add	r0, r5, #504	@, tmp217,
	bl	OSAL_SpinLockIRQ	@
	cmp	r4, #15	@ ChanID,
	bhi	.L2227	@,
	ldr	r6, [r5, r4, asl #2]	@ D.40013, s_pstVfmwChan
	cmp	r6, #0	@ D.40013,
	beq	.L2228	@,
	ldr	r3, [r6, #12]	@ <variable>.s32IsOpen, <variable>.s32IsOpen
	cmp	r3, #1	@ <variable>.s32IsOpen,
	bne	.L2229	@,
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
	bne	.L2230	@,
	movw	r9, #:lower16:.LANCHOR3	@ tmp168,
	movt	r9, #:upper16:.LANCHOR3	@ tmp168,
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	add	r8, r9, r4, asl #2	@, tmp171, tmp168, ChanID,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r4	@, ChanID
	bl	VCTRL_ResetChan	@
	bl	VDMDRV_ParamInit	@
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	str	r7, [r8, #-1476]	@ ret, g_DSPState
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, [r6, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r0, #4	@ <variable>.eVidStd,
	beq	.L2231	@,
.L2223:
	mov	r0, r4	@, ChanID
	sub	r7, fp, #124	@,,
	bl	VCTRL_UnInstallChan	@
	ldr	r3, [r5, r4, asl #2]	@ temp.5892, s_pstVfmwChan
	str	r7, [fp, #-168]	@, %sfp
	add	lr, r4, r4, asl #1	@, tmp200, ChanID, ChanID,
	add	ip, r3, #224	@, temp.5892,
	add	r9, r3, #140	@, temp.5892,
	ldr	r0, [r3, #264]	@ <variable>.s32SelfAllocChanMem_ctx, <variable>.s32SelfAllocChanMem_ctx
	add	r2, r3, #192	@ tmp187, temp.5892,
	str	ip, [fp, #-144]	@, %sfp
	sub	ip, fp, #64	@,,
	str	r9, [fp, #-148]	@, %sfp
	add	sl, r3, #248832	@ tmp185, temp.5892,
	str	r0, [fp, #-68]	@ <variable>.s32SelfAllocChanMem_ctx, ChanMem.s32SelfAllocChanMem_ctx
	sub	r0, fp, #108	@,,
	str	ip, [fp, #-164]	@, %sfp
	add	r1, sl, #400	@ tmp185, tmp185,
	str	r0, [fp, #-160]	@, %sfp
	movw	r0, #:lower16:s_SmIIS	@ tmp196,
	ldr	r9, [r3, #256]	@, <variable>.s32SelfAllocChanMem_vdh
	movt	r0, #:upper16:s_SmIIS	@ tmp196,
	add	r7, r3, #240	@ tmp189, temp.5892,
	add	sl, r3, #208	@ tmp191, temp.5892,
	sub	r6, fp, #140	@ tmp218,,
	sub	r8, fp, #92	@ tmp188,,
	str	r9, [fp, #-76]	@, ChanMem.s32SelfAllocChanMem_vdh
	add	r9, r0, lr, asl #4	@, tmp202, tmp196, tmp200,
	ldr	r0, [r3, #260]	@ <variable>.s32SelfAllocChanMem_scd, <variable>.s32SelfAllocChanMem_scd
	mov	lr, #0	@ tmp204,
	movw	ip, #:lower16:s_pFspInst	@ tmp205,
	movt	ip, #:upper16:s_pFspInst	@ tmp205,
	str	r0, [fp, #-72]	@ <variable>.s32SelfAllocChanMem_scd, ChanMem.s32SelfAllocChanMem_scd
	ldr	r0, [r3, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	str	r1, [fp, #-48]	@ tmp185, ChanMem.pstChanFrmBuf
	str	r0, [fp, #-52]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, ChanMem.u32DynamicAllocEn
	ldmia	r2, {r0, r1, r2, r3}	@ tmp187,,,,
	stmia	r6, {r0, r1, r2, r3}	@ tmp218,,,,
	ldmia	r7, {r0, r1, r2, r3}	@ tmp189,,,,
	ldr	r7, [fp, #-168]	@, %sfp
	stmia	r8, {r0, r1, r2, r3}	@ tmp188,,,,
	ldmia	sl, {r0, r1, r2, r3}	@ tmp191,,,,
	stmia	r7, {r0, r1, r2, r3}	@,,,,
	ldr	r7, [fp, #-144]	@, %sfp
	ldmia	r7, {r0, r1, r2, r3}	@,,,,
	ldr	r7, [fp, #-160]	@, %sfp
	stmia	r7, {r0, r1, r2, r3}	@,,,,
	ldr	r7, [fp, #-148]	@, %sfp
	ldmia	r7, {r0, r1, r2}	@,,,
	str	lr, [r5, r4, asl #2]	@ tmp204, s_pstVfmwChan
	str	lr, [r9, #40]	@ tmp204, <variable>.pSmInstArray
	ldr	r7, [fp, #-164]	@, %sfp
	str	lr, [ip, r4, asl #2]	@ tmp204, s_pFspInst
	stmia	r7, {r0, r1, r2}	@,,,
	mov	r0, r4	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	ldr	r3, [fp, #-52]	@ ChanMem.u32DynamicAllocEn, ChanMem.u32DynamicAllocEn
	cmp	r3, #1	@ ChanMem.u32DynamicAllocEn,
	beq	.L2232	@,
.L2224:
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinUnLockIRQ	@
	bl	VCTRL_EnableAllInt	@
	ldr	r0, .L2233	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r4	@, ChanID
	mov	r1, r6	@, tmp218
	bl	VCTRL_FreeChanResource	@
	mov	r0, #0	@ D.40011,
.L2219:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L2231:
	ldr	r3, [r5, #80]	@ D.40026, g_SdecFunc.pfun_iMediaSoftDEC_Destroy
	cmp	r3, #0	@ D.40026,
	beq	.L2223	@,
	add	sl, r6, #250880	@, D.40013,
	add	r0, sl, #616	@,,
	blx	r3	@ D.40026
	b	.L2223	@
.L2232:
	mov	r0, r4	@, ChanID
	bl	VDMDRV_ResetVDH	@
	b	.L2224	@
.L2229:
	movw	r1, #:lower16:.LC327	@,
	movw	r3, #:lower16:.LC329	@,
	movt	r1, #:upper16:.LC327	@,
	movt	r3, #:upper16:.LC329	@,
	movw	r2, #2479	@,
	mov	r0, #0	@,
.L2226:
	bl	dprint_vfmw	@
	bl	VCTRL_EnableAllInt	@
	add	r0, r5, #504	@, tmp217,
	bl	OSAL_SpinUnLockIRQ	@
	mvn	r0, #0	@ D.40011,
	b	.L2219	@
.L2230:
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinUnLockIRQ	@
	add	r0, r5, #504	@, tmp217,
	bl	OSAL_SpinUnLockIRQ	@
	mvn	r0, #0	@ D.40011,
	b	.L2219	@
.L2227:
	movw	r1, #:lower16:.LC327	@,
	movw	r3, #:lower16:.LC6	@,
	movw	r2, #2461	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC327	@,
	movt	r3, #:upper16:.LC6	@,
	b	.L2226	@
.L2228:
	movw	r1, #:lower16:.LC327	@,
	movw	r3, #:lower16:.LC328	@,
	mov	r0, r6	@, D.40013
	movw	r2, #2468	@,
	movt	r1, #:upper16:.LC327	@,
	movt	r3, #:upper16:.LC328	@,
	b	.L2226	@
.L2234:
	.align	2
.L2233:
	.word	.LANCHOR0+504
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
	mvnne	r0, #0	@ D.39143,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	ldr	r0, [r4, #0]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r0, #0	@ s_pstVfmwChan,
	beq	.L2240	@,
	mov	r0, #0	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2240:
	ldr	r1, [r4, #4]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r1, #0	@ s_pstVfmwChan,
	beq	.L2241	@,
	mov	r0, #1	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2241:
	ldr	r2, [r4, #8]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r2, #0	@ s_pstVfmwChan,
	beq	.L2242	@,
	mov	r0, #2	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2242:
	ldr	r5, [r4, #12]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r5, #0	@ s_pstVfmwChan,
	beq	.L2243	@,
	mov	r0, #3	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2243:
	ldr	ip, [r4, #16]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	ip, #0	@ s_pstVfmwChan,
	beq	.L2244	@,
	mov	r0, #4	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2244:
	ldr	lr, [r4, #20]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	lr, #0	@ s_pstVfmwChan,
	beq	.L2245	@,
	mov	r0, #5	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2245:
	ldr	r3, [r4, #24]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	beq	.L2246	@,
	mov	r0, #6	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2246:
	ldr	r0, [r4, #28]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r0, #0	@ s_pstVfmwChan,
	beq	.L2247	@,
	mov	r0, #7	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2247:
	ldr	r1, [r4, #32]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r1, #0	@ s_pstVfmwChan,
	beq	.L2248	@,
	mov	r0, #8	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2248:
	ldr	r2, [r4, #36]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r2, #0	@ s_pstVfmwChan,
	beq	.L2249	@,
	mov	r0, #9	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2249:
	ldr	r5, [r4, #40]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r5, #0	@ s_pstVfmwChan,
	beq	.L2250	@,
	mov	r0, #10	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2250:
	ldr	ip, [r4, #44]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	ip, #0	@ s_pstVfmwChan,
	beq	.L2251	@,
	mov	r0, #11	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2251:
	ldr	lr, [r4, #48]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	lr, #0	@ s_pstVfmwChan,
	beq	.L2252	@,
	mov	r0, #12	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2252:
	ldr	r3, [r4, #52]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	beq	.L2253	@,
	mov	r0, #13	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2253:
	ldr	r0, [r4, #56]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r0, #0	@ s_pstVfmwChan,
	beq	.L2254	@,
	mov	r0, #14	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2254:
	ldr	r1, [r4, #60]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r1, #0	@ s_pstVfmwChan,
	beq	.L2255	@,
	mov	r0, #15	@,
	bl	VCTRL_DestroyChanWithOption	@
.L2255:
	bl	FSP_Exit	@
	mov	r5, #0	@ i,
	mov	r2, #3	@ tmp171,
	str	r2, [r4, #144]	@ tmp171, s_VfmwCTrl.eTaskCommand
	b	.L2257	@
.L2262:
	bl	msleep	@
	ldr	r3, [r4, #140]	@ s_VfmwCTrl.eTaskState, s_VfmwCTrl.eTaskState
	mov	r0, #10	@,
	cmp	r3, #0	@ s_VfmwCTrl.eTaskState,
	beq	.L2256	@,
	bl	msleep	@
	cmp	r5, #50	@ i,
	beq	.L2256	@,
.L2257:
	ldr	ip, [r4, #140]	@ s_VfmwCTrl.eTaskState, s_VfmwCTrl.eTaskState
	add	r5, r5, #1	@ tmp187, i,
	mov	r0, #10	@,
	add	r5, r5, #1	@ i, tmp187,
	cmp	ip, #0	@ s_VfmwCTrl.eTaskState,
	bne	.L2262	@,
.L2256:
	mov	r1, #64	@,
	ldr	r0, .L2263	@,
	mov	r5, #0	@ tmp175,
	str	r5, [r4, #144]	@ tmp175, s_VfmwCTrl.eTaskCommand
	bl	__memzero	@
	ldr	r0, .L2263+4	@,
	bl	CloseDrivers	@
	bl	DBG_DestroyTracer	@
	mov	r0, r5	@ D.39143, tmp175
	str	r5, [r4, #104]	@ tmp175, s_VfmwCTrl.s32IsVCTRLOpen
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L2264:
	.align	2
.L2263:
	.word	.LANCHOR3-1476
	.word	.LANCHOR0+160
	.fnend
	.size	VCTRL_CloseVfmw, .-VCTRL_CloseVfmw
	.align	2
	.global	VCTRL_CreateChanWithOption
	.type	VCTRL_CreateChanWithOption, %function
VCTRL_CreateChanWithOption:
	.fnstart
.LFB1567:
	@ args = 0, pretend = 0, frame = 200
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #212
	sub	sp, sp, #212	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	sub	r7, fp, #56	@ tmp702,,
	sub	sl, fp, #68	@ tmp701,,
	mov	r5, r0	@ eCapLevel, eCapLevel
	mov	r4, r1	@ pChanOption, pChanOption
	mov	r0, r7	@, tmp702
	mov	r1, #12	@,
	sub	r6, fp, #80	@ tmp700,,
	mov	r8, r2	@ flag, flag
	str	r3, [fp, #-228]	@ OneChanMemFlag, %sfp
	bl	__memzero	@
	sub	r0, fp, #204	@,,
	mov	r1, #12	@,
	str	r0, [fp, #-232]	@, %sfp
	mov	r0, sl	@, tmp701
	bl	__memzero	@
	mov	r0, r6	@, tmp700
	mov	r1, #12	@,
	bl	__memzero	@
	sub	r0, fp, #204	@,,
	mov	r1, #96	@,
	bl	__memzero	@
	rsbs	r0, r8, #1	@ tmp192, flag
	movcc	r0, #0	@ tmp192
	cmp	r5, #25	@ eCapLevel,
	movw	r1, #:lower16:4780440	@ tmp718,
	movt	r1, #:upper16:4780440	@ tmp718,
	movw	r2, #:lower16:11613104	@ tmp717,
	moveq	r0, #0	@, tmp192,
	cmp	r5, #26	@ eCapLevel,
	movt	r2, #:upper16:11613104	@ tmp717,
	movw	r3, #:lower16:.LANCHOR4	@ tmp185,
	movne	r2, r1	@ tmp717, tmp718
	movt	r3, #:upper16:.LANCHOR4	@ tmp185,
	cmp	r0, #0	@ tmp192,
	str	r2, [fp, #-212]	@ tmp717, %sfp
	str	r4, [r3, #-3532]	@ pChanOption, pOption
	bne	.L2356	@,
	ldr	r3, [r4, #4]	@ D.39722, <variable>.Purpose
	cmp	r3, #2	@ D.39722,
	bhi	.L2357	@,
	beq	.L2358	@,
	cmp	r3, #1	@ D.39722,
	beq	.L2359	@,
.L2273:
	ldr	lr, [r4, #120]	@ <variable>.u32DynamicFrameStoreAllocEn, <variable>.u32DynamicFrameStoreAllocEn
	mov	r3, r8	@, flag
	mov	r0, r5	@, eCapLevel
	mov	r1, r4	@, pChanOption
	cmp	lr, #1	@ <variable>.u32DynamicFrameStoreAllocEn,
	sub	r2, fp, #92	@,,
	movhi	lr, #0	@ tmp212,
	strhi	lr, [r4, #120]	@ tmp212, <variable>.u32DynamicFrameStoreAllocEn
	bl	VCTRL_GetChanMemSizeWithOption	@
	subs	r3, r0, #0	@ D.39763,
	bne	.L2360	@,
	ldr	r2, [r4, #8]	@ D.39767, <variable>.MemAllocMode
	cmp	r2, #1	@ D.39767,
	beq	.L2361	@,
	cmp	r2, #2	@ D.39767,
	beq	.L2362	@,
	cmp	r2, #3	@ D.39767,
	bne	.L2295	@,
	ldr	r1, [r4, #112]	@ <variable>.MemDetail.ChanMemCtx.VirAddr, <variable>.MemDetail.ChanMemCtx.VirAddr
	cmp	r1, #0	@ <variable>.MemDetail.ChanMemCtx.VirAddr,
	beq	.L2296	@,
	ldr	r0, [r4, #116]	@ <variable>.MemDetail.ChanMemCtx.Length, <variable>.MemDetail.ChanMemCtx.Length
	cmp	r0, #0	@ <variable>.MemDetail.ChanMemCtx.Length,
	bne	.L2297	@,
.L2296:
	movw	r0, #:lower16:.LC335	@,
	mov	r1, #0	@,
	movt	r0, #:upper16:.LC335	@,
	sub	r3, fp, #108	@,,
	ldr	r2, [fp, #-84]	@, DetailMemSize.ChanCtxDetailMem
	mov	r6, #1	@ tmp284,
	str	r6, [sp, #0]	@ tmp284,
	bl	MEM_AllocMemBlock	@
	cmp	r0, #0	@,
	bne	.L2363	@,
	ldr	r1, [fp, #-104]	@, MemRecord.VirAddr
	ldr	r0, [fp, #-100]	@, MemRecord.PhyAddr
	ldr	r2, [fp, #-96]	@, MemRecord.Length
	str	r6, [fp, #-216]	@ tmp284, %sfp
	bl	MEM_AddMemRecord	@
	ldr	r1, [fp, #-100]	@ MemRecord.PhyAddr, MemRecord.PhyAddr
	ldr	r3, [fp, #-104]	@ MemRecord.VirAddr, MemRecord.VirAddr
	ldr	ip, [fp, #-96]	@ MemRecord.Length, MemRecord.Length
	str	r1, [fp, #-80]	@ MemRecord.PhyAddr, ChanMemCtx.PhyAddr
	str	r3, [fp, #-76]	@ MemRecord.VirAddr, ChanMemCtx.VirAddr
	str	ip, [fp, #-72]	@ MemRecord.Length, ChanMemCtx.Length
.L2299:
	ldr	ip, [r4, #88]	@ <variable>.MemDetail.ChanMemVdh.VirAddr, <variable>.MemDetail.ChanMemVdh.VirAddr
	cmp	ip, #0	@ <variable>.MemDetail.ChanMemVdh.VirAddr,
	beq	.L2301	@,
	ldr	r3, [r4, #92]	@ <variable>.MemDetail.ChanMemVdh.Length, <variable>.MemDetail.ChanMemVdh.Length
	cmp	r3, #0	@ <variable>.MemDetail.ChanMemVdh.Length,
	beq	.L2301	@,
	add	r2, r4, #84	@ tmp319, pChanOption,
	ldr	ip, [r4, #120]	@ <variable>.u32DynamicFrameStoreAllocEn, <variable>.u32DynamicFrameStoreAllocEn
	ldmia	r2, {r0, r1, r2}	@ tmp319,,,
	cmp	ip, #1	@ <variable>.u32DynamicFrameStoreAllocEn,
	stmia	r7, {r0, r1, r2}	@ tmp702,,,
	beq	.L2307	@,
	ldr	r2, [fp, #-48]	@ prephitmp.6061, ChanMemVDH.Length
	ldr	ip, [fp, #-92]	@ prephitmp.6062, DetailMemSize.VdhDetailMem
	cmp	r2, ip	@ prephitmp.6061, prephitmp.6062
	blt	.L2364	@,
.L2308:
	ldr	r0, [fp, #-56]	@, ChanMemVDH.PhyAddr
	mov	lr, #0	@,
	ldr	r1, [fp, #-52]	@, ChanMemVDH.VirAddr
	str	lr, [fp, #-220]	@, %sfp
	bl	MEM_AddMemRecord	@
.L2306:
	ldr	r1, [r4, #100]	@ <variable>.MemDetail.ChanMemScd.VirAddr, <variable>.MemDetail.ChanMemScd.VirAddr
	cmp	r1, #0	@ <variable>.MemDetail.ChanMemScd.VirAddr,
	beq	.L2310	@,
	ldr	ip, [r4, #104]	@ <variable>.MemDetail.ChanMemScd.Length, <variable>.MemDetail.ChanMemScd.Length
	cmp	ip, #0	@ <variable>.MemDetail.ChanMemScd.Length,
	beq	.L2310	@,
	add	ip, r4, #96	@ tmp344, pChanOption,
	ldr	r3, [r4, #4]	@ temp.6086, <variable>.Purpose
	ldmia	ip, {r0, r1, r2}	@ tmp344,,,
	cmp	r3, #2	@ temp.6086,
	stmia	sl, {r0, r1, r2}	@ tmp701,,,
	beq	.L2316	@,
	ldr	r1, [fp, #-64]	@ temp.6087, ChanMemScd.VirAddr
	cmp	r1, #0	@ temp.6087,
	beq	.L2317	@,
	ldr	r2, [fp, #-60]	@ prephitmp.5979, ChanMemScd.Length
	ldr	lr, [fp, #-88]	@ DetailMemSize.ScdDetailMem, DetailMemSize.ScdDetailMem
	cmp	r2, lr	@ prephitmp.5979, DetailMemSize.ScdDetailMem
	bge	.L2318	@,
.L2317:
	cmp	r3, #1	@ temp.6086,
	ldrne	r2, [fp, #-60]	@ prephitmp.5979, ChanMemScd.Length
	beq	.L2365	@,
.L2318:
	ldr	r0, [fp, #-68]	@, ChanMemScd.PhyAddr
	mov	r7, #0	@,
	str	r7, [fp, #-224]	@, %sfp
	bl	MEM_AddMemRecord	@
.L2286:
	movw	r7, #:lower16:.LANCHOR0	@ tmp707,
	movt	r7, #:upper16:.LANCHOR0	@ tmp707,
	add	r0, r7, #504	@, tmp707,
	bl	OSAL_SpinLockIRQ	@
	bl	VCTRL_MaskAllInt	@
	ldr	r3, [r7, #0]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	beq	.L2355	@,
	ldr	ip, [r7, #4]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	ip, #0	@ s_pstVfmwChan,
	moveq	ip, #1	@,
	streq	ip, [fp, #-208]	@, %sfp
	moveq	r6, ip	@ ChanID.6232,
	beq	.L2323	@,
	ldr	lr, [r7, #8]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	lr, #0	@ s_pstVfmwChan,
	moveq	lr, #2	@,
	streq	lr, [fp, #-208]	@, %sfp
	moveq	r6, lr	@ ChanID.6232,
	beq	.L2323	@,
	ldr	r3, [r7, #12]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	moveq	r0, #3	@,
	streq	r0, [fp, #-208]	@, %sfp
	moveq	r6, r0	@ ChanID.6232,
	beq	.L2323	@,
	ldr	r1, [r7, #16]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r1, #0	@ s_pstVfmwChan,
	moveq	r1, #4	@,
	streq	r1, [fp, #-208]	@, %sfp
	moveq	r6, r1	@ ChanID.6232,
	beq	.L2323	@,
	ldr	r2, [r7, #20]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r2, #0	@ s_pstVfmwChan,
	moveq	r2, #5	@,
	streq	r2, [fp, #-208]	@, %sfp
	moveq	r6, r2	@ ChanID.6232,
	beq	.L2323	@,
	ldr	r3, [r7, #24]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	addeq	r3, r3, #6	@,,
	streq	r3, [fp, #-208]	@, %sfp
	moveq	r6, r3	@ ChanID.6232,
	beq	.L2323	@,
	ldr	r3, [r7, #28]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	moveq	r8, #7	@,
	streq	r8, [fp, #-208]	@, %sfp
	moveq	r6, r8	@ ChanID.6232,
	beq	.L2323	@,
	ldr	r3, [r7, #32]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	moveq	ip, #8	@,
	streq	ip, [fp, #-208]	@, %sfp
	moveq	r6, ip	@ ChanID.6232,
	beq	.L2323	@,
	ldr	ip, [r7, #36]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	ip, #0	@ s_pstVfmwChan,
	moveq	lr, #9	@,
	streq	lr, [fp, #-208]	@, %sfp
	moveq	r6, lr	@ ChanID.6232,
	beq	.L2323	@,
	ldr	lr, [r7, #40]	@ s_pstVfmwChan, s_pstVfmwChan
	movw	r6, #:lower16:.LANCHOR0	@ tmp372,
	movt	r6, #:upper16:.LANCHOR0	@ tmp372,
	cmp	lr, #0	@ s_pstVfmwChan,
	moveq	r0, #10	@,
	streq	r0, [fp, #-208]	@, %sfp
	moveq	r6, r0	@ ChanID.6232,
	beq	.L2323	@,
	ldr	r0, [r6, #44]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r0, #0	@ s_pstVfmwChan,
	moveq	r1, #11	@,
	streq	r1, [fp, #-208]	@, %sfp
	moveq	r6, r1	@ ChanID.6232,
	beq	.L2323	@,
	ldr	r1, [r6, #48]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r1, #0	@ s_pstVfmwChan,
	moveq	r2, #12	@,
	streq	r2, [fp, #-208]	@, %sfp
	moveq	r6, r2	@ ChanID.6232,
	beq	.L2323	@,
	ldr	r3, [r6, #52]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	beq	.L2366	@,
	ldr	r2, [r6, #56]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r2, #0	@ s_pstVfmwChan,
	moveq	r8, #14	@,
	streq	r8, [fp, #-208]	@, %sfp
	moveq	r6, r8	@ ChanID.6232,
	beq	.L2323	@,
	ldr	r3, [r6, #60]	@ s_pstVfmwChan, s_pstVfmwChan
	cmp	r3, #0	@ s_pstVfmwChan,
	beq	.L2338	@,
	mov	r2, #16	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC347	@,
	movt	r1, #:upper16:.LC347	@,
	bl	dprint_vfmw	@
	mvn	ip, #0	@,
	str	ip, [fp, #-208]	@, %sfp
	bl	VCTRL_EnableAllInt	@
	add	r0, r6, #504	@, tmp372,
	bl	OSAL_SpinUnLockIRQ	@
.L2269:
	ldr	r0, [fp, #-208]	@, %sfp
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L2359:
	ldr	r1, [r4, #36]	@ <variable>.s32MaxRefFrameNum, <variable>.s32MaxRefFrameNum
	cmp	r1, #0	@ <variable>.s32MaxRefFrameNum,
	blt	.L2274	@,
	ldr	r0, [r4, #12]	@ <variable>.s32MaxWidth, <variable>.s32MaxWidth
	cmp	r0, #31	@ <variable>.s32MaxWidth,
	ble	.L2274	@,
	ldr	ip, [r4, #16]	@ <variable>.s32MaxHeight, <variable>.s32MaxHeight
	cmp	ip, #31	@ <variable>.s32MaxHeight,
	ble	.L2274	@,
	ldr	lr, [r4, #60]	@ <variable>.s32SCDBufSize, <variable>.s32SCDBufSize
	cmp	lr, #262144	@ <variable>.s32SCDBufSize,
	blt	.L2274	@,
	ldr	r3, [r4, #48]	@ D.39747, <variable>.s32SupportH264
	cmp	r3, #1	@ D.39747,
	beq	.L2367	@,
	cmp	r3, #2	@ D.39747,
	bne	.L2273	@,
	ldr	r2, [r4, #20]	@ <variable>.s32MaxSliceNum, <variable>.s32MaxSliceNum
	cmp	r2, #0	@ <variable>.s32MaxSliceNum,
	ble	.L2274	@,
	ldr	r1, [r4, #24]	@ <variable>.s32MaxVpsNum, <variable>.s32MaxVpsNum
	cmp	r1, #0	@ <variable>.s32MaxVpsNum,
	ble	.L2274	@,
.L2353:
	ldr	r0, [r4, #28]	@ <variable>.s32MaxSpsNum, <variable>.s32MaxSpsNum
	cmp	r0, #0	@ <variable>.s32MaxSpsNum,
	ble	.L2274	@,
	ldr	ip, [r4, #32]	@ <variable>.s32MaxPpsNum, <variable>.s32MaxPpsNum
	cmp	ip, #0	@ <variable>.s32MaxPpsNum,
	bgt	.L2273	@,
.L2274:
	movw	r1, #:lower16:.LC23	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC23	@,
	mvn	r8, #0	@,
	str	r8, [fp, #-208]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2269	@
.L2297:
	add	r2, r4, #108	@ tmp294, pChanOption,
	ldr	lr, [fp, #-84]	@ DetailMemSize.ChanCtxDetailMem, DetailMemSize.ChanCtxDetailMem
	ldmia	r2, {r0, r1, r2}	@ tmp294,,,
	stmia	r6, {r0, r1, r2}	@ tmp700,,,
	ldr	r2, [fp, #-72]	@ temp.6048, ChanMemCtx.Length
	cmp	r2, lr	@ temp.6048, DetailMemSize.ChanCtxDetailMem
	blt	.L2368	@,
	ldr	r0, [fp, #-80]	@, ChanMemCtx.PhyAddr
	ldr	r1, [fp, #-76]	@, ChanMemCtx.VirAddr
	str	r3, [fp, #-216]	@ D.39763, %sfp
	bl	MEM_AddMemRecord	@
	b	.L2299	@
.L2301:
	ldr	r1, [r4, #120]	@ <variable>.u32DynamicFrameStoreAllocEn, <variable>.u32DynamicFrameStoreAllocEn
	cmp	r1, #1	@ <variable>.u32DynamicFrameStoreAllocEn,
	beq	.L2303	@,
	mov	lr, #0	@ tmp306,
	movw	r0, #:lower16:.LC337	@,
	mov	r1, lr	@, tmp306
	movt	r0, #:upper16:.LC337	@,
	sub	r3, fp, #108	@,,
	ldr	r2, [fp, #-92]	@, DetailMemSize.VdhDetailMem
	str	lr, [sp, #0]	@ tmp306,
	bl	MEM_AllocMemBlock	@
	cmp	r0, #0	@,
	bne	.L2369	@,
	ldr	r1, [fp, #-104]	@, MemRecord.VirAddr
	mov	r8, #1	@,
	ldr	r0, [fp, #-100]	@, MemRecord.PhyAddr
	ldr	r2, [fp, #-96]	@, MemRecord.Length
	str	r8, [fp, #-220]	@, %sfp
	bl	MEM_AddMemRecord	@
	ldr	r1, [fp, #-100]	@ MemRecord.PhyAddr, MemRecord.PhyAddr
	ldr	r3, [fp, #-104]	@ MemRecord.VirAddr, MemRecord.VirAddr
	ldr	ip, [fp, #-96]	@ MemRecord.Length, MemRecord.Length
	str	r1, [fp, #-56]	@ MemRecord.PhyAddr, ChanMemVDH.PhyAddr
	str	r3, [fp, #-52]	@ MemRecord.VirAddr, ChanMemVDH.VirAddr
	str	ip, [fp, #-48]	@ MemRecord.Length, ChanMemVDH.Length
	b	.L2306	@
.L2358:
	ldr	r3, [r4, #68]	@ <variable>.s32SlotWidth, <variable>.s32SlotWidth
	cmp	r3, #0	@ <variable>.s32SlotWidth,
	beq	.L2272	@,
	ldr	r2, [r4, #72]	@ <variable>.s32SlotHeight, <variable>.s32SlotHeight
	cmp	r2, #0	@ <variable>.s32SlotHeight,
	bne	.L2273	@,
.L2272:
	movw	r1, #:lower16:.LC22	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC22	@,
	mvn	r5, #0	@,
	str	r5, [fp, #-208]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2269	@
.L2361:
	add	r3, r4, #84	@ tmp217, pChanOption,
	add	ip, r4, #96	@ tmp219, pChanOption,
	add	lr, r4, #108	@ tmp221, pChanOption,
	ldmia	r3, {r0, r1, r2}	@ tmp217,,,
	stmia	r7, {r0, r1, r2}	@ tmp702,,,
	ldmia	ip, {r0, r1, r2}	@ tmp219,,,
	stmia	sl, {r0, r1, r2}	@ tmp701,,,
	ldmia	lr, {r0, r1, r2}	@ tmp221,,,
	stmia	r6, {r0, r1, r2}	@ tmp700,,,
	ldr	r2, [fp, #-76]	@ ChanMemCtx.VirAddr, ChanMemCtx.VirAddr
	cmp	r2, #0	@ ChanMemCtx.VirAddr,
	beq	.L2279	@,
	ldr	r0, [fp, #-84]	@ DetailMemSize.ChanCtxDetailMem, DetailMemSize.ChanCtxDetailMem
	ldr	r1, [fp, #-72]	@ ChanMemCtx.Length, ChanMemCtx.Length
	cmp	r1, r0	@ ChanMemCtx.Length, DetailMemSize.ChanCtxDetailMem
	blt	.L2279	@,
	ldr	lr, [fp, #-64]	@ ChanMemScd.VirAddr, ChanMemScd.VirAddr
	cmp	lr, #0	@ ChanMemScd.VirAddr,
	beq	.L2281	@,
	ldr	r3, [fp, #-88]	@ DetailMemSize.ScdDetailMem, DetailMemSize.ScdDetailMem
	ldr	ip, [fp, #-60]	@ ChanMemScd.Length, ChanMemScd.Length
	cmp	ip, r3	@ ChanMemScd.Length, DetailMemSize.ScdDetailMem
	blt	.L2281	@,
.L2282:
	ldr	r1, [fp, #-52]	@ D.39788, ChanMemVDH.VirAddr
	cmp	r1, #0	@ D.39788,
	beq	.L2283	@,
	ldr	r2, [fp, #-48]	@ D.39790, ChanMemVDH.Length
	ldr	r0, [fp, #-92]	@ DetailMemSize.VdhDetailMem, DetailMemSize.VdhDetailMem
	cmp	r2, r0	@ D.39790, DetailMemSize.VdhDetailMem
	blt	.L2283	@,
	ldr	r0, [fp, #-56]	@, ChanMemVDH.PhyAddr
	bl	MEM_AddMemRecord	@
	sub	r0, fp, #80
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_AddMemRecord	@
	ldr	r7, [r4, #4]	@ <variable>.Purpose, <variable>.Purpose
	cmp	r7, #2	@ <variable>.Purpose,
	beq	.L2370	@,
	ldr	r0, [fp, #-68]	@, ChanMemScd.PhyAddr
	mov	r8, #0	@,
	ldr	r1, [fp, #-64]	@, ChanMemScd.VirAddr
	ldr	r2, [fp, #-60]	@, ChanMemScd.Length
	str	r8, [fp, #-216]	@, %sfp
	str	r8, [fp, #-224]	@, %sfp
	str	r8, [fp, #-220]	@, %sfp
	bl	MEM_AddMemRecord	@
	b	.L2286	@
.L2303:
	mov	lr, #0	@ tmp315,
	str	lr, [fp, #-56]	@ tmp315, ChanMemVDH.PhyAddr
	str	lr, [fp, #-52]	@ tmp315, ChanMemVDH.VirAddr
	str	lr, [fp, #-220]	@ tmp315, %sfp
	str	lr, [fp, #-48]	@ tmp315, ChanMemVDH.Length
	b	.L2306	@
.L2281:
	ldr	r0, [r4, #4]	@ <variable>.Purpose, <variable>.Purpose
	cmp	r0, #1	@ <variable>.Purpose,
	bne	.L2282	@,
	movw	r1, #:lower16:.LC333	@,
	movw	r2, #1861	@,
	movt	r1, #:upper16:.LC333	@,
	bl	dprint_vfmw	@
	mvn	r1, #0	@,
	str	r1, [fp, #-208]	@, %sfp
	b	.L2269	@
.L2370:
	mov	lr, #0	@,
	str	lr, [fp, #-216]	@, %sfp
	str	lr, [fp, #-224]	@, %sfp
	str	lr, [fp, #-220]	@, %sfp
	b	.L2286	@
.L2367:
	ldr	r3, [r4, #20]	@ <variable>.s32MaxSliceNum, <variable>.s32MaxSliceNum
	cmp	r3, #0	@ <variable>.s32MaxSliceNum,
	bgt	.L2353	@,
	b	.L2274	@
.L2338:
	mov	r8, #15	@,
	str	r8, [fp, #-208]	@, %sfp
	mov	r6, r8	@ ChanID.6232,
.L2323:
	ldr	r0, [fp, #-212]	@, %sfp
	movw	sl, #:lower16:g_FrameRate	@ tmp387,
	movw	lr, #:lower16:g_LastFrameRate	@ tmp389,
	movt	sl, #:upper16:g_FrameRate	@ tmp387,
	sub	r1, r0, #207872	@ __n,,
	ldr	r0, [fp, #-76]	@ prephitmp.5975, ChanMemCtx.VirAddr
	sub	r1, r1, #8	@ __n, __n,
	movt	lr, #:upper16:g_LastFrameRate	@ tmp389,
	cmp	r1, #0	@ __n,
	mov	r9, #30	@ tmp388,
	movw	r8, #:lower16:.LANCHOR0	@ tmp391,
	str	r0, [r7, r6, asl #2]	@ prephitmp.5975, s_pstVfmwChan
	str	r9, [lr, r6, asl #2]	@ tmp388, g_LastFrameRate
	movt	r8, #:upper16:.LANCHOR0	@ tmp391,
	str	r9, [sl, r6, asl #2]	@ tmp388, g_FrameRate
	beq	.L2339	@,
	bl	__memzero	@
	ldr	r2, [fp, #-208]	@, %sfp
	ldr	r0, [r8, r2, asl #2]	@ prephitmp.5975, s_pstVfmwChan
.L2339:
	add	r9, r0, #1760	@, prephitmp.5975,
	mov	r1, r4	@, pChanOption
	add	r0, r9, #8	@,,
	mov	r2, #148	@,
	bl	memcpy	@
	ldr	r3, [r7, r6, asl #2]	@ tmp401, s_pstVfmwChan
	ldr	r8, [fp, #-212]	@, %sfp
	mov	r9, #0	@ tmp408,
	mov	r1, #19	@ tmp416,
	movw	r2, #:lower16:251488	@ tmp419,
	movt	r2, #:upper16:251488	@ tmp419,
	add	lr, r6, r6, asl #1	@, tmp429, ChanID.6232, ChanID.6232,
	str	r8, [r3, #1712]	@, <variable>.stSynExtraData.s32BasicCtxSize
	movw	r0, #:lower16:s_SmIIS	@ tmp425,
	ldr	sl, [r7, r6, asl #2]	@ tmp403, s_pstVfmwChan
	movt	r0, #:upper16:s_SmIIS	@ tmp425,
	add	lr, r0, lr, asl #4	@, tmp431, tmp425, tmp429,
	movw	r3, #:lower16:s_pFspInst	@ tmp434,
	movt	r3, #:upper16:s_pFspInst	@ tmp434,
	mov	r0, r6	@, ChanID.6232
	str	r5, [sl, #40]	@ eCapLevel, <variable>.eChanCapLevel
	mvn	sl, #0	@ tmp713,
	ldr	ip, [r7, r6, asl #2]	@ tmp405, s_pstVfmwChan
	str	r9, [fp, #-244]	@ tmp408, %sfp
	str	r5, [ip, #1072]	@ eCapLevel, <variable>.stSynExtraData.eCapLevel
	ldr	r5, [r7, r6, asl #2]	@ tmp407, s_pstVfmwChan
	str	r9, [r5, #1728]	@ tmp408, <variable>.stSynExtraData.s32MoreGapEnable
	ldr	r8, [r7, r6, asl #2]	@ tmp410, s_pstVfmwChan
	str	r6, [r8, #8]	@ ChanID.6232, <variable>.s32ChanID
	ldr	r5, [r4, #0]	@ <variable>.eAdapterType, <variable>.eAdapterType
	ldr	ip, [r7, r6, asl #2]	@ tmp412, s_pstVfmwChan
	str	r5, [ip, #36]	@ <variable>.eAdapterType, <variable>.eAdapterType
	ldr	r8, [r7, r6, asl #2]	@ tmp415, s_pstVfmwChan
	str	r1, [r8, #1032]	@ tmp416, <variable>.eVidStd
	ldr	ip, [r7, r6, asl #2]	@ tmp418, s_pstVfmwChan
	str	r1, [ip, r2]	@ tmp416, <variable>.stSynCtx.eVidStd
	ldr	r2, [r7, r6, asl #2]	@ tmp422, s_pstVfmwChan
	str	r9, [r2, #32]	@ tmp408, <variable>.MatchVdhIdPlus1
	ldr	r8, [r7, r6, asl #2]	@ temp.6136, s_pstVfmwChan
	add	ip, r8, #1952	@ tmp433, temp.6136,
	add	r5, r8, #206848	@ tmp435, temp.6136,
	str	r5, [r3, r6, asl #2]	@ tmp435, s_pFspInst
	str	ip, [lr, #40]	@ tmp433, <variable>.pSmInstArray
	bl	VCTRL_ResetChan	@
	ldr	r1, [r7, r6, asl #2]	@ tmp437, s_pstVfmwChan
	ldr	r2, [fp, #-220]	@, %sfp
	movw	lr, #:lower16:249200	@ tmp444,
	movt	lr, #:upper16:249200	@ tmp444,
	movw	ip, #:lower16:249204	@ tmp448,
	movt	ip, #:upper16:249204	@ tmp448,
	movw	r0, #:lower16:249212	@ tmp452,
	str	r2, [r1, #256]	@, <variable>.s32SelfAllocChanMem_vdh
	movt	r0, #:upper16:249212	@ tmp452,
	ldr	r3, [r7, r6, asl #2]	@ tmp439, s_pstVfmwChan
	movw	r1, #:lower16:249216	@ tmp456,
	ldr	r5, [fp, #-224]	@, %sfp
	movt	r1, #:upper16:249216	@ tmp456,
	movw	r2, #:lower16:249208	@ tmp460,
	movt	r2, #:upper16:249208	@ tmp460,
	str	r5, [r3, #260]	@, <variable>.s32SelfAllocChanMem_scd
	movw	r3, #:lower16:249224	@ tmp464,
	ldr	r8, [fp, #-216]	@, %sfp
	movt	r3, #:upper16:249224	@ tmp464,
	ldr	r5, [r7, r6, asl #2]	@, s_pstVfmwChan
	str	r8, [r5, #264]	@, <variable>.s32SelfAllocChanMem_ctx
	ldr	r8, [r7, r6, asl #2]	@ tmp443, s_pstVfmwChan
	str	r9, [r8, lr]	@ tmp408, <variable>.s32CurFsSize
	ldr	r5, [r7, r6, asl #2]	@ tmp447, s_pstVfmwChan
	str	r9, [r5, ip]	@ tmp408, <variable>.s32RefNum
	ldr	lr, [r7, r6, asl #2]	@ tmp451, s_pstVfmwChan
	str	r9, [lr, r0]	@ tmp408, <variable>.s32PreAllocFrmNum
	ldr	r8, [r7, r6, asl #2]	@ tmp455, s_pstVfmwChan
	str	r9, [r8, r1]	@ tmp408, <variable>.s32MMZFrmNum
	ldr	ip, [r7, r6, asl #2]	@ tmp459, s_pstVfmwChan
	str	r9, [ip, r2]	@ tmp408, <variable>.s32NeededFrameNum
	ldr	r5, [r7, r6, asl #2]	@ tmp463, s_pstVfmwChan
	str	r9, [r5, r3]	@ tmp408, <variable>.s32RefNumChanged
	ldr	r8, [fp, #-244]	@ u32i, %sfp
.L2340:
	add	r3, r8, r8, asl #2	@, tmp471, u32i, u32i,
	ldr	r2, [r7, r6, asl #2]	@ tmp467, s_pstVfmwChan
	add	r5, r8, #1	@ tmp716, u32i,
	mov	r1, #16	@,
	mov	lr, r3, asl #2	@ tmp472, tmp471,
	add	r8, r5, #1	@ u32i, tmp716,
	add	r0, lr, r2	@ tmp473, tmp472, tmp467
	add	ip, lr, #248832	@ tmp482, tmp472,
	add	r9, r0, #248832	@ tmp474, tmp473,
	add	r3, ip, #400	@ tmp482, tmp482,
	add	r2, r9, #416	@ tmp474, tmp474,
	movw	r9, #:lower16:.LANCHOR0	@ tmp720,
	movt	r9, #:upper16:.LANCHOR0	@ tmp720,
	strb	sl, [r2, #0]	@ tmp713, <variable>.u8BufferNodeState
	ldr	lr, [r7, r6, asl #2]	@ tmp485, s_pstVfmwChan
	add	r0, r3, lr	@, tmp482, tmp485
	bl	__memzero	@
	add	r0, r5, r5, asl #2	@, tmp724, tmp716, tmp716,
	ldr	ip, [r7, r6, asl #2]	@ tmp721, s_pstVfmwChan
	mov	r1, #16	@,
	mov	r5, r0, asl #2	@ tmp725, tmp724,
	add	r3, r5, ip	@ tmp726, tmp725, tmp721
	add	r2, r5, #248832	@ tmp730, tmp725,
	add	r0, r3, #248832	@ tmp727, tmp726,
	add	r5, r2, #400	@ tmp730, tmp730,
	add	ip, r0, #416	@ tmp727, tmp727,
	strb	sl, [ip, #0]	@ tmp713, <variable>.u8BufferNodeState
	ldr	r2, [r7, r6, asl #2]	@ tmp731, s_pstVfmwChan
	add	r0, r5, r2	@, tmp730, tmp731
	bl	__memzero	@
	cmp	r8, #64	@ u32i,
	bne	.L2340	@,
	ldr	r3, [r9, r6, asl #2]	@ tmp489, s_pstVfmwChan
	mov	r1, #948	@,
	mov	r5, #0	@ tmp499,
	add	lr, r3, #249856	@, tmp489,
	add	r0, lr, #656	@,,
	bl	__memzero	@
	ldr	r2, [r9, r6, asl #2]	@ tmp493, s_pstVfmwChan
	mov	r1, #24	@,
	add	r0, r2, #250880	@, tmp493,
	add	r0, r0, #580	@,,
	bl	__memzero	@
	add	ip, r9, r6, asl #2	@, tmp497, tmp720, ChanID.6232,
	str	r5, [ip, #516]	@ tmp499, s_ChanControlState
	ldr	r1, [r4, #8]	@ <variable>.MemAllocMode, <variable>.MemAllocMode
	cmp	r1, #3	@ <variable>.MemAllocMode,
	beq	.L2371	@,
	ldr	r2, [fp, #-208]	@, %sfp
	ldr	r3, [r9, r2, asl #2]	@ prephitmp.5997, s_pstVfmwChan
.L2342:
	mov	r1, #0	@ tmp527,
	str	r1, [r3, #188]	@ tmp527, <variable>.s32OneChanMem
.L2343:
	ldr	r2, [r7, r6, asl #2]	@ tmp529, s_pstVfmwChan
	movw	lr, #:lower16:249192	@ tmp563,
	ldr	ip, [fp, #-56]	@ ChanMemVDH.PhyAddr, ChanMemVDH.PhyAddr
	movt	lr, #:upper16:249192	@ tmp563,
	mov	r1, #0	@ tmp564,
	movw	r3, #:lower16:.LANCHOR0	@ tmp528,
	movt	r3, #:upper16:.LANCHOR0	@ tmp528,
	str	ip, [r2, #216]	@ ChanMemVDH.PhyAddr, <variable>.stChanMem_vdh.PhyAddr
	ldr	r0, [fp, #-52]	@ ChanMemVDH.VirAddr, ChanMemVDH.VirAddr
	ldr	r5, [r7, r6, asl #2]	@ tmp532, s_pstVfmwChan
	str	r0, [r5, #212]	@ ChanMemVDH.VirAddr, <variable>.stChanMem_vdh.VirAddr
	ldr	ip, [fp, #-48]	@ ChanMemVDH.Length, ChanMemVDH.Length
	ldr	r2, [r7, r6, asl #2]	@ tmp535, s_pstVfmwChan
	str	ip, [r2, #220]	@ ChanMemVDH.Length, <variable>.stChanMem_vdh.Length
	ldr	r0, [fp, #-68]	@ ChanMemScd.PhyAddr, ChanMemScd.PhyAddr
	ldr	r5, [r7, r6, asl #2]	@ tmp538, s_pstVfmwChan
	str	r0, [r5, #232]	@ ChanMemScd.PhyAddr, <variable>.stChanMem_scd.PhyAddr
	ldr	ip, [fp, #-64]	@ ChanMemScd.VirAddr, ChanMemScd.VirAddr
	ldr	r2, [r7, r6, asl #2]	@ tmp541, s_pstVfmwChan
	str	ip, [r2, #228]	@ ChanMemScd.VirAddr, <variable>.stChanMem_scd.VirAddr
	ldr	r0, [fp, #-60]	@ ChanMemScd.Length, ChanMemScd.Length
	ldr	r5, [r7, r6, asl #2]	@ tmp544, s_pstVfmwChan
	str	r0, [r5, #236]	@ ChanMemScd.Length, <variable>.stChanMem_scd.Length
	ldr	ip, [fp, #-80]	@ ChanMemCtx.PhyAddr, ChanMemCtx.PhyAddr
	ldr	r2, [r7, r6, asl #2]	@ tmp547, s_pstVfmwChan
	str	ip, [r2, #248]	@ ChanMemCtx.PhyAddr, <variable>.stChanMem_ctx.PhyAddr
	ldr	r0, [fp, #-76]	@ ChanMemCtx.VirAddr, ChanMemCtx.VirAddr
	ldr	r5, [r7, r6, asl #2]	@ tmp550, s_pstVfmwChan
	str	r0, [r5, #244]	@ ChanMemCtx.VirAddr, <variable>.stChanMem_ctx.VirAddr
	ldr	ip, [fp, #-72]	@ ChanMemCtx.Length, ChanMemCtx.Length
	ldr	r2, [r7, r6, asl #2]	@ tmp553, s_pstVfmwChan
	str	ip, [r2, #252]	@ ChanMemCtx.Length, <variable>.stChanMem_ctx.Length
	ldr	r0, [fp, #-56]	@ ChanMemVDH.PhyAddr, ChanMemVDH.PhyAddr
	ldr	r5, [r7, r6, asl #2]	@ tmp556, s_pstVfmwChan
	str	r0, [r5, #288]	@ ChanMemVDH.PhyAddr, <variable>.s32SdecMemAddr
	ldr	ip, [fp, #-48]	@ ChanMemVDH.Length, ChanMemVDH.Length
	ldr	r2, [r7, r6, asl #2]	@ tmp559, s_pstVfmwChan
	str	ip, [r2, #292]	@ ChanMemVDH.Length, <variable>.s32SdecMemSize
	ldr	r0, [r7, r6, asl #2]	@ tmp562, s_pstVfmwChan
	str	r1, [r0, lr]	@ tmp564, <variable>.FspInst.eFspPartitionState
	ldr	r2, [r7, r6, asl #2]	@ temp.6184, s_pstVfmwChan
	ldr	r5, [r2, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r5, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	beq	.L2344	@,
	ldr	r0, [fp, #-56]	@ ChanMemVDH.PhyAddr, ChanMemVDH.PhyAddr
	ldr	ip, [r2, #280]	@ <variable>.s32OffLineDNRMemSize, <variable>.s32OffLineDNRMemSize
	ldr	lr, [r2, #4]	@ <variable>.s32BtlMemSize, <variable>.s32BtlMemSize
	add	r5, ip, r0	@ tmp567, <variable>.s32OffLineDNRMemSize, ChanMemVDH.PhyAddr
	add	r1, r5, lr	@ tmp571, tmp567, <variable>.s32BtlMemSize
	str	r1, [r2, #268]	@ tmp571, <variable>.s32VdmChanMemAddr
	ldr	r2, [r3, r6, asl #2]	@ temp.6187, s_pstVfmwChan
	ldr	ip, [fp, #-48]	@ ChanMemVDH.Length, ChanMemVDH.Length
	ldr	r0, [r2, #280]	@ <variable>.s32OffLineDNRMemSize, <variable>.s32OffLineDNRMemSize
	ldr	lr, [r2, #4]	@ <variable>.s32BtlMemSize, <variable>.s32BtlMemSize
	rsb	r5, r0, ip	@ tmp573, <variable>.s32OffLineDNRMemSize, ChanMemVDH.Length
	rsb	r1, lr, r5	@ tmp576, <variable>.s32BtlMemSize, tmp573
	sub	r0, r1, #16	@ tmp578, tmp576,
	str	r0, [r2, #272]	@ tmp578, <variable>.s32VdmChanMemSize
	ldr	lr, [r3, r6, asl #2]	@ temp.6190, s_pstVfmwChan
	ldr	r5, [lr, #272]	@ <variable>.s32VdmChanMemSize, <variable>.s32VdmChanMemSize
	sub	ip, r5, #14848	@ tmp582, <variable>.s32VdmChanMemSize,
	str	ip, [lr, #272]	@ tmp582, <variable>.s32VdmChanMemSize
	ldr	r2, [r3, r6, asl #2]	@ temp.6191, s_pstVfmwChan
	ldr	r1, [r2, #272]	@ <variable>.s32VdmChanMemSize, <variable>.s32VdmChanMemSize
	sub	r0, r1, #32768	@ tmp586, <variable>.s32VdmChanMemSize,
	str	r0, [r2, #272]	@ tmp586, <variable>.s32VdmChanMemSize
	ldr	r2, [r3, r6, asl #2]	@ temp.6193, s_pstVfmwChan
	ldr	r5, [r2, #268]	@ <variable>.s32VdmChanMemAddr, <variable>.s32VdmChanMemAddr
	ldr	lr, [r2, #272]	@ <variable>.s32VdmChanMemSize, <variable>.s32VdmChanMemSize
	add	ip, r5, lr	@ tmp588, <variable>.s32VdmChanMemAddr, <variable>.s32VdmChanMemSize
	mov	lr, #14848	@ tmp595,
	add	r1, ip, #15	@ tmp591, tmp588,
	bic	r0, r1, #15	@ tmp592, tmp591,
	str	r0, [r2, #300]	@ tmp592, <variable>.s32BpdChanMemAddr
	ldr	r5, [r3, r6, asl #2]	@ tmp594, s_pstVfmwChan
	str	lr, [r5, #304]	@ tmp595, <variable>.s32BpdChanMemSize
	ldr	lr, [r3, r6, asl #2]	@ temp.6196, s_pstVfmwChan
	ldr	ip, [lr, #268]	@ <variable>.s32VdmChanMemAddr, <variable>.s32VdmChanMemAddr
	ldr	r1, [lr, #272]	@ <variable>.s32VdmChanMemSize, <variable>.s32VdmChanMemSize
	ldr	r5, [lr, #304]	@ <variable>.s32BpdChanMemSize, <variable>.s32BpdChanMemSize
	add	r2, ip, r1	@ tmp597, <variable>.s32VdmChanMemAddr, <variable>.s32VdmChanMemSize
	add	r0, r2, #15	@ tmp600, tmp597,
	add	r1, r0, r5	@ tmp601, tmp600, <variable>.s32BpdChanMemSize
	mov	r0, #32768	@ tmp606,
	bic	ip, r1, #15	@ tmp603, tmp601,
	str	ip, [lr, #308]	@ tmp603, <variable>.s32Vp8SegIdChanMemAddr
	ldr	r2, [r3, r6, asl #2]	@ tmp605, s_pstVfmwChan
	str	r0, [r2, #312]	@ tmp606, <variable>.s32Vp8SegIdChanMemSize
	ldr	lr, [fp, #-68]	@ ChanMemScd.PhyAddr, ChanMemScd.PhyAddr
	ldr	r5, [r3, r6, asl #2]	@ tmp608, s_pstVfmwChan
	str	lr, [r5, #284]	@ ChanMemScd.PhyAddr, <variable>.s32ScdChanMemAddr
	ldr	r1, [fp, #-60]	@ ChanMemScd.Length, ChanMemScd.Length
	ldr	r3, [r3, r6, asl #2]	@ tmp611, s_pstVfmwChan
	str	r1, [r3, #296]	@ ChanMemScd.Length, <variable>.s32ScdChanMemSize
.L2345:
	ldr	ip, [r7, r6, asl #2]	@ tmp653, s_pstVfmwChan
	mov	lr, #206848	@ tmp660,
	movw	r3, #:lower16:192808	@ tmp664,
	movt	r3, #:upper16:192808	@ tmp664,
	mov	r0, r6	@, ChanID.6232
	movw	r5, #:lower16:.LANCHOR0	@ tmp652,
	str	r6, [ip, #8]	@ ChanID.6232, <variable>.s32ChanID
	movt	r5, #:upper16:.LANCHOR0	@ tmp652,
	ldr	r1, [r7, r6, asl #2]	@ tmp655, s_pstVfmwChan
	str	r6, [r1, #176]	@ ChanID.6232, <variable>.s32SCDInstID
	ldr	r2, [r7, r6, asl #2]	@ tmp657, s_pstVfmwChan
	str	r6, [r2, #180]	@ ChanID.6232, <variable>.s32VDMInstID
	ldr	ip, [r7, r6, asl #2]	@ tmp659, s_pstVfmwChan
	strb	r6, [ip, lr]	@ ChanID.6232, <variable>.FspInst.s32InstID
	ldr	r1, [r7, r6, asl #2]	@ tmp663, s_pstVfmwChan
	str	r6, [r1, r3]	@ ChanID.6232, <variable>.SmInstArray.InstID
	bl	FSP_EnableInstance	@
	cmp	r0, #0	@,
	bne	.L2372	@,
	mov	r0, r6	@, ChanID.6232
	mov	r7, #1	@ tmp674,
	bl	SM_ClearInst	@
	ldr	r2, [r5, r6, asl #2]	@ tmp667, s_pstVfmwChan
	ldr	r0, [fp, #-212]	@, %sfp
	ldr	r1, [r2, #244]	@ <variable>.stChanMem_ctx.VirAddr, <variable>.stChanMem_ctx.VirAddr
	sub	ip, r0, #205824	@ tmp668,,
	sub	r3, ip, #8	@ tmp668, tmp668,
	mov	r0, r6	@, ChanID.6232
	add	r1, r3, r1	@, tmp668, <variable>.stChanMem_ctx.VirAddr
	bl	OpenUsdPool_WithMem	@
	ldr	ip, [r5, r6, asl #2]	@ tmp673, s_pstVfmwChan
	mov	r0, r6	@, ChanID.6232
	str	r7, [ip, #12]	@ tmp674, <variable>.s32IsOpen
	bl	VDMDRV_ClearChanIsDec	@
	bl	VCTRL_EnableAllInt	@
	bl	VDMDRV_ParamInit	@
	add	r0, r5, #504	@, tmp652,
	bl	OSAL_SpinUnLockIRQ	@
	str	r7, [r4, #52]	@ tmp674, <variable>.s32ScdLowdlyEnable
	mov	r0, r6	@, ChanID.6232
	bl	SM_AllocDSPCtxMem	@
	b	.L2269	@
.L2310:
	ldr	r2, [r4, #4]	@ <variable>.Purpose, <variable>.Purpose
	cmp	r2, #2	@ <variable>.Purpose,
	beq	.L2312	@,
	mov	lr, #0	@ tmp331,
	movw	r0, #:lower16:.LC339	@,
	mov	r1, lr	@, tmp331
	movt	r0, #:upper16:.LC339	@,
	sub	r3, fp, #108	@,,
	ldr	r2, [fp, #-88]	@, DetailMemSize.ScdDetailMem
	str	lr, [sp, #0]	@ tmp331,
	bl	MEM_AllocMemBlock	@
	cmp	r0, #0	@,
	bne	.L2373	@,
	ldr	r0, [fp, #-100]	@, MemRecord.PhyAddr
	mov	r7, #1	@,
	ldr	r1, [fp, #-104]	@, MemRecord.VirAddr
	str	r7, [fp, #-224]	@, %sfp
.L2354:
	ldr	r2, [fp, #-96]	@, MemRecord.Length
	bl	MEM_AddMemRecord	@
	ldr	ip, [fp, #-100]	@ MemRecord.PhyAddr, MemRecord.PhyAddr
	ldr	r1, [fp, #-104]	@ MemRecord.VirAddr, MemRecord.VirAddr
	ldr	r3, [fp, #-96]	@ MemRecord.Length, MemRecord.Length
	str	ip, [fp, #-68]	@ MemRecord.PhyAddr, ChanMemScd.PhyAddr
	str	r1, [fp, #-64]	@ MemRecord.VirAddr, ChanMemScd.VirAddr
	str	r3, [fp, #-60]	@ MemRecord.Length, ChanMemScd.Length
	b	.L2286	@
.L2344:
	str	r1, [r2, #268]	@ tmp564, <variable>.s32VdmChanMemAddr
	ldr	r2, [r3, r6, asl #2]	@ tmp615, s_pstVfmwChan
	str	r1, [r2, #272]	@ tmp564, <variable>.s32VdmChanMemSize
	ldr	ip, [fp, #-68]	@ ChanMemScd.PhyAddr, ChanMemScd.PhyAddr
	ldr	lr, [r3, r6, asl #2]	@ tmp618, s_pstVfmwChan
	str	ip, [lr, #284]	@ ChanMemScd.PhyAddr, <variable>.s32ScdChanMemAddr
	ldr	r5, [r3, r6, asl #2]	@ tmp621, s_pstVfmwChan
	ldr	r1, [fp, #-60]	@ ChanMemScd.Length, ChanMemScd.Length
	sub	r0, r1, #16	@ tmp623, ChanMemScd.Length,
	str	r0, [r5, #296]	@ tmp623, <variable>.s32ScdChanMemSize
	ldr	lr, [r3, r6, asl #2]	@ temp.6210, s_pstVfmwChan
	ldr	r2, [lr, #296]	@ <variable>.s32ScdChanMemSize, <variable>.s32ScdChanMemSize
	sub	ip, r2, #14848	@ tmp627, <variable>.s32ScdChanMemSize,
	str	ip, [lr, #296]	@ tmp627, <variable>.s32ScdChanMemSize
	ldr	r5, [r3, r6, asl #2]	@ temp.6211, s_pstVfmwChan
	ldr	r1, [r5, #296]	@ <variable>.s32ScdChanMemSize, <variable>.s32ScdChanMemSize
	sub	r0, r1, #32768	@ tmp631, <variable>.s32ScdChanMemSize,
	str	r0, [r5, #296]	@ tmp631, <variable>.s32ScdChanMemSize
	ldr	r5, [r3, r6, asl #2]	@ temp.6213, s_pstVfmwChan
	ldr	r2, [r5, #284]	@ <variable>.s32ScdChanMemAddr, <variable>.s32ScdChanMemAddr
	ldr	lr, [r5, #296]	@ <variable>.s32ScdChanMemSize, <variable>.s32ScdChanMemSize
	add	ip, r2, lr	@ tmp633, <variable>.s32ScdChanMemAddr, <variable>.s32ScdChanMemSize
	mov	lr, #14848	@ tmp640,
	add	r1, ip, #15	@ tmp636, tmp633,
	bic	r0, r1, #15	@ tmp637, tmp636,
	str	r0, [r5, #300]	@ tmp637, <variable>.s32BpdChanMemAddr
	ldr	r2, [r3, r6, asl #2]	@ tmp639, s_pstVfmwChan
	str	lr, [r2, #304]	@ tmp640, <variable>.s32BpdChanMemSize
	ldr	lr, [r3, r6, asl #2]	@ temp.6216, s_pstVfmwChan
	ldr	r5, [lr, #296]	@ <variable>.s32ScdChanMemSize, <variable>.s32ScdChanMemSize
	ldr	ip, [lr, #284]	@ <variable>.s32ScdChanMemAddr, <variable>.s32ScdChanMemAddr
	ldr	r2, [lr, #304]	@ <variable>.s32BpdChanMemSize, <variable>.s32BpdChanMemSize
	add	r1, ip, r5	@ tmp642, <variable>.s32ScdChanMemAddr, <variable>.s32ScdChanMemSize
	add	r0, r1, #15	@ tmp645, tmp642,
	add	r5, r0, r2	@ tmp646, tmp645, <variable>.s32BpdChanMemSize
	mov	r2, #32768	@ tmp651,
	bic	r1, r5, #15	@ tmp648, tmp646,
	str	r1, [lr, #308]	@ tmp648, <variable>.s32Vp8SegIdChanMemAddr
	ldr	r3, [r3, r6, asl #2]	@ tmp650, s_pstVfmwChan
	str	r2, [r3, #312]	@ tmp651, <variable>.s32Vp8SegIdChanMemSize
	b	.L2345	@
.L2371:
	ldr	r3, [r9, r6, asl #2]	@ prephitmp.5997, s_pstVfmwChan
	ldr	r2, [r3, #264]	@ <variable>.s32SelfAllocChanMem_ctx, <variable>.s32SelfAllocChanMem_ctx
	cmp	r2, #1	@ <variable>.s32SelfAllocChanMem_ctx,
	bne	.L2342	@,
	ldr	r1, [r3, #256]	@ <variable>.s32SelfAllocChanMem_vdh, <variable>.s32SelfAllocChanMem_vdh
	cmp	r1, #0	@ <variable>.s32SelfAllocChanMem_vdh,
	bne	.L2342	@,
	ldr	r5, [r3, #260]	@ <variable>.s32SelfAllocChanMem_scd, <variable>.s32SelfAllocChanMem_scd
	cmp	r5, #0	@ <variable>.s32SelfAllocChanMem_scd,
	bne	.L2342	@,
	ldr	r8, [fp, #-60]	@ ChanMemScd.Length, ChanMemScd.Length
	ldr	r1, [fp, #-68]	@ temp.6151, ChanMemScd.PhyAddr
	ldr	r0, [fp, #-56]	@ ChanMemVDH.PhyAddr, ChanMemVDH.PhyAddr
	add	ip, r1, r8	@ tmp507, temp.6151, ChanMemScd.Length
	ldr	r8, [fp, #-228]	@, %sfp
	cmp	r8, #1	@,
	cmpeq	ip, r0	@, tmp507, ChanMemVDH.PhyAddr
	bne	.L2342	@,
	str	r1, [r3, #200]	@ temp.6151, <variable>.stChanMem.PhyAddr
	ldr	ip, [fp, #-64]	@ ChanMemScd.VirAddr, ChanMemScd.VirAddr
	ldr	lr, [r9, r6, asl #2]	@ tmp516, s_pstVfmwChan
	str	ip, [lr, #196]	@ ChanMemScd.VirAddr, <variable>.stChanMem.VirAddr
	ldr	r3, [r9, r6, asl #2]	@ tmp519, s_pstVfmwChan
	ldr	r5, [fp, #-60]	@ ChanMemScd.Length, ChanMemScd.Length
	ldr	r0, [fp, #-48]	@ ChanMemVDH.Length, ChanMemVDH.Length
	add	r1, r0, r5	@ tmp522, ChanMemVDH.Length, ChanMemScd.Length
	str	r1, [r3, #204]	@ tmp522, <variable>.stChanMem.Length
	ldr	lr, [r9, r6, asl #2]	@ tmp524, s_pstVfmwChan
	str	r2, [lr, #188]	@ <variable>.s32SelfAllocChanMem_ctx, <variable>.s32OneChanMem
	b	.L2343	@
.L2312:
	ldr	lr, [fp, #-56]	@ ChanMemVDH.PhyAddr, ChanMemVDH.PhyAddr
	mov	r0, #0	@ tmp342,
	ldr	r2, [fp, #-52]	@ ChanMemVDH.VirAddr, ChanMemVDH.VirAddr
	str	r0, [fp, #-224]	@ tmp342, %sfp
	str	r0, [fp, #-60]	@ tmp342, ChanMemScd.Length
	str	lr, [fp, #-68]	@ ChanMemVDH.PhyAddr, ChanMemScd.PhyAddr
	str	r2, [fp, #-64]	@ ChanMemVDH.VirAddr, ChanMemScd.VirAddr
	b	.L2286	@
.L2362:
	sub	r8, fp, #108	@ tmp708,,
	mov	r1, r3	@, D.39763
	movw	r0, #:lower16:.LC335	@,
	ldr	r2, [fp, #-84]	@, DetailMemSize.ChanCtxDetailMem
	movt	r0, #:upper16:.LC335	@,
	mov	r3, r8	@, tmp708
	mov	r7, #1	@ tmp246,
	str	r7, [sp, #0]	@ tmp246,
	bl	MEM_AllocMemBlock	@
	subs	r6, r0, #0	@ D.39802,
	bne	.L2374	@,
	ldr	r1, [fp, #-104]	@, MemRecord.VirAddr
	ldr	r2, [fp, #-96]	@, MemRecord.Length
	ldr	r0, [fp, #-100]	@, MemRecord.PhyAddr
	bl	MEM_AddMemRecord	@
	ldr	r2, [r4, #120]	@ <variable>.u32DynamicFrameStoreAllocEn, <variable>.u32DynamicFrameStoreAllocEn
	ldr	r0, [fp, #-100]	@ MemRecord.PhyAddr, MemRecord.PhyAddr
	ldr	r1, [fp, #-104]	@ MemRecord.VirAddr, MemRecord.VirAddr
	cmp	r2, #1	@ <variable>.u32DynamicFrameStoreAllocEn,
	ldr	r3, [fp, #-96]	@ MemRecord.Length, MemRecord.Length
	str	r0, [fp, #-80]	@ MemRecord.PhyAddr, ChanMemCtx.PhyAddr
	str	r1, [fp, #-76]	@ MemRecord.VirAddr, ChanMemCtx.VirAddr
	str	r3, [fp, #-72]	@ MemRecord.Length, ChanMemCtx.Length
	beq	.L2289	@,
	mov	r1, r6	@, D.39802
	movw	r0, #:lower16:.LC337	@,
	ldr	r2, [fp, #-92]	@, DetailMemSize.VdhDetailMem
	movt	r0, #:upper16:.LC337	@,
	mov	r3, r8	@, tmp708
	str	r6, [sp, #0]	@ D.39802,
	bl	MEM_AllocMemBlock	@
	cmp	r0, #0	@,
	bne	.L2375	@,
	ldr	r1, [fp, #-104]	@, MemRecord.VirAddr
	ldr	r0, [fp, #-100]	@, MemRecord.PhyAddr
	ldr	r2, [fp, #-96]	@, MemRecord.Length
	str	r7, [fp, #-220]	@ tmp246, %sfp
	bl	MEM_AddMemRecord	@
	ldr	r1, [fp, #-100]	@ MemRecord.PhyAddr, MemRecord.PhyAddr
	ldr	r3, [fp, #-104]	@ MemRecord.VirAddr, MemRecord.VirAddr
	ldr	ip, [fp, #-96]	@ MemRecord.Length, MemRecord.Length
	str	r1, [fp, #-56]	@ MemRecord.PhyAddr, ChanMemVDH.PhyAddr
	str	r3, [fp, #-52]	@ MemRecord.VirAddr, ChanMemVDH.VirAddr
	str	ip, [fp, #-48]	@ MemRecord.Length, ChanMemVDH.Length
.L2291:
	ldr	r0, [r4, #4]	@ <variable>.Purpose, <variable>.Purpose
	cmp	r0, #2	@ <variable>.Purpose,
	bne	.L2376	@,
	ldr	r2, [fp, #-56]	@ ChanMemVDH.PhyAddr, ChanMemVDH.PhyAddr
	mov	r3, #0	@ tmp278,
	ldr	r7, [fp, #-52]	@ ChanMemVDH.VirAddr, ChanMemVDH.VirAddr
	mov	ip, #1	@,
	str	r3, [fp, #-224]	@ tmp278, %sfp
	str	r3, [fp, #-60]	@ tmp278, ChanMemScd.Length
	str	ip, [fp, #-216]	@, %sfp
	str	r2, [fp, #-68]	@ ChanMemVDH.PhyAddr, ChanMemScd.PhyAddr
	str	r7, [fp, #-64]	@ ChanMemVDH.VirAddr, ChanMemScd.VirAddr
	b	.L2286	@
.L2316:
	mov	r8, #0	@,
	str	r8, [fp, #-224]	@, %sfp
	b	.L2286	@
.L2366:
	add	r3, r3, #13	@,,
.L2355:
	str	r3, [fp, #-208]	@, %sfp
	mov	r6, r3	@ ChanID.6232,
	b	.L2323	@
.L2289:
	str	r6, [fp, #-220]	@ D.39802, %sfp
	str	r6, [fp, #-56]	@ D.39802, ChanMemVDH.PhyAddr
	str	r6, [fp, #-52]	@ D.39802, ChanMemVDH.VirAddr
	str	r6, [fp, #-48]	@ D.39802, ChanMemVDH.Length
	b	.L2291	@
.L2307:
	ldr	r2, [fp, #-48]	@ prephitmp.6061, ChanMemVDH.Length
	b	.L2308	@
.L2376:
	mov	lr, #0	@ tmp270,
	mov	r3, r8	@, tmp708
	mov	r1, lr	@, tmp270
	movw	r0, #:lower16:.LC339	@,
	ldr	r2, [fp, #-88]	@, DetailMemSize.ScdDetailMem
	movt	r0, #:upper16:.LC339	@,
	str	lr, [sp, #0]	@ tmp270,
	bl	MEM_AllocMemBlock	@
	cmp	r0, #0	@,
	bne	.L2377	@,
	mov	r8, #1	@,
	ldr	r0, [fp, #-100]	@, MemRecord.PhyAddr
	str	r8, [fp, #-216]	@, %sfp
	ldr	r1, [fp, #-104]	@, MemRecord.VirAddr
	str	r8, [fp, #-224]	@, %sfp
	b	.L2354	@
.L2372:
.L2347:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC348	@,
	movt	r1, #:upper16:.LC348	@,
	mvn	r9, #0	@,
	str	r9, [fp, #-208]	@, %sfp
	bl	dprint_vfmw	@
	mov	r0, r6	@, ChanID.6232
	sub	r7, fp, #156	@,,
	bl	VCTRL_UnInstallChan	@
	ldr	r3, [r5, r6, asl #2]	@ temp.6227, s_pstVfmwChan
	str	r7, [fp, #-240]	@, %sfp
	sub	lr, fp, #128	@,,
	add	r2, r3, #192	@ tmp685, temp.6227,
	add	r4, r3, #248832	@ tmp683, temp.6227,
	ldr	sl, [r3, #264]	@ <variable>.s32SelfAllocChanMem_ctx, <variable>.s32SelfAllocChanMem_ctx
	add	r1, r4, #400	@ tmp683, tmp683,
	add	ip, r3, #240	@ tmp687, temp.6227,
	add	r4, r3, #208	@ tmp689, temp.6227,
	add	r8, r3, #224	@ tmp691, temp.6227,
	add	r9, r3, #140	@ tmp693, temp.6227,
	str	sl, [fp, #-132]	@ <variable>.s32SelfAllocChanMem_ctx, ChanMem.s32SelfAllocChanMem_ctx
	sub	r7, fp, #188	@ tmp688,,
	ldr	r0, [r3, #256]	@ <variable>.s32SelfAllocChanMem_vdh, <variable>.s32SelfAllocChanMem_vdh
	sub	sl, fp, #172	@ tmp690,,
	str	lr, [fp, #-236]	@, %sfp
	ldr	lr, [fp, #-232]	@, %sfp
	str	r0, [fp, #-140]	@ <variable>.s32SelfAllocChanMem_vdh, ChanMem.s32SelfAllocChanMem_vdh
	ldr	r0, [r3, #260]	@ <variable>.s32SelfAllocChanMem_scd, <variable>.s32SelfAllocChanMem_scd
	str	r1, [fp, #-112]	@ tmp683, ChanMem.pstChanFrmBuf
	str	r0, [fp, #-136]	@ <variable>.s32SelfAllocChanMem_scd, ChanMem.s32SelfAllocChanMem_scd
	ldmia	r2, {r0, r1, r2, r3}	@ tmp685,,,,
	stmia	lr, {r0, r1, r2, r3}	@,,,,
	mov	lr, #0	@ tmp695,
	ldmia	ip, {r0, r1, r2, r3}	@ tmp687,,,,
	ldr	ip, [fp, #-240]	@, %sfp
	stmia	ip, {r0, r1, r2, r3}	@,,,,
	ldmia	r4, {r0, r1, r2, r3}	@ tmp689,,,,
	stmia	r7, {r0, r1, r2, r3}	@ tmp688,,,,
	ldmia	r8, {r0, r1, r2, r3}	@ tmp691,,,,
	stmia	sl, {r0, r1, r2, r3}	@ tmp690,,,,
	ldr	r3, [fp, #-236]	@, %sfp
	ldmia	r9, {r0, r1, r2}	@ tmp693,,,
	str	lr, [r5, r6, asl #2]	@ tmp695, s_pstVfmwChan
	stmia	r3, {r0, r1, r2}	@,,,
	mov	r0, r6	@, ChanID.6232
	bl	VDMDRV_ClearChanIsDec	@
	bl	VCTRL_EnableAllInt	@
	add	r0, r5, #504	@, tmp652,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r6	@, ChanID.6232
	sub	r1, fp, #204	@,,
	bl	VCTRL_FreeChanResource	@
	b	.L2269	@
.L2283:
	movw	r2, #1867	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC334	@,
	movt	r1, #:upper16:.LC334	@,
	bl	dprint_vfmw	@
	mvn	r2, #0	@,
	str	r2, [fp, #-208]	@, %sfp
	b	.L2269	@
.L2295:
	movw	r1, #:lower16:.LC346	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC346	@,
	mvn	r5, #0	@,
	str	r5, [fp, #-208]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2269	@
.L2369:
	ldr	r2, [fp, #-216]	@, %sfp
	cmp	r2, #1	@,
	bne	.L2305	@,
	ldr	r0, [fp, #-80]	@, ChanMemCtx.PhyAddr
	ldr	r1, [fp, #-76]	@, ChanMemCtx.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #80
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
.L2305:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC343	@,
	movw	r2, #1990	@,
	movt	r1, #:upper16:.LC343	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@,
	str	r0, [fp, #-208]	@, %sfp
	b	.L2269	@
.L2373:
	ldr	r5, [fp, #-216]	@, %sfp
	cmp	r5, #1	@,
	beq	.L2378	@,
.L2314:
	ldr	r8, [fp, #-220]	@, %sfp
	cmp	r8, #1	@,
	bne	.L2315	@,
	ldr	r0, [fp, #-56]	@, ChanMemVDH.PhyAddr
	ldr	r1, [fp, #-52]	@, ChanMemVDH.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #56
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
.L2315:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC345	@,
	movw	r2, #2046	@,
	movt	r1, #:upper16:.LC345	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@,
	str	r0, [fp, #-208]	@, %sfp
	b	.L2269	@
.L2356:
	movw	r1, #:lower16:.LC330	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC330	@,
	mvn	ip, #0	@,
	str	ip, [fp, #-208]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2269	@
.L2360:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC331	@,
	movw	r2, #1844	@,
	movt	r1, #:upper16:.LC331	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@,
	str	r3, [fp, #-208]	@, %sfp
	b	.L2269	@
.L2357:
	movw	r1, #:lower16:.LC21	@,
	movt	r1, #:upper16:.LC21	@,
	mvn	lr, #0	@,
	str	lr, [fp, #-208]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2269	@
.L2363:
	movw	r2, #1957	@,
	mov	r0, r6	@, tmp284
	movw	r1, #:lower16:.LC341	@,
	movt	r1, #:upper16:.LC341	@,
	bl	dprint_vfmw	@
	mvn	r2, #0	@,
	str	r2, [fp, #-208]	@, %sfp
	b	.L2269	@
.L2364:
	ldr	r0, [fp, #-216]	@, %sfp
	cmp	r0, #1	@,
	beq	.L2379	@,
.L2309:
	mov	r3, r2	@, prephitmp.6061
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC344	@,
	movw	r2, #2020	@,
	movt	r1, #:upper16:.LC344	@,
	str	ip, [sp, #0]	@ prephitmp.6062,
	bl	dprint_vfmw	@
	mvn	r3, #0	@,
	str	r3, [fp, #-208]	@, %sfp
	b	.L2269	@
.L2279:
	mov	r2, #1856	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC332	@,
	movt	r1, #:upper16:.LC332	@,
	bl	dprint_vfmw	@
	mvn	r2, #0	@,
	str	r2, [fp, #-208]	@, %sfp
	b	.L2269	@
.L2368:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC342	@,
	movw	r2, #1971	@,
	movt	r1, #:upper16:.LC342	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@,
	str	r0, [fp, #-208]	@, %sfp
	b	.L2269	@
.L2374:
	mov	r0, r7	@, tmp246
	movw	r1, #:lower16:.LC336	@,
	movw	r2, #1883	@,
	movt	r1, #:upper16:.LC336	@,
	ldr	r3, [fp, #-84]	@, DetailMemSize.ChanCtxDetailMem
	mvn	ip, #0	@,
	str	ip, [fp, #-208]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2269	@
.L2378:
	ldr	r0, [fp, #-80]	@, ChanMemCtx.PhyAddr
	ldr	r1, [fp, #-76]	@, ChanMemCtx.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #80
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
	b	.L2314	@
.L2365:
	ldr	r3, [fp, #-216]	@, %sfp
	cmp	r3, #1	@,
	bne	.L2320	@,
	ldr	r0, [fp, #-80]	@, ChanMemCtx.PhyAddr
	ldr	r1, [fp, #-76]	@, ChanMemCtx.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #80
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
.L2320:
	ldr	r1, [fp, #-220]	@, %sfp
	cmp	r1, #1	@,
	bne	.L2321	@,
	ldr	r0, [fp, #-56]	@, ChanMemVDH.PhyAddr
	ldr	r1, [fp, #-52]	@, ChanMemVDH.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #56
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
.L2321:
	movw	r2, #2084	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC333	@,
	movt	r1, #:upper16:.LC333	@,
	bl	dprint_vfmw	@
	mvn	r2, #0	@,
	str	r2, [fp, #-208]	@, %sfp
	b	.L2269	@
.L2379:
	ldr	r0, [fp, #-80]	@, ChanMemCtx.PhyAddr
	ldr	r1, [fp, #-76]	@, ChanMemCtx.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #80
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
	ldr	r2, [fp, #-48]	@ prephitmp.6061, ChanMemVDH.Length
	ldr	ip, [fp, #-92]	@ prephitmp.6062, DetailMemSize.VdhDetailMem
	b	.L2309	@
.L2377:
	ldr	r0, [fp, #-80]	@, ChanMemCtx.PhyAddr
	ldr	r1, [fp, #-76]	@, ChanMemCtx.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #80
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
	ldr	r5, [fp, #-220]	@, %sfp
	cmp	r5, #1	@,
	bne	.L2294	@,
	ldr	r0, [fp, #-56]	@, ChanMemVDH.PhyAddr
	ldr	r1, [fp, #-52]	@, ChanMemVDH.VirAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #56
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
.L2294:
	movw	r1, #:lower16:.LC340	@,
	movw	r2, #1934	@,
	movt	r1, #:upper16:.LC340	@,
	ldr	r3, [fp, #-88]	@, DetailMemSize.ScdDetailMem
	mov	r0, #1	@,
	mvn	r5, #0	@,
	str	r5, [fp, #-208]	@, %sfp
	bl	dprint_vfmw	@
	b	.L2269	@
.L2375:
	ldr	r0, [fp, #-80]	@, ChanMemCtx.PhyAddr
	mvn	lr, #0	@,
	ldr	r1, [fp, #-76]	@, ChanMemCtx.VirAddr
	str	lr, [fp, #-208]	@, %sfp
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #80
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	bl	MEM_DelMemRecord	@
	mov	r0, r7	@, tmp246
	movw	r1, #:lower16:.LC338	@,
	movw	r2, #1901	@,
	movt	r1, #:upper16:.LC338	@,
	ldr	r3, [fp, #-92]	@, DetailMemSize.VdhDetailMem
	bl	dprint_vfmw	@
	b	.L2269	@
	.fnend
	.size	VCTRL_CreateChanWithOption, .-VCTRL_CreateChanWithOption
	.align	2
	.global	VCTRL_CreateChan
	.type	VCTRL_CreateChan, %function
VCTRL_CreateChan:
	.fnstart
.LFB1566:
	@ args = 0, pretend = 0, frame = 200
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #212
	sub	sp, sp, #212	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #32	@ eCapLevel,
	mov	r4, r0	@ eCapLevel, eCapLevel
	mov	r5, r1	@ pChanMem, pChanMem
	bhi	.L2395	@,
	sub	r8, fp, #240	@ tmp237,,
	sub	r6, fp, #80	@ tmp241,,
	mov	r1, #148	@,
	sub	r7, fp, #92	@ tmp239,,
	mov	r0, r8	@, tmp237
	bl	__memzero	@
	mov	r0, r6	@, tmp241
	mov	r1, #12	@,
	bl	__memzero	@
	mov	r0, r7	@, tmp239
	mov	r1, #12	@,
	bl	__memzero	@
	mov	r2, r4, asl #3	@ tmp240, eCapLevel,
	rsb	r1, r4, r2	@ tmp155, eCapLevel, tmp240
	movw	r3, #:lower16:CapItem	@ tmp238,
	movt	r3, #:upper16:CapItem	@ tmp238,
	sub	r0, r4, #18	@ D.45061, eCapLevel,
	cmp	r0, #7	@ D.45061,
	add	ip, r1, #1	@ tmp163, tmp155,
	ldr	r1, [r3, r1, asl #2]	@ tmp158, CapItem
	mov	lr, #1	@ tmp150,
	str	lr, [fp, #-236]	@ tmp150, stChanOption.Purpose
	mov	lr, #2	@ tmp151,
	str	lr, [fp, #-232]	@ tmp151, stChanOption.MemAllocMode
	mov	lr, #32	@ tmp166,
	str	lr, [fp, #-212]	@ tmp166, stChanOption.s32MaxSpsNum
	mov	lr, #256	@ tmp167,
	str	lr, [fp, #-208]	@ tmp167, stChanOption.s32MaxPpsNum
	movwls	lr, #:lower16:.LANCHOR1	@ tmp168,
	movtls	lr, #:upper16:.LANCHOR1	@ tmp168,
	str	r1, [fp, #-228]	@ tmp158, stChanOption.s32MaxWidth
	addls	r0, lr, r0, asl #2	@, tmp171, tmp168, D.45061,
	mov	r1, #136	@ tmp165,
	str	r1, [fp, #-220]	@ tmp165, stChanOption.s32MaxSliceNum
	rsb	r1, r4, r2	@ tmp177, eCapLevel, tmp240
	ldrls	lr, [r0, #460]	@ MinDispFspNum, CSWTCH.922
	movhi	lr, #6	@ MinDispFspNum,
	add	r0, r3, r1, asl #2	@, tmp179, tmp238, tmp177,
	ldr	ip, [r3, ip, asl #2]	@ tmp164, CapItem
	ldr	r1, [r0, #12]	@ D.39603, CapItem
	rsb	r0, r4, r2	@ tmp191, eCapLevel, tmp240
	str	ip, [fp, #-224]	@ tmp164, stChanOption.s32MaxHeight
	addls	ip, lr, #2	@ prephitmp.6263, MinDispFspNum,
	add	r3, r3, r0, asl #2	@, tmp193, tmp238, tmp191,
	movhi	ip, #8	@ prephitmp.6263,
	cmp	r1, ip	@ D.39603, prephitmp.6263
	mov	r2, #1	@ tmp184,
	subgt	r1, r1, #2	@ tmp182, D.39603,
	ldr	r3, [r3, #24]	@ tmp195, CapItem
	movle	r1, #1	@ tmp181,
	rsbgt	r1, lr, r1	@ tmp183, MinDispFspNum, tmp182
	cmp	r4, #24	@ eCapLevel,
	str	r1, [fp, #-204]	@ tmp183, stChanOption.s32MaxRefFrameNum
	str	lr, [fp, #-176]	@ MinDispFspNum, stChanOption.s32DisplayFrameNum
	mov	r1, #0	@ tmp196,
	str	r2, [fp, #-196]	@ tmp184, stChanOption.s32SupportBFrame
	str	r2, [fp, #-192]	@ tmp184, stChanOption.s32SupportH264
	str	r2, [fp, #-184]	@ tmp184, stChanOption.s32ReRangeEn
	str	r1, [fp, #-172]	@ tmp196, stChanOption.s32SlotWidth
	str	r3, [fp, #-180]	@ tmp195, stChanOption.s32SCDBufSize
	str	r1, [fp, #-168]	@ tmp196, stChanOption.s32SlotHeight
	streq	r1, [fp, #-204]	@ tmp196, stChanOption.s32MaxRefFrameNum
	streq	r2, [fp, #-176]	@ tmp184, stChanOption.s32DisplayFrameNum
	beq	.L2388	@,
	cmp	r4, #26	@ eCapLevel,
	beq	.L2396	@,
	cmp	r4, #18	@ eCapLevel,
	moveq	r3, #4	@ tmp202,
	streq	r3, [fp, #-204]	@ tmp202, stChanOption.s32MaxRefFrameNum
	moveq	r3, #2	@ tmp203,
	streq	r3, [fp, #-176]	@ tmp203, stChanOption.s32DisplayFrameNum
.L2388:
	mov	r0, r4	@, eCapLevel
	sub	r1, fp, #56	@,,
	sub	r2, fp, #68	@,,
	bl	VCTRL_GetChanMemSize	@
	cmp	r0, #0	@,
	bne	.L2397	@,
	cmp	r5, #0	@ pChanMem,
	beq	.L2391	@,
	ldr	r2, [r5, #8]	@ D.39623, <variable>.Length
	cmp	r2, #0	@ D.39623,
	beq	.L2391	@,
	ldr	lr, [r5, #0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	cmp	lr, #0	@ <variable>.PhyAddr,
	beq	.L2392	@,
	ldr	ip, [r5, #4]	@ <variable>.VirAddr, <variable>.VirAddr
	cmp	ip, #0	@ <variable>.VirAddr,
	beq	.L2392	@,
	ldr	r3, [fp, #-56]	@ VdmChanMemSize, VdmChanMemSize
	ldr	r1, [fp, #-68]	@ ScdChanMemSize, ScdChanMemSize
	add	r0, r1, r3	@ tmp209, ScdChanMemSize, VdmChanMemSize
	cmp	r2, r0	@ D.39623, tmp209
	blt	.L2392	@,
	ldr	r3, [fp, #-64]	@ D.39636, ScdChanMemSize
	sub	sl, fp, #144	@ tmp221,,
	str	lr, [fp, #-92]	@ <variable>.PhyAddr, scd_MemRecord.PhyAddr
	sub	r9, fp, #156	@ tmp223,,
	rsb	r5, r3, r2	@ tmp220, D.39636, D.39623
	str	ip, [fp, #-88]	@ <variable>.VirAddr, scd_MemRecord.VirAddr
	str	r3, [fp, #-84]	@ D.39636, scd_MemRecord.Length
	add	lr, lr, r3	@ tmp216, <variable>.PhyAddr, D.39636
	ldmia	r7, {r0, r1, r2}	@ tmp239,,,
	str	lr, [fp, #-80]	@ tmp216, vdh_MemRecord.PhyAddr
	add	r3, ip, r3	@ tmp218, <variable>.VirAddr, D.39636
	str	r5, [fp, #-72]	@ tmp220, vdh_MemRecord.Length
	str	r3, [fp, #-76]	@ tmp218, vdh_MemRecord.VirAddr
	mov	lr, #3	@ tmp212,
	mov	r3, #1	@ OneChanMemFlag,
	str	lr, [fp, #-232]	@ tmp212, stChanOption.MemAllocMode
	stmia	sl, {r0, r1, r2}	@ tmp221,,,
	ldmia	r6, {r0, r1, r2}	@ tmp241,,,
	stmia	r9, {r0, r1, r2}	@ tmp223,,,
	b	.L2393	@
.L2391:
	mov	r3, #0	@ OneChanMemFlag,
.L2393:
	mov	r0, r4	@, eCapLevel
	mov	r1, r8	@, tmp237
	mov	r2, #1	@,
	bl	VCTRL_CreateChanWithOption	@
	orr	r0, r0, r0, asr #31	@ D.39584,
.L2382:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L2396:
	mov	r2, #16	@ tmp200,
	mov	r3, #6	@ tmp201,
	str	r2, [fp, #-204]	@ tmp200, stChanOption.s32MaxRefFrameNum
	str	r3, [fp, #-176]	@ tmp201, stChanOption.s32DisplayFrameNum
	b	.L2388	@
.L2395:
	mov	r2, r0	@, eCapLevel
	movw	r1, #:lower16:.LC349	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC349	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39584,
	b	.L2382	@
.L2392:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC351	@,
	movt	r1, #:upper16:.LC351	@,
	bl	dprint_vfmw	@
	ldr	ip, [r5, #8]	@ <variable>.Length, <variable>.Length
	ldr	r2, [r5, #0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	mov	r0, #1	@,
	ldr	r3, [r5, #4]	@ <variable>.VirAddr, <variable>.VirAddr
	movw	r1, #:lower16:.LC352	@,
	movt	r1, #:upper16:.LC352	@,
	str	ip, [sp, #0]	@ <variable>.Length,
	bl	dprint_vfmw	@
	ldr	r3, [fp, #-56]	@ VdmChanMemSize, VdmChanMemSize
	ldr	ip, [fp, #-68]	@ ScdChanMemSize, ScdChanMemSize
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC353	@,
	movt	r1, #:upper16:.LC353	@,
	add	r2, ip, r3	@, ScdChanMemSize, VdmChanMemSize
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39584,
	b	.L2382	@
.L2397:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC350	@,
	movt	r1, #:upper16:.LC350	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39584,
	b	.L2382	@
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
	movw	r5, #:lower16:.LANCHOR3	@ tmp208,
	movt	r5, #:upper16:.LANCHOR3	@ tmp208,
	movw	r4, #:lower16:.LANCHOR0	@ tmp207,
	movt	r4, #:upper16:.LANCHOR0	@ tmp207,
	mov	r3, #100	@ tmp186,
	ldr	r0, [r5, #3848]	@ g_SleepTime.453, g_SleepTime
	str	r3, [r4, #152]	@ tmp186, s_VfmwCTrl.s32ThreadPos
	cmp	r0, #0	@ g_SleepTime.453,
	ble	.L2399	@,
	bl	msleep	@
.L2399:
	ldr	r0, .L2471	@,
	bl	OSAL_SpinLockIRQ	@
	bl	SM_Wakeup	@
	ldr	r0, [r5, #3856]	@ g_StopDec, g_StopDec
	mov	r2, #101	@ tmp191,
	str	r2, [r4, #152]	@ tmp191, s_VfmwCTrl.s32ThreadPos
	cmp	r0, #0	@ g_StopDec,
	movne	r5, #0	@ ret,
	beq	.L2453	@,
.L2401:
	mov	r6, #102	@ tmp195,
	str	r6, [r4, #152]	@ tmp195, s_VfmwCTrl.s32ThreadPos
	bl	VDMDRV_WakeUpVdm	@
	mov	r0, #0	@,
	bl	SCDDRV_EnableInt	@
	movw	r1, #:lower16:g_vdm_hal_fun_ptr	@ tmp196,
	movt	r1, #:upper16:g_vdm_hal_fun_ptr	@ tmp196,
	ldr	r3, [r1, #60]	@ D.38916, g_vdm_hal_fun_ptr.pfun_VDMHAL_EnableInt
	cmp	r3, #0	@ D.38916,
	beq	.L2454	@,
	mov	r0, #0	@,
	blx	r3	@ D.38916
.L2405:
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
	beq	.L2455	@,
.L2404:
	mov	r0, #1	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@ temp.6314,
	mov	r6, r0	@ temp.6314,
	beq	.L2456	@,
.L2408:
	mov	r0, #2	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2457	@,
.L2411:
	mov	r0, #3	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2458	@,
.L2414:
	mov	r0, #4	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2459	@,
.L2417:
	mov	r0, #5	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2460	@,
.L2420:
	mov	r0, #6	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2461	@,
.L2423:
	mov	r0, #7	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2462	@,
.L2426:
	mov	r0, #8	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2463	@,
.L2429:
	mov	r0, #9	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2464	@,
.L2432:
	mov	r0, #10	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2465	@,
.L2435:
	mov	r0, #11	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2466	@,
.L2438:
	mov	r0, #12	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2467	@,
.L2441:
	mov	r0, #13	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2468	@,
.L2444:
	mov	r0, #14	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2469	@,
.L2447:
	mov	r0, #15	@,
	bl	SM_GetInstanceRawDiscontinue	@
	cmp	r0, #1	@,
	beq	.L2470	@,
.L2450:
	ldr	r0, .L2471	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r1, #10	@,
	ldr	r0, .L2471+4	@,
	mov	ip, #105	@ tmp201,
	str	ip, [r4, #152]	@ tmp201, s_VfmwCTrl.s32ThreadPos
	bl	OSAL_WaitEvent	@
	mov	r0, r5	@, ret
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L2453:
	bl	DecSyntax	@
	mov	r5, r0	@ ret,
	b	.L2401	@
.L2454:
	mov	r0, r3	@, D.38916
	movw	r1, #:lower16:.LC0	@,
	mov	r2, #560	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	b	.L2405	@
.L2462:
	mov	r0, #7	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6333,
	mov	r0, #7	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2428	@,
	cmp	r6, #1	@ tmp.6333,
	bne	.L2426	@,
.L2428:
	mov	r1, #3	@,
	mov	r0, #7	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #7	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #7	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2426	@
.L2463:
	mov	r0, #8	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6336,
	mov	r0, #8	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2431	@,
	cmp	r6, #1	@ tmp.6336,
	bne	.L2429	@,
.L2431:
	mov	r1, #3	@,
	mov	r0, #8	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #8	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #8	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2429	@
.L2464:
	mov	r0, #9	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6339,
	mov	r0, #9	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2434	@,
	cmp	r6, #1	@ tmp.6339,
	bne	.L2432	@,
.L2434:
	mov	r1, #3	@,
	mov	r0, #9	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #9	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #9	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2432	@
.L2465:
	mov	r0, #10	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6342,
	mov	r0, #10	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2437	@,
	cmp	r6, #1	@ tmp.6342,
	bne	.L2435	@,
.L2437:
	mov	r1, #3	@,
	mov	r0, #10	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #10	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #10	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2435	@
.L2466:
	mov	r0, #11	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6345,
	mov	r0, #11	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2440	@,
	cmp	r6, #1	@ tmp.6345,
	bne	.L2438	@,
.L2440:
	mov	r1, #3	@,
	mov	r0, #11	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #11	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #11	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2438	@
.L2467:
	mov	r0, #12	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6348,
	mov	r0, #12	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2443	@,
	cmp	r6, #1	@ tmp.6348,
	bne	.L2441	@,
.L2443:
	mov	r1, #3	@,
	mov	r0, #12	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #12	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #12	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2441	@
.L2468:
	mov	r0, #13	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6351,
	mov	r0, #13	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2446	@,
	cmp	r6, #1	@ tmp.6351,
	bne	.L2444	@,
.L2446:
	mov	r1, #3	@,
	mov	r0, #13	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #13	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #13	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2444	@
.L2469:
	mov	r0, #14	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6354,
	mov	r0, #14	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2449	@,
	cmp	r6, #1	@ tmp.6354,
	bne	.L2447	@,
.L2449:
	mov	r1, #3	@,
	mov	r0, #14	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #14	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #14	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2447	@
.L2458:
	mov	r0, #3	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6321,
	mov	r0, #3	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2416	@,
	cmp	r6, #1	@ tmp.6321,
	bne	.L2414	@,
.L2416:
	mov	r0, #3	@,
	mov	r1, r0	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #3	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #3	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2414	@
.L2459:
	mov	r0, #4	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6324,
	mov	r0, #4	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2419	@,
	cmp	r6, #1	@ tmp.6324,
	bne	.L2417	@,
.L2419:
	mov	r1, #3	@,
	mov	r0, #4	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #4	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #4	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2417	@
.L2460:
	mov	r0, #5	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6327,
	mov	r0, #5	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2422	@,
	cmp	r6, #1	@ tmp.6327,
	bne	.L2420	@,
.L2422:
	mov	r1, #3	@,
	mov	r0, #5	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #5	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #5	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2420	@
.L2461:
	mov	r0, #6	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6330,
	mov	r0, #6	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2425	@,
	cmp	r6, #1	@ tmp.6330,
	bne	.L2423	@,
.L2425:
	mov	r1, #3	@,
	mov	r0, #6	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #6	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #6	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2423	@
.L2456:
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r7, r0	@ tmp.6315,
	mov	r0, r6	@, temp.6314
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2410	@,
	cmp	r7, #1	@ tmp.6315,
	bne	.L2408	@,
.L2410:
	mov	r1, #3	@,
	mov	r0, #1	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #1	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #1	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2408	@
.L2457:
	mov	r0, #2	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6318,
	mov	r0, #2	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2413	@,
	cmp	r6, #1	@ tmp.6318,
	bne	.L2411	@,
.L2413:
	mov	r1, #3	@,
	mov	r0, #2	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #2	@,
	bl	VCTRL_ResetChan	@
	mov	r0, #2	@,
	mov	r1, r0	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2411	@
.L2455:
	mov	r0, #0	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp.6312,
	mov	r0, #0	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2407	@,
	cmp	r6, #1	@ tmp.6312,
	bne	.L2404	@,
.L2407:
	mov	r1, #3	@,
	mov	r0, #0	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #0	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #0	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2404	@
.L2470:
	mov	r0, #15	@,
	bl	VCTRL_ChanDecparamInValidFlag	@
	mov	r6, r0	@ tmp,
	mov	r0, #15	@,
	bl	SM_GetInstanceStreamEmptyFlag	@
	cmp	r0, #1	@,
	beq	.L2451	@,
	cmp	r6, #1	@ tmp,
	bne	.L2450	@,
.L2451:
	mov	r1, #3	@,
	mov	r0, #15	@,
	bl	SM_SetRawDiscontinueFlag	@
	mov	r0, #15	@,
	bl	VCTRL_ResetChan	@
	mov	r1, #2	@,
	mov	r0, #15	@,
	bl	SM_SetRawDiscontinueFlag	@
	b	.L2450	@
.L2472:
	.align	2
.L2471:
	.word	.LANCHOR0+504
	.word	.LANCHOR3+3532
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
.L2474:
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
.L2479:
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC354	@,
	movt	r1, #:upper16:.LC354	@,
	str	r6, [r4, #152]	@ tmp176, s_VfmwCTrl.s32ThreadPos
	bl	dprint_vfmw	@
	ldr	r3, [r4, #144]	@ temp.6383, s_VfmwCTrl.eTaskCommand
	mov	r5, #2	@ tmp144,
	str	r5, [r4, #140]	@ tmp144, s_VfmwCTrl.eTaskState
	cmp	r3, r5	@ temp.6383,
	bne	.L2478	@,
	b	.L2475	@
.L2485:
	str	r5, [r4, #152]	@ tmp172, s_VfmwCTrl.s32ThreadPos
	bl	VCTRL_RunProcess	@
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC355	@,
	movt	r1, #:upper16:.LC355	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #144]	@ D.38877, s_VfmwCTrl.eTaskCommand
	cmp	r3, #2	@ D.38877,
	beq	.L2475	@,
.L2478:
	cmp	r3, #3	@ D.38877,
	bne	.L2485	@,
.L2476:
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC358	@,
	movt	r1, #:upper16:.LC358	@,
	mov	r2, #6	@ tmp162,
	str	r2, [r4, #152]	@ tmp162, s_VfmwCTrl.s32ThreadPos
	bl	dprint_vfmw	@
	mov	r0, #0	@ tmp165,
	str	r0, [r4, #140]	@ tmp165, s_VfmwCTrl.eTaskState
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L2475:
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC356	@,
	movt	r1, #:upper16:.LC356	@,
	mov	r3, #4	@ tmp154,
	str	r3, [r4, #152]	@ tmp154, s_VfmwCTrl.s32ThreadPos
	bl	dprint_vfmw	@
	str	r8, [r4, #140]	@ tmp177, s_VfmwCTrl.eTaskState
.L2480:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC357	@,
	movt	r1, #:upper16:.LC357	@,
	str	r7, [r4, #152]	@ tmp181, s_VfmwCTrl.s32ThreadPos
	bl	dprint_vfmw	@
	ldr	r3, [r4, #144]	@ temp.6380, s_VfmwCTrl.eTaskCommand
	cmp	r3, #1	@ temp.6380,
	beq	.L2479	@,
	cmp	r3, #3	@ temp.6380,
	mov	r0, #10	@,
	beq	.L2476	@,
	bl	msleep	@
	b	.L2480	@
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
	movw	r5, #:lower16:.LANCHOR0	@ tmp204,
	movt	r5, #:upper16:.LANCHOR0	@ tmp204,
	mov	r4, r0	@ ChanID, ChanID
	mov	r7, r1	@ pOption, pOption
	ldr	r3, [r5, r0, asl #2]	@ D.40683, s_pstVfmwChan
	cmp	r3, #0	@ D.40683,
	beq	.L2498	@,
	ldr	r2, [r1, #0]	@ <variable>.s32KeepBS, <variable>.s32KeepBS
	cmp	r2, #1	@ <variable>.s32KeepBS,
	bhi	.L2499	@,
	ldr	r8, [r3, #16]	@ ChanIsRun, <variable>.s32IsRun
	bl	VCTRL_StopChan	@
	ldr	r3, [r5, r4, asl #2]	@ tmp149, s_pstVfmwChan
	mov	r6, #0	@ tmp150,
	add	r1, r5, #1440	@ tmp155, tmp204,
	mov	r0, #300	@ tmp158,
	add	r2, r1, #4	@ tmp155, tmp155,
	mov	r1, r0	@, tmp158
	str	r6, [r3, #828]	@ tmp150, <variable>.s32CountNoDecparamFlag
	ldr	ip, [r5, r4, asl #2]	@ tmp152, s_pstVfmwChan
	mla	r0, r0, r4, r2	@, tmp158, ChanID, tmp155
	str	r6, [ip, #832]	@ tmp150, <variable>.u32NoDecparamStartTime
	bl	__memzero	@
	mov	r1, r6	@, tmp150
	mov	r0, r4	@, ChanID
	bl	VCTRL_SetSendStreamAgainFlag	@
	ldr	r3, [r5, r4, asl #2]	@ tmp161, s_pstVfmwChan
	ldr	r2, [r7, #4]	@ <variable>.s32KeepSPSPPS, <variable>.s32KeepSPSPPS
	mov	r0, r4	@, ChanID
	str	r2, [r3, #1736]	@ <variable>.s32KeepSPSPPS, <variable>.stSynExtraData.s32KeepSPSPPS
	bl	InitSyntaxCtx	@
	ldr	ip, [r5, r4, asl #2]	@ temp.6413, s_pstVfmwChan
	add	r1, ip, #250880	@, temp.6413,
	ldr	r0, [ip, #1032]	@, <variable>.eVidStd
	add	r1, r1, #616	@,,
	bl	ReleaseCurPic	@
	ldr	r3, [r5, r4, asl #2]	@ tmp169, s_pstVfmwChan
	mov	r1, #416	@,
	add	r2, r3, #1168	@, tmp169,
	add	r0, r2, #8	@,,
	bl	__memzero	@
	ldr	ip, [r5, r4, asl #2]	@ tmp172, s_pstVfmwChan
	movw	r0, #1096	@ tmp173,
	mvn	r3, #0	@,
	mvn	r2, #0	@ tmp174,
	mov	r1, #1104	@ tmp177,
	strd	r2, [ip, r0]	@ tmp174, tmp172, tmp173
	ldr	r0, [r5, r4, asl #2]	@ tmp176, s_pstVfmwChan
	strd	r2, [r0, r1]	@ tmp174, tmp176, tmp177
	ldr	ip, [r5, r4, asl #2]	@ tmp180, s_pstVfmwChan
	str	r6, [ip, #1592]	@ tmp150, <variable>.stSynExtraData.s32NewPicSegDetector
	ldr	r0, [r5, r4, asl #2]	@ prephitmp.6399, s_pstVfmwChan
	ldr	r1, [r0, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r1, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	streq	r6, [r0, #1924]	@ tmp150, <variable>.stSynExtraData.s32WaitFsFlag
	ldreq	r0, [r5, r4, asl #2]	@ prephitmp.6399, s_pstVfmwChan
	ldr	r3, [r0, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r3, #18	@ <variable>.eVidStd,
	beq	.L2491	@,
	mov	r0, r4	@, ChanID
	bl	FSP_ResetInstance	@
.L2492:
	mov	r0, r4	@, ChanID
	bl	InitUsdPool	@
	ldr	ip, [r7, #0]	@ <variable>.s32KeepBS, <variable>.s32KeepBS
	cmp	ip, #0	@ <variable>.s32KeepBS,
	beq	.L2500	@,
.L2493:
	ldr	lr, [r5, #1356]	@ g_ResetCreateNewSave, g_ResetCreateNewSave
	cmp	lr, #0	@ g_ResetCreateNewSave,
	beq	.L2494	@,
	movw	r5, #:lower16:.LANCHOR3	@ tmp190,
	movt	r5, #:upper16:.LANCHOR3	@ tmp190,
	add	r5, r5, r4, asl #2	@, tmp193, tmp190, ChanID,
	str	r4, [fp, #-40]	@ ChanID, data
	ldr	r0, [r5, #3556]	@ tmp195, vfmw_save_str_file
	cmp	r0, #0	@ tmp195,
	beq	.L2495	@,
	sub	r6, fp, #40	@ data.557,,
	mov	r0, #512	@,
	mov	r1, r6	@, data.557
	bl	VCTRL_SetDbgOption	@
	ldr	r2, [r5, #3556]	@ tmp201, vfmw_save_str_file
	cmp	r2, #0	@ tmp201,
	beq	.L2495	@,
	mov	r1, r6	@, data.557
	mov	r0, #512	@,
	bl	VCTRL_SetDbgOption	@
.L2495:
	movw	r1, #:lower16:.LC318	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC318	@,
	bl	dprint_vfmw	@
.L2494:
	cmp	r8, #0	@ ChanIsRun,
	bne	.L2501	@,
.L2496:
	mov	r0, r4	@, ChanID
	bl	VDMDRV_ClearChanIsDec	@
	mov	r0, #0	@ D.40687,
.L2488:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2500:
	mov	r0, r4	@, ChanID
	bl	SM_Reset	@
	b	.L2493	@
.L2501:
	mov	r0, r4	@, ChanID
	bl	VCTRL_StartChan	@
	b	.L2496	@
.L2491:
	mov	r0, r4	@, ChanID
	bl	FSP_EmptyInstance	@
	b	.L2492	@
.L2499:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC359	@,
	movw	r2, #3859	@,
	movt	r1, #:upper16:.LC359	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40687,
	b	.L2488	@
.L2498:
	mov	r0, r3	@, D.40683
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #3855	@,
	movt	r1, #:upper16:.LC5	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.40687,
	b	.L2488	@
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
	b	.L2503	@
.L2509:
	.word	.L2504
	.word	.L2505
	.word	.L2506
	.word	.L2507
	.word	.L2508
.L2508:
	mov	r0, r1	@, strState
	mov	r2, #7	@,
	movw	r1, #:lower16:.LC364	@,
	movt	r1, #:upper16:.LC364	@,
	bl	memcpy	@
	mov	ip, #0	@ tmp168,
	strb	ip, [r4, #7]	@ tmp168,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2503:
	mov	r3, #0	@ tmp170,
	strb	r3, [r1, #0]	@ tmp170,* strState
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2504:
	mov	r0, r1	@, strState
	mov	r2, #5	@,
	movw	r1, #:lower16:.LC360	@,
	movt	r1, #:upper16:.LC360	@,
	bl	memcpy	@
	mov	r3, #0	@ tmp140,
	strb	r3, [r4, #5]	@ tmp140,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2505:
	mov	r0, r1	@, strState
	mov	r2, #8	@,
	movw	r1, #:lower16:.LC361	@,
	movt	r1, #:upper16:.LC361	@,
	bl	memcpy	@
	mov	r0, #0	@ tmp147,
	strb	r0, [r4, #8]	@ tmp147,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2506:
	mov	r0, r1	@, strState
	mov	r2, #7	@,
	movw	r1, #:lower16:.LC362	@,
	movt	r1, #:upper16:.LC362	@,
	bl	memcpy	@
	mov	r1, #0	@ tmp154,
	strb	r1, [r4, #7]	@ tmp154,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2507:
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
	b	.L2513	@
.L2534:
	.word	.L2514
	.word	.L2515
	.word	.L2516
	.word	.L2517
	.word	.L2518
	.word	.L2519
	.word	.L2520
	.word	.L2521
	.word	.L2522
	.word	.L2523
	.word	.L2524
	.word	.L2525
	.word	.L2526
	.word	.L2527
	.word	.L2528
	.word	.L2529
	.word	.L2530
	.word	.L2531
	.word	.L2532
	.word	.L2533
.L2533:
	mov	r0, r1	@, strVidStd
	mov	r2, #8	@,
	movw	r1, #:lower16:.LC384	@,
	movt	r1, #:upper16:.LC384	@,
	bl	memcpy	@
	mov	ip, #0	@ tmp273,
	strb	ip, [r4, #8]	@ tmp273,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2532:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC383	@,
	movt	r1, #:upper16:.LC383	@,
	bl	memcpy	@
	mov	r2, #0	@ tmp266,
	strb	r2, [r4, #4]	@ tmp266,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2531:
	mov	r0, r1	@, strVidStd
	mov	r2, #3	@,
	movw	r1, #:lower16:.LC382	@,
	movt	r1, #:upper16:.LC382	@,
	bl	memcpy	@
	mov	r1, #0	@ tmp259,
	strb	r1, [r4, #3]	@ tmp259,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2530:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC381	@,
	movt	r1, #:upper16:.LC381	@,
	bl	memcpy	@
	mov	r0, #0	@ tmp252,
	strb	r0, [r4, #4]	@ tmp252,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2529:
	mov	r0, r1	@, strVidStd
	mov	r2, #3	@,
	movw	r1, #:lower16:.LC380	@,
	movt	r1, #:upper16:.LC380	@,
	bl	memcpy	@
	mov	r3, #0	@ tmp245,
	strb	r3, [r4, #3]	@ tmp245,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2528:
	mov	r0, r1	@, strVidStd
	mov	r2, #8	@,
	movw	r1, #:lower16:.LC379	@,
	movt	r1, #:upper16:.LC379	@,
	bl	memcpy	@
	mov	ip, #0	@ tmp238,
	strb	ip, [r4, #8]	@ tmp238,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2527:
	mov	r0, r1	@, strVidStd
	mov	r2, #3	@,
	movw	r1, #:lower16:.LC378	@,
	movt	r1, #:upper16:.LC378	@,
	bl	memcpy	@
	mov	r2, #0	@ tmp231,
	strb	r2, [r4, #3]	@ tmp231,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2526:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC377	@,
	movt	r1, #:upper16:.LC377	@,
	bl	memcpy	@
	mov	r1, #0	@ tmp224,
	strb	r1, [r4, #4]	@ tmp224,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2525:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC376	@,
	movt	r1, #:upper16:.LC376	@,
	bl	memcpy	@
	mov	r0, #0	@ tmp217,
	strb	r0, [r4, #4]	@ tmp217,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2524:
	mov	r0, r1	@, strVidStd
	mov	r2, #3	@,
	movw	r1, #:lower16:.LC375	@,
	movt	r1, #:upper16:.LC375	@,
	bl	memcpy	@
	mov	r3, #0	@ tmp210,
	strb	r3, [r4, #3]	@ tmp210,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2523:
	mov	r0, r1	@, strVidStd
	mov	r2, #5	@,
	movw	r1, #:lower16:.LC374	@,
	movt	r1, #:upper16:.LC374	@,
	bl	memcpy	@
	mov	ip, #0	@ tmp203,
	strb	ip, [r4, #5]	@ tmp203,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2522:
	mov	r0, r1	@, strVidStd
	mov	r2, #5	@,
	movw	r1, #:lower16:.LC373	@,
	movt	r1, #:upper16:.LC373	@,
	bl	memcpy	@
	mov	r2, #0	@ tmp196,
	strb	r2, [r4, #5]	@ tmp196,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2521:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC372	@,
	movt	r1, #:upper16:.LC372	@,
	bl	memcpy	@
	mov	r1, #0	@ tmp189,
	strb	r1, [r4, #4]	@ tmp189,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2520:
	mov	r0, r1	@, strVidStd
	mov	r2, #3	@,
	movw	r1, #:lower16:.LC371	@,
	movt	r1, #:upper16:.LC371	@,
	bl	memcpy	@
	mov	r0, #0	@ tmp182,
	strb	r0, [r4, #3]	@ tmp182,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2519:
	mov	r0, r1	@, strVidStd
	mov	r2, #5	@,
	movw	r1, #:lower16:.LC370	@,
	movt	r1, #:upper16:.LC370	@,
	bl	memcpy	@
	mov	r3, #0	@ tmp175,
	strb	r3, [r4, #5]	@ tmp175,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2518:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC369	@,
	movt	r1, #:upper16:.LC369	@,
	bl	memcpy	@
	mov	ip, #0	@ tmp168,
	strb	ip, [r4, #4]	@ tmp168,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2517:
	mov	r0, r1	@, strVidStd
	mov	r2, #5	@,
	movw	r1, #:lower16:.LC368	@,
	movt	r1, #:upper16:.LC368	@,
	bl	memcpy	@
	mov	r2, #0	@ tmp161,
	strb	r2, [r4, #5]	@ tmp161,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2516:
	mov	r0, r1	@, strVidStd
	mov	r2, #5	@,
	movw	r1, #:lower16:.LC367	@,
	movt	r1, #:upper16:.LC367	@,
	bl	memcpy	@
	mov	r1, #0	@ tmp154,
	strb	r1, [r4, #5]	@ tmp154,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2515:
	mov	r0, r1	@, strVidStd
	mov	r2, #3	@,
	movw	r1, #:lower16:.LC366	@,
	movt	r1, #:upper16:.LC366	@,
	bl	memcpy	@
	mov	r0, #0	@ tmp147,
	strb	r0, [r4, #3]	@ tmp147,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2514:
	mov	r0, r1	@, strVidStd
	mov	r2, #4	@,
	movw	r1, #:lower16:.LC365	@,
	movt	r1, #:upper16:.LC365	@,
	bl	memcpy	@
	mov	r3, #0	@ tmp140,
	strb	r3, [r4, #4]	@ tmp140,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L2513:
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
	ldr	r7, [r3, #1348]	@ i, g_CurProcChan
	ldr	r5, [r2, #40]	@ pInst, <variable>.pSmInstArray
	cmp	r5, #0	@ pInst,
	beq	.L2538	@,
	movw	ip, #:lower16:190872	@ tmp174,
	movt	ip, #:upper16:190872	@ tmp174,
	ldr	r1, [r5, ip]	@ <variable>.Mode, <variable>.Mode
	cmp	r1, #0	@ <variable>.Mode,
	bne	.L2544	@,
.L2538:
	mov	r0, #0	@,
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2544:
	add	r6, r5, #200	@ D.43648, pInst,
	sub	r1, fp, #36	@,,
	mov	r0, r6	@, D.43648
	bl	GetRawStreamSize	@
	cmp	r0, #0	@,
	bne	.L2545	@,
	mov	r0, r6	@, D.43648
	sub	r1, fp, #32	@,,
	bl	GetRawStreamNum	@
	cmp	r0, #0	@,
	bne	.L2546	@,
.L2540:
	add	r6, r5, #98304	@ D.43656, pInst,
	sub	r1, fp, #44	@,,
	add	r6, r6, #224	@ D.43656, D.43656,
	mov	r0, r6	@, D.43656
	bl	GetSegStreamSize	@
	cmp	r0, #0	@,
	bne	.L2547	@,
.L2541:
	mov	r0, r6	@, D.43656
	sub	r1, fp, #40	@,,
	bl	GetSegStreamNum	@
	cmp	r0, #0	@,
	bne	.L2548	@,
.L2542:
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
	b	.L2538	@
.L2545:
	ldr	r2, .L2549	@,
	movw	r3, #8995	@,
	movw	r1, #:lower16:.LC163	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC163	@,
	bl	dprint_vfmw	@
	mov	r0, r6	@, D.43648
	sub	r1, fp, #32	@,,
	bl	GetRawStreamNum	@
	cmp	r0, #0	@,
	beq	.L2540	@,
.L2546:
	add	r6, r5, #98304	@ D.43656, pInst,
	ldr	r2, .L2549	@,
	add	r6, r6, #224	@ D.43656, D.43656,
	movw	r3, #9000	@,
	movw	r1, #:lower16:.LC163	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC163	@,
	bl	dprint_vfmw	@
	sub	r1, fp, #44	@,,
	mov	r0, r6	@, D.43656
	bl	GetSegStreamSize	@
	cmp	r0, #0	@,
	beq	.L2541	@,
.L2547:
	ldr	r2, .L2549	@,
	movw	r3, #9005	@,
	movw	r1, #:lower16:.LC163	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC163	@,
	bl	dprint_vfmw	@
	mov	r0, r6	@, D.43656
	sub	r1, fp, #40	@,,
	bl	GetSegStreamNum	@
	cmp	r0, #0	@,
	beq	.L2542	@,
.L2548:
	movw	r1, #:lower16:.LC163	@,
	ldr	r2, .L2549	@,
	movt	r1, #:upper16:.LC163	@,
	movw	r3, #9010	@,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	b	.L2542	@
.L2550:
	.align	2
.L2549:
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
	movw	r9, #:lower16:.LANCHOR0	@ tmp490,
	movt	r9, #:upper16:.LANCHOR0	@ tmp490,
	movw	r1, #:lower16:.LC413	@,
	movt	r1, #:upper16:.LC413	@,
	mov	r4, #0	@ tmp163,
	ldr	r2, [r9, #1348]	@, g_CurProcChan
	movw	r6, #16718	@ tmp162,
	str	r4, [fp, #-64]	@ tmp163, szAttach
	mov	r5, r0	@ p, p
	str	r6, [fp, #-68]	@ tmp162, szAttach
	str	r4, [fp, #-60]	@ tmp163, szAttach
	bl	seq_printf	@
	ldr	r6, [r9, #1348]	@ i, g_CurProcChan
	movw	r3, #:lower16:s_pFspInst	@ tmp170,
	movt	r3, #:upper16:s_pFspInst	@ tmp170,
	str	r4, [fp, #-48]	@ tmp163, RefNum
	ldr	r8, [r3, r6, asl #2]	@ pFsp, s_pFspInst
	cmp	r8, r4	@ pFsp,
	beq	.L2552	@,
	ldr	sl, [r9, r6, asl #2]	@ pChan, s_pstVfmwChan
	cmp	sl, r4	@ pChan,
	beq	.L2552	@,
	movw	r7, #:lower16:g_ChanCtx	@ tmp174,
	add	r2, r6, #32	@ tmp175, i,
	movt	r7, #:upper16:g_ChanCtx	@ tmp174,
	str	r4, [fp, #-56]	@ tmp163, NewNum
	str	r4, [fp, #-52]	@ tmp163, ReadNum
	ldr	r1, [r7, r2, asl #2]	@ tmp176, g_ChanCtx.ChanDecByVdhPlusOne
	subs	r0, r1, #1	@, tmp176,
	str	r0, [fp, #-116]	@, %sfp
	bmi	.L2581	@,
	ldr	r1, [fp, #-116]	@, %sfp
	movw	r4, #:lower16:g_VdmExtParam	@ tmp184,
	movt	r4, #:upper16:g_VdmExtParam	@ tmp184,
	mov	r2, #140	@ tmp187,
	mla	r7, r2, r1, r4	@ tmp188, tmp187,, tmp184
	ldr	r0, [r7, #4]	@ <variable>.VdmAttachStr.VdmAttachMode, <variable>.VdmAttachStr.VdmAttachMode
	cmp	r0, #0	@ <variable>.VdmAttachStr.VdmAttachMode,
	beq	.L2582	@,
	movw	r2, #:lower16:.LC416	@ tmp198,
	movt	r2, #:upper16:.LC416	@ tmp198,
	sub	r1, fp, #68	@,,
	str	r1, [fp, #-112]	@, %sfp
	ldmia	r2, {r0, r1}	@ tmp198,,
	mov	r4, r1, lsr #16	@ tmp201,,
	strb	r4, [fp, #-62]	@ tmp201, szAttach
	str	r0, [fp, #-68]	@, szAttach
	strh	r1, [fp, #-64]	@ movhi	@, szAttach
.L2554:
	sub	r2, fp, #52	@,,
	sub	r1, fp, #48	@,,
	sub	r3, fp, #56	@,,
	mov	r0, r6	@, i
	bl	VCTRL_GetChanImgNum	@
	mov	r0, r6	@, i
	bl	VCTRL_GetChanVoQue	@
	sub	r7, fp, #88	@ tmp207,,
	sub	r4, fp, #108	@ tmp209,,
	cmp	r0, #0	@ pstDecQue
	streq	r0, [fp, #-120]	@ pstDecQue, %sfp
	streq	r0, [fp, #-124]	@ pstDecQue, %sfp
	ldrneh	r1, [r0, #8]	@, <variable>.tail
	streq	r0, [fp, #-128]	@ pstDecQue, %sfp
	strne	r1, [fp, #-120]	@, %sfp
	mov	r1, r7	@, tmp207
	ldrneh	r2, [r0, #4]	@, <variable>.history
	strne	r2, [fp, #-128]	@, %sfp
	ldrneh	r0, [r0, #6]	@, <variable>.head
	strne	r0, [fp, #-124]	@, %sfp
	ldr	r0, [sl, #1032]	@, <variable>.eVidStd
	bl	VID_STD_Enum2Str	@
	ldr	r0, [sl, #824]	@, <variable>.eLastFrameState
	mov	r1, r4	@, tmp209
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
	mov	r3, r7	@, tmp207
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
	mov	r3, r4	@, tmp209
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
	ldr	r3, [sl, #1032]	@ temp.6543, <variable>.eVidStd
	cmp	r3, #1	@ temp.6543,
	beq	.L2583	@,
	sub	r0, r3, #10	@ tmp256, temp.6543,
	cmp	r0, #2	@ tmp256,
	bls	.L2584	@,
	cmp	r3, #2	@ temp.6543,
	beq	.L2585	@,
	cmp	r3, #18	@ temp.6543,
	beq	.L2586	@,
.L2559:
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	ldr	r3, [sl, #216]	@, <variable>.stChanMem_vdh.PhyAddr
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC437	@,
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC437	@,
	bl	seq_printf	@
	ldr	r3, [sl, #220]	@, <variable>.stChanMem_vdh.Length
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC438	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC438	@,
	bl	seq_printf	@
	ldr	r3, [sl, #232]	@, <variable>.stChanMem_scd.PhyAddr
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC439	@,
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC439	@,
	bl	seq_printf	@
	ldr	r3, [sl, #236]	@, <variable>.stChanMem_scd.Length
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC440	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC440	@,
	bl	seq_printf	@
	ldr	r3, [sl, #248]	@, <variable>.stChanMem_ctx.PhyAddr
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC441	@,
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC441	@,
	bl	seq_printf	@
	ldr	r3, [sl, #252]	@, <variable>.stChanMem_ctx.Length
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
	ldr	r3, [sl, #1048]	@, <variable>.stSynExtraData.s32DecMode
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC447	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC447	@,
	bl	seq_printf	@
	ldr	r3, [sl, #1052]	@, <variable>.stSynExtraData.s32DecOrderOutput
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC448	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC448	@,
	bl	seq_printf	@
	ldr	r3, [sl, #480]	@, <variable>.stRecentImg.format
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC390	@,
	movw	r2, #:lower16:.LC449	@,
	movt	r1, #:upper16:.LC390	@,
	movt	r2, #:upper16:.LC449	@,
	bl	seq_printf	@
	ldr	r3, [sl, #680]	@, <variable>.stRecentImg.eFramePackingType
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
	ldrb	r3, [r8, #56]	@ zero_extendqisi2	@ D.43826, <variable>.stInstCfg.s32DispLoopEnable
	cmp	r3, #0	@ D.43826,
	bne	.L2587	@,
.L2562:
	ldrsb	r3, [r8, #10]	@, <variable>.s32DecFsNum
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC464	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC464	@,
	bl	seq_printf	@
	ldrsb	r3, [r8, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	cmp	r3, #0	@ <variable>.s32DecFsNum,
	addgt	r4, r8, #34304	@ ivtmp.6533, pFsp,
	movgt	r6, #0	@ j.6550,
	addgt	r4, r4, #156	@ ivtmp.6533, ivtmp.6533,
	ble	.L2567	@,
.L2568:
	ldrsb	r2, [r4, #0]	@, <variable>.IsDecRef
	mov	r0, r5	@, p
	ldrsb	r3, [r4, #2]	@, <variable>.DispState
	movw	r1, #:lower16:.LC463	@,
	movt	r1, #:upper16:.LC463	@,
	add	r6, r6, #1	@ j.6550, j.6550,
	bl	seq_printf	@
	ldrsb	r2, [r8, #10]	@ <variable>.s32DecFsNum, <variable>.s32DecFsNum
	add	r4, r4, #60	@ ivtmp.6533, ivtmp.6533,
	cmp	r2, r6	@ <variable>.s32DecFsNum, j.6550
	ble	.L2567	@,
	tst	r6, #15	@ j.6550,
	bne	.L2568	@,
	movw	r1, #:lower16:.LC71	@,
	mov	r0, r5	@, p
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	b	.L2568	@
.L2591:
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	ldr	r4, [sl, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r4, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	beq	.L2588	@,
.L2575:
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	movw	r6, #:lower16:-858993459	@ tmp431,
	bl	seq_printf	@
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC475	@,
	movt	r1, #:upper16:.LC475	@,
	bl	seq_printf	@
	ldr	r1, [r9, #1452]	@ <variable>.u32FrFrameRate, <variable>.u32FrFrameRate
	movt	r6, #:upper16:-858993459	@ tmp431,
	movw	r2, #:lower16:.LANCHOR0	@ tmp427,
	movt	r2, #:upper16:.LANCHOR0	@ tmp427,
	umull	r0, r3, r6, r1	@, tmp430, tmp431, <variable>.u32FrFrameRate
	ldr	r6, [r9, #1372]	@ D.43874, <variable>.u32VaVdmLoad
	movs	r7, r3, lsr #3	@ VdhFps, tmp430,
	beq	.L2576	@,
	ldr	r4, [r8, #68]	@ temp.6553, <variable>.stInstCfg.s32DecFsWidth
	add	sl, r4, #15	@ tmp432, temp.6553,
	cmp	sl, #30	@ tmp432,
	bls	.L2576	@,
	ldr	r8, [r8, #72]	@ temp.6554, <variable>.stInstCfg.s32DecFsHeight
	add	r3, r8, #15	@ tmp433, temp.6554,
	cmp	r3, #30	@ tmp433,
	bhi	.L2589	@,
.L2576:
	mov	r8, #0	@ VdhCycle,
.L2577:
	movw	r4, #:lower16:-858993459	@ tmp461,
	movt	r4, #:upper16:-858993459	@ tmp461,
	mov	r3, #0	@,
	mov	r0, r5	@, p
	umull	r1, lr, r4, r6	@, tmp460, tmp461, D.43874
	movw	r2, #:lower16:.LC477	@,
	movw	r1, #:lower16:.LC476	@,
	movt	r2, #:upper16:.LC477	@,
	movt	r1, #:upper16:.LC476	@,
	mov	ip, lr, lsr #3	@ tmp459, tmp460,
	str	ip, [sp, #0]	@ tmp459,
	add	lr, ip, ip, asl #2	@, tmp467, tmp459, tmp459,
	sub	ip, r6, lr, asl #1	@ tmp469, D.43874, tmp467,
	str	ip, [sp, #4]	@ tmp469,
	bl	seq_printf	@
	ldr	ip, [r9, #1452]	@ <variable>.u32FrFrameRate, <variable>.u32FrFrameRate
	mov	r3, r7	@, VdhFps
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC478	@,
	movt	r1, #:upper16:.LC478	@,
	umull	r2, lr, r4, ip	@, tmp475, tmp461, <variable>.u32FrFrameRate
	movw	r2, #:lower16:.LC479	@,
	movt	r2, #:upper16:.LC479	@,
	mov	lr, lr, lsr #3	@ tmp473, tmp475,
	add	lr, lr, lr, asl #2	@, tmp479, tmp473, tmp473,
	sub	ip, ip, lr, asl #1	@ tmp481, <variable>.u32FrFrameRate, tmp479,
	str	ip, [sp, #0]	@ tmp481,
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
.L2552:
	mov	r0, #0	@,
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L2582:
	movw	r7, #:lower16:.LC415	@ tmp192,
	movt	r7, #:upper16:.LC415	@ tmp192,
	sub	r0, fp, #68	@,,
	str	r0, [fp, #-112]	@, %sfp
	ldmia	r7, {r0, r1, r2}	@ tmp192,,,
	ldr	lr, [fp, #-112]	@, %sfp
	mov	r3, r2, lsr #16	@ tmp195,,
	strb	r3, [fp, #-58]	@ tmp195, szAttach
	stmia	lr!, {r0, r1}	@,,
	strh	r2, [lr, #0]	@ movhi	@, szAttach
	b	.L2554	@
.L2567:
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	mov	r4, r8	@ ivtmp.6529, pFsp
	bl	seq_printf	@
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC465	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC465	@,
	mov	r3, #64	@,
	mov	r7, #1	@ ivtmp.6526,
	bl	seq_printf	@
	mov	r6, #0	@ ivtmp.6525,
	b	.L2571	@
.L2592:
	tst	r6, #15	@ ivtmp.6525,
	beq	.L2590	@,
.L2573:
	ldrsb	r2, [r4, #96]	@, <variable>.s32IsRef
	mov	r0, r5	@, p
	ldrsb	r3, [r4, #97]	@, <variable>.s32DispState
	movw	r1, #:lower16:.LC463	@,
	movt	r1, #:upper16:.LC463	@,
	bl	seq_printf	@
	cmp	r7, #63	@ ivtmp.6526,
	bgt	.L2591	@,
.L2574:
	add	r6, r6, #1	@ ivtmp.6525, ivtmp.6525,
	add	r7, r7, #1	@ ivtmp.6526, ivtmp.6526,
	add	r4, r4, #536	@ ivtmp.6529, ivtmp.6529,
.L2571:
	cmp	r6, #0	@ ivtmp.6525,
	movw	r1, #:lower16:.LC463	@,
	mov	r0, r5	@, p
	movt	r1, #:upper16:.LC463	@,
	bne	.L2592	@,
	ldrsb	r2, [r4, #96]	@, <variable>.s32IsRef
	ldrsb	r3, [r4, #97]	@, <variable>.s32DispState
	bl	seq_printf	@
	b	.L2574	@
.L2590:
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	b	.L2573	@
.L2587:
	sxtb	r3, r3	@, D.43826
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
	addgt	r4, r8, #38144	@ ivtmp.6539, pFsp,
	movgt	r6, #0	@ j,
	addgt	r4, r4, #156	@ ivtmp.6539, ivtmp.6539,
	ble	.L2563	@,
.L2564:
	ldrsb	r2, [r4, #0]	@, <variable>.IsDecRef
	mov	r0, r5	@, p
	ldrsb	r3, [r4, #2]	@, <variable>.DispState
	movw	r1, #:lower16:.LC463	@,
	movt	r1, #:upper16:.LC463	@,
	add	r6, r6, #1	@ j, j,
	bl	seq_printf	@
	ldrsb	r0, [r8, #11]	@ <variable>.s32DispFsNum, <variable>.s32DispFsNum
	add	r4, r4, #60	@ ivtmp.6539, ivtmp.6539,
	cmp	r0, r6	@ <variable>.s32DispFsNum, j
	ble	.L2563	@,
	tst	r6, #15	@ j,
	bne	.L2564	@,
	movw	r1, #:lower16:.LC71	@,
	mov	r0, r5	@, p
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	b	.L2564	@
.L2563:
	movw	r1, #:lower16:.LC71	@,
	mov	r0, r5	@, p
	movt	r1, #:upper16:.LC71	@,
	bl	seq_printf	@
	b	.L2562	@
.L2584:
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC432	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC432	@,
	ldr	r3, [sl, #52]	@, <variable>.stChanCfg.StdExt.Vp6Ext.bReversed
	bl	seq_printf	@
	b	.L2559	@
.L2589:
	ldr	ip, [r2, #1416]	@ <variable>.u32VaVdmKiloCycle, <variable>.u32VaVdmKiloCycle
	mov	lr, #1000	@ tmp437,
	mov	r1, r7	@, VdhFps
	str	r3, [fp, #-132]	@,
	mul	r0, lr, ip	@, tmp437, <variable>.u32VaVdmKiloCycle
	bl	__aeabi_uidiv	@
	cmp	r4, #0	@ temp.6553,
	movlt	r4, sl	@ temp.6553, tmp432
	mov	r1, r4, asr #4	@, temp.6553,
	bl	__aeabi_uidiv	@
	ldr	r2, [fp, #-132]	@,
	cmp	r8, #0	@ temp.6554,
	movlt	r8, r2	@ temp.6554, tmp433
	mov	r1, r8, asr #4	@, temp.6554,
	bl	__aeabi_uidiv	@
	mov	r8, r0	@ VdhCycle,
	b	.L2577	@
.L2588:
	movw	r4, #:lower16:249200	@ tmp397,
	movt	r4, #:upper16:249200	@ tmp397,
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC466	@,
	movw	r7, #:lower16:.LANCHOR4	@ tmp401,
	movt	r1, #:upper16:.LC466	@,
	movt	r7, #:upper16:.LANCHOR4	@ tmp401,
	bl	seq_printf	@
	ldr	r3, [sl, r4]	@, <variable>.s32CurFsSize
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC467	@,
	movw	r2, #:lower16:.LC468	@,
	movt	r1, #:upper16:.LC467	@,
	movt	r2, #:upper16:.LC468	@,
	bl	seq_printf	@
	ldr	r3, [r7, #-3528]	@, g_u32DFSMaxAllocTime
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC467	@,
	movw	r2, #:lower16:.LC469	@,
	movt	r1, #:upper16:.LC467	@,
	movt	r2, #:upper16:.LC469	@,
	movw	r7, #:lower16:249208	@ tmp421,
	bl	seq_printf	@
	movw	ip, #:lower16:249204	@ tmp405,
	movt	ip, #:upper16:249204	@ tmp405,
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC467	@,
	movw	r2, #:lower16:.LC470	@,
	ldr	r3, [sl, ip]	@, <variable>.s32RefNum
	movt	r1, #:upper16:.LC467	@,
	movt	r2, #:upper16:.LC470	@,
	movt	r7, #:upper16:249208	@ tmp421,
	bl	seq_printf	@
	movw	r2, #:lower16:251472	@ tmp411,
	movt	r2, #:upper16:251472	@ tmp411,
	movw	r3, #:lower16:249212	@ tmp409,
	movt	r3, #:upper16:249212	@ tmp409,
	mov	r0, r5	@, p
	ldr	r6, [sl, r2]	@ <variable>.stDynamicFSTimestamp.u32PreAllocTime, <variable>.stDynamicFSTimestamp.u32PreAllocTime
	movw	r1, #:lower16:.LC471	@,
	ldr	r3, [sl, r3]	@ <variable>.s32PreAllocFrmNum, <variable>.s32PreAllocFrmNum
	movt	r1, #:upper16:.LC471	@,
	movw	r2, #:lower16:.LC472	@,
	movt	r2, #:upper16:.LC472	@,
	str	r6, [sp, #0]	@ <variable>.stDynamicFSTimestamp.u32PreAllocTime,
	bl	seq_printf	@
	movw	r1, #:lower16:251476	@ tmp417,
	movt	r1, #:upper16:251476	@ tmp417,
	movw	r0, #:lower16:249216	@ tmp415,
	movt	r0, #:upper16:249216	@ tmp415,
	ldr	r4, [sl, r1]	@ <variable>.stDynamicFSTimestamp.u32MMZAllocTime, <variable>.stDynamicFSTimestamp.u32MMZAllocTime
	movw	r2, #:lower16:.LC473	@,
	ldr	r3, [sl, r0]	@ <variable>.s32MMZFrmNum, <variable>.s32MMZFrmNum
	movt	r2, #:upper16:.LC473	@,
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC471	@,
	movt	r1, #:upper16:.LC471	@,
	str	r4, [sp, #0]	@ <variable>.stDynamicFSTimestamp.u32MMZAllocTime,
	bl	seq_printf	@
	movw	ip, #:lower16:251480	@ tmp423,
	movt	ip, #:upper16:251480	@ tmp423,
	ldr	r3, [sl, r7]	@ <variable>.s32NeededFrameNum, <variable>.s32NeededFrameNum
	movw	r1, #:lower16:.LC471	@,
	movw	r2, #:lower16:.LC474	@,
	ldr	r6, [sl, ip]	@ <variable>.stDynamicFSTimestamp.u32AllTime, <variable>.stDynamicFSTimestamp.u32AllTime
	movt	r1, #:upper16:.LC471	@,
	movt	r2, #:upper16:.LC474	@,
	mov	r0, r5	@, p
	str	r6, [sp, #0]	@ <variable>.stDynamicFSTimestamp.u32AllTime,
	bl	seq_printf	@
	b	.L2575	@
.L2583:
	movw	lr, #:lower16:USE_FF_APT_EN	@ tmp248,
	movt	lr, #:upper16:USE_FF_APT_EN	@ tmp248,
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
	b	.L2559	@
.L2581:
	movw	lr, #:lower16:.LC414	@ tmp178,
	movt	lr, #:upper16:.LC414	@ tmp178,
	sub	r3, fp, #68	@,,
	str	r3, [fp, #-112]	@, %sfp
	ldr	r4, [lr, #0]	@ tmp181,
	mov	ip, r4, lsr #16	@ tmp182, tmp181,
	strh	r4, [fp, #-68]	@ movhi	@ tmp181, szAttach
	strb	ip, [fp, #-66]	@ tmp182, szAttach
	b	.L2554	@
.L2585:
	mov	r4, #300	@ tmp265,
	mov	r0, r5	@, p
	mla	r4, r4, r6, r9	@ tmp266, tmp265, i, tmp490
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC433	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC433	@,
	ldr	r3, [r4, #1456]	@, <variable>.u32SkipFind
	bl	seq_printf	@
	ldr	r3, [r4, #1460]	@, <variable>.u32SkipDiscard
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movw	r2, #:lower16:.LC434	@,
	movt	r1, #:upper16:.LC66	@,
	movt	r2, #:upper16:.LC434	@,
	bl	seq_printf	@
	movw	r2, #:lower16:267360	@ tmp280,
	movt	r2, #:upper16:267360	@ tmp280,
	mov	r0, r5	@, p
	movw	r1, #:lower16:.LC66	@,
	movt	r1, #:upper16:.LC66	@,
	ldrb	r3, [sl, r2]	@ zero_extendqisi2	@ tmp282,
	movw	r2, #:lower16:.LC435	@,
	movt	r2, #:upper16:.LC435	@,
	and	r3, r3, #1	@, tmp282,
	bl	seq_printf	@
	b	.L2559	@
.L2586:
	ldr	lr, [sl, #1000]	@ <variable>.stRecentUsrdecFrame.s32YHeight, <variable>.stRecentUsrdecFrame.s32YHeight
	mov	ip, #984	@ tmp291,
	ldr	r2, [sl, #976]	@ <variable>.stRecentUsrdecFrame.enFmt, <variable>.stRecentUsrdecFrame.enFmt
	movw	r1, #:lower16:.LC436	@,
	ldr	r3, [sl, #996]	@ <variable>.stRecentUsrdecFrame.s32YWidth, <variable>.stRecentUsrdecFrame.s32YWidth
	movt	r1, #:upper16:.LC436	@,
	str	lr, [sp, #0]	@ <variable>.stRecentUsrdecFrame.s32YHeight,
	mov	r0, r5	@, p
	ldr	r7, [sl, #1008]	@ <variable>.stRecentUsrdecFrame.s32LumaStride, <variable>.stRecentUsrdecFrame.s32LumaStride
	str	r7, [sp, #4]	@ <variable>.stRecentUsrdecFrame.s32LumaStride,
	ldr	r6, [sl, #1020]	@ <variable>.stRecentUsrdecFrame.s32ChromStride, <variable>.stRecentUsrdecFrame.s32ChromStride
	str	r6, [sp, #8]	@ <variable>.stRecentUsrdecFrame.s32ChromStride,
	ldrd	r6, [sl, ip]	@ <variable>.stRecentUsrdecFrame.Pts, pChan, tmp291
	strd	r6, [sp, #16]	@ <variable>.stRecentUsrdecFrame.Pts,,
	bl	seq_printf	@
	b	.L2559	@
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
	.type	CSWTCH.916, %object
	.size	CSWTCH.916, 8
CSWTCH.916:
	.word	2
	.word	3
	.type	CSWTCH.919, %object
	.size	CSWTCH.919, 32
CSWTCH.919:
	.word	3
	.word	3
	.word	3
	.word	3
	.word	3
	.word	1
	.word	1
	.word	1
	.type	__func__.39042, %object
	.size	__func__.39042, 18
__func__.39042:
	.ascii	"VCTRL_SetCallBack\000"
	.space	2
	.type	__func__.39008, %object
	.size	__func__.39008, 18
__func__.39008:
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
	.type	__func__.43495, %object
	.size	__func__.43495, 20
__func__.43495:
	.ascii	"vfmw_read_proc_info\000"
	.type	__func__.44511, %object
	.size	__func__.44511, 21
__func__.44511:
	.ascii	"VCTRL_RequestChanMem\000"
	.space	3
	.type	__func__.42398, %object
	.size	__func__.42398, 14
__func__.42398:
	.ascii	"DecChanSyntax\000"
	.space	2
	.type	__func__.41220, %object
	.size	__func__.41220, 19
__func__.41220:
	.ascii	"VCTRL_FlushDecoder\000"
	.space	1
	.type	__func__.40940, %object
	.size	__func__.40940, 23
__func__.40940:
	.ascii	"VCTRL_ReleaseChanImage\000"
	.space	1
	.type	__func__.40810, %object
	.size	__func__.40810, 19
__func__.40810:
	.ascii	"VCTRL_GetChanImage\000"
	.space	1
	.type	__func__.39354, %object
	.size	__func__.39354, 29
__func__.39354:
	.ascii	"VCTRL_PartitionMemForStdUser\000"
	.space	3
	.type	__func__.42806, %object
	.size	__func__.42806, 18
__func__.42806:
	.ascii	"GetExtraRefFrmNum\000"
	.space	2
	.type	__func__.42842, %object
	.size	__func__.42842, 19
__func__.42842:
	.ascii	"GetExtraDispFrmNum\000"
	.space	1
	.type	__func__.42878, %object
	.size	__func__.42878, 16
__func__.42878:
	.ascii	"GetExtraCtrlCmd\000"
	.type	__func__.42713, %object
	.size	__func__.42713, 24
__func__.42713:
	.ascii	"VCTRL_ExtAccGetDecParam\000"
	.type	__func__.43995, %object
	.size	__func__.43995, 16
__func__.43995:
	.ascii	"vfmw_write_proc\000"
	.type	__func__.40335, %object
	.size	__func__.40335, 17
__func__.40335:
	.ascii	"VCTRL_ConfigChan\000"
	.space	3
	.type	CSWTCH.922, %object
	.size	CSWTCH.922, 32
CSWTCH.922:
	.word	3
	.word	3
	.word	3
	.word	3
	.word	3
	.word	1
	.word	1
	.word	1
	.type	__func__.43634, %object
	.size	__func__.43634, 19
__func__.43634:
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
	.ascii	"DFS, Wait Partition\012\000"
	.space	3
.LC226:
	.ascii	"DFS, Partition fail, u32DynamicFrameStoreAllocEn: %"
	.ascii	"d, eFspPartitionState: %d\012\000"
	.space	2
.LC227:
	.ascii	"line: %d Flush DPB failed!\012\000"
.LC228:
	.ascii	"VCTRL_FlushDecoder\012\000"
.LC229:
	.ascii	"fuction return value is null,%s %d MVC_OK != MVC_Fl"
	.ascii	"ushDPB!!\012\000"
	.space	3
.LC230:
	.ascii	"pImage is NULL\000"
	.space	1
.LC231:
	.ascii	"call VCTRL_ReleaseChanImage, ChanID, ImgID = %d,%d\012"
	.ascii	"\000"
.LC232:
	.ascii	"vdm_ctrl.c,L%d: Chan inactive\012\000"
	.space	1
.LC233:
	.ascii	"vdm_ctrl.c,L%d: This channel is not opened\012\000"
.LC234:
	.ascii	"%s call SYNTAX_ReleaseImage failed\012\000"
.LC235:
	.ascii	"call VCTRL_GetChanImage, ChanID = %d,\012\000"
	.space	1
.LC236:
	.ascii	"%s: view_0 id(%d) > view_1 id(%d), error!\012\000"
	.space	1
.LC237:
	.ascii	"%s: continuous view0 id(%d)!\012\000"
	.space	2
.LC238:
	.ascii	"%s: continuous view1 id(%d)!\012\000"
	.space	2
.LC239:
	.ascii	"vfmw_ctrl.c,L%d: VCTRL_GetChanCfg error\012\000"
	.space	3
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
	.ascii	"%-25s :%d.%d fps\012\000"
	.space	2
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
	.size	s_VfmwCTrl, 192
s_VfmwCTrl:
	.space	192
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
	.type	last_rec_pos_time.42392, %object
	.size	last_rec_pos_time.42392, 64
last_rec_pos_time.42392:
	.space	64
	.type	last_rec_pos_decparam_time.42393, %object
	.size	last_rec_pos_decparam_time.42393, 64
last_rec_pos_decparam_time.42393:
	.space	64
	.type	ChanPriTab.42276, %object
	.size	ChanPriTab.42276, 64
ChanPriTab.42276:
	.space	64
	.type	g_ActivateLock, %object
	.size	g_ActivateLock, 12
g_ActivateLock:
	.space	12
	.type	last_rec_pos_time.40937, %object
	.size	last_rec_pos_time.40937, 64
last_rec_pos_time.40937:
	.space	64
	.type	vfmw_save_yuv_file, %object
	.size	vfmw_save_yuv_file, 128
vfmw_save_yuv_file:
	.space	128
	.type	save_yuv_with_crop, %object
	.size	save_yuv_with_crop, 4
save_yuv_with_crop:
	.space	4
	.type	last_rec_pos_time.40815, %object
	.size	last_rec_pos_time.40815, 64
last_rec_pos_time.40815:
	.space	64
	.type	g_DSPState, %object
	.size	g_DSPState, 64
g_DSPState:
	.space	64
	.type	PrioArray.40044, %object
	.size	PrioArray.40044, 64
PrioArray.40044:
	.space	64
	.type	FspInstInfo.39347, %object
	.size	FspInstInfo.39347, 3852
FspInstInfo.39347:
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
	.type	LastEventTime.38963, %object
	.size	LastEventTime.38963, 4
LastEventTime.38963:
	.space	4
	.type	vfmw_save_str_file, %object
	.size	vfmw_save_str_file, 128
vfmw_save_str_file:
	.space	128
	.type	save_file_cnt.42952, %object
	.size	save_file_cnt.42952, 4
save_file_cnt.42952:
	.space	4
	.type	save_str_chan_num, %object
	.size	save_str_chan_num, 4
save_str_chan_num:
	.space	4
	.type	vfmw_save_seg_file, %object
	.size	vfmw_save_seg_file, 128
vfmw_save_seg_file:
	.space	128
	.type	save_file_cnt.42955, %object
	.size	save_file_cnt.42955, 4
save_file_cnt.42955:
	.space	4
	.type	save_seg_chan_num, %object
	.size	save_seg_chan_num, 4
save_seg_chan_num:
	.space	4
	.type	save_file_cnt.42960, %object
	.size	save_file_cnt.42960, 4
save_file_cnt.42960:
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
	.type	cmd.43963, %object
	.size	cmd.43963, 256
cmd.43963:
	.space	256
	.type	str.43964, %object
	.size	str.43964, 256
str.43964:
	.space	256
	.type	Capability.40321, %object
	.size	Capability.40321, 148
Capability.40321:
	.space	148
	.type	PrioArray.40320, %object
	.size	PrioArray.40320, 64
PrioArray.40320:
	.space	64
	.type	PrioArray.40077, %object
	.size	PrioArray.40077, 64
PrioArray.40077:
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
