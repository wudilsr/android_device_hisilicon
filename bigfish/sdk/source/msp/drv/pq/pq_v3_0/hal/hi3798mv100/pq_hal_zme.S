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
	.file	"pq_hal_zme.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_hal_zme)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/hal/hi3798mv100/.pq_hal_zme.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_zme.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_zme.o -O2 -Wall -Wundef
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
	.global	VDP_VID_SetZmeVchTap
	.type	VDP_VID_SetZmeVchTap, %function
VDP_VID_SetZmeVchTap:
	.fnstart
.LFB663:
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
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeVchTap, .-VDP_VID_SetZmeVchTap
	.align	2
	.global	VDP_WBC_SetZmeVerTap
	.type	VDP_WBC_SetZmeVerTap, %function
VDP_WBC_SetZmeVerTap:
	.fnstart
.LFB679:
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
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDP_WBC_SetZmeVerTap, .-VDP_WBC_SetZmeVerTap
	.align	2
	.global	VDP_SR_SetZmeVerTap
	.type	VDP_SR_SetZmeVerTap, %function
VDP_SR_SetZmeVerTap:
	.fnstart
.LFB693:
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
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VDP_SR_SetZmeVerTap, .-VDP_SR_SetZmeVerTap
	.align	2
	.global	VPSS_REG_SetZmeCoefAddr
	.type	VPSS_REG_SetZmeCoefAddr, %function
VPSS_REG_SetZmeCoefAddr:
	.fnstart
