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
	.file	"vdm_hal.c"
@ GNU C (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) version 4.4.1 (arm-hisiv200-linux-gnueabi)
@	compiled by GNU C version 4.1.1 20061011 (Red Hat 4.1.1-30), GMP version 4.3.1, MPFR version 2.4.2.
@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
@ options passed:  -nostdinc
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include
@ -Iarch/arm/include/generated
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include
@ -Iinclude
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/uapi
@ -Iarch/arm/include/generated/uapi
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/uapi
@ -Iinclude/generated/uapi
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0
@ -Idrivers/msp/vfmw/vfmw_v4.0
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/mach-hi3798mx/include
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/include
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/drv/include
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/scene/stb
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/common
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/osal/linux_kernel
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/common/softlib
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/common/syntax
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/driver/HiSCDV200
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/product/Hi3798MV100
@ -I/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/vfmw/vfmw_v4.0/firmware/common_test/vdecko
@ -imultilib armv7a_soft -iprefix
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/
@ -isysroot /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../target
@ -D__KERNEL__ -D__LINUX_ARM_ARCH__=7 -Uarm -DCHIP_TYPE_hi3796mv100
@ -DSDK_VERSION=HiSTBAndroidV600R001C00SPC065_v2016112920 -DHI_MCE_SUPPORT
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
@ -DKBUILD_BASENAME=KBUILD_STR(vdm_hal)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/.vdm_hal.o.d
@ /home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal.o -O2
@ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs
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
	.global	VDMHAL_V300R001_GetHalMemSize
	.type	VDMHAL_V300R001_GetHalMemSize, %function
VDMHAL_V300R001_GetHalMemSize:
	.fnstart
.LFB1528:
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
	movw	r0, #:lower16:4296704	@,
	movt	r0, #:upper16:4296704	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMHAL_V300R001_GetHalMemSize, .-VDMHAL_V300R001_GetHalMemSize
	.align	2
	.global	VDMHAL_V300R001_GetCharacter
	.type	VDMHAL_V300R001_GetCharacter, %function
