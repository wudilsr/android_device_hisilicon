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
	.file	"vdm_drv.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(vdm_drv)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_vfmw) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/vfmw/vfmw_v4.0/firmware/common/.vdm_drv.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/vfmw/vfmw_v4.0/firmware/common/vdm_drv.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/vfmw/vfmw_v4.0/firmware/common/vdm_drv.o -O2 -Wall -Wundef
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
	.global	VDMDRV_SetPriority
	.type	VDMDRV_SetPriority, %function
VDMDRV_SetPriority:
	.fnstart
.LFB1530:
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
	movw	r2, #:lower16:.LANCHOR0	@ tmp198,
	movt	r2, #:upper16:.LANCHOR0	@ tmp198,
	mov	r3, #0	@ i,
	mov	ip, r3	@ MaxPrioChanID, i
	mov	r6, r3	@ MaxPrio.575, i
	mov	r4, r2	@ ivtmp.572, tmp198
	b	.L2	@
.L3:
	add	r3, r3, #1	@ i, i,
	str	ip, [r4, #64]	@ MaxPrioChanID,
	cmp	r3, #16	@ i,
	str	r6, [r0, ip, asl #2]	@ MaxPrio.575,* pPrioArray
	add	r4, r4, #4	@ ivtmp.572, ivtmp.572,
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L2:
	ldmia	r0, {r1, r5}	@ phole ldm
	cmp	r1, #0	@ MaxPrio.575,
	movle	r1, #0	@ MaxPrio.575,
	movgt	ip, #0	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.577
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.577
	ldr	r5, [r0, #8]	@ MaxPrio.579,
	movlt	ip, #1	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.579
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.579
	ldr	r5, [r0, #12]	@ MaxPrio.581,
	movlt	ip, #2	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.581
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.581
	ldr	r5, [r0, #16]	@ MaxPrio.583,
	movlt	ip, #3	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.583
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.583
	ldr	r5, [r0, #20]	@ MaxPrio.585,
	movlt	ip, #4	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.585
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.585
	ldr	r5, [r0, #24]	@ MaxPrio.587,
	movlt	ip, #5	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.587
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.587
	ldr	r5, [r0, #28]	@ MaxPrio.589,
	movlt	ip, #6	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.589
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.589
	ldr	r5, [r0, #32]	@ MaxPrio.591,
	movlt	ip, #7	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.591
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.591
	ldr	r5, [r0, #36]	@ MaxPrio.593,
	movlt	ip, #8	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.593
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.593
	ldr	r5, [r0, #40]	@ MaxPrio.595,
	movlt	ip, #9	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.595
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.595
	ldr	r5, [r0, #44]	@ MaxPrio.597,
	movlt	ip, #10	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.597
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.597
	ldr	r5, [r0, #48]	@ MaxPrio.599,
	movlt	ip, #11	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.599
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.599
	ldr	r5, [r0, #52]	@ MaxPrio.601,
	movlt	ip, #12	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.601
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.601
	ldr	r5, [r0, #56]	@ MaxPrio.603,
	movlt	ip, #13	@ MaxPrioChanID,
	cmp	r1, r5	@ MaxPrio.575, MaxPrio.603
	movlt	r1, r5	@ MaxPrio.575, MaxPrio.603
	ldr	r5, [r0, #60]	@ MaxPrio,
	movlt	ip, #14	@ MaxPrioChanID,
	cmp	r5, r1	@ MaxPrio, MaxPrio.575
	movgt	r1, r5	@ MaxPrio.575, MaxPrio
	movgt	ip, #15	@ MaxPrioChanID,
	cmp	r1, #0	@ MaxPrio.575,
	bgt	.L3	@,
	cmp	r3, #15	@ i,
	ldmgtfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	mov	r0, r3, asl #2	@ ivtmp.555, i,
	add	r1, r3, #1	@ j.574, i,
	add	r4, r0, r2	@ tmp194, ivtmp.555, tmp198
	cmp	r1, #15	@ j.574,
	rsb	r3, r3, #15	@ tmp208, i,
	mvn	ip, #0	@ tmp199,
	add	r0, r0, #4	@ ivtmp.555, ivtmp.555,
	and	r3, r3, #1	@ tmp209, tmp208,
	str	ip, [r4, #64]	@ tmp199,
	ldmgtfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	cmp	r3, #0	@ tmp209,
	beq	.L5	@,
	add	r1, r1, #1	@ j.574, j.574,
	add	r3, r0, r2	@ tmp222, ivtmp.555, tmp198
	cmp	r1, #15	@ j.574,
	add	r0, r0, #4	@ ivtmp.555, ivtmp.555,
	str	ip, [r3, #64]	@ tmp199,
	ldmgtfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L5:
	add	r3, r0, #4	@ tmp211, ivtmp.555,
	add	r1, r1, #2	@ j.574, j.574,
	add	r5, r0, r2	@ tmp214, ivtmp.555, tmp198
	add	r4, r3, r2	@ tmp219, tmp211, tmp198
	cmp	r1, #15	@ j.574,
	add	r0, r3, #4	@ ivtmp.555, tmp211,
	str	ip, [r5, #64]	@ tmp199,
	str	ip, [r4, #64]	@ tmp199,
	ble	.L5	@,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDMDRV_SetPriority, .-VDMDRV_SetPriority
	.align	2
	.global	VDMDRV_AdjustPriorityAfterDec
	.type	VDMDRV_AdjustPriorityAfterDec, %function
VDMDRV_AdjustPriorityAfterDec:
	.fnstart
.LFB1531:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp189,
	movt	r3, #:upper16:.LANCHOR0	@ tmp189,
	ldr	r2, [r3, #64]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	r2, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #0	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	r1, [r3, #68]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	r1, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #1	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	r8, [r3, #72]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	r8, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #2	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	ip, [r3, #76]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	ip, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #3	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	r2, [r3, #80]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	r2, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #4	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	r1, [r3, #84]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	r1, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #5	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	r8, [r3, #88]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	r8, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #6	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	ip, [r3, #92]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	ip, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #7	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	r2, [r3, #96]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	r2, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #8	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	r1, [r3, #100]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	r1, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #9	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	ip, [r3, #104]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	movw	r8, #:lower16:.LANCHOR0	@ tmp162,
	movt	r8, #:upper16:.LANCHOR0	@ tmp162,
	cmp	ip, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #10	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	r2, [r8, #108]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	r2, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #11	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	r1, [r8, #112]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	r1, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #12	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	ip, [r8, #116]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	ip, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	moveq	r6, #13	@ i.448,
	moveq	r4, r6	@ i, i.448
	beq	.L34	@,
	ldr	r2, [r8, #120]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	r2, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	beq	.L48	@,
	ldr	r1, [r8, #124]	@ g_ChanCtx.ChanIdTabByPrior, g_ChanCtx.ChanIdTabByPrior
	cmp	r1, r0	@ g_ChanCtx.ChanIdTabByPrior, CurChanId
	beq	.L54	@,
	mov	r6, #0	@ i.448,
	add	r8, r8, #68	@ D.38560, tmp162,
	mov	r4, r6	@ i, i.448
	b	.L53	@
.L52:
	ldr	ip, [r2, r1]	@ D.38561,* ivtmp.655
	add	r1, r5, #4	@ ivtmp.655, tmp192,
	cmp	ip, #0	@ D.38561,
	blt	.L54	@,
	ldr	r7, [r2, r0, asl #2]	@ temp.657,
	ldr	sl, [r3, ip, asl #2]	@,
	ldr	r9, [r3, r7, asl #2]	@,
	cmp	sl, r9	@,
	strge	ip, [r2, r0, asl #2]	@ D.38561,
	ldrge	sl, [fp, #-48]	@, %sfp
	strge	r7, [sl, #0]	@ temp.657,
	ldr	ip, [r2, r5]	@ D.38561,
	cmp	ip, #0	@ D.38561,
	blt	.L54	@,
.L50:
	ldr	r7, [r2, r6, asl #2]	@ temp.657,
	add	r9, r2, r1	@, tmp188, ivtmp.655
	str	r9, [fp, #-48]	@, %sfp
	add	r0, r4, #1	@ tmp193, i,
	ldr	sl, [r3, ip, asl #2]	@,
	add	r4, r0, #1	@ i, tmp193,
	ldr	r9, [r3, r7, asl #2]	@,
	add	r5, r1, #4	@ tmp192, ivtmp.655,
	cmp	sl, r9	@,
	strge	ip, [r2, r6, asl #2]	@ D.38561,
	strge	r7, [r8, #0]	@ temp.657,* D.38560
	cmp	r0, #14	@ tmp193,
	mov	r6, r4	@ i.448, i
	add	r8, r2, r5	@ D.38560, tmp188, tmp192
	ble	.L52	@,
.L54:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L48:
	mov	r6, #14	@ i.448,
	mov	r4, r6	@ i, i.448
.L34:
	add	r8, r6, #1	@ pretmp.638, i.448,
	ldr	ip, .L64	@ tmp199,
	add	r8, ip, r8, asl #2	@, D.38560, tmp199, pretmp.638,
.L53:
	ldr	ip, [r8, #0]	@ D.38561,* D.38560
	cmp	ip, #0	@ D.38561,
	blt	.L54	@,
	add	r0, r6, #2	@ tmp175, i.448,
	tst	r4, #1	@ i,
	ldr	r2, .L64	@ tmp188,
	mov	r1, r0, asl #2	@ ivtmp.655, tmp175,
	beq	.L50	@,
	add	r6, r2, r6, asl #2	@, D.38553, tmp188, i.448,
	ldr	r7, [r3, ip, asl #2]	@ tmp203,
	add	r4, r4, #1	@ i, i,
	ldr	r0, [r6, #0]	@ temp.657,* D.38553
	ldr	r5, [r3, r0, asl #2]	@ tmp204,
	cmp	r7, r5	@ tmp203, tmp204
	strge	ip, [r6, #0]	@ D.38561,* D.38553
	strge	r0, [r8, #0]	@ temp.657,* D.38560
	cmp	r4, #14	@ i,
	bgt	.L54	@,
	add	r8, r2, r1	@ D.38560, tmp188, ivtmp.655
	mov	r6, r4	@ i.448, i
	add	r1, r1, #4	@ ivtmp.655, ivtmp.655,
	ldr	ip, [r8, #0]	@ D.38561,* D.38560
	cmp	ip, #0	@ D.38561,
	bge	.L50	@,
	b	.L54	@
.L65:
	.align	2
.L64:
	.word	.LANCHOR0+64
	.fnend
	.size	VDMDRV_AdjustPriorityAfterDec, .-VDMDRV_AdjustPriorityAfterDec
	.align	2
	.global	VDMDRV_PrepareSleep
	.type	VDMDRV_PrepareSleep, %function
VDMDRV_PrepareSleep:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp136,
	movt	r3, #:upper16:.LANCHOR0	@ tmp136,
	add	r2, r3, r0, asl #2	@, tmp139, tmp136, VdhId,
	ldr	r1, [r2, #192]	@ tmp141, s_eVdmDrvSleepState
	cmp	r1, #0	@ tmp141,
	mvnne	r0, #0	@ ret,
	ldmnefd	sp, {fp, sp, pc}	@
	rsb	r0, r0, r0, asl #3	@, tmp146, VdhId, VdhId,
	add	r3, r3, r0, asl #3	@, tmp148, tmp136, tmp146,
	ldr	r0, [r3, #196]	@ <variable>.VdmStateMachine, <variable>.VdmStateMachine
	cmp	r0, #0	@ <variable>.VdmStateMachine,
	moveq	r3, #2	@ tmp156,
	movne	r3, #1	@ tmp162,
	streq	r3, [r2, #192]	@ tmp156, s_eVdmDrvSleepState
	movne	r0, r1	@ ret, tmp141
	strne	r3, [r2, #192]	@ tmp162, s_eVdmDrvSleepState
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_PrepareSleep, .-VDMDRV_PrepareSleep
	.align	2
	.global	VDMDRV_GetSleepStage
	.type	VDMDRV_GetSleepStage, %function
VDMDRV_GetSleepStage:
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
	movw	r1, #:lower16:.LANCHOR0	@ tmp136,
	movt	r1, #:upper16:.LANCHOR0	@ tmp136,
	add	r3, r1, r0, asl #2	@, tmp139, tmp136, VdhId,
	ldr	r0, [r3, #192]	@, s_eVdmDrvSleepState
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_GetSleepStage, .-VDMDRV_GetSleepStage
	.align	2
	.global	VDMDRV_IsChanDec
	.type	VDMDRV_IsChanDec, %function
VDMDRV_IsChanDec:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp136,
	add	r1, r0, #32	@ tmp137, ChanID,
	movt	r3, #:upper16:.LANCHOR0	@ tmp136,
	ldr	r0, [r3, r1, asl #2]	@ tmp138, g_ChanCtx.ChanDecByVdhPlusOne
	subs	r0, r0, #0	@, tmp138,
	movne	r0, #1	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_IsChanDec, .-VDMDRV_IsChanDec
	.align	2
	.global	VDMDRV_SetChanIsDec
	.type	VDMDRV_SetChanIsDec, %function
VDMDRV_SetChanIsDec:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp135,
	add	r2, r0, #32	@ tmp136, ChanID,
	movt	r3, #:upper16:.LANCHOR0	@ tmp135,
	add	r1, r1, #1	@ tmp137, VdhID,
	str	r1, [r3, r2, asl #2]	@ tmp137, g_ChanCtx.ChanDecByVdhPlusOne
	bl	VDMDRV_AdjustPriorityAfterDec	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_SetChanIsDec, .-VDMDRV_SetChanIsDec
	.align	2
	.global	VDMDRV_ClearChanIsDec
	.type	VDMDRV_ClearChanIsDec, %function
VDMDRV_ClearChanIsDec:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp134,
	add	r0, r0, #32	@ tmp135, ChanID,
	movt	r3, #:upper16:.LANCHOR0	@ tmp134,
	mov	r2, #0	@ tmp136,
	str	r2, [r3, r0, asl #2]	@ tmp136, g_ChanCtx.ChanDecByVdhPlusOne
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_ClearChanIsDec, .-VDMDRV_ClearChanIsDec
	.align	2
	.global	VDMDRV_ParamInit
	.type	VDMDRV_ParamInit, %function
VDMDRV_ParamInit:
	.fnstart
.LFB1541:
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
	movw	r0, #:lower16:s_pstVfmwChan	@ tmp181,
	movt	r0, #:upper16:s_pstVfmwChan	@ tmp181,
	ldr	r2, [r0, #0]	@ temp.809, s_pstVfmwChan
	cmp	r2, #0	@ temp.809,
	movne	r1, #1	@ tmp150,
	strne	r1, [r2, #20]	@ tmp150, <variable>.s32IsInit
	ldr	ip, [r0, #4]	@ temp.810, s_pstVfmwChan
	cmp	ip, #0	@ temp.810,
	movne	r1, #1	@ tmp152,
	strne	r1, [ip, #20]	@ tmp152, <variable>.s32IsInit
	ldr	r3, [r0, #8]	@ temp.811, s_pstVfmwChan
	cmp	r3, #0	@ temp.811,
	movne	r1, #1	@ tmp154,
	strne	r1, [r3, #20]	@ tmp154, <variable>.s32IsInit
	ldr	r2, [r0, #12]	@ temp.812, s_pstVfmwChan
	cmp	r2, #0	@ temp.812,
	movne	r1, #1	@ tmp156,
	strne	r1, [r2, #20]	@ tmp156, <variable>.s32IsInit
	ldr	ip, [r0, #16]	@ temp.813, s_pstVfmwChan
	cmp	ip, #0	@ temp.813,
	movne	r1, #1	@ tmp158,
	strne	r1, [ip, #20]	@ tmp158, <variable>.s32IsInit
	ldr	r3, [r0, #20]	@ temp.814, s_pstVfmwChan
	cmp	r3, #0	@ temp.814,
	movne	r1, #1	@ tmp160,
	strne	r1, [r3, #20]	@ tmp160, <variable>.s32IsInit
	ldr	r2, [r0, #24]	@ temp.815, s_pstVfmwChan
	cmp	r2, #0	@ temp.815,
	movne	r1, #1	@ tmp162,
	strne	r1, [r2, #20]	@ tmp162, <variable>.s32IsInit
	ldr	ip, [r0, #28]	@ temp.816, s_pstVfmwChan
	cmp	ip, #0	@ temp.816,
	movne	r1, #1	@ tmp164,
	strne	r1, [ip, #20]	@ tmp164, <variable>.s32IsInit
	ldr	r3, [r0, #32]	@ temp.817, s_pstVfmwChan
	cmp	r3, #0	@ temp.817,
	movne	r1, #1	@ tmp166,
	strne	r1, [r3, #20]	@ tmp166, <variable>.s32IsInit
	ldr	r2, [r0, #36]	@ temp.818, s_pstVfmwChan
	cmp	r2, #0	@ temp.818,
	movne	r1, #1	@ tmp168,
	strne	r1, [r2, #20]	@ tmp168, <variable>.s32IsInit
	ldr	ip, [r0, #40]	@ temp.819, s_pstVfmwChan
	cmp	ip, #0	@ temp.819,
	movne	r1, #1	@ tmp170,
	strne	r1, [ip, #20]	@ tmp170, <variable>.s32IsInit
	ldr	r3, [r0, #44]	@ temp.820, s_pstVfmwChan
	cmp	r3, #0	@ temp.820,
	movne	r1, #1	@ tmp172,
	strne	r1, [r3, #20]	@ tmp172, <variable>.s32IsInit
	ldr	r2, [r0, #48]	@ temp.821, s_pstVfmwChan
	cmp	r2, #0	@ temp.821,
	movne	r1, #1	@ tmp174,
	strne	r1, [r2, #20]	@ tmp174, <variable>.s32IsInit
	ldr	ip, [r0, #52]	@ temp.822, s_pstVfmwChan
	cmp	ip, #0	@ temp.822,
	movne	r1, #1	@ tmp176,
	strne	r1, [ip, #20]	@ tmp176, <variable>.s32IsInit
	ldr	r2, [r0, #56]	@ temp.823, s_pstVfmwChan
	cmp	r2, #0	@ temp.823,
	movne	r1, #1	@ tmp178,
	strne	r1, [r2, #20]	@ tmp178, <variable>.s32IsInit
	ldr	r3, [r0, #60]	@ D.38655, s_pstVfmwChan
	cmp	r3, #0	@ D.38655,
	movne	r2, #1	@ tmp180,
	strne	r2, [r3, #20]	@ tmp180, <variable>.s32IsInit
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_ParamInit, .-VDMDRV_ParamInit
	.align	2
	.global	VDMDRV_AddMatchMode
	.type	VDMDRV_AddMatchMode, %function
VDMDRV_AddMatchMode:
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
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_AddMatchMode, .-VDMDRV_AddMatchMode
	.align	2
	.global	VDMDRV_IsVdmInISR
	.type	VDMDRV_IsVdmInISR, %function
VDMDRV_IsVdmInISR:
	.fnstart
.LFB1550:
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
	add	r3, r1, r0, asl #2	@, tmp139, tmp136, VdhId,
	ldr	r0, [r3, #252]	@, s_VdmIsInISR
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_IsVdmInISR, .-VDMDRV_IsVdmInISR
	.align	2
	.global	VDMDRV_IsVdmIdle
	.type	VDMDRV_IsVdmIdle, %function
VDMDRV_IsVdmIdle:
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
	rsb	r2, r0, r0, asl #3	@, tmp140, VdhId, VdhId,
	movw	r1, #:lower16:.LANCHOR0	@ tmp136,
	movt	r1, #:upper16:.LANCHOR0	@ tmp136,
	add	r3, r1, r2, asl #3	@, tmp142, tmp136, tmp140,
	ldr	r0, [r3, #196]	@ <variable>.VdmStateMachine, <variable>.VdmStateMachine
	subs	r0, r0, #0	@, <variable>.VdmStateMachine,
	movne	r0, #1	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_IsVdmIdle, .-VDMDRV_IsVdmIdle
	.align	2
	.global	VDMDRV_GetCurrChanID
	.type	VDMDRV_GetCurrChanID, %function
VDMDRV_GetCurrChanID:
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
	rsb	r0, r0, r0, asl #3	@, tmp139, VdhId, VdhId,
	movw	r1, #:lower16:.LANCHOR0	@ tmp136,
	movt	r1, #:upper16:.LANCHOR0	@ tmp136,
	add	r3, r1, r0, asl #3	@, tmp143, tmp136, tmp139,
	ldr	r0, [r3, #204]	@, <variable>.ChanId
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_GetCurrChanID, .-VDMDRV_GetCurrChanID
	.align	2
	.global	VDMDRV_WaitVdmReadyIfNoIsr
	.type	VDMDRV_WaitVdmReadyIfNoIsr, %function
VDMDRV_WaitVdmReadyIfNoIsr:
	.fnstart
.LFB1554:
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
	movw	r4, #:lower16:g_vdm_hal_fun_ptr	@ tmp141,
	mov	r5, r0	@ VdhId, VdhId
	movt	r4, #:upper16:g_vdm_hal_fun_ptr	@ tmp141,
	mov	r3, #0	@ cnt_wait,
	b	.L108	@
.L106:
	ldr	r2, [r4, #80]	@ D.39373, g_vdm_hal_fun_ptr.pfun_VDMHAL_IsVdmReady
	mov	r0, r5	@, VdhId
	cmp	r2, #0	@ D.39373,
	beq	.L111	@,
	blx	r2	@ D.39373
	cmp	r0, #0	@,
	bne	.L114	@,
.L111:
	add	r3, r6, #1	@ cnt_wait, tmp142,
	cmp	r3, #400	@ cnt_wait,
	beq	.L116	@,
.L108:
	ldr	r2, [r4, #80]	@ D.39373, g_vdm_hal_fun_ptr.pfun_VDMHAL_IsVdmReady
	mov	r0, r5	@, VdhId
	add	r6, r3, #1	@ tmp142, cnt_wait,
	cmp	r2, #0	@ D.39373,
	beq	.L106	@,
	blx	r2	@ D.39373
	cmp	r0, #0	@,
	beq	.L106	@,
.L114:
	mov	r0, #0	@ D.39380,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L116:
	mov	r0, #1	@ D.39380,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDMDRV_WaitVdmReadyIfNoIsr, .-VDMDRV_WaitVdmReadyIfNoIsr
	.align	2
	.global	VDMDRV_H264NeedMoreStart
	.type	VDMDRV_H264NeedMoreStart, %function
VDMDRV_H264NeedMoreStart:
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
	cmp	r0, #0	@ VidStd,
	cmpne	r0, #15	@, VidStd,
	movne	r0, #0	@, tmp144
	moveq	r0, #1	@, tmp144
	ldmnefd	sp, {fp, sp, pc}	@
	ldr	r2, [r1, #20]	@ <variable>.pic_height_in_mb, <variable>.pic_height_in_mb
	ldr	ip, [r1, #28]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	ldr	r3, [r1, #920]	@ <variable>.mbtodec, <variable>.mbtodec
	mul	r0, ip, r2	@ tmp145, <variable>.pic_width_in_mb, <variable>.pic_height_in_mb
	cmp	r0, r3	@ tmp145, <variable>.mbtodec
	movle	r0, #0	@, H264NeedMoreStart
	movgt	r0, #1	@, H264NeedMoreStart
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_H264NeedMoreStart, .-VDMDRV_H264NeedMoreStart
	.align	2
	.global	VDMDRV_H264FinishedMultiStart
	.type	VDMDRV_H264FinishedMultiStart, %function
VDMDRV_H264FinishedMultiStart:
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
	cmp	r0, #0	@ VidStd,
	cmpne	r0, #15	@, VidStd,
	bne	.L122	@,
	ldr	ip, [r1, #20]	@ <variable>.pic_height_in_mb, <variable>.pic_height_in_mb
	ldr	r0, [r1, #28]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	ldr	r3, [r1, #920]	@ <variable>.mbtodec, <variable>.mbtodec
	mul	r2, r0, ip	@ tmp145, <variable>.pic_width_in_mb, <variable>.pic_height_in_mb
	cmp	r2, r3	@ tmp145, <variable>.mbtodec
	bgt	.L122	@,
	ldrsb	r2, [r1, #2]	@ <variable>.NewPicFlag, <variable>.NewPicFlag
	rsbs	r0, r2, #1	@ H264FinishedMultiStart, <variable>.NewPicFlag
	movcc	r0, #0	@ H264FinishedMultiStart
	ldmfd	sp, {fp, sp, pc}	@
.L122:
	mov	r0, #0	@ H264FinishedMultiStart,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_H264FinishedMultiStart, .-VDMDRV_H264FinishedMultiStart
	.align	2
	.global	VDMDRV_AvsFirstFldNeedRepair
	.type	VDMDRV_AvsFirstFldNeedRepair, %function
VDMDRV_AvsFirstFldNeedRepair:
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
	cmp	r0, #6	@ VidStd,
	beq	.L129	@,
.L126:
	mov	r0, #0	@ D.39438,
	ldmfd	sp, {fp, sp, pc}	@
.L129:
	ldrb	r3, [r1, #8]	@ zero_extendqisi2	@ <variable>.PicStruct, <variable>.PicStruct
	cmp	r3, #1	@ <variable>.PicStruct,
	bne	.L126	@,
	ldr	ip, .L130	@ tmp140,
	mov	r1, #1744	@ tmp142,
	mla	r2, r1, r2, ip	@ tmp143, tmp142, VdhId, tmp140
	ldr	r0, [r2, #840]	@ <variable>.ValidGroupNum, <variable>.ValidGroupNum
	cmp	r0, #0	@ <variable>.ValidGroupNum,
	movle	r0, #0	@, D.39438
	movgt	r0, #1	@, D.39438
	ldmfd	sp, {fp, sp, pc}	@
.L131:
	.align	2
.L130:
	.word	.LANCHOR0+256
	.fnend
	.size	VDMDRV_AvsFirstFldNeedRepair, .-VDMDRV_AvsFirstFldNeedRepair
	.align	2
	.global	VDMDRV_AvsSecondFldNeedRepair
	.type	VDMDRV_AvsSecondFldNeedRepair, %function
VDMDRV_AvsSecondFldNeedRepair:
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
	cmp	r0, #6	@ VidStd,
	beq	.L136	@,
.L133:
	mov	r0, #0	@ D.39456,
	ldmfd	sp, {fp, sp, pc}	@
.L136:
	ldrb	r3, [r1, #8]	@ zero_extendqisi2	@ <variable>.PicStruct, <variable>.PicStruct
	cmp	r3, #1	@ <variable>.PicStruct,
	bne	.L133	@,
	ldr	ip, .L137	@ tmp140,
	mov	r1, #1744	@ tmp143,
	mla	r2, r1, r2, ip	@ tmp144, tmp143, VdhId, tmp140
	ldr	r0, [r2, #1712]	@ <variable>.ValidGroupNum, <variable>.ValidGroupNum
	cmp	r0, #0	@ <variable>.ValidGroupNum,
	movle	r0, #0	@, D.39456
	movgt	r0, #1	@, D.39456
	ldmfd	sp, {fp, sp, pc}	@
.L138:
	.align	2
.L137:
	.word	.LANCHOR0+256
	.fnend
	.size	VDMDRV_AvsSecondFldNeedRepair, .-VDMDRV_AvsSecondFldNeedRepair
	.align	2
	.global	VDMDRV_UpdateMatchMode
	.type	VDMDRV_UpdateMatchMode, %function
VDMDRV_UpdateMatchMode:
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
	.pad #8
	sub	sp, sp, #8	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #0	@ VdhId,
	mov	ip, r1	@ ChanID, ChanID
	bne	.L141	@,
	cmp	r1, #15	@ ChanID,
	bls	.L142	@,
.L141:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L142:
	movw	lr, #:lower16:s_pstVfmwChan	@ tmp135,
	movt	lr, #:upper16:s_pstVfmwChan	@ tmp135,
	mov	r5, #1	@ tmp137,
	movw	r1, #:lower16:.LC0	@,
	ldr	r4, [lr, ip, asl #2]	@ tmp136, s_pstVfmwChan
	movt	r1, #:upper16:.LC0	@,
	movw	r2, #:lower16:.LANCHOR1	@,
	movw	r3, #1969	@,
	movt	r2, #:upper16:.LANCHOR1	@,
	mov	r0, #22	@,
	str	r5, [r4, #32]	@ tmp137, <variable>.MatchVdhIdPlus1
	ldr	lr, [lr, ip, asl #2]	@ tmp141, s_pstVfmwChan
	ldr	lr, [lr, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	str	ip, [sp, #4]	@ ChanID,
	str	lr, [sp, #0]	@ <variable>.MatchVdhIdPlus1,
	bl	dprint_vfmw	@
	b	.L141	@
	.fnend
	.size	VDMDRV_UpdateMatchMode, .-VDMDRV_UpdateMatchMode
	.align	2
	.global	VDMDRV_MarkReloadDsp
	.type	VDMDRV_MarkReloadDsp, %function
VDMDRV_MarkReloadDsp:
	.fnstart
.LFB1563:
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
	subs	ip, r0, #0	@ VdhId, VdhId
	mov	r3, r1	@ ChanID, ChanID
	bne	.L145	@,
	add	r2, r1, #1	@ tmp135, ChanID,
	cmp	r2, #16	@ tmp135,
	bhi	.L145	@,
	cmn	r1, #1	@ ChanID,
	movw	r0, #:lower16:.LANCHOR0	@ tmp136,
	movt	r0, #:upper16:.LANCHOR0	@ tmp136,
	mov	r1, #1	@ tmp137,
	str	r1, [r0, #244]	@ tmp137, <variable>.DspReloadFlag
	beq	.L145	@,
	movw	lr, #:lower16:s_pstVfmwChan	@ tmp138,
	movt	lr, #:upper16:s_pstVfmwChan	@ tmp138,
	mvn	r5, #0	@ tmp140,
	movw	r1, #:lower16:.LC1	@,
	ldr	r4, [lr, r3, asl #2]	@ tmp139, s_pstVfmwChan
	movt	r1, #:upper16:.LC1	@,
	mov	r0, #22	@,
	ldr	r2, .L146	@,
	movw	r3, #1957	@,
	str	r5, [r4, #32]	@ tmp140, <variable>.MatchVdhIdPlus1
	ldr	lr, [lr, #0]	@ s_pstVfmwChan, s_pstVfmwChan
	str	ip, [sp, #0]	@ VdhId,
	ldr	ip, [lr, #32]	@ <variable>.MatchVdhIdPlus1, <variable>.MatchVdhIdPlus1
	str	ip, [sp, #4]	@ <variable>.MatchVdhIdPlus1,
	bl	dprint_vfmw	@
.L145:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L147:
	.align	2
.L146:
	.word	.LANCHOR1+24
	.fnend
	.size	VDMDRV_MarkReloadDsp, .-VDMDRV_MarkReloadDsp
	.align	2
	.global	VDMDRV_ResetVDH
	.type	VDMDRV_ResetVDH, %function
VDMDRV_ResetVDH:
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
	movw	r1, #:lower16:.LANCHOR0	@ tmp135,
	movt	r1, #:upper16:.LANCHOR0	@ tmp135,
	ldr	r3, [r1, #204]	@ <variable>.ChanId, <variable>.ChanId
	cmp	r3, r0	@ <variable>.ChanId, ChanID
	ldmnefd	sp, {fp, sp, pc}	@
	movw	r0, #:lower16:g_vdm_hal_fun_ptr	@ tmp137,
	movt	r0, #:upper16:g_vdm_hal_fun_ptr	@ tmp137,
	ldr	r3, [r0, #44]	@ D.39511, g_vdm_hal_fun_ptr.pfun_VDMHAL_ResetVdm
	cmp	r3, #0	@ D.39511,
	beq	.L150	@,
	mov	r0, #0	@,
	blx	r3	@ D.39511
	ldmfd	sp, {fp, sp, pc}	@
.L150:
	mov	r0, r3	@, D.39511
	movw	r1, #:lower16:.LC2	@,
	movw	r2, #1929	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_ResetVDH, .-VDMDRV_ResetVDH
	.align	2
	.global	VDMDRV_IsVp6NvopCopy
	.type	VDMDRV_IsVp6NvopCopy, %function
VDMDRV_IsVp6NvopCopy:
	.fnstart
.LFB1561:
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
	subs	r4, r1, #0	@ pDecParam, pDecParam
	beq	.L157	@,
	cmp	r0, #10	@ VidStd,
	cmpne	r0, #12	@, VidStd,
	movne	r3, #0	@, tmp144
	moveq	r3, #1	@, tmp144
	bne	.L158	@,
	ldrb	r0, [r4, #1]	@ zero_extendqisi2	@ <variable>.IsNvopCopy, <variable>.IsNvopCopy
	cmp	r0, #1	@ <variable>.IsNvopCopy,
	movne	r0, #0	@, D.39491
	moveq	r0, #1	@, D.39491
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L158:
	cmp	r0, #11	@ VidStd,
	movne	r0, r3	@ D.39491, tmp144
	ldmnefd	sp, {r3, r4, fp, sp, pc}	@
	ldrb	r0, [r4, #1]	@ zero_extendqisi2	@ <variable>.IsNvopCopy, <variable>.IsNvopCopy
	cmp	r0, #1	@ <variable>.IsNvopCopy,
	movne	r0, #0	@, D.39491
	moveq	r0, #1	@, D.39491
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L157:
	mov	r0, r4	@, pDecParam
	movw	r1, #:lower16:.LC3	@,
	movt	r1, #:upper16:.LC3	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ D.39491, pDecParam
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	VDMDRV_IsVp6NvopCopy, .-VDMDRV_IsVp6NvopCopy
	.align	2
	.global	VDMDRV_IsVc1SkpicCopy
	.type	VDMDRV_IsVc1SkpicCopy, %function
VDMDRV_IsVc1SkpicCopy:
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
	subs	r4, r1, #0	@ pDecParam, pDecParam
	beq	.L164	@,
	cmp	r0, #1	@ VidStd,
	movne	r0, #0	@ D.39478,
	ldmnefd	sp, {r3, r4, fp, sp, pc}	@
	ldrb	r0, [r4, #1]	@ zero_extendqisi2	@ <variable>.IsSkpicCopy, <variable>.IsSkpicCopy
	cmp	r0, #1	@ <variable>.IsSkpicCopy,
	movne	r0, #0	@, D.39478
	moveq	r0, #1	@, D.39478
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L164:
	mov	r0, r4	@, pDecParam
	movw	r1, #:lower16:.LC4	@,
	movt	r1, #:upper16:.LC4	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ D.39478, pDecParam
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	VDMDRV_IsVc1SkpicCopy, .-VDMDRV_IsVc1SkpicCopy
	.align	2
	.global	VDMDRV_IsMpeg4NvopCopy
	.type	VDMDRV_IsMpeg4NvopCopy, %function
VDMDRV_IsMpeg4NvopCopy:
	.fnstart
.LFB1559:
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
	subs	r4, r1, #0	@ pDecParam, pDecParam
	beq	.L170	@,
	cmp	r0, #2	@ VidStd,
	movne	r0, #0	@ D.39465,
	ldmnefd	sp, {r3, r4, fp, sp, pc}	@
	ldrb	r0, [r4, #158]	@ zero_extendqisi2	@ <variable>.IsNvopCopy, <variable>.IsNvopCopy
	cmp	r0, #1	@ <variable>.IsNvopCopy,
	movne	r0, #0	@, D.39465
	moveq	r0, #1	@, D.39465
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L170:
	mov	r0, r4	@, pDecParam
	movw	r1, #:lower16:.LC5	@,
	movt	r1, #:upper16:.LC5	@,
	bl	dprint_vfmw	@
	mov	r0, r4	@ D.39465, pDecParam
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	VDMDRV_IsMpeg4NvopCopy, .-VDMDRV_IsMpeg4NvopCopy
	.align	2
	.global	VDMDRV_CheckAttachMode
	.type	VDMDRV_CheckAttachMode, %function
VDMDRV_CheckAttachMode:
	.fnstart
.LFB1543:
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
	cmp	r0, #15	@ ChanID,
	mov	r4, r0	@ ChanID, ChanID
	bgt	.L187	@,
	movw	r7, #:lower16:s_pstVfmwChan	@ tmp228,
	movt	r7, #:upper16:s_pstVfmwChan	@ tmp228,
	ldr	r5, [r7, r0, asl #2]	@ prephitmp.1190, s_pstVfmwChan
	cmp	r5, #0	@ prephitmp.1190,
	beq	.L187	@,
	ldr	r3, [r5, #484]	@ <variable>.stRecentImg.image_width, <variable>.stRecentImg.image_width
	cmp	r3, #1920	@ <variable>.stRecentImg.image_width,
	bcs	.L189	@,
.L173:
	movw	sl, #:lower16:.LANCHOR0	@ tmp229,
	mov	r9, r4, asl #2	@ tmp226, ChanID,
	movt	sl, #:upper16:.LANCHOR0	@ tmp229,
	movw	r8, #:lower16:g_FrameRate	@ tmp227,
	add	r1, r9, sl	@ tmp196, tmp226, tmp229
	movt	r8, #:upper16:g_FrameRate	@ tmp227,
	mov	r3, r5	@ prephitmp.1210, prephitmp.1190
	ldr	r2, [r1, #2000]	@ prephitmp.1188, DiffFrameCnt
.L175:
	cmp	r2, #10	@ prephitmp.1188,
	ldreq	r3, [r7, r4, asl #2]	@ prephitmp.1210, s_pstVfmwChan
	beq	.L182	@,
.L181:
	ldr	r2, [r3, #20]	@ <variable>.s32IsInit, <variable>.s32IsInit
	cmp	r2, #0	@ <variable>.s32IsInit,
	beq	.L183	@,
.L182:
	ldr	r0, [r8, r4, asl #2]	@ tmp201, g_FrameRate
	cmp	r0, #30	@ tmp201,
	movle	r0, #0	@ tmp216,
	strle	r0, [r3, #1936]	@ tmp216, <variable>.stSynExtraData.s32Is4k60fps
	ble	.L188	@,
	ldr	ip, [r5, #484]	@ <variable>.stRecentImg.image_width, <variable>.stRecentImg.image_width
	cmp	ip, #1920	@ <variable>.stRecentImg.image_width,
	bcc	.L188	@,
	ldr	r1, [r5, #488]	@ <variable>.stRecentImg.image_height, <variable>.stRecentImg.image_height
	movw	r2, #1079	@ tmp206,
	cmp	r1, r2	@ <variable>.stRecentImg.image_height, tmp206
	bhi	.L186	@,
.L188:
	ldr	r3, [r7, r4, asl #2]	@ prephitmp.1210, s_pstVfmwChan
.L183:
	mov	r1, #0	@ tmp218,
	str	r1, [r3, #20]	@ tmp218, <variable>.s32IsInit
	ldr	ip, [r8, r4, asl #2]	@ tmp225, g_FrameRate
	add	sl, r9, sl	@ tmp222, tmp226, tmp229
	str	ip, [sl, #2064]	@ tmp225, g_LastFPS
.L187:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L189:
	ldr	r2, [r5, #488]	@ <variable>.stRecentImg.image_height, <variable>.stRecentImg.image_height
	movw	r0, #1079	@ tmp145,
	cmp	r2, r0	@ <variable>.stRecentImg.image_height, tmp145
	bls	.L173	@,
	movw	sl, #:lower16:.LANCHOR0	@ tmp229,
	mov	r9, r4, asl #2	@ tmp226, ChanID,
	movt	sl, #:upper16:.LANCHOR0	@ tmp229,
	movw	r8, #:lower16:g_FrameRate	@ tmp227,
	add	r1, r9, sl	@ tmp155, tmp226, tmp229
	movt	r8, #:upper16:g_FrameRate	@ tmp227,
	mov	r0, #22	@,
	ldr	r2, .L190	@,
	ldr	lr, [r1, #2064]	@ D.38691, g_LastFPS
	movw	r3, #505	@,
	ldr	ip, [r8, r4, asl #2]	@ D.38689, g_FrameRate
	movw	r1, #:lower16:.LC6	@,
	movt	r1, #:upper16:.LC6	@,
	cmp	ip, lr	@ D.38689, D.38691
	str	lr, [sp, #4]	@ D.38691,
	rsbhi	r6, lr, ip	@ diff, D.38691, D.38689
	rsbls	r6, ip, lr	@ diff, D.38689, D.38691
	str	ip, [sp, #0]	@ D.38689,
	bl	dprint_vfmw	@
	cmp	r6, #2	@ diff,
	bgt	.L178	@,
	add	r3, r9, sl	@ tmp163, tmp226, tmp229
	ldr	r2, [r3, #2000]	@ tmp165, DiffFrameCnt
	add	r2, r2, #1	@ prephitmp.1188, tmp165,
	str	r2, [r3, #2000]	@ prephitmp.1188, DiffFrameCnt
.L179:
	cmn	r2, #1	@ prephitmp.1188,
	ldrne	r3, [r7, r4, asl #2]	@ prephitmp.1210, s_pstVfmwChan
	bne	.L175	@,
	add	ip, r9, sl	@ tmp189, tmp226, tmp229
	mov	r0, #11	@ tmp191,
	ldr	r3, [r7, r4, asl #2]	@ prephitmp.1210, s_pstVfmwChan
	str	r0, [ip, #2000]	@ tmp191, DiffFrameCnt
	b	.L181	@
.L186:
	mov	r0, #1	@ tmp208,
	str	r0, [r3, #1936]	@ tmp208, <variable>.stSynExtraData.s32Is4k60fps
	ldr	r3, [r7, r4, asl #2]	@ tmp213, s_pstVfmwChan
	mov	r0, #22	@,
	str	r4, [sp, #0]	@ ChanID,
	movw	r1, #:lower16:.LC8	@,
	ldr	r2, .L190	@,
	movt	r1, #:upper16:.LC8	@,
	ldr	lr, [r3, #1936]	@ <variable>.stSynExtraData.s32Is4k60fps, <variable>.stSynExtraData.s32Is4k60fps
	movw	r3, #530	@,
	str	lr, [sp, #4]	@ <variable>.stSynExtraData.s32Is4k60fps,
	bl	dprint_vfmw	@
	ldr	r3, [r7, r4, asl #2]	@ prephitmp.1210, s_pstVfmwChan
	b	.L183	@
.L178:
	add	r6, r9, sl	@ tmp174, tmp226, tmp229
	ldr	r2, .L190	@,
	mov	lr, #0	@ tmp176,
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC7	@,
	movw	r3, #513	@,
	movt	r1, #:upper16:.LC7	@,
	str	lr, [r6, #2000]	@ tmp176, DiffFrameCnt
	bl	dprint_vfmw	@
	ldr	r2, [r6, #2000]	@ prephitmp.1188, DiffFrameCnt
	b	.L179	@
.L191:
	.align	2
.L190:
	.word	.LANCHOR1+48
	.fnend
	.size	VDMDRV_CheckAttachMode, .-VDMDRV_CheckAttachMode
	.align	2
	.global	VDMDRV_StartDec
	.type	VDMDRV_StartDec, %function
VDMDRV_StartDec:
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
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp135,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp135,
	mov	r4, r0	@ VdhId, VdhId
	ldr	r3, [r3, #72]	@ D.38622, g_vdm_hal_fun_ptr.pfun_VDMHAL_StartHwDecode
	cmp	r3, #0	@ D.38622,
	beq	.L193	@,
	blx	r3	@ D.38622
.L194:
	rsb	r4, r4, r4, asl #3	@, tmp141, VdhId, VdhId,
	movw	r1, #:lower16:.LANCHOR0	@ tmp137,
	movt	r1, #:upper16:.LANCHOR0	@ tmp137,
	mov	r2, #1	@ tmp145,
	add	r0, r1, r4, asl #3	@, tmp143, tmp137, tmp141,
	str	r2, [r0, #196]	@ tmp145, <variable>.VdmStateMachine
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L193:
	mov	r0, r3	@, D.38622
	movw	r1, #:lower16:.LC2	@,
	movw	r2, #283	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	b	.L194	@
	.fnend
	.size	VDMDRV_StartDec, .-VDMDRV_StartDec
	.align	2
	.global	VDMDRV_StartRepair
	.type	VDMDRV_StartRepair, %function
VDMDRV_StartRepair:
	.fnstart
.LFB1536:
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
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp136,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp136,
	mov	r5, r0	@ StateAfterRepair, StateAfterRepair
	mov	r4, r1	@ VdhId, VdhId
	ldr	r3, [r3, #68]	@ D.38613, g_vdm_hal_fun_ptr.pfun_VDMHAL_StartHwRepair
	cmp	r3, #0	@ D.38613,
	beq	.L197	@,
	mov	r0, r1	@, VdhId
	rsb	r4, r4, r4, asl #3	@, tmp142, VdhId, VdhId,
	blx	r3	@ D.38613
	movw	r1, #:lower16:.LANCHOR0	@ tmp138,
	movt	r1, #:upper16:.LANCHOR0	@ tmp138,
	add	r0, r1, r4, asl #3	@, tmp144, tmp138, tmp142,
	str	r5, [r0, #196]	@ StateAfterRepair, <variable>.VdmStateMachine
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L197:
	mov	r0, r3	@, D.38613
	movw	r1, #:lower16:.LC2	@,
	movw	r2, #275	@,
	movt	r1, #:upper16:.LC2	@,
	rsb	r4, r4, r4, asl #3	@, tmp142, VdhId, VdhId,
	bl	dprint_vfmw	@
	movw	r1, #:lower16:.LANCHOR0	@ tmp138,
	movt	r1, #:upper16:.LANCHOR0	@ tmp138,
	add	r0, r1, r4, asl #3	@, tmp144, tmp138, tmp142,
	str	r5, [r0, #196]	@ StateAfterRepair, <variable>.VdmStateMachine
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	VDMDRV_StartRepair, .-VDMDRV_StartRepair
	.align	2
	.global	VDMDRV_ExitSleep
	.type	VDMDRV_ExitSleep, %function
VDMDRV_ExitSleep:
	.fnstart
.LFB1535:
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
	mov	r4, r0	@ VdhId, VdhId
	ldr	r3, [r3, #0]	@ D.38603, g_vdm_hal_fun_ptr.pfun_VDMDRV_OpenHardware
	cmp	r3, #0	@ D.38603,
	beq	.L201	@,
	blx	r3	@ D.38603
	movw	r1, #:lower16:.LANCHOR0	@ tmp137,
	movt	r1, #:upper16:.LANCHOR0	@ tmp137,
	mov	r0, #0	@ tmp142,
	add	r4, r1, r4, asl #2	@, tmp140, tmp137, VdhId,
	str	r0, [r4, #192]	@ tmp142, s_eVdmDrvSleepState
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L201:
	mov	r0, r3	@, D.38603
	movw	r1, #:lower16:.LC2	@,
	movw	r2, #267	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	movw	r1, #:lower16:.LANCHOR0	@ tmp137,
	movt	r1, #:upper16:.LANCHOR0	@ tmp137,
	mov	r0, #0	@ tmp142,
	add	r4, r1, r4, asl #2	@, tmp140, tmp137, VdhId,
	str	r0, [r4, #192]	@ tmp142, s_eVdmDrvSleepState
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	VDMDRV_ExitSleep, .-VDMDRV_ExitSleep
	.align	2
	.global	VDMDRV_Reset
	.type	VDMDRV_Reset, %function
VDMDRV_Reset:
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
	ldr	r3, .L206	@ tmp135,
	rsb	r0, r0, r0, asl #3	@, tmp138, VdhId, VdhId,
	mov	r1, #56	@,
	add	r0, r3, r0, asl #3	@,, tmp135, tmp138,
	bl	__memzero	@
	ldmfd	sp, {fp, sp, pc}	@
.L207:
	.align	2
.L206:
	.word	.LANCHOR0+196
	.fnend
	.size	VDMDRV_Reset, .-VDMDRV_Reset
	.align	2
	.global	VDMDRV_ForceSleep
	.type	VDMDRV_ForceSleep, %function
VDMDRV_ForceSleep:
	.fnstart
.LFB1534:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp134,
	movt	r4, #:upper16:.LANCHOR0	@ tmp134,
	add	r4, r4, r0, asl #2	@, tmp137, tmp134, VdhId,
	ldr	r3, [r4, #192]	@ tmp139, s_eVdmDrvSleepState
	cmp	r3, #2	@ tmp139,
	beq	.L209	@,
	bl	VDMDRV_Reset	@
	mov	r0, #2	@ tmp145,
	str	r0, [r4, #192]	@ tmp145, s_eVdmDrvSleepState
.L209:
	movw	r1, #:lower16:.LC9	@,
	mov	r0, #0	@,
	movt	r1, #:upper16:.LC9	@,
	bl	dprint_vfmw	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	VDMDRV_ForceSleep, .-VDMDRV_ForceSleep
	.align	2
	.global	VDMDRV_Init
	.type	VDMDRV_Init, %function
VDMDRV_Init:
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
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp135,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp135,
	mov	r4, r0	@ VdhId, VdhId
	ldr	r3, [r3, #0]	@ D.38478, g_vdm_hal_fun_ptr.pfun_VDMDRV_OpenHardware
	cmp	r3, #0	@ D.38478,
	beq	.L212	@,
	blx	r3	@ D.38478
.L213:
	rsb	ip, r4, r4, asl #3	@, tmp141, VdhId, VdhId,
	movw	r5, #:lower16:.LANCHOR0	@ tmp137,
	movt	r5, #:upper16:.LANCHOR0	@ tmp137,
	mov	r1, #56	@,
	add	lr, r5, #196	@ tmp138, tmp137,
	add	r5, r5, r4, asl #2	@, tmp147, tmp137, VdhId,
	add	r0, lr, ip, asl #3	@,, tmp138, tmp141,
	bl	__memzero	@
	movw	r2, #:lower16:g_VfmwGlobalStat	@ tmp156,
	movt	r2, #:upper16:g_VfmwGlobalStat	@ tmp156,
	mov	r1, #84	@ tmp159,
	mov	r0, #0	@ tmp149,
	str	r0, [r5, #2128]	@ tmp149, g_DspDrvState
	mla	r4, r1, r4, r2	@ tmp160, tmp159, VdhId, tmp156
	str	r0, [r5, #192]	@ tmp149, s_eVdmDrvSleepState
	str	r0, [r4, #12]	@ tmp149, <variable>.u32VaVdmLoad
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L212:
	mov	r0, r3	@, D.38478
	movw	r1, #:lower16:.LC2	@,
	mov	r2, #130	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	b	.L213	@
	.fnend
	.size	VDMDRV_Init, .-VDMDRV_Init
	.align	2
	.global	VDMDRV_ChnDecReady
	.type	VDMDRV_ChnDecReady, %function
VDMDRV_ChnDecReady:
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
	mov	r6, r1	@ ppDecParam, ppDecParam
	mov	r4, r0	@ ChanID, ChanID
	bl	VCTRL_IsChanActive	@
	cmp	r0, #0	@,
	bne	.L221	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp142,
	add	r2, r4, #32	@ tmp143, ChanID,
	movt	r3, #:upper16:.LANCHOR0	@ tmp142,
	ldr	r5, [r3, r2, asl #2]	@ tmp144, g_ChanCtx.ChanDecByVdhPlusOne
	cmp	r5, #0	@ tmp144,
	beq	.L218	@,
	mov	r2, r4	@, ChanID
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC11	@,
	movt	r1, #:upper16:.LC11	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.38728,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L218:
	str	r5, [r6, #0]	@ tmp144,* ppDecParam
	mov	r0, r4	@, ChanID
	bl	VCTRL_GetDecParam	@
	cmp	r0, #0	@ D.38733,
	str	r0, [r6, #0]	@ D.38733,* ppDecParam
	movne	r0, r5	@ D.38728, tmp144
	ldmnefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	mov	r2, r4	@, ChanID
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC12	@,
	movt	r1, #:upper16:.LC12	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.38728,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L221:
	mov	r3, r4	@, ChanID
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC10	@,
	ldr	r2, .L222	@,
	movt	r1, #:upper16:.LC10	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.38728,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L223:
	.align	2
.L222:
	.word	.LANCHOR1+72
	.fnend
	.size	VDMDRV_ChnDecReady, .-VDMDRV_ChnDecReady
	.align	2
	.global	VDMDRV_DoBeforeDec
	.type	VDMDRV_DoBeforeDec, %function
VDMDRV_DoBeforeDec:
	.fnstart
.LFB1545:
	@ args = 0, pretend = 0, frame = 24
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
	ldr	r3, [r2, #0]	@ tmp158,* ppDecParam
	mov	r7, r2	@ ppDecParam, ppDecParam
	mov	r4, r0	@ VdhId, VdhId
	cmp	r3, #0	@ tmp158,
	mov	r6, r1	@ ChanID, ChanID
	beq	.L236	@,
	mov	r0, r1	@, ChanID
	mov	r8, r4, asl #3	@ tmp361, VdhId,
	bl	VCTRL_GetVidStd	@
	rsb	r1, r4, r8	@ tmp163, VdhId, tmp361
	add	sl, r1, #1	@ tmp164, tmp163,
	movw	r5, #:lower16:.LANCHOR0	@ tmp362,
	movt	r5, #:upper16:.LANCHOR0	@ tmp362,
	add	sl, r5, sl, asl #3	@, tmp167, tmp362, tmp164,
	mov	r2, r0	@ prephitmp.1389,
	movw	r0, #:lower16:AcceleratorCharacter	@ tmp169,
	movt	r0, #:upper16:AcceleratorCharacter	@ tmp169,
	ldr	r3, [r0, #0]	@ AcceleratorCharacter.462, AcceleratorCharacter
	str	r2, [sl, #200]	@ prephitmp.1389, <variable>.VidStd
	cmp	r3, #0	@ AcceleratorCharacter.462,
	beq	.L227	@,
	ldr	ip, [r7, #0]	@ tmp170,* ppDecParam
	sub	r0, fp, #56	@,,
	str	r2, [fp, #-52]	@ prephitmp.1389, DecparamInfo.VidStd
	str	r6, [fp, #-56]	@ ChanID, DecparamInfo.ChanID
	str	ip, [fp, #-48]	@ tmp170, DecparamInfo.pDecParam
	blx	r3	@ AcceleratorCharacter.462
	cmp	r0, #1	@ D.38765,
	beq	.L226	@,
	ldr	r2, [sl, #200]	@ prephitmp.1389, <variable>.VidStd
.L227:
	mov	r0, r2	@, prephitmp.1389
	ldr	r1, [r7, #0]	@,* ppDecParam
	bl	VDMDRV_IsMpeg4NvopCopy	@
	cmp	r0, #1	@,
	beq	.L237	@,
	rsb	r9, r4, r8	@, VdhId, tmp361
	str	r9, [fp, #-64]	@, %sfp
	add	r3, r9, #1	@ tmp215,,
	ldr	r1, [r7, #0]	@,* ppDecParam
	movw	r9, #:lower16:.LANCHOR0	@ tmp211,
	movt	r9, #:upper16:.LANCHOR0	@ tmp211,
	add	sl, r5, r3, asl #3	@, tmp218, tmp362, tmp215,
	ldr	r0, [sl, #200]	@, <variable>.VidStd
	bl	VDMDRV_IsVc1SkpicCopy	@
	cmp	r0, #1	@,
	beq	.L238	@,
	ldr	r0, [sl, #200]	@, <variable>.VidStd
	ldr	r1, [r7, #0]	@,* ppDecParam
	bl	VDMDRV_IsVp6NvopCopy	@
	cmp	r0, #1	@,
	beq	.L239	@,
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp293,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp293,
	ldr	r3, [r3, #76]	@ D.38827, g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareDec
	cmp	r3, #0	@ D.38827,
	beq	.L233	@,
	ldr	r1, [r7, #0]	@,* ppDecParam
	mov	r2, r4	@, VdhId
	ldr	r0, [sl, #200]	@, <variable>.VidStd
	blx	r3	@ D.38827
	subs	r7, r0, #0	@ D.38829,
	beq	.L234	@,
.L233:
	rsb	r8, r4, r8	@ tmp310, VdhId, tmp361
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC15	@,
	movt	r1, #:upper16:.LC15	@,
	add	r8, r5, r8, asl #3	@, tmp312, tmp362, tmp310,
	mov	r7, r0	@ tmp314,
	bl	dprint_vfmw	@
	mov	ip, #100	@ tmp323,
	mov	r0, r6	@, ChanID
	str	ip, [r8, #200]	@ tmp323, <variable>.ErrRatio
	mov	r2, #15	@,
	mov	r1, ip	@, tmp323
	mov	r3, r7	@, tmp314
	str	r7, [r8, #196]	@ tmp314, <variable>.VdmStateMachine
	add	r6, r6, #32	@ tmp325, ChanID,
	str	r4, [sp, #0]	@ VdhId,
	bl	VCTRL_VdmPostProc	@
	mov	r0, r4	@, VdhId
	bl	VDMDRV_Reset	@
	mov	r0, r7	@ D.38759, tmp314
	str	r7, [r5, r6, asl #2]	@ tmp314, g_ChanCtx.ChanDecByVdhPlusOne
.L226:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L237:
	ldr	r0, [r7, #0]	@,* ppDecParam
	mov	r1, r4	@, VdhId
	bl	PostPro_CopyYuv	@
	subs	r7, r0, #0	@ D.38775,
	beq	.L240	@,
.L230:
	mov	r0, #0	@ D.38759,
	b	.L226	@
.L238:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC14	@,
	movt	r1, #:upper16:.LC14	@,
	bl	dprint_vfmw	@
	ldr	r0, [r7, #0]	@,* ppDecParam
	mov	r1, r4	@, VdhId
	bl	PostPro_CopyYuv_Vc1	@
	subs	r7, r0, #0	@ D.38800,
	bne	.L230	@,
	ldr	r2, [fp, #-64]	@, %sfp
	mov	r0, #2	@,
	mov	r1, r4	@, VdhId
	add	ip, r9, r2, asl #3	@, tmp230, tmp211,,
	str	r7, [ip, #200]	@ D.38800, <variable>.ErrRatio
	bl	VDMDRV_StartRepair	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, VdhId
	bl	VDMDRV_SetChanIsDec	@
	mov	r0, #7	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	beq	.L230	@,
	bl	OSAL_GetTimeInMs	@
	add	r9, r9, r6, asl #2	@, tmp236, tmp211, ChanID,
	movw	r2, #:lower16:g_TraceFramePeriod	@ tmp240,
	movt	r2, #:upper16:g_TraceFramePeriod	@ tmp240,
	ldr	ip, [r9, #2132]	@ tmp239, last_rec_pos_time
	mov	r3, r0	@ currtime.1405,
	ldr	r0, [r2, #0]	@ g_TraceFramePeriod, g_TraceFramePeriod
	rsb	r1, ip, r3	@ tmp238, tmp239, currtime.1405
	cmp	r1, r0	@ tmp238, g_TraceFramePeriod
	bls	.L230	@,
	add	lr, r4, #458752	@ tmp249, VdhId,
	ldr	r0, .L241	@,
	add	r2, lr, r6, asl #24	@,, tmp249, ChanID,
	mov	r1, #636	@,
	str	r3, [r9, #2132]	@ currtime.1405, last_rec_pos_time
	bl	DBG_AddTrace	@
	mov	r0, r7	@ D.38759, D.38800
	b	.L226	@
.L234:
	bl	OSAL_GetTimeInMs	@
	ldr	r2, [fp, #-64]	@, %sfp
	movw	ip, #:lower16:g_VfmwGlobalStat	@ tmp335,
	movt	ip, #:upper16:g_VfmwGlobalStat	@ tmp335,
	add	r1, r9, r2, asl #3	@, tmp333, tmp211,,
	mov	r3, r0	@ D.38833,
	mov	r0, #84	@ tmp338,
	mla	r2, r0, r4, ip	@ tmp339, tmp338, VdhId, tmp335
	str	r3, [r1, #216]	@ D.38833, <variable>.StartTime
	mov	r0, r4	@, VdhId
	str	r3, [r2, #4]	@ D.38833, <variable>.u32VaLastStartTime
	bl	VDMDRV_StartDec	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, VdhId
	bl	VDMDRV_SetChanIsDec	@
	mov	r0, r6	@, ChanID
	mov	r1, #5	@,
	mov	r2, r7	@, D.38829
	bl	DBG_CountTimeInfo	@
	mov	r0, #5	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	beq	.L230	@,
	bl	OSAL_GetTimeInMs	@
	add	r9, r9, r6, asl #2	@, tmp344, tmp211, ChanID,
	movw	r2, #:lower16:g_TraceFramePeriod	@ tmp348,
	movt	r2, #:upper16:g_TraceFramePeriod	@ tmp348,
	ldr	ip, [r2, #0]	@ g_TraceFramePeriod, g_TraceFramePeriod
	mov	r3, r0	@ currtime.1429,
	ldr	r0, [r9, #2132]	@ tmp347, last_rec_pos_time
	rsb	r1, r0, r3	@ tmp346, tmp347, currtime.1429
	cmp	r1, ip	@ tmp346, g_TraceFramePeriod
	bls	.L230	@,
	add	lr, r4, #327680	@ tmp357, VdhId,
	ldr	r0, .L241	@,
	add	r2, lr, r6, asl #24	@,, tmp357, ChanID,
	movw	r1, #691	@,
	str	r3, [r9, #2132]	@ currtime.1429, last_rec_pos_time
	bl	DBG_AddTrace	@
	mov	r0, r7	@ D.38759, D.38829
	b	.L226	@
.L240:
	rsb	r8, r4, r8	@ tmp187, VdhId, tmp361
	mov	r0, #2	@,
	mov	r1, r4	@, VdhId
	movw	sl, #:lower16:.LANCHOR0	@ tmp183,
	add	r5, r5, r8, asl #3	@, tmp189, tmp362, tmp187,
	movt	sl, #:upper16:.LANCHOR0	@ tmp183,
	str	r7, [r5, #200]	@ D.38775, <variable>.ErrRatio
	bl	VDMDRV_StartRepair	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, VdhId
	bl	VDMDRV_SetChanIsDec	@
	mov	r0, #7	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	beq	.L230	@,
	bl	OSAL_GetTimeInMs	@
	add	r3, sl, r6, asl #2	@, tmp195, tmp183, ChanID,
	ldr	r1, [r3, #2132]	@ tmp198, last_rec_pos_time
	mov	ip, r0	@ currtime,
	movw	r0, #:lower16:g_TraceFramePeriod	@ tmp199,
	movt	r0, #:upper16:g_TraceFramePeriod	@ tmp199,
	ldr	r2, [r0, #0]	@ g_TraceFramePeriod, g_TraceFramePeriod
	rsb	r0, r1, ip	@ tmp197, tmp198, currtime
	cmp	r0, r2	@ tmp197, g_TraceFramePeriod
	bls	.L230	@,
	add	lr, r4, #458752	@ tmp208, VdhId,
	ldr	r0, .L241	@,
	add	r2, lr, r6, asl #24	@,, tmp208, ChanID,
	movw	r1, #614	@,
	str	ip, [r3, #2132]	@ currtime, last_rec_pos_time
	bl	DBG_AddTrace	@
	mov	r0, r7	@ D.38759, D.38775
	b	.L226	@
.L236:
	mov	r2, r1	@, ChanID
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC13	@,
	movt	r1, #:upper16:.LC13	@,
	bl	dprint_vfmw	@
	mov	r0, #1	@ D.38759,
	b	.L226	@
.L239:
	mov	r0, #22	@,
	movw	r1, #:lower16:.LC14	@,
	movt	r1, #:upper16:.LC14	@,
	bl	dprint_vfmw	@
	ldr	r0, [r7, #0]	@,* ppDecParam
	mov	r1, r4	@, VdhId
	bl	PostPro_CopyYuv_Vp6	@
	subs	r7, r0, #0	@ D.38814,
	bne	.L230	@,
	ldr	r1, [fp, #-64]	@, %sfp
	mov	r0, #2	@,
	add	r3, r9, r1, asl #3	@, tmp271, tmp211,,
	mov	r1, r4	@, VdhId
	str	r7, [r3, #200]	@ D.38814, <variable>.ErrRatio
	bl	VDMDRV_StartRepair	@
	mov	r0, r6	@, ChanID
	mov	r1, r4	@, VdhId
	bl	VDMDRV_SetChanIsDec	@
	mov	r0, #7	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	beq	.L230	@,
	bl	OSAL_GetTimeInMs	@
	add	r9, r9, r6, asl #2	@, tmp277, tmp211, ChanID,
	movw	r2, #:lower16:g_TraceFramePeriod	@ tmp281,
	movt	r2, #:upper16:g_TraceFramePeriod	@ tmp281,
	ldr	r1, [r9, #2132]	@ tmp280, last_rec_pos_time
	ldr	ip, [r2, #0]	@ g_TraceFramePeriod, g_TraceFramePeriod
	mov	r3, r0	@ currtime.1418,
	rsb	r0, r1, r0	@ tmp279, tmp280, currtime.1418
	cmp	r0, ip	@ tmp279, g_TraceFramePeriod
	bls	.L230	@,
	add	lr, r4, #458752	@ tmp290, VdhId,
	ldr	r0, .L241	@,
	add	r2, lr, r6, asl #24	@,, tmp290, ChanID,
	movw	r1, #658	@,
	str	r3, [r9, #2132]	@ currtime.1418, last_rec_pos_time
	bl	DBG_AddTrace	@
	mov	r0, r7	@ D.38759, D.38814
	b	.L226	@
.L242:
	.align	2
.L241:
	.word	.LANCHOR1+92
	.fnend
	.size	VDMDRV_DoBeforeDec, .-VDMDRV_DoBeforeDec
	.align	2
	.global	VDMDRV_ActivateVDH
	.type	VDMDRV_ActivateVDH, %function
VDMDRV_ActivateVDH:
	.fnstart
.LFB1546:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp512,
	mov	r7, r0, asl #3	@ tmp514, VdhId,
	movt	r4, #:upper16:.LANCHOR0	@ tmp512,
	rsb	r8, r0, r7	@ tmp187, VdhId, tmp514
	mov	r5, r0	@ VdhId, VdhId
	movw	r0, #:lower16:g_ActivateLock	@,
	movt	r0, #:upper16:g_ActivateLock	@,
	bl	OSAL_SpinLockIRQ	@
	ldr	r3, [r4, #64]	@ temp.1465, g_ChanCtx.ChanIdTabByPrior
	add	r6, r4, r8, asl #3	@, tmp189, tmp512, tmp187,
	cmp	r3, #0	@ temp.1465,
	add	r6, r6, #212	@ ppDecParam, tmp189,
	blt	.L244	@,
	add	r8, r8, #1	@ tmp196, tmp187,
	mov	r0, r3	@, temp.1465
	mov	r1, r6	@, ppDecParam
	add	r8, r4, r8, asl #3	@, tmp199, tmp512, tmp196,
	str	r3, [r8, #196]	@ temp.1465, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L262	@,
.L245:
	ldr	r2, [r4, #68]	@ temp.1469, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp211,
	movt	r3, #:upper16:.LANCHOR0	@ tmp211,
	cmp	r2, #0	@ temp.1469,
	blt	.L244	@,
	rsb	r1, r5, r7	@ tmp215, VdhId, tmp514
	mov	r0, r2	@, temp.1469
	add	ip, r1, #1	@ tmp216, tmp215,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, ip, asl #3	@, tmp219, tmp211, tmp216,
	str	r2, [r8, #196]	@ temp.1469, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L263	@,
.L246:
	ldr	r2, [r4, #72]	@ temp.1473, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp231,
	movt	r3, #:upper16:.LANCHOR0	@ tmp231,
	cmp	r2, #0	@ temp.1473,
	blt	.L244	@,
	rsb	r8, r5, r7	@ tmp235, VdhId, tmp514
	mov	r0, r2	@, temp.1473
	add	lr, r8, #1	@ tmp236, tmp235,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, lr, asl #3	@, tmp239, tmp231, tmp236,
	str	r2, [r8, #196]	@ temp.1473, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L264	@,
.L247:
	ldr	r2, [r4, #76]	@ temp.1477, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp251,
	movt	r3, #:upper16:.LANCHOR0	@ tmp251,
	cmp	r2, #0	@ temp.1477,
	blt	.L244	@,
	rsb	r1, r5, r7	@ tmp255, VdhId, tmp514
	mov	r0, r2	@, temp.1477
	add	ip, r1, #1	@ tmp256, tmp255,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, ip, asl #3	@, tmp259, tmp251, tmp256,
	str	r2, [r8, #196]	@ temp.1477, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L265	@,
.L248:
	ldr	r2, [r4, #80]	@ temp.1481, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp271,
	movt	r3, #:upper16:.LANCHOR0	@ tmp271,
	cmp	r2, #0	@ temp.1481,
	blt	.L244	@,
	rsb	r8, r5, r7	@ tmp275, VdhId, tmp514
	mov	r0, r2	@, temp.1481
	add	lr, r8, #1	@ tmp276, tmp275,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, lr, asl #3	@, tmp279, tmp271, tmp276,
	str	r2, [r8, #196]	@ temp.1481, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L266	@,
.L249:
	ldr	r2, [r4, #84]	@ temp.1485, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp291,
	movt	r3, #:upper16:.LANCHOR0	@ tmp291,
	cmp	r2, #0	@ temp.1485,
	blt	.L244	@,
	rsb	r1, r5, r7	@ tmp295, VdhId, tmp514
	mov	r0, r2	@, temp.1485
	add	ip, r1, #1	@ tmp296, tmp295,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, ip, asl #3	@, tmp299, tmp291, tmp296,
	str	r2, [r8, #196]	@ temp.1485, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L267	@,
.L250:
	ldr	r2, [r4, #88]	@ temp.1489, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp311,
	movt	r3, #:upper16:.LANCHOR0	@ tmp311,
	cmp	r2, #0	@ temp.1489,
	blt	.L244	@,
	rsb	r8, r5, r7	@ tmp315, VdhId, tmp514
	mov	r0, r2	@, temp.1489
	add	lr, r8, #1	@ tmp316, tmp315,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, lr, asl #3	@, tmp319, tmp311, tmp316,
	str	r2, [r8, #196]	@ temp.1489, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L268	@,
.L251:
	ldr	r2, [r4, #92]	@ temp.1493, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp331,
	movt	r3, #:upper16:.LANCHOR0	@ tmp331,
	cmp	r2, #0	@ temp.1493,
	blt	.L244	@,
	rsb	r1, r5, r7	@ tmp335, VdhId, tmp514
	mov	r0, r2	@, temp.1493
	add	ip, r1, #1	@ tmp336, tmp335,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, ip, asl #3	@, tmp339, tmp331, tmp336,
	str	r2, [r8, #196]	@ temp.1493, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L269	@,
.L252:
	ldr	r2, [r4, #96]	@ temp.1497, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp351,
	movt	r3, #:upper16:.LANCHOR0	@ tmp351,
	cmp	r2, #0	@ temp.1497,
	blt	.L244	@,
	rsb	r8, r5, r7	@ tmp355, VdhId, tmp514
	mov	r0, r2	@, temp.1497
	add	lr, r8, #1	@ tmp356, tmp355,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, lr, asl #3	@, tmp359, tmp351, tmp356,
	str	r2, [r8, #196]	@ temp.1497, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L270	@,
.L253:
	ldr	r2, [r4, #100]	@ temp.1501, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp371,
	movt	r3, #:upper16:.LANCHOR0	@ tmp371,
	cmp	r2, #0	@ temp.1501,
	blt	.L244	@,
	rsb	r1, r5, r7	@ tmp375, VdhId, tmp514
	mov	r0, r2	@, temp.1501
	add	ip, r1, #1	@ tmp376, tmp375,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, ip, asl #3	@, tmp379, tmp371, tmp376,
	str	r2, [r8, #196]	@ temp.1501, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L271	@,
.L254:
	ldr	r2, [r4, #104]	@ temp.1505, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp391,
	movt	r3, #:upper16:.LANCHOR0	@ tmp391,
	cmp	r2, #0	@ temp.1505,
	blt	.L244	@,
	rsb	r8, r5, r7	@ tmp395, VdhId, tmp514
	mov	r0, r2	@, temp.1505
	add	lr, r8, #1	@ tmp396, tmp395,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, lr, asl #3	@, tmp399, tmp391, tmp396,
	str	r2, [r8, #196]	@ temp.1505, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L272	@,
.L255:
	ldr	r2, [r4, #108]	@ temp.1509, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp411,
	movt	r3, #:upper16:.LANCHOR0	@ tmp411,
	cmp	r2, #0	@ temp.1509,
	blt	.L244	@,
	rsb	r1, r5, r7	@ tmp415, VdhId, tmp514
	mov	r0, r2	@, temp.1509
	add	ip, r1, #1	@ tmp416, tmp415,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, ip, asl #3	@, tmp419, tmp411, tmp416,
	str	r2, [r8, #196]	@ temp.1509, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L273	@,
.L256:
	ldr	r2, [r4, #112]	@ temp.1513, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp431,
	movt	r3, #:upper16:.LANCHOR0	@ tmp431,
	cmp	r2, #0	@ temp.1513,
	blt	.L244	@,
	rsb	r8, r5, r7	@ tmp435, VdhId, tmp514
	mov	r0, r2	@, temp.1513
	add	lr, r8, #1	@ tmp436, tmp435,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, lr, asl #3	@, tmp439, tmp431, tmp436,
	str	r2, [r8, #196]	@ temp.1513, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L274	@,
.L257:
	ldr	r3, [r4, #116]	@ temp.1517, g_ChanCtx.ChanIdTabByPrior
	movw	r2, #:lower16:.LANCHOR0	@ tmp451,
	movt	r2, #:upper16:.LANCHOR0	@ tmp451,
	cmp	r3, #0	@ temp.1517,
	blt	.L244	@,
	rsb	r1, r5, r7	@ tmp455, VdhId, tmp514
	mov	r0, r3	@, temp.1517
	add	ip, r1, #1	@ tmp456, tmp455,
	mov	r1, r6	@, ppDecParam
	add	r8, r2, ip, asl #3	@, tmp459, tmp451, tmp456,
	str	r3, [r8, #196]	@ temp.1517, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L275	@,
.L258:
	ldr	r2, [r4, #120]	@ temp.1521, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp471,
	movt	r3, #:upper16:.LANCHOR0	@ tmp471,
	cmp	r2, #0	@ temp.1521,
	blt	.L244	@,
	rsb	r8, r5, r7	@ tmp475, VdhId, tmp514
	mov	r0, r2	@, temp.1521
	add	lr, r8, #1	@ tmp476, tmp475,
	mov	r1, r6	@, ppDecParam
	add	r8, r3, lr, asl #3	@, tmp479, tmp471, tmp476,
	str	r2, [r8, #196]	@ temp.1521, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L276	@,
.L259:
	ldr	r2, [r4, #124]	@ D.38858, g_ChanCtx.ChanIdTabByPrior
	movw	r3, #:lower16:.LANCHOR0	@ tmp491,
	movt	r3, #:upper16:.LANCHOR0	@ tmp491,
	cmp	r2, #0	@ D.38858,
	blt	.L244	@,
	rsb	ip, r5, r7	@ tmp495, VdhId, tmp514
	mov	r0, r2	@, D.38858
	add	r4, ip, #1	@ tmp496, tmp495,
	mov	r1, r6	@, ppDecParam
	add	r4, r3, r4, asl #3	@, tmp499, tmp491, tmp496,
	str	r2, [r4, #196]	@ D.38858, <variable>.ChanId
	bl	VDMDRV_ChnDecReady	@
	cmp	r0, #0	@,
	beq	.L277	@,
.L244:
	movw	r0, #:lower16:g_ActivateLock	@,
	movt	r0, #:upper16:g_ActivateLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L262:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L245	@,
	movw	r0, #:lower16:g_ActivateLock	@,
	movt	r0, #:upper16:g_ActivateLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L263:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L246	@,
	b	.L244	@
.L264:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L247	@,
	b	.L244	@
.L265:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L248	@,
	b	.L244	@
.L266:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L249	@,
	b	.L244	@
.L271:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L254	@,
	b	.L244	@
.L272:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L255	@,
	b	.L244	@
.L267:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L250	@,
	b	.L244	@
.L268:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L251	@,
	b	.L244	@
.L269:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L252	@,
	b	.L244	@
.L270:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L253	@,
	b	.L244	@
.L273:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L256	@,
	b	.L244	@
.L277:
	mov	r0, r5	@, VdhId
	ldr	r1, [r4, #196]	@, <variable>.ChanId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	b	.L244	@
.L274:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L257	@,
	b	.L244	@
.L275:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L258	@,
	b	.L244	@
.L276:
	ldr	r1, [r8, #196]	@, <variable>.ChanId
	mov	r0, r5	@, VdhId
	mov	r2, r6	@, ppDecParam
	bl	VDMDRV_DoBeforeDec	@
	cmp	r0, #0	@,
	bne	.L259	@,
	b	.L244	@
	.fnend
	.size	VDMDRV_ActivateVDH, .-VDMDRV_ActivateVDH
	.align	2
	.global	VDMDRV_AfterDec
	.type	VDMDRV_AfterDec, %function
VDMDRV_AfterDec:
	.fnstart
.LFB1547:
	@ args = 0, pretend = 0, frame = 176
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #188
	sub	sp, sp, #188	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r8, r0, asl #3	@ tmp1587, VdhId,
	rsb	ip, r0, r8	@ tmp195, VdhId, tmp1587
	movw	r4, #:lower16:.LANCHOR0	@ tmp1585,
	movt	r4, #:upper16:.LANCHOR0	@ tmp1585,
	movw	r7, #:lower16:s_pstVfmwChan	@ tmp1586,
	add	sl, r4, ip, asl #3	@, tmp199, tmp1585, tmp195,
	movt	r7, #:upper16:s_pstVfmwChan	@ tmp1586,
	mov	r5, r0	@ VdhId, VdhId
	mov	r6, #180	@ tmp206,
	ldr	r9, [sl, #204]	@ <variable>.ChanId, <variable>.ChanId
	sub	r0, fp, #196	@,,
	ldr	sl, [r7, r9, asl #2]	@ D.38899, s_pstVfmwChan
	cmp	sl, #0	@ D.38899,
	streq	sl, [fp, #-208]	@ D.38899, %sfp
	ldrne	r1, [sl, #1744]	@, <variable>.stSynExtraData.s32ModuleLowlyEnable
	strne	r1, [fp, #-208]	@, %sfp
	mov	r1, #136	@,
	bl	__memzero	@
	mla	r3, r6, r5, r4	@ tmp207, tmp206, VdhId, tmp1585
	rsb	r2, r5, r8	@, VdhId, tmp1587
	movw	ip, #:lower16:.LANCHOR0	@ tmp226,
	movt	ip, #:upper16:.LANCHOR0	@ tmp226,
	add	r6, r4, r2, asl #3	@, tmp232, tmp1585,,
	ldr	r1, [r3, #2196]	@ <variable>.BasicCfg1, <variable>.BasicCfg1
	and	r0, r1, #15	@ tmp209, <variable>.BasicCfg1,
	movw	r1, #:lower16:.LC16	@,
	cmp	r0, #5	@ tmp209,
	movt	r1, #:upper16:.LC16	@,
	mov	r0, #2	@,
	ldreq	r3, [r3, #2208]	@ <variable>.SwitchRounding, <variable>.SwitchRounding
	ldrne	r3, [r3, #2204]	@ <variable>.Mb0QpInCurrPic, <variable>.Mb0QpInCurrPic
	andeq	r3, r3, #1	@, <variable>.SwitchRounding,
	str	r2, [fp, #-200]	@, %sfp
	andne	r3, r3, #31	@, <variable>.Mb0QpInCurrPic,
	str	r3, [fp, #-204]	@, %sfp
	ldr	lr, [r6, #200]	@ <variable>.ErrRatio, <variable>.ErrRatio
	ldr	r2, [r6, #196]	@ <variable>.VdmStateMachine, <variable>.VdmStateMachine
	ldr	r3, [r6, #232]	@ <variable>.VdmTimeOut, <variable>.VdmTimeOut
	str	ip, [fp, #-212]	@,
	str	lr, [sp, #0]	@ <variable>.ErrRatio,
	bl	dprint_vfmw	@
	ldr	r9, [r6, #196]	@ temp.1559, <variable>.VdmStateMachine
	ldr	ip, [fp, #-212]	@,
	cmp	r9, #1	@ temp.1559,
	beq	.L321	@,
	cmp	r9, #2	@ temp.1559,
	beq	.L322	@,
	cmp	r9, #3	@ temp.1559,
	beq	.L323	@,
	movw	r1, #:lower16:.LC20	@,
	mov	r2, r9	@, temp.1559
	movt	r1, #:upper16:.LC20	@,
	mov	r0, #0	@,
	bl	dprint_vfmw	@
.L315:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L323:
	ldr	r0, [r6, #232]	@ <variable>.VdmTimeOut, <variable>.VdmTimeOut
	rsb	r8, r5, r8	@ tmp1529, VdhId, tmp1587
	sub	r3, fp, #196	@,,
	mov	r7, #0	@ tmp1533,
	cmp	r0, #1	@ <variable>.VdmTimeOut,
	moveq	r0, #0	@ tmp1524,
	streq	r0, [r6, #232]	@ tmp1524, <variable>.VdmTimeOut
	add	r6, r8, #1	@ tmp1555, tmp1529,
	add	r8, r4, r8, asl #3	@, tmp1531, tmp1585, tmp1529,
	str	r5, [sp, #0]	@ VdhId,
	ldr	lr, [r8, #200]	@ <variable>.ErrRatio, <variable>.ErrRatio
	add	r6, r4, r6, asl #3	@, tmp1558, tmp1585, tmp1555,
	ldr	r2, [fp, #-204]	@, %sfp
	cmp	lr, #100	@ <variable>.ErrRatio,
	movge	lr, #100	@ iftmp.1669,
	ldr	r0, [r6, #196]	@ <variable>.ChanId, <variable>.ChanId
	bic	r1, lr, lr, asr #31	@ iftmp.488, iftmp.1669
	str	r7, [r8, #196]	@ tmp1533, <variable>.VdmStateMachine
	str	r1, [r8, #200]	@ iftmp.488, <variable>.ErrRatio
	bl	VCTRL_VdmPostProc	@
	ldr	ip, [r6, #196]	@ <variable>.ChanId, <variable>.ChanId
	mov	r0, r5	@, VdhId
	add	r2, ip, #32	@ tmp1572, <variable>.ChanId,
	str	r7, [r4, r2, asl #2]	@ tmp1533, g_ChanCtx.ChanDecByVdhPlusOne
	bl	VDMDRV_Reset	@
	mov	r0, r5	@, VdhId
	bl	VDMDRV_ActivateVDH	@
	b	.L315	@
.L321:
	ldr	lr, [r6, #232]	@ <variable>.VdmTimeOut, <variable>.VdmTimeOut
	cmp	lr, #1	@ <variable>.VdmTimeOut,
	beq	.L324	@,
	sub	lr, fp, #60	@ tmp308,,
	mov	r1, #12	@,
	str	lr, [fp, #-216]	@,
	mov	r0, lr	@, tmp308
	str	ip, [fp, #-212]	@,
	bl	__memzero	@
	ldr	r0, [fp, #-200]	@, %sfp
	ldr	ip, [fp, #-216]	@,
	ldr	r3, [fp, #-212]	@,
	add	r2, r0, #1	@ tmp313,,
	ldr	r1, [r6, #212]	@ <variable>.pDecParam, <variable>.pDecParam
	mov	r0, ip	@, tmp308
	add	ip, r3, r2, asl #3	@, tmp316, tmp226, tmp313,
	str	r5, [fp, #-52]	@ VdhId, Param.VdhId
	ldr	r2, [ip, #200]	@ <variable>.VidStd, <variable>.VidStd
	str	r1, [fp, #-56]	@ <variable>.pDecParam, Param.pDecParam
	str	ip, [fp, #-212]	@,
	str	r2, [fp, #-60]	@ <variable>.VidStd, Param.VidStd
	bl	PostPro_GetErrRatio	@
	movw	r1, #:lower16:.LC18	@,
	movt	r1, #:upper16:.LC18	@,
	mov	ip, r0	@ D.38934,
	mov	r0, r9	@, temp.1559
	mov	r2, ip	@, D.38934
	str	ip, [r6, #200]	@ D.38934, <variable>.ErrRatio
	bl	dprint_vfmw	@
	ldr	ip, [fp, #-212]	@,
	ldr	r3, [ip, #200]	@ D.38936, <variable>.VidStd
	sub	r1, r3, #8	@ tmp347, D.38936,
	cmp	r3, #5	@ D.38936,
	cmpne	r1, #1	@, tmp347,
	movls	r3, #0	@ tmp363,
	strls	r3, [r6, #200]	@ tmp363, <variable>.ErrRatio
	bls	.L285	@,
	ldr	r3, [r6, #200]	@ <variable>.ErrRatio, <variable>.ErrRatio
	cmp	r3, #0	@ <variable>.ErrRatio,
	beq	.L285	@,
	ldr	r1, [sl, #1656]	@ <variable>.stSynExtraData.stChanState.dec_error_frame_num, <variable>.stSynExtraData.stChanState.dec_error_frame_num
	movw	r3, #:lower16:g_event_report	@ tmp375,
	movt	r3, #:upper16:g_event_report	@ tmp375,
	add	r9, r1, #1	@ tmp374, <variable>.stSynExtraData.stChanState.dec_error_frame_num,
	str	r9, [sl, #1656]	@ tmp374, <variable>.stSynExtraData.stChanState.dec_error_frame_num
	ldr	sl, [r3, #0]	@ g_event_report.475, g_event_report
	cmp	sl, #0	@ g_event_report.475,
	beq	.L285	@,
	ldr	lr, [r6, #200]	@ <variable>.ErrRatio, <variable>.ErrRatio
	sub	r2, fp, #44	@ tmp395,,
	ldr	r0, [ip, #196]	@, <variable>.ChanId
	mov	r1, #114	@,
	mov	r3, #4	@,
	str	lr, [r2, #-4]!	@ <variable>.ErrRatio, para
	blx	sl	@ g_event_report.475
.L285:
	ldr	r0, [fp, #-208]	@, %sfp
	rsb	ip, r5, r8	@ tmp408, VdhId, tmp1587
	add	r2, ip, #1	@ tmp409, tmp408,
	cmp	r0, #1	@,
	add	r6, r4, ip, asl #3	@, tmp421, tmp1585, tmp408,
	rsbeq	r3, r5, r8	@ tmp400, VdhId, tmp1587
	add	sl, r4, r2, asl #3	@, tmp412, tmp1585, tmp409,
	moveq	r0, #0	@ tmp404,
	ldr	r1, [r6, #212]	@, <variable>.pDecParam
	addeq	r3, r4, r3, asl #3	@, tmp402, tmp1585, tmp400,
	streq	r0, [r3, #200]	@ tmp404, <variable>.ErrRatio
	ldr	r0, [sl, #200]	@, <variable>.VidStd
	bl	PostPro_GetRepairStratage	@
	str	r0, [fp, #-200]	@, %sfp
	ldr	r3, [sl, #200]	@ temp.1568, <variable>.VidStd
	ldr	r2, [r6, #212]	@ temp.1569, <variable>.pDecParam
	cmp	r3, #0	@ temp.1568,
	cmpne	r3, #15	@, temp.1568,
	movne	r3, #0	@, tmp447
	moveq	r3, #1	@, tmp447
	bne	.L289	@,
	ldr	r3, [r2, #20]	@ <variable>.pic_height_in_mb, <variable>.pic_height_in_mb
	ldr	r1, [r2, #28]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	ldr	lr, [r2, #920]	@ <variable>.mbtodec, <variable>.mbtodec
	mul	r9, r1, r3	@ tmp448, <variable>.pic_width_in_mb, <variable>.pic_height_in_mb
	cmp	r9, lr	@ tmp448, <variable>.mbtodec
	movle	r3, #0	@, H264NeedMoreStart
	movgt	r3, #1	@, H264NeedMoreStart
.L289:
	rsb	r2, r5, r8	@ tmp457, VdhId, tmp1587
	add	ip, r4, r2, asl #3	@, tmp468, tmp1585, tmp457,
	ldr	sl, [ip, #208]	@ temp.1570, <variable>.VidStd
	str	r3, [ip, #224]	@ H264NeedMoreStart, <variable>.H264NeedMoreStart
	cmp	sl, #0	@ temp.1570,
	cmpne	sl, #15	@, temp.1570,
	ldr	r3, [ip, #212]	@ temp.1571, <variable>.pDecParam
	beq	.L325	@,
.L290:
	mov	ip, #0	@ H264FinishedMultiStart,
.L291:
	rsb	r9, r5, r8	@ tmp495, VdhId, tmp1587
	mov	r3, ip	@, H264FinishedMultiStart
	mov	r0, #2	@,
	movw	r1, #:lower16:.LC19	@,
	add	r6, r4, r9, asl #3	@, tmp497, tmp1585, tmp495,
	movt	r1, #:upper16:.LC19	@,
	movw	sl, #:lower16:.LANCHOR0	@ tmp491,
	movt	sl, #:upper16:.LANCHOR0	@ tmp491,
	ldr	r2, [r6, #224]	@, <variable>.H264NeedMoreStart
	str	ip, [r6, #228]	@ H264FinishedMultiStart, <variable>.H264FinishedMultiStart
	bl	dprint_vfmw	@
	ldr	r3, [r6, #224]	@ <variable>.H264NeedMoreStart, <variable>.H264NeedMoreStart
	cmp	r3, #1	@ <variable>.H264NeedMoreStart,
	beq	.L326	@,
	ldr	lr, [r6, #228]	@ <variable>.H264FinishedMultiStart, <variable>.H264FinishedMultiStart
	cmp	lr, #1	@ <variable>.H264FinishedMultiStart,
	beq	.L327	@,
	ldr	r3, [r6, #200]	@ temp.1577, <variable>.ErrRatio
	ldr	r0, [fp, #-200]	@, %sfp
	cmp	r3, #0	@ temp.1577,
	cmpne	r0, #1	@,,
	movne	r2, #0	@, tmp625
	moveq	r2, #1	@, tmp625
	bne	.L295	@,
	ldr	ip, [fp, #-208]	@, %sfp
	cmp	ip, #1	@,
	beq	.L328	@,
	add	r9, r9, #1	@ tmp796, tmp495,
	cmp	r3, #100	@ temp.1577,
	movge	r3, #100	@ iftmp.478,
	bic	r0, r3, r3, asr #31	@ iftmp.1665, iftmp.478
	sub	r3, fp, #196	@,,
	add	r9, sl, r9, asl #3	@, tmp799, tmp491, tmp796,
	ldr	r2, [fp, #-204]	@, %sfp
	mov	r1, r0	@, iftmp.1665
	str	r0, [r6, #200]	@ iftmp.1665, <variable>.ErrRatio
	mov	r4, #0	@ tmp774,
	ldr	r0, [r9, #196]	@ <variable>.ChanId, <variable>.ChanId
	str	r5, [sp, #0]	@ VdhId,
	str	r4, [r6, #196]	@ tmp774, <variable>.VdmStateMachine
.L317:
	bl	VCTRL_VdmPostProc	@
	ldr	r2, [r9, #196]	@ <variable>.ChanId, <variable>.ChanId
	mov	r0, r5	@, VdhId
	add	r3, r2, #32	@ tmp813, <variable>.ChanId,
	str	r4, [sl, r3, asl #2]	@ tmp774, g_ChanCtx.ChanDecByVdhPlusOne
	bl	VDMDRV_Reset	@
	mov	r0, r5	@, VdhId
	bl	VDMDRV_ActivateVDH	@
	b	.L315	@
.L322:
	rsb	r7, r5, r8	@ tmp1166, VdhId, tmp1587
	ldr	r3, [r6, #232]	@ <variable>.VdmTimeOut, <variable>.VdmTimeOut
	add	sl, r7, #1	@ tmp1167, tmp1166,
	cmp	r3, #1	@ <variable>.VdmTimeOut,
	add	r7, r4, r7, asl #3	@, tmp1178, tmp1585, tmp1166,
	add	sl, r4, sl, asl #3	@, tmp1170, tmp1585, tmp1167,
	moveq	r3, #0	@ tmp1162,
	streq	r3, [r6, #232]	@ tmp1162, <variable>.VdmTimeOut
	ldr	r0, [sl, #200]	@ temp.1634, <variable>.VidStd
	movw	r6, #:lower16:.LANCHOR0	@ tmp1163,
	ldr	r1, [r7, #212]	@ temp.1635, <variable>.pDecParam
	movt	r6, #:upper16:.LANCHOR0	@ tmp1163,
	cmp	r0, #6	@ temp.1634,
	beq	.L329	@,
.L306:
	bl	VDMDRV_IsMpeg4NvopCopy	@
	cmp	r0, #1	@,
	beq	.L330	@,
	rsb	r2, r5, r8	@ tmp1338, VdhId, tmp1587
	movw	r6, #:lower16:.LANCHOR0	@ tmp1335,
	add	r3, r2, #1	@ tmp1339, tmp1338,
	movt	r6, #:upper16:.LANCHOR0	@ tmp1335,
	add	r8, r4, r2, asl #3	@, tmp1351, tmp1585, tmp1338,
	add	r4, r4, r3, asl #3	@, tmp1342, tmp1585, tmp1339,
	ldr	r1, [r8, #212]	@, <variable>.pDecParam
	ldr	r0, [r4, #200]	@, <variable>.VidStd
	bl	VDMDRV_IsVc1SkpicCopy	@
	cmp	r0, #1	@,
	beq	.L320	@,
	ldr	r0, [r4, #200]	@, <variable>.VidStd
	ldr	r1, [r8, #212]	@, <variable>.pDecParam
	bl	VDMDRV_IsVp6NvopCopy	@
	cmp	r0, #1	@,
	beq	.L320	@,
	ldr	ip, [r8, #200]	@ <variable>.ErrRatio, <variable>.ErrRatio
	sub	r3, fp, #196	@,,
	ldr	r2, [fp, #-204]	@, %sfp
	mov	r7, #0	@ tmp1465,
	cmp	ip, #100	@ <variable>.ErrRatio,
	movge	ip, #100	@ iftmp.1663,
	ldr	r0, [r4, #196]	@ <variable>.ChanId, <variable>.ChanId
	bic	r1, ip, ip, asr #31	@ iftmp.487, iftmp.1663
	str	r5, [sp, #0]	@ VdhId,
	str	r1, [r8, #200]	@ iftmp.487, <variable>.ErrRatio
	str	r7, [r8, #196]	@ tmp1465, <variable>.VdmStateMachine
.L319:
	bl	VCTRL_VdmPostProc	@
	ldr	r3, [r4, #196]	@ <variable>.ChanId, <variable>.ChanId
	mov	r0, r5	@, VdhId
	add	r1, r3, #32	@ tmp1504, <variable>.ChanId,
	str	r7, [r6, r1, asl #2]	@ tmp1465, g_ChanCtx.ChanDecByVdhPlusOne
	bl	VDMDRV_Reset	@
	mov	r0, r5	@, VdhId
	bl	VDMDRV_ActivateVDH	@
	b	.L315	@
.L325:
	ldr	r1, [r3, #20]	@ <variable>.pic_height_in_mb, <variable>.pic_height_in_mb
	ldr	r0, [r3, #28]	@ <variable>.pic_width_in_mb, <variable>.pic_width_in_mb
	ldr	lr, [r3, #920]	@ <variable>.mbtodec, <variable>.mbtodec
	mul	r9, r0, r1	@ tmp485, <variable>.pic_width_in_mb, <variable>.pic_height_in_mb
	cmp	r9, lr	@ tmp485, <variable>.mbtodec
	bgt	.L290	@,
	ldrsb	r6, [r3, #2]	@ <variable>.NewPicFlag, <variable>.NewPicFlag
	rsbs	ip, r6, #1	@ H264FinishedMultiStart, <variable>.NewPicFlag
	movcc	ip, #0	@ H264FinishedMultiStart
	b	.L291	@
.L295:
	add	ip, r9, #1	@ tmp828, tmp495,
	ldr	r1, [r6, #212]	@ temp.1595, <variable>.pDecParam
	add	r9, sl, ip, asl #3	@, tmp831, tmp491, tmp828,
	ldr	r7, [r9, #200]	@ <variable>.VidStd, <variable>.VidStd
	cmp	r7, #6	@ <variable>.VidStd,
	beq	.L331	@,
.L299:
	bl	OSAL_GetTimeInMs	@
	movw	r7, #:lower16:g_vdm_hal_fun_ptr	@ tmp1584,
	movt	r7, #:upper16:g_vdm_hal_fun_ptr	@ tmp1584,
	rsb	r2, r5, r8	@ tmp1580, VdhId, tmp1587
	movw	r6, #:lower16:.LANCHOR0	@ tmp1576,
	movt	r6, #:upper16:.LANCHOR0	@ tmp1576,
	ldr	ip, [r7, #88]	@ temp.1617, g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareRepair
	add	r7, r4, r2, asl #3	@, tmp1582, tmp1585, tmp1580,
	cmp	ip, #0	@ temp.1617,
	str	r0, [r7, #216]	@, <variable>.StartTime
	beq	.L307	@,
	add	r0, r2, #1	@ tmp1054, tmp1580,
	ldr	r1, [r7, #212]	@, <variable>.pDecParam
	mov	r2, #0	@,
	mov	r3, r5	@, VdhId
	add	sl, r6, r0, asl #3	@, tmp1057, tmp1576, tmp1054,
	ldr	r0, [sl, #200]	@, <variable>.VidStd
	blx	ip	@ temp.1617
	cmp	r0, #0	@,
	beq	.L332	@,
.L307:
	rsb	r8, r5, r8	@ tmp1263, VdhId, tmp1587
	str	r5, [sp, #0]	@ VdhId,
	add	r0, r8, #1	@ tmp1264, tmp1263,
	ldr	r2, [fp, #-204]	@, %sfp
	sub	r3, fp, #196	@,,
	mov	r1, #100	@,
	add	r5, r4, r0, asl #3	@, tmp1267, tmp1585, tmp1264,
	add	r8, r4, r8, asl #3	@, tmp1290, tmp1585, tmp1263,
	ldr	r0, [r5, #196]	@ <variable>.ChanId, <variable>.ChanId
	bl	VCTRL_VdmPostProc	@
	ldr	r2, [r5, #196]	@ <variable>.ChanId, <variable>.ChanId
	mov	r1, #0	@ tmp1283,
	add	r3, r2, #32	@ tmp1281, <variable>.ChanId,
	str	r1, [r4, r3, asl #2]	@ tmp1283, g_ChanCtx.ChanDecByVdhPlusOne
	str	r1, [r8, #196]	@ tmp1283, <variable>.VdmStateMachine
	b	.L315	@
.L329:
	ldrb	r9, [r1, #8]	@ zero_extendqisi2	@ <variable>.PicStruct, <variable>.PicStruct
	cmp	r9, #1	@ <variable>.PicStruct,
	bne	.L306	@,
	mov	lr, #1744	@ tmp1185,
	mla	r2, lr, r5, r6	@ tmp1186, tmp1185, VdhId, tmp1163
	ldr	ip, [r2, #1968]	@ <variable>.ValidGroupNum, <variable>.ValidGroupNum
	cmp	ip, #0	@ <variable>.ValidGroupNum,
	ble	.L306	@,
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:g_vdm_hal_fun_ptr	@ tmp1197,
	movt	r1, #:upper16:g_vdm_hal_fun_ptr	@ tmp1197,
	ldr	ip, [r1, #88]	@ temp.1636, g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareRepair
	cmp	ip, #0	@ temp.1636,
	str	r0, [r7, #216]	@, <variable>.StartTime
	beq	.L307	@,
	mov	r2, r9	@, <variable>.PicStruct
	ldr	r0, [sl, #200]	@, <variable>.VidStd
	ldr	r1, [r7, #212]	@, <variable>.pDecParam
	mov	r3, r5	@, VdhId
	blx	ip	@ temp.1636
	cmp	r0, #0	@,
	bne	.L307	@,
	movw	r0, #:lower16:g_VfmwGlobalStat	@ tmp1217,
	movt	r0, #:upper16:g_VfmwGlobalStat	@ tmp1217,
	mov	r2, #84	@ tmp1220,
	ldr	ip, [r7, #216]	@ <variable>.StartTime, <variable>.StartTime
	mla	r3, r2, r5, r0	@ tmp1221, tmp1220, VdhId, tmp1217
	mov	r1, r5	@, VdhId
	mov	r0, #3	@,
	str	ip, [r3, #4]	@ <variable>.StartTime, <variable>.u32VaLastStartTime
	bl	VDMDRV_StartRepair	@
	mov	r0, #7	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	beq	.L315	@,
	bl	OSAL_GetTimeInMs	@
	ldr	r1, [sl, #196]	@ temp.1641, <variable>.ChanId
	movw	ip, #:lower16:g_TraceFramePeriod	@ tmp1248,
	movt	ip, #:upper16:g_TraceFramePeriod	@ tmp1248,
	add	r6, r6, r1, asl #2	@, tmp1244, tmp1163, temp.1641,
	ldr	r2, [ip, #0]	@ g_TraceFramePeriod, g_TraceFramePeriod
	mov	r3, r0	@ currtime.1640,
	ldr	r0, [r6, #2376]	@ tmp1247, last_rec_pos_time
	rsb	ip, r0, r3	@ tmp1246, tmp1247, currtime.1640
	cmp	ip, r2	@ tmp1246, g_TraceFramePeriod
	bls	.L315	@,
	add	lr, r5, r1, asl #24	@, tmp1258, VdhId, temp.1641,
	ldr	r0, .L335	@,
	add	r2, lr, #458752	@, tmp1258,
	movw	r1, #1220	@,
	str	r3, [r6, #2376]	@ currtime.1640, last_rec_pos_time
	bl	DBG_AddTrace	@
	b	.L315	@
.L324:
	ldr	r0, [fp, #-200]	@, %sfp
	mov	r2, r5	@, VdhId
	ldr	r1, [r6, #212]	@, <variable>.pDecParam
	add	r9, ip, r0, asl #3	@, tmp277, tmp226,,
	ldr	r0, [r9, #208]	@, <variable>.VidStd
	bl	PostPro_SetFullRepair	@
	mov	r3, #0	@ tmp306,
	mov	r2, #100	@ tmp297,
	mov	r0, r3	@, tmp306
	movw	r1, #:lower16:.LC17	@,
	str	r3, [r6, #232]	@ tmp306, <variable>.VdmTimeOut
	movt	r1, #:upper16:.LC17	@,
	str	r2, [r6, #200]	@ tmp297, <variable>.ErrRatio
	bl	dprint_vfmw	@
	b	.L285	@
.L332:
	movw	r2, #:lower16:g_VfmwGlobalStat	@ tmp1069,
	movt	r2, #:upper16:g_VfmwGlobalStat	@ tmp1069,
	mov	r1, #84	@ tmp1072,
	ldr	ip, [r7, #216]	@ <variable>.StartTime, <variable>.StartTime
	mla	r3, r1, r5, r2	@ tmp1073, tmp1072, VdhId, tmp1069
	mov	r0, #2	@,
	mov	r1, r5	@, VdhId
	str	ip, [r3, #4]	@ <variable>.StartTime, <variable>.u32VaLastStartTime
	bl	VDMDRV_StartRepair	@
	mov	r0, #7	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	beq	.L315	@,
	bl	OSAL_GetTimeInMs	@
	ldr	r1, [sl, #196]	@ temp.1622, <variable>.ChanId
	movw	r2, #:lower16:g_TraceFramePeriod	@ tmp1100,
	movt	r2, #:upper16:g_TraceFramePeriod	@ tmp1100,
	add	r6, r6, r1, asl #2	@, tmp1096, tmp1576, temp.1622,
	ldr	ip, [r2, #0]	@ g_TraceFramePeriod, g_TraceFramePeriod
	mov	r3, r0	@ currtime.1621,
	ldr	r0, [r6, #2376]	@ tmp1099, last_rec_pos_time
	rsb	r0, r0, r3	@ tmp1098, tmp1099, currtime.1621
	cmp	r0, ip	@ tmp1098, g_TraceFramePeriod
	bls	.L315	@,
	add	lr, r5, r1, asl #24	@, tmp1110, VdhId, temp.1622,
	ldr	r0, .L335	@,
	add	r2, lr, #458752	@, tmp1110,
	mov	r1, #1184	@,
	str	r3, [r6, #2376]	@ currtime.1621, last_rec_pos_time
	bl	DBG_AddTrace	@
	b	.L315	@
.L331:
	ldrb	r7, [r1, #8]	@ zero_extendqisi2	@ <variable>.PicStruct, <variable>.PicStruct
	add	lr, sl, #256	@ tmp835, tmp491,
	mov	r1, #1744	@ tmp837,
	cmp	r7, #1	@ <variable>.PicStruct,
	mla	r3, r1, r5, lr	@ pRepairParam, tmp837, VdhId, tmp835
	bne	.L299	@,
	ldr	r0, [r3, #840]	@ <variable>.ValidGroupNum, <variable>.ValidGroupNum
	cmp	r0, #0	@ <variable>.ValidGroupNum,
	ble	.L300	@,
	str	r2, [fp, #-212]	@,
	bl	OSAL_GetTimeInMs	@
	movw	r3, #:lower16:g_vdm_hal_fun_ptr	@ tmp848,
	movt	r3, #:upper16:g_vdm_hal_fun_ptr	@ tmp848,
	ldr	ip, [r3, #88]	@ D.38999, g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareRepair
	cmp	ip, #0	@ D.38999,
	str	r0, [r6, #216]	@, <variable>.StartTime
	ldr	r2, [fp, #-212]	@,
	beq	.L307	@,
	ldr	r0, [r9, #200]	@, <variable>.VidStd
	mov	r3, r5	@, VdhId
	ldr	r1, [r6, #212]	@, <variable>.pDecParam
	blx	ip	@ D.38999
	cmp	r0, #0	@,
	bne	.L307	@,
	movw	lr, #:lower16:g_VfmwGlobalStat	@ tmp868,
	movt	lr, #:upper16:g_VfmwGlobalStat	@ tmp868,
	mov	r1, #84	@ tmp871,
	ldr	r2, [r6, #216]	@ <variable>.StartTime, <variable>.StartTime
	mla	ip, r1, r5, lr	@ tmp872, tmp871, VdhId, tmp868
	mov	r0, #2	@,
	mov	r1, r5	@, VdhId
	str	r2, [ip, #4]	@ <variable>.StartTime, <variable>.u32VaLastStartTime
	bl	VDMDRV_StartRepair	@
	mov	r0, #7	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	beq	.L315	@,
	bl	OSAL_GetTimeInMs	@
	ldr	r1, [r9, #196]	@ temp.1598, <variable>.ChanId
	movw	r2, #:lower16:g_TraceFramePeriod	@ tmp899,
	movt	r2, #:upper16:g_TraceFramePeriod	@ tmp899,
	ldr	r2, [r2, #0]	@ g_TraceFramePeriod, g_TraceFramePeriod
	mov	r3, r0	@ currtime,
	mov	r0, r1, asl #2	@ tmp1589, temp.1598,
	add	sl, r0, sl	@ tmp895, tmp1589, tmp491
	ldr	ip, [sl, #2376]	@ tmp898, last_rec_pos_time
	rsb	ip, ip, r3	@ tmp897, tmp898, currtime
	cmp	ip, r2	@ tmp897, g_TraceFramePeriod
	bls	.L315	@,
	add	r4, r0, r4	@ tmp904, tmp1589, tmp1585
	add	r0, r5, r1, asl #24	@, tmp910, VdhId, temp.1598,
	add	r2, r0, #458752	@, tmp910,
	movw	r1, #1129	@,
	ldr	r0, .L335	@,
	str	r3, [r4, #2376]	@ currtime, last_rec_pos_time
	bl	DBG_AddTrace	@
	b	.L315	@
.L328:
	ldr	r2, [r6, #248]	@ D.38977, <variable>.ChanIntState
	cmp	r3, #100	@ temp.1577,
	movge	r3, #100	@ iftmp.477,
	bic	r1, r3, r3, asr #31	@ iftmp.1672, iftmp.477
	str	r1, [r6, #200]	@ iftmp.1672, <variable>.ErrRatio
	cmp	r2, #1	@ D.38977,
	beq	.L333	@,
	cmp	r2, #2	@ D.38977,
	beq	.L334	@,
	cmp	r2, #3	@ D.38977,
	bne	.L315	@,
	add	lr, r9, #1	@ tmp709, tmp495,
	ldr	r2, [fp, #-204]	@, %sfp
	sub	r3, fp, #196	@,,
	str	r5, [sp, #0]	@ VdhId,
	add	r4, sl, lr, asl #3	@, tmp712, tmp491, tmp709,
	ldr	r0, [r4, #196]	@ <variable>.ChanId, <variable>.ChanId
	bl	VCTRL_VdmPostProc	@
	ldr	r2, [r4, #196]	@ <variable>.ChanId, <variable>.ChanId
	movw	r1, #:lower16:251856	@ tmp737,
	movt	r1, #:upper16:251856	@ tmp737,
	mov	r3, #0	@ tmp724,
	str	r3, [r6, #196]	@ tmp724, <variable>.VdmStateMachine
	ldr	ip, [r7, r2, asl #2]	@ tmp736, s_pstVfmwChan
	movw	r2, #:lower16:2211688	@ tmp751,
.L318:
	str	r3, [ip, r1]	@ tmp724, <variable>.stSynCtx.unSyntax.stH264Ctx.pH264DecParam
	movt	r2, #:upper16:2211688	@ tmp751,
	ldr	r1, [r4, #196]	@ <variable>.ChanId, <variable>.ChanId
	mov	r0, r5	@, VdhId
	ldr	lr, [r7, r1, asl #2]	@ tmp750, s_pstVfmwChan
	str	r3, [lr, r2]	@ tmp724, <variable>.stSynCtx.unSyntax.stHevcCtx.pHevcDecParam
	ldr	ip, [r4, #196]	@ <variable>.ChanId, <variable>.ChanId
	add	r1, ip, #32	@ tmp763, <variable>.ChanId,
	str	r3, [sl, r1, asl #2]	@ tmp724, g_ChanCtx.ChanDecByVdhPlusOne
	bl	VDMDRV_Reset	@
	mov	r0, r5	@, VdhId
	bl	VDMDRV_ActivateVDH	@
	b	.L315	@
.L320:
	mov	r7, #0	@ tmp1423,
	ldr	r2, [fp, #-204]	@, %sfp
	ldr	r0, [r4, #196]	@ <variable>.ChanId, <variable>.ChanId
	sub	r3, fp, #196	@,,
	str	r7, [r8, #200]	@ tmp1423, <variable>.ErrRatio
	mov	r1, r7	@, tmp1423
	str	r7, [r8, #196]	@ tmp1423, <variable>.VdmStateMachine
	str	r5, [sp, #0]	@ VdhId,
	b	.L319	@
.L330:
	rsb	lr, r5, r8	@ tmp1297, VdhId, tmp1587
	mov	r6, #0	@ tmp1301,
	add	r7, lr, #1	@ tmp1315, tmp1297,
	ldr	r2, [fp, #-204]	@, %sfp
	add	r8, r4, lr, asl #3	@, tmp1299, tmp1585, tmp1297,
	sub	r3, fp, #196	@,,
	add	r7, r4, r7, asl #3	@, tmp1318, tmp1585, tmp1315,
	mov	r1, r6	@, tmp1301
	str	r6, [r8, #200]	@ tmp1301, <variable>.ErrRatio
	ldr	r0, [r7, #196]	@ <variable>.ChanId, <variable>.ChanId
	str	r6, [r8, #196]	@ tmp1301, <variable>.VdmStateMachine
	str	r5, [sp, #0]	@ VdhId,
	bl	VCTRL_VdmPostProc	@
	ldr	r1, [r7, #196]	@ <variable>.ChanId, <variable>.ChanId
	mov	r0, r5	@, VdhId
	add	ip, r1, #32	@ tmp1332, <variable>.ChanId,
	str	r6, [r4, ip, asl #2]	@ tmp1301, g_ChanCtx.ChanDecByVdhPlusOne
	bl	VDMDRV_Reset	@
	mov	r0, r5	@, VdhId
	bl	VDMDRV_ActivateVDH	@
	b	.L315	@
.L326:
	add	r9, r9, #1	@ tmp540, tmp495,
	mov	r4, #0	@ tmp526,
	ldr	r2, [fp, #-204]	@, %sfp
	sub	r3, fp, #196	@,,
	add	r9, sl, r9, asl #3	@, tmp543, tmp491, tmp540,
	str	r4, [r6, #200]	@ tmp526, <variable>.ErrRatio
	mov	r1, r4	@, tmp526
	ldr	r0, [r9, #196]	@ <variable>.ChanId, <variable>.ChanId
	str	r5, [sp, #0]	@ VdhId,
	str	r4, [r6, #196]	@ tmp526, <variable>.VdmStateMachine
	bl	VCTRL_VdmPostProc	@
	ldr	r2, [r9, #196]	@ <variable>.ChanId, <variable>.ChanId
	add	ip, r2, #32	@ tmp557, <variable>.ChanId,
	str	r4, [sl, ip, asl #2]	@ tmp526, g_ChanCtx.ChanDecByVdhPlusOne
	b	.L315	@
.L327:
	add	r1, r9, #1	@ tmp591, tmp495,
	mov	r4, #0	@ tmp577,
	ldr	r2, [fp, #-204]	@, %sfp
	sub	r3, fp, #196	@,,
	add	r9, sl, r1, asl #3	@, tmp594, tmp491, tmp591,
	str	r4, [r6, #200]	@ tmp577, <variable>.ErrRatio
	str	r4, [r6, #196]	@ tmp577, <variable>.VdmStateMachine
	mov	r1, r4	@, tmp577
	ldr	r0, [r9, #196]	@ <variable>.ChanId, <variable>.ChanId
	str	r5, [sp, #0]	@ VdhId,
	b	.L317	@
.L300:
	ldr	r3, [r3, #1712]	@ <variable>.ValidGroupNum, <variable>.ValidGroupNum
	cmp	r3, #0	@ <variable>.ValidGroupNum,
	ble	.L299	@,
	bl	OSAL_GetTimeInMs	@
	movw	r1, #:lower16:g_vdm_hal_fun_ptr	@ tmp954,
	movt	r1, #:upper16:g_vdm_hal_fun_ptr	@ tmp954,
	ldr	ip, [r1, #88]	@ temp.1601, g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareRepair
	cmp	ip, #0	@ temp.1601,
	str	r0, [r6, #216]	@, <variable>.StartTime
	beq	.L307	@,
	ldr	r0, [r9, #200]	@, <variable>.VidStd
	mov	r2, r7	@, <variable>.PicStruct
	ldr	r1, [r6, #212]	@, <variable>.pDecParam
	mov	r3, r5	@, VdhId
	blx	ip	@ temp.1601
	cmp	r0, #0	@,
	bne	.L307	@,
	movw	r2, #:lower16:g_VfmwGlobalStat	@ tmp974,
	movt	r2, #:upper16:g_VfmwGlobalStat	@ tmp974,
	mov	r0, #84	@ tmp977,
	ldr	lr, [r6, #216]	@ <variable>.StartTime, <variable>.StartTime
	mla	ip, r0, r5, r2	@ tmp978, tmp977, VdhId, tmp974
	mov	r1, r5	@, VdhId
	mov	r0, #3	@,
	str	lr, [ip, #4]	@ <variable>.StartTime, <variable>.u32VaLastStartTime
	bl	VDMDRV_StartRepair	@
	mov	r0, #7	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	beq	.L315	@,
	bl	OSAL_GetTimeInMs	@
	rsb	r1, r5, r8	@ tmp992, VdhId, tmp1587
	movw	r2, #:lower16:g_TraceFramePeriod	@ tmp1005,
	movt	r2, #:upper16:g_TraceFramePeriod	@ tmp1005,
	add	ip, r4, r1, asl #3	@, tmp996, tmp1585, tmp992,
	ldr	r1, [r2, #0]	@ g_TraceFramePeriod, g_TraceFramePeriod
	ldr	r2, [ip, #204]	@ temp.1606, <variable>.ChanId
	add	r4, r4, r2, asl #2	@, tmp1001, tmp1585, temp.1606,
	mov	r3, r0	@ currtime.1605,
	ldr	r0, [r4, #2376]	@ tmp1004, last_rec_pos_time
	rsb	ip, r0, r3	@ tmp1003, tmp1004, currtime.1605
	cmp	ip, r1	@ tmp1003, g_TraceFramePeriod
	bls	.L315	@,
	add	lr, r5, r2, asl #24	@, tmp1015, VdhId, temp.1606,
	ldr	r0, .L335	@,
	add	r2, lr, #458752	@, tmp1015,
	movw	r1, #1157	@,
	str	r3, [r4, #2376]	@ currtime.1605, last_rec_pos_time
	bl	DBG_AddTrace	@
	b	.L315	@
.L333:
	add	r4, r9, #1	@ tmp646, tmp495,
	ldr	r2, [fp, #-204]	@, %sfp
	sub	r3, fp, #196	@,,
	str	r5, [sp, #0]	@ VdhId,
	add	r4, sl, r4, asl #3	@, tmp649, tmp491, tmp646,
	ldr	r0, [r4, #196]	@ <variable>.ChanId, <variable>.ChanId
	bl	VCTRL_VdmPostProc	@
	ldr	r0, [r4, #196]	@ <variable>.ChanId, <variable>.ChanId
	movw	r1, #:lower16:251856	@ tmp665,
	mov	r3, #0	@ tmp666,
	movt	r1, #:upper16:251856	@ tmp665,
	movw	r2, #:lower16:2211688	@ tmp679,
	ldr	ip, [r7, r0, asl #2]	@ tmp664, s_pstVfmwChan
	b	.L318	@
.L334:
	add	sl, sl, r9, asl #3	@, tmp701, tmp491, tmp495,
	ldr	r2, [fp, #-204]	@, %sfp
	sub	r3, fp, #196	@,,
	ldr	r0, [sl, #204]	@ <variable>.ChanId, <variable>.ChanId
	str	r5, [sp, #0]	@ VdhId,
	bl	VCTRL_VdmPostProc	@
	b	.L315	@
.L336:
	.align	2
.L335:
	.word	.LANCHOR1+112
	.fnend
	.size	VDMDRV_AfterDec, .-VDMDRV_AfterDec
	.global	__aeabi_uidiv
	.align	2
	.global	VDMDRV_VdmIntServProc
	.type	VDMDRV_VdmIntServProc, %function
VDMDRV_VdmIntServProc:
	.fnstart
.LFB1549:
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
	subs	r4, r0, #0	@ VdhId, VdhId
	mov	r3, #15	@ tmp155,
	str	r3, [fp, #-48]	@ tmp155, Mb0QpInCurrPic
	bgt	.L366	@,
	mov	r6, r4, asl #3	@ tmp676, VdhId,
	movw	r5, #:lower16:.LANCHOR0	@ tmp674,
	rsb	r7, r4, r6	@ tmp164, VdhId, tmp676
	movt	r5, #:upper16:.LANCHOR0	@ tmp674,
	movw	r0, #:lower16:s_pstVfmwChan	@ tmp160,
	movt	r0, #:upper16:s_pstVfmwChan	@ tmp160,
	add	r1, r5, r7, asl #3	@, tmp168, tmp674, tmp164,
	movw	r8, #:lower16:g_vdm_hal_fun_ptr	@ tmp671,
	movt	r8, #:upper16:g_vdm_hal_fun_ptr	@ tmp671,
	ldr	r2, [r1, #204]	@ <variable>.ChanId, <variable>.ChanId
	ldr	r7, [r0, r2, asl #2]	@ D.39224, s_pstVfmwChan
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	cmp	r7, #0	@ D.39224,
	ldrne	r7, [r7, #1744]	@ ModuleLowlyEnable, <variable>.stSynExtraData.s32ModuleLowlyEnable
	bl	OSAL_SpinLockIRQ	@
	ldr	r3, [r8, #64]	@ D.39229, g_vdm_hal_fun_ptr.pfun_VDMHAL_CheckReg
	cmp	r3, #0	@ D.39229,
	moveq	r0, r3	@ dat, D.39229
	beq	.L343	@,
	mov	r0, #2	@,
	mov	r1, r4	@, VdhId
	blx	r3	@ D.39229
.L343:
	cmp	r7, #1	@ ModuleLowlyEnable,
	beq	.L367	@,
	ands	r7, r0, #1	@ tmp184, dat,
	beq	.L368	@,
.L346:
	mov	r7, r4, asl #2	@ tmp675, VdhId,
	sub	sl, fp, #56	@ tmp247,,
	add	r3, r7, r5	@ tmp244, tmp675, tmp674
	mov	lr, #1	@ tmp246,
	mov	r1, #8	@,
	mov	r0, sl	@, tmp247
	str	lr, [r3, #252]	@ tmp246, s_VdmIsInISR
	bl	__memzero	@
	ldr	r3, [r8, #96]	@ D.39268, g_vdm_hal_fun_ptr.pfun_VDMHAL_BackupInfo
	sub	ip, fp, #48	@ tmp248,,
	str	r4, [fp, #-52]	@ VdhId, BackUpInfo.VdhId
	cmp	r3, #0	@ D.39268,
	str	ip, [fp, #-56]	@ tmp248, BackUpInfo.pMb0QpInCurrPic
	beq	.L350	@,
	mov	r0, sl	@, tmp247
	blx	r3	@ D.39268
.L351:
	ldr	r3, [r8, #52]	@ D.39273, g_vdm_hal_fun_ptr.pfun_VDMHAL_ClearIntState
	cmp	r3, #0	@ D.39273,
	beq	.L352	@,
	mov	r0, r4	@, VdhId
	blx	r3	@ D.39273
.L353:
	rsb	r8, r4, r6	@ tmp257, VdhId, tmp676
	mov	r1, #6	@,
	add	r0, r8, #1	@ tmp258, tmp257,
	mov	r2, #0	@,
	movw	r8, #:lower16:.LANCHOR0	@ tmp254,
	movt	r8, #:upper16:.LANCHOR0	@ tmp254,
	add	sl, r5, r0, asl #3	@, tmp261, tmp674, tmp258,
	ldr	r0, [sl, #196]	@, <variable>.ChanId
	bl	DBG_CountTimeInfo	@
	mov	r0, #6	@,
	bl	CHECK_REC_POS_ENABLE	@
	cmp	r0, #0	@,
	bne	.L369	@,
.L354:
	rsb	r1, r4, r6	@ tmp296, VdhId, tmp676
	movw	r3, #:lower16:.LANCHOR0	@ tmp292,
	movt	r3, #:upper16:.LANCHOR0	@ tmp292,
	add	r2, r5, r1, asl #3	@, tmp298, tmp674, tmp296,
	ldr	lr, [r2, #240]	@ <variable>.ChanResetFlag, <variable>.ChanResetFlag
	cmp	lr, #1	@ <variable>.ChanResetFlag,
	beq	.L370	@,
	mov	sl, #84	@ tmp354,
	mov	r8, #180	@ tmp345,
	mul	sl, sl, r4	@ tmp353, tmp354, VdhId
	movw	r1, #:lower16:g_VfmwGlobalStat	@ tmp672,
	mla	lr, r8, r4, r3	@ tmp346, tmp345, VdhId, tmp292
	movt	r1, #:upper16:g_VfmwGlobalStat	@ tmp672,
	add	r8, sl, r1	@ tmp355, tmp353, tmp672
	add	r3, r7, r3	@ tmp335, tmp675, tmp292
	ldr	ip, [r8, #4]	@ <variable>.u32VaLastStartTime, <variable>.u32VaLastStartTime
	ldr	r0, [r3, #2504]	@ tmp348, cycle
	ldr	r2, [lr, #2220]	@ <variable>.DecCyclePerPic, <variable>.DecCyclePerPic
	cmp	ip, #0	@ <variable>.u32VaLastStartTime,
	add	r9, r0, r2	@ tmp350, tmp348, <variable>.DecCyclePerPic
	str	r9, [r3, #2504]	@ tmp350, cycle
	bne	.L371	@,
.L357:
	rsb	sl, r4, r6	@ tmp511, VdhId, tmp676
	movw	r8, #:lower16:.LANCHOR0	@ tmp507,
	movt	r8, #:upper16:.LANCHOR0	@ tmp507,
	add	r3, r5, sl, asl #3	@, tmp513, tmp674, tmp511,
	ldr	r2, [r3, #196]	@ D.39318, <variable>.VdmStateMachine
	cmp	r2, #0	@ D.39318,
	beq	.L360	@,
	ldr	r9, [r3, #212]	@ <variable>.pDecParam, <variable>.pDecParam
	cmp	r9, #0	@ <variable>.pDecParam,
	beq	.L372	@,
.L360:
	rsb	r9, r4, r6	@ tmp571, VdhId, tmp676
	movw	r8, #:lower16:.LANCHOR0	@ tmp568,
	add	sl, r9, #1	@ tmp572, tmp571,
	movt	r8, #:upper16:.LANCHOR0	@ tmp568,
	add	sl, r5, sl, asl #3	@, tmp575, tmp674, tmp572,
	ldr	r0, [sl, #196]	@, <variable>.ChanId
	bl	VCTRL_IsChanActive	@
	cmp	r0, #0	@,
	bne	.L373	@,
	ldr	r0, [sl, #196]	@, <variable>.ChanId
	bl	VCTRL_GetDecParam	@
	subs	ip, r0, #0	@ D.39333,
	beq	.L374	@,
	mov	r0, r4	@, VdhId
	bl	VDMDRV_AfterDec	@
.L363:
	rsb	r4, r4, r6	@ tmp663, VdhId, tmp676
	add	r7, r7, r5	@ tmp657, tmp675, tmp674
	mov	lr, #0	@ tmp659,
	add	r5, r5, r4, asl #3	@, tmp667, tmp674, tmp663,
	str	lr, [r7, #252]	@ tmp659, s_VdmIsInISR
	ldr	r0, [r5, #204]	@, <variable>.ChanId
	bl	VCTRL_InformVdmFree	@
.L356:
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	bl	OSAL_SpinUnLockIRQ	@
	b	.L365	@
.L366:
	mov	ip, #0	@ tmp159,
	movw	r1, #:lower16:.LC21	@,
	mov	r3, r4	@, VdhId
	mov	r0, ip	@, tmp159
	movt	r1, #:upper16:.LC21	@,
	ldr	r2, .L378	@,
	str	ip, [sp, #0]	@ tmp159,
	bl	dprint_vfmw	@
.L365:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L367:
	ands	sl, r0, #5	@ tmp173, dat,
	beq	.L375	@,
	ldr	r3, [r8, #64]	@ temp.1699, g_vdm_hal_fun_ptr.pfun_VDMHAL_CheckReg
	cmp	r3, #0	@ temp.1699,
	beq	.L346	@,
	mov	r0, r7	@, ModuleLowlyEnable
	mov	r1, r4	@, VdhId
	blx	r3	@ temp.1699
	and	r0, r0, #655360	@ D.39250,,
	cmp	r0, #655360	@ D.39250,
	beq	.L376	@,
	cmp	r0, #524288	@ D.39250,
	beq	.L377	@,
	cmp	r0, #131072	@ D.39250,
	bne	.L346	@,
	rsb	sl, r4, r6	@ tmp218, VdhId, tmp676
	add	r0, r5, sl, asl #3	@, tmp220, tmp674, tmp218,
	ldr	r1, [r0, #248]	@ <variable>.ChanIntState, <variable>.ChanIntState
	cmp	r1, #2	@ <variable>.ChanIntState,
	strne	r7, [r0, #248]	@ ModuleLowlyEnable, <variable>.ChanIntState
	moveq	r1, #3	@ tmp231,
	streq	r1, [r0, #248]	@ tmp231, <variable>.ChanIntState
	b	.L346	@
.L373:
	movw	r2, #1640	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC23	@,
	ldr	r3, [sl, #196]	@, <variable>.ChanId
	movt	r1, #:upper16:.LC23	@,
	add	r9, r8, r9, asl #3	@, tmp608, tmp568, tmp571,
	bl	dprint_vfmw	@
	ldr	r2, [sl, #196]	@ <variable>.ChanId, <variable>.ChanId
	mov	r1, #0	@ tmp601,
	add	r0, r2, #32	@ tmp599, <variable>.ChanId,
	str	r1, [r8, r0, asl #2]	@ tmp601, g_ChanCtx.ChanDecByVdhPlusOne
	str	r1, [r9, #196]	@ tmp601, <variable>.VdmStateMachine
	b	.L363	@
.L369:
	bl	OSAL_GetTimeInMs	@
	ldr	r2, [sl, #196]	@ temp.1703, <variable>.ChanId
	movw	ip, #:lower16:g_TraceFramePeriod	@ tmp280,
	movt	ip, #:upper16:g_TraceFramePeriod	@ tmp280,
	add	r8, r8, r2, asl #2	@, tmp276, tmp254, temp.1703,
	ldr	r1, [ip, #0]	@ g_TraceFramePeriod, g_TraceFramePeriod
	mov	r3, r0	@ currtime,
	ldr	r0, [r8, #2440]	@ tmp279, last_rec_pos_time
	rsb	ip, r0, r3	@ tmp278, tmp279, currtime
	cmp	ip, r1	@ tmp278, g_TraceFramePeriod
	bls	.L354	@,
	add	r2, r4, r2, asl #24	@, tmp290, VdhId, temp.1703,
	ldr	r0, .L378	@,
	add	r2, r2, #393216	@, tmp290,
	movw	r1, #1573	@,
	str	r3, [r8, #2440]	@ currtime, last_rec_pos_time
	bl	DBG_AddTrace	@
	b	.L354	@
.L370:
	add	lr, r3, r1, asl #3	@, tmp318, tmp292, tmp296,
	mov	r0, #0	@ tmp309,
	str	r0, [r2, #240]	@ tmp309, <variable>.ChanResetFlag
	ldr	ip, [lr, #204]	@ <variable>.ChanId, <variable>.ChanId
	add	r1, ip, #32	@ tmp320, <variable>.ChanId,
	str	r0, [r3, r1, asl #2]	@ tmp309, g_ChanCtx.ChanDecByVdhPlusOne
	str	r0, [r2, #196]	@ tmp309, <variable>.VdmStateMachine
	b	.L356	@
.L371:
	str	r1, [fp, #-68]	@,
	bl	OSAL_GetTimeInMs	@
	ldr	r1, [fp, #-68]	@,
	ldr	r2, [r8, #4]	@ prephitmp.1688, <variable>.u32VaLastStartTime
	ldr	r9, [sl, r1]	@ <variable>.u32VaBeginTime, <variable>.u32VaBeginTime
	add	ip, r9, #49920	@ tmp368, <variable>.u32VaBeginTime,
	mov	r9, #84	@ tmp397,
	add	r3, ip, #80	@ tmp368, tmp368,
	cmp	r3, r2	@ tmp368, prephitmp.1688
	strcc	r2, [sl, r1]	@ prephitmp.1688, <variable>.u32VaBeginTime
	mul	r9, r9, r4	@ tmp396, tmp397, VdhId
	ldrcs	ip, [r8, #8]	@ prephitmp.1718, <variable>.u32VaVdmWorkTime
	movcc	r3, #0	@ tmp387,
	strcc	r3, [r8, #8]	@ tmp387, <variable>.u32VaVdmWorkTime
	mov	r8, #180	@ tmp418,
	movcc	ip, r3	@ prephitmp.1718, tmp387
	mla	lr, r8, r4, r5	@ tmp419, tmp418, VdhId, tmp674
	add	r8, r9, r1	@ tmp398, tmp396, tmp672
	movw	sl, #:lower16:g_VfmwGlobalStat	@ tmp394,
	movt	sl, #:upper16:g_VfmwGlobalStat	@ tmp394,
	ldr	lr, [lr, #2220]	@ <variable>.DecCyclePerPic, <variable>.DecCyclePerPic
	add	r3, ip, r0	@ tmp400, prephitmp.1718, CurTime
	rsb	ip, r2, r3	@ tmp401, prephitmp.1688, tmp400
	ldr	r2, [r9, r1]	@ <variable>.u32VaBeginTime, <variable>.u32VaBeginTime
	ldr	r1, [r8, #52]	@ <variable>.u32AccVdmKiloCycle, <variable>.u32AccVdmKiloCycle
	mov	r3, #0	@ tmp408,
	rsb	r2, r2, r0	@ Period, <variable>.u32VaBeginTime, CurTime
	ldr	r0, [r8, #48]	@ <variable>.u32PicNum, <variable>.u32PicNum
	add	r1, r1, lr, lsr #10	@,, <variable>.u32AccVdmKiloCycle, <variable>.DecCyclePerPic,
	str	ip, [r8, #8]	@ tmp401, <variable>.u32VaVdmWorkTime
	add	lr, r0, #1	@ tmp444, <variable>.u32PicNum,
	str	r1, [fp, #-64]	@, %sfp
	str	lr, [r8, #48]	@ tmp444, <variable>.u32PicNum
	cmp	r2, #1000	@ Period,
	str	r3, [r8, #4]	@ tmp408, <variable>.u32VaLastStartTime
	ldr	r1, [fp, #-64]	@, %sfp
	str	r1, [r8, #52]	@, <variable>.u32AccVdmKiloCycle
	bcc	.L357	@,
	mov	r0, #1000	@ tmp465,
	mov	r1, r2	@, Period
	mul	r0, r0, ip	@, tmp465, tmp401
	str	r3, [fp, #-72]	@,
	str	r2, [fp, #-68]	@,
	bl	__aeabi_uidiv	@
	ldr	r3, [fp, #-72]	@,
	str	r3, [r9, sl]	@ tmp408, <variable>.u32VaBeginTime
	str	r3, [r8, #48]	@ tmp408, <variable>.u32PicNum
	ldr	r1, [fp, #-64]	@, %sfp
	str	r1, [r8, #56]	@, <variable>.u32VaVdmKiloCycle
	ldr	sl, [fp, #-68]	@,
	str	r3, [r8, #52]	@ tmp408, <variable>.u32AccVdmKiloCycle
	str	sl, [r8, #60]	@ Period, <variable>.u32StatTime
	str	r0, [r8, #12]	@, <variable>.u32VaVdmLoad
	b	.L357	@
.L368:
	rsb	r4, r4, r6	@ tmp190, VdhId, tmp676
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	add	r5, r5, r4, asl #3	@, tmp192, tmp674, tmp190,
	bl	OSAL_SpinUnLockIRQ	@
	str	r7, [r5, #196]	@ tmp184, <variable>.VdmStateMachine
	b	.L365	@
.L350:
	mov	r0, r3	@, D.39268
	movw	r1, #:lower16:.LC2	@,
	movw	r2, #1560	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	b	.L351	@
.L352:
	mov	r0, r3	@, D.39273
	movw	r1, #:lower16:.LC2	@,
	movw	r2, #1562	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	b	.L353	@
.L377:
	rsb	r2, r4, r6	@ tmp209, VdhId, tmp676
	mov	ip, #2	@ tmp213,
	add	r3, r5, r2, asl #3	@, tmp211, tmp674, tmp209,
	str	ip, [r3, #248]	@ tmp213, <variable>.ChanIntState
	b	.L346	@
.L376:
	rsb	lr, r4, r6	@ tmp200, VdhId, tmp676
	add	sl, r5, lr, asl #3	@, tmp202, tmp674, tmp200,
	str	r7, [sl, #248]	@ ModuleLowlyEnable, <variable>.ChanIntState
	b	.L346	@
.L375:
	rsb	r4, r4, r6	@ tmp179, VdhId, tmp676
	movw	r0, #:lower16:g_TaskLock	@,
	movt	r0, #:upper16:g_TaskLock	@,
	add	r5, r5, r4, asl #3	@, tmp181, tmp674, tmp179,
	bl	OSAL_SpinUnLockIRQ	@
	str	sl, [r5, #196]	@ tmp173, <variable>.VdmStateMachine
	b	.L365	@
.L374:
	ldr	r3, [sl, #196]	@, <variable>.ChanId
	movw	r1, #:lower16:.LC24	@,
	movw	r2, #1650	@,
	movt	r1, #:upper16:.LC24	@,
	str	ip, [fp, #-68]	@,
	bl	dprint_vfmw	@
	ldr	r1, [sl, #196]	@ <variable>.ChanId, <variable>.ChanId
	add	r9, r8, r9, asl #3	@, tmp651, tmp568, tmp571,
	ldr	ip, [fp, #-68]	@,
	add	r3, r1, #32	@ tmp642, <variable>.ChanId,
	str	ip, [r8, r3, asl #2]	@ D.39333, g_ChanCtx.ChanDecByVdhPlusOne
	str	ip, [r9, #196]	@ D.39333, <variable>.VdmStateMachine
	b	.L363	@
.L372:
	add	sl, sl, #1	@ tmp529, tmp511,
	mov	r0, r9	@, <variable>.pDecParam
	movw	r1, #:lower16:.LC22	@,
	movt	r1, #:upper16:.LC22	@,
	add	r8, r8, sl, asl #3	@, tmp532, tmp507, tmp529,
	bl	dprint_vfmw	@
	ldr	r0, [r8, #196]	@, <variable>.ChanId
	bl	VCTRL_GetDecParam	@
	cmp	r0, #0	@,
	beq	.L361	@,
	ldr	r0, [r8, #196]	@ <variable>.ChanId, <variable>.ChanId
	mov	r3, r9	@, <variable>.pDecParam
	mov	r1, #100	@,
	ldr	r2, [fp, #-48]	@, Mb0QpInCurrPic
	str	r4, [sp, #0]	@ VdhId,
	bl	VCTRL_VdmPostProc	@
.L361:
	rsb	r4, r4, r6	@ tmp550, VdhId, tmp676
	mov	lr, #0	@ tmp558,
	add	r3, r5, r4, asl #3	@, tmp554, tmp674, tmp550,
	ldr	ip, [r3, #204]	@ <variable>.ChanId, <variable>.ChanId
	mov	r4, r3	@ tmp565, tmp554
	add	r2, ip, #32	@ tmp556, <variable>.ChanId,
	str	lr, [r5, r2, asl #2]	@ tmp558, g_ChanCtx.ChanDecByVdhPlusOne
	str	lr, [r3, #196]	@ tmp558, <variable>.VdmStateMachine
	b	.L356	@
.L379:
	.align	2
.L378:
	.word	.LANCHOR1+128
	.fnend
	.size	VDMDRV_VdmIntServProc, .-VDMDRV_VdmIntServProc
	.align	2
	.global	VDMDRV_CheckDevice
	.type	VDMDRV_CheckDevice, %function
VDMDRV_CheckDevice:
	.fnstart
.LFB1548:
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
	mov	r6, r0, asl #3	@ tmp559, VdhId,
	rsb	r7, r0, r6	@ tmp157, VdhId, tmp559
	movw	r4, #:lower16:.LANCHOR0	@ tmp560,
	movt	r4, #:upper16:.LANCHOR0	@ tmp560,
	mov	r5, r0	@ VdhId, VdhId
	add	r3, r4, r7, asl #3	@, tmp161, tmp560, tmp157,
	ldr	r0, [r3, #204]	@, <variable>.ChanId
	bl	VCTRL_GetDecParam	@
	cmp	r0, #0	@,
	beq	.L402	@,
.L381:
	rsb	r8, r5, r6	@ tmp220, VdhId, tmp559
	movw	r7, #:lower16:.LANCHOR0	@ tmp216,
	movt	r7, #:upper16:.LANCHOR0	@ tmp216,
	add	sl, r4, r8, asl #3	@, tmp222, tmp560, tmp220,
	ldr	lr, [sl, #196]	@ <variable>.VdmStateMachine, <variable>.VdmStateMachine
	cmp	lr, #0	@ <variable>.VdmStateMachine,
	bne	.L403	@,
.L382:
	rsb	r7, r5, r6	@ tmp333, VdhId, tmp559
	movw	r3, #:lower16:.LANCHOR0	@ tmp329,
	movt	r3, #:upper16:.LANCHOR0	@ tmp329,
	add	r7, r4, r7, asl #3	@, tmp335, tmp560, tmp333,
	ldr	r0, [r7, #224]	@ <variable>.H264NeedMoreStart, <variable>.H264NeedMoreStart
	cmp	r0, #1	@ <variable>.H264NeedMoreStart,
	beq	.L404	@,
	add	r5, r3, r5, asl #2	@, tmp550, tmp329, VdhId,
	ldr	r0, [r5, #192]	@ D.39192, s_eVdmDrvSleepState
	cmp	r0, #0	@ D.39192,
	beq	.L387	@,
	cmp	r0, #1	@ D.39192,
	moveq	r3, #2	@ tmp557,
	streq	r3, [r5, #192]	@ tmp557, s_eVdmDrvSleepState
	beq	.L387	@,
.L388:
	mov	r0, #1	@ D.39157,
.L387:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L403:
	bl	OSAL_GetTimeInMs	@
	ldr	r1, [sl, #216]	@ D.39135, <variable>.StartTime
	cmp	r0, r1	@ D.39133, D.39135
	mov	r3, r0	@ D.39133,
	str	r0, [sl, #220]	@ D.39133, <variable>.CurrTime
	strcc	r0, [sl, #216]	@ D.39133, <variable>.StartTime
	movcc	r0, #1	@ D.39157,
	bcc	.L387	@,
	subs	r2, r3, r1	@ TimeElapse, D.39133, D.39135
	bmi	.L385	@,
	cmp	r1, #0	@ D.39135,
	beq	.L385	@,
	cmp	r2, #500	@ TimeElapse,
	bls	.L388	@,
	mov	r0, #1	@,
	movw	r1, #:lower16:.LC25	@,
	movt	r1, #:upper16:.LC25	@,
	bl	dprint_vfmw	@
	movw	r3, #:lower16:g_event_report	@ tmp258,
	movt	r3, #:upper16:g_event_report	@ tmp258,
	ldr	ip, [r3, #0]	@ g_event_report.492, g_event_report
	cmp	ip, #0	@ g_event_report.492,
	beq	.L389	@,
	add	r7, r7, r8, asl #3	@, tmp266, tmp216, tmp220,
	mov	r2, #0	@,
	mov	r1, #101	@,
	mov	r3, r2	@,
	ldr	r0, [r7, #204]	@, <variable>.ChanId
	blx	ip	@ g_event_report.492
.L389:
	movw	r0, #:lower16:g_vdm_hal_fun_ptr	@ tmp269,
	movt	r0, #:upper16:g_vdm_hal_fun_ptr	@ tmp269,
	ldr	r3, [r0, #44]	@ D.39149, g_vdm_hal_fun_ptr.pfun_VDMHAL_ResetVdm
	cmp	r3, #0	@ D.39149,
	beq	.L390	@,
	mov	r0, r5	@, VdhId
	blx	r3	@ D.39149
.L391:
	rsb	r6, r5, r6	@ tmp275, VdhId, tmp559
	mov	r7, #1	@ tmp279,
	movw	r3, #:lower16:.LANCHOR0	@ tmp271,
	movt	r3, #:upper16:.LANCHOR0	@ tmp271,
	add	r4, r4, r6, asl #3	@, tmp277, tmp560, tmp275,
	ldr	r1, [r4, #240]	@ <variable>.ChanResetFlag, <variable>.ChanResetFlag
	str	r7, [r4, #232]	@ tmp279, <variable>.VdmTimeOut
	cmp	r1, r7	@ <variable>.ChanResetFlag,
	bne	.L392	@,
	add	r6, r3, r6, asl #3	@, tmp324, tmp271, tmp275,
	mov	r2, #0	@ tmp297,
	mov	r0, r2	@ D.39157, tmp297
	str	r2, [r4, #232]	@ tmp297, <variable>.VdmTimeOut
	ldr	lr, [r6, #204]	@ <variable>.ChanId, <variable>.ChanId
	str	r2, [r4, #240]	@ tmp297, <variable>.ChanResetFlag
	add	ip, lr, #32	@ tmp326, <variable>.ChanId,
	str	r2, [r4, #196]	@ tmp297, <variable>.VdmStateMachine
	str	r2, [r3, ip, asl #2]	@ tmp297, g_ChanCtx.ChanDecByVdhPlusOne
	b	.L387	@
.L404:
	ldr	r8, [r7, #236]	@ <variable>.LastWaitMoreStartTime, <variable>.LastWaitMoreStartTime
	cmp	r8, #0	@ <variable>.LastWaitMoreStartTime,
	beq	.L405	@,
.L394:
	rsb	ip, r5, r6	@ tmp359, VdhId, tmp559
	mov	sl, #0	@ tmp363,
	add	r1, ip, #1	@ tmp368, tmp359,
	add	r7, r4, ip, asl #3	@, tmp361, tmp560, tmp359,
	add	r8, r4, r1, asl #3	@, tmp371, tmp560, tmp368,
	str	sl, [r7, #212]	@ tmp363, <variable>.pDecParam
	ldr	r0, [r8, #196]	@, <variable>.ChanId
	bl	VCTRL_GetDecParam	@
	cmp	r0, sl	@ D.39165,
	str	r0, [r7, #212]	@ D.39165, <variable>.pDecParam
	beq	.L395	@,
	ldr	r0, [r8, #196]	@, <variable>.ChanId
	str	sl, [r7, #236]	@ tmp363, <variable>.LastWaitMoreStartTime
	bl	VCTRL_GetVidStd	@
	movw	r2, #:lower16:g_vdm_hal_fun_ptr	@ tmp410,
	movt	r2, #:upper16:g_vdm_hal_fun_ptr	@ tmp410,
	ldr	r3, [r2, #76]	@ D.39173, g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareDec
	cmp	r3, sl	@ D.39173,
	str	r0, [r8, #200]	@, <variable>.VidStd
	beq	.L396	@,
	ldr	r1, [r7, #212]	@, <variable>.pDecParam
	mov	r2, r5	@, VdhId
	blx	r3	@ D.39173
	cmp	r0, sl	@,
	beq	.L397	@,
.L396:
	mov	r0, #0	@,
	rsb	r6, r5, r6	@ tmp425, VdhId, tmp559
	movw	r1, #:lower16:.LC26	@,
	movt	r1, #:upper16:.LC26	@,
	mov	r7, r0	@ tmp429,
	bl	dprint_vfmw	@
	add	r0, r6, #1	@ tmp443, tmp425,
	add	r6, r4, r6, asl #3	@, tmp427, tmp560, tmp425,
	mov	r1, r7	@, tmp429
	mov	r3, r7	@, tmp429
	add	r8, r4, r0, asl #3	@, tmp446, tmp560, tmp443,
	str	r7, [r6, #200]	@ tmp429, <variable>.ErrRatio
	mov	r2, #15	@,
	ldr	r0, [r8, #196]	@ <variable>.ChanId, <variable>.ChanId
	str	r5, [sp, #0]	@ VdhId,
	str	r7, [r6, #196]	@ tmp429, <variable>.VdmStateMachine
	bl	VCTRL_VdmPostProc	@
	ldr	r1, [r8, #196]	@ <variable>.ChanId, <variable>.ChanId
	mov	r0, #1	@ D.39157,
	add	r3, r1, #32	@ tmp459, <variable>.ChanId,
	str	r7, [r4, r3, asl #2]	@ tmp429, g_ChanCtx.ChanDecByVdhPlusOne
	b	.L387	@
.L402:
	add	r7, r4, r7, asl #3	@, tmp170, tmp560, tmp157,
	ldr	r0, [r7, #196]	@ <variable>.VdmStateMachine, <variable>.VdmStateMachine
	cmp	r0, #0	@ <variable>.VdmStateMachine,
	beq	.L382	@,
	movw	r1, #:lower16:g_vdm_hal_fun_ptr	@ tmp173,
	movt	r1, #:upper16:g_vdm_hal_fun_ptr	@ tmp173,
	ldr	r3, [r1, #84]	@ D.39125, g_vdm_hal_fun_ptr.pfun_VDMHAL_IsVdmRun
	cmp	r3, #0	@ D.39125,
	beq	.L383	@,
	mov	r0, r5	@, VdhId
	blx	r3	@ D.39125
	cmp	r0, #0	@,
	movne	r3, #1	@ tmp182,
	strne	r3, [r7, #240]	@ tmp182, <variable>.ChanResetFlag
	bne	.L381	@,
.L383:
	rsb	sl, r5, r6	@ tmp187, VdhId, tmp559
	movw	r1, #1333	@,
	ldr	r0, .L406	@,
	mov	r7, #0	@ tmp191,
	add	ip, r4, sl, asl #3	@, tmp189, tmp560, tmp187,
	add	r8, r4, sl, asl #3	@, tmp211, tmp560, tmp187,
	ldr	r2, [ip, #196]	@, <variable>.VdmStateMachine
	str	r7, [ip, #240]	@ tmp191, <variable>.ChanResetFlag
	bl	DBG_AddTrace	@
	mov	r0, r5	@, VdhId
	bl	VDMDRV_Reset	@
	ldr	sl, [r8, #204]	@ <variable>.ChanId, <variable>.ChanId
	add	r2, sl, #32	@ tmp213, <variable>.ChanId,
	str	r7, [r4, r2, asl #2]	@ tmp191, g_ChanCtx.ChanDecByVdhPlusOne
	b	.L381	@
.L385:
	rsb	r5, r5, r6	@ tmp245, VdhId, tmp559
	mov	r0, #1	@ D.39157,
	add	r4, r4, r5, asl #3	@, tmp247, tmp560, tmp245,
	str	r3, [r4, #216]	@ D.39133, <variable>.StartTime
	b	.L387	@
.L392:
	mov	r0, r5	@, VdhId
	bl	VDMDRV_AfterDec	@
	mov	r0, r7	@ D.39157, tmp279
	b	.L387	@
.L405:
	bl	OSAL_GetTimeInMs	@
	str	r0, [r7, #236]	@, <variable>.LastWaitMoreStartTime
	b	.L394	@
.L397:
	bl	OSAL_GetTimeInMs	@
	movw	r3, #:lower16:g_VfmwGlobalStat	@ tmp470,
	movt	r3, #:upper16:g_VfmwGlobalStat	@ tmp470,
	mov	r1, #84	@ tmp473,
	mla	r2, r1, r5, r3	@ tmp474, tmp473, VdhId, tmp470
	mov	ip, r0	@ D.39180,
	mov	r0, r5	@, VdhId
	str	ip, [r7, #216]	@ D.39180, <variable>.StartTime
	str	ip, [r2, #4]	@ D.39180, <variable>.u32VaLastStartTime
	bl	VDMDRV_StartDec	@
	ldr	r0, [r8, #196]	@, <variable>.ChanId
	mov	r1, r5	@, VdhId
	bl	VDMDRV_SetChanIsDec	@
	mov	r0, #1	@ D.39157,
	b	.L387	@
.L395:
	movw	r1, #:lower16:.LC27	@,
	movt	r1, #:upper16:.LC27	@,
	bl	dprint_vfmw	@
	bl	OSAL_GetTimeInMs	@
	ldr	ip, [r7, #236]	@ temp.1753, <variable>.LastWaitMoreStartTime
	cmp	r0, ip	@ CurTime, temp.1753
	rsbcc	ip, r0, ip	@ tmp495, CurTime, temp.1753
	rsbcs	ip, ip, r0	@ TimeDiff, temp.1753, CurTime
	mvncc	ip, ip	@ TimeDiff, tmp495
	cmp	ip, #200	@ TimeDiff,
	bls	.L388	@,
	mov	r0, #0	@,
	movw	r1, #:lower16:.LC28	@,
	movt	r1, #:upper16:.LC28	@,
	mov	r7, r0	@ tmp505,
	bl	dprint_vfmw	@
	rsb	r1, r5, r6	@ tmp501, VdhId, tmp559
	add	r2, r1, #1	@ tmp528, tmp501,
	mov	r0, #100	@ tmp523,
	add	ip, r4, r1, asl #3	@, tmp503, tmp560, tmp501,
	mov	r3, r7	@, tmp505
	add	r6, r4, r2, asl #3	@, tmp531, tmp560, tmp528,
	mov	r1, r0	@, tmp523
	str	r0, [ip, #200]	@ tmp523, <variable>.ErrRatio
	mov	r2, #15	@,
	ldr	r0, [r6, #196]	@ <variable>.ChanId, <variable>.ChanId
	str	r5, [sp, #0]	@ VdhId,
	str	r7, [ip, #236]	@ tmp505, <variable>.LastWaitMoreStartTime
	str	r7, [ip, #196]	@ tmp505, <variable>.VdmStateMachine
	bl	VCTRL_VdmPostProc	@
	ldr	r3, [r6, #196]	@ <variable>.ChanId, <variable>.ChanId
	mov	r0, #1	@ D.39157,
	add	r2, r3, #32	@ tmp544, <variable>.ChanId,
	str	r7, [r4, r2, asl #2]	@ tmp505, g_ChanCtx.ChanDecByVdhPlusOne
	b	.L387	@
.L390:
	mov	r0, r3	@, D.39149
	movw	r1, #:lower16:.LC2	@,
	movw	r2, #1371	@,
	movt	r1, #:upper16:.LC2	@,
	bl	dprint_vfmw	@
	b	.L391	@
.L407:
	.align	2
.L406:
	.word	.LANCHOR1+152
	.fnend
	.size	VDMDRV_CheckDevice, .-VDMDRV_CheckDevice
	.align	2
	.global	VDMDRV_WakeUpVdm
	.type	VDMDRV_WakeUpVdm, %function
VDMDRV_WakeUpVdm:
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
	mov	r0, #0	@,
	bl	VDMDRV_CheckDevice	@
	cmp	r0, #0	@,
	ldmnefd	sp, {fp, sp, pc}	@
	bl	VDMDRV_ActivateVDH	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDMDRV_WakeUpVdm, .-VDMDRV_WakeUpVdm
	.global	CapItem
	.global	USE_FF_APT_EN
	.global	g_DspDrvState
	.global	g_HwMem
	.global	g_UpMsg
	.global	g_RepairParam
	.global	g_DecReport
	.global	g_BackUp
	.global	g_VdmDrvParam
	.global	g_ChanCtx
	.global	g_VdmExtParam
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.39543, %object
	.size	__func__.39543, 23
__func__.39543:
	.ascii	"VDMDRV_UpdateMatchMode\000"
	.space	1
	.type	__func__.39522, %object
	.size	__func__.39522, 21
__func__.39522:
	.ascii	"VDMDRV_MarkReloadDsp\000"
	.space	3
	.type	__func__.38669, %object
	.size	__func__.38669, 23
__func__.38669:
	.ascii	"VDMDRV_CheckAttachMode\000"
	.space	1
	.type	__func__.38723, %object
	.size	__func__.38723, 19
__func__.38723:
	.ascii	"VDMDRV_ChnDecReady\000"
	.space	1
	.type	__func__.38753, %object
	.size	__func__.38753, 19
__func__.38753:
	.ascii	"VDMDRV_DoBeforeDec\000"
	.space	1
	.type	__func__.38896, %object
	.size	__func__.38896, 16
__func__.38896:
	.ascii	"VDMDRV_AfterDec\000"
	.type	__func__.39211, %object
	.size	__func__.39211, 22
__func__.39211:
	.ascii	"VDMDRV_VdmIntServProc\000"
	.space	2
	.type	__func__.39114, %object
	.size	__func__.39114, 19
__func__.39114:
	.ascii	"VDMDRV_CheckDevice\000"
	.section	__ksymtab_strings,"a",%progbits
	.type	__kstrtab_CapItem, %object
	.size	__kstrtab_CapItem, 8
__kstrtab_CapItem:
	.ascii	"CapItem\000"
	.data
	.align	2
	.type	CapItem, %object
	.size	CapItem, 924
CapItem:
	.word	176
	.word	144
	.word	4
	.word	10
	.word	11
	.word	12
	.word	524288
	.word	352
	.word	288
	.word	4
	.word	10
	.word	11
	.word	12
	.word	786432
	.word	720
	.word	576
	.word	4
	.word	10
	.word	11
	.word	12
	.word	1048576
	.word	1280
	.word	736
	.word	4
	.word	10
	.word	11
	.word	12
	.word	2097152
	.word	1920
	.word	1088
	.word	4
	.word	10
	.word	11
	.word	12
	.word	3145728
	.word	176
	.word	144
	.word	15
	.word	19
	.word	22
	.word	24
	.word	524288
	.word	352
	.word	288
	.word	15
	.word	19
	.word	22
	.word	24
	.word	786432
	.word	720
	.word	576
	.word	9
	.word	15
	.word	16
	.word	17
	.word	1048576
	.word	1280
	.word	736
	.word	6
	.word	13
	.word	13
	.word	14
	.word	2097152
	.word	1920
	.word	1088
	.word	6
	.word	13
	.word	13
	.word	13
	.word	2097152
	.word	5632
	.word	4224
	.word	1
	.word	3
	.word	3
	.word	3
	.word	16777216
	.word	1280
	.word	800
	.word	6
	.word	13
	.word	13
	.word	14
	.word	2097152
	.word	800
	.word	1280
	.word	6
	.word	13
	.word	13
	.word	14
	.word	2097152
	.word	1488
	.word	1280
	.word	6
	.word	13
	.word	13
	.word	14
	.word	3145728
	.word	1280
	.word	1488
	.word	6
	.word	13
	.word	13
	.word	14
	.word	3145728
	.word	2160
	.word	1280
	.word	6
	.word	13
	.word	13
	.word	13
	.word	3145728
	.word	1280
	.word	2176
	.word	6
	.word	13
	.word	13
	.word	13
	.word	3145728
	.word	2160
	.word	2176
	.word	4
	.word	11
	.word	11
	.word	11
	.word	4194304
	.word	4096
	.word	2304
	.word	2
	.word	9
	.word	9
	.word	9
	.word	5242880
	.word	2304
	.word	4096
	.word	2
	.word	9
	.word	9
	.word	9
	.word	5242880
	.word	4096
	.word	4096
	.word	2
	.word	9
	.word	9
	.word	9
	.word	8388608
	.word	8192
	.word	4096
	.word	2
	.word	9
	.word	9
	.word	9
	.word	10485760
	.word	4096
	.word	8192
	.word	2
	.word	9
	.word	9
	.word	9
	.word	10485760
	.word	8192
	.word	8192
	.word	1
	.word	3
	.word	3
	.word	3
	.word	20971520
	.word	1920
	.word	1088
	.word	1
	.word	3
	.word	3
	.word	3
	.word	2097152
	.word	1920
	.word	1088
	.word	1
	.word	3
	.word	3
	.word	3
	.word	2097152
	.word	1920
	.word	1088
	.word	17
	.word	26
	.word	26
	.word	26
	.word	2097152
	.word	192
	.word	192
	.word	15
	.word	19
	.word	22
	.word	24
	.word	524288
	.word	384
	.word	320
	.word	15
	.word	19
	.word	22
	.word	24
	.word	786432
	.word	768
	.word	576
	.word	9
	.word	15
	.word	16
	.word	17
	.word	1048576
	.word	1280
	.word	768
	.word	6
	.word	13
	.word	13
	.word	14
	.word	2097152
	.word	1920
	.word	1088
	.word	6
	.word	13
	.word	13
	.word	13
	.word	2097152
	.word	4096
	.word	2304
	.word	4
	.word	4
	.word	4
	.word	4
	.word	16777216
	.type	USE_FF_APT_EN, %object
	.size	USE_FF_APT_EN, 4
USE_FF_APT_EN:
	.word	1
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%s,%d, MatchVdhIdPlus1 = %d,chanId = %d\012\000"
	.space	3
.LC1:
	.ascii	"%s,%d, i = %d, MatchVdhIdPlus1 = %d\012\000"
	.space	3
.LC2:
	.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000"
	.space	1
.LC3:
	.ascii	"VDMDRV_IsVp6NvopCopy point of picture para null, wa"
	.ascii	"it forever!!!\012\000"
	.space	2
.LC4:
	.ascii	"VDMDRV_IsVc1SkpicCopy point of picture para null, w"
	.ascii	"ait forever!!!\012\000"
	.space	1
.LC5:
	.ascii	"VDMHAL_V200_IsMpeg4NvopCopy point of picture para n"
	.ascii	"ull, wait forever!!!\012\000"
	.space	3
.LC6:
	.ascii	"%s,%d,  frameRate = %d,last = %d\012\000"
	.space	2
.LC7:
	.ascii	"%s,%d, the frameRate change!\012\000"
	.space	2
.LC8:
	.ascii	"%s,%d,chanid = %d,s32Is4k60fpsb = %d\012\000"
	.space	2
.LC9:
	.ascii	"====== forece VDM sleep! ======\012\000"
	.space	3
.LC10:
	.ascii	"%s The channel %d is not active\012\000"
	.space	3
.LC11:
	.ascii	"The channel %d is decoding\012\000"
.LC12:
	.ascii	"The channel %d DEC PARAM is not ready\012\000"
	.space	1
.LC13:
	.ascii	"The channel %d DEC PARAM is not ready(pDecParam == "
	.ascii	"NULL)\012\000"
	.space	2
.LC14:
	.ascii	"---SKIP REPAIR!---\012\000"
.LC15:
	.ascii	"VDM Start Fail 2 !\012\000"
.LC16:
	.ascii	"isr begin: *pVdmStateMachine = %d, timeout = %d, Er"
	.ascii	"rRatio = %d\012\000"
.LC17:
	.ascii	"ISR process vdm timeout!\012\000"
	.space	2
.LC18:
	.ascii	"*pErrRatio = %d\012\000"
	.space	3
.LC19:
	.ascii	"*pH264NeedMoreStart, *pH264FinishedMultiStart = %d,"
	.ascii	"%d\012\000"
	.space	1
.LC20:
	.ascii	"VdmStateMachine=%d Error!\012\000"
	.space	1
.LC21:
	.ascii	"%s: VdhId(%d) > %d\012\000"
.LC22:
	.ascii	"vdm state machine = %d, but DecParam is null!\012\000"
	.space	1
.LC23:
	.ascii	"line :%d ISR called but chan %d is not active!\012\000"
.LC24:
	.ascii	"lline: %d ISR called but chan %d is not active!\012"
	.ascii	"\000"
	.space	3
.LC25:
	.ascii	"VDM Time Out(%d ms), Reset VDM!\012\000"
	.space	3
.LC26:
	.ascii	"VDM Start Fail 1 !\012\000"
.LC27:
	.ascii	"h264 more start need parameter\012\000"
.LC28:
	.ascii	"wait more start time out!\012\000"
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_ChanCtx, %object
	.size	g_ChanCtx, 192
g_ChanCtx:
	.space	192
	.type	s_eVdmDrvSleepState, %object
	.size	s_eVdmDrvSleepState, 4
s_eVdmDrvSleepState:
	.space	4
	.type	g_VdmDrvParam, %object
	.size	g_VdmDrvParam, 56
g_VdmDrvParam:
	.space	56
	.type	s_VdmIsInISR, %object
	.size	s_VdmIsInISR, 4
s_VdmIsInISR:
	.space	4
	.type	g_RepairParam, %object
	.size	g_RepairParam, 1744
g_RepairParam:
	.space	1744
	.type	DiffFrameCnt.38666, %object
	.size	DiffFrameCnt.38666, 64
DiffFrameCnt.38666:
	.space	64
	.type	g_LastFPS.38667, %object
	.size	g_LastFPS.38667, 64
g_LastFPS.38667:
	.space	64
	.type	g_DspDrvState, %object
	.size	g_DspDrvState, 4
g_DspDrvState:
	.space	4
	.type	last_rec_pos_time.38751, %object
	.size	last_rec_pos_time.38751, 64
last_rec_pos_time.38751:
	.space	64
	.type	g_BackUp, %object
	.size	g_BackUp, 180
g_BackUp:
	.space	180
	.type	last_rec_pos_time.38884, %object
	.size	last_rec_pos_time.38884, 64
last_rec_pos_time.38884:
	.space	64
	.type	last_rec_pos_time.39207, %object
	.size	last_rec_pos_time.39207, 64
last_rec_pos_time.39207:
	.space	64
	.type	cycle.39206, %object
	.size	cycle.39206, 8
cycle.39206:
	.space	8
	.type	g_HwMem, %object
	.size	g_HwMem, 1208
g_HwMem:
	.space	1208
	.type	g_UpMsg, %object
	.size	g_UpMsg, 3200
g_UpMsg:
	.space	3200
	.type	g_DecReport, %object
	.size	g_DecReport, 816
g_DecReport:
	.space	816
	.type	g_VdmExtParam, %object
	.size	g_VdmExtParam, 140
g_VdmExtParam:
	.space	140
	.section	___ksymtab+CapItem,"a",%progbits
	.align	2
	.type	__ksymtab_CapItem, %object
	.size	__ksymtab_CapItem, 8
__ksymtab_CapItem:
@ value:
	.word	CapItem
@ name:
	.word	__kstrtab_CapItem
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