.LFB706:
	@ args = 4, pretend = 0, frame = 0
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
	cmp	r1, #2	@ ePort,
	ldr	r0, [fp, #4]	@ u32Addr, u32Addr
	beq	.L10	@,
	cmp	r1, #3	@ ePort,
	beq	.L11	@,
	cmp	r1, #0	@ ePort,
	bne	.L23	@,
	cmp	r3, #3	@ eMode,
	streq	r0, [r2, #536]	@ u32Addr, <variable>.VPSS_VHD_ZME_CHADDR.bits.vhd_scl_ch
	beq	.L13	@,
	cmp	r3, #2	@ eMode,
	streq	r0, [r2, #528]	@ u32Addr, <variable>.VPSS_VHD_ZME_LHADDR.bits.vhd_scl_lh
	beq	.L13	@,
	cmp	r3, #5	@ eMode,
	streq	r0, [r2, #540]	@ u32Addr, <variable>.VPSS_VHD_ZME_CVADDR.bits.vhd_scl_cv
	beq	.L13	@,
	cmp	r3, #4	@ eMode,
	streq	r0, [r2, #532]	@ u32Addr, <variable>.VPSS_VHD_ZME_LVADDR.bits.vhd_scl_lv
	beq	.L13	@,
.L23:
	movw	r0, #:lower16:.LC0	@,
	movt	r0, #:upper16:.LC0	@,
	bl	printk	@
.L13:
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.L11:
	cmp	r3, #3	@ eMode,
	streq	r0, [r2, #584]	@ u32Addr, <variable>.VPSS_HSCL_CADDR.bits.hscl_caddr
	beq	.L13	@,
	cmp	r3, #2	@ eMode,
	streq	r0, [r2, #580]	@ u32Addr, <variable>.VPSS_HSCL_LADDR.bits.hscl_laddr
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.L10:
	cmp	r3, #3	@ eMode,
	streq	r0, [r2, #552]	@ u32Addr, <variable>.VPSS_STR_ZME_CHADDR.bits.str_scl_ch
	beq	.L13	@,
	cmp	r3, #2	@ eMode,
	streq	r0, [r2, #544]	@ u32Addr, <variable>.VPSS_STR_ZME_LHADDR.bits.str_scl_lh
	beq	.L13	@,
	cmp	r3, #5	@ eMode,
	streq	r0, [r2, #556]	@ u32Addr, <variable>.VPSS_STR_ZME_CVADDR.bits.str_scl_cv
	beq	.L13	@,
	cmp	r3, #4	@ eMode,
	streq	r0, [r2, #548]	@ u32Addr, <variable>.VPSS_STR_ZME_LVADDR.bits.str_scl_lv
	bne	.L23	@,
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VPSS_REG_SetZmeCoefAddr, .-VPSS_REG_SetZmeCoefAddr
	.align	2
	.global	VPSS_REG_SetZmeOutFmt
	.type	VPSS_REG_SetZmeOutFmt, %function
VPSS_REG_SetZmeOutFmt:
	.fnstart
.LFB705:
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
	sub	r3, r3, #29	@ tmp140, eFormat,
	cmp	r3, #72	@ tmp140,
	ldrls	pc, [pc, r3, asl #2]	@ tmp140
	b	.L27	@
.L30:
	.word	.L28
	.word	.L28
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L28
	.word	.L27
	.word	.L28
	.word	.L28
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L29
	.word	.L29
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L28
	.word	.L28
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L27
	.word	.L29
	.word	.L29
	.word	.L27
	.word	.L27
	.word	.L28
	.word	.L28
	.word	.L27
	.word	.L27
	.word	.L29
	.word	.L29
	.word	.L27
	.word	.L29
	.word	.L29
.L29:
	cmp	r1, #2	@ ePort,
	mov	r3, #1	@ u32Format,
	beq	.L35	@,
.L40:
	cmp	r1, #3	@ ePort,
	moveq	r0, #0	@ D.25663,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r1, #0	@ ePort,
	bne	.L39	@,
	ldrb	ip, [r2, #366]	@ zero_extendqisi2	@,
	mov	r0, r1	@ D.25663, ePort
	bfi	ip, r3, #5, #2	@ tmp142, u32Format,,
	strb	ip, [r2, #366]	@ tmp142,
	ldmfd	sp, {fp, sp, pc}	@
.L28:
	cmp	r1, #2	@ ePort,
	mov	r3, #0	@ u32Format,
	bne	.L40	@,
.L35:
	ldrb	r1, [r2, #430]	@ zero_extendqisi2	@,
	mov	r0, #0	@ D.25663,
	bfi	r1, r3, #5, #2	@ tmp144, u32Format,,
	strb	r1, [r2, #430]	@ tmp144,
	ldmfd	sp, {fp, sp, pc}	@
.L27:
	movw	r0, #:lower16:.LC1	@,
	movt	r0, #:upper16:.LC1	@,
	bl	printk	@
	mvn	r0, #0	@ D.25663,
	ldmfd	sp, {fp, sp, pc}	@
.L39:
	movw	r0, #:lower16:.LC1	@,
	movt	r0, #:upper16:.LC1	@,
	bl	printk	@
	mov	r0, #0	@ D.25663,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VPSS_REG_SetZmeOutFmt, .-VPSS_REG_SetZmeOutFmt
	.align	2
	.global	VPSS_REG_SetZmeInFmt
	.type	VPSS_REG_SetZmeInFmt, %function
VPSS_REG_SetZmeInFmt:
	.fnstart
.LFB704:
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
	sub	r3, r3, #44	@ tmp140, eFormat,
	cmp	r3, #64	@ tmp140,
	ldrls	pc, [pc, r3, asl #2]	@ tmp140
	b	.L42	@
.L45:
	.word	.L43
	.word	.L42
	.word	.L43
	.word	.L43
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L44
	.word	.L44
	.word	.L42
	.word	.L44
	.word	.L44
	.word	.L43
	.word	.L43
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L42
	.word	.L44
	.word	.L44
	.word	.L42
	.word	.L44
	.word	.L44
	.word	.L44
	.word	.L44
	.word	.L44
	.word	.L43
	.word	.L44
	.word	.L43
	.word	.L43
.L44:
	mov	r3, #1	@ u32Format,
.L46:
	cmp	r1, #2	@ ePort,
	beq	.L49	@,
	cmp	r1, #3	@ ePort,
	moveq	r0, #0	@ D.25629,
	ldmeqfd	sp, {fp, sp, pc}	@
	cmp	r1, #0	@ ePort,
	bne	.L53	@,
.L49:
	ldrb	r1, [r2, #366]	@ zero_extendqisi2	@,
	mov	r0, #0	@ D.25629,
	bfi	r1, r3, #3, #2	@ tmp142, u32Format,,
	strb	r1, [r2, #366]	@ tmp142,
	ldmfd	sp, {fp, sp, pc}	@
.L43:
	mov	r3, #0	@ u32Format,
	b	.L46	@
.L42:
	movw	r0, #:lower16:.LC2	@,
	movt	r0, #:upper16:.LC2	@,
	bl	printk	@
	mvn	r0, #0	@ D.25629,
	ldmfd	sp, {fp, sp, pc}	@
.L53:
	movw	r0, #:lower16:.LC2	@,
	movt	r0, #:upper16:.LC2	@,
	bl	printk	@
	mov	r0, #0	@ D.25629,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VPSS_REG_SetZmeInFmt, .-VPSS_REG_SetZmeInFmt
	.align	2
	.global	VPSS_REG_SetZmeHfirOrder
	.type	VPSS_REG_SetZmeHfirOrder, %function
VPSS_REG_SetZmeHfirOrder:
	.fnstart
.LFB703:
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
	cmp	r1, #3	@ ePort,
	bls	.L59	@,
.L55:
	movw	r0, #:lower16:.LC3	@,
	movt	r0, #:upper16:.LC3	@,
	bl	printk	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.L59:
	mov	r3, #1	@ tmp139,
	mov	r1, r3, asl r1	@ tmp138, tmp139,
	tst	r1, #13	@ tmp138,
	beq	.L55	@,
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VPSS_REG_SetZmeHfirOrder, .-VPSS_REG_SetZmeHfirOrder
	.align	2
	.global	VPSS_REG_SetZmeRatio
	.type	VPSS_REG_SetZmeRatio, %function
VPSS_REG_SetZmeRatio:
	.fnstart
.LFB702:
	@ args = 4, pretend = 0, frame = 0
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
	cmp	r1, #2	@ ePort,
	ldr	r0, [fp, #4]	@ u32Ratio, u32Ratio
	beq	.L63	@,
	cmp	r1, #3	@ ePort,
	beq	.L64	@,
	cmp	r1, #0	@ ePort,
	beq	.L71	@,
	movw	r0, #:lower16:.LC4	@,
	movt	r0, #:upper16:.LC4	@,
	bl	printk	@
.L66:
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.L71:
	cmp	r3, #0	@ eMode,
	ldreq	r3, [r2, #352]	@ tmp139,
	movne	r3, #368	@ tmp140,
	strneh	r0, [r2, r3]	@ movhi	@ u32Ratio,
	bfieq	r3, r0, #0, #24	@ tmp139, u32Ratio,,
	mov	r0, #0	@,
	streq	r3, [r2, #352]	@ tmp139,
	ldmfd	sp, {fp, sp, pc}	@
.L64:
	cmp	r3, #2	@ eMode,
	cmpne	r3, #0	@, eMode,
	beq	.L68	@,
	cmp	r3, #6	@ eMode,
	bne	.L66	@,
.L68:
	ldr	r3, [r2, #748]	@ tmp150,
	bfi	r3, r0, #0, #24	@ tmp150, u32Ratio,,
	mov	r0, #0	@,
	str	r3, [r2, #748]	@ tmp150,
	ldmfd	sp, {fp, sp, pc}	@
.L63:
	cmp	r3, #0	@ eMode,
	ldreq	r3, [r2, #416]	@ tmp141,
	movne	r3, #428	@ tmp142,
	strneh	r0, [r2, r3]	@ movhi	@ u32Ratio,
	bfieq	r3, r0, #0, #24	@ tmp141, u32Ratio,,
	mov	r0, #0	@,
	streq	r3, [r2, #416]	@ tmp141,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VPSS_REG_SetZmeRatio, .-VPSS_REG_SetZmeRatio
	.align	2
	.global	VPSS_REG_SetZmePhase
	.type	VPSS_REG_SetZmePhase, %function
VPSS_REG_SetZmePhase:
	.fnstart
.LFB701:
	@ args = 4, pretend = 0, frame = 0
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
	cmp	r1, #2	@ ePort,
	ldr	r0, [fp, #4]	@ s32Phase, s32Phase
	beq	.L75	@,
	cmp	r1, #3	@ ePort,
	beq	.L76	@,
	cmp	r1, #0	@ ePort,
	bne	.L90	@,
	cmp	r3, #3	@ eMode,
	beq	.L92	@,
	cmp	r3, #2	@ eMode,
	beq	.L93	@,
	cmp	r3, #5	@ eMode,
	moveq	r3, #372	@ tmp142,
	streqh	r0, [r2, r3]	@ movhi	@ s32Phase,
	beq	.L78	@,
	cmp	r3, #4	@ eMode,
	movweq	r3, #374	@ tmp143,
	streqh	r0, [r2, r3]	@ movhi	@ s32Phase,
	beq	.L78	@,
.L90:
	movw	r0, #:lower16:.LC5	@,
	movt	r0, #:upper16:.LC5	@,
	bl	printk	@
.L78:
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.L76:
	rsbs	r1, r3, #1	@ D.25547, eMode
	movcc	r1, #0	@ D.25547
	cmp	r3, #0	@ eMode,
	cmpne	r3, #2	@, eMode,
	bne	.L94	@,
.L86:
	ldr	ip, [r2, #756]	@ tmp157,
	bfi	ip, r0, #0, #28	@ tmp157, s32Phase,,
	str	ip, [r2, #756]	@ tmp157,
.L87:
	cmp	r3, #3	@ eMode,
	orreq	r1, r1, #1	@,, tmp162, D.25547
	cmp	r1, #0	@ tmp162,
	bne	.L88	@,
	cmp	r3, #6	@ eMode,
	bne	.L78	@,
.L88:
	ldr	r1, [r2, #760]	@ tmp163,
	bfi	r1, r0, #0, #28	@ tmp163, s32Phase,,
	mov	r0, #0	@,
	str	r1, [r2, #760]	@ tmp163,
	ldmfd	sp, {fp, sp, pc}	@
.L75:
	cmp	r3, #3	@ eMode,
	beq	.L95	@,
	cmp	r3, #2	@ eMode,
	beq	.L96	@,
	cmp	r3, #5	@ eMode,
	moveq	r3, #432	@ tmp147,
	streqh	r0, [r2, r3]	@ movhi	@ s32Phase,
	beq	.L78	@,
	cmp	r3, #4	@ eMode,
	movweq	r3, #434	@ tmp148,
	streqh	r0, [r2, r3]	@ movhi	@ s32Phase,
	bne	.L90	@,
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.L94:
	cmp	r3, #6	@ eMode,
	bne	.L87	@,
	b	.L86	@
.L96:
	ldr	r3, [r2, #420]	@ tmp146,
	bfi	r3, r0, #0, #28	@ tmp146, s32Phase,,
	str	r3, [r2, #420]	@ tmp146,
	b	.L78	@
.L93:
	ldr	r1, [r2, #356]	@ tmp141,
	bfi	r1, r0, #0, #28	@ tmp141, s32Phase,,
	str	r1, [r2, #356]	@ tmp141,
	b	.L78	@
.L92:
	ldr	r3, [r2, #360]	@ tmp140,
	bfi	r3, r0, #0, #28	@ tmp140, s32Phase,,
	str	r3, [r2, #360]	@ tmp140,
	b	.L78	@
.L95:
	ldr	ip, [r2, #424]	@ tmp145,
	bfi	ip, r0, #0, #28	@ tmp145, s32Phase,,
	str	ip, [r2, #424]	@ tmp145,
	b	.L78	@
	.fnend
	.size	VPSS_REG_SetZmePhase, .-VPSS_REG_SetZmePhase
	.align	2
	.global	VPSS_REG_SetZmeMidEnable
	.type	VPSS_REG_SetZmeMidEnable, %function
VPSS_REG_SetZmeMidEnable:
	.fnstart
.LFB700:
	@ args = 4, pretend = 0, frame = 0
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
	cmp	r1, #2	@ ePort,
	ldr	r0, [fp, #4]	@ bEnable, bEnable
	beq	.L100	@,
	cmp	r1, #3	@ ePort,
	beq	.L101	@,
	cmp	r1, #0	@ ePort,
	beq	.L122	@,
	movw	r0, #:lower16:.LC6	@,
	movt	r0, #:upper16:.LC6	@,
	bl	printk	@
.L109:
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.L122:
	rsbs	r1, r3, #1	@ D.25465, eMode
	movcc	r1, #0	@ D.25465
	cmp	r3, #0	@ eMode,
	cmpne	r3, #2	@, eMode,
	bne	.L123	@,
.L102:
	ldrb	ip, [r2, #355]	@ zero_extendqisi2	@,
	bfi	ip, r0, #5, #1	@ tmp151, bEnable,,
	strb	ip, [r2, #355]	@ tmp151,
.L103:
	cmp	r3, #3	@ eMode,
	orreq	r1, r1, #1	@,, tmp157, D.25465
	cmp	r1, #0	@ tmp157,
	bne	.L104	@,
	cmp	r3, #6	@ eMode,
	beq	.L104	@,
.L105:
	cmp	r3, #1	@ eMode,
	movne	r1, #0	@, D.25478
	moveq	r1, #1	@, D.25478
	cmp	r3, #1	@ eMode,
	cmpne	r3, #4	@, eMode,
	beq	.L106	@,
	cmp	r3, #6	@ eMode,
	beq	.L106	@,
.L107:
	cmp	r3, #5	@ eMode,
	orreq	r1, r1, #1	@,, tmp173, D.25478
	cmp	r1, #0	@ tmp173,
	bne	.L108	@,
	cmp	r3, #6	@ eMode,
	bne	.L109	@,
.L108:
	ldrb	r3, [r2, #367]	@ zero_extendqisi2	@,
	bfi	r3, r0, #4, #1	@ tmp174, bEnable,,
	mov	r0, #0	@,
	strb	r3, [r2, #367]	@ tmp174,
	ldmfd	sp, {fp, sp, pc}	@
.L101:
	rsbs	r1, r3, #1	@ temp.553, eMode
	movcc	r1, #0	@ temp.553
	cmp	r3, #0	@ eMode,
	cmpne	r3, #2	@, eMode,
	bne	.L124	@,
.L117:
	ldrb	ip, [r2, #751]	@ zero_extendqisi2	@,
	bfi	ip, r0, #5, #1	@ tmp215, bEnable,,
	strb	ip, [r2, #751]	@ tmp215,
.L118:
	cmp	r3, #3	@ eMode,
	orreq	r1, r1, #1	@,, tmp221, temp.553
	cmp	r1, #0	@ tmp221,
	bne	.L119	@,
	cmp	r3, #6	@ eMode,
	bne	.L109	@,
.L119:
	ldrb	r1, [r2, #751]	@ zero_extendqisi2	@,
	bfi	r1, r0, #4, #1	@ tmp222, bEnable,,
	mov	r0, #0	@,
	strb	r1, [r2, #751]	@ tmp222,
	ldmfd	sp, {fp, sp, pc}	@
.L100:
	rsbs	r1, r3, #1	@ temp.535, eMode
	movcc	r1, #0	@ temp.535
	cmp	r3, #0	@ eMode,
	cmpne	r3, #3	@, eMode,
	bne	.L125	@,
.L110:
	ldrb	ip, [r2, #419]	@ zero_extendqisi2	@,
	bfi	ip, r0, #4, #1	@ tmp183, bEnable,,
	strb	ip, [r2, #419]	@ tmp183,
.L111:
	cmp	r3, #2	@ eMode,
	orreq	r1, r1, #1	@,, tmp189, temp.535
	cmp	r1, #0	@ tmp189,
	bne	.L112	@,
	cmp	r3, #6	@ eMode,
	beq	.L112	@,
.L113:
	cmp	r3, #1	@ eMode,
	movne	r1, #0	@, temp.544
	moveq	r1, #1	@, temp.544
	cmp	r3, #1	@ eMode,
	cmpne	r3, #4	@, eMode,
	beq	.L114	@,
	cmp	r3, #6	@ eMode,
	beq	.L114	@,
.L115:
	cmp	r3, #5	@ eMode,
	orreq	r1, r1, #1	@,, tmp205, temp.544
	cmp	r1, #0	@ tmp205,
	bne	.L116	@,
	cmp	r3, #6	@ eMode,
	bne	.L109	@,
.L116:
	ldrb	r3, [r2, #431]	@ zero_extendqisi2	@,
	bfi	r3, r0, #4, #1	@ tmp206, bEnable,,
	mov	r0, #0	@,
	strb	r3, [r2, #431]	@ tmp206,
	ldmfd	sp, {fp, sp, pc}	@
.L124:
	cmp	r3, #6	@ eMode,
	bne	.L118	@,
	b	.L117	@
.L125:
	cmp	r3, #6	@ eMode,
	bne	.L111	@,
	b	.L110	@
.L123:
	cmp	r3, #6	@ eMode,
	bne	.L103	@,
	b	.L102	@
.L114:
	ldrb	ip, [r2, #431]	@ zero_extendqisi2	@,
	bfi	ip, r0, #5, #1	@ tmp199, bEnable,,
	strb	ip, [r2, #431]	@ tmp199,
	b	.L115	@
.L112:
	ldrb	r1, [r2, #419]	@ zero_extendqisi2	@,
	bfi	r1, r0, #5, #1	@ tmp190, bEnable,,
	strb	r1, [r2, #419]	@ tmp190,
	b	.L113	@
.L106:
	ldrb	ip, [r2, #367]	@ zero_extendqisi2	@,
	bfi	ip, r0, #5, #1	@ tmp167, bEnable,,
	strb	ip, [r2, #367]	@ tmp167,
	b	.L107	@
.L104:
	ldrb	r1, [r2, #355]	@ zero_extendqisi2	@,
	bfi	r1, r0, #4, #1	@ tmp158, bEnable,,
	strb	r1, [r2, #355]	@ tmp158,
	b	.L105	@
	.fnend
	.size	VPSS_REG_SetZmeMidEnable, .-VPSS_REG_SetZmeMidEnable
	.align	2
	.global	VPSS_REG_SetZmeFirEnable
	.type	VPSS_REG_SetZmeFirEnable, %function
VPSS_REG_SetZmeFirEnable:
	.fnstart
.LFB699:
	@ args = 4, pretend = 0, frame = 0
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
	cmp	r1, #2	@ ePort,
	ldr	r0, [fp, #4]	@ bEnable, bEnable
	beq	.L129	@,
	cmp	r1, #3	@ ePort,
	beq	.L130	@,
	cmp	r1, #0	@ ePort,
	beq	.L151	@,
	movw	r0, #:lower16:.LC7	@,
	movt	r0, #:upper16:.LC7	@,
	bl	printk	@
.L138:
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.L151:
	rsbs	r1, r3, #1	@ D.25410, eMode
	movcc	r1, #0	@ D.25410
	cmp	r3, #0	@ eMode,
	cmpne	r3, #2	@, eMode,
	bne	.L152	@,
.L131:
	ldrb	ip, [r2, #355]	@ zero_extendqisi2	@,
	bfi	ip, r0, #2, #1	@ tmp151, bEnable,,
	strb	ip, [r2, #355]	@ tmp151,
.L132:
	cmp	r3, #3	@ eMode,
	orreq	r1, r1, #1	@,, tmp157, D.25410
	cmp	r1, #0	@ tmp157,
	bne	.L133	@,
	cmp	r3, #6	@ eMode,
	beq	.L133	@,
.L134:
	cmp	r3, #1	@ eMode,
	movne	r1, #0	@, D.25423
	moveq	r1, #1	@, D.25423
	cmp	r3, #1	@ eMode,
	cmpne	r3, #4	@, eMode,
	beq	.L135	@,
	cmp	r3, #6	@ eMode,
	beq	.L135	@,
.L136:
	cmp	r3, #5	@ eMode,
	orreq	r1, r1, #1	@,, tmp173, D.25423
	cmp	r1, #0	@ tmp173,
	bne	.L137	@,
	cmp	r3, #6	@ eMode,
	bne	.L138	@,
.L137:
	ldrb	r3, [r2, #366]	@ zero_extendqisi2	@,
	bfi	r3, r0, #7, #1	@ tmp174, bEnable,,
	mov	r0, #0	@,
	strb	r3, [r2, #366]	@ tmp174,
	ldmfd	sp, {fp, sp, pc}	@
.L130:
	rsbs	r1, r3, #1	@ temp.609, eMode
	movcc	r1, #0	@ temp.609
	cmp	r3, #0	@ eMode,
	cmpne	r3, #2	@, eMode,
	bne	.L153	@,
.L146:
	ldrb	ip, [r2, #751]	@ zero_extendqisi2	@,
	bfi	ip, r0, #2, #1	@ tmp215, bEnable,,
	strb	ip, [r2, #751]	@ tmp215,
.L147:
	cmp	r3, #3	@ eMode,
	orreq	r1, r1, #1	@,, tmp221, temp.609
	cmp	r1, #0	@ tmp221,
	bne	.L148	@,
	cmp	r3, #6	@ eMode,
	bne	.L138	@,
.L148:
	ldrb	r1, [r2, #751]	@ zero_extendqisi2	@,
	bfi	r1, r0, #1, #1	@ tmp222, bEnable,,
	mov	r0, #0	@,
	strb	r1, [r2, #751]	@ tmp222,
	ldmfd	sp, {fp, sp, pc}	@
.L129:
	rsbs	r1, r3, #1	@ temp.591, eMode
	movcc	r1, #0	@ temp.591
	cmp	r3, #0	@ eMode,
	cmpne	r3, #2	@, eMode,
	bne	.L154	@,
.L139:
	ldrb	ip, [r2, #419]	@ zero_extendqisi2	@,
	bfi	ip, r0, #2, #1	@ tmp183, bEnable,,
	strb	ip, [r2, #419]	@ tmp183,
.L140:
	cmp	r3, #3	@ eMode,
	orreq	r1, r1, #1	@,, tmp189, temp.591
	cmp	r1, #0	@ tmp189,
	bne	.L141	@,
	cmp	r3, #6	@ eMode,
	beq	.L141	@,
.L142:
	cmp	r3, #1	@ eMode,
	movne	r1, #0	@, temp.600
	moveq	r1, #1	@, temp.600
	cmp	r3, #1	@ eMode,
	cmpne	r3, #4	@, eMode,
	beq	.L143	@,
	cmp	r3, #6	@ eMode,
	beq	.L143	@,
.L144:
	cmp	r3, #5	@ eMode,
	orreq	r1, r1, #1	@,, tmp205, temp.600
	cmp	r1, #0	@ tmp205,
	bne	.L145	@,
	cmp	r3, #6	@ eMode,
	bne	.L138	@,
.L145:
	ldrb	r3, [r2, #430]	@ zero_extendqisi2	@,
	bfi	r3, r0, #7, #1	@ tmp206, bEnable,,
	mov	r0, #0	@,
	strb	r3, [r2, #430]	@ tmp206,
	ldmfd	sp, {fp, sp, pc}	@
.L153:
	cmp	r3, #6	@ eMode,
	bne	.L147	@,
	b	.L146	@
.L154:
	cmp	r3, #6	@ eMode,
	bne	.L140	@,
	b	.L139	@
.L152:
	cmp	r3, #6	@ eMode,
	bne	.L132	@,
	b	.L131	@
.L143:
	ldrb	ip, [r2, #431]	@ zero_extendqisi2	@,
	bfi	ip, r0, #0, #1	@ tmp199, bEnable,,
	strb	ip, [r2, #431]	@ tmp199,
	b	.L144	@
.L141:
	ldrb	r1, [r2, #419]	@ zero_extendqisi2	@,
	bfi	r1, r0, #1, #1	@ tmp190, bEnable,,
	strb	r1, [r2, #419]	@ tmp190,
	b	.L142	@
.L135:
	ldrb	ip, [r2, #367]	@ zero_extendqisi2	@,
	bfi	ip, r0, #0, #1	@ tmp167, bEnable,,
	strb	ip, [r2, #367]	@ tmp167,
	b	.L136	@
.L133:
	ldrb	r1, [r2, #355]	@ zero_extendqisi2	@,
	bfi	r1, r0, #1, #1	@ tmp158, bEnable,,
	strb	r1, [r2, #355]	@ tmp158,
	b	.L134	@
	.fnend
	.size	VPSS_REG_SetZmeFirEnable, .-VPSS_REG_SetZmeFirEnable
	.align	2
	.global	VPSS_REG_SetZmeOutSize
	.type	VPSS_REG_SetZmeOutSize, %function
VPSS_REG_SetZmeOutSize:
	.fnstart
.LFB698:
	@ args = 4, pretend = 0, frame = 0
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
	cmp	r1, #2	@ ePort,
	ldr	r0, [fp, #4]	@ u32Width, u32Width
	beq	.L158	@,
	cmp	r1, #3	@ ePort,
	beq	.L159	@,
	cmp	r1, #0	@ ePort,
	beq	.L163	@,
	movw	r0, #:lower16:.LC8	@,
	movt	r0, #:upper16:.LC8	@,
	bl	printk	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.L163:
	ldr	r1, [r2, #376]	@ tmp141,
	sub	ip, r3, #1	@ tmp140, u32Height,
	sub	r0, r0, #1	@ tmp143, u32Width,
	mov	r3, #376	@ tmp144,
	bfi	r1, ip, #12, #12	@ tmp141, tmp140,,
	str	r1, [r2, #376]	@ tmp141,
	bfi	r1, r0, #0, #12	@ tmp145, tmp143,,
	mov	r0, #0	@,
	strh	r1, [r2, r3]	@ movhi	@ tmp145,
	ldmfd	sp, {fp, sp, pc}	@
.L159:
	mov	r3, #752	@ tmp157,
	sub	r0, r0, #1	@ tmp156, u32Width,
	ldrh	r1, [r2, r3]	@,
	bfi	r1, r0, #0, #12	@ tmp158, tmp156,,
	mov	r0, #0	@,
	strh	r1, [r2, r3]	@ movhi	@ tmp158,
	ldmfd	sp, {fp, sp, pc}	@
.L158:
	ldr	r1, [r2, #436]	@ tmp149,
	sub	ip, r3, #1	@ tmp148, u32Height,
	sub	r0, r0, #1	@ tmp151, u32Width,
	mov	r3, #436	@ tmp152,
	bfi	r1, ip, #12, #12	@ tmp149, tmp148,,
	str	r1, [r2, #436]	@ tmp149,
	bfi	r1, r0, #0, #12	@ tmp153, tmp151,,
	mov	r0, #0	@,
	strh	r1, [r2, r3]	@ movhi	@ tmp153,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VPSS_REG_SetZmeOutSize, .-VPSS_REG_SetZmeOutSize
	.align	2
	.global	VPSS_REG_SetZmeInSize
	.type	VPSS_REG_SetZmeInSize, %function
VPSS_REG_SetZmeInSize:
	.fnstart
.LFB697:
	@ args = 4, pretend = 0, frame = 0
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
	cmp	r1, #3	@ ePort,
	bls	.L169	@,
.L165:
	movw	r0, #:lower16:.LC9	@,
	movt	r0, #:upper16:.LC9	@,
	bl	printk	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.L169:
	mov	r0, #1	@ tmp140,
	mov	r1, r0, asl r1	@ tmp139, tmp140,
	tst	r1, #13	@ tmp139,
	beq	.L165	@,
	ldr	ip, [r2, #380]	@ tmp144,
	sub	r3, r3, #1	@ tmp143, u32Height,
	ldr	r0, [fp, #4]	@ u32Width, u32Width
	bfi	ip, r3, #12, #12	@ tmp144, tmp143,,
	mov	r3, #380	@ tmp147,
	sub	r1, r0, #1	@ tmp146, u32Width,
	str	ip, [r2, #380]	@ tmp144,
	mov	r0, #0	@,
	bfi	ip, r1, #0, #12	@ tmp148, tmp146,,
	strh	ip, [r2, r3]	@ movhi	@ tmp148,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VPSS_REG_SetZmeInSize, .-VPSS_REG_SetZmeInSize
	.align	2
	.global	VPSS_REG_SetZmeEnable
	.type	VPSS_REG_SetZmeEnable, %function
VPSS_REG_SetZmeEnable:
	.fnstart
.LFB696:
	@ args = 4, pretend = 0, frame = 0
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
	cmp	r1, #2	@ ePort,
	ldr	r0, [fp, #4]	@ bEnable, bEnable
	beq	.L173	@,
	cmp	r1, #3	@ ePort,
	beq	.L174	@,
	cmp	r1, #0	@ ePort,
	beq	.L195	@,
	movw	r0, #:lower16:.LC10	@,
	movt	r0, #:upper16:.LC10	@,
	bl	printk	@
.L182:
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.L195:
	rsbs	r1, r3, #1	@ D.25317, eMode
	movcc	r1, #0	@ D.25317
	cmp	r3, #0	@ eMode,
	cmpne	r3, #2	@, eMode,
	bne	.L196	@,
.L175:
	ldrb	ip, [r2, #355]	@ zero_extendqisi2	@,
	bfi	ip, r0, #7, #1	@ tmp151, bEnable,,
	strb	ip, [r2, #355]	@ tmp151,
.L176:
	cmp	r3, #3	@ eMode,
	orreq	r1, r1, #1	@,, tmp157, D.25317
	cmp	r1, #0	@ tmp157,
	bne	.L177	@,
	cmp	r3, #6	@ eMode,
	beq	.L177	@,
.L178:
	cmp	r3, #1	@ eMode,
	movne	r1, #0	@, D.25330
	moveq	r1, #1	@, D.25330
	cmp	r3, #1	@ eMode,
	cmpne	r3, #4	@, eMode,
	beq	.L179	@,
	cmp	r3, #6	@ eMode,
	beq	.L179	@,
.L180:
	cmp	r3, #5	@ eMode,
	orreq	r1, r1, #1	@,, tmp173, D.25330
	cmp	r1, #0	@ tmp173,
	bne	.L181	@,
	cmp	r3, #6	@ eMode,
	bne	.L182	@,
.L181:
	ldrb	r3, [r2, #367]	@ zero_extendqisi2	@,
	bfi	r3, r0, #6, #1	@ tmp174, bEnable,,
	mov	r0, #0	@,
	strb	r3, [r2, #367]	@ tmp174,
	ldmfd	sp, {fp, sp, pc}	@
.L174:
	rsbs	r1, r3, #1	@ temp.720, eMode
	movcc	r1, #0	@ temp.720
	cmp	r3, #0	@ eMode,
	cmpne	r3, #2	@, eMode,
	bne	.L197	@,
.L190:
	ldrb	ip, [r2, #751]	@ zero_extendqisi2	@,
	bfi	ip, r0, #7, #1	@ tmp215, bEnable,,
	strb	ip, [r2, #751]	@ tmp215,
.L191:
	cmp	r3, #3	@ eMode,
	orreq	r1, r1, #1	@,, tmp221, temp.720
	cmp	r1, #0	@ tmp221,
	bne	.L192	@,
	cmp	r3, #6	@ eMode,
	bne	.L182	@,
.L192:
	ldrb	r1, [r2, #751]	@ zero_extendqisi2	@,
	bfi	r1, r0, #6, #1	@ tmp222, bEnable,,
	mov	r0, #0	@,
	strb	r1, [r2, #751]	@ tmp222,
	ldmfd	sp, {fp, sp, pc}	@
.L173:
	rsbs	r1, r3, #1	@ temp.702, eMode
	movcc	r1, #0	@ temp.702
	cmp	r3, #0	@ eMode,
	cmpne	r3, #2	@, eMode,
	bne	.L198	@,
.L183:
	ldrb	ip, [r2, #419]	@ zero_extendqisi2	@,
	bfi	ip, r0, #7, #1	@ tmp183, bEnable,,
	strb	ip, [r2, #419]	@ tmp183,
.L184:
	cmp	r3, #3	@ eMode,
	orreq	r1, r1, #1	@,, tmp189, temp.702
	cmp	r1, #0	@ tmp189,
	bne	.L185	@,
	cmp	r3, #6	@ eMode,
	beq	.L185	@,
.L186:
	cmp	r3, #1	@ eMode,
	movne	r1, #0	@, temp.711
	moveq	r1, #1	@, temp.711
	cmp	r3, #1	@ eMode,
	cmpne	r3, #4	@, eMode,
	beq	.L187	@,
	cmp	r3, #6	@ eMode,
	beq	.L187	@,
.L188:
	cmp	r3, #5	@ eMode,
	orreq	r1, r1, #1	@,, tmp205, temp.711
	cmp	r1, #0	@ tmp205,
	bne	.L189	@,
	cmp	r3, #6	@ eMode,
	bne	.L182	@,
.L189:
	ldrb	r3, [r2, #431]	@ zero_extendqisi2	@,
	bfi	r3, r0, #6, #1	@ tmp206, bEnable,,
	mov	r0, #0	@,
	strb	r3, [r2, #431]	@ tmp206,
	ldmfd	sp, {fp, sp, pc}	@
.L197:
	cmp	r3, #6	@ eMode,
	bne	.L191	@,
	b	.L190	@
.L198:
	cmp	r3, #6	@ eMode,
	bne	.L184	@,
	b	.L183	@
.L196:
	cmp	r3, #6	@ eMode,
	bne	.L176	@,
	b	.L175	@
.L187:
	ldrb	ip, [r2, #431]	@ zero_extendqisi2	@,
	bfi	ip, r0, #7, #1	@ tmp199, bEnable,,
	strb	ip, [r2, #431]	@ tmp199,
	b	.L188	@
.L185:
	ldrb	r1, [r2, #419]	@ zero_extendqisi2	@,
	bfi	r1, r0, #6, #1	@ tmp190, bEnable,,
	strb	r1, [r2, #419]	@ tmp190,
	b	.L186	@
.L179:
	ldrb	ip, [r2, #367]	@ zero_extendqisi2	@,
	bfi	ip, r0, #7, #1	@ tmp167, bEnable,,
	strb	ip, [r2, #367]	@ tmp167,
	b	.L180	@
.L177:
	ldrb	r1, [r2, #355]	@ zero_extendqisi2	@,
	bfi	r1, r0, #6, #1	@ tmp158, bEnable,,
	strb	r1, [r2, #355]	@ tmp158,
	b	.L178	@
	.fnend
	.size	VPSS_REG_SetZmeEnable, .-VPSS_REG_SetZmeEnable
	.align	2
	.global	ALG_VZmeVpssRegCfg
	.type	ALG_VZmeVpssRegCfg, %function
ALG_VZmeVpssRegCfg:
	.fnstart
.LFB707:
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
	ldr	r8, [r2, #76]	@ ih, <variable>.u32ZmeHIn
	ldr	sl, [r2, #72]	@ iw, <variable>.u32ZmeWIn
	mov	r7, r3	@ bFirEnable, bFirEnable
	ldr	r9, [r2, #84]	@ oh, <variable>.u32ZmeHOut
	mov	r5, r2	@ pstZmeRtlPara, pstZmeRtlPara
	ldr	r3, [r2, #80]	@, <variable>.u32ZmeWOut
	mov	r4, r0	@ u32LayerId, u32LayerId
	mov	r6, r1	@ pstReg, pstReg
	cmp	sl, r3	@ iw,
	cmpeq	r8, r9	@, ih, oh
	str	r3, [fp, #-48]	@, %sfp
	bne	.L200	@,
	cmp	r8, #1200	@ ih,
	cmphi	sl, #1920	@, iw,
	bhi	.L210	@,
.L200:
	mov	r0, #0	@,
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #6	@,
	mov	lr, #1	@ tmp156,
	str	lr, [sp, #0]	@ tmp156,
	bl	VPSS_REG_SetZmeEnable	@
.L201:
	cmp	r7, #0	@ bFirEnable,
	bne	.L202	@,
	ldr	lr, [r5, #16]	@ <variable>.bZmeMdHL, <variable>.bZmeMdHL
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #2	@,
	mov	r0, r7	@, bFirEnable
	str	lr, [sp, #0]	@ <variable>.bZmeMdHL,
	bl	VPSS_REG_SetZmeFirEnable	@
	ldr	ip, [r5, #20]	@ <variable>.bZmeMdHC, <variable>.bZmeMdHC
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #3	@,
	mov	r0, r7	@, bFirEnable
	str	ip, [sp, #0]	@ <variable>.bZmeMdHC,
	bl	VPSS_REG_SetZmeFirEnable	@
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #4	@,
	mov	r0, r7	@, bFirEnable
	str	r7, [sp, #0]	@ bFirEnable,
	bl	VPSS_REG_SetZmeFirEnable	@
	mov	r0, r7	@, bFirEnable
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #5	@,
	str	r7, [sp, #0]	@ bFirEnable,
	bl	VPSS_REG_SetZmeFirEnable	@
.L203:
	ldr	lr, [r5, #32]	@ <variable>.bZmeMedHL, <variable>.bZmeMedHL
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #2	@,
	mov	r0, #0	@,
	str	lr, [sp, #0]	@ <variable>.bZmeMedHL,
	bl	VPSS_REG_SetZmeMidEnable	@
	ldr	ip, [r5, #36]	@ <variable>.bZmeMedHC, <variable>.bZmeMedHC
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #3	@,
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ <variable>.bZmeMedHC,
	bl	VPSS_REG_SetZmeMidEnable	@
	ldr	ip, [r5, #40]	@ <variable>.bZmeMedVL, <variable>.bZmeMedVL
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #4	@,
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ <variable>.bZmeMedVL,
	bl	VPSS_REG_SetZmeMidEnable	@
	ldr	ip, [r5, #44]	@ <variable>.bZmeMedVC, <variable>.bZmeMedVC
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #5	@,
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ <variable>.bZmeMedVC,
	bl	VPSS_REG_SetZmeMidEnable	@
	ldr	ip, [r5, #56]	@ <variable>.s32ZmeOffsetVL, <variable>.s32ZmeOffsetVL
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #4	@,
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ <variable>.s32ZmeOffsetVL,
	bl	VPSS_REG_SetZmePhase	@
	ldr	ip, [r5, #60]	@ <variable>.s32ZmeOffsetVC, <variable>.s32ZmeOffsetVC
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #5	@,
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ <variable>.s32ZmeOffsetVC,
	bl	VPSS_REG_SetZmePhase	@
	ldr	ip, [r5, #88]	@ <variable>.u32ZmeRatioHL, <variable>.u32ZmeRatioHL
	mov	r0, #0	@,
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, r0	@,
	str	ip, [sp, #0]	@ <variable>.u32ZmeRatioHL,
	bl	VPSS_REG_SetZmeRatio	@
	ldr	ip, [r5, #92]	@ <variable>.u32ZmeRatioVL, <variable>.u32ZmeRatioVL
	mov	r0, #0	@,
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #1	@,
	str	ip, [sp, #0]	@ <variable>.u32ZmeRatioVL,
	bl	VPSS_REG_SetZmeRatio	@
	cmp	r4, #1	@ u32LayerId,
	beq	.L211	@,
.L204:
	ldrb	r0, [r5, #112]	@ zero_extendqisi2	@ <variable>.u8ZmeYCFmtIn, <variable>.u8ZmeYCFmtIn
	cmp	r0, #0	@ <variable>.u8ZmeYCFmtIn,
	moveq	r1, r4	@, u32LayerId
	moveq	r2, r6	@, pstReg
	moveq	r3, #64	@,
	movne	r1, r4	@, u32LayerId
	movne	r2, r6	@, pstReg
	movne	r3, #69	@,
	movne	r0, #0	@,
	bl	VPSS_REG_SetZmeInFmt	@
	ldrb	r0, [r5, #113]	@ zero_extendqisi2	@ <variable>.u8ZmeYCFmtOut, <variable>.u8ZmeYCFmtOut
	cmp	r0, #0	@ <variable>.u8ZmeYCFmtOut,
	moveq	r1, r4	@, u32LayerId
	moveq	r2, r6	@, pstReg
	moveq	r3, #64	@,
	movne	r1, r4	@, u32LayerId
	movne	r2, r6	@, pstReg
	movne	r3, #69	@,
	movne	r0, #0	@,
	bl	VPSS_REG_SetZmeOutFmt	@
	mov	r3, r8	@, ih
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r0, #0	@,
	str	sl, [sp, #0]	@ iw,
	bl	VPSS_REG_SetZmeInSize	@
	ldr	ip, [fp, #-48]	@, %sfp
	mov	r3, r9	@, oh
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r0, #0	@,
	str	ip, [sp, #0]	@,
	bl	VPSS_REG_SetZmeOutSize	@
	ldr	ip, [r5, #116]	@ <variable>.u32ZmeCoefAddrHL, <variable>.u32ZmeCoefAddrHL
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #2	@,
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ <variable>.u32ZmeCoefAddrHL,
	bl	VPSS_REG_SetZmeCoefAddr	@
	ldr	ip, [r5, #120]	@ <variable>.u32ZmeCoefAddrHC, <variable>.u32ZmeCoefAddrHC
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #3	@,
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ <variable>.u32ZmeCoefAddrHC,
	bl	VPSS_REG_SetZmeCoefAddr	@
	ldr	ip, [r5, #124]	@ <variable>.u32ZmeCoefAddrVL, <variable>.u32ZmeCoefAddrVL
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #4	@,
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ <variable>.u32ZmeCoefAddrVL,
	bl	VPSS_REG_SetZmeCoefAddr	@
	ldr	ip, [r5, #128]	@ <variable>.u32ZmeCoefAddrVC, <variable>.u32ZmeCoefAddrVC
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #5	@,
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ <variable>.u32ZmeCoefAddrVC,
	bl	VPSS_REG_SetZmeCoefAddr	@
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L202:
	ldr	lr, [r5, #16]	@ <variable>.bZmeMdHL, <variable>.bZmeMdHL
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #2	@,
	mov	r0, #0	@,
	str	lr, [sp, #0]	@ <variable>.bZmeMdHL,
	bl	VPSS_REG_SetZmeFirEnable	@
	ldr	ip, [r5, #20]	@ <variable>.bZmeMdHC, <variable>.bZmeMdHC
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #3	@,
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ <variable>.bZmeMdHC,
	bl	VPSS_REG_SetZmeFirEnable	@
	ldr	ip, [r5, #24]	@ <variable>.bZmeMdVL, <variable>.bZmeMdVL
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #4	@,
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ <variable>.bZmeMdVL,
	bl	VPSS_REG_SetZmeFirEnable	@
	ldr	ip, [r5, #28]	@ <variable>.bZmeMdVC, <variable>.bZmeMdVC
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r3, #5	@,
	mov	r0, #0	@,
	str	ip, [sp, #0]	@ <variable>.bZmeMdVC,
	bl	VPSS_REG_SetZmeFirEnable	@
	b	.L203	@
.L210:
	mov	ip, #0	@ tmp155,
	mov	r1, r0	@, u32LayerId
	mov	r2, r6	@, pstReg
	mov	r0, ip	@, tmp155
	mov	r3, #6	@,
	str	ip, [sp, #0]	@ tmp155,
	bl	VPSS_REG_SetZmeEnable	@
	b	.L201	@
.L211:
	mov	r1, r4	@, u32LayerId
	mov	r2, r6	@, pstReg
	ldr	r3, [r5, #104]	@, <variable>.bZmeOrder
	mov	r0, #0	@,
	bl	VPSS_REG_SetZmeHfirOrder	@
	b	.L204	@
	.fnend
	.size	ALG_VZmeVpssRegCfg, .-ALG_VZmeVpssRegCfg
	.align	2
	.global	VDP_SR_SetZmeCoef
	.type	VDP_SR_SetZmeCoef, %function
VDP_SR_SetZmeCoef:
	.fnstart
.LFB694:
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
	cmp	r0, #2	@ u32Data,
	mov	r4, r0	@ u32Data, u32Data
	mov	r7, r1	@ enMode, enMode
	mov	r5, r2	@ pstVdpSrZmeCoef, pstVdpSrZmeCoef
	bhi	.L218	@,
	bl	PQ_HAL_GetVdpReg	@
	movw	r6, #:lower16:.LANCHOR0	@ tmp178,
	cmp	r7, #0	@ enMode,
	movt	r6, #:upper16:.LANCHOR0	@ tmp178,
	str	r0, [r6, #0]	@ pVdpReg.279, pVdpReg
	beq	.L219	@,
	cmp	r7, #1	@ enMode,
	bne	.L216	@,
	add	r1, r0, #3360	@ tmp377, pVdpReg.279,
	mov	r4, r4, asl #11	@ temp.829, u32Data,
	add	lr, r1, #12	@ tmp377, tmp377,
	add	r0, r4, lr	@, temp.829, tmp377
	bl	PQ_HAL_RegRead	@
	ldrh	r3, [r5, #64]	@ <variable>.s16VLCoef0, <variable>.s16VLCoef0
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	r2, [r5, #68]	@ <variable>.s16VLCoef0, <variable>.s16VLCoef0
	mov	r1, r0	@ SR_VCOEF0,
	ldrh	r0, [r5, #66]	@ <variable>.s16VLCoef0, <variable>.s16VLCoef0
	bfi	r1, r3, #20, #10	@ SR_VCOEF0, <variable>.s16VLCoef0,,
	add	r3, ip, #3360	@ tmp390, pVdpReg,
	add	ip, r3, #12	@ tmp390, tmp390,
	bfi	r1, r0, #10, #10	@ SR_VCOEF0, <variable>.s16VLCoef0,,
	bfi	r1, r2, #0, #10	@ SR_VCOEF0, <variable>.s16VLCoef0,,
	add	r0, r4, ip	@, temp.829, tmp390
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	add	r1, r0, #3376	@ tmp395, pVdpReg,
	add	r0, r4, r1	@, temp.829, tmp395
	bl	PQ_HAL_RegRead	@
	ldrh	r2, [r5, #70]	@ <variable>.s16VLCoef0, <variable>.s16VLCoef0
	ldrh	r3, [r5, #72]	@ <variable>.s16VLCoef0, <variable>.s16VLCoef0
	ldrh	ip, [r5, #74]	@ <variable>.s16VLCoef0, <variable>.s16VLCoef0
	mov	r1, r0	@ SR_VCOEF1,
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r2, #20, #10	@ SR_VCOEF1, <variable>.s16VLCoef0,,
	bfi	r1, r3, #10, #10	@ SR_VCOEF1, <variable>.s16VLCoef0,,
	add	r3, r0, #3376	@ tmp408, pVdpReg,
	add	r0, r4, r3	@, temp.829, tmp408
	bfi	r1, ip, #0, #10	@ SR_VCOEF1, <variable>.s16VLCoef0,,
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r2, #3376	@ tmp412, pVdpReg,
	add	r1, ip, #4	@ tmp412, tmp412,
	add	r0, r4, r1	@, temp.829, tmp412
	bl	PQ_HAL_RegRead	@
	ldrh	r3, [r5, #76]	@ <variable>.s16VLCoef1, <variable>.s16VLCoef1
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	r2, [r5, #80]	@ <variable>.s16VLCoef1, <variable>.s16VLCoef1
	mov	r1, r0	@ SR_VCOEF2,
	ldrh	r0, [r5, #78]	@ <variable>.s16VLCoef1, <variable>.s16VLCoef1
	bfi	r1, r3, #20, #10	@ SR_VCOEF2, <variable>.s16VLCoef1,,
	bfi	r1, r0, #10, #10	@ SR_VCOEF2, <variable>.s16VLCoef1,,
	add	r0, ip, #3376	@ tmp426, pVdpReg,
	add	r3, r0, #4	@ tmp426, tmp426,
	bfi	r1, r2, #0, #10	@ SR_VCOEF2, <variable>.s16VLCoef1,,
	add	r0, r4, r3	@, temp.829, tmp426
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r2, #3376	@ tmp431, pVdpReg,
	add	r1, ip, #8	@ tmp431, tmp431,
	add	r0, r4, r1	@, temp.829, tmp431
	bl	PQ_HAL_RegRead	@
	ldrh	r3, [r5, #82]	@ <variable>.s16VLCoef1, <variable>.s16VLCoef1
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	r2, [r5, #86]	@ <variable>.s16VLCoef1, <variable>.s16VLCoef1
	mov	r1, r0	@ SR_VCOEF3,
	ldrh	r0, [r5, #84]	@ <variable>.s16VLCoef1, <variable>.s16VLCoef1
	bfi	r1, r3, #20, #10	@ SR_VCOEF3, <variable>.s16VLCoef1,,
	bfi	r1, r0, #10, #10	@ SR_VCOEF3, <variable>.s16VLCoef1,,
	add	r0, ip, #3376	@ tmp445, pVdpReg,
	add	r3, r0, #8	@ tmp445, tmp445,
	bfi	r1, r2, #0, #10	@ SR_VCOEF3, <variable>.s16VLCoef1,,
	add	r0, r4, r3	@, temp.829, tmp445
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r2, #3376	@ tmp450, pVdpReg,
	add	r1, ip, #12	@ tmp450, tmp450,
	add	r0, r4, r1	@, temp.829, tmp450
	bl	PQ_HAL_RegRead	@
	ldrh	r3, [r5, #88]	@ <variable>.s16VCCoef0, <variable>.s16VCCoef0
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	r2, [r5, #92]	@ <variable>.s16VCCoef0, <variable>.s16VCCoef0
	mov	r1, r0	@ SR_VCOEF4,
	ldrh	r0, [r5, #90]	@ <variable>.s16VCCoef0, <variable>.s16VCCoef0
	bfi	r1, r3, #20, #10	@ SR_VCOEF4, <variable>.s16VCCoef0,,
	add	r3, ip, #3376	@ tmp464, pVdpReg,
	bfi	r1, r0, #10, #10	@ SR_VCOEF4, <variable>.s16VCCoef0,,
	bfi	r1, r2, #0, #10	@ SR_VCOEF4, <variable>.s16VCCoef0,,
	add	r2, r3, #12	@ tmp464, tmp464,
	add	r0, r4, r2	@, temp.829, tmp464
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	add	r1, r0, #3392	@ tmp469, pVdpReg,
	add	r0, r4, r1	@, temp.829, tmp469
	bl	PQ_HAL_RegRead	@
	ldrh	ip, [r5, #94]	@ <variable>.s16VCCoef0, <variable>.s16VCCoef0
	ldrh	r3, [r5, #96]	@ <variable>.s16VCCoef0, <variable>.s16VCCoef0
	ldrh	r2, [r5, #98]	@ <variable>.s16VCCoef0, <variable>.s16VCCoef0
	mov	r1, r0	@ SR_VCOEF5,
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	bfi	r1, ip, #20, #10	@ SR_VCOEF5, <variable>.s16VCCoef0,,
	bfi	r1, r3, #10, #10	@ SR_VCOEF5, <variable>.s16VCCoef0,,
	add	ip, r0, #3392	@ tmp482, pVdpReg,
	add	r0, r4, ip	@, temp.829, tmp482
	bfi	r1, r2, #0, #10	@ SR_VCOEF5, <variable>.s16VCCoef0,,
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	r3, r2, #3392	@ tmp486, pVdpReg,
	add	r1, r3, #4	@ tmp486, tmp486,
	add	r0, r4, r1	@, temp.829, tmp486
	bl	PQ_HAL_RegRead	@
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	ip, [r5, #102]	@ <variable>.s16VCCoef1, <variable>.s16VCCoef1
	ldrh	r2, [r5, #104]	@ <variable>.s16VCCoef1, <variable>.s16VCCoef1
	mov	r1, r0	@ SR_VCOEF6,
	ldrh	r0, [r5, #100]	@ <variable>.s16VCCoef1, <variable>.s16VCCoef1
	bfi	r1, r0, #20, #10	@ SR_VCOEF6, <variable>.s16VCCoef1,,
	add	r0, r3, #3392	@ tmp500, pVdpReg,
	bfi	r1, ip, #10, #10	@ SR_VCOEF6, <variable>.s16VCCoef1,,
	add	ip, r0, #4	@ tmp500, tmp500,
	add	r0, r4, ip	@, temp.829, tmp500
	bfi	r1, r2, #0, #10	@ SR_VCOEF6, <variable>.s16VCCoef1,,
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	r3, r2, #3392	@ tmp505, pVdpReg,
	add	r1, r3, #8	@ tmp505, tmp505,
	add	r0, r4, r1	@, temp.829, tmp505
	bl	PQ_HAL_RegRead	@
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	ip, [r5, #108]	@ <variable>.s16VCCoef1, <variable>.s16VCCoef1
	ldrh	r2, [r5, #110]	@ <variable>.s16VCCoef1, <variable>.s16VCCoef1
	mov	r1, r0	@ SR_VCOEF7,
	ldrh	r0, [r5, #106]	@ <variable>.s16VCCoef1, <variable>.s16VCCoef1
	bfi	r1, r0, #20, #10	@ SR_VCOEF7, <variable>.s16VCCoef1,,
	add	r0, r3, #3392	@ tmp519, pVdpReg,
	bfi	r1, ip, #10, #10	@ SR_VCOEF7, <variable>.s16VCCoef1,,
	add	ip, r0, #8	@ tmp519, tmp519,
	bfi	r1, r2, #0, #10	@ SR_VCOEF7, <variable>.s16VCCoef1,,
	add	r0, r4, ip	@, temp.829, tmp519
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L219:
	mov	r4, r4, asl #11	@ D.25011, u32Data,
	add	lr, r0, #3328	@ tmp179, pVdpReg.279,
	add	r0, r4, lr	@, D.25011, tmp179
	bl	PQ_HAL_RegRead	@
	ldrh	r2, [r5, #0]	@ <variable>.s16HLCoef0, <variable>.s16HLCoef0
	ldrh	r3, [r5, #2]	@ <variable>.s16HLCoef0, <variable>.s16HLCoef0
	ldrh	ip, [r5, #4]	@ <variable>.s16HLCoef0, <variable>.s16HLCoef0
	mov	r1, r0	@ SR_HCOEF0,
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r2, #20, #10	@ SR_HCOEF0, <variable>.s16HLCoef0,,
	bfi	r1, r3, #10, #10	@ SR_HCOEF0, <variable>.s16HLCoef0,,
	add	r3, r0, #3328	@ tmp191, pVdpReg,
	add	r0, r4, r3	@, D.25011, tmp191
	bfi	r1, ip, #0, #10	@ SR_HCOEF0, <variable>.s16HLCoef0,,
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r2, #3328	@ tmp195, pVdpReg,
	add	r1, ip, #4	@ tmp195, tmp195,
	add	r0, r4, r1	@, D.25011, tmp195
	bl	PQ_HAL_RegRead	@
	ldrh	r3, [r5, #6]	@ <variable>.s16HLCoef0, <variable>.s16HLCoef0
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	r2, [r5, #10]	@ <variable>.s16HLCoef0, <variable>.s16HLCoef0
	mov	r1, r0	@ SR_HCOEF1,
	ldrh	r0, [r5, #8]	@ <variable>.s16HLCoef0, <variable>.s16HLCoef0
	bfi	r1, r3, #20, #10	@ SR_HCOEF1, <variable>.s16HLCoef0,,
	bfi	r1, r0, #10, #10	@ SR_HCOEF1, <variable>.s16HLCoef0,,
	add	r0, ip, #3328	@ tmp209, pVdpReg,
	add	r3, r0, #4	@ tmp209, tmp209,
	bfi	r1, r2, #0, #10	@ SR_HCOEF1, <variable>.s16HLCoef0,,
	add	r0, r4, r3	@, D.25011, tmp209
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r2, #3328	@ tmp214, pVdpReg,
	add	r1, ip, #8	@ tmp214, tmp214,
	add	r0, r4, r1	@, D.25011, tmp214
	bl	PQ_HAL_RegRead	@
	ldrh	r3, [r5, #12]	@ <variable>.s16HLCoef0, <variable>.s16HLCoef0
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	r2, [r5, #16]	@ <variable>.s16HLCoef1, <variable>.s16HLCoef1
	mov	r1, r0	@ SR_HCOEF2,
	ldrh	r0, [r5, #14]	@ <variable>.s16HLCoef0, <variable>.s16HLCoef0
	bfi	r1, r3, #20, #10	@ SR_HCOEF2, <variable>.s16HLCoef0,,
	bfi	r1, r0, #10, #10	@ SR_HCOEF2, <variable>.s16HLCoef0,,
	add	r0, ip, #3328	@ tmp228, pVdpReg,
	add	r3, r0, #8	@ tmp228, tmp228,
	bfi	r1, r2, #0, #10	@ SR_HCOEF2, <variable>.s16HLCoef1,,
	add	r0, r4, r3	@, D.25011, tmp228
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r2, #3328	@ tmp233, pVdpReg,
	add	r1, ip, #12	@ tmp233, tmp233,
	add	r0, r4, r1	@, D.25011, tmp233
	bl	PQ_HAL_RegRead	@
	ldrh	r3, [r5, #18]	@ <variable>.s16HLCoef1, <variable>.s16HLCoef1
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	r2, [r5, #22]	@ <variable>.s16HLCoef1, <variable>.s16HLCoef1
	mov	r1, r0	@ SR_HCOEF3,
	ldrh	r0, [r5, #20]	@ <variable>.s16HLCoef1, <variable>.s16HLCoef1
	bfi	r1, r3, #20, #10	@ SR_HCOEF3, <variable>.s16HLCoef1,,
	add	r3, ip, #3328	@ tmp247, pVdpReg,
	add	ip, r3, #12	@ tmp247, tmp247,
	bfi	r1, r0, #10, #10	@ SR_HCOEF3, <variable>.s16HLCoef1,,
	bfi	r1, r2, #0, #10	@ SR_HCOEF3, <variable>.s16HLCoef1,,
	add	r0, r4, ip	@, D.25011, tmp247
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	add	r1, r0, #3344	@ tmp252, pVdpReg,
	add	r0, r4, r1	@, D.25011, tmp252
	bl	PQ_HAL_RegRead	@
	ldrh	r2, [r5, #24]	@ <variable>.s16HLCoef1, <variable>.s16HLCoef1
	ldrh	r3, [r5, #26]	@ <variable>.s16HLCoef1, <variable>.s16HLCoef1
	ldrh	ip, [r5, #28]	@ <variable>.s16HLCoef1, <variable>.s16HLCoef1
	mov	r1, r0	@ SR_HCOEF4,
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r2, #20, #10	@ SR_HCOEF4, <variable>.s16HLCoef1,,
	bfi	r1, r3, #10, #10	@ SR_HCOEF4, <variable>.s16HLCoef1,,
	add	r3, r0, #3344	@ tmp265, pVdpReg,
	add	r0, r4, r3	@, D.25011, tmp265
	bfi	r1, ip, #0, #10	@ SR_HCOEF4, <variable>.s16HLCoef1,,
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r2, #3344	@ tmp269, pVdpReg,
	add	r1, ip, #4	@ tmp269, tmp269,
	add	r0, r4, r1	@, D.25011, tmp269
	bl	PQ_HAL_RegRead	@
	ldrh	r3, [r5, #30]	@ <variable>.s16HLCoef1, <variable>.s16HLCoef1
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	r2, [r5, #34]	@ <variable>.s16HCCoef0, <variable>.s16HCCoef0
	mov	r1, r0	@ SR_HCOEF5,
	ldrh	r0, [r5, #32]	@ <variable>.s16HCCoef0, <variable>.s16HCCoef0
	bfi	r1, r3, #20, #10	@ SR_HCOEF5, <variable>.s16HLCoef1,,
	bfi	r1, r0, #10, #10	@ SR_HCOEF5, <variable>.s16HCCoef0,,
	add	r0, ip, #3344	@ tmp283, pVdpReg,
	add	r3, r0, #4	@ tmp283, tmp283,
	bfi	r1, r2, #0, #10	@ SR_HCOEF5, <variable>.s16HCCoef0,,
	add	r0, r4, r3	@, D.25011, tmp283
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r2, #3344	@ tmp288, pVdpReg,
	add	r1, ip, #8	@ tmp288, tmp288,
	add	r0, r4, r1	@, D.25011, tmp288
	bl	PQ_HAL_RegRead	@
	ldrh	r3, [r5, #36]	@ <variable>.s16HCCoef0, <variable>.s16HCCoef0
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	r2, [r5, #40]	@ <variable>.s16HCCoef0, <variable>.s16HCCoef0
	mov	r1, r0	@ SR_HCOEF6,
	ldrh	r0, [r5, #38]	@ <variable>.s16HCCoef0, <variable>.s16HCCoef0
	bfi	r1, r3, #20, #10	@ SR_HCOEF6, <variable>.s16HCCoef0,,
	bfi	r1, r0, #10, #10	@ SR_HCOEF6, <variable>.s16HCCoef0,,
	add	r0, ip, #3344	@ tmp302, pVdpReg,
	add	r3, r0, #8	@ tmp302, tmp302,
	bfi	r1, r2, #0, #10	@ SR_HCOEF6, <variable>.s16HCCoef0,,
	add	r0, r4, r3	@, D.25011, tmp302
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r2, #3344	@ tmp307, pVdpReg,
	add	r1, ip, #12	@ tmp307, tmp307,
	add	r0, r4, r1	@, D.25011, tmp307
	bl	PQ_HAL_RegRead	@
	ldrh	r3, [r5, #42]	@ <variable>.s16HCCoef0, <variable>.s16HCCoef0
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	r2, [r5, #46]	@ <variable>.s16HCCoef0, <variable>.s16HCCoef0
	mov	r1, r0	@ SR_HCOEF7,
	ldrh	r0, [r5, #44]	@ <variable>.s16HCCoef0, <variable>.s16HCCoef0
	bfi	r1, r3, #20, #10	@ SR_HCOEF7, <variable>.s16HCCoef0,,
	add	r3, ip, #3344	@ tmp321, pVdpReg,
	add	ip, r3, #12	@ tmp321, tmp321,
	bfi	r1, r0, #10, #10	@ SR_HCOEF7, <variable>.s16HCCoef0,,
	bfi	r1, r2, #0, #10	@ SR_HCOEF7, <variable>.s16HCCoef0,,
	add	r0, r4, ip	@, D.25011, tmp321
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	add	r1, r0, #3360	@ tmp326, pVdpReg,
	add	r0, r4, r1	@, D.25011, tmp326
	bl	PQ_HAL_RegRead	@
	ldrh	r2, [r5, #48]	@ <variable>.s16HCCoef1, <variable>.s16HCCoef1
	ldrh	r3, [r5, #50]	@ <variable>.s16HCCoef1, <variable>.s16HCCoef1
	ldrh	ip, [r5, #52]	@ <variable>.s16HCCoef1, <variable>.s16HCCoef1
	mov	r1, r0	@ SR_HCOEF8,
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r2, #20, #10	@ SR_HCOEF8, <variable>.s16HCCoef1,,
	bfi	r1, r3, #10, #10	@ SR_HCOEF8, <variable>.s16HCCoef1,,
	add	r3, r0, #3360	@ tmp339, pVdpReg,
	add	r0, r4, r3	@, D.25011, tmp339
	bfi	r1, ip, #0, #10	@ SR_HCOEF8, <variable>.s16HCCoef1,,
	bl	PQ_HAL_RegWrite	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r2, #3360	@ tmp343, pVdpReg,
	add	r1, ip, #4	@ tmp343, tmp343,
	add	r0, r4, r1	@, D.25011, tmp343
	bl	PQ_HAL_RegRead	@
	ldrh	r3, [r5, #54]	@ <variable>.s16HCCoef1, <variable>.s16HCCoef1
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	r2, [r5, #58]	@ <variable>.s16HCCoef1, <variable>.s16HCCoef1
	mov	r1, r0	@ SR_HCOEF9,
	ldrh	r0, [r5, #56]	@ <variable>.s16HCCoef1, <variable>.s16HCCoef1
	bfi	r1, r3, #20, #10	@ SR_HCOEF9, <variable>.s16HCCoef1,,
	add	r3, ip, #3360	@ tmp357, pVdpReg,
	bfi	r1, r0, #10, #10	@ SR_HCOEF9, <variable>.s16HCCoef1,,
	bfi	r1, r2, #0, #10	@ SR_HCOEF9, <variable>.s16HCCoef1,,
	add	r2, r3, #4	@ tmp357, tmp357,
	add	r0, r4, r2	@, D.25011, tmp357
	bl	PQ_HAL_RegWrite	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	add	r0, ip, #3360	@ tmp362, pVdpReg,
	add	r1, r0, #8	@ tmp362, tmp362,
	add	r0, r4, r1	@, D.25011, tmp362
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldrh	r3, [r5, #60]	@ <variable>.s16HCCoef1, <variable>.s16HCCoef1
	ldrh	r2, [r5, #62]	@ <variable>.s16HCCoef1, <variable>.s16HCCoef1
	mov	r1, r0	@ SR_HCOEF10,
	add	r0, ip, #3360	@ tmp373, pVdpReg,
	bfi	r1, r3, #10, #10	@ SR_HCOEF10, <variable>.s16HCCoef1,,
	add	r3, r0, #8	@ tmp373, tmp373,
	bfi	r1, r2, #0, #10	@ SR_HCOEF10, <variable>.s16HCCoef1,,
	add	r0, r4, r3	@, D.25011, tmp373
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L218:
	movw	r0, #:lower16:.LC11	@,
	movt	r0, #:upper16:.LC11	@,
	bl	printk	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L216:
	movw	r0, #:lower16:.LC12	@,
	movt	r0, #:upper16:.LC12	@,
	bl	printk	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	VDP_SR_SetZmeCoef, .-VDP_SR_SetZmeCoef
	.align	2
	.global	VDP_SR_SetHfirOrder
	.type	VDP_SR_SetHfirOrder, %function
VDP_SR_SetHfirOrder:
	.fnstart
.LFB692:
	@ args = 0, pretend = 0, frame = 0
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
	cmp	r0, #2	@ u32Data,
	mov	r6, r1	@ u32HfirOrder, u32HfirOrder
	bhi	.L224	@,
	mov	r4, r0, asl #11	@ D.24968, u32Data,
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp140,
	movt	r5, #:upper16:.LANCHOR0	@ tmp140,
	add	r2, r0, #3520	@ tmp141, pVdpReg.277,
	mov	r1, r0	@ pVdpReg.277,
	add	r0, r4, r2	@, D.24968, tmp141
	str	r1, [r5, #0]	@ pVdpReg.277, pVdpReg
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ SR_HSP,
	ldr	r0, [r5, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r6, #27, #1	@ SR_HSP, u32HfirOrder,,
	add	r3, r0, #3520	@ tmp144, pVdpReg,
	add	r0, r4, r3	@, D.24968, tmp144
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L224:
	movw	r0, #:lower16:.LC13	@,
	movt	r0, #:upper16:.LC13	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_SR_SetHfirOrder, .-VDP_SR_SetHfirOrder
	.align	2
	.global	VDP_SR_SetZmeOutFmt
	.type	VDP_SR_SetZmeOutFmt, %function
VDP_SR_SetZmeOutFmt:
	.fnstart
.LFB691:
	@ args = 0, pretend = 0, frame = 0
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
	cmp	r0, #2	@ u32Data,
	mov	r4, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32Fmt, u32Fmt
	bhi	.L229	@,
	bl	PQ_HAL_GetVdpReg	@
	mov	r4, r4, asl #11	@ D.24951, u32Data,
	add	r5, r0, #3536	@ tmp141, pVdpReg.275,
	mov	r1, r0	@ pVdpReg.275,
	add	ip, r5, #8	@ tmp141, tmp141,
	movw	r5, #:lower16:.LANCHOR0	@ tmp140,
	movt	r5, #:upper16:.LANCHOR0	@ tmp140,
	add	r0, r4, ip	@, D.24951, tmp141
	str	r1, [r5, #0]	@ pVdpReg.275, pVdpReg
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ SR_VSP,
	add	r0, r2, #3536	@ tmp145, pVdpReg,
	add	r3, r0, #8	@ tmp145, tmp145,
	bfi	r1, r6, #21, #2	@ SR_VSP, u32Fmt,,
	add	r0, r4, r3	@, D.24951, tmp145
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L229:
	movw	r0, #:lower16:.LC14	@,
	movt	r0, #:upper16:.LC14	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_SR_SetZmeOutFmt, .-VDP_SR_SetZmeOutFmt
	.align	2
	.global	VDP_SR_SetZmeInFmt
	.type	VDP_SR_SetZmeInFmt, %function
VDP_SR_SetZmeInFmt:
	.fnstart
.LFB690:
	@ args = 0, pretend = 0, frame = 0
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
	cmp	r0, #2	@ u32Data,
	mov	r4, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32Fmt, u32Fmt
	bhi	.L234	@,
	bl	PQ_HAL_GetVdpReg	@
	mov	r4, r4, asl #11	@ D.24934, u32Data,
	add	r5, r0, #3536	@ tmp141, pVdpReg.273,
	mov	r1, r0	@ pVdpReg.273,
	add	ip, r5, #8	@ tmp141, tmp141,
	movw	r5, #:lower16:.LANCHOR0	@ tmp140,
	movt	r5, #:upper16:.LANCHOR0	@ tmp140,
	add	r0, r4, ip	@, D.24934, tmp141
	str	r1, [r5, #0]	@ pVdpReg.273, pVdpReg
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ SR_VSP,
	add	r0, r2, #3536	@ tmp145, pVdpReg,
	add	r3, r0, #8	@ tmp145, tmp145,
	bfi	r1, r6, #19, #2	@ SR_VSP, u32Fmt,,
	add	r0, r4, r3	@, D.24934, tmp145
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L234:
	movw	r0, #:lower16:.LC15	@,
	movt	r0, #:upper16:.LC15	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_SR_SetZmeInFmt, .-VDP_SR_SetZmeInFmt
	.align	2
	.global	VDP_SR_SetZmeMidEnable
	.type	VDP_SR_SetZmeMidEnable, %function
VDP_SR_SetZmeMidEnable:
	.fnstart
.LFB689:
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
	cmp	r0, #2	@ u32Data,
	mov	r5, r0	@ u32Data, u32Data
	mov	r4, r1	@ enMode, enMode
	mov	r7, r2	@ u32bEnable, u32bEnable
	bhi	.L246	@,
	rsbs	r8, r1, #1	@ D.24888, enMode
	movcc	r8, #0	@ D.24888
	bl	PQ_HAL_GetVdpReg	@
	movw	r6, #:lower16:.LANCHOR0	@ tmp209,
	cmp	r4, #0	@ enMode,
	cmpne	r4, #2	@, enMode,
	movt	r6, #:upper16:.LANCHOR0	@ tmp209,
	str	r0, [r6, #0]	@ pVdpReg.271, pVdpReg
	beq	.L238	@,
	cmp	r4, #10	@ enMode,
	beq	.L238	@,
	cmp	r4, #3	@ enMode,
	orreq	r8, r8, #1	@,, tmp168, D.24888
	cmp	r8, #0	@ tmp168,
	bne	.L240	@,
.L247:
	cmp	r4, #10	@ enMode,
	beq	.L240	@,
	cmp	r4, #1	@ enMode,
	movne	r8, #0	@, D.24909
	moveq	r8, #1	@, D.24909
	cmp	r4, #1	@ enMode,
	cmpne	r4, #4	@, enMode,
	beq	.L242	@,
.L248:
	cmp	r4, #10	@ enMode,
	beq	.L242	@,
.L243:
	cmp	r4, #5	@ enMode,
	orreq	r8, r8, #1	@,, tmp198, D.24909
	cmp	r8, #0	@ tmp198,
	bne	.L244	@,
	cmp	r4, #10	@ enMode,
	ldmnefd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L244:
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r5, r5, asl #11	@ temp.996, u32Data,
	add	lr, r3, #3536	@ tmp200, pVdpReg,
	add	r1, lr, #8	@ tmp200, tmp200,
	add	r0, r5, r1	@, temp.996, tmp200
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ SR_VSP,
	add	r0, ip, #3536	@ tmp205, pVdpReg,
	add	r2, r0, #8	@ tmp205, tmp205,
	bfi	r1, r7, #28, #1	@ SR_VSP, u32bEnable,,
	add	r0, r5, r2	@, temp.996, tmp205
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L238:
	add	r1, r0, #3520	@ tmp158, pVdpReg.271,
	mov	sl, r5, asl #11	@ D.24894, u32Data,
	add	r0, sl, r1	@, D.24894, tmp158
	cmp	r4, #3	@ enMode,
	orreq	r8, r8, #1	@,, tmp168, D.24888
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ SR_HSP,
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r7, #29, #1	@ SR_HSP, u32bEnable,,
	add	r3, r0, #3520	@ tmp161, pVdpReg,
	add	r0, sl, r3	@, D.24894, tmp161
	bl	PQ_HAL_RegWrite	@
	cmp	r8, #0	@ tmp168,
	beq	.L247	@,
.L240:
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r8, r5, asl #11	@ temp.976, u32Data,
	add	lr, r3, #3520	@ tmp170, pVdpReg,
	add	r0, r8, lr	@, temp.976, tmp170
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	add	r2, ip, #3520	@ tmp174, pVdpReg,
	mov	r1, r0	@ SR_HSP,
	add	r0, r8, r2	@, temp.976, tmp174
	bfi	r1, r7, #28, #1	@ SR_HSP, u32bEnable,,
	cmp	r4, #1	@ enMode,
	movne	r8, #0	@, D.24909
	moveq	r8, #1	@, D.24909
	bl	PQ_HAL_RegWrite	@
	cmp	r4, #1	@ enMode,
	cmpne	r4, #4	@, enMode,
	bne	.L248	@,
.L242:
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	sl, r5, asl #11	@ temp.986, u32Data,
	add	lr, r3, #3536	@ tmp185, pVdpReg,
	add	r1, lr, #8	@ tmp185, tmp185,
	add	r0, sl, r1	@, temp.986, tmp185
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ SR_VSP,
	add	r0, ip, #3536	@ tmp190, pVdpReg,
	add	r2, r0, #8	@ tmp190, tmp190,
	bfi	r1, r7, #29, #1	@ SR_VSP, u32bEnable,,
	add	r0, sl, r2	@, temp.986, tmp190
	bl	PQ_HAL_RegWrite	@
	b	.L243	@
.L246:
	movw	r0, #:lower16:.LC16	@,
	movt	r0, #:upper16:.LC16	@,
	bl	printk	@
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	.fnend
	.size	VDP_SR_SetZmeMidEnable, .-VDP_SR_SetZmeMidEnable
	.align	2
	.global	VDP_SR_SetZmeFirEnable
	.type	VDP_SR_SetZmeFirEnable, %function
VDP_SR_SetZmeFirEnable:
	.fnstart
.LFB688:
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
	cmp	r0, #2	@ u32Data,
	mov	r5, r0	@ u32Data, u32Data
	mov	r4, r1	@ enMode, enMode
	mov	r7, r2	@ u32bEnable, u32bEnable
	bhi	.L260	@,
	rsbs	r8, r1, #1	@ D.24840, enMode
	movcc	r8, #0	@ D.24840
	bl	PQ_HAL_GetVdpReg	@
	movw	r6, #:lower16:.LANCHOR0	@ tmp209,
	cmp	r4, #0	@ enMode,
	cmpne	r4, #2	@, enMode,
	movt	r6, #:upper16:.LANCHOR0	@ tmp209,
	str	r0, [r6, #0]	@ pVdpReg.269, pVdpReg
	beq	.L252	@,
	cmp	r4, #10	@ enMode,
	beq	.L252	@,
	cmp	r4, #3	@ enMode,
	orreq	r8, r8, #1	@,, tmp168, D.24840
	cmp	r8, #0	@ tmp168,
	bne	.L254	@,
.L261:
	cmp	r4, #10	@ enMode,
	beq	.L254	@,
	cmp	r4, #1	@ enMode,
	movne	r8, #0	@, D.24861
	moveq	r8, #1	@, D.24861
	cmp	r4, #1	@ enMode,
	cmpne	r4, #4	@, enMode,
	beq	.L256	@,
.L262:
	cmp	r4, #10	@ enMode,
	beq	.L256	@,
.L257:
	cmp	r4, #5	@ enMode,
	orreq	r8, r8, #1	@,, tmp198, D.24861
	cmp	r8, #0	@ tmp198,
	bne	.L258	@,
	cmp	r4, #10	@ enMode,
	ldmnefd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L258:
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r5, r5, asl #11	@ temp.1054, u32Data,
	add	lr, r3, #3536	@ tmp200, pVdpReg,
	add	r1, lr, #8	@ tmp200, tmp200,
	add	r0, r5, r1	@, temp.1054, tmp200
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ SR_VSP,
	add	r0, ip, #3536	@ tmp205, pVdpReg,
	add	r2, r0, #8	@ tmp205, tmp205,
	bfi	r1, r7, #23, #1	@ SR_VSP, u32bEnable,,
	add	r0, r5, r2	@, temp.1054, tmp205
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L252:
	add	r1, r0, #3520	@ tmp158, pVdpReg.269,
	mov	sl, r5, asl #11	@ D.24846, u32Data,
	add	r0, sl, r1	@, D.24846, tmp158
	cmp	r4, #3	@ enMode,
	orreq	r8, r8, #1	@,, tmp168, D.24840
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ SR_HSP,
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r7, #26, #1	@ SR_HSP, u32bEnable,,
	add	r3, r0, #3520	@ tmp161, pVdpReg,
	add	r0, sl, r3	@, D.24846, tmp161
	bl	PQ_HAL_RegWrite	@
	cmp	r8, #0	@ tmp168,
	beq	.L261	@,
.L254:
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r8, r5, asl #11	@ temp.1034, u32Data,
	add	lr, r3, #3520	@ tmp170, pVdpReg,
	add	r0, r8, lr	@, temp.1034, tmp170
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	add	r2, ip, #3520	@ tmp174, pVdpReg,
	mov	r1, r0	@ SR_HSP,
	add	r0, r8, r2	@, temp.1034, tmp174
	bfi	r1, r7, #25, #1	@ SR_HSP, u32bEnable,,
	cmp	r4, #1	@ enMode,
	movne	r8, #0	@, D.24861
	moveq	r8, #1	@, D.24861
	bl	PQ_HAL_RegWrite	@
	cmp	r4, #1	@ enMode,
	cmpne	r4, #4	@, enMode,
	bne	.L262	@,
.L256:
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	sl, r5, asl #11	@ temp.1044, u32Data,
	add	lr, r3, #3536	@ tmp185, pVdpReg,
	add	r1, lr, #8	@ tmp185, tmp185,
	add	r0, sl, r1	@, temp.1044, tmp185
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ SR_VSP,
	add	r0, ip, #3536	@ tmp190, pVdpReg,
	add	r2, r0, #8	@ tmp190, tmp190,
	bfi	r1, r7, #24, #1	@ SR_VSP, u32bEnable,,
	add	r0, sl, r2	@, temp.1044, tmp190
	bl	PQ_HAL_RegWrite	@
	b	.L257	@
.L260:
	movw	r0, #:lower16:.LC17	@,
	movt	r0, #:upper16:.LC17	@,
	bl	printk	@
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	.fnend
	.size	VDP_SR_SetZmeFirEnable, .-VDP_SR_SetZmeFirEnable
	.align	2
	.global	VDP_SR_SetZmePhase
	.type	VDP_SR_SetZmePhase, %function
VDP_SR_SetZmePhase:
	.fnstart
.LFB687:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #2	@ u32Data,
	mov	r5, r0	@ u32Data, u32Data
	mov	r4, r1	@ enMode, enMode
	mov	r7, r2	@ s32Phase, s32Phase
	bhi	.L278	@,
	rsbs	r8, r1, #1	@ D.24772, enMode
	movcc	r8, #0	@ D.24772
	bl	PQ_HAL_GetVdpReg	@
	movw	r6, #:lower16:.LANCHOR0	@ tmp246,
	cmp	r4, #0	@ enMode,
	cmpne	r4, #2	@, enMode,
	movt	r6, #:upper16:.LANCHOR0	@ tmp246,
	str	r0, [r6, #0]	@ pVdpReg.265, pVdpReg
	beq	.L266	@,
	cmp	r4, #10	@ enMode,
	beq	.L266	@,
	cmp	r4, #3	@ enMode,
	orreq	r8, r8, #1	@,, tmp179, D.24772
	cmp	r8, #0	@ tmp179,
	bne	.L268	@,
.L279:
	cmp	r4, #10	@ enMode,
	beq	.L268	@,
	cmp	r4, #4	@ enMode,
	movne	r9, #0	@, D.24796
	moveq	r9, #1	@, D.24796
	cmp	r4, #1	@ enMode,
	movne	sl, #0	@, D.24797
	moveq	sl, #1	@, D.24797
	orrs	r3, sl, r9	@, D.24797, D.24796
	bne	.L270	@,
.L280:
	cmp	r4, #10	@ enMode,
	beq	.L270	@,
	cmp	r4, #5	@ enMode,
	movne	r8, #0	@, D.24808
	moveq	r8, #1	@, D.24808
	orrs	sl, r8, sl	@, D.24808, D.24797
	bne	.L272	@,
.L281:
	cmp	r4, #10	@ enMode,
	beq	.L272	@,
	cmp	r4, #9	@ enMode,
	movne	sl, #0	@, D.24814
	moveq	sl, #1	@, D.24814
	orrs	r9, sl, r9	@, D.24814, D.24796
	bne	.L274	@,
.L282:
	cmp	r4, #10	@ enMode,
	beq	.L274	@,
.L275:
	orrs	r8, sl, r8	@, D.24814, D.24808
	bne	.L276	@,
	cmp	r4, #10	@ enMode,
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L276:
	ldr	lr, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r5, r5, asl #11	@ temp.1124, u32Data,
	add	r1, lr, #3552	@ tmp237, pVdpReg,
	add	ip, r1, #4	@ tmp237, tmp237,
	add	r0, r5, ip	@, temp.1124, tmp237
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ SR_VBOFFSET,
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r7, #0, #16	@ SR_VBOFFSET, s32Phase,,
	add	r2, r0, #3552	@ tmp242, pVdpReg,
	add	r8, r2, #4	@ tmp242, tmp242,
	add	r0, r5, r8	@, temp.1124, tmp242
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L266:
	add	r9, r0, #3520	@ tmp167, pVdpReg.265,
	mov	sl, r5, asl #11	@ D.24778, u32Data,
	add	r1, r9, #4	@ tmp167, tmp167,
	cmp	r4, #3	@ enMode,
	orreq	r8, r8, #1	@,, tmp179, D.24772
	add	r0, sl, r1	@, D.24778, tmp167
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ SR_HLOFFSET,
	add	r0, r2, #3520	@ tmp171, pVdpReg,
	add	r3, r0, #4	@ tmp171, tmp171,
	bfi	r1, r7, #0, #28	@ SR_HLOFFSET, s32Phase,,
	add	r0, sl, r3	@, D.24778, tmp171
	bl	PQ_HAL_RegWrite	@
	cmp	r8, #0	@ tmp179,
	beq	.L279	@,
.L268:
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r8, r5, asl #11	@ temp.1090, u32Data,
	cmp	r4, #4	@ enMode,
	movne	r9, #0	@, D.24796
	moveq	r9, #1	@, D.24796
	add	r0, r2, #3520	@ tmp181, pVdpReg,
	add	lr, r0, #8	@ tmp181, tmp181,
	add	r0, r8, lr	@, temp.1090, tmp181
	bl	PQ_HAL_RegRead	@
	ldr	sl, [r6, #0]	@ pVdpReg, pVdpReg
	add	r3, sl, #3520	@ tmp186, pVdpReg,
	cmp	r4, #1	@ enMode,
	movne	sl, #0	@, D.24797
	moveq	sl, #1	@, D.24797
	add	ip, r3, #8	@ tmp186, tmp186,
	mov	r1, r0	@ SR_HCOFFSET,
	add	r0, r8, ip	@, temp.1090, tmp186
	bfi	r1, r7, #0, #28	@ SR_HCOFFSET, s32Phase,,
	bl	PQ_HAL_RegWrite	@
	orrs	r3, sl, r9	@, D.24797, D.24796
	beq	.L280	@,
.L270:
	ldr	lr, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r8, r5, asl #11	@ temp.1098, u32Data,
	add	r1, lr, #3552	@ tmp198, pVdpReg,
	add	r0, r8, r1	@, temp.1098, tmp198
	bl	PQ_HAL_RegRead	@
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r3, #3552	@ tmp202, pVdpReg,
	mov	r1, r0	@ SR_VOFFSET,
	add	r0, r8, ip	@, temp.1098, tmp202
	bfi	r1, r7, #16, #16	@ SR_VOFFSET, s32Phase,,
	cmp	r4, #5	@ enMode,
	movne	r8, #0	@, D.24808
	moveq	r8, #1	@, D.24808
	bl	PQ_HAL_RegWrite	@
	orrs	sl, r8, sl	@, D.24808, D.24797
	beq	.L281	@,
.L272:
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	sl, r5, asl #11	@ temp.1106, u32Data,
	add	ip, r3, #3552	@ tmp211, pVdpReg,
	add	r0, sl, ip	@, temp.1106, tmp211
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ SR_VOFFSET,
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r7, #0, #16	@ SR_VOFFSET, s32Phase,,
	add	r2, r0, #3552	@ tmp215, pVdpReg,
	add	r0, sl, r2	@, temp.1106, tmp215
	cmp	r4, #9	@ enMode,
	movne	sl, #0	@, D.24814
	moveq	sl, #1	@, D.24814
	bl	PQ_HAL_RegWrite	@
	orrs	r9, sl, r9	@, D.24814, D.24796
	beq	.L282	@,
.L274:
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r9, r5, asl #11	@ temp.1115, u32Data,
	add	lr, r3, #3552	@ tmp224, pVdpReg,
	add	r1, lr, #4	@ tmp224, tmp224,
	add	r0, r9, r1	@, temp.1115, tmp224
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ SR_VBOFFSET,
	add	r0, ip, #3552	@ tmp229, pVdpReg,
	add	r2, r0, #4	@ tmp229, tmp229,
	bfi	r1, r7, #16, #16	@ SR_VBOFFSET, s32Phase,,
	add	r0, r9, r2	@, temp.1115, tmp229
	bl	PQ_HAL_RegWrite	@
	b	.L275	@
.L278:
	movw	r0, #:lower16:.LC18	@,
	movt	r0, #:upper16:.LC18	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	.fnend
	.size	VDP_SR_SetZmePhase, .-VDP_SR_SetZmePhase
	.align	2
	.global	VDP_SR_SetZmeEnable
	.type	VDP_SR_SetZmeEnable, %function
VDP_SR_SetZmeEnable:
	.fnstart
.LFB686:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r0, #2	@ u32Data,
	mov	r5, r0	@ u32Data, u32Data
	mov	r4, r1	@ enMode, enMode
	mov	r6, r2	@ u32bEnable, u32bEnable
	mov	r8, r3	@ u32firMode, u32firMode
	bhi	.L294	@,
	rsbs	sl, r1, #1	@ D.24720, enMode
	movcc	sl, #0	@ D.24720
	bl	PQ_HAL_GetVdpReg	@
	movw	r7, #:lower16:.LANCHOR0	@ tmp210,
	cmp	r4, #0	@ enMode,
	cmpne	r4, #2	@, enMode,
	movt	r7, #:upper16:.LANCHOR0	@ tmp210,
	str	r0, [r7, #0]	@ pVdpReg.263, pVdpReg
	beq	.L286	@,
	cmp	r4, #10	@ enMode,
	beq	.L286	@,
	cmp	r4, #3	@ enMode,
	orreq	sl, sl, #1	@,, tmp169, D.24720
	cmp	sl, #0	@ tmp169,
	bne	.L288	@,
.L295:
	cmp	r4, #10	@ enMode,
	beq	.L288	@,
	cmp	r4, #1	@ enMode,
	movne	sl, #0	@, D.24743
	moveq	sl, #1	@, D.24743
	cmp	r4, #1	@ enMode,
	cmpne	r4, #4	@, enMode,
	beq	.L290	@,
.L296:
	cmp	r4, #10	@ enMode,
	beq	.L290	@,
.L291:
	cmp	r4, #5	@ enMode,
	orreq	sl, sl, #1	@,, tmp199, D.24743
	cmp	sl, #0	@ tmp199,
	bne	.L292	@,
	cmp	r4, #10	@ enMode,
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L292:
	ldr	r0, [r7, #0]	@ pVdpReg, pVdpReg
	mov	r5, r5, asl #11	@ temp.1185, u32Data,
	add	lr, r0, #3536	@ tmp201, pVdpReg,
	add	r1, lr, #8	@ tmp201, tmp201,
	add	r0, r5, r1	@, temp.1185, tmp201
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r7, #0]	@ pVdpReg, pVdpReg
	add	r3, ip, #3536	@ tmp206, pVdpReg,
	add	r2, r3, #8	@ tmp206, tmp206,
	mov	r1, r0	@ SR_VSP,
	bfi	r1, r6, #30, #1	@ SR_VSP, u32bEnable,,
	bfi	r1, r8, #23, #1	@ SR_VSP, u32firMode,,
	add	r0, r5, r2	@, temp.1185, tmp206
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L286:
	add	r1, r0, #3520	@ tmp159, pVdpReg.263,
	mov	r9, r5, asl #11	@ D.24726, u32Data,
	add	r0, r9, r1	@, D.24726, tmp159
	cmp	r4, #3	@ enMode,
	orreq	sl, sl, #1	@,, tmp169, D.24720
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r7, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ SR_HSP,
	add	r0, r2, #3520	@ tmp162, pVdpReg,
	bfi	r1, r6, #31, #1	@ SR_HSP, u32bEnable,,
	add	r0, r9, r0	@, D.24726, tmp162
	bfi	r1, r8, #26, #1	@ SR_HSP, u32firMode,,
	bl	PQ_HAL_RegWrite	@
	cmp	sl, #0	@ tmp169,
	beq	.L295	@,
.L288:
	ldr	r0, [r7, #0]	@ pVdpReg, pVdpReg
	mov	sl, r5, asl #11	@ temp.1161, u32Data,
	add	lr, r0, #3520	@ tmp171, pVdpReg,
	add	r0, sl, lr	@, temp.1161, tmp171
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r7, #0]	@ pVdpReg, pVdpReg
	add	r3, ip, #3520	@ tmp175, pVdpReg,
	mov	r1, r0	@ SR_HSP,
	bfi	r1, r6, #30, #1	@ SR_HSP, u32bEnable,,
	add	r0, sl, r3	@, temp.1161, tmp175
	bfi	r1, r8, #25, #1	@ SR_HSP, u32firMode,,
	bl	PQ_HAL_RegWrite	@
	cmp	r4, #1	@ enMode,
	movne	sl, #0	@, D.24743
	moveq	sl, #1	@, D.24743
	cmp	r4, #1	@ enMode,
	cmpne	r4, #4	@, enMode,
	bne	.L296	@,
.L290:
	ldr	r0, [r7, #0]	@ pVdpReg, pVdpReg
	mov	r9, r5, asl #11	@ temp.1173, u32Data,
	add	lr, r0, #3536	@ tmp186, pVdpReg,
	add	r1, lr, #8	@ tmp186, tmp186,
	add	r0, r9, r1	@, temp.1173, tmp186
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r7, #0]	@ pVdpReg, pVdpReg
	add	r3, ip, #3536	@ tmp191, pVdpReg,
	add	r2, r3, #8	@ tmp191, tmp191,
	mov	r1, r0	@ SR_VSP,
	bfi	r1, r6, #31, #1	@ SR_VSP, u32bEnable,,
	bfi	r1, r8, #24, #1	@ SR_VSP, u32firMode,,
	add	r0, r9, r2	@, temp.1173, tmp191
	bl	PQ_HAL_RegWrite	@
	b	.L291	@
.L294:
	movw	r0, #:lower16:.LC19	@,
	movt	r0, #:upper16:.LC19	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	.fnend
	.size	VDP_SR_SetZmeEnable, .-VDP_SR_SetZmeEnable
	.align	2
	.global	VDP_SR_SetZmeVerRatio
	.type	VDP_SR_SetZmeVerRatio, %function
VDP_SR_SetZmeVerRatio:
	.fnstart
.LFB685:
	@ args = 0, pretend = 0, frame = 0
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
	cmp	r0, #2	@ u32Data,
	mov	r4, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32Ratio, u32Ratio
	bhi	.L301	@,
	bl	PQ_HAL_GetVdpReg	@
	mov	r4, r4, asl #11	@ D.24701, u32Data,
	add	r5, r0, #3536	@ tmp141, pVdpReg.261,
	mov	r1, r0	@ pVdpReg.261,
	add	ip, r5, #12	@ tmp141, tmp141,
	movw	r5, #:lower16:.LANCHOR0	@ tmp140,
	movt	r5, #:upper16:.LANCHOR0	@ tmp140,
	add	r0, r4, ip	@, D.24701, tmp141
	str	r1, [r5, #0]	@ pVdpReg.261, pVdpReg
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ SR_VSR,
	add	r0, r2, #3536	@ tmp145, pVdpReg,
	add	r3, r0, #12	@ tmp145, tmp145,
	bfi	r1, r6, #0, #16	@ SR_VSR, u32Ratio,,
	add	r0, r4, r3	@, D.24701, tmp145
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L301:
	movw	r0, #:lower16:.LC20	@,
	movt	r0, #:upper16:.LC20	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_SR_SetZmeVerRatio, .-VDP_SR_SetZmeVerRatio
	.align	2
	.global	VDP_SR_SetZmeHorRatio
	.type	VDP_SR_SetZmeHorRatio, %function
VDP_SR_SetZmeHorRatio:
	.fnstart
.LFB684:
	@ args = 0, pretend = 0, frame = 0
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
	cmp	r0, #2	@ u32Data,
	mov	r6, r1	@ u32Ratio, u32Ratio
	bhi	.L306	@,
	mov	r4, r0, asl #11	@ D.24685, u32Data,
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp140,
	movt	r5, #:upper16:.LANCHOR0	@ tmp140,
	add	r2, r0, #3520	@ tmp141, pVdpReg.258,
	mov	r1, r0	@ pVdpReg.258,
	add	r0, r4, r2	@, D.24685, tmp141
	str	r1, [r5, #0]	@ pVdpReg.258, pVdpReg
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ SR_HSP,
	ldr	r0, [r5, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r6, #0, #24	@ SR_HSP, u32Ratio,,
	add	r3, r0, #3520	@ tmp144, pVdpReg,
	add	r0, r4, r3	@, D.24685, tmp144
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L306:
	movw	r0, #:lower16:.LC21	@,
	movt	r0, #:upper16:.LC21	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_SR_SetZmeHorRatio, .-VDP_SR_SetZmeHorRatio
	.align	2
	.global	VDP_WBC_SetZmeInFmt
	.type	VDP_WBC_SetZmeInFmt, %function
VDP_WBC_SetZmeInFmt:
	.fnstart
.LFB682:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ enLayer, enLayer
	mov	r6, r1	@ u32Fmt, u32Fmt
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #0	@ enLayer,
	cmpne	r4, #4	@, enLayer,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.256, pVdpReg
	ldmnefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	add	ip, r0, #44544	@ tmp147, pVdpReg.256,
	mov	r4, r4, asl #10	@ D.24632, enLayer,
	add	r1, ip, #216	@ tmp147, tmp147,
	add	r0, r4, r1	@, D.24632, tmp147
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_VSP,
	add	r0, r2, #44544	@ tmp151, pVdpReg,
	add	r3, r0, #216	@ tmp151, tmp151,
	bfi	r1, r6, #19, #2	@ WBC_DHD0_ZME_VSP, u32Fmt,,
	add	r0, r4, r3	@, D.24632, tmp151
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_WBC_SetZmeInFmt, .-VDP_WBC_SetZmeInFmt
	.align	2
	.global	VDP_WBC_SetParaUpd
	.type	VDP_WBC_SetParaUpd, %function
VDP_WBC_SetParaUpd:
	.fnstart
.LFB681:
	@ args = 0, pretend = 0, frame = 8
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
	mov	r4, r0	@ enLayer, enLayer
	mov	r6, r1	@ enMode, enMode
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp150,
	cmp	r4, #0	@ enLayer,
	movt	r5, #:upper16:.LANCHOR0	@ tmp150,
	str	r0, [r5, #0]	@ pVdpReg.254, pVdpReg
	beq	.L316	@,
.L315:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L316:
	add	r0, r0, #44032	@, pVdpReg.254,
	add	r0, r0, #64	@,,
	bl	PQ_HAL_RegRead	@
	cmp	r6, #8	@ enMode,
	mov	r1, r0	@ prephitmp.1288,
	orreq	r1, r0, #3	@ prephitmp.1288, prephitmp.1288,
	beq	.L313	@,
	cmp	r6, #9	@ enMode,
	orreq	r1, r1, #12	@ prephitmp.1288, prephitmp.1288,
	bne	.L317	@,
.L313:
	ldr	r3, [r5, #0]	@ pVdpReg, pVdpReg
	add	r2, r3, #44032	@, pVdpReg,
	add	r0, r2, #64	@,,
	bl	PQ_HAL_RegWrite	@
	b	.L315	@
.L317:
	movw	r0, #:lower16:.LC22	@,
	movt	r0, #:upper16:.LC22	@,
	str	r1, [fp, #-32]	@,
	bl	printk	@
	ldr	r1, [fp, #-32]	@,
	b	.L313	@
	.fnend
	.size	VDP_WBC_SetParaUpd, .-VDP_WBC_SetParaUpd
	.align	2
	.global	VDP_WBC_SetZmeCoefAddr
	.type	VDP_WBC_SetZmeCoefAddr, %function
VDP_WBC_SetZmeCoefAddr:
	.fnstart
.LFB680:
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
	mov	r4, r0	@ enLayer, enLayer
	mov	r5, r1	@ u32Mode, u32Mode
	mov	r8, r2	@ u32Addr, u32Addr
	mov	r7, r3	@ u32CAddr, u32CAddr
	bl	PQ_HAL_GetVdpReg	@
	movw	r6, #:lower16:.LANCHOR0	@ tmp148,
	cmp	r4, #0	@ enLayer,
	cmpne	r4, #4	@, enLayer,
	movt	r6, #:upper16:.LANCHOR0	@ tmp148,
	str	r0, [r6, #0]	@ pVdpReg.252, pVdpReg
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	cmp	r5, #8	@ u32Mode,
	beq	.L323	@,
	cmp	r5, #9	@ u32Mode,
	bne	.L321	@,
	add	r1, r0, #44032	@ tmp174, pVdpReg.252,
	mov	r4, r4, asl #10	@ temp.1332, enLayer,
	add	lr, r1, #88	@ tmp174, tmp174,
	add	r0, r4, lr	@, temp.1332, tmp174
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r8	@, u32Addr
	add	r3, ip, #44032	@ tmp178, pVdpReg,
	add	r2, r3, #88	@ tmp178, tmp178,
	add	r0, r4, r2	@, temp.1332, tmp178
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	add	r1, r0, #44032	@ tmp183, pVdpReg,
	add	ip, r1, #92	@ tmp183, tmp183,
	add	r0, r4, ip	@, temp.1332, tmp183
	bl	PQ_HAL_RegRead	@
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r7	@, u32CAddr
	add	r2, r3, #44032	@ tmp188, pVdpReg,
	add	r0, r2, #92	@ tmp188, tmp188,
	add	r0, r4, r0	@, temp.1332, tmp188
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L323:
	add	r1, r0, #44032	@ tmp156, pVdpReg.252,
	mov	r4, r4, asl #10	@ D.24575, enLayer,
	add	lr, r1, #80	@ tmp156, tmp156,
	add	r0, r4, lr	@, D.24575, tmp156
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r8	@, u32Addr
	add	r3, ip, #44032	@ tmp160, pVdpReg,
	add	r2, r3, #80	@ tmp160, tmp160,
	add	r0, r4, r2	@, D.24575, tmp160
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r0, #44032	@ tmp165, pVdpReg,
	add	r1, ip, #84	@ tmp165, tmp165,
	add	r0, r4, r1	@, D.24575, tmp165
	bl	PQ_HAL_RegRead	@
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r7	@, u32CAddr
	add	r2, r3, #44032	@ tmp170, pVdpReg,
	add	r0, r2, #84	@ tmp170, tmp170,
	add	r0, r4, r0	@, D.24575, tmp170
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L321:
	movw	r0, #:lower16:.LC23	@,
	movt	r0, #:upper16:.LC23	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	.fnend
	.size	VDP_WBC_SetZmeCoefAddr, .-VDP_WBC_SetZmeCoefAddr
	.align	2
	.global	VDP_WBC_SetZmeHfirOrder
	.type	VDP_WBC_SetZmeHfirOrder, %function
VDP_WBC_SetZmeHfirOrder:
	.fnstart
.LFB678:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ enLayer, enLayer
	mov	r6, r1	@ u32HfirOrder, u32HfirOrder
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #0	@ enLayer,
	cmpne	r4, #4	@, enLayer,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.250, pVdpReg
	ldmnefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	add	ip, r0, #44544	@ tmp147, pVdpReg.250,
	mov	r4, r4, asl #10	@ D.24543, enLayer,
	add	r1, ip, #192	@ tmp147, tmp147,
	add	r0, r4, r1	@, D.24543, tmp147
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_HSP,
	add	r0, r2, #44544	@ tmp151, pVdpReg,
	add	r3, r0, #192	@ tmp151, tmp151,
	bfi	r1, r6, #24, #1	@ WBC_DHD0_ZME_HSP, u32HfirOrder,,
	add	r0, r4, r3	@, D.24543, tmp151
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_WBC_SetZmeHfirOrder, .-VDP_WBC_SetZmeHfirOrder
	.align	2
	.global	VDP_WBC_SetMidEnable
	.type	VDP_WBC_SetMidEnable, %function
VDP_WBC_SetMidEnable:
	.fnstart
.LFB677:
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
	mov	r5, r0	@ enLayer, enLayer
	mov	r4, r1	@ enMode, enMode
	mov	r7, r2	@ bEnable, bEnable
	bl	PQ_HAL_GetVdpReg	@
	movw	r6, #:lower16:.LANCHOR0	@ tmp219,
	cmp	r5, #0	@ enLayer,
	cmpne	r5, #4	@, enLayer,
	movt	r6, #:upper16:.LANCHOR0	@ tmp219,
	str	r0, [r6, #0]	@ pVdpReg.248, pVdpReg
	ldmnefd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	rsbs	r8, r4, #1	@ D.24494, enMode
	movcc	r8, #0	@ D.24494
	cmp	r4, #0	@ enMode,
	cmpne	r4, #2	@, enMode,
	beq	.L329	@,
	cmp	r4, #10	@ enMode,
	beq	.L329	@,
	cmp	r4, #3	@ enMode,
	orreq	r8, r8, #1	@,, tmp176, D.24494
	cmp	r8, #0	@ tmp176,
	bne	.L331	@,
.L337:
	cmp	r4, #10	@ enMode,
	beq	.L331	@,
	cmp	r4, #1	@ enMode,
	movne	r8, #0	@, D.24515
	moveq	r8, #1	@, D.24515
	cmp	r4, #1	@ enMode,
	cmpne	r4, #4	@, enMode,
	beq	.L333	@,
.L338:
	cmp	r4, #10	@ enMode,
	beq	.L333	@,
.L334:
	cmp	r4, #5	@ enMode,
	orreq	r8, r8, #1	@,, tmp208, D.24515
	cmp	r8, #0	@ tmp208,
	bne	.L335	@,
	cmp	r4, #10	@ enMode,
	ldmnefd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L335:
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r5, r5, asl #10	@ temp.1417, enLayer,
	add	r1, ip, #44544	@ tmp210, pVdpReg,
	add	lr, r1, #216	@ tmp210, tmp210,
	add	r0, r5, lr	@, temp.1417, tmp210
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_VSP,
	add	r0, r2, #44544	@ tmp215, pVdpReg,
	add	r3, r0, #216	@ tmp215, tmp215,
	bfi	r1, r7, #28, #1	@ WBC_DHD0_ZME_VSP, bEnable,,
	add	r0, r5, r3	@, temp.1417, tmp215
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L329:
	add	ip, r0, #44544	@ tmp164, pVdpReg.248,
	mov	sl, r5, asl #10	@ D.24500, enLayer,
	add	r1, ip, #192	@ tmp164, tmp164,
	cmp	r4, #3	@ enMode,
	orreq	r8, r8, #1	@,, tmp176, D.24494
	add	r0, sl, r1	@, D.24500, tmp164
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_HSP,
	add	r0, r2, #44544	@ tmp168, pVdpReg,
	add	r3, r0, #192	@ tmp168, tmp168,
	bfi	r1, r7, #29, #1	@ WBC_DHD0_ZME_HSP, bEnable,,
	add	r0, sl, r3	@, D.24500, tmp168
	bl	PQ_HAL_RegWrite	@
	cmp	r8, #0	@ tmp176,
	beq	.L337	@,
.L331:
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r8, r5, asl #10	@ temp.1397, enLayer,
	add	r1, ip, #44544	@ tmp178, pVdpReg,
	add	lr, r1, #192	@ tmp178, tmp178,
	add	r0, r8, lr	@, temp.1397, tmp178
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_HSP,
	add	r0, r2, #44544	@ tmp183, pVdpReg,
	add	r3, r0, #192	@ tmp183, tmp183,
	bfi	r1, r7, #28, #1	@ WBC_DHD0_ZME_HSP, bEnable,,
	add	r0, r8, r3	@, temp.1397, tmp183
	cmp	r4, #1	@ enMode,
	movne	r8, #0	@, D.24515
	moveq	r8, #1	@, D.24515
	bl	PQ_HAL_RegWrite	@
	cmp	r4, #1	@ enMode,
	cmpne	r4, #4	@, enMode,
	bne	.L338	@,
.L333:
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	mov	sl, r5, asl #10	@ temp.1407, enLayer,
	add	r1, ip, #44544	@ tmp195, pVdpReg,
	add	lr, r1, #216	@ tmp195, tmp195,
	add	r0, sl, lr	@, temp.1407, tmp195
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_VSP,
	add	r0, r2, #44544	@ tmp200, pVdpReg,
	add	r3, r0, #216	@ tmp200, tmp200,
	bfi	r1, r7, #29, #1	@ WBC_DHD0_ZME_VSP, bEnable,,
	add	r0, sl, r3	@, temp.1407, tmp200
	bl	PQ_HAL_RegWrite	@
	b	.L334	@
	.fnend
	.size	VDP_WBC_SetMidEnable, .-VDP_WBC_SetMidEnable
	.align	2
	.global	VDP_WBC_SetZmeEnable
	.type	VDP_WBC_SetZmeEnable, %function
VDP_WBC_SetZmeEnable:
	.fnstart
.LFB676:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r5, r0	@ enLayer, enLayer
	mov	r4, r1	@ enMode, enMode
	mov	r6, r2	@ u32bEnable, u32bEnable
	mov	r8, r3	@ u32firMode, u32firMode
	bl	PQ_HAL_GetVdpReg	@
	movw	r7, #:lower16:.LANCHOR0	@ tmp220,
	cmp	r5, #0	@ enLayer,
	cmpne	r5, #4	@, enLayer,
	movt	r7, #:upper16:.LANCHOR0	@ tmp220,
	str	r0, [r7, #0]	@ pVdpReg.246, pVdpReg
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	rsbs	sl, r4, #1	@ D.24441, enMode
	movcc	sl, #0	@ D.24441
	cmp	r4, #0	@ enMode,
	cmpne	r4, #2	@, enMode,
	beq	.L341	@,
	cmp	r4, #10	@ enMode,
	beq	.L341	@,
	cmp	r4, #3	@ enMode,
	orreq	sl, sl, #1	@,, tmp177, D.24441
	cmp	sl, #0	@ tmp177,
	bne	.L343	@,
.L349:
	cmp	r4, #10	@ enMode,
	beq	.L343	@,
	cmp	r4, #1	@ enMode,
	movne	sl, #0	@, D.24464
	moveq	sl, #1	@, D.24464
	cmp	r4, #1	@ enMode,
	cmpne	r4, #4	@, enMode,
	beq	.L345	@,
.L350:
	cmp	r4, #10	@ enMode,
	beq	.L345	@,
.L346:
	cmp	r4, #5	@ enMode,
	orreq	sl, sl, #1	@,, tmp209, D.24464
	cmp	sl, #0	@ tmp209,
	bne	.L347	@,
	cmp	r4, #10	@ enMode,
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L347:
	ldr	ip, [r7, #0]	@ pVdpReg, pVdpReg
	mov	r5, r5, asl #10	@ temp.1479, enLayer,
	add	r1, ip, #44544	@ tmp211, pVdpReg,
	add	lr, r1, #216	@ tmp211, tmp211,
	add	r0, r5, lr	@, temp.1479, tmp211
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r7, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_VSP,
	add	r0, r2, #44544	@ tmp216, pVdpReg,
	bfi	r1, r6, #30, #1	@ WBC_DHD0_ZME_VSP, u32bEnable,,
	add	r3, r0, #216	@ tmp216, tmp216,
	bfi	r1, r8, #23, #1	@ WBC_DHD0_ZME_VSP, u32firMode,,
	add	r0, r5, r3	@, temp.1479, tmp216
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
.L341:
	add	ip, r0, #44544	@ tmp165, pVdpReg.246,
	mov	r9, r5, asl #10	@ D.24447, enLayer,
	add	r1, ip, #192	@ tmp165, tmp165,
	cmp	r4, #3	@ enMode,
	orreq	sl, sl, #1	@,, tmp177, D.24441
	add	r0, r9, r1	@, D.24447, tmp165
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r7, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_HSP,
	add	r0, r2, #44544	@ tmp169, pVdpReg,
	add	r3, r0, #192	@ tmp169, tmp169,
	bfi	r1, r6, #31, #1	@ WBC_DHD0_ZME_HSP, u32bEnable,,
	bfi	r1, r8, #26, #1	@ WBC_DHD0_ZME_HSP, u32firMode,,
	add	r0, r9, r3	@, D.24447, tmp169
	bl	PQ_HAL_RegWrite	@
	cmp	sl, #0	@ tmp177,
	beq	.L349	@,
.L343:
	ldr	ip, [r7, #0]	@ pVdpReg, pVdpReg
	mov	sl, r5, asl #10	@ temp.1455, enLayer,
	add	r1, ip, #44544	@ tmp179, pVdpReg,
	add	lr, r1, #192	@ tmp179, tmp179,
	add	r0, sl, lr	@, temp.1455, tmp179
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r7, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_HSP,
	add	r0, r2, #44544	@ tmp184, pVdpReg,
	add	r3, r0, #192	@ tmp184, tmp184,
	bfi	r1, r6, #30, #1	@ WBC_DHD0_ZME_HSP, u32bEnable,,
	add	r0, sl, r3	@, temp.1455, tmp184
	bfi	r1, r8, #25, #1	@ WBC_DHD0_ZME_HSP, u32firMode,,
	bl	PQ_HAL_RegWrite	@
	cmp	r4, #1	@ enMode,
	movne	sl, #0	@, D.24464
	moveq	sl, #1	@, D.24464
	cmp	r4, #1	@ enMode,
	cmpne	r4, #4	@, enMode,
	bne	.L350	@,
.L345:
	ldr	ip, [r7, #0]	@ pVdpReg, pVdpReg
	mov	r9, r5, asl #10	@ temp.1467, enLayer,
	add	r1, ip, #44544	@ tmp196, pVdpReg,
	add	lr, r1, #216	@ tmp196, tmp196,
	add	r0, r9, lr	@, temp.1467, tmp196
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r7, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_VSP,
	add	r0, r2, #44544	@ tmp201, pVdpReg,
	bfi	r1, r6, #31, #1	@ WBC_DHD0_ZME_VSP, u32bEnable,,
	add	r3, r0, #216	@ tmp201, tmp201,
	bfi	r1, r8, #24, #1	@ WBC_DHD0_ZME_VSP, u32firMode,,
	add	r0, r9, r3	@, temp.1467, tmp201
	bl	PQ_HAL_RegWrite	@
	b	.L346	@
	.fnend
	.size	VDP_WBC_SetZmeEnable, .-VDP_WBC_SetZmeEnable
	.align	2
	.global	VDP_WBC_SetZmeVerRatio
	.type	VDP_WBC_SetZmeVerRatio, %function
VDP_WBC_SetZmeVerRatio:
	.fnstart
.LFB675:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ enLayer, enLayer
	mov	r6, r1	@ u32Ratio, u32Ratio
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #0	@ enLayer,
	cmpne	r4, #4	@, enLayer,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.244, pVdpReg
	ldmnefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	add	ip, r0, #44544	@ tmp147, pVdpReg.244,
	mov	r4, r4, asl #10	@ D.24419, enLayer,
	add	r1, ip, #220	@ tmp147, tmp147,
	add	r0, r4, r1	@, D.24419, tmp147
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_VSR,
	add	r0, r2, #44544	@ tmp151, pVdpReg,
	add	r3, r0, #220	@ tmp151, tmp151,
	bfi	r1, r6, #0, #16	@ WBC_DHD0_ZME_VSR, u32Ratio,,
	add	r0, r4, r3	@, D.24419, tmp151
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_WBC_SetZmeVerRatio, .-VDP_WBC_SetZmeVerRatio
	.align	2
	.global	VDP_WBC_SetZmeHorRatio
	.type	VDP_WBC_SetZmeHorRatio, %function
VDP_WBC_SetZmeHorRatio:
	.fnstart
.LFB674:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ enLayer, enLayer
	mov	r6, r1	@ u32Ratio, u32Ratio
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #0	@ enLayer,
	cmpne	r4, #4	@, enLayer,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.241, pVdpReg
	ldmnefd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	add	ip, r0, #44544	@ tmp147, pVdpReg.241,
	mov	r4, r4, asl #10	@ D.24400, enLayer,
	add	r1, ip, #192	@ tmp147, tmp147,
	add	r0, r4, r1	@, D.24400, tmp147
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_HSP,
	add	r0, r2, #44544	@ tmp151, pVdpReg,
	add	r3, r0, #192	@ tmp151, tmp151,
	bfi	r1, r6, #0, #24	@ WBC_DHD0_ZME_HSP, u32Ratio,,
	add	r0, r4, r3	@, D.24400, tmp151
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_WBC_SetZmeHorRatio, .-VDP_WBC_SetZmeHorRatio
	.align	2
	.global	VDP_WBC_SetZmePhaseV
	.type	VDP_WBC_SetZmePhaseV, %function
VDP_WBC_SetZmePhaseV:
	.fnstart
.LFB673:
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
	mov	r4, r0	@ enLayer, enLayer
	mov	r7, r1	@ s32PhaseL, s32PhaseL
	mov	r6, r2	@ s32PhaseC, s32PhaseC
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp140,
	cmp	r4, #0	@ enLayer,
	movt	r5, #:upper16:.LANCHOR0	@ tmp140,
	str	r0, [r5, #0]	@ pVdpReg.239, pVdpReg
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	add	lr, r0, #44544	@, pVdpReg.239,
	add	r0, lr, #224	@,,
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ WBC_DHD0_ZME_VOFFSET,
	ldr	r0, [r5, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r7, #16, #16	@ WBC_DHD0_ZME_VOFFSET, s32PhaseL,,
	add	ip, r0, #44544	@, pVdpReg,
	add	r0, ip, #224	@,,
	bl	PQ_HAL_RegWrite	@
	ldr	r3, [r5, #0]	@ pVdpReg, pVdpReg
	add	r1, r3, #44544	@, pVdpReg,
	add	r0, r1, #224	@,,
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_VOFFSET,
	add	r0, r2, #44544	@, pVdpReg,
	bfi	r1, r6, #0, #16	@ WBC_DHD0_ZME_VOFFSET, s32PhaseC,,
	add	r0, r0, #224	@,,
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	VDP_WBC_SetZmePhaseV, .-VDP_WBC_SetZmePhaseV
	.align	2
	.global	ALG_VZmeVdpSRRegCfg
	.type	ALG_VZmeVdpSRRegCfg, %function
ALG_VZmeVdpSRRegCfg:
	.fnstart
.LFB695:
	@ args = 0, pretend = 0, frame = 0
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
	cmp	r0, #5	@ u32LayerId,
	mov	r4, r0	@ u32LayerId, u32LayerId
	subhi	r4, r0, #6	@ u32LayerId, u32LayerId,
	mov	r5, r1	@ pstZmeRtlPara, pstZmeRtlPara
	ldr	r1, [r1, #88]	@, <variable>.u32ZmeRatioHL
	mov	r0, r4	@, u32LayerId
	add	r6, r5, #132	@ D.25301, pstZmeRtlPara,
	bl	VDP_SR_SetZmeHorRatio	@
	mov	r0, r4	@, u32LayerId
	ldr	r1, [r5, #92]	@, <variable>.u32ZmeRatioVL
	bl	VDP_SR_SetZmeVerRatio	@
	mov	r0, r4	@, u32LayerId
	ldr	r1, [r5, #48]	@, <variable>.s32ZmeOffsetHL
	ldr	r2, [r5, #52]	@, <variable>.s32ZmeOffsetHC
	bl	VDP_SR_SetZmePhase	@
	mov	r0, r4	@, u32LayerId
	ldr	r1, [r5, #56]	@, <variable>.s32ZmeOffsetVL
	ldr	r2, [r5, #60]	@, <variable>.s32ZmeOffsetVC
	bl	VDP_WBC_SetZmePhaseV	@
	mov	r0, r4	@, u32LayerId
	ldr	r2, [r5, #0]	@, <variable>.bZmeEnHL
	mov	r1, #2	@,
	mov	r3, #1	@,
	bl	VDP_SR_SetZmeEnable	@
	mov	r0, r4	@, u32LayerId
	ldr	r2, [r5, #4]	@, <variable>.bZmeEnHC
	mov	r1, #3	@,
	mov	r3, #1	@,
	bl	VDP_SR_SetZmeEnable	@
	mov	r0, r4	@, u32LayerId
	ldr	r2, [r5, #8]	@, <variable>.bZmeEnVL
	mov	r1, #4	@,
	mov	r3, #1	@,
	bl	VDP_SR_SetZmeEnable	@
	mov	r3, #1	@,
	mov	r0, r4	@, u32LayerId
	ldr	r2, [r5, #12]	@, <variable>.bZmeEnVC
	mov	r1, #5	@,
	bl	VDP_SR_SetZmeEnable	@
	mov	r0, r4	@, u32LayerId
	ldr	r2, [r5, #32]	@, <variable>.bZmeMedHL
	mov	r1, #2	@,
	bl	VDP_SR_SetZmeMidEnable	@
	mov	r0, r4	@, u32LayerId
	ldr	r2, [r5, #36]	@, <variable>.bZmeMedHC
	mov	r1, #3	@,
	bl	VDP_SR_SetZmeMidEnable	@
	mov	r0, r4	@, u32LayerId
	ldr	r2, [r5, #40]	@, <variable>.bZmeMedVL
	mov	r1, #4	@,
	bl	VDP_SR_SetZmeMidEnable	@
	ldr	r2, [r5, #44]	@, <variable>.bZmeMedVC
	mov	r0, r4	@, u32LayerId
	mov	r1, #5	@,
	bl	VDP_SR_SetZmeMidEnable	@
	mov	r0, r4	@, u32LayerId
	ldr	r1, [r5, #104]	@, <variable>.bZmeOrder
	bl	VDP_SR_SetHfirOrder	@
	mov	r2, r6	@, D.25301
	mov	r0, r4	@, u32LayerId
	mov	r1, #0	@,
	bl	VDP_SR_SetZmeCoef	@
	mov	r0, r4	@, u32LayerId
	mov	r2, r6	@, D.25301
	mov	r1, #1	@,
	bl	VDP_SR_SetZmeCoef	@
	mov	r0, r4	@, u32LayerId
	mov	r1, #2	@,
	bl	VDP_SR_SetZmeInFmt	@
	mov	r0, r4	@, u32LayerId
	mov	r1, #2	@,
	bl	VDP_SR_SetZmeOutFmt	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	ALG_VZmeVdpSRRegCfg, .-ALG_VZmeVdpSRRegCfg
	.align	2
	.global	VDP_WBC_SetZmePhaseH
	.type	VDP_WBC_SetZmePhaseH, %function
VDP_WBC_SetZmePhaseH:
	.fnstart
.LFB672:
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
	mov	r4, r0	@ enLayer, enLayer
	mov	r7, r1	@ s32PhaseL, s32PhaseL
	mov	r6, r2	@ s32PhaseC, s32PhaseC
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp141,
	cmp	r4, #0	@ enLayer,
	movt	r5, #:upper16:.LANCHOR0	@ tmp141,
	str	r0, [r5, #0]	@ pVdpReg.233, pVdpReg
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	add	lr, r0, #44544	@, pVdpReg.233,
	add	r0, lr, #196	@,,
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ WBC_DHD0_ZME_HLOFFSET,
	ldr	r0, [r5, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r7, #0, #28	@ WBC_DHD0_ZME_HLOFFSET, s32PhaseL,,
	add	ip, r0, #44544	@, pVdpReg,
	add	r0, ip, #196	@,,
	bl	PQ_HAL_RegWrite	@
	ldr	r3, [r5, #0]	@ pVdpReg, pVdpReg
	add	r1, r3, #44544	@, pVdpReg,
	add	r0, r1, #200	@,,
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ WBC_DHD0_ZME_HCOFFSET,
	add	r0, r2, #44544	@, pVdpReg,
	bfi	r1, r6, #0, #28	@ WBC_DHD0_ZME_HCOFFSET, s32PhaseC,,
	add	r0, r0, #200	@,,
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	VDP_WBC_SetZmePhaseH, .-VDP_WBC_SetZmePhaseH
	.align	2
	.global	ALG_VZmeVdpWbcRegCfg
	.type	ALG_VZmeVdpWbcRegCfg, %function
ALG_VZmeVdpWbcRegCfg:
	.fnstart
.LFB683:
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
	cmp	r0, #4	@ u32LayerId,
	mov	r5, r0	@ u32LayerId, u32LayerId
	subhi	r5, r0, #5	@ u32LayerId, u32LayerId,
	mov	r4, r1	@ pstZmeRtlPara, pstZmeRtlPara
	ldr	r1, [r1, #88]	@, <variable>.u32ZmeRatioHL
	mov	r0, r5	@, u32LayerId
	bl	VDP_WBC_SetZmeHorRatio	@
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #92]	@, <variable>.u32ZmeRatioVL
	bl	VDP_WBC_SetZmeVerRatio	@
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #48]	@, <variable>.s32ZmeOffsetHL
	ldr	r2, [r4, #52]	@, <variable>.s32ZmeOffsetHC
	bl	VDP_WBC_SetZmePhaseH	@
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #56]	@, <variable>.s32ZmeOffsetVL
	ldr	r2, [r4, #60]	@, <variable>.s32ZmeOffsetVC
	bl	VDP_WBC_SetZmePhaseV	@
	mov	r0, r5	@, u32LayerId
	mov	r1, #2	@,
	ldr	r2, [r4, #0]	@, <variable>.bZmeEnHL
	ldr	r3, [r4, #16]	@, <variable>.bZmeMdHL
	bl	VDP_WBC_SetZmeEnable	@
	mov	r0, r5	@, u32LayerId
	mov	r1, #3	@,
	ldr	r2, [r4, #4]	@, <variable>.bZmeEnHC
	ldr	r3, [r4, #20]	@, <variable>.bZmeMdHC
	bl	VDP_WBC_SetZmeEnable	@
	mov	r0, r5	@, u32LayerId
	mov	r1, #4	@,
	ldr	r2, [r4, #8]	@, <variable>.bZmeEnVL
	ldr	r3, [r4, #24]	@, <variable>.bZmeMdVL
	bl	VDP_WBC_SetZmeEnable	@
	ldr	r3, [r4, #28]	@, <variable>.bZmeMdVC
	mov	r0, r5	@, u32LayerId
	mov	r1, #5	@,
	ldr	r2, [r4, #12]	@, <variable>.bZmeEnVC
	bl	VDP_WBC_SetZmeEnable	@
	mov	r0, #0	@,
	mov	r1, #2	@,
	ldr	r2, [r4, #32]	@, <variable>.bZmeMedHL
	bl	VDP_WBC_SetMidEnable	@
	mov	r0, #0	@,
	mov	r1, #3	@,
	ldr	r2, [r4, #36]	@, <variable>.bZmeMedHC
	bl	VDP_WBC_SetMidEnable	@
	mov	r0, #0	@,
	mov	r1, #4	@,
	ldr	r2, [r4, #40]	@, <variable>.bZmeMedVL
	bl	VDP_WBC_SetMidEnable	@
	mov	r0, #0	@,
	mov	r1, #5	@,
	ldr	r2, [r4, #44]	@, <variable>.bZmeMedVC
	bl	VDP_WBC_SetMidEnable	@
	mov	r0, #0	@,
	ldr	r1, [r4, #104]	@, <variable>.bZmeOrder
	bl	VDP_WBC_SetZmeHfirOrder	@
	ldr	r3, [r4, #88]	@ <variable>.u32ZmeRatioHL, <variable>.u32ZmeRatioHL
	cmp	r3, #0	@ <variable>.u32ZmeRatioHL,
	bne	.L371	@,
.L368:
	ldr	r0, [r4, #92]	@ <variable>.u32ZmeRatioVL, <variable>.u32ZmeRatioVL
	cmp	r0, #0	@ <variable>.u32ZmeRatioVL,
	beq	.L369	@,
	mov	r0, #0	@,
	mov	r1, #9	@,
	ldr	r3, [r4, #128]	@, <variable>.u32ZmeCoefAddrVC
	ldr	r2, [r4, #124]	@, <variable>.u32ZmeCoefAddrVL
	bl	VDP_WBC_SetZmeCoefAddr	@
	mov	r0, #0	@,
	mov	r1, #9	@,
	bl	VDP_WBC_SetParaUpd	@
.L369:
	mov	r0, #0	@,
	mov	r1, r0	@,
	bl	VDP_WBC_SetZmeInFmt	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L371:
	mov	r0, #0	@,
	mov	r1, #8	@,
	ldr	r2, [r4, #116]	@, <variable>.u32ZmeCoefAddrHL
	ldr	r3, [r4, #120]	@, <variable>.u32ZmeCoefAddrHC
	bl	VDP_WBC_SetZmeCoefAddr	@
	mov	r0, #0	@,
	mov	r1, #8	@,
	bl	VDP_WBC_SetParaUpd	@
	b	.L368	@
	.fnend
	.size	ALG_VZmeVdpWbcRegCfg, .-ALG_VZmeVdpWbcRegCfg
	.align	2
	.type	VDP_VID_SetZmeHorLumEn, %function
VDP_VID_SetZmeHorLumEn:
	.fnstart
.LFB654:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32bEnable, u32bEnable
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #4	@ u32Data,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.196, pVdpReg
	bhi	.L376	@,
	mov	r4, r4, asl #11	@ D.23968, u32Data,
	add	r1, r0, #2240	@ tmp141, pVdpReg.196,
	add	r0, r4, r1	@, D.23968, tmp141
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ V0_HSP,
	ldr	r0, [r5, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r6, #31, #1	@ V0_HSP, u32bEnable,,
	add	r3, r0, #2240	@ tmp144, pVdpReg,
	add	r0, r4, r3	@, D.23968, tmp144
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L376:
	movw	r0, #:lower16:.LC24	@,
	movt	r0, #:upper16:.LC24	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeHorLumEn, .-VDP_VID_SetZmeHorLumEn
	.align	2
	.type	VDP_VID_SetZmeVerLumEn, %function
VDP_VID_SetZmeVerLumEn:
	.fnstart
.LFB655:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32bEnable, u32bEnable
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #4	@ u32Data,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.198, pVdpReg
	bhi	.L381	@,
	add	ip, r0, #2256	@ tmp141, pVdpReg.198,
	mov	r4, r4, asl #11	@ D.23986, u32Data,
	add	r1, ip, #8	@ tmp141, tmp141,
	add	r0, r4, r1	@, D.23986, tmp141
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ V0_VSP,
	add	r0, r2, #2256	@ tmp145, pVdpReg,
	add	r3, r0, #8	@ tmp145, tmp145,
	bfi	r1, r6, #31, #1	@ V0_VSP, u32bEnable,,
	add	r0, r4, r3	@, D.23986, tmp145
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L381:
	movw	r0, #:lower16:.LC24	@,
	movt	r0, #:upper16:.LC24	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeVerLumEn, .-VDP_VID_SetZmeVerLumEn
	.align	2
	.type	VDP_VID_SetZmeHorChmEn, %function
VDP_VID_SetZmeHorChmEn:
	.fnstart
.LFB656:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32bEnable, u32bEnable
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #4	@ u32Data,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.200, pVdpReg
	bhi	.L386	@,
	mov	r4, r4, asl #11	@ D.24004, u32Data,
	add	r1, r0, #2240	@ tmp141, pVdpReg.200,
	add	r0, r4, r1	@, D.24004, tmp141
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ V0_HSP,
	ldr	r0, [r5, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r6, #30, #1	@ V0_HSP, u32bEnable,,
	add	r3, r0, #2240	@ tmp144, pVdpReg,
	add	r0, r4, r3	@, D.24004, tmp144
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L386:
	movw	r0, #:lower16:.LC24	@,
	movt	r0, #:upper16:.LC24	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeHorChmEn, .-VDP_VID_SetZmeHorChmEn
	.align	2
	.type	VDP_VID_SetZmeVerChmEn, %function
VDP_VID_SetZmeVerChmEn:
	.fnstart
.LFB657:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32bEnable, u32bEnable
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #4	@ u32Data,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.202, pVdpReg
	bhi	.L391	@,
	add	ip, r0, #2256	@ tmp141, pVdpReg.202,
	mov	r4, r4, asl #11	@ D.24022, u32Data,
	add	r1, ip, #8	@ tmp141, tmp141,
	add	r0, r4, r1	@, D.24022, tmp141
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ V0_VSP,
	add	r0, r2, #2256	@ tmp145, pVdpReg,
	add	r3, r0, #8	@ tmp145, tmp145,
	bfi	r1, r6, #30, #1	@ V0_VSP, u32bEnable,,
	add	r0, r4, r3	@, D.24022, tmp145
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L391:
	movw	r0, #:lower16:.LC24	@,
	movt	r0, #:upper16:.LC24	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeVerChmEn, .-VDP_VID_SetZmeVerChmEn
	.align	2
	.global	VDP_VID_SetZmeOutFmt
	.type	VDP_VID_SetZmeOutFmt, %function
VDP_VID_SetZmeOutFmt:
	.fnstart
.LFB670:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32Fmt, u32Fmt
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #4	@ u32Data,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.231, pVdpReg
	bhi	.L396	@,
	add	ip, r0, #2256	@ tmp141, pVdpReg.231,
	mov	r4, r4, asl #11	@ D.24288, u32Data,
	add	r1, ip, #8	@ tmp141, tmp141,
	add	r0, r4, r1	@, D.24288, tmp141
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ V0_VSP,
	add	r0, r2, #2256	@ tmp145, pVdpReg,
	add	r3, r0, #8	@ tmp145, tmp145,
	bfi	r1, r6, #21, #2	@ V0_VSP, u32Fmt,,
	add	r0, r4, r3	@, D.24288, tmp145
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L396:
	movw	r0, #:lower16:.LC25	@,
	movt	r0, #:upper16:.LC25	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeOutFmt, .-VDP_VID_SetZmeOutFmt
	.align	2
	.global	VDP_VID_SetZmeInFmt
	.type	VDP_VID_SetZmeInFmt, %function
VDP_VID_SetZmeInFmt:
	.fnstart
.LFB669:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32Fmt, u32Fmt
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #4	@ u32Data,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.229, pVdpReg
	bhi	.L401	@,
	add	ip, r0, #2256	@ tmp141, pVdpReg.229,
	mov	r4, r4, asl #11	@ D.24271, u32Data,
	add	r1, ip, #8	@ tmp141, tmp141,
	add	r0, r4, r1	@, D.24271, tmp141
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ V0_VSP,
	add	r0, r2, #2256	@ tmp145, pVdpReg,
	add	r3, r0, #8	@ tmp145, tmp145,
	bfi	r1, r6, #19, #2	@ V0_VSP, u32Fmt,,
	add	r0, r4, r3	@, D.24271, tmp145
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L401:
	movw	r0, #:lower16:.LC25	@,
	movt	r0, #:upper16:.LC25	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeInFmt, .-VDP_VID_SetZmeInFmt
	.align	2
	.global	VDP_VID_SetParaUpd
	.type	VDP_VID_SetParaUpd, %function
VDP_VID_SetParaUpd:
	.fnstart
.LFB668:
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r7, r1	@ enMode, enMode
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp152,
	cmp	r4, #4	@ u32Data,
	movt	r5, #:upper16:.LANCHOR0	@ tmp152,
	str	r0, [r5, #0]	@ pVdpReg.227, pVdpReg
	bhi	.L409	@,
	add	r0, r0, #2112	@ tmp141, pVdpReg.227,
	mov	r4, r4, asl #11	@ D.24250, u32Data,
	add	r0, r4, r0	@, D.24250, tmp141
	bl	PQ_HAL_RegRead	@
	cmp	r7, #4	@ enMode,
	mov	r6, r0	@ prephitmp.1821,
	orreq	r6, r0, #3	@ prephitmp.1821, prephitmp.1821,
	beq	.L406	@,
	cmp	r7, #5	@ enMode,
	orreq	r6, r6, #12	@ prephitmp.1821, prephitmp.1821,
	bne	.L410	@,
.L406:
	ldr	r3, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r6	@, prephitmp.1821
	add	r2, r3, #2112	@ tmp149, pVdpReg,
	add	r0, r4, r2	@, D.24250, tmp149
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L409:
	movw	r0, #:lower16:.LC26	@,
	movt	r0, #:upper16:.LC26	@,
	bl	printk	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L410:
	movw	r0, #:lower16:.LC27	@,
	movt	r0, #:upper16:.LC27	@,
	bl	printk	@
	b	.L406	@
	.fnend
	.size	VDP_VID_SetParaUpd, .-VDP_VID_SetParaUpd
	.align	2
	.global	VDP_VID_SetZmeCoefAddr
	.type	VDP_VID_SetZmeCoefAddr, %function
VDP_VID_SetZmeCoefAddr:
	.fnstart
.LFB667:
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r5, r1	@ u32Mode, u32Mode
	mov	r8, r2	@ u32LAddr, u32LAddr
	mov	r7, r3	@ u32CAddr, u32CAddr
	bl	PQ_HAL_GetVdpReg	@
	movw	r6, #:lower16:.LANCHOR0	@ tmp148,
	cmp	r4, #4	@ u32Data,
	movt	r6, #:upper16:.LANCHOR0	@ tmp148,
	str	r0, [r6, #0]	@ pVdpReg.225, pVdpReg
	bhi	.L417	@,
	cmp	r5, #4	@ u32Mode,
	beq	.L418	@,
	cmp	r5, #5	@ u32Mode,
	bne	.L415	@,
	add	r1, r0, #2128	@ tmp166, pVdpReg.225,
	mov	r4, r4, asl #11	@ temp.1866, u32Data,
	add	lr, r1, #8	@ tmp166, tmp166,
	add	r0, r4, lr	@, temp.1866, tmp166
	bl	PQ_HAL_RegRead	@
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r8	@, u32LAddr
	add	r2, r3, #2128	@ tmp170, pVdpReg,
	add	r0, r2, #8	@ tmp170, tmp170,
	add	r0, r4, r0	@, temp.1866, tmp170
	bl	PQ_HAL_RegWrite	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	add	r3, ip, #2128	@ tmp175, pVdpReg,
	add	r1, r3, #12	@ tmp175, tmp175,
	add	r0, r4, r1	@, temp.1866, tmp175
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r7	@, u32CAddr
	add	r0, r2, #2128	@ tmp180, pVdpReg,
	add	ip, r0, #12	@ tmp180, tmp180,
	add	r0, r4, ip	@, temp.1866, tmp180
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L418:
	mov	r4, r4, asl #11	@ D.24216, u32Data,
	add	lr, r0, #2128	@ tmp150, pVdpReg.225,
	add	r0, r4, lr	@, D.24216, tmp150
	bl	PQ_HAL_RegRead	@
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r8	@, u32LAddr
	add	r2, r3, #2128	@ tmp153, pVdpReg,
	add	r0, r4, r2	@, D.24216, tmp153
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r0, #2128	@ tmp157, pVdpReg,
	add	r1, ip, #4	@ tmp157, tmp157,
	add	r0, r4, r1	@, D.24216, tmp157
	bl	PQ_HAL_RegRead	@
	ldr	r3, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r7	@, u32CAddr
	add	r2, r3, #2128	@ tmp162, pVdpReg,
	add	r0, r2, #4	@ tmp162, tmp162,
	add	r0, r4, r0	@, D.24216, tmp162
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L415:
	movw	r0, #:lower16:.LC29	@,
	movt	r0, #:upper16:.LC29	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L417:
	movw	r0, #:lower16:.LC28	@,
	movt	r0, #:upper16:.LC28	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeCoefAddr, .-VDP_VID_SetZmeCoefAddr
	.align	2
	.global	VDP_VID_SetZmeHfirOrder
	.type	VDP_VID_SetZmeHfirOrder, %function
VDP_VID_SetZmeHfirOrder:
	.fnstart
.LFB666:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32HfirOrder, u32HfirOrder
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #4	@ u32Data,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.223, pVdpReg
	bhi	.L423	@,
	mov	r4, r4, asl #11	@ D.24192, u32Data,
	add	r1, r0, #2240	@ tmp141, pVdpReg.223,
	add	r0, r4, r1	@, D.24192, tmp141
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ V0_HSP,
	ldr	r0, [r5, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r6, #24, #1	@ V0_HSP, u32HfirOrder,,
	add	r3, r0, #2240	@ tmp144, pVdpReg,
	add	r0, r4, r3	@, D.24192, tmp144
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L423:
	movw	r0, #:lower16:.LC30	@,
	movt	r0, #:upper16:.LC30	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeHfirOrder, .-VDP_VID_SetZmeHfirOrder
	.align	2
	.global	VDP_VID_SetZmeVerRatio
	.type	VDP_VID_SetZmeVerRatio, %function
VDP_VID_SetZmeVerRatio:
	.fnstart
.LFB665:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32Ratio, u32Ratio
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #4	@ u32Data,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.221, pVdpReg
	bhi	.L428	@,
	add	ip, r0, #2256	@ tmp141, pVdpReg.221,
	mov	r4, r4, asl #11	@ D.24176, u32Data,
	add	r1, ip, #12	@ tmp141, tmp141,
	add	r0, r4, r1	@, D.24176, tmp141
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ V0_VSR,
	add	r0, r2, #2256	@ tmp145, pVdpReg,
	add	r3, r0, #12	@ tmp145, tmp145,
	bfi	r1, r6, #0, #16	@ V0_VSR, u32Ratio,,
	add	r0, r4, r3	@, D.24176, tmp145
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L428:
	movw	r0, #:lower16:.LC31	@,
	movt	r0, #:upper16:.LC31	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeVerRatio, .-VDP_VID_SetZmeVerRatio
	.align	2
	.global	VDP_VID_SetZmeHorRatio
	.type	VDP_VID_SetZmeHorRatio, %function
VDP_VID_SetZmeHorRatio:
	.fnstart
.LFB664:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32Ratio, u32Ratio
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp139,
	cmp	r4, #4	@ u32Data,
	movt	r5, #:upper16:.LANCHOR0	@ tmp139,
	str	r0, [r5, #0]	@ pVdpReg.218, pVdpReg
	bhi	.L433	@,
	mov	r4, r4, asl #11	@ D.24160, u32Data,
	add	r1, r0, #2240	@ tmp141, pVdpReg.218,
	add	r0, r4, r1	@, D.24160, tmp141
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ V0_HSP,
	ldr	r0, [r5, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r6, #0, #24	@ V0_HSP, u32Ratio,,
	add	r3, r0, #2240	@ tmp144, pVdpReg,
	add	r0, r4, r3	@, D.24160, tmp144
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L433:
	movw	r0, #:lower16:.LC32	@,
	movt	r0, #:upper16:.LC32	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeHorRatio, .-VDP_VID_SetZmeHorRatio
	.align	2
	.global	VDP_VID_SetZmeMidEnable2
	.type	VDP_VID_SetZmeMidEnable2, %function
VDP_VID_SetZmeMidEnable2:
	.fnstart
.LFB662:
	@ args = 0, pretend = 0, frame = 0
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
	mov	r5, r0	@ u32Data, u32Data
	mov	r6, r1	@ u32bEnable, u32bEnable
	bl	PQ_HAL_GetVdpReg	@
	movw	r4, #:lower16:.LANCHOR0	@ tmp142,
	cmp	r5, #4	@ u32Data,
	movt	r4, #:upper16:.LANCHOR0	@ tmp142,
	str	r0, [r4, #0]	@ pVdpReg.216, pVdpReg
	bhi	.L438	@,
	mov	r5, r5, asl #11	@ D.24134, u32Data,
	add	lr, r0, #2240	@ tmp144, pVdpReg.216,
	add	r0, r5, lr	@, D.24134, tmp144
	and	r6, r6, #1	@ D.24138, u32bEnable,
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ V0_HSP,
	ldr	r0, [r4, #0]	@ pVdpReg, pVdpReg
	bfi	r1, r6, #29, #1	@ V0_HSP, D.24138,,
	add	r2, r0, #2240	@ tmp149, pVdpReg,
	bfi	r1, r6, #28, #1	@ V0_HSP, D.24138,,
	add	r0, r5, r2	@, D.24134, tmp149
	bl	PQ_HAL_RegWrite	@
	ldr	r3, [r4, #0]	@ pVdpReg, pVdpReg
	add	ip, r3, #2256	@ tmp153, pVdpReg,
	add	r1, ip, #8	@ tmp153, tmp153,
	add	r0, r5, r1	@, D.24134, tmp153
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r4, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ V0_VSP,
	add	r0, r2, #2256	@ tmp158, pVdpReg,
	bfi	r1, r6, #29, #1	@ V0_VSP, D.24138,,
	add	r3, r0, #8	@ tmp158, tmp158,
	bfi	r1, r6, #28, #1	@ V0_VSP, D.24138,,
	add	r0, r5, r3	@, D.24134, tmp158
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L438:
	movw	r0, #:lower16:.LC33	@,
	movt	r0, #:upper16:.LC33	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeMidEnable2, .-VDP_VID_SetZmeMidEnable2
	.align	2
	.global	VDP_VID_SetZmeFirEnable2
	.type	VDP_VID_SetZmeFirEnable2, %function
VDP_VID_SetZmeFirEnable2:
	.fnstart
.LFB661:
	@ args = 4, pretend = 0, frame = 0
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r5, r1	@ u32bEnableHl, u32bEnableHl
	mov	r8, r2	@ u32bEnableHc, u32bEnableHc
	mov	r7, r3	@ u32bEnableVl, u32bEnableVl
	bl	PQ_HAL_GetVdpReg	@
	movw	r6, #:lower16:.LANCHOR0	@ tmp144,
	cmp	r4, #4	@ u32Data,
	movt	r6, #:upper16:.LANCHOR0	@ tmp144,
	str	r0, [r6, #0]	@ pVdpReg.214, pVdpReg
	bhi	.L443	@,
	mov	r4, r4, asl #11	@ D.24105, u32Data,
	add	lr, r0, #2240	@ tmp146, pVdpReg.214,
	add	r0, r4, lr	@, D.24105, tmp146
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	add	ip, r2, #2240	@ tmp149, pVdpReg,
	mov	r1, r0	@ V0_HSP,
	bfi	r1, r5, #26, #1	@ V0_HSP, u32bEnableHl,,
	add	r0, r4, ip	@, D.24105, tmp149
	bfi	r1, r8, #25, #1	@ V0_HSP, u32bEnableHc,,
	bl	PQ_HAL_RegWrite	@
	ldr	r0, [r6, #0]	@ pVdpReg, pVdpReg
	add	r3, r0, #2256	@ tmp153, pVdpReg,
	add	r1, r3, #8	@ tmp153, tmp153,
	add	r0, r4, r1	@, D.24105, tmp153
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r6, #0]	@ pVdpReg, pVdpReg
	ldr	r2, [fp, #4]	@ u32bEnableVc, u32bEnableVc
	mov	r1, r0	@ V0_VSP,
	add	r0, ip, #2256	@ tmp158, pVdpReg,
	bfi	r1, r7, #24, #1	@ V0_VSP, u32bEnableVl,,
	add	r3, r0, #8	@ tmp158, tmp158,
	bfi	r1, r2, #23, #1	@ V0_VSP, u32bEnableVc,,
	add	r0, r4, r3	@, D.24105, tmp158
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L443:
	movw	r0, #:lower16:.LC34	@,
	movt	r0, #:upper16:.LC34	@,
	bl	printk	@
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmeFirEnable2, .-VDP_VID_SetZmeFirEnable2
	.align	2
	.global	VDP_VID_SetZmePhaseVB
	.type	VDP_VID_SetZmePhaseVB, %function
VDP_VID_SetZmePhaseVB:
	.fnstart
.LFB660:
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r5, r1	@ s32PhaseL, s32PhaseL
	mov	r7, r2	@ s32PhaseC, s32PhaseC
	bl	PQ_HAL_GetVdpReg	@
	movw	r6, #:lower16:.LANCHOR0	@ tmp140,
	cmp	r4, #4	@ u32Data,
	movt	r6, #:upper16:.LANCHOR0	@ tmp140,
	str	r0, [r6, #0]	@ pVdpReg.212, pVdpReg
	bhi	.L448	@,
	add	ip, r0, #2272	@ tmp142, pVdpReg.212,
	mov	r4, r4, asl #11	@ D.24084, u32Data,
	add	r1, ip, #4	@ tmp142, tmp142,
	add	r0, r4, r1	@, D.24084, tmp142
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ V0_VBOFFSET,
	add	r0, r2, #2272	@ tmp146, pVdpReg,
	bfi	r1, r5, #16, #16	@ V0_VBOFFSET, s32PhaseL,,
	add	r3, r0, #4	@ tmp146, tmp146,
	bfi	r1, r7, #0, #16	@ V0_VBOFFSET, s32PhaseC,,
	add	r0, r4, r3	@, D.24084, tmp146
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L448:
	movw	r0, #:lower16:.LC35	@,
	movt	r0, #:upper16:.LC35	@,
	bl	printk	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmePhaseVB, .-VDP_VID_SetZmePhaseVB
	.align	2
	.global	VDP_VID_SetZmePhaseV
	.type	VDP_VID_SetZmePhaseV, %function
VDP_VID_SetZmePhaseV:
	.fnstart
.LFB659:
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r5, r1	@ s32PhaseL, s32PhaseL
	mov	r7, r2	@ s32PhaseC, s32PhaseC
	bl	PQ_HAL_GetVdpReg	@
	movw	r6, #:lower16:.LANCHOR0	@ tmp140,
	cmp	r4, #4	@ u32Data,
	movt	r6, #:upper16:.LANCHOR0	@ tmp140,
	str	r0, [r6, #0]	@ pVdpReg.210, pVdpReg
	bhi	.L453	@,
	mov	r4, r4, asl #11	@ D.24066, u32Data,
	add	r1, r0, #2272	@ tmp142, pVdpReg.210,
	add	r0, r4, r1	@, D.24066, tmp142
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r6, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ V0_VOFFSET,
	add	r0, r2, #2272	@ tmp145, pVdpReg,
	bfi	r1, r5, #16, #16	@ V0_VOFFSET, s32PhaseL,,
	add	r0, r4, r0	@, D.24066, tmp145
	bfi	r1, r7, #0, #16	@ V0_VOFFSET, s32PhaseC,,
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L453:
	movw	r0, #:lower16:.LC35	@,
	movt	r0, #:upper16:.LC35	@,
	bl	printk	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmePhaseV, .-VDP_VID_SetZmePhaseV
	.align	2
	.global	VDP_VID_SetZmePhaseH
	.type	VDP_VID_SetZmePhaseH, %function
VDP_VID_SetZmePhaseH:
	.fnstart
.LFB658:
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
	mov	r4, r0	@ u32Data, u32Data
	mov	r7, r1	@ s32PhaseL, s32PhaseL
	mov	r6, r2	@ s32PhaseC, s32PhaseC
	bl	PQ_HAL_GetVdpReg	@
	movw	r5, #:lower16:.LANCHOR0	@ tmp142,
	cmp	r4, #4	@ u32Data,
	movt	r5, #:upper16:.LANCHOR0	@ tmp142,
	str	r0, [r5, #0]	@ pVdpReg.204, pVdpReg
	bhi	.L458	@,
	add	r1, r0, #2240	@ tmp144, pVdpReg.204,
	mov	r4, r4, asl #11	@ D.24041, u32Data,
	add	lr, r1, #4	@ tmp144, tmp144,
	add	r0, r4, lr	@, D.24041, tmp144
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ V0_HLOFFSET,
	add	r0, ip, #2240	@ tmp148, pVdpReg,
	add	r2, r0, #4	@ tmp148, tmp148,
	bfi	r1, r7, #0, #28	@ V0_HLOFFSET, s32PhaseL,,
	add	r0, r4, r2	@, D.24041, tmp148
	bl	PQ_HAL_RegWrite	@
	ldr	r3, [r5, #0]	@ pVdpReg, pVdpReg
	add	ip, r3, #2240	@ tmp153, pVdpReg,
	add	r1, ip, #8	@ tmp153, tmp153,
	add	r0, r4, r1	@, D.24041, tmp153
	bl	PQ_HAL_RegRead	@
	ldr	r2, [r5, #0]	@ pVdpReg, pVdpReg
	mov	r1, r0	@ V0_HCOFFSET,
	add	r0, r2, #2240	@ tmp158, pVdpReg,
	add	r3, r0, #8	@ tmp158, tmp158,
	bfi	r1, r6, #0, #28	@ V0_HCOFFSET, s32PhaseC,,
	add	r0, r4, r3	@, D.24041, tmp158
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L458:
	movw	r0, #:lower16:.LC35	@,
	movt	r0, #:upper16:.LC35	@,
	bl	printk	@
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	VDP_VID_SetZmePhaseH, .-VDP_VID_SetZmePhaseH
	.align	2
	.global	ALG_VZmeVdpRegCfg
	.type	ALG_VZmeVdpRegCfg, %function
ALG_VZmeVdpRegCfg:
	.fnstart
.LFB671:
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
	mov	r4, r1	@ pstZmeRtlPara, pstZmeRtlPara
	mov	r5, r0	@ u32LayerId, u32LayerId
	ldr	r1, [r1, #88]	@, <variable>.u32ZmeRatioHL
	mov	r6, r2	@ bFirEnable, bFirEnable
	bl	VDP_VID_SetZmeHorRatio	@
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #92]	@, <variable>.u32ZmeRatioVL
	bl	VDP_VID_SetZmeVerRatio	@
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #48]	@, <variable>.s32ZmeOffsetHL
	ldr	r2, [r4, #52]	@, <variable>.s32ZmeOffsetHC
	bl	VDP_VID_SetZmePhaseH	@
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #56]	@, <variable>.s32ZmeOffsetVL
	ldr	r2, [r4, #60]	@, <variable>.s32ZmeOffsetVC
	bl	VDP_VID_SetZmePhaseV	@
	ldr	r2, [r4, #68]	@, <variable>.s32ZmeOffsetVCBtm
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #64]	@, <variable>.s32ZmeOffsetVLBtm
	bl	VDP_VID_SetZmePhaseVB	@
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #32]	@, <variable>.bZmeMedHL
	bl	VDP_VID_SetZmeMidEnable2	@
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #104]	@, <variable>.bZmeOrder
	bl	VDP_VID_SetZmeHfirOrder	@
	ldr	r3, [r4, #16]	@ <variable>.bZmeMdHL, <variable>.bZmeMdHL
	cmp	r3, #0	@ <variable>.bZmeMdHL,
	bne	.L460	@,
	ldr	r1, [r4, #20]	@ <variable>.bZmeMdHC, <variable>.bZmeMdHC
	cmp	r1, #0	@ <variable>.bZmeMdHC,
	bne	.L460	@,
.L461:
	ldr	lr, [r4, #24]	@ <variable>.bZmeMdVL, <variable>.bZmeMdVL
	cmp	lr, #0	@ <variable>.bZmeMdVL,
	bne	.L462	@,
	ldr	r3, [r4, #28]	@ <variable>.bZmeMdVC, <variable>.bZmeMdVC
	cmp	r3, #0	@ <variable>.bZmeMdVC,
	bne	.L462	@,
.L463:
	cmp	r6, #0	@ bFirEnable,
	ldr	r1, [r4, #16]	@ <variable>.bZmeMdHL, <variable>.bZmeMdHL
	ldrne	ip, [r4, #28]	@ <variable>.bZmeMdVC, <variable>.bZmeMdVC
	moveq	r3, r6	@, bFirEnable
	ldreq	r2, [r4, #20]	@ <variable>.bZmeMdHC, <variable>.bZmeMdHC
	moveq	r0, r5	@, u32LayerId
	ldrne	r2, [r4, #20]	@ <variable>.bZmeMdHC, <variable>.bZmeMdHC
	movne	r0, r5	@, u32LayerId
	ldrne	r3, [r4, #24]	@ <variable>.bZmeMdVL, <variable>.bZmeMdVL
	streq	r6, [sp, #0]	@ bFirEnable,
	strne	ip, [sp, #0]	@ <variable>.bZmeMdVC,
	bl	VDP_VID_SetZmeFirEnable2	@
	cmp	r5, #1	@ u32LayerId,
	beq	.L470	@,
.L466:
	ldrb	r1, [r4, #112]	@ zero_extendqisi2	@, <variable>.u8ZmeYCFmtIn
	mov	r0, r5	@, u32LayerId
	bl	VDP_VID_SetZmeInFmt	@
	mov	r0, r5	@, u32LayerId
	ldrb	r1, [r4, #113]	@ zero_extendqisi2	@, <variable>.u8ZmeYCFmtOut
	bl	VDP_VID_SetZmeOutFmt	@
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #8]	@, <variable>.bZmeEnVL
	bl	VDP_VID_SetZmeHorLumEn	@
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #8]	@, <variable>.bZmeEnVL
	bl	VDP_VID_SetZmeVerLumEn	@
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #8]	@, <variable>.bZmeEnVL
	bl	VDP_VID_SetZmeHorChmEn	@
	mov	r0, r5	@, u32LayerId
	ldr	r1, [r4, #8]	@, <variable>.bZmeEnVL
	bl	VDP_VID_SetZmeVerChmEn	@
.L469:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L462:
	mov	r0, r5	@, u32LayerId
	mov	r1, #5	@,
	ldr	r2, [r4, #124]	@, <variable>.u32ZmeCoefAddrVL
	ldr	r3, [r4, #128]	@, <variable>.u32ZmeCoefAddrVC
	bl	VDP_VID_SetZmeCoefAddr	@
	mov	r0, r5	@, u32LayerId
	mov	r1, #5	@,
	bl	VDP_VID_SetParaUpd	@
	b	.L463	@
.L460:
	mov	r0, r5	@, u32LayerId
	mov	r1, #4	@,
	ldr	r2, [r4, #116]	@, <variable>.u32ZmeCoefAddrHL
	ldr	r3, [r4, #120]	@, <variable>.u32ZmeCoefAddrHC
	bl	VDP_VID_SetZmeCoefAddr	@
	mov	r0, r5	@, u32LayerId
	mov	r1, #4	@,
	bl	VDP_VID_SetParaUpd	@
	b	.L461	@
.L470:
	ldrh	r6, [r4, #112]	@ tmp161,
	cmp	r6, #0	@ tmp161,
	bne	.L466	@,
	mov	r0, r5	@, u32LayerId
	mov	r1, r6	@, tmp161
	bl	VDP_VID_SetZmeInFmt	@
	mov	r0, r5	@, u32LayerId
	mov	r1, r6	@, tmp161
	bl	VDP_VID_SetZmeOutFmt	@
	mov	r0, r5	@, u32LayerId
	mov	r1, r6	@, tmp161
	bl	VDP_VID_SetZmeHorLumEn	@
	mov	r0, r5	@, u32LayerId
	mov	r1, r6	@, tmp161
	bl	VDP_VID_SetZmeVerLumEn	@
	mov	r0, r5	@, u32LayerId
	mov	r1, r6	@, tmp161
	bl	VDP_VID_SetZmeHorChmEn	@
	mov	r0, r5	@, u32LayerId
	mov	r1, r6	@, tmp161
	bl	VDP_VID_SetZmeVerChmEn	@
	b	.L469	@
	.fnend
	.size	ALG_VZmeVdpRegCfg, .-ALG_VZmeVdpRegCfg
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"Error,VPSS_REG_SetZmeCoefAddr error\012\000"
	.space	3
.LC1:
	.ascii	"Error,VPSS_REG_SetZmeOutFmt error\012\000"
	.space	1
.LC2:
	.ascii	"Error,VPSS_REG_SetZmeInFmt error\012\000"
	.space	2
.LC3:
	.ascii	"Error,VPSS_REG_SetZmeHfirOrder error\012\000"
	.space	2
.LC4:
	.ascii	"Error,VPSS_REG_SetZmeRatio error\012\000"
	.space	2
.LC5:
	.ascii	"Error,VPSS_REG_SetZmePhase error\012\000"
	.space	2
.LC6:
	.ascii	"Error,VPSS_REG_SetZmeMidEnable error\012\000"
	.space	2
.LC7:
	.ascii	"Error,VPSS_REG_SetZmeFirEnable error\012\000"
	.space	2
.LC8:
	.ascii	"Error,VPSS_REG_SetZmeOutSize error\012\000"
.LC9:
	.ascii	"Error,VPSS_REG_SetZmeInSize error\012\000"
	.space	1
.LC10:
	.ascii	"Error,VPSS_REG_SetZmeEnable error\012\000"
	.space	1
.LC11:
	.ascii	"Error,VDP_SR_SetZmeCoefAddr() Select Wrong Video La"
	.ascii	"yer ID\012\000"
	.space	1
.LC12:
	.ascii	"Error,VDP_SR_SetZmeCoefAddr() Select a Wrong Mode!\012"
	.ascii	"\000"
.LC13:
	.ascii	"Error,VDP_SR_SetHfirOrder() Select Wrong Video Laye"
	.ascii	"r ID\012\000"
	.space	3
.LC14:
	.ascii	"Error,VDP_SR_SetZmeOutFmt() Select Wrong Video Laye"
	.ascii	"r ID\012\000"
	.space	3
.LC15:
	.ascii	"Error,VDP_SR_SetZmeInFmt() Select Wrong Video Layer"
	.ascii	" ID\012\000"
.LC16:
	.ascii	"Error,VDP_SR_SetZmeMidEnable() Select Wrong Video L"
	.ascii	"ayer ID\012\000"
.LC17:
	.ascii	"Error,VDP_SR_SetZmeFirEnable() Select Wrong Video L"
	.ascii	"ayer ID\012\000"
.LC18:
	.ascii	"Error,VDP_SR_SetZmePhase() Select Wrong Video Layer"
	.ascii	" ID\012\000"
.LC19:
	.ascii	"Error,VDP_SR_SetZmeEnable() Select Wrong Video Laye"
	.ascii	"r ID\012\000"
	.space	3
.LC20:
	.ascii	"Error,VDP_SR_SetZmeVerRatio() Select Wrong Video La"
	.ascii	"yer ID\012\000"
	.space	1
.LC21:
	.ascii	"Error,VDP_SR_SetZmeHorRatio() Select Wrong Video La"
	.ascii	"yer ID\012\000"
	.space	1
.LC22:
	.ascii	"error,VDP_WBC_DHD0_SetParaUpd() select wrong mode!\012"
	.ascii	"\000"
.LC23:
	.ascii	"Error,VDP_WBC_SetZmeCoefAddr() Select a Wrong Mode!"
	.ascii	"\012\000"
	.space	3
.LC24:
	.ascii	"Error,VDP_VID_SetZmeEnable() Select Wrong Video Lay"
	.ascii	"er ID\012\000"
	.space	2
.LC25:
	.ascii	"Error,VDP_VID_SetZmeInFmt() Select Wrong Video Laye"
	.ascii	"r ID\012\000"
	.space	3
.LC26:
	.ascii	"error,VDP_VID_SetParaUpd() select wrong video layer"
	.ascii	" id\012\000"
.LC27:
	.ascii	"error,VDP_VID_SetParaUpd() select wrong mode!\012\000"
	.space	1
.LC28:
	.ascii	"Error,VDP_VID_SetZmeCoefAddr() Select Wrong Video L"
	.ascii	"ayer ID\012\000"
.LC29:
	.ascii	"Error,VDP_VID_SetZmeCoefAddr() Select a Wrong Mode!"
	.ascii	"\012\000"
	.space	3
.LC30:
	.ascii	"Error,VDP_VID_SetZmeHfirOrder() Select Wrong Video "
	.ascii	"Layer ID\012\000"
	.space	3
.LC31:
	.ascii	"Error,VDP_VID_SetZmeVerRatio() Select Wrong Video L"
	.ascii	"ayer ID\012\000"
.LC32:
	.ascii	"Error,VDP_VID_SetZmeHorRatio() Select Wrong Video L"
	.ascii	"ayer ID\012\000"
.LC33:
	.ascii	"Error,VDP_VID_SetZmeMidEnable() Select Wrong Video "
	.ascii	"Layer ID\012\000"
	.space	3
.LC34:
	.ascii	"Error,VDP_VID_SetZmeFirEnable() Select Wrong Video "
	.ascii	"Layer ID\012\000"
	.space	3
.LC35:
	.ascii	"Error,VDP_VID_SetZmePhase() Select Wrong Video Laye"
	.ascii	"r ID\012\000"
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	pVdpReg, %object
	.size	pVdpReg, 4
pVdpReg:
	.space	4
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
