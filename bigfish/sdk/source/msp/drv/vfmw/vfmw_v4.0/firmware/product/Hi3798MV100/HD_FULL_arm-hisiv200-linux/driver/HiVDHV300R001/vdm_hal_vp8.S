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
	.file	"vdm_hal_vp8.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(vdm_hal_vp8)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD
@ drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/.vdm_hal_vp8.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal_vp8.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal_vp8.o
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
	.global	VP8HAL_V300R001_InitHal
	.type	VP8HAL_V300R001_InitHal, %function
VP8HAL_V300R001_InitHal:
	.fnstart
.LFB1524:
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
	.size	VP8HAL_V300R001_InitHal, .-VP8HAL_V300R001_InitHal
	.align	2
	.global	VP8HAL_V300R001_CfgDnMsg
	.type	VP8HAL_V300R001_CfgDnMsg, %function
VP8HAL_V300R001_CfgDnMsg:
	.fnstart
.LFB1527:
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
	mov	r4, r0	@ pVp8DecParam, pVp8DecParam
	ldr	r0, [r1, #48]	@, <variable>.MsgSlotAddr
	mov	r7, r1	@ pHwMem, pHwMem
	bl	MEM_Phy2Vir	@
	subs	r8, r0, #0	@ pMsgBase,
	beq	.L11	@,
	ldr	r1, [r4, #2796]	@ <variable>.frame_type, <variable>.frame_type
	mov	r5, r8	@ p32, pMsgBase
	ldr	lr, [r4, #2800]	@ <variable>.last_frame_type, <variable>.last_frame_type
	mov	r0, #4	@,
	and	r6, r1, #1	@ tmp357, <variable>.frame_type,
	movw	r1, #:lower16:.LC2	@,
	bfi	r6, lr, #1, #2	@ tmp357, <variable>.last_frame_type,,
	str	r6, [fp, #-48]	@ tmp357,
	str	r6, [r5], #4	@ tmp357,
	movt	r1, #:upper16:.LC2	@,
	ldr	r2, [fp, #-48]	@, D32
	mov	r6, #0	@ tmp353,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #2808]	@ <variable>.full_pixel, <variable>.full_pixel
	ldr	sl, [r4, #2804]	@ <variable>.use_bilinear_mc_filter, <variable>.use_bilinear_mc_filter
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC3	@,
	movt	r1, #:upper16:.LC3	@,
	rsb	r3, sl, r2, asl #1	@, tmp363, <variable>.use_bilinear_mc_filter, <variable>.full_pixel,
	add	sl, r5, r0	@ p32.562, p32,
	add	r9, r3, #1	@ D32.460, tmp363,
	str	r9, [fp, #-48]	@ D32.460, D32
	str	r9, [r8, #4]	@ D32.460,
	add	r9, sl, r0	@ p32.566, p32.562,
	ldr	r2, [fp, #-48]	@, D32
	add	ip, r9, r0	@, p32.566,
	str	ip, [fp, #-72]	@, %sfp
	bl	dprint_vfmw	@
	ldr	r1, [r4, #2784]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	mov	r0, #4	@,
	ldr	ip, [fp, #-72]	@, %sfp
	sub	r3, r1, #1	@ tmp370, <variable>.pic_width_in_mb,
	ldr	r2, [r4, #2788]	@ <variable>.pic_height_in_mb, <variable>.pic_height_in_mb
	add	ip, ip, r0	@,,
	str	ip, [fp, #-68]	@, %sfp
	mov	r3, r3, asl #23	@ tmp375, tmp370,
	add	ip, ip, r0	@,,
	sub	r2, r2, #1	@ tmp374, <variable>.pic_height_in_mb,
	str	ip, [fp, #-64]	@, %sfp
	mov	r3, r3, lsr #23	@ tmp375, tmp375,
	add	ip, ip, r0	@,,
	bfi	r3, r2, #16, #9	@ tmp375, tmp374,,
	str	ip, [fp, #-60]	@, %sfp
	str	r3, [fp, #-48]	@ tmp375,
	movw	r1, #:lower16:.LC4	@,
	str	r3, [r5, #4]	@ tmp375,
	add	r5, ip, r0	@,,
	str	r5, [fp, #-56]	@, %sfp
	movt	r1, #:upper16:.LC4	@,
	ldr	ip, [fp, #-56]	@, %sfp
	ldr	r2, [fp, #-48]	@, D32
	add	r5, ip, r0	@ p32.595,,
	bl	dprint_vfmw	@
	ldrb	r3, [r4, #2752]	@ zero_extendqisi2	@ <variable>.prob_skip_false, <variable>.prob_skip_false
	mov	r0, #4	@,
	str	r6, [fp, #-48]	@ tmp353, D32
	movw	r1, #:lower16:.LC5	@,
	ldrb	r2, [r4, #2753]	@ zero_extendqisi2	@ <variable>.mb_no_coeff_skip, <variable>.mb_no_coeff_skip
	movt	r1, #:upper16:.LC5	@,
	strb	r3, [fp, #-48]	@ <variable>.prob_skip_false, <variable>.prob_skip_false
	ldr	r3, [fp, #-48]	@ tmp381,
	ldrb	ip, [r4, #2754]	@ zero_extendqisi2	@ <variable>.multi_token_partition, <variable>.multi_token_partition
	bfi	r3, r2, #8, #1	@ tmp381, <variable>.mb_no_coeff_skip,,
	bfi	r3, ip, #9, #2	@ tmp385, <variable>.multi_token_partition,,
	str	r3, [fp, #-48]	@ tmp385,
	str	r3, [sl, #4]	@ tmp385,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldrb	r3, [r4, #2755]	@ zero_extendqisi2	@ <variable>.segmentation_enable, <variable>.segmentation_enable
	ldrb	r1, [r4, #2756]	@ zero_extendqisi2	@ <variable>.update_mb_segmentation_map, <variable>.update_mb_segmentation_map
	mov	r0, #4	@,
	ldrb	ip, [r4, #2757]	@ zero_extendqisi2	@ <variable>.mb_segmentation_abs_delta, <variable>.mb_segmentation_abs_delta
	and	r3, r3, #1	@ tmp396, <variable>.segmentation_enable,
	ldrb	r2, [r4, #2758]	@ zero_extendqisi2	@ <variable>.mode_ref_lf_delta_enabled, <variable>.mode_ref_lf_delta_enabled
	bfi	r3, r1, #1, #1	@ tmp396, <variable>.update_mb_segmentation_map,,
	bfi	r3, ip, #2, #1	@ tmp400, <variable>.mb_segmentation_abs_delta,,
	movw	r1, #:lower16:.LC6	@,
	bfi	r3, r2, #3, #1	@ tmp404, <variable>.mode_ref_lf_delta_enabled,,
	str	r3, [fp, #-48]	@ tmp404,
	str	r3, [r9, #4]	@ tmp404,
	movt	r1, #:upper16:.LC6	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldrb	r3, [r4, #2760]	@ zero_extendqisi2	@ <variable>.filter_type, <variable>.filter_type
	ldrb	r1, [r4, #2761]	@ zero_extendqisi2	@ <variable>.last_filter_type, <variable>.last_filter_type
	mov	r0, #4	@,
	ldrb	lr, [r4, #2762]	@ zero_extendqisi2	@ <variable>.filter_level, <variable>.filter_level
	and	r3, r3, #1	@ tmp415, <variable>.filter_type,
	bfi	r3, r1, #1, #2	@ tmp415, <variable>.last_filter_type,,
	ldrb	ip, [r4, #2763]	@ zero_extendqisi2	@ <variable>.sharpness_level, <variable>.sharpness_level
	bfi	r3, lr, #3, #6	@ tmp419, <variable>.filter_level,,
	ldr	lr, [fp, #-72]	@, %sfp
	ldrb	r2, [r4, #2764]	@ zero_extendqisi2	@ <variable>.last_sharpness_level, <variable>.last_sharpness_level
	bfi	r3, ip, #9, #3	@ tmp423, <variable>.sharpness_level,,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	bfi	r3, r2, #12, #3	@ tmp427, <variable>.last_sharpness_level,,
	str	r3, [fp, #-48]	@ tmp427,
	str	r3, [lr, #4]	@ tmp427,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldrb	r3, [r4, #2765]	@ zero_extendqisi2	@ <variable>.y1dc_sign, <variable>.y1dc_sign
	ldrb	r1, [r4, #2766]	@ zero_extendqisi2	@ <variable>.y1dc_absdelta_q, <variable>.y1dc_absdelta_q
	mov	r0, #4	@,
	ldrb	ip, [r4, #2767]	@ zero_extendqisi2	@ <variable>.y2dc_sign, <variable>.y2dc_sign
	and	r3, r3, #1	@ tmp438, <variable>.y1dc_sign,
	ldrb	r2, [r4, #2768]	@ zero_extendqisi2	@ <variable>.y2dc_absdelta_q, <variable>.y2dc_absdelta_q
	bfi	r3, r1, #1, #4	@ tmp438, <variable>.y1dc_absdelta_q,,
	ldrb	lr, [r4, #2769]	@ zero_extendqisi2	@ <variable>.y2ac_sign, <variable>.y2ac_sign
	bfi	r3, ip, #5, #1	@ tmp442, <variable>.y2dc_sign,,
	bfi	r3, r2, #6, #4	@ tmp446, <variable>.y2dc_absdelta_q,,
	ldrb	ip, [r4, #2770]	@ zero_extendqisi2	@ <variable>.y2ac_absdelta_q, <variable>.y2ac_absdelta_q
	ldrb	r2, [r4, #2771]	@ zero_extendqisi2	@ <variable>.uvdc_sign, <variable>.uvdc_sign
	bfi	r3, lr, #10, #1	@ tmp450, <variable>.y2ac_sign,,
	bfi	r3, ip, #11, #4	@ tmp454, <variable>.y2ac_absdelta_q,,
	ldrb	lr, [r4, #2772]	@ zero_extendqisi2	@ <variable>.uvdc_absdelta_q, <variable>.uvdc_absdelta_q
	bfi	r3, r2, #15, #1	@ tmp458, <variable>.uvdc_sign,,
	ldrb	ip, [r4, #2773]	@ zero_extendqisi2	@ <variable>.uvac_sign, <variable>.uvac_sign
	bfi	r3, lr, #16, #4	@ tmp462, <variable>.uvdc_absdelta_q,,
	ldr	lr, [fp, #-68]	@, %sfp
	ldrb	r2, [r4, #2774]	@ zero_extendqisi2	@ <variable>.uvac_absdelta_q, <variable>.uvac_absdelta_q
	bfi	r3, ip, #20, #1	@ tmp466, <variable>.uvac_sign,,
	movw	r1, #:lower16:.LC8	@,
	movt	r1, #:upper16:.LC8	@,
	bfi	r3, r2, #21, #4	@ tmp470, <variable>.uvac_absdelta_q,,
	str	r3, [fp, #-48]	@ tmp470,
	str	r3, [lr, #4]	@ tmp470,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r3, [fp, #-64]	@, %sfp
	ldrb	ip, [r4, #2759]	@ zero_extendqisi2	@ <variable>.base_qindex, <variable>.base_qindex
	mov	r1, r6	@ tmp478, tmp353
	mov	r0, #4	@,
	bfi	r1, ip, #0, #7	@ tmp478, <variable>.base_qindex,,
	str	r1, [fp, #-48]	@ tmp478,
	str	r1, [r3, #4]	@ tmp478,
	movw	r1, #:lower16:.LC9	@,
	ldr	r2, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC9	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #2780]	@ <variable>.value, <variable>.value
	ldr	ip, [fp, #-60]	@, %sfp
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC10	@,
	movt	r1, #:upper16:.LC10	@,
	str	r2, [fp, #-48]	@ <variable>.value, <variable>.value
	str	r2, [ip, #4]	@ <variable>.value,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldrb	r3, [r4, #2778]	@ zero_extendqisi2	@ <variable>.range, <variable>.range
	ldr	ip, [fp, #-56]	@, %sfp
	mov	r0, #4	@,
	str	r6, [fp, #-48]	@ tmp353, D32
	movw	r1, #:lower16:.LC11	@,
	ldrb	r2, [r4, #2779]	@ zero_extendqisi2	@ <variable>.count, <variable>.count
	movt	r1, #:upper16:.LC11	@,
	strb	r3, [fp, #-48]	@ <variable>.range, <variable>.range
	ldr	r3, [fp, #-48]	@ tmp492,
	bfi	r3, r2, #16, #6	@ tmp492, <variable>.count,,
	str	r3, [fp, #-48]	@ tmp492,
	str	r3, [ip, #4]	@ tmp492,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	ip, [r4, #2820]	@ D.32789, <variable>.bit_offset_0
	ldrb	r6, [r4, #2779]	@ zero_extendqisi2	@ D.32788, <variable>.count
	mov	r0, #4	@,
	ldr	r1, [r4, #2816]	@ D.32787, <variable>.bit_len_0
	cmp	r6, ip	@ D.32788, D.32789
	addhi	ip, ip, #128	@ tmp499, D.32789,
	add	r2, r6, r1	@ tmp501, D.32788, D.32787
	ldrhi	sl, [r4, #2824]	@ <variable>.bit_byte_offset_0, <variable>.bit_byte_offset_0
	rsbls	ip, r6, ip	@ D16_bit_offset_0, D.32788, D.32789
	rsbhi	ip, r6, ip	@ D16_bit_offset_0, D.32788, tmp499
	bic	r3, r2, #-33554432	@ tmp503, tmp501,
	ldrls	sl, [r4, #2824]	@ D17_bit_byte_offset_0, <variable>.bit_byte_offset_0
	bfi	r3, ip, #25, #7	@ tmp503, D16_bit_offset_0,,
	str	r3, [fp, #-48]	@ tmp503,
	subhi	sl, sl, #16	@ D17_bit_byte_offset_0, <variable>.bit_byte_offset_0,
	str	r3, [r5, #28]	@ tmp503,
	mov	r6, #0	@ tmp500,
	ldr	r2, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC12	@,
	movt	r1, #:upper16:.LC12	@,
	bl	dprint_vfmw	@
	mov	r0, r6	@ tmp508, tmp500
	bfi	r0, sl, #0, #24	@ tmp508, D17_bit_byte_offset_0,,
	str	r0, [fp, #-48]	@ tmp508,
	str	r0, [r5, #32]	@ tmp508,
	movw	r1, #:lower16:.LC13	@,
	ldr	r2, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC13	@,
	mov	r0, #4	@,
	bl	dprint_vfmw	@
	ldr	r1, [r4, #2828]	@ <variable>.bit_len_1, <variable>.bit_len_1
	ldr	r2, [r4, #2832]	@ <variable>.bit_offset_1, <variable>.bit_offset_1
	mov	r0, #4	@,
	bic	ip, r1, #-33554432	@ tmp515, <variable>.bit_len_1,
	movw	r1, #:lower16:.LC14	@,
	bfi	ip, r2, #25, #7	@ tmp515, <variable>.bit_offset_1,,
	str	ip, [fp, #-48]	@ tmp515,
	str	ip, [r5, #36]	@ tmp515,
	movt	r1, #:upper16:.LC14	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r3, [r4, #2836]	@ <variable>.bit_byte_offset_1, <variable>.bit_byte_offset_1
	mov	r1, r6	@ tmp520, tmp500
	mov	r0, #4	@,
	bfi	r1, r3, #0, #24	@ tmp520, <variable>.bit_byte_offset_1,,
	str	r1, [fp, #-48]	@ tmp520,
	str	r1, [r5, #40]	@ tmp520,
	movw	r1, #:lower16:.LC15	@,
	ldr	r2, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC15	@,
	bl	dprint_vfmw	@
	ldr	lr, [r4, #3036]	@ <variable>.segment_feature_dat0, <variable>.segment_feature_dat0
	ldr	ip, [r4, #3040]	@ <variable>.segment_feature_dat0, <variable>.segment_feature_dat0
	mov	r0, #4	@,
	ldr	r2, [r4, #3044]	@ <variable>.segment_feature_dat0, <variable>.segment_feature_dat0
	movw	r1, #:lower16:.LC16	@,
	ldr	r3, [r4, #3048]	@ <variable>.segment_feature_dat0, <variable>.segment_feature_dat0
	movt	r1, #:upper16:.LC16	@,
	strb	lr, [fp, #-48]	@ <variable>.segment_feature_dat0, <variable>.segment_feature_dat00
	strb	ip, [fp, #-47]	@ <variable>.segment_feature_dat0, <variable>.segment_feature_dat01
	strb	r2, [fp, #-46]	@ <variable>.segment_feature_dat0, <variable>.segment_feature_dat02
	strb	r3, [fp, #-45]	@ <variable>.segment_feature_dat0, <variable>.segment_feature_dat03
	ldr	r3, [fp, #-48]	@ D32.620, D32
	str	r3, [r5, #44]	@ D32.620,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	lr, [r4, #3052]	@ <variable>.segment_feature_dat1, <variable>.segment_feature_dat1
	ldr	ip, [r4, #3056]	@ <variable>.segment_feature_dat1, <variable>.segment_feature_dat1
	mov	r0, #4	@,
	ldr	r2, [r4, #3060]	@ <variable>.segment_feature_dat1, <variable>.segment_feature_dat1
	movw	r1, #:lower16:.LC17	@,
	ldr	r3, [r4, #3064]	@ <variable>.segment_feature_dat1, <variable>.segment_feature_dat1
	movt	r1, #:upper16:.LC17	@,
	strb	lr, [fp, #-48]	@ <variable>.segment_feature_dat1, <variable>.segment_feature_dat10
	strb	ip, [fp, #-47]	@ <variable>.segment_feature_dat1, <variable>.segment_feature_dat11
	strb	r2, [fp, #-46]	@ <variable>.segment_feature_dat1, <variable>.segment_feature_dat12
	strb	r3, [fp, #-45]	@ <variable>.segment_feature_dat1, <variable>.segment_feature_dat13
	ldr	r3, [fp, #-48]	@ D32.625, D32
	str	r3, [r5, #48]	@ D32.625,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	lr, [r4, #3068]	@ <variable>.ref_lf_delta, <variable>.ref_lf_delta
	ldr	ip, [r4, #3072]	@ <variable>.ref_lf_delta, <variable>.ref_lf_delta
	mov	r0, #4	@,
	ldr	r2, [r4, #3076]	@ <variable>.ref_lf_delta, <variable>.ref_lf_delta
	movw	r1, #:lower16:.LC18	@,
	ldr	r3, [r4, #3080]	@ <variable>.ref_lf_delta, <variable>.ref_lf_delta
	movt	r1, #:upper16:.LC18	@,
	strb	lr, [fp, #-48]	@ <variable>.ref_lf_delta, <variable>.ref_lf_delta0
	strb	ip, [fp, #-47]	@ <variable>.ref_lf_delta, <variable>.ref_lf_delta1
	strb	r2, [fp, #-46]	@ <variable>.ref_lf_delta, <variable>.ref_lf_delta2
	strb	r3, [fp, #-45]	@ <variable>.ref_lf_delta, <variable>.ref_lf_delta3
	ldr	r3, [fp, #-48]	@ D32.629, D32
	str	r3, [r5, #52]	@ D32.629,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	lr, [r4, #3084]	@ <variable>.mode_lf_delta, <variable>.mode_lf_delta
	ldr	ip, [r4, #3088]	@ <variable>.mode_lf_delta, <variable>.mode_lf_delta
	mov	r0, #4	@,
	ldr	r2, [r4, #3092]	@ <variable>.mode_lf_delta, <variable>.mode_lf_delta
	movw	r1, #:lower16:.LC19	@,
	ldr	r3, [r4, #3096]	@ <variable>.mode_lf_delta, <variable>.mode_lf_delta
	movt	r1, #:upper16:.LC19	@,
	strb	lr, [fp, #-48]	@ <variable>.mode_lf_delta, <variable>.mode_lf_delta0
	strb	ip, [fp, #-47]	@ <variable>.mode_lf_delta, <variable>.mode_lf_delta1
	strb	r2, [fp, #-46]	@ <variable>.mode_lf_delta, <variable>.mode_lf_delta2
	strb	r3, [fp, #-45]	@ <variable>.mode_lf_delta, <variable>.mode_lf_delta3
	ldr	r3, [fp, #-48]	@ D32.633, D32
	str	r3, [r5, #56]	@ D32.633,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	ip, [r4, #3104]	@ <variable>.ref_frame_sign_bias, <variable>.ref_frame_sign_bias
	ldr	lr, [r4, #3100]	@ <variable>.ref_frame_sign_bias, <variable>.ref_frame_sign_bias
	mov	r0, #4	@,
	ldr	r2, [r4, #3108]	@ <variable>.ref_frame_sign_bias, <variable>.ref_frame_sign_bias
	movw	r1, #:lower16:.LC20	@,
	ldr	r3, [r4, #3112]	@ <variable>.ref_frame_sign_bias, <variable>.ref_frame_sign_bias
	movt	r1, #:upper16:.LC20	@,
	strb	ip, [fp, #-47]	@ <variable>.ref_frame_sign_bias, <variable>.ref_frame_sign_bias_1
	strb	lr, [fp, #-48]	@ <variable>.ref_frame_sign_bias, <variable>.ref_frame_sign_bias_0
	strb	r3, [fp, #-45]	@ <variable>.ref_frame_sign_bias, <variable>.ref_frame_sign_bias_3
	strb	r2, [fp, #-46]	@ <variable>.ref_frame_sign_bias, <variable>.ref_frame_sign_bias_2
	ldr	lr, [fp, #-48]	@ D32.637, D32
	str	lr, [r5, #60]	@ D32.637,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r3, [r4, #3136]	@ D32.480, <variable>.SegIdAddr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC21	@,
	movt	r1, #:upper16:.LC21	@,
	str	r3, [fp, #-48]	@ D32.480, D32
	str	r3, [r5, #64]	@ D32.480,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	ip, [r4, #3116]	@ <variable>.image_curr_rcn_addr, <variable>.image_curr_rcn_addr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC22	@,
	movt	r1, #:upper16:.LC22	@,
	str	ip, [fp, #-48]	@ <variable>.image_curr_rcn_addr, <variable>.curr_rcn_addr
	str	ip, [r5, #92]	@ <variable>.image_curr_rcn_addr,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r4, #3120]	@ <variable>.image_alt_ref_addr, <variable>.image_alt_ref_addr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC23	@,
	movt	r1, #:upper16:.LC23	@,
	str	r2, [fp, #-48]	@ <variable>.image_alt_ref_addr, <variable>.alt_ref_addr
	str	r2, [r5, #96]	@ <variable>.image_alt_ref_addr,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r3, [r4, #3124]	@ <variable>.image_gld_ref_addr, <variable>.image_gld_ref_addr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC24	@,
	movt	r1, #:upper16:.LC24	@,
	str	r3, [fp, #-48]	@ <variable>.image_gld_ref_addr, <variable>.golden_ref_addr
	str	r3, [r5, #100]	@ <variable>.image_gld_ref_addr,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	ip, [r4, #3128]	@ <variable>.image_last_ref_addr, <variable>.image_last_ref_addr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC25	@,
	movt	r1, #:upper16:.LC25	@,
	str	ip, [fp, #-48]	@ <variable>.image_last_ref_addr, <variable>.last_ref_addr
	str	ip, [r5, #104]	@ <variable>.image_last_ref_addr,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r7, #1136]	@ <variable>.SedTopAddr, <variable>.SedTopAddr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC26	@,
	bic	r3, r2, #15	@ tmp604, <variable>.SedTopAddr,
	str	r3, [fp, #-48]	@ tmp604, <variable>.sed_top_addr
	str	r3, [r5, #108]	@ tmp604,
	movt	r1, #:upper16:.LC26	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	ip, [r7, #1140]	@ <variable>.PmvTopAddr, <variable>.PmvTopAddr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC27	@,
	bic	r2, ip, #15	@ tmp610, <variable>.PmvTopAddr,
	str	r2, [fp, #-48]	@ tmp610, <variable>.pmv_top_addr
	str	r2, [r5, #112]	@ tmp610,
	movt	r1, #:upper16:.LC27	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r3, [r7, #1144]	@ <variable>.RcnTopAddr, <variable>.RcnTopAddr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC28	@,
	bic	ip, r3, #15	@ tmp616, <variable>.RcnTopAddr,
	str	ip, [fp, #-48]	@ tmp616, <variable>.rcn_top_addr
	str	ip, [r5, #116]	@ tmp616,
	movt	r1, #:upper16:.LC28	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r7, #1180]	@ <variable>.Vp8TabAddr, <variable>.Vp8TabAddr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC29	@,
	bic	r3, r2, #15	@ tmp622, <variable>.Vp8TabAddr,
	str	r3, [fp, #-48]	@ tmp622, <variable>.tab_addr
	str	r3, [r5, #120]	@ tmp622,
	movt	r1, #:upper16:.LC29	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r0, [fp, #-48]	@, D32
	bl	MEM_Phy2Vir	@
	cmp	r0, r6	@,
	beq	.L12	@,
	mov	r1, r4	@, pVp8DecParam
	mov	r2, #2752	@,
	bl	memcpy	@
	ldr	r3, [r7, #1152]	@ <variable>.DblkTopAddr, <variable>.DblkTopAddr
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC31	@,
	bic	ip, r3, #15	@ tmp635, <variable>.DblkTopAddr,
	str	ip, [fp, #-48]	@ tmp635, <variable>.dblk_top_addr
	str	ip, [r5, #124]	@ tmp635,
	movt	r1, #:upper16:.LC31	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	mov	r0, r8	@, pMsgBase
	bl	MEM_Vir2Phy	@
	movw	r1, #:lower16:.LC32	@,
	movt	r1, #:upper16:.LC32	@,
	add	r2, r0, #256	@ D32.491,,
	str	r2, [fp, #-48]	@ D32.491, D32
	str	r2, [r5, #216]	@ D32.491,
	mov	r0, #4	@,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2844]	@ <variable>.bitn_len_0, <variable>.bitn_len_0
	ldr	r1, [r4, #2876]	@ <variable>.bitn_offset_0, <variable>.bitn_offset_0
	mov	r2, #64	@,
	bic	r3, r0, #-33554432	@ tmp644, <variable>.bitn_len_0,
	mov	r0, #4	@,
	bfi	r3, r1, #25, #7	@ tmp644, <variable>.bitn_offset_0,,
	str	r3, [fp, #-48]	@ tmp644,
	str	r3, [r5, #220]	@ tmp644,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	ip, [r4, #2908]	@ <variable>.bitn_byte_offset_0, <variable>.bitn_byte_offset_0
	mov	r3, r6	@ tmp647, tmp500
	mov	r2, #65	@,
	bfi	r3, ip, #0, #24	@ tmp647, <variable>.bitn_byte_offset_0,,
	str	r3, [fp, #-48]	@ tmp647,
	str	r3, [r5, #224]	@ tmp647,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2940]	@ <variable>.bitn_len_1, <variable>.bitn_len_1
	ldr	r1, [r4, #2972]	@ <variable>.bitn_offset_1, <variable>.bitn_offset_1
	mov	r2, #66	@,
	bic	ip, r0, #-33554432	@ tmp654, <variable>.bitn_len_1,
	mov	r0, #4	@,
	bfi	ip, r1, #25, #7	@ tmp654, <variable>.bitn_offset_1,,
	str	ip, [fp, #-48]	@ tmp654,
	str	ip, [r5, #228]	@ tmp654,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #3004]	@ <variable>.bitn_byte_offset_1, <variable>.bitn_byte_offset_1
	mov	ip, r6	@ tmp657, tmp500
	mov	r2, #67	@,
	bfi	ip, r3, #0, #24	@ tmp657, <variable>.bitn_byte_offset_1,,
	str	ip, [fp, #-48]	@ tmp657,
	str	ip, [r5, #232]	@ tmp657,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2848]	@ <variable>.bitn_len_0, <variable>.bitn_len_0
	ldr	r1, [r4, #2880]	@ <variable>.bitn_offset_0, <variable>.bitn_offset_0
	mov	r2, #68	@,
	bic	r3, r0, #-33554432	@ tmp664, <variable>.bitn_len_0,
	mov	r0, #4	@,
	bfi	r3, r1, #25, #7	@ tmp664, <variable>.bitn_offset_0,,
	str	r3, [fp, #-48]	@ tmp664,
	str	r3, [r5, #236]	@ tmp664,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	ip, [r4, #2912]	@ <variable>.bitn_byte_offset_0, <variable>.bitn_byte_offset_0
	mov	r3, r6	@ tmp667, tmp500
	mov	r2, #69	@,
	bfi	r3, ip, #0, #24	@ tmp667, <variable>.bitn_byte_offset_0,,
	str	r3, [fp, #-48]	@ tmp667,
	str	r3, [r5, #240]	@ tmp667,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2944]	@ <variable>.bitn_len_1, <variable>.bitn_len_1
	ldr	r1, [r4, #2976]	@ <variable>.bitn_offset_1, <variable>.bitn_offset_1
	mov	r2, #70	@,
	bic	ip, r0, #-33554432	@ tmp674, <variable>.bitn_len_1,
	mov	r0, #4	@,
	bfi	ip, r1, #25, #7	@ tmp674, <variable>.bitn_offset_1,,
	str	ip, [fp, #-48]	@ tmp674,
	str	ip, [r5, #244]	@ tmp674,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #3008]	@ <variable>.bitn_byte_offset_1, <variable>.bitn_byte_offset_1
	mov	ip, r6	@ tmp677, tmp500
	mov	r2, #71	@,
	bfi	ip, r3, #0, #24	@ tmp677, <variable>.bitn_byte_offset_1,,
	str	ip, [fp, #-48]	@ tmp677,
	str	ip, [r5, #248]	@ tmp677,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2852]	@ <variable>.bitn_len_0, <variable>.bitn_len_0
	ldr	r1, [r4, #2884]	@ <variable>.bitn_offset_0, <variable>.bitn_offset_0
	mov	r2, #72	@,
	bic	r3, r0, #-33554432	@ tmp684, <variable>.bitn_len_0,
	mov	r0, #4	@,
	bfi	r3, r1, #25, #7	@ tmp684, <variable>.bitn_offset_0,,
	str	r3, [fp, #-48]	@ tmp684,
	str	r3, [r5, #252]	@ tmp684,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	ip, [r4, #2916]	@ <variable>.bitn_byte_offset_0, <variable>.bitn_byte_offset_0
	mov	r3, r6	@ tmp687, tmp500
	mov	r2, #73	@,
	bfi	r3, ip, #0, #24	@ tmp687, <variable>.bitn_byte_offset_0,,
	str	r3, [fp, #-48]	@ tmp687,
	str	r3, [r5, #256]	@ tmp687,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2948]	@ <variable>.bitn_len_1, <variable>.bitn_len_1
	ldr	r1, [r4, #2980]	@ <variable>.bitn_offset_1, <variable>.bitn_offset_1
	mov	r2, #74	@,
	bic	ip, r0, #-33554432	@ tmp694, <variable>.bitn_len_1,
	mov	r0, #4	@,
	bfi	ip, r1, #25, #7	@ tmp694, <variable>.bitn_offset_1,,
	str	ip, [fp, #-48]	@ tmp694,
	str	ip, [r5, #260]	@ tmp694,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #3012]	@ <variable>.bitn_byte_offset_1, <variable>.bitn_byte_offset_1
	mov	ip, r6	@ tmp697, tmp500
	mov	r2, #75	@,
	bfi	ip, r3, #0, #24	@ tmp697, <variable>.bitn_byte_offset_1,,
	str	ip, [fp, #-48]	@ tmp697,
	str	ip, [r5, #264]	@ tmp697,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2856]	@ <variable>.bitn_len_0, <variable>.bitn_len_0
	ldr	r1, [r4, #2888]	@ <variable>.bitn_offset_0, <variable>.bitn_offset_0
	mov	r2, #76	@,
	bic	r3, r0, #-33554432	@ tmp704, <variable>.bitn_len_0,
	mov	r0, #4	@,
	bfi	r3, r1, #25, #7	@ tmp704, <variable>.bitn_offset_0,,
	str	r3, [fp, #-48]	@ tmp704,
	str	r3, [r5, #268]	@ tmp704,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	ip, [r4, #2920]	@ <variable>.bitn_byte_offset_0, <variable>.bitn_byte_offset_0
	mov	r3, r6	@ tmp707, tmp500
	mov	r2, #77	@,
	bfi	r3, ip, #0, #24	@ tmp707, <variable>.bitn_byte_offset_0,,
	str	r3, [fp, #-48]	@ tmp707,
	str	r3, [r5, #272]	@ tmp707,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2952]	@ <variable>.bitn_len_1, <variable>.bitn_len_1
	ldr	r1, [r4, #2984]	@ <variable>.bitn_offset_1, <variable>.bitn_offset_1
	mov	r2, #78	@,
	bic	ip, r0, #-33554432	@ tmp714, <variable>.bitn_len_1,
	mov	r0, #4	@,
	bfi	ip, r1, #25, #7	@ tmp714, <variable>.bitn_offset_1,,
	str	ip, [fp, #-48]	@ tmp714,
	str	ip, [r5, #276]	@ tmp714,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #3016]	@ <variable>.bitn_byte_offset_1, <variable>.bitn_byte_offset_1
	mov	ip, r6	@ tmp717, tmp500
	mov	r2, #79	@,
	bfi	ip, r3, #0, #24	@ tmp717, <variable>.bitn_byte_offset_1,,
	str	ip, [fp, #-48]	@ tmp717,
	str	ip, [r5, #280]	@ tmp717,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2860]	@ <variable>.bitn_len_0, <variable>.bitn_len_0
	ldr	r1, [r4, #2892]	@ <variable>.bitn_offset_0, <variable>.bitn_offset_0
	mov	r2, #80	@,
	bic	r3, r0, #-33554432	@ tmp724, <variable>.bitn_len_0,
	mov	r0, #4	@,
	bfi	r3, r1, #25, #7	@ tmp724, <variable>.bitn_offset_0,,
	str	r3, [fp, #-48]	@ tmp724,
	str	r3, [r5, #284]	@ tmp724,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	ip, [r4, #2924]	@ <variable>.bitn_byte_offset_0, <variable>.bitn_byte_offset_0
	mov	r3, r6	@ tmp727, tmp500
	mov	r2, #81	@,
	bfi	r3, ip, #0, #24	@ tmp727, <variable>.bitn_byte_offset_0,,
	str	r3, [fp, #-48]	@ tmp727,
	str	r3, [r5, #288]	@ tmp727,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2956]	@ <variable>.bitn_len_1, <variable>.bitn_len_1
	ldr	r1, [r4, #2988]	@ <variable>.bitn_offset_1, <variable>.bitn_offset_1
	mov	r2, #82	@,
	bic	ip, r0, #-33554432	@ tmp734, <variable>.bitn_len_1,
	mov	r0, #4	@,
	bfi	ip, r1, #25, #7	@ tmp734, <variable>.bitn_offset_1,,
	str	ip, [fp, #-48]	@ tmp734,
	str	ip, [r5, #292]	@ tmp734,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #3020]	@ <variable>.bitn_byte_offset_1, <variable>.bitn_byte_offset_1
	mov	ip, r6	@ tmp737, tmp500
	mov	r2, #83	@,
	bfi	ip, r3, #0, #24	@ tmp737, <variable>.bitn_byte_offset_1,,
	str	ip, [fp, #-48]	@ tmp737,
	str	ip, [r5, #296]	@ tmp737,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2864]	@ <variable>.bitn_len_0, <variable>.bitn_len_0
	ldr	r1, [r4, #2896]	@ <variable>.bitn_offset_0, <variable>.bitn_offset_0
	mov	r2, #84	@,
	bic	r3, r0, #-33554432	@ tmp744, <variable>.bitn_len_0,
	mov	r0, #4	@,
	bfi	r3, r1, #25, #7	@ tmp744, <variable>.bitn_offset_0,,
	str	r3, [fp, #-48]	@ tmp744,
	str	r3, [r5, #300]	@ tmp744,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	ip, [r4, #2928]	@ <variable>.bitn_byte_offset_0, <variable>.bitn_byte_offset_0
	mov	r3, r6	@ tmp747, tmp500
	mov	r2, #85	@,
	bfi	r3, ip, #0, #24	@ tmp747, <variable>.bitn_byte_offset_0,,
	str	r3, [fp, #-48]	@ tmp747,
	str	r3, [r5, #304]	@ tmp747,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2960]	@ <variable>.bitn_len_1, <variable>.bitn_len_1
	ldr	r1, [r4, #2992]	@ <variable>.bitn_offset_1, <variable>.bitn_offset_1
	mov	r2, #86	@,
	bic	ip, r0, #-33554432	@ tmp754, <variable>.bitn_len_1,
	mov	r0, #4	@,
	bfi	ip, r1, #25, #7	@ tmp754, <variable>.bitn_offset_1,,
	str	ip, [fp, #-48]	@ tmp754,
	str	ip, [r5, #308]	@ tmp754,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #3024]	@ <variable>.bitn_byte_offset_1, <variable>.bitn_byte_offset_1
	mov	ip, r6	@ tmp757, tmp500
	mov	r2, #87	@,
	bfi	ip, r3, #0, #24	@ tmp757, <variable>.bitn_byte_offset_1,,
	str	ip, [fp, #-48]	@ tmp757,
	str	ip, [r5, #312]	@ tmp757,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2868]	@ <variable>.bitn_len_0, <variable>.bitn_len_0
	ldr	r1, [r4, #2900]	@ <variable>.bitn_offset_0, <variable>.bitn_offset_0
	mov	r2, #88	@,
	bic	r3, r0, #-33554432	@ tmp764, <variable>.bitn_len_0,
	mov	r0, #4	@,
	bfi	r3, r1, #25, #7	@ tmp764, <variable>.bitn_offset_0,,
	str	r3, [fp, #-48]	@ tmp764,
	str	r3, [r5, #316]	@ tmp764,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	ip, [r4, #2932]	@ <variable>.bitn_byte_offset_0, <variable>.bitn_byte_offset_0
	mov	r3, r6	@ tmp767, tmp500
	mov	r2, #89	@,
	bfi	r3, ip, #0, #24	@ tmp767, <variable>.bitn_byte_offset_0,,
	str	r3, [fp, #-48]	@ tmp767,
	str	r3, [r5, #320]	@ tmp767,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2964]	@ <variable>.bitn_len_1, <variable>.bitn_len_1
	ldr	r1, [r4, #2996]	@ <variable>.bitn_offset_1, <variable>.bitn_offset_1
	mov	r2, #90	@,
	bic	ip, r0, #-33554432	@ tmp774, <variable>.bitn_len_1,
	mov	r0, #4	@,
	bfi	ip, r1, #25, #7	@ tmp774, <variable>.bitn_offset_1,,
	str	ip, [fp, #-48]	@ tmp774,
	str	ip, [r5, #324]	@ tmp774,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #3028]	@ <variable>.bitn_byte_offset_1, <variable>.bitn_byte_offset_1
	mov	ip, r6	@ tmp777, tmp500
	mov	r2, #91	@,
	bfi	ip, r3, #0, #24	@ tmp777, <variable>.bitn_byte_offset_1,,
	str	ip, [fp, #-48]	@ tmp777,
	str	ip, [r5, #328]	@ tmp777,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2872]	@ <variable>.bitn_len_0, <variable>.bitn_len_0
	ldr	r1, [r4, #2904]	@ <variable>.bitn_offset_0, <variable>.bitn_offset_0
	mov	r2, #92	@,
	bic	r3, r0, #-33554432	@ tmp784, <variable>.bitn_len_0,
	mov	r0, #4	@,
	bfi	r3, r1, #25, #7	@ tmp784, <variable>.bitn_offset_0,,
	str	r3, [fp, #-48]	@ tmp784,
	str	r3, [r5, #332]	@ tmp784,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	ip, [r4, #2936]	@ <variable>.bitn_byte_offset_0, <variable>.bitn_byte_offset_0
	mov	r3, r6	@ tmp787, tmp500
	mov	r2, #93	@,
	bfi	r3, ip, #0, #24	@ tmp787, <variable>.bitn_byte_offset_0,,
	str	r3, [fp, #-48]	@ tmp787,
	str	r3, [r5, #336]	@ tmp787,
	mov	r0, #4	@,
	ldr	r3, [fp, #-48]	@, D32
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #2968]	@ <variable>.bitn_len_1, <variable>.bitn_len_1
	ldr	r1, [r4, #3000]	@ <variable>.bitn_offset_1, <variable>.bitn_offset_1
	mov	r2, #94	@,
	bic	ip, r0, #-33554432	@ tmp794, <variable>.bitn_len_1,
	mov	r0, #4	@,
	bfi	ip, r1, #25, #7	@ tmp794, <variable>.bitn_offset_1,,
	str	ip, [fp, #-48]	@ tmp794,
	str	ip, [r5, #340]	@ tmp794,
	movw	r1, #:lower16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	movt	r1, #:upper16:.LC33	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #3032]	@ <variable>.bitn_byte_offset_1, <variable>.bitn_byte_offset_1
	mov	ip, r6	@ tmp797, tmp500
	mov	r0, #4	@,
	bfi	ip, r3, #0, #24	@ tmp797, <variable>.bitn_byte_offset_1,,
	str	ip, [fp, #-48]	@ tmp797,
	str	ip, [r5, #344]	@ tmp797,
	movw	r1, #:lower16:.LC33	@,
	mov	r2, #95	@,
	movt	r1, #:upper16:.LC33	@,
	ldr	r3, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	mov	r0, r6	@ D.32696, tmp500
.L5:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L11:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.32696,
	b	.L5	@
.L12:
	movw	r1, #:lower16:.LC30	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	movt	r1, #:upper16:.LC30	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.32696,
	b	.L5	@
	.fnend
	.size	VP8HAL_V300R001_CfgDnMsg, .-VP8HAL_V300R001_CfgDnMsg
	.align	2
	.global	VP8HAL_V300R001_CfgReg
	.type	VP8HAL_V300R001_CfgReg, %function
VP8HAL_V300R001_CfgReg:
	.fnstart
.LFB1525:
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
	cmp	r2, #1	@ VdhId,
	mov	ip, #0	@ tmp170,
	mov	r5, r0	@ pVp8DecParam, pVp8DecParam
	mov	r6, r1	@ pHwMem, pHwMem
	str	ip, [fp, #-32]	@ tmp170, D32
	bls	.L27	@,
	mov	r0, ip	@, tmp170
	movw	r1, #:lower16:.LC34	@,
	movt	r1, #:upper16:.LC34	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.32486,
.L16:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L27:
	beq	.L28	@,
	ldr	r3, [r1, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	cmp	r3, #0	@ <variable>.pVdmRegVirAddr,
	beq	.L29	@,
.L18:
	ldr	lr, [r5, #2788]	@ <variable>.pic_height_in_mb, <variable>.pic_height_in_mb
	movw	r4, #:lower16:g_HwMem	@ tmp303,
	ldr	ip, [r5, #2784]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	movt	r4, #:upper16:g_HwMem	@ tmp303,
	mov	r7, #0	@ tmp180,
	mov	r0, #3	@,
	ldr	r2, [r4, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movw	r1, #:lower16:.LC37	@,
	mul	r3, ip, lr	@ tmp181, <variable>.pic_width_in_mb, <variable>.pic_height_in_mb
	movt	r1, #:upper16:.LC37	@,
	sub	lr, r3, #1	@ tmp184, tmp181,
	bic	r3, lr, #-16777216	@ tmp187, tmp184,
	bic	ip, r3, #15728640	@ tmp187, tmp187,
	bfi	ip, r7, #31, #1	@ tmp187, tmp180,,
	str	ip, [fp, #-32]	@ tmp187,
	str	ip, [r2, #8]	@ tmp187,
	ldr	r2, [fp, #-32]	@, D32
	bl	dprint_vfmw	@
	ldr	r1, [r5, #2792]	@ <variable>.ddr_stride, <variable>.ddr_stride
	mov	r3, #536870924	@ tmp197,
	ldr	ip, [r5, #3140]	@ <variable>.Compress_en, <variable>.Compress_en
	ldr	r2, [r4, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r0, #3	@,
	mov	lr, r1, lsr #6	@ tmp195, <variable>.ddr_stride,
	movw	r1, #:lower16:.LC38	@,
	bfi	r3, lr, #4, #10	@ tmp197, tmp195,,
	movt	r1, #:upper16:.LC38	@,
	orr	r3, r3, #49152	@ tmp202, tmp197,
	bfi	r3, r7, #16, #12	@ tmp202, tmp180,,
	orr	lr, r3, #536870912	@ tmp206, tmp202,
	bfi	lr, ip, #30, #1	@ tmp206, <variable>.Compress_en,,
	bfi	lr, r7, #31, #1	@ tmp207, tmp180,,
	str	lr, [fp, #-32]	@ tmp207,
	str	lr, [r2, #12]	@ tmp207,
	ldr	r2, [fp, #-32]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r4, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	ldr	ip, [r6, #48]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC39	@,
	movt	r1, #:upper16:.LC39	@,
	bic	r3, ip, #15	@ tmp215, <variable>.MsgSlotAddr,
	str	r3, [fp, #-32]	@ tmp215, <variable>.av_msg_addr
	str	r3, [r2, #16]	@ tmp215,
	ldr	r2, [fp, #-32]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r4, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	ldr	ip, [r6, #32]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC40	@,
	movt	r1, #:upper16:.LC40	@,
	bic	r3, ip, #15	@ tmp223, <variable>.MsgSlotAddr,
	str	r3, [fp, #-32]	@ tmp223, <variable>.va_msg_addr
	str	r3, [r2, #20]	@ tmp223,
	ldr	r2, [fp, #-32]	@, D32
	bl	dprint_vfmw	@
	ldr	ip, [r5, #2812]	@ <variable>.stream_base_addr, <variable>.stream_base_addr
	ldr	r2, [r4, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC41	@,
	movt	r1, #:upper16:.LC41	@,
	str	ip, [fp, #-32]	@ <variable>.stream_base_addr, <variable>.stream_base_addr
	str	ip, [r2, #24]	@ <variable>.stream_base_addr,
	ldr	r2, [fp, #-32]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r4, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	ldr	r3, [r6, #1156]	@ <variable>.PpfdBufAddr, <variable>.PpfdBufAddr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC42	@,
	movt	r1, #:upper16:.LC42	@,
	bic	ip, r3, #15	@ D32.448, <variable>.PpfdBufAddr,
	str	ip, [fp, #-32]	@ D32.448, D32
	str	ip, [r2, #128]	@ D32.448,
	ldr	r2, [fp, #-32]	@, D32
	bl	dprint_vfmw	@
	ldr	r3, [r6, #1160]	@ D32.449, <variable>.PpfdBufLen
	ldr	r6, [r4, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC43	@,
	movt	r1, #:upper16:.LC43	@,
	str	r3, [fp, #-32]	@ D32.449, D32
	str	r3, [r6, #132]	@ D32.449,
	ldr	r2, [fp, #-32]	@, D32
	bl	dprint_vfmw	@
	ldr	r1, [r5, #2784]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	movw	ip, #:lower16:s_RegPhyBaseAddr	@ tmp247,
	movt	ip, #:upper16:s_RegPhyBaseAddr	@ tmp247,
	cmp	r1, #256	@ <variable>.pic_width_in_mb,
	ldr	r0, [ip, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	movwls	r1, #:lower16:96016	@ tmp246,
	movwhi	r1, #30480	@ tmp245,
	movtls	r1, #:upper16:96016	@ tmp246,
	add	r0, r0, #4	@, s_RegPhyBaseAddr,
	str	r1, [fp, #-32]	@ tmp246, D32
	bl	MEM_WritePhyWord	@
	ldr	r6, [r4, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r0, #3	@,
	ldr	r2, [r5, #3116]	@ <variable>.image_curr_rcn_addr, <variable>.image_curr_rcn_addr
	movw	r1, #:lower16:.LC44	@,
	movt	r1, #:upper16:.LC44	@,
	bic	r3, r2, #15	@ tmp253, <variable>.image_curr_rcn_addr,
	str	r3, [fp, #-32]	@ tmp253, <variable>.ystaddr_1d
	str	r3, [r6, #96]	@ tmp253,
	ldr	r2, [fp, #-32]	@, D32
	bl	dprint_vfmw	@
	ldr	r6, [r5, #2792]	@ ystride, <variable>.ddr_stride
	ldr	ip, [r4, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC45	@,
	movt	r1, #:upper16:.LC45	@,
	str	r6, [fp, #-32]	@ ystride, <variable>.ystride_1d
	str	r6, [ip, #100]	@ ystride,
	ldr	r2, [fp, #-32]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r5, #2784]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	movw	r3, #2047	@ tmp267,
	mov	r2, r2, asl #4	@ D.32595, <variable>.pic_width_in_mb,
	sub	r0, r2, #1	@ tmp266, D.32595,
	cmp	r0, r3	@ tmp266, tmp267
	bhi	.L30	@,
.L22:
	mov	r7, #16	@ level,
.L24:
	ldr	r2, [r5, #2788]	@ temp.962, <variable>.pic_height_in_mb
	mov	r0, #3	@,
	ldr	lr, [r4, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movw	r1, #:lower16:.LC46	@,
	add	ip, r2, #1	@ tmp283, temp.962,
	movt	r1, #:upper16:.LC46	@,
	mov	r3, r2, asl #4	@ tmp278, temp.962,
	add	r2, r3, #31	@ tmp279, tmp278,
	mov	ip, ip, lsr #1	@ tmp284, tmp283,
	mov	r3, r2, lsr #5	@ tmp280, tmp279,
	mul	r2, r6, ip	@ tmp285, ystride, tmp284
	mov	ip, r3, asl #4	@ tmp281, tmp280,
	mla	r6, r7, ip, r2	@ tmp286, level, tmp281, tmp285
	mov	r6, r6, asl #1	@ tmp287, tmp286,
	str	r6, [fp, #-32]	@ tmp287, <variable>.uvoffset_1d
	str	r6, [lr, #104]	@ tmp287,
	ldr	r2, [fp, #-32]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r5, #2788]	@ <variable>.pic_height_in_mb, <variable>.pic_height_in_mb
	ldr	ip, [r4, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r0, #0	@ D.32486,
	mov	r3, r2, asl #4	@ tmp292, <variable>.pic_height_in_mb,
	add	r1, r3, #31	@ tmp294, tmp292,
	bic	r2, r1, #31	@ tmp296, tmp294,
	mvn	r1, #0	@ tmp301,
	mul	r7, r7, r2	@ D32.455, level, tmp296
	str	r7, [ip, #108]	@ D32.455,
	ldr	r3, [r4, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r1, [r3, #32]	@ tmp301,
	b	.L16	@
.L30:
	sub	r1, r2, #2048	@ tmp268, D.32595,
	sub	r0, r1, #1	@ tmp268, tmp268,
	cmp	r0, r3	@ tmp268, tmp267
	movls	r7, #32	@ level,
	bls	.L24	@,
	sub	ip, r2, #4096	@ tmp271, D.32595,
	sub	lr, ip, #1	@ tmp271, tmp271,
	cmp	lr, r3	@ tmp271, tmp267
	movls	r7, #48	@ level,
	bls	.L24	@,
	sub	r0, r2, #6144	@ tmp274, D.32595,
	sub	r2, r0, #1	@ tmp274, tmp274,
	cmp	r2, r3	@ tmp274, tmp267
	movls	r7, #64	@ level,
	bls	.L24	@,
	b	.L22	@
.L29:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r1, r0, #0	@ D.32493,
	strne	r1, [r6, #0]	@ D.32493, <variable>.pVdmRegVirAddr
	bne	.L18	@,
	movw	r1, #:lower16:.LC36	@,
	movt	r1, #:upper16:.LC36	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.32486,
	b	.L16	@
.L28:
	mov	r3, r2	@, VdhId
	mov	r0, ip	@, tmp170
	movw	r1, #:lower16:.LC35	@,
	ldr	r2, .L31	@,
	movt	r1, #:upper16:.LC35	@,
	str	ip, [sp, #0]	@ tmp170,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.32486,
	b	.L16	@
.L32:
	.align	2
.L31:
	.word	.LANCHOR0+28
	.fnend
	.size	VP8HAL_V300R001_CfgReg, .-VP8HAL_V300R001_CfgReg
	.align	2
	.global	VP8HAL_V300R001_StartDec
	.type	VP8HAL_V300R001_StartDec, %function
VP8HAL_V300R001_StartDec:
	.fnstart
.LFB1526:
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
	cmp	r1, #1	@ VdhId,
	mov	r4, r0	@ pVp8DecParam, pVp8DecParam
	bls	.L43	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC47	@,
	movt	r1, #:upper16:.LC47	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.32655,
.L36:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L43:
	beq	.L45	@,
	ldr	r3, [r0, #2784]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	cmp	r3, #512	@ <variable>.pic_width_in_mb,
	bhi	.L44	@,
	ldr	r0, [r0, #2788]	@ <variable>.pic_height_in_mb, <variable>.pic_height_in_mb
	cmp	r0, #512	@ <variable>.pic_height_in_mb,
	bhi	.L44	@,
	movw	r5, #:lower16:g_HwMem	@ tmp155,
	movt	r5, #:upper16:g_HwMem	@ tmp155,
	ldr	r1, [r5, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	cmp	r1, #0	@ <variable>.pVdmRegVirAddr,
	beq	.L46	@,
.L40:
	mov	r2, #0	@,
	mov	r0, r4	@, pVp8DecParam
	movw	r1, #:lower16:g_HwMem	@,
	movt	r1, #:upper16:g_HwMem	@,
	bl	VP8HAL_V300R001_CfgReg	@
	mov	r0, r4	@, pVp8DecParam
	movw	r1, #:lower16:g_HwMem	@,
	mov	r2, #0	@,
	movt	r1, #:upper16:g_HwMem	@,
	bl	VP8HAL_V300R001_CfgDnMsg	@
	mov	r0, #0	@ D.32655,
	b	.L36	@
.L46:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r2, r0, #0	@ D.32669,
	strne	r2, [r5, #0]	@ D.32669, <variable>.pVdmRegVirAddr
	bne	.L40	@,
	movw	r1, #:lower16:.LC36	@,
	movt	r1, #:upper16:.LC36	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.32655,
	b	.L36	@
.L45:
	mov	ip, #0	@ tmp144,
	mov	r3, r1	@, VdhId
	mov	r0, ip	@, tmp144
	movw	r1, #:lower16:.LC35	@,
	ldr	r2, .L47	@,
	movt	r1, #:upper16:.LC35	@,
	str	ip, [sp, #0]	@ tmp144,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.32655,
	b	.L36	@
.L44:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	ldr	r2, .L47	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC48	@,
	movt	r3, #:upper16:.LC48	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.32655,
	b	.L36	@
.L48:
	.align	2
.L47:
	.word	.LANCHOR0+52
	.fnend
	.size	VP8HAL_V300R001_StartDec, .-VP8HAL_V300R001_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.32687, %object
	.size	__func__.32687, 25
__func__.32687:
	.ascii	"VP8HAL_V300R001_CfgDnMsg\000"
	.space	3
	.type	__func__.32480, %object
	.size	__func__.32480, 23
__func__.32480:
	.ascii	"VP8HAL_V300R001_CfgReg\000"
	.space	1
	.type	__func__.32651, %object
	.size	__func__.32651, 25
__func__.32651:
	.ascii	"VP8HAL_V300R001_StartDec\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%s: %s\012\000"
.LC1:
	.ascii	"can not map down msg virtual address!\000"
	.space	2
.LC2:
	.ascii	"D0 = 0x%x\012\000"
	.space	1
.LC3:
	.ascii	"D1 = 0x%x\012\000"
	.space	1
.LC4:
	.ascii	"D2 = 0x%x\012\000"
	.space	1
.LC5:
	.ascii	"D3 = 0x%x\012\000"
	.space	1
.LC6:
	.ascii	"D4 = 0x%x\012\000"
	.space	1
.LC7:
	.ascii	"D5 = 0x%x\012\000"
	.space	1
.LC8:
	.ascii	"D6 = 0x%x\012\000"
	.space	1
.LC9:
	.ascii	"D7 = 0x%x\012\000"
	.space	1
.LC10:
	.ascii	"D8 = 0x%x\012\000"
	.space	1
.LC11:
	.ascii	"D9 = 0x%x\012\000"
	.space	1
.LC12:
	.ascii	"D16 = 0x%x\012\000"
.LC13:
	.ascii	"D17 = 0x%x\012\000"
.LC14:
	.ascii	"D18 = 0x%x\012\000"
.LC15:
	.ascii	"D19 = 0x%x\012\000"
.LC16:
	.ascii	"D20 = 0x%x\012\000"
.LC17:
	.ascii	"D21 = 0x%x\012\000"
.LC18:
	.ascii	"D22 = 0x%x\012\000"
.LC19:
	.ascii	"D23 = 0x%x\012\000"
.LC20:
	.ascii	"D24 = 0x%x\012\000"
.LC21:
	.ascii	"D25 = 0x%x\012\000"
.LC22:
	.ascii	"D32 = 0x%x\012\000"
.LC23:
	.ascii	"D33 = 0x%x\012\000"
.LC24:
	.ascii	"D34 = 0x%x\012\000"
.LC25:
	.ascii	"D35 = 0x%x\012\000"
.LC26:
	.ascii	"D36 = 0x%x\012\000"
.LC27:
	.ascii	"D37 = 0x%x\012\000"
.LC28:
	.ascii	"D38 = 0x%x\012\000"
.LC29:
	.ascii	"D39 = 0x%x\012\000"
.LC30:
	.ascii	"%s: u8Tmp = NULL\012\000"
	.space	2
.LC31:
	.ascii	"D40 = 0x%x\012\000"
.LC32:
	.ascii	"D63 = 0x%x\012\000"
.LC33:
	.ascii	"D%d = 0x%x\012\000"
.LC34:
	.ascii	"VdhId is wrong! MP2HAL_V200R003_CfgReg\012\000"
.LC35:
	.ascii	"%s: VdhId(%d) > %d\012\000"
.LC36:
	.ascii	"vdm register virtual address not mapped, reset fail"
	.ascii	"ed!\012\000"
.LC37:
	.ascii	"BASIC_CFG0 = 0x%x\012\000"
	.space	1
.LC38:
	.ascii	"BASIC_CFG1 = 0x%x\012\000"
	.space	1
.LC39:
	.ascii	"AVM_ADDR = 0x%x\012\000"
	.space	3
.LC40:
	.ascii	"VAM_ADDR = 0x%x\012\000"
	.space	3
.LC41:
	.ascii	"STREAM_BASE_ADDR = 0x%x\012\000"
	.space	3
.LC42:
	.ascii	"PPFD_BUF_ADDR = 0x%x\012\000"
	.space	2
.LC43:
	.ascii	"PPFD_BUF_LEN = 0x%x\012\000"
	.space	3
.LC44:
	.ascii	"YSTADDR_1D = 0x%x\012\000"
	.space	1
.LC45:
	.ascii	"YSTRIDE_1D = 0x%x\012\000"
	.space	1
.LC46:
	.ascii	"UVOFFSET_1D = 0x%x\012\000"
.LC47:
	.ascii	"VdhId is wrong! VP8HAL_V200R003_StartDec\012\000"
	.space	2
.LC48:
	.ascii	"picture width out of range\000"
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
