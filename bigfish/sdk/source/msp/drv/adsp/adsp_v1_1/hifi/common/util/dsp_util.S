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
	.file	"dsp_util.c"
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
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/adsp/adsp_v1_1
@ -Idrivers/msp/adsp/adsp_v1_1
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/mach-hi3798mx/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/api/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/drv/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/api/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/component/ha_codec/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/component/ha_effect/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/include/comp
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/aoe/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/aflt/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/aoe/src/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/component/codec/iapcm_dec
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/component/codec/iamp3_dec
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/component/effect/base_effect
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1
@ -imultilib armv7a_soft -iprefix
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/
@ -isysroot /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../target
@ -D__KERNEL__ -D__LINUX_ARM_ARCH__=7 -Uarm -DCHIP_TYPE_hi3796mv100
@ -DSDK_VERSION=HiSTBAndroidV600R001C00SPC060_v2015040918 -DHI_MCE_SUPPORT
@ -DHI_GPIOI2C_SUPPORT -DHI_LOG_SUPPORT=1 -DHI_LOG_LEVEL=4
@ -DHI_PROC_SUPPORT=1 -DHI_HDMI_SUPPORT_1_4 -DHI_KEYLED_SUPPORT
@ -DHI_HDCP_SUPPORT -DHI_SCI_SUPPORT -DHI_PVR_SUPPORT -DHI_VI_SUPPORT
@ -DHI_VENC_SUPPORT -DHI_AENC_SUPPORT -DHI_PQ_V3_0
@ -DHI_SND_AOE_SWSIMULATE_SUPPORT -DHI_SND_AFLT_SWSIMULATE_SUPPORT
@ -DINTERLEAVED_OUTPUT -DPCM_DECODER_SUPPORT -DBASE_EFFECT_SUPPORT
@ -DHI_SND_TIMER_CAST -DKBUILD_STR(s)=#s
@ -DKBUILD_BASENAME=KBUILD_STR(dsp_util)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_adsp) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/adsp/adsp_v1_1/./hifi/common/util/.dsp_util.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/adsp/adsp_v1_1/./hifi/common/util/dsp_util.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/adsp/adsp_v1_1/./hifi/common/util/dsp_util.o -O2 -Wall
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
	.global	UTIL_CalcFrameSize
	.type	UTIL_CalcFrameSize, %function
UTIL_CalcFrameSize:
	.fnstart
.LFB890:
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
	cmp	r1, #16	@ uBitDepth,
	moveq	r0, r0, asl #1	@ uFrameSize, uCh,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r1, #24	@ uBitDepth,
	moveq	r0, r0, asl #2	@ uFrameSize, uCh,
	movne	r0, #0	@ uFrameSize,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	UTIL_CalcFrameSize, .-UTIL_CalcFrameSize
	.align	2
	.global	UTIL_LatencyMs2ByteSize
	.type	UTIL_LatencyMs2ByteSize, %function
UTIL_LatencyMs2ByteSize:
	.fnstart
.LFB891:
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
	mul	ip, r0, r1	@ tmp138, u32LatencyMs, u32FrameSize
	movw	r0, #:lower16:274877907	@ tmp142,
	movt	r0, #:upper16:274877907	@ tmp142,
	mul	r1, r2, ip	@ tmp139, u32SampleRate, tmp138
	umull	r2, r3, r0, r1	@, tmp140, tmp142, tmp139
	mov	r0, r3, lsr #6	@, tmp140,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	UTIL_LatencyMs2ByteSize, .-UTIL_LatencyMs2ByteSize
	.global	__aeabi_uidiv
	.align	2
	.global	UTIL_LatencyMs
	.type	UTIL_LatencyMs, %function
UTIL_LatencyMs:
	.fnstart
.LFB892:
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
	mov	r3, #1000	@ tmp139,
	mul	r0, r3, r0	@, tmp139, u32DataBytes
	mul	r1, r1, r2	@, u32FrameSize, u32SampleRate
	bl	__aeabi_uidiv	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	UTIL_LatencyMs, .-UTIL_LatencyMs
	.align	2
	.global	UTIL_LRLinearGainProcess
	.type	UTIL_LRLinearGainProcess, %function
UTIL_LRLinearGainProcess:
	.fnstart
