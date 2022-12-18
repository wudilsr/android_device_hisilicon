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
	.file	"scd_drv.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(scd_drv)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiSCDV200/.scd_drv.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiSCDV200/scd_drv.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/vfmw/vfmw_v4.0/firmware/driver/HiSCDV200/scd_drv.o -O2 -Wall
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
	.global	GetInstIDByRawArray
	.type	GetInstIDByRawArray, %function
GetInstIDByRawArray:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp185,
	movt	r3, #:upper16:.LANCHOR0	@ tmp185,
	ldr	r2, [r3, #40]	@ temp.760, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.760,
	beq	.L2	@,
	add	r2, r2, #200	@ tmp153, temp.760,
	cmp	r2, r0	@ tmp153, pRawArray
	moveq	r0, #0	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L2:
	ldr	r2, [r3, #88]	@ temp.762, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.762,
	beq	.L4	@,
	add	r1, r2, #200	@ tmp155, temp.762,
	cmp	r1, r0	@ tmp155, pRawArray
	moveq	r0, #1	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L4:
	ldr	r2, [r3, #136]	@ temp.764, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.764,
	beq	.L5	@,
	add	ip, r2, #200	@ tmp157, temp.764,
	cmp	ip, r0	@ tmp157, pRawArray
	moveq	r0, #2	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L5:
	ldr	r2, [r3, #184]	@ temp.766, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.766,
	beq	.L6	@,
	add	r2, r2, #200	@ tmp159, temp.766,
	cmp	r2, r0	@ tmp159, pRawArray
	moveq	r0, #3	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L6:
	ldr	r2, [r3, #232]	@ temp.768, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.768,
	beq	.L7	@,
	add	r1, r2, #200	@ tmp161, temp.768,
	cmp	r1, r0	@ tmp161, pRawArray
	moveq	r0, #4	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L7:
	ldr	r2, [r3, #280]	@ temp.770, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.770,
	beq	.L8	@,
	add	ip, r2, #200	@ tmp163, temp.770,
	cmp	ip, r0	@ tmp163, pRawArray
	moveq	r0, #5	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L8:
	ldr	r2, [r3, #328]	@ temp.772, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.772,
	beq	.L9	@,
	add	r2, r2, #200	@ tmp165, temp.772,
	cmp	r2, r0	@ tmp165, pRawArray
	moveq	r0, #6	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L9:
	ldr	r2, [r3, #376]	@ temp.774, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.774,
	beq	.L10	@,
	add	r1, r2, #200	@ tmp167, temp.774,
	cmp	r1, r0	@ tmp167, pRawArray
	moveq	r0, #7	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L10:
	ldr	r2, [r3, #424]	@ temp.776, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.776,
	beq	.L11	@,
	add	ip, r2, #200	@ tmp169, temp.776,
	cmp	ip, r0	@ tmp169, pRawArray
	moveq	r0, #8	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L11:
	ldr	r2, [r3, #472]	@ temp.778, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.778,
	beq	.L12	@,
	add	r2, r2, #200	@ tmp171, temp.778,
	cmp	r2, r0	@ tmp171, pRawArray
	moveq	r0, #9	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L12:
	ldr	r2, [r3, #520]	@ temp.780, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.780,
	beq	.L13	@,
	add	r1, r2, #200	@ tmp173, temp.780,
	cmp	r1, r0	@ tmp173, pRawArray
	moveq	r0, #10	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L13:
	ldr	r2, [r3, #568]	@ temp.782, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.782,
	beq	.L14	@,
	add	ip, r2, #200	@ tmp175, temp.782,
	cmp	ip, r0	@ tmp175, pRawArray
	moveq	r0, #11	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L14:
	ldr	r2, [r3, #616]	@ temp.784, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.784,
	beq	.L15	@,
	add	r2, r2, #200	@ tmp177, temp.784,
	cmp	r2, r0	@ tmp177, pRawArray
	moveq	r0, #12	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L15:
	ldr	r2, [r3, #664]	@ temp.786, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.786,
	beq	.L16	@,
	add	r1, r2, #200	@ tmp179, temp.786,
	cmp	r1, r0	@ tmp179, pRawArray
	moveq	r0, #13	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L16:
	ldr	r2, [r3, #712]	@ temp.788, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.788,
	beq	.L17	@,
	add	ip, r2, #200	@ tmp181, temp.788,
	cmp	ip, r0	@ tmp181, pRawArray
	moveq	r0, #14	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L17:
	ldr	r3, [r3, #760]	@ D.49612, <variable>.pSmInstArray
	cmp	r3, #0	@ D.49612,
	beq	.L18	@,
	add	r3, r3, #200	@ tmp183, D.49612,
	cmp	r3, r0	@ tmp183, pRawArray
	moveq	r0, #15	@ i,
	ldmeqfd	sp, {fp, sp, pc}	@
.L18:
	mvn	r0, #0	@ i,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	GetInstIDByRawArray, .-GetInstIDByRawArray
	.align	2
	.global	GetRawState
	.type	GetRawState, %function
GetRawState:
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
	cmp	r0, #15	@ SmID,
	bls	.L25	@,
.L22:
	mvn	r0, #3	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
.L25:
	add	r0, r0, r0, asl #1	@, tmp141, SmID, SmID,
	movw	r1, #:lower16:.LANCHOR0	@ tmp137,
	movt	r1, #:upper16:.LANCHOR0	@ tmp137,
	add	r3, r1, r0, asl #4	@, tmp143, tmp137, tmp141,
	ldr	r3, [r3, #40]	@ D.49699, <variable>.pSmInstArray
	cmp	r3, #0	@ D.49699,
	beq	.L22	@,
	movw	ip, #:lower16:98508	@ tmp145,
	movt	ip, #:upper16:98508	@ tmp145,
	movw	r2, #:lower16:98512	@ tmp155,
	movt	r2, #:upper16:98512	@ tmp155,
	ldr	r0, [r3, ip]	@ <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Tail
	ldr	ip, [r3, r2]	@ <variable>.RawPacketArray.History, <variable>.RawPacketArray.History
	add	r3, r0, #1	@ tmp146, <variable>.RawPacketArray.Tail,
	mov	r2, r3, asr #31	@ tmp149, tmp146,
	mov	r2, r2, lsr #22	@ tmp150, tmp149,
	add	r1, r3, r2	@ tmp151, tmp146, tmp150
	mov	r3, r1, asl #22	@ tmp152, tmp151,
	mov	r1, r3, lsr #22	@ tmp152, tmp152,
	rsb	r3, r2, r1	@ tmp154, tmp150, tmp152
	cmp	r3, ip	@ tmp154, <variable>.RawPacketArray.History
	movne	r0, #0	@ Ret,
	ldmnefd	sp, {fp, sp, pc}	@
	b	.L22	@
	.fnend
	.size	GetRawState, .-GetRawState
	.align	2
	.global	SetFirstOffset
	.type	SetFirstOffset, %function
SetFirstOffset:
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
	cmp	r0, #0	@ pRawStreamArray
	bne	.L31	@,
.L27:
	mvn	r0, #0	@ D.49755,
	ldmfd	sp, {fp, sp, pc}	@
.L31:
	movw	ip, #:lower16:98308	@ tmp140,
	movt	ip, #:upper16:98308	@ tmp140,
	mov	r2, #98304	@ tmp139,
	ldr	r2, [r0, r2]	@ D.49756, <variable>.Head
	ldr	r3, [r0, ip]	@ <variable>.Tail, <variable>.Tail
	cmp	r2, r3	@ D.49756, <variable>.Tail
	mvneq	r0, #2	@ D.49755,
	ldmeqfd	sp, {fp, sp, pc}	@
	add	ip, r2, r2, asl #1	@, tmp146, D.49756, D.49756,
	movw	r3, #:lower16:98316	@ tmp142,
	movt	r3, #:upper16:98316	@ tmp142,
	add	r2, r0, ip, asl #5	@, tmp148, pRawStreamArray, tmp146,
	ldr	ip, [r0, r3]	@ <variable>.FirstPacketOffset, <variable>.FirstPacketOffset
	ldr	r2, [r2, #8]	@ <variable>.Length, <variable>.Length
	add	r1, r1, ip	@ TargetOffset, Offset, <variable>.FirstPacketOffset
	cmp	r1, r2	@ TargetOffset, <variable>.Length
	strlt	r1, [r0, r3]	@ TargetOffset, <variable>.FirstPacketOffset
	movlt	r0, #0	@ D.49755,
	ldmltfd	sp, {fp, sp, pc}	@
	b	.L27	@
	.fnend
	.size	SetFirstOffset, .-SetFirstOffset
	.align	2
	.global	GetFirstOffset
	.type	GetFirstOffset, %function
GetFirstOffset:
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
	cmp	r0, #0	@ pRawStreamArray,
	cmpne	r1, #0	@, pOffset,
	mov	r3, r0	@ pRawStreamArray, pRawStreamArray
	movne	r0, #0	@, tmp143
	moveq	r0, #1	@, tmp143
	mvneq	r0, #0	@ D.49775,
	ldmeqfd	sp, {fp, sp, pc}	@
	movw	r2, #:lower16:98308	@ tmp145,
	movt	r2, #:upper16:98308	@ tmp145,
	mov	ip, #98304	@ tmp144,
	ldr	r2, [r3, r2]	@ <variable>.Tail, <variable>.Tail
	ldr	ip, [r3, ip]	@ <variable>.Head, <variable>.Head
	cmp	ip, r2	@ <variable>.Head, <variable>.Tail
	movwne	r2, #:lower16:98316	@ tmp148,
	movtne	r2, #:upper16:98316	@ tmp148,
	mvneq	r0, #2	@ D.49775,
	ldrne	r3, [r3, r2]	@ <variable>.FirstPacketOffset, <variable>.FirstPacketOffset
	strne	r3, [r1, #0]	@ <variable>.FirstPacketOffset,* pOffset
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	GetFirstOffset, .-GetFirstOffset
	.align	2
	.global	GetRawStreamSize
	.type	GetRawStreamSize, %function
GetRawStreamSize:
	.fnstart
.LFB1546:
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
	cmp	r0, #0	@ pRawStreamArray
	bne	.L41	@,
.L38:
	mvn	r0, #0	@ D.49999,
	ldmfd	sp, {fp, sp, pc}	@
.L41:
	movw	ip, #:lower16:98324	@ tmp139,
	movt	ip, #:upper16:98324	@ tmp139,
	movw	r3, #:lower16:98316	@ tmp140,
	movt	r3, #:upper16:98316	@ tmp140,
	ldr	r2, [r0, ip]	@ D.50000, <variable>.RawTotalSize
	str	r2, [r1, #0]	@ D.50000,* pStreamSize
	ldr	ip, [r0, r3]	@ <variable>.FirstPacketOffset, <variable>.FirstPacketOffset
	rsb	r3, ip, r2	@ D.50003, <variable>.FirstPacketOffset, D.50000
	str	r3, [r1, #0]	@ D.50003,* pStreamSize
	cmp	r3, #0	@ D.50003,
	movge	r0, #0	@ D.49999,
	ldmgefd	sp, {fp, sp, pc}	@
	b	.L38	@
	.fnend
	.size	GetRawStreamSize, .-GetRawStreamSize
	.align	2
	.global	GetRawStreamNum
	.type	GetRawStreamNum, %function
GetRawStreamNum:
	.fnstart
.LFB1547:
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
	cmp	r0, #0	@ pRawStreamArray
	mvneq	r0, #0	@ D.50012,
	ldmeqfd	sp, {fp, sp, pc}	@
	movw	r3, #:lower16:98308	@ tmp138,
	movt	r3, #:upper16:98308	@ tmp138,
	mov	ip, #98304	@ tmp139,
	ldr	r2, [r0, ip]	@ <variable>.Head, <variable>.Head
	ldr	ip, [r0, r3]	@ <variable>.Tail, <variable>.Tail
	mov	r0, #0	@ D.50012,
	rsb	r3, r2, ip	@ D.50015, <variable>.Head, <variable>.Tail
	str	r3, [r1, #0]	@ D.50015,* pStreamNum
	cmp	r3, #0	@ D.50015,
	addlt	r3, r3, #1024	@ tmp142, D.50015,
	strlt	r3, [r1, #0]	@ tmp142,* pStreamNum
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	GetRawStreamNum, .-GetRawStreamNum
	.align	2
	.global	GetRawStreamNumInBuffer
	.type	GetRawStreamNumInBuffer, %function
GetRawStreamNumInBuffer:
	.fnstart
.LFB1548:
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
	cmp	r0, #0	@ pRawStreamArray
	mvneq	r0, #0	@ D.50026,
	ldmeqfd	sp, {fp, sp, pc}	@
	movw	ip, #:lower16:98308	@ tmp138,
	movw	r3, #:lower16:98312	@ tmp139,
	movt	ip, #:upper16:98308	@ tmp138,
	movt	r3, #:upper16:98312	@ tmp139,
	ldr	r2, [r0, ip]	@ <variable>.Tail, <variable>.Tail
	ldr	ip, [r0, r3]	@ <variable>.History, <variable>.History
	mov	r0, #0	@ D.50026,
	rsb	r3, ip, r2	@ D.50029, <variable>.History, <variable>.Tail
	str	r3, [r1, #0]	@ D.50029,* pStreamNum
	cmp	r3, #0	@ D.50029,
	addlt	r3, r3, #1024	@ tmp142, D.50029,
	strlt	r3, [r1, #0]	@ tmp142,* pStreamNum
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	GetRawStreamNumInBuffer, .-GetRawStreamNumInBuffer
	.align	2
	.global	GetSegBuf
	.type	GetSegBuf, %function
GetSegBuf:
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
	cmp	r0, #0	@ pStreamSegArray,
	cmpne	r1, #0	@, pBufAddr,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r2, #0	@ pBufLength,
	ldmeqfd	sp, {fp, sp, pc}	@
	movw	ip, #:lower16:92184	@ tmp143,
	movt	ip, #:upper16:92184	@ tmp143,
	movw	r3, #:lower16:92188	@ tmp145,
	movt	r3, #:upper16:92188	@ tmp145,
	ldr	ip, [r0, ip]	@ <variable>.SegBufPhyAddr, <variable>.SegBufPhyAddr
	str	ip, [r1, #0]	@ <variable>.SegBufPhyAddr,* pBufAddr
	ldr	r3, [r0, r3]	@ <variable>.SegBufSize, <variable>.SegBufSize
	str	r3, [r2, #0]	@ <variable>.SegBufSize,* pBufLength
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	GetSegBuf, .-GetSegBuf
	.align	2
	.global	GetFreeSegBuf
	.type	GetFreeSegBuf, %function
GetFreeSegBuf:
	.fnstart
.LFB1552:
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
	cmp	r0, #0	@ pStreamSegArray,
	cmpne	r1, #0	@, pAddr,
	movne	r3, #0	@, tmp146
	moveq	r3, #1	@, tmp146
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r2, #0	@ pLength,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	movw	ip, #:lower16:92196	@ tmp147,
	movt	ip, #:upper16:92196	@ tmp147,
	movw	r4, #:lower16:92192	@ tmp151,
	movt	r4, #:upper16:92192	@ tmp151,
	ldr	r5, [r0, ip]	@ <variable>.SegBufWriteAddr, <variable>.SegBufWriteAddr
	str	r5, [r1, #0]	@ <variable>.SegBufWriteAddr,* pAddr
	str	r3, [r2, #0]	@ tmp146,* pLength
	ldr	r1, [r0, ip]	@ temp.976, <variable>.SegBufWriteAddr
	ldr	ip, [r0, r4]	@ D.50102, <variable>.SegBufReadAddr
	cmp	r1, ip	@ temp.976, D.50102
	bgt	.L61	@,
	movw	r3, #:lower16:92188	@ tmp156,
	movt	r3, #:upper16:92188	@ tmp156,
	sublt	ip, ip, #1	@ tmp155, D.50102,
	ldrge	r3, [r0, r3]	@ prephitmp.965, <variable>.SegBufSize
	rsblt	r1, r1, ip	@ Len, temp.976, tmp155
	ldrlt	r3, [r0, r3]	@ prephitmp.965, <variable>.SegBufSize
	subge	r1, r3, #1	@ Len, prephitmp.965,
	cmp	r1, r3	@ Len, prephitmp.965
	strle	r1, [r2, #0]	@ Len,* pLength
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L61:
	movw	r3, #:lower16:92188	@ tmp152,
	movt	r3, #:upper16:92188	@ tmp152,
	ldr	r3, [r0, r3]	@ prephitmp.965, <variable>.SegBufSize
	add	ip, ip, r3	@ tmp153, D.50102, prephitmp.965
	sub	r0, ip, #1	@ tmp154, tmp153,
	rsb	r1, r1, r0	@ Len, temp.976, tmp154
	cmp	r1, r3	@ Len, prephitmp.965
	strle	r1, [r2, #0]	@ Len,* pLength
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	GetFreeSegBuf, .-GetFreeSegBuf
	.align	2
	.global	GetSegStreamSize
	.type	GetSegStreamSize, %function
GetSegStreamSize:
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
	subs	r3, r0, #0	@ pSegStreamArray, pSegStreamArray
	movwne	r2, #:lower16:92200	@ tmp137,
	movtne	r2, #:upper16:92200	@ tmp137,
	mvneq	r0, #0	@ D.50266,
	movne	r0, #0	@ D.50266,
	ldrne	r3, [r3, r2]	@ <variable>.SegTotalSize, <variable>.SegTotalSize
	strne	r3, [r1, #0]	@ <variable>.SegTotalSize,* pStreamSize
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	GetSegStreamSize, .-GetSegStreamSize
	.align	2
	.global	GetSegStreamNum
	.type	GetSegStreamNum, %function
GetSegStreamNum:
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
	cmp	r0, #0	@ pSegStreamArray
	mvneq	r0, #0	@ D.50274,
	ldmeqfd	sp, {fp, sp, pc}	@
	movw	ip, #:lower16:92172	@ tmp138,
	movw	r3, #:lower16:92168	@ tmp139,
	movt	ip, #:upper16:92172	@ tmp138,
	movt	r3, #:upper16:92168	@ tmp139,
	ldr	r2, [r0, ip]	@ <variable>.Tail, <variable>.Tail
	ldr	ip, [r0, r3]	@ <variable>.Head, <variable>.Head
	mov	r0, #0	@ D.50274,
	rsb	r3, ip, r2	@ D.50277, <variable>.Head, <variable>.Tail
	str	r3, [r1, #0]	@ D.50277,* pStreamNum
	cmp	r3, #0	@ D.50277,
	addlt	r3, r3, #1152	@ tmp142, D.50277,
	strlt	r3, [r1, #0]	@ tmp142,* pStreamNum
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	GetSegStreamNum, .-GetSegStreamNum
	.align	2
	.global	GetFreshSegStream
	.type	GetFreshSegStream, %function
GetFreshSegStream:
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
	cmp	r0, #0	@ pSegStreamArray
	ldmeqfd	sp, {fp, sp, pc}	@
	movw	ip, #:lower16:92208	@ tmp136,
	movt	ip, #:upper16:92208	@ tmp136,
	movw	r3, #:lower16:92204	@ tmp138,
	movt	r3, #:upper16:92204	@ tmp138,
	ldr	ip, [r0, ip]	@ <variable>.SegFreshNum, <variable>.SegFreshNum
	str	ip, [r1, #0]	@ <variable>.SegFreshNum,* pFreshNum
	ldr	r3, [r0, r3]	@ <variable>.SegFreshSize, <variable>.SegFreshSize
	str	r3, [r2, #0]	@ <variable>.SegFreshSize,* pFreshSize
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	GetFreshSegStream, .-GetFreshSegStream
	.align	2
	.global	SCDDRV_PrepareSleep
	.type	SCDDRV_PrepareSleep, %function
SCDDRV_PrepareSleep:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp136,
	movt	r3, #:upper16:.LANCHOR0	@ tmp136,
	add	r2, r3, r0, asl #2	@, tmp139, tmp136, ScdId,
	ldr	r1, [r2, #768]	@ tmp141, s_eScdDrvSleepStage
	cmp	r1, #0	@ tmp141,
	mvnne	r0, #0	@ ret,
	ldmnefd	sp, {fp, sp, pc}	@
	add	r0, r0, r0, asl #1	@, tmp146, ScdId, ScdId,
	add	r3, r3, r0, asl #5	@, tmp148, tmp136, tmp146,
	ldr	r0, [r3, #856]	@ <variable>.SCDState, <variable>.SCDState
	cmp	r0, #0	@ <variable>.SCDState,
	moveq	r3, #2	@ tmp156,
	movne	r3, #1	@ tmp162,
	streq	r3, [r2, #768]	@ tmp156, s_eScdDrvSleepStage
	movne	r0, r1	@ ret, tmp141
	strne	r3, [r2, #768]	@ tmp162, s_eScdDrvSleepStage
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SCDDRV_PrepareSleep, .-SCDDRV_PrepareSleep
	.align	2
	.global	SCDDRV_GetSleepStage
	.type	SCDDRV_GetSleepStage, %function
SCDDRV_GetSleepStage:
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
	movw	r1, #:lower16:.LANCHOR0	@ tmp136,
	movt	r1, #:upper16:.LANCHOR0	@ tmp136,
	add	r3, r1, r0, asl #2	@, tmp139, tmp136, ScdId,
	ldr	r0, [r3, #768]	@, s_eScdDrvSleepStage
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SCDDRV_GetSleepStage, .-SCDDRV_GetSleepStage
	.align	2
	.global	SCDDRV_ForceSleep
	.type	SCDDRV_ForceSleep, %function
SCDDRV_ForceSleep:
	.fnstart
.LFB1561:
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
	movw	r1, #:lower16:.LANCHOR0	@ tmp134,
	movt	r1, #:upper16:.LANCHOR0	@ tmp134,
	add	r3, r1, r0, asl #2	@, tmp137, tmp134, ScdId,
	ldr	r2, [r3, #768]	@ tmp139, s_eScdDrvSleepStage
	cmp	r2, #2	@ tmp139,
	movne	r2, #2	@ tmp145,
	strne	r2, [r3, #768]	@ tmp145, s_eScdDrvSleepStage
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SCDDRV_ForceSleep, .-SCDDRV_ForceSleep
	.align	2
	.global	SM_Start
	.type	SM_Start, %function
SM_Start:
	.fnstart
.LFB1572:
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
	add	r0, r0, r0, asl #1	@, tmp140, SmID, SmID,
	movw	r1, #:lower16:.LANCHOR0	@ tmp136,
	movt	r1, #:upper16:.LANCHOR0	@ tmp136,
	add	r3, r1, r0, asl #4	@, tmp142, tmp136, tmp140,
	ldr	r3, [r3, #40]	@ D.50748, <variable>.pSmInstArray
	cmp	r3, #0	@ D.50748,
	beq	.L85	@,
	ldr	r2, [r3, #64]	@ <variable>.Config.BufSize, <variable>.Config.BufSize
	cmp	r2, #0	@ <variable>.Config.BufSize,
	beq	.L85	@,
	movw	r1, #:lower16:190872	@ tmp145,
	movt	r1, #:upper16:190872	@ tmp145,
	ldr	ip, [r3, r1]	@ <variable>.Mode, <variable>.Mode
	cmp	ip, #0	@ <variable>.Mode,
	moveq	ip, #1	@ tmp148,
	streq	ip, [r3, r1]	@ tmp148, <variable>.Mode
.L85:
	mvn	r0, #6	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SM_Start, .-SM_Start
	.align	2
	.global	SM_Stop
	.type	SM_Stop, %function
SM_Stop:
	.fnstart
.LFB1573:
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
	add	r1, r0, r0, asl #1	@, tmp144, SmID, SmID,
	movw	r3, #:lower16:.LANCHOR0	@ tmp140,
	movt	r3, #:upper16:.LANCHOR0	@ tmp140,
	add	r0, r3, r1, asl #4	@, tmp146, tmp140, tmp144,
	ldr	r1, [r0, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r1, #0	@ pSmInstArray,
	beq	.L88	@,
	movw	r2, #:lower16:190872	@ tmp148,
	movt	r2, #:upper16:190872	@ tmp148,
	ldr	ip, [r1, r2]	@ <variable>.Mode, <variable>.Mode
	cmp	ip, #0	@ <variable>.Mode,
	bne	.L95	@,
.L88:
	mov	r0, #0	@ D.50768,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L95:
	movw	r0, #:lower16:190860	@ tmp150,
	movt	r0, #:upper16:190860	@ tmp150,
	ldr	r0, [r1, r0]	@ <variable>.ScdID, <variable>.ScdID
	cmp	r0, #0	@ <variable>.ScdID,
	ble	.L96	@,
.L89:
	mvn	r0, #6	@ D.50768,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L96:
	mov	r4, #96	@ tmp158,
	mov	ip, #0	@ tmp153,
	mla	r3, r4, r0, r3	@ tmp159, tmp158, <variable>.ScdID, tmp140
	str	ip, [r1, r2]	@ tmp153, <variable>.Mode
	ldr	r3, [r3, #856]	@ <variable>.SCDState, <variable>.SCDState
	cmp	r3, ip	@ <variable>.SCDState,
	beq	.L88	@,
	mov	r3, ip	@ i, tmp153
.L90:
	add	r3, r3, #2	@ i, i,
	cmp	r3, #50	@ i,
	bne	.L90	@,
	b	.L89	@
	.fnend
	.size	SM_Stop, .-SM_Stop
	.align	2
	.global	SM_GetInfo
	.type	SM_GetInfo, %function
SM_GetInfo:
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
	cmp	r0, #15	@ SmID,
	bhi	.L98	@,
	add	r0, r0, r0, asl #1	@, tmp145, SmID, SmID,
	movw	r2, #:lower16:.LANCHOR0	@ tmp141,
	movt	r2, #:upper16:.LANCHOR0	@ tmp141,
	add	r3, r2, r0, asl #4	@, tmp147, tmp141, tmp145,
	ldr	r3, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r3, #0	@ pSmInstArray,
	beq	.L104	@,
	movw	r2, #:lower16:190872	@ tmp151,
	movt	r2, #:upper16:190872	@ tmp151,
	movw	ip, #:lower16:204740	@ tmp154,
	movt	ip, #:upper16:204740	@ tmp154,
	ldr	r4, [r3, r2]	@ <variable>.Mode, <variable>.Mode
	movw	r0, #:lower16:98508	@ tmp156,
	movw	r2, #:lower16:98504	@ tmp157,
	movt	r0, #:upper16:98508	@ tmp156,
	movt	r2, #:upper16:98504	@ tmp157,
	strb	r4, [r1, #0]	@ <variable>.Mode, <variable>.InstMode
	ldr	r4, [r3, ip]	@ <variable>.numReadSegFail, <variable>.numReadSegFail
	str	r4, [r1, #20]	@ <variable>.numReadSegFail, <variable>.numReadSegFail
	ldr	ip, [r3, r2]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Head
	movw	r2, #:lower16:98524	@ tmp161,
	ldr	r0, [r3, r0]	@ <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Tail
	movt	r2, #:upper16:98524	@ tmp161,
	rsb	r4, ip, r0	@ D.53541, <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Tail
	str	r4, [r1, #4]	@ D.53541, <variable>.RawNum
	cmp	r4, #0	@ D.53541,
	movw	ip, #:lower16:98516	@ tmp162,
	addlt	r4, r4, #1024	@ tmp160, D.53541,
	strlt	r4, [r1, #4]	@ tmp160, <variable>.RawNum
	ldr	r4, [r3, r2]	@ D.53551, <variable>.RawPacketArray.RawTotalSize
	movt	ip, #:upper16:98516	@ tmp162,
	movw	r0, #:lower16:190700	@ tmp165,
	movw	r2, #:lower16:190696	@ tmp166,
	movt	r0, #:upper16:190700	@ tmp165,
	movt	r2, #:upper16:190696	@ tmp166,
	str	r4, [r1, #12]	@ D.53551, <variable>.TotalRawSize
	ldr	ip, [r3, ip]	@ <variable>.RawPacketArray.FirstPacketOffset, <variable>.RawPacketArray.FirstPacketOffset
	rsb	r4, ip, r4	@ tmp164, <variable>.RawPacketArray.FirstPacketOffset, D.53551
	str	r4, [r1, #12]	@ tmp164, <variable>.TotalRawSize
	ldr	r0, [r3, r0]	@ <variable>.StreamSegArray.Tail, <variable>.StreamSegArray.Tail
	ldr	r2, [r3, r2]	@ <variable>.StreamSegArray.Head, <variable>.StreamSegArray.Head
	rsb	ip, r2, r0	@ D.53558, <variable>.StreamSegArray.Head, <variable>.StreamSegArray.Tail
	movw	r2, #:lower16:190728	@ tmp170,
	movt	r2, #:upper16:190728	@ tmp170,
	cmp	ip, #0	@ D.53558,
	str	ip, [r1, #8]	@ D.53558, <variable>.SegNum
	addlt	ip, ip, #1152	@ tmp169, D.53558,
	strlt	ip, [r1, #8]	@ tmp169, <variable>.SegNum
	mov	r0, #0	@ D.50784,
	ldr	ip, [r3, r2]	@ <variable>.StreamSegArray.SegTotalSize, <variable>.StreamSegArray.SegTotalSize
	str	ip, [r1, #16]	@ <variable>.StreamSegArray.SegTotalSize, <variable>.TotalSegSize
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L104:
	cmp	r1, #0	@ pSmInstInfo,
	strneb	r3, [r1, #0]	@ pSmInstArray, <variable>.InstMode
	mvnne	r0, #0	@ D.50784,
	ldmnefd	sp, {r3, r4, fp, sp, pc}	@
.L98:
	mvn	r0, #0	@ D.50784,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	SM_GetInfo, .-SM_GetInfo
	.align	2
	.global	SetInstMode
	.type	SetInstMode, %function
SetInstMode:
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
	add	ip, r0, r0, asl #1	@, tmp142, SmID, SmID,
	movw	r3, #:lower16:.LANCHOR0	@ tmp138,
	sub	r2, r1, #1	@ tmp146, Mode,
	movt	r3, #:upper16:.LANCHOR0	@ tmp138,
	cmp	r2, #1	@ tmp146,
	add	r0, r3, ip, asl #4	@, tmp144, tmp138, tmp142,
	ldr	r3, [r0, #40]	@ pSmInstArray, <variable>.pSmInstArray
	bls	.L109	@,
.L106:
	mvn	r0, #0	@ D.51163,
	ldmfd	sp, {fp, sp, pc}	@
.L109:
	cmp	r3, #0	@ pSmInstArray,
	beq	.L106	@,
	movw	r2, #:lower16:190872	@ tmp147,
	movt	r2, #:upper16:190872	@ tmp147,
	mov	r0, #0	@ D.51163,
	str	r1, [r3, r2]	@ Mode, <variable>.Mode
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SetInstMode, .-SetInstMode
	.align	2
	.global	CheckScdStateReg
	.type	CheckScdStateReg, %function
CheckScdStateReg:
	.fnstart
.LFB1588:
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
	ldr	r3, [r0, #16]	@ <variable>.ScdRollAddr, <variable>.ScdRollAddr
	cmp	r3, #0	@ <variable>.ScdRollAddr,
	mvneq	r0, #6	@,,
	movne	r0, #0	@,,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	CheckScdStateReg, .-CheckScdStateReg
	.align	2
	.global	ScdParseUpMsgInfo
	.type	ScdParseUpMsgInfo, %function
ScdParseUpMsgInfo:
	.fnstart
.LFB1589:
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
	cmp	r1, #0	@ ParseUpMsgInfo
	mvneq	r5, #0	@ D.51445,
	beq	.L116	@,
	ldr	r5, [r0, #12]	@ <variable>.ModeFlag, <variable>.ModeFlag
	ldrb	r4, [r1, #72]	@ zero_extendqisi2	@,
	mul	r2, r2, r3	@ D.51451, SegNum, UpMsgStepNum
	cmp	r5, #1	@ <variable>.ModeFlag,
	bfceq	r4, #0, #1	@ tmp142,,
	orrne	r4, r4, #1	@ tmp146, tmp145,
	strb	r4, [r1, #72]	@ tmp146,
	mov	r5, #0	@ D.51445,
	ldr	r3, [r0, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	add	ip, r2, #2	@ tmp153, D.51451,
	ldrb	r4, [r1, #72]	@ zero_extendqisi2	@,
	ldr	r3, [r3, r2, asl #2]	@ tmp150,* <variable>.pScdUpMsg
	mov	r3, r3, lsr #31	@ tmp149, tmp150,
	bfi	r4, r3, #1, #1	@ tmp151, tmp149,,
	strb	r4, [r1, #72]	@ tmp151,
	ldr	r2, [r0, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	uxtb	r3, r4	@ tmp163, tmp151
	ldr	r2, [r2, ip, asl #2]	@ tmp156,* <variable>.pScdUpMsg
	ubfx	r2, r2, #16, #1	@ tmp158, tmp156,,
	bfi	r3, r2, #2, #1	@ tmp163, tmp158,,
	strb	r3, [r1, #72]	@ tmp163,
	ldr	r2, [r0, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	uxtb	r3, r3	@ tmp174, tmp163
	ldr	r2, [r2, ip, asl #2]	@ tmp167,* <variable>.pScdUpMsg
	ubfx	r2, r2, #4, #3	@ tmp171, tmp167,,
	bfi	r3, r2, #3, #4	@ tmp174, tmp171,,
	strb	r3, [r1, #72]	@ tmp174,
	ldr	r2, [r0, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	ldrh	r3, [r1, #72]	@,
	ldr	r0, [r2, ip, asl #2]	@ tmp177,* <variable>.pScdUpMsg
	and	r2, r0, #7	@ tmp181, tmp177,
	bfi	r3, r2, #7, #4	@ tmp184, tmp181,,
	strh	r3, [r1, #72]	@ movhi	@ tmp184,
.L116:
	mov	r0, r5	@, D.51445
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	ScdParseUpMsgInfo, .-ScdParseUpMsgInfo
	.align	2
	.global	CheckSegValid
	.type	CheckSegValid, %function
CheckSegValid:
	.fnstart
.LFB1591:
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
	cmp	r0, #0	@ pSegPacket
	mvneq	r0, #0	@ D.51599,
	ldmeqfd	sp, {fp, sp, pc}	@
	ldr	r3, [r0, #8]	@ <variable>.PhyAddr, <variable>.PhyAddr
	cmp	r3, #0	@ <variable>.PhyAddr,
	bne	.L125	@,
.L123:
	mvn	r0, #6	@ D.51599,
	ldmfd	sp, {fp, sp, pc}	@
.L125:
	ldr	r2, [r0, #0]	@ <variable>.VirAddr, <variable>.VirAddr
	cmp	r2, #0	@ <variable>.VirAddr,
	beq	.L123	@,
	ldr	ip, [r0, #12]	@ <variable>.LenInByte, <variable>.LenInByte
	cmp	ip, r1	@ <variable>.LenInByte, SegFreeBufLen
	movle	r0, #0	@ D.51599,
	ldmlefd	sp, {fp, sp, pc}	@
	b	.L123	@
	.fnend
	.size	CheckSegValid, .-CheckSegValid
	.align	2
	.global	IsVopHeader
	.type	IsVopHeader, %function
IsVopHeader:
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
	cmp	r0, #1	@ ModeFlag,
	beq	.L133	@,
	cmp	r0, #2	@ ModeFlag,
	beq	.L134	@,
.L129:
	movw	ip, #:lower16:-33488896	@ tmp142,
	movt	ip, #:upper16:-33488896	@ tmp142,
	cmp	r1, ip	@ StartCode, tmp142
	mov	r0, #0	@ flag,
	ldmnefd	sp, {fp, sp, pc}	@
.L128:
	mov	r0, #1	@ flag,
	ldmfd	sp, {fp, sp, pc}	@
.L134:
	ubfx	r2, r1, #16, #8	@ tmp139, StartCode,,
	movw	ip, #:lower16:-33488896	@ tmp142,
	sub	r0, r2, #128	@ tmp140, tmp139,
	movt	ip, #:upper16:-33488896	@ tmp142,
	cmp	r0, #3	@ tmp140,
	movhi	r0, #0	@, flag
	movls	r0, #1	@, flag
	cmp	r1, ip	@ StartCode, tmp142
	ldmnefd	sp, {fp, sp, pc}	@
	b	.L128	@
.L133:
	movw	r3, #:lower16:-1241448448	@ tmp137,
	movt	r3, #:upper16:-1241448448	@ tmp137,
	cmp	r1, r3	@ StartCode, tmp137
	bne	.L129	@,
	b	.L128	@
	.fnend
	.size	IsVopHeader, .-IsVopHeader
	.align	2
	.global	SM_GetExteriorState
	.type	SM_GetExteriorState, %function
SM_GetExteriorState:
	.fnstart
.LFB1596:
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
	.size	SM_GetExteriorState, .-SM_GetExteriorState
	.align	2
	.global	SM_GetInstanceRawDiscontinue
	.type	SM_GetInstanceRawDiscontinue, %function
SM_GetInstanceRawDiscontinue:
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
	cmp	r0, #15	@ InstID,
	bhi	.L138	@,
	add	r0, r0, r0, asl #1	@, tmp141, InstID, InstID,
	movw	r1, #:lower16:.LANCHOR0	@ tmp137,
	movt	r1, #:upper16:.LANCHOR0	@ tmp137,
	add	r3, r1, r0, asl #4	@, tmp143, tmp137, tmp141,
	ldr	r2, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r2, #0	@ pSmInstArray,
	beq	.L138	@,
	movw	r3, #:lower16:190872	@ tmp145,
	movt	r3, #:upper16:190872	@ tmp145,
	ldr	ip, [r2, r3]	@ <variable>.Mode, <variable>.Mode
	cmp	ip, #0	@ <variable>.Mode,
	beq	.L138	@,
	ldr	r1, [r2, #84]	@ <variable>.Config.DisContinueRawPacketFlag, <variable>.Config.DisContinueRawPacketFlag
	cmp	r1, #1	@ <variable>.Config.DisContinueRawPacketFlag,
	movne	r0, #0	@, D.52062
	moveq	r0, #1	@, D.52062
	ldmfd	sp, {fp, sp, pc}	@
.L138:
	mov	r0, #0	@ D.52062,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SM_GetInstanceRawDiscontinue, .-SM_GetInstanceRawDiscontinue
	.align	2
	.global	SM_GetInstanceStreamEmptyFlag
	.type	SM_GetInstanceStreamEmptyFlag, %function
SM_GetInstanceStreamEmptyFlag:
	.fnstart
.LFB1599:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {fp, ip, lr, pc}	@,
	.pad #4
	.save {fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #24
	sub	sp, sp, #24	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ InstID,
	bls	.L146	@,
.L142:
	mov	r0, #0	@ D.52099,
.L144:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L146:
	sub	r1, fp, #36	@,,
	bl	SM_GetInfo	@
	ldrsb	r3, [fp, #-36]	@ stInstInfo.InstMode, stInstInfo.InstMode
	cmp	r3, #0	@ stInstInfo.InstMode,
	beq	.L142	@,
	ldr	ip, [fp, #-24]	@ stInstInfo.TotalRawSize, stInstInfo.TotalRawSize
	ldr	r2, [fp, #-20]	@ stInstInfo.TotalSegSize, stInstInfo.TotalSegSize
	add	r1, r2, ip	@ tmp138, stInstInfo.TotalSegSize, stInstInfo.TotalRawSize
	cmp	r1, #102400	@ tmp138,
	movlt	r0, #1	@ D.52099,
	blt	.L144	@,
	ldr	r0, [fp, #-28]	@ stInstInfo.SegNum, stInstInfo.SegNum
	cmp	r0, #9	@ stInstInfo.SegNum,
	bgt	.L142	@,
	ldr	lr, [fp, #-32]	@ stInstInfo.RawNum, stInstInfo.RawNum
	cmp	lr, #1	@ stInstInfo.RawNum,
	movgt	r0, #0	@, D.52099
	movle	r0, #1	@, D.52099
	b	.L144	@
	.fnend
	.size	SM_GetInstanceStreamEmptyFlag, .-SM_GetInstanceStreamEmptyFlag
	.align	2
	.global	SCDDRV_MarkReloadDsp
	.type	SCDDRV_MarkReloadDsp, %function
SCDDRV_MarkReloadDsp:
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
	cmp	r0, #0	@ ScdId,
	ldmnefd	sp, {fp, sp, pc}	@
	add	r3, r1, #1	@ tmp135, SmID,
	cmp	r3, #16	@ tmp135,
	ldmhifd	sp, {fp, sp, pc}	@
	movw	r3, #:lower16:.LANCHOR0	@ tmp136,
	cmn	r1, #1	@ SmID,
	movt	r3, #:upper16:.LANCHOR0	@ tmp136,
	mov	r2, #1	@ tmp137,
	str	r2, [r3, #864]	@ tmp137, <variable>.DspReloadFlag
	ldmeqfd	sp, {fp, sp, pc}	@
	add	r2, r1, r1, asl #1	@, tmp142, SmID, SmID,
	movw	r0, #:lower16:190868	@ tmp147,
	movt	r0, #:upper16:190868	@ tmp147,
	mvn	r1, #0	@ tmp148,
	add	r3, r3, r2, asl #4	@, tmp144, tmp136, tmp142,
	ldr	ip, [r3, #40]	@ <variable>.pSmInstArray, <variable>.pSmInstArray
	str	r1, [ip, r0]	@ tmp148, <variable>.MatchScdIdPlus1
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SCDDRV_MarkReloadDsp, .-SCDDRV_MarkReloadDsp
	.align	2
	.global	SM_UpdateMatchMode
	.type	SM_UpdateMatchMode, %function
SM_UpdateMatchMode:
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
	cmp	r0, #0	@ ScdId,
	ldmnefd	sp, {fp, sp, pc}	@
	cmp	r1, #15	@ SmID,
	ldmhifd	sp, {fp, sp, pc}	@
	add	r1, r1, r1, asl #1	@, tmp139, SmID, SmID,
	movw	ip, #:lower16:.LANCHOR0	@ tmp135,
	movt	ip, #:upper16:.LANCHOR0	@ tmp135,
	movw	r3, #:lower16:190868	@ tmp144,
	add	r0, ip, r1, asl #4	@, tmp141, tmp135, tmp139,
	movt	r3, #:upper16:190868	@ tmp144,
	mov	r1, #1	@ tmp145,
	ldr	r2, [r0, #40]	@ <variable>.pSmInstArray, <variable>.pSmInstArray
	str	r1, [r2, r3]	@ tmp145, <variable>.MatchScdIdPlus1
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SM_UpdateMatchMode, .-SM_UpdateMatchMode
	.align	2
	.global	PrintScdInputRawAfterStart
	.type	PrintScdInputRawAfterStart, %function
PrintScdInputRawAfterStart:
	.fnstart
.LFB1619:
	@ args = 4, pretend = 0, frame = 0
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
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PrintScdInputRawAfterStart, .-PrintScdInputRawAfterStart
	.align	2
	.global	PrintSmInfo
	.type	PrintSmInfo, %function
PrintSmInfo:
	.fnstart
.LFB1621:
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
	add	r4, r0, r0, asl #1	@, tmp151, SmID, SmID,
	sub	r1, fp, #68	@ tmp140,,
	movw	r7, #:lower16:.LANCHOR0	@ tmp147,
	movt	r7, #:upper16:.LANCHOR0	@ tmp147,
	add	r3, r1, #4	@ tmp281, tmp140,
	add	r2, r7, r4, asl #4	@, tmp153, tmp147, tmp151,
	mov	r5, #0	@ tmp141,
	str	r5, [r3], #4	@ tmp141, SmInstInfo
	mov	r6, r0	@ SmID, SmID
	str	r5, [r3], #4	@ tmp141, SmInstInfo
	ldr	r4, [r2, #40]	@ pSmInstArray, <variable>.pSmInstArray
	str	r5, [r3], #4	@ tmp141, SmInstInfo
	str	r5, [r3], #4	@ tmp141, SmInstInfo
	str	r5, [r3, #0]	@ tmp141, SmInstInfo
	str	r5, [fp, #-68]	@ tmp141, SmInstInfo
	bl	SM_GetInfo	@
	cmp	r4, r5	@ pSmInstArray,
	beq	.L161	@,
	mov	r2, r6	@, SmID
	movw	r6, #:lower16:190872	@ tmp158,
	movt	r6, #:upper16:190872	@ tmp158,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC0	@,
	movt	r1, #:upper16:.LC0	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, r6]	@, <variable>.Mode
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC2	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC2	@,
	movw	r8, #:lower16:98512	@,
	bl	dprint_vfmw	@
	ldrb	r3, [r4, #52]	@ zero_extendqisi2	@, <variable>.Config.Priority
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC3	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC3	@,
	movt	r8, #:upper16:98512	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #56]	@, <variable>.Config.VidStd
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC4	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC4	@,
	movw	r6, #:lower16:98508	@ tmp273,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #60]	@, <variable>.Config.BufPhyAddr
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #:lower16:.LC6	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r2, #:upper16:.LC6	@,
	movw	sl, #:lower16:1717986919	@ tmp277,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #48]	@, <variable>.Config.pBufVirAddr
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #:lower16:.LC7	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r2, #:upper16:.LC7	@,
	movt	r6, #:upper16:98508	@ tmp273,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #64]	@, <variable>.Config.BufSize
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC8	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC8	@,
	movt	sl, #:upper16:1717986919	@ tmp277,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #68]	@, <variable>.Config.RegPhyBaseAddr
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #:lower16:.LC9	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r2, #:upper16:.LC9	@,
	bl	dprint_vfmw	@
	movw	r2, #:lower16:190744	@ tmp173,
	movt	r2, #:upper16:190744	@ tmp173,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movt	r1, #:upper16:.LC1	@,
	ldr	r3, [r4, r2]	@, <variable>.SmPushRaw.PushRawNum
	movw	r2, #:lower16:.LC10	@,
	movt	r2, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	movw	r3, #:lower16:190748	@ tmp176,
	movt	r3, #:upper16:190748	@ tmp176,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC11	@,
	movt	r1, #:upper16:.LC1	@,
	ldr	r3, [r4, r3]	@, <variable>.SmPushRaw.PushRawTotalLen
	movt	r2, #:upper16:.LC11	@,
	bl	dprint_vfmw	@
	movw	ip, #:lower16:190760	@ tmp179,
	movt	ip, #:upper16:190760	@ tmp179,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #:lower16:.LC12	@,
	ldr	r3, [r4, ip]	@, <variable>.BufAddrCfg.DownMsgPhyAddr
	movt	r1, #:upper16:.LC5	@,
	movt	r2, #:upper16:.LC12	@,
	bl	dprint_vfmw	@
	movw	r2, #:lower16:190768	@ tmp182,
	movt	r2, #:upper16:190768	@ tmp182,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movt	r1, #:upper16:.LC1	@,
	ldr	r3, [r4, r2]	@, <variable>.BufAddrCfg.DownMsgSize
	movw	r2, #:lower16:.LC13	@,
	movt	r2, #:upper16:.LC13	@,
	bl	dprint_vfmw	@
	movw	r3, #:lower16:190772	@ tmp185,
	movt	r3, #:upper16:190772	@ tmp185,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #:lower16:.LC14	@,
	movt	r1, #:upper16:.LC5	@,
	ldr	r3, [r4, r3]	@, <variable>.BufAddrCfg.UpMsgPhyAddr
	movt	r2, #:upper16:.LC14	@,
	bl	dprint_vfmw	@
	movw	ip, #:lower16:190784	@ tmp188,
	movt	ip, #:upper16:190784	@ tmp188,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC15	@,
	ldr	r3, [r4, ip]	@, <variable>.BufAddrCfg.UpMsgNum
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC15	@,
	bl	dprint_vfmw	@
	movw	r2, #:lower16:190780	@ tmp191,
	movt	r2, #:upper16:190780	@ tmp191,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movt	r1, #:upper16:.LC1	@,
	ldr	r3, [r4, r2]	@, <variable>.BufAddrCfg.UpMsgSize
	movw	r2, #:lower16:.LC16	@,
	movt	r2, #:upper16:.LC16	@,
	bl	dprint_vfmw	@
	movw	r3, #:lower16:190848	@ tmp194,
	movt	r3, #:upper16:190848	@ tmp194,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #:lower16:.LC17	@,
	movt	r1, #:upper16:.LC5	@,
	ldr	r3, [r4, r3]	@, <variable>.BufAddrCfg.SegBufPhyAddr
	movt	r2, #:upper16:.LC17	@,
	bl	dprint_vfmw	@
	movw	ip, #:lower16:190852	@ tmp197,
	movt	ip, #:upper16:190852	@ tmp197,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC18	@,
	ldr	r3, [r4, ip]	@, <variable>.BufAddrCfg.SegBufSize
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC18	@,
	bl	dprint_vfmw	@
	ldr	r3, [fp, #-52]	@, SmInstInfo.TotalSegSize
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC19	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC19	@,
	bl	dprint_vfmw	@
	ldr	r3, [fp, #-60]	@, SmInstInfo.SegNum
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC20	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC20	@,
	bl	dprint_vfmw	@
	ldr	r3, [fp, #-56]	@, SmInstInfo.TotalRawSize
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC21	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC21	@,
	bl	dprint_vfmw	@
	ldr	r3, [fp, #-64]	@, SmInstInfo.RawNum
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC22	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC22	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #16]	@, <variable>.SegFilter.ProtocolType
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC23	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC23	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #20]	@, <variable>.SegFilter.ModeFlag
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC24	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC24	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #24]	@, <variable>.SegFilter.LastH263Num
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC25	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC25	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #28]	@, <variable>.SegFilter.SegBufPhyAddr
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #:lower16:.LC26	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r2, #:upper16:.LC26	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #32]	@, <variable>.SegFilter.SegBufSize
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC27	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #36]	@, <variable>.SegFilter.SegBufRollAddr
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #:lower16:.LC28	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r2, #:upper16:.LC28	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #12]	@, <variable>.SegFilter.pScdUpMsg
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC5	@,
	movw	r2, #:lower16:.LC29	@,
	movt	r1, #:upper16:.LC5	@,
	movt	r2, #:upper16:.LC29	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, #40]	@, <variable>.SegFilter.SegNum
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC30	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC30	@,
	bl	dprint_vfmw	@
	movw	r2, #:lower16:204700	@ tmp224,
	movt	r2, #:upper16:204700	@ tmp224,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movt	r1, #:upper16:.LC1	@,
	ldr	r3, [r4, r2]	@, <variable>.BlockTimeInMs
	movw	r2, #:lower16:.LC31	@,
	movt	r2, #:upper16:.LC31	@,
	bl	dprint_vfmw	@
	movw	r3, #:lower16:204704	@ tmp227,
	movt	r3, #:upper16:204704	@ tmp227,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC32	@,
	movt	r1, #:upper16:.LC1	@,
	ldr	r3, [r4, r3]	@, <variable>.LastBlockTime
	movt	r2, #:upper16:.LC32	@,
	bl	dprint_vfmw	@
	movw	ip, #:lower16:204712	@ tmp231,
	movt	ip, #:upper16:204712	@ tmp231,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC33	@,
	movt	r1, #:upper16:.LC33	@,
	ldrd	r2, [r4, ip]	@, pSmInstArray, tmp231
	strd	r2, [sp]	@,
	movw	r2, #:lower16:.LC34	@,
	movt	r2, #:upper16:.LC34	@,
	bl	dprint_vfmw	@
	movw	r2, #:lower16:190856	@ tmp234,
	movt	r2, #:upper16:190856	@ tmp234,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movt	r1, #:upper16:.LC1	@,
	ldr	r3, [r4, r2]	@, <variable>.InstID
	movw	r2, #:lower16:.LC35	@,
	movt	r2, #:upper16:.LC35	@,
	bl	dprint_vfmw	@
	ldr	r3, [r7, #856]	@, <variable>.SCDState
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC1	@,
	movw	r2, #:lower16:.LC36	@,
	movt	r1, #:upper16:.LC1	@,
	movt	r2, #:upper16:.LC36	@,
	movw	r7, #:lower16:98516	@ tmp246,
	bl	dprint_vfmw	@
	ldr	ip, [r4, r8]	@ <variable>.RawPacketArray.History, <variable>.RawPacketArray.History
	movw	r3, #:lower16:98504	@ tmp241,
	movt	r3, #:upper16:98504	@ tmp241,
	movt	r7, #:upper16:98516	@ tmp246,
	mov	r0, #32	@,
	ldr	r3, [r4, r3]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Head
	movw	r1, #:lower16:.LC37	@,
	movw	r2, #:lower16:.LC36	@,
	movt	r1, #:upper16:.LC37	@,
	movt	r2, #:upper16:.LC36	@,
	str	ip, [sp, #0]	@ <variable>.RawPacketArray.History,
	bl	dprint_vfmw	@
	ldr	r2, [r4, r7]	@, <variable>.RawPacketArray.FirstPacketOffset
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC38	@,
	movt	r1, #:upper16:.LC38	@,
	bl	dprint_vfmw	@
	ldr	r7, [r4, r8]	@ idx, <variable>.RawPacketArray.History
.L172:
	ldr	r3, [r4, r6]	@ <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Tail
	cmp	r3, r7	@ <variable>.RawPacketArray.Tail, idx
	beq	.L158	@,
.L175:
	add	r2, r7, r7, asl #1	@, tmp265, idx, idx,
	mov	r0, #32	@,
	add	r7, r7, #1	@ idx, idx,
	movw	r1, #:lower16:.LC40	@,
	mla	r8, r2, r0, r4	@ tmp267, tmp265,, pSmInstArray
	movt	r1, #:upper16:.LC40	@,
	add	r5, r5, #1	@ tmp279, i,
	ldr	r2, [r8, #208]	@, <variable>.Length
	movw	r8, #1023	@,
	bl	dprint_vfmw	@
	cmp	r7, r8	@ idx,
	subgt	r7, r7, #1024	@ idx, idx,
	cmp	r5, #1024	@ tmp279,
	beq	.L158	@,
	smull	r3, ip, sl, r5	@, tmp250, tmp277, tmp279
	mov	lr, r5, asr #31	@ tmp253, tmp279,
	rsb	r1, lr, ip, asr #2	@, tmp249, tmp253, tmp250,
	add	r0, r1, r1, asl #2	@, tmp256, tmp249, tmp249,
	cmp	r5, r0, asl #1	@ tmp279, tmp256,
	beq	.L173	@,
.L169:
	ldr	r0, [r4, r6]	@ <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Tail
	cmp	r0, r7	@ <variable>.RawPacketArray.Tail, idx
	beq	.L158	@,
	add	lr, r7, r7, asl #1	@, tmp290, idx, idx,
	mov	r0, #32	@,
	movw	r1, #:lower16:.LC40	@,
	movt	r1, #:upper16:.LC40	@,
	mla	r9, lr, r0, r4	@ tmp292, tmp290,, pSmInstArray
	add	r7, r7, #1	@ idx, idx,
	ldr	r2, [r9, #208]	@, <variable>.Length
	movw	r9, #1023	@,
	bl	dprint_vfmw	@
	add	r3, r5, #1	@ i, tmp279,
	cmp	r7, r9	@ idx,
	smull	ip, r0, sl, r3	@, tmp299, tmp277, i
	mov	r2, r3, asr #31	@ tmp301, i,
	subgt	r7, r7, #1024	@ idx, idx,
	rsb	ip, r2, r0, asr #2	@, tmp302, tmp301, tmp299,
	add	r1, ip, ip, asl #2	@, tmp304, tmp302, tmp302,
	cmp	r3, r1, asl #1	@ i, tmp304,
	beq	.L174	@,
.L170:
	ldr	r1, [r4, r6]	@ <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Tail
	cmp	r1, r7	@ <variable>.RawPacketArray.Tail, idx
	beq	.L158	@,
	add	r3, r7, r7, asl #1	@, tmp310, idx, idx,
	mov	r0, #32	@,
	add	r5, r5, #2	@ i, tmp279,
	movw	r1, #:lower16:.LC40	@,
	mla	lr, r3, r0, r4	@ tmp312, tmp310,, pSmInstArray
	movt	r1, #:upper16:.LC40	@,
	add	r7, r7, #1	@ idx, idx,
	ldr	r2, [lr, #208]	@, <variable>.Length
	bl	dprint_vfmw	@
	smull	r3, r2, sl, r5	@, tmp317, tmp277, i
	mov	r0, r5, asr #31	@ tmp319, i,
	movw	r1, #1023	@,
	cmp	r7, r1	@ idx,
	subgt	r7, r7, #1024	@ idx, idx,
	rsb	ip, r0, r2, asr #2	@, tmp320, tmp319, tmp317,
	add	r3, ip, ip, asl #2	@, tmp322, tmp320, tmp320,
	cmp	r5, r3, asl #1	@ i, tmp322,
	bne	.L172	@,
	movw	r1, #:lower16:.LC39	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC39	@,
	bl	dprint_vfmw	@
	ldr	r3, [r4, r6]	@ <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Tail
	cmp	r3, r7	@ <variable>.RawPacketArray.Tail, idx
	bne	.L175	@,
.L158:
	movw	r1, #:lower16:.LC39	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC39	@,
	bl	dprint_vfmw	@
.L161:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L173:
	movw	r1, #:lower16:.LC39	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC39	@,
	bl	dprint_vfmw	@
	b	.L169	@
.L174:
	movw	r1, #:lower16:.LC39	@,
	mov	r0, #32	@,
	movt	r1, #:upper16:.LC39	@,
	bl	dprint_vfmw	@
	b	.L170	@
	.fnend
	.size	PrintSmInfo, .-PrintSmInfo
	.align	2
	.global	PrintScdStateReg
	.type	PrintScdStateReg, %function
PrintScdStateReg:
	.fnstart
.LFB1618:
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
	mov	r4, r0	@ pSmStateReg, pSmStateReg
	mov	r2, r1	@ ScdId, ScdId
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC41	@,
	movt	r1, #:upper16:.LC41	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #0]	@, <variable>.Scdover
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC42	@,
	movt	r1, #:upper16:.LC42	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #4]	@, <variable>.ScdInt
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC43	@,
	movt	r1, #:upper16:.LC43	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #8]	@, <variable>.ShortScdNum
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC44	@,
	movt	r1, #:upper16:.LC44	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #12]	@, <variable>.ScdNum
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC45	@,
	movt	r1, #:upper16:.LC45	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #16]	@, <variable>.ScdRollAddr
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC46	@,
	movt	r1, #:upper16:.LC46	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #20]	@, <variable>.SrcEaten
	movw	r1, #:lower16:.LC47	@,
	mov	r0, #24	@,
	movt	r1, #:upper16:.LC47	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	PrintScdStateReg, .-PrintScdStateReg
	.align	2
	.global	PrintDownMsg
	.type	PrintDownMsg, %function
PrintDownMsg:
	.fnstart
.LFB1617:
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
	mov	r4, r0	@ DownMsgPhyAddr, DownMsgPhyAddr
	mov	r7, r1	@ pDownMsgVirAddr, pDownMsgVirAddr
	mov	r8, r2	@ PushRawNum, PushRawNum
	mov	r0, #24	@,
	mov	r2, r3	@, ScdId
	movw	r1, #:lower16:.LC48	@,
	movt	r1, #:upper16:.LC48	@,
	bl	dprint_vfmw	@
	mov	r2, r7	@, pDownMsgVirAddr
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC49	@,
	movt	r1, #:upper16:.LC49	@,
	bl	dprint_vfmw	@
	mov	r2, r4	@, DownMsgPhyAddr
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC50	@,
	movt	r1, #:upper16:.LC50	@,
	bl	dprint_vfmw	@
	cmp	r8, #0	@ PushRawNum,
	ldmlefd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	mov	r2, #0	@,
	ldr	r3, [r7, #0]	@,* pDownMsgVirAddr
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	sub	sl, r8, #1	@ tmp189, PushRawNum,
	bl	dprint_vfmw	@
	mov	r2, #1	@,
	ldr	r3, [r7, #4]	@,
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	mov	r2, #2	@,
	ldr	r3, [r7, #8]	@,
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC39	@,
	movt	r1, #:upper16:.LC39	@,
	bl	dprint_vfmw	@
	cmp	r8, #1	@ PushRawNum,
	and	sl, sl, #1	@ tmp191, tmp189,
	mov	r4, #3	@ j,
	mov	r6, #1	@ i,
	add	r5, r7, #12	@ ivtmp.1553, pDownMsgVirAddr,
	ldmlefd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	cmp	sl, #0	@ tmp191,
	beq	.L180	@,
	mov	r2, r4	@, j
	ldr	r3, [r5, #0]	@,* ivtmp.1553
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	mov	r6, #2	@ i,
	bl	dprint_vfmw	@
	ldr	r3, [r5, #4]	@,
	mov	r2, #4	@,
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	ldr	r3, [r5, #8]	@,
	mov	r2, #5	@,
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC39	@,
	movt	r1, #:upper16:.LC39	@,
	bl	dprint_vfmw	@
	cmp	r8, r6	@ PushRawNum, i
	add	r5, r7, #24	@ ivtmp.1553, pDownMsgVirAddr,
	mov	r4, #6	@ j,
	ldmlefd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L180:
	mov	r2, r4	@, j
	ldr	r3, [r5, #0]	@,* ivtmp.1553
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	add	sl, r4, #3	@ tmp194, j,
	bl	dprint_vfmw	@
	add	r2, r4, #1	@, j,
	ldr	r3, [r5, #4]	@,
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	add	r2, r4, #2	@, j,
	ldr	r3, [r5, #8]	@,
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	add	r7, r5, #12	@ tmp193, ivtmp.1553,
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC39	@,
	movt	r1, #:upper16:.LC39	@,
	add	r6, r6, #1	@ tmp192, i,
	bl	dprint_vfmw	@
	ldr	r3, [r5, #12]	@,
	mov	r2, sl	@, tmp194
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	add	r2, r4, #4	@, j,
	ldr	r3, [r7, #4]	@,
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	add	r2, r4, #5	@, j,
	ldr	r3, [r7, #8]	@,
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC51	@,
	movt	r1, #:upper16:.LC51	@,
	bl	dprint_vfmw	@
	add	r6, r6, #1	@ i, tmp192,
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC39	@,
	movt	r1, #:upper16:.LC39	@,
	add	r4, r4, #6	@ j, j,
	bl	dprint_vfmw	@
	cmp	r8, r6	@ PushRawNum, i
	add	r5, r5, #24	@ ivtmp.1553, ivtmp.1553,
	bgt	.L180	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	.fnend
	.size	PrintDownMsg, .-PrintDownMsg
	.align	2
	.global	SM_AddMatchMode
	.type	SM_AddMatchMode, %function
SM_AddMatchMode:
	.fnstart
.LFB1608:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp373,
	movt	r4, #:upper16:.LANCHOR0	@ tmp373,
	ldr	r5, [r4, #40]	@ temp.1590, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1590,
	beq	.L189	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L189	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp183,
	movt	r3, #:upper16:g_DspDrvState	@ tmp183,
	ldr	r2, [r3, #0]	@ temp.1592, g_DspDrvState
	cmp	r2, #1	@ temp.1592,
	ldrne	r3, [r3, #4]	@ prephitmp.1593, g_DspDrvState
	beq	.L285	@,
.L192:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp185,
	movt	r0, #:upper16:190868	@ tmp185,
	mov	r2, #0	@ tmp186,
	str	r2, [r5, r0]	@ tmp186, <variable>.MatchScdIdPlus1
.L189:
	ldr	r5, [r4, #88]	@ temp.1595, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1595,
	beq	.L194	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L194	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp195,
	movt	r3, #:upper16:g_DspDrvState	@ tmp195,
	ldr	r2, [r3, #0]	@ temp.1597, g_DspDrvState
	cmp	r2, #1	@ temp.1597,
	ldrne	r3, [r3, #4]	@ prephitmp.1598, g_DspDrvState
	beq	.L286	@,
.L197:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp197,
	movt	r0, #:upper16:190868	@ tmp197,
	mov	r2, #0	@ tmp198,
	str	r2, [r5, r0]	@ tmp198, <variable>.MatchScdIdPlus1
.L194:
	ldr	r5, [r4, #136]	@ temp.1600, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1600,
	beq	.L199	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L199	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp207,
	movt	r3, #:upper16:g_DspDrvState	@ tmp207,
	ldr	r2, [r3, #0]	@ temp.1602, g_DspDrvState
	cmp	r2, #1	@ temp.1602,
	ldrne	r3, [r3, #4]	@ prephitmp.1603, g_DspDrvState
	beq	.L287	@,
.L202:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp209,
	movt	r0, #:upper16:190868	@ tmp209,
	mov	r2, #0	@ tmp210,
	str	r2, [r5, r0]	@ tmp210, <variable>.MatchScdIdPlus1
.L199:
	ldr	r5, [r4, #184]	@ temp.1605, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1605,
	beq	.L204	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L204	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp219,
	movt	r3, #:upper16:g_DspDrvState	@ tmp219,
	ldr	r2, [r3, #0]	@ temp.1607, g_DspDrvState
	cmp	r2, #1	@ temp.1607,
	ldrne	r3, [r3, #4]	@ prephitmp.1608, g_DspDrvState
	beq	.L288	@,
.L207:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp221,
	movt	r0, #:upper16:190868	@ tmp221,
	mov	r2, #0	@ tmp222,
	str	r2, [r5, r0]	@ tmp222, <variable>.MatchScdIdPlus1
.L204:
	ldr	r5, [r4, #232]	@ temp.1610, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1610,
	beq	.L209	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L209	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp231,
	movt	r3, #:upper16:g_DspDrvState	@ tmp231,
	ldr	r2, [r3, #0]	@ temp.1612, g_DspDrvState
	cmp	r2, #1	@ temp.1612,
	ldrne	r3, [r3, #4]	@ prephitmp.1613, g_DspDrvState
	beq	.L289	@,
.L212:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp233,
	movt	r0, #:upper16:190868	@ tmp233,
	mov	r2, #0	@ tmp234,
	str	r2, [r5, r0]	@ tmp234, <variable>.MatchScdIdPlus1
.L209:
	ldr	r5, [r4, #280]	@ temp.1615, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1615,
	beq	.L214	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L214	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp243,
	movt	r3, #:upper16:g_DspDrvState	@ tmp243,
	ldr	r2, [r3, #0]	@ temp.1617, g_DspDrvState
	cmp	r2, #1	@ temp.1617,
	ldrne	r3, [r3, #4]	@ prephitmp.1618, g_DspDrvState
	beq	.L290	@,
.L217:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp245,
	movt	r0, #:upper16:190868	@ tmp245,
	mov	r2, #0	@ tmp246,
	str	r2, [r5, r0]	@ tmp246, <variable>.MatchScdIdPlus1
.L214:
	ldr	r5, [r4, #328]	@ temp.1620, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1620,
	beq	.L219	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L219	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp255,
	movt	r3, #:upper16:g_DspDrvState	@ tmp255,
	ldr	r2, [r3, #0]	@ temp.1622, g_DspDrvState
	cmp	r2, #1	@ temp.1622,
	ldrne	r3, [r3, #4]	@ prephitmp.1623, g_DspDrvState
	beq	.L291	@,
.L222:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp257,
	movt	r0, #:upper16:190868	@ tmp257,
	mov	r2, #0	@ tmp258,
	str	r2, [r5, r0]	@ tmp258, <variable>.MatchScdIdPlus1
.L219:
	ldr	r5, [r4, #376]	@ temp.1625, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1625,
	beq	.L224	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L224	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp267,
	movt	r3, #:upper16:g_DspDrvState	@ tmp267,
	ldr	r2, [r3, #0]	@ temp.1627, g_DspDrvState
	cmp	r2, #1	@ temp.1627,
	ldrne	r3, [r3, #4]	@ prephitmp.1628, g_DspDrvState
	beq	.L292	@,
.L227:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp269,
	movt	r0, #:upper16:190868	@ tmp269,
	mov	r2, #0	@ tmp270,
	str	r2, [r5, r0]	@ tmp270, <variable>.MatchScdIdPlus1
.L224:
	ldr	r5, [r4, #424]	@ temp.1630, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1630,
	beq	.L229	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L229	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp279,
	movt	r3, #:upper16:g_DspDrvState	@ tmp279,
	ldr	r2, [r3, #0]	@ temp.1632, g_DspDrvState
	cmp	r2, #1	@ temp.1632,
	ldrne	r3, [r3, #4]	@ prephitmp.1633, g_DspDrvState
	beq	.L293	@,
.L232:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp281,
	movt	r0, #:upper16:190868	@ tmp281,
	mov	r2, #0	@ tmp282,
	str	r2, [r5, r0]	@ tmp282, <variable>.MatchScdIdPlus1
.L229:
	ldr	r5, [r4, #472]	@ temp.1635, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1635,
	beq	.L234	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L234	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp291,
	movt	r3, #:upper16:g_DspDrvState	@ tmp291,
	ldr	r2, [r3, #0]	@ temp.1637, g_DspDrvState
	cmp	r2, #1	@ temp.1637,
	ldrne	r3, [r3, #4]	@ prephitmp.1638, g_DspDrvState
	beq	.L294	@,
.L237:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp293,
	movt	r0, #:upper16:190868	@ tmp293,
	mov	r2, #0	@ tmp294,
	str	r2, [r5, r0]	@ tmp294, <variable>.MatchScdIdPlus1
.L234:
	ldr	r5, [r4, #520]	@ temp.1640, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1640,
	beq	.L239	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L239	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp303,
	movt	r3, #:upper16:g_DspDrvState	@ tmp303,
	ldr	r2, [r3, #0]	@ temp.1642, g_DspDrvState
	cmp	r2, #1	@ temp.1642,
	ldrne	r3, [r3, #4]	@ prephitmp.1643, g_DspDrvState
	beq	.L295	@,
.L242:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp305,
	movt	r0, #:upper16:190868	@ tmp305,
	mov	r2, #0	@ tmp306,
	str	r2, [r5, r0]	@ tmp306, <variable>.MatchScdIdPlus1
.L239:
	ldr	r5, [r4, #568]	@ temp.1645, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1645,
	beq	.L244	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L244	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp315,
	movt	r3, #:upper16:g_DspDrvState	@ tmp315,
	ldr	r2, [r3, #0]	@ temp.1647, g_DspDrvState
	cmp	r2, #1	@ temp.1647,
	ldrne	r3, [r3, #4]	@ prephitmp.1648, g_DspDrvState
	beq	.L296	@,
.L247:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp317,
	movt	r0, #:upper16:190868	@ tmp317,
	mov	r2, #0	@ tmp318,
	str	r2, [r5, r0]	@ tmp318, <variable>.MatchScdIdPlus1
.L244:
	ldr	r5, [r4, #616]	@ temp.1650, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1650,
	beq	.L249	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L249	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp327,
	movt	r3, #:upper16:g_DspDrvState	@ tmp327,
	ldr	r2, [r3, #0]	@ temp.1652, g_DspDrvState
	cmp	r2, #1	@ temp.1652,
	ldrne	r3, [r3, #4]	@ prephitmp.1653, g_DspDrvState
	beq	.L297	@,
.L252:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp329,
	movt	r0, #:upper16:190868	@ tmp329,
	mov	r2, #0	@ tmp330,
	str	r2, [r5, r0]	@ tmp330, <variable>.MatchScdIdPlus1
.L249:
	ldr	r5, [r4, #664]	@ temp.1655, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1655,
	beq	.L254	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L254	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp339,
	movt	r3, #:upper16:g_DspDrvState	@ tmp339,
	ldr	r2, [r3, #0]	@ temp.1657, g_DspDrvState
	cmp	r2, #1	@ temp.1657,
	ldrne	r3, [r3, #4]	@ prephitmp.1658, g_DspDrvState
	beq	.L298	@,
.L257:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp341,
	movt	r0, #:upper16:190868	@ tmp341,
	mov	r2, #0	@ tmp342,
	str	r2, [r5, r0]	@ tmp342, <variable>.MatchScdIdPlus1
.L254:
	ldr	r5, [r4, #712]	@ temp.1660, <variable>.pSmInstArray
	cmp	r5, #0	@ temp.1660,
	beq	.L259	@,
	ldr	r3, [r5, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	beq	.L259	@,
	movw	r3, #:lower16:g_DspDrvState	@ tmp351,
	movt	r3, #:upper16:g_DspDrvState	@ tmp351,
	ldr	r2, [r3, #0]	@ temp.1662, g_DspDrvState
	cmp	r2, #1	@ temp.1662,
	ldrne	r3, [r3, #4]	@ prephitmp.1663, g_DspDrvState
	beq	.L299	@,
.L262:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC52	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
	movw	r0, #:lower16:190868	@ tmp353,
	movt	r0, #:upper16:190868	@ tmp353,
	mov	r2, #0	@ tmp354,
	str	r2, [r5, r0]	@ tmp354, <variable>.MatchScdIdPlus1
.L259:
	ldr	r4, [r4, #760]	@ D.52909, <variable>.pSmInstArray
	cmp	r4, #0	@ D.52909,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	ldr	r3, [r4, #88]	@ <variable>.Config.ScdLowdlyEnable, <variable>.Config.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.Config.ScdLowdlyEnable,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	movw	r3, #:lower16:g_DspDrvState	@ tmp363,
	movt	r3, #:upper16:g_DspDrvState	@ tmp363,
	ldr	r2, [r3, #0]	@ D.52917, g_DspDrvState
	cmp	r2, #1	@ D.52917,
	ldrne	r3, [r3, #4]	@ prephitmp.1578, g_DspDrvState
	beq	.L300	@,
.L267:
	movw	r1, #:lower16:.LC52	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC52	@,
	bl	dprint_vfmw	@
.L284:
	movw	r0, #:lower16:190868	@ tmp371,
	movt	r0, #:upper16:190868	@ tmp371,
	mov	r2, #0	@ tmp372,
	str	r2, [r4, r0]	@ tmp372, <variable>.MatchScdIdPlus1
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L300:
	ldr	r3, [r3, #4]	@ prephitmp.1578, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1578,
	beq	.L284	@,
	cmp	r3, #2	@ prephitmp.1578,
	movweq	r3, #:lower16:190868	@ tmp367,
	movteq	r3, #:upper16:190868	@ tmp367,
	streq	r2, [r4, r3]	@ D.52917, <variable>.MatchScdIdPlus1
	bne	.L267	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L285:
	ldr	r3, [r3, #4]	@ prephitmp.1593, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1593,
	beq	.L193	@,
	cmp	r3, #2	@ prephitmp.1593,
	movweq	r3, #:lower16:190868	@ tmp189,
	movteq	r3, #:upper16:190868	@ tmp189,
	streq	r2, [r5, r3]	@ temp.1592, <variable>.MatchScdIdPlus1
	bne	.L192	@,
	b	.L189	@
.L286:
	ldr	r3, [r3, #4]	@ prephitmp.1598, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1598,
	beq	.L198	@,
	cmp	r3, #2	@ prephitmp.1598,
	movweq	r3, #:lower16:190868	@ tmp201,
	movteq	r3, #:upper16:190868	@ tmp201,
	streq	r2, [r5, r3]	@ temp.1597, <variable>.MatchScdIdPlus1
	bne	.L197	@,
	b	.L194	@
.L287:
	ldr	r3, [r3, #4]	@ prephitmp.1603, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1603,
	beq	.L203	@,
	cmp	r3, #2	@ prephitmp.1603,
	movweq	r3, #:lower16:190868	@ tmp213,
	movteq	r3, #:upper16:190868	@ tmp213,
	streq	r2, [r5, r3]	@ temp.1602, <variable>.MatchScdIdPlus1
	bne	.L202	@,
	b	.L199	@
.L288:
	ldr	r3, [r3, #4]	@ prephitmp.1608, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1608,
	beq	.L208	@,
	cmp	r3, #2	@ prephitmp.1608,
	movweq	r3, #:lower16:190868	@ tmp225,
	movteq	r3, #:upper16:190868	@ tmp225,
	streq	r2, [r5, r3]	@ temp.1607, <variable>.MatchScdIdPlus1
	bne	.L207	@,
	b	.L204	@
.L289:
	ldr	r3, [r3, #4]	@ prephitmp.1613, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1613,
	beq	.L213	@,
	cmp	r3, #2	@ prephitmp.1613,
	movweq	r3, #:lower16:190868	@ tmp237,
	movteq	r3, #:upper16:190868	@ tmp237,
	streq	r2, [r5, r3]	@ temp.1612, <variable>.MatchScdIdPlus1
	bne	.L212	@,
	b	.L209	@
.L290:
	ldr	r3, [r3, #4]	@ prephitmp.1618, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1618,
	beq	.L218	@,
	cmp	r3, #2	@ prephitmp.1618,
	movweq	r3, #:lower16:190868	@ tmp249,
	movteq	r3, #:upper16:190868	@ tmp249,
	streq	r2, [r5, r3]	@ temp.1617, <variable>.MatchScdIdPlus1
	bne	.L217	@,
	b	.L214	@
.L291:
	ldr	r3, [r3, #4]	@ prephitmp.1623, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1623,
	beq	.L223	@,
	cmp	r3, #2	@ prephitmp.1623,
	movweq	r3, #:lower16:190868	@ tmp261,
	movteq	r3, #:upper16:190868	@ tmp261,
	streq	r2, [r5, r3]	@ temp.1622, <variable>.MatchScdIdPlus1
	bne	.L222	@,
	b	.L219	@
.L292:
	ldr	r3, [r3, #4]	@ prephitmp.1628, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1628,
	beq	.L228	@,
	cmp	r3, #2	@ prephitmp.1628,
	movweq	r3, #:lower16:190868	@ tmp273,
	movteq	r3, #:upper16:190868	@ tmp273,
	streq	r2, [r5, r3]	@ temp.1627, <variable>.MatchScdIdPlus1
	bne	.L227	@,
	b	.L224	@
.L293:
	ldr	r3, [r3, #4]	@ prephitmp.1633, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1633,
	beq	.L233	@,
	cmp	r3, #2	@ prephitmp.1633,
	movweq	r3, #:lower16:190868	@ tmp285,
	movteq	r3, #:upper16:190868	@ tmp285,
	streq	r2, [r5, r3]	@ temp.1632, <variable>.MatchScdIdPlus1
	bne	.L232	@,
	b	.L229	@
.L294:
	ldr	r3, [r3, #4]	@ prephitmp.1638, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1638,
	beq	.L238	@,
	cmp	r3, #2	@ prephitmp.1638,
	movweq	r3, #:lower16:190868	@ tmp297,
	movteq	r3, #:upper16:190868	@ tmp297,
	streq	r2, [r5, r3]	@ temp.1637, <variable>.MatchScdIdPlus1
	bne	.L237	@,
	b	.L234	@
.L295:
	ldr	r3, [r3, #4]	@ prephitmp.1643, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1643,
	beq	.L243	@,
	cmp	r3, #2	@ prephitmp.1643,
	movweq	r3, #:lower16:190868	@ tmp309,
	movteq	r3, #:upper16:190868	@ tmp309,
	streq	r2, [r5, r3]	@ temp.1642, <variable>.MatchScdIdPlus1
	bne	.L242	@,
	b	.L239	@
.L296:
	ldr	r3, [r3, #4]	@ prephitmp.1648, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1648,
	beq	.L248	@,
	cmp	r3, #2	@ prephitmp.1648,
	movweq	r3, #:lower16:190868	@ tmp321,
	movteq	r3, #:upper16:190868	@ tmp321,
	streq	r2, [r5, r3]	@ temp.1647, <variable>.MatchScdIdPlus1
	bne	.L247	@,
	b	.L244	@
.L297:
	ldr	r3, [r3, #4]	@ prephitmp.1653, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1653,
	beq	.L253	@,
	cmp	r3, #2	@ prephitmp.1653,
	movweq	r3, #:lower16:190868	@ tmp333,
	movteq	r3, #:upper16:190868	@ tmp333,
	streq	r2, [r5, r3]	@ temp.1652, <variable>.MatchScdIdPlus1
	bne	.L252	@,
	b	.L249	@
.L298:
	ldr	r3, [r3, #4]	@ prephitmp.1658, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1658,
	beq	.L258	@,
	cmp	r3, #2	@ prephitmp.1658,
	movweq	r3, #:lower16:190868	@ tmp345,
	movteq	r3, #:upper16:190868	@ tmp345,
	streq	r2, [r5, r3]	@ temp.1657, <variable>.MatchScdIdPlus1
	bne	.L257	@,
	b	.L254	@
.L299:
	ldr	r3, [r3, #4]	@ prephitmp.1663, g_DspDrvState
	cmp	r3, #1	@ prephitmp.1663,
	beq	.L263	@,
	cmp	r3, #2	@ prephitmp.1663,
	movweq	r3, #:lower16:190868	@ tmp357,
	movteq	r3, #:upper16:190868	@ tmp357,
	streq	r2, [r5, r3]	@ temp.1662, <variable>.MatchScdIdPlus1
	bne	.L262	@,
	b	.L259	@
.L193:
	movw	ip, #:lower16:190868	@ tmp191,
	movt	ip, #:upper16:190868	@ tmp191,
	mov	r1, #0	@ tmp192,
	str	r1, [r5, ip]	@ tmp192, <variable>.MatchScdIdPlus1
	b	.L189	@
.L263:
	movw	ip, #:lower16:190868	@ tmp359,
	movt	ip, #:upper16:190868	@ tmp359,
	mov	r1, #0	@ tmp360,
	str	r1, [r5, ip]	@ tmp360, <variable>.MatchScdIdPlus1
	b	.L259	@
.L258:
	movw	ip, #:lower16:190868	@ tmp347,
	movt	ip, #:upper16:190868	@ tmp347,
	mov	r1, #0	@ tmp348,
	str	r1, [r5, ip]	@ tmp348, <variable>.MatchScdIdPlus1
	b	.L254	@
.L253:
	movw	ip, #:lower16:190868	@ tmp335,
	movt	ip, #:upper16:190868	@ tmp335,
	mov	r1, #0	@ tmp336,
	str	r1, [r5, ip]	@ tmp336, <variable>.MatchScdIdPlus1
	b	.L249	@
.L248:
	movw	ip, #:lower16:190868	@ tmp323,
	movt	ip, #:upper16:190868	@ tmp323,
	mov	r1, #0	@ tmp324,
	str	r1, [r5, ip]	@ tmp324, <variable>.MatchScdIdPlus1
	b	.L244	@
.L243:
	movw	ip, #:lower16:190868	@ tmp311,
	movt	ip, #:upper16:190868	@ tmp311,
	mov	r1, #0	@ tmp312,
	str	r1, [r5, ip]	@ tmp312, <variable>.MatchScdIdPlus1
	b	.L239	@
.L238:
	movw	ip, #:lower16:190868	@ tmp299,
	movt	ip, #:upper16:190868	@ tmp299,
	mov	r1, #0	@ tmp300,
	str	r1, [r5, ip]	@ tmp300, <variable>.MatchScdIdPlus1
	b	.L234	@
.L233:
	movw	ip, #:lower16:190868	@ tmp287,
	movt	ip, #:upper16:190868	@ tmp287,
	mov	r1, #0	@ tmp288,
	str	r1, [r5, ip]	@ tmp288, <variable>.MatchScdIdPlus1
	b	.L229	@
.L228:
	movw	ip, #:lower16:190868	@ tmp275,
	movt	ip, #:upper16:190868	@ tmp275,
	mov	r1, #0	@ tmp276,
	str	r1, [r5, ip]	@ tmp276, <variable>.MatchScdIdPlus1
	b	.L224	@
.L223:
	movw	ip, #:lower16:190868	@ tmp263,
	movt	ip, #:upper16:190868	@ tmp263,
	mov	r1, #0	@ tmp264,
	str	r1, [r5, ip]	@ tmp264, <variable>.MatchScdIdPlus1
	b	.L219	@
.L218:
	movw	ip, #:lower16:190868	@ tmp251,
	movt	ip, #:upper16:190868	@ tmp251,
	mov	r1, #0	@ tmp252,
	str	r1, [r5, ip]	@ tmp252, <variable>.MatchScdIdPlus1
	b	.L214	@
.L213:
	movw	ip, #:lower16:190868	@ tmp239,
	movt	ip, #:upper16:190868	@ tmp239,
	mov	r1, #0	@ tmp240,
	str	r1, [r5, ip]	@ tmp240, <variable>.MatchScdIdPlus1
	b	.L209	@
.L208:
	movw	ip, #:lower16:190868	@ tmp227,
	movt	ip, #:upper16:190868	@ tmp227,
	mov	r1, #0	@ tmp228,
	str	r1, [r5, ip]	@ tmp228, <variable>.MatchScdIdPlus1
	b	.L204	@
.L203:
	movw	ip, #:lower16:190868	@ tmp215,
	movt	ip, #:upper16:190868	@ tmp215,
	mov	r1, #0	@ tmp216,
	str	r1, [r5, ip]	@ tmp216, <variable>.MatchScdIdPlus1
	b	.L199	@
.L198:
	movw	ip, #:lower16:190868	@ tmp203,
	movt	ip, #:upper16:190868	@ tmp203,
	mov	r1, #0	@ tmp204,
	str	r1, [r5, ip]	@ tmp204, <variable>.MatchScdIdPlus1
	b	.L194	@
	.fnend
	.size	SM_AddMatchMode, .-SM_AddMatchMode
	.align	2
	.global	SM_SetRawDiscontinueFlag
	.type	SM_SetRawDiscontinueFlag, %function
SM_SetRawDiscontinueFlag:
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
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ InstID,
	bhi	.L307	@,
	add	r0, r0, r0, asl #1	@, tmp142, InstID, InstID,
	movw	ip, #:lower16:.LANCHOR0	@ tmp138,
	movt	ip, #:upper16:.LANCHOR0	@ tmp138,
	add	r2, ip, r0, asl #4	@, tmp144, tmp138, tmp142,
	ldr	ip, [r2, #40]	@ pSmInstArray, <variable>.pSmInstArray
	rsbs	r3, ip, #1	@ tmp149, pSmInstArray
	movcc	r3, #0	@ tmp149
	orrs	r3, r3, r1, lsr #31	@,, tmp149, Flag,
	bne	.L308	@,
	movw	r2, #:lower16:190872	@ tmp155,
	movt	r2, #:upper16:190872	@ tmp155,
	ldr	r3, [ip, r2]	@ <variable>.Mode, <variable>.Mode
	cmp	r3, #0	@ <variable>.Mode,
	strne	r1, [ip, #84]	@ Flag, <variable>.Config.DisContinueRawPacketFlag
	streq	r3, [ip, #84]	@ <variable>.Mode, <variable>.Config.DisContinueRawPacketFlag
	moveq	r0, #1	@ D.52080,
	movne	r0, #1	@ D.52080,
	b	.L303	@
.L308:
	mov	r3, r1	@, Flag
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC53	@,
	movw	r2, #4108	@,
	movt	r1, #:upper16:.LC53	@,
	str	ip, [sp, #0]	@ pSmInstArray,
	bl	dprint_vfmw	@
.L307:
	mov	r0, #0	@ D.52080,
.L303:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
	.fnend
	.size	SM_SetRawDiscontinueFlag, .-SM_SetRawDiscontinueFlag
	.align	2
	.global	SM_CfgBuf
	.type	SM_CfgBuf, %function
SM_CfgBuf:
	.fnstart
.LFB1571:
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
	cmp	r0, #15	@ SmID,
	bhi	.L316	@,
	cmp	r1, #0	@ ScdId,
	bne	.L317	@,
	add	r0, r0, r0, asl #1	@, tmp144, SmID, SmID,
	movw	r2, #:lower16:.LANCHOR0	@ tmp140,
	movt	r2, #:upper16:.LANCHOR0	@ tmp140,
	add	r0, r2, r0, asl #4	@, tmp146, tmp140, tmp144,
	ldr	ip, [r0, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	ip, #0	@ pSmInstArray,
	mvneq	r0, #0	@ D.50713,
	beq	.L311	@,
	movw	r3, #:lower16:190860	@ tmp148,
	movt	r3, #:upper16:190860	@ tmp148,
	ldr	r0, [ip, r3]	@ <variable>.ScdID, <variable>.ScdID
	cmp	r0, #0	@ <variable>.ScdID,
	beq	.L311	@,
	ldr	sl, [r2, #780]	@ <variable>.ScdDrvMem.DownMsgMemAddr, <variable>.ScdDrvMem.DownMsgMemAddr
	movw	r7, #:lower16:190760	@ tmp150,
	movt	r7, #:upper16:190760	@ tmp150,
	movw	r8, #:lower16:190764	@ tmp153,
	movt	r8, #:upper16:190764	@ tmp153,
	movw	r4, #:lower16:190768	@ tmp156,
	str	sl, [ip, r7]	@ <variable>.ScdDrvMem.DownMsgMemAddr, <variable>.BufAddrCfg.DownMsgPhyAddr
	movt	r4, #:upper16:190768	@ tmp156,
	ldr	r6, [r2, #784]	@ <variable>.ScdDrvMem.pDownMsgMemVirAddr, <variable>.ScdDrvMem.pDownMsgMemVirAddr
	movw	r0, #:lower16:190772	@ tmp159,
	movt	r0, #:upper16:190772	@ tmp159,
	movw	r9, #:lower16:190820	@,
	movt	r9, #:upper16:190820	@,
	movw	sl, #:lower16:190776	@ tmp162,
	str	r6, [ip, r8]	@ <variable>.ScdDrvMem.pDownMsgMemVirAddr, <variable>.BufAddrCfg.pDownMsgVirAddr
	movt	sl, #:upper16:190776	@ tmp162,
	ldr	r5, [r2, #788]	@ <variable>.ScdDrvMem.DownMsgMemSize, <variable>.ScdDrvMem.DownMsgMemSize
	movw	r7, #:lower16:190780	@ tmp165,
	movw	r8, #:lower16:190784	@ tmp168,
	movt	r7, #:upper16:190780	@ tmp165,
	movt	r8, #:upper16:190784	@ tmp168,
	movw	r6, #:lower16:190812	@ tmp170,
	str	r5, [ip, r4]	@ <variable>.ScdDrvMem.DownMsgMemSize, <variable>.BufAddrCfg.DownMsgSize
	movt	r6, #:upper16:190812	@ tmp170,
	ldr	r4, [r2, #792]	@ <variable>.ScdDrvMem.UpMsgMemAddr, <variable>.ScdDrvMem.UpMsgMemAddr
	movw	r5, #:lower16:190816	@ tmp173,
	str	r9, [fp, #-56]	@, %sfp
	movw	r9, #:lower16:190824	@,
	movt	r9, #:upper16:190824	@,
	str	r9, [fp, #-48]	@, %sfp
	str	r4, [ip, r0]	@ <variable>.ScdDrvMem.UpMsgMemAddr, <variable>.BufAddrCfg.UpMsgPhyAddr
	movw	r0, #:lower16:190832	@,
	movt	r0, #:upper16:190832	@,
	str	r0, [fp, #-52]	@, %sfp
	ldr	r4, [r2, #796]	@, <variable>.ScdDrvMem.pUpMsgMemVirAddr
	movt	r5, #:upper16:190816	@ tmp173,
	movw	r9, #:lower16:190828	@ tmp182,
	movt	r9, #:upper16:190828	@ tmp182,
	mov	r0, r1	@ D.50713, ScdId
	str	r4, [ip, sl]	@, <variable>.BufAddrCfg.pUpMsgVirAddr
	ldr	sl, [r2, #800]	@, <variable>.ScdDrvMem.UpMsgMemSize
	str	sl, [ip, r7]	@, <variable>.BufAddrCfg.UpMsgSize
	mov	sl, #1152	@ tmp169,
	str	sl, [ip, r8]	@ tmp169, <variable>.BufAddrCfg.UpMsgNum
	ldr	r7, [r2, #804]	@ <variable>.ScdDrvMem.DvmMemAddr, <variable>.ScdDrvMem.DvmMemAddr
	str	r7, [ip, r6]	@ <variable>.ScdDrvMem.DvmMemAddr, <variable>.BufAddrCfg.DvmMemAddr
	ldr	r6, [r2, #808]	@ <variable>.ScdDrvMem.pDvmMemVirAddr, <variable>.ScdDrvMem.pDvmMemVirAddr
	str	r6, [ip, r5]	@ <variable>.ScdDrvMem.pDvmMemVirAddr, <variable>.BufAddrCfg.pDvmMemVirAddr
	ldr	r4, [fp, #-56]	@, %sfp
	ldr	r5, [r2, #812]	@ <variable>.ScdDrvMem.DvmMemSize, <variable>.ScdDrvMem.DvmMemSize
	str	r5, [ip, r4]	@ <variable>.ScdDrvMem.DvmMemSize, <variable>.BufAddrCfg.DvmMemSize
	ldr	r5, [fp, #-48]	@, %sfp
	ldr	r4, [r2, #816]	@ <variable>.ScdDrvMem.DspSedTopMemAddr, <variable>.ScdDrvMem.DspSedTopMemAddr
	str	r4, [ip, r5]	@ <variable>.ScdDrvMem.DspSedTopMemAddr, <variable>.BufAddrCfg.DspSedTopMemAddr
	ldr	r4, [r2, #820]	@ <variable>.ScdDrvMem.pDspSedTopMemVirAddr, <variable>.ScdDrvMem.pDspSedTopMemVirAddr
	str	r4, [ip, r9]	@ <variable>.ScdDrvMem.pDspSedTopMemVirAddr, <variable>.BufAddrCfg.pDspSedTopMemVirAddr
	ldr	r2, [r2, #824]	@ <variable>.ScdDrvMem.DspSedTopMemSize, <variable>.ScdDrvMem.DspSedTopMemSize
	str	r1, [ip, r3]	@ ScdId, <variable>.ScdID
	ldr	r9, [fp, #-52]	@, %sfp
	str	r2, [ip, r9]	@ <variable>.ScdDrvMem.DspSedTopMemSize, <variable>.BufAddrCfg.DspSedTopMemSize
.L311:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L317:
	mov	r3, r1	@, ScdId
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC55	@,
	movw	r2, #2052	@,
	movt	r1, #:upper16:.LC55	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50713,
	b	.L311	@
.L316:
	mov	r3, r0	@, SmID
	movw	r1, #:lower16:.LC54	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC54	@,
	movw	r2, #2046	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50713,
	b	.L311	@
	.fnend
	.size	SM_CfgBuf, .-SM_CfgBuf
	.align	2
	.global	SCDDRV_ExitSleep
	.type	SCDDRV_ExitSleep, %function
SCDDRV_ExitSleep:
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
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp135,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp135,
	mov	r4, r0	@ ScdId, ScdId
	ldr	r3, [r3, #8]	@ D.50320, g_vdm_hal_fun_ptr.pfun_SCDDRV_OpenHardware
	cmp	r3, #0	@ D.50320,
	beq	.L319	@,
	blx	r3	@ D.50320
	movw	r1, #:lower16:.LANCHOR0	@ tmp137,
	movt	r1, #:upper16:.LANCHOR0	@ tmp137,
	mov	r0, #0	@ tmp142,
	add	r4, r1, r4, asl #2	@, tmp140, tmp137, ScdId,
	str	r0, [r4, #768]	@ tmp142, s_eScdDrvSleepStage
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L319:
	mov	r0, r3	@, D.50320
	movw	r1, #:lower16:.LC56	@,
	movw	r2, #1437	@,
	movt	r1, #:upper16:.LC56	@,
	bl	dprint_vfmw	@
	movw	r1, #:lower16:.LANCHOR0	@ tmp137,
	movt	r1, #:upper16:.LANCHOR0	@ tmp137,
	mov	r0, #0	@ tmp142,
	add	r4, r1, r4, asl #2	@, tmp140, tmp137, ScdId,
	str	r0, [r4, #768]	@ tmp142, s_eScdDrvSleepStage
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	SCDDRV_ExitSleep, .-SCDDRV_ExitSleep
	.align	2
	.global	ReleaseStreamSeg
	.type	ReleaseStreamSeg, %function
ReleaseStreamSeg:
	.fnstart
.LFB1555:
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
	subs	r4, r0, #0	@ pStreamSegArray, pStreamSegArray
	mov	r5, r1	@ StreamID, StreamID
	bne	.L344	@,
.L323:
	mvn	r0, #0	@ Ret,
.L337:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L344:
	sub	r2, r1, #1152	@ tmp147, StreamID,
	movw	r3, #:lower16:-1154	@ tmp149,
	movt	r3, #:upper16:-1154	@ tmp149,
	cmp	r2, r3	@ tmp147, tmp149
	bls	.L323	@,
	cmn	r1, #1	@ StreamID,
	beq	.L345	@,
	movw	r3, #:lower16:92168	@ tmp198,
	movw	r2, #:lower16:92172	@ tmp199,
	movt	r3, #:upper16:92168	@ tmp198,
	movt	r2, #:upper16:92172	@ tmp199,
	ldr	r3, [r4, r3]	@ i.1771, <variable>.Head
	ldr	r0, [r4, r2]	@ temp.1781, <variable>.Tail
	cmp	r3, r0	@ i.1771, temp.1781
	beq	.L325	@,
	cmp	r1, r3	@ StreamID, i.1771
	movwne	r1, #:lower16:954437177	@ tmp288,
	movtne	r1, #:upper16:954437177	@ tmp288,
	bne	.L339	@,
	b	.L329	@
.L343:
	cmp	r5, r3	@ StreamID, i.1771
	beq	.L329	@,
.L339:
	add	r3, r3, #1	@ D.50235, i.1771,
	umull	ip, r2, r1, r3	@, tmp216, tmp288, D.50235
	mov	r2, r2, lsr #8	@ i.1771, tmp216,
	add	ip, r2, r2, asl #3	@, tmp220, i.1771, i.1771,
	sub	r3, r3, ip, asl #7	@ i.1771, D.50235, tmp220,
	cmp	r3, r0	@ i.1771, temp.1781
	bne	.L343	@,
.L325:
	mvn	r0, #2	@ Ret,
	b	.L337	@
.L329:
	add	sl, r5, r5, asl #2	@, tmp202, StreamID, StreamID,
	add	r1, r4, sl, asl #4	@, tmp206, pStreamSegArray, tmp202,
	add	sl, r1, #8	@ tmp207, tmp206,
	ldrsb	r0, [sl, #4]	@ <variable>.SegState, <variable>.SegState
	cmp	r0, #2	@ <variable>.SegState,
	bne	.L325	@,
.L328:
	ldrb	ip, [sl, #5]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	mov	lr, #0	@ tmp222,
	ldr	r2, [sl, #8]	@ <variable>.PhyAddr, <variable>.PhyAddr
	mov	r0, #26	@,
	ldr	r3, [sl, #12]	@ <variable>.LenInByte, <variable>.LenInByte
	movw	r1, #:lower16:.LC59	@,
	strb	lr, [sl, #4]	@ tmp222, <variable>.SegState
	movt	r1, #:upper16:.LC59	@,
	str	ip, [sp, #0]	@ <variable>.IsLastSeg,
	str	r5, [sp, #4]	@ StreamID,
	bl	dprint_vfmw	@
	movw	r1, #:lower16:92168	@ tmp228,
	movt	r1, #:upper16:92168	@ tmp228,
	ldr	r0, [r4, r1]	@ <variable>.Head, <variable>.Head
	cmp	r0, r5	@ <variable>.Head, StreamID
	beq	.L346	@,
.L332:
	movw	r3, #:lower16:92200	@ tmp262,
	movt	r3, #:upper16:92200	@ tmp262,
	ldr	r2, [sl, #12]	@ <variable>.LenInByte, <variable>.LenInByte
	mov	r0, #0	@ Ret,
	ldr	r1, [r4, r3]	@ <variable>.SegTotalSize, <variable>.SegTotalSize
	rsb	ip, r2, r1	@ tmp266, <variable>.LenInByte, <variable>.SegTotalSize
	bic	r2, ip, ip, asr #31	@ tmp267, tmp266
	str	r2, [r4, r3]	@ tmp267, <variable>.SegTotalSize
	b	.L337	@
.L345:
	movw	ip, #:lower16:92168	@ tmp150,
	movw	r1, #:lower16:92172	@ tmp151,
	movt	ip, #:upper16:92168	@ tmp150,
	movt	r1, #:upper16:92172	@ tmp151,
	ldr	sl, [r4, ip]	@ D.50206, <variable>.Head
	ldr	r0, [r4, r1]	@ <variable>.Tail, <variable>.Tail
	cmp	sl, r0	@ D.50206, <variable>.Tail
	beq	.L325	@,
	mov	r2, sl	@, D.50206
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC57	@,
	mov	r9, sl, asl #2	@ tmp270, D.50206,
	movt	r1, #:upper16:.LC57	@,
	mov	r5, sl	@ StreamID, D.50206
	bl	dprint_vfmw	@
	add	r3, r9, sl	@ tmp156, tmp270, D.50206
	add	r8, r3, #1	@ tmp157, tmp156,
	add	r8, r4, r8, asl #4	@, tmp160, pStreamSegArray, tmp157,
	ldr	r2, [r8, #4]	@ <variable>.LenInByte, <variable>.LenInByte
	cmp	r2, #0	@ <variable>.LenInByte,
	beq	.L326	@,
	mov	r6, r3, asl #1	@ tmp280, tmp156,
	add	r8, r8, #4	@ tmp287, tmp160,
	add	r7, r6, #1	@ tmp281, tmp280,
	mov	r6, #0	@ i.1769,
.L327:
	ldr	lr, [r4, r7, asl #3]	@ <variable>.VirAddr, <variable>.VirAddr
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC58	@,
	movt	r1, #:upper16:.LC58	@,
	ldrb	r2, [lr, r6]	@ zero_extendqisi2	@,* i.1769
	add	r6, r6, #1	@ i.1769, i.1769,
	bl	dprint_vfmw	@
	ldr	r1, [r8, #0]	@ <variable>.LenInByte, <variable>.LenInByte
	cmp	r6, #15	@ i.1769,
	movhi	r0, #0	@,
	movls	r0, #1	@,
	cmp	r1, r6	@ <variable>.LenInByte, i.1769
	movls	r0, #0	@,,
	cmp	r0, #0	@ tmp190,
	bne	.L327	@,
.L326:
	add	ip, r9, sl	@ tmp193, tmp270, D.50206
	movw	r1, #:lower16:.LC39	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC39	@,
	add	sl, r4, ip, asl #4	@, tmp196, pStreamSegArray, tmp193,
	add	sl, sl, #8	@ pSeg, tmp196,
	bl	dprint_vfmw	@
	b	.L328	@
.L346:
	movw	r7, #:lower16:92172	@ tmp277,
	movw	r6, #:lower16:954437177	@ tmp278,
	movt	r7, #:upper16:92172	@ tmp277,
	movt	r6, #:upper16:954437177	@ tmp278,
	movw	r8, #1151	@ tmp273,
	b	.L336	@
.L333:
	ldr	r0, [r4, r7]	@ temp.1774, <variable>.Tail
	add	r3, r5, #1	@ temp.1776, i,
	add	r1, r5, r5, asl #2	@, tmp241, i, i,
	cmp	r0, r5	@ temp.1774, i
	umull	ip, r2, r6, r3	@, tmp256, tmp278, temp.1776
	add	ip, r4, r1, asl #4	@, tmp245, pStreamSegArray, tmp241,
	beq	.L347	@,
	cmp	r5, r8	@ i, tmp273
	mov	r2, r2, lsr #8	@ i, tmp256,
	bhi	.L335	@,
	ldrsb	r0, [ip, #12]	@ <variable>.SegState, <variable>.SegState
	cmp	r0, #0	@ <variable>.SegState,
	bne	.L348	@,
.L335:
	add	r0, r2, r2, asl #3	@, tmp260, i, i,
	sub	r5, r3, r0, asl #7	@ i, temp.1776, tmp260,
.L336:
	cmp	r5, r8	@ i, tmp273
	bls	.L333	@,
	movw	r1, #:lower16:.LC60	@,
	movw	r2, #:lower16:.LANCHOR1	@,
	movt	r1, #:upper16:.LC60	@,
	movt	r2, #:upper16:.LANCHOR1	@,
	mov	r0, #1	@,
	bl	dprint_vfmw	@
	b	.L333	@
.L347:
	movw	ip, #:lower16:92196	@ tmp236,
	movt	ip, #:upper16:92196	@ tmp236,
	movw	r2, #:lower16:92168	@ tmp234,
	movw	r3, #:lower16:92192	@ tmp235,
	ldr	r1, [r4, ip]	@ <variable>.SegBufWriteAddr, <variable>.SegBufWriteAddr
	movt	r2, #:upper16:92168	@ tmp234,
	movt	r3, #:upper16:92192	@ tmp235,
	str	r5, [r4, r2]	@ i, <variable>.Head
	str	r1, [r4, r3]	@ <variable>.SegBufWriteAddr, <variable>.SegBufReadAddr
	b	.L332	@
.L348:
	add	r1, r1, #1	@ tmp254, tmp241,
	movw	ip, #:lower16:92168	@ tmp249,
	movt	ip, #:upper16:92168	@ tmp249,
	movw	r3, #:lower16:92192	@ tmp250,
	movt	r3, #:upper16:92192	@ tmp250,
	str	r5, [r4, ip]	@ i, <variable>.Head
	ldr	r2, [r4, r1, asl #4]	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	r2, [r4, r3]	@ <variable>.PhyAddr, <variable>.SegBufReadAddr
	b	.L332	@
	.fnend
	.size	ReleaseStreamSeg, .-ReleaseStreamSeg
	.align	2
	.global	SM_ReleaseStreamSeg
	.type	SM_ReleaseStreamSeg, %function
SM_ReleaseStreamSeg:
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
	add	r0, r0, r0, asl #1	@, tmp142, SmID, SmID,
	movw	r2, #:lower16:.LANCHOR0	@ tmp138,
	movt	r2, #:upper16:.LANCHOR0	@ tmp138,
	add	r3, r2, r0, asl #4	@, tmp144, tmp138, tmp142,
	ldr	r0, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r0, #0	@ pSmInstArray,
	mvneq	r0, #0	@ ret,
	ldmeqfd	sp, {fp, sp, pc}	@
	add	ip, r0, #98304	@, pSmInstArray,
	add	r0, ip, #224	@,,
	bl	ReleaseStreamSeg	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SM_ReleaseStreamSeg, .-SM_ReleaseStreamSeg
	.align	2
	.global	GetRawNumOffsert
	.type	GetRawNumOffsert, %function
GetRawNumOffsert:
	.fnstart
.LFB1543:
	@ args = 32, pretend = 0, frame = 32
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
	rsbs	ip, r0, #1	@ tmp161, pRawStreamArray
	movcc	ip, #0	@ tmp161
	orrs	ip, ip, r1, lsr #31	@,, tmp161, Len,
	beq	.L366	@,
.L354:
	mvn	ip, #0	@ D.49908,
.L362:
	mov	r0, ip	@, D.49908
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L366:
	cmp	r2, #0	@ pNum,
	cmpne	r3, #0	@, pOffset,
	beq	.L354	@,
	mov	ip, #98304	@ tmp173,
	movw	sl, #:lower16:98308	@ tmp180,
	ldr	r8, [r0, ip]	@ D.49914, <variable>.Head
	movt	sl, #:upper16:98308	@ tmp180,
	movw	r4, #:lower16:98316	@ tmp179,
	movt	r4, #:upper16:98316	@ tmp179,
	ldr	r6, [r0, sl]	@ <variable>.Tail, <variable>.Tail
	mov	r5, r8, asl #1	@ tmp333, D.49914,
	ldr	sl, [r0, r4]	@ D.49916, <variable>.FirstPacketOffset
	add	r7, r5, r8	@ tmp176, tmp333, D.49914
	add	r4, r5, r8	@ tmp184, tmp333, D.49914
	subs	r6, r6, r8	@ RawNum, <variable>.Tail, D.49914
	add	r9, r0, r7, asl #5	@, tmp178, pRawStreamArray, tmp176,
	addmi	r6, r6, #1024	@ RawNum, RawNum,
	add	ip, r6, r8	@, RawNum, D.49914
	ldr	r6, [fp, #4]	@, pPts
	ldr	r7, [r9, #8]	@ D.49915, <variable>.Length
	mov	r9, r4, asl #5	@ tmp186, tmp184,
	str	ip, [fp, #-48]	@, %sfp
	add	ip, r9, #16	@ tmp187, tmp186,
	add	r5, r0, r4, asl #5	@, tmp194, pRawStreamArray, tmp184,
	ldrd	r8, [ip, r0]	@ <variable>.Pts, tmp187, pRawStreamArray
	mov	r4, r5	@ tmp210, tmp194
	strd	r8, [r6]	@ <variable>.Pts,
	ldr	r6, [fp, #8]	@, pUsertag
	ldrd	r8, [r5, #32]	@ <variable>.UserTag, tmp194,
	strd	r8, [r6]	@ <variable>.UserTag,
	ldrd	r8, [ip, r0]	@ <variable>.Pts, tmp187, pRawStreamArray
	ldr	ip, [fp, #32]	@, pRawPts
	strd	r8, [ip]	@ <variable>.Pts,
	ldrd	r8, [r5, #40]	@ <variable>.DispTime, tmp210,
	ldr	r5, [fp, #12]	@, pDisptime
	strd	r8, [r5]	@ <variable>.DispTime,
	ldr	r5, [fp, #16]	@, pDispEnableFlag
	ldr	r6, [r4, #56]	@ <variable>.DispEnableFlag, <variable>.DispEnableFlag
	str	r6, [r5, #0]	@ <variable>.DispEnableFlag,
	ldr	r6, [fp, #20]	@, pDispFrameDistance
	ldr	ip, [r4, #60]	@ <variable>.DispFrameDistance, <variable>.DispFrameDistance
	str	ip, [r6, #0]	@ <variable>.DispFrameDistance,
	ldr	r8, [fp, #24]	@, pDistanceBeforeFirstFrame
	ldr	ip, [r4, #64]	@ <variable>.DistanceBeforeFirstFrame, <variable>.DistanceBeforeFirstFrame
	str	ip, [r8, #0]	@ <variable>.DistanceBeforeFirstFrame,
	ldr	r9, [fp, #28]	@, pGopNum
	ldr	ip, [r4, #68]	@ <variable>.GopNum, <variable>.GopNum
	str	ip, [r9, #0]	@ <variable>.GopNum,
	mov	ip, #98304	@ tmp245,
	ldr	r4, [r0, ip]	@ i, <variable>.Head
	ldr	ip, [fp, #-48]	@, %sfp
	cmp	ip, r4	@, i
	ble	.L356	@,
	rsb	r6, sl, r7	@ TotalLen, D.49916, D.49915
	cmp	r1, r6	@ Len, TotalLen
	blt	.L356	@,
	str	r6, [fp, #-72]	@ TotalLen, %sfp
	mov	sl, r1	@ Len, Len
	str	r2, [fp, #-52]	@ pNum, %sfp
	str	r3, [fp, #-56]	@ pOffset, %sfp
	b	.L365	@
.L359:
	ldr	r7, [fp, #-48]	@, %sfp
	ldr	r9, [fp, #4]	@, pPts
	cmp	r7, r4	@, i
	ldrd	r6, [fp, #-68]	@,,
	strd	r6, [r9]	@,
	ldr	ip, [fp, #8]	@, pUsertag
	ldrd	r8, [r1, #32]	@ <variable>.UserTag, tmp270,
	strd	r8, [ip]	@ <variable>.UserTag,
	ldr	r1, [fp, #32]	@, pRawPts
	ldrd	r8, [r2, #16]	@ <variable>.Pts, tmp278,
	strd	r8, [r1]	@ <variable>.Pts,
	ldr	r2, [fp, #12]	@, pDisptime
	ldrd	r8, [r3, #40]	@ <variable>.DispTime, tmp286,
	strd	r8, [r2]	@ <variable>.DispTime,
	ldr	r6, [fp, #16]	@, pDispEnableFlag
	ldr	ip, [r3, #56]	@ <variable>.DispEnableFlag, <variable>.DispEnableFlag
	str	ip, [r6, #0]	@ <variable>.DispEnableFlag,
	ldr	r1, [fp, #20]	@, pDispFrameDistance
	ldr	r2, [r3, #60]	@ <variable>.DispFrameDistance, <variable>.DispFrameDistance
	str	r2, [r1, #0]	@ <variable>.DispFrameDistance,
	ldr	r8, [fp, #24]	@, pDistanceBeforeFirstFrame
	ldr	r6, [r3, #64]	@ <variable>.DistanceBeforeFirstFrame, <variable>.DistanceBeforeFirstFrame
	str	r6, [r8, #0]	@ <variable>.DistanceBeforeFirstFrame,
	ldr	r9, [fp, #28]	@, pGopNum
	ldr	r7, [r3, #68]	@ <variable>.GopNum, <variable>.GopNum
	str	r7, [r9, #0]	@ <variable>.GopNum,
	ble	.L367	@,
	ldr	r1, [fp, #-72]	@, %sfp
	cmp	sl, r1	@ Len,
	blt	.L368	@,
.L365:
	add	r4, r4, #1	@ i, i,
	mvn	r7, #0	@,
	mvn	r6, #0	@,
	mov	r5, r4, asr #31	@ tmp246, i,
	mov	r1, r5, lsr #22	@ tmp247, tmp246,
	add	ip, r4, r1	@ tmp248, i, tmp247
	mov	r9, ip, asl #22	@ tmp249, tmp248,
	mov	r8, r9, lsr #22	@ tmp249, tmp249,
	rsb	r5, r1, r8	@ Index, tmp247, tmp249
	mov	r2, r5, asl #1	@, Index,
	str	r2, [fp, #-76]	@, %sfp
	add	r3, r2, r5	@ tmp268,, Index
	add	r1, r0, r3, asl #5	@, tmp270, pRawStreamArray, tmp268,
	ldrd	r8, [r1, #16]	@, tmp263,
	mov	r2, r1	@ tmp278, tmp270
	mov	r3, r1	@ tmp286, tmp278
	cmp	r9, r7	@,
	cmpeq	r8, r6	@,
	ldr	r7, [fp, #-72]	@, %sfp
	strd	r8, [fp, #-68]	@,,
	ldr	ip, [r1, #8]	@ <variable>.Length, <variable>.Length
	add	r7, r7, ip	@,, <variable>.Length
	str	r7, [fp, #-72]	@, %sfp
	ldreq	r9, [fp, #4]	@, pPts
	ldreqd	r8, [r9]	@,
	streqd	r8, [fp, #-68]	@,,
	b	.L359	@
.L367:
	ldr	r6, [fp, #-72]	@ TotalLen, %sfp
	mov	r1, sl	@ Len, Len
	ldr	r2, [fp, #-52]	@ pNum, %sfp
	ldr	r3, [fp, #-56]	@ pOffset, %sfp
	ldr	r7, [fp, #-76]	@ tmp332, %sfp
.L358:
	mov	ip, #98304	@ tmp321,
	ldr	ip, [r0, ip]	@ temp.1841, <variable>.Head
	cmp	ip, r4	@ temp.1841, i
	beq	.L356	@,
	add	r5, r7, r5	@ tmp325, tmp332, Index
	rsb	r4, ip, r4	@ tmp329, temp.1841, i
	mov	ip, #0	@ D.49908,
	add	r0, r0, r5, asl #5	@, tmp327, pRawStreamArray, tmp325,
	ldr	r0, [r0, #8]	@ <variable>.Length, <variable>.Length
	str	r4, [r2, #0]	@ tmp329,* pNum
	rsb	r6, r0, r6	@ TotalLen.1843, <variable>.Length, TotalLen
	rsb	r0, r6, r1	@ tmp330, TotalLen.1843, Len
	str	r0, [r3, #0]	@ tmp330,* pOffset
	b	.L362	@
.L368:
	mov	r6, r1	@ TotalLen,
	ldr	r2, [fp, #-52]	@ pNum, %sfp
	mov	r1, sl	@ Len, Len
	ldr	r3, [fp, #-56]	@ pOffset, %sfp
	ldr	r7, [fp, #-76]	@ tmp332, %sfp
	b	.L358	@
.L356:
	mov	ip, #0	@ tmp322,
	str	ip, [r2, #0]	@ tmp322,* pNum
	str	r1, [r3, #0]	@ Len,* pOffset
	b	.L362	@
	.fnend
	.size	GetRawNumOffsert, .-GetRawNumOffsert
	.align	2
	.global	GetSegPts
	.type	GetSegPts, %function
GetSegPts:
	.fnstart
.LFB1592:
	@ args = 0, pretend = 0, frame = 8
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
	mov	r4, r3	@ pSegPacket, pSegPacket
	mvn	r9, #0	@ tmp144,
	mvn	r6, #0	@ tmp140,
	str	r9, [r3, #68]	@ tmp144, <variable>.GopNum
	mvn	r7, #0	@,
	str	r9, [r4, #56]	@ tmp144, <variable>.DispEnableFlag
	mov	r5, r2	@ pLastPts, pLastPts
	strd	r6, [r3, #24]	@ tmp140, pSegPacket,
	sub	r2, fp, #48	@,,
	strd	r6, [r3, #40]	@ tmp140, pSegPacket,
	mov	lr, #0	@ tmp138,
	strd	r6, [r3, #32]	@ tmp140, pSegPacket,
	sub	r3, fp, #52	@,,
	str	r9, [r4, #60]	@ tmp144, <variable>.DispFrameDistance
	add	r8, r4, #24	@ tmp150, pSegPacket,
	str	r9, [r4, #64]	@ tmp144, <variable>.DistanceBeforeFirstFrame
	add	sl, r4, #40	@ tmp151, pSegPacket,
	strd	r6, [r4, #48]	@ tmp140, pSegPacket,
	add	ip, r4, #48	@ tmp152, pSegPacket,
	str	r8, [sp, #0]	@ tmp150,
	add	r9, r4, #56	@ tmp153, pSegPacket,
	add	r8, r4, #60	@, pSegPacket,
	str	sl, [sp, #4]	@ tmp151,
	str	r8, [sp, #16]	@,
	add	sl, r4, #64	@ tmp155, pSegPacket,
	str	ip, [sp, #8]	@ tmp152,
	add	r8, r4, #68	@ tmp156, pSegPacket,
	add	ip, r4, #32	@ tmp157, pSegPacket,
	str	lr, [fp, #-52]	@ tmp138, Offset
	str	r9, [sp, #12]	@ tmp153,
	str	sl, [sp, #20]	@ tmp155,
	str	r8, [sp, #24]	@ tmp156,
	str	ip, [sp, #28]	@ tmp157,
	str	lr, [fp, #-48]	@ tmp138, Num
	bl	GetRawNumOffsert	@
	ldrd	r2, [r4, #24]	@ D.51626, pSegPacket,
	ldrd	r0, [r5]	@ tmp158,* pLastPts
	cmp	r1, r3	@ tmp158, D.51626
	cmpeq	r0, r2	@ tmp158, D.51626
	beq	.L373	@,
	strd	r2, [r5]	@ D.51626,* pLastPts
.L372:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L373:
	strd	r6, [r4, #24]	@ tmp140, pSegPacket,
	b	.L372	@
	.fnend
	.size	GetSegPts, .-GetSegPts
	.align	2
	.global	DeleteRawPacket
	.type	DeleteRawPacket, %function
DeleteRawPacket:
	.fnstart
.LFB1541:
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
	cmp	r0, #0	@ pRawStreamArray,
	cmpne	r1, #0	@, DelNum,
	mov	r9, r1	@ DelNum, DelNum
	mov	r4, r0	@ pRawStreamArray, pRawStreamArray
	movne	r6, #0	@, tmp170
	moveq	r6, #1	@, tmp170
	beq	.L410	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp261,
	movt	r3, #:upper16:.LANCHOR0	@ tmp261,
	ldr	r2, [r3, #40]	@ D.53580, <variable>.pSmInstArray
	cmp	r2, #0	@ D.53580,
	beq	.L377	@,
	add	r2, r2, #200	@ tmp172, D.53580,
	cmp	r0, r2	@ pRawStreamArray, tmp172
	beq	.L378	@,
.L377:
	ldr	r2, [r3, #88]	@ temp.1906, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1906,
	beq	.L379	@,
	add	r0, r2, #200	@ tmp174, temp.1906,
	cmp	r4, r0	@ pRawStreamArray, tmp174
	moveq	r6, #1	@ SmID,
	beq	.L378	@,
.L379:
	ldr	r2, [r3, #136]	@ temp.1908, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1908,
	beq	.L380	@,
	add	r1, r2, #200	@ tmp176, temp.1908,
	cmp	r4, r1	@ pRawStreamArray, tmp176
	moveq	r6, #2	@ SmID,
	beq	.L378	@,
.L380:
	ldr	r2, [r3, #184]	@ temp.1910, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1910,
	beq	.L381	@,
	add	ip, r2, #200	@ tmp178, temp.1910,
	cmp	r4, ip	@ pRawStreamArray, tmp178
	moveq	r6, #3	@ SmID,
	beq	.L378	@,
.L381:
	ldr	r2, [r3, #232]	@ temp.1912, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1912,
	beq	.L382	@,
	add	lr, r2, #200	@ tmp180, temp.1912,
	cmp	r4, lr	@ pRawStreamArray, tmp180
	moveq	r6, #4	@ SmID,
	beq	.L378	@,
.L382:
	ldr	r2, [r3, #280]	@ temp.1914, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1914,
	beq	.L383	@,
	add	r2, r2, #200	@ tmp182, temp.1914,
	cmp	r4, r2	@ pRawStreamArray, tmp182
	moveq	r6, #5	@ SmID,
	beq	.L378	@,
.L383:
	ldr	r2, [r3, #328]	@ temp.1916, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1916,
	beq	.L384	@,
	add	r0, r2, #200	@ tmp184, temp.1916,
	cmp	r4, r0	@ pRawStreamArray, tmp184
	moveq	r6, #6	@ SmID,
	beq	.L378	@,
.L384:
	ldr	r2, [r3, #376]	@ temp.1918, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1918,
	beq	.L385	@,
	add	r1, r2, #200	@ tmp186, temp.1918,
	cmp	r4, r1	@ pRawStreamArray, tmp186
	moveq	r6, #7	@ SmID,
	beq	.L378	@,
.L385:
	ldr	r2, [r3, #424]	@ temp.1920, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1920,
	beq	.L386	@,
	add	ip, r2, #200	@ tmp188, temp.1920,
	cmp	r4, ip	@ pRawStreamArray, tmp188
	moveq	r6, #8	@ SmID,
	beq	.L378	@,
.L386:
	ldr	r2, [r3, #472]	@ temp.1922, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1922,
	beq	.L387	@,
	add	lr, r2, #200	@ tmp190, temp.1922,
	cmp	r4, lr	@ pRawStreamArray, tmp190
	moveq	r6, #9	@ SmID,
	beq	.L378	@,
.L387:
	ldr	r2, [r3, #520]	@ temp.1924, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1924,
	beq	.L388	@,
	add	r2, r2, #200	@ tmp192, temp.1924,
	cmp	r4, r2	@ pRawStreamArray, tmp192
	moveq	r6, #10	@ SmID,
	beq	.L378	@,
.L388:
	ldr	r2, [r3, #568]	@ temp.1926, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1926,
	beq	.L389	@,
	add	r0, r2, #200	@ tmp194, temp.1926,
	cmp	r4, r0	@ pRawStreamArray, tmp194
	moveq	r6, #11	@ SmID,
	beq	.L378	@,
.L389:
	ldr	r2, [r3, #616]	@ temp.1928, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1928,
	beq	.L390	@,
	add	r1, r2, #200	@ tmp196, temp.1928,
	cmp	r4, r1	@ pRawStreamArray, tmp196
	moveq	r6, #12	@ SmID,
	beq	.L378	@,
.L390:
	ldr	r2, [r3, #664]	@ temp.1930, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1930,
	beq	.L391	@,
	add	ip, r2, #200	@ tmp198, temp.1930,
	cmp	r4, ip	@ pRawStreamArray, tmp198
	moveq	r6, #13	@ SmID,
	beq	.L378	@,
.L391:
	ldr	r2, [r3, #712]	@ temp.1932, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1932,
	beq	.L392	@,
	add	lr, r2, #200	@ tmp200, temp.1932,
	cmp	r4, lr	@ pRawStreamArray, tmp200
	moveq	r6, #14	@ SmID,
	beq	.L378	@,
.L392:
	ldr	r2, [r3, #760]	@ temp.1904, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.1904,
	beq	.L393	@,
	add	r2, r2, #200	@ tmp202, temp.1904,
	cmp	r4, r2	@ pRawStreamArray, tmp202
	beq	.L394	@,
.L393:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC61	@,
	mov	r2, #660	@,
	movt	r1, #:upper16:.LC61	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.49797,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L394:
	mov	r6, #15	@ SmID,
.L378:
	movw	ip, #:lower16:98308	@ tmp205,
	movt	ip, #:upper16:98308	@ tmp205,
	mov	r1, #98304	@ tmp204,
	ldr	r0, [r4, ip]	@ D.49804, <variable>.Tail
	ldr	r7, [r4, r1]	@ D.49803, <variable>.Head
	cmp	r7, r0	@ D.49803, D.49804
	addgt	r0, r0, #1024	@ tmp206, D.49804,
	rsb	r2, r7, r0	@ PacketNum, D.49803, tmp206
	cmp	r2, r9	@ PacketNum, DelNum
	bcc	.L411	@,
	add	sl, r7, r7, asl #1	@, tmp210, D.49803, D.49803,
	add	r6, r6, r6, asl #1	@, tmp266, SmID, SmID,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC63	@,
	mov	lr, sl, asl #2	@ tmp217, tmp210,
	add	r6, r3, r6, asl #4	@, tmp269, tmp261, tmp266,
	add	r8, lr, #1	@ tmp218, tmp217,
	ldr	r2, [r4, sl, asl #5]	@, <variable>.PhyAddr
	movt	r1, #:upper16:.LC63	@,
	sub	r5, r9, #1	@ tmp271, DelNum,
	ldr	r3, [r4, r8, asl #3]	@, <variable>.Length
	and	sl, r5, #1	@ tmp273, tmp271,
	bl	dprint_vfmw	@
	ldr	r3, [r6, #40]!	@ D.49819, <variable>.pSmInstArray
	movw	r5, #:lower16:98524	@ tmp270,
	movt	r5, #:upper16:98524	@ tmp270,
	ldr	r2, [r4, r8, asl #3]	@ <variable>.Length, <variable>.Length
	add	r8, r7, #1	@ D.49823, D.49803,
	ldr	r1, [r3, r5]	@ <variable>.RawPacketArray.RawTotalSize, <variable>.RawPacketArray.RawTotalSize
	cmp	r9, #1	@ DelNum,
	mov	r7, r8, asl #22	@ j, D.49823,
	mov	r8, #1	@ i,
	rsb	ip, r2, r1	@ tmp237, <variable>.Length, <variable>.RawPacketArray.RawTotalSize
	str	ip, [r3, r5]	@ tmp237, <variable>.RawPacketArray.RawTotalSize
	ldr	r3, [r6, #0]	@ temp.1902, <variable>.pSmInstArray
	mov	r7, r7, lsr #22	@ j, j,
	ldr	r0, [r3, r5]	@ <variable>.RawPacketArray.RawTotalSize, <variable>.RawPacketArray.RawTotalSize
	bic	r2, r0, r0, asr #31	@ tmp249, <variable>.RawPacketArray.RawTotalSize
	str	r2, [r3, r5]	@ tmp249, <variable>.RawPacketArray.RawTotalSize
	bls	.L407	@,
	cmp	sl, #0	@ tmp273,
	beq	.L398	@,
	add	r8, r7, r7, asl #1	@, tmp324, j, j,
	movw	r1, #:lower16:.LC63	@,
	mov	r0, #26	@,
	movt	r1, #:upper16:.LC63	@,
	mov	sl, r8, asl #2	@ tmp328, tmp324,
	ldr	r2, [r4, r8, asl #5]	@, <variable>.PhyAddr
	add	sl, sl, #1	@ tmp329, tmp328,
	mov	r8, #2	@ i,
	b	.L409	@
.L398:
	add	r3, r7, r7, asl #1	@, tmp278, j, j,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC63	@,
	movt	r1, #:upper16:.LC63	@,
	mov	lr, r3, asl #2	@ tmp282, tmp278,
	ldr	r2, [r4, r3, asl #5]	@, <variable>.PhyAddr
	add	sl, lr, #1	@ tmp283, tmp282,
	add	r8, r8, #1	@ tmp274, i,
	add	r8, r8, #1	@ i, tmp274,
	ldr	r3, [r4, sl, asl #3]	@, <variable>.Length
	bl	dprint_vfmw	@
	ldr	r3, [r6, #0]	@ D.49819, <variable>.pSmInstArray
	add	r1, r7, #1	@ D.49823, j,
	ldr	r2, [r4, sl, asl #3]	@ <variable>.Length, <variable>.Length
	mov	r0, #26	@,
	ldr	ip, [r3, r5]	@ <variable>.RawPacketArray.RawTotalSize, <variable>.RawPacketArray.RawTotalSize
	mov	r7, r1, asl #22	@ j, D.49823,
	movw	r1, #:lower16:.LC63	@,
	movt	r1, #:upper16:.LC63	@,
	rsb	r2, r2, ip	@ tmp293, <variable>.Length, <variable>.RawPacketArray.RawTotalSize
	str	r2, [r3, r5]	@ tmp293, <variable>.RawPacketArray.RawTotalSize
	ldr	r2, [r6, #0]	@ temp.1902, <variable>.pSmInstArray
	mov	r7, r7, lsr #22	@ j, j,
	add	r3, r7, r7, asl #1	@, tmp302, j, j,
	ldr	ip, [r2, r5]	@ <variable>.RawPacketArray.RawTotalSize, <variable>.RawPacketArray.RawTotalSize
	mov	sl, r3, asl #2	@ tmp306, tmp302,
	bic	ip, ip, ip, asr #31	@ tmp296, <variable>.RawPacketArray.RawTotalSize
	str	ip, [r2, r5]	@ tmp296, <variable>.RawPacketArray.RawTotalSize
	ldr	r2, [r4, r3, asl #5]	@, <variable>.PhyAddr
	add	sl, sl, #1	@ tmp307, tmp306,
.L409:
	ldr	r3, [r4, sl, asl #3]	@, <variable>.Length
	bl	dprint_vfmw	@
	ldr	r3, [r6, #0]	@ D.49819, <variable>.pSmInstArray
	ldr	r2, [r4, sl, asl #3]	@ <variable>.Length, <variable>.Length
	add	ip, r7, #1	@ D.49823, j,
	cmp	r9, r8	@ DelNum, i
	ldr	r1, [r3, r5]	@ <variable>.RawPacketArray.RawTotalSize, <variable>.RawPacketArray.RawTotalSize
	mov	r7, ip, asl #22	@ j, D.49823,
	rsb	r0, r2, r1	@ tmp339, <variable>.Length, <variable>.RawPacketArray.RawTotalSize
	str	r0, [r3, r5]	@ tmp339, <variable>.RawPacketArray.RawTotalSize
	ldr	r3, [r6, #0]	@ temp.1902, <variable>.pSmInstArray
	mov	r7, r7, lsr #22	@ j, j,
	ldr	ip, [r3, r5]	@ <variable>.RawPacketArray.RawTotalSize, <variable>.RawPacketArray.RawTotalSize
	bic	r2, ip, ip, asr #31	@ tmp342, <variable>.RawPacketArray.RawTotalSize
	str	r2, [r3, r5]	@ tmp342, <variable>.RawPacketArray.RawTotalSize
	bhi	.L398	@,
.L407:
	mov	r0, #98304	@ tmp251,
	movw	ip, #:lower16:98316	@ tmp258,
	ldr	r1, [r4, r0]	@ <variable>.Head, <variable>.Head
	movt	ip, #:upper16:98316	@ tmp258,
	mov	r2, #0	@ tmp259,
	add	r9, r9, r1	@ D.49826, DelNum, <variable>.Head
	str	r2, [r4, ip]	@ tmp259, <variable>.FirstPacketOffset
	cmp	r9, #1024	@ D.49826,
	str	r9, [r4, r0]	@ D.49826, <variable>.Head
	subge	r9, r9, #1024	@ tmp257, D.49826,
	strge	r9, [r4, r0]	@ tmp257, <variable>.Head
	mov	r0, r2	@ D.49797, tmp259
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L411:
	movw	r1, #:lower16:.LC62	@,
	mov	r3, r9	@, DelNum
	mov	r0, #26	@,
	movt	r1, #:upper16:.LC62	@,
	bl	dprint_vfmw	@
.L410:
	mvn	r0, #0	@ D.49797,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	.fnend
	.size	DeleteRawPacket, .-DeleteRawPacket
	.align	2
	.global	DeleteRawLen
	.type	DeleteRawLen, %function
DeleteRawLen:
	.fnstart
.LFB1544:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #92
	sub	sp, sp, #92	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	rsbs	r6, r0, #1	@ tmp144, pRawStreamArray
	movcc	r6, #0	@ tmp144
	mov	r5, r0	@ pRawStreamArray, pRawStreamArray
	orrs	r6, r6, r1, lsr #31	@, tmp148, tmp144, DelLen,
	bne	.L413	@,
	movw	r2, #:lower16:98324	@ tmp151,
	movw	r4, #:lower16:98316	@ tmp152,
	movt	r2, #:upper16:98324	@ tmp151,
	movt	r4, #:upper16:98316	@ tmp152,
	str	r6, [fp, #-32]	@ tmp148, DelNum
	str	r6, [fp, #-36]	@ tmp148, RawPacketOffSet
	ldr	ip, [r0, r2]	@ <variable>.RawTotalSize, <variable>.RawTotalSize
	ldr	r2, [r0, r4]	@ <variable>.FirstPacketOffset, <variable>.FirstPacketOffset
	subs	r2, ip, r2	@ TotallLen, <variable>.RawTotalSize, <variable>.FirstPacketOffset
	bmi	.L413	@,
	cmp	r1, r2	@ DelLen, TotallLen
	ble	.L422	@,
.L413:
	mvn	r0, #0	@ Ret,
.L416:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L422:
	sub	r2, fp, #32	@,,
	sub	r3, fp, #36	@,,
	sub	ip, fp, #60	@ tmp157,,
	sub	lr, fp, #68	@ tmp158,,
	str	ip, [sp, #0]	@ tmp157,
	sub	ip, fp, #76	@ tmp159,,
	str	lr, [sp, #4]	@ tmp158,
	sub	lr, fp, #40	@ tmp160,,
	str	ip, [sp, #8]	@ tmp159,
	sub	ip, fp, #44	@ tmp161,,
	str	lr, [sp, #12]	@ tmp160,
	sub	lr, fp, #48	@ tmp162,,
	str	ip, [sp, #16]	@ tmp161,
	sub	ip, fp, #52	@ tmp163,,
	str	lr, [sp, #20]	@ tmp162,
	sub	lr, fp, #84	@ tmp164,,
	str	ip, [sp, #24]	@ tmp163,
	str	lr, [sp, #28]	@ tmp164,
	bl	GetRawNumOffsert	@
	ldr	r1, [fp, #-32]	@, DelNum
	mov	r0, r5	@, pRawStreamArray
	bl	DeleteRawPacket	@
	movw	r1, #:lower16:98308	@ tmp167,
	movt	r1, #:upper16:98308	@ tmp167,
	mov	ip, #98304	@ tmp166,
	ldr	r2, [r5, ip]	@ D.53598, <variable>.Head
	ldr	r3, [r5, r1]	@ <variable>.Tail, <variable>.Tail
	ldr	r1, [fp, #-36]	@ RawPacketOffSet.477, RawPacketOffSet
	cmp	r2, r3	@ D.53598, <variable>.Tail
	mvneq	r0, #2	@ Ret,
	beq	.L416	@,
	add	ip, r2, r2, asl #1	@, tmp173, D.53598, D.53598,
	ldr	r0, [r5, r4]	@ <variable>.FirstPacketOffset, <variable>.FirstPacketOffset
	add	lr, r5, ip, asl #5	@, tmp175, pRawStreamArray, tmp173,
	add	r2, r1, r0	@ TargetOffset, RawPacketOffSet.477, <variable>.FirstPacketOffset
	ldr	r3, [lr, #8]	@ <variable>.Length, <variable>.Length
	cmp	r2, r3	@ TargetOffset, <variable>.Length
	strlt	r2, [r5, r4]	@ TargetOffset, <variable>.FirstPacketOffset
	movlt	r0, r6	@ Ret, tmp148
	blt	.L416	@,
	b	.L413	@
	.fnend
	.size	DeleteRawLen, .-DeleteRawLen
	.align	2
	.global	DeleteLastSendRaw
	.type	DeleteLastSendRaw, %function
DeleteLastSendRaw:
	.fnstart
.LFB1545:
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
	cmp	r0, #15	@ SmID,
	ldmhifd	sp, {r4, r5, fp, sp, pc}	@
	add	r0, r0, r0, asl #1	@, tmp140, SmID, SmID,
	movw	r1, #:lower16:.LANCHOR0	@ tmp136,
	movt	r1, #:upper16:.LANCHOR0	@ tmp136,
	add	r3, r1, r0, asl #4	@, tmp142, tmp136, tmp140,
	ldr	r5, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r5, #0	@ pSmInstArray,
	beq	.L427	@,
	movw	r4, #:lower16:190744	@ tmp145,
	movt	r4, #:upper16:190744	@ tmp145,
	ldr	r1, [r5, r4]	@ LastPushRawNum, <variable>.SmPushRaw.PushRawNum
	cmp	r1, #0	@ LastPushRawNum,
	ldmlefd	sp, {r4, r5, fp, sp, pc}	@
	add	r0, r5, #200	@, pSmInstArray,
	bl	DeleteRawPacket	@
	mov	r2, #0	@ tmp148,
	str	r2, [r5, r4]	@ tmp148, <variable>.SmPushRaw.PushRawNum
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L427:
	mov	r0, r5	@, pSmInstArray
	movw	r1, #:lower16:.LC64	@,
	mov	r2, #924	@,
	movt	r1, #:upper16:.LC64	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	DeleteLastSendRaw, .-DeleteLastSendRaw
	.align	2
	.global	SetMaxSegSize
	.type	SetMaxSegSize, %function
SetMaxSegSize:
	.fnstart
.LFB1623:
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
	mov	r4, r1	@ pSmCfg, pSmCfg
	mov	r5, r0	@ ChanID, ChanID
	bl	VCTRL_GetChanCapLevel	@
	cmp	r0, #32	@ eCapLevel,
	bhi	.L435	@,
	cmp	r0, #25	@ eCapLevel,
	beq	.L436	@,
	ldr	r1, [r4, #8]	@ D.53439, <variable>.VidStd
	cmp	r1, #16	@ D.53439,
	cmpne	r1, #0	@, D.53439,
	bne	.L433	@,
	sub	r0, r0, #13	@ D.53602, eCapLevel,
	cmp	r0, #19	@ D.53602,
	bhi	.L433	@,
	movw	r2, #:lower16:.LANCHOR1	@ tmp160,
	movt	r2, #:upper16:.LANCHOR1	@ tmp160,
	add	r0, r2, r0, asl #2	@, tmp163, tmp160, D.53602,
	ldr	r0, [r0, #20]	@ MaxSegSize, CSWTCH.724
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L436:
	mov	r0, r5	@, ChanID
	bl	VCTRL_GetChanWidth	@
	mov	r4, r0	@ ChanWidth,
	mov	r0, r5	@, ChanID
	bl	VCTRL_GetChanHeight	@
	cmn	r0, #1	@ ChanHeight,
	cmnne	r4, #1	@, ChanWidth,
	beq	.L437	@,
	mul	r4, r4, r0	@ tmp151, ChanWidth, ChanHeight
	movw	r3, #:lower16:2088960	@ tmp152,
	movt	r3, #:upper16:2088960	@ tmp152,
	cmp	r4, r3	@ tmp151, tmp152
	movgt	r0, #20971520	@ MaxSegSize,
	ldmgtfd	sp, {r4, r5, fp, sp, pc}	@
.L433:
	mov	r0, #3145728	@ MaxSegSize,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L435:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC65	@,
	movt	r1, #:upper16:.LC65	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ MaxSegSize,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L437:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC66	@,
	movt	r1, #:upper16:.LC66	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ MaxSegSize,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	SetMaxSegSize, .-SetMaxSegSize
	.align	2
	.global	PrintScdSegState
	.type	PrintScdSegState, %function
PrintScdSegState:
	.fnstart
.LFB1622:
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
	mov	r8, r0	@ SmID, SmID
	mov	r0, #26	@,
	mov	r7, r1	@ PrintDetail, PrintDetail
	bl	IsDprintTypeEnable	@
	cmp	r0, #0	@,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	add	r2, r8, r8, asl #1	@, tmp213, SmID, SmID,
	movw	r0, #:lower16:.LANCHOR0	@ tmp209,
	movt	r0, #:upper16:.LANCHOR0	@ tmp209,
	movw	r6, #:lower16:190696	@ tmp219,
	add	r1, r0, r2, asl #4	@, tmp215, tmp209, tmp213,
	movt	r6, #:upper16:190696	@ tmp219,
	mov	r2, r8	@, SmID
	mov	r0, #26	@,
	ldr	r4, [r1, #40]	@ D.53354, <variable>.pSmInstArray
	movw	r5, #:lower16:190700	@ tmp222,
	movw	r1, #:lower16:.LC67	@,
	movt	r5, #:upper16:190700	@ tmp222,
	movt	r1, #:upper16:.LC67	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, r6]	@, <variable>.StreamSegArray.Head
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC68	@,
	movt	r1, #:upper16:.LC68	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, r5]	@, <variable>.StreamSegArray.Tail
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC69	@,
	movt	r1, #:upper16:.LC69	@,
	bl	dprint_vfmw	@
	movw	ip, #:lower16:190708	@ tmp225,
	movt	ip, #:upper16:190708	@ tmp225,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC70	@,
	movt	r1, #:upper16:.LC70	@,
	ldr	r2, [r4, ip]	@, <variable>.StreamSegArray.Current
	bl	dprint_vfmw	@
	movw	r3, #:lower16:190712	@ tmp228,
	movt	r3, #:upper16:190712	@ tmp228,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC71	@,
	movt	r1, #:upper16:.LC71	@,
	ldr	r2, [r4, r3]	@, <variable>.StreamSegArray.SegBufPhyAddr
	bl	dprint_vfmw	@
	movw	ip, #:lower16:98528	@ tmp231,
	movt	ip, #:upper16:98528	@ tmp231,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC72	@,
	movt	r1, #:upper16:.LC72	@,
	ldr	r2, [r4, ip]	@, <variable>.StreamSegArray.pSegBufVirAddr
	bl	dprint_vfmw	@
	movw	r3, #:lower16:190716	@ tmp234,
	movt	r3, #:upper16:190716	@ tmp234,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC73	@,
	movt	r1, #:upper16:.LC73	@,
	ldr	r2, [r4, r3]	@, <variable>.StreamSegArray.SegBufSize
	bl	dprint_vfmw	@
	movw	ip, #:lower16:190720	@ tmp237,
	movt	ip, #:upper16:190720	@ tmp237,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC74	@,
	movt	r1, #:upper16:.LC74	@,
	ldr	r2, [r4, ip]	@, <variable>.StreamSegArray.SegBufReadAddr
	bl	dprint_vfmw	@
	movw	r3, #:lower16:190724	@ tmp240,
	movt	r3, #:upper16:190724	@ tmp240,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC75	@,
	movt	r1, #:upper16:.LC75	@,
	ldr	r2, [r4, r3]	@, <variable>.StreamSegArray.SegBufWriteAddr
	bl	dprint_vfmw	@
	cmp	r7, #1	@ PrintDetail,
	beq	.L451	@,
.L440:
	mov	r2, r8	@, SmID
	movw	r1, #:lower16:.LC77	@,
	mov	r0, #26	@,
	movt	r1, #:upper16:.LC77	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L451:
	add	r3, r4, #98304	@ tmp242, D.53354,
	add	lr, r3, #224	@ tmp242, tmp242,
	cmp	lr, #0	@ tmp242,
	beq	.L441	@,
	ldr	r3, [r4, r6]	@ D.53614, <variable>.StreamSegArray.Head
	ldr	r7, [r4, r5]	@ <variable>.StreamSegArray.Tail, <variable>.StreamSegArray.Tail
	subs	r7, r7, r3	@ SegNum, <variable>.StreamSegArray.Tail, D.53614
	addmi	r7, r7, #1152	@ SegNum, SegNum,
	cmp	r7, #0	@ SegNum,
	ble	.L440	@,
	add	lr, r3, r3, asl #2	@, tmp260, D.53614, D.53614,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC78	@,
	movt	r1, #:upper16:.LC78	@,
	mov	r2, lr, asl #4	@ tmp262, tmp260,
	mov	r6, #1	@ i,
	add	ip, r2, #98304	@ tmp263, tmp262,
	sub	sl, r7, #1	@ tmp273, SegNum,
	add	r5, ip, #248	@ tmp263, tmp263,
	and	sl, sl, #1	@ tmp275, tmp273,
	add	r5, r4, r5	@ ivtmp.2037, D.53354, tmp263
	add	r4, r5, #80	@ ivtmp.2037, ivtmp.2037,
	ldr	r2, [r5, #-8]	@, <variable>.PhyAddr
	bl	dprint_vfmw	@
	ldr	r2, [r5, #-16]	@, <variable>.VirAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC79	@,
	movt	r1, #:upper16:.LC79	@,
	bl	dprint_vfmw	@
	ldr	r2, [r5, #-4]	@, <variable>.LenInByte
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC80	@,
	movt	r1, #:upper16:.LC80	@,
	bl	dprint_vfmw	@
	ldr	r2, [r5, #0]	@, <variable>.StreamID
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC81	@,
	movt	r1, #:upper16:.LC81	@,
	bl	dprint_vfmw	@
	ldrsb	r2, [r5, #-12]	@, <variable>.SegState
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC82	@,
	movt	r1, #:upper16:.LC82	@,
	bl	dprint_vfmw	@
	ldrb	r2, [r5, #-11]	@ zero_extendqisi2	@, <variable>.IsLastSeg
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC83	@,
	movt	r1, #:upper16:.LC83	@,
	bl	dprint_vfmw	@
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC84	@,
	ldrd	r2, [r5, #8]	@, ivtmp.2037,
	movt	r1, #:upper16:.LC84	@,
	bl	dprint_vfmw	@
	cmp	r6, r7	@ i, SegNum
	bge	.L440	@,
	cmp	sl, #0	@ tmp275,
	beq	.L443	@,
	ldr	r2, [r4, #-8]	@, <variable>.PhyAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC78	@,
	movt	r1, #:upper16:.LC78	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #-16]	@, <variable>.VirAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC79	@,
	movt	r1, #:upper16:.LC79	@,
	mov	r6, #2	@ i,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #-4]	@, <variable>.LenInByte
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC80	@,
	movt	r1, #:upper16:.LC80	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #0]	@, <variable>.StreamID
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC81	@,
	movt	r1, #:upper16:.LC81	@,
	bl	dprint_vfmw	@
	ldrsb	r2, [r4, #-12]	@, <variable>.SegState
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC82	@,
	movt	r1, #:upper16:.LC82	@,
	bl	dprint_vfmw	@
	ldrb	r2, [r4, #-11]	@ zero_extendqisi2	@, <variable>.IsLastSeg
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC83	@,
	movt	r1, #:upper16:.LC83	@,
	bl	dprint_vfmw	@
	ldrd	r2, [r4, #8]	@, ivtmp.2037,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC84	@,
	movt	r1, #:upper16:.LC84	@,
	add	r4, r5, #160	@ ivtmp.2037, ivtmp.2037,
	bl	dprint_vfmw	@
	cmp	r6, r7	@ i, SegNum
	bge	.L440	@,
.L443:
	ldr	r2, [r4, #-8]	@, <variable>.PhyAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC78	@,
	movt	r1, #:upper16:.LC78	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #-16]	@, <variable>.VirAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC79	@,
	movt	r1, #:upper16:.LC79	@,
	add	r5, r4, #80	@ tmp277, ivtmp.2037,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #-4]	@, <variable>.LenInByte
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC80	@,
	movt	r1, #:upper16:.LC80	@,
	add	r6, r6, #1	@ tmp276, i,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #0]	@, <variable>.StreamID
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC81	@,
	movt	r1, #:upper16:.LC81	@,
	add	r6, r6, #1	@ i, tmp276,
	bl	dprint_vfmw	@
	ldrsb	r2, [r4, #-12]	@, <variable>.SegState
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC82	@,
	movt	r1, #:upper16:.LC82	@,
	bl	dprint_vfmw	@
	ldrb	r2, [r4, #-11]	@ zero_extendqisi2	@, <variable>.IsLastSeg
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC83	@,
	movt	r1, #:upper16:.LC83	@,
	bl	dprint_vfmw	@
	ldrd	r2, [r4, #8]	@, ivtmp.2037,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC84	@,
	movt	r1, #:upper16:.LC84	@,
	bl	dprint_vfmw	@
	ldr	r2, [r5, #-8]	@, <variable>.PhyAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC78	@,
	movt	r1, #:upper16:.LC78	@,
	bl	dprint_vfmw	@
	ldr	r2, [r5, #-16]	@, <variable>.VirAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC79	@,
	movt	r1, #:upper16:.LC79	@,
	bl	dprint_vfmw	@
	ldr	r2, [r5, #-4]	@, <variable>.LenInByte
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC80	@,
	movt	r1, #:upper16:.LC80	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #80]	@, <variable>.StreamID
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC81	@,
	movt	r1, #:upper16:.LC81	@,
	add	r4, r4, #160	@ ivtmp.2037, ivtmp.2037,
	bl	dprint_vfmw	@
	ldrsb	r2, [r5, #-12]	@, <variable>.SegState
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC82	@,
	movt	r1, #:upper16:.LC82	@,
	bl	dprint_vfmw	@
	ldrb	r2, [r5, #-11]	@ zero_extendqisi2	@, <variable>.IsLastSeg
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC83	@,
	movt	r1, #:upper16:.LC83	@,
	bl	dprint_vfmw	@
	ldrd	r2, [r5, #8]	@, tmp277,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC84	@,
	movt	r1, #:upper16:.LC84	@,
	bl	dprint_vfmw	@
	cmp	r6, r7	@ i, SegNum
	blt	.L443	@,
	b	.L440	@
.L441:
	movw	r1, #:lower16:.LC76	@,
	ldr	r2, .L452	@,
	movt	r1, #:upper16:.LC76	@,
	movw	r3, #6198	@,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	b	.L440	@
.L453:
	.align	2
.L452:
	.word	.LANCHOR1+100
	.fnend
	.size	PrintScdSegState, .-PrintScdSegState
	.align	2
	.global	PrintScdRawState
	.type	PrintScdRawState, %function
PrintScdRawState:
	.fnstart
.LFB1620:
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
	mov	r8, r0	@ SmID, SmID
	mov	r0, #26	@,
	mov	r7, r1	@ PrintDetail, PrintDetail
	bl	IsDprintTypeEnable	@
	cmp	r0, #0	@,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	add	r2, r8, r8, asl #1	@, tmp153, SmID, SmID,
	movw	r0, #:lower16:.LANCHOR0	@ tmp149,
	movt	r0, #:upper16:.LANCHOR0	@ tmp149,
	movw	r6, #:lower16:98504	@ tmp159,
	add	r1, r0, r2, asl #4	@, tmp155, tmp149, tmp153,
	movt	r6, #:upper16:98504	@ tmp159,
	mov	r2, r8	@, SmID
	mov	r0, #26	@,
	ldr	r4, [r1, #40]	@ D.53239, <variable>.pSmInstArray
	movw	r5, #:lower16:98508	@ tmp162,
	movw	r1, #:lower16:.LC85	@,
	movt	r5, #:upper16:98508	@ tmp162,
	movt	r1, #:upper16:.LC85	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, r6]	@, <variable>.RawPacketArray.Head
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC86	@,
	movt	r1, #:upper16:.LC86	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, r5]	@, <variable>.RawPacketArray.Tail
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC87	@,
	movt	r1, #:upper16:.LC87	@,
	bl	dprint_vfmw	@
	movw	r3, #:lower16:98512	@ tmp165,
	movt	r3, #:upper16:98512	@ tmp165,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC88	@,
	movt	r1, #:upper16:.LC88	@,
	ldr	r2, [r4, r3]	@, <variable>.RawPacketArray.History
	bl	dprint_vfmw	@
	movw	ip, #:lower16:98516	@ tmp168,
	movt	ip, #:upper16:98516	@ tmp168,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC89	@,
	movt	r1, #:upper16:.LC89	@,
	ldr	r2, [r4, ip]	@, <variable>.RawPacketArray.FirstPacketOffset
	bl	dprint_vfmw	@
	movw	r3, #:lower16:98520	@ tmp171,
	movt	r3, #:upper16:98520	@ tmp171,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC90	@,
	movt	r1, #:upper16:.LC90	@,
	ldr	r2, [r4, r3]	@, <variable>.RawPacketArray.CurShowIndex
	bl	dprint_vfmw	@
	cmp	r7, #1	@ PrintDetail,
	beq	.L467	@,
.L456:
	mov	r2, r8	@, SmID
	movw	r1, #:lower16:.LC92	@,
	mov	r0, #26	@,
	movt	r1, #:upper16:.LC92	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L467:
	cmn	r4, #200	@ D.53239,
	beq	.L457	@,
	ldr	r3, [r4, r6]	@ D.53623, <variable>.RawPacketArray.Head
	ldr	r7, [r4, r5]	@ <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Tail
	subs	r7, r7, r3	@ RawNum, <variable>.RawPacketArray.Tail, D.53623
	addmi	r7, r7, #1024	@ RawNum, RawNum,
	cmp	r7, #0	@ RawNum,
	ble	.L456	@,
	add	r5, r3, r3, asl #1	@, tmp187, D.53623, D.53623,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC93	@,
	movt	r1, #:upper16:.LC93	@,
	add	r4, r4, r5, asl #5	@, tmp189, D.53239, tmp187,
	mov	r6, #1	@ i,
	add	r5, r4, #208	@ ivtmp.2080, tmp189,
	sub	sl, r7, #1	@ tmp195, RawNum,
	and	sl, sl, #1	@ tmp197, tmp195,
	add	r4, r5, #96	@ ivtmp.2080, ivtmp.2080,
	ldr	r2, [r5, #-8]	@, <variable>.PhyAddr
	bl	dprint_vfmw	@
	ldr	r2, [r5, #-4]	@, <variable>.VirAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC94	@,
	movt	r1, #:upper16:.LC94	@,
	bl	dprint_vfmw	@
	ldr	r2, [r5, #0]	@, <variable>.Length
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC95	@,
	movt	r1, #:upper16:.LC95	@,
	bl	dprint_vfmw	@
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC96	@,
	ldrd	r2, [r5, #8]	@, ivtmp.2080,
	movt	r1, #:upper16:.LC96	@,
	bl	dprint_vfmw	@
	cmp	r6, r7	@ i, RawNum
	bge	.L456	@,
	cmp	sl, #0	@ tmp197,
	beq	.L459	@,
	ldr	r2, [r4, #-8]	@, <variable>.PhyAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC93	@,
	movt	r1, #:upper16:.LC93	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #-4]	@, <variable>.VirAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC94	@,
	movt	r1, #:upper16:.LC94	@,
	mov	r6, #2	@ i,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #0]	@, <variable>.Length
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC95	@,
	movt	r1, #:upper16:.LC95	@,
	bl	dprint_vfmw	@
	ldrd	r2, [r4, #8]	@, ivtmp.2080,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC96	@,
	movt	r1, #:upper16:.LC96	@,
	add	r4, r5, #192	@ ivtmp.2080, ivtmp.2080,
	bl	dprint_vfmw	@
	cmp	r6, r7	@ i, RawNum
	bge	.L456	@,
.L459:
	ldr	r2, [r4, #-8]	@, <variable>.PhyAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC93	@,
	movt	r1, #:upper16:.LC93	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #-4]	@, <variable>.VirAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC94	@,
	movt	r1, #:upper16:.LC94	@,
	add	r5, r4, #96	@ tmp199, ivtmp.2080,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #0]	@, <variable>.Length
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC95	@,
	movt	r1, #:upper16:.LC95	@,
	add	r6, r6, #1	@ tmp198, i,
	bl	dprint_vfmw	@
	ldrd	r2, [r4, #8]	@, ivtmp.2080,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC96	@,
	movt	r1, #:upper16:.LC96	@,
	add	r6, r6, #1	@ i, tmp198,
	bl	dprint_vfmw	@
	ldr	r2, [r5, #-8]	@, <variable>.PhyAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC93	@,
	movt	r1, #:upper16:.LC93	@,
	bl	dprint_vfmw	@
	ldr	r2, [r5, #-4]	@, <variable>.VirAddr
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC94	@,
	movt	r1, #:upper16:.LC94	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #96]	@, <variable>.Length
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC95	@,
	movt	r1, #:upper16:.LC95	@,
	add	r4, r4, #192	@ ivtmp.2080, ivtmp.2080,
	bl	dprint_vfmw	@
	ldrd	r2, [r5, #8]	@, tmp199,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC96	@,
	movt	r1, #:upper16:.LC96	@,
	bl	dprint_vfmw	@
	cmp	r6, r7	@ i, RawNum
	blt	.L459	@,
	b	.L456	@
.L457:
	movw	r1, #:lower16:.LC91	@,
	ldr	r2, .L468	@,
	movt	r1, #:upper16:.LC91	@,
	movw	r3, #6060	@,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	b	.L456	@
.L469:
	.align	2
.L468:
	.word	.LANCHOR1+120
	.fnend
	.size	PrintScdRawState, .-PrintScdRawState
	.align	2
	.global	PrintScdVtrlReg
	.type	PrintScdVtrlReg, %function
PrintScdVtrlReg:
	.fnstart
.LFB1616:
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
	mov	r2, r0	@ ScdId, ScdId
	movw	r0, #:lower16:-121387004	@ tmp142,
	movt	r0, #:upper16:-121387004	@,
	str	r2, [fp, #-48]	@,
	bl	MEM_ReadPhyWord	@
	mov	r8, r0	@ D.53152,
	movw	r0, #:lower16:-121387000	@ tmp143,
	movt	r0, #:upper16:-121387000	@,
	bl	MEM_ReadPhyWord	@
	mov	r7, r0	@ D.53153,
	movw	r0, #:lower16:-121386996	@ tmp144,
	movt	r0, #:upper16:-121386996	@,
	bl	MEM_ReadPhyWord	@
	mov	r6, r0	@ D.53154,
	movw	r0, #:lower16:-121386992	@ tmp145,
	movt	r0, #:upper16:-121386992	@,
	bl	MEM_ReadPhyWord	@
	mov	r5, r0	@ D.53155,
	movw	r0, #:lower16:-121386988	@ tmp146,
	movt	r0, #:upper16:-121386988	@,
	bl	MEM_ReadPhyWord	@
	mov	r4, r0	@ D.53156,
	movw	r0, #:lower16:-121386984	@ tmp147,
	movt	r0, #:upper16:-121386984	@,
	bl	MEM_ReadPhyWord	@
	mov	sl, r0	@ D.53157,
	movw	r0, #:lower16:-121386976	@ tmp148,
	movt	r0, #:upper16:-121386976	@,
	bl	MEM_ReadPhyWord	@
	mov	r9, r0	@ D.53158,
	movw	r0, #:lower16:-121387008	@ tmp149,
	movt	r0, #:upper16:-121387008	@,
	bl	MEM_ReadPhyWord	@
	ldr	r2, [fp, #-48]	@,
	movw	r1, #:lower16:.LC97	@,
	movt	r1, #:upper16:.LC97	@,
	mov	ip, r0	@ D.53159,
	mov	r0, #24	@,
	str	ip, [fp, #-48]	@,
	bl	dprint_vfmw	@
	mov	r2, r8	@, D.53152
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC98	@,
	movt	r1, #:upper16:.LC98	@,
	bl	dprint_vfmw	@
	mov	r2, r7	@, D.53153
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC99	@,
	movt	r1, #:upper16:.LC99	@,
	bl	dprint_vfmw	@
	mov	r2, r6	@, D.53154
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC100	@,
	movt	r1, #:upper16:.LC100	@,
	bl	dprint_vfmw	@
	mov	r2, r5	@, D.53155
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC101	@,
	movt	r1, #:upper16:.LC101	@,
	bl	dprint_vfmw	@
	mov	r2, r4	@, D.53156
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC102	@,
	movt	r1, #:upper16:.LC102	@,
	bl	dprint_vfmw	@
	mov	r2, sl	@, D.53157
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC103	@,
	movt	r1, #:upper16:.LC103	@,
	bl	dprint_vfmw	@
	mov	r2, r9	@, D.53158
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC104	@,
	movt	r1, #:upper16:.LC104	@,
	bl	dprint_vfmw	@
	ldr	r3, [fp, #-48]	@,
	movw	r1, #:lower16:.LC105	@,
	mov	r0, #24	@,
	movt	r1, #:upper16:.LC105	@,
	sxtb	r2, r3	@, D.53159
	bl	dprint_vfmw	@
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
	.fnend
	.size	PrintScdVtrlReg, .-PrintScdVtrlReg
	.align	2
	.global	ReadScdStateReg
	.type	ReadScdStateReg, %function
ReadScdStateReg:
	.fnstart
.LFB1587:
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
	mov	r4, r0	@ pSmStateReg, pSmStateReg
	movw	r0, #:lower16:-121386944	@ tmp141,
	movt	r0, #:upper16:-121386944	@,
	mov	r6, r1	@ ScdId, ScdId
	bl	MEM_ReadPhyWord	@
	movw	r5, #:lower16:-121386932	@ tmp154,
	movt	r5, #:upper16:-121386932	@ tmp154,
	and	ip, r0, #1	@ tmp142,,
	movw	r0, #:lower16:-121386940	@ tmp143,
	str	ip, [r4, #0]	@ tmp142, <variable>.Scdover
	movt	r0, #:upper16:-121386940	@,
	bl	MEM_ReadPhyWord	@
	and	r2, r0, #1	@ tmp144,,
	mov	r0, r5	@, tmp154
	str	r2, [r4, #4]	@ tmp144, <variable>.ScdInt
	bl	MEM_ReadPhyWord	@
	mov	r0, r0, lsr #22	@ tmp146,,
	str	r0, [r4, #8]	@ tmp146, <variable>.ShortScdNum
	mov	r0, r5	@, tmp154
	bl	MEM_ReadPhyWord	@
	bic	r1, r0, #-16777216	@ tmp149,,
	movw	r0, #:lower16:-121386928	@ tmp150,
	bic	r3, r1, #12582912	@ tmp149, tmp149,
	movt	r0, #:upper16:-121386928	@,
	str	r3, [r4, #12]	@ tmp149, <variable>.ScdNum
	bl	MEM_ReadPhyWord	@
	str	r0, [r4, #16]	@, <variable>.ScdRollAddr
	movw	r0, #:lower16:-121386924	@ tmp151,
	movt	r0, #:upper16:-121386924	@,
	bl	MEM_ReadPhyWord	@
	mov	r1, r6	@, ScdId
	str	r0, [r4, #20]	@, <variable>.SrcEaten
	mov	r0, r4	@, pSmStateReg
	bl	PrintScdStateReg	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	ReadScdStateReg, .-ReadScdStateReg
	.align	2
	.global	GetNextVop
	.type	GetNextVop, %function
GetNextVop:
	.fnstart
.LFB1594:
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
	mov	r6, r0	@ pScdInstance, pScdInstance
	movw	r0, #:lower16:-121386976	@,
	movt	r0, #:upper16:-121386976	@,
	mov	r4, r2	@ pStreamSegArray, pStreamSegArray
	mov	r7, r3	@ Seg_num, Seg_num
	mov	r8, r1	@ pUsedSeg, pUsedSeg
	mov	r1, #0	@ tmp157,
	str	r1, [fp, #-48]	@ tmp157, SegNum
	bl	MEM_ReadPhyWord	@
	ldr	r1, [fp, #4]	@, ScdId
	sub	r0, fp, #72	@,,
	bl	ReadScdStateReg	@
	ldr	r3, [fp, #-56]	@ SmStateReg.ScdRollAddr, SmStateReg.ScdRollAddr
	cmp	r3, #0	@ SmStateReg.ScdRollAddr,
	mvneq	r5, #6	@, Ret,
	movne	r5, #0	@, Ret,
	cmp	r4, #0	@ pStreamSegArray,
	beq	.L477	@,
	movw	lr, #:lower16:92172	@ tmp161,
	movw	ip, #:lower16:92168	@ tmp162,
	movt	lr, #:upper16:92172	@ tmp161,
	movt	ip, #:upper16:92168	@ tmp162,
	ldr	r2, [r4, lr]	@ <variable>.Tail, <variable>.Tail
	ldr	r0, [r4, ip]	@ <variable>.Head, <variable>.Head
	subs	r3, r2, r0	@ prephitmp.2185, <variable>.Tail, <variable>.Head
	addmi	r3, r3, #1152	@ prephitmp.2185, prephitmp.2185,
.L478:
	cmp	r5, #0	@ Ret,
	rsb	r3, r3, #1152	@, prephitmp.2185,
	str	r3, [fp, #-88]	@, %sfp
	str	r3, [fp, #-48]	@, SegNum
	bne	.L479	@,
	subs	r3, r7, #1	@ i, Seg_num,
	movmi	r5, r7	@ Ret, Seg_num
	bmi	.L479	@,
	movw	r1, #:lower16:204748	@ tmp170,
	movt	r1, #:upper16:204748	@ tmp170,
	movw	r2, #:lower16:92184	@ tmp171,
	tst	r3, #1	@ i,
	ldr	r0, [r6, r1]	@ pretmp.2176, <variable>.UpMsgStepNum
	movt	r2, #:upper16:92184	@ tmp171,
	ldr	r1, [r6, #20]	@ pretmp.2183, <variable>.SegFilter.ModeFlag
	movw	sl, #:lower16:-1241448448	@,
	str	r5, [fp, #-80]	@ Ret, %sfp
	movt	sl, #:upper16:-1241448448	@,
	mov	r7, r0, asl #2	@ pretmp.2204, pretmp.2176,
	ldr	r6, [r4, r2]	@ pretmp.2182, <variable>.SegBufPhyAddr
	movw	r5, #:lower16:-33488896	@ tmp191,
	str	sl, [fp, #-84]	@, %sfp
	movt	r5, #:upper16:-33488896	@ tmp191,
	ldr	r2, [r4, #0]	@ pretmp.2178, <variable>.pSegBufVirAddr
	mla	r0, r7, r3, r8	@ ivtmp.2200, pretmp.2204, i, pUsedSeg
	rsb	ip, r7, #0	@ D.55298, pretmp.2204
	bne	.L499	@,
.L487:
	ldr	r7, [r0, #0]	@ tmp174,* ivtmp.2200
	cmp	r1, #1	@ pretmp.2183,
	rsb	r8, r6, r7	@ tmp173, pretmp.2182, tmp174
	add	r4, r2, r8	@ VirAddr, pretmp.2178, tmp173
	ldrb	r7, [r2, r8]	@ zero_extendqisi2	@ tmp180,
	ldrb	lr, [r4, #2]	@ zero_extendqisi2	@ tmp177,
	ldrb	r8, [r4, #1]	@ zero_extendqisi2	@ tmp175,
	ldrb	r4, [r4, #3]	@ zero_extendqisi2	@ tmp182,
	mov	sl, lr, asl #16	@ tmp178, tmp177,
	add	lr, sl, r8, asl #8	@, tmp179, tmp178, tmp175,
	add	sl, lr, r7	@ tmp181, tmp179, tmp180
	add	r4, sl, r4, asl #24	@, start_code, tmp181, tmp182,
	beq	.L510	@,
	cmp	r1, #2	@ pretmp.2183,
	beq	.L511	@,
.L483:
	mov	r7, #0	@ flag,
.L484:
	cmp	r4, r5	@ start_code, tmp191
	beq	.L482	@,
	cmp	r7, #1	@ flag,
	beq	.L482	@,
.L485:
	subs	r4, r3, #1	@ i.2203, i,
	add	r9, r0, ip	@ ivtmp.2200, ivtmp.2200, D.55298
	bmi	.L486	@,
	ldr	r7, [r0, ip]	@ tmp198,* D.55298
	cmp	r1, #1	@ pretmp.2183,
	mov	r3, r4	@ i, i.2203
	rsb	r8, r6, r7	@ tmp199, pretmp.2182, tmp198
	add	r0, r2, r8	@ VirAddr, pretmp.2178, tmp199
	ldrb	lr, [r2, r8]	@ zero_extendqisi2	@ tmp206,
	ldrb	sl, [r0, #2]	@ zero_extendqisi2	@ tmp203,
	ldrb	r8, [r0, #1]	@ zero_extendqisi2	@ tmp201,
	ldrb	r0, [r0, #3]	@ zero_extendqisi2	@ tmp208,
	mov	sl, sl, asl #16	@ tmp204, tmp203,
	add	sl, sl, r8, asl #8	@, tmp205, tmp204, tmp201,
	add	sl, sl, lr	@ tmp207, tmp205, tmp206
	add	r0, sl, r0, asl #24	@, start_code, tmp207, tmp208,
	beq	.L512	@,
	cmp	r1, #2	@ pretmp.2183,
	beq	.L513	@,
.L497:
	cmp	r0, r5	@ start_code, tmp191
	mov	r7, #0	@ flag,
	beq	.L496	@,
.L516:
	cmp	r7, #1	@ flag,
	beq	.L496	@,
.L495:
	add	r0, r9, ip	@ ivtmp.2200, ivtmp.2200, D.55298
	sub	r3, r4, #1	@ i, i.2203,
	b	.L487	@
.L499:
	ldr	lr, [r0, #0]	@ tmp211,* ivtmp.2200
	cmp	r1, #1	@ pretmp.2183,
	rsb	r8, r6, lr	@ tmp212, pretmp.2182, tmp211
	add	sl, r2, r8	@ VirAddr, pretmp.2178, tmp212
	ldrb	r7, [sl, #2]	@ zero_extendqisi2	@ tmp216,
	ldrb	r8, [sl, #1]	@ zero_extendqisi2	@ tmp214,
	ldrb	lr, [sl, #3]	@ zero_extendqisi2	@ tmp221,
	mov	r7, r7, asl #16	@ tmp217, tmp216,
	ldrb	r4, [sl, #0]	@ zero_extendqisi2	@ tmp219,* VirAddr
	add	sl, r7, r8, asl #8	@, tmp218, tmp217, tmp214,
	add	r7, sl, r4	@ tmp220, tmp218, tmp219
	add	sl, r7, lr, asl #24	@, start_code, tmp220, tmp221,
	beq	.L514	@,
	cmp	r1, #2	@ pretmp.2183,
	beq	.L515	@,
.L492:
	mov	r4, #0	@ flag,
.L502:
	cmp	sl, r5	@ start_code, tmp191
	beq	.L491	@,
	cmp	r4, #1	@ flag,
	beq	.L491	@,
.L490:
	subs	r4, r3, #1	@ i.2203, i,
	add	r0, r0, ip	@ ivtmp.2200, ivtmp.2200, D.55298
	movpl	r3, r4	@ i, i.2203
	bpl	.L487	@,
.L486:
	mov	r5, r3	@ Ret, i
.L479:
	mov	r0, r5	@, Ret
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L510:
	ldr	r7, [fp, #-84]	@, %sfp
	cmp	r4, r7	@ start_code,
	bne	.L483	@,
.L482:
	ldr	r4, [fp, #-80]	@, %sfp
	add	r4, r4, #1	@,,
	str	r4, [fp, #-80]	@, %sfp
	cmp	r4, #0	@,
	ble	.L485	@,
	ldr	r7, [fp, #-88]	@, %sfp
	cmp	r7, r3	@, i
	bcc	.L485	@,
	mov	r5, r3	@ Ret, i
	b	.L479	@
.L511:
	ubfx	r7, r4, #16, #8	@ tmp186, start_code,,
	sub	lr, r7, #128	@ tmp187, tmp186,
	cmp	lr, #3	@ tmp187,
	movhi	r7, #0	@, flag
	movls	r7, #1	@, flag
	b	.L484	@
.L513:
	ubfx	lr, r0, #16, #8	@ tmp234, start_code,,
	sub	r7, lr, #128	@ tmp235, tmp234,
	cmp	r7, #3	@ tmp235,
	movhi	r7, #0	@, flag
	movls	r7, #1	@, flag
	cmp	r0, r5	@ start_code, tmp191
	bne	.L516	@,
.L496:
	ldr	r0, [fp, #-80]	@, %sfp
	add	r7, r0, #1	@,,
	str	r7, [fp, #-80]	@, %sfp
	cmp	r7, #0	@,
	ble	.L495	@,
	ldr	lr, [fp, #-88]	@, %sfp
	cmp	lr, r4	@, i.2203
	bcc	.L495	@,
	mov	r5, r3	@ Ret, i
	b	.L479	@
.L512:
	ldr	r7, [fp, #-84]	@, %sfp
	cmp	r0, r7	@ start_code,
	bne	.L497	@,
	b	.L496	@
.L514:
	ldr	r4, [fp, #-84]	@, %sfp
	cmp	sl, r4	@ start_code,
	bne	.L492	@,
.L491:
	ldr	r4, [fp, #-88]	@, %sfp
	mov	r7, #1	@,
	str	r7, [fp, #-80]	@, %sfp
	cmp	r4, r3	@, i
	bcc	.L490	@,
	mov	r5, r3	@ Ret, i
	b	.L479	@
.L515:
	ubfx	lr, sl, #16, #8	@ tmp227, start_code,,
	sub	r4, lr, #128	@ tmp228, tmp227,
	cmp	r4, #3	@ tmp228,
	movhi	r4, #0	@, flag
	movls	r4, #1	@, flag
	b	.L502	@
.L477:
	movw	r3, #3560	@,
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC106	@,
	ldr	r2, .L517	@,
	movt	r1, #:upper16:.LC106	@,
	bl	dprint_vfmw	@
	ldr	r3, [fp, #-48]	@ prephitmp.2185, SegNum
	b	.L478	@
.L518:
	.align	2
.L517:
	.word	.LANCHOR1+140
	.fnend
	.size	GetNextVop, .-GetNextVop
	.align	2
	.global	WaitSCDFinish
	.type	WaitSCDFinish, %function
WaitSCDFinish:
	.fnstart
.LFB1615:
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
	add	r0, r0, r0, asl #1	@, tmp145, ScdId, ScdId,
	movw	r2, #:lower16:.LANCHOR0	@ tmp141,
	movt	r2, #:upper16:.LANCHOR0	@ tmp141,
	add	r1, r2, r0, asl #5	@, tmp147, tmp141, tmp145,
	ldr	r3, [r1, #856]	@ <variable>.SCDState, <variable>.SCDState
	cmp	r3, #1	@ <variable>.SCDState,
	beq	.L536	@,
.L520:
	mov	r0, #0	@ D.53138,
.L524:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L536:
	bl	OSAL_GetTimeInMs	@
	movw	r6, #:lower16:500000	@ tmp158,
	mov	r5, #0	@ i,
	movt	r6, #:upper16:500000	@ tmp158,
	mov	r4, r0	@ t_start,
	b	.L525	@
.L538:
	bl	OSAL_GetTimeInMs	@
	cmp	r4, r0	@ t_start, t_now
	rsbhi	ip, r0, r4	@ tmp152, t_now, t_start
	rsbls	ip, r4, r0	@ t_wait, t_start, t_now
	mvnhi	ip, ip	@ t_wait, tmp152
	cmp	ip, #1000	@ t_wait,
	bhi	.L534	@,
	movw	r0, #:lower16:-121386944	@,
	movt	r0, #:upper16:-121386944	@,
	bl	MEM_ReadPhyWord	@
	add	r5, r5, #1	@ tmp159, i,
	tst	r0, #1	@,
	bne	.L520	@,
	bl	OSAL_GetTimeInMs	@
	cmp	r4, r0	@ t_start, t_now
	rsbhi	ip, r0, r4	@ tmp164, t_now, t_start
	rsbls	ip, r4, r0	@ t_wait, t_start, t_now
	mvnhi	ip, ip	@ t_wait, tmp164
	cmp	ip, #1000	@ t_wait,
	bhi	.L534	@,
	add	r5, r5, #1	@ i, tmp159,
	cmp	r5, r6	@ i, tmp158
	beq	.L537	@,
.L525:
	movw	r0, #:lower16:-121386944	@,
	movt	r0, #:upper16:-121386944	@,
	bl	MEM_ReadPhyWord	@
	tst	r0, #1	@,
	beq	.L538	@,
	b	.L520	@
.L534:
	mov	r3, r0	@, t_now
	mov	r2, r4	@, t_start
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC107	@,
	movt	r1, #:upper16:.LC107	@,
	str	ip, [sp, #0]	@ t_wait,
	bl	dprint_vfmw	@
	mvn	r0, #6	@ D.53138,
	b	.L524	@
.L537:
	mvn	r0, #6	@ D.53138,
	b	.L524	@
	.fnend
	.size	WaitSCDFinish, .-WaitSCDFinish
	.align	2
	.global	CalcInstBlockTime
	.type	CalcInstBlockTime, %function
CalcInstBlockTime:
	.fnstart
.LFB1581:
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
	add	r0, r0, r0, asl #1	@, tmp145, SmID, SmID,
	movw	r2, #:lower16:.LANCHOR0	@ tmp141,
	movt	r2, #:upper16:.LANCHOR0	@ tmp141,
	add	r3, r2, r0, asl #4	@, tmp147, tmp141, tmp145,
	mov	r5, r1	@ FirstCalc, FirstCalc
	ldr	r4, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r4, #0	@ pSmInstArray,
	moveq	r0, r4	@ prephitmp.2249, pSmInstArray
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	bl	OSAL_GetTimeInMs	@
	cmp	r5, #0	@ FirstCalc,
	mov	r3, r0	@ CurTime,
	beq	.L542	@,
	movw	r1, #:lower16:204700	@ tmp149,
	movw	ip, #:lower16:204704	@ tmp151,
	movt	r1, #:upper16:204700	@ tmp149,
	movt	ip, #:upper16:204704	@ tmp151,
	mov	r0, #0	@ tmp150,
	str	r0, [r4, r1]	@ tmp150, <variable>.BlockTimeInMs
	str	r3, [r4, ip]	@ CurTime,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L542:
	movw	r2, #:lower16:204704	@ tmp152,
	movt	r2, #:upper16:204704	@ tmp152,
	ldr	r1, [r4, r2]	@ D.51147, <variable>.LastBlockTime
	cmp	r0, r1	@ CurTime, D.51147
	bls	.L543	@,
	rsb	r3, r1, r0	@ D.51150, D.51147, CurTime
	movw	lr, #:lower16:204700	@ tmp153,
	movt	lr, #:upper16:204700	@ tmp153,
	mov	r0, r3	@ prephitmp.2249, D.51150
	str	r3, [r4, lr]	@ D.51150,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L543:
	movw	ip, #:lower16:204700	@ tmp154,
	movt	ip, #:upper16:204700	@ tmp154,
	mov	r0, r5	@ prephitmp.2249, FirstCalc
	str	r3, [r4, r2]	@ CurTime, <variable>.LastBlockTime
	str	r5, [r4, ip]	@ FirstCalc, <variable>.BlockTimeInMs
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	CalcInstBlockTime, .-CalcInstBlockTime
	.align	2
	.global	WriteScdVtrlReg
	.type	WriteScdVtrlReg, %function
WriteScdVtrlReg:
	.fnstart
.LFB1584:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp220,
	movt	r4, #:upper16:.LANCHOR0	@ tmp220,
	mov	r5, r0	@ pSmCtrlReg, pSmCtrlReg
	mov	r6, r1	@ ScdId, ScdId
	ldr	r1, [r0, #4]	@, <variable>.DownMsgPhyAddr
	ldr	r3, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	add	lr, r3, #2048	@, s_RegPhyBaseAddr,
	add	r0, lr, #4	@,,
	bl	MEM_WritePhyWord	@
	ldr	r2, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldr	r1, [r5, #12]	@, <variable>.UpMsgPhyAddr
	add	ip, r2, #2048	@, s_RegPhyBaseAddr,
	add	r0, ip, #8	@,,
	bl	MEM_WritePhyWord	@
	ldr	r0, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldr	r1, [r5, #20]	@, <variable>.UpLen
	add	r3, r0, #2048	@, s_RegPhyBaseAddr,
	add	r0, r3, #12	@,,
	bl	MEM_WritePhyWord	@
	ldr	r2, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldr	r1, [r5, #24]	@, <variable>.BufferFirst
	add	r0, r2, #2064	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	ldr	ip, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldr	r1, [r5, #28]	@, <variable>.BufferLast
	add	r0, ip, #2064	@, s_RegPhyBaseAddr,
	add	r0, r0, #4	@,,
	bl	MEM_WritePhyWord	@
	ldr	r3, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldr	r1, [r5, #32]	@, <variable>.BufferIni
	add	r2, r3, #2064	@, s_RegPhyBaseAddr,
	add	r0, r2, #8	@,,
	bl	MEM_WritePhyWord	@
	ldrsb	r0, [r5, #1]	@ <variable>.SliceCheckFlag, <variable>.SliceCheckFlag
	ldr	ip, [r5, #36]	@ <variable>.ScdProtocol, <variable>.ScdProtocol
	ldr	r2, [r5, #104]	@ <variable>.ScdLowdlyEnable, <variable>.ScdLowdlyEnable
	mov	r3, r0, asl #4	@ tmp173, <variable>.SliceCheckFlag,
	and	r1, ip, #15	@ tmp167, <variable>.ScdProtocol,
	ldr	r0, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	and	ip, r3, #16	@ tmp174, tmp173,
	orr	r1, r1, r2, asl #8	@, tmp171, tmp167, <variable>.ScdLowdlyEnable,
	orr	r1, r1, ip	@, tmp171, tmp174
	add	r0, r0, #2080	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	ldr	r3, [r5, #104]	@ <variable>.ScdLowdlyEnable, <variable>.ScdLowdlyEnable
	cmp	r3, #0	@ <variable>.ScdLowdlyEnable,
	beq	.L546	@,
	ldr	r0, [r4, #868]	@, s_RegPhyBaseAddr
	ldr	r1, [r5, #108]	@, <variable>.reg_avs_flag
	bl	MEM_WritePhyWord	@
.L546:
	ldr	r2, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldr	r1, [r5, #44]	@, <variable>.DspSpsMsgMemAddr
	add	lr, r2, #2080	@, s_RegPhyBaseAddr,
	add	r0, lr, #8	@,,
	bl	MEM_WritePhyWord	@
	ldr	ip, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldr	r1, [r5, #56]	@, <variable>.DspPpsMsgMemAddr
	add	r0, ip, #2080	@, s_RegPhyBaseAddr,
	add	r0, r0, #12	@,,
	bl	MEM_WritePhyWord	@
	ldr	r3, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldr	r1, [r5, #68]	@, <variable>.DvmMemAddr
	add	r0, r3, #2096	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	ldr	r2, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldr	r1, [r5, #80]	@, <variable>.DspSedTopMemAddr
	add	ip, r2, #2096	@, s_RegPhyBaseAddr,
	add	r0, ip, #4	@,,
	bl	MEM_WritePhyWord	@
	add	r0, r6, r6, asl #1	@, tmp207, ScdId, ScdId,
	ldr	r1, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	add	r3, r4, r0, asl #5	@, tmp209, tmp220, tmp207,
	add	r2, r1, #2096	@, s_RegPhyBaseAddr,
	add	r0, r2, #8	@,,
	ldr	r1, [r3, #828]	@, <variable>.ScdDrvMem.DspCaMnMemAddr
	bl	MEM_WritePhyWord	@
	mov	r0, r6	@, ScdId
	bl	PrintScdVtrlReg	@
	ldr	ip, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	mov	r1, #0	@,
	add	r0, ip, #2048	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	ldr	r0, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldrb	r1, [r5, #2]	@ zero_extendqisi2	@ <variable>.ScdStart, <variable>.ScdStart
	add	r0, r0, #2048	@, s_RegPhyBaseAddr,
	and	r1, r1, #1	@, <variable>.ScdStart,
	bl	MEM_WritePhyWord	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	WriteScdVtrlReg, .-WriteScdVtrlReg
	.align	2
	.global	SCDDRV_EnableInt
	.type	SCDDRV_EnableInt, %function
SCDDRV_EnableInt:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp134,
	movt	r3, #:upper16:.LANCHOR0	@ tmp134,
	mov	r1, #0	@,
	ldr	r2, [r3, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	add	r0, r2, #2064	@, s_RegPhyBaseAddr,
	add	r0, r0, #12	@,,
	bl	MEM_WritePhyWord	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SCDDRV_EnableInt, .-SCDDRV_EnableInt
	.align	2
	.global	SCDDRV_MaskInt
	.type	SCDDRV_MaskInt, %function
SCDDRV_MaskInt:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp134,
	movt	r3, #:upper16:.LANCHOR0	@ tmp134,
	mov	r1, #1	@,
	ldr	r2, [r3, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	add	r0, r2, #2064	@, s_RegPhyBaseAddr,
	add	r0, r0, #12	@,,
	bl	MEM_WritePhyWord	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SCDDRV_MaskInt, .-SCDDRV_MaskInt
	.align	2
	.global	ResetSCD
	.type	ResetSCD, %function
ResetSCD:
	.fnstart
.LFB1531:
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
	movw	r0, #:lower16:-121386980	@,
	movt	r0, #:upper16:-121386980	@,
	movw	r4, #:lower16:g_pstRegCrg	@ tmp162,
	bl	MEM_ReadPhyWord	@
	movt	r4, #:upper16:g_pstRegCrg	@ tmp162,
	mov	r3, #0	@ i,
	movw	ip, #10000	@ tmp163,
	ldr	r2, [r4, #0]	@ g_pstRegCrg.449, g_pstRegCrg
	ldr	r5, [r2, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	orr	r5, r5, #32	@ u32TmpValue, u32TmpValue,
	str	r5, [r2, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r1, [r4, #0]	@ prephitmp.2358, g_pstRegCrg
	mov	r6, r0	@ D.49629,
	b	.L554	@
.L562:
	ldr	r2, [r1, #372]	@ D.49633, <variable>.PERI_CRG93.u32
	and	lr, r2, #2	@ tmp170, D.49633,
	str	r2, [fp, #-32]	@ D.49633, u32TmpValue_93.u32
	uxtb	r0, lr	@ tmp171, tmp170
	cmp	r0, #0	@ tmp171,
	bne	.L553	@,
	cmp	r3, ip	@ i, tmp163
	beq	.L561	@,
.L554:
	ldr	r0, [r1, #372]	@ D.49633, <variable>.PERI_CRG93.u32
	add	r3, r3, #1	@ tmp164, i,
	add	r3, r3, #1	@ i, tmp164,
	tst	r0, #2	@ D.49633,
	str	r0, [fp, #-32]	@ D.49633, u32TmpValue_93.u32
	beq	.L562	@,
.L553:
	movw	r3, #:lower16:.LANCHOR0	@ tmp154,
	movt	r3, #:upper16:.LANCHOR0	@ tmp154,
	bfc	r5, #5, #1	@ u32TmpValue,,
	str	r5, [r1, #120]	@ u32TmpValue, <variable>.PERI_CRG30.u32
	ldr	r0, [r3, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	and	r1, r6, #1	@, D.49629,
	add	ip, r0, #2064	@, s_RegPhyBaseAddr,
	add	r0, ip, #12	@,,
	bl	MEM_WritePhyWord	@
	mov	r0, #1	@,
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L561:
	movw	r1, #:lower16:.LC108	@,
	movt	r1, #:upper16:.LC108	@,
	bl	dprint_vfmw	@
	ldr	r1, [r4, #0]	@ prephitmp.2358, g_pstRegCrg
	b	.L553	@
	.fnend
	.size	ResetSCD, .-ResetSCD
	.align	2
	.global	SCDDRV_CheckDevice
	.type	SCDDRV_CheckDevice, %function
SCDDRV_CheckDevice:
	.fnstart
.LFB1610:
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
	subs	r5, r0, #0	@ ScdId, ScdId
	mvnne	r0, #0	@ D.53029,
	beq	.L570	@,
.L565:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L570:
	movw	r4, #:lower16:.LANCHOR0	@ tmp144,
	movt	r4, #:upper16:.LANCHOR0	@ tmp144,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC109	@,
	ldr	ip, [r4, #856]	@ <variable>.SCDState, <variable>.SCDState
	movt	r1, #:upper16:.LC109	@,
	ldr	r2, .L572	@,
	movw	r3, #5624	@,
	stmia	sp, {r5, ip}	@ phole stm
	bl	dprint_vfmw	@
	ldr	r6, [r4, #856]	@ temp.2399, <variable>.SCDState
	cmp	r6, #0	@ temp.2399,
	beq	.L571	@,
	movw	r3, #5633	@,
	ldr	r2, .L572	@,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC109	@,
	movt	r1, #:upper16:.LC109	@,
	stmia	sp, {r5, r6}	@ phole stm
	bl	dprint_vfmw	@
	bl	OSAL_GetTimeInMs	@
	ldr	r3, [r4, #860]	@ D.53038, <variable>.LastProcessTime
	cmp	r0, r3	@ CurTime, D.53038
	strcc	r0, [r4, #860]	@ CurTime, <variable>.LastProcessTime
	bcc	.L568	@,
	rsb	r3, r3, r0	@ DelayTime, D.53038, CurTime
	cmp	r3, #2000	@ DelayTime,
	bls	.L568	@,
	mov	r2, r5	@, ScdId
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC111	@,
	movt	r1, #:upper16:.LC111	@,
	bl	dprint_vfmw	@
	mov	r0, r5	@, ScdId
	bl	ResetSCD	@
	ldr	r0, [r4, #852]	@, <variable>.ThisInstID
	str	r5, [r4, #856]	@ ScdId, <variable>.SCDState
	bl	DeleteLastSendRaw	@
	mov	r0, r5	@ D.53029, ScdId
	b	.L565	@
.L568:
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC112	@,
	ldr	r2, .L572	@,
	movt	r1, #:upper16:.LC112	@,
	movw	r3, #5665	@,
	mov	lr, #0	@ tmp164,
	str	lr, [sp, #0]	@ tmp164,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.53029,
	b	.L565	@
.L571:
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC110	@,
	ldr	r2, .L572	@,
	movt	r1, #:upper16:.LC110	@,
	movw	r3, #5627	@,
	str	r6, [sp, #0]	@ temp.2399,
	bl	dprint_vfmw	@
	mov	r0, r6	@ D.53029, temp.2399
	b	.L565	@
.L573:
	.align	2
.L572:
	.word	.LANCHOR1+152
	.fnend
	.size	SCDDRV_CheckDevice, .-SCDDRV_CheckDevice
	.align	2
	.global	FillEosRawStream
	.type	FillEosRawStream, %function
FillEosRawStream:
	.fnstart
.LFB1601:
	@ args = 0, pretend = 0, frame = 104
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #116
	sub	sp, sp, #116	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	add	r0, r0, r0, asl #1	@, tmp146, InstID, InstID,
	movw	r2, #:lower16:.LANCHOR0	@ tmp142,
	sub	r5, fp, #128	@ tmp177,,
	movt	r2, #:upper16:.LANCHOR0	@ tmp142,
	mov	r4, r1	@ pRawPacket, pRawPacket
	add	r3, r2, r0, asl #4	@, tmp148, tmp142, tmp146,
	ldr	r1, .L593	@,
	mov	r0, r5	@, tmp177
	mov	r2, #100	@,
	ldr	r6, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	bl	memcpy	@
	cmp	r4, #0	@ pRawPacket,
	beq	.L591	@,
	ldr	r3, [r6, #56]	@ D.52324, <variable>.Config.VidStd
	cmp	r3, #16	@ D.52324,
	ldrls	pc, [pc, r3, asl #2]	@ D.52324
	b	.L577	@
.L586:
	.word	.L584
	.word	.L579
	.word	.L580
	.word	.L581
	.word	.L582
	.word	.L582
	.word	.L590
	.word	.L577
	.word	.L582
	.word	.L582
	.word	.L582
	.word	.L582
	.word	.L582
	.word	.L582
	.word	.L582
	.word	.L584
	.word	.L585
.L579:
	ldr	r1, [r6, #72]	@ <variable>.Config.StdExt.Vc1Ext.IsAdvProfile, <variable>.Config.StdExt.Vc1Ext.IsAdvProfile
	cmp	r1, #1	@ <variable>.Config.StdExt.Vc1Ext.IsAdvProfile,
	beq	.L590	@,
.L582:
	mov	r0, #0	@ D.52323,
.L576:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L584:
	mov	r1, r5	@ pu8Flag, tmp177
	mov	r6, #15	@ u32FlagLen,
.L587:
	ldr	ip, [r4, #8]	@ D.52329, <variable>.Length
	cmp	r6, ip	@ u32FlagLen, D.52329
	bhi	.L592	@,
	ldr	r0, [r4, #4]	@, <variable>.VirAddr
	mov	r2, r6	@, u32FlagLen
	bl	memcpy	@
	str	r6, [r4, #8]	@ u32FlagLen, <variable>.Length
	mov	r0, #0	@ D.52323,
	b	.L576	@
.L590:
	add	r1, r5, #20	@ pu8Flag, tmp177,
	mov	r6, #15	@ u32FlagLen,
	b	.L587	@
.L577:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC114	@,
	ldr	r2, .L593+4	@,
	movt	r1, #:upper16:.LC114	@,
	bl	dprint_vfmw	@
	mvn	r0, #6	@ D.52323,
	b	.L576	@
.L585:
	add	r1, r5, #80	@ pu8Flag, tmp177,
	mov	r6, #16	@ u32FlagLen,
	b	.L587	@
.L580:
	add	r1, r5, #40	@ pu8Flag, tmp177,
	mov	r6, #19	@ u32FlagLen,
	b	.L587	@
.L581:
	add	r1, r5, #60	@ pu8Flag, tmp177,
	mov	r6, #16	@ u32FlagLen,
	b	.L587	@
.L592:
	mov	r3, r6	@, u32FlagLen
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC115	@,
	ldr	r2, .L593+4	@,
	movt	r1, #:upper16:.LC115	@,
	str	ip, [sp, #0]	@ D.52329,
	bl	dprint_vfmw	@
	mvn	r0, #6	@ D.52323,
	b	.L576	@
.L591:
	mov	r0, r4	@, pRawPacket
	movw	r1, #:lower16:.LC113	@,
	ldr	r2, .L593+4	@,
	movt	r1, #:upper16:.LC113	@,
	bl	dprint_vfmw	@
	mvn	r0, #6	@ D.52323,
	b	.L576	@
.L594:
	.align	2
.L593:
	.word	.LANCHOR1+172
	.word	.LANCHOR1+272
	.fnend
	.size	FillEosRawStream, .-FillEosRawStream
	.align	2
	.global	GetStreamSeg
	.type	GetStreamSeg, %function
GetStreamSeg:
	.fnstart
.LFB1554:
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
	cmp	r0, #0	@ pStreamSegArray,
	cmpne	r1, #0	@, pStreamSeg,
	mov	r4, r0	@ pStreamSegArray, pStreamSegArray
	mvneq	r0, #0	@ Ret,
	beq	.L597	@,
	movw	r2, #:lower16:92168	@ tmp151,
	movw	r3, #:lower16:92172	@ tmp152,
	movt	r2, #:upper16:92168	@ tmp151,
	movt	r3, #:upper16:92172	@ tmp152,
	ldr	r6, [r4, r2]	@ i, <variable>.Head
	ldr	ip, [r4, r3]	@ D.50160, <variable>.Tail
	cmp	r6, ip	@ i, D.50160
	beq	.L598	@,
	mov	r3, r6, asl #2	@ tmp238, i,
	add	r2, r3, r6	@ tmp155, tmp238, i
	add	r2, r4, r2, asl #4	@, tmp159, pStreamSegArray, tmp155,
	ldrsb	r2, [r2, #12]	@ <variable>.SegState, <variable>.SegState
	cmp	r2, #1	@ <variable>.SegState,
	movwne	r0, #:lower16:954437177	@ tmp239,
	movtne	r0, #:upper16:954437177	@ tmp239,
	bne	.L603	@,
	b	.L599	@
.L601:
	add	r2, r4, r2, asl #4	@, tmp169, pStreamSegArray, tmp165,
	ldrsb	r2, [r2, #12]	@ <variable>.SegState, <variable>.SegState
	cmp	r2, #1	@ <variable>.SegState,
	beq	.L599	@,
.L603:
	add	r6, r6, #1	@ D.50169, i,
	smull	r3, r2, r0, r6	@, tmp228, tmp239, D.50169
	mov	r3, r6, asr #31	@ tmp231, D.50169,
	rsb	r3, r3, r2, asr #8	@, i, tmp231, tmp228,
	add	r2, r3, r3, asl #3	@, tmp234, i, i,
	sub	r6, r6, r2, asl #7	@ i, D.50169, tmp234,
	cmp	r6, ip	@ i, D.50160
	mov	r3, r6, asl #2	@ tmp238, i,
	add	r2, r3, r6	@ tmp165, tmp238, i
	bne	.L601	@,
.L598:
	mvn	r0, #2	@ Ret,
.L597:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L599:
	add	r6, r3, r6	@ tmp175, tmp238, i
	mov	r0, r1	@, pStreamSeg
	mov	r2, #80	@,
	add	r5, r4, r6, asl #4	@, tmp178, pStreamSegArray, tmp175,
	add	r6, r6, #1	@ tmp198, tmp175,
	add	r5, r5, #8	@ tmp179, tmp178,
	mov	r1, r5	@, tmp179
	bl	memcpy	@
	movw	ip, #:lower16:92204	@ tmp203,
	add	r3, r4, r6, asl #4	@, tmp201, pStreamSegArray, tmp198,
	movt	ip, #:upper16:92204	@ tmp203,
	movw	r2, #:lower16:92208	@ tmp206,
	movt	r2, #:upper16:92208	@ tmp206,
	ldr	r3, [r3, #4]	@ D.50173, <variable>.LenInByte
	mov	r1, #2	@ tmp193,
	strb	r1, [r5, #4]	@ tmp193, <variable>.SegState
	mov	r0, #26	@,
	ldr	r7, [r4, ip]	@ <variable>.SegFreshSize, <variable>.SegFreshSize
	movw	r1, #:lower16:.LC116	@,
	ldr	lr, [r4, r2]	@ <variable>.SegFreshNum, <variable>.SegFreshNum
	movt	r1, #:upper16:.LC116	@,
	rsb	r7, r3, r7	@ D.50174, D.50173, <variable>.SegFreshSize
	sub	lr, lr, #1	@ D.50176, <variable>.SegFreshNum,
	bic	r7, r7, r7, asr #31	@ tmp209, D.50174
	str	r7, [r4, ip]	@ tmp209, <variable>.SegFreshSize
	bic	ip, lr, lr, asr #31	@ tmp211, D.50176
	str	ip, [r4, r2]	@ tmp211, <variable>.SegFreshNum
	ldrb	ip, [r5, #5]	@ zero_extendqisi2	@ <variable>.IsLastSeg, <variable>.IsLastSeg
	ldr	r2, [r4, r6, asl #4]	@ <variable>.PhyAddr, <variable>.PhyAddr
	str	ip, [sp, #0]	@ <variable>.IsLastSeg,
	bl	dprint_vfmw	@
	mov	r0, #0	@ Ret,
	b	.L597	@
	.fnend
	.size	GetStreamSeg, .-GetStreamSeg
	.align	2
	.global	InsertStreamSeg
	.type	InsertStreamSeg, %function
InsertStreamSeg:
	.fnstart
.LFB1553:
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
	cmp	r0, #0	@ pStreamSegArray,
	cmpne	r1, #0	@, pStreamSeg,
	mov	r4, r0	@ pStreamSegArray, pStreamSegArray
	mov	r7, r1	@ pStreamSeg, pStreamSeg
	movne	sl, #0	@, tmp145
	moveq	sl, #1	@, tmp145
	mvneq	r0, #0	@ Ret,
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	movw	r5, #:lower16:92172	@ tmp146,
	movt	r5, #:upper16:92172	@ tmp146,
	movw	r6, #:lower16:954437177	@ tmp150,
	movt	r6, #:upper16:954437177	@ tmp150,
	ldr	r8, [r4, r5]	@ D.50126, <variable>.Tail
	movw	r2, #:lower16:92168	@ tmp158,
	movt	r2, #:upper16:92168	@ tmp158,
	add	r3, r8, #1	@ tmp147, D.50126,
	ldr	r2, [r4, r2]	@ <variable>.Head, <variable>.Head
	smull	r0, ip, r6, r3	@, tmp149, tmp150, tmp147
	mov	r0, r3, asr #31	@ tmp152, tmp147,
	rsb	r0, r0, ip, asr #8	@, tmp148, tmp152, tmp149,
	add	r0, r0, r0, asl #3	@, tmp155, tmp148, tmp148,
	sub	r3, r3, r0, asl #7	@ tmp157, tmp147, tmp155,
	cmp	r3, r2	@ tmp157, <variable>.Head
	mvneq	r0, #3	@ Ret,
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	add	r8, r8, r8, asl #2	@, tmp162, D.50126, D.50126,
	mov	r2, #80	@,
	add	lr, r4, r8, asl #4	@, tmp165, pStreamSegArray, tmp162,
	add	r9, r4, r8, asl #4	@, tmp189, pStreamSegArray, tmp162,
	add	r0, lr, #8	@, tmp165,
	mov	r8, #1	@ tmp182,
	bl	memcpy	@
	ldr	r3, [r4, r5]	@ <variable>.Tail, <variable>.Tail
	movw	ip, #:lower16:92196	@ tmp206,
	movw	r1, #:lower16:92200	@ tmp210,
	movt	ip, #:upper16:92196	@ tmp206,
	movt	r1, #:upper16:92200	@ tmp210,
	add	r2, r3, r3, asl #2	@, tmp175, <variable>.Tail, <variable>.Tail,
	movw	r3, #:lower16:92204	@ tmp215,
	movt	r3, #:upper16:92204	@ tmp215,
	add	r0, r4, r2, asl #4	@, tmp179, pStreamSegArray, tmp175,
	movw	r2, #:lower16:92208	@ tmp220,
	movt	r2, #:upper16:92208	@ tmp220,
	strb	r8, [r0, #12]	@ tmp182, <variable>.SegState
	mov	r0, sl	@ Ret, tmp145
	ldr	sl, [r4, r5]	@ <variable>.Tail, <variable>.Tail
	str	sl, [r9, #24]	@ <variable>.Tail, <variable>.StreamID
	ldr	r8, [r4, r5]	@ <variable>.Tail, <variable>.Tail
	ldr	r9, [r4, r2]	@ <variable>.SegFreshNum, <variable>.SegFreshNum
	add	r8, r8, #1	@ tmp194, <variable>.Tail,
	add	r9, r9, #1	@ tmp223, <variable>.SegFreshNum,
	smull	sl, r6, r6, r8	@, tmp196, tmp150, tmp194
	mov	sl, r8, asr #31	@ tmp199, tmp194,
	rsb	r6, sl, r6, asr #8	@, tmp200, tmp199, tmp196,
	add	sl, r6, r6, asl #3	@, tmp203, tmp200, tmp200,
	sub	r6, r8, sl, asl #7	@ tmp205, tmp194, tmp203,
	str	r6, [r4, r5]	@ tmp205, <variable>.Tail
	ldr	sl, [r7, #8]	@ <variable>.PhyAddr, <variable>.PhyAddr
	ldr	r6, [r7, #12]	@ <variable>.LenInByte, <variable>.LenInByte
	add	r5, r6, sl	@ tmp209, <variable>.LenInByte, <variable>.PhyAddr
	str	r5, [r4, ip]	@ tmp209, <variable>.SegBufWriteAddr
	ldr	r5, [r4, r1]	@, <variable>.SegTotalSize
	ldr	ip, [r7, #12]	@ <variable>.LenInByte, <variable>.LenInByte
	add	sl, ip, r5	@ tmp214, <variable>.LenInByte,
	str	sl, [r4, r1]	@ tmp214, <variable>.SegTotalSize
	ldr	sl, [r4, r3]	@, <variable>.SegFreshSize
	ldr	r1, [r7, #12]	@ <variable>.LenInByte, <variable>.LenInByte
	str	r9, [r4, r2]	@ tmp223, <variable>.SegFreshNum
	add	ip, r1, sl	@ tmp219, <variable>.LenInByte,
	str	ip, [r4, r3]	@ tmp219, <variable>.SegFreshSize
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	.fnend
	.size	InsertStreamSeg, .-InsertStreamSeg
	.align	2
	.global	ShowNextRawPacket
	.type	ShowNextRawPacket, %function
ShowNextRawPacket:
	.fnstart
.LFB1538:
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
	cmp	r0, #0	@ pRawStreamArray,
	cmpne	r1, #0	@, pRawPacket,
	mov	r3, r0	@ pRawStreamArray, pRawStreamArray
	movne	r4, #0	@, tmp144
	moveq	r4, #1	@, tmp144
	mvneq	r0, #0	@ D.49737,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	movw	r2, #:lower16:98320	@ tmp145,
	movt	r2, #:upper16:98320	@ tmp145,
	movw	r0, #:lower16:98308	@ tmp154,
	movt	r0, #:upper16:98308	@ tmp154,
	ldr	ip, [r3, r2]	@ <variable>.CurShowIndex, <variable>.CurShowIndex
	ldr	r5, [r3, r0]	@ <variable>.Tail, <variable>.Tail
	add	r0, ip, #1	@ tmp146, <variable>.CurShowIndex,
	mov	ip, r0, asr #31	@ tmp148, tmp146,
	mov	ip, ip, lsr #22	@ tmp149, tmp148,
	add	r0, r0, ip	@ tmp150, tmp146, tmp149
	mov	r0, r0, asl #22	@ tmp151, tmp150,
	mov	r0, r0, lsr #22	@ tmp151, tmp151,
	rsb	r0, ip, r0	@ tmp153, tmp149, tmp151
	cmp	r5, r0	@ <variable>.Tail, tmp153
	mvneq	r0, #2	@ D.49737,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	add	lr, r0, r0, asl #1	@, tmp159, tmp153, tmp153,
	str	r0, [r3, r2]	@ tmp153, <variable>.CurShowIndex
	mov	r0, r1	@, pRawPacket
	mov	r2, #96	@,
	add	r1, r3, lr, asl #5	@,, pRawStreamArray, tmp159,
	bl	memcpy	@
	mov	r0, r4	@ D.49737, tmp144
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	ShowNextRawPacket, .-ShowNextRawPacket
	.align	2
	.global	ShowFirstRawPacket
	.type	ShowFirstRawPacket, %function
ShowFirstRawPacket:
	.fnstart
.LFB1537:
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
	cmp	r0, #0	@ pRawStreamArray,
	cmpne	r1, #0	@, pRawPacket,
	mov	r3, r0	@ pRawStreamArray, pRawStreamArray
	movne	r4, #0	@, tmp144
	moveq	r4, #1	@, tmp144
	mvneq	r0, #0	@ D.49718,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	movw	r2, #:lower16:98308	@ tmp146,
	movt	r2, #:upper16:98308	@ tmp146,
	mov	r0, #98304	@ tmp145,
	ldr	ip, [r3, r0]	@ D.49719, <variable>.Head
	ldr	r2, [r3, r2]	@ <variable>.Tail, <variable>.Tail
	cmp	ip, r2	@ D.49719, <variable>.Tail
	mvneq	r0, #2	@ D.49718,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	add	r2, ip, ip, asl #1	@, tmp151, D.49719, D.49719,
	movw	lr, #:lower16:98320	@ tmp148,
	movt	lr, #:upper16:98320	@ tmp148,
	mov	r0, r1	@, pRawPacket
	add	r1, r3, r2, asl #5	@,, pRawStreamArray, tmp151,
	mov	r2, #96	@,
	str	ip, [r3, lr]	@ D.49719, <variable>.CurShowIndex
	bl	memcpy	@
	mov	r0, r4	@ D.49718, tmp144
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	ShowFirstRawPacket, .-ShowFirstRawPacket
	.align	2
	.global	WriteScdMsg
	.type	WriteScdMsg, %function
WriteScdMsg:
	.fnstart
.LFB1585:
	@ args = 12, pretend = 0, frame = 112
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
	sub	r9, fp, #140	@ tmp220,,
	mov	r6, r2	@ pRawStreamArray, pRawStreamArray
	str	r1, [fp, #-144]	@ SegStreamSize, %sfp
	mov	sl, r0	@ pSmPushRaw, pSmPushRaw
	mov	r1, #0	@,
	mov	r0, r9	@, tmp220
	mov	r2, #96	@,
	mov	r5, r3	@ pDownMsgVirAddr, pDownMsgVirAddr
	bl	memset	@
	cmp	r6, #0	@ pRawStreamArray,
	beq	.L622	@,
	movw	r0, #:lower16:98308	@ tmp160,
	movt	r0, #:upper16:98308	@ tmp160,
	mov	r1, #98304	@ tmp159,
	ldr	r2, [r6, r1]	@ <variable>.Head, <variable>.Head
	ldr	r3, [r6, r0]	@ <variable>.Tail, <variable>.Tail
	cmp	r2, r3	@ <variable>.Head, <variable>.Tail
	beq	.L622	@,
	movw	r7, #:lower16:98316	@ tmp163,
	movt	r7, #:upper16:98316	@ tmp163,
	ldr	r4, [r6, r7]	@ FirstRawOffset, <variable>.FirstPacketOffset
	mov	r8, r4	@ prephitmp.2539, FirstRawOffset
.L623:
	mov	r1, r9	@, tmp220
	mov	r0, r6	@, pRawStreamArray
	bl	ShowFirstRawPacket	@
	ldr	r0, [fp, #-132]	@ RawPacket.Length, RawPacket.Length
	ldr	r3, [fp, #-136]	@ RawPacket.VirAddr, RawPacket.VirAddr
	mov	r2, #0	@ tmp170,
	rsb	r7, r4, r0	@ RawShowTotalLen, FirstRawOffset, RawPacket.Length
	ldr	r0, [fp, #-144]	@, %sfp
	ldr	r1, [fp, #-140]	@ RawPacket.PhyAddr, RawPacket.PhyAddr
	add	r8, r3, r8	@ tmp168, RawPacket.VirAddr, prephitmp.2539
	cmp	r7, r0	@ RawShowTotalLen,
	movgt	ip, #0	@, tmp178
	movle	ip, #1	@, tmp178
	str	r8, [fp, #-136]	@ tmp168, RawPacket.VirAddr
	cmp	ip, r2	@ tmp178,
	add	r4, r1, r4	@ tmp166, RawPacket.PhyAddr, FirstRawOffset
	mov	r3, r7	@ RawPacket.Length, RawShowTotalLen
	str	r4, [fp, #-140]	@ tmp166, RawPacket.PhyAddr
	moveq	r8, ip	@ j.2582, tmp178
	str	r2, [r5, #0]	@ tmp170,* pDownMsgVirAddr
	str	r2, [r5, #4]	@ tmp170,
	moveq	r4, r8	@ PushRawNum, j.2582
	str	r2, [r5, #8]	@ tmp170,
	str	r7, [fp, #-132]	@ RawShowTotalLen, RawPacket.Length
	str	r2, [sl, #4]	@ tmp170, <variable>.PushRawTotalLen
	beq	.L625	@,
	mov	r8, r2	@ j.2582, tmp170
	str	r6, [fp, #-152]	@ pRawStreamArray, %sfp
	mov	r2, r7	@ prephitmp.2541, RawShowTotalLen
	mov	r4, r8	@ PushRawNum, j.2582
	b	.L627	@
.L634:
	ldr	r3, [fp, #-132]	@ RawPacket.Length, RawPacket.Length
	movw	r0, #1023	@,
	ldr	r2, [fp, #-144]	@, %sfp
	cmp	r4, r0	@ PushRawNum,
	movgt	r1, #0	@, tmp195
	movle	r1, #1	@, tmp195
	add	r7, r7, r3	@ RawShowTotalLen, RawShowTotalLen, RawPacket.Length
	cmp	r2, r7	@, RawShowTotalLen
	mov	r2, r3	@ prephitmp.2541, RawPacket.Length
	movlt	r1, #0	@, tmp195,
	cmp	r1, #0	@ tmp195,
	beq	.L625	@,
.L627:
	cmp	r2, #0	@ prephitmp.2541,
	add	ip, r8, #1	@ j, j.2582,
	ldr	r0, [fp, #-152]	@, %sfp
	mov	r1, r9	@, tmp220
	add	r2, ip, #1	@ j.2560, j,
	add	r4, r4, #1	@ PushRawNum, PushRawNum,
	ble	.L626	@,
	ldr	lr, [fp, #-140]	@ RawPacket.PhyAddr, RawPacket.PhyAddr
	mov	r6, #0	@,
	str	r6, [fp, #-132]	@, RawPacket.Length
	add	r3, lr, r3	@ tmp180, RawPacket.PhyAddr, RawPacket.Length
	str	lr, [r5, r8, asl #2]	@ RawPacket.PhyAddr,* pDownMsgVirAddr
	sub	r3, r3, #1	@ tmp183, tmp180,
	str	r3, [r5, ip, asl #2]	@ tmp183,* pDownMsgVirAddr
	add	r8, r2, #1	@ j.2582, j.2560,
	ldr	ip, [fp, #4]	@, DownMsgPhyAddr
	add	lr, ip, r8, asl #2	@, tmp185,, j.2582,
	str	lr, [r5, r2, asl #2]	@ tmp185,* pDownMsgVirAddr
.L626:
	str	r7, [sl, #4]	@ RawShowTotalLen, <variable>.PushRawTotalLen
	bl	ShowNextRawPacket	@
	cmp	r0, #0	@,
	beq	.L634	@,
.L625:
	ldr	ip, [fp, #8]	@, LowdlyFlag
	cmp	ip, #0	@,
	bne	.L628	@,
	ldr	r3, [fp, #-132]	@ temp.2565, RawPacket.Length
	cmp	r3, #0	@ temp.2565,
	bne	.L635	@,
.L628:
	cmp	r4, #0	@ PushRawNum,
	mvneq	r0, #5	@ D.51391,
	bne	.L629	@,
.L630:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L635:
	ldr	r6, [fp, #-144]	@, %sfp
	ldr	r2, [sl, #4]	@ D.51376, <variable>.PushRawTotalLen
	sub	lr, r6, #16	@ tmp198,,
	cmp	r6, r7	@, RawShowTotalLen
	cmplt	r2, lr	@, D.51376, tmp198
	bge	.L628	@,
	cmp	r4, #1024	@ PushRawNum,
	bge	.L629	@,
	rsb	r2, r2, r6	@ D.51385, D.51376,
	cmp	r3, r2	@ temp.2565, D.51385
	blt	.L628	@,
	ldr	r0, [fp, #-140]	@ RawPacket.PhyAddr, RawPacket.PhyAddr
	add	r6, r8, #1	@ j.2570, j.2582,
	ldr	ip, [fp, #8]	@, LowdlyFlag
	add	r3, r6, #1	@ j.2578, j.2570,
	add	r1, r0, r2	@ tmp206, RawPacket.PhyAddr, D.51385
	add	r4, r4, #1	@ PushRawNum, PushRawNum,
	sub	lr, r1, #1	@ tmp209, tmp206,
	str	ip, [fp, #-132]	@, RawPacket.Length
	str	r0, [r5, r8, asl #2]	@ RawPacket.PhyAddr,* pDownMsgVirAddr
	add	r8, r3, #1	@ j.2582, j.2578,
	str	lr, [r5, r6, asl #2]	@ tmp209,* pDownMsgVirAddr
	ldr	ip, [fp, #4]	@, DownMsgPhyAddr
	add	r1, ip, r8, asl #2	@, tmp211,, j.2582,
	str	r1, [r5, r3, asl #2]	@ tmp211,* pDownMsgVirAddr
	ldr	r0, [sl, #4]	@ <variable>.PushRawTotalLen, <variable>.PushRawTotalLen
	add	r6, r0, r2	@ tmp214, <variable>.PushRawTotalLen, D.51385
	str	r6, [sl, #4]	@ tmp214, <variable>.PushRawTotalLen
.L629:
	sub	r8, r8, #1	@ tmp216, j.2582,
	ldr	r0, [fp, #4]	@, DownMsgPhyAddr
	ldr	r3, [fp, #12]	@, ScdId
	mov	r6, #0	@ tmp217,
	mov	lr, #1	@ tmp218,
	str	r6, [r5, r8, asl #2]	@ tmp217,* pDownMsgVirAddr
	mov	r1, r5	@, pDownMsgVirAddr
	mov	r2, r4	@, PushRawNum
	str	lr, [sl, #8]	@ tmp218, <variable>.PushRawOver
	str	r4, [sl, #0]	@ PushRawNum, <variable>.PushRawNum
	bl	PrintDownMsg	@
	mov	r0, r6	@ D.51391, tmp217
	b	.L630	@
.L622:
	mov	r8, #0	@ prephitmp.2539,
	mov	r4, r8	@ FirstRawOffset, prephitmp.2539
	b	.L623	@
	.fnend
	.size	WriteScdMsg, .-WriteScdMsg
	.align	2
	.global	ScdDriver
	.type	ScdDriver, %function
ScdDriver:
	.fnstart
.LFB1586:
	@ args = 12, pretend = 0, frame = 0
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
	ldr	r4, [fp, #12]	@ ScdId, ScdId
	mov	r5, r0	@ pSmCtrlReg, pSmCtrlReg
	mov	r6, r1	@ pSmPushRaw, pSmPushRaw
	mov	r8, r2	@ SegStreamSize, SegStreamSize
	mov	r7, r3	@ pRawStreamArray, pRawStreamArray
	mov	r0, r4	@, ScdId
	bl	ResetSCD	@
	ldr	ip, [r5, #104]	@ <variable>.ScdLowdlyEnable, <variable>.ScdLowdlyEnable
	ldr	lr, [fp, #8]	@ DownMsgPhyAddr, DownMsgPhyAddr
	mov	r0, r6	@, pSmPushRaw
	mov	r1, r8	@, SegStreamSize
	mov	r2, r7	@, pRawStreamArray
	ldr	r3, [fp, #4]	@, pDownMsgVirAddr
	str	lr, [sp, #0]	@ DownMsgPhyAddr,
	str	ip, [sp, #4]	@ <variable>.ScdLowdlyEnable,
	str	r4, [sp, #8]	@ ScdId,
	bl	WriteScdMsg	@
	subs	r6, r0, #0	@ Ret,
	bne	.L637	@,
	bl	OSAL_GetTimeInMs	@
	movw	r3, #:lower16:g_VfmwGlobalStat	@ tmp144,
	movt	r3, #:upper16:g_VfmwGlobalStat	@ tmp144,
	mov	r2, #84	@ tmp147,
	mov	r1, r4	@, ScdId
	mla	r4, r2, r4, r3	@ tmp148, tmp147, ScdId, tmp144
	str	r0, [r4, #68]	@, <variable>.u32SaLastStartTime
	mov	r0, r5	@, pSmCtrlReg
	bl	WriteScdVtrlReg	@
.L637:
	mov	r0, r6	@, Ret
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	.fnend
	.size	ScdDriver, .-ScdDriver
	.align	2
	.global	InsertRawPacket
	.type	InsertRawPacket, %function
InsertRawPacket:
	.fnstart
.LFB1535:
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
	cmp	r0, #0	@ pRawStreamArray,
	cmpne	r1, #0	@, pRawPacket,
	mov	r4, r0	@ pRawStreamArray, pRawStreamArray
	movne	r5, #0	@, tmp144
	moveq	r5, #1	@, tmp144
	mvneq	r0, #0	@ D.49678,
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	movw	r6, #:lower16:98308	@ tmp145,
	movt	r6, #:upper16:98308	@ tmp145,
	movw	r3, #:lower16:98312	@ tmp154,
	movt	r3, #:upper16:98312	@ tmp154,
	ldr	r2, [r4, r6]	@ D.49679, <variable>.Tail
	ldr	ip, [r4, r3]	@ <variable>.History, <variable>.History
	add	r3, r2, #1	@ tmp146, D.49679,
	mov	r0, r3, asr #31	@ tmp148, tmp146,
	mov	r0, r0, lsr #22	@ tmp149, tmp148,
	add	r3, r3, r0	@ tmp150, tmp146, tmp149
	mov	r3, r3, asl #22	@ tmp151, tmp150,
	mov	r3, r3, lsr #22	@ tmp151, tmp151,
	rsb	r3, r0, r3	@ tmp153, tmp149, tmp151
	cmp	r3, ip	@ tmp153, <variable>.History
	mvneq	r0, #3	@ D.49678,
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	add	lr, r2, r2, asl #1	@, tmp158, D.49679, D.49679,
	mov	r2, #96	@,
	add	r0, r4, lr, asl #5	@,, pRawStreamArray, tmp158,
	bl	memcpy	@
	ldr	r3, [r4, r6]	@ <variable>.Tail, <variable>.Tail
	mov	r0, r5	@ D.49678, tmp144
	add	ip, r3, #1	@ tmp167, <variable>.Tail,
	mov	r2, ip, asr #31	@ tmp169, tmp167,
	mov	r2, r2, lsr #22	@ tmp170, tmp169,
	add	r1, ip, r2	@ tmp171, tmp167, tmp170
	mov	r3, r1, asl #22	@ tmp172, tmp171,
	mov	ip, r3, lsr #22	@ tmp172, tmp172,
	rsb	r1, r2, ip	@ tmp174, tmp170, tmp172
	str	r1, [r4, r6]	@ tmp174, <variable>.Tail
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	InsertRawPacket, .-InsertRawPacket
	.align	2
	.global	SM_PushRaw
	.type	SM_PushRaw, %function
SM_PushRaw:
	.fnstart
.LFB1575:
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
	add	r0, r0, r0, asl #1	@, tmp142, SmID, SmID,
	ldr	ip, [r1, #0]	@ <variable>.PhyAddr, <variable>.PhyAddr
	movw	r2, #:lower16:.LANCHOR0	@ tmp138,
	movt	r2, #:upper16:.LANCHOR0	@ tmp138,
	add	r2, r2, r0, asl #4	@, tmp144, tmp138, tmp142,
	cmp	ip, #0	@ <variable>.PhyAddr,
	ldr	r0, [r2, #40]	@ pSmInstArray, <variable>.pSmInstArray
	bne	.L648	@,
.L645:
	mvn	r0, #0	@ Ret,
	ldmfd	sp, {fp, sp, pc}	@
.L648:
	ldr	r3, [r1, #4]	@ <variable>.VirAddr, <variable>.VirAddr
	cmp	r3, #0	@ <variable>.VirAddr,
	beq	.L645	@,
	cmp	r0, #0	@ pSmInstArray,
	beq	.L645	@,
	add	r0, r0, #200	@, pSmInstArray,
	bl	InsertRawPacket	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SM_PushRaw, .-SM_PushRaw
	.align	2
	.global	ReleaseRawStreamData
	.type	ReleaseRawStreamData, %function
ReleaseRawStreamData:
	.fnstart
.LFB1604:
	@ args = 0, pretend = 0, frame = 16
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
	mov	r7, r1	@ pRawPacket, pRawPacket
	mov	r6, r0	@ InstID, InstID
	bl	VCTRL_GetStreamInterface	@
	sub	r5, fp, #48	@ tmp138,,
	mov	r1, #12	@,
	mov	r4, r0	@ pStreamIntf,
	mov	r0, r5	@, tmp138
	bl	__memzero	@
	cmp	r4, #0	@ pStreamIntf,
	beq	.L659	@,
	ldmia	r4, {r0, r1, r2}	@ pStreamIntf,,,
	stmia	r5, {r0, r1, r2}	@ tmp138,,,
	ldr	r3, [r4, #8]	@ <variable>.release_stream, <variable>.release_stream
	cmp	r3, #0	@ <variable>.release_stream,
	moveq	r8, r6, asl #1	@ tmp171, InstID,
	movweq	r5, #:lower16:.LANCHOR0	@ tmp170,
	movteq	r5, #:upper16:.LANCHOR0	@ tmp170,
	beq	.L652	@,
	mov	r8, r6, asl #1	@ tmp171, InstID,
	movw	r5, #:lower16:.LANCHOR0	@ tmp170,
	add	r4, r8, r6	@ tmp147, tmp171, InstID
	movt	r5, #:upper16:.LANCHOR0	@ tmp170,
	add	r2, r5, r4, asl #4	@, tmp149, tmp170, tmp147,
	ldr	r1, [r2, #40]	@ <variable>.pSmInstArray, <variable>.pSmInstArray
	ldr	r0, [r1, #92]	@ <variable>.Config.IsOmxPath, <variable>.Config.IsOmxPath
	cmp	r0, #1	@ <variable>.Config.IsOmxPath,
	beq	.L660	@,
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r1, r7	@, pRawPacket
	ldr	r0, [fp, #-48]	@, StreamIntf.stream_provider_inst_id
	ldr	r3, [fp, #-40]	@ StreamIntf.release_stream, StreamIntf.release_stream
	blx	r3	@ StreamIntf.release_stream
	mov	r4, r0	@ ret,
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
.L654:
	cmp	r4, #0	@ ret,
	bne	.L652	@,
.L655:
	add	r8, r8, r6	@ tmp163, tmp171, InstID
	add	r5, r5, r8, asl #4	@, tmp165, tmp170, tmp163,
	ldr	r0, [r5, #40]	@ <variable>.pSmInstArray, <variable>.pSmInstArray
	cmp	r0, #0	@ <variable>.pSmInstArray,
	beq	.L661	@,
.L651:
	mov	r0, r4	@, ret
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L652:
	mvn	r4, #6	@ ret,
	b	.L655	@
.L660:
	mov	r1, r7	@, pRawPacket
	ldr	r0, [fp, #-48]	@, StreamIntf.stream_provider_inst_id
	ldr	ip, [fp, #-40]	@ StreamIntf.release_stream, StreamIntf.release_stream
	blx	ip	@ StreamIntf.release_stream
	mov	r4, r0	@ ret,
	b	.L654	@
.L659:
	mov	r0, r4	@, pStreamIntf
	mov	r2, r6	@, InstID
	movw	r1, #:lower16:.LC117	@,
	movt	r1, #:upper16:.LC117	@,
	bl	dprint_vfmw	@
	mvn	r4, #6	@ ret,
	b	.L651	@
.L661:
	mov	r3, r6	@, InstID
	movw	r1, #:lower16:.LC118	@,
	movw	r2, #4763	@,
	movt	r1, #:upper16:.LC118	@,
	mvn	r4, #6	@ ret,
	bl	dprint_vfmw	@
	b	.L651	@
	.fnend
	.size	ReleaseRawStreamData, .-ReleaseRawStreamData
	.align	2
	.global	SM_MoveRawData
	.type	SM_MoveRawData, %function
SM_MoveRawData:
	.fnstart
.LFB1606:
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
	movw	r3, #:lower16:98508	@ tmp144,
	movt	r3, #:upper16:98508	@ tmp144,
	mov	r4, r0	@ pSmInstArray, pSmInstArray
	ldr	ip, [r4, #196]	@ D.52758, <variable>.Config.MaxRawPacketSize
	ldr	r1, [r0, r3]	@ D.52741, <variable>.RawPacketArray.Tail
	subs	r6, r1, #1	@ LastPos, D.52741,
	addmi	r6, r6, #1024	@ LastPos, LastPos,
	subs	r0, r1, #2	@ PrePos, D.52741,
	addmi	r0, r0, #1024	@ PrePos, PrePos,
	add	r8, r6, r6, asl #1	@, tmp155, LastPos, LastPos,
	add	r5, r0, r0, asl #1	@, tmp148, PrePos, PrePos,
	mov	r8, r8, asl #5	@ tmp156, tmp155,
	add	r5, r4, r5, asl #5	@, tmp150, pSmInstArray, tmp148,
	add	r7, r8, r4	@ tmp157, tmp156, pSmInstArray
	ldr	r0, [r5, #208]	@ D.52755, <variable>.Length
	ldr	r3, [r7, #208]	@ D.52756, <variable>.Length
	add	r2, r3, r0	@ tmp159, D.52756, D.52755
	cmp	r2, ip	@ tmp159, D.52758
	bgt	.L665	@,
	ldr	lr, [r5, #204]	@ <variable>.VirAddr, <variable>.VirAddr
	mov	r2, r3	@, D.52756
	ldr	r1, [r7, #204]	@, <variable>.VirAddr
	add	r0, r0, lr	@, D.52755, <variable>.VirAddr
	bl	memcpy	@
	ldr	r0, [r7, #208]	@ <variable>.Length, <variable>.Length
	ldr	ip, [r5, #208]	@ <variable>.Length, <variable>.Length
	movw	r3, #:lower16:190856	@ tmp205,
	movt	r3, #:upper16:190856	@ tmp205,
	add	r1, r8, #200	@ tmp211, tmp156,
	add	r2, r0, ip	@ tmp204, <variable>.Length, <variable>.Length
	add	r1, r4, r1	@, pSmInstArray, tmp211
	str	r2, [r5, #208]	@ tmp204, <variable>.Length
	ldr	r0, [r4, r3]	@, <variable>.InstID
	bl	ReleaseRawStreamData	@
	movw	ip, #:lower16:98508	@ tmp213,
	movt	ip, #:upper16:98508	@ tmp213,
	mov	r0, #0	@ D.52769,
	str	r6, [r4, ip]	@ LastPos, <variable>.RawPacketArray.Tail
.L666:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L665:
	mov	r2, r0	@, D.52755
	movw	r1, #:lower16:.LC119	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC119	@,
	str	ip, [sp, #0]	@ D.52758,
	bl	dprint_vfmw	@
	mvn	r0, #6	@ D.52769,
	b	.L666	@
	.fnend
	.size	SM_MoveRawData, .-SM_MoveRawData
	.align	2
	.global	DeleteRawPacketInBuffer
	.type	DeleteRawPacketInBuffer, %function
DeleteRawPacketInBuffer:
	.fnstart
.LFB1542:
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
	cmp	r0, #15	@ SmID,
	mov	r4, r0	@ SmID, SmID
	bhi	.L688	@,
	add	r2, r0, r0, asl #1	@, tmp152, SmID, SmID,
	movw	r0, #:lower16:.LANCHOR0	@ tmp148,
	movt	r0, #:upper16:.LANCHOR0	@ tmp148,
	add	r3, r0, r2, asl #4	@, tmp154, tmp148, tmp152,
	ldr	r5, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r5, #0	@ pSmInstArray,
	beq	.L671	@,
	cmp	r1, #0	@ ResetFlag,
	bne	.L672	@,
	movw	ip, #:lower16:190872	@ tmp156,
	movt	ip, #:upper16:190872	@ tmp156,
	ldr	r1, [r5, ip]	@ <variable>.Mode, <variable>.Mode
	cmp	r1, #0	@ <variable>.Mode,
	bne	.L672	@,
.L671:
	mvn	r0, #0	@ D.49849,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L688:
	mov	r2, r0	@, SmID
	movw	r1, #:lower16:.LC120	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC120	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.49849,
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L672:
	movw	r6, #:lower16:98504	@ tmp158,
	movw	r3, #:lower16:98512	@ tmp159,
	movt	r6, #:upper16:98504	@ tmp158,
	movt	r3, #:upper16:98512	@ tmp159,
	ldr	sl, [r5, r6]	@ RawHead, <variable>.RawPacketArray.Head
	ldr	r6, [r5, r3]	@ D.49861, <variable>.RawPacketArray.History
	cmp	sl, r6	@ RawHead, D.49861
	addlt	sl, sl, #1024	@ tmp160, RawHead,
	rsb	sl, r6, sl	@ DelNum, D.49861, tmp160
	cmp	sl, #0	@ DelNum,
	beq	.L671	@,
	add	r8, r6, r6, asl #1	@, tmp164, D.49861, D.49861,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC63	@,
	movt	r1, #:upper16:.LC63	@,
	mov	r8, r8, asl #5	@ tmp165, tmp164,
	mov	r7, #1	@ i,
	add	lr, r8, r5	@ tmp166, tmp165, pSmInstArray
	sub	r9, sl, #1	@ tmp195, DelNum,
	and	r9, r9, #1	@ tmp197, tmp195,
	ldr	r2, [lr, #200]	@, <variable>.PhyAddr
	ldr	r3, [lr, #208]	@, <variable>.Length
	bl	dprint_vfmw	@
	add	r1, r8, #200	@ tmp181, tmp165,
	add	r1, r5, r1	@, pSmInstArray, tmp181
	mov	r0, r4	@, SmID
	bl	ReleaseRawStreamData	@
	add	r2, r6, r7	@ D.49875, D.49861,
	cmp	r7, sl	@ i, DelNum
	mov	r0, r2, asl #22	@ j, D.49875,
	mov	r6, r0, lsr #22	@ j, j,
	bcs	.L684	@,
	cmp	r9, #0	@ tmp197,
	beq	.L675	@,
	add	r3, r6, r6, asl #1	@, tmp228, j, j,
	movw	r1, #:lower16:.LC63	@,
	mov	r0, #26	@,
	movt	r1, #:upper16:.LC63	@,
	mov	r8, r3, asl #5	@ tmp229, tmp228,
	mov	r7, #2	@ i,
	b	.L686	@
.L675:
	add	lr, r6, r6, asl #1	@, tmp202, j, j,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC63	@,
	movt	r1, #:upper16:.LC63	@,
	mov	r8, lr, asl #5	@ tmp203, tmp202,
	add	r6, r6, #1	@ D.49875, j,
	add	r2, r8, r5	@ tmp204, tmp203, pSmInstArray
	add	r7, r7, #1	@ tmp198, i,
	add	r7, r7, #1	@ i, tmp198,
	ldr	r3, [r2, #208]	@, <variable>.Length
	ldr	r2, [r2, #200]	@, <variable>.PhyAddr
	bl	dprint_vfmw	@
	add	r0, r8, #200	@ tmp209, tmp203,
	add	r1, r5, r0	@, pSmInstArray, tmp209
	mov	r0, r4	@, SmID
	bl	ReleaseRawStreamData	@
	mov	r3, r6, asl #22	@ j, D.49875,
	movw	r1, #:lower16:.LC63	@,
	movt	r1, #:upper16:.LC63	@,
	mov	r6, r3, lsr #22	@ j, j,
	mov	r0, #26	@,
	add	ip, r6, r6, asl #1	@, tmp216, j, j,
	mov	r8, ip, asl #5	@ tmp217, tmp216,
.L686:
	add	lr, r8, r5	@ tmp230, tmp229, pSmInstArray
	ldr	r2, [lr, #200]	@, <variable>.PhyAddr
	ldr	r3, [lr, #208]	@, <variable>.Length
	bl	dprint_vfmw	@
	add	r2, r8, #200	@ tmp235, tmp229,
	add	r1, r5, r2	@, pSmInstArray, tmp235
	mov	r0, r4	@, SmID
	bl	ReleaseRawStreamData	@
	add	r0, r6, #1	@ D.49875, j,
	cmp	r7, sl	@ i, DelNum
	mov	r6, r0, asl #22	@ j, D.49875,
	mov	r6, r6, lsr #22	@ j, j,
	bcc	.L675	@,
.L684:
	movw	r1, #:lower16:98512	@ tmp184,
	movt	r1, #:upper16:98512	@ tmp184,
	mov	r0, #0	@ D.49849,
	ldr	ip, [r5, r1]	@ <variable>.RawPacketArray.History, <variable>.RawPacketArray.History
	add	sl, sl, ip	@ D.49877, DelNum, <variable>.RawPacketArray.History
	str	sl, [r5, r1]	@ D.49877, <variable>.RawPacketArray.History
	cmp	sl, #1024	@ D.49877,
	subge	sl, sl, #1024	@ tmp190, D.49877,
	strge	sl, [r5, r1]	@ tmp190, <variable>.RawPacketArray.History
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	.fnend
	.size	DeleteRawPacketInBuffer, .-DeleteRawPacketInBuffer
	.align	2
	.global	CutStreamWithSCD
	.type	CutStreamWithSCD, %function
CutStreamWithSCD:
	.fnstart
.LFB1583:
	@ args = 0, pretend = 0, frame = 192
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
	adds	r7, r0, #200	@ pRawStreamArray, pScdInstance,
	mov	r3, #0	@ tmp150,
	mov	r4, r0	@ pScdInstance, pScdInstance
	str	r3, [fp, #-56]	@ tmp150, SegBufSize
	mov	sl, r1	@ ScdId, ScdId
	ldr	r6, [r0, #56]	@ StdType, <variable>.Config.VidStd
	ldr	r8, [r0, #88]	@ D.51187, <variable>.Config.ScdLowdlyEnable
	bne	.L710	@,
.L690:
	mvn	r5, #0	@ Ret,
.L697:
	mov	r0, r5	@, Ret
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L710:
	add	r5, r0, #98304	@ pStreamSegArray, pScdInstance,
	add	r5, r5, #224	@ pStreamSegArray, pStreamSegArray,
	cmp	r5, r3	@ pStreamSegArray,
	beq	.L690	@,
	add	lr, r0, #190464	@, pScdInstance,
	mov	r1, #12	@,
	add	r0, lr, #280	@,,
	str	r3, [fp, #-52]	@ tmp150, FreeSegBufAddr
	str	r3, [fp, #-48]	@ tmp150, SegStreamSize
	bl	__memzero	@
	movw	r3, #:lower16:98508	@ tmp156,
	movw	ip, #:lower16:98504	@ tmp157,
	movt	r3, #:upper16:98508	@ tmp156,
	movt	ip, #:upper16:98504	@ tmp157,
	mov	r0, #26	@,
	ldr	r1, [r4, ip]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Head
	ldr	r9, [r4, r3]	@ <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Tail
	subs	r9, r9, r1	@ StreamNum, <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Head
	movw	r1, #:lower16:.LC121	@,
	addmi	r9, r9, #1024	@ StreamNum, StreamNum,
	movt	r1, #:upper16:.LC121	@,
	mov	r2, r9	@, StreamNum
	bl	dprint_vfmw	@
	movw	r2, #:lower16:98524	@ tmp161,
	movw	r0, #:lower16:98516	@ tmp162,
	movt	r2, #:upper16:98524	@ tmp161,
	movt	r0, #:upper16:98516	@ tmp162,
	ldr	ip, [r4, r2]	@ <variable>.RawPacketArray.RawTotalSize, <variable>.RawPacketArray.RawTotalSize
	ldr	r3, [r4, r0]	@ <variable>.RawPacketArray.FirstPacketOffset, <variable>.RawPacketArray.FirstPacketOffset
	subs	ip, ip, r3	@ RawStreamSize, <variable>.RawPacketArray.RawTotalSize, <variable>.RawPacketArray.FirstPacketOffset
	bmi	.L690	@,
	mov	r2, ip	@, RawStreamSize
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC125	@,
	movt	r1, #:upper16:.LC125	@,
	str	ip, [fp, #-224]	@,
	bl	dprint_vfmw	@
	cmp	r9, #0	@ StreamNum,
	ldr	ip, [fp, #-224]	@,
	bgt	.L711	@,
.L693:
	mvn	r5, #4	@ Ret,
	b	.L697	@
.L711:
	cmp	ip, #3	@ RawStreamSize,
	ble	.L693	@,
	movw	r3, #:lower16:190700	@ tmp165,
	movw	r1, #:lower16:190696	@ tmp166,
	movt	r3, #:upper16:190700	@ tmp165,
	movt	r1, #:upper16:190696	@ tmp166,
	ldr	r9, [r4, r3]	@ <variable>.StreamSegArray.Tail, <variable>.StreamSegArray.Tail
	ldr	r2, [r4, r1]	@ <variable>.StreamSegArray.Head, <variable>.StreamSegArray.Head
	movw	r1, #:lower16:.LC122	@,
	movt	r1, #:upper16:.LC122	@,
	str	ip, [fp, #-224]	@,
	subs	r0, r9, r2	@ StreamNum.2788, <variable>.StreamSegArray.Tail, <variable>.StreamSegArray.Head
	addmi	r0, r0, #1152	@ StreamNum.2788, StreamNum.2788,
	rsb	r9, r0, #1152	@ StreamNum.559, StreamNum.2788,
	mov	r0, #26	@,
	mov	r2, r9	@, StreamNum.559
	bl	dprint_vfmw	@
	cmp	r9, #288	@ StreamNum.559,
	bgt	.L712	@,
.L695:
	mvn	r5, #5	@ Ret,
	b	.L697	@
.L712:
	mov	r0, r5	@, pStreamSegArray
	sub	r1, fp, #52	@,,
	sub	r2, fp, #48	@,,
	bl	GetFreeSegBuf	@
	ldr	r1, [fp, #-48]	@ SegStreamSize, SegStreamSize
	ldr	r2, [fp, #-52]	@ FreeSegBufAddr, FreeSegBufAddr
	mov	r0, #26	@,
	sub	lr, r1, #79	@ SegStreamSize.564, SegStreamSize,
	movw	r1, #:lower16:.LC123	@,
	add	r5, r2, #3	@ tmp172, FreeSegBufAddr,
	movt	r1, #:upper16:.LC123	@,
	mov	r2, lr	@, SegStreamSize.564
	bic	r3, r5, #3	@ tmp174, tmp172,
	str	lr, [fp, #-48]	@ SegStreamSize.564, SegStreamSize
	str	r3, [fp, #-52]	@ tmp174, FreeSegBufAddr
	bl	dprint_vfmw	@
	movw	ip, #:lower16:190716	@ tmp177,
	movt	ip, #:upper16:190716	@ tmp177,
	ldr	r5, [fp, #-48]	@ SegStreamSize, SegStreamSize
	ldr	r3, [r4, ip]	@ D.51225, <variable>.StreamSegArray.SegBufSize
	cmp	r5, r3, asr #3	@ SegStreamSize, D.51225,
	ble	.L695	@,
	movw	r5, #:lower16:190856	@ tmp182,
	movw	lr, #:lower16:190712	@ tmp180,
	movt	r5, #:upper16:190856	@ tmp182,
	movt	lr, #:upper16:190712	@ tmp180,
	mov	r1, sl	@, ScdId
	ldr	r0, [r4, r5]	@, <variable>.InstID
	str	r3, [fp, #-56]	@ D.51225,
	ldr	ip, [r4, lr]	@, <variable>.StreamSegArray.SegBufPhyAddr
	str	ip, [fp, #-184]	@, %sfp
	bl	SM_CfgBuf	@
	ldr	ip, [fp, #-224]	@,
	subs	r5, r0, #0	@ Ret,
	bne	.L713	@,
	movw	r1, #:lower16:204748	@ tmp188,
	movt	r1, #:upper16:204748	@ tmp188,
	movw	lr, #:lower16:190760	@ tmp194,
	movt	lr, #:upper16:190760	@ tmp194,
	ldr	r2, [r4, r1]	@ <variable>.UpMsgStepNum, <variable>.UpMsgStepNum
	movw	r0, #:lower16:190764	@ tmp196,
	movt	r0, #:upper16:190764	@ tmp196,
	movw	r1, #:lower16:190772	@ tmp198,
	movt	r1, #:upper16:190772	@ tmp198,
	mov	r3, r2, asl #2	@, <variable>.UpMsgStepNum,
	str	r3, [fp, #-176]	@, %sfp
	movw	r3, #:lower16:190788	@,
	movt	r3, #:upper16:190788	@,
	str	r3, [fp, #-208]	@, %sfp
	mul	r3, r2, r9	@, <variable>.UpMsgStepNum, StreamNum.559
	ldr	r2, [fp, #-176]	@, %sfp
	mul	r2, r9, r2	@, StreamNum.559,
	str	r3, [fp, #-204]	@, %sfp
	movw	r3, #:lower16:190800	@ tmp212,
	movt	r3, #:upper16:190800	@ tmp212,
	str	r2, [fp, #-188]	@, %sfp
	movw	r2, #:lower16:190812	@,
	movt	r2, #:upper16:190812	@,
	str	r2, [fp, #-176]	@, %sfp
	movw	r2, #:lower16:190824	@,
	movt	r2, #:upper16:190824	@,
	str	r2, [fp, #-180]	@, %sfp
	cmp	r6, #6	@ StdType,
	movne	r2, #0	@,
	moveq	r2, #1	@,
	ldr	lr, [r4, lr]	@, <variable>.BufAddrCfg.DownMsgPhyAddr
	cmp	r6, #1	@ StdType,
	cmpne	r6, #15	@, StdType,
	str	r2, [fp, #-220]	@, %sfp
	moveq	r6, r5	@ prephitmp.2767, Ret
	str	lr, [fp, #-192]	@, %sfp
	ldr	r0, [r4, r0]	@, <variable>.BufAddrCfg.pDownMsgVirAddr
	ldr	lr, [fp, #-208]	@, %sfp
	str	r0, [fp, #-196]	@, %sfp
	ldr	r1, [r4, r1]	@, <variable>.BufAddrCfg.UpMsgPhyAddr
	ldr	r0, [fp, #-176]	@, %sfp
	str	r1, [fp, #-200]	@, %sfp
	movw	r1, #:lower16:190864	@ tmp184,
	ldr	r2, [r4, lr]	@, <variable>.BufAddrCfg.DspSpsMsgMemAddr
	movt	r1, #:upper16:190864	@ tmp184,
	str	r2, [fp, #-208]	@, %sfp
	ldr	r3, [r4, r3]	@, <variable>.BufAddrCfg.DspPpsMsgMemAddr
	ldr	r2, [fp, #-180]	@, %sfp
	str	r3, [fp, #-212]	@, %sfp
	movw	r3, #:lower16:190784	@ tmp186,
	ldr	lr, [r4, r0]	@, <variable>.BufAddrCfg.DvmMemAddr
	movt	r3, #:upper16:190784	@ tmp186,
	str	lr, [fp, #-216]	@, %sfp
	ldr	lr, [fp, #-52]	@, FreeSegBufAddr
	ldr	r0, [r4, r2]	@, <variable>.BufAddrCfg.DspSedTopMemAddr
	ldr	r2, [fp, #-56]	@, SegBufSize
	str	lr, [fp, #-176]	@, %sfp
	ldr	lr, [fp, #-188]	@, %sfp
	str	r0, [fp, #-180]	@, %sfp
	movw	r0, #:lower16:190780	@ tmp187,
	movt	r0, #:upper16:190780	@ tmp187,
	str	r2, [fp, #-232]	@, %sfp
	mov	r2, #1	@ tmp185,
	str	lr, [r4, r0]	@, <variable>.BufAddrCfg.UpMsgSize
	ldr	lr, [fp, #-232]	@, %sfp
	ldr	r0, [fp, #-184]	@, %sfp
	add	r0, r0, lr	@,,
	str	r0, [fp, #-188]	@, %sfp
	str	r2, [r4, r1]	@ tmp185, <variable>.CutingFlag
	str	r9, [r4, r3]	@ StreamNum.559, <variable>.BufAddrCfg.UpMsgNum
	ldr	lr, [fp, #-192]	@, %sfp
	ldr	r1, [fp, #-196]	@, %sfp
	ldr	r3, [fp, #-200]	@, %sfp
	ldr	r0, [fp, #-204]	@, %sfp
	str	lr, [fp, #-164]	@, ScdCtrlReg.DownMsgPhyAddr
	str	r1, [fp, #-160]	@, ScdCtrlReg.pDownMsgVirAddr
	ldr	lr, [fp, #-188]	@, %sfp
	ldr	r1, [fp, #-176]	@, %sfp
	str	r3, [fp, #-156]	@, ScdCtrlReg.UpMsgPhyAddr
	str	r0, [fp, #-148]	@, ScdCtrlReg.UpLen
	ldr	r3, [fp, #-208]	@, %sfp
	ldr	r0, [fp, #-212]	@, %sfp
	str	lr, [fp, #-140]	@, ScdCtrlReg.BufferLast
	str	r1, [fp, #-136]	@, ScdCtrlReg.BufferIni
	str	r3, [fp, #-124]	@, ScdCtrlReg.DspSpsMsgMemAddr
	str	r0, [fp, #-112]	@, ScdCtrlReg.DspPpsMsgMemAddr
	ldr	lr, [fp, #-216]	@, %sfp
	ldr	r1, [fp, #-180]	@, %sfp
	ldr	r3, [fp, #-220]	@, %sfp
	ldr	r0, [fp, #-184]	@, %sfp
	str	r8, [fp, #-64]	@ D.51187, ScdCtrlReg.ScdLowdlyEnable
	str	lr, [fp, #-100]	@, ScdCtrlReg.DvmMemAddr
	str	r1, [fp, #-88]	@, ScdCtrlReg.DspSedTopMemAddr
	str	r3, [fp, #-60]	@, ScdCtrlReg.reg_avs_flag
	strb	r2, [fp, #-166]	@ tmp185, ScdCtrlReg.ScdStart
	str	r0, [fp, #-144]	@, ScdCtrlReg.BufferFirst
	strb	r2, [fp, #-168]	@ tmp185, ScdCtrlReg.ScdIntMask
	beq	.L702	@,
	cmp	r6, #6	@ StdType,
	beq	.L709	@,
	sub	r5, r6, #2	@ tmp228, StdType,
	cmp	r5, #1	@ tmp228,
	bls	.L709	@,
.L702:
	mov	r0, #0	@ tmp231,
	strb	r0, [fp, #-167]	@ tmp231, ScdCtrlReg.SliceCheckFlag
.L700:
	movw	r1, #:lower16:190764	@ tmp237,
	movw	r3, #:lower16:190760	@ tmp239,
	movt	r1, #:upper16:190764	@ tmp237,
	movt	r3, #:upper16:190760	@ tmp239,
	add	r2, r4, #190464	@, pScdInstance,
	sub	r0, fp, #168	@,,
	ldr	r5, [r4, r3]	@ <variable>.BufAddrCfg.DownMsgPhyAddr, <variable>.BufAddrCfg.DownMsgPhyAddr
	mov	r3, r7	@, pRawStreamArray
	ldr	lr, [r4, r1]	@ <variable>.BufAddrCfg.pDownMsgVirAddr, <variable>.BufAddrCfg.pDownMsgVirAddr
	add	r1, r2, #280	@,,
	ldr	r2, [fp, #-48]	@, SegStreamSize
	mov	r7, #1	@ tmp233,
	str	r5, [sp, #4]	@ <variable>.BufAddrCfg.DownMsgPhyAddr,
	str	ip, [fp, #-224]	@,
	str	r6, [fp, #-132]	@ prephitmp.2767, ScdCtrlReg.ScdProtocol
	str	lr, [sp, #0]	@ <variable>.BufAddrCfg.pDownMsgVirAddr,
	str	sl, [sp, #8]	@ ScdId,
	str	r7, [fp, #-128]	@ tmp233, ScdCtrlReg.ScdIniClr
	bl	ScdDriver	@
	ldr	ip, [fp, #-224]	@,
	subs	r5, r0, #0	@ Ret,
	bne	.L697	@,
	ldr	r6, [fp, #-48]	@ SegStreamSize, SegStreamSize
	movw	lr, #:lower16:204720	@ tmp243,
	movw	r0, #:lower16:204724	@ tmp244,
	movt	lr, #:upper16:204720	@ tmp243,
	movt	r0, #:upper16:204724	@ tmp244,
	cmp	r6, ip	@ SegStreamSize, RawStreamSize
	str	ip, [r4, lr]	@ RawStreamSize, <variable>.PrevCfgRawSize
	str	r6, [r4, r0]	@ SegStreamSize, <variable>.PrevCfgSegSize
	mov	r6, #0	@ tmp251,
	strb	r7, [r4, #5]	@ tmp233, <variable>.IsWaitSCD
	strgeb	r7, [r4, #2]	@ tmp233, <variable>.LastCfgAllRawFlag
	strltb	r5, [r4, #2]	@ Ret, <variable>.LastCfgAllRawFlag
	strb	r6, [r4, #4]	@ tmp251, <variable>.FillNewRawFlag
	bl	OSAL_GetTimeInMs	@
	movw	ip, #:lower16:204744	@ tmp253,
	movt	ip, #:upper16:204744	@ tmp253,
	strb	r6, [r4, #3]	@ tmp251, <variable>.InsertNewSegFlag
	str	r0, [r4, ip]	@, <variable>.LastSCDStartTime
	b	.L697	@
.L713:
	movw	r1, #:lower16:.LC124	@,
	mov	r2, r5	@, Ret
	movt	r1, #:upper16:.LC124	@,
	mov	r0, #26	@,
	bl	dprint_vfmw	@
	b	.L697	@
.L709:
	strb	r2, [fp, #-167]	@ tmp185, ScdCtrlReg.SliceCheckFlag
	b	.L700	@
	.fnend
	.size	CutStreamWithSCD, .-CutStreamWithSCD
	.align	2
	.global	SM_CloseSCDDrv
	.type	SM_CloseSCDDrv, %function
SM_CloseSCDDrv:
	.fnstart
.LFB1569:
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
	movw	ip, #:lower16:.LANCHOR0	@ tmp180,
	movt	ip, #:upper16:.LANCHOR0	@ tmp180,
	movw	r3, #:lower16:190872	@ tmp181,
	movw	r1, #:lower16:190860	@ tmp182,
	mov	r5, r0	@ ScdId, ScdId
	movt	r3, #:upper16:190872	@ tmp181,
	movt	r1, #:upper16:190860	@ tmp182,
	add	r2, ip, #768	@ D.55964, tmp180,
	mov	r0, ip	@ ivtmp.2828, tmp180
	mov	r6, #0	@ tmp183,
	b	.L717	@
.L715:
	add	r0, r0, #48	@ ivtmp.2828, ivtmp.2828,
	cmp	r0, r2	@ ivtmp.2828, D.55964
	beq	.L726	@,
.L717:
	ldr	lr, [r0, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	lr, #0	@ pSmInstArray,
	beq	.L715	@,
	ldr	r4, [lr, r3]	@ <variable>.Mode, <variable>.Mode
	cmp	r4, #0	@ <variable>.Mode,
	beq	.L715	@,
	ldr	r4, [lr, r1]	@ <variable>.ScdID, <variable>.ScdID
	cmp	r4, #0	@ <variable>.ScdID,
	bgt	.L715	@,
	add	r4, r4, r4, asl #1	@, tmp160, <variable>.ScdID, <variable>.ScdID,
	str	r6, [lr, r3]	@ tmp183, <variable>.Mode
	add	r4, ip, r4, asl #5	@, tmp162, tmp180, tmp160,
	ldr	lr, [r4, #856]	@ <variable>.SCDState, <variable>.SCDState
	cmp	lr, #0	@ <variable>.SCDState,
	beq	.L715	@,
	mov	lr, #2	@ i,
.L716:
	add	lr, lr, #2	@ i, i,
	cmp	lr, #50	@ i,
	bne	.L716	@,
	add	r0, r0, #48	@ ivtmp.2828, ivtmp.2828,
	cmp	r0, r2	@ ivtmp.2828, D.55964
	bne	.L717	@,
.L726:
	mov	r0, r5	@, ScdId
	mov	r4, #0	@ tmp171,
	bl	ResetSCD	@
	movw	r1, #:lower16:g_VfmwGlobalStat	@ tmp165,
	movt	r1, #:upper16:g_VfmwGlobalStat	@ tmp165,
	mov	r2, #84	@ tmp168,
	add	r0, r5, r5, asl #1	@, tmp176, ScdId, ScdId,
	ldr	r3, .L727	@ tmp173,
	mla	r5, r2, r5, r1	@ tmp169, tmp168, ScdId, tmp165
	add	r0, r3, r0, asl #5	@,, tmp173, tmp176,
	mov	r1, #96	@,
	str	r4, [r5, #76]	@ tmp171, <variable>.u32SaScdLoad
	bl	__memzero	@
	mov	r0, r4	@, tmp171
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L728:
	.align	2
.L727:
	.word	.LANCHOR0+772
	.fnend
	.size	SM_CloseSCDDrv, .-SM_CloseSCDDrv
	.align	2
	.global	SM_InstInit
	.type	SM_InstInit, %function
SM_InstInit:
	.fnstart
.LFB1567:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp133,
	movt	r4, #:upper16:.LANCHOR0	@ tmp133,
	mov	r1, #48	@,
	mov	r0, r4	@, tmp133
	bl	__memzero	@
	add	r0, r4, #48	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #96	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #144	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #192	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #240	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #288	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #336	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #384	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #432	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #480	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #528	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #576	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #624	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #672	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	add	r0, r4, #720	@, tmp133,
	mov	r1, #48	@,
	bl	__memzero	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	SM_InstInit, .-SM_InstInit
	.align	2
	.global	SM_ClearInst
	.type	SM_ClearInst, %function
SM_ClearInst:
	.fnstart
.LFB1564:
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
	cmp	r0, #15	@ SmID,
	mvnhi	r0, #0	@ D.50377,
	ldmhifd	sp, {r4, r5, fp, sp, pc}	@
	add	r0, r0, r0, asl #1	@, tmp140, SmID, SmID,
	movw	r5, #:lower16:.LANCHOR0	@ tmp136,
	movt	r5, #:upper16:.LANCHOR0	@ tmp136,
	movw	r1, #:lower16:204896	@,
	add	r4, r5, r0, asl #4	@, tmp142, tmp136, tmp140,
	movt	r1, #:upper16:204896	@,
	mvn	r5, #0	@,
	ldr	r0, [r4, #40]	@, <variable>.pSmInstArray
	bl	__memzero	@
	ldr	r2, [r4, #40]	@ <variable>.pSmInstArray, <variable>.pSmInstArray
	movw	r3, #:lower16:204712	@ tmp155,
	movt	r3, #:upper16:204712	@ tmp155,
	mvn	r4, #0	@ tmp156,
	mov	r0, #0	@ D.50377,
	strd	r4, [r2, r3]	@ tmp156, <variable>.pSmInstArray, tmp155
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	SM_ClearInst, .-SM_ClearInst
	.align	2
	.global	ResetStreamSegArray
	.type	ResetStreamSegArray, %function
ResetStreamSegArray:
	.fnstart
.LFB1550:
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
	subs	r4, r0, #0	@ pStreamSegArray, pStreamSegArray
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	add	r0, r4, #8	@, pStreamSegArray,
	mov	r1, #92160	@,
	bl	__memzero	@
	movw	r0, #:lower16:92184	@ tmp142,
	movt	r0, #:upper16:92184	@ tmp142,
	movw	r1, #:lower16:92168	@ tmp135,
	movw	r3, #:lower16:92172	@ tmp137,
	movt	r1, #:upper16:92168	@ tmp135,
	ldr	r5, [r4, r0]	@ <variable>.SegBufPhyAddr, <variable>.SegBufPhyAddr
	movt	r3, #:upper16:92172	@ tmp137,
	movw	r0, #:lower16:92176	@ tmp139,
	movw	r2, #:lower16:92192	@ tmp141,
	movt	r0, #:upper16:92176	@ tmp139,
	movt	r2, #:upper16:92192	@ tmp141,
	movw	ip, #:lower16:92196	@ tmp144,
	movt	ip, #:upper16:92196	@ tmp144,
	str	r5, [r4, r2]	@ <variable>.SegBufPhyAddr, <variable>.SegBufReadAddr
	mov	r2, #0	@ tmp136,
	str	r5, [r4, ip]	@ <variable>.SegBufPhyAddr, <variable>.SegBufWriteAddr
	str	r2, [r4, r0]	@ tmp136, <variable>.History
	str	r2, [r4, r1]	@ tmp136, <variable>.Head
	str	r2, [r4, r3]	@ tmp136, <variable>.Tail
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	ResetStreamSegArray, .-ResetStreamSegArray
	.align	2
	.global	SM_CopyYuvToDnr
	.type	SM_CopyYuvToDnr, %function
SM_CopyYuvToDnr:
	.fnstart
.LFB1577:
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
	add	r0, r0, r0, asl #1	@, tmp152, SmID, SmID,
	movw	r1, #:lower16:.LANCHOR0	@ tmp148,
	movt	r1, #:upper16:.LANCHOR0	@ tmp148,
	add	r3, r1, r0, asl #4	@, tmp154, tmp148, tmp152,
	ldr	r4, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r4, #0	@ pSmInstArray,
	mvneq	r0, #0	@ D.50980,
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	movw	r3, #:lower16:98504	@ tmp156,
	movw	ip, #:lower16:98508	@ tmp157,
	movt	r3, #:upper16:98504	@ tmp156,
	movt	ip, #:upper16:98508	@ tmp157,
	ldr	r5, [r4, r3]	@ D.50987, <variable>.RawPacketArray.Head
	ldr	r2, [r4, ip]	@ <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Tail
	cmp	r2, r5	@ <variable>.RawPacketArray.Tail, D.50987
	mvneq	r0, #3	@ D.50980,
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	add	r7, r4, #98304	@, pSmInstArray,
	mov	r6, r5, asl #1	@ tmp221, D.50987,
	add	r0, r7, #224	@,,
	add	r7, r4, #200	@ pRawPacketArray, pSmInstArray,
	bl	ResetStreamSegArray	@
	add	r0, r6, r5	@ tmp164, tmp221, D.50987
	add	r1, r4, r0, asl #5	@, tmp166, pSmInstArray, tmp164,
	ldr	r3, [r1, #204]	@ pu32tmp, <variable>.VirAddr
	ldmia	r3, {r0, r2}	@ phole ldm
	sub	ip, r0, #32	@ tmp170, D.50995,
	cmp	ip, #1888	@ tmp170,
	movls	ip, #0	@, tmp172
	movhi	ip, #1	@, tmp172
	cmp	r2, #31	@ h,
	orrle	ip, ip, #1	@,, tmp175, tmp172
	cmp	ip, #0	@ tmp175,
	bne	.L742	@,
	cmp	r2, #1088	@ h,
	bgt	.L742	@,
	ldr	r1, [r1, #208]	@ D.51007, <variable>.Length
	cmp	r1, #1552	@ D.51007,
	blt	.L742	@,
	movw	lr, #:lower16:3133456	@ tmp184,
	movt	lr, #:upper16:3133456	@ tmp184,
	cmp	r1, lr	@ D.51007, tmp184
	bgt	.L742	@,
	mov	lr, #3	@ tmp186,
	movw	ip, #:lower16:190716	@ tmp188,
	mul	r0, lr, r0	@ tmp185, tmp186, D.50995
	movt	ip, #:upper16:190716	@ tmp188,
	ldr	lr, [r4, ip]	@ <variable>.StreamSegArray.SegBufSize, <variable>.StreamSegArray.SegBufSize
	sub	ip, lr, #262144	@ tmp189, <variable>.StreamSegArray.SegBufSize,
	mul	r2, r2, r0	@ tmp187, h, tmp185
	mov	r2, r2, asr #1	@ D.51012, tmp187,
	cmp	r2, ip	@ D.51012, tmp189
	bgt	.L742	@,
	add	r2, r2, #16	@ tmp191, D.51012,
	cmp	r1, r2	@ D.51007, tmp191
	blt	.L742	@,
	ldr	r2, [r3, #8]	@ tmp205,
	movw	lr, #1916	@ tmp207,
	ldr	r3, [r3, #12]	@ disp_h,
	sub	r0, r2, #4	@ tmp204, tmp205,
	cmp	r0, lr	@ tmp204, tmp207
	movls	ip, #0	@, tmp208
	movhi	ip, #1	@, tmp208
	cmp	r3, #3	@ disp_h,
	orrle	ip, ip, #1	@,, tmp211, tmp208
	cmp	ip, #0	@ tmp211,
	bne	.L745	@,
	cmp	r3, #1088	@ disp_h,
	ble	.L746	@,
.L745:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC128	@,
	movt	r1, #:upper16:.LC128	@,
	bl	dprint_vfmw	@
	mov	r1, #96	@ tmp215,
	mla	r4, r1, r5, r4	@ tmp216, tmp215, D.50987, pSmInstArray
	mov	r0, r7	@, pRawPacketArray
	ldr	r1, [r4, #208]	@, <variable>.Length
	bl	DeleteRawLen	@
	cmp	r0, #0	@,
	bne	.L748	@,
.L744:
	mov	r0, #0	@ D.50980,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L742:
	add	r5, r6, r5	@ tmp196, tmp221, D.50987
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC126	@,
	movt	r1, #:upper16:.LC126	@,
	add	r4, r4, r5, asl #5	@, tmp198, pSmInstArray, tmp196,
	bl	dprint_vfmw	@
	mov	r0, r7	@, pRawPacketArray
	ldr	r1, [r4, #208]	@, <variable>.Length
	bl	DeleteRawLen	@
	cmp	r0, #0	@,
	beq	.L744	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC127	@,
	movw	r2, #2503	@,
	movt	r1, #:upper16:.LC127	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.50980,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L746:
	mov	r0, r7	@, pRawPacketArray
	bl	DeleteRawLen	@
	mov	r0, #0	@ D.50980,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L748:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC127	@,
	movw	r2, #2514	@,
	movt	r1, #:upper16:.LC127	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.50980,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	SM_CopyYuvToDnr, .-SM_CopyYuvToDnr
	.align	2
	.global	SM_DoNextInstance
	.type	SM_DoNextInstance, %function
SM_DoNextInstance:
	.fnstart
.LFB1607:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #68
	sub	sp, sp, #68	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #0	@ ScdId
	mov	r3, #0	@ tmp156,
	str	r1, [fp, #-108]	@ pNextInstId, %sfp
	str	r3, [fp, #-52]	@ tmp156, SegBufAddr
	str	r3, [fp, #-48]	@ tmp156, SegBufTotalSize
	bne	.L770	@,
	movw	r9, #:lower16:.LANCHOR0	@ tmp269,
	movt	r9, #:upper16:.LANCHOR0	@ tmp269,
	ldr	r3, [r9, #768]	@ D.52799, s_eScdDrvSleepStage
	cmp	r3, #0	@ D.52799,
	bne	.L771	@,
	ldr	r5, [r9, #852]	@ NextInstId, <variable>.ThisInstID
	movw	r8, #:lower16:190864	@ tmp272,
	str	r3, [fp, #-84]	@ D.52799, %sfp
	movw	r7, #:lower16:204744	@ tmp273,
	ldr	r2, [fp, #-84]	@, %sfp
	movw	r6, #:lower16:190736	@,
	movw	r4, #:lower16:190732	@,
	movt	r6, #:upper16:190736	@,
	movt	r4, #:upper16:190732	@,
	str	r6, [fp, #-88]	@, %sfp
	movw	r1, #:lower16:190712	@,
	movw	r0, #:lower16:190716	@,
	movt	r1, #:upper16:190712	@,
	movt	r0, #:upper16:190716	@,
	movt	r8, #:upper16:190864	@ tmp272,
	movt	r7, #:upper16:204744	@ tmp273,
	str	r4, [fp, #-92]	@, %sfp
	mov	r6, r2	@ i,
	str	r1, [fp, #-96]	@, %sfp
	str	r0, [fp, #-100]	@, %sfp
	str	r2, [fp, #-104]	@, %sfp
	b	.L767	@
.L755:
	cmp	r3, #11	@ D.52815,
	beq	.L754	@,
	cmp	r3, #14	@ D.52815,
	beq	.L754	@,
	cmp	r3, #4	@ D.52815,
	beq	.L754	@,
	cmp	r3, #12	@ D.52815,
	beq	.L754	@,
	cmp	r3, #10	@ D.52815,
	beq	.L754	@,
	cmp	r3, #13	@ D.52815,
	beq	.L754	@,
	cmp	r3, #18	@ D.52815,
	beq	.L754	@,
	cmp	r3, #17	@ D.52815,
	beq	.L772	@,
.L757:
	mov	r1, #0	@,
	mov	r0, r5	@, NextInstId
	bl	PrintScdRawState	@
	mov	r0, r5	@, NextInstId
	mov	r1, #0	@,
	bl	PrintScdSegState	@
	bl	OSAL_GetTimeInMs	@
	ldr	r2, [r4, r7]	@ <variable>.LastSCDStartTime, <variable>.LastSCDStartTime
	ldrsb	r3, [r4, #2]	@ <variable>.LastCfgAllRawFlag, <variable>.LastCfgAllRawFlag
	subs	r2, r0, r2	@ WaitTime, CurTimeInMs, <variable>.LastSCDStartTime
	strmi	r0, [r4, r7]	@ CurTimeInMs, <variable>.LastSCDStartTime
	movmi	r2, #200	@ WaitTime,
	cmp	r3, #1	@ <variable>.LastCfgAllRawFlag,
	beq	.L773	@,
	ldrsb	lr, [r4, #0]	@ <variable>.SegFullFlag, <variable>.SegFullFlag
	str	r0, [r4, r7]	@ CurTimeInMs, <variable>.LastSCDStartTime
	cmp	lr, #1	@ <variable>.SegFullFlag,
	movne	lr, #0	@ tmp232,
	strneb	lr, [r4, #1]	@ tmp232, <variable>.IsCounting
	beq	.L774	@,
.L763:
	mov	r0, r4	@, pSmInstArray
	mov	r1, #0	@,
	bl	CutStreamWithSCD	@
	cmn	r0, #6	@ Ret,
	moveq	r3, #1	@ tmp234,
	streqb	r3, [r4, #0]	@ tmp234, <variable>.SegFullFlag
	beq	.L754	@,
	cmp	r0, #0	@ Ret,
	mov	r3, #0	@ tmp236,
	strb	r3, [r4, #0]	@ tmp236, <variable>.SegFullFlag
	beq	.L775	@,
.L754:
	add	r6, r6, #1	@ i, i,
	cmp	r6, #16	@ i,
	beq	.L753	@,
.L767:
	add	r0, r5, #1	@ D.52804, NextInstId,
	sub	r1, fp, #76	@,,
	mov	r4, r0, asr #31	@ tmp163, D.52804,
	mov	sl, r4, lsr #28	@ tmp164, tmp163,
	add	r2, r0, sl	@ tmp165, D.52804, tmp164
	and	r5, r2, #15	@ tmp166, tmp165,
	rsb	r5, sl, r5	@ NextInstId, tmp164, tmp166
	mov	sl, r5, asl #1	@ tmp270, NextInstId,
	mov	r0, r5	@, NextInstId
	add	r3, sl, r5	@ tmp172, tmp270, NextInstId
	add	lr, r9, r3, asl #4	@, tmp174, tmp269, tmp172,
	ldr	r4, [lr, #40]	@ pSmInstArray, <variable>.pSmInstArray
	bl	SM_GetInfo	@
	ldrsb	ip, [fp, #-76]	@ stInstInfo.InstMode, stInstInfo.InstMode
	cmp	ip, #0	@ stInstInfo.InstMode,
	beq	.L754	@,
	ldr	r1, [r4, r8]	@ <variable>.CutingFlag, <variable>.CutingFlag
	cmp	r1, #1	@ <variable>.CutingFlag,
	beq	.L754	@,
	ldr	r3, [r4, #56]	@ D.52815, <variable>.Config.VidStd
	sub	ip, r3, #8	@ tmp180, D.52815,
	cmp	r3, #5	@ D.52815,
	cmpne	ip, #1	@, tmp180,
	bls	.L754	@,
	cmp	r3, #1	@ D.52815,
	bne	.L755	@,
	ldr	lr, [r4, #72]	@ <variable>.Config.StdExt.Vc1Ext.IsAdvProfile, <variable>.Config.StdExt.Vc1Ext.IsAdvProfile
	cmp	lr, #0	@ <variable>.Config.StdExt.Vc1Ext.IsAdvProfile,
	bne	.L757	@,
	b	.L754	@
.L771:
	cmp	r3, #1	@ D.52799,
	moveq	r3, #2	@ tmp161,
	mvneq	r0, #2	@ D.52797,
	streq	r3, [r9, #768]	@ tmp161, s_eScdDrvSleepStage
	beq	.L751	@,
.L753:
	mvn	r0, #2	@ D.52797,
.L751:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L773:
	ldrsb	ip, [r4, #4]	@ <variable>.FillNewRawFlag, <variable>.FillNewRawFlag
	cmp	r2, #500	@ WaitTime,
	movge	r1, #0	@, tmp202
	movlt	r1, #1	@, tmp202
	cmp	ip, #0	@ <variable>.FillNewRawFlag,
	movne	r1, #0	@, tmp202,
	cmp	r1, #0	@ tmp202,
	bne	.L754	@,
	ldrsb	lr, [r4, #0]	@ <variable>.SegFullFlag, <variable>.SegFullFlag
	str	r0, [r4, r7]	@ CurTimeInMs, <variable>.LastSCDStartTime
	cmp	lr, #1	@ <variable>.SegFullFlag,
	movne	lr, #0	@ tmp232,
	strneb	lr, [r4, #1]	@ tmp232, <variable>.IsCounting
	bne	.L763	@,
.L774:
	mov	r1, #0	@,
	mov	r0, r5	@, NextInstId
	add	ip, r4, #98304	@, pSmInstArray,
	str	ip, [fp, #-80]	@, %sfp
	bl	PrintScdRawState	@
	ldr	r2, [fp, #-80]	@, %sfp
	mov	r0, r5	@, NextInstId
	mov	r1, #0	@,
	add	r3, r2, #224	@,,
	str	r3, [fp, #-80]	@, %sfp
	bl	PrintScdSegState	@
	ldr	r0, [fp, #-80]	@, %sfp
	cmp	r0, #0	@,
	beq	.L761	@,
	ldr	r1, [fp, #-88]	@, %sfp
	ldr	lr, [fp, #-96]	@, %sfp
	ldr	r2, [fp, #-92]	@, %sfp
	ldr	ip, [r4, r1]	@, <variable>.StreamSegArray.SegFreshNum
	ldr	r0, [r4, lr]	@ <variable>.StreamSegArray.SegBufPhyAddr, <variable>.StreamSegArray.SegBufPhyAddr
	ldr	lr, [fp, #-100]	@, %sfp
	str	ip, [fp, #-84]	@, %sfp
	ldr	r3, [r4, r2]	@, <variable>.StreamSegArray.SegFreshSize
	str	r0, [fp, #-52]	@ <variable>.StreamSegArray.SegBufPhyAddr,
	str	r3, [fp, #-104]	@, %sfp
	ldr	r1, [r4, lr]	@ <variable>.StreamSegArray.SegBufSize, <variable>.StreamSegArray.SegBufSize
	str	r1, [fp, #-48]	@ <variable>.StreamSegArray.SegBufSize,
.L761:
	ldrsb	r0, [r4, #1]	@ <variable>.IsCounting, <variable>.IsCounting
	cmp	r0, #0	@ <variable>.IsCounting,
	bne	.L762	@,
	ldr	ip, [fp, #-48]	@ SegBufTotalSize, SegBufTotalSize
	ldr	r2, [fp, #-104]	@, %sfp
	add	r3, ip, ip, lsr #31	@, tmp218, SegBufTotalSize, SegBufTotalSize,
	cmp	r2, r3, asr #1	@, tmp218,
	bge	.L763	@,
	ldr	r1, [fp, #-84]	@, %sfp
	cmp	r1, #127	@,
	bgt	.L763	@,
	mov	r1, #1	@ tmp220,
	mov	r0, r5	@, NextInstId
	strb	r1, [r4, #1]	@ tmp220, <variable>.IsCounting
	bl	CalcInstBlockTime	@
	b	.L763	@
.L775:
	add	sl, sl, r5	@ tmp242, tmp270, NextInstId
	ldr	r2, [fp, #-108]	@, %sfp
	mov	r0, r5	@, NextInstId
	add	sl, r9, sl, asl #4	@, tmp244, tmp269, tmp242,
	str	r5, [r2, #0]	@ NextInstId,
	ldr	lr, [sl, #40]	@ pSmInstArray, <variable>.pSmInstArray
	ldr	r2, [r4, #88]	@, <variable>.Config.ScdLowdlyEnable
	cmp	lr, r3	@ pSmInstArray,
	movwne	r3, #:lower16:190872	@ tmp246,
	movtne	r3, #:upper16:190872	@ tmp246,
	movne	r1, #1	@ tmp247,
	strne	r1, [lr, r3]	@ tmp247, <variable>.Mode
	mov	r1, #1	@,
	bl	DBG_CountTimeInfo	@
	mov	r0, #1	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	bne	.L776	@,
.L766:
	mov	r0, #0	@ D.52797,
	b	.L751	@
.L776:
	bl	OSAL_GetTimeInMs	@
	add	r9, r9, r5, asl #2	@, tmp252, tmp269, NextInstId,
	movw	r2, #:lower16:g_TraceBsPeriod	@ tmp256,
	movt	r2, #:upper16:g_TraceBsPeriod	@ tmp256,
	ldr	ip, [r2, #0]	@ g_TraceBsPeriod, g_TraceBsPeriod
	mov	r3, r0	@ D.52887,
	ldr	r0, [r9, #872]	@ tmp255, last_rec_pos_time
	rsb	r1, r0, r3	@ tmp254, tmp255, D.52887
	cmp	r1, ip	@ tmp254, g_TraceBsPeriod
	bls	.L766	@,
	mov	lr, r5, asl #24	@ tmp265, NextInstId,
	ldr	r0, .L777	@,
	add	r2, lr, #65536	@, tmp265,
	movw	r1, #5340	@,
	str	r3, [r9, #872]	@ D.52887, last_rec_pos_time
	bl	DBG_AddTrace	@
	mov	r0, #0	@ D.52797,
	b	.L751	@
.L762:
	mov	r0, r5	@, NextInstId
	mov	r1, #0	@,
	bl	CalcInstBlockTime	@
	cmp	r0, #1000	@ WaitSegTime,
	ble	.L763	@,
	ldr	r3, [fp, #-48]	@ SegBufTotalSize, SegBufTotalSize
	ldr	lr, [fp, #-104]	@, %sfp
	cmp	r3, #0	@ SegBufTotalSize,
	add	r2, r3, #3	@ tmp225, SegBufTotalSize,
	movlt	r3, r2	@ SegBufTotalSize, tmp225
	cmp	lr, r3, asr #2	@, SegBufTotalSize,
	bge	.L763	@,
	ldr	ip, [fp, #-84]	@, %sfp
	cmp	ip, #63	@,
	bgt	.L763	@,
	mov	r2, r0	@, WaitSegTime
	movw	r1, #:lower16:.LC131	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC131	@,
	bl	dprint_vfmw	@
	ldr	r0, [fp, #-80]	@, %sfp
	mvn	r1, #0	@,
	bl	ReleaseStreamSeg	@
	mov	r0, #0	@ tmp228,
	strb	r0, [r4, #0]	@ tmp228, <variable>.SegFullFlag
	strb	r0, [r4, #1]	@ tmp228, <variable>.IsCounting
	b	.L763	@
.L772:
	mov	r0, r5	@, NextInstId
	bl	SM_CopyYuvToDnr	@
	cmp	r0, #0	@,
	beq	.L754	@,
	movw	r1, #:lower16:.LC130	@,
	mov	r0, #26	@,
	movt	r1, #:upper16:.LC130	@,
	bl	dprint_vfmw	@
	b	.L754	@
.L770:
	mov	r2, r0	@, ScdId
	movw	r1, #:lower16:.LC129	@,
	mov	r0, #26	@,
	movt	r1, #:upper16:.LC129	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52797,
	b	.L751	@
.L778:
	.align	2
.L777:
	.word	.LANCHOR1+292
	.fnend
	.size	SM_DoNextInstance, .-SM_DoNextInstance
	.align	2
	.global	SCDDRV_ActivateSCD
	.type	SCDDRV_ActivateSCD, %function
SCDDRV_ActivateSCD:
	.fnstart
.LFB1611:
	@ args = 0, pretend = 0, frame = 8
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
	cmp	r0, #0	@ ScdId,
	beq	.L782	@,
.L781:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L782:
	sub	r1, fp, #24	@,,
	bl	SM_DoNextInstance	@
	cmp	r0, #0	@,
	bne	.L781	@,
	ldr	r0, [fp, #-24]	@ NextInstID, NextInstID
	movw	r4, #:lower16:.LANCHOR0	@ tmp137,
	movt	r4, #:upper16:.LANCHOR0	@ tmp137,
	mov	r3, #1	@ tmp140,
	str	r0, [r4, #852]	@ NextInstID, <variable>.ThisInstID
	str	r3, [r4, #856]	@ tmp140, <variable>.SCDState
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:.LC132	@,
	ldr	r2, .L783	@,
	movt	r1, #:upper16:.LC132	@,
	movw	r3, #5684	@,
	str	r0, [r4, #860]	@, <variable>.LastProcessTime
	mov	r0, #26	@,
	bl	dprint_vfmw	@
	b	.L781	@
.L784:
	.align	2
.L783:
	.word	.LANCHOR1+312
	.fnend
	.size	SCDDRV_ActivateSCD, .-SCDDRV_ActivateSCD
	.align	2
	.global	ConfigStreamSegArray
	.type	ConfigStreamSegArray, %function
ConfigStreamSegArray:
	.fnstart
.LFB1549:
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
	cmp	r0, #0	@ pStreamSegArray,
	cmpne	r1, #0	@, BufPhyAddr,
	mov	r4, r1	@ BufPhyAddr, BufPhyAddr
	mov	r5, r0	@ pStreamSegArray, pStreamSegArray
	bne	.L789	@,
.L786:
	mvn	r0, #0	@ D.50052,
.L787:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L789:
	rsbs	r6, r2, #1	@ tmp151, pBufVirAddr
	movcc	r6, #0	@ tmp151
	cmp	r3, #262144	@ BufSize,
	orrcc	r6, r6, #1	@,, tmp154, tmp151
	cmp	r6, #0	@ tmp154,
	bne	.L786	@,
	movw	r1, #:lower16:92216	@,
	movt	r1, #:upper16:92216	@,
	str	r2, [fp, #-32]	@,
	movw	r7, #:lower16:92184	@ tmp156,
	str	r3, [fp, #-36]	@,
	movt	r7, #:upper16:92184	@ tmp156,
	bl	__memzero	@
	movw	r0, #:lower16:92196	@ tmp158,
	movt	r0, #:upper16:92196	@ tmp158,
	str	r4, [r5, r7]	@ BufPhyAddr, <variable>.SegBufPhyAddr
	movw	ip, #:lower16:92188	@ tmp159,
	movt	ip, #:upper16:92188	@ tmp159,
	str	r4, [r5, r0]	@ BufPhyAddr, <variable>.SegBufWriteAddr
	movw	r1, #:lower16:92192	@ tmp157,
	ldr	r3, [fp, #-36]	@,
	movt	r1, #:upper16:92192	@ tmp157,
	mov	r0, r6	@ D.50052, tmp154
	str	r3, [r5, ip]	@ BufSize, <variable>.SegBufSize
	ldr	r2, [fp, #-32]	@,
	str	r4, [r5, r1]	@ BufPhyAddr, <variable>.SegBufReadAddr
	str	r2, [r5, #0]	@ pBufVirAddr, <variable>.pSegBufVirAddr
	b	.L787	@
	.fnend
	.size	ConfigStreamSegArray, .-ConfigStreamSegArray
	.align	2
	.global	SM_Config
	.type	SM_Config, %function
SM_Config:
	.fnstart
.LFB1570:
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
	cmp	r0, #15	@ SmID,
	movls	r3, #0	@, tmp151
	movhi	r3, #1	@, tmp151
	cmp	r1, #0	@ pSmCfg,
	orreq	r3, r3, #1	@,, tmp154, tmp151
	mov	r4, r0	@ SmID, SmID
	cmp	r3, #0	@ tmp154,
	mov	r6, r1	@ pSmCfg, pSmCfg
	bne	.L805	@,
	add	ip, r0, r0, asl #1	@, tmp160, SmID, SmID,
	movw	r3, #:lower16:.LANCHOR0	@ tmp156,
	movt	r3, #:upper16:.LANCHOR0	@ tmp156,
	add	r2, r3, ip, asl #4	@, tmp162, tmp156, tmp160,
	ldr	r5, [r2, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r5, #0	@ pSmInstArray,
	beq	.L793	@,
	ldr	r7, [r5, #60]	@ <variable>.Config.BufPhyAddr, <variable>.Config.BufPhyAddr
	ldr	r8, [r1, #12]	@ D.50643, <variable>.BufPhyAddr
	cmp	r7, r8	@ <variable>.Config.BufPhyAddr, D.50643
	addeq	r7, r5, #48	@ tmp303, pSmInstArray,
	bne	.L806	@,
.L794:
	mov	r1, r6	@, pSmCfg
	mov	r2, #152	@,
	mov	r0, r7	@, tmp303
	bl	memcpy	@
	movw	r0, #:lower16:204748	@ tmp294,
	movt	r0, #:upper16:204748	@ tmp294,
	mov	r2, #2	@ tmp295,
	movw	r3, #:lower16:190856	@ tmp299,
	movt	r3, #:upper16:190856	@ tmp299,
	str	r2, [r5, r0]	@ tmp295, <variable>.UpMsgStepNum
	ldr	r1, [r6, #8]	@ <variable>.VidStd, <variable>.VidStd
	str	r4, [r5, r3]	@ SmID, <variable>.InstID
	cmp	r1, #2	@ <variable>.VidStd,
	moveq	r1, #3	@ tmp298,
	streq	r1, [r5, r0]	@ tmp298, <variable>.UpMsgStepNum
	mov	r0, #0	@ D.50635,
.L792:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L805:
	mov	r3, r0	@, SmID
	movw	r1, #:lower16:.LC133	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC133	@,
	mov	r2, #1936	@,
	str	r6, [sp, #0]	@ pSmCfg,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50635,
	b	.L792	@
.L806:
	cmp	r8, #0	@ D.50643,
	bne	.L807	@,
.L793:
	mvn	r0, #0	@ D.50635,
	b	.L792	@
.L807:
	ldr	r7, [r1, #0]	@ <variable>.pBufVirAddr, <variable>.pBufVirAddr
	cmp	r7, #0	@ <variable>.pBufVirAddr,
	beq	.L793	@,
	ldr	sl, [r3, #780]	@ <variable>.ScdDrvMem.DownMsgMemAddr, <variable>.ScdDrvMem.DownMsgMemAddr
	movw	r7, #:lower16:190760	@ tmp166,
	movt	r7, #:upper16:190760	@ tmp166,
	movw	r9, #:lower16:190780	@,
	movw	lr, #:lower16:190764	@ tmp169,
	movt	lr, #:upper16:190764	@ tmp169,
	str	sl, [r5, r7]	@ <variable>.ScdDrvMem.DownMsgMemAddr, <variable>.BufAddrCfg.DownMsgPhyAddr
	movw	r8, #:lower16:190768	@ tmp172,
	str	r9, [fp, #-88]	@, %sfp
	movt	r8, #:upper16:190768	@ tmp172,
	ldr	r9, [r3, #784]	@, <variable>.ScdDrvMem.pDownMsgMemVirAddr
	movw	r7, #:lower16:190772	@ tmp175,
	movt	r7, #:upper16:190772	@ tmp175,
	movw	sl, #:lower16:190776	@ tmp178,
	movt	sl, #:upper16:190776	@ tmp178,
	add	ip, ip, #1	@, tmp160,
	str	r9, [r5, lr]	@, <variable>.BufAddrCfg.pDownMsgVirAddr
	movw	r9, #:lower16:190812	@,
	ldr	lr, [fp, #-88]	@, %sfp
	movt	r9, #:upper16:190812	@,
	str	r9, [fp, #-48]	@, %sfp
	movt	lr, #:upper16:190780	@,
	str	lr, [fp, #-88]	@, %sfp
	ldr	r9, [r3, #788]	@, <variable>.ScdDrvMem.DownMsgMemSize
	movw	lr, #:lower16:190784	@ tmp184,
	movt	lr, #:upper16:190784	@ tmp184,
	str	r9, [r5, r8]	@, <variable>.BufAddrCfg.DownMsgSize
	movw	r8, #:lower16:190816	@,
	str	r8, [fp, #-52]	@, %sfp
	movw	r9, #:lower16:190816	@,
	ldr	r8, [r3, #792]	@ <variable>.ScdDrvMem.UpMsgMemAddr, <variable>.ScdDrvMem.UpMsgMemAddr
	movt	r9, #:upper16:190816	@,
	str	r9, [fp, #-52]	@, %sfp
	movw	r9, #:lower16:190820	@,
	movt	r9, #:upper16:190820	@,
	str	r9, [fp, #-56]	@, %sfp
	movw	r9, #:lower16:190824	@,
	movt	r9, #:upper16:190824	@,
	str	r9, [fp, #-60]	@, %sfp
	movw	r9, #:lower16:190832	@,
	str	r8, [r5, r7]	@ <variable>.ScdDrvMem.UpMsgMemAddr, <variable>.BufAddrCfg.UpMsgPhyAddr
	movw	r7, #:lower16:190828	@,
	str	r7, [fp, #-64]	@, %sfp
	movt	r9, #:upper16:190832	@,
	ldr	r7, [r3, #796]	@ <variable>.ScdDrvMem.pUpMsgMemVirAddr, <variable>.ScdDrvMem.pUpMsgMemVirAddr
	movw	r8, #:lower16:190828	@,
	str	ip, [fp, #-80]	@, %sfp
	movt	r8, #:upper16:190828	@,
	str	r9, [fp, #-68]	@, %sfp
	movw	ip, #:lower16:190788	@,
	str	r8, [fp, #-64]	@, %sfp
	movt	ip, #:upper16:190788	@,
	str	r7, [r5, sl]	@ <variable>.ScdDrvMem.pUpMsgMemVirAddr, <variable>.BufAddrCfg.pUpMsgVirAddr
	mov	sl, #1152	@ tmp185,
	ldr	r8, [fp, #-80]	@, %sfp
	movw	r9, #:lower16:190792	@,
	movt	r9, #:upper16:190792	@,
	add	r7, r3, r8, asl #4	@,, tmp156,,
	str	r7, [fp, #-84]	@, %sfp
	ldr	r7, [r3, #800]	@ <variable>.ScdDrvMem.UpMsgMemSize, <variable>.ScdDrvMem.UpMsgMemSize
	str	ip, [fp, #-72]	@, %sfp
	movw	ip, #:lower16:190800	@,
	str	sl, [r5, lr]	@ tmp185, <variable>.BufAddrCfg.UpMsgNum
	movw	lr, #:lower16:190796	@,
	ldr	r8, [fp, #-88]	@, %sfp
	movt	lr, #:upper16:190796	@,
	str	r9, [fp, #-92]	@, %sfp
	movt	ip, #:upper16:190800	@,
	str	r7, [r5, r8]	@ <variable>.ScdDrvMem.UpMsgMemSize, <variable>.BufAddrCfg.UpMsgSize
	ldr	r9, [fp, #-48]	@, %sfp
	str	lr, [fp, #-76]	@, %sfp
	movw	lr, #:lower16:190804	@ tmp242,
	ldr	sl, [r3, #804]	@ <variable>.ScdDrvMem.DvmMemAddr, <variable>.ScdDrvMem.DvmMemAddr
	movt	lr, #:upper16:190804	@ tmp242,
	str	ip, [fp, #-88]	@, %sfp
	movw	ip, #:lower16:190808	@ tmp252,
	movt	ip, #:upper16:190808	@ tmp252,
	str	sl, [r5, r9]	@ <variable>.ScdDrvMem.DvmMemAddr, <variable>.BufAddrCfg.DvmMemAddr
	movw	sl, #:lower16:190848	@ tmp265,
	ldr	r7, [r3, #808]	@, <variable>.ScdDrvMem.pDvmMemVirAddr
	movt	sl, #:upper16:190848	@ tmp265,
	ldr	r8, [fp, #-52]	@, %sfp
	movw	r9, #:lower16:190756	@ tmp267,
	movt	r9, #:upper16:190756	@ tmp267,
	str	r7, [r5, r8]	@, <variable>.BufAddrCfg.pDvmMemVirAddr
	ldr	r8, [fp, #-56]	@, %sfp
	ldr	r7, [r3, #812]	@, <variable>.ScdDrvMem.DvmMemSize
	str	r7, [r5, r8]	@, <variable>.BufAddrCfg.DvmMemSize
	ldr	r8, [fp, #-60]	@, %sfp
	ldr	r7, [r3, #816]	@, <variable>.ScdDrvMem.DspSedTopMemAddr
	str	r7, [r5, r8]	@, <variable>.BufAddrCfg.DspSedTopMemAddr
	ldr	r8, [fp, #-64]	@, %sfp
	ldr	r7, [r3, #820]	@, <variable>.ScdDrvMem.pDspSedTopMemVirAddr
	str	r7, [r5, r8]	@, <variable>.BufAddrCfg.pDspSedTopMemVirAddr
	ldr	r8, [fp, #-68]	@, %sfp
	ldr	r7, [r3, #824]	@, <variable>.ScdDrvMem.DspSedTopMemSize
	str	r7, [r5, r8]	@, <variable>.BufAddrCfg.DspSedTopMemSize
	ldr	r8, [fp, #-80]	@, %sfp
	ldr	r7, [fp, #-72]	@, %sfp
	ldr	r3, [r3, r8, asl #4]	@ <variable>.DspCtxMem.DspSpsMsgMemAddr, <variable>.DspCtxMem.DspSpsMsgMemAddr
	str	r3, [r5, r7]	@ <variable>.DspCtxMem.DspSpsMsgMemAddr, <variable>.BufAddrCfg.DspSpsMsgMemAddr
	ldr	r8, [fp, #-84]	@, %sfp
	ldr	r7, [fp, #-92]	@, %sfp
	ldr	r3, [r8, #4]	@ <variable>.DspCtxMem.pDspSpsMsgMemVirAddr, <variable>.DspCtxMem.pDspSpsMsgMemVirAddr
	str	r3, [r5, r7]	@ <variable>.DspCtxMem.pDspSpsMsgMemVirAddr, <variable>.BufAddrCfg.pDspSpsMsgMemVirAddr
	ldr	r8, [fp, #-76]	@, %sfp
	ldr	r3, [r2, #24]	@ <variable>.DspCtxMem.DspSpsMsgMemSize, <variable>.DspCtxMem.DspSpsMsgMemSize
	str	r3, [r5, r8]	@ <variable>.DspCtxMem.DspSpsMsgMemSize, <variable>.BufAddrCfg.DspSpsMsgMemSize
	ldr	r7, [fp, #-88]	@, %sfp
	ldr	r8, [r2, #28]	@ <variable>.DspCtxMem.DspPpsMsgMemAddr, <variable>.DspCtxMem.DspPpsMsgMemAddr
	str	r8, [r5, r7]	@ <variable>.DspCtxMem.DspPpsMsgMemAddr, <variable>.BufAddrCfg.DspPpsMsgMemAddr
	ldr	r3, [r2, #32]	@ <variable>.DspCtxMem.pDspPpsMsgMemVirAddr, <variable>.DspCtxMem.pDspPpsMsgMemVirAddr
	str	r3, [r5, lr]	@ <variable>.DspCtxMem.pDspPpsMsgMemVirAddr, <variable>.BufAddrCfg.pDspPpsMsgMemVirAddr
	ldr	r7, [r2, #36]	@ <variable>.DspCtxMem.DspPpsMsgMemSize, <variable>.DspCtxMem.DspPpsMsgMemSize
	str	r7, [r5, ip]	@ <variable>.DspCtxMem.DspPpsMsgMemSize, <variable>.BufAddrCfg.DspPpsMsgMemSize
	ldr	r8, [r1, #12]	@ temp.3041, <variable>.BufPhyAddr
	ldr	r7, [r1, #8]	@ <variable>.VidStd, <variable>.VidStd
	add	r2, r8, #3	@ tmp263, temp.3041,
	ldr	ip, [r1, #0]	@ <variable>.pBufVirAddr, <variable>.pBufVirAddr
	bic	r3, r2, #3	@ TmpPhyAddr, tmp263,
	cmp	r7, #6	@ <variable>.VidStd,
	rsb	r8, r8, r3	@ ByteOffsetInWord, temp.3041, TmpPhyAddr
	add	r2, r8, ip	@ pTmpVirAddr, ByteOffsetInWord, <variable>.pBufVirAddr
	moveq	r7, #1048576	@ prephitmp.3029,
	movne	r7, #131072	@ prephitmp.3029,
	add	lr, r7, r3	@ tmp266, prephitmp.3029, TmpPhyAddr
	add	ip, r2, r7	@ tmp268, pTmpVirAddr, prephitmp.3029
	str	lr, [r5, sl]	@ tmp266, <variable>.BufAddrCfg.SegBufPhyAddr
	str	ip, [r5, r9]	@ tmp268, <variable>.BufAddrCfg.pSegBufVirAddr
	bl	SetMaxSegSize	@
	ldr	r1, [r6, #16]	@ <variable>.BufSize, <variable>.BufSize
	rsb	r8, r8, r1	@ D.50683, ByteOffsetInWord, <variable>.BufSize
	cmn	r0, #1	@,
	moveq	r0, #2097152	@ SmMaxSegBufSize,
	cmp	r0, r8	@ SmMaxSegBufSize, D.50683
	bge	.L798	@,
	movw	r3, #:lower16:-1024	@ tmp270,
	movw	r1, #:lower16:190852	@ tmp272,
	movt	r3, #:upper16:-1024	@ tmp270,
	movt	r1, #:upper16:190852	@ tmp272,
	rsb	r2, r7, r3	@ tmp270, prephitmp.3029, tmp270
	add	r3, r2, r0	@ prephitmp.3030, tmp270, SmMaxSegBufSize
	str	r3, [r5, r1]	@ prephitmp.3030, <variable>.BufAddrCfg.SegBufSize
.L799:
	movw	ip, #:lower16:190848	@ tmp278,
	movw	r0, #:lower16:190756	@ tmp280,
	movt	ip, #:upper16:190848	@ tmp278,
	movt	r0, #:upper16:190756	@ tmp280,
	add	lr, r5, #98304	@, pSmInstArray,
	add	r7, r5, #48	@ tmp303, pSmInstArray,
	ldr	r1, [r5, ip]	@, <variable>.BufAddrCfg.SegBufPhyAddr
	ldr	r2, [r5, r0]	@, <variable>.BufAddrCfg.pSegBufVirAddr
	add	r0, lr, #224	@,,
	bl	ConfigStreamSegArray	@
	mov	r1, r6	@, pSmCfg
	mov	r2, #152	@,
	mov	r0, r7	@, tmp303
	bl	memcpy	@
	movw	r2, #:lower16:190860	@ tmp287,
	movt	r2, #:upper16:190860	@ tmp287,
	mov	r1, #0	@ tmp288,
	str	r1, [r5, r2]	@ tmp288, <variable>.ScdID
	b	.L794	@
.L798:
	sub	ip, r8, #1024	@ tmp273, D.50683,
	movw	r0, #:lower16:190852	@ tmp274,
	rsb	r3, r7, ip	@ prephitmp.3030, prephitmp.3029, tmp273
	movt	r0, #:upper16:190852	@ tmp274,
	cmp	r3, #262144	@ prephitmp.3030,
	str	r3, [r5, r0]	@ prephitmp.3030, <variable>.BufAddrCfg.SegBufSize
	bge	.L799	@,
	mvn	r0, #0	@ D.50635,
	b	.L792	@
	.fnend
	.size	SM_Config, .-SM_Config
	.align	2
	.global	SM_Reset
	.type	SM_Reset, %function
SM_Reset:
	.fnstart
.LFB1563:
	@ args = 0, pretend = 0, frame = 152
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #156
	sub	sp, sp, #156	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #15	@ SmID,
	mov	r5, r0	@ SmID, SmID
	bhi	.L820	@,
	mov	r7, r0, asl #1	@ tmp202, SmID,
	movw	r6, #:lower16:.LANCHOR0	@ tmp203,
	add	r1, r7, r0	@ tmp146, tmp202, SmID
	movt	r6, #:upper16:.LANCHOR0	@ tmp203,
	add	r3, r6, r1, asl #4	@, tmp148, tmp203, tmp146,
	ldr	r4, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r4, #0	@ pSmInstArray,
	beq	.L822	@,
	ldr	r8, [r4, #84]	@ <variable>.Config.DisContinueRawPacketFlag, <variable>.Config.DisContinueRawPacketFlag
	sub	r2, r8, #1	@ tmp151, <variable>.Config.DisContinueRawPacketFlag,
	cmp	r2, #1	@ tmp151,
	bls	.L823	@,
.L812:
	add	r7, r7, r5	@ tmp165, tmp202, SmID
	sub	r8, fp, #196	@ tmp204,,
	mov	sl, #0	@ tmp154,
	mvn	r0, #0	@ tmp155,
	add	r6, r6, r7, asl #4	@, tmp167, tmp203, tmp165,
	str	r0, [r4, #80]	@ tmp155, <variable>.Config.LastRawDisContinueCount
	add	r1, r4, #48	@, pSmInstArray,
	mov	r2, #152	@,
	str	sl, [r4, #84]	@ tmp154, <variable>.Config.DisContinueRawPacketFlag
	mov	r0, r8	@, tmp204
	bl	memcpy	@
	ldr	r2, [r6, #40]	@ pSmInstArray, <variable>.pSmInstArray
	movw	r3, #:lower16:190872	@ tmp160,
	movt	r3, #:upper16:190872	@ tmp160,
	cmp	r2, sl	@ pSmInstArray,
	movw	r1, #:lower16:.LANCHOR0	@ tmp161,
	ldr	r9, [r4, r3]	@ TmpMode, <variable>.Mode
	movt	r1, #:upper16:.LANCHOR0	@ tmp161,
	beq	.L813	@,
	ldr	ip, [r2, r3]	@ <variable>.Mode, <variable>.Mode
	cmp	ip, sl	@ <variable>.Mode,
	bne	.L824	@,
.L813:
	movw	r1, #:lower16:98508	@ tmp185,
	movw	lr, #:lower16:98504	@ tmp186,
	movt	r1, #:upper16:98508	@ tmp185,
	movt	lr, #:upper16:98504	@ tmp186,
	mvn	r6, #0	@ tmp192,
	sub	r9, r9, #1	@ tmp196, TmpMode,
	ldr	r0, [r4, lr]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Head
	ldr	r7, [r4, r1]	@ <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Tail
	subs	r1, r7, r0	@ RawNum, <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Head
	add	r0, r4, #200	@, pSmInstArray,
	addmi	r1, r1, #1024	@ RawNum, RawNum,
	mvn	r7, #0	@,
	bl	DeleteRawPacket	@
	mov	r1, #1	@,
	mov	r0, r5	@, SmID
	bl	DeleteRawPacketInBuffer	@
	mov	r0, r4	@, pSmInstArray
	movw	r1, #:lower16:204896	@,
	movt	r1, #:upper16:204896	@,
	bl	__memzero	@
	movw	r3, #:lower16:204712	@ tmp191,
	movw	ip, #:lower16:204748	@ tmp193,
	movt	r3, #:upper16:204712	@ tmp191,
	movt	ip, #:upper16:204748	@ tmp193,
	mov	r2, #2	@ tmp194,
	strd	r6, [r4, r3]	@ tmp192, pSmInstArray, tmp191
	mov	r0, r5	@, SmID
	str	r2, [r4, ip]	@ tmp194, <variable>.UpMsgStepNum
	mov	r1, r8	@, tmp204
	bl	SM_Config	@
	cmp	r9, #1	@ tmp196,
	movwls	r3, #:lower16:190872	@ tmp197,
	movhi	r2, #0	@ tmp200,
	movwhi	r3, #:lower16:190872	@ tmp199,
	movls	r0, #0	@ D.50340,
	movls	r2, #1	@ tmp198,
	movtls	r3, #:upper16:190872	@ tmp197,
	movthi	r3, #:upper16:190872	@ tmp199,
	movhi	r0, r2	@ D.50340, tmp200
	str	r2, [r4, r3]	@ tmp200, <variable>.Mode
.L810:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L824:
	movw	lr, #:lower16:190860	@ tmp171,
	movt	lr, #:upper16:190860	@ tmp171,
	ldr	r0, [r2, lr]	@ <variable>.ScdID, <variable>.ScdID
	cmp	r0, sl	@ <variable>.ScdID,
	bgt	.L813	@,
	add	r6, r0, r0, asl #1	@, tmp180, <variable>.ScdID, <variable>.ScdID,
	str	sl, [r2, r3]	@ tmp154, <variable>.Mode
	add	r1, r1, r6, asl #5	@, tmp182, tmp161, tmp180,
	ldr	r3, [r1, #856]	@ <variable>.SCDState, <variable>.SCDState
	cmp	r3, sl	@ <variable>.SCDState,
	beq	.L813	@,
.L814:
	add	sl, sl, #2	@ i, i,
	cmp	sl, #50	@ i,
	beq	.L813	@,
	add	sl, sl, #2	@ i, i,
	cmp	sl, #50	@ i,
	bne	.L814	@,
	b	.L813	@
.L822:
	movw	r1, #:lower16:.LC134	@,
	mov	r0, r4	@, pSmInstArray
	movt	r1, #:upper16:.LC134	@,
	movw	r2, #1463	@,
	bl	dprint_vfmw	@
.L820:
	mvn	r0, #0	@ D.50340,
	b	.L810	@
.L823:
	add	r1, r4, #96	@, pSmInstArray,
	bl	ReleaseRawStreamData	@
	b	.L812	@
	.fnend
	.size	SM_Reset, .-SM_Reset
	.align	2
	.global	ResetRawStreamArray
	.type	ResetRawStreamArray, %function
ResetRawStreamArray:
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
	cmp	r0, #0	@ pRawStreamArray,
	ldmeqfd	sp, {fp, sp, pc}	@
	movw	r1, #:lower16:98328	@,
	movt	r1, #:upper16:98328	@,
	bl	__memzero	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	ResetRawStreamArray, .-ResetRawStreamArray
	.align	2
	.global	FillExtraData
	.type	FillExtraData, %function
FillExtraData:
	.fnstart
.LFB1602:
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
	cmp	r0, #15	@ InstID,
	mov	r4, r1	@ pRawPacket, pRawPacket
	bls	.L850	@,
.L829:
	mvn	r0, #0	@ D.52356,
.L831:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L850:
	cmp	r1, #0	@ pRawPacket,
	beq	.L829	@,
	ldr	ip, [r1, #8]	@ D.52359, <variable>.Length
	cmp	ip, #0	@ D.52359,
	ble	.L851	@,
	add	r0, r0, r0, asl #1	@, tmp167, InstID, InstID,
	movw	r1, #:lower16:.LANCHOR0	@ tmp163,
	movt	r1, #:upper16:.LANCHOR0	@ tmp163,
	add	r3, r1, r0, asl #4	@, tmp169, tmp163, tmp167,
	ldr	r5, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	ldr	r3, [r5, #56]	@ <variable>.Config.VidStd, <variable>.Config.VidStd
	cmp	r3, #5	@ <variable>.Config.VidStd,
	beq	.L834	@,
	cmp	r3, #8	@ <variable>.Config.VidStd,
	beq	.L835	@,
	cmp	r3, #1	@ <variable>.Config.VidStd,
	beq	.L852	@,
.L832:
	mov	r0, #0	@ D.52356,
	b	.L831	@
.L852:
	ldr	r0, [r5, #72]	@ <variable>.Config.StdExt.Vc1Ext.IsAdvProfile, <variable>.Config.StdExt.Vc1Ext.IsAdvProfile
	cmp	r0, #1	@ <variable>.Config.StdExt.Vc1Ext.IsAdvProfile,
	beq	.L853	@,
	ldr	r7, [r4, #76]	@ <variable>.RawExt.Flags, <variable>.RawExt.Flags
	ands	r7, r7, #128	@ tmp205, <variable>.RawExt.Flags,
	beq	.L840	@,
	ldr	r6, [r4, #80]	@ temp.3135, <variable>.RawExt.BufLen
	add	lr, ip, #12	@ D.52395, D.52359,
	cmp	lr, r6	@ D.52395, temp.3135
	bhi	.L841	@,
	cmp	lr, #128	@ D.52395,
	bgt	.L841	@,
	ldr	r1, [r4, #4]	@ temp.3136, <variable>.VirAddr
	mov	r2, ip	@, D.52359
	add	r0, r1, #8	@, temp.3136,
	bl	memmove	@
	add	r1, r4, #84	@, pRawPacket,
	mov	r2, #4	@,
	ldr	r0, [r4, #4]	@, <variable>.VirAddr
	bl	memcpy	@
	ldr	r0, [r4, #4]	@ <variable>.VirAddr, <variable>.VirAddr
	mov	r2, #4	@,
	add	r1, r4, #88	@, pRawPacket,
	add	r0, r0, r2	@, <variable>.VirAddr,
	bl	memcpy	@
	ldr	r2, [r4, #4]	@ <variable>.VirAddr, <variable>.VirAddr
	mov	r1, #4	@,
	add	r0, r2, #12	@, <variable>.VirAddr,
	bl	__memzero	@
	movw	r3, #:lower16:204760	@ tmp228,
	movt	r3, #:upper16:204760	@ tmp228,
	add	r1, r5, #203776	@, pSmInstArray,
	mov	ip, #16	@ tmp227,
	add	r0, r1, #988	@,,
	str	ip, [r4, #8]	@ tmp227, <variable>.Length
	str	ip, [r5, r3]	@ tmp227, <variable>.HeaderLen
	ldmib	r4, {r1, r2}	@ phole ldm
	bl	memcpy	@
	mov	r0, #0	@ D.52356,
	b	.L831	@
.L835:
	ldr	r7, [r4, #76]	@ <variable>.RawExt.Flags, <variable>.RawExt.Flags
	ands	r7, r7, #128	@ tmp273, <variable>.RawExt.Flags,
	beq	.L845	@,
	cmp	ip, #128	@ D.52359,
	bgt	.L854	@,
.L846:
	movw	r2, #:lower16:204760	@ tmp279,
	movt	r2, #:upper16:204760	@ tmp279,
	add	r1, r5, #203776	@, pSmInstArray,
	str	ip, [r5, r2]	@ D.52359, <variable>.HeaderLen
	add	r0, r1, #988	@,,
	ldmib	r4, {r1, r2}	@ phole ldm
	bl	memcpy	@
	mov	r0, #0	@ D.52356,
	b	.L831	@
.L834:
	ldr	lr, [r4, #80]	@ temp.3160, <variable>.RawExt.BufLen
	add	r5, ip, #8	@ D.52411, D.52359,
	cmp	r5, lr	@ D.52411, temp.3160
	bhi	.L855	@,
	ldr	r1, [r4, #4]	@ temp.3161, <variable>.VirAddr
	mov	r2, ip	@, D.52359
	add	r0, r1, #8	@, temp.3161,
	bl	memmove	@
	add	r1, r4, #84	@, pRawPacket,
	mov	r2, #4	@,
	ldr	r0, [r4, #4]	@, <variable>.VirAddr
	bl	memcpy	@
	ldr	r0, [r4, #4]	@ <variable>.VirAddr, <variable>.VirAddr
	mov	r2, #4	@,
	add	r1, r4, #88	@, pRawPacket,
	add	r0, r0, r2	@, <variable>.VirAddr,
	bl	memcpy	@
	ldr	r3, [r4, #8]	@ <variable>.Length, <variable>.Length
	mov	r0, #0	@ D.52356,
	add	ip, r3, #8	@ tmp272, <variable>.Length,
	str	ip, [r4, #8]	@ tmp272, <variable>.Length
	b	.L831	@
.L845:
	movw	r6, #:lower16:204760	@ tmp287,
	movt	r6, #:upper16:204760	@ tmp287,
	ldr	r8, [r4, #80]	@ temp.3182, <variable>.RawExt.BufLen
	ldr	r0, [r5, r6]	@ temp.3180, <variable>.HeaderLen
	add	lr, ip, r0	@ temp.3181, D.52359, temp.3180
	cmp	lr, r8	@ temp.3181, temp.3182
	bhi	.L856	@,
.L847:
	ldr	r1, [r4, #4]	@ temp.3184, <variable>.VirAddr
	mov	r2, ip	@, D.52359
	add	r0, r1, r0	@, temp.3184, temp.3180
	bl	memmove	@
	add	r0, r5, #203776	@, pSmInstArray,
	add	r1, r0, #988	@,,
	ldr	r2, [r5, r6]	@, <variable>.HeaderLen
	ldr	r0, [r4, #4]	@, <variable>.VirAddr
	bl	memcpy	@
	ldr	r3, [r5, r6]	@ <variable>.HeaderLen, <variable>.HeaderLen
	ldr	r1, [r4, #8]	@ <variable>.Length, <variable>.Length
	mov	r0, r7	@ D.52356, tmp273
	add	ip, r1, r3	@ tmp303, <variable>.Length, <variable>.HeaderLen
	str	ip, [r4, #8]	@ tmp303, <variable>.Length
	b	.L831	@
.L840:
	movw	r6, #:lower16:204760	@ tmp237,
	movt	r6, #:upper16:204760	@ tmp237,
	ldr	r8, [r4, #80]	@ temp.3148, <variable>.RawExt.BufLen
	ldr	r0, [r5, r6]	@ temp.3146, <variable>.HeaderLen
	add	lr, ip, r0	@ temp.3147, D.52359, temp.3146
	cmp	lr, r8	@ temp.3147, temp.3148
	bls	.L847	@,
	mov	r0, r3	@, <variable>.Config.VidStd
	movw	r1, #:lower16:.LC137	@,
	ldr	r2, .L858	@,
	movt	r1, #:upper16:.LC137	@,
	str	lr, [sp, #0]	@ temp.3147,
	str	r8, [sp, #4]	@ temp.3148,
	bl	dprint_vfmw	@
	mvn	r0, #1	@ D.52356,
	b	.L831	@
.L853:
	ldr	r2, [r4, #76]	@ <variable>.RawExt.Flags, <variable>.RawExt.Flags
	tst	r2, #128	@ <variable>.RawExt.Flags,
	beq	.L837	@,
	cmp	ip, #128	@ D.52359,
	ble	.L846	@,
	ldr	r2, .L858	@,
	movw	r1, #:lower16:.LC136	@,
	movt	r1, #:upper16:.LC136	@,
	mov	r3, r0	@,
.L849:
	mov	lr, #128	@ tmp278,
	stmia	sp, {ip, lr}	@ phole stm
	bl	dprint_vfmw	@
	mvn	r0, #1	@ D.52356,
	b	.L831	@
.L837:
	ldrb	r3, [r4, #72]	@ zero_extendqisi2	@ <variable>.RawExt.IsSeekPending, <variable>.RawExt.IsSeekPending
	cmp	r3, #0	@ <variable>.RawExt.IsSeekPending,
	beq	.L832	@,
	movw	r6, #:lower16:204760	@ tmp188,
	movt	r6, #:upper16:204760	@ tmp188,
	ldr	lr, [r4, #80]	@ D.52384, <variable>.RawExt.BufLen
	ldr	r0, [r5, r6]	@ D.52382, <variable>.HeaderLen
	add	r6, ip, r0	@ D.52383, D.52359, D.52382
	cmp	r6, lr	@ D.52383, D.52384
	bhi	.L857	@,
	ldr	r1, [r4, #4]	@ temp.3125, <variable>.VirAddr
	mov	r2, ip	@, D.52359
	movw	r6, #:lower16:204760	@ tmp194,
	movt	r6, #:upper16:204760	@ tmp194,
	add	r0, r1, r0	@, temp.3125, D.52382
	bl	memmove	@
	add	r0, r5, #203776	@, pSmInstArray,
	add	r1, r0, #988	@,,
	ldr	r2, [r5, r6]	@, <variable>.HeaderLen
	ldr	r0, [r4, #4]	@, <variable>.VirAddr
	bl	memcpy	@
	ldr	r1, [r5, r6]	@ <variable>.HeaderLen, <variable>.HeaderLen
	ldr	r2, [r4, #8]	@ <variable>.Length, <variable>.Length
	mov	r0, #0	@ D.52356,
	add	ip, r2, r1	@ tmp204, <variable>.Length, <variable>.HeaderLen
	str	ip, [r4, #8]	@ tmp204, <variable>.Length
	b	.L831	@
.L855:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC139	@,
	ldr	r2, .L858	@,
	movt	r1, #:upper16:.LC139	@,
	stmia	sp, {r5, lr}	@ phole stm
	bl	dprint_vfmw	@
	mvn	r0, #1	@ D.52356,
	b	.L831	@
.L841:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC138	@,
	ldr	r2, .L858	@,
	movt	r1, #:upper16:.LC138	@,
	mov	r3, r0	@,
	str	lr, [sp, #0]	@ D.52395,
	str	r6, [sp, #4]	@ temp.3135,
	mov	lr, #128	@ tmp210,
	str	lr, [sp, #8]	@ tmp210,
	bl	dprint_vfmw	@
	mvn	r0, #1	@ D.52356,
	b	.L831	@
.L856:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC137	@,
	ldr	r2, .L858	@,
	movt	r1, #:upper16:.LC137	@,
	str	lr, [sp, #0]	@ temp.3181,
	str	r8, [sp, #4]	@ temp.3182,
	bl	dprint_vfmw	@
	mvn	r0, #1	@ D.52356,
	b	.L831	@
.L851:
	mov	r3, ip	@, D.52359
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC135	@,
	ldr	r2, .L858	@,
	movt	r1, #:upper16:.LC135	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.52356,
	b	.L831	@
.L854:
	movw	r1, #:lower16:.LC136	@,
	mov	r0, #1	@,
	movt	r1, #:upper16:.LC136	@,
	ldr	r2, .L858	@,
	b	.L849	@
.L857:
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC137	@,
	ldr	r2, .L858	@,
	movt	r1, #:upper16:.LC137	@,
	mov	r3, r0	@,
	stmia	sp, {r6, lr}	@ phole stm
	bl	dprint_vfmw	@
	mvn	r0, #1	@ D.52356,
	b	.L831	@
.L859:
	.align	2
.L858:
	.word	.LANCHOR1+332
	.fnend
	.size	FillExtraData, .-FillExtraData
	.align	2
	.global	ReadRawStreamData
	.type	ReadRawStreamData, %function
ReadRawStreamData:
	.fnstart
.LFB1603:
	@ args = 0, pretend = 0, frame = 16
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
	add	r7, r0, r0, asl #1	@, tmp146, InstID, InstID,
	movw	r3, #:lower16:.LANCHOR0	@ tmp142,
	movt	r3, #:upper16:.LANCHOR0	@ tmp142,
	add	r7, r3, r7, asl #4	@, tmp148, tmp142, tmp146,
	sub	r4, fp, #48	@ tmp150,,
	mov	r5, r0	@ InstID, InstID
	mov	r8, r1	@ pRawPacket, pRawPacket
	ldr	r6, [r7, #40]	@ pSmInstArray, <variable>.pSmInstArray
	mov	r1, #12	@,
	mov	r0, r4	@, tmp150
	bl	__memzero	@
	cmp	r6, #0	@ pSmInstArray,
	beq	.L864	@,
	mov	r0, r5	@, InstID
	bl	VCTRL_GetStreamInterface	@
	subs	r3, r0, #0	@ pStreamIntf,
	beq	.L874	@,
	ldmia	r3, {r0, r1, r2}	@ pStreamIntf,,,
	stmia	r4, {r0, r1, r2}	@ tmp150,,,
	ldr	r0, [r3, #4]	@ <variable>.read_stream, <variable>.read_stream
	cmp	r0, #0	@ <variable>.read_stream,
	beq	.L864	@,
	ldr	r1, [r6, #92]	@ <variable>.Config.IsOmxPath, <variable>.Config.IsOmxPath
	cmp	r1, #1	@ <variable>.Config.IsOmxPath,
	beq	.L875	@,
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	mov	r1, r8	@, pRawPacket
	ldr	r4, [fp, #-44]	@ StreamIntf.read_stream, StreamIntf.read_stream
	ldr	r0, [fp, #-48]	@, StreamIntf.stream_provider_inst_id
	blx	r4	@ StreamIntf.read_stream
	mov	r4, r0	@ ret,
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r0, [r7, #40]	@ <variable>.pSmInstArray, <variable>.pSmInstArray
	cmp	r0, #0	@ <variable>.pSmInstArray,
	beq	.L876	@,
.L866:
	cmp	r4, #0	@ ret,
	bne	.L864	@,
	ldrb	r7, [r8, #53]	@ zero_extendqisi2	@ <variable>.is_stream_end_flag, <variable>.is_stream_end_flag
	cmp	r7, #1	@ <variable>.is_stream_end_flag,
	beq	.L877	@,
	ldr	ip, [r6, #92]	@ <variable>.Config.IsOmxPath, <variable>.Config.IsOmxPath
	cmp	ip, #1	@ <variable>.Config.IsOmxPath,
	beq	.L878	@,
.L869:
	movw	r3, #:lower16:98524	@ tmp177,
	movt	r3, #:upper16:98524	@ tmp177,
	ldr	r1, [r8, #8]	@ <variable>.Length, <variable>.Length
	ldr	r0, [r6, r3]	@ <variable>.RawPacketArray.RawTotalSize, <variable>.RawPacketArray.RawTotalSize
	add	lr, r1, r0	@ tmp181, <variable>.Length, <variable>.RawPacketArray.RawTotalSize
	str	lr, [r6, r3]	@ tmp181, <variable>.RawPacketArray.RawTotalSize
	b	.L863	@
.L864:
	mvn	r4, #6	@ ret,
.L863:
	mov	r0, r4	@, ret
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L875:
	mov	r1, r8	@, pRawPacket
	ldr	r0, [fp, #-48]	@, StreamIntf.stream_provider_inst_id
	ldr	r2, [fp, #-44]	@ StreamIntf.read_stream, StreamIntf.read_stream
	blx	r2	@ StreamIntf.read_stream
	mov	r4, r0	@ ret,
	b	.L866	@
.L877:
	mov	r0, r5	@, InstID
	mov	r1, r8	@, pRawPacket
	bl	FillEosRawStream	@
	cmp	r0, #0	@,
	bne	.L879	@,
	mov	r0, r5	@, InstID
	mov	r1, r7	@, <variable>.is_stream_end_flag
	bl	VCTRL_SetLastFrameState	@
	b	.L869	@
.L878:
	mov	r0, r5	@, InstID
	mov	r1, r8	@, pRawPacket
	bl	FillExtraData	@
	cmp	r0, #0	@,
	beq	.L869	@,
	mov	r2, r5	@, InstID
	mov	r0, r4	@, ret
	movw	r1, #:lower16:.LC143	@,
	movt	r1, #:upper16:.LC143	@,
	bl	dprint_vfmw	@
	mov	r1, r8	@, pRawPacket
	ldr	r0, [fp, #-48]	@, StreamIntf.stream_provider_inst_id
	bl	ReleaseRawStreamData	@
	cmp	r0, #0	@,
	beq	.L864	@,
	mov	r0, r4	@, ret
	movw	r1, #:lower16:.LC144	@,
	movt	r1, #:upper16:.LC144	@,
	mvn	r4, #6	@ ret,
	bl	dprint_vfmw	@
	b	.L863	@
.L879:
	mov	r0, r4	@, ret
	mov	r2, r5	@, InstID
	movw	r1, #:lower16:.LC142	@,
	movt	r1, #:upper16:.LC142	@,
	bl	dprint_vfmw	@
	mvn	r4, #6	@ ret,
	b	.L863	@
.L874:
	mov	r2, r5	@, InstID
	movw	r1, #:lower16:.LC140	@,
	movt	r1, #:upper16:.LC140	@,
	mvn	r4, #6	@ ret,
	bl	dprint_vfmw	@
	b	.L863	@
.L876:
	mov	r3, r5	@, InstID
	movw	r1, #:lower16:.LC141	@,
	movw	r2, #4683	@,
	movt	r1, #:upper16:.LC141	@,
	mvn	r4, #6	@ ret,
	bl	dprint_vfmw	@
	b	.L863	@
	.fnend
	.size	ReadRawStreamData, .-ReadRawStreamData
	.global	__aeabi_uidiv
	.align	2
	.global	FillRawData
	.type	FillRawData, %function
FillRawData:
	.fnstart
.LFB1600:
	@ args = 0, pretend = 0, frame = 120
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #124
	sub	sp, sp, #124	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r5, r0	@ InstID, InstID
	add	r0, r0, r0, asl #1	@, tmp160, InstID, InstID,
	movw	r6, #:lower16:.LANCHOR0	@ tmp368,
	movt	r6, #:upper16:.LANCHOR0	@ tmp368,
	mov	r1, #96	@,
	add	r3, r6, r0, asl #4	@, tmp162, tmp368, tmp160,
	sub	r0, fp, #140	@,,
	ldr	r4, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	bl	__memzero	@
	cmp	r4, #0	@ pSmInstArray,
	beq	.L903	@,
	ldr	r1, [r4, #56]	@ <variable>.Config.VidStd, <variable>.Config.VidStd
	cmp	r1, #18	@ <variable>.Config.VidStd,
	beq	.L903	@,
	ldr	r3, [r4, #84]	@ D.52141, <variable>.Config.DisContinueRawPacketFlag
	cmp	r3, #1	@ D.52141,
	beq	.L903	@,
	cmp	r3, #2	@ D.52141,
	movne	r0, r5, asl #24	@, InstID,
	strne	r0, [fp, #-156]	@, %sfp
	beq	.L915	@,
.L911:
	add	r2, r6, r5, asl #2	@, tmp375, tmp368, InstID,
	movw	r7, #:lower16:204756	@ tmp372,
	movw	r6, #:lower16:204728	@ tmp371,
	movw	sl, #:lower16:204752	@ tmp373,
	movt	r6, #:upper16:204728	@ tmp371,
	movt	r7, #:upper16:204756	@ tmp372,
	movt	sl, #:upper16:204752	@ tmp373,
	add	lr, r2, #936	@, tmp375,
	movw	r1, #:lower16:g_TraceBsPeriod	@,
	movw	ip, #:lower16:vfmw_save_str_file	@,
	movt	r1, #:upper16:g_TraceBsPeriod	@,
	movt	ip, #:upper16:vfmw_save_str_file	@,
	str	lr, [fp, #-152]	@, %sfp
	str	r1, [fp, #-148]	@, %sfp
	str	ip, [fp, #-144]	@, %sfp
.L909:
	ldr	r3, [r4, #92]	@ <variable>.Config.IsOmxPath, <variable>.Config.IsOmxPath
	cmp	r3, #1	@ <variable>.Config.IsOmxPath,
	beq	.L916	@,
.L891:
	mov	r0, r5	@, InstID
	bl	GetRawState	@
	cmp	r0, #0	@,
	bne	.L892	@,
	mov	r0, r5	@, InstID
	sub	r1, fp, #140	@,,
	bl	ReadRawStreamData	@
	cmp	r0, #0	@,
	bne	.L903	@,
	ldr	ip, [r4, #80]	@ prephitmp.3249, <variable>.Config.LastRawDisContinueCount
	cmn	ip, #1	@ prephitmp.3249,
	ldreq	ip, [fp, #-92]	@ prephitmp.3249, RawPacket.discontinue_count
	streq	ip, [r4, #80]	@ prephitmp.3249, <variable>.Config.LastRawDisContinueCount
	ldr	r0, [fp, #-92]	@ RawPacket.discontinue_count, RawPacket.discontinue_count
	cmp	r0, ip	@ RawPacket.discontinue_count, prephitmp.3249
	beq	.L894	@,
	ldr	r1, [r4, #56]	@ D.52229, <variable>.Config.VidStd
	cmp	r1, #3	@ D.52229,
	cmpne	r1, #1	@, D.52229,
	beq	.L917	@,
.L894:
	ldr	r1, [fp, #-132]	@ RawPacket.Length, RawPacket.Length
	movw	r8, #:lower16:204732	@ tmp284,
	ldr	r9, [r4, r6]	@ <variable>.TotalRawSize, <variable>.TotalRawSize
	movt	r8, #:upper16:204732	@ tmp284,
	ldr	r0, [r4, r7]	@ <variable>.u32RawNumCount, <variable>.u32RawNumCount
	add	ip, r1, r9	@ tmp274, RawPacket.Length, <variable>.TotalRawSize
	str	ip, [r4, r6]	@ tmp274, <variable>.TotalRawSize
	add	r3, r0, #1	@ tmp278, <variable>.u32RawNumCount,
	str	r3, [r4, r7]	@ tmp278, <variable>.u32RawNumCount
	ldr	lr, [r4, sl]	@ <variable>.u32RawSizeCount, <variable>.u32RawSizeCount
	ldr	r2, [fp, #-132]	@ RawPacket.Length, RawPacket.Length
	add	r9, r2, lr	@ tmp283, RawPacket.Length, <variable>.u32RawSizeCount
	str	r9, [r4, sl]	@ tmp283, <variable>.u32RawSizeCount
	bl	OSAL_GetTimeInMs	@
	ldr	r1, [r4, r8]	@ temp.3271, <variable>.LastStatTime
	cmp	r1, #0	@ temp.3271,
	mov	r9, r0	@ ThisTime.3270,
	streq	r0, [r4, r8]	@ ThisTime.3270, <variable>.LastStatTime
	beq	.L896	@,
	rsb	r1, r1, r0	@ TimePeriod.3272, temp.3271, ThisTime.3270
	cmp	r1, #2000	@ TimePeriod.3272,
	bls	.L896	@,
	ldr	r0, [r4, r6]	@ <variable>.TotalRawSize, <variable>.TotalRawSize
	movw	lr, #:lower16:204736	@ tmp286,
	movt	lr, #:upper16:204736	@ tmp286,
	str	lr, [fp, #-160]	@,
	mov	r0, r0, asl #3	@, <variable>.TotalRawSize,
	bl	__aeabi_uidiv	@
	mov	ip, #1000	@ tmp295,
	str	r9, [r4, r8]	@ ThisTime.3270, <variable>.LastStatTime
	mov	r1, #0	@ tmp298,
	str	r1, [r4, r6]	@ tmp298, <variable>.TotalRawSize
	ldr	r3, [fp, #-160]	@,
	mul	r2, ip, r0	@ tmp294, tmp295,
	mov	r8, r2, lsr #10	@ tmp296, tmp294,
	str	r8, [r4, r3]	@ tmp296, <variable>.BitRate
.L896:
	ldrd	r2, [fp, #-124]	@,,
	mov	r0, #29	@,
	movw	r1, #:lower16:.LC145	@,
	movt	r1, #:upper16:.LC145	@,
	bl	dprint_vfmw	@
	ldr	r2, [fp, #-140]	@, RawPacket.PhyAddr
	ldr	r3, [fp, #-132]	@, RawPacket.Length
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC146	@,
	movt	r1, #:upper16:.LC146	@,
	bl	dprint_vfmw	@
	ldrd	r0, [fp, #-124]	@ RawPacket.Pts,,
	mvn	r2, #0	@ tmp306,
	mov	r3, #0	@,
	cmp	r1, r3	@ RawPacket.Pts, tmp306
	cmpeq	r0, r2	@ RawPacket.Pts, tmp306
	beq	.L918	@,
	mov	r0, r5	@, InstID
	sub	r1, fp, #140	@,,
	bl	SM_PushRaw	@
	subs	r8, r0, #0	@ D.52255,
	bne	.L914	@,
.L898:
	mov	r3, #1	@ tmp310,
	mov	r1, r8	@, D.52255
	mov	r2, r8	@, D.52255
	strb	r3, [r4, #4]	@ tmp310, <variable>.FillNewRawFlag
	mov	r0, r5	@, InstID
	bl	DBG_CountTimeInfo	@
	mov	r0, r8	@, D.52255
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	bne	.L919	@,
.L899:
	ldr	r2, [fp, #-144]	@, %sfp
	ldr	r3, [r2, r5, asl #2]	@ tmp329, vfmw_save_str_file
	cmp	r3, #0	@ tmp329,
	beq	.L909	@,
	ldr	r8, [r4, #56]	@ eStd, <variable>.Config.VidStd
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	sub	r1, r8, #10	@ tmp331, eStd,
	cmp	r8, #4	@ eStd,
	cmpne	r1, #3	@, tmp331,
	bls	.L901	@,
	cmp	r8, #14	@ eStd,
	cmpne	r8, #17	@, eStd,
	bne	.L920	@,
.L901:
	ldr	ip, [fp, #-144]	@, %sfp
	sub	lr, fp, #140	@,,
	add	r0, lr, #8	@,,
	mov	r1, #4	@,
	ldr	r2, [ip, r5, asl #2]	@, vfmw_save_str_file
	bl	klib_fwrite	@
.L902:
	ldr	r3, [fp, #-144]	@, %sfp
	ldr	r1, [fp, #-132]	@, RawPacket.Length
	ldr	r0, [fp, #-136]	@, RawPacket.VirAddr
	ldr	r2, [r3, r5, asl #2]	@, vfmw_save_str_file
	bl	klib_fwrite	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r3, [r4, #92]	@ <variable>.Config.IsOmxPath, <variable>.Config.IsOmxPath
	cmp	r3, #1	@ <variable>.Config.IsOmxPath,
	bne	.L891	@,
.L916:
	mov	r0, r5	@, InstID
	bl	VCTRL_IsChanSegEnough	@
	cmp	r0, #1	@,
	bne	.L891	@,
.L903:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L919:
	bl	OSAL_GetTimeInMs	@
	ldr	ip, [fp, #-152]	@, %sfp
	ldr	r1, [ip, #0]	@ tmp318, last_rec_pos_time
	mov	r3, r0	@ ThisTime.3284,
	ldr	r0, [fp, #-148]	@, %sfp
	rsb	ip, r1, r3	@ tmp317, tmp318, ThisTime.3284
	ldr	r2, [r0, #0]	@ g_TraceBsPeriod, g_TraceBsPeriod
	cmp	ip, r2	@ tmp317, g_TraceBsPeriod
	bls	.L899	@,
	ldr	lr, [fp, #-152]	@, %sfp
	movw	r1, #4350	@,
	ldr	r0, .L924	@,
	ldr	r2, [fp, #-156]	@, %sfp
	str	r3, [lr, #0]	@ ThisTime.3284, last_rec_pos_time
	bl	DBG_AddTrace	@
	b	.L899	@
.L918:
	mov	r0, r5	@, InstID
	sub	r1, fp, #140	@,,
	mvn	r2, #0	@ tmp307,
	mvn	r3, #0	@,
	strd	r2, [fp, #-124]	@ tmp307,,
	bl	SM_PushRaw	@
	subs	r8, r0, #0	@ D.52255,
	beq	.L898	@,
.L914:
	movw	r1, #:lower16:.LC147	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC147	@,
	bl	dprint_vfmw	@
	b	.L903	@
.L920:
	cmp	r8, #8	@ eStd,
	cmpne	r8, #9	@, eStd,
	beq	.L901	@,
	cmp	r8, #5	@ eStd,
	beq	.L901	@,
	cmp	r8, #1	@ eStd,
	bne	.L902	@,
	ldr	r0, [r4, #72]	@ <variable>.Config.StdExt.Vc1Ext.IsAdvProfile, <variable>.Config.StdExt.Vc1Ext.IsAdvProfile
	cmp	r0, #1	@ <variable>.Config.StdExt.Vc1Ext.IsAdvProfile,
	bne	.L901	@,
	b	.L902	@
.L915:
	movw	r7, #:lower16:204728	@ tmp166,
	movt	r7, #:upper16:204728	@ tmp166,
	ldr	r2, [r4, #104]	@ <variable>.Config.DisContinueRawPacket.Length, <variable>.Config.DisContinueRawPacket.Length
	movw	r8, #:lower16:204732	@ tmp171,
	ldr	ip, [r4, r7]	@ <variable>.TotalRawSize, <variable>.TotalRawSize
	movt	r8, #:upper16:204732	@ tmp171,
	add	sl, r2, ip	@ tmp170, <variable>.Config.DisContinueRawPacket.Length, <variable>.TotalRawSize
	str	sl, [r4, r7]	@ tmp170, <variable>.TotalRawSize
	bl	OSAL_GetTimeInMs	@
	ldr	r3, [r4, r8]	@ D.52150, <variable>.LastStatTime
	cmp	r3, #0	@ D.52150,
	mov	sl, r0	@ ThisTime,
	streq	r0, [r4, r8]	@ ThisTime, <variable>.LastStatTime
	beq	.L884	@,
	rsb	r1, r3, r0	@ TimePeriod, D.52150, ThisTime
	cmp	r1, #2000	@ TimePeriod,
	bls	.L884	@,
	ldr	lr, [r4, r7]	@ <variable>.TotalRawSize, <variable>.TotalRawSize
	movw	r9, #:lower16:204736	@ tmp173,
	movt	r9, #:upper16:204736	@ tmp173,
	mov	r0, lr, asl #3	@, <variable>.TotalRawSize,
	bl	__aeabi_uidiv	@
	mov	r1, #1000	@ tmp182,
	mov	ip, #0	@ tmp185,
	str	sl, [r4, r8]	@ ThisTime, <variable>.LastStatTime
	str	ip, [r4, r7]	@ tmp185, <variable>.TotalRawSize
	mul	r3, r1, r0	@ tmp181, tmp182,
	mov	r7, r3, lsr #10	@ tmp183, tmp181,
	str	r7, [r4, r9]	@ tmp183, <variable>.BitRate
.L884:
	ldrd	r2, [r4, #112]	@, pSmInstArray,
	mov	r0, #29	@,
	movw	r1, #:lower16:.LC145	@,
	movt	r1, #:upper16:.LC145	@,
	bl	dprint_vfmw	@
	ldr	r2, [r4, #96]	@, <variable>.Config.DisContinueRawPacket.PhyAddr
	ldr	r3, [r4, #104]	@, <variable>.Config.DisContinueRawPacket.Length
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC146	@,
	movt	r1, #:upper16:.LC146	@,
	bl	dprint_vfmw	@
	ldrd	r0, [r4, #112]	@ <variable>.Config.DisContinueRawPacket.Pts, pSmInstArray,
	mvn	r2, #0	@ tmp193,
	mov	r3, #0	@,
	cmp	r1, r3	@ <variable>.Config.DisContinueRawPacket.Pts, tmp193
	cmpeq	r0, r2	@ <variable>.Config.DisContinueRawPacket.Pts, tmp193
	beq	.L921	@,
.L885:
	mov	r0, r5	@, InstID
	add	r1, r4, #96	@, pSmInstArray,
	bl	SM_PushRaw	@
	subs	r7, r0, #0	@ D.52168,
	bne	.L914	@,
	mov	r1, r7	@, D.52168
	mov	r2, r7	@, D.52168
	mov	r0, #1	@ tmp197,
	strb	r0, [r4, #4]	@ tmp197, <variable>.FillNewRawFlag
	mov	r0, r5	@, InstID
	bl	DBG_CountTimeInfo	@
	mov	r0, r7	@, D.52168
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	moveq	r1, r5, asl #24	@, InstID,
	streq	r1, [fp, #-156]	@, %sfp
	bne	.L922	@,
.L887:
	movw	r7, #:lower16:vfmw_save_str_file	@ tmp370,
	movt	r7, #:upper16:vfmw_save_str_file	@ tmp370,
	ldr	r2, [r7, r5, asl #2]	@ tmp217, vfmw_save_str_file
	cmp	r2, #0	@ tmp217,
	beq	.L888	@,
	ldr	r8, [r4, #56]	@ eStd, <variable>.Config.VidStd
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	sub	r3, r8, #10	@ tmp219, eStd,
	cmp	r8, #4	@ eStd,
	cmpne	r3, #3	@, tmp219,
	bls	.L889	@,
	cmp	r8, #14	@ eStd,
	cmpne	r8, #17	@, eStd,
	beq	.L889	@,
	cmp	r8, #8	@ eStd,
	cmpne	r8, #9	@, eStd,
	beq	.L889	@,
	cmp	r8, #5	@ eStd,
	beq	.L889	@,
	cmp	r8, #1	@ eStd,
	beq	.L923	@,
.L890:
	ldr	r2, [r7, r5, asl #2]	@, vfmw_save_str_file
	ldr	r0, [r4, #100]	@, <variable>.Config.DisContinueRawPacket.VirAddr
	ldr	r1, [r4, #104]	@, <variable>.Config.DisContinueRawPacket.Length
	bl	klib_fwrite	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
.L888:
	ldr	sl, [r4, #144]	@ <variable>.Config.DisContinueRawPacket.discontinue_count, <variable>.Config.DisContinueRawPacket.discontinue_count
	mov	r7, #0	@ tmp251,
	str	r7, [r4, #84]	@ tmp251, <variable>.Config.DisContinueRawPacketFlag
	str	sl, [r4, #80]	@ <variable>.Config.DisContinueRawPacket.discontinue_count, <variable>.Config.LastRawDisContinueCount
	b	.L911	@
.L892:
	mov	r2, r5	@, InstID
	mov	r0, #23	@,
	movw	r1, #:lower16:.LC149	@,
	movt	r1, #:upper16:.LC149	@,
	bl	dprint_vfmw	@
	movw	r2, #:lower16:190856	@ tmp364,
	movt	r2, #:upper16:190856	@ tmp364,
	mov	r1, #0	@,
	ldr	r0, [r4, r2]	@, <variable>.InstID
	bl	PrintScdRawState	@
	b	.L903	@
.L917:
	sub	r1, fp, #140	@,,
	add	r0, r4, #96	@, pSmInstArray,
	mov	r2, #96	@,
	bl	memcpy	@
	mov	r0, #1	@ tmp266,
	str	r0, [r4, #84]	@ tmp266, <variable>.Config.DisContinueRawPacketFlag
	movw	r1, #:lower16:.LC148	@,
	ldr	r2, [r4, #80]	@, <variable>.Config.LastRawDisContinueCount
	movt	r1, #:upper16:.LC148	@,
	ldr	r3, [fp, #-92]	@, RawPacket.discontinue_count
	bl	dprint_vfmw	@
	b	.L903	@
.L923:
	ldr	r0, [r4, #72]	@ <variable>.Config.StdExt.Vc1Ext.IsAdvProfile, <variable>.Config.StdExt.Vc1Ext.IsAdvProfile
	cmp	r0, #1	@ <variable>.Config.StdExt.Vc1Ext.IsAdvProfile,
	beq	.L890	@,
.L889:
	add	r0, r4, #104	@, pSmInstArray,
	mov	r1, #4	@,
	ldr	r2, [r7, r5, asl #2]	@, vfmw_save_str_file
	bl	klib_fwrite	@
	b	.L890	@
.L921:
	mvn	r2, #0	@ tmp194,
	mvn	r3, #0	@,
	strd	r2, [r4, #112]	@ tmp194, pSmInstArray,
	b	.L885	@
.L922:
	bl	OSAL_GetTimeInMs	@
	add	r3, r6, r5, asl #2	@, tmp202, tmp368, InstID,
	movw	r1, #:lower16:g_TraceBsPeriod	@ tmp206,
	movt	r1, #:upper16:g_TraceBsPeriod	@ tmp206,
	ldr	ip, [r3, #936]	@ tmp205, last_rec_pos_time
	ldr	r7, [r1, #0]	@ g_TraceBsPeriod, g_TraceBsPeriod
	rsb	sl, ip, r0	@ tmp204, tmp205, ThisTime.3263
	mov	r2, r0	@ ThisTime.3263,
	cmp	sl, r7	@ tmp204, g_TraceBsPeriod
	movls	r2, r5, asl #24	@, InstID,
	strls	r2, [fp, #-156]	@, %sfp
	bls	.L887	@,
	mov	lr, r5, asl #24	@, InstID,
	str	r2, [r3, #936]	@ ThisTime.3263, last_rec_pos_time
	ldr	r0, .L924	@,
	movw	r1, #4233	@,
	mov	r2, lr	@,
	str	lr, [fp, #-156]	@, %sfp
	bl	DBG_AddTrace	@
	b	.L887	@
.L925:
	.align	2
.L924:
	.word	.LANCHOR1+348
	.fnend
	.size	FillRawData, .-FillRawData
	.align	2
	.global	SM_Wakeup
	.type	SM_Wakeup, %function
SM_Wakeup:
	.fnstart
.LFB1614:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp211,
	movt	r4, #:upper16:.LANCHOR0	@ tmp211,
	ldr	r2, [r4, #40]	@ D.53105, <variable>.pSmInstArray
	cmp	r2, #0	@ D.53105,
	beq	.L927	@,
	movw	r0, #:lower16:190872	@ tmp151,
	movt	r0, #:upper16:190872	@ tmp151,
	ldr	r3, [r2, r0]	@ <variable>.Mode, <variable>.Mode
	cmp	r3, #1	@ <variable>.Mode,
	beq	.L946	@,
.L927:
	ldr	r2, [r4, #88]	@ temp.3323, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3323,
	beq	.L928	@,
	movw	r1, #:lower16:190872	@ tmp154,
	movt	r1, #:upper16:190872	@ tmp154,
	ldr	r0, [r2, r1]	@ <variable>.Mode, <variable>.Mode
	cmp	r0, #1	@ <variable>.Mode,
	beq	.L947	@,
.L928:
	ldr	r2, [r4, #136]	@ temp.3325, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3325,
	beq	.L929	@,
	movw	ip, #:lower16:190872	@ tmp157,
	movt	ip, #:upper16:190872	@ tmp157,
	ldr	r5, [r2, ip]	@ <variable>.Mode, <variable>.Mode
	cmp	r5, #1	@ <variable>.Mode,
	beq	.L948	@,
.L929:
	ldr	r2, [r4, #184]	@ temp.3327, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3327,
	beq	.L930	@,
	movw	r3, #:lower16:190872	@ tmp160,
	movt	r3, #:upper16:190872	@ tmp160,
	ldr	lr, [r2, r3]	@ <variable>.Mode, <variable>.Mode
	cmp	lr, #1	@ <variable>.Mode,
	beq	.L949	@,
.L930:
	ldr	r2, [r4, #232]	@ temp.3329, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3329,
	beq	.L931	@,
	movw	r1, #:lower16:190872	@ tmp163,
	movt	r1, #:upper16:190872	@ tmp163,
	ldr	r0, [r2, r1]	@ <variable>.Mode, <variable>.Mode
	cmp	r0, #1	@ <variable>.Mode,
	beq	.L950	@,
.L931:
	ldr	r2, [r4, #280]	@ temp.3331, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3331,
	beq	.L932	@,
	movw	ip, #:lower16:190872	@ tmp166,
	movt	ip, #:upper16:190872	@ tmp166,
	ldr	r5, [r2, ip]	@ <variable>.Mode, <variable>.Mode
	cmp	r5, #1	@ <variable>.Mode,
	beq	.L951	@,
.L932:
	ldr	r2, [r4, #328]	@ temp.3333, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3333,
	beq	.L933	@,
	movw	r3, #:lower16:190872	@ tmp169,
	movt	r3, #:upper16:190872	@ tmp169,
	ldr	lr, [r2, r3]	@ <variable>.Mode, <variable>.Mode
	cmp	lr, #1	@ <variable>.Mode,
	beq	.L952	@,
.L933:
	ldr	r2, [r4, #376]	@ temp.3335, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3335,
	beq	.L934	@,
	movw	r1, #:lower16:190872	@ tmp172,
	movt	r1, #:upper16:190872	@ tmp172,
	ldr	r0, [r2, r1]	@ <variable>.Mode, <variable>.Mode
	cmp	r0, #1	@ <variable>.Mode,
	beq	.L953	@,
.L934:
	ldr	r2, [r4, #424]	@ temp.3337, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3337,
	beq	.L935	@,
	movw	ip, #:lower16:190872	@ tmp175,
	movt	ip, #:upper16:190872	@ tmp175,
	ldr	r5, [r2, ip]	@ <variable>.Mode, <variable>.Mode
	cmp	r5, #1	@ <variable>.Mode,
	beq	.L954	@,
.L935:
	ldr	r2, [r4, #472]	@ temp.3339, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3339,
	beq	.L936	@,
	movw	r3, #:lower16:190872	@ tmp178,
	movt	r3, #:upper16:190872	@ tmp178,
	ldr	lr, [r2, r3]	@ <variable>.Mode, <variable>.Mode
	cmp	lr, #1	@ <variable>.Mode,
	beq	.L955	@,
.L936:
	ldr	r2, [r4, #520]	@ temp.3341, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3341,
	beq	.L937	@,
	movw	r1, #:lower16:190872	@ tmp181,
	movt	r1, #:upper16:190872	@ tmp181,
	ldr	r0, [r2, r1]	@ <variable>.Mode, <variable>.Mode
	cmp	r0, #1	@ <variable>.Mode,
	beq	.L956	@,
.L937:
	ldr	r2, [r4, #568]	@ temp.3343, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3343,
	beq	.L938	@,
	movw	ip, #:lower16:190872	@ tmp184,
	movt	ip, #:upper16:190872	@ tmp184,
	ldr	r5, [r2, ip]	@ <variable>.Mode, <variable>.Mode
	cmp	r5, #1	@ <variable>.Mode,
	beq	.L957	@,
.L938:
	ldr	r2, [r4, #616]	@ temp.3345, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3345,
	beq	.L939	@,
	movw	r3, #:lower16:190872	@ tmp187,
	movt	r3, #:upper16:190872	@ tmp187,
	ldr	lr, [r2, r3]	@ <variable>.Mode, <variable>.Mode
	cmp	lr, #1	@ <variable>.Mode,
	beq	.L958	@,
.L939:
	ldr	r2, [r4, #664]	@ temp.3347, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3347,
	beq	.L940	@,
	movw	r1, #:lower16:190872	@ tmp190,
	movt	r1, #:upper16:190872	@ tmp190,
	ldr	r0, [r2, r1]	@ <variable>.Mode, <variable>.Mode
	cmp	r0, #1	@ <variable>.Mode,
	beq	.L959	@,
.L940:
	ldr	r2, [r4, #712]	@ temp.3349, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3349,
	beq	.L941	@,
	movw	ip, #:lower16:190872	@ tmp193,
	movt	ip, #:upper16:190872	@ tmp193,
	ldr	r5, [r2, ip]	@ <variable>.Mode, <variable>.Mode
	cmp	r5, #1	@ <variable>.Mode,
	beq	.L960	@,
.L941:
	ldr	r2, [r4, #760]	@ temp.3321, <variable>.pSmInstArray
	cmp	r2, #0	@ temp.3321,
	beq	.L942	@,
	movw	lr, #:lower16:190872	@ tmp196,
	movt	lr, #:upper16:190872	@ tmp196,
	ldr	r4, [r2, lr]	@ <variable>.Mode, <variable>.Mode
	cmp	r4, #1	@ <variable>.Mode,
	beq	.L961	@,
.L942:
	mov	r4, #0	@ tmp201,
	ldr	r2, .L962	@,
	movw	r3, #5751	@,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC150	@,
	movt	r1, #:upper16:.LC150	@,
	mov	r5, #1	@ tmp202,
	stmia	sp, {r4, r5}	@ phole stm
	bl	dprint_vfmw	@
	mov	r0, r4	@, tmp201
	bl	SCDDRV_CheckDevice	@
	subs	r5, r0, #0	@ D.53112,
	bne	.L943	@,
	ldr	r2, .L962	@,
	movw	r3, #5754	@,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC151	@,
	movt	r1, #:upper16:.LC151	@,
	str	r5, [sp, #0]	@ D.53112,
	bl	dprint_vfmw	@
	mov	r0, r5	@, D.53112
	bl	SCDDRV_ActivateSCD	@
.L945:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L943:
	movw	r1, #:lower16:.LC152	@,
	ldr	r2, .L962	@,
	movt	r1, #:upper16:.LC152	@,
	movw	r3, #5759	@,
	mov	r0, #26	@,
	str	r4, [sp, #0]	@ tmp201,
	bl	dprint_vfmw	@
	b	.L945	@
.L946:
	mov	r0, #0	@,
	bl	FillRawData	@
	b	.L927	@
.L947:
	bl	FillRawData	@
	b	.L928	@
.L948:
	mov	r0, #2	@,
	bl	FillRawData	@
	b	.L929	@
.L949:
	mov	r0, #3	@,
	bl	FillRawData	@
	b	.L930	@
.L950:
	mov	r0, #4	@,
	bl	FillRawData	@
	b	.L931	@
.L951:
	mov	r0, #5	@,
	bl	FillRawData	@
	b	.L932	@
.L952:
	mov	r0, #6	@,
	bl	FillRawData	@
	b	.L933	@
.L953:
	mov	r0, #7	@,
	bl	FillRawData	@
	b	.L934	@
.L954:
	mov	r0, #8	@,
	bl	FillRawData	@
	b	.L935	@
.L955:
	mov	r0, #9	@,
	bl	FillRawData	@
	b	.L936	@
.L956:
	mov	r0, #10	@,
	bl	FillRawData	@
	b	.L937	@
.L957:
	mov	r0, #11	@,
	bl	FillRawData	@
	b	.L938	@
.L958:
	mov	r0, #12	@,
	bl	FillRawData	@
	b	.L939	@
.L959:
	mov	r0, #13	@,
	bl	FillRawData	@
	b	.L940	@
.L960:
	mov	r0, #14	@,
	bl	FillRawData	@
	b	.L941	@
.L961:
	mov	r0, #15	@,
	bl	FillRawData	@
	b	.L942	@
.L963:
	.align	2
.L962:
	.word	.LANCHOR1+360
	.fnend
	.size	SM_Wakeup, .-SM_Wakeup
	.align	2
	.global	SM_SeekPts
	.type	SM_SeekPts, %function
SM_SeekPts:
	.fnstart
.LFB1605:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #68
	sub	sp, sp, #68	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	add	r2, r0, r0, asl #1	@, tmp215, ChanID, ChanID,
	movw	r4, #:lower16:.LANCHOR0	@ tmp211,
	movt	r4, #:upper16:.LANCHOR0	@ tmp211,
	add	r3, r4, r2, asl #4	@, tmp217, tmp211, tmp215,
	str	r0, [fp, #-56]	@ ChanID, %sfp
	str	r1, [fp, #-60]	@ pArgs, %sfp
	ldr	r4, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r4, #0	@ pSmInstArray,
	mvneq	r0, #0	@ D.52571,
	bne	.L1051	@,
.L966:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1051:
	ldr	r1, [fp, #-60]	@, %sfp
	movw	sl, #:lower16:190752	@ tmp220,
	movt	sl, #:upper16:190752	@ tmp220,
	ldr	r7, [fp, #-60]	@, %sfp
	movw	r5, #:lower16:190696	@ tmp224,
	movt	r5, #:upper16:190696	@ tmp224,
	ldrd	r0, [r1]	@,
	add	r8, r4, #98304	@ pStreamSegArray, pSmInstArray,
	movw	r3, #:lower16:190704	@ tmp223,
	add	r8, r8, #224	@ pStreamSegArray, pStreamSegArray,
	movt	r3, #:upper16:190704	@ tmp223,
	strd	r0, [fp, #-52]	@,,
	ldr	r9, [r4, sl]	@, <variable>.SmPushRaw.PushRawOver
	ldr	r1, [fp, #-60]	@, %sfp
	cmp	r9, #1	@,
	str	r9, [fp, #-64]	@, %sfp
	ldrd	r6, [r7, #8]	@,,
	moveq	r9, #3	@ tmp222,
	strd	r6, [fp, #-92]	@,,
	ldrd	r0, [r1, #16]	@,,
	strd	r0, [fp, #-76]	@,,
	streq	r9, [r4, sl]	@ tmp222, <variable>.SmPushRaw.PushRawOver
	movw	r9, #:lower16:190700	@ tmp227,
	movt	r9, #:upper16:190700	@ tmp227,
	ldr	ip, [r4, r5]	@ <variable>.StreamSegArray.Head, <variable>.StreamSegArray.Head
	movw	sl, #:lower16:954437177	@ tmp653,
	movt	sl, #:upper16:954437177	@ tmp653,
	ldr	r7, [r4, r9]	@ prephitmp.3365, <variable>.StreamSegArray.Tail
	mov	r5, ip	@ i.3438, <variable>.StreamSegArray.Head
	str	ip, [r4, r3]	@ <variable>.StreamSegArray.Head, <variable>.StreamSegArray.History
.L1041:
	cmp	r5, r7	@ i.3438, prephitmp.3365
	mov	r6, r5, asl #2	@ tmp606, i.3438,
	mov	r1, r5	@, i.3438
	mov	r0, r8	@, pStreamSegArray
	add	r3, r6, r5	@ tmp269, tmp606, i.3438
	beq	.L1052	@,
.L968:
	add	r3, r4, r3, asl #4	@, tmp271, pSmInstArray, tmp269,
	movw	ip, #:lower16:98568	@ tmp274,
	add	r2, r3, #98304	@ tmp280, tmp271,
	movt	ip, #:upper16:98568	@ tmp274,
	add	r3, r2, #232	@ tmp272, tmp272,
	add	r2, r2, #264	@ tmp280, tmp280,
	ldrsb	r3, [r3, #4]	@ <variable>.SegState, <variable>.SegState
	cmp	r3, #1	@ <variable>.SegState,
	bne	.L971	@,
	ldrd	r2, [r2]	@ D.52599, <variable>.RawPts
	mvn	r0, #0	@,
	mvn	r1, #0	@,
	cmp	r3, r1	@ D.52599,
	cmpeq	r2, r0	@ D.52599,
	beq	.L1053	@,
	add	r0, r5, #1	@, i.3438,
	str	r0, [fp, #-80]	@, %sfp
	ldrd	r0, [fp, #-52]	@,,
	cmp	r1, r3	@, D.52599
	cmpeq	r0, r2	@, D.52599
	ldr	r1, [fp, #-80]	@, %sfp
	ldr	r0, [fp, #-80]	@, %sfp
	smull	r1, r2, sl, r1	@, tmp291, tmp653,
	mov	r3, r0, asr #31	@ tmp294,,
	bls	.L974	@,
	rsb	r3, r3, r2, asr #8	@, i.3438, tmp294, tmp291,
	movw	r7, #:lower16:190704	@,
	movt	r7, #:upper16:190704	@,
	add	r2, r3, r3, asl #3	@, tmp297, i.3438, i.3438,
	str	r5, [r4, r7]	@ i.3438, <variable>.StreamSegArray.History
	ldr	r7, [r4, r9]	@ prephitmp.3365, <variable>.StreamSegArray.Tail
	sub	r5, r0, r2, asl #7	@ i.3438,, tmp297,
	mov	r0, r8	@, pStreamSegArray
	cmp	r5, r7	@ i.3438, prephitmp.3365
	mov	r6, r5, asl #2	@ tmp606, i.3438,
	mov	r1, r5	@, i.3438
	add	r3, r6, r5	@ tmp269, tmp606, i.3438
	bne	.L968	@,
.L1052:
	movw	r0, #:lower16:190696	@ tmp228,
	movt	r0, #:upper16:190696	@ tmp228,
	ldr	r6, [r4, r0]	@ j, <variable>.StreamSegArray.Head
	cmp	r5, r6	@ i.3438, j
	beq	.L969	@,
	movw	r7, #:lower16:190732	@ tmp635,
	movw	r5, #:lower16:190736	@ tmp637,
	movw	r9, #:lower16:954437177	@ tmp638,
	movw	sl, #:lower16:190700	@ tmp639,
	movt	r7, #:upper16:190732	@ tmp635,
	movt	r5, #:upper16:190736	@ tmp637,
	movt	r9, #:upper16:954437177	@ tmp638,
	movt	sl, #:upper16:190700	@ tmp639,
.L1044:
	add	ip, r6, r6, asl #2	@, tmp232, j, j,
	mov	r1, r6	@, j
	add	r6, r6, #1	@ D.52594, j,
	mov	r0, r8	@, pStreamSegArray
	add	lr, r4, ip, asl #4	@, tmp234, pSmInstArray, tmp232,
	mov	ip, #2	@,
	add	r3, lr, #98304	@ tmp245, tmp234,
	add	lr, r3, #232	@ tmp235, tmp235,
	add	r3, r3, #240	@ tmp245, tmp245,
	strb	ip, [lr, #4]	@, <variable>.SegState
	ldr	ip, [r3, #4]	@ <variable>.LenInByte, <variable>.LenInByte
	ldr	r2, [r4, r7]	@ <variable>.StreamSegArray.SegFreshSize, <variable>.StreamSegArray.SegFreshSize
	ldr	lr, [r4, r5]	@ <variable>.StreamSegArray.SegFreshNum, <variable>.StreamSegArray.SegFreshNum
	rsb	r3, ip, r2	@ D.52588, <variable>.LenInByte, <variable>.StreamSegArray.SegFreshSize
	sub	ip, lr, #1	@ D.52590, <variable>.StreamSegArray.SegFreshNum,
	bic	r2, r3, r3, asr #31	@ tmp253, D.52588
	bic	lr, ip, ip, asr #31	@ tmp255, D.52590
	str	r2, [r4, r7]	@ tmp253, <variable>.StreamSegArray.SegFreshSize
	str	lr, [r4, r5]	@ tmp255, <variable>.StreamSegArray.SegFreshNum
	bl	ReleaseStreamSeg	@
	smull	r0, r1, r9, r6	@, tmp256, tmp638, D.52594
	mov	r3, r6, asr #31	@ tmp259, D.52594,
	ldr	ip, [r4, sl]	@ <variable>.StreamSegArray.Tail, <variable>.StreamSegArray.Tail
	rsb	r2, r3, r1, asr #8	@, j, tmp259, tmp256,
	add	r1, r2, r2, asl #3	@, tmp262, j, j,
	sub	r6, r6, r1, asl #7	@ j, D.52594, tmp262,
	cmp	ip, r6	@ <variable>.StreamSegArray.Tail, j
	bne	.L1044	@,
.L969:
	mov	r1, #0	@,
	ldr	r0, [fp, #-56]	@, %sfp
	bl	DeleteRawPacketInBuffer	@
	movw	ip, #:lower16:98504	@ tmp410,
	movw	r0, #:lower16:98508	@ tmp411,
	movt	ip, #:upper16:98504	@ tmp410,
	movt	r0, #:upper16:98508	@ tmp411,
	add	r1, r4, #200	@, pSmInstArray,
	str	r1, [fp, #-96]	@, %sfp
	movw	r9, #:lower16:98504	@ tmp414,
	ldr	r1, [r4, ip]	@ D.52628, <variable>.RawPacketArray.Head
	movt	r9, #:upper16:98504	@ tmp414,
	ldr	r3, [r4, r0]	@ D.52629, <variable>.RawPacketArray.Tail
	movw	r7, #:lower16:98512	@ tmp413,
	movt	r7, #:upper16:98512	@ tmp413,
	cmp	r1, r3	@ D.52628, D.52629
	addgt	r3, r3, #1024	@ tmp412, D.52629,
	rsb	sl, r1, r3	@, D.52628, tmp412
	str	sl, [fp, #-80]	@, %sfp
	movw	sl, #:lower16:98508	@ tmp415,
	movt	sl, #:upper16:98508	@ tmp415,
	ldr	r3, [r4, r9]	@ i, <variable>.RawPacketArray.Head
	mov	r9, r7	@ tmp631, tmp413
	ldr	ip, [r4, sl]	@ prephitmp.3370, <variable>.RawPacketArray.Tail
	str	r1, [r4, r7]	@ D.52628, <variable>.RawPacketArray.History
.L1042:
	add	lr, r3, r3, asl #1	@, tmp422, i, i,
	cmp	r3, ip	@ i, prephitmp.3370
	add	r2, r4, lr, asl #5	@, tmp426, pSmInstArray, tmp422,
	beq	.L1054	@,
.L985:
	add	r2, r2, #16	@ tmp427, tmp426,
	mvn	r6, #0	@,
	mvn	r7, #0	@,
	add	r8, r2, #200	@ tmp428, tmp427,
	ldrd	r0, [r2, #200]	@ temp.3418, tmp427,
	cmp	r1, r7	@ temp.3418,
	cmpeq	r0, r6	@ temp.3418,
	beq	.L1055	@,
	ldrd	r6, [fp, #-52]	@,,
	add	r2, r3, #1	@ temp.3420, i,
	cmp	r7, r1	@, temp.3418
	cmpeq	r6, r0	@, temp.3418
	mov	r5, r2, asr #31	@ tmp437, temp.3420,
	bls	.L992	@,
	mov	r5, r5, lsr #22	@ tmp438, tmp437,
	str	r3, [r4, r9]	@ i, <variable>.RawPacketArray.History
	add	lr, r2, r5	@ tmp439, temp.3420, tmp438
	ldr	ip, [r4, sl]	@ prephitmp.3370, <variable>.RawPacketArray.Tail
	mov	r3, lr, asl #22	@ tmp440, tmp439,
	mov	r0, r3, lsr #22	@ tmp440, tmp440,
	rsb	r3, r5, r0	@ i, tmp438, tmp440
	cmp	r3, ip	@ i, prephitmp.3370
	add	lr, r3, r3, asl #1	@, tmp422, i, i,
	add	r2, r4, lr, asl #5	@, tmp426, pSmInstArray, tmp422,
	bne	.L985	@,
.L1054:
	movw	r6, #:lower16:98504	@ tmp416,
	movt	r6, #:upper16:98504	@ tmp416,
	ldr	r2, [r4, r6]	@ temp.3395, <variable>.RawPacketArray.Head
	cmp	r3, r2	@ i, temp.3395
	rsblt	r1, r2, #1024	@ tmp417, temp.3395,
	rsbge	r1, r2, r3	@ DelNum.3389, temp.3395, i
	addlt	r1, r1, r3	@ DelNum.3389, tmp417, i
	cmp	r1, #0	@ DelNum.3389,
	movweq	r3, #:lower16:98512	@ tmp418,
	movteq	r3, #:upper16:98512	@ tmp418,
	streq	r2, [r4, r3]	@ temp.3395, <variable>.RawPacketArray.History
	bne	.L1056	@,
.L989:
	ldr	r9, [fp, #-80]	@, %sfp
	ldrd	r0, [fp, #-76]	@,,
	mov	r6, r9	@ RawNumInVfmw,
	mov	r7, r6, asr #31	@ RawNumInVfmw
	cmp	r1, r7	@, RawNumInVfmw
	cmpeq	r0, r6	@, RawNumInVfmw
	bls	.L1057	@,
	ldrd	r2, [fp, #-76]	@,,
	subs	r6, r2, r6	@ RawNumToSeek,, RawNumInVfmw
	sbc	r7, r3, r7	@ RawNumToSeek,, RawNumInVfmw
	movw	r2, #1023	@ tmp514,
	mov	r3, #0	@,
	and	r2, r2, r6	@ tmp513, tmp514, RawNumToSeek
	and	r3, r3, r7	@,, RawNumToSeek
	mov	lr, r6, lsr #10	@ tmp601, RawNumToSeek,
	orrs	r8, r2, r3	@, tmp513
	orr	r0, lr, r7, asl #22	@, tmp664, tmp601, RawNumToSeek,
	addne	r0, r0, #1	@ SeekTime, tmp664,
	add	r8, r0, #1	@, SeekTime,
	str	r8, [fp, #-100]	@, %sfp
	cmp	r8, #0	@,
	ble	.L1008	@,
	movw	sl, #:lower16:98512	@ tmp623,
	movt	sl, #:upper16:98512	@ tmp623,
	movw	ip, #:lower16:98504	@,
	movw	r6, #:lower16:98508	@,
	movt	ip, #:upper16:98504	@,
	movt	r6, #:upper16:98508	@,
	mov	r9, #0	@,
	str	ip, [fp, #-76]	@, %sfp
	str	r6, [fp, #-64]	@, %sfp
	str	r9, [fp, #-80]	@, %sfp
.L1027:
	mov	r1, #0	@,
	ldr	r0, [fp, #-56]	@, %sfp
	bl	DeleteRawPacketInBuffer	@
	ldr	r0, [fp, #-56]	@, %sfp
	bl	FillRawData	@
	ldr	r1, [fp, #-76]	@, %sfp
	ldr	r3, [fp, #-64]	@, %sfp
	ldr	r2, [r4, r1]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Head
	ldr	r0, [r4, r3]	@ prephitmp.3374, <variable>.RawPacketArray.Tail
	mov	r3, r2	@ i.3392, <variable>.RawPacketArray.Head
	str	r2, [r4, sl]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.History
.L1043:
	add	lr, r3, r3, asl #1	@, tmp532, i.3392, i.3392,
	cmp	r3, r0	@ i.3392, prephitmp.3374
	add	r2, r4, lr, asl #5	@, tmp536, pSmInstArray, tmp532,
	beq	.L1058	@,
.L1009:
	add	r2, r2, #16	@ tmp537, tmp536,
	mvn	r6, #0	@,
	mvn	r7, #0	@,
	add	r5, r2, #200	@ tmp538, tmp537,
	ldrd	r8, [r2, #200]	@ D.52643, tmp537,
	cmp	r9, r7	@ D.52643,
	cmpeq	r8, r6	@ D.52643,
	beq	.L1059	@,
	ldrd	r6, [fp, #-52]	@,,
	add	r1, r3, #1	@ temp.3403, i.3392,
	cmp	r7, r9	@, D.52643
	cmpeq	r6, r8	@, D.52643
	mov	ip, r1, asr #31	@ tmp547, temp.3403,
	bls	.L1016	@,
	mov	r6, ip, lsr #22	@ tmp548, tmp547,
	str	r3, [r4, sl]	@ i.3392, <variable>.RawPacketArray.History
	add	lr, r1, r6	@ tmp549, temp.3403, tmp548
	ldr	r7, [fp, #-64]	@, %sfp
	mov	r3, lr, asl #22	@ tmp550, tmp549,
	ldr	r0, [r4, r7]	@ prephitmp.3374, <variable>.RawPacketArray.Tail
	mov	r9, r3, lsr #22	@ tmp550, tmp550,
	rsb	r3, r6, r9	@ i.3392, tmp548, tmp550
	cmp	r3, r0	@ i.3392, prephitmp.3374
	add	lr, r3, r3, asl #1	@, tmp532, i.3392, i.3392,
	add	r2, r4, lr, asl #5	@, tmp536, pSmInstArray, tmp532,
	bne	.L1009	@,
.L1058:
	ldr	r6, [fp, #-76]	@, %sfp
	ldr	r2, [r4, r6]	@ temp.3399, <variable>.RawPacketArray.Head
	cmp	r3, r2	@ i.3392, temp.3399
	rsblt	r1, r2, #1024	@ tmp527, temp.3399,
	rsbge	r1, r2, r3	@ DelNum.3390, temp.3399, i.3392
	addlt	r1, r1, r3	@ DelNum.3390, tmp527, i.3392
	cmp	r1, #0	@ DelNum.3390,
	streq	r2, [r4, sl]	@ temp.3399, <variable>.RawPacketArray.History
	bne	.L1060	@,
.L1013:
	ldr	r9, [fp, #-80]	@, %sfp
	ldr	r0, [fp, #-100]	@, %sfp
	add	r9, r9, #1	@,,
	str	r9, [fp, #-80]	@, %sfp
	cmp	r9, r0	@,
	blt	.L1027	@,
.L1008:
	mvn	r0, #1	@ D.52571,
	b	.L966	@
.L971:
	add	r5, r5, #1	@ temp.3462, i.3438,
	bl	ReleaseStreamSeg	@
	ldr	r7, [r4, r9]	@ prephitmp.3365, <variable>.StreamSegArray.Tail
	smull	r3, r2, sl, r5	@, tmp401, tmp653, temp.3462
	mov	ip, r5, asr #31	@ tmp404, temp.3462,
	rsb	r0, ip, r2, asr #8	@, i.3438, tmp404, tmp401,
	add	r6, r0, r0, asl #3	@, tmp407, i.3438, i.3438,
	sub	r5, r5, r6, asl #7	@ i.3438, temp.3462, tmp407,
	b	.L1041	@
.L992:
	beq	.L1061	@,
	bcs	.L1042	@,
	movw	r2, #:lower16:98512	@ tmp462,
	movt	r2, #:upper16:98512	@ tmp462,
	mov	ip, r8	@ tmp428, tmp428
	ldr	r1, [r4, r2]	@ i.3426, <variable>.RawPacketArray.History
	add	r9, r1, r1, asl #1	@, tmp465, i.3426, i.3426,
	add	r8, r4, r9, asl #5	@, tmp469, pSmInstArray, tmp465,
	ldrd	r6, [r8, #216]	@, tmp469,
	strd	r6, [fp, #-76]	@,,
	mvn	r6, #0	@ tmp429,
	ldrd	r8, [fp, #-76]	@,,
	mvn	r7, #0	@,
	cmp	r9, r7	@, tmp429
	cmpeq	r8, r6	@, tmp429
	beq	.L1047	@,
	ldrd	r6, [fp, #-52]	@,,
	ldrd	r8, [fp, #-76]	@,,
	cmp	r7, r9	@,
	cmpeq	r6, r8	@,
	bls	.L1000	@,
	subs	r6, r6, r8	@ tmp483, tmp483,
	sbc	r7, r7, r9	@ tmp483, tmp483,
	ldrd	r8, [fp, #-92]	@,,
	cmp	r9, r7	@, tmp483
	cmpeq	r8, r6	@, tmp483
	bcs	.L1000	@,
.L1047:
	str	r3, [r4, r2]	@ i, <variable>.RawPacketArray.History
	ldrd	r0, [ip]	@, <variable>.Pts
	strd	r0, [fp, #-76]	@,,
.L999:
	movw	r6, #:lower16:98504	@ tmp494,
	movt	r6, #:upper16:98504	@ tmp494,
	ldr	r1, [r4, r6]	@ temp.3428, <variable>.RawPacketArray.Head
	cmp	r3, r1	@ i, temp.3428
	rsblt	r1, r1, #1024	@ tmp495, temp.3428,
	rsbge	r3, r1, r3	@ DelNum.3387, temp.3428, i
	addlt	r3, r1, r3	@ DelNum.3387, tmp495, i
	cmp	r3, #0	@ DelNum.3387,
	beq	.L1003	@,
	movw	r2, #:lower16:190744	@ tmp496,
	movt	r2, #:upper16:190744	@ tmp496,
	ldr	r0, [fp, #-64]	@, %sfp
	ldr	r5, [r4, r2]	@ <variable>.SmPushRaw.PushRawNum, <variable>.SmPushRaw.PushRawNum
	cmp	r3, r5	@ DelNum.3387, <variable>.SmPushRaw.PushRawNum
	cmple	r0, #1	@,,
	movne	r5, #0	@, tmp504
	moveq	r5, #1	@, tmp504
	bne	.L1004	@,
.L1003:
	ldrd	r6, [fp, #-76]	@,,
	movw	r2, #:lower16:98504	@ tmp506,
	ldr	r8, [fp, #-60]	@, %sfp
	movt	r2, #:upper16:98504	@ tmp506,
	strd	r6, [r8]	@,
.L1050:
	ldr	r9, [fp, #-64]	@, %sfp
	movw	r3, #:lower16:98512	@ tmp505,
	ldr	lr, [r4, r2]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Head
	movt	r3, #:upper16:98512	@ tmp505,
	movw	ip, #:lower16:190752	@ tmp508,
	movt	ip, #:upper16:190752	@ tmp508,
	mov	r0, #0	@ D.52571,
	str	r9, [r4, ip]	@, <variable>.SmPushRaw.PushRawOver
	str	lr, [r4, r3]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.History
	b	.L966	@
.L974:
	beq	.L1062	@,
	bcs	.L1041	@,
	movw	r3, #:lower16:190704	@ tmp344,
	movt	r3, #:upper16:190704	@ tmp344,
	mvn	r1, #0	@,
	ldr	r2, [r4, r3]	@ i.3451, <variable>.StreamSegArray.History
	add	r6, r2, r2, asl #2	@, tmp348, i.3451, i.3451,
	add	r0, r4, r6, asl #4	@, tmp350, pSmInstArray, tmp348,
	ldrd	r6, [r0, ip]	@ D.52613, tmp350, tmp274
	mvn	r0, #0	@ tmp281,
	cmp	r7, r1	@ D.52613, tmp281
	cmpeq	r6, r0	@ D.52613, tmp281
	beq	.L1045	@,
	ldrd	r0, [fp, #-52]	@,,
	cmp	r1, r7	@, D.52613
	cmpeq	r0, r6	@, D.52613
	bls	.L980	@,
	subs	r6, r0, r6	@ tmp354,, D.52613
	sbc	r7, r1, r7	@ tmp354,, D.52613
	ldrd	r0, [fp, #-92]	@,,
	cmp	r1, r7	@, tmp354
	cmpeq	r0, r6	@, tmp354
	bcc	.L1045	@,
.L980:
	mov	r5, r2	@ i.3438, i.3451
.L979:
	movw	r3, #:lower16:190696	@ tmp356,
	movt	r3, #:upper16:190696	@ tmp356,
	ldr	r6, [r4, r3]	@ j.3394, <variable>.StreamSegArray.Head
	cmp	r5, r6	@ i.3438, j.3394
	moveq	r3, r5	@ j.3393, i.3438
	beq	.L982	@,
	movw	sl, #:lower16:190732	@ tmp648,
	movw	r7, #:lower16:190736	@ tmp650,
	movw	r5, #:lower16:954437177	@ tmp651,
	movw	r9, #:lower16:190704	@ tmp652,
	movt	sl, #:upper16:190732	@ tmp648,
	movt	r7, #:upper16:190736	@ tmp650,
	movt	r5, #:upper16:954437177	@ tmp651,
	movt	r9, #:upper16:190704	@ tmp652,
.L1034:
	add	ip, r6, r6, asl #2	@, tmp360, j.3394, j.3394,
	mov	r1, r6	@, j.3394
	mov	r0, r8	@, pStreamSegArray
	add	lr, r4, ip, asl #4	@, tmp362, pSmInstArray, tmp360,
	mov	ip, #2	@,
	add	r3, lr, #98304	@ tmp373, tmp362,
	add	lr, r3, #232	@ tmp363, tmp363,
	add	r3, r3, #240	@ tmp373, tmp373,
	strb	ip, [lr, #4]	@, <variable>.SegState
	ldr	lr, [r3, #4]	@ <variable>.LenInByte, <variable>.LenInByte
	ldr	r2, [r4, sl]	@ <variable>.StreamSegArray.SegFreshSize, <variable>.StreamSegArray.SegFreshSize
	ldr	ip, [r4, r7]	@ <variable>.StreamSegArray.SegFreshNum, <variable>.StreamSegArray.SegFreshNum
	rsb	r3, lr, r2	@ temp.3455, <variable>.LenInByte, <variable>.StreamSegArray.SegFreshSize
	sub	lr, ip, #1	@ temp.3457, <variable>.StreamSegArray.SegFreshNum,
	bic	r2, r3, r3, asr #31	@ tmp381, temp.3455
	bic	r3, lr, lr, asr #31	@ tmp383, temp.3457
	str	r2, [r4, sl]	@ tmp381, <variable>.StreamSegArray.SegFreshSize
	str	r3, [r4, r7]	@ tmp383, <variable>.StreamSegArray.SegFreshNum
	bl	ReleaseStreamSeg	@
	add	ip, r6, #1	@ temp.3460, j.3394,
	ldr	r3, [r4, r9]	@ j.3393, <variable>.StreamSegArray.History
	smull	r0, r1, r5, ip	@, tmp384, tmp651, temp.3460
	mov	r2, ip, asr #31	@ tmp387, temp.3460,
	rsb	r0, r2, r1, asr #8	@, j.3394, tmp387, tmp384,
	add	r2, r0, r0, asl #3	@, tmp390, j.3394, j.3394,
	sub	r6, ip, r2, asl #7	@ j.3394, temp.3460, tmp390,
	cmp	r3, r6	@ j.3393, j.3394
	bne	.L1034	@,
.L982:
	add	r3, r3, r3, asl #2	@, tmp396, j.3393, j.3393,
	movw	r2, #:lower16:98568	@ tmp393,
	movt	r2, #:upper16:98568	@ tmp393,
	ldr	r1, [fp, #-60]	@, %sfp
	add	r4, r4, r3, asl #4	@, tmp398, pSmInstArray, tmp396,
	mov	r0, #0	@ D.52571,
	ldrd	r2, [r2, r4]	@ <variable>.RawPts, tmp393, tmp398
	strd	r2, [r1]	@ <variable>.RawPts,
	b	.L966	@
.L1055:
	add	r7, r3, #1	@ temp.3419, i,
	mov	r2, r7, asr #31	@ tmp430, temp.3419,
	mov	r0, r2, lsr #22	@ tmp431, tmp430,
	add	r6, r7, r0	@ tmp432, temp.3419, tmp431
	mov	lr, r6, asl #22	@ tmp433, tmp432,
	mov	r3, lr, lsr #22	@ tmp433, tmp433,
	rsb	r3, r0, r3	@ i, tmp431, tmp433
	b	.L1042	@
.L1053:
	add	r5, r5, #1	@ temp.3437, i.3438,
	smull	r1, ip, sl, r5	@, tmp282, tmp653, temp.3437
	mov	r1, r5, asr #31	@ tmp285, temp.3437,
	rsb	r6, r1, ip, asr #8	@, i.3438, tmp285, tmp282,
	add	r0, r6, r6, asl #3	@, tmp288, i.3438, i.3438,
	sub	r5, r5, r0, asl #7	@ i.3438, temp.3437, tmp288,
	b	.L1041	@
.L1057:
	mov	r2, r0	@,
	mov	r3, r1	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC153	@,
	movt	r1, #:upper16:.LC153	@,
	strd	r6, [sp]	@ RawNumInVfmw,
	bl	dprint_vfmw	@
	mvn	r0, #1	@ D.52571,
	b	.L966	@
.L1056:
	movw	r7, #:lower16:98512	@ tmp419,
	movt	r7, #:upper16:98512	@ tmp419,
	ldr	r0, [fp, #-96]	@, %sfp
	str	r2, [r4, r7]	@ temp.3395, <variable>.RawPacketArray.History
	bl	DeleteRawPacket	@
	ldr	r0, [fp, #-56]	@, %sfp
	mov	r1, #0	@,
	bl	DeleteRawPacketInBuffer	@
	b	.L989	@
.L1045:
	str	r5, [r4, r3]	@ i.3438, <variable>.StreamSegArray.History
	b	.L979	@
.L1016:
	beq	.L1063	@,
	bcs	.L1043	@,
	movw	r1, #:lower16:98512	@ tmp562,
	movt	r1, #:upper16:98512	@ tmp562,
	ldr	r0, [r4, r1]	@ i.3409, <variable>.RawPacketArray.History
	add	r7, r0, r0, asl #1	@, tmp565, i.3409, i.3409,
	add	r8, r4, r7, asl #5	@, tmp569, pSmInstArray, tmp565,
	ldrd	r6, [r8, #216]	@, tmp569,
	strd	r6, [fp, #-76]	@,,
	mvn	r6, #0	@ tmp539,
	ldrd	r8, [fp, #-76]	@,,
	mvn	r7, #0	@,
	cmp	r9, r7	@, tmp539
	cmpeq	r8, r6	@, tmp539
	beq	.L1064	@,
	ldrd	r6, [fp, #-52]	@,,
	ldrd	r8, [fp, #-76]	@,,
	cmp	r7, r9	@,
	cmpeq	r6, r8	@,
	bls	.L1023	@,
	subs	r6, r6, r8	@,,
	sbc	r7, r7, r9	@,,
	ldrd	r8, [fp, #-92]	@,,
	cmp	r9, r7	@,
	cmpeq	r8, r6	@,
	bcs	.L1023	@,
	str	r3, [r4, r1]	@ i.3392, <variable>.RawPacketArray.History
	ldrd	r0, [r2, #200]	@, tmp537,
	strd	r0, [fp, #-76]	@,,
.L1022:
	movw	r2, #:lower16:98504	@ tmp592,
	movt	r2, #:upper16:98504	@ tmp592,
	ldr	r6, [r4, r2]	@ temp.3410, <variable>.RawPacketArray.Head
	cmp	r3, r6	@ i.3392, temp.3410
	rsblt	r6, r6, #1024	@ tmp593, temp.3410,
	rsbge	r0, r6, r3	@ DelNum, temp.3410, i.3392
	addlt	r0, r6, r3	@ DelNum, tmp593, i.3392
	cmp	r0, #0	@ DelNum,
	bne	.L1026	@,
	ldrd	r6, [fp, #-76]	@,,
	movw	r1, #:lower16:98504	@ tmp595,
	ldr	r8, [fp, #-60]	@, %sfp
	movt	r1, #:upper16:98504	@ tmp595,
	movw	r3, #:lower16:98512	@ tmp594,
	movt	r3, #:upper16:98512	@ tmp594,
	strd	r6, [r8]	@,
	ldr	lr, [r4, r1]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Head
	str	lr, [r4, r3]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.History
	b	.L966	@
.L1059:
	add	lr, r3, #1	@ D.52602, i.3392,
	mov	r2, lr, asr #31	@ tmp540, D.52602,
	mov	r6, r2, lsr #22	@ tmp541, tmp540,
	add	r3, lr, r6	@ tmp542, D.52602, tmp541
	mov	ip, r3, asl #22	@ tmp543, tmp542,
	mov	r9, ip, lsr #22	@ tmp543, tmp543,
	rsb	r3, r6, r9	@ i.3392, tmp541, tmp543
	b	.L1043	@
.L1061:
	movw	r2, #:lower16:98504	@ tmp444,
	movt	r2, #:upper16:98504	@ tmp444,
	ldr	ip, [r4, r2]	@ temp.3421, <variable>.RawPacketArray.Head
	cmp	r3, ip	@ i, temp.3421
	rsblt	ip, ip, #1024	@ tmp445, temp.3421,
	rsbge	r3, ip, r3	@ DelNum.3391, temp.3421, i
	addlt	r3, ip, r3	@ DelNum.3391, tmp445, i
	cmp	r3, #0	@ DelNum.3391,
	beq	.L996	@,
	movw	r7, #:lower16:190744	@ tmp446,
	movt	r7, #:upper16:190744	@ tmp446,
	ldr	r5, [r4, r7]	@ <variable>.SmPushRaw.PushRawNum, <variable>.SmPushRaw.PushRawNum
	ldr	r7, [fp, #-64]	@, %sfp
	cmp	r3, r5	@ DelNum.3391, <variable>.SmPushRaw.PushRawNum
	cmple	r7, #1	@,,
	movne	r5, #0	@, tmp454
	moveq	r5, #1	@, tmp454
	bne	.L997	@,
.L996:
	ldr	r8, [fp, #-60]	@, %sfp
	movw	r2, #:lower16:98504	@ tmp456,
	movt	r2, #:upper16:98504	@ tmp456,
	strd	r0, [r8]	@ temp.3418,
	b	.L1050	@
.L1063:
	movw	ip, #:lower16:98504	@ tmp554,
	movt	ip, #:upper16:98504	@ tmp554,
	ldr	r1, [r4, ip]	@ temp.3404, <variable>.RawPacketArray.Head
	cmp	r1, r3	@ temp.3404, i.3392
	rsbgt	r1, r1, #1024	@ tmp555, temp.3404,
	rsble	r0, r1, r3	@ DelNum.3388, temp.3404, i.3392
	addgt	r0, r1, r3	@ DelNum.3388, tmp555, i.3392
	cmp	r0, #0	@ DelNum.3388,
	bne	.L1020	@,
	ldr	r1, [fp, #-60]	@, %sfp
	movw	lr, #:lower16:98504	@ tmp557,
	movt	lr, #:upper16:98504	@ tmp557,
	movw	r3, #:lower16:98512	@ tmp556,
	movt	r3, #:upper16:98512	@ tmp556,
	strd	r8, [r1]	@ D.52643,
	ldr	r2, [r4, lr]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Head
	str	r2, [r4, r3]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.History
	b	.L966	@
.L1062:
	movw	ip, #:lower16:190696	@ tmp300,
	movt	ip, #:upper16:190696	@ tmp300,
	ldr	r7, [r4, ip]	@ j.3440, <variable>.StreamSegArray.Head
	cmp	r5, r7	@ i.3438, j.3440
	beq	.L976	@,
	movw	lr, #:lower16:954437177	@ tmp645,
	movt	lr, #:upper16:954437177	@ tmp645,
	movw	r9, #:lower16:190732	@ tmp642,
	movw	sl, #:lower16:190736	@ tmp644,
	movt	r9, #:upper16:190732	@ tmp642,
	movt	sl, #:upper16:190736	@ tmp644,
	str	r6, [fp, #-52]	@ tmp606, %sfp
	mov	r6, lr	@ tmp645, tmp645
.L1033:
	add	ip, r7, r7, asl #2	@, tmp304, j.3440, j.3440,
	mov	r1, r7	@, j.3440
	mov	r0, r8	@, pStreamSegArray
	add	r2, r4, ip, asl #4	@, tmp306, pSmInstArray, tmp304,
	mov	ip, #2	@,
	add	r3, r2, #98304	@ tmp317, tmp306,
	add	r2, r3, #232	@ tmp307, tmp307,
	add	lr, r3, #240	@ tmp317, tmp317,
	strb	ip, [r2, #4]	@, <variable>.SegState
	ldr	r2, [lr, #4]	@ <variable>.LenInByte, <variable>.LenInByte
	ldr	r3, [r4, r9]	@ <variable>.StreamSegArray.SegFreshSize, <variable>.StreamSegArray.SegFreshSize
	ldr	lr, [r4, sl]	@ <variable>.StreamSegArray.SegFreshNum, <variable>.StreamSegArray.SegFreshNum
	rsb	r2, r2, r3	@ temp.3444, <variable>.LenInByte, <variable>.StreamSegArray.SegFreshSize
	sub	r3, lr, #1	@ temp.3446, <variable>.StreamSegArray.SegFreshNum,
	bic	ip, r2, r2, asr #31	@ tmp325, temp.3444
	bic	lr, r3, r3, asr #31	@ tmp327, temp.3446
	str	ip, [r4, r9]	@ tmp325, <variable>.StreamSegArray.SegFreshSize
	str	lr, [r4, sl]	@ tmp327, <variable>.StreamSegArray.SegFreshNum
	bl	ReleaseStreamSeg	@
	add	r1, r7, #1	@ temp.3449, j.3440,
	smull	r0, r2, r6, r1	@, tmp328, tmp645, temp.3449
	mov	ip, r1, asr #31	@ tmp331, temp.3449,
	rsb	r3, ip, r2, asr #8	@, j.3440, tmp331, tmp328,
	add	r0, r3, r3, asl #3	@, tmp334, j.3440, j.3440,
	sub	r7, r1, r0, asl #7	@ j.3440, temp.3449, tmp334,
	cmp	r5, r7	@ i.3438, j.3440
	bne	.L1033	@,
	ldr	r6, [fp, #-52]	@ tmp606, %sfp
.L976:
	add	r5, r6, r5	@ tmp339, tmp606, i.3438
	movw	r3, #:lower16:98568	@ tmp336,
	movt	r3, #:upper16:98568	@ tmp336,
	ldr	r1, [fp, #-60]	@, %sfp
	add	r4, r4, r5, asl #4	@, tmp341, pSmInstArray, tmp339,
	mov	r0, #0	@ D.52571,
	ldrd	r2, [r3, r4]	@ <variable>.RawPts, tmp336, tmp341
	strd	r2, [r1]	@ <variable>.RawPts,
	b	.L966	@
.L1060:
	str	r2, [r4, sl]	@ temp.3399, <variable>.RawPacketArray.History
	ldr	r0, [fp, #-96]	@, %sfp
	bl	DeleteRawPacket	@
	ldr	r0, [fp, #-56]	@, %sfp
	mov	r1, #0	@,
	bl	DeleteRawPacketInBuffer	@
	b	.L1013	@
.L1000:
	mov	r3, r1	@ i, i.3426
	b	.L999	@
.L1023:
	mov	r3, r0	@ i.3392, i.3409
	b	.L1022	@
.L1026:
	ldrd	r6, [fp, #-76]	@,,
	movw	r3, #:lower16:98504	@ tmp598,
	ldr	r8, [fp, #-60]	@, %sfp
	movt	r3, #:upper16:98504	@ tmp598,
	strd	r6, [r8]	@,
.L1048:
	ldr	ip, [r4, r3]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Head
	movw	r2, #:lower16:98512	@ tmp597,
	movt	r2, #:upper16:98512	@ tmp597,
	mov	r1, r0	@, DelNum
	ldr	r0, [fp, #-96]	@, %sfp
	str	ip, [r4, r2]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.History
	bl	DeleteRawPacket	@
	ldr	r0, [fp, #-56]	@, %sfp
	mov	r1, #0	@,
	bl	DeleteRawPacketInBuffer	@
	mov	r0, #0	@ D.52571,
	b	.L966	@
.L1020:
	ldr	ip, [fp, #-60]	@, %sfp
	movw	r3, #:lower16:98504	@ tmp560,
	movt	r3, #:upper16:98504	@ tmp560,
	strd	r8, [ip]	@ D.52643,
	b	.L1048	@
.L1064:
	str	r3, [r4, r1]	@ i.3392, <variable>.RawPacketArray.History
	ldrd	r0, [r5]	@, <variable>.Pts
	strd	r0, [fp, #-76]	@,,
	b	.L1022	@
.L1004:
	ldrd	r6, [fp, #-76]	@,,
	movw	r1, #:lower16:98504	@ tmp510,
	ldr	r8, [fp, #-60]	@, %sfp
	movt	r1, #:upper16:98504	@ tmp510,
	movw	r2, #:lower16:98512	@ tmp509,
	strd	r6, [r8]	@,
	ldr	ip, [r4, r1]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Head
.L1049:
	movt	r2, #:upper16:98512	@ tmp509,
	mov	r1, r3	@, DelNum.3387
	ldr	r0, [fp, #-96]	@, %sfp
	str	ip, [r4, r2]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.History
	bl	DeleteRawPacket	@
	ldr	r0, [fp, #-56]	@, %sfp
	mov	r1, r5	@, tmp504
	bl	DeleteRawPacketInBuffer	@
	mov	r0, r5	@ D.52571, tmp504
	b	.L966	@
.L997:
	ldr	ip, [fp, #-60]	@, %sfp
	movw	lr, #:lower16:98504	@ tmp460,
	movt	lr, #:upper16:98504	@ tmp460,
	movw	r2, #:lower16:98512	@ tmp459,
	strd	r0, [ip]	@ temp.3418,
	ldr	ip, [r4, lr]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Head
	b	.L1049	@
	.fnend
	.size	SM_SeekPts, .-SM_SeekPts
	.align	2
	.global	ScdReturnSegFilter
	.type	ScdReturnSegFilter, %function
ScdReturnSegFilter:
	.fnstart
.LFB1590:
	@ args = 4, pretend = 0, frame = 24
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
	mov	sl, r1	@ pTransFormSeg, pTransFormSeg
	ldr	r1, [r0, #32]	@, <variable>.SegNum
	mov	r4, r0	@ pSegStreamFilter, pSegStreamFilter
	mov	r5, #0	@ tmp169,
	mov	r0, #24	@,
	str	r1, [fp, #-52]	@, %sfp
	movw	r1, #:lower16:.LC154	@,
	str	r5, [r2, #0]	@ tmp169,* pExtraSrcBack
	movt	r1, #:upper16:.LC154	@,
	str	r3, [fp, #-56]	@ pSegNum, %sfp
	ldr	r6, [fp, #4]	@ UpMsgStepNum, UpMsgStepNum
	bl	dprint_vfmw	@
	ldr	r7, [r4, #8]	@ <variable>.ProtocolType, <variable>.ProtocolType
	cmp	r7, #2	@ <variable>.ProtocolType,
	beq	.L1066	@,
	ldr	r2, [fp, #-52]	@, %sfp
	cmp	r2, r5	@,
	ble	.L1067	@,
	ldr	r3, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	mov	r2, r5	@, tmp169
	ldr	r5, [r4, #20]	@ <variable>.SegBufPhyAddr, <variable>.SegBufPhyAddr
	mov	r0, #24	@,
	ldr	r1, [fp, #-52]	@, %sfp
	ldr	ip, [r3, #0]	@ tmp174,* <variable>.pScdUpMsg
	and	r7, r5, #-2147483648	@ tmp175, <variable>.SegBufPhyAddr,
	mov	r5, r6, asl #2	@ D.56709, UpMsgStepNum,
	sub	r9, r1, #1	@ tmp256,,
	bic	r8, ip, #-2147483648	@ tmp173, tmp174,
	movw	r1, #:lower16:.LC155	@,
	orr	r6, r8, r7	@ tmp177, tmp173, tmp175
	str	r6, [sl, #0]	@ tmp177,* pTransFormSeg
	ldr	lr, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	movt	r1, #:upper16:.LC155	@,
	mov	r7, #1	@ i.3529,
	and	r9, r9, #1	@ tmp258, tmp256,
	add	r6, sl, r5	@ ivtmp.3508, pTransFormSeg, D.56709
	mov	r8, r5	@ ivtmp.3507, D.56709
	ldr	ip, [lr, #4]	@ tmp182,
	str	ip, [sl, #4]	@ tmp182,
	ldr	r3, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	ldr	r3, [r3, #0]	@,* <variable>.pScdUpMsg
	bl	dprint_vfmw	@
	ldr	r0, [fp, #-52]	@, %sfp
	cmp	r0, r7	@,
	ble	.L1067	@,
	cmp	r9, #0	@ tmp258,
	beq	.L1068	@,
	ldr	r8, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	mov	r2, r7	@, i.3529
	ldr	r7, [r4, #20]	@ <variable>.SegBufPhyAddr, <variable>.SegBufPhyAddr
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC155	@,
	movt	r1, #:upper16:.LC155	@,
	ldr	lr, [r8, r5]	@ tmp291,* D.56709
	and	ip, r7, #-2147483648	@ tmp294, <variable>.SegBufPhyAddr,
	mov	r7, #2	@ i.3529,
	mov	r8, r5, asl #1	@ ivtmp.3507, D.56709,
	bic	r3, lr, #-2147483648	@ tmp292, tmp291,
	orr	lr, r3, ip	@ tmp295, tmp292, tmp294
	str	lr, [r6, #0]	@ tmp295,* ivtmp.3508
	ldr	r3, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	add	ip, r5, r3	@ tmp297, D.56709, <variable>.pScdUpMsg
	ldr	lr, [ip, #4]	@ tmp299,
	str	lr, [r6, #4]	@ tmp299,
	add	r6, r6, r5	@ ivtmp.3508, ivtmp.3508, D.56709
	ldr	r3, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	ldr	r3, [r3, #4]	@,
	bl	dprint_vfmw	@
	ldr	ip, [fp, #-52]	@, %sfp
	cmp	ip, r7	@, i.3529
	ble	.L1067	@,
.L1068:
	ldr	r3, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	add	lr, r6, r5	@, ivtmp.3508, D.56709
	ldr	sl, [r4, #20]	@ <variable>.SegBufPhyAddr, <variable>.SegBufPhyAddr
	mov	r2, r7	@, i.3529
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC155	@,
	ldr	r9, [r3, r8]	@ tmp264,* ivtmp.3507
	and	ip, sl, #-2147483648	@ tmp267, <variable>.SegBufPhyAddr,
	str	lr, [fp, #-48]	@, %sfp
	movt	r1, #:upper16:.LC155	@,
	bic	lr, r9, #-2147483648	@ tmp265, tmp264,
	add	sl, r8, r5	@ ivtmp.3507, ivtmp.3507, D.56709
	orr	r3, lr, ip	@ tmp268, tmp265, tmp267
	str	r3, [r6, #0]	@ tmp268,* ivtmp.3508
	ldr	lr, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	add	r9, r7, #1	@ tmp259, i.3529,
	add	ip, r8, lr	@ tmp270, ivtmp.3507, <variable>.pScdUpMsg
	add	r8, sl, r5	@ ivtmp.3507, ivtmp.3507, D.56709
	ldr	r3, [ip, #4]	@ tmp272,
	str	r3, [r6, #4]	@ tmp272,
	ldr	lr, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	ldr	r3, [lr, r7, asl #2]	@,* <variable>.pScdUpMsg
	add	r7, r9, #1	@ i.3529, tmp259,
	bl	dprint_vfmw	@
	ldr	ip, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	ldr	r2, [r4, #20]	@ <variable>.SegBufPhyAddr, <variable>.SegBufPhyAddr
	mov	r0, #24	@,
	movw	r1, #:lower16:.LC155	@,
	movt	r1, #:upper16:.LC155	@,
	ldr	r3, [ip, sl]	@ tmp279,* ivtmp.3507
	and	ip, r2, #-2147483648	@ tmp282, <variable>.SegBufPhyAddr,
	mov	r2, r9	@, tmp259
	bic	r3, r3, #-2147483648	@ tmp280, tmp279,
	orr	r3, r3, ip	@ tmp283, tmp280, tmp282
	str	r3, [r6, r5]	@ tmp283,* D.56709
	ldr	r3, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	ldr	ip, [fp, #-48]	@, %sfp
	add	sl, sl, r3	@ tmp285, ivtmp.3507, <variable>.pScdUpMsg
	add	r6, ip, r5	@ ivtmp.3508,, D.56709
	ldr	r3, [sl, #4]	@ tmp287,
	str	r3, [ip, #4]	@ tmp287,
	ldr	ip, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	ldr	r3, [ip, r9, asl #2]	@,* <variable>.pScdUpMsg
	bl	dprint_vfmw	@
	ldr	r2, [fp, #-52]	@, %sfp
	cmp	r2, r7	@, i.3529
	bgt	.L1068	@,
.L1067:
	mov	r0, #0	@ tmp185,
	str	r0, [r4, #16]	@ tmp185, <variable>.LastH263Num
	str	r0, [r4, #12]	@ tmp185, <variable>.ModeFlag
	ldr	r1, [fp, #-52]	@, %sfp
	ldr	r2, [fp, #-56]	@, %sfp
	str	r1, [r2, #0]	@,
.L1069:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1066:
	ldr	r0, [r4, #20]	@, <variable>.SegBufPhyAddr
	bl	MEM_Phy2Vir	@
	subs	r3, r0, #0	@ D.51526,
	bne	.L1090	@,
.L1070:
	mvn	r0, #6	@ D.51529,
	b	.L1069	@
.L1090:
	ldrb	lr, [r3, #1]	@ zero_extendqisi2	@ D.51534,
	ldrb	ip, [r3, #2]	@ zero_extendqisi2	@ D.51539,
	ldr	r0, [r4, #28]	@, <variable>.SegBufRollAddr
	ldrb	r9, [r3, #3]	@ zero_extendqisi2	@ D.51544,
	ldrb	r8, [r3, #0]	@ zero_extendqisi2	@ D.51530,* D.51526
	str	lr, [fp, #-68]	@,
	str	ip, [fp, #-64]	@,
	bl	MEM_Phy2Vir	@
	ldr	r2, [fp, #-68]	@,
	ldr	r3, [fp, #-64]	@,
	cmp	r0, #0	@ D.51547
	beq	.L1070	@,
	orr	r8, r9, r8, asl #24	@, tmp188, D.51544, D.51530,
	mov	r9, sl	@ ivtmp.3522, pTransFormSeg
	orr	ip, r8, r2, asl #16	@, tmp190, tmp188, D.51534,
	mov	sl, r5	@ i, tmp169
	orr	r7, ip, r3, asl #8	@, Data32, tmp190, D.51539,
	mov	r2, r6, asl #2	@, UpMsgStepNum,
	strb	r7, [r0, #3]	@ Data32,
	mov	r5, r7, lsr #16	@ tmp194, Data32,
	str	r2, [fp, #-48]	@, %sfp
	mov	r6, r7, lsr #8	@ tmp196, Data32,
	strb	r5, [r0, #1]	@ tmp194,
	strb	r6, [r0, #2]	@ tmp196,
	mov	r1, r7, lsr #24	@ tmp192, Data32,
	add	r6, r9, #4	@ ivtmp.3525, ivtmp.3522,
	strb	r1, [r0, #0]	@ tmp192,* D.51547
	mov	r7, r9	@ ivtmp.3580, ivtmp.3522
	movw	r0, #:lower16:g_event_report	@,
	mov	r5, #4	@ ivtmp.3524,
	movt	r0, #:upper16:g_event_report	@,
	str	r0, [fp, #-60]	@, %sfp
	b	.L1071	@
.L1092:
	mov	r2, #1	@,
	mov	ip, #0	@,
	str	r2, [r4, #12]	@, <variable>.ModeFlag
	str	ip, [r4, #16]	@, <variable>.LastH263Num
	str	r8, [r7, #0]	@ TmpPhyAddr.3544,* ivtmp.3580
	ldr	lr, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	ldr	r0, [lr, r5]	@ tmp227,* ivtmp.3524
	str	r0, [r6, #0]	@ tmp227,* ivtmp.3525
.L1073:
	ldr	r0, [fp, #-48]	@, %sfp
	add	sl, sl, #1	@ i, i,
	add	r7, r7, r0	@ ivtmp.3580, ivtmp.3580,
	add	r5, r5, r0	@ ivtmp.3524, ivtmp.3524,
	add	r6, r6, r0	@ ivtmp.3525, ivtmp.3525,
.L1071:
	ldr	lr, [fp, #-52]	@, %sfp
	cmp	sl, lr	@ i,
	bge	.L1091	@,
	ldr	r2, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	ldr	r1, [r4, #20]	@ <variable>.SegBufPhyAddr, <variable>.SegBufPhyAddr
	add	r0, r5, r2	@ tmp201, ivtmp.3524, <variable>.pScdUpMsg
	and	r3, r1, #-2147483648	@ tmp205, <variable>.SegBufPhyAddr,
	ldr	lr, [r0, #-4]	@ tmp204,
	bic	r8, lr, #-2147483648	@ tmp203, tmp204,
	orrs	r8, r8, r3	@ TmpPhyAddr.3544, tmp203, tmp205
	beq	.L1070	@,
	mov	r0, r8	@, TmpPhyAddr.3544
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@ D.51559
	beq	.L1070	@,
	ldrb	r1, [r0, #0]	@ zero_extendqisi2	@ tmp208,* D.51559
	ldrb	r3, [r0, #3]	@ zero_extendqisi2	@ tmp207,
	ldrb	ip, [r0, #1]	@ zero_extendqisi2	@ tmp211,
	ldrb	lr, [r0, #2]	@ zero_extendqisi2	@ tmp214,
	orr	r2, r3, r1, asl #24	@, tmp210, tmp207, tmp208,
	orr	r3, r2, ip, asl #16	@, tmp213, tmp210, tmp211,
	movw	ip, #438	@,
	orr	r0, r3, lr, asl #8	@, Data32.3563, tmp213, tmp214,
	cmp	r0, ip	@ Data32.3563,
	cmpne	r0, #288	@, Data32.3563,
	movne	r2, #0	@, tmp223
	moveq	r2, #1	@, tmp223
	beq	.L1092	@,
	bic	r1, r0, #1020	@ tmp228, Data32.3563,
	bic	r3, r1, #3	@ tmp228, tmp228,
	cmp	r3, #32768	@ tmp228,
	beq	.L1093	@,
.L1074:
	str	r8, [r7, #0]	@ TmpPhyAddr.3544,* ivtmp.3580
	ldr	r1, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	ldr	r3, [r1, r5]	@ tmp242,* ivtmp.3524
	str	r3, [r6, #0]	@ tmp242,* ivtmp.3525
	b	.L1073	@
.L1093:
	ldr	r0, [r4, #12]	@ <variable>.ModeFlag, <variable>.ModeFlag
	cmp	r0, #1	@ <variable>.ModeFlag,
	beq	.L1075	@,
	mov	r2, #2	@,
	str	r2, [r4, #12]	@, <variable>.ModeFlag
	str	r8, [r7, #0]	@ TmpPhyAddr.3544,* ivtmp.3580
	ldr	ip, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	ldr	lr, [ip, r5]	@ tmp233,* ivtmp.3524
	str	lr, [r6, #0]	@ tmp233,* ivtmp.3525
	b	.L1073	@
.L1091:
	ldr	r4, [fp, #-56]	@, %sfp
	str	sl, [r4, #0]	@ i,
	mov	r4, #0	@ i.3526,
	ldr	r5, [fp, #-48]	@ D.56728, %sfp
	b	.L1079	@
.L1080:
	ldr	r3, [r3, #0]	@,
	bl	dprint_vfmw	@
.L1079:
	cmp	r4, sl	@ i.3526, i
	add	r9, r9, r5	@ ivtmp.3522, ivtmp.3522, D.56728
	mov	r2, r4	@, i.3526
	movw	r1, #:lower16:.LC155	@,
	mov	r0, #24	@,
	movt	r1, #:upper16:.LC155	@,
	add	r4, r4, #1	@ i.3526, i.3526,
	rsb	r3, r5, r9	@ tmp244, D.56728, ivtmp.3522
	blt	.L1080	@,
	mov	r0, #0	@ D.51529,
	b	.L1069	@
.L1075:
	ldr	r1, [r4, #16]	@ <variable>.LastH263Num, <variable>.LastH263Num
	add	r3, r1, #1	@ D.51583, <variable>.LastH263Num,
	str	r3, [r4, #16]	@ D.51583, <variable>.LastH263Num
	cmp	r3, #12	@ D.51583,
	ble	.L1074	@,
	ldr	r0, [fp, #-60]	@, %sfp
	ldr	ip, [r0, #0]	@ g_event_report.587, g_event_report
	cmp	ip, #0	@ g_event_report.587,
	beq	.L1077	@,
	ldr	r0, [r4, #36]	@, <variable>.SMInstID
	mov	r1, #102	@,
	mov	r3, r2	@,
	blx	ip	@ g_event_report.587
.L1077:
	mov	r2, #2	@,
	str	r2, [r4, #12]	@, <variable>.ModeFlag
	str	r8, [r7, #0]	@ TmpPhyAddr.3544,* ivtmp.3580
	ldr	ip, [r4, #4]	@ <variable>.pScdUpMsg, <variable>.pScdUpMsg
	ldr	lr, [ip, r5]	@ tmp238,* ivtmp.3524
	str	lr, [r6, #0]	@ tmp238,* ivtmp.3525
	b	.L1073	@
	.fnend
	.size	ScdReturnSegFilter, .-ScdReturnSegFilter
	.align	2
	.global	ProcessScdReturn
	.type	ProcessScdReturn, %function
ProcessScdReturn:
	.fnstart
.LFB1595:
	@ args = 0, pretend = 0, frame = 272
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #284
	sub	sp, sp, #284	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	ldrsb	r3, [r0, #5]	@ <variable>.IsWaitSCD, <variable>.IsWaitSCD
	mov	r6, #0	@ tmp189,
	mov	r4, r0	@ pScdInstance, pScdInstance
	cmp	r3, r6	@ <variable>.IsWaitSCD,
	mov	r5, r1	@ ScdId, ScdId
	str	r6, [fp, #-52]	@ tmp189, SegBufAddr
	str	r6, [fp, #-56]	@ tmp189, SegBufLength
	beq	.L1095	@,
	movw	r7, #:lower16:190752	@ tmp192,
	movt	r7, #:upper16:190752	@ tmp192,
	ldr	r0, [r0, r7]	@ <variable>.SmPushRaw.PushRawOver, <variable>.SmPushRaw.PushRawOver
	cmp	r0, #3	@ <variable>.SmPushRaw.PushRawOver,
	beq	.L1148	@,
	movw	r0, #:lower16:-121386976	@,
	movt	r0, #:upper16:-121386976	@,
	bl	MEM_ReadPhyWord	@
	sub	r8, fp, #92	@ tmp201,,
	mov	ip, #2	@ tmp198,
	sub	r0, fp, #172	@,,
	str	ip, [r4, r7]	@ tmp198, <variable>.SmPushRaw.PushRawOver
	mov	r1, #80	@,
	bl	__memzero	@
	sub	r0, fp, #252	@,,
	mov	r1, #80	@,
	bl	__memzero	@
	mov	r0, r8	@, tmp201
	mov	r1, #24	@,
	bl	__memzero	@
	movw	r2, #:lower16:204748	@ tmp204,
	movt	r2, #:upper16:204748	@ tmp204,
	str	r6, [fp, #-64]	@ tmp189, TmpAddr
	str	r6, [fp, #-60]	@ tmp189, SegFreeBufLen
	mov	r0, r8	@, tmp201
	ldr	r3, [r4, r2]	@, <variable>.UpMsgStepNum
	mov	r1, r5	@, ScdId
	str	r3, [fp, #-264]	@, %sfp
	bl	ReadScdStateReg	@
	ldr	ip, [fp, #-76]	@ SmStateReg.ScdRollAddr, SmStateReg.ScdRollAddr
	cmp	ip, #0	@ SmStateReg.ScdRollAddr,
	beq	.L1095	@,
	ldr	ip, [fp, #-80]	@, SmStateReg.ScdNum
	movw	r0, #:lower16:100000	@ tmp541,
	movt	r0, #:upper16:100000	@ tmp541,
	add	r2, r4, #200	@, pScdInstance,
	str	r2, [fp, #-292]	@, %sfp
	str	ip, [fp, #-284]	@, %sfp
	ldr	lr, [fp, #-284]	@, %sfp
	cmp	lr, r0	@, tmp541
	str	lr, [fp, #-48]	@, ScdSegNum
	bls	.L1099	@,
	ldr	r0, [r4, #56]	@ <variable>.Config.VidStd, <variable>.Config.VidStd
	cmp	r0, #0	@ <variable>.Config.VidStd,
	beq	.L1149	@,
.L1099:
	add	r7, r4, #98304	@, pScdInstance,
	add	r6, r7, #224	@,,
	str	r6, [fp, #-268]	@, %sfp
	cmp	r6, #0	@,
	beq	.L1100	@,
	movw	r0, #:lower16:190712	@ tmp211,
	movw	sl, #:lower16:190716	@ tmp214,
	movt	r0, #:upper16:190712	@ tmp211,
	movt	sl, #:upper16:190716	@ tmp214,
	ldr	r9, [r4, r0]	@ <variable>.StreamSegArray.SegBufPhyAddr, <variable>.StreamSegArray.SegBufPhyAddr
	ldr	r8, [r4, sl]	@ <variable>.StreamSegArray.SegBufSize, <variable>.StreamSegArray.SegBufSize
	str	r9, [fp, #-52]	@ <variable>.StreamSegArray.SegBufPhyAddr,
	str	r8, [fp, #-56]	@ <variable>.StreamSegArray.SegBufSize,
.L1100:
	movw	r0, #:lower16:-121386976	@,
	movt	r0, #:upper16:-121386976	@,
	bl	MEM_ReadPhyWord	@
	ldr	r6, [fp, #-48]	@ ScdSegNum, ScdSegNum
	cmp	r6, #1152	@ ScdSegNum,
	movge	r6, #1152	@ D.51813,
	and	r1, r0, #15	@ tmp217,,
	movw	r0, #:lower16:-121386996	@,
	str	r1, [r4, #16]	@ tmp217, <variable>.SegFilter.ProtocolType
	movt	r0, #:upper16:-121386996	@,
	bl	MEM_ReadPhyWord	@
	ldr	r1, [fp, #-264]	@, %sfp
	bl	__aeabi_uidiv	@
	cmp	r6, r0	@ D.51813,
	bhi	.L1150	@,
	ldr	r3, [fp, #-48]	@ ScdSegNum, ScdSegNum
	cmp	r3, #1152	@ ScdSegNum,
	movge	r3, #1152	@ iftmp.599,
.L1102:
	ldr	ip, [fp, #-76]	@, SmStateReg.ScdRollAddr
	movw	r6, #:lower16:190776	@ tmp229,
	movw	r0, #:lower16:190712	@ tmp233,
	movt	r6, #:upper16:190776	@ tmp229,
	movt	r0, #:upper16:190712	@ tmp233,
	movw	r1, #:lower16:190856	@ tmp241,
	movt	r1, #:upper16:190856	@ tmp241,
	add	r9, r4, #190464	@ D.51834, pScdInstance,
	movw	r2, #:lower16:98528	@ tmp232,
	movt	r2, #:upper16:98528	@ tmp232,
	ldr	lr, [fp, #-52]	@ SegBufAddr, SegBufAddr
	add	sl, r4, #8	@, pScdInstance,
	ldr	r8, [r4, r6]	@ <variable>.BufAddrCfg.pUpMsgVirAddr, <variable>.BufAddrCfg.pUpMsgVirAddr
	add	r6, r9, #412	@ D.51834, D.51834,
	ldr	r7, [r4, r0]	@ <variable>.StreamSegArray.SegBufPhyAddr, <variable>.StreamSegArray.SegBufPhyAddr
	ldr	r9, [r4, r1]	@ <variable>.InstID, <variable>.InstID
	mov	r1, r6	@, D.51834
	str	sl, [fp, #-296]	@, %sfp
	rsb	r7, r7, lr	@ tmp234, <variable>.StreamSegArray.SegBufPhyAddr, SegBufAddr
	ldr	sl, [fp, #-56]	@ SegBufLength, SegBufLength
	ldr	r0, [fp, #-296]	@, %sfp
	str	ip, [r4, #36]	@, <variable>.SegFilter.SegBufRollAddr
	ldr	ip, [r4, r2]	@ <variable>.StreamSegArray.pSegBufVirAddr, <variable>.StreamSegArray.pSegBufVirAddr
	sub	r2, fp, #68	@,,
	str	r3, [r4, #40]	@ iftmp.599, <variable>.SegFilter.SegNum
	sub	r3, fp, #48	@,,
	str	r8, [r4, #12]	@ <variable>.BufAddrCfg.pUpMsgVirAddr, <variable>.SegFilter.pScdUpMsg
	add	ip, ip, r7	@ tmp238, <variable>.StreamSegArray.pSegBufVirAddr, tmp234
	str	sl, [r4, #32]	@ SegBufLength, <variable>.SegFilter.SegBufSize
	str	ip, [r4, #8]	@ tmp238, <variable>.SegFilter.pSegBufVirAddr
	str	r9, [r4, #44]	@ <variable>.InstID, <variable>.SegFilter.SMInstID
	str	lr, [r4, #28]	@ SegBufAddr, <variable>.SegFilter.SegBufPhyAddr
	ldr	ip, [fp, #-264]	@, %sfp
	str	ip, [sp, #0]	@,
	bl	ScdReturnSegFilter	@
	cmp	r0, #0	@
	str	r0, [fp, #-272]	@, %sfp
	bne	.L1095	@,
	ldr	r7, [fp, #-48]	@ ScdSegNum.3645, ScdSegNum
	cmp	r7, #1	@ ScdSegNum.3645,
	ble	.L1151	@,
	ldr	r1, [fp, #-272]	@, %sfp
	movw	r0, #:lower16:-121386996	@,
	movt	r0, #:upper16:-121386996	@,
	strb	r1, [r4, #0]	@, <variable>.SegFullFlag
	bl	MEM_ReadPhyWord	@
	ldr	r1, [fp, #-264]	@, %sfp
	bl	__aeabi_uidiv	@
	cmp	r7, r0	@ ScdSegNum.3645,
	bcs	.L1109	@,
	ldr	r3, [fp, #-48]	@ ScdSegNum, ScdSegNum
	ldr	r0, [fp, #-264]	@, %sfp
	sub	r3, r3, #1	@ prephitmp.3618, ScdSegNum,
	str	r3, [fp, #-48]	@ prephitmp.3618, ScdSegNum
	mul	r2, r0, r3	@ tmp278,, prephitmp.3618
	add	r1, r2, #47616	@ tmp279, tmp278,
	add	ip, r1, #103	@ tmp279, tmp279,
	add	lr, r4, ip, asl #2	@, tmp283, pScdInstance, tmp279,
	ldr	r0, [lr, #4]	@ tmp285, <variable>.TransFormSeg
	bic	r2, r0, #-2147483648	@, tmp285,
	str	r2, [fp, #-316]	@, %sfp
.L1110:
	ldr	lr, [r4, #56]	@ <variable>.Config.VidStd, <variable>.Config.VidStd
	cmp	lr, #2	@ <variable>.Config.VidStd,
	beq	.L1113	@,
	ldr	r6, [fp, #-48]	@, ScdSegNum
	str	r6, [fp, #-308]	@, %sfp
.L1114:
	movw	r3, #:lower16:190700	@ tmp298,
	movt	r3, #:upper16:190700	@ tmp298,
	add	r1, r4, #203776	@, pScdInstance,
	movw	lr, #:lower16:98528	@,
	add	r6, r1, #936	@,,
	movt	lr, #:upper16:98528	@,
	str	r6, [fp, #-288]	@, %sfp
	movw	r0, #:lower16:190712	@,
	str	lr, [fp, #-276]	@, %sfp
	movt	r0, #:upper16:190712	@,
	movw	ip, #:lower16:190696	@,
	str	r0, [fp, #-280]	@, %sfp
	movt	ip, #:upper16:190696	@,
	str	ip, [fp, #-304]	@, %sfp
	ldr	r1, [r4, r3]	@, <variable>.StreamSegArray.Tail
	mov	r2, #0	@ ivtmp.3639,
	ldr	r3, [fp, #-308]	@ prephitmp.3759, %sfp
	mov	r6, r2	@ i.3698, ivtmp.3639
	str	r2, [fp, #-300]	@ ivtmp.3639, %sfp
	str	r1, [fp, #-312]	@, %sfp
.L1115:
	cmp	r6, r3	@ i.3698, prephitmp.3759
	bge	.L1152	@,
	ldr	r9, [fp, #-264]	@, %sfp
	add	r8, r2, #1	@, ivtmp.3639,
	str	r8, [fp, #-256]	@, %sfp
	add	r7, r2, r9	@ ivtmp.3652, ivtmp.3639,
	add	r2, r2, #47616	@ tmp300, ivtmp.3639,
	add	r0, r7, #47616	@ tmp306, ivtmp.3652,
	add	sl, r2, #102	@ tmp300, tmp300,
	add	ip, r0, #102	@ tmp306, tmp306,
	add	r9, r8, #47616	@ tmp549,,
	add	r0, r4, sl, asl #2	@, tmp304, pScdInstance, tmp300,
	add	r8, r6, #1	@, i.3698,
	add	r1, r4, ip, asl #2	@, tmp310, pScdInstance, tmp306,
	ldr	ip, [fp, #-52]	@ prephitmp.3676, SegBufAddr
	add	r3, r4, r9, asl #2	@, tmp316, pScdInstance, tmp549,
	ldr	sl, [r1, #4]	@ NextSegPhyAddr, <variable>.TransFormSeg
	ldr	r3, [r3, #412]	@ tmp319, <variable>.TransFormSeg
	cmp	ip, sl	@ prephitmp.3676, NextSegPhyAddr
	str	r8, [fp, #-260]	@, %sfp
	ldr	r8, [r0, #4]	@ CurrSegPhyAddr, <variable>.TransFormSeg
	ldreq	r5, [fp, #-76]	@ SmStateReg.ScdRollAddr, SmStateReg.ScdRollAddr
	mov	r2, r3, lsr #31	@ tmp318, tmp319,
	rsbne	r5, r8, sl	@ SegPacketLen, CurrSegPhyAddr, NextSegPhyAddr
	strb	r2, [fp, #-165]	@ tmp318, SegPacket.DspCheckPicOverFlag
	rsbeq	r5, r8, r5	@ SegPacketLen, CurrSegPhyAddr, SmStateReg.ScdRollAddr
	cmp	r5, #3	@ SegPacketLen,
	ble	.L1118	@,
	ldr	lr, [fp, #-244]	@ LastSegPacket.PhyAddr, LastSegPacket.PhyAddr
	cmp	lr, #0	@ LastSegPacket.PhyAddr,
	bne	.L1153	@,
	ldr	ip, [r4, #56]	@ <variable>.Config.VidStd, <variable>.Config.VidStd
	cmp	ip, #2	@ <variable>.Config.VidStd,
	beq	.L1154	@,
.L1124:
	ldr	r0, [fp, #-280]	@, %sfp
	ldr	r1, [fp, #-276]	@, %sfp
	ldr	r2, [r4, r0]	@ <variable>.StreamSegArray.SegBufPhyAddr, <variable>.StreamSegArray.SegBufPhyAddr
	ldr	ip, [r4, r1]	@ <variable>.StreamSegArray.pSegBufVirAddr, <variable>.StreamSegArray.pSegBufVirAddr
	sub	r1, fp, #64	@,,
	rsb	lr, r2, r8	@ tmp363, <variable>.StreamSegArray.SegBufPhyAddr, CurrSegPhyAddr
	ldr	r0, [fp, #-268]	@, %sfp
	sub	r2, fp, #60	@,,
	add	r3, ip, lr	@ tmp366, <variable>.StreamSegArray.pSegBufVirAddr, tmp363
	str	r5, [fp, #-160]	@ SegPacketLen, SegPacket.LenInByte
	mov	lr, #1	@,
	str	r3, [fp, #-172]	@ tmp366, SegPacket.VirAddr
	strb	lr, [fp, #-167]	@, SegPacket.IsLastSeg
	str	r8, [fp, #-164]	@ CurrSegPhyAddr, SegPacket.PhyAddr
	bl	GetFreeSegBuf	@
	ldr	r3, [fp, #-164]	@ SegPacket.PhyAddr, SegPacket.PhyAddr
	ldr	r2, [fp, #-60]	@ SegFreeBufLen.3671, SegFreeBufLen
	cmp	r3, #0	@ SegPacket.PhyAddr,
	bne	.L1155	@,
.L1125:
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC165	@,
	movt	r1, #:upper16:.LC165	@,
	mov	r5, #1	@ ScdErrFlag,
	bl	dprint_vfmw	@
	ldr	r3, [fp, #-316]	@, %sfp
	ldr	r2, [fp, #-60]	@, SegFreeBufLen
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC166	@,
	movt	r1, #:upper16:.LC166	@,
	bl	dprint_vfmw	@
	ldrb	ip, [fp, #-167]	@ zero_extendqisi2	@ SegPacket.IsLastSeg, SegPacket.IsLastSeg
	movw	r1, #:lower16:.LC160	@,
	mov	r0, #0	@,
	ldr	r2, [fp, #-164]	@, SegPacket.PhyAddr
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [fp, #-160]	@, SegPacket.LenInByte
	str	ip, [sp, #0]	@ SegPacket.IsLastSeg,
	bl	dprint_vfmw	@
.L1122:
	movw	r3, #:lower16:190700	@ tmp516,
	movt	r3, #:upper16:190700	@ tmp516,
	ldr	r2, [fp, #-312]	@, %sfp
	ldr	r0, [r4, r3]	@ <variable>.StreamSegArray.Tail, <variable>.StreamSegArray.Tail
	cmp	r0, r2	@ <variable>.StreamSegArray.Tail,
	movne	r0, #1	@ tmp518,
	moveq	r0, #0	@ tmp520,
	cmp	r6, #0	@ i.3698,
	strb	r0, [r4, #3]	@ tmp520, <variable>.InsertNewSegFlag
	bgt	.L1156	@,
	ldr	ip, [fp, #-308]	@, %sfp
	ldr	r1, [fp, #-284]	@, %sfp
	rsbs	r2, ip, #1	@ tmp537,
	movcc	r2, #0	@ tmp537
	cmp	r1, #1152	@,
	movls	r2, #0	@, tmp537,
	cmp	r2, #0	@ tmp537,
	beq	.L1140	@,
	ldr	r3, [r4, #56]	@ <variable>.Config.VidStd, <variable>.Config.VidStd
	cmp	r3, #2	@ <variable>.Config.VidStd,
	beq	.L1157	@,
.L1140:
	cmp	r5, #1	@ ScdErrFlag,
	bne	.L1097	@,
.L1095:
	mvn	r1, #6	@,
	str	r1, [fp, #-272]	@, %sfp
.L1097:
	ldr	r0, [fp, #-272]	@, %sfp
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1150:
	movw	r0, #:lower16:-121386996	@,
	movt	r0, #:upper16:-121386996	@,
	bl	MEM_ReadPhyWord	@
	ldr	r1, [fp, #-264]	@, %sfp
	bl	__aeabi_uidiv	@
	mov	r3, r0	@ iftmp.599,
	b	.L1102	@
.L1118:
	sub	r2, r5, #1	@ tmp407, SegPacketLen,
	cmp	r2, #2	@ tmp407,
	bhi	.L1127	@,
	ldr	r1, [r4, #56]	@ <variable>.Config.VidStd, <variable>.Config.VidStd
	cmp	r1, #2	@ <variable>.Config.VidStd,
	beq	.L1158	@,
.L1123:
	ldr	r3, [fp, #-48]	@ prephitmp.3759, ScdSegNum
	mov	r2, r7	@ ivtmp.3639, ivtmp.3652
	ldr	r6, [fp, #-260]	@ i.3698, %sfp
	b	.L1115	@
.L1127:
	cmp	r5, #0	@ SegPacketLen,
	beq	.L1123	@,
	ldr	r5, [r4, #56]	@ <variable>.Config.VidStd, <variable>.Config.VidStd
	cmp	r5, #2	@ <variable>.Config.VidStd,
	beq	.L1159	@,
.L1128:
	ldr	r1, [fp, #-280]	@, %sfp
	ldr	lr, [fp, #-276]	@, %sfp
	ldr	r5, [fp, #-76]	@ SmStateReg.ScdRollAddr, SmStateReg.ScdRollAddr
	ldr	r2, [r4, r1]	@ <variable>.StreamSegArray.SegBufPhyAddr, <variable>.StreamSegArray.SegBufPhyAddr
	sub	r1, fp, #64	@,,
	add	r3, sl, r5	@ tmp450, NextSegPhyAddr, SmStateReg.ScdRollAddr
	ldr	r5, [r4, lr]	@ <variable>.StreamSegArray.pSegBufVirAddr, <variable>.StreamSegArray.pSegBufVirAddr
	ldr	r0, [fp, #-268]	@, %sfp
	rsb	lr, r8, r3	@ tmp452, CurrSegPhyAddr, tmp450
	rsb	r3, r2, r8	@ tmp446, <variable>.StreamSegArray.SegBufPhyAddr, CurrSegPhyAddr
	sub	r2, fp, #60	@,,
	add	r3, r5, r3	@ tmp449, <variable>.StreamSegArray.pSegBufVirAddr, tmp446
	rsb	ip, ip, lr	@ tmp453, prephitmp.3676, tmp452
	str	r3, [fp, #-172]	@ tmp449, SegPacket.VirAddr
	mov	lr, #0	@,
	str	ip, [fp, #-160]	@ tmp453, SegPacket.LenInByte
	strb	lr, [fp, #-167]	@, SegPacket.IsLastSeg
	str	r8, [fp, #-164]	@ CurrSegPhyAddr, SegPacket.PhyAddr
	bl	GetFreeSegBuf	@
	ldr	r3, [fp, #-160]	@ SegPacket.LenInByte, SegPacket.LenInByte
	cmp	r3, #3	@ SegPacket.LenInByte,
	ble	.L1123	@,
	ldr	r0, [fp, #-268]	@, %sfp
	cmp	r0, #0	@,
	beq	.L1129	@,
	ldr	lr, [fp, #-304]	@, %sfp
	movw	r5, #:lower16:190700	@,
	movt	r5, #:upper16:190700	@,
	ldr	r3, [r4, lr]	@ <variable>.StreamSegArray.Head, <variable>.StreamSegArray.Head
	ldr	r2, [r4, r5]	@ <variable>.StreamSegArray.Tail, <variable>.StreamSegArray.Tail
	subs	ip, r2, r3	@, <variable>.StreamSegArray.Tail, <variable>.StreamSegArray.Head
	str	ip, [fp, #-300]	@, %sfp
	addmi	ip, ip, #1152	@,,
	strmi	ip, [fp, #-300]	@, %sfp
.L1130:
	ldr	r0, [fp, #-164]	@ D.53796, SegPacket.PhyAddr
	ldr	ip, [fp, #-300]	@, %sfp
	cmp	r0, #0	@ D.53796,
	ldr	r2, [fp, #-60]	@ SegFreeBufLen.3707, SegFreeBufLen
	rsb	r1, ip, #1152	@,,
	str	r1, [fp, #-300]	@, %sfp
	bne	.L1160	@,
.L1131:
	ldr	r5, [fp, #-300]	@, %sfp
	cmp	r5, #1	@,
	ble	.L1161	@,
	movw	r2, #4012	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC161	@,
	movt	r1, #:upper16:.LC161	@,
	bl	dprint_vfmw	@
	ldr	r5, [fp, #-316]	@, %sfp
	movw	r2, #4013	@,
	ldr	r3, [fp, #-60]	@, SegFreeBufLen
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC162	@,
	movt	r1, #:upper16:.LC162	@,
	str	r5, [sp, #0]	@,
	bl	dprint_vfmw	@
	ldrb	ip, [fp, #-247]	@ zero_extendqisi2	@ LastSegPacket.IsLastSeg, LastSegPacket.IsLastSeg
	ldr	r3, [fp, #-244]	@, LastSegPacket.PhyAddr
	movw	r1, #:lower16:.LC163	@,
	movt	r1, #:upper16:.LC163	@,
	mov	r0, #1	@,
	movw	r2, #4014	@,
.L1146:
	ldr	lr, [fp, #-240]	@ LastSegPacket.LenInByte, LastSegPacket.LenInByte
	mov	r5, #1	@ ScdErrFlag,
	str	ip, [sp, #4]	@ LastSegPacket.IsLastSeg,
	str	lr, [sp, #0]	@ LastSegPacket.LenInByte,
	bl	dprint_vfmw	@
	b	.L1122	@
.L1155:
	ldr	r3, [fp, #-172]	@ SegPacket.VirAddr, SegPacket.VirAddr
	cmp	r3, #0	@ SegPacket.VirAddr,
	beq	.L1125	@,
	ldr	lr, [fp, #-160]	@ SegPacket.LenInByte, SegPacket.LenInByte
	cmp	r2, lr	@ SegFreeBufLen.3671, SegPacket.LenInByte
	blt	.L1125	@,
	add	r9, r9, #102	@ tmp372, tmp549,
	ldr	r2, [fp, #-288]	@, %sfp
	sub	r3, fp, #172	@,,
	ldr	r0, [fp, #-292]	@, %sfp
	add	r9, r4, r9, asl #2	@, tmp376, pScdInstance, tmp372,
	ldr	ip, [r9, #4]	@ tmp379, <variable>.TransFormSeg
	bic	r1, ip, #-2147483648	@, tmp379,
	bl	GetSegPts	@
	ldr	r0, [fp, #-268]	@, %sfp
	sub	r1, fp, #172	@,,
	bl	InsertStreamSeg	@
	cmp	r0, #0	@,
	bne	.L1162	@,
	ldr	r6, [r9, #4]	@ tmp394, <variable>.TransFormSeg
	movw	r1, #:lower16:.LC164	@,
	ldrd	r8, [fp, #-148]	@ SegPacket.Pts,,
	mov	r0, #26	@,
	bic	r2, r6, #-2147483648	@, tmp394,
	movt	r1, #:upper16:.LC164	@,
	strd	r8, [sp]	@ SegPacket.Pts,
	bl	dprint_vfmw	@
.L1134:
	ldrb	r6, [fp, #-167]	@ zero_extendqisi2	@ SegPacket.IsLastSeg, SegPacket.IsLastSeg
	movw	r1, #:lower16:.LC160	@,
	ldr	r2, [fp, #-164]	@, SegPacket.PhyAddr
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [fp, #-160]	@, SegPacket.LenInByte
	mov	r0, #26	@,
	str	r6, [sp, #0]	@ SegPacket.IsLastSeg,
	bl	dprint_vfmw	@
	b	.L1123	@
.L1153:
	ldr	r3, [fp, #-240]	@ LastSegPacket.LenInByte, LastSegPacket.LenInByte
	sub	r2, fp, #60	@,,
	ldr	r0, [fp, #-268]	@, %sfp
	sub	r1, fp, #64	@,,
	add	ip, r3, r5	@ tmp324, LastSegPacket.LenInByte, SegPacketLen
	str	ip, [fp, #-240]	@ tmp324, LastSegPacket.LenInByte
	bl	GetFreeSegBuf	@
	ldr	r5, [fp, #-244]	@ LastSegPacket.PhyAddr, LastSegPacket.PhyAddr
	ldr	r2, [fp, #-60]	@ SegFreeBufLen.611, SegFreeBufLen
	cmp	r5, #0	@ LastSegPacket.PhyAddr,
	bne	.L1163	@,
.L1120:
	mov	r2, #3872	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC161	@,
	movt	r1, #:upper16:.LC161	@,
	bl	dprint_vfmw	@
	ldr	r5, [fp, #-316]	@, %sfp
	movw	r2, #3873	@,
	ldr	r3, [fp, #-60]	@, SegFreeBufLen
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC162	@,
	movt	r1, #:upper16:.LC162	@,
	str	r5, [sp, #0]	@,
	bl	dprint_vfmw	@
	movw	r1, #:lower16:.LC163	@,
	mov	r0, #1	@,
	ldrb	ip, [fp, #-247]	@ zero_extendqisi2	@ LastSegPacket.IsLastSeg, LastSegPacket.IsLastSeg
	ldr	r3, [fp, #-244]	@, LastSegPacket.PhyAddr
	movt	r1, #:upper16:.LC163	@,
	movw	r2, #3874	@,
	b	.L1146	@
.L1163:
	ldr	r1, [fp, #-252]	@ LastSegPacket.VirAddr, LastSegPacket.VirAddr
	cmp	r1, #0	@ LastSegPacket.VirAddr,
	beq	.L1120	@,
	ldr	r0, [fp, #-240]	@ LastSegPacket.LenInByte, LastSegPacket.LenInByte
	cmp	r2, r0	@ SegFreeBufLen.611, LastSegPacket.LenInByte
	blt	.L1120	@,
	sub	r1, fp, #252	@,,
	ldr	r0, [fp, #-268]	@, %sfp
	bl	InsertStreamSeg	@
	mov	r1, #80	@,
	mov	r5, r0	@ Ret.3654,
	sub	r0, fp, #252	@,,
	bl	__memzero	@
	cmp	r5, #0	@ Ret.3654,
	bne	.L1164	@,
	add	r8, r4, r9, asl #2	@, tmp341, pScdInstance, tmp549,
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC159	@,
	movt	r1, #:upper16:.LC159	@,
	ldr	r2, [r8, #412]	@ tmp344, <variable>.TransFormSeg
	ldrd	r8, [fp, #-228]	@ LastSegPacket.Pts,,
	bic	r2, r2, #-2147483648	@, tmp344,
	strd	r8, [sp]	@ LastSegPacket.Pts,
	bl	dprint_vfmw	@
	ldrb	r6, [fp, #-247]	@ zero_extendqisi2	@ LastSegPacket.IsLastSeg, LastSegPacket.IsLastSeg
	movw	r1, #:lower16:.LC160	@,
	ldr	r2, [fp, #-244]	@, LastSegPacket.PhyAddr
	movt	r1, #:upper16:.LC160	@,
	ldr	r3, [fp, #-240]	@, LastSegPacket.LenInByte
	mov	r0, #26	@,
	str	r6, [sp, #0]	@ LastSegPacket.IsLastSeg,
	bl	dprint_vfmw	@
	b	.L1123	@
.L1154:
	ldr	r0, [fp, #-296]	@, %sfp
	sub	r1, fp, #172	@,,
	mov	r2, r6	@, i.3698
	ldr	r3, [fp, #-264]	@, %sfp
	bl	ScdParseUpMsgInfo	@
	b	.L1124	@
.L1149:
	ldr	r3, [fp, #-284]	@, %sfp
	movw	r2, #3710	@,
	movw	r1, #:lower16:.LC156	@,
	movt	r1, #:upper16:.LC156	@,
	mvn	lr, #6	@,
	str	lr, [fp, #-272]	@, %sfp
	bl	dprint_vfmw	@
	ldr	r0, [fp, #-292]	@, %sfp
	mov	r1, #1	@,
	bl	DeleteRawPacket	@
	b	.L1097	@
.L1152:
	mov	r5, #0	@ ScdErrFlag,
	b	.L1122	@
.L1160:
	ldr	r3, [fp, #-172]	@ SegPacket.VirAddr, SegPacket.VirAddr
	cmp	r3, #0	@ SegPacket.VirAddr,
	beq	.L1131	@,
	ldr	r3, [fp, #-160]	@ prephitmp.3620, SegPacket.LenInByte
	cmp	r2, r3	@ SegFreeBufLen.3707, prephitmp.3620
	blt	.L1131	@,
	ldr	r2, [fp, #-300]	@, %sfp
	cmp	r2, #1	@,
	ble	.L1132	@,
	add	r9, r9, #102	@ tmp467, tmp549,
	ldr	r1, [fp, #-76]	@ SmStateReg.ScdRollAddr, SmStateReg.ScdRollAddr
	ldr	r2, [fp, #-288]	@, %sfp
	sub	r3, fp, #172	@,,
	add	r9, r4, r9, asl #2	@, tmp471, pScdInstance, tmp467,
	rsb	r5, r0, r1	@ tmp466, D.53796, SmStateReg.ScdRollAddr
	str	r5, [fp, #-160]	@ tmp466, SegPacket.LenInByte
	ldr	lr, [r9, #4]	@ tmp474, <variable>.TransFormSeg
	ldr	r0, [fp, #-292]	@, %sfp
	bic	r1, lr, #-2147483648	@, tmp474,
	bl	GetSegPts	@
	ldr	r0, [fp, #-268]	@, %sfp
	sub	r1, fp, #172	@,,
	bl	InsertStreamSeg	@
	subs	r5, r0, #0	@ Ret.3712,
	bne	.L1165	@,
	ldr	r8, [r9, #4]	@ tmp487, <variable>.TransFormSeg
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC164	@,
	movt	r1, #:upper16:.LC164	@,
	bic	r2, r8, #-2147483648	@, tmp487,
	ldrd	r8, [fp, #-148]	@ SegPacket.Pts,,
	strd	r8, [sp]	@ SegPacket.Pts,
	bl	dprint_vfmw	@
	ldrb	ip, [fp, #-167]	@ zero_extendqisi2	@ SegPacket.IsLastSeg, SegPacket.IsLastSeg
	mov	r0, #26	@,
	ldr	r2, [fp, #-164]	@, SegPacket.PhyAddr
	movw	r1, #:lower16:.LC160	@,
	ldr	r3, [fp, #-160]	@, SegPacket.LenInByte
	movt	r1, #:upper16:.LC160	@,
	str	ip, [sp, #0]	@ SegPacket.IsLastSeg,
	bl	dprint_vfmw	@
	ldr	r1, [fp, #-280]	@, %sfp
	ldr	lr, [fp, #-276]	@, %sfp
	ldr	r3, [fp, #-52]	@ SegBufAddr.3727, SegBufAddr
	ldr	r2, [r4, r1]	@ <variable>.StreamSegArray.SegBufPhyAddr, <variable>.StreamSegArray.SegBufPhyAddr
	sub	r1, fp, #172	@,,
	ldr	ip, [r4, lr]	@ <variable>.StreamSegArray.pSegBufVirAddr, <variable>.StreamSegArray.pSegBufVirAddr
	rsb	sl, r3, sl	@ tmp500, SegBufAddr.3727, NextSegPhyAddr
	rsb	lr, r2, r3	@ tmp496, <variable>.StreamSegArray.SegBufPhyAddr, SegBufAddr.3727
	ldr	r0, [fp, #-268]	@, %sfp
	add	r2, ip, lr	@ tmp499, <variable>.StreamSegArray.pSegBufVirAddr, tmp496
	str	sl, [fp, #-160]	@ tmp500, SegPacket.LenInByte
	mov	ip, #1	@,
	str	r2, [fp, #-172]	@ tmp499, SegPacket.VirAddr
	strb	ip, [fp, #-167]	@, SegPacket.IsLastSeg
	str	r3, [fp, #-164]	@ SegBufAddr.3727, SegPacket.PhyAddr
	bl	InsertStreamSeg	@
	cmp	r0, #0	@,
	beq	.L1134	@,
	ldrb	lr, [fp, #-167]	@ zero_extendqisi2	@ SegPacket.IsLastSeg, SegPacket.IsLastSeg
	movw	r1, #:lower16:.LC158	@,
	ldr	r2, [fp, #-164]	@, SegPacket.PhyAddr
	movt	r1, #:upper16:.LC158	@,
	ldr	r3, [fp, #-160]	@, SegPacket.LenInByte
	mov	r0, #26	@,
	str	lr, [sp, #0]	@ SegPacket.IsLastSeg,
	bl	dprint_vfmw	@
	b	.L1122	@
.L1109:
	movw	r0, #:lower16:-121386996	@,
	movt	r0, #:upper16:-121386996	@,
	bl	MEM_ReadPhyWord	@
	ldr	r1, [fp, #-264]	@, %sfp
	rsb	r0, r1, r0	@,,
	bl	__aeabi_uidiv	@
	sub	r3, r0, #1	@ prephitmp.3618,,
	str	r3, [fp, #-48]	@ prephitmp.3618, ScdSegNum
	cmp	r3, #0	@ prephitmp.3618,
	ldrge	r2, [fp, #-264]	@, %sfp
	movlt	r1, #4	@ prephitmp.3625,
	ldrlt	r3, [fp, #-272]	@ prephitmp.3618, %sfp
	mulge	r1, r2, r3	@ tmp292,, prephitmp.3618
	strlt	r3, [fp, #-48]	@ prephitmp.3618, ScdSegNum
	ldr	r0, [r4, #12]	@ <variable>.SegFilter.pScdUpMsg, <variable>.SegFilter.pScdUpMsg
	addge	r1, r1, #1	@ tmp293, tmp292,
	movge	r1, r1, asl #2	@ prephitmp.3625, tmp293,
	ldr	r2, [r0, r1]	@ tmp296,* prephitmp.3625
	bic	ip, r2, #-2147483648	@, tmp296,
	str	ip, [fp, #-316]	@, %sfp
	b	.L1110	@
.L1159:
	ldr	r0, [fp, #-296]	@, %sfp
	sub	r1, fp, #172	@,,
	mov	r2, r6	@, i.3698
	ldr	r3, [fp, #-264]	@, %sfp
	bl	ScdParseUpMsgInfo	@
	ldr	ip, [fp, #-52]	@ prephitmp.3676, SegBufAddr
	b	.L1128	@
.L1162:
	ldrb	ip, [fp, #-167]	@ zero_extendqisi2	@ SegPacket.IsLastSeg, SegPacket.IsLastSeg
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC158	@,
.L1147:
	movt	r1, #:upper16:.LC158	@,
	ldr	r2, [fp, #-164]	@, SegPacket.PhyAddr
	ldr	r3, [fp, #-160]	@, SegPacket.LenInByte
	mov	r5, #0	@ ScdErrFlag,
	str	ip, [sp, #0]	@ SegPacket.IsLastSeg,
	bl	dprint_vfmw	@
	b	.L1122	@
.L1148:
	mov	r2, #2	@ tmp195,
	mvn	r1, #6	@,
	str	r2, [r4, r7]	@ tmp195, <variable>.SmPushRaw.PushRawOver
	str	r1, [fp, #-272]	@, %sfp
	b	.L1097	@
.L1113:
	mov	r1, r6	@, D.51834
	mov	r0, r4	@, pScdInstance
	ldr	r2, [fp, #-268]	@, %sfp
	str	r5, [sp, #0]	@ ScdId,
	bl	GetNextVop	@
	str	r0, [fp, #-308]	@, %sfp
	str	r0, [fp, #-48]	@, ScdSegNum
	b	.L1114	@
.L1129:
	movw	r1, #:lower16:.LC167	@,
	ldr	r2, .L1166	@,
	movt	r1, #:upper16:.LC167	@,
	movw	r3, #3969	@,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	b	.L1130	@
.L1157:
	mov	r2, r1	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC169	@,
	movt	r1, #:upper16:.LC169	@,
	bl	dprint_vfmw	@
	ldr	r0, [fp, #-292]	@, %sfp
	mov	r1, #1	@,
	bl	DeleteRawPacket	@
	b	.L1140	@
.L1164:
	ldrb	lr, [fp, #-247]	@ zero_extendqisi2	@ LastSegPacket.IsLastSeg, LastSegPacket.IsLastSeg
	movw	r1, #:lower16:.LC158	@,
	ldr	r2, [fp, #-244]	@, LastSegPacket.PhyAddr
	movt	r1, #:upper16:.LC158	@,
	ldr	r3, [fp, #-240]	@, LastSegPacket.LenInByte
	mov	r0, #26	@,
	mov	r5, #0	@ ScdErrFlag,
	str	lr, [sp, #0]	@ LastSegPacket.IsLastSeg,
	bl	dprint_vfmw	@
	b	.L1122	@
.L1156:
	ldr	r0, [fp, #-264]	@, %sfp
	mul	r3, r0, r6	@ tmp522,, i.3698
	ldr	r0, [fp, #-292]	@, %sfp
	add	r2, r3, #47616	@ tmp523, tmp522,
	add	lr, r2, #103	@ tmp523, tmp523,
	add	ip, r4, lr, asl #2	@, tmp527, pScdInstance, tmp523,
	ldr	r1, [ip, #4]	@ tmp530, <variable>.TransFormSeg
	bic	r1, r1, #-2147483648	@, tmp530,
	bl	DeleteRawLen	@
	cmp	r0, #0	@,
	beq	.L1140	@,
	b	.L1095	@
.L1151:
	movw	r2, #:lower16:204720	@ tmp247,
	movw	ip, #:lower16:204724	@ tmp248,
	movt	r2, #:upper16:204720	@ tmp247,
	movt	ip, #:upper16:204724	@ tmp248,
	ldr	lr, [r4, r2]	@ <variable>.PrevCfgRawSize, <variable>.PrevCfgRawSize
	ldr	r3, [r4, ip]	@ <variable>.PrevCfgSegSize, <variable>.PrevCfgSegSize
	cmp	lr, r3	@ <variable>.PrevCfgRawSize, <variable>.PrevCfgSegSize
	ldrle	r1, [fp, #-272]	@, %sfp
	movgt	r3, #1	@ tmp251,
	strgtb	r3, [r4, #0]	@ tmp251, <variable>.SegFullFlag
	strleb	r1, [r4, #0]	@, <variable>.SegFullFlag
	cmp	r7, #0	@ ScdSegNum.3645,
	bne	.L1106	@,
	movw	r0, #:lower16:190748	@ tmp255,
	movt	r0, #:upper16:190748	@ tmp255,
	ldr	r1, [r4, r0]	@ SrcEaten.3646, <variable>.SmPushRaw.PushRawTotalLen
	cmp	r1, #3	@ SrcEaten.3646,
	subgt	r1, r1, #3	@ SrcEaten, SrcEaten.3646,
	bgt	.L1108	@,
.L1107:
	mov	r1, #0	@ SrcEaten,
.L1108:
	ldr	r0, [fp, #-292]	@, %sfp
	bl	DeleteRawLen	@
	cmp	r0, #0	@
	str	r0, [fp, #-272]	@, %sfp
	bne	.L1095	@,
	b	.L1097	@
.L1158:
	mov	r0, sl	@, NextSegPhyAddr
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@ D.51970
	beq	.L1095	@,
	ldrb	lr, [r0, #0]	@ zero_extendqisi2	@ tmp410,* D.51970
	ldrb	r2, [r0, #3]	@ zero_extendqisi2	@ tmp409,
	ldrb	r1, [r0, #1]	@ zero_extendqisi2	@ tmp413,
	ldrb	ip, [r0, #2]	@ zero_extendqisi2	@ tmp416,
	orr	r3, r2, lr, asl #24	@, tmp412, tmp409, tmp410,
	orr	lr, r3, r1, asl #16	@, tmp415, tmp412, tmp413,
	orr	r3, lr, ip, asl #8	@, tmp418, tmp415, tmp416,
	bic	r0, r3, #255	@ tmp419, tmp418,
	cmp	r0, #256	@ tmp419,
	beq	.L1123	@,
	mov	r2, r6	@, i.3698
	ldr	r3, [fp, #-264]	@, %sfp
	sub	r1, fp, #252	@,,
	ldr	r0, [fp, #-296]	@, %sfp
	bl	ScdParseUpMsgInfo	@
	ldr	r0, [fp, #-280]	@, %sfp
	ldr	r1, [fp, #-276]	@, %sfp
	mov	lr, #1	@,
	ldr	r2, [r4, r0]	@ <variable>.StreamSegArray.SegBufPhyAddr, <variable>.StreamSegArray.SegBufPhyAddr
	ldr	ip, [r4, r1]	@ <variable>.StreamSegArray.pSegBufVirAddr, <variable>.StreamSegArray.pSegBufVirAddr
	sub	r1, fp, #64	@,,
	rsb	r3, r2, r8	@ tmp425, <variable>.StreamSegArray.SegBufPhyAddr, CurrSegPhyAddr
	ldr	r0, [fp, #-268]	@, %sfp
	sub	r2, fp, #60	@,,
	add	r6, ip, r3	@ tmp428, <variable>.StreamSegArray.pSegBufVirAddr, tmp425
	str	r5, [fp, #-240]	@ SegPacketLen, LastSegPacket.LenInByte
	str	r6, [fp, #-252]	@ tmp428, LastSegPacket.VirAddr
	strb	lr, [fp, #-247]	@, LastSegPacket.IsLastSeg
	str	r8, [fp, #-244]	@ CurrSegPhyAddr, LastSegPacket.PhyAddr
	bl	GetFreeSegBuf	@
	ldr	r0, [fp, #-256]	@, %sfp
	ldr	r2, [fp, #-288]	@, %sfp
	add	r3, r0, #47616	@ tmp431,,
	ldr	r0, [fp, #-292]	@, %sfp
	add	r1, r3, #102	@ tmp431, tmp431,
	sub	r3, fp, #252	@,,
	add	ip, r4, r1, asl #2	@, tmp435, pScdInstance, tmp431,
	ldr	r6, [ip, #4]	@ tmp438, <variable>.TransFormSeg
	bic	r1, r6, #-2147483648	@, tmp438,
	bl	GetSegPts	@
	b	.L1123	@
.L1106:
	cmp	r7, #1	@ ScdSegNum.3645,
	bne	.L1107	@,
	movw	r5, #:lower16:190716	@ tmp257,
	movt	r5, #:upper16:190716	@ tmp257,
	mov	lr, #3	@ tmp260,
	movw	ip, #:lower16:190880	@ tmp256,
	ldr	r0, [r4, r5]	@ <variable>.StreamSegArray.SegBufSize, <variable>.StreamSegArray.SegBufSize
	movt	ip, #:upper16:190880	@ tmp256,
	movw	r5, #:lower16:190748	@ tmp265,
	movt	r5, #:upper16:190748	@ tmp265,
	ldr	r1, [r4, ip]	@ SrcEaten, <variable>.TransFormSeg
	mul	r3, lr, r0	@ tmp258, tmp260, <variable>.StreamSegArray.SegBufSize
	ldr	r2, [r4, r5]	@ <variable>.SmPushRaw.PushRawTotalLen, <variable>.SmPushRaw.PushRawTotalLen
	rsb	lr, r1, r2	@ tmp266, SrcEaten, <variable>.SmPushRaw.PushRawTotalLen
	cmp	r3, #0	@ tmp258,
	add	ip, r3, #3	@ tmp263, tmp258,
	movlt	r3, ip	@ tmp262, tmp263
	cmp	lr, r3, asr #2	@ tmp266, tmp262,
	ble	.L1108	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC157	@,
	movt	r1, #:upper16:.LC157	@,
	bl	dprint_vfmw	@
	ldr	r1, [r4, r5]	@ SrcEaten, <variable>.SmPushRaw.PushRawTotalLen
	b	.L1108	@
.L1165:
	ldrb	ip, [fp, #-167]	@ zero_extendqisi2	@ SegPacket.IsLastSeg, SegPacket.IsLastSeg
	mov	r0, #26	@,
	movw	r1, #:lower16:.LC158	@,
	b	.L1147	@
.L1161:
	ldr	r3, [fp, #-160]	@ prephitmp.3620, SegPacket.LenInByte
.L1132:
	ldrb	ip, [fp, #-167]	@ zero_extendqisi2	@ SegPacket.IsLastSeg, SegPacket.IsLastSeg
	mov	r2, r0	@, D.53796
	movw	r1, #:lower16:.LC168	@,
	mov	r0, #26	@,
	movt	r1, #:upper16:.LC168	@,
	mov	r5, #0	@ ScdErrFlag,
	str	ip, [sp, #0]	@ SegPacket.IsLastSeg,
	bl	dprint_vfmw	@
	b	.L1122	@
.L1167:
	.align	2
.L1166:
	.word	.LANCHOR1+372
	.fnend
	.size	ProcessScdReturn, .-ProcessScdReturn
	.align	2
	.global	SM_CopyRawToSeg
	.type	SM_CopyRawToSeg, %function
SM_CopyRawToSeg:
	.fnstart
.LFB1576:
	@ args = 0, pretend = 0, frame = 48
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
	add	r0, r0, r0, asl #1	@, tmp171, SmID, SmID,
	movw	r2, #:lower16:.LANCHOR0	@ tmp167,
	movt	r2, #:upper16:.LANCHOR0	@ tmp167,
	add	r3, r2, r0, asl #4	@, tmp173, tmp167, tmp171,
	mov	r5, r1	@ pStreamSeg, pStreamSeg
	ldr	r4, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r4, #0	@ pSmInstArray,
	bne	.L1191	@,
.L1169:
	mvn	r0, #0	@ D.50856,
.L1175:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1191:
	cmp	r1, #0	@ pStreamSeg,
	beq	.L1169	@,
	movw	ip, #:lower16:98508	@ tmp175,
	movw	r1, #:lower16:98504	@ tmp176,
	movt	ip, #:upper16:98508	@ tmp175,
	movt	r1, #:upper16:98504	@ tmp176,
	ldr	r0, [r4, ip]	@ D.50863, <variable>.RawPacketArray.Tail
	ldr	r3, [r4, r1]	@, <variable>.RawPacketArray.Head
	cmp	r0, r3	@ D.50863,
	str	r3, [fp, #-48]	@, %sfp
	beq	.L1170	@,
	mov	r1, r3, asl #1	@ tmp423,,
	mov	r6, #1	@ rawnum,
	add	r9, r1, r3	@ tmp180, tmp423, index
	add	r8, r4, r9, asl #5	@, tmp182, pSmInstArray, tmp180,
	mov	r9, r5	@ pStreamSeg, pStreamSeg
	ldr	r7, [r8, #208]	@, <variable>.Length
	str	r7, [fp, #-68]	@, %sfp
	mov	r8, r7	@ TotalSrcLength,
	b	.L1171	@
.L1172:
	mov	r2, r2, lsr #22	@ index, index,
	cmp	r0, ip	@ D.50863, index
	add	r3, r2, #1	@ D.50871, index,
	add	r6, r6, #1	@ rawnum, rawnum,
	add	ip, r2, r2, asl #1	@, tmp446, index, index,
	ldr	r1, [r7, #208]	@ D.50873, <variable>.Length
	mov	r3, r3, asl #22	@ index, D.50871,
	beq	.L1170	@,
	movw	r5, #1025	@,
	cmp	r6, r5	@ rawnum,
	add	ip, r4, ip, asl #5	@, tmp448, pSmInstArray, tmp446,
	mov	r3, r3, lsr #22	@ index, index,
	add	r8, r8, r1	@ TotalSrcLength, TotalSrcLength, D.50873
	mov	r5, r6	@ tmp434, rawnum
	beq	.L1170	@,
	ldrb	sl, [r7, #252]	@ zero_extendqisi2	@ <variable>.is_not_last_packet_flag, <variable>.is_not_last_packet_flag
	mov	r1, r3, asl #1	@ tmp426, index,
	add	r7, r1, r3	@ tmp459, tmp426, index
	cmp	sl, #0	@ <variable>.is_not_last_packet_flag,
	add	r7, r4, r7, asl #5	@, tmp461, pSmInstArray, tmp459,
	beq	.L1190	@,
	cmp	r0, r2	@ D.50863, index
	add	r6, r6, #1	@ rawnum, rawnum,
	ldr	r2, [ip, #208]	@ D.50873, <variable>.Length
	beq	.L1170	@,
	ldrb	ip, [ip, #252]	@ zero_extendqisi2	@ <variable>.is_not_last_packet_flag, <variable>.is_not_last_packet_flag
	add	r8, r8, r2	@ TotalSrcLength, TotalSrcLength, D.50873
	cmp	ip, #0	@ <variable>.is_not_last_packet_flag,
	beq	.L1190	@,
	cmp	r0, r3	@ D.50863, index
	add	r6, r5, #2	@ rawnum, tmp434,
	ldr	r2, [r7, #208]	@ D.50873, <variable>.Length
	beq	.L1170	@,
	add	r8, r8, r2	@ TotalSrcLength, TotalSrcLength, D.50873
.L1171:
	add	r2, r1, r3	@ tmp437, tmp426, index
	add	r7, r3, #1	@ D.50871, index,
	mov	ip, r7, asl #22	@ index, D.50871,
	add	r7, r4, r2, asl #5	@, tmp439, pSmInstArray, tmp437,
	mov	ip, ip, lsr #22	@ index, index,
	ldrb	r3, [r7, #252]	@ zero_extendqisi2	@ <variable>.is_not_last_packet_flag, <variable>.is_not_last_packet_flag
	add	r2, ip, #1	@ D.50871, index,
	add	r1, ip, ip, asl #1	@, tmp188, index, index,
	cmp	r3, #0	@ <variable>.is_not_last_packet_flag,
	mov	r2, r2, asl #22	@ index, D.50871,
	add	r7, r4, r1, asl #5	@, tmp190, pSmInstArray, tmp188,
	bne	.L1172	@,
.L1190:
	add	lr, r4, #98304	@, pSmInstArray,
	str	r8, [fp, #-68]	@ TotalSrcLength, %sfp
	add	r8, lr, #224	@,,
	mov	r5, r9	@ pStreamSeg, pStreamSeg
	str	r8, [fp, #-52]	@, %sfp
	add	r9, r4, #200	@, pSmInstArray,
	mov	r0, r8	@,
	str	r9, [fp, #-64]	@, %sfp
	bl	ResetStreamSegArray	@
	movw	r3, #:lower16:190716	@ tmp202,
	movt	r3, #:upper16:190716	@ tmp202,
	ldr	ip, [fp, #-68]	@, %sfp
	movw	r7, #:lower16:98528	@ tmp201,
	movt	r7, #:upper16:98528	@ tmp201,
	ldr	r1, [r4, r3]	@ <variable>.StreamSegArray.SegBufSize, <variable>.StreamSegArray.SegBufSize
	sub	r0, r1, #262144	@ tmp203, <variable>.StreamSegArray.SegBufSize,
	cmp	r0, ip	@ tmp203,
	blt	.L1192	@,
	ldr	r3, [r4, #56]	@ prephitmp.3779, <variable>.Config.VidStd
	movw	r2, #:lower16:190712	@ tmp208,
	movt	r2, #:upper16:190712	@ tmp208,
	ldr	sl, [r4, r7]	@ TmpVirAddr, <variable>.StreamSegArray.pSegBufVirAddr
	cmp	r3, #10	@ prephitmp.3779,
	cmpne	r3, #12	@, prephitmp.3779,
	ldr	ip, [r4, r2]	@ TmpPhyAddr, <variable>.StreamSegArray.SegBufPhyAddr
	bne	.L1176	@,
	movw	r0, #:lower16:g_VdmCharacter	@ tmp424,
	movt	r0, #:upper16:g_VdmCharacter	@ tmp424,
	ldr	r2, [r0, #0]	@ g_VdmCharacter, g_VdmCharacter
	ands	lr, r2, #1	@ tmp218, g_VdmCharacter,
	streqb	lr, [sl], #1	@ tmp218,
	ldr	r7, [fp, #-48]	@, %sfp
	mov	r2, #96	@ tmp224,
	ldreq	r3, [r4, #56]	@ prephitmp.3779, <variable>.Config.VidStd
	mla	r1, r2, r7, r4	@ tmp225, tmp224,, pSmInstArray
	cmp	r3, #12	@ prephitmp.3779,
	movw	r3, #:lower16:98504	@ tmp232,
	movt	r3, #:upper16:98504	@ tmp232,
	ldr	r7, [r4, r3]	@ index.3806, <variable>.RawPacketArray.Head
	ldr	r3, [r1, #208]	@ SrcLength, <variable>.Length
	ldr	r1, [r1, #204]	@ SrcVirAddr, <variable>.VirAddr
	bne	.L1178	@,
	ldr	r0, [r0, #0]	@ g_VdmCharacter, g_VdmCharacter
	cmp	r3, #0	@ SrcLength,
	moveq	r0, #0	@, tmp241
	andne	r0, r0, #1	@,, tmp241, g_VdmCharacter
	cmp	r0, #0	@ tmp241,
	beq	.L1178	@,
	cmp	r3, #2	@ SrcLength,
	addgt	r1, r1, #3	@ SrcVirAddr, SrcVirAddr,
	subgt	r3, r3, #3	@ SrcLength, SrcLength,
	ble	.L1193	@,
.L1178:
	str	ip, [r5, #8]	@ TmpPhyAddr, <variable>.PhyAddr
	mov	r0, ip	@, TmpPhyAddr
	str	r1, [fp, #-84]	@,
	str	r3, [fp, #-80]	@,
	bl	MEM_Phy2Vir	@
	ldr	r8, [fp, #-48]	@, %sfp
	mov	r3, #6	@ tmp301,
	mov	r2, #3	@ tmp317,
	cmp	r6, #0	@ rawnum,
	mul	r1, r3, r8	@ tmp300, tmp301,
	mul	r3, r2, r8	@ tmp316, tmp317,
	add	ip, r1, #1	@ tmp302, tmp300,
	add	r1, r4, ip, asl #4	@, tmp305, pSmInstArray, tmp302,
	add	ip, r4, r3, asl #5	@, tmp321, pSmInstArray, tmp316,
	str	r0, [r5, #0]	@ D.50934, <variable>.VirAddr
	rsb	r9, r0, sl	@ tmp299, D.50934, TmpVirAddr
	str	r9, [r5, #12]	@ tmp299, <variable>.LenInByte
	mov	r0, #1	@ tmp324,
	ldrd	r8, [r1, #200]	@, tmp305,
	strd	r8, [r5, #24]	@, pStreamSeg,
	ldrd	r2, [r1, #200]	@, tmp305,
	strd	r2, [r5, #32]	@, pStreamSeg,
	ldrd	r8, [ip, #232]	@, tmp321,
	strb	r0, [r5, #5]	@ tmp324, <variable>.IsLastSeg
	strd	r8, [r5, #40]	@, pStreamSeg,
	ldr	r1, [fp, #-84]	@,
	ldr	r3, [fp, #-80]	@,
	beq	.L1181	@,
	cmp	r1, #0	@ SrcVirAddr,
	cmpne	sl, #0	@, TmpVirAddr,
	beq	.L1170	@,
	add	r8, ip, #240	@, tmp429,
	mov	r9, #0	@,
	mov	lr, r7, asl r0	@ tmp425, index.3806,
	str	r9, [fp, #-48]	@, %sfp
	add	r9, ip, #264	@ tmp432, tmp429,
	add	ip, ip, #256	@ tmp431, tmp429,
	str	r8, [fp, #-56]	@, %sfp
	mov	r8, r4	@ pSmInstArray, pSmInstArray
	str	r6, [fp, #-60]	@ rawnum, %sfp
	mov	r4, ip	@ tmp431, tmp431
	str	r3, [fp, #-88]	@ SrcLength, %sfp
	mov	ip, lr	@ tmp425, tmp425
	b	.L1182	@
.L1183:
	adds	sl, sl, r6	@ TmpVirAddr, TmpVirAddr, SrcLength.537
	moveq	r0, #0	@, tmp334
	movne	r0, #1	@, tmp334
	cmp	r1, #0	@ SrcVirAddr,
	moveq	r0, #0	@, tmp339
	andne	r0, r0, #1	@,, tmp339, tmp334
	cmp	r0, #0	@ tmp339,
	beq	.L1170	@,
.L1182:
	ldr	r6, [fp, #-88]	@ SrcLength.537, %sfp
	mov	r0, sl	@, TmpVirAddr
	str	ip, [fp, #-80]	@,
	mov	r2, r6	@, SrcLength.537
	bl	memcpy	@
	ldr	r1, [fp, #-80]	@,
	ldr	ip, [fp, #-48]	@, %sfp
	add	r0, r7, #1	@ temp.3825, index.3806,
	add	r3, r1, r7	@ tmp347, tmp425, index.3806
	ldr	r1, [fp, #-60]	@, %sfp
	mov	r7, r0, asl #22	@ index.3806, temp.3825,
	add	r0, ip, #1	@,,
	add	ip, r8, r3, asl #5	@, tmp349, pSmInstArray, tmp347,
	ldr	r2, [r5, #12]	@ <variable>.LenInByte, <variable>.LenInByte
	cmp	r1, r0	@,
	str	r0, [fp, #-48]	@, %sfp
	ldrb	r1, [ip, #253]	@ zero_extendqisi2	@ <variable>.is_stream_end_flag, <variable>.is_stream_end_flag
	add	r2, r2, r6	@ tmp354, <variable>.LenInByte, SrcLength.537
	mov	r7, r7, lsr #22	@ index.3806, index.3806,
	str	r2, [r5, #12]	@ tmp354, <variable>.LenInByte
	strb	r1, [r5, #6]	@ <variable>.is_stream_end_flag, <variable>.IsStreamEnd
	mov	ip, r7, asl #1	@ tmp425, index.3806,
	ldr	r1, [fp, #-56]	@, %sfp
	add	r2, ip, r7	@ tmp359, tmp425, index.3806
	add	r2, r8, r2, asl #5	@, tmp361, pSmInstArray, tmp359,
	ldrd	r0, [r1]	@, <variable>.DispTime
	strd	r0, [fp, #-76]	@,,
	ldr	r3, [r2, #208]	@, <variable>.Length
	str	r3, [fp, #-88]	@, %sfp
	ldr	r1, [r2, #204]	@ SrcVirAddr, <variable>.VirAddr
	ldrd	r2, [fp, #-76]	@,,
	strd	r2, [r5, #48]	@, pStreamSeg,
	ldr	r2, [r4, #0]	@ <variable>.DispEnableFlag, <variable>.DispEnableFlag
	str	r2, [r5, #56]	@ <variable>.DispEnableFlag, <variable>.DispEnableFlag
	ldr	r2, [r4, #4]	@ <variable>.DispFrameDistance, <variable>.DispFrameDistance
	str	r2, [r5, #60]	@ <variable>.DispFrameDistance, <variable>.DispFrameDistance
	ldr	r2, [r9, #0]	@ <variable>.DistanceBeforeFirstFrame, <variable>.DistanceBeforeFirstFrame
	str	r2, [r5, #64]	@ <variable>.DistanceBeforeFirstFrame, <variable>.DistanceBeforeFirstFrame
	ldr	r2, [r9, #4]	@ <variable>.GopNum, <variable>.GopNum
	str	r2, [r5, #68]	@ <variable>.GopNum, <variable>.GopNum
	bhi	.L1183	@,
.L1181:
	mov	r1, r5	@, pStreamSeg
	ldr	r0, [fp, #-52]	@, %sfp
	bl	InsertStreamSeg	@
	ldr	r0, [fp, #-64]	@, %sfp
	ldr	r1, [fp, #-68]	@, %sfp
	bl	DeleteRawLen	@
	mov	r0, #0	@ D.50856,
	b	.L1175	@
.L1170:
	mvn	r0, #3	@ D.50856,
	b	.L1175	@
.L1176:
	ldr	r8, [fp, #-48]	@, %sfp
	mov	r7, #96	@ tmp413,
	movw	r9, #:lower16:98504	@ tmp421,
	movt	r9, #:upper16:98504	@ tmp421,
	mla	lr, r7, r8, r4	@ tmp414, tmp413,, pSmInstArray
	ldr	r7, [r4, r9]	@ index.3806, <variable>.RawPacketArray.Head
	ldr	r3, [lr, #208]	@ SrcLength, <variable>.Length
	ldr	r1, [lr, #204]	@ SrcVirAddr, <variable>.VirAddr
	b	.L1178	@
.L1192:
	mov	r2, ip	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC170	@,
	movt	r1, #:upper16:.LC170	@,
	bl	dprint_vfmw	@
	ldr	r0, [fp, #-64]	@, %sfp
	ldr	r1, [fp, #-68]	@, %sfp
	bl	DeleteRawLen	@
	cmp	r0, #0	@ D.50885
	beq	.L1175	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC127	@,
	movw	r2, #2301	@,
	movt	r1, #:upper16:.LC127	@,
	bl	dprint_vfmw	@
	mov	r0, #0	@ D.50856,
	b	.L1175	@
.L1193:
	cmp	r6, #1	@ rawnum,
	beq	.L1170	@,
	add	r0, r7, #1	@ temp.3811, index.3806,
	mov	r7, r0, asl #22	@ index.3806, temp.3811,
	mov	r7, r7, lsr #22	@ index.3806, index.3806,
	mla	r1, r2, r7, r4	@ tmp246, tmp224, index.3806, pSmInstArray
	ldr	lr, [r1, #208]	@ <variable>.Length, <variable>.Length
	ldr	r1, [r1, #204]	@ SrcVirAddr.3814, <variable>.VirAddr
	add	r3, r3, lr	@ SrcLength.3813, SrcLength, <variable>.Length
	cmp	r3, #2	@ SrcLength.3813,
	ble	.L1180	@,
	add	r9, r7, #1020	@ tmp254, index.3806,
	sub	r3, r3, #3	@ SrcLength, SrcLength.3813,
	add	r8, r9, #3	@ tmp254, tmp254,
	sub	r6, r6, #1	@ rawnum, rawnum,
	mov	r0, r8, asl #22	@ tmp256, tmp254,
	mov	lr, r0, lsr #22	@ tmp256, tmp256,
	mla	r2, r2, lr, r4	@ tmp261, tmp224, tmp256, pSmInstArray
	ldr	r9, [r2, #208]	@ <variable>.Length, <variable>.Length
	rsb	r8, r9, #3	@ tmp263, <variable>.Length,
	add	r1, r1, r8	@ SrcVirAddr, SrcVirAddr.3814, tmp263
	b	.L1178	@
.L1180:
	cmp	r6, #2	@ rawnum,
	beq	.L1170	@,
	add	r0, r7, #1	@ temp.3815, index.3806,
	mov	r7, r0, asl #22	@ index.3806, temp.3815,
	mov	r7, r7, lsr #22	@ index.3806, index.3806,
	mla	r1, r2, r7, r4	@ tmp269, tmp224, index.3806, pSmInstArray
	ldr	lr, [r1, #208]	@ <variable>.Length, <variable>.Length
	ldr	r9, [r1, #204]	@ SrcVirAddr.3818, <variable>.VirAddr
	add	r3, r3, lr	@ SrcLength.3817, SrcLength.3813, <variable>.Length
	cmp	r3, #2	@ SrcLength.3817,
	ble	.L1170	@,
	add	r0, r7, #1020	@ tmp277, index.3806,
	sub	r3, r3, #3	@ SrcLength, SrcLength.3817,
	add	r8, r0, #3	@ tmp277, tmp277,
	add	lr, r0, #2	@ tmp288, tmp288,
	sub	r6, r6, #2	@ rawnum, rawnum,
	mov	r0, r8, asl #22	@ tmp279, tmp277,
	mov	r1, lr, asl #22	@ tmp290, tmp288,
	mov	r8, r0, lsr #22	@ tmp279, tmp279,
	mov	lr, r1, lsr #22	@ tmp290, tmp290,
	mla	r0, r2, r8, r4	@ tmp284, tmp224, tmp279, pSmInstArray
	mla	r8, r2, lr, r4	@ tmp295, tmp224, tmp290, pSmInstArray
	ldr	r1, [r0, #208]	@ <variable>.Length, <variable>.Length
	ldr	r2, [r8, #208]	@ <variable>.Length, <variable>.Length
	rsb	lr, r1, #3	@ tmp286, <variable>.Length,
	rsb	r8, r2, lr	@ tmp297, <variable>.Length, tmp286
	add	r1, r9, r8	@ SrcVirAddr, SrcVirAddr.3818, tmp297
	b	.L1178	@
	.fnend
	.size	SM_CopyRawToSeg, .-SM_CopyRawToSeg
	.align	2
	.global	SM_ReadStreamSeg
	.type	SM_ReadStreamSeg, %function
SM_ReadStreamSeg:
	.fnstart
.LFB1578:
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
	mov	r7, r0	@ SmID, SmID
	add	r2, r7, r7, asl #1	@, tmp144, SmID, SmID,
	movw	r0, #:lower16:.LANCHOR0	@ tmp140,
	movt	r0, #:upper16:.LANCHOR0	@ tmp140,
	subs	r6, r1, #0	@ pStreamSeg, pStreamSeg
	add	r3, r0, r2, asl #4	@, tmp146, tmp140, tmp144,
	ldr	r5, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	bne	.L1202	@,
.L1195:
	mvn	r4, #0	@ ret,
.L1200:
	mov	r0, r4	@, ret
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L1202:
	cmp	r5, #0	@ pSmInstArray,
	beq	.L1195	@,
	ldr	r3, [r5, #56]	@ D.51057, <variable>.Config.VidStd
	sub	r1, r3, #8	@ tmp148, D.51057,
	cmp	r3, #5	@ D.51057,
	cmpne	r1, #1	@, tmp148,
	bls	.L1196	@,
	cmp	r3, #4	@ D.51057,
	beq	.L1196	@,
	cmp	r3, #10	@ D.51057,
	beq	.L1196	@,
	cmp	r3, #14	@ D.51057,
	beq	.L1196	@,
	cmp	r3, #11	@ D.51057,
	beq	.L1196	@,
	cmp	r3, #12	@ D.51057,
	beq	.L1196	@,
	cmp	r3, #13	@ D.51057,
	beq	.L1196	@,
	cmp	r3, #1	@ D.51057,
	bne	.L1197	@,
	ldr	r4, [r5, #72]	@ <variable>.Config.StdExt.Vc1Ext.IsAdvProfile, <variable>.Config.StdExt.Vc1Ext.IsAdvProfile
	cmp	r4, #0	@ <variable>.Config.StdExt.Vc1Ext.IsAdvProfile,
	bne	.L1197	@,
.L1196:
	mov	r0, r7	@, SmID
	mov	r1, r6	@, pStreamSeg
	bl	SM_CopyRawToSeg	@
	cmp	r0, #0	@,
	bne	.L1203	@,
.L1197:
	add	ip, r5, #98304	@, pSmInstArray,
	mov	r1, r6	@, pStreamSeg
	add	r0, ip, #224	@,,
	bl	GetStreamSeg	@
	subs	r4, r0, #0	@ ret,
	beq	.L1204	@,
.L1198:
	movw	r3, #:lower16:204740	@ tmp168,
	movt	r3, #:upper16:204740	@ tmp168,
	ldr	r2, [r5, r3]	@ <variable>.numReadSegFail, <variable>.numReadSegFail
	add	r0, r2, #1	@ tmp171, <variable>.numReadSegFail,
	str	r0, [r5, r3]	@ tmp171, <variable>.numReadSegFail
	b	.L1200	@
.L1204:
	movw	r8, #:lower16:vfmw_save_seg_file	@ tmp160,
	movt	r8, #:upper16:vfmw_save_seg_file	@ tmp160,
	ldr	lr, [r8, r7, asl #2]	@ tmp161, vfmw_save_seg_file
	cmp	lr, #0	@ tmp161,
	beq	.L1199	@,
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	ldr	r2, [r8, r7, asl #2]	@, vfmw_save_seg_file
	ldr	r1, [r6, #12]	@, <variable>.LenInByte
	ldr	r0, [r6, #0]	@, <variable>.VirAddr
	bl	klib_fwrite	@
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
.L1199:
	movw	ip, #:lower16:204740	@ tmp173,
	movt	ip, #:upper16:204740	@ tmp173,
	mov	r1, #0	@ tmp174,
	str	r1, [r5, ip]	@ tmp174, <variable>.numReadSegFail
	b	.L1200	@
.L1203:
	movw	r1, #:lower16:.LC171	@,
	mov	r0, #26	@,
	movt	r1, #:upper16:.LC171	@,
	mvn	r4, #6	@ ret,
	bl	dprint_vfmw	@
	b	.L1198	@
	.fnend
	.size	SM_ReadStreamSeg, .-SM_ReadStreamSeg
	.align	2
	.global	WriteHexFile
	.type	WriteHexFile, %function
WriteHexFile:
	.fnstart
.LFB1529:
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
	subs	r6, r1, #0	@ ScdId, ScdId
	mov	r5, r0	@ eVidStd, eVidStd
	ldmnefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	movw	r4, #:lower16:.LANCHOR0	@ tmp178,
	movt	r4, #:upper16:.LANCHOR0	@ tmp178,
	ldr	r0, [r4, #1000]	@, g_hex_base_addr
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@,
	beq	.L1216	@,
	cmp	r5, #6	@ eVidStd,
	beq	.L1217	@,
	cmp	r5, #0	@ eVidStd,
	bne	.L1210	@,
	ldr	r1, .L1219	@,
	mov	r2, #17920	@,
	bl	memcpy	@
.L1209:
	ldr	ip, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	mov	r1, #4480	@,
	add	r0, ip, #264	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	ldr	r3, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	ldr	r1, [r4, #1000]	@, g_hex_base_addr
	add	r0, r3, #268	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	ldr	r2, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	mov	r1, #0	@,
	add	r0, r2, #256	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
	ldr	r0, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	mov	r1, #1	@,
	add	r0, r0, #256	@, s_RegPhyBaseAddr,
	bl	MEM_WritePhyWord	@
.L1211:
	movw	r0, #:lower16:-121388796	@,
	movt	r0, #:upper16:-121388796	@,
	bl	MEM_ReadPhyWord	@
	and	r0, r0, #1	@ tmp170,,
	cmp	r0, #1	@ tmp170,
	bne	.L1211	@,
	cmp	r5, #6	@ eVidStd,
	beq	.L1218	@,
	cmp	r5, #0	@ eVidStd,
	movw	r3, #:lower16:g_DspDrvState	@ tmp173,
	movt	r3, #:upper16:g_DspDrvState	@ tmp173,
	movne	r2, #0	@ tmp176,
	streq	r0, [r3, #0]	@ tmp170, g_DspDrvState
	strne	r2, [r3, #0]	@ tmp176, g_DspDrvState
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1210:
	mov	r0, r6	@, ScdId
	movw	r1, #:lower16:.LC173	@,
	movt	r1, #:upper16:.LC173	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1217:
	movw	r1, #:lower16:.LANCHOR2	@,
	mov	r2, #17920	@,
	movt	r1, #:upper16:.LANCHOR2	@,
	bl	memcpy	@
	b	.L1209	@
.L1218:
	movw	lr, #:lower16:g_DspDrvState	@ tmp171,
	movt	lr, #:upper16:g_DspDrvState	@ tmp171,
	mov	r1, #2	@ tmp172,
	str	r1, [lr, #0]	@ tmp172, g_DspDrvState
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1216:
	ldr	r2, [r4, #1000]	@, g_hex_base_addr
	movw	r1, #:lower16:.LC172	@,
	movt	r1, #:upper16:.LC172	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1220:
	.align	2
.L1219:
	.word	.LANCHOR3+1552
	.fnend
	.size	WriteHexFile, .-WriteHexFile
	.align	2
	.global	WriteCabacTabDsp
	.type	WriteCabacTabDsp, %function
WriteCabacTabDsp:
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
	addne	r4, r0, #5120	@ D.57157, p,
	movwne	r3, #:lower16:g_CabacMN	@ ivtmp.3920,
	movtne	r3, #:upper16:g_CabacMN	@ ivtmp.3920,
	beq	.L1228	@,
.L1223:
	ldr	ip, [r3, #0]	@ tmp144, g_CabacMN
	add	lr, r3, #32	@ tmp153, ivtmp.3920,
	add	r2, r0, #32	@ tmp152, p,
	str	ip, [r0, #0]	@ tmp144,* p
	ldr	r1, [r3, #4]	@ tmp145, g_CabacMN
	str	r1, [r0, #4]	@ tmp145,
	ldr	ip, [r3, #8]	@ tmp146, g_CabacMN
	str	ip, [r0, #8]	@ tmp146,
	ldr	r1, [r3, #12]	@ tmp147, g_CabacMN
	str	r1, [r0, #12]	@ tmp147,
	ldr	ip, [r3, #16]	@ tmp148, g_CabacMN
	str	ip, [r0, #16]	@ tmp148,
	ldr	r1, [r3, #20]	@ tmp149, g_CabacMN
	str	r1, [r0, #20]	@ tmp149,
	ldr	ip, [r3, #24]	@ tmp150, g_CabacMN
	str	ip, [r0, #24]	@ tmp150,
	ldr	r1, [r3, #28]	@ tmp151, g_CabacMN
	str	r1, [r0, #28]	@ tmp151,
	ldr	ip, [r3, #32]	@ tmp156, g_CabacMN
	add	r3, lr, #32	@ ivtmp.3920, tmp153,
	str	ip, [r0, #32]	@ tmp156,
	add	r0, r2, #32	@ p, tmp152,
	ldr	r1, [lr, #4]	@ tmp157, g_CabacMN
	cmp	r0, r4	@ p, D.57157
	str	r1, [r2, #4]	@ tmp157,
	ldr	ip, [lr, #8]	@ tmp158, g_CabacMN
	str	ip, [r2, #8]	@ tmp158,
	ldr	r1, [lr, #12]	@ tmp159, g_CabacMN
	str	r1, [r2, #12]	@ tmp159,
	ldr	ip, [lr, #16]	@ tmp160, g_CabacMN
	str	ip, [r2, #16]	@ tmp160,
	ldr	r1, [lr, #20]	@ tmp161, g_CabacMN
	str	r1, [r2, #20]	@ tmp161,
	ldr	ip, [lr, #24]	@ tmp162, g_CabacMN
	str	ip, [r2, #24]	@ tmp162,
	ldr	r1, [lr, #28]	@ tmp163, g_CabacMN
	str	r1, [r2, #28]	@ tmp163,
	bne	.L1223	@,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L1228:
	movw	r1, #:lower16:.LC174	@,
	mov	r2, #112	@,
	movt	r1, #:upper16:.LC174	@,
	mov	r0, #22	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	WriteCabacTabDsp, .-WriteCabacTabDsp
	.align	2
	.global	SM_OpenSCDDrv
	.type	SM_OpenSCDDrv, %function
SM_OpenSCDDrv:
	.fnstart
.LFB1568:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp240,
	cmp	r2, #1	@ ScdId,
	movt	r4, #:upper16:.LANCHOR0	@ tmp240,
	movw	r3, #:lower16:-121389056	@ tmp163,
	mov	r5, r0	@ MemAddr, MemAddr
	movt	r3, #:upper16:-121389056	@ tmp163,
	mov	r6, r1	@ MemSize, MemSize
	str	r3, [r4, #1004]	@ tmp163, s_RegPhyBaseAddr_1
	str	r3, [r4, #868]	@ tmp163, s_RegPhyBaseAddr
	bls	.L1242	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC175	@,
	ldr	r2, .L1248	@,
	movt	r1, #:upper16:.LC175	@,
	bl	dprint_vfmw	@
	mvn	r0, #6	@ D.50503,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1242:
	bne	.L1233	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC176	@,
	ldr	r2, .L1248	@,
	movt	r1, #:upper16:.LC176	@,
	movw	r3, #1652	@,
	bl	dprint_vfmw	@
	mvn	r0, #6	@ D.50503,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1233:
	movw	r0, #:lower16:g_vdm_hal_fun_ptr	@ tmp173,
	movt	r0, #:upper16:g_vdm_hal_fun_ptr	@ tmp173,
	ldr	r3, [r0, #8]	@ D.50507, g_vdm_hal_fun_ptr.pfun_SCDDRV_OpenHardware
	cmp	r3, #0	@ D.50507,
	beq	.L1234	@,
	mov	r0, #0	@,
	blx	r3	@ D.50507
.L1235:
	ldr	r1, [r4, #848]	@ <variable>.IsScdDrvOpen, <variable>.IsScdDrvOpen
	movw	r4, #:lower16:.LANCHOR0	@ tmp175,
	movt	r4, #:upper16:.LANCHOR0	@ tmp175,
	cmp	r1, #1	@ <variable>.IsScdDrvOpen,
	beq	.L1236	@,
	mov	r0, #0	@,
	mov	sl, r0	@ tmp180,
	bl	ResetSCD	@
	mov	r1, #96	@,
	add	r0, r4, #772	@, tmp175,
	bl	__memzero	@
	add	ip, r5, #3	@ tmp183, MemAddr,
	bic	r8, ip, #3	@ tmp184, tmp183,
	movw	r0, #:lower16:g_VfmwGlobalStat	@ tmp181,
	rsb	r8, r5, r8	@ Offset, MemAddr, tmp184
	movt	r0, #:upper16:g_VfmwGlobalStat	@ tmp181,
	add	r3, r8, r5	@ D.50528, Offset, MemAddr
	str	sl, [r4, #768]	@ tmp180, s_eScdDrvSleepStage
	str	sl, [r0, #76]	@ tmp180, <variable>.u32SaScdLoad
	mov	r0, r3	@, D.50528
	str	r3, [r4, #780]	@ D.50528, <variable>.ScdDrvMem.DownMsgMemAddr
	str	r5, [r4, #772]	@ MemAddr, <variable>.ScdDrvMem.HwMemAddr
	str	r6, [r4, #776]	@ MemSize, <variable>.ScdDrvMem.HwMemSize
	bl	MEM_Phy2Vir	@
	add	r1, r8, #12288	@ D.50533, Offset,
	mov	r2, #12288	@ tmp190,
	add	ip, r1, r5	@ temp.3969, D.50533, MemAddr
	str	r2, [r4, #788]	@ tmp190, <variable>.ScdDrvMem.DownMsgMemSize
	str	ip, [r4, #792]	@ temp.3969, <variable>.ScdDrvMem.UpMsgMemAddr
	str	r0, [r4, #784]	@, <variable>.ScdDrvMem.pDownMsgMemVirAddr
	mov	r0, ip	@, temp.3969
	bl	MEM_Phy2Vir	@
	add	r3, r8, #21504	@ Offset.3970, Offset,
	add	ip, r3, r5	@ temp.3971, Offset.3970, MemAddr
	mov	r1, #9216	@ tmp194,
	str	ip, [r4, #804]	@ temp.3971, <variable>.ScdDrvMem.DvmMemAddr
	str	r1, [r4, #800]	@ tmp194, <variable>.ScdDrvMem.UpMsgMemSize
	str	r0, [r4, #796]	@, <variable>.ScdDrvMem.pUpMsgMemVirAddr
	mov	r0, ip	@, temp.3971
	bl	MEM_Phy2Vir	@
	cmp	r0, sl	@ D.50539,
	str	r0, [r4, #808]	@ D.50539, <variable>.ScdDrvMem.pDvmMemVirAddr
	beq	.L1243	@,
	mov	r1, #512	@,
	add	r8, r8, #22016	@ Offset.3972, Offset,
	bl	__memzero	@
	add	r0, r8, r5	@ temp.3973, Offset.3972, MemAddr
	mov	r1, #512	@ tmp201,
	str	r0, [r4, #816]	@ temp.3973, <variable>.ScdDrvMem.DspSedTopMemAddr
	str	r1, [r4, #812]	@ tmp201, <variable>.ScdDrvMem.DvmMemSize
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@ D.50551,
	str	r0, [r4, #820]	@ D.50551, <variable>.ScdDrvMem.pDspSedTopMemVirAddr
	beq	.L1244	@,
	mov	r7, #278528	@ tmp208,
	str	r7, [r4, #824]	@ tmp208, <variable>.ScdDrvMem.DspSedTopMemSize
	mov	r1, r7	@, tmp208
	bl	__memzero	@
	add	r0, r8, r7	@ Offset.3974, Offset.3972,
	add	r0, r0, r5	@ temp.3975, Offset.3974, MemAddr
	str	r0, [r4, #828]	@ temp.3975, <variable>.ScdDrvMem.DspCaMnMemAddr
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@ D.50563,
	str	r0, [r4, #832]	@ D.50563, <variable>.ScdDrvMem.pDspCaMnMemVirAddr
	beq	.L1245	@,
	mov	r1, r7	@, tmp208
	add	r8, r8, #557056	@ Offset.3976, Offset.3972,
	bl	__memzero	@
	ldr	r0, [r4, #828]	@, <variable>.ScdDrvMem.DspCaMnMemAddr
	str	r7, [r4, #836]	@ tmp208, <variable>.ScdDrvMem.DspCaMnMemSize
	bl	WriteCabacTabDsp	@
	add	r1, r8, r5	@ tmp218, Offset.3976, MemAddr
	add	r2, r1, #127	@ tmp219, tmp218,
	bic	r0, r2, #127	@ g_hex_base_addr.506, tmp219,
	str	r0, [r4, #1000]	@ g_hex_base_addr.506, g_hex_base_addr
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@ D.50580,
	str	r0, [r4, #1008]	@ D.50580, g_hex_base_vir_addr
	beq	.L1246	@,
	add	r8, r8, #17920	@ D.50588, Offset.3976,
	ldr	lr, [r4, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	cmp	r6, r8	@ MemSize, D.50588
	mov	r3, #17920	@ tmp227,
	str	sl, [r4, #844]	@ tmp180, <variable>.ScdDrvMem.ScdResetRegAddr
	str	r3, [r4, #1012]	@ tmp227, g_hex_len
	str	lr, [r4, #840]	@ s_RegPhyBaseAddr, <variable>.ScdDrvMem.ScdRegAddr
	bge	.L1247	@,
.L1236:
	mvn	r0, #6	@ D.50503,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1234:
	mov	r0, r3	@, D.50507
	movw	r1, #:lower16:.LC56	@,
	movw	r2, #1656	@,
	movt	r1, #:upper16:.LC56	@,
	bl	dprint_vfmw	@
	b	.L1235	@
.L1246:
	movw	r1, #:lower16:.LC180	@,
	ldr	r2, .L1248	@,
	movt	r1, #:upper16:.LC180	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50503,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1247:
	ldr	ip, [r4, #784]	@ <variable>.ScdDrvMem.pDownMsgMemVirAddr, <variable>.ScdDrvMem.pDownMsgMemVirAddr
	cmp	ip, #0	@ <variable>.ScdDrvMem.pDownMsgMemVirAddr,
	beq	.L1236	@,
	ldr	r2, [r4, #796]	@ <variable>.ScdDrvMem.pUpMsgMemVirAddr, <variable>.ScdDrvMem.pUpMsgMemVirAddr
	cmp	r2, #0	@ <variable>.ScdDrvMem.pUpMsgMemVirAddr,
	movne	r2, #1	@ tmp238,
	movne	r0, sl	@ D.50503, tmp180
	strne	r2, [r4, #848]	@ tmp238, <variable>.IsScdDrvOpen
	ldmnefd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	b	.L1236	@
.L1245:
	movw	r1, #:lower16:.LC179	@,
	ldr	r2, .L1248	@,
	movt	r1, #:upper16:.LC179	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50503,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1243:
	movw	r1, #:lower16:.LC177	@,
	ldr	r2, .L1248	@,
	movt	r1, #:upper16:.LC177	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50503,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1244:
	movw	r1, #:lower16:.LC178	@,
	ldr	r2, .L1248	@,
	movt	r1, #:upper16:.LC178	@,
	bl	dprint_vfmw	@
	mvn	r0, #0	@ D.50503,
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L1249:
	.align	2
.L1248:
	.word	.LANCHOR1+392
	.fnend
	.size	SM_OpenSCDDrv, .-SM_OpenSCDDrv
	.align	2
	.global	SM_GiveThreadEvent
	.type	SM_GiveThreadEvent, %function
SM_GiveThreadEvent:
	.fnstart
.LFB1580:
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
	mov	r6, r0	@ SmID, SmID
	bl	OSAL_GetTimeInMs	@
	movw	r4, #:lower16:.LANCHOR0	@ tmp160,
	movt	r4, #:upper16:.LANCHOR0	@ tmp160,
	mov	r5, r0	@ CurTime,
	add	r0, r6, r6, asl #1	@, tmp145, SmID, SmID,
	add	r3, r4, r0, asl #4	@, tmp147, tmp160, tmp145,
	ldr	r3, [r3, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	r3, #0	@ pSmInstArray,
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	ldrsb	r7, [r3, #3]	@ <variable>.InsertNewSegFlag, <variable>.InsertNewSegFlag
	cmp	r7, #1	@ <variable>.InsertNewSegFlag,
	beq	.L1257	@,
.L1252:
	mov	r7, #0	@ prephitmp.4004,
.L1253:
	ldr	r2, [r4, #1016]	@ LastEventTime.549, LastEventTime
	movw	r1, #:lower16:.LANCHOR0	@ tmp150,
	movt	r1, #:upper16:.LANCHOR0	@ tmp150,
	cmp	r5, r2	@ CurTime, LastEventTime.549
	strls	r5, [r1, #1016]	@ CurTime, LastEventTime
	movls	r2, #1	@ prephitmp.3993,
	bls	.L1255	@,
	rsb	r2, r2, r5	@ tmp151, LastEventTime.549, CurTime
	cmp	r2, #1	@ tmp151,
	movls	r2, #0	@, prephitmp.3993
	movhi	r2, #1	@, prephitmp.3993
.L1255:
	tst	r2, r7	@ prephitmp.3993, prephitmp.4004
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	movw	r0, #:lower16:g_IntEvent	@,
	movt	r0, #:upper16:g_IntEvent	@,
	bl	OSAL_GiveEvent	@
	str	r5, [r4, #1016]	@ CurTime, LastEventTime
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L1257:
	mov	r0, r6	@, SmID
	bl	VCTRL_GetDecParam	@
	cmp	r0, #0	@,
	bne	.L1252	@,
	mov	r0, r6	@, SmID
	bl	VCTRL_IsChanSegEnough	@
	cmp	r0, #0	@,
	beq	.L1253	@,
	b	.L1252	@
	.fnend
	.size	SM_GiveThreadEvent, .-SM_GiveThreadEvent
	.align	2
	.global	SM_SCDIntServeProc
	.type	SM_SCDIntServeProc, %function
SM_SCDIntServeProc:
	.fnstart
.LFB1609:
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
	subs	r4, r0, #0	@ ScdId, ScdId
	ble	.L1259	@,
	mov	ip, #0	@ tmp151,
	movw	r1, #:lower16:.LC181	@,
	mov	r3, r4	@, ScdId
	mov	r0, ip	@, tmp151
	movt	r1, #:upper16:.LC181	@,
	ldr	r2, .L1281	@,
	str	ip, [sp, #0]	@ tmp151,
	bl	dprint_vfmw	@
.L1273:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L1259:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinLockIRQ	@
	movw	r0, #:lower16:-121386944	@,
	movt	r0, #:upper16:-121386944	@,
	bl	MEM_ReadPhyWord	@
	tst	r0, #1	@,
	beq	.L1275	@,
	movw	r5, #:lower16:.LANCHOR0	@ tmp342,
	movt	r5, #:upper16:.LANCHOR0	@ tmp342,
	mov	r1, #1	@,
	mov	r8, r4, asl #2	@ tmp341, ScdId,
	ldr	r7, [r5, #868]	@ s_RegPhyBaseAddr, s_RegPhyBaseAddr
	add	r6, r4, r4, asl #1	@, tmp160, ScdId, ScdId,
	add	sl, r5, #772	@ tmp157, tmp342,
	add	r0, r7, #2080	@, s_RegPhyBaseAddr,
	add	r6, sl, r6, asl #5	@, pScdDrvParam, tmp157, tmp160,
	add	r0, r0, #4	@,,
	bl	MEM_WritePhyWord	@
	add	r3, r8, r5	@ tmp169, tmp341, tmp342
	mov	r2, #1	@ tmp171,
	mov	r0, #2	@,
	str	r2, [r3, #1020]	@ tmp171, s_SCDInISR
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	bne	.L1262	@,
.L1274:
	ldr	r7, [r6, #80]	@ prephitmp.4030, <variable>.ThisInstID
.L1263:
	add	r2, r7, r7, asl #1	@, tmp194, prephitmp.4030, prephitmp.4030,
	ldr	ip, [r6, #76]	@ <variable>.IsScdDrvOpen, <variable>.IsScdDrvOpen
	movw	r3, #:lower16:.LANCHOR0	@ tmp190,
	movt	r3, #:upper16:.LANCHOR0	@ tmp190,
	add	r1, r5, r2, asl #4	@, tmp196, tmp342, tmp194,
	ldr	sl, [r1, #40]	@ pSmInstArray, <variable>.pSmInstArray
	cmp	ip, #0	@ <variable>.IsScdDrvOpen,
	cmpne	sl, #0	@, pSmInstArray,
	movne	r2, #0	@, tmp205
	moveq	r2, #1	@, tmp205
	beq	.L1276	@,
	movw	r9, #:lower16:g_VfmwGlobalStat	@ tmp340,
	movt	r9, #:upper16:g_VfmwGlobalStat	@ tmp340,
	mov	lr, #84	@ tmp217,
	mla	r3, lr, r4, r9	@ tmp218, tmp217, ScdId, tmp340
	ldr	r0, [r3, #68]	@ <variable>.u32SaLastStartTime, <variable>.u32SaLastStartTime
	cmp	r0, #0	@ <variable>.u32SaLastStartTime,
	bne	.L1277	@,
.L1265:
	ldr	lr, [r6, #84]	@ <variable>.SCDState, <variable>.SCDState
	cmp	lr, #1	@ <variable>.SCDState,
	beq	.L1278	@,
.L1268:
	add	r5, r8, r5	@ tmp335, tmp341, tmp342
	mov	lr, #0	@ tmp337,
	mov	r0, r7	@, prephitmp.4030
	str	lr, [r5, #1020]	@ tmp337, s_SCDInISR
	bl	SM_GiveThreadEvent	@
.L1275:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L1273	@
.L1262:
	bl	OSAL_GetTimeInMs	@
	ldr	r7, [r6, #80]	@ prephitmp.4030, <variable>.ThisInstID
	movw	sl, #:lower16:g_TraceBsPeriod	@ tmp179,
	movt	sl, #:upper16:g_TraceBsPeriod	@ tmp179,
	add	r3, r5, r7, asl #2	@, tmp175, tmp342, prephitmp.4030,
	ldr	r2, [sl, #0]	@ g_TraceBsPeriod, g_TraceBsPeriod
	mov	ip, r0	@ CurTimeInMs,
	ldr	r0, [r3, #1024]	@ tmp178, last_rec_pos_time
	rsb	r1, r0, ip	@ tmp177, tmp178, CurTimeInMs
	cmp	r1, r2	@ tmp177, g_TraceBsPeriod
	bls	.L1263	@,
	mov	lr, r7, asl #24	@ tmp188, prephitmp.4030,
	ldr	r0, .L1281	@,
	add	r2, lr, #131072	@, tmp188,
	movw	r1, #5445	@,
	str	ip, [r3, #1024]	@ CurTimeInMs, last_rec_pos_time
	bl	DBG_AddTrace	@
	b	.L1274	@
.L1277:
	str	r2, [fp, #-60]	@,
	str	r3, [fp, #-56]	@,
	bl	OSAL_GetTimeInMs	@
	ldr	r3, [fp, #-56]	@,
	ldr	r2, [r3, #64]	@ <variable>.u32SaBeginTime, <variable>.u32SaBeginTime
	ldr	ip, [r3, #68]	@ prephitmp.4032, <variable>.u32SaLastStartTime
	add	r1, r2, #49920	@ tmp233, <variable>.u32SaBeginTime,
	ldr	r2, [fp, #-60]	@,
	add	r1, r1, #80	@ tmp233, tmp233,
	cmp	r1, ip	@ tmp233, prephitmp.4032
	strcc	ip, [r3, #64]	@ prephitmp.4032, <variable>.u32SaBeginTime
	strcc	r2, [r3, #72]	@ tmp205, <variable>.u32SaScdWorkTime
	ldrcs	r1, [r3, #72]	@ prephitmp.4048, <variable>.u32SaScdWorkTime
	movcc	r1, r2	@ prephitmp.4048, tmp205
	mov	r3, #0	@ tmp275,
	add	r2, r1, r0	@ tmp267, prephitmp.4048, CurTime
	mov	r1, #84	@ tmp264,
	mla	r9, r1, r4, r9	@ tmp265, tmp264, ScdId, tmp340
	rsb	r2, ip, r2	@ tmp268, prephitmp.4032, tmp267
	ldr	ip, [r9, #64]	@ <variable>.u32SaBeginTime, <variable>.u32SaBeginTime
	str	r2, [r9, #72]	@ tmp268, <variable>.u32SaScdWorkTime
	rsb	r1, ip, r0	@ Period, <variable>.u32SaBeginTime, CurTime
	str	r3, [r9, #68]	@ tmp275, <variable>.u32SaLastStartTime
	cmp	r1, #1000	@ Period,
	bcc	.L1265	@,
	mov	r0, #1000	@ tmp298,
	str	r3, [fp, #-56]	@,
	mul	r0, r0, r2	@, tmp298, tmp268
	bl	__aeabi_uidiv	@
	ldr	ip, [fp, #-56]	@,
	str	ip, [r9, #64]	@ tmp275, <variable>.u32SaBeginTime
	str	r0, [r9, #76]	@, <variable>.u32SaScdLoad
	b	.L1265	@
.L1278:
	movw	r1, #:lower16:190872	@ tmp310,
	movt	r1, #:upper16:190872	@ tmp310,
	ldr	r3, [sl, r1]	@ <variable>.Mode, <variable>.Mode
	cmp	r3, #1	@ <variable>.Mode,
	beq	.L1279	@,
.L1269:
	movw	r2, #:lower16:190864	@ tmp326,
	movt	r2, #:upper16:190864	@ tmp326,
	mov	r0, r4	@, ScdId
	sub	r1, fp, #48	@,,
	mov	r4, #0	@ tmp327,
	str	r4, [sl, r2]	@ tmp327, <variable>.CutingFlag
	bl	SM_DoNextInstance	@
	cmp	r0, r4	@,
	strne	r4, [r6, #84]	@ tmp327, <variable>.SCDState
	bne	.L1268	@,
	mov	r0, #1	@ tmp330,
	str	r0, [r6, #84]	@ tmp330, <variable>.SCDState
	ldr	ip, [fp, #-48]	@ NextInstID, NextInstID
	str	ip, [r6, #80]	@ NextInstID, <variable>.ThisInstID
	bl	OSAL_GetTimeInMs	@
	str	r0, [r6, #88]	@, <variable>.LastProcessTime
	b	.L1268	@
.L1276:
	add	r8, r8, r3	@ tmp209, tmp341, tmp190
	movw	r0, #:lower16:g_TaskLock	@,
	mov	r3, #0	@ tmp211,
	movt	r0, #:upper16:g_TaskLock	@,
	str	r3, [r8, #1020]	@ tmp211, s_SCDInISR
	str	r3, [r6, #84]	@ tmp211, <variable>.SCDState
	bl	OSAL_SpinUnLockIRQ	@
	b	.L1273	@
.L1279:
	ldr	r0, [r6, #80]	@, <variable>.ThisInstID
	mov	r1, #0	@,
	bl	PrintScdRawState	@
	ldr	r0, [r6, #80]	@, <variable>.ThisInstID
	mov	r1, #0	@,
	bl	PrintScdSegState	@
	mov	r2, #0	@,
	ldr	r0, [r6, #80]	@, <variable>.ThisInstID
	mov	r1, #2	@,
	bl	DBG_CountTimeInfo	@
	mov	r0, sl	@, pSmInstArray
	mov	r1, r4	@, ScdId
	bl	ProcessScdReturn	@
	ldr	r2, [sl, #92]	@ <variable>.Config.IsOmxPath, <variable>.Config.IsOmxPath
	cmp	r2, #1	@ <variable>.Config.IsOmxPath,
	beq	.L1280	@,
.L1270:
	ldr	r0, [r6, #80]	@, <variable>.ThisInstID
	mov	r1, #0	@,
	bl	PrintScdRawState	@
	ldr	r0, [r6, #80]	@, <variable>.ThisInstID
	mov	r1, #0	@,
	bl	PrintScdSegState	@
	b	.L1269	@
.L1280:
	movw	lr, #:lower16:98508	@ tmp316,
	movw	r0, #:lower16:98504	@ tmp317,
	movt	lr, #:upper16:98508	@ tmp316,
	movt	r0, #:upper16:98504	@ tmp317,
	ldr	ip, [sl, lr]	@ <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Tail
	ldr	r9, [sl, r0]	@ <variable>.RawPacketArray.Head, <variable>.RawPacketArray.Head
	subs	r3, ip, r9	@ CurRawNum, <variable>.RawPacketArray.Tail, <variable>.RawPacketArray.Head
	ldrsb	r9, [sl, #2]	@ <variable>.LastCfgAllRawFlag, <variable>.LastCfgAllRawFlag
	addmi	r3, r3, #1024	@ CurRawNum, CurRawNum,
	cmp	r9, #1	@ <variable>.LastCfgAllRawFlag,
	bne	.L1270	@,
	ldr	r1, [sl, #192]	@ <variable>.Config.MaxRawPacketNum, <variable>.Config.MaxRawPacketNum
	cmp	r3, r1	@ CurRawNum, <variable>.Config.MaxRawPacketNum
	bne	.L1270	@,
	mov	r0, sl	@, pSmInstArray
	bl	SM_MoveRawData	@
	cmp	r0, #0	@,
	beq	.L1270	@,
	mov	r0, r9	@, <variable>.LastCfgAllRawFlag
	movw	r1, #:lower16:.LC182	@,
	movt	r1, #:upper16:.LC182	@,
	bl	dprint_vfmw	@
	movw	r3, #:lower16:190856	@ tmp323,
	movt	r3, #:upper16:190856	@ tmp323,
	ldr	r0, [sl, r3]	@, <variable>.InstID
	bl	SM_Reset	@
	b	.L1270	@
.L1282:
	.align	2
.L1281:
	.word	.LANCHOR1+408
	.fnend
	.size	SM_SCDIntServeProc, .-SM_SCDIntServeProc
	.align	2
	.global	SM_DeletDSPCtxMem
	.type	SM_DeletDSPCtxMem, %function
SM_DeletDSPCtxMem:
	.fnstart
.LFB1566:
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
	mov	r6, r0, asl #1	@ tmp187, SmID,
	add	r3, r6, r0	@ tmp138, tmp187, SmID
	movw	r4, #:lower16:.LANCHOR0	@ tmp186,
	movt	r4, #:upper16:.LANCHOR0	@ tmp186,
	mov	r5, r0	@ SmID, SmID
	add	r2, r4, r3, asl #4	@, tmp140, tmp186, tmp138,
	ldr	r0, [r2, #8]	@ D.50453, <variable>.DspCtxMem.stBaseMemInfo.PhyAddr
	cmp	r0, #0	@ D.50453,
	bne	.L1287	@,
	add	r1, r4, r3, asl #4	@, tmp156, tmp186, tmp138,
	ldr	r0, [r1, #4]	@, <variable>.DspCtxMem.stBaseMemInfo.VirAddr
	bl	KernelMunmap	@
.L1285:
	add	r5, r6, r5	@ tmp162, tmp187, SmID
	mov	r0, r5, asl #1	@ tmp163, tmp162,
	add	r5, r4, r5, asl #4	@, tmp172, tmp186, tmp162,
	add	r2, r0, #1	@ tmp164, tmp163,
	ldr	r1, [r5, #4]	@, <variable>.DspCtxMem.stBaseMemInfo.VirAddr
	add	ip, r4, r2, asl #3	@, tmp183, tmp186, tmp164,
	ldr	r0, [r4, r2, asl #3]	@, <variable>.DspCtxMem.stBaseMemInfo.PhyAddr
	ldr	r2, [ip, #4]	@, <variable>.DspCtxMem.stBaseMemInfo.Length
	bl	MEM_DelMemRecord	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L1287:
	ldr	r1, [r2, #4]	@, <variable>.DspCtxMem.stBaseMemInfo.VirAddr
	bl	MEM_ReleaseMemBlock	@
	b	.L1285	@
	.fnend
	.size	SM_DeletDSPCtxMem, .-SM_DeletDSPCtxMem
	.align	2
	.global	SM_AllocDSPCtxMem
	.type	SM_AllocDSPCtxMem, %function
SM_AllocDSPCtxMem:
	.fnstart
.LFB1565:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #24
	sub	sp, sp, #24	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	sub	r4, fp, #52	@ tmp145,,
	mov	r1, #16	@,
	mov	r5, #0	@ tmp148,
	mov	r7, r0	@ SmID, SmID
	mov	r0, r4	@, tmp145
	bl	__memzero	@
	movw	r0, #:lower16:.LC183	@,
	mov	r1, r5	@, tmp148
	movt	r0, #:upper16:.LC183	@,
	movw	r2, #9248	@,
	mov	r3, r4	@, tmp145
	str	r5, [sp, #0]	@ tmp148,
	bl	MEM_AllocMemBlock	@
	subs	sl, r0, #0	@ D.50411,
	bne	.L1289	@,
	ldr	r1, [fp, #-48]	@, stTempMem.VirAddr
	add	r7, r7, r7, asl #1	@, tmp155, SmID, SmID,
	ldr	r2, [fp, #-40]	@, stTempMem.Length
	movw	r5, #:lower16:.LANCHOR0	@ tmp152,
	ldr	r0, [fp, #-44]	@, stTempMem.PhyAddr
	movt	r5, #:upper16:.LANCHOR0	@ tmp152,
	bl	MEM_AddMemRecord	@
	ldr	r6, [fp, #-44]	@ MemAddr, stTempMem.PhyAddr
	ldmia	r4, {r0, r1, r2, r3}	@ tmp145,,,,
	add	r4, r6, #3	@ tmp159, MemAddr,
	bic	r8, r4, #3	@ tmp160, tmp159,
	add	r4, r7, #1	@ tmp165, tmp155,
	rsb	r8, r6, r8	@ Offset, MemAddr, tmp160
	add	r7, r5, r7, asl #4	@, tmp157, tmp152, tmp155,
	add	ip, r8, r6	@ D.50423, Offset, MemAddr
	stmia	r7, {r0, r1, r2, r3}	@ tmp157,,,,
	str	ip, [r5, r4, asl #4]	@ D.50423, <variable>.DspCtxMem.DspSpsMsgMemAddr
	mov	r0, ip	@, D.50423
	add	r5, r5, r4, asl #4	@, tmp173, tmp152, tmp165,
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@ D.50425,
	str	r0, [r5, #4]	@ D.50425, <variable>.DspCtxMem.pDspSpsMsgMemVirAddr
	beq	.L1296	@,
	mov	r1, #1024	@ tmp189,
	add	r6, r6, #1024	@ tmp200, MemAddr,
	str	r1, [r7, #24]	@ tmp189, <variable>.DspCtxMem.DspSpsMsgMemSize
	bl	__memzero	@
	add	r0, r6, r8	@ temp.4112, tmp200, Offset
	str	r0, [r7, #28]	@ temp.4112, <variable>.DspCtxMem.DspPpsMsgMemAddr
	bl	MEM_Phy2Vir	@
	cmp	r0, #0	@ D.50437,
	str	r0, [r7, #32]	@ D.50437, <variable>.DspCtxMem.pDspPpsMsgMemVirAddr
	beq	.L1297	@,
	mov	r1, #8192	@ tmp228,
	str	r1, [r7, #36]	@ tmp228, <variable>.DspCtxMem.DspPpsMsgMemSize
	bl	__memzero	@
	mov	r0, sl	@ D.50419, D.50411
.L1292:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L1289:
	mov	r0, r5	@, tmp148
	movw	r1, #:lower16:.LC184	@,
	ldr	r2, .L1298	@,
	movt	r1, #:upper16:.LC184	@,
	bl	dprint_vfmw	@
	mvn	r0, #6	@ D.50419,
	b	.L1292	@
.L1297:
	movw	r1, #:lower16:.LC186	@,
	ldr	r2, .L1298	@,
	movt	r1, #:upper16:.LC186	@,
	bl	dprint_vfmw	@
	mvn	r0, #6	@ D.50419,
	b	.L1292	@
.L1296:
	movw	r1, #:lower16:.LC185	@,
	ldr	r2, .L1298	@,
	movt	r1, #:upper16:.LC185	@,
	bl	dprint_vfmw	@
	mvn	r0, #6	@ D.50419,
	b	.L1292	@
.L1299:
	.align	2
.L1298:
	.word	.LANCHOR1+428
	.fnend
	.size	SM_AllocDSPCtxMem, .-SM_AllocDSPCtxMem
	.global	g_hex_flag
	.global	ForceRelease
	.global	s_RegPhyBaseAddr
	.global	s_RegPhyBaseAddr_1
	.global	g_pScdDrvParamBase
	.global	g_pSmIISBase
	.global	g_hex_base_vir_addr
	.global	g_hex_base_addr
	.global	g_hex_len
	.global	s_SmIIS
	.global	g_ScdDrvParam
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.50196, %object
	.size	__func__.50196, 17
__func__.50196:
	.ascii	"ReleaseStreamSeg\000"
	.space	3
	.type	CSWTCH.724, %object
	.size	CSWTCH.724, 80
CSWTCH.724:
	.word	4194304
	.word	4194304
	.word	4194304
	.word	4194304
	.word	4194304
	.word	20971520
	.word	20971520
	.word	20971520
	.word	20971520
	.word	20971520
	.word	20971520
	.word	3145728
	.word	3145728
	.word	3145728
	.word	3145728
	.word	3145728
	.word	3145728
	.word	3145728
	.word	3145728
	.word	20971520
	.type	__func__.53346, %object
	.size	__func__.53346, 17
__func__.53346:
	.ascii	"PrintScdSegState\000"
	.space	3
	.type	__func__.53231, %object
	.size	__func__.53231, 17
__func__.53231:
	.ascii	"PrintScdRawState\000"
	.space	3
	.type	__func__.51667, %object
	.size	__func__.51667, 11
__func__.51667:
	.ascii	"GetNextVop\000"
	.space	1
	.type	__func__.53026, %object
	.size	__func__.53026, 19
__func__.53026:
	.ascii	"SCDDRV_CheckDevice\000"
	.space	1
	.type	C.636.52319, %object
	.size	C.636.52319, 100
C.636.52319:
	.byte	0
	.byte	0
	.byte	1
	.byte	11
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-73
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	-73
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	98
	.byte	0
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	__func__.52299, %object
	.size	__func__.52299, 17
__func__.52299:
	.ascii	"FillEosRawStream\000"
	.space	3
	.type	__func__.52790, %object
	.size	__func__.52790, 18
__func__.52790:
	.ascii	"SM_DoNextInstance\000"
	.space	2
	.type	__func__.53052, %object
	.size	__func__.53052, 19
__func__.53052:
	.ascii	"SCDDRV_ActivateSCD\000"
	.space	1
	.type	__func__.52344, %object
	.size	__func__.52344, 14
__func__.52344:
	.ascii	"FillExtraData\000"
	.space	2
	.type	__func__.52125, %object
	.size	__func__.52125, 12
__func__.52125:
	.ascii	"FillRawData\000"
	.type	__func__.53100, %object
	.size	__func__.53100, 10
__func__.53100:
	.ascii	"SM_Wakeup\000"
	.space	2
	.type	__func__.51770, %object
	.size	__func__.51770, 17
__func__.51770:
	.ascii	"ProcessScdReturn\000"
	.space	3
	.type	__func__.50489, %object
	.size	__func__.50489, 14
__func__.50489:
	.ascii	"SM_OpenSCDDrv\000"
	.space	2
	.type	__func__.52938, %object
	.size	__func__.52938, 19
__func__.52938:
	.ascii	"SM_SCDIntServeProc\000"
	.space	1
	.type	__func__.50397, %object
	.size	__func__.50397, 18
__func__.50397:
	.ascii	"SM_AllocDSPCtxMem\000"
	.data
	.align	2
.LANCHOR2 = . + 0
.LANCHOR3 = . + 16368
	.type	g_avsp_firmware, %object
	.size	g_avsp_firmware, 17920
g_avsp_firmware:
	.word	0
	.word	16283648
	.word	16349954
	.word	9468936
	.word	-252085482
	.word	9468688
	.word	9468692
	.word	16284426
	.word	9468680
	.word	18807566
	.word	-258442240
	.word	10517258
	.word	18807566
	.word	-258442239
	.word	10517258
	.word	18807566
	.word	-258442238
	.word	10517258
	.word	18807566
	.word	-258442237
	.word	10517258
	.word	18807566
	.word	-258442236
	.word	10517258
	.word	18807566
	.word	-258442235
	.word	10517258
	.word	18807566
	.word	-258442234
	.word	10517258
	.word	18807566
	.word	-258442233
	.word	10517258
	.word	-251200754
	.word	10517258
	.word	17758990
	.word	33128448
	.word	24738824
	.word	-1879048192
	.word	16349954
	.word	0
	.word	18512896
	.word	33390592
	.word	24738817
	.word	-250447311
	.word	9468672
	.word	17988136
	.word	-795837688
	.word	12090128
	.word	18807566
	.word	24967950
	.word	-249398743
	.word	33259520
	.word	554859056
	.word	-258966784
	.word	19561007
	.word	-235307008
	.word	-1063027960
	.word	16349968
	.word	0
	.word	11041536
	.word	0
	.word	1073741824
	.word	33259520
	.word	554859057
	.word	9468672
	.word	0
	.word	-1342177280
	.word	0
	.word	33128448
	.word	-1592624595
	.word	-258966776
	.word	12090128
	.word	0
	.word	17988137
	.word	9468680
	.word	16349968
	.word	17988143
	.word	-258966784
	.word	0
	.word	33521664
	.word	-1879048192
	.word	0
	.word	-1610612736
	.word	-248874449
	.word	9468688
	.word	9468692
	.word	11041536
	.word	0
	.word	0
	.word	0
	.word	286948352
	.word	9467906
	.word	33128448
	.word	-1320519377
	.word	1630697896
	.word	33128448
	.word	-786269183
	.word	17988140
	.word	9468680
	.word	12090128
	.word	21953294
	.word	19400197
	.word	33128448
	.word	-1059883006
	.word	33062912
	.word	-1073741824
	.word	1358526466
	.word	-1342177280
	.word	-1879048192
	.word	17988009
	.word	1620081416
	.word	1354267408
	.word	21953294
	.word	19400216
	.word	33128448
	.word	-2133624830
	.word	33062912
	.word	-2147483648
	.word	-2131134462
	.word	19400222
	.word	33128448
	.word	0
	.word	19036462
	.word	33390592
	.word	33398784
	.word	1092253959
	.word	33128448
	.word	1362626056
	.word	17988013
	.word	9468680
	.word	12090128
	.word	21429006
	.word	1092253999
	.word	33128448
	.word	-250447444
	.word	9468680
	.word	12090128
	.word	24673282
	.word	-250447445
	.word	814775048
	.word	12090128
	.word	0
	.word	-785744896
	.word	556956675
	.word	33128448
	.word	-235298816
	.word	-235290624
	.word	25000964
	.word	-2147483648
	.word	33128448
	.word	-1050147328
	.word	18351619
	.word	18875907
	.word	554858927
	.word	33128448
	.word	-235290624
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	-1845493760
	.word	23594500
	.word	18875906
	.word	554858927
	.word	33128448
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	872415232
	.word	-2147483648
	.word	18351646
	.word	24926480
	.word	-2124785392
	.word	-2147483648
	.word	0
	.word	19028272
	.word	20601264
	.word	554858927
	.word	10517258
	.word	546339592
	.word	0
	.word	-268435456
	.word	-1592100601
	.word	12090128
	.word	33128448
	.word	1634207232
	.word	18351619
	.word	18875907
	.word	554859050
	.word	33128448
	.word	-235290624
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	17988139
	.word	9468680
	.word	0
	.word	-771751936
	.word	23594500
	.word	18875906
	.word	554859050
	.word	33128448
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	17988139
	.word	9468680
	.word	0
	.word	-1543503872
	.word	1073741824
	.word	18351646
	.word	24926480
	.word	1096440080
	.word	-2147483648
	.word	17988138
	.word	19028272
	.word	20601264
	.word	536870912
	.word	10517258
	.word	9468680
	.word	17988139
	.word	9468680
	.word	0
	.word	-1879048192
	.word	1366850566
	.word	33398784
	.word	17987886
	.word	33398784
	.word	33398784
	.word	-518882770
	.word	9468680
	.word	16349968
	.word	0
	.word	-536870912
	.word	1903720450
	.word	1092093440
	.word	17988010
	.word	9468680
	.word	12090128
	.word	18807566
	.word	33259520
	.word	293436421
	.word	25000967
	.word	-1055753810
	.word	9468680
	.word	12090128
	.word	0
	.word	33460224
	.word	33460224
	.word	33198080
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1011712
	.word	0
	.word	0
	.word	1013760
	.word	18687
	.word	0
	.word	0
	.word	18688
	.word	0
	.word	0
	.word	103084
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	102700
	.word	0
	.word	18432
	.word	916608
	.word	0
	.word	1027074
	.word	0
	.word	1013760
	.word	18432
	.word	916620
	.word	908352
	.word	1027075
	.word	0
	.word	1013760
	.word	105964
	.word	0
	.word	1013760
	.word	0
	.word	1031171
	.word	916484
	.word	1031173
	.word	98348
	.word	1013760
	.word	904428
	.word	1027075
	.word	0
	.word	1013760
	.word	0
	.word	1013760
	.word	1027075
	.word	916484
	.word	1031173
	.word	0
	.word	1013760
	.word	1035269
	.word	1031168
	.word	916712
	.word	1031172
	.word	23807
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	98348
	.word	1013760
	.word	916484
	.word	1031170
	.word	1007616
	.word	1018885
	.word	18687
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	1018880
	.word	1007616
	.word	18432
	.word	20480
	.word	916688
	.word	1031175
	.word	23552
	.word	916696
	.word	1027078
	.word	908752
	.word	0
	.word	0
	.word	1013760
	.word	108112
	.word	917096
	.word	1031174
	.word	917076
	.word	1027078
	.word	25600
	.word	1018887
	.word	23553
	.word	908752
	.word	19456
	.word	22528
	.word	1013760
	.word	108112
	.word	917096
	.word	1031175
	.word	917076
	.word	1027079
	.word	25601
	.word	108108
	.word	917076
	.word	222628
	.word	19456
	.word	917068
	.word	917072
	.word	1027086
	.word	917068
	.word	1027080
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	23552
	.word	917068
	.word	1027080
	.word	0
	.word	0
	.word	1013760
	.word	1027080
	.word	23552
	.word	0
	.word	1013760
	.word	19457
	.word	20480
	.word	916756
	.word	916908
	.word	916844
	.word	0
	.word	1027083
	.word	917068
	.word	1027082
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	916844
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	989193
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	989194
	.word	1018891
	.word	113316
	.word	112296
	.word	1031179
	.word	310092
	.word	113572
	.word	0
	.word	0
	.word	69916
	.word	0
	.word	23552
	.word	1013760
	.word	988170
	.word	23553
	.word	0
	.word	917068
	.word	1027085
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	916844
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	1013760
	.word	989195
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	1013760
	.word	989196
	.word	1018894
	.word	113316
	.word	112296
	.word	1031182
	.word	310092
	.word	113572
	.word	0
	.word	0
	.word	69916
	.word	0
	.word	0
	.word	1013760
	.word	0
	.word	1013760
	.word	988173
	.word	19456
	.word	917068
	.word	19456
	.word	917068
	.word	917064
	.word	1027086
	.word	0
	.word	0
	.word	1013760
	.word	1018894
	.word	23552
	.word	1027087
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	916712
	.word	23556
	.word	0
	.word	1027087
	.word	0
	.word	0
	.word	1013760
	.word	999424
	.word	999424
	.word	999424
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65537
	.word	1900544
	.word	513
	.word	1537
	.word	336598617
	.word	336598617
	.word	65536
	.word	131074
	.word	4
	.word	0
	.word	65537
	.word	131073
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	2
	.word	327686
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	131072
	.word	1
	.word	131072
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65538
	.word	1
	.word	0
	.word	0
	.word	131072
	.word	131073
	.word	131073
	.word	1
	.word	131072
	.word	1
	.word	131072
	.word	131073
	.word	131073
	.word	1
	.word	0
	.word	0
	.word	2
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	3
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	524289
	.word	4196352
	.word	1048608
	.word	8396800
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65536
	.word	0
	.word	65536
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65536
	.word	65537
	.word	65537
	.word	1
	.word	65536
	.word	1
	.word	65536
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	131073
	.word	33554688
	.word	1073741828
	.word	132096
	.word	65540
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	g_h264_firmware, %object
	.size	g_h264_firmware, 17920
g_h264_firmware:
	.word	0
	.word	823064910
	.word	8419328
	.word	9239400
	.word	16349184
	.word	285670144
	.word	33128448
	.word	-1879048192
	.word	1342177280
	.word	0
	.word	8420384
	.word	8420386
	.word	8420387
	.word	8420388
	.word	8420389
	.word	8420390
	.word	8420391
	.word	8420393
	.word	8420394
	.word	8420395
	.word	8420392
	.word	8420396
	.word	8715424
	.word	8715428
	.word	8682668
	.word	8682542
	.word	8682671
	.word	268435456
	.word	8420385
	.word	-1342177280
	.word	24673452
	.word	-268435456
	.word	24673326
	.word	1610612736
	.word	17234198
	.word	0
	.word	-2130020076
	.word	33259520
	.word	1610612736
	.word	1091206148
	.word	33259520
	.word	1610612736
	.word	17234274
	.word	822770726
	.word	33259520
	.word	1610612736
	.word	33325056
	.word	1610612736
	.word	-1342177280
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	-2147483648
	.word	268435456
	.word	16349184
	.word	277150492
	.word	9239324
	.word	805306368
	.word	8419328
	.word	0
	.word	805306368
	.word	8419328
	.word	17234796
	.word	17758530
	.word	0
	.word	-268435456
	.word	1342177280
	.word	-235044864
	.word	1628371250
	.word	0
	.word	17464358
	.word	0
	.word	-235044864
	.word	1610612736
	.word	0
	.word	536870912
	.word	1610612736
	.word	24673326
	.word	-536870912
	.word	17234200
	.word	0
	.word	-2130020076
	.word	33259520
	.word	1610612736
	.word	1091206148
	.word	33259520
	.word	1610612736
	.word	17234274
	.word	822770726
	.word	33259520
	.word	1610612736
	.word	33325056
	.word	1610612736
	.word	-1342177280
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	1879048192
	.word	0
	.word	16349184
	.word	277150492
	.word	9239324
	.word	805306368
	.word	8419328
	.word	0
	.word	805306368
	.word	8419328
	.word	17234796
	.word	17758530
	.word	0
	.word	-268435456
	.word	1342177280
	.word	-235044864
	.word	1628371250
	.word	0
	.word	17464358
	.word	0
	.word	-235044864
	.word	-536870912
	.word	268435456
	.word	536870912
	.word	1610612736
	.word	24673455
	.word	1610612736
	.word	24935457
	.word	1610612736
	.word	24706208
	.word	1610612736
	.word	0
	.word	536870912
	.word	16349184
	.word	17758488
	.word	8715034
	.word	9239322
	.word	0
	.word	17234228
	.word	17758984
	.word	17758980
	.word	268435456
	.word	0
	.word	-234913792
	.word	1342177280
	.word	21428994
	.word	23525654
	.word	21952790
	.word	20904718
	.word	17758520
	.word	0
	.word	17234288
	.word	18282794
	.word	18807142
	.word	-2147483648
	.word	19331382
	.word	17235072
	.word	18283652
	.word	0
	.word	8715418
	.word	0
	.word	9763996
	.word	33325056
	.word	-1610612736
	.word	18282774
	.word	824113430
	.word	9239710
	.word	17235098
	.word	1610612736
	.word	16349184
	.word	9239710
	.word	17235098
	.word	17758988
	.word	0
	.word	805306368
	.word	17235098
	.word	18283278
	.word	18807964
	.word	0
	.word	805306368
	.word	18283278
	.word	-1073741824
	.word	268435456
	.word	17988648
	.word	286194026
	.word	33128448
	.word	-1879048192
	.word	33128448
	.word	-1861813906
	.word	33128448
	.word	822540652
	.word	33128448
	.word	-536870912
	.word	0
	.word	-1073741824
	.word	24673280
	.word	805306368
	.word	16349184
	.word	17234704
	.word	19037185
	.word	-2129725162
	.word	18282848
	.word	18807144
	.word	-2147483648
	.word	805306368
	.word	805306368
	.word	24673296
	.word	805306368
	.word	16349184
	.word	17234706
	.word	19037201
	.word	-2129725088
	.word	18282848
	.word	18807144
	.word	-2147483648
	.word	805306368
	.word	17235098
	.word	17759388
	.word	18283678
	.word	8715424
	.word	9239714
	.word	9764004
	.word	14711981
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	21952864
	.word	-2147483648
	.word	16349184
	.word	17234228
	.word	17758984
	.word	0
	.word	17758980
	.word	268435456
	.word	33062912
	.word	-2147483648
	.word	-235175936
	.word	0
	.word	-235110400
	.word	-2147483648
	.word	16349184
	.word	17234288
	.word	17758978
	.word	18282782
	.word	18807142
	.word	-2147483648
	.word	16349184
	.word	20904718
	.word	17758520
	.word	0
	.word	19331382
	.word	17235072
	.word	0
	.word	0
	.word	8715420
	.word	16349184
	.word	17235100
	.word	17758982
	.word	0
	.word	17758988
	.word	33259520
	.word	-805306368
	.word	17235100
	.word	17758982
	.word	805306368
	.word	18282774
	.word	18807062
	.word	1879048192
	.word	17235100
	.word	17758988
	.word	0
	.word	0
	.word	805306368
	.word	17235100
	.word	18283278
	.word	18807558
	.word	0
	.word	805306368
	.word	-1073741824
	.word	268435456
	.word	17988648
	.word	286194026
	.word	33128448
	.word	1073741824
	.word	33128448
	.word	1073741824
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420524
	.word	24706208
	.word	-2147483648
	.word	17759396
	.word	33521664
	.word	-536870912
	.word	17235104
	.word	17759396
	.word	18282774
	.word	18807062
	.word	-1879048192
	.word	16349184
	.word	17235104
	.word	17758988
	.word	0
	.word	805306368
	.word	17235104
	.word	18283278
	.word	18807970
	.word	0
	.word	805306368
	.word	18283278
	.word	-1073741824
	.word	268435456
	.word	17988648
	.word	286194026
	.word	33390592
	.word	0
	.word	536870912
	.word	33390592
	.word	-2147483648
	.word	268435456
	.word	1879048192
	.word	268435456
	.word	268435456
	.word	8420524
	.word	0
	.word	0
	.word	8420398
	.word	0
	.word	16349184
	.word	17234708
	.word	8715430
	.word	17758498
	.word	0
	.word	8715432
	.word	17758488
	.word	18807562
	.word	1073741824
	.word	0
	.word	805306368
	.word	8419328
	.word	16940070
	.word	17758514
	.word	0
	.word	-250676968
	.word	-268435456
	.word	1342177280
	.word	17758488
	.word	-268435456
	.word	1610612736
	.word	0
	.word	-268435456
	.word	-268435456
	.word	268435456
	.word	0
	.word	8715104
	.word	268435456
	.word	-536870912
	.word	8715106
	.word	16349184
	.word	17234708
	.word	805306368
	.word	10516480
	.word	8715108
	.word	17235088
	.word	8715110
	.word	17234214
	.word	8715120
	.word	17234244
	.word	8715118
	.word	16940060
	.word	-268435456
	.word	-805306368
	.word	17464339
	.word	-268435456
	.word	-1073741824
	.word	17464340
	.word	-268435456
	.word	-1323894504
	.word	17464322
	.word	0
	.word	-268435456
	.word	-1610612736
	.word	17464324
	.word	-268435456
	.word	268435456
	.word	24673285
	.word	-2147483648
	.word	17758486
	.word	805306368
	.word	24673316
	.word	-512197595
	.word	-1055983330
	.word	805306368
	.word	17758488
	.word	805306368
	.word	24673286
	.word	286193958
	.word	805306368
	.word	17758486
	.word	805306368
	.word	-536870912
	.word	17464323
	.word	0
	.word	8715328
	.word	17235110
	.word	18282776
	.word	18807144
	.word	-2147483648
	.word	16349184
	.word	17234710
	.word	8715330
	.word	1090976934
	.word	0
	.word	286718232
	.word	18807144
	.word	-2147483648
	.word	17235112
	.word	8715332
	.word	1090976934
	.word	0
	.word	555153688
	.word	18807144
	.word	-2147483648
	.word	16349184
	.word	17234712
	.word	8715334
	.word	-2130248538
	.word	0
	.word	823589144
	.word	18807144
	.word	-2147483648
	.word	17235090
	.word	8715336
	.word	16940202
	.word	8715338
	.word	17235092
	.word	33259520
	.word	-1610612736
	.word	0
	.word	8715340
	.word	17235094
	.word	8715342
	.word	16940203
	.word	8715344
	.word	17235096
	.word	33259520
	.word	805306368
	.word	0
	.word	8715346
	.word	-1593672675
	.word	17464365
	.word	0
	.word	-268435456
	.word	-1342177280
	.word	822770723
	.word	0
	.word	-268435456
	.word	-1879048192
	.word	17464353
	.word	0
	.word	8715348
	.word	-251495381
	.word	0
	.word	-268435456
	.word	1628077098
	.word	0
	.word	-268435456
	.word	268435456
	.word	17464327
	.word	-536870912
	.word	17464354
	.word	18807064
	.word	33128448
	.word	0
	.word	33128448
	.word	536870912
	.word	1091500310
	.word	268435456
	.word	1073741824
	.word	536870912
	.word	1073741824
	.word	0
	.word	8715350
	.word	17235112
	.word	1092024672
	.word	18807144
	.word	-2147483648
	.word	16940070
	.word	17758514
	.word	0
	.word	-268435456
	.word	8715352
	.word	17235112
	.word	0
	.word	-1055459048
	.word	18807144
	.word	-2147483648
	.word	0
	.word	8715354
	.word	-1056506712
	.word	0
	.word	-787023592
	.word	18807144
	.word	-2147483648
	.word	0
	.word	554173952
	.word	17827336
	.word	1879048192
	.word	-251200684
	.word	0
	.word	8420526
	.word	822609408
	.word	17827352
	.word	1879048192
	.word	-1073741824
	.word	11566081
	.word	-250446847
	.word	33325056
	.word	-805306368
	.word	17988609
	.word	33325056
	.word	-805306368
	.word	20085934
	.word	554203411
	.word	33128448
	.word	0
	.word	33128448
	.word	0
	.word	-2130151150
	.word	33128448
	.word	0
	.word	33128448
	.word	0
	.word	-519538416
	.word	33128448
	.word	0
	.word	33128448
	.word	16808209
	.word	33128448
	.word	0
	.word	-805306368
	.word	1091074311
	.word	33128448
	.word	-1342177280
	.word	33128448
	.word	-1342177280
	.word	-1593280239
	.word	33128448
	.word	-1342177280
	.word	33128448
	.word	-1342177280
	.word	-805306368
	.word	-1073741824
	.word	11566082
	.word	17827329
	.word	0
	.word	0
	.word	33390592
	.word	-805306368
	.word	-1073741824
	.word	0
	.word	33390592
	.word	-805306368
	.word	-1073741824
	.word	0
	.word	33390592
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	0
	.word	33390592
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	268435456
	.word	33390592
	.word	-268435456
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1073741824
	.word	-2128083448
	.word	0
	.word	0
	.word	33128448
	.word	805306368
	.word	-805306368
	.word	18282786
	.word	0
	.word	17758564
	.word	0
	.word	0
	.word	33128448
	.word	1879048192
	.word	0
	.word	286193948
	.word	0
	.word	33062912
	.word	-1073741824
	.word	-1342177280
	.word	-234881024
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1342177280
	.word	-2128083448
	.word	0
	.word	0
	.word	33128448
	.word	536870912
	.word	-805306368
	.word	18282786
	.word	0
	.word	17758564
	.word	0
	.word	0
	.word	33128448
	.word	1610612736
	.word	0
	.word	286193964
	.word	0
	.word	33062912
	.word	-1342177280
	.word	-1610612736
	.word	-536870912
	.word	-268435456
	.word	268435456
	.word	8420354
	.word	-1073741824
	.word	11566088
	.word	-1073741824
	.word	33259520
	.word	1342177280
	.word	-805306368
	.word	-1073741824
	.word	11566089
	.word	0
	.word	33128448
	.word	268435456
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	536870912
	.word	33128448
	.word	-805306368
	.word	-805306368
	.word	-1073741824
	.word	11566091
	.word	-1073741824
	.word	33521664
	.word	-805306368
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	17234772
	.word	8420362
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	1879048192
	.word	1879048192
	.word	-1073741824
	.word	11566254
	.word	-268435456
	.word	33259520
	.word	-805306368
	.word	0
	.word	33521664
	.word	-805306368
	.word	16940206
	.word	0
	.word	1879048192
	.word	-1342177280
	.word	-1073741824
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	-1073741824
	.word	11566083
	.word	286193960
	.word	33325056
	.word	-805306368
	.word	33062912
	.word	-805306368
	.word	-1073741824
	.word	11566084
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566085
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	0
	.word	33128448
	.word	1610612736
	.word	-2147483648
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566086
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	286193946
	.word	20085764
	.word	33325056
	.word	-805306368
	.word	33062912
	.word	-805306368
	.word	825392131
	.word	33325056
	.word	-805306368
	.word	0
	.word	0
	.word	8420358
	.word	286193956
	.word	20085764
	.word	33325056
	.word	-805306368
	.word	33062912
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566087
	.word	24673455
	.word	-805306368
	.word	822609409
	.word	17827329
	.word	1879048192
	.word	268435456
	.word	8420352
	.word	0
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420352
	.word	0
	.word	-1073741824
	.word	11566097
	.word	17827583
	.word	33325056
	.word	-1342177280
	.word	33259520
	.word	-1342177280
	.word	-1073741824
	.word	11566098
	.word	17827359
	.word	33325056
	.word	-1342177280
	.word	33259520
	.word	-1342177280
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	-2147483648
	.word	268435456
	.word	16349184
	.word	17758992
	.word	19037202
	.word	-2130249450
	.word	18282848
	.word	18807142
	.word	-2147483648
	.word	24935424
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566099
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566101
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	-1073741824
	.word	0
	.word	33390592
	.word	-1342177280
	.word	-1073741824
	.word	11566103
	.word	-268435456
	.word	33259520
	.word	-1342177280
	.word	-1073741824
	.word	11566104
	.word	-268435456
	.word	33259520
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566106
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827330
	.word	1879048192
	.word	20380500
	.word	11566107
	.word	822609408
	.word	17827330
	.word	1879048192
	.word	805306368
	.word	33062912
	.word	-1342177280
	.word	-805306368
	.word	11566109
	.word	-805306368
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566105
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566100
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566102
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	17234198
	.word	8420380
	.word	822541470
	.word	17759062
	.word	0
	.word	33521664
	.word	805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566108
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935452
	.word	805306368
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	33390592
	.word	268435456
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	17235102
	.word	17759062
	.word	33521664
	.word	-536870912
	.word	-268435456
	.word	0
	.word	8420380
	.word	805306368
	.word	268435456
	.word	8420380
	.word	24673455
	.word	-1342177280
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	268435456
	.word	8420368
	.word	0
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420368
	.word	0
	.word	-1073741824
	.word	11566113
	.word	17758528
	.word	33062912
	.word	268435456
	.word	-1073741824
	.word	536870912
	.word	33128448
	.word	1610612736
	.word	1073741824
	.word	33128448
	.word	1610612736
	.word	1879048192
	.word	33128448
	.word	1610612736
	.word	-1879048192
	.word	33128448
	.word	1610612736
	.word	0
	.word	33128448
	.word	-1879048192
	.word	805306368
	.word	33128448
	.word	-1879048192
	.word	1342177280
	.word	33128448
	.word	-1879048192
	.word	-2147483648
	.word	33128448
	.word	-1879048192
	.word	268435456
	.word	33128448
	.word	-1073741824
	.word	1610612736
	.word	33128448
	.word	-1073741824
	.word	268435456
	.word	536870912
	.word	8944674
	.word	-536870912
	.word	0
	.word	8944674
	.word	-536870912
	.word	268435456
	.word	8944674
	.word	-1073741824
	.word	11566112
	.word	-268435456
	.word	33259520
	.word	268435456
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	-1610612736
	.word	805306368
	.word	16349184
	.word	17758994
	.word	19037216
	.word	-2130249376
	.word	18282848
	.word	18807142
	.word	-2147483648
	.word	24935440
	.word	268435456
	.word	16349184
	.word	17758992
	.word	19037202
	.word	-2130249450
	.word	18282848
	.word	18807142
	.word	-2147483648
	.word	24935424
	.word	268435456
	.word	822609408
	.word	1092254728
	.word	0
	.word	1879048192
	.word	0
	.word	8420388
	.word	8420389
	.word	24673285
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566116
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673316
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566117
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	16940035
	.word	17464324
	.word	-268435456
	.word	-268435456
	.word	-2147483648
	.word	8420390
	.word	24673285
	.word	-1610612736
	.word	24673316
	.word	-1610612736
	.word	554335270
	.word	-2147483648
	.word	8420390
	.word	554335236
	.word	-268435456
	.word	-2147483648
	.word	268435456
	.word	0
	.word	8420356
	.word	285375524
	.word	17464326
	.word	0
	.word	8420391
	.word	1359641640
	.word	33390592
	.word	1342177280
	.word	-1073741824
	.word	17758528
	.word	33259520
	.word	268435456
	.word	17464329
	.word	33390592
	.word	536870912
	.word	822609408
	.word	1092254731
	.word	0
	.word	1879048192
	.word	16940053
	.word	285899812
	.word	0
	.word	33521664
	.word	536870912
	.word	1879048192
	.word	16940041
	.word	285899786
	.word	0
	.word	33521664
	.word	-536870912
	.word	1879048192
	.word	16940053
	.word	285899812
	.word	0
	.word	33521664
	.word	-536870912
	.word	1879048192
	.word	24935446
	.word	1073741824
	.word	-1073741824
	.word	0
	.word	33259520
	.word	268435456
	.word	285899810
	.word	33390592
	.word	-536870912
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	17234772
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	16940055
	.word	17464344
	.word	8420394
	.word	8944683
	.word	554335266
	.word	33128448
	.word	1610612736
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566121
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935465
	.word	1610612736
	.word	-1073741824
	.word	11566122
	.word	285899810
	.word	33390592
	.word	1610612736
	.word	-1073741824
	.word	11566123
	.word	554335266
	.word	33390592
	.word	-1342177280
	.word	0
	.word	8420394
	.word	285899810
	.word	33128448
	.word	0
	.word	0
	.word	8420395
	.word	554335266
	.word	33390592
	.word	1073741824
	.word	1610612736
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935598
	.word	1610612736
	.word	0
	.word	554335274
	.word	0
	.word	-1073741824
	.word	805306368
	.word	33259520
	.word	268435456
	.word	805306368
	.word	33128448
	.word	1610612736
	.word	0
	.word	33128448
	.word	536870912
	.word	268435456
	.word	33128448
	.word	536870912
	.word	536870912
	.word	33128448
	.word	1073741824
	.word	1342177280
	.word	1879048192
	.word	1342177280
	.word	1879048192
	.word	268435456
	.word	285899810
	.word	33390592
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935598
	.word	-1342177280
	.word	0
	.word	554335275
	.word	0
	.word	-1073741824
	.word	805306368
	.word	33259520
	.word	268435456
	.word	805306368
	.word	33128448
	.word	-1342177280
	.word	0
	.word	33128448
	.word	1879048192
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	536870912
	.word	33128448
	.word	-1879048192
	.word	-1610612736
	.word	1879048192
	.word	-1610612736
	.word	1879048192
	.word	1610612736
	.word	17464354
	.word	286948379
	.word	33390592
	.word	293108762
	.word	-2147483648
	.word	1879048192
	.word	17464354
	.word	33390592
	.word	1879048192
	.word	-235044864
	.word	1879048192
	.word	-2147483648
	.word	536870912
	.word	-1073741824
	.word	24673282
	.word	-1073741824
	.word	-1073741824
	.word	17464362
	.word	268435456
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1342177280
	.word	-805306368
	.word	-805306368
	.word	24673282
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1342177280
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	-268435456
	.word	285899810
	.word	17988635
	.word	33390592
	.word	536870912
	.word	-235044864
	.word	536870912
	.word	17464363
	.word	268435456
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	268435456
	.word	-805306368
	.word	-805306368
	.word	24673282
	.word	268435456
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	268435456
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	1342177280
	.word	24673324
	.word	-536870912
	.word	1359641640
	.word	33390592
	.word	-1342177280
	.word	822609408
	.word	17827330
	.word	1879048192
	.word	-536870912
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-536870912
	.word	-1073741824
	.word	11566254
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	536870912
	.word	33128448
	.word	1879048192
	.word	1073741824
	.word	33128448
	.word	1879048192
	.word	1610612736
	.word	33128448
	.word	1879048192
	.word	805306368
	.word	33128448
	.word	-1879048192
	.word	-1342177280
	.word	-1073741824
	.word	-1342177280
	.word	-1073741824
	.word	-1073741824
	.word	16940206
	.word	33259520
	.word	1342177280
	.word	24673299
	.word	-1073741824
	.word	16940066
	.word	33128448
	.word	1879048192
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	-1073741824
	.word	-1073741824
	.word	11566115
	.word	805306368
	.word	33062912
	.word	268435456
	.word	-805306368
	.word	11566125
	.word	24935449
	.word	-1879048192
	.word	-1073741824
	.word	536870912
	.word	33259520
	.word	268435456
	.word	17827329
	.word	33128448
	.word	-1879048192
	.word	-805306368
	.word	-805306368
	.word	24673455
	.word	268435456
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	268435456
	.word	8420398
	.word	0
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420398
	.word	0
	.word	1073741824
	.word	9992192
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	-1879048192
	.word	-1342177280
	.word	268435456
	.word	8420527
	.word	0
	.word	1073741824
	.word	11565056
	.word	19331386
	.word	20379926
	.word	33390592
	.word	-536870912
	.word	20379926
	.word	11336516
	.word	11860806
	.word	19855676
	.word	0
	.word	805306368
	.word	11336520
	.word	9239370
	.word	9763660
	.word	11860814
	.word	10287952
	.word	-536870912
	.word	20379926
	.word	11336516
	.word	0
	.word	0
	.word	11336518
	.word	19855676
	.word	0
	.word	805306368
	.word	11336520
	.word	9239370
	.word	11860812
	.word	19855676
	.word	0
	.word	805306368
	.word	11336526
	.word	10287952
	.word	268435456
	.word	8715074
	.word	0
	.word	1073741824
	.word	11565056
	.word	823064854
	.word	18282784
	.word	1879048192
	.word	554629398
	.word	18282848
	.word	1879048192
	.word	-251200684
	.word	17758502
	.word	1342177280
	.word	9468968
	.word	9993260
	.word	823064854
	.word	18282848
	.word	1879048192
	.word	0
	.word	0
	.word	33390592
	.word	-1342177280
	.word	16349184
	.word	-2129724670
	.word	18906285
	.word	-2130249360
	.word	18282782
	.word	18807142
	.word	-2147483648
	.word	17235074
	.word	17758488
	.word	-268435456
	.word	-268435456
	.word	268435456
	.word	0
	.word	8715394
	.word	16349184
	.word	-2130248958
	.word	18906285
	.word	-2129725072
	.word	18282782
	.word	18807144
	.word	-2147483648
	.word	1879048192
	.word	16349184
	.word	-2129724670
	.word	19331848
	.word	-268435456
	.word	-2130249360
	.word	18282782
	.word	18807142
	.word	-2147483648
	.word	16349184
	.word	17234694
	.word	17759362
	.word	0
	.word	9239686
	.word	17234694
	.word	17759360
	.word	18283276
	.word	33259520
	.word	-536870912
	.word	805306368
	.word	17235072
	.word	17758988
	.word	18283270
	.word	18283278
	.word	0
	.word	9239684
	.word	17235074
	.word	17758488
	.word	-268435456
	.word	-268435456
	.word	268435456
	.word	0
	.word	8715394
	.word	16349184
	.word	-2130248958
	.word	19331848
	.word	-268435456
	.word	-2129725072
	.word	18282794
	.word	18807144
	.word	-2147483648
	.word	16349184
	.word	287767304
	.word	0
	.word	8715016
	.word	0
	.word	536870912
	.word	10516480
	.word	8715042
	.word	277674784
	.word	546634532
	.word	33128448
	.word	1073741824
	.word	33128448
	.word	-2147483648
	.word	33128448
	.word	-1073741824
	.word	-268435456
	.word	268435456
	.word	8715046
	.word	0
	.word	-268435456
	.word	268435456
	.word	8715048
	.word	0
	.word	-268435456
	.word	268435456
	.word	8715050
	.word	0
	.word	0
	.word	1073741824
	.word	11565056
	.word	20380502
	.word	24935443
	.word	-1879048192
	.word	1898379590
	.word	0
	.word	0
	.word	0
	.word	16349184
	.word	0
	.word	33390592
	.word	-1879048192
	.word	17235104
	.word	17759394
	.word	33259520
	.word	1610612736
	.word	17235104
	.word	17758988
	.word	0
	.word	805306368
	.word	33259520
	.word	1610612736
	.word	9763988
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235104
	.word	19331386
	.word	0
	.word	19855676
	.word	0
	.word	0
	.word	825162046
	.word	0
	.word	0
	.word	805306368
	.word	11336850
	.word	19855662
	.word	0
	.word	11041962
	.word	0
	.word	10288278
	.word	19331388
	.word	18283278
	.word	0
	.word	805306368
	.word	9993387
	.word	17759394
	.word	0
	.word	805306368
	.word	10288280
	.word	1342177280
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235104
	.word	17758988
	.word	0
	.word	805306368
	.word	0
	.word	17234236
	.word	17758990
	.word	0
	.word	805306368
	.word	0
	.word	19855678
	.word	0
	.word	805306368
	.word	10288274
	.word	19855662
	.word	0
	.word	9993386
	.word	17234702
	.word	17759394
	.word	0
	.word	805306368
	.word	0
	.word	10288276
	.word	0
	.word	10288278
	.word	9993387
	.word	10288280
	.word	-1073741824
	.word	17235104
	.word	17759396
	.word	-1879048192
	.word	17235100
	.word	17758982
	.word	18283276
	.word	33259520
	.word	1342177280
	.word	17235100
	.word	17758988
	.word	0
	.word	805306368
	.word	33259520
	.word	805306368
	.word	9763988
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235100
	.word	19331386
	.word	0
	.word	19855676
	.word	0
	.word	0
	.word	825162046
	.word	0
	.word	0
	.word	805306368
	.word	11336850
	.word	19855662
	.word	0
	.word	11041962
	.word	0
	.word	10288278
	.word	19331388
	.word	18283278
	.word	0
	.word	805306368
	.word	9993387
	.word	17758982
	.word	823590036
	.word	0
	.word	10288280
	.word	1073741824
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235100
	.word	17758988
	.word	0
	.word	805306368
	.word	0
	.word	17234236
	.word	17758990
	.word	0
	.word	805306368
	.word	0
	.word	19855678
	.word	0
	.word	805306368
	.word	10288274
	.word	19855662
	.word	0
	.word	9993386
	.word	17234694
	.word	17759388
	.word	18283276
	.word	0
	.word	0
	.word	805306368
	.word	0
	.word	10288276
	.word	0
	.word	10288278
	.word	9993387
	.word	10288280
	.word	-1073741824
	.word	17235100
	.word	17758982
	.word	805306368
	.word	-1879048192
	.word	19331386
	.word	0
	.word	10288272
	.word	19331388
	.word	0
	.word	805306368
	.word	19331374
	.word	0
	.word	11041962
	.word	0
	.word	9239700
	.word	19331390
	.word	0
	.word	805306368
	.word	11336850
	.word	0
	.word	10288278
	.word	9993387
	.word	10288280
	.word	0
	.word	1090520577
	.word	9992192
	.word	-2147483648
	.word	-1610612736
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17758538
	.word	20380498
	.word	18807090
	.word	0
	.word	33128448
	.word	-1055983284
	.word	0
	.word	286194514
	.word	-268435456
	.word	-805306368
	.word	18282776
	.word	33128448
	.word	-1879048192
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	-1879048192
	.word	-1342177280
	.word	268435456
	.word	8420527
	.word	0
	.word	1090520576
	.word	9992192
	.word	-2147483648
	.word	-1610612736
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17234226
	.word	20380498
	.word	0
	.word	286194514
	.word	-268435456
	.word	-805306368
	.word	18282776
	.word	33128448
	.word	1073741824
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	1073741824
	.word	1610612736
	.word	268435456
	.word	8420527
	.word	0
	.word	18875904
	.word	0
	.word	1091044864
	.word	546863104
	.word	17827332
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17234772
	.word	0
	.word	17455440
	.word	16778756
	.word	33390592
	.word	-1342177280
	.word	1091044864
	.word	815298560
	.word	17827332
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17303041
	.word	17827336
	.word	33325056
	.word	-1879048192
	.word	17303072
	.word	33062912
	.word	268435456
	.word	285738497
	.word	18351620
	.word	-2147483648
	.word	0
	.word	17827352
	.word	33062912
	.word	1073741824
	.word	17303064
	.word	0
	.word	1091044864
	.word	815298560
	.word	17827352
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	536870912
	.word	1091044864
	.word	815298560
	.word	0
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	-536870912
	.word	1091044864
	.word	815298560
	.word	-2147483648
	.word	0
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	1342177280
	.word	1879048192
	.word	268435456
	.word	8420527
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1011712
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	17408
	.word	916484
	.word	1031168
	.word	1018880
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035272
	.word	0
	.word	1031172
	.word	0
	.word	1027080
	.word	0
	.word	1035361
	.word	16391
	.word	916544
	.word	1031176
	.word	16388
	.word	916544
	.word	1031176
	.word	0
	.word	18432
	.word	916544
	.word	1031176
	.word	916552
	.word	1031176
	.word	1035284
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031171
	.word	1018883
	.word	16384
	.word	17408
	.word	0
	.word	16384
	.word	0
	.word	1013760
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	593924
	.word	103056
	.word	103056
	.word	905516
	.word	1031176
	.word	589828
	.word	0
	.word	902208
	.word	916588
	.word	1031176
	.word	16384
	.word	1035355
	.word	1018888
	.word	0
	.word	1027079
	.word	0
	.word	1035361
	.word	16391
	.word	916544
	.word	1031176
	.word	16388
	.word	916544
	.word	1031176
	.word	0
	.word	18432
	.word	916544
	.word	1031176
	.word	916552
	.word	1031176
	.word	1035284
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031174
	.word	1018886
	.word	16384
	.word	17408
	.word	0
	.word	16384
	.word	0
	.word	1013760
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	593924
	.word	103056
	.word	103056
	.word	905516
	.word	1031176
	.word	589828
	.word	0
	.word	902208
	.word	916588
	.word	1031175
	.word	16384
	.word	1035355
	.word	1018888
	.word	0
	.word	1031176
	.word	0
	.word	1027080
	.word	0
	.word	1027080
	.word	16384
	.word	1035355
	.word	0
	.word	16384
	.word	0
	.word	0
	.word	1007616
	.word	0
	.word	0
	.word	589828
	.word	99972
	.word	622596
	.word	901164
	.word	1031182
	.word	0
	.word	109184
	.word	0
	.word	0
	.word	0
	.word	597444
	.word	107044
	.word	100000
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	589840
	.word	98332
	.word	592016
	.word	100508
	.word	0
	.word	902272
	.word	1031178
	.word	0
	.word	67204
	.word	0
	.word	0
	.word	1018891
	.word	17408
	.word	0
	.word	0
	.word	0
	.word	902208
	.word	67204
	.word	0
	.word	0
	.word	0
	.word	904392
	.word	69260
	.word	0
	.word	1035351
	.word	1035354
	.word	0
	.word	16384
	.word	916608
	.word	1031181
	.word	916612
	.word	1031181
	.word	916608
	.word	1031180
	.word	916608
	.word	1031180
	.word	1018894
	.word	1035295
	.word	0
	.word	1027086
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	98324
	.word	0
	.word	1035359
	.word	1018894
	.word	1035312
	.word	0
	.word	1027086
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	98324
	.word	0
	.word	1035359
	.word	1018894
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	983049
	.word	0
	.word	0
	.word	0
	.word	589828
	.word	0
	.word	99972
	.word	916484
	.word	1031188
	.word	916524
	.word	1031184
	.word	916524
	.word	1031188
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	597444
	.word	0
	.word	0
	.word	589840
	.word	98332
	.word	0
	.word	0
	.word	0
	.word	0
	.word	98308
	.word	0
	.word	916484
	.word	1031184
	.word	0
	.word	0
	.word	67204
	.word	0
	.word	0
	.word	1018897
	.word	0
	.word	0
	.word	902208
	.word	103044
	.word	67204
	.word	0
	.word	0
	.word	0
	.word	904400
	.word	69260
	.word	1035351
	.word	1035354
	.word	0
	.word	16384
	.word	916608
	.word	1031188
	.word	916612
	.word	1031188
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	0
	.word	1027092
	.word	16384
	.word	916544
	.word	1031186
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1018899
	.word	0
	.word	0
	.word	0
	.word	902208
	.word	67204
	.word	0
	.word	0
	.word	0
	.word	904392
	.word	69260
	.word	0
	.word	1035351
	.word	1035354
	.word	0
	.word	16384
	.word	916608
	.word	1031188
	.word	1018900
	.word	916612
	.word	1031188
	.word	1035322
	.word	1018900
	.word	1035322
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	999424
	.word	0
	.word	0
	.word	0
	.word	0
	.word	98308
	.word	0
	.word	0
	.word	0
	.word	102028
	.word	592972
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	589828
	.word	901164
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	67204
	.word	606212
	.word	69260
	.word	69260
	.word	69260
	.word	606220
	.word	0
	.word	16384
	.word	66176
	.word	0
	.word	0
	.word	0
	.word	20480
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	66176
	.word	66176
	.word	0
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	67204
	.word	606212
	.word	590920
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	67204
	.word	606212
	.word	1027096
	.word	0
	.word	1018905
	.word	0
	.word	1027096
	.word	1027096
	.word	1018905
	.word	0
	.word	1018905
	.word	0
	.word	1027097
	.word	1018905
	.word	0
	.word	1018905
	.word	67204
	.word	606212
	.word	606212
	.word	0
	.word	0
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	17409
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	17410
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	17414
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	0
	.word	17408
	.word	901124
	.word	1031195
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	17408
	.word	901124
	.word	1031196
	.word	16384
	.word	0
	.word	17409
	.word	98308
	.word	98308
	.word	66176
	.word	66176
	.word	18432
	.word	590980
	.word	67204
	.word	67204
	.word	606212
	.word	606212
	.word	0
	.word	18433
	.word	589832
	.word	66176
	.word	66176
	.word	590920
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	606212
	.word	18432
	.word	916552
	.word	1031198
	.word	916556
	.word	1031198
	.word	1018910
	.word	17408
	.word	1018910
	.word	17408
	.word	1018910
	.word	606212
	.word	0
	.word	0
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	589828
	.word	901164
	.word	0
	.word	17419
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	16384
	.word	0
	.word	17423
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	17423
	.word	589828
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	1035374
	.word	0
	.word	16385
	.word	916488
	.word	1031215
	.word	16384
	.word	916608
	.word	1031215
	.word	0
	.word	16388
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	16389
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	16390
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	916864
	.word	1031202
	.word	1031215
	.word	16390
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	16391
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	1018920
	.word	1035374
	.word	0
	.word	17408
	.word	902532
	.word	903560
	.word	605256
	.word	1031215
	.word	1035374
	.word	17408
	.word	902532
	.word	1031215
	.word	1035374
	.word	17408
	.word	902532
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	902532
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	902532
	.word	1031208
	.word	29696
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027110
	.word	20480
	.word	30720
	.word	16384
	.word	916800
	.word	1031206
	.word	1035372
	.word	0
	.word	104840
	.word	104848
	.word	595332
	.word	16384
	.word	906560
	.word	1031206
	.word	103060
	.word	16384
	.word	112696
	.word	917380
	.word	1031206
	.word	1018917
	.word	990244
	.word	29696
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027112
	.word	20480
	.word	30720
	.word	16384
	.word	916800
	.word	1031208
	.word	1035372
	.word	0
	.word	104840
	.word	104848
	.word	595332
	.word	16384
	.word	906560
	.word	1031208
	.word	103060
	.word	16384
	.word	112696
	.word	917380
	.word	1031208
	.word	1018919
	.word	990246
	.word	1018920
	.word	16384
	.word	0
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1027113
	.word	1018927
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031210
	.word	17408
	.word	916868
	.word	1031210
	.word	17408
	.word	916868
	.word	1031211
	.word	1018927
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031211
	.word	1018927
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	1035376
	.word	1035376
	.word	1035374
	.word	0
	.word	17423
	.word	916868
	.word	1031215
	.word	17408
	.word	916868
	.word	1031211
	.word	29696
	.word	110208
	.word	1035376
	.word	988203
	.word	1035374
	.word	16384
	.word	0
	.word	1035350
	.word	1035374
	.word	0
	.word	16384
	.word	916864
	.word	1031215
	.word	916868
	.word	1031215
	.word	1035374
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	916868
	.word	1031213
	.word	1018926
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	916864
	.word	1031215
	.word	916868
	.word	1031215
	.word	16384
	.word	916864
	.word	1031215
	.word	1018927
	.word	16384
	.word	0
	.word	16384
	.word	0
	.word	916864
	.word	1031215
	.word	916868
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	0
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031225
	.word	916872
	.word	1031225
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031225
	.word	916872
	.word	1031225
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031217
	.word	1018929
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	99412
	.word	0
	.word	1035359
	.word	0
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	1035374
	.word	17408
	.word	916868
	.word	1031225
	.word	1035374
	.word	0
	.word	17409
	.word	916868
	.word	1031225
	.word	1035374
	.word	0
	.word	17409
	.word	916868
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	916868
	.word	1031225
	.word	1035372
	.word	0
	.word	1035372
	.word	1035372
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	18432
	.word	0
	.word	901124
	.word	901128
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031225
	.word	20480
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	916880
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	916484
	.word	1031224
	.word	1018935
	.word	16384
	.word	0
	.word	1018937
	.word	16384
	.word	0
	.word	0
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	1035374
	.word	0
	.word	0
	.word	916868
	.word	1031254
	.word	1035374
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	1018966
	.word	17408
	.word	0
	.word	1018940
	.word	17408
	.word	0
	.word	1018940
	.word	17408
	.word	0
	.word	1035374
	.word	0
	.word	17423
	.word	916868
	.word	1031254
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031229
	.word	1018941
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	99412
	.word	0
	.word	1035359
	.word	0
	.word	1031254
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	99412
	.word	0
	.word	1035359
	.word	0
	.word	1031254
	.word	16384
	.word	18432
	.word	100492
	.word	1035350
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	1031232
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027136
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	98348
	.word	99436
	.word	294916
	.word	0
	.word	0
	.word	1031233
	.word	0
	.word	1031233
	.word	16384
	.word	294916
	.word	0
	.word	16384
	.word	99436
	.word	294916
	.word	17408
	.word	901124
	.word	0
	.word	18432
	.word	49160
	.word	589828
	.word	0
	.word	16384
	.word	916544
	.word	1031234
	.word	1035374
	.word	0
	.word	916868
	.word	1031254
	.word	16384
	.word	916544
	.word	1031235
	.word	16384
	.word	18432
	.word	100492
	.word	1035350
	.word	0
	.word	18432
	.word	50248
	.word	605188
	.word	1031235
	.word	1035376
	.word	0
	.word	18432
	.word	50308
	.word	605188
	.word	1031235
	.word	1035376
	.word	0
	.word	18432
	.word	50308
	.word	605188
	.word	1031235
	.word	1035376
	.word	0
	.word	1031236
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	16384
	.word	916484
	.word	1031236
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16384
	.word	916544
	.word	1031238
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031238
	.word	1035374
	.word	0
	.word	16384
	.word	916484
	.word	1031238
	.word	1035374
	.word	0
	.word	16384
	.word	916484
	.word	1031238
	.word	16386
	.word	0
	.word	16384
	.word	916484
	.word	1031239
	.word	16386
	.word	0
	.word	16384
	.word	916484
	.word	1031239
	.word	1018953
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031241
	.word	28672
	.word	16384
	.word	108548
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	17408
	.word	916868
	.word	1031241
	.word	17408
	.word	916868
	.word	1031241
	.word	18432
	.word	916872
	.word	1031241
	.word	17408
	.word	916868
	.word	1031241
	.word	1018953
	.word	1035376
	.word	1018953
	.word	1035376
	.word	983112
	.word	16384
	.word	902148
	.word	1031243
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031243
	.word	28672
	.word	16384
	.word	108548
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	17408
	.word	916868
	.word	1031243
	.word	17408
	.word	916868
	.word	1031243
	.word	18432
	.word	916872
	.word	1031243
	.word	17408
	.word	916868
	.word	1031243
	.word	1018955
	.word	1035376
	.word	1018955
	.word	1035376
	.word	983114
	.word	16384
	.word	18432
	.word	901124
	.word	1031244
	.word	1031244
	.word	1018956
	.word	0
	.word	916612
	.word	1031244
	.word	130284
	.word	1031244
	.word	1018956
	.word	1018961
	.word	1035374
	.word	0
	.word	1027148
	.word	1035374
	.word	28672
	.word	16384
	.word	108548
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027149
	.word	1035372
	.word	1035372
	.word	0
	.word	1027150
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027150
	.word	1035372
	.word	1035372
	.word	1035372
	.word	1035372
	.word	983116
	.word	16384
	.word	0
	.word	916484
	.word	1031249
	.word	916652
	.word	1031249
	.word	28672
	.word	16384
	.word	108548
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027152
	.word	1035372
	.word	1035372
	.word	0
	.word	1027153
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027153
	.word	1035372
	.word	1035372
	.word	1035372
	.word	1035372
	.word	983119
	.word	0
	.word	1027155
	.word	16384
	.word	916544
	.word	1031249
	.word	16384
	.word	0
	.word	1035350
	.word	1018963
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027155
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	1018963
	.word	1035374
	.word	1018963
	.word	1035374
	.word	1035374
	.word	17408
	.word	916484
	.word	1031250
	.word	0
	.word	1027156
	.word	17408
	.word	916484
	.word	1031252
	.word	18432
	.word	916488
	.word	1031252
	.word	1018964
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031254
	.word	1035372
	.word	0
	.word	0
	.word	1031253
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	0
	.word	916872
	.word	1031253
	.word	1035372
	.word	1035372
	.word	0
	.word	1031254
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	19456
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031255
	.word	1018967
	.word	16384
	.word	0
	.word	999424
	.word	22528
	.word	0
	.word	0
	.word	0
	.word	916632
	.word	1031256
	.word	594960
	.word	0
	.word	0
	.word	0
	.word	594964
	.word	71316
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1018969
	.word	595088
	.word	0
	.word	593936
	.word	906516
	.word	0
	.word	0
	.word	594964
	.word	71316
	.word	0
	.word	0
	.word	0
	.word	0
	.word	595092
	.word	71316
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	999424
	.word	22528
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	17409
	.word	591876
	.word	98944
	.word	592900
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	999424
	.word	17408
	.word	916484
	.word	1031260
	.word	0
	.word	21504
	.word	0
	.word	300368
	.word	99652
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	67204
	.word	67204
	.word	67204
	.word	606212
	.word	0
	.word	0
	.word	21504
	.word	0
	.word	300368
	.word	98624
	.word	0
	.word	1035359
	.word	1018975
	.word	0
	.word	21504
	.word	0
	.word	905516
	.word	300368
	.word	99652
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	99392
	.word	0
	.word	0
	.word	0
	.word	99392
	.word	916552
	.word	1031261
	.word	1018974
	.word	0
	.word	0
	.word	902208
	.word	902276
	.word	99460
	.word	0
	.word	0
	.word	0
	.word	67204
	.word	67204
	.word	67204
	.word	606212
	.word	0
	.word	0
	.word	21504
	.word	0
	.word	905516
	.word	300368
	.word	98624
	.word	0
	.word	1035359
	.word	0
	.word	16384
	.word	98560
	.word	0
	.word	999424
	.word	20480
	.word	0
	.word	20480
	.word	21504
	.word	22528
	.word	916688
	.word	1031264
	.word	916692
	.word	1031264
	.word	916696
	.word	1031264
	.word	1018976
	.word	16384
	.word	0
	.word	1013760
	.word	1018976
	.word	16384
	.word	0
	.word	1013760
	.word	1018976
	.word	16384
	.word	0
	.word	1013760
	.word	999424
	.word	22528
	.word	0
	.word	0
	.word	108184
	.word	1031265
	.word	19456
	.word	104664
	.word	596248
	.word	108184
	.word	0
	.word	17408
	.word	916484
	.word	1031270
	.word	0
	.word	0
	.word	916544
	.word	1031270
	.word	104088
	.word	0
	.word	903232
	.word	68232
	.word	903316
	.word	1027172
	.word	0
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	594176
	.word	905480
	.word	595264
	.word	102676
	.word	70288
	.word	102680
	.word	595220
	.word	104084
	.word	0
	.word	0
	.word	595220
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	593040
	.word	69260
	.word	0
	.word	0
	.word	904264
	.word	69260
	.word	0
	.word	1018982
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	903232
	.word	68232
	.word	903560
	.word	108168
	.word	0
	.word	589828
	.word	66176
	.word	100480
	.word	0
	.word	593044
	.word	102028
	.word	0
	.word	0
	.word	593044
	.word	0
	.word	0
	.word	0
	.word	904256
	.word	69260
	.word	904420
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	1018988
	.word	0
	.word	0
	.word	1018987
	.word	0
	.word	0
	.word	98308
	.word	916608
	.word	1031275
	.word	104088
	.word	0
	.word	903232
	.word	68232
	.word	903316
	.word	1027177
	.word	0
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	594176
	.word	905480
	.word	595264
	.word	102676
	.word	70288
	.word	102680
	.word	595220
	.word	104084
	.word	0
	.word	0
	.word	595220
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	593040
	.word	69260
	.word	0
	.word	0
	.word	67204
	.word	904264
	.word	0
	.word	1018987
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	903232
	.word	68232
	.word	903560
	.word	108168
	.word	0
	.word	589828
	.word	66176
	.word	100480
	.word	0
	.word	593044
	.word	102028
	.word	0
	.word	0
	.word	593044
	.word	0
	.word	0
	.word	0
	.word	0
	.word	903300
	.word	904200
	.word	69260
	.word	904420
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	1018988
	.word	0
	.word	0
	.word	67204
	.word	1018987
	.word	0
	.word	592912
	.word	0
	.word	0
	.word	592912
	.word	69260
	.word	101592
	.word	595152
	.word	0
	.word	902244
	.word	0
	.word	0
	.word	595152
	.word	104084
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	999424
	.word	19456
	.word	17408
	.word	66176
	.word	67204
	.word	606212
	.word	606216
	.word	0
	.word	1013760
	.word	16384
	.word	0
	.word	590936
	.word	596184
	.word	916544
	.word	1031277
	.word	612440
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031278
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031278
	.word	1018990
	.word	16384
	.word	0
	.word	999424
	.word	19456
	.word	17408
	.word	66176
	.word	67204
	.word	606212
	.word	606216
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	595992
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031280
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031280
	.word	1018992
	.word	16384
	.word	0
	.word	999424
	.word	21504
	.word	22528
	.word	19456
	.word	16384
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	0
	.word	113280
	.word	0
	.word	102660
	.word	916544
	.word	1031282
	.word	19456
	.word	16384
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	0
	.word	104836
	.word	916872
	.word	1031280
	.word	104080
	.word	916804
	.word	1031285
	.word	70288
	.word	102660
	.word	295128
	.word	905472
	.word	104080
	.word	916628
	.word	1031284
	.word	0
	.word	905476
	.word	19456
	.word	16384
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	1018995
	.word	19456
	.word	16384
	.word	101008
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	1018997
	.word	19456
	.word	16384
	.word	299224
	.word	903504
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031286
	.word	1018998
	.word	16384
	.word	0
	.word	999424
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65537
	.word	7208960
	.word	513
	.word	1537
	.word	319365736
	.word	319365736
	.word	9437306
	.word	5046372
	.word	0
	.word	0
	.word	1
	.word	131
	.word	16
	.word	2
	.word	24
	.word	256
	.word	263
	.word	3
	.word	351
	.word	4
	.word	64
	.word	127
	.word	262143
	.word	1048575
	.word	4194303
	.word	2147483647
	.word	-2147483648
	.word	-16
	.word	15
	.word	-128
	.word	8192
	.word	1048576
	.word	96000
	.word	-8
	.word	-1
	.word	262144
	.word	-524288
	.word	65280000
	.word	196612
	.word	131074
	.word	65537
	.word	65537
	.word	0
	.word	0
	.word	0
	.word	0
	.word	8
	.word	8160
	.word	255
	.word	0
	.word	1
	.word	5
	.word	8
	.word	7
	.word	64
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	g_hex_flag, %object
	.size	g_hex_flag, 4
g_hex_flag:
	.word	1
	.type	g_pScdDrvParamBase, %object
	.size	g_pScdDrvParamBase, 4
g_pScdDrvParamBase:
	.word	g_ScdDrvParam
	.type	g_pSmIISBase, %object
	.size	g_pSmIISBase, 4
g_pSmIISBase:
	.word	s_SmIIS
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"------------------ s_SmIIS[%d].SmInstArray --------"
	.ascii	"------------\012\000"
	.space	3
.LC1:
	.ascii	"%-25s :%d\012\000"
	.space	1
.LC2:
	.ascii	"Mode\000"
	.space	3
.LC3:
	.ascii	"Priority\000"
	.space	3
.LC4:
	.ascii	"VidStd\000"
	.space	1
.LC5:
	.ascii	"%-25s :0x%x\012\000"
	.space	3
.LC6:
	.ascii	"BufPhyAddr\000"
	.space	1
.LC7:
	.ascii	"pBufVirAddr\000"
.LC8:
	.ascii	"BufSize\000"
.LC9:
	.ascii	"RegPhyBaseAddr\000"
	.space	1
.LC10:
	.ascii	"SmPushRaw.PushRawNum\000"
	.space	3
.LC11:
	.ascii	"SmPushRaw.PushRawTotalLen\000"
	.space	2
.LC12:
	.ascii	"DownMsgPhyAddr\000"
	.space	1
.LC13:
	.ascii	"DownMsgSize\000"
.LC14:
	.ascii	"UpMsgPhyAddr\000"
	.space	3
.LC15:
	.ascii	"UpMsgNum\000"
	.space	3
.LC16:
	.ascii	"UpMsgSize\000"
	.space	2
.LC17:
	.ascii	"seg BufPhyAddr\000"
	.space	1
.LC18:
	.ascii	"seg BufSize\000"
.LC19:
	.ascii	"seg BufUsed\000"
.LC20:
	.ascii	"seg BufItemNum\000"
	.space	1
.LC21:
	.ascii	"raw StreamHold\000"
	.space	1
.LC22:
	.ascii	"raw StreamPacketNum\000"
.LC23:
	.ascii	"filter ProtocolType\000"
.LC24:
	.ascii	"filter ModeFlag\000"
.LC25:
	.ascii	"filter LastH263Num\000"
	.space	1
.LC26:
	.ascii	"filter SegBufPhyAddr\000"
	.space	3
.LC27:
	.ascii	"filter SegBufSize\000"
	.space	2
.LC28:
	.ascii	"filter SegBufRollAddr\000"
	.space	2
.LC29:
	.ascii	"filter pScdUpMsg\000"
	.space	3
.LC30:
	.ascii	"filter SegNum\000"
	.space	2
.LC31:
	.ascii	"BlockTimeInMs\000"
	.space	2
.LC32:
	.ascii	"LastBlockTime\000"
	.space	2
.LC33:
	.ascii	"%-25s :%lld\012\000"
	.space	3
.LC34:
	.ascii	"LastPts\000"
.LC35:
	.ascii	"ThisInstID\000"
	.space	1
.LC36:
	.ascii	"SCDState\000"
	.space	3
.LC37:
	.ascii	"\012raw packets Head : %d, Histroy : %d\012\000"
	.space	2
.LC38:
	.ascii	"\012raw packets length is(first packet %d bytes use"
	.ascii	"d):\012\000"
	.space	3
.LC39:
	.ascii	"\012\000"
	.space	2
.LC40:
	.ascii	"%5d \000"
	.space	3
.LC41:
	.ascii	"***Print Scd[%d] State Reg\012\000"
.LC42:
	.ascii	"Scdover = %d \012\000"
	.space	1
.LC43:
	.ascii	"ScdInt = %d \012\000"
	.space	2
.LC44:
	.ascii	"ShortScdNum = %d \012\000"
	.space	1
.LC45:
	.ascii	"ScdNum = %d \012\000"
	.space	2
.LC46:
	.ascii	"ScdRollAddr = %0x \012\000"
.LC47:
	.ascii	"SrcEaten = %d \012\000"
.LC48:
	.ascii	"***Print SCD[%d] Down Msg Now\012\000"
	.space	1
.LC49:
	.ascii	"DownMsgVirAddr = %x   \012\000"
.LC50:
	.ascii	"DownMsgPhyAddr = %x   \012\000"
.LC51:
	.ascii	"DownMsg[%d] = %x   \000"
.LC52:
	.ascii	"Error:now DspState[0]= %d,[1]= %d not except!!\012\000"
.LC53:
	.ascii	"line; %d, Flag = %d, pSmInstArray = %p\012\000"
.LC54:
	.ascii	"line: %d, SmID = %d is not expected!\012\000"
	.space	2
.LC55:
	.ascii	"line: %d, SmID = %d, ScdId = %d is not expected!\012"
	.ascii	"\000"
	.space	2
.LC56:
	.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000"
	.space	1
.LC57:
	.ascii	"-------- forece release seg[%d] -----------\012\000"
	.space	3
.LC58:
	.ascii	"0x%02x,\000"
.LC59:
	.ascii	"Release SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg"
	.ascii	"=%d StreamID=%d\012\000"
.LC60:
	.ascii	"Array out of bound in function %s\012\000"
	.space	1
.LC61:
	.ascii	"line: %d Get SmID fail!\000"
.LC62:
	.ascii	"DelRaw err PacketNum=%d,DelNum=%d\012\000"
	.space	1
.LC63:
	.ascii	"Release RawPhyAddr=0x%x,Len=%d\012\000"
.LC64:
	.ascii	"line: %d pSmInstArray is NULL!\012\000"
.LC65:
	.ascii	"SetMaxSegSize get eCapLevel failed!\012\000"
	.space	3
.LC66:
	.ascii	"SetMaxSegSize get ChanWidth/ChanHeight failed!\012\000"
.LC67:
	.ascii	"********** SmID [%d] SegState begin **********\012\000"
.LC68:
	.ascii	"SegHead=%d\012\000"
.LC69:
	.ascii	"SegTail=%d\012\000"
.LC70:
	.ascii	"SegCurrent=%d\012\000"
	.space	1
.LC71:
	.ascii	"SegBufPhyAddr=%p\012\000"
	.space	2
.LC72:
	.ascii	"SegBufVirAddr=%p\012\000"
	.space	2
.LC73:
	.ascii	"SegBufSize=%d\012\000"
	.space	1
.LC74:
	.ascii	"SegBufReadAddr=%p\012\000"
	.space	1
.LC75:
	.ascii	"SegBufWriteAddr=%pd\012\000"
	.space	3
.LC76:
	.ascii	"%s %d FMW_OK !=  GetSegStreamNum\012\000"
	.space	2
.LC77:
	.ascii	"********** SmID [%d] SegState end   **********\012\000"
.LC78:
	.ascii	"SegPhyAddr=0x%x\012\000"
	.space	3
.LC79:
	.ascii	"SegVirAddr=0x%x\012\000"
	.space	3
.LC80:
	.ascii	"SegLength=%d\012\000"
	.space	2
.LC81:
	.ascii	"SegStreamID=%d\012\000"
.LC82:
	.ascii	"SegState=%d\012\000"
	.space	3
.LC83:
	.ascii	"SegIsLastSeg=%d\012\000"
	.space	3
.LC84:
	.ascii	"SegPts=%lld\012\000"
	.space	3
.LC85:
	.ascii	"********** SmID [%d] RawState begin **********\012\000"
.LC86:
	.ascii	"RawHead=%d\012\000"
.LC87:
	.ascii	"RawTail=%d\012\000"
.LC88:
	.ascii	"RawHistory=%d\012\000"
	.space	1
.LC89:
	.ascii	"RawFirstPacketOffset=%d\012\000"
	.space	3
.LC90:
	.ascii	"CurShowIndex=%d\012\000"
	.space	3
.LC91:
	.ascii	"%s %d FMW_OK !=  GetRawStreamNum!!\012\000"
.LC92:
	.ascii	"********** SmID [%d] RawState end   **********\012\000"
.LC93:
	.ascii	"RawPhyAddr=0x%x\012\000"
	.space	3
.LC94:
	.ascii	"RawVirAddr=0x%x\012\000"
	.space	3
.LC95:
	.ascii	"RawLength=%d\012\000"
	.space	2
.LC96:
	.ascii	"RawPts=%ld\012\000"
.LC97:
	.ascii	"***Print Scd[%d] Vtrl Reg Now\012\000"
	.space	1
.LC98:
	.ascii	"DownMsgPhyAddr = %x\012\000"
	.space	3
.LC99:
	.ascii	"UpMsgPhyAddr = %x\012\000"
	.space	1
.LC100:
	.ascii	"UpLen = %x\012\000"
.LC101:
	.ascii	"BufferFirst = %x\012\000"
	.space	2
.LC102:
	.ascii	"BufferLast = %x\012\000"
	.space	3
.LC103:
	.ascii	"BufferIni = %x\012\000"
.LC104:
	.ascii	"ScdProtocol = %x\012\000"
	.space	2
.LC105:
	.ascii	"ScdStart = %x\012\000"
	.space	1
.LC106:
	.ascii	"%s %d FMW_OK !=  GetSegStreamNum!!\012\000"
.LC107:
	.ascii	"scd time out: t_start,t_now,t_wait = %d,%d,%d\012\000"
	.space	1
.LC108:
	.ascii	"ResetSCD ERROR!!!\012\000"
	.space	1
.LC109:
	.ascii	"%s,%d,SCD(ID = %d) SCDState = %d\012\000"
	.space	2
.LC110:
	.ascii	"%s,%d,SCD(ID = %d) return Idle!\012\000"
	.space	3
.LC111:
	.ascii	"SCD[%d] Time Out(%d ms), Reset SCD!\012\000"
	.space	3
.LC112:
	.ascii	"%s,%d,SCD(ID = %d) really busy!\012\000"
	.space	3
.LC113:
	.ascii	"%s: pRawPacket = NULL!\012\000"
.LC114:
	.ascii	"%s: unkown standard type = %d!\012\000"
.LC115:
	.ascii	"%s: FlagLen(%d) > RawPacketLength(%d)\012\000"
	.space	1
.LC116:
	.ascii	"Read_seg SegPacket.PhyAddr=0x%x, LenByte=%d, IsLast"
	.ascii	"Seg=%d\012\000"
	.space	1
.LC117:
	.ascii	"Chan %d has been destroyed or the function pointer "
	.ascii	"-- ReleaseRawStreamData pStreamIntf is NULL!\000"
.LC118:
	.ascii	"line: %d s_SmIIS[%d].pSmInstArray is NULL\012\000"
	.space	1
.LC119:
	.ascii	"No space for raw move, total:%d+%d > max:%d!\012\000"
	.space	2
.LC120:
	.ascii	"SmID = %d is not expected!\012\000"
.LC121:
	.ascii	"RawStreamNum=%d\012\000"
	.space	3
.LC122:
	.ascii	"SegStreamNum=%d\012\000"
	.space	3
.LC123:
	.ascii	"SegStreamSize=%d\012\000"
	.space	2
.LC124:
	.ascii	"SM_CfgBuf Err! ret =%d\012\000"
.LC125:
	.ascii	"RawStreamSize=%d\012\000"
	.space	2
.LC126:
	.ascii	"Raw packet(VFMW_RAW YUV) TOO BIG(maybe caused by w/"
	.ascii	"h... err)! can't copy to seg!\012\000"
	.space	2
.LC127:
	.ascii	"line: %d, delet raw failed!\012\000"
	.space	3
.LC128:
	.ascii	"VFMW_RAW YUV disp w/h err)! discard raw packet!\012"
	.ascii	"\000"
	.space	3
.LC129:
	.ascii	"SM_DoNextInstance parm 1:scdId(%d) Error!\012\000"
	.space	1
.LC130:
	.ascii	"VFMW_RAW SM_CopyYuvToDnr fail\012\000"
	.space	1
.LC131:
	.ascii	"long time(%d ms) not release stream seg, release an"
	.ascii	"yway!\012\000"
	.space	2
.LC132:
	.ascii	"%s,%d, active scd Success!\012\000"
.LC133:
	.ascii	"line: %d, SmID = %d, pSmCfg = %p is not expected!\012"
	.ascii	"\000"
	.space	1
.LC134:
	.ascii	"line: %d, pSmInstArray is NULL!\012\000"
	.space	3
.LC135:
	.ascii	"%s: RawPacket Length %d <= 0\012\000"
	.space	2
.LC136:
	.ascii	"%s(): Std(%d) buffer has no enough space,(act:%d, h"
	.ascii	"eader_buf:%d)\012\000"
	.space	2
.LC137:
	.ascii	"%s(): Std(%d) buffer has no enough space,(act:%d, s"
	.ascii	"tr_buf:%d)\012\000"
	.space	1
.LC138:
	.ascii	"%s(): Std(%d) buffer has no enough space,(act:%d, s"
	.ascii	"tr_buf:%d, header_buf:%d)\012\000"
	.space	2
.LC139:
	.ascii	"%s(): Std(%d) buffer has no enough space, (act:%d, "
	.ascii	"str_buf:%d)\012\000"
.LC140:
	.ascii	"Chan %d has been destroyed or the function pointer "
	.ascii	"-- ReadRawStreamData pStreamIntf is NULL!\000"
	.space	3
.LC141:
	.ascii	"line: %d s_SmIIS.pSmInstArray[%d] is NULL\012\000"
	.space	1
.LC142:
	.ascii	"Chan %d FillEosRawStream failed!\012\000"
	.space	2
.LC143:
	.ascii	"Chan %d FillExtraData failed!\012\000"
	.space	1
.LC144:
	.ascii	"Release this packet failed!\012\000"
	.space	3
.LC145:
	.ascii	"raw_pts: %lld\012\000"
	.space	1
.LC146:
	.ascii	"Get RawPhyAddr=0x%x,Len=%d\012\000"
.LC147:
	.ascii	"!!!push raw err!!!\012\000"
.LC148:
	.ascii	"DisContinueRawPacket found! %d ---> %d\012\000"
.LC149:
	.ascii	"Chan%d raw full\012\000"
	.space	3
.LC150:
	.ascii	"%s,%d, prepare to check SCD(%d) !(MAX_SCD_NUM = %d)"
	.ascii	"\012\000"
	.space	3
.LC151:
	.ascii	"%s,%d,find idle SCD(ID = %d)\012\000"
	.space	2
.LC152:
	.ascii	"%s,%d,SCD(ID = %d) return BUSY!!\012\000"
	.space	2
.LC153:
	.ascii	"RawNum %lld <= RawNumInVfmw %lld\012\000"
	.space	2
.LC154:
	.ascii	"***Print Up Msg Now\012\000"
	.space	3
.LC155:
	.ascii	"ScdUpMsg[%d] = 0x%x\012\000"
	.space	3
.LC156:
	.ascii	"line:%d ReadScdSegNum = %d, FilterScdSegNum = 0 rel"
	.ascii	"ease raw packet anyway!\012\000"
.LC157:
	.ascii	"Error! (PushRawTotalLen - SrcEaten) > SM_RAW_DISCAR"
	.ascii	"D_SIZE, packet discard...\012\000"
	.space	2
.LC158:
	.ascii	"Insert err Scd SegPacket.PhyAddr=0x%x,LenByte=%d,Is"
	.ascii	"LastSeg=%d\012\000"
	.space	1
.LC159:
	.ascii	"RawLen = %d, Pts = %ld, \012\000"
	.space	2
.LC160:
	.ascii	"Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\012"
	.ascii	"\000"
.LC161:
	.ascii	"line %d CheckSeg err\012\000"
	.space	2
.LC162:
	.ascii	"line %d SegFreeBufLen=%d,SrcEaten=%d\000"
	.space	3
.LC163:
	.ascii	"line %d Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLas"
	.ascii	"tSeg=%d\012\000"
.LC164:
	.ascii	"RawLen = %d, Pts =  %lld, \012\000"
.LC165:
	.ascii	"CheckSeg err\012\000"
	.space	2
.LC166:
	.ascii	"SegFreeBufLen=%d,SrcEaten=%d\000"
	.space	3
.LC167:
	.ascii	"%s %d FMW_OK != GetSegStreamNum!!\012\000"
	.space	1
.LC168:
	.ascii	"Insert 2 err Scd SegPacket.PhyAddr=0x%x,LenByte=%d,"
	.ascii	"IsLastSeg=%d\012\000"
	.space	3
.LC169:
	.ascii	"ReadScdSegNum = %d, FilterScdSegNum = 0 release raw"
	.ascii	" packet anyway!\012\000"
.LC170:
	.ascii	"Raw packet TOO BIG! can't copy to seg! Len: %#x\012"
	.ascii	"\000"
	.space	3
.LC171:
	.ascii	"copy raw to seg fail\012\000"
	.space	2
.LC172:
	.ascii	"Fatal: get g_hex_base_addr(0x%x) vir addr failed!\012"
	.ascii	"\000"
	.space	1
.LC173:
	.ascii	"Warn: eVidStd = %d have not DSP vfmw bin file!!\012"
	.ascii	"\000"
	.space	3
.LC174:
	.ascii	"line: %d, p = NULL is not expected value!\012\000"
	.space	1
.LC175:
	.ascii	"ScdId is wrong! %s error\012\000"
	.space	2
.LC176:
	.ascii	"%s,line: %d\012\000"
	.space	3
.LC177:
	.ascii	"%s: pScdDrvParam->ScdDrvMem.pDvmMemVirAddr = NULL\012"
	.ascii	"\000"
	.space	1
.LC178:
	.ascii	"%s: pScdDrvParam->ScdDrvMem.pDspSedTopMemVirAddr = "
	.ascii	"NULL\012\000"
	.space	3
.LC179:
	.ascii	"%s: pScdDrvParam->ScdDrvMem.pDspCaMnMemVirAddr = NU"
	.ascii	"LL\012\000"
	.space	1
.LC180:
	.ascii	"%s: g_hex_base_vir_addr = NULL\012\000"
.LC181:
	.ascii	"%s: ScdId(%d) > %d\012\000"
.LC182:
	.ascii	"Move raw data failed, force to reset scd.\012\000"
	.space	1
.LC183:
	.ascii	"VFMW_DspCtxMem\000"
	.space	1
.LC184:
	.ascii	"%s Alloc mem for DSP (SPS PPS) failed!\012\000"
.LC185:
	.ascii	"%s pDspSpsMsgMemVirAddr is NULL!\012\000"
	.space	2
.LC186:
	.ascii	"%s pDspPpsMsgMemVirAddr is NULL!\012\000"
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	s_SmIIS, %object
	.size	s_SmIIS, 768
s_SmIIS:
	.space	768
	.type	s_eScdDrvSleepStage, %object
	.size	s_eScdDrvSleepStage, 4
s_eScdDrvSleepStage:
	.space	4
	.type	g_ScdDrvParam, %object
	.size	g_ScdDrvParam, 96
g_ScdDrvParam:
	.space	96
	.type	s_RegPhyBaseAddr, %object
	.size	s_RegPhyBaseAddr, 4
s_RegPhyBaseAddr:
	.space	4
	.type	last_rec_pos_time.52786, %object
	.size	last_rec_pos_time.52786, 64
last_rec_pos_time.52786:
	.space	64
	.type	last_rec_pos_time.52118, %object
	.size	last_rec_pos_time.52118, 64
last_rec_pos_time.52118:
	.space	64
	.type	g_hex_base_addr, %object
	.size	g_hex_base_addr, 4
g_hex_base_addr:
	.space	4
	.type	s_RegPhyBaseAddr_1, %object
	.size	s_RegPhyBaseAddr_1, 4
s_RegPhyBaseAddr_1:
	.space	4
	.type	g_hex_base_vir_addr, %object
	.size	g_hex_base_vir_addr, 4
g_hex_base_vir_addr:
	.space	4
	.type	g_hex_len, %object
	.size	g_hex_len, 4
g_hex_len:
	.space	4
	.type	LastEventTime.51106, %object
	.size	LastEventTime.51106, 4
LastEventTime.51106:
	.space	4
	.type	s_SCDInISR, %object
	.size	s_SCDInISR, 4
s_SCDInISR:
	.space	4
	.type	last_rec_pos_time.52937, %object
	.size	last_rec_pos_time.52937, 64
last_rec_pos_time.52937:
	.space	64
	.type	ForceRelease, %object
	.size	ForceRelease, 4
ForceRelease:
	.space	4
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
