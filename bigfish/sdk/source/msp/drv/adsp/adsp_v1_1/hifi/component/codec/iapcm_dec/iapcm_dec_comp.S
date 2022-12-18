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
	.file	"iapcm_dec_comp.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(iapcm_dec_comp)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_adsp) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD
@ drivers/msp/adsp/adsp_v1_1/./hifi/component/codec/iapcm_dec/.iapcm_dec_comp.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/adsp/adsp_v1_1/./hifi/component/codec/iapcm_dec/iapcm_dec_comp.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/adsp/adsp_v1_1/./hifi/component/codec/iapcm_dec/iapcm_dec_comp.o
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
	.type	Aflt_PCMDecCompSetConfig, %function
Aflt_PCMDecCompSetConfig:
	.fnstart
.LFB151:
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
	mov	r1, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	Aflt_PCMDecCompSetConfig, .-Aflt_PCMDecCompSetConfig
	.align	2
	.type	Aflt_PCMDecCompGetConfig, %function
Aflt_PCMDecCompGetConfig:
	.fnstart
.LFB152:
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
	mov	r1, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	Aflt_PCMDecCompGetConfig, .-Aflt_PCMDecCompGetConfig
	.align	2
	.type	Aflt_PCMDecCompGetParameter, %function
Aflt_PCMDecCompGetParameter:
	.fnstart
.LFB154:
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
	cmp	r0, #0	@ hAde,
	cmpne	r2, #0	@, pstParameterStructure,
	movweq	r2, #:lower16:-2147479551	@ D.4490,
	movteq	r2, #:upper16:-2147479551	@ D.4490,
	movne	r2, #0	@ D.4490,
	movne	r3, #0	@ D.4490,
	mvneq	r3, #0	@ D.4490,
	mov	r0, r2	@, D.4490
	mov	r1, r3	@, D.4490
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	Aflt_PCMDecCompGetParameter, .-Aflt_PCMDecCompGetParameter
	.align	2
	.type	Aflt_PCMDecCompSetInputBuffer, %function
Aflt_PCMDecCompSetInputBuffer:
	.fnstart