.LFB895:
	@ args = 4, pretend = 0, frame = 0
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
	ldrsh	ip, [fp, #4]	@ s16VolumeR, s16VolumeR
	cmp	r3, ip	@ s16VolumeL, s16VolumeR
	beq	.L13	@,
	cmp	r2, #0	@ InSamps,
	ldmlefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	sub	r5, r2, #1	@ tmp191, InSamps,
	ldrsh	r4, [r0, #0]	@ tmp215,* pSrcPcmBuf
	and	r6, r5, #1	@ tmp193, tmp191,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r4, r4, r3	@ ret, tmp215, s16VolumeL
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r5, r4, r4	@ sum, ret, ret
@ 0 "" 2
	mov	r4, #1	@ n.384,
	cmp	r4, r2	@ n.384, InSamps
	strh	r5, [r1, #0]	@ movhi	@ sum,* pDestPcmBuf
	mov	r5, #2	@ ivtmp.376,
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	cmp	r6, #0	@ tmp193,
	beq	.L19	@,
	ldrsh	r6, [r0, r5]	@ tmp224,* ivtmp.376
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r6, r6, ip	@ ret, tmp224, s16VolumeR
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, r6, r6	@ sum, ret, ret
@ 0 "" 2
	add	r4, r4, #1	@ n.384, n.384,
	strh	r6, [r1, r5]	@ movhi	@ sum,* ivtmp.376
	cmp	r4, r2	@ n.384, InSamps
	add	r5, r5, #2	@ ivtmp.376, ivtmp.376,
	bne	.L19	@,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L39:
	ldrsh	r6, [r0, r5]	@ tmp184,* ivtmp.376
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r6, r6, ip	@ ret, tmp184, s16VolumeR
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, r6, r6	@ sum, ret, ret
@ 0 "" 2
	add	r4, r4, #1	@ tmp194, n.384,
	strh	r6, [r1, r5]	@ movhi	@ sum,* ivtmp.376
	tst	r4, #1	@ tmp194,
	add	r5, r5, #2	@ tmp195, ivtmp.376,
	beq	.L32	@,
.L40:
	ldrsh	r6, [r0, r5]	@ tmp229,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r6, r6, ip	@ ret, tmp229, s16VolumeR
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, r6, r6	@ sum, ret, ret
@ 0 "" 2
	add	r4, r4, #1	@ n.384, tmp194,
	strh	r6, [r1, r5]	@ movhi	@ sum,
	cmp	r4, r2	@ n.384, InSamps
	add	r5, r5, #2	@ ivtmp.376, tmp195,
	beq	.L38	@,
.L19:
	tst	r4, #1	@ n.384,
	bne	.L39	@,
	ldrsh	r6, [r0, r5]	@ tmp185,* ivtmp.376
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r6, r6, r3	@ ret, tmp185, s16VolumeL
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, r6, r6	@ sum, ret, ret
@ 0 "" 2
	add	r4, r4, #1	@ tmp194, n.384,
	strh	r6, [r1, r5]	@ movhi	@ sum,* ivtmp.376
	tst	r4, #1	@ tmp194,
	add	r5, r5, #2	@ tmp195, ivtmp.376,
	bne	.L40	@,
.L32:
	ldrsh	r6, [r0, r5]	@ tmp226,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r6, r6, r3	@ ret, tmp226, s16VolumeL
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, r6, r6	@ sum, ret, ret
@ 0 "" 2
	add	r4, r4, #1	@ n.384, tmp194,
	strh	r6, [r1, r5]	@ movhi	@ sum,
	cmp	r4, r2	@ n.384, InSamps
	add	r5, r5, #2	@ ivtmp.376, tmp195,
	bne	.L19	@,
.L38:
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L13:
	cmp	r2, #0	@ InSamps,
	ldmlefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	sub	r4, r2, #1	@ tmp186, InSamps,
	ldrsh	ip, [r0, #0]	@ tmp182,* pSrcPcmBuf
	and	r4, r4, #1	@ tmp188, tmp186,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r5, ip, r3	@ ret, tmp182, s16VolumeL
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    ip, r5, r5	@ sum.385, ret, ret
@ 0 "" 2
	mov	r5, #1	@ n,
	cmp	r5, r2	@ n, InSamps
	strh	ip, [r1, #0]	@ movhi	@ sum.385,* pDestPcmBuf
	mov	ip, #2	@ ivtmp.371,
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	cmp	r4, #0	@ tmp188,
	beq	.L16	@,
	ldrsh	r5, [r0, #2]	@ tmp212,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r4, r5, r3	@ ret, tmp212, s16VolumeL
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r4, r4, r4	@ sum.385, ret, ret
@ 0 "" 2
	cmp	ip, r2	@ n, InSamps
	mov	r5, ip	@ n, ivtmp.371
	strh	r4, [r1, #2]	@ movhi	@ sum.385,
	mov	ip, #4	@ ivtmp.371,
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L16:
	ldrsh	r6, [r0, ip]	@ tmp198,* ivtmp.371
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r4, r6, r3	@ ret, tmp198, s16VolumeL
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, r4, r4	@ sum.385, ret, ret
@ 0 "" 2
	add	r4, ip, #2	@ tmp190, ivtmp.371,
	strh	r6, [r1, ip]	@ movhi	@ sum.385,* ivtmp.371
	add	r5, r5, #1	@ tmp189, n,
	ldrsh	ip, [r0, r4]	@ tmp203,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  ip, ip, r3	@ ret, tmp203, s16VolumeL
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    ip, ip, ip	@ sum.385, ret, ret
@ 0 "" 2
	add	r5, r5, #1	@ n, tmp189,
	strh	ip, [r1, r4]	@ movhi	@ sum.385,
	cmp	r5, r2	@ n, InSamps
	add	ip, r4, #2	@ ivtmp.371, tmp190,
	bne	.L16	@,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	UTIL_LRLinearGainProcess, .-UTIL_LRLinearGainProcess
	.align	2
	.global	UTIL_UpmixPcmData
	.type	UTIL_UpmixPcmData, %function
UTIL_UpmixPcmData:
	.fnstart
.LFB898:
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
	ldr	r3, [r2, #16]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
	cmp	r3, #24	@ <variable>.u32BitPerSample,
	beq	.L105	@,
	cmp	r3, #16	@ <variable>.u32BitPerSample,
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	ldr	ip, [r2, #12]	@ <variable>.u32SamplesPerFrame, <variable>.u32SamplesPerFrame
	ldr	r5, [r2, #0]	@ temp.427, <variable>.pDataBuf
	cmp	ip, #0	@ <variable>.u32SamplesPerFrame,
	movne	r7, #0	@ i.431,
	movne	r6, r1	@ pu16Dst, WkBuf
	movne	r4, r7	@ Data, i.431
	beq	.L54	@,
.L55:
	cmp	r0, #0	@ dstCh,
	beq	.L59	@,
	ldr	r3, [r2, #20]	@ <variable>.u32Channels, <variable>.u32Channels
	add	ip, r6, #2	@ ivtmp.420, pu16Dst,
	sub	r8, r0, #1	@ tmp206, dstCh,
	cmp	r3, #0	@ <variable>.u32Channels,
	and	r8, r8, #1	@ tmp208, tmp206,
	strlsh	r4, [ip, #-2]	@ movhi	@ Data,
	movls	r6, ip	@ pu16Dst, ivtmp.420
	ldrhih	r4, [r5], #2	@ Data,
	movhi	r6, ip	@ pu16Dst, ivtmp.420
	strhih	r4, [ip, #-2]	@ movhi	@ Data,
.L94:
	mov	r3, #1	@ ch.430,
	cmp	r0, r3	@ dstCh, ch.430
	add	ip, ip, #2	@ ivtmp.420, ivtmp.420,
	bls	.L95	@,
	cmp	r8, #0	@ tmp208,
	beq	.L58	@,
	ldr	r6, [r2, #20]	@ <variable>.u32Channels, <variable>.u32Channels
	cmp	r6, r3	@ <variable>.u32Channels, ch.430
	add	r3, r3, #1	@ ch.430, tmp210,
	strlsh	r4, [ip, #-2]	@ movhi	@ Data,
	ldrhih	r4, [r5], #2	@ Data,
	movls	r6, ip	@ pu16Dst, ivtmp.420
	movhi	r6, ip	@ pu16Dst, ivtmp.420
	strhih	r4, [ip, #-2]	@ movhi	@ Data,
	cmp	r0, r3	@ dstCh, ch.430
	add	ip, ip, #2	@ ivtmp.420, tmp209,
	bls	.L95	@,
.L58:
	ldr	r6, [r2, #20]	@ <variable>.u32Channels, <variable>.u32Channels
	cmp	r6, r3	@ <variable>.u32Channels, ch.430
	add	r3, r3, #1	@ tmp210, ch.430,
	ldrhih	r4, [r5], #2	@ Data,
	strh	r4, [ip, #-2]	@ movhi	@ Data,
	add	ip, ip, #2	@ tmp209, ivtmp.420,
	ldr	r8, [r2, #20]	@ <variable>.u32Channels, <variable>.u32Channels
	mov	r6, ip	@ pu16Dst, tmp209
	cmp	r8, r3	@ <variable>.u32Channels, tmp210
	ldrhih	r4, [r5], #2	@ Data,
	movhi	r6, ip	@ pu16Dst, tmp209
.L100:
	add	r3, r3, #1	@ ch.430, tmp210,
	strh	r4, [ip, #-2]	@ movhi	@ Data,
	cmp	r0, r3	@ dstCh, ch.430
	add	ip, ip, #2	@ ivtmp.420, tmp209,
	bhi	.L58	@,
.L95:
	ldr	ip, [r2, #12]	@ <variable>.u32SamplesPerFrame, <variable>.u32SamplesPerFrame
.L59:
	add	r7, r7, #1	@ i.431, i.431,
	cmp	ip, r7	@ <variable>.u32SamplesPerFrame, i.431
	bhi	.L55	@,
.L104:
	ldr	r3, [r2, #16]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
.L54:
	cmp	r3, #16	@ <variable>.u32BitPerSample,
	str	r0, [r2, #20]	@ dstCh, <variable>.u32Channels
	moveq	ip, ip, asl #1	@ tmp193, <variable>.u32SamplesPerFrame,
	str	r1, [r2, #0]	@ WkBuf, <variable>.pDataBuf
	muleq	r0, r0, ip	@ prephitmp.437, dstCh, tmp193
	beq	.L63	@,
	cmp	r3, #24	@ <variable>.u32BitPerSample,
	movne	r0, #0	@ prephitmp.437,
	moveq	ip, ip, asl #2	@ tmp195, <variable>.u32SamplesPerFrame,
	muleq	r0, r0, ip	@ prephitmp.437, dstCh, tmp195
.L63:
	str	r0, [r2, #8]	@ prephitmp.437, <variable>.u32DataBytes
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L105:
	ldr	ip, [r2, #12]	@ <variable>.u32SamplesPerFrame, <variable>.u32SamplesPerFrame
	ldr	r5, [r2, #0]	@ D.14630, <variable>.pDataBuf
	cmp	ip, #0	@ <variable>.u32SamplesPerFrame,
	movne	r7, #0	@ i,
	movne	r6, r1	@ pu32Dst, WkBuf
	movne	r4, r7	@ Data, i
	beq	.L54	@,
.L44:
	cmp	r0, #0	@ dstCh,
	beq	.L48	@,
	ldr	r3, [r2, #20]	@ <variable>.u32Channels, <variable>.u32Channels
	add	ip, r6, #4	@ ivtmp.413, pu32Dst,
	sub	r8, r0, #1	@ tmp201, dstCh,
	cmp	r3, #0	@ <variable>.u32Channels,
	and	r8, r8, #1	@ tmp203, tmp201,
	strls	r4, [ip, #-4]	@ Data,
	movls	r6, ip	@ pu32Dst, ivtmp.413
	ldrhi	r4, [r5], #4	@ Data,
	movhi	r6, ip	@ pu32Dst, ivtmp.413
	strhi	r4, [ip, #-4]	@ Data,
.L89:
	mov	r3, #1	@ ch,
	cmp	r0, r3	@ dstCh, ch
	add	ip, ip, #4	@ ivtmp.413, ivtmp.413,
	bls	.L90	@,
	cmp	r8, #0	@ tmp203,
	beq	.L47	@,
	ldr	r6, [r2, #20]	@ <variable>.u32Channels, <variable>.u32Channels
	cmp	r6, r3	@ <variable>.u32Channels, ch
	add	r3, r3, #1	@ ch, tmp204,
	strls	r4, [ip, #-4]	@ Data,
	ldrhi	r4, [r5], #4	@ Data,
	movls	r6, ip	@ pu32Dst, ivtmp.413
	movhi	r6, ip	@ pu32Dst, ivtmp.413
	strhi	r4, [ip, #-4]	@ Data,
	cmp	r0, r3	@ dstCh, ch
	add	ip, ip, #4	@ ivtmp.413, tmp205,
	bls	.L90	@,
.L47:
	ldr	r6, [r2, #20]	@ <variable>.u32Channels, <variable>.u32Channels
	cmp	r6, r3	@ <variable>.u32Channels, ch
	add	r3, r3, #1	@ tmp204, ch,
	ldrhi	r4, [r5], #4	@ Data,
	str	r4, [ip, #-4]	@ Data,
	add	ip, ip, #4	@ tmp205, ivtmp.413,
	ldr	r8, [r2, #20]	@ <variable>.u32Channels, <variable>.u32Channels
	mov	r6, ip	@ pu32Dst, tmp205
	cmp	r8, r3	@ <variable>.u32Channels, tmp204
	ldrhi	r4, [r5], #4	@ Data,
	movhi	r6, ip	@ pu32Dst, tmp205
.L99:
	add	r3, r3, #1	@ ch, tmp204,
	str	r4, [ip, #-4]	@ Data,
	cmp	r0, r3	@ dstCh, ch
	add	ip, ip, #4	@ ivtmp.413, tmp205,
	bhi	.L47	@,
.L90:
	ldr	ip, [r2, #12]	@ <variable>.u32SamplesPerFrame, <variable>.u32SamplesPerFrame
.L48:
	add	r7, r7, #1	@ i, i,
	cmp	ip, r7	@ <variable>.u32SamplesPerFrame, i
	bhi	.L44	@,
	b	.L104	@
	.fnend
	.size	UTIL_UpmixPcmData, .-UTIL_UpmixPcmData
	.align	2
	.global	UTIL_DownmixPcmData
	.type	UTIL_DownmixPcmData, %function
UTIL_DownmixPcmData:
	.fnstart
.LFB899:
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
	ldr	r3, [r2, #16]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
	cmp	r3, #24	@ <variable>.u32BitPerSample,
	beq	.L138	@,
	cmp	r3, #16	@ <variable>.u32BitPerSample,
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	ldr	ip, [r2, #12]	@ <variable>.u32SamplesPerFrame, <variable>.u32SamplesPerFrame
	ldr	r4, [r2, #0]	@ temp.480, <variable>.pDataBuf
	cmp	ip, #0	@ <variable>.u32SamplesPerFrame,
	movne	r5, r1	@ pu16Dst, WkBuf
	movne	r6, #0	@ i.483,
	beq	.L119	@,
.L120:
	cmp	r0, #0	@ dstCh,
	beq	.L124	@,
	add	r3, r4, #2	@ ivtmp.474, pu16Src,
	mov	ip, #0	@ ch.482,
	movls	r4, r3	@ pu16Src, ivtmp.474
	bhi	.L131	@,
	add	ip, ip, #1	@ ch.482, ch.482,
	add	r3, r3, #2	@ ivtmp.474, ivtmp.474,
	cmp	r0, ip	@ dstCh, ch.482
	bls	.L139	@,
.L131:
	ldrh	r4, [r3, #-2]	@,
	add	ip, ip, #1	@ ch.482, ch.482,
	cmp	r0, ip	@ dstCh, ch.482
	strh	r4, [r5], #2	@ movhi	@,
	mov	r4, r3	@ pu16Src, ivtmp.474
	add	r3, r3, #2	@ ivtmp.474, ivtmp.474,
	bhi	.L131	@,
.L139:
	ldr	ip, [r2, #12]	@ <variable>.u32SamplesPerFrame, <variable>.u32SamplesPerFrame
.L124:
	add	r6, r6, #1	@ i.483, i.483,
	cmp	ip, r6	@ <variable>.u32SamplesPerFrame, i.483
	bhi	.L120	@,
.L137:
	ldr	r3, [r2, #16]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
.L119:
	cmp	r3, #16	@ <variable>.u32BitPerSample,
	str	r0, [r2, #20]	@ dstCh, <variable>.u32Channels
	moveq	ip, ip, asl #1	@ tmp164, <variable>.u32SamplesPerFrame,
	str	r1, [r2, #0]	@ WkBuf, <variable>.pDataBuf
	muleq	r0, r0, ip	@ prephitmp.487, dstCh, tmp164
	beq	.L128	@,
	cmp	r3, #24	@ <variable>.u32BitPerSample,
	movne	r0, #0	@ prephitmp.487,
	moveq	ip, ip, asl #2	@ tmp166, <variable>.u32SamplesPerFrame,
	muleq	r0, r0, ip	@ prephitmp.487, dstCh, tmp166
.L128:
	str	r0, [r2, #8]	@ prephitmp.487, <variable>.u32DataBytes
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L138:
	ldr	ip, [r2, #12]	@ <variable>.u32SamplesPerFrame, <variable>.u32SamplesPerFrame
	ldr	r4, [r2, #0]	@ D.14674, <variable>.pDataBuf
	cmp	ip, #0	@ <variable>.u32SamplesPerFrame,
	movne	r5, r1	@ pu32Dst, WkBuf
	movne	r7, #0	@ i,
	beq	.L119	@,
.L109:
	cmp	r0, #0	@ dstCh,
	beq	.L113	@,
	add	r3, r4, #4	@ ivtmp.467, pu32Src,
	mov	ip, #0	@ ch,
	movls	r4, r3	@ pu32Src, ivtmp.467
	bhi	.L130	@,
	add	ip, ip, #1	@ ch, ch,
	add	r3, r3, #4	@ ivtmp.467, ivtmp.467,
	cmp	r0, ip	@ dstCh, ch
	bls	.L140	@,
.L130:
	ldr	r6, [r3, #-4]	@ tmp152,
	add	ip, ip, #1	@ ch, ch,
	cmp	r0, ip	@ dstCh, ch
	mov	r4, r3	@ pu32Src, ivtmp.467
	add	r3, r3, #4	@ ivtmp.467, ivtmp.467,
	str	r6, [r5], #4	@ tmp152,
	bhi	.L130	@,
.L140:
	ldr	ip, [r2, #12]	@ <variable>.u32SamplesPerFrame, <variable>.u32SamplesPerFrame
.L113:
	add	r7, r7, #1	@ i, i,
	cmp	ip, r7	@ <variable>.u32SamplesPerFrame, i
	bhi	.L109	@,
	b	.L137	@
	.fnend
	.size	UTIL_DownmixPcmData, .-UTIL_DownmixPcmData
	.align	2
	.global	UTIL_UnifyBitDepthPcmData
	.type	UTIL_UnifyBitDepthPcmData, %function
UTIL_UnifyBitDepthPcmData:
	.fnstart
.LFB900:
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
	ldr	r3, [r2, #20]	@ <variable>.u32Channels, <variable>.u32Channels
	ldr	ip, [r2, #12]	@ <variable>.u32SamplesPerFrame, <variable>.u32SamplesPerFrame
	cmp	r0, #16	@ dstBitDepth,
	mul	r3, ip, r3	@ Samples, <variable>.u32SamplesPerFrame, <variable>.u32Channels
	beq	.L161	@,
	cmp	r0, #24	@ dstBitDepth,
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	ldr	ip, [r2, #16]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
	cmp	ip, #16	@ <variable>.u32BitPerSample,
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	cmp	r3, #0	@ Samples,
	ldr	r4, [r2, #0]	@ temp.542, <variable>.pDataBuf
	beq	.L146	@,
	ldrh	ip, [r4, #0]	@ Data,* temp.542
	cmp	r3, #1	@ Samples,
	sub	r5, r3, #1	@ tmp165, Samples,
	mov	r0, #1	@ i.544,
	and	r5, r5, r0	@ tmp167, tmp165,
	mov	ip, ip, asl #16	@ tmp157, Data,
	str	ip, [r1, #0]	@ tmp157,* WkBuf
	bls	.L146	@,
	cmp	r5, #0	@ tmp167,
	beq	.L147	@,
	mov	r0, #2	@ tmp193,
	cmp	r3, r0	@ Samples, i.544
	ldrh	ip, [r4, r0]	@ Data,
	mov	ip, ip, asl #16	@ tmp196, Data,
	str	ip, [r1, #4]	@ tmp196,
	bls	.L146	@,
.L147:
	mov	r5, r0, asl #1	@ tmp180, i.544,
	add	ip, r0, #1	@ tmp168, i.544,
	ldrh	r6, [r4, r5]	@ Data,
	mov	r5, ip, asl #1	@ tmp185, tmp168,
	mov	r6, r6, asl #16	@ tmp183, Data,
	str	r6, [r1, r0, asl #2]	@ tmp183,* WkBuf
	add	r0, ip, #1	@ i.544, tmp168,
	ldrh	r5, [r4, r5]	@ Data,
	cmp	r3, r0	@ Samples, i.544
	mov	r5, r5, asl #16	@ tmp188, Data,
	str	r5, [r1, ip, asl #2]	@ tmp188,* WkBuf
	bhi	.L147	@,
.L146:
	ldr	r3, [r2, #8]	@ <variable>.u32DataBytes, <variable>.u32DataBytes
	mov	r0, #24	@ tmp158,
	str	r1, [r2, #0]	@ WkBuf, <variable>.pDataBuf
	str	r0, [r2, #16]	@ tmp158, <variable>.u32BitPerSample
	mov	r1, r3, asl #1	@ tmp160, <variable>.u32DataBytes,
	str	r1, [r2, #8]	@ tmp160, <variable>.u32DataBytes
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L161:
	ldr	r0, [r2, #16]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
	cmp	r0, #24	@ <variable>.u32BitPerSample,
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	cmp	r3, #0	@ Samples,
	ldr	r4, [r2, #0]	@ D.14717, <variable>.pDataBuf
	beq	.L144	@,
	sub	r0, r3, #1	@ tmp161, Samples,
	cmp	r3, #1	@ Samples,
	and	ip, r0, #1	@ tmp163, tmp161,
	ldrh	r0, [r4, #2]	@,
	strh	r0, [r1, #0]	@ movhi	@,* WkBuf
	mov	r0, #1	@ i,
	bls	.L144	@,
	cmp	ip, #0	@ tmp163,
	beq	.L145	@,
	ldrh	r5, [r4, #6]	@,
	mov	ip, #2	@ tmp191,
	cmp	r3, ip	@ Samples, i
	mov	r0, ip	@ i, tmp191
	strh	r5, [r1, ip]	@ movhi	@,
	bls	.L144	@,
.L145:
	add	r7, r4, r0, asl #2	@, tmp173, D.14717, i,
	add	ip, r0, #1	@ tmp164, i,
	mov	r6, r0, asl #1	@ tmp172, i,
	add	r0, ip, #1	@ i, tmp164,
	ldrh	r7, [r7, #2]	@,
	mov	r5, ip, asl #1	@ tmp177, tmp164,
	add	ip, r4, ip, asl #2	@, tmp178, D.14717, tmp164,
	cmp	r3, r0	@ Samples, i
	strh	r7, [r1, r6]	@ movhi	@,
	ldrh	ip, [ip, #2]	@,
	strh	ip, [r1, r5]	@ movhi	@,
	bhi	.L145	@,
.L144:
	ldr	r3, [r2, #8]	@ <variable>.u32DataBytes, <variable>.u32DataBytes
	mov	r0, #16	@ tmp151,
	str	r1, [r2, #0]	@ WkBuf, <variable>.pDataBuf
	str	r0, [r2, #16]	@ tmp151, <variable>.u32BitPerSample
	mov	r1, r3, lsr #1	@ tmp153, <variable>.u32DataBytes,
	str	r1, [r2, #8]	@ tmp153, <variable>.u32DataBytes
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	UTIL_UnifyBitDepthPcmData, .-UTIL_UnifyBitDepthPcmData
	.align	2
	.global	UTIL_GainProcess
	.type	UTIL_GainProcess, %function
UTIL_GainProcess:
	.fnstart
.LFB907:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	ldr	r3, [r0, #20]	@ <variable>.u32Channels, <variable>.u32Channels
	ldr	ip, [r0, #12]	@ <variable>.u32SamplesPerFrame, <variable>.u32SamplesPerFrame
	cmp	r1, #1	@ bLinearMode,
	mul	ip, ip, r3	@ samples, <variable>.u32SamplesPerFrame, <variable>.u32Channels
	beq	.L259	@,
	ldr	r3, [r0, #16]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
	cmp	r3, #16	@ <variable>.u32BitPerSample,
	beq	.L175	@,
	cmp	r3, #24	@ <variable>.u32BitPerSample,
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	uxtb	r1, r2	@ tmp209, Volume
	movw	r3, #:lower16:.LANCHOR0	@ tmp210,
	rsb	r2, r1, #139	@ idx, tmp209,
	movt	r3, #:upper16:.LANCHOR0	@ tmp210,
	cmp	r2, #99	@ idx,
	movge	r2, #99	@ tmp211,
	cmp	ip, #0	@ samples,
	ldr	r0, [r0, #0]	@ temp.637, <variable>.pDataBuf
	ldr	r1, [r3, r2, asl #2]	@ realVol, g_u32VolCoef
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	cmp	r1, #0	@ realVol,
	sub	r6, ip, #1	@ tmp263, samples,
	and	r4, r6, #1	@ tmp264, tmp263,
	movw	r5, #:lower16:8388607	@ tmp239,
	mov	r2, r1	@ D.15720, realVol
	mov	r3, r2, asr #31	@ D.15720
	movt	r5, #:upper16:8388607	@ tmp239,
	ldr	r6, [r0, #0]	@ data,* temp.637
	beq	.L260	@,
	mov	r7, r6, asr #31	@ data
	cmp	r1, #8388608	@ realVol,
	mul	r8, r2, r7	@ tmp374, D.15720, data
	mla	r8, r6, r3, r8	@ tmp375, data, D.15720, tmp374
	umull	r6, r7, r2, r6	@ tmp376, D.15720, data
	add	r7, r8, r7	@, tmp375,
	mov	r8, r6, lsr #23	@ tmp379, tmp376,
	orr	r6, r8, r7, asl #9	@, tmp380, tmp379,,
	mov	r8, r6	@ var.642, tmp380
	bls	.L223	@,
	mov	r6, r6, asr #8	@ tmp382, tmp380,
	mov	r7, r6, asr #31	@ tmp383
	mul	r8, r6, r3	@ tmp385, tmp383, D.15720
	mla	r8, r2, r7, r8	@ tmp386, D.15720,, tmp385
	umull	r6, r7, r6, r2	@ tmp387, tmp383, D.15720
	add	r7, r8, r7	@, tmp386,
	mov	r8, r6, lsr #23	@ D.15718, tmp387,
	orr	r8, r8, r7, asl #9	@, var, D.15718,,
	mov	r6, r8, asr #31	@ sign, var,
	cmp	r6, r8, asr #23	@ sign, var,
	eorne	r8, r6, r5	@ var, sign, tmp239
	mov	r8, r8, asl #8	@ var.642, var,
.L223:
	subs	r6, ip, #1	@ ivtmp.615, samples,
	str	r8, [r0, #0]	@ var.642,* temp.637
	mov	ip, #4	@ ivtmp.621,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L264:
	cmp	r4, #0	@ tmp264,
	beq	.L185	@,
	cmp	r1, #0	@ realVol,
	ldr	r8, [r0, ip]	@ data,* ivtmp.621
	moveq	r4, r1	@ var.642, realVol
	beq	.L227	@,
	mov	r9, r8, asr #31	@ data
	cmp	r1, #8388608	@ realVol,
	mul	r4, r2, r9	@ tmp399, D.15720, data
	mla	r4, r8, r3, r4	@ tmp400, data, D.15720, tmp399
	umull	r8, r9, r2, r8	@ tmp401, D.15720, data
	add	r9, r4, r9	@, tmp400,
	mov	r4, r8, lsr #23	@ tmp404, tmp401,
	orr	r8, r4, r9, asl #9	@, tmp405, tmp404,,
	mov	r4, r8	@ var.642, tmp405
	bls	.L227	@,
	mov	r8, r8, asr #8	@ tmp407, tmp405,
	mov	r9, r8, asr #31	@ tmp408
	mul	r4, r8, r3	@ tmp410, tmp408, D.15720
	mla	r4, r2, r9, r4	@ tmp411, D.15720,, tmp410
	umull	r8, r9, r8, r2	@ tmp412, tmp408, D.15720
	add	r9, r4, r9	@, tmp411,
	mov	r4, r8, lsr #23	@ D.15718, tmp412,
	orr	r4, r4, r9, asl #9	@, var, D.15718,,
	mov	r8, r4, asr #31	@ sign, var,
	cmp	r8, r4, asr #23	@ sign, var,
	eorne	r4, r8, r5	@ var, sign, tmp239
	mov	r4, r4, asl #8	@ var.642, var,
.L227:
	subs	r6, r6, #1	@ ivtmp.615, ivtmp.615,
	str	r4, [r0, ip]	@ var.642,* ivtmp.621
	add	ip, ip, #4	@ ivtmp.621, ivtmp.621,
	bne	.L185	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L259:
	ldr	r3, [r0, #16]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
	cmp	r3, #16	@ <variable>.u32BitPerSample,
	beq	.L165	@,
	cmp	r3, #24	@ <variable>.u32BitPerSample,
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	uxth	r2, r2	@ temp.634, Volume
	ldr	r3, [r0, #0]	@ temp.633, <variable>.pDataBuf
	cmp	r2, #0	@ temp.634,
	bne	.L261	@,
	cmp	ip, #0	@ samples,
	ldmlefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	cmp	ip, #1	@ samples,
	sub	r0, ip, #1	@ tmp250, samples,
	and	r0, r0, #1	@ tmp252, tmp250,
	str	r2, [r3, #0]	@ tmp234,* temp.633
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	cmp	r0, #0	@ tmp252,
	beq	.L173	@,
	mov	r1, #2	@ n,
	cmp	ip, r1	@ samples, n
	str	r2, [r3, #4]	@ tmp234,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L173:
	add	r0, r1, #1	@ tmp253, n,
	str	r2, [r3, r1, asl #2]	@ tmp234,* temp.633
	add	r1, r0, #1	@ n, tmp253,
	cmp	ip, r1	@ samples, n
	str	r2, [r3, r0, asl #2]	@ tmp234,* temp.633
	bne	.L173	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L175:
	uxtb	r1, r2	@ tmp193, Volume
	movw	r3, #:lower16:.LANCHOR0	@ tmp194,
	rsb	r2, r1, #139	@ idx, tmp193,
	movt	r3, #:upper16:.LANCHOR0	@ tmp194,
	cmp	r2, #99	@ idx,
	movge	r2, #99	@ tmp195,
	cmp	ip, #0	@ samples,
	ldr	r1, [r0, #0]	@ temp.636, <variable>.pDataBuf
	ldr	r2, [r3, r2, asl #2]	@ realVol, g_u32VolCoef
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	cmp	r2, #0	@ realVol,
	sub	r8, ip, #1	@ tmp259, samples,
	and	r8, r8, #1	@ tmp260, tmp259,
	mov	r6, r2	@ realVol, realVol
	mov	r7, r6, asr #31	@ realVol
	movw	r3, #32767	@ tmp236,
	ldrh	r4, [r1, #0]	@ D.15690,* temp.636
	bne	.L209	@,
	subs	ip, ip, #1	@ ivtmp.615, samples,
	mov	r0, r2	@ D.15691, realVol
	strh	r0, [r1, #0]	@ movhi	@ D.15691,* temp.636
	mov	r0, #2	@ ivtmp.605,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L265:
	cmp	r8, #0	@ tmp260,
	beq	.L181	@,
	cmp	r2, #0	@ realVol,
	ldrh	r4, [r1, r0]	@ D.15690,* ivtmp.605
	moveq	r4, r2	@ D.15691, realVol
	beq	.L251	@,
	sxth	r4, r4	@ D.15690, D.15690
	cmp	r2, #8388608	@ realVol,
	mov	r5, r4, asr #31	@ D.15690
	mul	r8, r6, r5	@ tmp345, realVol, D.15690
	mla	r8, r4, r7, r8	@ tmp346, D.15690, realVol, tmp345
	umull	r4, r5, r6, r4	@ tmp347, realVol, D.15690
	add	r5, r8, r5	@, tmp346,
	mov	r8, r4, lsr #23	@ tmp350, tmp347,
	orr	r4, r8, r5, asl #9	@, var, tmp350,,
	bls	.L249	@,
	mov	r5, r4, asr #31	@ sign, var,
	cmp	r5, r4, asr #15	@ sign, var,
	eorne	r4, r5, r3	@ var, sign, tmp236
.L249:
	uxth	r4, r4	@ D.15691, var
.L251:
	subs	ip, ip, #1	@ ivtmp.615, ivtmp.615,
	strh	r4, [r1, r0]	@ movhi	@ D.15691,* ivtmp.605
	add	r0, r0, #2	@ ivtmp.605, ivtmp.605,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L181:
	cmp	r2, #0	@ realVol,
	ldrh	r4, [r1, r0]	@ D.15690,* ivtmp.605
	moveq	r5, r2	@ D.15691, realVol
	beq	.L178	@,
	sxth	r4, r4	@ D.15690, D.15690
	cmp	r2, #8388608	@ realVol,
	mov	r5, r4, asr #31	@ D.15690
	mul	r8, r6, r5	@ tmp200, realVol, D.15690
	mla	r8, r4, r7, r8	@ tmp299, D.15690, realVol, tmp200
	umull	r4, r5, r6, r4	@ tmp201, realVol, D.15690
	add	r5, r8, r5	@, tmp299,
	mov	r8, r4, lsr #23	@ tmp229, tmp201,
	orr	r5, r8, r5, asl #9	@, var, tmp229,,
	bls	.L180	@,
	mov	r4, r5, asr #31	@ sign, var,
	cmp	r4, r5, asr #15	@ sign, var,
	eorne	r5, r4, r3	@ var, sign, tmp236
.L180:
	uxth	r5, r5	@ D.15691, var
.L178:
	add	r4, r0, #2	@ tmp262, ivtmp.605,
	cmp	r2, #0	@ realVol,
	strh	r5, [r1, r0]	@ movhi	@ D.15691,* ivtmp.605
	sub	ip, ip, #1	@ tmp261, ivtmp.615,
	ldrh	r8, [r1, r4]	@ D.15690,
	bne	.L218	@,
	mov	r0, r2	@ D.15691, realVol
.L254:
	subs	ip, ip, #1	@ ivtmp.615, tmp261,
	strh	r0, [r1, r4]	@ movhi	@ D.15691,
	add	r0, r4, #2	@ ivtmp.605, tmp262,
	bne	.L181	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L263:
	mov	r8, r1	@ var.642, realVol
.L232:
	subs	r6, ip, #1	@ ivtmp.615, tmp265,
	str	r8, [r0, r4]	@ var.642,
	add	ip, r4, #4	@ ivtmp.621, tmp266,
	beq	.L262	@,
.L185:
	cmp	r1, #0	@ realVol,
	ldr	r8, [r0, ip]	@ data,* ivtmp.621
	moveq	r8, r1	@ var.642, realVol
	beq	.L183	@,
	mov	r9, r8, asr #31	@ data
	cmp	r1, #8388608	@ realVol,
	mul	r4, r2, r9	@ tmp214, D.15720, data
	mla	r4, r8, r3, r4	@ tmp307, data, D.15720, tmp214
	umull	r8, r9, r2, r8	@ tmp215, D.15720, data
	add	r9, r4, r9	@, tmp307,
	mov	r4, r8, lsr #23	@ tmp231, tmp215,
	orr	r4, r4, r9, asl #9	@, tmp309, tmp231,,
	mov	r8, r4	@ var.642, tmp309
	bls	.L183	@,
	mov	r8, r4, asr #8	@ tmp219, tmp309,
	mov	r9, r8, asr #31	@ tmp220
	mul	r4, r8, r3	@ tmp222, tmp220, D.15720
	mla	r4, r2, r9, r4	@ tmp310, D.15720,, tmp222
	umull	r8, r9, r8, r2	@ tmp223, tmp220, D.15720
	add	r9, r4, r9	@, tmp310,
	mov	r4, r8, lsr #23	@ D.15718, tmp223,
	orr	r8, r4, r9, asl #9	@, var, D.15718,,
	mov	r4, r8, asr #31	@ sign, var,
	cmp	r4, r8, asr #23	@ sign, var,
	eorne	r8, r4, r5	@ var, sign, tmp239
	mov	r8, r8, asl #8	@ var.642, var,
.L183:
	add	r4, ip, #4	@ tmp266, ivtmp.621,
	cmp	r1, #0	@ realVol,
	str	r8, [r0, ip]	@ var.642,* ivtmp.621
	sub	ip, r6, #1	@ tmp265, ivtmp.615,
	ldr	r6, [r0, r4]	@ data,
	beq	.L263	@,
	mov	r7, r6, asr #31	@ data
	cmp	r1, #8388608	@ realVol,
	mul	r8, r2, r7	@ tmp423, D.15720, data
	mla	r8, r6, r3, r8	@ tmp424, data, D.15720, tmp423
	umull	r6, r7, r2, r6	@ tmp425, D.15720, data
	add	r7, r8, r7	@, tmp424,
	mov	r8, r6, lsr #23	@ tmp428, tmp425,
	orr	r6, r8, r7, asl #9	@, tmp429, tmp428,,
	mov	r8, r6	@ var.642, tmp429
	bls	.L232	@,
	mov	r6, r6, asr #8	@ tmp431, tmp429,
	mov	r7, r6, asr #31	@ tmp432
	mul	r8, r6, r3	@ tmp434, tmp432, D.15720
	mla	r8, r2, r7, r8	@ tmp435, D.15720,, tmp434
	umull	r6, r7, r6, r2	@ tmp436, tmp432, D.15720
	add	r7, r8, r7	@, tmp435,
	mov	r8, r6, lsr #23	@ D.15718, tmp436,
	orr	r8, r8, r7, asl #9	@, var, D.15718,,
	mov	r6, r8, asr #31	@ sign, var,
	cmp	r6, r8, asr #23	@ sign, var,
	eorne	r8, r6, r5	@ var, sign, tmp239
	mov	r8, r8, asl #8	@ var.642, var,
	b	.L232	@
.L260:
	subs	r6, ip, #1	@ ivtmp.615, samples,
	mov	r8, r1	@ var.642, realVol
	mov	ip, #4	@ ivtmp.621,
	str	r8, [r0, #0]	@ var.642,* temp.637
	bne	.L264	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L209:
	sxth	r4, r4	@ D.15690, D.15690
	cmp	r2, #8388608	@ realVol,
	mov	r5, r4, asr #31	@ D.15690
	mul	r0, r6, r5	@ tmp329, realVol, D.15690
	mla	r0, r4, r7, r0	@ tmp330, D.15690, realVol, tmp329
	umull	r4, r5, r6, r4	@ tmp331, realVol, D.15690
	add	r5, r0, r5	@, tmp330,
	mov	r0, r4, lsr #23	@ tmp334, tmp331,
	orr	r0, r0, r5, asl #9	@, var, tmp334,,
	bls	.L245	@,
	mov	r4, r0, asr #31	@ sign, var,
	cmp	r4, r0, asr #15	@ sign, var,
	eorne	r0, r4, r3	@ var, sign, tmp236
.L245:
	subs	ip, ip, #1	@ ivtmp.615, samples,
	uxth	r0, r0	@ D.15691, var
	strh	r0, [r1, #0]	@ movhi	@ D.15691,* temp.636
	mov	r0, #2	@ ivtmp.605,
	bne	.L265	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L165:
	uxth	r2, r2	@ D.14855, Volume
	ldr	r3, [r0, #0]	@ D.14853, <variable>.pDataBuf
	cmp	r2, #0	@ D.14855,
	bne	.L266	@,
	cmp	ip, #0	@ samples,
	ldmlefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	cmp	ip, #1	@ samples,
	sub	r0, ip, #1	@ tmp241, samples,
	and	r0, r0, #1	@ tmp243, tmp241,
	strh	r2, [r3, #0]	@ movhi	@ D.14855,* D.14853
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	cmp	r0, #0	@ tmp243,
	beq	.L169	@,
	mov	r0, #2	@ tmp316,
	cmp	ip, r0	@ samples, n
	mov	r1, r0	@ n, tmp316
	strh	r2, [r3, r0]	@ movhi	@ D.14855,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L169:
	add	r4, r1, #1	@ tmp244, n,
	mov	r0, r1, asl #1	@ tmp268, n,
	add	r1, r4, #1	@ n, tmp244,
	mov	r2, r4, asl #1	@ tmp270, tmp244,
	cmp	ip, r1	@ samples, n
	mov	r4, #0	@ movhi	@,
	strh	r4, [r3, r0]	@ movhi	@,
	strh	r4, [r3, r2]	@ movhi	@,
	bne	.L169	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L218:
	sxth	r8, r8	@ D.15690, D.15690
	cmp	r2, #8388608	@ realVol,
	mov	r9, r8, asr #31	@ D.15690
	mul	r0, r6, r9	@ tmp360, realVol, D.15690
	mla	r0, r8, r7, r0	@ tmp361, D.15690, realVol, tmp360
	umull	r8, r9, r6, r8	@ tmp362, realVol, D.15690
	add	r9, r0, r9	@, tmp361,
	mov	r0, r8, lsr #23	@ tmp365, tmp362,
	orr	r0, r0, r9, asl #9	@, var, tmp365,,
	bls	.L252	@,
	mov	r5, r0, asr #31	@ sign, var,
	cmp	r5, r0, asr #15	@ sign, var,
	eorne	r0, r5, r3	@ var, sign, tmp236
.L252:
	uxth	r0, r0	@ D.15691, var
	b	.L254	@
.L262:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L266:
	cmp	ip, #0	@ samples,
	ldmlefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	sub	r0, ip, #1	@ tmp245, samples,
	sxth	r4, r2	@ pretmp.574, D.14855
	and	r0, r0, #1	@ tmp247, tmp245,
	ldrsh	r2, [r3, #0]	@ tmp185,* D.14853
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r2, r2, r4	@ ret, tmp185, pretmp.574
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r2, r2, r2	@ sum, ret, ret
@ 0 "" 2
	cmp	ip, #1	@ samples,
	strh	r2, [r3, #0]	@ movhi	@ sum,* D.14853
	mov	r2, #2	@ ivtmp.592,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	cmp	r0, #0	@ tmp247,
	beq	.L170	@,
	ldrsh	r0, [r3, #2]	@ tmp317,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r1, r0, r4	@ ret, tmp317, pretmp.574
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r0, r1, r1	@ sum, ret, ret
@ 0 "" 2
	cmp	ip, r2	@ samples, n.638
	mov	r1, r2	@ n.638, ivtmp.592
	strh	r0, [r3, #2]	@ movhi	@ sum,
	mov	r2, #4	@ ivtmp.592,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L170:
	ldrsh	r5, [r3, r2]	@ tmp273,* ivtmp.592
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r0, r5, r4	@ ret, tmp273, pretmp.574
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r5, r0, r0	@ sum, ret, ret
@ 0 "" 2
	add	r0, r2, #2	@ tmp249, ivtmp.592,
	strh	r5, [r3, r2]	@ movhi	@ sum,* ivtmp.592
	add	r1, r1, #1	@ tmp248, n.638,
	ldrsh	r2, [r3, r0]	@ tmp278,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r2, r2, r4	@ ret, tmp278, pretmp.574
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r2, r2, r2	@ sum, ret, ret
@ 0 "" 2
	add	r1, r1, #1	@ n.638, tmp248,
	strh	r2, [r3, r0]	@ movhi	@ sum,
	cmp	ip, r1	@ samples, n.638
	add	r2, r0, #2	@ ivtmp.592, tmp249,
	bne	.L170	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L261:
	cmp	ip, #0	@ samples,
	ldmlefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	sub	r0, ip, #1	@ tmp254, samples,
	sxth	r4, r2	@ temp.634, temp.634
	and	r0, r0, #1	@ tmp256, tmp254,
	ldr	r2, [r3, #0]	@ tmp188,* temp.633
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r2, r2, r4	@ ret, tmp188, temp.634
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r2, r2, r2	@ sum, ret, ret
@ 0 "" 2
	cmp	ip, #1	@ samples,
	str	r2, [r3, #0]	@ sum,* temp.633
	mov	r2, #4	@ ivtmp.600,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	cmp	r0, #0	@ tmp256,
	beq	.L174	@,
	ldr	r0, [r3, #4]	@ tmp322,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r1, r0, r4	@ ret, tmp322, temp.634
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r2, r1, r1	@ sum, ret, ret
@ 0 "" 2
	mov	r1, #2	@ n.639,
	cmp	ip, r1	@ samples, n.639
	str	r2, [r3, #4]	@ sum,
	mov	r2, #8	@ ivtmp.600,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
.L174:
	ldr	r5, [r3, r2]	@ tmp289,* ivtmp.600
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r0, r5, r4	@ ret, tmp289, temp.634
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r5, r0, r0	@ sum, ret, ret
@ 0 "" 2
	add	r0, r2, #4	@ tmp258, ivtmp.600,
	str	r5, [r3, r2]	@ sum,* ivtmp.600
	add	r1, r1, #1	@ tmp257, n.639,
	ldr	r2, [r3, r0]	@ tmp294,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r2, r2, r4	@ ret, tmp294, temp.634
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r2, r2, r2	@ sum, ret, ret
@ 0 "" 2
	add	r1, r1, #1	@ n.639, tmp257,
	str	r2, [r3, r0]	@ sum,
	cmp	ip, r1	@ samples, n.639
	add	r2, r0, #4	@ ivtmp.600, tmp258,
	bne	.L174	@,
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}	@
	.fnend
	.size	UTIL_GainProcess, .-UTIL_GainProcess
	.align	2
	.global	UTIL_LRGainProcess
	.type	UTIL_LRGainProcess, %function
UTIL_LRGainProcess:
	.fnstart
.LFB908:
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
	ldr	ip, [r0, #20]	@ <variable>.u32Channels, <variable>.u32Channels
	ldr	r4, [r0, #12]	@ <variable>.u32SamplesPerFrame, <variable>.u32SamplesPerFrame
	cmp	r1, #1	@ bLinearMode,
	mul	r4, r4, ip	@ samples, <variable>.u32SamplesPerFrame, <variable>.u32Channels
	beq	.L414	@,
	ldr	r1, [r0, #16]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
	cmp	r1, #16	@ <variable>.u32BitPerSample,
	beq	.L284	@,
	cmp	r1, #24	@ <variable>.u32BitPerSample,
	beq	.L415	@,
.L319:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L415:
	uxtb	r1, r3	@ tmp282, VolumeR
	uxtb	r6, r2	@ tmp277, VolumeL
	rsb	ip, r1, #139	@ idx.794, tmp282,
	rsb	r6, r6, #139	@ idx, tmp277,
	cmp	r6, #99	@ idx,
	movge	r6, #99	@ tmp279,
	cmp	ip, #99	@ idx.794,
	movge	ip, #99	@ tmp284,
	cmp	r2, r3	@ VolumeL, VolumeR
	movw	r3, #:lower16:.LANCHOR0	@ tmp278,
	movt	r3, #:upper16:.LANCHOR0	@ tmp278,
	ldr	r1, [r0, #0]	@ temp.778, <variable>.pDataBuf
	ldr	ip, [r3, ip, asl #2]	@ realVolR, g_u32VolCoef
	ldr	r0, [r3, r6, asl #2]	@ realVolL, g_u32VolCoef
	beq	.L304	@,
	cmp	r4, #0	@ samples,
	beq	.L319	@,
	sub	r2, r4, #1	@ samples.801, samples,
	movw	sl, #:lower16:8388607	@ tmp365,
	tst	r2, #1	@ samples.801,
	movt	sl, #:upper16:8388607	@ tmp365,
	mov	r3, #0	@ ivtmp.765,
	mov	r4, ip	@, realVolR
	mov	r5, r4, asr #31	@
	mov	r6, r0	@ D.15840, realVolL
	mov	r7, r6, asr #31	@ D.15840
	strd	r4, [fp, #-52]	@,,
	mov	r9, sl	@ tmp365, tmp365
	ldr	r4, [r1, r3]	@ data.796,* ivtmp.765
	beq	.L310	@,
.L416:
	cmp	ip, #0	@ realVolR,
	moveq	sl, ip	@ var.797, realVolR
	beq	.L312	@,
	ldr	sl, [fp, #-52]	@, %sfp
	mov	r5, r4, asr #31	@ data.796
	cmp	ip, #8388608	@ realVolR,
	mul	r8, sl, r5	@ tmp303,, data.796
	ldr	r5, [fp, #-48]	@, %sfp
	ldr	sl, [fp, #-52]	@, %sfp
	mla	r8, r4, r5, r8	@ tmp452, data.796,, tmp303
	umull	r4, r5, sl, r4	@ tmp304,, data.796
	add	r5, r8, r5	@, tmp452,
	mov	r8, r4, lsr #23	@ tmp345, tmp304,
	orr	r8, r8, r5, asl #9	@, tmp454, tmp345,,
	mov	sl, r8	@ var.797, tmp454
	bls	.L312	@,
	mov	r4, r8, asr #8	@ tmp308, tmp454,
	ldr	r8, [fp, #-48]	@, %sfp
	mov	r5, r4, asr #31	@ tmp309
	mul	sl, r4, r8	@ tmp311, tmp309,
	ldr	r8, [fp, #-52]	@, %sfp
	mla	sl, r8, r5, sl	@ tmp455,,, tmp311
	umull	r4, r5, r4, r8	@ tmp312, tmp309,
	add	r5, sl, r5	@, tmp455,
	mov	r8, r4, lsr #23	@ D.15854, tmp312,
	orr	r8, r8, r5, asl #9	@, var, D.15854,,
	mov	r4, r8, asr #31	@ sign, var,
	cmp	r4, r8, asr #23	@ sign, var,
	eorne	r8, r4, r9	@ var, sign, tmp365
	mov	sl, r8, asl #8	@ var.797, var,
.L312:
	str	sl, [r1, r3]	@ var.797,* ivtmp.765
	sub	r2, r2, #1	@ samples.801, samples.801,
	add	r3, r3, #4	@ ivtmp.765, ivtmp.765,
.L417:
	tst	r2, #1	@ samples.801,
	ldr	r4, [r1, r3]	@ data.796,* ivtmp.765
	bne	.L416	@,
.L310:
	cmp	r0, #0	@ realVolL,
	moveq	sl, r0	@ var.798, realVolL
	beq	.L316	@,
	mov	r5, r4, asr #31	@ data.796
	cmp	r0, #8388608	@ realVolL,
	mul	sl, r6, r5	@ tmp318, D.15840, data.796
	mla	r8, r4, r7, sl	@ tmp457, data.796, D.15840, tmp318
	umull	r4, r5, r6, r4	@ tmp319, D.15840, data.796
	add	r5, r8, r5	@, tmp457,
	mov	sl, r4, lsr #23	@ tmp347, tmp319,
	orr	r8, sl, r5, asl #9	@, tmp459, tmp347,,
	mov	sl, r8	@ var.798, tmp459
	bls	.L316	@,
	mov	r4, r8, asr #8	@ tmp323, tmp459,
	mov	r5, r4, asr #31	@ tmp324
	mul	r8, r4, r7	@ tmp326, tmp324, D.15840
	mla	sl, r6, r5, r8	@ tmp460, D.15840,, tmp326
	umull	r4, r5, r4, r6	@ tmp327, tmp324, D.15840
	add	r5, sl, r5	@, tmp460,
	mov	r8, r4, lsr #23	@ D.15842, tmp327,
	orr	r8, r8, r5, asl #9	@, var, D.15842,,
	mov	r4, r8, asr #31	@ sign, var,
	cmp	r4, r8, asr #23	@ sign, var,
	eorne	r8, r4, r9	@ var, sign, tmp365
	mov	sl, r8, asl #8	@ var.798, var,
.L316:
	cmp	r2, #0	@ samples.801,
	str	sl, [r1, r3]	@ var.798,* ivtmp.765
	add	r3, r3, #4	@ ivtmp.765, ivtmp.765,
	beq	.L319	@,
	sub	r2, r2, #1	@ samples.801, samples.801,
	b	.L417	@
.L414:
	ldr	ip, [r0, #16]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
	cmp	ip, #16	@ <variable>.u32BitPerSample,
	beq	.L270	@,
	cmp	ip, #24	@ <variable>.u32BitPerSample,
	bne	.L319	@,
	sxth	r2, r2	@ temp.774, VolumeL
	sxth	r3, r3	@ temp.775, VolumeR
	cmp	r2, r3	@ temp.774, temp.775
	ldr	r0, [r0, #0]	@ temp.773, <variable>.pDataBuf
	beq	.L278	@,
	cmp	r4, #0	@ samples,
	ble	.L319	@,
	sub	r6, r4, #1	@ tmp384, samples,
	ldr	ip, [r0, #0]	@ tmp484,* temp.773
	and	r6, r6, #1	@ tmp386, tmp384,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  ip, ip, r2	@ ret, tmp484, temp.774
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    ip, ip, ip	@ sum.787, ret, ret
@ 0 "" 2
	cmp	r4, r1	@ samples, n.790
	str	ip, [r0], #4	@ sum.787,
	beq	.L319	@,
	cmp	r6, #0	@ tmp386,
	beq	.L283	@,
	ldr	ip, [r0, #0]	@ tmp493,* ivtmp.707
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  ip, ip, r3	@ ret, tmp493, temp.775
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    ip, ip, ip	@ sum.787, ret, ret
@ 0 "" 2
	add	r1, r1, #1	@ n.790, n.790,
	str	ip, [r0], #4	@ sum.787,
	cmp	r4, r1	@ samples, n.790
	bne	.L283	@,
	b	.L319	@
.L418:
	ldr	r6, [r0, #0]	@ tmp226,* ivtmp.707
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  ip, r6, r3	@ ret, tmp226, temp.775
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, ip, ip	@ sum.787, ret, ret
@ 0 "" 2
	add	r1, r1, #1	@ tmp387, n.790,
	mov	ip, r0	@ tmp388, ivtmp.707
	tst	r1, #1	@ tmp387,
	str	r6, [ip], #4	@ sum.787,
	beq	.L346	@,
.L419:
	ldr	r6, [r0, #4]	@ tmp498,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r0, r6, r3	@ ret, tmp498, temp.775
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, r0, r0	@ sum.787, ret, ret
@ 0 "" 2
.L387:
	add	r1, r1, #1	@ n.790, tmp387,
	mov	r0, ip	@ ivtmp.707, tmp388
	cmp	r4, r1	@ samples, n.790
	str	r6, [r0], #4	@ sum.787,
	beq	.L319	@,
.L283:
	tst	r1, #1	@ n.790,
	bne	.L418	@,
	ldr	r6, [r0, #0]	@ tmp228,* ivtmp.707
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  ip, r6, r2	@ ret, tmp228, temp.774
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, ip, ip	@ sum.787, ret, ret
@ 0 "" 2
	add	r1, r1, #1	@ tmp387, n.790,
	mov	ip, r0	@ tmp388, ivtmp.707
	tst	r1, #1	@ tmp387,
	str	r6, [ip], #4	@ sum.787,
	bne	.L419	@,
.L346:
	ldr	r6, [r0, #4]	@ tmp495,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r0, r6, r2	@ ret, tmp495, temp.774
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, r0, r0	@ sum.787, ret, ret
@ 0 "" 2
	b	.L387	@
.L284:
	uxtb	r6, r2	@ tmp233, VolumeL
	uxtb	r1, r3	@ tmp238, VolumeR
	rsb	ip, r1, #139	@ idx.792, tmp238,
	rsb	r6, r6, #139	@ idx.791, tmp233,
	cmp	r6, #99	@ idx.791,
	movge	r6, #99	@ tmp235,
	cmp	ip, #99	@ idx.792,
	movge	ip, #99	@ tmp240,
	cmp	r2, r3	@ VolumeL, VolumeR
	movw	r2, #:lower16:.LANCHOR0	@ tmp234,
	movt	r2, #:upper16:.LANCHOR0	@ tmp234,
	ldr	r1, [r0, #0]	@ temp.777, <variable>.pDataBuf
	ldr	ip, [r2, ip, asl #2]	@ realVolR, g_u32VolCoef
	ldr	r0, [r2, r6, asl #2]	@ realVolL, g_u32VolCoef
	beq	.L286	@,
	cmp	r4, #0	@ samples,
	beq	.L319	@,
	sub	r2, r4, #1	@ samples.800, samples,
	mov	r3, #0	@ ivtmp.733,
	tst	r2, #1	@ samples.800,
	mov	r4, r0	@, realVolL
	mov	r5, r4, asr #31	@
	mov	r6, ip	@ realVolR, realVolR
	mov	r7, r6, asr #31	@ realVolR
	strd	r4, [fp, #-52]	@,,
	movw	sl, #32767	@ tmp357,
	ldrh	r4, [r1, r3]	@ temp.793,* ivtmp.733
	beq	.L293	@,
.L420:
	cmp	r0, #0	@ realVolL,
	moveq	r4, r0	@ D.15798, realVolL
	beq	.L295	@,
	ldr	r9, [fp, #-52]	@, %sfp
	sxth	r4, r4	@ temp.793, temp.793
	cmp	r0, #8388608	@ realVolL,
	mov	r5, r4, asr #31	@ temp.793
	mul	r8, r9, r5	@ tmp257,, temp.793
	ldr	r9, [fp, #-48]	@, %sfp
	mla	r8, r4, r9, r8	@ tmp437, temp.793,, tmp257
	ldr	r9, [fp, #-52]	@, %sfp
	umull	r4, r5, r9, r4	@ tmp258,, temp.793
	add	r5, r8, r5	@, tmp437,
	mov	r8, r4, lsr #23	@ tmp339, tmp258,
	orr	r4, r8, r5, asl #9	@, var, tmp339,,
	bls	.L297	@,
	mov	r8, r4, asr #31	@ sign, var,
	cmp	r8, r4, asr #15	@ sign, var,
	eorne	r4, r8, sl	@ var, sign, tmp357
.L297:
	uxth	r4, r4	@ D.15798, var
.L295:
	strh	r4, [r1, r3]	@ movhi	@ D.15798,* ivtmp.733
	sub	r2, r2, #1	@ samples.800, samples.800,
	add	r3, r3, #2	@ ivtmp.733, ivtmp.733,
.L421:
	tst	r2, #1	@ samples.800,
	ldrh	r4, [r1, r3]	@ temp.793,* ivtmp.733
	bne	.L420	@,
.L293:
	cmp	ip, #0	@ realVolR,
	moveq	r4, ip	@ D.15789, realVolR
	beq	.L300	@,
	sxth	r4, r4	@ temp.793, temp.793
	cmp	ip, #8388608	@ realVolR,
	mov	r5, r4, asr #31	@ temp.793
	mul	r8, r6, r5	@ tmp268, realVolR, temp.793
	mla	r8, r4, r7, r8	@ tmp439, temp.793, realVolR, tmp268
	umull	r4, r5, r6, r4	@ tmp269, realVolR, temp.793
	add	r5, r8, r5	@, tmp439,
	mov	r8, r4, lsr #23	@ tmp341, tmp269,
	orr	r4, r8, r5, asl #9	@, var, tmp341,,
	bls	.L302	@,
	mov	r8, r4, asr #31	@ sign, var,
	cmp	r8, r4, asr #15	@ sign, var,
	eorne	r4, r8, sl	@ var, sign, tmp357
.L302:
	uxth	r4, r4	@ D.15789, var
.L300:
	cmp	r2, #0	@ samples.800,
	strh	r4, [r1, r3]	@ movhi	@ D.15789,* ivtmp.733
	add	r3, r3, #2	@ ivtmp.733, ivtmp.733,
	beq	.L319	@,
	sub	r2, r2, #1	@ samples.800, samples.800,
	b	.L421	@
.L270:
	sxth	r2, r2	@ D.14881, VolumeL
	sxth	r3, r3	@ D.14882, VolumeR
	cmp	r2, r3	@ D.14881, D.14882
	ldr	r0, [r0, #0]	@ D.14879, <variable>.pDataBuf
	beq	.L272	@,
	cmp	r4, #0	@ samples,
	ble	.L319	@,
	sub	r6, r4, #1	@ tmp374, samples,
	ldrsh	ip, [r0, #0]	@ tmp465,* D.14879
	and	r6, r6, #1	@ tmp376, tmp374,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  ip, ip, r2	@ ret, tmp465, D.14881
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    ip, ip, ip	@ sum.781, ret, ret
@ 0 "" 2
	cmp	r4, r1	@ samples, n.785
	strh	ip, [r0], #2	@ movhi	@ sum.781,
	beq	.L319	@,
	cmp	r6, #0	@ tmp376,
	beq	.L277	@,
	ldrsh	ip, [r0, #0]	@ tmp474,* ivtmp.699
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  ip, ip, r3	@ ret, tmp474, D.14882
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    ip, ip, ip	@ sum.781, ret, ret
@ 0 "" 2
	add	r1, r1, #1	@ n.785, n.785,
	strh	ip, [r0], #2	@ movhi	@ sum.781,
	cmp	r4, r1	@ samples, n.785
	bne	.L277	@,
	b	.L319	@
.L422:
	ldrsh	r6, [r0, #0]	@ tmp217,* ivtmp.699
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  ip, r6, r3	@ ret, tmp217, D.14882
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, ip, ip	@ sum.781, ret, ret
@ 0 "" 2
	add	r1, r1, #1	@ tmp377, n.785,
	mov	ip, r0	@ tmp378, ivtmp.699
	tst	r1, #1	@ tmp377,
	strh	r6, [ip], #2	@ movhi	@ sum.781,
	beq	.L335	@,
.L423:
	ldrsh	r6, [r0, #2]	@ tmp479,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r0, r6, r3	@ ret, tmp479, D.14882
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, r0, r0	@ sum.781, ret, ret
@ 0 "" 2
.L386:
	add	r1, r1, #1	@ n.785, tmp377,
	mov	r0, ip	@ ivtmp.699, tmp378
	cmp	r4, r1	@ samples, n.785
	strh	r6, [r0], #2	@ movhi	@ sum.781,
	beq	.L319	@,
.L277:
	tst	r1, #1	@ n.785,
	bne	.L422	@,
	ldrsh	r6, [r0, #0]	@ tmp219,* ivtmp.699
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  ip, r6, r2	@ ret, tmp219, D.14881
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, ip, ip	@ sum.781, ret, ret
@ 0 "" 2
	add	r1, r1, #1	@ tmp377, n.785,
	mov	ip, r0	@ tmp378, ivtmp.699
	tst	r1, #1	@ tmp377,
	strh	r6, [ip], #2	@ movhi	@ sum.781,
	bne	.L423	@,
.L335:
	ldrsh	r6, [r0, #2]	@ tmp476,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r0, r6, r2	@ ret, tmp476, D.14881
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, r0, r0	@ sum.781, ret, ret
@ 0 "" 2
	b	.L386	@
.L304:
	cmp	r4, #0	@ samples,
	beq	.L319	@,
	cmp	r0, #0	@ realVolL,
	sub	r7, r4, #1	@ tmp393, samples,
	and	ip, r7, #1	@ tmp394, tmp393,
	movw	r2, #:lower16:8388607	@ tmp362,
	mov	r6, r0	@ D.15864, realVolL
	mov	r7, r6, asr #31	@ D.15864
	movt	r2, #:upper16:8388607	@ tmp362,
	ldr	r8, [r1, #0]	@ data,* temp.778
	beq	.L424	@,
	mov	r9, r8, asr #31	@ data
	cmp	r0, #8388608	@ realVolL,
	mul	r3, r6, r9	@ tmp549, D.15864, data
	mla	r3, r8, r7, r3	@ tmp550, data, D.15864, tmp549
	umull	r8, r9, r6, r8	@ tmp551, D.15864, data
	add	r9, r3, r9	@, tmp550,
	mov	r3, r8, lsr #23	@ tmp554, tmp551,
	orr	r8, r3, r9, asl #9	@, tmp555, tmp554,,
	mov	r3, r8	@ var.795, tmp555
	bls	.L362	@,
	mov	r8, r8, asr #8	@ tmp557, tmp555,
	mov	r9, r8, asr #31	@ tmp558
	mul	r3, r8, r7	@ tmp560, tmp558, D.15864
	mla	r3, r6, r9, r3	@ tmp561, D.15864,, tmp560
	umull	r8, r9, r8, r6	@ tmp562, tmp558, D.15864
	add	r9, r3, r9	@, tmp561,
	mov	r3, r8, lsr #23	@ D.15866, tmp562,
	orr	r3, r3, r9, asl #9	@, var, D.15866,,
	mov	r8, r3, asr #31	@ sign, var,
	cmp	r8, r3, asr #23	@ sign, var,
	eorne	r3, r8, r2	@ var, sign, tmp362
	mov	r3, r3, asl #8	@ var.795, var,
.L362:
	subs	r4, r4, #1	@ ivtmp.723, samples,
	str	r3, [r1, #0]	@ var.795,* temp.778
	mov	r3, #4	@ ivtmp.745,
	beq	.L319	@,
	cmp	ip, #0	@ tmp394,
	beq	.L309	@,
	cmp	r0, #0	@ realVolL,
	ldr	r8, [r1, r3]	@ data,* ivtmp.745
	moveq	ip, r0	@ var.795, realVolL
	beq	.L366	@,
	mov	r9, r8, asr #31	@ data
	cmp	r0, #8388608	@ realVolL,
	mul	ip, r6, r9	@ tmp574, D.15864, data
	mla	ip, r8, r7, ip	@ tmp575, data, D.15864, tmp574
	umull	r8, r9, r6, r8	@ tmp576, D.15864, data
	add	r9, ip, r9	@, tmp575,
	mov	ip, r8, lsr #23	@ tmp579, tmp576,
	orr	r8, ip, r9, asl #9	@, tmp580, tmp579,,
	mov	ip, r8	@ var.795, tmp580
	bls	.L366	@,
	mov	r8, r8, asr #8	@ tmp582, tmp580,
	mov	r9, r8, asr #31	@ tmp583
	mul	ip, r8, r7	@ tmp585, tmp583, D.15864
	mla	ip, r6, r9, ip	@ tmp586, D.15864,, tmp585
	umull	r8, r9, r8, r6	@ tmp587, tmp583, D.15864
	add	r9, ip, r9	@, tmp586,
	mov	ip, r8, lsr #23	@ D.15866, tmp587,
	orr	ip, ip, r9, asl #9	@, var, D.15866,,
	mov	r8, ip, asr #31	@ sign, var,
	cmp	r8, ip, asr #23	@ sign, var,
	eorne	ip, r8, r2	@ var, sign, tmp362
	mov	ip, ip, asl #8	@ var.795, var,
.L366:
	subs	r4, r4, #1	@ ivtmp.723, ivtmp.723,
	str	ip, [r1, r3]	@ var.795,* ivtmp.745
	add	r3, r3, #4	@ ivtmp.745, ivtmp.745,
	bne	.L309	@,
	b	.L319	@
.L425:
	mov	r3, r0	@ var.795, realVolL
.L371:
	subs	r4, r4, #1	@ ivtmp.723, tmp396,
	str	r3, [r1, ip]	@ var.795,
	add	r3, ip, #4	@ ivtmp.745, tmp395,
	beq	.L319	@,
.L309:
	cmp	r0, #0	@ realVolL,
	ldr	r8, [r1, r3]	@ data,* ivtmp.745
	moveq	r8, r0	@ var.795, realVolL
	beq	.L307	@,
	mov	r9, r8, asr #31	@ data
	cmp	r0, #8388608	@ realVolL,
	mul	ip, r6, r9	@ tmp287, D.15864, data
	mla	ip, r8, r7, ip	@ tmp443, data, D.15864, tmp287
	umull	r8, r9, r6, r8	@ tmp288, D.15864, data
	add	r9, ip, r9	@, tmp443,
	mov	ip, r8, lsr #23	@ tmp343, tmp288,
	orr	ip, ip, r9, asl #9	@, tmp445, tmp343,,
	mov	r8, ip	@ var.795, tmp445
	bls	.L307	@,
	mov	r8, ip, asr #8	@ tmp292, tmp445,
	mov	r9, r8, asr #31	@ tmp293
	mul	sl, r8, r7	@ tmp295, tmp293, D.15864
	mla	sl, r6, r9, sl	@ tmp446, D.15864,, tmp295
	umull	r8, r9, r8, r6	@ tmp296, tmp293, D.15864
	add	r9, sl, r9	@, tmp446,
	mov	ip, r8, lsr #23	@ D.15866, tmp296,
	orr	r8, ip, r9, asl #9	@, var, D.15866,,
	mov	ip, r8, asr #31	@ sign, var,
	cmp	ip, r8, asr #23	@ sign, var,
	eorne	r8, ip, r2	@ var, sign, tmp362
	mov	r8, r8, asl #8	@ var.795, var,
.L307:
	add	ip, r3, #4	@ tmp395, ivtmp.745,
	cmp	r0, #0	@ realVolL,
	str	r8, [r1, r3]	@ var.795,* ivtmp.745
	sub	r4, r4, #1	@ tmp396, ivtmp.723,
	ldr	r8, [r1, ip]	@ data,
	beq	.L425	@,
	mov	r9, r8, asr #31	@ data
	cmp	r0, #8388608	@ realVolL,
	mul	r3, r6, r9	@ tmp598, D.15864, data
	mla	r3, r8, r7, r3	@ tmp599, data, D.15864, tmp598
	umull	r8, r9, r6, r8	@ tmp600, D.15864, data
	add	r9, r3, r9	@, tmp599,
	mov	r3, r8, lsr #23	@ tmp603, tmp600,
	orr	r8, r3, r9, asl #9	@, tmp604, tmp603,,
	mov	r3, r8	@ var.795, tmp604
	bls	.L371	@,
	mov	r8, r8, asr #8	@ tmp606, tmp604,
	mov	r9, r8, asr #31	@ tmp607
	mul	r3, r8, r7	@ tmp609, tmp607, D.15864
	mla	r3, r6, r9, r3	@ tmp610, D.15864,, tmp609
	umull	r8, r9, r8, r6	@ tmp611, tmp607, D.15864
	add	r9, r3, r9	@, tmp610,
	mov	r3, r8, lsr #23	@ D.15866, tmp611,
	orr	r3, r3, r9, asl #9	@, var, D.15866,,
	mov	r8, r3, asr #31	@ sign, var,
	cmp	r8, r3, asr #23	@ sign, var,
	eorne	r3, r8, r2	@ var, sign, tmp362
	mov	r3, r3, asl #8	@ var.795, var,
	b	.L371	@
.L286:
	cmp	r4, #0	@ samples,
	beq	.L319	@,
	cmp	r0, #0	@ realVolL,
	sub	r8, r4, #1	@ tmp389, samples,
	and	ip, r8, #1	@ tmp390, tmp389,
	movw	r2, #32767	@ tmp354,
	mov	r8, r0	@ realVolL, realVolL
	mov	r9, r8, asr #31	@ realVolL
	ldrh	r3, [r1, #0]	@ D.15814,* temp.777
	bne	.L348	@,
	mov	r3, r0	@ D.15807, realVolL
.L390:
	subs	r4, r4, #1	@ ivtmp.723, samples,
	strh	r3, [r1, #0]	@ movhi	@ D.15807,* temp.777
	mov	r3, #2	@ ivtmp.713,
	beq	.L319	@,
	cmp	ip, #0	@ tmp390,
	beq	.L292	@,
	cmp	r0, #0	@ realVolL,
	ldrh	ip, [r1, r3]	@ D.15814,* ivtmp.713
	moveq	ip, r0	@ D.15807, realVolL
	beq	.L394	@,
	sxth	ip, ip	@ D.15814, D.15814
	cmp	r0, #8388608	@ realVolL,
	mov	r6, ip	@ D.15814, D.15814
	mov	r7, r6, asr #31	@ D.15814
	mul	ip, r8, r7	@ tmp520, realVolL, D.15814
	mla	ip, r6, r9, ip	@ tmp521, D.15814, realVolL, tmp520
	umull	r6, r7, r8, r6	@ tmp522, realVolL, D.15814
	add	r7, ip, r7	@, tmp521,
	mov	ip, r6, lsr #23	@ tmp525, tmp522,
	orr	ip, ip, r7, asl #9	@, var, tmp525,,
	bls	.L392	@,
	mov	r6, ip, asr #31	@ sign, var,
	cmp	r6, ip, asr #15	@ sign, var,
	eorne	ip, r6, r2	@ var, sign, tmp354
.L392:
	uxth	ip, ip	@ D.15807, var
.L394:
	subs	r4, r4, #1	@ ivtmp.723, ivtmp.723,
	strh	ip, [r1, r3]	@ movhi	@ D.15807,* ivtmp.713
	add	r3, r3, #2	@ ivtmp.713, ivtmp.713,
	beq	.L319	@,
.L292:
	cmp	r0, #0	@ realVolL,
	ldrh	r6, [r1, r3]	@ D.15814,* ivtmp.713
	moveq	r6, r0	@ D.15807, realVolL
	beq	.L289	@,
	sxth	r6, r6	@ D.15814, D.15814
	cmp	r0, #8388608	@ realVolL,
	mov	r7, r6, asr #31	@ D.15814
	mul	ip, r8, r7	@ tmp245, realVolL, D.15814
	mla	ip, r6, r9, ip	@ tmp431, D.15814, realVolL, tmp245
	umull	r6, r7, r8, r6	@ tmp246, realVolL, D.15814
	add	r7, ip, r7	@, tmp431,
	mov	ip, r6, lsr #23	@ tmp337, tmp246,
	orr	r6, ip, r7, asl #9	@, var, tmp337,,
	bls	.L291	@,
	mov	ip, r6, asr #31	@ sign, var,
	cmp	ip, r6, asr #15	@ sign, var,
	eorne	r6, ip, r2	@ var, sign, tmp354
.L291:
	uxth	r6, r6	@ D.15807, var
.L289:
	add	ip, r3, #2	@ tmp391, ivtmp.713,
	cmp	r0, #0	@ realVolL,
	strh	r6, [r1, r3]	@ movhi	@ D.15807,* ivtmp.713
	sub	r4, r4, #1	@ tmp392, ivtmp.723,
	ldrh	r6, [r1, ip]	@ D.15814,
	bne	.L357	@,
	mov	r3, r0	@ D.15807, realVolL
.L397:
	subs	r4, r4, #1	@ ivtmp.723, tmp392,
	strh	r3, [r1, ip]	@ movhi	@ D.15807,
	add	r3, ip, #2	@ ivtmp.713, tmp391,
	bne	.L292	@,
	b	.L319	@
.L348:
	sxth	r3, r3	@ D.15814, D.15814
	cmp	r0, #8388608	@ realVolL,
	mov	r6, r3	@ D.15814, D.15814
	mov	r7, r6, asr #31	@ D.15814
	mul	r3, r8, r7	@ tmp504, realVolL, D.15814
	mla	r3, r6, r9, r3	@ tmp505, D.15814, realVolL, tmp504
	umull	r6, r7, r8, r6	@ tmp506, realVolL, D.15814
	add	r7, r3, r7	@, tmp505,
	mov	r3, r6, lsr #23	@ tmp509, tmp506,
	orr	r3, r3, r7, asl #9	@, var, tmp509,,
	bls	.L388	@,
	mov	r6, r3, asr #31	@ sign, var,
	cmp	r6, r3, asr #15	@ sign, var,
	eorne	r3, r6, r2	@ var, sign, tmp354
.L388:
	uxth	r3, r3	@ D.15807, var
	b	.L390	@
.L424:
	mov	r3, r0	@ var.795, realVolL
	b	.L362	@
.L357:
	sxth	r6, r6	@ D.15814, D.15814
	cmp	r0, #8388608	@ realVolL,
	mov	r7, r6, asr #31	@ D.15814
	mul	r3, r8, r7	@ tmp535, realVolL, D.15814
	mla	r3, r6, r9, r3	@ tmp536, D.15814, realVolL, tmp535
	umull	r6, r7, r8, r6	@ tmp537, realVolL, D.15814
	add	r7, r3, r7	@, tmp536,
	mov	r3, r6, lsr #23	@ tmp540, tmp537,
	orr	r3, r3, r7, asl #9	@, var, tmp540,,
	bls	.L395	@,
	mov	r6, r3, asr #31	@ sign, var,
	cmp	r6, r3, asr #15	@ sign, var,
	eorne	r3, r6, r2	@ var, sign, tmp354
.L395:
	uxth	r3, r3	@ D.15807, var
	b	.L397	@
.L272:
	cmp	r4, #0	@ samples,
	ble	.L319	@,
	sub	ip, r4, #1	@ tmp369, samples,
	ldrsh	r3, [r0, #0]	@ tmp215,* D.14879
	and	ip, ip, #1	@ tmp371, tmp369,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r3, r3, r2	@ ret, tmp215, D.14881
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r3, r3, r3	@ sum, ret, ret
@ 0 "" 2
	cmp	r4, #1	@ samples,
	strh	r3, [r0, #0]	@ movhi	@ sum,* D.14879
	mov	r3, #2	@ ivtmp.696,
	beq	.L319	@,
	cmp	ip, #0	@ tmp371,
	beq	.L274	@,
	ldrsh	ip, [r0, #2]	@ tmp462,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r1, ip, r2	@ ret, tmp462, D.14881
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    ip, r1, r1	@ sum, ret, ret
@ 0 "" 2
	cmp	r4, r3	@ samples, n
	mov	r1, r3	@ n, ivtmp.696
	strh	ip, [r0, #2]	@ movhi	@ sum,
	mov	r3, #4	@ ivtmp.696,
	beq	.L319	@,
.L274:
	ldrsh	r6, [r0, r3]	@ tmp399,* ivtmp.696
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  ip, r6, r2	@ ret, tmp399, D.14881
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, ip, ip	@ sum, ret, ret
@ 0 "" 2
	add	ip, r3, #2	@ tmp372, ivtmp.696,
	strh	r6, [r0, r3]	@ movhi	@ sum,* ivtmp.696
	add	r1, r1, #1	@ tmp373, n,
	ldrsh	r3, [r0, ip]	@ tmp404,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r3, r3, r2	@ ret, tmp404, D.14881
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r3, r3, r3	@ sum, ret, ret
@ 0 "" 2
	add	r1, r1, #1	@ n, tmp373,
	strh	r3, [r0, ip]	@ movhi	@ sum,
	cmp	r4, r1	@ samples, n
	add	r3, ip, #2	@ ivtmp.696, tmp372,
	bne	.L274	@,
	b	.L319	@
.L278:
	cmp	r4, #0	@ samples,
	ble	.L319	@,
	sub	ip, r4, #1	@ tmp379, samples,
	ldr	r3, [r0, #0]	@ tmp223,* temp.773
	and	ip, ip, #1	@ tmp381, tmp379,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r3, r3, r2	@ ret, tmp223, temp.774
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r3, r3, r3	@ sum, ret, ret
@ 0 "" 2
	cmp	r4, #1	@ samples,
	str	r3, [r0, #0]	@ sum,* temp.773
	mov	r3, #4	@ ivtmp.704,
	beq	.L319	@,
	cmp	ip, #0	@ tmp381,
	beq	.L280	@,
	ldr	ip, [r0, #4]	@ tmp481,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r1, ip, r2	@ ret, tmp481, temp.774
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r3, r1, r1	@ sum, ret, ret
@ 0 "" 2
	mov	r1, #2	@ n,
	cmp	r4, r1	@ samples, n
	str	r3, [r0, #4]	@ sum,
	mov	r3, #8	@ ivtmp.704,
	beq	.L319	@,
.L280:
	ldr	r6, [r0, r3]	@ tmp415,* ivtmp.704
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  ip, r6, r2	@ ret, tmp415, temp.774
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r6, ip, ip	@ sum, ret, ret
@ 0 "" 2
	add	ip, r3, #4	@ tmp383, ivtmp.704,
	str	r6, [r0, r3]	@ sum,* ivtmp.704
	add	r1, r1, #1	@ tmp382, n,
	ldr	r3, [r0, ip]	@ tmp420,
#APP
@ 649 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	smulwb  r3, r3, r2	@ ret, tmp420, temp.774
@ 0 "" 2
@ 650 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd    r3, r3, r3	@ sum, ret, ret
@ 0 "" 2
	add	r1, r1, #1	@ n, tmp382,
	str	r3, [r0, ip]	@ sum,
	cmp	r4, r1	@ samples, n
	add	r3, ip, #4	@ ivtmp.704, tmp383,
	bne	.L280	@,
	b	.L319	@
	.fnend
	.size	UTIL_LRGainProcess, .-UTIL_LRGainProcess
	.align	2
	.global	UTIL_MixerPro
	.type	UTIL_MixerPro, %function
UTIL_MixerPro:
	.fnstart
.LFB909:
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
	cmp	r2, #0	@ samples
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	cmp	r3, #16	@ uBitDepth,
	beq	.L450	@,
	cmp	r3, #24	@ uBitDepth,
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	sub	r3, r2, #1	@ tmp156, samples,
	ldr	r4, [r0, #0]	@ tmp148,* pMixBuf
	ldr	ip, [r1, #0]	@ tmp149,* pInBuf
	and	r5, r3, #1	@ tmp158, tmp156,
#APP
@ 699 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd r3, r4, ip	@ Lvar1, tmp148, tmp149
@ 0 "" 2
	cmp	r2, #1	@ samples,
	str	r3, [r0, #0]	@ Lvar1,* pMixBuf
	mov	r4, #1	@ i.853,
	mov	r3, #4	@ ivtmp.848,
	ldmlsfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	cmp	r5, #0	@ tmp158,
	beq	.L431	@,
	ldr	r4, [r0, #4]	@ tmp193,
	ldr	ip, [r1, #4]	@ tmp194,
#APP
@ 699 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd r3, r4, ip	@ Lvar1, tmp193, tmp194
@ 0 "" 2
	mov	r4, #2	@ i.853,
	cmp	r2, r4	@ samples, i.853
	str	r3, [r0, #4]	@ Lvar1,
	mov	r3, #8	@ ivtmp.848,
	ldmlsfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L431:
	ldr	ip, [r0, r3]	@ tmp177,* ivtmp.848
	ldr	r5, [r1, r3]	@ tmp178,* ivtmp.848
#APP
@ 699 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd r5, ip, r5	@ Lvar1, tmp177, tmp178
@ 0 "" 2
	add	ip, r3, #4	@ tmp159, ivtmp.848,
	str	r5, [r0, r3]	@ Lvar1,* ivtmp.848
	add	r4, r4, #1	@ tmp160, i.853,
	ldr	r3, [r0, ip]	@ tmp182,
	ldr	r5, [r1, ip]	@ tmp183,
#APP
@ 699 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd r3, r3, r5	@ Lvar1, tmp182, tmp183
@ 0 "" 2
	add	r4, r4, #1	@ i.853, tmp160,
	str	r3, [r0, ip]	@ Lvar1,
	cmp	r2, r4	@ samples, i.853
	add	r3, ip, #4	@ ivtmp.848, tmp159,
	bhi	.L431	@,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L450:
	ldrsh	r5, [r1, #0]	@ tmp144,* pInBuf
	movw	r7, #32767	@ tmp150,
	ldrsh	r3, [r0, #0]	@ tmp145,* pMixBuf
	sub	r4, r2, #1	@ tmp151, samples,
	and	r4, r4, #1	@ tmp153, tmp151,
	add	r3, r5, r3	@ x, tmp144, tmp145
	mov	r5, #1	@ i,
	mov	ip, r3, asr #31	@ sign, x,
	cmp	ip, r3, asr #15	@ sign, x,
	eorne	r3, ip, r7	@ x, sign, tmp150
	cmp	r2, r5	@ samples, i
	strh	r3, [r0, #0]	@ movhi	@ x,* pMixBuf
	mov	r3, #2	@ ivtmp.836,
	ldmlsfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	cmp	r4, #0	@ tmp153,
	beq	.L430	@,
	ldrsh	r4, [r1, r3]	@ tmp186,* ivtmp.836
	add	r5, r5, #1	@ i, i,
	ldrsh	ip, [r0, r3]	@ tmp187,* ivtmp.836
	add	ip, r4, ip	@ x, tmp186, tmp187
	mov	r4, ip, asr #31	@ sign, x,
	cmp	r4, ip, asr #15	@ sign, x,
	eorne	ip, r4, r7	@ x, sign, tmp150
	cmp	r2, r5	@ samples, i
	strh	ip, [r0, r3]	@ movhi	@ x,* ivtmp.836
	add	r3, r3, #2	@ ivtmp.836, ivtmp.836,
	ldmlsfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L430:
	ldrsh	r6, [r1, r3]	@ tmp162,* ivtmp.836
	add	ip, r3, #2	@ tmp155, ivtmp.836,
	ldrsh	r4, [r0, r3]	@ tmp163,* ivtmp.836
	add	r5, r5, #1	@ tmp154, i,
	add	r5, r5, #1	@ i, tmp154,
	add	r4, r6, r4	@ x, tmp162, tmp163
	mov	r6, r4, asr #31	@ sign, x,
	cmp	r6, r4, asr #15	@ sign, x,
	eorne	r4, r6, r7	@ x, sign, tmp150
	strh	r4, [r0, r3]	@ movhi	@ x,* ivtmp.836
	ldrsh	r4, [r1, ip]	@ tmp170,
	ldrsh	r3, [r0, ip]	@ tmp171,
	add	r3, r4, r3	@ x, tmp170, tmp171
	mov	r4, r3, asr #31	@ sign, x,
	cmp	r4, r3, asr #15	@ sign, x,
	eorne	r3, r4, r7	@ x, sign, tmp150
	cmp	r2, r5	@ samples, i
	strh	r3, [r0, ip]	@ movhi	@ x,
	add	r3, ip, #2	@ ivtmp.836, tmp155,
	bhi	.L430	@,
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	UTIL_MixerPro, .-UTIL_MixerPro
	.align	2
	.global	UTIL_ChannelModeProcess
	.type	UTIL_ChannelModeProcess, %function
UTIL_ChannelModeProcess:
	.fnstart
.LFB917:
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
	ldr	r3, [r0, #20]	@ <variable>.u32Channels, <variable>.u32Channels
	ldr	ip, [r0, #12]	@ <variable>.u32SamplesPerFrame, <variable>.u32SamplesPerFrame
	sub	r1, r1, #1	@ tmp189, u32ChannelMode,
	mul	r3, ip, r3	@ D.15112, <variable>.u32SamplesPerFrame, <variable>.u32Channels
	cmp	r1, #6	@ tmp189,
	ldrls	pc, [pc, r1, asl #2]	@ tmp189
	b	.L483	@
.L460:
	.word	.L453
	.word	.L454
	.word	.L455
	.word	.L456
	.word	.L457
	.word	.L458
	.word	.L459
.L459:
	cmp	r3, #0	@ D.15112,
	ldr	r1, [r0, #0]	@ temp.983, <variable>.pDataBuf
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r2, #16	@ dstBitDepth,
	beq	.L570	@,
	cmp	r2, #24	@ dstBitDepth,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r3, #1	@ D.15112,
	sub	r2, r3, #1	@ tmp284, D.15112,
	and	r0, r2, #1	@ tmp286, tmp284,
	mov	ip, #0	@ tmp221,
	mov	r2, #1	@ i.990,
	str	ip, [r1, #0]	@ tmp221,* temp.983
	ldmlsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r0, #0	@ tmp286,
	beq	.L482	@,
	mov	r2, #2	@ i.990,
	cmp	r3, r2	@ D.15112, i.990
	str	ip, [r1, #4]	@ tmp221,
	ldmlsfd	sp, {r4, r5, fp, sp, pc}	@
.L482:
	add	r0, r2, #1	@ tmp287, i.990,
	str	ip, [r1, r2, asl #2]	@ tmp221,* temp.983
	add	r2, r0, #1	@ i.990, tmp287,
	cmp	r3, r2	@ D.15112, i.990
	str	ip, [r1, r0, asl #2]	@ tmp221,* temp.983
	bhi	.L482	@,
.L483:
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L453:
	cmp	r3, #0	@ D.15112,
	ldr	r1, [r0, #0]	@ D.15113, <variable>.pDataBuf
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r2, #16	@ dstBitDepth,
	beq	.L571	@,
	cmp	r2, #24	@ dstBitDepth,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	movs	r3, r3, lsr #1	@ temp.991, D.15112,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	sub	ip, r3, #1	@ tmp227, temp.991,
	ldr	r2, [r1, #0]	@ tmp194,* D.15113
	ldr	r0, [r1, #4]	@ tmp195,
	and	r4, ip, #1	@ tmp229, tmp227,
#APP
@ 699 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd ip, r2, r0	@ mix, tmp194, tmp195
@ 0 "" 2
	mov	r0, #1	@ i.984,
	cmp	r0, r3	@ i.984, temp.991
	str	ip, [r1, #4]	@ mix,
	add	r2, r1, #8	@ ps32In, D.15113,
	str	ip, [r1, #0]	@ mix,* D.15113
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r4, #0	@ tmp229,
	beq	.L464	@,
	ldr	r1, [r2, #0]	@ tmp384,* ps32In
	ldr	r0, [r2, #4]	@ tmp385,
#APP
@ 699 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd ip, r1, r0	@ mix, tmp384, tmp385
@ 0 "" 2
	mov	r0, #2	@ i.984,
	cmp	r0, r3	@ i.984, temp.991
	str	ip, [r2, #4]	@ mix,
	str	ip, [r2, #0]	@ mix,* ps32In
	add	r2, r2, #8	@ ps32In, ps32In,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
.L464:
	ldmia	r2, {r1, ip}	@ phole ldm
#APP
@ 699 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd r4, r1, ip	@ mix, tmp297, tmp298
@ 0 "" 2
	add	r1, r2, #8	@ tmp230, ps32In,
	str	r4, [r2, #4]	@ mix,
	str	r4, [r2, #0]	@ mix,* ps32In
	add	r0, r0, #1	@ tmp231, i.984,
	ldr	ip, [r2, #8]	@ tmp302,
	ldr	r4, [r1, #4]	@ tmp303,
#APP
@ 699 "/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include/hi_dsp_basicop.h" 1
	qadd ip, ip, r4	@ mix, tmp302, tmp303
@ 0 "" 2
	add	r0, r0, #1	@ i.984, tmp231,
	str	ip, [r2, #8]	@ mix,
	cmp	r0, r3	@ i.984, temp.991
	str	ip, [r1, #4]	@ mix,
	add	r2, r1, #8	@ ps32In, tmp230,
	bcc	.L464	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L454:
	cmp	r3, #0	@ D.15112,
	ldr	ip, [r0, #0]	@ temp.978, <variable>.pDataBuf
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r2, #16	@ dstBitDepth,
	beq	.L572	@,
	cmp	r2, #24	@ dstBitDepth,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	movs	r3, r3, lsr #1	@ temp.992, D.15112,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	ldr	r2, [ip, #0]	@ tmp198,* temp.978
	mov	r0, #1	@ i.985,
	cmp	r0, r3	@ i.985, temp.992
	sub	r1, r3, #1	@ tmp237, temp.992,
	and	r4, r1, r0	@ tmp239, tmp237,
	add	r1, ip, #8	@ ps32In, temp.978,
	str	r2, [ip, #4]	@ tmp198,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r4, #0	@ tmp239,
	beq	.L467	@,
	ldr	r2, [r1, #0]	@ tmp388,* ps32In
	mov	r0, #2	@ i.985,
	cmp	r0, r3	@ i.985, temp.992
	str	r2, [r1, #4]	@ tmp388,
	add	r1, r1, #8	@ ps32In, ps32In,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
.L467:
	ldr	r4, [r1, #0]	@ tmp313,* ps32In
	add	r0, r0, #2	@ i.985, i.985,
	ldr	ip, [r1, #8]	@ tmp316,
	add	r2, r1, #8	@ tmp240, ps32In,
	cmp	r0, r3	@ i.985, temp.992
	str	r4, [r1, #4]	@ tmp313,
	add	r1, r2, #8	@ ps32In, tmp240,
	str	ip, [r2, #4]	@ tmp316,
	bcc	.L467	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L455:
	cmp	r3, #0	@ D.15112,
	ldr	r1, [r0, #0]	@ temp.979, <variable>.pDataBuf
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r2, #16	@ dstBitDepth,
	beq	.L573	@,
	cmp	r2, #24	@ dstBitDepth,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	movs	r3, r3, lsr #1	@ temp.993, D.15112,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	ldr	ip, [r1, #4]	@ tmp201,
	mov	r0, #1	@ i.986,
	cmp	r0, r3	@ i.986, temp.993
	mov	r2, r1	@ ps32In, temp.979
	sub	r1, r3, #1	@ tmp247, temp.993,
	str	ip, [r2], #8	@ tmp201,
	and	r1, r1, r0	@ tmp249, tmp247,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r1, #0	@ tmp249,
	beq	.L470	@,
	ldr	r1, [r2, #4]	@ tmp390,
	mov	r0, #2	@ i.986,
	cmp	r0, r3	@ i.986, temp.993
	str	r1, [r2], #8	@ tmp390,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
.L470:
	ldr	ip, [r2, #4]	@ tmp325,
	mov	r1, r2	@ tmp250, ps32In
	add	r0, r0, #2	@ i.986, i.986,
	cmp	r0, r3	@ i.986, temp.993
	str	ip, [r1], #8	@ tmp325,
	ldr	ip, [r1, #4]	@ tmp328,
	str	ip, [r2, #8]	@ tmp328,
	add	r2, r1, #8	@ ps32In, tmp250,
	bcc	.L470	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L456:
	cmp	r3, #0	@ D.15112,
	ldr	ip, [r0, #0]	@ temp.980, <variable>.pDataBuf
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r2, #16	@ dstBitDepth,
	beq	.L574	@,
	cmp	r2, #24	@ dstBitDepth,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	movs	r3, r3, lsr #1	@ temp.994, D.15112,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	ldr	r5, [ip, #0]	@ data,* temp.980
	mov	r0, #1	@ i.987,
	ldr	r2, [ip, #4]	@ tmp204,
	cmp	r0, r3	@ i.987, temp.994
	sub	r4, r3, #1	@ tmp257, temp.994,
	add	r1, ip, #8	@ ps32In, temp.980,
	str	r5, [ip, #4]	@ data,
	and	r4, r4, r0	@ tmp259, tmp257,
	str	r2, [ip, #0]	@ tmp204,* temp.980
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r4, #0	@ tmp259,
	beq	.L473	@,
	ldr	ip, [r1, #0]	@ data,* ps32In
	mov	r0, #2	@ i.987,
	ldr	r2, [r1, #4]	@ tmp394,
	cmp	r0, r3	@ i.987, temp.994
	stmia	r1, {r2, ip}	@ phole stm
	add	r1, r1, #8	@ ps32In, ps32In,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
.L473:
	ldr	r4, [r1, #4]	@ tmp340,
	add	r2, r1, #8	@ tmp260, ps32In,
	ldr	r5, [r1, #0]	@ data,* ps32In
	add	r0, r0, #2	@ i.987, i.987,
	ldr	ip, [r1, #8]	@ data,
	cmp	r0, r3	@ i.987, temp.994
	stmia	r1, {r4, r5}	@ phole stm
	ldr	r4, [r2, #4]	@ tmp344,
	str	r4, [r1, #8]	@ tmp344,
	add	r1, r2, #8	@ ps32In, tmp260,
	str	ip, [r2, #4]	@ data,
	bcc	.L473	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L457:
	cmp	r3, #0	@ D.15112,
	ldr	r1, [r0, #0]	@ temp.981, <variable>.pDataBuf
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r2, #16	@ dstBitDepth,
	beq	.L575	@,
	cmp	r2, #24	@ dstBitDepth,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	movs	r3, r3, lsr #1	@ temp.995, D.15112,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	mov	r2, #1	@ i.988,
	cmp	r2, r3	@ i.988, temp.995
	sub	r0, r3, #1	@ tmp266, temp.995,
	mov	ip, #0	@ tmp219,
	and	r0, r0, r2	@ tmp268, tmp266,
	str	ip, [r1, #0]	@ tmp219,* temp.981
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r0, #0	@ tmp268,
	beq	.L476	@,
	mov	r2, #2	@ i.988,
	cmp	r2, r3	@ i.988, temp.995
	str	ip, [r1, #8]	@ tmp219,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
.L476:
	add	r0, r2, #1	@ tmp269, i.988,
	str	ip, [r1, r2, asl #3]	@ tmp219,* temp.981
	add	r2, r0, #1	@ i.988, tmp269,
	cmp	r2, r3	@ i.988, temp.995
	str	ip, [r1, r0, asl #3]	@ tmp219,* temp.981
	bcc	.L476	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L458:
	cmp	r3, #0	@ D.15112,
	ldr	r1, [r0, #0]	@ temp.982, <variable>.pDataBuf
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r2, #16	@ dstBitDepth,
	beq	.L576	@,
	cmp	r2, #24	@ dstBitDepth,
	ldmnefd	sp, {r4, r5, fp, sp, pc}	@
	movs	r3, r3, lsr #1	@ temp.996, D.15112,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	mov	r2, #1	@ i.989,
	cmp	r2, r3	@ i.989, temp.996
	sub	ip, r3, #1	@ tmp275, temp.996,
	add	r0, r1, #8	@ ps32In, temp.982,
	and	r4, ip, r2	@ tmp277, tmp275,
	mov	ip, #0	@ tmp220,
	str	ip, [r1, #4]	@ tmp220,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r4, #0	@ tmp277,
	beq	.L479	@,
	mov	r2, #2	@ i.989,
	cmp	r2, r3	@ i.989, temp.996
	str	ip, [r0, #4]	@ tmp220,
	add	r0, r0, #8	@ ps32In, ps32In,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
.L479:
	add	r2, r2, #2	@ i.989, i.989,
	add	r1, r0, #8	@ tmp278, ps32In,
	cmp	r2, r3	@ i.989, temp.996
	str	ip, [r0, #4]	@ tmp220,
	str	ip, [r1, #4]	@ tmp220,
	add	r0, r1, #8	@ ps32In, tmp278,
	bcc	.L479	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L570:
	cmp	r3, #1	@ D.15112,
	sub	ip, r3, #1	@ tmp280, D.15112,
	mov	r2, #0	@ movhi	@,
	and	r0, ip, #1	@ tmp282, tmp280,
	strh	r2, [r1, #0]	@ movhi	@,* temp.983
	mov	r2, #1	@ i,
	ldmlsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r0, #0	@ tmp282,
	beq	.L481	@,
	mov	ip, #2	@ tmp399,
	cmp	r3, ip	@ D.15112, i
	mov	r5, #0	@ movhi	@,
	mov	r2, ip	@ i, tmp399
	strh	r5, [r1, ip]	@ movhi	@,
	ldmlsfd	sp, {r4, r5, fp, sp, pc}	@
.L481:
	add	r4, r2, #1	@ tmp283, i,
	mov	ip, r2, asl #1	@ tmp366, i,
	add	r2, r4, #1	@ i, tmp283,
	mov	r0, r4, asl #1	@ tmp368, tmp283,
	cmp	r3, r2	@ D.15112, i
	mov	r4, #0	@ movhi	@,
	strh	r4, [r1, ip]	@ movhi	@,
	strh	r4, [r1, r0]	@ movhi	@,
	bhi	.L481	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L572:
	movs	r3, r3, lsr #1	@ D.15923, D.15112,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	ldrh	r2, [ip, #0]	@,* temp.978
	cmp	r3, #1	@ D.15923,
	sub	r1, r3, #1	@ tmp232, D.15923,
	and	r0, r1, #1	@ tmp234, tmp232,
	mov	r1, #1	@ i,
	strh	r2, [ip, #2]	@ movhi	@,
	add	r2, ip, #4	@ ps16In, temp.978,
	ldmlsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r0, #0	@ tmp234,
	beq	.L466	@,
	ldrh	r5, [r2, #0]	@,* ps16In
	mov	r1, #2	@ i,
	cmp	r3, r1	@ D.15923, i
	strh	r5, [r2, #2]	@ movhi	@,
	add	r2, r2, #4	@ ps16In, ps16In,
	ldmlsfd	sp, {r4, r5, fp, sp, pc}	@
.L466:
	ldrh	r4, [r2, #0]	@,* ps16In
	add	r1, r1, #2	@ i, i,
	ldrh	ip, [r2, #4]	@,
	add	r0, r2, #4	@ tmp235, ps16In,
	cmp	r3, r1	@ D.15923, i
	strh	r4, [r2, #2]	@ movhi	@,
	add	r2, r0, #4	@ ps16In, tmp235,
	strh	ip, [r0, #2]	@ movhi	@,
	bhi	.L466	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L571:
	movs	r5, r3, lsr #1	@ D.15911, D.15112,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	tst	r5, #1	@ D.15911,
	mov	r2, r1	@ ps16In, D.15113
	mov	ip, #0	@ i,
	movw	r4, #32767	@ tmp218,
	bne	.L463	@,
	ldrsh	r3, [r1, #2]	@ tmp375,
	ldrsh	r0, [r1, #0]	@ tmp376,* D.15113
	add	ip, r3, r0	@ x, tmp375, tmp376
	mov	r2, ip, asr #31	@ sign, x,
	cmp	r2, ip, asr #15	@ sign, x,
	eorne	ip, r2, r4	@ x, sign, tmp218
	add	r2, r1, #4	@ ps16In, D.15113,
	uxth	r3, ip	@ mix, x
	mov	ip, #1	@ i,
	strh	r3, [r1, #2]	@ movhi	@ mix,
	strh	r3, [r1, #0]	@ movhi	@ mix,* D.15113
.L463:
	ldrsh	r3, [r2, #0]	@ tmp191,* ps16In
	add	ip, ip, #1	@ tmp225, i,
	ldrsh	r1, [r2, #2]	@ tmp190,
	add	r0, r2, #4	@ tmp226, ps16In,
	add	r1, r1, r3	@ x, tmp190, tmp191
	mov	r3, r1, asr #31	@ sign, x,
	cmp	r3, r1, asr #15	@ sign, x,
	eorne	r1, r3, r4	@ x, sign, tmp218
	cmp	r5, ip	@ D.15911, tmp225
	uxth	r1, r1	@ mix, x
	strh	r1, [r2, #2]	@ movhi	@ mix,
	strh	r1, [r2, #0]	@ movhi	@ mix,* ps16In
	ldmlsfd	sp, {r4, r5, fp, sp, pc}	@
	ldrsh	r3, [r2, #4]	@ tmp291,
	add	ip, ip, #1	@ i, tmp225,
	ldrsh	r1, [r0, #2]	@ tmp290,
	add	r1, r1, r3	@ x, tmp290, tmp291
	mov	r2, r1, asr #31	@ sign, x,
	cmp	r2, r1, asr #15	@ sign, x,
	eorne	r1, r2, r4	@ x, sign, tmp218
	add	r2, r0, #4	@ ps16In, tmp226,
	uxth	r1, r1	@ mix, x
	strh	r1, [r0, #2]	@ movhi	@ mix,
	strh	r1, [r0, #0]	@ movhi	@ mix,
	b	.L463	@
.L576:
	movs	r3, r3, lsr #1	@ D.15964, D.15112,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	mov	r2, #1	@ i,
	cmp	r2, r3	@ i, D.15964
	sub	ip, r3, #1	@ tmp270, D.15964,
	mov	r5, #0	@ movhi	@,
	and	r0, ip, r2	@ tmp272, tmp270,
	strh	r5, [r1, #2]	@ movhi	@,
	add	r1, r1, #4	@ ps16In, temp.982,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r0, #0	@ tmp272,
	beq	.L478	@,
	mov	r2, #2	@ i,
	cmp	r2, r3	@ i, D.15964
	mov	r4, #0	@ movhi	@,
	strh	r4, [r1, #2]	@ movhi	@,
	add	r1, r1, #4	@ ps16In, ps16In,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
.L478:
	add	r2, r2, #2	@ i, i,
	add	r0, r1, #4	@ tmp274, ps16In,
	cmp	r2, r3	@ i, D.15964
	mov	ip, #0	@ movhi	@,
	strh	ip, [r1, #2]	@ movhi	@,
	add	r1, r0, #4	@ ps16In, tmp274,
	strh	ip, [r0, #2]	@ movhi	@,
	bcc	.L478	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L575:
	movs	r3, r3, lsr #1	@ D.15956, D.15112,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	mov	r2, #1	@ i,
	cmp	r2, r3	@ i, D.15956
	sub	r0, r3, #1	@ tmp262, D.15956,
	mov	r5, #0	@ movhi	@,
	and	r0, r0, r2	@ tmp264, tmp262,
	strh	r5, [r1, #0]	@ movhi	@,* temp.981
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r0, #0	@ tmp264,
	beq	.L475	@,
	mov	r2, #2	@ i,
	cmp	r2, r3	@ i, D.15956
	mov	r0, #0	@ movhi	@,
	strh	r0, [r1, #4]	@ movhi	@,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
.L475:
	add	r4, r2, #1	@ tmp265, i,
	mov	ip, r2, asl #2	@ tmp346, i,
	add	r2, r4, #1	@ i, tmp265,
	mov	r0, r4, asl #2	@ tmp348, tmp265,
	cmp	r2, r3	@ i, D.15956
	mov	r4, #0	@ movhi	@,
	strh	r4, [r1, ip]	@ movhi	@,
	strh	r4, [r1, r0]	@ movhi	@,
	bcc	.L475	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L574:
	movs	r3, r3, lsr #1	@ D.15947, D.15112,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	ldrh	r2, [ip, #0]	@ data,* temp.980
	mov	r0, #1	@ i,
	ldrh	r4, [ip, #2]	@,
	cmp	r0, r3	@ i, D.15947
	sub	r1, r3, #1	@ tmp252, D.15947,
	strh	r2, [ip, #2]	@ movhi	@ data,
	and	r1, r1, r0	@ tmp254, tmp252,
	strh	r4, [ip, #0]	@ movhi	@,* temp.980
	add	r2, ip, #4	@ ps16In, temp.980,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	r1, #0	@ tmp254,
	beq	.L472	@,
	ldrh	r1, [r2, #0]	@ data,* ps16In
	mov	r0, #2	@ i,
	ldrh	ip, [r2, #2]	@,
	cmp	r0, r3	@ i, D.15947
	strh	r1, [r2, #2]	@ movhi	@ data,
	strh	ip, [r2, #0]	@ movhi	@,* ps16In
	add	r2, r2, #4	@ ps16In, ps16In,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
.L472:
	ldrh	r4, [r2, #0]	@ data,* ps16In
	add	r1, r2, #4	@ tmp255, ps16In,
	ldrh	r5, [r2, #2]	@,
	add	r0, r0, #2	@ i, i,
	ldrh	ip, [r2, #4]	@ data,
	cmp	r0, r3	@ i, D.15947
	strh	r4, [r2, #2]	@ movhi	@ data,
	strh	r5, [r2, #0]	@ movhi	@,* ps16In
	ldrh	r4, [r1, #2]	@,
	strh	r4, [r2, #4]	@ movhi	@,
	add	r2, r1, #4	@ ps16In, tmp255,
	strh	ip, [r1, #2]	@ movhi	@ data,
	bcc	.L472	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L573:
	movs	r3, r3, lsr #1	@ D.15934, D.15112,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
	mov	r2, r1	@ ps16In, temp.979
	ldrh	r1, [r1, #2]	@,
	mov	r0, #1	@ i,
	cmp	r0, r3	@ i, D.15934
	sub	ip, r3, #1	@ tmp242, D.15934,
	strh	r1, [r2], #4	@ movhi	@,
	and	ip, ip, r0	@ tmp244, tmp242,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
	cmp	ip, #0	@ tmp244,
	beq	.L469	@,
	ldrh	ip, [r2, #2]	@ tmp389,
	mov	r0, #2	@ i,
	cmp	r0, r3	@ i, D.15934
	strh	ip, [r2], #4	@ movhi	@ tmp389,
	ldmcsfd	sp, {r4, r5, fp, sp, pc}	@
.L469:
	ldrh	r5, [r2, #2]	@,
	mov	r1, r2	@ tmp245, ps16In
	add	r0, r0, #2	@ i, i,
	cmp	r0, r3	@ i, D.15934
	strh	r5, [r1], #4	@ movhi	@,
	ldrh	ip, [r1, #2]	@,
	strh	ip, [r2, #4]	@ movhi	@,
	add	r2, r1, #4	@ ps16In, tmp245,
	bcc	.L469	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	UTIL_ChannelModeProcess, .-UTIL_ChannelModeProcess
	.align	2
	.global	FADE_Active
	.type	FADE_Active, %function
FADE_Active:
	.fnstart
.LFB922:
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
	cmp	r0, #0	@ hFade
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r2, #0	@ u32FadeMs,
	str	r2, [r0, #12]	@ u32FadeMs, <variable>.u32FadeMs
	mov	r3, #0	@ tmp137,
	str	r3, [r0, #20]	@ tmp137, <variable>.u32FadeCnt
	ldrne	ip, [r0, #8]	@ <variable>.u32InRate, <variable>.u32InRate
	movwne	r3, #:lower16:-819967583	@ tmp143,
	movtne	r3, #:upper16:-819967583	@ tmp143,
	streq	r2, [r0, #24]	@ u32FadeMs, <variable>.u32FadeStep
	str	r1, [r0, #32]	@ enUserFadeStauts, <variable>.enCurnFadeStauts
	mulne	r2, ip, r2	@ tmp139, <variable>.u32InRate, u32FadeMs
	umullne	ip, r3, r3, r2	@, tmp142, tmp143, tmp139
	movne	r3, r3, lsr #16	@ tmp141, tmp142,
	addne	r3, r3, #1	@ tmp144, tmp141,
	strne	r3, [r0, #24]	@ tmp144, <variable>.u32FadeStep
	cmp	r1, #1	@ enUserFadeStauts,
	beq	.L583	@,
	cmp	r1, #2	@ enUserFadeStauts,
	moveq	r3, #18	@ tmp147,
	streq	r3, [r0, #16]	@ tmp147, <variable>.u32FadeCurnCoefIdx
	ldmfd	sp, {fp, sp, pc}	@
.L583:
	mov	r1, #99	@ tmp145,
	mov	r3, #0	@ tmp146,
	str	r1, [r0, #16]	@ tmp145, <variable>.u32FadeCurnCoefIdx
	str	r3, [r0, #28]	@ tmp146, <variable>.bStartFade
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FADE_Active, .-FADE_Active
	.align	2
	.global	FADE_Flush
	.type	FADE_Flush, %function
FADE_Flush:
	.fnstart
.LFB920:
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
	movw	ip, #:lower16:191999	@ tmp142,
	sub	r4, r1, #1	@ tmp141, inRate,
	movt	ip, #:upper16:191999	@ tmp142,
	cmp	r4, ip	@ tmp141, tmp142
	mov	ip, r0	@ hFade, hFade
	ldmhifd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r2, #24	@ BitPerSample,
	cmpne	r2, #16	@, BitPerSample,
	ldmnefd	sp, {r3, r4, fp, sp, pc}	@
	sub	r0, r3, #1	@ tmp150, Channels,
	cmp	r3, #8	@ Channels,
	cmpne	r0, #1	@, tmp150,
	ldmhifd	sp, {r3, r4, fp, sp, pc}	@
	cmp	ip, #0	@ hFade,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	ldr	r0, [ip, #4]	@ <variable>.u32Channels, <variable>.u32Channels
	ldr	r4, [ip, #0]	@ D.15208, <variable>.u32BitPerSample
	cmp	r3, r0	@ Channels, <variable>.u32Channels
	movne	r4, #1	@ isChange,
	beq	.L590	@,
.L587:
	ldr	r0, [ip, #8]	@ <variable>.u32InRate, <variable>.u32InRate
	cmp	r0, r1	@ <variable>.u32InRate, inRate
	beq	.L591	@,
.L588:
	str	r2, [ip, #0]	@ BitPerSample, <variable>.u32BitPerSample
	mov	r0, ip	@, hFade
	str	r1, [ip, #8]	@ inRate, <variable>.u32InRate
	str	r3, [ip, #4]	@ Channels, <variable>.u32Channels
	ldr	r1, [ip, #32]	@, <variable>.enCurnFadeStauts
	ldr	r2, [ip, #12]	@, <variable>.u32FadeMs
	bl	FADE_Active	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L590:
	subs	r4, r2, r4	@ isChange, BitPerSample, D.15208
	movne	r4, #1	@ isChange
	b	.L587	@
.L591:
	cmp	r4, #0	@ isChange,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	b	.L588	@
	.fnend
	.size	FADE_Flush, .-FADE_Flush
	.align	2
	.global	FADE_InProcess
	.type	FADE_InProcess, %function
FADE_InProcess:
	.fnstart
.LFB923:
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
	cmp	r0, #0	@ hFade
	beq	.L619	@,
	ldr	r3, [r0, #32]	@ <variable>.enCurnFadeStauts, <variable>.enCurnFadeStauts
	cmp	r3, #0	@ <variable>.enCurnFadeStauts,
	beq	.L619	@,
	cmp	r2, #0	@ samples,
	ldr	sl, [r0, #4]	@ ivtmp.1082, <variable>.u32Channels
	beq	.L619	@,
	sub	ip, r2, #1	@ ivtmp.1103, samples,
	movw	r4, #:lower16:8388607	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	movt	r4, #:upper16:8388607	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	str	r4, [fp, #-48]	@, %sfp
	mov	r5, sl, asl #2	@, ivtmp.1082,
	mov	r4, sl, asl #1	@, ivtmp.1082,
	str	r2, [fp, #-56]	@, %sfp
	str	r4, [fp, #-64]	@, %sfp
	str	r5, [fp, #-60]	@, %sfp
.L618:
	ldr	r3, [r0, #28]	@ <variable>.bStartFade, <variable>.bStartFade
	cmp	r3, #0	@ <variable>.bStartFade,
	ldrne	r2, [r0, #0]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
	beq	.L697	@,
	ldr	r3, [r0, #16]	@ <variable>.u32FadeCurnCoefIdx, <variable>.u32FadeCurnCoefIdx
	cmp	r2, #16	@ <variable>.u32BitPerSample,
	ldr	r8, [fp, #-56]	@, %sfp
	ldr	r3, [r8, r3, asl #2]	@ Volume, g_u32VolCoef
	beq	.L602	@,
.L707:
	cmp	r2, #24	@ <variable>.u32BitPerSample,
	beq	.L698	@,
.L601:
	ldr	r3, [r0, #20]	@ <variable>.u32FadeCnt, <variable>.u32FadeCnt
	ldr	r2, [r0, #24]	@ <variable>.u32FadeStep, <variable>.u32FadeStep
	add	r3, r3, #1	@ D.15283, <variable>.u32FadeCnt,
	str	r3, [r0, #20]	@ D.15283, <variable>.u32FadeCnt
	cmp	r3, r2	@ D.15283, <variable>.u32FadeStep
	beq	.L699	@,
.L605:
	cmp	ip, #0	@ ivtmp.1103,
	sub	ip, ip, #1	@ ivtmp.1111, ivtmp.1103,
	bne	.L618	@,
.L619:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L698:
	cmp	sl, #0	@ ivtmp.1082,
	beq	.L613	@,
	cmp	r3, #0	@ Volume,
	sub	r6, sl, #1	@ tmp229, ivtmp.1082,
	and	r6, r6, #1	@ tmp230, tmp229,
	mov	r4, r3	@ D.16015, Volume
	mov	r5, r4, asr #31	@ D.16015
	ldr	r8, [r1, #0]	@ data,* pInBuf
	bne	.L637	@,
	mov	r8, r3	@ var.1110, Volume
.L638:
	subs	r7, sl, #1	@ ivtmp.1109, ivtmp.1082,
	str	r8, [r1, #0]	@ var.1110,* pInBuf
	mov	r2, #4	@ ivtmp.1088,
	beq	.L613	@,
	cmp	r6, #0	@ tmp230,
	beq	.L688	@,
	cmp	r3, #0	@ Volume,
	ldr	r8, [r1, r2]	@ data,* ivtmp.1088
	moveq	r8, r3	@ var.1110, Volume
	beq	.L642	@,
	mov	r9, r8, asr #31	@ data
	cmp	r3, #8388608	@ Volume,
	mul	r6, r4, r9	@ tmp332, D.16015, data
	mla	r6, r8, r5, r6	@ tmp333, data, D.16015, tmp332
	umull	r8, r9, r4, r8	@ tmp334, D.16015, data
	add	r9, r6, r9	@, tmp333,
	mov	r6, r8, lsr #23	@ tmp337, tmp334,
	orr	r6, r6, r9, asl #9	@, tmp338, tmp337,,
	mov	r8, r6	@ var.1110, tmp338
	bhi	.L700	@,
.L642:
	subs	r7, r7, #1	@ ivtmp.1109, ivtmp.1109,
	str	r8, [r1, r2]	@ var.1110,* ivtmp.1088
	add	r2, r2, #4	@ ivtmp.1088, ivtmp.1088,
	beq	.L613	@,
.L688:
	str	ip, [fp, #-52]	@ ivtmp.1103, %sfp
	mov	r8, r7	@ ivtmp.1109, ivtmp.1109
	b	.L617	@
.L702:
	mov	r6, r3	@ var.1110, Volume
.L647:
	subs	r8, r7, #1	@ ivtmp.1109, tmp231,
	str	r6, [r1, ip]	@ var.1110,
	add	r2, ip, #4	@ ivtmp.1088, tmp232,
	beq	.L701	@,
.L617:
	cmp	r3, #0	@ Volume,
	ldr	r6, [r1, r2]	@ data,* ivtmp.1088
	moveq	r7, r3	@ var.1110, Volume
	beq	.L615	@,
	mov	r7, r6, asr #31	@ data
	cmp	r3, #8388608	@ Volume,
	mul	ip, r4, r7	@ tmp184, D.16015, data
	mla	ip, r6, r5, ip	@ tmp249, data, D.16015, tmp184
	umull	r6, r7, r4, r6	@ tmp185, D.16015, data
	add	r7, ip, r7	@, tmp249,
	mov	ip, r6, lsr #23	@ tmp207, tmp185,
	orr	ip, ip, r7, asl #9	@, tmp251, tmp207,,
	mov	r7, ip	@ var.1110, tmp251
	bls	.L615	@,
	mov	ip, ip, asr #8	@ tmp189, tmp251,
	mov	r6, ip	@ tmp190, tmp189
	mov	r7, r6, asr #31	@ tmp190
	mul	ip, r6, r5	@ tmp192, tmp190, D.16015
	mla	ip, r4, r7, ip	@ tmp252, D.16015,, tmp192
	umull	r6, r7, r6, r4	@ tmp193, tmp190, D.16015
	add	r7, ip, r7	@, tmp252,
	mov	ip, r6, lsr #23	@ D.16017, tmp193,
	orr	ip, ip, r7, asl #9	@, var, D.16017,,
	mov	r6, ip, asr #31	@ sign, var,
	cmp	r6, ip, asr #23	@ sign, var,
	ldrne	r9, [fp, #-48]	@, %sfp
	eorne	ip, r6, r9	@ var, sign,
	mov	r7, ip, asl #8	@ var.1110, var,
.L615:
	add	ip, r2, #4	@ tmp232, ivtmp.1088,
	cmp	r3, #0	@ Volume,
	str	r7, [r1, r2]	@ var.1110,* ivtmp.1088
	sub	r7, r8, #1	@ tmp231, ivtmp.1109,
	ldr	r8, [r1, ip]	@ data,
	beq	.L702	@,
	mov	r9, r8, asr #31	@ data
	cmp	r3, #8388608	@ Volume,
	mul	r2, r4, r9	@ tmp356, D.16015, data
	mla	r6, r8, r5, r2	@ tmp357, data, D.16015, tmp356
	umull	r8, r9, r4, r8	@ tmp358, D.16015, data
	add	r9, r6, r9	@, tmp357,
	mov	r2, r8, lsr #23	@ tmp361, tmp358,
	orr	r2, r2, r9, asl #9	@, tmp362, tmp361,,
	mov	r6, r2	@ var.1110, tmp362
	bls	.L647	@,
	mov	r2, r2, asr #8	@ tmp364, tmp362,
	mov	r8, r2	@ tmp365, tmp364
	mov	r9, r8, asr #31	@ tmp365
	mul	r6, r8, r5	@ tmp367, tmp365, D.16015
	mla	r2, r4, r9, r6	@ tmp368, D.16015,, tmp367
	umull	r8, r9, r8, r4	@ tmp369, tmp365, D.16015
	add	r9, r2, r9	@, tmp368,
	mov	r6, r8, lsr #23	@ D.16017, tmp369,
	orr	r2, r6, r9, asl #9	@, var, D.16017,,
	mov	r6, r2, asr #31	@ sign, var,
	cmp	r6, r2, asr #23	@ sign, var,
	ldrne	r8, [fp, #-48]	@, %sfp
	eorne	r2, r6, r8	@ var, sign,
.L648:
	subs	r8, r7, #1	@ ivtmp.1109, tmp231,
	mov	r6, r2, asl #8	@ var.1110, var,
	add	r2, ip, #4	@ ivtmp.1088, tmp232,
	str	r6, [r1, ip]	@ var.1110,
	bne	.L617	@,
.L701:
	ldr	ip, [fp, #-52]	@ ivtmp.1103, %sfp
.L613:
	ldr	r3, [fp, #-60]	@, %sfp
	ldr	r2, [r0, #24]	@ <variable>.u32FadeStep, <variable>.u32FadeStep
	add	r1, r1, r3	@ pInBuf, pInBuf,
	ldr	r3, [r0, #20]	@ <variable>.u32FadeCnt, <variable>.u32FadeCnt
	add	r3, r3, #1	@ D.15283, <variable>.u32FadeCnt,
	str	r3, [r0, #20]	@ D.15283, <variable>.u32FadeCnt
	cmp	r3, r2	@ D.15283, <variable>.u32FadeStep
	bne	.L605	@,
.L699:
	ldr	r3, [r0, #32]	@ <variable>.enCurnFadeStauts, <variable>.enCurnFadeStauts
	mov	r4, #0	@,
	str	r4, [r0, #20]	@, <variable>.u32FadeCnt
	cmp	r3, #1	@ <variable>.enCurnFadeStauts,
	bne	.L605	@,
	ldr	r3, [r0, #16]	@ <variable>.u32FadeCurnCoefIdx, <variable>.u32FadeCurnCoefIdx
	sub	r3, r3, #1	@ D.15289, <variable>.u32FadeCurnCoefIdx,
	str	r3, [r0, #16]	@ D.15289, <variable>.u32FadeCurnCoefIdx
	cmp	r3, #18	@ D.15289,
	streq	r4, [r0, #32]	@, <variable>.enCurnFadeStauts
	b	.L605	@
.L697:
	ldr	r4, [r0, #4]	@ D.15975, <variable>.u32Channels
	cmp	r4, #0	@ D.15975,
	beq	.L595	@,
	ldr	r2, [r0, #0]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
	sub	r5, r4, #1	@ tmp233, D.15975,
	and	r5, r5, #1	@ tmp235, tmp233,
	cmp	r2, #16	@ <variable>.u32BitPerSample,
	beq	.L703	@,
	cmp	r2, #24	@ <variable>.u32BitPerSample,
	beq	.L704	@,
.L651:
	mov	r3, #1	@ i,
	cmp	r3, r4	@ i, D.15975
	bcs	.L600	@,
	cmp	r5, #0	@ tmp235,
	beq	.L599	@,
.L696:
	cmp	r2, #16	@ <variable>.u32BitPerSample,
	beq	.L665	@,
	cmp	r2, #24	@ <variable>.u32BitPerSample,
	beq	.L705	@,
.L658:
	add	r3, r3, #1	@ i, tmp236,
	cmp	r3, r4	@ i, D.15975
	bcs	.L600	@,
.L599:
	cmp	r2, #16	@ <variable>.u32BitPerSample,
	add	r3, r3, #1	@ tmp236, i,
	beq	.L706	@,
	cmp	r2, #24	@ <variable>.u32BitPerSample,
	bne	.L696	@,
	ldr	r5, [r1, #0]	@ tmp166,* pInBuf
	cmp	r5, #0	@ tmp166,
	beq	.L696	@,
.L597:
	mov	r7, #1	@,
	str	r7, [r0, #28]	@, <variable>.bStartFade
.L709:
	ldr	r3, [r0, #16]	@ <variable>.u32FadeCurnCoefIdx, <variable>.u32FadeCurnCoefIdx
	cmp	r2, #16	@ <variable>.u32BitPerSample,
	ldr	r8, [fp, #-56]	@, %sfp
	ldr	r3, [r8, r3, asl #2]	@ Volume, g_u32VolCoef
	bne	.L707	@,
.L602:
	cmp	sl, #0	@ ivtmp.1082,
	beq	.L607	@,
	cmp	r3, #0	@ Volume,
	sub	r2, sl, #1	@ tmp225, ivtmp.1082,
	and	r4, r2, #1	@ tmp226, tmp225,
	mov	r6, r3	@ Volume, Volume
	mov	r7, r6, asr #31	@ Volume
	ldrh	r2, [r1, #0]	@ D.16001,* pInBuf
	bne	.L624	@,
	mov	r2, r3	@ D.15999, Volume
.L672:
	subs	r5, sl, #1	@ ivtmp.1108, ivtmp.1082,
	strh	r2, [r1, #0]	@ movhi	@ D.15999,* pInBuf
	mov	r2, #2	@ ivtmp.1072,
	beq	.L607	@,
	cmp	r4, #0	@ tmp226,
	beq	.L686	@,
	cmp	r3, #0	@ Volume,
	ldrh	r4, [r1, r2]	@ D.16001,* ivtmp.1072
	moveq	r4, r3	@ D.15999, Volume
	beq	.L676	@,
	sxth	r4, r4	@ D.16001, D.16001
	cmp	r3, #8388608	@ Volume,
	mov	r8, r4	@ D.16001, D.16001
	mov	r9, r8, asr #31	@ D.16001
	mul	r4, r6, r9	@ tmp278, Volume, D.16001
	mla	r4, r8, r7, r4	@ tmp279, D.16001, Volume, tmp278
	umull	r8, r9, r6, r8	@ tmp280, Volume, D.16001
	add	r9, r4, r9	@, tmp279,
	mov	r4, r8, lsr #23	@ tmp283, tmp280,
	orr	r4, r4, r9, asl #9	@, var, tmp283,,
	bhi	.L708	@,
.L674:
	uxth	r4, r4	@ D.15999, var
.L676:
	subs	r5, r5, #1	@ ivtmp.1108, ivtmp.1108,
	strh	r4, [r1, r2]	@ movhi	@ D.15999,* ivtmp.1072
	add	r2, r2, #2	@ ivtmp.1072, ivtmp.1072,
	beq	.L607	@,
.L686:
	mov	r8, r5	@ ivtmp.1108, ivtmp.1108
	str	ip, [fp, #-52]	@ ivtmp.1103, %sfp
.L612:
	cmp	r3, #0	@ Volume,
	ldrh	r4, [r1, r2]	@ D.16001,* ivtmp.1072
	moveq	r4, r3	@ D.15999, Volume
	beq	.L609	@,
	sxth	r4, r4	@ D.16001, D.16001
	cmp	r3, #8388608	@ Volume,
	mov	r5, r4, asr #31	@ D.16001
	mul	ip, r6, r5	@ tmp175, Volume, D.16001
	mla	ip, r4, r7, ip	@ tmp241, D.16001, Volume, tmp175
	umull	r4, r5, r6, r4	@ tmp176, Volume, D.16001
	add	r5, ip, r5	@, tmp241,
	mov	ip, r4, lsr #23	@ tmp205, tmp176,
	orr	ip, ip, r5, asl #9	@, var, tmp205,,
	bls	.L611	@,
	mov	r4, ip, asr #31	@ sign, var,
	cmp	r4, ip, asr #15	@ sign, var,
	movwne	r5, #32767	@,
	eorne	ip, r4, r5	@ var, sign,
.L611:
	uxth	r4, ip	@ D.15999, var
.L609:
	add	ip, r2, #2	@ tmp227, ivtmp.1072,
	cmp	r3, #0	@ Volume,
	strh	r4, [r1, r2]	@ movhi	@ D.15999,* ivtmp.1072
	sub	r5, r8, #1	@ tmp228, ivtmp.1108,
	ldrh	r8, [r1, ip]	@ D.16001,
	bne	.L633	@,
	mov	r2, r3	@ D.15999, Volume
.L679:
	subs	r8, r5, #1	@ ivtmp.1108, tmp228,
	strh	r2, [r1, ip]	@ movhi	@ D.15999,
	add	r2, ip, #2	@ ivtmp.1072, tmp227,
	bne	.L612	@,
	ldr	ip, [fp, #-52]	@ ivtmp.1103, %sfp
.L607:
	ldr	r7, [fp, #-64]	@, %sfp
	add	r1, r1, r7	@ pInBuf, pInBuf,
	b	.L601	@
.L665:
	ldrsh	r5, [r1, #0]	@ tmp382,* pInBuf
	cmp	r5, #0	@ tmp382,
	bne	.L597	@,
	add	r3, r3, #1	@ i, tmp236,
	cmp	r3, r4	@ i, D.15975
	bcc	.L599	@,
.L600:
	cmp	r2, #16	@ <variable>.u32BitPerSample,
	beq	.L604	@,
	cmp	r2, #24	@ <variable>.u32BitPerSample,
	ldreq	r2, [fp, #-60]	@, %sfp
	addeq	r1, r1, r2	@ pInBuf, pInBuf,
	b	.L605	@
.L705:
	ldr	r5, [r1, #0]	@ tmp381,* pInBuf
	cmp	r5, #0	@ tmp381,
	beq	.L658	@,
	mov	r7, #1	@,
	str	r7, [r0, #28]	@, <variable>.bStartFade
	b	.L709	@
.L706:
	ldrsh	r5, [r1, #0]	@ tmp165,* pInBuf
	cmp	r5, #0	@ tmp165,
	beq	.L696	@,
	mov	r7, #1	@,
	str	r7, [r0, #28]	@, <variable>.bStartFade
	b	.L709	@
.L604:
	ldr	r9, [fp, #-64]	@, %sfp
	add	r1, r1, r9	@ pInBuf, pInBuf,
	b	.L605	@
.L703:
	ldrsh	r3, [r1, #0]	@ tmp378,* pInBuf
	cmp	r3, #0	@ tmp378,
	beq	.L651	@,
	b	.L597	@
.L704:
	ldr	r3, [r1, #0]	@ tmp377,* pInBuf
	cmp	r3, #0	@ tmp377,
	beq	.L651	@,
	b	.L597	@
.L624:
	sxth	r2, r2	@ D.16001, D.16001
	cmp	r3, #8388608	@ Volume,
	mov	r8, r2	@ D.16001, D.16001
	mov	r9, r8, asr #31	@ D.16001
	mul	r5, r6, r9	@ tmp262, Volume, D.16001
	mla	r2, r8, r7, r5	@ tmp263, D.16001, Volume, tmp262
	umull	r8, r9, r6, r8	@ tmp264, Volume, D.16001
	add	r9, r2, r9	@, tmp263,
	mov	r5, r8, lsr #23	@ tmp267, tmp264,
	orr	r2, r5, r9, asl #9	@, var, tmp267,,
	bls	.L670	@,
	mov	r5, r2, asr #31	@ sign, var,
	cmp	r5, r2, asr #15	@ sign, var,
	movwne	r8, #32767	@,
	eorne	r2, r5, r8	@ var, sign,
.L670:
	uxth	r2, r2	@ D.15999, var
	b	.L672	@
.L637:
	mov	r9, r8, asr #31	@ data
	cmp	r3, #8388608	@ Volume,
	mul	r7, r4, r9	@ tmp307, D.16015, data
	mla	r2, r8, r5, r7	@ tmp308, data, D.16015, tmp307
	umull	r8, r9, r4, r8	@ tmp309, D.16015, data
	add	r9, r2, r9	@, tmp308,
	mov	r7, r8, lsr #23	@ tmp312, tmp309,
	orr	r2, r7, r9, asl #9	@, tmp313, tmp312,,
	mov	r8, r2	@ var.1110, tmp313
	bls	.L638	@,
	mov	r7, r2, asr #8	@ tmp315, tmp313,
	mov	r8, r7	@ tmp316, tmp315
	mov	r9, r8, asr #31	@ tmp316
	mul	r2, r8, r5	@ tmp318, tmp316, D.16015
	mla	r7, r4, r9, r2	@ tmp319, D.16015,, tmp318
	umull	r8, r9, r8, r4	@ tmp320, tmp316, D.16015
	add	r9, r7, r9	@, tmp319,
	mov	r2, r8, lsr #23	@ D.16017, tmp320,
	orr	r2, r2, r9, asl #9	@, var, D.16017,,
	mov	r7, r2, asr #31	@ sign, var,
	cmp	r7, r2, asr #23	@ sign, var,
	ldrne	r9, [fp, #-48]	@, %sfp
	eorne	r2, r7, r9	@ var, sign,
.L639:
	mov	r8, r2, asl #8	@ var.1110, var,
	b	.L638	@
.L633:
	sxth	r8, r8	@ D.16001, D.16001
	cmp	r3, #8388608	@ Volume,
	mov	r9, r8, asr #31	@ D.16001
	mul	r2, r6, r9	@ tmp293, Volume, D.16001
	mla	r2, r8, r7, r2	@ tmp294, D.16001, Volume, tmp293
	umull	r8, r9, r6, r8	@ tmp295, Volume, D.16001
	add	r9, r2, r9	@, tmp294,
	mov	r2, r8, lsr #23	@ tmp298, tmp295,
	orr	r2, r2, r9, asl #9	@, var, tmp298,,
	bls	.L677	@,
	mov	r4, r2, asr #31	@ sign, var,
	cmp	r4, r2, asr #15	@ sign, var,
	movwne	r8, #32767	@,
	eorne	r2, r4, r8	@ var, sign,
.L677:
	uxth	r2, r2	@ D.15999, var
	b	.L679	@
.L700:
	mov	r6, r6, asr #8	@ tmp340, tmp338,
	mov	r8, r6	@ tmp341, tmp340
	mov	r9, r8, asr #31	@ tmp341
	mul	r6, r8, r5	@ tmp343, tmp341, D.16015
	mla	r6, r4, r9, r6	@ tmp344, D.16015,, tmp343
	umull	r8, r9, r8, r4	@ tmp345, tmp341, D.16015
	add	r9, r6, r9	@, tmp344,
	mov	r6, r8, lsr #23	@ D.16017, tmp345,
	orr	r6, r6, r9, asl #9	@, var, D.16017,,
	mov	r8, r6, asr #31	@ sign, var,
	cmp	r8, r6, asr #23	@ sign, var,
	ldrne	r9, [fp, #-48]	@, %sfp
	eorne	r6, r8, r9	@ var, sign,
.L643:
	mov	r8, r6, asl #8	@ var.1110, var,
	b	.L642	@
.L708:
	mov	r8, r4, asr #31	@ sign, var,
	cmp	r8, r4, asr #15	@ sign, var,
	movwne	r9, #32767	@,
	eorne	r4, r8, r9	@ var, sign,
	b	.L674	@
.L595:
	ldr	r2, [r0, #0]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
	b	.L600	@
	.fnend
	.size	FADE_InProcess, .-FADE_InProcess
	.align	2
	.global	FADE_OutProcess
	.type	FADE_OutProcess, %function
FADE_OutProcess:
	.fnstart
.LFB924:
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
	cmp	r0, #0	@ hFade
	beq	.L728	@,
	cmp	r2, #0	@ samples,
	ldr	sl, [r0, #4]	@ ivtmp.1150, <variable>.u32Channels
	beq	.L728	@,
	movw	r3, #:lower16:.LANCHOR0	@,
	movw	r4, #:lower16:8388607	@,
	movt	r3, #:upper16:.LANCHOR0	@,
	movt	r4, #:upper16:8388607	@,
	mov	r5, sl, asl #1	@, ivtmp.1150,
	mov	r7, sl, asl #2	@, ivtmp.1150,
	str	r3, [fp, #-48]	@, %sfp
	str	r4, [fp, #-56]	@, %sfp
	str	r5, [fp, #-64]	@, %sfp
	str	r7, [fp, #-60]	@, %sfp
	b	.L727	@
.L784:
	cmp	ip, #24	@ <variable>.u32BitPerSample,
	beq	.L782	@,
.L712:
	ldr	r3, [r0, #20]	@ <variable>.u32FadeCnt, <variable>.u32FadeCnt
	sub	r2, r2, #1	@ samples, samples,
	ldr	ip, [r0, #24]	@ <variable>.u32FadeStep, <variable>.u32FadeStep
	add	r3, r3, #1	@ D.15316, <variable>.u32FadeCnt,
	str	r3, [r0, #20]	@ D.15316, <variable>.u32FadeCnt
	cmp	r3, ip	@ D.15316, <variable>.u32FadeStep
	beq	.L783	@,
.L726:
	cmp	r2, #0	@ samples,
	beq	.L728	@,
.L727:
	ldr	ip, [r0, #0]	@ <variable>.u32BitPerSample, <variable>.u32BitPerSample
	ldr	r3, [r0, #16]	@ <variable>.u32FadeCurnCoefIdx, <variable>.u32FadeCurnCoefIdx
	ldr	r8, [fp, #-48]	@, %sfp
	cmp	ip, #16	@ <variable>.u32BitPerSample,
	ldr	r3, [r8, r3, asl #2]	@ Volume, g_u32VolCoef
	bne	.L784	@,
	cmp	sl, #0	@ ivtmp.1150,
	beq	.L715	@,
	cmp	r3, #0	@ Volume,
	sub	r4, sl, #1	@ tmp213, ivtmp.1150,
	and	r4, r4, #1	@ tmp214, tmp213,
	mov	r6, r3	@ Volume, Volume
	mov	r7, r6, asr #31	@ Volume
	ldrh	r8, [r1, #0]	@ D.16044,* pInBuf
	bne	.L732	@,
	mov	ip, r3	@ D.16042, Volume
.L766:
	subs	r5, sl, #1	@ ivtmp.1175, ivtmp.1150,
	strh	ip, [r1, #0]	@ movhi	@ D.16042,* pInBuf
	mov	ip, #2	@ ivtmp.1140,
	beq	.L715	@,
	cmp	r4, #0	@ tmp214,
	beq	.L779	@,
	cmp	r3, #0	@ Volume,
	ldrh	r8, [r1, ip]	@ D.16044,* ivtmp.1140
	moveq	r4, r3	@ D.16042, Volume
	beq	.L770	@,
	sxth	r8, r8	@ D.16044, D.16044
	cmp	r3, #8388608	@ Volume,
	mov	r9, r8, asr #31	@ D.16044
	mul	r4, r6, r9	@ tmp260, Volume, D.16044
	mla	r4, r8, r7, r4	@ tmp261, D.16044, Volume, tmp260
	umull	r8, r9, r6, r8	@ tmp262, Volume, D.16044
	add	r9, r4, r9	@, tmp261,
	mov	r4, r8, lsr #23	@ tmp265, tmp262,
	orr	r4, r4, r9, asl #9	@, var, tmp265,,
	bls	.L768	@,
	mov	r8, r4, asr #31	@ sign, var,
	cmp	r8, r4, asr #15	@ sign, var,
	movwne	r9, #32767	@,
	eorne	r4, r8, r9	@ var, sign,
.L768:
	uxth	r4, r4	@ D.16042, var
.L770:
	subs	r5, r5, #1	@ ivtmp.1175, ivtmp.1175,
	strh	r4, [r1, ip]	@ movhi	@ D.16042,* ivtmp.1140
	add	ip, ip, #2	@ ivtmp.1140, ivtmp.1140,
	beq	.L715	@,
.L779:
	mov	r8, r5	@ ivtmp.1175, ivtmp.1175
	str	sl, [fp, #-52]	@ ivtmp.1150, %sfp
.L720:
	cmp	r3, #0	@ Volume,
	ldrh	r4, [r1, ip]	@ D.16044,* ivtmp.1140
	moveq	sl, r3	@ D.16042, Volume
	beq	.L717	@,
	sxth	r4, r4	@ D.16044, D.16044
	cmp	r3, #8388608	@ Volume,
	mov	r5, r4, asr #31	@ D.16044
	mul	sl, r6, r5	@ tmp165, Volume, D.16044
	mla	sl, r4, r7, sl	@ tmp223, D.16044, Volume, tmp165
	umull	r4, r5, r6, r4	@ tmp166, Volume, D.16044
	add	r5, sl, r5	@, tmp223,
	mov	sl, r4, lsr #23	@ tmp195, tmp166,
	orr	sl, sl, r5, asl #9	@, var, tmp195,,
	bls	.L719	@,
	mov	r4, sl, asr #31	@ sign, var,
	cmp	r4, sl, asr #15	@ sign, var,
	movwne	r9, #32767	@,
	eorne	sl, r4, r9	@ var, sign,
.L719:
	uxth	sl, sl	@ D.16042, var
.L717:
	add	r4, ip, #2	@ tmp215, ivtmp.1140,
	cmp	r3, #0	@ Volume,
	strh	sl, [r1, ip]	@ movhi	@ D.16042,* ivtmp.1140
	sub	r5, r8, #1	@ tmp216, ivtmp.1175,
	ldrh	r8, [r1, r4]	@ D.16044,
	bne	.L741	@,
	mov	ip, r3	@ D.16042, Volume
.L773:
	subs	r8, r5, #1	@ ivtmp.1175, tmp216,
	strh	ip, [r1, r4]	@ movhi	@ D.16042,
	add	ip, r4, #2	@ ivtmp.1140, tmp215,
	bne	.L720	@,
	ldr	sl, [fp, #-52]	@ ivtmp.1150, %sfp
.L715:
	ldr	ip, [fp, #-64]	@, %sfp
	sub	r2, r2, #1	@ samples, samples,
	ldr	r3, [r0, #20]	@ <variable>.u32FadeCnt, <variable>.u32FadeCnt
	add	r1, r1, ip	@ pInBuf, pInBuf,
	ldr	ip, [r0, #24]	@ <variable>.u32FadeStep, <variable>.u32FadeStep
	add	r3, r3, #1	@ D.15316, <variable>.u32FadeCnt,
	str	r3, [r0, #20]	@ D.15316, <variable>.u32FadeCnt
	cmp	r3, ip	@ D.15316, <variable>.u32FadeStep
	bne	.L726	@,
.L783:
	ldr	ip, [r0, #32]	@ <variable>.enCurnFadeStauts, <variable>.enCurnFadeStauts
	mov	r9, #0	@,
	str	r9, [r0, #20]	@, <variable>.u32FadeCnt
	cmp	ip, #2	@ <variable>.enCurnFadeStauts,
	bne	.L726	@,
	ldr	ip, [r0, #16]	@ <variable>.u32FadeCurnCoefIdx, <variable>.u32FadeCurnCoefIdx
	add	r3, ip, #1	@ D.15323, <variable>.u32FadeCurnCoefIdx,
	str	r3, [r0, #16]	@ D.15323, <variable>.u32FadeCurnCoefIdx
	cmp	r3, #99	@ D.15323,
	streq	r9, [r0, #32]	@, <variable>.enCurnFadeStauts
	cmp	r2, #0	@ samples,
	bne	.L727	@,
.L728:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L741:
	sxth	r8, r8	@ D.16044, D.16044
	cmp	r3, #8388608	@ Volume,
	mov	r9, r8, asr #31	@ D.16044
	mul	ip, r6, r9	@ tmp275, Volume, D.16044
	mla	ip, r8, r7, ip	@ tmp276, D.16044, Volume, tmp275
	umull	r8, r9, r6, r8	@ tmp277, Volume, D.16044
	add	r9, ip, r9	@, tmp276,
	mov	ip, r8, lsr #23	@ tmp280, tmp277,
	orr	ip, ip, r9, asl #9	@, var, tmp280,,
	bls	.L771	@,
	mov	r8, ip, asr #31	@ sign, var,
	cmp	r8, ip, asr #15	@ sign, var,
	movwne	sl, #32767	@,
	eorne	ip, r8, sl	@ var, sign,
.L771:
	uxth	ip, ip	@ D.16042, var
	b	.L773	@
.L782:
	cmp	sl, #0	@ ivtmp.1150,
	beq	.L721	@,
	cmp	r3, #0	@ Volume,
	sub	r6, sl, #1	@ tmp217, ivtmp.1150,
	and	r6, r6, #1	@ tmp218, tmp217,
	mov	r4, r3	@ D.16058, Volume
	mov	r5, r4, asr #31	@ D.16058
	ldr	r8, [r1, #0]	@ data,* pInBuf
	bne	.L745	@,
	mov	r8, r3	@ var.1174, Volume
.L746:
	subs	r7, sl, #1	@ ivtmp.1173, ivtmp.1150,
	str	r8, [r1, #0]	@ var.1174,* pInBuf
	mov	ip, #4	@ ivtmp.1156,
	beq	.L721	@,
	cmp	r6, #0	@ tmp218,
	beq	.L781	@,
	cmp	r3, #0	@ Volume,
	ldr	r8, [r1, ip]	@ data,* ivtmp.1156
	moveq	r8, r3	@ var.1174, Volume
	beq	.L750	@,
	mov	r9, r8, asr #31	@ data
	cmp	r3, #8388608	@ Volume,
	mul	r6, r4, r9	@ tmp314, D.16058, data
	mla	r6, r8, r5, r6	@ tmp315, data, D.16058, tmp314
	umull	r8, r9, r4, r8	@ tmp316, D.16058, data
	add	r9, r6, r9	@, tmp315,
	mov	r6, r8, lsr #23	@ tmp319, tmp316,
	orr	r6, r6, r9, asl #9	@, tmp320, tmp319,,
	mov	r8, r6	@ var.1174, tmp320
	bls	.L750	@,
	mov	r6, r6, asr #8	@ tmp322, tmp320,
	mov	r8, r6	@ tmp323, tmp322
	mov	r9, r8, asr #31	@ tmp323
	mul	r6, r8, r5	@ tmp325, tmp323, D.16058
	mla	r6, r4, r9, r6	@ tmp326, D.16058,, tmp325
	umull	r8, r9, r8, r4	@ tmp327, tmp323, D.16058
	add	r9, r6, r9	@, tmp326,
	mov	r6, r8, lsr #23	@ D.16060, tmp327,
	orr	r6, r6, r9, asl #9	@, var, D.16060,,
	mov	r8, r6, asr #31	@ sign, var,
	cmp	r8, r6, asr #23	@ sign, var,
	ldrne	r9, [fp, #-56]	@, %sfp
	eorne	r6, r8, r9	@ var, sign,
.L751:
	mov	r8, r6, asl #8	@ var.1174, var,
.L750:
	subs	r7, r7, #1	@ ivtmp.1173, ivtmp.1173,
	str	r8, [r1, ip]	@ var.1174,* ivtmp.1156
	add	ip, ip, #4	@ ivtmp.1156, ivtmp.1156,
	beq	.L721	@,
.L781:
	str	sl, [fp, #-52]	@ ivtmp.1150, %sfp
	mov	r8, r7	@ ivtmp.1173, ivtmp.1173
	b	.L725	@
.L786:
	mov	sl, r3	@ var.1174, Volume
.L755:
	subs	r8, r7, #1	@ ivtmp.1173, tmp220,
	str	sl, [r1, r6]	@ var.1174,
	add	ip, r6, #4	@ ivtmp.1156, tmp219,
	beq	.L785	@,
.L725:
	cmp	r3, #0	@ Volume,
	ldr	r6, [r1, ip]	@ data,* ivtmp.1156
	moveq	r7, r3	@ var.1174, Volume
	beq	.L723	@,
	mov	r7, r6, asr #31	@ data
	cmp	r3, #8388608	@ Volume,
	mul	sl, r4, r7	@ tmp174, D.16058, data
	mla	sl, r6, r5, sl	@ tmp231, data, D.16058, tmp174
	umull	r6, r7, r4, r6	@ tmp175, D.16058, data
	add	r7, sl, r7	@, tmp231,
	mov	sl, r6, lsr #23	@ tmp197, tmp175,
	orr	sl, sl, r7, asl #9	@, tmp233, tmp197,,
	mov	r7, sl	@ var.1174, tmp233
	bls	.L723	@,
	mov	r6, sl, asr #8	@ tmp179, tmp233,
	mov	r7, r6, asr #31	@ tmp180
	mul	sl, r6, r5	@ tmp182, tmp180, D.16058
	mla	sl, r4, r7, sl	@ tmp234, D.16058,, tmp182
	umull	r6, r7, r6, r4	@ tmp183, tmp180, D.16058
	add	r7, sl, r7	@, tmp234,
	mov	sl, r6, lsr #23	@ D.16060, tmp183,
	orr	sl, sl, r7, asl #9	@, var, D.16060,,
	mov	r6, sl, asr #31	@ sign, var,
	cmp	r6, sl, asr #23	@ sign, var,
	ldrne	r7, [fp, #-56]	@, %sfp
	eorne	sl, r6, r7	@ var, sign,
	mov	r7, sl, asl #8	@ var.1174, var,
.L723:
	add	r6, ip, #4	@ tmp219, ivtmp.1156,
	cmp	r3, #0	@ Volume,
	str	r7, [r1, ip]	@ var.1174,* ivtmp.1156
	sub	r7, r8, #1	@ tmp220, ivtmp.1173,
	ldr	r8, [r1, r6]	@ data,
	beq	.L786	@,
	mov	r9, r8, asr #31	@ data
	cmp	r3, #8388608	@ Volume,
	mul	sl, r4, r9	@ tmp338, D.16058, data
	mla	ip, r8, r5, sl	@ tmp339, data, D.16058, tmp338
	umull	r8, r9, r4, r8	@ tmp340, D.16058, data
	add	r9, ip, r9	@, tmp339,
	mov	sl, r8, lsr #23	@ tmp343, tmp340,
	orr	ip, sl, r9, asl #9	@, tmp344, tmp343,,
	mov	sl, ip	@ var.1174, tmp344
	bls	.L755	@,
	mov	r8, ip, asr #8	@ tmp346, tmp344,
	mov	r9, r8, asr #31	@ tmp347
	mul	ip, r8, r5	@ tmp349, tmp347, D.16058
	mla	sl, r4, r9, ip	@ tmp350, D.16058,, tmp349
	umull	r8, r9, r8, r4	@ tmp351, tmp347, D.16058
	add	r9, sl, r9	@, tmp350,
	mov	ip, r8, lsr #23	@ D.16060, tmp351,
	orr	ip, ip, r9, asl #9	@, var, D.16060,,
	mov	r8, ip, asr #31	@ sign, var,
	cmp	r8, ip, asr #23	@ sign, var,
	ldrne	sl, [fp, #-56]	@, %sfp
	eorne	ip, r8, sl	@ var, sign,
.L756:
	subs	r8, r7, #1	@ ivtmp.1173, tmp220,
	mov	sl, ip, asl #8	@ var.1174, var,
	add	ip, r6, #4	@ ivtmp.1156, tmp219,
	str	sl, [r1, r6]	@ var.1174,
	bne	.L725	@,
.L785:
	ldr	sl, [fp, #-52]	@ ivtmp.1150, %sfp
.L721:
	ldr	r8, [fp, #-60]	@, %sfp
	add	r1, r1, r8	@ pInBuf, pInBuf,
	b	.L712	@
.L745:
	mov	r9, r8, asr #31	@ data
	cmp	r3, #8388608	@ Volume,
	mul	r7, r4, r9	@ tmp289, D.16058, data
	mla	ip, r8, r5, r7	@ tmp290, data, D.16058, tmp289
	umull	r8, r9, r4, r8	@ tmp291, D.16058, data
	add	r9, ip, r9	@, tmp290,
	mov	r7, r8, lsr #23	@ tmp294, tmp291,
	orr	ip, r7, r9, asl #9	@, tmp295, tmp294,,
	mov	r8, ip	@ var.1174, tmp295
	bls	.L746	@,
	mov	r7, ip, asr #8	@ tmp297, tmp295,
	mov	r8, r7	@ tmp298, tmp297
	mov	r9, r8, asr #31	@ tmp298
	mul	ip, r8, r5	@ tmp300, tmp298, D.16058
	mla	r7, r4, r9, ip	@ tmp301, D.16058,, tmp300
	umull	r8, r9, r8, r4	@ tmp302, tmp298, D.16058
	add	r9, r7, r9	@, tmp301,
	mov	ip, r8, lsr #23	@ D.16060, tmp302,
	orr	ip, ip, r9, asl #9	@, var, D.16060,,
	mov	r7, ip, asr #31	@ sign, var,
	cmp	r7, ip, asr #23	@ sign, var,
	ldrne	r8, [fp, #-56]	@, %sfp
	eorne	ip, r7, r8	@ var, sign,
.L747:
	mov	r8, ip, asl #8	@ var.1174, var,
	b	.L746	@
.L732:
	sxth	r8, r8	@ D.16044, D.16044
	cmp	r3, #8388608	@ Volume,
	mov	r9, r8, asr #31	@ D.16044
	mul	r5, r6, r9	@ tmp244, Volume, D.16044
	mla	ip, r8, r7, r5	@ tmp245, D.16044, Volume, tmp244
	umull	r8, r9, r6, r8	@ tmp246, Volume, D.16044
	add	r9, ip, r9	@, tmp245,
	mov	r5, r8, lsr #23	@ tmp249, tmp246,
	orr	ip, r5, r9, asl #9	@, var, tmp249,,
	bls	.L764	@,
	mov	r5, ip, asr #31	@ sign, var,
	cmp	r5, ip, asr #15	@ sign, var,
	movwne	r8, #32767	@,
	eorne	ip, r5, r8	@ var, sign,
.L764:
	uxth	ip, ip	@ D.16042, var
	b	.L766	@
	.fnend
	.size	FADE_OutProcess, .-FADE_OutProcess
	.align	2
	.global	FADE_Destroy
	.type	FADE_Destroy, %function
FADE_Destroy:
	.fnstart
.LFB921:
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
	subs	r1, r0, #0	@ hFade, hFade
	ldmeqfd	sp, {fp, sp, pc}	@
	mov	r0, #17	@,
	bl	HI_ADSP_FREE	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	FADE_Destroy, .-FADE_Destroy
	.align	2
	.global	FADE_Create
	.type	FADE_Create, %function
FADE_Create:
	.fnstart
.LFB919:
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
	mov	r5, r1	@ inRate, inRate
	movw	r1, #:lower16:191999	@ tmp142,
	sub	ip, r5, #1	@ tmp141, inRate,
	movt	r1, #:upper16:191999	@ tmp142,
	mov	r7, r3	@ Channels, Channels
	cmp	ip, r1	@ tmp141, tmp142
	mov	r3, #0	@ tmp140,
	mov	r4, r0	@ phFade, phFade
	mov	r6, r2	@ BitPerSample, BitPerSample
	str	r3, [r0, #0]	@ tmp140,* phFade
	ldmhifd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	cmp	r2, #24	@ BitPerSample,
	cmpne	r2, #16	@, BitPerSample,
	ldmnefd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	sub	sl, r7, #1	@ tmp150, Channels,
	cmp	r7, #8	@ Channels,
	cmpne	sl, #1	@, tmp150,
	movls	sl, #0	@, tmp157
	movhi	sl, #1	@, tmp157
	ldmhifd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	mov	r0, #17	@,
	mov	r1, #36	@,
	bl	HI_ADSP_MALLOC	@
	subs	r8, r0, #0	@ D.15173,
	ldmeqfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	mov	r1, #36	@,
	bl	__memzero	@
	stmia	r8, {r6, r7}	@ phole stm
	str	r5, [r8, #8]	@ inRate, <variable>.u32InRate
	str	sl, [r8, #32]	@ tmp157, <variable>.enCurnFadeStauts
	str	r8, [r4, #0]	@ D.15173,* phFade
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	.fnend
	.size	FADE_Create, .-FADE_Create
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	g_u32VolCoef, %object
	.size	g_u32VolCoef, 400
g_u32VolCoef:
	.word	66633081
	.word	59386796
	.word	52928538
	.word	47172609
	.word	42042632
	.word	37470535
	.word	33395649
	.word	29763904
	.word	26527107
	.word	23642309
	.word	21071230
	.word	18779754
	.word	16737473
	.word	14917288
	.word	13295047
	.word	11849223
	.word	10560631
	.word	9412172
	.word	8388608
	.word	7476354
	.word	6663308
	.word	5938679
	.word	5292853
	.word	4717260
	.word	4204263
	.word	3747053
	.word	3339564
	.word	2976390
	.word	2652710
	.word	2364230
	.word	2107123
	.word	1877975
	.word	1673747
	.word	1491728
	.word	1329504
	.word	1184922
	.word	1056063
	.word	941217
	.word	838860
	.word	747635
	.word	666330
	.word	593867
	.word	529285
	.word	471726
	.word	420426
	.word	374705
	.word	333956
	.word	297639
	.word	265271
	.word	236423
	.word	210712
	.word	187797
	.word	167374
	.word	149172
	.word	132950
	.word	118492
	.word	105606
	.word	94121
	.word	83886
	.word	74763
	.word	66633
	.word	59386
	.word	52928
	.word	47172
	.word	42042
	.word	37470
	.word	33395
	.word	29763
	.word	26527
	.word	23642
	.word	21071
	.word	18779
	.word	16737
	.word	14917
	.word	13295
	.word	11849
	.word	10560
	.word	9412
	.word	8388
	.word	7476
	.word	6663
	.word	5938
	.word	5292
	.word	4717
	.word	4204
	.word	3747
	.word	3339
	.word	2976
	.word	2652
	.word	2364
	.word	2107
	.word	1877
	.word	1673
	.word	1491
	.word	1329
	.word	1184
	.word	1056
	.word	941
	.word	838
	.word	0
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
