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
	.file	"pq_mng_dbdr_98m.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_mng_dbdr_98m)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/mng/.pq_mng_dbdr_98m.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/mng/pq_mng_dbdr_98m.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/mng/pq_mng_dbdr_98m.o -O2 -Wall -Wundef
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
	.global	PQ_MNG_DnrParaInitDefault
	.type	PQ_MNG_DnrParaInitDefault, %function
PQ_MNG_DnrParaInitDefault:
	.fnstart
.LFB654:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp133,
	movt	r3, #:upper16:.LANCHOR0	@ tmp133,
	mov	r2, #1	@ tmp134,
	mov	r1, #8	@ tmp138,
	mov	r0, #0	@ tmp136,
	mov	ip, #16	@ tmp144,
	str	r0, [r3, #4]	@ tmp136, g_stDnrPara.stPqDnrCtrl.u32Dr_Demo_en
	str	ip, [r3, #76]	@ tmp144, g_stDnrPara.stPqDnrDrFilter.u32Dr_thr_maxsimilarpixdiff
	mov	r0, #64	@ tmp146,
	mov	ip, #40	@ tmp148,
	str	r0, [r3, #88]	@ tmp146, g_stDnrPara.stPqDnrInfo.u32thd_cntrst8
	str	r2, [r3, #104]	@ tmp134, sg_bDR_EnFlag
	mov	r0, #4	@ tmp150,
	str	r1, [r3, #72]	@ tmp138, g_stDnrPara.stPqDnrDrFilter.u32Dr_thr_flat3x3zone
	str	ip, [r3, #92]	@ tmp148, g_stDnrPara.stPqDnrInfo.u32thd_maxgrad
	str	r0, [r3, #96]	@ tmp150, g_stDnrPara.stPqDnrInfo.u32thr_intl_cnt
	str	r2, [r3, #0]	@ tmp134, g_stDnrPara.stPqDnrCtrl.u32Dr_en
	str	r1, [r3, #84]	@ tmp138, g_stDnrPara.stPqDnrDrFilter.u32Dr_alphascale
	str	r1, [r3, #80]	@ tmp138, g_stDnrPara.stPqDnrDrFilter.u32Dr_betascale
	str	r2, [r3, #100]	@ tmp134, g_stDnrPara.stPqDnrInfo.u32thr_intl_colcnt
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_DnrParaInitDefault, .-PQ_MNG_DnrParaInitDefault
	.align	2
	.global	PQ_MNG_DeinitDNR
	.type	PQ_MNG_DeinitDNR, %function
PQ_MNG_DeinitDNR:
	.fnstart
.LFB656:
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
	movt	r3, #:upper16:.LANCHOR0	@ tmp134,
	mov	r0, #0	@,
	ldr	r2, [r3, #108]	@ sg_bDNRInitFlag, sg_bDNRInitFlag
	cmp	r2, #0	@ sg_bDNRInitFlag,
	movne	r2, #0	@ tmp137,
	strne	r2, [r3, #108]	@ tmp137, sg_bDNRInitFlag
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_DeinitDNR, .-PQ_MNG_DeinitDNR
	.align	2
	.global	PQ_MNG_GetDRDemoFlag
	.type	PQ_MNG_GetDRDemoFlag, %function
PQ_MNG_GetDRDemoFlag:
	.fnstart
.LFB662:
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
	beq	.L11	@,
	movw	r1, #:lower16:.LANCHOR0	@ tmp138,
	movt	r1, #:upper16:.LANCHOR0	@ tmp138,
	mov	r0, #0	@ D.23315,
	ldr	r3, [r1, #112]	@ sg_bDRDemo_EnFlag, sg_bDRDemo_EnFlag
	str	r3, [r2, #0]	@ sg_bDRDemo_EnFlag,* pbOnOff
.L8:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L11:
	mov	r0, #1	@,
	mov	r1, #41	@,
	movw	r2, #:lower16:.LANCHOR1	@,
	movw	r3, #285	@,
	movt	r2, #:upper16:.LANCHOR1	@,
	movw	ip, #:lower16:.LC0	@ tmp137,
	movt	ip, #:upper16:.LC0	@ tmp137,
	str	ip, [sp, #0]	@ tmp137,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.23315,
	b	.L8	@
	.fnend
	.size	PQ_MNG_GetDRDemoFlag, .-PQ_MNG_GetDRDemoFlag
	.align	2
	.global	PQ_MNG_GetDREnableFlag
	.type	PQ_MNG_GetDREnableFlag, %function
PQ_MNG_GetDREnableFlag:
	.fnstart
.LFB660:
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
	movw	r1, #:lower16:.LANCHOR0	@ tmp139,
	movt	r1, #:upper16:.LANCHOR0	@ tmp139,
	mov	r0, #0	@ D.23289,
	ldr	r3, [r1, #104]	@ sg_bDR_EnFlag, sg_bDR_EnFlag
	str	r3, [r2, #0]	@ sg_bDR_EnFlag,* pbOnOff
.L14:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L16:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L17	@,
	mov	r3, #229	@,
	movw	ip, #:lower16:.LC0	@ tmp138,
	movt	ip, #:upper16:.LC0	@ tmp138,
	str	ip, [sp, #0]	@ tmp138,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.23289,
	b	.L14	@
.L18:
	.align	2
.L17:
	.word	.LANCHOR1+24
	.fnend
	.size	PQ_MNG_GetDREnableFlag, .-PQ_MNG_GetDREnableFlag
	.align	2
	.global	PQ_MNG_GetDBEnableFlag
	.type	PQ_MNG_GetDBEnableFlag, %function
PQ_MNG_GetDBEnableFlag:
	.fnstart
.LFB658:
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
	beq	.L23	@,
	movw	r1, #:lower16:.LANCHOR0	@ tmp139,
	movt	r1, #:upper16:.LANCHOR0	@ tmp139,
	mov	r0, #0	@ D.23263,
	ldr	r3, [r1, #116]	@ sg_bDB_EnFlag, sg_bDB_EnFlag
	str	r3, [r2, #0]	@ sg_bDB_EnFlag,* pbOnOff
.L21:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L23:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L24	@,
	mov	r3, #173	@,
	movw	ip, #:lower16:.LC0	@ tmp138,
	movt	ip, #:upper16:.LC0	@ tmp138,
	str	ip, [sp, #0]	@ tmp138,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.23263,
	b	.L21	@
.L25:
	.align	2
.L24:
	.word	.LANCHOR1+48
	.fnend
	.size	PQ_MNG_GetDBEnableFlag, .-PQ_MNG_GetDBEnableFlag
	.align	2
	.global	PQ_MNG_EnableDRDemo
	.type	PQ_MNG_EnableDRDemo, %function
PQ_MNG_EnableDRDemo:
	.fnstart
.LFB661:
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
	mov	r4, r0	@ bOnOff, bOnOff
	mov	r0, #0	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	mvnne	r5, #0	@ s32Ret,
	beq	.L47	@,
	mov	r0, #1	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L48	@,
.L29:
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L49	@,
.L30:
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L50	@,
.L31:
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L51	@,
.L32:
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L52	@,
.L33:
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L53	@,
.L34:
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L54	@,
.L35:
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L55	@,
.L36:
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L56	@,
.L37:
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L57	@,
.L38:
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L58	@,
.L39:
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L59	@,
.L40:
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L60	@,
.L41:
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L61	@,
.L42:
	mov	r0, #15	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L62	@,
.L43:
	cmp	r5, #0	@ s32Ret,
	bne	.L63	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp156,
	movt	r3, #:upper16:.LANCHOR0	@ tmp156,
	mov	r0, r5	@ D.23308, s32Ret
	str	r4, [r3, #112]	@ bOnOff, sg_bDRDemo_EnFlag
.L45:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L47:
	mov	r1, r4	@, bOnOff
	mov	r0, #0	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #1	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L29	@,
.L48:
	mov	r1, r4	@, bOnOff
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L30	@,
.L49:
	mov	r1, r4	@, bOnOff
	mov	r0, #2	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L31	@,
.L50:
	mov	r1, r4	@, bOnOff
	mov	r0, #3	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L32	@,
.L51:
	mov	r1, r4	@, bOnOff
	mov	r0, #4	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L33	@,
.L52:
	mov	r1, r4	@, bOnOff
	mov	r0, #5	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L34	@,
.L53:
	mov	r1, r4	@, bOnOff
	mov	r0, #6	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L35	@,
.L54:
	mov	r1, r4	@, bOnOff
	mov	r0, #7	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L36	@,
.L55:
	mov	r1, r4	@, bOnOff
	mov	r0, #8	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L37	@,
.L56:
	mov	r1, r4	@, bOnOff
	mov	r0, #9	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L38	@,
.L57:
	mov	r1, r4	@, bOnOff
	mov	r0, #10	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L39	@,
.L58:
	mov	r1, r4	@, bOnOff
	mov	r0, #11	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L40	@,
.L59:
	mov	r1, r4	@, bOnOff
	mov	r0, #12	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L41	@,
.L60:
	mov	r1, r4	@, bOnOff
	mov	r0, #13	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L42	@,
.L61:
	mov	r1, r4	@, bOnOff
	mov	r0, #14	@,
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #15	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L43	@,
.L62:
	mov	r0, #15	@,
	mov	r1, r4	@, bOnOff
	bl	PQ_HAL_EnableDRDemo	@
	mov	r5, r0	@ s32Ret,
	b	.L43	@
.L63:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L64	@,
	movw	r3, #261	@,
	movw	ip, #:lower16:.LC1	@ tmp155,
	movt	ip, #:upper16:.LC1	@ tmp155,
	str	ip, [sp, #0]	@ tmp155,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.23308,
	b	.L45	@
.L65:
	.align	2
.L64:
	.word	.LANCHOR1+72
	.fnend
	.size	PQ_MNG_EnableDRDemo, .-PQ_MNG_EnableDRDemo
	.align	2
	.global	PQ_MNG_EnableDR
	.type	PQ_MNG_EnableDR, %function
PQ_MNG_EnableDR:
	.fnstart
.LFB659:
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
	mov	r4, r0	@ bOnOff, bOnOff
	mov	r0, #0	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	mvnne	r5, #0	@ s32Ret,
	beq	.L87	@,
	mov	r0, #1	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L88	@,
.L69:
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L89	@,
.L70:
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L90	@,
.L71:
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L91	@,
.L72:
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L92	@,
.L73:
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L93	@,
.L74:
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L94	@,
.L75:
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L95	@,
.L76:
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L96	@,
.L77:
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L97	@,
.L78:
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L98	@,
.L79:
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L99	@,
.L80:
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L100	@,
.L81:
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L101	@,
.L82:
	mov	r0, #15	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L102	@,
.L83:
	cmp	r5, #0	@ s32Ret,
	bne	.L103	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp156,
	movt	r3, #:upper16:.LANCHOR0	@ tmp156,
	mov	r0, r5	@ D.23282, s32Ret
	str	r4, [r3, #104]	@ bOnOff, sg_bDR_EnFlag
.L85:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L87:
	mov	r1, r4	@, bOnOff
	mov	r0, #0	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #1	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L69	@,
.L88:
	mov	r1, r4	@, bOnOff
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L70	@,
.L89:
	mov	r1, r4	@, bOnOff
	mov	r0, #2	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L71	@,
.L90:
	mov	r1, r4	@, bOnOff
	mov	r0, #3	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L72	@,
.L91:
	mov	r1, r4	@, bOnOff
	mov	r0, #4	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L73	@,
.L92:
	mov	r1, r4	@, bOnOff
	mov	r0, #5	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L74	@,
.L93:
	mov	r1, r4	@, bOnOff
	mov	r0, #6	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L75	@,
.L94:
	mov	r1, r4	@, bOnOff
	mov	r0, #7	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L76	@,
.L95:
	mov	r1, r4	@, bOnOff
	mov	r0, #8	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L77	@,
.L96:
	mov	r1, r4	@, bOnOff
	mov	r0, #9	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L78	@,
.L97:
	mov	r1, r4	@, bOnOff
	mov	r0, #10	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L79	@,
.L98:
	mov	r1, r4	@, bOnOff
	mov	r0, #11	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L80	@,
.L99:
	mov	r1, r4	@, bOnOff
	mov	r0, #12	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L81	@,
.L100:
	mov	r1, r4	@, bOnOff
	mov	r0, #13	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L82	@,
.L101:
	mov	r1, r4	@, bOnOff
	mov	r0, #14	@,
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #15	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L83	@,
.L102:
	mov	r0, #15	@,
	mov	r1, r4	@, bOnOff
	bl	PQ_HAL_EnableDR	@
	mov	r5, r0	@ s32Ret,
	b	.L83	@
.L103:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L104	@,
	mov	r3, #205	@,
	movw	ip, #:lower16:.LC1	@ tmp155,
	movt	ip, #:upper16:.LC1	@ tmp155,
	str	ip, [sp, #0]	@ tmp155,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.23282,
	b	.L85	@
.L105:
	.align	2
.L104:
	.word	.LANCHOR1+92
	.fnend
	.size	PQ_MNG_EnableDR, .-PQ_MNG_EnableDR
	.align	2
	.global	PQ_MNG_EnableDB
	.type	PQ_MNG_EnableDB, %function
PQ_MNG_EnableDB:
	.fnstart
.LFB657:
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
	mov	r4, r0	@ bOnOff, bOnOff
	mov	r0, #0	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	mvnne	r5, #0	@ s32Ret,
	beq	.L127	@,
	mov	r0, #1	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L128	@,
.L109:
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L129	@,
.L110:
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L130	@,
.L111:
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L131	@,
.L112:
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L132	@,
.L113:
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L133	@,
.L114:
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L134	@,
.L115:
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L135	@,
.L116:
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L136	@,
.L117:
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L137	@,
.L118:
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L138	@,
.L119:
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L139	@,
.L120:
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L140	@,
.L121:
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L141	@,
.L122:
	mov	r0, #15	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	beq	.L142	@,
.L123:
	cmp	r5, #0	@ s32Ret,
	bne	.L143	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp156,
	movt	r3, #:upper16:.LANCHOR0	@ tmp156,
	mov	r0, r5	@ D.23256, s32Ret
	str	r4, [r3, #116]	@ bOnOff, sg_bDB_EnFlag
.L125:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L127:
	mov	r1, r4	@, bOnOff
	mov	r0, #0	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #1	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L109	@,
.L128:
	mov	r1, r4	@, bOnOff
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L110	@,
.L129:
	mov	r1, r4	@, bOnOff
	mov	r0, #2	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L111	@,
.L130:
	mov	r1, r4	@, bOnOff
	mov	r0, #3	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L112	@,
.L131:
	mov	r1, r4	@, bOnOff
	mov	r0, #4	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L113	@,
.L132:
	mov	r1, r4	@, bOnOff
	mov	r0, #5	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L114	@,
.L133:
	mov	r1, r4	@, bOnOff
	mov	r0, #6	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L115	@,
.L134:
	mov	r1, r4	@, bOnOff
	mov	r0, #7	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L116	@,
.L135:
	mov	r1, r4	@, bOnOff
	mov	r0, #8	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L117	@,
.L136:
	mov	r1, r4	@, bOnOff
	mov	r0, #9	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L118	@,
.L137:
	mov	r1, r4	@, bOnOff
	mov	r0, #10	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L119	@,
.L138:
	mov	r1, r4	@, bOnOff
	mov	r0, #11	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L120	@,
.L139:
	mov	r1, r4	@, bOnOff
	mov	r0, #12	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L121	@,
.L140:
	mov	r1, r4	@, bOnOff
	mov	r0, #13	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L122	@,
.L141:
	mov	r1, r4	@, bOnOff
	mov	r0, #14	@,
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	mov	r0, #15	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #1	@,
	bne	.L123	@,
.L142:
	mov	r0, #15	@,
	mov	r1, r4	@, bOnOff
	bl	PQ_HAL_EnableDB	@
	mov	r5, r0	@ s32Ret,
	b	.L123	@
.L143:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L144	@,
	mov	r3, #150	@,
	movw	ip, #:lower16:.LC2	@ tmp155,
	movt	ip, #:upper16:.LC2	@ tmp155,
	str	ip, [sp, #0]	@ tmp155,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.23256,
	b	.L125	@
.L145:
	.align	2
.L144:
	.word	.LANCHOR1+108
	.fnend
	.size	PQ_MNG_EnableDB, .-PQ_MNG_EnableDB
	.align	2
	.global	PQ_MNG_InitDNR
	.type	PQ_MNG_InitDNR, %function
PQ_MNG_InitDNR:
	.fnstart
.LFB655:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp136,
	movt	r4, #:upper16:.LANCHOR0	@ tmp136,
	ldr	r3, [r4, #108]	@ sg_bDNRInitFlag, sg_bDNRInitFlag
	cmp	r3, #1	@ sg_bDNRInitFlag,
	moveq	r0, #0	@ D.23227,
	beq	.L148	@,
	mov	r5, #0	@ tmp141,
	mov	r1, r4	@, tmp136
	mov	r0, r5	@, tmp141
	mov	ip, #8	@ tmp143,
	str	r5, [r4, #4]	@ tmp141, g_stDnrPara.stPqDnrCtrl.u32Dr_Demo_en
	mov	r2, #16	@ tmp149,
	mov	r5, #1	@ tmp139,
	str	r2, [r4, #76]	@ tmp149, g_stDnrPara.stPqDnrDrFilter.u32Dr_thr_maxsimilarpixdiff
	mov	r3, #64	@ tmp151,
	mov	lr, #40	@ tmp153,
	mov	r2, #4	@ tmp155,
	str	r5, [r4, #0]	@ tmp139, g_stDnrPara.stPqDnrCtrl.u32Dr_en
	str	r5, [r4, #100]	@ tmp139, g_stDnrPara.stPqDnrInfo.u32thr_intl_colcnt
	str	ip, [r4, #72]	@ tmp143, g_stDnrPara.stPqDnrDrFilter.u32Dr_thr_flat3x3zone
	str	r3, [r4, #88]	@ tmp151, g_stDnrPara.stPqDnrInfo.u32thd_cntrst8
	str	lr, [r4, #92]	@ tmp153, g_stDnrPara.stPqDnrInfo.u32thd_maxgrad
	str	r2, [r4, #96]	@ tmp155, g_stDnrPara.stPqDnrInfo.u32thr_intl_cnt
	str	ip, [r4, #84]	@ tmp143, g_stDnrPara.stPqDnrDrFilter.u32Dr_alphascale
	str	ip, [r4, #80]	@ tmp143, g_stDnrPara.stPqDnrDrFilter.u32Dr_betascale
	str	r5, [r4, #104]	@ tmp139, sg_bDR_EnFlag
	bl	PQ_HAL_SetDnrParamRegister	@
	cmp	r0, #0	@ s32Ret
	streq	r5, [r4, #108]	@ tmp139, sg_bDNRInitFlag
	bne	.L151	@,
.L148:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L151:
	mov	r0, r5	@, tmp139
	mov	r1, #41	@,
	ldr	r2, .L152	@,
	mov	r3, #90	@,
	movw	ip, #:lower16:.LC3	@ tmp163,
	movt	ip, #:upper16:.LC3	@ tmp163,
	str	ip, [sp, #0]	@ tmp163,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.23227,
	b	.L148	@
.L153:
	.align	2
.L152:
	.word	.LANCHOR1+124
	.fnend
	.size	PQ_MNG_InitDNR, .-PQ_MNG_InitDNR
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.23312, %object
	.size	__func__.23312, 21
__func__.23312:
	.ascii	"PQ_MNG_GetDRDemoFlag\000"
	.space	3
	.type	__func__.23286, %object
	.size	__func__.23286, 23
__func__.23286:
	.ascii	"PQ_MNG_GetDREnableFlag\000"
	.space	1
	.type	__func__.23260, %object
	.size	__func__.23260, 23
__func__.23260:
	.ascii	"PQ_MNG_GetDBEnableFlag\000"
	.space	1
	.type	__func__.23299, %object
	.size	__func__.23299, 20
__func__.23299:
	.ascii	"PQ_MNG_EnableDRDemo\000"
	.type	__func__.23273, %object
	.size	__func__.23273, 16
__func__.23273:
	.ascii	"PQ_MNG_EnableDR\000"
	.type	__func__.23247, %object
	.size	__func__.23247, 16
__func__.23247:
	.ascii	"PQ_MNG_EnableDB\000"
	.type	__func__.23223, %object
	.size	__func__.23223, 15
__func__.23223:
	.ascii	"PQ_MNG_InitDNR\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"pointer is NULL!\012\000"
	.space	2
.LC1:
	.ascii	"error in mng enable DR!\012\000"
	.space	3
.LC2:
	.ascii	"error in mng enable DB!\012\000"
	.space	3
.LC3:
	.ascii	"Set DNR register error!\012\000"
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_stDnrPara, %object
	.size	g_stDnrPara, 104
g_stDnrPara:
	.space	104
	.type	sg_bDR_EnFlag, %object
	.size	sg_bDR_EnFlag, 4
sg_bDR_EnFlag:
	.space	4
	.type	sg_bDNRInitFlag, %object
	.size	sg_bDNRInitFlag, 4
sg_bDNRInitFlag:
	.space	4
	.type	sg_bDRDemo_EnFlag, %object
	.size	sg_bDRDemo_EnFlag, 4
sg_bDRDemo_EnFlag:
	.space	4
	.type	sg_bDB_EnFlag, %object
	.size	sg_bDB_EnFlag, 4
sg_bDB_EnFlag:
	.space	4
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
