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
	.file	"pq_hal_fmd.c"
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
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0
@ -Idrivers/msp/pq/pq_v3_0
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/mach-hi3798mx/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/api/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/drv/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/api/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/api/pq/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/api/higo/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/pq/pq_v3_0/mng
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/pq/pq_v3_0/hal/hi3798mv100
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/pq/pq_v3_0/hal/common
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/pq/pq_v3_0
@ -imultilib armv7a_soft -iprefix
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/
@ -isysroot /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../target
@ -D__KERNEL__ -D__LINUX_ARM_ARCH__=7 -Uarm -DCHIP_TYPE_hi3796mv100
@ -DSDK_VERSION=HiSTBAndroidV600R001C00SPC060_v2015040918 -DHI_MCE_SUPPORT
@ -DHI_GPIOI2C_SUPPORT -DHI_LOG_SUPPORT=1 -DHI_LOG_LEVEL=4
@ -DHI_PROC_SUPPORT=1 -DHI_HDMI_SUPPORT_1_4 -DHI_KEYLED_SUPPORT
@ -DHI_HDCP_SUPPORT -DHI_SCI_SUPPORT -DHI_PVR_SUPPORT -DHI_VI_SUPPORT
@ -DHI_VENC_SUPPORT -DHI_AENC_SUPPORT -DHI_PQ_V3_0 -DKBUILD_STR(s)=#s
@ -DKBUILD_BASENAME=KBUILD_STR(pq_hal_fmd)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/hal/hi3798mv100/.pq_hal_fmd.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_fmd.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_fmd.o -O2 -Wall -Wundef
@ -Wstrict-prototypes -Wno-trigraphs -Werror-implicit-function-declaration
@ -Wno-format-security -Wframe-larger-than=1024
@ -Wdeclaration-after-statement -Wno-pointer-sign -p -fno-strict-aliasing
@ -fno-common -fno-delete-null-pointer-checks -fno-dwarf2-cfi-asm
@ -funwind-tables -fno-stack-protector -fno-omit-frame-pointer
@ -fno-optimize-sibling-calls -fno-strict-overflow -fconserve-stack
@ -fverbose-asm
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
	.global	PQ_HAL_SetEdgeSmoothEn
	.type	PQ_HAL_SetEdgeSmoothEn, %function
PQ_HAL_SetEdgeSmoothEn:
	.fnstart
.LFB1395:
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
	mov	r4, r1	@ bEdgeSmoothEn, bEdgeSmoothEn
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	beq	.L6	@,
	movw	r2, #4435	@ tmp140,
	mov	r0, #0	@ D.35646,
	ldrb	r1, [r3, r2]	@ zero_extendqisi2	@,
	bfi	r1, r4, #6, #1	@ tmp141, bEdgeSmoothEn,,
	strb	r1, [r3, r2]	@ tmp141,
