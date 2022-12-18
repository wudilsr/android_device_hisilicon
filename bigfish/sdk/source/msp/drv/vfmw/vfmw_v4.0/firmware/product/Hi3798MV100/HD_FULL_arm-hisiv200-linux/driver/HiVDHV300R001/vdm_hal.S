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
@ -DKBUILD_BASENAME=KBUILD_STR(vdm_hal)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/.vdm_hal.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal.c
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
	ldr	r4, [r3, r2]	@ D.52628, <variable>.pVdmRegVirAddr
	cmp	r4, #0	@ D.52628,
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
	mov	r0, r4	@ D.52632, tmp148
.L7:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L12:
	ldr	r0, [r4, #40]	@ Data32,
	subs	r0, r0, #1	@ D.52632, Data32,
	movne	r0, #1	@ D.52632
	b	.L7	@
.L11:
	mov	r0, r4	@, D.52628
	movw	r1, #:lower16:.LC0	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ D.52632, D.52628
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
	ldr	r3, [r3, r2]	@ D.52609, <variable>.pVdmRegVirAddr
	cmp	r3, #0	@ D.52609,
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
	ldr	r0, [r3, #28]	@ Data32.636,
	ubfx	r0, r0, #17, #1	@ Data32, Data32.636,,
	b	.L15	@
.L18:
	mov	r0, r3	@, D.52609
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
	mov	r0, r4	@ D.52859, tmp151
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L23:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC4	@,
	movt	r1, #:upper16:.LC4	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52859,
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
	mov	r0, r4	@ D.52839, tmp144
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L33:
	mov	r0, r4	@, tmp144
	movw	r1, #:lower16:.LC6	@,
	movt	r1, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52839,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L32:
	mov	r2, r0	@, pDst
	movw	r1, #:lower16:.LC5	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC5	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52839,
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
	ubfx	r8, r3, #29, #2	@ PicStructure.823, Height,,
	cmp	r8, #1	@ PicStructure.823,
	mov	r6, r3	@ Height, Height
	str	r0, [fp, #-100]	@ fpYuv, %sfp
	mov	r4, r1	@ Yaddress, Yaddress
	mov	r7, r2	@ Width, Width
	moveq	r8, #0	@ PicStructure,
	beq	.L36	@,
	cmp	r8, #2	@ PicStructure.823,
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
	subs	ip, r0, #0	@ D.53614,
	bne	.L133	@,
	mov	r1, ip	@, D.53614
	movw	r0, #:lower16:.LC9	@,
	mov	r2, #4194304	@,
	movt	r0, #:upper16:.LC9	@,
	sub	r3, fp, #76	@,,
	str	ip, [sp, #0]	@ D.53614,
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
	and	r7, r9, #15	@ pretmp.728, i,
	ldr	r6, [fp, #-92]	@, %sfp
	mov	r3, r9, lsr #4	@ pretmp.872, i,
	ldr	r0, [fp, #-84]	@, %sfp
	mov	r8, r7, asl #8	@ tmp280, pretmp.728,
	mov	r2, #256	@,
	sub	r5, sl, #1	@ tmp370, ImgWidthInPixAln,
	mla	r8, r6, r3, r8	@ pretmp.729,, pretmp.872, tmp280
	ubfx	r7, r5, #8, #1	@ tmp371, tmp370,,
	add	r6, r0, r2	@ ivtmp.834,,
	mov	r5, r2	@ j,
	add	r1, r4, r8	@, Yaddress, pretmp.729
	bl	memcpy	@
	cmp	sl, r5	@ ImgWidthInPixAln, j
	bls	.L46	@,
	cmp	r7, #0	@ tmp371,
	beq	.L44	@,
	add	r0, r8, #4096	@ tmp485, pretmp.729,
	mov	r2, r5	@, j
	add	r1, r4, r0	@, Yaddress, tmp485
	mov	r0, r6	@, ivtmp.834
	bl	memcpy	@
	mov	r5, #512	@ j,
	cmp	sl, r5	@ ImgWidthInPixAln, j
	add	r6, r6, #256	@ ivtmp.834, ivtmp.834,
	bls	.L46	@,
.L44:
	mov	r1, r5, lsr #8	@ tmp271, j,
	add	r7, r5, #256	@ tmp372, j,
	mov	r2, #256	@,
	add	r5, r7, r2	@ j, tmp372,
	add	ip, r8, r1, asl #12	@, tmp273, pretmp.729, tmp271,
	mov	r7, r7, lsr #8	@ tmp404, tmp372,
	add	r1, r4, ip	@, Yaddress, tmp273
	mov	r0, r6	@, ivtmp.834
	add	r6, r6, r2	@ tmp373, ivtmp.834,
	bl	memcpy	@
	add	r3, r8, r7, asl #12	@, tmp406, pretmp.729, tmp404,
	mov	r2, #256	@,
	mov	r0, r6	@, tmp373
	add	r1, r4, r3	@, Yaddress, tmp406
	add	r6, r6, r2	@ ivtmp.834, tmp373,
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
	mov	sl, #0	@ i.833,
.L48:
	cmp	r8, #0	@ ImgWidthInPixAln,
	beq	.L50	@,
	and	r6, sl, #7	@ pretmp.864, i.833,
	ldr	r1, [fp, #-88]	@, %sfp
	mov	r3, sl, lsr #3	@ pretmp.871, i.833,
	ldr	r0, [fp, #-80]	@, %sfp
	mov	r7, r6, asl #8	@ tmp294, pretmp.864,
	mov	r2, #256	@,
	sub	r5, r8, #1	@ tmp364, ImgWidthInPixAln,
	mov	r4, r2	@ j.832,
	mla	r7, r1, r3, r7	@ pretmp.733,, pretmp.871, tmp294
	ubfx	r6, r5, #8, #1	@ tmp365, tmp364,,
	add	r5, r0, r2	@ ivtmp.828,,
	add	r1, r9, r7	@, Caddress, pretmp.733
	bl	memcpy	@
	cmp	r8, r4	@ ImgWidthInPixAln, j.832
	bls	.L50	@,
	cmp	r6, #0	@ tmp365,
	beq	.L49	@,
	add	lr, r7, #2048	@ tmp481, pretmp.733,
	mov	r2, r4	@, j.832
	mov	r0, r5	@, ivtmp.828
	add	r1, r9, lr	@, Caddress, tmp481
	bl	memcpy	@
	mov	r4, #512	@ j.832,
	cmp	r8, r4	@ ImgWidthInPixAln, j.832
	add	r5, r5, #256	@ ivtmp.828, ivtmp.828,
	bls	.L50	@,
.L49:
	mov	ip, r4, lsr #8	@ tmp285, j.832,
	add	r6, r4, #256	@ tmp366, j.832,
	mov	r2, #256	@,
	mov	r0, r5	@, ivtmp.828
	add	r4, r7, ip, asl #11	@, tmp287, pretmp.733, tmp285,
	add	r5, r5, r2	@ tmp367, ivtmp.828,
	add	r1, r9, r4	@, Caddress, tmp287
	add	r4, r6, r2	@ j.832, tmp366,
	mov	r6, r6, lsr #8	@ tmp416, tmp366,
	bl	memcpy	@
	mov	r0, r5	@, tmp367
	mov	r2, #256	@,
	add	r3, r7, r6, asl #11	@, tmp418, pretmp.733, tmp416,
	add	r5, r5, r2	@ ivtmp.828, tmp367,
	add	r1, r9, r3	@, Caddress, tmp418
	bl	memcpy	@
	cmp	r8, r4	@ ImgWidthInPixAln, j.832
	bhi	.L49	@,
.L50:
	ldr	r2, [fp, #-84]	@, %sfp
	add	sl, sl, #1	@ i.833, i.833,
	ldr	lr, [fp, #-80]	@, %sfp
	cmp	sl, r2	@ i.833,
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
	mul	r4, r0, r3	@ temp.861,,
	ldr	r0, [fp, #-108]	@, %sfp
	mov	r1, r4	@, temp.861
	bl	klib_fwrite	@
	ldr	r2, [fp, #-100]	@, %sfp
	mov	r1, r4	@, temp.861
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
	mov	r9, r8	@ i.844, i.844
.L58:
	cmp	sl, #0	@ ImgWidthInPixAln,
	beq	.L60	@,
	ldr	r5, [fp, #-96]	@, %sfp
	mov	r2, r9, lsr #1	@ pretmp.873, i.844,
	ldr	r1, [fp, #-92]	@, %sfp
	mov	r7, r9, lsr #4	@ pretmp.867, i.844,
	and	lr, r9, #15	@ pretmp.879, i.844,
	sub	r6, sl, #1	@ tmp393, ImgWidthInPixAln,
	mla	r0, sl, r2, r5	@ ivtmp.817, ImgWidthInPixAln, pretmp.873,
	mov	r2, #256	@,
	mul	r8, r1, r7	@ tmp310,, pretmp.867
	mov	r5, r2	@ j.843,
	mla	r8, lr, r2, r8	@ pretmp.725, pretmp.879,, tmp310
	ubfx	r7, r6, #8, #1	@ tmp394, tmp393,,
	add	r6, r0, r2	@ ivtmp.817, ivtmp.817,
	add	r1, r4, r8	@, Yaddress, pretmp.725
	bl	memcpy	@
	cmp	sl, r5	@ ImgWidthInPixAln, j.843
	bls	.L60	@,
	cmp	r7, #0	@ tmp394,
	beq	.L59	@,
	add	ip, r8, #4096	@ tmp496, pretmp.725,
	mov	r2, r5	@, j.843
	mov	r0, r6	@, ivtmp.817
	add	r1, r4, ip	@, Yaddress, tmp496
	bl	memcpy	@
	mov	r5, #512	@ j.843,
	cmp	sl, r5	@ ImgWidthInPixAln, j.843
	add	r6, r6, #256	@ ivtmp.817, ivtmp.817,
	bls	.L60	@,
.L59:
	mov	r3, r5, lsr #8	@ tmp301, j.843,
	add	r7, r5, #256	@ tmp395, j.843,
	mov	r2, #256	@,
	mov	r0, r6	@, ivtmp.817
	add	r5, r8, r3, asl #12	@, tmp303, pretmp.725, tmp301,
	add	r6, r6, r2	@ tmp396, ivtmp.817,
	add	r1, r4, r5	@, Yaddress, tmp303
	add	r5, r7, r2	@ j.843, tmp395,
	mov	r7, r7, lsr #8	@ tmp440, tmp395,
	bl	memcpy	@
	mov	r0, r6	@, tmp396
	mov	r2, #256	@,
	add	r1, r8, r7, asl #12	@, tmp442, pretmp.725, tmp440,
	add	r6, r6, r2	@ ivtmp.817, tmp396,
	add	r1, r4, r1	@, Yaddress, tmp442
	bl	memcpy	@
	cmp	sl, r5	@ ImgWidthInPixAln, j.843
	bhi	.L59	@,
.L60:
	ldr	ip, [fp, #-88]	@, %sfp
	add	r9, r9, #2	@ i.844, i.844,
	cmp	ip, r9	@, i.844
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
	mov	sl, #0	@ i.851,
	mov	r8, lr, asr #1	@,,
	str	r8, [fp, #-88]	@, %sfp
	mov	r8, r5	@ ImgWidthInPixAln, ImgWidthInPixAln
.L62:
	cmp	r8, #0	@ ImgWidthInPixAln,
	beq	.L64	@,
	and	r6, sl, #7	@ pretmp.881, i.851,
	ldr	lr, [fp, #-88]	@, %sfp
	mov	r1, sl, lsr #3	@ pretmp.722, i.851,
	ldr	r0, [fp, #-80]	@, %sfp
	mov	r7, r6, asl #8	@ tmp326, pretmp.881,
	mov	r2, #256	@,
	sub	r5, r8, #1	@ tmp387, ImgWidthInPixAln,
	mov	r4, r2	@ j.850,
	mla	r7, lr, r1, r7	@ pretmp.723,, pretmp.722, tmp326
	ubfx	r6, r5, #8, #1	@ tmp388, tmp387,,
	add	r5, r0, r2	@ ivtmp.855,,
	add	r1, r9, r7	@, Caddress, pretmp.723
	bl	memcpy	@
	cmp	r8, r4	@ ImgWidthInPixAln, j.850
	bls	.L64	@,
	cmp	r6, #0	@ tmp388,
	beq	.L63	@,
	add	r3, r7, #2048	@ tmp492, pretmp.723,
	mov	r2, r4	@, j.850
	mov	r0, r5	@, ivtmp.855
	add	r1, r9, r3	@, Caddress, tmp492
	bl	memcpy	@
	mov	r4, #512	@ j.850,
	cmp	r8, r4	@ ImgWidthInPixAln, j.850
	add	r5, r5, #256	@ ivtmp.855, ivtmp.855,
	bls	.L64	@,
.L63:
	mov	r3, r4, lsr #8	@ tmp317, j.850,
	add	r6, r4, #256	@ tmp389, j.850,
	mov	r2, #256	@,
	mov	r0, r5	@, ivtmp.855
	add	r4, r7, r3, asl #11	@, tmp319, pretmp.723, tmp317,
	add	r5, r5, r2	@ tmp390, ivtmp.855,
	add	r1, r9, r4	@, Caddress, tmp319
	add	r4, r6, r2	@ j.850, tmp389,
	mov	r6, r6, lsr #8	@ tmp452, tmp389,
	bl	memcpy	@
	mov	r0, r5	@, tmp390
	mov	r2, #256	@,
	add	r1, r7, r6, asl #11	@, tmp454, pretmp.723, tmp452,
	add	r5, r5, r2	@ ivtmp.855, tmp390,
	add	r1, r9, r1	@, Caddress, tmp454
	bl	memcpy	@
	cmp	r8, r4	@ ImgWidthInPixAln, j.850
	bhi	.L63	@,
.L64:
	ldr	r2, [fp, #-84]	@, %sfp
	add	sl, sl, #1	@ i.851, i.851,
	ldr	ip, [fp, #-80]	@, %sfp
	cmp	sl, r2	@ i.851,
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
	add	r3, r3, #2	@ i.838,,
	ldr	r1, [fp, #-112]	@, %sfp
	cmp	r4, r3	@, i.838
	mvn	r2, r1	@ tmp381,
	add	ip, r2, r4	@ tmp382, tmp381,
	ubfx	r2, ip, #1, #1	@ tmp383, tmp382,,
	bls	.L70	@,
	cmp	r2, #0	@ tmp383,
	beq	.L128	@,
	ldr	r2, [fp, #-104]	@, %sfp
	add	r3, r3, #2	@ i.838, i.838,
	cmp	r2, r3	@, i.838
	bls	.L70	@,
.L128:
	ldr	r2, [fp, #-104]	@ chrom_height, %sfp
.L73:
	add	r3, r3, #4	@ i.838, i.838,
	cmp	r2, r3	@ chrom_height, i.838
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
	mla	r0, r5, ip, r2	@ tmp.852, ImgWidthInPixAln,,
	mov	r5, r5, asl #1	@ D.53698, ImgWidthInPixAln,
	mov	ip, #0	@ i.858,
.L67:
	cmp	lr, #0	@ chrom_width,
	beq	.L69	@,
	mov	r3, ip, lsr #1	@ pretmp.865, i.858,
	ldrb	sl, [r0, #0]	@ zero_extendqisi2	@ tmp472,* tmp.852
	mov	r1, #1	@ j.857,
	cmp	lr, r1	@ chrom_width, j.857
	mul	r6, lr, r3	@ tmp333, chrom_width, pretmp.865
	sub	r9, lr, #1	@ tmp374, chrom_width,
	and	r9, r9, r1	@ tmp376, tmp374,
	add	r3, r0, #2	@ ivtmp.785, tmp.852,
	add	r4, r7, r6	@ ivtmp.788, ul, tmp333
	add	r8, r4, #2097152	@ tmp471, ivtmp.788,
	add	r2, r4, r1	@ ivtmp.788, ivtmp.788,
	strb	sl, [r8, #0]	@ tmp472,
	ldrb	r8, [r0, #1]	@ zero_extendqisi2	@ tmp473,
	strb	r8, [r7, r6]	@ tmp473,
	bls	.L69	@,
	cmp	r9, #0	@ tmp376,
	beq	.L68	@,
	ldrb	r8, [r3, #0]	@ zero_extendqisi2	@ tmp488,* ivtmp.785
	add	r6, r2, #2097152	@ tmp487, ivtmp.788,
	mov	r1, #2	@ j.857,
	cmp	lr, r1	@ chrom_width, j.857
	add	r2, r2, #1	@ ivtmp.788, ivtmp.788,
	strb	r8, [r6, #0]	@ tmp488,
	ldrb	r6, [r3, #1]	@ zero_extendqisi2	@ tmp489,
	add	r3, r3, r1	@ ivtmp.785, ivtmp.785,
	strb	r6, [r4, #1]	@ tmp489,
	bls	.L69	@,
.L68:
	ldrb	sl, [r3, #0]	@ zero_extendqisi2	@ tmp329,* ivtmp.785
	add	r8, r2, #2097152	@ tmp328, ivtmp.788,
	mov	r4, r2	@ tmp379, ivtmp.788
	add	r6, r3, #2	@ tmp378, ivtmp.785,
	add	r1, r1, #2	@ j.857, j.857,
	strb	sl, [r8, #0]	@ tmp329,
	cmp	lr, r1	@ chrom_width, j.857
	ldrb	sl, [r3, #1]	@ zero_extendqisi2	@ tmp331,
	strb	sl, [r4], #1	@ tmp331,
	add	r8, r4, #2097152	@ tmp465, tmp379,
	ldrb	sl, [r3, #2]	@ zero_extendqisi2	@ tmp466,
	add	r3, r6, #2	@ ivtmp.785, tmp378,
	strb	sl, [r8, #0]	@ tmp466,
	ldrb	r6, [r6, #1]	@ zero_extendqisi2	@ tmp467,
	strb	r6, [r2, #1]	@ tmp467,
	add	r2, r4, #1	@ ivtmp.788, tmp379,
	bhi	.L68	@,
.L69:
	ldr	r1, [fp, #-104]	@, %sfp
	add	ip, ip, #2	@ i.858, i.858,
	cmp	r1, ip	@, i.858
	bls	.L66	@,
	add	r0, r0, r5	@ tmp.852, tmp.852, D.53698
	b	.L67	@
.L134:
	ldr	r3, [fp, #-104]	@, %sfp
	cmp	r3, #0	@,
	beq	.L66	@,
	ldr	r6, [fp, #-96]	@ tmp, %sfp
	mov	r8, #0	@ i.837,
	ldr	r7, [fp, #-108]	@ ivtmp.835, %sfp
	mov	r9, r3	@ chrom_height,
	ldr	lr, [fp, #-120]	@ chrom_width, %sfp
.L53:
	cmp	lr, #0	@ chrom_width,
	beq	.L55	@,
	ldrb	ip, [r6, #0]	@ zero_extendqisi2	@ tmp436,* tmp
	add	r4, r7, #2097152	@ tmp435, ivtmp.835,
	mov	r0, #1	@ j.836,
	cmp	lr, r0	@ chrom_width, j.836
	sub	r3, lr, #1	@ tmp356, chrom_width,
	mov	r2, r7	@ ivtmp.750, ivtmp.835
	strb	ip, [r4, #0]	@ tmp436,
	and	ip, r3, r0	@ tmp358, tmp356,
	ldrb	r1, [r6, #1]	@ zero_extendqisi2	@ tmp437,
	add	r3, r6, #2	@ ivtmp.747, tmp,
	strb	r1, [r2], #1	@ tmp437,
	bls	.L55	@,
	cmp	ip, #0	@ tmp358,
	beq	.L54	@,
	ldrb	r1, [r3, #0]	@ zero_extendqisi2	@ tmp477,* ivtmp.747
	add	r4, r2, #2097152	@ tmp476, ivtmp.750,
	mov	r0, #2	@ j.836,
	cmp	lr, r0	@ chrom_width, j.836
	strb	r1, [r4, #0]	@ tmp477,
	ldrb	ip, [r3, #1]	@ zero_extendqisi2	@ tmp478,
	add	r3, r3, r0	@ ivtmp.747, ivtmp.747,
	strb	ip, [r2], #1	@ tmp478,
	bls	.L55	@,
.L54:
	ldrb	sl, [r3, #0]	@ zero_extendqisi2	@ tmp296,* ivtmp.747
	add	r4, r2, #2097152	@ tmp295, ivtmp.750,
	mov	r1, r2	@ tmp361, ivtmp.750
	add	ip, r3, #2	@ tmp360, ivtmp.747,
	add	r0, r0, #2	@ j.836, j.836,
	strb	sl, [r4, #0]	@ tmp296,
	cmp	lr, r0	@ chrom_width, j.836
	ldrb	sl, [r3, #1]	@ zero_extendqisi2	@ tmp298,
	strb	sl, [r1], #1	@ tmp298,
	add	r4, r1, #2097152	@ tmp429, tmp361,
	ldrb	sl, [r3, #2]	@ zero_extendqisi2	@ tmp430,
	add	r3, ip, #2	@ ivtmp.747, tmp360,
	strb	sl, [r4, #0]	@ tmp430,
	ldrb	ip, [ip, #1]	@ zero_extendqisi2	@ tmp431,
	strb	ip, [r2, #1]	@ tmp431,
	add	r2, r1, #1	@ ivtmp.750, tmp361,
	bhi	.L54	@,
.L55:
	add	r8, r8, #1	@ i.837, i.837,
	add	r7, r7, lr	@ ivtmp.835, ivtmp.835, chrom_width
	cmp	r9, r8	@ chrom_height, i.837
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
	add	r0, r5, #15	@ D.52184, Width,
	movw	r2, #:lower16:g_not_direct_8x8_inference_flag	@ tmp259,
	movt	r2, #:upper16:g_not_direct_8x8_inference_flag	@ tmp259,
	mov	r3, r1, asr #4	@ ImgHeightInMb, tmp251,
	mov	r1, r0, asr #4	@ ImgWidthInMb, D.52184,
	ldrb	r6, [r2, #0]	@ zero_extendqisi2	@ g_not_direct_8x8_inference_flag, g_not_direct_8x8_inference_flag
	cmp	sl, #20	@ PmvNum,
	movge	sl, #20	@ PmvNum.943,
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
	mul	r2, sl, r6	@, PmvNum.943, PmvSlotLen
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
	str	sl, [r7, #936]	@ PmvNum.943, <variable>.ValidPMVNum
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
	mul	r9, r8, r9	@ D.52229, tmp291, level
	mul	r8, ip, r8	@ D.52224, SlotWidth, tmp291
	add	ip, r9, r8	@ tmp292, D.52229, D.52224
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
	ldr	r5, [fp, #12]	@ prephitmp.903, s32DisplayFrameNum
.L157:
	ldr	r2, [fp, #8]	@, s32MaxRefFrameNum
	ldr	r3, [fp, #-48]	@, %sfp
	cmp	r2, #0	@,
	add	r5, r5, r3	@ Offset.947, prephitmp.903,
	bne	.L162	@,
.L204:
	str	r2, [r7, #548]	@, <variable>.ValidFrameNum
	ldr	sl, [fp, #8]	@ prephitmp.952, s32MaxRefFrameNum
.L163:
	ldr	r9, [r7, #936]	@ D.52287, <variable>.ValidPMVNum
	add	r5, sl, r5	@ Offset.950, prephitmp.952, Offset.947
	add	r2, r5, r4	@ MemAddr.951, Offset.950, MemAddr
	cmp	r9, #0	@ D.52287,
	ble	.L168	@,
	mov	r1, #1	@ i,
	cmp	r1, r9	@ i, D.52287
	sub	lr, r9, #1	@ tmp359, D.52287,
	str	r2, [r7, #812]	@ MemAddr.951, <variable>.PMVAddr
	and	r0, lr, r1	@ tmp361, tmp359,
	add	r2, r2, r6	@ ivtmp.916, MemAddr.951, PmvSlotLen
	add	r3, r7, #4	@ ivtmp.920, pVdmMemArrange,
	bge	.L168	@,
	cmp	r0, #0	@ tmp361,
	beq	.L169	@,
	mov	r1, #2	@ i,
	cmp	r1, r9	@ i, D.52287
	str	r2, [r3, #812]	@ ivtmp.916, <variable>.PMVAddr
	add	r2, r2, r6	@ ivtmp.916, ivtmp.916, PmvSlotLen
	add	r3, r3, #4	@ ivtmp.920, ivtmp.920,
	bge	.L168	@,
.L169:
	add	r1, r1, #2	@ i, i,
	add	r0, r3, #4	@ tmp363, ivtmp.920,
	cmp	r1, r9	@ i, D.52287
	add	ip, r2, r6	@ ivtmp.916, ivtmp.916, PmvSlotLen
	str	r2, [r3, #812]	@ ivtmp.916, <variable>.PMVAddr
	add	r2, ip, r6	@ ivtmp.916, ivtmp.916, PmvSlotLen
	str	ip, [r0, #812]	@ ivtmp.916, <variable>.PMVAddr
	add	r3, r0, #4	@ ivtmp.920, tmp363,
	blt	.L169	@,
.L168:
	mla	r5, r9, r6, r5	@ tmp357, D.52287, PmvSlotLen, Offset.950
	mov	r0, #0	@ D.52162,
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
	ldr	r3, [fp, #12]	@ s32DisplayFrameNum.946, s32DisplayFrameNum
.L160:
	cmp	r3, #0	@ s32DisplayFrameNum.946,
	addle	r2, r5, r2	@ tmp335, ImgInfoSlotLen, DbdrInfoSlotLen
	mulle	r5, r2, r3	@ prephitmp.903, tmp335, s32DisplayFrameNum.946
	ble	.L157	@,
	ldr	sl, [r7, #808]	@ D.52269, <variable>.ValidBTLFrameNum
	add	r5, r5, r2	@ pretmp.955, ImgInfoSlotLen, DbdrInfoSlotLen
	ldr	ip, [fp, #-48]	@, %sfp
	add	r3, r7, #4	@ ivtmp.934, pVdmMemArrange,
	cmp	sl, #1	@ D.52269,
	sub	r1, sl, #1	@ tmp369, D.52269,
	add	r2, ip, r4	@ ivtmp.930,, MemAddr
	and	r0, r1, #1	@ tmp371, tmp369,
	str	r2, [r7, #552]	@ ivtmp.930, <variable>.BtlAddr
	mov	r1, #1	@ i.945,
	add	r2, r2, r5	@ ivtmp.930, ivtmp.930, pretmp.955
	ble	.L189	@,
	cmp	r0, #0	@ tmp371,
	beq	.L161	@,
	mov	r1, #2	@ i.945,
	cmp	sl, r1	@ D.52269, i.945
	str	r2, [r3, #552]	@ ivtmp.930, <variable>.BtlAddr
	add	r2, r2, r5	@ ivtmp.930, ivtmp.930, pretmp.955
	add	r3, r3, #4	@ ivtmp.934, ivtmp.934,
	ble	.L189	@,
.L161:
	add	r1, r1, #2	@ i.945, i.945,
	add	lr, r3, #4	@ tmp373, ivtmp.934,
	cmp	sl, r1	@ D.52269, i.945
	add	r0, r2, r5	@ ivtmp.930, ivtmp.930, pretmp.955
	str	r2, [r3, #552]	@ ivtmp.930, <variable>.BtlAddr
	add	r2, r0, r5	@ ivtmp.930, ivtmp.930, pretmp.955
	str	r0, [lr, #552]	@ ivtmp.930, <variable>.BtlAddr
	add	r3, lr, #4	@ ivtmp.934, tmp373,
	bgt	.L161	@,
.L189:
	mul	r5, r5, sl	@ prephitmp.903, pretmp.955, D.52269
	ldr	r2, [fp, #8]	@, s32MaxRefFrameNum
	ldr	r3, [fp, #-48]	@, %sfp
	cmp	r2, #0	@,
	add	r5, r5, r3	@ Offset.947, prephitmp.903,
	beq	.L204	@,
.L162:
	ldr	lr, [fp, #24]	@, Btl1Dt2DEnable
	add	r8, r8, r8, asl #1	@, tmp345, D.52224, D.52224,
	add	r0, r9, r9, asl #1	@, tmp340, D.52229, D.52229,
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
	rsb	r0, r5, r1	@, Offset.947, FramePoolSize
	mov	r1, r8	@, ImgSlotLen
	bl	__aeabi_idiv	@
	cmp	r0, #64	@,
	movge	r0, #64	@ D.52280,
	cmp	r0, sl	@ D.52280, ValidFrameNum
	movlt	sl, r0	@ D.52280, D.52280
	movge	sl, sl	@ D.52280, ValidFrameNum
	str	sl, [r7, #548]	@ D.52280, <variable>.ValidFrameNum
	cmp	sl, #0	@ D.52280,
	ble	.L190	@,
	cmp	sl, #1	@ D.52280,
	add	r9, r5, r4	@ ivtmp.923, Offset.947, MemAddr
	sub	r3, sl, #1	@ tmp364, D.52280,
	str	r9, [r7, #8]	@ ivtmp.923, <variable>.FrameAddr
	and	r0, r3, #1	@ tmp366, tmp364,
	add	r2, r9, r8	@ ivtmp.923, ivtmp.923, ImgSlotLen
	mov	r1, #1	@ i.949,
	add	r3, r7, #4	@ ivtmp.927, pVdmMemArrange,
	ble	.L190	@,
	cmp	r0, #0	@ tmp366,
	beq	.L167	@,
	mov	r1, #2	@ i.949,
	cmp	sl, r1	@ D.52280, i.949
	str	r2, [r3, #8]	@ ivtmp.923, <variable>.FrameAddr
	add	r2, r2, r8	@ ivtmp.923, ivtmp.923, ImgSlotLen
	add	r3, r3, #4	@ ivtmp.927, ivtmp.927,
	ble	.L190	@,
.L167:
	add	r1, r1, #2	@ i.949, i.949,
	add	r0, r3, #4	@ tmp368, ivtmp.927,
	cmp	sl, r1	@ D.52280, i.949
	add	ip, r2, r8	@ ivtmp.923, ivtmp.923, ImgSlotLen
	str	r2, [r3, #8]	@ ivtmp.923, <variable>.FrameAddr
	add	r2, ip, r8	@ ivtmp.923, ivtmp.923, ImgSlotLen
	str	ip, [r0, #8]	@ ivtmp.923, <variable>.FrameAddr
	add	r3, r0, #4	@ ivtmp.927, tmp368,
	bgt	.L167	@,
.L190:
	mul	sl, sl, r8	@ prephitmp.952, D.52280, ImgSlotLen
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
	cmp	r0, #0	@ D.52184,
	add	lr, r0, #15	@ tmp296, D.52184,
	movge	lr, r0	@ D.52184, D.52184
	mov	r2, lr, asr #4	@ tmp297, D.52184,
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
	mvn	r0, #0	@ D.52162,
	b	.L138	@
.L159:
	ldr	r3, [fp, #12]	@ s32DisplayFrameNum.946, s32DisplayFrameNum
	cmp	r3, #6	@ s32DisplayFrameNum.946,
	movlt	r3, #6	@ s32DisplayFrameNum.946,
	str	r3, [r7, #808]	@ s32DisplayFrameNum.946, <variable>.ValidBTLFrameNum
	b	.L160	@
.L200:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L206	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC13	@,
	movt	r3, #:upper16:.LC13	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52162,
	b	.L138	@
.L197:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L206	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52162,
	b	.L138	@
.L199:
	mov	r0, r7	@, pVdmMemArrange
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L206	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC12	@,
	movt	r3, #:upper16:.LC12	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52162,
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
	movw	r5, #:lower16:g_ChanCtx	@ ivtmp.992,
	movt	r5, #:upper16:g_ChanCtx	@ ivtmp.992,
	movw	r1, #:lower16:s_pFspInst	@,
	movw	r0, #:lower16:g_FrameRate	@,
	movt	r1, #:upper16:s_pFspInst	@,
	ldr	r4, [r5, #64]	@ D.53407,
	movt	r0, #:upper16:g_FrameRate	@,
	movw	r2, #:lower16:86236207	@,
	movw	r3, #:lower16:g_LastFrameRate	@,
	cmp	r4, #0	@ D.53407,
	movt	r2, #:upper16:86236207	@,
	movt	r3, #:upper16:g_LastFrameRate	@,
	str	r1, [fp, #-52]	@, %sfp
	str	r0, [fp, #-56]	@, %sfp
	add	sl, r5, #64	@ D.54258, ivtmp.992,
	str	r2, [fp, #-60]	@, %sfp
	mov	r7, #30	@ s32FrameRate.1078,
	str	r3, [fp, #-64]	@, %sfp
	mov	r8, #0	@ clk_need,
	blt	.L209	@,
.L233:
	mov	r0, r4	@, D.53407
	bl	VCTRL_IsChanActive	@
	cmp	r0, #0	@,
	movne	r6, r7	@ s32FrameRate, s32FrameRate.1078
	bne	.L211	@,
	ldr	r6, [fp, #-52]	@, %sfp
	ldr	r9, [fp, #-56]	@, %sfp
	ldr	ip, [r6, r4, asl #2]	@ pFsp, s_pFspInst
	ldr	r6, [r9, r4, asl #2]	@ s32FrameRate, g_FrameRate
	ldr	r2, [ip, #68]	@ <variable>.stInstCfg.s32DecFsWidth, <variable>.stInstCfg.s32DecFsWidth
	ldr	r3, [ip, #72]	@ <variable>.stInstCfg.s32DecFsHeight, <variable>.stInstCfg.s32DecFsHeight
	adds	r1, r2, #15	@ tmp177, <variable>.stInstCfg.s32DecFsWidth,
	addmi	lr, r2, #30	@, tmp179, <variable>.stInstCfg.s32DecFsWidth,
	movpl	lr, r1	@, tmp179, tmp177
	adds	r0, r3, #15	@ tmp182, <variable>.stInstCfg.s32DecFsHeight,
	addmi	ip, r3, #30	@, tmp184, <variable>.stInstCfg.s32DecFsHeight,
	movpl	ip, r0	@, tmp184, tmp182
	cmp	r6, #30	@ s32FrameRate,
	mov	r9, lr, asr #4	@, tmp179,
	str	r9, [fp, #-48]	@, %sfp
	mov	r9, ip, asr #4	@ picHeightInMb, tmp184,
	ldrgt	ip, [fp, #-64]	@, %sfp
	mov	r0, r4	@, D.53407
	movle	r6, r7	@ s32FrameRate, s32FrameRate.1078
	strgt	r6, [ip, r4, asl #2]	@ s32FrameRate, g_LastFrameRate
	bl	VCTRL_GetVidStd	@
	cmp	r0, #16	@,
	ldrls	pc, [pc, r0, asl #2]	@
	b	.L211	@
.L226:
	.word	.L223
	.word	.L223
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
	ldr	r0, [fp, #-48]	@, %sfp
	mul	r3, r0, r9	@ tmp267,, picHeightInMb
.L231:
	mul	lr, r6, r3	@ tmp268, s32FrameRate, tmp267
	ldr	r2, [fp, #-60]	@, %sfp
	ubfx	ip, lr, #1, #26	@ tmp271, tmp268,,
	umull	r2, r1, r2, ip	@, tmp272,, tmp271
	add	r8, r8, r1, lsr #7	@, clk_need, clk_need, tmp272,
.L211:
	add	r5, r5, #4	@ ivtmp.992, ivtmp.992,
	cmp	r5, sl	@ ivtmp.992, D.54258
	beq	.L209	@,
	ldr	r4, [r5, #64]	@ D.53407,
	mov	r7, r6	@ s32FrameRate.1078, s32FrameRate
	cmp	r4, #0	@ D.53407,
	bge	.L233	@,
.L209:
	movw	ip, #:lower16:g_pstRegCrg	@ tmp274,
	movt	ip, #:upper16:g_pstRegCrg	@ tmp274,
	rsb	r8, r8, #32	@ clk_skip, clk_need,
	ldr	r0, [ip, #0]	@ g_pstRegCrg.536, g_pstRegCrg
	cmp	r8, #25	@ clk_skip,
	movge	r8, #25	@ clk_skip.1071,
	cmp	r8, #0	@ clk_skip.1071,
	ldr	r2, [r0, #120]	@ D.53434, <variable>.PERI_CRG30.u32
	bfigt	r2, r8, #12, #5	@ u32TmpValue, clk_skip.1071,,
	bfcle	r2, #12, #5	@ u32TmpValue,,
	bfc	r2, #17, #1	@ u32TmpValue,,
	str	r2, [r0, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r3, [ip, #0]	@ g_pstRegCrg.1076, g_pstRegCrg
	ldr	r1, [r3, #120]	@ D.53441, <variable>.PERI_CRG30.u32
	orr	r0, r1, #131072	@ u32TmpValue, D.53441,
	str	r0, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L224:
	ldr	r3, [fp, #-48]	@, %sfp
	mul	lr, r9, r3	@ tmp203, picHeightInMb,
	mov	r3, lr, asl #1	@ tmp204, tmp203,
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
	stmfd	sp!, {r4, r5, r6, r7, r8, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r6, r0, asl #3	@ tmp234, VdhId,
	rsb	r8, r0, r6	@ tmp156, VdhId, tmp234
	movw	r5, #:lower16:g_VdmDrvParam	@ tmp233,
	add	r1, r8, #1	@ tmp157, tmp156,
	movt	r5, #:upper16:g_VdmDrvParam	@ tmp233,
	movw	r7, #:lower16:s_pstVfmwChan	@ tmp235,
	movt	r7, #:upper16:s_pstVfmwChan	@ tmp235,
	ldr	r2, [r5, r1, asl #3]	@ <variable>.ChanId, <variable>.ChanId
	add	lr, r5, r1, asl #3	@, tmp160, tmp233, tmp157,
	movw	r8, #:lower16:g_pstRegCrg	@ tmp232,
	movt	r8, #:upper16:g_pstRegCrg	@ tmp232,
	ldr	sl, [lr, #4]	@ VidStd, <variable>.VidStd
	mov	r4, r0	@ VdhId, VdhId
	ldr	r3, [r7, r2, asl #2]	@ tmp169, s_pstVfmwChan
	ldr	r1, [r8, #0]	@ g_pstRegCrg.539, g_pstRegCrg
	ldr	r3, [r3, #1072]	@ eCapLevel, <variable>.stSynExtraData.eCapLevel
	ldr	r2, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	cmp	r3, #9	@ eCapLevel,
	movls	ip, #0	@,
	movhi	ip, #1	@,
	cmp	sl, #0	@ VidStd,
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
	rsb	sl, r4, r6	@ tmp185, VdhId, tmp234
	ldr	r3, [lr, #4]	@ arm_delay_ops.const_udelay, arm_delay_ops.const_udelay
	movw	r0, #:lower16:32212230	@,
	movt	r0, #:upper16:32212230	@,
	blx	r3	@ arm_delay_ops.const_udelay
	add	ip, sl, #1	@ tmp186, tmp185,
	ldr	sl, [r5, ip, asl #3]	@ s32ChanId.1103, <variable>.ChanId
	ldr	r3, [r7, sl, asl #2]	@ temp.1104, s_pstVfmwChan
	ldr	r0, [r3, #1744]	@ <variable>.stSynExtraData.s32ModuleLowlyEnable, <variable>.stSynExtraData.s32ModuleLowlyEnable
	cmp	r0, #0	@ <variable>.stSynExtraData.s32ModuleLowlyEnable,
	beq	.L237	@,
	ldr	ip, [r3, #1732]	@ <variable>.stSynExtraData.s32FastForwardBackwardSpeed, <variable>.stSynExtraData.s32FastForwardBackwardSpeed
	movw	r2, #4094	@ tmp192,
	add	r0, ip, #2032	@ tmp189, <variable>.stSynExtraData.s32FastForwardBackwardSpeed,
	add	r1, r0, #15	@ tmp189, tmp189,
	cmp	r1, r2	@ tmp189, tmp192
	bhi	.L238	@,
.L237:
	mov	r0, r4	@, VdhId
	bl	VDMHAL_V300R001_SetVdhClkSkip	@
.L239:
	ldr	ip, [r7, sl, asl #2]	@ tmp197, s_pstVfmwChan
	ldr	r1, [ip, #1032]	@ <variable>.eVidStd, <variable>.eVidStd
	cmp	r1, #16	@ <variable>.eVidStd,
	movne	r1, #3	@ ClockGatingData,
	moveq	r1, #0	@ ClockGatingData,
	cmp	r4, #0	@ VdhId,
	bne	.L250	@,
	movw	r3, #:lower16:s_RegPhyBaseAddr	@ tmp199,
	movt	r3, #:upper16:s_RegPhyBaseAddr	@ tmp199,
	ldr	lr, [r3, #0]	@ s_RegPhyBaseAddr,
	add	r0, lr, #12	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
.L245:
#APP
@ 2841 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal.c" 1
	dsb
@ 0 "" 2
	cmp	r4, #0	@ VdhId,
	bgt	.L251	@,
.L246:
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
	ldr	r6, [r0, r2]	@ D.53494, <variable>.pVdmRegVirAddr
	str	ip, [r6, #0]	@ tmp214,* D.53494
	mov	r6, #1	@ tmp219,
	ldr	lr, [r0, r2]	@ temp.1111, <variable>.pVdmRegVirAddr
	str	r6, [lr, #0]	@ tmp219,* temp.1111
	ldr	lr, [r0, r2]	@ temp.1113, <variable>.pVdmRegVirAddr
	str	ip, [lr, #0]	@ tmp214,* temp.1113
	ldr	r0, [r5, r4, asl #3]	@ D.53503, <variable>.ChanId
	ldr	r2, [r3, r0, asl #2]	@, g_LowDelaySeqIndex
	bl	VDEC_Lowdelay_Event_Time	@
.L248:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L235:
	bfc	r2, #8, #2	@ u32TmpValue,,
	b	.L236	@
.L250:
	cmp	r4, #1	@ VdhId,
	beq	.L252	@,
	movw	r1, #:lower16:.LC14	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC14	@,
	bl	dprint_vfmw	@
#APP
@ 2841 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal.c" 1
	dsb
@ 0 "" 2
	cmp	r4, #0	@ VdhId,
	ble	.L246	@,
.L251:
	mov	ip, #0	@ tmp209,
	mov	r3, r4	@, VdhId
	mov	r0, ip	@, tmp209
	movw	r1, #:lower16:.LC15	@,
	ldr	r2, .L253	@,
	movt	r1, #:upper16:.LC15	@,
	str	ip, [sp, #0]	@ tmp209,
	bl	dprint_vfmw	@
	b	.L248	@
.L238:
	ldr	r1, [r8, #0]	@ g_pstRegCrg.1105, g_pstRegCrg
	ldr	r0, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	bfc	r0, #12, #5	@ u32TmpValue,,
	bfc	r0, #17, #1	@ u32TmpValue,,
	str	r0, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r3, [r8, #0]	@ g_pstRegCrg.1107, g_pstRegCrg
	ldr	r2, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	orr	lr, r2, #131072	@ u32TmpValue, u32TmpValue,
	str	lr, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	b	.L239	@
.L252:
	movw	r0, #:lower16:s_RegPhyBaseAddr_1	@ tmp202,
	movt	r0, #:upper16:s_RegPhyBaseAddr_1	@ tmp202,
	ldr	r2, [r0, #0]	@ s_RegPhyBaseAddr_1,
	add	r0, r2, #12	@, s_RegPhyBaseAddr_1,
	bl	MEM_WritePhyWord	@
	b	.L245	@
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
@ 2606 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal.c" 1
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
	orr	r7, r7, #67108864	@ dat.1137, dat,
	ldr	r2, [r1, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	uxth	r1, r0	@ tmp153,
	add	r0, r2, #4	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	ldr	r3, [r6, r5]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r7, [r3, #8]	@ dat.1137,
#APP
@ 2606 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal.c" 1
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
	ldr	r2, [r4, ip]	@ D.53360, <variable>.pVdmRegVirAddr
	str	lr, [r2, #0]	@ tmp178,* D.53360
	ldr	r1, [r4, ip]	@ temp.1146, <variable>.pVdmRegVirAddr
	str	r3, [r1, #0]	@ tmp183,* temp.1146
	ldr	r0, [r4, ip]	@ temp.1148, <variable>.pVdmRegVirAddr
	str	lr, [r0, #0]	@ tmp178,* temp.1148
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
	mvn	r0, #0	@ D.53078,
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
	mov	r0, #0	@ D.53078,
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
	subs	r2, r0, #0	@ D.53085,
	strne	r2, [r1, #0]	@ D.53085, <variable>.pVdmRegVirAddr
	bne	.L270	@,
	movw	r1, #:lower16:.LC18	@,
	movt	r1, #:upper16:.LC18	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53078,
	b	.L268	@
.L274:
	mov	r0, ip	@, tmp152
	movw	r1, #:lower16:.LC15	@,
	ldr	r2, .L276	@,
	movt	r1, #:upper16:.LC15	@,
	str	ip, [sp, #0]	@ tmp152,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53078,
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
	ldr	r2, [r9, #840]	@ D.52899, <variable>.ValidGroupNum
	sub	r3, r2, #1	@ tmp238, D.52899,
	cmp	r3, #199	@ tmp238,
	bhi	.L321	@,
	ldr	r1, [r9, #24]	@ <variable>.ImageWidth, <variable>.ImageWidth
	ldr	r2, [r9, #864]	@ D.52907, <variable>.CtbSize
	ldr	r0, [r9, #28]	@ <variable>.ImageHeight, <variable>.ImageHeight
	mov	r3, r1, asl r2	@ pic_width, <variable>.ImageWidth,
	ldr	lr, [r9, #0]	@ <variable>.VidStd, <variable>.VidStd
	add	ip, r3, #255	@ tmp242, pic_width,
	cmp	lr, #16	@ <variable>.VidStd,
	bic	r1, ip, #255	@ SlotWidth, tmp242,
	mov	r2, r0, asl r2	@ pic_height, <variable>.ImageHeight,
	moveq	r3, #0	@ prephitmp.1226,
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
	str	r3, [lr, #20]	@ prephitmp.1226,
	ldr	r1, [r9, #24]	@ <variable>.ImageWidth, <variable>.ImageWidth
	ldr	ip, [r9, #28]	@ <variable>.ImageHeight, <variable>.ImageHeight
	sub	r0, r1, #1	@ tmp283, <variable>.ImageWidth,
	sub	r2, ip, #1	@ tmp287, <variable>.ImageHeight,
	mov	r3, r0, asl #23	@ tmp288, tmp283,
	mov	r1, r3, lsr #23	@ tmp288, tmp288,
	bfi	r1, r2, #16, #9	@ tmp288, tmp287,,
	str	r1, [fp, #-48]	@ tmp288,
	str	r1, [lr, #24]	@ tmp288,
	ldr	r3, [r9, #864]	@ temp.1280, <variable>.CtbSize
	cmp	r3, #6	@ temp.1280,
	moveq	r4, #2	@ align_mb,
	beq	.L285	@,
	cmp	r3, #5	@ temp.1280,
	moveq	r4, #4	@ align_mb,
	beq	.L285	@,
	cmp	r3, #4	@ temp.1280,
	moveq	r4, #8	@ align_mb,
	beq	.L285	@,
	movw	r1, #:lower16:.LC21	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC21	@,
	mov	r4, #1	@ align_mb,
	bl	dprint_vfmw	@
.L285:
	ldr	r3, [r9, #856]	@ prephitmp.1230, <variable>.FullRepair
	cmp	r3, #0	@ prephitmp.1230,
	movne	r5, #0	@ actual_repairTime,
	bne	.L289	@,
	ldr	lr, [r9, #840]	@, <variable>.ValidGroupNum
	cmp	lr, #0	@,
	str	lr, [fp, #-56]	@, %sfp
	movle	r5, r3	@ actual_repairTime, prephitmp.1230
	ble	.L291	@,
	sub	r5, r4, #1	@, align_mb,
	str	r3, [fp, #-60]	@ prephitmp.1230, %sfp
	str	r5, [fp, #-76]	@, %sfp
	mov	r6, r3	@ i, prephitmp.1230
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
	ldrh	r8, [sl, #2]	@ prephitmp.1239, <variable>.EndMbn
	sxth	ip, r8	@, prephitmp.1239
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
	mul	sl, sl, r3	@ D.53016, <variable>.ImageWidth, <variable>.ImageHeight
	cmp	r5, sl	@ cur_EndMb, D.53016
	subge	sl, sl, #1	@ end_Mb, D.53016,
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
	str	r7, [ip, r2, asl #3]	@ D32.1300,
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
	str	r7, [ip, r2]	@ D32.1304,
	ldr	r1, [r9, #840]	@, <variable>.ValidGroupNum
	str	r1, [fp, #-56]	@, %sfp
	ldr	r0, [fp, #-56]	@, %sfp
	cmp	r0, r6	@, i
	bgt	.L325	@,
.L304:
	ldr	r3, [r9, #856]	@ prephitmp.1230, <variable>.FullRepair
.L289:
	cmp	r3, #1	@ prephitmp.1230,
	beq	.L303	@,
.L291:
	sub	r5, r5, #1	@ tmp395, actual_repairTime,
	uxth	r5, r5	@ prephitmp.1228, tmp395
.L306:
	ldr	lr, [r9, #848]	@ <variable>.Compress_en, <variable>.Compress_en
	mov	r0, #0	@ D.52898,
	ldrb	r3, [fp, #-46]	@ zero_extendqisi2	@,
	ldr	r2, [r9, #852]	@ <variable>.Pic_type, <variable>.Pic_type
	bfi	r3, lr, #0, #1	@ tmp410, <variable>.Compress_en,,
	strb	r3, [fp, #-46]	@ tmp410,
	ldr	ip, [r9, #864]	@ <variable>.CtbSize, <variable>.CtbSize
	ldrb	r1, [fp, #-45]	@ zero_extendqisi2	@,
	uxtb	lr, r3	@ tmp413, tmp410
	bfi	lr, r2, #4, #2	@ tmp413, <variable>.Pic_type,,
	sub	ip, ip, #4	@ tmp420, <variable>.CtbSize,
	strh	r5, [fp, #-48]	@ movhi	@ prephitmp.1228, <variable>.total_grp_num_minus1
	bfi	lr, r2, #6, #2	@ tmp416, <variable>.Pic_type,,
	bfi	r1, ip, #0, #2	@ tmp421, tmp420,,
	strb	lr, [fp, #-46]	@ tmp416,
	strb	r1, [fp, #-45]	@ tmp421,
	ldr	r3, [fp, #-48]	@ D32.1324, D32
	ldr	lr, [fp, #-68]	@, %sfp
	str	r3, [lr, #28]	@ D32.1324,
.L280:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L322:
	ldr	ip, [fp, #-56]	@, %sfp
	mvn	r5, r6	@ tmp434, i
	add	r7, r5, ip	@ tmp433, tmp434,
	tst	r7, #1	@ tmp433,
	mov	r7, sl	@ ivtmp.1257, tmp292
	bne	.L326	@,
	str	r9, [fp, #-64]	@ pRepairParam, %sfp
	ldr	r9, [fp, #-76]	@ tmp431, %sfp
	b	.L297	@
.L298:
	bl	__aeabi_uidiv	@
	mov	r1, r4	@, align_mb
	mul	r5, r4, r0	@ temp.1286, align_mb,
	ldrsh	r0, [r7, #4]	@, <variable>.StartMbn
	bl	__aeabi_uidiv	@
	mul	r1, r4, r0	@ D.53012, align_mb,
	cmp	r5, r1	@ temp.1286, D.53012
	add	r3, r1, #1	@ tmp347, D.53012,
	bhi	.L299	@,
	cmp	r5, r3	@ temp.1286, tmp347
	mov	r1, r4	@, align_mb
	beq	.L299	@,
	ldrsh	lr, [r7, #-2]	@ <variable>.EndMbn, <variable>.EndMbn
	sub	r2, lr, #1	@ tmp349, <variable>.EndMbn,
	add	r0, r2, r4	@, tmp349, align_mb
	bl	__aeabi_uidiv	@
	mul	ip, r4, r0	@ tmp355, align_mb,
	cmp	r5, ip	@ temp.1286, tmp355
	bhi	.L319	@,
.L299:
	ldrsh	r2, [r7, #6]	@ prephitmp.1239, <variable>.EndMbn
	mov	r1, r4	@, align_mb
	mov	r6, sl	@ i, i.1281
	add	r0, r9, r2	@, tmp431, prephitmp.1239
	bl	__aeabi_uidiv	@
	mov	r1, r4	@, align_mb
	mul	r5, r4, r0	@ temp.1286, align_mb,
	ldrsh	r0, [r8, #4]	@, <variable>.StartMbn
	bl	__aeabi_uidiv	@
	mul	r0, r4, r0	@ D.53012, align_mb,
	cmp	r5, r0	@ temp.1286, D.53012
	bhi	.L313	@,
	add	r2, r0, #1	@ tmp462, D.53012,
	mov	r1, r4	@, align_mb
	cmp	r5, r2	@ temp.1286, tmp462
	beq	.L313	@,
	ldrsh	ip, [r8, #-2]	@ <variable>.EndMbn, <variable>.EndMbn
	sub	r0, ip, #1	@ tmp464, <variable>.EndMbn,
	add	r0, r0, r4	@, tmp464, align_mb
	bl	__aeabi_uidiv	@
	mul	r1, r4, r0	@ tmp467, align_mb,
	cmp	r5, r1	@ temp.1286, tmp467
	bhi	.L319	@,
.L313:
	add	r7, r8, #4	@ ivtmp.1257, tmp436,
	ldrh	r8, [r8, #6]	@ prephitmp.1239, <variable>.EndMbn
	add	r6, sl, #1	@ i, i.1281,
.L297:
	ldr	lr, [fp, #-56]	@, %sfp
	add	sl, r6, #1	@ i.1281, i,
	sxtah	r0, r9, r8	@, tmp431, prephitmp.1239
	mov	r1, r4	@, align_mb
	cmp	sl, lr	@ i.1281,
	add	r8, r7, #4	@ tmp436, ivtmp.1257,
	blt	.L298	@,
	ldr	r9, [fp, #-64]	@ pRepairParam, %sfp
.L316:
	add	r3, r9, r6, asl #2	@, tmp330, pRepairParam, i,
	mov	r1, r4	@, align_mb
	ldrsh	r0, [r3, #42]	@ pretmp.1270, <variable>.EndMbn
	sub	sl, r0, #1	@ pretmp.1276, pretmp.1270,
	add	r0, sl, r4	@, pretmp.1276, align_mb
	bl	__aeabi_uidiv	@
	mul	r5, r4, r0	@ cur_EndMb, align_mb,
	b	.L296	@
.L326:
	ldr	r5, [fp, #-56]	@, %sfp
	add	r3, r6, #1	@ i.1281, i,
	cmp	r3, r5	@ i.1281,
	bge	.L316	@,
	ldr	r2, [fp, #-64]	@, %sfp
	ldr	r1, [fp, #-76]	@, %sfp
	str	r3, [fp, #-80]	@,
	add	r0, r1, r2	@,,
	mov	r1, r4	@, align_mb
	bl	__aeabi_uidiv	@
	mov	r1, r4	@, align_mb
	mul	r5, r4, r0	@ temp.1286, align_mb,
	ldrsh	r0, [sl, #4]	@, <variable>.StartMbn
	bl	__aeabi_uidiv	@
	ldr	r3, [fp, #-80]	@,
	mul	r0, r4, r0	@ D.53012, align_mb,
	cmp	r5, r0	@ temp.1286, D.53012
	bhi	.L310	@,
	add	r0, r0, #1	@ tmp456, D.53012,
	cmp	r5, r0	@ temp.1286, tmp456
	beq	.L310	@,
	ldrsh	lr, [sl, #-2]	@ <variable>.EndMbn, <variable>.EndMbn
	mov	r1, r4	@, align_mb
	sub	r3, lr, #1	@ tmp458, <variable>.EndMbn,
	add	r0, r3, r4	@, tmp458, align_mb
	bl	__aeabi_uidiv	@
	ldr	r3, [fp, #-80]	@,
	mul	ip, r4, r0	@ tmp461, align_mb,
	cmp	r5, ip	@ temp.1286, tmp461
	bhi	.L296	@,
.L310:
	ldrh	r8, [sl, #6]	@ prephitmp.1239, <variable>.EndMbn
	add	r7, r7, #4	@ ivtmp.1257, ivtmp.1257,
	str	r9, [fp, #-64]	@ pRepairParam, %sfp
	mov	r6, r3	@ i, i.1281
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
	mvn	r0, #0	@ D.52898,
	b	.L280	@
.L320:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L327	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC19	@,
	movt	r3, #:upper16:.LC19	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52898,
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
	mvn	r0, #0	@ D.53290,
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
	movw	r3, #:lower16:g_RepairParam	@ g_RepairParam.525,
	movt	r3, #:upper16:g_RepairParam	@ g_RepairParam.525,
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
	mov	r0, #0	@ D.53290,
	b	.L332	@
.L336:
	cmp	r2, #1	@ RepairTime,
	movne	r0, #0	@ D.53290,
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
	ldr	r3, [r0, #44]	@ D.53329, g_vdm_hal_fun_ptr.pfun_VDMHAL_ResetVdm
	cmp	r3, #0	@ D.53329,
	beq	.L342	@,
	mov	r0, #0	@,
	blx	r3	@ D.53329
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
	subs	r1, r0, #0	@ D.53297,
	strne	r1, [r6, #0]	@ D.53297, <variable>.pVdmRegVirAddr
	bne	.L334	@,
	movw	r1, #:lower16:.LC23	@,
	movt	r1, #:upper16:.LC23	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53290,
	b	.L332	@
.L347:
	mov	ip, #0	@ tmp150,
	movw	r1, #:lower16:.LC15	@,
	mov	r0, ip	@, tmp150
	movt	r1, #:upper16:.LC15	@,
	ldr	r2, .L349+4	@,
	str	ip, [sp, #0]	@ tmp150,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53290,
	b	.L332	@
.L341:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC26	@,
	movt	r1, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53290,
	b	.L332	@
.L342:
	mov	r0, r3	@, D.53329
	movw	r1, #:lower16:.LC25	@,
	movw	r2, #2566	@,
	movt	r1, #:upper16:.LC25	@,
	bl	dprint_vfmw	@
	b	.L343	@
.L337:
	mov	r0, r2	@, RepairTime
	movw	r1, #:lower16:.LC24	@,
	movt	r1, #:upper16:.LC24	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53290,
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
	mvn	r0, #0	@ D.52669,
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
	ldr	r7, [r3, #12]	@ D.52694,
	movw	r4, #:lower16:g_BackUp	@ tmp276,
	movt	r4, #:upper16:g_BackUp	@ tmp276,
	cmp	r6, #1	@ LowdlyFlag,
	str	r7, [r4, #0]	@ D.52694, <variable>.BasicCfg1
	ldr	r7, [r3, #28]	@ D.52702,
	str	r7, [r4, #4]	@ D.52702, <variable>.VdmState
	beq	.L376	@,
	add	r2, r3, #4096	@ D.52732, D.52691,
	ldr	r0, [r2, #0]	@ D.52733,* D.52732
	str	r0, [r4, #16]	@ D.52733, <variable>.SedSta
	ldr	ip, [r2, #20]	@ D.52740,
	str	ip, [r4, #20]	@ D.52740, <variable>.SedEnd0
	ldr	r5, [r3, #208]	@ D.52747,
	str	r5, [r4, #8]	@ D.52747, <variable>.Mb0QpInCurrPic
	ldr	r1, [r3, #212]	@ D.52754,
	str	r1, [r4, #12]	@ D.52754, <variable>.SwitchRounding
	ldr	r7, [r3, #176]	@ D.52763,
	str	r7, [r4, #24]	@ D.52763, <variable>.DecCyclePerPic
	ldr	r0, [r3, #180]	@ D.52770,
	str	r0, [r4, #28]	@ D.52770, <variable>.RdBdwidthPerPic
	ldr	r2, [r3, #184]	@ D.52777,
	str	r2, [r4, #32]	@ D.52777, <variable>.WrBdWidthPerPic
	ldr	ip, [r3, #188]	@ D.52784,
	str	ip, [r4, #36]	@ D.52784, <variable>.RdReqPerPic
	ldr	r5, [r3, #192]	@ D.52791,
	str	r5, [r4, #40]	@ D.52791, <variable>.WrReqPerPic
.L365:
	add	r3, r3, #33024	@ tmp275, D.52691,
	movw	r2, #:lower16:g_BackUp	@ ivtmp.1402,
	movt	r2, #:upper16:g_BackUp	@ ivtmp.1402,
	add	r7, r2, #128	@ D.54676, ivtmp.1402,
	mov	r0, r3	@ ivtmp.1398, tmp275
.L366:
	mov	r1, r0	@ tmp279, ivtmp.1398
	add	ip, r2, #4	@ tmp280, ivtmp.1402,
	ldr	r5, [r1], #4	@ D.52800,
	str	r5, [r2, #52]	@ D.52800, <variable>.LumaHistorgam
	add	r2, ip, #4	@ ivtmp.1402, tmp280,
	ldr	r5, [r0, #4]	@ D.52800,
	cmp	r2, r7	@ ivtmp.1402, D.54676
	add	r0, r1, #4	@ ivtmp.1398, tmp279,
	str	r5, [ip, #52]	@ D.52800, <variable>.LumaHistorgam
	bne	.L366	@,
	cmp	r6, #0	@ LowdlyFlag,
	ldr	ip, [r4, #0]	@ <variable>.BasicCfg1, <variable>.BasicCfg1
	ldreq	r2, [r3, #128]	@ D.52809,
	streq	r2, [r4, #48]	@ D.52809, <variable>.LumaSumLow
	and	r2, ip, #15	@ tmp266, <variable>.BasicCfg1,
	ldreq	r3, [r3, #132]	@ D.52816,
	streq	r3, [r4, #44]	@ D.52816, <variable>.LumaSumHigh
	cmp	r2, #5	@ tmp266,
	movw	r3, #:lower16:g_BackUp	@ tmp265,
	movt	r3, #:upper16:g_BackUp	@ tmp265,
	moveq	r0, #0	@ D.52669,
	movne	r0, #0	@ D.52669,
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
	bic	r1, r7, #-16777216	@ DecSliceNum, D.52702,
	bic	r7, r1, #16646144	@ DecSliceNum, DecSliceNum,
	sub	r3, r7, #1	@ tmp240, DecSliceNum,
	cmp	r3, #199	@ tmp240,
	subls	r3, r7, #-1073741823	@ tmp241, DecSliceNum,
	movls	r1, r7, asl #4	@ tmp243, DecSliceNum,
	movhi	r3, #0	@ prephitmp.1378,
	subls	r1, r1, #8	@ prephitmp.1380, tmp243,
	movls	r3, r3, asl #4	@ prephitmp.1378, tmp241,
	movhi	r1, #8	@ prephitmp.1380,
	ldr	r0, [r2, r3]	@ tmp245,* prephitmp.1378
	ldr	r3, [r5, #0]	@ D.52691, <variable>.pVdmRegVirAddr
	str	r0, [r4, #16]	@ tmp245, <variable>.SedSta
	ldr	r2, [r2, r1]	@ tmp247,* prephitmp.1380
	str	r2, [r4, #20]	@ tmp247, <variable>.SedEnd0
	ldr	ip, [r3, #208]	@ temp.1409,
	str	ip, [r4, #8]	@ temp.1409, <variable>.Mb0QpInCurrPic
	ldr	lr, [r3, #212]	@ temp.1411,
	str	lr, [r4, #12]	@ temp.1411, <variable>.SwitchRounding
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
	mvn	r0, #0	@ D.52669,
	b	.L353	@
.L374:
	mov	ip, #0	@ tmp192,
	movw	r1, #:lower16:.LC15	@,
	mov	r0, ip	@, tmp192
	movt	r1, #:upper16:.LC15	@,
	ldr	r2, .L378	@,
	str	ip, [sp, #0]	@ tmp192,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52669,
	b	.L353	@
.L373:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L378	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC27	@,
	movt	r3, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52669,
	b	.L353	@
.L377:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L378	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC29	@,
	movt	r3, #:upper16:.LC29	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52669,
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
	subs	r4, r0, #0	@ D.52528,
	strne	r4, [r5, #0]	@ D.52528, <variable>.pVdmRegVirAddr
	bne	.L385	@,
	movw	r1, #:lower16:.LC32	@,
	ldr	r2, .L398	@,
	movt	r1, #:upper16:.LC32	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ dat, D.52528
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
	ldr	r5, [r3, r2, asl #2]	@ D.52471, s_pstVfmwChan
	cmp	r5, #0	@ D.52471,
	ldrne	r5, [r5, #1744]	@ ModuleLowlyEnable, <variable>.stSynExtraData.s32ModuleLowlyEnable
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
	ldr	r6, [r3, r2, asl #2]	@ D.52377, s_pstVfmwChan
	cmp	r6, #0	@ D.52377,
	ldrne	r6, [r6, #1744]	@ ModuleLowlyEnable, <variable>.stSynExtraData.s32ModuleLowlyEnable
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
	ldr	r2, [r4, #52]	@ D.52395, <variable>.ChanIntState
	cmp	r2, #1	@ D.52395,
	beq	.L438	@,
	cmp	r2, #2	@ D.52395,
	ldr	r1, [r3, #28]	@ dat,
	mvneq	r2, #11	@ tmp165,
	streq	r2, [r3, #32]	@ tmp165,
	beq	.L441	@,
	cmp	r2, #3	@ D.52395,
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
	subs	r2, r0, #0	@ D.52348,
	beq	.L459	@,
	movw	r4, #:lower16:g_pstRegCrg	@ tmp157,
	movt	r4, #:upper16:g_pstRegCrg	@ tmp157,
	mov	r3, #0	@ i,
	movw	r0, #10000	@ tmp158,
	ldr	r2, [r4, #0]	@ g_pstRegCrg.470, g_pstRegCrg
	ldr	r5, [r2, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	orr	r5, r5, #16	@ u32TmpValue, u32TmpValue,
	str	r5, [r2, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r1, [r4, #0]	@ prephitmp.1554, g_pstRegCrg
	b	.L452	@
.L460:
	ldr	lr, [r1, #372]	@ D.52355, <variable>.PERI_CRG93.u32
	add	r3, r3, #1	@ i, i,
	tst	lr, #1	@ D.52355,
	str	lr, [fp, #-24]	@ D.52355, u32TmpValue_93.u32
	bne	.L451	@,
	add	r3, r3, #1	@ i, i,
	cmp	r3, r0	@ i, tmp158
	beq	.L453	@,
.L452:
	ldr	ip, [r1, #372]	@ D.52355, <variable>.PERI_CRG93.u32
	tst	ip, #1	@ D.52355,
	str	ip, [fp, #-24]	@ D.52355, u32TmpValue_93.u32
	beq	.L460	@,
.L451:
	movw	r0, #8999	@ tmp154,
	cmp	r3, r0	@ i, tmp154
	bgt	.L453	@,
.L454:
	bfc	r5, #4, #1	@ u32TmpValue,,
	str	r5, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
.L455:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L453:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC38	@,
	movt	r1, #:upper16:.LC38	@,
	bl	dprint_vfmw	@
	ldr	r1, [r4, #0]	@ prephitmp.1554, g_pstRegCrg
	b	.L454	@
.L459:
	movw	r1, #:lower16:.LC37	@,
	movt	r1, #:upper16:.LC37	@,
	bl	dprint_vfmw	@
	b	.L455	@
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
	bne	.L477	@,
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r2, r0, #0	@ D.52306,
	beq	.L478	@,
	movw	r5, #:lower16:g_HwMem	@ tmp170,
	movw	r6, #:lower16:g_pstRegCrg	@ tmp171,
	movt	r5, #:upper16:g_HwMem	@ tmp170,
	movt	r6, #:upper16:g_pstRegCrg	@ tmp171,
	mov	r2, r4	@ i, VdhId
	movw	ip, #10000	@ tmp172,
	ldr	r1, [r5, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	ldr	r3, [r6, #0]	@ g_pstRegCrg.469, g_pstRegCrg
	ldr	r7, [r1, #36]	@ tmp,
	ldr	r4, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	orr	r4, r4, #64	@ u32TmpValue, u32TmpValue,
	str	r4, [r3, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r1, [r6, #0]	@ prephitmp.1586, g_pstRegCrg
	b	.L469	@
.L480:
	ldr	r3, [r1, #372]	@ D.52327, <variable>.PERI_CRG93.u32
	and	lr, r3, #4	@ tmp179, D.52327,
	str	r3, [fp, #-32]	@ D.52327, u32TmpValue_93.u32
	uxtb	r0, lr	@ tmp180, tmp179
	cmp	r0, #0	@ tmp180,
	bne	.L468	@,
	cmp	r2, ip	@ i, tmp172
	beq	.L479	@,
.L469:
	ldr	r0, [r1, #372]	@ D.52327, <variable>.PERI_CRG93.u32
	add	r2, r2, #1	@ tmp173, i,
	add	r2, r2, #1	@ i, tmp173,
	tst	r0, #4	@ D.52327,
	str	r0, [fp, #-32]	@ D.52327, u32TmpValue_93.u32
	beq	.L480	@,
.L468:
	bfc	r4, #6, #1	@ u32TmpValue,,
	str	r4, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	ip, [r5, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r7, [ip, #36]	@ tmp,
	b	.L470	@
.L477:
	cmp	r4, #1	@ VdhId,
	beq	.L481	@,
	movw	r1, #:lower16:.LC39	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC39	@,
	bl	dprint_vfmw	@
.L470:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L481:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	mov	ip, #0	@ tmp152,
	mov	r0, ip	@, tmp152
	mov	r3, r4	@, VdhId
	movw	r1, #:lower16:.LC15	@,
	ldr	r2, .L482	@,
	movt	r1, #:upper16:.LC15	@,
	str	ip, [sp, #0]	@ tmp152,
	bl	dprint_vfmw	@
	b	.L470	@
.L479:
	movw	r1, #:lower16:.LC40	@,
	mov	r2, r0	@,
	movt	r1, #:upper16:.LC40	@,
	bl	dprint_vfmw	@
	ldr	r1, [r6, #0]	@ prephitmp.1586, g_pstRegCrg
	b	.L468	@
.L478:
	movw	r1, #:lower16:.LC37	@,
	movt	r1, #:upper16:.LC37	@,
	bl	dprint_vfmw	@
	b	.L470	@
.L483:
	.align	2
.L482:
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
	bls	.L490	@,
	movw	r1, #:lower16:.LC41	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC41	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L490:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp139,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp139,
	ldr	r3, [r3, #44]	@ D.51717, g_vdm_hal_fun_ptr.pfun_VDMHAL_ResetVdm
	cmp	r3, #0	@ D.51717,
	beq	.L488	@,
	mov	r0, r4	@, VdhId
	blx	r3	@ D.51717
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L488:
	mov	r0, r3	@, D.51717
	movw	r1, #:lower16:.LC25	@,
	movw	r2, #413	@,
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
	beq	.L517	@,
	ldmib	r3, {r6, r7}	@ phole ldm
	cmp	r6, #0	@ pDecReport,
	ldr	r5, [r3, #0]	@ VidStd, <variable>.VidStd
	beq	.L518	@,
	movw	r0, #1208	@ tmp166,
	movw	r3, #:lower16:g_HwMem	@ tmp167,
	mul	r2, r0, r7	@ tmp165, tmp166, VdhId
	movt	r3, #:upper16:g_HwMem	@ tmp167,
	add	r4, r3, r2	@ pHwMem, tmp167, tmp165
	ldr	r0, [r3, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	cmp	r0, #0	@ <variable>.pVdmRegVirAddr,
	beq	.L519	@,
	movw	r3, #:lower16:g_DSPState	@ tmp305,
	movt	r3, #:upper16:g_DSPState	@ tmp305,
	ldr	r1, [r3, #0]	@ g_DSPState, g_DSPState
	cmp	r1, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	r8, [r3, #4]	@ g_DSPState, g_DSPState
	cmp	r8, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	ip, [r3, #8]	@ g_DSPState, g_DSPState
	cmp	ip, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	lr, [r3, #12]	@ g_DSPState, g_DSPState
	cmp	lr, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	r2, [r3, #16]	@ g_DSPState, g_DSPState
	cmp	r2, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	r0, [r3, #20]	@ g_DSPState, g_DSPState
	cmp	r0, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	r1, [r3, #24]	@ g_DSPState, g_DSPState
	cmp	r1, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	r8, [r3, #28]	@ g_DSPState, g_DSPState
	movw	r3, #:lower16:g_DSPState	@ tmp187,
	movt	r3, #:upper16:g_DSPState	@ tmp187,
	cmp	r8, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	ip, [r3, #32]	@ g_DSPState, g_DSPState
	cmp	ip, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	lr, [r3, #36]	@ g_DSPState, g_DSPState
	cmp	lr, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	r2, [r3, #40]	@ g_DSPState, g_DSPState
	cmp	r2, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	r0, [r3, #44]	@ g_DSPState, g_DSPState
	cmp	r0, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	r1, [r3, #48]	@ g_DSPState, g_DSPState
	cmp	r1, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	r8, [r3, #52]	@ g_DSPState, g_DSPState
	cmp	r8, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	ip, [r3, #56]	@ g_DSPState, g_DSPState
	cmp	ip, #1	@ g_DSPState,
	beq	.L496	@,
	ldr	lr, [r3, #60]	@ g_DSPState, g_DSPState
	cmp	lr, #1	@ g_DSPState,
	movne	r8, #0	@, LowdlyFlag
	moveq	r8, #1	@, LowdlyFlag
.L497:
	mov	r0, r6	@, pDecReport
	mov	r1, #816	@,
	bl	__memzero	@
	movw	r3, #:lower16:g_BackUp	@ tmp304,
	movt	r3, #:upper16:g_BackUp	@ tmp304,
	mov	r0, #180	@ tmp211,
	ldr	r1, [r4, #24]	@ <variable>.VahbStride, <variable>.VahbStride
	mla	ip, r0, r7, r3	@ tmp212, tmp211, VdhId, tmp304
	str	r1, [r6, #4]	@ <variable>.VahbStride, <variable>.ImgStride
	ldr	r2, [ip, #4]	@ D.53201, <variable>.VdmState
	mov	r2, r2, lsr #17	@ tmp214, D.53201,
	and	r0, r2, #3	@ tmp215, tmp214,
	cmp	r0, #1	@ tmp215,
	moveq	r2, #0	@ prephitmp.1649,
	beq	.L499	@,
	eor	lr, r2, #1	@ tmp217, tmp214,
	and	r2, lr, #1	@ tmp219, tmp217,
	cmp	r5, #3	@ VidStd,
	orrne	r2, r2, #1	@,, prephitmp.1649, tmp219
.L499:
	mov	r1, #180	@ tmp227,
	str	r2, [r6, #0]	@ prephitmp.1649, <variable>.RetType
	mla	r3, r1, r7, r3	@ tmp228, tmp227, VdhId, tmp304
	cmp	r5, #0	@ VidStd,
	cmpne	r5, #15	@, VidStd,
	ldr	ip, [r3, #4]	@ <variable>.VdmState, <variable>.VdmState
	bic	r2, ip, #-16777216	@ D.53211, <variable>.VdmState,
	bic	r2, r2, #16646144	@ D.53211, D.53211,
	str	r2, [r6, #8]	@ D.53211, <variable>.DecSliceNum
	bne	.L500	@,
	cmp	r8, #1	@ LowdlyFlag,
	beq	.L520	@,
	movw	ip, #:lower16:g_not_allow_H264FullPictureRepair_flag	@ tmp253,
	movt	ip, #:upper16:g_not_allow_H264FullPictureRepair_flag	@ tmp253,
	ldrb	r1, [ip, #0]	@ zero_extendqisi2	@ g_not_allow_H264FullPictureRepair_flag, g_not_allow_H264FullPictureRepair_flag
	cmp	r1, #0	@ g_not_allow_H264FullPictureRepair_flag,
	beq	.L521	@,
.L500:
	cmp	r2, #200	@ D.53211,
	bhi	.L522	@,
.L502:
	ldr	r8, [r4, #32]	@ D.53236, <variable>.MsgSlotAddr
	mov	r0, r8	@, D.53236
	bl	MEM_Phy2Vir	@
	subs	r1, r0, #0	@ D.53238,
	beq	.L523	@,
	movw	r4, #:lower16:g_UpMsg	@ tmp306,
	movt	r4, #:upper16:g_UpMsg	@ tmp306,
	mov	r5, #3200	@ tmp276,
	ldr	lr, [r6, #8]	@ <variable>.DecSliceNum, <variable>.DecSliceNum
	mla	r5, r5, r7, r4	@ tmp277, tmp276, VdhId, tmp306
	mov	r2, lr, asl #2	@, <variable>.DecSliceNum,
	mov	r0, r5	@, tmp277
	bl	VDMHAL_V300R001_ReadMsgSlot	@
	ldr	ip, [r6, #8]	@ temp.1696, <variable>.DecSliceNum
	cmp	ip, #0	@ temp.1696,
	beq	.L504	@,
	ldrh	r2, [r5, #4]	@, g_UpMsg
	mov	r0, #1	@ i,
	cmp	r0, ip	@ i, temp.1696
	sub	r3, ip, #1	@ tmp309, temp.1696,
	strh	r2, [r6, #12]	@ movhi	@, <variable>.SliceMbRange
	and	r2, r3, r0	@ tmp311, tmp309,
	ldrh	r1, [r5, #8]	@, g_UpMsg
	add	r3, r6, #4	@ ivtmp.1679, pDecReport,
	add	r5, r5, #16	@ ivtmp.1676, tmp277,
	strh	r1, [r6, #14]	@ movhi	@, <variable>.SliceMbRange
	bcs	.L504	@,
	cmp	r2, #0	@ tmp311,
	beq	.L505	@,
	ldrh	r1, [r5, #4]	@, g_UpMsg
	mov	r0, #2	@ i,
	cmp	r0, ip	@ i, temp.1696
	strh	r1, [r3, #12]	@ movhi	@, <variable>.SliceMbRange
	ldrh	r2, [r5, #8]	@, g_UpMsg
	add	r5, r5, #16	@ ivtmp.1676, ivtmp.1676,
	strh	r2, [r3, #14]	@ movhi	@, <variable>.SliceMbRange
	add	r3, r3, #4	@ ivtmp.1679, ivtmp.1679,
	bcs	.L504	@,
.L505:
	ldrh	lr, [r5, #4]	@, g_UpMsg
	add	r2, r5, #16	@ tmp313, ivtmp.1676,
	add	r0, r0, #2	@ i, i,
	cmp	r0, ip	@ i, temp.1696
	strh	lr, [r3, #12]	@ movhi	@, <variable>.SliceMbRange
	add	lr, r3, #4	@ tmp314, ivtmp.1679,
	ldrh	r1, [r5, #8]	@, g_UpMsg
	strh	r1, [r3, #14]	@ movhi	@, <variable>.SliceMbRange
	add	r3, lr, #4	@ ivtmp.1679, tmp314,
	ldrh	r5, [r2, #4]	@, g_UpMsg
	strh	r5, [lr, #12]	@ movhi	@, <variable>.SliceMbRange
	add	r5, r2, #16	@ ivtmp.1676, tmp313,
	ldrh	r1, [r2, #8]	@, g_UpMsg
	strh	r1, [lr, #14]	@ movhi	@, <variable>.SliceMbRange
	bcc	.L505	@,
.L504:
	mov	r0, #6	@,
	bl	IsDprintTypeEnable	@
	cmp	r0, #0	@ D.53252
	bne	.L524	@,
.L493:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L496:
	mov	r8, #1	@ LowdlyFlag,
	b	.L497	@
.L524:
	ldr	r2, [r6, #8]	@, <variable>.DecSliceNum
	mov	r0, #6	@,
	movw	r1, #:lower16:.LC45	@,
	movt	r1, #:upper16:.LC45	@,
	bl	dprint_vfmw	@
	mov	r2, r8	@, D.53236
	mov	r0, #6	@,
	movw	r1, #:lower16:.LC46	@,
	movt	r1, #:upper16:.LC46	@,
	bl	dprint_vfmw	@
	ldr	r0, [r6, #8]	@ <variable>.DecSliceNum, <variable>.DecSliceNum
	mov	ip, r0, asl #2	@ tmp289, <variable>.DecSliceNum,
	cmp	ip, #3	@ tmp289,
	beq	.L507	@,
	mov	r3, #3200	@ tmp292,
	mov	r5, #0	@ i_cnt,
	mla	r4, r3, r7, r4	@ ivtmp.1666, tmp292, VdhId, tmp306
.L508:
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
	add	r4, r4, #16	@ ivtmp.1666, ivtmp.1666,
	str	r7, [sp, #8]	@ tmp297,
	bl	dprint_vfmw	@
	ldr	ip, [r6, #8]	@ <variable>.DecSliceNum, <variable>.DecSliceNum
	mov	r1, ip, asl #2	@ tmp298, <variable>.DecSliceNum,
	sub	r2, r1, #3	@ tmp300, tmp298,
	cmp	r2, r5	@ tmp300, i_cnt
	bhi	.L508	@,
.L507:
	mov	r0, #6	@,
	movw	r1, #:lower16:.LC48	@,
	movt	r1, #:upper16:.LC48	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.53178,
	b	.L493	@
.L522:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC44	@,
	mov	r3, #200	@,
	movt	r1, #:upper16:.LC44	@,
	bl	dprint_vfmw	@
	mov	r8, #0	@ tmp270,
	str	r8, [r6, #8]	@ tmp270, <variable>.DecSliceNum
	b	.L502	@
.L521:
	ldrb	r0, [r3, #19]	@ zero_extendqisi2	@ tmp261, <variable>.SedSta
	and	r3, r0, #3	@ tmp263, tmp261,
	cmp	r3, #2	@ tmp263,
	bne	.L500	@,
	mov	r2, #1	@ tmp264,
	strh	r1, [r6, #14]	@ movhi	@ g_not_allow_H264FullPictureRepair_flag, <variable>.SliceMbRange
	mov	r0, r1	@ D.53178, g_not_allow_H264FullPictureRepair_flag
	strh	r1, [r6, #12]	@ movhi	@ g_not_allow_H264FullPictureRepair_flag, <variable>.SliceMbRange
	str	r2, [r6, #8]	@ tmp264, <variable>.DecSliceNum
	b	.L493	@
.L520:
	ldr	r0, [r3, #16]	@ <variable>.SedSta, <variable>.SedSta
	ubfx	r3, r0, #21, #2	@ tmp247, <variable>.SedSta,,
	cmp	r3, #2	@ tmp247,
	bne	.L500	@,
	mov	lr, #0	@ movhi	@,
	str	r8, [r6, #8]	@ LowdlyFlag, <variable>.DecSliceNum
	strh	lr, [r6, #14]	@ movhi	@, <variable>.SliceMbRange
	mov	r0, #0	@ D.53178,
	strh	lr, [r6, #12]	@ movhi	@, <variable>.SliceMbRange
	b	.L493	@
.L523:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L525	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC29	@,
	movt	r3, #:upper16:.LC29	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53178,
	b	.L493	@
.L517:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L525	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC42	@,
	movt	r3, #:upper16:.LC42	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53178,
	b	.L493	@
.L519:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L525	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC3	@,
	movt	r3, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53178,
	b	.L493	@
.L518:
	mov	r0, r6	@, pDecReport
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L525	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC43	@,
	movt	r3, #:upper16:.LC43	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.53178,
	b	.L493	@
.L526:
	.align	2
.L525:
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
	beq	.L528	@,
	cmp	r0, #6	@ VidStd,
	movw	r6, #:lower16:s_RegPhyBaseAddr	@ tmp153,
	movt	r6, #:upper16:s_RegPhyBaseAddr	@ tmp153,
	moveq	r1, #1	@,
	movne	r1, #0	@,
	ldr	r0, [r6, #0]	@, s_RegPhyBaseAddr
	bl	MEM_WritePhyWord	@
	cmp	r7, #0	@ VdhId,
	bne	.L552	@,
	ldr	r0, [r6, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	mov	r1, #1	@,
	add	r0, r0, #8	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
.L534:
	cmp	r4, #16	@ VidStd,
	ldrls	pc, [pc, r4, asl #2]	@ VidStd
	b	.L528	@
.L549:
	.word	.L547
	.word	.L538
	.word	.L539
	.word	.L540
	.word	.L528
	.word	.L541
	.word	.L542
	.word	.L528
	.word	.L543
	.word	.L544
	.word	.L545
	.word	.L545
	.word	.L545
	.word	.L546
	.word	.L528
	.word	.L547
	.word	.L548
.L552:
	cmp	r7, #1	@ VdhId,
	beq	.L553	@,
	cmp	r7, #0	@ VdhId,
	ble	.L534	@,
.L535:
	mov	ip, #0	@ tmp151,
	mov	r3, r7	@, VdhId
	mov	r0, ip	@, tmp151
	movw	r1, #:lower16:.LC15	@,
	ldr	r2, .L554	@,
	movt	r1, #:upper16:.LC15	@,
	str	ip, [sp, #0]	@ tmp151,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52569,
.L536:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L553:
	movw	r3, #:lower16:s_RegPhyBaseAddr_1	@ tmp145,
	movt	r3, #:upper16:s_RegPhyBaseAddr_1	@ tmp145,
	mov	r1, r7	@, VdhId
	ldr	r2, [r3, #0]	@ s_RegPhyBaseAddr_1, s_RegPhyBaseAddr_1
	add	r0, r2, #8	@, s_RegPhyBaseAddr_1,
	bl	MEM_WritePhyWord	@
	b	.L535	@
.L547:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	H264HAL_V300R001_StartDec	@
	b	.L536	@
.L528:
	mvn	r0, #0	@ D.52569,
	b	.L536	@
.L545:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	VP6HAL_V300R001_StartDec	@
	b	.L536	@
.L540:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	MP2HAL_V300R001_StartDec	@
	b	.L536	@
.L541:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	DIVX3HAL_V300R001_StartDec	@
	b	.L536	@
.L542:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	AVSHAL_V300R001_StartDec	@
	b	.L536	@
.L543:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	RV8HAL_V300R001_StartDec	@
	b	.L536	@
.L538:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	VC1HAL_V300R001_StartDec	@
	b	.L536	@
.L539:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	MP4HAL_V300R001_StartDec	@
	b	.L536	@
.L548:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	HEVCHAL_V300R001_StartDec	@
	b	.L536	@
.L546:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	VP8HAL_V300R001_StartDec	@
	b	.L536	@
.L544:
	mov	r0, r5	@, pDecParam
	mov	r1, r7	@, VdhId
	bl	RV9HAL_V300R001_StartDec	@
	b	.L536	@
.L555:
	.align	2
.L554:
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
	beq	.L557	@,
	cmp	r4, #0	@ eFlag,
	movlt	r9, #19	@ VidStd,
	blt	.L559	@,
	mov	r0, r4	@, eFlag
	movw	r6, #:lower16:s_pstVfmwChan	@ tmp607,
	bl	VCTRL_GetVidStd	@
	movt	r6, #:upper16:s_pstVfmwChan	@ tmp607,
	mov	r9, r0	@ VidStd,
	ldr	r0, [r6, r4, asl #2]	@ D.51929, s_pstVfmwChan
	ldr	r3, [r0, #1888]	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r3, #1	@ <variable>.stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn,
	beq	.L675	@,
.L559:
	cmp	r5, #0	@ MemAddr,
	beq	.L676	@,
	cmp	sl, #31	@ Height,
	movgt	lr, #0	@, tmp434
	movle	lr, #1	@, tmp434
	sub	ip, r7, #32	@ tmp429, Width,
	movw	r3, #8160	@ tmp431,
	cmp	ip, r3	@ tmp429, tmp431
	movls	r0, lr	@, tmp437, tmp434
	orrhi	r0, lr, #1	@,, tmp437, tmp434
	cmp	r0, #0	@ tmp437,
	bne	.L598	@,
	cmp	sl, #8192	@ Height,
	bgt	.L598	@,
	cmp	r8, #0	@ pVdmMemArrange,
	beq	.L677	@,
	mov	r0, r8	@, pVdmMemArrange
	mov	r1, #940	@,
	bl	__memzero	@
	add	r0, r7, #15	@ tmp446, Width,
	add	r2, sl, #15	@ tmp447, Height,
	movw	r1, #:lower16:g_not_direct_8x8_inference_flag	@ tmp455,
	mov	r3, r0, asr #4	@ ImgWidthInMb, tmp446,
	movt	r1, #:upper16:g_not_direct_8x8_inference_flag	@ tmp455,
	mov	r0, r2, asr #4	@ ImgHeightInMb, tmp447,
	ldr	r2, [fp, #4]	@ PmvNum, PmvNum
	ldrb	r6, [r1, #0]	@ zero_extendqisi2	@ g_not_direct_8x8_inference_flag, g_not_direct_8x8_inference_flag
	cmp	r2, #20	@ PmvNum,
	movge	r2, #20	@ PmvNum.1826,
	cmp	r0, #36	@ ImgHeightInMb,
	cmple	r3, #45	@, ImgWidthInMb,
	mul	r1, r3, r0	@ tmp457, ImgWidthInMb, ImgHeightInMb
	movle	ip, #64	@, ColMbSize,
	movgt	ip, #32	@, ColMbSize,
	cmp	r6, #1	@ g_not_direct_8x8_inference_flag,
	moveq	ip, #64	@ ColMbSize,
	cmp	r9, #16	@ VidStd,
	moveq	ip, #16	@ ColMbSize,
	mul	lr, ip, r1	@ tmp458, ColMbSize, tmp457
	ldr	ip, [fp, #-76]	@, %sfp
	add	r6, lr, #127	@ tmp459, tmp458,
	bic	r6, r6, #127	@ PmvSlotLen, tmp459,
	mul	r1, r2, r6	@ PmvPoolSize, PmvNum.1826, PmvSlotLen
	cmp	r1, ip	@ PmvPoolSize,
	bge	.L678	@,
	cmp	r9, #16	@ VidStd,
	mov	r3, r3, asl #4	@ ImgWidthInPixAln, ImgWidthInMb,
	mov	ip, r6, asr #1	@ tmp466, PmvSlotLen,
	sub	lr, r3, #1	@ tmp470, ImgWidthInPixAln,
	str	ip, [r8, #932]	@ tmp466, <variable>.HafPmvOffset
	addeq	ip, r7, #255	@ tmp467, Width,
	addne	ip, r3, #255	@ tmp468, ImgWidthInPixAln,
	str	r2, [r8, #936]	@ PmvNum.1826, <variable>.ValidPMVNum
	bic	r2, ip, #255	@ SlotWidth, tmp468,
	movw	ip, #2047	@ tmp471,
	cmp	lr, ip	@ tmp470, tmp471
	mov	lr, r2, asl #4	@ tmp469, SlotWidth,
	str	lr, [r8, #0]	@ tmp469, <variable>.VahbStride
	bhi	.L679	@,
.L607:
	mov	ip, #16	@ level,
.L609:
	ldr	r3, [fp, #12]	@, UserDec
	cmp	r3, #1	@,
	mov	r3, r0, asl #4	@ ImgHeightInPixAln, ImgHeightInMb,
	addeq	r0, r3, r0, asl #5	@, tmp483, ImgHeightInPixAln, ImgHeightInMb,
	muleq	r7, r2, r0	@ ImgSlotLen, SlotWidth, tmp483
	beq	.L612	@,
	cmp	r9, #16	@ VidStd,
	beq	.L680	@,
	adds	r0, r3, #31	@ tmp491, ImgHeightInPixAln,
	addmi	r0, r3, #62	@, tmp492, ImgHeightInPixAln,
	mov	r7, r0, asr #5	@ tmp494, tmp492,
	add	lr, r7, r7, asl #1	@, tmp497, tmp494, tmp494,
	mov	r0, lr, asl #5	@ tmp498, tmp497,
	mul	r7, r2, r0	@ tmp505, SlotWidth, tmp498
	mul	r0, ip, r0	@ tmp499, level, tmp498
	mov	lr, r7, asr #1	@ tmp509, tmp505,
	add	r7, lr, r0, lsr #1	@, ImgSlotLen, tmp509, tmp499,
.L612:
	cmp	r4, #0	@ eFlag,
	blt	.L614	@,
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
	beq	.L681	@,
	ldr	r4, [fp, #-68]	@, %sfp
	add	r0, r0, #15	@, ChanHeight,
	str	r0, [fp, #-68]	@, %sfp
	add	lr, r4, #15	@ tmp518,,
	movw	r4, #2047	@ tmp524,
	bic	lr, lr, #15	@ ChanImgWidthInPixAln, tmp518,
	sub	r0, lr, #1	@, ChanImgWidthInPixAln,
	str	r0, [fp, #-64]	@, %sfp
	add	r0, lr, #255	@, ChanImgWidthInPixAln,
	str	r0, [fp, #-80]	@, %sfp
	ldr	r0, [fp, #-64]	@, %sfp
	cmp	r0, r4	@, tmp524
	ldr	r0, [fp, #-68]	@, %sfp
	bic	r0, r0, #15	@,,
	str	r0, [fp, #-68]	@, %sfp
	ldr	r0, [fp, #-80]	@, %sfp
	bic	r0, r0, #255	@,,
	str	r0, [fp, #-80]	@, %sfp
	bls	.L616	@,
	sub	r0, lr, #2048	@ tmp525, ChanImgWidthInPixAln,
	sub	r0, r0, #1	@ tmp525, tmp525,
	cmp	r0, r4	@ tmp525, tmp524
	movls	r4, #32	@,
	strls	r4, [fp, #-64]	@, %sfp
	bhi	.L682	@,
.L618:
	ldr	r0, [fp, #12]	@, UserDec
	cmp	r0, #1	@,
	beq	.L683	@,
.L620:
	ldr	r0, [fp, #-68]	@, %sfp
	ldr	r4, [fp, #-80]	@, %sfp
	adds	lr, r0, #31	@ tmp537,,
	addmi	lr, r0, #62	@, tmp538,,
	mov	r0, lr, asr #5	@ tmp540, tmp538,
	mul	lr, r0, r4	@ tmp547, tmp540,
	add	r4, r0, r0, asl #1	@, tmp543, tmp540, tmp540,
	mov	r0, r4, asl #5	@ tmp544, tmp543,
	ldr	r4, [fp, #-64]	@, %sfp
	mul	r0, r4, r0	@ tmp545,, tmp544
	add	lr, lr, lr, asl #1	@, tmp550, tmp547, tmp547,
	mov	lr, lr, asl #5	@ tmp551, tmp550,
	mov	lr, lr, asr #1	@ tmp555, tmp551,
	add	r0, lr, r0, lsr #1	@, ChanSlotLen, tmp555, tmp545,
.L621:
	cmp	r7, r0	@ ImgSlotLen, ChanSlotLen
	bgt	.L684	@,
.L614:
	cmp	r9, #16	@ VidStd,
	muleq	r2, sl, r2	@ tmp560, Height, SlotWidth
	streq	r2, [r8, #536]	@ tmp560, <variable>.ChromOffset
	beq	.L623	@,
	adds	r0, r3, #31	@ tmp561, ImgHeightInPixAln,
	addmi	r9, r3, #62	@, tmp562, ImgHeightInPixAln,
	movpl	r9, r0	@, tmp562, tmp561
	mov	lr, r9, asr #5	@ tmp564, tmp562,
	mul	r2, lr, r2	@ tmp566, tmp564, SlotWidth
	mla	r3, lr, ip, r2	@ tmp567, tmp564, level, tmp566
	mov	r9, r3, asl #5	@ tmp568, tmp567,
	str	r9, [r8, #536]	@ tmp568, <variable>.ChromOffset
.L623:
	ldr	r9, [fp, #8]	@, FrameNum
	cmp	r9, #0	@,
	streq	r9, [r8, #548]	@, <variable>.ValidFrameNum
	bne	.L685	@,
.L625:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L691	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC58	@,
	movt	r3, #:upper16:.LC58	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
.L578:
	mov	r0, r3	@, ret
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L679:
	sub	lr, r3, #2048	@ tmp472, ImgWidthInPixAln,
	sub	lr, lr, #1	@ tmp472, tmp472,
	cmp	lr, ip	@ tmp472, tmp471
	movls	ip, #32	@ level,
	bls	.L609	@,
	sub	lr, r3, #4096	@ tmp475, ImgWidthInPixAln,
	sub	lr, lr, #1	@ tmp475, tmp475,
	cmp	lr, ip	@ tmp475, tmp471
	movls	ip, #48	@ level,
	bls	.L609	@,
	sub	lr, r3, #6144	@ tmp478, ImgWidthInPixAln,
	sub	r3, lr, #1	@ tmp478, tmp478,
	cmp	r3, ip	@ tmp478, tmp471
	movls	ip, #64	@ level,
	bls	.L609	@,
	b	.L607	@
.L685:
	add	lr, r5, #1020	@ tmp570, MemAddr,
	ldr	r2, [fp, #-76]	@, %sfp
	add	sl, lr, #3	@ tmp570, tmp570,
	bic	r4, sl, #1020	@ tmp572, tmp570,
	rsb	r3, r1, r2	@ tmp574, PmvPoolSize,
	bic	ip, r4, #3	@ tmp572, tmp572,
	mov	r1, r7	@, ImgSlotLen
	rsb	r4, r5, ip	@ Offset, MemAddr, tmp572
	ldr	sl, [fp, #8]	@ D.52100, FrameNum
	rsb	r0, r4, r3	@, Offset, tmp574
	bl	__aeabi_idiv	@
	cmp	sl, #64	@ D.52100,
	movge	sl, #64	@ D.52100,
	cmp	sl, r0	@ D.52100,
	movlt	r0, sl	@ D.52100, D.52100
	movge	r0, r0	@ D.52100,
	str	r0, [r8, #548]	@ D.52100, <variable>.ValidFrameNum
	cmp	r0, #0	@ D.52100,
	beq	.L625	@,
	ble	.L686	@,
	cmp	r0, #1	@ D.52100,
	add	r1, r4, r5	@ ivtmp.1802, Offset, MemAddr
	sub	r3, r0, #1	@ tmp624, D.52100,
	str	r1, [r8, #8]	@ ivtmp.1802, <variable>.FrameAddr
	and	ip, r3, #1	@ tmp626, tmp624,
	add	r2, r1, r7	@ ivtmp.1802, ivtmp.1802, ImgSlotLen
	add	r3, r8, #4	@ ivtmp.1806, pVdmMemArrange,
	mov	r1, #1	@ i,
	ble	.L662	@,
	cmp	ip, #0	@ tmp626,
	beq	.L628	@,
	mov	r1, #2	@ i,
	cmp	r0, r1	@ D.52100, i
	str	r2, [r3, #8]	@ ivtmp.1802, <variable>.FrameAddr
	add	r2, r2, r7	@ ivtmp.1802, ivtmp.1802, ImgSlotLen
	add	r3, r3, #4	@ ivtmp.1806, ivtmp.1806,
	ble	.L662	@,
.L628:
	add	r1, r1, #2	@ i, i,
	add	ip, r3, #4	@ tmp628, ivtmp.1806,
	cmp	r0, r1	@ D.52100, i
	add	sl, r2, r7	@ ivtmp.1802, ivtmp.1802, ImgSlotLen
	str	r2, [r3, #8]	@ ivtmp.1802, <variable>.FrameAddr
	add	r2, sl, r7	@ ivtmp.1802, ivtmp.1802, ImgSlotLen
	str	sl, [ip, #8]	@ ivtmp.1802, <variable>.FrameAddr
	add	r3, ip, #4	@ ivtmp.1806, tmp628,
	bgt	.L628	@,
.L662:
	mla	r4, r0, r7, r4	@ Offset.1836, D.52100, ImgSlotLen, Offset
	ldr	r0, [r8, #548]	@ D.52100, <variable>.ValidFrameNum
	mov	r1, #1	@ i.1837,
	add	r3, r8, #4	@ ivtmp.1870, pVdmMemArrange,
	cmp	r0, r1	@ D.52100,
	sub	r2, r0, #1	@ tmp618, D.52100,
	add	lr, r4, r5	@ ivtmp.1795, Offset.1836, MemAddr
	and	ip, r2, r1	@ tmp620, tmp618,
	str	lr, [r8, #264]	@ ivtmp.1795, <variable>.LineNumAddr
	add	r2, lr, #32	@ ivtmp.1795, ivtmp.1795,
	ble	.L633	@,
	cmp	ip, #0	@ tmp620,
	beq	.L629	@,
	mov	r1, #2	@ i.1837,
	cmp	r0, r1	@ D.52100, i.1837
	str	r2, [r3, #264]	@ ivtmp.1795, <variable>.LineNumAddr
	add	r2, r2, #32	@ ivtmp.1795, ivtmp.1795,
	add	r3, r3, #4	@ ivtmp.1870, ivtmp.1870,
	ble	.L633	@,
.L629:
	add	r1, r1, #2	@ i.1837, i.1837,
	add	ip, r3, #4	@ tmp621, ivtmp.1870,
	cmp	r0, r1	@ D.52100, i.1837
	add	r7, r2, #32	@ tmp623, ivtmp.1795,
	str	r2, [r3, #264]	@ ivtmp.1795, <variable>.LineNumAddr
	add	r2, r7, #32	@ ivtmp.1795, tmp623,
	str	r7, [ip, #264]	@ tmp623, <variable>.LineNumAddr
	add	r3, ip, #4	@ ivtmp.1870, tmp621,
	bgt	.L629	@,
.L633:
	ldr	sl, [r8, #936]	@ D.52113, <variable>.ValidPMVNum
	add	r0, r4, r0, asl #5	@, Offset.1838, Offset.1836, D.52100,
	add	r2, r0, r5	@ MemAddr.1839, Offset.1838, MemAddr
	cmp	sl, #0	@ D.52113,
	ble	.L630	@,
	mov	r1, #1	@ i.1840,
	cmp	r1, sl	@ i.1840, D.52113
	sub	r3, sl, #1	@ tmp613, D.52113,
	str	r2, [r8, #812]	@ MemAddr.1839, <variable>.PMVAddr
	and	ip, r3, r1	@ tmp615, tmp613,
	add	r2, r2, r6	@ ivtmp.1788, MemAddr.1839, PmvSlotLen
	add	r3, r8, #4	@ ivtmp.1792, pVdmMemArrange,
	bge	.L630	@,
	cmp	ip, #0	@ tmp615,
	beq	.L631	@,
	mov	r1, #2	@ i.1840,
	cmp	r1, sl	@ i.1840, D.52113
	str	r2, [r3, #812]	@ ivtmp.1788, <variable>.PMVAddr
	add	r2, r2, r6	@ ivtmp.1788, ivtmp.1788, PmvSlotLen
	add	r3, r3, #4	@ ivtmp.1792, ivtmp.1792,
	bge	.L630	@,
.L631:
	add	r1, r1, #2	@ i.1840, i.1840,
	add	lr, r3, #4	@ tmp617, ivtmp.1792,
	cmp	r1, sl	@ i.1840, D.52113
	add	r4, r2, r6	@ ivtmp.1788, ivtmp.1788, PmvSlotLen
	str	r2, [r3, #812]	@ ivtmp.1788, <variable>.PMVAddr
	add	r2, r4, r6	@ ivtmp.1788, ivtmp.1788, PmvSlotLen
	str	r4, [lr, #812]	@ ivtmp.1788, <variable>.PMVAddr
	add	r3, lr, #4	@ ivtmp.1792, tmp617,
	blt	.L631	@,
.L630:
	mla	r0, sl, r6, r0	@ tmp587, D.52113, PmvSlotLen, Offset.1838
	mov	r3, #0	@ ret,
	str	r0, [r8, #4]	@ tmp587, <variable>.TotalMemUsed
	b	.L578	@
.L557:
	mov	r9, #16	@ VidStd,
	b	.L559	@
.L682:
	sub	r0, lr, #4096	@ tmp528, ChanImgWidthInPixAln,
	sub	r0, r0, #1	@ tmp528, tmp528,
	cmp	r0, r4	@ tmp528, tmp524
	movls	lr, #48	@,
	strls	lr, [fp, #-64]	@, %sfp
	bls	.L618	@,
	sub	lr, lr, #6144	@ tmp531, ChanImgWidthInPixAln,
	sub	lr, lr, #1	@ tmp531, tmp531,
	cmp	lr, r4	@ tmp531, tmp524
	movls	r0, #64	@,
	strls	r0, [fp, #-64]	@, %sfp
	bls	.L618	@,
.L616:
	ldr	r0, [fp, #12]	@, UserDec
	mov	r4, #16	@,
	str	r4, [fp, #-64]	@, %sfp
	cmp	r0, #1	@,
	bne	.L620	@,
.L683:
	ldr	r4, [fp, #-68]	@, %sfp
	ldr	lr, [fp, #-80]	@, %sfp
	add	r0, r4, r4, asl #1	@, tmp536,,,
	mul	r0, lr, r0	@ ChanSlotLen,, tmp536
	b	.L621	@
.L675:
	movw	r2, #:lower16:249200	@ tmp226,
	movt	r2, #:upper16:249200	@ tmp226,
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
	bne	.L560	@,
	cmp	sl, #8192	@ Height,
	ble	.L561	@,
.L560:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L691+4	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC11	@,
	movt	r3, #:upper16:.LC11	@,
	bl	dprint_vfmw	@
	mvn	r9, #0	@ CurFsSize,
.L562:
	mov	r2, r9	@, CurFsSize
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC49	@,
	movt	r1, #:upper16:.LC49	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L578	@
.L680:
	add	r0, sl, sl, asl #1	@, tmp486, Height, Height,
	mul	r7, r2, r0	@ tmp487, SlotWidth, tmp486
	mov	r7, r7, asr #1	@ ImgSlotLen, tmp487,
	b	.L612	@
.L598:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L691	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC11	@,
	movt	r3, #:upper16:.LC11	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L578	@
.L561:
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
	beq	.L566	@,
	mul	lr, r2, r3	@ tmp251, ImgWidthInMb, ImgHeightInMb
	add	r5, r1, #255	@ tmp254, ImgWidthInPixAln,
	bic	r5, r5, #255	@ SlotWidth, tmp254,
	mul	r3, ip, lr	@ tmp252, ColMbSize, tmp251
	add	lr, r3, #127	@ tmp253, tmp252,
	bic	r3, lr, #127	@ PmvSlotLen, tmp253,
.L632:
	sub	ip, r1, #1	@ tmp255, ImgWidthInPixAln,
	movw	r2, #2047	@ tmp256,
	cmp	ip, r2	@ tmp255, tmp256
	movls	r2, #16	@ level,
	bls	.L568	@,
	sub	ip, r1, #2048	@ tmp257, ImgWidthInPixAln,
	sub	lr, ip, #1	@ tmp257, tmp257,
	cmp	lr, r2	@ tmp257, tmp256
	movls	r2, #32	@ level,
	bls	.L568	@,
	sub	ip, r1, #4096	@ tmp260, ImgWidthInPixAln,
	sub	lr, ip, #1	@ tmp260, tmp260,
	cmp	lr, r2	@ tmp260, tmp256
	movls	r2, #48	@ level,
	bls	.L568	@,
	sub	lr, r1, #6144	@ tmp263, ImgWidthInPixAln,
	sub	r1, lr, #1	@ tmp263, tmp263,
	cmp	r1, r2	@ tmp263, tmp256
	movls	r2, #64	@ level,
	movhi	r2, #0	@ level,
.L568:
	ldr	ip, [fp, #12]	@, UserDec
	cmp	ip, #1	@,
	beq	.L687	@,
	cmp	r9, #16	@ VidStd,
	beq	.L688	@,
	ldr	r1, [fp, #-72]	@, %sfp
	mov	ip, #96	@ tmp300,
	add	r0, r0, #249856	@, D.51929,
	str	r2, [fp, #-88]	@,
	add	r9, r1, #31	@,,
	add	r0, r0, #656	@,,
	mov	r1, #948	@,
	str	r9, [fp, #-72]	@, %sfp
	mov	lr, r9, asr #5	@ tmp299,,
	str	r3, [fp, #-84]	@,
	movw	r9, #:lower16:250512	@ tmp309,
	movt	r9, #:upper16:250512	@ tmp309,
	mul	ip, ip, lr	@ D.55059, tmp300, tmp299
	mul	lr, ip, r5	@ tmp303, D.55059, SlotWidth
	mul	ip, ip, r2	@, D.55059, level
	str	ip, [fp, #-64]	@, %sfp
	mov	ip, lr, asr #1	@ tmp307, tmp303,
	ldr	lr, [fp, #-64]	@, %sfp
	add	ip, ip, lr, asr #1	@,, tmp307,,
	str	ip, [fp, #-64]	@, %sfp
	bl	__memzero	@
	ldr	r3, [fp, #-84]	@,
	ldr	lr, [r6, r4, asl #2]	@ tmp311, s_pstVfmwChan
	movw	r1, #:lower16:251444	@ tmp312,
	movt	r1, #:upper16:251444	@ tmp312,
	mov	r2, r5, asl #4	@ tmp319, SlotWidth,
	mov	ip, r3, asr #1	@ tmp315, PmvSlotLen,
	str	ip, [lr, r1]	@ tmp315, <variable>.stMemArrangeInfo.stMemArrange.HafPmvOffset
	ldr	r0, [r6, r4, asl #2]	@ tmp317, s_pstVfmwChan
	str	r2, [r0, r9]	@ tmp319, <variable>.stMemArrangeInfo.stMemArrange.VahbStride
	ldr	r2, [fp, #-88]	@,
.L574:
	add	r1, r2, r5	@ tmp330, level, SlotWidth
	ldr	r5, [fp, #-72]	@, %sfp
	ldr	lr, [r6, r4, asl #2]	@ tmp325, s_pstVfmwChan
	movw	r0, #:lower16:251048	@ tmp326,
	bic	ip, r5, #31	@ tmp329,,
	movt	r0, #:upper16:251048	@ tmp326,
	mul	r9, r1, ip	@ tmp331, tmp330, tmp329
	str	r9, [lr, r0]	@ tmp331, <variable>.stMemArrangeInfo.stMemArrange.ChromOffset
.L576:
	ldr	r2, [r6, r4, asl #2]	@ tmp333, s_pstVfmwChan
	movw	r0, #:lower16:251452	@ tmp334,
	ldr	r5, [fp, #-64]	@, %sfp
	movt	r0, #:upper16:251452	@ tmp334,
	ldr	r1, [fp, #-64]	@, %sfp
	add	r9, r3, #1056	@ tmp338, PmvSlotLen,
	str	r5, [r2, r0]	@, <variable>.stMemArrangeInfo.ImgSlotLen
	adds	r9, r9, r1	@ CurFsSize, tmp338,
	ldr	lr, [r6, r4, asl #2]	@ tmp336, s_pstVfmwChan
	movw	r1, #:lower16:251456	@ tmp337,
	movt	r1, #:upper16:251456	@ tmp337,
	movw	r2, #:lower16:s_pstVfmwChan	@ tmp332,
	movt	r2, #:upper16:s_pstVfmwChan	@ tmp332,
	str	r3, [lr, r1]	@ PmvSlotLen, <variable>.stMemArrangeInfo.PmvSlotLen
	bmi	.L562	@,
	ldr	r5, [r2, r4, asl #2]	@ prephitmp.1769, s_pstVfmwChan
	movw	ip, #:lower16:249204	@ tmp341,
	movt	ip, #:upper16:249204	@ tmp341,
	ldr	lr, [fp, #-76]	@, %sfp
	ldr	r3, [r5, ip]	@, <variable>.s32RefNum
	cmp	lr, r9	@, CurFsSize
	str	r3, [fp, #-64]	@, %sfp
	beq	.L689	@,
.L579:
	movw	r2, #:lower16:249200	@ tmp344,
	movw	r0, #:lower16:g_event_report	@ tmp345,
	movt	r2, #:upper16:249200	@ tmp344,
	movt	r0, #:upper16:g_event_report	@ tmp345,
	str	r9, [r5, r2]	@ CurFsSize, <variable>.s32CurFsSize
	ldr	ip, [r0, #0]	@ g_event_report.452, g_event_report
	cmp	ip, #0	@ g_event_report.452,
	beq	.L581	@,
	ldr	r5, [fp, #-64]	@, %sfp
	mov	r0, r4	@, eFlag
	str	r7, [fp, #-52]	@ Width, para
	mov	r1, #118	@,
	str	sl, [fp, #-48]	@ Height, para
	sub	r2, fp, #60	@,,
	str	r5, [fp, #-60]	@, para
	mov	r3, #16	@,
	str	r9, [fp, #-56]	@ CurFsSize, para
	blx	ip	@ g_event_report.452
.L581:
	ldr	r5, [r6, r4, asl #2]	@ tmp349, s_pstVfmwChan
	movw	r1, #:lower16:249224	@ tmp350,
	movt	r1, #:upper16:249224	@ tmp350,
	mov	r2, r9	@, CurFsSize
	ldr	r3, [fp, #-64]	@, %sfp
	mov	r0, #31	@,
	ldr	lr, [r5, r1]	@ <variable>.s32RefNumChanged, <variable>.s32RefNumChanged
	movw	r1, #:lower16:.LC50	@,
	movt	r1, #:upper16:.LC50	@,
	str	lr, [sp, #0]	@ <variable>.s32RefNumChanged,
	bl	dprint_vfmw	@
	ldr	r5, [r6, r4, asl #2]	@ temp.1816, s_pstVfmwChan
	bl	OSAL_GetTimeInMs	@
	movw	ip, #:lower16:251460	@ tmp353,
	movt	ip, #:upper16:251460	@ tmp353,
	movw	r2, #:lower16:249192	@ tmp356,
	movt	r2, #:upper16:249192	@ tmp356,
	mov	r3, #2	@ ret,
	str	r0, [r5, ip]	@, <variable>.stDynamicFSTimestamp.u32StartTime
	mov	ip, #1	@ tmp357,
	ldr	r1, [r6, r4, asl #2]	@ tmp355, s_pstVfmwChan
	str	ip, [r1, r2]	@ tmp357, <variable>.FspInst.eFspPartitionState
	b	.L578	@
.L689:
	movw	ip, #:lower16:249224	@ tmp342,
	movt	ip, #:upper16:249224	@ tmp342,
	ldr	r3, [r5, ip]	@ <variable>.s32RefNumChanged, <variable>.s32RefNumChanged
	cmp	r3, #1	@ <variable>.s32RefNumChanged,
	beq	.L579	@,
	cmp	r8, #0	@ pVdmMemArrange,
	beq	.L690	@,
	ldr	r3, [fp, #-64]	@, %sfp
	ldr	r7, [r5, r1]	@, <variable>.stMemArrangeInfo.PmvSlotLen
	cmp	r3, #0	@,
	ldr	sl, [r5, r0]	@ ImgSlotLen, <variable>.stMemArrangeInfo.ImgSlotLen
	movne	r3, r5	@ prephitmp.1869, prephitmp.1769
	str	r7, [fp, #-64]	@, %sfp
	bne	.L584	@,
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	str	r2, [fp, #-88]	@,
	bl	dprint_vfmw	@
	ldr	r0, [fp, #-88]	@,
	ldr	r3, [r0, r4, asl #2]	@ prephitmp.1869, s_pstVfmwChan
.L584:
	movw	r7, #:lower16:249208	@ tmp366,
	movt	r7, #:upper16:249208	@ tmp366,
	ldr	r2, [r3, r7]	@ prephitmp.1771, <variable>.s32NeededFrameNum
	cmp	r2, #30	@ prephitmp.1771,
	ble	.L585	@,
	mov	r0, #31	@,
	movw	r1, #:lower16:.LC53	@,
	movt	r1, #:upper16:.LC53	@,
	bl	dprint_vfmw	@
	ldr	ip, [r6, r4, asl #2]	@ tmp369, s_pstVfmwChan
	mov	r2, #30	@ tmp371,
	str	r2, [ip, r7]	@ tmp371, <variable>.s32NeededFrameNum
	ldr	r3, [r6, r4, asl #2]	@ tmp373, s_pstVfmwChan
	ldr	r2, [r3, r7]	@ prephitmp.1771, <variable>.s32NeededFrameNum
.L585:
	movw	lr, #:lower16:251060	@ tmp375,
	cmp	r2, #0	@ prephitmp.1771,
	movt	lr, #:upper16:251060	@ tmp375,
	str	r2, [r5, lr]	@ prephitmp.1771, <variable>.stMemArrangeInfo.stMemArrange.ValidFrameNum
	ble	.L586	@,
	ldr	r0, [r6, r4, asl #2]	@ temp.1871, s_pstVfmwChan
	movw	r7, #:lower16:249240	@ tmp377,
	movt	r7, #:upper16:249240	@ tmp377,
	movw	r1, #:lower16:s_pstVfmwChan	@ tmp376,
	movt	r1, #:upper16:s_pstVfmwChan	@ tmp376,
	ldr	ip, [r0, r7]	@ s32PhyAddr, <variable>.stFrameBuffer.PhyAddr
	cmp	ip, #0	@ s32PhyAddr,
	beq	.L587	@,
	add	r3, ip, #1020	@ tmp378, s32PhyAddr,
	movw	r7, #:lower16:250520	@ tmp382,
	add	lr, r3, #3	@ tmp378, tmp378,
	movt	r7, #:upper16:250520	@ tmp382,
	bic	r0, lr, #1020	@ tmp380, tmp378,
	movw	lr, #:lower16:250776	@ tmp384,
	bic	r3, r0, #3	@ tmp380, tmp380,
	movt	lr, #:upper16:250776	@ tmp384,
	rsb	r9, ip, r3	@ s32Offset.1874, s32PhyAddr, tmp380
	movw	r0, #:lower16:251324	@ tmp386,
	add	r9, r9, sl	@, s32Offset.1874, ImgSlotLen
	str	r9, [fp, #-68]	@, %sfp
	add	r9, r9, #32	@,,
	str	r9, [fp, #-72]	@, %sfp
	str	r3, [r5, r7]	@ tmp380, <variable>.stMemArrangeInfo.stMemArrange.FrameAddr
	movt	r0, #:upper16:251324	@ tmp386,
	ldr	r7, [fp, #-68]	@, %sfp
	add	r9, r7, ip	@ tmp385,, s32PhyAddr
	str	r9, [r5, lr]	@ tmp385, <variable>.stMemArrangeInfo.stMemArrange.LineNumAddr
	ldr	r9, [fp, #-72]	@, %sfp
	add	r3, r9, ip	@ tmp387,, s32PhyAddr
	str	r3, [r5, r0]	@ tmp387, <variable>.stMemArrangeInfo.stMemArrange.PMVAddr
	ldr	r1, [r1, r4, asl #2]	@ D.55109, s_pstVfmwChan
	movw	r3, #:lower16:249200	@ tmp389,
	movt	r3, #:upper16:249200	@ tmp389,
	ldr	r0, [fp, #-64]	@, %sfp
	ldr	lr, [r1, r3]	@ prephitmp.1773, <variable>.s32CurFsSize
	add	r7, r9, r0	@ s32Offset.1854,,
	cmp	r7, lr	@ s32Offset.1854, prephitmp.1773
	movgt	r3, #0	@ i,
	bgt	.L589	@,
	tst	r2, #1	@ prephitmp.1771,
	add	ip, r5, #249856	@ ivtmp.1809, prephitmp.1769,
	add	r0, ip, #668	@ ivtmp.1809, ivtmp.1809,
	mov	r3, #0	@ i,
	bne	.L671	@,
	add	ip, r1, #248832	@ tmp662, D.55109,
	mov	r3, #1	@ i,
	add	lr, ip, #428	@ tmp662, tmp662,
	ldr	ip, [lr, #0]	@ s32PhyAddr, <variable>.stFrameBuffer.PhyAddr
	cmp	ip, #0	@ s32PhyAddr,
	beq	.L663	@,
	add	r7, ip, #1020	@ tmp663, s32PhyAddr,
	add	r9, r7, #3	@ tmp664, tmp663,
	bic	lr, r9, #1020	@ tmp665, tmp664,
	bic	r1, lr, #3	@ tmp665, tmp665,
	str	r1, [r0, #0]	@ tmp665, <variable>.stMemArrangeInfo.stMemArrange.FrameAddr
	rsb	r7, ip, r1	@ s32Offset, s32PhyAddr, tmp665
	add	r9, r7, sl	@ s32Offset.1850, s32Offset, ImgSlotLen
	add	r7, r9, #32	@ s32Offset.1852, s32Offset.1850,
	add	lr, r9, ip	@ tmp669, s32Offset.1850, s32PhyAddr
	add	r1, r7, ip	@ tmp671, s32Offset.1852, s32PhyAddr
	str	lr, [r0, #256]	@ tmp669, <variable>.stMemArrangeInfo.stMemArrange.LineNumAddr
	str	r1, [r0, #804]	@ tmp671, <variable>.stMemArrangeInfo.stMemArrange.PMVAddr
	add	r0, r0, #4	@ ivtmp.1809, ivtmp.1809,
	ldr	r9, [fp, #-64]	@, %sfp
	ldr	r1, [r6, r4, asl #2]	@ D.55109, s_pstVfmwChan
	add	r7, r7, r9	@ s32Offset.1854, s32Offset.1852,
	movw	r9, #:lower16:249200	@,
	movt	r9, #:upper16:249200	@,
	ldr	lr, [r1, r9]	@ prephitmp.1773, <variable>.s32CurFsSize
	cmp	r7, lr	@ s32Offset.1854, prephitmp.1773
	bgt	.L589	@,
.L671:
	str	r5, [fp, #-68]	@ prephitmp.1769, %sfp
	b	.L590	@
.L592:
	add	ip, r1, ip, asl #2	@, tmp396, D.55109, tmp394,
	add	lr, ip, #248832	@ tmp397, tmp396,
	add	ip, lr, #408	@ tmp397, tmp397,
	ldr	ip, [ip, #0]	@ s32PhyAddr, <variable>.stFrameBuffer.PhyAddr
	add	lr, ip, #1020	@ tmp399, s32PhyAddr,
	cmp	ip, #0	@ s32PhyAddr,
	add	lr, lr, #3	@ tmp399, tmp399,
	bic	lr, lr, #1020	@ tmp401, tmp399,
	beq	.L663	@,
	bic	r7, lr, #3	@ tmp401, tmp401,
	str	r7, [r0, #0]	@ tmp401, <variable>.stMemArrangeInfo.stMemArrange.FrameAddr
	rsb	r5, ip, r7	@ s32Offset, s32PhyAddr, tmp401
	add	r1, r5, sl	@ s32Offset.1850, s32Offset, ImgSlotLen
	add	r5, r1, #32	@ s32Offset.1852, s32Offset.1850,
	add	lr, r1, ip	@ tmp404, s32Offset.1850, s32PhyAddr
	add	r7, r5, ip	@ tmp405, s32Offset.1852, s32PhyAddr
	str	lr, [r0, #256]	@ tmp404, <variable>.stMemArrangeInfo.stMemArrange.LineNumAddr
	str	r7, [r0, #804]	@ tmp405, <variable>.stMemArrangeInfo.stMemArrange.PMVAddr
	add	r0, r9, #4	@ ivtmp.1809, tmp632,
	ldr	r1, [fp, #-64]	@, %sfp
	add	r7, r5, r1	@ s32Offset.1854, s32Offset.1852,
	ldr	r1, [r6, r4, asl #2]	@ D.55109, s_pstVfmwChan
	movw	r5, #:lower16:249200	@,
	movt	r5, #:upper16:249200	@,
	ldr	lr, [r1, r5]	@ prephitmp.1773, <variable>.s32CurFsSize
	cmp	r7, lr	@ s32Offset.1854, prephitmp.1773
	bgt	.L589	@,
	add	r3, r3, #1	@ i, i,
	add	lr, r3, r3, asl #2	@, tmp675, i, i,
	add	ip, r1, lr, asl #2	@, tmp677, D.55109, tmp675,
	add	lr, ip, #248832	@ tmp678, tmp677,
	add	ip, lr, #408	@ tmp678, tmp678,
	ldr	ip, [ip, #0]	@ s32PhyAddr, <variable>.stFrameBuffer.PhyAddr
	add	lr, ip, #1020	@ tmp680, s32PhyAddr,
	cmp	ip, #0	@ s32PhyAddr,
	add	lr, lr, #3	@ tmp680, tmp680,
	bic	lr, lr, #1020	@ tmp681, tmp680,
	beq	.L663	@,
	bic	r7, lr, #3	@ tmp681, tmp681,
	str	r7, [r9, #0]	@ tmp681, <variable>.stMemArrangeInfo.stMemArrange.FrameAddr
	rsb	r5, ip, r7	@ s32Offset, s32PhyAddr, tmp681
	add	r1, r5, sl	@ s32Offset.1850, s32Offset, ImgSlotLen
	add	r5, r1, #32	@ s32Offset.1852, s32Offset.1850,
	add	lr, r1, ip	@ tmp685, s32Offset.1850, s32PhyAddr
	add	r7, r5, ip	@ tmp687, s32Offset.1852, s32PhyAddr
	str	lr, [r9, #256]	@ tmp685, <variable>.stMemArrangeInfo.stMemArrange.LineNumAddr
	str	r7, [r9, #804]	@ tmp687, <variable>.stMemArrangeInfo.stMemArrange.PMVAddr
	ldr	r1, [fp, #-64]	@, %sfp
	add	r7, r5, r1	@ s32Offset.1854, s32Offset.1852,
	ldr	r1, [r6, r4, asl #2]	@ D.55109, s_pstVfmwChan
	movw	r5, #:lower16:249200	@,
	movt	r5, #:upper16:249200	@,
	ldr	lr, [r1, r5]	@ prephitmp.1773, <variable>.s32CurFsSize
	cmp	r7, lr	@ s32Offset.1854, prephitmp.1773
	bgt	.L589	@,
.L590:
	add	r3, r3, #1	@ i, i,
	add	r9, r0, #4	@ tmp632, ivtmp.1809,
	cmp	r2, r3	@ prephitmp.1771, i
	add	ip, r3, r3, asl #2	@, tmp394, i, i,
	bgt	.L592	@,
	ldr	r5, [fp, #-68]	@ prephitmp.1769, %sfp
.L593:
	movw	r0, #:lower16:249200	@ tmp594,
	movt	r0, #:upper16:249200	@ tmp594,
	movw	r3, #:lower16:250516	@ tmp593,
	movw	lr, #:lower16:251448	@ tmp597,
	ldr	ip, [r1, r0]	@ <variable>.s32CurFsSize, <variable>.s32CurFsSize
	movt	r3, #:upper16:250516	@ tmp593,
	movt	lr, #:upper16:251448	@ tmp597,
	add	r1, r5, #249856	@, prephitmp.1769,
	mov	r0, r8	@, pVdmMemArrange
	add	r1, r1, #656	@,,
	mul	ip, ip, r2	@ tmp596, <variable>.s32CurFsSize, prephitmp.1771
	str	r2, [r5, lr]	@ prephitmp.1771, <variable>.stMemArrangeInfo.stMemArrange.ValidPMVNum
	mov	r2, #940	@,
	str	ip, [r5, r3]	@ tmp596, <variable>.stMemArrangeInfo.stMemArrange.TotalMemUsed
	bl	memcpy	@
	mov	r3, #0	@ ret,
	b	.L578	@
.L678:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L691	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC13	@,
	movt	r3, #:upper16:.LC13	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L578	@
.L676:
	mov	r0, r5	@, MemAddr
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L691	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC55	@,
	movt	r3, #:upper16:.LC55	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L578	@
.L686:
	mla	r4, r7, r0, r4	@ Offset.1836, ImgSlotLen, D.52100, Offset
	b	.L633	@
.L663:
	movw	r2, #:lower16:249200	@ tmp398,
	movt	r2, #:upper16:249200	@ tmp398,
	ldr	lr, [r1, r2]	@ prephitmp.1773, <variable>.s32CurFsSize
.L589:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC54	@,
	ldr	r2, .L691+8	@,
	movt	r1, #:upper16:.LC54	@,
	stmia	sp, {r7, lr}	@ phole stm
	str	ip, [sp, #8]	@ s32PhyAddr,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L578	@
.L684:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L691	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC57	@,
	movt	r3, #:upper16:.LC57	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L578	@
.L688:
	mov	r9, #3	@ tmp281,
	add	r1, r0, #249856	@, D.51929,
	mul	ip, r9, sl	@ tmp280, tmp281, Height
	add	r0, r1, #656	@,,
	mov	r1, #948	@,
	str	r3, [fp, #-84]	@,
	movw	r9, #:lower16:250512	@ tmp287,
	movt	r9, #:upper16:250512	@ tmp287,
	mul	r2, r5, ip	@ tmp282, SlotWidth, tmp280
	mov	lr, r2, asr #1	@, tmp282,
	str	lr, [fp, #-64]	@, %sfp
	bl	__memzero	@
	ldr	r3, [fp, #-84]	@,
	ldr	ip, [r6, r4, asl #2]	@ tmp289, s_pstVfmwChan
	movw	r2, #:lower16:251444	@ tmp290,
	movt	r2, #:upper16:251444	@ tmp290,
	mov	r1, r5, asl #4	@ tmp297, SlotWidth,
	mov	r0, r3, asr #1	@ tmp293, PmvSlotLen,
	str	r0, [ip, r2]	@ tmp293, <variable>.stMemArrangeInfo.stMemArrange.HafPmvOffset
	ldr	r2, [r6, r4, asl #2]	@ tmp295, s_pstVfmwChan
	str	r1, [r2, r9]	@ tmp297, <variable>.stMemArrangeInfo.stMemArrange.VahbStride
.L573:
	mul	r5, sl, r5	@ tmp323, Height, SlotWidth
	ldr	ip, [r6, r4, asl #2]	@ tmp321, s_pstVfmwChan
	movw	r2, #:lower16:251048	@ tmp322,
	movt	r2, #:upper16:251048	@ tmp322,
	str	r5, [ip, r2]	@ tmp323, <variable>.stMemArrangeInfo.stMemArrange.ChromOffset
	b	.L576	@
.L687:
	ldr	r1, [fp, #-72]	@, %sfp
	mov	ip, #3	@ tmp267,
	add	r0, r0, #249856	@, D.51929,
	str	r2, [fp, #-88]	@,
	add	r0, r0, #656	@,,
	str	r3, [fp, #-84]	@,
	mul	lr, ip, r1	@ tmp266, tmp267,
	mov	r1, #948	@,
	movw	ip, #:lower16:250512	@ tmp269,
	movt	ip, #:upper16:250512	@ tmp269,
	str	ip, [fp, #-92]	@,
	mul	lr, r5, lr	@, SlotWidth, tmp266
	str	lr, [fp, #-64]	@, %sfp
	bl	__memzero	@
	ldr	r3, [fp, #-84]	@,
	movw	r0, #:lower16:251444	@ tmp272,
	ldr	lr, [r6, r4, asl #2]	@ tmp271, s_pstVfmwChan
	movt	r0, #:upper16:251444	@ tmp272,
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
	bne	.L574	@,
	b	.L573	@
.L566:
	mul	ip, r3, r1	@ tmp589, ImgHeightInMb, ImgWidthInPixAln
	add	r5, r7, #255	@ tmp591, Width,
	bic	r5, r5, #255	@ SlotWidth, tmp591,
	add	r2, ip, #127	@ tmp590, tmp589,
	bic	r3, r2, #127	@ PmvSlotLen, tmp590,
	b	.L632	@
.L677:
	mov	r0, r8	@, pVdmMemArrange
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L691	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC12	@,
	movt	r3, #:upper16:.LC12	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L578	@
.L681:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC56	@,
	movt	r1, #:upper16:.LC56	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L578	@
.L690:
	mov	r0, r8	@, pVdmMemArrange
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L691+8	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC51	@,
	movt	r3, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	mvn	r3, #0	@ ret,
	b	.L578	@
.L586:
	ldr	r1, [r6, r4, asl #2]	@ D.55109, s_pstVfmwChan
	b	.L593	@
.L587:
	movw	r2, #:lower16:249200	@ tmp408,
	movt	r2, #:upper16:249200	@ tmp408,
	mov	r3, ip	@ i, s32PhyAddr
	mov	r7, ip	@ s32Offset.1854, s32PhyAddr
	ldr	lr, [r0, r2]	@ prephitmp.1773, <variable>.s32CurFsSize
	b	.L589	@
.L692:
	.align	2
.L691:
	.word	.LANCHOR0+532
	.word	.LANCHOR0+468
	.word	.LANCHOR0+496
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
	beq	.L718	@,
	ldr	r5, [r2, #0]	@ MemBaseAddr, <variable>.MemBaseAddr
	ldr	r3, [r2, #8]	@ VdhId, <variable>.VdhId
	cmp	r5, #0	@ MemBaseAddr,
	ldr	r6, [r2, #4]	@ Size, <variable>.Size
	beq	.L719	@,
	movw	r2, #:lower16:4296703	@ tmp195,
	movt	r2, #:upper16:4296703	@ tmp195,
	cmp	r6, r2	@ Size, tmp195
	ble	.L720	@,
	cmp	r3, #1	@ VdhId,
	bhi	.L721	@,
	beq	.L722	@,
	movw	r4, #:lower16:g_HwMem	@ tmp280,
	movt	r4, #:upper16:g_HwMem	@ tmp280,
	movw	r1, #1208	@,
	add	sl, r5, #1020	@ tmp213, MemBaseAddr,
	mov	r0, r4	@, tmp280
	add	r9, r6, r5	@ tmp218, Size, MemBaseAddr
	bl	__memzero	@
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	movw	r1, #:lower16:.LC63	@,
	movt	r1, #:upper16:.LC63	@,
	mov	ip, r0	@ D.51632,
	mov	r2, r0	@, D.51632
	str	ip, [r4, #0]	@ D.51632, <variable>.pVdmRegVirAddr
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:-121241600	@,
	movt	r0, #:upper16:-121241600	@,
	bl	MEM_Phy2Vir	@
	movw	r1, #:lower16:.LC64	@,
	movt	r1, #:upper16:.LC64	@,
	mov	r7, r0	@ D.51636,
	mov	r2, r0	@, D.51636
	str	r7, [r4, #8]	@ D.51636, <variable>.pBpdRegVirAddr
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	add	r3, sl, #3	@ tmp213, tmp213,
	bic	r0, r3, #1020	@ D.51641, tmp213,
	movw	r7, #:lower16:268800	@ tmp281,
	movt	r7, #:upper16:268800	@ tmp281,
	bic	r0, r0, #3	@ D.51641, D.51641,
	mov	r2, r4	@ ivtmp.1915, tmp280
	mov	r3, #0	@ ivtmp.1912,
	rsb	r8, r0, r9	@ tmp219, D.51641, tmp218
	mov	r1, #1024	@ tmp221,
	str	r8, [r4, #20]	@ tmp219, <variable>.HALMemSize
	str	r1, [r4, #24]	@ tmp221, <variable>.VahbStride
	str	r0, [r4, #16]	@ D.51641, <variable>.HALMemBaseAddr
.L701:
	add	r9, r3, r0	@ tmp223, ivtmp.1912, D.51641
	add	r8, r3, #1280	@ tmp282, ivtmp.1912,
	add	r3, r3, #2560	@ ivtmp.1912, ivtmp.1912,
	add	r1, r2, #4	@ tmp283, ivtmp.1915,
	cmp	r3, r7	@ ivtmp.1912, tmp281
	str	r9, [r2, #32]	@ tmp223, <variable>.MsgSlotAddr
	add	lr, r8, r0	@ tmp286, tmp282, D.51641
	add	r2, r1, #4	@ ivtmp.1915, tmp283,
	str	lr, [r1, #32]	@ tmp286, <variable>.MsgSlotAddr
	bne	.L701	@,
	add	r0, r0, r3	@ PhyAddr.1918, D.51641, ivtmp.1912
	movw	r3, #:lower16:1081343	@ D.51648,
	add	r7, r0, #5120	@ PhyAddr.1919, PhyAddr.1918,
	movt	r3, #:upper16:1081343	@ D.51648,
	add	r8, r7, r3	@ D.51648, PhyAddr.1919, D.51648
	mov	r9, #210	@ tmp227,
	bic	sl, r8, #32512	@ PhyAddr.1920, D.51648,
	str	r7, [r4, #1100]	@ PhyAddr.1919, <variable>.mn_phy_addr
	bic	r1, sl, #255	@ PhyAddr.1920, PhyAddr.1920,
	str	r9, [r4, #1056]	@ tmp227, <variable>.ValidMsgSlotNum
	add	ip, r1, #191488	@ PhyAddr.1924, PhyAddr.1920,
	add	r3, r1, #2850816	@ PhyAddr_HEVC.1933, PhyAddr.1920,
	add	r2, ip, #158720	@ PhyAddr.1929, PhyAddr.1924,
	add	sl, r1, #78848	@ PhyAddr.1922, PhyAddr.1920,
	cmp	r2, r3	@ PhyAddr.1929, PhyAddr_HEVC.1933
	rsbge	r2, r5, r2	@,, D.51659, MemBaseAddr, PhyAddr.1929
	rsblt	r2, r5, r3	@,, D.51659, MemBaseAddr, PhyAddr_HEVC.1933
	add	r8, ip, #121856	@ PhyAddr.1927, PhyAddr.1924,
	cmp	r6, r2	@ Size, D.51659
	add	r7, r1, #589824	@ PhyAddr_HEVC, PhyAddr.1920,
	add	r5, r1, #1212416	@ PhyAddr_HEVC.1931, PhyAddr.1920,
	add	lr, r1, #1802240	@ PhyAddr_HEVC.1932, PhyAddr.1920,
	add	r9, r1, #33792	@ PhyAddr.1921, PhyAddr.1920,
	str	r1, [r4, #1136]	@ PhyAddr.1920, <variable>.SedTopAddr
	str	ip, [r4, #1156]	@ PhyAddr.1924, <variable>.PpfdBufAddr
	str	r1, [r4, #1084]	@ PhyAddr.1920, <variable>.sed_top_phy_addr
	str	r1, [r4, #1088]	@ PhyAddr.1920, <variable>.pmv_top_phy_addr
	str	r1, [r4, #1092]	@ PhyAddr.1920, <variable>.pmv_left_phy_addr
	str	r9, [r4, #1140]	@ PhyAddr.1921, <variable>.PmvTopAddr
	add	r9, r1, #123904	@ PhyAddr.1923, PhyAddr.1920,
	str	r0, [r4, #1080]	@ PhyAddr.1918, <variable>.H264MnAddr
	str	r9, [r4, #1152]	@ PhyAddr.1923, <variable>.DblkTopAddr
	movw	r9, #799	@ tmp239,
	str	sl, [r4, #1148]	@ PhyAddr.1922, <variable>.ItransTopAddr
	str	r9, [r4, #1160]	@ tmp239, <variable>.PpfdBufLen
	add	r9, ip, #102400	@ PhyAddr.1925, PhyAddr.1924,
	str	r8, [r4, #1180]	@ PhyAddr.1927, <variable>.Vp8TabAddr
	str	r9, [r4, #1168]	@ PhyAddr.1925, <variable>.IntensityConvTabAddr
	add	r9, ip, #105472	@ PhyAddr.1926, PhyAddr.1924,
	str	r7, [r4, #1104]	@ PhyAddr_HEVC, <variable>.tile_segment_info_phy_addr
	add	ip, ip, #154624	@ PhyAddr.1928, PhyAddr.1924,
	str	r5, [r4, #1116]	@ PhyAddr_HEVC.1931, <variable>.sao_left_phy_addr
	str	ip, [r4, #1176]	@ PhyAddr.1928, <variable>.Vp6TabAddr
	add	ip, r1, #622592	@ PhyAddr_HEVC.1930, PhyAddr.1920,
	str	lr, [r4, #1124]	@ PhyAddr_HEVC.1932, <variable>.upmsgslot_phy_addr
	mov	r1, #0	@ tmp257,
	str	r9, [r4, #1172]	@ PhyAddr.1926, <variable>.BitplaneInfoAddr
	str	ip, [r4, #1108]	@ PhyAddr_HEVC.1930, <variable>.dblk_left_phy_addr
	str	sl, [r4, #1144]	@ PhyAddr.1922, <variable>.RcnTopAddr
	str	r8, [r4, #1184]	@ PhyAddr.1927, <variable>.DnrMbInfoAddr
	str	r7, [r4, #1096]	@ PhyAddr_HEVC, <variable>.rcn_top_phy_addr
	str	r5, [r4, #1112]	@ PhyAddr_HEVC.1931, <variable>.dblk_top_phy_addr
	str	lr, [r4, #1120]	@ PhyAddr_HEVC.1932, <variable>.sao_top_phy_addr
	str	r3, [r4, #1128]	@ PhyAddr_HEVC.1933, <variable>.ppfd_phy_addr
	str	r1, [r4, #1132]	@ tmp257, <variable>.ppfd_buf_len
	blt	.L702	@,
	bl	H264HAL_V300R001_InitHal	@
	subs	r5, r0, #0	@ D.51663,
	ldr	r0, [r4, #1100]	@, <variable>.mn_phy_addr
	mvnne	r5, #0	@, Ret,
	bl	HEVCHAL_V300R001_InitHal	@
	cmp	r0, #0	@,
	ldr	r0, [r4, #1064]	@, <variable>.MPEG2TabAddr
	mvnne	r5, #0	@, Ret,
	bl	MP2HAL_V300R001_InitHal	@
	cmp	r0, #0	@,
	ldr	r0, [r4, #1068]	@, <variable>.MPEG4TabAddr
	mvnne	r5, #0	@, Ret,
	bl	MP4HAL_V300R001_InitHal	@
	cmp	r0, #0	@,
	ldr	r0, [r4, #1072]	@, <variable>.AVSTabAddr
	mvnne	r5, #0	@, Ret,
	bl	AVSHAL_V300R001_InitHal	@
	cmp	r0, #0	@,
	mvnne	r5, #0	@, Ret,
	bl	RV8HAL_V300R001_InitHal	@
	cmp	r0, #0	@,
	mvnne	r5, #0	@, Ret,
	bl	RV9HAL_V300R001_InitHal	@
	cmp	r0, #0	@,
	ldr	r0, [r4, #1076]	@, <variable>.VC1TabAddr
	mvnne	r5, #0	@, Ret,
	bl	VC1HAL_V300R001_InitHal	@
	cmp	r0, #0	@,
	ldr	r0, [r4, #1176]	@, <variable>.Vp6TabAddr
	mvnne	r5, #0	@, Ret,
	bl	VP6HAL_V300R001_InitHal	@
	cmp	r0, #0	@,
	ldr	r0, [r4, #1180]	@, <variable>.Vp8TabAddr
	mvnne	r5, #0	@, Ret,
	bl	VP8HAL_V300R001_InitHal	@
	cmp	r0, #0	@,
	ldr	r0, [r4, #1080]	@, <variable>.H264MnAddr
	moveq	r4, r5	@, Ret, Ret
	mvnne	r4, #0	@, Ret,
	bl	H264HAL_V300R001_InitHal	@
	cmp	r0, #0	@,
	moveq	r0, r4	@, Ret, Ret
	mvnne	r0, #0	@, Ret,
.L695:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L722:
	mov	ip, #0	@ tmp205,
	movw	r1, #:lower16:.LC15	@,
	mov	r0, ip	@, tmp205
	movt	r1, #:upper16:.LC15	@,
	ldr	r2, .L723	@,
	str	ip, [sp, #0]	@ tmp205,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	b	.L695	@
.L721:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC62	@,
	movt	r1, #:upper16:.LC62	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	b	.L695	@
.L702:
	mov	r0, r1	@, tmp257
	mov	r3, r6	@, Size
	movw	r1, #:lower16:.LC65	@,
	movt	r1, #:upper16:.LC65	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	b	.L695	@
.L719:
	mov	r0, r5	@, MemBaseAddr
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L723	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC60	@,
	movt	r3, #:upper16:.LC60	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	b	.L695	@
.L720:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L723	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC61	@,
	movt	r3, #:upper16:.LC61	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	b	.L695	@
.L718:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L723	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC59	@,
	movt	r3, #:upper16:.LC59	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ Ret,
	b	.L695	@
.L724:
	.align	2
.L723:
	.word	.LANCHOR0+560
	.fnend
	.size	VDMHAL_V300R001_OpenHAL, .-VDMHAL_V300R001_OpenHAL
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.52626, %object
	.size	__func__.52626, 25
__func__.52626:
	.ascii	"VDMHAL_V300R001_IsVdmRun\000"
	.space	3
	.type	__func__.52607, %object
	.size	__func__.52607, 27
__func__.52607:
	.ascii	"VDMHAL_V300R001_IsVdmReady\000"
	.space	1
	.type	__func__.52146, %object
	.size	__func__.52146, 31
__func__.52146:
	.ascii	"VDMHAL_V300R001_ArrangeMem_BTL\000"
	.space	1
	.type	__func__.53454, %object
	.size	__func__.53454, 30
__func__.53454:
	.ascii	"VDMHAL_V300R001_StartHwDecode\000"
	.space	2
	.type	__func__.53341, %object
	.size	__func__.53341, 30
__func__.53341:
	.ascii	"VDMHAL_V300R001_StartHwRepair\000"
	.space	2
	.type	__func__.53076, %object
	.size	__func__.53076, 25
__func__.53076:
	.ascii	"VDMHAL_V300R001_CfgRpReg\000"
	.space	3
	.type	__func__.52885, %object
	.size	__func__.52885, 25
__func__.52885:
	.ascii	"VDMHAL_V300R001_CfgRpMsg\000"
	.space	3
	.type	__func__.53282, %object
	.size	__func__.53282, 30
__func__.53282:
	.ascii	"VDMHAL_V300R001_PrepareRepair\000"
	.space	2
	.type	__func__.52655, %object
	.size	__func__.52655, 27
__func__.52655:
	.ascii	"VDMHAL_V300R001_BackupInfo\000"
	.space	1
	.type	__func__.52508, %object
	.size	__func__.52508, 25
__func__.52508:
	.ascii	"VDMHAL_V300R001_CheckReg\000"
	.space	3
	.type	__func__.52468, %object
	.size	__func__.52468, 26
__func__.52468:
	.ascii	"VDMHAL_V300R001_EnableInt\000"
	.space	2
	.type	__func__.52436, %object
	.size	__func__.52436, 24
__func__.52436:
	.ascii	"VDMHAL_V300R001_MaskInt\000"
	.type	__func__.52374, %object
	.size	__func__.52374, 30
__func__.52374:
	.ascii	"VDMHAL_V300R001_ClearIntState\000"
	.space	2
	.type	__func__.52301, %object
	.size	__func__.52301, 25
__func__.52301:
	.ascii	"VDMHAL_V300R001_ResetVdm\000"
	.space	3
	.type	__func__.53161, %object
	.size	__func__.53161, 30
__func__.53161:
	.ascii	"VDMHAL_V300R001_MakeDecReport\000"
	.space	2
	.type	__func__.52550, %object
	.size	__func__.52550, 27
__func__.52550:
	.ascii	"VDMHAL_V300R001_PrepareDec\000"
	.space	1
	.type	__func__.51740, %object
	.size	__func__.51740, 27
__func__.51740:
	.ascii	"VDMHAL_V300R001_CalcFsSize\000"
	.space	1
	.type	__func__.51838, %object
	.size	__func__.51838, 34
__func__.51838:
	.ascii	"VDMHAL_V300R001_FillVdmMemElement\000"
	.space	2
	.type	__func__.51907, %object
	.size	__func__.51907, 27
__func__.51907:
	.ascii	"VDMHAL_V300R001_ArrangeMem\000"
	.space	1
	.type	__func__.51601, %object
	.size	__func__.51601, 24
__func__.51601:
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