.LFB157:
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
	cmp	r0, #0	@ hAde,
	cmpne	r1, #0	@, pInBuf,
	strne	r1, [r0, #4]	@ pInBuf, <variable>.pu8InputBuf
	movweq	r4, #:lower16:-2147479551	@ D.4548,
	movteq	r4, #:upper16:-2147479551	@ D.4548,
	mvneq	r5, #0	@ D.4548,
	movne	r4, #0	@ D.4548,
	movne	r5, #0	@ D.4548,
	strne	r2, [r0, #8]	@ u32InBufSize, <variable>.u32InBufSize
	mov	r1, r5	@, D.4548
	mov	r0, r4	@, D.4548
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	Aflt_PCMDecCompSetInputBuffer, .-Aflt_PCMDecCompSetInputBuffer
	.align	2
	.type	Aflt_PCMDecCompSetOutputBuffer, %function
Aflt_PCMDecCompSetOutputBuffer:
	.fnstart
.LFB158:
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
	cmp	r0, #0	@ hAde,
	cmpne	r1, #0	@, pOutBuf,
	strne	r1, [r0, #12]	@ pOutBuf, <variable>.pu8OutBuf
	movweq	r4, #:lower16:-2147479551	@ D.4560,
	movteq	r4, #:upper16:-2147479551	@ D.4560,
	mvneq	r5, #0	@ D.4560,
	movne	r4, #0	@ D.4560,
	movne	r5, #0	@ D.4560,
	strne	r2, [r0, #16]	@ u32OutBufSize, <variable>.u32OutBufSize
	mov	r1, r5	@, D.4560
	mov	r0, r4	@, D.4560
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	Aflt_PCMDecCompSetOutputBuffer, .-Aflt_PCMDecCompSetOutputBuffer
	.align	2
	.type	Aflt_PCMDecCompGetInputBytesleft, %function
Aflt_PCMDecCompGetInputBytesleft:
	.fnstart
.LFB159:
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
	cmp	r0, #0	@ hAde
	ldrne	r0, [r0, #24]	@ <variable>.u32InPutByteLeft, <variable>.u32InPutByteLeft
	movweq	r2, #:lower16:-2147479551	@ D.4568,
	movteq	r2, #:upper16:-2147479551	@ D.4568,
	mvneq	r3, #0	@ D.4568,
	movne	r2, #0	@ D.4568,
	movne	r3, #0	@ D.4568,
	strne	r0, [r1, #0]	@ <variable>.u32InPutByteLeft,* pu32Bytesleft
	mov	r1, r3	@, D.4568
	mov	r0, r2	@, D.4568
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	Aflt_PCMDecCompGetInputBytesleft, .-Aflt_PCMDecCompGetInputBytesleft
	.align	2
	.type	Aflt_PCMDecCompGetMinInputBufSize, %function
Aflt_PCMDecCompGetMinInputBufSize:
	.fnstart
.LFB160:
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
	cmp	r0, #0	@ hAde,
	movweq	r2, #:lower16:-2147479551	@ D.4577,
	movteq	r2, #:upper16:-2147479551	@ D.4577,
	mvneq	r3, #0	@ D.4577,
	movne	r2, #0	@ D.4577,
	movne	r3, #0	@ D.4577,
	movne	r0, #30720	@ tmp137,
	strne	r0, [r1, #0]	@ tmp137,* pu32InBufsize
	mov	r1, r3	@, D.4577
	mov	r0, r2	@, D.4577
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	Aflt_PCMDecCompGetMinInputBufSize, .-Aflt_PCMDecCompGetMinInputBufSize
	.align	2
	.type	Aflt_PCMDecCompSetEosFlag, %function
Aflt_PCMDecCompSetEosFlag:
	.fnstart
.LFB163:
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
	cmp	r0, #0	@ hAde,
	movweq	r2, #:lower16:-2147479551	@ D.4650,
	movteq	r2, #:upper16:-2147479551	@ D.4650,
	movne	r2, #0	@ D.4650,
	movne	r3, #0	@ D.4650,
	mvneq	r3, #0	@ D.4650,
	mov	r0, r2	@, D.4650
	mov	r1, r3	@, D.4650
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	Aflt_PCMDecCompSetEosFlag, .-Aflt_PCMDecCompSetEosFlag
	.align	2
	.type	Aflt_PCMDecCompGetCurnFramePrivInfo, %function
Aflt_PCMDecCompGetCurnFramePrivInfo:
	.fnstart
.LFB161:
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #72
	sub	sp, sp, #72	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #0	@ hAde
	mov	r5, r1	@ pstFramePrivInfo, pstFramePrivInfo
	movweq	r2, #:lower16:-2147479551	@ D.4590,
	mvneq	r3, #0	@ D.4590,
	movteq	r2, #:upper16:-2147479551	@ D.4590,
	beq	.L31	@,
	ldr	r4, [r0, #28]	@ pstFrmInfo, <variable>.pstFrmInfo
	sub	r7, fp, #100	@ tmp138,,
	mov	r1, #72	@,
	mov	r0, r7	@, tmp138
	mov	r6, r1	@ tmp153,
	bl	__memzero	@
	mov	r1, #1	@ tmp139,
	mov	r0, #16	@ tmp140,
	str	r1, [fp, #-36]	@ tmp139, stFrame.bInterlace
	str	r0, [fp, #-64]	@ tmp140, stFrame.u32PcmBitDepth
	mov	r2, r6	@, tmp153
	ldr	ip, [r4, #12]	@ <variable>.outputSamps, <variable>.outputSamps
	mov	r1, r7	@, tmp138
	ldr	r0, [r5, #0]	@, <variable>.pOutPrivInfo
	mov	r3, ip, asl #1	@ tmp142, <variable>.outputSamps,
	str	r3, [fp, #-52]	@ tmp142, stFrame.u32PcmBytesPerFrame
	ldr	ip, [r4, #0]	@ <variable>.nChans, <variable>.nChans
	str	ip, [fp, #-76]	@ <variable>.nChans, stFrame.u32PcmChannels
	ldr	r3, [r4, #4]	@ <variable>.samprate, <variable>.samprate
	str	r3, [fp, #-88]	@ <variable>.samprate, stFrame.u32PcmSampleRate
	ldr	ip, [r4, #4]	@ <variable>.samprate, <variable>.samprate
	mov	r3, ip, asl #4	@ tmp146, <variable>.samprate,
	str	r3, [fp, #-92]	@ tmp146, stFrame.u32StreamBitRate
	ldr	ip, [r4, #0]	@ <variable>.nChans, <variable>.nChans
	str	ip, [fp, #-96]	@ <variable>.nChans, stFrame.u32StreamChannels
	ldr	r3, [r4, #4]	@ <variable>.samprate, <variable>.samprate
	str	r3, [fp, #-100]	@ <variable>.samprate, stFrame.u32StreamSampleRate
	bl	memcpy	@
	mov	r2, #0	@ D.4590,
	mov	r3, #0	@ D.4590,
	str	r6, [r5, #4]	@ tmp153, <variable>.u32OutPrivBytesProduced
.L31:
	mov	r1, r3	@, D.4590
	mov	r0, r2	@, D.4590
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	.fnend
	.size	Aflt_PCMDecCompGetCurnFramePrivInfo, .-Aflt_PCMDecCompGetCurnFramePrivInfo
	.align	2
	.type	Aflt_PCMDecCompEexcuteFrame, %function
Aflt_PCMDecCompEexcuteFrame:
	.fnstart
.LFB162:
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
	cmp	r0, #0	@ hAde,
	cmpne	r1, #0	@, pstExcuteFrame,
	mov	r5, r1	@ pstExcuteFrame, pstExcuteFrame
	mov	r4, r0	@ hAde, hAde
	movweq	r6, #:lower16:-2147479551	@ D.4618,
	movne	r8, #0	@, tmp148
	moveq	r8, #1	@, tmp148
	movteq	r6, #:upper16:-2147479551	@ D.4618,
	mvneq	r7, #0	@ D.4618,
	bne	.L42	@,
.L36:
	mov	r1, r7	@, D.4618
	mov	r0, r6	@, D.4618
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L42:
	ldr	r2, [r0, #4]	@ <variable>.pu8InputBuf, <variable>.pu8InputBuf
	mov	r0, r1	@, pstExcuteFrame
	mov	r1, #8	@,
	str	r2, [fp, #-52]	@ <variable>.pu8InputBuf, readPtr
	ldr	r3, [r4, #8]	@ <variable>.u32InBufSize, <variable>.u32InBufSize
	str	r3, [fp, #-48]	@ <variable>.u32InBufSize, bytesLeft
	ldr	sl, [r4, #8]	@ s32BytesPriv, <variable>.u32InBufSize
	bl	__memzero	@
	ldr	r3, [fp, #-48]	@ bytesLeft.88, bytesLeft
	cmp	r3, #7	@ bytesLeft.88,
	ble	.L43	@,
	sub	r7, fp, #52	@ tmp156,,
	sub	r6, fp, #48	@ tmp157,,
	ldr	r0, [r4, #0]	@, <variable>.hDecoder
	mov	r1, r7	@, tmp156
	mov	r2, r6	@, tmp157
	bl	PCMDecFindSyncWord	@
	cmp	r0, #0	@,
	blt	.L44	@,
	mov	r1, r7	@, tmp156
	mov	r2, r6	@, tmp157
	ldr	r0, [r4, #0]	@, <variable>.hDecoder
	ldr	r3, [r4, #12]	@, <variable>.pu8OutBuf
	bl	PCMDecDecodeFrame	@
	subs	r9, r0, #0	@ err,
	beq	.L45	@,
	movw	r6, #:lower16:-2147479550	@ D.4618,
	movt	r6, #:upper16:-2147479550	@ D.4618,
	mvn	r7, #0	@ D.4618,
	str	r8, [r5, #4]	@ tmp148, <variable>.u32OutDataBytesProduced
.L40:
	ldr	lr, [fp, #-48]	@ bytesLeft, bytesLeft
	rsb	sl, lr, sl	@ tmp181, bytesLeft, s32BytesPriv
	str	sl, [r5, #0]	@ tmp181, <variable>.u32InBytesConsumed
	b	.L36	@
.L45:
	sub	r6, fp, #72	@ tmp170,,
	ldr	r0, [r4, #0]	@, <variable>.hDecoder
	mov	r7, #0	@ D.4618,
	mov	r1, r6	@, tmp170
	bl	PCMDecGetFrameInfo	@
	mov	ip, r6	@ tmp186, tmp170
	ldmia	ip!, {r0, r1, r2, r3}	@ tmp186,,,,
	ldr	r8, [r4, #28]	@ <variable>.pstFrmInfo, <variable>.pstFrmInfo
	mov	r6, #0	@ D.4618,
	stmia	r8!, {r0, r1, r2, r3}	@ <variable>.pstFrmInfo,,,,
	ldr	r2, [ip, #0]	@ stFrameInfo, stFrameInfo
	str	r2, [r8, #0]	@ stFrameInfo,* <variable>.pstFrmInfo
	ldr	r0, [r4, #20]	@ <variable>.u32ByteConsume, <variable>.u32ByteConsume
	str	r9, [r4, #20]	@ err, <variable>.u32ByteConsume
	str	r0, [r4, #24]	@ <variable>.u32ByteConsume, <variable>.u32InPutByteLeft
	ldr	r3, [fp, #-60]	@ stFrameInfo.outputSamps, stFrameInfo.outputSamps
	mov	ip, r3, asl #1	@ tmp178, stFrameInfo.outputSamps,
	str	ip, [r5, #4]	@ tmp178, <variable>.u32OutDataBytesProduced
	b	.L40	@
.L43:
	ldr	ip, [r4, #20]	@ <variable>.u32ByteConsume, <variable>.u32ByteConsume
	rsb	r1, r3, sl	@ tmp151, bytesLeft.88, s32BytesPriv
	movw	r6, #:lower16:-2147479549	@ D.4618,
	mvn	r7, #0	@ D.4618,
	add	r0, ip, r1	@ tmp153, <variable>.u32ByteConsume, tmp151
	movt	r6, #:upper16:-2147479549	@ D.4618,
	str	r0, [r4, #20]	@ tmp153, <variable>.u32ByteConsume
	str	r8, [r5, #4]	@ tmp148, <variable>.u32OutDataBytesProduced
	b	.L36	@
.L44:
	ldr	r1, [fp, #-48]	@ bytesLeft, bytesLeft
	movw	r6, #:lower16:-2147479549	@ D.4618,
	ldr	r2, [r4, #20]	@ <variable>.u32ByteConsume, <variable>.u32ByteConsume
	movt	r6, #:upper16:-2147479549	@ D.4618,
	rsb	r0, r1, sl	@ tmp158, bytesLeft, s32BytesPriv
	mvn	r7, #0	@ D.4618,
	add	r3, r2, r0	@ tmp161, <variable>.u32ByteConsume, tmp158
	str	r3, [r4, #20]	@ tmp161, <variable>.u32ByteConsume
	ldr	lr, [fp, #-48]	@ bytesLeft, bytesLeft
	str	r8, [r5, #4]	@ tmp148, <variable>.u32OutDataBytesProduced
	rsb	sl, lr, sl	@ tmp163, bytesLeft, s32BytesPriv
	str	sl, [r5, #0]	@ tmp163, <variable>.u32InBytesConsumed
	b	.L36	@
	.fnend
	.size	Aflt_PCMDecCompEexcuteFrame, .-Aflt_PCMDecCompEexcuteFrame
	.align	2
	.type	Aflt_PCMDecCompRestoreSetting, %function
Aflt_PCMDecCompRestoreSetting:
	.fnstart
.LFB155:
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
	cmp	r0, #0	@ hAde,
	cmpne	r1, #0	@, pstSettingStructure,
	bne	.L50	@,
.L47:
	movw	r2, #:lower16:-2147479551	@ D.4504,
	movt	r2, #:upper16:-2147479551	@ D.4504,
	mvn	r3, #0	@ D.4504,
.L48:
	mov	r1, r3	@, D.4504
	mov	r0, r2	@, D.4504
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L50:
	ldr	lr, [r1, #16]	@ <variable>.bBigEndian, <variable>.bBigEndian
	sub	r3, fp, #12	@ tmp153,,
	str	lr, [fp, #-20]	@ <variable>.bBigEndian, sPcmDecoderParams.bBigEndian
	ldr	ip, [r1, #20]	@ <variable>.bInterlace, <variable>.bInterlace
	str	ip, [fp, #-16]	@ <variable>.bInterlace, sPcmDecoderParams.bInterlace
	ldr	r2, [r1, #12]	@ <variable>.u32SampleRate, <variable>.u32SampleRate
	str	r2, [fp, #-24]	@ <variable>.u32SampleRate, sPcmDecoderParams.u32SampleRate
	ldr	lr, [r1, #8]	@ <variable>.u32BitWidth, <variable>.u32BitWidth
	str	lr, [fp, #-28]	@ <variable>.u32BitWidth, sPcmDecoderParams.u32BitWidth
	ldr	ip, [r1, #4]	@ <variable>.u32ChnNumber, <variable>.u32ChnNumber
	str	ip, [fp, #-32]	@ <variable>.u32ChnNumber, sPcmDecoderParams.u32ChnNumber
	ldr	r2, [r1, #0]	@ <variable>.u32FrameSize, <variable>.u32FrameSize
	str	r2, [r3, #-24]!	@ <variable>.u32FrameSize, sPcmDecoderParams.u32FrameSize
	mov	r1, r3	@, tmp153
	ldr	r0, [r0, #0]	@, <variable>.hDecoder
	bl	SetPCMDecoderParam	@
	cmp	r0, #0	@,
	moveq	r2, #0	@ D.4504,
	moveq	r3, #0	@ D.4504,
	beq	.L48	@,
	b	.L47	@
	.fnend
	.size	Aflt_PCMDecCompRestoreSetting, .-Aflt_PCMDecCompRestoreSetting
	.global	__aeabi_uidiv
	.align	2
	.type	Aflt_PCMDecCompSetParameter, %function
Aflt_PCMDecCompSetParameter:
	.fnstart
.LFB153:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #24
	sub	sp, sp, #24	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #0	@ hAde,
	cmpne	r2, #0	@, pstParameterStructure,
	mov	r4, r0	@ hAde, hAde
	bne	.L58	@,
.L52:
	movw	r2, #:lower16:-2147479551	@ D.4470,
	movt	r2, #:upper16:-2147479551	@ D.4470,
	mvn	r3, #0	@ D.4470,
.L56:
	mov	r1, r3	@, D.4470
	mov	r0, r2	@, D.4470
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L58:
	cmp	r1, #0	@ u32ParamIndex,
	bne	.L52	@,
	ldrh	r5, [r2, #0]	@ <variable>.nChannels, <variable>.nChannels
	cmp	r5, #2	@ <variable>.nChannels,
	bhi	.L52	@,
	str	r5, [fp, #-40]	@ <variable>.nChannels, sPcmDecoderParams.u32ChnNumber
	ldrh	r0, [r2, #8]	@ <variable>.wBitsPerSample, <variable>.wBitsPerSample
	str	r0, [fp, #-36]	@ <variable>.wBitsPerSample, sPcmDecoderParams.u32BitWidth
	ldr	r0, [r2, #4]	@ <variable>.nSamplesPerSec, <variable>.nSamplesPerSec
	str	r0, [fp, #-32]	@ <variable>.nSamplesPerSec, sPcmDecoderParams.u32SampleRate
	ldrh	r3, [r2, #10]	@ <variable>.cbSize, <variable>.cbSize
	cmp	r3, #4	@ <variable>.cbSize,
	strne	r1, [fp, #-28]	@ u32ParamIndex, sPcmDecoderParams.bBigEndian
	beq	.L59	@,
.L55:
	mov	r1, #1000	@,
	mov	lr, #1	@ tmp155,
	str	lr, [fp, #-24]	@ tmp155, sPcmDecoderParams.bInterlace
	bl	__aeabi_uidiv	@
	mov	r2, #20	@ tmp161,
	ldr	r3, [fp, #-36]	@ sPcmDecoderParams.u32BitWidth, sPcmDecoderParams.u32BitWidth
	sub	r1, fp, #20	@ tmp168,,
	mov	ip, r3, lsr #3	@ tmp165, sPcmDecoderParams.u32BitWidth,
	mul	r2, r2, r0	@ sampls, tmp161,
	bic	r0, r2, #7	@ tmp162, sampls,
	mul	r5, r5, r0	@ tmp164, <variable>.nChannels, tmp162
	mul	r2, ip, r5	@ tmp167, tmp165, tmp164
	str	r2, [r1, #-24]!	@ tmp167, sPcmDecoderParams.u32FrameSize
	ldr	r0, [r4, #0]	@, <variable>.hDecoder
	bl	SetPCMDecoderParam	@
	cmp	r0, #0	@,
	moveq	r2, #0	@ D.4470,
	moveq	r3, #0	@ D.4470,
	beq	.L56	@,
	b	.L52	@
.L59:
	ldrh	r1, [r2, #12]	@ <variable>.cbExtWord, <variable>.cbExtWord
	cmp	r1, #0	@ <variable>.cbExtWord,
	movne	r1, #1	@ tmp153,
	strne	r1, [fp, #-28]	@ tmp153, sPcmDecoderParams.bBigEndian
	b	.L55	@
	.fnend
	.size	Aflt_PCMDecCompSetParameter, .-Aflt_PCMDecCompSetParameter
	.align	2
	.type	Aflt_PCMDecCompStoreSetting, %function
Aflt_PCMDecCompStoreSetting:
	.fnstart
.LFB156:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #36
	sub	sp, sp, #36	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #0	@ hAde,
	cmpne	r1, #0	@, pstSettingStructure,
	mov	r4, r1	@ pstSettingStructure, pstSettingStructure
	bne	.L64	@,
.L61:
	movw	r6, #:lower16:-2147479551	@ D.4529,
	movt	r6, #:upper16:-2147479551	@ D.4529,
	mvn	r7, #0	@ D.4529,
.L62:
	mov	r1, r7	@, D.4529
	mov	r0, r6	@, D.4529
	sub	sp, fp, #24
	ldmfd	sp, {r4, r6, r7, fp, sp, pc}
.L64:
	cmp	r2, #0	@ pu32SettingStructureSize,
	beq	.L61	@,
	ldr	r0, [r0, #0]	@, <variable>.hDecoder
	sub	r1, fp, #52	@,,
	str	r2, [fp, #-56]	@,
	bl	StorePCMDecoderParam	@
	ldr	r0, [fp, #-36]	@ sPcmDecoderParams.bBigEndian, sPcmDecoderParams.bBigEndian
	mov	r6, #0	@ D.4529,
	mov	r7, #0	@ D.4529,
	str	r0, [r4, #16]	@ sPcmDecoderParams.bBigEndian, <variable>.bBigEndian
	ldr	r3, [fp, #-32]	@ sPcmDecoderParams.bInterlace, sPcmDecoderParams.bInterlace
	str	r3, [r4, #20]	@ sPcmDecoderParams.bInterlace, <variable>.bInterlace
	mov	r3, #24	@ tmp154,
	ldr	r2, [fp, #-40]	@ sPcmDecoderParams.u32SampleRate, sPcmDecoderParams.u32SampleRate
	str	r2, [r4, #12]	@ sPcmDecoderParams.u32SampleRate, <variable>.u32SampleRate
	ldr	ip, [fp, #-44]	@ sPcmDecoderParams.u32BitWidth, sPcmDecoderParams.u32BitWidth
	str	ip, [r4, #8]	@ sPcmDecoderParams.u32BitWidth, <variable>.u32BitWidth
	ldr	r1, [fp, #-48]	@ sPcmDecoderParams.u32ChnNumber, sPcmDecoderParams.u32ChnNumber
	str	r1, [r4, #4]	@ sPcmDecoderParams.u32ChnNumber, <variable>.u32ChnNumber
	ldr	r0, [fp, #-52]	@ sPcmDecoderParams.u32FrameSize, sPcmDecoderParams.u32FrameSize
	str	r0, [r4, #0]	@ sPcmDecoderParams.u32FrameSize, <variable>.u32FrameSize
	ldr	r2, [fp, #-56]	@,
	str	r3, [r2, #0]	@ tmp154,* pu32SettingStructureSize
	b	.L62	@
	.fnend
	.size	Aflt_PCMDecCompStoreSetting, .-Aflt_PCMDecCompStoreSetting
	.align	2
	.type	Aflt_PCMDecCompDeInit, %function
Aflt_PCMDecCompDeInit:
	.fnstart
.LFB150:
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
	subs	r4, r0, #0	@ hAde, hAde
	movweq	r2, #:lower16:-2147479551	@ D.4435,
	mvneq	r3, #0	@ D.4435,
	movteq	r2, #:upper16:-2147479551	@ D.4435,
	bne	.L70	@,
	mov	r1, r3	@, D.4435
	mov	r0, r2	@, D.4435
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L70:
	ldr	r0, [r4, #0]	@, <variable>.hDecoder
	bl	PCMCloseDecoder	@
	ldr	r1, [r4, #28]	@ D.4437, <variable>.pstFrmInfo
	cmp	r1, #0	@ D.4437,
	beq	.L68	@,
	mov	r0, #25	@,
	bl	HI_ADSP_FREE	@
	mov	r3, #0	@ tmp139,
	str	r3, [r4, #28]	@ tmp139, <variable>.pstFrmInfo
.L68:
	mov	r1, r4	@, hAde
	mov	r0, #25	@,
	bl	HI_ADSP_FREE	@
	mov	r2, #0	@ D.4435,
	mov	r3, #0	@ D.4435,
	mov	r0, r2	@, D.4435
	mov	r1, r3	@, D.4435
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	Aflt_PCMDecCompDeInit, .-Aflt_PCMDecCompDeInit
	.align	2
	.type	Aflt_PCMDecCompInit, %function
Aflt_PCMDecCompInit:
	.fnstart
.LFB149:
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
	subs	r4, r0, #0	@ phAde, phAde
	movweq	r2, #:lower16:-2147479551	@ D.4413,
	mvneq	r3, #0	@ D.4413,
	movteq	r2, #:upper16:-2147479551	@ D.4413,
	bne	.L80	@,
.L73:
	mov	r1, r3	@, D.4413
	mov	r0, r2	@, D.4413
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L80:
	mov	r0, #25	@,
	mov	r1, #32	@,
	bl	HI_ADSP_MALLOC	@
	subs	r5, r0, #0	@ D.4414,
	beq	.L79	@,
	bl	PCMOpenDecoder	@
	subs	r3, r0, #0	@ nRet,
	bne	.L75	@,
	ldr	r2, [r5, #0]	@ <variable>.hDecoder, <variable>.hDecoder
	cmp	r2, #0	@ <variable>.hDecoder,
	beq	.L75	@,
	str	r3, [r5, #16]	@ nRet, <variable>.u32OutBufSize
	mov	r0, #25	@,
	str	r3, [r5, #20]	@ nRet, <variable>.u32ByteConsume
	mov	r1, #20	@,
	str	r3, [r5, #8]	@ nRet, <variable>.u32InBufSize
	str	r3, [r5, #24]	@ nRet, <variable>.u32InPutByteLeft
	bl	HI_ADSP_MALLOC	@
	cmp	r0, #0	@ D.4423,
	str	r0, [r5, #28]	@ D.4423, <variable>.pstFrmInfo
	strne	r5, [r4, #0]	@ D.4414,* phAde
	movne	r2, #0	@ D.4413,
	movne	r3, #0	@ D.4413,
	bne	.L73	@,
	ldr	r0, [r5, #0]	@, <variable>.hDecoder
	bl	PCMCloseDecoder	@
	mov	r1, r5	@, D.4414
	mov	r0, #25	@,
	bl	HI_ADSP_FREE	@
	movw	r2, #:lower16:-2147479552	@ D.4413,
	mvn	r3, #0	@ D.4413,
	movt	r2, #:upper16:-2147479552	@ D.4413,
	b	.L73	@
.L75:
	mov	r1, r5	@, D.4414
	mov	r0, #25	@,
	bl	HI_ADSP_FREE	@
.L79:
	movw	r2, #:lower16:-2147479552	@ D.4413,
	mvn	r3, #0	@ D.4413,
	movt	r2, #:upper16:-2147479552	@ D.4413,
	b	.L73	@
	.fnend
	.size	Aflt_PCMDecCompInit, .-Aflt_PCMDecCompInit
	.global	g_stComponentPcmDecoder
	.data
	.align	2
	.type	g_stComponentPcmDecoder, %object
	.size	g_stComponentPcmDecoder, 60
g_stComponentPcmDecoder:
@ Init:
	.word	Aflt_PCMDecCompInit
@ DeInit:
	.word	Aflt_PCMDecCompDeInit
@ SetConfig:
	.word	Aflt_PCMDecCompSetConfig
@ GetConfig:
	.word	Aflt_PCMDecCompGetConfig
@ GetParameter:
	.word	Aflt_PCMDecCompGetParameter
@ SetParameter:
	.word	Aflt_PCMDecCompSetParameter
@ StoreSetting:
	.word	Aflt_PCMDecCompStoreSetting
@ RestoreSetting:
	.word	Aflt_PCMDecCompRestoreSetting
@ SetInputBuffer:
	.word	Aflt_PCMDecCompSetInputBuffer
@ SetOutputBuffer:
	.word	Aflt_PCMDecCompSetOutputBuffer
@ GetInputBytesleft:
	.word	Aflt_PCMDecCompGetInputBytesleft
@ GetMinInputBufSize:
	.word	Aflt_PCMDecCompGetMinInputBufSize
@ ExcuteFrame:
	.word	Aflt_PCMDecCompEexcuteFrame
@ GetCurnFramePrivInfo:
	.word	Aflt_PCMDecCompGetCurnFramePrivInfo
@ SetEosFlag:
	.word	Aflt_PCMDecCompSetEosFlag
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
