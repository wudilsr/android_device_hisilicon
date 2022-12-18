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
	.file	"vdm_hal_h264.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(vdm_hal_h264)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD
@ drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/.vdm_hal_h264.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal_h264.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiVDHV300R001/vdm_hal_h264.o
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
	.global	Get_V300R001_VirAddr
	.type	Get_V300R001_VirAddr, %function
Get_V300R001_VirAddr:
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
	.size	Get_V300R001_VirAddr, .-Get_V300R001_VirAddr
	.align	2
	.global	Get_V300R001_PhyAddr
	.type	Get_V300R001_PhyAddr, %function
Get_V300R001_PhyAddr:
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
	.size	Get_V300R001_PhyAddr, .-Get_V300R001_PhyAddr
	.align	2
	.global	Write_V300R001_Qmatrix
	.type	Write_V300R001_Qmatrix, %function
Write_V300R001_Qmatrix:
	.fnstart
.LFB1533:
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
	cmp	r1, #0	@ size
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	ldr	ip, [r0, #0]	@ tmp168,* qmatrix
	cmp	r1, #1	@ size,
	sub	r2, r1, #1	@ tmp169, size,
	mov	r4, #1	@ i,
	and	r5, r2, r4	@ tmp171, tmp169,
	mov	r2, #4	@ ivtmp.595,
	str	ip, [r3, #0]	@ tmp168,* vir_addr
	ldmlsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r5, #0	@ tmp171,
	beq	.L7	@,
	ldr	ip, [r0, #4]	@ tmp180,
	mov	r4, #2	@ i,
	cmp	r1, r4	@ size, i
	mov	r2, #8	@ ivtmp.595,
	str	ip, [r3, #4]	@ tmp180,
	ldmlsfd	sp, {r4, r5, fp, sp, pc}	@
.L7:
	ldr	r5, [r0, r2]	@ tmp176,* ivtmp.595
	add	ip, r2, #4	@ tmp173, ivtmp.595,
	add	r4, r4, #2	@ i, i,
	cmp	r1, r4	@ size, i
	str	r5, [r3, r2]	@ tmp176,* ivtmp.595
	add	r2, ip, #4	@ ivtmp.595, tmp173,
	ldr	r5, [r0, ip]	@ tmp179,
	str	r5, [r3, ip]	@ tmp179,
	bhi	.L7	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	Write_V300R001_Qmatrix, .-Write_V300R001_Qmatrix
	.global	__aeabi_idiv
	.align	2
	.global	H264HAL_V300R001_SetSliceMsg
	.type	H264HAL_V300R001_SetSliceMsg, %function
H264HAL_V300R001_SetSliceMsg:
	.fnstart
.LFB1535:
	@ args = 16, pretend = 0, frame = 32
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
	mov	r4, r0	@ pParam, pParam
	mov	r0, r3	@, CurrMsgSlotPhy
	mov	r5, r2	@ pSlcPara, pSlcPara
	bl	MEM_Phy2Vir	@
	subs	r9, r0, #0	@ D.38984,
	beq	.L174	@,
	ldr	r3, [r5, #8]	@ <variable>.valid_bitlen, <variable>.valid_bitlen
	cmp	r3, #0	@ <variable>.valid_bitlen,
	streq	r3, [r9, #0]	@ <variable>.valid_bitlen,* D.38984
	streq	r3, [r9, #4]	@ <variable>.valid_bitlen,
	streq	r3, [r9, #8]	@ <variable>.valid_bitlen,
	beq	.L20	@,
	ldr	ip, [r5, #24]	@ temp.1099, <variable>.bytespos
	ldr	r2, [r5, #16]	@ <variable>.bitsoffset, <variable>.bitsoffset
	ldr	lr, [r4, #916]	@ <variable>.stream_base_addr, <variable>.stream_base_addr
	bic	r1, ip, #15	@ tmp362, temp.1099,
	add	r0, r2, ip, asl #3	@, tmp360, <variable>.bitsoffset, temp.1099,
	and	r3, r0, #127	@ tmp.1087, tmp360,
	str	r3, [r9, #4]	@ tmp.1087,
	ldr	r2, [r5, #8]	@ tmp.1081, <variable>.valid_bitlen
	bic	ip, lr, #15	@ stream_base_addr.1100, <variable>.stream_base_addr,
	rsb	r0, ip, r1	@ temp.1080, stream_base_addr.1100, tmp362
	str	r2, [r9, #8]	@ tmp.1081,
	str	r0, [r9, #0]	@ temp.1080,* D.38984
.L20:
	ldr	r1, [r5, #12]	@ <variable>.valid_bitlen, <variable>.valid_bitlen
	cmp	r1, #0	@ <variable>.valid_bitlen,
	streq	r1, [r9, #12]	@ <variable>.valid_bitlen,
	streq	r1, [r9, #16]	@ <variable>.valid_bitlen,
	streq	r1, [r9, #20]	@ <variable>.valid_bitlen,
	beq	.L22	@,
	ldr	ip, [r5, #28]	@ D.38996, <variable>.bytespos
	ldr	r3, [r5, #20]	@ <variable>.bitsoffset, <variable>.bitsoffset
	ldr	r0, [r4, #916]	@ <variable>.stream_base_addr, <variable>.stream_base_addr
	bic	r1, ip, #15	@ tmp369, D.38996,
	add	lr, r3, ip, asl #3	@, tmp367, <variable>.bitsoffset, D.38996,
	and	r2, lr, #127	@ tmp.454, tmp367,
	str	r2, [r9, #16]	@ tmp.454,
	ldr	ip, [r5, #12]	@ tmp.858, <variable>.valid_bitlen
	bic	r3, r0, #15	@ stream_base_addr, <variable>.stream_base_addr,
	rsb	lr, r3, r1	@ D.39012, stream_base_addr, tmp369
	str	ip, [r9, #20]	@ tmp.858,
	str	lr, [r9, #12]	@ D.39012,
.L22:
	ldr	r1, [r5, #48]	@ <variable>.first_mb_in_slice, <variable>.first_mb_in_slice
	movw	lr, #:lower16:g_not_direct_8x8_inference_flag	@ tmp382,
	ldr	ip, [r5, #36]	@ <variable>.cabac_init_idc, <variable>.cabac_init_idc
	movt	lr, #:upper16:g_not_direct_8x8_inference_flag	@ tmp382,
	ldr	r0, [r5, #32]	@ <variable>.SliceQPy, <variable>.SliceQPy
	bic	r2, r1, #-16777216	@ tmp373, <variable>.first_mb_in_slice,
	bic	r3, r2, #15728640	@ tmp373, tmp373,
	and	r1, ip, #3	@ tmp379, <variable>.cabac_init_idc,
	orr	ip, r3, r0, asl #26	@, tmp378, tmp373, <variable>.SliceQPy,
	orr	r2, ip, r1, asl #24	@, tmp.868, tmp378, tmp379,
	str	r2, [r9, #24]	@ tmp.868,
	ldrb	r3, [lr, #0]	@ zero_extendqisi2	@ g_not_direct_8x8_inference_flag, g_not_direct_8x8_inference_flag
	cmp	r3, #0	@ g_not_direct_8x8_inference_flag,
	ldrneb	r3, [r5, #3]	@ zero_extendqisi2	@ prephitmp.710, <variable>.direct_8x8_inference_flag
	bne	.L24	@,
	ldrb	r3, [r5, #3]	@ zero_extendqisi2	@ prephitmp.710, <variable>.direct_8x8_inference_flag
	cmp	r3, #0	@ prephitmp.710,
	beq	.L175	@,
.L24:
	ldr	r7, [r5, #56]	@ <variable>.listXsize, <variable>.listXsize
	movw	r2, #:lower16:.LANCHOR0	@,
	movw	r6, #:lower16:.LANCHOR0	@,
	str	r2, [fp, #-52]	@, %sfp
	movt	r6, #:upper16:.LANCHOR0	@,
	ldrb	r0, [r5, #0]	@ zero_extendqisi2	@ <variable>.slice_type, <variable>.slice_type
	str	r6, [fp, #-52]	@, %sfp
	mov	r8, r7, asl #8	@ tmp390, <variable>.listXsize,
	ldr	lr, [r5, #40]	@ <variable>.num_ref_idx_l1_active_minus1, <variable>.num_ref_idx_l1_active_minus1
	ldr	r7, [fp, #-52]	@, %sfp
	ldr	r6, [r5, #52]	@ <variable>.listXsize, <variable>.listXsize
	and	r2, lr, #31	@ tmp393, <variable>.num_ref_idx_l1_active_minus1,
	ldr	ip, [r5, #44]	@ <variable>.num_ref_idx_l0_active_minus1, <variable>.num_ref_idx_l0_active_minus1
	add	r0, r7, r0, asl #2	@, tmp405,, <variable>.slice_type,
	and	lr, ip, #31	@ tmp397, <variable>.num_ref_idx_l0_active_minus1,
	orr	r1, r8, r6, asl #2	@, tmp392, tmp390, <variable>.listXsize,
	orr	r8, r1, r2, asl #21	@, tmp396, tmp392, tmp393,
	ldr	r0, [r0, #32]	@ tmp408, g_SliceTypeForPMV
	ldrb	r1, [r5, #2]	@ zero_extendqisi2	@ <variable>.direct_spatial_mv_pred_flag, <variable>.direct_spatial_mv_pred_flag
	orr	r2, r8, lr, asl #16	@, tmp400, tmp396, tmp397,
	orr	ip, r2, r0	@ tmp407, tmp400, tmp408
	orr	r2, ip, r1, asl #15	@, tmp411, tmp407, <variable>.direct_spatial_mv_pred_flag,
	orr	lr, r2, r3, asl #14	@, tmp.870, tmp411, prephitmp.710,
	str	lr, [r9, #28]	@ tmp.870,
	ldrb	r3, [r5, #0]	@ zero_extendqisi2	@ <variable>.slice_type, <variable>.slice_type
	add	r8, r7, r3, asl #2	@, tmp417,, <variable>.slice_type,
	ldr	r3, [r8, #32]	@ tmp419, g_SliceTypeForPMV
	cmp	r3, #2	@ tmp419,
	movne	r3, #0	@ prephitmp.1079,
	movne	r2, r3	@ prephitmp.712, prephitmp.1079
	beq	.L176	@,
.L26:
	str	r2, [r9, #32]	@ prephitmp.712,
	str	r3, [r9, #36]	@ prephitmp.1079,
	ldr	r3, [r5, #60]	@ <variable>.chroma_qp_index_offset, <variable>.chroma_qp_index_offset
	ldrb	r8, [r5, #4]	@ zero_extendqisi2	@ <variable>.weight_flag, <variable>.weight_flag
	and	ip, r3, #31	@ tmp446, <variable>.chroma_qp_index_offset,
	ldr	lr, [r5, #64]	@ <variable>.second_chroma_qp_index_offset, <variable>.second_chroma_qp_index_offset
	mov	r1, ip, asl #5	@ tmp448, tmp446,
	and	r2, lr, #31	@ tmp450, <variable>.second_chroma_qp_index_offset,
	orr	r3, r1, r8, asl #16	@, tmp449, tmp448, <variable>.weight_flag,
	orr	ip, r3, r2	@ D.39098, tmp449, tmp450
	str	ip, [r9, #40]	@ D.39098,
	ldr	lr, [r5, #68]	@ <variable>.slice_alpha_c0_offset_div2, <variable>.slice_alpha_c0_offset_div2
	ldr	r8, [r5, #72]	@ <variable>.slice_beta_offset_div2, <variable>.slice_beta_offset_div2
	and	r3, lr, #15	@ tmp455, <variable>.slice_alpha_c0_offset_div2,
	ldr	r2, [r5, #76]	@ <variable>.disable_deblocking_filter_idc, <variable>.disable_deblocking_filter_idc
	and	r1, r8, #15	@ tmp452, <variable>.slice_beta_offset_div2,
	mov	ip, r3, asl #16	@ tmp457, tmp455,
	orr	lr, ip, r1, asl #8	@, tmp458, tmp457, tmp452,
	orr	r8, lr, r2	@ tmp.891, tmp458, <variable>.disable_deblocking_filter_idc
	str	r8, [r9, #44]	@ tmp.891,
	ldr	r3, [r5, #4056]	@ <variable>.pNextSlice, <variable>.pNextSlice
	cmp	r3, #0	@ <variable>.pNextSlice,
	ldrne	r0, [fp, #16]	@ tmp, last_mb_in_slice
	beq	.L177	@,
.L32:
	str	r0, [r9, #176]	@ tmp,
	ldr	lr, [fp, #8]	@ NextSlcMsgSlotPhy, NextSlcMsgSlotPhy
	bic	r8, lr, #15	@ tmp.897, NextSlcMsgSlotPhy,
	str	r8, [r9, #252]	@ tmp.897,
	ldrb	r1, [r5, #0]	@ zero_extendqisi2	@ <variable>.slice_type, <variable>.slice_type
	ldr	r8, [fp, #-52]	@, %sfp
	add	r2, r8, r1, asl #2	@, tmp474,, <variable>.slice_type,
	ldr	r3, [r2, #32]	@ prephitmp.725, g_SliceTypeForPMV
	cmp	r3, #0	@ prephitmp.725,
	beq	.L34	@,
	ldrb	ip, [r4, #0]	@ zero_extendqisi2	@ <variable>.pic_structure, <variable>.pic_structure
	cmp	ip, #0	@ <variable>.pic_structure,
	bne	.L178	@,
	ldr	r0, [r5, #52]	@ <variable>.listXsize, <variable>.listXsize
	cmp	r0, #0	@ <variable>.listXsize,
	beq	.L38	@,
	mov	r1, #20	@,
	mov	r7, #12	@,
	mov	r2, r5	@ ivtmp.814, pSlcPara
	mov	r6, ip	@ tmp.848, tmp1
	mov	r3, ip	@ i.903, tmp1
	str	r1, [fp, #-48]	@, %sfp
	str	r7, [fp, #-60]	@, %sfp
	str	r9, [fp, #-64]	@ D.38984, %sfp
	str	r5, [fp, #-56]	@ pSlcPara, %sfp
	b	.L43	@
.L41:
	cmp	r1, #3	@ D.39152,
	beq	.L179	@,
.L42:
	ldr	r8, [fp, #-56]	@, %sfp
	ldr	r1, [r8, #52]	@ temp.901, <variable>.listXsize
	cmp	r1, r3	@ temp.901, i.903
	bls	.L180	@,
.L43:
	ldrb	sl, [r2, #1626]	@ zero_extendqisi2	@ <variable>.frame_structure, <variable>.frame_structure
	and	r0, r3, #7	@ D.39145, i.903,
	ldr	r5, [r4, #32]	@ <variable>.mb_adaptive_frame_field_flag, <variable>.mb_adaptive_frame_field_flag
	and	r1, r3, #3	@ D.39152, i.903,
	ldr	r8, [fp, #-52]	@, %sfp
	mov	r7, r0, asl #2	@, D.39145,
	add	lr, r5, sl, asl #1	@, tmp483, <variable>.mb_adaptive_frame_field_flag, <variable>.frame_structure,
	ldrb	r5, [r2, #1627]	@ zero_extendqisi2	@ <variable>.frame_is_long_term, <variable>.frame_is_long_term
	str	r7, [fp, #-72]	@, %sfp
	add	r7, r1, r1, asl #2	@, tmp499, D.39152, D.39152,
	add	sl, r8, lr, asl #2	@, tmp487,, tmp483,
	ldr	r9, [r2, #1644]	@, <variable>.apc_idc
	cmp	r5, #1	@ <variable>.frame_is_long_term,
	add	r3, r3, #1	@ i.903, i.903,
	ldr	lr, [sl, #44]	@ tmp490, g_ListStructFrame
	add	r2, r2, #36	@ ivtmp.814, ivtmp.814,
	mov	r8, r9, asl #1	@ tmp494,,
	moveq	r5, #8	@ iftmp.460,
	and	r9, lr, #3	@ tmp489, tmp490,
	movne	r5, #0	@ iftmp.460,
	and	r8, r8, #31	@ tmp496, tmp494,
	cmp	r0, #7	@ D.39145,
	ldr	sl, [fp, #-72]	@, %sfp
	orr	r0, r5, r9	@ tmp491, iftmp.460, tmp489
	orr	ip, ip, r8, asl r7	@, tmp1, tmp1, tmp496,
	orr	r6, r6, r0, asl sl	@, tmp.848, tmp.848, tmp491,
	bne	.L41	@,
	ldr	r0, [fp, #-60]	@, %sfp
	cmp	r1, #3	@ D.39152,
	ldr	r9, [fp, #-64]	@, %sfp
	str	r6, [r9, r0, asl #2]	@ tmp.848,
	add	r0, r0, #1	@,,
	mov	r6, #0	@ tmp.848,
	str	r0, [fp, #-60]	@, %sfp
	bne	.L42	@,
.L179:
	ldr	r1, [fp, #-48]	@, %sfp
	ldr	lr, [fp, #-64]	@, %sfp
	add	r7, r1, #1	@,,
	str	ip, [lr, r1, asl #2]	@ tmp1,
	mov	ip, #0	@ tmp1,
	ldr	r8, [fp, #-56]	@, %sfp
	str	r7, [fp, #-48]	@, %sfp
	ldr	r1, [r8, #52]	@ temp.901, <variable>.listXsize
	cmp	r1, r3	@ temp.901, i.903
	bhi	.L43	@,
.L180:
	tst	r1, #7	@ temp.901,
	ldr	r9, [fp, #-64]	@ D.38984, %sfp
	ldr	r5, [fp, #-56]	@ pSlcPara, %sfp
	ldrne	r0, [fp, #-60]	@, %sfp
	ldreq	sl, [fp, #-52]	@, %sfp
	ldreqb	r3, [r5, #0]	@ zero_extendqisi2	@ <variable>.slice_type, <variable>.slice_type
	strne	r6, [r9, r0, asl #2]	@ tmp.848,* D.38984
	ldrne	r1, [fp, #-48]	@, %sfp
	addeq	r3, sl, r3, asl #2	@, tmp508,, <variable>.slice_type,
	strne	ip, [r9, r1, asl #2]	@ tmp1,* D.38984
	ldrneb	r3, [r5, #0]	@ zero_extendqisi2	@ <variable>.slice_type, <variable>.slice_type
	ldrne	r2, [fp, #-52]	@, %sfp
	addne	r3, r2, r3, asl #2	@, tmp516,, <variable>.slice_type,
	ldr	r3, [r3, #32]	@ prephitmp.725, g_SliceTypeForPMV
.L38:
	cmp	r3, #2	@ prephitmp.725,
	bne	.L45	@,
	ldr	r6, [r5, #56]	@ <variable>.listXsize, <variable>.listXsize
	cmp	r6, #0	@ <variable>.listXsize,
	beq	.L45	@,
	mov	ip, #0	@ tmp1.853,
	add	r3, r5, #2784	@ ivtmp.809, pSlcPara,
	mov	sl, #28	@,
	mov	r7, #16	@,
	add	r3, r3, #12	@ ivtmp.809, ivtmp.809,
	mov	r6, ip	@ tmp.849, tmp1.853
	mov	r2, ip	@ i.929, tmp1.853
	str	sl, [fp, #-48]	@, %sfp
	str	r7, [fp, #-60]	@, %sfp
	str	r9, [fp, #-64]	@ D.38984, %sfp
	str	r5, [fp, #-56]	@ pSlcPara, %sfp
	b	.L50	@
.L48:
	cmp	r1, #3	@ temp.917,
	beq	.L181	@,
.L49:
	ldr	r8, [fp, #-56]	@, %sfp
	ldr	r1, [r8, #56]	@ temp.912, <variable>.listXsize
	cmp	r1, r2	@ temp.912, i.929
	bls	.L182	@,
.L50:
	ldrb	sl, [r3, #-18]	@ zero_extendqisi2	@ <variable>.frame_structure, <variable>.frame_structure
	and	r0, r2, #7	@ temp.914, i.929,
	ldr	r5, [r4, #32]	@ <variable>.mb_adaptive_frame_field_flag, <variable>.mb_adaptive_frame_field_flag
	and	r1, r2, #3	@ temp.917, i.929,
	ldr	r8, [fp, #-52]	@, %sfp
	mov	r7, r0, asl #2	@, temp.914,
	add	lr, r5, sl, asl #1	@, tmp524, <variable>.mb_adaptive_frame_field_flag, <variable>.frame_structure,
	ldrb	r5, [r3, #-17]	@ zero_extendqisi2	@ <variable>.frame_is_long_term, <variable>.frame_is_long_term
	str	r7, [fp, #-72]	@, %sfp
	add	r7, r1, r1, asl #2	@, tmp540, temp.917, temp.917,
	add	sl, r8, lr, asl #2	@, tmp528,, tmp524,
	ldr	r9, [r3, #0]	@, <variable>.apc_idc
	cmp	r5, #1	@ <variable>.frame_is_long_term,
	add	r2, r2, #1	@ i.929, i.929,
	ldr	lr, [sl, #44]	@ tmp531, g_ListStructFrame
	add	r3, r3, #36	@ ivtmp.809, ivtmp.809,
	moveq	r5, #8	@ iftmp.461,
	movne	r5, #0	@ iftmp.461,
	mov	r8, r9, asl #1	@ tmp535,,
	cmp	r0, #7	@ temp.914,
	and	r0, lr, #3	@ tmp530, tmp531,
	and	r9, r8, #31	@ tmp537, tmp535,
	orr	r0, r5, r0	@ tmp532, iftmp.461, tmp530
	ldr	sl, [fp, #-72]	@, %sfp
	orr	ip, ip, r9, asl r7	@, tmp1.853, tmp1.853, tmp537,
	orr	r6, r6, r0, asl sl	@, tmp.849, tmp.849, tmp532,
	bne	.L48	@,
	ldr	r0, [fp, #-60]	@, %sfp
	cmp	r1, #3	@ temp.917,
	ldr	r9, [fp, #-64]	@, %sfp
	str	r6, [r9, r0, asl #2]	@ tmp.849,
	add	r0, r0, #1	@,,
	mov	r6, #0	@ tmp.849,
	str	r0, [fp, #-60]	@, %sfp
	bne	.L49	@,
.L181:
	ldr	r1, [fp, #-48]	@, %sfp
	ldr	lr, [fp, #-64]	@, %sfp
	add	r7, r1, #1	@,,
	str	ip, [lr, r1, asl #2]	@ tmp1.853,
	mov	ip, #0	@ tmp1.853,
	str	r7, [fp, #-48]	@, %sfp
	b	.L49	@
.L188:
	ldr	r4, [fp, #-56]	@ pParam, %sfp
	mov	r5, sl	@ pSlcPara, pSlcPara
	ldr	r2, [r4, #284]	@ <variable>.weighted_pred_flag, <variable>.weighted_pred_flag
	cmp	r2, #0	@ <variable>.weighted_pred_flag,
	beq	.L107	@,
	ldrb	r1, [sl, #0]	@ zero_extendqisi2	@ <variable>.slice_type, <variable>.slice_type
	ldr	ip, [fp, #-52]	@, %sfp
	add	r0, ip, r1, asl #2	@, tmp747,, <variable>.slice_type,
	ldr	r3, [r0, #32]	@ tmp749, g_SliceTypeForPMV
	cmp	r3, #1	@ tmp749,
	beq	.L108	@,
.L107:
	ldr	lr, [r4, #288]	@ <variable>.weighted_bipred_idc, <variable>.weighted_bipred_idc
	cmp	lr, #1	@ <variable>.weighted_bipred_idc,
	bne	.L34	@,
	ldrb	r0, [r5, #0]	@ zero_extendqisi2	@ <variable>.slice_type, <variable>.slice_type
	ldr	r7, [fp, #-52]	@, %sfp
	add	r3, r7, r0, asl #2	@, tmp755,, <variable>.slice_type,
	ldr	r2, [r3, #32]	@ tmp757, g_SliceTypeForPMV
	cmp	r2, #2	@ tmp757,
	bne	.L34	@,
.L108:
	add	r2, r9, #256	@ ivtmp.787, D.38984,
	mov	r4, r5	@ ivtmp.785, pSlcPara
	mov	r3, r5	@ ivtmp.1072, pSlcPara
	mov	r0, #0	@ i.1053,
.L109:
	ldr	r1, [r3, #88]	@ tmp759, <variable>.wp_weight_l0_y
	add	r0, r0, #1	@ i.1053, i.1053,
	ldrb	sl, [r3, #856]	@ zero_extendqisi2	@ tmp762, <variable>.wp_offset_l0_y
	ldr	ip, [r5, #80]	@ <variable>.luma_log2_weight_denom, <variable>.luma_log2_weight_denom
	mov	r8, r1, asl #23	@ tmp758, tmp759,
	mov	lr, sl, asl #12	@ tmp764, tmp762,
	and	sl, ip, #7	@ tmp766, <variable>.luma_log2_weight_denom,
	mov	r1, r8, lsr #23	@ tmp758, tmp758,
	orr	r8, lr, r1, asl #3	@, tmp765, tmp764, tmp758,
	orr	lr, r8, sl	@ tmp.1049, tmp765, tmp766
	str	lr, [r2, #0]	@ tmp.1049,* ivtmp.787
	ldr	r1, [r3, #216]	@ tmp769, <variable>.wp_weight_l0_u
	ldrb	ip, [r3, #984]	@ zero_extendqisi2	@ tmp772, <variable>.wp_offset_l0_u
	ldr	sl, [r5, #84]	@ <variable>.chroma_log2_weight_denom, <variable>.chroma_log2_weight_denom
	mov	r8, r1, asl #23	@ tmp768, tmp769,
	mov	lr, ip, asl #12	@ tmp774, tmp772,
	and	ip, sl, #7	@ tmp776, <variable>.chroma_log2_weight_denom,
	mov	r1, r8, lsr #23	@ tmp768, tmp768,
	orr	sl, lr, r1, asl #3	@, tmp775, tmp774, tmp768,
	orr	r8, sl, ip	@ tmp1.1052, tmp775, tmp776
	str	r8, [r2, #256]	@ tmp1.1052,
	ldr	lr, [r3, #344]	@ tmp782, <variable>.wp_weight_l0_v
	ldrb	ip, [r3, #1112]	@ zero_extendqisi2	@ tmp778, <variable>.wp_offset_l0_v
	add	r3, r3, #4	@ ivtmp.1072, ivtmp.1072,
	mov	r1, lr, asl #23	@ tmp781, tmp782,
	mov	sl, r1, lsr #23	@ tmp781, tmp781,
	orr	r8, sl, ip, asl #9	@, D.39408, tmp781, tmp778,
	str	r8, [r2, #512]	@ D.39408,
	ldr	r1, [r5, #44]	@ temp.924, <variable>.num_ref_idx_l0_active_minus1
	add	r2, r2, #4	@ ivtmp.787, ivtmp.787,
	cmp	r1, r0	@ temp.924, i.1053
	bcs	.L109	@,
	cmp	r1, #1	@ temp.924,
	and	r2, r1, #1	@ tmp847, temp.924,
	mov	r3, #1	@ i.859,
	bcc	.L159	@,
	cmp	r2, #0	@ tmp847,
	beq	.L110	@,
	mov	r3, #2	@ i.859,
	cmp	r1, r3	@ temp.924, i.859
	bcc	.L159	@,
.L110:
	add	r3, r3, #2	@ i.859, i.859,
	cmp	r1, r3	@ temp.924, i.859
	bcs	.L110	@,
.L159:
	ldrb	r2, [r5, #0]	@ zero_extendqisi2	@ <variable>.slice_type, <variable>.slice_type
	ldr	r8, [fp, #-52]	@, %sfp
	add	r3, r8, r2, asl #2	@, tmp788,, <variable>.slice_type,
	ldr	r2, [r3, #32]	@ tmp790, g_SliceTypeForPMV
	cmp	r2, #2	@ tmp790,
	beq	.L183	@,
.L111:
	ldr	r2, [r5, #84]	@, <variable>.chroma_log2_weight_denom
	mov	r0, #4	@,
	movw	r1, #:lower16:.LC2	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldr	r2, [r5, #44]	@ temp.893, <variable>.num_ref_idx_l0_active_minus1
	mov	r3, #1	@ i.896,
	cmp	r2, r3	@ temp.893,
	and	r1, r2, r3	@ tmp841, temp.893,
	bcc	.L160	@,
	cmp	r1, #0	@ tmp841,
	beq	.L113	@,
	mov	r3, #2	@ i.896,
	cmp	r2, r3	@ temp.893, i.896
	bcc	.L160	@,
.L113:
	add	r3, r3, #2	@ i.896, i.896,
	cmp	r2, r3	@ temp.893, i.896
	bcs	.L113	@,
.L160:
	ldrb	lr, [r5, #0]	@ zero_extendqisi2	@ <variable>.slice_type, <variable>.slice_type
	ldr	sl, [fp, #-52]	@, %sfp
	add	r0, sl, lr, asl #2	@, tmp797,, <variable>.slice_type,
	ldr	r1, [r0, #32]	@ tmp799, g_SliceTypeForPMV
	cmp	r1, #2	@ tmp799,
	beq	.L184	@,
.L34:
	mov	r0, #0	@ D.38988,
.L18:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L178:
	ldr	sl, [r5, #52]	@ <variable>.listXsize, <variable>.listXsize
	cmp	sl, #0	@ <variable>.listXsize,
	beq	.L37	@,
	mov	ip, #0	@ tmp1.854,
	mov	r3, r5	@ ivtmp.833, pSlcPara
	mov	r6, ip	@ tmp.850, tmp1.854
	mov	r2, ip	@ i.977, tmp1.854
	mov	r7, #20	@ Dn_0.846,
	mov	r8, #12	@ Dn_num.842,
	str	r9, [fp, #-56]	@ D.38984, %sfp
	b	.L77	@
.L52:
	cmp	r1, #2	@ D.39192,
	andne	r1, r2, #3	@ prephitmp.968, i.977,
	andne	r0, r2, #7	@ prephitmp.742, i.977,
	beq	.L185	@,
.L63:
	cmp	r0, #7	@ prephitmp.742,
	add	r2, r2, #1	@ i.977, i.977,
	add	r3, r3, #36	@ ivtmp.833, ivtmp.833,
	ldreq	r0, [fp, #-56]	@, %sfp
	streq	r6, [r0, r8, asl #2]	@ tmp.850,
	addeq	r8, r8, #1	@ Dn_num.842, Dn_num.842,
	moveq	r6, #0	@ tmp.850,
	cmp	r1, #3	@ prephitmp.968,
	ldreq	r1, [fp, #-56]	@, %sfp
	streq	ip, [r1, r7, asl #2]	@ tmp1.854,
	addeq	r7, r7, #1	@ Dn_0.846, Dn_0.846,
	ldr	r1, [r5, #52]	@ temp.933, <variable>.listXsize
	moveq	ip, #0	@ tmp1.854,
	cmp	r1, r2	@ temp.933, i.977
	bls	.L186	@,
.L77:
	ldrb	r1, [r3, #1624]	@ zero_extendqisi2	@ D.39192, <variable>.list_structure
	cmp	r1, #1	@ D.39192,
	bne	.L52	@,
	ldrb	r1, [r3, #1625]	@ zero_extendqisi2	@ <variable>.is_used, <variable>.is_used
	cmp	r1, #3	@ <variable>.is_used,
	beq	.L53	@,
	ldrb	r1, [r3, #1628]	@ zero_extendqisi2	@ D.39204, <variable>.top_structure
	and	r0, r2, #7	@ prephitmp.742, i.977,
	ldrb	sl, [r3, #1629]	@ zero_extendqisi2	@ <variable>.top_is_long_term, <variable>.top_is_long_term
	cmp	r1, #1	@ D.39204,
	mov	lr, r0, asl #2	@, prephitmp.742,
	moveq	r9, #4	@,
	movne	r9, #0	@,
	str	r9, [fp, #-60]	@, %sfp
	cmp	sl, #1	@ <variable>.top_is_long_term,
	ldr	r9, [r4, #32]	@, <variable>.mb_adaptive_frame_field_flag
	str	lr, [fp, #-48]	@, %sfp
	moveq	sl, #8	@ iftmp.462,
	add	r1, r9, r1, asl #1	@, tmp554,, D.39204,
	ldr	r9, [fp, #-52]	@, %sfp
	movne	sl, #0	@ iftmp.462,
	add	lr, r9, r1, asl #2	@, tmp558,, tmp554,
	ldr	r9, [fp, #-60]	@, %sfp
	orr	sl, r9, sl	@ tmp551,, iftmp.462
	ldr	r9, [lr, #76]	@ tmp561, g_ListStructField
	and	r1, r9, #3	@ tmp560, tmp561,
	ldr	r9, [fp, #-48]	@, %sfp
	orr	lr, sl, r1	@ tmp562, tmp551, tmp560
	orr	r6, r6, lr, asl r9	@, tmp.850, tmp.850, tmp562,
.L58:
	ldr	lr, [r3, #1644]	@ <variable>.apc_idc, <variable>.apc_idc
	and	r1, r2, #3	@ prephitmp.968, i.977,
	add	r9, r1, r1, asl #2	@, tmp587, prephitmp.968, prephitmp.968,
	mov	sl, lr, asl #1	@ tmp582, <variable>.apc_idc,
	and	lr, sl, #31	@ tmp584, tmp582,
	orr	ip, ip, lr, asl r9	@, tmp1.854, tmp1.854, tmp584,
	b	.L63	@
.L185:
	ldrb	r0, [r3, #1625]	@ zero_extendqisi2	@ <variable>.is_used, <variable>.is_used
	cmp	r0, #3	@ <variable>.is_used,
	beq	.L65	@,
	ldrb	r1, [r3, #1630]	@ zero_extendqisi2	@ D.39241, <variable>.btm_structure
	and	r0, r2, #7	@ prephitmp.742, i.977,
	ldrb	sl, [r3, #1631]	@ zero_extendqisi2	@ <variable>.btm_is_long_term, <variable>.btm_is_long_term
	cmp	r1, #1	@ D.39241,
	moveq	r9, #4	@,
	movne	r9, #0	@,
	str	r9, [fp, #-60]	@, %sfp
	cmp	sl, #1	@ <variable>.btm_is_long_term,
	ldr	r9, [r4, #32]	@, <variable>.mb_adaptive_frame_field_flag
	moveq	sl, #8	@ iftmp.466,
	movne	sl, #0	@ iftmp.466,
	add	lr, r9, r1, asl #1	@, tmp594,, D.39241,
	mov	r9, r0, asl #2	@, prephitmp.742,
	str	r9, [fp, #-48]	@, %sfp
	ldr	r9, [fp, #-52]	@, %sfp
	add	r1, r9, lr, asl #2	@, tmp598,, tmp594,
	ldr	r9, [fp, #-60]	@, %sfp
	orr	lr, r9, sl	@ tmp591,, iftmp.466
	ldr	r9, [r1, #76]	@ tmp601, g_ListStructField
	ldr	r1, [fp, #-48]	@, %sfp
	and	r9, r9, #3	@ tmp600, tmp601,
	orr	sl, lr, r9	@ tmp602, tmp591, tmp600
	orr	r6, r6, sl, asl r1	@, tmp.850, tmp.850, tmp602,
.L70:
	ldr	sl, [r3, #1644]	@ <variable>.apc_idc, <variable>.apc_idc
	and	r1, r2, #3	@ prephitmp.968, i.977,
	add	r9, r1, r1, asl #2	@, tmp628, prephitmp.968, prephitmp.968,
	mov	lr, sl, asl #1	@ tmp622, <variable>.apc_idc,
	and	sl, lr, #30	@ tmp624, tmp622,
	orr	lr, sl, #1	@ tmp625, tmp624,
	orr	ip, ip, lr, asl r9	@, tmp1.854, tmp1.854, tmp625,
	b	.L63	@
.L53:
	and	r0, r2, #7	@ prephitmp.742, i.977,
	ldrb	r1, [r3, #1626]	@ zero_extendqisi2	@ <variable>.frame_structure, <variable>.frame_structure
	ldrb	lr, [r3, #1629]	@ zero_extendqisi2	@ <variable>.top_is_long_term, <variable>.top_is_long_term
	mov	r9, r0, asl #2	@, prephitmp.742,
	str	r9, [fp, #-48]	@, %sfp
	ldr	sl, [r4, #32]	@, <variable>.mb_adaptive_frame_field_flag
	cmp	lr, #1	@ <variable>.top_is_long_term,
	add	r9, sl, r1, asl #1	@,,, <variable>.frame_structure,
	str	r9, [fp, #-60]	@, %sfp
	ldrb	sl, [r3, #1628]	@ zero_extendqisi2	@, <variable>.top_structure
	moveq	lr, #8	@ iftmp.464,
	ldr	r1, [fp, #-60]	@, %sfp
	movne	lr, #0	@ iftmp.464,
	ldr	r9, [fp, #-52]	@, %sfp
	str	sl, [fp, #-64]	@, %sfp
	add	sl, r9, r1, asl #2	@,,,,
	ldr	r1, [fp, #-64]	@, %sfp
	str	sl, [fp, #-60]	@, %sfp
	ldr	r9, [fp, #-60]	@, %sfp
	cmp	r1, #1	@,
	moveq	sl, #4	@ iftmp.465,
	movne	sl, #0	@ iftmp.465,
	orr	sl, sl, lr	@ tmp567, iftmp.465, iftmp.464
	ldr	lr, [r9, #76]	@ tmp578, g_ListStructField
	and	r1, lr, #3	@ tmp577, tmp578,
	orr	lr, sl, r1	@ tmp579, tmp567, tmp577
	ldr	sl, [fp, #-48]	@, %sfp
	orr	r6, r6, lr, asl sl	@, tmp.850, tmp.850, tmp579,
	b	.L58	@
.L65:
	and	r0, r2, #7	@ prephitmp.742, i.977,
	ldrb	r1, [r3, #1626]	@ zero_extendqisi2	@ <variable>.frame_structure, <variable>.frame_structure
	ldrb	lr, [r3, #1631]	@ zero_extendqisi2	@ <variable>.btm_is_long_term, <variable>.btm_is_long_term
	mov	r9, r0, asl #2	@, prephitmp.742,
	str	r9, [fp, #-48]	@, %sfp
	ldr	sl, [r4, #32]	@, <variable>.mb_adaptive_frame_field_flag
	cmp	lr, #1	@ <variable>.btm_is_long_term,
	add	r9, sl, r1, asl #1	@,,, <variable>.frame_structure,
	str	r9, [fp, #-60]	@, %sfp
	ldrb	sl, [r3, #1630]	@ zero_extendqisi2	@, <variable>.btm_structure
	moveq	lr, #8	@ iftmp.468,
	ldr	r1, [fp, #-60]	@, %sfp
	movne	lr, #0	@ iftmp.468,
	ldr	r9, [fp, #-52]	@, %sfp
	str	sl, [fp, #-64]	@, %sfp
	add	sl, r9, r1, asl #2	@,,,,
	ldr	r1, [fp, #-64]	@, %sfp
	str	sl, [fp, #-60]	@, %sfp
	ldr	r9, [fp, #-60]	@, %sfp
	cmp	r1, #1	@,
	moveq	sl, #4	@ iftmp.469,
	movne	sl, #0	@ iftmp.469,
	orr	sl, sl, lr	@ tmp607, iftmp.469, iftmp.468
	ldr	lr, [r9, #76]	@ tmp618, g_ListStructField
	and	r1, lr, #3	@ tmp617, tmp618,
	orr	lr, sl, r1	@ tmp619, tmp607, tmp617
	ldr	sl, [fp, #-48]	@, %sfp
	orr	r6, r6, lr, asl sl	@, tmp.850, tmp.850, tmp619,
	b	.L70	@
.L186:
	ldr	r9, [fp, #-56]	@ D.38984, %sfp
	tst	r1, #7	@ temp.933,
	ldreqb	r3, [r5, #0]	@ zero_extendqisi2	@ <variable>.slice_type, <variable>.slice_type
	strne	r6, [r9, r8, asl #2]	@ tmp.850,* D.38984
	strne	ip, [r9, r7, asl #2]	@ tmp1.854,* D.38984
	ldrneb	r3, [r5, #0]	@ zero_extendqisi2	@ <variable>.slice_type, <variable>.slice_type
	ldreq	r2, [fp, #-52]	@, %sfp
	ldrne	r7, [fp, #-52]	@, %sfp
	addeq	r3, r2, r3, asl #2	@, tmp637,, <variable>.slice_type,
	addne	r3, r7, r3, asl #2	@, tmp645,, <variable>.slice_type,
	ldr	r3, [r3, #32]	@ prephitmp.725, g_SliceTypeForPMV
.L37:
	cmp	r3, #2	@ prephitmp.725,
	beq	.L187	@,
.L45:
	add	r0, r5, #3920	@ tmp548, pSlcPara,
	ldr	sl, [r5, #3928]	@ <variable>.Apc2RefIdx, <variable>.Apc2RefIdx
	add	r3, r0, #16	@ ivtmp.800, tmp548,
	mov	r8, #36	@ Dn_num.1040,
	ldr	r6, [r0, #12]	@ tmp736, <variable>.Apc2RefIdx
	and	r2, sl, #31	@ tmp.852, <variable>.Apc2RefIdx,
	mov	r0, #1	@ i.845,
	mov	sl, r5	@ pSlcPara, pSlcPara
	and	ip, r6, #31	@ tmp735, tmp736,
	str	r4, [fp, #-56]	@ pParam, %sfp
	orr	ip, r2, ip, asl #5	@, tmp.852, tmp.852, tmp735,
.L51:
	add	r5, r0, #1	@ tmp849, i.845,
	add	r4, r3, #4	@ tmp850, ivtmp.800,
	add	r0, r5, #1	@ i.845, tmp849,
	and	r1, r5, #3	@ temp.1034, tmp849,
	and	r2, r0, #3	@ temp.1034, i.845,
	cmp	r5, #32	@ tmp849,
	add	r6, r1, r1, asl #2	@, tmp859, temp.1034, temp.1034,
	add	r5, r2, r2, asl #2	@, tmp867, temp.1034, temp.1034,
	beq	.L188	@,
	ldr	lr, [r3, #0]	@ tmp856, <variable>.Apc2RefIdx
	cmp	r1, #3	@ temp.1034,
	and	r7, lr, #31	@ tmp857, tmp856,
	orr	r7, ip, r7, asl r6	@, tmp.852, tmp.852, tmp857,
	streq	r7, [r9, r8, asl #2]	@ tmp.852,* D.38984
	ldr	r6, [r3, #4]	@ tmp864, <variable>.Apc2RefIdx
	moveq	r7, #0	@ tmp.852,
	addeq	r8, r8, #1	@ Dn_num.1040, Dn_num.1040,
	cmp	r2, #3	@ temp.1034,
	and	ip, r6, #31	@ tmp865, tmp864,
	orr	ip, r7, ip, asl r5	@, tmp.852, tmp.852, tmp865,
	addne	r3, r4, #4	@ ivtmp.800, tmp850,
	bne	.L51	@
.L189:
	str	ip, [r9, r8, asl #2]	@ tmp.852,* D.38984
	add	r3, r4, #4	@ ivtmp.800, tmp850,
	add	r8, r8, #1	@ Dn_num.1040, Dn_num.1040,
	mov	ip, #0	@ tmp.852,
	b	.L51	@
.L176:
	ldrb	r3, [r4, #0]	@ zero_extendqisi2	@ <variable>.pic_structure, <variable>.pic_structure
	cmp	r3, #0	@ <variable>.pic_structure,
	beq	.L190	@,
	ldr	r8, [r5, #2776]	@ tmp431,
	bic	ip, r8, #-16777216	@ tmp429, tmp431,
	bic	r3, ip, #255	@ tmp429, tmp429,
	cmp	r3, #768	@ tmp429,
	beq	.L173	@,
	ldrb	lr, [r5, #2776]	@ zero_extendqisi2	@ <variable>.list_structure, <variable>.list_structure
	cmp	lr, #1	@ <variable>.list_structure,
	beq	.L173	@,
	ldr	ip, [r5, #2788]	@ <variable>.pmv_address_idc, <variable>.pmv_address_idc
	mov	r3, #0	@ prephitmp.1079,
	ldr	lr, [r4, #908]	@ <variable>.half_pmvblk_offset, <variable>.half_pmvblk_offset
	add	r1, ip, #206	@ tmp439, <variable>.pmv_address_idc,
	ldr	r2, [r4, r1, asl #2]	@ tmp442, <variable>.PmvPhyAddr
	add	r8, r2, lr	@ tmp441, tmp442, <variable>.half_pmvblk_offset
	bic	r2, r8, #15	@ prephitmp.712, tmp441,
	b	.L26	@
.L190:
	ldrb	r1, [r5, #2778]	@ zero_extendqisi2	@ <variable>.frame_structure, <variable>.frame_structure
	ldr	r2, [r5, #2788]	@ <variable>.pmv_address_idc, <variable>.pmv_address_idc
	cmp	r1, #3	@ <variable>.frame_structure,
	addeq	r2, r2, #206	@ tmp425, <variable>.pmv_address_idc,
	addne	r2, r2, #206	@ tmp422, <variable>.pmv_address_idc,
	ldreq	r3, [r4, #908]	@ <variable>.half_pmvblk_offset, <variable>.half_pmvblk_offset
	ldreq	r2, [r4, r2, asl #2]	@ temp.876, <variable>.PmvPhyAddr
	ldrne	r2, [r4, r2, asl #2]	@ tmp424, <variable>.PmvPhyAddr
	addeq	r3, r2, r3	@ tmp427, temp.876, <variable>.half_pmvblk_offset
	biceq	r2, r2, #15	@ prephitmp.712, temp.876,
	bicne	r2, r2, #15	@ prephitmp.712, tmp424,
	biceq	r3, r3, #15	@ prephitmp.1079, tmp427,
	b	.L26	@
.L187:
	ldr	r3, [r5, #56]	@ <variable>.listXsize, <variable>.listXsize
	cmp	r3, #0	@ <variable>.listXsize,
	beq	.L45	@,
	add	r7, r5, #2784	@ ivtmp.822, pSlcPara,
	mov	ip, #0	@ tmp1.855,
	add	r3, r7, #12	@ ivtmp.822, ivtmp.822,
	mov	r6, ip	@ tmp.851, tmp1.855
	mov	r2, ip	@ i.1026, tmp1.855
	mov	r7, #28	@ Dn_0.847,
	mov	r8, #16	@ Dn_num.843,
	str	r9, [fp, #-56]	@ D.38984, %sfp
	b	.L104	@
.L79:
	cmp	r1, #2	@ D.39277,
	andne	r1, r2, #3	@ prephitmp.1017, i.1026,
	andne	r0, r2, #7	@ prephitmp.1012, i.1026,
	beq	.L191	@,
.L90:
	cmp	r0, #7	@ prephitmp.1012,
	add	r2, r2, #1	@ i.1026, i.1026,
	add	r3, r3, #36	@ ivtmp.822, ivtmp.822,
	ldreq	r0, [fp, #-56]	@, %sfp
	streq	r6, [r0, r8, asl #2]	@ tmp.851,
	addeq	r8, r8, #1	@ Dn_num.843, Dn_num.843,
	moveq	r6, #0	@ tmp.851,
	cmp	r1, #3	@ prephitmp.1017,
	ldreq	r1, [fp, #-56]	@, %sfp
	streq	ip, [r1, r7, asl #2]	@ tmp1.855,
	addeq	r7, r7, #1	@ Dn_0.847, Dn_0.847,
	ldr	r1, [r5, #56]	@ temp.925, <variable>.listXsize
	moveq	ip, #0	@ tmp1.855,
	cmp	r1, r2	@ temp.925, i.1026
	bls	.L192	@,
.L104:
	ldrb	r1, [r3, #-20]	@ zero_extendqisi2	@ D.39277, <variable>.list_structure
	cmp	r1, #1	@ D.39277,
	bne	.L79	@,
	ldrb	r0, [r3, #-19]	@ zero_extendqisi2	@ <variable>.is_used, <variable>.is_used
	cmp	r0, #3	@ <variable>.is_used,
	beq	.L80	@,
	ldrb	r1, [r3, #-16]	@ zero_extendqisi2	@ D.39289, <variable>.top_structure
	and	r0, r2, #7	@ prephitmp.1012, i.1026,
	ldrb	sl, [r3, #-15]	@ zero_extendqisi2	@ <variable>.top_is_long_term, <variable>.top_is_long_term
	cmp	r1, #1	@ D.39289,
	moveq	r9, #4	@,
	movne	r9, #0	@,
	str	r9, [fp, #-60]	@, %sfp
	cmp	sl, #1	@ <variable>.top_is_long_term,
	ldr	r9, [r4, #32]	@, <variable>.mb_adaptive_frame_field_flag
	moveq	sl, #8	@ iftmp.470,
	movne	sl, #0	@ iftmp.470,
	add	lr, r9, r1, asl #1	@, tmp654,, D.39289,
	mov	r9, r0, asl #2	@, prephitmp.1012,
	str	r9, [fp, #-48]	@, %sfp
	ldr	r9, [fp, #-52]	@, %sfp
	add	r1, r9, lr, asl #2	@, tmp658,, tmp654,
	ldr	r9, [fp, #-60]	@, %sfp
	orr	lr, r9, sl	@ tmp651,, iftmp.470
	ldr	r9, [r1, #76]	@ tmp661, g_ListStructField
	and	r1, r9, #3	@ tmp660, tmp661,
	orr	r9, lr, r1	@ tmp662, tmp651, tmp660
	ldr	r1, [fp, #-48]	@, %sfp
	orr	r6, r6, r9, asl r1	@, tmp.851, tmp.851, tmp662,
.L85:
	ldr	lr, [r3, #0]	@ <variable>.apc_idc, <variable>.apc_idc
	and	r1, r2, #3	@ prephitmp.1017, i.1026,
	add	r9, r1, r1, asl #2	@, tmp687, prephitmp.1017, prephitmp.1017,
	mov	sl, lr, asl #1	@ tmp682, <variable>.apc_idc,
	and	lr, sl, #31	@ tmp684, tmp682,
	orr	ip, ip, lr, asl r9	@, tmp1.855, tmp1.855, tmp684,
	b	.L90	@
.L191:
	ldrb	r0, [r3, #-19]	@ zero_extendqisi2	@ <variable>.is_used, <variable>.is_used
	cmp	r0, #3	@ <variable>.is_used,
	beq	.L92	@,
	ldrb	r1, [r3, #-14]	@ zero_extendqisi2	@ D.39326, <variable>.btm_structure
	and	r0, r2, #7	@ prephitmp.1012, i.1026,
	ldrb	sl, [r3, #-13]	@ zero_extendqisi2	@ <variable>.btm_is_long_term, <variable>.btm_is_long_term
	cmp	r1, #1	@ D.39326,
	mov	lr, r0, asl #2	@, prephitmp.1012,
	moveq	r9, #4	@,
	movne	r9, #0	@,
	str	r9, [fp, #-60]	@, %sfp
	cmp	sl, #1	@ <variable>.btm_is_long_term,
	ldr	r9, [r4, #32]	@, <variable>.mb_adaptive_frame_field_flag
	str	lr, [fp, #-48]	@, %sfp
	moveq	sl, #8	@ iftmp.474,
	add	r1, r9, r1, asl #1	@, tmp694,, D.39326,
	ldr	r9, [fp, #-52]	@, %sfp
	movne	sl, #0	@ iftmp.474,
	add	lr, r9, r1, asl #2	@, tmp698,, tmp694,
	ldr	r9, [fp, #-60]	@, %sfp
	ldr	r1, [lr, #76]	@ tmp701, g_ListStructField
	orr	sl, r9, sl	@ tmp691,, iftmp.474
	and	lr, r1, #3	@ tmp700, tmp701,
	ldr	r1, [fp, #-48]	@, %sfp
	orr	r9, sl, lr	@ tmp702, tmp691, tmp700
	orr	r6, r6, r9, asl r1	@, tmp.851, tmp.851, tmp702,
.L97:
	ldr	sl, [r3, #0]	@ <variable>.apc_idc, <variable>.apc_idc
	and	r1, r2, #3	@ prephitmp.1017, i.1026,
	add	r9, r1, r1, asl #2	@, tmp728, prephitmp.1017, prephitmp.1017,
	mov	lr, sl, asl #1	@ tmp722, <variable>.apc_idc,
	and	sl, lr, #30	@ tmp724, tmp722,
	orr	lr, sl, #1	@ tmp725, tmp724,
	orr	ip, ip, lr, asl r9	@, tmp1.855, tmp1.855, tmp725,
	b	.L90	@
.L80:
	and	r0, r2, #7	@ prephitmp.1012, i.1026,
	ldrb	r1, [r3, #-18]	@ zero_extendqisi2	@ <variable>.frame_structure, <variable>.frame_structure
	ldrb	lr, [r3, #-15]	@ zero_extendqisi2	@ <variable>.top_is_long_term, <variable>.top_is_long_term
	mov	r9, r0, asl #2	@, prephitmp.1012,
	str	r9, [fp, #-48]	@, %sfp
	ldr	sl, [r4, #32]	@, <variable>.mb_adaptive_frame_field_flag
	cmp	lr, #1	@ <variable>.top_is_long_term,
	add	r9, sl, r1, asl #1	@,,, <variable>.frame_structure,
	str	r9, [fp, #-60]	@, %sfp
	ldrb	sl, [r3, #-16]	@ zero_extendqisi2	@, <variable>.top_structure
	moveq	lr, #8	@ iftmp.472,
	ldr	r1, [fp, #-60]	@, %sfp
	movne	lr, #0	@ iftmp.472,
	ldr	r9, [fp, #-52]	@, %sfp
	str	sl, [fp, #-64]	@, %sfp
	add	sl, r9, r1, asl #2	@,,,,
	ldr	r1, [fp, #-64]	@, %sfp
	str	sl, [fp, #-60]	@, %sfp
	ldr	r9, [fp, #-60]	@, %sfp
	cmp	r1, #1	@,
	moveq	sl, #4	@ iftmp.473,
	movne	sl, #0	@ iftmp.473,
	orr	sl, sl, lr	@ tmp667, iftmp.473, iftmp.472
	ldr	lr, [r9, #76]	@ tmp678, g_ListStructField
	and	r1, lr, #3	@ tmp677, tmp678,
	orr	lr, sl, r1	@ tmp679, tmp667, tmp677
	ldr	sl, [fp, #-48]	@, %sfp
	orr	r6, r6, lr, asl sl	@, tmp.851, tmp.851, tmp679,
	b	.L85	@
.L92:
	and	r0, r2, #7	@ prephitmp.1012, i.1026,
	ldrb	r1, [r3, #-18]	@ zero_extendqisi2	@ <variable>.frame_structure, <variable>.frame_structure
	ldrb	lr, [r3, #-13]	@ zero_extendqisi2	@ <variable>.btm_is_long_term, <variable>.btm_is_long_term
	mov	r9, r0, asl #2	@, prephitmp.1012,
	str	r9, [fp, #-48]	@, %sfp
	ldr	sl, [r4, #32]	@, <variable>.mb_adaptive_frame_field_flag
	cmp	lr, #1	@ <variable>.btm_is_long_term,
	add	r9, sl, r1, asl #1	@,,, <variable>.frame_structure,
	str	r9, [fp, #-60]	@, %sfp
	ldrb	sl, [r3, #-14]	@ zero_extendqisi2	@, <variable>.btm_structure
	moveq	lr, #8	@ iftmp.476,
	ldr	r1, [fp, #-60]	@, %sfp
	movne	lr, #0	@ iftmp.476,
	ldr	r9, [fp, #-52]	@, %sfp
	str	sl, [fp, #-64]	@, %sfp
	add	sl, r9, r1, asl #2	@,,,,
	ldr	r1, [fp, #-64]	@, %sfp
	str	sl, [fp, #-60]	@, %sfp
	ldr	r9, [fp, #-60]	@, %sfp
	cmp	r1, #1	@,
	moveq	sl, #4	@ iftmp.477,
	movne	sl, #0	@ iftmp.477,
	orr	sl, sl, lr	@ tmp707, iftmp.477, iftmp.476
	ldr	lr, [r9, #76]	@ tmp718, g_ListStructField
	and	r1, lr, #3	@ tmp717, tmp718,
	orr	lr, sl, r1	@ tmp719, tmp707, tmp717
	ldr	sl, [fp, #-48]	@, %sfp
	orr	r6, r6, lr, asl sl	@, tmp.851, tmp.851, tmp719,
	b	.L97	@
.L192:
	ldr	r9, [fp, #-56]	@ D.38984, %sfp
	tst	r1, #7	@ temp.925,
	strne	r6, [r9, r8, asl #2]	@ tmp.851,* D.38984
	strne	ip, [r9, r7, asl #2]	@ tmp1.855,* D.38984
	b	.L45	@
.L182:
	tst	r1, #7	@ temp.912,
	ldr	r9, [fp, #-64]	@ D.38984, %sfp
	ldr	r5, [fp, #-56]	@ pSlcPara, %sfp
	ldrne	sl, [fp, #-60]	@, %sfp
	strne	r6, [r9, sl, asl #2]	@ tmp.849,* D.38984
	ldrne	r0, [fp, #-48]	@, %sfp
	strne	ip, [r9, r0, asl #2]	@ tmp1.853,* D.38984
	b	.L45	@
.L173:
	ldr	ip, [r5, #2788]	@ <variable>.pmv_address_idc, <variable>.pmv_address_idc
	mov	r3, #0	@ prephitmp.1079,
	add	r1, ip, #206	@ tmp436, <variable>.pmv_address_idc,
	ldr	r2, [r4, r1, asl #2]	@ tmp438, <variable>.PmvPhyAddr
	bic	r2, r2, #15	@ prephitmp.712, tmp438,
	b	.L26	@
.L184:
	ldr	r2, [r5, #40]	@ temp.1075, <variable>.num_ref_idx_l1_active_minus1
	mov	r3, #1	@ i.1061,
	cmp	r3, r2	@ i.1061, temp.1075
	and	r0, r2, r3	@ tmp838, temp.1075,
	bhi	.L161	@,
	cmp	r0, #0	@ tmp838,
	beq	.L114	@,
	cmp	r1, r2	@ i.1061, temp.1075
	mov	r3, r1	@ i.1061, tmp799
	bhi	.L161	@,
.L114:
	add	r3, r3, #2	@ i.1061, i.1061,
	cmp	r3, r2	@ i.1061, temp.1075
	bls	.L114	@,
.L161:
	mov	r3, #1	@ i.1062,
	cmp	r3, r2	@ i.1062, temp.1075
	and	r1, r2, r3	@ tmp835, temp.1075,
	bhi	.L162	@,
	cmp	r1, #0	@ tmp835,
	beq	.L115	@,
	mov	r3, #2	@ i.1062,
	cmp	r3, r2	@ i.1062, temp.1075
	bhi	.L162	@,
.L115:
	add	r3, r3, #2	@ i.1062, i.1062,
	cmp	r3, r2	@ i.1062, temp.1075
	bls	.L115	@,
.L162:
	add	r9, r9, #384	@ ivtmp.763, D.38984,
	mov	r2, #0	@ i,
.L116:
	ldr	ip, [r4, #472]	@ tmp801, <variable>.wp_weight_l1_y
	add	r2, r2, #1	@ i, i,
	ldrb	lr, [r4, #1240]	@ zero_extendqisi2	@ tmp804, <variable>.wp_offset_l1_y
	ldr	r1, [r5, #80]	@ <variable>.luma_log2_weight_denom, <variable>.luma_log2_weight_denom
	mov	r3, ip, asl #23	@ tmp800, tmp801,
	mov	r0, lr, asl #12	@ tmp806, tmp804,
	and	lr, r1, #7	@ tmp808, <variable>.luma_log2_weight_denom,
	mov	ip, r3, lsr #23	@ tmp800, tmp800,
	orr	r3, r0, ip, asl #3	@, tmp807, tmp806, tmp800,
	orr	r0, r3, lr	@ tmp.1068, tmp807, tmp808
	str	r0, [r9, #0]	@ tmp.1068,* ivtmp.763
	ldr	ip, [r4, #600]	@ tmp811, <variable>.wp_weight_l1_u
	ldrb	r1, [r4, #1368]	@ zero_extendqisi2	@ tmp814, <variable>.wp_offset_l1_u
	ldr	lr, [r5, #84]	@ <variable>.chroma_log2_weight_denom, <variable>.chroma_log2_weight_denom
	mov	r3, ip, asl #23	@ tmp810, tmp811,
	mov	r0, r1, asl #12	@ tmp816, tmp814,
	and	r1, lr, #7	@ tmp818, <variable>.chroma_log2_weight_denom,
	mov	ip, r3, lsr #23	@ tmp810, tmp810,
	orr	lr, r0, ip, asl #3	@, tmp817, tmp816, tmp810,
	orr	r3, lr, r1	@ tmp1.1073, tmp817, tmp818
	str	r3, [r9, #256]	@ tmp1.1073,
	ldr	ip, [r4, #728]	@ tmp824, <variable>.wp_weight_l1_v
	ldrb	r1, [r4, #1496]	@ zero_extendqisi2	@ tmp820, <variable>.wp_offset_l1_v
	add	r4, r4, #4	@ ivtmp.785, ivtmp.785,
	mov	lr, ip, asl #23	@ tmp823, tmp824,
	mov	r0, lr, lsr #23	@ tmp823, tmp823,
	orr	r3, r0, r1, asl #9	@, D.39448, tmp823, tmp820,
	str	r3, [r9, #512]	@ D.39448,
	ldr	ip, [r5, #40]	@ <variable>.num_ref_idx_l1_active_minus1, <variable>.num_ref_idx_l1_active_minus1
	add	r9, r9, #4	@ ivtmp.763, ivtmp.763,
	cmp	ip, r2	@ <variable>.num_ref_idx_l1_active_minus1, i
	bcs	.L116	@,
	b	.L34	@
.L175:
	ldr	r2, [r4, #24]	@ <variable>.frame_height_in_mb, <variable>.frame_height_in_mb
	movw	ip, #1620	@ tmp387,
	ldr	r1, [r4, #28]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	mul	lr, r1, r2	@ tmp384, <variable>.pic_width_in_mb, <variable>.frame_height_in_mb
	cmp	lr, ip	@ tmp384, tmp387
	mvnhi	r0, #0	@ D.38988,
	bls	.L24	@,
	b	.L18	@
.L183:
	ldr	r1, [r5, #40]	@ temp.1076, <variable>.num_ref_idx_l1_active_minus1
	mov	r3, #1	@ i.1047,
	cmp	r3, r1	@ i.1047, temp.1076
	and	r0, r1, r3	@ tmp844, temp.1076,
	bhi	.L111	@,
	cmp	r0, #0	@ tmp844,
	beq	.L112	@,
	cmp	r2, r1	@ i.1047, temp.1076
	mov	r3, r2	@ i.1047, tmp790
	bhi	.L111	@,
.L112:
	add	r3, r3, #2	@ i.1047, i.1047,
	cmp	r3, r1	@ i.1047, temp.1076
	bls	.L112	@,
	b	.L111	@
.L177:
	ldr	r0, [r4, #920]	@ D.39119, <variable>.mbtodec
	ldrb	r1, [r5, #1]	@ zero_extendqisi2	@ D.39115, <variable>.MbaffFrameFlag
	cmp	r0, #262144	@ D.39119,
	addgt	r1, r1, #1	@, D.39115,
	suble	r0, r0, #1	@, D.39119,
	movwgt	r0, #:lower16:262143	@,
	addle	r1, r1, #1	@, D.39115,
	movtgt	r0, #:upper16:262143	@,
	bl	__aeabi_idiv	@
	b	.L32	@
.L174:
	movw	r1, #:lower16:.LC0	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	movt	r1, #:upper16:.LC0	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38988,
	b	.L18	@
	.fnend
	.size	H264HAL_V300R001_SetSliceMsg, .-H264HAL_V300R001_SetSliceMsg
	.align	2
	.global	H264HAL_V300R001_SetPicMsg
	.type	H264HAL_V300R001_SetPicMsg, %function
H264HAL_V300R001_SetPicMsg:
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
	mov	r4, r0	@ pParam, pParam
	mov	r0, r2	@, PicMsgSlotPhy
	mov	r5, r1	@ pHwMem, pHwMem
	mov	r6, r3	@ FstSlcMsgSlotPhy, FstSlcMsgSlotPhy
	bl	MEM_Phy2Vir	@
	subs	r2, r0, #0	@ D.38816,
	beq	.L232	@,
	ldrb	ip, [r4, #0]	@ zero_extendqisi2	@ <variable>.pic_structure, <variable>.pic_structure
	movw	r3, #:lower16:.LANCHOR0	@ tmp221,
	ldr	lr, [r4, #32]	@ <variable>.mb_adaptive_frame_field_flag, <variable>.mb_adaptive_frame_field_flag
	movt	r3, #:upper16:.LANCHOR0	@ tmp221,
	ldr	r0, [r4, #36]	@ D.38826, <variable>.transform_8x8_mode_flag
	bic	r6, r6, #15	@ tmp.1253, FstSlcMsgSlotPhy,
	ldr	r7, [r4, #40]	@ D.38829, <variable>.entropy_coding_mode_flag
	add	r1, lr, ip, asl #1	@, tmp224, <variable>.mb_adaptive_frame_field_flag, <variable>.pic_structure,
	ldr	ip, [r4, #44]	@ D.38832, <variable>.constrained_intra_pred_flag
	add	lr, r3, r1, asl #2	@, tmp228, tmp221, tmp224,
	mov	r0, r0, asl #28	@ tmp210, D.38826,
	ldr	r1, [r4, #28]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	orr	r0, r0, r7, asl #27	@, tmp211, tmp210, D.38829,
	ldr	r7, [r4, #20]	@ <variable>.pic_height_in_mb, <variable>.pic_height_in_mb
	orr	r0, r0, ip, asl #26	@, tmp213, tmp211, D.38832,
	ldr	ip, [lr, #136]	@ tmp231, g_StructTrans
	sub	r1, r1, #1	@ tmp214, <variable>.pic_width_in_mb,
	ldr	lr, [r4, #16]	@ <variable>.nal_ref_idc, <variable>.nal_ref_idc
	sub	r7, r7, #1	@ tmp217, <variable>.pic_height_in_mb,
	orr	r0, r0, r1	@ tmp216, tmp213, tmp214
	ldrb	r1, [r4, #1]	@ zero_extendqisi2	@ <variable>.chroma_format_idc, <variable>.chroma_format_idc
	cmp	lr, #0	@ <variable>.nal_ref_idc,
	orr	r3, r0, r7, asl #16	@, tmp220, tmp216, tmp217,
	orr	r0, r3, ip, asl #14	@, tmp232, tmp220, tmp231,
	movne	lr, #-2147483648	@, iftmp.444,
	cmp	r1, #1	@ <variable>.chroma_format_idc,
	orr	r3, r0, lr	@ tmp233, tmp232, iftmp.444
	moveq	r1, #33554432	@ iftmp.445,
	movne	r1, #0	@ iftmp.445,
	orr	lr, r3, r1	@ tmp.447, tmp233, iftmp.445
	str	lr, [r2, #0]	@ tmp.447,* D.38816
	ldr	r0, [r4, #296]	@ <variable>.CurrPicImg2DAddr, <variable>.CurrPicImg2DAddr
	bic	r3, r0, #15	@ tmp.1238, <variable>.CurrPicImg2DAddr,
	str	r3, [r2, #4]	@ tmp.1238,
	ldr	lr, [r4, #48]	@ D.38858, <variable>.ThisPoc
	str	lr, [r2, #8]	@ D.38858,
	ldr	r0, [r4, #32]	@ <variable>.mb_adaptive_frame_field_flag, <variable>.mb_adaptive_frame_field_flag
	cmp	r0, #0	@ <variable>.mb_adaptive_frame_field_flag,
	streq	r0, [r2, #12]	@ <variable>.mb_adaptive_frame_field_flag,
	ldrne	r0, [r4, #52]	@ D.38862, <variable>.TopPoc
	strne	r0, [r2, #12]	@ D.38862,
	ldrne	r0, [r4, #56]	@ D.38864, <variable>.BottomPoc
	str	r0, [r2, #16]	@ <variable>.mb_adaptive_frame_field_flag,
	ldr	r3, [r5, #1136]	@ <variable>.SedTopAddr, <variable>.SedTopAddr
	bic	lr, r3, #15	@ tmp.1243, <variable>.SedTopAddr,
	str	lr, [r2, #20]	@ tmp.1243,
	ldr	r0, [r5, #1140]	@ <variable>.PmvTopAddr, <variable>.PmvTopAddr
	bic	r3, r0, #15	@ tmp.1245, <variable>.PmvTopAddr,
	str	r3, [r2, #24]	@ tmp.1245,
	ldrb	lr, [r4, #0]	@ zero_extendqisi2	@ <variable>.pic_structure, <variable>.pic_structure
	cmp	lr, #2	@ <variable>.pic_structure,
	ldreq	r1, [r4, #300]	@ <variable>.CurrPicPmvIdc, <variable>.CurrPicPmvIdc
	ldrne	lr, [r4, #300]	@ <variable>.CurrPicPmvIdc, <variable>.CurrPicPmvIdc
	addeq	r1, r1, #206	@ tmp244, <variable>.CurrPicPmvIdc,
	ldreq	lr, [r4, #908]	@ <variable>.half_pmvblk_offset, <variable>.half_pmvblk_offset
	addne	lr, lr, #206	@ tmp241, <variable>.CurrPicPmvIdc,
	ldreq	r1, [r4, r1, asl #2]	@ tmp247, <variable>.PmvPhyAddr
	ldrne	lr, [r4, lr, asl #2]	@ tmp243, <variable>.PmvPhyAddr
	addeq	lr, r1, lr	@ tmp246, tmp247, <variable>.half_pmvblk_offset
	bic	r0, lr, #15	@ tmp, tmp246,
	str	r0, [r2, #28]	@ tmp,
	ldr	r3, [r5, #1144]	@ <variable>.RcnTopAddr, <variable>.RcnTopAddr
	bic	r3, r3, #15	@ tmp.1251, <variable>.RcnTopAddr,
	str	r3, [r2, #32]	@ tmp.1251,
	str	r6, [r2, #36]	@ tmp.1253,
	ldr	r0, [r4, #1116]	@ i, <variable>.ApcSize
	cmp	r0, #0	@ i,
	addne	ip, r2, #40	@ ivtmp.1234, D.38816,
	movne	r1, r4	@ ivtmp.1233, pParam
	movne	r3, #0	@ i.1256,
	beq	.L207	@,
.L206:
	ldr	r0, [r1, #924]	@ tmp253, <variable>.Apc2Idc
	add	r3, r3, #1	@ i.1256, i.1256,
	add	r1, r1, #4	@ ivtmp.1233, ivtmp.1233,
	add	lr, r4, r0, asl #2	@, tmp256, pParam, tmp253,
	ldr	r0, [lr, #308]	@ tmp258, <variable>.ImgPhyAddr
	bic	lr, r0, #15	@ tmp.1255, tmp258,
	str	lr, [ip], #4	@ tmp.1255,
	ldr	r0, [r4, #1116]	@ i, <variable>.ApcSize
	cmp	r0, r3	@ i, i.1256
	bhi	.L206	@,
	cmp	r0, #15	@ i,
	bhi	.L208	@,
.L207:
	ldr	r1, [r4, #924]	@ <variable>.Apc2Idc, <variable>.Apc2Idc
	add	r3, r0, #10	@ tmp250, i,
	add	ip, r0, #1	@ i, i,
	rsb	r0, r0, #15	@ tmp284, i,
	add	r3, r2, r3, asl #2	@, ivtmp.1227, D.38816, tmp250,
	cmp	ip, #15	@ i,
	add	lr, r4, r1, asl #2	@, tmp263, pParam, <variable>.Apc2Idc,
	and	r0, r0, #1	@ tmp285, tmp284,
	ldr	r1, [lr, #308]	@ tmp265, <variable>.ImgPhyAddr
	bic	r1, r1, #15	@ tmp.1258, tmp265,
	str	r1, [r3], #4	@ tmp.1258,
	bhi	.L208	@,
	cmp	r0, #0	@ tmp285,
	beq	.L205	@,
	ldr	lr, [r4, #924]	@ <variable>.Apc2Idc, <variable>.Apc2Idc
	add	ip, ip, #1	@ i, i,
	cmp	ip, #15	@ i,
	add	r1, r4, lr, asl #2	@, tmp321, pParam, <variable>.Apc2Idc,
	ldr	lr, [r1, #308]	@ tmp323, <variable>.ImgPhyAddr
	bic	r1, lr, #15	@ tmp.1258, tmp323,
	str	r1, [r3], #4	@ tmp.1258,
	bhi	.L208	@,
.L205:
	ldr	lr, [r4, #924]	@ <variable>.Apc2Idc, <variable>.Apc2Idc
	mov	r1, r3	@ tmp286, ivtmp.1227
	add	ip, ip, #2	@ i, i,
	cmp	ip, #15	@ i,
	add	r0, r4, lr, asl #2	@, tmp293, pParam, <variable>.Apc2Idc,
	ldr	lr, [r0, #308]	@ tmp295, <variable>.ImgPhyAddr
	bic	r0, lr, #15	@ tmp.1258, tmp295,
	str	r0, [r1], #4	@ tmp.1258,
	ldr	lr, [r4, #924]	@ <variable>.Apc2Idc, <variable>.Apc2Idc
	add	r0, r4, lr, asl #2	@, tmp302, pParam, <variable>.Apc2Idc,
	ldr	lr, [r0, #308]	@ tmp304, <variable>.ImgPhyAddr
	bic	r0, lr, #15	@ tmp.1258, tmp304,
	str	r0, [r3, #4]	@ tmp.1258,
	add	r3, r1, #4	@ ivtmp.1227, tmp286,
	bls	.L205	@,
.L208:
	ldr	ip, [r5, #1080]	@ <variable>.H264MnAddr, <variable>.H264MnAddr
	bic	r3, ip, #15	@ tmp.1261, <variable>.H264MnAddr,
	str	r3, [r2, #104]	@ tmp.1261,
	ldr	ip, [r4, #1116]	@ i.1267, <variable>.ApcSize
	cmp	ip, #0	@ i.1267,
	addne	r1, r2, #108	@ ivtmp.1219, D.38816,
	movne	r3, r4	@ ivtmp.1218, pParam
	movne	r0, #0	@ i.1266,
	beq	.L212	@,
.L211:
	ldr	lr, [r3, #988]	@ tmp.1263, <variable>.Apc2Poc
	add	r0, r0, #1	@ i.1266, i.1266,
	str	lr, [r1, #0]	@ tmp.1263,* ivtmp.1219
	ldr	ip, [r3, #1052]	@ tmp.1265, <variable>.Apc2Poc
	add	r3, r3, #4	@ ivtmp.1218, ivtmp.1218,
	str	ip, [r1, #4]	@ tmp.1265,
	add	r1, r1, #8	@ ivtmp.1219, ivtmp.1219,
	ldr	ip, [r4, #1116]	@ i.1267, <variable>.ApcSize
	cmp	ip, r0	@ i.1267, i.1266
	bhi	.L211	@,
	cmp	ip, #15	@ i.1267,
	bhi	.L213	@,
.L212:
	add	r1, ip, #14	@ tmp269, i.1267,
	add	r3, r2, ip, asl #3	@, tmp268, D.38816, i.1267,
	add	r7, ip, #1	@ i.1267, i.1267,
	add	r0, r3, #108	@ ivtmp.1210, tmp268,
	add	r1, r2, r1, asl #3	@, ivtmp.1213, D.38816, tmp269,
	cmp	r7, #15	@ i.1267,
	rsb	lr, ip, #15	@ tmp279, i.1267,
	mov	r3, #0	@ tmp276,
	and	ip, lr, #1	@ tmp280, tmp279,
	str	r3, [r0], #8	@ tmp276,
	str	r3, [r1], #8	@ tmp276,
	bhi	.L213	@,
	cmp	ip, #0	@ tmp280,
	beq	.L210	@,
	add	r7, r7, #1	@ i.1267, i.1267,
	str	r3, [r0], #8	@ tmp276,
	cmp	r7, #15	@ i.1267,
	str	r3, [r1], #8	@ tmp276,
	bhi	.L213	@,
.L210:
	add	r7, r7, #2	@ i.1267, i.1267,
	mov	r6, r0	@ tmp282, ivtmp.1210
	cmp	r7, #15	@ i.1267,
	mov	ip, r1	@ tmp283, ivtmp.1213
	str	r3, [r6], #8	@ tmp276,
	str	r3, [ip], #8	@ tmp276,
	str	r3, [r0, #8]	@ tmp276,
	add	r0, r6, #8	@ ivtmp.1210, tmp282,
	str	r3, [r1, #8]	@ tmp276,
	add	r1, ip, #8	@ ivtmp.1213, tmp283,
	bls	.L210	@,
.L213:
	ldr	r1, [r5, #1152]	@ <variable>.DblkTopAddr, <variable>.DblkTopAddr
	add	ip, r2, #224	@ D.40628, ivtmp.1206,
	mov	r3, r2	@ ivtmp.1206, D.38816
	bic	r0, r1, #15	@ tmp.1270, <variable>.DblkTopAddr,
	str	r0, [r2, #236]	@ tmp.1270,
.L214:
	ldr	r0, [r4, #60]	@ tmp274, <variable>.Qmatrix
	add	r1, r4, #4	@ tmp277, ivtmp.1204,
	add	r2, r3, #4	@ tmp278, ivtmp.1206,
	add	r4, r1, #4	@ ivtmp.1204, tmp277,
	str	r0, [r3, #256]	@ tmp274,
	add	r3, r2, #4	@ ivtmp.1206, tmp278,
	ldr	lr, [r1, #60]	@ tmp316, <variable>.Qmatrix
	cmp	r3, ip	@ ivtmp.1206, D.40628
	str	lr, [r2, #256]	@ tmp316,
	bne	.L214	@,
	mov	r0, #0	@ D.38820,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L232:
	movw	r1, #:lower16:.LC0	@,
	ldr	r2, .L233	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC3	@,
	movt	r3, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38820,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L234:
	.align	2
.L233:
	.word	.LANCHOR0+108
	.fnend
	.size	H264HAL_V300R001_SetPicMsg, .-H264HAL_V300R001_SetPicMsg
	.align	2
	.global	H264HAL_V300R001_CutSliceChain
	.type	H264HAL_V300R001_CutSliceChain, %function
H264HAL_V300R001_CutSliceChain:
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
	subs	r3, r0, #0	@ D.38770,
	beq	.L239	@,
	mov	r0, #0	@ tmp142,
	str	r0, [r3, #252]	@ tmp142,
	ldmfd	sp, {fp, sp, pc}	@
.L239:
	movw	r1, #:lower16:.LC0	@,
	ldr	r2, .L240	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC1	@,
	movt	r3, #:upper16:.LC1	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.38774,
	ldmfd	sp, {fp, sp, pc}	@
.L241:
	.align	2
.L240:
	.word	.LANCHOR0+168
	.fnend
	.size	H264HAL_V300R001_CutSliceChain, .-H264HAL_V300R001_CutSliceChain
	.align	2
	.global	Write_V300R001_CabacTab
	.type	Write_V300R001_CabacTab, %function
Write_V300R001_CabacTab:
	.fnstart
.LFB1528:
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
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@ p
	addne	r4, r0, #5120	@ D.40788, p,
	movwne	r3, #:lower16:.LANCHOR1	@ ivtmp.1331,
	movtne	r3, #:upper16:.LANCHOR1	@ ivtmp.1331,
	beq	.L249	@,
.L244:
	ldr	ip, [r3, #0]	@ tmp146, g_CabacMN
	add	lr, r3, #32	@ tmp154, ivtmp.1331,
	add	r2, r0, #32	@ tmp155, p,
	str	ip, [r0, #0]	@ tmp146,* p
	ldr	r1, [r3, #4]	@ tmp147, g_CabacMN
	str	r1, [r0, #4]	@ tmp147,
	ldr	ip, [r3, #8]	@ tmp148, g_CabacMN
	str	ip, [r0, #8]	@ tmp148,
	ldr	r1, [r3, #12]	@ tmp149, g_CabacMN
	str	r1, [r0, #12]	@ tmp149,
	ldr	ip, [r3, #16]	@ tmp150, g_CabacMN
	str	ip, [r0, #16]	@ tmp150,
	ldr	r1, [r3, #20]	@ tmp151, g_CabacMN
	str	r1, [r0, #20]	@ tmp151,
	ldr	ip, [r3, #24]	@ tmp152, g_CabacMN
	str	ip, [r0, #24]	@ tmp152,
	ldr	r1, [r3, #28]	@ tmp153, g_CabacMN
	str	r1, [r0, #28]	@ tmp153,
	ldr	ip, [r3, #32]	@ tmp158, g_CabacMN
	add	r3, lr, #32	@ ivtmp.1331, tmp154,
	str	ip, [r0, #32]	@ tmp158,
	add	r0, r2, #32	@ p, tmp155,
	ldr	r1, [lr, #4]	@ tmp159, g_CabacMN
	cmp	r0, r4	@ p, D.40788
	str	r1, [r2, #4]	@ tmp159,
	ldr	ip, [lr, #8]	@ tmp160, g_CabacMN
	str	ip, [r2, #8]	@ tmp160,
	ldr	r1, [lr, #12]	@ tmp161, g_CabacMN
	str	r1, [r2, #12]	@ tmp161,
	ldr	ip, [lr, #16]	@ tmp162, g_CabacMN
	str	ip, [r2, #16]	@ tmp162,
	ldr	r1, [lr, #20]	@ tmp163, g_CabacMN
	str	r1, [r2, #20]	@ tmp163,
	ldr	ip, [lr, #24]	@ tmp164, g_CabacMN
	str	ip, [r2, #24]	@ tmp164,
	ldr	r1, [lr, #28]	@ tmp165, g_CabacMN
	str	r1, [r2, #28]	@ tmp165,
	bne	.L244	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L249:
	movw	r1, #:lower16:.LC4	@,
	movw	r2, #258	@,
	movt	r1, #:upper16:.LC4	@,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	Write_V300R001_CabacTab, .-Write_V300R001_CabacTab
	.align	2
	.global	H264HAL_V300R001_InitHal
	.type	H264HAL_V300R001_InitHal, %function
H264HAL_V300R001_InitHal:
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
	bl	Write_V300R001_CabacTab	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	H264HAL_V300R001_InitHal, .-H264HAL_V300R001_InitHal
	.align	2
	.global	H264HAL_V300R001_StartDec
	.type	H264HAL_V300R001_StartDec, %function
H264HAL_V300R001_StartDec:
	.fnstart
.LFB1536:
	@ args = 0, pretend = 0, frame = 40
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
	rsb	r5, r1, r1, asl #3	@, tmp255, VdhId, VdhId,
	add	ip, r5, #1	@ tmp256, tmp255,
	movw	r4, #:lower16:g_VdmDrvParam	@ tmp252,
	movt	r4, #:upper16:g_VdmDrvParam	@ tmp252,
	movw	r3, #:lower16:s_pstVfmwChan	@ tmp251,
	movt	r3, #:upper16:s_pstVfmwChan	@ tmp251,
	mov	r5, r0	@ pParam, pParam
	ldr	r2, [r4, ip, asl #3]	@ <variable>.ChanId, <variable>.ChanId
	ldr	r4, [r3, r2, asl #2]	@ D.39503, s_pstVfmwChan
	cmp	r4, #0	@ D.39503,
	ldrne	r4, [r4, #1744]	@ ModuleLowlyEnable, <variable>.stSynExtraData.s32ModuleLowlyEnable
	cmp	r1, #1	@ VdhId,
	bls	.L302	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC5	@,
	movt	r1, #:upper16:.LC5	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39508,
.L257:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L302:
	beq	.L313	@,
	cmp	r0, #0	@ pParam,
	beq	.L314	@,
	ldr	r0, [r0, #28]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	cmp	r0, #512	@ <variable>.pic_width_in_mb,
	bhi	.L311	@,
	ldr	r1, [r5, #20]	@ <variable>.pic_height_in_mb, <variable>.pic_height_in_mb
	cmp	r1, #512	@ <variable>.pic_height_in_mb,
	bhi	.L311	@,
	ldr	r0, [r5, #1124]	@ <variable>.pFirstSlice, <variable>.pFirstSlice
	cmp	r0, #0	@ <variable>.pFirstSlice,
	beq	.L315	@,
	movw	r6, #:lower16:g_HwMem	@ tmp611,
	movt	r6, #:upper16:g_HwMem	@ tmp611,
	ldr	r2, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	cmp	r2, #0	@ <variable>.pVdmRegVirAddr,
	beq	.L316	@,
.L263:
	movw	lr, #:lower16:.LANCHOR2	@ tmp288,
	movt	lr, #:upper16:.LANCHOR2	@ tmp288,
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC11	@,
	ldr	r7, [lr, #0]	@ StartCnt, StartCnt
	movt	r1, #:upper16:.LC11	@,
	add	r2, r7, #1	@ StartCnt.492, StartCnt,
	str	r2, [lr, #0]	@ StartCnt.492, StartCnt
	bl	dprint_vfmw	@
	ldr	ip, [r5, #920]	@ D.39540, <variable>.mbtodec
	sub	r7, fp, #44	@ D32.493,,
	mov	r1, #0	@ tmp292,
	cmp	ip, #262144	@ D.39540,
	mov	r0, #3	@,
	suble	ip, ip, #1	@ iftmp.494, D.39540,
	str	r1, [r7, #-4]!	@ tmp292, D32
	bicle	ip, ip, #-16777216	@ iftmp.494, iftmp.494,
	ldr	r3, [r7, #0]	@ tmp294,* D32.493
	movwgt	ip, #:lower16:262143	@ iftmp.494,
	bicle	ip, ip, #15728640	@ iftmp.494, iftmp.494,
	movtgt	ip, #:upper16:262143	@ iftmp.494,
	movw	r1, #:lower16:.LC12	@,
	bfi	r3, ip, #0, #20	@ tmp294, iftmp.494,,
	movt	r1, #:upper16:.LC12	@,
	orr	r2, r3, #1073741824	@ tmp297, tmp294,
	bic	sl, r2, #-2147483648	@ tmp298, tmp297,
	bic	ip, sl, #4194304	@ tmp299, tmp298,
	bfc	ip, #23, #1	@ tmp299,,
	orr	r2, ip, #16777216	@ tmp302, tmp299,
	bfc	r2, #25, #1	@ tmp302,,
	str	r2, [r7, #0]	@ tmp302,* D32.493
	str	r2, [r5, #1136]	@ D32, <variable>.basic_cfg0
	movw	r7, #:lower16:16368	@ tmp313,
	ldr	r3, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movt	r7, #:upper16:16368	@ tmp313,
	str	r2, [r3, #8]	@ D32,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	sl, [r5, #912]	@ <variable>.imgstride, <variable>.imgstride
	ldrb	r1, [r5, #2]	@ zero_extendqisi2	@ <variable>.NewPicFlag, <variable>.NewPicFlag
	mov	r2, #1	@ tmp319,
	mov	r0, sl, lsr #2	@ tmp312, <variable>.imgstride,
	ldr	sl, [r5, #1384]	@ <variable>.Compress_en, <variable>.Compress_en
	and	ip, r0, r7	@ tmp313, tmp312, tmp313
	mov	r0, #3	@,
	bfi	ip, r1, #14, #1	@ tmp313, <variable>.NewPicFlag,,
	movw	r1, #:lower16:.LC13	@,
	bic	r3, ip, #32768	@ tmp318, tmp313,
	movt	r1, #:upper16:.LC13	@,
	bfi	r3, r2, #16, #12	@ tmp318, tmp319,,
	bfi	r3, r4, #28, #1	@ tmp320, ModuleLowlyEnable,,
	orr	r7, r3, #536870912	@ tmp324, tmp320,
	bfi	r7, sl, #30, #1	@ tmp324, <variable>.Compress_en,,
	bfc	r7, #31, #1	@ tmp325,,
	str	r7, [r5, #1140]	@ tmp325, <variable>.basic_cfg1
	ldr	ip, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r7, [fp, #-48]	@ tmp325,
	str	r7, [ip, #12]	@ tmp325,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r6, #48]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC14	@,
	bic	r3, r2, #15	@ tmp335, <variable>.MsgSlotAddr,
	str	r3, [r5, #1144]	@ tmp335, <variable>.avm_addr
	ldr	sl, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movt	r1, #:upper16:.LC14	@,
	str	r3, [fp, #-48]	@ tmp335, <variable>.av_msg_addr
	str	r3, [sl, #16]	@ tmp335,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r7, [r6, #32]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC15	@,
	bic	ip, r7, #15	@ tmp345, <variable>.MsgSlotAddr,
	str	ip, [r5, #1148]	@ tmp345, <variable>.vam_addr
	ldr	r2, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movt	r1, #:upper16:.LC15	@,
	str	ip, [fp, #-48]	@ tmp345, <variable>.va_msg_addr
	str	ip, [r2, #20]	@ tmp345,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	sl, [r5, #916]	@ <variable>.stream_base_addr, <variable>.stream_base_addr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC16	@,
	bic	r3, sl, #15	@ tmp354, <variable>.stream_base_addr,
	str	r3, [r5, #1152]	@ tmp354, <variable>.stream_base_addr_reg_tmp
	ldr	r7, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movt	r1, #:upper16:.LC16	@,
	str	r3, [fp, #-48]	@ tmp354, <variable>.stream_base_addr
	movw	sl, #:lower16:3148803	@ tmp366,
	movt	sl, #:upper16:3148803	@ tmp366,
	str	r3, [r7, #24]	@ tmp354,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r0, [r5, #28]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	movw	ip, #:lower16:s_RegPhyBaseAddr	@ tmp363,
	movt	ip, #:upper16:s_RegPhyBaseAddr	@ tmp363,
	cmp	r0, #256	@ <variable>.pic_width_in_mb,
	ldr	r2, [ip, #0]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	movwls	r1, #:lower16:96016	@ tmp362,
	movwhi	r1, #30480	@ tmp361,
	add	r0, r2, #4	@, s_RegPhyBaseAddr,
	movtls	r1, #:upper16:96016	@ tmp362,
	str	r1, [fp, #-48]	@ tmp362, D32
	bl	MEM_WritePhyWord	@
	str	sl, [r5, #1160]	@ tmp366, <variable>.sed_to
	str	sl, [r5, #1164]	@ tmp366, <variable>.itrans_to
	cmp	r4, #1	@ ModuleLowlyEnable,
	str	sl, [r5, #1168]	@ tmp366, <variable>.pmv_to
	movw	r2, #:lower16:g_HwMem	@ tmp374,
	str	sl, [r5, #1172]	@ tmp366, <variable>.prc_to
	movt	r2, #:upper16:g_HwMem	@ tmp374,
	str	sl, [r5, #1176]	@ tmp366, <variable>.rcn_to
	str	sl, [r5, #1180]	@ tmp366, <variable>.dblk_to
	str	sl, [r5, #1184]	@ tmp366, <variable>.ppfd_to
	ldr	r7, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	sl, [fp, #-48]	@ tmp366, D32
	str	sl, [r7, #60]	@ tmp366,
	ldr	r1, [fp, #-48]	@ D32.1492, D32
	ldr	r3, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r1, [r3, #64]	@ D32.1492,
	ldr	ip, [fp, #-48]	@ D32.1495, D32
	ldr	r0, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	ip, [r0, #68]	@ D32.1495,
	ldr	r7, [fp, #-48]	@ D32.1498, D32
	ldr	sl, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r7, [sl, #72]	@ D32.1498,
	ldr	r1, [fp, #-48]	@ D32.1501, D32
	ldr	r3, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r1, [r3, #76]	@ D32.1501,
	ldr	ip, [fp, #-48]	@ D32.1504, D32
	ldr	r0, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	ip, [r0, #80]	@ D32.1504,
	ldr	r7, [fp, #-48]	@ D32.1507, D32
	ldr	sl, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r7, [sl, #84]	@ D32.1507,
	beq	.L317	@,
.L269:
	ldr	sl, [r5, #292]	@ <variable>.CurrPicImgIdc, <variable>.CurrPicImgIdc
	mov	r1, #0	@ tmp393,
	str	r1, [fp, #-48]	@ tmp393, D32
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC18	@,
	movt	r1, #:upper16:.LC18	@,
	add	r2, r5, sl, asl #2	@, tmp399, pParam, <variable>.CurrPicImgIdc,
	ldr	ip, [r2, #308]	@ tmp401, <variable>.ImgPhyAddr
	bic	r7, ip, #15	@ tmp402, tmp401,
	str	r7, [r5, #1188]	@ tmp402, <variable>.ystaddr_1d
	ldr	lr, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r7, [fp, #-48]	@ tmp402, <variable>.ystaddr_1d
	str	r7, [lr, #96]	@ tmp402,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r3, [r5, #912]	@ <variable>.imgstride, <variable>.imgstride
	ldr	r7, [r5, #24]	@ height_in_mb, <variable>.frame_height_in_mb
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC19	@,
	movt	r1, #:upper16:.LC19	@,
	str	r3, [r5, #1192]	@ <variable>.imgstride, <variable>.ystride_1d
	ldr	sl, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r3, [fp, #-48]	@ <variable>.imgstride, <variable>.ystride_1d
	str	r3, [sl, #100]	@ <variable>.imgstride,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r2, [r5, #28]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	movw	r3, #2047	@ tmp419,
	mov	r2, r2, asl #4	@ D.39673, <variable>.pic_width_in_mb,
	sub	ip, r2, #1	@ tmp418, D.39673,
	cmp	ip, r3	@ tmp418, tmp419
	bhi	.L318	@,
.L270:
	mov	r8, #16	@ level,
.L272:
	ldr	sl, [r5, #24]	@ <variable>.frame_height_in_mb, <variable>.frame_height_in_mb
	add	r1, r7, #1	@ tmp436, height_in_mb,
	ldr	ip, [r5, #912]	@ <variable>.imgstride, <variable>.imgstride
	mov	r0, #3	@,
	mov	r2, r1, lsr #1	@ tmp437, tmp436,
	movw	r1, #:lower16:.LC20	@,
	mov	r7, sl, asl #4	@ tmp430, <variable>.frame_height_in_mb,
	movt	r1, #:upper16:.LC20	@,
	add	r3, r7, #31	@ tmp432, tmp430,
	movw	r7, #:lower16:g_HwMem	@ tmp443,
	mul	sl, ip, r2	@ tmp438, <variable>.imgstride, tmp437
	mov	lr, r3, lsr #5	@ tmp433, tmp432,
	movt	r7, #:upper16:g_HwMem	@ tmp443,
	mov	ip, lr, asl #4	@ tmp434, tmp433,
	mla	r3, r8, ip, sl	@ tmp440, level, tmp434, tmp438
	mov	r2, r3, asl #1	@ tmp441, tmp440,
	str	r2, [r5, #1196]	@ tmp441, <variable>.uvoffset_1d
	ldr	lr, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r2, [fp, #-48]	@ tmp441, <variable>.uvoffset_1d
	str	r2, [lr, #104]	@ tmp441,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	sl, [r5, #24]	@ <variable>.frame_height_in_mb, <variable>.frame_height_in_mb
	cmp	r4, #1	@ ModuleLowlyEnable,
	mov	ip, sl, asl #4	@ tmp447, <variable>.frame_height_in_mb,
	add	r0, ip, #31	@ tmp449, tmp447,
	bic	r3, r0, #31	@ tmp451, tmp449,
	mul	r8, r8, r3	@ D.39707, level, tmp451
	str	r8, [r5, #1200]	@ D.39707, <variable>.prcnum_1d_cnt
	ldr	r4, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r8, [fp, #-48]	@ D.39707, D32
	str	r8, [r4, #108]	@ D.39707,
	beq	.L319	@,
.L274:
	ldr	r7, [r6, #1156]	@ <variable>.PpfdBufAddr, <variable>.PpfdBufAddr
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC22	@,
	movt	r1, #:upper16:.LC22	@,
	bic	ip, r7, #15	@ tmp468, <variable>.PpfdBufAddr,
	str	ip, [r5, #1212]	@ tmp468, <variable>.ppfd_buf_addr
	ldr	lr, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r7, #0	@ tmp464,
	str	ip, [fp, #-48]	@ tmp468, <variable>.ppfd_buf_addr
	str	ip, [lr, #128]	@ tmp468,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	sl, [r6, #1160]	@ <variable>.PpfdBufLen, <variable>.PpfdBufLen
	str	r7, [fp, #-48]	@ tmp464, D32
	mov	r0, #3	@,
	movw	r1, #:lower16:.LC23	@,
	movt	r1, #:upper16:.LC23	@,
	strh	sl, [fp, #-48]	@ movhi	@ <variable>.PpfdBufLen, <variable>.ppfd_buf_len
	ldr	r2, [fp, #-48]	@ D32, D32
	str	r2, [r5, #1216]	@ D32, <variable>.ppfd_buf_len
	ldr	r4, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	str	r2, [r4, #132]	@ D32,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldr	r3, [r5, #1260]	@ <variable>.RefPicType, <variable>.RefPicType
	ldr	ip, [r5, #1256]	@ <variable>.RefPicType, <variable>.RefPicType
	mov	r0, #3	@,
	ldr	sl, [r5, #1264]	@ <variable>.RefPicType, <variable>.RefPicType
	and	r4, r3, r0	@ tmp485, <variable>.RefPicType,
	ldr	r1, [r5, #1268]	@ <variable>.RefPicType, <variable>.RefPicType
	and	r2, ip, r0	@ D32.1580, <variable>.RefPicType,
	and	lr, sl, r0	@ tmp488, <variable>.RefPicType,
	ldr	sl, [r5, #1272]	@ <variable>.RefPicType, <variable>.RefPicType
	orr	ip, r2, r4, asl #2	@, temp.1585, D32.1580, tmp485,
	ldr	r2, [r5, #1276]	@ <variable>.RefPicType, <variable>.RefPicType
	and	r4, r1, r0	@ tmp491, <variable>.RefPicType,
	orr	r3, ip, lr, asl #4	@, temp.1591, temp.1585, tmp488,
	and	ip, sl, r0	@ tmp494, <variable>.RefPicType,
	ldr	sl, [r5, #1280]	@ <variable>.RefPicType, <variable>.RefPicType
	orr	lr, r3, r4, asl #6	@, temp.1597, temp.1591, tmp491,
	ldr	r3, [r5, #1284]	@ <variable>.RefPicType, <variable>.RefPicType
	and	r4, r2, r0	@ tmp497, <variable>.RefPicType,
	orr	r1, lr, ip, asl #8	@, temp.1603, temp.1597, tmp494,
	and	lr, sl, r0	@ tmp500, <variable>.RefPicType,
	ldr	sl, [r5, #1288]	@ <variable>.RefPicType, <variable>.RefPicType
	orr	ip, r1, r4, asl #10	@, temp.1609, temp.1603, tmp497,
	ldr	r4, [r5, #1292]	@ <variable>.RefPicType, <variable>.RefPicType
	and	r1, r3, r0	@ tmp503, <variable>.RefPicType,
	orr	r2, ip, lr, asl #12	@, temp.1615, temp.1609, tmp500,
	ldr	lr, [r5, #1296]	@ <variable>.RefPicType, <variable>.RefPicType
	and	ip, sl, r0	@ tmp506, <variable>.RefPicType,
	orr	sl, r2, r1, asl #14	@, temp.1621, temp.1615, tmp503,
	ldr	r2, [r5, #1300]	@ <variable>.RefPicType, <variable>.RefPicType
	and	r1, r4, r0	@ tmp509, <variable>.RefPicType,
	orr	r3, sl, ip, asl #16	@, temp.1627, temp.1621, tmp506,
	and	r4, lr, r0	@ tmp512, <variable>.RefPicType,
	ldr	sl, [r5, #1304]	@ <variable>.RefPicType, <variable>.RefPicType
	orr	r1, r3, r1, asl #18	@, temp.1633, temp.1627, tmp509,
	and	r2, r2, r0	@ tmp515, <variable>.RefPicType,
	ldr	r3, [r5, #1308]	@ <variable>.RefPicType, <variable>.RefPicType
	and	ip, sl, r0	@ tmp518, <variable>.RefPicType,
	orr	lr, r1, r4, asl #20	@, temp.1639, temp.1633, tmp512,
	ldr	sl, [r5, #1312]	@ <variable>.RefPicType, <variable>.RefPicType
	orr	r4, lr, r2, asl #22	@, temp.1645, temp.1639, tmp515,
	and	lr, r3, r0	@ tmp521, <variable>.RefPicType,
	orr	r2, r4, ip, asl #24	@, temp.1651, temp.1645, tmp518,
	and	r1, sl, r0	@ tmp524, <variable>.RefPicType,
	ldr	ip, [r5, #1316]	@ <variable>.RefPicType, <variable>.RefPicType
	orr	r3, r2, lr, asl #26	@, temp.1657, temp.1651, tmp521,
	ldr	lr, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	orr	r4, r3, r1, asl #28	@, temp.1663, temp.1657, tmp524,
	movw	r1, #:lower16:.LC24	@,
	movt	r1, #:upper16:.LC24	@,
	orr	sl, r4, ip, asl #30	@, D.39748, temp.1663, <variable>.RefPicType,
	str	sl, [fp, #-48]	@ D.39748, D32
	str	sl, [lr, #148]	@ D.39748,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	ldrb	ip, [r5, #0]	@ zero_extendqisi2	@ <variable>.pic_structure, <variable>.pic_structure
	ldr	r2, [r5, #32]	@ <variable>.mb_adaptive_frame_field_flag, <variable>.mb_adaptive_frame_field_flag
	movw	r3, #:lower16:.LANCHOR0	@ tmp534,
	movt	r3, #:upper16:.LANCHOR0	@ tmp534,
	ldr	r4, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	add	sl, r2, ip, asl #1	@, tmp537, <variable>.mb_adaptive_frame_field_flag, <variable>.pic_structure,
	add	r1, r3, sl, asl #2	@, tmp541, tmp534, tmp537,
	ldr	r0, [r1, #136]	@ tmp543, g_StructTrans
	movw	r1, #:lower16:.LC25	@,
	movt	r1, #:upper16:.LC25	@,
	cmp	r0, r7	@ tmp543,
	strne	r7, [fp, #-48]	@ tmp464, D32
	mov	r0, #3	@,
	moveq	sl, #2	@ tmp544,
	movne	sl, r7	@ prephitmp.1411, tmp464
	streq	sl, [fp, #-48]	@ tmp544, D32
	movw	r7, #:lower16:g_HwMem	@ tmp546,
	str	sl, [r4, #152]	@ prephitmp.1411,
	movt	r7, #:upper16:g_HwMem	@ tmp546,
	ldr	r2, [fp, #-48]	@, D32
	mvn	sl, #0	@ tmp552,
	bl	dprint_vfmw	@
	ldr	ip, [r6, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	mov	r0, r5	@, pParam
	mov	r1, r7	@, tmp546
	str	sl, [ip, #32]	@ tmp552,
	ldr	r2, [r6, #48]	@, <variable>.MsgSlotAddr
	ldr	r3, [r6, #52]	@, <variable>.MsgSlotAddr
	bl	H264HAL_V300R001_SetPicMsg	@
	ldr	r4, [r5, #1124]	@ pSlicePara, <variable>.pFirstSlice
	cmp	r4, #0	@ pSlicePara,
	beq	.L320	@,
	ldr	r8, [r4, #48]	@ D.39778, <variable>.first_mb_in_slice
	cmp	r8, #0	@ D.39778,
	moveq	r9, r8	@ AddSlice0Flag, D.39778
	bne	.L321	@,
.L279:
	ldr	r1, [r5, #1120]	@ temp.1577, <variable>.SliceParaNum
	cmp	r1, #0	@ temp.1577,
	ble	.L281	@,
	ldr	ip, [r4, #48]	@ prephitmp.1426, <variable>.first_mb_in_slice
	add	sl, r9, #5	@ pretmp.1418, AddSlice0Flag,
	mov	r8, #0	@ pre_first_mb_in_slice,
	add	r9, r9, #4	@ pretmp.1417, AddSlice0Flag,
	mov	r2, r4	@ tmp_pSlicePara.1578, pSlicePara
	mov	r7, r8	@ i, pre_first_mb_in_slice
.L295:
	cmp	r8, ip	@ pre_first_mb_in_slice, prephitmp.1426
	movcc	r3, #0	@, tmp588
	movcs	r3, #1	@, tmp588
	cmp	r7, #0	@ i,
	add	lr, r9, r7	@ tmp578, pretmp.1417, i
	add	r0, r7, sl	@ D.39814, i, pretmp.1418
	movle	r3, #0	@, tmp588,
	add	lr, lr, #8	@ tmp579, tmp578,
	cmp	r3, #0	@ tmp588,
	add	r3, r0, #8	@ tmp581, D.39814,
	ldr	lr, [r6, lr, asl #2]	@ prev_slcmsg_phy.1570, <variable>.MsgSlotAddr
	ldr	r3, [r6, r3, asl #2]	@ cur_slcmsg_phy.1571, <variable>.MsgSlotAddr
	movne	r4, r2	@ tmp_pSlicePara, tmp_pSlicePara.1578
	bne	.L293	@,
	add	r7, r7, #1	@ j, i,
	cmp	r1, r7	@ temp.1577, j
	movle	r4, r2	@ tmp_pSlicePara, tmp_pSlicePara.1578
	ble	.L284	@,
	ldr	r4, [r2, #4056]	@ tmp_pSlicePara, <variable>.pNextSlice
	cmp	r4, #0	@ tmp_pSlicePara,
	beq	.L285	@,
	ldr	r8, [r4, #48]	@ <variable>.first_mb_in_slice, <variable>.first_mb_in_slice
	cmp	r8, ip	@ <variable>.first_mb_in_slice, prephitmp.1426
	bhi	.L284	@,
	mvn	r8, r7	@ tmp617, j
	add	r8, r8, r1	@ tmp616, tmp617, temp.1577
	tst	r8, #1	@ tmp616,
	bne	.L304	@,
	b	.L301	@
.L322:
	ldr	r8, [r4, #48]	@ <variable>.first_mb_in_slice, <variable>.first_mb_in_slice
	cmp	r8, ip	@ <variable>.first_mb_in_slice, prephitmp.1426
	bhi	.L284	@,
.L301:
	add	r7, r7, #1	@ j, j,
	cmp	r1, r7	@ temp.1577, j
	ble	.L284	@,
	ldr	r4, [r4, #4056]	@ tmp_pSlicePara, <variable>.pNextSlice
	cmp	r4, #0	@ tmp_pSlicePara,
	beq	.L285	@,
	ldr	r8, [r4, #48]	@ <variable>.first_mb_in_slice, <variable>.first_mb_in_slice
	cmp	r8, ip	@ <variable>.first_mb_in_slice, prephitmp.1426
	bhi	.L284	@,
.L304:
	ldr	r4, [r4, #4056]	@ tmp_pSlicePara, <variable>.pNextSlice
	add	r7, r7, #1	@ j, j,
	cmp	r4, #0	@ tmp_pSlicePara,
	bne	.L322	@,
.L285:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC28	@,
	movw	r2, #1474	@,
	movt	r1, #:upper16:.LC28	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39508,
	b	.L257	@
.L284:
	cmp	r7, r1	@ j, temp.1577
	beq	.L288	@,
	cmp	r0, #140	@ D.39814,
	beq	.L288	@,
	add	r0, sl, r7	@ tmp598, pretmp.1418, j
	ldr	r8, [r4, #48]	@ <variable>.first_mb_in_slice, <variable>.first_mb_in_slice
	add	r0, r0, #8	@ tmp599, tmp598,
	sub	r8, r8, #1	@ last_mb_in_slice, <variable>.first_mb_in_slice,
	ldr	r0, [r6, r0, asl #2]	@, <variable>.MsgSlotAddr
	str	r0, [fp, #-56]	@, %sfp
.L290:
	sub	r1, r1, #1	@ tmp600, temp.1577,
	sub	r7, r7, #1	@ i, j,
	cmp	r1, r7	@ tmp600, i
	mov	r0, r5	@, pParam
	moveq	r1, #0	@,
	streq	r1, [r2, #4056]	@, <variable>.pNextSlice
	str	r8, [sp, #12]	@ last_mb_in_slice,
	mov	r8, ip	@ pre_first_mb_in_slice, prephitmp.1426
	ldr	ip, [fp, #-56]	@, %sfp
	movw	r1, #:lower16:g_HwMem	@,
	movt	r1, #:upper16:g_HwMem	@,
	str	lr, [sp, #0]	@ prev_slcmsg_phy.1570,
	str	r8, [sp, #8]	@ pre_first_mb_in_slice,
	str	ip, [sp, #4]	@,
	bl	H264HAL_V300R001_SetSliceMsg	@
	cmp	r0, #0	@,
	bne	.L323	@,
	ldr	r2, [fp, #-56]	@, %sfp
	cmp	r2, #0	@,
	beq	.L306	@,
	ldr	r1, [r5, #1120]	@ temp.1577, <variable>.SliceParaNum
.L293:
	add	r7, r7, #1	@ i, i,
	mov	r3, r1	@ temp.1577, temp.1577
	cmp	r1, r7	@ temp.1577, i
	ble	.L294	@,
	mov	r2, r4	@ tmp_pSlicePara.1578, tmp_pSlicePara
	ldr	ip, [r4, #48]	@ prephitmp.1426, <variable>.first_mb_in_slice
	b	.L295	@
.L288:
	ldr	r0, [r5, #20]	@ <variable>.pic_height_in_mb, <variable>.pic_height_in_mb
	mov	r1, #0	@,
	str	r1, [fp, #-56]	@, %sfp
	ldr	r8, [r5, #28]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	str	r1, [r2, #4056]	@, <variable>.pNextSlice
	ldr	r1, [r5, #1120]	@ temp.1577, <variable>.SliceParaNum
	mul	r8, r8, r0	@ tmp592, <variable>.pic_width_in_mb, <variable>.pic_height_in_mb
	sub	r8, r8, #1	@ last_mb_in_slice, tmp592,
	b	.L290	@
.L318:
	sub	lr, r2, #2048	@ tmp420, D.39673,
	sub	r0, lr, #1	@ tmp420, tmp420,
	cmp	r0, r3	@ tmp420, tmp419
	movls	r8, #32	@ level,
	bls	.L272	@,
	sub	sl, r2, #4096	@ tmp423, D.39673,
	sub	ip, sl, #1	@ tmp423, tmp423,
	cmp	ip, r3	@ tmp423, tmp419
	movls	r8, #48	@ level,
	bls	.L272	@,
	sub	r1, r2, #6144	@ tmp426, D.39673,
	sub	r2, r1, #1	@ tmp426, tmp426,
	cmp	r2, r3	@ tmp426, tmp419
	movls	r8, #64	@ level,
	bls	.L272	@,
	b	.L270	@
.L321:
	ldr	r9, [r4, #8]	@, <variable>.valid_bitlen
	mov	ip, #0	@ tmp559,
	str	ip, [r4, #48]	@ tmp559, <variable>.first_mb_in_slice
	sub	lr, r8, #1	@, D.39778,
	mov	r1, r7	@, tmp546
	mov	r2, r4	@, pSlicePara
	str	r9, [fp, #-76]	@, %sfp
	mov	r9, #1	@ tmp560,
	ldr	r0, [r4, #12]	@, <variable>.valid_bitlen
	str	r9, [r4, #8]	@ tmp560, <variable>.valid_bitlen
	str	r0, [fp, #-72]	@, %sfp
	mov	r0, r5	@, pParam
	ldr	r3, [r4, #16]	@, <variable>.bitsoffset
	str	ip, [r4, #12]	@ tmp559, <variable>.valid_bitlen
	str	lr, [fp, #-80]	@, %sfp
	str	r3, [fp, #-68]	@, %sfp
	ldr	r3, [r4, #20]	@, <variable>.bitsoffset
	str	ip, [r4, #16]	@ tmp559, <variable>.bitsoffset
	str	r3, [fp, #-64]	@, %sfp
	ldr	lr, [r4, #24]	@, <variable>.bytespos
	str	ip, [r4, #20]	@ tmp559, <variable>.bitsoffset
	str	lr, [fp, #-60]	@, %sfp
	ldr	r3, [r4, #28]	@, <variable>.bytespos
	str	ip, [r4, #24]	@ tmp559, <variable>.bytespos
	str	r3, [fp, #-56]	@, %sfp
	str	ip, [r4, #28]	@ tmp559, <variable>.bytespos
	ldr	lr, [r7, #48]	@, <variable>.MsgSlotAddr
	ldr	r3, [r7, #52]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	str	lr, [sp, #0]	@,
	ldr	lr, [fp, #-80]	@, %sfp
	ldr	r7, [r7, #56]	@ <variable>.MsgSlotAddr, <variable>.MsgSlotAddr
	stmib	sp, {r7, ip, lr}	@ phole stm
	bl	H264HAL_V300R001_SetSliceMsg	@
	cmp	r0, #0	@,
	bne	.L324	@,
	ldr	r0, [fp, #-56]	@, %sfp
	str	r8, [r4, #48]	@ D.39778, <variable>.first_mb_in_slice
	str	r0, [r4, #28]	@, <variable>.bytespos
	ldr	r3, [fp, #-76]	@, %sfp
	str	r3, [r4, #8]	@, <variable>.valid_bitlen
	ldr	lr, [fp, #-72]	@, %sfp
	str	lr, [r4, #12]	@, <variable>.valid_bitlen
	ldr	ip, [fp, #-68]	@, %sfp
	str	ip, [r4, #16]	@, <variable>.bitsoffset
	ldr	r2, [fp, #-64]	@, %sfp
	str	r2, [r4, #20]	@, <variable>.bitsoffset
	ldr	r1, [fp, #-60]	@, %sfp
	str	r1, [r4, #24]	@, <variable>.bytespos
	ldr	r4, [r5, #1124]	@ pSlicePara, <variable>.pFirstSlice
	b	.L279	@
.L317:
	movw	r0, #:lower16:g_TunnelLineNumber	@ tmp388,
	movt	r0, #:upper16:g_TunnelLineNumber	@ tmp388,
	ldr	sl, [r2, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movw	r1, #:lower16:.LC17	@,
	ldr	r3, [r0, #0]	@ g_TunnelLineNumber.503, g_TunnelLineNumber
	movt	r1, #:upper16:.LC17	@,
	mov	r0, #3	@,
	str	r3, [fp, #-48]	@ g_TunnelLineNumber.503, D32
	str	r3, [sl, #92]	@ g_TunnelLineNumber.503,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	b	.L269	@
.L319:
	ldr	r2, [r5, #292]	@ <variable>.CurrPicImgIdc, <variable>.CurrPicImgIdc
	movw	r1, #:lower16:.LC21	@,
	ldr	r4, [r7, #0]	@ <variable>.pVdmRegVirAddr, <variable>.pVdmRegVirAddr
	movt	r1, #:upper16:.LC21	@,
	mov	r0, #3	@,
	add	r3, r5, r2, asl #2	@, tmp458, pParam, <variable>.CurrPicImgIdc,
	ldr	lr, [r3, #564]	@ D32.508, <variable>.LineNumPhyAddr
	str	lr, [fp, #-48]	@ D32.508, D32
	str	lr, [r4, #112]	@ D32.508,
	ldr	r2, [fp, #-48]	@, D32
	bl	dprint_vfmw	@
	b	.L274	@
.L316:
	movw	r0, #:lower16:-121438208	@,
	movt	r0, #:upper16:-121438208	@,
	bl	MEM_Phy2Vir	@
	subs	r3, r0, #0	@ D.39527,
	strne	r3, [r6, #0]	@ D.39527, <variable>.pVdmRegVirAddr
	bne	.L263	@,
	movw	r1, #:lower16:.LC10	@,
	movt	r1, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39508,
	b	.L257	@
.L306:
	ldr	r3, [r5, #1120]	@ temp.1577, <variable>.SliceParaNum
.L294:
	cmp	r3, #0	@ temp.1577,
	ble	.L281	@,
	add	r3, r3, r9	@ tmp606, temp.1577, pretmp.1417
	add	lr, r3, #8	@ tmp607, tmp606,
	ldr	r0, [r6, lr, asl #2]	@, <variable>.MsgSlotAddr
	bl	H264HAL_V300R001_CutSliceChain	@
	mov	r0, #0	@ D.39508,
	b	.L257	@
.L313:
	mov	lr, #0	@ tmp263,
	mov	r3, r1	@, VdhId
	mov	r0, lr	@, tmp263
	movw	r1, #:lower16:.LC6	@,
	ldr	r2, .L325	@,
	movt	r1, #:upper16:.LC6	@,
	str	lr, [sp, #0]	@ tmp263,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39508,
	b	.L257	@
.L323:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC27	@,
	movw	r2, #1602	@,
	movt	r1, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39508,
	b	.L257	@
.L311:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC0	@,
	ldr	r2, .L325	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC8	@,
	movt	r3, #:upper16:.LC8	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39508,
	b	.L257	@
.L324:
	mov	r0, r9	@, tmp560
	movw	r1, #:lower16:.LC27	@,
	movw	r2, #1430	@,
	movt	r1, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	mov	r0, sl	@ D.39508, tmp552
	b	.L257	@
.L314:
	movw	r1, #:lower16:.LC0	@,
	ldr	r2, .L325	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC7	@,
	movt	r3, #:upper16:.LC7	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39508,
	b	.L257	@
.L281:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC29	@,
	movt	r1, #:upper16:.LC29	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39508,
	b	.L257	@
.L320:
	mov	r0, r4	@, pSlicePara
	movw	r1, #:lower16:.LC26	@,
	movt	r1, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	mov	r0, sl	@ D.39508, tmp552
	b	.L257	@
.L315:
	movw	r1, #:lower16:.LC0	@,
	ldr	r2, .L325	@,
	movt	r1, #:upper16:.LC0	@,
	movw	r3, #:lower16:.LC9	@,
	movt	r3, #:upper16:.LC9	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.39508,
	b	.L257	@
.L326:
	.align	2
.L325:
	.word	.LANCHOR0+200
	.fnend
	.size	H264HAL_V300R001_StartDec, .-H264HAL_V300R001_StartDec
	.global	g_CabacMN
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.38941, %object
	.size	__func__.38941, 29
__func__.38941:
	.ascii	"H264HAL_V300R001_SetSliceMsg\000"
	.space	3
	.type	g_SliceTypeForPMV, %object
	.size	g_SliceTypeForPMV, 12
g_SliceTypeForPMV:
	.word	1
	.word	2
	.word	0
	.type	g_ListStructFrame, %object
	.size	g_ListStructFrame, 32
g_ListStructFrame:
	.word	0
	.word	1
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	2
	.type	g_ListStructField, %object
	.size	g_ListStructField, 32
g_ListStructField:
	.word	0
	.word	1
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.type	__func__.38803, %object
	.size	__func__.38803, 27
__func__.38803:
	.ascii	"H264HAL_V300R001_SetPicMsg\000"
	.space	1
	.type	g_StructTrans, %object
	.size	g_StructTrans, 32
g_StructTrans:
	.word	0
	.word	3
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.type	__func__.38769, %object
	.size	__func__.38769, 31
__func__.38769:
	.ascii	"H264HAL_V300R001_CutSliceChain\000"
	.space	1
	.type	__func__.39484, %object
	.size	__func__.39484, 26
__func__.39484:
	.ascii	"H264HAL_V300R001_StartDec\000"
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	g_CabacMN, %object
	.size	g_CabacMN, 5120
g_CabacMN:
	.word	388044546
	.word	352326208
	.word	153820416
	.word	721207
	.word	4522025
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	521477919
	.word	422707200
	.word	0
	.word	0
	.word	87683918
	.word	-180289218
	.word	17367089
	.word	-613020375
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	21230414
	.word	-180289218
	.word	440602714
	.word	157864575
	.word	-328728576
	.word	0
	.word	0
	.word	0
	.word	204602441
	.word	288553558
	.word	-278922691
	.word	154007875
	.word	-78971830
	.word	-78579384
	.word	20578304
	.word	0
	.word	-45745583
	.word	-178256329
	.word	121895766
	.word	39321658
	.word	-45287842
	.word	87426117
	.word	-45023144
	.word	0
	.word	370745856
	.word	268442146
	.word	320219136
	.word	721207
	.word	4522025
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	521477919
	.word	422707200
	.word	0
	.word	0
	.word	37878343
	.word	-212925132
	.word	-32963543
	.word	-478802647
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-62064057
	.word	-212925132
	.word	956442916
	.word	440783743
	.word	-245039104
	.word	0
	.word	0
	.word	0
	.word	154336582
	.word	171312709
	.word	-212205516
	.word	137101122
	.word	-11730618
	.word	-27854008
	.word	3997696
	.word	0
	.word	-28968110
	.word	-161480133
	.word	38534487
	.word	-43777736
	.word	-45417899
	.word	3931473
	.word	-111740065
	.word	0
	.word	487594240
	.word	234886184
	.word	336207104
	.word	721207
	.word	4522025
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	521477919
	.word	422707200
	.word	0
	.word	0
	.word	437320789
	.word	-395967175
	.word	-164364994
	.word	-446493399
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-28640171
	.word	-395967175
	.word	905979178
	.word	207741055
	.word	-361431040
	.word	0
	.word	0
	.word	0
	.word	104460105
	.word	238680669
	.word	-229049812
	.word	70714167
	.word	-61866421
	.word	-194905806
	.word	20709376
	.word	0
	.word	-178654873
	.word	-344714439
	.word	339346516
	.word	106955071
	.word	-78253206
	.word	88016459
	.word	-44368027
	.word	0
	.word	388044546
	.word	352326208
	.word	153820416
	.word	3013710
	.word	-44040151
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	203950899
	.word	238747648
	.word	0
	.word	0
	.word	87683918
	.word	-180289218
	.word	17367089
	.word	-613020375
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	21230414
	.word	-180289218
	.word	440602714
	.word	157864575
	.word	-328728576
	.word	0
	.word	0
	.word	0
	.word	204602441
	.word	288553558
	.word	-278922691
	.word	154007875
	.word	-78971830
	.word	-78579384
	.word	20578304
	.word	0
	.word	-45745583
	.word	-178256329
	.word	121895766
	.word	39321658
	.word	-45287842
	.word	87426117
	.word	-45023144
	.word	0
	.word	370745856
	.word	268442146
	.word	320219136
	.word	219088691
	.word	38797353
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	421532977
	.word	355860480
	.word	0
	.word	0
	.word	37878343
	.word	-212925132
	.word	-32963543
	.word	-478802647
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-62064057
	.word	-212925132
	.word	956442916
	.word	440783743
	.word	-245039104
	.word	0
	.word	0
	.word	0
	.word	154336582
	.word	171312709
	.word	-212205516
	.word	137101122
	.word	-11730618
	.word	-27854008
	.word	3997696
	.word	0
	.word	-28968110
	.word	-161480133
	.word	38534487
	.word	-43777736
	.word	-45417899
	.word	3931473
	.word	-111740065
	.word	0
	.word	487594240
	.word	234886184
	.word	336207104
	.word	119732056
	.word	-327221207
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	354489138
	.word	289210368
	.word	0
	.word	0
	.word	437320789
	.word	-395967175
	.word	-164364994
	.word	-446493399
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-28640171
	.word	-395967175
	.word	905979178
	.word	207741055
	.word	-361431040
	.word	0
	.word	0
	.word	0
	.word	104460105
	.word	238680669
	.word	-229049812
	.word	70714167
	.word	-61866421
	.word	-194905806
	.word	20709376
	.word	0
	.word	-178654873
	.word	-344714439
	.word	339346516
	.word	106955071
	.word	-78253206
	.word	88016459
	.word	-44368027
	.word	0
	.word	-276827290
	.word	5437770
	.word	-345250433
	.word	-511711105
	.word	-295705217
	.word	-344792449
	.word	0
	.word	0
	.word	-277089165
	.word	-260377229
	.word	-45614550
	.word	-80544458
	.word	-29491142
	.word	20971080
	.word	-11864229
	.word	0
	.word	-111282857
	.word	-45221049
	.word	-62915516
	.word	-195757762
	.word	-113178563
	.word	87621186
	.word	20971581
	.word	-28442624
	.word	402657033
	.word	135859474
	.word	252251411
	.word	170200082
	.word	102568993
	.word	253625389
	.word	20578366
	.word	121438208
	.word	-94504364
	.word	-129040318
	.word	-12124098
	.word	-29557189
	.word	-78906050
	.word	-63244478
	.word	-11599801
	.word	54788096
	.word	252053011
	.word	118492174
	.word	302845195
	.word	219090704
	.word	202837271
	.word	252972570
	.word	237769000
	.word	288292864
	.word	-197132732
	.word	-246090904
	.word	-79430885
	.word	-47710676
	.word	3076160
	.word	-129698226
	.word	-95553962
	.word	0
	.word	20055860
	.word	170065964
	.word	187040045
	.word	3015980
	.word	521208115
	.word	120724499
	.word	270601790
	.word	0
	.word	203819821
	.word	254217002
	.word	220991533
	.word	204016177
	.word	505549354
	.word	171381043
	.word	288227417
	.word	0
	.word	170719550
	.word	254021160
	.word	270208029
	.word	19665956
	.word	304088362
	.word	19925566
	.word	288229696
	.word	0
	.word	403772693
	.word	420880155
	.word	371004195
	.word	238160441
	.word	121634381
	.word	-61670050
	.word	155579501
	.word	0
	.word	-45680547
	.word	-161815937
	.word	-195235529
	.word	-163775938
	.word	-62786487
	.word	-129173168
	.word	-145166482
	.word	0
	.word	-210964124
	.word	-211422373
	.word	-195103144
	.word	-262867370
	.word	-111938729
	.word	-312606394
	.word	4782922
	.word	305856512
	.word	451745519
	.word	451878631
	.word	485237225
	.word	635773417
	.word	686040815
	.word	569714929
	.word	704259585
	.word	688979968
	.word	-194448031
	.word	-262080168
	.word	-128583339
	.word	-145362088
	.word	71499085
	.word	-45286836
	.word	171638604
	.word	-11337728
	.word	618472670
	.word	551953890
	.word	752886510
	.word	586230001
	.word	569975803
	.word	553657858
	.word	554506019
	.word	221904896
	.word	-11863455
	.word	-111416193
	.word	-178131884
	.word	-179307959
	.word	-62196906
	.word	-211749535
	.word	-311099392
	.word	0
	.word	-127471260
	.word	6225920
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	519707395
	.word	437649408
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-110890401
	.word	39780352
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	503126528
	.word	371064832
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-63374510
	.word	-112399747
	.word	-129041631
	.word	-63898059
	.word	-46206137
	.word	-162532266
	.word	-212143519
	.word	0
	.word	-62193080
	.word	-179569337
	.word	254735173
	.word	4063297
	.word	354808136
	.word	154734646
	.word	4066376
	.word	0
	.word	636494844
	.word	653797117
	.word	620963333
	.word	704652048
	.word	655756848
	.word	455415100
	.word	205783649
	.word	0
	.word	5045066
	.word	4650315
	.word	21233729
	.word	-230096066
	.word	71237444
	.word	-213185737
	.word	88083526
	.word	0
	.word	536421361
	.word	587014659
	.word	620700165
	.word	537600773
	.word	571221771
	.word	505225754
	.word	489100098
	.word	0
	.word	0
	.word	0
	.word	-45351145
	.word	19005739
	.word	3604023
	.word	3998016
	.word	4519772
	.word	0
	.word	-277287824
	.word	-294455979
	.word	-245566887
	.word	-431492783
	.word	-229638076
	.word	-230234056
	.word	-381360078
	.word	-179699712
	.word	401808115
	.word	686895602
	.word	738405638
	.word	740434230
	.word	324141056
	.word	0
	.word	0
	.word	0
	.word	-227871903
	.word	-245697446
	.word	-296159671
	.word	-145755562
	.word	-162924986
	.word	-163185854
	.word	-146736326
	.word	37421056
	.word	368449781
	.word	486022399
	.word	486743305
	.word	588520740
	.word	239271936
	.word	0
	.word	0
	.word	0
	.word	-444668830
	.word	-412751549
	.word	-464327586
	.word	-262935954
	.word	-346296730
	.word	-211950721
	.word	0
	.word	0
	.word	-111346855
	.word	-111086740
	.word	-95617492
	.word	2949172
	.word	-46072261
	.word	-62456757
	.word	-128782490
	.word	0
	.word	-27919794
	.word	-11798195
	.word	37094706
	.word	-45874894
	.word	103480401
	.word	20970566
	.word	4391481
	.word	-28573696
	.word	186384936
	.word	53215281
	.word	3015212
	.word	36896815
	.word	69665342
	.word	103678006
	.word	53871162
	.word	71237632
	.word	-211095446
	.word	-162010254
	.word	-294718878
	.word	-361829526
	.word	-295179413
	.word	-378739088
	.word	-161418145
	.word	-77922304
	.word	235604750
	.word	151720459
	.word	352917502
	.word	552673521
	.word	585836521
	.word	719268321
	.word	786704116
	.word	354222080
	.word	-47251647
	.word	-12978339
	.word	-145947880
	.word	2752560
	.word	3668539
	.word	-112724909
	.word	-178789769
	.word	0
	.word	186844224
	.word	20777763
	.word	303631384
	.word	220007716
	.word	-161613495
	.word	-28766930
	.word	154270052
	.word	0
	.word	104007225
	.word	120915508
	.word	104270637
	.word	237242421
	.word	-11401417
	.word	-45215954
	.word	371195732
	.word	0
	.word	-144840098
	.word	-78247613
	.word	-61802923
	.word	-12187844
	.word	154797373
	.word	204607282
	.word	305205558
	.word	0
	.word	770192851
	.word	820396501
	.word	736962550
	.word	503910938
	.word	337313849
	.word	-229442741
	.word	-312353411
	.word	0
	.word	-45418660
	.word	-128456322
	.word	20643101
	.word	-14417626
	.word	36436535
	.word	3801152
	.word	-45418918
	.word	0
	.word	154468917
	.word	87424573
	.word	3670072
	.word	-213910724
	.word	-12712903
	.word	-96140231
	.word	237438003
	.word	222560256
	.word	419897081
	.word	469965828
	.word	536879871
	.word	503717382
	.word	537468691
	.word	437983774
	.word	622074914
	.word	289800192
	.word	170460974
	.word	-13433039
	.word	137627945
	.word	103744055
	.word	220793388
	.word	103941429
	.word	221316159
	.word	104857600
	.word	452992000
	.word	536615686
	.word	570957322
	.word	404103443
	.word	371202591
	.word	355015212
	.word	388960321
	.word	239534080
	.word	87426620
	.word	104531525
	.word	4652061
	.word	85919530
	.word	20708922
	.word	-45548207
	.word	-178192384
	.word	0
	.word	54526269
	.word	155123712
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	21169467
	.word	155385856
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-28967365
	.word	105250816
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	138151487
	.word	289472512
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-13631420
	.word	-62523304
	.word	3803141
	.word	168693266
	.word	219873832
	.word	3865926
	.word	-95422379
	.word	0
	.word	120721447
	.word	86770740
	.word	187759420
	.word	-12910533
	.word	371262764
	.word	237764430
	.word	3934533
	.word	0
	.word	270406176
	.word	304289309
	.word	404690726
	.word	304813097
	.word	188680507
	.word	155254622
	.word	-27658388
	.word	0
	.word	170658079
	.word	204145461
	.word	237111846
	.word	-46920408
	.word	287311660
	.word	119934258
	.word	171514411
	.word	0
	.word	353900308
	.word	437721888
	.word	471276568
	.word	388503584
	.word	471668522
	.word	322508341
	.word	373099350
	.word	0
	.word	0
	.word	0
	.word	-96274141
	.word	-114624467
	.word	-80677832
	.word	-96666818
	.word	-129828788
	.word	0
	.word	-61867705
	.word	-79300794
	.word	-129829308
	.word	-313920443
	.word	-263786173
	.word	-331420346
	.word	-264050111
	.word	-331415552
	.word	167647991
	.word	569845753
	.word	704523523
	.word	822684955
	.word	607846400
	.word	0
	.word	0
	.word	0
	.word	-78251439
	.word	-162662063
	.word	-279908791
	.word	-62196141
	.word	-146278589
	.word	-12715966
	.word	-230555589
	.word	37421056
	.word	368255474
	.word	670641918
	.word	855784454
	.word	1024538402
	.word	708706304
	.word	0
	.word	0
	.word	0
	.word	-645927333
	.word	-278862255
	.word	-580720538
	.word	-379460233
	.word	-396104850
	.word	-295248769
	.word	0
	.word	0
	.word	5307225
	.word	-111215524
	.word	-378474169
	.word	-113442763
	.word	-79497907
	.word	-145688748
	.word	-162013569
	.word	0
	.word	-211291301
	.word	-145100196
	.word	-129174441
	.word	-378607511
	.word	-162599824
	.word	-278678913
	.word	-1166029185
	.word	-763428864
	.word	70060572
	.word	169812469
	.word	886379023
	.word	469771242
	.word	652681728
	.word	669917428
	.word	1721892864
	.word	955318272
	.word	-344004228
	.word	-328276354
	.word	-411242647
	.word	-444996235
	.word	-278469003
	.word	-445325446
	.word	-161484188
	.word	-127991808
	.word	335155962
	.word	234887924
	.word	535831015
	.word	568993252
	.word	669133538
	.word	802565596
	.word	836643311
	.word	537460736
	.word	2555969
	.word	-246096513
	.word	-345637593
	.word	-80348867
	.word	-179572403
	.word	-279189653
	.word	-412097414
	.word	0
	.word	-62719154
	.word	-62392248
	.word	37486391
	.word	-112788917
	.word	-128328073
	.word	-45408236
	.word	504812671
	.word	0
	.word	570170634
	.word	637219811
	.word	670512350
	.word	1170621377
	.word	754655239
	.word	937631745
	.word	6948
	.word	0
	.word	-277879694
	.word	-94765488
	.word	-61671595
	.word	-128843960
	.word	88080707
	.word	154665029
	.word	21301061
	.word	0
	.word	1169768385
	.word	1119899062
	.word	920204509
	.word	703996928
	.word	687808014
	.word	471471909
	.word	204933953
	.word	0
	.word	-28707736
	.word	-144973441
	.word	-179505620
	.word	-164301255
	.word	-147132344
	.word	-112853947
	.word	-78973098
	.word	0
	.word	3603261
	.word	3866428
	.word	-46270397
	.word	-413863350
	.word	-79624908
	.word	37290045
	.word	-146410170
	.word	305594368
	.word	568795874
	.word	618931940
	.word	652550894
	.word	602940146
	.word	553133562
	.word	587210250
	.word	470948377
	.word	489226240
	.word	-112854461
	.word	-263324096
	.word	37616195
	.word	-46136775
	.word	-46006974
	.word	4065587
	.word	-12386745
	.word	-28639232
	.word	635381724
	.word	685450978
	.word	786377442
	.word	686305763
	.word	653535478
	.word	654126843
	.word	521411870
	.word	422313984
	.word	53937976
	.word	121047101
	.word	37943074
	.word	18877215
	.word	87359031
	.word	-29163447
	.word	-128385024
	.word	0
	.word	-62455750
	.word	121438208
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	4915784
	.word	139264000
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-12126392
	.word	238813184
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	204475185
	.word	439156736
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-46858172
	.word	-112527528
	.word	53741316
	.word	168300808
	.word	269681445
	.word	-12715191
	.word	-12125106
	.word	0
	.word	153686553
	.word	153093419
	.word	154075180
	.word	3342894
	.word	321322050
	.word	254151722
	.word	153223257
	.word	0
	.word	237179423
	.word	287511838
	.word	288166954
	.word	304945946
	.word	271976258
	.word	272108361
	.word	172226164
	.word	0
	.word	270860335
	.word	304286501
	.word	204016169
	.word	36703273
	.word	220790843
	.word	53613352
	.word	54661682
	.word	0
	.word	370546454
	.word	454369556
	.word	438050328
	.word	455217706
	.word	421990962
	.word	205919542
	.word	239536979
	.word	0
	.word	0
	.word	0
	.word	-79233000
	.word	-14352854
	.word	-30083271
	.word	-96469951
	.word	-62654126
	.word	0
	.word	-78251439
	.word	-162662063
	.word	-279908791
	.word	-62196141
	.word	-146278589
	.word	-12715966
	.word	-230555589
	.word	37421056
	.word	301342963
	.word	720843259
	.word	889208835
	.word	1141522971
	.word	792264704
	.word	0
	.word	0
	.word	0
	.word	-44958388
	.word	-112657842
	.word	-196545980
	.word	-45680052
	.word	-79496386
	.word	3800125
	.word	-147062474
	.word	37355520
	.word	301342963
	.word	720843259
	.word	889208835
	.word	1141522971
	.word	792264704
	.word	0
	.word	0
	.word	0
	.word	-595595429
	.word	-228595884
	.word	-413731751
	.word	-279191169
	.word	-229839257
	.word	-212149377
	.word	0
	.word	0
	.word	189793612
	.word	39060814
	.word	-395056558
	.word	-146931659
	.word	3928661
	.word	-212208802
	.word	-178461825
	.word	0
	.word	-61410216
	.word	-78447288
	.word	-62654392
	.word	-262539451
	.word	-12909246
	.word	70908999
	.word	-28900806
	.word	-11927552
	.word	69664810
	.word	119671581
	.word	136250917
	.word	120193832
	.word	136383787
	.word	220464175
	.word	53936698
	.word	104595456
	.word	-360716417
	.word	-411507329
	.word	-311236235
	.word	-411638155
	.word	-395189130
	.word	-512173188
	.word	-161549978
	.word	-161284096
	.word	301142263
	.word	301210603
	.word	635578840
	.word	718745809
	.word	669003480
	.word	885862103
	.word	886647789
	.word	537591808
	.word	-97057731
	.word	-229385345
	.word	-345705927
	.word	-196872889
	.word	-162665643
	.word	-262608536
	.word	-245179521
	.word	0
	.word	-64159931
	.word	4127027
	.word	-63964630
	.word	-47580619
	.word	139261774
	.word	-179107532
	.word	4455258
	.word	0
	.word	137104172
	.word	237635376
	.word	70779956
	.word	220530993
	.word	322570800
	.word	204275781
	.word	337709119
	.word	0
	.word	-211104129
	.word	-77852359
	.word	-78187682
	.word	-195297715
	.word	4718409
	.word	71366993
	.word	88084281
	.word	0
	.word	1036597458
	.word	1053708733
	.word	770450430
	.word	470753793
	.word	654384657
	.word	338039341
	.word	255197263
	.word	0
	.word	-78645912
	.word	-178527617
	.word	-162334672
	.word	-130156478
	.word	-112790965
	.word	-162531501
	.word	-195236244
	.word	0
	.word	21229896
	.word	-78907312
	.word	-346821824
	.word	-216012992
	.word	-480376501
	.word	289405002
	.word	-81527269
	.word	224067584
	.word	602808807
	.word	486348810
	.word	452993778
	.word	886319080
	.word	319889177
	.word	605886497
	.word	571416084
	.word	373882880
	.word	21168196
	.word	-163380924
	.word	5046848
	.word	4520782
	.word	121046331
	.word	37817910
	.word	254543164
	.word	38141952
	.word	619718130
	.word	636428289
	.word	571415823
	.word	404300310
	.word	521151250
	.word	521937193
	.word	605821743
	.word	356384768
	.word	4324943
	.word	4783196
	.word	-61871547
	.word	-263455174
	.word	20640590
	.word	-145490863
	.word	-211615744
	.word	0
	.word	54655301
	.word	139264000
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	337777439
	.word	455868416
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-28512682
	.word	205914112
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	304026394
	.word	605552640
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-96992444
	.word	-129502366
	.word	-212731354
	.word	-213976518
	.word	-29626295
	.word	-162729130
	.word	-145492393
	.word	0
	.word	-163445954
	.word	-45814703
	.word	1966343
	.word	-48764086
	.word	272820604
	.word	287649006
	.word	853469823
	.word	0
	.word	319819556
	.word	254022940
	.word	420814356
	.word	520887056
	.word	405405789
	.word	238554937
	.word	438757503
	.word	0
	.word	88142918
	.word	188155192
	.word	4522561
	.word	-95812298
	.word	121043532
	.word	-179110323
	.word	-28501718
	.word	0
	.word	404167440
	.word	404627229
	.word	371791402
	.word	272371508
	.word	238814030
	.word	-260369099
	.word	372775229
	.word	0
	.word	0
	.word	0
	.word	-146278107
	.word	-131271375
	.word	-164039621
	.word	-130025661
	.word	-96143793
	.word	0
	.word	-45156278
	.word	-146213304
	.word	-297012153
	.word	-180356282
	.word	-280235448
	.word	-263981003
	.word	-230951116
	.word	-180092928
	.word	167649014
	.word	536617471
	.word	554114828
	.word	622272294
	.word	339738624
	.word	0
	.word	0
	.word	0
	.word	-45156278
	.word	-146213304
	.word	-297012153
	.word	-180356282
	.word	-280235448
	.word	-263981003
	.word	-230951116
	.word	-180092928
	.word	167649014
	.word	536617471
	.word	554114828
	.word	622272294
	.word	339738624
	.word	0
	.word	0
	.word	0
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%s: %s\012\000"
.LC1:
	.ascii	"can not map slice msg virtual address!\012\000"
.LC2:
	.ascii	"chroma_lg = %d\012\000"
.LC3:
	.ascii	"can not map down msg virtual address!\012\000"
	.space	1
.LC4:
	.ascii	"line: %d, p = NULL is not expected value!\012\000"
	.space	1
.LC5:
	.ascii	"VdhId is wrong! H264HAL_V200R003_StartDec\012\000"
	.space	1
.LC6:
	.ascii	"%s: VdhId(%d) > %d\012\000"
.LC7:
	.ascii	"point of picture para null\012\000"
.LC8:
	.ascii	"picture width out of range\012\000"
.LC9:
	.ascii	"point of fst slice para null\012\000"
	.space	2
.LC10:
	.ascii	"vdm register virtual address not mapped, reset fail"
	.ascii	"ed!\012\000"
.LC11:
	.ascii	"\012\012***********************H264HAL_V200R003_Sta"
	.ascii	"rtDec is Now %d***********************\012\000"
	.space	3
.LC12:
	.ascii	"BASIC_V200R003_CFG0 = 0x%x\012\000"
.LC13:
	.ascii	"BASIC_V300R001_CFG1 = 0x%x\012\000"
.LC14:
	.ascii	"AVM_V300R001_ADDR = 0x%x\012\000"
	.space	2
.LC15:
	.ascii	"VAM_V300R001_ADDR = 0x%x\012\000"
	.space	2
.LC16:
	.ascii	"STREAM_V200R003_BASE_ADDR = 0x%x\012\000"
	.space	2
.LC17:
	.ascii	"VREG_V300R001_PART_DEC_OVER_INT_LEVEL=0x%x\012\000"
.LC18:
	.ascii	"YSTADDR_V300R001_1D = 0x%x\012\000"
.LC19:
	.ascii	"YSTRIDE_V300R001_1D = 0x%x\012\000"
.LC20:
	.ascii	"UVOFFSET_V300R001_1D = 0x%x\012\000"
	.space	3
.LC21:
	.ascii	"VREG_LINE_NUM_STADDR = 0x%x\012\000"
	.space	3
.LC22:
	.ascii	"PPFD_V300R001_BUF_ADDR = 0x%x\012\000"
	.space	1
.LC23:
	.ascii	"PPFD_V300R001_BUF_LEN = 0x%x\012\000"
	.space	2
.LC24:
	.ascii	"REF_V300R001_PIC_TYPE = 0x%x\012\000"
	.space	2
.LC25:
	.ascii	"FF_V300R001_APT_EN = 0x%x\012\000"
	.space	1
.LC26:
	.ascii	"pSlicePara = NULL!\012\000"
.LC27:
	.ascii	"line %d Set slice msg not wrong!\012\000"
	.space	2
.LC28:
	.ascii	"line %d tmp_pSlicePara is NULL!\012\000"
	.space	3
.LC29:
	.ascii	"!!! no slice to dec, add up msg report.\000"
	.bss
	.align	2
.LANCHOR2 = . + 0
	.type	StartCnt.39474, %object
	.size	StartCnt.39474, 4
StartCnt.39474:
	.space	4
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
