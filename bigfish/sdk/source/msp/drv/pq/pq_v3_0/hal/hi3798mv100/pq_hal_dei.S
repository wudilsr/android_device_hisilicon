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
	.file	"pq_hal_dei.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_hal_dei)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/hal/hi3798mv100/.pq_hal_dei.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_dei.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/hal/hi3798mv100/pq_hal_dei.o -O2 -Wall -Wundef
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
	.global	PQ_HAL_SetDeiAdjustGain
	.type	PQ_HAL_SetDeiAdjustGain, %function
PQ_HAL_SetDeiAdjustGain:
	.fnstart
.LFB1393:
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
	mov	r4, r1	@ u32AdjustGain, u32AdjustGain
	bl	PQ_HAL_GetVpssReg	@
	subs	r3, r0, #0	@ pstVpssVirReg,
	beq	.L6	@,
	movw	r1, #4234	@ tmp144,
	movw	r2, #4232	@ tmp142,
	mov	r0, #0	@ D.35884,
	uxtb	r4, r4	@ D.35885, u32AdjustGain
	strb	r4, [r3, r1]	@ D.35885, <variable>.VPSS_DIEMTNADJ.bits.motion_adjust_gain_chr
	strb	r4, [r3, r2]	@ D.35885, <variable>.VPSS_DIEMTNADJ.bits.motion_adjust_gain
.L3:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L6:
	mov	r0, #1	@,
	mov	r1, #41	@,
	movw	r2, #:lower16:.LANCHOR0	@,
	movw	r3, #297	@,
	movt	r2, #:upper16:.LANCHOR0	@,
	movw	ip, #:lower16:.LC0	@ tmp141,
	movt	ip, #:upper16:.LC0	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35884,
	b	.L3	@
	.fnend
	.size	PQ_HAL_SetDeiAdjustGain, .-PQ_HAL_SetDeiAdjustGain
	.align	2
	.global	PQ_HAL_SetDeiRegist
	.type	PQ_HAL_SetDeiRegist, %function
PQ_HAL_SetDeiRegist:
	.fnstart
