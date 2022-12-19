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
	.file	"vdm_hal_hevc.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(vdm_hal_hevc)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD
@ drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/.vdm_hal_hevc.o.d
@ /home/t00194509/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/verify/maintain_spc062/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC065/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal_hevc.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal_hevc.o
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
	.global	HEVCGet_V300R001_VirAddr
	.type	HEVCGet_V300R001_VirAddr, %function
HEVCGet_V300R001_VirAddr:
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
	add	r0, r1, r0, asl #2	@,, pbase_vir_addr, Dn,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	HEVCGet_V300R001_VirAddr, .-HEVCGet_V300R001_VirAddr
	.align	2
	.global	HEVCGet_V300R001_PhyAddr
	.type	HEVCGet_V300R001_PhyAddr, %function
HEVCGet_V300R001_PhyAddr:
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
	add	r0, r1, r0, asl #2	@,, base_phy_addr, Dn,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	HEVCGet_V300R001_PhyAddr, .-HEVCGet_V300R001_PhyAddr
	.align	2
	.global	HEVC_WriteQmatrix
	.type	HEVC_WriteQmatrix, %function
HEVC_WriteQmatrix:
	.fnstart
.LFB1533:
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
	cmp	r1, #0	@
	mov	r6, r0	@ qmatrix, qmatrix
	str	r1, [fp, #-48]	@, %sfp
	mov	r9, r2	@ phy_addr, phy_addr
	mov	r7, r3	@ vir_addr, vir_addr
	beq	.L8	@,
	ldr	r3, [r0, #0]	@ tmp170,* qmatrix
	mov	r2, #0	@,
	sub	r5, r1, #1	@ tmp177,,
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC0	@,
	movt	r1, #:upper16:.LC0	@,
	str	r3, [r7, #0]	@ tmp170,* vir_addr
	mov	r8, #1	@ i,
	ldr	r3, [r6, #0]	@,* qmatrix
	and	r5, r5, #1	@ tmp179, tmp177,
	bl	dprint_vfmw	@
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC1	@,
	mov	r2, r9	@, phy_addr
	movt	r1, #:upper16:.LC1	@,
	ldr	r3, [r7, #0]	@,* vir_addr
	bl	dprint_vfmw	@
	ldr	r1, [fp, #-48]	@, %sfp
	mov	r4, #4	@ ivtmp.571,
	cmp	r1, r8	@,
	bls	.L8	@,
	cmp	r5, #0	@ tmp179,
	beq	.L7	@,
	ldr	ip, [r6, #4]	@ tmp194,
	mov	r2, r8	@, i
	mov	r0, r4	@, ivtmp.571
	movw	r1, #:lower16:.LC0	@,
	movt	r1, #:upper16:.LC0	@,
	mov	r8, #2	@ i,
	str	ip, [r7, #4]	@ tmp194,
	ldr	r3, [r6, #4]	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@, ivtmp.571
	add	r2, r9, #4	@, phy_addr,
	movw	r1, #:lower16:.LC1	@,
	ldr	r3, [r7, #4]	@,
	movt	r1, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	ldr	r2, [fp, #-48]	@, %sfp
	mov	r4, #8	@ ivtmp.571,
	cmp	r2, r8	@, i
	bls	.L8	@,
.L7:
	ldr	sl, [r6, r4]	@ tmp184,* ivtmp.571
	add	r5, r4, #4	@ tmp181, ivtmp.571,
	mov	r2, r8	@, i
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC0	@,
	movt	r1, #:upper16:.LC0	@,
	str	sl, [r7, r4]	@ tmp184,* ivtmp.571
	add	sl, r8, #1	@ tmp180, i,
	ldr	r3, [r6, r4]	@,* ivtmp.571
	add	r8, sl, #1	@ i, tmp180,
	bl	dprint_vfmw	@
	add	r2, r4, r9	@, ivtmp.571, phy_addr
	ldr	r3, [r7, r4]	@,* ivtmp.571
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC1	@,
	movt	r1, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	ldr	r4, [r6, r5]	@ tmp190,
	mov	r2, sl	@, tmp180
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC0	@,
	movt	r1, #:upper16:.LC0	@,
	str	r4, [r7, r5]	@ tmp190,
	add	r4, r5, r0	@ ivtmp.571, tmp181,
	ldr	r3, [r6, r5]	@,
	bl	dprint_vfmw	@
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC1	@,
	add	r2, r5, r9	@, tmp181, phy_addr
	movt	r1, #:upper16:.LC1	@,
	ldr	r3, [r7, r5]	@,
	bl	dprint_vfmw	@
	ldr	r0, [fp, #-48]	@, %sfp
	cmp	r0, r8	@, i
	bhi	.L7	@,
.L8:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
	.fnend
	.size	HEVC_WriteQmatrix, .-HEVC_WriteQmatrix
	.align	2
	.global	HEVC_WriteTileInfo
	.type	HEVC_WriteTileInfo, %function
HEVC_WriteTileInfo:
	.fnstart
.LFB1534:
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
	mov	r9, r0	@ pParam, pParam
	ldr	r0, [r1, #1104]	@, <variable>.tile_segment_info_phy_addr
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@ D.38933,
	mov	r2, r0	@ D.38933,
	mov	r3, r0	@ p_base, D.38933
	movne	sl, #0	@ i,
	beq	.L40	@,
.L18:
	mov	r1, sl, asl #11	@ tmp180, i,
	mov	ip, #8	@ j,
	add	r8, r1, #1920	@ tmp181, tmp180,
	add	r0, r8, #12	@ tmp181, tmp181,
	add	r8, r9, r0	@ tmp183, pParam, tmp181
	add	r1, r8, #20	@ ivtmp.675, tmp183,
	mov	r4, r8	@ ivtmp.675, tmp183
	ldr	r7, [r8, #4]	@ tmp223, <variable>.TileId
	ldr	r6, [r4], #4	@ tmp225, <variable>.TileId
	ldr	r5, [r4, #-8]	@ tmp230, <variable>.TileId
	mov	lr, r6, asl #16	@ tmp226, tmp225,
	ldr	r4, [r4, #-12]	@ tmp228, <variable>.TileId
	orr	r6, lr, r7, asl #24	@, tmp227, tmp226, tmp223,
	orr	lr, r6, r4	@ tmp229, tmp227, tmp228
	orr	r4, lr, r5, asl ip	@, tmp232, tmp229, tmp230,
	str	r4, [r3, #0]	@ tmp232,* p_base
	ldr	r5, [r1, #-4]	@ tmp257, <variable>.TileId
	ldr	r7, [r8, #20]	@ tmp255, <variable>.TileId
	ldr	r4, [r1, #-8]	@ tmp262, <variable>.TileId
	mov	lr, r5, asl #16	@ tmp258, tmp257,
	ldr	r5, [r1, #-12]	@ tmp260, <variable>.TileId
	orr	r6, lr, r7, asl #24	@, tmp259, tmp258, tmp255,
	add	r1, r8, #36	@ ivtmp.675, tmp183,
	orr	r7, r6, r5	@ tmp261, tmp259, tmp260
	orr	lr, r7, r4, asl ip	@, tmp264, tmp261, tmp262,
	str	lr, [r3, #4]	@ tmp264,
.L20:
	ldr	r0, [r1, #-4]	@ tmp173, <variable>.TileId
	add	lr, r1, #16	@ tmp208, ivtmp.675,
	ldr	r8, [r1, #0]	@ tmp171, <variable>.TileId
	add	r4, ip, #4	@ tmp207, j,
	ldr	r5, [r1, #-12]	@ tmp176, <variable>.TileId
	mov	r7, r0, asl #16	@ tmp172, tmp173,
	ldr	r0, [r1, #-8]	@ tmp178, <variable>.TileId
	orr	r6, r7, r8, asl #24	@, tmp174, tmp172, tmp171,
	orr	r8, r6, r5	@ tmp175, tmp174, tmp176
	orr	r7, r8, r0, asl #8	@, tmp179, tmp175, tmp178,
	str	r7, [r3, ip]	@ tmp179,* j
	ldr	r6, [lr, #-4]	@ tmp213, <variable>.TileId
	add	ip, r4, #4	@ j, tmp207,
	ldr	r7, [r1, #16]	@ tmp211, <variable>.TileId
	cmp	ip, #512	@ j,
	ldr	r8, [lr, #-8]	@ tmp218, <variable>.TileId
	add	r1, lr, #16	@ ivtmp.675, tmp208,
	ldr	r5, [lr, #-12]	@ tmp216, <variable>.TileId
	mov	r6, r6, asl #16	@ tmp214, tmp213,
	orr	r0, r6, r7, asl #24	@, tmp215, tmp214, tmp211,
	orr	lr, r0, r5	@ tmp217, tmp215, tmp216
	orr	r0, lr, r8, asl #8	@, tmp220, tmp217, tmp218,
	str	r0, [r3, r4]	@ tmp220,
	bne	.L20	@,
	add	sl, sl, #1	@ i, i,
	add	r3, r3, #512	@ p_base, p_base,
	cmp	sl, #2	@ i,
	bne	.L18	@,
	add	r3, r9, #6016	@ ivtmp.662, pParam,
	add	r4, r2, #80	@ D.40099, D.38933,
	add	r3, r3, #8	@ ivtmp.662, ivtmp.662,
	mov	r1, r2	@ ivtmp.666, D.38933
.L22:
	ldr	r5, [r3, #0]	@ tmp186, <variable>.TilePosX
	add	lr, r3, #8	@ tmp202, ivtmp.662,
	ldr	ip, [r3, #-4]	@ tmp187, <variable>.TilePosX
	orr	r0, ip, r5, asl #16	@, tmp188, tmp187, tmp186,
	str	r0, [r1, #1024]	@ tmp188,
	ldr	ip, [r3, #8]	@ tmp235, <variable>.TilePosX
	add	r3, lr, #8	@ ivtmp.662, tmp202,
	ldr	r0, [lr, #-4]	@ tmp237, <variable>.TilePosX
	orr	lr, r0, ip, asl #16	@, tmp238, tmp237, tmp235,
	str	lr, [r1, #1028]	@ tmp238,
	add	r1, r1, #8	@ ivtmp.666, ivtmp.666,
	cmp	r1, r4	@ ivtmp.666, D.40099
	bne	.L22	@,
	add	r9, r9, #6144	@ tmp189, pParam,
	add	r3, r2, #4	@ ivtmp.691, D.38933,
	add	r4, r2, #88	@ D.40083, D.38933,
	add	r1, r9, #48	@ ivtmp.649, tmp189,
	mov	lr, r9	@ ivtmp.649, tmp189
	cmp	r3, r4	@ ivtmp.691, D.40083
	ldr	ip, [lr, #40]!	@ tmp191, <variable>.TilePosY
	ldr	r0, [lr, #-4]	@ tmp192, <variable>.TilePosY
	orr	lr, r0, ip, asl #16	@, tmp193, tmp192, tmp191,
	str	lr, [r2, #1104]	@ tmp193,
	beq	.L39	@,
	mov	lr, #1	@ tmp199,
	cmp	lr, #0	@ tmp199,
	beq	.L23	@,
	ldr	r0, [r1, #0]	@ tmp251, <variable>.TilePosY
	ldr	ip, [r1, #-4]	@ tmp253, <variable>.TilePosY
	add	r1, r9, #56	@ ivtmp.649, tmp189,
	orr	r2, ip, r0, asl #16	@, tmp254, tmp253, tmp251,
	str	r2, [r3, #1104]	@ tmp254,
	add	r3, r3, #4	@ ivtmp.691, ivtmp.691,
	cmp	r3, r4	@ ivtmp.691, D.40083
	beq	.L39	@,
.L23:
	ldr	ip, [r1, #0]	@ tmp241, <variable>.TilePosY
	add	lr, r1, #8	@ tmp200, ivtmp.649,
	ldr	r0, [r1, #-4]	@ tmp243, <variable>.TilePosY
	orr	r2, r0, ip, asl #16	@, tmp244, tmp243, tmp241,
	str	r2, [r3, #1104]	@ tmp244,
	ldr	r0, [r1, #8]	@ tmp247, <variable>.TilePosY
	add	r1, lr, #8	@ ivtmp.649, tmp200,
	ldr	ip, [lr, #-4]	@ tmp249, <variable>.TilePosY
	orr	r2, ip, r0, asl #16	@, tmp250, tmp249, tmp247,
	str	r2, [r3, #1108]	@ tmp250,
	add	r3, r3, #8	@ ivtmp.691, ivtmp.691,
	cmp	r3, r4	@ ivtmp.691, D.40083
	bne	.L23	@,
.L39:
	mov	r0, #0	@ D.38937,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L40:
	movw	r1, #:lower16:.LC2	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	movt	r1, #:upper16:.LC2	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	movw	r3, #:lower16:.LC3	@,
	movt	r3, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38937,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	.fnend
	.size	HEVC_WriteTileInfo, .-HEVC_WriteTileInfo
	.align	2
	.global	HEVCHAL_V300R001_CutSliceChain
	.type	HEVCHAL_V300R001_CutSliceChain, %function
HEVCHAL_V300R001_CutSliceChain:
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
	bl	MEM_Phy2Vir	@
	subs	r3, r0, #0	@ D.38886,
	beq	.L45	@,
	mov	r0, #0	@ tmp142,
	str	r0, [r3, #252]	@ tmp142,
	ldmfd	sp, {fp, sp, pc}	@
.L45:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L46	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC4	@,
	movt	r3, #:upper16:.LC4	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38890,
	ldmfd	sp, {fp, sp, pc}	@
.L47:
	.align	2
.L46:
	.word	.LANCHOR0+20
	.fnend
	.size	HEVCHAL_V300R001_CutSliceChain, .-HEVCHAL_V300R001_CutSliceChain
	.align	2
	.global	HEVCWriteCabacTab
	.type	HEVCWriteCabacTab, %function
HEVCWriteCabacTab:
	.fnstart
.LFB1528:
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
	ldr	r1, .L80	@ tmp219,
	mov	r3, #0	@ idx,
	movw	r2, #:lower16:.LANCHOR1	@ ivtmp.750,
	movt	r2, #:upper16:.LANCHOR1	@ ivtmp.750,
	mov	r8, r3	@ i, idx
	mov	r7, r3	@ tmp221, idx
.L54:
	cmp	r8, #0	@ i,
	add	r6, r8, r8, asl #2	@, tmp181, i, i,
	add	r4, r2, r3, asl #1	@, ivtmp.761, ivtmp.750, idx,
	moveq	r5, #16	@ j,
	movne	r5, #0	@ j,
	add	lr, r5, r6, asl #5	@, tmp183, j, tmp181,
	ldr	ip, [r1, lr, asl #2]	@ initValue, s_InitValue
	add	r6, r1, lr, asl #2	@, ivtmp.759, tmp219, tmp183,
	cmn	ip, #1	@ initValue,
	beq	.L78	@,
	and	lr, ip, #15	@ tmp248, initValue,
	mov	ip, ip, asr #4	@ tmp244, initValue,
	mov	lr, lr, asl #3	@ tmp249, tmp248,
	add	ip, ip, ip, asl #2	@, tmp246, tmp244, tmp244,
	sub	ip, ip, #45	@ tmp247, tmp246,
	strb	ip, [r2, r3, asl #1]	@ tmp247, s_CabacMN
	sub	ip, lr, #16	@ tmp250, tmp249,
	strb	ip, [r4, #1]	@ tmp250, s_CabacMN
.L73:
	mov	ip, #1	@ tmp226,
	cmp	ip, #0	@ tmp226,
	add	r3, r3, ip	@ idx, idx,
	add	r5, r5, ip	@ j, j,
	add	lr, r6, #4	@ ivtmp.759, ivtmp.759,
	add	ip, r4, #2	@ ivtmp.761, ivtmp.761,
	beq	.L53	@,
	ldr	r6, [r6, #4]	@ initValue, s_InitValue
	add	r5, r5, #1	@ j, j,
	add	r3, r3, #1	@ idx, idx,
	add	lr, lr, #4	@ ivtmp.759, ivtmp.759,
	cmn	r6, #1	@ initValue,
	streqb	r7, [r4, #2]	@ tmp221, s_CabacMN
	andne	sl, r6, #15	@ tmp257, initValue,
	movne	r6, r6, asr #4	@ tmp253, initValue,
	streqb	r7, [ip, #1]	@ tmp221, s_CabacMN
	addne	r6, r6, r6, asl #2	@, tmp255, tmp253, tmp253,
	movne	sl, sl, asl #3	@ tmp258, tmp257,
	subne	r6, r6, #45	@ tmp256, tmp255,
	strneb	r6, [r4, #2]	@ tmp256, s_CabacMN
	subne	r4, sl, #16	@ tmp259, tmp258,
	strneb	r4, [ip, #1]	@ tmp259, s_CabacMN
	cmp	r5, #159	@ j,
	add	ip, ip, #2	@ ivtmp.761, ivtmp.761,
	ble	.L53	@,
	b	.L74	@
.L68:
	add	r5, r5, #1	@ j, tmp228,
	add	r4, r4, r4, asl #2	@, tmp263, tmp261, tmp261,
	cmp	r5, #159	@ j,
	sub	sl, sl, #16	@ tmp267, tmp266,
	sub	r4, r4, #45	@ tmp264, tmp263,
	add	r3, r3, #1	@ idx, tmp227,
	strb	r4, [ip, #2]	@ tmp264, s_CabacMN
	add	lr, lr, #4	@ ivtmp.759, tmp229,
	strb	sl, [r6, #1]	@ tmp267, s_CabacMN
	add	ip, r6, #2	@ ivtmp.761, tmp230,
	bgt	.L74	@,
.L53:
	ldr	r4, [lr, #0]	@ initValue, s_InitValue
	add	r3, r3, #1	@ tmp227, idx,
	add	r5, r5, #1	@ tmp228, j,
	and	r6, r4, #15	@ tmp200, initValue,
	cmn	r4, #1	@ initValue,
	mov	sl, r4, asr #4	@ tmp191, initValue,
	ldr	r4, [lr, #4]	@ initValue, s_InitValue
	mov	r6, r6, asl #3	@ tmp202, tmp200,
	streqb	r7, [ip, #0]	@ tmp221, s_CabacMN
	addne	sl, sl, sl, asl #2	@, tmp196, tmp191, tmp191,
	subne	r6, r6, #16	@ tmp204, tmp202,
	subne	sl, sl, #45	@ tmp198, tmp196,
	strneb	r6, [ip, #1]	@ tmp204, s_CabacMN
	strneb	sl, [ip, #0]	@ tmp198, s_CabacMN
	and	sl, r4, #15	@ tmp265, initValue,
	streqb	r7, [ip, #1]	@ tmp221, s_CabacMN
	cmn	r4, #1	@ initValue,
	add	r6, ip, #2	@ tmp230, ivtmp.761,
	add	lr, lr, #4	@ tmp229, ivtmp.759,
	mov	r4, r4, asr #4	@ tmp261, initValue,
	mov	sl, sl, asl #3	@ tmp266, tmp265,
	bne	.L68	@,
	add	r5, r5, #1	@ j, tmp228,
	strb	r7, [ip, #2]	@ tmp221, s_CabacMN
	cmp	r5, #159	@ j,
	strb	r7, [r6, #1]	@ tmp221, s_CabacMN
	add	r3, r3, #1	@ idx, tmp227,
	add	lr, lr, #4	@ ivtmp.759, tmp229,
	add	ip, r6, #2	@ ivtmp.761, tmp230,
	ble	.L53	@,
.L74:
	add	r8, r8, #1	@ i, i,
	cmp	r8, #3	@ i,
	bne	.L54	@,
	bl	MEM_Phy2Vir	@
	subs	r3, r0, #0	@ p,
	addne	r4, r3, #928	@ D.40191, p,
	movwne	r2, #:lower16:.LANCHOR1	@ ivtmp.750,
	movtne	r2, #:upper16:.LANCHOR1	@ ivtmp.750,
	beq	.L79	@,
.L57:
	ldrb	ip, [r2, #0]	@ zero_extendqisi2	@ tmp212, s_CabacMN
	mov	r1, r3	@ tmp224, p
	add	lr, r2, #2	@ tmp223, ivtmp.750,
	strb	ip, [r3, #1]	@ tmp212,
	ldrb	r0, [r2, #1]	@ zero_extendqisi2	@ tmp214, s_CabacMN
	strb	r0, [r1], #2	@ tmp214,
	ldrb	ip, [r2, #2]	@ zero_extendqisi2	@ tmp242, s_CabacMN
	add	r2, lr, #2	@ ivtmp.750, tmp223,
	strb	ip, [r1, #1]	@ tmp242,
	ldrb	r0, [lr, #1]	@ zero_extendqisi2	@ tmp243, s_CabacMN
	strb	r0, [r3, #2]	@ tmp243,
	add	r3, r1, #2	@ p, tmp224,
	cmp	r3, r4	@ p, D.40191
	bne	.L57	@,
	mov	r0, #0	@ D.38855,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L78:
	strb	r7, [r2, r3, asl #1]	@ tmp221, s_CabacMN
	strb	r7, [r4, #1]	@ tmp221, s_CabacMN
	b	.L73	@
.L79:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L80+4	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC5	@,
	movt	r3, #:upper16:.LC5	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38855,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L81:
	.align	2
.L80:
	.word	.LANCHOR0+52
	.word	.LANCHOR0+1972
	.fnend
	.size	HEVCWriteCabacTab, .-HEVCWriteCabacTab
	.align	2
	.global	HEVCHAL_V300R001_InitHal
	.type	HEVCHAL_V300R001_InitHal, %function
HEVCHAL_V300R001_InitHal:
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
	bl	HEVCWriteCabacTab	@
	cmp	r0, #0	@ D.38862
	ldmeqfd	sp, {fp, sp, pc}	@
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC6	@,
	movt	r1, #:upper16:.LC6	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38866,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	HEVCHAL_V300R001_InitHal, .-HEVCHAL_V300R001_InitHal
	.align	2
	.global	HEVCHAL_V300R001_CfgVdmReg
	.type	HEVCHAL_V300R001_CfgVdmReg, %function
HEVCHAL_V300R001_CfgVdmReg:
	.fnstart
.LFB1537:
	@ args = 0, pretend = 0, frame = 8
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
	ldr	r6, [r0, #16]	@ <variable>.PicHightInCtbsYMinus1, <variable>.PicHightInCtbsYMinus1
	ldr	ip, [r0, #20]	@ <variable>.PicWidthInCtbsYMinus1, <variable>.PicWidthInCtbsYMinus1
	subs	r5, r2, #0	@ VdhId, VdhId
	add	sl, r6, #1	@ tmp199, <variable>.PicHightInCtbsYMinus1,
	mov	r6, r1	@ pHwMem, pHwMem
	ldrb	r7, [r0, #1]	@ zero_extendqisi2	@ <variable>.scaling_list_enabled_flag, <variable>.scaling_list_enabled_flag
	mov	r3, #16777216	@ tmp190,
	mla	r1, ip, sl, sl	@ tmp201, <variable>.PicWidthInCtbsYMinus1, tmp199, tmp199
	bfi	r3, r7, #30, #1	@ tmp190, <variable>.scaling_list_enabled_flag,,
	mov	r4, r0	@ pPicParam, pPicParam
	bic	r3, r3, #-1342177280	@ tmp203, tmp190,
	movw	r2, #6440	@ tmp204,
	sub	r0, r1, #1	@ tmp202, tmp201,
	bfi	r3, r0, #0, #20	@ tmp203, tmp202,,
	str	r3, [r4, r2]	@ tmp203, <variable>.basic_cfg0
	str	r3, [fp, #-40]	@ tmp203,
	ble	.L111	@,
	movw	r1, #:lower16:.LC7	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC7	@,
	ldr	r2, .L118	@,
	mov	r3, r5	@, VdhId
	mov	r7, #1	@ tmp215,
	str	r7, [sp, #0]	@ tmp215,
	bl	dprint_vfmw	@
.L88:
	ldr	r2, [r4, #1316]	@ <variable>.NewPicFlag, <variable>.NewPicFlag
	mov	r0, #13	@ tmp220,
	mov	sl, #3	@ tmp223,
	cmp	r5, #0	@ VdhId,
	bfi	r0, r2, #14, #1	@ tmp220, <variable>.NewPicFlag,,
	movw	ip, #6444	@ tmp230,
	bic	lr, r0, #32768	@ tmp222, tmp220,
	bfi	lr, sl, #16, #12	@ tmp222, tmp223,,
	bic	r3, lr, #1879048192	@ tmp228, tmp222,
	orr	r3, r3, #536870912	@ tmp229, tmp228,
	bfc	r3, #31, #1	@ tmp229,,
	str	r3, [r4, ip]	@ tmp229, <variable>.basic_cfg1
	str	r3, [fp, #-40]	@ tmp229,
	ble	.L112	@,
	ldr	r2, .L118	@,
	mov	r3, r5	@, VdhId
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	mov	r7, #1	@ tmp275,
	str	r7, [sp, #0]	@ tmp275,
	bl	dprint_vfmw	@
	ldr	r0, [r6, #48]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	movw	r1, #6448	@ tmp280,
	mov	r3, r5	@, VdhId
	ldr	r2, .L118	@,
	bic	ip, r0, #15	@ tmp279, <variable>.MsgSlotAddr,
	mov	r0, #32	@,
	str	ip, [r4, r1]	@ tmp279, <variable>.avm_addr
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	str	ip, [fp, #-40]	@ tmp279, <variable>.av_msg_addr
	str	r7, [sp, #0]	@ tmp275,
	bl	dprint_vfmw	@
	ldr	r2, [fp, #-40]	@, D32
	mov	r0, sl	@, tmp223
	movw	r1, #:lower16:.LC8	@,
	movt	r1, #:upper16:.LC8	@,
	bl	dprint_vfmw	@
	ldr	r0, [r6, #32]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	movw	r1, #6452	@ tmp292,
	ldr	r2, .L118	@,
	bic	ip, r0, #15	@ tmp291, <variable>.MsgSlotAddr,
	mov	r3, r5	@, VdhId
	str	ip, [r4, r1]	@ tmp291, <variable>.vam_addr
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	str	ip, [fp, #-40]	@ tmp291, <variable>.va_msg_addr
	str	r7, [sp, #0]	@ tmp275,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #1308]	@ <variable>.stream_base_addr, <variable>.stream_base_addr
	movw	r0, #6456	@ tmp302,
	movw	r1, #:lower16:.LC7	@,
	ldr	r2, .L118	@,
	bic	ip, r3, #15	@ tmp301, <variable>.stream_base_addr,
	movt	r1, #:upper16:.LC7	@,
	str	ip, [r4, r0]	@ tmp301, <variable>.stream_base_addr_reg_tmp
	mov	r3, r5	@, VdhId
	mov	r0, #32	@,
	str	r7, [sp, #0]	@ tmp275,
	str	ip, [fp, #-40]	@ tmp301, <variable>.stream_base_addr
	bl	dprint_vfmw	@
.L90:
	mov	lr, #6464	@ tmp309,
	movw	r2, #6468	@ tmp311,
	cmp	r5, #0	@ VdhId,
	movw	r3, #:lower16:3148803	@ tmp308,
	movw	r0, #6472	@ tmp313,
	movt	r3, #:upper16:3148803	@ tmp308,
	movw	r1, #6476	@ tmp315,
	str	r3, [r4, lr]	@ tmp308, <variable>.sed_to
	str	r3, [r4, r2]	@ tmp308, <variable>.itrans_to
	movw	ip, #6480	@ tmp317,
	movw	lr, #6484	@ tmp319,
	movw	r2, #6488	@ tmp321,
	str	r3, [r4, r0]	@ tmp308, <variable>.pmv_to
	str	r3, [r4, r1]	@ tmp308, <variable>.prc_to
	str	r3, [r4, ip]	@ tmp308, <variable>.rcn_to
	str	r3, [r4, lr]	@ tmp308, <variable>.dblk_to
	str	r3, [r4, r2]	@ tmp308, <variable>.ppfd_to
	str	r3, [fp, #-40]	@ tmp308, D32
	ble	.L113	@,
	ldr	r2, .L118	@,
	mov	r3, r5	@, VdhId
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	mov	r6, #1	@ tmp395,
	str	r6, [sp, #0]	@ tmp395,
	bl	dprint_vfmw	@
	ldr	r2, .L118	@,
	mov	r3, r5	@, VdhId
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	str	r6, [sp, #0]	@ tmp395,
	bl	dprint_vfmw	@
	ldr	r2, .L118	@,
	mov	r3, r5	@, VdhId
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	str	r6, [sp, #0]	@ tmp395,
	bl	dprint_vfmw	@
	ldr	r2, .L118	@,
	mov	r3, r5	@, VdhId
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	str	r6, [sp, #0]	@ tmp395,
	bl	dprint_vfmw	@
	ldr	r2, .L118	@,
	mov	r3, r5	@, VdhId
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	str	r6, [sp, #0]	@ tmp395,
	bl	dprint_vfmw	@
	ldr	r2, .L118	@,
	mov	r3, r5	@, VdhId
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	str	r6, [sp, #0]	@ tmp395,
	bl	dprint_vfmw	@
	ldr	r2, .L118	@,
	mov	r3, r5	@, VdhId
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	str	r6, [sp, #0]	@ tmp395,
	bl	dprint_vfmw	@
	ldr	r0, [r4, #1280]	@ <variable>.CurrPicImgIdc, <variable>.CurrPicImgIdc
	movw	lr, #6492	@ tmp427,
	str	r6, [sp, #0]	@ tmp395,
	mov	r3, r5	@, VdhId
	add	r1, r0, #328	@ tmp422, <variable>.CurrPicImgIdc,
	ldr	r2, .L118	@,
	add	ip, r1, #2	@ tmp422, tmp422,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	ldr	ip, [r4, ip, asl #2]	@ tmp425, <variable>.ImgPhyAddr
	bic	ip, ip, #255	@ tmp426, tmp425,
	str	ip, [r4, lr]	@ tmp426, <variable>.ystaddr_1d
	str	ip, [fp, #-40]	@ tmp426, <variable>.ystaddr_1d
	bl	dprint_vfmw	@
	ldr	ip, [r4, #1288]	@ <variable>.imgstride, <variable>.imgstride
	movw	lr, #6496	@ tmp436,
	ldr	r2, .L118	@,
	mov	r3, r5	@, VdhId
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC7	@,
	str	ip, [r4, lr]	@ <variable>.imgstride, <variable>.ystride_1d
	movt	r1, #:upper16:.LC7	@,
	str	ip, [fp, #-40]	@ <variable>.imgstride, <variable>.ystride_1d
	str	r6, [sp, #0]	@ tmp395,
	bl	dprint_vfmw	@
	ldr	ip, [r4, #1292]	@ <variable>.UVOffset, <variable>.UVOffset
	movw	r3, #6500	@ tmp445,
	movw	r1, #:lower16:.LC7	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC7	@,
	ldr	r2, .L118	@,
	str	ip, [r4, r3]	@ <variable>.UVOffset, <variable>.uvoffset_1d
	mov	r3, r5	@, VdhId
	str	r6, [sp, #0]	@ tmp395,
	str	ip, [fp, #-40]	@ <variable>.UVOffset, <variable>.uvoffset_1d
	bl	dprint_vfmw	@
.L92:
	ldr	r1, [r4, #20]	@ <variable>.PicWidthInCtbsYMinus1, <variable>.PicWidthInCtbsYMinus1
	movw	r3, #2047	@ tmp455,
	ldr	ip, [r4, #68]	@ <variable>.CtbLog2SizeY, <variable>.CtbLog2SizeY
	add	r2, r1, #1	@ tmp451, <variable>.PicWidthInCtbsYMinus1,
	mov	r2, r2, asl ip	@ D.39631, tmp451,
	sub	lr, r2, #1	@ tmp454, D.39631,
	cmp	lr, r3	@ tmp454, tmp455
	bls	.L93	@,
	sub	r0, r2, #2048	@ tmp456, D.39631,
	sub	r1, r0, #1	@ tmp456, tmp456,
	cmp	r1, r3	@ tmp456, tmp455
	movls	r1, #1024	@ prephitmp.818,
	bhi	.L114	@,
.L95:
	ldr	r2, [r4, #184]	@ D.39648, <variable>.pic_height_in_luma_samples
	tst	r2, #15	@ D.39648,
	mov	lr, r2, lsr #4	@ tmp466, D.39648,
	addne	lr, lr, #1	@ frame_height_in_mb, tmp466,
	cmp	r5, #0	@ VdhId,
	add	r0, lr, #1	@ tmp467, frame_height_in_mb,
	mov	r3, r0, lsr #1	@ tmp468, tmp467,
	mul	r3, r1, r3	@ D.39657, prephitmp.818, tmp468
	movw	r1, #6504	@ tmp469,
	str	r3, [r4, r1]	@ D.39657, <variable>.head_inf_offset
	str	r3, [fp, #-40]	@ D.39657, D32
	ble	.L115	@,
	ldr	r2, .L118	@,
	mov	r3, r5	@, VdhId
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	mov	r7, #1	@ tmp499,
	str	r7, [sp, #0]	@ tmp499,
	bl	dprint_vfmw	@
	movw	r2, #6540	@ tmp503,
	mov	r6, #0	@ tmp500,
	mov	r3, r5	@, VdhId
	str	r6, [r4, r2]	@ tmp500, <variable>.ppfd_buf_addr
	mov	r0, #32	@,
	ldr	r2, .L118	@,
	movw	r1, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC7	@,
	str	r6, [fp, #-40]	@ tmp500, <variable>.ppfd_buf_addr
	str	r7, [sp, #0]	@ tmp499,
	bl	dprint_vfmw	@
	movw	ip, #6544	@ tmp513,
	str	r6, [fp, #-40]	@ tmp500, D32
	movw	r1, #:lower16:.LC7	@,
	str	r6, [r4, ip]	@ D32, <variable>.ppfd_buf_len
	movt	r1, #:upper16:.LC7	@,
	mov	r0, #32	@,
	ldr	r2, .L118	@,
	mov	r3, r5	@, VdhId
	str	r7, [sp, #0]	@ tmp499,
	bl	dprint_vfmw	@
.L100:
	ldr	r3, [r4, #188]	@ <variable>.pic_width_in_luma_samples, <variable>.pic_width_in_luma_samples
	movw	r1, #6548	@ tmp520,
	mov	r0, #24	@ tmp519,
	str	r0, [r4, r1]	@ tmp519, <variable>.DnrBasicCfg
	cmp	r3, #4096	@ <variable>.pic_width_in_luma_samples,
	movwls	r3, #:lower16:96016	@ tmp523,
	movwhi	r3, #30480	@ tmp524,
	movtls	r3, #:upper16:96016	@ tmp523,
	cmp	r5, #0	@ VdhId,
	str	r3, [fp, #-40]	@ tmp524, D32
	bne	.L116	@,
	movw	r2, #:lower16:s_RegPhyBaseAddr	@ tmp525,
	movt	r2, #:upper16:s_RegPhyBaseAddr	@ tmp525,
	ldr	r1, [fp, #-40]	@, D32
	ldr	lr, [r2, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	add	r0, lr, #4	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	mov	ip, #2	@ tmp529,
	str	ip, [fp, #-40]	@ tmp529, D32
.L106:
	movw	r0, #1208	@ tmp538,
	movw	r3, #:lower16:g_HwMem	@ tmp536,
	mul	r5, r0, r5	@ tmp537, tmp538, VdhId
	movt	r3, #:upper16:g_HwMem	@ tmp536,
	mov	lr, #2	@ tmp541,
	ldr	r2, [r5, r3]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	lr, [r2, #152]	@ tmp541,
	b	.L108	@
.L114:
	sub	lr, r2, #4096	@ tmp459, D.39631,
	sub	r1, lr, #1	@ tmp459, tmp459,
	cmp	r1, r3	@ tmp459, tmp455
	movls	r1, #1536	@ prephitmp.818,
	bls	.L95	@,
	sub	ip, r2, #6144	@ tmp462, D.39631,
	sub	r2, ip, #1	@ tmp462, tmp462,
	cmp	r2, r3	@ tmp462, tmp455
	movls	r1, #2048	@ prephitmp.818,
	bls	.L95	@,
.L93:
	mov	r1, #512	@ prephitmp.818,
	b	.L95	@
.L116:
	cmp	r5, #1	@ VdhId,
	beq	.L117	@,
	cmp	r5, #0	@ VdhId,
	mov	r1, #2	@ tmp535,
	str	r1, [fp, #-40]	@ tmp535, D32
	ble	.L106	@,
.L107:
	movw	r1, #:lower16:.LC7	@,
	mov	r3, r5	@, VdhId
	movt	r1, #:upper16:.LC7	@,
	mov	r0, #32	@,
	ldr	r2, .L118	@,
	mov	ip, #1	@ tmp546,
	str	ip, [sp, #0]	@ tmp546,
	bl	dprint_vfmw	@
.L108:
	ldr	r2, [fp, #-40]	@, D32
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC9	@,
	movt	r1, #:upper16:.LC9	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@,
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L117:
	movw	ip, #:lower16:s_RegPhyBaseAddr_1	@ tmp530,
	movt	ip, #:upper16:s_RegPhyBaseAddr_1	@ tmp530,
	ldr	r1, [fp, #-40]	@, D32
	ldr	r0, [ip, #0]	@ s_RegPhyBaseAddr_1, s_RegPhyBaseAddr_1
	add	r0, r0, #4	@, s_RegPhyBaseAddr_1,
	bl	MEM_WritePhyWord	@
	mov	r3, #2	@ tmp534,
	str	r3, [fp, #-40]	@ tmp534, D32
	b	.L107	@
.L113:
	movw	r1, #1208	@ tmp325,
	movw	r2, #:lower16:g_HwMem	@ tmp323,
	mul	r1, r1, r5	@ tmp324, tmp325, VdhId
	movt	r2, #:upper16:g_HwMem	@ tmp323,
	ldr	r0, [r1, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r3, [r0, #60]	@ tmp308,
	ldr	lr, [fp, #-40]	@ D32.876, D32
	ldr	ip, [r1, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	lr, [ip, #64]	@ D32.876,
	ldr	r0, [fp, #-40]	@ D32.879, D32
	ldr	r3, [r1, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r0, [r3, #68]	@ D32.879,
	ldr	lr, [fp, #-40]	@ D32.882, D32
	ldr	ip, [r1, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	lr, [ip, #72]	@ D32.882,
	ldr	r0, [fp, #-40]	@ D32.885, D32
	ldr	r3, [r1, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r0, [r3, #76]	@ D32.885,
	ldr	lr, [fp, #-40]	@ D32.888, D32
	ldr	ip, [r1, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	lr, [ip, #80]	@ D32.888,
	ldr	r0, [fp, #-40]	@ D32.891, D32
	ldr	r3, [r1, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r0, [r3, #84]	@ D32.891,
	ldr	ip, [r4, #1280]	@ <variable>.CurrPicImgIdc, <variable>.CurrPicImgIdc
	add	lr, ip, #328	@ tmp360, <variable>.CurrPicImgIdc,
	movw	ip, #6492	@ tmp365,
	add	r0, lr, #2	@ tmp360, tmp360,
	ldr	r3, [r4, r0, asl #2]	@ tmp363, <variable>.ImgPhyAddr
	bic	lr, r3, #255	@ tmp364, tmp363,
	str	lr, [r4, ip]	@ tmp364, <variable>.ystaddr_1d
	ldr	r0, [r1, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movw	r3, #6496	@ tmp375,
	str	lr, [r0, #96]	@ tmp364,
	movw	r0, #6500	@ tmp385,
	ldr	ip, [r4, #1288]	@ <variable>.imgstride, <variable>.imgstride
	str	ip, [r4, r3]	@ <variable>.imgstride, <variable>.ystride_1d
	ldr	lr, [r1, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	ip, [lr, #100]	@ <variable>.imgstride,
	ldr	r3, [r4, #1292]	@ <variable>.UVOffset, <variable>.UVOffset
	str	r3, [r4, r0]	@ <variable>.UVOffset, <variable>.uvoffset_1d
	ldr	ip, [r1, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r3, [ip, #104]	@ <variable>.UVOffset,
	b	.L92	@
.L115:
	movw	r1, #1208	@ tmp472,
	movw	lr, #:lower16:g_HwMem	@ tmp470,
	mul	r1, r1, r5	@ tmp471, tmp472, VdhId
	movt	lr, #:upper16:g_HwMem	@ tmp470,
	mov	r2, #0	@ tmp475,
	ldr	r0, [r1, lr]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r3, [r0, #108]	@ D.39657,
	movw	r3, #6540	@ tmp478,
	str	r2, [r4, r3]	@ tmp475, <variable>.ppfd_buf_addr
	movw	r0, #6544	@ tmp489,
	ldr	ip, [r1, lr]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r2, [ip, #128]	@ tmp475,
	str	r2, [fp, #-40]	@ tmp475, D32
	str	r2, [r4, r0]	@ D32, <variable>.ppfd_buf_len
	ldr	ip, [r1, lr]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r2, [ip, #132]	@ D32,
	b	.L100	@
.L112:
	movw	r8, #1208	@ tmp234,
	movw	r7, #:lower16:g_HwMem	@ tmp232,
	mul	r8, r8, r5	@ tmp233, tmp234, VdhId
	movt	r7, #:upper16:g_HwMem	@ tmp232,
	movw	r2, #6448	@ tmp241,
	mov	r0, sl	@, tmp223
	movw	r1, #:lower16:.LC8	@,
	movt	r1, #:upper16:.LC8	@,
	ldr	lr, [r8, r7]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r3, [lr, #12]	@ tmp229,
	ldr	ip, [r6, #48]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	bic	r3, ip, #15	@ tmp240, <variable>.MsgSlotAddr,
	str	r3, [r4, r2]	@ tmp240, <variable>.avm_addr
	ldr	lr, [r8, r7]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r3, [fp, #-40]	@ tmp240, <variable>.av_msg_addr
	str	r3, [lr, #16]	@ tmp240,
	ldr	r2, [fp, #-40]	@, D32
	bl	dprint_vfmw	@
	ldr	r0, [r6, #32]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	movw	ip, #6452	@ tmp254,
	bic	r1, r0, #15	@ tmp253, <variable>.MsgSlotAddr,
	str	r1, [r4, ip]	@ tmp253, <variable>.vam_addr
	ldr	r2, [r8, r7]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movw	r0, #6456	@ tmp265,
	str	r1, [r2, #20]	@ tmp253,
	ldr	r3, [r4, #1308]	@ <variable>.stream_base_addr, <variable>.stream_base_addr
	bic	ip, r3, #15	@ tmp264, <variable>.stream_base_addr,
	str	ip, [r4, r0]	@ tmp264, <variable>.stream_base_addr_reg_tmp
	ldr	r1, [r8, r7]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	ip, [r1, #24]	@ tmp264,
	b	.L90	@
.L111:
	movw	r1, #1208	@ tmp208,
	movw	r2, #:lower16:g_HwMem	@ tmp206,
	mul	r0, r1, r5	@ tmp207, tmp208, VdhId
	movt	r2, #:upper16:g_HwMem	@ tmp206,
	ldr	lr, [r0, r2]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r3, [lr, #8]	@ tmp203,
	b	.L88	@
.L119:
	.align	2
.L118:
	.word	.LANCHOR0+1992
	.fnend
	.size	HEVCHAL_V300R001_CfgVdmReg, .-HEVCHAL_V300R001_CfgVdmReg
	.global	__aeabi_uidivmod
	.global	__aeabi_uidiv
	.align	2
	.global	HEVCHAL_V300R001_SetSliceMsg
	.type	HEVCHAL_V300R001_SetSliceMsg, %function
HEVCHAL_V300R001_SetSliceMsg:
	.fnstart
.LFB1536:
	@ args = 24, pretend = 0, frame = 0
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
	mov	r6, r0	@ pPicParam, pPicParam
	mov	r0, r3	@, CurrMsgSlotPhy
	mov	r7, r3	@ CurrMsgSlotPhy, CurrMsgSlotPhy
	mov	r4, r2	@ pSliceParam, pSliceParam
	ldr	sl, [fp, #12]	@ slice_segment_address, slice_segment_address
	bl	MEM_Phy2Vir	@
	subs	r5, r0, #0	@ pSLOT_BASE,
	beq	.L167	@,
	mov	r1, #1280	@,
	bl	__memzero	@
	ldr	r0, [r4, #0]	@ <variable>.valid_bitlen, <variable>.valid_bitlen
	cmp	r0, #0	@ <variable>.valid_bitlen,
	beq	.L123	@,
	ldr	r0, [r4, #16]	@ <variable>.bytespos, <variable>.bytespos
	mov	r2, #0	@,
	ldr	r1, [r6, #1308]	@ <variable>.stream_base_addr, <variable>.stream_base_addr
	mov	r3, r7	@, CurrMsgSlotPhy
	bic	lr, r0, #15	@ tmp257, <variable>.bytespos,
	mov	r0, #4	@,
	bic	r8, r1, #15	@ tmp259, <variable>.stream_base_addr,
	movw	r1, #:lower16:.LC11	@,
	rsb	ip, r8, lr	@ temp.1191, tmp259, tmp257
	str	ip, [r5, #0]	@ temp.1191,* pSLOT_BASE
	ldr	r8, [r5, #0]	@ tmp261,* pSLOT_BASE
	movt	r1, #:upper16:.LC11	@,
	str	r8, [sp, #0]	@ tmp261,
	bl	dprint_vfmw	@
	ldr	lr, [r4, #16]	@ <variable>.bytespos, <variable>.bytespos
	mov	r2, #1	@,
	ldr	ip, [r4, #8]	@ <variable>.bitsoffset, <variable>.bitsoffset
	add	r3, r7, #4	@, CurrMsgSlotPhy,
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC11	@,
	add	r8, ip, lr, asl #3	@, tmp265, <variable>.bitsoffset, <variable>.bytespos,
	movt	r1, #:upper16:.LC11	@,
	and	ip, r8, #127	@ tmp.1203, tmp265,
	str	ip, [r5, #4]	@ tmp.1203,
	ldr	lr, [r5, #4]	@ tmp268,
	str	lr, [sp, #0]	@ tmp268,
	bl	dprint_vfmw	@
	ldr	r8, [r4, #0]	@ tmp.1209, <variable>.valid_bitlen
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC11	@,
	mov	r2, #2	@,
	movt	r1, #:upper16:.LC11	@,
	add	r3, r7, #8	@, CurrMsgSlotPhy,
	str	r8, [r5, #8]	@ tmp.1209,
	ldr	ip, [r5, #8]	@ tmp270,
	str	ip, [sp, #0]	@ tmp270,
	bl	dprint_vfmw	@
	ldr	r8, [r4, #4]	@ <variable>.valid_bitlen, <variable>.valid_bitlen
	cmp	r8, #0	@ <variable>.valid_bitlen,
	bne	.L168	@,
	str	r8, [r5, #12]	@ <variable>.valid_bitlen,
	add	r3, r7, #12	@, CurrMsgSlotPhy,
	ldr	lr, [r5, #12]	@ tmp291,
	mov	r2, #3	@,
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC11	@,
	movt	r1, #:upper16:.LC11	@,
	str	lr, [sp, #0]	@ tmp291,
	bl	dprint_vfmw	@
	str	r8, [r5, #16]	@ <variable>.valid_bitlen,
	mov	r0, #4	@,
	ldr	ip, [r5, #16]	@ tmp294,
	add	r3, r7, #16	@, CurrMsgSlotPhy,
	mov	r2, r0	@,
	movw	r1, #:lower16:.LC11	@,
	movt	r1, #:upper16:.LC11	@,
	str	ip, [sp, #0]	@ tmp294,
	bl	dprint_vfmw	@
	str	r8, [r5, #20]	@ <variable>.valid_bitlen,
	add	r3, r7, #20	@, CurrMsgSlotPhy,
	ldr	r7, [r5, #20]	@ tmp297,
	movw	r1, #:lower16:.LC11	@,
	mov	r0, #4	@,
	movt	r1, #:upper16:.LC11	@,
	mov	r2, #5	@,
	str	r7, [sp, #0]	@ tmp297,
	bl	dprint_vfmw	@
.L126:
	ldrb	ip, [r4, #24]	@ zero_extendqisi2	@ <variable>.IsLowDelay, <variable>.IsLowDelay
	movw	r3, #:lower16:.LANCHOR0	@ tmp325,
	ldrb	r7, [r4, #25]	@ zero_extendqisi2	@ <variable>.dependent_slice_segment_flag, <variable>.dependent_slice_segment_flag
	movt	r3, #:upper16:.LANCHOR0	@ tmp325,
	ldr	r2, [r4, #28]	@ <variable>.SliceQpY, <variable>.SliceQpY
	mov	r0, sl	@, slice_segment_address
	mov	r1, ip, asl #27	@ tmp301, <variable>.IsLowDelay,
	ldrb	ip, [r4, #32]	@ zero_extendqisi2	@ <variable>.cabac_init_flag, <variable>.cabac_init_flag
	and	lr, r2, #63	@ tmp303, <variable>.SliceQpY,
	orr	r8, r1, r7, asl #26	@, tmp302, tmp301, <variable>.dependent_slice_segment_flag,
	ldr	r7, [r4, #36]	@ <variable>.IndependentSliceSegmentAddr, <variable>.IndependentSliceSegmentAddr
	orr	r2, r8, lr, asl #19	@, tmp306, tmp302, tmp303,
	orr	lr, r2, ip, asl #18	@, tmp309, tmp306, <variable>.cabac_init_flag,
	orr	r8, lr, r7	@ tmp.1135, tmp309, <variable>.IndependentSliceSegmentAddr
	str	r8, [r5, #24]	@ tmp.1135,
	ldr	r1, [r4, #44]	@ <variable>.MaxNumMergeCand, <variable>.MaxNumMergeCand
	ldr	r7, [r4, #56]	@ <variable>.num_ref_idx_l1_active_minus1, <variable>.num_ref_idx_l1_active_minus1
	ldr	ip, [r4, #76]	@ <variable>.SliceType, <variable>.SliceType
	ldr	lr, [r4, #60]	@ <variable>.num_ref_idx_l0_active_minus1, <variable>.num_ref_idx_l0_active_minus1
	mov	r2, r1, asl #24	@ tmp313, <variable>.MaxNumMergeCand,
	ldr	r1, [r4, #72]	@ <variable>.listXsize, <variable>.listXsize
	orr	r8, r2, r7, asl #20	@, tmp315, tmp313, <variable>.num_ref_idx_l1_active_minus1,
	add	r7, r3, ip, asl #2	@, tmp329, tmp325, <variable>.SliceType,
	ldr	ip, [r4, #68]	@ <variable>.listXsize, <variable>.listXsize
	orr	r2, r8, lr, asl #16	@, tmp318, tmp315, <variable>.num_ref_idx_l0_active_minus1,
	ldrb	lr, [r4, #64]	@ zero_extendqisi2	@ <variable>.slice_temporal_mvp_enabled_flag, <variable>.slice_temporal_mvp_enabled_flag
	orr	r8, r2, r1, asl #8	@, tmp321, tmp318, <variable>.listXsize,
	ldr	r3, [r7, #2052]	@ tmp332, s_SliceTypeForPMV
	ldr	r1, [r4, #40]	@ <variable>.ColPicApc, <variable>.ColPicApc
	orr	r7, r8, ip, asl #2	@, tmp324, tmp321, <variable>.listXsize,
	orr	r2, r7, r3	@ tmp331, tmp324, tmp332
	ldrb	ip, [r4, #65]	@ zero_extendqisi2	@ <variable>.mvd_l1_zero_flag, <variable>.mvd_l1_zero_flag
	ldrb	r7, [r4, #52]	@ zero_extendqisi2	@ <variable>.collocated_from_l0_flag, <variable>.collocated_from_l0_flag
	orr	r8, r2, lr, asl #15	@, tmp335, tmp331, <variable>.slice_temporal_mvp_enabled_flag,
	mov	r1, r1, asl #28	@ tmp341, <variable>.ColPicApc,
	orr	r2, r8, ip, asl #14	@, tmp338, tmp335, <variable>.mvd_l1_zero_flag,
	orr	r3, r1, r7, asl #27	@, tmp343, tmp341, <variable>.collocated_from_l0_flag,
	orr	lr, r2, r3	@ tmp.1139, tmp338, tmp343
	str	lr, [r5, #28]	@ tmp.1139,
	str	sl, [r5, #32]	@ slice_segment_address,
	ldr	r8, [r6, #20]	@ <variable>.PicWidthInCtbsYMinus1, <variable>.PicWidthInCtbsYMinus1
	add	r7, r8, #1	@ D.39350, <variable>.PicWidthInCtbsYMinus1,
	mov	r1, r7	@, D.39350
	bl	__aeabi_uidivmod	@
	mov	r0, sl	@, slice_segment_address
	mov	r8, r1	@ tmp349,
	mov	r1, r7	@, D.39350
	bl	__aeabi_uidiv	@
	orr	r7, r8, r0, asl #16	@, tmp.1142, tmp349,,
	str	r7, [r5, #36]	@ tmp.1142,
	ldr	ip, [fp, #16]	@ SliceSegmentTileAddress, SliceSegmentTileAddress
	str	ip, [r5, #40]	@ SliceSegmentTileAddress,
	ldr	r0, [r4, #96]	@ <variable>.slice_cb_qp_offset, <variable>.slice_cb_qp_offset
	ldr	r1, [r4, #100]	@ <variable>.slice_cr_qp_offset, <variable>.slice_cr_qp_offset
	and	r2, r0, #31	@ tmp354, <variable>.slice_cb_qp_offset,
	and	r3, r1, #31	@ tmp357, <variable>.slice_cr_qp_offset,
	orr	r7, r3, r2, asl #8	@, D.39359, tmp357, tmp354,
	str	r7, [r5, #44]	@ D.39359,
	ldr	ip, [r4, #108]	@ <variable>.slice_beta_offset_div2, <variable>.slice_beta_offset_div2
	ldr	r0, [r4, #104]	@ <variable>.slice_tc_offset_div2, <variable>.slice_tc_offset_div2
	and	r1, ip, #15	@ tmp362, <variable>.slice_beta_offset_div2,
	ldrb	ip, [r4, #115]	@ zero_extendqisi2	@ <variable>.slice_loop_filter_across_slices_enabled_flag, <variable>.slice_loop_filter_across_slices_enabled_flag
	and	r2, r0, #15	@ tmp359, <variable>.slice_tc_offset_div2,
	ldrb	r0, [r4, #113]	@ zero_extendqisi2	@ <variable>.slice_sao_luma_flag, <variable>.slice_sao_luma_flag
	mov	r3, r1, asl #8	@ tmp364, tmp362,
	ldrb	r1, [r4, #112]	@ zero_extendqisi2	@ <variable>.slice_sao_chroma_flag, <variable>.slice_sao_chroma_flag
	orr	r7, r3, r2, asl #16	@, tmp365, tmp364, tmp359,
	ldrb	r2, [r4, #114]	@ zero_extendqisi2	@ <variable>.slice_deblocking_filter_disabled_flag, <variable>.slice_deblocking_filter_disabled_flag
	orr	r3, r7, ip	@ tmp367, tmp365, <variable>.slice_loop_filter_across_slices_enabled_flag
	orr	r7, r3, r0, asl #3	@, tmp370, tmp367, <variable>.slice_sao_luma_flag,
	orr	r0, r7, r1, asl #2	@, tmp373, tmp370, <variable>.slice_sao_chroma_flag,
	orr	r3, r0, r2, asl #1	@, D.39382, tmp373, <variable>.slice_deblocking_filter_disabled_flag,
	str	r3, [r5, #48]	@ D.39382,
	ldr	r7, [r4, #68]	@ D.39341, <variable>.listXsize
	cmp	r7, #0	@ D.39341,
	moveq	ip, r7	@ prephitmp.1037, D.39341
	beq	.L128	@,
	mov	r3, #1	@ i.1128,
	cmp	r3, r7	@ i.1128, D.39341
	sub	r0, r7, #1	@ tmp467, D.39341,
	ldr	ip, [r4, #116]	@ tmp.1145, <variable>.IsLongTerm
	and	r1, r0, r3	@ tmp469, tmp467,
	add	r2, r4, #4	@ ivtmp.1115, pSliceParam,
	beq	.L128	@,
	cmp	r1, #0	@ tmp469,
	beq	.L129	@,
	ldr	r0, [r2, #116]	@ tmp494, <variable>.IsLongTerm
	mov	r3, #2	@ i.1128,
	cmp	r3, r7	@ i.1128, D.39341
	add	r2, r2, #4	@ ivtmp.1115, ivtmp.1115,
	orr	ip, ip, r0, asl #1	@, tmp.1145, tmp.1145, tmp494,
	beq	.L128	@,
.L129:
	ldr	r8, [r2, #116]	@ tmp475, <variable>.IsLongTerm
	add	r0, r2, #4	@ tmp470, ivtmp.1115,
	add	r1, r3, #1	@ tmp471, i.1128,
	add	r2, r0, #4	@ ivtmp.1115, tmp470,
	ldr	r0, [r0, #116]	@ tmp480, <variable>.IsLongTerm
	orr	ip, ip, r8, asl r3	@, tmp.1145, tmp.1145, tmp475,
	add	r3, r1, #1	@ i.1128, tmp471,
	cmp	r3, r7	@ i.1128, D.39341
	orr	ip, ip, r0, asl r1	@, tmp.1145, tmp.1145, tmp480,
	bne	.L129	@,
.L128:
	str	ip, [r5, #52]	@ prephitmp.1037,
	ldr	r7, [r4, #72]	@ D.39338, <variable>.listXsize
	cmp	r7, #0	@ D.39338,
	moveq	ip, r7	@ prephitmp.1187, D.39338
	beq	.L131	@,
	mov	r3, #1	@ i,
	cmp	r3, r7	@ i, D.39338
	sub	r2, r7, #1	@ tmp462, D.39338,
	ldr	ip, [r4, #176]	@ tmp.1147, <variable>.IsLongTerm
	and	r1, r2, r3	@ tmp464, tmp462,
	add	r2, r4, #4	@ ivtmp.1110, pSliceParam,
	beq	.L131	@,
	cmp	r1, #0	@ tmp464,
	beq	.L132	@,
	ldr	r1, [r2, #176]	@ tmp492, <variable>.IsLongTerm
	mov	r3, #2	@ i,
	cmp	r3, r7	@ i, D.39338
	add	r2, r2, #4	@ ivtmp.1110, ivtmp.1110,
	orr	ip, ip, r1, asl #1	@, tmp.1147, tmp.1147, tmp492,
	beq	.L131	@,
.L132:
	ldr	r8, [r2, #176]	@ tmp485, <variable>.IsLongTerm
	add	r0, r2, #4	@ tmp466, ivtmp.1110,
	add	r1, r3, #1	@ tmp465, i,
	add	r2, r0, #4	@ ivtmp.1110, tmp466,
	ldr	r0, [r0, #176]	@ tmp490, <variable>.IsLongTerm
	orr	ip, ip, r8, asl r3	@, tmp.1147, tmp.1147, tmp485,
	add	r3, r1, #1	@ i, tmp465,
	cmp	r3, r7	@ i, D.39338
	orr	ip, ip, r0, asl r1	@, tmp.1147, tmp.1147, tmp490,
	bne	.L132	@,
.L131:
	str	ip, [r5, #56]	@ prephitmp.1187,
	ldr	ip, [r4, #68]	@ temp.1143, <variable>.listXsize
	cmp	ip, #0	@ temp.1143,
	beq	.L133	@,
	mov	r0, #0	@ tmp1,
	mov	r2, r4	@ ivtmp.1105, pSliceParam
	mov	r3, r0	@ i.1144, tmp1
	mov	sl, #15	@ Dn_0,
	b	.L136	@
.L134:
	cmp	r8, r3	@ tmp384, i.1144
	streq	r0, [r5, sl, asl #2]	@ tmp1,* pSLOT_BASE
	add	r3, r3, #1	@ i.1144, i.1144,
	add	r2, r2, #4	@ ivtmp.1105, ivtmp.1105,
	ldreq	ip, [r4, #68]	@ temp.1143, <variable>.listXsize
	cmp	ip, r3	@ temp.1143, i.1144
	bls	.L133	@,
.L136:
	and	r1, r3, #7	@ D.39392, i.1144,
	ldr	r7, [r2, #356]	@ tmp382, <variable>.Idx2Apc
	cmp	r1, #7	@ D.39392,
	sub	r8, ip, #1	@ tmp384, temp.1143,
	mov	r1, r1, asl #2	@ tmp380, D.39392,
	orr	r0, r0, r7, asl r1	@, tmp1, tmp1, tmp382,
	bne	.L134	@,
	str	r0, [r5, sl, asl #2]	@ tmp1,* pSLOT_BASE
	add	r3, r3, #1	@ i.1144, i.1144,
	ldr	ip, [r4, #68]	@ temp.1143, <variable>.listXsize
	add	sl, sl, #1	@ Dn_0, Dn_0,
	mov	r0, #0	@ tmp1,
	add	r2, r2, #4	@ ivtmp.1105, ivtmp.1105,
	cmp	ip, r3	@ temp.1143, i.1144
	bhi	.L136	@,
.L133:
	ldr	ip, [r4, #72]	@ temp.1146, <variable>.listXsize
	cmp	ip, #0	@ temp.1146,
	beq	.L137	@,
	mov	r0, #0	@ tmp1.1117,
	mov	r2, r4	@ ivtmp.1100, pSliceParam
	mov	r3, r0	@ i.1148, tmp1.1117
	mov	sl, #17	@ Dn_0.1116,
	b	.L140	@
.L138:
	cmp	r8, r3	@ tmp390, i.1148
	streq	r0, [r5, sl, asl #2]	@ tmp1.1117,* pSLOT_BASE
	add	r3, r3, #1	@ i.1148, i.1148,
	add	r2, r2, #4	@ ivtmp.1100, ivtmp.1100,
	ldreq	ip, [r4, #72]	@ temp.1146, <variable>.listXsize
	cmp	ip, r3	@ temp.1146, i.1148
	bls	.L137	@,
.L140:
	and	r1, r3, #7	@ temp.1152, i.1148,
	ldr	r7, [r2, #420]	@ tmp388, <variable>.Idx2Apc
	cmp	r1, #7	@ temp.1152,
	sub	r8, ip, #1	@ tmp390, temp.1146,
	mov	r1, r1, asl #2	@ tmp386, temp.1152,
	orr	r0, r0, r7, asl r1	@, tmp1.1117, tmp1.1117, tmp388,
	bne	.L138	@,
	str	r0, [r5, sl, asl #2]	@ tmp1.1117,* pSLOT_BASE
	add	r3, r3, #1	@ i.1148, i.1148,
	ldr	ip, [r4, #72]	@ temp.1146, <variable>.listXsize
	add	sl, sl, #1	@ Dn_0.1116, Dn_0.1116,
	mov	r0, #0	@ tmp1.1117,
	add	r2, r2, #4	@ ivtmp.1100, ivtmp.1100,
	cmp	ip, r3	@ temp.1146, i.1148
	bhi	.L140	@,
.L137:
	ldr	r1, [r4, #548]	@ tmp.1162, <variable>.Apc2MvAddr
	str	r1, [r5, #92]	@ tmp.1162,
	ldr	r0, [r6, #76]	@ <variable>.QpBdOffsetY, <variable>.QpBdOffsetY
	mov	ip, r0, lsr #1	@ tmp392, <variable>.QpBdOffsetY,
	mov	r2, ip, asl #8	@ tmp394, tmp392,
	orr	r3, r2, #16384	@ tmp.1164, tmp394,
	orr	r1, r3, #10	@ tmp.1164, tmp.1164,
	str	r1, [r5, #96]	@ tmp.1164,
	ldr	r0, [fp, #20]	@ end_ctb_in_slice_raster, end_ctb_in_slice_raster
	str	r0, [r5, #172]	@ end_ctb_in_slice_raster,
	ldr	ip, [fp, #24]	@ end_ctb_in_slice_tile, end_ctb_in_slice_tile
	str	ip, [r5, #176]	@ end_ctb_in_slice_tile,
	ldr	r2, [fp, #8]	@ NextSlcMsgSlotPhy, NextSlcMsgSlotPhy
	str	r2, [r5, #252]	@ NextSlcMsgSlotPhy,
	ldrb	r3, [r6, #33]	@ zero_extendqisi2	@ <variable>.weighted_pred_flag, <variable>.weighted_pred_flag
	cmp	r3, #0	@ <variable>.weighted_pred_flag,
	beq	.L141	@,
	ldr	r3, [r4, #76]	@ <variable>.SliceType, <variable>.SliceType
	cmp	r3, #1	@ <variable>.SliceType,
	beq	.L142	@,
.L141:
	ldrb	r2, [r6, #32]	@ zero_extendqisi2	@ <variable>.weighted_bipred_flag, <variable>.weighted_bipred_flag
	cmp	r2, #1	@ <variable>.weighted_bipred_flag,
	beq	.L169	@,
.L143:
	mov	r0, #0	@ D.39244,
.L122:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L168:
	ldr	r0, [r4, #20]	@ <variable>.bytespos, <variable>.bytespos
	add	r3, r7, #12	@, CurrMsgSlotPhy,
	ldr	r1, [r6, #1308]	@ <variable>.stream_base_addr, <variable>.stream_base_addr
	mov	r2, #3	@,
	bic	lr, r0, #15	@ tmp276, <variable>.bytespos,
	mov	r0, #4	@,
	bic	ip, r1, #15	@ tmp278, <variable>.stream_base_addr,
	movw	r1, #:lower16:.LC11	@,
	rsb	r8, ip, lr	@ D.39264, tmp278, tmp276
	str	r8, [r5, #12]	@ D.39264,
	ldr	ip, [r5, #12]	@ tmp280,
	movt	r1, #:upper16:.LC11	@,
	str	ip, [sp, #0]	@ tmp280,
	bl	dprint_vfmw	@
	ldr	lr, [r4, #20]	@ <variable>.bytespos, <variable>.bytespos
	mov	r0, #4	@,
	ldr	r8, [r4, #12]	@ <variable>.bitsoffset, <variable>.bitsoffset
	add	r3, r7, #16	@, CurrMsgSlotPhy,
	mov	r2, r0	@,
	movw	r1, #:lower16:.LC11	@,
	add	ip, r8, lr, asl #3	@, tmp284, <variable>.bitsoffset, <variable>.bytespos,
	movt	r1, #:upper16:.LC11	@,
	and	lr, ip, #127	@ tmp.457, tmp284,
	str	lr, [r5, #16]	@ tmp.457,
	ldr	r8, [r5, #16]	@ tmp287,
	str	r8, [sp, #0]	@ tmp287,
	bl	dprint_vfmw	@
	ldr	ip, [r4, #4]	@ tmp.1120, <variable>.valid_bitlen
	add	r3, r7, #20	@, CurrMsgSlotPhy,
	movw	r1, #:lower16:.LC11	@,
	mov	r2, #5	@,
	movt	r1, #:upper16:.LC11	@,
	mov	r0, #4	@,
	str	ip, [r5, #20]	@ tmp.1120,
	ldr	r7, [r5, #20]	@ tmp289,
	str	r7, [sp, #0]	@ tmp289,
	bl	dprint_vfmw	@
	b	.L126	@
.L169:
	ldr	ip, [r4, #76]	@ <variable>.SliceType, <variable>.SliceType
	cmp	ip, #0	@ <variable>.SliceType,
	bne	.L143	@,
.L142:
	mov	r1, r5	@, pSLOT_BASE
	mov	r0, #64	@,
	bl	HEVC_GetVirAddr	@
	mov	r1, r5	@, pSLOT_BASE
	mov	r6, r0	@ pSLOT_line0,
	mov	r0, #128	@,
	bl	HEVC_GetVirAddr	@
	ldr	r1, [r4, #68]	@ <variable>.listXsize, <variable>.listXsize
	cmp	r1, #0	@ <variable>.listXsize,
	beq	.L144	@,
	mov	r3, r4	@ ivtmp.1085, pSliceParam
	mov	r7, r6	@ ivtmp.1087, pSLOT_line0
	mov	r1, r0	@ ivtmp.1092, pSLOT_line1
	mov	r2, r4	@ ivtmp.1186, pSliceParam
	mov	r5, #0	@ i.1166,
.L145:
	ldr	sl, [r2, #572]	@ tmp402, <variable>.LumaWeightL0
	add	r5, r5, #1	@ i.1166, i.1166,
	ldrb	lr, [r2, #692]	@ zero_extendqisi2	@ tmp405, <variable>.luma_offset_l0
	add	r2, r2, #4	@ ivtmp.1186, ivtmp.1186,
	ldr	r8, [r4, #564]	@ <variable>.luma_log2_weight_denom, <variable>.luma_log2_weight_denom
	mov	ip, sl, asl #23	@ tmp401, tmp402,
	mov	sl, lr, asl #12	@ tmp407, tmp405,
	and	r8, r8, #7	@ tmp409, <variable>.luma_log2_weight_denom,
	mov	lr, ip, lsr #23	@ tmp401, tmp401,
	orr	ip, sl, lr, asl #3	@, tmp408, tmp407, tmp401,
	orr	lr, ip, r8	@ tmp.1173, tmp408, tmp409
	str	lr, [r7], #4	@ tmp.1173,
	ldr	ip, [r3, #812]	@ tmp412, <variable>.ChromaWeightL0
	ldrb	sl, [r3, #1052]	@ zero_extendqisi2	@ tmp415, <variable>.ChromaOffsetL0
	ldr	r8, [r4, #568]	@ <variable>.chroma_log2_weight_denom, <variable>.chroma_log2_weight_denom
	mov	lr, ip, asl #23	@ tmp411, tmp412,
	mov	sl, sl, asl #12	@ tmp417, tmp415,
	and	r8, r8, #7	@ tmp419, <variable>.chroma_log2_weight_denom,
	mov	ip, lr, lsr #23	@ tmp411, tmp411,
	orr	lr, sl, ip, asl #3	@, tmp418, tmp417, tmp411,
	orr	ip, lr, r8	@ tmp.1175, tmp418, tmp419
	str	ip, [r1, #0]	@ tmp.1175,* ivtmp.1092
	ldr	lr, [r3, #816]	@ tmp425, <variable>.ChromaWeightL0
	ldrb	r8, [r3, #1056]	@ zero_extendqisi2	@ tmp421, <variable>.ChromaOffsetL0
	add	r3, r3, #8	@ ivtmp.1085, ivtmp.1085,
	mov	ip, lr, asl #23	@ tmp424, tmp425,
	mov	lr, ip, lsr #23	@ tmp424, tmp424,
	orr	ip, lr, r8, asl #9	@, D.39460, tmp424, tmp421,
	str	ip, [r1, #128]	@ D.39460,
	ldr	lr, [r4, #68]	@ <variable>.listXsize, <variable>.listXsize
	add	r1, r1, #4	@ ivtmp.1092, ivtmp.1092,
	cmp	lr, r5	@ <variable>.listXsize, i.1166
	bhi	.L145	@,
.L144:
	ldr	ip, [r4, #76]	@ <variable>.SliceType, <variable>.SliceType
	cmp	ip, #0	@ <variable>.SliceType,
	bne	.L143	@,
	ldr	r3, [r4, #72]	@ <variable>.listXsize, <variable>.listXsize
	cmp	r3, #0	@ <variable>.listXsize,
	beq	.L143	@,
	add	r6, r6, #64	@ ivtmp.1070, pSLOT_line0,
	add	r1, r0, #64	@ ivtmp.1076, pSLOT_line1,
	mov	r2, r4	@ ivtmp.1068, pSliceParam
	mov	r3, r4	@ ivtmp.1212, pSliceParam
.L146:
	ldr	r0, [r2, #632]	@ tmp431, <variable>.LumaWeightL1
	add	ip, ip, #1	@ i.1168, i.1168,
	ldrb	r7, [r2, #752]	@ zero_extendqisi2	@ tmp434, <variable>.luma_offset_l1
	add	r2, r2, #4	@ ivtmp.1068, ivtmp.1068,
	ldr	r5, [r4, #564]	@ <variable>.luma_log2_weight_denom, <variable>.luma_log2_weight_denom
	mov	lr, r0, asl #23	@ tmp430, tmp431,
	mov	r7, r7, asl #12	@ tmp436, tmp434,
	and	r5, r5, #7	@ tmp438, <variable>.luma_log2_weight_denom,
	mov	r0, lr, lsr #23	@ tmp430, tmp430,
	orr	lr, r7, r0, asl #3	@, tmp437, tmp436, tmp430,
	orr	r0, lr, r5	@ tmp.1181, tmp437, tmp438
	str	r0, [r6], #4	@ tmp.1181,
	ldr	lr, [r3, #932]	@ tmp441, <variable>.ChromaWeightL1
	ldrb	r7, [r3, #1172]	@ zero_extendqisi2	@ tmp444, <variable>.ChromaOffsetL1
	ldr	r5, [r4, #568]	@ <variable>.chroma_log2_weight_denom, <variable>.chroma_log2_weight_denom
	mov	r0, lr, asl #23	@ tmp440, tmp441,
	mov	r7, r7, asl #12	@ tmp446, tmp444,
	and	r5, r5, #7	@ tmp448, <variable>.chroma_log2_weight_denom,
	mov	lr, r0, lsr #23	@ tmp440, tmp440,
	orr	r0, r7, lr, asl #3	@, tmp447, tmp446, tmp440,
	orr	lr, r0, r5	@ tmp.1185, tmp447, tmp448
	str	lr, [r1, #0]	@ tmp.1185,* ivtmp.1076
	ldr	r0, [r3, #936]	@ tmp454, <variable>.ChromaWeightL1
	ldrb	r5, [r3, #1176]	@ zero_extendqisi2	@ tmp450, <variable>.ChromaOffsetL1
	add	r3, r3, #8	@ ivtmp.1212, ivtmp.1212,
	mov	lr, r0, asl #23	@ tmp453, tmp454,
	mov	r0, lr, lsr #23	@ tmp453, tmp453,
	orr	lr, r0, r5, asl #9	@, D.39494, tmp453, tmp450,
	str	lr, [r1, #128]	@ D.39494,
	ldr	r0, [r4, #72]	@ <variable>.listXsize, <variable>.listXsize
	add	r1, r1, #4	@ ivtmp.1076, ivtmp.1076,
	cmp	r0, ip	@ <variable>.listXsize, i.1168
	bhi	.L146	@,
	b	.L143	@
.L123:
	movw	r1, #:lower16:.LC12	@,
	ldr	r2, .L170	@,
	movt	r1, #:upper16:.LC12	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39244,
	b	.L122	@
.L167:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L170	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC10	@,
	movt	r3, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39244,
	b	.L122	@
.L171:
	.align	2
.L170:
	.word	.LANCHOR0+2020
	.fnend
	.size	HEVCHAL_V300R001_SetSliceMsg, .-HEVCHAL_V300R001_SetSliceMsg
	.align	2
	.global	HEVCHAL_V300R001_SetPicMsg
	.type	HEVCHAL_V300R001_SetPicMsg, %function
HEVCHAL_V300R001_SetPicMsg:
	.fnstart
.LFB1535:
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
	mov	r4, r0	@ pParam, pParam
	mov	r0, r2	@, PicMsgSlotPhy
	mov	r7, r2	@ PicMsgSlotPhy, PicMsgSlotPhy
	mov	r6, r1	@ pHwMem, pHwMem
	mov	r9, r3	@ FstSlcMsgSlotPhy, FstSlcMsgSlotPhy
	bl	MEM_Phy2Vir	@
	subs	r5, r0, #0	@ D.38984,
	beq	.L189	@,
	mov	r1, #1280	@,
	bl	__memzero	@
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC14	@,
	movt	r1, #:upper16:.LC14	@,
	bl	dprint_vfmw	@
	ldrb	ip, [r4, #0]	@ zero_extendqisi2	@ <variable>.strong_intra_smoothing_enabled_flag, <variable>.strong_intra_smoothing_enabled_flag
	ldr	r8, [r4, #16]	@ <variable>.PicHightInCtbsYMinus1, <variable>.PicHightInCtbsYMinus1
	mov	r0, #4	@,
	ldrb	lr, [r4, #1]	@ zero_extendqisi2	@ <variable>.scaling_list_enabled_flag, <variable>.scaling_list_enabled_flag
	movw	r1, #:lower16:.LC15	@,
	ldr	sl, [r4, #8]	@ <variable>.chroma_format_idc, <variable>.chroma_format_idc
	mov	r3, ip, asl #25	@ tmp243, <variable>.strong_intra_smoothing_enabled_flag,
	ldrb	ip, [r4, #2]	@ zero_extendqisi2	@ <variable>.pcm_loop_filter_disabled_flag, <variable>.pcm_loop_filter_disabled_flag
	mov	r2, r8, asl #9	@ tmp232, <variable>.PicHightInCtbsYMinus1,
	orr	r3, r3, lr, asl #24	@, tmp244, tmp243, <variable>.scaling_list_enabled_flag,
	ldrb	r8, [r4, #3]	@ zero_extendqisi2	@ <variable>.sample_adaptive_offset_enabled_flag, <variable>.sample_adaptive_offset_enabled_flag
	ldrb	lr, [r4, #12]	@ zero_extendqisi2	@ <variable>.pcm_enabled_flag, <variable>.pcm_enabled_flag
	orr	r2, r2, sl, asl #19	@, tmp234, tmp232, <variable>.chroma_format_idc,
	orr	r3, r3, ip, asl #23	@, tmp247, tmp244, <variable>.pcm_loop_filter_disabled_flag,
	ldr	sl, [r4, #20]	@, <variable>.PicWidthInCtbsYMinus1
	ldrb	ip, [r4, #4]	@ zero_extendqisi2	@ <variable>.amp_enabled_flag, <variable>.amp_enabled_flag
	orr	r3, r3, r8, asl #22	@, tmp250, tmp247, <variable>.sample_adaptive_offset_enabled_flag,
	orr	r2, r2, sl	@ tmp235, tmp234,
	movt	r1, #:upper16:.LC15	@,
	orr	r8, r2, lr, asl #18	@, tmp239, tmp235, <variable>.pcm_enabled_flag,
	mov	r2, r7	@, PicMsgSlotPhy
	orr	r3, r3, ip, asl #21	@, tmp253, tmp250, <variable>.amp_enabled_flag,
	orr	lr, r8, r3	@ tmp.448, tmp239, tmp253
	str	lr, [r5, #0]	@ tmp.448,* D.38984
	ldr	r3, [r5, #0]	@,* D.38984
	bl	dprint_vfmw	@
	ldr	r3, [r4, #24]	@ D.39031, <variable>.ThisPoc
	movw	ip, #6420	@ tmp311,
	str	r3, [r5, #4]	@ D.39031,
	ldr	r0, [r4, #36]	@ <variable>.max_transform_hierarchy_depth_inter, <variable>.max_transform_hierarchy_depth_inter
	ldr	r1, [r4, #28]	@ <variable>.log2_parallel_merge_level_minus2, <variable>.log2_parallel_merge_level_minus2
	ldr	r2, [r4, #68]	@ <variable>.CtbLog2SizeY, <variable>.CtbLog2SizeY
	mov	r8, r0, asl #24	@ tmp258, <variable>.max_transform_hierarchy_depth_inter,
	ldr	r0, [r4, #40]	@ <variable>.max_transform_hierarchy_depth_intra, <variable>.max_transform_hierarchy_depth_intra
	orr	r3, r8, r1, asl #29	@, tmp260, tmp258, <variable>.log2_parallel_merge_level_minus2,
	ldr	r1, [r4, #44]	@ <variable>.Log2MinIpcmCbSizeY, <variable>.Log2MinIpcmCbSizeY
	orr	r8, r3, r2	@ tmp261, tmp260, <variable>.CtbLog2SizeY
	ldr	r2, [r4, #48]	@ <variable>.Log2MaxIpcmCbSizeY, <variable>.Log2MaxIpcmCbSizeY
	orr	r3, r8, r0, asl #21	@, tmp265, tmp261, <variable>.max_transform_hierarchy_depth_intra,
	ldr	r0, [r4, #52]	@ <variable>.Log2MinTrafoSize, <variable>.Log2MinTrafoSize
	orr	r8, r3, r1, asl #18	@, tmp268, tmp265, <variable>.Log2MinIpcmCbSizeY,
	ldr	r1, [r4, #56]	@ <variable>.Log2MaxTrafoSize, <variable>.Log2MaxTrafoSize
	orr	r3, r8, r2, asl #15	@, tmp271, tmp268, <variable>.Log2MaxIpcmCbSizeY,
	ldr	r2, [r4, #60]	@ <variable>.MaxCuDepth, <variable>.MaxCuDepth
	orr	r8, r3, r0, asl #12	@, tmp274, tmp271, <variable>.Log2MinTrafoSize,
	ldr	r0, [r4, #64]	@ <variable>.Log2MinCbSizeY, <variable>.Log2MinCbSizeY
	orr	r3, r8, r1, asl #9	@, tmp277, tmp274, <variable>.Log2MaxTrafoSize,
	ldrb	r1, [r4, #32]	@ zero_extendqisi2	@ <variable>.weighted_bipred_flag, <variable>.weighted_bipred_flag
	orr	r8, r3, r2, asl #6	@, tmp280, tmp277, <variable>.MaxCuDepth,
	ldrb	r2, [r4, #33]	@ zero_extendqisi2	@ <variable>.weighted_pred_flag, <variable>.weighted_pred_flag
	orr	r3, r8, r0, asl #3	@, tmp283, tmp280, <variable>.Log2MinCbSizeY,
	orr	r8, r3, r1, asl #28	@, tmp286, tmp283, <variable>.weighted_bipred_flag,
	orr	r3, r8, r2, asl #27	@, tmp.1278, tmp286, <variable>.weighted_pred_flag,
	str	r3, [r5, #8]	@ tmp.1278,
	ldr	r0, [r4, #76]	@ <variable>.QpBdOffsetY, <variable>.QpBdOffsetY
	ldr	r1, [r4, #72]	@ <variable>.QpBdOffsetC, <variable>.QpBdOffsetC
	ldr	r2, [r4, #92]	@ <variable>.BitDepthY, <variable>.BitDepthY
	mov	r8, r0, asl #16	@ tmp291, <variable>.QpBdOffsetY,
	ldr	r0, [r4, #80]	@ <variable>.PcmBitDepthC, <variable>.PcmBitDepthC
	orr	r3, r8, r1, asl #22	@, tmp293, tmp291, <variable>.QpBdOffsetC,
	ldr	r1, [r4, #84]	@ <variable>.PcmBitDepthY, <variable>.PcmBitDepthY
	orr	r8, r3, r2	@ tmp294, tmp293, <variable>.BitDepthY
	ldr	r2, [r4, #88]	@ <variable>.BitDepthC, <variable>.BitDepthC
	orr	r3, r8, r0, asl #12	@, tmp298, tmp294, <variable>.PcmBitDepthC,
	orr	r8, r3, r1, asl #8	@, tmp301, tmp298, <variable>.PcmBitDepthY,
	orr	r0, r8, r2, asl #4	@, tmp.1280, tmp301, <variable>.BitDepthC,
	str	r0, [r5, #12]	@ tmp.1280,
	ldr	r3, [r6, #1084]	@ D.39088, <variable>.sed_top_phy_addr
	str	r3, [r5, #16]	@ D.39088,
	ldr	r8, [r6, #1088]	@ D.39090, <variable>.pmv_top_phy_addr
	str	r8, [r5, #20]	@ D.39090,
	ldr	r2, [r4, #1284]	@ <variable>.CurrPicPmvIdc, <variable>.CurrPicPmvIdc
	add	r1, r4, r2, asl #2	@, tmp309, pParam, <variable>.CurrPicPmvIdc,
	ldr	r0, [r1, #1580]	@ tmp.1282, <variable>.PmvPhyAddr
	str	r0, [r5, #24]	@ tmp.1282,
	ldr	r3, [r6, #1096]	@ D.39094, <variable>.rcn_top_phy_addr
	str	r3, [r5, #28]	@ D.39094,
	ldr	r3, [r4, ip]	@ i.1285, <variable>.ApcSize
	cmp	r3, #0	@ i.1285,
	beq	.L178	@,
	add	r1, r4, #6336	@ ivtmp.1272, pParam,
	add	r0, r5, #32	@ ivtmp.1275, D.38984,
	add	r1, r1, #20	@ ivtmp.1272, ivtmp.1272,
	mov	r2, #0	@ i,
.L177:
	ldr	lr, [r1], #4	@ tmp316, <variable>.Apc2Idc
	add	r2, r2, #1	@ i, i,
	add	r8, lr, #328	@ tmp315, tmp316,
	add	r3, r8, #2	@ tmp315, tmp315,
	ldr	lr, [r4, r3, asl #2]	@ tmp.1284, <variable>.ImgPhyAddr
	str	lr, [r0], #4	@ tmp.1284,
	ldr	r3, [r4, ip]	@ i.1285, <variable>.ApcSize
	cmp	r3, r2	@ i.1285, i
	bhi	.L177	@,
	cmp	r3, #15	@ i.1285,
	bhi	.L179	@,
.L178:
	movw	ip, #6356	@ tmp370,
	add	r2, r3, #8	@ tmp312, i.1285,
	ldr	r0, [r4, ip]	@ <variable>.Apc2Idc, <variable>.Apc2Idc
	add	r1, r3, #1	@ i.1285, i.1285,
	add	r2, r5, r2, asl #2	@, ivtmp.1268, D.38984, tmp312,
	cmp	r1, #15	@ i.1285,
	add	r8, r0, #328	@ tmp319, <variable>.Apc2Idc,
	rsb	r3, r3, #15	@ tmp372, i.1285,
	add	lr, r8, #2	@ tmp319, tmp319,
	and	r3, r3, #1	@ tmp373, tmp372,
	ldr	r0, [r4, lr, asl #2]	@ tmp.1287, <variable>.ImgPhyAddr
	str	r0, [r2], #4	@ tmp.1287,
	bhi	.L179	@,
	cmp	r3, #0	@ tmp373,
	beq	.L176	@,
	ldr	lr, [r4, ip]	@ <variable>.Apc2Idc, <variable>.Apc2Idc
	add	r1, r1, #1	@ i.1285, i.1285,
	cmp	r1, #15	@ i.1285,
	add	r3, lr, #328	@ tmp393, <variable>.Apc2Idc,
	add	r8, r3, #2	@ tmp393, tmp393,
	ldr	r0, [r4, r8, asl #2]	@ tmp.1287, <variable>.ImgPhyAddr
	str	r0, [r2], #4	@ tmp.1287,
	bhi	.L179	@,
.L176:
	ldr	r8, [r4, ip]	@ <variable>.Apc2Idc, <variable>.Apc2Idc
	mov	r3, r2	@ tmp375, ivtmp.1268
	add	r1, r1, #2	@ i.1285, i.1285,
	add	r0, r8, #328	@ tmp381, <variable>.Apc2Idc,
	cmp	r1, #15	@ i.1285,
	add	lr, r0, #2	@ tmp381, tmp381,
	ldr	r8, [r4, lr, asl #2]	@ tmp.1287, <variable>.ImgPhyAddr
	str	r8, [r3], #4	@ tmp.1287,
	ldr	r0, [r4, ip]	@ <variable>.Apc2Idc, <variable>.Apc2Idc
	add	lr, r0, #328	@ tmp388, <variable>.Apc2Idc,
	add	r8, lr, #2	@ tmp388, tmp388,
	ldr	r0, [r4, r8, asl #2]	@ tmp.1287, <variable>.ImgPhyAddr
	str	r0, [r2, #4]	@ tmp.1287,
	add	r2, r3, #4	@ ivtmp.1268, tmp375,
	bls	.L176	@,
.L179:
	ldr	ip, [r6, #1100]	@ D.39104, <variable>.mn_phy_addr
	mov	r0, r4	@, pParam
	mov	r1, r6	@, pHwMem
	str	ip, [r5, #100]	@ D.39104,
	ldr	r8, [r4, #120]	@ tmp.1296, <variable>.Apc2PocTable
	str	r8, [r5, #104]	@ tmp.1296,
	ldr	lr, [r4, #124]	@ tmp.1300, <variable>.Apc2PocTable
	str	lr, [r5, #108]	@ tmp.1300,
	ldr	r2, [r4, #128]	@ tmp.1304, <variable>.Apc2PocTable
	str	r2, [r5, #112]	@ tmp.1304,
	ldr	r3, [r4, #132]	@ tmp.1308, <variable>.Apc2PocTable
	str	r3, [r5, #116]	@ tmp.1308,
	ldr	ip, [r4, #136]	@ tmp.1312, <variable>.Apc2PocTable
	str	ip, [r5, #120]	@ tmp.1312,
	ldr	r8, [r4, #140]	@ tmp.1316, <variable>.Apc2PocTable
	str	r8, [r5, #124]	@ tmp.1316,
	ldr	lr, [r4, #144]	@ tmp.1320, <variable>.Apc2PocTable
	str	lr, [r5, #128]	@ tmp.1320,
	ldr	r2, [r4, #148]	@ tmp.1324, <variable>.Apc2PocTable
	str	r2, [r5, #132]	@ tmp.1324,
	ldr	r3, [r4, #152]	@ tmp.1328, <variable>.Apc2PocTable
	str	r3, [r5, #136]	@ tmp.1328,
	ldr	ip, [r4, #156]	@ tmp.1332, <variable>.Apc2PocTable
	str	ip, [r5, #140]	@ tmp.1332,
	ldr	r8, [r4, #160]	@ tmp.1336, <variable>.Apc2PocTable
	str	r8, [r5, #144]	@ tmp.1336,
	ldr	lr, [r4, #164]	@ tmp.1340, <variable>.Apc2PocTable
	str	lr, [r5, #148]	@ tmp.1340,
	ldr	r2, [r4, #168]	@ tmp.1344, <variable>.Apc2PocTable
	str	r2, [r5, #152]	@ tmp.1344,
	ldr	r3, [r4, #172]	@ tmp.1349, <variable>.Apc2PocTable
	str	r3, [r5, #156]	@ tmp.1349,
	ldr	ip, [r4, #176]	@ tmp.1353, <variable>.Apc2PocTable
	str	ip, [r5, #160]	@ tmp.1353,
	ldr	r8, [r4, #180]	@ tmp.1289, <variable>.Apc2PocTable
	str	r8, [r5, #164]	@ tmp.1289,
	ldr	lr, [r6, #1092]	@ D.39110, <variable>.pmv_left_phy_addr
	str	lr, [r5, #172]	@ D.39110,
	ldr	r2, [r4, #184]	@ <variable>.pic_height_in_luma_samples, <variable>.pic_height_in_luma_samples
	ldr	r3, [r4, #188]	@ <variable>.pic_width_in_luma_samples, <variable>.pic_width_in_luma_samples
	orr	ip, r3, r2, asl #16	@, tmp.1291, <variable>.pic_width_in_luma_samples, <variable>.pic_height_in_luma_samples,
	str	ip, [r5, #216]	@ tmp.1291,
	bl	HEVC_WriteTileInfo	@
	subs	r8, r0, #0	@ D.39116,
	bne	.L190	@,
	ldr	lr, [r6, #1104]	@ D.39120, <variable>.tile_segment_info_phy_addr
	mov	r1, r5	@, D.38984
	mov	r0, #64	@,
	str	lr, [r5, #220]	@ D.39120,
	ldr	ip, [r6, #1116]	@ D.39122, <variable>.sao_left_phy_addr
	str	ip, [r5, #224]	@ D.39122,
	ldr	r2, [r6, #1108]	@ D.39124, <variable>.dblk_left_phy_addr
	str	r2, [r5, #228]	@ D.39124,
	ldr	r3, [r6, #1120]	@ D.39126, <variable>.sao_top_phy_addr
	str	r3, [r5, #232]	@ D.39126,
	ldr	lr, [r6, #1112]	@ D.39128, <variable>.dblk_top_phy_addr
	str	lr, [r5, #236]	@ D.39128,
	ldr	ip, [r4, #220]	@ <variable>.Log2MinCuQpDeltaSize, <variable>.Log2MinCuQpDeltaSize
	ldr	r6, [r4, #224]	@ <variable>.diff_cu_qp_delta_depth, <variable>.diff_cu_qp_delta_depth
	ldr	r3, [r4, #236]	@ <variable>.pps_cr_qp_offset, <variable>.pps_cr_qp_offset
	mov	r2, ip, asl #16	@ tmp329, <variable>.Log2MinCuQpDeltaSize,
	ldrb	ip, [r4, #212]	@ zero_extendqisi2	@ <variable>.loop_filter_across_tiles_enabled_flag, <variable>.loop_filter_across_tiles_enabled_flag
	orr	lr, r2, r6, asl #13	@, tmp331, tmp329, <variable>.diff_cu_qp_delta_depth,
	ldrb	r2, [r4, #213]	@ zero_extendqisi2	@ <variable>.transform_skip_enabled_flag, <variable>.transform_skip_enabled_flag
	and	r6, r3, #31	@ tmp332, <variable>.pps_cr_qp_offset,
	orr	r3, lr, r6	@ tmp334, tmp331, tmp332
	ldrb	lr, [r4, #214]	@ zero_extendqisi2	@ <variable>.sign_data_hiding_enabled_flag, <variable>.sign_data_hiding_enabled_flag
	orr	r6, r3, ip, asl #24	@, tmp337, tmp334, <variable>.loop_filter_across_tiles_enabled_flag,
	ldrb	ip, [r4, #215]	@ zero_extendqisi2	@ <variable>.entropy_coding_sync_enabled_flag, <variable>.entropy_coding_sync_enabled_flag
	orr	r3, r6, r2, asl #23	@, tmp340, tmp337, <variable>.transform_skip_enabled_flag,
	ldrb	r2, [r4, #216]	@ zero_extendqisi2	@ <variable>.uniform_spacing_flag, <variable>.uniform_spacing_flag
	orr	r6, r3, lr, asl #22	@, tmp343, tmp340, <variable>.sign_data_hiding_enabled_flag,
	ldrb	lr, [r4, #217]	@ zero_extendqisi2	@ <variable>.tiles_enabled_flag, <variable>.tiles_enabled_flag
	orr	r3, r6, ip, asl #21	@, tmp346, tmp343, <variable>.entropy_coding_sync_enabled_flag,
	ldrb	r6, [r4, #228]	@ zero_extendqisi2	@ <variable>.cu_qp_delta_enabled_flag, <variable>.cu_qp_delta_enabled_flag
	ldrb	ip, [r4, #229]	@ zero_extendqisi2	@ <variable>.transquant_bypass_enabled_flag, <variable>.transquant_bypass_enabled_flag
	orr	r3, r3, r2, asl #20	@, tmp349, tmp346, <variable>.uniform_spacing_flag,
	orr	lr, r3, lr, asl #19	@, tmp352, tmp349, <variable>.tiles_enabled_flag,
	ldr	r2, [r4, #232]	@ <variable>.pps_cb_qp_offset, <variable>.pps_cb_qp_offset
	ldrb	r3, [r4, #230]	@ zero_extendqisi2	@ <variable>.constrained_intra_pred_flag, <variable>.constrained_intra_pred_flag
	orr	lr, lr, r6, asl #12	@, tmp355, tmp352, <variable>.cu_qp_delta_enabled_flag,
	orr	ip, lr, ip, asl #11	@, tmp358, tmp355, <variable>.transquant_bypass_enabled_flag,
	and	lr, r2, #31	@ tmp362, <variable>.pps_cb_qp_offset,
	orr	r3, ip, r3, asl #10	@, tmp361, tmp358, <variable>.constrained_intra_pred_flag,
	orr	ip, r3, lr, asl #5	@, D.39177, tmp361, tmp362,
	str	ip, [r5, #240]	@ D.39177,
	ldr	r2, [r4, #240]	@ <variable>.num_tile_rows_minus1, <variable>.num_tile_rows_minus1
	ldr	lr, [r4, #244]	@ <variable>.num_tile_columns_minus1, <variable>.num_tile_columns_minus1
	orr	r3, lr, r2, asl #16	@, D.39182, <variable>.num_tile_columns_minus1, <variable>.num_tile_rows_minus1,
	str	r3, [r5, #244]	@ D.39182,
	str	r9, [r5, #252]	@ FstSlcMsgSlotPhy,
	bl	HEVC_GetVirAddr	@
	mov	r1, r7	@, PicMsgSlotPhy
	mov	r5, r0	@ pSlot,
	mov	r0, #64	@,
	bl	HEVC_GetPhyAddr	@
	mov	r3, r5	@, pSlot
	mov	r1, #256	@,
	mov	r2, r0	@ pSlot_phy,
	add	r0, r4, #252	@, pParam,
	bl	HEVC_WriteQmatrix	@
	mov	r0, r8	@ D.38988, D.39116
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L190:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC16	@,
	movt	r1, #:upper16:.LC16	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38988,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L189:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L191	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC13	@,
	movt	r3, #:upper16:.LC13	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38988,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L192:
	.align	2
.L191:
	.word	.LANCHOR0+2064
	.fnend
	.size	HEVCHAL_V300R001_SetPicMsg, .-HEVCHAL_V300R001_SetPicMsg
	.align	2
	.global	HEVCHAL_V300R001_StartDec
	.type	HEVCHAL_V300R001_StartDec, %function
HEVCHAL_V300R001_StartDec:
	.fnstart
.LFB1538:
	@ args = 0, pretend = 0, frame = 32
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
	cmp	r1, #1	@ VdhId,
	mov	ip, r1	@ VdhId, VdhId
	mov	r6, r0	@ pParam, pParam
	bls	.L234	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC17	@,
	movt	r1, #:upper16:.LC17	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
.L196:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L234:
	beq	.L242	@,
	cmp	r0, #0	@ pParam,
	beq	.L243	@,
	movw	r0, #6420	@ tmp184,
	ldr	r3, [r6, r0]	@ <variable>.ApcSize, <variable>.ApcSize
	cmp	r3, #16	@ <variable>.ApcSize,
	bhi	.L244	@,
	movw	r7, #:lower16:g_HwMem	@ tmp313,
	movt	r7, #:upper16:g_HwMem	@ tmp313,
	ldr	r1, [r7, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	cmp	r1, #0	@ <variable>.pVdmRegVirAddr,
	beq	.L245	@,
.L200:
	mov	r2, #0	@,
	mov	r0, r6	@, pParam
	movw	r1, #:lower16:g_HwMem	@,
	movt	r1, #:upper16:g_HwMem	@,
	bl	HEVCHAL_V300R001_CfgVdmReg	@
	ldr	r3, [r7, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mvn	r4, #0	@ tmp202,
	mvn	r8, #1	@ tmp205,
	mov	r0, r6	@, pParam
	movw	r1, #:lower16:g_HwMem	@,
	str	r4, [r3, #32]	@ tmp202,
	movt	r1, #:upper16:g_HwMem	@,
	ldr	ip, [r7, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r8, [ip, #36]	@ tmp205,
	ldr	r3, [r7, #52]	@, <variable>.MsgSlotAddr
	ldr	r2, [r7, #48]	@, <variable>.MsgSlotAddr
	bl	HEVCHAL_V300R001_SetPicMsg	@
	movw	r3, #6428	@ tmp211,
	ldr	r8, [r6, r3]	@ pSlicePara, <variable>.pFirstSlice
	cmp	r8, #0	@ pSlicePara,
	beq	.L246	@,
	ldr	r4, [r8, #92]	@ temp.1403, <variable>.SliceSegmentTileAddress
	cmp	r4, #0	@ temp.1403,
	streq	r4, [fp, #-48]	@ temp.1403, %sfp
	bne	.L247	@,
.L204:
	ldr	r5, [r6, #20]	@ <variable>.PicWidthInCtbsYMinus1, <variable>.PicWidthInCtbsYMinus1
	mov	r1, #0	@ pre_end_ctb_in_slice_tile,
	ldr	r2, [r6, #16]	@ <variable>.PicHightInCtbsYMinus1, <variable>.PicHightInCtbsYMinus1
	movw	sl, #6424	@ tmp314,
	add	r3, r5, #1	@ tmp240, <variable>.PicWidthInCtbsYMinus1,
	ldr	ip, [fp, #-48]	@, %sfp
	mov	r5, r1	@ i, pre_end_ctb_in_slice_tile
	str	r1, [fp, #-60]	@ pre_end_ctb_in_slice_tile, %sfp
	mla	r0, r2, r3, r3	@ tmp242, <variable>.PicHightInCtbsYMinus1, tmp240, tmp240
	add	lr, ip, #5	@,,
	str	lr, [fp, #-52]	@, %sfp
	sub	r2, r0, #1	@, tmp242,
	str	r2, [fp, #-56]	@, %sfp
.L208:
	ldr	r0, [r6, sl]	@ prephitmp.1377, <variable>.NumSlicePara
	cmp	r5, r0	@ i, prephitmp.1377
	bge	.L226	@,
	ldr	r9, [fp, #-48]	@, %sfp
	cmp	r8, #0	@ pTargetSlicePara.1399,
	add	r2, r9, r5	@ tmp244,, i
	ldr	r9, [fp, #-52]	@, %sfp
	add	r3, r2, #12	@ tmp245, tmp244,
	add	lr, r5, r9	@ D.39824, i,
	add	ip, lr, #8	@ tmp247, D.39824,
	ldr	r2, [r7, r3, asl #2]	@ prev_slcmsg_phy.1404, <variable>.MsgSlotAddr
	ldr	r3, [r7, ip, asl #2]	@ cur_slcmsg_phy.1405, <variable>.MsgSlotAddr
	beq	.L248	@,
	ldr	ip, [r8, #92]	@ D.39772, <variable>.SliceSegmentTileAddress
	cmp	ip, r1	@ D.39772, pre_end_ctb_in_slice_tile
	movcs	r4, #0	@, tmp258
	movcc	r4, #1	@, tmp258
	cmp	r5, #0	@ i,
	movle	r4, #0	@, tmp258,
	cmp	r4, #0	@ tmp258,
	bne	.L249	@,
	add	r5, r5, #1	@ j, i,
	cmp	r0, r5	@ prephitmp.1377, j
	movle	r4, r8	@ pTargetSlicePara, pTargetSlicePara.1399
	ble	.L212	@,
	ldr	r4, [r8, #1292]	@ pTargetSlicePara, <variable>.pNextSlice
	cmp	r4, #0	@ pTargetSlicePara,
	beq	.L213	@,
	ldr	r1, [r4, #92]	@ <variable>.SliceSegmentTileAddress, <variable>.SliceSegmentTileAddress
	cmp	ip, r1	@ D.39772, <variable>.SliceSegmentTileAddress
	bcc	.L212	@,
	mvn	r1, r5	@ tmp321, j
	add	r1, r1, r0	@ tmp320, tmp321, prephitmp.1377
	tst	r1, #1	@ tmp320,
	bne	.L236	@,
	b	.L233	@
.L250:
	ldr	r1, [r4, #92]	@ <variable>.SliceSegmentTileAddress, <variable>.SliceSegmentTileAddress
	cmp	ip, r1	@ D.39772, <variable>.SliceSegmentTileAddress
	bcc	.L212	@,
.L233:
	add	r5, r5, #1	@ j, j,
	cmp	r0, r5	@ prephitmp.1377, j
	ble	.L212	@,
	ldr	r4, [r4, #1292]	@ pTargetSlicePara, <variable>.pNextSlice
	cmp	r4, #0	@ pTargetSlicePara,
	beq	.L213	@,
	ldr	r1, [r4, #92]	@ <variable>.SliceSegmentTileAddress, <variable>.SliceSegmentTileAddress
	cmp	ip, r1	@ D.39772, <variable>.SliceSegmentTileAddress
	bcc	.L212	@,
.L236:
	ldr	r4, [r4, #1292]	@ pTargetSlicePara, <variable>.pNextSlice
	add	r5, r5, #1	@ j, j,
	cmp	r4, #0	@ pTargetSlicePara,
	bne	.L250	@,
.L213:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC26	@,
	ldr	r2, .L257	@,
	movt	r1, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L212:
	cmp	r5, r0	@ j, prephitmp.1377
	beq	.L216	@,
	cmp	lr, #209	@ D.39824,
	beq	.L216	@,
	ldr	lr, [r4, #92]	@ <variable>.SliceSegmentTileAddress, <variable>.SliceSegmentTileAddress
	subs	lr, lr, #1	@ end_ctb_in_slice_tile.1407, <variable>.SliceSegmentTileAddress,
	bmi	.L251	@,
	ldrb	r0, [r6, #217]	@ zero_extendqisi2	@ <variable>.tiles_enabled_flag, <variable>.tiles_enabled_flag
	ldr	r9, [fp, #-52]	@, %sfp
	cmp	r0, #0	@ <variable>.tiles_enabled_flag,
	ldr	r1, [fp, #-56]	@, %sfp
	addne	r0, lr, #1664	@ tmp273, end_ctb_in_slice_tile.1407,
	streq	lr, [fp, #-64]	@ end_ctb_in_slice_tile.1407, %sfp
	add	r9, r5, r9	@, j,
	ldrne	r0, [r6, r0, asl #2]	@, <variable>.TsToRsMap
	str	r9, [fp, #-68]	@, %sfp
	strne	r0, [fp, #-64]	@, %sfp
	cmp	r1, lr	@, end_ctb_in_slice_tile.1407
	movge	r0, #0	@, tmp280
	movlt	r0, #1	@, tmp280
	ldr	r9, [fp, #-64]	@, %sfp
	cmp	r9, r1	@,
	orrgt	r0, r0, #1	@,, tmp283, tmp280
	ldr	r9, [fp, #-68]	@, %sfp
	cmp	r0, #0	@ tmp283,
	add	r1, r9, #8	@ tmp276,,
	ldr	r9, [r7, r1, asl #2]	@ next_slcmsg_phy.1411, <variable>.MsgSlotAddr
	bne	.L252	@,
.L218:
	cmp	ip, lr	@ D.39772, end_ctb_in_slice_tile.1407
	str	lr, [r8, #556]	@ end_ctb_in_slice_tile.1407, <variable>.end_ctb_in_slice_tile
	bhi	.L253	@,
	ldr	r0, [r6, sl]	@ <variable>.NumSlicePara, <variable>.NumSlicePara
	sub	r1, r5, #1	@ tmp289, j,
	sub	r0, r0, #1	@ tmp287, <variable>.NumSlicePara,
	cmp	r0, r1	@ tmp287, tmp289
	mov	r0, r6	@, pParam
	moveq	r1, #0	@,
	streq	r1, [r8, #1292]	@, <variable>.pNextSlice
	str	r2, [sp, #0]	@ prev_slcmsg_phy.1404,
	movw	r1, #:lower16:g_HwMem	@,
	str	r9, [sp, #4]	@ next_slcmsg_phy.1411,
	movt	r1, #:upper16:g_HwMem	@,
	ldr	r2, [r8, #80]	@, <variable>.slice_segment_address
	str	ip, [sp, #12]	@ D.39772,
	ldr	ip, [fp, #-64]	@, %sfp
	str	r2, [sp, #8]	@,
	mov	r2, r8	@, pTargetSlicePara.1399
	str	lr, [sp, #20]	@ end_ctb_in_slice_tile.1407,
	str	ip, [sp, #16]	@,
	bl	HEVCHAL_V300R001_SetSliceMsg	@
	cmp	r0, #0	@,
	bne	.L254	@,
	ldr	lr, [fp, #-60]	@, %sfp
	cmp	r9, #0	@ next_slcmsg_phy.1411,
	add	r3, lr, #1	@,,
	str	r3, [fp, #-60]	@, %sfp
	ldr	r1, [r8, #556]	@ pre_end_ctb_in_slice_tile, <variable>.end_ctb_in_slice_tile
	beq	.L255	@,
	mov	r8, r4	@ pTargetSlicePara.1399, pTargetSlicePara
	b	.L208	@
.L216:
	mov	r0, #0	@,
	str	r0, [r8, #1292]	@, <variable>.pNextSlice
	ldr	r9, [fp, #-56]	@, %sfp
	str	r9, [fp, #-64]	@, %sfp
	mov	lr, r9	@ end_ctb_in_slice_tile.1407,
	mov	r9, r0	@ next_slcmsg_phy.1411,
	b	.L218	@
.L247:
	ldrb	sl, [r6, #217]	@ zero_extendqisi2	@ <variable>.tiles_enabled_flag, <variable>.tiles_enabled_flag
	sub	lr, r4, #1	@ end_ctb_in_slice_tile, temp.1403,
	ldr	r0, [r8, #0]	@, <variable>.valid_bitlen
	mov	ip, #0	@ tmp220,
	cmp	sl, #0	@ <variable>.tiles_enabled_flag,
	movw	r1, #:lower16:g_HwMem	@,
	addne	r3, lr, #1664	@ tmp218, end_ctb_in_slice_tile,
	movt	r1, #:upper16:g_HwMem	@,
	movne	r2, #6656	@ tmp217,
	moveq	r9, lr	@ end_ctb_in_slice_raster, end_ctb_in_slice_tile
	ldrne	sl, [r6, r2]	@ slice_segment_address, <variable>.TsToRsMap
	ldrne	r9, [r6, r3, asl #2]	@ end_ctb_in_slice_raster, <variable>.TsToRsMap
	str	r0, [fp, #-76]	@, %sfp
	mov	r0, r6	@, pParam
	ldr	r5, [r8, #4]	@, <variable>.valid_bitlen
	str	r5, [fp, #-72]	@, %sfp
	mov	r5, #1	@ tmp219,
	ldr	r2, [r8, #8]	@, <variable>.bitsoffset
	stmia	r8, {r5, ip}	@ phole stm
	str	r2, [fp, #-68]	@, %sfp
	mov	r2, r8	@, pSlicePara
	ldr	r3, [r8, #12]	@, <variable>.bitsoffset
	str	ip, [r8, #8]	@ tmp220, <variable>.bitsoffset
	str	r3, [fp, #-64]	@, %sfp
	ldr	r3, [r8, #16]	@, <variable>.bytespos
	str	ip, [r8, #12]	@ tmp220, <variable>.bitsoffset
	str	r3, [fp, #-60]	@, %sfp
	ldr	r3, [r8, #20]	@, <variable>.bytespos
	str	r3, [fp, #-56]	@, %sfp
	ldr	r3, [r6, #1308]	@, <variable>.stream_base_addr
	str	ip, [r8, #20]	@ tmp220, <variable>.bytespos
	str	r3, [r8, #16]	@, <variable>.bytespos
	str	sl, [sp, #8]	@ slice_segment_address,
	ldr	sl, [r7, #48]	@, <variable>.MsgSlotAddr
	ldr	r3, [r7, #52]	@, <variable>.MsgSlotAddr
	str	ip, [sp, #12]	@ tmp220,
	str	sl, [sp, #0]	@,
	ldr	sl, [r7, #56]	@, <variable>.MsgSlotAddr
	str	r9, [sp, #16]	@ end_ctb_in_slice_raster,
	str	lr, [sp, #20]	@ end_ctb_in_slice_tile,
	str	sl, [sp, #4]	@,
	bl	HEVCHAL_V300R001_SetSliceMsg	@
	cmp	r0, #0	@,
	bne	.L256	@,
	ldr	r3, [fp, #-56]	@, %sfp
	movw	r1, #6428	@ tmp237,
	str	r4, [r8, #92]	@ temp.1403, <variable>.SliceSegmentTileAddress
	str	r3, [r8, #20]	@, <variable>.bytespos
	ldr	sl, [fp, #-76]	@, %sfp
	str	r5, [fp, #-48]	@ tmp219, %sfp
	str	sl, [r8, #0]	@, <variable>.valid_bitlen
	ldr	ip, [fp, #-72]	@, %sfp
	str	ip, [r8, #4]	@, <variable>.valid_bitlen
	ldr	r9, [fp, #-68]	@, %sfp
	str	r9, [r8, #8]	@, <variable>.bitsoffset
	ldr	r9, [fp, #-64]	@, %sfp
	str	r9, [r8, #12]	@, <variable>.bitsoffset
	ldr	lr, [fp, #-60]	@, %sfp
	str	lr, [r8, #16]	@, <variable>.bytespos
	ldr	r8, [r6, r1]	@ pSlicePara, <variable>.pFirstSlice
	b	.L204	@
.L245:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r2, r0, #0	@ D.39746,
	strne	r2, [r7, #0]	@ D.39746, <variable>.pVdmRegVirAddr
	bne	.L200	@,
	movw	r1, #:lower16:.LC21	@,
	ldr	r2, .L257	@,
	movt	r1, #:upper16:.LC21	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L255:
	movw	ip, #6424	@ tmp297,
	ldr	r0, [r6, ip]	@ prephitmp.1377, <variable>.NumSlicePara
.L226:
	ldr	r2, [fp, #-60]	@, %sfp
	cmp	r2, #0	@,
	cmpgt	r0, #0	@, prephitmp.1377,
	ble	.L228	@,
	ldr	r9, [fp, #-48]	@, %sfp
	add	r3, r0, r9	@ tmp307, prephitmp.1377,
	add	r1, r3, #12	@ tmp308, tmp307,
	ldr	r0, [r7, r1, asl #2]	@, <variable>.MsgSlotAddr
	bl	HEVCHAL_V300R001_CutSliceChain	@
	mov	r0, #0	@ D.39733,
	b	.L196	@
.L242:
	mov	r3, r1	@, VdhId
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC18	@,
	ldr	r2, .L257	@,
	movt	r1, #:upper16:.LC18	@,
	str	ip, [sp, #0]	@ VdhId,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L249:
	mov	r3, r1	@, pre_end_ctb_in_slice_tile
	mov	r2, ip	@, D.39772
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC25	@,
	movt	r1, #:upper16:.LC25	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L248:
	mov	r3, r5	@, i
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC24	@,
	ldr	r2, .L257	@,
	movt	r1, #:upper16:.LC24	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L252:
	ldr	sl, [fp, #-56]	@, %sfp
	mov	r3, lr	@, end_ctb_in_slice_tile.1407
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC28	@,
	movt	r1, #:upper16:.LC28	@,
	str	sl, [sp, #0]	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L253:
	mov	r2, ip	@, D.39772
	mov	r3, lr	@, end_ctb_in_slice_tile.1407
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC29	@,
	movt	r1, #:upper16:.LC29	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L254:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC30	@,
	ldr	r2, .L257	@,
	movt	r1, #:upper16:.LC30	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L244:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L257	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC20	@,
	movt	r3, #:upper16:.LC20	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L251:
	mov	r3, lr	@, end_ctb_in_slice_tile.1407
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC27	@,
	ldr	r2, .L257	@,
	movt	r1, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L256:
	mov	r0, r5	@, tmp219
	movw	r1, #:lower16:.LC23	@,
	ldr	r2, .L257	@,
	movt	r1, #:upper16:.LC23	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L228:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC31	@,
	movt	r1, #:upper16:.LC31	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L243:
	movw	r1, #:lower16:.LC2	@,
	ldr	r2, .L257	@,
	movt	r1, #:upper16:.LC2	@,
	movw	r3, #:lower16:.LC19	@,
	movt	r3, #:upper16:.LC19	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39733,
	b	.L196	@
.L246:
	mov	r0, r8	@, pSlicePara
	movw	r1, #:lower16:.LC22	@,
	ldr	r2, .L257	@,
	movt	r1, #:upper16:.LC22	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ D.39733, tmp202
	b	.L196	@
.L258:
	.align	2
.L257:
	.word	.LANCHOR0+2092
	.fnend
	.size	HEVCHAL_V300R001_StartDec, .-HEVCHAL_V300R001_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.38919, %object
	.size	__func__.38919, 19
__func__.38919:
	.ascii	"HEVC_WriteTileInfo\000"
	.space	1
	.type	__func__.38885, %object
	.size	__func__.38885, 31
__func__.38885:
	.ascii	"HEVCHAL_V300R001_CutSliceChain\000"
	.space	1
	.type	s_InitValue, %object
	.size	s_InitValue, 1920
s_InitValue:
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	153
	.word	200
	.word	139
	.word	141
	.word	157
	.word	154
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	184
	.word	-1
	.word	-1
	.word	-1
	.word	184
	.word	63
	.word	94
	.word	138
	.word	182
	.word	154
	.word	111
	.word	141
	.word	154
	.word	154
	.word	139
	.word	139
	.word	138
	.word	153
	.word	136
	.word	167
	.word	152
	.word	152
	.word	110
	.word	110
	.word	124
	.word	125
	.word	140
	.word	153
	.word	125
	.word	127
	.word	140
	.word	109
	.word	111
	.word	143
	.word	127
	.word	111
	.word	79
	.word	108
	.word	123
	.word	63
	.word	110
	.word	110
	.word	124
	.word	125
	.word	140
	.word	153
	.word	125
	.word	127
	.word	140
	.word	109
	.word	111
	.word	143
	.word	127
	.word	111
	.word	79
	.word	108
	.word	123
	.word	63
	.word	91
	.word	171
	.word	134
	.word	141
	.word	140
	.word	92
	.word	137
	.word	138
	.word	140
	.word	152
	.word	138
	.word	139
	.word	153
	.word	74
	.word	149
	.word	92
	.word	139
	.word	107
	.word	122
	.word	152
	.word	140
	.word	179
	.word	166
	.word	182
	.word	140
	.word	227
	.word	122
	.word	197
	.word	111
	.word	111
	.word	125
	.word	110
	.word	110
	.word	94
	.word	124
	.word	108
	.word	124
	.word	107
	.word	125
	.word	141
	.word	179
	.word	153
	.word	125
	.word	107
	.word	125
	.word	141
	.word	179
	.word	153
	.word	125
	.word	107
	.word	125
	.word	141
	.word	179
	.word	153
	.word	125
	.word	140
	.word	139
	.word	182
	.word	182
	.word	152
	.word	136
	.word	152
	.word	136
	.word	153
	.word	136
	.word	139
	.word	111
	.word	136
	.word	139
	.word	111
	.word	-1
	.word	153
	.word	138
	.word	138
	.word	-1
	.word	-1
	.word	79
	.word	110
	.word	122
	.word	95
	.word	79
	.word	63
	.word	31
	.word	31
	.word	153
	.word	153
	.word	168
	.word	140
	.word	198
	.word	-1
	.word	-1
	.word	-1
	.word	153
	.word	185
	.word	107
	.word	139
	.word	126
	.word	154
	.word	197
	.word	185
	.word	201
	.word	149
	.word	154
	.word	139
	.word	154
	.word	154
	.word	154
	.word	152
	.word	149
	.word	107
	.word	167
	.word	154
	.word	153
	.word	111
	.word	154
	.word	154
	.word	139
	.word	139
	.word	107
	.word	167
	.word	91
	.word	122
	.word	107
	.word	167
	.word	125
	.word	110
	.word	94
	.word	110
	.word	95
	.word	79
	.word	125
	.word	111
	.word	110
	.word	78
	.word	110
	.word	111
	.word	111
	.word	95
	.word	94
	.word	108
	.word	123
	.word	108
	.word	125
	.word	110
	.word	94
	.word	110
	.word	95
	.word	79
	.word	125
	.word	111
	.word	110
	.word	78
	.word	110
	.word	111
	.word	111
	.word	95
	.word	94
	.word	108
	.word	123
	.word	108
	.word	121
	.word	140
	.word	61
	.word	154
	.word	154
	.word	196
	.word	196
	.word	167
	.word	154
	.word	152
	.word	167
	.word	182
	.word	182
	.word	134
	.word	149
	.word	136
	.word	153
	.word	121
	.word	136
	.word	137
	.word	169
	.word	194
	.word	166
	.word	167
	.word	154
	.word	167
	.word	137
	.word	182
	.word	155
	.word	154
	.word	139
	.word	153
	.word	139
	.word	123
	.word	123
	.word	63
	.word	153
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	170
	.word	153
	.word	123
	.word	123
	.word	107
	.word	121
	.word	107
	.word	121
	.word	167
	.word	151
	.word	183
	.word	140
	.word	151
	.word	183
	.word	140
	.word	-1
	.word	124
	.word	138
	.word	94
	.word	-1
	.word	-1
	.word	79
	.word	154
	.word	137
	.word	95
	.word	79
	.word	63
	.word	31
	.word	31
	.word	153
	.word	153
	.word	168
	.word	169
	.word	198
	.word	-1
	.word	-1
	.word	-1
	.word	153
	.word	160
	.word	107
	.word	139
	.word	126
	.word	154
	.word	197
	.word	185
	.word	201
	.word	134
	.word	154
	.word	139
	.word	154
	.word	154
	.word	183
	.word	152
	.word	149
	.word	92
	.word	167
	.word	154
	.word	153
	.word	111
	.word	154
	.word	154
	.word	139
	.word	139
	.word	107
	.word	167
	.word	91
	.word	107
	.word	107
	.word	167
	.word	125
	.word	110
	.word	124
	.word	110
	.word	95
	.word	94
	.word	125
	.word	111
	.word	111
	.word	79
	.word	125
	.word	126
	.word	111
	.word	111
	.word	79
	.word	108
	.word	123
	.word	93
	.word	125
	.word	110
	.word	124
	.word	110
	.word	95
	.word	94
	.word	125
	.word	111
	.word	111
	.word	79
	.word	125
	.word	126
	.word	111
	.word	111
	.word	79
	.word	108
	.word	123
	.word	93
	.word	121
	.word	140
	.word	61
	.word	154
	.word	154
	.word	196
	.word	167
	.word	167
	.word	154
	.word	152
	.word	167
	.word	182
	.word	182
	.word	134
	.word	149
	.word	136
	.word	153
	.word	121
	.word	136
	.word	122
	.word	169
	.word	208
	.word	166
	.word	167
	.word	154
	.word	152
	.word	167
	.word	182
	.word	170
	.word	154
	.word	139
	.word	153
	.word	139
	.word	123
	.word	123
	.word	63
	.word	124
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	170
	.word	153
	.word	138
	.word	138
	.word	122
	.word	121
	.word	122
	.word	121
	.word	167
	.word	151
	.word	183
	.word	140
	.word	151
	.word	183
	.word	140
	.word	-1
	.word	224
	.word	167
	.word	122
	.word	-1
	.word	-1
	.type	__func__.38830, %object
	.size	__func__.38830, 18
__func__.38830:
	.ascii	"HEVCWriteCabacTab\000"
	.space	2
	.type	__func__.39507, %object
	.size	__func__.39507, 27
__func__.39507:
	.ascii	"HEVCHAL_V300R001_CfgVdmReg\000"
	.space	1
	.type	__func__.39215, %object
	.size	__func__.39215, 29
__func__.39215:
	.ascii	"HEVCHAL_V300R001_SetSliceMsg\000"
	.space	3
	.type	s_SliceTypeForPMV, %object
	.size	s_SliceTypeForPMV, 12
s_SliceTypeForPMV:
	.word	2
	.word	1
	.word	0
	.type	__func__.38971, %object
	.size	__func__.38971, 27
__func__.38971:
	.ascii	"HEVCHAL_V300R001_SetPicMsg\000"
	.space	1
	.type	__func__.39722, %object
	.size	__func__.39722, 26
__func__.39722:
	.ascii	"HEVCHAL_V300R001_StartDec\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"qmatrix[%d] = 0x%x\012\000"
.LC1:
	.ascii	"picmsg Dxx addr 0x%x = 0x%x\012\000"
	.space	3
.LC2:
	.ascii	"%s: %s\012\000"
.LC3:
	.ascii	"can not map slice segment info virtual address!\012"
	.ascii	"\000"
	.space	3
.LC4:
	.ascii	"can not map slice msg virtual address!\012\000"
.LC5:
	.ascii	"can not map mn virtual address!\012\000"
	.space	3
.LC6:
	.ascii	"HEVCWriteCabacTab return error.\012\000"
	.space	3
.LC7:
	.ascii	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000"
	.space	3
.LC8:
	.ascii	"AVM_ADDR = 0x%x\012\000"
	.space	3
.LC9:
	.ascii	"HEVC_VFMW_PRC_CACHE_TYPE = 0x%x\012\000"
	.space	3
.LC10:
	.ascii	"HEVCHAL_V300R001_SetSliceMsg can not map slice msg "
	.ascii	"virtual address!\012\000"
	.space	3
.LC11:
	.ascii	"slicemsg D[%d] addr 0x%x = 0x%x\012\000"
	.space	3
.LC12:
	.ascii	"%s FATAL: i=0, valid_bitlen=0\012\000"
	.space	1
.LC13:
	.ascii	"can not map down msg virtual address!\012\000"
	.space	1
.LC14:
	.ascii	"pic msg burst0:\012\000"
	.space	3
.LC15:
	.ascii	"picmsg D[0] addr 0x%x = 0x%x\012\000"
	.space	2
.LC16:
	.ascii	"HEVC_WriteTileInfo return error.\012\000"
	.space	2
.LC17:
	.ascii	"VdhId is wrong! HEVC4HAL_V200R003_StartDec\012\000"
.LC18:
	.ascii	"%s VdhId %d >= %d\012\000"
	.space	1
.LC19:
	.ascii	"pParam is null\012\000"
.LC20:
	.ascii	"FATAL: ApcSize > 16\012\000"
	.space	3
.LC21:
	.ascii	"%s vdm register virtual address not mapped, reset f"
	.ascii	"ailed!\012\000"
	.space	1
.LC22:
	.ascii	"%s pFirstSlice = NULL!\012\000"
.LC23:
	.ascii	"%s 0: set slice msg failed!\012\000"
	.space	3
.LC24:
	.ascii	"%s: i = %d, pSlicePara = NULL!\012\000"
.LC25:
	.ascii	"SliceSegmentTileAddress %d < pre_end_ctb_in_slice_t"
	.ascii	"ile %d\012\000"
	.space	1
.LC26:
	.ascii	"%s pTargetSlicePara is NULL!\012\000"
	.space	2
.LC27:
	.ascii	"%s end_ctb_in_slice_tile(%d) < 0\012\000"
	.space	2
.LC28:
	.ascii	"end_ctb_in_slice_raster(%d)/end_ctb_in_slice_tile(%"
	.ascii	"d) > pic_max_ctb(%d)\012\000"
	.space	3
.LC29:
	.ascii	"SliceSegmentTileAddress %d > end_ctb_in_slice_tile "
	.ascii	"%d\012\000"
	.space	1
.LC30:
	.ascii	"%s 1: set slice msg failed!\012\000"
	.space	3
.LC31:
	.ascii	"No slice to dec, add up msg report.\012\000"
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	s_CabacMN, %object
	.size	s_CabacMN, 928
s_CabacMN:
	.space	928
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
