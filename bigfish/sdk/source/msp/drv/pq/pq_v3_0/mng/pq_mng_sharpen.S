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
	.file	"pq_mng_sharpen.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_mng_sharpen)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/mng/.pq_mng_sharpen.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/mng/pq_mng_sharpen.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/mng/pq_mng_sharpen.o -O2 -Wall -Wundef
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
	.global	PQ_MNG_SharpenParaInitDefault
	.type	PQ_MNG_SharpenParaInitDefault, %function
PQ_MNG_SharpenParaInitDefault:
	.fnstart
.LFB836:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp133,
	movt	r3, #:upper16:.LANCHOR0	@ tmp133,
	mov	r2, #0	@ tmp134,
	mov	r0, #128	@ tmp162,
	mov	r1, #4	@ tmp182,
	mov	r6, #127	@ tmp140,
	mvn	r5, #0	@ tmp148,
	mov	r4, #3	@ tmp154,
	mvn	ip, #20	@ tmp176,
	mov	r7, #180	@ tmp138,
	str	r2, [r3, #224]	@ tmp134, sg_bSharpen_EnFlag
	str	r7, [r3, #12]	@ tmp138, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lgain_ratio
	mvn	r7, #18	@ tmp142,
	str	r0, [r3, #68]	@ tmp162, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lgain_coef2
	str	r7, [r3, #20]	@ tmp142, g_stSharpPara.stSharpHdData.stPqSharpLuma.s32Lhpass_coef0
	mvn	r7, #7	@ tmp144,
	str	r1, [r3, #108]	@ tmp182, g_stSharpPara.stSharpHdData.stPqSharpChroma.u32Cover_swing
	str	r7, [r3, #24]	@ tmp144, g_stSharpPara.stSharpHdData.stPqSharpLuma.s32Lhpass_coef1
	mvn	r7, #1	@ tmp146,
	str	r6, [r3, #84]	@ tmp140, g_stSharpPara.stSharpHdData.stPqSharpChroma.u32Cmixing_ratio
	str	r7, [r3, #28]	@ tmp146, g_stSharpPara.stSharpHdData.stPqSharpLuma.s32Lhpass_coef2
	mov	r7, #2	@ tmp152,
	str	r5, [r3, #36]	@ tmp148, g_stSharpPara.stSharpHdData.stPqSharpLuma.s32Lhpass_coef4
	str	r7, [r3, #40]	@ tmp152, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lcoring_thd
	mov	r7, #50	@ tmp158,
	str	r4, [r3, #48]	@ tmp154, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lover_swing
	str	r7, [r3, #52]	@ tmp158, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lhfreq_thd0
	mov	r7, #51	@ tmp160,
	str	ip, [r3, #92]	@ tmp176, g_stSharpPara.stSharpHdData.stPqSharpChroma.s32Chpass_coef1
	str	r7, [r3, #56]	@ tmp160, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lhfreq_thd1
	mov	r7, #256	@ tmp172,
	str	r2, [r3, #0]	@ tmp134, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lti_en
	str	r7, [r3, #80]	@ tmp172, g_stSharpPara.stSharpHdData.stPqSharpChroma.u32Cgain_ratio
	mvn	r7, #10	@ tmp180,
	str	r2, [r3, #4]	@ tmp134, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lti_demo_en
	str	r7, [r3, #96]	@ tmp180, g_stSharpPara.stSharpHdData.stPqSharpChroma.s32Chpass_coef2
	str	r6, [r3, #16]	@ tmp140, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lmixing_ratio
	str	r5, [r3, #32]	@ tmp148, g_stSharpPara.stSharpHdData.stPqSharpLuma.s32Lhpass_coef3
	str	r4, [r3, #44]	@ tmp154, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lunder_swing
	str	r0, [r3, #60]	@ tmp162, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lgain_coef0
	str	r0, [r3, #64]	@ tmp162, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lgain_coef1
	str	r2, [r3, #72]	@ tmp134, g_stSharpPara.stSharpHdData.stPqSharpChroma.u32Cti_en
	str	r2, [r3, #76]	@ tmp134, g_stSharpPara.stSharpHdData.stPqSharpChroma.u32Cti_demo_en
	str	ip, [r3, #88]	@ tmp176, g_stSharpPara.stSharpHdData.stPqSharpChroma.s32Chpass_coef0
	str	r1, [r3, #100]	@ tmp182, g_stSharpPara.stSharpHdData.stPqSharpChroma.u32Ccoring_thd
	str	r1, [r3, #104]	@ tmp182, g_stSharpPara.stSharpHdData.stPqSharpChroma.u32Cunder_swing
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_SharpenParaInitDefault, .-PQ_MNG_SharpenParaInitDefault
	.align	2
	.global	PQ_MNG_SharpDeinit
	.type	PQ_MNG_SharpDeinit, %function
PQ_MNG_SharpDeinit:
	.fnstart
.LFB838:
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
	.size	PQ_MNG_SharpDeinit, .-PQ_MNG_SharpDeinit
	.align	2
	.global	PQ_MNG_GetSharpenStrReg
	.type	PQ_MNG_GetSharpenStrReg, %function
PQ_MNG_GetSharpenStrReg:
	.fnstart
.LFB839:
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
	movw	r1, #:lower16:.LANCHOR1	@ tmp135,
	movt	r1, #:upper16:.LANCHOR1	@ tmp135,
	ldr	r3, [r1, #0]	@ sg_s32SharpStrength, sg_s32SharpStrength
	str	r3, [r0, #0]	@ sg_s32SharpStrength,* ps32ShpStr
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_GetSharpenStrReg, .-PQ_MNG_GetSharpenStrReg
	.align	2
	.global	PQ_MNG_DeinitSharpen
	.type	PQ_MNG_DeinitSharpen, %function
PQ_MNG_DeinitSharpen:
	.fnstart
.LFB843:
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
	.size	PQ_MNG_DeinitSharpen, .-PQ_MNG_DeinitSharpen
	.align	2
	.global	PQ_MNG_GetSharpenStr
	.type	PQ_MNG_GetSharpenStr, %function
PQ_MNG_GetSharpenStr:
	.fnstart
.LFB846:
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
	movw	r1, #:lower16:.LANCHOR1	@ tmp135,
	movt	r1, #:upper16:.LANCHOR1	@ tmp135,
	ldr	r3, [r1, #0]	@ sg_s32SharpStrength, sg_s32SharpStrength
	str	r3, [r0, #0]	@ sg_s32SharpStrength,* ps32ShpStr
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_GetSharpenStr, .-PQ_MNG_GetSharpenStr
	.align	2
	.global	PQ_MNG_GetSharpEn
	.type	PQ_MNG_GetSharpEn, %function
PQ_MNG_GetSharpEn:
	.fnstart
.LFB841:
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
	subs	r2, r0, #0	@ pbOnOff, pbOnOff
	beq	.L16	@,
	movw	r1, #:lower16:.LANCHOR0	@ tmp138,
	movt	r1, #:upper16:.LANCHOR0	@ tmp138,
	mov	r0, #0	@ D.26382,
	ldr	r3, [r1, #224]	@ sg_bSharpen_EnFlag, sg_bSharpen_EnFlag
	str	r3, [r2, #0]	@ sg_bSharpen_EnFlag,* pbOnOff
.L13:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L16:
	mov	r0, #1	@,
	mov	r1, #41	@,
	movw	r2, #:lower16:.LANCHOR2	@,
	movw	r3, #262	@,
	movt	r2, #:upper16:.LANCHOR2	@,
	movw	ip, #:lower16:.LC0	@ tmp137,
	movt	ip, #:upper16:.LC0	@ tmp137,
	str	ip, [sp, #0]	@ tmp137,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26382,
	b	.L13	@
	.fnend
	.size	PQ_MNG_GetSharpEn, .-PQ_MNG_GetSharpEn
	.align	2
	.global	PQ_MNG_GetSharpenEnable
	.type	PQ_MNG_GetSharpenEnable, %function
PQ_MNG_GetSharpenEnable:
	.fnstart
.LFB848:
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
	bl	PQ_MNG_GetSharpEn	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_GetSharpenEnable, .-PQ_MNG_GetSharpenEnable
	.align	2
	.global	PQ_MNG_SharpDemoEn
	.type	PQ_MNG_SharpDemoEn, %function
PQ_MNG_SharpDemoEn:
	.fnstart
.LFB842:
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
	mov	r4, r0	@ bOnOff, bOnOff
	mov	r0, #0	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L39	@,
	mov	r0, #1	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@ temp.520,
	mov	r5, r0	@ temp.520,
	beq	.L40	@,
.L22:
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L41	@,
.L23:
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L42	@,
.L24:
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L43	@,
.L25:
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L44	@,
.L26:
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L45	@,
.L27:
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L46	@,
.L28:
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L47	@,
.L29:
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L48	@,
.L30:
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L49	@,
.L31:
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L50	@,
.L32:
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L51	@,
.L33:
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L52	@,
.L34:
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L53	@,
.L35:
	mov	r0, #15	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L54	@,
.L36:
	mov	r0, #0	@ D.26403,
.L37:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L54:
	mov	r1, r4	@, bOnOff
	mov	r0, #15	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret,
	mov	r0, #15	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret
	beq	.L36	@,
.L21:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L55	@,
	movw	r3, #290	@,
	movw	ip, #:lower16:.LC1	@ tmp203,
	movt	ip, #:upper16:.LC1	@ tmp203,
	str	ip, [sp, #0]	@ tmp203,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26403,
	b	.L37	@
.L39:
	mov	r1, r4	@, bOnOff
	mov	r0, #0	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.517,
	mov	r0, #0	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.517
	bne	.L21	@,
	mov	r0, #1	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@ temp.520,
	mov	r5, r0	@ temp.520,
	bne	.L22	@,
.L40:
	mov	r1, r4	@, bOnOff
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r6, r0	@ s32Ret.521,
	mov	r0, r5	@, temp.520
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r6, r0, r6	@,, s32Ret.521
	bne	.L21	@,
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L23	@,
.L41:
	mov	r1, r4	@, bOnOff
	mov	r0, #2	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.525,
	mov	r0, #2	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.525
	bne	.L21	@,
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L24	@,
.L42:
	mov	r1, r4	@, bOnOff
	mov	r0, #3	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.529,
	mov	r0, #3	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.529
	bne	.L21	@,
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L25	@,
.L43:
	mov	r1, r4	@, bOnOff
	mov	r0, #4	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.533,
	mov	r0, #4	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.533
	bne	.L21	@,
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L26	@,
.L44:
	mov	r1, r4	@, bOnOff
	mov	r0, #5	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.537,
	mov	r0, #5	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.537
	bne	.L21	@,
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L27	@,
.L45:
	mov	r1, r4	@, bOnOff
	mov	r0, #6	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.541,
	mov	r0, #6	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.541
	bne	.L21	@,
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L28	@,
.L46:
	mov	r1, r4	@, bOnOff
	mov	r0, #7	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.545,
	mov	r0, #7	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.545
	bne	.L21	@,
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L29	@,
.L47:
	mov	r1, r4	@, bOnOff
	mov	r0, #8	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.549,
	mov	r0, #8	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.549
	bne	.L21	@,
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L30	@,
.L48:
	mov	r1, r4	@, bOnOff
	mov	r0, #9	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.553,
	mov	r0, #9	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.553
	bne	.L21	@,
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L31	@,
.L49:
	mov	r1, r4	@, bOnOff
	mov	r0, #10	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.557,
	mov	r0, #10	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.557
	bne	.L21	@,
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L32	@,
.L50:
	mov	r1, r4	@, bOnOff
	mov	r0, #11	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.561,
	mov	r0, #11	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.561
	bne	.L21	@,
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L33	@,
.L51:
	mov	r1, r4	@, bOnOff
	mov	r0, #12	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.565,
	mov	r0, #12	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.565
	bne	.L21	@,
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L34	@,
.L52:
	mov	r1, r4	@, bOnOff
	mov	r0, #13	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.569,
	mov	r0, #13	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.569
	bne	.L21	@,
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L35	@,
.L53:
	mov	r1, r4	@, bOnOff
	mov	r0, #14	@,
	bl	PQ_HAL_EnableLTIDemo	@
	mov	r1, r4	@, bOnOff
	mov	r5, r0	@ s32Ret.573,
	mov	r0, #14	@,
	bl	PQ_HAL_EnableCTIDemo	@
	orrs	r5, r0, r5	@,, s32Ret.573
	beq	.L35	@,
	b	.L21	@
.L56:
	.align	2
.L55:
	.word	.LANCHOR2+20
	.fnend
	.size	PQ_MNG_SharpDemoEn, .-PQ_MNG_SharpDemoEn
	.align	2
	.global	PQ_MNG_EnableSharpenDemo
	.type	PQ_MNG_EnableSharpenDemo, %function
PQ_MNG_EnableSharpenDemo:
	.fnstart
.LFB849:
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
	bl	PQ_MNG_SharpDemoEn	@
	cmp	r0, #0	@ s32Ret
	bne	.L61	@,
.L59:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L61:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L62	@,
	movw	r3, #486	@,
	movw	ip, #:lower16:.LC2	@ tmp140,
	movt	ip, #:upper16:.LC2	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26488,
	b	.L59	@
.L63:
	.align	2
.L62:
	.word	.LANCHOR2+40
	.fnend
	.size	PQ_MNG_EnableSharpenDemo, .-PQ_MNG_EnableSharpenDemo
	.align	2
	.global	PQ_MNG_SharpEn
	.type	PQ_MNG_SharpEn, %function
PQ_MNG_SharpEn:
	.fnstart
.LFB840:
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
	mov	r4, r0	@ u8Enable, u8Enable
	mov	r0, #0	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L84	@,
.L65:
	mov	r0, #1	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@ temp.626,
	mov	r5, r0	@ temp.626,
	beq	.L85	@,
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L86	@,
.L68:
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L87	@,
.L69:
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L88	@,
.L70:
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L89	@,
.L71:
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L90	@,
.L72:
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L91	@,
.L73:
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L92	@,
.L74:
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L93	@,
.L75:
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L94	@,
.L76:
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L95	@,
.L77:
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L96	@,
.L78:
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L97	@,
.L79:
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L98	@,
.L80:
	mov	r0, #15	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L99	@,
.L81:
	movw	r3, #:lower16:.LANCHOR0	@ tmp203,
	movt	r3, #:upper16:.LANCHOR0	@ tmp203,
	mov	r0, #0	@ D.26374,
	str	r4, [r3, #224]	@ u8Enable, sg_bSharpen_EnFlag
.L82:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L84:
	mov	r1, r4	@, u8Enable
	mov	r0, #0	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.623,
	mov	r0, #0	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.623
	beq	.L65	@,
.L66:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L100	@,
	mov	r3, #240	@,
	movw	ip, #:lower16:.LC3	@ tmp202,
	movt	ip, #:upper16:.LC3	@ tmp202,
	str	ip, [sp, #0]	@ tmp202,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26374,
	b	.L82	@
.L85:
	mov	r1, r4	@, u8Enable
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r6, r0	@ s32Ret.627,
	mov	r0, r5	@, temp.626
	bl	PQ_HAL_EnableCTI	@
	orrs	r6, r0, r6	@,, s32Ret.627
	bne	.L66	@,
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L68	@,
.L86:
	mov	r1, r4	@, u8Enable
	mov	r0, #2	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.631,
	mov	r0, #2	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.631
	bne	.L66	@,
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L69	@,
.L87:
	mov	r1, r4	@, u8Enable
	mov	r0, #3	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.635,
	mov	r0, #3	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.635
	bne	.L66	@,
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L70	@,
.L88:
	mov	r1, r4	@, u8Enable
	mov	r0, #4	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.639,
	mov	r0, #4	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.639
	bne	.L66	@,
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L71	@,
.L89:
	mov	r1, r4	@, u8Enable
	mov	r0, #5	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.643,
	mov	r0, #5	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.643
	bne	.L66	@,
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L72	@,
.L90:
	mov	r1, r4	@, u8Enable
	mov	r0, #6	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.647,
	mov	r0, #6	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.647
	bne	.L66	@,
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L73	@,
.L91:
	mov	r1, r4	@, u8Enable
	mov	r0, #7	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.651,
	mov	r0, #7	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.651
	bne	.L66	@,
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L74	@,
.L92:
	mov	r1, r4	@, u8Enable
	mov	r0, #8	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.655,
	mov	r0, #8	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.655
	bne	.L66	@,
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L75	@,
.L93:
	mov	r1, r4	@, u8Enable
	mov	r0, #9	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.659,
	mov	r0, #9	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.659
	bne	.L66	@,
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L76	@,
.L94:
	mov	r1, r4	@, u8Enable
	mov	r0, #10	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.663,
	mov	r0, #10	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.663
	bne	.L66	@,
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L77	@,
.L95:
	mov	r1, r4	@, u8Enable
	mov	r0, #11	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.667,
	mov	r0, #11	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.667
	bne	.L66	@,
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L78	@,
.L96:
	mov	r1, r4	@, u8Enable
	mov	r0, #12	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.671,
	mov	r0, #12	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.671
	bne	.L66	@,
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L79	@,
.L97:
	mov	r1, r4	@, u8Enable
	mov	r0, #13	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.675,
	mov	r0, #13	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.675
	bne	.L66	@,
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L80	@,
.L98:
	mov	r1, r4	@, u8Enable
	mov	r0, #14	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret.679,
	mov	r0, #14	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret.679
	bne	.L66	@,
	mov	r0, #15	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L81	@,
.L99:
	mov	r1, r4	@, u8Enable
	mov	r0, #15	@,
	bl	PQ_HAL_EnableLTI	@
	mov	r1, r4	@, u8Enable
	mov	r5, r0	@ s32Ret,
	mov	r0, #15	@,
	bl	PQ_HAL_EnableCTI	@
	orrs	r5, r0, r5	@,, s32Ret
	beq	.L81	@,
	b	.L66	@
.L101:
	.align	2
.L100:
	.word	.LANCHOR2+68
	.fnend
	.size	PQ_MNG_SharpEn, .-PQ_MNG_SharpEn
	.align	2
	.global	PQ_MNG_EnableSharpen
	.type	PQ_MNG_EnableSharpen, %function
PQ_MNG_EnableSharpen:
	.fnstart
.LFB847:
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
	bl	PQ_MNG_SharpEn	@
	cmp	r0, #0	@ s32Ret
	bne	.L106	@,
.L104:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L106:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L107	@,
	movw	r3, #443	@,
	movw	ip, #:lower16:.LC4	@ tmp140,
	movt	ip, #:upper16:.LC4	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26472,
	b	.L104	@
.L108:
	.align	2
.L107:
	.word	.LANCHOR2+84
	.fnend
	.size	PQ_MNG_EnableSharpen, .-PQ_MNG_EnableSharpen
	.align	2
	.global	PQ_MNG_SharpInit
	.type	PQ_MNG_SharpInit, %function
PQ_MNG_SharpInit:
	.fnstart
.LFB837:
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
	mov	r4, r0	@ u32HandleNo, u32HandleNo
	bl	PQ_MNG_SharpenParaInitDefault	@
	mov	r0, r4	@, u32HandleNo
	movw	r1, #:lower16:.LANCHOR0	@,
	movt	r1, #:upper16:.LANCHOR0	@,
	bl	PQ_HAL_SetSharpRegist	@
	cmp	r0, #0	@ s32Ret
	bne	.L113	@,
.L111:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L113:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L114	@,
	mov	r3, #188	@,
	movw	ip, #:lower16:.LC5	@ tmp141,
	movt	ip, #:upper16:.LC5	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26345,
	b	.L111	@
.L115:
	.align	2
.L114:
	.word	.LANCHOR2+108
	.fnend
	.size	PQ_MNG_SharpInit, .-PQ_MNG_SharpInit
	.align	2
	.global	PQ_MNG_InitSharpen
	.type	PQ_MNG_InitSharpen, %function
PQ_MNG_InitSharpen:
	.fnstart
.LFB844:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	mov	r2, r0	@ pstPqParam, pstPqParam
	mov	r1, r0	@, pstPqParam
	mov	r0, #0	@,
	str	r2, [r3, #228]	@ pstPqParam, g_pstPqParam
	bl	PQ_MNG_SharpInit	@
	cmp	r0, #0	@ s32Ret
	bne	.L120	@,
.L118:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L120:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L121	@,
	mov	r3, #344	@,
	movw	ip, #:lower16:.LC6	@ tmp140,
	movt	ip, #:upper16:.LC6	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26421,
	b	.L118	@
.L122:
	.align	2
.L121:
	.word	.LANCHOR2+128
	.fnend
	.size	PQ_MNG_InitSharpen, .-PQ_MNG_InitSharpen
	.align	2
	.type	T.333, %function
T.333:
	.fnstart
.LFB850:
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
	movw	ip, #:lower16:.LANCHOR0	@ tmp207,
	movt	ip, #:upper16:.LANCHOR0	@ tmp207,
	ldr	ip, [ip, #228]	@ g_pstPqParam.308, g_pstPqParam
	cmp	ip, #0	@ g_pstPqParam.308,
	beq	.L135	@,
	add	r4, ip, #37888	@ ivtmp.781, g_pstPqParam.308,
	mov	r7, #0	@ i,
	add	ip, r4, #244	@ ivtmp.781, ivtmp.781,
.L127:
	ldr	r6, [ip, #-12]	@ <variable>.u32RegAddr, <variable>.u32RegAddr
	ldr	r5, [ip, #0]	@ u32Value, <variable>.u32Value
	cmp	r6, r1	@ <variable>.u32RegAddr, u32RegAddr
	ldrb	r4, [ip, #-8]	@ zero_extendqisi2	@ u8Lsb, <variable>.u8Lsb
	ldrb	r6, [ip, #-7]	@ zero_extendqisi2	@ u8Msb, <variable>.u8Msb
	ldrb	r8, [ip, #-6]	@ zero_extendqisi2	@ u8SourceMode, <variable>.u8SourceMode
	ldrb	sl, [ip, #-5]	@ zero_extendqisi2	@ u8OutputMode, <variable>.u8OutputMode
	bne	.L126	@,
	cmp	r4, #16	@ u8Lsb,
	bne	.L126	@,
	cmp	r6, #27	@ u8Msb,
	bne	.L126	@,
	cmp	r8, r2	@ u8SourceMode, u8InMode
	bne	.L126	@,
	cmp	sl, r3	@ u8OutputMode, u8OutMode
	bne	.L126	@,
.L133:
	str	r5, [r0, #0]	@ u32Value,* pu32Value
	mov	r0, #0	@ D.26532,
.L125:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L126:
	add	r4, ip, #16	@ tmp215, ivtmp.781,
	ldr	r5, [ip, #16]	@ u32Value, <variable>.u32Value
	add	r7, r7, #1	@ tmp214, i,
	ldr	r8, [r4, #-12]	@ <variable>.u32RegAddr, <variable>.u32RegAddr
	ldrb	r6, [r4, #-8]	@ zero_extendqisi2	@ u8Lsb, <variable>.u8Lsb
	cmp	r8, r1	@ <variable>.u32RegAddr, u32RegAddr
	ldrb	ip, [r4, #-7]	@ zero_extendqisi2	@ u8Msb, <variable>.u8Msb
	ldrb	r8, [r4, #-6]	@ zero_extendqisi2	@ u8SourceMode, <variable>.u8SourceMode
	ldrb	sl, [r4, #-5]	@ zero_extendqisi2	@ u8OutputMode, <variable>.u8OutputMode
	bne	.L130	@,
	cmp	r6, #16	@ u8Lsb,
	bne	.L130	@,
	cmp	ip, #27	@ u8Msb,
	bne	.L130	@,
	cmp	r8, r2	@ u8SourceMode, u8InMode
	bne	.L130	@,
	cmp	sl, r3	@ u8OutputMode, u8OutMode
	beq	.L133	@,
.L130:
	add	r7, r7, #1	@ i, tmp214,
	add	ip, r4, #16	@ ivtmp.781, tmp215,
	cmp	r7, #2048	@ i,
	bne	.L127	@,
	mvn	r0, #0	@ D.26532,
	b	.L125	@
.L135:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L136	@,
	mov	r3, #55	@,
	movw	lr, #:lower16:.LC0	@ tmp210,
	movt	lr, #:upper16:.LC0	@ tmp210,
	str	lr, [sp, #0]	@ tmp210,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26532,
	b	.L125	@
.L137:
	.align	2
.L136:
	.word	.LANCHOR2+148
	.fnend
	.size	T.333, .-T.333
	.align	2
	.global	PQ_MNG_SetSharpenStr
	.type	PQ_MNG_SetSharpenStr, %function
PQ_MNG_SetSharpenStr:
	.fnstart
.LFB845:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #32
	sub	sp, sp, #32	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #255	@ s32ShpStr,
	mov	r3, #0	@ tmp160,
	mov	r4, r0	@ s32ShpStr, s32ShpStr
	str	r3, [fp, #-36]	@ tmp160, u32BinChromaGain
	str	r3, [fp, #-32]	@ tmp160, u32BinLumaGain
	bhi	.L160	@,
	uxtb	r5, r1	@ D.26443, u32SourceMode
	uxtb	r7, r2	@ D.26444, u32OutputMode
	sub	r0, fp, #32	@,,
	movw	r1, #:lower16:-120913536	@,
	mov	r2, r5	@, D.26443
	movt	r1, #:upper16:-120913536	@,
	mov	r3, r7	@, D.26444
	bl	T.333	@
	mov	r2, r5	@, D.26443
	mov	r3, r7	@, D.26444
	movw	r1, #:lower16:-120913516	@,
	movt	r1, #:upper16:-120913516	@,
	mov	r6, r0	@ s32Ret,
	sub	r0, fp, #36	@,,
	bl	T.333	@
	orr	r0, r0, r6	@ tmp170,, s32Ret
	cmn	r0, #1	@ tmp170,
	ldrne	r1, [fp, #-32]	@ prephitmp.814, u32BinLumaGain
	moveq	r3, #304	@ tmp172,
	ldrne	r2, [fp, #-36]	@ prephitmp.800, u32BinChromaGain
	moveq	r2, r3	@ prephitmp.800, tmp172
	streq	r3, [fp, #-36]	@ tmp172, u32BinChromaGain
	movw	r3, #:lower16:.LANCHOR0	@ tmp173,
	movt	r3, #:upper16:.LANCHOR0	@ tmp173,
	moveq	r0, #256	@ tmp171,
	moveq	r1, r0	@ prephitmp.814, tmp171
	streq	r0, [fp, #-32]	@ tmp171, u32BinLumaGain
	str	r2, [r3, #192]	@ prephitmp.800, g_stSharpPara.stSharpSdData.stPqSharpChroma.u32Cgain_ratio
	mov	r0, #0	@,
	str	r1, [r3, #12]	@ prephitmp.814, g_stSharpPara.stSharpHdData.stPqSharpLuma.u32Lgain_ratio
	str	r2, [r3, #80]	@ prephitmp.800, g_stSharpPara.stSharpHdData.stPqSharpChroma.u32Cgain_ratio
	str	r1, [r3, #124]	@ prephitmp.814, g_stSharpPara.stSharpSdData.stPqSharpLuma.u32Lgain_ratio
	str	r1, [fp, #-44]	@ prephitmp.814, stSharpGainRatio.u32SD_Lgain_ratio
	str	r2, [fp, #-40]	@ prephitmp.800, stSharpGainRatio.u32SD_Cgain_ratio
	str	r1, [fp, #-52]	@ prephitmp.814, stSharpGainRatio.u32HD_Lgain_ratio
	str	r2, [fp, #-48]	@ prephitmp.800, stSharpGainRatio.u32HD_Cgain_ratio
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L161	@,
	mov	r0, #1	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L162	@,
.L144:
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L163	@,
.L145:
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L164	@,
.L146:
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L165	@,
.L147:
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L166	@,
.L148:
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L167	@,
.L149:
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L168	@,
.L150:
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L169	@,
.L151:
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L170	@,
.L152:
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L171	@,
.L153:
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L172	@,
.L154:
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L173	@,
.L155:
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L174	@,
.L156:
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L175	@,
.L157:
	mov	r0, #15	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L176	@,
.L158:
	movw	r1, #:lower16:.LANCHOR1	@ tmp193,
	movt	r1, #:upper16:.LANCHOR1	@ tmp193,
	mov	r0, #0	@ D.26442,
	str	r4, [r1, #0]	@ s32ShpStr, sg_s32SharpStrength
.L140:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L161:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #0	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #1	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L144	@,
.L162:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L145	@,
.L163:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #2	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L146	@,
.L164:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #3	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L147	@,
.L165:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #4	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L148	@,
.L166:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #5	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L149	@,
.L167:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #6	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L150	@,
.L168:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #7	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L151	@,
.L169:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #8	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L152	@,
.L170:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #9	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L153	@,
.L171:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #10	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L154	@,
.L172:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #11	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L155	@,
.L173:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #12	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L156	@,
.L174:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #13	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L157	@,
.L175:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #14	@,
	bl	PQ_HAL_SetSharpStrReg	@
	mov	r0, #15	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L158	@,
.L176:
	mov	r1, r4	@, s32ShpStr
	sub	r2, fp, #52	@,,
	mov	r0, #15	@,
	bl	PQ_HAL_SetSharpStrReg	@
	b	.L158	@
.L160:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L177	@,
	movw	r3, #375	@,
	movw	ip, #:lower16:.LC7	@ tmp165,
	movt	ip, #:upper16:.LC7	@ tmp165,
	str	ip, [sp, #0]	@ tmp165,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.26442,
	b	.L140	@
.L178:
	.align	2
.L177:
	.word	.LANCHOR2+176
	.fnend
	.size	PQ_MNG_SetSharpenStr, .-PQ_MNG_SetSharpenStr
	.section	.rodata
	.align	2
.LANCHOR2 = . + 0
	.type	__func__.26379, %object
	.size	__func__.26379, 18
__func__.26379:
	.ascii	"PQ_MNG_GetSharpEn\000"
	.space	2
	.type	__func__.26389, %object
	.size	__func__.26389, 19
__func__.26389:
	.ascii	"PQ_MNG_SharpDemoEn\000"
	.space	1
	.type	__func__.26481, %object
	.size	__func__.26481, 25
__func__.26481:
	.ascii	"PQ_MNG_EnableSharpenDemo\000"
	.space	3
	.type	__func__.26360, %object
	.size	__func__.26360, 15
__func__.26360:
	.ascii	"PQ_MNG_SharpEn\000"
	.space	1
	.type	__func__.26465, %object
	.size	__func__.26465, 21
__func__.26465:
	.ascii	"PQ_MNG_EnableSharpen\000"
	.space	3
	.type	__func__.26338, %object
	.size	__func__.26338, 17
__func__.26338:
	.ascii	"PQ_MNG_SharpInit\000"
	.space	3
	.type	__func__.26413, %object
	.size	__func__.26413, 19
__func__.26413:
	.ascii	"PQ_MNG_InitSharpen\000"
	.space	1
	.type	__func__.26291, %object
	.size	__func__.26291, 28
__func__.26291:
	.ascii	"PQ_MNG_FindSharpenGainRatio\000"
	.type	__func__.26432, %object
	.size	__func__.26432, 21
__func__.26432:
	.ascii	"PQ_MNG_SetSharpenStr\000"
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	sg_s32SharpStrength, %object
	.size	sg_s32SharpStrength, 4
sg_s32SharpStrength:
	.word	128
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"pointer is NULL!\012\000"
	.space	2
.LC1:
	.ascii	"error in sharpen demo enable!\012\000"
	.space	1
.LC2:
	.ascii	"error in enable sharpen demo!\012\000"
	.space	1
.LC3:
	.ascii	"error in sharpen enable!\012\000"
	.space	2
.LC4:
	.ascii	"error in enable sharpen!\012\000"
	.space	2
.LC5:
	.ascii	"error in init sharpen parameters!\012\000"
	.space	1
.LC6:
	.ascii	"error in init sharpen!\012\000"
.LC7:
	.ascii	"the value of setting sharpen strength is out of ran"
	.ascii	"ge!\012\000"
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_stSharpPara, %object
	.size	g_stSharpPara, 224
g_stSharpPara:
	.space	224
	.type	sg_bSharpen_EnFlag, %object
	.size	sg_bSharpen_EnFlag, 4
sg_bSharpen_EnFlag:
	.space	4
	.type	g_pstPqParam, %object
	.size	g_pstPqParam, 4
g_pstPqParam:
	.space	4
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
