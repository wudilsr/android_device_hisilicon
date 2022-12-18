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
	.file	"pq_hal_acm_convert.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_hal_acm_convert)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/hal/hi3798mv100/.pq_hal_acm_convert.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_acm_convert.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_acm_convert.o -O2 -Wall
@ -Wundef -Wstrict-prototypes -Wno-trigraphs
@ -Werror-implicit-function-declaration -Wno-format-security
@ -Wframe-larger-than=1024 -Wdeclaration-after-statement -Wno-pointer-sign
@ -p -fno-strict-aliasing -fno-common -fno-delete-null-pointer-checks
@ -fno-dwarf2-cfi-asm -funwind-tables -fno-stack-protector
@ -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-strict-overflow
@ -fconserve-stack -fverbose-asm
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
	.global	PQ_HAL_AcmCoefConvert
	.type	PQ_HAL_AcmCoefConvert, %function
PQ_HAL_AcmCoefConvert:
	.fnstart
.LFB1393:
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
	cmp	r0, #0	@
	str	r1, [fp, #-52]	@ pstSplitTable_S, %sfp
	str	r0, [fp, #-60]	@, %sfp
	str	r2, [fp, #-56]	@ pstSplitTable_H, %sfp
	beq	.L32	@,
	ldr	r0, [fp, #-52]	@, %sfp
	cmp	r0, #0	@,
	beq	.L33	@,
	ldr	r1, [fp, #-56]	@, %sfp
	cmp	r1, #0	@,
	beq	.L34	@,
	cmp	r3, #0	@ pBitCoef,
	beq	.L35	@,
	ldr	r4, [fp, #-60]	@ ivtmp.675, %sfp
	mov	r5, #0	@ i,
	ldr	ip, [fp, #-56]	@ ivtmp.676, %sfp
	ldr	r0, [fp, #-52]	@ ivtmp.677, %sfp
.L7:
	add	r2, r3, r5, asl #4	@, tmp262, pBitCoef, i,
	ldr	r7, [r4, #0]	@ tmp259,* ivtmp.675
	add	r1, r2, #8	@ tmp323, tmp322,
	add	r5, r5, #1	@ i, i,
	ldrh	sl, [r2, #4]	@,
	cmp	r5, #45	@ i,
	ldrb	r6, [r2, #8]	@ zero_extendqisi2	@,
	bfi	sl, r7, #0, #9	@ tmp264, tmp259,,
	strh	sl, [r2, #4]	@ movhi	@ tmp264,
	ldr	r8, [r4, #4]	@ tmp266,
	ldr	r7, [r2, #4]	@ tmp271,
	bfi	r7, r8, #9, #9	@ tmp271, tmp266,,
	str	r7, [r2, #4]	@ tmp271,
	ldr	sl, [r0, #0]	@ tmp272,* ivtmp.677
	ldrh	r7, [r2, #6]	@,
	bfi	r7, sl, #2, #9	@ tmp277, tmp272,,
	strh	r7, [r2, #6]	@ movhi	@ tmp277,
	ldr	r8, [r0, #4]	@ s32Tmp,
	ldrb	r7, [r2, #7]	@ zero_extendqisi2	@,
	mov	sl, r8, asr #5	@ tmp285, s32Tmp,
	bfi	r7, r8, #3, #5	@ tmp283, s32Tmp,,
	bfi	r6, sl, #0, #4	@ tmp290, tmp285,,
	strb	r7, [r2, #7]	@ tmp283,
	strb	r6, [r2, #8]	@ tmp290,
	ldr	sl, [ip, #0]	@ tmp292,* ivtmp.676
	ldrh	r6, [r2, #8]	@,
	bfi	r6, sl, #4, #7	@ tmp297, tmp292,,
	strh	r6, [r2, #8]	@ movhi	@ tmp297,
	ldr	r7, [ip, #4]	@ tmp299,
	ldr	r8, [r2, #8]	@ tmp304,
	bfi	r8, r7, #11, #7	@ tmp304, tmp299,,
	str	r8, [r2, #8]	@ tmp304,
	ldr	sl, [r4, #8]	@ tmp305,
	ldrh	r6, [r2, #10]	@,
	bfi	r6, sl, #2, #9	@ tmp310, tmp305,,
	strh	r6, [r2, #10]	@ movhi	@ tmp310,
	ldr	r8, [r4, #12]	@ s32Tmp.700,
	add	r4, r4, #16	@ ivtmp.675, ivtmp.675,
	ldrb	r7, [r2, #11]	@ zero_extendqisi2	@,
	bfi	r7, r8, #3, #5	@ tmp316, s32Tmp.700,,
	strb	r7, [r2, #11]	@ tmp316,
	ldrb	r2, [r1, #4]	@ zero_extendqisi2	@,
	mov	sl, r8, asr #5	@ tmp320, s32Tmp.700,
	bfi	r2, sl, #0, #4	@ tmp325, tmp320,,
	strb	r2, [r1, #4]	@ tmp325,
	ldr	r6, [r0, #8]	@ tmp329,
	ldrh	r7, [r1, #4]	@,
	bfi	r7, r6, #4, #9	@ tmp334, tmp329,,
	strh	r7, [r1, #4]	@ movhi	@ tmp334,
	ldr	r8, [r0, #12]	@ tmp338,
	add	r0, r0, #16	@ ivtmp.677, ivtmp.677,
	ldr	sl, [r1, #4]	@ tmp343,
	bfi	sl, r8, #13, #9	@ tmp343, tmp338,,
	str	sl, [r1, #4]	@ tmp343,
	ldr	r2, [ip, #8]	@ tmp346,
	ldrh	r6, [r1, #6]	@,
	ldrb	sl, [r1, #8]	@ zero_extendqisi2	@,
	bfi	r6, r2, #6, #7	@ tmp351, tmp346,,
	strh	r6, [r1, #6]	@ movhi	@ tmp351,
	ldr	r7, [ip, #12]	@ s32Tmp.715,
	add	ip, ip, #16	@ ivtmp.676, ivtmp.676,
	ldrb	r2, [r1, #7]	@ zero_extendqisi2	@,
	mov	r8, r7, asr #3	@ tmp363, s32Tmp.715,
	bfi	r2, r7, #5, #3	@ tmp359, s32Tmp.715,,
	bfi	sl, r8, #0, #4	@ tmp368, tmp363,,
	strb	sl, [r1, #8]	@ tmp368,
	ldr	r6, [r1, #8]	@ tmp376,
	strb	r2, [r1, #7]	@ tmp359,
	bfc	r6, #4, #28	@ tmp376,,
	str	r6, [r1, #8]	@ tmp376,
	bne	.L7	@,
	ldr	ip, [fp, #-60]	@, %sfp
	ldr	r0, [fp, #-56]	@, %sfp
	ldr	r2, [fp, #-52]	@, %sfp
	add	r4, ip, #720	@ ivtmp.653,,
	add	ip, r0, #720	@ ivtmp.654,,
	add	r0, r2, #720	@ ivtmp.655,,
.L8:
	add	r2, r3, r5, asl #4	@, tmp380, pBitCoef, ivtmp.659,
	ldr	r7, [r4, #0]	@ tmp377,* ivtmp.653
	add	r1, r2, #8	@ tmp441, tmp440,
	add	r5, r5, #1	@ ivtmp.659, ivtmp.659,
	ldrh	sl, [r2, #4]	@,
	cmp	r5, #75	@ ivtmp.659,
	ldrb	r6, [r2, #8]	@ zero_extendqisi2	@,
	bfi	sl, r7, #0, #9	@ tmp382, tmp377,,
	strh	sl, [r2, #4]	@ movhi	@ tmp382,
	ldr	r8, [r4, #4]	@ tmp384,
	ldr	r7, [r2, #4]	@ tmp389,
	bfi	r7, r8, #9, #9	@ tmp389, tmp384,,
	str	r7, [r2, #4]	@ tmp389,
	ldr	sl, [r0, #0]	@ tmp390,* ivtmp.655
	ldrh	r7, [r2, #6]	@,
	bfi	r7, sl, #2, #9	@ tmp395, tmp390,,
	strh	r7, [r2, #6]	@ movhi	@ tmp395,
	ldr	r8, [r0, #4]	@ s32Tmp.729,
	ldrb	r7, [r2, #7]	@ zero_extendqisi2	@,
	mov	sl, r8, asr #5	@ tmp403, s32Tmp.729,
	bfi	r7, r8, #3, #5	@ tmp401, s32Tmp.729,,
	bfi	r6, sl, #0, #4	@ tmp408, tmp403,,
	strb	r7, [r2, #7]	@ tmp401,
	strb	r6, [r2, #8]	@ tmp408,
	ldr	r8, [ip, #0]	@ tmp410,* ivtmp.654
	ldrh	sl, [r2, #8]	@,
	bfi	sl, r8, #4, #7	@ tmp415, tmp410,,
	strh	sl, [r2, #8]	@ movhi	@ tmp415,
	ldr	r7, [ip, #4]	@ tmp417,
	ldr	r6, [r2, #8]	@ tmp422,
	bfi	r6, r7, #11, #7	@ tmp422, tmp417,,
	str	r6, [r2, #8]	@ tmp422,
	ldr	r8, [r4, #8]	@ tmp423,
	ldrh	sl, [r2, #10]	@,
	bfi	sl, r8, #2, #9	@ tmp428, tmp423,,
	strh	sl, [r2, #10]	@ movhi	@ tmp428,
	ldr	r6, [r4, #12]	@ s32Tmp.744,
	add	r4, r4, #16	@ ivtmp.653, ivtmp.653,
	ldrb	r7, [r2, #11]	@ zero_extendqisi2	@,
	bfi	r7, r6, #3, #5	@ tmp434, s32Tmp.744,,
	strb	r7, [r2, #11]	@ tmp434,
	ldrb	sl, [r1, #4]	@ zero_extendqisi2	@,
	mov	r8, r6, asr #5	@ tmp438, s32Tmp.744,
	bfi	sl, r8, #0, #4	@ tmp443, tmp438,,
	strb	sl, [r1, #4]	@ tmp443,
	ldr	r2, [r0, #8]	@ tmp447,
	ldrh	r7, [r1, #4]	@,
	bfi	r7, r2, #4, #9	@ tmp452, tmp447,,
	strh	r7, [r1, #4]	@ movhi	@ tmp452,
	ldr	r6, [r0, #12]	@ tmp456,
	add	r0, r0, #16	@ ivtmp.655, ivtmp.655,
	ldr	r8, [r1, #4]	@ tmp461,
	bfi	r8, r6, #13, #9	@ tmp461, tmp456,,
	str	r8, [r1, #4]	@ tmp461,
	ldr	sl, [ip, #8]	@ tmp464,
	ldrh	r2, [r1, #6]	@,
	ldrb	r6, [r1, #8]	@ zero_extendqisi2	@,
	bfi	r2, sl, #6, #7	@ tmp469, tmp464,,
	strh	r2, [r1, #6]	@ movhi	@ tmp469,
	ldr	r7, [ip, #12]	@ s32Tmp.759,
	add	ip, ip, #16	@ ivtmp.654, ivtmp.654,
	ldrb	sl, [r1, #7]	@ zero_extendqisi2	@,
	mov	r8, r7, asr #3	@ tmp481, s32Tmp.759,
	bfi	sl, r7, #5, #3	@ tmp477, s32Tmp.759,,
	bfi	r6, r8, #0, #4	@ tmp486, tmp481,,
	strb	r6, [r1, #8]	@ tmp486,
	ldr	r6, [r1, #8]	@ tmp494,
	strb	sl, [r1, #7]	@ tmp477,
	bfc	r6, #4, #28	@ tmp494,,
	str	r6, [r1, #8]	@ tmp494,
	bne	.L8	@,
	ldr	ip, [fp, #-60]	@, %sfp
	ldr	r0, [fp, #-52]	@, %sfp
	ldr	r4, [fp, #-56]	@, %sfp
	add	r5, ip, #1200	@ stACM_PSCoef$ps16Luma.765,,
	add	r1, r0, #1200	@ stACM_PSCoef$ps16Sat.766,,
	add	r2, r4, #1200	@ stACM_PSCoef$ps16Hue.767,,
	mov	r4, #0	@ i.846,
.L9:
	add	r6, r4, #75	@ D.35523, i.846,
	ldr	r7, [r5, #0]	@ tmp538,* stACM_PSCoef$ps16Luma.765
	add	r4, r4, #1	@ i.846, i.846,
	add	r0, r3, r6, asl #4	@, tmp541, pBitCoef, D.35523,
	cmp	r4, #34	@ i.846,
	add	ip, r0, #8	@ tmp602, tmp601,
	ldrh	sl, [r0, #4]	@,
	ldrb	r6, [r0, #8]	@ zero_extendqisi2	@,
	bfi	sl, r7, #0, #9	@ tmp543, tmp538,,
	strh	sl, [r0, #4]	@ movhi	@ tmp543,
	ldr	r8, [r5, #4]	@ tmp545,
	ldr	r7, [r0, #4]	@ tmp550,
	bfi	r7, r8, #9, #9	@ tmp550, tmp545,,
	str	r7, [r0, #4]	@ tmp550,
	ldr	sl, [r1, #0]	@ tmp551,* stACM_PSCoef$ps16Sat.766
	ldrh	r7, [r0, #6]	@,
	bfi	r7, sl, #2, #9	@ tmp556, tmp551,,
	strh	r7, [r0, #6]	@ movhi	@ tmp556,
	ldr	r8, [r1, #4]	@ s32Tmp.810,
	ldrb	r7, [r0, #7]	@ zero_extendqisi2	@,
	mov	sl, r8, asr #5	@ tmp564, s32Tmp.810,
	bfi	r7, r8, #3, #5	@ tmp562, s32Tmp.810,,
	bfi	r6, sl, #0, #4	@ tmp569, tmp564,,
	strb	r7, [r0, #7]	@ tmp562,
	strb	r6, [r0, #8]	@ tmp569,
	ldr	r7, [r2, #0]	@ tmp571,* stACM_PSCoef$ps16Hue.767
	ldrh	r8, [r0, #8]	@,
	bfi	r8, r7, #4, #7	@ tmp576, tmp571,,
	strh	r8, [r0, #8]	@ movhi	@ tmp576,
	ldr	sl, [r2, #4]	@ tmp578,
	ldr	r6, [r0, #8]	@ tmp583,
	bfi	r6, sl, #11, #7	@ tmp583, tmp578,,
	str	r6, [r0, #8]	@ tmp583,
	ldr	r7, [r5, #8]	@ tmp584,
	ldrh	r8, [r0, #10]	@,
	bfi	r8, r7, #2, #9	@ tmp589, tmp584,,
	strh	r8, [r0, #10]	@ movhi	@ tmp589,
	ldr	r6, [r5, #12]	@ s32Tmp.825,
	add	r5, r5, #16	@ stACM_PSCoef$ps16Luma.765, stACM_PSCoef$ps16Luma.765,
	ldrb	sl, [r0, #11]	@ zero_extendqisi2	@,
	bfi	sl, r6, #3, #5	@ tmp595, s32Tmp.825,,
	strb	sl, [r0, #11]	@ tmp595,
	ldrb	r7, [ip, #4]	@ zero_extendqisi2	@,
	mov	r8, r6, asr #5	@ tmp599, s32Tmp.825,
	bfi	r7, r8, #0, #4	@ tmp604, tmp599,,
	strb	r7, [ip, #4]	@ tmp604,
	ldr	r0, [r1, #8]	@ tmp608,
	ldrh	sl, [ip, #4]	@,
	bfi	sl, r0, #4, #9	@ tmp613, tmp608,,
	strh	sl, [ip, #4]	@ movhi	@ tmp613,
	ldr	r6, [r1, #12]	@ tmp617,
	add	r1, r1, #16	@ stACM_PSCoef$ps16Sat.766, stACM_PSCoef$ps16Sat.766,
	ldr	r8, [ip, #4]	@ tmp622,
	bfi	r8, r6, #13, #9	@ tmp622, tmp617,,
	str	r8, [ip, #4]	@ tmp622,
	ldr	r7, [r2, #8]	@ tmp625,
	ldrh	r0, [ip, #6]	@,
	ldrb	r6, [ip, #8]	@ zero_extendqisi2	@,
	bfi	r0, r7, #6, #7	@ tmp630, tmp625,,
	strh	r0, [ip, #6]	@ movhi	@ tmp630,
	ldr	sl, [r2, #12]	@ s32Tmp.840,
	add	r2, r2, #16	@ stACM_PSCoef$ps16Hue.767, stACM_PSCoef$ps16Hue.767,
	ldrb	r0, [ip, #7]	@ zero_extendqisi2	@,
	mov	r8, sl, asr #3	@ tmp642, s32Tmp.840,
	bfi	r0, sl, #5, #3	@ tmp638, s32Tmp.840,,
	bfi	r6, r8, #0, #4	@ tmp647, tmp642,,
	strb	r6, [ip, #8]	@ tmp647,
	ldr	r7, [ip, #8]	@ tmp655,
	strb	r0, [ip, #7]	@ tmp638,
	bfc	r7, #4, #28	@ tmp655,,
	str	r7, [ip, #8]	@ tmp655,
	beq	.L10	@,
	cmp	r4, #33	@ i.846,
	bne	.L9	@,
	mov	r4, r5	@ D.35491, stACM_PSCoef$ps16Luma.765
	movw	r6, #1732	@ tmp496,
	ldr	r9, [r4], #4	@ tmp495,
	mov	ip, r1	@ D.35496, stACM_PSCoef$ps16Sat.766
	ldrh	sl, [r3, r6]	@,
	movw	r8, #1734	@ tmp502,
	ldrb	r7, [r3, #1736]	@ zero_extendqisi2	@,
	mov	r0, r2	@ D.35506, stACM_PSCoef$ps16Hue.767
	bfi	sl, r9, #0, #9	@ tmp497, tmp495,,
	strh	sl, [r3, r6]	@ movhi	@ tmp497,
	ldr	r9, [r5, #4]	@ tmp499,
	ldr	sl, [r3, #1732]	@ tmp500,
	ldrb	r5, [r3, #1740]	@ zero_extendqisi2	@,
	bfi	sl, r9, #9, #9	@ tmp500, tmp499,,
	str	sl, [r3, #1732]	@ tmp500,
	ldr	r6, [ip], #4	@,
	bfc	r5, #0, #4	@ tmp522,,
	ldrh	sl, [r3, r8]	@,
	movw	r9, #1742	@ tmp530,
	bfi	sl, r6, #2, #9	@ tmp503,,,
	strh	sl, [r3, r8]	@ movhi	@ tmp503,
	ldr	r8, [r1, #4]	@ s32Tmp.778,
	ldrb	r1, [r3, #1735]	@ zero_extendqisi2	@,
	mov	r6, r8, asr #5	@ tmp507, s32Tmp.778,
	bfi	r1, r8, #3, #5	@ tmp505, s32Tmp.778,,
	movw	r8, #1736	@,
	strb	r1, [r3, #1735]	@ tmp505,
	bfi	r7, r6, #0, #4	@ tmp508, tmp507,,
	strb	r7, [r3, #1736]	@ tmp508,
	ldr	sl, [r0], #4	@ tmp510,
	ldrh	r6, [r3, r8]	@,
	bfi	r6, sl, #4, #7	@ tmp512, tmp510,,
	strh	r6, [r3, r8]	@ movhi	@ tmp512,
	ldr	r1, [r2, #4]	@ tmp514,
	movw	r8, #1738	@,
	ldr	r7, [r3, #1736]	@ tmp515,
	bfi	r7, r1, #11, #7	@ tmp515, tmp514,,
	str	r7, [r3, #1736]	@ tmp515,
	ldr	sl, [r4, #4]	@ tmp516,
	movw	r4, #1740	@,
	ldrh	r6, [r3, r8]	@,
	strb	r5, [r3, #1740]	@ tmp522,
	bfi	r6, sl, #2, #9	@ tmp518, tmp516,,
	strh	r6, [r3, r8]	@ movhi	@ tmp518,
	ldrh	r1, [r3, r4]	@,
	mov	r2, r6, lsr #8	@ tmp520, tmp518,
	bfc	r2, #3, #5	@ tmp520,,
	strb	r2, [r3, #1739]	@ tmp520,
	ldr	r5, [ip, #4]	@ tmp524,
	bfi	r1, r5, #4, #9	@ tmp526, tmp524,,
	strh	r1, [r3, r4]	@ movhi	@ tmp526,
	ldr	r7, [r3, #1740]	@ tmp528,
	bfc	r7, #13, #9	@ tmp528,,
	str	r7, [r3, #1740]	@ tmp528,
	ldr	sl, [r0, #4]	@ tmp529,
	ldrh	r8, [r3, r9]	@,
	bfi	r8, sl, #6, #7	@ tmp531, tmp529,,
	strh	r8, [r3, r9]	@ movhi	@ tmp531,
	ldrb	r6, [r3, #1744]	@ zero_extendqisi2	@,
	mov	r2, r8, lsr #8	@ tmp533, tmp531,
	bfc	r6, #0, #4	@ tmp535,,
	strb	r6, [r3, #1744]	@ tmp535,
	ldr	r5, [r3, #1744]	@ tmp537,
	bfc	r2, #5, #3	@ tmp533,,
	strb	r2, [r3, #1743]	@ tmp533,
	bfc	r5, #4, #28	@ tmp537,,
	str	r5, [r3, #1744]	@ tmp537,
.L10:
	ldr	r8, [fp, #-60]	@, %sfp
	ldr	r1, [fp, #-56]	@, %sfp
	ldr	r0, [fp, #-52]	@, %sfp
	add	r4, r8, #1728	@ stACM_PSCoef$ps16Luma,,
	add	r2, r1, #1728	@ stACM_PSCoef$ps16Hue.848,,
	add	r4, r4, #12	@ stACM_PSCoef$ps16Luma, stACM_PSCoef$ps16Luma,
	add	r5, r0, #1728	@ stACM_PSCoef$ps16Sat.847,,
	add	r0, r2, #12	@ stACM_PSCoef$ps16Hue.848, stACM_PSCoef$ps16Hue.848,
	add	ip, r5, #12	@ stACM_PSCoef$ps16Sat.847, stACM_PSCoef$ps16Sat.847,
	mov	r5, #0	@ i.918,
.L12:
	add	r6, r5, #109	@ D.35530, i.918,
	ldr	r7, [r4, #0]	@ tmp681,* stACM_PSCoef$ps16Luma
	add	r5, r5, #1	@ i.918, i.918,
	add	r2, r3, r6, asl #4	@, tmp684, pBitCoef, D.35530,
	cmp	r5, #23	@ i.918,
	add	r1, r2, #8	@ tmp745, tmp744,
	ldrh	sl, [r2, #4]	@,
	ldrb	r6, [r2, #8]	@ zero_extendqisi2	@,
	bfi	sl, r7, #0, #9	@ tmp686, tmp681,,
	strh	sl, [r2, #4]	@ movhi	@ tmp686,
	ldr	r8, [r4, #4]	@ tmp688,
	ldr	r7, [r2, #4]	@ tmp693,
	bfi	r7, r8, #9, #9	@ tmp693, tmp688,,
	str	r7, [r2, #4]	@ tmp693,
	ldr	sl, [ip, #0]	@ tmp694,* stACM_PSCoef$ps16Sat.847
	ldrh	r7, [r2, #6]	@,
	bfi	r7, sl, #2, #9	@ tmp699, tmp694,,
	strh	r7, [r2, #6]	@ movhi	@ tmp699,
	ldr	r8, [ip, #4]	@ s32Tmp.882,
	ldrb	r7, [r2, #7]	@ zero_extendqisi2	@,
	mov	sl, r8, asr #5	@ tmp707, s32Tmp.882,
	bfi	r7, r8, #3, #5	@ tmp705, s32Tmp.882,,
	bfi	r6, sl, #0, #4	@ tmp712, tmp707,,
	strb	r7, [r2, #7]	@ tmp705,
	strb	r6, [r2, #8]	@ tmp712,
	ldr	r8, [r0, #0]	@ tmp714,* stACM_PSCoef$ps16Hue.848
	ldrh	sl, [r2, #8]	@,
	bfi	sl, r8, #4, #7	@ tmp719, tmp714,,
	strh	sl, [r2, #8]	@ movhi	@ tmp719,
	ldr	r7, [r0, #4]	@ tmp721,
	ldr	r6, [r2, #8]	@ tmp726,
	bfi	r6, r7, #11, #7	@ tmp726, tmp721,,
	str	r6, [r2, #8]	@ tmp726,
	ldr	r8, [r4, #8]	@ tmp727,
	ldrh	sl, [r2, #10]	@,
	bfi	sl, r8, #2, #9	@ tmp732, tmp727,,
	strh	sl, [r2, #10]	@ movhi	@ tmp732,
	ldr	r6, [r4, #12]	@ s32Tmp.897,
	add	r4, r4, #16	@ stACM_PSCoef$ps16Luma, stACM_PSCoef$ps16Luma,
	ldrb	r7, [r2, #11]	@ zero_extendqisi2	@,
	bfi	r7, r6, #3, #5	@ tmp738, s32Tmp.897,,
	strb	r7, [r2, #11]	@ tmp738,
	ldrb	r2, [r1, #4]	@ zero_extendqisi2	@,
	mov	r8, r6, asr #5	@ tmp742, s32Tmp.897,
	bfi	r2, r8, #0, #4	@ tmp747, tmp742,,
	strb	r2, [r1, #4]	@ tmp747,
	ldr	sl, [ip, #8]	@ tmp751,
	ldrh	r7, [r1, #4]	@,
	bfi	r7, sl, #4, #9	@ tmp756, tmp751,,
	strh	r7, [r1, #4]	@ movhi	@ tmp756,
	ldr	r6, [ip, #12]	@ tmp760,
	add	ip, ip, #16	@ stACM_PSCoef$ps16Sat.847, stACM_PSCoef$ps16Sat.847,
	ldr	r8, [r1, #4]	@ tmp765,
	bfi	r8, r6, #13, #9	@ tmp765, tmp760,,
	str	r8, [r1, #4]	@ tmp765,
	ldr	r2, [r0, #8]	@ tmp768,
	ldrh	sl, [r1, #6]	@,
	ldrb	r6, [r1, #8]	@ zero_extendqisi2	@,
	bfi	sl, r2, #6, #7	@ tmp773, tmp768,,
	strh	sl, [r1, #6]	@ movhi	@ tmp773,
	ldr	r7, [r0, #12]	@ s32Tmp.912,
	add	r0, r0, #16	@ stACM_PSCoef$ps16Hue.848, stACM_PSCoef$ps16Hue.848,
	ldrb	r2, [r1, #7]	@ zero_extendqisi2	@,
	mov	r8, r7, asr #3	@ tmp785, s32Tmp.912,
	bfi	r2, r7, #5, #3	@ tmp781, s32Tmp.912,,
	bfi	r6, r8, #0, #4	@ tmp790, tmp785,,
	strb	r6, [r1, #8]	@ tmp790,
	ldr	sl, [r1, #8]	@ tmp798,
	strb	r2, [r1, #7]	@ tmp781,
	bfc	sl, #4, #28	@ tmp798,,
	str	sl, [r1, #8]	@ tmp798,
	beq	.L13	@,
	cmp	r5, #22	@ i.918,
	bne	.L12	@,
	movw	r6, #2100	@ tmp660,
	ldr	r8, [r4, #0]	@ tmp659,* stACM_PSCoef$ps16Luma
	ldrh	r7, [r3, r6]	@,
	movw	sl, #2102	@ tmp666,
	ldrb	r1, [r3, #2104]	@ zero_extendqisi2	@,
	movw	r2, #2104	@ tmp675,
	bfi	r7, r8, #0, #9	@ tmp661, tmp659,,
	strh	r7, [r3, r6]	@ movhi	@ tmp661,
	ldr	r5, [r4, #4]	@ tmp663,
	ldr	r8, [r3, #2100]	@ tmp664,
	ldr	r4, [r3, #2112]	@ tmp680,
	bfi	r8, r5, #9, #9	@ tmp664, tmp663,,
	str	r8, [r3, #2100]	@ tmp664,
	ldr	r7, [ip, #0]	@ tmp665,* stACM_PSCoef$ps16Sat.847
	bfc	r4, #4, #28	@ tmp680,,
	ldrh	r6, [r3, sl]	@,
	bfi	r6, r7, #2, #9	@ tmp667, tmp665,,
	strh	r6, [r3, sl]	@ movhi	@ tmp667,
	ldr	r5, [ip, #4]	@ s32Tmp.860,
	ldrb	r8, [r3, #2103]	@ zero_extendqisi2	@,
	mov	sl, r5, asr #5	@ tmp671, s32Tmp.860,
	bfi	r8, r5, #3, #5	@ tmp669, s32Tmp.860,,
	bfi	r1, sl, #0, #4	@ tmp672, tmp671,,
	strb	r8, [r3, #2103]	@ tmp669,
	strb	r1, [r3, #2104]	@ tmp672,
	ldr	ip, [r0, #0]	@ tmp674,* stACM_PSCoef$ps16Hue.848
	ldrh	r6, [r3, r2]	@,
	bfi	r6, ip, #4, #7	@ tmp676, tmp674,,
	strh	r6, [r3, r2]	@ movhi	@ tmp676,
	ldr	r7, [r0, #4]	@ tmp678,
	ldr	sl, [r3, #2104]	@ tmp679,
	str	r4, [r3, #2112]	@ tmp680,
	bfi	sl, r7, #11, #7	@ tmp679, tmp678,,
	str	sl, [r3, #2104]	@ tmp679,
.L13:
	sub	r2, fp, #60
	ldmia	r2, {r2, r5, r8}	@ phole ldm
	add	r0, r5, #2096	@ ivtmp.586,,
	add	r4, r8, #2096	@ ivtmp.582,,
	add	r0, r0, #4	@ ivtmp.586, ivtmp.586,
	add	ip, r2, #2096	@ ivtmp.584,,
	add	r4, r4, #4	@ ivtmp.582, ivtmp.582,
	add	ip, ip, #4	@ ivtmp.584, ivtmp.584,
	mov	r5, #132	@ ivtmp.593,
.L15:
	add	r2, r3, r5, asl #4	@, tmp805, pBitCoef, ivtmp.593,
	ldr	r7, [ip, #0]	@ tmp802,* ivtmp.584
	add	r1, r2, #8	@ tmp866, tmp865,
	add	r5, r5, #1	@ ivtmp.593, ivtmp.593,
	ldrh	sl, [r2, #4]	@,
	cmp	r5, #174	@ ivtmp.593,
	ldrb	r6, [r2, #8]	@ zero_extendqisi2	@,
	bfi	sl, r7, #0, #9	@ tmp807, tmp802,,
	strh	sl, [r2, #4]	@ movhi	@ tmp807,
	ldr	r8, [ip, #4]	@ tmp809,
	ldr	r7, [r2, #4]	@ tmp814,
	bfi	r7, r8, #9, #9	@ tmp814, tmp809,,
	str	r7, [r2, #4]	@ tmp814,
	ldr	sl, [r4, #0]	@ tmp815,* ivtmp.582
	ldrh	r7, [r2, #6]	@,
	bfi	r7, sl, #2, #9	@ tmp820, tmp815,,
	strh	r7, [r2, #6]	@ movhi	@ tmp820,
	ldr	r8, [r4, #4]	@ s32Tmp.931,
	ldrb	r7, [r2, #7]	@ zero_extendqisi2	@,
	mov	sl, r8, asr #5	@ tmp828, s32Tmp.931,
	bfi	r7, r8, #3, #5	@ tmp826, s32Tmp.931,,
	bfi	r6, sl, #0, #4	@ tmp833, tmp828,,
	strb	r7, [r2, #7]	@ tmp826,
	strb	r6, [r2, #8]	@ tmp833,
	ldr	r8, [r0, #0]	@ tmp835,* ivtmp.586
	ldrh	sl, [r2, #8]	@,
	bfi	sl, r8, #4, #7	@ tmp840, tmp835,,
	strh	sl, [r2, #8]	@ movhi	@ tmp840,
	ldr	r7, [r0, #4]	@ tmp842,
	ldr	r6, [r2, #8]	@ tmp847,
	bfi	r6, r7, #11, #7	@ tmp847, tmp842,,
	str	r6, [r2, #8]	@ tmp847,
	ldr	r8, [ip, #8]	@ tmp848,
	ldrh	sl, [r2, #10]	@,
	bfi	sl, r8, #2, #9	@ tmp853, tmp848,,
	strh	sl, [r2, #10]	@ movhi	@ tmp853,
	ldr	r6, [ip, #12]	@ s32Tmp.946,
	add	ip, ip, #16	@ ivtmp.584, ivtmp.584,
	ldrb	r7, [r2, #11]	@ zero_extendqisi2	@,
	bfi	r7, r6, #3, #5	@ tmp859, s32Tmp.946,,
	strb	r7, [r2, #11]	@ tmp859,
	ldrb	r2, [r1, #4]	@ zero_extendqisi2	@,
	mov	r8, r6, asr #5	@ tmp863, s32Tmp.946,
	bfi	r2, r8, #0, #4	@ tmp868, tmp863,,
	strb	r2, [r1, #4]	@ tmp868,
	ldr	sl, [r4, #8]	@ tmp872,
	ldrh	r7, [r1, #4]	@,
	bfi	r7, sl, #4, #9	@ tmp877, tmp872,,
	strh	r7, [r1, #4]	@ movhi	@ tmp877,
	ldr	r6, [r4, #12]	@ tmp881,
	add	r4, r4, #16	@ ivtmp.582, ivtmp.582,
	ldr	r8, [r1, #4]	@ tmp886,
	bfi	r8, r6, #13, #9	@ tmp886, tmp881,,
	str	r8, [r1, #4]	@ tmp886,
	ldr	r2, [r0, #8]	@ tmp889,
	ldrh	sl, [r1, #6]	@,
	ldrb	r6, [r1, #8]	@ zero_extendqisi2	@,
	bfi	sl, r2, #6, #7	@ tmp894, tmp889,,
	strh	sl, [r1, #6]	@ movhi	@ tmp894,
	ldr	r7, [r0, #12]	@ s32Tmp.961,
	add	r0, r0, #16	@ ivtmp.586, ivtmp.586,
	ldrb	r2, [r1, #7]	@ zero_extendqisi2	@,
	mov	r8, r7, asr #3	@ tmp906, s32Tmp.961,
	bfi	r2, r7, #5, #3	@ tmp902, s32Tmp.961,,
	bfi	r6, r8, #0, #4	@ tmp911, tmp906,,
	strb	r6, [r1, #8]	@ tmp911,
	ldr	sl, [r1, #8]	@ tmp919,
	strb	r2, [r1, #7]	@ tmp902,
	bfc	sl, #4, #28	@ tmp919,,
	str	sl, [r1, #8]	@ tmp919,
	bne	.L15	@,
	ldr	r8, [fp, #-52]	@, %sfp
	ldr	r6, [fp, #-60]	@, %sfp
	ldr	r2, [fp, #-56]	@, %sfp
	add	r4, r8, #2768	@ ivtmp.560,,
	add	ip, r6, #2768	@ ivtmp.562,,
	add	r4, r4, #4	@ ivtmp.560, ivtmp.560,
	add	r0, r2, #2768	@ ivtmp.563,,
	add	ip, ip, #4	@ ivtmp.562, ivtmp.562,
	add	r0, r0, #4	@ ivtmp.563, ivtmp.563,
.L16:
	add	r2, r3, r5, asl #4	@, tmp926, pBitCoef, ivtmp.571,
	ldr	r7, [ip, #0]	@ tmp923,* ivtmp.562
	add	r1, r2, #8	@ tmp987, tmp986,
	add	r5, r5, #1	@ ivtmp.571, ivtmp.571,
	ldrh	sl, [r2, #4]	@,
	cmp	r5, #202	@ ivtmp.571,
	ldrb	r6, [r2, #8]	@ zero_extendqisi2	@,
	bfi	sl, r7, #0, #9	@ tmp928, tmp923,,
	strh	sl, [r2, #4]	@ movhi	@ tmp928,
	ldr	r8, [ip, #4]	@ tmp930,
	ldr	r7, [r2, #4]	@ tmp935,
	bfi	r7, r8, #9, #9	@ tmp935, tmp930,,
	str	r7, [r2, #4]	@ tmp935,
	ldr	sl, [r4, #0]	@ tmp936,* ivtmp.560
	ldrh	r7, [r2, #6]	@,
	bfi	r7, sl, #2, #9	@ tmp941, tmp936,,
	strh	r7, [r2, #6]	@ movhi	@ tmp941,
	ldr	r8, [r4, #4]	@ s32Tmp.979,
	ldrb	r7, [r2, #7]	@ zero_extendqisi2	@,
	mov	sl, r8, asr #5	@ tmp949, s32Tmp.979,
	bfi	r7, r8, #3, #5	@ tmp947, s32Tmp.979,,
	bfi	r6, sl, #0, #4	@ tmp954, tmp949,,
	strb	r7, [r2, #7]	@ tmp947,
	strb	r6, [r2, #8]	@ tmp954,
	ldr	r8, [r0, #0]	@ tmp956,* ivtmp.563
	ldrh	sl, [r2, #8]	@,
	bfi	sl, r8, #4, #7	@ tmp961, tmp956,,
	strh	sl, [r2, #8]	@ movhi	@ tmp961,
	ldr	r7, [r0, #4]	@ tmp963,
	ldr	r6, [r2, #8]	@ tmp968,
	bfi	r6, r7, #11, #7	@ tmp968, tmp963,,
	str	r6, [r2, #8]	@ tmp968,
	ldr	r8, [ip, #8]	@ tmp969,
	ldrh	sl, [r2, #10]	@,
	bfi	sl, r8, #2, #9	@ tmp974, tmp969,,
	strh	sl, [r2, #10]	@ movhi	@ tmp974,
	ldr	r6, [ip, #12]	@ s32Tmp.994,
	add	ip, ip, #16	@ ivtmp.562, ivtmp.562,
	ldrb	r7, [r2, #11]	@ zero_extendqisi2	@,
	bfi	r7, r6, #3, #5	@ tmp980, s32Tmp.994,,
	strb	r7, [r2, #11]	@ tmp980,
	ldrb	r2, [r1, #4]	@ zero_extendqisi2	@,
	mov	r8, r6, asr #5	@ tmp984, s32Tmp.994,
	bfi	r2, r8, #0, #4	@ tmp989, tmp984,,
	strb	r2, [r1, #4]	@ tmp989,
	ldr	sl, [r4, #8]	@ tmp993,
	ldrh	r7, [r1, #4]	@,
	bfi	r7, sl, #4, #9	@ tmp998, tmp993,,
	strh	r7, [r1, #4]	@ movhi	@ tmp998,
	ldr	r6, [r4, #12]	@ tmp1002,
	add	r4, r4, #16	@ ivtmp.560, ivtmp.560,
	ldr	r8, [r1, #4]	@ tmp1007,
	bfi	r8, r6, #13, #9	@ tmp1007, tmp1002,,
	str	r8, [r1, #4]	@ tmp1007,
	ldr	r2, [r0, #8]	@ tmp1010,
	ldrh	sl, [r1, #6]	@,
	ldrb	r6, [r1, #8]	@ zero_extendqisi2	@,
	bfi	sl, r2, #6, #7	@ tmp1015, tmp1010,,
	strh	sl, [r1, #6]	@ movhi	@ tmp1015,
	ldr	r7, [r0, #12]	@ s32Tmp.1009,
	add	r0, r0, #16	@ ivtmp.563, ivtmp.563,
	ldrb	r2, [r1, #7]	@ zero_extendqisi2	@,
	mov	r8, r7, asr #3	@ tmp1027, s32Tmp.1009,
	bfi	r2, r7, #5, #3	@ tmp1023, s32Tmp.1009,,
	bfi	r6, r8, #0, #4	@ tmp1032, tmp1027,,
	strb	r6, [r1, #8]	@ tmp1032,
	ldr	sl, [r1, #8]	@ tmp1040,
	strb	r2, [r1, #7]	@ tmp1023,
	bfc	sl, #4, #28	@ tmp1040,,
	str	sl, [r1, #8]	@ tmp1040,
	bne	.L16	@,
	ldr	r4, [fp, #-56]	@, %sfp
	ldr	r6, [fp, #-60]	@, %sfp
	ldr	r2, [fp, #-52]	@, %sfp
	add	r5, r4, #3216	@ stACM_PSCoef$ps16Hue.1017,,
	add	ip, r6, #3216	@ stACM_PSCoef$ps16Luma.1015,,
	add	r0, r2, #3216	@ stACM_PSCoef$ps16Sat.1016,,
	add	r4, ip, #4	@ stACM_PSCoef$ps16Luma.1015, stACM_PSCoef$ps16Luma.1015,
	add	ip, r0, #4	@ stACM_PSCoef$ps16Sat.1016, stACM_PSCoef$ps16Sat.1016,
	add	r0, r5, #4	@ stACM_PSCoef$ps16Hue.1017, stACM_PSCoef$ps16Hue.1017,
	mov	r5, #0	@ i.1075,
.L17:
	add	r6, r5, #202	@ D.35545, i.1075,
	ldr	r7, [r4, #0]	@ tmp1066,* stACM_PSCoef$ps16Luma.1015
	add	r5, r5, #1	@ i.1075, i.1075,
	add	r2, r3, r6, asl #4	@, tmp1069, pBitCoef, D.35545,
	cmp	r5, #32	@ i.1075,
	add	r1, r2, #8	@ tmp1130, tmp1129,
	ldrh	sl, [r2, #4]	@,
	ldrb	r6, [r2, #8]	@ zero_extendqisi2	@,
	bfi	sl, r7, #0, #9	@ tmp1071, tmp1066,,
	strh	sl, [r2, #4]	@ movhi	@ tmp1071,
	ldr	r8, [r4, #4]	@ tmp1073,
	ldr	r7, [r2, #4]	@ tmp1078,
	bfi	r7, r8, #9, #9	@ tmp1078, tmp1073,,
	str	r7, [r2, #4]	@ tmp1078,
	ldr	sl, [ip, #0]	@ tmp1079,* stACM_PSCoef$ps16Sat.1016
	ldrh	r7, [r2, #6]	@,
	bfi	r7, sl, #2, #9	@ tmp1084, tmp1079,,
	strh	r7, [r2, #6]	@ movhi	@ tmp1084,
	ldr	r8, [ip, #4]	@ s32Tmp.1051,
	ldrb	r7, [r2, #7]	@ zero_extendqisi2	@,
	mov	sl, r8, asr #5	@ tmp1092, s32Tmp.1051,
	bfi	r7, r8, #3, #5	@ tmp1090, s32Tmp.1051,,
	bfi	r6, sl, #0, #4	@ tmp1097, tmp1092,,
	strb	r7, [r2, #7]	@ tmp1090,
	strb	r6, [r2, #8]	@ tmp1097,
	ldr	r8, [r0, #0]	@ tmp1099,* stACM_PSCoef$ps16Hue.1017
	ldrh	sl, [r2, #8]	@,
	bfi	sl, r8, #4, #7	@ tmp1104, tmp1099,,
	strh	sl, [r2, #8]	@ movhi	@ tmp1104,
	ldr	r7, [r0, #4]	@ tmp1106,
	ldr	r6, [r2, #8]	@ tmp1111,
	bfi	r6, r7, #11, #7	@ tmp1111, tmp1106,,
	str	r6, [r2, #8]	@ tmp1111,
	ldr	r8, [r4, #8]	@ tmp1112,
	ldrh	sl, [r2, #10]	@,
	bfi	sl, r8, #2, #9	@ tmp1117, tmp1112,,
	strh	sl, [r2, #10]	@ movhi	@ tmp1117,
	ldr	r6, [r4, #12]	@ s32Tmp.1066,
	add	r4, r4, #16	@ stACM_PSCoef$ps16Luma.1015, stACM_PSCoef$ps16Luma.1015,
	ldrb	r7, [r2, #11]	@ zero_extendqisi2	@,
	bfi	r7, r6, #3, #5	@ tmp1123, s32Tmp.1066,,
	strb	r7, [r2, #11]	@ tmp1123,
	ldrb	r2, [r1, #4]	@ zero_extendqisi2	@,
	mov	r8, r6, asr #5	@ tmp1127, s32Tmp.1066,
	bfi	r2, r8, #0, #4	@ tmp1132, tmp1127,,
	strb	r2, [r1, #4]	@ tmp1132,
	ldr	sl, [ip, #8]	@ tmp1136,
	ldrh	r7, [r1, #4]	@,
	bfi	r7, sl, #4, #9	@ tmp1141, tmp1136,,
	strh	r7, [r1, #4]	@ movhi	@ tmp1141,
	ldr	r6, [ip, #12]	@ tmp1145,
	add	ip, ip, #16	@ stACM_PSCoef$ps16Sat.1016, stACM_PSCoef$ps16Sat.1016,
	ldr	r8, [r1, #4]	@ tmp1150,
	bfi	r8, r6, #13, #9	@ tmp1150, tmp1145,,
	str	r8, [r1, #4]	@ tmp1150,
	ldr	r2, [r0, #8]	@ tmp1153,
	ldrh	sl, [r1, #6]	@,
	ldrb	r6, [r1, #8]	@ zero_extendqisi2	@,
	bfi	sl, r2, #6, #7	@ tmp1158, tmp1153,,
	strh	sl, [r1, #6]	@ movhi	@ tmp1158,
	ldr	r7, [r0, #12]	@ s32Tmp.1082,
	add	r0, r0, #16	@ stACM_PSCoef$ps16Hue.1017, stACM_PSCoef$ps16Hue.1017,
	ldrb	r2, [r1, #7]	@ zero_extendqisi2	@,
	mov	r8, r7, asr #3	@ tmp1170, s32Tmp.1082,
	bfi	r2, r7, #5, #3	@ tmp1166, s32Tmp.1082,,
	bfi	r6, r8, #0, #4	@ tmp1175, tmp1170,,
	strb	r6, [r1, #8]	@ tmp1175,
	ldr	sl, [r1, #8]	@ tmp1183,
	strb	r2, [r1, #7]	@ tmp1166,
	bfc	sl, #4, #28	@ tmp1183,,
	str	sl, [r1, #8]	@ tmp1183,
	beq	.L18	@,
	cmp	r5, #31	@ i.1075,
	bne	.L17	@,
	movw	r6, #3732	@ tmp1045,
	ldr	r8, [r4, #0]	@ tmp1044,* stACM_PSCoef$ps16Luma.1015
	ldrh	r7, [r3, r6]	@,
	movw	r1, #3734	@ tmp1051,
	ldrb	sl, [r3, #3736]	@ zero_extendqisi2	@,
	movw	r2, #3736	@ tmp1060,
	bfi	r7, r8, #0, #9	@ tmp1046, tmp1044,,
	strh	r7, [r3, r6]	@ movhi	@ tmp1046,
	ldr	r5, [r4, #4]	@ tmp1048,
	ldr	r6, [r3, #3732]	@ tmp1049,
	ldr	r4, [r3, #3744]	@ tmp1065,
	bfi	r6, r5, #9, #9	@ tmp1049, tmp1048,,
	str	r6, [r3, #3732]	@ tmp1049,
	ldr	r7, [ip, #0]	@ tmp1050,* stACM_PSCoef$ps16Sat.1016
	bfc	r4, #4, #28	@ tmp1065,,
	ldrh	r8, [r3, r1]	@,
	bfi	r8, r7, #2, #9	@ tmp1052, tmp1050,,
	strh	r8, [r3, r1]	@ movhi	@ tmp1052,
	ldr	r5, [ip, #4]	@ s32Tmp.1029,
	ldrb	ip, [r3, #3735]	@ zero_extendqisi2	@,
	mov	r6, r5, asr #5	@ tmp1056, s32Tmp.1029,
	bfi	ip, r5, #3, #5	@ tmp1054, s32Tmp.1029,,
	bfi	sl, r6, #0, #4	@ tmp1057, tmp1056,,
	strb	ip, [r3, #3735]	@ tmp1054,
	strb	sl, [r3, #3736]	@ tmp1057,
	ldr	r1, [r0, #0]	@ tmp1059,* stACM_PSCoef$ps16Hue.1017
	ldrh	r7, [r3, r2]	@,
	bfi	r7, r1, #4, #7	@ tmp1061, tmp1059,,
	strh	r7, [r3, r2]	@ movhi	@ tmp1061,
	ldr	sl, [r0, #4]	@ tmp1063,
	ldr	r8, [r3, #3736]	@ tmp1064,
	str	r4, [r3, #3744]	@ tmp1065,
	bfi	r8, sl, #11, #7	@ tmp1064, tmp1063,,
	str	r8, [r3, #3736]	@ tmp1064,
.L18:
	sub	r2, fp, #60
	ldmia	r2, {r2, r5, r8}	@ phole ldm
	add	r0, r5, #3712	@ ivtmp.520,,
	add	r4, r8, #3712	@ ivtmp.515,,
	add	r0, r0, #12	@ ivtmp.520, ivtmp.520,
	add	ip, r2, #3712	@ ivtmp.517,,
	add	r4, r4, #12	@ ivtmp.515, ivtmp.515,
	add	ip, ip, #12	@ ivtmp.517, ivtmp.517,
	mov	r5, #234	@ ivtmp.526,
.L20:
	add	r2, r3, r5, asl #4	@, tmp1190, pBitCoef, ivtmp.526,
	ldr	sl, [ip, #0]	@ tmp1187,* ivtmp.517
	add	r1, r2, #8	@ tmp1251, tmp1250,
	add	r5, r5, #1	@ ivtmp.526, ivtmp.526,
	ldrh	r7, [r2, #4]	@,
	cmp	r5, #255	@ ivtmp.526,
	ldrb	r6, [r2, #8]	@ zero_extendqisi2	@,
	bfi	r7, sl, #0, #9	@ tmp1192, tmp1187,,
	strh	r7, [r2, #4]	@ movhi	@ tmp1192,
	ldr	r8, [ip, #4]	@ tmp1194,
	ldr	sl, [r2, #4]	@ tmp1199,
	bfi	sl, r8, #9, #9	@ tmp1199, tmp1194,,
	str	sl, [r2, #4]	@ tmp1199,
	ldr	r7, [r4, #0]	@ tmp1200,* ivtmp.515
	ldrh	sl, [r2, #6]	@,
	bfi	sl, r7, #2, #9	@ tmp1205, tmp1200,,
	strh	sl, [r2, #6]	@ movhi	@ tmp1205,
	ldr	r8, [r4, #4]	@ s32Tmp.1100,
	ldrb	r7, [r2, #7]	@ zero_extendqisi2	@,
	mov	sl, r8, asr #5	@ tmp1213, s32Tmp.1100,
	bfi	r7, r8, #3, #5	@ tmp1211, s32Tmp.1100,,
	bfi	r6, sl, #0, #4	@ tmp1218, tmp1213,,
	strb	r7, [r2, #7]	@ tmp1211,
	strb	r6, [r2, #8]	@ tmp1218,
	ldr	r8, [r0, #0]	@ tmp1220,* ivtmp.520
	ldrh	r6, [r2, #8]	@,
	bfi	r6, r8, #4, #7	@ tmp1225, tmp1220,,
	strh	r6, [r2, #8]	@ movhi	@ tmp1225,
	ldr	r7, [r0, #4]	@ tmp1227,
	ldr	r8, [r2, #8]	@ tmp1232,
	bfi	r8, r7, #11, #7	@ tmp1232, tmp1227,,
	str	r8, [r2, #8]	@ tmp1232,
	ldr	r6, [ip, #8]	@ tmp1233,
	ldrh	r8, [r2, #10]	@,
	bfi	r8, r6, #2, #9	@ tmp1238, tmp1233,,
	strh	r8, [r2, #10]	@ movhi	@ tmp1238,
	ldr	r6, [ip, #12]	@ s32Tmp.1115,
	add	ip, ip, #16	@ ivtmp.517, ivtmp.517,
	ldrb	r7, [r2, #11]	@ zero_extendqisi2	@,
	bfi	r7, r6, #3, #5	@ tmp1244, s32Tmp.1115,,
	strb	r7, [r2, #11]	@ tmp1244,
	ldrb	r8, [r1, #4]	@ zero_extendqisi2	@,
	mov	r2, r6, asr #5	@ tmp1248, s32Tmp.1115,
	bfi	r8, r2, #0, #4	@ tmp1253, tmp1248,,
	strb	r8, [r1, #4]	@ tmp1253,
	ldr	r6, [r4, #8]	@ tmp1257,
	ldrh	r7, [r1, #4]	@,
	bfi	r7, r6, #4, #9	@ tmp1262, tmp1257,,
	strh	r7, [r1, #4]	@ movhi	@ tmp1262,
	ldr	r2, [r4, #12]	@ tmp1266,
	add	r4, r4, #16	@ ivtmp.515, ivtmp.515,
	ldr	r8, [r1, #4]	@ tmp1271,
	bfi	r8, r2, #13, #9	@ tmp1271, tmp1266,,
	str	r8, [r1, #4]	@ tmp1271,
	ldr	r7, [r0, #8]	@ tmp1274,
	ldrh	r6, [r1, #6]	@,
	ldrb	r2, [r1, #8]	@ zero_extendqisi2	@,
	bfi	r6, r7, #6, #7	@ tmp1279, tmp1274,,
	strh	r6, [r1, #6]	@ movhi	@ tmp1279,
	ldr	r7, [r0, #12]	@ s32Tmp.1130,
	add	r0, r0, #16	@ ivtmp.520, ivtmp.520,
	ldrb	r6, [r1, #7]	@ zero_extendqisi2	@,
	mov	r8, r7, asr #3	@ tmp1291, s32Tmp.1130,
	bfi	r6, r7, #5, #3	@ tmp1287, s32Tmp.1130,,
	bfi	r2, r8, #0, #4	@ tmp1296, tmp1291,,
	strb	r2, [r1, #8]	@ tmp1296,
	ldr	r2, [r1, #8]	@ tmp1304,
	strb	r6, [r1, #7]	@ tmp1287,
	bfc	r2, #4, #28	@ tmp1304,,
	str	r2, [r1, #8]	@ tmp1304,
	bne	.L20	@,
	mov	r0, #0	@ D.35479,
	mov	ip, #4080	@ tmp1305,
	str	ip, [r3, #0]	@ tmp1305, <variable>.u32Size
.L3:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L32:
	movw	r2, #:lower16:.LANCHOR0	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	mov	r3, #146	@,
.L30:
	movw	ip, #:lower16:.LC0	@ tmp254,
	movt	ip, #:upper16:.LC0	@ tmp254,
	str	ip, [sp, #0]	@ tmp254,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35479,
	b	.L3	@
.L33:
	movw	r2, #:lower16:.LANCHOR0	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	mov	r3, #147	@,
	b	.L30	@
.L34:
	movw	r2, #:lower16:.LANCHOR0	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	mov	r3, #148	@,
	b	.L30	@
.L35:
	movw	r2, #:lower16:.LANCHOR0	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	mov	r3, #149	@,
	b	.L30	@
	.fnend
	.size	PQ_HAL_AcmCoefConvert, .-PQ_HAL_AcmCoefConvert
	.align	2
	.global	PQ_HAL_Split_Table
	.type	PQ_HAL_Split_Table, %function
PQ_HAL_Split_Table:
	.fnstart
.LFB1392:
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #84
	sub	sp, sp, #84	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r1, #0	@ pSplitTbl
	str	r0, [fp, #-92]	@ ps16OriLUT, %sfp
	beq	.L98	@,
	ldr	sl, [fp, #-92]	@, %sfp
	add	r8, r1, #1728	@, pSplitTbl,
	add	r7, r1, #2096	@, pSplitTbl,
	str	r8, [fp, #-72]	@, %sfp
	str	r7, [fp, #-68]	@, %sfp
	add	r5, r1, #3216	@, pSplitTbl,
	ldr	r2, [fp, #-92]	@, %sfp
	add	r9, sl, #1616	@,,
	str	r5, [fp, #-60]	@, %sfp
	add	r4, r1, #3712	@, pSplitTbl,
	ldr	r0, [fp, #-92]	@, %sfp
	add	r6, r1, #2768	@, pSplitTbl,
	str	r4, [fp, #-56]	@, %sfp
	add	r3, r2, #1216	@,,
	ldr	sl, [fp, #-72]	@, %sfp
	add	ip, r0, #404	@,,
	ldr	r8, [fp, #-68]	@, %sfp
	ldr	r4, [fp, #-60]	@, %sfp
	str	r9, [fp, #-96]	@, %sfp
	add	r7, r8, #4	@,,
	str	r3, [fp, #-104]	@, %sfp
	add	r9, sl, #12	@,,
	str	ip, [fp, #-100]	@, %sfp
	add	r2, r4, #4	@,,
	str	r6, [fp, #-64]	@, %sfp
	add	r4, r1, #720	@, pSplitTbl,
	ldr	r6, [fp, #-64]	@, %sfp
	ldr	r3, [fp, #-56]	@, %sfp
	ldr	ip, [fp, #-96]	@, %sfp
	add	r5, r6, #4	@,,
	str	r1, [fp, #-52]	@ pSplitTbl, %sfp
	add	r0, r3, #12	@,,
	str	r9, [fp, #-72]	@, %sfp
	add	sl, ip, #8	@,,
	ldr	r9, [fp, #-104]	@, %sfp
	mov	r3, #0	@,
	str	r7, [fp, #-68]	@, %sfp
	str	r2, [fp, #-60]	@, %sfp
	add	r2, r1, #1200	@, pSplitTbl,
	ldr	r7, [fp, #-100]	@, %sfp
	add	r8, r9, #2	@,,
	ldr	r1, [fp, #-92]	@, %sfp
	str	r5, [fp, #-64]	@, %sfp
	add	r6, r7, #2	@,,
	str	r0, [fp, #-56]	@, %sfp
	movw	r5, #:lower16:.LC2	@,
	str	sl, [fp, #-96]	@, %sfp
	movt	r5, #:upper16:.LC2	@,
	str	r8, [fp, #-104]	@, %sfp
	add	r0, r1, #812	@,,
	str	r6, [fp, #-100]	@, %sfp
	str	r5, [fp, #-112]	@, %sfp
	str	r4, [fp, #-80]	@, %sfp
	str	r2, [fp, #-76]	@, %sfp
	str	r3, [fp, #-84]	@, %sfp
	str	r0, [fp, #-108]	@, %sfp
.L39:
	ldr	r6, [fp, #-84]	@, %sfp
	ldr	r7, [fp, #-100]	@, %sfp
	and	r3, r6, #1	@ pretmp.1201,,
	ldr	sl, [fp, #-92]	@, %sfp
	ldr	r9, [fp, #-104]	@, %sfp
	mov	r5, r6, asl #1	@ tmp257,,
	ldr	ip, [fp, #-96]	@, %sfp
	add	r6, r7, r5	@ ivtmp.1174,, tmp257
	ldr	r4, [fp, #-108]	@, %sfp
	mov	r8, r3, asl #2	@, pretmp.1201,
	add	r7, ip, r5	@ ivtmp.1169,, tmp257
	str	r8, [fp, #-48]	@, %sfp
	add	r8, sl, r5	@ ivtmp.1171,, tmp257
	add	sl, r9, r5	@ ivtmp.1172,, tmp257
	add	r9, r4, r5	@ ivtmp.1173,, tmp257
	mov	r5, #0	@ j,
.L96:
	and	r4, r5, #1	@ pretmp.1203, j,
	ldr	ip, [fp, #-48]	@, %sfp
	add	r4, ip, r4, asl #1	@, pretmp.1149,, pretmp.1203,
	cmp	r4, #7	@ pretmp.1149,
	ldrls	pc, [pc, r4, asl #2]	@ pretmp.1149
	b	.L51	@
.L60:
	.word	.L52
	.word	.L53
	.word	.L54
	.word	.L55
	.word	.L56
	.word	.L57
	.word	.L58
	.word	.L59
.L59:
	ldrsh	r1, [r8, #0]	@ tmp214,* ivtmp.1171
	add	ip, r4, #1	@ D.35432, pretmp.1149,
	ldr	r2, [fp, #-56]	@, %sfp
	movw	r3, #:lower16:.LC2	@,
	movt	r3, #:upper16:.LC2	@,
	str	r3, [fp, #-88]	@, %sfp
	str	r1, [r2], #4	@ tmp214,
	str	r2, [fp, #-56]	@, %sfp
.L61:
	ldr	lr, [fp, #-88]	@, %sfp
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L99	@,
	mov	r3, #128	@,
	str	ip, [fp, #-116]	@,
	str	lr, [sp, #0]	@,
	bl	HI_LogOut	@
	ldr	ip, [fp, #-116]	@,
.L71:
	cmp	r4, #7	@ pretmp.1149,
	ldrls	pc, [pc, r4, asl #2]	@ pretmp.1149
	b	.L72	@
.L81:
	.word	.L73
	.word	.L74
	.word	.L75
	.word	.L76
	.word	.L77
	.word	.L78
	.word	.L79
	.word	.L80
.L80:
	ldrsh	r3, [r9, #0]	@ tmp236,* ivtmp.1173
	ldr	r1, [fp, #-56]	@, %sfp
	str	r3, [r1], #4	@ tmp236,
	str	r1, [fp, #-56]	@, %sfp
.L82:
	cmp	ip, #7	@ D.35432,
	ldrls	pc, [pc, ip, asl #2]	@ D.35432
	b	.L83	@
.L92:
	.word	.L84
	.word	.L85
	.word	.L86
	.word	.L87
	.word	.L88
	.word	.L89
	.word	.L90
	.word	.L91
.L91:
	ldrsh	r3, [sl, #0]	@ tmp247,* ivtmp.1172
	ldr	r1, [fp, #-56]	@, %sfp
	str	r3, [r1], #4	@ tmp247,
	str	r1, [fp, #-56]	@, %sfp
.L93:
	cmp	r4, #7	@ pretmp.1149,
	ldrls	pc, [pc, r4, asl #2]	@ pretmp.1149
	b	.L49	@
.L94:
	.word	.L40
	.word	.L42
	.word	.L43
	.word	.L44
	.word	.L45
	.word	.L46
	.word	.L47
	.word	.L48
.L48:
	ldrsh	r3, [r7, #0]	@ tmp207,* ivtmp.1169
	ldr	r1, [fp, #-56]	@, %sfp
	str	r3, [r1], #4	@ tmp207,
	str	r1, [fp, #-56]	@, %sfp
.L41:
	add	r5, r5, #1	@ j, j,
	add	r7, r7, #58	@ ivtmp.1169, ivtmp.1169,
	cmp	r5, #7	@ j,
	add	r8, r8, #58	@ ivtmp.1171, ivtmp.1171,
	add	sl, sl, #58	@ ivtmp.1172, ivtmp.1172,
	add	r9, r9, #58	@ ivtmp.1173, ivtmp.1173,
	add	r6, r6, #58	@ ivtmp.1174, ivtmp.1174,
	bne	.L96	@,
	ldr	r2, [fp, #-84]	@, %sfp
	add	r0, r2, #1	@,,
	str	r0, [fp, #-84]	@, %sfp
	cmp	r0, #29	@,
	bne	.L39	@,
	mov	r0, #0	@ D.35425,
.L38:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L47:
	ldrsh	r2, [r7, #0]	@ tmp206,* ivtmp.1169
	ldr	r0, [fp, #-60]	@, %sfp
	str	r2, [r0], #4	@ tmp206,
	str	r0, [fp, #-60]	@, %sfp
	b	.L41	@
.L79:
	ldrsh	r2, [r9, #0]	@ tmp237,* ivtmp.1173
	ldr	r0, [fp, #-60]	@, %sfp
	str	r2, [r0], #4	@ tmp237,
	str	r0, [fp, #-60]	@, %sfp
	b	.L82	@
.L78:
	ldrsh	r3, [r9, #0]	@ tmp238,* ivtmp.1173
	ldr	r1, [fp, #-64]	@, %sfp
	str	r3, [r1], #4	@ tmp238,
	str	r1, [fp, #-64]	@, %sfp
	b	.L82	@
.L77:
	ldrsh	r2, [r9, #0]	@ tmp239,* ivtmp.1173
	ldr	r0, [fp, #-68]	@, %sfp
	str	r2, [r0], #4	@ tmp239,
	str	r0, [fp, #-68]	@, %sfp
	b	.L82	@
.L76:
	ldrsh	r3, [r9, #0]	@ tmp240,* ivtmp.1173
	ldr	r1, [fp, #-72]	@, %sfp
	str	r3, [r1], #4	@ tmp240,
	str	r1, [fp, #-72]	@, %sfp
	b	.L82	@
.L75:
	ldrsh	r2, [r9, #0]	@ tmp241,* ivtmp.1173
	ldr	r0, [fp, #-76]	@, %sfp
	str	r2, [r0], #4	@ tmp241,
	str	r0, [fp, #-76]	@, %sfp
	b	.L82	@
.L74:
	ldrsh	r3, [r9, #0]	@ tmp242,* ivtmp.1173
	ldr	r1, [fp, #-80]	@, %sfp
	str	r3, [r1], #4	@ tmp242,
	str	r1, [fp, #-80]	@, %sfp
	b	.L82	@
.L73:
	ldrsh	r2, [r9, #0]	@ tmp243,* ivtmp.1173
	ldr	r0, [fp, #-52]	@, %sfp
	str	r2, [r0], #4	@ tmp243,
	str	r0, [fp, #-52]	@, %sfp
	b	.L82	@
.L58:
	ldrsh	r2, [r8, #0]	@ tmp215,* ivtmp.1171
	add	ip, r4, #1	@ D.35432, pretmp.1149,
	ldr	r0, [fp, #-60]	@, %sfp
	str	r2, [r0], #4	@ tmp215,
	str	r0, [fp, #-60]	@, %sfp
.L69:
	ldrsh	r3, [r6, #0]	@ tmp225,* ivtmp.1174
	ldr	r1, [fp, #-56]	@, %sfp
	str	r3, [r1], #4	@ tmp225,
	str	r1, [fp, #-56]	@, %sfp
	b	.L71	@
.L57:
	ldrsh	r3, [r8, #0]	@ tmp216,* ivtmp.1171
	add	ip, r4, #1	@ D.35432, pretmp.1149,
	ldr	r1, [fp, #-64]	@, %sfp
	str	r3, [r1], #4	@ tmp216,
	str	r1, [fp, #-64]	@, %sfp
.L68:
	ldrsh	r2, [r6, #0]	@ tmp226,* ivtmp.1174
	ldr	r0, [fp, #-60]	@, %sfp
	str	r2, [r0], #4	@ tmp226,
	str	r0, [fp, #-60]	@, %sfp
	b	.L71	@
.L56:
	ldrsh	r2, [r8, #0]	@ tmp217,* ivtmp.1171
	add	ip, r4, #1	@ D.35432, pretmp.1149,
	ldr	r0, [fp, #-68]	@, %sfp
	str	r2, [r0], #4	@ tmp217,
	str	r0, [fp, #-68]	@, %sfp
.L67:
	ldrsh	r3, [r6, #0]	@ tmp227,* ivtmp.1174
	ldr	r1, [fp, #-64]	@, %sfp
	str	r3, [r1], #4	@ tmp227,
	str	r1, [fp, #-64]	@, %sfp
	b	.L71	@
.L55:
	ldrsh	r3, [r8, #0]	@ tmp218,* ivtmp.1171
	add	ip, r4, #1	@ D.35432, pretmp.1149,
	ldr	r1, [fp, #-72]	@, %sfp
	str	r3, [r1], #4	@ tmp218,
	str	r1, [fp, #-72]	@, %sfp
.L66:
	ldrsh	r2, [r6, #0]	@ tmp228,* ivtmp.1174
	ldr	r0, [fp, #-68]	@, %sfp
	str	r2, [r0], #4	@ tmp228,
	str	r0, [fp, #-68]	@, %sfp
	b	.L71	@
.L54:
	ldrsh	r2, [r8, #0]	@ tmp219,* ivtmp.1171
	add	ip, r4, #1	@ D.35432, pretmp.1149,
	ldr	r0, [fp, #-76]	@, %sfp
	str	r2, [r0], #4	@ tmp219,
	str	r0, [fp, #-76]	@, %sfp
.L65:
	ldrsh	r3, [r6, #0]	@ tmp229,* ivtmp.1174
	ldr	r1, [fp, #-72]	@, %sfp
	str	r3, [r1], #4	@ tmp229,
	str	r1, [fp, #-72]	@, %sfp
	b	.L71	@
.L53:
	ldrsh	r3, [r8, #0]	@ tmp220,* ivtmp.1171
	add	ip, r4, #1	@ D.35432, pretmp.1149,
	ldr	r1, [fp, #-80]	@, %sfp
	str	r3, [r1], #4	@ tmp220,
	str	r1, [fp, #-80]	@, %sfp
.L64:
	ldrsh	r2, [r6, #0]	@ tmp230,* ivtmp.1174
	ldr	r0, [fp, #-76]	@, %sfp
	str	r2, [r0], #4	@ tmp230,
	str	r0, [fp, #-76]	@, %sfp
	b	.L71	@
.L52:
	ldrsh	r2, [r8, #0]	@ tmp221,* ivtmp.1171
	add	ip, r4, #1	@ D.35432, pretmp.1149,
	ldr	r0, [fp, #-52]	@, %sfp
	str	r2, [r0], #4	@ tmp221,
	str	r0, [fp, #-52]	@, %sfp
.L63:
	ldrsh	r3, [r6, #0]	@ tmp231,* ivtmp.1174
	ldr	r1, [fp, #-80]	@, %sfp
	str	r3, [r1], #4	@ tmp231,
	str	r1, [fp, #-80]	@, %sfp
	b	.L71	@
.L90:
	ldrsh	r2, [sl, #0]	@ tmp248,* ivtmp.1172
	ldr	r0, [fp, #-60]	@, %sfp
	str	r2, [r0], #4	@ tmp248,
	str	r0, [fp, #-60]	@, %sfp
	b	.L93	@
.L89:
	ldrsh	r1, [sl, #0]	@ tmp249,* ivtmp.1172
	ldr	ip, [fp, #-64]	@, %sfp
	str	r1, [ip], #4	@ tmp249,
	str	ip, [fp, #-64]	@, %sfp
	b	.L93	@
.L88:
	ldrsh	r3, [sl, #0]	@ tmp250,* ivtmp.1172
	ldr	r0, [fp, #-68]	@, %sfp
	str	r3, [r0], #4	@ tmp250,
	str	r0, [fp, #-68]	@, %sfp
	b	.L93	@
.L87:
	ldrsh	ip, [sl, #0]	@ tmp251,* ivtmp.1172
	ldr	r2, [fp, #-72]	@, %sfp
	str	ip, [r2], #4	@ tmp251,
	str	r2, [fp, #-72]	@, %sfp
	b	.L93	@
.L86:
	ldrsh	r0, [sl, #0]	@ tmp252,* ivtmp.1172
	ldr	r1, [fp, #-76]	@, %sfp
	str	r0, [r1], #4	@ tmp252,
	str	r1, [fp, #-76]	@, %sfp
	b	.L93	@
.L85:
	ldrsh	r3, [sl, #0]	@ tmp253,* ivtmp.1172
	ldr	r2, [fp, #-80]	@, %sfp
	str	r3, [r2], #4	@ tmp253,
	str	r2, [fp, #-80]	@, %sfp
	b	.L93	@
.L84:
	ldrsh	r1, [sl, #0]	@ tmp254,* ivtmp.1172
	ldr	ip, [fp, #-52]	@, %sfp
	str	r1, [ip], #4	@ tmp254,
	str	ip, [fp, #-52]	@, %sfp
	b	.L93	@
.L43:
	ldrsh	r1, [r7, #0]	@ tmp202,* ivtmp.1169
	ldr	r2, [fp, #-76]	@, %sfp
	str	r1, [r2], #4	@ tmp202,
	str	r2, [fp, #-76]	@, %sfp
	b	.L41	@
.L42:
	ldrsh	r3, [r7, #0]	@ tmp201,* ivtmp.1169
	ldr	r0, [fp, #-80]	@, %sfp
	str	r3, [r0], #4	@ tmp201,
	str	r0, [fp, #-80]	@, %sfp
	b	.L41	@
.L40:
	ldrsh	ip, [r7, #0]	@ tmp200,* ivtmp.1169
	ldr	r1, [fp, #-52]	@, %sfp
	str	ip, [r1], #4	@ tmp200,
	str	r1, [fp, #-52]	@, %sfp
	b	.L41	@
.L45:
	ldrsh	r3, [r7, #0]	@ tmp204,* ivtmp.1169
	ldr	r2, [fp, #-68]	@, %sfp
	str	r3, [r2], #4	@ tmp204,
	str	r2, [fp, #-68]	@, %sfp
	b	.L41	@
.L44:
	ldrsh	r0, [r7, #0]	@ tmp203,* ivtmp.1169
	ldr	ip, [fp, #-72]	@, %sfp
	str	r0, [ip], #4	@ tmp203,
	str	ip, [fp, #-72]	@, %sfp
	b	.L41	@
.L46:
	ldrsh	ip, [r7, #0]	@ tmp205,* ivtmp.1169
	ldr	r1, [fp, #-64]	@, %sfp
	str	ip, [r1], #4	@ tmp205,
	str	r1, [fp, #-64]	@, %sfp
	b	.L41	@
.L83:
	ldr	ip, [fp, #-112]	@, %sfp
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L99	@,
	mov	r3, #128	@,
	str	ip, [sp, #0]	@,
	bl	HI_LogOut	@
	b	.L93	@
.L49:
	ldr	lr, [fp, #-112]	@, %sfp
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L99	@,
	mov	r3, #128	@,
	str	lr, [sp, #0]	@,
	bl	HI_LogOut	@
	b	.L41	@
.L72:
	ldr	lr, [fp, #-112]	@, %sfp
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L99	@,
	mov	r3, #128	@,
	str	ip, [fp, #-116]	@,
	str	lr, [sp, #0]	@,
	bl	HI_LogOut	@
	ldr	ip, [fp, #-116]	@,
	b	.L82	@
.L51:
	ldr	lr, [fp, #-112]	@, %sfp
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L99	@,
	mov	r3, #128	@,
	add	ip, r4, r0	@ D.35432, pretmp.1149,
	str	lr, [sp, #0]	@,
	str	ip, [fp, #-116]	@,
	bl	HI_LogOut	@
	ldr	ip, [fp, #-116]	@,
	movw	r0, #:lower16:.LC2	@,
	movt	r0, #:upper16:.LC2	@,
	str	r0, [fp, #-88]	@, %sfp
	cmp	ip, #7	@ D.35432,
	ldrls	pc, [pc, ip, asl #2]	@ D.35432
	b	.L61	@
.L70:
	.word	.L62
	.word	.L63
	.word	.L64
	.word	.L65
	.word	.L66
	.word	.L67
	.word	.L68
	.word	.L69
.L62:
	ldrsh	r2, [r6, #0]	@ tmp232,* ivtmp.1174
	ldr	r0, [fp, #-52]	@, %sfp
	str	r2, [r0], #4	@ tmp232,
	str	r0, [fp, #-52]	@, %sfp
	b	.L71	@
.L98:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L99	@,
	mov	r3, #75	@,
	movw	ip, #:lower16:.LC1	@ tmp194,
	movt	ip, #:upper16:.LC1	@ tmp194,
	str	ip, [sp, #0]	@ tmp194,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35425,
	b	.L38	@
.L100:
	.align	2
.L99:
	.word	.LANCHOR0+24
	.fnend
	.size	PQ_HAL_Split_Table, .-PQ_HAL_Split_Table
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.35452, %object
	.size	__func__.35452, 22
__func__.35452:
	.ascii	"PQ_HAL_AcmCoefConvert\000"
	.space	2
	.type	__func__.35400, %object
	.size	__func__.35400, 19
__func__.35400:
	.ascii	"PQ_HAL_Split_Table\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"pointer is NULL!\012\000"
	.space	2
.LC1:
	.ascii	"pSplitTbl is NULL pointer!\012\000"
.LC2:
	.ascii	"ACM Split_Table ERROR!\012\000"
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
