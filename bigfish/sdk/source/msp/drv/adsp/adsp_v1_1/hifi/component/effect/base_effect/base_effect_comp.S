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
	.file	"base_effect_comp.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(base_effect_comp)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_adsp) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD
@ drivers/msp/adsp/adsp_v1_1/./hifi/component/effect/base_effect/.base_effect_comp.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/adsp/adsp_v1_1/./hifi/component/effect/base_effect/base_effect_comp.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/adsp/adsp_v1_1/./hifi/component/effect/base_effect/base_effect_comp.o
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
	.type	COMP_BAE_SetInputBuffer, %function
COMP_BAE_SetInputBuffer:
	.fnstart
.LFB865:
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
	cmp	r0, #0	@ hComp,
	cmpne	r1, #0	@, pInBuf,
	strne	r1, [r0, #8]	@ pInBuf, <variable>.pInBuf
	movweq	r4, #:lower16:-2147479551	@ D.14780,
	movteq	r4, #:upper16:-2147479551	@ D.14780,
	mvneq	r5, #0	@ D.14780,
	movne	r4, #0	@ D.14780,
	movne	r5, #0	@ D.14780,
	strne	r2, [r0, #12]	@ u32InBufSize, <variable>.u32InBufSize
	mov	r1, r5	@, D.14780
	mov	r0, r4	@, D.14780
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	COMP_BAE_SetInputBuffer, .-COMP_BAE_SetInputBuffer
	.align	2
	.type	COMP_BAE_SetOutputBuffer, %function
COMP_BAE_SetOutputBuffer:
	.fnstart
.LFB866:
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
	cmp	r0, #0	@ hComp,
	cmpne	r1, #0	@, pOutBuf,
	strne	r1, [r0, #16]	@ pOutBuf, <variable>.pOutBuf
	movweq	r4, #:lower16:-2147479551	@ D.14792,
	movteq	r4, #:upper16:-2147479551	@ D.14792,
	mvneq	r5, #0	@ D.14792,
	movne	r4, #0	@ D.14792,
	movne	r5, #0	@ D.14792,
	strne	r2, [r0, #20]	@ u32OutBufSize, <variable>.u32OutBufSize
	mov	r1, r5	@, D.14792
	mov	r0, r4	@, D.14792
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	COMP_BAE_SetOutputBuffer, .-COMP_BAE_SetOutputBuffer
	.align	2
	.type	COMP_BAE_GetInputBytesleft, %function
COMP_BAE_GetInputBytesleft:
	.fnstart
.LFB867:
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
	cmp	r0, #0	@ hComp,
	cmpne	r1, #0	@, pu32Bytesleft,
	movweq	r2, #:lower16:-2147479551	@ D.14802,
	movteq	r2, #:upper16:-2147479551	@ D.14802,
	mvneq	r3, #0	@ D.14802,
	movne	r2, #0	@ D.14802,
	movne	r3, #0	@ D.14802,
	movne	r0, #0	@, tmp143
	moveq	r0, #1	@, tmp143
	strne	r0, [r1, #0]	@ tmp143,* pu32Bytesleft
	mov	r1, r3	@, D.14802
	mov	r0, r2	@, D.14802
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	COMP_BAE_GetInputBytesleft, .-COMP_BAE_GetInputBytesleft
	.align	2
	.type	COMP_BAE_SetEosFlag, %function
COMP_BAE_SetEosFlag:
	.fnstart
.LFB873:
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
	cmp	r0, #0	@ hComp
	strne	r1, [r0, #4]	@ bEosFlag, <variable>.bEosFlag
	movweq	r2, #:lower16:-2147479551	@ D.14958,
	movteq	r2, #:upper16:-2147479551	@ D.14958,
	mvneq	r3, #0	@ D.14958,
	movne	r2, #0	@ D.14958,
	movne	r3, #0	@ D.14958,
	mov	r0, r2	@, D.14958
	mov	r1, r3	@, D.14958
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	COMP_BAE_SetEosFlag, .-COMP_BAE_SetEosFlag
	.align	2
	.type	COMP_BAE_GetCurnFramePrivInfo, %function
COMP_BAE_GetCurnFramePrivInfo:
	.fnstart
.LFB872:
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
	cmp	r0, #0	@ hComp,
	cmpne	r1, #0	@, pstFramePrivInfo,
	mov	r4, r1	@ pstFramePrivInfo, pstFramePrivInfo
	movweq	r2, #:lower16:-2147479551	@ D.14948,
	mvneq	r3, #0	@ D.14948,
	movteq	r2, #:upper16:-2147479551	@ D.14948,
	beq	.L19	@,
	mov	r5, #20	@ tmp148,
	add	r1, r0, #28	@, hComp,
	mov	r2, r5	@, tmp148
	ldr	r0, [r4, #0]	@, <variable>.pOutPrivInfo
	bl	memcpy	@
	mov	r2, #0	@ D.14948,
	mov	r3, #0	@ D.14948,
	str	r5, [r4, #4]	@ tmp148, <variable>.u32OutPrivBytesProduced
.L19:
	mov	r1, r3	@, D.14948
	mov	r0, r2	@, D.14948
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	COMP_BAE_GetCurnFramePrivInfo, .-COMP_BAE_GetCurnFramePrivInfo
	.align	2
	.type	COMP_BAE_RestoreSetting, %function
COMP_BAE_RestoreSetting:
	.fnstart
.LFB864:
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
	cmp	r0, #0	@ hComp,
	cmpne	r1, #0	@, pSettingStructure,
	movweq	r2, #:lower16:-2147479551	@ D.14767,
	mvneq	r3, #0	@ D.14767,
	movteq	r2, #:upper16:-2147479551	@ D.14767,
	beq	.L24	@,
	mov	r2, #40	@,
	add	r0, r0, #24	@, hComp,
	bl	memcpy	@
	mov	r2, #0	@ D.14767,
	mov	r3, #0	@ D.14767,
.L24:
	mov	r1, r3	@, D.14767
	mov	r0, r2	@, D.14767
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	COMP_BAE_RestoreSetting, .-COMP_BAE_RestoreSetting
	.align	2
	.type	COMP_BAE_StoreSetting, %function
COMP_BAE_StoreSetting:
	.fnstart
.LFB863:
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
	cmp	r0, #0	@ hComp,
	cmpne	r1, #0	@, pSettingStructure,
	mov	r3, r0	@ hComp, hComp
	mov	r4, r2	@ pu32SettingStructureSize, pu32SettingStructureSize
	bne	.L30	@,
.L27:
	movw	r2, #:lower16:-2147479551	@ D.14755,
	movt	r2, #:upper16:-2147479551	@ D.14755,
	mvn	r3, #0	@ D.14755,
.L28:
	mov	r1, r3	@, D.14755
	mov	r0, r2	@, D.14755
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L30:
	cmp	r2, #0	@ pu32SettingStructureSize,
	beq	.L27	@,
	mov	r5, #40	@ tmp148,
	mov	r0, r1	@, pSettingStructure
	mov	r2, r5	@, tmp148
	add	r1, r3, #24	@, hComp,
	bl	memcpy	@
	str	r5, [r4, #0]	@ tmp148,* pu32SettingStructureSize
	mov	r2, #0	@ D.14755,
	mov	r3, #0	@ D.14755,
	b	.L28	@
	.fnend
	.size	COMP_BAE_StoreSetting, .-COMP_BAE_StoreSetting
	.align	2
	.type	COMP_BAE_SetParameter, %function
COMP_BAE_SetParameter:
	.fnstart
.LFB861:
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
	cmp	r0, #0	@ hComp,
	cmpne	r2, #0	@, pParameterStructure,
	bne	.L36	@,
.L32:
	movw	r2, #:lower16:-2147479551	@ D.14723,
	movt	r2, #:upper16:-2147479551	@ D.14723,
	mvn	r3, #0	@ D.14723,
.L34:
	mov	r1, r3	@, D.14723
	mov	r0, r2	@, D.14723
	ldmfd	sp, {fp, sp, pc}	@
.L36:
	cmp	r1, #0	@ u32ParamIndex,
	bne	.L32	@,
	mov	r1, r2	@, pParameterStructure
	add	r0, r0, #24	@, hComp,
	mov	r2, #24	@,
	bl	memcpy	@
	mov	r2, #0	@ D.14723,
	mov	r3, #0	@ D.14723,
	b	.L34	@
	.fnend
	.size	COMP_BAE_SetParameter, .-COMP_BAE_SetParameter
	.align	2
	.type	COMP_BAE_GetParameter, %function
COMP_BAE_GetParameter:
	.fnstart
.LFB862:
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
	cmp	r0, #0	@ hComp,
	cmpne	r2, #0	@, pParameterStructure,
	mov	ip, r0	@ hComp, hComp
	bne	.L42	@,
.L38:
	movw	r2, #:lower16:-2147479551	@ D.14741,
	movt	r2, #:upper16:-2147479551	@ D.14741,
	mvn	r3, #0	@ D.14741,
.L40:
	mov	r1, r3	@, D.14741
	mov	r0, r2	@, D.14741
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L42:
	cmp	r3, #0	@ pu32ParameterStructureSize,
	beq	.L38	@,
	cmp	r1, #0	@ u32ParamIndex,
	bne	.L38	@,
	mov	r4, #24	@ tmp149,
	mov	r0, r2	@, pParameterStructure
	add	r1, ip, r4	@, hComp,
	mov	r2, r4	@, tmp149
	str	r3, [fp, #-24]	@,
	bl	memcpy	@
	ldr	r3, [fp, #-24]	@,
	mov	r2, #0	@ D.14741,
	str	r4, [r3, #0]	@ tmp149,* pu32ParameterStructureSize
	mov	r3, #0	@ D.14741,
	b	.L40	@
	.fnend
	.size	COMP_BAE_GetParameter, .-COMP_BAE_GetParameter
	.align	2
	.type	COMP_BAE_GetConfig, %function
COMP_BAE_GetConfig:
	.fnstart
.LFB860:
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
	cmp	r0, #0	@ hComp,
	cmpne	r2, #0	@, pConfigStructure,
	mov	ip, r0	@ hComp, hComp
	bne	.L50	@,
.L44:
	movw	r2, #:lower16:-2147479551	@ D.14706,
	movt	r2, #:upper16:-2147479551	@ D.14706,
	mvn	r3, #0	@ D.14706,
.L47:
	mov	r1, r3	@, D.14706
	mov	r0, r2	@, D.14706
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L50:
	cmp	r3, #0	@ pu32ConfigStructureSize,
	beq	.L44	@,
	cmp	r1, #4	@ u32ConfigIndex,
	beq	.L45	@,
	cmp	r1, #5	@ u32ConfigIndex,
	bne	.L44	@,
	add	r1, ip, #56	@, hComp,
	mov	r4, #8	@ tmp156,
	mov	r0, r2	@, pConfigStructure
.L49:
	mov	r2, r4	@, tmp156
	str	r3, [fp, #-24]	@,
	bl	memcpy	@
	ldr	r3, [fp, #-24]	@,
	mov	r2, #0	@ D.14706,
	str	r4, [r3, #0]	@ tmp156,* pu32ConfigStructureSize
	mov	r3, #0	@ D.14706,
	b	.L47	@
.L45:
	mov	r4, #8	@ tmp150,
	mov	r0, r2	@, pConfigStructure
	add	r1, ip, #48	@, hComp,
	b	.L49	@
	.fnend
	.size	COMP_BAE_GetConfig, .-COMP_BAE_GetConfig
	.align	2
	.type	COMP_BAE_SetConfig, %function
COMP_BAE_SetConfig:
	.fnstart
.LFB859:
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
	cmp	r0, #0	@ hComp,
	cmpne	r2, #0	@, pConfigStructure,
	bne	.L58	@,
.L52:
	movw	r2, #:lower16:-2147479551	@ D.14686,
	movt	r2, #:upper16:-2147479551	@ D.14686,
	mvn	r3, #0	@ D.14686,
.L55:
	mov	r1, r3	@, D.14686
	mov	r0, r2	@, D.14686
	ldmfd	sp, {fp, sp, pc}	@
.L58:
	cmp	r1, #4	@ u32ConfigIndex,
	beq	.L53	@,
	cmp	r1, #5	@ u32ConfigIndex,
	bne	.L52	@,
	add	r0, r0, #56	@, hComp,
.L57:
	mov	r1, r2	@, pConfigStructure
	mov	r2, #8	@,
	bl	memcpy	@
	mov	r2, #0	@ D.14686,
	mov	r3, #0	@ D.14686,
	b	.L55	@
.L53:
	add	r0, r0, #48	@, hComp,
	b	.L57	@
	.fnend
	.size	COMP_BAE_SetConfig, .-COMP_BAE_SetConfig
	.align	2
	.type	COMP_BAE_GetMinInputBufSize, %function
COMP_BAE_GetMinInputBufSize:
	.fnstart
.LFB868:
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
	cmp	r0, #0	@ hComp,
	cmpne	r1, #0	@, pu32InBufsize,
	mov	r4, r1	@ pu32InBufsize, pu32InBufsize
	movweq	r2, #:lower16:-2147479551	@ D.14815,
	mvneq	r3, #0	@ D.14815,
	movteq	r2, #:upper16:-2147479551	@ D.14815,
	beq	.L61	@,
	ldr	r1, [r0, #28]	@, <variable>.stSetting.stOpenParam.stPrivInfo.u32BitDepth
	ldr	r0, [r0, #32]	@, <variable>.stSetting.stOpenParam.stPrivInfo.u32Channels
	bl	UTIL_CalcFrameSize	@
	mov	r2, #0	@ D.14815,
	mov	r3, #0	@ D.14815,
	mov	r0, r0, asl #11	@ tmp148,,
	str	r0, [r4, #0]	@ tmp148,* pu32InBufsize
.L61:
	mov	r1, r3	@, D.14815
	mov	r0, r2	@, D.14815
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	COMP_BAE_GetMinInputBufSize, .-COMP_BAE_GetMinInputBufSize
	.global	__aeabi_uidivmod
	.global	__aeabi_uidiv
	.align	2
	.type	COMP_BAE_EexcuteFrame, %function
COMP_BAE_EexcuteFrame:
	.fnstart
.LFB871:
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
	cmp	r0, #0	@ hComp,
	cmpne	r1, #0	@, pstExcuteFrame,
	mov	r5, r1	@ pstExcuteFrame, pstExcuteFrame
	mov	r4, r0	@ hComp, hComp
	bne	.L85	@,
.L64:
	movw	r2, #:lower16:-2147479551	@ D.14898,
	movt	r2, #:upper16:-2147479551	@ D.14898,
	mvn	r3, #0	@ D.14898,
.L66:
	mov	r1, r3	@, D.14898
	mov	r0, r2	@, D.14898
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L85:
	ldr	r0, [r0, #32]	@, <variable>.stSetting.stOpenParam.stPrivInfo.u32Channels
	ldr	r1, [r4, #28]	@, <variable>.stSetting.stOpenParam.stPrivInfo.u32BitDepth
	bl	UTIL_CalcFrameSize	@
	subs	r7, r0, #0	@ u32SampleSize,
	beq	.L64	@,
	ldr	r6, [r4, #12]	@ u32BytesPriv, <variable>.u32InBufSize
	ldr	r9, [r4, #8]	@ pReadPtr.235, <variable>.pInBuf
	cmp	r6, #0	@ u32BytesPriv,
	ldr	sl, [r4, #16]	@ pWritePtr.236, <variable>.pOutBuf
	beq	.L84	@,
	ldr	r3, [r4, #24]	@ <variable>.stSetting.stOpenParam.bMaster, <variable>.stSetting.stOpenParam.bMaster
	cmp	r3, #0	@ <variable>.stSetting.stOpenParam.bMaster,
	beq	.L67	@,
	mov	r8, r7, asl #8	@ u32FrameMinSize, u32SampleSize,
	cmp	r8, r6	@ u32FrameMinSize, u32BytesPriv
	movls	r6, r8	@ u32BytesPriv, u32BytesLeft
	bls	.L69	@,
	ldr	r1, [r4, #4]	@ <variable>.bEosFlag, <variable>.bEosFlag
	cmp	r1, #0	@ <variable>.bEosFlag,
	beq	.L86	@,
.L67:
	mov	r8, r6	@ u32BytesLeft, u32BytesPriv
.L69:
	mov	r0, r6	@, u32BytesPriv
	mov	r1, r7	@, u32SampleSize
	bl	__aeabi_uidivmod	@
	cmp	r1, #0	@,
	beq	.L70	@,
	mov	r0, r6	@, u32BytesPriv
	mov	r1, r7	@, u32SampleSize
	bl	__aeabi_uidiv	@
	mul	r6, r7, r0	@ u32BytesPriv, u32SampleSize,
	cmp	r6, #0	@ u32BytesPriv,
	movne	r8, r6	@ u32BytesLeft, u32BytesPriv
	bne	.L70	@,
.L84:
	movw	r2, #:lower16:-2147479549	@ D.14898,
	str	r6, [r5, #4]	@ u32BytesPriv, <variable>.u32OutDataBytesProduced
	movt	r2, #:upper16:-2147479549	@ D.14898,
	mvn	r3, #0	@ D.14898,
	str	r6, [r5, #0]	@ u32BytesPriv, <variable>.u32InBytesConsumed
	b	.L66	@
.L86:
	movw	r2, #:lower16:-2147479549	@ D.14898,
	str	r1, [r5, #4]	@ <variable>.bEosFlag, <variable>.u32OutDataBytesProduced
	movt	r2, #:upper16:-2147479549	@ D.14898,
	mvn	r3, #0	@ D.14898,
	str	r1, [r5, #0]	@ <variable>.bEosFlag, <variable>.u32InBytesConsumed
	b	.L66	@
.L70:
	mov	r3, #0	@ tmp173,
	str	r3, [fp, #-52]	@ tmp173, s32RTargetGain
	str	r3, [fp, #-48]	@ tmp173, s32LTargetGain
	ldr	r0, [r4, #48]	@ <variable>.stSetting.stMasterVol.bEnable, <variable>.stSetting.stMasterVol.bEnable
	cmp	r0, r3	@ <variable>.stSetting.stMasterVol.bEnable,
	subeq	r3, fp, #48	@ tmp208,,
	moveq	r1, r0	@,
	moveq	r2, r3	@, tmp208
	beq	.L83	@,
	ldr	r0, [r4, #52]	@ D.15326, <variable>.stSetting.stMasterVol.s32MasterVol
	cmp	r0, r3	@ D.15326,
	andgt	r1, r0, #7	@ s32OrgFracGain, D.15326,
	ble	.L87	@,
.L74:
	add	r2, r0, #7	@ tmp181, D.15326,
	cmp	r0, #0	@ D.15326,
	sub	r3, fp, #48	@ tmp208,,
	movlt	r0, r2	@ D.15326, tmp181
	mov	r0, r0, asr #3	@, D.15326,
	mov	r2, r3	@, tmp208
.L83:
	str	r3, [fp, #-56]	@,
	bl	UTILS_GaindB2Linear	@
	ldr	ip, [fp, #-48]	@ s32LTargetGain, s32LTargetGain
	ldr	r3, [fp, #-56]	@,
	str	ip, [fp, #-52]	@ s32LTargetGain, s32RTargetGain
	ldr	r0, [r4, #56]	@ <variable>.stSetting.stBalance.bEnable, <variable>.stSetting.stBalance.bEnable
	cmp	r0, #0	@ <variable>.stSetting.stBalance.bEnable,
	bne	.L88	@,
.L77:
	ldr	lr, [r4, #48]	@ <variable>.stSetting.stMasterVol.bEnable, <variable>.stSetting.stMasterVol.bEnable
	cmp	lr, #0	@ <variable>.stSetting.stMasterVol.bEnable,
	bne	.L78	@,
	ldr	r3, [r4, #56]	@ <variable>.stSetting.stBalance.bEnable, <variable>.stSetting.stBalance.bEnable
	cmp	r3, #0	@ <variable>.stSetting.stBalance.bEnable,
	beq	.L79	@,
.L78:
	ldr	ip, [fp, #-52]	@ s32RTargetGain, s32RTargetGain
	mov	r0, r9	@, pReadPtr.235
	mov	r1, sl	@, pWritePtr.236
	mov	r2, r8, lsr #2	@, u32BytesLeft,
	ldr	r3, [fp, #-48]	@, s32LTargetGain
	str	ip, [sp, #0]	@ s32RTargetGain,
	bl	UTILS_GainProcessFrame_16BIT_Pro	@
.L80:
	str	r6, [r5, #4]	@ u32BytesPriv, <variable>.u32OutDataBytesProduced
	str	r6, [r5, #0]	@ u32BytesPriv, <variable>.u32InBytesConsumed
	ldr	r3, [r4, #24]	@ <variable>.stSetting.stOpenParam.bMaster, <variable>.stSetting.stOpenParam.bMaster
	cmp	r3, #0	@ <variable>.stSetting.stOpenParam.bMaster,
	moveq	r2, #0	@ D.14898,
	moveq	r3, #0	@ D.14898,
	beq	.L66	@,
	str	r6, [r4, #44]	@ u32BytesPriv, <variable>.stSetting.stOpenParam.stPrivInfo.u32BytesPerFrame
	mov	r0, r6	@, u32BytesPriv
	mov	r1, r7	@, u32SampleSize
	bl	__aeabi_uidiv	@
	mov	r2, #0	@ D.14898,
	mov	r3, #0	@ D.14898,
	str	r0, [r4, #40]	@, <variable>.stSetting.stOpenParam.stPrivInfo.u32SamplesPerFrame
	b	.L66	@
.L79:
	mov	r0, sl	@, pWritePtr.236
	mov	r1, r9	@, pReadPtr.235
	mov	r2, r8	@, u32BytesLeft
	bl	memcpy	@
	b	.L80	@
.L88:
	mov	r0, r3	@, tmp208
	sub	r1, fp, #52	@,,
	ldr	r2, [r4, #60]	@, <variable>.stSetting.stBalance.u32Balance
	bl	UTILS_GainBalance	@
	b	.L77	@
.L87:
	ands	r1, r0, #-2147483641	@ tmp177, D.15326,
	submi	r1, r1, #1	@ tmp209, tmp177,
	mvnmi	r1, r1, asl #29	@ tmp210, tmp209,
	mvnmi	r1, r1, lsr #29	@ tmp210, tmp210,
	addmi	r1, r1, #1	@ tmp177, tmp210,
	rsb	r1, r1, #0	@ s32OrgFracGain, tmp177
	b	.L74	@
	.fnend
	.size	COMP_BAE_EexcuteFrame, .-COMP_BAE_EexcuteFrame
	.align	2
	.type	COMP_BAE_DeInit, %function
COMP_BAE_DeInit:
	.fnstart
.LFB858:
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
	subs	r1, r0, #0	@ hComp, hComp
	movweq	r2, #:lower16:-2147479551	@ D.14670,
	mvneq	r3, #0	@ D.14670,
	movteq	r2, #:upper16:-2147479551	@ D.14670,
	beq	.L91	@,
	mov	r0, #25	@,
	bl	HI_ADSP_FREE	@
	mov	r2, #0	@ D.14670,
	mov	r3, #0	@ D.14670,
.L91:
	mov	r1, r3	@, D.14670
	mov	r0, r2	@, D.14670
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	COMP_BAE_DeInit, .-COMP_BAE_DeInit
	.align	2
	.type	COMP_BAE_Init, %function
COMP_BAE_Init:
	.fnstart
.LFB857:
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
	subs	r4, r0, #0	@ phComp, phComp
	movweq	r2, #:lower16:-2147479551	@ D.14654,
	mvneq	r3, #0	@ D.14654,
	movteq	r2, #:upper16:-2147479551	@ D.14654,
	bne	.L98	@,
.L95:
	mov	r1, r3	@, D.14654
	mov	r0, r2	@, D.14654
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L98:
	mov	r0, #25	@,
	mov	r1, #64	@,
	bl	HI_ADSP_MALLOC	@
	subs	r5, r0, #0	@ D.14655,
	movweq	r2, #:lower16:-2147479552	@ D.14654,
	mvneq	r3, #0	@ D.14654,
	movteq	r2, #:upper16:-2147479552	@ D.14654,
	beq	.L95	@,
	mov	r1, #64	@,
	bl	__memzero	@
	mov	r2, #0	@ D.14654,
	mov	r3, #0	@ D.14654,
	str	r5, [r4, #0]	@ D.14655,* phComp
	b	.L95	@
	.fnend
	.size	COMP_BAE_Init, .-COMP_BAE_Init
	.global	g_stComponentBaseAudioEffect
	.data
	.align	2
	.type	g_stComponentBaseAudioEffect, %object
	.size	g_stComponentBaseAudioEffect, 60
g_stComponentBaseAudioEffect:
@ Init:
	.word	COMP_BAE_Init
@ DeInit:
	.word	COMP_BAE_DeInit
@ SetConfig:
	.word	COMP_BAE_SetConfig
@ GetConfig:
	.word	COMP_BAE_GetConfig
@ GetParameter:
	.word	COMP_BAE_GetParameter
@ SetParameter:
	.word	COMP_BAE_SetParameter
@ StoreSetting:
	.word	COMP_BAE_StoreSetting
@ RestoreSetting:
	.word	COMP_BAE_RestoreSetting
@ SetInputBuffer:
	.word	COMP_BAE_SetInputBuffer
@ SetOutputBuffer:
	.word	COMP_BAE_SetOutputBuffer
@ GetInputBytesleft:
	.word	COMP_BAE_GetInputBytesleft
@ GetMinInputBufSize:
	.word	COMP_BAE_GetMinInputBufSize
@ ExcuteFrame:
	.word	COMP_BAE_EexcuteFrame
@ GetCurnFramePrivInfo:
	.word	COMP_BAE_GetCurnFramePrivInfo
@ SetEosFlag:
	.word	COMP_BAE_SetEosFlag
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
