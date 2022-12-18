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
	.file	"vfmw.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(vfmw) -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw)
@ -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/vfmw/vfmw_v4.0/firmware/product/Hi3798MV100/.vfmw.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/product/Hi3798MV100/vfmw.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/vfmw/vfmw_v4.0/firmware/product/Hi3798MV100/vfmw.o -O2 -Wall
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
	.global	VDM_ResetClock
	.type	VDM_ResetClock, %function
VDM_ResetClock:
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
	movw	ip, #:lower16:g_pstRegCrg	@ tmp139,
	movt	ip, #:upper16:g_pstRegCrg	@ tmp139,
	ldr	r1, [ip, #0]	@ g_pstRegCrg.443, g_pstRegCrg
	ldr	r0, [r1, #120]	@ D.50070, <variable>.PERI_CRG30.u32
	bfc	r0, #12, #5	@ u32TmpValue,,
	bfc	r0, #17, #1	@ u32TmpValue,,
	str	r0, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r2, [ip, #0]	@ g_pstRegCrg.546, g_pstRegCrg
	orr	r3, r0, #131072	@ u32TmpValue, u32TmpValue,
	str	r3, [r2, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDM_ResetClock, .-VDM_ResetClock
	.align	2
	.global	VDM_OpenHardware
	.type	VDM_OpenHardware, %function
VDM_OpenHardware:
	.fnstart
.LFB1532:
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
	movw	ip, #:lower16:g_pstRegCrg	@ tmp144,
	movt	ip, #:upper16:g_pstRegCrg	@ tmp144,
	ldr	r3, [ip, #0]	@ g_pstRegCrg.444, g_pstRegCrg
	ldr	r0, [r3, #120]	@ D.50077, <variable>.PERI_CRG30.u32
	orr	r2, r0, #3	@ u32TmpValue, D.50077,
	bfc	r2, #4, #1	@ u32TmpValue,,
	bfc	r2, #6, #1	@ u32TmpValue,,
	bfc	r2, #8, #2	@ u32TmpValue,,
	str	r2, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r1, [ip, #0]	@ g_pstRegCrg.443, g_pstRegCrg
	ldr	r0, [r1, #120]	@ D.50663, <variable>.PERI_CRG30.u32
	bfc	r0, #12, #5	@ u32TmpValue,,
	bfc	r0, #17, #1	@ u32TmpValue,,
	str	r0, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r3, [ip, #0]	@ g_pstRegCrg.571, g_pstRegCrg
	orr	r2, r0, #131072	@ u32TmpValue, u32TmpValue,
	str	r2, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDM_OpenHardware, .-VDM_OpenHardware
	.align	2
	.global	VDM_CloseHardware
	.type	VDM_CloseHardware, %function
VDM_CloseHardware:
	.fnstart
.LFB1533:
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
	movw	r1, #:lower16:g_pstRegCrg	@ tmp138,
	movt	r1, #:upper16:g_pstRegCrg	@ tmp138,
	ldr	r2, [r1, #0]	@ g_pstRegCrg.445, g_pstRegCrg
	ldr	r0, [r2, #120]	@ D.50084, <variable>.PERI_CRG30.u32
	orr	r3, r0, #80	@ u32TmpValue, D.50084,
	bfc	r3, #0, #1	@ u32TmpValue,,
	bfc	r3, #1, #1	@ u32TmpValue,,
	str	r3, [r2, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDM_CloseHardware, .-VDM_CloseHardware
	.align	2
	.global	SCD_OpenHardware
	.type	SCD_OpenHardware, %function
SCD_OpenHardware:
	.fnstart
.LFB1534:
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
	movw	r0, #:lower16:g_pstRegCrg	@ tmp138,
	movt	r0, #:upper16:g_pstRegCrg	@ tmp138,
	ldr	r3, [r0, #0]	@ g_pstRegCrg.446, g_pstRegCrg
	ldr	r2, [r3, #120]	@ D.50091, <variable>.PERI_CRG30.u32
	bfc	r2, #5, #1	@ u32TmpValue,,
	str	r2, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SCD_OpenHardware, .-SCD_OpenHardware
	.align	2
	.global	SCD_CloseHardware
	.type	SCD_CloseHardware, %function
SCD_CloseHardware:
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
	movw	r1, #:lower16:g_pstRegCrg	@ tmp138,
	movt	r1, #:upper16:g_pstRegCrg	@ tmp138,
	ldr	r3, [r1, #0]	@ g_pstRegCrg.447, g_pstRegCrg
	ldr	r0, [r3, #120]	@ D.50098, <variable>.PERI_CRG30.u32
	orr	r2, r0, #32	@ u32TmpValue, D.50098,
	str	r2, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SCD_CloseHardware, .-SCD_CloseHardware
	.align	2
	.global	BPD_OpenHardware
	.type	BPD_OpenHardware, %function
BPD_OpenHardware:
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
	movw	ip, #:lower16:g_pstRegCrg	@ tmp138,
	movt	ip, #:upper16:g_pstRegCrg	@ tmp138,
	mov	r0, #0	@,
	ldr	r3, [ip, #0]	@ g_pstRegCrg.448, g_pstRegCrg
	ldr	r1, [r3, #136]	@ D.50105, <variable>.PERI_CRG34.u32
	orr	r2, r1, #1	@ u32TmpValue, D.50105,
	bfc	r2, #4, #1	@ u32TmpValue,,
	str	r2, [r3, #136]	@ u32TmpValue, <variable>.PERI_CRG34.u32
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	BPD_OpenHardware, .-BPD_OpenHardware
	.align	2
	.global	VDEC_Resume
	.type	VDEC_Resume, %function
VDEC_Resume:
	.fnstart
.LFB1544:
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
	bl	VCTRL_Resume	@
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDEC_Resume, .-VDEC_Resume
	.align	2
	.global	VDEC_Suspend
	.type	VDEC_Suspend, %function
VDEC_Suspend:
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
	bl	VCTRL_Suspend	@
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC1	@,
	movt	r1, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDEC_Suspend, .-VDEC_Suspend
	.align	2
	.global	GetVdecCapability
	.type	GetVdecCapability, %function
GetVdecCapability:
	.fnstart
.LFB1542:
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
	mov	r1, #148	@,
	mov	r4, r0	@ pCap, pCap
	bl	__memzero	@
	mov	r2, #16	@ tmp134,
	mov	r1, #50	@ tmp135,
	mov	r0, #4096	@ tmp136,
	mov	r3, #2304	@ tmp137,
	str	r2, [r4, #80]	@ tmp134, <variable>.SupportedStd
	movw	ip, #:lower16:424673280	@ tmp158,
	str	r1, [r4, #4]	@ tmp135, <variable>.s32MaxBitRate
	movt	ip, #:upper16:424673280	@ tmp158,
	mov	r1, #0	@ tmp139,
	str	r0, [r4, #8]	@ tmp136, <variable>.s32MaxFrameWidth
	str	r3, [r4, #12]	@ tmp137, <variable>.s32MaxFrameHeight
	mov	r0, #3	@ tmp140,
	mov	r3, #2	@ tmp141,
	str	r2, [r4, #0]	@ tmp134, <variable>.s32MaxChanNum
	str	ip, [r4, #16]	@ tmp158, <variable>.s32MaxPixelPerSec
	mov	r2, #8	@ tmp143,
	mov	ip, #6	@ tmp142,
	str	r1, [r4, #20]	@ tmp139, <variable>.SupportedStd
	str	r0, [r4, #24]	@ tmp140, <variable>.SupportedStd
	mov	r1, #9	@ tmp144,
	mov	r0, #1	@ tmp145,
	str	r3, [r4, #28]	@ tmp141, <variable>.SupportedStd
	str	ip, [r4, #32]	@ tmp142, <variable>.SupportedStd
	mov	r3, #5	@ tmp146,
	mov	ip, #4	@ tmp147,
	str	r2, [r4, #36]	@ tmp143, <variable>.SupportedStd
	str	r1, [r4, #40]	@ tmp144, <variable>.SupportedStd
	mov	r2, #10	@ tmp148,
	mov	r1, #14	@ tmp149,
	str	r0, [r4, #44]	@ tmp145, <variable>.SupportedStd
	str	r3, [r4, #48]	@ tmp146, <variable>.SupportedStd
	mov	r0, #11	@ tmp150,
	mov	r3, #12	@ tmp151,
	str	ip, [r4, #52]	@ tmp147, <variable>.SupportedStd
	str	r2, [r4, #56]	@ tmp148, <variable>.SupportedStd
	mov	ip, #13	@ tmp152,
	str	r1, [r4, #60]	@ tmp149, <variable>.SupportedStd
	mov	r2, #15	@ tmp153,
	str	r0, [r4, #64]	@ tmp150, <variable>.SupportedStd
	mov	r1, #17	@ tmp155,
	str	r3, [r4, #68]	@ tmp151, <variable>.SupportedStd
	mov	r0, #18	@ tmp156,
	mov	r3, #19	@ tmp157,
	str	ip, [r4, #72]	@ tmp152, <variable>.SupportedStd
	str	r2, [r4, #76]	@ tmp153, <variable>.SupportedStd
	str	r1, [r4, #84]	@ tmp155, <variable>.SupportedStd
	str	r0, [r4, #88]	@ tmp156, <variable>.SupportedStd
	str	r3, [r4, #92]	@ tmp157, <variable>.SupportedStd
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	GetVdecCapability, .-GetVdecCapability
	.align	2
	.global	VDEC_Control
	.type	VDEC_Control, %function
VDEC_Control:
	.fnstart
.LFB1541:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #60
	sub	sp, sp, #60	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r3, #:lower16:.LANCHOR0	@ tmp312,
	movt	r3, #:upper16:.LANCHOR0	@ tmp312,
	mov	r6, r0	@ ChanID, ChanID
	mov	r4, r2	@ pArgs, pArgs
	ldr	r0, [r3, #0]	@ g_VfmwEnableFlag, g_VfmwEnableFlag
	cmp	r0, #1	@ g_VfmwEnableFlag,
	beq	.L20	@,
	movw	r1, #:lower16:.LC2	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC2	@,
	mvn	r5, #0	@ ret,
	bl	dprint_vfmw	@
.L21:
	mov	r0, r5	@, ret
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L20:
	cmp	r1, #59	@ eCmdID,
	ldrls	pc, [pc, r1, asl #2]	@ eCmdID
	b	.L70	@
.L48:
	.word	.L23
	.word	.L24
	.word	.L23
	.word	.L23
	.word	.L25
	.word	.L26
	.word	.L23
	.word	.L23
	.word	.L27
	.word	.L28
	.word	.L23
	.word	.L23
	.word	.L23
	.word	.L23
	.word	.L29
	.word	.L30
	.word	.L31
	.word	.L70
	.word	.L32
	.word	.L33
	.word	.L34
	.word	.L35
	.word	.L23
	.word	.L23
	.word	.L36
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L37
	.word	.L38
	.word	.L70
	.word	.L39
	.word	.L40
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L23
	.word	.L23
	.word	.L41
	.word	.L42
	.word	.L43
	.word	.L44
	.word	.L45
	.word	.L46
	.word	.L23
	.word	.L47
.L117:
	mov	r2, r6	@, ChanID
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC8	@,
	movt	r1, #:upper16:.LC8	@,
	bl	dprint_vfmw	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, pArgs
	bl	VCTRL_SetFsParamToChan	@
	mov	r0, r6	@, ChanID
	bl	VCTRL_RequestChanMem	@
	cmp	r0, #0	@,
	bne	.L118	@,
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	mov	r1, #2	@,
	bl	VCTRL_SetChanFsPartitionState	@
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC9	@,
	movt	r1, #:upper16:.LC9	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
.L119:
	mov	r0, r6	@, ChanID
	mov	r1, #0	@,
	bl	VCTRT_SetChanCtrlState	@
	subs	r5, r0, #0	@ ret,
	beq	.L21	@,
.L70:
	mvn	r5, #0	@ ret,
	b	.L21	@
.L37:
	cmp	r2, #0	@ pArgs,
	beq	.L140	@,
.L65:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	sub	r1, fp, #80	@,,
	bl	VCTRL_GetUsrdecFrame	@
	ldr	r5, [fp, #-72]	@ stMem.Length, stMem.Length
	ldr	r2, [fp, #-80]	@ stMem.PhyAddr, stMem.PhyAddr
	stmia	r4, {r2, r5}	@ phole stm
.L135:
	cmp	r0, #0	@ ret
	moveq	r5, r0	@, ret, ret
	mvnne	r5, #0	@, ret,
.L136:
	bl	VCTRL_EnableAllInt	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L21	@
.L24:
	cmp	r2, #0	@ pArgs,
	beq	.L141	@,
.L49:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r4	@, pArgs
	bl	GetVdecCapability	@
	mov	r5, #0	@ ret,
	bl	VCTRL_EnableAllInt	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L21	@
.L25:
	cmp	r2, #0	@ pArgs,
	beq	.L142	@,
	ldr	r0, [r2, #0]	@ prephitmp.757,* pArgs
	cmp	r0, #33	@ prephitmp.757,
	bgt	.L143	@,
.L52:
	add	r1, r4, #4	@, pArgs,
	bl	VCTRL_CreateChan	@
	movw	r1, #:lower16:.LC6	@,
	movt	r1, #:upper16:.LC6	@,
	mov	r5, r0	@ ret.818,
	mov	r0, #2	@,
	mov	r2, r5	@, ret.818
	bl	dprint_vfmw	@
	cmp	r5, #0	@ ret.818,
	str	r5, [r4, #0]	@ ret.818,* pArgs
	blt	.L70	@,
.L75:
	mov	r5, #0	@ ret,
	b	.L21	@
.L47:
	cmp	r2, #0	@ pArgs,
	beq	.L144	@,
	mov	r0, r6	@, ChanID
	mov	r1, #1	@,
	bl	VCTRT_SetChanCtrlState	@
	cmp	r0, #0	@,
	bne	.L70	@,
	mov	r0, r6	@, ChanID
	bl	VCTRL_RlsAllFrameNode	@
	subs	r5, r0, #0	@ ret,
	beq	.L117	@,
	mov	r2, r6	@, ChanID
	movw	r1, #:lower16:.LC7	@,
	mov	r0, #31	@,
	movt	r1, #:upper16:.LC7	@,
	bl	dprint_vfmw	@
	b	.L21	@
.L46:
	cmp	r2, #0	@ pArgs,
	beq	.L145	@,
.L73:
	add	r5, r6, r3	@ tmp292, ChanID, tmp312
	add	r1, r3, r6, asl #2	@, tmp299, tmp312, ChanID,
	mov	r2, #0	@ tmp294,
	strb	r2, [r5, #4]	@ tmp294, g_LowDelayCalcStat
	mov	r5, r2	@ ret, tmp294
	str	r2, [r1, #20]	@ tmp294, g_LowDelayCalcHandle
	b	.L21	@
.L45:
	cmp	r2, #0	@ pArgs,
	beq	.L146	@,
.L72:
	add	r0, r6, r3	@ tmp280, ChanID, tmp312
	mov	ip, #1	@ tmp282,
	add	r3, r3, r6, asl #2	@, tmp287, tmp312, ChanID,
	mov	r5, #0	@ ret,
	strb	ip, [r0, #4]	@ tmp282, g_LowDelayCalcStat
	ldr	r2, [r4, #0]	@ tmp289,* pArgs
	str	r2, [r3, #20]	@ tmp289, g_LowDelayCalcHandle
	b	.L21	@
.L42:
	cmp	r2, #0	@ pArgs,
	beq	.L147	@,
.L68:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, pArgs
	bl	VCTRL_ConfigFFFBSpeed	@
	b	.L135	@
.L26:
	cmp	r2, #0	@ pArgs,
	beq	.L148	@,
	ldr	r0, [r2, #0]	@ prephitmp.753,* pArgs
	cmp	r0, #33	@ prephitmp.753,
	bgt	.L149	@,
.L54:
	ldr	r1, [r4, #4]	@,
	mov	r2, #2	@,
	mov	r3, #0	@,
	bl	VCTRL_CreateChanWithOption	@
	cmp	r0, #0	@ ret.822,
	str	r0, [r4, #0]	@ ret.822,* pArgs
	blt	.L70	@,
	mov	r5, #0	@ ret,
	b	.L21	@
.L27:
	cmp	r2, #0	@ pArgs,
	beq	.L150	@,
.L55:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, pArgs
	bl	VCTRL_GetChanCfg	@
	b	.L135	@
.L28:
	cmp	r2, #0	@ pArgs,
	beq	.L151	@,
.L56:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r1, r4	@, pArgs
	mov	r0, r6	@, ChanID
	bl	VCTRL_ConfigChan	@
	cmp	r0, #0	@ ret
	moveq	r5, r0	@, ret, ret
	mvnne	r5, #0	@, ret,
	bl	VCTRL_EnableAllInt	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r0, r6	@, ChanID
	bl	VCTRL_LoadDspCode	@
	b	.L21	@
.L31:
	cmp	r2, #0	@ pArgs,
	beq	.L152	@,
.L59:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, pArgs
	bl	VCTRL_GetStreamSize	@
	mov	r5, r0	@ ret,
	b	.L136	@
.L41:
	cmp	r2, #0	@ pArgs,
	beq	.L153	@,
.L67:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	sub	r1, fp, #80	@,,
	mov	ip, #1	@ tmp266,
	mov	r3, #0	@ tmp267,
	str	ip, [fp, #-80]	@ tmp266, option.s32KeepBS
	str	r3, [fp, #-76]	@ tmp267, option.s32KeepSPSPPS
	bl	VCTRL_ResetChanWithOption	@
	cmp	r0, #0	@,
	bne	.L112	@,
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, pArgs
	bl	VCTRL_SeekPts	@
	subs	r5, r0, #0	@ ret,
	beq	.L136	@,
.L112:
	mvn	r5, #0	@ ret,
	b	.L136	@
.L39:
	cmp	r2, #0	@ pArgs,
	beq	.L154	@,
.L64:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, pArgs
	bl	VCTRL_SetDiscardPicParam	@
	mov	r5, r0	@ ret,
	b	.L136	@
.L35:
	cmp	r2, #0	@ pArgs,
	beq	.L155	@,
.L63:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, [r4, #0]	@,* pArgs
	bl	VCTRL_GetChanIDByMemAddr	@
	cmn	r0, #1	@ D.50520,
	str	r0, [r4, #0]	@ D.50520,* pArgs
	moveq	r5, r0	@, ret, D.50520
	movne	r5, #0	@, ret,
	bl	VCTRL_EnableAllInt	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L21	@
.L44:
	cmp	r2, #0	@ pArgs,
	beq	.L156	@,
.L71:
	ldr	r0, [r4, #0]	@ tmp277,* pArgs
	movw	r1, #:lower16:.LANCHOR1	@ tmp276,
	movt	r1, #:upper16:.LANCHOR1	@ tmp276,
	mov	r5, #0	@ ret,
	str	r0, [r1, r6, asl #2]	@ tmp277, g_FrameRate
	b	.L21	@
.L33:
	cmp	r2, #0	@ pArgs,
	beq	.L157	@,
.L61:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	ldmia	r4, {r0, r1}	@ phole ldm
	sub	r2, fp, #64	@,,
	mov	r3, #1	@,
	bl	VCTRL_GetChanMemSizeWithOption	@
	subs	r5, r0, #0	@ D.50500,
	bne	.L112	@,
	ldr	r3, [fp, #-60]	@ DetailMemSize.ScdDetailMem, DetailMemSize.ScdDetailMem
	ldr	r0, [fp, #-56]	@ DetailMemSize.ChanCtxDetailMem, DetailMemSize.ChanCtxDetailMem
	ldr	r1, [fp, #-64]	@ DetailMemSize.VdhDetailMem, DetailMemSize.VdhDetailMem
	str	r3, [r4, #4]	@ DetailMemSize.ScdDetailMem,
	str	r0, [r4, #8]	@ DetailMemSize.ChanCtxDetailMem,
	str	r1, [r4, #0]	@ DetailMemSize.VdhDetailMem,* pArgs
	b	.L136	@
.L29:
	cmp	r2, #0	@ pArgs,
	beq	.L158	@,
.L57:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, pArgs
	bl	VCTRL_SetStreamInterface	@
	b	.L135	@
.L38:
	cmp	r2, #0	@ pArgs,
	beq	.L159	@,
.L66:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, pArgs
	bl	VCTRL_PutUsrdecFrame	@
	b	.L135	@
.L43:
	cmp	r2, #0	@ pArgs,
	beq	.L160	@,
.L69:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, pArgs
	bl	VCTRL_ConfigPVRInfo	@
	b	.L135	@
.L32:
	cmp	r2, #0	@ pArgs,
	beq	.L161	@,
.L60:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, [r4, #0]	@,* pArgs
	sub	r1, fp, #40	@,,
	sub	r2, fp, #52	@,,
	bl	VCTRL_GetChanMemSize	@
	subs	r5, r0, #0	@ D.50487,
	bne	.L112	@,
	ldr	r2, [fp, #-40]	@ VdmMem, VdmMem
	ldr	lr, [fp, #-52]	@ ScdMem, ScdMem
	ldr	r1, [fp, #-44]	@ ScdMem, ScdMem
	ldr	r3, [fp, #-36]	@ VdmMem, VdmMem
	add	r0, lr, r2	@ tmp232, ScdMem, VdmMem
	ldr	ip, [fp, #-48]	@ ScdMem, ScdMem
	ldr	r2, [fp, #-32]	@ VdmMem, VdmMem
	add	lr, ip, r3	@ tmp235, ScdMem, VdmMem
	str	r0, [r4, #0]	@ tmp232, <variable>.MinMemSize
	add	r2, r1, r2	@ tmp238, ScdMem, VdmMem
	str	lr, [r4, #4]	@ tmp235, <variable>.NormalMemSize
	str	r2, [r4, #8]	@ tmp238, <variable>.FluentMemSize
	b	.L136	@
.L30:
	cmp	r2, #0	@ pArgs,
	beq	.L162	@,
.L58:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	str	r6, [r4, #0]	@ ChanID, <variable>.image_provider_inst_id
	movw	r1, #:lower16:VCTRL_GetChanImage	@ tmp221,
	movw	r3, #:lower16:VCTRL_ReleaseChanImage	@ tmp222,
	movt	r1, #:upper16:VCTRL_GetChanImage	@ tmp221,
	movt	r3, #:upper16:VCTRL_ReleaseChanImage	@ tmp222,
	str	r1, [r4, #4]	@ tmp221, <variable>.read_image
	mov	r5, #0	@ ret,
	str	r3, [r4, #8]	@ tmp222, <variable>.release_image
	bl	VCTRL_EnableAllInt	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L21	@
.L40:
	cmp	r2, #0	@ pArgs,
	bne	.L70	@,
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #711	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L34:
	cmp	r2, #0	@ pArgs,
	beq	.L163	@,
.L62:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	sub	r1, fp, #80	@,,
	bl	VCTRL_GetChanMemInfo	@
	subs	r5, r0, #0	@ ret,
	bne	.L164	@,
	ldr	lr, [fp, #-76]	@ D.50512, MemRec.VirAddr
	ldr	r2, [fp, #-72]	@ D.50511, MemRec.PhyAddr
	ldr	ip, [fp, #-68]	@ MemRec.Length, MemRec.Length
	cmp	lr, #0	@ D.50512,
	stmia	r4, {r2, lr}	@ phole stm
	str	ip, [r4, #8]	@ MemRec.Length, <variable>.Length
	beq	.L112	@,
	cmp	r2, #0	@ D.50511,
	mvneq	r5, #0	@ ret,
	b	.L136	@
.L36:
	cmp	r2, #0	@ pArgs,
	beq	.L165	@,
.L50:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	ldmia	r4, {r0, r1}	@ phole ldm
	mov	r5, #0	@ ret,
	bl	VCTRL_SetVdecExtra	@
	bl	VCTRL_EnableAllInt	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L21	@
.L23:
	cmp	r1, #58	@ eCmdID,
	ldrls	pc, [pc, r1, asl #2]	@ eCmdID
	b	.L70	@
.L87:
	.word	.L75
	.word	.L49
	.word	.L75
	.word	.L75
	.word	.L76
	.word	.L77
	.word	.L78
	.word	.L79
	.word	.L55
	.word	.L56
	.word	.L80
	.word	.L81
	.word	.L82
	.word	.L83
	.word	.L57
	.word	.L58
	.word	.L59
	.word	.L70
	.word	.L60
	.word	.L61
	.word	.L62
	.word	.L63
	.word	.L84
	.word	.L85
	.word	.L50
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L65
	.word	.L66
	.word	.L70
	.word	.L64
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L70
	.word	.L75
	.word	.L75
	.word	.L67
	.word	.L68
	.word	.L69
	.word	.L71
	.word	.L72
	.word	.L73
	.word	.L86
.L85:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, pArgs
	bl	VCTRL_ResetChanWithOption	@
	b	.L135	@
.L84:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	bl	VCTRL_ReleaseStream	@
	b	.L135	@
.L83:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	bl	VCTRL_ResetChan	@
	b	.L135	@
.L82:
	mov	r0, r6	@, ChanID
	bl	VCTRL_StopChanWithCheck	@
	subs	r5, r0, #0	@ ret,
	beq	.L21	@,
	b	.L70	@
.L81:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	bl	VCTRL_StartChan	@
	b	.L135	@
.L80:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, pArgs
	mov	r5, #0	@ ret,
	bl	VCTRL_GetChanState	@
	bl	VCTRL_EnableAllInt	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L21	@
.L86:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, pArgs
	bl	VCTRL_StartChanWithOption	@
	b	.L135	@
.L143:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #537	@,
	movt	r1, #:upper16:.LC5	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L149:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #553	@,
	movt	r1, #:upper16:.LC5	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L164:
	bl	VCTRL_EnableAllInt	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	mvn	r5, #0	@ ret,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L21	@
.L144:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	mov	r2, #740	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L141:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #506	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L147:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #695	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L142:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #529	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L152:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #618	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L155:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #649	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L159:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #681	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L148:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #545	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L163:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #641	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L154:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #658	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L162:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #611	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L146:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #725	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L153:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	mov	r2, #688	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L151:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	mov	r2, #576	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L160:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #702	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L145:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	mov	r2, #732	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L150:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	mov	r2, #568	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L140:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #673	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L165:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC4	@,
	mov	r2, #520	@,
	movt	r1, #:upper16:.LC4	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L156:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #718	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L158:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #603	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L157:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #633	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L161:
	mov	r0, r2	@, pArgs
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #626	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r5, #0	@ ret,
	b	.L21	@
.L118:
	mov	r0, r6	@, ChanID
	bl	VCTRL_GetCurChanFsSize	@
	cmp	r0, #0	@,
	beq	.L119	@,
	mov	r2, r6	@, ChanID
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC10	@,
	movt	r1, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	mov	r0, r6	@, ChanID
	mov	r1, #3	@,
	bl	VCTRL_SetChanFsPartitionState	@
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC11	@,
	movt	r1, #:upper16:.LC11	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L119	@
.L79:
	mov	r4, #500	@ s32Loop.794,
	b	.L88	@
.L166:
	cmp	r4, #0	@ s32Loop.794,
	sub	r4, r4, #1	@ s32Loop.794, s32Loop.794,
	beq	.L70	@,
	bl	msleep	@
	mov	r1, #2	@,
	mov	r0, r6	@, ChanID
	bl	VCTRT_SetChanCtrlState	@
	cmn	r0, #1	@,
	mov	r0, #1	@,
	bne	.L92	@,
	bl	msleep	@
	sub	r4, r4, #1	@ s32Loop.794, s32Loop.794,
.L88:
	mov	r1, #2	@,
	mov	r0, r6	@, ChanID
	bl	VCTRT_SetChanCtrlState	@
	cmn	r0, #1	@,
	mov	r0, #1	@,
	beq	.L166	@,
.L92:
	cmp	r4, #0	@ s32Loop.794,
	ble	.L70	@,
	mov	r0, r6	@, ChanID
	bl	VCTRL_DestroyChanWithOption	@
	subs	r5, r0, #0	@ ret,
	beq	.L21	@,
	b	.L70	@
.L76:
	ldr	r0, [r2, #0]	@ prephitmp.757,* pArgs
	b	.L52	@
.L78:
	mov	r4, #500	@ s32Loop,
	b	.L89	@
.L167:
	cmp	r4, #0	@ s32Loop,
	sub	r4, r4, #1	@ s32Loop, s32Loop,
	beq	.L70	@,
	bl	msleep	@
	mov	r1, #2	@,
	mov	r0, r6	@, ChanID
	bl	VCTRT_SetChanCtrlState	@
	cmn	r0, #1	@,
	mov	r0, #1	@,
	bne	.L90	@,
	bl	msleep	@
	sub	r4, r4, #1	@ s32Loop, s32Loop,
.L89:
	mov	r1, #2	@,
	mov	r0, r6	@, ChanID
	bl	VCTRT_SetChanCtrlState	@
	cmn	r0, #1	@,
	mov	r0, #1	@,
	beq	.L167	@,
.L90:
	cmp	r4, #0	@ s32Loop,
	ble	.L70	@,
	mov	r0, r6	@, ChanID
	bl	VCTRL_DestroyChan	@
	subs	r5, r0, #0	@ ret,
	beq	.L21	@,
	b	.L70	@
.L77:
	ldr	r0, [r2, #0]	@ prephitmp.753,* pArgs
	b	.L54	@
	.fnend
	.size	VDEC_Control, .-VDEC_Control
	.align	2
	.global	VDEC_Exit
	.type	VDEC_Exit, %function
VDEC_Exit:
	.fnstart
.LFB1540:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp137,
	movt	r4, #:upper16:.LANCHOR0	@ tmp137,
	bl	OSAL_DOWN_INTERRUPTIBLE	@
	ldr	r0, [r4, #84]	@ g_VfmwInitCount, g_VfmwInitCount
	sub	r3, r0, #1	@ g_VfmwInitCount.460, g_VfmwInitCount,
	str	r3, [r4, #84]	@ g_VfmwInitCount.460, g_VfmwInitCount
	cmp	r3, #0	@ g_VfmwInitCount.460,
	ble	.L169	@,
	bl	OSAL_UP	@
	mov	r0, #0	@ D.50230,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L169:
	bl	VCTRL_CloseVfmw	@
	mov	r5, r0	@ ret,
	bl	MEM_ManagerClearOperation	@
	mov	r1, #0	@ tmp141,
	str	r1, [r4, #0]	@ tmp141, g_VfmwEnableFlag
	bl	OSAL_UP	@
	cmp	r5, #0	@ ret,
	moveq	r0, r5	@, D.50230, ret
	mvnne	r0, #0	@, D.50230,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	VDEC_Exit, .-VDEC_Exit
	.align	2
	.global	VDEC_SpinLockInit
	.type	VDEC_SpinLockInit, %function
VDEC_SpinLockInit:
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
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQInit	@
	movw	r0, #:lower16:g_RecordLock	@,
	movt	r0, #:upper16:g_RecordLock	@,
	bl	OSAL_SpinLockIRQInit	@
	movw	r0, #:lower16:g_SpinLock	@,
	movt	r0, #:upper16:g_SpinLock	@,
	bl	OSAL_SpinLockIRQInit	@
	movw	r0, #:lower16:g_SpinLock_fsp	@,
	movt	r0, #:upper16:g_SpinLock_fsp	@,
	bl	OSAL_SpinLockIRQInit	@
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	OSAL_SpinLockIRQInit	@
	movw	r0, #:lower16:g_ActivateLock	@,
	movt	r0, #:upper16:g_ActivateLock	@,
	bl	OSAL_SpinLockIRQInit	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDEC_SpinLockInit, .-VDEC_SpinLockInit
	.align	2
	.global	VDEC_InitWithOperation
	.type	VDEC_InitWithOperation, %function
VDEC_InitWithOperation:
	.fnstart
.LFB1539:
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
	mov	r5, r0	@ pArgs, pArgs
	bl	OSAL_DOWN_INTERRUPTIBLE	@
	cmp	r5, #0	@ pArgs,
	beq	.L186	@,
	movw	r4, #:lower16:.LANCHOR0	@ tmp225,
	movt	r4, #:upper16:.LANCHOR0	@ tmp225,
	ldr	r3, [r4, #0]	@ g_VfmwEnableFlag, g_VfmwEnableFlag
	cmp	r3, #1	@ g_VfmwEnableFlag,
	beq	.L187	@,
	mov	r1, #12	@,
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	movw	r6, #:lower16:VDM_OpenHardware	@ tmp159,
	bl	__memzero	@
	mov	r1, #12	@,
	movw	r0, #:lower16:g_RecordLock	@,
	movt	r0, #:upper16:g_RecordLock	@,
	bl	__memzero	@
	mov	r1, #12	@,
	movw	r0, #:lower16:g_SpinLock	@,
	movt	r0, #:upper16:g_SpinLock	@,
	bl	__memzero	@
	mov	r1, #12	@,
	movw	r0, #:lower16:g_SpinLock_fsp	@,
	movt	r0, #:upper16:g_SpinLock_fsp	@,
	bl	__memzero	@
	mov	r1, #12	@,
	movw	r0, #:lower16:g_SpinLockIrq_Destroy	@,
	movt	r0, #:upper16:g_SpinLockIrq_Destroy	@,
	bl	__memzero	@
	mov	r1, #12	@,
	movw	r0, #:lower16:g_ActivateLock	@,
	movt	r0, #:upper16:g_ActivateLock	@,
	bl	__memzero	@
	movw	r1, #:lower16:AcceleratorCharacter	@ tmp154,
	movw	r3, #:lower16:.LANCHOR1	@ tmp156,
	movt	r1, #:upper16:AcceleratorCharacter	@ tmp154,
	movt	r3, #:upper16:.LANCHOR1	@ tmp156,
	mov	r0, #0	@ tmp155,
	mov	ip, #10	@ tmp157,
	str	r0, [r1, #0]	@ tmp155, AcceleratorCharacter
	str	ip, [r3, #64]	@ tmp157, g_chipID
	movt	r6, #:upper16:VDM_OpenHardware	@ tmp159,
	movw	r2, #:lower16:VDM_CloseHardware	@ tmp161,
	str	r6, [r4, #88]	@ tmp159, g_vdm_hal_fun_ptr.pfun_VDMDRV_OpenHardware
	movt	r2, #:upper16:VDM_CloseHardware	@ tmp161,
	movw	r1, #:lower16:SCD_OpenHardware	@ tmp163,
	str	r2, [r4, #92]	@ tmp161, g_vdm_hal_fun_ptr.pfun_VDMDRV_CloseHardware
	movt	r1, #:upper16:SCD_OpenHardware	@ tmp163,
	movw	r0, #:lower16:SCD_CloseHardware	@ tmp165,
	str	r1, [r4, #96]	@ tmp163, g_vdm_hal_fun_ptr.pfun_SCDDRV_OpenHardware
	movt	r0, #:upper16:SCD_CloseHardware	@ tmp165,
	movw	r3, #:lower16:BPD_OpenHardware	@ tmp167,
	str	r0, [r4, #100]	@ tmp165, g_vdm_hal_fun_ptr.pfun_SCDDRV_CloseHardware
	movt	r3, #:upper16:BPD_OpenHardware	@ tmp167,
	movw	ip, #:lower16:VDMHAL_V300R001_GetHalMemSize	@ tmp169,
	str	r3, [r4, #104]	@ tmp167, g_vdm_hal_fun_ptr.pfun_BPDDRV_OpenHardware
	movt	ip, #:upper16:VDMHAL_V300R001_GetHalMemSize	@ tmp169,
	movw	r6, #:lower16:VDMHAL_V300R001_OpenHAL	@ tmp171,
	str	ip, [r4, #112]	@ tmp169, g_vdm_hal_fun_ptr.pfun_VDMHAL_GetHalMemSize
	movt	r6, #:upper16:VDMHAL_V300R001_OpenHAL	@ tmp171,
	movw	r2, #:lower16:VDMHAL_V300R001_CloseHAL	@ tmp173,
	str	r6, [r4, #116]	@ tmp171, g_vdm_hal_fun_ptr.pfun_VDMHAL_OpenHAL
	movt	r2, #:upper16:VDMHAL_V300R001_CloseHAL	@ tmp173,
	movw	r1, #:lower16:VDMHAL_V300R001_ArrangeMem	@ tmp175,
	str	r2, [r4, #120]	@ tmp173, g_vdm_hal_fun_ptr.pfun_VDMHAL_CloseHAL
	movt	r1, #:upper16:VDMHAL_V300R001_ArrangeMem	@ tmp175,
	movw	r0, #:lower16:VDMHAL_V300R001_ArrangeMem_BTL	@ tmp177,
	str	r1, [r4, #124]	@ tmp175, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem
	movt	r0, #:upper16:VDMHAL_V300R001_ArrangeMem_BTL	@ tmp177,
	movw	r3, #:lower16:VDMHAL_V300R001_ResetVdm	@ tmp179,
	str	r0, [r4, #128]	@ tmp177, g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem_BTL
	movt	r3, #:upper16:VDMHAL_V300R001_ResetVdm	@ tmp179,
	movw	ip, #:lower16:VDMHAL_V300R001_GlbReset	@ tmp181,
	str	r3, [r4, #132]	@ tmp179, g_vdm_hal_fun_ptr.pfun_VDMHAL_ResetVdm
	movt	ip, #:upper16:VDMHAL_V300R001_GlbReset	@ tmp181,
	movw	r6, #:lower16:VDMHAL_V300R001_ClearIntState	@ tmp183,
	str	ip, [r4, #136]	@ tmp181, g_vdm_hal_fun_ptr.pfun_VDMHAL_GlbReset
	movt	r6, #:upper16:VDMHAL_V300R001_ClearIntState	@ tmp183,
	movw	r2, #:lower16:VDMHAL_V300R001_MaskInt	@ tmp185,
	str	r6, [r4, #140]	@ tmp183, g_vdm_hal_fun_ptr.pfun_VDMHAL_ClearIntState
	movt	r2, #:upper16:VDMHAL_V300R001_MaskInt	@ tmp185,
	movw	r1, #:lower16:VDMHAL_V300R001_EnableInt	@ tmp187,
	str	r2, [r4, #144]	@ tmp185, g_vdm_hal_fun_ptr.pfun_VDMHAL_MaskInt
	movt	r1, #:upper16:VDMHAL_V300R001_EnableInt	@ tmp187,
	movw	r0, #:lower16:VDMHAL_V300R001_CheckReg	@ tmp189,
	str	r1, [r4, #148]	@ tmp187, g_vdm_hal_fun_ptr.pfun_VDMHAL_EnableInt
	movt	r0, #:upper16:VDMHAL_V300R001_CheckReg	@ tmp189,
	movw	r3, #:lower16:VDMHAL_V300R001_StartHwRepair	@ tmp191,
	str	r0, [r4, #152]	@ tmp189, g_vdm_hal_fun_ptr.pfun_VDMHAL_CheckReg
	movt	r3, #:upper16:VDMHAL_V300R001_StartHwRepair	@ tmp191,
	movw	ip, #:lower16:VDMHAL_V300R001_StartHwDecode	@ tmp193,
	str	r3, [r4, #156]	@ tmp191, g_vdm_hal_fun_ptr.pfun_VDMHAL_StartHwRepair
	movt	ip, #:upper16:VDMHAL_V300R001_StartHwDecode	@ tmp193,
	movw	r6, #:lower16:VDMHAL_V300R001_PrepareDec	@ tmp195,
	str	ip, [r4, #160]	@ tmp193, g_vdm_hal_fun_ptr.pfun_VDMHAL_StartHwDecode
	movt	r6, #:upper16:VDMHAL_V300R001_PrepareDec	@ tmp195,
	movw	r2, #:lower16:VDMHAL_V300R001_IsVdmReady	@ tmp197,
	str	r6, [r4, #164]	@ tmp195, g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareDec
	movt	r2, #:upper16:VDMHAL_V300R001_IsVdmReady	@ tmp197,
	movw	r1, #:lower16:VDMHAL_V300R001_IsVdmRun	@ tmp199,
	str	r2, [r4, #168]	@ tmp197, g_vdm_hal_fun_ptr.pfun_VDMHAL_IsVdmReady
	movt	r1, #:upper16:VDMHAL_V300R001_IsVdmRun	@ tmp199,
	movw	r0, #:lower16:VDMHAL_V300R001_PrepareRepair	@ tmp201,
	str	r1, [r4, #172]	@ tmp199, g_vdm_hal_fun_ptr.pfun_VDMHAL_IsVdmRun
	movt	r0, #:upper16:VDMHAL_V300R001_PrepareRepair	@ tmp201,
	movw	r3, #:lower16:VDMHAL_V300R001_MakeDecReport	@ tmp203,
	str	r0, [r4, #176]	@ tmp201, g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareRepair
	movt	r3, #:upper16:VDMHAL_V300R001_MakeDecReport	@ tmp203,
	movw	ip, #:lower16:VDMHAL_V300R001_BackupInfo	@ tmp205,
	str	r3, [r4, #180]	@ tmp203, g_vdm_hal_fun_ptr.pfun_VDMHAL_MakeDecReport
	movt	ip, #:upper16:VDMHAL_V300R001_BackupInfo	@ tmp205,
	movw	r6, #:lower16:VDMHAL_V300R001_GetCharacter	@ tmp207,
	str	ip, [r4, #184]	@ tmp205, g_vdm_hal_fun_ptr.pfun_VDMHAL_BackupInfo
	movt	r6, #:upper16:VDMHAL_V300R001_GetCharacter	@ tmp207,
	movw	r2, #:lower16:VDMHAL_V300R001_WriteBigTitle1DYuv	@ tmp209,
	str	r6, [r4, #108]	@ tmp207, g_vdm_hal_fun_ptr.pfun_VDMHAL_GetCharacter
	movt	r2, #:upper16:VDMHAL_V300R001_WriteBigTitle1DYuv	@ tmp209,
	str	r2, [r4, #188]	@ tmp209, g_vdm_hal_fun_ptr.pfun_VDMHAL_Write1DYuv
	bl	VDEC_SpinLockInit	@
	ldr	r3, [r4, #108]	@ D.50201, g_vdm_hal_fun_ptr.pfun_VDMHAL_GetCharacter
	cmp	r3, #0	@ D.50201,
	beq	.L179	@,
	blx	r3	@ D.50201
.L179:
	mov	r0, r5	@, pArgs
	bl	MEM_ManagerWithOperation	@
	bl	VCTRL_OpenVfmw	@
	movw	r1, #:lower16:.LC13	@,
	movt	r1, #:upper16:.LC13	@,
	mov	r6, r0	@ ret,
	mov	r0, #2	@,
	mov	r2, r6	@, ret
	bl	dprint_vfmw	@
	cmp	r6, #0	@ ret,
	ldr	r0, [r4, #136]	@ D.50210, g_vdm_hal_fun_ptr.pfun_VDMHAL_GlbReset
	moveq	r3, #1	@ tmp213,
	movne	r3, #0	@ tmp217,
	cmp	r0, #0	@ D.50210,
	str	r3, [r4, #84]	@ tmp217, g_VfmwInitCount
	str	r3, [r4, #0]	@ tmp217, g_VfmwEnableFlag
	beq	.L182	@,
	blx	r0	@ D.50210
.L183:
	ldmia	r5, {r0, r1}	@ phole ldm
	bl	VCTRL_SetCallBack	@
	bl	OSAL_UP	@
	cmp	r6, #0	@ ret,
	moveq	r0, r6	@, D.50162, ret
	mvnne	r0, #0	@, D.50162,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L187:
	ldr	r1, [r4, #84]	@ g_VfmwInitCount, g_VfmwInitCount
	add	r0, r1, #1	@ tmp145, g_VfmwInitCount,
	str	r0, [r4, #84]	@ tmp145, g_VfmwInitCount
	ldmia	r5, {r0, r1}	@ phole ldm
	bl	VCTRL_SetCallBack	@
	bl	OSAL_UP	@
	mov	r0, #0	@ D.50162,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L182:
	movw	r1, #:lower16:.LC14	@,
	movw	r2, #441	@,
	movt	r1, #:upper16:.LC14	@,
	bl	dprint_vfmw	@
	b	.L183	@
.L186:
	bl	OSAL_UP	@
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC12	@,
	movt	r1, #:upper16:.LC12	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50162,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDEC_InitWithOperation, .-VDEC_InitWithOperation
	.align	2
	.global	VDEC_Init
	.type	VDEC_Init, %function
VDEC_Init:
	.fnstart
.LFB1538:
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
	sub	r4, fp, #36	@ tmp137,,
	mov	r5, r0	@ VdecCallback, VdecCallback
	mov	r1, #16	@,
	mov	r0, r4	@, tmp137
	bl	__memzero	@
	mov	r0, r4	@, tmp137
	mov	r3, #0	@ tmp138,
	str	r5, [fp, #-32]	@ VdecCallback, Args.VdecCallback
	str	r3, [fp, #-24]	@ tmp138, Args.mem_free
	str	r3, [fp, #-28]	@ tmp138, Args.mem_malloc
	bl	VDEC_InitWithOperation	@
	cmp	r0, #0	@ ret
	mvnne	r0, #0	@,,
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
	.fnend
	.size	VDEC_Init, .-VDEC_Init
	.align	2
	.global	VDEC_ExitModule
	.type	VDEC_ExitModule, %function
VDEC_ExitModule:
	.fnstart
.LFB1530:
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
	bl	vfmw_proc_exit	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDEC_ExitModule, .-VDEC_ExitModule
	.align	2
	.global	VDEC_OpenModule
	.type	VDEC_OpenModule, %function
VDEC_OpenModule:
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
	bl	OSAL_SEMA_INTIT	@
	bl	vfmw_proc_init	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDEC_OpenModule, .-VDEC_OpenModule
	.align	2
	.global	VDEC_Lowdelay_Event_Time
	.type	VDEC_Lowdelay_Event_Time, %function
VDEC_Lowdelay_Event_Time:
	.fnstart
.LFB1528:
	@ args = 0, pretend = 0, frame = 24
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
	sub	r5, fp, #28	@ tmp139,,
	mov	r4, r0	@ ChanId, ChanId
	mov	r6, #0	@ tmp138,
	str	r6, [r5, #-4]!	@ tmp138, TmpTime
	mov	r0, r5	@, tmp139
	mov	r6, r2	@ u32FrameId, u32FrameId
	mov	r5, r1	@ eventId, eventId
	bl	HI_DRV_SYS_GetTimeStampMs	@
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	add	r0, r4, r3	@ tmp147, ChanId, tmp140
	add	r4, r3, r4, asl #2	@, tmp143, tmp140, ChanId,
	ldr	r3, [fp, #-32]	@ TmpTime.442, TmpTime
	ldrb	r2, [r0, #4]	@ zero_extendqisi2	@ tmp149, g_LowDelayCalcStat
	ldr	r1, [r4, #20]	@ D.50053, g_LowDelayCalcHandle
	cmp	r2, #1	@ tmp149,
	beq	.L199	@,
.L198:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L199:
	sub	r0, fp, #48	@,,
	str	r5, [fp, #-48]	@ eventId, evt.evt_id
	str	r6, [fp, #-40]	@ u32FrameId, evt.frame
	str	r1, [fp, #-44]	@ D.50053, evt.handle
	str	r3, [fp, #-36]	@ TmpTime.442, evt.time
	bl	HI_DRV_LD_Notify_Event	@
	b	.L198	@
	.fnend
	.size	VDEC_Lowdelay_Event_Time, .-VDEC_Lowdelay_Event_Time
	.global	g_VfmwEnableFlag
	.global	g_VfmwInitCount
	.global	g_chipID
	.global	g_ChipMaxWidth
	.global	g_ChipMaxHeight
	.global	g_vdm_hal_fun_ptr
	.global	g_FrameRate
	.global	g_LastFrameRate
	.global	g_LowDelayCalcStat
	.global	g_LowDelayCalcHandle
	.global	g_LowDelaySeqIndex
	.section	___ksymtab+VDEC_Resume,"a",%progbits
	.align	2
	.type	__ksymtab_VDEC_Resume, %object
	.size	__ksymtab_VDEC_Resume, 8
__ksymtab_VDEC_Resume:
@ value:
	.word	VDEC_Resume
@ name:
	.word	__kstrtab_VDEC_Resume
	.section	___ksymtab+VDM_ResetClock,"a",%progbits
	.align	2
	.type	__ksymtab_VDM_ResetClock, %object
	.size	__ksymtab_VDM_ResetClock, 8
__ksymtab_VDM_ResetClock:
@ value:
	.word	VDM_ResetClock
@ name:
	.word	__kstrtab_VDM_ResetClock
	.section	___ksymtab+VDEC_InitWithOperation,"a",%progbits
	.align	2
	.type	__ksymtab_VDEC_InitWithOperation, %object
	.size	__ksymtab_VDEC_InitWithOperation, 8
__ksymtab_VDEC_InitWithOperation:
@ value:
	.word	VDEC_InitWithOperation
@ name:
	.word	__kstrtab_VDEC_InitWithOperation
	.section	___ksymtab+VDEC_Control,"a",%progbits
	.align	2
	.type	__ksymtab_VDEC_Control, %object
	.size	__ksymtab_VDEC_Control, 8
__ksymtab_VDEC_Control:
@ value:
	.word	VDEC_Control
@ name:
	.word	__kstrtab_VDEC_Control
	.section	___ksymtab+VDEC_Exit,"a",%progbits
	.align	2
	.type	__ksymtab_VDEC_Exit, %object
	.size	__ksymtab_VDEC_Exit, 8
__ksymtab_VDEC_Exit:
@ value:
	.word	VDEC_Exit
@ name:
	.word	__kstrtab_VDEC_Exit
	.section	___ksymtab+VDEC_Init,"a",%progbits
	.align	2
	.type	__ksymtab_VDEC_Init, %object
	.size	__ksymtab_VDEC_Init, 8
__ksymtab_VDEC_Init:
@ value:
	.word	VDEC_Init
@ name:
	.word	__kstrtab_VDEC_Init
	.section	__ksymtab_strings,"a",%progbits
	.type	__kstrtab_VDM_ResetClock, %object
	.size	__kstrtab_VDM_ResetClock, 15
__kstrtab_VDM_ResetClock:
	.ascii	"VDM_ResetClock\000"
	.type	__kstrtab_VDEC_Resume, %object
	.size	__kstrtab_VDEC_Resume, 12
__kstrtab_VDEC_Resume:
	.ascii	"VDEC_Resume\000"
	.type	__kstrtab_VDEC_Suspend, %object
	.size	__kstrtab_VDEC_Suspend, 13
__kstrtab_VDEC_Suspend:
	.ascii	"VDEC_Suspend\000"
	.type	__kstrtab_VDEC_InitWithOperation, %object
	.size	__kstrtab_VDEC_InitWithOperation, 23
__kstrtab_VDEC_InitWithOperation:
	.ascii	"VDEC_InitWithOperation\000"
	.type	__kstrtab_VDEC_Control, %object
	.size	__kstrtab_VDEC_Control, 13
__kstrtab_VDEC_Control:
	.ascii	"VDEC_Control\000"
	.type	__kstrtab_VDEC_Exit, %object
	.size	__kstrtab_VDEC_Exit, 10
__kstrtab_VDEC_Exit:
	.ascii	"VDEC_Exit\000"
	.type	__kstrtab_VDEC_Init, %object
	.size	__kstrtab_VDEC_Init, 10
__kstrtab_VDEC_Init:
	.ascii	"VDEC_Init\000"
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	g_FrameRate, %object
	.size	g_FrameRate, 64
g_FrameRate:
	.word	30
	.space	60
	.type	g_chipID, %object
	.size	g_chipID, 4
g_chipID:
	.word	4
	.type	g_ChipMaxWidth, %object
	.size	g_ChipMaxWidth, 4
g_ChipMaxWidth:
	.word	8192
	.type	g_ChipMaxHeight, %object
	.size	g_ChipMaxHeight, 4
g_ChipMaxHeight:
	.word	8192
	.type	g_LastFrameRate, %object
	.size	g_LastFrameRate, 64
g_LastFrameRate:
	.word	30
	.space	60
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"VDEC_Resume ok !\012\000"
	.space	2
.LC1:
	.ascii	"VDEC_Suspend ok !\012\000"
	.space	1
.LC2:
	.ascii	"VFMW has been destroyed, so any operation is unusef"
	.ascii	"ul!\012\000"
.LC3:
	.ascii	"vfmw.c,L%d: pArgs is NULL!\012\000"
.LC4:
	.ascii	"vfmw.c, L%d: pArgs is NULL!\012\000"
	.space	3
.LC5:
	.ascii	"vfmw.c,L%d: capability level out of range\012\000"
	.space	1
.LC6:
	.ascii	"VCTRL_CreateChan() return %d\012\000"
	.space	2
.LC7:
	.ascii	"DFS, rls chan %d frame store fail!\012\000"
.LC8:
	.ascii	"DFS, rls chan %d frame store success!\012\000"
	.space	1
.LC9:
	.ascii	"DFS, set decoding thread state to success!\012 \000"
	.space	3
.LC10:
	.ascii	"DFS, request frame store fail!, chanid: %d\012\000"
.LC11:
	.ascii	"DFS, set decoding thread state to fail\012\000"
.LC12:
	.ascii	"VDEC_InitWithOperation has NULL parameter, error!\012"
	.ascii	"\000"
	.space	1
.LC13:
	.ascii	"VCTRL_OpenVfmw() return %d\012\000"
.LC14:
	.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000"
	.section	___ksymtab+VDEC_Suspend,"a",%progbits
	.align	2
	.type	__ksymtab_VDEC_Suspend, %object
	.size	__ksymtab_VDEC_Suspend, 8
__ksymtab_VDEC_Suspend:
@ value:
	.word	VDEC_Suspend
@ name:
	.word	__kstrtab_VDEC_Suspend
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_VfmwEnableFlag, %object
	.size	g_VfmwEnableFlag, 4
g_VfmwEnableFlag:
	.space	4
	.type	g_LowDelayCalcStat, %object
	.size	g_LowDelayCalcStat, 16
g_LowDelayCalcStat:
	.space	16
	.type	g_LowDelayCalcHandle, %object
	.size	g_LowDelayCalcHandle, 64
g_LowDelayCalcHandle:
	.space	64
	.type	g_VfmwInitCount, %object
	.size	g_VfmwInitCount, 4
g_VfmwInitCount:
	.space	4
	.type	g_vdm_hal_fun_ptr, %object
	.size	g_vdm_hal_fun_ptr, 108
g_vdm_hal_fun_ptr:
	.space	108
	.type	g_LowDelaySeqIndex, %object
	.size	g_LowDelaySeqIndex, 64
g_LowDelaySeqIndex:
	.space	64
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
