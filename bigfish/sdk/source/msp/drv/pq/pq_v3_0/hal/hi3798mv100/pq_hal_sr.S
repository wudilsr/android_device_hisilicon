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
	.file	"pq_hal_sr.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_hal_sr)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/hal/hi3798mv100/.pq_hal_sr.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_sr.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_sr.o -O2 -Wall -Wundef
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
	.global	PQ_HAL_GetSRParam
	.type	PQ_HAL_GetSRParam, %function
PQ_HAL_GetSRParam:
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
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_HAL_GetSRParam, .-PQ_HAL_GetSRParam
	.align	2
	.global	PQ_HAL_SetSRSpMode
	.type	PQ_HAL_SetSRSpMode, %function
PQ_HAL_SetSRSpMode:
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
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r5, r1	@ eHsh_nodir, eHsh_nodir
	mov	r4, r0	@ u32ChId, u32ChId
	bl	PQ_HAL_GetVdpReg	@
	add	r1, r0, #3472	@ tmp140,,
	add	r0, r1, #4	@ tmp140, tmp140,
	add	r4, r0, r4, asl #11	@, D.23397, tmp140, u32ChId,
	mov	r0, r4	@, D.23397
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ SR_SHARP_EN,
	mov	r0, r4	@, D.23397
	bfi	r1, r5, #30, #1	@ SR_SHARP_EN, eHsh_nodir,,
	bl	PQ_HAL_RegWrite	@
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	PQ_HAL_SetSRSpMode, .-PQ_HAL_SetSRSpMode
	.align	2
	.global	PQ_HAL_SR_EnZme
	.type	PQ_HAL_SR_EnZme, %function
PQ_HAL_SR_EnZme:
	.fnstart
.LFB658:
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
	cmp	r0, #4	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	mov	r5, r1	@ enZme, enZme
	bls	.L6	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	mov	r3, #195	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
.L8:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L6:
	bl	PQ_HAL_GetVdpReg	@
	add	r0, r0, #3456	@ tmp142,,
	add	r4, r0, r4, asl #11	@, D.23382, tmp142, u32ChId,
	mov	r0, r4	@, D.23382
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ SR_CTRL,
	mov	r0, r4	@, D.23382
	bfi	r1, r5, #29, #2	@ SR_CTRL, enZme,,
	bl	PQ_HAL_RegWrite	@
	b	.L8	@
	.fnend
	.size	PQ_HAL_SR_EnZme, .-PQ_HAL_SR_EnZme
	.align	2
	.global	PQ_HAL_EnableSR
	.type	PQ_HAL_EnableSR, %function
PQ_HAL_EnableSR:
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
	cmp	r0, #4	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	mov	r5, r1	@ bOnOff, bOnOff
	bls	.L11	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L14	@,
	mov	r3, #166	@,
	movw	ip, #:lower16:.LC0	@ tmp141,
	movt	ip, #:upper16:.LC0	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
.L13:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L11:
	bl	PQ_HAL_GetVdpReg	@
	add	r0, r0, #3456	@ tmp143,,
	add	r4, r0, r4, asl #11	@, D.23361, tmp143, u32ChId,
	mov	r0, r4	@, D.23361
	bl	PQ_HAL_RegRead	@
	mov	r1, r0	@ SR_CTRL,
	mov	r0, r4	@, D.23361
	bfi	r1, r5, #31, #1	@ SR_CTRL, bOnOff,,
	bl	PQ_HAL_RegWrite	@
	b	.L13	@
.L15:
	.align	2
.L14:
	.word	.LANCHOR0+16
	.fnend
	.size	PQ_HAL_EnableSR, .-PQ_HAL_EnableSR
	.align	2
	.global	PQ_HAL_GetSREnable
	.type	PQ_HAL_GetSREnable, %function
PQ_HAL_GetSREnable:
	.fnstart
.LFB656:
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
	cmp	r0, #4	@ u32ChId,
	mov	r4, r0	@ u32ChId, u32ChId
	mov	r5, r1	@ bOnOff, bOnOff
	bls	.L17	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L20	@,
	mov	r3, #137	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