.L3:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L6:
	mov	r0, #1	@,
	mov	r1, #41	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	mov	r3, #213	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	movw	ip, #:lower16:.LC0	@ tmp139,
	movt	ip, #:upper16:.LC0	@ tmp139,
	str	ip, [sp, #0]	@ tmp139,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35646,
	b	.L3	@
	.fnend
	.size	PQ_HAL_SetEdgeSmoothEn, .-PQ_HAL_SetEdgeSmoothEn
	.align	2
	.global	PQ_HAL_SetIFmdInfo
	.type	PQ_HAL_SetIFmdInfo, %function
PQ_HAL_SetIFmdInfo:
	.fnstart
.LFB1394:
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
	mov	r4, r1	@ NewCfg, NewCfg
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	beq	.L11	@,
	movw	lr, #4099	@ tmp142,
	ldr	r6, [r4, #12]	@ <variable>.die_out_sel, <variable>.die_out_sel
	ldrb	r5, [r3, lr]	@ zero_extendqisi2	@,
	movw	r2, #4435	@ tmp150,
	ldrb	ip, [r3, r2]	@ zero_extendqisi2	@,
	mov	r0, #0	@ D.35630,
	bfi	r5, r6, #4, #1	@ tmp143, <variable>.die_out_sel,,
	strb	r5, [r3, lr]	@ tmp143,
	ldr	r6, [r4, #12]	@ <variable>.die_out_sel, <variable>.die_out_sel
	uxtb	r5, r5	@ tmp147, tmp143
	bfi	r5, r6, #5, #1	@ tmp147, <variable>.die_out_sel,,
	strb	r5, [r3, lr]	@ tmp147,
	ldr	r1, [r4, #8]	@ <variable>.dir_mch, <variable>.dir_mch
	bfi	ip, r1, #5, #1	@ tmp151, <variable>.dir_mch,,
	strb	ip, [r3, r2]	@ tmp151,
	ldr	lr, [r4, #8]	@ <variable>.dir_mch, <variable>.dir_mch
	ldrb	r1, [r3, r2]	@ zero_extendqisi2	@,
	bfi	r1, lr, #7, #1	@ tmp155, <variable>.dir_mch,,
	strb	r1, [r3, r2]	@ tmp155,
.L9:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L11:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L12	@,
	mov	r3, #198	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35630,
	b	.L9	@
.L13:
	.align	2
.L12:
	.word	.LANCHOR0+24
	.fnend
	.size	PQ_HAL_SetIFmdInfo, .-PQ_HAL_SetIFmdInfo
	.align	2
	.global	PQ_HAL_SetIFmdRegist
	.type	PQ_HAL_SetIFmdRegist, %function
PQ_HAL_SetIFmdRegist:
	.fnstart
.LFB1392:
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
	mov	r4, r1	@ pstFmdDectCfg, pstFmdDectCfg
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	beq	.L18	@,
	ldr	r1, [r4, #32]	@ <variable>.stPqFmdHistbinThd.u32Hist_thd0, <variable>.stPqFmdHistbinThd.u32Hist_thd0
	movw	lr, #4420	@ tmp141,
	movw	r2, #4421	@ tmp144,
	movw	r6, #4422	@ tmp147,
	movw	r0, #4423	@ tmp150,
	strb	r1, [r3, lr]	@ <variable>.stPqFmdHistbinThd.u32Hist_thd0, <variable>.VPSS_PDPHISTTHD1.bits.hist_thd0
	movw	lr, #4432	@ tmp163,
	ldr	ip, [r4, #36]	@ <variable>.stPqFmdHistbinThd.u32Hist_thd1, <variable>.stPqFmdHistbinThd.u32Hist_thd1
	movw	r1, #4434	@ tmp167,
	ldrb	r5, [r3, lr]	@ zero_extendqisi2	@,
	strb	ip, [r3, r2]	@ <variable>.stPqFmdHistbinThd.u32Hist_thd1, <variable>.VPSS_PDPHISTTHD1.bits.hist_thd1
	movw	r2, #4424	@ tmp153,
	ldr	r8, [r4, #40]	@ <variable>.stPqFmdHistbinThd.u32Hist_thd2, <variable>.stPqFmdHistbinThd.u32Hist_thd2
	ldrh	ip, [r3, r1]	@,
	strb	r8, [r3, r6]	@ <variable>.stPqFmdHistbinThd.u32Hist_thd2, <variable>.VPSS_PDPHISTTHD1.bits.hist_thd2
	movw	r8, #4425	@ tmp156,
	ldr	r7, [r4, #44]	@ <variable>.stPqFmdHistbinThd.u32Hist_thd3, <variable>.stPqFmdHistbinThd.u32Hist_thd3
	strb	r7, [r3, r0]	@ <variable>.stPqFmdHistbinThd.u32Hist_thd3, <variable>.VPSS_PDPHISTTHD1.bits.hist_thd3
	movw	r7, #4426	@ tmp159,
	ldr	r6, [r4, #116]	@ <variable>.stPqFmdPccBlk.u32Mov_coring_blk, <variable>.stPqFmdPccBlk.u32Mov_coring_blk
	strb	r6, [r3, r2]	@ <variable>.stPqFmdPccBlk.u32Mov_coring_blk, <variable>.VPSS_PDPCCMOV.bits.mov_coring_blk
	movw	r2, #4476	@ tmp250,
	ldr	r0, [r4, #68]	@ <variable>.stPqFmdPccThd.u32Mov_coring_tkr, <variable>.stPqFmdPccThd.u32Mov_coring_tkr
	strb	r0, [r3, r8]	@ <variable>.stPqFmdPccThd.u32Mov_coring_tkr, <variable>.VPSS_PDPCCMOV.bits.mov_coring_tkr
	mov	r0, #0	@ D.35456,
	ldr	r8, [r4, #64]	@ <variable>.stPqFmdPccThd.u32Mov_coring_norm, <variable>.stPqFmdPccThd.u32Mov_coring_norm
	strb	r8, [r3, r7]	@ <variable>.stPqFmdPccThd.u32Mov_coring_norm, <variable>.VPSS_PDPCCMOV.bits.mov_coring_norm
	ldr	r7, [r4, #28]	@ <variable>.stPqFmdCtrl.u32Bitsmov2r, <variable>.stPqFmdCtrl.u32Bitsmov2r
	bfi	r5, r7, #0, #3	@ tmp164, <variable>.stPqFmdCtrl.u32Bitsmov2r,,
	strb	r5, [r3, lr]	@ tmp164,
	ldr	r6, [r4, #24]	@ <variable>.stPqFmdCtrl.u32Edge_smooth_ratio, <variable>.stPqFmdCtrl.u32Edge_smooth_ratio
	movw	r5, #4437	@ tmp170,
	bfi	ip, r6, #4, #8	@ tmp168, <variable>.stPqFmdCtrl.u32Edge_smooth_ratio,,
	strh	ip, [r3, r1]	@ movhi	@ tmp168,
	ldr	lr, [r4, #56]	@ <variable>.stPqFmdHistbinThd.u32Diff_movblk_thd, <variable>.stPqFmdHistbinThd.u32Diff_movblk_thd
	movw	ip, #4444	@ tmp173,
	strb	lr, [r3, r5]	@ <variable>.stPqFmdHistbinThd.u32Diff_movblk_thd, <variable>.VPSS_PDBLKTHD.bits.diff_movblk_thd
	movw	r5, #4445	@ tmp176,
	ldr	r6, [r4, #124]	@ <variable>.stPqFmdUmThd.u32Um_thd0, <variable>.stPqFmdUmThd.u32Um_thd0
	strb	r6, [r3, ip]	@ <variable>.stPqFmdUmThd.u32Um_thd0, <variable>.VPSS_PDUMTHD.bits.um_thd0
	movw	ip, #4446	@ tmp179,
	ldr	lr, [r4, #128]	@ <variable>.stPqFmdUmThd.u32Um_thd1, <variable>.stPqFmdUmThd.u32Um_thd1
	strb	lr, [r3, r5]	@ <variable>.stPqFmdUmThd.u32Um_thd1, <variable>.VPSS_PDUMTHD.bits.um_thd1
	movw	r5, #4448	@ tmp182,
	ldr	r6, [r4, #132]	@ <variable>.stPqFmdUmThd.u32Um_thd2, <variable>.stPqFmdUmThd.u32Um_thd2
	strb	r6, [r3, ip]	@ <variable>.stPqFmdUmThd.u32Um_thd2, <variable>.VPSS_PDUMTHD.bits.um_thd2
	movw	ip, #4449	@ tmp185,
	ldr	lr, [r4, #76]	@ <variable>.stPqFmdPccThd.u32Coring_tkr, <variable>.stPqFmdPccThd.u32Coring_tkr
	strb	lr, [r3, r5]	@ <variable>.stPqFmdPccThd.u32Coring_tkr, <variable>.VPSS_PDPCCCORING.bits.coring_tkr
	movw	r5, #4450	@ tmp188,
	ldr	r6, [r4, #72]	@ <variable>.stPqFmdPccThd.u32Coring_norm, <variable>.stPqFmdPccThd.u32Coring_norm
	strb	r6, [r3, ip]	@ <variable>.stPqFmdPccThd.u32Coring_norm, <variable>.VPSS_PDPCCCORING.bits.coring_norm
	movw	ip, #4452	@ tmp191,
	ldr	lr, [r4, #120]	@ <variable>.stPqFmdPccBlk.u32Coring_blk, <variable>.stPqFmdPccBlk.u32Coring_blk
	strb	lr, [r3, r5]	@ <variable>.stPqFmdPccBlk.u32Coring_blk, <variable>.VPSS_PDPCCCORING.bits.coring_blk
	ldr	r6, [r4, #80]	@ <variable>.stPqFmdPccThd.u32Pcc_hthd, <variable>.stPqFmdPccThd.u32Pcc_hthd
	ldrb	lr, [r3, r1]	@ zero_extendqisi2	@,
	strb	r6, [r3, ip]	@ <variable>.stPqFmdPccThd.u32Pcc_hthd, <variable>.VPSS_PDPCCHTHD.bits.pcc_hthd
	movw	ip, #4456	@ tmp194,
	ldr	r5, [r4, #84]	@ <variable>.stPqFmdPccThd.u32Pcc_vthd0, <variable>.stPqFmdPccThd.u32Pcc_vthd0
	strb	r5, [r3, ip]	@ <variable>.stPqFmdPccThd.u32Pcc_vthd0, <variable>.VPSS_PDPCCVTHD.bits.pcc_vthd0
	movw	r5, #4457	@ tmp197,
	ldr	r6, [r4, #88]	@ <variable>.stPqFmdPccThd.u32Pcc_vthd1, <variable>.stPqFmdPccThd.u32Pcc_vthd1
	strb	r6, [r3, r5]	@ <variable>.stPqFmdPccThd.u32Pcc_vthd1, <variable>.VPSS_PDPCCVTHD.bits.pcc_vthd1
	movw	r5, #4458	@ tmp200,
	ldr	ip, [r4, #92]	@ <variable>.stPqFmdPccThd.u32Pcc_vthd2, <variable>.stPqFmdPccThd.u32Pcc_vthd2
	strb	ip, [r3, r5]	@ <variable>.stPqFmdPccThd.u32Pcc_vthd2, <variable>.VPSS_PDPCCVTHD.bits.pcc_vthd2
	movw	ip, #4459	@ tmp203,
	ldr	r6, [r4, #96]	@ <variable>.stPqFmdPccThd.u32Pcc_vthd3, <variable>.stPqFmdPccThd.u32Pcc_vthd3
	strb	r6, [r3, ip]	@ <variable>.stPqFmdPccThd.u32Pcc_vthd3, <variable>.VPSS_PDPCCVTHD.bits.pcc_vthd3
	movw	ip, #4460	@ tmp206,
	ldr	r5, [r4, #136]	@ <variable>.stPqFmdItdiffThd.u32Itdiff_vthd0, <variable>.stPqFmdItdiffThd.u32Itdiff_vthd0
	strb	r5, [r3, ip]	@ <variable>.stPqFmdItdiffThd.u32Itdiff_vthd0, <variable>.VPSS_PDITDIFFVTHD.bits.itdiff_vthd0
	movw	r5, #4461	@ tmp209,
	ldr	r6, [r4, #140]	@ <variable>.stPqFmdItdiffThd.u32Itdiff_vthd1, <variable>.stPqFmdItdiffThd.u32Itdiff_vthd1
	strb	r6, [r3, r5]	@ <variable>.stPqFmdItdiffThd.u32Itdiff_vthd1, <variable>.VPSS_PDITDIFFVTHD.bits.itdiff_vthd1
	movw	r5, #4462	@ tmp212,
	ldr	ip, [r4, #144]	@ <variable>.stPqFmdItdiffThd.u32Itdiff_vthd2, <variable>.stPqFmdItdiffThd.u32Itdiff_vthd2
	strb	ip, [r3, r5]	@ <variable>.stPqFmdItdiffThd.u32Itdiff_vthd2, <variable>.VPSS_PDITDIFFVTHD.bits.itdiff_vthd2
	movw	ip, #4463	@ tmp215,
	ldr	r6, [r4, #148]	@ <variable>.stPqFmdItdiffThd.u32Itdiff_vthd3, <variable>.stPqFmdItdiffThd.u32Itdiff_vthd3
	strb	r6, [r3, ip]	@ <variable>.stPqFmdItdiffThd.u32Itdiff_vthd3, <variable>.VPSS_PDITDIFFVTHD.bits.itdiff_vthd3
	movw	ip, #4464	@ tmp218,
	ldr	r5, [r4, #156]	@ <variable>.stPqFmdLashThd.u32Lasi_thd, <variable>.stPqFmdLashThd.u32Lasi_thd
	strb	r5, [r3, ip]	@ <variable>.stPqFmdLashThd.u32Lasi_thd, <variable>.VPSS_PDLASITHD.bits.lasi_coring_thd
	movw	r5, #4465	@ tmp221,
	ldr	r6, [r4, #160]	@ <variable>.stPqFmdLashThd.u32Edge_thd, <variable>.stPqFmdLashThd.u32Edge_thd
	movw	ip, #4466	@ tmp224,
	strb	r6, [r3, r5]	@ <variable>.stPqFmdLashThd.u32Edge_thd, <variable>.VPSS_PDLASITHD.bits.lasi_edge_thd
	ldr	r6, [r4, #164]	@ <variable>.stPqFmdLashThd.u32Lasi_mov_thr, <variable>.stPqFmdLashThd.u32Lasi_mov_thr
	strb	r6, [r3, ip]	@ <variable>.stPqFmdLashThd.u32Lasi_mov_thr, <variable>.VPSS_PDLASITHD.bits.lasi_mov_thd
	ldr	r5, [r4, #152]	@ <variable>.stPqFmdLashThd.u32Lasi_mode, <variable>.stPqFmdLashThd.u32Lasi_mode
	bfi	lr, r5, #3, #1	@ tmp229, <variable>.stPqFmdLashThd.u32Lasi_mode,,
	strb	lr, [r3, r1]	@ tmp229,
	ldr	ip, [r4, #168]	@ <variable>.stPqFmdLashThd.u32LasiTxtAlpha, <variable>.stPqFmdLashThd.u32LasiTxtAlpha
	movw	r5, #4468	@ tmp231,
	movw	r1, #4469	@ tmp234,
	strb	ip, [r3, r5]	@ <variable>.stPqFmdLashThd.u32LasiTxtAlpha, <variable>.VPSS_PDLASIMODE0COEF.bits.lasi_txt_alpha
	movw	r5, #4472	@ tmp237,
	ldr	lr, [r4, #172]	@ <variable>.stPqFmdLashThd.u32LasiTxtCoring, <variable>.stPqFmdLashThd.u32LasiTxtCoring
	strb	lr, [r3, r1]	@ <variable>.stPqFmdLashThd.u32LasiTxtCoring, <variable>.VPSS_PDLASIMODE0COEF.bits.lasi_txt_coring
	movw	r1, #4473	@ tmp240,
	ldr	ip, [r4, #176]	@ <variable>.stPqFmdLashThd.u32LasiTxtThd0, <variable>.stPqFmdLashThd.u32LasiTxtThd0
	strb	ip, [r3, r5]	@ <variable>.stPqFmdLashThd.u32LasiTxtThd0, <variable>.VPSS_PDLASIMODE1COEF.bits.lasi_txt_thd0
	movw	ip, #4474	@ tmp243,
	ldr	lr, [r4, #180]	@ <variable>.stPqFmdLashThd.u32LasiTxtThd1, <variable>.stPqFmdLashThd.u32LasiTxtThd1
	strb	lr, [r3, r1]	@ <variable>.stPqFmdLashThd.u32LasiTxtThd1, <variable>.VPSS_PDLASIMODE1COEF.bits.lasi_txt_thd1
	movw	lr, #4475	@ tmp246,
	ldr	r5, [r4, #184]	@ <variable>.stPqFmdLashThd.u32LasiTxtThd2, <variable>.stPqFmdLashThd.u32LasiTxtThd2
	ldr	r1, [r3, r2]	@ tmp251,
	strb	r5, [r3, ip]	@ <variable>.stPqFmdLashThd.u32LasiTxtThd2, <variable>.VPSS_PDLASIMODE1COEF.bits.lasi_txt_thd2
	ldr	r5, [r4, #188]	@ <variable>.stPqFmdLashThd.u32LasiTxtThd3, <variable>.stPqFmdLashThd.u32LasiTxtThd3
	strb	r5, [r3, lr]	@ <variable>.stPqFmdLashThd.u32LasiTxtThd3, <variable>.VPSS_PDLASIMODE1COEF.bits.lasi_txt_thd3
	ldr	ip, [r4, #192]	@ <variable>.stPqFmdRegion.u32Region1YStt, <variable>.stPqFmdRegion.u32Region1YStt
	bfi	r1, ip, #12, #12	@ tmp251, <variable>.stPqFmdRegion.u32Region1YStt,,
	str	r1, [r3, r2]	@ tmp251,
	ldr	lr, [r4, #196]	@ <variable>.stPqFmdRegion.u32Region1YEnd, <variable>.stPqFmdRegion.u32Region1YEnd
	ldrh	r1, [r3, r2]	@,
	bfi	r1, lr, #0, #12	@ tmp254, <variable>.stPqFmdRegion.u32Region1YEnd,,
	strh	r1, [r3, r2]	@ movhi	@ tmp254,
.L16:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L18:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L19	@,
	mov	r3, #38	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35456,
	b	.L16	@
.L20:
	.align	2
.L19:
	.word	.LANCHOR0+44
	.fnend
	.size	PQ_HAL_SetIFmdRegist, .-PQ_HAL_SetIFmdRegist
	.align	2
	.global	PQ_HAL_GetIFmdStatInfo
	.type	PQ_HAL_GetIFmdStatInfo, %function
PQ_HAL_GetIFmdStatInfo:
	.fnstart
.LFB1393:
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
	subs	r4, r1, #0	@ pIfmdTotalHardPara, pIfmdTotalHardPara
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	ldr	r0, [r0, #0]	@, <variable>.u32HandleNo
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	movw	lr, #4548	@ tmp137,
	movw	r0, #4552	@ tmp139,
	ldr	ip, [r3, lr]	@ <variable>.bits.hsit_bin, <variable>.bits.hsit_bin
	movw	r1, #4556	@ tmp141,
	str	ip, [r4, #120]	@ <variable>.bits.hsit_bin, <variable>.stFmdRtlStatPara.frmHstBin.HISTOGRAM_BIN_1
	movw	ip, #4560	@ tmp143,
	ldr	r2, [r3, r0]	@ <variable>.bits.hsit_bin, <variable>.bits.hsit_bin
	str	r2, [r4, #124]	@ <variable>.bits.hsit_bin, <variable>.stFmdRtlStatPara.frmHstBin.HISTOGRAM_BIN_2
	mov	r2, #4480	@ tmp145,
	ldr	lr, [r3, r1]	@ <variable>.bits.hsit_bin, <variable>.bits.hsit_bin
	str	lr, [r4, #128]	@ <variable>.bits.hsit_bin, <variable>.stFmdRtlStatPara.frmHstBin.HISTOGRAM_BIN_3
	movw	lr, #4588	@ tmp147,
	ldr	r0, [r3, ip]	@ <variable>.bits.hsit_bin, <variable>.bits.hsit_bin
	str	r0, [r4, #132]	@ <variable>.bits.hsit_bin, <variable>.stFmdRtlStatPara.frmHstBin.HISTOGRAM_BIN_4
	movw	r0, #4584	@ tmp149,
	ldr	r1, [r3, r2]	@ <variable>.VPSS_PDFRMITDIFF.bits.frm_it_diff, <variable>.VPSS_PDFRMITDIFF.bits.frm_it_diff
	str	r1, [r4, #0]	@ <variable>.VPSS_PDFRMITDIFF.bits.frm_it_diff, <variable>.stFmdRtlStatPara.frmITDiff
	movw	r1, #4580	@ tmp151,
	ldr	ip, [r3, lr]	@ <variable>.VPSS_PDPCCBWD0.bits.pcc_bwd_0, <variable>.VPSS_PDPCCBWD0.bits.pcc_bwd_0
	str	ip, [r4, #28]	@ <variable>.VPSS_PDPCCBWD0.bits.pcc_bwd_0, <variable>.stFmdRtlStatPara.frmPcc.PCC_BWD
	movw	ip, #4592	@ tmp153,
	ldr	r2, [r3, r0]	@ <variable>.VPSS_PDPCCFWD0.bits.pcc_fwd_0, <variable>.VPSS_PDPCCFWD0.bits.pcc_fwd_0
	str	r2, [r4, #24]	@ <variable>.VPSS_PDPCCFWD0.bits.pcc_fwd_0, <variable>.stFmdRtlStatPara.frmPcc.PCC_FWD
	movw	r2, #4596	@ tmp155,
	ldr	lr, [r3, r1]	@ <variable>.VPSS_PDPCCFFWD0.bits.pcc_ffwd_0, <variable>.VPSS_PDPCCFFWD0.bits.pcc_ffwd_0
	add	r1, r3, #4224	@, pstVpssVirReg,
	add	r1, r1, #28	@,,
	str	lr, [r4, #20]	@ <variable>.VPSS_PDPCCFFWD0.bits.pcc_ffwd_0, <variable>.stFmdRtlStatPara.frmPcc.PCC_FFWD
	ldr	r0, [r3, ip]	@ <variable>.VPSS_PDPCCCRSS0.bits.pcc_crss_0, <variable>.VPSS_PDPCCCRSS0.bits.pcc_crss_0
	movw	ip, #4600	@ tmp157,
	str	r0, [r4, #32]	@ <variable>.VPSS_PDPCCCRSS0.bits.pcc_crss_0, <variable>.stFmdRtlStatPara.frmPcc.PCC_CRSS
	add	r0, r4, #332	@, pIfmdTotalHardPara,
	ldr	lr, [r3, r2]	@ <variable>.VPSS_PDPCCFWDTKR0.bits.pcc_fwd_tkr_0, <variable>.VPSS_PDPCCFWDTKR0.bits.pcc_fwd_tkr_0
	mov	r2, #128	@,
	str	lr, [r4, #40]	@ <variable>.VPSS_PDPCCFWDTKR0.bits.pcc_fwd_tkr_0, <variable>.stFmdRtlStatPara.frmPcc.PCC_FWD_TKR
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDPCCBWDTKR0.bits.pcc_bwd_tkr_0, <variable>.VPSS_PDPCCBWDTKR0.bits.pcc_bwd_tkr_0
	movw	ip, #4612	@ tmp159,
	str	lr, [r4, #44]	@ <variable>.VPSS_PDPCCBWDTKR0.bits.pcc_bwd_tkr_0, <variable>.stFmdRtlStatPara.frmPcc.PCC_BWD_TKR
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDPCCBWD1.bits.pcc_bwd_1, <variable>.VPSS_PDPCCBWD1.bits.pcc_bwd_1
	mov	ip, #4608	@ tmp161,
	str	lr, [r4, #228]	@ <variable>.VPSS_PDPCCBWD1.bits.pcc_bwd_1, <variable>.stFmdRtlStatPara.frmPcc2.PCC_BWD
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDPCCFWD1.bits.pcc_fwd_1, <variable>.VPSS_PDPCCFWD1.bits.pcc_fwd_1
	movw	ip, #4604	@ tmp163,
	str	lr, [r4, #224]	@ <variable>.VPSS_PDPCCFWD1.bits.pcc_fwd_1, <variable>.stFmdRtlStatPara.frmPcc2.PCC_FWD
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDPCCFFWD1.bits.pcc_ffwd_1, <variable>.VPSS_PDPCCFFWD1.bits.pcc_ffwd_1
	movw	ip, #4616	@ tmp165,
	str	lr, [r4, #220]	@ <variable>.VPSS_PDPCCFFWD1.bits.pcc_ffwd_1, <variable>.stFmdRtlStatPara.frmPcc2.PCC_FFWD
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDPCCCRSS1.bits.pcc_crss_1, <variable>.VPSS_PDPCCCRSS1.bits.pcc_crss_1
	movw	ip, #4620	@ tmp167,
	str	lr, [r4, #232]	@ <variable>.VPSS_PDPCCCRSS1.bits.pcc_crss_1, <variable>.stFmdRtlStatPara.frmPcc2.PCC_CRSS
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDPCCFWDTKR1.bits.pcc_fwd_tkr_1, <variable>.VPSS_PDPCCFWDTKR1.bits.pcc_fwd_tkr_1
	movw	ip, #4624	@ tmp169,
	str	lr, [r4, #240]	@ <variable>.VPSS_PDPCCFWDTKR1.bits.pcc_fwd_tkr_1, <variable>.stFmdRtlStatPara.frmPcc2.PCC_FWD_TKR
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDPCCBWDTKR1.bits.pcc_bwd_tkr_1, <variable>.VPSS_PDPCCBWDTKR1.bits.pcc_bwd_tkr_1
	movw	ip, #4564	@ tmp171,
	str	lr, [r4, #244]	@ <variable>.VPSS_PDPCCBWDTKR1.bits.pcc_bwd_tkr_1, <variable>.stFmdRtlStatPara.frmPcc2.PCC_BWD_TKR
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDUMMATCH0.bits.match_um, <variable>.VPSS_PDUMMATCH0.bits.match_um
	movw	ip, #4568	@ tmp173,
	str	lr, [r4, #4]	@ <variable>.VPSS_PDUMMATCH0.bits.match_um, <variable>.stFmdRtlStatPara.frmUm.match_UM
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDUMNOMATCH0.bits.nomatch_um, <variable>.VPSS_PDUMNOMATCH0.bits.nomatch_um
	movw	ip, #4572	@ tmp175,
	str	lr, [r4, #8]	@ <variable>.VPSS_PDUMNOMATCH0.bits.nomatch_um, <variable>.stFmdRtlStatPara.frmUm.nonmatch_UM
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDUMMATCH1.bits.match_um, <variable>.VPSS_PDUMMATCH1.bits.match_um
	movw	ip, #4576	@ tmp177,
	str	lr, [r4, #12]	@ <variable>.VPSS_PDUMMATCH1.bits.match_um, <variable>.stFmdRtlStatPara.frmUm.match_UM2
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDUMNOMATCH1.bits.nomatch_um, <variable>.VPSS_PDUMNOMATCH1.bits.nomatch_um
	movw	ip, #4628	@ tmp179,
	str	lr, [r4, #16]	@ <variable>.VPSS_PDUMNOMATCH1.bits.nomatch_um, <variable>.stFmdRtlStatPara.frmUm.nonmatch_UM2
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDLASICNT140.bits.lasi_14_cnt_0, <variable>.VPSS_PDLASICNT140.bits.lasi_14_cnt_0
	movw	ip, #4632	@ tmp181,
	str	lr, [r4, #136]	@ <variable>.VPSS_PDLASICNT140.bits.lasi_14_cnt_0, <variable>.stFmdRtlStatPara.lasiStat.lasiCnt14
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDLASICNT320.bits.lasi_32_cnt_0, <variable>.VPSS_PDLASICNT320.bits.lasi_32_cnt_0
	movw	ip, #4636	@ tmp183,
	str	lr, [r4, #140]	@ <variable>.VPSS_PDLASICNT320.bits.lasi_32_cnt_0, <variable>.stFmdRtlStatPara.lasiStat.lasiCnt32
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDLASICNT340.bits.lasi_34_cnt_0, <variable>.VPSS_PDLASICNT340.bits.lasi_34_cnt_0
	movw	ip, #4640	@ tmp185,
	str	lr, [r4, #144]	@ <variable>.VPSS_PDLASICNT340.bits.lasi_34_cnt_0, <variable>.stFmdRtlStatPara.lasiStat.lasiCnt34
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDLASICNT141.bits.lasi_14_cnt_1, <variable>.VPSS_PDLASICNT141.bits.lasi_14_cnt_1
	movw	ip, #4644	@ tmp187,
	str	lr, [r4, #320]	@ <variable>.VPSS_PDLASICNT141.bits.lasi_14_cnt_1, <variable>.stFmdRtlStatPara.lasiStat2.lasiCnt14
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDLASICNT321.bits.lasi_32_cnt_1, <variable>.VPSS_PDLASICNT321.bits.lasi_32_cnt_1
	movw	ip, #4648	@ tmp189,
	str	lr, [r4, #324]	@ <variable>.VPSS_PDLASICNT321.bits.lasi_32_cnt_1, <variable>.stFmdRtlStatPara.lasiStat2.lasiCnt32
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDLASICNT341.bits.lasi_34_cnt_1, <variable>.VPSS_PDLASICNT341.bits.lasi_34_cnt_1
	movw	ip, #4428	@ tmp191,
	str	lr, [r4, #328]	@ <variable>.VPSS_PDLASICNT341.bits.lasi_34_cnt_1, <variable>.stFmdRtlStatPara.lasiStat2.lasiCnt34
	ldr	lr, [r3, ip]	@ <variable>.VPSS_PDICHD.bits.ichd, <variable>.VPSS_PDICHD.bits.ichd
	movw	ip, #4484	@ tmp193,
	str	lr, [r4, #216]	@ <variable>.VPSS_PDICHD.bits.ichd, <variable>.stFmdRtlStatPara.SceneChangeInfo.iCHD
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4488	@ tmp195,
	str	lr, [r4, #152]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4492	@ tmp197,
	str	lr, [r4, #156]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4496	@ tmp199,
	str	lr, [r4, #160]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4500	@ tmp201,
	str	lr, [r4, #164]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4504	@ tmp203,
	str	lr, [r4, #168]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4508	@ tmp205,
	str	lr, [r4, #172]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4512	@ tmp207,
	str	lr, [r4, #176]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4516	@ tmp209,
	str	lr, [r4, #180]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4520	@ tmp211,
	str	lr, [r4, #184]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4524	@ tmp213,
	str	lr, [r4, #188]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4528	@ tmp215,
	str	lr, [r4, #192]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4532	@ tmp217,
	str	lr, [r4, #196]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4536	@ tmp219,
	str	lr, [r4, #200]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4540	@ tmp221,
	str	lr, [r4, #204]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	mov	ip, #4544	@ tmp223,
	str	lr, [r4, #208]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.bits.stlblk_sad, <variable>.bits.stlblk_sad
	movw	ip, #4380	@ tmp225,
	str	lr, [r4, #212]	@ <variable>.bits.stlblk_sad, <variable>.stFmdRtlStatPara.StillBlkInfo.BlkSad
	ldr	lr, [r3, ip]	@ <variable>.VPSS_DIEMTNNUM0.bits.glbm_num0, <variable>.VPSS_DIEMTNNUM0.bits.glbm_num0
	movw	ip, #4384	@ tmp227,
	str	lr, [r4, #460]	@ <variable>.VPSS_DIEMTNNUM0.bits.glbm_num0, <variable>.stMadRtlStatPara.u32SmallMtnNum
	ldr	lr, [r3, ip]	@ <variable>.VPSS_DIEMTNSUM0.bits.glbm_sum0, <variable>.VPSS_DIEMTNSUM0.bits.glbm_sum0
	movw	ip, #4388	@ tmp229,
	str	lr, [r4, #464]	@ <variable>.VPSS_DIEMTNSUM0.bits.glbm_sum0, <variable>.stMadRtlStatPara.u32SmallMtnSum
	ldr	lr, [r3, ip]	@ <variable>.VPSS_DIEMTNNUM1.bits.glbm_num1, <variable>.VPSS_DIEMTNNUM1.bits.glbm_num1
	movw	ip, #4392	@ tmp231,
	str	lr, [r4, #476]	@ <variable>.VPSS_DIEMTNNUM1.bits.glbm_num1, <variable>.stMadRtlStatPara.u32MidMtnNum0
	ldr	lr, [r3, ip]	@ <variable>.VPSS_DIEMTNSUM1.bits.glbm_sum1, <variable>.VPSS_DIEMTNSUM1.bits.glbm_sum1
	movw	ip, #4396	@ tmp233,
	str	lr, [r4, #480]	@ <variable>.VPSS_DIEMTNSUM1.bits.glbm_sum1, <variable>.stMadRtlStatPara.u32MidMtnSum0
	ldr	lr, [r3, ip]	@ <variable>.VPSS_DIEMTNNUM2.bits.glbm_num2, <variable>.VPSS_DIEMTNNUM2.bits.glbm_num2
	movw	ip, #4400	@ tmp235,
	str	lr, [r4, #484]	@ <variable>.VPSS_DIEMTNNUM2.bits.glbm_num2, <variable>.stMadRtlStatPara.u32MidMtnNum1
	ldr	lr, [r3, ip]	@ <variable>.VPSS_DIEMTNSUM2.bits.glbm_sum2, <variable>.VPSS_DIEMTNSUM2.bits.glbm_sum2
	movw	ip, #4404	@ tmp237,
	str	lr, [r4, #488]	@ <variable>.VPSS_DIEMTNSUM2.bits.glbm_sum2, <variable>.stMadRtlStatPara.u32MidMtnSum1
	ldr	lr, [r3, ip]	@ <variable>.VPSS_DIEMTNNUM3.bits.glbm_num3, <variable>.VPSS_DIEMTNNUM3.bits.glbm_num3
	movw	ip, #4408	@ tmp239,
	str	lr, [r4, #492]	@ <variable>.VPSS_DIEMTNNUM3.bits.glbm_num3, <variable>.stMadRtlStatPara.u32MidMtnNum2
	ldr	lr, [r3, ip]	@ <variable>.VPSS_DIEMTNSUM3.bits.glbm_sum3, <variable>.VPSS_DIEMTNSUM3.bits.glbm_sum3
	movw	ip, #4412	@ tmp241,
	str	lr, [r4, #496]	@ <variable>.VPSS_DIEMTNSUM3.bits.glbm_sum3, <variable>.stMadRtlStatPara.u32MidMtnSum2
	ldr	lr, [r3, ip]	@ <variable>.VPSS_DIEMTNNUM4.bits.glbm_num4, <variable>.VPSS_DIEMTNNUM4.bits.glbm_num4
	mov	ip, #4416	@ tmp243,
	str	lr, [r4, #468]	@ <variable>.VPSS_DIEMTNNUM4.bits.glbm_num4, <variable>.stMadRtlStatPara.u32LargeMtnNum
	ldr	r3, [r3, ip]	@ <variable>.VPSS_DIEMTNSUM4.bits.glbm_sum4, <variable>.VPSS_DIEMTNSUM4.bits.glbm_sum4
	str	r3, [r4, #472]	@ <variable>.VPSS_DIEMTNSUM4.bits.glbm_sum4, <variable>.stMadRtlStatPara.u32LargeMtnSum
	bl	memcpy	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	PQ_HAL_GetIFmdStatInfo, .-PQ_HAL_GetIFmdStatInfo
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.35642, %object
	.size	__func__.35642, 23
__func__.35642:
	.ascii	"PQ_HAL_SetEdgeSmoothEn\000"
	.space	1
	.type	__func__.35626, %object
	.size	__func__.35626, 19
__func__.35626:
	.ascii	"PQ_HAL_SetIFmdInfo\000"
	.space	1
	.type	__func__.35452, %object
	.size	__func__.35452, 21
__func__.35452:
	.ascii	"PQ_HAL_SetIFmdRegist\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"pointer is NULL!\012\000"
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
