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
	.file	"vdm_hal_avs.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(vdm_hal_avs)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD
@ drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/.vdm_hal_avs.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal_avs.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal_avs.o
@ -O2 -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs
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
	.global	AVSHAL_V300R001_InitHal
	.type	AVSHAL_V300R001_InitHal, %function
AVSHAL_V300R001_InitHal:
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
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	AVSHAL_V300R001_InitHal, .-AVSHAL_V300R001_InitHal
	.align	2
	.global	AVSHAL_V300R001_WirteSlicMsg
	.type	AVSHAL_V300R001_WirteSlicMsg, %function
AVSHAL_V300R001_WirteSlicMsg:
	.fnstart
.LFB1530:
	@ args = 0, pretend = 0, frame = 56
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
	str	r2, [fp, #-64]	@ VdhId, %sfp
	ldr	r9, [fp, #-64]	@, %sfp
	movw	r5, #:lower16:g_HwMem	@ tmp230,
	movt	r5, #:upper16:g_HwMem	@ tmp230,
	movw	r2, #1208	@ tmp233,
	str	r1, [fp, #-60]	@ stream_base_addr, %sfp
	mla	r6, r2, r9, r5	@ tmp234, tmp233,, tmp230
	mov	r5, r0	@ pAvsDecParam, pAvsDecParam
	ldr	r0, [r6, #48]	@ D.39389, <variable>.MsgSlotAddr
	add	ip, r0, #320	@, D.39389,
	str	ip, [fp, #-68]	@, %sfp
	bl	MEM_Phy2Vir	@
	ldr	r3, [r5, #104]	@ <variable>.slice_start_mbn, <variable>.slice_start_mbn
	cmp	r3, #0	@ <variable>.slice_start_mbn,
	streq	r3, [fp, #-80]	@ <variable>.slice_start_mbn, %sfp
	add	r6, r0, #320	@ pMsgBase.566, D.39392,
	beq	.L5	@,
	ldr	r1, [r5, #88]	@ <variable>.stream_phy_addr, <variable>.stream_phy_addr
	ldr	r2, [fp, #-60]	@, %sfp
	add	ip, r1, #4	@ tmp237, <variable>.stream_phy_addr,
	rsb	r3, r2, ip	@ D.39404,, tmp237
	and	r9, r3, #15	@ tmp239, D.39404,
	bic	sl, r3, #15	@ bit_stream_addr_0, D.39404,
	mov	r3, #1	@,
	mov	lr, r9, asl #3	@ bit_offset_0.568, tmp239,
	mov	r9, #0	@ tmp242,
	cmp	lr, #7	@ bit_offset_0.568,
	addls	lr, lr, #120	@ bit_offset_0, bit_offset_0.568,
	subhi	lr, lr, #8	@ bit_offset_0, bit_offset_0.568,
	subls	sl, sl, #4	@ bit_stream_addr_0, bit_stream_addr_0,
	mov	r1, lr, asl #25	@ tmp241, bit_offset_0,
	bic	ip, sl, #-16777216	@ D32.569, bit_stream_addr_0,
	orr	r2, r1, #8	@ D32, tmp241,
	str	r2, [r0, #320]	@ D32,
	str	ip, [r6, #4]	@ D32.569,
	str	r9, [r6, #8]	@ tmp242,
	str	r3, [fp, #-80]	@, %sfp
	str	r9, [r6, #12]	@ tmp242,
	ldr	lr, [r5, #104]	@ <variable>.slice_start_mbn, <variable>.slice_start_mbn
	ldr	r9, [fp, #-68]	@, %sfp
	sub	sl, lr, #1	@ tmp244, <variable>.slice_start_mbn,
	add	r0, r9, #256	@ D32.573,,
	mov	r1, sl, asl #16	@ D32.572, tmp244,
	str	r1, [r6, #16]	@ D32.572,
	str	r0, [r6, #252]	@ D32.573,
.L5:
	movw	sl, #14424	@ tmp248,
	ldr	r0, [r5, sl]	@ <variable>.SlcNum, <variable>.SlcNum
	cmp	r0, #0	@ <variable>.SlcNum,
	ble	.L30	@,
	mov	r2, #0	@ k,
	movw	r7, #:lower16:s_RegPhyBaseAddr	@,
	movw	r4, #:lower16:s_RegPhyBaseAddr_1	@,
	movt	r7, #:upper16:s_RegPhyBaseAddr	@,
	movt	r4, #:upper16:s_RegPhyBaseAddr_1	@,
	str	r7, [fp, #-72]	@, %sfp
	str	r4, [fp, #-76]	@, %sfp
	mov	r7, r2	@ j, k
	mov	r4, r2	@ i, k
.L29:
	movw	lr, #511	@,
	cmp	r7, lr	@ j,
	bgt	.L9	@,
	sub	ip, r4, #1	@ tmp260, i,
	mov	r8, r4, asl #3	@ tmp444, i,
	rsb	r3, r4, r8	@ tmp256, i, tmp444
	rsb	lr, ip, ip, asl #3	@, tmp264, tmp260, tmp260,
	cmp	r4, #0	@ i,
	movle	ip, #0	@,
	movgt	ip, #1	@,
	add	r3, r5, r3, asl #2	@, tmp258, pAvsDecParam, tmp256,
	add	r0, r5, lr, asl #2	@, tmp266, pAvsDecParam, tmp264,
	ldr	r9, [r3, #104]	@ <variable>.slice_start_mbn, <variable>.slice_start_mbn
	ldr	r1, [r0, #104]	@ <variable>.slice_start_mbn, <variable>.slice_start_mbn
	cmp	r9, r1	@ <variable>.slice_start_mbn, <variable>.slice_start_mbn
	movhi	ip, #0	@,,
	cmp	ip, #0	@ tmp274,
	mov	r9, ip	@ tmp274,
	bne	.L10	@,
	ldr	r2, [r3, #88]	@ temp.575, <variable>.stream_phy_addr
	add	ip, r2, #3	@ tmp282, temp.575,
#APP
@ 182 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/asm/memory.h" 1
	@ __pv_stub
1:	sub	lr, ip, #-2130706432	@ t, tmp282,
	.pushsection .pv_table,"a"
	.long	1b
	.popsection

@ 0 "" 2
	ldr	r0, [lr, #0]	@ tmp284,* t
	bic	r1, r0, #-16777216	@ tmp283, tmp284,
	cmp	r1, #131072	@ tmp283,
	beq	.L45	@,
	ldr	ip, [fp, #-60]	@, %sfp
	add	lr, r2, #4	@ tmp320, temp.575,
	rsb	r3, ip, lr	@ temp.589,, tmp320
	and	r9, r3, #15	@ tmp321, temp.589,
	bic	r2, r3, #15	@ bit_stream_addr_0.565, temp.589,
	mov	r3, r9, asl #3	@ bit_offset_0.562, tmp321,
.L15:
	rsb	r0, r4, r8	@ tmp351, i, tmp444
	add	r1, r5, r0, asl #2	@, tmp353, pAvsDecParam, tmp351,
	ldr	r0, [r1, #92]	@ D.39500, <variable>.stream_phy_addr
	ldr	lr, [r1, #96]	@ <variable>.stream_lenInByte, <variable>.stream_lenInByte
	cmp	r0, #0	@ D.39500,
	mov	ip, lr, asl #3	@ bit_len_0, <variable>.stream_lenInByte,
	beq	.L18	@,
	ldr	r1, [r1, #100]	@ <variable>.stream_lenInByte, <variable>.stream_lenInByte
	cmp	r1, #0	@ <variable>.stream_lenInByte,
	ble	.L18	@,
	ldr	r9, [fp, #-60]	@, %sfp
	cmp	ip, #0	@ bit_len_0,
	mov	r1, r1, asl #3	@, <variable>.stream_lenInByte,
	str	r1, [fp, #-48]	@, %sfp
	rsb	lr, r9, r0	@ D.39505,, D.39500
	and	r9, lr, #15	@ tmp371, D.39505,
	bic	r0, lr, #15	@ bit_stream_addr_1, D.39505,
	mov	r9, r9, asl #3	@ bit_offset_1, tmp371,
	bne	.L19	@,
	mov	r1, #0	@ prephitmp.539,
	mov	r2, r0	@ bit_stream_addr_0.565, bit_stream_addr_1
	ldr	ip, [fp, #-48]	@ bit_len_0, %sfp
	mov	r3, r9	@ bit_offset_0.562, bit_offset_1
	str	r1, [fp, #-56]	@ prephitmp.539, %sfp
	b	.L20	@
.L18:
	mov	r1, #0	@ prephitmp.539,
	str	r1, [fp, #-56]	@ prephitmp.539, %sfp
.L20:
	cmp	r3, #7	@ bit_offset_0.562,
	add	r9, ip, #8	@, bit_len_0,
	mov	ip, r4, asl #5	@ tmp386, i,
	str	r9, [fp, #-96]	@, %sfp
	addls	r3, r3, #120	@, bit_offset_0.562,
	subhi	r3, r3, #8	@, bit_offset_0.562,
	str	r3, [fp, #-48]	@, %sfp
	add	r3, ip, #1	@, tmp386,
	str	r3, [fp, #-100]	@, %sfp
	mov	r9, r4, asl #8	@ D.39417, i,
	ldr	r3, [fp, #-96]	@, %sfp
	mov	r0, r4, asl #6	@ tmp383, i,
	add	ip, r9, #12	@, D.39417,
	str	ip, [fp, #-52]	@, %sfp
	bic	ip, r3, #-33554432	@ tmp382,,
	ldr	r3, [fp, #-48]	@, %sfp
	add	lr, r0, #1	@ tmp384, tmp383,
	subls	r2, r2, #4	@ bit_stream_addr_0.565, bit_stream_addr_0.565,
	bic	r2, r2, #-16777216	@ D32.598, bit_stream_addr_0.565,
	orr	ip, ip, r3, asl #25	@, D32.595, tmp382,,
	str	ip, [r6, r4, asl #8]	@ D32.595,* pMsgBase.566
	str	r2, [r6, lr, asl #2]	@ D32.598,* pMsgBase.566
	add	r2, r4, #1	@ k, i,
	ldr	ip, [fp, #-100]	@, %sfp
	ldr	r0, [fp, #-56]	@, %sfp
	str	r0, [r6, ip, asl #3]	@,* pMsgBase.566
	ldr	r3, [fp, #-52]	@, %sfp
	str	r1, [r6, r3]	@ prephitmp.539,
	ldr	ip, [r5, sl]	@ temp.590, <variable>.SlcNum
	cmp	ip, r2	@ temp.590, k
	ble	.L46	@,
	rsb	r3, r4, r8	@ tmp401, i, tmp444
	rsb	r0, r2, r2, asl #3	@, tmp408, k, k,
	mov	r3, r3, asl #2	@ tmp402, tmp401,
	add	r1, r5, r0, asl #2	@, tmp410, pAvsDecParam, tmp408,
	add	lr, r3, r5	@ tmp403, tmp402, pAvsDecParam
	ldr	r0, [r1, #104]	@ <variable>.slice_start_mbn, <variable>.slice_start_mbn
	ldr	r1, [lr, #104]	@ prephitmp.541, <variable>.slice_start_mbn
	cmp	r1, r0	@ prephitmp.541, <variable>.slice_start_mbn
	bcc	.L24	@,
	mvn	lr, r2	@ tmp454, k
	add	r0, lr, ip	@ tmp453, tmp454, temp.590
	tst	r0, #1	@ tmp453,
	add	lr, r3, #88	@ tmp417, tmp402,
	add	r3, r5, lr	@ ivtmp.560, pAvsDecParam, tmp417
	beq	.L42	@,
	ldr	r0, [r3, #72]	@ temp.605, <variable>.slice_start_mbn
	add	r2, r2, #1	@ k, k,
	add	r3, r3, #28	@ ivtmp.560, ivtmp.560,
	cmp	r1, r0	@ prephitmp.541, temp.605
	bcc	.L24	@,
.L42:
	mov	r8, r6	@ pMsgBase.566, pMsgBase.566
	b	.L25	@
.L26:
	ldr	r6, [r3, #72]	@ temp.605, <variable>.slice_start_mbn
	add	r3, r3, #56	@ ivtmp.560, ivtmp.560,
	cmp	r1, r6	@ prephitmp.541, temp.605
	bcc	.L43	@,
	ldr	r6, [r0, #72]	@ temp.605, <variable>.slice_start_mbn
	add	r2, r2, #1	@ k, k,
	cmp	r1, r6	@ prephitmp.541, temp.605
	bcc	.L43	@,
.L25:
	add	r2, r2, #1	@ k, k,
	add	r0, r3, #28	@ tmp456, ivtmp.560,
	cmp	ip, r2	@ temp.590, k
	bgt	.L26	@,
.L43:
	mov	r6, r8	@ pMsgBase.566, pMsgBase.566
.L24:
	cmp	ip, r2	@ temp.590, k
	beq	.L47	@,
	rsb	r0, r2, r2, asl #3	@, tmp424, k, k,
	ldr	lr, [fp, #-80]	@, %sfp
	ldr	ip, [fp, #-68]	@, %sfp
	add	r3, r2, lr	@ tmp429, k,
	add	lr, r5, r0, asl #2	@, tmp426, pAvsDecParam, tmp424,
	ldr	r0, [lr, #104]	@ <variable>.slice_start_mbn, <variable>.slice_start_mbn
	add	r3, ip, r3, asl #8	@, prephitmp.543,, tmp429,
	sub	r0, r0, #1	@ slice_end_mbn, <variable>.slice_start_mbn,
.L28:
	mov	lr, r4, asl #4	@ tmp436, i,
	add	r9, r9, #252	@ tmp439, D.39417,
	add	r4, lr, #1	@ tmp437, tmp436,
	add	r7, r7, #1	@ j, j,
	uxth	ip, r1	@ tmp434, prephitmp.541
	orr	r1, ip, r0, asl #16	@, D32.610, tmp434, slice_end_mbn,
	str	r1, [r6, r4, asl #4]	@ D32.610,* pMsgBase.566
	str	r3, [r6, r9]	@ prephitmp.543,
.L9:
	sub	r4, r2, #1	@ i, k,
.L10:
	ldr	r3, [r5, sl]	@ <variable>.SlcNum, <variable>.SlcNum
	add	r4, r4, #1	@ i, i,
	cmp	r3, r4	@ <variable>.SlcNum, i
	bgt	.L29	@,
.L30:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L45:
	ldr	r0, [fp, #-64]	@, %sfp
	add	r1, r2, #2	@ tmp285, temp.575,
#APP
@ 182 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/asm/memory.h" 1
	@ __pv_stub
1:	sub	r2, r1, #-2130706432	@ t, tmp285,
	.pushsection .pv_table,"a"
	.long	1b
	.popsection

@ 0 "" 2
	strb	r9, [r2, #0]	@ tmp274,* t
	ldr	ip, [r3, #88]	@ <variable>.stream_phy_addr, <variable>.stream_phy_addr
	add	lr, ip, #4	@ tmp295, <variable>.stream_phy_addr,
#APP
@ 182 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/asm/memory.h" 1
	@ __pv_stub
1:	sub	r1, lr, #-2130706432	@ t, tmp295,
	.pushsection .pv_table,"a"
	.long	1b
	.popsection

@ 0 "" 2
	mov	lr, #64	@,
	strb	lr, [r1, #0]	@,* t
	ldr	r2, [r3, #88]	@ <variable>.stream_phy_addr, <variable>.stream_phy_addr
	add	ip, r2, #5	@ tmp306, <variable>.stream_phy_addr,
#APP
@ 182 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC062/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/include/asm/memory.h" 1
	@ __pv_stub
1:	sub	r1, ip, #-2130706432	@ t, tmp306,
	.pushsection .pv_table,"a"
	.long	1b
	.popsection

@ 0 "" 2
	strb	lr, [r1, #0]	@,* t
	str	r3, [fp, #-84]	@,
	bl	VDMHAL_V300R001_ResetVdm	@
	ldr	r2, [fp, #-84]	@,
	ldr	r0, [fp, #-60]	@, %sfp
	ldr	r3, [fp, #-64]	@, %sfp
	ldr	ip, [r2, #88]	@ <variable>.stream_phy_addr, <variable>.stream_phy_addr
	cmp	r3, #0	@,
	add	r1, ip, #2	@ tmp317, <variable>.stream_phy_addr,
	rsb	r2, r0, r1	@ D.39485,, tmp317
	and	r3, r2, #15	@ tmp319, D.39485,
	bic	r2, r2, #15	@ bit_stream_addr_0.565, D.39485,
	mov	r3, r3, asl #3	@ bit_offset_0.562, tmp319,
	bne	.L48	@,
	ldr	r9, [fp, #-72]	@, %sfp
	mov	r1, #1	@,
	ldr	lr, [r9, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	movw	r9, #:lower16:s_RegPhyBaseAddr	@ tmp442,
	str	r2, [fp, #-88]	@,
	movt	r9, #:upper16:s_RegPhyBaseAddr	@ tmp442,
	add	r0, lr, #2032	@, s_RegPhyBaseAddr,
	str	r3, [fp, #-84]	@,
	bl	MEM_WritePhyWord	@
	ldr	ip, [fp, #-72]	@, %sfp
	mov	r1, #1	@,
	ldr	r3, [ip, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	add	r0, r3, #1792	@, s_RegPhyBaseAddr,
	add	r0, r0, #12	@,,
	bl	MEM_WritePhyWord	@
	ldr	r1, [fp, #-72]	@, %sfp
	ldr	r2, [r1, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldr	r1, [fp, #-64]	@, %sfp
	add	r0, r2, #2032	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	ldr	r2, [fp, #-88]	@,
	ldr	r3, [fp, #-84]	@,
.L16:
	ldr	ip, [r9, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	mov	r1, #0	@,
	str	r2, [fp, #-88]	@,
	add	r0, ip, #8	@, s_RegPhyBaseAddr,
	str	r3, [fp, #-84]	@,
	bl	MEM_WritePhyWord	@
	ldr	r2, [fp, #-88]	@,
	ldr	r3, [fp, #-84]	@,
	b	.L15	@
.L47:
	ldrh	lr, [r5, #50]	@ <variable>.PicHeightInMb, <variable>.PicHeightInMb
	mov	r3, #0	@ prephitmp.543,
	ldrh	ip, [r5, #48]	@ <variable>.PicWidthInMb, <variable>.PicWidthInMb
	mul	r0, ip, lr	@ tmp420, <variable>.PicWidthInMb, <variable>.PicHeightInMb
	sub	r0, r0, #1	@ slice_end_mbn, tmp420,
	b	.L28	@
.L19:
	ldr	lr, [fp, #-48]	@, %sfp
	bic	r1, lr, #-33554432	@,,
	str	r1, [fp, #-48]	@, %sfp
	bic	r1, r0, #-16777216	@ prephitmp.539, bit_stream_addr_1,
	ldr	r0, [fp, #-48]	@, %sfp
	orr	lr, r0, r9, asl #25	@,,, bit_offset_1,
	str	lr, [fp, #-56]	@, %sfp
	b	.L20	@
.L48:
	ldr	r0, [fp, #-64]	@, %sfp
	cmp	r0, #1	@,
	beq	.L49	@,
	ldr	r9, [fp, #-64]	@, %sfp
	cmp	r9, #0	@,
	movweq	r9, #:lower16:s_RegPhyBaseAddr	@ tmp442,
	movteq	r9, #:upper16:s_RegPhyBaseAddr	@ tmp442,
	beq	.L16	@,
	ldr	ip, [fp, #-64]	@, %sfp
	cmp	ip, #1	@,
	movweq	ip, #:lower16:s_RegPhyBaseAddr_1	@ tmp443,
	movteq	ip, #:upper16:s_RegPhyBaseAddr_1	@ tmp443,
	bne	.L15	@,
	ldr	r9, [ip, #0]	@ s_RegPhyBaseAddr_1, s_RegPhyBaseAddr_1
	mov	r1, #0	@,
	str	r2, [fp, #-88]	@,
	add	r0, r9, #8	@, s_RegPhyBaseAddr_1,
	str	r3, [fp, #-84]	@,
	bl	MEM_WritePhyWord	@
	ldr	r3, [fp, #-84]	@,
	ldr	r2, [fp, #-88]	@,
	b	.L15	@
.L49:
	ldr	r1, [fp, #-76]	@, %sfp
	movw	lr, #:lower16:s_RegPhyBaseAddr_1	@ tmp443,
	movt	lr, #:upper16:s_RegPhyBaseAddr_1	@ tmp443,
	ldr	r0, [r1, #0]	@ s_RegPhyBaseAddr_1, s_RegPhyBaseAddr_1
	ldr	r1, [fp, #-64]	@, %sfp
	add	r0, r0, #2032	@, s_RegPhyBaseAddr_1,
	str	lr, [fp, #-92]	@,
	str	r2, [fp, #-88]	@,
	str	r3, [fp, #-84]	@,
	bl	MEM_WritePhyWord	@
	ldr	ip, [fp, #-76]	@, %sfp
	ldr	r1, [fp, #-64]	@, %sfp
	ldr	r3, [ip, #0]	@ s_RegPhyBaseAddr_1, s_RegPhyBaseAddr_1
	add	r0, r3, #1792	@, s_RegPhyBaseAddr_1,
	add	r0, r0, #12	@,,
	bl	MEM_WritePhyWord	@
	ldr	r1, [fp, #-76]	@, %sfp
	ldr	r2, [r1, #0]	@ s_RegPhyBaseAddr_1, s_RegPhyBaseAddr_1
	mov	r1, r9	@, tmp274
	add	r0, r2, #2032	@, s_RegPhyBaseAddr_1,
	bl	MEM_WritePhyWord	@
	ldr	ip, [fp, #-92]	@,
	ldr	r2, [fp, #-88]	@,
	mov	r1, #0	@,
	ldr	r3, [fp, #-84]	@,
	ldr	r9, [ip, #0]	@ s_RegPhyBaseAddr_1, s_RegPhyBaseAddr_1
	str	r2, [fp, #-88]	@,
	add	r0, r9, #8	@, s_RegPhyBaseAddr_1,
	str	r3, [fp, #-84]	@,
	bl	MEM_WritePhyWord	@
	ldr	r3, [fp, #-84]	@,
	ldr	r2, [fp, #-88]	@,
	b	.L15	@
.L46:
	rsb	r1, r4, r8	@ tmp394, i, tmp444
	add	lr, r5, r1, asl #2	@, tmp396, pAvsDecParam, tmp394,
	ldr	r1, [lr, #104]	@ prephitmp.541, <variable>.slice_start_mbn
	b	.L24	@
	.fnend
	.size	AVSHAL_V300R001_WirteSlicMsg, .-AVSHAL_V300R001_WirteSlicMsg
	.align	2
	.global	AVSHAL_V300R001_StartDec
	.type	AVSHAL_V300R001_StartDec, %function
AVSHAL_V300R001_StartDec:
	.fnstart
.LFB1529:
	@ args = 0, pretend = 0, frame = 64
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
	ldrh	r3, [r0, #48]	@ <variable>.PicWidthInMb, <variable>.PicWidthInMb
	mov	r5, r0	@ pAvsDecParam, pAvsDecParam
	cmp	r3, #512	@ <variable>.PicWidthInMb,
	bhi	.L109	@,
	ldrh	r0, [r0, #50]	@ <variable>.PicHeightInMb, <variable>.PicHeightInMb
	cmp	r0, #512	@ <variable>.PicHeightInMb,
	bhi	.L109	@,
	cmp	r1, #1	@ VdhId,
	bls	.L98	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38938,
.L52:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L98:
	beq	.L117	@,
	movw	r6, #:lower16:g_HwMem	@ tmp759,
	movt	r6, #:upper16:g_HwMem	@ tmp759,
	ldr	r1, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	cmp	r1, #0	@ <variable>.pVdmRegVirAddr,
	beq	.L118	@,
.L57:
	movw	r2, #14424	@ tmp293,
	ldr	r0, [r5, r2]	@ D.38963, <variable>.SlcNum
	cmp	r0, #0	@ D.38963,
	ble	.L59	@,
	ldr	r3, [r5, #88]	@ temp.881, <variable>.stream_phy_addr
	sub	r4, r0, #1	@ tmp765, D.38963,
	and	r1, r4, #1	@ tmp767, tmp765,
	mvn	r4, #0	@ stream_base_addr,
	cmp	r3, #0	@ temp.881,
	beq	.L87	@,
	ldr	r2, [r5, #96]	@ <variable>.stream_lenInByte, <variable>.stream_lenInByte
	cmp	r2, #0	@ <variable>.stream_lenInByte,
	ble	.L87	@,
	bic	r3, r3, #15	@ tmp868, temp.881,
	cmp	r4, r3	@ stream_base_addr, tmp868
	movcs	r4, r3	@ stream_base_addr, tmp868
.L87:
	ldr	r3, [r5, #92]	@ D.38957, <variable>.stream_phy_addr
	cmp	r3, #0	@ D.38957,
	bne	.L119	@,
.L89:
	mov	r2, #1	@ i,
	cmp	r2, r0	@ i, D.38963
	add	r3, r5, #28	@ ivtmp.716, pAvsDecParam,
	beq	.L86	@,
	cmp	r1, #0	@ tmp767,
	beq	.L60	@,
	ldr	r1, [r3, #88]	@ temp.881, <variable>.stream_phy_addr
	cmp	r1, #0	@ temp.881,
	bne	.L100	@,
.L94:
	ldr	r1, [r3, #92]	@ D.38957, <variable>.stream_phy_addr
	cmp	r1, #0	@ D.38957,
	beq	.L96	@,
.L120:
	ldr	lr, [r3, #100]	@ tmp881, <variable>.stream_lenInByte
	cmp	lr, #0	@ tmp881,
	ble	.L96	@,
	bic	ip, r1, #15	@ tmp882, D.38957,
	cmp	r4, ip	@ stream_base_addr, tmp882
	movcs	r4, ip	@ stream_base_addr, tmp882
.L96:
	add	r2, r2, #1	@ i, tmp768,
	add	r3, r3, #28	@ ivtmp.716, tmp769,
	cmp	r2, r0	@ i, D.38963
	beq	.L86	@,
.L60:
	ldr	r1, [r3, #88]	@ temp.881, <variable>.stream_phy_addr
	cmp	r1, #0	@ temp.881,
	beq	.L63	@,
	ldr	lr, [r3, #96]	@ <variable>.stream_lenInByte, <variable>.stream_lenInByte
	cmp	lr, #0	@ <variable>.stream_lenInByte,
	ble	.L63	@,
	bic	r1, r1, #15	@ tmp298, temp.881,
	cmp	r4, r1	@ stream_base_addr, tmp298
	movcs	r4, r1	@ stream_base_addr, tmp298
.L63:
	ldr	r1, [r3, #92]	@ D.38957, <variable>.stream_phy_addr
	cmp	r1, #0	@ D.38957,
	beq	.L61	@,
	ldr	lr, [r3, #100]	@ tmp295, <variable>.stream_lenInByte
	cmp	lr, #0	@ tmp295,
	ble	.L61	@,
	bic	ip, r1, #15	@ tmp296, D.38957,
	cmp	r4, ip	@ stream_base_addr, tmp296
	movcs	r4, ip	@ stream_base_addr, tmp296
.L61:
	add	r3, r3, #28	@ tmp769, ivtmp.716,
	add	r2, r2, #1	@ tmp768, i,
	ldr	r1, [r3, #88]	@ temp.881, <variable>.stream_phy_addr
	cmp	r1, #0	@ temp.881,
	beq	.L94	@,
.L100:
	ldr	ip, [r3, #96]	@ <variable>.stream_lenInByte, <variable>.stream_lenInByte
	cmp	ip, #0	@ <variable>.stream_lenInByte,
	ble	.L94	@,
	bic	r1, r1, #15	@ tmp879, temp.881,
	cmp	r4, r1	@ stream_base_addr, tmp879
	movcs	r4, r1	@ stream_base_addr, tmp879
	ldr	r1, [r3, #92]	@ D.38957, <variable>.stream_phy_addr
	cmp	r1, #0	@ D.38957,
	bne	.L120	@,
	add	r2, r2, #1	@ i, tmp768,
	add	r3, r3, #28	@ ivtmp.716, tmp769,
	cmp	r2, r0	@ i, D.38963
	bne	.L60	@,
.L86:
	cmn	r4, #1	@ stream_base_addr,
	beq	.L59	@,
	ldrh	ip, [r5, #50]	@ <variable>.PicHeightInMb, <variable>.PicHeightInMb
	mov	r7, #0	@ tmp300,
	ldrh	lr, [r5, #48]	@ <variable>.PicWidthInMb, <variable>.PicWidthInMb
	mov	r3, r7	@ tmp305, tmp300
	ldr	sl, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC6	@,
	movt	r1, #:upper16:.LC6	@,
	mul	r8, lr, ip	@ tmp303, <variable>.PicWidthInMb, <variable>.PicHeightInMb
	sub	r9, r8, #1	@ tmp304, tmp303,
	bfi	r3, r9, #0, #20	@ tmp305, tmp304,,
	mov	r9, #805306374	@ tmp325,
	orr	r2, r3, #1090519040	@ tmp314, tmp305,
	orr	lr, r2, #4194304	@ tmp314, tmp314,
	bfi	lr, r7, #25, #1	@ tmp314, tmp300,,
	str	lr, [fp, #-48]	@ tmp314,
	str	lr, [sl, #8]	@ tmp314,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	movw	ip, #14844	@ tmp322,
	ldr	r8, [r5, ip]	@ <variable>.VahbStride, <variable>.VahbStride
	movw	r0, #14864	@ tmp334,
	mov	r2, #1	@ tmp330,
	ldr	ip, [r5, r0]	@ <variable>.Compress_en, <variable>.Compress_en
	mov	r0, #3	@,
	mov	r1, r8, lsr #6	@ tmp323, <variable>.VahbStride,
	ldr	r8, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	bfi	r9, r1, #4, #10	@ tmp325, tmp323,,
	movw	r1, #:lower16:.LC7	@,
	orr	r3, r9, #16384	@ tmp328, tmp325,
	movt	r1, #:upper16:.LC7	@,
	bic	sl, r3, #32768	@ tmp329, tmp328,
	bfi	sl, r2, #16, #12	@ tmp329, tmp330,,
	bic	r9, sl, #805306368	@ tmp331, tmp329,
	orr	lr, r9, #536870912	@ tmp336, tmp331,
	bfi	lr, ip, #30, #1	@ tmp336, <variable>.Compress_en,,
	bfi	lr, r7, #31, #1	@ tmp337, tmp300,,
	str	lr, [fp, #-48]	@ tmp337,
	str	lr, [r8, #12]	@ tmp337,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	sl, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	ldr	r2, [r6, #48]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC8	@,
	movt	r1, #:upper16:.LC8	@,
	bic	r3, r2, #15	@ tmp346, <variable>.MsgSlotAddr,
	str	r3, [fp, #-48]	@ tmp346, <variable>.av_msg_addr
	str	r3, [sl, #16]	@ tmp346,
	movw	sl, #:lower16:s_RegPhyBaseAddr	@ tmp370,
	ldr	r2, [fp, #-48]	@, D32
	movt	sl, #:upper16:s_RegPhyBaseAddr	@ tmp370,
	bl	dprint_vfmw	@
	ldr	ip, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	ldr	r9, [r6, #32]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC9	@,
	movt	r1, #:upper16:.LC9	@,
	bic	r8, r9, #15	@ tmp355, <variable>.MsgSlotAddr,
	str	r8, [fp, #-48]	@ tmp355, <variable>.va_msg_addr
	str	r8, [ip, #20]	@ tmp355,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r4, [fp, #-48]	@ stream_base_addr, <variable>.stream_base_addr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC10	@,
	movt	r1, #:upper16:.LC10	@,
	str	r4, [r2, #24]	@ stream_base_addr,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldrh	r3, [r5, #48]	@ <variable>.PicWidthInMb, <variable>.PicWidthInMb
	movw	r0, #:lower16:-121389052	@,
	movt	r0, #:upper16:-121389052	@,
	cmp	r3, #120	@ <variable>.PicWidthInMb,
	strhi	r7, [fp, #-48]	@ tmp300, D32
	movls	r3, #65536	@ tmp368,
	strls	r3, [fp, #-48]	@ tmp368, D32
	bl	MEM_ReadPhyWord	@
	ldr	r8, [sl, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldr	r9, [fp, #-48]	@ D32, D32
	orr	r1, r0, r9	@ tmp373,, D32
	add	r0, r8, #4	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	ldr	r0, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movw	r1, #:lower16:3148803	@ tmp375,
	movt	r1, #:upper16:3148803	@ tmp375,
	str	r1, [fp, #-48]	@ tmp375, D32
	str	r1, [r0, #60]	@ tmp375,
	mov	r0, #3	@,
	ldr	ip, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movw	r1, #:lower16:.LC11	@,
	ldr	r2, [fp, #-48]	@ D32.748, D32
	movt	r1, #:upper16:.LC11	@,
	str	r2, [ip, #64]	@ D32.748,
	ldr	r7, [fp, #-48]	@ D32.751, D32
	ldr	r3, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r7, [r3, #68]	@ D32.751,
	ldr	r9, [fp, #-48]	@ D32.754, D32
	ldr	sl, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r9, [sl, #72]	@ D32.754,
	movw	r9, #14440	@ tmp393,
	ldr	r8, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	ldr	ip, [fp, #-48]	@ D32.757, D32
	str	ip, [r8, #76]	@ D32.757,
	ldr	r7, [fp, #-48]	@ D32.760, D32
	ldr	r2, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r7, [r2, #80]	@ D32.760,
	movw	r7, #14844	@ tmp402,
	ldr	r3, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	ldr	sl, [fp, #-48]	@ D32.763, D32
	str	sl, [r3, #84]	@ D32.763,
	ldr	r2, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	ldr	r8, [r5, r9]	@ <variable>.CurPicAddr, <variable>.CurPicAddr
	bic	ip, r8, #15	@ tmp395, <variable>.CurPicAddr,
	str	ip, [fp, #-48]	@ tmp395, <variable>.ystaddr_1d
	str	ip, [r2, #96]	@ tmp395,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r3, [r5, r7]	@ <variable>.VahbStride, <variable>.VahbStride
	ldr	sl, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r0, #3	@,
	ldrh	r7, [r5, #50]	@ height_in_mb, <variable>.PicHeightInMb
	movw	r1, #:lower16:.LC12	@,
	str	r3, [fp, #-48]	@ <variable>.VahbStride, <variable>.ystride_1d
	movt	r1, #:upper16:.LC12	@,
	str	r3, [sl, #100]	@ <variable>.VahbStride,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldrh	r9, [r5, #48]	@ <variable>.PicWidthInMb, <variable>.PicWidthInMb
	movw	r3, #2047	@ tmp411,
	mov	r2, r9, asl #4	@ D.39082, <variable>.PicWidthInMb,
	sub	r8, r2, #1	@ tmp410, D.39082,
	cmp	r8, r3	@ tmp410, tmp411
	bhi	.L121	@,
.L68:
	mov	r3, #16	@ level,
.L70:
	mov	r8, r7, asl #4	@ tmp421, height_in_mb,
	movw	ip, #14844	@ tmp428,
	add	r1, r8, #31	@ tmp422, tmp421,
	add	r0, r7, #1	@ tmp426, height_in_mb,
	ldr	sl, [r5, ip]	@ <variable>.VahbStride, <variable>.VahbStride
	mov	r9, r1, lsr #5	@ tmp423, tmp422,
	mov	r7, r0, lsr #1	@ tmp427, tmp426,
	ldr	r2, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r0, #3	@,
	mul	r8, r9, r3	@ D.39105, tmp423, level
	movw	r1, #:lower16:.LC13	@,
	mul	r3, sl, r7	@ tmp429, <variable>.VahbStride, tmp427
	movt	r1, #:upper16:.LC13	@,
	mov	r7, #0	@ tmp444,
	mvn	r9, #0	@ tmp458,
	movw	sl, #:lower16:g_HwMem	@ tmp433,
	movt	sl, #:upper16:g_HwMem	@ tmp433,
	add	r3, r3, r8, asl #4	@, tmp431, tmp429, D.39105,
	mov	lr, r3, asl #1	@ tmp432, tmp431,
	str	lr, [fp, #-48]	@ tmp432, <variable>.uvoffset_1d
	str	lr, [r2, #104]	@ tmp432,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	ip, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r2, r8, asl #5	@ D32.455, D.39105,
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC14	@,
	movt	r1, #:upper16:.LC14	@,
	str	r2, [ip, #108]	@ D32.455,
	ldr	r3, [r6, #1184]	@ D32.456, <variable>.DnrMbInfoAddr
	ldr	r8, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r3, [fp, #-48]	@ D32.456, D32
	str	r3, [r8, #144]	@ D32.456,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r7, [fp, #-48]	@ tmp444, D32
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC15	@,
	movt	r1, #:upper16:.LC15	@,
	str	r7, [r2, #148]	@ tmp444,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	ip, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r7, [fp, #-48]	@ tmp444, D32
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC16	@,
	movt	r1, #:upper16:.LC16	@,
	str	r7, [ip, #152]	@ tmp444,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r3, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r9, [r3, #32]	@ tmp458,
	ldr	r0, [r6, #48]	@, <variable>.MsgSlotAddr
	bl	MEM_Phy2Vir	@
	subs	r8, r0, #0	@ pMsgBase,
	beq	.L122	@,
	ldrh	r2, [r5, #48]	@ <variable>.PicWidthInMb, <variable>.PicWidthInMb
	mov	r9, r8	@ p32.801, pMsgBase
	ldrh	r3, [r5, #50]	@ <variable>.PicHeightInMb, <variable>.PicHeightInMb
	mov	r0, #4	@,
	ldr	lr, [fp, #-48]	@ tmp467,
	sub	ip, r2, #1	@ tmp466, <variable>.PicWidthInMb,
	sub	r1, r3, #1	@ tmp470, <variable>.PicHeightInMb,
	ldrb	r2, [r5, #31]	@ zero_extendqisi2	@ <variable>.ChromaFormat, <variable>.ChromaFormat
	bfi	lr, ip, #0, #9	@ tmp467, tmp466,,
	ldrb	ip, [r5, #30]	@ zero_extendqisi2	@ <variable>.SamplePrecision, <variable>.SamplePrecision
	bfi	lr, r1, #16, #9	@ tmp471, tmp470,,
	movw	r1, #:lower16:.LC18	@,
	bfi	lr, r2, #25, #2	@ tmp472, <variable>.ChromaFormat,,
	movt	r1, #:upper16:.LC18	@,
	bfi	lr, ip, #27, #2	@ tmp476, <variable>.SamplePrecision,,
	bic	r3, lr, #65024	@ tmp481, tmp476,
	bfi	r3, r7, #29, #3	@ tmp481, tmp444,,
	str	r3, [fp, #-48]	@ tmp481,
	str	r3, [r9], #4	@ tmp481,
	add	r2, r9, r0	@, p32.801,
	str	r2, [fp, #-100]	@, %sfp
	ldr	ip, [fp, #-100]	@, %sfp
	ldr	r2, [fp, #-48]	@, D32
	add	lr, ip, r0	@,,
	str	lr, [fp, #-96]	@, %sfp
	bl	dprint_vfmw	@
	ldrb	r3, [r5, #16]	@ zero_extendqisi2	@ <variable>.ProgrsvFrame, <variable>.ProgrsvFrame
	ldrb	r1, [r5, #8]	@ zero_extendqisi2	@ <variable>.PicStruct, <variable>.PicStruct
	mov	r0, #4	@,
	ldrb	r2, [r5, #7]	@ zero_extendqisi2	@ <variable>.PicCodingType, <variable>.PicCodingType
	and	r3, r3, #1	@ tmp489, <variable>.ProgrsvFrame,
	bfi	r3, r1, #1, #2	@ tmp489, <variable>.PicStruct,,
	ldrb	ip, [r5, #15]	@ zero_extendqisi2	@ <variable>.TopFieldFirst, <variable>.TopFieldFirst
	bfi	r3, r2, #3, #2	@ tmp493, <variable>.PicCodingType,,
	ldrb	r2, [r5, #13]	@ zero_extendqisi2	@, <variable>.FixQPFlag
	ldrb	lr, [r5, #14]	@ zero_extendqisi2	@ <variable>.RepeatFirstField, <variable>.RepeatFirstField
	bfi	r3, ip, #5, #1	@ tmp497, <variable>.TopFieldFirst,,
	movw	r1, #:lower16:.LC19	@,
	movt	r1, #:upper16:.LC19	@,
	str	r2, [fp, #-56]	@, %sfp
	bfi	r3, lr, #6, #1	@ tmp501, <variable>.RepeatFirstField,,
	ldr	r2, [fp, #-96]	@, %sfp
	ldrb	ip, [r5, #12]	@ zero_extendqisi2	@ <variable>.PicQuant, <variable>.PicQuant
	add	r2, r2, r0	@,,
	str	r2, [fp, #-92]	@, %sfp
	ldrb	lr, [r5, #11]	@ zero_extendqisi2	@, <variable>.SkipModeFlag
	str	lr, [fp, #-60]	@, %sfp
	add	lr, r2, r0	@,,
	ldr	r2, [fp, #-56]	@, %sfp
	str	lr, [fp, #-88]	@, %sfp
	ldrb	lr, [r5, #22]	@ zero_extendqisi2	@, <variable>.AdvPredModeDisable
	bfi	r3, r2, #7, #1	@ tmp505,,,
	ldr	r2, [fp, #-88]	@, %sfp
	bfi	r3, ip, #8, #6	@ tmp509, <variable>.PicQuant,,
	str	lr, [fp, #-56]	@, %sfp
	add	lr, r2, r0	@,,
	add	r2, lr, r0	@,,
	str	lr, [fp, #-84]	@, %sfp
	ldrb	ip, [r5, #10]	@ zero_extendqisi2	@ <variable>.PicRefFlag, <variable>.PicRefFlag
	str	r2, [fp, #-80]	@, %sfp
	ldr	lr, [fp, #-80]	@, %sfp
	ldr	r2, [fp, #-60]	@, %sfp
	add	lr, lr, r0	@,,
	bfi	r3, r2, #14, #1	@ tmp513,,,
	ldrb	r2, [r5, #9]	@ zero_extendqisi2	@ <variable>.NoFwdRefFlag, <variable>.NoFwdRefFlag
	str	lr, [fp, #-76]	@, %sfp
	ldr	lr, [fp, #-56]	@, %sfp
	bfi	r3, lr, #15, #1	@ tmp517,,,
	ldr	lr, [fp, #-76]	@, %sfp
	bfi	r3, ip, #16, #1	@ tmp521, <variable>.PicRefFlag,,
	add	lr, lr, r0	@,,
	bfi	r3, r2, #17, #1	@ tmp525, <variable>.NoFwdRefFlag,,
	add	ip, lr, r0	@,,
	str	lr, [fp, #-72]	@, %sfp
	add	lr, ip, r0	@,,
	bfi	r3, r7, #18, #14	@ tmp529, tmp444,,
	add	r2, lr, r0	@,,
	str	r3, [fp, #-48]	@ tmp529,
	str	ip, [fp, #-68]	@, %sfp
	add	ip, r2, r0	@,,
	str	lr, [fp, #-64]	@, %sfp
	add	lr, ip, r0	@,,
	str	r2, [fp, #-60]	@, %sfp
	str	r3, [r8, #4]	@ tmp529,
	ldr	r2, [fp, #-48]	@, D32
	str	ip, [fp, #-56]	@, %sfp
	str	lr, [fp, #-104]	@, %sfp
	bl	dprint_vfmw	@
	ldrb	r3, [r5, #20]	@ zero_extendqisi2	@ <variable>.LoopFiltDisable, <variable>.LoopFiltDisable
	mov	r0, #4	@,
	ldrb	r1, [r5, #19]	@ zero_extendqisi2	@ <variable>.LoopFiltParamFlag, <variable>.LoopFiltParamFlag
	ldrb	r2, [r5, #18]	@ zero_extendqisi2	@ <variable>.AlphaOffset, <variable>.AlphaOffset
	and	r3, r3, #1	@ tmp537, <variable>.LoopFiltDisable,
	ldrb	ip, [r5, #17]	@ zero_extendqisi2	@ <variable>.BetaOffset, <variable>.BetaOffset
	bfi	r3, r1, #1, #1	@ tmp537, <variable>.LoopFiltParamFlag,,
	bfi	r3, r2, #2, #5	@ tmp541, <variable>.AlphaOffset,,
	movw	r1, #:lower16:.LC20	@,
	bfi	r3, ip, #7, #5	@ tmp545, <variable>.BetaOffset,,
	str	r3, [fp, #-48]	@ tmp545,
	str	r3, [r9, #4]	@ tmp545,
	movt	r1, #:upper16:.LC20	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldrb	r3, [r5, #25]	@ zero_extendqisi2	@ <variable>.FwdTopFieldFirst0, <variable>.FwdTopFieldFirst0
	ldrb	r1, [r5, #26]	@ zero_extendqisi2	@ <variable>.FwdPicStruct0, <variable>.FwdPicStruct0
	mov	r0, #4	@,
	ldrb	ip, [r5, #27]	@ zero_extendqisi2	@ <variable>.FwdTopFieldFirst1, <variable>.FwdTopFieldFirst1
	and	r3, r3, #1	@ tmp556, <variable>.FwdTopFieldFirst0,
	ldrb	r2, [r5, #28]	@ zero_extendqisi2	@ <variable>.FwdPicStruct1, <variable>.FwdPicStruct1
	bfi	r3, r1, #1, #2	@ tmp556, <variable>.FwdPicStruct0,,
	ldrb	lr, [r5, #23]	@ zero_extendqisi2	@ <variable>.BwdTopFieldFirst, <variable>.BwdTopFieldFirst
	bfi	r3, ip, #3, #1	@ tmp560, <variable>.FwdTopFieldFirst1,,
	bfi	r3, r2, #4, #2	@ tmp564, <variable>.FwdPicStruct1,,
	ldrb	ip, [r5, #24]	@ zero_extendqisi2	@ <variable>.BwdPicStruct, <variable>.BwdPicStruct
	bfi	r3, lr, #6, #1	@ tmp568, <variable>.BwdTopFieldFirst,,
	ldr	lr, [fp, #-100]	@, %sfp
	bfi	r3, ip, #7, #2	@ tmp572, <variable>.BwdPicStruct,,
	movw	r1, #:lower16:.LC21	@,
	bfi	r3, r7, #9, #23	@ tmp576, tmp444,,
	str	r3, [fp, #-48]	@ tmp576,
	str	r3, [lr, #4]	@ tmp576,
	movt	r1, #:upper16:.LC21	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [fp, #-96]	@, %sfp
	movw	r1, #14428	@ tmp581,
	mov	r0, #4	@,
	ldr	r3, [r5, r1]	@ <variable>.BwdRefPicAddr, <variable>.BwdRefPicAddr
	movw	r1, #:lower16:.LC22	@,
	movt	r1, #:upper16:.LC22	@,
	bic	ip, r3, #15	@ tmp583, <variable>.BwdRefPicAddr,
	str	ip, [fp, #-48]	@ tmp583, <variable>.bwd_address
	str	ip, [r2, #4]	@ tmp583,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	ip, [fp, #-92]	@, %sfp
	movw	r0, #14432	@ tmp588,
	movw	r1, #:lower16:.LC23	@,
	ldr	r3, [r5, r0]	@ <variable>.FwdRefPic0Addr, <variable>.FwdRefPic0Addr
	movt	r1, #:upper16:.LC23	@,
	mov	r0, #4	@,
	bic	r2, r3, #15	@ tmp590, <variable>.FwdRefPic0Addr,
	str	r2, [fp, #-48]	@ tmp590, <variable>.fwd_address_0
	str	r2, [ip, #4]	@ tmp590,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	lr, [fp, #-88]	@, %sfp
	movw	r1, #14436	@ tmp595,
	mov	r0, #4	@,
	ldr	r3, [r5, r1]	@ <variable>.FwdRefPic1Addr, <variable>.FwdRefPic1Addr
	movw	r1, #:lower16:.LC24	@,
	movt	r1, #:upper16:.LC24	@,
	bic	ip, r3, #15	@ tmp597, <variable>.FwdRefPic1Addr,
	str	ip, [fp, #-48]	@ tmp597, <variable>.fwd_address_1
	str	ip, [lr, #4]	@ tmp597,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	ip, [fp, #-84]	@, %sfp
	movw	r0, #14452	@ tmp602,
	movw	r1, #:lower16:.LC25	@,
	ldr	r2, [r5, r0]	@ <variable>.rcn_address, <variable>.rcn_address
	movt	r1, #:upper16:.LC25	@,
	mov	r0, #4	@,
	bic	r3, r2, #15	@ tmp604, <variable>.rcn_address,
	str	r3, [fp, #-48]	@ tmp604, <variable>.rcn_address
	str	r3, [ip, #4]	@ tmp604,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldrb	r1, [r5, #29]	@ zero_extendqisi2	@ <variable>.ColPicType, <variable>.ColPicType
	ldr	ip, [fp, #-80]	@, %sfp
	mov	r0, #4	@,
	ldrb	r2, [r5, #21]	@ zero_extendqisi2	@ <variable>.ColPicStruct, <variable>.ColPicStruct
	and	r3, r1, #1	@ tmp612, <variable>.ColPicType,
	movw	r1, #:lower16:.LC26	@,
	movt	r1, #:upper16:.LC26	@,
	bfi	r3, r2, #24, #2	@ tmp612, <variable>.ColPicStruct,,
	str	r3, [fp, #-48]	@ tmp612,
	str	r3, [ip, #4]	@ tmp612,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	lr, [fp, #-76]	@, %sfp
	ldr	r2, [r5, #64]	@ <variable>.StreamPhyAddr, <variable>.StreamPhyAddr
	mov	r3, r7	@ tmp620, tmp444
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC27	@,
	bfi	r3, r2, #0, #24	@ tmp620, <variable>.StreamPhyAddr,,
	str	r3, [fp, #-48]	@ tmp620,
	str	r3, [lr, #4]	@ tmp620,
	movt	r1, #:upper16:.LC27	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r1, [r5, #80]	@ <variable>.StreamLength, <variable>.StreamLength
	ldr	r2, [fp, #-72]	@, %sfp
	mov	r0, #4	@,
	ldr	ip, [r5, #72]	@ <variable>.StreamBitOffset, <variable>.StreamBitOffset
	bic	r3, r1, #-16777216	@ tmp628, <variable>.StreamLength,
	movw	r1, #:lower16:.LC28	@,
	movt	r1, #:upper16:.LC28	@,
	bfi	r3, ip, #24, #7	@ tmp628, <variable>.StreamBitOffset,,
	str	r3, [fp, #-48]	@ tmp628,
	str	r3, [r2, #4]	@ tmp628,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [fp, #-68]	@, %sfp
	ldr	ip, [r5, #68]	@ <variable>.StreamPhyAddr, <variable>.StreamPhyAddr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC29	@,
	movt	r1, #:upper16:.LC29	@,
	bfi	r7, ip, #0, #24	@ tmp633, <variable>.StreamPhyAddr,,
	str	r7, [fp, #-48]	@ tmp633,
	str	r7, [r2, #4]	@ tmp633,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldrb	r3, [r5, #32]	@ zero_extendqisi2	@ <variable>.weighting_quant_flag, <variable>.weighting_quant_flag
	ldrb	r1, [r5, #33]	@ zero_extendqisi2	@ <variable>.chroma_quant_param_disable, <variable>.chroma_quant_param_disable
	mov	r0, #4	@,
	ldrb	ip, [r5, #35]	@ zero_extendqisi2	@ <variable>.chroma_quant_param_delta_v, <variable>.chroma_quant_param_delta_v
	and	r3, r3, #1	@ tmp642, <variable>.weighting_quant_flag,
	ldrb	r2, [r5, #34]	@ zero_extendqisi2	@ <variable>.chroma_quant_param_delta_u, <variable>.chroma_quant_param_delta_u
	bfi	r3, r1, #1, #1	@ tmp642, <variable>.chroma_quant_param_disable,,
	ldrb	lr, [r5, #36]	@ zero_extendqisi2	@ <variable>.aec_enable, <variable>.aec_enable
	bfi	r3, ip, #2, #6	@ tmp646, <variable>.chroma_quant_param_delta_v,,
	bfi	r3, r2, #8, #6	@ tmp650, <variable>.chroma_quant_param_delta_u,,
	ldrb	ip, [r5, #37]	@ zero_extendqisi2	@ <variable>.p_filed_enhanced_flag, <variable>.p_filed_enhanced_flag
	bfi	r3, lr, #14, #1	@ tmp654, <variable>.aec_enable,,
	ldrb	r2, [r5, #38]	@ zero_extendqisi2	@ <variable>.b_filed_enhanced_flag, <variable>.b_filed_enhanced_flag
	bfi	r3, ip, #15, #1	@ tmp658, <variable>.p_filed_enhanced_flag,,
	ldr	ip, [fp, #-64]	@, %sfp
	bfi	r3, r2, #16, #1	@ tmp662, <variable>.b_filed_enhanced_flag,,
	str	r3, [fp, #-48]	@ tmp662,
	movw	r1, #:lower16:.LC30	@,
	movt	r1, #:upper16:.LC30	@,
	str	r3, [ip, #4]	@ tmp662,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	lr, [fp, #-60]	@, %sfp
	ldr	r2, [sl, #1140]	@ <variable>.PmvTopAddr, <variable>.PmvTopAddr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC31	@,
	movt	r1, #:upper16:.LC31	@,
	bic	ip, r2, #15	@ tmp672, <variable>.PmvTopAddr,
	str	ip, [fp, #-48]	@ tmp672, <variable>.pmv_top_addr
	str	ip, [lr, #4]	@ tmp672,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	ip, [fp, #-56]	@, %sfp
	ldr	r3, [sl, #1144]	@ <variable>.RcnTopAddr, <variable>.RcnTopAddr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC32	@,
	movt	r1, #:upper16:.LC32	@,
	bic	r2, r3, #15	@ tmp679, <variable>.RcnTopAddr,
	str	r2, [fp, #-48]	@ tmp679, <variable>.topmb_intra_addr
	str	r2, [ip, #4]	@ tmp679,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r1, [fp, #-104]	@, %sfp
	movw	r0, #14448	@ tmp684,
	ldr	r3, [r5, r0]	@ <variable>.ColPmvAddr, <variable>.ColPmvAddr
	add	r2, r1, #4	@ p32.857,,
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC33	@,
	bic	r3, r3, #15	@ tmp686, <variable>.ColPmvAddr,
	str	r3, [fp, #-48]	@ tmp686, <variable>.colpic_mv_addr
	str	r3, [r2, #4]	@ tmp686,
	movt	r1, #:upper16:.LC33	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	add	r2, r5, #14400	@ ivtmp.707, pAvsDecParam,
	add	r0, r2, #60	@ ivtmp.707, ivtmp.707,
	add	r3, r8, #68	@ ivtmp.710, pMsgBase,
	add	lr, r8, #196	@ D.39817, pMsgBase,
.L73:
	mov	r1, r0	@ tmp763, ivtmp.707
	mov	r2, r3	@ tmp764, ivtmp.710
	ldr	ip, [r1], #4	@ D32.475, <variable>.PmvConfigTab
	str	ip, [fp, #-48]	@ D32.475, D32
	str	ip, [r2], #4	@ D32.475,
	ldr	ip, [r0, #4]	@ D32.475, <variable>.PmvConfigTab
	add	r0, r1, #4	@ ivtmp.707, tmp763,
	str	ip, [fp, #-48]	@ D32.475, D32
	str	ip, [r3, #4]	@ D32.475,
	add	r3, r2, #4	@ ivtmp.710, tmp764,
	cmp	r3, lr	@ ivtmp.710, D.39817
	bne	.L73	@,
	movw	r1, #14444	@ tmp692,
	mov	r0, #4	@,
	ldr	r3, [r5, r1]	@ <variable>.CurPmvAddr, <variable>.CurPmvAddr
	movw	r1, #:lower16:.LC34	@,
	movt	r1, #:upper16:.LC34	@,
	bic	lr, r3, #15	@ tmp694, <variable>.CurPmvAddr,
	str	lr, [fp, #-48]	@ tmp694, <variable>.pmv_colmb_addr
	str	lr, [r8, #196]	@ tmp694,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	ip, [r6, #1152]	@ <variable>.DblkTopAddr, <variable>.DblkTopAddr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC35	@,
	bic	r2, ip, #15	@ tmp701, <variable>.DblkTopAddr,
	str	r2, [fp, #-48]	@ tmp701, <variable>.dblk_top_addr
	str	r2, [r8, #200]	@ tmp701,
	movt	r1, #:upper16:.LC35	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r3, [r6, #1136]	@ <variable>.SedTopAddr, <variable>.SedTopAddr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC36	@,
	bic	ip, r3, #15	@ tmp708, <variable>.SedTopAddr,
	str	ip, [fp, #-48]	@ tmp708, <variable>.sed_top_addr
	str	ip, [r8, #204]	@ tmp708,
	movt	r1, #:upper16:.LC36	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r6, #48]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC37	@,
	add	r3, r2, #320	@ D32.479, <variable>.MsgSlotAddr,
	str	r3, [fp, #-48]	@ D32.479, D32
	str	r3, [r8, #252]	@ D32.479,
	movt	r1, #:upper16:.LC37	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldrb	r0, [r5, #32]	@ zero_extendqisi2	@ <variable>.weighting_quant_flag, <variable>.weighting_quant_flag
	cmp	r0, #1	@ <variable>.weighting_quant_flag,
	beq	.L123	@,
.L74:
	mov	r0, r5	@, pAvsDecParam
	mov	r1, r4	@, stream_base_addr
	mov	r2, #0	@,
	bl	AVSHAL_V300R001_WirteSlicMsg	@
	mov	r0, #0	@ D.38938,
	b	.L52	@
.L121:
	sub	r0, r2, #2048	@ tmp412, D.39082,
	sub	r1, r0, #1	@ tmp412, tmp412,
	cmp	r1, r3	@ tmp412, tmp411
	movls	r3, #32	@ level,
	bls	.L70	@,
	sub	r9, r2, #4096	@ tmp415, D.39082,
	sub	sl, r9, #1	@ tmp415, tmp415,
	cmp	sl, r3	@ tmp415, tmp411
	movls	r3, #48	@ level,
	bls	.L70	@,
	sub	r8, r2, #6144	@ tmp418, D.39082,
	sub	r2, r8, #1	@ tmp418, tmp418,
	cmp	r2, r3	@ tmp418, tmp411
	movls	r3, #64	@ level,
	bls	.L70	@,
	b	.L68	@
.L119:
	ldr	ip, [r5, #100]	@ tmp870, <variable>.stream_lenInByte
	cmp	ip, #0	@ tmp870,
	ble	.L89	@,
	bic	lr, r3, #15	@ tmp871, D.38957,
	cmp	r4, lr	@ stream_base_addr, tmp871
	movcs	r4, lr	@ stream_base_addr, tmp871
	b	.L89	@
.L123:
	add	r8, r8, #256	@ p32.791, pMsgBase,
	mov	r2, #0	@ ivtmp.683,
	mov	r3, r2	@ ivtmp.663, ivtmp.683
	mov	r1, r8	@ p32.791, p32.791
	b	.L77	@
.L124:
	add	r7, r5, r2	@ D.39786, pAvsDecParam, ivtmp.683
	add	r0, r7, #14592	@ tmp718, D.39786,
	add	ip, r7, #14528	@ tmp729, D.39786,
	ldrb	r6, [r0, #12]	@ zero_extendqisi2	@ tmp724, <variable>.cur_wq_matrix
	ldrb	r7, [r0, #20]	@ zero_extendqisi2	@ tmp719, <variable>.cur_wq_matrix
	ldrb	lr, [ip, #60]	@ zero_extendqisi2	@ tmp730, <variable>.cur_wq_matrix
	mov	r6, r6, asl #16	@ tmp726, tmp724,
	ldrb	ip, [r0, #4]	@ zero_extendqisi2	@ tmp735, <variable>.cur_wq_matrix
	orr	r0, r6, r7, asl #24	@, tmp727, tmp726, tmp719,
	orr	r0, r0, lr	@ tmp732, tmp727, tmp730
	orr	r0, r0, ip, asl #8	@, prephitmp.648, tmp732, tmp735,
	str	r0, [fp, #-48]	@ prephitmp.648, D32
.L76:
	add	r3, r3, #1	@ tmp760, ivtmp.663,
	str	r0, [r1, #0]	@ prephitmp.648,* p32.791
	cmp	r3, #16	@ tmp760,
	add	r2, r2, #16	@ tmp761, ivtmp.683,
	beq	.L74	@,
	tst	r3, #1	@ tmp760,
	add	r1, r1, #4	@ tmp762, p32.791,
	bne	.L81	@,
	add	lr, r5, r2	@ D.39786, pAvsDecParam, tmp761
	add	r0, lr, #14592	@ tmp804, D.39786,
	add	ip, lr, #14528	@ tmp814, D.39786,
	ldrb	r6, [r0, #12]	@ zero_extendqisi2	@ tmp811, <variable>.cur_wq_matrix
	ldrb	r7, [r0, #20]	@ zero_extendqisi2	@ tmp807, <variable>.cur_wq_matrix
	ldrb	lr, [ip, #60]	@ zero_extendqisi2	@ tmp817, <variable>.cur_wq_matrix
	mov	r6, r6, asl #16	@ tmp812, tmp811,
	ldrb	ip, [r0, #4]	@ zero_extendqisi2	@ tmp821, <variable>.cur_wq_matrix
	orr	r0, r6, r7, asl #24	@, tmp813, tmp812, tmp807,
	orr	r7, r0, lr	@ tmp818, tmp813, tmp817
	orr	r0, r7, ip, asl #8	@, prephitmp.648, tmp818, tmp821,
.L102:
	tst	r3, #1	@ tmp760,
	str	r0, [r1, #0]	@ prephitmp.648,
	add	r0, r2, #16	@ ivtmp.683, tmp761,
	bne	.L103	@,
	add	r6, r5, r0	@ D.39794, pAvsDecParam, ivtmp.683
	add	lr, r6, #14592	@ tmp828, D.39794,
	add	ip, r6, #14528	@ tmp837, D.39794,
	ldrb	r0, [lr, #0]	@ zero_extendqisi2	@ tmp834, <variable>.cur_wq_matrix
	ldrb	r7, [lr, #8]	@ zero_extendqisi2	@ tmp831, <variable>.cur_wq_matrix
	ldrb	lr, [ip, #56]	@ zero_extendqisi2	@ tmp844, <variable>.cur_wq_matrix
	mov	r6, r0, asl #16	@ tmp835, tmp834,
	ldrb	r0, [ip, #48]	@ zero_extendqisi2	@ tmp840, <variable>.cur_wq_matrix
	orr	ip, r6, r7, asl #24	@, tmp836, tmp835, tmp831,
	orr	r7, ip, r0	@ tmp841, tmp836, tmp840
	orr	r0, r7, lr, asl #8	@, prephitmp.648, tmp841, tmp844,
.L104:
	str	r0, [r1, #4]	@ prephitmp.648,
	add	r3, r3, #2	@ ivtmp.663, tmp760,
	add	r2, r2, #32	@ ivtmp.683, tmp761,
	add	r1, r1, #8	@ p32.791, tmp762,
.L77:
	tst	r3, #1	@ ivtmp.663,
	beq	.L124	@,
	add	r7, r5, r2	@ D.39794, pAvsDecParam, ivtmp.683
	add	lr, r7, #14592	@ tmp739, D.39794,
	add	ip, r7, #14528	@ tmp749, D.39794,
	ldrb	r6, [lr, #0]	@ zero_extendqisi2	@ tmp744, <variable>.cur_wq_matrix
	ldrb	r7, [lr, #8]	@ zero_extendqisi2	@ tmp740, <variable>.cur_wq_matrix
	ldrb	r0, [ip, #48]	@ zero_extendqisi2	@ tmp750, <variable>.cur_wq_matrix
	ldrb	lr, [ip, #56]	@ zero_extendqisi2	@ tmp755, <variable>.cur_wq_matrix
	mov	r6, r6, asl #16	@ tmp746, tmp744,
	orr	ip, r6, r7, asl #24	@, tmp747, tmp746, tmp740,
	orr	r0, ip, r0	@ tmp752, tmp747, tmp750
	orr	r0, r0, lr, asl #8	@, prephitmp.648, tmp752, tmp755,
	str	r0, [fp, #-48]	@ prephitmp.648, D32
	b	.L76	@
.L103:
	add	lr, r5, r0	@ D.39786, pAvsDecParam, ivtmp.683
	add	r0, lr, #14592	@ tmp848, D.39786,
	add	ip, lr, #14528	@ tmp858, D.39786,
	ldrb	r6, [r0, #12]	@ zero_extendqisi2	@ tmp855, <variable>.cur_wq_matrix
	ldrb	r7, [r0, #20]	@ zero_extendqisi2	@ tmp851, <variable>.cur_wq_matrix
	ldrb	lr, [ip, #60]	@ zero_extendqisi2	@ tmp861, <variable>.cur_wq_matrix
	mov	r6, r6, asl #16	@ tmp856, tmp855,
	ldrb	ip, [r0, #4]	@ zero_extendqisi2	@ tmp865, <variable>.cur_wq_matrix
	orr	r0, r6, r7, asl #24	@, tmp857, tmp856, tmp851,
	orr	r7, r0, lr	@ tmp862, tmp857, tmp861
	orr	r0, r7, ip, asl #8	@, prephitmp.648, tmp862, tmp865,
	b	.L104	@
.L81:
	add	r0, r5, r2	@ D.39794, pAvsDecParam, tmp761
	add	lr, r0, #14592	@ tmp784, D.39794,
	add	ip, r0, #14528	@ tmp793, D.39794,
	ldrb	r6, [lr, #0]	@ zero_extendqisi2	@ tmp790, <variable>.cur_wq_matrix
	ldrb	r7, [lr, #8]	@ zero_extendqisi2	@ tmp787, <variable>.cur_wq_matrix
	ldrb	r0, [ip, #48]	@ zero_extendqisi2	@ tmp796, <variable>.cur_wq_matrix
	ldrb	lr, [ip, #56]	@ zero_extendqisi2	@ tmp800, <variable>.cur_wq_matrix
	mov	r6, r6, asl #16	@ tmp791, tmp790,
	orr	ip, r6, r7, asl #24	@, tmp792, tmp791, tmp787,
	orr	r0, ip, r0	@ tmp797, tmp792, tmp796
	orr	r0, r0, lr, asl #8	@, prephitmp.648, tmp797, tmp800,
	b	.L102	@
.L109:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38938,
	b	.L52	@
.L117:
	mov	ip, #0	@ tmp288,
	mov	r3, r1	@, VdhId
	mov	r0, ip	@, tmp288
	movw	r1, #:lower16:.LC3	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	movt	r1, #:upper16:.LC3	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	str	ip, [sp, #0]	@ tmp288,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38938,
	b	.L52	@
.L118:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r3, r0, #0	@ D.38950,
	strne	r3, [r6, #0]	@ D.38950, <variable>.pVdmRegVirAddr
	bne	.L57	@
.L58:
	movw	r1, #:lower16:.LC4	@,
	movt	r1, #:upper16:.LC4	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38938,
	b	.L52	@
.L122:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	movw	r3, #:lower16:.LC17	@,
	movt	r3, #:upper16:.LC17	@,
	bl	dprint_vfmw	@
	mov	r0, r9	@ D.38938, tmp458
	b	.L52	@
.L59:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	mvn	r2, #0	@,
	movt	r1, #:upper16:.LC5	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38938,
	b	.L52	@
	.fnend
	.size	AVSHAL_V300R001_StartDec, .-AVSHAL_V300R001_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.38917, %object
	.size	__func__.38917, 25
__func__.38917:
	.ascii	"AVSHAL_V300R001_StartDec\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%s: %s\012\000"
.LC1:
	.ascii	"picture width out of range\000"
	.space	1
.LC2:
	.ascii	"VdhId is wrong! AVSHAL_V200R003_StartDec\012\000"
	.space	2
.LC3:
	.ascii	"%s: VdhId(%d) > %d\012\000"
.LC4:
	.ascii	"vdm register virtual address not mapped, reset fail"
	.ascii	"ed!\012\000"
.LC5:
	.ascii	"stream_base_addr = %#x\012\000"
.LC6:
	.ascii	"BASIC_V300R001_CFG0 = 0x%x\012\000"
.LC7:
	.ascii	"BASIC_V300R001_CFG1 = 0x%x\012\000"
.LC8:
	.ascii	"AVM_V300R001_ADDR = 0x%x\012\000"
	.space	2
.LC9:
	.ascii	"VAM_V300R001_ADDR = 0x%x\012\000"
	.space	2
.LC10:
	.ascii	"STREAM_V300R001_BASE_ADDR = 0x%x\012\000"
	.space	2
.LC11:
	.ascii	"YSTADDR_V300R001_1D = 0x%x\012\000"
.LC12:
	.ascii	"YSTRIDE_V300R001_1D = 0x%x\012\000"
.LC13:
	.ascii	"UVOFFSET_V300R001_1D = 0x%x\012\000"
	.space	3
.LC14:
	.ascii	"VREG_V300R001_DNR_MBINFO_STADDR = 0x%x\012\000"
.LC15:
	.ascii	"VREG_V200R003_REF_PIC_TYPE = 0x%x\012\000"
	.space	1
.LC16:
	.ascii	"VREG_V300R001_FF_APT_EN = 0x%x\012\000"
.LC17:
	.ascii	"can not map down msg virtual address!\000"
	.space	2
.LC18:
	.ascii	"D0 = 0x%x\012\000"
	.space	1
.LC19:
	.ascii	"D1 = 0x%x\012\000"
	.space	1
.LC20:
	.ascii	"D2 = 0x%x\012\000"
	.space	1
.LC21:
	.ascii	"D3 = 0x%x\012\000"
	.space	1
.LC22:
	.ascii	"D4 = 0x%x\012\000"
	.space	1
.LC23:
	.ascii	"D5 = 0x%x\012\000"
	.space	1
.LC24:
	.ascii	"D6 = 0x%x\012\000"
	.space	1
.LC25:
	.ascii	"D7 = 0x%x\012\000"
	.space	1
.LC26:
	.ascii	"D8 = 0x%x\012\000"
	.space	1
.LC27:
	.ascii	"D9 = 0x%x\012\000"
	.space	1
.LC28:
	.ascii	"D10 = 0x%x\012\000"
.LC29:
	.ascii	"D11 = 0x%x\012\000"
.LC30:
	.ascii	"D12 = 0x%x\012\000"
.LC31:
	.ascii	"D13 = 0x%x\012\000"
.LC32:
	.ascii	"D14 = 0x%x\012\000"
.LC33:
	.ascii	"D16 = 0x%x\012\000"
.LC34:
	.ascii	"D49 = 0x%x\012\000"
.LC35:
	.ascii	"D50 = 0x%x\012\000"
.LC36:
	.ascii	"D51 = 0x%x\012\000"
.LC37:
	.ascii	"D63 = 0x%x\012\000"
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
