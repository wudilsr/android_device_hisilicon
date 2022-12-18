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
	.file	"pq_mng_dei.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_mng_dei)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/mng/.pq_mng_dei.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/mng/pq_mng_dei.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/mng/pq_mng_dei.o -O2 -Wall -Wundef
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
	.global	PQ_MNG_GlobalMotionInit
	.type	PQ_MNG_GlobalMotionInit, %function
PQ_MNG_GlobalMotionInit:
	.fnstart
.LFB1400:
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
	mov	r2, #255	@ tmp143,
	mov	ip, #1	@ movhi	@,
	mov	r1, #192	@ movhi	@,
	mov	r3, #3	@ movhi	@,
	mov	r4, #128	@ movhi	@,
	strh	ip, [r0, #160]	@ movhi	@, <variable>.GLOBAL_MOTION_EN
	mov	ip, #16	@ tmp134,
	strh	r1, [r0, #164]	@ movhi	@, <variable>.GLOBAL_MOTION_THD
	mov	r1, #0	@ tmp153,
	strh	r3, [r0, #184]	@ movhi	@, <variable>.GLOBAL_MOTION_SLOPE
	mov	r3, #98	@ tmp165,
	strh	r4, [r0, #192]	@ movhi	@, <variable>.MAX_GLOBAL_MOTION_RATIO
	mov	r4, #32	@ tmp161,
	strh	r2, [r0, #172]	@ movhi	@ tmp143, <variable>.GLOBAL_MOTION_THD
	strh	r3, [r0, #182]	@ movhi	@ tmp165, <variable>.GLOBAL_MOTION_RATIO
	strh	ip, [r0, #162]	@ movhi	@ tmp134, <variable>.GLOBAL_MOTION_THD
	strh	r1, [r0, #190]	@ movhi	@ tmp153, <variable>.GLOBAL_MOTION_SLOPE
	strh	r4, [r0, #174]	@ movhi	@ tmp161, <variable>.GLOBAL_MOTION_RATIO
	str	ip, [r0, #0]	@ tmp134, <variable>.SMALL_MOTION_THD
	str	ip, [r0, #4]	@ tmp134, <variable>.LARGE_MOTION_THD
	strh	r2, [r0, #166]	@ movhi	@ tmp143, <variable>.GLOBAL_MOTION_THD
	strh	r2, [r0, #168]	@ movhi	@ tmp143, <variable>.GLOBAL_MOTION_THD
	strh	r2, [r0, #170]	@ movhi	@ tmp143, <variable>.GLOBAL_MOTION_THD
	strh	r1, [r0, #186]	@ movhi	@ tmp153, <variable>.GLOBAL_MOTION_SLOPE
	strh	r1, [r0, #188]	@ movhi	@ tmp153, <variable>.GLOBAL_MOTION_SLOPE
	strh	r4, [r0, #194]	@ movhi	@ tmp161, <variable>.MIN_GLOBAL_MOTION_RATIO
	strh	r3, [r0, #176]	@ movhi	@ tmp165, <variable>.GLOBAL_MOTION_RATIO
	strh	r3, [r0, #178]	@ movhi	@ tmp165, <variable>.GLOBAL_MOTION_RATIO
	strh	r3, [r0, #180]	@ movhi	@ tmp165, <variable>.GLOBAL_MOTION_RATIO
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_GlobalMotionInit, .-PQ_MNG_GlobalMotionInit
	.align	2
	.global	PQ_MNG_LUTMapping
	.type	PQ_MNG_LUTMapping, %function
PQ_MNG_LUTMapping:
	.fnstart
.LFB1401:
	@ args = 12, pretend = 0, frame = 0
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
	ldrb	ip, [fp, #12]	@ zero_extendqisi2	@ u8BitDepth, u8BitDepth
	ldrh	r4, [fp, #8]	@ DataIn, DataIn
	cmp	ip, #8	@ u8BitDepth,
	ldrh	ip, [r0, #0]	@ D.35687,* T
	ldrh	r5, [fp, #4]	@ DataMin, DataMin
	moveq	r7, #4	@, HalfValue,
	movne	r7, #16	@, HalfValue,
	moveq	r6, #3	@, Shift,
	movne	r6, #5	@, Shift,
	cmp	ip, r4	@ D.35687, DataIn
	ldrcsh	r4, [r1, #0]	@ DataOut,* R
	bcs	.L7	@,
	ldrh	r8, [r0, #2]	@ D.35696,
	cmp	r4, r8	@ DataIn, D.35696
	bls	.L17	@,
	ldrh	ip, [r0, #4]	@ D.35711,
	cmp	r4, ip	@ DataIn, D.35711
	bls	.L9	@,
	ldrh	r8, [r0, #6]	@ D.35728,
	cmp	r4, r8	@ DataIn, D.35728
	bls	.L10	@,
	ldrh	ip, [r0, #8]	@ tmp180,
	cmp	ip, r4	@ tmp180, DataIn
	bcs	.L11	@,
	ldrh	r4, [r1, #8]	@ DataOut,
.L7:
	cmp	r4, r3	@ DataOut, DataMax
	movlt	r3, r4	@ D.35768, DataOut
	movge	r3, r3	@ D.35768, DataMax
	cmp	r3, r5	@ D.35768, DataMin
	movge	r0, r3	@, D.35768
	movlt	r0, r5	@, DataMin
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L17:
	ldrh	r0, [r2, #0]	@ tmp156,* K
	rsb	r4, ip, r4	@ tmp155, D.35687, DataIn
	ldrh	r2, [r1, #0]	@ tmp160,* R
	mla	r4, r0, r4, r7	@ tmp158, tmp156, tmp155, HalfValue
	add	r4, r2, r4, asr r6	@, DataOut, tmp160, tmp158,
	b	.L7	@
.L9:
	ldrh	r0, [r2, #2]	@ tmp162,
	rsb	r2, r8, r4	@ tmp161, D.35696, DataIn
	ldrh	ip, [r1, #2]	@ tmp166,
	mla	r1, r0, r2, r7	@ tmp164, tmp162, tmp161, HalfValue
	add	r4, ip, r1, asr r6	@, DataOut, tmp166, tmp164,
	b	.L7	@
.L10:
	ldrh	r0, [r2, #4]	@ tmp168,
	rsb	r2, ip, r4	@ tmp167, D.35711, DataIn
	ldrh	ip, [r1, #4]	@ tmp172,
	mla	r4, r0, r2, r7	@ tmp170, tmp168, tmp167, HalfValue
	add	r4, ip, r4, asr r6	@, DataOut, tmp172, tmp170,
	b	.L7	@
.L11:
	ldrh	r0, [r2, #6]	@ tmp174,
	rsb	r4, r8, r4	@ tmp173, D.35728, DataIn
	ldrh	ip, [r1, #6]	@ tmp178,
	mla	r1, r0, r4, r7	@ tmp176, tmp174, tmp173, HalfValue
	add	r4, ip, r1, asr r6	@, DataOut, tmp178, tmp176,
	b	.L7	@
	.fnend
	.size	PQ_MNG_LUTMapping, .-PQ_MNG_LUTMapping
	.global	__aeabi_uidiv
	.align	2
	.global	PQ_MNG_DEIGlobalMotionGain
	.type	PQ_MNG_DEIGlobalMotionGain, %function
PQ_MNG_DEIGlobalMotionGain:
	.fnstart
.LFB1402:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #20
	sub	sp, sp, #20	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r4, r3	@ pstMotionHist, pstMotionHist
	ldrh	r3, [r3, #160]	@ <variable>.GLOBAL_MOTION_EN, <variable>.GLOBAL_MOTION_EN
	cmp	r3, #0	@ <variable>.GLOBAL_MOTION_EN,
	moveq	r6, #64	@ gain,
	bne	.L24	@,
.L20:
	mov	r0, r6	@, gain
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L24:
	movw	r5, #:lower16:.LANCHOR0	@ tmp168,
	movt	r5, #:upper16:.LANCHOR0	@ tmp168,
	ldrh	r0, [r4, #194]	@ <variable>.MIN_GLOBAL_MOTION_RATIO, <variable>.MIN_GLOBAL_MOTION_RATIO
	mov	lr, #8	@ tmp151,
	ldrh	r6, [r5, #0]	@ global_motion_last, global_motion_last
	add	r1, r4, #174	@, pstMotionHist,
	ldrh	r3, [r4, #192]	@ <variable>.MAX_GLOBAL_MOTION_RATIO, <variable>.MAX_GLOBAL_MOTION_RATIO
	add	r2, r4, #184	@, pstMotionHist,
	str	lr, [sp, #8]	@ tmp151,
	str	r0, [sp, #0]	@ <variable>.MIN_GLOBAL_MOTION_RATIO,
	add	r0, r4, #162	@, pstMotionHist,
	str	r6, [sp, #4]	@ global_motion_last,
	bl	PQ_MNG_LUTMapping	@
	ldr	r1, [r4, #156]	@ <variable>.MIDDL_MOTION_SUM, <variable>.MIDDL_MOTION_SUM
	ldr	r2, [r4, #148]	@ <variable>.LARGE_MOTION_SUM, <variable>.LARGE_MOTION_SUM
	ldr	r3, [r4, #152]	@ <variable>.MIDDL_MOTION_NUM, <variable>.MIDDL_MOTION_NUM
	ldr	ip, [r4, #144]	@ <variable>.LARGE_MOTION_NUM, <variable>.LARGE_MOTION_NUM
	mov	r6, r0	@ gain,
	add	r0, r1, r2	@ tmp152, <variable>.MIDDL_MOTION_SUM, <variable>.LARGE_MOTION_SUM
	add	r1, ip, r3	@ tmp156, <variable>.LARGE_MOTION_NUM, <variable>.MIDDL_MOTION_NUM
	mov	r0, r0, asl #1	@, tmp152,
	add	r1, r1, #1	@, tmp156,
	bl	__aeabi_uidiv	@
	cmp	r0, #0	@ tmp162
	beq	.L22	@,
	cmp	r0, #255	@ tmp162,
	movcs	r0, #255	@ iftmp.432,
.L22:
	str	r0, [r5, #8]	@ iftmp.432, global_motion_return
	str	r6, [r5, #12]	@ gain, gain_return
	str	r0, [r5, #4]	@ iftmp.432, global_motion_current
	str	r0, [r5, #0]	@ iftmp.432, global_motion_last
	b	.L20	@
	.fnend
	.size	PQ_MNG_DEIGlobalMotionGain, .-PQ_MNG_DEIGlobalMotionGain
	.align	2
	.global	PQ_MNG_DeInitDei
	.type	PQ_MNG_DeInitDei, %function
PQ_MNG_DeInitDei:
	.fnstart
.LFB1406:
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
	movw	r3, #:lower16:.LANCHOR1	@ tmp134,
	movt	r3, #:upper16:.LANCHOR1	@ tmp134,
	mov	r0, #0	@,
	ldr	r2, [r3, #0]	@ sg_bDeiInitFlag, sg_bDeiInitFlag
	cmp	r2, #0	@ sg_bDeiInitFlag,
	movne	r2, #0	@ tmp137,
	strne	r2, [r3, #0]	@ tmp137, sg_bDeiInitFlag
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_DeInitDei, .-PQ_MNG_DeInitDei
	.align	2
	.global	PQ_MNG_SetInterlaceMotionEn
	.type	PQ_MNG_SetInterlaceMotionEn, %function
PQ_MNG_SetInterlaceMotionEn:
	.fnstart
.LFB1407:
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
	.size	PQ_MNG_SetInterlaceMotionEn, .-PQ_MNG_SetInterlaceMotionEn
	.align	2
	.global	PQ_MNG_DEIParaInit
	.type	PQ_MNG_DEIParaInit, %function
PQ_MNG_DEIParaInit:
	.fnstart
.LFB1404:
	@ args = 0, pretend = 0, frame = 8
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
	movw	r3, #:lower16:.LANCHOR1	@ tmp136,
	movt	r3, #:upper16:.LANCHOR1	@ tmp136,
	mov	r2, #0	@ tmp137,
	mov	ip, #8	@ tmp159,
	mov	lr, #64	@ tmp269,
	mov	r5, #255	@ tmp275,
	mov	r4, #1	@ tmp145,
	mov	r6, #2	@ tmp169,
	mov	r7, #6	@ tmp213,
	mov	sl, #16	@ tmp315,
	mov	r9, #4	@ tmp171,
	str	r6, [r3, #56]	@ tmp169, g_stDeiPara.stMadIntpCtrl.s32DirIntenVer
	movw	r8, #:lower16:-320	@,
	str	r6, [r3, #60]	@ tmp169, g_stDeiPara.stMadIntpCtrl.s32RangeScale
	mov	r0, r2	@, tmp137
	str	r6, [r3, #92]	@ tmp169, g_stDeiPara.stMadChk1.s32CkRangeGain
	add	r1, r3, #4	@, tmp136,
	str	r6, [r3, #104]	@ tmp169, g_stDeiPara.stMadChk2.s32CkRangeGain
	str	r2, [r3, #4]	@ tmp137, g_stDeiPara.stFmdCtrl.u32Die_cmmode
	str	r2, [r3, #8]	@ tmp137, g_stDeiPara.stFmdCtrl.u32Die_lmmode
	str	r2, [r3, #12]	@ tmp137, g_stDeiPara.stFmdCtrl.u32Die_out_sel_c
	str	r2, [r3, #16]	@ tmp137, g_stDeiPara.stFmdCtrl.u32Die_out_sel_l
	str	r4, [r3, #40]	@ tmp145, g_stDeiPara.stMadMtnCtrl.bFrmMtnSmthEn
	str	r2, [r3, #20]	@ tmp137, g_stDeiPara.stMadMtnCtrl.bMfMaxChr
	str	r2, [r3, #24]	@ tmp137, g_stDeiPara.stMadMtnCtrl.bMfMaxLum
	str	r4, [r3, #36]	@ tmp145, g_stDeiPara.stMadMtnCtrl.bMtnIIrEn
	str	r4, [r3, #32]	@ tmp145, g_stDeiPara.stMadMtnCtrl.bRecMdEn
	str	r2, [r3, #44]	@ tmp137, g_stDeiPara.stMadMtnCtrl.bRecmdFrmfldBldMd
	str	r2, [r3, #28]	@ tmp137, g_stDeiPara.stMadMtnCtrl.bSceSdfMaxLum
	str	ip, [r3, #48]	@ tmp159, g_stDeiPara.stMadMtnCtrl.s32MfOffsetChr
	str	r2, [r3, #80]	@ tmp137, g_stDeiPara.stMadIntpCtrl.bEdgeMd
	str	r2, [r3, #76]	@ tmp137, g_stDeiPara.stMadIntpCtrl.bHorEdgeEn
	str	r2, [r3, #84]	@ tmp137, g_stDeiPara.stMadIntpCtrl.bMedBldEn
	str	r8, [fp, #-48]	@, %sfp
	mov	r8, #32	@,
	str	r9, [r3, #68]	@ tmp171, g_stDeiPara.stMadIntpCtrl.s32DirThd
	str	r8, [r3, #72]	@, g_stDeiPara.stMadIntpCtrl.s32BcGain
	movw	r8, #:lower16:-320	@,
	str	ip, [r3, #88]	@ tmp159, g_stDeiPara.stMadChk1.s32CkGain
	movt	r8, #:upper16:-320	@,
	str	ip, [r3, #100]	@ tmp159, g_stDeiPara.stMadChk2.s32CkGain
	str	r8, [r3, #52]	@, g_stDeiPara.stMadIntpCtrl.s32MinIntenVer
	movw	r8, #5000	@ tmp177,
	str	r8, [r3, #64]	@ tmp177, g_stDeiPara.stMadIntpCtrl.s32StrengthThd
	mov	r8, #40	@ tmp191,
	str	r8, [r3, #112]	@ tmp191, g_stDeiPara.stMadDirMult.s32MultDir
	mov	r8, #24	@ tmp193,
	str	r8, [r3, #116]	@ tmp193, g_stDeiPara.stMadDirMult.s32MultDir
	mov	r8, #27	@ tmp197,
	str	r8, [r3, #124]	@ tmp197, g_stDeiPara.stMadDirMult.s32MultDir
	mov	r8, #18	@ tmp199,
	str	r8, [r3, #128]	@ tmp199, g_stDeiPara.stMadDirMult.s32MultDir
	mov	r8, #30	@,
	str	r8, [r3, #96]	@, g_stDeiPara.stMadChk1.s32CkMaxRange
	str	r8, [r3, #108]	@, g_stDeiPara.stMadChk2.s32CkMaxRange
	mov	r8, #32	@,
	str	r8, [r3, #120]	@, g_stDeiPara.stMadDirMult.s32MultDir
	mov	r8, #15	@,
	str	r8, [r3, #132]	@, g_stDeiPara.stMadDirMult.s32MultDir
	mov	r8, #12	@ tmp203,
	str	r7, [r3, #220]	@ tmp213, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	str	r8, [r3, #136]	@ tmp203, g_stDeiPara.stMadDirMult.s32MultDir
	mov	r8, #11	@ tmp205,
	str	r7, [r3, #156]	@ tmp213, g_stDeiPara.stMadDirMult.s32MultDir
	str	r8, [r3, #140]	@ tmp205, g_stDeiPara.stMadDirMult.s32MultDir
	mov	r8, #9	@ tmp207,
	str	r7, [r3, #196]	@ tmp213, g_stDeiPara.stMadCcrScl.s32NCcrDetBld
	str	r8, [r3, #144]	@ tmp207, g_stDeiPara.stMadDirMult.s32MultDir
	mov	r8, #3	@ tmp219,
	str	r7, [r3, #204]	@ tmp213, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	str	r8, [r3, #168]	@ tmp219, g_stDeiPara.stMadDirMult.s32MultDir
	mov	r8, #192	@ tmp235,
	str	r7, [r3, #216]	@ tmp213, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	mov	r7, #7	@,
	str	r8, [r3, #200]	@ tmp235, g_stDeiPara.stMadCcrScl.s32XChrMax
	mov	r8, #5	@,
	str	r7, [r3, #224]	@, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	mov	r7, #30	@,
	str	r8, [r3, #212]	@, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	mov	r8, #7	@,
	str	r9, [r3, #192]	@ tmp171, g_stDeiPara.stMadCcrScl.s32SimlrThd
	str	r8, [r3, #228]	@, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	str	r8, [r3, #152]	@, g_stDeiPara.stMadDirMult.s32MultDir
	mov	r8, #5	@,
	str	ip, [r3, #148]	@ tmp159, g_stDeiPara.stMadDirMult.s32MultDir
	str	r8, [r3, #160]	@, g_stDeiPara.stMadDirMult.s32MultDir
	str	r8, [r3, #164]	@, g_stDeiPara.stMadDirMult.s32MultDir
	str	r8, [r3, #208]	@, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	mov	r8, #10	@ tmp271,
	str	r4, [r3, #172]	@ tmp145, g_stDeiPara.stMadCcrScl.bCcrEn
	str	r9, [r3, #176]	@ tmp171, g_stDeiPara.stMadCcrScl.s32ChrMaOffset
	str	ip, [r3, #180]	@ tmp159, g_stDeiPara.stMadCcrScl.s32NCcrDetMax
	str	r9, [r3, #184]	@ tmp171, g_stDeiPara.stMadCcrScl.s32NccrDetThd
	str	ip, [r3, #188]	@ tmp159, g_stDeiPara.stMadCcrScl.s32SimlrMax
	str	ip, [r3, #232]	@ tmp159, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	str	ip, [r3, #236]	@ tmp159, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	str	ip, [r3, #240]	@ tmp159, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	str	ip, [r3, #244]	@ tmp159, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	str	ip, [r3, #248]	@ tmp159, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	str	ip, [r3, #252]	@ tmp159, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	str	ip, [r3, #256]	@ tmp159, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	str	ip, [r3, #260]	@ tmp159, g_stDeiPara.stMadIntpScl.s32IntpSclRat
	str	r2, [r3, #264]	@ tmp137, g_stDeiPara.stMadCombChk.bCombChkEn
	str	lr, [r3, #288]	@ tmp269, g_stDeiPara.stMadCombChk.s32CombChkEdgeThd
	str	r8, [r3, #272]	@ tmp271, g_stDeiPara.stMadCombChk.s32CombChkLowLmt
	mov	r8, #15	@,
	str	r7, [r3, #284]	@, g_stDeiPara.stMadCombChk.s32CombChkMdThd
	mov	r7, #160	@ tmp279,
	str	r8, [r3, #276]	@, g_stDeiPara.stMadCombChk.s32CombChkMinThdV
	mvn	r8, #1	@ tmp287,
	str	r7, [r3, #268]	@ tmp279, g_stDeiPara.stMadCombChk.s32CombChkUpLmt
	mov	r7, #144	@ tmp317,
	str	r8, [r3, #316]	@ tmp287, g_stDeiPara.stMadFldMtn.s32FldMtnCrvSlp
	mov	r8, #208	@ tmp319,
	str	r7, [r3, #364]	@ tmp317, g_stDeiPara.stIirMtnCrv.s32MtnDiffThd
	mov	r7, #48	@ tmp329,
	str	r8, [r3, #368]	@ tmp319, g_stDeiPara.stIirMtnCrv.s32MtnDiffThd
	mov	r8, #32	@,
	str	r7, [r3, #404]	@ tmp329, g_stDeiPara.stIirMtnCrv.s32MtnIirCrvRat
	mov	r7, #128	@,
	str	r5, [r3, #280]	@ tmp275, g_stDeiPara.stMadCombChk.s32CombChkMinThdH
	str	ip, [r3, #292]	@ tmp159, g_stDeiPara.stMadJitMtn.s32JitGain
	str	r2, [r3, #296]	@ tmp137, g_stDeiPara.stMadJitMtn.s32JitCoring
	str	r2, [r3, #304]	@ tmp137, g_stDeiPara.stMadFldMtn.s32FldMtnCoring
	str	ip, [r3, #300]	@ tmp159, g_stDeiPara.stMadFldMtn.s32FldMtnGain
	str	r5, [r3, #312]	@ tmp275, g_stDeiPara.stMadFldMtn.s32FldMtnThdHigh
	str	r2, [r3, #308]	@ tmp137, g_stDeiPara.stMadFldMtn.s32FldMtnThdLow
	str	r4, [r3, #320]	@ tmp145, g_stDeiPara.stMadHistMtn.bHistMtnEn
	str	r2, [r3, #328]	@ tmp137, g_stDeiPara.stMadHistMtn.bHistMtnWrtMd
	str	r2, [r3, #324]	@ tmp137, g_stDeiPara.stMadHistMtn.bHistMtnInfoWrtMd
	str	r4, [r3, #332]	@ tmp145, g_stDeiPara.stMadHistMtn.bHistMtnUseMd
	str	r4, [r3, #340]	@ tmp145, g_stDeiPara.stMadHistMtn.bPpreInfoEn
	str	r2, [r3, #336]	@ tmp137, g_stDeiPara.stMadHistMtn.bPreInfoEn
	str	r4, [r3, #352]	@ tmp145, g_stDeiPara.stMadRecMd.s32RecMdFldMtnStp
	str	r4, [r3, #356]	@ tmp145, g_stDeiPara.stMadRecMd.s32RecMdFldMtnStp
	str	r2, [r3, #344]	@ tmp137, g_stDeiPara.stMadRecMd.s32RecMdFrmMtnStp
	str	r2, [r3, #348]	@ tmp137, g_stDeiPara.stMadRecMd.s32RecMdFrmMtnStp
	str	sl, [r3, #360]	@ tmp315, g_stDeiPara.stIirMtnCrv.s32MtnDiffThd
	str	r5, [r3, #372]	@ tmp275, g_stDeiPara.stIirMtnCrv.s32MtnDiffThd
	str	r5, [r3, #376]	@ tmp275, g_stDeiPara.stIirMtnCrv.s32MtnDiffThd
	str	r5, [r3, #380]	@ tmp275, g_stDeiPara.stIirMtnCrv.s32MtnDiffThd
	str	r8, [r3, #400]	@, g_stDeiPara.stIirMtnCrv.s32MtnIirCrvRat
	str	lr, [r3, #408]	@ tmp269, g_stDeiPara.stIirMtnCrv.s32MtnIirCrvRat
	str	lr, [r3, #412]	@ tmp269, g_stDeiPara.stIirMtnCrv.s32MtnIirCrvRat
	str	lr, [r3, #416]	@ tmp269, g_stDeiPara.stIirMtnCrv.s32MtnIirCrvRat
	str	r4, [r3, #384]	@ tmp145, g_stDeiPara.stIirMtnCrv.s32MtnIirCrvSlp
	str	r6, [r3, #388]	@ tmp169, g_stDeiPara.stIirMtnCrv.s32MtnIirCrvSlp
	mov	r6, #72	@,
	str	r8, [r3, #420]	@, g_stDeiPara.stIirMtnCrv.s32MtnIirCrvRatMin
	str	ip, [r3, #496]	@ tmp159, g_stDeiPara.stFrmFldBld.s32FrmFldBldThd
	str	r6, [r3, #500]	@, g_stDeiPara.stFrmFldBld.s32FrmFldBldThd
	str	r2, [r3, #392]	@ tmp137, g_stDeiPara.stIirMtnCrv.s32MtnIirCrvSlp
	str	r2, [r3, #396]	@ tmp137, g_stDeiPara.stIirMtnCrv.s32MtnIirCrvSlp
	str	lr, [r3, #424]	@ tmp269, g_stDeiPara.stIirMtnCrv.s32MtnIirCrvRatMax
	str	r2, [r3, #468]	@ tmp137, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthRat
	str	lr, [r3, #472]	@ tmp269, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthRat
	str	lr, [r3, #476]	@ tmp269, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthRat
	str	lr, [r3, #480]	@ tmp269, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthRat
	str	lr, [r3, #484]	@ tmp269, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthRat
	str	ip, [r3, #452]	@ tmp159, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthSlp
	str	r2, [r3, #456]	@ tmp137, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthSlp
	str	r2, [r3, #460]	@ tmp137, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthSlp
	str	r2, [r3, #464]	@ tmp137, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthSlp
	str	ip, [r3, #428]	@ tmp159, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthThd
	str	r6, [r3, #432]	@, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthThd
	str	r5, [r3, #436]	@ tmp275, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthThd
	str	r5, [r3, #440]	@ tmp275, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthThd
	str	r5, [r3, #444]	@ tmp275, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthThd
	str	r5, [r3, #448]	@ tmp275, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthThd
	str	lr, [r3, #492]	@ tmp269, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthRatMax
	str	r2, [r3, #488]	@ tmp137, g_stDeiPara.stFrmMtnSmth.s32FrmMtnSmthRatMin
	str	r2, [r3, #536]	@ tmp137, g_stDeiPara.stFrmFldBld.s32FrmFldBldRat
	str	lr, [r3, #540]	@ tmp269, g_stDeiPara.stFrmFldBld.s32FrmFldBldRat
	str	lr, [r3, #544]	@ tmp269, g_stDeiPara.stFrmFldBld.s32FrmFldBldRat
	str	lr, [r3, #548]	@ tmp269, g_stDeiPara.stFrmFldBld.s32FrmFldBldRat
	str	lr, [r3, #552]	@ tmp269, g_stDeiPara.stFrmFldBld.s32FrmFldBldRat
	str	ip, [r3, #520]	@ tmp159, g_stDeiPara.stFrmFldBld.s32FrmFldBldSlp
	str	r2, [r3, #524]	@ tmp137, g_stDeiPara.stFrmFldBld.s32FrmFldBldSlp
	str	r2, [r3, #528]	@ tmp137, g_stDeiPara.stFrmFldBld.s32FrmFldBldSlp
	str	r2, [r3, #532]	@ tmp137, g_stDeiPara.stFrmFldBld.s32FrmFldBldSlp
	str	r5, [r3, #504]	@ tmp275, g_stDeiPara.stFrmFldBld.s32FrmFldBldThd
	str	r5, [r3, #508]	@ tmp275, g_stDeiPara.stFrmFldBld.s32FrmFldBldThd
	str	r5, [r3, #516]	@ tmp275, g_stDeiPara.stFrmFldBld.s32FrmFldBldThd
	str	lr, [r3, #560]	@ tmp269, g_stDeiPara.stFrmFldBld.s32FrmFldBldRatMax
	str	r7, [r3, #580]	@, g_stDeiPara.stMadMtnAdj.s32MtnAdjGainChr
	str	sl, [r3, #592]	@ tmp315, g_stDeiPara.stMadGlbMtnThd.s32MtnThdLarge
	str	r5, [r3, #512]	@ tmp275, g_stDeiPara.stFrmFldBld.s32FrmFldBldThd
	str	r2, [r3, #556]	@ tmp137, g_stDeiPara.stFrmFldBld.s32FrmFldBldRatMin
	str	r4, [r3, #564]	@ tmp145, g_stDeiPara.stMadMorFlt.bMorFltEn
	str	r2, [r3, #568]	@ tmp137, g_stDeiPara.stMadMorFlt.s32MorFltSize
	str	r2, [r3, #572]	@ tmp137, g_stDeiPara.stMadMorFlt.s32MorFltThd
	str	r4, [r3, #620]	@ tmp145, g_stDeiPara.bIgblEn
	str	r7, [r3, #576]	@, g_stDeiPara.stMadMtnAdj.s32MtnAdjGain
	str	r2, [r3, #584]	@ tmp137, g_stDeiPara.stMadMtnAdj.s32MtnAdjCoring
	str	sl, [r3, #588]	@ tmp315, g_stDeiPara.stMadGlbMtnThd.s32MtnThdSmall
	str	sl, [r3, #596]	@ tmp315, g_stDeiPara.stMadGlbMtnThd.s32MtnThdMiddle0
	str	sl, [r3, #600]	@ tmp315, g_stDeiPara.stMadGlbMtnThd.s32MtnThdMiddle1
	bl	PQ_HAL_SetDeiRegist	@
	cmp	r0, #0	@ s32Ret
	bne	.L34	@,
.L32:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L34:
	mov	r0, r4	@, tmp145
	mov	r1, #41	@,
	movw	r2, #:lower16:.LANCHOR2	@,
	mov	r3, #424	@,
	movt	r2, #:upper16:.LANCHOR2	@,
	movw	lr, #:lower16:.LC0	@ tmp441,
	movt	lr, #:upper16:.LC0	@ tmp441,
	str	lr, [sp, #0]	@ tmp441,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35837,
	b	.L32	@
	.fnend
	.size	PQ_MNG_DEIParaInit, .-PQ_MNG_DEIParaInit
	.align	2
	.global	PQ_MNG_InitDei
	.type	PQ_MNG_InitDei, %function
PQ_MNG_InitDei:
	.fnstart
.LFB1405:
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
	movw	r4, #:lower16:.LANCHOR1	@ tmp136,
	movt	r4, #:upper16:.LANCHOR1	@ tmp136,
	ldr	r3, [r4, #0]	@ sg_bDeiInitFlag, sg_bDeiInitFlag
	cmp	r3, #1	@ sg_bDeiInitFlag,
	moveq	r0, #0	@ D.35853,
	beq	.L37	@,
	bl	PQ_MNG_DEIParaInit	@
	cmp	r0, #0	@ s32Ret
	bne	.L40	@,
	mov	r2, #255	@ tmp142,
	mov	lr, #64	@ tmp174,
	mov	r1, #1	@ tmp206,
	str	r2, [r4, #684]	@ tmp142, global_motion_last
	str	lr, [r4, #748]	@ tmp174, gain_last
	str	r1, [r4, #0]	@ tmp206, sg_bDeiInitFlag
	str	r2, [r4, #624]	@ tmp142, global_motion_last
	str	r2, [r4, #628]	@ tmp142, global_motion_last
	str	r2, [r4, #632]	@ tmp142, global_motion_last
	str	r2, [r4, #636]	@ tmp142, global_motion_last
	str	r2, [r4, #640]	@ tmp142, global_motion_last
	str	r2, [r4, #644]	@ tmp142, global_motion_last
	str	r2, [r4, #648]	@ tmp142, global_motion_last
	str	r2, [r4, #652]	@ tmp142, global_motion_last
	str	r2, [r4, #656]	@ tmp142, global_motion_last
	str	r2, [r4, #660]	@ tmp142, global_motion_last
	str	r2, [r4, #664]	@ tmp142, global_motion_last
	str	r2, [r4, #668]	@ tmp142, global_motion_last
	str	r2, [r4, #672]	@ tmp142, global_motion_last
	str	r2, [r4, #676]	@ tmp142, global_motion_last
	str	r2, [r4, #680]	@ tmp142, global_motion_last
	str	lr, [r4, #688]	@ tmp174, gain_last
	str	lr, [r4, #692]	@ tmp174, gain_last
	str	lr, [r4, #696]	@ tmp174, gain_last
	str	lr, [r4, #700]	@ tmp174, gain_last
	str	lr, [r4, #704]	@ tmp174, gain_last
	str	lr, [r4, #708]	@ tmp174, gain_last
	str	lr, [r4, #712]	@ tmp174, gain_last
	str	lr, [r4, #716]	@ tmp174, gain_last
	str	lr, [r4, #720]	@ tmp174, gain_last
	str	lr, [r4, #724]	@ tmp174, gain_last
	str	lr, [r4, #728]	@ tmp174, gain_last
	str	lr, [r4, #732]	@ tmp174, gain_last
	str	lr, [r4, #736]	@ tmp174, gain_last
	str	lr, [r4, #740]	@ tmp174, gain_last
	str	lr, [r4, #744]	@ tmp174, gain_last
.L37:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L40:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L41	@,
	mov	r3, #456	@,
	movw	ip, #:lower16:.LC1	@ tmp140,
	movt	ip, #:upper16:.LC1	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35853,
	b	.L37	@
.L42:
	.align	2
.L41:
	.word	.LANCHOR2+20
	.fnend
	.size	PQ_MNG_InitDei, .-PQ_MNG_InitDei
	.align	2
	.global	PQ_MNG_GetGlobalMotion
	.type	PQ_MNG_GetGlobalMotion, %function
PQ_MNG_GetGlobalMotion:
	.fnstart
.LFB1403:
	@ args = 0, pretend = 0, frame = 200
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #200
	sub	sp, sp, #200	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r4, r0	@ pstMotionInput, pstMotionInput
	sub	r5, fp, #224	@ tmp137,,
	ldr	r7, [r0, #0]	@ s32WidthY, <variable>.u32Width
	ldr	r6, [r4, #4]	@ s32HeightY, <variable>.u32Height
	mov	r0, r5	@, tmp137
	bl	PQ_MNG_GlobalMotionInit	@
	mov	r1, r5	@, tmp137
	mov	r0, r4	@, pstMotionInput
	bl	PQ_HAL_GetMotionHistReg	@
	mov	r1, r6	@, s32HeightY
	mov	r3, r5	@, tmp137
	mov	r0, r7	@, s32WidthY
	mov	r2, #8	@,
	bl	PQ_MNG_DEIGlobalMotionGain	@
	movw	r3, #:lower16:.LANCHOR0	@ tmp141,
	movt	r3, #:upper16:.LANCHOR0	@ tmp141,
	ldr	r0, [r4, #8]	@, <variable>.u32HandleNo
	ldr	r2, [r3, #8]	@, global_motion_return
	ldr	r1, [r3, #12]	@, gain_return
	bl	PQ_HAL_SetDeiAdjustGain	@
	mov	r0, #0	@,
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	.fnend
	.size	PQ_MNG_GetGlobalMotion, .-PQ_MNG_GetGlobalMotion
	.global	g_stDeiPara
	.section	.rodata
	.align	2
.LANCHOR2 = . + 0
	.type	__func__.35830, %object
	.size	__func__.35830, 19
__func__.35830:
	.ascii	"PQ_MNG_DEIParaInit\000"
	.space	1
	.type	__func__.35843, %object
	.size	__func__.35843, 15
__func__.35843:
	.ascii	"PQ_MNG_InitDei\000"
	.data
	.align	2
.LANCHOR0 = . + 0
	.type	global_motion_last.35778, %object
	.size	global_motion_last.35778, 4
global_motion_last.35778:
	.word	255
	.type	global_motion_current.35777, %object
	.size	global_motion_current.35777, 4
global_motion_current.35777:
	.word	255
	.type	global_motion_return, %object
	.size	global_motion_return, 4
global_motion_return:
	.word	255
	.type	gain_return, %object
	.size	gain_return, 4
gain_return:
	.word	64
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"error in set dei register\012\000"
	.space	1
.LC1:
	.ascii	"dei init error\012\000"
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	sg_bDeiInitFlag, %object
	.size	sg_bDeiInitFlag, 4
sg_bDeiInitFlag:
	.space	4
	.type	g_stDeiPara, %object
	.size	g_stDeiPara, 620
g_stDeiPara:
	.space	620
	.type	global_motion_last, %object
	.size	global_motion_last, 64
global_motion_last:
	.space	64
	.type	gain_last, %object
	.size	gain_last, 64
gain_last:
	.space	64
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
