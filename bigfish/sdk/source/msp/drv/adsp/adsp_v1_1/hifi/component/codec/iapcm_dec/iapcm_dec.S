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
	.file	"iapcm_dec.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(iapcm_dec)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_adsp) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD
@ drivers/msp/adsp/adsp_v1_1/./hifi/component/codec/iapcm_dec/.iapcm_dec.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/adsp/adsp_v1_1/./hifi/component/codec/iapcm_dec/iapcm_dec.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/adsp/adsp_v1_1/./hifi/component/codec/iapcm_dec/iapcm_dec.o
@ -O2 -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs
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
	.global	SetPCMDecoderParam
	.type	SetPCMDecoderParam, %function
SetPCMDecoderParam:
	.fnstart
.LFB1:
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
	subs	r3, r0, #0	@ hPCMDec, hPCMDec
	bne	.L2	@,
.L10:
	mov	r0, #-2147483646	@ D.1510,
	ldmfd	sp, {fp, sp, pc}	@
.L2:
	cmp	r1, #0	@ pOpenPara,
	beq	.L10	@,
	ldr	r0, [r1, #4]	@ <variable>.u32ChnNumber, <variable>.u32ChnNumber
	sub	r2, r0, #1	@ tmp139, <variable>.u32ChnNumber,
	cmp	r2, #1	@ tmp139,
	bls	.L5	@,
.L9:
	mov	r0, #-2147483645	@ D.1510,
	ldmfd	sp, {fp, sp, pc}	@
.L5:
	ldr	r2, [r1, #8]	@ D.1519, <variable>.u32BitWidth
	cmp	r2, #16	@ D.1519,
	cmpne	r2, #8	@, D.1519,
	beq	.L6	@,
	cmp	r2, #24	@ D.1519,
	bne	.L9	@,
.L6:
	ldr	ip, [r1, #0]	@ <variable>.u32FrameSize, <variable>.u32FrameSize
	cmp	ip, #30720	@ <variable>.u32FrameSize,
	bhi	.L9	@,
	ldr	ip, [r1, #16]	@ <variable>.bBigEndian, <variable>.bBigEndian
	mov	r0, #0	@ D.1510,
	str	ip, [r3, #16]	@ <variable>.bBigEndian, <variable>.bBigEndian
	ldr	r2, [r1, #20]	@ <variable>.bInterlace, <variable>.bInterlace
	str	r2, [r3, #20]	@ <variable>.bInterlace, <variable>.bInterlace
	ldr	ip, [r1, #12]	@ <variable>.u32SampleRate, <variable>.u32SampleRate
	str	ip, [r3, #12]	@ <variable>.u32SampleRate, <variable>.u32SampleRate
	ldr	r2, [r1, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	str	r2, [r3, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	ldr	ip, [r1, #4]	@ <variable>.u32ChnNumber, <variable>.u32ChnNumber
	str	ip, [r3, #4]	@ <variable>.u32ChnNumber, <variable>.u32ChnNumber
	ldr	r2, [r1, #0]	@ <variable>.u32FrameSize, <variable>.u32FrameSize
	str	r2, [r3, #0]	@ <variable>.u32FrameSize, <variable>.u32FrameSize
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	SetPCMDecoderParam, .-SetPCMDecoderParam
	.align	2
	.global	StorePCMDecoderParam
	.type	StorePCMDecoderParam, %function
StorePCMDecoderParam:
	.fnstart
.LFB2:
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
	subs	r3, r0, #0	@ hPCMDec, hPCMDec
	bne	.L13	@,
.L17:
	mov	r0, #-2147483646	@ D.1541,
	ldmfd	sp, {fp, sp, pc}	@
.L13:
	cmp	r1, #0	@ pOpenPara,
	beq	.L17	@,
	ldr	r2, [r3, #16]	@ <variable>.bBigEndian, <variable>.bBigEndian
	mov	r0, #0	@ D.1541,
	str	r2, [r1, #16]	@ <variable>.bBigEndian, <variable>.bBigEndian
	ldr	ip, [r3, #20]	@ <variable>.bInterlace, <variable>.bInterlace
	str	ip, [r1, #20]	@ <variable>.bInterlace, <variable>.bInterlace
	ldr	r2, [r3, #12]	@ <variable>.u32SampleRate, <variable>.u32SampleRate
	str	r2, [r1, #12]	@ <variable>.u32SampleRate, <variable>.u32SampleRate
	ldr	ip, [r3, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	str	ip, [r1, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	ldr	r2, [r3, #4]	@ <variable>.u32ChnNumber, <variable>.u32ChnNumber
	str	r2, [r1, #4]	@ <variable>.u32ChnNumber, <variable>.u32ChnNumber
	ldr	r3, [r3, #0]	@ <variable>.u32FrameSize, <variable>.u32FrameSize
	str	r3, [r1, #0]	@ <variable>.u32FrameSize, <variable>.u32FrameSize
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	StorePCMDecoderParam, .-StorePCMDecoderParam
	.align	2
	.global	PCMResetDecoder
	.type	PCMResetDecoder, %function
PCMResetDecoder:
	.fnstart
.LFB4:
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
	subs	r3, r0, #0	@ hPCMDec, hPCMDec
	moveq	r0, #-2147483647	@ D.1564,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r1, #0	@ pResetPara,
	moveq	r0, #-2147483646	@ D.1564,
	ldmeqfd	sp, {fp, sp, pc}	@
	ldr	r0, [r1, #4]	@ <variable>.u32ChnNumber, <variable>.u32ChnNumber
	sub	r2, r0, #1	@ tmp139, <variable>.u32ChnNumber,
	cmp	r2, #1	@ tmp139,
	bls	.L22	@,
.L26:
	mov	r0, #-2147483645	@ D.1564,
	ldmfd	sp, {fp, sp, pc}	@
.L22:
	ldr	r2, [r1, #8]	@ D.1571, <variable>.u32BitWidth
	cmp	r2, #16	@ D.1571,
	cmpne	r2, #8	@, D.1571,
	beq	.L23	@,
	cmp	r2, #24	@ D.1571,
	bne	.L26	@,
.L23:
	ldr	ip, [r1, #0]	@ <variable>.u32FrameSize, <variable>.u32FrameSize
	cmp	ip, #30720	@ <variable>.u32FrameSize,
	bhi	.L26	@,
	ldr	ip, [r1, #16]	@ <variable>.bBigEndian, <variable>.bBigEndian
	mov	r0, #0	@ D.1564,
	str	ip, [r3, #16]	@ <variable>.bBigEndian, <variable>.bBigEndian
	ldr	r2, [r1, #20]	@ <variable>.bInterlace, <variable>.bInterlace
	str	r2, [r3, #20]	@ <variable>.bInterlace, <variable>.bInterlace
	ldr	ip, [r1, #12]	@ <variable>.u32SampleRate, <variable>.u32SampleRate
	str	ip, [r3, #12]	@ <variable>.u32SampleRate, <variable>.u32SampleRate
	ldr	r2, [r1, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	str	r2, [r3, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	ldr	ip, [r1, #4]	@ <variable>.u32ChnNumber, <variable>.u32ChnNumber
	str	ip, [r3, #4]	@ <variable>.u32ChnNumber, <variable>.u32ChnNumber
	ldr	r2, [r1, #0]	@ <variable>.u32FrameSize, <variable>.u32FrameSize
	str	r2, [r3, #0]	@ <variable>.u32FrameSize, <variable>.u32FrameSize
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PCMResetDecoder, .-PCMResetDecoder
	.align	2
	.global	PCMDecFindSyncWord
	.type	PCMDecFindSyncWord, %function
PCMDecFindSyncWord:
	.fnstart
.LFB5:
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
	cmp	r0, #0	@ hPCMDec
	ldr	r3, [r1, #0]	@ pInData,* ppInbufPtr
	moveq	r0, #-2147483647	@ D.1596,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r1, #0	@ ppInbufPtr,
	bne	.L30	@,
.L35:
	mov	r0, #-2147483646	@ D.1596,
	ldmfd	sp, {fp, sp, pc}	@
.L30:
	cmp	r3, #0	@ pInData,
	beq	.L35	@,
	cmp	r2, #0	@ pBytesLeft,
	beq	.L35	@,
	ldr	r3, [r0, #0]	@ <variable>.u32FrameSize, <variable>.u32FrameSize
	ldr	r2, [r2, #0]	@ tmp139,* pBytesLeft
	cmp	r2, r3	@ tmp139, <variable>.u32FrameSize
	movlt	r0, #-2147483643	@ D.1596,
	movge	r0, #0	@ D.1596,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PCMDecFindSyncWord, .-PCMDecFindSyncWord
	.global	__aeabi_idiv
	.align	2
	.global	PCMDecDecodeFrame
	.type	PCMDecDecodeFrame, %function
PCMDecDecodeFrame:
	.fnstart
.LFB12:
	@ args = 0, pretend = 0, frame = 40
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
	subs	r5, r0, #0	@ hPCMDec, hPCMDec
	mov	r4, r1	@ ppInbufPtr, ppInbufPtr
	ldr	r6, [r1, #0]	@ pInData,* ppInbufPtr
	moveq	r0, #-2147483647	@ nRet,
	beq	.L38	@,
	cmp	r1, #0	@ ppInbufPtr,
	beq	.L150	@,
	cmp	r6, #0	@ pInData,
	beq	.L150	@,
	cmp	r2, #0	@ pBytesLeft,
	beq	.L150	@,
	ldr	r0, [r2, #0]	@ tmp307,* pBytesLeft
	ldr	r1, [r5, #0]	@ D.2042, <variable>.u32FrameSize
	cmp	r0, r1	@ tmp307, D.2042
	movlt	r0, #-2147483643	@ nRet,
	blt	.L38	@,
	tst	r3, #1	@ pOutPCM,
	movne	r0, #-2147483645	@ nRet,
	beq	.L151	@,
.L38:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L150:
	mov	r0, #-2147483646	@ nRet,
	b	.L38	@
.L151:
	ldr	r8, [r5, #16]	@ <variable>.bBigEndian, <variable>.bBigEndian
	cmp	r8, #1	@ <variable>.bBigEndian,
	beq	.L152	@,
.L43:
	cmp	r3, #0	@ pOutPCM,
	beq	.L150	@,
	ldr	r7, [r5, #20]	@ <variable>.bInterlace, <variable>.bInterlace
	ldr	r0, [r2, #0]	@,* pBytesLeft
	cmp	r7, #0	@ <variable>.bInterlace,
	str	r0, [fp, #-64]	@, %sfp
	bne	.L48	@,
	ldr	r8, [r5, #4]	@ D.1955, <variable>.u32ChnNumber
	cmp	r8, #2	@ D.1955,
	bne	.L49	@,
	ldr	ip, [r5, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	ldr	r0, [r5, #0]	@, <variable>.u32FrameSize
	str	r2, [fp, #-68]	@,
	mov	sl, ip, lsr #3	@ BytePerSample, <variable>.u32BitWidth,
	str	r3, [fp, #-72]	@,
	mov	r1, sl	@, BytePerSample
	bl	__aeabi_idiv	@
	ldr	r3, [fp, #-72]	@,
	cmp	sl, #1	@ BytePerSample,
	add	r2, r0, r0, lsr #31	@, tmp328,,,
	mov	r0, r2, asr #1	@, tmp328,
	ldr	r2, [fp, #-68]	@,
	str	r0, [fp, #-48]	@, %sfp
	str	r0, [fp, #-56]	@, %sfp
	add	r1, r3, r0, asl #1	@, pOutR, pOutPCM,,
	beq	.L153	@,
	cmp	sl, #2	@ BytePerSample,
	beq	.L154	@,
	cmp	sl, #3	@ BytePerSample,
	strne	r7, [fp, #-48]	@ <variable>.bInterlace, %sfp
	beq	.L155	@,
.L51:
	ldr	r7, [fp, #-48]	@, %sfp
	mov	r0, #0	@ nRet,
	ldr	r1, [r5, #0]	@ temp.482, <variable>.u32FrameSize
	str	r7, [r5, #24]	@, <variable>.nOutSamplesPerChn
	add	r6, r6, r1	@ tmp382, pInData, temp.482
	str	r6, [r4, #0]	@ tmp382,* ppInbufPtr
	ldr	r8, [fp, #-64]	@, %sfp
	rsb	r3, r1, r8	@ D.1961, temp.482,
	str	r3, [r2, #0]	@ D.1961,* pBytesLeft
	b	.L38	@
.L48:
	ldr	r8, [r5, #4]	@ temp.493, <variable>.u32ChnNumber
	cmp	r8, #2	@ temp.493,
	bne	.L75	@,
	ldr	r7, [r5, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	ldr	r0, [r5, #0]	@, <variable>.u32FrameSize
	str	r2, [fp, #-68]	@,
	mov	r7, r7, lsr #3	@ BytePerSample, <variable>.u32BitWidth,
	str	r3, [fp, #-72]	@,
	mov	r1, r7	@, BytePerSample
	bl	__aeabi_idiv	@
	cmp	r7, #1	@ BytePerSample,
	ldr	r2, [fp, #-68]	@,
	ldr	r3, [fp, #-72]	@,
	beq	.L156	@,
	cmp	r7, #2	@ BytePerSample,
	beq	.L157	@,
	cmp	r7, #3	@ BytePerSample,
	movne	r3, #0	@ prephitmp.578,
	beq	.L158	@,
.L79:
	ldr	lr, [r5, #0]	@ temp.497, <variable>.u32FrameSize
	mov	r0, #0	@ nRet,
	str	r3, [r5, #24]	@ prephitmp.578, <variable>.nOutSamplesPerChn
	add	r6, r6, lr	@ tmp448, pInData, temp.497
	str	r6, [r4, #0]	@ tmp448,* ppInbufPtr
	ldr	r3, [fp, #-64]	@, %sfp
	rsb	r1, lr, r3	@ temp.500, temp.497,
	str	r1, [r2, #0]	@ temp.500,* pBytesLeft
	b	.L38	@
.L152:
	ldr	r0, [r5, #8]	@ D.1949, <variable>.u32BitWidth
	cmp	r0, #16	@ D.1949,
	beq	.L159	@,
	cmp	r0, #24	@ D.1949,
	bne	.L43	@,
	cmp	r1, #0	@ D.2042,
	ble	.L43	@,
	mov	r0, r6	@ ivtmp.478, pInData
	mov	ip, #0	@ i.510,
.L46:
	ldrb	sl, [r0, #2]	@ zero_extendqisi2	@ tmp317,
	ldrb	r8, [r6, ip]	@ zero_extendqisi2	@ data0,* i.510
	ldrb	r7, [r0, #1]	@ zero_extendqisi2	@ data1,
	strb	sl, [r6, ip]	@ tmp317,* i.510
	add	ip, ip, #3	@ i.510, i.510,
	cmp	r1, ip	@ D.2042, i.510
	strb	r8, [r0, #2]	@ data0,
	strb	r7, [r0, #1]	@ data1,
	add	r0, r0, #3	@ ivtmp.478, ivtmp.478,
	bgt	.L46	@,
	b	.L43	@
.L156:
	cmp	r0, #0	@ nSamples,
	ble	.L88	@,
	ldrb	lr, [r6, #0]	@ zero_extendqisi2	@ tmp421,* pInData
	cmp	r7, r0	@ i, nSamples
	sub	ip, r0, #1	@ tmp495, nSamples,
	sub	r1, lr, #128	@ tmp422, tmp421,
	and	ip, ip, #1	@ tmp497, tmp495,
	mov	lr, r1, asl #24	@ tmp423, tmp422,
	mov	r1, lr, asr #16	@ tmp424, tmp423,
	strh	r1, [r3, #0]	@ movhi	@ tmp424,* pOutPCM
	beq	.L88	@,
	cmp	ip, #0	@ tmp497,
	beq	.L78	@,
	ldrb	r1, [r6, #1]	@ zero_extendqisi2	@ tmp691,
	cmp	r8, r0	@ i, nSamples
	mov	r7, r8	@ i, temp.493
	sub	lr, r1, #128	@ tmp692, tmp691,
	mov	ip, lr, asl #24	@ tmp693, tmp692,
	mov	r1, ip, asr #16	@ tmp694, tmp693,
	strh	r1, [r3, r8]	@ movhi	@ tmp694,* temp.493
	beq	.L88	@,
.L78:
	ldrb	ip, [r6, r7]	@ zero_extendqisi2	@ tmp616,* i
	add	r1, r7, #1	@ tmp498, i,
	mov	r8, r7, asl #1	@ tmp614, i,
	add	r7, r1, #1	@ i, tmp498,
	sub	lr, ip, #128	@ tmp617, tmp616,
	mov	ip, r1, asl #1	@ tmp621, tmp498,
	cmp	r7, r0	@ i, nSamples
	mov	sl, lr, asl #24	@ tmp618, tmp617,
	mov	sl, sl, asr #16	@ tmp619, tmp618,
	strh	sl, [r3, r8]	@ movhi	@ tmp619,
	ldrb	lr, [r6, r1]	@ zero_extendqisi2	@ tmp623,
	sub	r1, lr, #128	@ tmp624, tmp623,
	mov	lr, r1, asl #24	@ tmp625, tmp624,
	mov	r1, lr, asr #16	@ tmp626, tmp625,
	strh	r1, [r3, ip]	@ movhi	@ tmp626,
	bne	.L78	@,
.L88:
	mov	r3, r0, asr #1	@ prephitmp.578, nSamples,
	b	.L79	@
.L153:
	cmp	r0, #0	@,
	ble	.L51	@,
	ldrsb	r0, [r6, #1]	@ R_in,
	ldr	ip, [fp, #-48]	@, %sfp
	ldrb	r7, [r6, #0]	@ zero_extendqisi2	@ tmp332,* pInData
	mov	r0, r0, asl #24	@ tmp337, R_in,
	sub	lr, ip, #1	@ tmp483,,
	add	r0, r0, #-2147483648	@, tmp337,
	str	r0, [fp, #-52]	@, %sfp
	and	r9, lr, #1	@, tmp483,
	sub	r7, r7, #128	@ tmp333, tmp332,
	ldr	lr, [fp, #-52]	@, %sfp
	cmp	sl, ip	@ i,
	mov	r0, r7, asl #24	@, tmp333,
	str	r0, [fp, #-80]	@, %sfp
	str	r9, [fp, #-60]	@, %sfp
	add	ip, r6, #2	@ pData, pInData,
	mov	r9, lr, asr #16	@,,
	str	r9, [fp, #-52]	@, %sfp
	ldr	r9, [fp, #-80]	@, %sfp
	mov	r0, r8	@ ivtmp.195, D.1955
	mov	r7, r9, asr #16	@ tmp335,,
	strh	r7, [r3, #0]	@ movhi	@ tmp335,* pOutPCM
	ldr	lr, [fp, #-52]	@, %sfp
	strh	lr, [r1, #0]	@ movhi	@,* pOutR
	beq	.L51	@,
	ldr	r9, [fp, #-60]	@, %sfp
	cmp	r9, #0	@,
	beq	.L52	@,
	ldr	sl, [fp, #-48]	@, %sfp
	ldrsb	r7, [ip, #1]	@ R_in,
	add	ip, ip, #2	@ pData, pData,
	cmp	r8, sl	@ D.1955,
	ldrb	r8, [r6, #2]	@ zero_extendqisi2	@ tmp657,
	mov	sl, r0	@ i, ivtmp.195
	mov	r0, #4	@ ivtmp.195,
	sub	lr, r8, #128	@ tmp658, tmp657,
	mov	r7, r7, asl #24	@ tmp662, R_in,
	add	r7, r7, #-2147483648	@ tmp663, tmp662,
	mov	r8, lr, asl #24	@ tmp659, tmp658,
	mov	lr, r7, asr #16	@ tmp664, tmp663,
	mov	r8, r8, asr #16	@ tmp660, tmp659,
	strh	r8, [r3, #2]	@ movhi	@ tmp660,
	strh	lr, [r1, #2]	@ movhi	@ tmp664,
	beq	.L51	@,
.L52:
	ldrsb	lr, [ip, #1]	@,
	add	sl, sl, #2	@ i, i,
	add	r7, ip, #2	@ tmp486, pData,
	add	ip, r7, #2	@ pData, tmp486,
	str	lr, [fp, #-52]	@, %sfp
	add	lr, r0, #2	@ tmp487, ivtmp.195,
	ldrb	r9, [r6, r0]	@ zero_extendqisi2	@ tmp539,* ivtmp.195
	sub	r8, r9, #128	@, tmp539,
	ldr	r9, [fp, #-52]	@, %sfp
	str	r8, [fp, #-60]	@, %sfp
	mov	r8, r9, asl #24	@,,
	add	r9, r8, #-2147483648	@,,
	str	r9, [fp, #-80]	@, %sfp
	ldr	r9, [fp, #-60]	@, %sfp
	ldr	r8, [fp, #-56]	@, %sfp
	cmp	sl, r8	@ i,
	mov	r8, r9, asl #24	@,,
	ldr	r9, [fp, #-80]	@, %sfp
	str	r8, [fp, #-52]	@, %sfp
	mov	r8, r9, asr #16	@,,
	ldr	r9, [fp, #-52]	@, %sfp
	str	r8, [fp, #-60]	@, %sfp
	mov	r8, r9, asr #16	@,,
	str	r8, [fp, #-52]	@, %sfp
	strh	r8, [r3, r0]	@ movhi	@,* ivtmp.195
	ldr	r9, [fp, #-60]	@, %sfp
	strh	r9, [r1, r0]	@ movhi	@,* ivtmp.195
	add	r0, lr, #2	@ ivtmp.195, tmp487,
	ldrsb	r9, [r7, #1]	@ R_in,
	ldrb	r8, [r6, lr]	@ zero_extendqisi2	@ tmp551,
	sub	r8, r8, #128	@ tmp552, tmp551,
	mov	r7, r9, asl #24	@ tmp556, R_in,
	add	r9, r7, #-2147483648	@ tmp557, tmp556,
	mov	r7, r8, asl #24	@ tmp553, tmp552,
	mov	r9, r9, asr #16	@ tmp558, tmp557,
	mov	r8, r7, asr #16	@ tmp554, tmp553,
	strh	r8, [r3, lr]	@ movhi	@ tmp554,
	strh	r9, [r1, lr]	@ movhi	@ tmp558,
	bne	.L52	@,
	b	.L51	@
.L49:
	cmp	r8, #1	@ D.1955,
	beq	.L61	@,
.L149:
	mov	r0, #-2147483642	@ nRet,
	b	.L38	@
.L61:
	ldr	r8, [r5, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	ldr	r0, [r5, #0]	@, <variable>.u32FrameSize
	str	r2, [fp, #-68]	@,
	mov	r8, r8, lsr #3	@ BytePerSample, <variable>.u32BitWidth,
	str	r3, [fp, #-72]	@,
	mov	r1, r8	@, BytePerSample
	bl	__aeabi_idiv	@
	cmp	r8, #1	@ BytePerSample,
	ldr	r3, [fp, #-72]	@,
	ldr	r2, [fp, #-68]	@,
	moveq	r8, r7	@ i, ivtmp.276
	mov	r1, r0	@ prephitmp.179,
	add	ip, r3, r1, asl #1	@, pOutR, pOutPCM, prephitmp.179,
	beq	.L63	@,
	cmp	r8, #2	@ BytePerSample,
	beq	.L160	@,
	cmp	r8, #3	@ BytePerSample,
	movne	r1, r7	@ prephitmp.179, <variable>.bInterlace
	beq	.L161	@,
.L65:
	ldr	lr, [r5, #0]	@ temp.488, <variable>.u32FrameSize
	mov	r0, #0	@ nRet,
	str	r1, [r5, #24]	@ prephitmp.179, <variable>.nOutSamplesPerChn
	add	r6, r6, lr	@ tmp414, pInData, temp.488
	str	r6, [r4, #0]	@ tmp414,* ppInbufPtr
	ldr	r7, [fp, #-64]	@, %sfp
	rsb	ip, lr, r7	@ temp.491, temp.488,
	str	ip, [r2, #0]	@ temp.491,* pBytesLeft
	b	.L38	@
.L64:
	ldrb	lr, [r6, r8]	@ zero_extendqisi2	@ tmp389,* i
	add	r8, r8, #1	@ i, i,
	sub	sl, lr, #128	@ tmp390, tmp389,
	mov	lr, sl, asl #24	@ tmp391, tmp390,
	mov	sl, lr, lsr #16	@ L_out, tmp391,
	strh	sl, [r3, r7]	@ movhi	@ L_out,* ivtmp.276
	strh	sl, [ip, r7]	@ movhi	@ L_out,* ivtmp.276
	add	r7, r7, #2	@ ivtmp.276, ivtmp.276,
.L63:
	cmp	r0, r8	@ nSamples, i
	bgt	.L64	@,
	b	.L65	@
.L158:
	cmp	r0, #0	@ nSamples,
	ble	.L88	@,
	mla	r7, r7, r0, r6	@ D.2650, BytePerSample, nSamples, pInData
	ldrb	ip, [r6, #2]	@ zero_extendqisi2	@ tmp443,
	ldrb	sl, [r6, #1]	@ zero_extendqisi2	@ tmp441,
	add	r1, r6, #3	@ pData, pInData,
	mov	lr, ip, asl #16	@ data2, tmp443,
	rsb	r9, r6, r7	@ tmp500, pInData, D.2650
	cmp	r1, r7	@ pData, D.2650
	orr	ip, lr, sl, asl #8	@, tmp444, data2, tmp441,
	sub	r9, r9, #3	@ tmp501, tmp500,
	sbfx	lr, ip, #8, #16	@ tmp447, tmp444,,
	and	r9, r9, #1	@ tmp513, tmp501,
	strh	lr, [r3, #0]	@ movhi	@ tmp447,* pOutPCM
	beq	.L88	@,
	cmp	r9, #0	@ tmp513,
	beq	.L144	@,
	ldrb	lr, [r1, #2]	@ zero_extendqisi2	@ tmp701,
	mov	r8, #4	@ ivtmp.389,
	ldrb	sl, [r1, #1]	@ zero_extendqisi2	@ tmp698,
	add	r1, r6, #6	@ pData, pInData,
	cmp	r1, r7	@ pData, D.2650
	mov	ip, lr, asl #16	@ data2, tmp701,
	orr	lr, ip, sl, asl #8	@, tmp703, data2, tmp698,
	sbfx	ip, lr, #8, #16	@ tmp706, tmp703,,
	strh	ip, [r3, #2]	@ movhi	@ tmp706,
	beq	.L88	@,
.L144:
	str	r2, [fp, #-56]	@ pBytesLeft, %sfp
.L89:
	ldrb	r9, [r1, #1]	@ zero_extendqisi2	@,
	add	lr, r1, #3	@ tmp515, pData,
	ldrb	ip, [r1, #2]	@ zero_extendqisi2	@ tmp635,
	add	r1, r1, #6	@ pData, pData,
	cmp	r1, r7	@ pData, D.2650
	str	r9, [fp, #-48]	@, %sfp
	add	r9, r8, #2	@ tmp514, ivtmp.389,
	ldr	r2, [fp, #-48]	@, %sfp
	mov	sl, ip, asl #16	@, tmp635,
	orr	ip, sl, r2, asl #8	@,,,,
	str	ip, [fp, #-48]	@, %sfp
	sbfx	r2, ip, #8, #16	@ tmp641,,,
	strh	r2, [r3, r8]	@ movhi	@ tmp641,* ivtmp.389
	ldrb	sl, [lr, #2]	@ zero_extendqisi2	@ tmp649,
	add	r8, r9, #2	@ ivtmp.389, tmp514,
	ldrb	ip, [lr, #1]	@ zero_extendqisi2	@ tmp646,
	mov	sl, sl, asl #16	@ data2, tmp649,
	orr	lr, sl, ip, asl #8	@, tmp651, data2, tmp646,
	sbfx	r2, lr, #8, #16	@ tmp654, tmp651,,
	strh	r2, [r3, r9]	@ movhi	@ tmp654,
	bne	.L89	@,
	ldr	r2, [fp, #-56]	@ pBytesLeft, %sfp
	mov	r3, r0, asr #1	@ prephitmp.578, nSamples,
	b	.L79	@
.L157:
	ands	r1, r6, #1	@ tmp425, pInData,
	moveq	ip, r1	@ i.524, ivtmp.375
	movne	ip, r6	@ ivtmp.356, pInData
	movne	r1, #0	@ i.523,
	bne	.L83	@,
	b	.L82	@
.L84:
	ldrsb	sl, [ip, #-1]	@ tmp429,
	ldrb	r8, [ip, #-2]	@ zero_extendqisi2	@ ndata,
	orr	r8, r8, sl, asl #8	@, tmp433, ndata, tmp429,
	strh	r8, [r3, r7]	@ movhi	@ tmp433,
.L83:
	cmp	r0, r1	@ nSamples, i.523
	mov	r7, r1, asl #1	@ tmp428, i.523,
	add	ip, ip, #2	@ ivtmp.356, ivtmp.356,
	add	r1, r1, #1	@ i.523, i.523,
	bgt	.L84	@,
	mov	r3, r0, asr #1	@ prephitmp.578, nSamples,
	b	.L79	@
.L86:
	ldrh	r8, [r6, r1]	@,* ivtmp.375
	strh	r8, [r3, r1]	@ movhi	@,* ivtmp.375
	add	r1, r1, #2	@ ivtmp.375, ivtmp.375,
.L82:
	cmp	r0, ip	@ nSamples, i.524
	add	ip, ip, #1	@ i.524, i.524,
	bgt	.L86	@,
	mov	r3, r0, asr #1	@ prephitmp.578, nSamples,
	b	.L79	@
.L75:
	cmp	r8, #1	@ temp.493,
	bne	.L149	@,
	ldr	r7, [r5, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	ldr	r0, [r5, #0]	@, <variable>.u32FrameSize
	str	r2, [fp, #-68]	@,
	mov	r7, r7, lsr #3	@ BytePerSample, <variable>.u32BitWidth,
	str	r3, [fp, #-72]	@,
	mov	r1, r7	@, BytePerSample
	bl	__aeabi_idiv	@
	cmp	r7, #1	@ BytePerSample,
	ldr	r2, [fp, #-68]	@,
	ldr	r3, [fp, #-72]	@,
	moveq	r1, #0	@ i,
	beq	.L92	@,
	cmp	r7, #2	@ BytePerSample,
	beq	.L162	@,
	cmp	r7, #3	@ BytePerSample,
	movne	r3, #0	@ prephitmp.577,
	moveq	r1, r6	@ ivtmp.450, pInData
	moveq	ip, #0	@ i.540,
	beq	.L102	@,
.L94:
	ldr	ip, [r5, #0]	@ temp.505, <variable>.u32FrameSize
	mov	r0, #0	@ nRet,
	str	r3, [r5, #24]	@ prephitmp.577, <variable>.nOutSamplesPerChn
	add	r6, r6, ip	@ tmp480, pInData, temp.505
	str	r6, [r4, #0]	@ tmp480,* ppInbufPtr
	ldr	r7, [fp, #-64]	@, %sfp
	rsb	r1, ip, r7	@ temp.508, temp.505,
	str	r1, [r2, #0]	@ temp.508,* pBytesLeft
	b	.L38	@
.L93:
	ldrb	ip, [r6, r1]	@ zero_extendqisi2	@ tmp454,* i
	add	r1, r1, #1	@ i, i,
	sub	r7, ip, #128	@ tmp455, tmp454,
	mov	lr, r7, asl #24	@ tmp456, tmp455,
	mov	ip, lr, lsr #16	@ L_out, tmp456,
	strh	ip, [r3, #-2]	@ movhi	@ L_out,
	strh	ip, [r3, #-4]	@ movhi	@ L_out,
.L92:
	cmp	r0, r1	@ nSamples, i
	add	r3, r3, #4	@ ivtmp.400, ivtmp.400,
	bgt	.L93	@,
.L148:
	mov	r3, r0	@ prephitmp.577, nSamples
	b	.L94	@
.L159:
	add	r1, r1, r1, lsr #31	@, tmp310, D.2042, D.2042,
	mov	ip, r1, asr #1	@ D.2067, tmp310,
	cmp	ip, #0	@ D.2067,
	ble	.L43	@,
	ldrh	r7, [r6, #0]	@ pcmdata,* pInData
	cmp	r8, ip	@ i, D.2067
	mov	r1, r8	@ i, <variable>.bBigEndian
	sub	r8, ip, #1	@ tmp516, D.2067,
	and	r8, r8, #1	@ tmp518, tmp516,
	mov	r0, #2	@ ivtmp.472,
	mov	sl, r7, lsr #8	@ tmp313, pcmdata,
	orr	r7, sl, r7, asl #8	@, tmp316, tmp313, pcmdata,
	strh	r7, [r6, #0]	@ movhi	@ tmp316,* pInData
	beq	.L43	@,
	cmp	r8, #0	@ tmp518,
	beq	.L45	@,
	ldrh	r7, [r6, #2]	@ pcmdata,
	mov	r1, #2	@ i,
	cmp	r1, ip	@ i, D.2067
	mov	r0, #4	@ ivtmp.472,
	mov	r8, r7, lsr #8	@ tmp709, pcmdata,
	orr	r7, r8, r7, asl #8	@, tmp710, tmp709, pcmdata,
	strh	r7, [r6, #2]	@ movhi	@ tmp710,
	beq	.L43	@,
.L45:
	ldrh	r8, [r6, r0]	@ pcmdata,* ivtmp.472
	add	r7, r0, #2	@ tmp520, ivtmp.472,
	add	r1, r1, #2	@ i, i,
	cmp	r1, ip	@ i, D.2067
	mov	sl, r8, lsr #8	@ tmp525, pcmdata,
	orr	r8, sl, r8, asl #8	@, tmp526, tmp525, pcmdata,
	strh	r8, [r6, r0]	@ movhi	@ tmp526,* ivtmp.472
	ldrh	r8, [r6, r7]	@ pcmdata,
	add	r0, r7, #2	@ ivtmp.472, tmp520,
	mov	sl, r8, lsr #8	@ tmp531, pcmdata,
	orr	r8, sl, r8, asl #8	@, tmp532, tmp531, pcmdata,
	strh	r8, [r6, r7]	@ movhi	@ tmp532,
	bne	.L45	@,
	b	.L43	@
.L155:
	ldr	sl, [fp, #-56]	@, %sfp
	cmp	sl, #0	@,
	ble	.L51	@,
	ldrb	sl, [r6, #2]	@ zero_extendqisi2	@ tmp364,
	mov	r7, #1	@ i.576,
	ldrb	r9, [r6, #1]	@ zero_extendqisi2	@ tmp362,
	ldr	r0, [fp, #-56]	@, %sfp
	mov	lr, sl, asl #16	@ tmp365, tmp364,
	orr	sl, lr, r9, asl #8	@, tmp366, tmp365, tmp362,
	sub	ip, r0, #1	@ tmp489,,
	sbfx	r9, sl, #8, #16	@ tmp371, tmp366,,
	and	ip, ip, r7	@, tmp489,
	str	ip, [fp, #-52]	@, %sfp
	cmp	r7, r0	@ i.576,
	strh	r9, [r3, #0]	@ movhi	@ tmp371,* pOutPCM
	add	r0, r6, #6	@ pData, pInData,
	ldrb	lr, [r6, #5]	@ zero_extendqisi2	@ tmp377,
	mov	ip, r8	@ ivtmp.254, D.1955
	ldrb	r9, [r6, #4]	@ zero_extendqisi2	@ tmp375,
	mov	sl, lr, asl #16	@ data2.569, tmp377,
	orr	lr, sl, r9, asl #8	@, tmp378, data2.569, tmp375,
	sbfx	sl, lr, #8, #16	@ tmp381, tmp378,,
	strh	sl, [r1, #0]	@ movhi	@ tmp381,* pOutR
	beq	.L51	@,
	ldr	r9, [fp, #-52]	@, %sfp
	cmp	r9, #0	@,
	beq	.L140	@,
	ldr	r7, [fp, #-56]	@, %sfp
	ldrb	lr, [r0, #2]	@ zero_extendqisi2	@ tmp669,
	cmp	r8, r7	@ D.1955,
	ldrb	r8, [r0, #1]	@ zero_extendqisi2	@ tmp666,
	mov	r7, ip	@ i.576, ivtmp.254
	mov	ip, #4	@ ivtmp.254,
	mov	sl, lr, asl #16	@ tmp670, tmp669,
	orr	lr, sl, r8, asl #8	@, tmp671, tmp670, tmp666,
	sbfx	sl, lr, #8, #16	@ tmp676, tmp671,,
	strh	sl, [r3, #2]	@ movhi	@ tmp676,
	ldrb	r8, [r0, #5]	@ zero_extendqisi2	@ tmp683,
	ldrb	sl, [r0, #4]	@ zero_extendqisi2	@ tmp680,
	add	r0, r6, #12	@ pData, pInData,
	mov	lr, r8, asl #16	@ data2.569, tmp683,
	orr	r8, lr, sl, asl #8	@, tmp685, data2.569, tmp680,
	sbfx	lr, r8, #8, #16	@ tmp688, tmp685,,
	strh	lr, [r1, #2]	@ movhi	@ tmp688,
	beq	.L51	@,
.L140:
	mov	r9, r6	@ pInData, pInData
	str	r2, [fp, #-80]	@ pBytesLeft, %sfp
.L60:
	ldrb	r2, [r0, #2]	@ zero_extendqisi2	@ tmp566,
	add	r7, r7, #2	@ i.576, i.576,
	ldrb	lr, [r0, #1]	@ zero_extendqisi2	@,
	add	r6, r0, #6	@ tmp494, pData,
	add	r8, ip, #2	@ tmp493, ivtmp.254,
	mov	sl, r2, asl #16	@, tmp566,
	str	sl, [fp, #-60]	@, %sfp
	ldr	sl, [fp, #-60]	@, %sfp
	ldr	r2, [fp, #-56]	@, %sfp
	cmp	r7, r2	@ i.576,
	orr	r2, sl, lr, asl #8	@,,,,
	sbfx	lr, r2, #8, #16	@ tmp573,,,
	str	r2, [fp, #-52]	@, %sfp
	strh	lr, [r3, ip]	@ movhi	@ tmp573,* ivtmp.254
	ldrb	sl, [r0, #5]	@ zero_extendqisi2	@,
	ldrb	lr, [r0, #4]	@ zero_extendqisi2	@,
	add	r0, r0, #12	@ pData, pData,
	mov	r2, sl, asl #16	@,,
	str	r2, [fp, #-60]	@, %sfp
	orr	sl, r2, lr, asl #8	@,,,,
	str	sl, [fp, #-52]	@, %sfp
	sbfx	lr, sl, #8, #16	@ tmp586,,,
	strh	lr, [r1, ip]	@ movhi	@ tmp586,* ivtmp.254
	ldrb	ip, [r6, #2]	@ zero_extendqisi2	@,
	str	ip, [fp, #-60]	@, %sfp
	add	ip, r8, #2	@ ivtmp.254, tmp493,
	ldr	r2, [fp, #-60]	@, %sfp
	ldrb	lr, [r6, #1]	@ zero_extendqisi2	@,
	mov	sl, r2, asl #16	@,,
	str	sl, [fp, #-60]	@, %sfp
	orr	r2, sl, lr, asl #8	@,,,,
	str	r2, [fp, #-52]	@, %sfp
	sbfx	lr, r2, #8, #16	@ tmp600,,,
	strh	lr, [r3, r8]	@ movhi	@ tmp600,
	ldrb	sl, [r6, #5]	@ zero_extendqisi2	@ tmp607,
	ldrb	lr, [r6, #4]	@ zero_extendqisi2	@ tmp604,
	mov	sl, sl, asl #16	@ data2.569, tmp607,
	orr	r2, sl, lr, asl #8	@, tmp609, data2.569, tmp604,
	sbfx	r6, r2, #8, #16	@ tmp612, tmp609,,
	strh	r6, [r1, r8]	@ movhi	@ tmp612,
	bne	.L60	@,
	mov	r6, r9	@ pInData, pInData
	ldr	r2, [fp, #-80]	@ pBytesLeft, %sfp
	b	.L51	@
.L154:
	ands	r0, r6, #1	@ tmp340, pInData,
	movne	r0, r6	@ ivtmp.206, pInData
	movne	ip, r7	@ i.552, ivtmp.213
	bne	.L55	@,
	mov	ip, r6	@ ivtmp.232, pInData
	mov	r7, r0	@ i.554, ivtmp.239
	b	.L57	@
.L58:
	ldrh	sl, [ip, #-4]	@,
	strh	sl, [r3, r0]	@ movhi	@,* ivtmp.239
	ldrh	r9, [ip, #-2]	@,
	strh	r9, [r1, r0]	@ movhi	@,* ivtmp.239
	add	r0, r0, #2	@ ivtmp.239, ivtmp.239,
.L57:
	ldr	r9, [fp, #-56]	@, %sfp
	add	ip, ip, #4	@ ivtmp.232, ivtmp.232,
	cmp	r9, r7	@, i.554
	add	r7, r7, #1	@ i.554, i.554,
	bgt	.L58	@,
	b	.L51	@
.L56:
	ldrsb	sl, [r0, #-3]	@ tmp341,
	ldrb	r8, [r0, #-4]	@ zero_extendqisi2	@ tmp344,
	orr	lr, r8, sl, asl #8	@, tmp347, tmp344, tmp341,
	strh	lr, [r3, r7]	@ movhi	@ tmp347,* ivtmp.213
	ldrsb	sl, [r0, #-1]	@ tmp348,
	ldrb	r9, [r0, #-2]	@ zero_extendqisi2	@ tmp351,
	orr	r8, r9, sl, asl #8	@, tmp354, tmp351, tmp348,
	strh	r8, [r1, r7]	@ movhi	@ tmp354,* ivtmp.213
	add	r7, r7, #2	@ ivtmp.213, ivtmp.213,
.L55:
	ldr	r9, [fp, #-56]	@, %sfp
	add	r0, r0, #4	@ ivtmp.206, ivtmp.206,
	cmp	r9, ip	@, i.552
	add	ip, ip, #1	@ i.552, i.552,
	bgt	.L56	@,
	b	.L51	@
.L102:
	cmp	r0, ip	@ nSamples, i.540
	add	r1, r1, #3	@ ivtmp.450, ivtmp.450,
	add	ip, ip, #1	@ i.540, i.540,
	add	r3, r3, #4	@ ivtmp.456, ivtmp.456,
	ble	.L148	@,
	ldrb	r7, [r1, #-1]	@ zero_extendqisi2	@ tmp472,
	ldrb	r8, [r1, #-2]	@ zero_extendqisi2	@ tmp468,
	mov	lr, r7, asl #16	@ tmp473, tmp472,
	orr	r7, lr, r8, asl #8	@, tmp474, tmp473, tmp468,
	mov	lr, r7, lsr #8	@ D.2175, tmp474,
	strh	lr, [r3, #-2]	@ movhi	@ D.2175,
	strh	lr, [r3, #-4]	@ movhi	@ D.2175,
	b	.L102	@
.L162:
	ands	r1, r6, #1	@ tmp458, pInData,
	movne	r1, r6	@ ivtmp.412, pInData
	movne	ip, #0	@ i.533,
	bne	.L97	@,
.L99:
	cmp	r0, r1	@ nSamples, i.535
	mov	ip, r1, asl #1	@ tmp466, i.535,
	add	r3, r3, #4	@ ivtmp.438, ivtmp.438,
	add	r1, r1, #1	@ i.535, i.535,
	ble	.L148	@,
	ldrh	ip, [r6, ip]	@ ndata.534,
	strh	ip, [r3, #-2]	@ movhi	@ ndata.534,
	strh	ip, [r3, #-4]	@ movhi	@ ndata.534,
	b	.L99	@
.L161:
	mov	r8, r6	@ ivtmp.325, pInData
	mov	r9, r7	@ i.520, ivtmp.334
	mov	sl, r1	@ prephitmp.179, prephitmp.179
	str	r3, [fp, #-52]	@ pOutPCM, %sfp
	b	.L73	@
.L74:
	ldrb	r1, [r8, #-1]	@ zero_extendqisi2	@ tmp406,
	ldrb	r3, [r8, #-2]	@ zero_extendqisi2	@,
	mov	lr, r1, asl #16	@ tmp407, tmp406,
	orr	r1, lr, r3, asl #8	@, tmp408, tmp407,,
	ldr	r3, [fp, #-52]	@, %sfp
	mov	lr, r1, lsr #8	@ D.2089, tmp408,
	strh	lr, [r3, r7]	@ movhi	@ D.2089,* ivtmp.334
	strh	lr, [ip, r7]	@ movhi	@ D.2089,* ivtmp.334
	add	r7, r7, #2	@ ivtmp.334, ivtmp.334,
.L73:
	cmp	r0, r9	@ nSamples, i.520
	add	r8, r8, #3	@ ivtmp.325, ivtmp.325,
	add	r9, r9, #1	@ i.520, i.520,
	bgt	.L74	@,
.L147:
	mov	r1, sl	@ prephitmp.179, prephitmp.179
	b	.L65	@
.L160:
	ands	r8, r6, #1	@ tmp393, pInData,
	moveq	r7, r8	@ ivtmp.310, tmp393
	beq	.L68	@,
	mov	r8, r6	@ pData, pInData
	mov	r9, r7	@ i.513, ivtmp.290
	mov	sl, r1	@ prephitmp.179, prephitmp.179
	str	r3, [fp, #-52]	@ pOutPCM, %sfp
	b	.L69	@
.L70:
	ldrb	r1, [r8, #1]	@ zero_extendqisi2	@,
	add	r8, r8, #2	@ pData, pData,
	str	r1, [fp, #-48]	@, %sfp
	ldr	r3, [fp, #-48]	@, %sfp
	ldrb	lr, [r6, r7]	@ zero_extendqisi2	@ ndata,* ivtmp.290
	orr	r1, lr, r3, asl #8	@, ndata.512, ndata,,
	ldr	r3, [fp, #-52]	@, %sfp
	strh	r1, [r3, r7]	@ movhi	@ ndata.512,* ivtmp.290
	strh	r1, [ip, r7]	@ movhi	@ ndata.512,* ivtmp.290
	add	r7, r7, #2	@ ivtmp.290, ivtmp.290,
.L69:
	cmp	r0, r9	@ nSamples, i.513
	add	r9, r9, #1	@ i.513, i.513,
	bgt	.L70	@,
	b	.L147	@
.L71:
	ldrh	sl, [r6, r7]	@ ndata.514,* ivtmp.310
	strh	sl, [r3, r7]	@ movhi	@ ndata.514,* ivtmp.310
	strh	sl, [ip, r7]	@ movhi	@ ndata.514,* ivtmp.310
	add	r7, r7, #2	@ ivtmp.310, ivtmp.310,
.L68:
	cmp	r0, r8	@ nSamples, i.515
	add	r8, r8, #1	@ i.515, i.515,
	bgt	.L71	@,
	b	.L65	@
.L97:
	cmp	r0, ip	@ nSamples, i.533
	add	r1, r1, #2	@ ivtmp.412, ivtmp.412,
	add	ip, ip, #1	@ i.533, i.533,
	add	r3, r3, #4	@ ivtmp.418, ivtmp.418,
	ble	.L148	@,
	ldrb	r8, [r1, #-1]	@ zero_extendqisi2	@ tmp465,
	ldrb	r7, [r1, #-2]	@ zero_extendqisi2	@ ndata,
	orr	lr, r7, r8, asl #8	@, ndata.532, ndata, tmp465,
	strh	lr, [r3, #-2]	@ movhi	@ ndata.532,
	strh	lr, [r3, #-4]	@ movhi	@ ndata.532,
	b	.L97	@
	.fnend
	.size	PCMDecDecodeFrame, .-PCMDecDecodeFrame
	.align	2
	.global	PCMDecGetFrameInfo
	.type	PCMDecGetFrameInfo, %function
PCMDecGetFrameInfo:
	.fnstart
.LFB13:
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
	subs	r3, r0, #0	@ hPCMDec, hPCMDec
	moveq	r0, #-2147483647	@ D.1986,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r1, #0	@ pFrmInfo,
	moveq	r0, #-2147483646	@ D.1986,
	ldmeqfd	sp, {fp, sp, pc}	@
	mov	ip, #16	@ tmp138,
	mov	r0, #2	@ tmp139,
	str	ip, [r1, #8]	@ tmp138, <variable>.bitsPerSample
	str	r0, [r1, #0]	@ tmp139, <variable>.nChans
	mov	r0, #0	@ D.1986,
	ldr	r2, [r3, #24]	@ <variable>.nOutSamplesPerChn, <variable>.nOutSamplesPerChn
	mov	ip, r2, asl #1	@ tmp141, <variable>.nOutSamplesPerChn,
	str	ip, [r1, #12]	@ tmp141, <variable>.outputSamps
	ldr	r2, [r3, #12]	@ <variable>.u32SampleRate, <variable>.u32SampleRate
	str	r2, [r1, #4]	@ <variable>.u32SampleRate, <variable>.samprate
	ldr	r3, [r3, #20]	@ <variable>.bInterlace, <variable>.bInterlace
	str	r3, [r1, #16]	@ <variable>.bInterlace, <variable>.bInterlace
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PCMDecGetFrameInfo, .-PCMDecGetFrameInfo
	.global	__aeabi_uidiv
	.align	2
	.global	PCMDecCompGetSamplePerFrame
	.type	PCMDecCompGetSamplePerFrame, %function
PCMDecCompGetSamplePerFrame:
	.fnstart
.LFB14:
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
	cmp	r0, #0	@ hPCMDec
	ldmeqfd	sp, {fp, sp, pc}	@
	ldr	r3, [r0, #4]	@ <variable>.u32ChnNumber, <variable>.u32ChnNumber
	cmp	r3, #2	@ <variable>.u32ChnNumber,
	beq	.L173	@,
	ldr	r2, [r0, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	ldr	r0, [r0, #0]	@, <variable>.u32FrameSize
	mov	r1, r2, lsr #3	@, <variable>.u32BitWidth,
	bl	__aeabi_uidiv	@
	ldmfd	sp, {fp, sp, pc}	@
.L173:
	ldr	r1, [r0, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	ldr	r0, [r0, #0]	@, <variable>.u32FrameSize
	mov	r1, r1, lsr #3	@, <variable>.u32BitWidth,
	bl	__aeabi_uidiv	@
	mov	r0, r0, lsr #1	@ nSamples,,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PCMDecCompGetSamplePerFrame, .-PCMDecCompGetSamplePerFrame
	.align	2
	.global	PCMCloseDecoder
	.type	PCMCloseDecoder, %function
PCMCloseDecoder:
	.fnstart
.LFB3:
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
	subs	r1, r0, #0	@ hPCMDec, hPCMDec
	ldmeqfd	sp, {fp, sp, pc}	@
	mov	r0, #25	@,
	bl	HI_ADSP_FREE	@
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PCMCloseDecoder, .-PCMCloseDecoder
	.align	2
	.global	PCMOpenDecoder
	.type	PCMOpenDecoder, %function
PCMOpenDecoder:
	.fnstart
.LFB0:
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
	subs	r4, r0, #0	@ phPCMDec, phPCMDec
	moveq	r0, #-2147483646	@ D.1499,
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	mov	r1, #28	@,
	mov	r0, #25	@,
	bl	HI_ADSP_MALLOC	@
	subs	r3, r0, #0	@ D.1500,
	strne	r3, [r4, #0]	@ D.1500,* phPCMDec
	moveq	r0, #-2147483644	@ D.1499,
	movne	r0, #0	@ D.1499,
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	PCMOpenDecoder, .-PCMOpenDecoder
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