.LFB1392:
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
	mov	r4, r1	@ pstDeiPara, pstDeiPara
	bl	PQ_HAL_GetVpssReg	@
	cmp	r0, #0	@ pstVpssVirReg
	beq	.L11	@,
	movw	r1, #4099	@ tmp142,
	ldr	r7, [r4, #0]	@ <variable>.stFmdCtrl.u32Die_cmmode, <variable>.stFmdCtrl.u32Die_cmmode
	ldrb	r9, [r0, r1]	@ zero_extendqisi2	@,
	movw	r3, #4100	@ tmp158,
	movw	ip, #4105	@ tmp186,
	ldrb	r8, [r0, r3]	@ zero_extendqisi2	@,
	bfi	r9, r7, #0, #2	@ tmp143, <variable>.stFmdCtrl.u32Die_cmmode,,
	ldrb	r5, [r0, ip]	@ zero_extendqisi2	@,
	strb	r9, [r0, r1]	@ tmp143,
	ldr	sl, [r4, #4]	@ <variable>.stFmdCtrl.u32Die_lmmode, <variable>.stFmdCtrl.u32Die_lmmode
	uxtb	r6, r9	@ tmp147, tmp143
	movw	r9, #4113	@ tmp198,
	bfi	r6, sl, #2, #2	@ tmp147, <variable>.stFmdCtrl.u32Die_lmmode,,
	strb	r6, [r0, r1]	@ tmp147,
	ldr	r2, [r4, #8]	@ <variable>.stFmdCtrl.u32Die_out_sel_c, <variable>.stFmdCtrl.u32Die_out_sel_c
	uxtb	lr, r6	@ tmp151, tmp147
	bfi	lr, r2, #4, #1	@ tmp151, <variable>.stFmdCtrl.u32Die_out_sel_c,,
	strb	lr, [r0, r1]	@ tmp151,
	ldr	r7, [r4, #12]	@ <variable>.stFmdCtrl.u32Die_out_sel_l, <variable>.stFmdCtrl.u32Die_out_sel_l
	uxtb	sl, lr	@ tmp155, tmp151
	bfi	sl, r7, #5, #1	@ tmp155, <variable>.stFmdCtrl.u32Die_out_sel_l,,
	strb	sl, [r0, r1]	@ tmp155,
	ldr	r6, [r4, #40]	@ <variable>.stMadMtnCtrl.bRecmdFrmfldBldMd, <variable>.stMadMtnCtrl.bRecmdFrmfldBldMd
	bfi	r8, r6, #0, #1	@ tmp159, <variable>.stMadMtnCtrl.bRecmdFrmfldBldMd,,
	strb	r8, [r0, r3]	@ tmp159,
	ldr	r2, [r4, #36]	@ <variable>.stMadMtnCtrl.bFrmMtnSmthEn, <variable>.stMadMtnCtrl.bFrmMtnSmthEn
	ldrb	lr, [r0, r3]	@ zero_extendqisi2	@,
	bfi	lr, r2, #1, #1	@ tmp163, <variable>.stMadMtnCtrl.bFrmMtnSmthEn,,
	strb	lr, [r0, r3]	@ tmp163,
	ldr	sl, [r4, #24]	@ <variable>.stMadMtnCtrl.bSceSdfMaxLum, <variable>.stMadMtnCtrl.bSceSdfMaxLum
	uxtb	r7, lr	@ tmp167, tmp163
	bfi	r7, sl, #2, #1	@ tmp167, <variable>.stMadMtnCtrl.bSceSdfMaxLum,,
	strb	r7, [r0, r3]	@ tmp167,
	ldr	r1, [r4, #32]	@ <variable>.stMadMtnCtrl.bMtnIIrEn, <variable>.stMadMtnCtrl.bMtnIIrEn
	uxtb	r8, r7	@ tmp171, tmp167
	bfi	r8, r1, #4, #1	@ tmp171, <variable>.stMadMtnCtrl.bMtnIIrEn,,
	strb	r8, [r0, r3]	@ tmp171,
	ldr	r6, [r4, #20]	@ <variable>.stMadMtnCtrl.bMfMaxLum, <variable>.stMadMtnCtrl.bMfMaxLum
	movw	r1, #4157	@ tmp341,
	uxtb	r2, r8	@ tmp175, tmp171
	bfi	r2, r6, #5, #1	@ tmp175, <variable>.stMadMtnCtrl.bMfMaxLum,,
	strb	r2, [r0, r3]	@ tmp175,
	ldr	lr, [r4, #16]	@ <variable>.stMadMtnCtrl.bMfMaxChr, <variable>.stMadMtnCtrl.bMfMaxChr
	mov	r2, #4160	@ tmp355,
	ldrb	sl, [r0, r3]	@ zero_extendqisi2	@,
	bfi	sl, lr, #6, #1	@ tmp179, <variable>.stMadMtnCtrl.bMfMaxChr,,
	strb	sl, [r0, r3]	@ tmp179,
	ldr	r7, [r4, #28]	@ <variable>.stMadMtnCtrl.bRecMdEn, <variable>.stMadMtnCtrl.bRecMdEn
	uxtb	r8, sl	@ tmp183, tmp179
	movw	sl, #4106	@ tmp189,
	bfi	r8, r7, #7, #1	@ tmp183, <variable>.stMadMtnCtrl.bRecMdEn,,
	strb	r8, [r0, r3]	@ tmp183,
	ldr	r6, [r4, #52]	@ <variable>.stMadIntpCtrl.s32DirIntenVer, <variable>.stMadIntpCtrl.s32DirIntenVer
	movw	r3, #4117	@,
	movw	r8, #4114	@,
	movw	r7, #4108	@ tmp191,
	bfi	r5, r6, #0, #4	@ tmp187, <variable>.stMadIntpCtrl.s32DirIntenVer,,
	strb	r5, [r0, ip]	@ tmp187,
	ldrh	lr, [r4, #48]	@, <variable>.stMadIntpCtrl.s32MinIntenVer
	movw	r6, #4118	@,
	strh	lr, [r0, sl]	@ movhi	@, <variable>.VPSS_DIEINTEN.bits.ver_min_inten
	ldr	r5, [r4, #56]	@ <variable>.stMadIntpCtrl.s32RangeScale, <variable>.stMadIntpCtrl.s32RangeScale
	ldrb	ip, [r0, r3]	@ zero_extendqisi2	@,
	movw	r3, #4112	@ tmp194,
	ldrb	lr, [r0, r9]	@ zero_extendqisi2	@,
	ldrb	sl, [r0, r8]	@ zero_extendqisi2	@,
	movw	r8, #4120	@,
	strb	ip, [fp, #-60]	@, %sfp
	movw	ip, #4121	@,
	strb	r5, [r0, r7]	@ <variable>.stMadIntpCtrl.s32RangeScale, <variable>.VPSS_DIESCALE.bits.range_scale
	ldr	r5, [r4, #92]	@ <variable>.stMadChk1.s32CkMaxRange, <variable>.stMadChk1.s32CkMaxRange
	ldrb	r7, [r0, r6]	@ zero_extendqisi2	@,
	ldrb	r6, [r0, r8]	@ zero_extendqisi2	@,
	strb	r5, [r0, r3]	@ <variable>.stMadChk1.s32CkMaxRange, <variable>.VPSS_DIECHECK1.bits.ck1_max_range
	movw	r3, #4122	@,
	ldr	r8, [r4, #88]	@ <variable>.stMadChk1.s32CkRangeGain, <variable>.stMadChk1.s32CkRangeGain
	ldrb	r5, [r0, ip]	@ zero_extendqisi2	@,
	movw	ip, #4123	@,
	bfi	lr, r8, #0, #4	@ tmp199, <variable>.stMadChk1.s32CkRangeGain,,
	strb	lr, [r0, r9]	@ tmp199,
	ldr	r8, [r4, #84]	@ <variable>.stMadChk1.s32CkGain, <variable>.stMadChk1.s32CkGain
	movw	r9, #4114	@,
	ldrb	lr, [r0, r3]	@ zero_extendqisi2	@,
	movw	r3, #4186	@ tmp457,
	bfi	sl, r8, #0, #4	@ tmp203, <variable>.stMadChk1.s32CkGain,,
	movw	r8, #4124	@,
	strb	sl, [r0, r9]	@ tmp203,
	ldrb	sl, [r0, r8]	@ zero_extendqisi2	@,
	ldrb	r9, [r0, ip]	@ zero_extendqisi2	@,
	movw	ip, #4116	@,
	strb	sl, [fp, #-48]	@, %sfp
	ldr	r8, [r4, #104]	@, <variable>.stMadChk2.s32CkMaxRange
	strb	r8, [r0, ip]	@, <variable>.VPSS_DIECHECK2.bits.ck2_max_range
	movw	ip, #4117	@,
	ldr	sl, [r4, #100]	@ <variable>.stMadChk2.s32CkRangeGain, <variable>.stMadChk2.s32CkRangeGain
	ldrb	r8, [fp, #-60]	@ zero_extendqisi2	@, %sfp
	bfi	r8, sl, #0, #4	@, <variable>.stMadChk2.s32CkRangeGain,,
	strb	r8, [r0, ip]	@,
	ldr	sl, [r4, #96]	@ <variable>.stMadChk2.s32CkGain, <variable>.stMadChk2.s32CkGain
	movw	ip, #4118	@,
	bfi	r7, sl, #0, #4	@ tmp214, <variable>.stMadChk2.s32CkGain,,
	strb	r7, [r0, ip]	@ tmp214,
	ldr	r8, [r4, #108]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	r7, #4120	@,
	movw	ip, #4121	@,
	bfi	r6, r8, #0, #6	@ tmp218, <variable>.stMadDirMult.s32MultDir,,
	strb	r6, [r0, r7]	@ tmp218,
	ldr	sl, [r4, #112]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	r6, #4122	@,
	bfi	r5, sl, #0, #6	@ tmp222, <variable>.stMadDirMult.s32MultDir,,
	strb	r5, [r0, ip]	@ tmp222,
	ldr	r8, [r4, #116]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	sl, #4123	@,
	movw	r5, #4208	@ tmp546,
	bfi	lr, r8, #0, #6	@ tmp226, <variable>.stMadDirMult.s32MultDir,,
	strb	lr, [r0, r6]	@ tmp226,
	ldr	r7, [r4, #120]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	r8, #4124	@,
	movw	r6, #4125	@,
	bfi	r9, r7, #0, #6	@ tmp230, <variable>.stMadDirMult.s32MultDir,,
	strb	r9, [r0, sl]	@ tmp230,
	ldr	ip, [r4, #124]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	sl, #4125	@,
	ldrb	lr, [fp, #-48]	@ zero_extendqisi2	@, %sfp
	bfi	lr, ip, #0, #6	@, <variable>.stMadDirMult.s32MultDir,,
	strb	lr, [r0, r8]	@,
	ldr	r7, [r4, #128]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	r8, #4126	@,
	ldrb	r9, [r0, r6]	@ zero_extendqisi2	@,
	ldrb	lr, [r0, r8]	@ zero_extendqisi2	@,
	bfi	r9, r7, #0, #6	@ tmp238, <variable>.stMadDirMult.s32MultDir,,
	strb	r9, [r0, sl]	@ tmp238,
	ldr	ip, [r4, #132]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	sl, #4127	@,
	ldrb	r9, [r0, sl]	@ zero_extendqisi2	@,
	movw	r7, #4128	@,
	bfi	lr, ip, #0, #6	@ tmp242, <variable>.stMadDirMult.s32MultDir,,
	strb	lr, [r0, r8]	@ tmp242,
	ldr	r6, [r4, #136]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	ip, #4129	@,
	ldrb	lr, [r0, r7]	@ zero_extendqisi2	@,
	movw	r7, #4128	@,
	bfi	r9, r6, #0, #6	@ tmp246, <variable>.stMadDirMult.s32MultDir,,
	strb	r9, [r0, sl]	@ tmp246,
	ldr	r8, [r4, #140]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	r9, #4130	@,
	ldrb	r6, [r0, ip]	@ zero_extendqisi2	@,
	mov	ip, #4224	@ tmp607,
	bfi	lr, r8, #0, #6	@ tmp250, <variable>.stMadDirMult.s32MultDir,,
	strb	lr, [r0, r7]	@ tmp250,
	ldr	sl, [r4, #144]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	r8, #4129	@,
	ldrb	lr, [r0, r9]	@ zero_extendqisi2	@,
	movw	r7, #4131	@,
	bfi	r6, sl, #0, #6	@ tmp254, <variable>.stMadDirMult.s32MultDir,,
	strb	r6, [r0, r8]	@ tmp254,
	ldr	sl, [r4, #148]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	r9, #4130	@,
	ldrb	r6, [r0, r7]	@ zero_extendqisi2	@,
	movw	r8, #4132	@,
	bfi	lr, sl, #0, #6	@ tmp258, <variable>.stMadDirMult.s32MultDir,,
	strb	lr, [r0, r9]	@ tmp258,
	ldr	r7, [r4, #152]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	sl, #4131	@,
	ldrb	lr, [r0, r8]	@ zero_extendqisi2	@,
	movw	r9, #4133	@,
	bfi	r6, r7, #0, #6	@ tmp262, <variable>.stMadDirMult.s32MultDir,,
	strb	r6, [r0, sl]	@ tmp262,
	ldr	r8, [r4, #156]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	r7, #4132	@,
	ldrb	r6, [r0, r9]	@ zero_extendqisi2	@,
	movw	sl, #4134	@,
	bfi	lr, r8, #0, #6	@ tmp266, <variable>.stMadDirMult.s32MultDir,,
	strb	lr, [r0, r7]	@ tmp266,
	ldr	r8, [r4, #160]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	r9, #4133	@,
	ldrb	lr, [r0, sl]	@ zero_extendqisi2	@,
	movw	sl, #4134	@,
	bfi	r6, r8, #0, #6	@ tmp270, <variable>.stMadDirMult.s32MultDir,,
	strb	r6, [r0, r9]	@ tmp270,
	ldr	r7, [r4, #164]	@ <variable>.stMadDirMult.s32MultDir, <variable>.stMadDirMult.s32MultDir
	movw	r9, #4148	@,
	ldrb	r6, [r0, r9]	@ zero_extendqisi2	@,
	bfi	lr, r7, #0, #6	@ tmp274, <variable>.stMadDirMult.s32MultDir,,
	strb	lr, [r0, sl]	@ tmp274,
	ldr	r8, [r4, #200]	@ <variable>.stMadIntpScl.s32IntpSclRat, <variable>.stMadIntpScl.s32IntpSclRat
	movw	sl, #4150	@,
	bfi	r6, r8, #0, #4	@ tmp278, <variable>.stMadIntpScl.s32IntpSclRat,,
	strb	r6, [r0, r9]	@ tmp278,
	ldr	r7, [r4, #204]	@ <variable>.stMadIntpScl.s32IntpSclRat, <variable>.stMadIntpScl.s32IntpSclRat
	uxtb	lr, r6	@ tmp282, tmp278
	mov	r6, #0	@,
	bfi	lr, r7, #4, #4	@ tmp282, <variable>.stMadIntpScl.s32IntpSclRat,,
	movw	r7, #4149	@,
	strb	lr, [r0, r9]	@ tmp282,
	movw	r9, #4151	@,
	ldr	r8, [r4, #208]	@ <variable>.stMadIntpScl.s32IntpSclRat, <variable>.stMadIntpScl.s32IntpSclRat
	str	r6, [fp, #-48]	@, %sfp
	ldrb	lr, [r0, r7]	@ zero_extendqisi2	@,
	ldrb	r6, [r0, sl]	@ zero_extendqisi2	@,
	bfi	lr, r8, #0, #4	@ tmp286, <variable>.stMadIntpScl.s32IntpSclRat,,
	strb	lr, [r0, r7]	@ tmp286,
	ldr	sl, [r4, #212]	@ <variable>.stMadIntpScl.s32IntpSclRat, <variable>.stMadIntpScl.s32IntpSclRat
	movw	r8, #4149	@,
	uxtb	r7, lr	@ tmp290, tmp286
	ldrb	lr, [r0, r9]	@ zero_extendqisi2	@,
	bfi	r7, sl, #4, #4	@ tmp290, <variable>.stMadIntpScl.s32IntpSclRat,,
	strb	r7, [r0, r8]	@ tmp290,
	ldr	sl, [r4, #216]	@ <variable>.stMadIntpScl.s32IntpSclRat, <variable>.stMadIntpScl.s32IntpSclRat
	movw	r9, #4152	@,
	movw	r7, #4150	@,
	ldrb	r8, [r0, r9]	@ zero_extendqisi2	@,
	bfi	r6, sl, #0, #4	@ tmp294, <variable>.stMadIntpScl.s32IntpSclRat,,
	movw	r9, #4153	@,
	strb	r6, [r0, r7]	@ tmp294,
	ldr	sl, [r4, #220]	@, <variable>.stMadIntpScl.s32IntpSclRat
	uxtb	r6, r6	@ tmp298, tmp294
	ldrb	r7, [r0, r9]	@ zero_extendqisi2	@,
	movw	r9, #4150	@,
	bfi	r6, sl, #4, #4	@ tmp298,,,
	strb	r6, [r0, r9]	@ tmp298,
	ldr	r9, [r4, #224]	@, <variable>.stMadIntpScl.s32IntpSclRat
	movw	sl, #4154	@,
	ldrb	r6, [r0, sl]	@ zero_extendqisi2	@,
	movw	sl, #4151	@,
	bfi	lr, r9, #0, #4	@ tmp302,,,
	strb	lr, [r0, sl]	@ tmp302,
	ldr	r9, [r4, #228]	@, <variable>.stMadIntpScl.s32IntpSclRat
	uxtb	sl, lr	@ tmp306, tmp302
	movw	lr, #4151	@,
	bfi	sl, r9, #4, #4	@ tmp306,,,
	strb	sl, [r0, lr]	@ tmp306,
	ldr	r9, [r4, #232]	@ <variable>.stMadIntpScl.s32IntpSclRat, <variable>.stMadIntpScl.s32IntpSclRat
	movw	lr, #4152	@,
	bfi	r8, r9, #0, #4	@ tmp310, <variable>.stMadIntpScl.s32IntpSclRat,,
	strb	r8, [r0, lr]	@ tmp310,
	ldr	sl, [r4, #236]	@ <variable>.stMadIntpScl.s32IntpSclRat, <variable>.stMadIntpScl.s32IntpSclRat
	movw	r9, #4152	@,
	uxtb	lr, r8	@ tmp314, tmp310
	bfi	lr, sl, #4, #4	@ tmp314, <variable>.stMadIntpScl.s32IntpSclRat,,
	strb	lr, [r0, r9]	@ tmp314,
	ldr	r9, [r4, #240]	@ <variable>.stMadIntpScl.s32IntpSclRat, <variable>.stMadIntpScl.s32IntpSclRat
	movw	sl, #4153	@,
	bfi	r7, r9, #0, #4	@ tmp318, <variable>.stMadIntpScl.s32IntpSclRat,,
	strb	r7, [r0, sl]	@ tmp318,
	ldr	r8, [r4, #244]	@ <variable>.stMadIntpScl.s32IntpSclRat, <variable>.stMadIntpScl.s32IntpSclRat
	movw	r9, #4154	@,
	uxtb	lr, r7	@ tmp322, tmp318
	bfi	lr, r8, #4, #4	@ tmp322, <variable>.stMadIntpScl.s32IntpSclRat,,
	strb	lr, [r0, sl]	@ tmp322,
	ldr	r7, [r4, #248]	@ <variable>.stMadIntpScl.s32IntpSclRat, <variable>.stMadIntpScl.s32IntpSclRat
	movw	sl, #4154	@,
	bfi	r6, r7, #0, #4	@ tmp326, <variable>.stMadIntpScl.s32IntpSclRat,,
	strb	r6, [r0, r9]	@ tmp326,
	ldr	r8, [r4, #252]	@ <variable>.stMadIntpScl.s32IntpSclRat, <variable>.stMadIntpScl.s32IntpSclRat
	movw	r9, #4155	@,
	uxtb	lr, r6	@ tmp330, tmp326
	bfi	lr, r8, #4, #4	@ tmp330, <variable>.stMadIntpScl.s32IntpSclRat,,
	strb	lr, [r0, sl]	@ tmp330,
	ldr	r7, [r4, #256]	@ <variable>.stMadIntpScl.s32IntpSclRat, <variable>.stMadIntpScl.s32IntpSclRat
	movw	sl, #4156	@,
	ldrb	r6, [r0, r9]	@ zero_extendqisi2	@,
	ldrb	lr, [r0, sl]	@ zero_extendqisi2	@,
	bfi	r6, r7, #0, #4	@ tmp334, <variable>.stMadIntpScl.s32IntpSclRat,,
	strb	r6, [r0, r9]	@ tmp334,
	ldr	r8, [r4, #68]	@ <variable>.stMadIntpCtrl.s32BcGain, <variable>.stMadIntpCtrl.s32BcGain
	movw	r9, #4166	@,
	ldrb	r6, [r0, r1]	@ zero_extendqisi2	@,
	bfi	lr, r8, #0, #7	@ tmp338, <variable>.stMadIntpCtrl.s32BcGain,,
	strb	lr, [r0, sl]	@ tmp338,
	ldr	r7, [r4, #64]	@ <variable>.stMadIntpCtrl.s32DirThd, <variable>.stMadIntpCtrl.s32DirThd
	ldrb	r8, [r0, r2]	@ zero_extendqisi2	@,
	bfi	r6, r7, #0, #4	@ tmp342, <variable>.stMadIntpCtrl.s32DirThd,,
	strb	r6, [r0, r1]	@ tmp342,
	ldr	sl, [r4, #76]	@ <variable>.stMadIntpCtrl.bEdgeMd, <variable>.stMadIntpCtrl.bEdgeMd
	uxtb	lr, r6	@ tmp346, tmp342
	ldrb	r7, [r0, r9]	@ zero_extendqisi2	@,
	bfi	lr, sl, #4, #1	@ tmp346, <variable>.stMadIntpCtrl.bEdgeMd,,
	strb	lr, [r0, r1]	@ tmp346,
	ldr	r6, [r4, #72]	@, <variable>.stMadIntpCtrl.bHorEdgeEn
	movw	r9, #4167	@,
	uxtb	sl, lr	@ tmp350, tmp346
	ldrb	lr, [r0, r9]	@ zero_extendqisi2	@,
	bfi	sl, r6, #5, #1	@ tmp350,,,
	strb	sl, [r0, r1]	@ tmp350,
	ldrh	sl, [r4, #60]	@, <variable>.stMadIntpCtrl.s32StrengthThd
	movw	r9, #4158	@ tmp352,
	strh	sl, [r0, r9]	@ movhi	@, <variable>.VPSS_DIEDIRTHD.bits.strength_thd
	ldr	r1, [r4, #288]	@ <variable>.stMadJitMtn.s32JitGain, <variable>.stMadJitMtn.s32JitGain
	bfi	r8, r1, #0, #4	@ tmp356, <variable>.stMadJitMtn.s32JitGain,,
	strb	r8, [r0, r2]	@ tmp356,
	ldr	r6, [r4, #292]	@ <variable>.stMadJitMtn.s32JitCoring, <variable>.stMadJitMtn.s32JitCoring
	movw	r1, #4164	@ tmp365,
	ldrh	r9, [r0, r2]	@,
	bfi	r9, r6, #4, #8	@ tmp360, <variable>.stMadJitMtn.s32JitCoring,,
	strh	r9, [r0, r2]	@ movhi	@ tmp360,
	ldr	r8, [r4, #300]	@ <variable>.stMadFldMtn.s32FldMtnCoring, <variable>.stMadFldMtn.s32FldMtnCoring
	movw	r9, #4165	@ tmp368,
	ldr	sl, [r0, r2]	@ tmp364,
	bfi	sl, r8, #12, #8	@ tmp364, <variable>.stMadFldMtn.s32FldMtnCoring,,
	str	sl, [r0, r2]	@ tmp364,
	ldr	r6, [r4, #304]	@ <variable>.stMadFldMtn.s32FldMtnThdLow, <variable>.stMadFldMtn.s32FldMtnThdLow
	movw	r8, #4166	@,
	strb	r6, [r0, r1]	@ <variable>.stMadFldMtn.s32FldMtnThdLow, <variable>.VPSS_DIEFLDMTN.bits.fld_motion_thd_low
	movw	r6, #4174	@,
	ldr	sl, [r4, #308]	@ <variable>.stMadFldMtn.s32FldMtnThdHigh, <variable>.stMadFldMtn.s32FldMtnThdHigh
	strb	sl, [r0, r9]	@ <variable>.stMadFldMtn.s32FldMtnThdHigh, <variable>.VPSS_DIEFLDMTN.bits.fld_motion_thd_high
	movw	r9, #4175	@,
	ldr	r2, [r4, #312]	@ <variable>.stMadFldMtn.s32FldMtnCrvSlp, <variable>.stMadFldMtn.s32FldMtnCrvSlp
	movw	sl, #4168	@ tmp379,
	bfi	r7, r2, #0, #6	@ tmp373, <variable>.stMadFldMtn.s32FldMtnCrvSlp,,
	strb	r7, [r0, r8]	@ tmp373,
	ldr	r1, [r4, #296]	@ <variable>.stMadFldMtn.s32FldMtnGain, <variable>.stMadFldMtn.s32FldMtnGain
	movw	r7, #4167	@,
	movw	r2, #4176	@,
	movw	r8, #4180	@,
	bfi	lr, r1, #0, #4	@ tmp377, <variable>.stMadFldMtn.s32FldMtnGain,,
	strb	lr, [r0, r7]	@ tmp377,
	ldr	lr, [r4, #356]	@ <variable>.stIirMtnCrv.s32MtnDiffThd, <variable>.stIirMtnCrv.s32MtnDiffThd
	ldrb	r7, [r0, r6]	@ zero_extendqisi2	@,
	ldrb	r6, [r0, r9]	@ zero_extendqisi2	@,
	movw	r9, #4169	@ tmp382,
	strb	lr, [r0, sl]	@ <variable>.stIirMtnCrv.s32MtnDiffThd, <variable>.VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_0
	ldr	r1, [r4, #360]	@ <variable>.stIirMtnCrv.s32MtnDiffThd, <variable>.stIirMtnCrv.s32MtnDiffThd
	ldrb	lr, [r0, r2]	@ zero_extendqisi2	@,
	ldrb	r2, [r0, r8]	@ zero_extendqisi2	@,
	movw	r8, #4170	@ tmp385,
	strb	r1, [r0, r9]	@ <variable>.stIirMtnCrv.s32MtnDiffThd, <variable>.VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_1
	movw	r9, #4171	@ tmp388,
	ldr	sl, [r4, #364]	@ <variable>.stIirMtnCrv.s32MtnDiffThd, <variable>.stIirMtnCrv.s32MtnDiffThd
	strb	sl, [r0, r8]	@ <variable>.stIirMtnCrv.s32MtnDiffThd, <variable>.VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_2
	movw	r8, #4172	@ tmp391,
	ldr	r1, [r4, #368]	@ <variable>.stIirMtnCrv.s32MtnDiffThd, <variable>.stIirMtnCrv.s32MtnDiffThd
	strb	r1, [r0, r9]	@ <variable>.stIirMtnCrv.s32MtnDiffThd, <variable>.VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_3
	movw	r9, #4173	@ tmp394,
	ldr	sl, [r4, #372]	@ <variable>.stIirMtnCrv.s32MtnDiffThd, <variable>.stIirMtnCrv.s32MtnDiffThd
	strb	sl, [r0, r8]	@ <variable>.stIirMtnCrv.s32MtnDiffThd, <variable>.VPSS_DIEMTNDIFFTHD1.bits.motion_diff_thd_4
	movw	sl, #4174	@,
	ldr	r1, [r4, #376]	@ <variable>.stIirMtnCrv.s32MtnDiffThd, <variable>.stIirMtnCrv.s32MtnDiffThd
	strb	r1, [r0, r9]	@ <variable>.stIirMtnCrv.s32MtnDiffThd, <variable>.VPSS_DIEMTNDIFFTHD1.bits.motion_diff_thd_5
	movw	r9, #4175	@,
	ldr	r8, [r4, #416]	@ <variable>.stIirMtnCrv.s32MtnIirCrvRatMin, <variable>.stIirMtnCrv.s32MtnIirCrvRatMin
	bfi	r7, r8, #0, #7	@ tmp399, <variable>.stIirMtnCrv.s32MtnIirCrvRatMin,,
	strb	r7, [r0, sl]	@ tmp399,
	ldr	r1, [r4, #420]	@ <variable>.stIirMtnCrv.s32MtnIirCrvRatMax, <variable>.stIirMtnCrv.s32MtnIirCrvRatMax
	movw	r8, #4176	@,
	bfi	r6, r1, #0, #7	@ tmp403, <variable>.stIirMtnCrv.s32MtnIirCrvRatMax,,
	strb	r6, [r0, r9]	@ tmp403,
	ldr	r7, [r4, #380]	@ <variable>.stIirMtnCrv.s32MtnIirCrvSlp, <variable>.stIirMtnCrv.s32MtnIirCrvSlp
	movw	r9, #4176	@,
	bfi	lr, r7, #0, #6	@ tmp407, <variable>.stIirMtnCrv.s32MtnIirCrvSlp,,
	strb	lr, [r0, r8]	@ tmp407,
	ldr	r6, [r4, #384]	@ <variable>.stIirMtnCrv.s32MtnIirCrvSlp, <variable>.stIirMtnCrv.s32MtnIirCrvSlp
	movw	r8, #4178	@,
	ldrh	sl, [r0, r9]	@,
	bfi	sl, r6, #6, #6	@ tmp411, <variable>.stIirMtnCrv.s32MtnIirCrvSlp,,
	strh	sl, [r0, r9]	@ movhi	@ tmp411,
	ldr	r1, [r4, #388]	@ <variable>.stIirMtnCrv.s32MtnIirCrvSlp, <variable>.stIirMtnCrv.s32MtnIirCrvSlp
	ldr	lr, [r0, r9]	@ tmp415,
	bfi	lr, r1, #12, #6	@ tmp415, <variable>.stIirMtnCrv.s32MtnIirCrvSlp,,
	str	lr, [r0, r9]	@ tmp415,
	ldr	r7, [r4, #392]	@ <variable>.stIirMtnCrv.s32MtnIirCrvSlp, <variable>.stIirMtnCrv.s32MtnIirCrvSlp
	movw	r9, #4179	@,
	ldrb	sl, [r0, r8]	@ zero_extendqisi2	@,
	ldrb	r1, [r0, r9]	@ zero_extendqisi2	@,
	bfi	sl, r7, #2, #6	@ tmp418, <variable>.stIirMtnCrv.s32MtnIirCrvSlp,,
	strb	sl, [r0, r8]	@ tmp418,
	ldr	r6, [r4, #396]	@ <variable>.stIirMtnCrv.s32MtnIirCrvRat, <variable>.stIirMtnCrv.s32MtnIirCrvRat
	movw	sl, #4180	@,
	movw	r7, #4181	@,
	bfi	r1, r6, #0, #7	@ tmp422, <variable>.stIirMtnCrv.s32MtnIirCrvRat,,
	strb	r1, [r0, r9]	@ tmp422,
	ldr	lr, [r4, #400]	@ <variable>.stIirMtnCrv.s32MtnIirCrvRat, <variable>.stIirMtnCrv.s32MtnIirCrvRat
	movw	r1, #4181	@,
	bfi	r2, lr, #0, #7	@ tmp426, <variable>.stIirMtnCrv.s32MtnIirCrvRat,,
	strb	r2, [r0, sl]	@ tmp426,
	ldr	r8, [r4, #404]	@ <variable>.stIirMtnCrv.s32MtnIirCrvRat, <variable>.stIirMtnCrv.s32MtnIirCrvRat
	movw	lr, #4182	@,
	ldrb	r9, [r0, r1]	@ zero_extendqisi2	@,
	movw	r1, #4183	@,
	ldrb	sl, [r0, lr]	@ zero_extendqisi2	@,
	bfi	r9, r8, #0, #7	@ tmp430, <variable>.stIirMtnCrv.s32MtnIirCrvRat,,
	strb	r9, [r0, r7]	@ tmp430,
	ldr	r6, [r4, #408]	@ <variable>.stIirMtnCrv.s32MtnIirCrvRat, <variable>.stIirMtnCrv.s32MtnIirCrvRat
	movw	r7, #4185	@,
	ldrb	r8, [r0, r1]	@ zero_extendqisi2	@,
	bfi	sl, r6, #0, #7	@ tmp434, <variable>.stIirMtnCrv.s32MtnIirCrvRat,,
	strb	sl, [r0, lr]	@ tmp434,
	ldr	r2, [r4, #412]	@ <variable>.stIirMtnCrv.s32MtnIirCrvRat, <variable>.stIirMtnCrv.s32MtnIirCrvRat
	movw	sl, #4184	@,
	ldrb	lr, [r0, sl]	@ zero_extendqisi2	@,
	bfi	r8, r2, #0, #7	@ tmp438, <variable>.stIirMtnCrv.s32MtnIirCrvRat,,
	strb	r8, [r0, r1]	@ tmp438,
	ldr	r9, [r4, #348]	@ <variable>.stMadRecMd.s32RecMdFldMtnStp, <variable>.stMadRecMd.s32RecMdFldMtnStp
	ldrb	r8, [r0, r7]	@ zero_extendqisi2	@,
	movw	r7, #4185	@,
	bfi	lr, r9, #0, #3	@ tmp442, <variable>.stMadRecMd.s32RecMdFldMtnStp,,
	strb	lr, [r0, sl]	@ tmp442,
	ldr	r6, [r4, #352]	@ <variable>.stMadRecMd.s32RecMdFldMtnStp, <variable>.stMadRecMd.s32RecMdFldMtnStp
	uxtb	r1, lr	@ tmp446, tmp442
	ldrb	lr, [r0, r3]	@ zero_extendqisi2	@,
	bfi	r1, r6, #4, #3	@ tmp446, <variable>.stMadRecMd.s32RecMdFldMtnStp,,
	strb	r1, [r0, sl]	@ tmp446,
	ldr	sl, [r4, #340]	@ <variable>.stMadRecMd.s32RecMdFrmMtnStp, <variable>.stMadRecMd.s32RecMdFrmMtnStp
	bfi	r8, sl, #0, #2	@ tmp450, <variable>.stMadRecMd.s32RecMdFrmMtnStp,,
	strb	r8, [r0, r7]	@ tmp450,
	ldr	r2, [r4, #344]	@ <variable>.stMadRecMd.s32RecMdFrmMtnStp, <variable>.stMadRecMd.s32RecMdFrmMtnStp
	uxtb	r9, r8	@ tmp454, tmp450
	bfi	r9, r2, #4, #2	@ tmp454, <variable>.stMadRecMd.s32RecMdFrmMtnStp,,
	strb	r9, [r0, r7]	@ tmp454,
	ldr	r6, [r4, #336]	@ <variable>.stMadHistMtn.bPpreInfoEn, <variable>.stMadHistMtn.bPpreInfoEn
	bfi	lr, r6, #0, #1	@ tmp458, <variable>.stMadHistMtn.bPpreInfoEn,,
	strb	lr, [r0, r3]	@ tmp458,
	ldr	r1, [r4, #332]	@ <variable>.stMadHistMtn.bPreInfoEn, <variable>.stMadHistMtn.bPreInfoEn
	uxtb	sl, lr	@ tmp462, tmp458
	bfi	sl, r1, #1, #1	@ tmp462, <variable>.stMadHistMtn.bPreInfoEn,,
	strb	sl, [r0, r3]	@ tmp462,
	ldr	r8, [r4, #316]	@ <variable>.stMadHistMtn.bHistMtnEn, <variable>.stMadHistMtn.bHistMtnEn
	uxtb	r2, sl	@ tmp466, tmp462
	bfi	r2, r8, #2, #1	@ tmp466, <variable>.stMadHistMtn.bHistMtnEn,,
	strb	r2, [r0, r3]	@ tmp466,
	ldr	r7, [r4, #328]	@ <variable>.stMadHistMtn.bHistMtnUseMd, <variable>.stMadHistMtn.bHistMtnUseMd
	movw	r8, #4188	@ tmp480,
	uxtb	r9, r2	@ tmp470, tmp466
	bfi	r9, r7, #3, #1	@ tmp470, <variable>.stMadHistMtn.bHistMtnUseMd,,
	strb	r9, [r0, r3]	@ tmp470,
	ldr	lr, [r4, #324]	@ <variable>.stMadHistMtn.bHistMtnWrtMd, <variable>.stMadHistMtn.bHistMtnWrtMd
	uxtb	r6, r9	@ tmp474, tmp470
	movw	r9, #4189	@,
	bfi	r6, lr, #4, #1	@ tmp474, <variable>.stMadHistMtn.bHistMtnWrtMd,,
	strb	r6, [r0, r3]	@ tmp474,
	ldr	r1, [r4, #320]	@ <variable>.stMadHistMtn.bHistMtnInfoWrtMd, <variable>.stMadHistMtn.bHistMtnInfoWrtMd
	uxtb	sl, r6	@ tmp478, tmp474
	ldrb	lr, [r0, r9]	@ zero_extendqisi2	@,
	bfi	sl, r1, #5, #1	@ tmp478, <variable>.stMadHistMtn.bHistMtnInfoWrtMd,,
	strb	sl, [r0, r3]	@ tmp478,
	ldr	r2, [r4, #568]	@ <variable>.stMadMorFlt.s32MorFltThd, <variable>.stMadMorFlt.s32MorFltThd
	movw	sl, #4191	@,
	movw	r3, #4196	@,
	ldrb	r6, [r0, sl]	@ zero_extendqisi2	@,
	ldrb	r1, [r0, r3]	@ zero_extendqisi2	@,
	strb	r2, [r0, r8]	@ <variable>.stMadMorFlt.s32MorFltThd, <variable>.VPSS_DIEMORFLT.bits.mor_flt_thd
	movw	r8, #4197	@,
	ldr	r7, [r4, #564]	@ <variable>.stMadMorFlt.s32MorFltSize, <variable>.stMadMorFlt.s32MorFltSize
	ldrb	r2, [r0, r8]	@ zero_extendqisi2	@,
	bfi	lr, r7, #0, #2	@ tmp485, <variable>.stMadMorFlt.s32MorFltSize,,
	strb	lr, [r0, r9]	@ tmp485,
	ldr	r3, [r4, #560]	@ <variable>.stMadMorFlt.bMorFltEn, <variable>.stMadMorFlt.bMorFltEn
	movw	r9, #4198	@,
	ldrb	lr, [r0, r9]	@ zero_extendqisi2	@,
	bfi	r6, r3, #0, #1	@ tmp489, <variable>.stMadMorFlt.bMorFltEn,,
	strb	r6, [r0, sl]	@ tmp489,
	ldr	r7, [r4, #80]	@ <variable>.stMadIntpCtrl.bMedBldEn, <variable>.stMadIntpCtrl.bMedBldEn
	uxtb	r3, r6	@ tmp493, tmp489
	bfi	r3, r7, #2, #1	@ tmp493, <variable>.stMadIntpCtrl.bMedBldEn,,
	strb	r3, [r0, sl]	@ tmp493,
	ldr	r7, [r4, #276]	@ <variable>.stMadCombChk.s32CombChkMinThdH, <variable>.stMadCombChk.s32CombChkMinThdH
	movw	sl, #4192	@ tmp495,
	movw	r3, #4193	@ tmp498,
	strb	r7, [r0, sl]	@ <variable>.stMadCombChk.s32CombChkMinThdH, <variable>.VPSS_DIECOMBCHK0.bits.comb_chk_min_hthd
	movw	sl, #4194	@ tmp501,
	ldr	r6, [r4, #272]	@ <variable>.stMadCombChk.s32CombChkMinThdV, <variable>.stMadCombChk.s32CombChkMinThdV
	strb	r6, [r0, r3]	@ <variable>.stMadCombChk.s32CombChkMinThdV, <variable>.VPSS_DIECOMBCHK0.bits.comb_chk_min_vthd
	movw	r3, #4195	@ tmp504,
	ldr	r7, [r4, #268]	@ <variable>.stMadCombChk.s32CombChkLowLmt, <variable>.stMadCombChk.s32CombChkLowLmt
	strb	r7, [r0, sl]	@ <variable>.stMadCombChk.s32CombChkLowLmt, <variable>.VPSS_DIECOMBCHK0.bits.comb_chk_lower_limit
	movw	r7, #4196	@,
	ldr	r6, [r4, #264]	@ <variable>.stMadCombChk.s32CombChkUpLmt, <variable>.stMadCombChk.s32CombChkUpLmt
	strb	r6, [r0, r3]	@ <variable>.stMadCombChk.s32CombChkUpLmt, <variable>.VPSS_DIECOMBCHK0.bits.comb_chk_upper_limit
	movw	r3, #4200	@ tmp519,
	ldr	sl, [r4, #284]	@ <variable>.stMadCombChk.s32CombChkEdgeThd, <variable>.stMadCombChk.s32CombChkEdgeThd
	bfi	r1, sl, #0, #7	@ tmp509, <variable>.stMadCombChk.s32CombChkEdgeThd,,
	strb	r1, [r0, r7]	@ tmp509,
	ldr	r6, [r4, #280]	@ <variable>.stMadCombChk.s32CombChkMdThd, <variable>.stMadCombChk.s32CombChkMdThd
	bfi	r2, r6, #0, #5	@ tmp513, <variable>.stMadCombChk.s32CombChkMdThd,,
	strb	r2, [r0, r8]	@ tmp513,
	ldr	r1, [r4, #260]	@ <variable>.stMadCombChk.bCombChkEn, <variable>.stMadCombChk.bCombChkEn
	movw	r8, #4201	@ tmp522,
	movw	r6, #4206	@,
	movw	r2, #4207	@,
	bfi	lr, r1, #0, #1	@ tmp517, <variable>.stMadCombChk.bCombChkEn,,
	strb	lr, [r0, r9]	@ tmp517,
	ldr	sl, [r4, #424]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthThd, <variable>.stFrmMtnSmth.s32FrmMtnSmthThd
	movw	r1, #4202	@ tmp525,
	movw	r9, #4212	@,
	strb	sl, [r0, r3]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthThd, <variable>.VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd0
	movw	r3, #4203	@ tmp528,
	ldr	r7, [r4, #428]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthThd, <variable>.stFrmMtnSmth.s32FrmMtnSmthThd
	strb	r7, [r0, r8]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthThd, <variable>.VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd1
	movw	r8, #4213	@,
	ldr	lr, [r4, #432]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthThd, <variable>.stFrmMtnSmth.s32FrmMtnSmthThd
	ldrb	r7, [r0, r6]	@ zero_extendqisi2	@,
	ldrb	r6, [r0, r2]	@ zero_extendqisi2	@,
	strb	lr, [r0, r1]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthThd, <variable>.VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd2
	ldr	sl, [r4, #436]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthThd, <variable>.stFrmMtnSmth.s32FrmMtnSmthThd
	ldrb	r1, [r0, r5]	@ zero_extendqisi2	@,
	ldrb	lr, [r0, r9]	@ zero_extendqisi2	@,
	movw	r9, #4204	@ tmp531,
	strb	sl, [r0, r3]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthThd, <variable>.VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd3
	ldr	r2, [r4, #440]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthThd, <variable>.stFrmMtnSmth.s32FrmMtnSmthThd
	ldrb	r3, [r0, r8]	@ zero_extendqisi2	@,
	movw	r8, #4205	@ tmp534,
	strb	r2, [r0, r9]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthThd, <variable>.VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_thd4
	movw	r9, #4206	@,
	ldr	sl, [r4, #444]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthThd, <variable>.stFrmMtnSmth.s32FrmMtnSmthThd
	strb	sl, [r0, r8]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthThd, <variable>.VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_thd5
	movw	sl, #4207	@,
	ldr	r2, [r4, #484]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthRatMin, <variable>.stFrmMtnSmth.s32FrmMtnSmthRatMin
	bfi	r7, r2, #0, #7	@ tmp539, <variable>.stFrmMtnSmth.s32FrmMtnSmthRatMin,,
	strb	r7, [r0, r9]	@ tmp539,
	ldr	r8, [r4, #488]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthRatMax, <variable>.stFrmMtnSmth.s32FrmMtnSmthRatMax
	bfi	r6, r8, #0, #7	@ tmp543, <variable>.stFrmMtnSmth.s32FrmMtnSmthRatMax,,
	strb	r6, [r0, sl]	@ tmp543,
	ldr	r6, [r4, #448]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthSlp, <variable>.stFrmMtnSmth.s32FrmMtnSmthSlp
	movw	sl, #4210	@,
	bfi	r1, r6, #0, #6	@ tmp547, <variable>.stFrmMtnSmth.s32FrmMtnSmthSlp,,
	strb	r1, [r0, r5]	@ tmp547,
	ldr	r2, [r4, #452]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthSlp, <variable>.stFrmMtnSmth.s32FrmMtnSmthSlp
	movw	r1, #4210	@,
	ldrh	r7, [r0, r5]	@,
	bfi	r7, r2, #6, #6	@ tmp551, <variable>.stFrmMtnSmth.s32FrmMtnSmthSlp,,
	strh	r7, [r0, r5]	@ movhi	@ tmp551,
	ldr	r9, [r4, #456]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthSlp, <variable>.stFrmMtnSmth.s32FrmMtnSmthSlp
	movw	r7, #4211	@,
	ldr	r8, [r0, r5]	@ tmp555,
	bfi	r8, r9, #12, #6	@ tmp555, <variable>.stFrmMtnSmth.s32FrmMtnSmthSlp,,
	str	r8, [r0, r5]	@ tmp555,
	ldr	r6, [r4, #460]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthSlp, <variable>.stFrmMtnSmth.s32FrmMtnSmthSlp
	ldrb	r5, [r0, sl]	@ zero_extendqisi2	@,
	movw	sl, #4212	@,
	ldrb	r9, [r0, r7]	@ zero_extendqisi2	@,
	bfi	r5, r6, #2, #6	@ tmp558, <variable>.stFrmMtnSmth.s32FrmMtnSmthSlp,,
	strb	r5, [r0, r1]	@ tmp558,
	ldr	r2, [r4, #464]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthRat, <variable>.stFrmMtnSmth.s32FrmMtnSmthRat
	movw	r5, #4213	@,
	movw	r1, #4214	@,
	bfi	r9, r2, #0, #7	@ tmp562, <variable>.stFrmMtnSmth.s32FrmMtnSmthRat,,
	strb	r9, [r0, r7]	@ tmp562,
	ldr	r8, [r4, #468]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthRat, <variable>.stFrmMtnSmth.s32FrmMtnSmthRat
	movw	r7, #4214	@,
	bfi	lr, r8, #0, #7	@ tmp566, <variable>.stFrmMtnSmth.s32FrmMtnSmthRat,,
	strb	lr, [r0, sl]	@ tmp566,
	ldr	r6, [r4, #472]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthRat, <variable>.stFrmMtnSmth.s32FrmMtnSmthRat
	movw	lr, #4215	@,
	bfi	r3, r6, #0, #7	@ tmp570, <variable>.stFrmMtnSmth.s32FrmMtnSmthRat,,
	strb	r3, [r0, r5]	@ tmp570,
	ldr	r2, [r4, #476]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthRat, <variable>.stFrmMtnSmth.s32FrmMtnSmthRat
	movw	r3, #4216	@ tmp580,
	ldrb	r9, [r0, r1]	@ zero_extendqisi2	@,
	movw	r1, #4217	@ tmp583,
	ldrb	sl, [r0, lr]	@ zero_extendqisi2	@,
	bfi	r9, r2, #0, #7	@ tmp574, <variable>.stFrmMtnSmth.s32FrmMtnSmthRat,,
	strb	r9, [r0, r7]	@ tmp574,
	ldr	r8, [r4, #480]	@ <variable>.stFrmMtnSmth.s32FrmMtnSmthRat, <variable>.stFrmMtnSmth.s32FrmMtnSmthRat
	movw	r7, #4222	@,
	ldrb	r9, [r0, r7]	@ zero_extendqisi2	@,
	bfi	sl, r8, #0, #7	@ tmp578, <variable>.stFrmMtnSmth.s32FrmMtnSmthRat,,
	strb	sl, [r0, lr]	@ tmp578,
	ldr	r6, [r4, #492]	@ <variable>.stFrmFldBld.s32FrmFldBldThd, <variable>.stFrmFldBld.s32FrmFldBldThd
	movw	r8, #4223	@,
	ldrb	lr, [r0, r8]	@ zero_extendqisi2	@,
	ldrb	sl, [r0, ip]	@ zero_extendqisi2	@,
	strb	r6, [r0, r3]	@ <variable>.stFrmFldBld.s32FrmFldBldThd, <variable>.VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd0
	movw	r3, #4218	@ tmp586,
	ldr	r5, [r4, #496]	@ <variable>.stFrmFldBld.s32FrmFldBldThd, <variable>.stFrmFldBld.s32FrmFldBldThd
	strb	r5, [r0, r1]	@ <variable>.stFrmFldBld.s32FrmFldBldThd, <variable>.VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd1
	movw	r5, #4219	@ tmp589,
	ldr	r2, [r4, #500]	@ <variable>.stFrmFldBld.s32FrmFldBldThd, <variable>.stFrmFldBld.s32FrmFldBldThd
	strb	r2, [r0, r3]	@ <variable>.stFrmFldBld.s32FrmFldBldThd, <variable>.VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd2
	movw	r2, #4220	@ tmp592,
	ldr	r6, [r4, #504]	@ <variable>.stFrmFldBld.s32FrmFldBldThd, <variable>.stFrmFldBld.s32FrmFldBldThd
	strb	r6, [r0, r5]	@ <variable>.stFrmFldBld.s32FrmFldBldThd, <variable>.VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd3
	movw	r5, #4221	@ tmp595,
	ldr	r1, [r4, #508]	@ <variable>.stFrmFldBld.s32FrmFldBldThd, <variable>.stFrmFldBld.s32FrmFldBldThd
	strb	r1, [r0, r2]	@ <variable>.stFrmFldBld.s32FrmFldBldThd, <variable>.VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_thd4
	ldr	r3, [r4, #512]	@ <variable>.stFrmFldBld.s32FrmFldBldThd, <variable>.stFrmFldBld.s32FrmFldBldThd
	strb	r3, [r0, r5]	@ <variable>.stFrmFldBld.s32FrmFldBldThd, <variable>.VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_thd5
	ldr	r6, [r4, #552]	@ <variable>.stFrmFldBld.s32FrmFldBldRatMin, <variable>.stFrmFldBld.s32FrmFldBldRatMin
	bfi	r9, r6, #0, #7	@ tmp600, <variable>.stFrmFldBld.s32FrmFldBldRatMin,,
	strb	r9, [r0, r7]	@ tmp600,
	ldr	r1, [r4, #556]	@ <variable>.stFrmFldBld.s32FrmFldBldRatMax, <variable>.stFrmFldBld.s32FrmFldBldRatMax
	bfi	lr, r1, #0, #7	@ tmp604, <variable>.stFrmFldBld.s32FrmFldBldRatMax,,
	strb	lr, [r0, r8]	@ tmp604,
	ldr	r2, [r4, #516]	@ <variable>.stFrmFldBld.s32FrmFldBldSlp, <variable>.stFrmFldBld.s32FrmFldBldSlp
	movw	lr, #4226	@,
	bfi	sl, r2, #0, #6	@ tmp608, <variable>.stFrmFldBld.s32FrmFldBldSlp,,
	strb	sl, [r0, ip]	@ tmp608,
	ldr	r7, [r4, #520]	@ <variable>.stFrmFldBld.s32FrmFldBldSlp, <variable>.stFrmFldBld.s32FrmFldBldSlp
	movw	sl, #4227	@,
	ldrh	r9, [r0, ip]	@,
	bfi	r9, r7, #6, #6	@ tmp612, <variable>.stFrmFldBld.s32FrmFldBldSlp,,
	strh	r9, [r0, ip]	@ movhi	@ tmp612,
	ldr	r3, [r4, #524]	@ <variable>.stFrmFldBld.s32FrmFldBldSlp, <variable>.stFrmFldBld.s32FrmFldBldSlp
	movw	r7, #4228	@,
	ldr	r5, [r0, ip]	@ tmp616,
	bfi	r5, r3, #12, #6	@ tmp616, <variable>.stFrmFldBld.s32FrmFldBldSlp,,
	str	r5, [r0, ip]	@ tmp616,
	ldr	r6, [r4, #528]	@ <variable>.stFrmFldBld.s32FrmFldBldSlp, <variable>.stFrmFldBld.s32FrmFldBldSlp
	movw	r5, #4229	@,
	ldrb	r8, [r0, lr]	@ zero_extendqisi2	@,
	bfi	r8, r6, #2, #6	@ tmp619, <variable>.stFrmFldBld.s32FrmFldBldSlp,,
	strb	r8, [r0, lr]	@ tmp619,
	ldr	r1, [r4, #532]	@ <variable>.stFrmFldBld.s32FrmFldBldRat, <variable>.stFrmFldBld.s32FrmFldBldRat
	movw	r8, #4230	@,
	ldrb	ip, [r0, sl]	@ zero_extendqisi2	@,
	ldrb	r9, [r0, r7]	@ zero_extendqisi2	@,
	bfi	ip, r1, #0, #7	@ tmp623, <variable>.stFrmFldBld.s32FrmFldBldRat,,
	strb	ip, [r0, sl]	@ tmp623,
	ldr	r2, [r4, #536]	@ <variable>.stFrmFldBld.s32FrmFldBldRat, <variable>.stFrmFldBld.s32FrmFldBldRat
	ldrb	r6, [r0, r5]	@ zero_extendqisi2	@,
	bfi	r9, r2, #0, #7	@ tmp627, <variable>.stFrmFldBld.s32FrmFldBldRat,,
	strb	r9, [r0, r7]	@ tmp627,
	ldr	r3, [r4, #540]	@ <variable>.stFrmFldBld.s32FrmFldBldRat, <variable>.stFrmFldBld.s32FrmFldBldRat
	movw	r7, #4231	@,
	ldrb	ip, [r0, r8]	@ zero_extendqisi2	@,
	movw	r2, #4232	@ tmp641,
	bfi	r6, r3, #0, #7	@ tmp631, <variable>.stFrmFldBld.s32FrmFldBldRat,,
	strb	r6, [r0, r5]	@ tmp631,
	ldr	lr, [r4, #544]	@ <variable>.stFrmFldBld.s32FrmFldBldRat, <variable>.stFrmFldBld.s32FrmFldBldRat
	movw	r3, #4233	@,
	ldrb	sl, [r0, r7]	@ zero_extendqisi2	@,
	movw	r6, #4240	@,
	bfi	ip, lr, #0, #7	@ tmp635, <variable>.stFrmFldBld.s32FrmFldBldRat,,
	strb	ip, [r0, r8]	@ tmp635,
	ldr	r1, [r4, #548]	@ <variable>.stFrmFldBld.s32FrmFldBldRat, <variable>.stFrmFldBld.s32FrmFldBldRat
	ldrb	lr, [r0, r3]	@ zero_extendqisi2	@,
	bfi	sl, r1, #0, #7	@ tmp639, <variable>.stFrmFldBld.s32FrmFldBldRat,,
	strb	sl, [r0, r7]	@ tmp639,
	ldr	r9, [r4, #572]	@ <variable>.stMadMtnAdj.s32MtnAdjGain, <variable>.stMadMtnAdj.s32MtnAdjGain
	movw	r7, #4236	@,
	movw	sl, #4238	@,
	ldrh	ip, [r0, r7]	@,
	ldrh	r1, [r0, sl]	@,
	strb	r9, [r0, r2]	@ <variable>.stMadMtnAdj.s32MtnAdjGain, <variable>.VPSS_DIEMTNADJ.bits.motion_adjust_gain
	movw	r9, #4234	@ tmp648,
	ldr	r5, [r4, #580]	@ <variable>.stMadMtnAdj.s32MtnAdjCoring, <variable>.stMadMtnAdj.s32MtnAdjCoring
	ldrh	r2, [r0, r6]	@,
	bfi	lr, r5, #0, #6	@ tmp646, <variable>.stMadMtnAdj.s32MtnAdjCoring,,
	strb	lr, [r0, r3]	@ tmp646,
	ldr	r8, [r4, #576]	@ <variable>.stMadMtnAdj.s32MtnAdjGainChr, <variable>.stMadMtnAdj.s32MtnAdjGainChr
	movw	r3, #4242	@,
	ldrh	lr, [r0, r3]	@,
	strb	r8, [r0, r9]	@ <variable>.stMadMtnAdj.s32MtnAdjGainChr, <variable>.VPSS_DIEMTNADJ.bits.motion_adjust_gain_chr
	ldr	r5, [r4, #584]	@ <variable>.stMadGlbMtnThd.s32MtnThdSmall, <variable>.stMadGlbMtnThd.s32MtnThdSmall
	bfi	ip, r5, #0, #10	@ tmp653, <variable>.stMadGlbMtnThd.s32MtnThdSmall,,
	strh	ip, [r0, r7]	@ movhi	@ tmp653,
	ldr	r6, [r4, #592]	@ <variable>.stMadGlbMtnThd.s32MtnThdMiddle0, <variable>.stMadGlbMtnThd.s32MtnThdMiddle0
	bfi	r1, r6, #0, #10	@ tmp657, <variable>.stMadGlbMtnThd.s32MtnThdMiddle0,,
	strh	r1, [r0, sl]	@ movhi	@ tmp657,
	ldr	r8, [r4, #596]	@ <variable>.stMadGlbMtnThd.s32MtnThdMiddle1, <variable>.stMadGlbMtnThd.s32MtnThdMiddle1
	movw	sl, #4248	@,
	bfi	r2, r8, #0, #10	@ tmp661, <variable>.stMadGlbMtnThd.s32MtnThdMiddle1,,
	movw	r8, #4240	@,
	strh	r2, [r0, r8]	@ movhi	@ tmp661,
	ldr	r9, [r4, #588]	@ <variable>.stMadGlbMtnThd.s32MtnThdLarge, <variable>.stMadGlbMtnThd.s32MtnThdLarge
	bfi	lr, r9, #0, #10	@ tmp665, <variable>.stMadGlbMtnThd.s32MtnThdLarge,,
	movw	r9, #4244	@,
	strh	lr, [r0, r3]	@ movhi	@ tmp665,
	movw	lr, #4246	@,
	ldr	r7, [r4, #180]	@ <variable>.stMadCcrScl.s32NccrDetThd, <variable>.stMadCcrScl.s32NccrDetThd
	ldrh	r2, [r0, r9]	@,
	ldrh	r6, [r0, sl]	@,
	bfi	r2, r7, #0, #10	@ tmp669, <variable>.stMadCcrScl.s32NccrDetThd,,
	strh	r2, [r0, r9]	@ movhi	@ tmp669,
	ldr	r3, [r4, #176]	@ <variable>.stMadCcrScl.s32NCcrDetMax, <variable>.stMadCcrScl.s32NCcrDetMax
	ldr	ip, [r0, r9]	@ tmp673,
	bfi	ip, r3, #10, #10	@ tmp673, <variable>.stMadCcrScl.s32NCcrDetMax,,
	str	ip, [r0, r9]	@ tmp673,
	ldr	r1, [r4, #172]	@ <variable>.stMadCcrScl.s32ChrMaOffset, <variable>.stMadCcrScl.s32ChrMaOffset
	ldrh	r5, [r0, lr]	@,
	bfi	r5, r1, #4, #10	@ tmp676, <variable>.stMadCcrScl.s32ChrMaOffset,,
	strh	r5, [r0, lr]	@ movhi	@ tmp676,
	movw	r5, #4247	@,
	ldr	r7, [r4, #168]	@ <variable>.stMadCcrScl.bCcrEn, <variable>.stMadCcrScl.bCcrEn
	ldrb	r2, [r0, r5]	@ zero_extendqisi2	@,
	bfi	r2, r7, #6, #1	@ tmp680, <variable>.stMadCcrScl.bCcrEn,,
	strb	r2, [r0, r5]	@ tmp680,
	ldr	r3, [r4, #196]	@ <variable>.stMadCcrScl.s32XChrMax, <variable>.stMadCcrScl.s32XChrMax
	bfi	r6, r3, #0, #10	@ tmp684, <variable>.stMadCcrScl.s32XChrMax,,
	strh	r6, [r0, sl]	@ movhi	@ tmp684,
	movw	r6, #4249	@,
	ldr	ip, [r4, #192]	@ <variable>.stMadCcrScl.s32NCcrDetBld, <variable>.stMadCcrScl.s32NCcrDetBld
	ldrb	r1, [r0, r6]	@ zero_extendqisi2	@,
	bfi	r1, ip, #2, #4	@ tmp688, <variable>.stMadCcrScl.s32NCcrDetBld,,
	strb	r1, [r0, r6]	@ tmp688,
	ldr	lr, [r4, #188]	@ <variable>.stMadCcrScl.s32SimlrThd, <variable>.stMadCcrScl.s32SimlrThd
	ldr	r7, [r0, sl]	@ tmp692,
	bfi	r7, lr, #14, #9	@ tmp692, <variable>.stMadCcrScl.s32SimlrThd,,
	str	r7, [r0, sl]	@ tmp692,
	movw	r7, #4250	@,
	ldr	r2, [r4, #184]	@ <variable>.stMadCcrScl.s32SimlrMax, <variable>.stMadCcrScl.s32SimlrMax
	ldrh	r3, [r0, r7]	@,
	bfi	r3, r2, #7, #9	@ tmp695, <variable>.stMadCcrScl.s32SimlrMax,,
	strh	r3, [r0, r7]	@ movhi	@ tmp695,
.L9:
	ldr	r0, [fp, #-48]	@, %sfp
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L11:
	mov	r1, #41	@,
	mov	r0, #1	@,
	ldr	r2, .L12	@,
	mov	r3, #39	@,
	movw	ip, #:lower16:.LC0	@ tmp140,
	movt	ip, #:upper16:.LC0	@ tmp140,
	str	ip, [sp, #0]	@ tmp140,
	bl	HI_LogOut	@
	mvn	r1, #0	@,
	str	r1, [fp, #-48]	@, %sfp
	b	.L9	@
.L13:
	.align	2
.L12:
	.word	.LANCHOR0+24
	.fnend
	.size	PQ_HAL_SetDeiRegist, .-PQ_HAL_SetDeiRegist
	.align	2
	.global	PQ_HAL_GetMotionHistReg
	.type	PQ_HAL_GetMotionHistReg, %function
PQ_HAL_GetMotionHistReg:
	.fnstart
.LFB1394:
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
	ldr	r0, [r0, #8]	@, <variable>.u32HandleNo
	mov	r5, r1	@ pstMotionHist, pstMotionHist
	bl	PQ_HAL_GetVpssReg	@
	subs	r4, r0, #0	@ pstVpssVirReg,
	beq	.L18	@,
	add	lr, r4, #4224	@, pstVpssVirReg,
	mov	r2, #128	@,
	add	r1, lr, #28	@,,
	add	r0, r5, #8	@, pstMotionHist,
	bl	memcpy	@
	movw	r2, #4380	@ tmp149,
	ldr	ip, [r4, r2]	@ <variable>.VPSS_DIEMTNNUM0.bits.glbm_num0, <variable>.VPSS_DIEMTNNUM0.bits.glbm_num0
	movw	r0, #4384	@ tmp151,
	movw	r3, #4396	@ tmp153,
	movw	r2, #4388	@ tmp154,
	str	ip, [r5, #136]	@ <variable>.VPSS_DIEMTNNUM0.bits.glbm_num0, <variable>.SMALL_MOTION_NUM
	movw	ip, #4404	@ tmp158,
	ldr	r1, [r4, r0]	@ <variable>.VPSS_DIEMTNSUM0.bits.glbm_sum0, <variable>.VPSS_DIEMTNSUM0.bits.glbm_sum0
	mov	r0, #0	@ D.35896,
	str	r1, [r5, #140]	@ <variable>.VPSS_DIEMTNSUM0.bits.glbm_sum0, <variable>.SMALL_MOTION_SUM
	ldr	r1, [r4, r3]	@ <variable>.VPSS_DIEMTNNUM2.bits.glbm_num2, <variable>.VPSS_DIEMTNNUM2.bits.glbm_num2
	ldr	r3, [r4, r2]	@ <variable>.VPSS_DIEMTNNUM1.bits.glbm_num1, <variable>.VPSS_DIEMTNNUM1.bits.glbm_num1
	ldr	r2, [r4, ip]	@ <variable>.VPSS_DIEMTNNUM3.bits.glbm_num3, <variable>.VPSS_DIEMTNNUM3.bits.glbm_num3
	add	ip, r1, r3	@ tmp155, <variable>.VPSS_DIEMTNNUM2.bits.glbm_num2, <variable>.VPSS_DIEMTNNUM1.bits.glbm_num1
	movw	r3, #4400	@ tmp161,
	add	r1, ip, r2	@ tmp160, tmp155, <variable>.VPSS_DIEMTNNUM3.bits.glbm_num3
	movw	r2, #4392	@ tmp162,
	str	r1, [r5, #152]	@ tmp160, <variable>.MIDDL_MOTION_NUM
	movw	ip, #4408	@ tmp166,
	ldr	r1, [r4, r3]	@ <variable>.VPSS_DIEMTNSUM2.bits.glbm_sum2, <variable>.VPSS_DIEMTNSUM2.bits.glbm_sum2
	ldr	r3, [r4, r2]	@ <variable>.VPSS_DIEMTNSUM1.bits.glbm_sum1, <variable>.VPSS_DIEMTNSUM1.bits.glbm_sum1
	ldr	r2, [r4, ip]	@ <variable>.VPSS_DIEMTNSUM3.bits.glbm_sum3, <variable>.VPSS_DIEMTNSUM3.bits.glbm_sum3
	add	ip, r1, r3	@ tmp163, <variable>.VPSS_DIEMTNSUM2.bits.glbm_sum2, <variable>.VPSS_DIEMTNSUM1.bits.glbm_sum1
	mov	r1, #4416	@ tmp171,
	add	r3, ip, r2	@ tmp168, tmp163, <variable>.VPSS_DIEMTNSUM3.bits.glbm_sum3
	movw	ip, #4412	@ tmp169,
	str	r3, [r5, #156]	@ tmp168, <variable>.MIDDL_MOTION_SUM
	ldr	r2, [r4, ip]	@ <variable>.VPSS_DIEMTNNUM4.bits.glbm_num4, <variable>.VPSS_DIEMTNNUM4.bits.glbm_num4
	str	r2, [r5, #144]	@ <variable>.VPSS_DIEMTNNUM4.bits.glbm_num4, <variable>.LARGE_MOTION_NUM
	ldr	r3, [r4, r1]	@ <variable>.VPSS_DIEMTNSUM4.bits.glbm_sum4, <variable>.VPSS_DIEMTNSUM4.bits.glbm_sum4
	str	r3, [r5, #148]	@ <variable>.VPSS_DIEMTNSUM4.bits.glbm_sum4, <variable>.LARGE_MOTION_SUM
.L16:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L18:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L19	@,
	movw	r3, #310	@,
	movw	ip, #:lower16:.LC0	@ tmp141,
	movt	ip, #:upper16:.LC0	@ tmp141,
	str	ip, [sp, #0]	@ tmp141,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35896,
	b	.L16	@
.L20:
	.align	2
.L19:
	.word	.LANCHOR0+44
	.fnend
	.size	PQ_HAL_GetMotionHistReg, .-PQ_HAL_GetMotionHistReg
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.35880, %object
	.size	__func__.35880, 24
__func__.35880:
	.ascii	"PQ_HAL_SetDeiAdjustGain\000"
	.type	__func__.35456, %object
	.size	__func__.35456, 20
__func__.35456:
	.ascii	"PQ_HAL_SetDeiRegist\000"
	.type	__func__.35891, %object
	.size	__func__.35891, 24
__func__.35891:
	.ascii	"PQ_HAL_GetMotionHistReg\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"pointer is NULL!\012\000"
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