.L19:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L17:
	bl	PQ_HAL_GetVdpReg	@
	add	r1, r0, #3456	@ tmp142,,
	add	r0, r1, r4, asl #11	@,, tmp142, u32ChId,
	bl	PQ_HAL_RegRead	@
	mov	r0, r0, lsr #31	@ tmp145,,
	str	r0, [r5, #0]	@ tmp145,* bOnOff
	b	.L19	@
.L21:
	.align	2
.L20:
	.word	.LANCHOR0+32
	.fnend
	.size	PQ_HAL_GetSREnable, .-PQ_HAL_GetSREnable
	.align	2
	.global	PQ_HAL_SetSRParam
	.type	PQ_HAL_SetSRParam, %function
PQ_HAL_SetSRParam:
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
	cmp	r0, #4	@ u32ChId,
	mov	r4, r1	@ pstSRPara, pstSRPara
	bls	.L23	@,
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L26	@,
	mov	r3, #68	@,
	movw	ip, #:lower16:.LC0	@ tmp163,
	movt	ip, #:upper16:.LC0	@ tmp163,
	str	ip, [sp, #0]	@ tmp163,
	bl	HI_LogOut	@
.L25:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L23:
	mov	r5, r0, asl #11	@ D.23248, u32ChId,
	bl	PQ_HAL_GetVdpReg	@
	add	r7, r0, #3456	@ tmp164, pstVdpReg,
	add	r6, r0, #3472	@ tmp187, pstVdpReg,
	add	sl, r5, r7	@ D.23249, D.23248, tmp164
	add	r8, r5, r6	@ D.23283, D.23248, tmp187
	mov	r0, sl	@, D.23249
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r4, #4]	@ <variable>.sr_zme_en, <variable>.sr_zme_en
	mov	r1, r0	@ SR_CTRL,
	mov	r0, sl	@, D.23249
	bfi	r1, ip, #29, #2	@ SR_CTRL, <variable>.sr_zme_en,,
	bl	PQ_HAL_RegWrite	@
	add	r0, r7, #4	@ tmp166, tmp164,
	add	sl, r5, r0	@ D.23257, D.23248, tmp166
	mov	r0, sl	@, D.23257
	bl	PQ_HAL_RegRead	@
	ldrh	r3, [r4, #16]	@ <variable>.u16grd_sub_ratio, <variable>.u16grd_sub_ratio
	mov	r1, r0	@ SR_LDIR_RATIO,
	mov	r0, sl	@, D.23257
	add	sl, r7, #8	@ tmp171, tmp164,
	bfi	r1, r3, #0, #6	@ SR_LDIR_RATIO, <variable>.u16grd_sub_ratio,,
	add	sl, r5, sl	@ D.23265, D.23248, tmp171
	bl	PQ_HAL_RegWrite	@
	mov	r0, sl	@, D.23265
	bl	PQ_HAL_RegRead	@
	ldrh	r2, [r4, #18]	@ <variable>.s16grd_thrl, <variable>.s16grd_thrl
	ldrh	ip, [r4, #20]	@ <variable>.s16grd_thrh, <variable>.s16grd_thrh
	ldrb	r3, [r4, #22]	@ zero_extendqisi2	@ <variable>.u8grd_thrh_subl, <variable>.u8grd_thrh_subl
	mov	r1, r0	@ SR_LTEX_THR,
	bfi	r1, r2, #0, #11	@ SR_LTEX_THR, <variable>.s16grd_thrl,,
	bfi	r1, ip, #12, #11	@ SR_LTEX_THR, <variable>.s16grd_thrh,,
	mov	r0, sl	@, D.23265
	bfi	r1, r3, #24, #8	@ SR_LTEX_THR, <variable>.u8grd_thrh_subl,,
	bl	PQ_HAL_RegWrite	@
	add	r1, r7, #12	@ tmp182, tmp164,
	add	r7, r5, r1	@ D.23277, D.23248, tmp182
	mov	r0, r7	@, D.23277
	bl	PQ_HAL_RegRead	@
	ldrb	r2, [r4, #23]	@ zero_extendqisi2	@ <variable>.u8grd_add_ctrl, <variable>.u8grd_add_ctrl
	mov	r1, r0	@ SR_LTEX_ADD,
	mov	r0, r7	@, D.23277
	bfi	r1, r2, #0, #8	@ SR_LTEX_ADD, <variable>.u8grd_add_ctrl,,
	bl	PQ_HAL_RegWrite	@
	mov	r0, r8	@, D.23283
	bl	PQ_HAL_RegRead	@
	ldrh	ip, [r4, #24]	@ <variable>.u16disc_detail_gain, <variable>.u16disc_detail_gain
	mov	r1, r0	@ SR_DIPL_DETAIL,
	mov	r0, r8	@, D.23283
	bfi	r1, ip, #0, #12	@ SR_DIPL_DETAIL, <variable>.u16disc_detail_gain,,
	bl	PQ_HAL_RegWrite	@
	add	r0, r6, #4	@ tmp191, tmp187,
	add	r7, r5, r0	@ D.23290, D.23248, tmp191
	mov	r0, r7	@, D.23290
	bl	PQ_HAL_RegRead	@
	ldr	r3, [r4, #8]	@ <variable>.sharp_en, <variable>.sharp_en
	ldr	r2, [r4, #12]	@ <variable>.hsh_nodir, <variable>.hsh_nodir
	ldrh	ip, [r4, #26]	@ <variable>.u16ensc_detail_gain, <variable>.u16ensc_detail_gain
	mov	r1, r0	@ SR_SHARP_EN,
	mov	r0, r7	@, D.23290
	bfi	r1, r3, #31, #1	@ SR_SHARP_EN, <variable>.sharp_en,,
	add	r7, r6, #8	@ tmp198, tmp187,
	bfi	r1, r2, #30, #1	@ SR_SHARP_EN, <variable>.hsh_nodir,,
	add	r7, r5, r7	@ D.23303, D.23248, tmp198
	bfi	r1, ip, #0, #12	@ SR_SHARP_EN, <variable>.u16ensc_detail_gain,,
	add	r6, r6, #12	@ tmp212, tmp187,
	bl	PQ_HAL_RegWrite	@
	mov	r0, r7	@, D.23303
	bl	PQ_HAL_RegRead	@
	ldrb	r3, [r4, #28]	@ zero_extendqisi2	@ <variable>.u8sharp_coring, <variable>.u8sharp_coring
	ldrh	ip, [r4, #30]	@ <variable>.u16sharp_gain, <variable>.u16sharp_gain
	add	r5, r5, r6	@ D.23314, D.23248, tmp212
	ldrb	r2, [r4, #32]	@ zero_extendqisi2	@ <variable>.u8over_thrsh, <variable>.u8over_thrsh
	mov	r1, r0	@ SR_SHARP_THR,
	bfi	r1, r3, #28, #4	@ SR_SHARP_THR, <variable>.u8sharp_coring,,
	bfi	r1, ip, #16, #10	@ SR_SHARP_THR, <variable>.u16sharp_gain,,
	ldrb	r3, [r4, #33]	@ zero_extendqisi2	@ <variable>.u8under_thrsh, <variable>.u8under_thrsh
	bfi	r1, r2, #8, #8	@ SR_SHARP_THR, <variable>.u8over_thrsh,,
	mov	r0, r7	@, D.23303
	bfi	r1, r3, #0, #8	@ SR_SHARP_THR, <variable>.u8under_thrsh,,
	bl	PQ_HAL_RegWrite	@
	mov	r0, r5	@, D.23314
	bl	PQ_HAL_RegRead	@
	ldr	ip, [r4, #36]	@ <variable>.bsmooth_en, <variable>.bsmooth_en
	ldr	r2, [r4, #40]	@ <variable>.bplus_en, <variable>.bplus_en
	ldrh	r3, [r4, #44]	@ <variable>.u16plus_ctrl, <variable>.u16plus_ctrl
	mov	r1, r0	@ SR_SMOOTH,
	bfi	r1, ip, #31, #1	@ SR_SMOOTH, <variable>.bsmooth_en,,
	bfi	r1, r2, #30, #1	@ SR_SMOOTH, <variable>.bplus_en,,
	mov	r0, r5	@, D.23314
	bfi	r1, r3, #0, #10	@ SR_SMOOTH, <variable>.u16plus_ctrl,,
	bl	PQ_HAL_RegWrite	@
	b	.L25	@
.L27:
	.align	2
.L26:
	.word	.LANCHOR0+52
	.fnend
	.size	PQ_HAL_SetSRParam, .-PQ_HAL_SetSRParam
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.23372, %object
	.size	__func__.23372, 16
__func__.23372:
	.ascii	"PQ_HAL_SR_EnZme\000"
	.type	__func__.23351, %object
	.size	__func__.23351, 16
__func__.23351:
	.ascii	"PQ_HAL_EnableSR\000"
	.type	__func__.23331, %object
	.size	__func__.23331, 19
__func__.23331:
	.ascii	"PQ_HAL_GetSREnable\000"
	.space	1
	.type	__func__.23239, %object
	.size	__func__.23239, 18
__func__.23239:
	.ascii	"PQ_HAL_SetSRParam\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"select wrong VP layer id\012\000"
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
