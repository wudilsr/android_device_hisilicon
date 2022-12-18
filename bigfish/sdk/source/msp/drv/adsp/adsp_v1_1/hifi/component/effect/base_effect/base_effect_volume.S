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
	.file	"base_effect_volume.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(base_effect_volume)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_adsp) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD
@ drivers/msp/adsp/adsp_v1_1/./hifi/component/effect/base_effect/.base_effect_volume.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/adsp/adsp_v1_1/./hifi/component/effect/base_effect/base_effect_volume.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/adsp/adsp_v1_1/./hifi/component/effect/base_effect/base_effect_volume.o
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
	.global	UTILS_GaindB2Linear
	.type	UTILS_GaindB2Linear, %function
UTILS_GaindB2Linear:
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
	cmp	r0, #17	@ dB_Inter,
	movwgt	r1, #:lower16:66633081	@ s32Gain.61,
	movtgt	r1, #:upper16:66633081	@ s32Gain.61,
	bgt	.L3	@,
	cmn	r0, #119	@ dB_Inter,
	movlt	r1, #0	@ s32Gain.61,
	blt	.L3	@,
	cmp	r0, #0	@ dB_Inter,
	movw	r3, #:lower16:.LANCHOR0	@ tmp145,
	rsb	r0, r0, #18	@ volumeIndex, dB_Inter,
	movt	r3, #:upper16:.LANCHOR0	@ tmp145,
	ldr	ip, [r3, r0, asl #2]	@ s32Gain, g_dB2LinearTab
	blt	.L5	@,
	add	r0, r0, #1	@ pretmp.29, volumeIndex,
	ldr	r3, [r3, r0, asl #2]	@ pretmp.57, g_dB2LinearTab
	rsb	r0, r3, ip	@ tmp147, pretmp.57, s32Gain
	mul	r1, r1, r0	@ tmp148, dB_Frac, tmp147
	add	r3, r1, #7	@ tmp150, tmp148,
	cmp	r1, #0	@ tmp148,
	movlt	r1, r3	@ tmp149, tmp150
	add	r1, ip, r1, asr #3	@, s32Gain.61, s32Gain, tmp149,
.L3:
	str	r1, [r2, #0]	@ s32Gain.61,* ps32TargetGain
	ldmfd	sp, {fp, sp, pc}	@
.L5:
	add	r0, r0, #1	@ pretmp.37, volumeIndex,
	ldr	r3, [r3, r0, asl #2]	@ pretmp.59, g_dB2LinearTab
	rsb	r0, r3, ip	@ tmp153, pretmp.59, s32Gain
	mul	r1, r1, r0	@ tmp154, dB_Frac, tmp153
	add	r3, r1, #7	@ tmp156, tmp154,
	cmp	r1, #0	@ tmp154,
	movlt	r1, r3	@ tmp155, tmp156
	sub	r1, ip, r1, asr #3	@ s32Gain.61, s32Gain, tmp155,
	str	r1, [r2, #0]	@ s32Gain.61,* ps32TargetGain
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	UTILS_GaindB2Linear, .-UTILS_GaindB2Linear
	.align	2
	.global	UTILS_GainBalance
	.type	UTILS_GainBalance, %function
UTILS_GainBalance:
	.fnstart
.LFB6:
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
	cmp	r2, #50	@ u32Balance,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r2, #49	@ u32Balance,
	bls	.L12	@,
	ldr	r1, [r0, #0]	@ tmp144,* ps32Gain_L
	rsb	ip, r2, #100	@ tmp142, u32Balance,
	movw	r3, #:lower16:1374389535	@ tmp146,
	movt	r3, #:upper16:1374389535	@ tmp146,
	mul	r2, r1, ip	@ tmp143, tmp144, tmp142
	umull	r1, ip, r3, r2	@, tmp145, tmp146, tmp143
	mov	r1, ip, lsr #4	@ D.1395, tmp145,
	str	r1, [r0, #0]	@ D.1395,* ps32Gain_L
	ldmfd	sp, {fp, sp, pc}	@
.L12:
	ldr	r0, [r1, #0]	@ tmp139,* ps32Gain_R
	movw	r3, #:lower16:1374389535	@ tmp141,
	movt	r3, #:upper16:1374389535	@ tmp141,
	mul	r2, r0, r2	@ tmp138, tmp139, u32Balance
	umull	r0, ip, r3, r2	@, tmp140, tmp141, tmp138
	mov	r3, ip, lsr #4	@ D.1389, tmp140,
	str	r3, [r1, #0]	@ D.1389,* ps32Gain_R
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	UTILS_GainBalance, .-UTILS_GainBalance
	.align	2
	.global	UTILS_GainPercent
	.type	UTILS_GainPercent, %function
UTILS_GainPercent:
	.fnstart
.LFB7:
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
	str	r0, [r1, #0]	@ s32OrgGain,* ps32TargetGain
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	UTILS_GainPercent, .-UTILS_GainPercent
	.align	2
	.global	UTILS_GainProcessFrame_16BIT
	.type	UTILS_GainProcessFrame_16BIT, %function
UTILS_GainProcessFrame_16BIT:
	.fnstart
.LFB8:
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
	cmp	r3, #8388608	@ s32Gain_R,
	cmple	r2, #8388608	@, s32Gain_L,
	mov	r8, r0	@ ps16PcmBuf, ps16PcmBuf
	ble	.L16	@,
	cmp	r1, #0	@ samples,
	beq	.L23	@,
	mov	r4, r3	@, s32Gain_R
	mov	r5, r4, asr #31	@
	mov	r6, r2	@ pretmp.193, s32Gain_L
	mov	r7, r6, asr #31	@ pretmp.193
	mov	ip, r1	@ ivtmp.183, samples
	mov	r3, r0	@ s16src.188, ps16PcmBuf
	movw	sl, #32767	@ tmp237,
	strd	r4, [fp, #-52]	@,,
.L22:
	ldrh	r0, [r3, #2]	@ data_R.187,
	ldrsh	r4, [r3, #0]	@ tmp210,* s16src.188
	ldr	r9, [fp, #-52]	@, %sfp
	sxth	r0, r0	@ data_R.187, data_R.187
	mov	r5, r4, asr #31	@ tmp209
	mov	r1, r0, asr #31	@ data_R.187
	mul	r2, r6, r5	@ tmp212, pretmp.193,
	mul	r8, r9, r1	@ tmp222,, data_R.187
	ldr	r9, [fp, #-48]	@, %sfp
	mla	r1, r4, r7, r2	@ tmp294, tmp209, pretmp.193, tmp212
	ldr	r2, [fp, #-52]	@, %sfp
	umull	r4, r5, r6, r4	@ tmp213, pretmp.193, tmp209
	mla	r8, r0, r9, r8	@ tmp297, data_R.187,, tmp222
	add	r5, r1, r5	@, tmp294,
	umull	r0, r1, r2, r0	@ tmp223,, data_R.187
	mov	r2, r4, lsr #23	@ data.190, tmp213,
	orr	r2, r2, r5, asl #9	@, data.190, data.190,,
	add	r1, r8, r1	@, tmp297,
	mov	r4, r2, asr #31	@ sign, data.190,
	cmp	r4, r2, asr #15	@ sign, data.190,
	mov	r8, r0, lsr #23	@ data.191, tmp223,
	eorne	r2, r4, sl	@ data.190, sign, tmp237
	orr	r8, r8, r1, asl #9	@, data.191, data.191,,
	strh	r2, [r3, #0]	@ movhi	@ data.190,* s16src.188
	mov	r0, r8, asr #31	@ sign, data.191,
	cmp	r0, r8, asr #15	@ sign, data.191,
	eorne	r8, r0, sl	@ data.191, sign, tmp237
	subs	ip, ip, #1	@ ivtmp.183, ivtmp.183,
	strh	r8, [r3, #2]	@ movhi	@ data.191,
	add	r3, r3, #4	@ s16src.188, s16src.188,
	bne	.L22	@,
.L23:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L16:
	cmp	r1, #0	@ samples,
	beq	.L23	@,
	ldrh	ip, [r0, #2]	@ data_R,
	mov	r6, r2	@ pretmp.146, s32Gain_L
	mov	r7, r6, asr #31	@ pretmp.146
	ldrsh	sl, [r0, #0]	@ tmp194,* ps16PcmBuf
	mov	r4, r3	@ pretmp.192, s32Gain_R
	mov	r5, r4, asr #31	@ pretmp.192
	sub	r1, r1, #1	@ tmp238, samples,
	add	r0, r0, #4	@ s16src, ps16PcmBuf,
	sxth	r9, ip	@ data_R, data_R
	subs	ip, r1, #0	@, tmp238
	mov	r2, sl	@, tmp194
	mov	r3, r2, asr #31	@
	strd	r2, [fp, #-52]	@,,
	and	sl, r1, #1	@ tmp239, tmp238,
	ldr	r1, [fp, #-48]	@, %sfp
	mov	r2, r9	@, data_R
	mov	r3, r2, asr #31	@
	strd	r2, [fp, #-68]	@,,
	ldr	r2, [fp, #-52]	@, %sfp
	mul	r3, r6, r1	@ tmp196, pretmp.146,
	ldr	r9, [fp, #-64]	@, %sfp
	mla	r1, r2, r7, r3	@ tmp242,, pretmp.146, tmp196
	str	ip, [fp, #-60]	@, %sfp
	umull	r2, r3, r6, r2	@, pretmp.146, tmp3
	mul	ip, r4, r9	@ tmp204, pretmp.192,
	ldr	r9, [fp, #-68]	@, %sfp
	strd	r2, [fp, #-76]	@,,
	add	r3, r1, r3	@, tmp242,
	str	r3, [fp, #-72]	@, %sfp
	umull	r2, r3, r4, r9	@, pretmp.192, tmp3
	mla	ip, r9, r5, ip	@ tmp245,, pretmp.192, tmp204
	ldr	r9, [fp, #-76]	@, %sfp
	strd	r2, [fp, #-52]	@,,
	mov	r1, r9, lsr #23	@ tmp229,,
	ldr	r2, [fp, #-72]	@, %sfp
	orr	r9, r1, r2, asl #9	@, tmp244, tmp229,,
	strh	r9, [r8, #0]	@ movhi	@ tmp244,* ps16PcmBuf
	add	r2, ip, r3	@, tmp245,
	ldr	r9, [fp, #-52]	@, %sfp
	str	r2, [fp, #-48]	@, %sfp
	ldr	ip, [fp, #-48]	@, %sfp
	mov	r1, r9, lsr #23	@ tmp231,,
	orr	r3, r1, ip, asl #9	@, tmp247, tmp231,,
	strh	r3, [r8, #2]	@ movhi	@ tmp247,
	beq	.L23	@,
	cmp	sl, #0	@ tmp239,
	beq	.L31	@,
	ldr	r3, [fp, #-60]	@, %sfp
	ldrh	r8, [r0, #2]	@ data_R,
	subs	r2, r3, #1	@,,
	str	r2, [fp, #-60]	@, %sfp
	ldrsh	r2, [r0, #0]	@ tmp301,* s16src
	sxth	r8, r8	@ data_R, data_R
	mov	r3, r2, asr #31	@ tmp302
	mov	r9, r8, asr #31	@ data_R
	mul	r1, r6, r3	@ tmp304, pretmp.146,
	mul	ip, r4, r9	@ tmp314, pretmp.192, data_R
	mla	r9, r2, r7, r1	@ tmp305, tmp302, pretmp.146, tmp304
	umull	r2, r3, r6, r2	@ tmp306, pretmp.146, tmp302
	mla	ip, r8, r5, ip	@ tmp315, data_R, pretmp.192, tmp314
	add	r3, r9, r3	@, tmp305,
	umull	r8, r9, r4, r8	@ tmp316, pretmp.192, data_R
	mov	r1, r2, lsr #23	@ tmp309, tmp306,
	orr	r1, r1, r3, asl #9	@, tmp310, tmp309,,
	strh	r1, [r0, #0]	@ movhi	@ tmp310,* s16src
	add	r9, ip, r9	@, tmp315,
	mov	ip, r8, lsr #23	@ tmp319, tmp316,
	orr	r3, ip, r9, asl #9	@, tmp320, tmp319,,
	strh	r3, [r0, #2]	@ movhi	@ tmp320,
	add	r0, r0, #4	@ s16src, s16src,
	beq	.L23	@,
.L31:
	ldr	sl, [fp, #-60]	@ ivtmp.165, %sfp
	strd	r4, [fp, #-52]	@ pretmp.192,,
.L19:
	ldrsh	r4, [r0, #0]	@ tmp251,* s16src
	add	r1, r0, #4	@ tmp240, s16src,
	ldrsh	ip, [r0, #4]	@ tmp274,
	subs	sl, sl, #2	@ ivtmp.165, ivtmp.165,
	ldrh	r2, [r0, #2]	@ data_R,
	mov	r5, r4, asr #31	@ tmp252
	mov	r8, ip	@, tmp274
	mov	r9, r8, asr #31	@
	strd	r8, [fp, #-60]	@,,
	sxth	r2, r2	@ data_R, data_R
	ldr	r9, [fp, #-48]	@, %sfp
	mul	r8, r6, r5	@ tmp254, pretmp.146,
	ldr	r5, [fp, #-52]	@, %sfp
	mov	r3, r2, asr #31	@ data_R
	mul	ip, r5, r3	@ tmp264,, data_R
	mla	r3, r4, r7, r8	@ tmp255, tmp252, pretmp.146, tmp254
	umull	r4, r5, r6, r4	@ tmp256, pretmp.146, tmp252
	mla	ip, r2, r9, ip	@ tmp265, data_R,, tmp264
	ldr	r9, [fp, #-52]	@, %sfp
	add	r5, r3, r5	@, tmp255,
	umull	r2, r3, r9, r2	@ tmp266,, data_R
	mov	r8, r4, lsr #23	@ tmp259, tmp256,
	orr	r4, r8, r5, asl #9	@, tmp260, tmp259,,
	strh	r4, [r0, #0]	@ movhi	@ tmp260,* s16src
	add	r3, ip, r3	@, tmp265,
	ldr	r9, [fp, #-56]	@, %sfp
	mov	ip, r2, lsr #23	@ tmp269, tmp266,
	orr	r2, ip, r3, asl #9	@, tmp270, tmp269,,
	strh	r2, [r0, #2]	@ movhi	@ tmp270,
	ldrh	r5, [r1, #2]	@ data_R,
	mul	r8, r6, r9	@ tmp277, pretmp.146,
	ldr	r9, [fp, #-52]	@, %sfp
	sxth	r2, r5	@ data_R, data_R
	ldr	r4, [fp, #-60]	@, %sfp
	mov	r3, r2, asr #31	@ data_R
	mul	ip, r9, r3	@ tmp287,, data_R
	ldr	r3, [fp, #-48]	@, %sfp
	mla	r8, r4, r7, r8	@ tmp278,, pretmp.146, tmp277
	mla	ip, r2, r3, ip	@ tmp288, data_R,, tmp287
	umull	r4, r5, r6, r4	@ tmp279, pretmp.146, tmp9
	umull	r2, r3, r9, r2	@ tmp289,, data_R
	add	r5, r8, r5	@, tmp278,
	add	r3, ip, r3	@, tmp288,
	mov	r8, r4, lsr #23	@ tmp282, tmp279,
	orr	r8, r8, r5, asl #9	@, tmp283, tmp282,,
	strh	r8, [r0, #4]	@ movhi	@ tmp283,
	add	r0, r1, #4	@ s16src, tmp240,
	mov	ip, r2, lsr #23	@ tmp292, tmp289,
	orr	r3, ip, r3, asl #9	@, tmp293, tmp292,,
	strh	r3, [r1, #2]	@ movhi	@ tmp293,
	bne	.L19	@,
	b	.L23	@
	.fnend
	.size	UTILS_GainProcessFrame_16BIT, .-UTILS_GainProcessFrame_16BIT
	.align	2
	.global	UTILS_GainProcessFrame_16BIT_Pro
	.type	UTILS_GainProcessFrame_16BIT_Pro, %function
UTILS_GainProcessFrame_16BIT_Pro:
	.fnstart
.LFB9:
	@ args = 4, pretend = 0, frame = 32
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
	ldr	ip, [fp, #4]	@ s32Gain_R, s32Gain_R
	cmp	ip, #8388608	@ s32Gain_R,
	cmple	r3, #8388608	@, s32Gain_L,
	ble	.L33	@,
	cmp	r2, #0	@ samples,
	beq	.L40	@,
	mov	r4, ip	@, s32Gain_R
	mov	r5, r4, asr #31	@
	mov	r8, r3	@ pretmp.285, s32Gain_L
	mov	r9, r8, asr #31	@ pretmp.285
	mov	ip, r1	@ s16dest.280, ps16PcmOutBuf
	strd	r4, [fp, #-52]	@,,
.L39:
	ldrh	r4, [r0, #2]	@ data_R.278,
	ldrsh	r6, [r0, #0]	@ tmp178,* s16src.279
	add	r0, r0, #4	@ s16src.279, s16src.279,
	ldr	sl, [fp, #-52]	@, %sfp
	sxth	r4, r4	@ data_R.278, data_R.278
	mov	r7, r6, asr #31	@ tmp177
	mov	r5, r4, asr #31	@ data_R.278
	mul	r1, r8, r7	@ tmp180, pretmp.285,
	mul	r3, sl, r5	@ tmp190,, data_R.278
	ldr	sl, [fp, #-48]	@, %sfp
	mla	r5, r6, r9, r1	@ tmp265, tmp177, pretmp.285, tmp180
	ldr	r1, [fp, #-52]	@, %sfp
	umull	r6, r7, r8, r6	@ tmp181, pretmp.285, tmp177
	mla	r3, r4, sl, r3	@ tmp268, data_R.278,, tmp190
	add	r7, r5, r7	@, tmp265,
	umull	r4, r5, r1, r4	@ tmp191,, data_R.278
	mov	r1, r6, lsr #23	@ data.282, tmp181,
	orr	r1, r1, r7, asl #9	@, data.282, data.282,,
	add	r5, r3, r5	@, tmp268,
	mov	r3, r1, asr #31	@ sign, data.282,
	cmp	r3, r1, asr #15	@ sign, data.282,
	mov	r6, r4, lsr #23	@ data.283, tmp191,
	orr	r6, r6, r5, asl #9	@, data.283, data.283,,
	movwne	r4, #32767	@,
	eorne	r1, r3, r4	@ data.282, sign,
	strh	r1, [ip, #0]	@ movhi	@ data.282,* s16dest.280
	mov	r3, r6, asr #31	@ sign, data.283,
	cmp	r3, r6, asr #15	@ sign, data.283,
	movwne	r5, #32767	@,
	eorne	r6, r3, r5	@ data.283, sign,
	subs	r2, r2, #1	@ ivtmp.274, ivtmp.274,
	strh	r6, [ip, #2]	@ movhi	@ data.283,
	add	ip, ip, #4	@ s16dest.280, s16dest.280,
	bne	.L39	@,
.L40:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L33:
	cmp	r2, #0	@ samples,
	beq	.L40	@,
	ldrh	r6, [r0, #2]	@ data_R,
	mov	r4, ip	@, s32Gain_R
	mov	r5, r4, asr #31	@
	ldrsh	r7, [r0], #4	@ tmp162,
	sub	r2, r2, #1	@ tmp206, samples,
	strd	r4, [fp, #-52]	@,,
	mov	r8, r3	@ pretmp.229, s32Gain_L
	mov	r9, r8, asr #31	@ pretmp.229
	ldr	sl, [fp, #-52]	@, %sfp
	sxth	r6, r6	@ data_R, data_R
	subs	r5, r2, #0	@, tmp206
	str	r5, [fp, #-56]	@, %sfp
	mov	r4, r7	@ tmp161, tmp162
	mov	r5, r4, asr #31	@ tmp161
	and	ip, r2, #1	@, tmp206,
	mov	r7, r6, asr #31	@ data_R
	str	ip, [fp, #-64]	@, %sfp
	mul	r2, r8, r5	@ tmp164, pretmp.229,
	add	r3, r1, #4	@ s16dest, ps16PcmOutBuf,
	mul	ip, sl, r7	@ tmp172,, data_R
	ldr	sl, [fp, #-48]	@, %sfp
	mla	r7, r4, r9, r2	@ tmp211, tmp161, pretmp.229, tmp164
	ldr	r2, [fp, #-52]	@, %sfp
	umull	r4, r5, r8, r4	@ tmp165, pretmp.229, tmp161
	mla	ip, r6, sl, ip	@ tmp214, data_R,, tmp172
	add	r5, r7, r5	@, tmp211,
	umull	r6, r7, r2, r6	@ tmp173,, data_R
	mov	r2, r4, lsr #23	@ tmp197, tmp165,
	orr	r2, r2, r5, asl #9	@, tmp213, tmp197,,
	strh	r2, [r1, #0]	@ movhi	@ tmp213,* ps16PcmOutBuf
	add	r7, ip, r7	@, tmp214,
	mov	ip, r6, lsr #23	@ tmp199, tmp173,
	orr	r2, ip, r7, asl #9	@, tmp216, tmp199,,
	strh	r2, [r1, #2]	@ movhi	@ tmp216,
	beq	.L40	@,
	ldr	r2, [fp, #-64]	@, %sfp
	cmp	r2, #0	@,
	beq	.L36	@,
	ldr	sl, [fp, #-56]	@, %sfp
	ldrh	r6, [r0, #2]	@ data_R,
	subs	r5, sl, #1	@,,
	str	r5, [fp, #-56]	@, %sfp
	ldrsh	r4, [r0], #4	@ tmp272,
	ldr	sl, [fp, #-52]	@, %sfp
	sxth	r6, r6	@ data_R, data_R
	ldr	ip, [fp, #-48]	@, %sfp
	mov	r5, r4, asr #31	@ tmp273
	mov	r7, r6, asr #31	@ data_R
	mul	r2, r8, r5	@ tmp275, pretmp.229,
	mul	r1, sl, r7	@ tmp285,, data_R
	mla	r7, r4, r9, r2	@ tmp276, tmp273, pretmp.229, tmp275
	umull	r4, r5, r8, r4	@ tmp277, pretmp.229, tmp273
	mla	r1, r6, ip, r1	@ tmp286, data_R,, tmp285
	add	r5, r7, r5	@, tmp276,
	umull	r6, r7, sl, r6	@ tmp287, tmp2, data_R
	mov	ip, r4, lsr #23	@ tmp280, tmp277,
	orr	r2, ip, r5, asl #9	@, tmp281, tmp280,,
	strh	r2, [r3, #0]	@ movhi	@ tmp281,* s16dest
	add	r7, r1, r7	@, tmp286,
	mov	r1, r6, lsr #23	@ tmp290, tmp287,
	orr	ip, r1, r7, asl #9	@, tmp291, tmp290,,
	strh	ip, [r3, #2]	@ movhi	@ tmp291,
	add	r3, r3, #4	@ s16dest, s16dest,
	beq	.L40	@,
.L36:
	mov	r2, r0	@ tmp208, s16src
	ldrh	r6, [r0, #2]	@ data_R,
	ldrsh	r4, [r2], #4	@ tmp221,
	ldr	r7, [fp, #-56]	@, %sfp
	ldr	sl, [fp, #-52]	@, %sfp
	sxth	r6, r6	@ data_R, data_R
	mov	r5, r4, asr #31	@ tmp222
	subs	r1, r7, #2	@,,
	mul	ip, r8, r5	@ tmp224, pretmp.229,
	mov	r7, r6, asr #31	@ data_R
	mla	r5, r4, r9, ip	@, tmp222, pretmp.229, tmp224
	str	r1, [fp, #-56]	@, %sfp
	mul	sl, sl, r7	@,, data_R
	ldr	r7, [fp, #-48]	@, %sfp
	add	r1, r3, #4	@ tmp209, s16dest,
	str	r5, [fp, #-72]	@, %sfp
	umull	r4, r5, r8, r4	@ tmp226, pretmp.229, tmp222
	mla	ip, r6, r7, sl	@, data_R,,
	ldr	sl, [fp, #-52]	@, %sfp
	ldr	r7, [fp, #-72]	@, %sfp
	add	r5, r7, r5	@,,
	umull	r6, r7, sl, r6	@ tmp236,, data_R
	str	ip, [fp, #-64]	@, %sfp
	mov	ip, r4, lsr #23	@ tmp229, tmp226,
	orr	sl, ip, r5, asl #9	@, tmp230, tmp229,,
	strh	sl, [r3, #0]	@ movhi	@ tmp230,* s16dest
	ldr	ip, [fp, #-64]	@, %sfp
	add	r7, ip, r7	@,,
	mov	r5, r6, lsr #23	@ tmp239, tmp236,
	orr	r6, r5, r7, asl #9	@, tmp240, tmp239,,
	strh	r6, [r3, #2]	@ movhi	@ tmp240,
	ldrh	r4, [r2, #2]	@ data_R,
	ldrsh	r6, [r0, #4]	@ tmp245,
	add	r0, r2, #4	@ s16src, tmp208,
	ldr	sl, [fp, #-52]	@, %sfp
	sxth	r4, r4	@ data_R, data_R
	mov	r7, r6, asr #31	@ tmp246
	mov	r5, r4, asr #31	@ data_R
	mul	ip, r8, r7	@ tmp248, pretmp.229,
	mul	r2, sl, r5	@ tmp258,, data_R
	ldr	sl, [fp, #-48]	@, %sfp
	mla	r5, r6, r9, ip	@ tmp249, tmp246, pretmp.229, tmp248
	ldr	ip, [fp, #-52]	@, %sfp
	umull	r6, r7, r8, r6	@ tmp250, pretmp.229, tmp246
	mla	r2, r4, sl, r2	@ tmp259, data_R,, tmp258
	add	r7, r5, r7	@, tmp249,
	umull	r4, r5, ip, r4	@ tmp260,, data_R
	mov	ip, r6, lsr #23	@ tmp253, tmp250,
	orr	ip, ip, r7, asl #9	@, tmp254, tmp253,,
	strh	ip, [r3, #4]	@ movhi	@ tmp254,
	add	r5, r2, r5	@, tmp259,
	add	r3, r1, #4	@ s16dest, tmp209,
	mov	r2, r4, lsr #23	@ tmp263, tmp260,
	orr	ip, r2, r5, asl #9	@, tmp264, tmp263,,
	strh	ip, [r1, #2]	@ movhi	@ tmp264,
	bne	.L36	@,
	b	.L40	@
	.fnend
	.size	UTILS_GainProcessFrame_16BIT_Pro, .-UTILS_GainProcessFrame_16BIT_Pro
	.align	2
	.global	UTILS_GainProcessFrame_24BIT
	.type	UTILS_GainProcessFrame_24BIT, %function
UTILS_GainProcessFrame_24BIT:
	.fnstart
.LFB10:
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
	cmp	r3, #8388608	@ s32Gain_R,
	cmple	r2, #8388608	@, s32Gain_L,
	ble	.L50	@,
	cmp	r1, #0	@ samples,
	beq	.L55	@,
	ldr	r6, [r0, #0]	@ tmp204,* ps32PcmBuf
	sub	sl, r1, #1	@ tmp234, samples,
	ldr	r8, [r0, #4]	@ data_R.354,
	mov	r4, r2	@ pretmp.360, s32Gain_L
	mov	r5, r4, asr #31	@ pretmp.360
	and	r7, sl, #1	@, tmp234,
	str	r7, [fp, #-52]	@, %sfp
	mov	r6, r6, asr #8	@ tmp203, tmp204,
	mov	r2, r3	@ pretmp.361, s32Gain_R
	mov	r3, r2, asr #31	@ pretmp.361
	mov	r8, r8, asr #8	@ tmp213, data_R.354,
	subs	r9, sl, #0	@, tmp234
	mov	r7, r6, asr #31	@ tmp205
	str	r9, [fp, #-60]	@, %sfp
	mul	r1, r4, r7	@ tmp207, pretmp.360,
	mov	r9, r8, asr #31	@ tmp214
	mul	sl, r2, r9	@ tmp216, pretmp.361,
	add	ip, r0, #8	@ s32src.355, ps32PcmBuf,
	mla	r9, r6, r5, r1	@ tmp288, tmp205, pretmp.360, tmp207
	umull	r6, r7, r4, r6	@ tmp208, pretmp.360, tmp205
	mla	sl, r8, r3, sl	@ tmp291, tmp214, pretmp.361, tmp216
	add	r7, r9, r7	@, tmp288,
	umull	r8, r9, r2, r8	@ tmp217, pretmp.361, tmp214
	mov	r1, r6, lsr #23	@ tmp226, tmp208,
	orr	r1, r1, r7, asl #9	@, tmp290, tmp226,,
	add	r9, sl, r9	@, tmp291,
	mov	r1, r1, asl #8	@ tmp212, tmp290,
	str	r1, [r0, #0]	@ tmp212,* ps32PcmBuf
	mov	r1, r8, lsr #23	@ tmp228, tmp217,
	orr	r1, r1, r9, asl #9	@, tmp293, tmp228,,
	mov	r1, r1, asl #8	@ tmp221, tmp293,
	str	r1, [r0, #4]	@ tmp221,
	beq	.L55	@,
	ldr	r6, [fp, #-52]	@, %sfp
	cmp	r6, #0	@,
	beq	.L71	@,
	ldr	r9, [fp, #-60]	@, %sfp
	ldr	r6, [ip, #4]	@ data_R.354,
	subs	r9, r9, #1	@,,
	str	r9, [fp, #-60]	@, %sfp
	ldr	r0, [ip, #0]	@ tmp367,* s32src.355
	mov	r6, r6, asr #8	@ tmp379, data_R.354,
	mov	r0, r0, asr #8	@ tmp368, tmp367,
	mov	r7, r6, asr #31	@ tmp380
	mul	sl, r2, r7	@ tmp382, pretmp.361,
	mov	r1, r0, asr #31	@ tmp369
	mul	r8, r4, r1	@ tmp371, pretmp.360,
	mla	r7, r0, r5, r8	@ tmp372, tmp369, pretmp.360, tmp371
	umull	r0, r1, r4, r0	@ tmp373, pretmp.360, tmp369
	mla	sl, r6, r3, sl	@ tmp383, tmp380, pretmp.361, tmp382
	add	r1, r7, r1	@, tmp372,
	umull	r6, r7, r2, r6	@ tmp384, pretmp.361, tmp380
	mov	r8, r0, lsr #23	@ tmp376, tmp373,
	orr	r8, r8, r1, asl #9	@, tmp377, tmp376,,
	add	r7, sl, r7	@, tmp383,
	mov	r8, r8, asl #8	@ tmp378, tmp377,
	str	r8, [ip, #0]	@ tmp378,* s32src.355
	mov	r0, r6, lsr #23	@ tmp387, tmp384,
	orr	r1, r0, r7, asl #9	@, tmp388, tmp387,,
	mov	r0, r1, asl #8	@ tmp389, tmp388,
	str	r0, [ip, #4]	@ tmp389,
	add	ip, ip, #8	@ s32src.355, s32src.355,
	beq	.L55	@,
.L71:
	ldr	sl, [fp, #-60]	@ ivtmp.352, %sfp
	strd	r2, [fp, #-52]	@ pretmp.361,,
.L54:
	ldr	r0, [ip, #0]	@ tmp297,* s32src.355
	add	r6, ip, #8	@ tmp236, s32src.355,
	ldr	r1, [ip, #8]	@ tmp323,
	subs	sl, sl, #2	@ ivtmp.352, ivtmp.352,
	ldr	r2, [ip, #4]	@ data_R.354,
	mov	r0, r0, asr #8	@ tmp298, tmp297,
	mov	r7, r1, asr #8	@ tmp324, tmp323,
	mov	r1, r0, asr #31	@ tmp299
	mov	r2, r2, asr #8	@ tmp309, data_R.354,
	mul	r8, r4, r1	@, pretmp.360,
	mov	r3, r2, asr #31	@ tmp310
	str	r8, [fp, #-64]	@, %sfp
	mov	r8, r7	@, tmp324
	mov	r9, r8, asr #31	@
	ldr	r1, [fp, #-64]	@, %sfp
	strd	r8, [fp, #-60]	@,,
	ldr	r9, [fp, #-52]	@, %sfp
	ldr	r8, [fp, #-52]	@, %sfp
	mul	r7, r9, r3	@ tmp312,,
	ldr	r9, [fp, #-48]	@, %sfp
	mla	r3, r0, r5, r1	@ tmp302, tmp299, pretmp.360,
	umull	r0, r1, r4, r0	@ tmp303, pretmp.360, tmp299
	mla	r7, r2, r9, r7	@ tmp313, tmp310,, tmp312
	add	r1, r3, r1	@, tmp302,
	umull	r2, r3, r8, r2	@ tmp314,, tmp310
	mov	r9, r0, lsr #23	@ tmp306, tmp303,
	orr	r8, r9, r1, asl #9	@, tmp307, tmp306,,
	add	r0, r7, r3	@, tmp313,
	mov	r7, r8, asl #8	@ tmp308, tmp307,
	str	r7, [ip, #0]	@ tmp308,* s32src.355
	ldr	r3, [fp, #-56]	@, %sfp
	mov	r9, r2, lsr #23	@ tmp317, tmp314,
	orr	r8, r9, r0, asl #9	@, tmp318, tmp317,,
	mul	r7, r4, r3	@ tmp327, pretmp.360,
	mov	r1, r8, asl #8	@ tmp319, tmp318,
	str	r1, [ip, #4]	@ tmp319,
	ldr	r2, [r6, #4]	@ data_R.354,
	ldr	r0, [fp, #-60]	@, %sfp
	ldr	r9, [fp, #-52]	@, %sfp
	mov	r2, r2, asr #8	@ tmp335, data_R.354,
	mla	r8, r0, r5, r7	@ tmp328,, pretmp.360, tmp327
	mov	r3, r2, asr #31	@ tmp336
	mul	r7, r9, r3	@ tmp338,,
	ldr	r3, [fp, #-48]	@, %sfp
	umull	r0, r1, r4, r0	@ tmp329, pretmp.360, tmp9
	mla	r7, r2, r3, r7	@ tmp339, tmp336,, tmp338
	add	r1, r8, r1	@, tmp328,
	umull	r2, r3, r9, r2	@ tmp340,, tmp336
	mov	r8, r0, lsr #23	@ tmp332, tmp329,
	orr	r8, r8, r1, asl #9	@, tmp333, tmp332,,
	add	r3, r7, r3	@, tmp339,
	mov	r8, r8, asl #8	@ tmp334, tmp333,
	str	r8, [ip, #8]	@ tmp334,
	add	ip, r6, #8	@ s32src.355, tmp236,
	mov	r1, r2, lsr #23	@ tmp343, tmp340,
	orr	r0, r1, r3, asl #9	@, tmp344, tmp343,,
	mov	r2, r0, asl #8	@ tmp345, tmp344,
	str	r2, [r6, #4]	@ tmp345,
	bne	.L54	@,
.L55:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L50:
	cmp	r1, #0	@ samples,
	beq	.L55	@,
	ldr	r6, [r0, #0]	@ tmp187,* ps32PcmBuf
	sub	r1, r1, #1	@ tmp230, samples,
	ldr	r8, [r0, #4]	@ data_R,
	mov	r4, r2	@ pretmp.324, s32Gain_L
	mov	r5, r4, asr #31	@ pretmp.324
	subs	r7, r1, #0	@, tmp230
	str	r7, [fp, #-60]	@, %sfp
	mov	r7, r6, asr #31	@ tmp186
	mov	r2, r3	@ pretmp.359, s32Gain_R
	mov	r3, r2, asr #31	@ pretmp.359
	mov	r9, r8, asr #31	@ data_R
	and	sl, r1, #1	@, tmp230,
	mul	r1, r4, r7	@ tmp189, pretmp.324,
	str	sl, [fp, #-52]	@, %sfp
	mul	sl, r2, r9	@ tmp197, pretmp.359, data_R
	add	ip, r0, #8	@ s32src, ps32PcmBuf,
	mla	r9, r6, r5, r1	@ tmp238, tmp186, pretmp.324, tmp189
	umull	r6, r7, r4, r6	@ tmp190, pretmp.324, tmp186
	mla	sl, r8, r3, sl	@ tmp241, data_R, pretmp.359, tmp197
	add	r7, r9, r7	@, tmp238,
	umull	r8, r9, r2, r8	@ tmp198, pretmp.359, data_R
	mov	r1, r6, lsr #23	@ tmp222, tmp190,
	orr	r1, r1, r7, asl #9	@, tmp240, tmp222,,
	str	r1, [r0, #0]	@ tmp240,* ps32PcmBuf
	add	r9, sl, r9	@, tmp241,
	mov	r1, r8, lsr #23	@ tmp224, tmp198,
	orr	r1, r1, r9, asl #9	@, tmp243, tmp224,,
	str	r1, [r0, #4]	@ tmp243,
	beq	.L55	@,
	ldr	sl, [fp, #-52]	@, %sfp
	cmp	sl, #0	@,
	beq	.L69	@,
	ldr	r1, [fp, #-60]	@, %sfp
	ldr	r6, [ip, #4]	@ data_R,
	subs	r0, r1, #1	@,,
	str	r0, [fp, #-60]	@, %sfp
	ldr	r0, [ip, #0]	@ tmp347,* s32src
	mov	r7, r6, asr #31	@ data_R
	mul	sl, r2, r7	@ tmp359, pretmp.359, data_R
	mov	r1, r0, asr #31	@ tmp348
	mul	r8, r4, r1	@ tmp350, pretmp.324,
	mla	r7, r0, r5, r8	@ tmp351, tmp348, pretmp.324, tmp350
	umull	r0, r1, r4, r0	@ tmp352, pretmp.324, tmp348
	mla	sl, r6, r3, sl	@ tmp360, data_R, pretmp.359, tmp359
	add	r1, r7, r1	@, tmp351,
	umull	r6, r7, r2, r6	@ tmp361, pretmp.359, data_R
	mov	r8, r0, lsr #23	@ tmp355, tmp352,
	orr	r8, r8, r1, asl #9	@, tmp356, tmp355,,
	str	r8, [ip, #0]	@ tmp356,* s32src
	add	r7, sl, r7	@, tmp360,
	mov	r0, r6, lsr #23	@ tmp364, tmp361,
	orr	r1, r0, r7, asl #9	@, tmp365, tmp364,,
	str	r1, [ip, #4]	@ tmp365,
	add	ip, ip, #8	@ s32src, s32src,
	beq	.L55	@,
.L69:
	ldr	sl, [fp, #-60]	@ ivtmp.343, %sfp
	strd	r2, [fp, #-52]	@ pretmp.359,,
.L53:
	ldr	r0, [ip, #0]	@ tmp247,* s32src
	add	r6, ip, #8	@ tmp232, s32src,
	ldr	r7, [ip, #8]	@ tmp269,
	subs	sl, sl, #2	@ ivtmp.343, ivtmp.343,
	ldr	r2, [ip, #4]	@ data_R,
	mov	r1, r0, asr #31	@ tmp248
	mul	r8, r4, r1	@, pretmp.324,
	mov	r3, r2, asr #31	@ data_R
	str	r8, [fp, #-64]	@, %sfp
	mov	r8, r7	@, tmp269
	mov	r9, r8, asr #31	@
	strd	r8, [fp, #-60]	@,,
	ldr	r9, [fp, #-52]	@, %sfp
	ldr	r1, [fp, #-64]	@, %sfp
	mul	r7, r9, r3	@ tmp259,, data_R
	ldr	r9, [fp, #-48]	@, %sfp
	mla	r3, r0, r5, r1	@ tmp251, tmp248, pretmp.324,
	umull	r0, r1, r4, r0	@ tmp252, pretmp.324, tmp248
	mla	r7, r2, r9, r7	@ tmp260, data_R,, tmp259
	ldr	r9, [fp, #-52]	@, %sfp
	add	r1, r3, r1	@, tmp251,
	umull	r2, r3, r9, r2	@ tmp261,, data_R
	mov	r8, r0, lsr #23	@ tmp255, tmp252,
	orr	r0, r8, r1, asl #9	@, tmp256, tmp255,,
	str	r0, [ip, #0]	@ tmp256,* s32src
	add	r3, r7, r3	@, tmp260,
	ldr	r9, [fp, #-56]	@, %sfp
	mov	r7, r2, lsr #23	@ tmp264, tmp261,
	orr	r2, r7, r3, asl #9	@, tmp265, tmp264,,
	str	r2, [ip, #4]	@ tmp265,
	ldr	r2, [r6, #4]	@ data_R,
	ldr	r0, [fp, #-60]	@, %sfp
	ldr	r1, [fp, #-52]	@, %sfp
	mov	r3, r2, asr #31	@ data_R
	mul	r8, r4, r9	@ tmp272, pretmp.324,
	ldr	r9, [fp, #-48]	@, %sfp
	mla	r8, r0, r5, r8	@ tmp273,, pretmp.324, tmp272
	mul	r7, r1, r3	@ tmp281,, data_R
	umull	r0, r1, r4, r0	@ tmp274, pretmp.324, tmp9
	mla	r7, r2, r9, r7	@ tmp282, data_R,, tmp281
	add	r1, r8, r1	@, tmp273,
	ldr	r8, [fp, #-52]	@, %sfp
	umull	r2, r3, r8, r2	@ tmp283,, data_R
	mov	r8, r0, lsr #23	@ tmp277, tmp274,
	orr	r8, r8, r1, asl #9	@, tmp278, tmp277,,
	str	r8, [ip, #8]	@ tmp278,
	add	r0, r7, r3	@, tmp282,
	add	ip, r6, #8	@ s32src, tmp232,
	mov	r1, r2, lsr #23	@ tmp286, tmp283,
	orr	r3, r1, r0, asl #9	@, tmp287, tmp286,,
	str	r3, [r6, #4]	@ tmp287,
	bne	.L53	@,
	b	.L55	@
	.fnend
	.size	UTILS_GainProcessFrame_24BIT, .-UTILS_GainProcessFrame_24BIT
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	g_dB2LinearTab, %object
	.size	g_dB2LinearTab, 560
g_dB2LinearTab:
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
	.word	747
	.word	666
	.word	593
	.word	529
	.word	471
	.word	420
	.word	374
	.word	333
	.word	297
	.word	265
	.word	236
	.word	210
	.word	187
	.word	167
	.word	149
	.word	132
	.word	118
	.word	105
	.word	94
	.word	83
	.word	74
	.word	66
	.word	59
	.word	52
	.word	47
	.word	42
	.word	37
	.word	33
	.word	29
	.word	26
	.word	23
	.word	21
	.word	18
	.word	16
	.word	14
	.word	13
	.word	11
	.word	10
	.word	9
	.word	0
	.word	0
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
