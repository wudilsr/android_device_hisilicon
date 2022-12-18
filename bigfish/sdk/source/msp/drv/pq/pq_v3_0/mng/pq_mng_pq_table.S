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
	.file	"pq_mng_pq_table.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_mng_pq_table)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/mng/.pq_mng_pq_table.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/mng/pq_mng_pq_table.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/mng/pq_mng_pq_table.o -O2 -Wall -Wundef
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
	.global	PQ_MNG_DeInitPQTable
	.type	PQ_MNG_DeInitPQTable, %function
PQ_MNG_DeInitPQTable:
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp134,
	movt	r3, #:upper16:.LANCHOR0	@ tmp134,
	mov	r0, #0	@,
	ldr	r2, [r3, #0]	@ sg_bPqTableInitial, sg_bPqTableInitial
	cmp	r2, #0	@ sg_bPqTableInitial,
	movne	r2, #0	@ tmp137,
	strne	r2, [r3, #0]	@ tmp137, sg_bPqTableInitial
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_DeInitPQTable, .-PQ_MNG_DeInitPQTable
	.align	2
	.global	PQ_MNG_CheckSourceMode
	.type	PQ_MNG_CheckSourceMode, %function
PQ_MNG_CheckSourceMode:
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
	cmp	r1, #720	@ u32Height,
	movcc	r0, #1	@ D.23488,
	ldmccfd	sp, {fp, sp, pc}	@
	cmp	r1, #1920	@ u32Height,
	movls	r0, #2	@ D.23488,
	movhi	r0, #3	@ D.23488,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_CheckSourceMode, .-PQ_MNG_CheckSourceMode
	.align	2
	.global	PQ_MNG_CheckOutputMode
	.type	PQ_MNG_CheckOutputMode, %function
PQ_MNG_CheckOutputMode:
	.fnstart
.LFB657:
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
	cmp	r0, #1	@ bSRState,
	moveq	r0, #3	@,
	movne	r0, #2	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_CheckOutputMode, .-PQ_MNG_CheckOutputMode
	.align	2
	.global	PQ_MNG_UpdatePhyList
	.type	PQ_MNG_UpdatePhyList, %function
PQ_MNG_UpdatePhyList:
	.fnstart
.LFB658:
	@ args = 8, pretend = 0, frame = 0
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
	movw	ip, #:lower16:.LANCHOR0	@ tmp210,
	movt	ip, #:upper16:.LANCHOR0	@ tmp210,
	ldrb	r6, [fp, #4]	@ zero_extendqisi2	@ u8OutputMode, u8OutputMode
	ldr	ip, [ip, #4]	@ sg_pstPhyReg.201, sg_pstPhyReg
	cmp	ip, #0	@ sg_pstPhyReg.201,
	movne	r4, #0	@ i,
	beq	.L29	@,
.L20:
	ldr	r5, [ip, #0]	@ <variable>.u32RegAddr, <variable>.u32RegAddr
	cmp	r5, r0	@ <variable>.u32RegAddr, u32Addr
	bne	.L17	@,
	ldrb	r5, [ip, #4]	@ zero_extendqisi2	@ <variable>.u8Lsb, <variable>.u8Lsb
	cmp	r5, r1	@ <variable>.u8Lsb, u8Lsb
	bne	.L17	@,
	ldrb	r5, [ip, #5]	@ zero_extendqisi2	@ <variable>.u8Msb, <variable>.u8Msb
	cmp	r5, r2	@ <variable>.u8Msb, u8Msb
	bne	.L17	@,
	ldrb	r5, [ip, #6]	@ zero_extendqisi2	@ D.23529, <variable>.u8SourceMode
	cmp	r5, #0	@ D.23529,
	bne	.L30	@,
.L18:
	ldrb	r5, [ip, #7]	@ zero_extendqisi2	@ D.23534, <variable>.u8OutputMode
	cmp	r5, #0	@ D.23534,
	beq	.L19	@,
	cmp	r5, r6	@ D.23534, u8OutputMode
	bne	.L17	@,
.L19:
	ldr	r3, [fp, #8]	@ u32Value, u32Value
	mov	r0, r4	@ D.23515, i
	str	r3, [ip, #12]	@ u32Value, <variable>.u32Value
.L16:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L30:
	cmp	r5, r3	@ D.23529, u8SourceMode
	beq	.L18	@,
.L17:
	add	ip, ip, #16	@ ivtmp.313, ivtmp.313,
	add	r4, r4, #1	@ i, i,
	ldr	r5, [ip, #0]	@ <variable>.u32RegAddr, <variable>.u32RegAddr
	mov	r8, r4	@ tmp217, i
	mov	r7, ip	@ tmp218, ivtmp.313
	cmp	r5, r0	@ <variable>.u32RegAddr, u32Addr
	bne	.L23	@,
	ldrb	r5, [ip, #4]	@ zero_extendqisi2	@ <variable>.u8Lsb, <variable>.u8Lsb
	cmp	r5, r1	@ <variable>.u8Lsb, u8Lsb
	bne	.L23	@,
	ldrb	r5, [ip, #5]	@ zero_extendqisi2	@ <variable>.u8Msb, <variable>.u8Msb
	cmp	r5, r2	@ <variable>.u8Msb, u8Msb
	bne	.L23	@,
	ldrb	r5, [ip, #6]	@ zero_extendqisi2	@ D.23529, <variable>.u8SourceMode
	cmp	r5, #0	@ D.23529,
	bne	.L27	@,
.L24:
	ldrb	r5, [r7, #7]	@ zero_extendqisi2	@ D.23534, <variable>.u8OutputMode
	cmp	r5, #0	@ D.23534,
	beq	.L19	@,
	cmp	r5, r6	@ D.23534, u8OutputMode
	beq	.L19	@,
.L23:
	add	r4, r8, #1	@ i, tmp217,
	add	ip, r7, #16	@ ivtmp.313, tmp218,
	cmp	r4, #552	@ i,
	bne	.L20	@,
	mvn	r0, #0	@ D.23515,
	b	.L16	@
.L27:
	cmp	r5, r3	@ D.23529, u8SourceMode
	beq	.L24	@,
	b	.L23	@
.L29:
	mov	r0, #1	@,
	mov	r1, #41	@,
	movw	r2, #:lower16:.LANCHOR1	@,
	mov	r3, #122	@,
	movt	r2, #:upper16:.LANCHOR1	@,
	movw	lr, #:lower16:.LC0	@ tmp212,
	movt	lr, #:upper16:.LC0	@ tmp212,
	str	lr, [sp, #0]	@ tmp212,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.23515,
	b	.L16	@
	.fnend
	.size	PQ_MNG_UpdatePhyList, .-PQ_MNG_UpdatePhyList
	.align	2
	.global	PQ_MNG_SetVpssReg
	.type	PQ_MNG_SetVpssReg, %function
PQ_MNG_SetVpssReg:
	.fnstart
.LFB660:
	@ args = 0, pretend = 0, frame = 8
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
	mov	r4, #0	@ tmp171,
	mov	r5, r0	@ u32Addr, u32Addr
	mov	r0, r4	@, tmp171
	str	r4, [fp, #-40]	@ tmp171, u32RegValue
	mov	r6, r1	@ u8Lsb, u8Lsb
	mov	r8, r2	@ u8Msb, u8Msb
	mov	r7, r3	@ u32Value, u32Value
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, r4	@,
	mvneq	r4, #0	@ s32Ret.346,
	bne	.L51	@,
.L33:
	mov	r0, #1	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L52	@,
.L35:
	mov	r0, #2	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L53	@,
.L36:
	mov	r0, #3	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L54	@,
.L37:
	mov	r0, #4	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L55	@,
.L38:
	mov	r0, #5	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L56	@,
.L39:
	mov	r0, #6	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L57	@,
.L40:
	mov	r0, #7	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L58	@,
.L41:
	mov	r0, #8	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L59	@,
.L42:
	mov	r0, #9	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L60	@,
.L43:
	mov	r0, #10	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L61	@,
.L44:
	mov	r0, #11	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L62	@,
.L45:
	mov	r0, #12	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L63	@,
.L46:
	mov	r0, #13	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L64	@,
.L47:
	mov	r0, #14	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L65	@,
.L48:
	mov	r0, #15	@,
	bl	PQ_HAL_CheckVpssValid	@
	cmp	r0, #0	@,
	bne	.L66	@,
.L49:
	mov	r0, r4	@, s32Ret.346
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L51:
	sub	sl, fp, #40	@ tmp172,,
	mov	r0, r4	@, tmp171
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp172
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.344,
	bne	.L34	@,
	mov	r0, sl	@, tmp172
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.344
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L33	@
.L66:
	sub	sl, fp, #40	@ tmp202,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp202
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret,
	bne	.L34	@,
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r0, sl	@, tmp202
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L49	@
.L65:
	sub	sl, fp, #40	@ tmp200,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp200
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.387,
	bne	.L34	@,
	mov	r0, sl	@, tmp200
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.387
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L48	@
.L64:
	sub	sl, fp, #40	@ tmp198,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp198
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.384,
	bne	.L34	@,
	mov	r0, sl	@, tmp198
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.384
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L47	@
.L63:
	sub	sl, fp, #40	@ tmp196,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp196
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.381,
	bne	.L34	@,
	mov	r0, sl	@, tmp196
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.381
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L46	@
.L62:
	sub	sl, fp, #40	@ tmp194,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp194
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.378,
	bne	.L34	@,
	mov	r0, sl	@, tmp194
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.378
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L45	@
.L61:
	sub	sl, fp, #40	@ tmp192,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp192
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.375,
	bne	.L34	@,
	mov	r0, sl	@, tmp192
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.375
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L44	@
.L60:
	sub	sl, fp, #40	@ tmp190,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp190
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.372,
	bne	.L34	@,
	mov	r0, sl	@, tmp190
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.372
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L43	@
.L59:
	sub	sl, fp, #40	@ tmp188,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp188
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.369,
	bne	.L34	@,
	mov	r0, sl	@, tmp188
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.369
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L42	@
.L58:
	sub	sl, fp, #40	@ tmp186,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp186
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.366,
	bne	.L34	@,
	mov	r0, sl	@, tmp186
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.366
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L41	@
.L57:
	sub	sl, fp, #40	@ tmp184,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp184
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.363,
	bne	.L34	@,
	mov	r0, sl	@, tmp184
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.363
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L40	@
.L56:
	sub	sl, fp, #40	@ tmp182,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp182
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.360,
	bne	.L34	@,
	mov	r0, sl	@, tmp182
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.360
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L39	@
.L55:
	sub	sl, fp, #40	@ tmp180,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp180
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.357,
	bne	.L34	@,
	mov	r0, sl	@, tmp180
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.357
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L38	@
.L54:
	sub	sl, fp, #40	@ tmp178,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp178
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.354,
	bne	.L34	@,
	mov	r0, sl	@, tmp178
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.354
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L37	@
.L53:
	sub	sl, fp, #40	@ tmp176,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp176
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.351,
	bne	.L34	@,
	mov	r0, sl	@, tmp176
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.351
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L36	@
.L52:
	sub	sl, fp, #40	@ tmp174,,
	mov	r0, #0	@,
	mov	r1, r5	@, u32Addr
	mov	r2, sl	@, tmp174
	bl	PQ_HAL_ReadRegister	@
	subs	r4, r0, #0	@ s32Ret.348,
	bne	.L34	@,
	mov	r0, sl	@, tmp174
	mov	r2, r6	@, u8Lsb
	mov	r3, r7	@, u32Value
	mov	r1, r8	@, u8Msb
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r4	@, s32Ret.348
	mov	r1, r5	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	mov	r4, r0	@ s32Ret.346,
	b	.L35	@
.L34:
	mvn	r4, #0	@ s32Ret.346,
	b	.L49	@
	.fnend
	.size	PQ_MNG_SetVpssReg, .-PQ_MNG_SetVpssReg
	.align	2
	.global	PQ_MNG_SetVdpReg
	.type	PQ_MNG_SetVdpReg, %function
PQ_MNG_SetVdpReg:
	.fnstart
.LFB659:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #16
	sub	sp, sp, #16	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r6, #0	@ tmp141,
	mov	r4, r0	@ u32Addr, u32Addr
	mov	r5, r1	@ u8Lsb, u8Lsb
	mov	r7, r2	@ u8Msb, u8Msb
	mov	r8, r3	@ u32Value, u32Value
	str	r6, [fp, #-40]	@ tmp141, u32RegValue
	bl	PQ_HAL_CheckVdpValid	@
	cmp	r0, #1	@,
	beq	.L73	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L74	@,
	mov	r3, #178	@,
	movw	ip, #:lower16:.LC1	@ tmp147,
	movt	ip, #:upper16:.LC1	@ tmp147,
	str	ip, [sp, #0]	@ tmp147,
	bl	HI_LogOut	@
.L72:
	mvn	r0, #0	@ s32Ret,
.L70:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L73:
	sub	sl, fp, #40	@ tmp142,,
	mov	r0, r6	@, tmp141
	mov	r1, r4	@, u32Addr
	mov	r2, sl	@, tmp142
	bl	PQ_HAL_ReadRegister	@
	subs	r6, r0, #0	@ s32Ret.411,
	bne	.L72	@,
	mov	r2, r5	@, u8Lsb
	mov	r0, sl	@, tmp142
	mov	r1, r7	@, u8Msb
	mov	r3, r8	@, u32Value
	bl	PQ_HAL_SetU32ByBit	@
	mov	r0, r6	@, s32Ret.411
	mov	r1, r4	@, u32Addr
	ldr	r2, [fp, #-40]	@, u32RegValue
	bl	PQ_HAL_WriteRegister	@
	b	.L70	@
.L75:
	.align	2
.L74:
	.word	.LANCHOR1+24
	.fnend
	.size	PQ_MNG_SetVdpReg, .-PQ_MNG_SetVdpReg
	.align	2
	.global	PQ_MNG_LoadPhyList
	.type	PQ_MNG_LoadPhyList, %function
PQ_MNG_LoadPhyList:
	.fnstart
.LFB661:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #68
	sub	sp, sp, #68	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r6, #:lower16:.LANCHOR0	@ tmp163,
	movt	r6, #:upper16:.LANCHOR0	@ tmp163,
	str	r1, [fp, #-60]	@ enSourceMode, %sfp
	mov	r5, r0	@ enRegType, enRegType
	str	r2, [fp, #-68]	@ enOutputMode, %sfp
	ldr	r1, [r6, #4]	@ prephitmp.428, sg_pstPhyReg
	str	r3, [fp, #-64]	@ enModule, %sfp
	cmp	r1, #0	@ prephitmp.428,
	beq	.L113	@,
	cmp	r0, #0	@ enRegType,
	ldrb	r8, [r1, #7]	@ zero_extendqisi2	@ u8OutputMode, <variable>.u8OutputMode
	mvn	r3, #0	@,
	movw	r2, #:lower16:.LC2	@,
	str	r3, [fp, #-76]	@, %sfp
	movt	r2, #:upper16:.LC2	@,
	str	r2, [fp, #-72]	@, %sfp
	ldr	r7, [r1, #0]	@ u32Addr, <variable>.u32RegAddr
	ldr	r3, [r1, #12]	@ u32Value, <variable>.u32Value
	ldr	r9, [r1, #8]	@ u32Module, <variable>.u32Module
	ldrb	sl, [r1, #4]	@ zero_extendqisi2	@ u8Lsb, <variable>.u8Lsb
	ldrb	r2, [r1, #5]	@ zero_extendqisi2	@ u8Msb, <variable>.u8Msb
	ldrb	r4, [r1, #6]	@ zero_extendqisi2	@ u8SourceMode, <variable>.u8SourceMode
	beq	.L114	@,
	cmp	r0, #1	@ enRegType,
	beq	.L115	@,
.L95:
	cmp	r4, #0	@ u8SourceMode,
	beq	.L90	@,
	ldr	r1, [fp, #-60]	@, %sfp
	cmp	r4, r1	@ u8SourceMode,
	beq	.L90	@,
.L92:
	mov	r4, #16	@ ivtmp.451,
	ldr	r2, [r6, #4]	@ prephitmp.428, sg_pstPhyReg
	b	.L86	@
.L120:
	ldr	ip, [fp, #-60]	@, %sfp
	cmp	r7, ip	@ u8SourceMode,
	beq	.L82	@,
.L80:
	add	r4, r4, #16	@ tmp169, ivtmp.451,
	cmp	r4, #8832	@ tmp169,
	beq	.L78	@,
.L123:
	ldr	r8, [r6, #4]	@ prephitmp.428, sg_pstPhyReg
	cmp	r5, #0	@ enRegType,
	add	r0, r8, r4	@ D.23609, prephitmp.428, tmp169
	ldr	sl, [r8, r4]	@ u32Addr, <variable>.u32RegAddr
	ldr	r9, [r0, #12]	@, <variable>.u32Value
	ldrb	r8, [r0, #7]	@ zero_extendqisi2	@ u8OutputMode, <variable>.u8OutputMode
	str	r9, [fp, #-48]	@, %sfp
	ldrb	r1, [r0, #4]	@ zero_extendqisi2	@, <variable>.u8Lsb
	ldr	r9, [r0, #8]	@ u32Module, <variable>.u32Module
	str	r1, [fp, #-52]	@, %sfp
	ldrb	r7, [r0, #5]	@ zero_extendqisi2	@, <variable>.u8Msb
	str	r7, [fp, #-56]	@, %sfp
	ldrb	r7, [r0, #6]	@ zero_extendqisi2	@ u8SourceMode, <variable>.u8SourceMode
	beq	.L116	@,
	cmp	r5, #1	@ enRegType,
	beq	.L117	@,
.L102:
	cmp	r7, #0	@ u8SourceMode,
	beq	.L97	@,
	ldr	ip, [fp, #-60]	@, %sfp
	cmp	r7, ip	@ u8SourceMode,
	beq	.L97	@,
.L99:
	ldr	r2, [r6, #4]	@ prephitmp.428, sg_pstPhyReg
	add	r4, r4, #16	@ ivtmp.451, tmp169,
.L86:
	add	r0, r2, r4	@ D.23609, prephitmp.428, ivtmp.451
	ldr	sl, [r2, r4]	@ u32Addr, <variable>.u32RegAddr
	cmp	r5, #0	@ enRegType,
	ldr	r9, [r0, #12]	@, <variable>.u32Value
	ldrb	r8, [r0, #7]	@ zero_extendqisi2	@ u8OutputMode, <variable>.u8OutputMode
	str	r9, [fp, #-48]	@, %sfp
	ldrb	r1, [r0, #4]	@ zero_extendqisi2	@, <variable>.u8Lsb
	ldr	r9, [r0, #8]	@ u32Module, <variable>.u32Module
	str	r1, [fp, #-52]	@, %sfp
	ldrb	r7, [r0, #5]	@ zero_extendqisi2	@, <variable>.u8Msb
	str	r7, [fp, #-56]	@, %sfp
	ldrb	r7, [r0, #6]	@ zero_extendqisi2	@ u8SourceMode, <variable>.u8SourceMode
	beq	.L118	@,
	cmp	r5, #1	@ enRegType,
	beq	.L119	@,
.L81:
	cmp	r7, #0	@ u8SourceMode,
	bne	.L120	@,
.L82:
	cmp	r8, #0	@ u8OutputMode,
	beq	.L83	@,
	ldr	r3, [fp, #-68]	@, %sfp
	cmp	r8, r3	@ u8OutputMode,
	bne	.L80	@,
.L83:
	ldr	r2, [fp, #-64]	@, %sfp
	tst	r2, r9	@, u32Module
	beq	.L80	@,
	mov	r0, sl	@, u32Addr
	bl	PQ_HAL_IsVpssReg	@
	cmp	r0, #1	@,
	beq	.L121	@,
	mov	r0, sl	@, u32Addr
	bl	PQ_HAL_IsVdpReg	@
	cmp	r0, #1	@,
	beq	.L122	@,
.L85:
	ldr	lr, [fp, #-72]	@, %sfp
	mov	r0, #4	@,
	mov	r1, #41	@,
	ldr	r2, .L128	@,
	movw	r3, #267	@,
	add	r4, r4, #16	@ tmp169, ivtmp.451,
	str	sl, [sp, #4]	@ u32Addr,
	str	r7, [sp, #8]	@ u8SourceMode,
	str	r8, [sp, #12]	@ u8OutputMode,
	str	r9, [sp, #16]	@ u32Module,
	str	lr, [sp, #0]	@,
	bl	HI_LogOut	@
	cmp	r4, #8832	@ tmp169,
	bne	.L123	@,
.L78:
	ldr	r0, [fp, #-76]	@, %sfp
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L90:
	cmp	r8, #0	@ u8OutputMode,
	beq	.L91	@,
	ldr	r0, [fp, #-68]	@, %sfp
	cmp	r8, r0	@ u8OutputMode,
	bne	.L92	@,
.L91:
	ldr	ip, [fp, #-64]	@, %sfp
	tst	ip, r9	@, u32Module
	beq	.L92	@,
	mov	r0, r7	@, u32Addr
	str	r2, [fp, #-80]	@,
	str	r3, [fp, #-84]	@,
	bl	PQ_HAL_IsVpssReg	@
	ldr	r2, [fp, #-80]	@,
	ldr	r3, [fp, #-84]	@,
	cmp	r0, #1	@,
	beq	.L124	@,
	mov	r0, r7	@, u32Addr
	str	r2, [fp, #-80]	@,
	str	r3, [fp, #-84]	@,
	bl	PQ_HAL_IsVdpReg	@
	ldr	r2, [fp, #-80]	@,
	ldr	r3, [fp, #-84]	@,
	cmp	r0, #1	@,
	beq	.L125	@,
.L94:
	str	r4, [sp, #8]	@ u8SourceMode,
	mov	r0, #4	@,
	ldr	r4, [fp, #-72]	@, %sfp
	mov	r1, #41	@,
	ldr	r2, .L128	@,
	movw	r3, #267	@,
	str	r7, [sp, #4]	@ u32Addr,
	str	r8, [sp, #12]	@ u8OutputMode,
	str	r9, [sp, #16]	@ u32Module,
	str	r4, [sp, #0]	@,
	bl	HI_LogOut	@
	b	.L92	@
.L97:
	cmp	r8, #0	@ u8OutputMode,
	beq	.L98	@,
	ldr	r2, [fp, #-68]	@, %sfp
	cmp	r8, r2	@ u8OutputMode,
	bne	.L99	@,
.L98:
	ldr	r3, [fp, #-64]	@, %sfp
	tst	r3, r9	@, u32Module
	beq	.L99	@,
	mov	r0, sl	@, u32Addr
	bl	PQ_HAL_IsVpssReg	@
	cmp	r0, #1	@,
	beq	.L126	@,
	mov	r0, sl	@, u32Addr
	bl	PQ_HAL_IsVdpReg	@
	cmp	r0, #1	@,
	beq	.L127	@,
.L101:
	str	sl, [sp, #4]	@ u32Addr,
	mov	r0, #4	@,
	ldr	sl, [fp, #-72]	@, %sfp
	mov	r1, #41	@,
	ldr	r2, .L128	@,
	movw	r3, #267	@,
	str	r7, [sp, #8]	@ u8SourceMode,
	str	r8, [sp, #12]	@ u8OutputMode,
	str	r9, [sp, #16]	@ u32Module,
	str	sl, [sp, #0]	@,
	bl	HI_LogOut	@
	b	.L99	@
.L118:
	mov	r0, sl	@, u32Addr
	bl	PQ_HAL_IsVpssReg	@
	cmp	r0, #1	@,
	bne	.L80	@,
	b	.L81	@
.L116:
	mov	r0, sl	@, u32Addr
	bl	PQ_HAL_IsVpssReg	@
	cmp	r0, #1	@,
	bne	.L99	@,
	b	.L102	@
.L119:
	mov	r0, sl	@, u32Addr
	bl	PQ_HAL_IsVdpReg	@
	cmp	r0, #1	@,
	bne	.L80	@,
	b	.L81	@
.L117:
	mov	r0, sl	@, u32Addr
	bl	PQ_HAL_IsVdpReg	@
	cmp	r0, #1	@,
	bne	.L99	@,
	b	.L102	@
.L121:
	ldr	r1, [fp, #-52]	@, %sfp
	mov	r0, sl	@, u32Addr
	ldr	r2, [fp, #-56]	@, %sfp
	ldr	r3, [fp, #-48]	@, %sfp
	bl	PQ_MNG_SetVpssReg	@
	str	r0, [fp, #-76]	@, %sfp
	b	.L85	@
.L126:
	ldr	r1, [fp, #-52]	@, %sfp
	mov	r0, sl	@, u32Addr
	ldr	r2, [fp, #-56]	@, %sfp
	ldr	r3, [fp, #-48]	@, %sfp
	bl	PQ_MNG_SetVpssReg	@
	str	r0, [fp, #-76]	@, %sfp
	b	.L101	@
.L122:
	ldr	r1, [fp, #-52]	@, %sfp
	mov	r0, sl	@, u32Addr
	ldr	r2, [fp, #-56]	@, %sfp
	ldr	r3, [fp, #-48]	@, %sfp
	bl	PQ_MNG_SetVdpReg	@
	str	r0, [fp, #-76]	@, %sfp
	b	.L85	@
.L127:
	ldr	r1, [fp, #-52]	@, %sfp
	mov	r0, sl	@, u32Addr
	ldr	r2, [fp, #-56]	@, %sfp
	ldr	r3, [fp, #-48]	@, %sfp
	bl	PQ_MNG_SetVdpReg	@
	str	r0, [fp, #-76]	@, %sfp
	b	.L101	@
.L114:
	mov	r0, r7	@, u32Addr
	str	r2, [fp, #-80]	@,
	str	r3, [fp, #-84]	@,
	bl	PQ_HAL_IsVpssReg	@
	ldr	r2, [fp, #-80]	@,
	ldr	r3, [fp, #-84]	@,
	cmp	r0, #1	@,
	bne	.L92	@,
	b	.L95	@
.L115:
	mov	r0, r7	@, u32Addr
	str	r2, [fp, #-80]	@,
	str	r3, [fp, #-84]	@,
	bl	PQ_HAL_IsVdpReg	@
	ldr	r2, [fp, #-80]	@,
	ldr	r3, [fp, #-84]	@,
	cmp	r0, #1	@,
	bne	.L92	@,
	b	.L95	@
.L124:
	mov	r1, sl	@, u8Lsb
	mov	r0, r7	@, u32Addr
	bl	PQ_MNG_SetVpssReg	@
	str	r0, [fp, #-76]	@, %sfp
	b	.L94	@
.L125:
	mov	r1, sl	@, u8Lsb
	mov	r0, r7	@, u32Addr
	bl	PQ_MNG_SetVdpReg	@
	str	r0, [fp, #-76]	@, %sfp
	b	.L94	@
.L113:
	add	r1, r1, #41	@,,
	mov	r0, #1	@,
	ldr	r2, .L128	@,
	mov	r3, #214	@,
	movw	ip, #:lower16:.LC0	@ tmp156,
	movt	ip, #:upper16:.LC0	@ tmp156,
	str	ip, [sp, #0]	@ tmp156,
	bl	HI_LogOut	@
	mvn	r1, #0	@,
	str	r1, [fp, #-76]	@, %sfp
	b	.L78	@
.L129:
	.align	2
.L128:
	.word	.LANCHOR1+44
	.fnend
	.size	PQ_MNG_LoadPhyList, .-PQ_MNG_LoadPhyList
	.align	2
	.global	PQ_MNG_InitPQTable
	.type	PQ_MNG_InitPQTable, %function
PQ_MNG_InitPQTable:
	.fnstart
.LFB655:
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
	subs	r3, r0, #0	@ pstPqParam, pstPqParam
	beq	.L139	@,
	movw	sl, #:lower16:.LANCHOR0	@ tmp184,
	movt	sl, #:upper16:.LANCHOR0	@ tmp184,
	add	r0, r3, #37888	@ sg_pstPhyReg.197, pstPqParam,
	ldr	r2, [sl, #0]	@ sg_bPqTableInitial, sg_bPqTableInitial
	add	r0, r0, #232	@ sg_pstPhyReg.197, sg_pstPhyReg.197,
	str	r0, [sl, #4]	@ sg_pstPhyReg.197, sg_pstPhyReg
	cmp	r2, #1	@ sg_bPqTableInitial,
	moveq	r0, #0	@ D.23464,
	beq	.L132	@,
	cmp	r1, #1	@ bDefault,
	beq	.L140	@,
.L134:
	mov	r0, #0	@ D.23464,
	mov	ip, #1	@ tmp181,
	str	ip, [sl, #0]	@ tmp181, sg_bPqTableInitial
.L132:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L140:
	mov	r1, #552	@ tmp174,
	str	r1, [r3, #1240]	@ tmp174, <variable>.stPQFileHeader.u32PhyRegNum
	mov	r1, #32768	@,
	ldr	r6, .L141	@ tmp183,
	bl	__memzero	@
	ldr	r5, [sl, #4]	@ pretmp.467, sg_pstPhyReg
	mov	ip, #0	@ ivtmp.487,
.L135:
	add	r3, r6, ip	@ tmp179, tmp183, ivtmp.487
	add	r4, ip, #16	@ tmp186, ivtmp.487,
	add	r7, r5, ip	@ tmp178, pretmp.467, ivtmp.487
	add	r8, r6, r4	@ tmp189, tmp183, tmp186
	ldmia	r3, {r0, r1, r2, r3}	@ tmp179,,,,
	add	ip, r4, #16	@ ivtmp.487, tmp186,
	cmp	ip, #8832	@ ivtmp.487,
	add	r4, r5, r4	@ tmp188, pretmp.467, tmp186
	stmia	r7, {r0, r1, r2, r3}	@ tmp178,,,,
	ldmia	r8, {r0, r1, r2, r3}	@ tmp189,,,,
	stmia	r4, {r0, r1, r2, r3}	@ tmp188,,,,
	bne	.L135	@,
	b	.L134	@
.L139:
	add	r0, r0, #1	@,,
	mov	r1, #41	@,
	ldr	r2, .L141+4	@,
	mov	r3, #59	@,
	movw	ip, #:lower16:.LC0	@ tmp169,
	movt	ip, #:upper16:.LC0	@ tmp169,
	str	ip, [sp, #0]	@ tmp169,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.23464,
	b	.L132	@
.L142:
	.align	2
.L141:
	.word	.LANCHOR1+84
	.word	.LANCHOR1+64
	.fnend
	.size	PQ_MNG_InitPQTable, .-PQ_MNG_InitPQTable
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.23507, %object
	.size	__func__.23507, 21
__func__.23507:
	.ascii	"PQ_MNG_UpdatePhyList\000"
	.space	3
	.type	__func__.23547, %object
	.size	__func__.23547, 17
__func__.23547:
	.ascii	"PQ_MNG_SetVdpReg\000"
	.space	3
	.type	__func__.23597, %object
	.size	__func__.23597, 19
__func__.23597:
	.ascii	"PQ_MNG_LoadPhyList\000"
	.space	1
	.type	__func__.23455, %object
	.size	__func__.23455, 19
__func__.23455:
	.ascii	"PQ_MNG_InitPQTable\000"
	.space	1
	.type	sg_stPhyReg, %object
	.size	sg_stPhyReg, 8832
sg_stPhyReg:
@ u32RegAddr:
	.word	-120909824
@ u8Lsb:
	.byte	29
@ u8Msb:
	.byte	29
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909824
@ u8Lsb:
	.byte	28
@ u8Msb:
	.byte	28
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909820
@ u8Lsb:
	.byte	7
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120909820
@ u8Lsb:
	.byte	6
@ u8Msb:
	.byte	6
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909820
@ u8Lsb:
	.byte	5
@ u8Msb:
	.byte	5
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909820
@ u8Lsb:
	.byte	4
@ u8Msb:
	.byte	4
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120909820
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	2
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909820
@ u8Lsb:
	.byte	1
@ u8Msb:
	.byte	1
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120909820
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	0
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909808
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909808
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120909808
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	30
@ u32RegAddr:
	.word	-120909804
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909804
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120909804
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	30
@ u32RegAddr:
	.word	-120909788
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120909788
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	13
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	5
@ u32RegAddr:
	.word	-120909788
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	5
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	5
@ u32RegAddr:
	.word	-120909792
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	29
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	6
@ u32RegAddr:
	.word	-120909792
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	7
@ u32RegAddr:
	.word	-120909792
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	13
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909792
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	5
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	9
@ u32RegAddr:
	.word	-120909796
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	29
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	11
@ u32RegAddr:
	.word	-120909796
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	12
@ u32RegAddr:
	.word	-120909796
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	13
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	15
@ u32RegAddr:
	.word	-120909796
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	5
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	18
@ u32RegAddr:
	.word	-120909800
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	29
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	27
@ u32RegAddr:
	.word	-120909800
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120909800
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	13
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	24
@ u32RegAddr:
	.word	-120909800
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	5
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	40
@ u32RegAddr:
	.word	-120909768
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909768
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909768
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909768
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909768
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909768
@ u8Lsb:
	.byte	4
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909768
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	3
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909772
@ u8Lsb:
	.byte	28
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909772
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	7
@ u32RegAddr:
	.word	-120909772
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	7
@ u32RegAddr:
	.word	-120909772
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	6
@ u32RegAddr:
	.word	-120909772
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	6
@ u32RegAddr:
	.word	-120909772
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	5
@ u32RegAddr:
	.word	-120909772
@ u8Lsb:
	.byte	4
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	5
@ u32RegAddr:
	.word	-120909772
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	3
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	6
@ u32RegAddr:
	.word	-120909764
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	5000
@ u32RegAddr:
	.word	-120909764
@ u8Lsb:
	.byte	13
@ u8Msb:
	.byte	13
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909764
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	12
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909764
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120909764
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	6
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120909816
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	-320
@ u32RegAddr:
	.word	-120909816
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120909812
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120909760
@ u8Lsb:
	.byte	4
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909760
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	3
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909760
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909756
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909756
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	-2
@ u32RegAddr:
	.word	-120909756
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909756
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909748
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909748
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	22
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120909748
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909748
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909752
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909752
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	208
@ u32RegAddr:
	.word	-120909752
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	144
@ u32RegAddr:
	.word	-120909752
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120909744
@ u8Lsb:
	.byte	18
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909744
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	17
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909744
@ u8Lsb:
	.byte	6
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120909744
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	5
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120909740
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909740
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	22
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909740
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	14
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909740
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	6
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	48
@ u32RegAddr:
	.word	-120909744
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120909736
@ u8Lsb:
	.byte	21
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909736
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	20
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909736
@ u8Lsb:
	.byte	19
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120909736
@ u8Lsb:
	.byte	18
@ u8Msb:
	.byte	18
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120909736
@ u8Lsb:
	.byte	17
@ u8Msb:
	.byte	17
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909736
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	16
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120909736
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	13
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909736
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909736
@ u8Lsb:
	.byte	4
@ u8Msb:
	.byte	6
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120909736
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	2
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120909732
@ u8Lsb:
	.byte	26
@ u8Msb:
	.byte	26
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909732
@ u8Lsb:
	.byte	25
@ u8Msb:
	.byte	25
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909732
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	24
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120909732
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909732
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909732
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909724
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	16
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909724
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	12
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	30
@ u32RegAddr:
	.word	-120909724
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	6
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909728
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	160
@ u32RegAddr:
	.word	-120909728
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	10
@ u32RegAddr:
	.word	-120909728
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	15
@ u32RegAddr:
	.word	-120909728
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909716
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909716
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	22
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909716
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909716
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909720
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909720
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909720
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	72
@ u32RegAddr:
	.word	-120909720
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909712
@ u8Lsb:
	.byte	18
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909712
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	17
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909712
@ u8Lsb:
	.byte	6
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909712
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	5
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909708
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909708
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	22
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909708
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	14
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909708
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	6
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909712
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909700
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909700
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	22
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909700
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909700
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909704
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909704
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120909704
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	72
@ u32RegAddr:
	.word	-120909704
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909696
@ u8Lsb:
	.byte	18
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909696
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	17
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909696
@ u8Lsb:
	.byte	6
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909696
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	5
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909692
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909692
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	22
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909692
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	14
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909692
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	6
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909696
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909688
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120909688
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	13
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909688
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120909680
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	25
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120909680
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120909684
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	25
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120909684
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120909676
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120909676
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	29
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120909676
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909676
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120909672
@ u8Lsb:
	.byte	23
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909672
@ u8Lsb:
	.byte	14
@ u8Msb:
	.byte	22
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120909672
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	13
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	6
@ u32RegAddr:
	.word	-120909672
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	1
@ u32Value:
	.word	192
@ u32RegAddr:
	.word	-120909488
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909488
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120909488
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	2
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	6
@ u32RegAddr:
	.word	-120909500
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909500
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120909500
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120909480
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909480
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909484
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	30
@ u32RegAddr:
	.word	-120909484
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909496
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	20
@ u32RegAddr:
	.word	-120909496
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	50
@ u32RegAddr:
	.word	-120909496
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	20
@ u32RegAddr:
	.word	-120909472
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120909472
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120909472
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	90
@ u32RegAddr:
	.word	-120909468
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120909464
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120909464
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909464
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120909464
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120909460
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120909460
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120909460
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909460
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120909476
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120909476
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120909476
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120909488
@ u8Lsb:
	.byte	19
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909456
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	20
@ u32RegAddr:
	.word	-120909456
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	15
@ u32RegAddr:
	.word	-120909456
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120909452
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909452
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909448
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909448
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909448
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909448
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909444
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120909444
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	2
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	180
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	127
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-19
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-8
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-2
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-1
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-1
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120913524
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	50
@ u32RegAddr:
	.word	-120913524
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	51
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	256
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	127
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-21
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-21
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-11
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	180
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	127
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-19
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-8
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-2
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-1
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-1
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120913524
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	50
@ u32RegAddr:
	.word	-120913524
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	51
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	256
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	127
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-21
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-21
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-11
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	180
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	127
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-19
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-8
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-2
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-1
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-1
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120913524
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	50
@ u32RegAddr:
	.word	-120913524
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	51
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	256
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	127
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-21
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-21
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	-11
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	2
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	180
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	127
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-19
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-8
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-2
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-1
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-1
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120913524
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	50
@ u32RegAddr:
	.word	-120913524
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	51
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	256
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	127
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-21
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-21
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-11
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	180
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	127
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-19
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-8
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-2
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-1
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-1
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120913524
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	50
@ u32RegAddr:
	.word	-120913524
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	51
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	256
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	127
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-21
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-21
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-11
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	180
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	127
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-19
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-8
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-2
@ u32RegAddr:
	.word	-120913532
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-1
@ u32RegAddr:
	.word	-120913536
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-1
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120913528
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	3
@ u32RegAddr:
	.word	-120913524
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	50
@ u32RegAddr:
	.word	-120913524
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	51
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913520
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	256
@ u32RegAddr:
	.word	-120913516
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	127
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-21
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-21
@ u32RegAddr:
	.word	-120913512
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	-11
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913508
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	3
@ u32Module:
	.word	4
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913920
@ u8Lsb:
	.byte	11
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	8
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120913476
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	24
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	8
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120913480
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	28
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	8
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120913480
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	20
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	8
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120913476
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	20
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	8
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120913476
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	4
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	8
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120913460
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	8
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120913460
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	8
@ u32Value:
	.word	40
@ u32RegAddr:
	.word	-120913460
@ u8Lsb:
	.byte	4
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	8
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120913460
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	3
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	8
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	28
@ u8Msb:
	.byte	28
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	27
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	26
@ u8Msb:
	.byte	26
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	25
@ u8Msb:
	.byte	25
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	24
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	23
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	22
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	19
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	18
@ u8Msb:
	.byte	18
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831744
@ u8Lsb:
	.byte	17
@ u8Msb:
	.byte	17
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831732
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	64
@ u32RegAddr:
	.word	-120831732
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831732
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831728
@ u8Lsb:
	.byte	23
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831724
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831724
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831724
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831720
@ u8Lsb:
	.byte	26
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	18
@ u32RegAddr:
	.word	-120831720
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	25
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	18
@ u32RegAddr:
	.word	-120831720
@ u8Lsb:
	.byte	14
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	18
@ u32RegAddr:
	.word	-120831720
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	13
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120831720
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	17
@ u32RegAddr:
	.word	-120831716
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	50
@ u32RegAddr:
	.word	-120831716
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	60
@ u32RegAddr:
	.word	-120831716
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	70
@ u32RegAddr:
	.word	-120831712
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831712
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120831708
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831708
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120831704
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831704
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	255
@ u32RegAddr:
	.word	-120831700
@ u8Lsb:
	.byte	26
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120831700
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	25
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120831700
@ u8Lsb:
	.byte	14
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	32
@ u32RegAddr:
	.word	-120831700
@ u8Lsb:
	.byte	26
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	42
@ u32RegAddr:
	.word	-120831700
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	25
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	42
@ u32RegAddr:
	.word	-120831700
@ u8Lsb:
	.byte	14
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	42
@ u32RegAddr:
	.word	-120831700
@ u8Lsb:
	.byte	26
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	48
@ u32RegAddr:
	.word	-120831700
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	25
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	48
@ u32RegAddr:
	.word	-120831700
@ u8Lsb:
	.byte	14
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	42
@ u32RegAddr:
	.word	-120831696
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	20
@ u32RegAddr:
	.word	-120831696
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	30
@ u32RegAddr:
	.word	-120831696
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	40
@ u32RegAddr:
	.word	-120831696
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	50
@ u32RegAddr:
	.word	-120831692
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	60
@ u32RegAddr:
	.word	-120831692
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	70
@ u32RegAddr:
	.word	-120831692
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	115
@ u32RegAddr:
	.word	-120831688
@ u8Lsb:
	.byte	28
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831688
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120831688
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120831688
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	6
@ u32RegAddr:
	.word	-120831688
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	7
@ u32RegAddr:
	.word	-120831688
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120831688
@ u8Lsb:
	.byte	4
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	9
@ u32RegAddr:
	.word	-120831688
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	3
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	10
@ u32RegAddr:
	.word	-120831684
@ u8Lsb:
	.byte	28
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	10
@ u32RegAddr:
	.word	-120831680
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	25
@ u32RegAddr:
	.word	-120831680
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	51
@ u32RegAddr:
	.word	-120831680
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	51
@ u32RegAddr:
	.word	-120831676
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	25
@ u32RegAddr:
	.word	-120831676
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	25
@ u32RegAddr:
	.word	-120831676
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	25
@ u32RegAddr:
	.word	-120831672
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	5
@ u32RegAddr:
	.word	-120831672
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831668
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	30
@ u32RegAddr:
	.word	-120831668
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	50
@ u32RegAddr:
	.word	-120831668
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	70
@ u32RegAddr:
	.word	-120831668
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	90
@ u32RegAddr:
	.word	-120831664
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	130
@ u32RegAddr:
	.word	-120831664
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	150
@ u32RegAddr:
	.word	-120831664
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	170
@ u32RegAddr:
	.word	-120831660
@ u8Lsb:
	.byte	28
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831660
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120831660
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	23
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120831660
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120831660
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120831660
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120831660
@ u8Lsb:
	.byte	4
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120831660
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	3
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120831656
@ u8Lsb:
	.byte	28
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	2
@ u32RegAddr:
	.word	-120831652
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120831652
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	12
@ u32RegAddr:
	.word	-120831652
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831648
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831648
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831648
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831644
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831644
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831640
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831640
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831640
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831636
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	-16
@ u32RegAddr:
	.word	-120831636
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	-30
@ u32RegAddr:
	.word	-120831636
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	-41
@ u32RegAddr:
	.word	-120831632
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	-49
@ u32RegAddr:
	.word	-120831632
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	-45
@ u32RegAddr:
	.word	-120831632
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	-38
@ u32RegAddr:
	.word	-120831628
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	-32
@ u32RegAddr:
	.word	-120831628
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	-26
@ u32RegAddr:
	.word	-120831628
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	-12
@ u32RegAddr:
	.word	-120831624
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	-6
@ u32RegAddr:
	.word	-120831624
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	13
@ u32RegAddr:
	.word	-120831624
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	28
@ u32RegAddr:
	.word	-120831620
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	38
@ u32RegAddr:
	.word	-120831620
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	53
@ u32RegAddr:
	.word	-120831620
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	62
@ u32RegAddr:
	.word	-120831616
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	69
@ u32RegAddr:
	.word	-120831616
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	70
@ u32RegAddr:
	.word	-120831616
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	72
@ u32RegAddr:
	.word	-120831612
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	73
@ u32RegAddr:
	.word	-120831612
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	70
@ u32RegAddr:
	.word	-120831612
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	66
@ u32RegAddr:
	.word	-120831608
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	58
@ u32RegAddr:
	.word	-120831608
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	52
@ u32RegAddr:
	.word	-120831608
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	44
@ u32RegAddr:
	.word	-120831604
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	34
@ u32RegAddr:
	.word	-120831604
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	10
@ u32RegAddr:
	.word	-120831604
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831600
@ u8Lsb:
	.byte	22
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831600
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	21
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831600
@ u8Lsb:
	.byte	2
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	16
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831584
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120831584
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831584
@ u8Lsb:
	.byte	29
@ u8Msb:
	.byte	29
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120831584
@ u8Lsb:
	.byte	28
@ u8Msb:
	.byte	28
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120831584
@ u8Lsb:
	.byte	27
@ u8Msb:
	.byte	27
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831584
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120831580
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	29
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	112
@ u32RegAddr:
	.word	-120831580
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	112
@ u32RegAddr:
	.word	-120831580
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	112
@ u32RegAddr:
	.word	-120831580
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	29
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	112
@ u32RegAddr:
	.word	-120831580
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	112
@ u32RegAddr:
	.word	-120831580
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	112
@ u32RegAddr:
	.word	-120831580
@ u8Lsb:
	.byte	20
@ u8Msb:
	.byte	29
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	112
@ u32RegAddr:
	.word	-120831580
@ u8Lsb:
	.byte	10
@ u8Msb:
	.byte	19
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	112
@ u32RegAddr:
	.word	-120831580
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	32
@ u32Value:
	.word	112
@ u32RegAddr:
	.word	-120844928
@ u8Lsb:
	.byte	29
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120844908
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120844908
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120844908
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120844904
@ u8Lsb:
	.byte	28
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120844904
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	25
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120844924
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	5
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	14
@ u32RegAddr:
	.word	-120844920
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120844920
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	22
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120844920
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	10
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	-48
@ u32RegAddr:
	.word	-120844916
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120844912
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120844904
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	80
@ u32RegAddr:
	.word	-120844904
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	80
@ u32RegAddr:
	.word	-120844900
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120844900
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120844900
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	1
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	140
@ u32RegAddr:
	.word	-120844928
@ u8Lsb:
	.byte	29
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120844908
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120844908
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120844908
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120844904
@ u8Lsb:
	.byte	28
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120844904
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	25
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	80
@ u32RegAddr:
	.word	-120844924
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	5
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	14
@ u32RegAddr:
	.word	-120844920
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120844920
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	22
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120844920
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	10
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	-48
@ u32RegAddr:
	.word	-120844916
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120844912
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120844904
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	80
@ u32RegAddr:
	.word	-120844904
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	80
@ u32RegAddr:
	.word	-120844900
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120844900
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120844900
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	2
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	140
@ u32RegAddr:
	.word	-120844928
@ u8Lsb:
	.byte	29
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120844908
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120844908
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120844908
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	128
@ u32RegAddr:
	.word	-120844904
@ u8Lsb:
	.byte	28
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120844904
@ u8Lsb:
	.byte	16
@ u8Msb:
	.byte	25
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	80
@ u32RegAddr:
	.word	-120844924
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	5
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	14
@ u32RegAddr:
	.word	-120844920
@ u8Lsb:
	.byte	24
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	4
@ u32RegAddr:
	.word	-120844920
@ u8Lsb:
	.byte	12
@ u8Msb:
	.byte	22
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	16
@ u32RegAddr:
	.word	-120844920
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	10
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	-48
@ u32RegAddr:
	.word	-120844916
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	8
@ u32RegAddr:
	.word	-120844912
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	11
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	0
@ u32RegAddr:
	.word	-120844904
@ u8Lsb:
	.byte	8
@ u8Msb:
	.byte	15
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	80
@ u32RegAddr:
	.word	-120844904
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	7
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	80
@ u32RegAddr:
	.word	-120844900
@ u8Lsb:
	.byte	31
@ u8Msb:
	.byte	31
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120844900
@ u8Lsb:
	.byte	30
@ u8Msb:
	.byte	30
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	1
@ u32RegAddr:
	.word	-120844900
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	9
@ u8SourceMode:
	.byte	3
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	256
@ u32Value:
	.word	140
@ u32RegAddr:
	.word	-131071
@ u8Lsb:
	.byte	0
@ u8Msb:
	.byte	1
@ u8SourceMode:
	.byte	0
@ u8OutputMode:
	.byte	0
@ u32Module:
	.word	0
@ u32Value:
	.word	0
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"pointer is NULL!\012\000"
	.space	2
.LC1:
	.ascii	"PQ_HAL_CheckVdpValid false\012\000"
.LC2:
	.ascii	"Load u32Addr:0x%x, SourceMode:%d, u8OutputMode:%d, "
	.ascii	"Module:%d\012\000"
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	sg_bPqTableInitial, %object
	.size	sg_bPqTableInitial, 4
sg_bPqTableInitial:
	.space	4
	.type	sg_pstPhyReg, %object
	.size	sg_pstPhyReg, 4
sg_pstPhyReg:
	.space	4
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