VDMHAL_V300R001_GetCharacter:
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
	movw	r0, #:lower16:g_VdmCharacter	@ tmp133,
	movw	r3, #:lower16:g_eVdmVersion	@ tmp135,
	movt	r0, #:upper16:g_VdmCharacter	@ tmp133,
	movt	r3, #:upper16:g_eVdmVersion	@ tmp135,
	mov	r1, #15	@ tmp134,
	mov	r2, #4	@ tmp136,
	str	r1, [r0, #0]	@ tmp134, g_VdmCharacter
	str	r2, [r3, #0]	@ tmp136, g_eVdmVersion
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMHAL_V300R001_GetCharacter, .-VDMHAL_V300R001_GetCharacter
	.align	2
	.global	VDMHAL_V300R001_IsVdmRun
	.type	VDMHAL_V300R001_IsVdmRun, %function
VDMHAL_V300R001_IsVdmRun:
	.fnstart
.LFB1543:
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
	movw	r1, #1208	@ tmp141,
	mul	r3, r1, r0	@ tmp140, tmp141, VdhId
	movw	r2, #:lower16:g_HwMem	@ tmp139,
	movt	r2, #:upper16:g_HwMem	@ tmp139,
	ldr	r4, [r3, r2]	@ D.52687, <variable>.pVdmRegVirAddr
	cmp	r4, #0	@ D.52687,
	beq	.L11	@,
	cmp	r0, #0	@ VdhId,
	ble	.L12	@,
	mov	r3, r0	@, VdhId
	mov	r4, #1	@ tmp148,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	str	r4, [sp, #0]	@ tmp148,
	bl	dprint_vfmw	@
	mov	r0, r4	@ D.52691, tmp148
.L7:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L12:
	ldr	r0, [r4, #40]	@ Data32,
	subs	r0, r0, #1	@ D.52691, Data32,
	movne	r0, #1	@ D.52691
	b	.L7	@
.L11:
	mov	r0, r4	@, D.52687
	movw	r1, #:lower16:.LC0	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ D.52691, D.52687
	b	.L7	@
	.fnend
	.size	VDMHAL_V300R001_IsVdmRun, .-VDMHAL_V300R001_IsVdmRun
	.align	2
	.global	VDMHAL_V300R001_IsVdmReady
	.type	VDMHAL_V300R001_IsVdmReady, %function
VDMHAL_V300R001_IsVdmReady:
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
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r1, #1208	@ tmp142,
	mul	r3, r1, r0	@ tmp141, tmp142, VdhId
	movw	r2, #:lower16:g_HwMem	@ tmp140,
	movt	r2, #:upper16:g_HwMem	@ tmp140,
	ldr	r3, [r3, r2]	@ D.52668, <variable>.pVdmRegVirAddr
	cmp	r3, #0	@ D.52668,
	beq	.L18	@,
	cmp	r0, #0	@ VdhId,
	ble	.L19	@,
	mov	r3, r0	@, VdhId
	movw	r1, #:lower16:.LC1	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC1	@,
	ldr	r2, .L20	@,
	mov	ip, #1	@ tmp151,
	str	ip, [sp, #0]	@ tmp151,
	bl	dprint_vfmw	@
	mov	r0, #0	@ Data32,
.L15:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L19:
	ldr	r0, [r3, #28]	@ Data32.650,
	ubfx	r0, r0, #17, #1	@ Data32, Data32.650,,
	b	.L15	@
.L18:
	mov	r0, r3	@, D.52668
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L20	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC3	@,
	movt	r3, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Data32,
	b	.L15	@
.L21:
	.align	2
.L20:
	.word	.LANCHOR0+28
	.fnend
	.size	VDMHAL_V300R001_IsVdmReady, .-VDMHAL_V300R001_IsVdmReady
	.align	2
	.global	VDMHAL_V300R001_WriteMsgSlot
	.type	VDMHAL_V300R001_WriteMsgSlot, %function
VDMHAL_V300R001_WriteMsgSlot:
	.fnstart
.LFB1546:
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
	cmp	r0, #0	@ pDst,
	cmpne	r1, #0	@, pSrc,
	beq	.L23	@,
	rsbs	r4, r2, #1	@ tmp148, dnmsg_size
	movcc	r4, #0	@ tmp148
	cmp	r2, #256	@ dnmsg_size,
	orrhi	r4, r4, #1	@,, tmp151, tmp148
	cmp	r4, #0	@ tmp151,
	bne	.L23	@,
	mov	r2, r2, asl #2	@, dnmsg_size,
	bl	memcpy	@
	mov	r0, r4	@ D.52918, tmp151
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L23:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC4	@,
	movt	r1, #:upper16:.LC4	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52918,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	VDMHAL_V300R001_WriteMsgSlot, .-VDMHAL_V300R001_WriteMsgSlot
	.align	2
	.global	VDMHAL_V300R001_ReadMsgSlot
	.type	VDMHAL_V300R001_ReadMsgSlot, %function
VDMHAL_V300R001_ReadMsgSlot:
	.fnstart
.LFB1545:
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
	cmp	r0, #0	@ pDst,
	cmpne	r1, #0	@, pSrc,
	mov	r3, r1	@ pSrc, pSrc
	movne	r4, #0	@, tmp144
	moveq	r4, #1	@, tmp144
	beq	.L32	@,
	cmp	r2, #800	@ upmsg_size,
	bhi	.L33	@,
	mov	r2, r2, asl #2	@, upmsg_size,
	bl	memcpy	@
	mov	r0, r4	@ D.52898, tmp144
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L33:
	mov	r0, r4	@, tmp144
	movw	r1, #:lower16:.LC6	@,
	movt	r1, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52898,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L32:
	mov	r2, r0	@, pDst
	movw	r1, #:lower16:.LC5	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC5	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52898,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	VDMHAL_V300R001_ReadMsgSlot, .-VDMHAL_V300R001_ReadMsgSlot
	.align	2
	.global	VDMHAL_V300R001_WriteBigTitle1DYuv
	.type	VDMHAL_V300R001_WriteBigTitle1DYuv, %function
VDMHAL_V300R001_WriteBigTitle1DYuv:
	.fnstart
.LFB1555:
	@ args = 4, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #92
	sub	sp, sp, #92	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	ubfx	r8, r3, #29, #2	@ PicStructure.837, Height,,
	cmp	r8, #1	@ PicStructure.837,
	mov	r6, r3	@ Height, Height
	str	r0, [fp, #-100]	@ fpYuv, %sfp
	mov	r4, r1	@ Yaddress, Yaddress
	mov	r7, r2	@ Width, Width
	moveq	r8, #0	@ PicStructure,
	beq	.L36	@,
	cmp	r8, #2	@ PicStructure.837,
	moveq	r8, #1	@ PicStructure,
	movne	r8, #2	@ PicStructure,
.L36:
	ldr	r1, [fp, #-100]	@, %sfp
	cmp	r1, #0	@,
	beq	.L72	@,
	sub	r3, fp, #60	@ tmp242,,
	sub	r2, fp, #76	@,,
	add	lr, r3, #4	@ tmp400, tmp242,
	add	r5, r2, #4	@ tmp397,,
	mov	ip, #0	@ tmp238,
	movw	r0, #:lower16:.LC7	@,
	str	ip, [r5], #4	@ tmp238, MemRecord_ul
	mov	r1, ip	@, tmp238
	str	ip, [lr], #4	@ tmp238, MemRecord_y
	movt	r0, #:upper16:.LC7	@,
	str	ip, [r5], #4	@ tmp238, MemRecord_ul
	mov	r2, #4194304	@,
	str	ip, [lr], #4	@ tmp238, MemRecord_y
	str	ip, [r5, #0]	@ tmp238, MemRecord_ul
	str	ip, [lr, #0]	@ tmp238, MemRecord_y
	str	ip, [fp, #-76]	@ tmp238, MemRecord_ul
	str	ip, [fp, #-60]	@ tmp238, MemRecord_y
	str	ip, [sp, #0]	@ tmp238,
	bl	MEM_AllocMemBlock	@
	subs	ip, r0, #0	@ D.53666,
	bne	.L133	@,
	mov	r1, ip	@, D.53666
	movw	r0, #:lower16:.LC9	@,
	mov	r2, #4194304	@,
	movt	r0, #:upper16:.LC9	@,
	sub	r3, fp, #76	@,,
	str	ip, [sp, #0]	@ D.53666,
	bl	MEM_AllocMemBlock	@
	cmp	r0, #0	@,
	bne	.L133	@,
	add	r5, r7, #15	@ tmp255, Width,
	add	lr, r6, #15	@ tmp257, Height,
	bic	r5, r5, #15	@ ImgWidthInPixAln, tmp255,
	bic	r1, lr, #15	@, tmp257,
	add	ip, r5, #255	@ tmp259, ImgWidthInPixAln,
	str	r1, [fp, #-88]	@, %sfp
	bic	r3, ip, #255	@ tmp260, tmp259,
	ldr	r0, [fp, #-56]	@, MemRecord_y.VirAddr
	ldr	r9, [fp, #-72]	@, MemRecord_ul.VirAddr
	mov	r7, r7, lsr #1	@, Width,
	mov	r2, r3, asl #4	@, tmp260,
	str	r2, [fp, #-92]	@, %sfp
	ldr	r1, [fp, #-92]	@, %sfp
	add	lr, r9, #2097152	@,,
	ldr	r2, [fp, #-88]	@, %sfp
	mov	r6, r6, lsr #1	@, Height,
	cmp	r1, #0	@,
	add	ip, r1, #15	@ tmp263,,
	str	r0, [fp, #-96]	@, %sfp
	movge	ip, r1	@ Stride,
	adds	r0, r2, #31	@ tmp265,,
	addmi	r0, r2, #62	@, tmp267,,
	str	r9, [fp, #-108]	@, %sfp
	mov	r3, ip, asr #4	@ tmp264, Stride,
	cmp	r8, #0	@ PicStructure,
	mov	r9, r0, asr #5	@ tmp269, tmp267,
	str	r7, [fp, #-120]	@, %sfp
	str	r6, [fp, #-104]	@, %sfp
	str	lr, [fp, #-116]	@, %sfp
	mla	r9, r9, r3, r4	@ Caddress, tmp269, tmp264, Yaddress
	bne	.L41	@,
	cmp	r2, #0	@,
	beq	.L42	@,
	ldr	sl, [fp, #-96]	@, %sfp
	str	r9, [fp, #-112]	@ Caddress, %sfp
	mov	r9, r8	@ i, i
	str	sl, [fp, #-80]	@, %sfp
	str	sl, [fp, #-84]	@, %sfp
	mov	sl, r5	@ ImgWidthInPixAln, ImgWidthInPixAln
.L43:
	cmp	sl, #0	@ ImgWidthInPixAln,
	beq	.L46	@,
	and	r7, r9, #15	@ pretmp.742, i,
	ldr	r6, [fp, #-92]	@, %sfp
	mov	r3, r9, lsr #4	@ pretmp.886, i,
	ldr	r0, [fp, #-84]	@, %sfp
	mov	r8, r7, asl #8	@ tmp280, pretmp.742,
	mov	r2, #256	@,
	sub	r5, sl, #1	@ tmp370, ImgWidthInPixAln,
	mla	r8, r6, r3, r8	@ pretmp.743,, pretmp.886, tmp280
	ubfx	r7, r5, #8, #1	@ tmp371, tmp370,,
	add	r6, r0, r2	@ ivtmp.848,,
	mov	r5, r2	@ j,
	add	r1, r4, r8	@, Yaddress, pretmp.743
	bl	memcpy	@
	cmp	sl, r5	@ ImgWidthInPixAln, j
	bls	.L46	@,
	cmp	r7, #0	@ tmp371,
	beq	.L44	@,
	add	r0, r8, #4096	@ tmp485, pretmp.743,
	mov	r2, r5	@, j
	add	r1, r4, r0	@, Yaddress, tmp485
	mov	r0, r6	@, ivtmp.848
	bl	memcpy	@
	mov	r5, #512	@ j,
	cmp	sl, r5	@ ImgWidthInPixAln, j
	add	r6, r6, #256	@ ivtmp.848, ivtmp.848,
	bls	.L46	@,
.L44:
	mov	r1, r5, lsr #8	@ tmp271, j,
	add	r7, r5, #256	@ tmp372, j,
	mov	r2, #256	@,
	add	r5, r7, r2	@ j, tmp372,
	add	ip, r8, r1, asl #12	@, tmp273, pretmp.743, tmp271,
	mov	r7, r7, lsr #8	@ tmp404, tmp372,
	add	r1, r4, ip	@, Yaddress, tmp273
	mov	r0, r6	@, ivtmp.848
	add	r6, r6, r2	@ tmp373, ivtmp.848,
	bl	memcpy	@
	add	r3, r8, r7, asl #12	@, tmp406, pretmp.743, tmp404,
	mov	r2, #256	@,
	mov	r0, r6	@, tmp373
	add	r1, r4, r3	@, Yaddress, tmp406
	add	r6, r6, r2	@ ivtmp.848, tmp373,
	bl	memcpy	@
	cmp	sl, r5	@ ImgWidthInPixAln, j
	bhi	.L44	@,
.L46:
	ldr	r2, [fp, #-88]	@, %sfp
	add	r9, r9, #1	@ i, i,
	ldr	lr, [fp, #-84]	@, %sfp
	cmp	r2, r9	@, i
	add	r0, lr, sl	@,, ImgWidthInPixAln
	str	r0, [fp, #-84]	@, %sfp
	bhi	.L43	@,
	ldr	lr, [fp, #-88]	@, %sfp
	mov	r5, sl	@ ImgWidthInPixAln, ImgWidthInPixAln
	ldr	r0, [fp, #-96]	@, %sfp
	ldr	r2, [fp, #-100]	@, %sfp
	mul	r1, sl, lr	@, ImgWidthInPixAln,
	ldr	r9, [fp, #-112]	@ Caddress, %sfp
	bl	klib_fwrite	@
	ldr	ip, [fp, #-88]	@, %sfp
	movs	r4, ip, lsr #1	@,,
	str	r4, [fp, #-84]	@, %sfp
	beq	.L47	@,
	ldr	r1, [fp, #-92]	@, %sfp
	mov	r8, r5	@ ImgWidthInPixAln, ImgWidthInPixAln
	mov	sl, r1, asr #1	@,,
	str	sl, [fp, #-88]	@, %sfp
	mov	sl, #0	@ i.847,
.L48:
	cmp	r8, #0	@ ImgWidthInPixAln,
	beq	.L50	@,
	and	r6, sl, #7	@ pretmp.878, i.847,
	ldr	r1, [fp, #-88]	@, %sfp
	mov	r3, sl, lsr #3	@ pretmp.885, i.847,
	ldr	r0, [fp, #-80]	@, %sfp
	mov	r7, r6, asl #8	@ tmp294, pretmp.878,
	mov	r2, #256	@,
	sub	r5, r8, #1	@ tmp364, ImgWidthInPixAln,
	mov	r4, r2	@ j.846,
	mla	r7, r1, r3, r7	@ pretmp.747,, pretmp.885, tmp294
	ubfx	r6, r5, #8, #1	@ tmp365, tmp364,,
	add	r5, r0, r2	@ ivtmp.842,,
	add	r1, r9, r7	@, Caddress, pretmp.747
	bl	memcpy	@
	cmp	r8, r4	@ ImgWidthInPixAln, j.846
	bls	.L50	@,
	cmp	r6, #0	@ tmp365,
	beq	.L49	@,
	add	lr, r7, #2048	@ tmp481, pretmp.747,
	mov	r2, r4	@, j.846
	mov	r0, r5	@, ivtmp.842
	add	r1, r9, lr	@, Caddress, tmp481
	bl	memcpy	@
	mov	r4, #512	@ j.846,
	cmp	r8, r4	@ ImgWidthInPixAln, j.846
	add	r5, r5, #256	@ ivtmp.842, ivtmp.842,
	bls	.L50	@,
.L49:
	mov	ip, r4, lsr #8	@ tmp285, j.846,
	add	r6, r4, #256	@ tmp366, j.846,
	mov	r2, #256	@,
	mov	r0, r5	@, ivtmp.842
	add	r4, r7, ip, asl #11	@, tmp287, pretmp.747, tmp285,
	add	r5, r5, r2	@ tmp367, ivtmp.842,
	add	r1, r9, r4	@, Caddress, tmp287
	add	r4, r6, r2	@ j.846, tmp366,
	mov	r6, r6, lsr #8	@ tmp416, tmp366,
	bl	memcpy	@
	mov	r0, r5	@, tmp367
	mov	r2, #256	@,
	add	r3, r7, r6, asl #11	@, tmp418, pretmp.747, tmp416,
	add	r5, r5, r2	@ ivtmp.842, tmp367,
	add	r1, r9, r3	@, Caddress, tmp418
	bl	memcpy	@
	cmp	r8, r4	@ ImgWidthInPixAln, j.846
	bhi	.L49	@,
.L50:
	ldr	r2, [fp, #-84]	@, %sfp
	add	sl, sl, #1	@ i.847, i.847,
	ldr	lr, [fp, #-80]	@, %sfp
	cmp	sl, r2	@ i.847,
	add	r0, lr, r8	@,, ImgWidthInPixAln
	str	r0, [fp, #-80]	@, %sfp
	bcc	.L48	@,
	mov	r5, r8	@ ImgWidthInPixAln, ImgWidthInPixAln
.L47:
	ldr	r4, [fp, #4]	@, chroma_idc
	cmp	r4, #1	@,
	beq	.L134	@,
	ldr	r2, [fp, #4]	@, chroma_idc
	cmp	r2, #0	@,
	beq	.L70	@,
.L66:
	ldr	r3, [fp, #-104]	@, %sfp
	ldr	r0, [fp, #-120]	@, %sfp
	ldr	r2, [fp, #-100]	@, %sfp
	mul	r4, r0, r3	@ temp.875,,
	ldr	r0, [fp, #-108]	@, %sfp
	mov	r1, r4	@, temp.875
	bl	klib_fwrite	@
	ldr	r2, [fp, #-100]	@, %sfp
	mov	r1, r4	@, temp.875
	ldr	r0, [fp, #-116]	@, %sfp
	bl	klib_fwrite	@
	ldr	r1, [fp, #-56]	@, MemRecord_y.VirAddr
	ldr	r0, [fp, #-52]	@, MemRecord_y.PhyAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #60	@,,
	mov	r1, #16	@,
	bl	__memzero	@
	ldr	r1, [fp, #-72]	@, MemRecord_ul.VirAddr
	ldr	r0, [fp, #-68]	@, MemRecord_ul.PhyAddr
	bl	MEM_ReleaseMemBlock	@
	sub	r0, fp, #76	@,,
	mov	r1, #16	@,
	bl	__memzero	@
.L72:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L133:
	movw	r1, #:lower16:.LC8	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC8	@,
	bl	dprint_vfmw	@
	b	.L72	@
.L41:
	ldr	r0, [fp, #-88]	@, %sfp
	subs	r8, r8, #1	@, PicStructure,
	movne	r8, #1	@
	str	r8, [fp, #-112]	@, %sfp
	cmp	r0, r8	@,
	bls	.L57	@,
	str	r9, [fp, #-80]	@ Caddress, %sfp
	mov	sl, r5	@ ImgWidthInPixAln, ImgWidthInPixAln
	mov	r9, r8	@ i.858, i.858
.L58:
	cmp	sl, #0	@ ImgWidthInPixAln,
	beq	.L60	@,
	ldr	r5, [fp, #-96]	@, %sfp
	mov	r2, r9, lsr #1	@ pretmp.887, i.858,
	ldr	r1, [fp, #-92]	@, %sfp
	mov	r7, r9, lsr #4	@ pretmp.881, i.858,
	and	lr, r9, #15	@ pretmp.893, i.858,
	sub	r6, sl, #1	@ tmp393, ImgWidthInPixAln,
	mla	r0, sl, r2, r5	@ ivtmp.831, ImgWidthInPixAln, pretmp.887,
	mov	r2, #256	@,
	mul	r8, r1, r7	@ tmp310,, pretmp.881
	mov	r5, r2	@ j.857,
	mla	r8, lr, r2, r8	@ pretmp.739, pretmp.893,, tmp310
	ubfx	r7, r6, #8, #1	@ tmp394, tmp393,,
	add	r6, r0, r2	@ ivtmp.831, ivtmp.831,
	add	r1, r4, r8	@, Yaddress, pretmp.739
	bl	memcpy	@
	cmp	sl, r5	@ ImgWidthInPixAln, j.857
	bls	.L60	@,
	cmp	r7, #0	@ tmp394,
	beq	.L59	@,
	add	ip, r8, #4096	@ tmp496, pretmp.739,
	mov	r2, r5	@, j.857
	mov	r0, r6	@, ivtmp.831
	add	r1, r4, ip	@, Yaddress, tmp496
	bl	memcpy	@
	mov	r5, #512	@ j.857,
	cmp	sl, r5	@ ImgWidthInPixAln, j.857
	add	r6, r6, #256	@ ivtmp.831, ivtmp.831,
	bls	.L60	@,
.L59:
	mov	r3, r5, lsr #8	@ tmp301, j.857,
	add	r7, r5, #256	@ tmp395, j.857,
	mov	r2, #256	@,
	mov	r0, r6	@, ivtmp.831
	add	r5, r8, r3, asl #12	@, tmp303, pretmp.739, tmp301,
	add	r6, r6, r2	@ tmp396, ivtmp.831,
	add	r1, r4, r5	@, Yaddress, tmp303
	add	r5, r7, r2	@ j.857, tmp395,
	mov	r7, r7, lsr #8	@ tmp440, tmp395,
	bl	memcpy	@
	mov	r0, r6	@, tmp396
	mov	r2, #256	@,
	add	r1, r8, r7, asl #12	@, tmp442, pretmp.739, tmp440,
	add	r6, r6, r2	@ ivtmp.831, tmp396,
	add	r1, r4, r1	@, Yaddress, tmp442
	bl	memcpy	@
	cmp	sl, r5	@ ImgWidthInPixAln, j.857
	bhi	.L59	@,
.L60:
	ldr	ip, [fp, #-88]	@, %sfp
	add	r9, r9, #2	@ i.858, i.858,
	cmp	ip, r9	@, i.858
	bhi	.L58	@,
	ldr	r9, [fp, #-80]	@ Caddress, %sfp
	mov	r5, sl	@ ImgWidthInPixAln, ImgWidthInPixAln
.L57:
	ldr	ip, [fp, #-88]	@, %sfp
	ldr	r0, [fp, #-96]	@, %sfp
	ldr	r2, [fp, #-100]	@, %sfp
	mul	r3, r5, ip	@ tmp312, ImgWidthInPixAln,
	mov	r1, r3, lsr #1	@, tmp312,
	bl	klib_fwrite	@
	ldr	r0, [fp, #-88]	@, %sfp
	movs	r4, r0, lsr #1	@,,
	str	r4, [fp, #-84]	@, %sfp
	beq	.L61	@,
	ldr	sl, [fp, #-96]	@, %sfp
	ldr	lr, [fp, #-92]	@, %sfp
	str	sl, [fp, #-80]	@, %sfp
	mov	sl, #0	@ i.865,
	mov	r8, lr, asr #1	@,,
	str	r8, [fp, #-88]	@, %sfp
	mov	r8, r5	@ ImgWidthInPixAln, ImgWidthInPixAln
.L62:
	cmp	r8, #0	@ ImgWidthInPixAln,
	beq	.L64	@,
	and	r6, sl, #7	@ pretmp.895, i.865,
	ldr	lr, [fp, #-88]	@, %sfp
	mov	r1, sl, lsr #3	@ pretmp.736, i.865,
	ldr	r0, [fp, #-80]	@, %sfp
	mov	r7, r6, asl #8	@ tmp326, pretmp.895,
	mov	r2, #256	@,
	sub	r5, r8, #1	@ tmp387, ImgWidthInPixAln,
	mov	r4, r2	@ j.864,
	mla	r7, lr, r1, r7	@ pretmp.737,, pretmp.736, tmp326
	ubfx	r6, r5, #8, #1	@ tmp388, tmp387,,
	add	r5, r0, r2	@ ivtmp.869,,
	add	r1, r9, r7	@, Caddress, pretmp.737
	bl	memcpy	@
	cmp	r8, r4	@ ImgWidthInPixAln, j.864
	bls	.L64	@,
	cmp	r6, #0	@ tmp388,
	beq	.L63	@,
	add	r3, r7, #2048	@ tmp492, pretmp.737,
	mov	r2, r4	@, j.864
	mov	r0, r5	@, ivtmp.869
	add	r1, r9, r3	@, Caddress, tmp492
	bl	memcpy	@
	mov	r4, #512	@ j.864,
	cmp	r8, r4	@ ImgWidthInPixAln, j.864
	add	r5, r5, #256	@ ivtmp.869, ivtmp.869,
	bls	.L64	@,
.L63:
	mov	r3, r4, lsr #8	@ tmp317, j.864,
	add	r6, r4, #256	@ tmp389, j.864,
	mov	r2, #256	@,
	mov	r0, r5	@, ivtmp.869
	add	r4, r7, r3, asl #11	@, tmp319, pretmp.737, tmp317,
	add	r5, r5, r2	@ tmp390, ivtmp.869,
	add	r1, r9, r4	@, Caddress, tmp319
	add	r4, r6, r2	@ j.864, tmp389,
	mov	r6, r6, lsr #8	@ tmp452, tmp389,
	bl	memcpy	@
	mov	r0, r5	@, tmp390
	mov	r2, #256	@,
	add	r1, r7, r6, asl #11	@, tmp454, pretmp.737, tmp452,
	add	r5, r5, r2	@ ivtmp.869, tmp390,
	add	r1, r9, r1	@, Caddress, tmp454
	bl	memcpy	@
	cmp	r8, r4	@ ImgWidthInPixAln, j.864
	bhi	.L63	@,
.L64:
	ldr	r2, [fp, #-84]	@, %sfp
	add	sl, sl, #1	@ i.865, i.865,
	ldr	ip, [fp, #-80]	@, %sfp
	cmp	sl, r2	@ i.865,
	add	r0, ip, r8	@,, ImgWidthInPixAln
	str	r0, [fp, #-80]	@, %sfp
	bcc	.L62	@,
	mov	r5, r8	@ ImgWidthInPixAln, ImgWidthInPixAln
.L61:
	ldr	r4, [fp, #4]	@, chroma_idc
	cmp	r4, #1	@,
	beq	.L135	@,
	ldr	r0, [fp, #4]	@, chroma_idc
	cmp	r0, #0	@,
	bne	.L66	@,
	ldr	lr, [fp, #-104]	@, %sfp
	ldr	r3, [fp, #-112]	@, %sfp
	cmp	lr, r3	@,
	bls	.L70	@,
	ldr	r4, [fp, #-104]	@, %sfp
	add	r3, r3, #2	@ i.852,,
	ldr	r1, [fp, #-112]	@, %sfp
	cmp	r4, r3	@, i.852
	mvn	r2, r1	@ tmp381,
	add	ip, r2, r4	@ tmp382, tmp381,
	ubfx	r2, ip, #1, #1	@ tmp383, tmp382,,
	bls	.L70	@,
	cmp	r2, #0	@ tmp383,
	beq	.L128	@,
	ldr	r2, [fp, #-104]	@, %sfp
	add	r3, r3, #2	@ i.852, i.852,
	cmp	r2, r3	@, i.852
	bls	.L70	@,
.L128:
	ldr	r2, [fp, #-104]	@ chrom_height, %sfp
.L73:
	add	r3, r3, #4	@ i.852, i.852,
	cmp	r2, r3	@ chrom_height, i.852
	bhi	.L73	@,
.L70:
	mov	r1, #128	@,
	mov	r2, #1048576	@,
	ldr	r0, [fp, #-116]	@, %sfp
	bl	memset	@
	ldr	r0, [fp, #-108]	@, %sfp
	mov	r1, #128	@,
	mov	r2, #1048576	@,
	bl	memset	@
	b	.L66	@
.L135:
	ldr	r3, [fp, #-104]	@, %sfp
	cmp	r3, #0	@,
	beq	.L66	@,
	ldr	ip, [fp, #-112]	@, %sfp
	ldr	r2, [fp, #-96]	@, %sfp
	ldr	r7, [fp, #-108]	@ ul, %sfp
	ldr	lr, [fp, #-120]	@ chrom_width, %sfp
	mla	r0, r5, ip, r2	@ tmp.866, ImgWidthInPixAln,,
	mov	r5, r5, asl #1	@ D.53750, ImgWidthInPixAln,
	mov	ip, #0	@ i.872,
.L67:
	cmp	lr, #0	@ chrom_width,
	beq	.L69	@,
	mov	r3, ip, lsr #1	@ pretmp.879, i.872,
	ldrb	sl, [r0, #0]	@ zero_extendqisi2	@ tmp472,* tmp.866
	mov	r1, #1	@ j.871,
	cmp	lr, r1	@ chrom_width, j.871
	mul	r6, lr, r3	@ tmp333, chrom_width, pretmp.879
	sub	r9, lr, #1	@ tmp374, chrom_width,
	and	r9, r9, r1	@ tmp376, tmp374,
	add	r3, r0, #2	@ ivtmp.799, tmp.866,
	add	r4, r7, r6	@ ivtmp.802, ul, tmp333
	add	r8, r4, #2097152	@ tmp471, ivtmp.802,
	add	r2, r4, r1	@ ivtmp.802, ivtmp.802,
	strb	sl, [r8, #0]	@ tmp472,
	ldrb	r8, [r0, #1]	@ zero_extendqisi2	@ tmp473,
	strb	r8, [r7, r6]	@ tmp473,
	bls	.L69	@,
	cmp	r9, #0	@ tmp376,
	beq	.L68	@,
	ldrb	r8, [r3, #0]	@ zero_extendqisi2	@ tmp488,* ivtmp.799
	add	r6, r2, #2097152	@ tmp487, ivtmp.802,
	mov	r1, #2	@ j.871,
	cmp	lr, r1	@ chrom_width, j.871
	add	r2, r2, #1	@ ivtmp.802, ivtmp.802,
	strb	r8, [r6, #0]	@ tmp488,
	ldrb	r6, [r3, #1]	@ zero_extendqisi2	@ tmp489,
	add	r3, r3, r1	@ ivtmp.799, ivtmp.799,
	strb	r6, [r4, #1]	@ tmp489,
	bls	.L69	@,
.L68:
	ldrb	sl, [r3, #0]	@ zero_extendqisi2	@ tmp329,* ivtmp.799
	add	r8, r2, #2097152	@ tmp328, ivtmp.802,
	mov	r4, r2	@ tmp379, ivtmp.802
	add	r6, r3, #2	@ tmp378, ivtmp.799,
	add	r1, r1, #2	@ j.871, j.871,
	strb	sl, [r8, #0]	@ tmp329,
	cmp	lr, r1	@ chrom_width, j.871
	ldrb	sl, [r3, #1]	@ zero_extendqisi2	@ tmp331,
	strb	sl, [r4], #1	@ tmp331,
	add	r8, r4, #2097152	@ tmp465, tmp379,
	ldrb	sl, [r3, #2]	@ zero_extendqisi2	@ tmp466,
	add	r3, r6, #2	@ ivtmp.799, tmp378,
	strb	sl, [r8, #0]	@ tmp466,
	ldrb	r6, [r6, #1]	@ zero_extendqisi2	@ tmp467,
	strb	r6, [r2, #1]	@ tmp467,
	add	r2, r4, #1	@ ivtmp.802, tmp379,
	bhi	.L68	@,
.L69:
	ldr	r1, [fp, #-104]	@, %sfp
	add	ip, ip, #2	@ i.872, i.872,
	cmp	r1, ip	@, i.872
	bls	.L66	@,
	add	r0, r0, r5	@ tmp.866, tmp.866, D.53750
	b	.L67	@
.L134:
	ldr	r3, [fp, #-104]	@, %sfp
	cmp	r3, #0	@,
	beq	.L66	@,
	ldr	r6, [fp, #-96]	@ tmp, %sfp
	mov	r8, #0	@ i.851,
	ldr	r7, [fp, #-108]	@ ivtmp.849, %sfp
	mov	r9, r3	@ chrom_height,
	ldr	lr, [fp, #-120]	@ chrom_width, %sfp
.L53:
	cmp	lr, #0	@ chrom_width,
	beq	.L55	@,
	ldrb	ip, [r6, #0]	@ zero_extendqisi2	@ tmp436,* tmp
	add	r4, r7, #2097152	@ tmp435, ivtmp.849,
	mov	r0, #1	@ j.850,
	cmp	lr, r0	@ chrom_width, j.850
	sub	r3, lr, #1	@ tmp356, chrom_width,
	mov	r2, r7	@ ivtmp.764, ivtmp.849
	strb	ip, [r4, #0]	@ tmp436,
	and	ip, r3, r0	@ tmp358, tmp356,
	ldrb	r1, [r6, #1]	@ zero_extendqisi2	@ tmp437,
	add	r3, r6, #2	@ ivtmp.761, tmp,
	strb	r1, [r2], #1	@ tmp437,
	bls	.L55	@,
	cmp	ip, #0	@ tmp358,
	beq	.L54	@,
	ldrb	r1, [r3, #0]	@ zero_extendqisi2	@ tmp477,* ivtmp.761
	add	r4, r2, #2097152	@ tmp476, ivtmp.764,
	mov	r0, #2	@ j.850,
	cmp	lr, r0	@ chrom_width, j.850
	strb	r1, [r4, #0]	@ tmp477,
	ldrb	ip, [r3, #1]	@ zero_extendqisi2	@ tmp478,
	add	r3, r3, r0	@ ivtmp.761, ivtmp.761,
	strb	ip, [r2], #1	@ tmp478,
	bls	.L55	@,
.L54:
	ldrb	sl, [r3, #0]	@ zero_extendqisi2	@ tmp296,* ivtmp.761
	add	r4, r2, #2097152	@ tmp295, ivtmp.764,
	mov	r1, r2	@ tmp361, ivtmp.764
	add	ip, r3, #2	@ tmp360, ivtmp.761,
	add	r0, r0, #2	@ j.850, j.850,
	strb	sl, [r4, #0]	@ tmp296,
	cmp	lr, r0	@ chrom_width, j.850
	ldrb	sl, [r3, #1]	@ zero_extendqisi2	@ tmp298,
	strb	sl, [r1], #1	@ tmp298,
	add	r4, r1, #2097152	@ tmp429, tmp361,
	ldrb	sl, [r3, #2]	@ zero_extendqisi2	@ tmp430,
	add	r3, ip, #2	@ ivtmp.761, tmp360,
	strb	sl, [r4, #0]	@ tmp430,
	ldrb	ip, [ip, #1]	@ zero_extendqisi2	@ tmp431,
	strb	ip, [r2, #1]	@ tmp431,
	add	r2, r1, #1	@ ivtmp.764, tmp361,
	bhi	.L54	@,
.L55:
	add	r8, r8, #1	@ i.851, i.851,
	add	r7, r7, lr	@ ivtmp.849, ivtmp.849, chrom_width
	cmp	r9, r8	@ chrom_height, i.851
	bls	.L66	@,
	add	r6, r6, r5	@ tmp, tmp, ImgWidthInPixAln
	b	.L53	@
.L42:
	mov	r1, r8	@, PicStructure
	ldr	r0, [fp, #-96]	@, %sfp
	ldr	r2, [fp, #-100]	@, %sfp
	bl	klib_fwrite	@
	b	.L47	@
	.fnend
	.size	VDMHAL_V300R001_WriteBigTitle1DYuv, .-VDMHAL_V300R001_WriteBigTitle1DYuv
	.global	__aeabi_idiv
	.align	2
	.global	VDMHAL_V300R001_ArrangeMem_BTL
	.type	VDMHAL_V300R001_ArrangeMem_BTL, %function
VDMHAL_V300R001_ArrangeMem_BTL:
	.fnstart
.LFB1534:
	@ args = 28, pretend = 0, frame = 16
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
	subs	r4, r0, #0	@ MemAddr, MemAddr
	str	r1, [fp, #-52]	@ MemSize, %sfp
	mov	r5, r2	@ Width, Width
	mov	r6, r3	@ Height, Height
	ldr	r7, [fp, #20]	@ pVdmMemArrange, pVdmMemArrange
	beq	.L197	@,
	ldr	r3, [fp, #16]	@ UserDec, UserDec
	cmp	r3, #1	@ UserDec,
	beq	.L198	@,
	cmp	r6, #31	@ Height,
	movgt	ip, #0	@, tmp239
	movle	ip, #1	@, tmp239
	sub	r0, r2, #32	@ tmp234, Width,
	movw	r3, #8160	@ tmp236,
	cmp	r0, r3	@ tmp234, tmp236
	movls	lr, ip	@, tmp242, tmp239
	orrhi	lr, ip, #1	@,, tmp242, tmp239
	cmp	lr, #0	@ tmp242,
	bne	.L142	@,
	cmp	r6, #8192	@ Height,
	bgt	.L142	@,
.L141:
	cmp	r7, #0	@ pVdmMemArrange,
	beq	.L199	@,
	mov	r0, r7	@, pVdmMemArrange
	mov	r1, #940	@,
	ldr	sl, [fp, #4]	@ PmvNum, PmvNum
	bl	__memzero	@
	add	r1, r6, #15	@ tmp251, Height,
	add	r0, r5, #15	@ D.52238, Width,
	movw	r2, #:lower16:g_not_direct_8x8_inference_flag	@ tmp259,
	movt	r2, #:upper16:g_not_direct_8x8_inference_flag	@ tmp259,
	mov	r3, r1, asr #4	@ ImgHeightInMb, tmp251,
	mov	r1, r0, asr #4	@ ImgWidthInMb, D.52238,
	ldrb	r6, [r2, #0]	@ zero_extendqisi2	@ g_not_direct_8x8_inference_flag, g_not_direct_8x8_inference_flag
	cmp	sl, #20	@ PmvNum,
	movge	sl, #20	@ PmvNum.957,
	mul	r2, r1, r3	@ tmp261, ImgWidthInMb, ImgHeightInMb
	cmp	r3, #36	@ ImgHeightInMb,
	cmple	r1, #45	@, ImgWidthInMb,
	movle	ip, #64	@, ColMbSize,
	movgt	ip, #32	@, ColMbSize,
	cmp	r6, #1	@ g_not_direct_8x8_inference_flag,
	moveq	ip, #64	@ ColMbSize,
	mul	r2, ip, r2	@ tmp262, ColMbSize, tmp261
	ldr	ip, [fp, #-52]	@, %sfp
	add	r6, r2, #127	@ tmp263, tmp262,
	bic	r6, r6, #127	@ PmvSlotLen, tmp263,
	mul	r2, sl, r6	@, PmvNum.957, PmvSlotLen
	cmp	r2, ip	@,
	str	r2, [fp, #-56]	@, %sfp
	bge	.L200	@,
	mov	r1, r1, asl #4	@ ImgWidthInPixAln, ImgWidthInMb,
	add	r9, r4, #1020	@ tmp271, MemAddr,
	add	ip, r9, #3	@ tmp271, tmp271,
	add	r8, r1, #255	@ tmp275, ImgWidthInPixAln,
	sub	r9, r1, #1	@ tmp277, ImgWidthInPixAln,
	bic	lr, ip, #1020	@ tmp273, tmp271,
	bic	ip, r8, #255	@ SlotWidth, tmp275,
	movw	r8, #2047	@ tmp278,
	cmp	r9, r8	@ tmp277, tmp278
	bic	r2, lr, #3	@ tmp273, tmp273,
	rsb	lr, r4, r2	@, MemAddr, tmp273
	str	sl, [r7, #936]	@ PmvNum.957, <variable>.ValidPMVNum
	mov	r2, r6, asr #1	@ tmp270, PmvSlotLen,
	str	lr, [fp, #-48]	@, %sfp
	mov	lr, ip, asl #4	@ tmp276, SlotWidth,
	str	r2, [r7, #932]	@ tmp270, <variable>.HafPmvOffset
	str	lr, [r7, #0]	@ tmp276, <variable>.VahbStride
	bhi	.L201	@,
.L148:
	mov	r9, #16	@ level,
.L150:
	mov	r3, r3, asl #4	@ ImgHeightInPixAln, ImgHeightInMb,
	ldr	r1, [fp, #28]	@, BtlDbdrEnable
	adds	lr, r3, #31	@ tmp288, ImgHeightInPixAln,
	addmi	lr, r3, #62	@, tmp289, ImgHeightInPixAln,
	cmp	r1, #0	@,
	mov	r8, lr, asr #5	@ tmp291, tmp289,
	mul	r9, r8, r9	@ D.52283, tmp291, level
	mul	r8, ip, r8	@ D.52278, SlotWidth, tmp291
	add	ip, r9, r8	@ tmp292, D.52283, D.52278
	mov	r2, ip, asl #5	@ tmp293, tmp292,
	str	r2, [r7, #536]	@ tmp293, <variable>.ChromOffset
	ldreq	r2, [fp, #28]	@ DbdrInfoSlotLen, BtlDbdrEnable
	bne	.L202	@,
	ldr	r1, [fp, #24]	@, Btl1Dt2DEnable
	cmp	r1, #0	@,
	moveq	r5, r1	@ ImgInfoSlotLen,
	bne	.L203	@,
.L155:
	ldr	r1, [fp, #12]	@, s32DisplayFrameNum
	cmp	r1, #0	@,
	bne	.L156	@,
.L205:
	str	r1, [r7, #808]	@, <variable>.ValidBTLFrameNum
	ldr	r5, [fp, #12]	@ prephitmp.917, s32DisplayFrameNum
.L157:
	ldr	r2, [fp, #8]	@, s32MaxRefFrameNum
	ldr	r3, [fp, #-48]	@, %sfp
	cmp	r2, #0	@,
	add	r5, r5, r3	@ Offset.961, prephitmp.917,
	bne	.L162	@,
.L204:
	str	r2, [r7, #548]	@, <variable>.ValidFrameNum
	ldr	sl, [fp, #8]	@ prephitmp.966, s32MaxRefFrameNum
.L163:
	ldr	r9, [r7, #936]	@ D.52341, <variable>.ValidPMVNum
	add	r5, sl, r5	@ Offset.964, prephitmp.966, Offset.961
	add	r2, r5, r4	@ MemAddr.965, Offset.964, MemAddr
	cmp	r9, #0	@ D.52341,
	ble	.L168	@,
	mov	r1, #1	@ i,
	cmp	r1, r9	@ i, D.52341
	sub	lr, r9, #1	@ tmp359, D.52341,
	str	r2, [r7, #812]	@ MemAddr.965, <variable>.PMVAddr
	and	r0, lr, r1	@ tmp361, tmp359,
	add	r2, r2, r6	@ ivtmp.930, MemAddr.965, PmvSlotLen
	add	r3, r7, #4	@ ivtmp.934, pVdmMemArrange,
	bge	.L168	@,
	cmp	r0, #0	@ tmp361,
	beq	.L169	@,
	mov	r1, #2	@ i,
	cmp	r1, r9	@ i, D.52341
	str	r2, [r3, #812]	@ ivtmp.930, <variable>.PMVAddr
	add	r2, r2, r6	@ ivtmp.930, ivtmp.930, PmvSlotLen
	add	r3, r3, #4	@ ivtmp.934, ivtmp.934,
	bge	.L168	@,
.L169:
	add	r1, r1, #2	@ i, i,
	add	r0, r3, #4	@ tmp363, ivtmp.934,
	cmp	r1, r9	@ i, D.52341
	add	ip, r2, r6	@ ivtmp.930, ivtmp.930, PmvSlotLen
	str	r2, [r3, #812]	@ ivtmp.930, <variable>.PMVAddr
	add	r2, ip, r6	@ ivtmp.930, ivtmp.930, PmvSlotLen
	str	ip, [r0, #812]	@ ivtmp.930, <variable>.PMVAddr
	add	r3, r0, #4	@ ivtmp.934, tmp363,
	blt	.L169	@,
.L168:
	mla	r5, r9, r6, r5	@ tmp357, D.52341, PmvSlotLen, Offset.964
	mov	r0, #0	@ D.52216,
	str	r5, [r7, #4]	@ tmp357, <variable>.TotalMemUsed
.L138:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L156:
	ldr	r3, [fp, #24]	@, Btl1Dt2DEnable
	cmp	r3, #0	@,
	beq	.L159	@,
	ldr	r0, [fp, #12]	@, s32DisplayFrameNum
	str	r0, [r7, #808]	@, <variable>.ValidBTLFrameNum
	ldr	r3, [fp, #12]	@ s32DisplayFrameNum.960, s32DisplayFrameNum
.L160:
	cmp	r3, #0	@ s32DisplayFrameNum.960,
	addle	r2, r5, r2	@ tmp335, ImgInfoSlotLen, DbdrInfoSlotLen
	mulle	r5, r2, r3	@ prephitmp.917, tmp335, s32DisplayFrameNum.960
	ble	.L157	@,
	ldr	sl, [r7, #808]	@ D.52323, <variable>.ValidBTLFrameNum
	add	r5, r5, r2	@ pretmp.969, ImgInfoSlotLen, DbdrInfoSlotLen
	ldr	ip, [fp, #-48]	@, %sfp
	add	r3, r7, #4	@ ivtmp.948, pVdmMemArrange,
	cmp	sl, #1	@ D.52323,
	sub	r1, sl, #1	@ tmp369, D.52323,
	add	r2, ip, r4	@ ivtmp.944,, MemAddr
	and	r0, r1, #1	@ tmp371, tmp369,
	str	r2, [r7, #552]	@ ivtmp.944, <variable>.BtlAddr
	mov	r1, #1	@ i.959,
	add	r2, r2, r5	@ ivtmp.944, ivtmp.944, pretmp.969
	ble	.L189	@,
	cmp	r0, #0	@ tmp371,
	beq	.L161	@,
	mov	r1, #2	@ i.959,
	cmp	sl, r1	@ D.52323, i.959
	str	r2, [r3, #552]	@ ivtmp.944, <variable>.BtlAddr
	add	r2, r2, r5	@ ivtmp.944, ivtmp.944, pretmp.969
	add	r3, r3, #4	@ ivtmp.948, ivtmp.948,
	ble	.L189	@,
.L161:
	add	r1, r1, #2	@ i.959, i.959,
	add	lr, r3, #4	@ tmp373, ivtmp.948,
	cmp	sl, r1	@ D.52323, i.959
	add	r0, r2, r5	@ ivtmp.944, ivtmp.944, pretmp.969
	str	r2, [r3, #552]	@ ivtmp.944, <variable>.BtlAddr
	add	r2, r0, r5	@ ivtmp.944, ivtmp.944, pretmp.969
	str	r0, [lr, #552]	@ ivtmp.944, <variable>.BtlAddr
	add	r3, lr, #4	@ ivtmp.948, tmp373,
	bgt	.L161	@,
.L189:
	mul	r5, r5, sl	@ prephitmp.917, pretmp.969, D.52323
	ldr	r2, [fp, #8]	@, s32MaxRefFrameNum
	ldr	r3, [fp, #-48]	@, %sfp
	cmp	r2, #0	@,
	add	r5, r5, r3	@ Offset.961, prephitmp.917,
	beq	.L204	@,
.L162:
	ldr	lr, [fp, #24]	@, Btl1Dt2DEnable
	add	r8, r8, r8, asl #1	@, tmp345, D.52278, D.52278,
	add	r0, r9, r9, asl #1	@, tmp340, D.52283, D.52283,
	ldr	ip, [fp, #-52]	@, %sfp
	cmp	lr, #0	@,
	ldreq	r2, [fp, #8]	@, s32MaxRefFrameNum
	ldreq	r3, [fp, #12]	@, s32DisplayFrameNum
	ldrne	r1, [fp, #8]	@, s32MaxRefFrameNum
	addeq	sl, r2, #2	@ tmp337,,
	addeq	sl, sl, r3	@ ValidFrameNum, tmp337,
	mov	r3, r8, asl #5	@ tmp346, tmp345,
	addne	sl, r1, #2	@ ValidFrameNum,,
	mov	r8, r0, asl #5	@ tmp341, tmp340,
	ldr	r1, [fp, #-56]	@, %sfp
	mov	r9, r3, asr #1	@ tmp350, tmp346,
	ldr	r2, [fp, #-48]	@, %sfp
	add	r8, r9, r8, lsr #1	@, ImgSlotLen, tmp350, tmp341,
	rsb	lr, r1, ip	@ tmp351,,
	rsb	r1, r2, lr	@ FramePoolSize,, tmp351
	rsb	r0, r5, r1	@, Offset.961, FramePoolSize
	mov	r1, r8	@, ImgSlotLen
	bl	__aeabi_idiv	@
	cmp	r0, #64	@,
	movge	r0, #64	@ D.52334,
	cmp	r0, sl	@ D.52334, ValidFrameNum
	movlt	sl, r0	@ D.52334, D.52334
	movge	sl, sl	@ D.52334, ValidFrameNum
	str	sl, [r7, #548]	@ D.52334, <variable>.ValidFrameNum
	cmp	sl, #0	@ D.52334,
	ble	.L190	@,
	cmp	sl, #1	@ D.52334,
	add	r9, r5, r4	@ ivtmp.937, Offset.961, MemAddr
	sub	r3, sl, #1	@ tmp364, D.52334,
	str	r9, [r7, #8]	@ ivtmp.937, <variable>.FrameAddr
	and	r0, r3, #1	@ tmp366, tmp364,
	add	r2, r9, r8	@ ivtmp.937, ivtmp.937, ImgSlotLen
	mov	r1, #1	@ i.963,
	add	r3, r7, #4	@ ivtmp.941, pVdmMemArrange,
	ble	.L190	@,
	cmp	r0, #0	@ tmp366,
	beq	.L167	@,
	mov	r1, #2	@ i.963,
	cmp	sl, r1	@ D.52334, i.963
	str	r2, [r3, #8]	@ ivtmp.937, <variable>.FrameAddr
	add	r2, r2, r8	@ ivtmp.937, ivtmp.937, ImgSlotLen
	add	r3, r3, #4	@ ivtmp.941, ivtmp.941,
	ble	.L190	@,
.L167:
	add	r1, r1, #2	@ i.963, i.963,
	add	r0, r3, #4	@ tmp368, ivtmp.941,
	cmp	sl, r1	@ D.52334, i.963
	add	ip, r2, r8	@ ivtmp.937, ivtmp.937, ImgSlotLen
	str	r2, [r3, #8]	@ ivtmp.937, <variable>.FrameAddr
	add	r2, ip, r8	@ ivtmp.937, ivtmp.937, ImgSlotLen
	str	ip, [r0, #8]	@ ivtmp.937, <variable>.FrameAddr
	add	r3, r0, #4	@ ivtmp.941, tmp368,
	bgt	.L167	@,
.L190:
	mul	sl, sl, r8	@ prephitmp.966, D.52334, ImgSlotLen
	b	.L163	@
.L203:
	adds	lr, r5, #127	@ tmp321, Width,
	ldr	r1, [fp, #12]	@, s32DisplayFrameNum
	addmi	lr, r5, #254	@, tmp323, Width,
	cmp	r1, #0	@,
	mov	ip, lr, asr #7	@ tmp325, tmp323,
	add	r0, ip, ip, asl #1	@, tmp328, tmp325, tmp325,
	mov	r5, r0, asl #7	@ tmp329, tmp328,
	mul	r3, r3, r5	@ tmp330, ImgHeightInPixAln, tmp329
	mov	r5, r3, asr #1	@ ImgInfoSlotLen, tmp330,
	bne	.L156	@,
	b	.L205	@
.L202:
	cmp	r0, #0	@ D.52238,
	add	lr, r0, #15	@ tmp296, D.52238,
	movge	lr, r0	@ D.52238, D.52238
	mov	r2, lr, asr #4	@ tmp297, D.52238,
	adds	ip, r2, #7	@ tmp298, tmp297,
	addmi	r0, r2, #14	@, tmp300, tmp297,
	movpl	r0, ip	@, tmp300, tmp298
	mov	r1, r0, asr #3	@ tmp302, tmp300,
	mul	lr, r1, r3	@ tmp303, tmp302, ImgHeightInPixAln
	mov	r2, lr, asl #4	@ tmp304, tmp303,
	add	ip, r2, #7	@ tmp307, tmp304,
	cmp	r2, #0	@ tmp304,
	movlt	r2, ip	@ tmp306, tmp307
	mov	r0, r2, asr #3	@ tmp308, tmp306,
	add	r1, r0, r0, asl #1	@, tmp311, tmp308, tmp308,
	add	lr, r1, r1, lsr #31	@, tmp314, tmp311, tmp311,
	ldr	r1, [fp, #24]	@, Btl1Dt2DEnable
	mov	r2, lr, asr #1	@ tmp315, tmp314,
	adds	ip, r2, #127	@ tmp316, tmp315,
	addmi	r0, r2, #254	@, tmp318, tmp315,
	movpl	r0, ip	@, tmp318, tmp316
	cmp	r1, #0	@,
	bic	r2, r0, #127	@ DbdrInfoSlotLen, tmp318,
	moveq	r5, r1	@ ImgInfoSlotLen,
	beq	.L155	@,
	b	.L203	@
.L201:
	sub	lr, r1, #2048	@ tmp279, ImgWidthInPixAln,
	sub	r2, lr, #1	@ tmp279, tmp279,
	cmp	r2, r8	@ tmp279, tmp278
	movls	r9, #32	@ level,
	bls	.L150	@,
	sub	lr, r1, #4096	@ tmp282, ImgWidthInPixAln,
	sub	r2, lr, #1	@ tmp282, tmp282,
	cmp	r2, r8	@ tmp282, tmp278
	movls	r9, #48	@ level,
	bls	.L150	@,
	sub	r2, r1, #6144	@ tmp285, ImgWidthInPixAln,
	sub	r1, r2, #1	@ tmp285, tmp285,
	cmp	r1, r8	@ tmp285, tmp278
	movls	r9, #64	@ level,
	bls	.L150	@,
	b	.L148	@
.L198:
	cmp	r6, #31	@ Height,
	movgt	r2, #0	@, tmp226
	movle	r2, #1	@, tmp226
	sub	r1, r5, #32	@ tmp221, Width,
	movw	ip, #8160	@ tmp223,
	cmp	r1, ip	@ tmp221, tmp223
	movls	r0, r2	@, tmp229, tmp226
	orrhi	r0, r2, #1	@,, tmp229, tmp226
	cmp	r0, #0	@ tmp229,
	bne	.L142	@,
	cmp	r6, #16384	@ Height,
	ble	.L141	@,
.L142:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L206	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC11	@,
	movt	r3, #:upper16:.LC11	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52216,
	b	.L138	@
.L159:
	ldr	r3, [fp, #12]	@ s32DisplayFrameNum.960, s32DisplayFrameNum
	cmp	r3, #6	@ s32DisplayFrameNum.960,
	movlt	r3, #6	@ s32DisplayFrameNum.960,
	str	r3, [r7, #808]	@ s32DisplayFrameNum.960, <variable>.ValidBTLFrameNum
	b	.L160	@
.L200:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L206	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC13	@,
	movt	r3, #:upper16:.LC13	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52216,
	b	.L138	@
.L197:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L206	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52216,
	b	.L138	@
.L199:
	mov	r0, r7	@, pVdmMemArrange
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L206	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC12	@,
	movt	r3, #:upper16:.LC12	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52216,
	b	.L138	@
.L207:
	.align	2
.L206:
	.word	.LANCHOR0+56
	.fnend
	.size	VDMHAL_V300R001_ArrangeMem_BTL, .-VDMHAL_V300R001_ArrangeMem_BTL
	.align	2
	.global	VDMHAL_V300R001_SetVdhClkSkip
	.type	VDMHAL_V300R001_SetVdhClkSkip, %function
VDMHAL_V300R001_SetVdhClkSkip:
	.fnstart
.LFB1552:
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
	movw	r5, #:lower16:g_ChanCtx	@ ivtmp.1006,
	movt	r5, #:upper16:g_ChanCtx	@ ivtmp.1006,
	movw	r4, #:lower16:s_pFspInst	@,
	movt	r4, #:upper16:s_pFspInst	@,
	str	r4, [fp, #-52]	@, %sfp
	ldr	r4, [r5, #64]	@ D.53453,
	movw	r1, #:lower16:g_FrameRate	@,
	movw	r0, #:lower16:86236207	@,
	movt	r1, #:upper16:g_FrameRate	@,
	cmp	r4, #0	@ D.53453,
	movt	r0, #:upper16:86236207	@,
	movw	r3, #:lower16:s_pstVfmwChan	@,
	movw	r2, #:lower16:g_LastFrameRate	@,
	movt	r3, #:upper16:s_pstVfmwChan	@,
	movt	r2, #:upper16:g_LastFrameRate	@,
	mov	r8, #0	@ clk_need,
	str	r1, [fp, #-56]	@, %sfp
	str	r0, [fp, #-60]	@, %sfp
	add	sl, r5, #64	@ D.54310, ivtmp.1006,
	str	r3, [fp, #-68]	@, %sfp
	mov	r7, #30	@ s32FrameRate.1090,
	str	r2, [fp, #-64]	@, %sfp
	str	r8, [fp, #-48]	@ clk_need, %sfp
	blt	.L209	@,
.L233:
	mov	r0, r4	@, D.53453
	bl	VCTRL_IsChanActive	@
	cmp	r0, #0	@,
	movne	r6, r7	@ s32FrameRate, s32FrameRate.1090
	bne	.L211	@,
	ldr	r6, [fp, #-52]	@, %sfp
	ldr	r0, [fp, #-56]	@, %sfp
	ldr	r3, [r6, r4, asl #2]	@ pFsp, s_pFspInst
	ldr	r6, [r0, r4, asl #2]	@ s32FrameRate, g_FrameRate
	mov	r0, r4	@, D.53453
	ldr	r2, [r3, #68]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stInstCfg.s32DecFsWidth
	ldr	r8, [r3, #72]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stInstCfg.s32DecFsHeight
	adds	lr, r2, #15	@ tmp178, <variable>.stInstCfg.s32DecFsWidth,
	addmi	lr, r2, #30	@, tmp180, <variable>.stInstCfg.s32DecFsWidth,
	adds	r9, r8, #15	@ tmp183, <variable>.stInstCfg.s32DecFsHeight,
	addmi	ip, r8, #30	@, tmp185, <variable>.stInstCfg.s32DecFsHeight,
	movpl	ip, r9	@, tmp185, tmp183
	cmp	r6, #30	@ s32FrameRate,
	mov	r8, lr, asr #4	@ picWidthInMb, tmp180,
	mov	r9, ip, asr #4	@ picHeightInMb, tmp185,
	ldrgt	ip, [fp, #-64]	@, %sfp
	movle	r6, r7	@ s32FrameRate, s32FrameRate.1090
	strgt	r6, [ip, r4, asl #2]	@ s32FrameRate, g_LastFrameRate
	bl	VCTRL_GetVidStd	@
	cmp	r0, #16	@,
	ldrls	pc, [pc, r0, asl #2]	@
	b	.L211	@
.L226:
	.word	.L223
	.word	.L215
	.word	.L223
	.word	.L223
	.word	.L211
	.word	.L223
	.word	.L223
	.word	.L211
	.word	.L223
	.word	.L223
	.word	.L223
	.word	.L223
	.word	.L223
	.word	.L223
	.word	.L211
	.word	.L224
	.word	.L223
.L223:
	mul	r2, r8, r9	@ tmp271, picWidthInMb, picHeightInMb
	mul	r8, r6, r2	@ tmp272, s32FrameRate, tmp271
	ubfx	r3, r8, #1, #26	@ tmp275, tmp272,,
.L231:
	ldr	ip, [fp, #-60]	@, %sfp
	ldr	r1, [fp, #-48]	@, %sfp
	umull	r2, r3, ip, r3	@, tmp276,, tmp275
	add	r0, r1, r3, lsr #7	@,,, tmp276,
	str	r0, [fp, #-48]	@, %sfp
.L211:
	add	r5, r5, #4	@ ivtmp.1006, ivtmp.1006,
	cmp	r5, sl	@ ivtmp.1006, D.54310
	beq	.L209	@,
	ldr	r4, [r5, #64]	@ D.53453,
	mov	r7, r6	@ s32FrameRate.1090, s32FrameRate
	cmp	r4, #0	@ D.53453,
	bge	.L233	@,
.L209:
	movw	r3, #:lower16:g_pstRegCrg	@ tmp278,
	movt	r3, #:upper16:g_pstRegCrg	@ tmp278,
	ldr	r8, [fp, #-48]	@ clk_need, %sfp
	ldr	ip, [r3, #0]	@ g_pstRegCrg.550, g_pstRegCrg
	rsb	r8, r8, #32	@ clk_skip, clk_need,
	cmp	r8, #25	@ clk_skip,
	movge	r8, #25	@ clk_skip.1083,
	ldr	r2, [ip, #120]	@ D.53485, <variable>.PERI_CRG30.u32
	cmp	r8, #0	@ clk_skip.1083,
	bfigt	r2, r8, #12, #5	@ u32TmpValue, clk_skip.1083,,
	bfcle	r2, #12, #5	@ u32TmpValue,,
	bfc	r2, #17, #1	@ u32TmpValue,,
	str	r2, [ip, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r0, [r3, #0]	@ g_pstRegCrg.1088, g_pstRegCrg
	ldr	r1, [r0, #120]	@ D.53492, <variable>.PERI_CRG30.u32
	orr	r2, r1, #131072	@ u32TmpValue, D.53492,
	str	r2, [r0, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L224:
	mul	lr, r9, r8	@ tmp204, picHeightInMb, picWidthInMb
	mov	ip, lr, asl #1	@ tmp205, tmp204,
	mul	r1, r6, ip	@ tmp206, s32FrameRate, tmp205
	ubfx	r3, r1, #1, #26	@ tmp209, tmp206,,
	b	.L231	@
.L215:
	ldr	lr, [fp, #-68]	@, %sfp
	ldr	ip, [lr, r4, asl #2]	@ D.53477, s_pstVfmwChan
	ldr	r1, [ip, #1472]	@ <variable>.stSynExtraData.heightInMB, <variable>.stSynExtraData.heightInMB
	ldr	r0, [ip, #1468]	@ <variable>.stSynExtraData.widthInMB, <variable>.stSynExtraData.widthInMB
	mul	r3, r1, r0	@ tmp255, <variable>.stSynExtraData.heightInMB, <variable>.stSynExtraData.widthInMB
	mov	r2, r3, asl #5	@ tmp258, tmp255,
	mul	r8, r6, r2	@ tmp259, s32FrameRate, tmp258
	mov	r3, r8, lsr #6	@ tmp261, tmp259,
	b	.L231	@
	.fnend
	.size	VDMHAL_V300R001_SetVdhClkSkip, .-VDMHAL_V300R001_SetVdhClkSkip
	.align	2
	.global	VDMHAL_V300R001_StartHwDecode
	.type	VDMHAL_V300R001_StartHwDecode, %function
VDMHAL_V300R001_StartHwDecode:
	.fnstart
.LFB1553:
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
	mov	r6, r0, asl #3	@ tmp234, VdhId,
	rsb	r7, r0, r6	@ tmp156, VdhId, tmp234
	movw	r5, #:lower16:g_VdmDrvParam	@ tmp233,
	add	r1, r7, #1	@ tmp157, tmp156,
	movt	r5, #:upper16:g_VdmDrvParam	@ tmp233,
	movw	r8, #:lower16:s_pstVfmwChan	@ tmp235,
	movt	r8, #:upper16:s_pstVfmwChan	@ tmp235,
	ldr	r2, [r5, r1, asl #3]	@ <variable>.ChanId, <variable>.ChanId
	add	sl, r5, r1, asl #3	@, tmp160, tmp233, tmp157,
	movw	r7, #:lower16:g_pstRegCrg	@ tmp232,
	movt	r7, #:upper16:g_pstRegCrg	@ tmp232,
	ldr	r9, [sl, #4]	@ VidStd, <variable>.VidStd
	mov	r4, r0	@ VdhId, VdhId
	ldr	r3, [r8, r2, asl #2]	@ tmp169, s_pstVfmwChan
	ldr	r1, [r7, #0]	@ g_pstRegCrg.553, g_pstRegCrg
	ldr	r3, [r3, #592]	@ eCapLevel, <variable>.stSynExtraData.eCapLevel
	ldr	r2, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	cmp	r3, #9	@ eCapLevel,
	movls	ip, #0	@,
	movhi	ip, #1	@,
	cmp	r9, #0	@ VidStd,
	movne	ip, #0	@,,
	cmp	ip, #0	@ tmp177,
	beq	.L235	@,
	cmp	r3, #23	@ eCapLevel,
	orrls	r2, r2, #768	@ u32TmpValue, u32TmpValue,
	bhi	.L235	@,
.L236:
	movw	lr, #:lower16:arm_delay_ops	@ tmp179,
	movt	lr, #:upper16:arm_delay_ops	@ tmp179,
	str	r2, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	rsb	r9, r4, r6	@ tmp185, VdhId, tmp234
	ldr	r3, [lr, #4]	@ arm_delay_ops.const_udelay, arm_delay_ops.const_udelay
	movw	r0, #:lower16:32212230	@,
	movt	r0, #:upper16:32212230	@,
	movw	sl, #:lower16:s_pstVfmwChan	@ tmp187,
	blx	r3	@ arm_delay_ops.const_udelay
	add	ip, r9, #1	@ tmp186, tmp185,
	movt	sl, #:upper16:s_pstVfmwChan	@ tmp187,
	ldr	r9, [r5, ip, asl #3]	@ s32ChanId.1116, <variable>.ChanId
	ldr	r3, [r8, r9, asl #2]	@ prephitmp.1105, s_pstVfmwChan
	ldr	r0, [r3, #1264]	@ <variable>.stSynExtraData.s32ModuleLowlyEnable, <variable>.stSynExtraData.s32ModuleLowlyEnable
	cmp	r0, #0	@ <variable>.stSynExtraData.s32ModuleLowlyEnable,
	bne	.L237	@,
	ldr	ip, [r3, #1252]	@ <variable>.stSynExtraData.s32FastForwardBackwardSpeed, <variable>.stSynExtraData.s32FastForwardBackwardSpeed
	movw	r1, #4094	@ tmp192,
	add	r0, ip, #2032	@ tmp189, <variable>.stSynExtraData.s32FastForwardBackwardSpeed,
	add	r2, r0, #15	@ tmp189, tmp189,
	cmp	r2, r1	@ tmp189, tmp192
	bls	.L249	@,
.L238:
	ldr	r1, [r3, #552]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r1, #16	@ <variable>.eVidStd,
	movne	r1, #3	@ ClockGatingData,
	moveq	r1, #0	@ ClockGatingData,
	cmp	r4, #0	@ VdhId,
	bne	.L250	@,
.L242:
	movw	lr, #:lower16:s_RegPhyBaseAddr	@ tmp199,
	movt	lr, #:upper16:s_RegPhyBaseAddr	@ tmp199,
	ldr	ip, [lr, #0]	@ s_RegPhyBaseAddr,
	add	r0, ip, #12	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
.L244:
#APP
@ 2819 "/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal.c" 1
	dsb
@ 0 "" 2
	cmp	r4, #0	@ VdhId,
	bgt	.L251	@,
.L245:
	movw	r1, #1208	@ tmp212,
	movw	r2, #:lower16:g_HwMem	@ tmp210,
	mul	r0, r1, r4	@ tmp211, tmp212, VdhId
	movt	r2, #:upper16:g_HwMem	@ tmp210,
	rsb	r4, r4, r6	@ tmp228, VdhId, tmp234
	mov	ip, #0	@ tmp214,
	add	r4, r4, #1	@ tmp229, tmp228,
	movw	r3, #:lower16:g_LowDelaySeqIndex	@ tmp230,
	movt	r3, #:upper16:g_LowDelaySeqIndex	@ tmp230,
	mov	r1, #4	@,
	ldr	r6, [r0, r2]	@ D.53546, <variable>.pVdmRegVirAddr
	str	ip, [r6, #0]	@ tmp214,* D.53546
	mov	r6, #1	@ tmp219,
	ldr	lr, [r0, r2]	@ temp.1122, <variable>.pVdmRegVirAddr
	str	r6, [lr, #0]	@ tmp219,* temp.1122
	ldr	lr, [r0, r2]	@ temp.1124, <variable>.pVdmRegVirAddr
	str	ip, [lr, #0]	@ tmp214,* temp.1124
	ldr	r0, [r5, r4, asl #3]	@ D.53555, <variable>.ChanId
	ldr	r2, [r3, r0, asl #2]	@, g_LowDelaySeqIndex
	bl	VDEC_Lowdelay_Event_Time	@
.L247:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L235:
	bfc	r2, #8, #2	@ u32TmpValue,,
	b	.L236	@
.L237:
	ldr	r2, [r7, #0]	@ g_pstRegCrg.1117, g_pstRegCrg
	ldr	r0, [r2, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	bfc	r0, #12, #5	@ u32TmpValue,,
	bfc	r0, #17, #1	@ u32TmpValue,,
	str	r0, [r2, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r3, [r7, #0]	@ g_pstRegCrg.1119, g_pstRegCrg
	ldr	r1, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	orr	lr, r1, #131072	@ u32TmpValue, u32TmpValue,
	str	lr, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r3, [sl, r9, asl #2]	@ prephitmp.1105, s_pstVfmwChan
	ldr	r1, [r3, #552]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r1, #16	@ <variable>.eVidStd,
	movne	r1, #3	@ ClockGatingData,
	moveq	r1, #0	@ ClockGatingData,
	cmp	r4, #0	@ VdhId,
	beq	.L242	@,
.L250:
	cmp	r4, #1	@ VdhId,
	beq	.L252	@,
	movw	r1, #:lower16:.LC14	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC14	@,
	bl	dprint_vfmw	@
#APP
@ 2819 "/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal.c" 1
	dsb
@ 0 "" 2
	cmp	r4, #0	@ VdhId,
	ble	.L245	@,
.L251:
	mov	ip, #0	@ tmp209,
	mov	r3, r4	@, VdhId
	mov	r0, ip	@, tmp209
	movw	r1, #:lower16:.LC15	@,
	ldr	r2, .L253	@,
	movt	r1, #:upper16:.LC15	@,
	str	ip, [sp, #0]	@ tmp209,
	bl	dprint_vfmw	@
	b	.L247	@
.L252:
	movw	r3, #:lower16:s_RegPhyBaseAddr_1	@ tmp202,
	movt	r3, #:upper16:s_RegPhyBaseAddr_1	@ tmp202,
	ldr	r2, [r3, #0]	@ s_RegPhyBaseAddr_1,
	add	r0, r2, #12	@, s_RegPhyBaseAddr_1,
	bl	MEM_WritePhyWord	@
	b	.L244	@
.L249:
	mov	r0, r4	@, VdhId
	bl	VDMHAL_V300R001_SetVdhClkSkip	@
	ldr	r3, [sl, r9, asl #2]	@ prephitmp.1105, s_pstVfmwChan
	b	.L238	@
.L254:
	.align	2
.L253:
	.word	.LANCHOR0+88
	.fnend
	.size	VDMHAL_V300R001_StartHwDecode, .-VDMHAL_V300R001_StartHwDecode
	.align	2
	.global	VDMHAL_V300R001_StartHwRepair
	.type	VDMHAL_V300R001_StartHwRepair, %function
VDMHAL_V300R001_StartHwRepair:
	.fnstart
.LFB1551:
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
	subs	r4, r0, #0	@ VdhId, VdhId
	ble	.L261	@,
	mov	r3, r4	@, VdhId
	ldr	r2, .L263	@,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movt	r1, #:upper16:.LC1	@,
	mov	r5, #1	@ tmp163,
	str	r5, [sp, #0]	@ tmp163,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:-121389052	@,
	movt	r0, #:upper16:-121389052	@,
	bl	MEM_ReadPhyWord	@
	movw	r2, #:lower16:s_RegPhyBaseAddr	@ tmp165,
	movt	r2, #:upper16:s_RegPhyBaseAddr	@ tmp165,
	ldr	r3, [r2, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	uxth	r1, r0	@ tmp168,
	add	r0, r3, #4	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	ldr	r2, .L263	@,
	mov	r3, r4	@, VdhId
	movw	r1, #:lower16:.LC16	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC16	@,
	str	r5, [sp, #0]	@ tmp163,
	bl	dprint_vfmw	@
#APP
@ 2573 "/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal.c" 1
	dsb
@ 0 "" 2
	cmp	r4, #0	@ VdhId,
	ble	.L262	@,
.L258:
	ldr	r2, .L263	@,
	mov	r3, r4	@, VdhId
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC16	@,
	movt	r1, #:upper16:.LC16	@,
	mov	r5, #1	@ tmp191,
	str	r5, [sp, #0]	@ tmp191,
	bl	dprint_vfmw	@
	ldr	r2, .L263	@,
	mov	r3, r4	@, VdhId
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC16	@,
	movt	r1, #:upper16:.LC16	@,
	str	r5, [sp, #0]	@ tmp191,
	bl	dprint_vfmw	@
	movw	r1, #:lower16:.LC16	@,
	mov	r3, r4	@, VdhId
	movt	r1, #:upper16:.LC16	@,
	mov	r0, #32	@,
	ldr	r2, .L263	@,
	str	r5, [sp, #0]	@ tmp191,
	bl	dprint_vfmw	@
.L260:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L261:
	movw	r6, #1208	@ tmp146,
	movw	r5, #:lower16:g_HwMem	@ tmp144,
	mul	r6, r6, r4	@ tmp145, tmp146, VdhId
	movt	r5, #:upper16:g_HwMem	@ tmp144,
	movw	r0, #:lower16:-121389052	@,
	movt	r0, #:upper16:-121389052	@,
	ldr	ip, [r6, r5]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	ldr	r7, [ip, #8]	@ dat,
	bl	MEM_ReadPhyWord	@
	movw	r1, #:lower16:s_RegPhyBaseAddr	@ tmp150,
	movt	r1, #:upper16:s_RegPhyBaseAddr	@ tmp150,
	orr	r7, r7, #67108864	@ dat.1148, dat,
	ldr	r2, [r1, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	uxth	r1, r0	@ tmp153,
	add	r0, r2, #4	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	ldr	r3, [r6, r5]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r7, [r3, #8]	@ dat.1148,
#APP
@ 2573 "/home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal.c" 1
	dsb
@ 0 "" 2
	cmp	r4, #0	@ VdhId,
	bgt	.L258	@,
.L262:
	movw	lr, #1208	@ tmp176,
	movw	ip, #:lower16:g_HwMem	@ tmp174,
	mul	r4, lr, r4	@ tmp175, tmp176, VdhId
	movt	ip, #:upper16:g_HwMem	@ tmp174,
	mov	lr, #0	@ tmp178,
	mov	r3, #1	@ tmp183,
	ldr	r2, [r4, ip]	@ D.53406, <variable>.pVdmRegVirAddr
	str	lr, [r2, #0]	@ tmp178,* D.53406
	ldr	r1, [r4, ip]	@ temp.1157, <variable>.pVdmRegVirAddr
	str	r3, [r1, #0]	@ tmp183,* temp.1157
	ldr	r0, [r4, ip]	@ temp.1159, <variable>.pVdmRegVirAddr
	str	lr, [r0, #0]	@ tmp178,* temp.1159
	b	.L260	@
.L264:
	.align	2
.L263:
	.word	.LANCHOR0+120
	.fnend
	.size	VDMHAL_V300R001_StartHwRepair, .-VDMHAL_V300R001_StartHwRepair
	.align	2
	.global	VDMHAL_V300R001_CfgRpReg
	.type	VDMHAL_V300R001_CfgRpReg, %function
VDMHAL_V300R001_CfgRpReg:
	.fnstart
.LFB1548:
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
	cmp	r3, #1	@ VdhId,
	mov	ip, #0	@ tmp152,
	str	ip, [fp, #-24]	@ tmp152, D32
	bls	.L273	@,
	mov	r0, ip	@, tmp152
	movw	r1, #:lower16:.LC17	@,
	movt	r1, #:upper16:.LC17	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53124,
.L268:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L273:
	beq	.L274	@,
	ldr	r3, [r1, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	cmp	r3, #0	@ <variable>.pVdmRegVirAddr,
	beq	.L275	@,
.L270:
	movw	r3, #:lower16:g_HwMem	@ tmp166,
	movt	r3, #:upper16:g_HwMem	@ tmp166,
	ldr	r2, [r1, #40]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	movw	r1, #:lower16:536920579	@ tmp172,
	ldr	r0, [r3, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movt	r1, #:upper16:536920579	@ tmp172,
	bic	r4, r2, #15	@ tmp165, <variable>.MsgSlotAddr,
	movw	r2, #:lower16:3148803	@ tmp176,
	movt	r2, #:upper16:3148803	@ tmp176,
	str	r4, [r0, #16]	@ tmp165,
	mov	r4, #7	@ tmp168,
	ldr	ip, [r3, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r0, #0	@ D.53124,
	str	r4, [ip, #36]	@ tmp168,
	ldr	ip, [r3, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r1, [ip, #12]	@ tmp172,
	ldr	r1, [r3, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r2, [r1, #60]	@ tmp176,
	ldr	ip, [r3, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r2, [ip, #64]	@ tmp176,
	ldr	r1, [r3, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r2, [r1, #68]	@ tmp176,
	ldr	ip, [r3, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r2, [ip, #72]	@ tmp176,
	ldr	r1, [r3, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r2, [r1, #76]	@ tmp176,
	ldr	ip, [r3, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r2, [ip, #80]	@ tmp176,
	ldr	r1, [r3, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r2, [r1, #84]	@ tmp176,
	b	.L268	@
.L275:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	str	r1, [fp, #-32]	@,
	bl	MEM_Phy2Vir	@
	ldr	r1, [fp, #-32]	@,
	subs	r2, r0, #0	@ D.53131,
	strne	r2, [r1, #0]	@ D.53131, <variable>.pVdmRegVirAddr
	bne	.L270	@,
	movw	r1, #:lower16:.LC18	@,
	movt	r1, #:upper16:.LC18	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53124,
	b	.L268	@
.L274:
	mov	r0, ip	@, tmp152
	movw	r1, #:lower16:.LC15	@,
	ldr	r2, .L276	@,
	movt	r1, #:upper16:.LC15	@,
	str	ip, [sp, #0]	@ tmp152,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53124,
	b	.L268	@
.L277:
	.align	2
.L276:
	.word	.LANCHOR0+152
	.fnend
	.size	VDMHAL_V300R001_CfgRpReg, .-VDMHAL_V300R001_CfgRpReg
	.global	__aeabi_uidiv
	.global	__aeabi_idivmod
	.align	2
	.global	VDMHAL_V300R001_CfgRpMsg
	.type	VDMHAL_V300R001_CfgRpMsg, %function
VDMHAL_V300R001_CfgRpMsg:
	.fnstart
.LFB1547:
	@ args = 0, pretend = 0, frame = 40
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
	mov	r9, r0	@ pRepairParam, pRepairParam
	ldr	r0, [r1, #40]	@, <variable>.MsgSlotAddr
	bl	MEM_Phy2Vir	@
	subs	r1, r0, #0	@,
	str	r1, [fp, #-68]	@, %sfp
	beq	.L320	@,
	ldr	r2, [r9, #840]	@ D.52956, <variable>.ValidGroupNum
	sub	r3, r2, #1	@ tmp238, D.52956,
	cmp	r3, #199	@ tmp238,
	bhi	.L321	@,
	ldr	r1, [r9, #24]	@ <variable>.ImageWidth, <variable>.ImageWidth
	ldr	r2, [r9, #864]	@ D.52964, <variable>.CtbSize
	ldr	r0, [r9, #28]	@ <variable>.ImageHeight, <variable>.ImageHeight
	mov	r3, r1, asl r2	@ pic_width, <variable>.ImageWidth,
	ldr	lr, [r9, #0]	@ <variable>.VidStd, <variable>.VidStd
	add	ip, r3, #255	@ tmp242, pic_width,
	cmp	lr, #16	@ <variable>.VidStd,
	bic	r1, ip, #255	@ SlotWidth, tmp242,
	mov	r2, r0, asl r2	@ pic_height, <variable>.ImageHeight,
	moveq	r3, #0	@ prephitmp.1237,
	muleq	r2, r2, r1	@ ChromaOffset, pic_height, SlotWidth
	beq	.L283	@,
	adds	ip, r2, #31	@ tmp244, pic_height,
	addmi	r2, r2, #62	@, tmp245, pic_height,
	movpl	r2, ip	@, tmp245, tmp244
	adds	r0, r3, #127	@ tmp249, pic_width,
	addmi	lr, r3, #254	@, tmp251, pic_width,
	movpl	lr, r0	@, tmp251, tmp249
	mov	r2, r2, asr #5	@ tmp247, tmp245,
	mov	r3, lr, asr #7	@ tmp253, tmp251,
	adds	ip, r3, #15	@ tmp254, tmp253,
	mov	r0, r2, asl #9	@ tmp248, tmp247,
	addmi	lr, r3, #30	@, tmp256, tmp253,
	movpl	lr, ip	@, tmp256, tmp254
	mul	r2, r2, r1	@ tmp259, tmp247, SlotWidth
	mov	r3, lr, asr #4	@ tmp258, tmp256,
	mul	r3, r3, r0	@ HeadInfOffset, tmp258, tmp248
	add	r2, r3, r2, asl #5	@, ChromaOffset, HeadInfOffset, tmp259,
.L283:
	ldr	r0, [r9, #16]	@ <variable>.RefImageAddr, <variable>.RefImageAddr
	mov	ip, r1, asl #4	@ tmp277, SlotWidth,
	ldr	lr, [fp, #-68]	@, %sfp
	str	r0, [lr, #0]	@ <variable>.RefImageAddr,
	ldr	r0, [r9, #16]	@ <variable>.RefImageAddr, <variable>.RefImageAddr
	add	r0, r2, r0	@ tmp267, ChromaOffset, <variable>.RefImageAddr
	str	r0, [lr, #4]	@ tmp267,
	ldr	r0, [r9, #4]	@ <variable>.ImageAddr, <variable>.ImageAddr
	str	r0, [lr, #8]	@ <variable>.ImageAddr,
	ldr	r0, [r9, #4]	@ <variable>.ImageAddr, <variable>.ImageAddr
	add	r2, r2, r0	@ tmp274, ChromaOffset, <variable>.ImageAddr
	str	r2, [lr, #12]	@ tmp274,
	str	ip, [lr, #16]	@ tmp277,
	str	r3, [lr, #20]	@ prephitmp.1237,
	ldr	r1, [r9, #24]	@ <variable>.ImageWidth, <variable>.ImageWidth
	ldr	ip, [r9, #28]	@ <variable>.ImageHeight, <variable>.ImageHeight
	sub	r0, r1, #1	@ tmp283, <variable>.ImageWidth,
	sub	r2, ip, #1	@ tmp287, <variable>.ImageHeight,
	mov	r3, r0, asl #23	@ tmp288, tmp283,
	mov	r1, r3, lsr #23	@ tmp288, tmp288,
	bfi	r1, r2, #16, #9	@ tmp288, tmp287,,
	str	r1, [fp, #-48]	@ tmp288,
	str	r1, [lr, #24]	@ tmp288,
	ldr	r3, [r9, #864]	@ temp.1291, <variable>.CtbSize
	cmp	r3, #6	@ temp.1291,
	moveq	r4, #2	@ align_mb,
	beq	.L285	@,
	cmp	r3, #5	@ temp.1291,
	moveq	r4, #4	@ align_mb,
	beq	.L285	@,
	cmp	r3, #4	@ temp.1291,
	moveq	r4, #8	@ align_mb,
	beq	.L285	@,
	movw	r1, #:lower16:.LC21	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC21	@,
	mov	r4, #1	@ align_mb,
	bl	dprint_vfmw	@
.L285:
	ldr	r3, [r9, #856]	@ prephitmp.1241, <variable>.FullRepair
	cmp	r3, #0	@ prephitmp.1241,
	movne	r5, #0	@ actual_repairTime,
	bne	.L289	@,
	ldr	lr, [r9, #840]	@, <variable>.ValidGroupNum
	cmp	lr, #0	@,
	str	lr, [fp, #-56]	@, %sfp
	movle	r5, r3	@ actual_repairTime, prephitmp.1241
	ble	.L291	@,
	sub	r5, r4, #1	@, align_mb,
	str	r3, [fp, #-60]	@ prephitmp.1241, %sfp
	str	r5, [fp, #-76]	@, %sfp
	mov	r6, r3	@ i, prephitmp.1241
	b	.L305	@
.L323:
	add	r3, r9, r6, asl #2	@, tmp310, pRepairParam, i,
	mov	r1, r4	@, align_mb
	ldrsh	lr, [r3, #38]	@ <variable>.EndMbn, <variable>.EndMbn
	sub	r0, lr, #1	@ tmp313, <variable>.EndMbn,
	add	r0, r0, r4	@, tmp313, align_mb
	bl	__aeabi_uidiv	@
	mul	r1, r4, r0	@ tmp319, align_mb,
	cmp	r5, r1	@ cur_EndMb, tmp319
	ldrle	r5, [fp, #-60]	@ actual_repairTime, %sfp
	bgt	.L322	@,
	ldr	r0, [fp, #-56]	@, %sfp
	add	r6, r6, #1	@ i, i,
	cmp	r0, r6	@, i
	ble	.L304	@,
.L325:
	str	r5, [fp, #-60]	@ actual_repairTime, %sfp
.L305:
	add	sl, r6, #10	@ tmp426, i,
	mov	r1, r4	@, align_mb
	mov	r2, sl, asl #2	@ tmp291, tmp426,
	add	sl, r2, r9	@ tmp292, tmp291, pRepairParam
	ldrh	r8, [r2, r9]	@, <variable>.StartMbn
	str	r8, [fp, #-72]	@, %sfp
	ldrh	r8, [sl, #2]	@ prephitmp.1250, <variable>.EndMbn
	sxth	ip, r8	@, prephitmp.1250
	str	ip, [fp, #-64]	@, %sfp
	sub	r3, ip, #1	@ tmp299,,
	add	r0, r3, r4	@, tmp299, align_mb
	bl	__aeabi_uidiv	@
	cmp	r6, #0	@ i,
	mul	r5, r4, r0	@ cur_EndMb, align_mb,
	bne	.L323	@,
.L296:
	ldr	r3, [r9, #28]	@ <variable>.ImageHeight, <variable>.ImageHeight
	ldr	sl, [r9, #24]	@ <variable>.ImageWidth, <variable>.ImageWidth
	ldr	r0, [fp, #-60]	@, %sfp
	mul	sl, sl, r3	@ D.53062, <variable>.ImageWidth, <variable>.ImageHeight
	cmp	r5, sl	@ cur_EndMb, D.53062
	subge	sl, sl, #1	@ end_Mb, D.53062,
	movlt	sl, r5	@ end_Mb, cur_EndMb
	add	r5, r0, #1	@ actual_repairTime,,
	cmp	r5, #252	@ actual_repairTime,
	bgt	.L324	@,
	ldr	lr, [fp, #-72]	@, %sfp
	mov	r1, r4	@, align_mb
	mov	r8, #0	@,
	add	r6, r6, #1	@ i, i,
	sxth	r0, lr	@,
	bl	__aeabi_uidiv	@
	ldr	r1, [r9, #24]	@, <variable>.ImageWidth
	str	r8, [fp, #-48]	@, D32
	mul	r8, r4, r0	@ cur_StartMb, align_mb,
	mov	r0, r8	@, cur_StartMb
	bl	__aeabi_idivmod	@
	ldr	r7, [fp, #-48]	@ tmp371,
	mov	r0, r8	@, cur_StartMb
	bfi	r7, r1, #0, #9	@ tmp371,,,
	ldr	r1, [r9, #24]	@, <variable>.ImageWidth
	bl	__aeabi_idiv	@
	ldr	r3, [fp, #-60]	@, %sfp
	ldr	ip, [fp, #-68]	@, %sfp
	add	r2, r3, #4	@ tmp377,,
	bfi	r7, r0, #16, #9	@ tmp376,,,
	mov	r0, sl	@, end_Mb
	str	r7, [ip, r2, asl #3]	@ D32.1311,
	mov	r7, #0	@,
	ldr	r1, [r9, #24]	@, <variable>.ImageWidth
	str	r7, [fp, #-48]	@, D32
	bl	__aeabi_idivmod	@
	ldr	r7, [fp, #-48]	@ tmp386,
	mov	r0, sl	@, end_Mb
	bfi	r7, r1, #0, #9	@ tmp386,,,
	ldr	r1, [r9, #24]	@, <variable>.ImageWidth
	bl	__aeabi_idiv	@
	ldr	r1, [fp, #-60]	@, %sfp
	ldr	ip, [fp, #-68]	@, %sfp
	mov	r3, r1, asl #3	@ tmp392,,
	add	r2, r3, #36	@ tmp393, tmp392,
	bfi	r7, r0, #16, #9	@ tmp391,,,
	str	r7, [fp, #-48]	@ tmp391,
	str	r7, [ip, r2]	@ D32.1315,
	ldr	r1, [r9, #840]	@, <variable>.ValidGroupNum
	str	r1, [fp, #-56]	@, %sfp
	ldr	r0, [fp, #-56]	@, %sfp
	cmp	r0, r6	@, i
	bgt	.L325	@,
.L304:
	ldr	r3, [r9, #856]	@ prephitmp.1241, <variable>.FullRepair
.L289:
	cmp	r3, #1	@ prephitmp.1241,
	beq	.L303	@,
.L291:
	sub	r5, r5, #1	@ tmp395, actual_repairTime,
	uxth	r5, r5	@ prephitmp.1239, tmp395
.L306:
	ldr	lr, [r9, #848]	@ <variable>.Compress_en, <variable>.Compress_en
	mov	r0, #0	@ D.52955,
	ldrb	r3, [fp, #-46]	@ zero_extendqisi2	@,
	ldr	r2, [r9, #852]	@ <variable>.Pic_type, <variable>.Pic_type
	bfi	r3, lr, #0, #1	@ tmp410, <variable>.Compress_en,,
	strb	r3, [fp, #-46]	@ tmp410,
	ldr	ip, [r9, #864]	@ <variable>.CtbSize, <variable>.CtbSize
	ldrb	r1, [fp, #-45]	@ zero_extendqisi2	@,
	uxtb	lr, r3	@ tmp413, tmp410
	bfi	lr, r2, #4, #2	@ tmp413, <variable>.Pic_type,,
	sub	ip, ip, #4	@ tmp420, <variable>.CtbSize,
	strh	r5, [fp, #-48]	@ movhi	@ prephitmp.1239, <variable>.total_grp_num_minus1
	bfi	lr, r2, #6, #2	@ tmp416, <variable>.Pic_type,,
	bfi	r1, ip, #0, #2	@ tmp421, tmp420,,
	strb	lr, [fp, #-46]	@ tmp416,
	strb	r1, [fp, #-45]	@ tmp421,
	ldr	r3, [fp, #-48]	@ D32.1335, D32
	ldr	lr, [fp, #-68]	@, %sfp
	str	r3, [lr, #28]	@ D32.1335,
.L280:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L322:
	ldr	ip, [fp, #-56]	@, %sfp
	mvn	r5, r6	@ tmp434, i
	add	r7, r5, ip	@ tmp433, tmp434,
	tst	r7, #1	@ tmp433,
	mov	r7, sl	@ ivtmp.1268, tmp292
	bne	.L326	@,
	str	r9, [fp, #-64]	@ pRepairParam, %sfp
	ldr	r9, [fp, #-76]	@ tmp431, %sfp
	b	.L297	@
.L298:
	bl	__aeabi_uidiv	@
	mov	r1, r4	@, align_mb
	mul	r5, r4, r0	@ temp.1297, align_mb,
	ldrsh	r0, [r7, #4]	@, <variable>.StartMbn
	bl	__aeabi_uidiv	@
	mul	r1, r4, r0	@ D.53058, align_mb,
	cmp	r5, r1	@ temp.1297, D.53058
	add	r3, r1, #1	@ tmp347, D.53058,
	bhi	.L299	@,
	cmp	r5, r3	@ temp.1297, tmp347
	mov	r1, r4	@, align_mb
	beq	.L299	@,
	ldrsh	lr, [r7, #-2]	@ <variable>.EndMbn, <variable>.EndMbn
	sub	r2, lr, #1	@ tmp349, <variable>.EndMbn,
	add	r0, r2, r4	@, tmp349, align_mb
	bl	__aeabi_uidiv	@
	mul	ip, r4, r0	@ tmp355, align_mb,
	cmp	r5, ip	@ temp.1297, tmp355
	bhi	.L319	@,
.L299:
	ldrsh	r2, [r7, #6]	@ prephitmp.1250, <variable>.EndMbn
	mov	r1, r4	@, align_mb
	mov	r6, sl	@ i, i.1292
	add	r0, r9, r2	@, tmp431, prephitmp.1250
	bl	__aeabi_uidiv	@
	mov	r1, r4	@, align_mb
	mul	r5, r4, r0	@ temp.1297, align_mb,
	ldrsh	r0, [r8, #4]	@, <variable>.StartMbn
	bl	__aeabi_uidiv	@
	mul	r0, r4, r0	@ D.53058, align_mb,
	cmp	r5, r0	@ temp.1297, D.53058
	bhi	.L313	@,
	add	r2, r0, #1	@ tmp462, D.53058,
	mov	r1, r4	@, align_mb
	cmp	r5, r2	@ temp.1297, tmp462
	beq	.L313	@,
	ldrsh	ip, [r8, #-2]	@ <variable>.EndMbn, <variable>.EndMbn
	sub	r0, ip, #1	@ tmp464, <variable>.EndMbn,
	add	r0, r0, r4	@, tmp464, align_mb
	bl	__aeabi_uidiv	@
	mul	r1, r4, r0	@ tmp467, align_mb,
	cmp	r5, r1	@ temp.1297, tmp467
	bhi	.L319	@,
.L313:
	add	r7, r8, #4	@ ivtmp.1268, tmp436,
	ldrh	r8, [r8, #6]	@ prephitmp.1250, <variable>.EndMbn
	add	r6, sl, #1	@ i, i.1292,
.L297:
	ldr	lr, [fp, #-56]	@, %sfp
	add	sl, r6, #1	@ i.1292, i,
	sxtah	r0, r9, r8	@, tmp431, prephitmp.1250
	mov	r1, r4	@, align_mb
	cmp	sl, lr	@ i.1292,
	add	r8, r7, #4	@ tmp436, ivtmp.1268,
	blt	.L298	@,
	ldr	r9, [fp, #-64]	@ pRepairParam, %sfp
.L316:
	add	r3, r9, r6, asl #2	@, tmp330, pRepairParam, i,
	mov	r1, r4	@, align_mb
	ldrsh	r0, [r3, #42]	@ pretmp.1281, <variable>.EndMbn
	sub	sl, r0, #1	@ pretmp.1287, pretmp.1281,
	add	r0, sl, r4	@, pretmp.1287, align_mb
	bl	__aeabi_uidiv	@
	mul	r5, r4, r0	@ cur_EndMb, align_mb,
	b	.L296	@
.L326:
	ldr	r5, [fp, #-56]	@, %sfp
	add	r3, r6, #1	@ i.1292, i,
	cmp	r3, r5	@ i.1292,
	bge	.L316	@,
	ldr	r2, [fp, #-64]	@, %sfp
	ldr	r1, [fp, #-76]	@, %sfp
	str	r3, [fp, #-80]	@,
	add	r0, r1, r2	@,,
	mov	r1, r4	@, align_mb
	bl	__aeabi_uidiv	@
	mov	r1, r4	@, align_mb
	mul	r5, r4, r0	@ temp.1297, align_mb,
	ldrsh	r0, [sl, #4]	@, <variable>.StartMbn
	bl	__aeabi_uidiv	@
	ldr	r3, [fp, #-80]	@,
	mul	r0, r4, r0	@ D.53058, align_mb,
	cmp	r5, r0	@ temp.1297, D.53058
	bhi	.L310	@,
	add	r0, r0, #1	@ tmp456, D.53058,
	cmp	r5, r0	@ temp.1297, tmp456
	beq	.L310	@,
	ldrsh	lr, [sl, #-2]	@ <variable>.EndMbn, <variable>.EndMbn
	mov	r1, r4	@, align_mb
	sub	r3, lr, #1	@ tmp458, <variable>.EndMbn,
	add	r0, r3, r4	@, tmp458, align_mb
	bl	__aeabi_uidiv	@
	ldr	r3, [fp, #-80]	@,
	mul	ip, r4, r0	@ tmp461, align_mb,
	cmp	r5, ip	@ temp.1297, tmp461
	bhi	.L296	@,
.L310:
	ldrh	r8, [sl, #6]	@ prephitmp.1250, <variable>.EndMbn
	add	r7, r7, #4	@ ivtmp.1268, ivtmp.1268,
	str	r9, [fp, #-64]	@ pRepairParam, %sfp
	mov	r6, r3	@ i, i.1292
	ldr	r9, [fp, #-76]	@ tmp431, %sfp
	b	.L297	@
.L319:
	ldr	r9, [fp, #-64]	@ pRepairParam, %sfp
	b	.L296	@
.L324:
	mov	r5, #1	@ tmp358,
	str	r5, [r9, #856]	@ tmp358, <variable>.FullRepair
.L303:
	mov	ip, #1	@ tmp396,
	str	ip, [r9, #840]	@ tmp396, <variable>.ValidGroupNum
	ldr	ip, [fp, #-68]	@, %sfp
	mov	r5, #0	@ tmp397,
	mov	r2, r5	@ tmp399, tmp397
	bfi	r2, r5, #16, #9	@ tmp399, tmp397,,
	str	r2, [ip, #32]	@ tmp399,
	ldr	r1, [r9, #24]	@ <variable>.ImageWidth, <variable>.ImageWidth
	ldr	r0, [r9, #28]	@ <variable>.ImageHeight, <variable>.ImageHeight
	sub	lr, r1, #1	@ tmp403, <variable>.ImageWidth,
	sub	r2, r0, #1	@ tmp407, <variable>.ImageHeight,
	mov	r3, lr, asl #23	@ tmp408, tmp403,
	mov	r1, r3, lsr #23	@ tmp408, tmp408,
	bfi	r1, r2, #16, #9	@ tmp408, tmp407,,
	str	r1, [fp, #-48]	@ tmp408,
	str	r1, [ip, #36]	@ tmp408,
	b	.L306	@
.L321:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC20	@,
	movt	r1, #:upper16:.LC20	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52955,
	b	.L280	@
.L320:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L327	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC19	@,
	movt	r3, #:upper16:.LC19	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52955,
	b	.L280	@
.L328:
	.align	2
.L327:
	.word	.LANCHOR0+180
	.fnend
	.size	VDMHAL_V300R001_CfgRpMsg, .-VDMHAL_V300R001_CfgRpMsg
	.align	2
	.global	VDMHAL_V300R001_PrepareRepair
	.type	VDMHAL_V300R001_PrepareRepair, %function
VDMHAL_V300R001_PrepareRepair:
	.fnstart
.LFB1550:
	@ args = 0, pretend = 0, frame = 8
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
	cmp	r3, #1	@ VdhId,
	mov	r4, r0	@ VidStd, VidStd
	mov	r5, r1	@ pDecParam, pDecParam
	bls	.L345	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC22	@,
	movt	r1, #:upper16:.LC22	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53336,
.L332:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L345:
	beq	.L347	@,
	movw	r6, #:lower16:g_HwMem	@ tmp151,
	movt	r6, #:upper16:g_HwMem	@ tmp151,
	ldr	r3, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	cmp	r3, #0	@ <variable>.pVdmRegVirAddr,
	beq	.L348	@,
.L334:
	cmp	r2, #0	@ RepairTime,
	movw	r3, #:lower16:g_RepairParam	@ g_RepairParam.538,
	movt	r3, #:upper16:g_RepairParam	@ g_RepairParam.538,
	bne	.L336	@,
	ldr	r0, [r3, #840]	@ <variable>.ValidGroupNum, <variable>.ValidGroupNum
	cmp	r0, #0	@ <variable>.ValidGroupNum,
	ble	.L337	@,
	cmp	r4, #6	@ VidStd,
	bne	.L338	@,
	ldrb	r2, [r5, #8]	@ zero_extendqisi2	@ <variable>.PicStruct, <variable>.PicStruct
	cmp	r2, #1	@ <variable>.PicStruct,
	movne	r2, #0	@, tmp176,
	str	r2, [r3, #1724]	@ tmp176, <variable>.Pic_type
.L338:
	mov	r2, r5	@, pDecParam
	mov	r0, r4	@, VidStd
	mov	r3, #0	@,
	movw	r1, #:lower16:g_HwMem	@,
	movt	r1, #:upper16:g_HwMem	@,
	bl	VDMHAL_V300R001_CfgRpReg	@
	movw	r0, #:lower16:g_RepairParam	@,
	movt	r0, #:upper16:g_RepairParam	@,
.L346:
	movw	r1, #:lower16:g_HwMem	@,
	mov	r2, #0	@,
	movt	r1, #:upper16:g_HwMem	@,
	bl	VDMHAL_V300R001_CfgRpMsg	@
	mov	r0, #0	@ D.53336,
	b	.L332	@
.L336:
	cmp	r2, #1	@ RepairTime,
	movne	r0, #0	@ D.53336,
	bne	.L332	@,
	cmp	r4, #6	@ VidStd,
	bne	.L341	@,
	ldrb	lr, [r5, #8]	@ zero_extendqisi2	@ <variable>.PicStruct, <variable>.PicStruct
	cmp	lr, #1	@ <variable>.PicStruct,
	bne	.L341	@,
	ldr	ip, [r3, #1712]	@ <variable>.ValidGroupNum, <variable>.ValidGroupNum
	cmp	ip, #0	@ <variable>.ValidGroupNum,
	ble	.L341	@,
	movw	r0, #:lower16:g_vdm_hal_fun_ptr	@ tmp169,
	movt	r0, #:upper16:g_vdm_hal_fun_ptr	@ tmp169,
	mov	r1, #2	@ tmp166,
	str	r1, [r3, #1724]	@ tmp166, <variable>.Pic_type
	ldr	r3, [r0, #56]	@ D.53375, g_vdm_hal_fun_ptr.pfun_VDMHAL_ResetVdm
	cmp	r3, #0	@ D.53375,
	beq	.L342	@,
	mov	r0, #0	@,
	blx	r3	@ D.53375
.L343:
	mov	r2, r5	@, pDecParam
	mov	r3, #0	@,
	mov	r0, #6	@,
	movw	r1, #:lower16:g_HwMem	@,
	movt	r1, #:upper16:g_HwMem	@,
	bl	VDMHAL_V300R001_CfgRpReg	@
	ldr	r0, .L349	@,
	b	.L346	@
.L348:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	str	r2, [fp, #-32]	@,
	bl	MEM_Phy2Vir	@
	ldr	r2, [fp, #-32]	@,
	subs	r1, r0, #0	@ D.53343,
	strne	r1, [r6, #0]	@ D.53343, <variable>.pVdmRegVirAddr
	bne	.L334	@,
	movw	r1, #:lower16:.LC23	@,
	movt	r1, #:upper16:.LC23	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53336,
	b	.L332	@
.L347:
	mov	ip, #0	@ tmp150,
	movw	r1, #:lower16:.LC15	@,
	mov	r0, ip	@, tmp150
	movt	r1, #:upper16:.LC15	@,
	ldr	r2, .L349+4	@,
	str	ip, [sp, #0]	@ tmp150,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53336,
	b	.L332	@
.L341:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC26	@,
	movt	r1, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53336,
	b	.L332	@
.L342:
	mov	r0, r3	@, D.53375
	movw	r1, #:lower16:.LC25	@,
	movw	r2, #2533	@,
	movt	r1, #:upper16:.LC25	@,
	bl	dprint_vfmw	@
	b	.L343	@
.L337:
	mov	r0, r2	@, RepairTime
	movw	r1, #:lower16:.LC24	@,
	movt	r1, #:upper16:.LC24	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53336,
	b	.L332	@
.L350:
	.align	2
.L349:
	.word	g_RepairParam+872
	.word	.LANCHOR0+208
	.fnend
	.size	VDMHAL_V300R001_PrepareRepair, .-VDMHAL_V300R001_PrepareRepair
	.align	2
	.global	VDMHAL_V300R001_BackupInfo
	.type	VDMHAL_V300R001_BackupInfo, %function
VDMHAL_V300R001_BackupInfo:
	.fnstart
.LFB1544:
	@ args = 0, pretend = 0, frame = 0
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
	subs	r2, r0, #0	@ pBackUpInfo, pBackUpInfo
	beq	.L373	@,
	ldr	r3, [r2, #4]	@ VdhId, <variable>.VdhId
	ldr	r8, [r2, #0]	@ pMb0QpInCurrPic, <variable>.pMb0QpInCurrPic
	cmp	r3, #1	@ VdhId,
	bls	.L372	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC28	@,
	movt	r1, #:upper16:.LC28	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52728,
.L353:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L372:
	cmp	r3, #0	@ VdhId,
	bne	.L374	@,
	movw	r3, #:lower16:g_DSPState	@ tmp277,
	movt	r3, #:upper16:g_DSPState	@ tmp277,
	ldr	r2, [r3, #0]	@ g_DSPState, g_DSPState
	cmp	r2, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r0, [r3, #4]	@ g_DSPState, g_DSPState
	cmp	r0, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r1, [r3, #8]	@ g_DSPState, g_DSPState
	cmp	r1, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r5, [r3, #12]	@ g_DSPState, g_DSPState
	cmp	r5, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r6, [r3, #16]	@ g_DSPState, g_DSPState
	cmp	r6, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	ip, [r3, #20]	@ g_DSPState, g_DSPState
	cmp	ip, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r2, [r3, #24]	@ g_DSPState, g_DSPState
	cmp	r2, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r0, [r3, #28]	@ g_DSPState, g_DSPState
	movw	r3, #:lower16:g_DSPState	@ tmp207,
	movt	r3, #:upper16:g_DSPState	@ tmp207,
	cmp	r0, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r1, [r3, #32]	@ g_DSPState, g_DSPState
	cmp	r1, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r5, [r3, #36]	@ g_DSPState, g_DSPState
	cmp	r5, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r6, [r3, #40]	@ g_DSPState, g_DSPState
	cmp	r6, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	ip, [r3, #44]	@ g_DSPState, g_DSPState
	cmp	ip, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r2, [r3, #48]	@ g_DSPState, g_DSPState
	cmp	r2, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r0, [r3, #52]	@ g_DSPState, g_DSPState
	cmp	r0, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r1, [r3, #56]	@ g_DSPState, g_DSPState
	cmp	r1, #1	@ g_DSPState,
	beq	.L357	@,
	ldr	r5, [r3, #60]	@ g_DSPState, g_DSPState
	cmp	r5, #1	@ g_DSPState,
	movne	r6, #0	@, LowdlyFlag
	moveq	r6, #1	@, LowdlyFlag
.L358:
	movw	r5, #:lower16:g_HwMem	@ tmp278,
	movt	r5, #:upper16:g_HwMem	@ tmp278,
	ldr	r3, [r5, #0]	@ p32, <variable>.pVdmRegVirAddr
	cmp	r3, #0	@ p32,
	beq	.L375	@,
.L359:
	ldr	r7, [r3, #12]	@ D.52753,
	movw	r4, #:lower16:g_BackUp	@ tmp276,
	movt	r4, #:upper16:g_BackUp	@ tmp276,
	cmp	r6, #1	@ LowdlyFlag,
	str	r7, [r4, #0]	@ D.52753, <variable>.BasicCfg1
	ldr	r7, [r3, #28]	@ D.52761,
	str	r7, [r4, #4]	@ D.52761, <variable>.VdmState
	beq	.L376	@,
	add	r2, r3, #4096	@ D.52791, D.52750,
	ldr	r0, [r2, #0]	@ D.52792,* D.52791
	str	r0, [r4, #16]	@ D.52792, <variable>.SedSta
	ldr	ip, [r2, #20]	@ D.52799,
	str	ip, [r4, #20]	@ D.52799, <variable>.SedEnd0
	ldr	r5, [r3, #208]	@ D.52806,
	str	r5, [r4, #8]	@ D.52806, <variable>.Mb0QpInCurrPic
	ldr	r1, [r3, #212]	@ D.52813,
	str	r1, [r4, #12]	@ D.52813, <variable>.SwitchRounding
	ldr	r7, [r3, #176]	@ D.52822,
	str	r7, [r4, #24]	@ D.52822, <variable>.DecCyclePerPic
	ldr	r0, [r3, #180]	@ D.52829,
	str	r0, [r4, #28]	@ D.52829, <variable>.RdBdwidthPerPic
	ldr	r2, [r3, #184]	@ D.52836,
	str	r2, [r4, #32]	@ D.52836, <variable>.WrBdWidthPerPic
	ldr	ip, [r3, #188]	@ D.52843,
	str	ip, [r4, #36]	@ D.52843, <variable>.RdReqPerPic
	ldr	r5, [r3, #192]	@ D.52850,
	str	r5, [r4, #40]	@ D.52850, <variable>.WrReqPerPic
.L365:
	add	r3, r3, #33024	@ tmp275, D.52750,
	movw	r2, #:lower16:g_BackUp	@ ivtmp.1413,
	movt	r2, #:upper16:g_BackUp	@ ivtmp.1413,
	add	r7, r2, #128	@ D.54725, ivtmp.1413,
	mov	r0, r3	@ ivtmp.1409, tmp275
.L366:
	mov	r1, r0	@ tmp279, ivtmp.1409
	add	ip, r2, #4	@ tmp280, ivtmp.1413,
	ldr	r5, [r1], #4	@ D.52859,
	str	r5, [r2, #52]	@ D.52859, <variable>.LumaHistorgam
	add	r2, ip, #4	@ ivtmp.1413, tmp280,
	ldr	r5, [r0, #4]	@ D.52859,
	cmp	r2, r7	@ ivtmp.1413, D.54725
	add	r0, r1, #4	@ ivtmp.1409, tmp279,
	str	r5, [ip, #52]	@ D.52859, <variable>.LumaHistorgam
	bne	.L366	@,
	cmp	r6, #0	@ LowdlyFlag,
	ldr	ip, [r4, #0]	@ <variable>.BasicCfg1, <variable>.BasicCfg1
	ldreq	r2, [r3, #128]	@ D.52868,
	streq	r2, [r4, #48]	@ D.52868, <variable>.LumaSumLow
	and	r2, ip, #15	@ tmp266, <variable>.BasicCfg1,
	ldreq	r3, [r3, #132]	@ D.52875,
	streq	r3, [r4, #44]	@ D.52875, <variable>.LumaSumHigh
	cmp	r2, #5	@ tmp266,
	movw	r3, #:lower16:g_BackUp	@ tmp265,
	movt	r3, #:upper16:g_BackUp	@ tmp265,
	moveq	r0, #0	@ D.52728,
	movne	r0, #0	@ D.52728,
	ldreq	r3, [r3, #12]	@ <variable>.SwitchRounding, <variable>.SwitchRounding
	ldrne	r3, [r3, #8]	@ <variable>.Mb0QpInCurrPic, <variable>.Mb0QpInCurrPic
	andeq	r3, r3, #1	@ tmp270, <variable>.SwitchRounding,
	andne	r3, r3, #31	@ tmp273, <variable>.Mb0QpInCurrPic,
	str	r3, [r8, #0]	@ tmp273,* pMb0QpInCurrPic
	b	.L353	@
.L357:
	mov	r6, #1	@ LowdlyFlag,
	b	.L358	@
.L376:
	ldr	r0, [r5, #32]	@, <variable>.MsgSlotAddr
	bl	MEM_Phy2Vir	@
	subs	r2, r0, #0	@ pMsgBase,
	beq	.L377	@,
	bic	r1, r7, #-16777216	@ DecSliceNum, D.52761,
	bic	r7, r1, #16646144	@ DecSliceNum, DecSliceNum,
	sub	r3, r7, #1	@ tmp240, DecSliceNum,
	cmp	r3, #199	@ tmp240,
	subls	r3, r7, #-1073741823	@ tmp241, DecSliceNum,
	movls	r1, r7, asl #4	@ tmp243, DecSliceNum,
	movhi	r3, #0	@ prephitmp.1389,
	subls	r1, r1, #8	@ prephitmp.1391, tmp243,
	movls	r3, r3, asl #4	@ prephitmp.1389, tmp241,
	movhi	r1, #8	@ prephitmp.1391,
	ldr	r0, [r2, r3]	@ tmp245,* prephitmp.1389
	ldr	r3, [r5, #0]	@ D.52750, <variable>.pVdmRegVirAddr
	str	r0, [r4, #16]	@ tmp245, <variable>.SedSta
	ldr	r2, [r2, r1]	@ tmp247,* prephitmp.1391
	str	r2, [r4, #20]	@ tmp247, <variable>.SedEnd0
	ldr	ip, [r3, #208]	@ temp.1420,
	str	ip, [r4, #8]	@ temp.1420, <variable>.Mb0QpInCurrPic
	ldr	lr, [r3, #212]	@ temp.1422,
	str	lr, [r4, #12]	@ temp.1422, <variable>.SwitchRounding
	b	.L365	@
.L375:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r3, r0, #0	@ p32,
	strne	r3, [r5, #0]	@ p32, <variable>.pVdmRegVirAddr
	bne	.L359	@,
	movw	r1, #:lower16:.LC18	@,
	movt	r1, #:upper16:.LC18	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52728,
	b	.L353	@
.L374:
	mov	ip, #0	@ tmp192,
	movw	r1, #:lower16:.LC15	@,
	mov	r0, ip	@, tmp192
	movt	r1, #:upper16:.LC15	@,
	ldr	r2, .L378	@,
	str	ip, [sp, #0]	@ tmp192,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52728,
	b	.L353	@
.L373:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L378	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC27	@,
	movt	r3, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52728,
	b	.L353	@
.L377:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L378	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC29	@,
	movt	r3, #:upper16:.LC29	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52728,
	b	.L353	@
.L379:
	.align	2
.L378:
	.word	.LANCHOR0+240
	.fnend
	.size	VDMHAL_V300R001_BackupInfo, .-VDMHAL_V300R001_BackupInfo
	.align	2
	.global	VDMHAL_V300R001_CheckReg
	.type	VDMHAL_V300R001_CheckReg, %function
VDMHAL_V300R001_CheckReg:
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
	cmp	r1, #0	@ VdhId
	mov	r6, r0	@ reg_id, reg_id
	bgt	.L395	@,
	bne	.L396	@,
	movw	r5, #:lower16:g_HwMem	@ tmp161,
	movt	r5, #:upper16:g_HwMem	@ tmp161,
	ldr	r3, [r5, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	cmp	r3, #0	@ <variable>.pVdmRegVirAddr,
	beq	.L397	@,
.L385:
	sub	r0, r6, #1	@ tmp154, reg_id,
	cmp	r0, #3	@ tmp154,
	ldrls	pc, [pc, r0, asl #2]	@ tmp154
	b	.L387	@
.L392:
	.word	.L388
	.word	.L389
	.word	.L390
	.word	.L391
.L396:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC31	@,
	ldr	r2, .L398	@,
	movt	r1, #:upper16:.LC31	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ dat,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L387:
	mov	r3, r6	@, reg_id
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC33	@,
	ldr	r2, .L398	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ dat,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L388:
	ldr	r1, [r5, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r2, #28	@ reg_type,
	ldr	r0, [r2, r1]	@ dat,* <variable>.pVdmRegVirAddr
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L389:
	ldr	r1, [r5, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r2, #32	@ reg_type,
	ldr	r0, [r2, r1]	@ dat,* <variable>.pVdmRegVirAddr
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L390:
	ldr	r1, [r5, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r2, #36	@ reg_type,
	ldr	r0, [r2, r1]	@ dat,* <variable>.pVdmRegVirAddr
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L391:
	ldr	r1, [r5, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r2, #40	@ reg_type,
	ldr	r0, [r2, r1]	@ dat,* <variable>.pVdmRegVirAddr
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L397:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r4, r0, #0	@ D.52586,
	strne	r4, [r5, #0]	@ D.52586, <variable>.pVdmRegVirAddr
	bne	.L385	@,
	movw	r1, #:lower16:.LC32	@,
	ldr	r2, .L398	@,
	movt	r1, #:upper16:.LC32	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ dat, D.52586
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L395:
	mov	r3, r1	@, VdhId
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC30	@,
	ldr	r2, .L398	@,
	movt	r1, #:upper16:.LC30	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ dat,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L399:
	.align	2
.L398:
	.word	.LANCHOR0+268
	.fnend
	.size	VDMHAL_V300R001_CheckReg, .-VDMHAL_V300R001_CheckReg
	.align	2
	.global	VDMHAL_V300R001_EnableInt
	.type	VDMHAL_V300R001_EnableInt, %function
VDMHAL_V300R001_EnableInt:
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
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	rsb	r5, r0, r0, asl #3	@, tmp144, VdhId, VdhId,
	add	r1, r5, #1	@ tmp145, tmp144,
	movw	r2, #:lower16:g_VdmDrvParam	@ tmp141,
	movt	r2, #:upper16:g_VdmDrvParam	@ tmp141,
	movw	r3, #:lower16:s_pstVfmwChan	@ tmp140,
	movt	r3, #:upper16:s_pstVfmwChan	@ tmp140,
	ldr	r2, [r2, r1, asl #3]	@ <variable>.ChanId, <variable>.ChanId
	ldr	r5, [r3, r2, asl #2]	@ D.52529, s_pstVfmwChan
	cmp	r5, #0	@ D.52529,
	ldrne	r5, [r5, #1264]	@ ModuleLowlyEnable, <variable>.stSynExtraData.s32ModuleLowlyEnable
	cmp	r0, #1	@ VdhId,
	bls	.L411	@,
	movw	r1, #:lower16:.LC34	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC34	@,
	bl	dprint_vfmw	@
.L410:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L411:
	beq	.L412	@,
	movw	r4, #:lower16:g_HwMem	@ tmp153,
	movt	r4, #:upper16:g_HwMem	@ tmp153,
	ldr	r3, [r4, #0]	@ p32, <variable>.pVdmRegVirAddr
	cmp	r3, #0	@ p32,
	beq	.L413	@,
.L407:
	cmp	r5, #1	@ ModuleLowlyEnable,
	mvneq	r2, #5	@ tmp157,
	mvnne	r2, #1	@ tmp158,
	str	r2, [r3, #36]	@ tmp158,
	b	.L410	@
.L412:
	mov	ip, #0	@ tmp152,
	mov	r3, r0	@, VdhId
	movw	r1, #:lower16:.LC15	@,
	mov	r0, ip	@, tmp152
	movt	r1, #:upper16:.LC15	@,
	ldr	r2, .L414	@,
	str	ip, [sp, #0]	@ tmp152,
	bl	dprint_vfmw	@
	b	.L410	@
.L413:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r3, r0, #0	@ p32,
	strne	r3, [r4, #0]	@ p32, <variable>.pVdmRegVirAddr
	bne	.L407	@,
	movw	r1, #:lower16:.LC18	@,
	movt	r1, #:upper16:.LC18	@,
	bl	dprint_vfmw	@
	b	.L410	@
.L415:
	.align	2
.L414:
	.word	.LANCHOR0+296
	.fnend
	.size	VDMHAL_V300R001_EnableInt, .-VDMHAL_V300R001_EnableInt
	.align	2
	.global	VDMHAL_V300R001_MaskInt
	.type	VDMHAL_V300R001_MaskInt, %function
VDMHAL_V300R001_MaskInt:
	.fnstart
.LFB1538:
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
	cmp	r0, #1	@ VdhId,
	bls	.L424	@,
	movw	r1, #:lower16:.LC35	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC35	@,
	bl	dprint_vfmw	@
.L423:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L424:
	beq	.L425	@,
	movw	r4, #:lower16:g_HwMem	@ tmp143,
	movt	r4, #:upper16:g_HwMem	@ tmp143,
	ldr	r3, [r4, #0]	@ p32, <variable>.pVdmRegVirAddr
	cmp	r3, #0	@ p32,
	beq	.L426	@,
.L421:
	mvn	r2, #0	@ tmp147,
	str	r2, [r3, #36]	@ tmp147,
	b	.L423	@
.L425:
	mov	ip, #0	@ tmp142,
	mov	r3, r0	@, VdhId
	movw	r1, #:lower16:.LC15	@,
	mov	r0, ip	@, tmp142
	movt	r1, #:upper16:.LC15	@,
	ldr	r2, .L427	@,
	str	ip, [sp, #0]	@ tmp142,
	bl	dprint_vfmw	@
	b	.L423	@
.L426:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r3, r0, #0	@ p32,
	strne	r3, [r4, #0]	@ p32, <variable>.pVdmRegVirAddr
	bne	.L421	@,
	movw	r1, #:lower16:.LC18	@,
	movt	r1, #:upper16:.LC18	@,
	bl	dprint_vfmw	@
	b	.L423	@
.L428:
	.align	2
.L427:
	.word	.LANCHOR0+324
	.fnend
	.size	VDMHAL_V300R001_MaskInt, .-VDMHAL_V300R001_MaskInt
	.align	2
	.global	VDMHAL_V300R001_ClearIntState
	.type	VDMHAL_V300R001_ClearIntState, %function
VDMHAL_V300R001_ClearIntState:
	.fnstart
.LFB1537:
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
	rsb	r6, r0, r0, asl #3	@, tmp150, VdhId, VdhId,
	add	r1, r6, #1	@ tmp151, tmp150,
	movw	r4, #:lower16:g_VdmDrvParam	@ tmp168,
	movt	r4, #:upper16:g_VdmDrvParam	@ tmp168,
	movw	r3, #:lower16:s_pstVfmwChan	@ tmp146,
	movt	r3, #:upper16:s_pstVfmwChan	@ tmp146,
	ldr	r2, [r4, r1, asl #3]	@ <variable>.ChanId, <variable>.ChanId
	ldr	r6, [r3, r2, asl #2]	@ D.52435, s_pstVfmwChan
	cmp	r6, #0	@ D.52435,
	ldrne	r6, [r6, #1264]	@ ModuleLowlyEnable, <variable>.stSynExtraData.s32ModuleLowlyEnable
	cmp	r0, #1	@ VdhId,
	bls	.L442	@,
	movw	r1, #:lower16:.LC36	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC36	@,
	bl	dprint_vfmw	@
.L441:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L442:
	beq	.L443	@,
	movw	r5, #:lower16:g_HwMem	@ tmp159,
	movt	r5, #:upper16:g_HwMem	@ tmp159,
	ldr	r3, [r5, #0]	@ p32, <variable>.pVdmRegVirAddr
	cmp	r3, #0	@ p32,
	beq	.L444	@,
.L436:
	cmp	r6, #1	@ ModuleLowlyEnable,
	beq	.L445	@,
.L438:
	mvn	r0, #0	@ tmp167,
	str	r0, [r3, #32]	@ tmp167,
	b	.L441	@
.L443:
	mov	ip, #0	@ tmp158,
	mov	r3, r0	@, VdhId
	movw	r1, #:lower16:.LC15	@,
	mov	r0, ip	@, tmp158
	movt	r1, #:upper16:.LC15	@,
	ldr	r2, .L446	@,
	str	ip, [sp, #0]	@ tmp158,
	bl	dprint_vfmw	@
	b	.L441	@
.L445:
	ldr	r2, [r4, #52]	@ D.52453, <variable>.ChanIntState
	cmp	r2, #1	@ D.52453,
	beq	.L438	@,
	cmp	r2, #2	@ D.52453,
	ldr	r1, [r3, #28]	@ dat,
	mvneq	r2, #11	@ tmp165,
	streq	r2, [r3, #32]	@ tmp165,
	beq	.L441	@,
	cmp	r2, #3	@ D.52453,
	mvneq	r2, #14	@ tmp166,
	streq	r2, [r3, #32]	@ tmp166,
	b	.L441	@
.L444:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r3, r0, #0	@ p32,
	strne	r3, [r5, #0]	@ p32, <variable>.pVdmRegVirAddr
	bne	.L436	@,
	movw	r1, #:lower16:.LC18	@,
	movt	r1, #:upper16:.LC18	@,
	bl	dprint_vfmw	@
	b	.L441	@
.L447:
	.align	2
.L446:
	.word	.LANCHOR0+348
	.fnend
	.size	VDMHAL_V300R001_ClearIntState, .-VDMHAL_V300R001_ClearIntState
	.align	2
	.global	VDMHAL_V300R001_GlbReset
	.type	VDMHAL_V300R001_GlbReset, %function
VDMHAL_V300R001_GlbReset:
	.fnstart
.LFB1536:
	@ args = 0, pretend = 0, frame = 8
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
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r2, r0, #0	@ D.52402,
	beq	.L459	@,
	movw	r4, #:lower16:g_pstRegCrg	@ tmp160,
	movt	r4, #:upper16:g_pstRegCrg	@ tmp160,
	ldr	r3, [r4, #0]	@ g_pstRegCrg.471, g_pstRegCrg
	ldr	r5, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	tst	r5, #1	@ u32TmpValue,
	beq	.L454	@,
	orr	r5, r5, #16	@ u32TmpValue, u32TmpValue,
	mov	r2, #0	@ i,
	str	r5, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	movw	ip, #10000	@ tmp161,
	ldr	r1, [r4, #0]	@ prephitmp.1565, g_pstRegCrg
	b	.L452	@
.L461:
	ldr	lr, [r1, #372]	@ D.52413, <variable>.PERI_CRG93.u32
	ands	r0, lr, #1	@ tmp169, D.52413,
	str	lr, [fp, #-24]	@ D.52413, u32TmpValue_93.u32
	bne	.L451	@,
	cmp	r2, ip	@ i, tmp161
	beq	.L460	@,
.L452:
	ldr	r3, [r1, #372]	@ D.52413, <variable>.PERI_CRG93.u32
	add	r2, r2, #1	@ tmp162, i,
	add	r2, r2, #1	@ i, tmp162,
	tst	r3, #1	@ D.52413,
	str	r3, [fp, #-24]	@ D.52413, u32TmpValue_93.u32
	beq	.L461	@,
.L451:
	bfc	r5, #4, #1	@ u32TmpValue,,
	str	r5, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
.L454:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L460:
	movw	r1, #:lower16:.LC38	@,
	movt	r1, #:upper16:.LC38	@,
	bl	dprint_vfmw	@
	ldr	r1, [r4, #0]	@ prephitmp.1565, g_pstRegCrg
	b	.L451	@
.L459:
	movw	r1, #:lower16:.LC37	@,
	movt	r1, #:upper16:.LC37	@,
	bl	dprint_vfmw	@
	b	.L454	@
	.fnend
	.size	VDMHAL_V300R001_GlbReset, .-VDMHAL_V300R001_GlbReset
	.align	2
	.global	VDMHAL_V300R001_ResetVdm
	.type	VDMHAL_V300R001_ResetVdm, %function
VDMHAL_V300R001_ResetVdm:
	.fnstart
.LFB1535:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #16
	sub	sp, sp, #16	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	subs	r4, r0, #0	@ VdhId, VdhId
	bne	.L478	@,
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r2, r0, #0	@ D.52360,
	beq	.L479	@,
	movw	r5, #:lower16:g_HwMem	@ tmp170,
	movw	r6, #:lower16:g_pstRegCrg	@ tmp171,
	movt	r5, #:upper16:g_HwMem	@ tmp170,
	movt	r6, #:upper16:g_pstRegCrg	@ tmp171,
	mov	r2, r4	@ i, VdhId
	movw	ip, #10000	@ tmp172,
	ldr	r1, [r5, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	ldr	r3, [r6, #0]	@ g_pstRegCrg.470, g_pstRegCrg
	ldr	r7, [r1, #36]	@ tmp,
	ldr	r4, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	orr	r4, r4, #64	@ u32TmpValue, u32TmpValue,
	str	r4, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r1, [r6, #0]	@ prephitmp.1597, g_pstRegCrg
	b	.L470	@
.L481:
	ldr	r3, [r1, #372]	@ D.52381, <variable>.PERI_CRG93.u32
	and	lr, r3, #4	@ tmp179, D.52381,
	str	r3, [fp, #-32]	@ D.52381, u32TmpValue_93.u32
	uxtb	r0, lr	@ tmp180, tmp179
	cmp	r0, #0	@ tmp180,
	bne	.L469	@,
	cmp	r2, ip	@ i, tmp172
	beq	.L480	@,
.L470:
	ldr	r0, [r1, #372]	@ D.52381, <variable>.PERI_CRG93.u32
	add	r2, r2, #1	@ tmp173, i,
	add	r2, r2, #1	@ i, tmp173,
	tst	r0, #4	@ D.52381,
	str	r0, [fp, #-32]	@ D.52381, u32TmpValue_93.u32
	beq	.L481	@,
.L469:
	bfc	r4, #6, #1	@ u32TmpValue,,
	str	r4, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	ip, [r5, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r7, [ip, #36]	@ tmp,
	b	.L471	@
.L478:
	cmp	r4, #1	@ VdhId,
	beq	.L482	@,
	movw	r1, #:lower16:.LC39	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC39	@,
	bl	dprint_vfmw	@
.L471:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L482:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	mov	ip, #0	@ tmp152,
	mov	r0, ip	@, tmp152
	mov	r3, r4	@, VdhId
	movw	r1, #:lower16:.LC15	@,
	ldr	r2, .L483	@,
	movt	r1, #:upper16:.LC15	@,
	str	ip, [sp, #0]	@ tmp152,
	bl	dprint_vfmw	@
	b	.L471	@
.L480:
	movw	r1, #:lower16:.LC40	@,
	mov	r2, r0	@,
	movt	r1, #:upper16:.LC40	@,
	bl	dprint_vfmw	@
	ldr	r1, [r6, #0]	@ prephitmp.1597, g_pstRegCrg
	b	.L469	@
.L479:
	movw	r1, #:lower16:.LC37	@,
	movt	r1, #:upper16:.LC37	@,
	bl	dprint_vfmw	@
	b	.L471	@
.L484:
	.align	2
.L483:
	.word	.LANCHOR0+380
	.fnend
	.size	VDMHAL_V300R001_ResetVdm, .-VDMHAL_V300R001_ResetVdm
	.align	2
	.global	VDMHAL_V300R001_CloseHAL
	.type	VDMHAL_V300R001_CloseHAL, %function
VDMHAL_V300R001_CloseHAL:
	.fnstart
.LFB1530:
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
	cmp	r0, #1	@ VdhId,
	mov	r4, r0	@ VdhId, VdhId
	bls	.L491	@,
	movw	r1, #:lower16:.LC41	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC41	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L491:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp139,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp139,
	ldr	r3, [r3, #56]	@ D.51772, g_vdm_hal_fun_ptr.pfun_VDMHAL_ResetVdm
	cmp	r3, #0	@ D.51772,
	beq	.L489	@,
	mov	r0, r4	@, VdhId
	blx	r3	@ D.51772
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L489:
	mov	r0, r3	@, D.51772
	movw	r1, #:lower16:.LC25	@,
	mov	r2, #376	@,
	movt	r1, #:upper16:.LC25	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	VDMHAL_V300R001_CloseHAL, .-VDMHAL_V300R001_CloseHAL
	.align	2
	.global	VDMHAL_V300R001_MakeDecReport
	.type	VDMHAL_V300R001_MakeDecReport, %function
VDMHAL_V300R001_MakeDecReport:
	.fnstart
.LFB1549:
	@ args = 0, pretend = 0, frame = 0
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
	subs	r3, r0, #0	@ pMakeDecReport, pMakeDecReport
	beq	.L518	@,
	ldmib	r3, {r6, r7}	@ phole ldm
	cmp	r6, #0	@ pDecReport,
	ldr	r5, [r3, #0]	@ VidStd, <variable>.VidStd
	beq	.L519	@,
	movw	r0, #1208	@ tmp166,
	movw	r3, #:lower16:g_HwMem	@ tmp167,
	mul	r2, r0, r7	@ tmp165, tmp166, VdhId
	movt	r3, #:upper16:g_HwMem	@ tmp167,
	add	r4, r3, r2	@ pHwMem, tmp167, tmp165
	ldr	r0, [r3, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	cmp	r0, #0	@ <variable>.pVdmRegVirAddr,
	beq	.L520	@,
	movw	r3, #:lower16:g_DSPState	@ tmp305,
	movt	r3, #:upper16:g_DSPState	@ tmp305,
	ldr	r1, [r3, #0]	@ g_DSPState, g_DSPState
	cmp	r1, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	r8, [r3, #4]	@ g_DSPState, g_DSPState
	cmp	r8, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	ip, [r3, #8]	@ g_DSPState, g_DSPState
	cmp	ip, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	lr, [r3, #12]	@ g_DSPState, g_DSPState
	cmp	lr, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	r2, [r3, #16]	@ g_DSPState, g_DSPState
	cmp	r2, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	r0, [r3, #20]	@ g_DSPState, g_DSPState
	cmp	r0, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	r1, [r3, #24]	@ g_DSPState, g_DSPState
	cmp	r1, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	r8, [r3, #28]	@ g_DSPState, g_DSPState
	movw	r3, #:lower16:g_DSPState	@ tmp187,
	movt	r3, #:upper16:g_DSPState	@ tmp187,
	cmp	r8, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	ip, [r3, #32]	@ g_DSPState, g_DSPState
	cmp	ip, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	lr, [r3, #36]	@ g_DSPState, g_DSPState
	cmp	lr, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	r2, [r3, #40]	@ g_DSPState, g_DSPState
	cmp	r2, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	r0, [r3, #44]	@ g_DSPState, g_DSPState
	cmp	r0, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	r1, [r3, #48]	@ g_DSPState, g_DSPState
	cmp	r1, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	r8, [r3, #52]	@ g_DSPState, g_DSPState
	cmp	r8, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	ip, [r3, #56]	@ g_DSPState, g_DSPState
	cmp	ip, #1	@ g_DSPState,
	beq	.L497	@,
	ldr	lr, [r3, #60]	@ g_DSPState, g_DSPState
	cmp	lr, #1	@ g_DSPState,
	movne	r8, #0	@, LowdlyFlag
	moveq	r8, #1	@, LowdlyFlag
.L498:
	mov	r0, r6	@, pDecReport
	mov	r1, #816	@,
	bl	__memzero	@
	movw	r3, #:lower16:g_BackUp	@ tmp304,
	movt	r3, #:upper16:g_BackUp	@ tmp304,
	mov	r0, #180	@ tmp211,
	ldr	r1, [r4, #24]	@ <variable>.VahbStride, <variable>.VahbStride
	mla	ip, r0, r7, r3	@ tmp212, tmp211, VdhId, tmp304
	str	r1, [r6, #4]	@ <variable>.VahbStride, <variable>.ImgStride
	ldr	r2, [ip, #4]	@ D.53247, <variable>.VdmState
	mov	r2, r2, lsr #17	@ tmp214, D.53247,
	and	r0, r2, #3	@ tmp215, tmp214,
	cmp	r0, #1	@ tmp215,
	moveq	r2, #0	@ prephitmp.1660,
	beq	.L500	@,
	eor	lr, r2, #1	@ tmp217, tmp214,
	and	r2, lr, #1	@ tmp219, tmp217,
	cmp	r5, #3	@ VidStd,
	orrne	r2, r2, #1	@,, prephitmp.1660, tmp219
.L500:
	mov	r1, #180	@ tmp227,
	str	r2, [r6, #0]	@ prephitmp.1660, <variable>.RetType
	mla	r3, r1, r7, r3	@ tmp228, tmp227, VdhId, tmp304
	cmp	r5, #0	@ VidStd,
	cmpne	r5, #15	@, VidStd,
	ldr	ip, [r3, #4]	@ <variable>.VdmState, <variable>.VdmState
	bic	r2, ip, #-16777216	@ D.53257, <variable>.VdmState,
	bic	r2, r2, #16646144	@ D.53257, D.53257,
	str	r2, [r6, #8]	@ D.53257, <variable>.DecSliceNum
	bne	.L501	@,
	cmp	r8, #1	@ LowdlyFlag,
	beq	.L521	@,
	movw	ip, #:lower16:g_not_allow_H264FullPictureRepair_flag	@ tmp253,
	movt	ip, #:upper16:g_not_allow_H264FullPictureRepair_flag	@ tmp253,
	ldrb	r1, [ip, #0]	@ zero_extendqisi2	@ g_not_allow_H264FullPictureRepair_flag, g_not_allow_H264FullPictureRepair_flag
	cmp	r1, #0	@ g_not_allow_H264FullPictureRepair_flag,
	beq	.L522	@,
.L501:
	cmp	r2, #200	@ D.53257,
	bhi	.L523	@,
.L503:
	ldr	r8, [r4, #32]	@ D.53282, <variable>.MsgSlotAddr
	mov	r0, r8	@, D.53282
	bl	MEM_Phy2Vir	@
	subs	r1, r0, #0	@ D.53284,
	beq	.L524	@,
	movw	r4, #:lower16:g_UpMsg	@ tmp306,
	movt	r4, #:upper16:g_UpMsg	@ tmp306,
	mov	r5, #3200	@ tmp276,
	ldr	lr, [r6, #8]	@ <variable>.DecSliceNum, <variable>.DecSliceNum
	mla	r5, r5, r7, r4	@ tmp277, tmp276, VdhId, tmp306
	mov	r2, lr, asl #2	@, <variable>.DecSliceNum,
	mov	r0, r5	@, tmp277
	bl	VDMHAL_V300R001_ReadMsgSlot	@
	ldr	ip, [r6, #8]	@ temp.1707, <variable>.DecSliceNum
	cmp	ip, #0	@ temp.1707,
	beq	.L505	@,
	ldrh	r2, [r5, #4]	@, g_UpMsg
	mov	r0, #1	@ i,
	cmp	r0, ip	@ i, temp.1707
	sub	r3, ip, #1	@ tmp309, temp.1707,
	strh	r2, [r6, #12]	@ movhi	@, <variable>.SliceMbRange
	and	r2, r3, r0	@ tmp311, tmp309,
	ldrh	r1, [r5, #8]	@, g_UpMsg
	add	r3, r6, #4	@ ivtmp.1690, pDecReport,
	add	r5, r5, #16	@ ivtmp.1687, tmp277,
	strh	r1, [r6, #14]	@ movhi	@, <variable>.SliceMbRange
	bcs	.L505	@,
	cmp	r2, #0	@ tmp311,
	beq	.L506	@,
	ldrh	r1, [r5, #4]	@, g_UpMsg
	mov	r0, #2	@ i,
	cmp	r0, ip	@ i, temp.1707
	strh	r1, [r3, #12]	@ movhi	@, <variable>.SliceMbRange
	ldrh	r2, [r5, #8]	@, g_UpMsg
	add	r5, r5, #16	@ ivtmp.1687, ivtmp.1687,
	strh	r2, [r3, #14]	@ movhi	@, <variable>.SliceMbRange
	add	r3, r3, #4	@ ivtmp.1690, ivtmp.1690,
	bcs	.L505	@,
.L506:
	ldrh	lr, [r5, #4]	@, g_UpMsg
	add	r2, r5, #16	@ tmp313, ivtmp.1687,
	add	r0, r0, #2	@ i, i,
	cmp	r0, ip	@ i, temp.1707
	strh	lr, [r3, #12]	@ movhi	@, <variable>.SliceMbRange
	add	lr, r3, #4	@ tmp314, ivtmp.1690,
	ldrh	r1, [r5, #8]	@, g_UpMsg
	strh	r1, [r3, #14]	@ movhi	@, <variable>.SliceMbRange
	add	r3, lr, #4	@ ivtmp.1690, tmp314,
	ldrh	r5, [r2, #4]	@, g_UpMsg
	strh	r5, [lr, #12]	@ movhi	@, <variable>.SliceMbRange
	add	r5, r2, #16	@ ivtmp.1687, tmp313,
	ldrh	r1, [r2, #8]	@, g_UpMsg
	strh	r1, [lr, #14]	@ movhi	@, <variable>.SliceMbRange
	bcc	.L506	@,
.L505:
	mov	r0, #6	@,
	bl	IsDprintTypeEnable	@
	cmp	r0, #0	@ D.53298
	bne	.L525	@,
.L494:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L497:
	mov	r8, #1	@ LowdlyFlag,
	b	.L498	@
.L525:
	ldr	r2, [r6, #8]	@, <variable>.DecSliceNum
	mov	r0, #6	@,
	movw	r1, #:lower16:.LC45	@,
	movt	r1, #:upper16:.LC45	@,
	bl	dprint_vfmw	@
	mov	r2, r8	@, D.53282
	mov	r0, #6	@,
	movw	r1, #:lower16:.LC46	@,
	movt	r1, #:upper16:.LC46	@,
	bl	dprint_vfmw	@
	ldr	r0, [r6, #8]	@ <variable>.DecSliceNum, <variable>.DecSliceNum
	mov	ip, r0, asl #2	@ tmp289, <variable>.DecSliceNum,
	cmp	ip, #3	@ tmp289,
	beq	.L508	@,
	mov	r3, #3200	@ tmp292,
	mov	r5, #0	@ i_cnt,
	mla	r4, r3, r7, r4	@ ivtmp.1677, tmp292, VdhId, tmp306
.L509:
	ldr	ip, [r4, #8]	@ tmp296, g_UpMsg
	mov	r2, r5	@, i_cnt
	ldr	lr, [r4, #4]	@ tmp295, g_UpMsg
	mov	r0, #6	@,
	ldr	r7, [r4, #12]	@ tmp297, g_UpMsg
	movw	r1, #:lower16:.LC47	@,
	ldr	r3, [r4, #0]	@ tmp294, g_UpMsg
	movt	r1, #:upper16:.LC47	@,
	str	ip, [sp, #4]	@ tmp296,
	add	r5, r5, #4	@ i_cnt, i_cnt,
	str	lr, [sp, #0]	@ tmp295,
	add	r4, r4, #16	@ ivtmp.1677, ivtmp.1677,
	str	r7, [sp, #8]	@ tmp297,
	bl	dprint_vfmw	@
	ldr	ip, [r6, #8]	@ <variable>.DecSliceNum, <variable>.DecSliceNum
	mov	r1, ip, asl #2	@ tmp298, <variable>.DecSliceNum,
	sub	r2, r1, #3	@ tmp300, tmp298,
	cmp	r2, r5	@ tmp300, i_cnt
	bhi	.L509	@,
.L508:
	mov	r0, #6	@,
	movw	r1, #:lower16:.LC48	@,
	movt	r1, #:upper16:.LC48	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.53224,
	b	.L494	@
.L523:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC44	@,
	mov	r3, #200	@,
	movt	r1, #:upper16:.LC44	@,
	bl	dprint_vfmw	@
	mov	r8, #0	@ tmp270,
	str	r8, [r6, #8]	@ tmp270, <variable>.DecSliceNum
	b	.L503	@
.L522:
	ldrb	r0, [r3, #19]	@ zero_extendqisi2	@ tmp261, <variable>.SedSta
	and	r3, r0, #3	@ tmp263, tmp261,
	cmp	r3, #2	@ tmp263,
	bne	.L501	@,
	mov	r2, #1	@ tmp264,
	strh	r1, [r6, #14]	@ movhi	@ g_not_allow_H264FullPictureRepair_flag, <variable>.SliceMbRange
	mov	r0, r1	@ D.53224, g_not_allow_H264FullPictureRepair_flag
	strh	r1, [r6, #12]	@ movhi	@ g_not_allow_H264FullPictureRepair_flag, <variable>.SliceMbRange
	str	r2, [r6, #8]	@ tmp264, <variable>.DecSliceNum
	b	.L494	@
.L521:
	ldr	r0, [r3, #16]	@ <variable>.SedSta, <variable>.SedSta
	ubfx	r3, r0, #21, #2	@ tmp247, <variable>.SedSta,,
	cmp	r3, #2	@ tmp247,
	bne	.L501	@,
	mov	lr, #0	@ movhi	@,
	str	r8, [r6, #8]	@ LowdlyFlag, <variable>.DecSliceNum
	strh	lr, [r6, #14]	@ movhi	@, <variable>.SliceMbRange
	mov	r0, #0	@ D.53224,
	strh	lr, [r6, #12]	@ movhi	@, <variable>.SliceMbRange
	b	.L494	@
.L524:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L526	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC29	@,
	movt	r3, #:upper16:.LC29	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53224,
	b	.L494	@
.L518:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L526	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC42	@,
	movt	r3, #:upper16:.LC42	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53224,
	b	.L494	@
.L520:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L526	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC3	@,
	movt	r3, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53224,
	b	.L494	@
.L519:
	mov	r0, r6	@, pDecReport
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L526	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC43	@,
	movt	r3, #:upper16:.LC43	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53224,
	b	.L494	@
.L527:
	.align	2
.L526:
	.word	.LANCHOR0+408
	.fnend
	.size	VDMHAL_V300R001_MakeDecReport, .-VDMHAL_V300R001_MakeDecReport
	.align	2
	.global	VDMHAL_V300R001_PrepareDec
	.type	VDMHAL_V300R001_PrepareDec, %function
VDMHAL_V300R001_PrepareDec:
	.fnstart
.LFB1541:
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
	subs	r5, r1, #0	@ pDecParam, pDecParam
	mov	r4, r0	@ VidStd, VidStd
	mov	r7, r2	@ VdhId, VdhId
	beq	.L538	@,
	cmp	r0, #6	@ VidStd,
	movw	r6, #:lower16:s_RegPhyBaseAddr	@ tmp153,
	movt	r6, #:upper16:s_RegPhyBaseAddr	@ tmp153,
	moveq	r1, #1	@,
	movne	r1, #0	@,
	ldr	r0, [r6, #0]	@, s_RegPhyBaseAddr
	bl	MEM_WritePhyWord	@
	cmp	r7, #0	@ VdhId,
	beq	.L534	@,
	cmp	r7, #1	@ VdhId,
	beq	.L554	@,
	cmp	r7, #0	@ VdhId,
	bgt	.L537	@,
.L536:
	cmp	r4, #16	@ VidStd,
	ldrls	pc, [pc, r4, asl #2]	@ VidStd
	b	.L538	@
.L551:
	.word	.L549
	.word	.L540
	.word	.L541
	.word	.L542
	.word	.L538
	.word	.L543
	.word	.L544
	.word	.L538
	.word	.L545
	.word	.L546
	.word	.L547
	.word	.L547
	.word	.L547
	.word	.L548
	.word	.L538
	.word	.L549
	.word	.L550
.L534:
	ldr	r0, [r6, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	mov	r1, #1	@,
	add	r0, r0, #8	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	b	.L536	@
.L554:
	movw	r3, #:lower16:s_RegPhyBaseAddr_1	@ tmp145,
	movt	r3, #:upper16:s_RegPhyBaseAddr_1	@ tmp145,
	mov	r1, r7	@, VdhId
	ldr	r2, [r3, #0]	@ s_RegPhyBaseAddr_1, s_RegPhyBaseAddr_1
	add	r0, r2, #8	@, s_RegPhyBaseAddr_1,
	bl	MEM_WritePhyWord	@
.L537:
	mov	ip, #0	@ tmp151,
	mov	r3, r7	@, VdhId
	mov	r0, ip	@, tmp151
	movw	r1, #:lower16:.LC15	@,
	ldr	r2, .L555	@,
	movt	r1, #:upper16:.LC15	@,
	str	ip, [sp, #0]	@ tmp151,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ s32ret,
.L530:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L549:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	H264HAL_V300R001_StartDec	@
	b	.L530	@
.L538:
	mvn	r0, #0	@ s32ret,
	b	.L530	@
.L548:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	VP8HAL_V300R001_StartDec	@
	b	.L530	@
.L547:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	VP6HAL_V300R001_StartDec	@
	b	.L530	@
.L546:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	RV9HAL_V300R001_StartDec	@
	b	.L530	@
.L545:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	RV8HAL_V300R001_StartDec	@
	b	.L530	@
.L544:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	AVSHAL_V300R001_StartDec	@
	b	.L530	@
.L543:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	DIVX3HAL_V300R001_StartDec	@
	b	.L530	@
.L542:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	MP2HAL_V300R001_StartDec	@
	b	.L530	@
.L541:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	MP4HAL_V300R001_StartDec	@
	b	.L530	@
.L540:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	VC1HAL_V300R001_StartDec	@
	b	.L530	@
.L550:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	HEVCHAL_V300R001_StartDec	@
	b	.L530	@
.L556:
	.align	2
.L555:
	.word	.LANCHOR0+440
	.fnend
	.size	VDMHAL_V300R001_PrepareDec, .-VDMHAL_V300R001_PrepareDec
	.align	2
	.global	VDMHAL_V300R001_ArrangeMem
	.type	VDMHAL_V300R001_ArrangeMem, %function
VDMHAL_V300R001_ArrangeMem:
	.fnstart
.LFB1533:
	@ args = 20, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #76
	sub	sp, sp, #76	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	ldr	r4, [fp, #16]	@ eFlag, eFlag
	mov	r5, r0	@ MemAddr, MemAddr
	str	r1, [fp, #-76]	@ MemSize, %sfp
	cmn	r4, #2	@ eFlag,
	mov	r7, r2	@ Width, Width
	mov	sl, r3	@ Height, Height
	ldr	r8, [fp, #20]	@ pVdmMemArrange, pVdmMemArrange
	beq	.L558	@,
	cmp	r4, #0	@ eFlag,
	movlt	r9, #19	@ VidStd,
	blt	.L560	@,
	mov	r0, r4	@, eFlag
	movw	r6, #:lower16:s_pstVfmwChan	@ tmp609,
	bl	VCTRL_GetVidStd	@
	movt	r6, #:upper16:s_pstVfmwChan	@ tmp609,
	mov	r9, r0	@ VidStd,
	ldr	r0, [r6, r4, asl #2]	@ D.51983, s_pstVfmwChan
	ldr	r3, [r0, #1424]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r3, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	beq	.L676	@,
.L560:
	cmp	r5, #0	@ MemAddr,
	beq	.L677	@,
	cmp	sl, #31	@ Height,
	movgt	lr, #0	@, tmp437
	movle	lr, #1	@, tmp437
	sub	ip, r7, #32	@ tmp432, Width,
	movw	r3, #8160	@ tmp434,
	cmp	ip, r3	@ tmp432, tmp434
	movls	r0, lr	@, tmp440, tmp437
	orrhi	r0, lr, #1	@,, tmp440, tmp437
	cmp	r0, #0	@ tmp440,
	bne	.L599	@,
	cmp	sl, #8192	@ Height,
	bgt	.L599	@,
	cmp	r8, #0	@ pVdmMemArrange,
	beq	.L678	@,
	mov	r0, r8	@, pVdmMemArrange
	mov	r1, #940	@,
	bl	__memzero	@
	add	r0, r7, #15	@ tmp449, Width,
	add	r2, sl, #15	@ tmp450, Height,
	movw	r1, #:lower16:g_not_direct_8x8_inference_flag	@ tmp458,
	mov	r3, r0, asr #4	@ ImgWidthInMb, tmp449,
	movt	r1, #:upper16:g_not_direct_8x8_inference_flag	@ tmp458,
	mov	r0, r2, asr #4	@ ImgHeightInMb, tmp450,
	ldr	r2, [fp, #4]	@ PmvNum, PmvNum
	ldrb	r6, [r1, #0]	@ zero_extendqisi2	@ g_not_direct_8x8_inference_flag, g_not_direct_8x8_inference_flag
	cmp	r2, #20	@ PmvNum,
	movge	r2, #20	@ PmvNum.1837,
	cmp	r0, #36	@ ImgHeightInMb,
	cmple	r3, #45	@, ImgWidthInMb,
	mul	r1, r3, r0	@ tmp460, ImgWidthInMb, ImgHeightInMb
	movle	ip, #64	@, ColMbSize,
	movgt	ip, #32	@, ColMbSize,
	cmp	r6, #1	@ g_not_direct_8x8_inference_flag,
	moveq	ip, #64	@ ColMbSize,
	cmp	r9, #16	@ VidStd,
	moveq	ip, #16	@ ColMbSize,
	mul	lr, ip, r1	@ tmp461, ColMbSize, tmp460
	ldr	ip, [fp, #-76]	@, %sfp
	add	r6, lr, #127	@ tmp462, tmp461,
	bic	r6, r6, #127	@ PmvSlotLen, tmp462,
	mul	r1, r2, r6	@ PmvPoolSize, PmvNum.1837, PmvSlotLen
	cmp	r1, ip	@ PmvPoolSize,
	bge	.L679	@,
	cmp	r9, #16	@ VidStd,
	mov	r3, r3, asl #4	@ ImgWidthInPixAln, ImgWidthInMb,
	mov	ip, r6, asr #1	@ tmp469, PmvSlotLen,
	sub	lr, r3, #1	@ tmp473, ImgWidthInPixAln,
	str	ip, [r8, #932]	@ tmp469, <variable>.HafPmvOffset
	addeq	ip, r7, #255	@ tmp470, Width,
	addne	ip, r3, #255	@ tmp471, ImgWidthInPixAln,
	str	r2, [r8, #936]	@ PmvNum.1837, <variable>.ValidPMVNum
	bic	r2, ip, #255	@ SlotWidth, tmp471,
	movw	ip, #2047	@ tmp474,
	cmp	lr, ip	@ tmp473, tmp474
	mov	lr, r2, asl #4	@ tmp472, SlotWidth,
	str	lr, [r8, #0]	@ tmp472, <variable>.VahbStride
	bhi	.L680	@,
.L608:
	mov	ip, #16	@ level,
.L610:
	ldr	r3, [fp, #12]	@, UserDec
	cmp	r3, #1	@,
	mov	r3, r0, asl #4	@ ImgHeightInPixAln, ImgHeightInMb,
	addeq	r0, r3, r0, asl #5	@, tmp486, ImgHeightInPixAln, ImgHeightInMb,
	muleq	r7, r2, r0	@ ImgSlotLen, SlotWidth, tmp486
	beq	.L613	@,
	cmp	r9, #16	@ VidStd,
	beq	.L681	@,
	adds	r0, r3, #31	@ tmp494, ImgHeightInPixAln,
	addmi	r0, r3, #62	@, tmp495, ImgHeightInPixAln,
	mov	r7, r0, asr #5	@ tmp497, tmp495,
	add	lr, r7, r7, asl #1	@, tmp500, tmp497, tmp497,
	mov	r0, lr, asl #5	@ tmp501, tmp500,
	mul	r7, r2, r0	@ tmp508, SlotWidth, tmp501
	mul	r0, ip, r0	@ tmp502, level, tmp501
	mov	lr, r7, asr #1	@ tmp512, tmp508,
	add	r7, lr, r0, lsr #1	@, ImgSlotLen, tmp512, tmp502,
.L613:
	cmp	r4, #0	@ eFlag,
	blt	.L615	@,
	mov	r0, r4	@, eFlag
	str	r1, [fp, #-96]	@,
	str	r2, [fp, #-88]	@,
	str	r3, [fp, #-84]	@,
	str	ip, [fp, #-92]	@,
	bl	VCTRL_GetChanWidth	@
	str	r0, [fp, #-68]	@, %sfp
	mov	r0, r4	@, eFlag
	bl	VCTRL_GetChanHeight	@
	ldr	r4, [fp, #-68]	@, %sfp
	ldr	r1, [fp, #-96]	@,
	ldr	r2, [fp, #-88]	@,
	ldr	r3, [fp, #-84]	@,
	ldr	ip, [fp, #-92]	@,
	cmn	r0, #1	@ ChanHeight,
	cmnne	r4, #1	@,,
	beq	.L682	@,
	ldr	r4, [fp, #-68]	@, %sfp
	add	r0, r0, #15	@, ChanHeight,
	str	r0, [fp, #-68]	@, %sfp
	add	lr, r4, #15	@ tmp521,,
	movw	r4, #2047	@ tmp527,
	bic	lr, lr, #15	@ ChanImgWidthInPixAln, tmp521,
	sub	r0, lr, #1	@, ChanImgWidthInPixAln,
	str	r0, [fp, #-64]	@, %sfp
	add	r0, lr, #255	@, ChanImgWidthInPixAln,
	str	r0, [fp, #-80]	@, %sfp
	ldr	r0, [fp, #-64]	@, %sfp
	cmp	r0, r4	@, tmp527
	ldr	r0, [fp, #-68]	@, %sfp
	bic	r0, r0, #15	@,,
	str	r0, [fp, #-68]	@, %sfp
	ldr	r0, [fp, #-80]	@, %sfp
	bic	r0, r0, #255	@,,
	str	r0, [fp, #-80]	@, %sfp
	bls	.L617	@,
	sub	r0, lr, #2048	@ tmp528, ChanImgWidthInPixAln,
	sub	r0, r0, #1	@ tmp528, tmp528,
	cmp	r0, r4	@ tmp528, tmp527
	movls	r4, #32	@,
	strls	r4, [fp, #-64]	@, %sfp
	bhi	.L683	@,
.L619:
	ldr	r0, [fp, #12]	@, UserDec
	cmp	r0, #1	@,
	beq	.L684	@,
.L621:
	ldr	r0, [fp, #-68]	@, %sfp
	ldr	r4, [fp, #-80]	@, %sfp
	adds	lr, r0, #31	@ tmp540,,
	addmi	lr, r0, #62	@, tmp541,,
	mov	r0, lr, asr #5	@ tmp543, tmp541,
	mul	lr, r0, r4	@ tmp550, tmp543,
	add	r4, r0, r0, asl #1	@, tmp546, tmp543, tmp543,
	mov	r0, r4, asl #5	@ tmp547, tmp546,
	ldr	r4, [fp, #-64]	@, %sfp
	mul	r0, r4, r0	@ tmp548,, tmp547
	add	lr, lr, lr, asl #1	@, tmp553, tmp550, tmp550,
	mov	lr, lr, asl #5	@ tmp554, tmp553,
	mov	lr, lr, asr #1	@ tmp558, tmp554,
	add	r0, lr, r0, lsr #1	@, ChanSlotLen, tmp558, tmp548,
.L622:
	cmp	r7, r0	@ ImgSlotLen, ChanSlotLen
	bgt	.L685	@,
.L615:
	cmp	r9, #16	@ VidStd,
	muleq	r2, sl, r2	@ tmp563, Height, SlotWidth
	streq	r2, [r8, #536]	@ tmp563, <variable>.ChromOffset
	beq	.L624	@,
	adds	r0, r3, #31	@ tmp564, ImgHeightInPixAln,
	addmi	r9, r3, #62	@, tmp565, ImgHeightInPixAln,
	movpl	r9, r0	@, tmp565, tmp564
	mov	lr, r9, asr #5	@ tmp567, tmp565,
	mul	r2, lr, r2	@ tmp569, tmp567, SlotWidth
	mla	r3, lr, ip, r2	@ tmp570, tmp567, level, tmp569
	mov	r9, r3, asl #5	@ tmp571, tmp570,
	str	r9, [r8, #536]	@ tmp571, <variable>.ChromOffset
.L624:
	ldr	r9, [fp, #8]	@, FrameNum
	cmp	r9, #0	@,
	streq	r9, [r8, #548]	@, <variable>.ValidFrameNum
	bne	.L686	@,
.L626:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L693	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC58	@,
	movt	r3, #:upper16:.LC58	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
.L579:
	mov	r0, r3	@, ret
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L680:
	sub	lr, r3, #2048	@ tmp475, ImgWidthInPixAln,
	sub	lr, lr, #1	@ tmp475, tmp475,
	cmp	lr, ip	@ tmp475, tmp474
	movls	ip, #32	@ level,
	bls	.L610	@,
	sub	lr, r3, #4096	@ tmp478, ImgWidthInPixAln,
	sub	lr, lr, #1	@ tmp478, tmp478,
	cmp	lr, ip	@ tmp478, tmp474
	movls	ip, #48	@ level,
	bls	.L610	@,
	sub	lr, r3, #6144	@ tmp481, ImgWidthInPixAln,
	sub	r3, lr, #1	@ tmp481, tmp481,
	cmp	r3, ip	@ tmp481, tmp474
	movls	ip, #64	@ level,
	bls	.L610	@,
	b	.L608	@
.L686:
	add	lr, r5, #1020	@ tmp573, MemAddr,
	ldr	r2, [fp, #-76]	@, %sfp
	add	sl, lr, #3	@ tmp573, tmp573,
	bic	r4, sl, #1020	@ tmp575, tmp573,
	rsb	r3, r1, r2	@ tmp577, PmvPoolSize,
	bic	ip, r4, #3	@ tmp575, tmp575,
	mov	r1, r7	@, ImgSlotLen
	rsb	r4, r5, ip	@ Offset, MemAddr, tmp575
	ldr	sl, [fp, #8]	@ D.52154, FrameNum
	rsb	r0, r4, r3	@, Offset, tmp577
	bl	__aeabi_idiv	@
	cmp	sl, #64	@ D.52154,
	movge	sl, #64	@ D.52154,
	cmp	sl, r0	@ D.52154,
	movlt	r0, sl	@ D.52154, D.52154
	movge	r0, r0	@ D.52154,
	str	r0, [r8, #548]	@ D.52154, <variable>.ValidFrameNum
	cmp	r0, #0	@ D.52154,
	beq	.L626	@,
	ble	.L687	@,
	cmp	r0, #1	@ D.52154,
	add	r1, r4, r5	@ ivtmp.1813, Offset, MemAddr
	sub	r3, r0, #1	@ tmp627, D.52154,
	str	r1, [r8, #8]	@ ivtmp.1813, <variable>.FrameAddr
	and	ip, r3, #1	@ tmp629, tmp627,
	add	r2, r1, r7	@ ivtmp.1813, ivtmp.1813, ImgSlotLen
	add	r3, r8, #4	@ ivtmp.1817, pVdmMemArrange,
	mov	r1, #1	@ i,
	ble	.L663	@,
	cmp	ip, #0	@ tmp629,
	beq	.L629	@,
	mov	r1, #2	@ i,
	cmp	r0, r1	@ D.52154, i
	str	r2, [r3, #8]	@ ivtmp.1813, <variable>.FrameAddr
	add	r2, r2, r7	@ ivtmp.1813, ivtmp.1813, ImgSlotLen
	add	r3, r3, #4	@ ivtmp.1817, ivtmp.1817,
	ble	.L663	@,
.L629:
	add	r1, r1, #2	@ i, i,
	add	ip, r3, #4	@ tmp631, ivtmp.1817,
	cmp	r0, r1	@ D.52154, i
	add	sl, r2, r7	@ ivtmp.1813, ivtmp.1813, ImgSlotLen
	str	r2, [r3, #8]	@ ivtmp.1813, <variable>.FrameAddr
	add	r2, sl, r7	@ ivtmp.1813, ivtmp.1813, ImgSlotLen
	str	sl, [ip, #8]	@ ivtmp.1813, <variable>.FrameAddr
	add	r3, ip, #4	@ ivtmp.1817, tmp631,
	bgt	.L629	@,
.L663:
	mla	r4, r0, r7, r4	@ Offset.1847, D.52154, ImgSlotLen, Offset
	ldr	r0, [r8, #548]	@ D.52154, <variable>.ValidFrameNum
	mov	r1, #1	@ i.1848,
	add	r3, r8, #4	@ ivtmp.1866, pVdmMemArrange,
	cmp	r0, r1	@ D.52154,
	sub	r2, r0, #1	@ tmp621, D.52154,
	add	lr, r4, r5	@ ivtmp.1806, Offset.1847, MemAddr
	and	ip, r2, r1	@ tmp623, tmp621,
	str	lr, [r8, #264]	@ ivtmp.1806, <variable>.LineNumAddr
	add	r2, lr, #32	@ ivtmp.1806, ivtmp.1806,
	ble	.L634	@,
	cmp	ip, #0	@ tmp623,
	beq	.L630	@,
	mov	r1, #2	@ i.1848,
	cmp	r0, r1	@ D.52154, i.1848
	str	r2, [r3, #264]	@ ivtmp.1806, <variable>.LineNumAddr
	add	r2, r2, #32	@ ivtmp.1806, ivtmp.1806,
	add	r3, r3, #4	@ ivtmp.1866, ivtmp.1866,
	ble	.L634	@,
.L630:
	add	r1, r1, #2	@ i.1848, i.1848,
	add	ip, r3, #4	@ tmp626, ivtmp.1866,
	cmp	r0, r1	@ D.52154, i.1848
	add	r7, r2, #32	@ tmp625, ivtmp.1806,
	str	r2, [r3, #264]	@ ivtmp.1806, <variable>.LineNumAddr
	add	r2, r7, #32	@ ivtmp.1806, tmp625,
	str	r7, [ip, #264]	@ tmp625, <variable>.LineNumAddr
	add	r3, ip, #4	@ ivtmp.1866, tmp626,
	bgt	.L630	@,
.L634:
	ldr	sl, [r8, #936]	@ D.52167, <variable>.ValidPMVNum
	add	r0, r4, r0, asl #5	@, Offset.1849, Offset.1847, D.52154,
	add	r2, r0, r5	@ MemAddr.1850, Offset.1849, MemAddr
	cmp	sl, #0	@ D.52167,
	ble	.L631	@,
	mov	r1, #1	@ i.1851,
	cmp	r1, sl	@ i.1851, D.52167
	sub	r3, sl, #1	@ tmp616, D.52167,
	str	r2, [r8, #812]	@ MemAddr.1850, <variable>.PMVAddr
	and	ip, r3, r1	@ tmp618, tmp616,
	add	r2, r2, r6	@ ivtmp.1799, MemAddr.1850, PmvSlotLen
	add	r3, r8, #4	@ ivtmp.1803, pVdmMemArrange,
	bge	.L631	@,
	cmp	ip, #0	@ tmp618,
	beq	.L632	@,
	mov	r1, #2	@ i.1851,
	cmp	r1, sl	@ i.1851, D.52167
	str	r2, [r3, #812]	@ ivtmp.1799, <variable>.PMVAddr
	add	r2, r2, r6	@ ivtmp.1799, ivtmp.1799, PmvSlotLen
	add	r3, r3, #4	@ ivtmp.1803, ivtmp.1803,
	bge	.L631	@,
.L632:
	add	r1, r1, #2	@ i.1851, i.1851,
	add	lr, r3, #4	@ tmp620, ivtmp.1803,
	cmp	r1, sl	@ i.1851, D.52167
	add	r4, r2, r6	@ ivtmp.1799, ivtmp.1799, PmvSlotLen
	str	r2, [r3, #812]	@ ivtmp.1799, <variable>.PMVAddr
	add	r2, r4, r6	@ ivtmp.1799, ivtmp.1799, PmvSlotLen
	str	r4, [lr, #812]	@ ivtmp.1799, <variable>.PMVAddr
	add	r3, lr, #4	@ ivtmp.1803, tmp620,
	blt	.L632	@,
.L631:
	mla	r0, sl, r6, r0	@ tmp590, D.52167, PmvSlotLen, Offset.1849
	mov	r3, #0	@ ret,
	str	r0, [r8, #4]	@ tmp590, <variable>.TotalMemUsed
	b	.L579	@
.L558:
	mov	r9, #16	@ VidStd,
	b	.L560	@
.L683:
	sub	r0, lr, #4096	@ tmp531, ChanImgWidthInPixAln,
	sub	r0, r0, #1	@ tmp531, tmp531,
	cmp	r0, r4	@ tmp531, tmp527
	movls	lr, #48	@,
	strls	lr, [fp, #-64]	@, %sfp
	bls	.L619	@,
	sub	lr, lr, #6144	@ tmp534, ChanImgWidthInPixAln,
	sub	lr, lr, #1	@ tmp534, tmp534,
	cmp	lr, r4	@ tmp534, tmp527
	movls	r0, #64	@,
	strls	r0, [fp, #-64]	@, %sfp
	bls	.L619	@,
.L617:
	ldr	r0, [fp, #12]	@, UserDec
	mov	r4, #16	@,
	str	r4, [fp, #-64]	@, %sfp
	cmp	r0, #1	@,
	bne	.L621	@,
.L684:
	ldr	r4, [fp, #-68]	@, %sfp
	ldr	lr, [fp, #-80]	@, %sfp
	add	r0, r4, r4, asl #1	@, tmp539,,,
	mul	r0, lr, r0	@ ChanSlotLen,, tmp539
	b	.L622	@
.L676:
	movw	r2, #:lower16:250808	@ tmp226,
	movt	r2, #:upper16:250808	@ tmp226,
	cmp	sl, #31	@ Height,
	movgt	r1, #0	@, tmp232
	movle	r1, #1	@, tmp232
	sub	r3, r7, #32	@ tmp227, Width,
	movw	lr, #8160	@ tmp229,
	cmp	r3, lr	@ tmp227, tmp229
	movls	ip, r1	@, tmp235, tmp232
	orrhi	ip, r1, #1	@,, tmp235, tmp232
	ldr	r1, [r0, r2]	@, <variable>.s32CurFsSize
	cmp	ip, #0	@ tmp235,
	str	r1, [fp, #-76]	@, %sfp
	bne	.L561	@,
	cmp	sl, #8192	@ Height,
	bgt	.L561	@,
	add	r2, r7, #15	@ tmp240, Width,
	add	r3, sl, #15	@ tmp241, Height,
	movw	ip, #:lower16:g_not_direct_8x8_inference_flag	@ tmp249,
	movt	ip, #:upper16:g_not_direct_8x8_inference_flag	@ tmp249,
	mov	r2, r2, asr #4	@ ImgWidthInMb, tmp240,
	mov	r3, r3, asr #4	@ ImgHeightInMb, tmp241,
	cmp	r3, #36	@ ImgHeightInMb,
	cmple	r2, #45	@, ImgWidthInMb,
	ldrb	lr, [ip, #0]	@ zero_extendqisi2	@ g_not_direct_8x8_inference_flag, g_not_direct_8x8_inference_flag
	mov	r5, r3, asl #4	@, ImgHeightInMb,
	mov	r1, r2, asl #4	@ ImgWidthInPixAln, ImgWidthInMb,
	movle	ip, #64	@, ColMbSize,
	movgt	ip, #32	@, ColMbSize,
	cmp	lr, #1	@ g_not_direct_8x8_inference_flag,
	str	r5, [fp, #-72]	@, %sfp
	moveq	ip, #64	@ ColMbSize,
	cmp	r9, #16	@ VidStd,
	beq	.L567	@,
	mul	lr, r2, r3	@ tmp251, ImgWidthInMb, ImgHeightInMb
	add	r5, r1, #255	@ tmp254, ImgWidthInPixAln,
	bic	r5, r5, #255	@ SlotWidth, tmp254,
	mul	r3, ip, lr	@ tmp252, ColMbSize, tmp251
	add	lr, r3, #127	@ tmp253, tmp252,
	bic	r3, lr, #127	@ PmvSlotLen, tmp253,
.L633:
	sub	ip, r1, #1	@ tmp255, ImgWidthInPixAln,
	movw	r2, #2047	@ tmp256,
	cmp	ip, r2	@ tmp255, tmp256
	movls	r2, #16	@ level,
	bls	.L569	@,
	sub	ip, r1, #2048	@ tmp257, ImgWidthInPixAln,
	sub	lr, ip, #1	@ tmp257, tmp257,
	cmp	lr, r2	@ tmp257, tmp256
	movls	r2, #32	@ level,
	bhi	.L688	@,
.L569:
	ldr	ip, [fp, #12]	@, UserDec
	cmp	ip, #1	@,
	beq	.L689	@,
	cmp	r9, #16	@ VidStd,
	beq	.L690	@,
	ldr	r1, [fp, #-72]	@, %sfp
	add	r0, r0, #251904	@, D.51983,
	add	r0, r0, #216	@,,
	str	r2, [fp, #-88]	@,
	add	r9, r1, #31	@,,
	mov	r1, #948	@,
	str	r9, [fp, #-72]	@, %sfp
	mov	ip, r9, asr #5	@ tmp299,,
	str	r3, [fp, #-84]	@,
	movw	r9, #:lower16:252120	@ tmp312,
	movt	r9, #:upper16:252120	@ tmp312,
	add	lr, ip, ip, asl #1	@, tmp302, tmp299, tmp299,
	mov	ip, lr, asl #5	@ tmp303, tmp302,
	mul	lr, ip, r5	@ tmp306, tmp303, SlotWidth
	mul	ip, ip, r2	@, tmp303, level
	str	ip, [fp, #-64]	@, %sfp
	mov	ip, lr, asr #1	@ tmp310, tmp306,
	ldr	lr, [fp, #-64]	@, %sfp
	add	ip, ip, lr, asr #1	@,, tmp310,,
	str	ip, [fp, #-64]	@, %sfp
	bl	__memzero	@
	ldr	r3, [fp, #-84]	@,
	ldr	lr, [r6, r4, asl #2]	@ tmp314, s_pstVfmwChan
	movw	r1, #:lower16:253052	@ tmp315,
	movt	r1, #:upper16:253052	@ tmp315,
	mov	r2, r5, asl #4	@ tmp322, SlotWidth,
	mov	ip, r3, asr #1	@ tmp318, PmvSlotLen,
	str	ip, [lr, r1]	@ tmp318, <variable>.stMemArrangeInfo.stMemArrange.HafPmvOffset
	ldr	r0, [r6, r4, asl #2]	@ tmp320, s_pstVfmwChan
	str	r2, [r0, r9]	@ tmp322, <variable>.stMemArrangeInfo.stMemArrange.VahbStride
	ldr	r2, [fp, #-88]	@,
.L575:
	add	lr, r2, r5	@ tmp333, level, SlotWidth
	ldr	r5, [fp, #-72]	@, %sfp
	ldr	r9, [r6, r4, asl #2]	@ tmp328, s_pstVfmwChan
	movw	r0, #:lower16:252656	@ tmp329,
	bic	ip, r5, #31	@ tmp332,,
	movt	r0, #:upper16:252656	@ tmp329,
	mul	r1, lr, ip	@ tmp334, tmp333, tmp332
	str	r1, [r9, r0]	@ tmp334, <variable>.stMemArrangeInfo.stMemArrange.ChromOffset
.L577:
	ldr	r2, [r6, r4, asl #2]	@ tmp336, s_pstVfmwChan
	movw	r0, #:lower16:253060	@ tmp337,
	ldr	r5, [fp, #-64]	@, %sfp
	movt	r0, #:upper16:253060	@ tmp337,
	ldr	r1, [fp, #-64]	@, %sfp
	add	r9, r3, #1056	@ tmp341, PmvSlotLen,
	str	r5, [r2, r0]	@, <variable>.stMemArrangeInfo.ImgSlotLen
	adds	r9, r9, r1	@ CurFsSize, tmp341,
	ldr	lr, [r6, r4, asl #2]	@ tmp339, s_pstVfmwChan
	movw	r1, #:lower16:253064	@ tmp340,
	movt	r1, #:upper16:253064	@ tmp340,
	movw	r2, #:lower16:s_pstVfmwChan	@ tmp335,
	movt	r2, #:upper16:s_pstVfmwChan	@ tmp335,
	str	r3, [lr, r1]	@ PmvSlotLen, <variable>.stMemArrangeInfo.PmvSlotLen
	bmi	.L563	@,
	ldr	r5, [r2, r4, asl #2]	@ prephitmp.1780, s_pstVfmwChan
	movw	ip, #:lower16:250812	@ tmp344,
	movt	ip, #:upper16:250812	@ tmp344,
	ldr	lr, [fp, #-76]	@, %sfp
	ldr	r3, [r5, ip]	@, <variable>.s32RefNum
	cmp	lr, r9	@, CurFsSize
	str	r3, [fp, #-64]	@, %sfp
	beq	.L691	@,
.L580:
	movw	r2, #:lower16:250808	@ tmp347,
	movw	r0, #:lower16:g_event_report	@ tmp348,
	movt	r2, #:upper16:250808	@ tmp347,
	movt	r0, #:upper16:g_event_report	@ tmp348,
	str	r9, [r5, r2]	@ CurFsSize, <variable>.s32CurFsSize
	ldr	ip, [r0, #0]	@ g_event_report.453, g_event_report
	cmp	ip, #0	@ g_event_report.453,
	beq	.L582	@,
	ldr	r5, [fp, #-64]	@, %sfp
	mov	r0, r4	@, eFlag
	str	r7, [fp, #-52]	@ Width, para
	mov	r1, #118	@,
	str	sl, [fp, #-48]	@ Height, para
	sub	r2, fp, #60	@,,
	str	r5, [fp, #-60]	@, para
	mov	r3, #16	@,
	str	r9, [fp, #-56]	@ CurFsSize, para
	blx	ip	@ g_event_report.453
.L582:
	ldr	r5, [r6, r4, asl #2]	@ tmp352, s_pstVfmwChan
	movw	r1, #:lower16:250832	@ tmp353,
	movt	r1, #:upper16:250832	@ tmp353,
	mov	r2, r9	@, CurFsSize
	ldr	r3, [fp, #-64]	@, %sfp
	mov	r0, #31	@,
	ldr	lr, [r5, r1]	@ <variable>.s32RefNumChanged, <variable>.s32RefNumChanged
	movw	r1, #:lower16:.LC50	@,
	movt	r1, #:upper16:.LC50	@,
	str	lr, [sp, #0]	@ <variable>.s32RefNumChanged,
	bl	dprint_vfmw	@
	ldr	r5, [r6, r4, asl #2]	@ temp.1827, s_pstVfmwChan
	bl	OSAL_GetTimeInMs	@
	movw	ip, #:lower16:253068	@ tmp356,
	movt	ip, #:upper16:253068	@ tmp356,
	movw	r2, #:lower16:250800	@ tmp359,
	movt	r2, #:upper16:250800	@ tmp359,
	mov	r3, #2	@ ret,
	str	r0, [r5, ip]	@, <variable>.stDynamicFSTimestamp.u32StartTime
	mov	ip, #1	@ tmp360,
	ldr	r1, [r6, r4, asl #2]	@ tmp358, s_pstVfmwChan
	str	ip, [r1, r2]	@ tmp360, <variable>.FspInst.eFspPartitionState
	b	.L579	@
.L681:
	add	r0, sl, sl, asl #1	@, tmp489, Height, Height,
	mul	r7, r2, r0	@ tmp490, SlotWidth, tmp489
	mov	r7, r7, asr #1	@ ImgSlotLen, tmp490,
	b	.L613	@
.L599:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L693	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC11	@,
	movt	r3, #:upper16:.LC11	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L579	@
.L688:
	sub	ip, r1, #4096	@ tmp260, ImgWidthInPixAln,
	sub	lr, ip, #1	@ tmp260, tmp260,
	cmp	lr, r2	@ tmp260, tmp256
	movls	r2, #48	@ level,
	bls	.L569	@,
	sub	lr, r1, #6144	@ tmp263, ImgWidthInPixAln,
	sub	r1, lr, #1	@ tmp263, tmp263,
	cmp	r1, r2	@ tmp263, tmp256
	movls	r2, #64	@ level,
	movhi	r2, #0	@ level,
	b	.L569	@
.L567:
	mul	ip, r3, r1	@ tmp592, ImgHeightInMb, ImgWidthInPixAln
	add	r5, r7, #255	@ tmp594, Width,
	bic	r5, r5, #255	@ SlotWidth, tmp594,
	add	r2, ip, #127	@ tmp593, tmp592,
	bic	r3, r2, #127	@ PmvSlotLen, tmp593,
	b	.L633	@
.L691:
	movw	ip, #:lower16:250832	@ tmp345,
	movt	ip, #:upper16:250832	@ tmp345,
	ldr	r3, [r5, ip]	@ <variable>.s32RefNumChanged, <variable>.s32RefNumChanged
	cmp	r3, #1	@ <variable>.s32RefNumChanged,
	beq	.L580	@,
	cmp	r8, #0	@ pVdmMemArrange,
	beq	.L692	@,
	ldr	r3, [fp, #-64]	@, %sfp
	ldr	r7, [r5, r1]	@, <variable>.stMemArrangeInfo.PmvSlotLen
	cmp	r3, #0	@,
	ldr	sl, [r5, r0]	@ ImgSlotLen, <variable>.stMemArrangeInfo.ImgSlotLen
	movne	r3, r5	@ prephitmp.1881, prephitmp.1780
	str	r7, [fp, #-64]	@, %sfp
	bne	.L585	@,
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	str	r2, [fp, #-88]	@,
	bl	dprint_vfmw	@
	ldr	r0, [fp, #-88]	@,
	ldr	r3, [r0, r4, asl #2]	@ prephitmp.1881, s_pstVfmwChan
.L585:
	movw	r7, #:lower16:250816	@ tmp369,
	movt	r7, #:upper16:250816	@ tmp369,
	ldr	r2, [r3, r7]	@ prephitmp.1782, <variable>.s32NeededFrameNum
	cmp	r2, #30	@ prephitmp.1782,
	ble	.L586	@,
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC53	@,
	movt	r1, #:upper16:.LC53	@,
	bl	dprint_vfmw	@
	ldr	ip, [r6, r4, asl #2]	@ tmp372, s_pstVfmwChan
	mov	r2, #30	@ tmp374,
	str	r2, [ip, r7]	@ tmp374, <variable>.s32NeededFrameNum
	ldr	r3, [r6, r4, asl #2]	@ tmp376, s_pstVfmwChan
	ldr	r2, [r3, r7]	@ prephitmp.1782, <variable>.s32NeededFrameNum
.L586:
	movw	lr, #:lower16:252668	@ tmp378,
	cmp	r2, #0	@ prephitmp.1782,
	movt	lr, #:upper16:252668	@ tmp378,
	str	r2, [r5, lr]	@ prephitmp.1782, <variable>.stMemArrangeInfo.stMemArrange.ValidFrameNum
	ble	.L587	@,
	ldr	r0, [r6, r4, asl #2]	@ temp.1882, s_pstVfmwChan
	movw	r7, #:lower16:250848	@ tmp380,
	movt	r7, #:upper16:250848	@ tmp380,
	movw	r1, #:lower16:s_pstVfmwChan	@ tmp379,
	movt	r1, #:upper16:s_pstVfmwChan	@ tmp379,
	ldr	ip, [r0, r7]	@ s32PhyAddr, <variable>.stFrameBuffer.PhyAddr
	cmp	ip, #0	@ s32PhyAddr,
	beq	.L588	@,
	add	r3, ip, #1020	@ tmp381, s32PhyAddr,
	movw	r7, #:lower16:252128	@ tmp385,
	add	lr, r3, #3	@ tmp381, tmp381,
	movt	r7, #:upper16:252128	@ tmp385,
	bic	r0, lr, #1020	@ tmp383, tmp381,
	movw	lr, #:lower16:252384	@ tmp387,
	bic	r3, r0, #3	@ tmp383, tmp383,
	movt	lr, #:upper16:252384	@ tmp387,
	rsb	r9, ip, r3	@ s32Offset.1885, s32PhyAddr, tmp383
	movw	r0, #:lower16:252932	@ tmp389,
	add	r9, r9, sl	@, s32Offset.1885, ImgSlotLen
	str	r9, [fp, #-68]	@, %sfp
	add	r9, r9, #32	@,,
	str	r9, [fp, #-72]	@, %sfp
	str	r3, [r5, r7]	@ tmp383, <variable>.stMemArrangeInfo.stMemArrange.FrameAddr
	movt	r0, #:upper16:252932	@ tmp389,
	ldr	r7, [fp, #-68]	@, %sfp
	add	r9, r7, ip	@ tmp388,, s32PhyAddr
	str	r9, [r5, lr]	@ tmp388, <variable>.stMemArrangeInfo.stMemArrange.LineNumAddr
	ldr	r9, [fp, #-72]	@, %sfp
	add	r3, r9, ip	@ tmp390,, s32PhyAddr
	str	r3, [r5, r0]	@ tmp390, <variable>.stMemArrangeInfo.stMemArrange.PMVAddr
	ldr	r1, [r1, r4, asl #2]	@ D.55159, s_pstVfmwChan
	movw	r3, #:lower16:250808	@ tmp392,
	movt	r3, #:upper16:250808	@ tmp392,
	ldr	r0, [fp, #-64]	@, %sfp
	ldr	lr, [r1, r3]	@ prephitmp.1784, <variable>.s32CurFsSize
	add	r7, r9, r0	@ s32Offset.1865,,
	cmp	r7, lr	@ s32Offset.1865, prephitmp.1784
	movgt	r3, #0	@ i,
	bgt	.L590	@,
	tst	r2, #1	@ prephitmp.1782,
	add	ip, r5, #251904	@ ivtmp.1820, prephitmp.1780,
	add	r0, ip, #228	@ ivtmp.1820, ivtmp.1820,
	mov	r3, #0	@ i,
	bne	.L672	@,
	add	ip, r1, #249856	@ tmp665, D.55159,
	mov	r3, #1	@ i,
	add	lr, ip, #1012	@ tmp665, tmp665,
	ldr	ip, [lr, #0]	@ s32PhyAddr, <variable>.stFrameBuffer.PhyAddr
	cmp	ip, #0	@ s32PhyAddr,
	beq	.L664	@,
	add	r7, ip, #1020	@ tmp666, s32PhyAddr,
	add	r9, r7, #3	@ tmp667, tmp666,
	bic	lr, r9, #1020	@ tmp668, tmp667,
	bic	r1, lr, #3	@ tmp668, tmp668,
	str	r1, [r0, #0]	@ tmp668, <variable>.stMemArrangeInfo.stMemArrange.FrameAddr
	rsb	r7, ip, r1	@ s32Offset, s32PhyAddr, tmp668
	add	r9, r7, sl	@ s32Offset.1861, s32Offset, ImgSlotLen
	add	r7, r9, #32	@ s32Offset.1863, s32Offset.1861,
	add	lr, r9, ip	@ tmp672, s32Offset.1861, s32PhyAddr
	add	r1, r7, ip	@ tmp674, s32Offset.1863, s32PhyAddr
	str	lr, [r0, #256]	@ tmp672, <variable>.stMemArrangeInfo.stMemArrange.LineNumAddr
	str	r1, [r0, #804]	@ tmp674, <variable>.stMemArrangeInfo.stMemArrange.PMVAddr
	add	r0, r0, #4	@ ivtmp.1820, ivtmp.1820,
	ldr	r9, [fp, #-64]	@, %sfp
	ldr	r1, [r6, r4, asl #2]	@ D.55159, s_pstVfmwChan
	add	r7, r7, r9	@ s32Offset.1865, s32Offset.1863,
	movw	r9, #:lower16:250808	@,
	movt	r9, #:upper16:250808	@,
	ldr	lr, [r1, r9]	@ prephitmp.1784, <variable>.s32CurFsSize
	cmp	r7, lr	@ s32Offset.1865, prephitmp.1784
	bgt	.L590	@,
.L672:
	str	r5, [fp, #-68]	@ prephitmp.1780, %sfp
	b	.L591	@
.L593:
	add	ip, r1, ip, asl #2	@, tmp399, D.55159, tmp397,
	add	lr, ip, #249856	@ tmp400, tmp399,
	add	ip, lr, #992	@ tmp400, tmp400,
	ldr	ip, [ip, #0]	@ s32PhyAddr, <variable>.stFrameBuffer.PhyAddr
	add	lr, ip, #1020	@ tmp402, s32PhyAddr,
	cmp	ip, #0	@ s32PhyAddr,
	add	lr, lr, #3	@ tmp402, tmp402,
	bic	lr, lr, #1020	@ tmp404, tmp402,
	beq	.L664	@,
	bic	r7, lr, #3	@ tmp404, tmp404,
	str	r7, [r0, #0]	@ tmp404, <variable>.stMemArrangeInfo.stMemArrange.FrameAddr
	rsb	r5, ip, r7	@ s32Offset, s32PhyAddr, tmp404
	add	r1, r5, sl	@ s32Offset.1861, s32Offset, ImgSlotLen
	add	r5, r1, #32	@ s32Offset.1863, s32Offset.1861,
	add	lr, r1, ip	@ tmp407, s32Offset.1861, s32PhyAddr
	add	r7, r5, ip	@ tmp408, s32Offset.1863, s32PhyAddr
	str	lr, [r0, #256]	@ tmp407, <variable>.stMemArrangeInfo.stMemArrange.LineNumAddr
	str	r7, [r0, #804]	@ tmp408, <variable>.stMemArrangeInfo.stMemArrange.PMVAddr
	add	r0, r9, #4	@ ivtmp.1820, tmp635,
	ldr	r1, [fp, #-64]	@, %sfp
	add	r7, r5, r1	@ s32Offset.1865, s32Offset.1863,
	ldr	r1, [r6, r4, asl #2]	@ D.55159, s_pstVfmwChan
	movw	r5, #:lower16:250808	@,
	movt	r5, #:upper16:250808	@,
	ldr	lr, [r1, r5]	@ prephitmp.1784, <variable>.s32CurFsSize
	cmp	r7, lr	@ s32Offset.1865, prephitmp.1784
	bgt	.L590	@,
	add	r3, r3, #1	@ i, i,
	add	lr, r3, r3, asl #2	@, tmp678, i, i,
	add	ip, r1, lr, asl #2	@, tmp680, D.55159, tmp678,
	add	lr, ip, #249856	@ tmp681, tmp680,
	add	ip, lr, #992	@ tmp681, tmp681,
	ldr	ip, [ip, #0]	@ s32PhyAddr, <variable>.stFrameBuffer.PhyAddr
	add	lr, ip, #1020	@ tmp683, s32PhyAddr,
	cmp	ip, #0	@ s32PhyAddr,
	add	lr, lr, #3	@ tmp683, tmp683,
	bic	lr, lr, #1020	@ tmp684, tmp683,
	beq	.L664	@,
	bic	r7, lr, #3	@ tmp684, tmp684,
	str	r7, [r9, #0]	@ tmp684, <variable>.stMemArrangeInfo.stMemArrange.FrameAddr
	rsb	r5, ip, r7	@ s32Offset, s32PhyAddr, tmp684
	add	r1, r5, sl	@ s32Offset.1861, s32Offset, ImgSlotLen
	add	r5, r1, #32	@ s32Offset.1863, s32Offset.1861,
	add	lr, r1, ip	@ tmp688, s32Offset.1861, s32PhyAddr
	add	r7, r5, ip	@ tmp690, s32Offset.1863, s32PhyAddr
	str	lr, [r9, #256]	@ tmp688, <variable>.stMemArrangeInfo.stMemArrange.LineNumAddr
	str	r7, [r9, #804]	@ tmp690, <variable>.stMemArrangeInfo.stMemArrange.PMVAddr
	ldr	r1, [fp, #-64]	@, %sfp
	add	r7, r5, r1	@ s32Offset.1865, s32Offset.1863,
	ldr	r1, [r6, r4, asl #2]	@ D.55159, s_pstVfmwChan
	movw	r5, #:lower16:250808	@,
	movt	r5, #:upper16:250808	@,
	ldr	lr, [r1, r5]	@ prephitmp.1784, <variable>.s32CurFsSize
	cmp	r7, lr	@ s32Offset.1865, prephitmp.1784
	bgt	.L590	@,
.L591:
	add	r3, r3, #1	@ i, i,
	add	r9, r0, #4	@ tmp635, ivtmp.1820,
	cmp	r3, r2	@ i, prephitmp.1782
	add	ip, r3, r3, asl #2	@, tmp397, i, i,
	blt	.L593	@,
	ldr	r5, [fp, #-68]	@ prephitmp.1780, %sfp
	b	.L594	@
.L689:
	ldr	r1, [fp, #-72]	@, %sfp
	mov	ip, #3	@ tmp267,
	add	r0, r0, #251904	@, D.51983,
	str	r2, [fp, #-88]	@,
	add	r0, r0, #216	@,,
	str	r3, [fp, #-84]	@,
	mul	lr, ip, r1	@ tmp266, tmp267,
	mov	r1, #948	@,
	movw	ip, #:lower16:252120	@ tmp269,
	movt	ip, #:upper16:252120	@ tmp269,
	str	ip, [fp, #-92]	@,
	mul	lr, r5, lr	@, SlotWidth, tmp266
	str	lr, [fp, #-64]	@, %sfp
	bl	__memzero	@
	ldr	r3, [fp, #-84]	@,
	movw	r0, #:lower16:253052	@ tmp272,
	ldr	lr, [r6, r4, asl #2]	@ tmp271, s_pstVfmwChan
	movt	r0, #:upper16:253052	@ tmp272,
	cmp	r9, #16	@ VidStd,
	mov	ip, r3, asr #1	@ tmp275, PmvSlotLen,
	str	ip, [lr, r0]	@ tmp275, <variable>.stMemArrangeInfo.stMemArrange.HafPmvOffset
	mov	r0, r5, asl #4	@ tmp279, SlotWidth,
	ldr	r2, [r6, r4, asl #2]	@ tmp277, s_pstVfmwChan
	ldr	r1, [fp, #-92]	@,
	str	r0, [r2, r1]	@ tmp279, <variable>.stMemArrangeInfo.stMemArrange.VahbStride
	ldrne	r9, [fp, #-72]	@, %sfp
	ldr	r2, [fp, #-88]	@,
	addne	r9, r9, #31	@,,
	strne	r9, [fp, #-72]	@, %sfp
	bne	.L575	@,
.L574:
	mul	r5, sl, r5	@ tmp326, Height, SlotWidth
	ldr	lr, [r6, r4, asl #2]	@ tmp324, s_pstVfmwChan
	movw	r2, #:lower16:252656	@ tmp325,
	movt	r2, #:upper16:252656	@ tmp325,
	str	r5, [lr, r2]	@ tmp326, <variable>.stMemArrangeInfo.stMemArrange.ChromOffset
	b	.L577	@
.L690:
	mov	r9, #3	@ tmp281,
	add	r1, r0, #251904	@, D.51983,
	mul	ip, r9, sl	@ tmp280, tmp281, Height
	add	r0, r1, #216	@,,
	mov	r1, #948	@,
	str	r3, [fp, #-84]	@,
	movw	r9, #:lower16:252120	@ tmp287,
	movt	r9, #:upper16:252120	@ tmp287,
	mul	r2, r5, ip	@ tmp282, SlotWidth, tmp280
	mov	lr, r2, asr #1	@, tmp282,
	str	lr, [fp, #-64]	@, %sfp
	bl	__memzero	@
	ldr	r3, [fp, #-84]	@,
	ldr	ip, [r6, r4, asl #2]	@ tmp289, s_pstVfmwChan
	movw	r2, #:lower16:253052	@ tmp290,
	movt	r2, #:upper16:253052	@ tmp290,
	mov	r1, r5, asl #4	@ tmp297, SlotWidth,
	mov	r0, r3, asr #1	@ tmp293, PmvSlotLen,
	str	r0, [ip, r2]	@ tmp293, <variable>.stMemArrangeInfo.stMemArrange.HafPmvOffset
	ldr	r2, [r6, r4, asl #2]	@ tmp295, s_pstVfmwChan
	str	r1, [r2, r9]	@ tmp297, <variable>.stMemArrangeInfo.stMemArrange.VahbStride
	b	.L574	@
.L679:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L693	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC13	@,
	movt	r3, #:upper16:.LC13	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L579	@
.L677:
	mov	r0, r5	@, MemAddr
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L693	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC55	@,
	movt	r3, #:upper16:.LC55	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L579	@
.L687:
	mla	r4, r7, r0, r4	@ Offset.1847, ImgSlotLen, D.52154, Offset
	b	.L634	@
.L685:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L693	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC57	@,
	movt	r3, #:upper16:.LC57	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L579	@
.L678:
	mov	r0, r8	@, pVdmMemArrange
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L693	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC12	@,
	movt	r3, #:upper16:.LC12	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L579	@
.L682:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC56	@,
	movt	r1, #:upper16:.LC56	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L579	@
.L664:
	movw	r2, #:lower16:250808	@ tmp401,
	movt	r2, #:upper16:250808	@ tmp401,
	ldr	lr, [r1, r2]	@ prephitmp.1784, <variable>.s32CurFsSize
.L590:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC54	@,
	ldr	r2, .L693+4	@,
	movt	r1, #:upper16:.LC54	@,
	stmia	sp, {r7, lr}	@ phole stm
	str	ip, [sp, #8]	@ s32PhyAddr,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L579	@
.L561:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L693+8	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC11	@,
	movt	r3, #:upper16:.LC11	@,
	bl	dprint_vfmw	@
	mvn	r9, #0	@ CurFsSize,
.L563:
	mov	r2, r9	@, CurFsSize
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC49	@,
	movt	r1, #:upper16:.LC49	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L579	@
.L588:
	movw	r2, #:lower16:250808	@ tmp411,
	movt	r2, #:upper16:250808	@ tmp411,
	mov	r3, ip	@ i, s32PhyAddr
	mov	r7, ip	@ s32Offset.1865, s32PhyAddr
	ldr	lr, [r0, r2]	@ prephitmp.1784, <variable>.s32CurFsSize
	b	.L590	@
.L587:
	ldr	r1, [r6, r4, asl #2]	@ D.55159, s_pstVfmwChan
.L594:
	movw	r0, #:lower16:250808	@ tmp597,
	movt	r0, #:upper16:250808	@ tmp597,
	movw	r3, #:lower16:252124	@ tmp596,
	movw	lr, #:lower16:253056	@ tmp600,
	ldr	ip, [r1, r0]	@ <variable>.s32CurFsSize, <variable>.s32CurFsSize
	movt	r3, #:upper16:252124	@ tmp596,
	movt	lr, #:upper16:253056	@ tmp600,
	add	r1, r5, #251904	@, prephitmp.1780,
	mov	r0, r8	@, pVdmMemArrange
	add	r1, r1, #216	@,,
	mul	ip, ip, r2	@ tmp599, <variable>.s32CurFsSize, prephitmp.1782
	str	r2, [r5, lr]	@ prephitmp.1782, <variable>.stMemArrangeInfo.stMemArrange.ValidPMVNum
	mov	r2, #940	@,
	str	ip, [r5, r3]	@ tmp599, <variable>.stMemArrangeInfo.stMemArrange.TotalMemUsed
	bl	memcpy	@
	mov	r3, #0	@ ret,
	b	.L579	@
.L692:
	mov	r0, r8	@, pVdmMemArrange
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L693+4	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC51	@,
	movt	r3, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L579	@
.L694:
	.align	2
.L693:
	.word	.LANCHOR0+532
	.word	.LANCHOR0+496
	.word	.LANCHOR0+468
	.fnend
	.size	VDMHAL_V300R001_ArrangeMem, .-VDMHAL_V300R001_ArrangeMem
	.align	2
	.global	VDMHAL_V300R001_OpenHAL
	.type	VDMHAL_V300R001_OpenHAL, %function
VDMHAL_V300R001_OpenHAL:
	.fnstart
.LFB1529:
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
	subs	r2, r0, #0	@ pOpenParam, pOpenParam
	beq	.L712	@,
	ldr	r5, [r2, #0]	@ MemBaseAddr, <variable>.MemBaseAddr
	ldr	r3, [r2, #8]	@ VdhId, <variable>.VdhId
	cmp	r5, #0	@ MemBaseAddr,
	ldr	r6, [r2, #4]	@ Size, <variable>.Size
	beq	.L713	@,
	movw	r2, #:lower16:4296703	@ tmp187,
	movt	r2, #:upper16:4296703	@ tmp187,
	cmp	r6, r2	@ Size, tmp187
	ble	.L714	@,
	cmp	r3, #1	@ VdhId,
	bhi	.L715	@,
	beq	.L716	@,
	movw	r4, #:lower16:g_HwMem	@ tmp259,
	movt	r4, #:upper16:g_HwMem	@ tmp259,
	movw	r1, #1208	@,
	add	sl, r5, #1020	@ tmp205, MemBaseAddr,
	mov	r0, r4	@, tmp259
	add	r9, r6, r5	@ tmp210, Size, MemBaseAddr
	bl	__memzero	@
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	movw	r1, #:lower16:.LC63	@,
	movt	r1, #:upper16:.LC63	@,
	mov	ip, r0	@ D.51717,
	mov	r2, r0	@, D.51717
	str	ip, [r4, #0]	@ D.51717, <variable>.pVdmRegVirAddr
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:-121241600	@,
	movt	r0, #:upper16:-121241600	@,
	bl	MEM_Phy2Vir	@
	movw	r1, #:lower16:.LC64	@,
	movt	r1, #:upper16:.LC64	@,
	mov	r7, r0	@ D.51721,
	mov	r2, r0	@, D.51721
	str	r7, [r4, #8]	@ D.51721, <variable>.pBpdRegVirAddr
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	add	r3, sl, #3	@ tmp205, tmp205,
	bic	r0, r3, #1020	@ D.51726, tmp205,
	movw	r7, #:lower16:268800	@ tmp261,
	movt	r7, #:upper16:268800	@ tmp261,
	bic	r0, r0, #3	@ D.51726, D.51726,
	mov	r2, r4	@ ivtmp.1926, tmp259
	mov	r3, #0	@ ivtmp.1923,
	rsb	r8, r0, r9	@ tmp211, D.51726, tmp210
	mov	r1, #1024	@ tmp213,
	str	r8, [r4, #20]	@ tmp211, <variable>.HALMemSize
	str	r1, [r4, #24]	@ tmp213, <variable>.VahbStride
	str	r0, [r4, #16]	@ D.51726, <variable>.HALMemBaseAddr
.L703:
	add	r9, r3, r0	@ tmp215, ivtmp.1923, D.51726
	add	r8, r3, #1280	@ tmp262, ivtmp.1923,
	add	r3, r3, #2560	@ ivtmp.1923, ivtmp.1923,
	add	r1, r2, #4	@ tmp263, ivtmp.1926,
	cmp	r3, r7	@ ivtmp.1923, tmp261
	str	r9, [r2, #32]	@ tmp215, <variable>.MsgSlotAddr
	add	lr, r8, r0	@ tmp266, tmp262, D.51726
	add	r2, r1, #4	@ ivtmp.1926, tmp263,
	str	lr, [r1, #32]	@ tmp266, <variable>.MsgSlotAddr
	bne	.L703	@,
	add	r0, r0, r3	@ PhyAddr.1929, D.51726, ivtmp.1923
	movw	r3, #:lower16:1081343	@ D.51733,
	add	r7, r0, #5120	@ PhyAddr.1930, PhyAddr.1929,
	movt	r3, #:upper16:1081343	@ D.51733,
	add	r8, r7, r3	@ D.51733, PhyAddr.1930, D.51733
	mov	r9, #210	@ tmp219,
	bic	sl, r8, #32512	@ PhyAddr.1931, D.51733,
	str	r7, [r4, #1100]	@ PhyAddr.1930, <variable>.mn_phy_addr
	bic	r1, sl, #255	@ PhyAddr.1931, PhyAddr.1931,
	str	r9, [r4, #1056]	@ tmp219, <variable>.ValidMsgSlotNum
	add	ip, r1, #191488	@ PhyAddr.1935, PhyAddr.1931,
	add	r3, r1, #2850816	@ PhyAddr_HEVC.1944, PhyAddr.1931,
	add	r2, ip, #158720	@ PhyAddr.1940, PhyAddr.1935,
	add	sl, r1, #78848	@ PhyAddr.1933, PhyAddr.1931,
	cmp	r2, r3	@ PhyAddr.1940, PhyAddr_HEVC.1944
	rsbge	r2, r5, r2	@,, D.51744, MemBaseAddr, PhyAddr.1940
	rsblt	r2, r5, r3	@,, D.51744, MemBaseAddr, PhyAddr_HEVC.1944
	add	r8, ip, #121856	@ PhyAddr.1938, PhyAddr.1935,
	cmp	r6, r2	@ Size, D.51744
	add	r7, r1, #589824	@ PhyAddr_HEVC, PhyAddr.1931,
	add	r5, r1, #1212416	@ PhyAddr_HEVC.1942, PhyAddr.1931,
	add	lr, r1, #1802240	@ PhyAddr_HEVC.1943, PhyAddr.1931,
	add	r9, r1, #33792	@ PhyAddr.1932, PhyAddr.1931,
	str	r1, [r4, #1136]	@ PhyAddr.1931, <variable>.SedTopAddr
	str	ip, [r4, #1156]	@ PhyAddr.1935, <variable>.PpfdBufAddr
	str	r1, [r4, #1084]	@ PhyAddr.1931, <variable>.sed_top_phy_addr
	str	r1, [r4, #1088]	@ PhyAddr.1931, <variable>.pmv_top_phy_addr
	str	r1, [r4, #1092]	@ PhyAddr.1931, <variable>.pmv_left_phy_addr
	str	r9, [r4, #1140]	@ PhyAddr.1932, <variable>.PmvTopAddr
	add	r9, r1, #123904	@ PhyAddr.1934, PhyAddr.1931,
	str	r0, [r4, #1080]	@ PhyAddr.1929, <variable>.H264MnAddr
	str	r9, [r4, #1152]	@ PhyAddr.1934, <variable>.DblkTopAddr
	movw	r9, #799	@ tmp231,
	str	sl, [r4, #1148]	@ PhyAddr.1933, <variable>.ItransTopAddr
	str	r9, [r4, #1160]	@ tmp231, <variable>.PpfdBufLen
	add	r9, ip, #102400	@ PhyAddr.1936, PhyAddr.1935,
	str	r8, [r4, #1180]	@ PhyAddr.1938, <variable>.Vp8TabAddr
	str	r9, [r4, #1168]	@ PhyAddr.1936, <variable>.IntensityConvTabAddr
	add	r9, ip, #105472	@ PhyAddr.1937, PhyAddr.1935,
	str	r7, [r4, #1104]	@ PhyAddr_HEVC, <variable>.tile_segment_info_phy_addr
	add	ip, ip, #154624	@ PhyAddr.1939, PhyAddr.1935,
	str	r5, [r4, #1116]	@ PhyAddr_HEVC.1942, <variable>.sao_left_phy_addr
	str	ip, [r4, #1176]	@ PhyAddr.1939, <variable>.Vp6TabAddr
	add	ip, r1, #622592	@ PhyAddr_HEVC.1941, PhyAddr.1931,
	str	lr, [r4, #1124]	@ PhyAddr_HEVC.1943, <variable>.upmsgslot_phy_addr
	mov	r1, #0	@ tmp249,
	str	r9, [r4, #1172]	@ PhyAddr.1937, <variable>.BitplaneInfoAddr
	str	ip, [r4, #1108]	@ PhyAddr_HEVC.1941, <variable>.dblk_left_phy_addr
	str	sl, [r4, #1144]	@ PhyAddr.1933, <variable>.RcnTopAddr
	str	r8, [r4, #1184]	@ PhyAddr.1938, <variable>.DnrMbInfoAddr
	str	r7, [r4, #1096]	@ PhyAddr_HEVC, <variable>.rcn_top_phy_addr
	str	r5, [r4, #1112]	@ PhyAddr_HEVC.1942, <variable>.dblk_top_phy_addr
	str	lr, [r4, #1120]	@ PhyAddr_HEVC.1943, <variable>.sao_top_phy_addr
	str	r3, [r4, #1128]	@ PhyAddr_HEVC.1944, <variable>.ppfd_phy_addr
	str	r1, [r4, #1132]	@ tmp249, <variable>.ppfd_buf_len
	blt	.L704	@,
	bl	H264HAL_V300R001_InitHal	@
	subs	r5, r0, #0	@ D.51748,
	ldr	r0, [r4, #1100]	@, <variable>.mn_phy_addr
	mvnne	r5, #0	@, Ret,
	bl	HEVCHAL_V300R001_InitHal	@
	cmp	r0, #0	@,
	ldr	r0, [r4, #1080]	@, <variable>.H264MnAddr
	moveq	r4, r5	@, Ret, Ret
	mvnne	r4, #0	@, Ret,
	bl	H264HAL_V300R001_InitHal	@
	cmp	r0, #0	@,
	moveq	r0, r4	@, Ret, Ret
	mvnne	r0, #0	@, Ret,
.L697:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L716:
	mov	ip, #0	@ tmp197,
	movw	r1, #:lower16:.LC15	@,
	mov	r0, ip	@, tmp197
	movt	r1, #:upper16:.LC15	@,
	ldr	r2, .L717	@,
	str	ip, [sp, #0]	@ tmp197,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	b	.L697	@
.L715:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC62	@,
	movt	r1, #:upper16:.LC62	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	b	.L697	@
.L704:
	mov	r0, r1	@, tmp249
	mov	r3, r6	@, Size
	movw	r1, #:lower16:.LC65	@,
	movt	r1, #:upper16:.LC65	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	b	.L697	@
.L713:
	mov	r0, r5	@, MemBaseAddr
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L717	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC60	@,
	movt	r3, #:upper16:.LC60	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	b	.L697	@
.L714:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L717	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC61	@,
	movt	r3, #:upper16:.LC61	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	b	.L697	@
.L712:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L717	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC59	@,
	movt	r3, #:upper16:.LC59	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	b	.L697	@
.L718:
	.align	2
.L717:
	.word	.LANCHOR0+560
	.fnend
	.size	VDMHAL_V300R001_OpenHAL, .-VDMHAL_V300R001_OpenHAL
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.52685, %object
	.size	__func__.52685, 25
__func__.52685:
	.ascii	"VDMHAL_V300R001_IsVdmRun\000"
	.space	3
	.type	__func__.52666, %object
	.size	__func__.52666, 27
__func__.52666:
	.ascii	"VDMHAL_V300R001_IsVdmReady\000"
	.space	1
	.type	__func__.52200, %object
	.size	__func__.52200, 31
__func__.52200:
	.ascii	"VDMHAL_V300R001_ArrangeMem_BTL\000"
	.space	1
	.type	__func__.53505, %object
	.size	__func__.53505, 30
__func__.53505:
	.ascii	"VDMHAL_V300R001_StartHwDecode\000"
	.space	2
	.type	__func__.53387, %object
	.size	__func__.53387, 30
__func__.53387:
	.ascii	"VDMHAL_V300R001_StartHwRepair\000"
	.space	2
	.type	__func__.53122, %object
	.size	__func__.53122, 25
__func__.53122:
	.ascii	"VDMHAL_V300R001_CfgRpReg\000"
	.space	3
	.type	__func__.52942, %object
	.size	__func__.52942, 25
__func__.52942:
	.ascii	"VDMHAL_V300R001_CfgRpMsg\000"
	.space	3
	.type	__func__.53328, %object
	.size	__func__.53328, 30
__func__.53328:
	.ascii	"VDMHAL_V300R001_PrepareRepair\000"
	.space	2
	.type	__func__.52714, %object
	.size	__func__.52714, 27
__func__.52714:
	.ascii	"VDMHAL_V300R001_BackupInfo\000"
	.space	1
	.type	__func__.52566, %object
	.size	__func__.52566, 25
__func__.52566:
	.ascii	"VDMHAL_V300R001_CheckReg\000"
	.space	3
	.type	__func__.52526, %object
	.size	__func__.52526, 26
__func__.52526:
	.ascii	"VDMHAL_V300R001_EnableInt\000"
	.space	2
	.type	__func__.52494, %object
	.size	__func__.52494, 24
__func__.52494:
	.ascii	"VDMHAL_V300R001_MaskInt\000"
	.type	__func__.52432, %object
	.size	__func__.52432, 30
__func__.52432:
	.ascii	"VDMHAL_V300R001_ClearIntState\000"
	.space	2
	.type	__func__.52355, %object
	.size	__func__.52355, 25
__func__.52355:
	.ascii	"VDMHAL_V300R001_ResetVdm\000"
	.space	3
	.type	__func__.53207, %object
	.size	__func__.53207, 30
__func__.53207:
	.ascii	"VDMHAL_V300R001_MakeDecReport\000"
	.space	2
	.type	__func__.52609, %object
	.size	__func__.52609, 27
__func__.52609:
	.ascii	"VDMHAL_V300R001_PrepareDec\000"
	.space	1
	.type	__func__.51795, %object
	.size	__func__.51795, 27
__func__.51795:
	.ascii	"VDMHAL_V300R001_CalcFsSize\000"
	.space	1
	.type	__func__.51892, %object
	.size	__func__.51892, 34
__func__.51892:
	.ascii	"VDMHAL_V300R001_FillVdmMemElement\000"
	.space	2
	.type	__func__.51961, %object
	.size	__func__.51961, 27
__func__.51961:
	.ascii	"VDMHAL_V300R001_ArrangeMem\000"
	.space	1
	.type	__func__.51686, %object
	.size	__func__.51686, 24
__func__.51686:
	.ascii	"VDMHAL_V300R001_OpenHAL\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"VDM register not mapped yet!\012\000"
	.space	2
.LC1:
	.ascii	"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000"
	.space	3
.LC2:
	.ascii	"%s: %s\012\000"
.LC3:
	.ascii	"VDM register not mapped yet!\000"
	.space	3
.LC4:
	.ascii	"WriteMsgSlot error!\012\000"
	.space	3
.LC5:
	.ascii	"ReadUpMsgSlot error! pDst=%p, pSrc=%p\012\000"
	.space	1
.LC6:
	.ascii	"ReadUpMsgSlot error! upmsg_size(%d) > 512\012\000"
	.space	1
.LC7:
	.ascii	"BigTile1d_y\000"
.LC8:
	.ascii	"failed mem_allocMemBlock BigTile_yuv save!\012\000"
.LC9:
	.ascii	"BigTile1d_uv\000"
	.space	3
.LC10:
	.ascii	"Mem addr is 0\000"
	.space	2
.LC11:
	.ascii	"image size out of range\000"
.LC12:
	.ascii	"'pVdmMemArrange' is NULL\000"
	.space	3
.LC13:
	.ascii	"MemSize not enough for pmv slot\000"
.LC14:
	.ascii	"VdhId is wrong! VDMHAL_V300R001_StartHwDecode\012\000"
	.space	1
.LC15:
	.ascii	"%s: VdhId(%d) > %d\012\000"
.LC16:
	.ascii	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000"
	.space	3
.LC17:
	.ascii	"VdhId is wrong! VDMHAL_V300_CfgRpReg\012\000"
	.space	2
.LC18:
	.ascii	"vdm register virtual address not mapped, reset fail"
	.ascii	"ed!\012\000"
.LC19:
	.ascii	"can not map repair msg virtual address!\000"
.LC20:
	.ascii	"ValidGroupNum=%d out of range!\012\000"
.LC21:
	.ascii	"align_mb error\012\000"
.LC22:
	.ascii	"VdhId is wrong! VDMHAL_V200R003_PrepareRepair\012\000"
	.space	1
.LC23:
	.ascii	"vdm register virtual address not mapped, VDMHAL_V20"
	.ascii	"0R003_PrepareRepair failed!\012\000"
.LC24:
	.ascii	"FIRST_REPAIR Parameter Error!\012\000"
	.space	1
.LC25:
	.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000"
	.space	1
.LC26:
	.ascii	"SECOND_REPAIR Parameter Error!\012\000"
.LC27:
	.ascii	"pBackUpInfo = NULL!\000"
.LC28:
	.ascii	"VdhId is wrong! VDMHAL_V300R001_BackupInfo\012\000"
.LC29:
	.ascii	"can NOT map vir addr for up-msg\000"
.LC30:
	.ascii	"%s: VdhId(%d) Invalid!\012\000"
.LC31:
	.ascii	"%s: VdhId is wrong!\012\000"
	.space	3
.LC32:
	.ascii	"%s: vdm register virtual address not mapped, reset "
	.ascii	"failed!\012\000"
.LC33:
	.ascii	"%s: unkown reg_id = %d\012\000"
.LC34:
	.ascii	"VdhId is wrong! VDMHAL_V200R003_EnableInt\012\000"
	.space	1
.LC35:
	.ascii	"VdhId is wrong! VDMHAL_V200_MaskInt\012\000"
	.space	3
.LC36:
	.ascii	"VdhId is wrong! VDMHAL_V200R003_ClearIntState\012\000"
	.space	1
.LC37:
	.ascii	"VDMHAL_V300R001_ResetVdm: map vdm register fail, vi"
	.ascii	"r(reg) = (%p)\012\000"
	.space	2
.LC38:
	.ascii	"GLB Reset failed!\012\000"
	.space	1
.LC39:
	.ascii	"VdhId is wrong! VDMHAL_V300R001_ResetVdm\012\000"
	.space	2
.LC40:
	.ascii	"VDH: %d VDMHAL_V300R001_ResetVdm ERROR!!!\012\000"
	.space	1
.LC41:
	.ascii	"VdhId is wrong! VDMHAL_V300R001_CloseHAL\012\000"
	.space	2
.LC42:
	.ascii	"'pMakeDecReport' is NULL\000"
	.space	3
.LC43:
	.ascii	"'pDecReport' is NULL\000"
	.space	3
.LC44:
	.ascii	"pDecReport->DecSliceNum(%d) > %d, set to 0 for full"
	.ascii	" repair.\012\000"
	.space	3
.LC45:
	.ascii	"\012***** UpMsg DecSliceNum=%d\012\000"
	.space	3
.LC46:
	.ascii	"\012***** Up Msg (phy addr: %#8x) *****\012\000"
	.space	2
.LC47:
	.ascii	"\0120x%02x 0x%08x 0x%08x 0x%08x 0x%08x\012\000"
	.space	3
.LC48:
	.ascii	"\012***** Up Msg print finished *****\012\000"
.LC49:
	.ascii	"DFS, CurFsSize < 0, CurFsSize: %d\012\000"
	.space	1
.LC50:
	.ascii	"DFS, report event. Size: %#x, Num: %#x, RefChanged:"
	.ascii	" %#x\012\000"
	.space	3
.LC51:
	.ascii	"pVdmMemArrange is NULL\000"
	.space	1
.LC52:
	.ascii	"DFS, no ref frame!\012\000"
.LC53:
	.ascii	"DFS, Frame number = %d > 30, Then, Frame num = 30, "
	.ascii	"\012\000"
	.space	3
.LC54:
	.ascii	"%s, FrameStore %d over bountry, Offset: 0x%x, curFs"
	.ascii	"Size: 0x%x, phyadd: 0x%x\012\000"
	.space	3
.LC55:
	.ascii	"VDMHAL_V300R001_ArrangeMem Mem addr is NULL\000"
.LC56:
	.ascii	"VDMHAL_V200R003_ArrangeMem get ChanWidth/ChanHeight"
	.ascii	" failed!\012\000"
	.space	3
.LC57:
	.ascii	"ImgSlotLen > ChanSlotLen\000"
	.space	3
.LC58:
	.ascii	"cann't allocate img slot\000"
	.space	3
.LC59:
	.ascii	"pOpenParam = NULL error!\000"
	.space	3
.LC60:
	.ascii	"MemBaseAddr = 0 error!\000"
	.space	1
.LC61:
	.ascii	"VDMHAL_V300R001_OpenHAL: Size error!\000"
	.space	3
.LC62:
	.ascii	"VdhId is wrong! VDMHAL_V300R001_OpenHAL\012\000"
	.space	3
.LC63:
	.ascii	"g_VdmRegVirAddr, g_VdmResetVirAddr = %p\012\000"
	.space	3
.LC64:
	.ascii	"BPDRegVirAddr %p\012\000"
	.space	2
.LC65:
	.ascii	"!!!!!! HAL memory not enouph! need %d, have %d\012\000"
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
