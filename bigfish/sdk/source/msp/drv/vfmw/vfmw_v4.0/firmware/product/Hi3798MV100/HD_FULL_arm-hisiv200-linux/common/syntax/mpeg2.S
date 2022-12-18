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
	.file	"mpeg2.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(mpeg2) -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw)
@ -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/vfmw/vfmw_v4.0/firmware/common/syntax/.mpeg2.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/common/syntax/mpeg2.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/vfmw/vfmw_v4.0/firmware/common/syntax/mpeg2.o -O2 -Wall
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
	.global	MP2_VerifyMemPara
	.type	MP2_VerifyMemPara, %function
MP2_VerifyMemPara:
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
	mov	r0, #1	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	MP2_VerifyMemPara, .-MP2_VerifyMemPara
	.align	2
	.global	MP2_EstimatePicQp
	.type	MP2_EstimatePicQp, %function
MP2_EstimatePicQp:
	.fnstart
.LFB1533:
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #132
	sub	sp, sp, #132	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r1, #:lower16:.LANCHOR0	@,
	mov	r4, r0	@ pCtx, pCtx
	movt	r1, #:upper16:.LANCHOR0	@,
	sub	r0, fp, #148	@,,
	mov	r2, #128	@,
	bl	memcpy	@
	movw	r1, #:lower16:78704	@ tmp142,
	movt	r1, #:upper16:78704	@ tmp142,
	ldr	r0, [r4, #300]	@ QuantScaleCode, <variable>.quantiser_scale_code
	ldr	r3, [r4, r1]	@ <variable>.CodecInfo.MpegFlag, <variable>.CodecInfo.MpegFlag
	cmp	r3, #1	@ <variable>.CodecInfo.MpegFlag,
	beq	.L5	@,
	movw	lr, #:lower16:79992	@ tmp145,
	movt	lr, #:upper16:79992	@ tmp145,
	ldr	ip, [r4, lr]	@ <variable>.pSyntaxInfNew, <variable>.pSyntaxInfNew
	ldrb	r2, [ip, #13]	@ zero_extendqisi2	@ <variable>.q_scale_type, <variable>.q_scale_type
	cmp	r2, #0	@ <variable>.q_scale_type,
	subne	r2, fp, #20	@,,
	moveq	r0, r0, asl #1	@ QuantScale, QuantScaleCode,
	addne	r0, r2, r0, asl #2	@, tmp149,, QuantScaleCode,
	ldrne	r0, [r0, #-128]	@ QuantScale, Non_Linear_quantizer_scale
.L5:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
	.fnend
	.size	MP2_EstimatePicQp, .-MP2_EstimatePicQp
	.global	__aeabi_idiv
	.align	2
	.global	MP2_CalcRealEncFrameRate
	.type	MP2_CalcRealEncFrameRate, %function
MP2_CalcRealEncFrameRate:
	.fnstart
.LFB1537:
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
	movw	ip, #:lower16:79992	@ tmp152,
	movt	ip, #:upper16:79992	@ tmp152,
	mov	r4, r0	@ pCtx, pCtx
	movw	r6, #:lower16:78808	@ tmp146,
	movw	r2, #:lower16:78820	@ tmp147,
	ldr	r7, [r0, ip]	@ D.39433, <variable>.pSyntaxInfNew
	movt	r6, #:upper16:78808	@ tmp146,
	movt	r2, #:upper16:78820	@ tmp147,
	movw	r5, #:lower16:78804	@ tmp148,
	movw	r1, #:lower16:78816	@ tmp149,
	movt	r5, #:upper16:78804	@ tmp148,
	ldrb	r3, [r7, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	movt	r1, #:upper16:78816	@ tmp149,
	movw	ip, #:lower16:78800	@ tmp150,
	movw	r0, #:lower16:78812	@ tmp151,
	cmp	r3, #1	@ <variable>.picture_coding_type,
	movt	r0, #:upper16:78812	@ tmp151,
	movt	ip, #:upper16:78800	@ tmp150,
	ldr	r3, [r4, r6]	@ D.39427, <variable>.GopFrmCnt
	ldr	r2, [r4, r2]	@ D.39428, <variable>.GopFrmCnt
	ldr	r6, [r4, r5]	@ D.39429, <variable>.GopFldCnt
	ldr	r1, [r4, r1]	@ D.39430, <variable>.GopFldCnt
	ldr	r5, [r4, r0]	@ D.39432, <variable>.GopFrmCntNoRpt
	ldr	ip, [r4, ip]	@ D.39431, <variable>.GopFrmCntNoRpt
	ldr	r0, [r7, #72]	@ D.39434, <variable>.frame_rate
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	add	ip, r5, ip	@ FrmNumNoRpt, D.39432, D.39431
	cmp	r0, #0	@ D.39434,
	cmpgt	ip, #0	@, FrmNumNoRpt,
	ble	.L11	@,
	add	r1, r1, r6	@ FldNum, D.39430, D.39429
	cmp	r1, #0	@ FldNum,
	ble	.L11	@,
	mul	r0, ip, r0	@, FrmNumNoRpt, D.39434
	ldrb	lr, [r7, #27]	@ zero_extendqisi2	@ <variable>.progressive_sequence, <variable>.progressive_sequence
	cmp	lr, #1	@ <variable>.progressive_sequence,
	addeq	r1, r2, r3	@, D.39428, D.39427
	movne	r0, r0, asl #1	@, tmp168,
	bl	__aeabi_idiv	@
	mov	r2, #100	@ tmp176,
	movw	r1, #:lower16:78836	@ tmp173,
	movt	r1, #:upper16:78836	@ tmp173,
	mul	r3, r2, r0	@ tmp175, tmp176, prephitmp.589
	str	r0, [r4, r1]	@ prephitmp.589, <variable>.CodecInfo.RealFrmRate
	movw	r1, #:lower16:78836	@ tmp174,
	movt	r1, #:upper16:78836	@ tmp174,
	add	ip, r3, #1020	@ tmp178, tmp175,
	cmp	r3, #0	@ tmp175,
	add	r2, ip, #3	@ tmp178, tmp178,
	movlt	r3, r2	@ tmp177, tmp178
	mov	r0, r3, asr #10	@ tmp180, tmp177,
	str	r0, [r4, r1]	@ tmp180, <variable>.CodecInfo.RealFrmRate
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L11:
	movw	r3, #:lower16:78836	@ tmp181,
	movt	r3, #:upper16:78836	@ tmp181,
	mov	r0, #0	@ tmp182,
	str	r0, [r4, r3]	@ tmp182, <variable>.CodecInfo.RealFrmRate
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	MP2_CalcRealEncFrameRate, .-MP2_CalcRealEncFrameRate
	.align	2
	.global	MP2_CalcDar
	.type	MP2_CalcDar, %function
MP2_CalcDar:
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
	movw	r3, #:lower16:79992	@ tmp138,
	movt	r3, #:upper16:79992	@ tmp138,
	ldr	ip, [r0, r3]	@ <variable>.pSyntaxInfNew, <variable>.pSyntaxInfNew
	ldr	r1, [ip, #84]	@ <variable>.aspect_ratio_information, <variable>.aspect_ratio_information
	sub	r3, r1, #1	@ D.41090, <variable>.aspect_ratio_information,
	cmp	r3, #2	@ D.41090,
	movwls	r2, #:lower16:.LANCHOR0	@ tmp140,
	movtls	r2, #:upper16:.LANCHOR0	@ tmp140,
	addls	r3, r2, r3, asl #2	@, tmp143, tmp140, D.41090,
	movhi	r0, #0	@ prephitmp.614,
	ldrls	r0, [r3, #128]	@ prephitmp.614, CSWTCH.528
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	MP2_CalcDar, .-MP2_CalcDar
	.align	2
	.global	MP2_SearchStartCode
	.type	MP2_SearchStartCode, %function
MP2_SearchStartCode:
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
	cmp	r1, #4	@ CodeLen,
	movle	r0, #0	@ ofst,
	ldmlefd	sp, {fp, sp, pc}	@
	add	ip, r0, r1	@ pEnd, pCode, CodeLen
	add	r3, r0, #2	@ ptr, pCode,
.L33:
	cmp	ip, r3	@ pEnd, ptr
	bls	.L22	@,
.L34:
	ldrb	r2, [r3, #0]	@ zero_extendqisi2	@ byte,* ptr
	cmp	r2, #1	@ byte,
	bls	.L23	@,
.L28:
	add	r3, r3, #3	@ ptr, ptr,
	cmp	ip, r3	@ pEnd, ptr
	bhi	.L34	@,
.L22:
	sub	r0, r1, #3	@ ofst, CodeLen,
	ldmfd	sp, {fp, sp, pc}	@
.L23:
	cmp	r2, #0	@ byte,
	beq	.L35	@,
	ldrb	r2, [r3, #-2]	@ zero_extendqisi2	@ tmp142,
	cmp	r2, #0	@ tmp142,
	bne	.L28	@,
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2	@ tmp143,
	cmp	r2, #0	@ tmp143,
	bne	.L28	@,
	movw	ip, #:lower16:-2	@ tmp144,
	movt	ip, #:upper16:-2	@ tmp144,
	rsb	r1, r0, ip	@ tmp144, pCode, tmp144
	add	r0, r1, r3	@ ofst, tmp144, ptr
	ldmfd	sp, {fp, sp, pc}	@
.L35:
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2	@ tmp140,
	cmp	r2, #0	@ tmp140,
	addeq	r3, r3, #1	@ ptr, ptr,
	beq	.L33	@,
	ldrb	r2, [r3, #1]	@ zero_extendqisi2	@ tmp141,
	cmp	r2, #0	@ tmp141,
	addeq	r3, r3, #2	@ ptr, ptr,
	addne	r3, r3, #4	@ ptr, ptr,
	b	.L33	@
	.fnend
	.size	MP2_SearchStartCode, .-MP2_SearchStartCode
	.align	2
	.global	MP2_RecordVFMWState
	.type	MP2_RecordVFMWState, %function
MP2_RecordVFMWState:
	.fnstart
.LFB1544:
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
	movw	r5, #:lower16:79992	@ tmp141,
	movt	r5, #:upper16:79992	@ tmp141,
	ldr	r2, [r0, #0]	@ D.39770, <variable>.pstExtraData
	ldr	r1, [r0, r5]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	ldr	r4, [r1, #48]	@ <variable>.horizontal_size, <variable>.horizontal_size
	str	r4, [r2, #568]	@ <variable>.horizontal_size, <variable>.stChanState.image_width
	ldr	r6, [r1, #52]	@ <variable>.vertical_size, <variable>.vertical_size
	str	r6, [r2, #572]	@ <variable>.vertical_size, <variable>.stChanState.image_height
	ldr	r3, [r0, r5]	@ <variable>.pSyntaxInfNew, <variable>.pSyntaxInfNew
	movw	r5, #:lower16:78704	@ tmp156,
	movt	r5, #:upper16:78704	@ tmp156,
	ldr	ip, [r3, #84]	@ <variable>.aspect_ratio_information, <variable>.aspect_ratio_information
	movw	r3, #:lower16:113652	@ tmp161,
	movt	r3, #:upper16:113652	@ tmp161,
	sub	r4, ip, #1	@ D.41101, <variable>.aspect_ratio_information,
	mov	ip, #0	@ tmp152,
	cmp	r4, #2	@ D.41101,
	str	ip, [r2, #580]	@ tmp152, <variable>.stChanState.scan_type
	str	ip, [r2, #584]	@ tmp152, <variable>.stChanState.video_format
	movwls	r6, #:lower16:.LANCHOR0	@ tmp147,
	movtls	r6, #:upper16:.LANCHOR0	@ tmp147,
	addls	r4, r6, r4, asl #2	@, tmp150, tmp147, D.41101,
	movhi	r4, #0	@ prephitmp.664,
	ldrls	r4, [r4, #128]	@ prephitmp.664, CSWTCH.528
	str	r4, [r2, #576]	@ prephitmp.664, <variable>.stChanState.aspect_ratio
	movw	r4, #:lower16:113656	@ tmp164,
	ldr	r6, [r1, #72]	@ <variable>.frame_rate, <variable>.frame_rate
	movt	r4, #:upper16:113656	@ tmp164,
	str	ip, [r2, #592]	@ tmp152, <variable>.stChanState.bit_rate
	str	r6, [r2, #588]	@ <variable>.frame_rate, <variable>.stChanState.frame_rate
	ldr	r5, [r0, r5]	@ <variable>.CodecInfo.MpegFlag, <variable>.CodecInfo.MpegFlag
	cmp	r5, #1	@ <variable>.CodecInfo.MpegFlag,
	movne	r5, #0	@, tmp158
	moveq	r5, #1	@, tmp158
	str	r5, [r2, #596]	@ tmp158, <variable>.stChanState.sub_video_standard
	ldr	r5, [r1, #40]	@ <variable>.profile, <variable>.profile
	str	r5, [r2, #600]	@ <variable>.profile, <variable>.stChanState.profile
	ldr	r1, [r1, #44]	@ <variable>.level, <variable>.level
	str	r1, [r2, #604]	@ <variable>.level, <variable>.stChanState.level
	ldr	r1, [r0, r3]	@ <variable>.numTotalFrame, <variable>.numTotalFrame
	str	r1, [r2, #608]	@ <variable>.numTotalFrame, <variable>.stChanState.total_frame_num
	ldr	r1, [r0, r4]	@ D.39781, <variable>.numOutputFrame
	ldr	r3, [r0, r3]	@ temp.675, <variable>.numTotalFrame
	cmp	r3, r1	@ temp.675, D.39781
	rsbge	ip, r1, r3	@ iftmp.485, D.39781, temp.675
	str	ip, [r2, #612]	@ iftmp.485, <variable>.stChanState.error_frame_num
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	MP2_RecordVFMWState, .-MP2_RecordVFMWState
	.align	2
	.global	MP2_OutputDispFrame
	.type	MP2_OutputDispFrame, %function
MP2_OutputDispFrame:
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
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	MP2_OutputDispFrame, .-MP2_OutputDispFrame
	.align	2
	.global	MP2_DecideAdjustQp
	.type	MP2_DecideAdjustQp, %function
MP2_DecideAdjustQp:
	.fnstart
.LFB1569:
	@ args = 8, pretend = 0, frame = 0
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
	mov	r4, r0	@ PicWidth, PicWidth
	add	r0, r0, r0, asl #1	@, tmp144, PicWidth, PicWidth,
	mov	r5, r1	@ PicHeight, PicHeight
	ldr	r6, [fp, #8]	@ pCodecInfo, pCodecInfo
	mul	r1, r1, r0	@ tmp145, PicHeight, tmp144
	mul	r2, r2, r1	@ D.40740, FrmRate, tmp145
	cmp	r2, #2000	@ D.40740,
	movlt	r7, #1	@ AvgBpp1000,
	blt	.L46	@,
	movw	ip, #:lower16:274877907	@ tmp149,
	movt	ip, #:upper16:274877907	@ tmp149,
	mov	lr, r2, asr #31	@ tmp151, D.40740,
	mov	r0, r3	@, BitRate
	smull	r3, r2, ip, r2	@, tmp148, tmp149, D.40740
	rsb	r1, lr, r2, asr #7	@,, tmp151, tmp148,
	bl	__aeabi_idiv	@
	mov	r7, r0	@ AvgBpp1000,
.L46:
	movw	r1, #:lower16:g_DnrEnable	@ tmp155,
	movt	r1, #:upper16:g_DnrEnable	@ tmp155,
	ldr	r3, [r1, #0]	@ g_DnrEnable, g_DnrEnable
	cmp	r3, #0	@ g_DnrEnable,
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	cmp	r7, #39	@ AvgBpp1000,
	movw	r3, #33456	@ tmp157,
	movw	ip, #33452	@ tmp161,
	mov	r0, #36	@ tmp158,
	str	r0, [r6, r3]	@ tmp158, <variable>.AdjustQpDr
	movle	r0, #56	@ tmp160,
	movgt	r0, #40	@ tmp162,
	str	r0, [r6, ip]	@ tmp162, <variable>.AdjustQpDb
	ldr	r2, [fp, #4]	@ ByteSize, ByteSize
	mov	lr, #16000	@ tmp164,
	mov	r1, r4	@, PicWidth
	mul	r0, lr, r2	@, tmp164, ByteSize
	bl	__aeabi_idiv	@
	mov	r1, r5	@, PicHeight
	bl	__aeabi_idiv	@
	movw	r1, #:lower16:1431655766	@ tmp174,
	movt	r1, #:upper16:1431655766	@ tmp174,
	smull	r2, r3, r1, r0	@, tmp173, tmp174, tmp172
	sub	ip, r3, r0, asr #31	@ InstBpp1000, tmp173, tmp172,
	cmp	r7, ip, asl #2	@ AvgBpp1000, InstBpp1000,
	movle	r0, #0	@, tmp178
	movgt	r0, #1	@, tmp178
	cmp	ip, #11	@ InstBpp1000,
	movgt	r2, #0	@, tmp183
	andle	r2, r0, #1	@,, tmp183, tmp178
	cmp	r2, #0	@ tmp183,
	movwne	r2, #33452	@ tmp184,
	movne	r0, #80	@ tmp185,
	strne	r0, [r6, r2]	@ tmp185, <variable>.AdjustQpDb
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	MP2_DecideAdjustQp, .-MP2_DecideAdjustQp
	.align	2
	.global	MP2_ExitMb
	.type	MP2_ExitMb, %function
MP2_ExitMb:
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
	mov	r3, #0	@ tmp134,
	str	r3, [r0, #16]	@ tmp134, <variable>.FirstMbInSliceFlag
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	MP2_ExitMb, .-MP2_ExitMb
	.align	2
	.global	MP2_GetPacketState
	.type	MP2_GetPacketState, %function
MP2_GetPacketState:
	.fnstart
.LFB1581:
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
	mov	r3, #113664	@ tmp136,
	ldrb	r0, [r0, r3]	@ zero_extendqisi2	@ <variable>.IsWaitToDecFlag, <variable>.IsWaitToDecFlag
	cmp	r0, #1	@ <variable>.IsWaitToDecFlag,
	moveq	r0, #2	@,
	movne	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	MP2_GetPacketState, .-MP2_GetPacketState
	.align	2
	.global	MPEG2DEC_Destroy
	.type	MPEG2DEC_Destroy, %function
MPEG2DEC_Destroy:
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
	movw	r3, #:lower16:78676	@ tmp139,
	movt	r3, #:upper16:78676	@ tmp139,
	movw	r1, #:lower16:.LC0	@,
	movt	r1, #:upper16:.LC0	@,
	ldr	r2, [r0, r3]	@ <variable>.CodecInfo.Frame_Cnt, <variable>.CodecInfo.Frame_Cnt
	mov	r0, #2	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	MPEG2DEC_Destroy, .-MPEG2DEC_Destroy
	.align	2
	.global	MP2_SetVDMInf
	.type	MP2_SetVDMInf, %function
MP2_SetVDMInf:
	.fnstart
.LFB1543:
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
	movw	r1, #:lower16:78620	@ tmp144,
	movt	r1, #:upper16:78620	@ tmp144,
	mov	r4, r0	@ pCtx, pCtx
	add	r0, r0, #78848	@ pBs, pCtx,
	ldrsb	r3, [r4, r1]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	add	r0, r0, #64	@ pBs, pBs,
	cmp	r3, #1	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg,
	beq	.L63	@,
	movw	r5, #:lower16:78936	@ tmp168,
	movt	r5, #:upper16:78936	@ tmp168,
	movw	r7, #:lower16:78632	@ tmp169,
	movt	r7, #:upper16:78632	@ tmp169,
	ldr	r3, [r4, r5]	@ temp.814, <variable>.Bs.TotalPos
	movw	r2, #:lower16:78616	@ tmp173,
	ldr	r1, [r4, r7]	@ <variable>.CodecInfo.stMp2Packet.BsPhyAddr, <variable>.CodecInfo.stMp2Packet.BsPhyAddr
	movt	r2, #:upper16:78616	@ tmp173,
	cmp	r3, #0	@ temp.814,
	add	r7, r3, #7	@ tmp176, temp.814,
	ldr	lr, [r4, r2]	@ <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.BsOffset
	add	ip, r1, r3, lsr #3	@, tmp185, <variable>.CodecInfo.stMp2Packet.BsPhyAddr, temp.814,
	movge	r7, r3	@ temp.814, temp.814
	movw	r5, #:lower16:78636	@ tmp166,
	add	r3, r3, r1, asl #3	@, bs_offset.819, temp.814, <variable>.CodecInfo.stMp2Packet.BsPhyAddr,
	movt	r5, #:upper16:78636	@ tmp166,
	add	r1, lr, r7, asr #3	@, tmp180, <variable>.CodecInfo.BsOffset, temp.814,
	and	lr, r3, #31	@ tmp188, bs_offset.819,
	str	r1, [r4, r2]	@ tmp180, <variable>.CodecInfo.BsOffset
	bic	r1, ip, #3	@ tmp187, tmp185,
	str	lr, [r4, #172]	@ tmp188, <variable>.Mp2DecParam.StreamBitOffset
	str	r1, [r4, #164]	@ tmp187, <variable>.Mp2DecParam.StreamPhyAddr
	ldr	r6, [r4, r5]	@ <variable>.CodecInfo.stMp2Packet.BsPhyAddr, <variable>.CodecInfo.stMp2Packet.BsPhyAddr
	bl	BsResidBits	@
	movw	r3, #:lower16:78644	@ tmp193,
	movt	r3, #:upper16:78644	@ tmp193,
	ldr	r2, [r4, r5]	@ <variable>.CodecInfo.stMp2Packet.BsPhyAddr, <variable>.CodecInfo.stMp2Packet.BsPhyAddr
	bic	r6, r6, #3	@ stream_base_addr.813, <variable>.CodecInfo.stMp2Packet.BsPhyAddr,
	ldr	r3, [r4, r3]	@ <variable>.CodecInfo.stMp2Packet.BsLength, <variable>.CodecInfo.stMp2Packet.BsLength
	and	ip, r2, #3	@ tmp190, <variable>.CodecInfo.stMp2Packet.BsPhyAddr,
	str	r6, [r4, #168]	@ stream_base_addr.813, <variable>.Mp2DecParam.StreamPhyAddr
	mov	r1, ip, asl #3	@ tmp192, tmp190,
	mov	r2, r3, asl #3	@ tmp195, <variable>.CodecInfo.stMp2Packet.BsLength,
	str	r1, [r4, #176]	@ tmp192, <variable>.Mp2DecParam.StreamBitOffset
	str	r2, [r4, #184]	@ tmp195, <variable>.Mp2DecParam.StreamLength
	str	r0, [r4, #180]	@, <variable>.Mp2DecParam.StreamLength
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L63:
	movw	ip, #:lower16:78936	@ tmp147,
	movt	ip, #:upper16:78936	@ tmp147,
	movw	r5, #:lower16:78632	@ tmp146,
	movt	r5, #:upper16:78632	@ tmp146,
	ldr	r3, [r4, ip]	@ D.39745, <variable>.Bs.TotalPos
	movw	r2, #:lower16:78616	@ tmp148,
	ldr	r1, [r4, r5]	@ D.39744, <variable>.CodecInfo.stMp2Packet.BsPhyAddr
	movt	r2, #:upper16:78616	@ tmp148,
	cmp	r3, #0	@ D.39745,
	add	r5, r3, #7	@ tmp151, D.39745,
	ldr	lr, [r4, r2]	@ <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.BsOffset
	add	ip, r3, r1, asl #3	@, tmp161, D.39745, D.39744,
	movge	r5, r3	@ D.39745, D.39745
	add	r3, r1, r3, lsr #3	@, tmp157, D.39744, D.39745,
	add	r1, lr, r5, asr #3	@, tmp155, <variable>.CodecInfo.BsOffset, D.39745,
	bic	r3, r3, #3	@ tmp158, tmp157,
	str	r1, [r4, r2]	@ tmp155, <variable>.CodecInfo.BsOffset
	and	lr, ip, #31	@ tmp162, tmp161,
	str	r3, [r4, #164]	@ tmp158, <variable>.Mp2DecParam.StreamPhyAddr
	str	lr, [r4, #172]	@ tmp162, <variable>.Mp2DecParam.StreamBitOffset
	bl	BsResidBits	@
	mov	r2, #0	@ tmp163,
	str	r2, [r4, #184]	@ tmp163, <variable>.Mp2DecParam.StreamLength
	str	r2, [r4, #168]	@ tmp163, <variable>.Mp2DecParam.StreamPhyAddr
	str	r2, [r4, #176]	@ tmp163, <variable>.Mp2DecParam.StreamBitOffset
	str	r0, [r4, #180]	@, <variable>.Mp2DecParam.StreamLength
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	MP2_SetVDMInf, .-MP2_SetVDMInf
	.align	2
	.global	MP2_DecNewPic
	.type	MP2_DecNewPic, %function
MP2_DecNewPic:
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
	mov	r5, r0	@ pCtx, pCtx
	bl	MP2_SetVDMInf	@
	ldr	r2, [r5, #0]	@ temp.857, <variable>.pstExtraData
	movw	r0, #:lower16:79992	@ tmp146,
	movt	r0, #:upper16:79992	@ tmp146,
	movw	r3, #45324	@ tmp143,
	ldr	r1, [r5, r0]	@ D.39371, <variable>.pSyntaxInfNew
	ldr	r0, [r2, #684]	@ <variable>.s32Compress_en, <variable>.s32Compress_en
	str	r0, [r5, r3]	@ <variable>.s32Compress_en, <variable>.Mp2DecParam.Compress_en
	ldrb	r3, [r1, #22]	@ zero_extendqisi2	@ D.39372, <variable>.picture_coding_type
	cmp	r3, #3	@ D.39372,
	beq	.L73	@,
	cmp	r3, #2	@ D.39372,
	movweq	r3, #:lower16:113660	@ tmp156,
	movteq	r3, #:upper16:113660	@ tmp156,
	moveq	r1, #1	@ tmp157,
	streq	r1, [r5, r3]	@ tmp157, <variable>.PPicFound
.L66:
	add	r1, r5, #8	@ D.39386, pCtx,
	str	r1, [r5, #4]	@ D.39386, <variable>.pMp2DecParam
	ldr	r3, [r2, #876]	@ D.39387, <variable>.stDisParams.s32Mode
	cmp	r3, #1	@ D.39387,
	beq	.L74	@,
	cmp	r3, #2	@ D.39387,
	beq	.L75	@,
.L70:
	movw	r3, #:lower16:79992	@ tmp174,
	movt	r3, #:upper16:79992	@ tmp174,
	movw	r0, #:lower16:78668	@ tmp169,
	movt	r0, #:upper16:78668	@ tmp169,
	ldr	r2, [r5, r3]	@ <variable>.pSyntaxInfNew, <variable>.pSyntaxInfNew
	ldr	lr, [r5, r0]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	bic	r4, lr, #16252928	@ tmp172, <variable>.CodecInfo.StreamIntegrality,
	str	r4, [r5, r0]	@ tmp172, <variable>.CodecInfo.StreamIntegrality
	ldrb	r4, [r2, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	cmp	r4, #1	@ <variable>.picture_coding_type,
	beq	.L76	@,
.L71:
	mov	r0, #1	@ Ret,
.L68:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L76:
	movw	r1, #:lower16:g_event_report	@ tmp176,
	movt	r1, #:upper16:g_event_report	@ tmp176,
	ldr	ip, [r1, #0]	@ g_event_report.472, g_event_report
	cmp	ip, #0	@ g_event_report.472,
	beq	.L71	@,
	ldr	r0, [r5, #180]	@ <variable>.Mp2DecParam.StreamLength, <variable>.Mp2DecParam.StreamLength
	movw	r3, #:lower16:113648	@ tmp183,
	ldr	lr, [r5, #184]	@ <variable>.Mp2DecParam.StreamLength, <variable>.Mp2DecParam.StreamLength
	movt	r3, #:upper16:113648	@ tmp183,
	sub	r2, fp, #20	@ tmp185,,
	mov	r1, #20	@,
	add	lr, lr, r0	@ tmp177, <variable>.Mp2DecParam.StreamLength, <variable>.Mp2DecParam.StreamLength
	ldr	r0, [r5, r3]	@, <variable>.ChanID
	cmp	lr, #0	@ tmp177,
	add	r5, lr, #7	@ tmp181, tmp177,
	mov	r3, #4	@,
	movlt	lr, r5	@ tmp180, tmp181
	mov	lr, lr, asr #3	@ tmp182, tmp180,
	str	lr, [r2, #-4]!	@ tmp182, para
	blx	ip	@ g_event_report.472
	mov	r0, r4	@ Ret, <variable>.picture_coding_type
	b	.L68	@
.L73:
	movw	ip, #:lower16:113660	@ tmp147,
	movt	ip, #:upper16:113660	@ tmp147,
	ldr	r0, [r5, ip]	@ <variable>.PPicFound, <variable>.PPicFound
	cmp	r0, #0	@ <variable>.PPicFound,
	bne	.L66	@,
	movw	r3, #:lower16:78708	@ tmp149,
	movt	r3, #:upper16:78708	@ tmp149,
	ldr	lr, [r5, r3]	@ <variable>.CodecInfo.RefNum, <variable>.CodecInfo.RefNum
	cmp	lr, #2	@ <variable>.CodecInfo.RefNum,
	beq	.L66	@,
	ldrb	r2, [r1, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	cmp	r2, #3	@ <variable>.picture_structure,
	beq	.L68	@,
	movw	ip, #:lower16:78680	@ tmp152,
	movt	ip, #:upper16:78680	@ tmp152,
	ldr	lr, [r5, ip]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	rsbs	r1, lr, #1	@ tmp155, <variable>.CodecInfo.Second_Field
	movcc	r1, #0	@ tmp155
	str	r1, [r5, ip]	@ tmp155, <variable>.CodecInfo.Second_Field
	b	.L68	@
.L74:
	cmp	r1, #0	@ D.39386,
	beq	.L70	@,
	movw	r1, #:lower16:79992	@ tmp159,
	movt	r1, #:upper16:79992	@ tmp159,
	ldr	r2, [r5, r1]	@ <variable>.pSyntaxInfNew, <variable>.pSyntaxInfNew
	ldrb	r3, [r2, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	cmp	r3, #3	@ <variable>.picture_coding_type,
	moveq	r0, #0	@ tmp161,
	streq	r0, [r5, #4]	@ tmp161, <variable>.pMp2DecParam
	bne	.L70	@,
	b	.L68	@
.L75:
	ldr	r0, [r2, #880]	@ <variable>.stDisParams.s32DisNums, <variable>.stDisParams.s32DisNums
	cmp	r0, #0	@ <variable>.stDisParams.s32DisNums,
	ble	.L70	@,
	cmp	r1, #0	@ D.39386,
	beq	.L70	@,
	movw	r3, #:lower16:79992	@ tmp164,
	movt	r3, #:upper16:79992	@ tmp164,
	ldr	lr, [r5, r3]	@ <variable>.pSyntaxInfNew, <variable>.pSyntaxInfNew
	ldrb	ip, [lr, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	cmp	ip, #3	@ <variable>.picture_coding_type,
	bne	.L70	@,
	mov	r0, #0	@ tmp166,
	str	r0, [r5, #4]	@ tmp166, <variable>.pMp2DecParam
	ldr	ip, [r2, #880]	@ <variable>.stDisParams.s32DisNums, <variable>.stDisParams.s32DisNums
	sub	r1, ip, #1	@ tmp168, <variable>.stDisParams.s32DisNums,
	str	r1, [r2, #880]	@ tmp168, <variable>.stDisParams.s32DisNums
	b	.L68	@
	.fnend
	.size	MP2_DecNewPic, .-MP2_DecNewPic
	.align	2
	.global	MP2_u_v
	.type	MP2_u_v, %function
MP2_u_v:
	.fnstart
.LFB1576:
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
	mov	r7, r2	@ SeTraceString, SeTraceString
	mov	r6, r0	@ pBs, pBs
	mov	r5, r1	@ LenInBits, LenInBits
	bl	BsShow	@
	mov	r1, r5	@, LenInBits
	mov	r4, r0	@ D.40919,
	mov	r0, r6	@, pBs
	bl	BsSkip	@
	mov	r2, r7	@, SeTraceString
	mov	r3, r4	@, D.40919
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC1	@,
	movt	r1, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, D.40919
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	MP2_u_v, .-MP2_u_v
	.align	2
	.global	MP2_MbAddrInc
	.type	MP2_MbAddrInc, %function
MP2_MbAddrInc:
	.fnstart
.LFB1580:
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
	mov	r1, #4	@,
	mov	r6, r0	@ pBs, pBs
	bl	BsShow	@
	movw	r4, #:lower16:.LANCHOR0	@ tmp144,
	movt	r4, #:upper16:.LANCHOR0	@ tmp144,
	add	r3, r4, r0, asl #3	@, tmp147, tmp144, D.41020,
	ldr	r5, [r3, #140]	@ MbAddrInc, tab_for_first_4bit
	ldr	r1, [r3, #144]	@ SkipBit, tab_for_first_4bit
	cmp	r5, #6	@ MbAddrInc,
	bls	.L84	@,
	cmp	r5, #9	@ MbAddrInc,
	beq	.L85	@,
	mov	r1, #11	@,
	mov	r0, r6	@, pBs
	bl	BsShow	@
	movw	r2, #:lower16:.LC2	@,
	movt	r2, #:upper16:.LC2	@,
	and	ip, r0, #127	@ code.914,,
	mov	r0, r6	@, pBs
	sub	r5, ip, #24	@ code.915, code.914,
	add	r1, r4, r5, asl #3	@, tmp167, tmp144, code.915,
	mov	r4, r1	@ tmp161, tmp167
	ldr	r1, [r1, #272]	@, tab_for_last_7bit
	ldr	r5, [r4, #268]	@ MbAddrInc, tab_for_last_7bit
	bl	MP2_u_v	@
	mov	r0, r5	@, MbAddrInc
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L84:
	mov	r0, r6	@, pBs
	movw	r2, #:lower16:.LC2	@,
	movt	r2, #:upper16:.LC2	@,
	bl	MP2_u_v	@
	mov	r0, r5	@, MbAddrInc
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L85:
	mov	r0, r6	@, pBs
	movw	r2, #:lower16:.LC2	@,
	movt	r2, #:upper16:.LC2	@,
	bl	MP2_u_v	@
	rsb	r5, r0, #9	@ MbAddrInc,,
	mov	r0, r5	@, MbAddrInc
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	MP2_MbAddrInc, .-MP2_MbAddrInc
	.align	2
	.global	MP2_InitMb
	.type	MP2_InitMb, %function
MP2_InitMb:
	.fnstart
.LFB1577:
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
	mov	r5, #0	@ macroblock_escape,
	mov	r6, r0	@ pSlcInfo, pSlcInfo
	ldr	r4, [r0, #52]	@ pBs, <variable>.pBs
	b	.L87	@
.L91:
	cmp	r0, #15	@ D.40943,
	beq	.L88	@,
	cmp	r0, #8	@ D.40943,
	add	r5, r5, #33	@ macroblock_escape, macroblock_escape,
	bne	.L97	@,
.L88:
	movw	r2, #:lower16:.LC4	@,
	mov	r0, r4	@, pBs
	movt	r2, #:upper16:.LC4	@,
	mov	r1, #11	@,
	bl	MP2_u_v	@
.L87:
	mov	r1, #11	@,
	mov	r0, r4	@, pBs
	bl	BsShow	@
	cmp	r0, #23	@ D.40943,
	bls	.L91	@,
	mov	r0, r4	@, pBs
	bl	MP2_MbAddrInc	@
	ldr	r4, [r6, #16]	@ <variable>.FirstMbInSliceFlag, <variable>.FirstMbInSliceFlag
	cmp	r4, #0	@ <variable>.FirstMbInSliceFlag,
	beq	.L92	@,
	ldr	r1, [r6, #28]	@ D.40948, <variable>.previous_macroblock_address
	add	r2, r5, r0	@ tmp147, macroblock_escape, macroblock_address_increment
	ldr	r3, [r6, #12]	@ <variable>.pic_total_mb_num, <variable>.pic_total_mb_num
	cmp	r1, #0	@ D.40948,
	addne	r2, r2, r1	@ SlcStartMbNum, tmp147, D.40948
	subeq	r2, r2, #1	@ SlcStartMbNum, tmp148,
	sub	r3, r3, #1	@ D.40956, <variable>.pic_total_mb_num,
	str	r2, [r6, #44]	@ SlcStartMbNum, <variable>.slicen_start_mb_num
	cmp	r2, r3	@ SlcStartMbNum, D.40956
	movls	r0, #1	@ ret,
	ldmlsfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC5	@,
	movt	r1, #:upper16:.LC5	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ ret,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L97:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC3	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ ret,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L92:
	mov	r2, r4	@, <variable>.FirstMbInSliceFlag
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC6	@,
	movt	r1, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ ret, <variable>.FirstMbInSliceFlag
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	MP2_InitMb, .-MP2_InitMb
	.align	2
	.global	MP2_DecSliceHeader
	.type	MP2_DecSliceHeader, %function
MP2_DecSliceHeader:
	.fnstart
.LFB1575:
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
	mov	r5, r0	@ pSlcInfo, pSlcInfo
	ldr	r0, [r0, #4]	@ <variable>.pic_height_in_mb, <variable>.pic_height_in_mb
	mov	r2, #1	@ tmp145,
	mov	r3, #0	@ tmp146,
	str	r2, [r5, #16]	@ tmp145, <variable>.FirstMbInSliceFlag
	cmp	r0, #175	@ <variable>.pic_height_in_mb,
	str	r3, [r5, #24]	@ tmp146, <variable>.slice_vertical_position_extension
	ldr	r4, [r5, #52]	@ pBs, <variable>.pBs
	bls	.L99	@,
	ldr	r1, [r5, #0]	@ <variable>.mpeg1_flag, <variable>.mpeg1_flag
	cmp	r1, #0	@ <variable>.mpeg1_flag,
	beq	.L108	@,
.L99:
	mov	r1, #0	@ prephitmp.955,
.L100:
	ldr	ip, [r5, #20]	@ <variable>.slice_vertical_position, <variable>.slice_vertical_position
	ldr	r0, [r5, #8]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	sub	r2, ip, #1	@ tmp150, <variable>.slice_vertical_position,
	add	r3, r2, r1	@ tmp152, tmp150, prephitmp.955
	mov	r1, #5	@,
	movw	r2, #:lower16:.LC8	@,
	movt	r2, #:upper16:.LC8	@,
	mul	lr, r0, r3	@ D.40893, <variable>.pic_width_in_mb, tmp152
	mov	r0, r4	@, pBs
	cmp	lr, #0	@ D.40893,
	subne	lr, lr, #1	@ iftmp.521, D.40893,
	str	lr, [r5, #28]	@ iftmp.521, <variable>.previous_macroblock_address
	bl	MP2_u_v	@
	mov	ip, #0	@ tmp155,
	mov	r1, #1	@,
	str	ip, [r5, #32]	@ tmp155, <variable>.intra_slice
	str	r0, [r5, #48]	@, <variable>.quantiser_scale_code
	mov	r0, r4	@, pBs
	bl	BsShow	@
	cmp	r0, #0	@,
	bne	.L109	@,
.L103:
	mov	r0, r4	@, pBs
	mov	r1, #1	@,
	movw	r2, #:lower16:.LC12	@,
	movt	r2, #:upper16:.LC12	@,
	bl	MP2_u_v	@
	mov	r0, #0	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L109:
	mov	r0, r4	@, pBs
	mov	r1, #1	@,
	movw	r2, #:lower16:.LC9	@,
	movt	r2, #:upper16:.LC9	@,
	bl	MP2_u_v	@
	mov	r0, r4	@, pBs
	mov	r1, #1	@,
	movw	r2, #:lower16:.LC10	@,
	movt	r2, #:upper16:.LC10	@,
	bl	MP2_u_v	@
	mov	r1, #7	@,
	movw	r2, #:lower16:.LC11	@,
	movt	r2, #:upper16:.LC11	@,
	str	r0, [r5, #32]	@, <variable>.intra_slice
	mov	r0, r4	@, pBs
	bl	MP2_u_v	@
	b	.L104	@
.L105:
	bl	MP2_u_v	@
	movw	r2, #:lower16:.LC13	@,
	mov	r0, r4	@, pBs
	movt	r2, #:upper16:.LC13	@,
	mov	r1, #8	@,
	bl	MP2_u_v	@
.L104:
	mov	r1, #1	@,
	mov	r0, r4	@, pBs
	bl	BsShow	@
	movw	r2, #:lower16:.LC12	@,
	mov	r1, #1	@,
	movt	r2, #:upper16:.LC12	@,
	cmp	r0, #0	@,
	mov	r0, r4	@, pBs
	bne	.L105	@,
	b	.L103	@
.L108:
	mov	r1, #3	@,
	mov	r0, r4	@, pBs
	movw	r2, #:lower16:.LC7	@,
	movt	r2, #:upper16:.LC7	@,
	bl	MP2_u_v	@
	mov	r1, r0, asl #7	@ prephitmp.955, D.40887,
	str	r0, [r5, #24]	@ D.40887, <variable>.slice_vertical_position_extension
	b	.L100	@
	.fnend
	.size	MP2_DecSliceHeader, .-MP2_DecSliceHeader
	.align	2
	.global	MP2_GetFirstMbInSlice
	.type	MP2_GetFirstMbInSlice, %function
MP2_GetFirstMbInSlice:
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
	mov	r4, r0	@ pSlcInfo, pSlcInfo
	bl	MP2_DecSliceHeader	@
	mov	r0, r4	@, pSlcInfo
	bl	MP2_InitMb	@
	mov	r3, #0	@ tmp136,
	str	r3, [r4, #16]	@ tmp136, <variable>.FirstMbInSliceFlag
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	MP2_GetFirstMbInSlice, .-MP2_GetFirstMbInSlice
	.align	2
	.global	copyright_extension
	.type	copyright_extension, %function
copyright_extension:
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
	add	r0, r0, #78848	@, pCtx,
	mov	r1, #32	@,
	add	r0, r0, #64	@,,
	bl	BsSkip	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	copyright_extension, .-copyright_extension
	.align	2
	.global	picture_temporal_scalable_extension
	.type	picture_temporal_scalable_extension, %function
picture_temporal_scalable_extension:
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
	add	r0, r0, #78848	@, pCtx,
	mov	r1, #32	@,
	add	r0, r0, #64	@,,
	bl	BsSkip	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	picture_temporal_scalable_extension, .-picture_temporal_scalable_extension
	.align	2
	.global	picture_spatial_scalable_extension
	.type	picture_spatial_scalable_extension, %function
picture_spatial_scalable_extension:
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
	add	r0, r0, #78848	@, pCtx,
	mov	r1, #32	@,
	add	r0, r0, #64	@,,
	bl	BsSkip	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	picture_spatial_scalable_extension, .-picture_spatial_scalable_extension
	.align	2
	.global	sequence_scalable_extension
	.type	sequence_scalable_extension, %function
sequence_scalable_extension:
	.fnstart
.LFB1553:
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
	add	r0, r0, #78848	@, pCtx,
	mov	r1, #32	@,
	add	r0, r0, #64	@,,
	bl	BsSkip	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	sequence_scalable_extension, .-sequence_scalable_extension
	.align	2
	.global	MP2_ClearCurPic
	.type	MP2_ClearCurPic, %function
MP2_ClearCurPic:
	.fnstart
.LFB1572:
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
	movw	r8, #45316	@ tmp166,
	ldr	r3, [r0, r8]	@ <variable>.Mp2DecParam.SlcNum, <variable>.Mp2DecParam.SlcNum
	mov	r6, r0	@ pCtx, pCtx
	cmp	r3, #0	@ <variable>.Mp2DecParam.SlcNum,
	beq	.L121	@,
	movw	r7, #:lower16:113648	@ tmp181,
	mov	r4, r0	@ ivtmp.1111, pCtx
	movt	r7, #:upper16:113648	@ tmp181,
	mov	r5, #0	@ i,
	b	.L123	@
.L122:
	ldr	r2, [r6, r8]	@ <variable>.Mp2DecParam.SlcNum, <variable>.Mp2DecParam.SlcNum
	add	r4, r4, #44	@ ivtmp.1111, ivtmp.1111,
	cmp	r2, r5	@ <variable>.Mp2DecParam.SlcNum, i
	bls	.L121	@,
.L123:
	ldr	r1, [r4, #284]	@, <variable>.BsID
	add	r5, r5, #1	@ i, i,
	ldr	r0, [r6, r7]	@, <variable>.ChanID
	bl	SM_ReleaseStreamSeg	@
	ldr	r0, [r4, #264]	@ <variable>.BsPhyAddr, <variable>.BsPhyAddr
	cmp	r0, #0	@ <variable>.BsPhyAddr,
	beq	.L122	@,
	ldr	r1, [r4, #272]	@ <variable>.BsLenInBit, <variable>.BsLenInBit
	cmp	r1, #0	@ <variable>.BsLenInBit,
	beq	.L122	@,
	ldr	r1, [r4, #288]	@, <variable>.BsID
	add	r4, r4, #44	@ ivtmp.1111, ivtmp.1111,
	ldr	r0, [r6, r7]	@, <variable>.ChanID
	bl	SM_ReleaseStreamSeg	@
	ldr	r2, [r6, r8]	@ <variable>.Mp2DecParam.SlcNum, <variable>.Mp2DecParam.SlcNum
	cmp	r2, r5	@ <variable>.Mp2DecParam.SlcNum, i
	bhi	.L123	@,
.L121:
	movw	r3, #45316	@ tmp178,
	mov	ip, #0	@ tmp179,
	str	ip, [r6, r3]	@ tmp179, <variable>.Mp2DecParam.SlcNum
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	.fnend
	.size	MP2_ClearCurPic, .-MP2_ClearCurPic
	.align	2
	.global	MP2_WriteSliceInfo
	.type	MP2_WriteSliceInfo, %function
MP2_WriteSliceInfo:
	.fnstart
.LFB1579:
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
	movw	r1, #45316	@ tmp141,
	mov	r4, r0	@ pCtx, pCtx
	ldr	r0, [r0, r1]	@ D.40976, <variable>.Mp2DecParam.SlcNum
	mov	r5, #44	@ tmp144,
	movw	r3, #:lower16:78888	@ tmp147,
	movt	r3, #:upper16:78888	@ tmp147,
	movw	r2, #:lower16:78904	@ tmp154,
	mla	r5, r5, r0, r4	@ tmp145, tmp144, D.40976, pCtx
	ldr	ip, [r4, r3]	@ <variable>.SliceInfo.intra_slice, <variable>.SliceInfo.intra_slice
	movt	r2, #:upper16:78904	@ tmp154,
	movw	lr, #:lower16:78900	@ tmp161,
	movt	lr, #:upper16:78900	@ tmp161,
	add	r0, r5, #288	@ tmp146, tmp145,
	str	ip, [r0, #8]	@ <variable>.SliceInfo.intra_slice, <variable>.intra_slice
	ldr	r2, [r4, r2]	@ <variable>.SliceInfo.quantiser_scale_code, <variable>.SliceInfo.quantiser_scale_code
	str	r2, [r5, #300]	@ <variable>.SliceInfo.quantiser_scale_code, <variable>.quantiser_scale_code
	ldr	r3, [r4, lr]	@ <variable>.SliceInfo.slicen_start_mb_num, <variable>.SliceInfo.slicen_start_mb_num
	str	r3, [r0, #4]	@ <variable>.SliceInfo.slicen_start_mb_num, <variable>.slice_start_mbn
	ldr	r2, [r4, r1]	@ temp.1142, <variable>.Mp2DecParam.SlcNum
	cmp	r2, #1024	@ temp.1142,
	bcs	.L133	@,
	movw	r3, #:lower16:78936	@ tmp172,
	movt	r3, #:upper16:78936	@ tmp172,
	movw	r0, #:lower16:78632	@ tmp179,
	movt	r0, #:upper16:78632	@ tmp179,
	ldr	r1, [r4, r3]	@ D.40990, <variable>.Bs.TotalPos
	movw	r3, #:lower16:78648	@ tmp193,
	ldr	r2, [r4, r0]	@ <variable>.CodecInfo.stMp2Packet.BsPhyAddr, <variable>.CodecInfo.stMp2Packet.BsPhyAddr
	movt	r3, #:upper16:78648	@ tmp193,
	and	lr, r1, #7	@ tmp187, D.40990,
	str	lr, [r5, #276]	@ tmp187, <variable>.BsBitOffset
	add	ip, r2, r1, lsr #3	@, tmp181, <variable>.CodecInfo.stMp2Packet.BsPhyAddr, D.40990,
	str	ip, [r5, #260]	@ tmp181, <variable>.BsPhyAddr
	ldr	lr, [r4, r3]	@ <variable>.CodecInfo.stMp2Packet.StreamID, <variable>.CodecInfo.stMp2Packet.StreamID
	add	r0, r4, #78848	@, pCtx,
	add	r0, r0, #64	@,,
	str	lr, [r5, #284]	@ <variable>.CodecInfo.stMp2Packet.StreamID, <variable>.BsID
	bl	BsResidBits	@
	movw	r3, #:lower16:78620	@ tmp202,
	movt	r3, #:upper16:78620	@ tmp202,
	str	r0, [r5, #268]	@, <variable>.BsLenInBit
	ldrsh	r2, [r4, r3]	@ D.40995,
	cmp	r2, #1	@ D.40995,
	beq	.L134	@,
	cmp	r2, #256	@ D.40995,
	bne	.L131	@,
	movw	ip, #:lower16:78636	@ tmp234,
	movt	ip, #:upper16:78636	@ tmp234,
	add	r0, r5, #276	@ tmp240, tmp145,
	movw	lr, #:lower16:78652	@ tmp247,
	ldr	r1, [r4, ip]	@ <variable>.CodecInfo.stMp2Packet.BsPhyAddr, <variable>.CodecInfo.stMp2Packet.BsPhyAddr
	movt	lr, #:upper16:78652	@ tmp247,
	mov	r3, #0	@ tmp241,
	str	r3, [r0, #4]	@ tmp241, <variable>.BsBitOffset
	movw	ip, #:lower16:78644	@ tmp254,
	movt	ip, #:upper16:78644	@ tmp254,
	str	r1, [r5, #264]	@ <variable>.CodecInfo.stMp2Packet.BsPhyAddr, <variable>.BsPhyAddr
	movw	r1, #45316	@ tmp262,
	ldr	r2, [r4, lr]	@ <variable>.CodecInfo.stMp2Packet.StreamID, <variable>.CodecInfo.stMp2Packet.StreamID
	str	r2, [r5, #288]	@ <variable>.CodecInfo.stMp2Packet.StreamID, <variable>.BsID
	ldr	r3, [r4, ip]	@ <variable>.CodecInfo.stMp2Packet.BsLength, <variable>.CodecInfo.stMp2Packet.BsLength
	mov	r0, r3, asl #3	@ tmp256, <variable>.CodecInfo.stMp2Packet.BsLength,
	str	r0, [r5, #272]	@ tmp256, <variable>.BsLenInBit
	ldr	r3, [r4, r1]	@ <variable>.Mp2DecParam.SlcNum, <variable>.Mp2DecParam.SlcNum
	mov	r0, #1	@ D.40987,
	add	r2, r3, r0	@ tmp265, <variable>.Mp2DecParam.SlcNum,
	str	r2, [r4, r1]	@ tmp265, <variable>.Mp2DecParam.SlcNum
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L133:
	mov	r3, #1024	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC14	@,
	movt	r1, #:upper16:.LC14	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, pCtx
	bl	MP2_ClearCurPic	@
	movw	r3, #:lower16:78668	@ tmp166,
	movt	r3, #:upper16:78668	@ tmp166,
	movw	r2, #:lower16:78724	@ tmp170,
	movt	r2, #:upper16:78724	@ tmp170,
	mov	r1, #0	@ tmp171,
	ldr	ip, [r4, r3]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	mov	r0, r1	@ D.40987, tmp171
	str	r1, [r4, r2]	@ tmp171, <variable>.CodecInfo.HDRState
	bic	r1, ip, #5767168	@ tmp169, <variable>.CodecInfo.StreamIntegrality,
	str	r1, [r4, r3]	@ tmp169, <variable>.CodecInfo.StreamIntegrality
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L134:
	add	r1, r5, #260	@ tmp208, tmp145,
	add	lr, r5, #268	@ tmp226, tmp145,
	add	r2, r5, #276	@ tmp214, tmp145,
	add	r5, r5, #284	@ tmp220, tmp145,
	mov	ip, #0	@ tmp209,
	str	ip, [r1, #4]	@ tmp209, <variable>.BsPhyAddr
	movw	r1, #45316	@ tmp262,
	str	ip, [r2, #4]	@ tmp209, <variable>.BsBitOffset
	str	ip, [lr, #4]	@ tmp209, <variable>.BsLenInBit
	mov	r0, #1	@ D.40987,
	str	ip, [r5, #4]	@ tmp209, <variable>.BsID
	ldr	r3, [r4, r1]	@ <variable>.Mp2DecParam.SlcNum, <variable>.Mp2DecParam.SlcNum
	add	r2, r3, r0	@ tmp265, <variable>.Mp2DecParam.SlcNum,
	str	r2, [r4, r1]	@ tmp265, <variable>.Mp2DecParam.SlcNum
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L131:
	movw	lr, #:lower16:78621	@ tmp260,
	movt	lr, #:upper16:78621	@ tmp260,
	ldrsb	r2, [r4, r3]	@, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	mov	r0, #1	@,
	ldrsb	r3, [r4, lr]	@, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	movw	r1, #:lower16:.LC15	@,
	movt	r1, #:upper16:.LC15	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.40987,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	MP2_WriteSliceInfo, .-MP2_WriteSliceInfo
	.align	2
	.global	MP2_DecSlice
	.type	MP2_DecSlice, %function
MP2_DecSlice:
	.fnstart
.LFB1573:
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
	movw	r3, #:lower16:79992	@ tmp140,
	movw	lr, #:lower16:78624	@ tmp142,
	movt	r3, #:upper16:79992	@ tmp140,
	movt	lr, #:upper16:78624	@ tmp142,
	movw	r2, #:lower16:78640	@ tmp145,
	movt	r2, #:upper16:78640	@ tmp145,
	movw	r5, #:lower16:78704	@ tmp148,
	movt	r5, #:upper16:78704	@ tmp148,
	ldr	r3, [r0, r3]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	ldr	r6, [r0, lr]	@ <variable>.CodecInfo.stMp2Packet.BsVirAddr, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	mov	r4, r0	@ pCtx, pCtx
	ldr	r7, [r0, r2]	@ <variable>.CodecInfo.stMp2Packet.BsLength, <variable>.CodecInfo.stMp2Packet.BsLength
	movw	ip, #:lower16:78892	@ tmp141,
	ldr	lr, [r0, r5]	@ <variable>.CodecInfo.MpegFlag, <variable>.CodecInfo.MpegFlag
	movt	ip, #:upper16:78892	@ tmp141,
	movw	r0, #:lower16:78896	@ tmp144,
	movw	r2, #:lower16:78856	@ tmp147,
	movt	r0, #:upper16:78896	@ tmp144,
	movt	r2, #:upper16:78856	@ tmp147,
	str	r6, [r4, ip]	@ <variable>.CodecInfo.stMp2Packet.BsVirAddr, <variable>.SliceInfo.VirAddr
	cmp	lr, #1	@ <variable>.CodecInfo.MpegFlag,
	movne	r5, #0	@, tmp150
	moveq	r5, #1	@, tmp150
	str	r7, [r4, r0]	@ <variable>.CodecInfo.stMp2Packet.BsLength, <variable>.SliceInfo.ByteLen
	movw	r7, #:lower16:78860	@ tmp151,
	str	r5, [r4, r2]	@ tmp150, <variable>.SliceInfo.mpeg1_flag
	movt	r7, #:upper16:78860	@ tmp151,
	ldr	ip, [r3, #60]	@ <variable>.mb_height, <variable>.mb_height
	movw	r6, #:lower16:78864	@ tmp153,
	movt	r6, #:upper16:78864	@ tmp153,
	movw	r5, #:lower16:78876	@ tmp163,
	movt	r5, #:upper16:78876	@ tmp163,
	add	lr, r4, #78848	@ tmp167, pCtx,
	str	ip, [r4, r7]	@ <variable>.mb_height, <variable>.SliceInfo.pic_height_in_mb
	movw	r2, #:lower16:78868	@ tmp155,
	ldr	r7, [r3, #56]	@ <variable>.mb_width, <variable>.mb_width
	movt	r2, #:upper16:78868	@ tmp155,
	movw	ip, #:lower16:78908	@ tmp165,
	movt	ip, #:upper16:78908	@ tmp165,
	mov	r0, lr	@, tmp167
	add	lr, lr, #64	@ tmp167, tmp167,
	str	r7, [r4, r6]	@ <variable>.mb_width, <variable>.SliceInfo.pic_width_in_mb
	uxtb	r6, r1	@ tmp164, code
	ldr	r1, [r3, #48]	@ <variable>.horizontal_size, <variable>.horizontal_size
	add	r0, r0, #8	@,,
	ldr	r3, [r3, #52]	@ <variable>.vertical_size, <variable>.vertical_size
	add	r1, r1, #15	@ tmp159, <variable>.horizontal_size,
	str	r6, [r4, r5]	@ tmp164, <variable>.SliceInfo.slice_vertical_position
	add	r3, r3, #15	@ tmp156, <variable>.vertical_size,
	str	lr, [r4, ip]	@ tmp167, <variable>.SliceInfo.pBs
	mov	r1, r1, lsr #4	@ tmp161, tmp159,
	mov	r5, r3, lsr #4	@ tmp158, tmp156,
	mul	r3, r1, r5	@ tmp162, tmp161, tmp158
	str	r3, [r4, r2]	@ tmp162, <variable>.SliceInfo.pic_total_mb_num
	bl	MP2_GetFirstMbInSlice	@
	cmp	r0, #1	@ D.40855,
	mov	r5, r0	@ D.40855,
	beq	.L136	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC16	@,
	movt	r1, #:upper16:.LC16	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ ret,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L136:
	mov	r0, r4	@, pCtx
	bl	MP2_WriteSliceInfo	@
	cmp	r0, #1	@ D.40860,
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	mov	r0, r5	@, D.40855
	movw	r1, #:lower16:.LC17	@,
	movt	r1, #:upper16:.LC17	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ ret,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	MP2_DecSlice, .-MP2_DecSlice
	.align	2
	.global	MP2_ClearCurPacket
	.type	MP2_ClearCurPacket, %function
MP2_ClearCurPacket:
	.fnstart
.LFB1571:
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
	mov	r4, r1	@ pMp2Packet, pMp2Packet
	ldr	r1, [r1, #28]	@, <variable>.StreamID
	mov	r5, r0	@ ChanID, ChanID
	bl	SM_ReleaseStreamSeg	@
	ldrsb	r3, [r4, #0]	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r3, #1	@ <variable>.IsLastSeg,
	beq	.L141	@,
	mov	r0, r5	@, ChanID
	ldr	r1, [r4, #32]	@, <variable>.StreamID
	bl	SM_ReleaseStreamSeg	@
.L141:
	mov	r0, r4	@, pMp2Packet
	mov	r1, #36	@,
	bl	__memzero	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	MP2_ClearCurPacket, .-MP2_ClearCurPacket
	.align	2
	.global	MP2_ReceivePacket
	.type	MP2_ReceivePacket, %function
MP2_ReceivePacket:
	.fnstart
.LFB1570:
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
	subs	r4, r1, #0	@ pPacket, pPacket
	mov	r1, r0	@ pMp2CodecInfo, pMp2CodecInfo
	beq	.L149	@,
	movw	ip, #33288	@ tmp141,
	mov	r5, #0	@ tmp142,
	str	r5, [r0, ip]	@ tmp142, <variable>.BsOffset
	movw	r3, #33332	@ tmp143,
	ldr	r0, [r4, #12]	@ <variable>.LenInByte, <variable>.LenInByte
	movw	ip, #33304	@ tmp145,
	str	r0, [r1, r3]	@ <variable>.LenInByte, <variable>.PacketTail
	movw	r3, #33296	@ tmp147,
	ldr	r0, [r4, #8]	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	r0, [r1, ip]	@ <variable>.PhyAddr, <variable>.stMp2Packet.BsPhyAddr
	movw	r0, #33312	@ tmp149,
	ldr	ip, [r4, #0]	@ <variable>.VirAddr, <variable>.VirAddr
	str	ip, [r1, r3]	@ <variable>.VirAddr, <variable>.stMp2Packet.BsVirAddr
	movw	r3, #33292	@ tmp151,
	ldr	ip, [r4, #12]	@ <variable>.LenInByte, <variable>.LenInByte
	str	ip, [r1, r0]	@ <variable>.LenInByte, <variable>.stMp2Packet.BsLength
	movw	ip, #33320	@ tmp154,
	ldrb	r0, [r4, #5]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	strb	r0, [r1, r3]	@ <variable>.IsLastSeg, <variable>.stMp2Packet.IsLastSeg
	ldr	r0, [r4, #16]	@ <variable>.StreamID, <variable>.StreamID
	str	r0, [r1, ip]	@ <variable>.StreamID, <variable>.stMp2Packet.StreamID
	ldrb	r0, [r4, #5]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r0, #1	@ <variable>.IsLastSeg,
	beq	.L146	@,
	ldr	r0, [r4, #88]	@ <variable>.PhyAddr, <variable>.PhyAddr
	movw	r3, #33308	@ tmp157,
	movw	ip, #33300	@ tmp159,
	str	r0, [r1, r3]	@ <variable>.PhyAddr, <variable>.stMp2Packet.BsPhyAddr
	movw	r3, #33316	@ tmp161,
	ldr	r0, [r4, #80]	@ <variable>.VirAddr, <variable>.VirAddr
	str	r0, [r1, ip]	@ <variable>.VirAddr, <variable>.stMp2Packet.BsVirAddr
	movw	r0, #33293	@ tmp163,
	ldr	ip, [r4, #92]	@ <variable>.LenInByte, <variable>.LenInByte
	str	ip, [r1, r3]	@ <variable>.LenInByte, <variable>.stMp2Packet.BsLength
	movw	r3, #33324	@ tmp166,
	ldrb	ip, [r4, #85]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	strb	ip, [r1, r0]	@ <variable>.IsLastSeg, <variable>.stMp2Packet.IsLastSeg
	ldr	r0, [r4, #96]	@ <variable>.StreamID, <variable>.StreamID
	str	r0, [r1, r3]	@ <variable>.StreamID, <variable>.stMp2Packet.StreamID
	ldrb	r0, [r4, #85]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	cmp	r0, #1	@ <variable>.IsLastSeg,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	add	r1, r1, #33280	@, pMp2CodecInfo,
	mov	r0, r2	@, ChanID
	add	r1, r1, #12	@,,
	bl	MP2_ClearCurPacket	@
	ldrb	r2, [r4, #85]	@ zero_extendqisi2	@, <variable>.IsLastSeg
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC19	@,
	movt	r1, #:upper16:.LC19	@,
	bl	dprint_vfmw	@
	mov	r0, r5	@ D.40766, tmp142
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L146:
	movw	ip, #33324	@ tmp182,
	movw	r2, #33308	@ tmp173,
	str	r5, [r1, ip]	@ tmp142, <variable>.stMp2Packet.StreamID
	movw	r3, #33300	@ tmp175,
	str	r5, [r1, r2]	@ tmp142, <variable>.stMp2Packet.BsPhyAddr
	movw	ip, #33316	@ tmp177,
	movw	r2, #33293	@ tmp179,
	str	r5, [r1, r3]	@ tmp142, <variable>.stMp2Packet.BsVirAddr
	str	r5, [r1, ip]	@ tmp142, <variable>.stMp2Packet.BsLength
	strb	r5, [r1, r2]	@ tmp142, <variable>.stMp2Packet.IsLastSeg
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L149:
	movw	r3, #33348	@ tmp139,
	mov	r0, #1	@,
	ldr	r2, [r1, r3]	@, <variable>.Frame_Cnt
	movw	r1, #:lower16:.LC18	@,
	movt	r1, #:upper16:.LC18	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ D.40766, pPacket
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	MP2_ReceivePacket, .-MP2_ReceivePacket
	.align	2
	.global	MPEG2DEC_GetImageBuffer
	.type	MPEG2DEC_GetImageBuffer, %function
MPEG2DEC_GetImageBuffer:
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
	mov	r4, r0	@ pCtx, pCtx
	movw	r0, #45329	@ tmp138,
	ldrb	r3, [r4, r0]	@ zero_extendqisi2	@ <variable>.CodecInfo.Last_FieldStruct, <variable>.CodecInfo.Last_FieldStruct
	cmp	r3, #3	@ <variable>.CodecInfo.Last_FieldStruct,
	beq	.L151	@,
	movw	r2, #:lower16:78680	@ tmp140,
	movt	r2, #:upper16:78680	@ tmp140,
	ldr	r1, [r4, r2]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	cmp	r1, #0	@ <variable>.CodecInfo.Second_Field,
	beq	.L152	@,
.L151:
	movw	r5, #:lower16:113648	@ tmp142,
	movt	r5, #:upper16:113648	@ tmp142,
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	bl	FSP_IsNewFsAvalible	@
	cmp	r0, #1	@,
	beq	.L152	@,
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	bl	FSP_IsNewFsAvalible	@
	cmn	r0, #1	@,
	beq	.L153	@,
.L156:
	mov	r0, #0	@ D.40705,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L152:
	mov	r0, #1	@ D.40705,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L153:
	add	ip, r4, #79872	@, pCtx,
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	add	r1, ip, #128	@,,
	bl	FSP_ClearNotInVoQueue	@
	b	.L156	@
	.fnend
	.size	MPEG2DEC_GetImageBuffer, .-MPEG2DEC_GetImageBuffer
	.align	2
	.global	MP2_ProtocolPPSCheck
	.type	MP2_ProtocolPPSCheck, %function
MP2_ProtocolPPSCheck:
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
	movw	r3, #:lower16:78704	@ tmp144,
	movt	r3, #:upper16:78704	@ tmp144,
	movw	r2, #:lower16:79992	@ tmp143,
	movt	r2, #:upper16:79992	@ tmp143,
	mov	r4, r0	@ pCtx, pCtx
	ldr	r3, [r0, r3]	@ <variable>.CodecInfo.MpegFlag, <variable>.CodecInfo.MpegFlag
	ldr	r1, [r0, r2]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	cmp	r3, #1	@ <variable>.CodecInfo.MpegFlag,
	beq	.L159	@,
	cmp	r3, #2	@ <variable>.CodecInfo.MpegFlag,
	beq	.L177	@,
	movw	ip, #:lower16:78668	@ tmp168,
	movt	ip, #:upper16:78668	@ tmp168,
	ldr	r2, [r0, ip]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orr	r2, r2, #63	@ prephitmp.1263, <variable>.CodecInfo.StreamIntegrality,
	str	r2, [r0, ip]	@ prephitmp.1263, <variable>.CodecInfo.StreamIntegrality
	ldrb	r3, [r1, #22]	@ zero_extendqisi2	@ prephitmp.1267, <variable>.picture_coding_type
.L167:
	tst	r2, #24	@ prephitmp.1263,
	beq	.L171	@,
	cmp	r3, #3	@ prephitmp.1267,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	movw	lr, #:lower16:78668	@ tmp172,
	movw	r5, #:lower16:113648	@ tmp174,
	movt	lr, #:upper16:78668	@ tmp172,
	movt	r5, #:upper16:113648	@ tmp174,
	movw	r7, #:lower16:78748	@ tmp176,
	movt	r7, #:upper16:78748	@ tmp176,
	orr	r6, r2, #64	@ tmp173, prephitmp.1263,
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	str	r6, [r4, lr]	@ tmp173, <variable>.CodecInfo.StreamIntegrality
	ldr	r1, [r4, r7]	@, <variable>.CodecInfo.BwdFsID
	bl	FSP_GetFsImagePtr	@
	subs	r6, r0, #0	@ pImg,
	beq	.L173	@,
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	movw	sl, #:lower16:78744	@ tmp200,
	ldr	r1, [r6, #212]	@, <variable>.p_usrdat
	movt	sl, #:upper16:78744	@ tmp200,
	bl	FreeUsdByDec	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r6, #216]	@, <variable>.p_usrdat
	mov	r8, #0	@ tmp190,
	bl	FreeUsdByDec	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r6, #220]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r6, #224]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	str	r8, [r6, #224]	@ tmp190, <variable>.p_usrdat
	str	r8, [r6, #212]	@ tmp190, <variable>.p_usrdat
	mov	r2, #1	@,
	str	r8, [r6, #216]	@ tmp190, <variable>.p_usrdat
	str	r8, [r6, #220]	@ tmp190, <variable>.p_usrdat
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r4, r7]	@, <variable>.CodecInfo.BwdFsID
	bl	FSP_ClearLogicFs	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r4, sl]	@, <variable>.CodecInfo.FwdFsID
	mov	r2, #1	@,
	bl	FSP_ClearLogicFs	@
	str	r8, [r4, r7]	@ tmp190, <variable>.CodecInfo.BwdFsID
	str	r8, [r4, sl]	@ tmp190, <variable>.CodecInfo.FwdFsID
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	bl	FSP_GetFspType	@
	cmp	r0, r8	@,
	bne	.L178	@,
.L173:
	movw	r3, #:lower16:78708	@ tmp212,
	movt	r3, #:upper16:78708	@ tmp212,
	mov	r1, #0	@ tmp213,
	str	r1, [r4, r3]	@ tmp213,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L171:
	cmp	r3, #1	@ prephitmp.1267,
	biceq	r2, r2, #192	@ tmp215, prephitmp.1263,
	movweq	r3, #:lower16:78668	@ tmp214,
	movteq	r3, #:upper16:78668	@ tmp214,
	streq	r2, [r4, r3]	@ tmp215,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L177:
	movw	r3, #:lower16:78668	@ tmp161,
	movt	r3, #:upper16:78668	@ tmp161,
	ldr	r2, [r0, r3]	@ prephitmp.1266, <variable>.CodecInfo.StreamIntegrality
	tst	r2, #1048576	@ prephitmp.1266,
	orreq	r2, r2, #16	@ prephitmp.1266, prephitmp.1266,
	streq	r2, [r0, r3]	@ prephitmp.1266, <variable>.CodecInfo.StreamIntegrality
	ldrb	r3, [r1, #22]	@ zero_extendqisi2	@ prephitmp.1267, <variable>.picture_coding_type
	sub	ip, r3, #1	@ tmp164, prephitmp.1267,
	uxtb	r0, ip	@ tmp165, tmp164
	cmp	r0, #2	@ tmp165,
	bls	.L176	@,
.L170:
	movw	r0, #:lower16:78668	@ tmp167,
	movt	r0, #:upper16:78668	@ tmp167,
	orr	r2, r2, #8	@ prephitmp.1263, prephitmp.1266,
	str	r2, [r4, r0]	@ prephitmp.1263, <variable>.CodecInfo.StreamIntegrality
	ldrb	r3, [r1, #22]	@ zero_extendqisi2	@ prephitmp.1267, <variable>.picture_coding_type
	b	.L167	@
.L159:
	ldrb	r3, [r1, #22]	@ zero_extendqisi2	@ prephitmp.1267, <variable>.picture_coding_type
	sub	r2, r3, #1	@ tmp146, prephitmp.1267,
	uxtb	r2, r2	@ tmp147, tmp146
	cmp	r2, #3	@ tmp147,
	movwhi	r3, #:lower16:78668	@ tmp149,
	movthi	r3, #:upper16:78668	@ tmp149,
	movwls	r2, #:lower16:78668	@ tmp148,
	movtls	r2, #:upper16:78668	@ tmp148,
	ldrhi	r2, [r0, r3]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	ldrls	r2, [r0, r2]	@ prephitmp.1269, <variable>.CodecInfo.StreamIntegrality
	orrhi	r2, r2, #8	@ prephitmp.1269, <variable>.CodecInfo.StreamIntegrality,
	strhi	r2, [r0, r3]	@ prephitmp.1269, <variable>.CodecInfo.StreamIntegrality
	ldrhib	r3, [r1, #22]	@ zero_extendqisi2	@ prephitmp.1267, <variable>.picture_coding_type
	sub	ip, r3, #2	@ tmp152, prephitmp.1267,
	uxtb	r0, ip	@ tmp153, tmp152
	cmp	r0, #1	@ tmp153,
	bls	.L179	@,
.L176:
	movw	r1, #:lower16:78668	@ tmp166,
	movt	r1, #:upper16:78668	@ tmp166,
	ldr	r2, [r4, r1]	@ prephitmp.1263, <variable>.CodecInfo.StreamIntegrality
	b	.L167	@
.L179:
	ldrb	r0, [r1, #24]	@ zero_extendqisi2	@ <variable>.forward_f_code, <variable>.forward_f_code
	cmp	r0, #0	@ <variable>.forward_f_code,
	orreq	r2, r2, #8	@ prephitmp.1273, prephitmp.1269,
	movweq	r3, #:lower16:78668	@ tmp156,
	movteq	r3, #:upper16:78668	@ tmp156,
	movwne	r2, #:lower16:78668	@ tmp155,
	movtne	r2, #:upper16:78668	@ tmp155,
	streq	r2, [r4, r3]	@ prephitmp.1273, <variable>.CodecInfo.StreamIntegrality
	ldreqb	r3, [r1, #22]	@ zero_extendqisi2	@ prephitmp.1267, <variable>.picture_coding_type
	ldrne	r2, [r4, r2]	@ prephitmp.1273, <variable>.CodecInfo.StreamIntegrality
	cmp	r3, #3	@ prephitmp.1267,
	bne	.L176	@,
	ldrb	ip, [r1, #26]	@ zero_extendqisi2	@ <variable>.backward_f_code, <variable>.backward_f_code
	cmp	ip, #0	@ <variable>.backward_f_code,
	beq	.L170	@,
	b	.L176	@
.L178:
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	bl	FSP_GetNullLogicFs	@
	str	r0, [r4, r7]	@ D.39681, <variable>.CodecInfo.BwdFsID
	str	r0, [r4, sl]	@ D.39681, <variable>.CodecInfo.FwdFsID
	b	.L173	@
	.fnend
	.size	MP2_ProtocolPPSCheck, .-MP2_ProtocolPPSCheck
	.align	2
	.global	MPEG2DEC_RecycleImage
	.type	MPEG2DEC_RecycleImage, %function
MPEG2DEC_RecycleImage:
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
	movw	r4, #:lower16:113648	@ tmp138,
	movt	r4, #:upper16:113648	@ tmp138,
	mov	r6, r1	@ img_id, img_id
	mov	r5, r0	@ pCtx, pCtx
	mov	r2, #0	@,
	ldr	r0, [r0, r4]	@, <variable>.ChanID
	bl	FSP_SetDisplay	@
	mov	r1, r6	@, img_id
	ldr	r0, [r5, r4]	@, <variable>.ChanID
	bl	FSP_GetFsImagePtr	@
	subs	r6, r0, #0	@ pImg,
	beq	.L181	@,
	ldr	r0, [r5, r4]	@, <variable>.ChanID
	mov	r7, #0	@ tmp145,
	ldr	r1, [r6, #212]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	str	r7, [r6, #212]	@ tmp145, <variable>.p_usrdat
	ldr	r1, [r6, #216]	@, <variable>.p_usrdat
	ldr	r0, [r5, r4]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	str	r7, [r6, #216]	@ tmp145, <variable>.p_usrdat
	ldr	r1, [r6, #220]	@, <variable>.p_usrdat
	ldr	r0, [r5, r4]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	str	r7, [r6, #220]	@ tmp145, <variable>.p_usrdat
	ldr	r1, [r6, #224]	@, <variable>.p_usrdat
	ldr	r0, [r5, r4]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	str	r7, [r6, #224]	@ tmp145, <variable>.p_usrdat
.L181:
	mov	r0, #1	@,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	MPEG2DEC_RecycleImage, .-MPEG2DEC_RecycleImage
	.align	2
	.global	MPEG2DEC_Init
	.type	MPEG2DEC_Init, %function
MPEG2DEC_Init:
	.fnstart
.LFB1561:
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
	movw	r5, #:lower16:80344	@ tmp139,
	movt	r5, #:upper16:80344	@ tmp139,
	mov	r7, r1	@ pstExtraData, pstExtraData
	movw	r1, #:lower16:113672	@,
	movt	r1, #:upper16:113672	@,
	ldr	r8, [r0, r5]	@ D.40394, <variable>.ImageQue.ResetMagicWord
	mov	r4, r0	@ pCtx, pCtx
	bl	__memzero	@
	add	r2, r4, #79872	@, pCtx,
	add	r0, r2, #128	@,,
	mov	r6, #0	@ tmp151,
	str	r8, [r4, r5]	@ D.40394, <variable>.ImageQue.ResetMagicWord
	movw	r5, #:lower16:113660	@ tmp150,
	bl	ResetVoQueue	@
	add	lr, r4, #78848	@ tmp146, pCtx,
	movw	ip, #:lower16:79996	@ tmp144,
	movt	ip, #:upper16:79996	@ tmp144,
	movt	r5, #:upper16:113660	@ tmp150,
	movw	r1, #:lower16:79992	@ tmp147,
	movw	r2, #:lower16:78680	@ tmp152,
	movt	r1, #:upper16:79992	@ tmp147,
	movt	r2, #:upper16:78680	@ tmp152,
	movw	r3, #:lower16:78724	@ tmp157,
	movt	r3, #:upper16:78724	@ tmp157,
	mov	r0, lr	@ tmp149, tmp146
	add	lr, lr, #768	@ tmp146, tmp146,
	str	lr, [r4, ip]	@ tmp146, <variable>.pSyntaxInfOld
	movw	lr, #45329	@ tmp154,
	str	r6, [r4, r5]	@ tmp151, <variable>.PPicFound
	str	r6, [r4, r3]	@ tmp151, <variable>.CodecInfo.HDRState
	add	r5, r0, #956	@ tmp149, tmp149,
	str	r7, [r4, #0]	@ pstExtraData, <variable>.pstExtraData
	mov	r0, #3	@ tmp155,
	str	r5, [r4, r1]	@ tmp149, <variable>.pSyntaxInfNew
	mov	r5, #1	@ tmp153,
	strb	r0, [r4, lr]	@ tmp155, <variable>.CodecInfo.Last_FieldStruct
	movw	ip, #:lower16:78656	@ tmp159,
	str	r5, [r4, r2]	@ tmp153, <variable>.CodecInfo.Second_Field
	movt	ip, #:upper16:78656	@ tmp159,
	ldr	r1, [r7, #8]	@ <variable>.s32DecMode, <variable>.s32DecMode
	movw	r2, #:lower16:78716	@ tmp161,
	movt	r2, #:upper16:78716	@ tmp161,
	mov	r0, r4	@, pCtx
	str	r6, [r4, r2]	@ tmp151, <variable>.CodecInfo.Imgbuf_allocated
	str	r1, [r4, ip]	@ <variable>.s32DecMode, <variable>.CodecInfo.UsedDecMode
	bl	VCTRL_GetChanIDByCtx	@
	movw	r3, #:lower16:113648	@ tmp163,
	movt	r3, #:upper16:113648	@ tmp163,
	cmn	r0, #1	@ D.40407,
	str	r0, [r4, r3]	@ D.40407, <variable>.ChanID
	movne	r0, r5	@ D.40412, tmp153
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	mov	r0, r6	@, tmp151
	movw	r1, #:lower16:.LC20	@,
	movt	r1, #:upper16:.LC20	@,
	bl	dprint_vfmw	@
	mvn	r0, #19	@ D.40412,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	.fnend
	.size	MPEG2DEC_Init, .-MPEG2DEC_Init
	.align	2
	.global	extra_bit_information
	.type	extra_bit_information, %function
extra_bit_information:
	.fnstart
.LFB1558:
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
	add	r4, r0, #78848	@ pBs, pCtx,
	add	r4, r4, #64	@ pBs, pBs,
	mov	r5, #0	@ Byte_Count,
.L188:
	mov	r1, #1	@,
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #8	@,
	cmp	r0, #0	@,
	mov	r0, r4	@, pBs
	beq	.L189	@,
	bl	BsSkip	@
	mov	r0, r4	@, pBs
	bl	BsResidBits	@
	add	r5, r5, #1	@ Byte_Count, Byte_Count,
	cmp	r0, #8	@,
	bgt	.L188	@,
.L189:
	mov	r0, r5	@, Byte_Count
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	extra_bit_information, .-extra_bit_information
	.align	2
	.global	picture_coding_extension
	.type	picture_coding_extension, %function
picture_coding_extension:
	.fnstart
.LFB1555:
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
	movw	r7, #:lower16:78668	@ tmp165,
	movt	r7, #:upper16:78668	@ tmp165,
	add	r4, r0, #78848	@ pBs, pCtx,
	add	r4, r4, #64	@ pBs, pBs,
	movw	lr, #:lower16:79992	@ tmp164,
	ldr	r2, [r0, r7]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	movt	lr, #:upper16:79992	@ tmp164,
	mov	r6, r0	@ pCtx, pCtx
	mov	r1, #4	@,
	orr	r5, r2, #1048576	@ tmp168, <variable>.CodecInfo.StreamIntegrality,
	str	r5, [r0, r7]	@ tmp168, <variable>.CodecInfo.StreamIntegrality
	mov	r0, r4	@, pBs
	ldr	r5, [r6, lr]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	bl	BsGet	@
	uxtb	r0, r0	@ temp.1420,
	strb	r0, [r5, #4]	@ temp.1420, <variable>.f_code
	sub	ip, r0, #10	@ tmp170, temp.1420,
	uxtb	r1, ip	@ tmp172, tmp170
	cmp	r0, #0	@ temp.1420,
	cmpne	r1, #4	@, tmp172,
	mov	r0, r4	@, pBs
	ldrls	r1, [r6, r7]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orrls	r1, r1, #16	@ tmp182, <variable>.CodecInfo.StreamIntegrality,
	strls	r1, [r6, r7]	@ tmp182, <variable>.CodecInfo.StreamIntegrality
	mov	r1, #4	@,
	bl	BsGet	@
	mov	r1, #4	@,
	uxtb	r2, r0	@ temp.1428,
	strb	r2, [r5, #5]	@ temp.1428, <variable>.f_code
	sub	r3, r2, #10	@ tmp184, temp.1428,
	mov	r0, r4	@, pBs
	uxtb	ip, r3	@ tmp186, tmp184
	cmp	r2, #0	@ temp.1428,
	cmpne	ip, #4	@, tmp186,
	movwls	ip, #:lower16:78668	@ tmp193,
	movtls	ip, #:upper16:78668	@ tmp193,
	ldrls	r2, [r6, ip]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orrls	r2, r2, #16	@ tmp196, <variable>.CodecInfo.StreamIntegrality,
	strls	r2, [r6, ip]	@ tmp196, <variable>.CodecInfo.StreamIntegrality
	bl	BsGet	@
	uxtb	r0, r0	@ temp.1413,
	strb	r0, [r5, #6]	@ temp.1413, <variable>.f_code
	sub	r1, r0, #10	@ tmp198, temp.1413,
	uxtb	r3, r1	@ tmp200, tmp198
	cmp	r0, #0	@ temp.1413,
	cmpne	r3, #4	@, tmp200,
	bhi	.L196	@,
	movw	r1, #:lower16:78668	@ tmp213,
	movt	r1, #:upper16:78668	@ tmp213,
	ldr	r2, [r6, r1]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orr	lr, r2, #16	@ tmp216, <variable>.CodecInfo.StreamIntegrality,
	str	lr, [r6, r1]	@ tmp216, <variable>.CodecInfo.StreamIntegrality
.L196:
	mov	r0, r4	@, pBs
	mov	r1, #4	@,
	bl	BsGet	@
	uxtb	r0, r0	@ D.40292,
	strb	r0, [r5, #7]	@ D.40292, <variable>.f_code
	sub	ip, r0, #10	@ tmp218, D.40292,
	uxtb	r3, ip	@ tmp220, tmp218
	cmp	r0, #0	@ D.40292,
	cmpne	r3, #4	@, tmp220,
	bhi	.L200	@,
	movw	r3, #:lower16:78668	@ tmp207,
	movt	r3, #:upper16:78668	@ tmp207,
	ldr	r0, [r6, r3]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orr	r1, r0, #16	@ tmp210, <variable>.CodecInfo.StreamIntegrality,
	str	r1, [r6, r3]	@ tmp210, <variable>.CodecInfo.StreamIntegrality
.L200:
	mov	r1, #2	@,
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #2	@,
	strb	r0, [r5, #8]	@, <variable>.intra_dc_precision
	mov	r0, r4	@, pBs
	bl	BsGet	@
	uxtb	ip, r0	@ D.40304,
	strb	ip, [r5, #9]	@ D.40304, <variable>.picture_structure
	cmp	ip, #0	@ D.40304,
	bne	.L204	@,
	movw	r1, #:lower16:78668	@ tmp227,
	movt	r1, #:upper16:78668	@ tmp227,
	ldr	r2, [r6, r1]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orr	lr, r2, #16	@ tmp230, <variable>.CodecInfo.StreamIntegrality,
	str	lr, [r6, r1]	@ tmp230, <variable>.CodecInfo.StreamIntegrality
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L204:
	mov	r1, #1	@,
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	strb	r0, [r5, #10]	@, <variable>.top_field_first
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	strb	r0, [r5, #11]	@, <variable>.frame_pred_frame_dct
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	strb	r0, [r5, #12]	@, <variable>.concealment_motion_vectors
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	strb	r0, [r5, #13]	@, <variable>.q_scale_type
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	strb	r0, [r5, #14]	@, <variable>.intra_vlc_format
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	strb	r0, [r5, #15]	@, <variable>.alternate_scan
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	strb	r0, [r5, #16]	@, <variable>.repeat_first_field
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	strb	r0, [r5, #17]	@, <variable>.chroma_420_type
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	strb	r0, [r5, #18]	@, <variable>.progressive_frame
	mov	r0, r4	@, pBs
	bl	BsGet	@
	uxtb	r0, r0	@ D.40327,
	strb	r0, [r5, #3]	@ D.40327, <variable>.composite_display_flag
	cmp	r0, #0	@ D.40327,
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	mov	r1, #1	@,
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #3	@,
	strb	r0, [r5, #19]	@, <variable>.v_axis
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	strb	r0, [r5, #20]	@, <variable>.field_sequence
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #7	@,
	strb	r0, [r5, #21]	@, <variable>.sub_carrier
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #8	@,
	str	r0, [r5, #32]	@, <variable>.burst_amplitude
	mov	r0, r4	@, pBs
	bl	BsGet	@
	str	r0, [r5, #36]	@, <variable>.sub_carrier_phase
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	picture_coding_extension, .-picture_coding_extension
	.align	2
	.global	picture_display_extension
	.type	picture_display_extension, %function
picture_display_extension:
	.fnstart
.LFB1554:
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
	movw	r7, #:lower16:79992	@ tmp145,
	movt	r7, #:upper16:79992	@ tmp145,
	movw	r2, #:lower16:78668	@ tmp146,
	movt	r2, #:upper16:78668	@ tmp146,
	mov	sl, r0	@ pCtx, pCtx
	ldr	r5, [r0, r7]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	add	r4, r0, #78848	@ pBs, pCtx,
	ldr	r1, [r0, r2]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	add	r4, r4, #64	@ pBs, pBs,
	orr	r0, r1, #2097152	@ tmp149, <variable>.CodecInfo.StreamIntegrality,
	str	r0, [sl, r2]	@ tmp149, <variable>.CodecInfo.StreamIntegrality
	ldrb	r3, [r5, #27]	@ zero_extendqisi2	@ <variable>.progressive_sequence, <variable>.progressive_sequence
	cmp	r3, #0	@ <variable>.progressive_sequence,
	beq	.L206	@,
	ldrb	r8, [r5, #16]	@ zero_extendqisi2	@ <variable>.repeat_first_field, <variable>.repeat_first_field
	cmp	r8, #0	@ <variable>.repeat_first_field,
	bne	.L230	@,
.L207:
	mov	r8, #1	@ number_of_frame_center_offsets,
.L210:
	sub	r2, r8, #1	@ tmp166, number_of_frame_center_offsets,
	mov	r1, #16	@,
	mov	r0, r4	@, pBs
	and	r7, r2, #1	@ tmp168, tmp166,
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [r5, #164]	@, <variable>.frame_center_horizontal_offset
	mov	r0, r4	@, pBs
	bl	BsGet	@
	cmp	r0, #0	@,
	beq	.L229	@,
	mov	r1, #16	@,
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [r5, #176]	@, <variable>.frame_center_vertical_offset
	mov	r0, r4	@, pBs
	bl	BsGet	@
	cmp	r0, #0	@,
	beq	.L229	@,
	mov	r6, #1	@ i,
	cmp	r8, r6	@ number_of_frame_center_offsets, i
	add	r5, r5, #4	@ ivtmp.1462, pSyntaxInfNew,
	ldmlefd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	cmp	r7, #0	@ tmp168,
	beq	.L214	@,
	mov	r1, #16	@,
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, r6	@, i
	str	r0, [r5, #164]	@, <variable>.frame_center_horizontal_offset
	mov	r0, r4	@, pBs
	bl	BsGet	@
	cmp	r0, #0	@,
	beq	.L229	@,
	mov	r1, #16	@,
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, r6	@, i
	str	r0, [r5, #176]	@, <variable>.frame_center_vertical_offset
	mov	r0, r4	@, pBs
	bl	BsGet	@
	cmp	r0, #0	@,
	beq	.L229	@,
	mov	r6, #2	@ i,
	cmp	r8, r6	@ number_of_frame_center_offsets, i
	add	r5, r5, #4	@ ivtmp.1462, ivtmp.1462,
	bgt	.L214	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L211:
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [r5, #176]	@, <variable>.frame_center_vertical_offset
	mov	r0, r4	@, pBs
	bl	BsGet	@
	add	r5, r7, #4	@ ivtmp.1462, tmp170,
	mov	r1, #16	@,
	cmp	r0, #0	@,
	mov	r0, r4	@, pBs
	beq	.L229	@,
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [r7, #164]	@, <variable>.frame_center_horizontal_offset
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #16	@,
	cmp	r0, #0	@,
	mov	r0, r4	@, pBs
	beq	.L229	@,
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [r7, #176]	@, <variable>.frame_center_vertical_offset
	mov	r0, r4	@, pBs
	bl	BsGet	@
	cmp	r0, #0	@,
	beq	.L229	@,
	cmp	r8, r6	@ number_of_frame_center_offsets, i
	ble	.L231	@,
.L214:
	mov	r1, #16	@,
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	add	r6, r6, r1	@ tmp169, i,
	add	r7, r5, #4	@ tmp170, ivtmp.1462,
	add	r6, r6, r1	@ i, tmp169,
	str	r0, [r5, #164]	@, <variable>.frame_center_horizontal_offset
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #16	@,
	cmp	r0, #0	@,
	mov	r0, r4	@, pBs
	bne	.L211	@,
.L229:
	movw	r1, #:lower16:78668	@ tmp159,
	movt	r1, #:upper16:78668	@ tmp159,
	ldr	ip, [sl, r1]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orr	r0, ip, #32	@ tmp162, <variable>.CodecInfo.StreamIntegrality,
	str	r0, [sl, r1]	@ tmp162, <variable>.CodecInfo.StreamIntegrality
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L206:
	ldrb	lr, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	cmp	lr, #3	@ <variable>.picture_structure,
	bne	.L207	@,
	ldrb	r3, [r5, #16]	@ zero_extendqisi2	@ <variable>.repeat_first_field, <variable>.repeat_first_field
	cmp	r3, #0	@ <variable>.repeat_first_field,
	beq	.L209	@,
.L208:
	mov	r8, #3	@ number_of_frame_center_offsets,
	b	.L210	@
.L230:
	ldrb	ip, [r5, #10]	@ zero_extendqisi2	@ <variable>.top_field_first, <variable>.top_field_first
	cmp	ip, #0	@ <variable>.top_field_first,
	bne	.L208	@,
.L209:
	mov	r8, #2	@ number_of_frame_center_offsets,
	b	.L210	@
.L231:
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	.fnend
	.size	picture_display_extension, .-picture_display_extension
	.align	2
	.global	quant_matrix_extension
	.type	quant_matrix_extension, %function
quant_matrix_extension:
	.fnstart
.LFB1552:
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
	add	r4, r0, #78848	@ pBs, pCtx,
	add	r4, r4, #64	@ pBs, pBs,
	movw	r3, #:lower16:79992	@ tmp179,
	movt	r3, #:upper16:79992	@ tmp179,
	mov	r5, r0	@ pCtx, pCtx
	mov	r1, #1	@,
	mov	r0, r4	@, pBs
	ldr	sl, [r5, r3]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	bl	BsGet	@
	cmp	r0, #1	@ D.40202,
	str	r0, [sl, #76]	@ D.40202, <variable>.load_intra_quantizer_matrix
	beq	.L250	@,
	mov	r0, r4	@, pBs
	mov	r1, #1	@,
	bl	BsGet	@
	cmp	r0, #1	@ D.40212,
	str	r0, [sl, #80]	@ D.40212, <variable>.load_non_intra_quantizer_matrix
	beq	.L251	@,
.L235:
	mov	r0, r4	@, pBs
	mov	r1, #1	@,
	bl	BsGet	@
	cmp	r0, #0	@,
	beq	.L237	@,
	mov	r5, #0	@ i.1524,
.L238:
	mov	r1, #8	@,
	add	r5, r5, #1	@ tmp192, i.1524,
	mov	r0, r4	@, pBs
	add	r5, r5, #1	@ i.1524, tmp192,
	bl	BsGet	@
	mov	r0, r4	@, pBs
	mov	r1, #8	@,
	bl	BsGet	@
	cmp	r5, #64	@ i.1524,
	bne	.L238	@,
.L237:
	mov	r0, r4	@, pBs
	mov	r1, #1	@,
	bl	BsGet	@
	cmp	r0, #0	@,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	mov	r5, #0	@ i.1525,
.L240:
	add	lr, r5, #1	@ tmp191, i.1525,
	mov	r1, #8	@,
	mov	r0, r4	@, pBs
	add	r5, lr, #1	@ i.1525, tmp191,
	bl	BsGet	@
	mov	r0, r4	@, pBs
	mov	r1, #8	@,
	bl	BsGet	@
	cmp	r5, #64	@ i.1525,
	bne	.L240	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L250:
	movw	r7, #:lower16:.LANCHOR1	@ tmp186,
	movt	r7, #:upper16:.LANCHOR1	@ tmp186,
	mov	r6, #0	@ i,
.L234:
	mov	r1, #8	@,
	mov	r0, r4	@, pBs
	ldrb	r8, [r7, r6]	@ zero_extendqisi2	@ D.40209, zigzag
	bl	BsGet	@
	add	r2, r6, #1	@ tmp194, i,
	mov	r1, #8	@,
	add	r3, r8, #19712	@ tmp181, D.40209,
	add	r6, r2, #1	@ i, tmp194,
	add	ip, r3, #24	@ tmp181, tmp181,
	str	r0, [r5, ip, asl #2]	@, <variable>.intra_quantizer_matrix
	mov	r0, r4	@, pBs
	ldrb	r8, [r7, r2]	@ zero_extendqisi2	@ D.40209, zigzag
	bl	BsGet	@
	cmp	r6, #64	@ i,
	add	r8, r8, #19712	@ tmp199, D.40209,
	add	r8, r8, #24	@ tmp199, tmp199,
	str	r0, [r5, r8, asl #2]	@, <variable>.intra_quantizer_matrix
	bne	.L234	@,
	mov	r0, r4	@, pBs
	mov	r1, #1	@,
	bl	BsGet	@
	cmp	r0, #1	@ D.40212,
	str	r0, [sl, #80]	@ D.40212, <variable>.load_non_intra_quantizer_matrix
	bne	.L235	@,
.L251:
	movw	r7, #:lower16:.LANCHOR1	@ tmp200,
	movt	r7, #:upper16:.LANCHOR1	@ tmp200,
	mov	r6, #0	@ i.1523,
.L236:
	mov	r1, #8	@,
	mov	r0, r4	@, pBs
	ldrb	r8, [r7, r6]	@ zero_extendqisi2	@ temp.1522, zigzag
	bl	BsGet	@
	add	r2, r6, #1	@ tmp193, i.1523,
	mov	r1, #8	@,
	add	r3, r8, #19712	@ tmp184, temp.1522,
	add	r6, r2, #1	@ i.1523, tmp193,
	add	ip, r3, #88	@ tmp184, tmp184,
	str	r0, [r5, ip, asl #2]	@, <variable>.non_intra_quantizer_matrix
	mov	r0, r4	@, pBs
	ldrb	r8, [r7, r2]	@ zero_extendqisi2	@ temp.1522, zigzag
	bl	BsGet	@
	cmp	r6, #64	@ i.1523,
	add	r1, r8, #19712	@ tmp205, temp.1522,
	add	r8, r1, #88	@ tmp205, tmp205,
	str	r0, [r5, r8, asl #2]	@, <variable>.non_intra_quantizer_matrix
	bne	.L236	@,
	b	.L235	@
	.fnend
	.size	quant_matrix_extension, .-quant_matrix_extension
	.align	2
	.global	sequence_display_extension
	.type	sequence_display_extension, %function
sequence_display_extension:
	.fnstart
.LFB1551:
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
	movw	r2, #:lower16:78668	@ tmp147,
	movt	r2, #:upper16:78668	@ tmp147,
	add	r4, r0, #78848	@ pBs, pCtx,
	mov	r5, r0	@ pCtx, pCtx
	add	r4, r4, #64	@ pBs, pBs,
	ldr	r0, [r0, r2]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	movw	r3, #:lower16:79992	@ tmp146,
	movt	r3, #:upper16:79992	@ tmp146,
	orr	r1, r0, #262144	@ tmp150, <variable>.CodecInfo.StreamIntegrality,
	mov	r0, r4	@, pBs
	str	r1, [r5, r2]	@ tmp150, <variable>.CodecInfo.StreamIntegrality
	mov	r1, #3	@,
	ldr	r6, [r5, r3]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [r6, #128]	@, <variable>.video_format
	mov	r0, r4	@, pBs
	bl	BsGet	@
	cmp	r0, #0	@ D.40165,
	str	r0, [r6, #132]	@ D.40165, <variable>.color_description
	bne	.L257	@,
.L253:
	mov	r1, #14	@,
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [r6, #148]	@, <variable>.display_horizontal_size
	mov	r0, r4	@, pBs
	bl	BsGet	@
	cmp	r0, #0	@,
	bne	.L254	@,
	movw	lr, #:lower16:78668	@ tmp151,
	movt	lr, #:upper16:78668	@ tmp151,
	ldr	r3, [r5, lr]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orr	ip, r3, #4	@ tmp154, <variable>.CodecInfo.StreamIntegrality,
	str	ip, [r5, lr]	@ tmp154, <variable>.CodecInfo.StreamIntegrality
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L254:
	mov	r0, r4	@, pBs
	mov	r1, #14	@,
	bl	BsGet	@
	str	r0, [r6, #152]	@, <variable>.display_vertical_size
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L257:
	mov	r1, #8	@,
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #8	@,
	str	r0, [r6, #136]	@, <variable>.color_primaries
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #8	@,
	str	r0, [r6, #140]	@, <variable>.transfer_characteristics
	mov	r0, r4	@, pBs
	bl	BsGet	@
	str	r0, [r6, #144]	@, <variable>.matrix_coefficients
	b	.L253	@
	.fnend
	.size	sequence_display_extension, .-sequence_display_extension
	.align	2
	.global	sequence_extension
	.type	sequence_extension, %function
sequence_extension:
	.fnstart
.LFB1550:
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
	movw	r7, #:lower16:78668	@ tmp159,
	movt	r7, #:upper16:78668	@ tmp159,
	add	r8, r0, #78848	@ pBs, pCtx,
	add	r8, r8, #64	@ pBs, pBs,
	movw	r2, #:lower16:78664	@ tmp163,
	ldr	r4, [r0, r7]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	movt	r2, #:upper16:78664	@ tmp163,
	mov	r5, r0	@ pCtx, pCtx
	movw	r3, #:lower16:79992	@ tmp158,
	movt	r3, #:upper16:79992	@ tmp158,
	orr	r1, r4, #131072	@ tmp162, <variable>.CodecInfo.StreamIntegrality,
	str	r1, [r0, r7]	@ tmp162, <variable>.CodecInfo.StreamIntegrality
	mov	r1, #8	@,
	mov	r0, #0	@ tmp164,
	str	r0, [r5, r2]	@ tmp164, <variable>.CodecInfo.NewSeqInited
	mov	r0, r8	@, pBs
	ldr	r4, [r5, r3]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [r4, #124]	@, <variable>.profile_and_level_indication
	mov	r0, r8	@, pBs
	bl	BsGet	@
	mov	r1, #2	@,
	strb	r0, [r4, #27]	@, <variable>.progressive_sequence
	mov	r0, r8	@, pBs
	bl	BsGet	@
	mov	r1, #2	@,
	strb	r0, [r4, #28]	@, <variable>.chroma_format
	mov	r0, r8	@, pBs
	bl	BsGet	@
	mov	r1, #2	@,
	mov	r9, r0	@ D.40078,
	mov	r0, r8	@, pBs
	bl	BsGet	@
	mov	r1, #12	@,
	mov	sl, r0	@ D.40079,
	mov	r0, r8	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	mov	r6, r0	@ D.40080,
	mov	r0, r8	@, pBs
	bl	BsGet	@
	cmp	r0, #0	@,
	bne	.L259	@,
	ldr	lr, [r5, r7]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orr	ip, lr, #2	@ tmp170, <variable>.CodecInfo.StreamIntegrality,
	str	ip, [r5, r7]	@ tmp170, <variable>.CodecInfo.StreamIntegrality
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L259:
	mov	r1, #8	@,
	mov	r0, r8	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	mov	r7, r0	@ D.40085,
	mov	r0, r8	@, pBs
	bl	BsGet	@
	mov	r1, #2	@,
	strb	r0, [r4, #29]	@, <variable>.low_delay
	mov	r0, r8	@, pBs
	bl	BsGet	@
	mov	r1, #5	@,
	strb	r0, [r4, #30]	@, <variable>.frame_rate_extension_n
	mov	r0, r8	@, pBs
	bl	BsGet	@
	ldrb	ip, [r4, #30]	@ zero_extendqisi2	@ <variable>.frame_rate_extension_n, <variable>.frame_rate_extension_n
	uxtb	r2, r0	@ D.40091,
	add	r0, ip, #1	@, <variable>.frame_rate_extension_n,
	add	r1, r2, #1	@, D.40091,
	strb	r2, [r4, #31]	@ D.40091, <variable>.frame_rate_extension_d
	bl	__aeabi_idiv	@
	ldr	r1, [r4, #88]	@ <variable>.frame_rate_code, <variable>.frame_rate_code
	movw	r3, #:lower16:.LANCHOR0	@ tmp181,
	movt	r3, #:upper16:.LANCHOR0	@ tmp181,
	ldr	r2, [r4, #124]	@ D.40105, <variable>.profile_and_level_indication
	add	ip, r3, r1, asl #2	@, tmp185, tmp181, <variable>.frame_rate_code,
	tst	r2, #128	@ D.40105,
	ldr	r1, [ip, #1100]	@ tmp187, frame_rate_Table
	mul	r3, r1, r0	@ tmp188, tmp187,
	str	r3, [r4, #72]	@ tmp188, <variable>.frame_rate
	bne	.L271	@,
	and	ip, r2, #15	@ tmp196, D.40105,
	ubfx	r1, r2, #4, #3	@ tmp194, D.40105,,
	str	ip, [r4, #44]	@ tmp196, <variable>.level
	str	r1, [r4, #40]	@ tmp194, <variable>.profile
.L262:
	ldr	ip, [r4, #48]	@ <variable>.horizontal_size, <variable>.horizontal_size
	ldr	r3, [r4, #52]	@ <variable>.vertical_size, <variable>.vertical_size
	mov	r1, ip, asl #20	@ tmp198, <variable>.horizontal_size,
	mov	r0, r3, asl #20	@ tmp202, <variable>.vertical_size,
	mov	lr, r1, lsr #20	@ tmp198, tmp198,
	orr	r9, lr, r9, asl #12	@, prephitmp.1564, tmp198, D.40078,
	mov	r2, r0, lsr #20	@ tmp202, tmp202,
	cmp	r9, #0	@ prephitmp.1564,
	orr	sl, r2, sl, asl #12	@, D.40122, tmp202, D.40079,
	str	r9, [r4, #48]	@ prephitmp.1564, <variable>.horizontal_size
	str	sl, [r4, #52]	@ D.40122, <variable>.vertical_size
	beq	.L263	@,
	cmp	sl, #0	@ D.40122,
	bne	.L264	@,
.L263:
	movw	r0, #:lower16:78668	@ tmp205,
	movt	r0, #:upper16:78668	@ tmp205,
	ldr	r2, [r5, r0]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orr	r9, r2, #1	@ tmp208, <variable>.CodecInfo.StreamIntegrality,
	str	r9, [r5, r0]	@ tmp208, <variable>.CodecInfo.StreamIntegrality
	ldr	r9, [r4, #48]	@ prephitmp.1564, <variable>.horizontal_size
.L264:
	cmp	r9, #8192	@ prephitmp.1564,
	bhi	.L265	@,
	ldr	lr, [r4, #52]	@ <variable>.vertical_size, <variable>.vertical_size
	cmp	lr, #8192	@ <variable>.vertical_size,
	bls	.L266	@,
.L265:
	movw	r3, #:lower16:78668	@ tmp210,
	movt	r3, #:upper16:78668	@ tmp210,
	movw	r0, #:lower16:g_event_report	@ tmp214,
	movt	r0, #:upper16:g_event_report	@ tmp214,
	ldr	ip, [r5, r3]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orr	r1, ip, #1	@ tmp213, <variable>.CodecInfo.StreamIntegrality,
	str	r1, [r5, r3]	@ tmp213, <variable>.CodecInfo.StreamIntegrality
	ldr	ip, [r0, #0]	@ g_event_report.494, g_event_report
	cmp	ip, #0	@ g_event_report.494,
	beq	.L266	@,
	movw	lr, #:lower16:113648	@ tmp215,
	movt	lr, #:upper16:113648	@ tmp215,
	mov	r2, #0	@,
	mov	r1, #102	@,
	ldr	r0, [r5, lr]	@, <variable>.ChanID
	mov	r3, r2	@,
	blx	ip	@ g_event_report.494
.L266:
	ldr	ip, [r4, #92]	@ <variable>.bit_rate_value, <variable>.bit_rate_value
	mov	r0, #400	@ tmp219,
	ldr	r2, [r4, #40]	@ prephitmp.1582, <variable>.profile
	add	r6, ip, r6, asl #18	@, D.40136, <variable>.bit_rate_value, D.40080,
	str	r6, [r4, #92]	@ D.40136, <variable>.bit_rate_value
	sub	r1, r2, #4	@ tmp224, prephitmp.1582,
	ldr	r3, [r4, #96]	@ <variable>.vbv_buffer_size, <variable>.vbv_buffer_size
	mul	r6, r0, r6	@ tmp220, tmp219, D.40136
	cmp	r1, #1	@ tmp224,
	add	r7, r3, r7, asl #10	@, tmp223, <variable>.vbv_buffer_size, D.40085,
	str	r7, [r4, #96]	@ tmp223, <variable>.vbv_buffer_size
	str	r6, [r4, #68]	@ tmp220, <variable>.bit_rate
	bls	.L267	@,
	movw	lr, #:lower16:g_event_report	@ tmp225,
	movt	lr, #:upper16:g_event_report	@ tmp225,
	ldr	ip, [lr, #0]	@ g_event_report.1583, g_event_report
	cmp	ip, #0	@ g_event_report.1583,
	beq	.L268	@,
	movw	r3, #:lower16:113648	@ tmp226,
	movt	r3, #:upper16:113648	@ tmp226,
	mov	r2, #0	@,
	mov	r1, #102	@,
	ldr	r0, [r5, r3]	@, <variable>.ChanID
	mov	r3, r2	@,
	blx	ip	@ g_event_report.1583
	ldr	r2, [r4, #40]	@ prephitmp.1582, <variable>.profile
.L268:
	movw	r1, #:lower16:.LC21	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC21	@,
	bl	dprint_vfmw	@
.L267:
	ldr	r2, [r4, #44]	@ prephitmp.1585, <variable>.level
	sub	r1, r2, #4	@ tmp229, prephitmp.1585,
	cmp	r1, #6	@ tmp229,
	ldmlsfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	movw	r0, #:lower16:g_event_report	@ tmp230,
	movt	r0, #:upper16:g_event_report	@ tmp230,
	ldr	ip, [r0, #0]	@ g_event_report.1586, g_event_report
	cmp	ip, #0	@ g_event_report.1586,
	beq	.L269	@,
	movw	lr, #:lower16:113648	@ tmp231,
	movt	lr, #:upper16:113648	@ tmp231,
	mov	r2, #0	@,
	mov	r1, #102	@,
	mov	r3, r2	@,
	ldr	r0, [r5, lr]	@, <variable>.ChanID
	blx	ip	@ g_event_report.1586
	ldr	r2, [r4, #44]	@ prephitmp.1585, <variable>.level
.L269:
	movw	r1, #:lower16:.LC22	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC22	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L271:
	and	r0, r2, #15	@ tmp190, D.40105,
	cmp	r0, #5	@ tmp190,
	moveq	r3, #133	@ tmp191,
	moveq	lr, #8	@ tmp192,
	streq	r3, [r4, #40]	@ tmp191, <variable>.profile
	streq	lr, [r4, #44]	@ tmp192, <variable>.level
	b	.L262	@
	.fnend
	.size	sequence_extension, .-sequence_extension
	.align	2
	.global	extension
	.type	extension, %function
extension:
	.fnstart
.LFB1560:
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
	movw	ip, #:lower16:79992	@ tmp137,
	movt	ip, #:upper16:79992	@ tmp137,
	add	r1, r0, #78848	@, pCtx,
	mov	r2, #0	@ tmp138,
	mov	r4, r0	@ pCtx, pCtx
	ldr	r3, [r0, ip]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	add	r0, r1, #64	@,,
	mov	r1, #4	@,
	str	r2, [r3, #152]	@ tmp138, <variable>.display_vertical_size
	str	r2, [r3, #128]	@ tmp138, <variable>.video_format
	str	r2, [r3, #132]	@ tmp138, <variable>.color_description
	str	r2, [r3, #136]	@ tmp138, <variable>.color_primaries
	str	r2, [r3, #140]	@ tmp138, <variable>.transfer_characteristics
	str	r2, [r3, #144]	@ tmp138, <variable>.matrix_coefficients
	str	r2, [r3, #148]	@ tmp138, <variable>.display_horizontal_size
	bl	BsGet	@
	sub	r0, r0, #1	@ tmp147,,
	cmp	r0, #9	@ tmp147,
	ldrls	pc, [pc, r0, asl #2]	@ tmp147
	b	.L273	@
.L283:
	.word	.L274
	.word	.L275
	.word	.L276
	.word	.L277
	.word	.L278
	.word	.L273
	.word	.L279
	.word	.L280
	.word	.L281
	.word	.L282
.L277:
	mov	r0, r4	@, pCtx
	bl	copyright_extension	@
.L273:
	mov	r0, #1	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L282:
	mov	r0, r4	@, pCtx
	bl	picture_temporal_scalable_extension	@
	mov	r0, #1	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L274:
	mov	r0, r4	@, pCtx
	bl	sequence_extension	@
	mov	r0, #1	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L275:
	mov	r0, r4	@, pCtx
	bl	sequence_display_extension	@
	mov	r0, #1	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L276:
	mov	r0, r4	@, pCtx
	bl	quant_matrix_extension	@
	mov	r0, #1	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L278:
	mov	r0, r4	@, pCtx
	bl	sequence_scalable_extension	@
	mov	r0, #1	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L279:
	mov	r0, r4	@, pCtx
	bl	picture_display_extension	@
	mov	r0, #1	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L280:
	mov	r0, r4	@, pCtx
	bl	picture_coding_extension	@
	mov	r0, #1	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L281:
	mov	r0, r4	@, pCtx
	bl	picture_spatial_scalable_extension	@
	mov	r0, #1	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	extension, .-extension
	.align	2
	.global	picture_header
	.type	picture_header, %function
picture_header:
	.fnstart
.LFB1549:
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
	movw	r6, #:lower16:78668	@ tmp146,
	movt	r6, #:upper16:78668	@ tmp146,
	add	r4, r0, #78848	@ pBs, pCtx,
	mov	r5, r0	@ pCtx, pCtx
	add	r4, r4, #64	@ pBs, pBs,
	ldr	r1, [r0, r6]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	movw	lr, #:lower16:79992	@ tmp145,
	movt	lr, #:upper16:79992	@ tmp145,
	bic	r0, r1, #3145728	@ tmp148, <variable>.CodecInfo.StreamIntegrality,
	mov	r1, #10	@,
	bic	r3, r0, #56	@ tmp148, tmp148,
	mov	r0, r4	@, pBs
	orr	ip, r3, #524288	@ tmp151, tmp148,
	str	ip, [r5, r6]	@ tmp151, <variable>.CodecInfo.StreamIntegrality
	ldr	r6, [r5, lr]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	bl	BsGet	@
	mov	r1, #3	@,
	str	r0, [r6, #156]	@, <variable>.temporal_reference
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #16	@,
	strb	r0, [r6, #22]	@, <variable>.picture_coding_type
	mov	r0, r4	@, pBs
	bl	BsGet	@
	ldrb	r2, [r6, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	sub	r1, r2, #2	@ tmp155, <variable>.picture_coding_type,
	uxtb	r3, r1	@ tmp156, tmp155
	cmp	r3, #1	@ tmp156,
	str	r0, [r6, #160]	@, <variable>.vbv_delay
	bls	.L288	@,
.L286:
	mov	r0, r5	@, pCtx
	bl	extra_bit_information	@
	mov	r0, #1	@,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L288:
	mov	r1, #1	@,
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, #3	@,
	strb	r0, [r6, #23]	@, <variable>.full_pel_forward_vector
	mov	r0, r4	@, pBs
	bl	BsGet	@
	ldrb	r7, [r6, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	cmp	r7, #3	@ <variable>.picture_coding_type,
	strb	r0, [r6, #24]	@, <variable>.forward_f_code
	bne	.L286	@,
	mov	r1, #1	@,
	mov	r0, r4	@, pBs
	bl	BsGet	@
	mov	r1, r7	@, <variable>.picture_coding_type
	strb	r0, [r6, #25]	@, <variable>.full_pel_backward_vector
	mov	r0, r4	@, pBs
	bl	BsGet	@
	strb	r0, [r6, #26]	@, <variable>.backward_f_code
	mov	r0, r5	@, pCtx
	bl	extra_bit_information	@
	mov	r0, #1	@,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	picture_header, .-picture_header
	.align	2
	.global	group_of_pictures_header
	.type	group_of_pictures_header, %function
group_of_pictures_header:
	.fnstart
.LFB1548:
	@ args = 0, pretend = 0, frame = 8
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
	mov	r4, r0	@ pCtx, pCtx
	add	r0, r0, #78848	@ pBs, pCtx,
	movw	r9, #:lower16:79992	@ tmp165,
	add	r7, r0, #64	@ pBs, pBs,
	movt	r9, #:upper16:79992	@ tmp165,
	mov	r1, #1	@,
	add	r6, r4, #77824	@ tmp149, pCtx,
	mov	r0, r7	@, pBs
	ldr	r8, [r4, r9]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	bl	BsGet	@
	mov	r1, #5	@,
	add	r5, r4, #77824	@ tmp148, pCtx,
	movw	r9, #:lower16:78832	@ tmp170,
	movt	r9, #:upper16:78832	@ tmp170,
	mov	sl, #0	@ tmp159,
	strb	r0, [r8, #2]	@, <variable>.drop_flag
	mov	r0, r7	@, pBs
	bl	BsGet	@
	mov	r1, #6	@,
	str	r0, [r8, #100]	@, <variable>.hour
	mov	r0, r7	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [r8, #104]	@, <variable>.minute
	mov	r0, r7	@, pBs
	bl	BsSkip	@
	mov	r0, r7	@, pBs
	mov	r1, #6	@,
	bl	BsGet	@
	mov	r1, #6	@,
	str	r0, [r8, #108]	@, <variable>.sec
	mov	r0, r7	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [r8, #112]	@, <variable>.frame
	mov	r0, r7	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [r8, #116]	@, <variable>.closed_gop
	mov	r0, r7	@, pBs
	bl	BsGet	@
	add	ip, r6, #976	@ tmp149, tmp149,
	movw	r6, #:lower16:78824	@ tmp169,
	movt	r6, #:upper16:78824	@ tmp169,
	mov	r1, r5	@ tmp153, tmp148
	add	r2, r4, r6	@, pCtx, tmp169
	add	r3, r1, #988	@ tmp153, tmp153,
	str	r2, [fp, #-48]	@, %sfp
	add	r5, r5, #964	@ tmp148, tmp148,
	movw	r7, #:lower16:78828	@ tmp171,
	movt	r7, #:upper16:78828	@ tmp171,
	str	r0, [r8, #120]	@, <variable>.broken_link
	ldmia	ip, {r0, r1, r2}	@ tmp149,,,
	stmia	r5, {r0, r1, r2}	@ tmp148,,,
	ldmia	r3, {r0, r1, r2}	@ tmp153,,,
	stmia	ip, {r0, r1, r2}	@ tmp149,,,
	ldr	ip, [fp, #-48]	@, %sfp
	ldmia	ip, {r0, r1, r2}	@,,,
	stmia	r3, {r0, r1, r2}	@ tmp153,,,
	str	sl, [r4, r7]	@ tmp159, <variable>.GopFldCnt
	str	sl, [r4, r6]	@ tmp159, <variable>.GopFrmCntNoRpt
	str	sl, [r4, r9]	@ tmp159, <variable>.GopFrmCnt
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
	.fnend
	.size	group_of_pictures_header, .-group_of_pictures_header
	.align	2
	.global	sequence_header
	.type	sequence_header, %function
sequence_header:
	.fnstart
.LFB1547:
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
	add	r5, r0, #78848	@ pBs, pCtx,
	add	r5, r5, #64	@ pBs, pBs,
	movw	r6, #:lower16:78668	@ tmp164,
	movw	r2, #:lower16:78664	@ tmp166,
	movt	r6, #:upper16:78668	@ tmp164,
	movt	r2, #:upper16:78664	@ tmp166,
	mov	r4, r0	@ pCtx, pCtx
	movw	r3, #:lower16:79992	@ tmp163,
	movt	r3, #:upper16:79992	@ tmp163,
	mov	r1, #12	@,
	mov	sl, #65536	@ tmp165,
	str	sl, [r0, r6]	@ tmp165, <variable>.CodecInfo.StreamIntegrality
	mov	r0, #0	@ tmp167,
	str	r0, [r4, r2]	@ tmp167, <variable>.CodecInfo.NewSeqInited
	mov	r0, r5	@, pBs
	ldr	sl, [r4, r3]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	bl	BsGet	@
	mov	r1, #12	@,
	str	r0, [sl, #48]	@, <variable>.horizontal_size
	mov	r0, r5	@, pBs
	bl	BsGet	@
	mov	r1, #4	@,
	str	r0, [sl, #52]	@, <variable>.vertical_size
	mov	r0, r5	@, pBs
	bl	BsGet	@
	mov	r1, #4	@,
	str	r0, [sl, #84]	@, <variable>.aspect_ratio_information
	mov	r0, r5	@, pBs
	bl	BsGet	@
	mov	r1, #18	@,
	str	r0, [sl, #88]	@, <variable>.frame_rate_code
	mov	r0, r5	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [sl, #92]	@, <variable>.bit_rate_value
	mov	r0, r5	@, pBs
	bl	BsGet	@
	mov	r1, #10	@,
	cmp	r0, #0	@,
	mov	r0, r5	@, pBs
	ldreq	r3, [r4, r6]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orreq	r3, r3, #1	@ tmp171, <variable>.CodecInfo.StreamIntegrality,
	streq	r3, [r4, r6]	@ tmp171, <variable>.CodecInfo.StreamIntegrality
	bl	BsGet	@
	mov	r1, #1	@,
	str	r0, [sl, #96]	@, <variable>.vbv_buffer_size
	mov	r0, r5	@, pBs
	bl	BsGet	@
	mov	r1, #1	@,
	strb	r0, [sl, #1]	@, <variable>.constrained_parameters_flag
	mov	r0, r5	@, pBs
	bl	BsGet	@
	cmp	r0, #1	@ D.39988,
	str	r0, [sl, #76]	@ D.39988, <variable>.load_intra_quantizer_matrix
	beq	.L310	@,
	add	r1, r4, #78848	@ ivtmp.1723, pCtx,
	movw	r6, #:lower16:.LANCHOR1	@ tmp188,
	movt	r6, #:upper16:.LANCHOR1	@ tmp188,
	add	r1, r1, #96	@ ivtmp.1723, ivtmp.1723,
	add	ip, r6, #64	@ tmp189, tmp188,
	mov	r3, #0	@ i.1726,
.L296:
	ldrb	lr, [ip, r3]	@ zero_extendqisi2	@ tmp179, default_intra_quantizer_matrix
	add	r0, r3, #1	@ tmp198, i.1726,
	mov	r2, r1	@ tmp199, ivtmp.1723
	add	r3, r0, #1	@ i.1726, tmp198,
	cmp	r3, #64	@ i.1726,
	str	lr, [r2], #4	@ tmp179, <variable>.intra_quantizer_matrix
	ldrb	lr, [ip, r0]	@ zero_extendqisi2	@ tmp207, default_intra_quantizer_matrix
	str	lr, [r1, #4]	@ tmp207, <variable>.intra_quantizer_matrix
	add	r1, r2, #4	@ ivtmp.1723, tmp199,
	bne	.L296	@,
	mov	r0, r5	@, pBs
	mov	r1, #1	@,
	bl	BsGet	@
	cmp	r0, #1	@ D.40001,
	str	r0, [sl, #80]	@ D.40001, <variable>.load_non_intra_quantizer_matrix
	movne	r3, #0	@ ivtmp.1707,
	movne	ip, #16	@ tmp193,
	beq	.L311	@,
.L300:
	add	r0, r3, #4	@ tmp196, ivtmp.1707,
	add	r3, r4, r3	@ tmp183, pCtx, ivtmp.1707
	add	r2, r4, r0	@ tmp214, pCtx, tmp196
	add	r1, r3, #78848	@ tmp184, tmp183,
	add	lr, r2, #78848	@ tmp216, tmp214,
	add	r3, r0, #4	@ ivtmp.1707, tmp196,
	add	r1, r1, #352	@ tmp184, tmp184,
	add	r0, lr, #352	@ tmp216, tmp216,
	cmp	r3, #256	@ ivtmp.1707,
	str	ip, [r1, #0]	@ tmp193, <variable>.non_intra_quantizer_matrix
	str	ip, [r0, #0]	@ tmp193, <variable>.non_intra_quantizer_matrix
	bne	.L300	@,
	mov	r0, #1	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L310:
	movw	r6, #:lower16:.LANCHOR1	@ tmp188,
	movt	r6, #:upper16:.LANCHOR1	@ tmp188,
	mov	r7, #0	@ i,
.L294:
	mov	r1, #8	@,
	mov	r0, r5	@, pBs
	ldrb	r8, [r6, r7]	@ zero_extendqisi2	@ D.39995, zigzag
	bl	BsGet	@
	add	ip, r7, #1	@ tmp197, i,
	mov	r1, #8	@,
	add	r2, r8, #19712	@ tmp174, D.39995,
	add	r7, ip, #1	@ i, tmp197,
	add	r3, r2, #24	@ tmp174, tmp174,
	str	r0, [r4, r3, asl #2]	@, <variable>.intra_quantizer_matrix
	mov	r0, r5	@, pBs
	ldrb	r8, [r6, ip]	@ zero_extendqisi2	@ D.39995, zigzag
	bl	BsGet	@
	cmp	r7, #64	@ i,
	add	r8, r8, #19712	@ tmp204, D.39995,
	add	r8, r8, #24	@ tmp204, tmp204,
	str	r0, [r4, r8, asl #2]	@, <variable>.intra_quantizer_matrix
	bne	.L294	@,
	mov	r0, r5	@, pBs
	mov	r1, #1	@,
	bl	BsGet	@
	cmp	r0, #1	@ D.40001,
	str	r0, [sl, #80]	@ D.40001, <variable>.load_non_intra_quantizer_matrix
	movne	r3, #0	@ ivtmp.1707,
	movne	ip, #16	@ tmp193,
	bne	.L300	@,
.L311:
	mov	r7, #0	@ i.1729,
.L298:
	mov	r1, #8	@,
	mov	r0, r5	@, pBs
	ldrb	r8, [r6, r7]	@ zero_extendqisi2	@ temp.1728, zigzag
	bl	BsGet	@
	add	r3, r7, #1	@ tmp195, i.1729,
	mov	r1, #8	@,
	add	ip, r8, #19712	@ tmp181, temp.1728,
	add	r7, r3, #1	@ i.1729, tmp195,
	add	r2, ip, #88	@ tmp181, tmp181,
	str	r0, [r4, r2, asl #2]	@, <variable>.non_intra_quantizer_matrix
	mov	r0, r5	@, pBs
	ldrb	r8, [r6, r3]	@ zero_extendqisi2	@ temp.1728, zigzag
	bl	BsGet	@
	cmp	r7, #64	@ i.1729,
	add	ip, r8, #19712	@ tmp212, temp.1728,
	add	r8, ip, #88	@ tmp212, tmp212,
	str	r0, [r4, r8, asl #2]	@, <variable>.non_intra_quantizer_matrix
	bne	.L298	@,
	mov	r0, #1	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	.fnend
	.size	sequence_header, .-sequence_header
	.align	2
	.global	next_start_code
	.type	next_start_code, %function
next_start_code:
	.fnstart
.LFB1546:
	@ args = 0, pretend = 0, frame = 16
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
	add	r4, r0, #78848	@ pBs, pCtx,
	add	r4, r4, #64	@ pBs, pBs,
	mov	r5, r0	@ pCtx, pCtx
	mov	r0, r4	@, pBs
	bl	BsToNextByte	@
	mov	r0, r4	@, pBs
	bl	BsGetNextBytePtr	@
	mov	r6, r0	@ pcode,
	mov	r0, r4	@, pBs
	bl	BsResidBits	@
	mov	r7, r0	@ D.39907,
	add	r2, r0, #7	@ tmp157, D.39907,
	cmp	r7, #0	@ D.39907,
	mov	r0, r6	@, pcode
	movlt	r7, r2	@ D.39907, tmp157
	mov	r1, r7, asr #3	@, D.39907,
	bl	MP2_SearchStartCode	@
	mov	r1, r0, asl #3	@ tmp159,,
	mov	r0, r4	@, pBs
	bl	BsLongSkip	@
	mov	r0, r4	@, pBs
	bl	BsResidBits	@
	add	r3, r0, #7	@ tmp162, D.39913,
	cmp	r0, #0	@ D.39913,
	movlt	r0, r3	@ D.39913, tmp162
	mov	r3, r0, asr #3	@ tmp163, D.39913,
	sub	r7, r3, #3	@ remain_byte, tmp163,
	cmp	r7, #0	@ remain_byte,
	ble	.L313	@,
	mov	r0, r4	@, pBs
	mov	r1, #24	@,
	and	r8, r3, #1	@ tmp233, tmp163,
	bl	BsShow	@
	cmp	r0, #1	@,
	beq	.L314	@,
	mov	r0, r4	@, pBs
	mov	r1, #8	@,
	bl	BsSkip	@
	mov	r6, #1	@ i,
	cmp	r7, r6	@ remain_byte, i
	ble	.L313	@,
	cmp	r8, #0	@ tmp233,
	beq	.L315	@,
	mov	r0, r4	@, pBs
	mov	r1, #24	@,
	bl	BsShow	@
	cmp	r0, r6	@,
	beq	.L314	@,
	mov	r0, r4	@, pBs
	mov	r1, #8	@,
	bl	BsSkip	@
	mov	r6, #2	@ i,
	cmp	r7, r6	@ remain_byte, i
	bgt	.L315	@,
	b	.L313	@
.L340:
	bl	BsSkip	@
	mov	r1, #24	@,
	mov	r0, r4	@, pBs
	bl	BsShow	@
	mov	r1, #8	@,
	cmp	r0, #1	@,
	mov	r0, r4	@, pBs
	beq	.L314	@,
	bl	BsSkip	@
	cmp	r7, r6	@ remain_byte, i
	ble	.L313	@,
.L315:
	mov	r1, #24	@,
	mov	r0, r4	@, pBs
	bl	BsShow	@
	add	r6, r6, #1	@ tmp234, i,
	mov	r1, #8	@,
	add	r6, r6, #1	@ i, tmp234,
	cmp	r0, #1	@,
	mov	r0, r4	@, pBs
	bne	.L340	@,
.L314:
	mov	r0, #1	@ D.39918,
.L318:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L313:
	movw	r6, #:lower16:78620	@ tmp164,
	movt	r6, #:upper16:78620	@ tmp164,
	ldrsb	r8, [r5, r6]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	cmp	r8, #0	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg,
	bne	.L316	@,
	movw	r7, #:lower16:78621	@ tmp166,
	movt	r7, #:upper16:78621	@ tmp166,
	ldrsb	r0, [r5, r7]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	cmp	r0, #0	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg,
	beq	.L316	@,
	movw	sl, #:lower16:78644	@ tmp168,
	movt	sl, #:upper16:78644	@ tmp168,
	ldr	r1, [r5, sl]	@ <variable>.CodecInfo.stMp2Packet.BsLength, <variable>.CodecInfo.stMp2Packet.BsLength
	cmp	r1, #0	@ <variable>.CodecInfo.stMp2Packet.BsLength,
	beq	.L316	@,
	mov	r0, #7	@,
	movw	r1, #:lower16:.LC23	@,
	movt	r1, #:upper16:.LC23	@,
	movw	r9, #:lower16:78640	@,
	movw	lr, #:lower16:78624	@ tmp174,
	movt	r9, #:upper16:78640	@,
	movt	lr, #:upper16:78624	@ tmp174,
	str	r9, [fp, #-48]	@, %sfp
	str	lr, [fp, #-56]	@,
	bl	dprint_vfmw	@
	ldr	r2, [fp, #-48]	@, %sfp
	movw	r9, #:lower16:78628	@ tmp171,
	ldr	ip, [fp, #-56]	@,
	movt	r9, #:upper16:78628	@ tmp171,
	ldr	r1, [r5, r2]	@ <variable>.CodecInfo.stMp2Packet.BsLength, <variable>.CodecInfo.stMp2Packet.BsLength
	mov	r2, #3	@,
	ldr	r3, [r5, ip]	@ <variable>.CodecInfo.stMp2Packet.BsVirAddr, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	ldr	r0, [r5, r9]	@ <variable>.CodecInfo.stMp2Packet.BsVirAddr, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	sub	r1, r1, #3	@ tmp176, <variable>.CodecInfo.stMp2Packet.BsLength,
	add	r1, r1, r3	@, tmp176, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	sub	r0, r0, #3	@, <variable>.CodecInfo.stMp2Packet.BsVirAddr,
	bl	memcpy	@
	ldr	r2, [fp, #-56]	@,
	ldr	r0, [r5, sl]	@ <variable>.CodecInfo.stMp2Packet.BsLength, <variable>.CodecInfo.stMp2Packet.BsLength
	movw	r3, #:lower16:78636	@ tmp187,
	ldr	r1, [r5, r9]	@ <variable>.CodecInfo.stMp2Packet.BsVirAddr, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	movt	r3, #:upper16:78636	@ tmp187,
	add	ip, r0, #3	@, <variable>.CodecInfo.stMp2Packet.BsLength,
	str	ip, [fp, #-52]	@, %sfp
	sub	r1, r1, #3	@ D.39939, <variable>.CodecInfo.stMp2Packet.BsVirAddr,
	str	r1, [r5, r2]	@ D.39939, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	ldr	r2, [fp, #-52]	@, %sfp
	movw	lr, #:lower16:78632	@ tmp192,
	ldr	r0, [fp, #-48]	@, %sfp
	movt	lr, #:upper16:78632	@ tmp192,
	ldr	ip, [r5, r3]	@, <variable>.CodecInfo.stMp2Packet.BsPhyAddr
	str	r8, [r5, r9]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	str	r2, [r5, r0]	@, <variable>.CodecInfo.stMp2Packet.BsLength
	sub	r0, ip, #3	@ D.39938,,
	str	r8, [r5, sl]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.BsLength
	str	r0, [r5, lr]	@ D.39938, <variable>.CodecInfo.stMp2Packet.BsPhyAddr
	mov	lr, #1	@,
	str	r8, [r5, r3]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.BsPhyAddr
	mov	r0, r4	@, pBs
	strb	lr, [r5, r6]	@, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	strb	r8, [r5, r7]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	bl	BsInit	@
	strb	r8, [r5, r6]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	mov	r0, r4	@, pBs
	mov	r6, #1	@,
	strb	r6, [r5, r7]	@, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	bl	BsToNextByte	@
	mov	r0, r4	@, pBs
	bl	BsGetNextBytePtr	@
	mov	r5, r0	@ pcode.1762,
	mov	r0, r4	@, pBs
	bl	BsResidBits	@
	mov	r3, r0	@ D.39941,
	add	r2, r0, #7	@ tmp215, D.39941,
	cmp	r3, #0	@ D.39941,
	mov	r0, r5	@, pcode.1762
	movlt	r3, r2	@ D.39941, tmp215
	mov	r1, r3, asr #3	@, D.39941,
	bl	MP2_SearchStartCode	@
	mov	r1, r0, asl #3	@ tmp217,,
	mov	r0, r4	@, pBs
	bl	BsLongSkip	@
	mov	r0, r4	@, pBs
	bl	BsResidBits	@
	cmp	r0, #0	@ D.39944,
	add	ip, r0, #7	@ tmp220, D.39944,
	movlt	r0, ip	@ D.39944, tmp220
	mov	r3, r0, asr #3	@ tmp221, D.39944,
	sub	r6, r3, #3	@ remain_byte.1766, tmp221,
	cmp	r6, #0	@ remain_byte.1766,
	ble	.L316	@,
	mov	r0, r4	@, pBs
	mov	r1, #24	@,
	and	r7, r3, #1	@ tmp229, tmp221,
	bl	BsShow	@
	cmp	r0, #1	@,
	beq	.L314	@,
	mov	r0, r4	@, pBs
	mov	r1, #8	@,
	bl	BsSkip	@
	mov	r5, #1	@ i.1761,
	cmp	r6, r5	@ remain_byte.1766, i.1761
	ble	.L316	@,
	cmp	r7, #0	@ tmp229,
	beq	.L317	@,
	mov	r0, r4	@, pBs
	mov	r1, #24	@,
	bl	BsShow	@
	cmp	r0, r5	@,
	beq	.L314	@,
	mov	r0, r4	@, pBs
	mov	r1, #8	@,
	bl	BsSkip	@
	mov	r5, #2	@ i.1761,
	cmp	r6, r5	@ remain_byte.1766, i.1761
	bgt	.L317	@,
	b	.L316	@
.L341:
	bl	BsSkip	@
	mov	r1, #24	@,
	mov	r0, r4	@, pBs
	bl	BsShow	@
	mov	r1, #8	@,
	cmp	r0, #1	@,
	mov	r0, r4	@, pBs
	beq	.L314	@,
	bl	BsSkip	@
	cmp	r6, r5	@ remain_byte.1766, i.1761
	ble	.L316	@,
.L317:
	mov	r1, #24	@,
	mov	r0, r4	@, pBs
	bl	BsShow	@
	add	r5, r5, #1	@ tmp230, i.1761,
	mov	r1, #8	@,
	add	r5, r5, #1	@ i.1761, tmp230,
	cmp	r0, #1	@,
	mov	r0, r4	@, pBs
	bne	.L341	@,
	b	.L314	@
.L316:
	mov	r0, #0	@ D.39918,
	b	.L318	@
	.fnend
	.size	next_start_code, .-next_start_code
	.align	2
	.global	MP2_GetUsrData
	.type	MP2_GetUsrData, %function
MP2_GetUsrData:
	.fnstart
.LFB1545:
	@ args = 0, pretend = 0, frame = 16
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
	add	r6, r0, #78848	@ pBs, pCtx,
	add	r6, r6, #64	@ pBs, pBs,
	mov	r4, r0	@ pCtx, pCtx
	mov	r0, r6	@, pBs
	bl	BsToNextByte	@
	mov	r0, r6	@, pBs
	bl	BsResidBits	@
	add	r9, r0, #7	@ tmp160, D.39807,
	cmp	r0, #0	@ D.39807,
	movlt	r0, r9	@ D.39807, tmp160
	mov	r9, r0, asr #3	@ RemainByte, D.39807,
	cmp	r9, #0	@ RemainByte,
	ble	.L343	@,
	sub	r2, r9, #1	@ tmp386, RemainByte,
	mov	r0, r6	@, pBs
	mov	r1, #24	@,
	and	r3, r2, #1	@, tmp386,
	str	r3, [fp, #-48]	@, %sfp
	bl	BsShow	@
	movw	sl, #:lower16:.LANCHOR2	@ tmp381,
	mov	r5, #0	@ cnt,
	movt	sl, #:upper16:.LANCHOR2	@ tmp381,
	movw	r8, #1023	@ tmp379,
	bic	r0, r0, #-16777216	@ tmp162,,
	cmp	r0, #1	@ tmp162,
	beq	.L344	@,
	mov	r0, r6	@, pBs
	mov	r1, #8	@,
	bl	BsGet	@
	mov	r5, #1	@ cnt,
	cmp	r9, r5	@ RemainByte, cnt
	mov	r7, r5	@ i, cnt
	strb	r0, [sl, #0]	@, g_tmpusd
	ble	.L348	@,
	ldr	lr, [fp, #-48]	@, %sfp
	cmp	lr, #0	@,
	beq	.L347	@,
	mov	r1, #24	@,
	mov	r0, r6	@, pBs
	bl	BsShow	@
	bic	r1, r0, #-16777216	@ tmp417,,
	cmp	r1, r5	@ tmp417,
	beq	.L344	@,
	mov	r0, r6	@, pBs
	mov	r1, #8	@,
	bl	BsGet	@
	add	r7, r5, r5	@ i, i,
	cmp	r9, r7	@ RemainByte, i
	strb	r0, [sl, r5]	@, g_tmpusd
	mov	r5, r7	@ cnt, i
	bgt	.L347	@,
	b	.L348	@
.L401:
	bl	BsGet	@
	strb	r0, [sl, r5]	@, g_tmpusd
	add	r5, r5, #1	@ cnt, cnt,
.L346:
	mov	r1, #24	@,
	mov	r0, r6	@, pBs
	bl	BsShow	@
	add	r7, r7, #1	@ tmp389, i,
	mov	r1, #8	@,
	bic	r3, r0, #-16777216	@ tmp395,,
	mov	r0, r6	@, pBs
	cmp	r3, #1	@ tmp395,
	beq	.L344	@,
	cmp	r5, r8	@ cnt, tmp379
	ble	.L392	@,
	mov	r0, r6	@, pBs
	mov	r1, #8	@,
	add	r7, r7, #1	@ i, tmp389,
	bl	BsGet	@
	cmp	r9, r7	@ RemainByte, i
	ble	.L348	@,
.L347:
	mov	r1, #24	@,
	mov	r0, r6	@, pBs
	bl	BsShow	@
	mov	r1, #8	@,
	bic	ip, r0, #-16777216	@ tmp391,,
	mov	r0, r6	@, pBs
	cmp	ip, #1	@ tmp391,
	beq	.L344	@,
	cmp	r5, r8	@ cnt, tmp379
	ble	.L401	@,
	mov	r0, r6	@, pBs
	mov	r1, #8	@,
	bl	BsGet	@
	b	.L346	@
.L392:
	bl	BsGet	@
	add	r7, r7, #1	@ i, tmp389,
	cmp	r9, r7	@ RemainByte, i
	strb	r0, [sl, r5]	@, g_tmpusd
	add	r5, r5, #1	@ cnt, cnt,
	bgt	.L347	@,
.L348:
	movw	r7, #:lower16:78620	@ tmp368,
	movt	r7, #:upper16:78620	@ tmp368,
	ldrsb	r8, [r4, r7]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	cmp	r8, #0	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg,
	bne	.L349	@,
	movw	sl, #:lower16:78621	@ tmp166,
	movt	sl, #:upper16:78621	@ tmp166,
	ldrsb	r1, [r4, sl]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	cmp	r1, #0	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg,
	beq	.L349	@,
	movw	r9, #:lower16:78644	@ tmp168,
	movt	r9, #:upper16:78644	@ tmp168,
	ldr	lr, [r4, r9]	@ <variable>.CodecInfo.stMp2Packet.BsLength, <variable>.CodecInfo.stMp2Packet.BsLength
	cmp	lr, #0	@ <variable>.CodecInfo.stMp2Packet.BsLength,
	bne	.L402	@,
.L349:
	mov	lr, #0	@,
	str	lr, [fp, #-48]	@, %sfp
	b	.L353	@
.L344:
	mov	r6, #1	@,
	str	r6, [fp, #-48]	@, %sfp
.L353:
	movw	r6, #:lower16:78700	@ tmp222,
	movt	r6, #:upper16:78700	@ tmp222,
	ldr	r2, [r4, r6]	@ D.39851, <variable>.CodecInfo.TotalUsrDatNum
	cmp	r2, #3	@ D.39851,
	ble	.L355	@,
	movw	r8, #:lower16:113648	@ tmp223,
	movw	sl, #:lower16:78684	@ tmp225,
	movt	r8, #:upper16:113648	@ tmp223,
	movt	sl, #:upper16:78684	@ tmp225,
	movw	r9, #:lower16:78688	@ tmp231,
	movt	r9, #:upper16:78688	@ tmp231,
	ldr	r1, [r4, sl]	@, <variable>.CodecInfo.pUsrDatArray
	movw	r7, #:lower16:78692	@ tmp237,
	ldr	r0, [r4, r8]	@, <variable>.ChanID
	movt	r7, #:upper16:78692	@ tmp237,
	str	r7, [fp, #-56]	@,
	bl	FreeUsdByDec	@
	mov	r7, #0	@ tmp228,
	ldr	r0, [r4, r8]	@, <variable>.ChanID
	str	r7, [r4, sl]	@ tmp228, <variable>.CodecInfo.pUsrDatArray
	movw	sl, #:lower16:78696	@ tmp243,
	ldr	r1, [r4, r9]	@, <variable>.CodecInfo.pUsrDatArray
	movt	sl, #:upper16:78696	@ tmp243,
	str	r7, [fp, #-60]	@ tmp12,
	bl	FreeUsdByDec	@
	str	r7, [r4, r9]	@ tmp228, <variable>.CodecInfo.pUsrDatArray
	ldr	r2, [fp, #-56]	@,
	ldr	r0, [r4, r8]	@, <variable>.ChanID
	ldr	r1, [r4, r2]	@, <variable>.CodecInfo.pUsrDatArray
	bl	FreeUsdByDec	@
	ldr	r3, [fp, #-56]	@,
	ldr	r0, [r4, r8]	@, <variable>.ChanID
	str	r7, [r4, r3]	@ tmp228, <variable>.CodecInfo.pUsrDatArray
	ldr	r1, [r4, sl]	@, <variable>.CodecInfo.pUsrDatArray
	bl	FreeUsdByDec	@
	str	r7, [r4, sl]	@ tmp228, <variable>.CodecInfo.pUsrDatArray
	str	r7, [r4, r6]	@ tmp228, <variable>.CodecInfo.TotalUsrDatNum
	ldr	r2, [fp, #-60]	@,
.L355:
	movw	lr, #:lower16:113648	@ tmp249,
	movt	lr, #:upper16:113648	@ tmp249,
	add	r6, r2, #19456	@ tmp370, prephitmp.1788,
	ldr	r0, [r4, lr]	@, <variable>.ChanID
	add	r6, r6, #214	@ tmp370, tmp370,
	bl	GetUsd	@
	movw	r2, #:lower16:78700	@ tmp257,
	movt	r2, #:upper16:78700	@ tmp257,
	add	r3, r4, r6, asl #2	@, tmp255, pCtx, tmp370,
	ldr	r2, [r4, r2]	@ temp.1817, <variable>.CodecInfo.TotalUsrDatNum
	add	r1, r2, #19456	@ tmp258, temp.1817,
	add	ip, r1, #214	@ tmp258, tmp258,
	add	r1, r4, ip, asl #2	@, tmp262, pCtx, tmp258,
	str	r0, [r3, #4]	@ D.39858, <variable>.CodecInfo.pUsrDatArray
	ldr	r1, [r1, #4]	@ tmp264, <variable>.CodecInfo.pUsrDatArray
	cmp	r1, #0	@ tmp264,
	beq	.L356	@,
	ldr	r7, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	movw	lr, #:lower16:78672	@ tmp275,
	movt	lr, #:upper16:78672	@ tmp275,
	movw	r2, #:lower16:79992	@ tmp292,
	movt	r2, #:upper16:79992	@ tmp292,
	movw	ip, #:lower16:113652	@ tmp302,
	ldrd	r8, [r7, #56]	@ <variable>.pts, <variable>.pstExtraData,
	mov	r7, #1056	@ tmp265,
	movt	ip, #:upper16:113652	@ tmp302,
	movw	r1, #:lower16:78668	@ tmp315,
	movt	r1, #:upper16:78668	@ tmp315,
	strd	r8, [r0, r7]	@ <variable>.pts, D.39858, tmp265
	ldr	r0, [r3, #4]	@ tmp270, <variable>.CodecInfo.pUsrDatArray
	ldr	lr, [r4, lr]	@ <variable>.CodecInfo.SeqCnt, <variable>.CodecInfo.SeqCnt
	str	lr, [r0, #1040]	@ <variable>.CodecInfo.SeqCnt, <variable>.seq_cnt
	ldr	r0, [r3, #4]	@ tmp279, <variable>.CodecInfo.pUsrDatArray
	str	r5, [r0, #1048]	@ cnt, <variable>.data_size
	ldr	lr, [r4, r2]	@ <variable>.pSyntaxInfNew, <variable>.pSyntaxInfNew
	ldr	r0, [r3, #4]	@ tmp286, <variable>.CodecInfo.pUsrDatArray
	ldrb	lr, [lr, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	strb	lr, [r0, #1024]	@ <variable>.picture_coding_type, <variable>.pic_coding_type
	ldr	lr, [r3, #4]	@ tmp297, <variable>.CodecInfo.pUsrDatArray
	ldr	ip, [r4, ip]	@ <variable>.numTotalFrame, <variable>.numTotalFrame
	str	ip, [lr, #1028]	@ <variable>.numTotalFrame, <variable>.pic_num_count
	ldr	r0, [r4, r2]	@ <variable>.pSyntaxInfNew, <variable>.pSyntaxInfNew
	ldr	r2, [r3, #4]	@ tmp306, <variable>.CodecInfo.pUsrDatArray
	ldrb	lr, [r0, #10]	@ zero_extendqisi2	@ <variable>.top_field_first, <variable>.top_field_first
	strb	lr, [r2, #1025]	@ <variable>.top_field_first, <variable>.top_field_first
	ldr	ip, [r4, r1]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	ldr	r1, [r3, #4]	@ tmp320, <variable>.CodecInfo.pUsrDatArray
	add	r3, r4, r6, asl #2	@, tmp338, pCtx, tmp370,
	tst	ip, #524288	@ <variable>.CodecInfo.StreamIntegrality,
	movne	ip, #3	@ tmp325,
	moveq	ip, #1	@ tmp333,
	str	ip, [r1, #1036]	@ tmp333, <variable>.from
	movw	r1, #:lower16:.LANCHOR2	@,
	ldr	r0, [r3, #4]	@ prephitmp.1790, <variable>.CodecInfo.pUsrDatArray
	movt	r1, #:upper16:.LANCHOR2	@,
	ldr	r2, [r0, #1048]	@ prephitmp.1792, <variable>.data_size
	cmp	r2, #1024	@ prephitmp.1792,
	movgt	r2, #1024	@ tmp340,
	strgt	r2, [r0, #1048]	@ tmp340, <variable>.data_size
	ldrgt	r0, [r3, #4]	@ prephitmp.1790, <variable>.CodecInfo.pUsrDatArray
	ldrgt	r2, [r0, #1048]	@ prephitmp.1792, <variable>.data_size
	bl	memcpy	@
	movw	r0, #:lower16:g_event_report	@ tmp352,
	movt	r0, #:upper16:g_event_report	@ tmp352,
	ldr	ip, [r0, #0]	@ g_event_report.489, g_event_report
	cmp	ip, #0	@ g_event_report.489,
	beq	.L360	@,
	add	r6, r4, r6, asl #2	@, tmp359, pCtx, tmp370,
	movw	r0, #:lower16:113648	@ tmp353,
	movt	r0, #:upper16:113648	@ tmp353,
	mov	r1, #6	@,
	ldr	r2, [r6, #4]	@, <variable>.CodecInfo.pUsrDatArray
	mov	r3, #1072	@,
	ldr	r0, [r4, r0]	@, <variable>.ChanID
	blx	ip	@ g_event_report.489
.L360:
	movw	r3, #:lower16:78700	@ tmp362,
	movt	r3, #:upper16:78700	@ tmp362,
	ldr	r2, [r4, r3]	@ <variable>.CodecInfo.TotalUsrDatNum, <variable>.CodecInfo.TotalUsrDatNum
	add	r1, r2, #1	@ tmp365, <variable>.CodecInfo.TotalUsrDatNum,
	str	r1, [r4, r3]	@ tmp365, <variable>.CodecInfo.TotalUsrDatNum
.L361:
	ldr	r0, [fp, #-48]	@, %sfp
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L356:
	mov	r0, r1	@, tmp264
	movw	r1, #:lower16:.LC24	@,
	movt	r1, #:upper16:.LC24	@,
	bl	dprint_vfmw	@
	b	.L361	@
.L402:
	movw	r0, #:lower16:78640	@,
	movw	r1, #:lower16:.LC23	@,
	movt	r0, #:upper16:78640	@,
	movt	r1, #:upper16:.LC23	@,
	str	r0, [fp, #-52]	@, %sfp
	mov	r0, r8	@, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	movw	ip, #:lower16:78628	@ tmp171,
	movw	r3, #:lower16:78624	@,
	movt	ip, #:upper16:78628	@ tmp171,
	movt	r3, #:upper16:78624	@,
	str	ip, [fp, #-56]	@,
	str	r3, [fp, #-48]	@, %sfp
	bl	dprint_vfmw	@
	ldr	r2, [fp, #-52]	@, %sfp
	ldr	lr, [fp, #-56]	@,
	ldr	r3, [fp, #-48]	@, %sfp
	ldr	r1, [r4, r2]	@ <variable>.CodecInfo.stMp2Packet.BsLength, <variable>.CodecInfo.stMp2Packet.BsLength
	mov	r2, #3	@,
	ldr	r0, [r4, lr]	@ <variable>.CodecInfo.stMp2Packet.BsVirAddr, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	ldr	ip, [r4, r3]	@ <variable>.CodecInfo.stMp2Packet.BsVirAddr, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	sub	lr, r1, #3	@ tmp176, <variable>.CodecInfo.stMp2Packet.BsLength,
	sub	r0, r0, #3	@, <variable>.CodecInfo.stMp2Packet.BsVirAddr,
	add	r1, lr, ip	@, tmp176, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	bl	memcpy	@
	ldr	r3, [fp, #-56]	@,
	ldr	r0, [fp, #-48]	@, %sfp
	movw	ip, #:lower16:78636	@ tmp187,
	movt	ip, #:upper16:78636	@ tmp187,
	ldr	r2, [r4, r9]	@ <variable>.CodecInfo.stMp2Packet.BsLength, <variable>.CodecInfo.stMp2Packet.BsLength
	ldr	r1, [r4, r3]	@ <variable>.CodecInfo.stMp2Packet.BsVirAddr, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	movw	lr, #:lower16:78632	@ tmp193,
	movt	lr, #:upper16:78632	@ tmp193,
	add	r2, r2, #3	@ D.39837, <variable>.CodecInfo.stMp2Packet.BsLength,
	sub	r1, r1, #3	@ D.39840, <variable>.CodecInfo.stMp2Packet.BsVirAddr,
	str	r1, [r4, r0]	@ D.39840, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	ldr	r0, [fp, #-52]	@, %sfp
	str	r8, [r4, r3]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	ldr	r3, [r4, ip]	@, <variable>.CodecInfo.stMp2Packet.BsPhyAddr
	str	r2, [r4, r0]	@ D.39837, <variable>.CodecInfo.stMp2Packet.BsLength
	sub	r0, r3, #3	@ D.39839,,
	str	r8, [r4, r9]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.BsLength
	str	r0, [r4, lr]	@ D.39839, <variable>.CodecInfo.stMp2Packet.BsPhyAddr
	mov	r0, r6	@, pBs
	str	r8, [r4, ip]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.BsPhyAddr
	mov	ip, #1	@,
	strb	ip, [r4, r7]	@, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	strb	r8, [r4, sl]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	bl	BsInit	@
	strb	r8, [r4, r7]	@ <variable>.CodecInfo.stMp2Packet.IsLastSeg, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	mov	r0, #1	@,
	strb	r0, [r4, sl]	@, <variable>.CodecInfo.stMp2Packet.IsLastSeg
	mov	r0, r6	@, pBs
	bl	BsToNextByte	@
	mov	r0, r6	@, pBs
	bl	BsResidBits	@
	add	r9, r0, #7	@ tmp216, D.39841,
	cmp	r0, #0	@ D.39841,
	movlt	r0, r9	@ D.39841, tmp216
	mov	r3, r0, asr #3	@ tmp217, D.39841,
	sub	r9, r3, #3	@ RemainByte.1812, tmp217,
	cmp	r9, #0	@ RemainByte.1812,
	ble	.L349	@,
	mov	r1, #24	@,
	mov	r0, r6	@, pBs
	and	r8, r3, #1	@, tmp217,
	str	r8, [fp, #-48]	@, %sfp
	bl	BsShow	@
	movw	sl, #:lower16:.LANCHOR2	@ tmp377,
	movw	r8, #1023	@ tmp375,
	movt	sl, #:upper16:.LANCHOR2	@ tmp377,
	bic	r1, r0, #-16777216	@ tmp218,,
	cmp	r1, #1	@ tmp218,
	beq	.L344	@,
	cmp	r5, r8	@ cnt, tmp375
	ble	.L386	@,
	mov	r0, r6	@, pBs
	mov	r1, #8	@,
	bl	BsGet	@
.L387:
	mov	r7, #1	@ i.1815,
	cmp	r9, r7	@ RemainByte.1812, i.1815
	ble	.L349	@,
	ldr	ip, [fp, #-48]	@, %sfp
	cmp	ip, #0	@,
	beq	.L352	@,
	mov	r0, r6	@, pBs
	mov	r1, #24	@,
	bl	BsShow	@
	bic	r0, r0, #-16777216	@ tmp406,,
	cmp	r0, r7	@ tmp406,
	beq	.L344	@,
	cmp	r5, r8	@ cnt, tmp375
	bgt	.L400	@,
	mov	r0, r6	@, pBs
	mov	r1, #8	@,
	bl	BsGet	@
	strb	r0, [sl, r5]	@, g_tmpusd
	add	r5, r5, #1	@ cnt, cnt,
.L391:
	add	r7, r7, #1	@ i.1815, tmp385,
	cmp	r9, r7	@ RemainByte.1812, i.1815
	ble	.L349	@,
.L352:
	mov	r1, #24	@,
	mov	r0, r6	@, pBs
	bl	BsShow	@
	mov	r1, #8	@,
	bic	r2, r0, #-16777216	@ tmp397,,
	mov	r0, r6	@, pBs
	cmp	r2, #1	@ tmp397,
	beq	.L344	@,
	cmp	r5, r8	@ cnt, tmp375
	bgt	.L350	@,
	bl	BsGet	@
	strb	r0, [sl, r5]	@, g_tmpusd
	add	r5, r5, #1	@ cnt, cnt,
.L351:
	mov	r1, #24	@,
	mov	r0, r6	@, pBs
	bl	BsShow	@
	add	r7, r7, #1	@ tmp385, i.1815,
	mov	r1, #8	@,
	bic	ip, r0, #-16777216	@ tmp401,,
	mov	r0, r6	@, pBs
	cmp	ip, #1	@ tmp401,
	beq	.L344	@,
	cmp	r5, r8	@ cnt, tmp375
	bgt	.L400	@,
	bl	BsGet	@
	add	r7, r7, #1	@ i.1815, tmp385,
	cmp	r9, r7	@ RemainByte.1812, i.1815
	strb	r0, [sl, r5]	@, g_tmpusd
	add	r5, r5, #1	@ cnt, cnt,
	bgt	.L352	@,
	b	.L349	@
.L400:
	mov	r0, r6	@, pBs
	mov	r1, #8	@,
	bl	BsGet	@
	b	.L391	@
.L350:
	mov	r0, r6	@, pBs
	mov	r1, #8	@,
	bl	BsGet	@
	b	.L351	@
.L343:
	mov	r5, #0	@ cnt,
	b	.L348	@
.L386:
	mov	r0, r6	@, pBs
	mov	r1, #8	@,
	bl	BsGet	@
	strb	r0, [sl, r5]	@, g_tmpusd
	add	r5, r5, #1	@ cnt, cnt,
	b	.L387	@
	.fnend
	.size	MP2_GetUsrData, .-MP2_GetUsrData
	.align	2
	.global	MP2_GetImageBuffer
	.type	MP2_GetImageBuffer, %function
MP2_GetImageBuffer:
	.fnstart
.LFB1542:
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
	movw	r5, #:lower16:113648	@ tmp145,
	movt	r5, #:upper16:113648	@ tmp145,
	mov	r4, r0	@ pCtx, pCtx
	mov	r1, #1	@,
	movw	r6, #:lower16:78752	@ tmp147,
	ldr	r0, [r0, r5]	@, <variable>.ChanID
	movt	r6, #:upper16:78752	@ tmp147,
	bl	FSP_NewLogicFs	@
	cmp	r0, #0	@ D.39695,
	mov	r1, r0	@ D.39695,
	str	r0, [r4, r6]	@ D.39695, <variable>.CodecInfo.CurFsID
	blt	.L410	@,
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	bl	FSP_GetLogicFs	@
	subs	r5, r0, #0	@ pLf,
	beq	.L411	@,
	ldr	r2, [r4, r6]	@, <variable>.CodecInfo.CurFsID
	mov	r0, #18	@,
	movw	r1, #:lower16:.LC27	@,
	movt	r1, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	ldr	r2, [r5, #512]	@ D.39720, <variable>.pstDecodeFs
	cmp	r2, #0	@ D.39720,
	beq	.L408	@,
	ldr	r3, [r5, #516]	@ D.39723, <variable>.pstDispOutFs
	cmp	r3, #0	@ D.39723,
	beq	.L408	@,
	ldr	ip, [r5, #520]	@ D.39726, <variable>.pstTfOutFs
	cmp	ip, #0	@ D.39726,
	beq	.L408	@,
	ldr	ip, [ip, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	mov	r0, #18	@,
	ldr	r2, [r2, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	movw	r1, #:lower16:.LC28	@,
	ldr	r3, [r3, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	movt	r1, #:upper16:.LC28	@,
	str	ip, [sp, #0]	@ <variable>.PhyAddr,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.39714,
.L406:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L408:
	mov	r0, #1	@ D.39714,
	b	.L406	@
.L410:
	movw	r7, #:lower16:78748	@ tmp151,
	movt	r7, #:upper16:78748	@ tmp151,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC25	@,
	movt	r1, #:upper16:.LC25	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r4, r7]	@, <variable>.CodecInfo.BwdFsID
	bl	FSP_GetFsImagePtr	@
	subs	r6, r0, #0	@ pImg,
	beq	.L405	@,
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	movw	sl, #:lower16:78744	@ tmp175,
	ldr	r1, [r6, #212]	@, <variable>.p_usrdat
	movt	sl, #:upper16:78744	@ tmp175,
	bl	FreeUsdByDec	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r6, #216]	@, <variable>.p_usrdat
	mov	r8, #0	@ tmp165,
	bl	FreeUsdByDec	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r6, #220]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r6, #224]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	str	r8, [r6, #224]	@ tmp165, <variable>.p_usrdat
	str	r8, [r6, #212]	@ tmp165, <variable>.p_usrdat
	mov	r2, #1	@,
	str	r8, [r6, #216]	@ tmp165, <variable>.p_usrdat
	str	r8, [r6, #220]	@ tmp165, <variable>.p_usrdat
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r4, r7]	@, <variable>.CodecInfo.BwdFsID
	bl	FSP_ClearLogicFs	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r4, sl]	@, <variable>.CodecInfo.FwdFsID
	mov	r2, #1	@,
	bl	FSP_ClearLogicFs	@
	str	r8, [r4, r7]	@ tmp165, <variable>.CodecInfo.BwdFsID
	str	r8, [r4, sl]	@ tmp165, <variable>.CodecInfo.FwdFsID
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	bl	FSP_GetFspType	@
	cmp	r0, r8	@,
	bne	.L412	@,
.L405:
	movw	r2, #:lower16:78708	@ tmp187,
	movw	r3, #:lower16:113648	@ tmp189,
	movt	r2, #:upper16:78708	@ tmp187,
	movt	r3, #:upper16:113648	@ tmp189,
	add	r1, r4, #79872	@, pCtx,
	mov	r5, #0	@ tmp188,
	add	r1, r1, #128	@,,
	str	r5, [r4, r2]	@ tmp188, <variable>.CodecInfo.RefNum
	ldr	r0, [r4, r3]	@, <variable>.ChanID
	bl	FSP_ClearNotInVoQueue	@
	mov	r0, r5	@ D.39714, tmp188
	b	.L406	@
.L412:
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	bl	FSP_GetNullLogicFs	@
	str	r0, [r4, r7]	@ D.39712, <variable>.CodecInfo.BwdFsID
	str	r0, [r4, sl]	@ D.39712, <variable>.CodecInfo.FwdFsID
	b	.L405	@
.L411:
	movw	r1, #:lower16:.LC26	@,
	movw	r2, #1771	@,
	movt	r1, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mov	r0, r5	@ D.39714, pLf
	b	.L406	@
	.fnend
	.size	MP2_GetImageBuffer, .-MP2_GetImageBuffer
	.align	2
	.global	MP2_SetImgFormat
	.type	MP2_SetImgFormat, %function
MP2_SetImgFormat:
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
	movw	r1, #:lower16:113648	@ tmp161,
	movw	r2, #:lower16:78752	@ tmp163,
	movt	r1, #:upper16:113648	@ tmp161,
	movt	r2, #:upper16:78752	@ tmp163,
	mov	r6, r0	@ pCtx, pCtx
	movw	r3, #:lower16:79992	@ tmp160,
	movt	r3, #:upper16:79992	@ tmp160,
	ldr	r0, [r0, r1]	@, <variable>.ChanID
	ldr	r1, [r6, r2]	@, <variable>.CodecInfo.CurFsID
	ldr	r5, [r6, r3]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	bl	FSP_GetFsImagePtr	@
	subs	r4, r0, #0	@ pImg,
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	ldrb	ip, [r5, #22]	@ zero_extendqisi2	@ D.39489, <variable>.picture_coding_type
	ldrb	lr, [r5, #27]	@ zero_extendqisi2	@ D.39495, <variable>.progressive_sequence
	cmp	ip, #4	@ D.39489,
	ldr	r8, [r5, #128]	@ vfmt, <variable>.video_format
	subne	ip, ip, #1	@ tmp165, D.39489,
	ldr	r3, [r4, #160]	@ D.39496, <variable>.format
	moveq	ip, #0	@ prephitmp.1892,
	andne	ip, ip, #3	@ prephitmp.1892, tmp165,
	cmp	lr, #0	@ D.39495,
	ldrb	r7, [r5, #9]	@ zero_extendqisi2	@ D.39498, <variable>.picture_structure
	movne	r0, #4096	@ prephitmp.1918,
	bne	.L418	@,
	cmp	r7, #3	@ D.39498,
	beq	.L433	@,
	movw	r2, #:lower16:78680	@ tmp168,
	movt	r2, #:upper16:78680	@ tmp168,
	ldr	r0, [r6, r2]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	cmp	r0, #0	@ <variable>.CodecInfo.Second_Field,
	bne	.L420	@,
	cmp	r7, #1	@ D.39498,
	movne	r0, #0	@, tmp172
	moveq	r0, #1	@, tmp172
	mov	r0, r0, asl #12	@ prephitmp.1918, tmp172,
.L418:
	movw	r2, #:lower16:79992	@ tmp177,
	movt	r2, #:upper16:79992	@ tmp177,
	orr	r3, r7, r3, lsr #10	@, tmp192, D.39498, D.39496,
	and	r8, r8, #3	@ tmp189, vfmt,
	ldr	r2, [r6, r2]	@ <variable>.pSyntaxInfNew, <variable>.pSyntaxInfNew
	and	r3, r3, #3	@ tmp193, tmp192,
	ldr	r2, [r2, #84]	@ <variable>.aspect_ratio_information, <variable>.aspect_ratio_information
	str	ip, [r4, #156]	@ prephitmp.1892, <variable>.bottom_fld_type
	sub	r2, r2, #1	@ D.41115, <variable>.aspect_ratio_information,
	str	ip, [r4, #152]	@ prephitmp.1892, <variable>.top_fld_type
	cmp	r2, #2	@ D.41115,
	movwls	r1, #:lower16:.LANCHOR0	@ tmp179,
	movtls	r1, #:upper16:.LANCHOR0	@ tmp179,
	addls	r2, r1, r2, asl #2	@, tmp182, tmp179, D.41115,
	movhi	r1, #0	@ prephitmp.1919,
	movhi	r2, r1	@ prephitmp.1921, prephitmp.1919
	ldrls	r1, [r2, #128]	@ prephitmp.1919, CSWTCH.528
	andls	r2, r1, #7	@ pretmp.1920, prephitmp.1919,
	movls	r2, r2, asl #14	@ prephitmp.1921, pretmp.1920,
	cmp	lr, #0	@ D.39495,
	moveq	lr, #256	@ tmp188,
	movne	lr, #0	@ tmp188,
	orr	lr, lr, r8, asl #5	@, tmp191, tmp188, tmp189,
	orr	r3, lr, r3, asl #10	@, tmp195, tmp191, tmp193,
	orr	r3, r3, ip	@ tmp196, tmp195, prephitmp.1892
	orr	ip, r3, r0	@ tmp197, tmp196, prephitmp.1918
	mov	r0, r4	@, pImg
	orr	lr, ip, r2	@ tmp198, tmp197, prephitmp.1921
	str	lr, [r4, #160]	@ tmp198, <variable>.format
	bl	SetAspectRatio	@
	mov	r3, #3	@ tmp199,
	str	r3, [r4, #380]	@ tmp199, <variable>.ImageDnr.video_standard
	mov	r1, #1	@ tmp202,
	ldrb	ip, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	mov	r2, #1	@ tmp209,
	strb	r1, [r4, #375]	@ tmp202, <variable>.ImageDnr.use_pic_qp_en
	cmp	ip, #3	@ <variable>.picture_structure,
	movne	r1, #4	@ iftmp.475,
	moveq	r1, #0	@ iftmp.475,
	strb	r1, [r4, #368]	@ iftmp.475, <variable>.ImageDnr.pic_structure
	ldr	r0, [r6, #4]	@ D.39536, <variable>.pMp2DecParam
	cmp	r0, #0	@ D.39536,
	streqb	r0, [r4, #375]	@ D.39536, <variable>.ImageDnr.use_pic_qp_en
	ldrneb	r0, [r0, #144]	@ zero_extendqisi2	@ prephitmp.1893, <variable>.EstmatedPicQp
	moveq	ip, #32	@ tmp208,
	strb	r2, [r4, #373]	@ tmp209, <variable>.ImageDnr.chroma_format_idc
	moveq	r0, ip	@ prephitmp.1893, tmp208
	streq	ip, [r4, #384]	@ tmp208, <variable>.ImageDnr.QP_Y
	strne	r0, [r4, #384]	@ prephitmp.1893, <variable>.ImageDnr.QP_Y
	str	r0, [r4, #388]	@ prephitmp.1893, <variable>.ImageDnr.QP_U
	str	r0, [r4, #392]	@ prephitmp.1893, <variable>.ImageDnr.QP_V
	ldr	r3, [r5, #72]	@ <variable>.frame_rate, <variable>.frame_rate
	str	r3, [r4, #188]	@ <variable>.frame_rate, <variable>.frame_rate
	ldr	r3, [r5, #48]	@ prephitmp.1894, <variable>.horizontal_size
	str	r3, [r4, #164]	@ prephitmp.1894, <variable>.image_width
	ldr	r2, [r5, #52]	@ D.39546, <variable>.vertical_size
	str	r2, [r4, #168]	@ D.39546, <variable>.image_height
	ldr	r1, [r6, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	ip, [r1, #32]	@ <variable>.eCapLevel, <variable>.eCapLevel
	cmp	ip, #25	@ <variable>.eCapLevel,
	movne	r2, r3	@ <variable>.image_width, prephitmp.1894
	beq	.L434	@,
.L427:
	ldr	r1, [r4, #168]	@ <variable>.image_height, <variable>.image_height
	mov	ip, r3, lsr #1	@ tmp226, prephitmp.1894,
	str	ip, [r4, #180]	@ tmp226, <variable>.disp_center_x
	mov	r3, r1, lsr #1	@ tmp228, <variable>.image_height,
	str	r3, [r4, #184]	@ tmp228, <variable>.disp_center_y
	ldr	r3, [r5, #148]	@ D.39578, <variable>.display_horizontal_size
	cmp	r3, #0	@ D.39578,
	beq	.L428	@,
	ldr	lr, [r5, #152]	@ <variable>.display_vertical_size, <variable>.display_vertical_size
	cmp	lr, #0	@ <variable>.display_vertical_size,
	beq	.L428	@,
	cmp	r2, r3	@ <variable>.image_width, D.39578
	strls	r2, [r4, #172]	@, <variable>.image_width, <variable>.disp_width
	strhi	r3, [r4, #172]	@, D.39578, <variable>.disp_width
	ldr	r2, [r5, #152]	@ <variable>.display_vertical_size, <variable>.display_vertical_size
	cmp	r1, r2	@ <variable>.image_height, <variable>.display_vertical_size
	strls	r1, [r4, #176]	@, <variable>.image_height, <variable>.disp_height
	strhi	r2, [r4, #176]	@, <variable>.display_vertical_size, <variable>.disp_height
	b	.L429	@
.L428:
	str	r2, [r4, #172]	@ <variable>.image_width, <variable>.disp_width
	str	r1, [r4, #176]	@ <variable>.image_height, <variable>.disp_height
.L429:
	ldrb	lr, [r5, #27]	@ zero_extendqisi2	@ <variable>.progressive_sequence, <variable>.progressive_sequence
	mov	r0, r6	@, pCtx
	str	lr, [r4, #476]	@ <variable>.progressive_sequence, <variable>.optm_inf.IsProgressiveSeq
	ldrb	ip, [r5, #18]	@ zero_extendqisi2	@ <variable>.progressive_frame, <variable>.progressive_frame
	str	ip, [r4, #480]	@ <variable>.progressive_frame, <variable>.optm_inf.IsProgressiveFrm
	ldr	r3, [r5, #144]	@ <variable>.matrix_coefficients, <variable>.matrix_coefficients
	str	r3, [r4, #488]	@ <variable>.matrix_coefficients, <variable>.optm_inf.MatrixCoef
	bl	MP2_CalcRealEncFrameRate	@
	movw	r0, #:lower16:78836	@ tmp240,
	movt	r0, #:upper16:78836	@ tmp240,
	ldr	r1, [r6, r0]	@ <variable>.CodecInfo.RealFrmRate, <variable>.CodecInfo.RealFrmRate
	str	r1, [r4, #484]	@ <variable>.CodecInfo.RealFrmRate, <variable>.optm_inf.RealFrmRate
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L420:
	subs	r2, r7, #1	@ tmp175, D.39498,
	movne	r2, #1	@ tmp175
	mov	r0, r2, asl #12	@ prephitmp.1918, tmp175,
	b	.L418	@
.L433:
	ldrb	r2, [r5, #10]	@ zero_extendqisi2	@ <variable>.top_field_first, <variable>.top_field_first
	and	r0, r2, #1	@ tmp167, <variable>.top_field_first,
	mov	r0, r0, asl #12	@ prephitmp.1918, tmp167,
	b	.L418	@
.L434:
	ldr	r1, [r4, #192]	@ D.39551, <variable>.image_stride
	add	r0, r2, #15	@ tmp215, D.39546,
	ldr	r3, [r4, #104]	@ <variable>.luma_phy_addr, <variable>.luma_phy_addr
	mov	r2, r0, lsr #4	@ tmp216, tmp215,
	ldr	r0, [r4, #32]	@ <variable>.luma_vir_addr, <variable>.luma_vir_addr
	mov	lr, r1, asl #4	@ tmp214, D.39551,
	add	ip, r3, r1	@ tmp221, <variable>.luma_phy_addr, D.39551
	str	ip, [r4, #96]	@ tmp221, <variable>.btm_luma_phy_addr
	mul	r2, r2, lr	@ D.39557, tmp216, tmp214
	str	r3, [r4, #120]	@ <variable>.luma_phy_addr, <variable>.luma_2d_phy_addr
	str	r0, [r4, #48]	@ <variable>.luma_vir_addr, <variable>.luma_2d_vir_addr
	str	r3, [r4, #88]	@ <variable>.luma_phy_addr, <variable>.top_luma_phy_addr
	add	ip, r2, r3	@ tmp218, D.39557, <variable>.luma_phy_addr
	add	lr, r0, r2	@ tmp220, <variable>.luma_vir_addr, D.39557
	str	ip, [r4, #108]	@ tmp218, <variable>.chrom_phy_addr
	add	r0, ip, r1	@ tmp222, tmp218, D.39551
	str	lr, [r4, #36]	@ tmp220, <variable>.chrom_vir_addr
	str	r0, [r4, #100]	@ tmp222, <variable>.btm_chrom_phy_addr
	mov	r0, ip	@, tmp218
	str	ip, [r4, #92]	@ tmp218, <variable>.top_chrom_phy_addr
	bl	MEM_Phy2Vir	@
	ldr	r2, [r4, #164]	@ <variable>.image_width, <variable>.image_width
	ldr	r1, [r4, #92]	@ <variable>.top_chrom_phy_addr, <variable>.top_chrom_phy_addr
	mov	r3, r2	@ prephitmp.1894, <variable>.image_width
	str	r1, [r4, #124]	@ <variable>.top_chrom_phy_addr, <variable>.chrom_2d_phy_addr
	str	r0, [r4, #52]	@, <variable>.chrom_2d_vir_addr
	b	.L427	@
	.fnend
	.size	MP2_SetImgFormat, .-MP2_SetImgFormat
	.align	2
	.global	MPEG2DEC_VDMPostProc
	.type	MPEG2DEC_VDMPostProc, %function
MPEG2DEC_VDMPostProc:
	.fnstart
.LFB1566:
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
	ldrb	ip, [r0, #152]	@ zero_extendqisi2	@ <variable>.Mp2DecParam.EstmatedPicQp, <variable>.Mp2DecParam.EstmatedPicQp
	mov	r4, r0	@ pCtx, pCtx
	mov	r2, r1	@, ErrRatio
	mov	r7, r1	@ ErrRatio, ErrRatio
	movw	r8, #:lower16:79992	@ tmp160,
	mov	r1, #78848	@ tmp161,
	movt	r8, #:upper16:79992	@ tmp160,
	strb	ip, [r4, r1]	@ <variable>.Mp2DecParam.EstmatedPicQp, <variable>.CodecInfo.EstmatedPicQp
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC29	@,
	movt	r1, #:upper16:.LC29	@,
	ldr	r5, [r4, r8]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	bl	dprint_vfmw	@
	mov	r0, r4	@, pCtx
	movw	r8, #:lower16:113648	@ tmp166,
	bl	MP2_RecordVFMWState	@
	movt	r8, #:upper16:113648	@ tmp166,
	mov	r0, r4	@, pCtx
	movw	r6, #:lower16:78752	@ tmp168,
	movt	r6, #:upper16:78752	@ tmp168,
	bl	MP2_ClearCurPic	@
	add	r0, r4, #8	@, pCtx,
	movw	r1, #45320	@,
	bl	__memzero	@
	ldr	r1, [r4, r6]	@, <variable>.CodecInfo.CurFsID
	ldr	r0, [r4, r8]	@, <variable>.ChanID
	bl	FSP_GetFsImagePtr	@
	movw	r2, #:lower16:78748	@ tmp172,
	movt	r2, #:upper16:78748	@ tmp172,
	ldr	r1, [r4, r2]	@, <variable>.CodecInfo.BwdFsID
	mov	r6, r0	@ pCurImg,
	ldr	r0, [r4, r8]	@, <variable>.ChanID
	bl	FSP_GetFsImagePtr	@
	movw	r3, #:lower16:78744	@ tmp176,
	movt	r3, #:upper16:78744	@ tmp176,
	ldr	r1, [r4, r3]	@, <variable>.CodecInfo.FwdFsID
	mov	sl, r0	@ pBwdImg,
	ldr	r0, [r4, r8]	@, <variable>.ChanID
	bl	FSP_GetFsImagePtr	@
	cmp	r6, #0	@ pCurImg,
	mov	ip, r0	@ pFwdImg,
	beq	.L462	@,
	ldrb	r0, [r5, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	cmp	r7, #0	@ ErrRatio,
	movw	lr, #45328	@ tmp179,
	movlt	r7, #0	@ iftmp.513,
	strb	r0, [r4, lr]	@ <variable>.picture_coding_type, <variable>.CodecInfo.LastDecPicCodingType
	blt	.L439	@,
	cmp	r7, #100	@ ErrRatio,
	movge	r7, #100	@ iftmp.513,
.L439:
	str	r7, [r6, #200]	@ iftmp.513, <variable>.error_level
	ldrb	r3, [r5, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	cmp	r3, #3	@ <variable>.picture_coding_type,
	beq	.L440	@,
	ldr	r1, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	r2, [r1, #0]	@ <variable>.s32RefErrThr, <variable>.s32RefErrThr
	cmp	r7, r2	@ iftmp.513, <variable>.s32RefErrThr
	bhi	.L463	@,
.L440:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC31	@,
	movt	r1, #:upper16:.LC31	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, pCtx
	bl	MP2_SetImgFormat	@
	ldrb	r0, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	cmp	r0, #3	@ <variable>.picture_structure,
	beq	.L448	@,
	movw	lr, #:lower16:78680	@ tmp243,
	movt	lr, #:upper16:78680	@ tmp243,
	ldr	ip, [r4, lr]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	cmp	ip, #1	@ <variable>.CodecInfo.Second_Field,
	movne	r0, #1	@ D.40591,
	beq	.L448	@,
.L437:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L448:
	movw	r3, #:lower16:78684	@ tmp227,
	movt	r3, #:upper16:78684	@ tmp227,
	movw	r0, #:lower16:78684	@ tmp230,
	movw	lr, #:lower16:78688	@ tmp232,
	ldr	r1, [r4, r3]	@ temp.2005, <variable>.CodecInfo.pUsrDatArray
	movt	lr, #:upper16:78688	@ tmp232,
	movt	r0, #:upper16:78684	@ tmp230,
	mov	ip, #0	@ tmp231,
	cmp	r1, #0	@ temp.2005,
	strne	r1, [r6, #212]	@ temp.2005, <variable>.p_usrdat
	movne	r1, #0	@ tmp229,
	strne	r1, [r4, r3]	@ tmp229, <variable>.CodecInfo.pUsrDatArray
	str	ip, [r4, r0]	@ tmp231, <variable>.CodecInfo.pUsrDatArray
	movw	r3, #:lower16:78688	@ tmp235,
	ldr	r2, [r4, lr]	@ temp.2007, <variable>.CodecInfo.pUsrDatArray
	movt	r3, #:upper16:78688	@ tmp235,
	movw	r0, #:lower16:78692	@ tmp237,
	movt	r0, #:upper16:78692	@ tmp237,
	cmp	r2, ip	@ temp.2007,
	strne	r2, [r6, #216]	@ temp.2007, <variable>.p_usrdat
	strne	ip, [r4, lr]	@ tmp231, <variable>.CodecInfo.pUsrDatArray
	mov	lr, #0	@ tmp236,
	str	lr, [r4, r3]	@ tmp236, <variable>.CodecInfo.pUsrDatArray
	movw	ip, #:lower16:78692	@ tmp240,
	ldr	r1, [r4, r0]	@ temp.2008, <variable>.CodecInfo.pUsrDatArray
	movt	ip, #:upper16:78692	@ tmp240,
	movw	r3, #:lower16:78696	@ tmp242,
	movt	r3, #:upper16:78696	@ tmp242,
	cmp	r1, lr	@ temp.2008,
	strne	r1, [r6, #220]	@ temp.2008, <variable>.p_usrdat
	mov	r1, #0	@ tmp241,
	strne	lr, [r4, r0]	@ tmp236, <variable>.CodecInfo.pUsrDatArray
	str	r1, [r4, ip]	@ tmp241, <variable>.CodecInfo.pUsrDatArray
	movw	ip, #:lower16:78696	@ tmp247,
	ldr	r2, [r4, r3]	@ D.40630, <variable>.CodecInfo.pUsrDatArray
	movt	ip, #:upper16:78696	@ tmp247,
	cmp	r2, r1	@ D.40630,
	strne	r2, [r6, #224]	@ D.40630, <variable>.p_usrdat
	ldr	r0, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	strne	r1, [r4, r3]	@ tmp241, <variable>.CodecInfo.pUsrDatArray
	movw	r3, #:lower16:78700	@ tmp249,
	movt	r3, #:upper16:78700	@ tmp249,
	mov	r1, #0	@ tmp248,
	str	r1, [r4, ip]	@ tmp248, <variable>.CodecInfo.pUsrDatArray
	str	r1, [r4, r3]	@ tmp248, <variable>.CodecInfo.TotalUsrDatNum
	ldr	r2, [r0, #12]	@ <variable>.s32DecOrderOutput, <variable>.s32DecOrderOutput
	cmp	r2, #1	@ <variable>.s32DecOrderOutput,
	beq	.L449	@,
	ldrb	lr, [r5, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	cmp	lr, #3	@ <variable>.picture_coding_type,
	beq	.L449	@,
	movw	r2, #:lower16:78744	@ tmp254,
	movt	r2, #:upper16:78744	@ tmp254,
	movw	r0, #:lower16:78756	@ tmp255,
	movt	r0, #:upper16:78756	@ tmp255,
	ldr	r1, [r4, r2]	@ prephitmp.1944,
	str	r1, [r4, r0]	@ prephitmp.1944, <variable>.CodecInfo.ToQueFsID
.L451:
	cmn	r1, #1	@ prephitmp.1944,
	beq	.L452	@,
	movw	r6, #:lower16:113648	@ tmp260,
	movt	r6, #:upper16:113648	@ tmp260,
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	bl	FSP_GetDisplay	@
	cmp	r0, #1	@,
	beq	.L453	@,
	movw	lr, #:lower16:78756	@ tmp264,
	movt	lr, #:upper16:78756	@ tmp264,
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	ldr	r1, [r4, lr]	@, <variable>.CodecInfo.ToQueFsID
	bl	FSP_GetDisplay	@
	cmp	r0, #2	@,
	beq	.L453	@,
.L452:
	ldrb	ip, [r5, #27]	@ zero_extendqisi2	@ <variable>.progressive_sequence, <variable>.progressive_sequence
	cmp	ip, #1	@ <variable>.progressive_sequence,
	beq	.L464	@,
	ldrb	r2, [r5, #18]	@ zero_extendqisi2	@ <variable>.progressive_frame, <variable>.progressive_frame
	cmp	r2, #1	@ <variable>.progressive_frame,
	beq	.L465	@,
	movw	r0, #:lower16:78832	@ tmp350,
	movt	r0, #:upper16:78832	@ tmp350,
	movw	lr, #:lower16:78828	@ tmp353,
	movt	lr, #:upper16:78828	@ tmp353,
	ldr	r2, [r4, r0]	@ <variable>.GopFrmCnt, <variable>.GopFrmCnt
	add	r1, r2, #1	@ temp.2004, <variable>.GopFrmCnt,
	str	r1, [r4, r0]	@ temp.2004, <variable>.GopFrmCnt
	mov	r3, r1, asl #1	@ tmp354, temp.2004,
	str	r3, [r4, lr]	@ tmp354, <variable>.GopFldCnt
.L459:
	movw	r2, #:lower16:78824	@ tmp355,
	movt	r2, #:upper16:78824	@ tmp355,
	movw	r3, #:lower16:78676	@ tmp359,
	movt	r3, #:upper16:78676	@ tmp359,
	ldr	ip, [r4, r2]	@ <variable>.GopFrmCntNoRpt, <variable>.GopFrmCntNoRpt
	mov	r0, #1	@ D.40591,
	add	r1, ip, r0	@ tmp358, <variable>.GopFrmCntNoRpt,
	str	r1, [r4, r2]	@ tmp358, <variable>.GopFrmCntNoRpt
	ldr	lr, [r4, r3]	@ <variable>.CodecInfo.Frame_Cnt, <variable>.CodecInfo.Frame_Cnt
	add	ip, lr, r0	@ tmp362, <variable>.CodecInfo.Frame_Cnt,
	str	ip, [r4, r3]	@ tmp362,
	b	.L437	@
.L463:
	movw	r5, #:lower16:113648	@ tmp185,
	movw	r7, #:lower16:78748	@ tmp187,
	movt	r5, #:upper16:113648	@ tmp185,
	movt	r7, #:upper16:78748	@ tmp187,
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r4, r7]	@, <variable>.CodecInfo.BwdFsID
	bl	FSP_GetFsImagePtr	@
	subs	r6, r0, #0	@ pImg,
	beq	.L441	@,
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	movw	sl, #:lower16:78744	@ tmp211,
	ldr	r1, [r6, #212]	@, <variable>.p_usrdat
	movt	sl, #:upper16:78744	@ tmp211,
	bl	FreeUsdByDec	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r6, #216]	@, <variable>.p_usrdat
	mov	r8, #0	@ tmp201,
	bl	FreeUsdByDec	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r6, #220]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r6, #224]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	str	r8, [r6, #224]	@ tmp201, <variable>.p_usrdat
	str	r8, [r6, #212]	@ tmp201, <variable>.p_usrdat
	mov	r2, #1	@,
	str	r8, [r6, #216]	@ tmp201, <variable>.p_usrdat
	str	r8, [r6, #220]	@ tmp201, <variable>.p_usrdat
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r4, r7]	@, <variable>.CodecInfo.BwdFsID
	bl	FSP_ClearLogicFs	@
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	ldr	r1, [r4, sl]	@, <variable>.CodecInfo.FwdFsID
	mov	r2, #1	@,
	bl	FSP_ClearLogicFs	@
	str	r8, [r4, r7]	@ tmp201, <variable>.CodecInfo.BwdFsID
	str	r8, [r4, sl]	@ tmp201, <variable>.CodecInfo.FwdFsID
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	bl	FSP_GetFspType	@
	cmp	r0, r8	@,
	beq	.L441	@,
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	bl	FSP_GetNullLogicFs	@
	str	r0, [r4, r7]	@ D.40622, <variable>.CodecInfo.BwdFsID
	str	r0, [r4, sl]	@ D.40622, <variable>.CodecInfo.FwdFsID
.L441:
	movw	lr, #:lower16:78708	@ tmp223,
	movt	lr, #:upper16:78708	@ tmp223,
	mov	ip, #0	@ tmp224,
	mov	r0, #1	@ D.40591,
	str	ip, [r4, lr]	@ tmp224,
	b	.L437	@
.L465:
	movw	r2, #:lower16:78832	@ tmp340,
	movt	r2, #:upper16:78832	@ tmp340,
	movw	r3, #:lower16:78828	@ tmp344,
	movt	r3, #:upper16:78828	@ tmp344,
	ldr	ip, [r4, r2]	@ <variable>.GopFrmCnt, <variable>.GopFrmCnt
	ldr	lr, [r4, r3]	@ <variable>.GopFldCnt, <variable>.GopFldCnt
	add	r0, ip, #1	@ tmp343, <variable>.GopFrmCnt,
	str	r0, [r4, r2]	@ tmp343, <variable>.GopFrmCnt
	ldrb	r1, [r5, #16]	@ zero_extendqisi2	@ <variable>.repeat_first_field, <variable>.repeat_first_field
	add	ip, lr, #2	@ tmp346, <variable>.GopFldCnt,
	add	r0, ip, r1	@ tmp349, tmp346, <variable>.repeat_first_field
	str	r0, [r4, r3]	@ tmp349, <variable>.GopFldCnt
	b	.L459	@
.L453:
	movw	r7, #:lower16:113648	@ tmp266,
	movw	r8, #:lower16:78756	@ tmp268,
	movt	r7, #:upper16:113648	@ tmp266,
	movt	r8, #:upper16:78756	@ tmp268,
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	ldr	r1, [r4, r8]	@, <variable>.CodecInfo.ToQueFsID
	bl	FSP_GetFsImagePtr	@
	subs	r6, r0, #0	@ pToQueImg,
	beq	.L466	@,
	ldr	r2, [r6, #200]	@ D.40655, <variable>.error_level
	cmp	r2, #0	@ D.40655,
	beq	.L455	@,
	ldr	sl, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	r3, [sl, #4]	@ D.40657, <variable>.s32OutErrThr
	cmp	r2, r3	@ D.40655, D.40657
	bhi	.L456	@,
.L455:
	movw	r8, #:lower16:78756	@ tmp272,
	movt	r8, #:upper16:78756	@ tmp272,
	movw	r7, #:lower16:113648	@ tmp273,
	movt	r7, #:upper16:113648	@ tmp273,
	ldr	sl, [r4, r8]	@ temp.1992, <variable>.CodecInfo.ToQueFsID
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	mov	r1, sl	@, temp.1992
	bl	FSP_GetRef	@
	mov	r2, sl	@, temp.1992
	movw	r1, #:lower16:.LC32	@,
	movt	r1, #:upper16:.LC32	@,
	mov	r3, r0	@ D.40660,
	mov	r0, #12	@,
	bl	dprint_vfmw	@
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	ldr	r1, [r4, r8]	@, <variable>.CodecInfo.ToQueFsID
	mov	r2, #1	@,
	bl	FSP_SetDisplay	@
	add	r2, r4, #79872	@, pCtx,
	ldr	r0, [r4, r7]	@ <variable>.ChanID, <variable>.ChanID
	add	r3, r2, #128	@,,
	mov	r1, #3	@,
	mov	r2, r4	@, pCtx
	str	r6, [sp, #0]	@ pToQueImg,
	bl	InsertImgToVoQueue	@
	cmp	r0, #1	@,
	beq	.L457	@,
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	mov	r5, #0	@ tmp287,
	ldr	r1, [r6, #212]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	str	r5, [r6, #212]	@ tmp287, <variable>.p_usrdat
	ldr	r1, [r6, #216]	@, <variable>.p_usrdat
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	str	r5, [r6, #216]	@ tmp287, <variable>.p_usrdat
	ldr	r1, [r6, #220]	@, <variable>.p_usrdat
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	str	r5, [r6, #220]	@ tmp287, <variable>.p_usrdat
	ldr	r1, [r6, #224]	@, <variable>.p_usrdat
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	str	r5, [r6, #224]	@ tmp287, <variable>.p_usrdat
	mov	r2, r5	@, tmp287
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	ldr	r1, [r4, r8]	@, <variable>.CodecInfo.ToQueFsID
	bl	FSP_SetDisplay	@
	mov	r0, r5	@ D.40591, tmp287
	b	.L437	@
.L449:
	movw	ip, #:lower16:78752	@ tmp258,
	movt	ip, #:upper16:78752	@ tmp258,
	movw	r3, #:lower16:78756	@ tmp259,
	movt	r3, #:upper16:78756	@ tmp259,
	ldr	r1, [r4, ip]	@ prephitmp.1944,
	str	r1, [r4, r3]	@ prephitmp.1944, <variable>.CodecInfo.ToQueFsID
	b	.L451	@
.L464:
	movw	r3, #:lower16:78832	@ tmp330,
	movt	r3, #:upper16:78832	@ tmp330,
	ldrb	ip, [r5, #16]	@ zero_extendqisi2	@ <variable>.repeat_first_field, <variable>.repeat_first_field
	movw	r2, #:lower16:78828	@ tmp337,
	ldr	lr, [r4, r3]	@ <variable>.GopFrmCnt, <variable>.GopFrmCnt
	movt	r2, #:upper16:78828	@ tmp337,
	ldrb	r0, [r5, #10]	@ zero_extendqisi2	@ <variable>.top_field_first, <variable>.top_field_first
	add	r1, lr, #1	@ tmp331, <variable>.GopFrmCnt,
	add	lr, r1, ip	@ tmp334, tmp331, <variable>.repeat_first_field
	add	r1, lr, r0	@ D.40679, tmp334, <variable>.top_field_first
	str	r1, [r4, r3]	@ D.40679, <variable>.GopFrmCnt
	mov	lr, r1, asl #1	@ tmp338, D.40679,
	str	lr, [r4, r2]	@ tmp338, <variable>.GopFldCnt
	b	.L459	@
.L456:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	mov	sl, #0	@ tmp312,
	bl	dprint_vfmw	@
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	ldr	r1, [r6, #212]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	str	sl, [r6, #212]	@ tmp312, <variable>.p_usrdat
	ldr	r1, [r6, #216]	@, <variable>.p_usrdat
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	str	sl, [r6, #216]	@ tmp312, <variable>.p_usrdat
	ldr	r1, [r6, #220]	@, <variable>.p_usrdat
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	str	sl, [r6, #220]	@ tmp312, <variable>.p_usrdat
	ldr	r1, [r6, #224]	@, <variable>.p_usrdat
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	str	sl, [r6, #224]	@ tmp312, <variable>.p_usrdat
	mov	r2, sl	@, tmp312
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	ldr	r1, [r4, r8]	@, <variable>.CodecInfo.ToQueFsID
	bl	FSP_SetDisplay	@
	b	.L452	@
.L462:
	mov	r3, sl	@, pBwdImg
	mov	r0, r6	@, pCurImg
	movw	r1, #:lower16:.LC30	@,
	mov	r2, r6	@, pCurImg
	movt	r1, #:upper16:.LC30	@,
	str	ip, [sp, #0]	@ pFwdImg,
	bl	dprint_vfmw	@
	mov	r0, r6	@ D.40591, pCurImg
	b	.L437	@
.L457:
	movw	r0, #:lower16:113656	@ tmp304,
	movt	r0, #:upper16:113656	@ tmp304,
	ldr	r3, [r4, r0]	@ <variable>.numOutputFrame, <variable>.numOutputFrame
	add	r1, r3, #1	@ tmp307, <variable>.numOutputFrame,
	str	r1, [r4, r0]	@ tmp307, <variable>.numOutputFrame
	b	.L452	@
.L466:
	movw	r1, #:lower16:.LC26	@,
	movw	r2, #3258	@,
	movt	r1, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mov	r0, r6	@ D.40591, pToQueImg
	b	.L437	@
	.fnend
	.size	MPEG2DEC_VDMPostProc, .-MPEG2DEC_VDMPostProc
	.align	2
	.global	MPEG2DEC_GetRemainImg
	.type	MPEG2DEC_GetRemainImg, %function
MPEG2DEC_GetRemainImg:
	.fnstart
.LFB1565:
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
	mov	r4, r0	@ pCtx, pCtx
	ldr	r0, [r0, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	r3, [r0, #12]	@ <variable>.s32DecOrderOutput, <variable>.s32DecOrderOutput
	cmp	r3, #1	@ <variable>.s32DecOrderOutput,
	beq	.L468	@,
	movw	r7, #:lower16:113648	@ tmp146,
	movw	r6, #:lower16:78748	@ tmp148,
	movt	r7, #:upper16:113648	@ tmp146,
	movt	r6, #:upper16:78748	@ tmp148,
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	ldr	r1, [r4, r6]	@, <variable>.CodecInfo.BwdFsID
	bl	FSP_GetFsImagePtr	@
	subs	r5, r0, #0	@ pImg,
	beq	.L468	@,
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	ldr	r1, [r4, r6]	@, <variable>.CodecInfo.BwdFsID
	bl	FSP_GetDisplay	@
	cmp	r0, #2	@,
	beq	.L479	@,
.L468:
	add	r0, r4, #79872	@, pCtx,
	add	r0, r0, #128	@,,
	bl	GetVoLastImageID	@
.L474:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L479:
	mov	r0, r4	@, pCtx
	mov	r7, #0	@ tmp158,
	bl	MP2_SetImgFormat	@
	movw	r3, #:lower16:78684	@ tmp154,
	movt	r3, #:upper16:78684	@ tmp154,
	movw	r1, #:lower16:78684	@ tmp157,
	movw	r0, #:lower16:78688	@ tmp159,
	movt	r1, #:upper16:78684	@ tmp157,
	ldr	ip, [r4, r3]	@ temp.2052, <variable>.CodecInfo.pUsrDatArray
	movt	r0, #:upper16:78688	@ tmp159,
	movw	r6, #:lower16:78688	@ tmp162,
	movt	r6, #:upper16:78688	@ tmp162,
	cmp	ip, #0	@ temp.2052,
	strne	ip, [r5, #212]	@ temp.2052, <variable>.p_usrdat
	movne	ip, #0	@ tmp156,
	strne	ip, [r4, r3]	@ tmp156, <variable>.CodecInfo.pUsrDatArray
	str	r7, [r4, r1]	@ tmp158, <variable>.CodecInfo.pUsrDatArray
	movw	ip, #:lower16:78692	@ tmp164,
	ldr	r2, [r4, r0]	@ temp.2057, <variable>.CodecInfo.pUsrDatArray
	movt	ip, #:upper16:78692	@ tmp164,
	mov	r1, #0	@ tmp163,
	cmp	r2, r7	@ temp.2057,
	strne	r2, [r5, #216]	@ temp.2057, <variable>.p_usrdat
	movw	r2, #:lower16:78692	@ tmp167,
	strne	r7, [r4, r0]	@ tmp158, <variable>.CodecInfo.pUsrDatArray
	movt	r2, #:upper16:78692	@ tmp167,
	str	r1, [r4, r6]	@ tmp163, <variable>.CodecInfo.pUsrDatArray
	movw	r7, #:lower16:78696	@ tmp169,
	ldr	r3, [r4, ip]	@ temp.2058, <variable>.CodecInfo.pUsrDatArray
	movt	r7, #:upper16:78696	@ tmp169,
	mov	r6, #0	@ tmp168,
	cmp	r3, r1	@ temp.2058,
	strne	r3, [r5, #220]	@ temp.2058, <variable>.p_usrdat
	movw	r3, #:lower16:78696	@ tmp172,
	strne	r1, [r4, ip]	@ tmp163, <variable>.CodecInfo.pUsrDatArray
	movt	r3, #:upper16:78696	@ tmp172,
	str	r6, [r4, r2]	@ tmp168, <variable>.CodecInfo.pUsrDatArray
	movw	ip, #:lower16:78700	@ tmp174,
	ldr	r0, [r4, r7]	@ D.40526, <variable>.CodecInfo.pUsrDatArray
	movt	ip, #:upper16:78700	@ tmp174,
	mov	r1, #1	@ tmp176,
	cmp	r0, r6	@ D.40526,
	mov	r2, r1	@, tmp176
	strne	r0, [r5, #224]	@ D.40526, <variable>.p_usrdat
	strne	r6, [r4, r7]	@ tmp168, <variable>.CodecInfo.pUsrDatArray
	movw	r7, #:lower16:113648	@ tmp177,
	movt	r7, #:upper16:113648	@ tmp177,
	mov	r6, #0	@ tmp173,
	str	r6, [r4, r3]	@ tmp173, <variable>.CodecInfo.pUsrDatArray
	str	r6, [r4, ip]	@ tmp173, <variable>.CodecInfo.TotalUsrDatNum
	str	r1, [r5, #244]	@ tmp176, <variable>.last_frame
	ldr	r1, [r5, #196]	@, <variable>.image_id
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	bl	FSP_SetDisplay	@
	add	r2, r4, #79872	@, pCtx,
	ldr	r0, [r4, r7]	@ <variable>.ChanID, <variable>.ChanID
	add	r3, r2, #128	@,,
	mov	r1, #3	@,
	mov	r2, r4	@, pCtx
	str	r5, [sp, #0]	@ pImg,
	bl	InsertImgToVoQueue	@
	cmp	r0, #1	@,
	beq	.L473	@,
	ldr	r1, [r5, #196]	@, <variable>.image_id
	mov	r0, r4	@, pCtx
	bl	MPEG2DEC_RecycleImage	@
	b	.L468	@
.L473:
	ldr	lr, [r5, #200]	@ <variable>.error_level, <variable>.error_level
	cmp	lr, #100	@ <variable>.error_level,
	bhi	.L468	@,
	ldr	r2, [r5, #164]	@ <variable>.image_width, <variable>.image_width
	cmp	r2, #31	@ <variable>.image_width,
	bls	.L468	@,
	ldr	r1, [r5, #168]	@ <variable>.image_height, <variable>.image_height
	cmp	r1, #31	@ <variable>.image_height,
	movhi	r0, r6	@ ret, tmp173
	bhi	.L474	@,
	b	.L468	@
	.fnend
	.size	MPEG2DEC_GetRemainImg, .-MPEG2DEC_GetRemainImg
	.align	2
	.global	MP2_GetPictureInfo
	.type	MP2_GetPictureInfo, %function
MP2_GetPictureInfo:
	.fnstart
.LFB1534:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #16
	sub	sp, sp, #16	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r5, #:lower16:78704	@ tmp165,
	movt	r5, #:upper16:78704	@ tmp165,
	movw	r2, #:lower16:79992	@ tmp163,
	movw	r3, #:lower16:79996	@ tmp164,
	movt	r2, #:upper16:79992	@ tmp163,
	ldr	r1, [r0, r5]	@ <variable>.CodecInfo.MpegFlag, <variable>.CodecInfo.MpegFlag
	movt	r3, #:upper16:79996	@ tmp164,
	mov	r4, r0	@ pCtx, pCtx
	ldr	r5, [r0, r2]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	cmp	r1, #1	@ <variable>.CodecInfo.MpegFlag,
	ldr	r6, [r0, r3]	@ pSyntaxInfOld, <variable>.pSyntaxInfOld
	beq	.L518	@,
.L481:
	ldrb	lr, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	cmp	lr, #3	@ <variable>.picture_structure,
	beq	.L482	@,
	movw	r7, #:lower16:78680	@ tmp176,
	movt	r7, #:upper16:78680	@ tmp176,
	movw	r1, #:lower16:78712	@ tmp180,
	movt	r1, #:upper16:78712	@ tmp180,
	ldr	r8, [r4, r7]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	ldr	r3, [r4, r1]	@ <variable>.CodecInfo.LastTempReference, <variable>.CodecInfo.LastTempReference
	rsbs	r8, r8, #1	@ tmp178, <variable>.CodecInfo.Second_Field
	movcc	r8, #0	@ tmp178
	str	r8, [r4, r7]	@ tmp178, <variable>.CodecInfo.Second_Field
	ldr	r2, [r5, #156]	@ <variable>.temporal_reference, <variable>.temporal_reference
	cmp	r2, r3	@ <variable>.temporal_reference, <variable>.CodecInfo.LastTempReference
	beq	.L483	@,
	cmp	r8, #1	@ tmp178,
	beq	.L519	@,
.L483:
	ldrb	lr, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	movw	r1, #45329	@ tmp214,
	movw	r3, #:lower16:78712	@ tmp217,
	movt	r3, #:upper16:78712	@ tmp217,
	strb	lr, [r4, r1]	@ <variable>.picture_structure, <variable>.CodecInfo.Last_FieldStruct
	movw	lr, #:lower16:78680	@ tmp234,
	ldr	r2, [r5, #156]	@ <variable>.temporal_reference, <variable>.temporal_reference
	movt	lr, #:upper16:78680	@ tmp234,
	str	r2, [r4, r3]	@ <variable>.temporal_reference, <variable>.CodecInfo.LastTempReference
	movw	r3, #:lower16:78704	@ tmp241,
	ldrh	ip, [r5, #56]	@, <variable>.mb_width
	movt	r3, #:upper16:78704	@ tmp241,
	strh	ip, [r4, #160]	@ movhi	@, <variable>.Mp2DecParam.PicWidthInMb
	ldrb	r0, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	ldr	ip, [r4, lr]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	cmp	r0, #3	@ <variable>.picture_structure,
	ldrne	r0, [r5, #60]	@ <variable>.mb_height, <variable>.mb_height
	ldreq	r0, [r5, #64]	@ <variable>.mb_height_progressive_subtract1mb, <variable>.mb_height_progressive_subtract1mb
	ldreq	r2, [r5, #60]	@ <variable>.mb_height, <variable>.mb_height
	movne	r0, r0, lsr #1	@ tmp221, <variable>.mb_height,
	rsbeq	r0, r0, r2	@ tmp228, <variable>.mb_height_progressive_subtract1mb, <variable>.mb_height
	strh	r0, [r4, #156]	@ movhi	@ tmp228, <variable>.Mp2DecParam.PicHeightInMb
	ldrh	r6, [r5, #60]	@, <variable>.mb_height
	ldr	r0, [r4, r3]	@ <variable>.CodecInfo.MpegFlag, <variable>.CodecInfo.MpegFlag
	strh	r6, [r4, #158]	@ movhi	@, <variable>.Mp2DecParam.FrameHeightInMb
	cmp	r0, #1	@ <variable>.CodecInfo.MpegFlag,
	ldrb	r1, [r5, #11]	@ zero_extendqisi2	@ <variable>.frame_pred_frame_dct, <variable>.frame_pred_frame_dct
	movne	lr, #0	@, tmp243
	moveq	lr, #1	@, tmp243
	strb	r1, [r4, #13]	@ <variable>.frame_pred_frame_dct, <variable>.Mp2DecParam.FramePredFrameDct
	ldrb	r2, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	strb	ip, [r4, #12]	@ <variable>.CodecInfo.Second_Field, <variable>.Mp2DecParam.SecondFieldFlag
	strb	r2, [r4, #11]	@ <variable>.picture_structure, <variable>.Mp2DecParam.PictureStructure
	ldrb	r6, [r5, #12]	@ zero_extendqisi2	@ <variable>.concealment_motion_vectors, <variable>.concealment_motion_vectors
	strb	r6, [r4, #15]	@ <variable>.concealment_motion_vectors, <variable>.Mp2DecParam.ConcealmentMotionVectors
	ldrb	r1, [r5, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	str	lr, [r4, #188]	@ tmp243, <variable>.Mp2DecParam.Mpeg1Flag
	strb	r1, [r4, #8]	@ <variable>.picture_coding_type, <variable>.Mp2DecParam.PicCodingType
	ldreqb	r1, [r5, #25]	@ zero_extendqisi2	@ <variable>.full_pel_backward_vector, <variable>.full_pel_backward_vector
	streqb	r1, [r4, #9]	@ <variable>.full_pel_backward_vector, <variable>.Mp2DecParam.Mp1BwdmvFullPel
	ldreqb	r1, [r5, #23]	@ zero_extendqisi2	@ <variable>.full_pel_forward_vector, <variable>.full_pel_forward_vector
	streqb	r1, [r4, #10]	@ <variable>.full_pel_forward_vector, <variable>.Mp2DecParam.Mp1FwdmvFullPel
	ldrb	r3, [r5, #4]	@ zero_extendqisi2	@ <variable>.f_code, <variable>.f_code
	strb	r3, [r4, #20]	@ <variable>.f_code, <variable>.Mp2DecParam.Fcode
	ldrb	ip, [r5, #5]	@ zero_extendqisi2	@ <variable>.f_code, <variable>.f_code
	strb	ip, [r4, #21]	@ <variable>.f_code, <variable>.Mp2DecParam.Fcode
	ldrb	r2, [r5, #6]	@ zero_extendqisi2	@ <variable>.f_code, <variable>.f_code
	strb	r2, [r4, #22]	@ <variable>.f_code, <variable>.Mp2DecParam.Fcode
	ldrb	r0, [r5, #7]	@ zero_extendqisi2	@ <variable>.f_code, <variable>.f_code
	strb	r0, [r4, #23]	@ <variable>.f_code, <variable>.Mp2DecParam.Fcode
	ldrb	r6, [r5, #10]	@ zero_extendqisi2	@ <variable>.top_field_first, <variable>.top_field_first
	strb	r6, [r4, #14]	@ <variable>.top_field_first, <variable>.Mp2DecParam.TopFieldFirst
	ldrb	lr, [r5, #8]	@ zero_extendqisi2	@ <variable>.intra_dc_precision, <variable>.intra_dc_precision
	strb	lr, [r4, #19]	@ <variable>.intra_dc_precision, <variable>.Mp2DecParam.IntraDcPrecision
	ldrb	r1, [r5, #13]	@ zero_extendqisi2	@ <variable>.q_scale_type, <variable>.q_scale_type
	strb	r1, [r4, #18]	@ <variable>.q_scale_type, <variable>.Mp2DecParam.QuantType
	ldrb	r3, [r5, #14]	@ zero_extendqisi2	@ <variable>.intra_vlc_format, <variable>.intra_vlc_format
	strb	r3, [r4, #17]	@ <variable>.intra_vlc_format, <variable>.Mp2DecParam.IntraVlcFormat
	ldrb	ip, [r5, #15]	@ zero_extendqisi2	@ <variable>.alternate_scan, <variable>.alternate_scan
	strb	ip, [r4, #16]	@ <variable>.alternate_scan, <variable>.Mp2DecParam.AlternateScan
	ldrb	r2, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	cmp	r2, #3	@ <variable>.picture_structure,
	beq	.L488	@,
	movw	r0, #:lower16:78680	@ tmp269,
	movt	r0, #:upper16:78680	@ tmp269,
	ldr	r6, [r4, r0]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	cmp	r6, #0	@ <variable>.CodecInfo.Second_Field,
	beq	.L488	@,
.L489:
	movw	r7, #:lower16:113648	@ tmp327,
	movw	lr, #:lower16:78752	@ tmp329,
	movt	r7, #:upper16:113648	@ tmp327,
	movt	lr, #:upper16:78752	@ tmp329,
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	ldr	r1, [r4, lr]	@, <variable>.CodecInfo.CurFsID
	bl	FSP_GetLogicFs	@
	movw	ip, #:lower16:78744	@ tmp333,
	movt	ip, #:upper16:78744	@ tmp333,
	ldr	r1, [r4, ip]	@, <variable>.CodecInfo.FwdFsID
	mov	r5, r0	@ pCur,
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	bl	FSP_GetLogicFs	@
	movw	r2, #:lower16:78748	@ tmp337,
	movt	r2, #:upper16:78748	@ tmp337,
	ldr	r1, [r4, r2]	@, <variable>.CodecInfo.BwdFsID
	mov	r6, r0	@ pFwd,
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	bl	FSP_GetLogicFs	@
	cmp	r5, #0	@ pCur,
	cmpne	r6, #0	@, pFwd,
	mov	r7, r0	@ pBwd,
	beq	.L496	@,
	cmp	r0, #0	@ pBwd,
	beq	.L496	@,
	ldr	r2, [r5, #512]	@ D.39183, <variable>.pstDecodeFs
	cmp	r2, #0	@ D.39183,
	beq	.L498	@,
	ldr	r0, [r5, #520]	@ <variable>.pstTfOutFs, <variable>.pstTfOutFs
	cmp	r0, #0	@ <variable>.pstTfOutFs,
	beq	.L498	@,
	ldr	ip, [r5, #516]	@ <variable>.pstDispOutFs, <variable>.pstDispOutFs
	cmp	ip, #0	@ <variable>.pstDispOutFs,
	beq	.L498	@,
	ldr	ip, [r7, #512]	@ D.39190, <variable>.pstDecodeFs
	cmp	ip, #0	@ D.39190,
	ldrne	lr, [ip, #12]	@ iftmp.461, <variable>.PhyAddr
	ldreq	lr, [r2, #12]	@ iftmp.461, <variable>.PhyAddr
	str	lr, [r4, #200]	@ iftmp.461, <variable>.Mp2DecParam.BwdRefPhyAddr
	ldr	r2, [r6, #512]	@ D.39197, <variable>.pstDecodeFs
	cmp	r2, #0	@ D.39197,
	ldreq	r2, [r5, #512]	@ <variable>.pstDecodeFs, <variable>.pstDecodeFs
	ldr	ip, [r2, #12]	@ iftmp.462, <variable>.PhyAddr
	str	ip, [r4, #204]	@ iftmp.462, <variable>.Mp2DecParam.FwdRefPhyAddr
	ldr	r8, [r5, #512]	@ <variable>.pstDecodeFs, <variable>.pstDecodeFs
	ldr	r2, [r8, #12]	@ D.39202, <variable>.PhyAddr
	str	r2, [r4, #208]	@ D.39202, <variable>.Mp2DecParam.CurPicPhyAddr
	ldr	r8, [r5, #524]	@ D.39204, <variable>.PmvAddr
	str	r8, [r4, #248]	@ D.39204, <variable>.Mp2DecParam.PmvColmbPhyAddr
	ldr	r0, [r7, #520]	@ D.39206, <variable>.pstTfOutFs
	cmp	r0, #0	@ D.39206,
	ldreq	r0, [r5, #520]	@ <variable>.pstTfOutFs, <variable>.pstTfOutFs
	ldr	r3, [r0, #12]	@ iftmp.463, <variable>.PhyAddr
	str	r3, [r4, #220]	@ iftmp.463, <variable>.Mp2DecParam.TfBwdPhyAddr
	ldr	r1, [r6, #520]	@ D.39213, <variable>.pstTfOutFs
	cmp	r1, #0	@ D.39213,
	ldreq	r1, [r5, #520]	@ <variable>.pstTfOutFs, <variable>.pstTfOutFs
	ldr	r0, [r1, #12]	@ iftmp.464, <variable>.PhyAddr
	movw	r1, #:lower16:.LC42	@,
	movt	r1, #:upper16:.LC42	@,
	str	r0, [r4, #224]	@ iftmp.464, <variable>.Mp2DecParam.TfFwdPhyAddr
	mov	r0, #13	@,
	ldr	r3, [r5, #520]	@ <variable>.pstTfOutFs, <variable>.pstTfOutFs
	ldr	r3, [r3, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	r3, [r4, #228]	@ <variable>.PhyAddr, <variable>.Mp2DecParam.TfCurPhyAddr
	ldr	r3, [r5, #516]	@ <variable>.pstDispOutFs, <variable>.pstDispOutFs
	ldr	r3, [r3, #12]	@ D.39220, <variable>.PhyAddr
	str	r3, [r4, #232]	@ D.39220, <variable>.Mp2DecParam.DispFramePhyAddr
	ldr	r7, [r7, #156]	@ <variable>.stDispImg.is_fld_save, <variable>.stDispImg.is_fld_save
	str	r7, [r4, #212]	@ <variable>.stDispImg.is_fld_save, <variable>.Mp2DecParam.BwdRefIsFldSave
	ldr	r6, [r6, #156]	@ <variable>.stDispImg.is_fld_save, <variable>.stDispImg.is_fld_save
	str	r6, [r4, #216]	@ <variable>.stDispImg.is_fld_save, <variable>.Mp2DecParam.FwdRefIsFldSave
	ldr	r7, [r5, #520]	@ <variable>.pstTfOutFs, <variable>.pstTfOutFs
	ldr	r6, [r7, #12]	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	ip, [sp, #0]	@ iftmp.462,
	movw	ip, #45320	@ tmp376,
	str	lr, [sp, #4]	@ iftmp.461,
	str	r6, [r4, ip]	@ <variable>.PhyAddr, <variable>.Mp2DecParam.DnrMbInfoStAddr
	str	r8, [sp, #8]	@ D.39204,
	bl	dprint_vfmw	@
	ldr	r7, [r5, #516]	@ <variable>.pstDispOutFs, <variable>.pstDispOutFs
	add	r3, r4, #78848	@ ivtmp.2091, pCtx,
	add	r3, r3, #96	@ ivtmp.2091, ivtmp.2091,
	mov	r2, r4	@ ivtmp.2095, pCtx
	mov	r0, #0	@ i,
	ldr	r5, [r7, #20]	@ <variable>.Stride, <variable>.Stride
	str	r5, [r4, #240]	@ <variable>.Stride, <variable>.Mp2DecParam.VahbStride
.L508:
	add	ip, r3, #4	@ tmp398, ivtmp.2091,
	ldr	r5, [r3, #4]	@ tmp403, <variable>.intra_quantizer_matrix
	ldr	r7, [r3, #0]	@ tmp383, <variable>.intra_quantizer_matrix
	add	r0, r0, #2	@ i, i,
	ldr	r6, [r3, #256]	@ tmp385, <variable>.non_intra_quantizer_matrix
	add	r1, r2, #1	@ tmp399, ivtmp.2095,
	ldr	lr, [ip, #256]	@ tmp404, <variable>.non_intra_quantizer_matrix
	cmp	r0, #64	@ i,
	strb	r7, [r2, #88]	@ tmp383, <variable>.Mp2DecParam.IntraQuantTab
	add	r3, ip, #4	@ ivtmp.2091, tmp398,
	strb	r6, [r2, #24]	@ tmp385, <variable>.Mp2DecParam.NonIntraQuantTab
	add	r2, r1, #1	@ ivtmp.2095, tmp399,
	strb	r5, [r1, #88]	@ tmp403, <variable>.Mp2DecParam.IntraQuantTab
	strb	lr, [r1, #24]	@ tmp404, <variable>.Mp2DecParam.NonIntraQuantTab
	bne	.L508	@,
	mov	r0, r4	@, pCtx
	mov	r6, #1	@ D.39141,
	bl	MP2_EstimatePicQp	@
	strb	r0, [r4, #152]	@, <variable>.Mp2DecParam.EstmatedPicQp
	b	.L491	@
.L488:
	mov	r0, r4	@, pCtx
	mov	r1, #0	@,
	bl	MP2_GetImageBuffer	@
	subs	r6, r0, #0	@ D.39137,
	beq	.L520	@,
	movw	r2, #:lower16:113648	@ tmp274,
	movw	r7, #:lower16:78752	@ tmp276,
	movt	r2, #:upper16:113648	@ tmp274,
	movt	r7, #:upper16:78752	@ tmp276,
	ldr	r0, [r4, r2]	@, <variable>.ChanID
	ldr	r1, [r4, r7]	@, <variable>.CodecInfo.CurFsID
	bl	FSP_GetFsImagePtr	@
	subs	r6, r0, #0	@ pImg,
	beq	.L492	@,
	ldr	r3, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	mov	r0, #29	@,
	movw	r1, #:lower16:.LC37	@,
	movt	r1, #:upper16:.LC37	@,
	ldrd	r2, [r3, #56]	@ <variable>.pts, <variable>.pstExtraData,
	strd	r2, [r6, #8]	@ <variable>.pts, pImg,
	ldr	r3, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldrd	r2, [r3, #72]	@ <variable>.Usertag, <variable>.pstExtraData,
	strd	r2, [r6, #16]	@ <variable>.Usertag, pImg,
	ldr	r3, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldrd	r2, [r3, #88]	@ <variable>.DispTime, <variable>.pstExtraData,
	strd	r2, [r6, #24]	@ <variable>.DispTime, pImg,
	ldr	r8, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	r9, [r8, #104]	@ <variable>.DispEnableFlag, <variable>.DispEnableFlag
	str	r9, [r6, #68]	@ <variable>.DispEnableFlag, <variable>.DispEnableFlag
	ldr	lr, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	r3, [lr, #108]	@ <variable>.DispFrameDistance, <variable>.DispFrameDistance
	str	r3, [r6, #72]	@ <variable>.DispFrameDistance, <variable>.DispFrameDistance
	ldr	r7, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	ip, [r7, #112]	@ <variable>.DistanceBeforeFirstFrame, <variable>.DistanceBeforeFirstFrame
	str	ip, [r6, #76]	@ <variable>.DistanceBeforeFirstFrame, <variable>.DistanceBeforeFirstFrame
	ldr	r8, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	r9, [r8, #128]	@ <variable>.GopNum, <variable>.GopNum
	mvn	r8, #0	@ tmp293,
	str	r9, [r6, #80]	@ <variable>.GopNum, <variable>.GopNum
	mvn	r9, #0	@,
	ldr	lr, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	strd	r8, [lr, #56]	@ tmp293, <variable>.pstExtraData,
	ldrd	r8, [r6, #16]	@ <variable>.Usertag, pImg,
	ldrd	r2, [r6, #8]	@ <variable>.PTS, pImg,
	strd	r8, [sp]	@ <variable>.Usertag,
	bl	dprint_vfmw	@
	ldrb	r1, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	subs	r3, r1, #3	@ tmp298, <variable>.picture_structure,
	movne	r3, #1	@ tmp298
	str	r3, [r6, #148]	@ tmp298, <variable>.is_fld_save
.L492:
	ldrb	r6, [r5, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	cmp	r6, #3	@ <variable>.picture_coding_type,
	beq	.L489	@,
	movw	ip, #:lower16:78708	@ tmp300,
	movt	ip, #:upper16:78708	@ tmp300,
	movw	r6, #:lower16:78744	@ tmp303,
	movw	r5, #:lower16:78748	@ tmp304,
	ldr	r0, [r4, ip]	@ <variable>.CodecInfo.RefNum, <variable>.CodecInfo.RefNum
	movt	r6, #:upper16:78744	@ tmp303,
	movt	r5, #:upper16:78748	@ tmp304,
	cmp	r0, #0	@ <variable>.CodecInfo.RefNum,
	ldr	r2, [r4, r6]	@ prephitmp.2074, <variable>.CodecInfo.FwdFsID
	ldr	r1, [r4, r5]	@ <variable>.CodecInfo.BwdFsID, <variable>.CodecInfo.BwdFsID
	movne	r0, #2	@ iftmp.457,
	moveq	r0, #1	@ iftmp.457,
	cmp	r2, r1	@ prephitmp.2074, <variable>.CodecInfo.BwdFsID
	str	r0, [r4, ip]	@ iftmp.457, <variable>.CodecInfo.RefNum
	beq	.L495	@,
	movw	r7, #:lower16:113648	@ tmp307,
	movt	r7, #:upper16:113648	@ tmp307,
	mov	r0, #13	@,
	movw	r1, #:lower16:.LC38	@,
	movt	r1, #:upper16:.LC38	@,
	bl	dprint_vfmw	@
	mov	r2, #0	@,
	ldr	r1, [r4, r6]	@, <variable>.CodecInfo.FwdFsID
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	bl	FSP_SetRef	@
	ldr	r2, [r4, r5]	@ prephitmp.2074, <variable>.CodecInfo.BwdFsID
.L495:
	movw	r5, #:lower16:78752	@ tmp314,
	movt	r5, #:upper16:78752	@ tmp314,
	movw	r6, #:lower16:78744	@ tmp312,
	movw	r3, #:lower16:78748	@ tmp313,
	ldr	r1, [r4, r5]	@ <variable>.CodecInfo.CurFsID, <variable>.CodecInfo.CurFsID
	movt	r3, #:upper16:78748	@ tmp313,
	movt	r6, #:upper16:78744	@ tmp312,
	movw	r7, #:lower16:113648	@ tmp316,
	movt	r7, #:upper16:113648	@ tmp316,
	str	r1, [r4, r3]	@ <variable>.CodecInfo.CurFsID, <variable>.CodecInfo.BwdFsID
	str	r2, [r4, r6]	@ prephitmp.2074, <variable>.CodecInfo.FwdFsID
	mov	r2, #1	@,
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	bl	FSP_SetRef	@
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	ldr	r1, [r4, r6]	@, <variable>.CodecInfo.FwdFsID
	bl	FSP_RemovePmv	@
	ldr	r2, [r4, r5]	@, <variable>.CodecInfo.CurFsID
	movw	r1, #:lower16:.LC39	@,
	mov	r0, #13	@,
	movt	r1, #:upper16:.LC39	@,
	bl	dprint_vfmw	@
	b	.L489	@
.L520:
	movw	ip, #:lower16:78676	@ tmp272,
	movt	ip, #:upper16:78676	@ tmp272,
	movw	r1, #:lower16:.LC36	@,
	movt	r1, #:upper16:.LC36	@,
	ldr	r2, [r4, ip]	@, <variable>.CodecInfo.Frame_Cnt
	bl	dprint_vfmw	@
.L491:
	mov	r0, r6	@, D.39141
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L482:
	movw	r3, #45329	@ tmp197,
	ldrb	ip, [r4, r3]	@ zero_extendqisi2	@ D.39095, <variable>.CodecInfo.Last_FieldStruct
	cmp	ip, #3	@ D.39095,
	beq	.L484	@,
	movw	r1, #:lower16:78680	@ tmp198,
	movt	r1, #:upper16:78680	@ tmp198,
	ldr	r3, [r4, r1]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	cmp	r3, #0	@ <variable>.CodecInfo.Second_Field,
	beq	.L521	@,
.L484:
	movw	r0, #:lower16:78680	@ tmp212,
	movt	r0, #:upper16:78680	@ tmp212,
	mov	r6, #1	@ tmp213,
	str	r6, [r4, r0]	@ tmp213,
	b	.L483	@
.L518:
	ldrb	ip, [r5, #26]	@ zero_extendqisi2	@ <variable>.backward_f_code, <variable>.backward_f_code
	ldrb	r0, [r5, #24]	@ zero_extendqisi2	@ <variable>.forward_f_code, <variable>.forward_f_code
	strb	ip, [r5, #6]	@ <variable>.backward_f_code, <variable>.f_code
	strb	r0, [r5, #4]	@ <variable>.forward_f_code, <variable>.f_code
	strb	ip, [r5, #7]	@ <variable>.backward_f_code, <variable>.f_code
	strb	r0, [r5, #5]	@ <variable>.forward_f_code, <variable>.f_code
	b	.L481	@
.L496:
	movw	r1, #:lower16:113648	@ tmp346,
	movw	r3, #:lower16:78752	@ tmp348,
	movt	r1, #:upper16:113648	@ tmp346,
	movt	r3, #:upper16:78752	@ tmp348,
	mov	r2, #1	@,
	ldr	r0, [r4, r1]	@, <variable>.ChanID
	ldr	r1, [r4, r3]	@, <variable>.CodecInfo.CurFsID
	bl	FSP_ClearLogicFs	@
	mov	r3, r5	@, pCur
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC40	@,
	movw	r2, #1133	@,
	movt	r1, #:upper16:.LC40	@,
	str	r6, [sp, #0]	@ pFwd,
	mov	r6, #0	@ D.39141,
	str	r7, [sp, #4]	@ pBwd,
	bl	dprint_vfmw	@
	b	.L491	@
.L519:
	movw	lr, #:lower16:78676	@ tmp184,
	movt	lr, #:upper16:78676	@ tmp184,
	mov	r0, r8	@, tmp178
	movw	r1, #:lower16:.LC34	@,
	ldr	r2, [r4, lr]	@, <variable>.CodecInfo.Frame_Cnt
	movt	r1, #:upper16:.LC34	@,
	bl	dprint_vfmw	@
	movw	r1, #:lower16:113648	@ tmp188,
	movw	ip, #:lower16:78752	@ tmp190,
	movt	r1, #:upper16:113648	@ tmp188,
	movt	ip, #:upper16:78752	@ tmp190,
	mov	r3, #0	@ tmp187,
	ldr	r0, [r4, r1]	@, <variable>.ChanID
	mov	r2, r8	@, tmp178
	str	r3, [r4, r7]	@ tmp187, <variable>.CodecInfo.Second_Field
	ldr	r1, [r4, ip]	@, <variable>.CodecInfo.CurFsID
	bl	FSP_ClearLogicFs	@
	ldrb	r0, [r6, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	cmp	r0, #3	@ <variable>.picture_coding_type,
	beq	.L483	@,
	movw	r0, #:lower16:78668	@ tmp193,
	movt	r0, #:upper16:78668	@ tmp193,
	ldr	r2, [r4, r0]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orr	r6, r2, #192	@ tmp196, <variable>.CodecInfo.StreamIntegrality,
	str	r6, [r4, r0]	@ tmp196,
	b	.L483	@
.L521:
	movw	lr, #:lower16:78676	@ tmp201,
	movt	lr, #:upper16:78676	@ tmp201,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC35	@,
	ldr	r2, [r4, lr]	@ <variable>.CodecInfo.Frame_Cnt, <variable>.CodecInfo.Frame_Cnt
	movt	r1, #:upper16:.LC35	@,
	str	ip, [sp, #0]	@ D.39095,
	bl	dprint_vfmw	@
	movw	r1, #:lower16:113648	@ tmp203,
	movw	r3, #:lower16:78752	@ tmp205,
	movt	r1, #:upper16:113648	@ tmp203,
	movt	r3, #:upper16:78752	@ tmp205,
	mov	r2, #1	@,
	ldr	r0, [r4, r1]	@, <variable>.ChanID
	ldr	r1, [r4, r3]	@, <variable>.CodecInfo.CurFsID
	bl	FSP_ClearLogicFs	@
	ldrb	ip, [r6, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	cmp	ip, #3	@ <variable>.picture_coding_type,
	movwne	ip, #:lower16:78668	@ tmp208,
	movtne	ip, #:upper16:78668	@ tmp208,
	ldrne	r2, [r4, ip]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	orrne	r2, r2, #192	@ tmp211, <variable>.CodecInfo.StreamIntegrality,
	strne	r2, [r4, ip]	@ tmp211, <variable>.CodecInfo.StreamIntegrality
	b	.L484	@
.L498:
	movw	lr, #:lower16:113648	@ tmp353,
	movw	r6, #:lower16:78752	@ tmp355,
	movt	lr, #:upper16:113648	@ tmp353,
	movt	r6, #:upper16:78752	@ tmp355,
	mov	r2, #1	@,
	ldr	r0, [r4, lr]	@, <variable>.ChanID
	ldr	r1, [r4, r6]	@, <variable>.CodecInfo.CurFsID
	bl	FSP_ClearLogicFs	@
	movw	r1, #:lower16:78748	@ tmp362,
	movt	r1, #:upper16:78748	@ tmp362,
	movw	r2, #:lower16:78744	@ tmp358,
	movt	r2, #:upper16:78744	@ tmp358,
	ldr	r3, [r4, r6]	@ <variable>.CodecInfo.CurFsID, <variable>.CodecInfo.CurFsID
	ldr	ip, [r4, r1]	@ <variable>.CodecInfo.BwdFsID, <variable>.CodecInfo.BwdFsID
	mov	r0, #0	@,
	ldr	r2, [r4, r2]	@ <variable>.CodecInfo.FwdFsID, <variable>.CodecInfo.FwdFsID
	movw	r1, #:lower16:.LC41	@,
	movt	r1, #:upper16:.LC41	@,
	str	ip, [sp, #0]	@ <variable>.CodecInfo.BwdFsID,
	ldr	r6, [r5, #512]	@ <variable>.pstDecodeFs, <variable>.pstDecodeFs
	str	r6, [sp, #4]	@ <variable>.pstDecodeFs,
	ldr	ip, [r5, #520]	@ <variable>.pstTfOutFs, <variable>.pstTfOutFs
	str	ip, [sp, #8]	@ <variable>.pstTfOutFs,
	ldr	r6, [r5, #516]	@ <variable>.pstDispOutFs, <variable>.pstDispOutFs
	str	r6, [sp, #12]	@ <variable>.pstDispOutFs,
	bl	dprint_vfmw	@
	mov	r6, #0	@ D.39141,
	b	.L491	@
	.fnend
	.size	MP2_GetPictureInfo, .-MP2_GetPictureInfo
	.align	2
	.global	MP2_DecodingDecide
	.type	MP2_DecodingDecide, %function
MP2_DecodingDecide:
	.fnstart
.LFB1532:
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
	movw	r3, #:lower16:78668	@ tmp167,
	movt	r3, #:upper16:78668	@ tmp167,
	movw	r2, #:lower16:79992	@ tmp166,
	movt	r2, #:upper16:79992	@ tmp166,
	mov	r4, r0	@ pCtx, pCtx
	ldr	r3, [r0, r3]	@ prephitmp.2199, <variable>.CodecInfo.StreamIntegrality
	ldr	r5, [r0, r2]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	tst	r3, #8388608	@ prephitmp.2199,
	mvneq	r0, #0	@ D.38854,
	beq	.L524	@,
	ldrb	r0, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	cmp	r0, #3	@ <variable>.picture_structure,
	beq	.L525	@,
	movw	r7, #:lower16:78680	@ tmp170,
	movt	r7, #:upper16:78680	@ tmp170,
	ldr	r1, [r4, r7]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	cmp	r1, #1	@ <variable>.CodecInfo.Second_Field,
	beq	.L525	@,
	ands	r7, r3, #255	@ tmp177, prephitmp.2199,
	beq	.L527	@,
.L568:
	movw	r0, #:lower16:g_event_report	@ tmp178,
	movt	r0, #:upper16:g_event_report	@ tmp178,
	ldr	ip, [r0, #0]	@ g_event_report.448, g_event_report
	cmp	ip, #0	@ g_event_report.448,
	beq	.L528	@,
	movw	lr, #:lower16:113648	@ tmp179,
	movt	lr, #:upper16:113648	@ tmp179,
	mov	r2, #0	@,
	mov	r1, #103	@,
	mov	r3, r2	@,
	ldr	r0, [r4, lr]	@, <variable>.ChanID
	blx	ip	@ g_event_report.448
	movw	r1, #:lower16:78668	@ tmp181,
	movt	r1, #:upper16:78668	@ tmp181,
	ldr	r3, [r4, r1]	@ prephitmp.2199, <variable>.CodecInfo.StreamIntegrality
.L528:
	movw	ip, #:lower16:78676	@ tmp183,
	movt	ip, #:upper16:78676	@ tmp183,
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC43	@,
	ldr	r2, [r4, ip]	@, <variable>.CodecInfo.Frame_Cnt
	movt	r1, #:upper16:.LC43	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.38854,
.L524:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L525:
	movw	r3, #:lower16:78668	@ tmp176,
	movt	r3, #:upper16:78668	@ tmp176,
	movw	lr, #:lower16:113652	@ tmp172,
	movt	lr, #:upper16:113652	@ tmp172,
	ldr	r3, [r4, r3]	@ prephitmp.2199, <variable>.CodecInfo.StreamIntegrality
	ldr	r2, [r4, lr]	@ <variable>.numTotalFrame, <variable>.numTotalFrame
	ands	r7, r3, #255	@ tmp177, prephitmp.2199,
	add	ip, r2, #1	@ tmp175, <variable>.numTotalFrame,
	str	ip, [r4, lr]	@ tmp175, <variable>.numTotalFrame
	bne	.L568	@,
.L527:
	movw	r2, #:lower16:78716	@ tmp185,
	movt	r2, #:upper16:78716	@ tmp185,
	ldr	r6, [r4, r2]	@ <variable>.CodecInfo.Imgbuf_allocated, <variable>.CodecInfo.Imgbuf_allocated
	cmp	r6, #0	@ <variable>.CodecInfo.Imgbuf_allocated,
	beq	.L569	@,
	movw	r9, #:lower16:78656	@ tmp190,
	movt	r9, #:upper16:78656	@ tmp190,
	ldr	r8, [r4, r9]	@ <variable>.CodecInfo.UsedDecMode, <variable>.CodecInfo.UsedDecMode
	sub	r6, r8, #2	@ tmp191, <variable>.CodecInfo.UsedDecMode,
	cmp	r6, #1	@ tmp191,
	bls	.L530	@,
	ldr	sl, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	r1, [sl, #8]	@ prephitmp.2205, <variable>.s32DecMode
.L531:
	movw	r3, #:lower16:78656	@ tmp248,
	movt	r3, #:upper16:78656	@ tmp248,
	sub	r2, r1, #1	@ tmp249, prephitmp.2205,
	str	r1, [r4, r3]	@ prephitmp.2205, <variable>.CodecInfo.UsedDecMode
	cmp	r2, #3	@ tmp249,
	ldrls	pc, [pc, r2, asl #2]	@ tmp249
	b	.L533	@
.L538:
	.word	.L534
	.word	.L535
	.word	.L536
	.word	.L537
.L530:
	ldr	r0, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	r2, [r0, #8]	@ D.38880, <variable>.s32DecMode
	cmp	r2, #4	@ D.38880,
	cmpne	r2, #1	@, D.38880,
	mov	r1, r2	@ prephitmp.2205, D.38880
	bhi	.L531	@,
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC45	@,
	movt	r1, #:upper16:.LC45	@,
	movw	r6, #:lower16:113648	@ tmp207,
	bl	dprint_vfmw	@
	movw	ip, #:lower16:78668	@ tmp203,
	movt	ip, #:upper16:78668	@ tmp203,
	movt	r6, #:upper16:113648	@ tmp207,
	movw	sl, #:lower16:78748	@ tmp209,
	movt	sl, #:upper16:78748	@ tmp209,
	ldr	r2, [r4, ip]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	orr	r1, r2, #128	@ tmp206, <variable>.CodecInfo.StreamIntegrality,
	str	r1, [r4, ip]	@ tmp206, <variable>.CodecInfo.StreamIntegrality
	ldr	r1, [r4, sl]	@, <variable>.CodecInfo.BwdFsID
	bl	FSP_GetFsImagePtr	@
	subs	r8, r0, #0	@ pImg,
	beq	.L532	@,
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	movw	r9, #:lower16:78744	@ tmp233,
	ldr	r1, [r8, #212]	@, <variable>.p_usrdat
	movt	r9, #:upper16:78744	@ tmp233,
	bl	FreeUsdByDec	@
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	ldr	r1, [r8, #216]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	ldr	r1, [r8, #220]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	ldr	r1, [r8, #224]	@, <variable>.p_usrdat
	bl	FreeUsdByDec	@
	str	r7, [r8, #224]	@ tmp177, <variable>.p_usrdat
	str	r7, [r8, #212]	@ tmp177, <variable>.p_usrdat
	mov	r2, #1	@,
	str	r7, [r8, #216]	@ tmp177, <variable>.p_usrdat
	str	r7, [r8, #220]	@ tmp177, <variable>.p_usrdat
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	ldr	r1, [r4, sl]	@, <variable>.CodecInfo.BwdFsID
	bl	FSP_ClearLogicFs	@
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	ldr	r1, [r4, r9]	@, <variable>.CodecInfo.FwdFsID
	mov	r2, #1	@,
	bl	FSP_ClearLogicFs	@
	str	r7, [r4, sl]	@ tmp177, <variable>.CodecInfo.BwdFsID
	str	r7, [r4, r9]	@ tmp177, <variable>.CodecInfo.FwdFsID
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	bl	FSP_GetFspType	@
	cmp	r0, #0	@,
	bne	.L570	@,
.L532:
	ldr	r7, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	movw	r3, #:lower16:78708	@ tmp245,
	movt	r3, #:upper16:78708	@ tmp245,
	mov	lr, #0	@ tmp246,
	str	lr, [r4, r3]	@ tmp246, <variable>.CodecInfo.RefNum
	ldr	r1, [r7, #8]	@ prephitmp.2205, <variable>.s32DecMode
	b	.L531	@
.L569:
	movw	r3, #:lower16:78676	@ tmp188,
	movt	r3, #:upper16:78676	@ tmp188,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC44	@,
	ldr	r2, [r4, r3]	@, <variable>.CodecInfo.Frame_Cnt
	movt	r1, #:upper16:.LC44	@,
	bl	dprint_vfmw	@
	mov	r0, r6	@ D.38854, <variable>.CodecInfo.Imgbuf_allocated
	b	.L524	@
.L537:
	ldrb	r7, [r5, #22]	@ zero_extendqisi2	@ prephitmp.2273, <variable>.picture_coding_type
	cmp	r7, #1	@ prephitmp.2273,
	movweq	r3, #:lower16:113660	@ tmp266,
	movteq	r3, #:upper16:113660	@ tmp266,
	moveq	r2, #0	@ tmp267,
	streq	r2, [r4, r3]	@ tmp267, <variable>.PPicFound
	ldreqb	r7, [r5, #22]	@ zero_extendqisi2	@ prephitmp.2273, <variable>.picture_coding_type
	cmp	r7, #3	@ prephitmp.2273,
	beq	.L571	@,
	cmp	r7, #2	@ prephitmp.2273,
	beq	.L548	@,
.L566:
	mov	r9, r7	@ prephitmp.2207, prephitmp.2273
	ldrb	r7, [r5, #9]	@ zero_extendqisi2	@ prephitmp.2273, <variable>.picture_structure
	mov	sl, #1	@ ret,
.L539:
	movw	r0, #:lower16:78616	@ tmp278,
	movw	r2, #:lower16:78720	@ tmp279,
	movt	r0, #:upper16:78616	@ tmp278,
	movt	r2, #:upper16:78720	@ tmp279,
	add	r3, r4, #78848	@, pCtx,
	movw	lr, #:lower16:78676	@ tmp277,
	ldr	r8, [r4, r0]	@ <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.BsOffset
	movt	lr, #:upper16:78676	@ tmp277,
	ldr	r1, [r4, r2]	@ <variable>.CodecInfo.Used_byte, <variable>.CodecInfo.Used_byte
	add	r0, r3, #64	@,,
	add	r6, r8, r1	@ D.38939, <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.Used_byte
	ldr	r8, [r4, lr]	@ temp.2243, <variable>.CodecInfo.Frame_Cnt
	bl	BsPos	@
	mov	r3, r9	@, prephitmp.2207
	movw	r1, #:lower16:.LC46	@,
	movt	r1, #:upper16:.LC46	@,
	mov	r2, r8	@, temp.2243
	str	r7, [sp, #0]	@ prephitmp.2273,
	add	ip, r6, r0, lsr #3	@, tmp286, D.38939,,
	mov	r0, #18	@,
	str	ip, [sp, #4]	@ tmp286,
	bl	dprint_vfmw	@
	movw	r3, #:lower16:78668	@ tmp287,
	movt	r3, #:upper16:78668	@ tmp287,
	ldr	r7, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	r0, [r4, r3]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	bic	r6, r0, #14155776	@ tmp290, <variable>.CodecInfo.StreamIntegrality,
	str	r6, [r4, r3]	@ tmp290, <variable>.CodecInfo.StreamIntegrality
	ldr	r0, [r7, #700]	@ <variable>.s32SupportAllP, <variable>.s32SupportAllP
	cmp	r0, #1	@ <variable>.s32SupportAllP,
	beq	.L572	@,
	movw	ip, #:lower16:78708	@ tmp297,
	movt	ip, #:upper16:78708	@ tmp297,
	ldr	r3, [r4, ip]	@ temp.2246, <variable>.CodecInfo.RefNum
	cmp	r3, #0	@ temp.2246,
	bne	.L552	@,
	ldrb	r1, [r5, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	sub	lr, r1, #2	@ tmp300, <variable>.picture_coding_type,
	uxtb	r6, lr	@ tmp301, tmp300
	cmp	r6, #1	@ tmp301,
	bls	.L573	@,
.L550:
	movw	r6, #:lower16:113648	@ tmp305,
	movw	r7, #:lower16:78744	@ tmp307,
	movt	r6, #:upper16:113648	@ tmp305,
	movt	r7, #:upper16:78744	@ tmp307,
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	ldr	r1, [r4, r7]	@, <variable>.CodecInfo.FwdFsID
	bl	FSP_GetFsImagePtr	@
	movw	r2, #:lower16:78748	@ tmp311,
	movt	r2, #:upper16:78748	@ tmp311,
	ldr	r1, [r4, r2]	@, <variable>.CodecInfo.BwdFsID
	mov	r7, r0	@ pFwdImg,
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	bl	FSP_GetFsImagePtr	@
	cmp	r7, #0	@ pFwdImg,
	cmpne	r0, #0	@, pBwdImg,
	movne	r6, #0	@, tmp319
	moveq	r6, #1	@, tmp319
	beq	.L574	@,
	ldrb	r3, [r5, #22]	@ zero_extendqisi2	@ temp.2253, <variable>.picture_coding_type
	cmp	r3, #2	@ temp.2253,
	beq	.L575	@,
	cmp	r3, #3	@ temp.2253,
	beq	.L576	@,
.L555:
	cmp	sl, #0	@ ret,
	movne	r0, #1	@ D.38854,
	bne	.L524	@,
	ldrb	r1, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	cmp	r1, #3	@ <variable>.picture_structure,
	beq	.L558	@,
	movw	r2, #:lower16:78680	@ tmp330,
	movt	r2, #:upper16:78680	@ tmp330,
	ldr	r3, [r4, r2]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	cmp	r3, #0	@ <variable>.CodecInfo.Second_Field,
	movne	r0, sl	@ D.38854, ret
	bne	.L524	@,
.L558:
	ldrb	r0, [r5, #27]	@ zero_extendqisi2	@ <variable>.progressive_sequence, <variable>.progressive_sequence
	cmp	r0, #1	@ <variable>.progressive_sequence,
	beq	.L577	@,
	ldrb	lr, [r5, #18]	@ zero_extendqisi2	@ <variable>.progressive_frame, <variable>.progressive_frame
	cmp	lr, #1	@ <variable>.progressive_frame,
	beq	.L578	@,
	movw	r0, #:lower16:78832	@ tmp353,
	movt	r0, #:upper16:78832	@ tmp353,
	movw	lr, #:lower16:78828	@ tmp356,
	movt	lr, #:upper16:78828	@ tmp356,
	ldr	r2, [r4, r0]	@ <variable>.GopFrmCnt, <variable>.GopFrmCnt
	add	r1, r2, #1	@ temp.2265, <variable>.GopFrmCnt,
	str	r1, [r4, r0]	@ temp.2265, <variable>.GopFrmCnt
	mov	r3, r1, asl #1	@ tmp357, temp.2265,
	str	r3, [r4, lr]	@ tmp357, <variable>.GopFldCnt
.L560:
	movw	r2, #:lower16:78824	@ tmp358,
	movt	r2, #:upper16:78824	@ tmp358,
	movw	r3, #:lower16:78676	@ tmp362,
	movt	r3, #:upper16:78676	@ tmp362,
	ldr	ip, [r4, r2]	@ <variable>.GopFrmCntNoRpt, <variable>.GopFrmCntNoRpt
	mov	r0, #0	@ D.38854,
	add	r1, ip, #1	@ tmp361, <variable>.GopFrmCntNoRpt,
	str	r1, [r4, r2]	@ tmp361, <variable>.GopFrmCntNoRpt
	ldr	lr, [r4, r3]	@ <variable>.CodecInfo.Frame_Cnt, <variable>.CodecInfo.Frame_Cnt
	add	ip, lr, #1	@ tmp365, <variable>.CodecInfo.Frame_Cnt,
	str	ip, [r4, r3]	@ tmp365, <variable>.CodecInfo.Frame_Cnt
	b	.L524	@
.L536:
	ldrb	r9, [r5, #22]	@ zero_extendqisi2	@ prephitmp.2207, <variable>.picture_coding_type
	mov	sl, #0	@ ret,
	ldrb	r7, [r5, #9]	@ zero_extendqisi2	@ prephitmp.2273, <variable>.picture_structure
	b	.L539	@
.L535:
	ldrb	r9, [r5, #22]	@ zero_extendqisi2	@ prephitmp.2207, <variable>.picture_coding_type
	sub	r1, r9, #2	@ tmp255, prephitmp.2207,
	uxtb	sl, r1	@ tmp256, tmp255
	cmp	sl, #1	@ tmp256,
	bls	.L542	@,
	ldrb	r7, [r5, #9]	@ zero_extendqisi2	@ prephitmp.2273, <variable>.picture_structure
	mov	sl, #1	@ ret,
	b	.L539	@
.L534:
	ldrb	r7, [r5, #22]	@ zero_extendqisi2	@ prephitmp.2273, <variable>.picture_coding_type
	cmp	r7, #3	@ prephitmp.2273,
	bne	.L566	@,
	ldrb	r6, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	cmp	r6, #3	@ <variable>.picture_structure,
	beq	.L541	@,
	movw	r9, #:lower16:78680	@ tmp251,
	movt	r9, #:upper16:78680	@ tmp251,
	mov	sl, #0	@ ret,
	ldr	r0, [r4, r9]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	cmp	r0, sl	@ <variable>.CodecInfo.Second_Field,
	movne	r8, #0	@, tmp254
	moveq	r8, #1	@, tmp254
	str	r8, [r4, r9]	@ tmp254, <variable>.CodecInfo.Second_Field
	ldrb	r9, [r5, #22]	@ zero_extendqisi2	@ prephitmp.2207, <variable>.picture_coding_type
	ldrb	r7, [r5, #9]	@ zero_extendqisi2	@ prephitmp.2273, <variable>.picture_structure
	b	.L539	@
.L533:
	ldrb	r9, [r5, #22]	@ zero_extendqisi2	@ prephitmp.2207, <variable>.picture_coding_type
	mov	sl, #1	@ ret,
	ldrb	r7, [r5, #9]	@ zero_extendqisi2	@ prephitmp.2273, <variable>.picture_structure
	b	.L539	@
.L552:
	cmp	r3, #1	@ temp.2246,
	bhi	.L550	@,
	ldrb	r3, [r5, #22]	@ zero_extendqisi2	@ <variable>.picture_coding_type, <variable>.picture_coding_type
	cmp	r3, #3	@ <variable>.picture_coding_type,
	bne	.L550	@,
	movw	r1, #:lower16:.LC50	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC50	@,
	mov	sl, #0	@ ret,
	bl	dprint_vfmw	@
	b	.L550	@
.L572:
	movw	r7, #:lower16:78708	@ tmp293,
	movt	r7, #:upper16:78708	@ tmp293,
	ldr	r3, [r4, r7]	@ <variable>.CodecInfo.RefNum, <variable>.CodecInfo.RefNum
	cmp	r3, #0	@ <variable>.CodecInfo.RefNum,
	bne	.L550	@,
	ldrb	r2, [r5, #22]	@ zero_extendqisi2	@ D.38904, <variable>.picture_coding_type
	cmp	r2, #3	@ D.38904,
	beq	.L579	@,
	cmp	r2, #2	@ D.38904,
	bne	.L550	@,
	movw	r1, #:lower16:.LC48	@,
	movt	r1, #:upper16:.LC48	@,
	bl	dprint_vfmw	@
	b	.L550	@
.L574:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC51	@,
	ldr	r2, .L582	@,
	movt	r1, #:upper16:.LC51	@,
	movw	r3, #847	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.38854,
	b	.L524	@
.L575:
	ldr	ip, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	r2, [r7, #200]	@ D.38983, <variable>.error_level
	ldr	r3, [ip, #0]	@ D.38984, <variable>.s32RefErrThr
	cmp	r2, r3	@ D.38983, D.38984
	bls	.L555	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	mov	r0, r6	@ D.38854, tmp319
	b	.L524	@
.L576:
	ldr	lr, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	r2, [r7, #200]	@ temp.2255, <variable>.error_level
	ldr	r3, [lr, #0]	@ temp.2257, <variable>.s32RefErrThr
	cmp	r2, r3	@ temp.2255, temp.2257
	bhi	.L580	@,
	ldr	r2, [r0, #200]	@ D.39000, <variable>.error_level
	cmp	r3, r2	@ temp.2257, D.39000
	bcs	.L555	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC54	@,
	movt	r1, #:upper16:.LC54	@,
	bl	dprint_vfmw	@
	mov	r0, r6	@ D.38854, tmp319
	b	.L524	@
.L577:
	movw	r3, #:lower16:78832	@ tmp333,
	movt	r3, #:upper16:78832	@ tmp333,
	ldrb	ip, [r5, #16]	@ zero_extendqisi2	@ <variable>.repeat_first_field, <variable>.repeat_first_field
	movw	lr, #:lower16:78828	@ tmp340,
	ldr	r2, [r4, r3]	@ <variable>.GopFrmCnt, <variable>.GopFrmCnt
	movt	lr, #:upper16:78828	@ tmp340,
	ldrb	r0, [r5, #10]	@ zero_extendqisi2	@ <variable>.top_field_first, <variable>.top_field_first
	add	r1, r2, #1	@ tmp334, <variable>.GopFrmCnt,
	add	r2, r1, ip	@ tmp337, tmp334, <variable>.repeat_first_field
	add	r1, r2, r0	@ D.39017, tmp337, <variable>.top_field_first
	str	r1, [r4, r3]	@ D.39017, <variable>.GopFrmCnt
	mov	ip, r1, asl #1	@ tmp341, D.39017,
	str	ip, [r4, lr]	@ tmp341, <variable>.GopFldCnt
	b	.L560	@
.L580:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC53	@,
	movt	r1, #:upper16:.LC53	@,
	bl	dprint_vfmw	@
	mov	r0, r6	@ D.38854, tmp319
	b	.L524	@
.L571:
	movw	r8, #:lower16:113660	@ tmp268,
	movt	r8, #:upper16:113660	@ tmp268,
	ldr	sl, [r4, r8]	@ <variable>.PPicFound, <variable>.PPicFound
	cmp	sl, #0	@ <variable>.PPicFound,
	bne	.L566	@,
	ldrb	r9, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	cmp	r9, #3	@ <variable>.picture_structure,
	beq	.L541	@,
	movw	r1, #:lower16:78680	@ tmp271,
	movt	r1, #:upper16:78680	@ tmp271,
	ldr	ip, [r4, r1]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	rsbs	r0, ip, #1	@ tmp274, <variable>.CodecInfo.Second_Field
	movcc	r0, #0	@ tmp274
	str	r0, [r4, r1]	@ tmp274, <variable>.CodecInfo.Second_Field
	ldrb	r9, [r5, #22]	@ zero_extendqisi2	@ prephitmp.2207, <variable>.picture_coding_type
	ldrb	r7, [r5, #9]	@ zero_extendqisi2	@ prephitmp.2273, <variable>.picture_structure
	b	.L539	@
.L542:
	cmp	r9, #2	@ prephitmp.2207,
	beq	.L581	@,
.L543:
	ldrb	r7, [r5, #9]	@ zero_extendqisi2	@ <variable>.picture_structure, <variable>.picture_structure
	cmp	r7, #3	@ <variable>.picture_structure,
	beq	.L567	@,
	movw	r3, #:lower16:78680	@ tmp262,
	movt	r3, #:upper16:78680	@ tmp262,
	mov	sl, #0	@ ret,
	ldr	r6, [r4, r3]	@ <variable>.CodecInfo.Second_Field, <variable>.CodecInfo.Second_Field
	cmp	r6, sl	@ <variable>.CodecInfo.Second_Field,
	movne	lr, #0	@, tmp265
	moveq	lr, #1	@, tmp265
	str	lr, [r4, r3]	@ tmp265, <variable>.CodecInfo.Second_Field
	ldrb	r9, [r5, #22]	@ zero_extendqisi2	@ prephitmp.2207, <variable>.picture_coding_type
	ldrb	r7, [r5, #9]	@ zero_extendqisi2	@ prephitmp.2273, <variable>.picture_structure
	b	.L539	@
.L578:
	movw	r2, #:lower16:78832	@ tmp343,
	movt	r2, #:upper16:78832	@ tmp343,
	movw	r3, #:lower16:78828	@ tmp347,
	movt	r3, #:upper16:78828	@ tmp347,
	ldr	ip, [r4, r2]	@ <variable>.GopFrmCnt, <variable>.GopFrmCnt
	ldr	lr, [r4, r3]	@ <variable>.GopFldCnt, <variable>.GopFldCnt
	add	r0, ip, #1	@ tmp346, <variable>.GopFrmCnt,
	str	r0, [r4, r2]	@ tmp346, <variable>.GopFrmCnt
	ldrb	ip, [r5, #16]	@ zero_extendqisi2	@ <variable>.repeat_first_field, <variable>.repeat_first_field
	add	r1, lr, #2	@ tmp349, <variable>.GopFldCnt,
	add	r0, r1, ip	@ tmp352, tmp349, <variable>.repeat_first_field
	str	r0, [r4, r3]	@ tmp352, <variable>.GopFldCnt
	b	.L560	@
.L548:
	movw	r2, #:lower16:113660	@ tmp275,
	movt	r2, #:upper16:113660	@ tmp275,
	mov	sl, #1	@ tmp276,
	str	sl, [r4, r2]	@ tmp276, <variable>.PPicFound
	ldrb	r9, [r5, #22]	@ zero_extendqisi2	@ prephitmp.2207, <variable>.picture_coding_type
	ldrb	r7, [r5, #9]	@ zero_extendqisi2	@ prephitmp.2273, <variable>.picture_structure
	b	.L539	@
.L573:
	movw	r1, #:lower16:.LC49	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC49	@,
	mov	sl, r3	@ ret, temp.2246
	bl	dprint_vfmw	@
	b	.L550	@
.L541:
	mov	r9, #3	@ prephitmp.2207,
.L567:
	mov	sl, #0	@ ret,
	b	.L539	@
.L579:
	movw	r1, #:lower16:.LC47	@,
	movt	r1, #:upper16:.LC47	@,
	mov	sl, r3	@ ret, <variable>.CodecInfo.RefNum
	bl	dprint_vfmw	@
	b	.L550	@
.L570:
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	bl	FSP_GetNullLogicFs	@
	str	r0, [r4, sl]	@ D.38902, <variable>.CodecInfo.BwdFsID
	str	r0, [r4, r9]	@ D.38902, <variable>.CodecInfo.FwdFsID
	b	.L532	@
.L581:
	movw	r2, #45329	@ tmp257,
	ldrb	ip, [r4, r2]	@ zero_extendqisi2	@ <variable>.CodecInfo.Last_FieldStruct, <variable>.CodecInfo.Last_FieldStruct
	cmp	ip, #3	@ <variable>.CodecInfo.Last_FieldStruct,
	beq	.L543	@,
	movw	r7, #45328	@ tmp259,
	ldrb	sl, [r4, r7]	@ zero_extendqisi2	@ <variable>.CodecInfo.LastDecPicCodingType, <variable>.CodecInfo.LastDecPicCodingType
	cmp	sl, #1	@ <variable>.CodecInfo.LastDecPicCodingType,
	bne	.L543	@,
	ldrb	r7, [r5, #9]	@ zero_extendqisi2	@ prephitmp.2273, <variable>.picture_structure
	b	.L539	@
.L583:
	.align	2
.L582:
	.word	.LANCHOR0+1164
	.fnend
	.size	MP2_DecodingDecide, .-MP2_DecodingDecide
	.align	2
	.global	MP2_ArrangeVHBMem
	.type	MP2_ArrangeVHBMem, %function
MP2_ArrangeVHBMem:
	.fnstart
.LFB1529:
	@ args = 0, pretend = 0, frame = 40
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
	movw	r3, #:lower16:79992	@ tmp157,
	movt	r3, #:upper16:79992	@ tmp157,
	mov	r6, r0	@ pCtx, pCtx
	ldr	r3, [r0, r3]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	ldr	r2, [r3, #48]	@ D.38585, <variable>.horizontal_size
	cmp	r2, #31	@ D.38585,
	ldrls	r3, [r3, #52]	@ prephitmp.2288, <variable>.vertical_size
	bls	.L586	@,
	ldr	r3, [r3, #52]	@ prephitmp.2288, <variable>.vertical_size
	cmp	r3, #31	@ prephitmp.2288,
	bls	.L586	@,
	ldr	r1, [r0, #0]	@ D.38592, <variable>.pstExtraData
	ldr	r0, [r1, #32]	@ <variable>.eCapLevel, <variable>.eCapLevel
	cmp	r0, #25	@ <variable>.eCapLevel,
	beq	.L609	@,
	mov	r4, r2	@ PicWidth, D.38585
	mov	r5, r3	@ PicHeight, prephitmp.2288
	mov	r8, #5	@ prephitmp.2290,
	mov	sl, #2	@ PmvNum,
	mov	r9, #3	@ DecFsNum,
.L596:
	sub	r7, fp, #84	@ tmp193,,
	mov	r1, #36	@,
	mov	r0, r7	@, tmp193
	bl	__memzero	@
	ldr	r3, [r6, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	mov	r0, #0	@ tmp171,
	ldr	ip, [r3, #20]	@ <variable>.s32DnrDispOutEnable, <variable>.s32DnrDispOutEnable
	str	r4, [fp, #-56]	@ PicWidth, FspInstCfg.s32DispFsWidth
	strb	r0, [fp, #-82]	@ tmp171, FspInstCfg.s32RprEnable
	str	r4, [fp, #-72]	@ PicWidth, FspInstCfg.s32DecFsWidth
	str	r5, [fp, #-52]	@ PicHeight, FspInstCfg.s32DispFsHeight
	strb	ip, [fp, #-84]	@ <variable>.s32DnrDispOutEnable, FspInstCfg.s32DispLoopEnable
	str	r5, [fp, #-68]	@ PicHeight, FspInstCfg.s32DecFsHeight
	ldr	r5, [r3, #32]	@ <variable>.eCapLevel, <variable>.eCapLevel
	strb	r8, [fp, #-77]	@ prephitmp.2290, FspInstCfg.s32ExpectedDispFsNum
	cmp	r5, #24	@ <variable>.eCapLevel,
	movw	r5, #:lower16:113648	@ tmp182,
	uxtbne	r0, r9	@ iftmp.441, DecFsNum
	strb	r0, [fp, #-79]	@ iftmp.441, FspInstCfg.s32ExpectedDecFsNum
	ldr	r1, [r3, #32]	@ <variable>.eCapLevel, <variable>.eCapLevel
	movt	r5, #:upper16:113648	@ tmp182,
	cmp	r1, #24	@ <variable>.eCapLevel,
	mov	r1, r7	@, tmp193
	uxtbne	sl, sl	@ iftmp.442, PmvNum
	mov	r7, #0	@ tmp180,
	moveq	sl, #1	@ iftmp.442,
	strb	sl, [fp, #-76]	@ iftmp.442, FspInstCfg.s32ExpectedPmvNum
	ldr	r0, [r6, r5]	@, <variable>.ChanID
	strb	r7, [fp, #-80]	@ tmp180, FspInstCfg.s32UserDec
	bl	FSP_ConfigInstance	@
	subs	r4, r0, #0	@ D.38636,
	bne	.L606	@,
	ldr	lr, [r6, #0]	@ temp.2317, <variable>.pstExtraData
	sub	r3, fp, #48	@,,
	ldr	r0, [r6, r5]	@, <variable>.ChanID
	ldr	r2, [lr, #28]	@, <variable>.s32SyntaxMemSize
	ldr	r1, [lr, #24]	@, <variable>.s32SyntaxMemAddr
	bl	FSP_PartitionFsMemory	@
	cmp	r0, r7	@,
	moveq	r0, #1	@ D.38589,
	beq	.L588	@,
	mov	r0, r4	@, D.38636
	movw	r1, #:lower16:.LC57	@,
	movt	r1, #:upper16:.LC57	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ D.38589, D.38636
	b	.L588	@
.L586:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC55	@,
	movt	r1, #:upper16:.LC55	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.38589,
.L588:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L606:
	mov	r0, r7	@, tmp180
	movw	r1, #:lower16:.LC58	@,
	movt	r1, #:upper16:.LC58	@,
	bl	dprint_vfmw	@
	mov	r0, r7	@ D.38589, tmp180
	b	.L588	@
.L609:
	ldr	ip, [r1, #784]	@ <variable>.stChanOption.s32ReRangeEn, <variable>.stChanOption.s32ReRangeEn
	cmp	ip, #0	@ <variable>.stChanOption.s32ReRangeEn,
	bne	.L590	@,
	ldr	r4, [r1, #740]	@ PicWidth, <variable>.stChanOption.s32MaxWidth
	cmp	r2, r4	@ D.38585, PicWidth
	ldrhi	r5, [r1, #744]	@ PicHeight, <variable>.stChanOption.s32MaxHeight
	bhi	.L592	@,
	ldr	r5, [r1, #744]	@ PicHeight, <variable>.stChanOption.s32MaxHeight
	cmp	r3, r5	@ prephitmp.2288, PicHeight
	bhi	.L592	@,
	ldr	r2, [r1, #772]	@ <variable>.stChanOption.s32SupportBFrame, <variable>.stChanOption.s32SupportBFrame
	ldr	r9, [r1, #764]	@ D.38605, <variable>.stChanOption.s32MaxRefFrameNum
	cmp	r2, #0	@ <variable>.stChanOption.s32SupportBFrame,
	moveq	sl, #1	@ PmvNum,
	beq	.L595	@,
	add	sl, r9, #1	@ PmvNum.2303, D.38605,
	cmp	sl, #17	@ PmvNum.2303,
	movge	sl, #17	@ PmvNum,
.L595:
	add	r9, r9, #2	@ DecFsNum, D.38605,
	ldrb	r8, [r1, #792]	@ zero_extendqisi2	@ prephitmp.2290, <variable>.stChanOption.s32DisplayFrameNum
	b	.L596	@
.L590:
	ldr	ip, [r1, #740]	@ D.38599, <variable>.stChanOption.s32MaxWidth
	cmp	r2, ip	@ D.38585, D.38599
	ldrhi	lr, [r1, #744]	@ prephitmp.2292, <variable>.stChanOption.s32MaxHeight
	bhi	.L598	@,
	ldr	lr, [r1, #744]	@ prephitmp.2292, <variable>.stChanOption.s32MaxHeight
	cmp	r3, lr	@ prephitmp.2288, prephitmp.2292
	bhi	.L598	@,
	ldr	r4, [r1, #772]	@ <variable>.stChanOption.s32SupportBFrame, <variable>.stChanOption.s32SupportBFrame
	ldr	r9, [r1, #764]	@ temp.2306, <variable>.stChanOption.s32MaxRefFrameNum
	cmp	r4, #0	@ <variable>.stChanOption.s32SupportBFrame,
	moveq	sl, #1	@ PmvNum,
	beq	.L601	@,
	add	sl, r9, #1	@ PmvNum.2308, temp.2306,
	cmp	sl, #17	@ PmvNum.2308,
	movge	sl, #17	@ PmvNum,
.L601:
	ldrb	r8, [r1, #792]	@ zero_extendqisi2	@ prephitmp.2290, <variable>.stChanOption.s32DisplayFrameNum
	add	r9, r9, #2	@ DecFsNum, temp.2306,
	mov	r4, r2	@ PicWidth, D.38585
	mov	r5, r3	@ PicHeight, prephitmp.2288
	b	.L596	@
.L598:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC56	@,
	movt	r1, #:upper16:.LC56	@,
	stmia	sp, {ip, lr}	@ phole stm
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.38589,
	b	.L588	@
.L592:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC56	@,
	movt	r1, #:upper16:.LC56	@,
	stmia	sp, {r4, r5}	@ phole stm
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.38589,
	b	.L588	@
	.fnend
	.size	MP2_ArrangeVHBMem, .-MP2_ArrangeVHBMem
	.align	2
	.global	MP2_GetSequenceInfo
	.type	MP2_GetSequenceInfo, %function
MP2_GetSequenceInfo:
	.fnstart
.LFB1535:
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
	movw	r3, #:lower16:78704	@ tmp156,
	movt	r3, #:upper16:78704	@ tmp156,
	mov	r4, r0	@ pCtx, pCtx
	movw	ip, #:lower16:79996	@ tmp155,
	movw	r0, #:lower16:79992	@ tmp154,
	ldr	r2, [r4, r3]	@ <variable>.CodecInfo.MpegFlag, <variable>.CodecInfo.MpegFlag
	movt	r0, #:upper16:79992	@ tmp154,
	movt	ip, #:upper16:79996	@ tmp155,
	mov	r1, #0	@ tmp151,
	cmp	r2, #1	@ <variable>.CodecInfo.MpegFlag,
	ldr	r5, [r4, r0]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	ldr	r9, [r4, ip]	@ pSyntaxInfOld, <variable>.pSyntaxInfOld
	str	r1, [fp, #-56]	@ tmp151, NewNum
	str	r1, [fp, #-48]	@ tmp151, RefNum
	str	r1, [fp, #-52]	@ tmp151, ReadNum
	beq	.L612	@,
	cmp	r2, #2	@ <variable>.CodecInfo.MpegFlag,
	beq	.L637	@,
	movw	r2, #:lower16:78668	@ tmp169,
	movt	r2, #:upper16:78668	@ tmp169,
	ldr	r1, [r4, r2]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	tst	r1, #3538944	@ <variable>.CodecInfo.StreamIntegrality,
	bne	.L638	@,
.L617:
	mov	r2, #1	@ tmp183,
	str	r2, [r4, r3]	@ tmp183, <variable>.CodecInfo.MpegFlag
.L615:
	mov	r0, #17	@,
	movw	r1, #:lower16:.LC59	@,
	movt	r1, #:upper16:.LC59	@,
	bl	dprint_vfmw	@
	movw	r3, #:lower16:78704	@ tmp185,
	movt	r3, #:upper16:78704	@ tmp185,
	ldr	r3, [r4, r3]	@ <variable>.CodecInfo.MpegFlag, <variable>.CodecInfo.MpegFlag
	cmp	r3, #1	@ <variable>.CodecInfo.MpegFlag,
	beq	.L639	@,
.L620:
	ldr	lr, [r5, #48]	@ <variable>.horizontal_size, <variable>.horizontal_size
	movw	r0, #:lower16:78704	@ tmp211,
	movt	r0, #:upper16:78704	@ tmp211,
	add	r2, lr, #15	@ tmp208, <variable>.horizontal_size,
	mov	r3, r2, lsr #4	@ tmp210, tmp208,
	str	r3, [r5, #56]	@ tmp210, <variable>.mb_width
	ldr	ip, [r4, r0]	@ <variable>.CodecInfo.MpegFlag, <variable>.CodecInfo.MpegFlag
	cmp	ip, #2	@ <variable>.CodecInfo.MpegFlag,
	beq	.L640	@,
.L621:
	ldr	r2, [r5, #52]	@ temp.2358, <variable>.vertical_size
	add	r3, r2, #15	@ tmp217, temp.2358,
	mov	r1, r3, lsr #4	@ iftmp.466, tmp217,
.L622:
	movw	ip, #:lower16:78704	@ tmp220,
	movt	ip, #:upper16:78704	@ tmp220,
	str	r1, [r5, #60]	@ iftmp.466, <variable>.mb_height
	mov	r1, #0	@ tmp219,
	str	r1, [r5, #64]	@ tmp219, <variable>.mb_height_progressive_subtract1mb
	ldr	lr, [r4, ip]	@ <variable>.CodecInfo.MpegFlag, <variable>.CodecInfo.MpegFlag
	cmp	lr, #2	@ <variable>.CodecInfo.MpegFlag,
	beq	.L641	@,
.L623:
	movw	r0, #:lower16:78716	@ tmp229,
	movt	r0, #:upper16:78716	@ tmp229,
	ldr	r3, [r4, r0]	@ prephitmp.2363, <variable>.CodecInfo.Imgbuf_allocated
	cmp	r3, #0	@ prephitmp.2363,
	beq	.L624	@,
	ldr	r1, [r5, #56]	@ <variable>.mb_width, <variable>.mb_width
	ldr	r2, [r9, #56]	@ <variable>.mb_width, <variable>.mb_width
	cmp	r1, r2	@ <variable>.mb_width, <variable>.mb_width
	beq	.L642	@,
.L624:
	movw	r6, #:lower16:113648	@ tmp234,
	movw	r8, #:lower16:78748	@ tmp236,
	movt	r6, #:upper16:113648	@ tmp234,
	movt	r8, #:upper16:78748	@ tmp236,
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	ldr	r1, [r4, r8]	@, <variable>.CodecInfo.BwdFsID
	bl	FSP_GetFsImagePtr	@
	subs	r7, r0, #0	@ pImg,
	beq	.L626	@,
	ldr	r1, [r7, #212]	@, <variable>.p_usrdat
	movw	sl, #:lower16:78744	@,
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	movt	sl, #:upper16:78744	@,
	str	sl, [fp, #-72]	@, %sfp
	bl	FreeUsdByDec	@
	ldr	r1, [r7, #216]	@, <variable>.p_usrdat
	mov	sl, #0	@ tmp250,
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	ldr	r1, [r7, #220]	@, <variable>.p_usrdat
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	ldr	r1, [r7, #224]	@, <variable>.p_usrdat
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	bl	FreeUsdByDec	@
	str	sl, [r7, #224]	@ tmp250, <variable>.p_usrdat
	str	sl, [r7, #212]	@ tmp250, <variable>.p_usrdat
	mov	r2, #1	@,
	str	sl, [r7, #216]	@ tmp250, <variable>.p_usrdat
	str	sl, [r7, #220]	@ tmp250, <variable>.p_usrdat
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	ldr	r1, [r4, r8]	@, <variable>.CodecInfo.BwdFsID
	bl	FSP_ClearLogicFs	@
	ldr	r3, [fp, #-72]	@, %sfp
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	mov	r2, #1	@,
	ldr	r1, [r4, r3]	@, <variable>.CodecInfo.FwdFsID
	bl	FSP_ClearLogicFs	@
	str	sl, [r4, r8]	@ tmp250, <variable>.CodecInfo.BwdFsID
	ldr	r7, [fp, #-72]	@, %sfp
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	str	sl, [r4, r7]	@ tmp250, <variable>.CodecInfo.FwdFsID
	bl	FSP_GetFspType	@
	cmp	r0, sl	@,
	bne	.L643	@,
.L626:
	add	ip, r4, #79872	@ D.39321, pCtx,
	movw	r2, #:lower16:78708	@ tmp272,
	add	r6, ip, #128	@ D.39321, D.39321,
	movt	r2, #:upper16:78708	@ tmp272,
	movw	lr, #:lower16:113648	@ tmp275,
	movt	lr, #:upper16:113648	@ tmp275,
	mov	r1, #0	@ tmp273,
	str	r1, [r4, r2]	@ tmp273, <variable>.CodecInfo.RefNum
	ldr	r0, [r4, lr]	@, <variable>.ChanID
	mov	r1, r6	@, D.39321
	bl	FSP_ClearNotInVoQueue	@
	ldr	r3, [r4, #0]	@ D.39324, <variable>.pstExtraData
	ldr	r0, [r3, #784]	@ <variable>.stChanOption.s32ReRangeEn, <variable>.stChanOption.s32ReRangeEn
	cmp	r0, #0	@ <variable>.stChanOption.s32ReRangeEn,
	bne	.L627	@,
	ldr	r7, [r3, #32]	@ <variable>.eCapLevel, <variable>.eCapLevel
	cmp	r7, #25	@ <variable>.eCapLevel,
	beq	.L644	@,
.L627:
	movw	r3, #:lower16:78716	@ tmp284,
	movt	r3, #:upper16:78716	@ tmp284,
	ldr	r0, [r4, r3]	@ <variable>.CodecInfo.Imgbuf_allocated, <variable>.CodecInfo.Imgbuf_allocated
	cmp	r0, #0	@ <variable>.CodecInfo.Imgbuf_allocated,
	beq	.L629	@,
	ldr	lr, [r9, #56]	@ <variable>.mb_width, <variable>.mb_width
	cmp	lr, #0	@ <variable>.mb_width,
	beq	.L629	@,
	ldr	r1, [r9, #60]	@ <variable>.mb_height, <variable>.mb_height
	cmp	r1, #0	@ <variable>.mb_height,
	bne	.L645	@,
.L629:
	movw	r7, #:lower16:113648	@ tmp294,
	movt	r7, #:upper16:113648	@ tmp294,
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	bl	FSP_GetFspType	@
	cmp	r0, #0	@,
	bne	.L630	@,
	sub	r3, fp, #56	@,,
	ldr	r0, [r4, r7]	@, <variable>.ChanID
	sub	r1, fp, #48	@,,
	sub	r2, fp, #52	@,,
	bl	VCTRL_GetChanImgNum	@
	ldr	ip, [r4, #0]	@ <variable>.pstExtraData, <variable>.pstExtraData
	ldr	r3, [ip, #784]	@ <variable>.stChanOption.s32ReRangeEn, <variable>.stChanOption.s32ReRangeEn
	cmp	r3, #1	@ <variable>.stChanOption.s32ReRangeEn,
	beq	.L646	@,
.L631:
	mov	r0, r6	@, D.39321
	mov	r6, #0	@ tmp310,
	bl	ResetVoQueue	@
	movw	r2, #:lower16:113665	@ tmp309,
	movt	r2, #:upper16:113665	@ tmp309,
	strb	r6, [r4, r2]	@ tmp310, <variable>.IsWaitToReRange
.L630:
	movw	r6, #:lower16:78716	@ tmp312,
	movw	r0, #:lower16:78732	@ tmp314,
	movt	r6, #:upper16:78716	@ tmp312,
	movt	r0, #:upper16:78732	@ tmp314,
	mov	r1, #0	@ tmp313,
	str	r1, [r4, r0]	@ tmp313, <variable>.CodecInfo.QueueImageNum
	mov	r0, r4	@, pCtx
	str	r1, [r4, r6]	@ tmp313, <variable>.CodecInfo.Imgbuf_allocated
	bl	MP2_ArrangeVHBMem	@
	movw	r1, #:lower16:.LC61	@,
	movt	r1, #:upper16:.LC61	@,
	str	r0, [r4, r6]	@, <variable>.CodecInfo.Imgbuf_allocated
	mov	r0, #1	@,
	ldr	ip, [r5, #56]	@ <variable>.mb_width, <variable>.mb_width
	ldr	r3, [r5, #60]	@ <variable>.mb_height, <variable>.mb_height
	mov	r2, ip, asl #4	@, <variable>.mb_width,
	mov	r3, r3, asl #4	@, <variable>.mb_height,
	bl	dprint_vfmw	@
.L628:
	movw	lr, #:lower16:g_event_report	@ tmp322,
	movt	lr, #:upper16:g_event_report	@ tmp322,
	ldr	ip, [lr, #0]	@ g_event_report.2384, g_event_report
	cmp	ip, #0	@ g_event_report.2384,
	beq	.L636	@,
	ldrh	r2, [r9, #56]	@, <variable>.mb_width
	movw	r3, #:lower16:113648	@ tmp328,
	movt	r3, #:upper16:113648	@ tmp328,
	strh	r2, [fp, #-64]	@ movhi	@, para
	sub	r2, fp, #64	@,,
	ldrh	r9, [r9, #60]	@, <variable>.mb_height
	strh	r9, [fp, #-62]	@ movhi	@, para
	ldrh	r1, [r5, #56]	@, <variable>.mb_width
	strh	r1, [fp, #-60]	@ movhi	@, para
	mov	r1, #2	@,
	ldrh	r5, [r5, #60]	@, <variable>.mb_height
	strh	r5, [fp, #-58]	@ movhi	@, para
	ldr	r0, [r4, r3]	@, <variable>.ChanID
	mov	r3, #8	@,
	blx	ip	@ g_event_report.2384
.L636:
	movw	ip, #:lower16:78716	@ tmp331,
	movt	ip, #:upper16:78716	@ tmp331,
	ldr	r3, [r4, ip]	@ prephitmp.2363, <variable>.CodecInfo.Imgbuf_allocated
.L625:
	movw	r0, #:lower16:78664	@ tmp332,
	movt	r0, #:upper16:78664	@ tmp332,
	str	r3, [r4, r0]	@ prephitmp.2363, <variable>.CodecInfo.NewSeqInited
.L634:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L637:
	movw	ip, #:lower16:78668	@ tmp164,
	movt	ip, #:upper16:78668	@ tmp164,
	ldr	r1, [r4, ip]	@ tmp166,
	and	lr, r1, #1769472	@ tmp165, tmp166,
	cmp	lr, #589824	@ tmp165,
	bne	.L615	@,
	b	.L617	@
.L612:
	movw	r0, #:lower16:78668	@ tmp158,
	movt	r0, #:upper16:78668	@ tmp158,
	movw	r1, #:lower16:1179666	@ tmp159,
	movt	r1, #:upper16:1179666	@ tmp159,
	ldr	ip, [r4, r0]	@ tmp161,
	and	lr, ip, r1	@ tmp159, tmp161, tmp159
	cmp	lr, #1179648	@ tmp159,
	moveq	r2, #2	@ tmp163,
	streq	r2, [r4, r3]	@ tmp163, <variable>.CodecInfo.MpegFlag
	b	.L615	@
.L639:
	mov	r2, #0	@ tmp198,
	mov	r1, #3	@ tmp191,
	mov	lr, #5	@ tmp197,
	strb	r3, [r5, #28]	@ <variable>.CodecInfo.MpegFlag, <variable>.chroma_format
	strb	r2, [r5, #8]	@ tmp198, <variable>.intra_dc_precision
	strb	r1, [r5, #9]	@ tmp191, <variable>.picture_structure
	str	lr, [r5, #144]	@ tmp197, <variable>.matrix_coefficients
	strb	r3, [r5, #27]	@ <variable>.CodecInfo.MpegFlag, <variable>.progressive_sequence
	strb	r3, [r5, #18]	@ <variable>.CodecInfo.MpegFlag, <variable>.progressive_frame
	strb	r3, [r5, #11]	@ <variable>.CodecInfo.MpegFlag, <variable>.frame_pred_frame_dct
	strb	r2, [r5, #12]	@ tmp198, <variable>.concealment_motion_vectors
	strb	r2, [r5, #13]	@ tmp198, <variable>.q_scale_type
	strb	r2, [r5, #14]	@ tmp198, <variable>.intra_vlc_format
	strb	r2, [r5, #15]	@ tmp198, <variable>.alternate_scan
	b	.L620	@
.L641:
	ldrb	r0, [r5, #27]	@ zero_extendqisi2	@ <variable>.progressive_sequence, <variable>.progressive_sequence
	cmp	r0, r1	@ <variable>.progressive_sequence,
	bne	.L623	@,
	add	ip, r2, #31	@ tmp223, temp.2358,
	add	lr, r2, #15	@ tmp226, temp.2358,
	mov	r3, ip, lsr #5	@ tmp224, tmp223,
	mov	r1, lr, lsr #4	@ tmp227, tmp226,
	rsb	r2, r1, r3, asl #1	@, tmp228, tmp227, tmp224,
	str	r2, [r5, #64]	@ tmp228, <variable>.mb_height_progressive_subtract1mb
	b	.L623	@
.L640:
	ldrb	r1, [r5, #27]	@ zero_extendqisi2	@ <variable>.progressive_sequence, <variable>.progressive_sequence
	cmp	r1, #0	@ <variable>.progressive_sequence,
	bne	.L621	@,
	ldr	r2, [r5, #52]	@ temp.2358, <variable>.vertical_size
	add	r0, r2, #31	@ tmp214, temp.2358,
	mov	ip, r0, lsr #5	@ tmp216, tmp214,
	mov	r1, ip, asl #1	@ iftmp.466, tmp216,
	b	.L622	@
.L638:
	tst	r1, #131072	@ prephitmp.2337,
	mov	r0, #2	@ tmp173,
	orreq	r1, r1, r0	@ prephitmp.2337, prephitmp.2337,
	streq	r1, [r4, r2]	@ prephitmp.2337, <variable>.CodecInfo.StreamIntegrality
	tst	r1, #1048576	@ prephitmp.2337,
	str	r0, [r4, r3]	@ tmp173, <variable>.CodecInfo.MpegFlag
	orreq	r1, r1, #16	@ tmp180, prephitmp.2337,
	movweq	r2, #:lower16:78668	@ tmp179,
	movwne	r3, #:lower16:78704	@ tmp178,
	movteq	r2, #:upper16:78668	@ tmp179,
	movweq	r3, #:lower16:78704	@ tmp181,
	movtne	r3, #:upper16:78704	@ tmp178,
	movteq	r3, #:upper16:78704	@ tmp181,
	streq	r1, [r4, r2]	@ tmp180, <variable>.CodecInfo.StreamIntegrality
	ldr	r2, [r4, r3]	@ prephitmp.2361, <variable>.CodecInfo.MpegFlag
	b	.L615	@
.L645:
	mov	r7, #0	@ tmp289,
	mov	r0, #1	@,
	str	r7, [r4, r3]	@ tmp289, <variable>.CodecInfo.Imgbuf_allocated
	movw	r1, #:lower16:.LC60	@,
	movt	r1, #:upper16:.LC60	@,
	bl	dprint_vfmw	@
	movw	r2, #:lower16:g_event_report	@ tmp291,
	movt	r2, #:upper16:g_event_report	@ tmp291,
	ldr	ip, [r2, #0]	@ g_event_report.469, g_event_report
	cmp	ip, r7	@ g_event_report.469,
	beq	.L629	@,
	movw	r3, #:lower16:113648	@ tmp292,
	movt	r3, #:upper16:113648	@ tmp292,
	mov	r2, r7	@, tmp289
	mov	r1, #120	@,
	ldr	r0, [r4, r3]	@, <variable>.ChanID
	mov	r3, r7	@, tmp2
	blx	ip	@ g_event_report.469
	b	.L629	@
.L642:
	ldr	lr, [r5, #60]	@ <variable>.mb_height, <variable>.mb_height
	ldr	ip, [r9, #60]	@ <variable>.mb_height, <variable>.mb_height
	cmp	lr, ip	@ <variable>.mb_height, <variable>.mb_height
	bne	.L624	@,
	b	.L625	@
.L646:
	ldr	lr, [fp, #-52]	@ ReadNum, ReadNum
	ldr	r1, [fp, #-56]	@ NewNum, NewNum
	add	r0, r1, lr	@ tmp303, NewNum, ReadNum
	cmp	r0, #0	@ tmp303,
	movwgt	r0, #:lower16:113665	@ tmp306,
	movtgt	r0, #:upper16:113665	@ tmp306,
	strgtb	r3, [r4, r0]	@ <variable>.stChanOption.s32ReRangeEn, <variable>.IsWaitToReRange
	bgt	.L634	@,
	b	.L631	@
.L643:
	ldr	r0, [r4, r6]	@, <variable>.ChanID
	bl	FSP_GetNullLogicFs	@
	str	r0, [r4, r8]	@ D.39320, <variable>.CodecInfo.BwdFsID
	ldr	r6, [fp, #-72]	@, %sfp
	str	r0, [r4, r6]	@ D.39320, <variable>.CodecInfo.FwdFsID
	b	.L626	@
.L644:
	movw	r7, #:lower16:78716	@ tmp279,
	movt	r7, #:upper16:78716	@ tmp279,
	ldr	r8, [r4, r7]	@ <variable>.CodecInfo.Imgbuf_allocated, <variable>.CodecInfo.Imgbuf_allocated
	cmp	r8, #0	@ <variable>.CodecInfo.Imgbuf_allocated,
	bne	.L628	@,
	mov	r0, r6	@, D.39321
	bl	ResetVoQueue	@
	mov	r0, r4	@, pCtx
	mov	r1, r8	@, <variable>.CodecInfo.Imgbuf_allocated
	bl	MP2_ArrangeVHBMem	@
	movw	r3, #:lower16:78732	@ tmp282,
	movt	r3, #:upper16:78732	@ tmp282,
	str	r8, [r4, r3]	@ <variable>.CodecInfo.Imgbuf_allocated, <variable>.CodecInfo.QueueImageNum
	str	r0, [r4, r7]	@, <variable>.CodecInfo.Imgbuf_allocated
	b	.L628	@
	.fnend
	.size	MP2_GetSequenceInfo, .-MP2_GetSequenceInfo
	.align	2
	.global	GetSliceHdr
	.type	GetSliceHdr, %function
GetSliceHdr:
	.fnstart
.LFB1531:
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
	add	r6, r0, #78848	@ pBs, pCtx,
	movw	r7, #:lower16:78728	@ tmp159,
	mov	r5, r0	@ pCtx, pCtx
	add	r6, r6, #64	@ pBs, pBs,
	movt	r7, #:upper16:78728	@ tmp159,
	b	.L648	@
.L653:
	bl	BsShow	@
	mov	r4, r0	@ D.38811,
	mov	r0, r6	@, pBs
	bl	BsPos	@
	sub	r4, r4, #256	@ tmp146, D.38811,
	sub	r4, r4, #1	@ tmp146, tmp146,
	mov	r1, #32	@,
	cmp	r4, #174	@ tmp146,
	str	r0, [r5, r7]	@, <variable>.CodecInfo.HDRUsedBits
	mov	r0, r6	@, pBs
	bls	.L658	@,
	bl	BsSkip	@
.L648:
	mov	r0, r5	@, pCtx
	bl	next_start_code	@
	mov	r1, #32	@,
	mov	r4, r0	@ ret.2415,
	cmp	r4, #1	@ ret.2415,
	mov	r0, r6	@, pBs
	beq	.L653	@,
	cmn	r4, #1	@ ret.2415,
	beq	.L654	@,
.L657:
	mov	r0, r4	@ prephitmp.2404, ret.2415
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L654:
	movw	lr, #:lower16:g_event_report	@ tmp154,
	movt	lr, #:upper16:g_event_report	@ tmp154,
	ldr	ip, [lr, #0]	@ g_event_report.447, g_event_report
	cmp	ip, #0	@ g_event_report.447,
	beq	.L657	@,
	movw	r3, #:lower16:113648	@ tmp155,
	movt	r3, #:upper16:113648	@ tmp155,
	mov	r2, #0	@,
	mov	r1, #113	@,
	ldr	r0, [r5, r3]	@, <variable>.ChanID
	mov	r3, r2	@,
	blx	ip	@ g_event_report.447
	mov	r0, r4	@ prephitmp.2404, ret.2415
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L658:
	bl	BsResidBits	@
	cmp	r0, #40	@,
	mvnle	r4, #0	@ ret.2415,
	ble	.L654	@,
	movw	r0, #:lower16:78664	@ tmp150,
	movt	r0, #:upper16:78664	@ tmp150,
	mov	r1, #0	@ tmp149,
	movw	r3, #:lower16:78724	@ tmp148,
	ldr	r2, [r5, r0]	@ <variable>.CodecInfo.NewSeqInited, <variable>.CodecInfo.NewSeqInited
	movt	r3, #:upper16:78724	@ tmp148,
	cmp	r2, r1	@ <variable>.CodecInfo.NewSeqInited,
	str	r1, [r5, r3]	@ tmp149, <variable>.CodecInfo.HDRState
	bne	.L651	@,
	mov	r0, r5	@, pCtx
	bl	MP2_GetSequenceInfo	@
	movw	ip, #:lower16:78716	@ tmp152,
	movt	ip, #:upper16:78716	@ tmp152,
	ldr	r0, [r5, ip]	@ <variable>.CodecInfo.Imgbuf_allocated, <variable>.CodecInfo.Imgbuf_allocated
	cmp	r0, #0	@ <variable>.CodecInfo.Imgbuf_allocated,
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L651:
	mov	r0, r5	@, pCtx
	bl	MP2_ProtocolPPSCheck	@
	mov	r0, #1	@ prephitmp.2404,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	GetSliceHdr, .-GetSliceHdr
	.align	2
	.global	MP2_GetHDR
	.type	MP2_GetHDR, %function
MP2_GetHDR:
	.fnstart
.LFB1530:
	@ args = 0, pretend = 0, frame = 96
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #100
	sub	sp, sp, #100	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	ip, #:lower16:79996	@ tmp172,
	movt	ip, #:upper16:79996	@ tmp172,
	mov	r4, r0	@ pCtx, pCtx
	add	r5, r0, #78848	@ pBs, pCtx,
	movw	lr, #:lower16:79992	@ tmp171,
	ldr	r6, [r4, ip]	@, <variable>.pSyntaxInfOld
	add	r5, r5, #64	@ pBs, pBs,
	movt	lr, #:upper16:79992	@ tmp171,
	mov	sl, #113664	@ tmp173,
	mov	r1, #32	@,
	mov	r8, #0	@ tmp174,
	strb	r8, [r0, sl]	@ tmp174, <variable>.IsWaitToDecFlag
	mov	r0, r5	@, pBs
	ldr	r9, [r4, lr]	@ pSyntaxInfNew, <variable>.pSyntaxInfNew
	movw	r7, #:lower16:78668	@ tmp176,
	str	r6, [fp, #-112]	@, %sfp
	bl	BsShow	@
	movt	r7, #:upper16:78668	@ tmp176,
	ldr	r1, [r4, r7]	@, <variable>.CodecInfo.StreamIntegrality
	str	r1, [fp, #-116]	@, %sfp
	mov	r6, r0	@ code,
	mov	r0, r5	@, pBs
	bl	BsPos	@
	movw	r2, #:lower16:78728	@ tmp177,
	movt	r2, #:upper16:78728	@ tmp177,
	mov	r1, #32	@,
	str	r0, [r4, r2]	@, <variable>.CodecInfo.HDRUsedBits
	mov	r0, r5	@, pBs
	bl	BsSkip	@
	movw	r3, #439	@ tmp178,
	cmp	r6, r3	@ code, tmp178
	beq	.L696	@,
	movw	ip, #435	@ tmp218,
	cmp	r6, ip	@ code, tmp218
	cmpne	r6, #440	@, code,
	bne	.L697	@,
.L661:
	movw	r3, #:lower16:78724	@ tmp231,
	movt	r3, #:upper16:78724	@ tmp231,
	ldr	r7, [r4, r3]	@ <variable>.CodecInfo.HDRState, <variable>.CodecInfo.HDRState
	cmp	r7, #1	@ <variable>.CodecInfo.HDRState,
	beq	.L698	@,
.L664:
	movw	r2, #435	@ tmp245,
	cmp	r6, r2	@ code, tmp245
	beq	.L668	@,
.L701:
	bls	.L699	@,
	movw	r3, #437	@ tmp248,
	cmp	r6, r3	@ code, tmp248
	beq	.L670	@,
	bcs	.L700	@,
.L684:
	mov	r0, #0	@ prephitmp.2434,
.L663:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L697:
	cmp	r6, #256	@ code,
	beq	.L661	@,
	movw	r2, #435	@ tmp245,
	cmp	r6, r2	@ code, tmp245
	bne	.L701	@,
.L668:
	movw	r0, #:lower16:78616	@ tmp251,
	movw	r1, #:lower16:78720	@ tmp252,
	movt	r0, #:upper16:78616	@ tmp251,
	movt	r1, #:upper16:78720	@ tmp252,
	ldr	r6, [r4, r0]	@ <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.BsOffset
	mov	r0, r5	@, pBs
	ldr	lr, [r4, r1]	@ <variable>.CodecInfo.Used_byte, <variable>.CodecInfo.Used_byte
	add	r6, r6, lr	@ D.38705, <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.Used_byte
	bl	BsPos	@
	movw	r1, #:lower16:.LC62	@,
	movt	r1, #:upper16:.LC62	@,
	add	r2, r6, r0, lsr #3	@, tmp257, D.38705,,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, pCtx
	bl	sequence_header	@
	mov	r0, r5	@, pBs
	bl	BsResidBits	@
	cmp	r0, #0	@,
	blt	.L702	@,
	movw	r5, #:lower16:78668	@ tmp267,
	movt	r5, #:upper16:78668	@ tmp267,
	ldr	r6, [r4, r5]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	ands	r6, r6, #7	@ tmp268, <variable>.CodecInfo.StreamIntegrality,
	bne	.L675	@,
	ldr	r0, [fp, #-112]	@, %sfp
	mov	r1, r9	@, pSyntaxInfNew
	mov	lr, #1	@ tmp270,
	mov	r2, #188	@,
	strb	lr, [r9, #0]	@ tmp270, <variable>.valid_flag
	bl	memcpy	@
	movw	r1, #:lower16:78672	@ tmp276,
	movt	r1, #:upper16:78672	@ tmp276,
	mov	r0, r6	@ prephitmp.2434, tmp268
	ldr	r2, [r4, r1]	@ <variable>.CodecInfo.SeqCnt, <variable>.CodecInfo.SeqCnt
	add	ip, r2, #1	@ tmp279, <variable>.CodecInfo.SeqCnt,
	str	ip, [r4, r1]	@ tmp279, <variable>.CodecInfo.SeqCnt
	b	.L663	@
.L699:
	cmp	r6, #256	@ code,
	beq	.L666	@,
	bcc	.L665	@,
	cmp	r6, #432	@ code,
	bls	.L665	@,
	movw	r0, #:lower16:78616	@ tmp327,
	movw	lr, #:lower16:78720	@ tmp328,
	movt	r0, #:upper16:78616	@ tmp327,
	movt	lr, #:upper16:78720	@ tmp328,
	ldr	r6, [r4, r0]	@ <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.BsOffset
	mov	r0, r5	@, pBs
	ldr	r3, [r4, lr]	@ <variable>.CodecInfo.Used_byte, <variable>.CodecInfo.Used_byte
	add	r5, r6, r3	@ temp.2479, <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.Used_byte
	bl	BsPos	@
	movw	r1, #:lower16:.LC68	@,
	movt	r1, #:upper16:.LC68	@,
	add	r2, r5, r0, lsr #3	@, tmp333, temp.2479,,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, pCtx
	bl	MP2_GetUsrData	@
	subs	r6, r0, #0	@ D.38761,
	beq	.L703	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC70	@,
	movt	r1, #:upper16:.LC70	@,
	bl	dprint_vfmw	@
	mov	r0, r6	@ prephitmp.2434, D.38761
	b	.L663	@
.L700:
	movw	ip, #439	@ tmp250,
	cmp	r6, ip	@ code, tmp250
	beq	.L684	@,
	cmp	r6, #440	@ code,
	beq	.L704	@,
.L665:
	sub	r2, r6, #256	@ tmp357, code,
	sub	r0, r2, #1	@ tmp357, tmp357,
	cmp	r0, #174	@ tmp357,
	bhi	.L682	@,
	movw	r3, #:lower16:78664	@ tmp359,
	movt	r3, #:upper16:78664	@ tmp359,
	ldr	r1, [r4, r3]	@ <variable>.CodecInfo.NewSeqInited, <variable>.CodecInfo.NewSeqInited
	cmp	r1, #0	@ <variable>.CodecInfo.NewSeqInited,
	beq	.L705	@,
.L683:
	movw	r3, #:lower16:78668	@ tmp365,
	movt	r3, #:upper16:78668	@ tmp365,
	ldr	r2, [r4, r3]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	tst	r2, #589824	@ <variable>.CodecInfo.StreamIntegrality,
	beq	.L684	@,
	movw	r1, #:lower16:78724	@ tmp368,
	movt	r1, #:upper16:78724	@ tmp368,
	orr	r5, r2, #4194304	@ tmp373, <variable>.CodecInfo.StreamIntegrality,
	mov	r0, r4	@, pCtx
	str	r5, [r4, r3]	@ tmp373, <variable>.CodecInfo.StreamIntegrality
	mov	r5, #1	@ tmp369,
	str	r5, [r4, r1]	@ tmp369, <variable>.CodecInfo.HDRState
	mov	r1, r6	@, code
	bl	MP2_DecSlice	@
	cmp	r0, r5	@ D.38793,
	beq	.L663	@,
	mov	r0, r5	@, tmp369
	mov	r2, r6	@, code
	movw	r1, #:lower16:.LC72	@,
	movt	r1, #:upper16:.LC72	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ prephitmp.2434,
	b	.L663	@
.L704:
	movw	r0, #:lower16:78616	@ tmp295,
	movw	lr, #:lower16:78720	@ tmp296,
	movt	r0, #:upper16:78616	@ tmp295,
	movt	lr, #:upper16:78720	@ tmp296,
	ldr	r6, [r4, r0]	@ <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.BsOffset
	mov	r0, r5	@, pBs
	ldr	r2, [r4, lr]	@ <variable>.CodecInfo.Used_byte, <variable>.CodecInfo.Used_byte
	add	r6, r6, r2	@ temp.2463, <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.Used_byte
	bl	BsPos	@
	movw	r1, #:lower16:.LC64	@,
	movt	r1, #:upper16:.LC64	@,
	add	r2, r6, r0, lsr #3	@, tmp301, temp.2463,,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, pCtx
	bl	group_of_pictures_header	@
	mov	r0, r5	@, pBs
	bl	BsResidBits	@
	cmp	r0, #0	@,
	bge	.L684	@,
	ldr	ip, [fp, #-116]	@, %sfp
	movw	r1, #:lower16:78668	@ tmp302,
	movw	r3, #:lower16:g_event_report	@ tmp303,
	movt	r1, #:upper16:78668	@ tmp302,
	movt	r3, #:upper16:g_event_report	@ tmp303,
	str	ip, [r4, r1]	@, <variable>.CodecInfo.StreamIntegrality
	ldr	ip, [r3, #0]	@ g_event_report.2464, g_event_report
	cmp	ip, #0	@ g_event_report.2464,
	beq	.L677	@,
	movw	lr, #:lower16:113648	@ tmp304,
	movt	lr, #:upper16:113648	@ tmp304,
	mov	r2, #0	@,
	mov	r1, #113	@,
	ldr	r0, [r4, lr]	@, <variable>.ChanID
	mov	r3, r2	@,
	blx	ip	@ g_event_report.2464
.L677:
	movw	r3, #:lower16:113648	@ tmp306,
	movt	r3, #:upper16:113648	@ tmp306,
	add	r2, r4, #77824	@, pCtx,
	ldr	r0, [r4, r3]	@, <variable>.ChanID
	add	r1, r2, #796	@,,
	bl	MP2_ClearCurPacket	@
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC65	@,
	mov	r2, #440	@,
	movt	r1, #:upper16:.LC65	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ prephitmp.2434,
	b	.L663	@
.L698:
	movw	r2, #:lower16:78668	@ tmp233,
	movt	r2, #:upper16:78668	@ tmp233,
	ldr	r1, [r4, r2]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	tst	r1, #4194304	@ <variable>.CodecInfo.StreamIntegrality,
	beq	.L664	@,
	orr	r0, r1, #8388608	@ tmp242, <variable>.CodecInfo.StreamIntegrality,
	mov	r1, #113664	@ tmp236,
	str	r0, [r4, r2]	@ tmp242, <variable>.CodecInfo.StreamIntegrality
	mov	lr, #0	@ tmp244,
	mov	r0, r4	@, pCtx
	strb	r7, [r4, r1]	@ <variable>.CodecInfo.HDRState, <variable>.IsWaitToDecFlag
	str	lr, [r4, r3]	@ tmp244, <variable>.CodecInfo.HDRState
	bl	MP2_ProtocolPPSCheck	@
	mov	r0, r7	@ prephitmp.2434, <variable>.CodecInfo.HDRState
	b	.L663	@
.L696:
	mov	lr, r5	@, pBs
	sub	ip, fp, #108	@,,
	ldmia	lr!, {r0, r1, r2, r3}	@,,,,
	str	ip, [fp, #-136]	@, %sfp
	str	lr, [fp, #-120]	@, %sfp
	sub	lr, fp, #76	@,,
	str	lr, [fp, #-128]	@, %sfp
	ldr	lr, [fp, #-136]	@ tmp381, %sfp
	stmia	lr!, {r0, r1, r2, r3}	@ tmp381,,,,
	ldr	ip, [fp, #-120]	@, %sfp
	ldmia	ip, {r0, r1, r2, r3}	@,,,,
	stmia	lr, {r0, r1, r2, r3}	@ tmp381,,,,
	ldr	ip, [fp, #-136]	@ tmp382, %sfp
	ldmia	ip!, {r0, r1, r2, r3}	@ tmp382,,,,
	ldr	ip, [fp, #-128]	@ tmp383, %sfp
	stmia	ip!, {r0, r1, r2, r3}	@ tmp383,,,,
	ldmia	lr, {r0, r1, r2, r3}	@ tmp381,,,,
	stmia	ip, {r0, r1, r2, r3}	@ tmp383,,,,
	mov	r1, #32	@,
	sub	r0, fp, #76	@,,
	bl	BsGet	@
	mov	r1, #32	@,
	mov	ip, r0	@ D.38675,
	sub	r0, fp, #76	@,,
	str	ip, [fp, #-124]	@,
	bl	BsGet	@
	ldr	r1, [fp, #-124]	@,
	movw	r2, #:lower16:1128615492	@ tmp187,
	movw	r3, #:lower16:1213419593	@ tmp190,
	movt	r2, #:upper16:1128615492	@ tmp187,
	movt	r3, #:upper16:1213419593	@ tmp190,
	cmp	r0, r2	@, tmp187
	cmpeq	r1, r3	@, D.38675, tmp190
	bne	.L661	@,
	movw	r3, #:lower16:78724	@ tmp195,
	movt	r3, #:upper16:78724	@ tmp195,
	ldr	r6, [r4, r3]	@ <variable>.CodecInfo.HDRState, <variable>.CodecInfo.HDRState
	cmp	r6, #1	@ <variable>.CodecInfo.HDRState,
	beq	.L706	@,
.L662:
	movw	r3, #:lower16:113666	@ tmp212,
	movt	r3, #:upper16:113666	@ tmp212,
	mov	r2, #1	@ tmp213,
	mov	r0, #0	@ prephitmp.2434,
	strb	r2, [r4, r3]	@ tmp213, <variable>.IsStreamEndFlag
	b	.L663	@
.L666:
	movw	r0, #:lower16:78616	@ tmp311,
	movw	ip, #:lower16:78720	@ tmp312,
	movt	r0, #:upper16:78616	@ tmp311,
	movt	ip, #:upper16:78720	@ tmp312,
	ldr	r6, [r4, r0]	@ <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.BsOffset
	mov	r0, r5	@, pBs
	ldr	r1, [r4, ip]	@ <variable>.CodecInfo.Used_byte, <variable>.CodecInfo.Used_byte
	add	r6, r6, r1	@ temp.2471, <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.Used_byte
	bl	BsPos	@
	movw	r1, #:lower16:.LC66	@,
	movt	r1, #:upper16:.LC66	@,
	add	r2, r6, r0, lsr #3	@, tmp317, temp.2471,,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, pCtx
	bl	picture_header	@
	mov	r0, r5	@, pBs
	bl	BsResidBits	@
	cmp	r0, #0	@,
	bge	.L684	@,
	ldr	r3, [fp, #-116]	@, %sfp
	movw	r2, #:lower16:78668	@ tmp318,
	movw	lr, #:lower16:g_event_report	@ tmp319,
	movt	r2, #:upper16:78668	@ tmp318,
	movt	lr, #:upper16:g_event_report	@ tmp319,
	str	r3, [r4, r2]	@, <variable>.CodecInfo.StreamIntegrality
	ldr	ip, [lr, #0]	@ g_event_report.2472, g_event_report
	cmp	ip, #0	@ g_event_report.2472,
	beq	.L678	@,
	movw	lr, #:lower16:113648	@ tmp320,
	movt	lr, #:upper16:113648	@ tmp320,
	mov	r2, #0	@,
	mov	r1, #113	@,
	ldr	r0, [r4, lr]	@, <variable>.ChanID
	mov	r3, r2	@,
	blx	ip	@ g_event_report.2472
.L678:
	movw	ip, #:lower16:113648	@ tmp322,
	movt	ip, #:upper16:113648	@ tmp322,
	add	r1, r4, #77824	@, pCtx,
	ldr	r0, [r4, ip]	@, <variable>.ChanID
	add	r1, r1, #796	@,,
	bl	MP2_ClearCurPacket	@
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC67	@,
	mov	r2, #256	@,
	movt	r1, #:upper16:.LC67	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ prephitmp.2434,
	b	.L663	@
.L670:
	movw	lr, #:lower16:78616	@ tmp342,
	movw	r6, #:lower16:78720	@ tmp343,
	movt	lr, #:upper16:78616	@ tmp342,
	movt	r6, #:upper16:78720	@ tmp343,
	mov	r0, r5	@, pBs
	ldr	ip, [r4, lr]	@ <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.BsOffset
	ldr	r3, [r4, r6]	@ <variable>.CodecInfo.Used_byte, <variable>.CodecInfo.Used_byte
	add	r6, ip, r3	@ temp.2487, <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.Used_byte
	bl	BsPos	@
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	add	r2, r6, r0, lsr #3	@, tmp348, temp.2487,,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, pCtx
	bl	extension	@
	mov	r0, r5	@, pBs
	bl	BsResidBits	@
	cmp	r0, #0	@,
	bge	.L684	@,
	ldr	r1, [fp, #-116]	@, %sfp
	movw	r2, #:lower16:78668	@ tmp349,
	movw	r0, #:lower16:g_event_report	@ tmp350,
	movt	r2, #:upper16:78668	@ tmp349,
	movt	r0, #:upper16:g_event_report	@ tmp350,
	str	r1, [r4, r2]	@, <variable>.CodecInfo.StreamIntegrality
	ldr	ip, [r0, #0]	@ g_event_report.2488, g_event_report
	cmp	ip, #0	@ g_event_report.2488,
	beq	.L681	@,
	movw	r3, #:lower16:113648	@ tmp351,
	movt	r3, #:upper16:113648	@ tmp351,
	mov	r2, #0	@,
	mov	r1, #113	@,
	ldr	r0, [r4, r3]	@, <variable>.ChanID
	mov	r3, r2	@,
	blx	ip	@ g_event_report.2488
.L681:
	movw	lr, #:lower16:113648	@ tmp353,
	movt	lr, #:upper16:113648	@ tmp353,
	add	ip, r4, #77824	@, pCtx,
	ldr	r0, [r4, lr]	@, <variable>.ChanID
	add	r1, ip, #796	@,,
	bl	MP2_ClearCurPacket	@
.L692:
	mvn	r0, #0	@ prephitmp.2434,
	b	.L663	@
.L675:
	ldr	r2, [fp, #-112]	@, %sfp
	ldrb	r0, [r2, #0]	@ zero_extendqisi2	@ <variable>.valid_flag, <variable>.valid_flag
	cmp	r0, #1	@ <variable>.valid_flag,
	beq	.L707	@,
.L682:
	movw	r3, #:lower16:g_event_report	@ tmp375,
	movt	r3, #:upper16:g_event_report	@ tmp375,
	ldr	ip, [r3, #0]	@ g_event_report.2494, g_event_report
	cmp	ip, #0	@ g_event_report.2494,
	beq	.L684	@,
.L693:
	movw	lr, #:lower16:113648	@ tmp376,
	movt	lr, #:upper16:113648	@ tmp376,
	mov	r2, #0	@,
	mov	r1, #113	@,
	ldr	r0, [r4, lr]	@, <variable>.ChanID
	mov	r3, r2	@,
	blx	ip	@ g_event_report.2494
	mov	r0, #0	@ prephitmp.2434,
	b	.L663	@
.L706:
	ldr	r2, [r4, r7]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	tst	r2, #4194304	@ <variable>.CodecInfo.StreamIntegrality,
	beq	.L662	@,
	movw	r1, #:lower16:113666	@ tmp200,
	movt	r1, #:upper16:113666	@ tmp200,
	orr	r0, r2, #8388608	@ tmp209, <variable>.CodecInfo.StreamIntegrality,
	str	r8, [r4, r3]	@ tmp174, <variable>.CodecInfo.HDRState
	str	r0, [r4, r7]	@ tmp209, <variable>.CodecInfo.StreamIntegrality
	mov	r0, r4	@, pCtx
	strb	r6, [r4, r1]	@ <variable>.CodecInfo.HDRState, <variable>.IsStreamEndFlag
	strb	r6, [r4, sl]	@ <variable>.CodecInfo.HDRState, <variable>.IsWaitToDecFlag
	bl	MP2_ProtocolPPSCheck	@
	mov	r0, r6	@ prephitmp.2434, <variable>.CodecInfo.HDRState
	b	.L663	@
.L705:
	mov	r0, r4	@, pCtx
	bl	MP2_GetSequenceInfo	@
	movw	r0, #:lower16:78716	@ tmp361,
	movt	r0, #:upper16:78716	@ tmp361,
	ldr	ip, [r4, r0]	@ <variable>.CodecInfo.Imgbuf_allocated, <variable>.CodecInfo.Imgbuf_allocated
	cmp	ip, #0	@ <variable>.CodecInfo.Imgbuf_allocated,
	beq	.L684	@,
	movw	r2, #:lower16:113665	@ tmp363,
	movt	r2, #:upper16:113665	@ tmp363,
	ldrb	lr, [r4, r2]	@ zero_extendqisi2	@ <variable>.IsWaitToReRange, <variable>.IsWaitToReRange
	cmp	lr, #1	@ <variable>.IsWaitToReRange,
	bne	.L683	@,
	b	.L684	@
.L707:
	mov	r1, r2	@,
	mov	r0, r9	@, pSyntaxInfNew
	mov	r2, #188	@,
	bl	memcpy	@
	ldr	r1, [r4, r5]	@ <variable>.CodecInfo.StreamIntegrality, <variable>.CodecInfo.StreamIntegrality
	movw	r3, #:lower16:g_event_report	@ tmp289,
	movt	r3, #:upper16:g_event_report	@ tmp289,
	bic	ip, r1, #7	@ tmp288, <variable>.CodecInfo.StreamIntegrality,
	str	ip, [r4, r5]	@ tmp288, <variable>.CodecInfo.StreamIntegrality
	ldr	ip, [r3, #0]	@ g_event_report.2456, g_event_report
	cmp	ip, #0	@ g_event_report.2456,
	bne	.L693	@,
	b	.L684	@
.L703:
	movw	r5, #:lower16:113648	@ tmp334,
	movt	r5, #:upper16:113648	@ tmp334,
	add	r1, r4, #77824	@, pCtx,
	add	r1, r1, #796	@,,
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	bl	MP2_ClearCurPacket	@
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC69	@,
	movt	r1, #:upper16:.LC69	@,
	bl	dprint_vfmw	@
	movw	r2, #:lower16:g_event_report	@ tmp339,
	movt	r2, #:upper16:g_event_report	@ tmp339,
	ldr	ip, [r2, #0]	@ g_event_report.2482, g_event_report
	cmp	ip, #0	@ g_event_report.2482,
	beq	.L692	@,
	mov	r2, r6	@, D.38761
	ldr	r0, [r4, r5]	@, <variable>.ChanID
	mov	r1, #113	@,
	mov	r3, r6	@, tmp2
	blx	ip	@ g_event_report.2482
	mvn	r0, #0	@ prephitmp.2434,
	b	.L663	@
.L702:
	ldr	ip, [fp, #-116]	@, %sfp
	movw	r2, #:lower16:78668	@ tmp258,
	movw	r3, #:lower16:g_event_report	@ tmp259,
	movt	r2, #:upper16:78668	@ tmp258,
	movt	r3, #:upper16:g_event_report	@ tmp259,
	str	ip, [r4, r2]	@, <variable>.CodecInfo.StreamIntegrality
	ldr	ip, [r3, #0]	@ g_event_report.445, g_event_report
	cmp	ip, #0	@ g_event_report.445,
	beq	.L674	@,
	movw	lr, #:lower16:113648	@ tmp260,
	movt	lr, #:upper16:113648	@ tmp260,
	mov	r2, #0	@,
	mov	r1, #113	@,
	ldr	r0, [r4, lr]	@, <variable>.ChanID
	mov	r3, r2	@,
	blx	ip	@ g_event_report.445
.L674:
	movw	r3, #:lower16:113648	@ tmp262,
	movt	r3, #:upper16:113648	@ tmp262,
	add	r1, r4, #77824	@, pCtx,
	ldr	r0, [r4, r3]	@, <variable>.ChanID
	add	r1, r1, #796	@,,
	bl	MP2_ClearCurPacket	@
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC63	@,
	movw	r2, #435	@,
	movt	r1, #:upper16:.LC63	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ prephitmp.2434,
	b	.L663	@
	.fnend
	.size	MP2_GetHDR, .-MP2_GetHDR
	.align	2
	.global	MPEG2DEC_Decode
	.type	MPEG2DEC_Decode, %function
MPEG2DEC_Decode:
	.fnstart
.LFB1563:
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
	add	r2, r0, #78848	@ D.40426, pCtx,
	add	r4, r2, #608	@ D.40426, D.40426,
	mov	r5, r0	@ pCtx, pCtx
	mov	r2, #160	@,
	mov	r0, r4	@, D.40426
	bl	memcpy	@
	movw	r3, #:lower16:113648	@ tmp155,
	movt	r3, #:upper16:113648	@ tmp155,
	add	r0, r5, #45312	@, pCtx,
	add	r0, r0, #16	@,,
	mov	r1, r4	@, D.40426
	ldr	r2, [r5, r3]	@, <variable>.ChanID
	bl	MP2_ReceivePacket	@
	cmp	r0, #1	@,
	beq	.L709	@,
	movw	r1, #:lower16:.LC73	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC73	@,
	mov	r4, #0	@ ret,
	bl	dprint_vfmw	@
.L710:
	mov	r0, r4	@, ret
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L709:
	movw	r3, #:lower16:78624	@ tmp160,
	movw	ip, #:lower16:78640	@ tmp162,
	movt	r3, #:upper16:78624	@ tmp160,
	movt	ip, #:upper16:78640	@ tmp162,
	add	lr, r5, #78848	@, pCtx,
	ldr	r1, [r5, r3]	@, <variable>.CodecInfo.stMp2Packet.BsVirAddr
	add	r0, lr, #64	@,,
	ldr	r2, [r5, ip]	@, <variable>.CodecInfo.stMp2Packet.BsLength
	bl	BsInit	@
	ldr	r3, [r5, #0]	@ D.40438, <variable>.pstExtraData
	ldr	r1, [r3, #848]	@ <variable>.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r1, #1	@ <variable>.stChanOption.u32DynamicFrameStoreAllocEn,
	beq	.L724	@,
.L711:
	movw	r3, #:lower16:78668	@ tmp170,
	movt	r3, #:upper16:78668	@ tmp170,
	movw	lr, #:lower16:78852	@ tmp169,
	movt	lr, #:upper16:78852	@ tmp169,
	ldr	ip, [r5, r3]	@ <variable>.CodecInfo.StreamIntegrality,
	str	ip, [r5, lr]	@ <variable>.CodecInfo.StreamIntegrality,
.L712:
	mov	r0, r5	@, pCtx
	bl	MP2_GetHDR	@
	add	r4, r0, #1	@ tmp172,,
	cmp	r4, #1	@ tmp172,
	bls	.L725	@,
	mov	r0, r5	@, pCtx
	bl	MP2_DecodingDecide	@
	subs	r4, r0, #0	@ ret,
	beq	.L726	@,
	cmn	r4, #1	@ ret,
	beq	.L715	@,
	mov	r0, r5	@, pCtx
	bl	MP2_GetPictureInfo	@
	subs	r6, r0, #0	@ D.40467,
	bne	.L719	@,
	movw	r4, #:lower16:113648	@ tmp189,
	movt	r4, #:upper16:113648	@ tmp189,
	add	ip, r5, #77824	@, pCtx,
	add	r1, ip, #796	@,,
	ldr	r0, [r5, r4]	@, <variable>.ChanID
	bl	MP2_ClearCurPacket	@
	mov	r0, r5	@, pCtx
	bl	MP2_ClearCurPic	@
	movw	r2, #:lower16:g_event_report	@ tmp193,
	movt	r2, #:upper16:g_event_report	@ tmp193,
	ldr	ip, [r2, #0]	@ g_event_report.2529, g_event_report
	cmp	ip, #0	@ g_event_report.2529,
	beq	.L720	@,
	mov	r2, r6	@, D.40467
	ldr	r0, [r5, r4]	@, <variable>.ChanID
	mov	r1, #113	@,
	mov	r3, r6	@, tmp2
	blx	ip	@ g_event_report.2529
.L720:
	movw	r1, #:lower16:.LC75	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC75	@,
	mov	r4, #0	@ ret,
	bl	dprint_vfmw	@
	b	.L710	@
.L725:
	ldr	r3, [r5, #0]	@ temp.2520, <variable>.pstExtraData
	ldr	r0, [r3, #848]	@ <variable>.stChanOption.u32DynamicFrameStoreAllocEn, <variable>.stChanOption.u32DynamicFrameStoreAllocEn
	cmp	r0, #1	@ <variable>.stChanOption.u32DynamicFrameStoreAllocEn,
	beq	.L727	@,
.L714:
	movw	ip, #:lower16:113665	@ tmp175,
	movt	ip, #:upper16:113665	@ tmp175,
	ldrb	r2, [r5, ip]	@ zero_extendqisi2	@ <variable>.IsWaitToReRange, <variable>.IsWaitToReRange
	cmp	r2, #1	@ <variable>.IsWaitToReRange,
	beq	.L715	@,
	movw	r3, #:lower16:113648	@ tmp177,
	movt	r3, #:upper16:113648	@ tmp177,
	add	lr, r5, #77824	@, pCtx,
	mov	r4, #0	@ ret,
	ldr	r0, [r5, r3]	@, <variable>.ChanID
	add	r1, lr, #796	@,,
	bl	MP2_ClearCurPacket	@
	b	.L710	@
.L727:
	ldr	r1, [r3, #884]	@ <variable>.s32WaitFsFlag, <variable>.s32WaitFsFlag
	cmp	r1, #0	@ <variable>.s32WaitFsFlag,
	beq	.L714	@,
.L715:
	mov	r4, #0	@ ret,
	mov	r0, r4	@, ret
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L724:
	ldr	r4, [r3, #884]	@ <variable>.s32WaitFsFlag, <variable>.s32WaitFsFlag
	cmp	r4, #1	@ <variable>.s32WaitFsFlag,
	bne	.L711	@,
	movw	r2, #:lower16:78852	@ tmp167,
	movt	r2, #:upper16:78852	@ tmp167,
	movw	r1, #:lower16:78668	@ tmp166,
	movt	r1, #:upper16:78668	@ tmp166,
	ldr	r0, [r5, r2]	@ <variable>.CodecInfo.LastStreamIntegrality,
	str	r0, [r5, r1]	@ <variable>.CodecInfo.LastStreamIntegrality,
	b	.L712	@
.L726:
	movw	r6, #:lower16:113648	@ tmp181,
	movt	r6, #:upper16:113648	@ tmp181,
	add	r1, r5, #77824	@, pCtx,
	add	r1, r1, #796	@,,
	ldr	r0, [r5, r6]	@, <variable>.ChanID
	bl	MP2_ClearCurPacket	@
	mov	r0, r5	@, pCtx
	bl	MP2_ClearCurPic	@
	movw	r0, #:lower16:g_event_report	@ tmp185,
	movt	r0, #:upper16:g_event_report	@ tmp185,
	ldr	ip, [r0, #0]	@ g_event_report.502, g_event_report
	cmp	ip, #0	@ g_event_report.502,
	beq	.L717	@,
	ldr	r0, [r5, r6]	@, <variable>.ChanID
	mov	r1, #113	@,
	mov	r2, r4	@, ret
	mov	r3, r4	@, ret
	blx	ip	@ g_event_report.502
.L717:
	movw	r1, #:lower16:.LC74	@,
	mov	r0, #22	@,
	movt	r1, #:upper16:.LC74	@,
	bl	dprint_vfmw	@
	b	.L710	@
.L719:
	mov	r0, r5	@, pCtx
	bl	MP2_DecNewPic	@
	subs	r6, r0, #0	@ D.40473,
	beq	.L728	@,
	movw	lr, #:lower16:78616	@ tmp215,
	movt	lr, #:upper16:78616	@ tmp215,
	movw	ip, #:lower16:78720	@ tmp209,
	movw	r0, #:lower16:78640	@ tmp210,
	movt	ip, #:upper16:78720	@ tmp209,
	movt	r0, #:upper16:78640	@ tmp210,
	ldr	r4, [r5, lr]	@ <variable>.CodecInfo.BsOffset, <variable>.CodecInfo.BsOffset
	ldr	r3, [r5, ip]	@ <variable>.CodecInfo.Used_byte, <variable>.CodecInfo.Used_byte
	ldr	r1, [r5, r0]	@ <variable>.CodecInfo.stMp2Packet.BsLength, <variable>.CodecInfo.stMp2Packet.BsLength
	mov	r4, r4, asl #3	@ ret, <variable>.CodecInfo.BsOffset,
	add	r2, r1, r3	@ tmp214, <variable>.CodecInfo.stMp2Packet.BsLength, <variable>.CodecInfo.Used_byte
	str	r2, [r5, ip]	@ tmp214, <variable>.CodecInfo.Used_byte
	b	.L710	@
.L728:
	movw	r4, #:lower16:113648	@ tmp197,
	movw	lr, #:lower16:78752	@ tmp199,
	movt	r4, #:upper16:113648	@ tmp197,
	movt	lr, #:upper16:78752	@ tmp199,
	mov	r2, #1	@,
	ldr	r1, [r5, lr]	@, <variable>.CodecInfo.CurFsID
	ldr	r0, [r5, r4]	@, <variable>.ChanID
	bl	FSP_ClearLogicFs	@
	add	r0, r5, #77824	@, pCtx,
	add	r1, r0, #796	@,,
	ldr	r0, [r5, r4]	@, <variable>.ChanID
	bl	MP2_ClearCurPacket	@
	mov	r0, r5	@, pCtx
	bl	MP2_ClearCurPic	@
	movw	r3, #:lower16:g_event_report	@ tmp205,
	movt	r3, #:upper16:g_event_report	@ tmp205,
	ldr	ip, [r3, #0]	@ g_event_report.2534, g_event_report
	cmp	ip, #0	@ g_event_report.2534,
	beq	.L722	@,
	mov	r2, r6	@, D.40473
	ldr	r0, [r5, r4]	@, <variable>.ChanID
	mov	r1, #113	@,
	mov	r3, r6	@, tmp2
	blx	ip	@ g_event_report.2534
.L722:
	movw	r1, #:lower16:.LC76	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC76	@,
	mov	r4, #0	@ ret,
	bl	dprint_vfmw	@
	b	.L710	@
	.fnend
	.size	MPEG2DEC_Decode, .-MPEG2DEC_Decode
	.global	default_intra_quantizer_matrix
	.global	zigzag
	.global	g_tmpusd
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	C.452.39038, %object
	.size	C.452.39038, 128
C.452.39038:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	10
	.word	12
	.word	14
	.word	16
	.word	18
	.word	20
	.word	22
	.word	24
	.word	28
	.word	32
	.word	36
	.word	40
	.word	44
	.word	48
	.word	52
	.word	56
	.word	64
	.word	72
	.word	80
	.word	88
	.word	96
	.word	104
	.word	112
	.type	CSWTCH.528, %object
	.size	CSWTCH.528, 12
CSWTCH.528:
	.word	5
	.word	1
	.word	2
	.type	tab_for_first_4bit, %object
	.size	tab_for_first_4bit, 128
tab_for_first_4bit:
	.word	8
	.word	4
	.word	9
	.word	5
	.word	5
	.word	4
	.word	4
	.word	4
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	3
	.word	2
	.word	3
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.type	tab_for_last_7bit, %object
	.size	tab_for_last_7bit, 832
tab_for_last_7bit:
	.word	33
	.word	11
	.word	32
	.word	11
	.word	31
	.word	11
	.word	30
	.word	11
	.word	29
	.word	11
	.word	28
	.word	11
	.word	27
	.word	11
	.word	26
	.word	11
	.word	25
	.word	11
	.word	24
	.word	11
	.word	23
	.word	11
	.word	22
	.word	11
	.word	21
	.word	10
	.word	21
	.word	10
	.word	20
	.word	10
	.word	20
	.word	10
	.word	19
	.word	10
	.word	19
	.word	10
	.word	18
	.word	10
	.word	18
	.word	10
	.word	17
	.word	10
	.word	17
	.word	10
	.word	16
	.word	10
	.word	16
	.word	10
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.type	frame_rate_Table, %object
	.size	frame_rate_Table, 64
frame_rate_Table:
	.word	0
	.word	24551
	.word	24576
	.word	25600
	.word	30689
	.word	30720
	.word	51200
	.word	61378
	.word	61440
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.type	__func__.38849, %object
	.size	__func__.38849, 19
__func__.38849:
	.ascii	"MP2_DecodingDecide\000"
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	zigzag, %object
	.size	zigzag, 64
zigzag:
	.byte	0
	.byte	1
	.byte	8
	.byte	16
	.byte	9
	.byte	2
	.byte	3
	.byte	10
	.byte	17
	.byte	24
	.byte	32
	.byte	25
	.byte	18
	.byte	11
	.byte	4
	.byte	5
	.byte	12
	.byte	19
	.byte	26
	.byte	33
	.byte	40
	.byte	48
	.byte	41
	.byte	34
	.byte	27
	.byte	20
	.byte	13
	.byte	6
	.byte	7
	.byte	14
	.byte	21
	.byte	28
	.byte	35
	.byte	42
	.byte	49
	.byte	56
	.byte	57
	.byte	50
	.byte	43
	.byte	36
	.byte	29
	.byte	22
	.byte	15
	.byte	23
	.byte	30
	.byte	37
	.byte	44
	.byte	51
	.byte	58
	.byte	59
	.byte	52
	.byte	45
	.byte	38
	.byte	31
	.byte	39
	.byte	46
	.byte	53
	.byte	60
	.byte	61
	.byte	54
	.byte	47
	.byte	55
	.byte	62
	.byte	63
	.type	default_intra_quantizer_matrix, %object
	.size	default_intra_quantizer_matrix, 64
default_intra_quantizer_matrix:
	.byte	8
	.byte	16
	.byte	19
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	16
	.byte	16
	.byte	22
	.byte	24
	.byte	27
	.byte	29
	.byte	34
	.byte	37
	.byte	19
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	34
	.byte	38
	.byte	22
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	37
	.byte	40
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	32
	.byte	35
	.byte	40
	.byte	48
	.byte	26
	.byte	27
	.byte	29
	.byte	32
	.byte	35
	.byte	40
	.byte	48
	.byte	58
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	38
	.byte	46
	.byte	56
	.byte	69
	.byte	27
	.byte	29
	.byte	35
	.byte	38
	.byte	46
	.byte	56
	.byte	69
	.byte	83
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"Decoding quits at frm %d\012\000"
	.space	2
.LC1:
	.ascii	"%-40s%20d\012\000"
	.space	1
.LC2:
	.ascii	"macroblock_address_increment\000"
	.space	3
.LC3:
	.ascii	"macroblock_escape ERROR\012\000"
	.space	3
.LC4:
	.ascii	"macroblock_escape\000"
	.space	2
.LC5:
	.ascii	"SlcStartMbNum = %d > PicEndMum = %d\012\000"
	.space	3
.LC6:
	.ascii	"FirstMbInSliceFlag = %d\012\000"
	.space	3
.LC7:
	.ascii	"slice_vertical_position\000"
.LC8:
	.ascii	"quantiser_scale_code\000"
	.space	3
.LC9:
	.ascii	"intra_slice_flag\000"
	.space	3
.LC10:
	.ascii	"intra_slice\000"
.LC11:
	.ascii	"reserved_bits\000"
	.space	2
.LC12:
	.ascii	"extra_bit_slice\000"
.LC13:
	.ascii	"extra_infrmation_slice\000"
	.space	1
.LC14:
	.ascii	"Slice num = %d >= %d\012\000"
	.space	2
.LC15:
	.ascii	"seg info is wrong! IsLastSeg[0] = %d, IsLastSeg[1] "
	.ascii	"= %d\012\000"
	.space	3
.LC16:
	.ascii	"MP2_GetFirstMbInSlice Failed!\012\000"
	.space	1
.LC17:
	.ascii	"MP2_WriteSliceInfo Failed!\012\000"
.LC18:
	.ascii	"ERROR: frm %d, Invalid packet pointer!\012\000"
.LC19:
	.ascii	"line %d, pPacket->StreamPack[1].IsLastSeg = %d\012\000"
.LC20:
	.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000"
.LC21:
	.ascii	"ERROR: unsupported profile %d\012\000"
	.space	1
.LC22:
	.ascii	"ERROR: unsupported level %d\012\000"
	.space	3
.LC23:
	.ascii	"\012mpeg2 copy last 3 bytes of the first packet!\012"
	.ascii	"\012\000"
.LC24:
	.ascii	"pMp2CodecInfo->pUsrDatArray[%d] is null\012\000"
	.space	3
.LC25:
	.ascii	"get frame store fail!\012\000"
	.space	1
.LC26:
	.ascii	"line: %d, pImage is NULL!\012\000"
	.space	1
.LC27:
	.ascii	"get image buffer ok: LogicFsID = %d\012\000"
	.space	3
.LC28:
	.ascii	"decode %p, disp %p, tf %p\012\000"
	.space	1
.LC29:
	.ascii	"ErrRatio = %d\012\000"
	.space	1
.LC30:
	.ascii	"pImg is null, pCurImg %#x pBwdImg %#x pFwdImg %#x\012"
	.ascii	"\000"
	.space	1
.LC31:
	.ascii	"DEBUG: DEC over\012\000"
	.space	3
.LC32:
	.ascii	"insert buf %d ref %d\012\000"
	.space	2
.LC33:
	.ascii	"err(%d) > out_thr(%d)\012\000"
	.space	1
.LC34:
	.ascii	"ERROR: frm %d, lost one field\012\000"
	.space	1
.LC35:
	.ascii	"ERROR: frm %d, lost one field flg = %d, last_struct"
	.ascii	" = %d\012\000"
	.space	2
.LC36:
	.ascii	"Fatal Error: frm%d, get image buffer failed\012\000"
	.space	3
.LC37:
	.ascii	"dec_pts: %lld Usertag: %lld\012\000"
	.space	3
.LC38:
	.ascii	"---------- unref %d\012\000"
	.space	3
.LC39:
	.ascii	"++++++++++ ref %d\012\000"
	.space	1
.LC40:
	.ascii	"line: %d(pCur, pFwd, pBwd)(%p, %p, %p)\012\000"
.LC41:
	.ascii	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\012\000"
	.space	3
.LC42:
	.ascii	"dec addr: cur,cur2d,fwd,bwd,pmv = %p,%p,%p,%p,%p\012"
	.ascii	"\000"
	.space	2
.LC43:
	.ascii	"ERROR: frm %d, integrality: %#x\012\000"
	.space	3
.LC44:
	.ascii	"ERROR: frm %d, No Img buffer is allocated\012\000"
	.space	1
.LC45:
	.ascii	"----------------- mp2 Imode -> %d -----------------"
	.ascii	"-\012\000"
	.space	2
.LC46:
	.ascii	"frm %d pic type %d struct is %d total pos %#x\012\000"
	.space	1
.LC47:
	.ascii	"NOTE: Drop non-I, cur is B\012\000"
.LC48:
	.ascii	"NOTE: Drop non-I, cur is P\012\000"
.LC49:
	.ascii	"NOTE: Drop non-I\012\000"
	.space	2
.LC50:
	.ascii	"NOTE: Drop B\012\000"
	.space	2
.LC51:
	.ascii	"%s %d pFwdImg = NULL,  pBwdImg = NULL!!\012\000"
	.space	3
.LC52:
	.ascii	"dec P frame, fwd ref err(%d) > ref_thr(%d)\012\000"
.LC53:
	.ascii	"dec B frame, bwd ref err(%d) > ref_thr(%d)\012\000"
.LC54:
	.ascii	"dec B frame, fwd ref err(%d) > ref_thr(%d)\012\000"
.LC55:
	.ascii	"image size abnormal(%dx%d)\012\000"
.LC56:
	.ascii	"mp2 actual frame size(%dx%d) exeed max config(%dx%d"
	.ascii	")\012\000"
	.space	2
.LC57:
	.ascii	"partition fs memory fail!\012\000"
	.space	1
.LC58:
	.ascii	"FSP_ConfigInstance fail!\012\000"
	.space	2
.LC59:
	.ascii	"Protocol %d\012\000"
	.space	3
.LC60:
	.ascii	"seq size change, call vpss to release all frames.\012"
	.ascii	"\000"
	.space	1
.LC61:
	.ascii	"new seq size %dx%d\012\000"
.LC62:
	.ascii	"found sh %#x\012\000"
	.space	2
.LC63:
	.ascii	"SEQUENCE_HEADER_CODE Bitstream is not enough!\012\000"
	.space	1
.LC64:
	.ascii	"found gh %#x\012\000"
	.space	2
.LC65:
	.ascii	"GROUP_START_CODE Bitstream is not enough!\012\000"
	.space	1
.LC66:
	.ascii	"found ph %#x\012\000"
	.space	2
.LC67:
	.ascii	"PICTURE_START_CODE Bitstream is not enough!\012\000"
	.space	3
.LC68:
	.ascii	"found ud %#x\012\000"
	.space	2
.LC69:
	.ascii	"get usd err\012\000"
	.space	3
.LC70:
	.ascii	"cann't get ud pointer\012\000"
	.space	1
.LC71:
	.ascii	"found ext %#x\012\000"
	.space	1
.LC72:
	.ascii	"MP2_DecSlice is wrong!\012\000"
.LC73:
	.ascii	"line %d, MP2_ReceivePacket receive packet failed!\012"
	.ascii	"\000"
	.space	1
.LC74:
	.ascii	"MP2 Decode Decide is wrong!\012\000"
	.space	3
.LC75:
	.ascii	"MP2 get picture info is wrong!\012\000"
.LC76:
	.ascii	"MP2 dec new pic failed!\012\000"
	.bss
	.align	2
.LANCHOR2 = . + 0
	.type	g_tmpusd, %object
	.size	g_tmpusd, 1024
g_tmpusd:
	.space	1024
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
