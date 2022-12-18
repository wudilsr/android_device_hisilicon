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
	.file	"pq_mng_ifmd.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_mng_ifmd)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/mng/.pq_mng_ifmd.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/mng/pq_mng_ifmd.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/mng/pq_mng_ifmd.o -O2 -Wall -Wundef
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
	.global	PQ_MNG_DeInitIfmd
	.type	PQ_MNG_DeInitIfmd, %function
PQ_MNG_DeInitIfmd:
	.fnstart
.LFB1397:
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
	ldr	r2, [r3, #0]	@ sg_bIFmdInitFlag, sg_bIFmdInitFlag
	cmp	r2, #0	@ sg_bIFmdInitFlag,
	movne	r2, #0	@ tmp137,
	strne	r2, [r3, #0]	@ tmp137, sg_bIFmdInitFlag
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_DeInitIfmd, .-PQ_MNG_DeInitIfmd
	.align	2
	.type	Check32PdPattern, %function
Check32PdPattern:
	.fnstart
.LFB1402:
	@ args = 4, pretend = 0, frame = 104
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #108
	sub	sp, sp, #108	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	sub	r4, fp, #136	@ tmp147,,
	mov	r5, r0	@ Phase, Phase
	mov	r6, r1	@ Sads, Sads
	mov	r8, r2	@ MaxSad, MaxSad
	mov	r0, r4	@, tmp147
	movw	r1, #:lower16:.LANCHOR1	@,
	mov	r2, #100	@,
	movt	r1, #:upper16:.LANCHOR1	@,
	mov	r7, r3	@ MinSad, MinSad
	bl	memcpy	@
	ldr	r3, [fp, #4]	@ MinSad2nd, MinSad2nd
	add	r5, r5, r5, asl #2	@, tmp154, Phase, Phase,
	cmp	r3, r7, asl #1	@ MinSad2nd, MinSad,
	add	r3, r4, r5, asl #2	@, pMask, tmp147, tmp154,
	movlt	r0, #0	@ RetFlag,
	blt	.L6	@,
	ldr	r2, [r4, r5, asl #2]	@ tmp157,
	cmp	r2, #0	@ tmp157,
	beq	.L7	@,
	ldr	r0, [r6, #0]	@ tmp159,* Sads
	ldr	ip, [r3, #4]	@ tmp163,
	cmp	r8, r0, asl #5	@ MaxSad, tmp159,
	movge	r2, #0	@, PatCnt.574
	movlt	r2, #1	@, PatCnt.574
	cmp	ip, #0	@ tmp163,
	beq	.L9	@,
.L19:
	ldr	r0, [r6, #4]	@ tmp165,
	mov	lr, r0, asl #5	@ tmp167, tmp165,
	cmp	lr, r8	@ tmp167, MaxSad
	movle	r0, r2	@, PatCnt.582, PatCnt.574
	addgt	r0, r2, #1	@,, PatCnt.582, PatCnt.574
	ldr	r2, [r3, #8]	@ tmp171,
	cmp	r2, #0	@ tmp171,
	beq	.L11	@,
.L20:
	ldr	lr, [r6, #8]	@ tmp173,
	mov	ip, lr, asl #5	@ tmp175, tmp173,
	cmp	ip, r8	@ tmp175, MaxSad
	movle	r1, r0	@, PatCnt.592, PatCnt.582
	addgt	r1, r0, #1	@,, PatCnt.592, PatCnt.582
	ldr	r0, [r3, #12]	@ tmp179,
	cmp	r0, #0	@ tmp179,
	beq	.L13	@,
.L21:
	ldr	ip, [r6, #12]	@ tmp181,
	ldr	r3, [r3, #16]	@ tmp187,
	mov	r2, ip, asl #5	@ tmp183, tmp181,
	cmp	r2, r8	@ tmp183, MaxSad
	movle	r2, r1	@, PatCnt.602, PatCnt.592
	addgt	r2, r1, #1	@,, PatCnt.602, PatCnt.592
	cmp	r3, #0	@ tmp187,
	bne	.L15	@,
.L22:
	ldr	r1, [r6, #16]	@ tmp189,
	cmp	r1, r7	@ tmp189, MinSad
	movne	r0, r2	@, PatCnt, PatCnt.602
	addeq	r0, r2, #1	@,, PatCnt, PatCnt.602
.L16:
	cmp	r0, #4	@ PatCnt,
	movle	r0, #0	@, RetFlag
	movgt	r0, #1	@, RetFlag
.L6:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L7:
	ldr	r1, [r6, #0]	@ tmp161,* Sads
	ldr	ip, [r3, #4]	@ tmp163,
	cmp	r1, r7	@ tmp161, MinSad
	movne	r2, #0	@, PatCnt.574
	moveq	r2, #1	@, PatCnt.574
	cmp	ip, #0	@ tmp163,
	bne	.L19	@,
.L9:
	ldr	r1, [r6, #4]	@ tmp169,
	cmp	r1, r7	@ tmp169, MinSad
	movne	r0, r2	@, PatCnt.582, PatCnt.574
	addeq	r0, r2, #1	@,, PatCnt.582, PatCnt.574
	ldr	r2, [r3, #8]	@ tmp171,
	cmp	r2, #0	@ tmp171,
	bne	.L20	@,
.L11:
	ldr	r1, [r6, #8]	@ tmp177,
	cmp	r1, r7	@ tmp177, MinSad
	movne	r1, r0	@, PatCnt.592, PatCnt.582
	addeq	r1, r0, #1	@,, PatCnt.592, PatCnt.582
	ldr	r0, [r3, #12]	@ tmp179,
	cmp	r0, #0	@ tmp179,
	bne	.L21	@,
.L13:
	ldr	lr, [r6, #12]	@ tmp185,
	ldr	r3, [r3, #16]	@ tmp187,
	cmp	lr, r7	@ tmp185, MinSad
	movne	r2, r1	@, PatCnt.602, PatCnt.592
	addeq	r2, r1, #1	@,, PatCnt.602, PatCnt.592
	cmp	r3, #0	@ tmp187,
	beq	.L22	@,
.L15:
	ldr	ip, [r6, #16]	@ tmp192,
	mov	r0, ip, asl #5	@ tmp194, tmp192,
	cmp	r0, r8	@ tmp194, MaxSad
	movle	r0, r2	@, PatCnt, PatCnt.602
	addgt	r0, r2, #1	@,, PatCnt, PatCnt.602
	b	.L16	@
	.fnend
	.size	Check32PdPattern, .-Check32PdPattern
	.global	__aeabi_idiv
	.align	2
	.type	Detect22Pld, %function
Detect22Pld:
	.fnstart
.LFB1407:
	@ args = 4, pretend = 0, frame = 168
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #172
	sub	sp, sp, #172	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r6, r3	@ Pld22LockState, Pld22LockState
	ldr	r3, [fp, #4]	@ s32DeiMdLum, s32DeiMdLum
	mov	r7, r0	@ Is2ndFld, Is2ndFld
	ldr	ip, [r6, #4]	@ tmp214,
	mov	r5, r1	@ pstFmdStatInfo, pstFmdStatInfo
	ldr	r0, [r6, #8]	@ tmp215,
	cmp	r3, #1	@ s32DeiMdLum,
	mov	r4, r2	@ pCntxt22, pCntxt22
	str	ip, [r6, #0]	@ tmp214,* Pld22LockState
	str	r0, [r6, #4]	@ tmp215,
	beq	.L137	@,
	ldrb	r9, [r2, #91]	@ zero_extendqisi2	@,
	rsbs	r7, r7, #1	@ phase, Is2ndFld
	movcc	r7, #0	@ phase
	cmp	r7, #1	@ phase,
	str	r9, [fp, #-160]	@, %sfp
	ldrb	r0, [r2, #92]	@ zero_extendqisi2	@,
	ldrb	r1, [r2, #90]	@ zero_extendqisi2	@ tmp2862,
	str	r0, [fp, #-168]	@, %sfp
	orr	sl, r1, r9, asl #8	@, tmp1211, tmp2862,,
	ldrb	r2, [r2, #93]	@ zero_extendqisi2	@,
	orr	r8, sl, r0, asl #16	@, tmp1214, tmp1211,,
	str	r2, [fp, #-156]	@, %sfp
	orr	r8, r8, r2, asl #24	@, lstLock, tmp1214,,
	ldr	r9, [r5, #124]	@, <variable>.frmHstBin.HISTOGRAM_BIN_2
	str	r9, [fp, #-188]	@, %sfp
	ldr	r0, [r5, #132]	@, <variable>.frmHstBin.HISTOGRAM_BIN_4
	str	r0, [fp, #-184]	@, %sfp
	ldr	sl, [r5, #128]	@, <variable>.frmHstBin.HISTOGRAM_BIN_3
	str	sl, [fp, #-180]	@, %sfp
	ldr	r2, [r5, #120]	@, <variable>.frmHstBin.HISTOGRAM_BIN_1
	str	r2, [fp, #-192]	@, %sfp
	ldr	sl, [r5, #0]	@ Frame_IT_diff, <variable>.frmITDiff
	beq	.L138	@,
	cmp	r3, #0	@ s32DeiMdLum,
	bne	.L65	@,
	ldrb	ip, [r4, #49]	@ zero_extendqisi2	@ tmp1346,
	ldrb	r9, [r4, #48]	@ zero_extendqisi2	@ tmp1345,
	ldrb	r0, [r4, #50]	@ zero_extendqisi2	@ tmp1349,
	ldrb	r2, [r4, #51]	@ zero_extendqisi2	@ tmp1352,
	orr	r3, r9, ip, asl #8	@, tmp1348, tmp1345, tmp1346,
	ldr	r9, [r5, #24]	@ <variable>.frmPcc.PCC_FWD, <variable>.frmPcc.PCC_FWD
	orr	ip, r3, r0, asl #16	@, tmp1351, tmp1348, tmp1349,
	ldrb	r0, [r4, #53]	@ zero_extendqisi2	@ tmp1391,
	orr	r3, ip, r2, asl #24	@, tmp1354, tmp1351, tmp1352,
	ldrb	r2, [r4, #52]	@ zero_extendqisi2	@ tmp1390,
	add	r3, r3, r9	@ prephitmp.860, tmp1354, <variable>.frmPcc.PCC_FWD
	ldrb	ip, [r4, #54]	@ zero_extendqisi2	@ tmp1394,
	orr	r2, r2, r0, asl #8	@, tmp1393, tmp1390, tmp1391,
	ubfx	r0, r3, #8, #8	@ tmp1365, prephitmp.860,,
	strb	r0, [r4, #69]	@ tmp1365,
	ldrb	r0, [r4, #57]	@ zero_extendqisi2	@,
	orr	r2, r2, ip, asl #16	@, tmp1396, tmp1393, tmp1394,
	strb	r3, [r4, #68]	@ prephitmp.860,
	ubfx	ip, r3, #16, #8	@ tmp1374, prephitmp.860,,
	ldrb	r9, [r4, #55]	@ zero_extendqisi2	@ tmp1397,
	str	r0, [fp, #-164]	@, %sfp
	mov	r0, r3, lsr #24	@ tmp1382, prephitmp.860,
	strb	ip, [r4, #70]	@ tmp1374,
	ldrb	ip, [r4, #58]	@ zero_extendqisi2	@,
	orr	r2, r2, r9, asl #24	@, tmp1399, tmp1396, tmp1397,
	strb	r0, [r4, #71]	@ tmp1382,
	ldrb	r0, [r4, #56]	@ zero_extendqisi2	@ tmp1435,
	str	ip, [fp, #-172]	@, %sfp
	ldr	r9, [r5, #28]	@, <variable>.frmPcc.PCC_BWD
	ldrb	ip, [r4, #59]	@ zero_extendqisi2	@,
	add	r2, r2, r9	@ prephitmp.859, tmp1399,
	ldr	r9, [fp, #-164]	@, %sfp
	str	ip, [fp, #-152]	@, %sfp
	strb	r2, [r4, #72]	@ prephitmp.859,
	orr	ip, r0, r9, asl #8	@, tmp1438, tmp1435,,
	ldr	r9, [fp, #-172]	@, %sfp
	ubfx	r0, r2, #8, #8	@ tmp1410, prephitmp.859,,
	strb	r0, [r4, #73]	@ tmp1410,
	mov	r0, r2, lsr #24	@ tmp1427, prephitmp.859,
	strb	r0, [r4, #75]	@ tmp1427,
	orr	ip, ip, r9, asl #16	@, tmp1441, tmp1438,,
	ubfx	r9, r2, #16, #8	@ tmp1419, prephitmp.859,,
	strb	r9, [r4, #74]	@ tmp1419,
	ldr	r9, [fp, #-152]	@, %sfp
	ldr	r0, [r5, #32]	@ <variable>.frmPcc.PCC_CRSS, <variable>.frmPcc.PCC_CRSS
	orr	ip, ip, r9, asl #24	@, tmp1444, tmp1441,,
	add	ip, ip, r0	@ prephitmp.651, tmp1444, <variable>.frmPcc.PCC_CRSS
	strb	ip, [r4, #76]	@ prephitmp.651,
	ubfx	r0, ip, #8, #8	@ tmp1455, prephitmp.651,,
	ubfx	r9, ip, #16, #8	@ tmp1464, prephitmp.651,,
	strb	r0, [r4, #77]	@ tmp1455,
	mov	r0, ip, lsr #24	@ tmp1472, prephitmp.651,
	strb	r9, [r4, #78]	@ tmp1464,
	strb	r0, [r4, #79]	@ tmp1472,
	ldrb	r0, [r5, #24]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_FWD, <variable>.frmPcc.PCC_FWD
	ldr	r9, [r5, #40]	@, <variable>.frmPcc.PCC_FWD_TKR
	str	r9, [fp, #-172]	@, %sfp
	strb	r0, [r4, #48]	@ <variable>.frmPcc.PCC_FWD,
	ldrb	r9, [r5, #25]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_FWD, <variable>.frmPcc.PCC_FWD
	strb	r9, [r4, #49]	@ <variable>.frmPcc.PCC_FWD,
	ldrb	r0, [r5, #26]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_FWD, <variable>.frmPcc.PCC_FWD
	strb	r0, [r4, #50]	@ <variable>.frmPcc.PCC_FWD,
	ldrb	r9, [r5, #27]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_FWD, <variable>.frmPcc.PCC_FWD
	strb	r9, [r4, #51]	@ <variable>.frmPcc.PCC_FWD,
	ldrb	r0, [r5, #28]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_BWD, <variable>.frmPcc.PCC_BWD
	strb	r0, [r4, #52]	@ <variable>.frmPcc.PCC_BWD,
	ldrb	r9, [r5, #29]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_BWD, <variable>.frmPcc.PCC_BWD
	strb	r9, [r4, #53]	@ <variable>.frmPcc.PCC_BWD,
	ldrb	r0, [r5, #30]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_BWD, <variable>.frmPcc.PCC_BWD
	strb	r0, [r4, #54]	@ <variable>.frmPcc.PCC_BWD,
	ldrb	r9, [r5, #31]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_BWD, <variable>.frmPcc.PCC_BWD
	strb	r9, [r4, #55]	@ <variable>.frmPcc.PCC_BWD,
	ldrb	r0, [r5, #32]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_CRSS, <variable>.frmPcc.PCC_CRSS
	strb	r0, [r4, #56]	@ <variable>.frmPcc.PCC_CRSS,
	ldrb	r9, [r5, #33]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_CRSS, <variable>.frmPcc.PCC_CRSS
	strb	r9, [r4, #57]	@ <variable>.frmPcc.PCC_CRSS,
	ldrb	r0, [r5, #34]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_CRSS, <variable>.frmPcc.PCC_CRSS
	strb	r0, [r4, #58]	@ <variable>.frmPcc.PCC_CRSS,
	ldrb	r9, [r5, #35]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_CRSS, <variable>.frmPcc.PCC_CRSS
	strb	r9, [r4, #59]	@ <variable>.frmPcc.PCC_CRSS,
.L67:
	ldr	r0, [r5, #16]	@, <variable>.frmUm.nonmatch_UM2
	str	r0, [fp, #-164]	@, %sfp
	cmp	r2, ip	@ prephitmp.859, prephitmp.651
	movge	r0, r2	@ max_crss_nonmatch, prephitmp.859
	movlt	r0, ip	@ max_crss_nonmatch, prephitmp.651
	ldr	r9, [r5, #4]	@, <variable>.frmUm.match_UM
	str	r9, [fp, #-208]	@, %sfp
	ldr	r9, [r5, #8]	@, <variable>.frmUm.nonmatch_UM
	str	r9, [fp, #-152]	@, %sfp
	ldr	r5, [r5, #12]	@, <variable>.frmUm.match_UM2
	str	r5, [fp, #-212]	@, %sfp
	ldr	r5, [fp, #-208]	@, %sfp
	cmp	r9, r5	@,
	movlt	r9, r5	@,
	ldr	r5, [fp, #-212]	@, %sfp
	str	r9, [fp, #-176]	@, %sfp
	ldr	r9, [fp, #-164]	@, %sfp
	cmp	r9, r5	@,
	movlt	r9, r5	@,
	cmp	r0, #4	@ max_crss_nonmatch,
	cmple	r3, #4	@, prephitmp.860,
	str	r9, [fp, #-196]	@, %sfp
	bgt	.L68	@,
	ldr	r5, [fp, #-176]	@, %sfp
	cmp	r9, #500	@,
	cmplt	r5, #500	@,,
	bge	.L69	@,
	ldr	r9, [fp, #-180]	@, %sfp
	cmp	r9, #1	@,
	ble	.L139	@,
.L69:
	cmp	r3, #120	@ prephitmp.860,
	cmple	r0, #120	@, max_crss_nonmatch,
	ble	.L71	@,
	cmp	r3, #10	@ prephitmp.860,
	movge	r9, r3	@ match_weave, prephitmp.860
	movlt	r9, #10	@ match_weave,
	cmp	r2, ip	@ prephitmp.859, prephitmp.651
	movlt	r1, r2	@ min_crss_nonmatch, prephitmp.859
	movge	r1, ip	@ min_crss_nonmatch, prephitmp.651
	mov	r5, r9, asl #2	@ tmp2848, match_weave,
	mov	r3, r1, asl #1	@ tmp2849, min_crss_nonmatch,
	cmp	r5, r3	@ tmp2848, tmp2849
	bge	.L72	@,
	cmp	r1, #120	@ min_crss_nonmatch,
	ble	.L73	@,
	cmp	r0, #800	@ max_crss_nonmatch,
	ble	.L74	@,
	add	r2, r9, r9, asl #1	@, tmp1629, match_weave, match_weave,
	cmp	r3, r2	@ tmp2849, tmp1629
	ble	.L74	@,
	cmp	r0, r3	@ max_crss_nonmatch, tmp2849
	bgt	.L83	@,
	mov	ip, r1, asl #2	@ tmp1636, min_crss_nonmatch,
	add	r5, ip, r1	@ tmp1637, tmp1636, min_crss_nonmatch
	cmp	r5, r0, asl #2	@ tmp1637, max_crss_nonmatch,
	ble	.L76	@,
	cmp	r1, r2	@ min_crss_nonmatch, tmp1629
	ble	.L77	@,
	add	r5, r7, r4	@ tmp1640, phase, pCntxt22
	mov	r0, #0	@,
	str	r0, [fp, #-168]	@, %sfp
	ldrb	r2, [r5, #88]	@ zero_extendqisi2	@ tmp1646, <variable>.phaseCnt
	add	r1, r2, #1	@ tmp1647, tmp1646,
	strb	r1, [r5, #88]	@ tmp1647, <variable>.phaseCnt
	b	.L70	@
.L119:
	cmp	r0, #19	@ iftmp.469,
	bgt	.L140	@,
	mov	r0, #0	@ tmp2363,
	strb	r0, [r4, #93]	@ tmp2363,
	strb	r0, [r4, #90]	@ tmp2363,
	strb	r0, [r4, #91]	@ tmp2363,
	strb	r0, [r4, #92]	@ tmp2363,
.L121:
	ldrb	r0, [r4, #13]	@ zero_extendqisi2	@ tmp2378,
	ubfx	r1, sl, #8, #8	@, Frame_IT_diff,,
	ldrb	r2, [r4, #12]	@ zero_extendqisi2	@ tmp2377,
	movw	r5, #:lower16:-3000	@,
	ldrb	ip, [r4, #14]	@ zero_extendqisi2	@ tmp2381,
	movt	r5, #:upper16:-3000	@,
	str	r1, [fp, #-164]	@, %sfp
	orr	r7, r2, r0, asl #8	@, tmp2380, tmp2377, tmp2378,
	ldrb	r1, [r4, #9]	@ zero_extendqisi2	@ tmp2422,
	movw	r9, #:lower16:1717986919	@ tmp2592,
	ldrb	r3, [r4, #8]	@ zero_extendqisi2	@ tmp2421,
	orr	r0, r7, ip, asl #16	@, tmp2383, tmp2380, tmp2381,
	ldrb	r2, [r4, #15]	@ zero_extendqisi2	@ tmp2384,
	movt	r9, #:upper16:1717986919	@ tmp2592,
	ldrb	ip, [r4, #10]	@ zero_extendqisi2	@ tmp2425,
	orr	r7, r3, r1, asl #8	@, tmp2424, tmp2421, tmp2422,
	str	r5, [fp, #-160]	@, %sfp
	ldrb	r3, [r4, #11]	@ zero_extendqisi2	@,
	orr	r0, r0, r2, asl #24	@, tmp2386, tmp2383, tmp2384,
	ldrb	r5, [r4, #5]	@ zero_extendqisi2	@ tmp2466,
	orr	r1, r7, ip, asl #16	@, tmp2427, tmp2424, tmp2425,
	add	r7, r0, sl	@ tmp2587, tmp2386, Frame_IT_diff
	str	r3, [fp, #-172]	@, %sfp
	ldrb	r3, [r4, #1]	@ zero_extendqisi2	@,
	ldrb	r2, [r4, #4]	@ zero_extendqisi2	@ tmp2465,
	ldrb	ip, [r4, #6]	@ zero_extendqisi2	@ tmp2469,
	str	r3, [fp, #-152]	@, %sfp
	orr	r2, r2, r5, asl #8	@, tmp2468, tmp2465, tmp2466,
	ldrb	r3, [r4, #7]	@ zero_extendqisi2	@,
	ldr	r5, [fp, #-172]	@, %sfp
	orr	r2, r2, ip, asl #16	@, tmp2471, tmp2468, tmp2469,
	ldr	ip, [fp, #-152]	@, %sfp
	str	r3, [fp, #-156]	@, %sfp
	ldrb	r3, [r4, #0]	@ zero_extendqisi2	@ tmp2509,* pCntxt22
	orr	r1, r1, r5, asl #24	@, tmp2430, tmp2427,,
	ldrb	r5, [r4, #2]	@ zero_extendqisi2	@ tmp2513,
	add	r7, r7, r1	@, tmp2587, tmp2430
	orr	r3, r3, ip, asl #8	@, tmp2512, tmp2509,,
	ldr	ip, [fp, #-156]	@, %sfp
	str	r7, [fp, #-172]	@, %sfp
	strb	r0, [r4, #16]	@ tmp2386,
	orr	r3, r3, r5, asl #16	@, tmp2515, tmp2512, tmp2513,
	ldrb	r7, [r4, #3]	@ zero_extendqisi2	@ tmp2516,
	orr	r2, r2, ip, asl #24	@, tmp2474, tmp2471,,
	ldr	r5, [fp, #-172]	@, %sfp
	strb	r1, [r4, #12]	@ tmp2430,
	orr	r3, r3, r7, asl #24	@, tmp2518, tmp2515, tmp2516,
	add	ip, r5, r2	@ tmp2589,, tmp2474
	add	ip, ip, r3	@ tmp2590, tmp2589, tmp2518
	ubfx	r7, r0, #8, #8	@ tmp2396, tmp2386,,
	strb	r2, [r4, #8]	@ tmp2474,
	smull	r5, r9, r9, ip	@, tmp2591, tmp2592, tmp2590
	ubfx	r5, r0, #16, #8	@ tmp2405, tmp2386,,
	strb	r3, [r4, #4]	@ tmp2518,
	mov	r0, r0, lsr #24	@ tmp2413, tmp2386,
	strb	r7, [r4, #17]	@ tmp2396,
	ubfx	r7, r1, #16, #8	@ tmp2449, tmp2430,,
	strb	r5, [r4, #18]	@ tmp2405,
	ubfx	r5, r1, #8, #8	@ tmp2440, tmp2430,,
	strb	r0, [r4, #19]	@ tmp2413,
	ubfx	r0, r2, #8, #8	@ tmp2484, tmp2474,,
	strb	r5, [r4, #13]	@ tmp2440,
	mov	r5, r1, lsr #24	@ tmp2457, tmp2430,
	strb	r7, [r4, #14]	@ tmp2449,
	ubfx	r1, r2, #16, #8	@ tmp2493, tmp2474,,
	strb	r5, [r4, #15]	@ tmp2457,
	ubfx	r7, r3, #8, #8	@ tmp2528, tmp2518,,
	strb	r0, [r4, #9]	@ tmp2484,
	ubfx	r5, r3, #16, #8	@ tmp2537, tmp2518,,
	strb	r1, [r4, #10]	@ tmp2493,
	mov	r0, r3, lsr #24	@ tmp2545, tmp2518,
	strb	r7, [r4, #5]	@ tmp2528,
	mov	r2, r2, lsr #24	@ tmp2501, tmp2474,
	strb	r5, [r4, #6]	@ tmp2537,
	mov	r1, ip, asr #31	@ tmp2594, tmp2590,
	strb	r0, [r4, #7]	@ tmp2545,
	rsb	r9, r1, r9, asr #1	@, D.37904, tmp2594, tmp2591,
	strb	r2, [r4, #11]	@ tmp2501,
	ubfx	r1, r9, #8, #8	@ tmp2604, D.37904,,
	strb	sl, [r4, #0]	@ Frame_IT_diff,* pCntxt22
	and	r0, r9, #255	@ tmp2595, D.37904,
	ldrb	r3, [r4, #21]	@ zero_extendqisi2	@,
	ldr	r2, [fp, #-164]	@, %sfp
	ldrb	r5, [r4, #29]	@ zero_extendqisi2	@ tmp2630,
	strb	r2, [r4, #1]	@,
	ubfx	r2, r9, #16, #8	@ tmp2613, D.37904,,
	str	r3, [fp, #-196]	@, %sfp
	mov	r3, r9, lsr #24	@ tmp2621, D.37904,
	ldrb	r7, [r4, #30]	@ zero_extendqisi2	@,
	ldrb	ip, [r4, #28]	@ zero_extendqisi2	@ tmp2629,
	str	r7, [fp, #-164]	@, %sfp
	ubfx	r7, sl, #16, #8	@, Frame_IT_diff,,
	str	r7, [fp, #-156]	@, %sfp
	orr	ip, ip, r5, asl #8	@, tmp2632, tmp2629, tmp2630,
	ldrb	r7, [r4, #20]	@ zero_extendqisi2	@,
	mov	r5, sl, lsr #24	@, Frame_IT_diff,
	str	r7, [fp, #-176]	@, %sfp
	ldrb	r7, [r4, #22]	@ zero_extendqisi2	@,
	str	r5, [fp, #-152]	@, %sfp
	ldr	r5, [fp, #-196]	@, %sfp
	str	r7, [fp, #-200]	@, %sfp
	ldrb	r7, [r4, #31]	@ zero_extendqisi2	@,
	ldr	sl, [fp, #-176]	@, %sfp
	str	r7, [fp, #-172]	@, %sfp
	orr	r7, sl, r5, asl #8	@, tmp2642,,,
	ldr	r5, [fp, #-164]	@, %sfp
	ldrb	sl, [r4, #23]	@ zero_extendqisi2	@ tmp2646,
	orr	ip, ip, r5, asl #16	@, tmp2635, tmp2632,,
	ldr	r5, [fp, #-200]	@, %sfp
	orr	r7, r7, r5, asl #16	@, tmp2645, tmp2642,,
	ldr	r5, [fp, #-156]	@, %sfp
	orr	r7, r7, sl, asl #24	@, tmp2648, tmp2645, tmp2646,
	strb	r5, [r4, #2]	@,
	ldr	r5, [fp, #-172]	@, %sfp
	orr	ip, ip, r5, asl #24	@, tmp2638, tmp2635,,
	ldr	r5, [fp, #-152]	@, %sfp
	rsb	ip, r7, ip	@ tmp2649, tmp2648, tmp2638
	movw	r7, #3000	@ tmp2651,
	add	sl, ip, r9	@ iftmp.856, tmp2649, D.37904
	strb	r5, [r4, #3]	@,
	strb	r1, [r4, #21]	@ tmp2604,
	strb	r2, [r4, #22]	@ tmp2613,
	strb	r0, [r4, #20]	@ tmp2595,
	ldr	r5, [fp, #-160]	@, %sfp
	strb	r1, [r4, #25]	@ tmp2604,
	cmp	sl, r5	@ iftmp.856,
	movlt	sl, r5	@ iftmp.856,
	strb	r2, [r4, #26]	@ tmp2613,
	cmp	sl, r7	@ iftmp.856, tmp2651
	movge	sl, r7	@ iftmp.471, tmp2651
	strb	r3, [r4, #23]	@ tmp2621,
	cmp	sl, #1000	@ iftmp.471,
	cmpge	r8, #1	@, lstLock,
	ubfx	r9, sl, #8, #8	@ tmp2661, iftmp.471,,
	mov	r2, sl, lsr #24	@ tmp2678, iftmp.471,
	ubfx	r1, sl, #16, #8	@ tmp2670, iftmp.471,,
	strb	r2, [r4, #31]	@ tmp2678,
	mov	r2, #0	@ tmp2390,
	strb	r0, [r4, #24]	@ tmp2595,
	strb	r9, [r4, #29]	@ tmp2661,
	strb	r1, [r4, #30]	@ tmp2670,
	strb	r3, [r4, #27]	@ tmp2621,
	strb	sl, [r4, #28]	@ iftmp.471,
	bne	.L123	@,
	ldr	sl, [fp, #-168]	@, %sfp
	cmp	sl, r2	@,
	bne	.L141	@,
.L123:
	ldrb	ip, [r4, #91]	@ zero_extendqisi2	@ tmp2868,
	ldrb	r3, [r4, #90]	@ zero_extendqisi2	@ tmp2867,
	ldrb	r0, [r4, #92]	@ zero_extendqisi2	@ tmp2869,
	ldrb	r1, [r4, #93]	@ zero_extendqisi2	@ tmp2870,
	orr	r7, r3, ip, asl #8	@, tmp2751, tmp2867, tmp2868,
	orr	r5, r7, r0, asl #16	@, tmp2754, tmp2751, tmp2869,
	orr	r9, r5, r1, asl #24	@, tmp2757, tmp2754, tmp2870,
	cmp	r9, #1	@ tmp2757,
	cmpeq	r8, #0	@, lstLock,
	moveq	r9, #0	@ tmp2767,
	streqb	r9, [r4, #31]	@ tmp2767,
	streqb	r9, [r4, #28]	@ tmp2767,
	streqb	r9, [r4, #29]	@ tmp2767,
	streqb	r9, [r4, #30]	@ tmp2767,
.L124:
	ldr	r5, [fp, #-184]	@, %sfp
	orr	r9, r3, ip, asl #8	@, tmp2824, tmp2867, tmp2868,
	ldr	sl, [fp, #-180]	@, %sfp
	orr	r8, r9, r0, asl #16	@, tmp2827, tmp2824, tmp2869,
	ldr	r7, [fp, #-188]	@, %sfp
	orr	r8, r8, r1, asl #24	@, lstLock, tmp2827, tmp2870,
	add	r2, sl, r5, asl #1	@, tmp2782,,,
	ldr	r9, [fp, #-192]	@, %sfp
	add	r3, r7, r2, asl #1	@, tmp2784,, tmp2782,
	add	r3, r9, r3, asl #1	@, tmp2786,, tmp2784,
.L132:
	ubfx	r1, r3, #8, #8	@ tmp2796, tmp2786,,
	mov	r0, r3, lsr #24	@ tmp2813, tmp2786,
	ubfx	ip, r3, #16, #8	@ tmp2805, tmp2786,,
	strb	r3, [r4, #32]	@ tmp2786,
	strb	r1, [r4, #33]	@ tmp2796,
	strb	r0, [r4, #35]	@ tmp2813,
	strb	ip, [r4, #34]	@ tmp2805,
.L65:
	str	r8, [r6, #8]	@ lstLock,
	mov	r0, r8	@, lstLock
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L68:
	cmp	r3, #800	@ prephitmp.860,
	ble	.L69	@,
	add	r3, r7, r4	@ tmp1611, phase, pCntxt22
	mov	r9, #1	@,
	str	r9, [fp, #-168]	@, %sfp
	ldrb	ip, [r3, #88]	@ zero_extendqisi2	@ tmp1617, <variable>.phaseCnt
	sub	r2, ip, #15	@ tmp1618, tmp1617,
	strb	r2, [r3, #88]	@ tmp1618, <variable>.phaseCnt
.L70:
	ldr	r3, [fp, #-172]	@, %sfp
	mov	r5, r3, asl #5	@ tmp2270,,
	cmp	r5, #127	@ tmp2270,
	addgt	r7, r7, r4	@ tmp2272, phase, pCntxt22
	ldrgtb	r5, [r7, #88]	@ zero_extendqisi2	@ tmp2278, <variable>.phaseCnt
	subgt	r5, r5, #5	@ tmp2279, tmp2278,
	strgtb	r5, [r7, #88]	@ tmp2279, <variable>.phaseCnt
	ldr	ip, [fp, #-168]	@, %sfp
	ldrsb	r9, [r4, #88]	@ <variable>.phaseCnt, <variable>.phaseCnt
	cmp	ip, #1	@,
	ldrsb	r1, [r4, #89]	@ <variable>.phaseCnt, <variable>.phaseCnt
	ldreqb	r0, [r4, #37]	@ zero_extendqisi2	@ tmp2282,
	movne	r5, #0	@ iftmp.468,
	ldreqb	r5, [r4, #38]	@ zero_extendqisi2	@ tmp2285,
	ldreqb	r3, [r4, #36]	@ zero_extendqisi2	@ tmp2281,
	ldreqb	ip, [r4, #39]	@ zero_extendqisi2	@ tmp2288,
	orreq	r3, r3, r0, asl #8	@, tmp2284, tmp2281, tmp2282,
	orreq	r5, r3, r5, asl #16	@, tmp2287, tmp2284, tmp2285,
	orreq	r5, r5, ip, asl #24	@, tmp2290, tmp2287, tmp2288,
	addeq	r5, r5, #1	@ iftmp.468, tmp2290,
	cmp	r9, #32	@ <variable>.phaseCnt,
	movge	r9, #32	@ iftmp.854,
	bic	r3, r9, r9, asr #31	@ tmp2330, iftmp.854
	cmp	r1, #32	@ <variable>.phaseCnt,
	movge	r1, #32	@ iftmp.855,
	bic	ip, r1, r1, asr #31	@ tmp2337, iftmp.855
	ubfx	r7, r5, #8, #8	@ tmp2300, iftmp.468,,
	uxtb	r0, r3	@ iftmp.469, tmp2330
	strb	r0, [r4, #88]	@ iftmp.469, <variable>.phaseCnt
	mov	r2, r5, lsr #24	@ tmp2317, iftmp.468,
	strb	r7, [r4, #37]	@ tmp2300,
	sxtb	r0, r0	@ iftmp.469, iftmp.469
	uxtb	r1, ip	@ iftmp.470, tmp2337
	cmp	r0, #24	@ iftmp.469,
	ubfx	r7, r5, #16, #8	@ tmp2309, iftmp.468,,
	strb	r2, [r4, #39]	@ tmp2317,
	mov	r3, #0	@ tmp2294,
	strb	r5, [r4, #36]	@ iftmp.468,
	strb	r1, [r4, #89]	@ iftmp.470, <variable>.phaseCnt
	strb	r7, [r4, #38]	@ tmp2309,
	ble	.L119	@,
	sxtb	r1, r1	@ iftmp.470, iftmp.470
	cmp	r1, #24	@ iftmp.470,
	ble	.L120	@,
	mov	r5, #1	@ tmp2345,
	strb	r3, [r4, #93]	@ tmp2294,
	strb	r5, [r4, #90]	@ tmp2345,
	strb	r3, [r4, #91]	@ tmp2294,
	strb	r3, [r4, #92]	@ tmp2294,
	b	.L121	@
.L140:
	sxtb	r1, r1	@ iftmp.470, iftmp.470
.L120:
	cmp	r1, #19	@ iftmp.470,
	bgt	.L121	@,
	mov	r0, #0	@ tmp2363,
	strb	r0, [r4, #93]	@ tmp2363,
	strb	r0, [r4, #90]	@ tmp2363,
	strb	r0, [r4, #91]	@ tmp2363,
	strb	r0, [r4, #92]	@ tmp2363,
	b	.L121	@
.L138:
	cmp	r3, #0	@ s32DeiMdLum,
	bne	.L65	@,
	ldrb	r2, [r5, #20]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_FFWD, <variable>.frmPcc.PCC_FFWD
	ldrb	ip, [r4, #77]	@ zero_extendqisi2	@,
	ldrb	r0, [r4, #69]	@ zero_extendqisi2	@ tmp1316,
	strb	r2, [r4, #48]	@ <variable>.frmPcc.PCC_FFWD,
	ldrb	r3, [r5, #21]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_FFWD, <variable>.frmPcc.PCC_FFWD
	ldrb	r9, [r4, #73]	@ zero_extendqisi2	@ tmp1326,
	str	ip, [fp, #-172]	@, %sfp
	strb	r3, [r4, #49]	@ <variable>.frmPcc.PCC_FFWD,
	ldrb	ip, [r5, #22]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_FFWD, <variable>.frmPcc.PCC_FFWD
	ldrb	r2, [r4, #68]	@ zero_extendqisi2	@ tmp1315,
	ldrb	r3, [r4, #70]	@ zero_extendqisi2	@ tmp1319,
	strb	ip, [r4, #50]	@ <variable>.frmPcc.PCC_FFWD,
	orr	r0, r2, r0, asl #8	@, tmp1318, tmp1315, tmp1316,
	ldrb	ip, [r5, #23]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_FFWD, <variable>.frmPcc.PCC_FFWD
	ldrb	r2, [r4, #72]	@ zero_extendqisi2	@ tmp1325,
	orr	r9, r2, r9, asl #8	@,, tmp1325, tmp1326,
	orr	r2, r0, r3, asl #16	@,, tmp1318, tmp1319,
	str	r9, [fp, #-164]	@, %sfp
	ldrb	r9, [r4, #74]	@ zero_extendqisi2	@ tmp1329,
	str	r2, [fp, #-152]	@, %sfp
	strb	ip, [r4, #51]	@ <variable>.frmPcc.PCC_FFWD,
	ldr	ip, [fp, #-172]	@, %sfp
	ldrb	r2, [r5, #24]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_FWD, <variable>.frmPcc.PCC_FWD
	ldr	r0, [fp, #-164]	@, %sfp
	ldrb	r3, [r4, #76]	@ zero_extendqisi2	@ tmp1335,
	orr	r9, r0, r9, asl #16	@,,, tmp1329,
	orr	r3, r3, ip, asl #8	@, tmp1338, tmp1335,,
	ldrb	ip, [r4, #78]	@ zero_extendqisi2	@ tmp1339,
	str	r9, [fp, #-164]	@, %sfp
	strb	r2, [r4, #52]	@ <variable>.frmPcc.PCC_FWD,
	ldrb	r9, [r5, #25]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_FWD, <variable>.frmPcc.PCC_FWD
	orr	r2, r3, ip, asl #16	@,, tmp1338, tmp1339,
	ldrb	r0, [r4, #71]	@ zero_extendqisi2	@ tmp1322,
	ldr	ip, [fp, #-152]	@, %sfp
	str	r2, [fp, #-172]	@, %sfp
	strb	r9, [r4, #53]	@ <variable>.frmPcc.PCC_FWD,
	orr	r3, ip, r0, asl #24	@, prephitmp.860,, tmp1322,
	ldrb	r2, [r4, #75]	@ zero_extendqisi2	@ tmp1332,
	ldr	r9, [fp, #-164]	@, %sfp
	ldrb	ip, [r4, #79]	@ zero_extendqisi2	@ tmp1342,
	ldrb	r0, [r5, #26]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_FWD, <variable>.frmPcc.PCC_FWD
	orr	r2, r9, r2, asl #24	@, prephitmp.859,, tmp1332,
	ldr	r9, [fp, #-172]	@, %sfp
	strb	r0, [r4, #54]	@ <variable>.frmPcc.PCC_FWD,
	orr	ip, r9, ip, asl #24	@, prephitmp.651,, tmp1342,
	ldrb	r9, [r5, #27]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_FWD, <variable>.frmPcc.PCC_FWD
	strb	r9, [r4, #55]	@ <variable>.frmPcc.PCC_FWD,
	ldrb	r0, [r5, #32]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_CRSS, <variable>.frmPcc.PCC_CRSS
	strb	r0, [r4, #56]	@ <variable>.frmPcc.PCC_CRSS,
	ldrb	r9, [r5, #33]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_CRSS, <variable>.frmPcc.PCC_CRSS
	strb	r9, [r4, #57]	@ <variable>.frmPcc.PCC_CRSS,
	ldrb	r0, [r5, #34]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_CRSS, <variable>.frmPcc.PCC_CRSS
	strb	r0, [r4, #58]	@ <variable>.frmPcc.PCC_CRSS,
	ldrb	r9, [r5, #35]	@ zero_extendqisi2	@ <variable>.frmPcc.PCC_CRSS, <variable>.frmPcc.PCC_CRSS
	strb	r9, [r4, #59]	@ <variable>.frmPcc.PCC_CRSS,
	ldr	r0, [r5, #44]	@, <variable>.frmPcc.PCC_BWD_TKR
	str	r0, [fp, #-172]	@, %sfp
	b	.L67	@
.L141:
	mov	r3, r2	@ tmp2867, tmp2390
	strb	r2, [r4, #88]	@ tmp2390, <variable>.phaseCnt
	strb	r2, [r4, #89]	@ tmp2390, <variable>.phaseCnt
	mov	ip, r2	@ tmp2868, tmp2867
	strb	r2, [r4, #90]	@ tmp2390,
	mov	r0, r2	@ tmp2869, tmp2867
	strb	r2, [r4, #91]	@ tmp2390,
	mov	r1, r2	@ tmp2870, tmp2867
	strb	r2, [r4, #92]	@ tmp2390,
	strb	r2, [r4, #93]	@ tmp2390,
	b	.L124	@
.L71:
	ldr	ip, [fp, #-212]	@, %sfp
	movw	r0, #5499	@ tmp1795,
	ldr	r5, [fp, #-208]	@, %sfp
	cmp	r5, r0	@, tmp1795
	cmple	ip, r0	@,, tmp1795
	bgt	.L87	@,
	cmp	r3, #39	@ prephitmp.860,
	ble	.L88	@,
	cmp	r3, r2, asl #1	@ prephitmp.860, prephitmp.859,
	bge	.L87	@,
.L88:
	ldr	r9, [fp, #-208]	@, %sfp
	movw	r3, #2500	@ tmp1810,
	ldr	r5, [fp, #-152]	@, %sfp
	ldr	ip, [fp, #-176]	@, %sfp
	add	r0, r9, r9, asl #2	@, tmp1814,,,
	mov	r2, r5, asl #2	@ tmp1815,,
	cmp	ip, r3	@, tmp1810
	cmpgt	r0, r2	@, tmp1814, tmp1815
	movle	r0, #0	@, tmp1820
	movgt	r0, #1	@, tmp1820
	bgt	.L129	@,
	ldr	r9, [fp, #-212]	@, %sfp
	ldr	r5, [fp, #-164]	@, %sfp
	add	ip, r9, r9, asl #2	@,,,,
	str	ip, [fp, #-200]	@, %sfp
	ldr	r9, [fp, #-196]	@, %sfp
	mov	ip, r5, asl #2	@ tmp1832,,
	ldr	r5, [fp, #-200]	@, %sfp
	cmp	r9, r3	@, tmp1810
	cmpgt	r5, ip	@,, tmp1832
	movle	r3, #0	@, tmp1837
	movgt	r3, #1	@, tmp1837
	ble	.L90	@,
	add	r1, r7, r4	@ tmp1839, phase, pCntxt22
	mov	r3, #1	@,
	str	r3, [fp, #-168]	@, %sfp
	strb	r0, [r1, #88]	@ tmp1820, <variable>.phaseCnt
	b	.L70	@
.L137:
	add	r1, r1, #20	@, pstFmdStatInfo,
	mov	r2, #100	@,
	sub	r0, fp, #144	@,,
	rsbs	r7, r7, #1	@ phase, Is2ndFld
	movcc	r7, #0	@ phase
	bl	memcpy	@
	ldr	sl, [r5, #8]	@, <variable>.frmUm.nonmatch_UM
	ldr	r3, [r5, #0]	@ Frame_IT_diff, <variable>.frmITDiff
	cmp	r7, #1	@ phase,
	ldr	r1, [fp, #-140]	@ pcc_stat$PCC_FWD, pcc_stat.PCC_FWD
	str	sl, [fp, #-180]	@, %sfp
	ldr	r0, [r5, #124]	@, <variable>.frmHstBin.HISTOGRAM_BIN_2
	ldr	sl, [r5, #4]	@ um_stat$match_UM, <variable>.frmUm.match_UM
	ldr	r9, [fp, #-120]	@ pcc_stat$PCC_BWD_TKR, pcc_stat.PCC_BWD_TKR
	str	r0, [fp, #-188]	@, %sfp
	ldr	r0, [r5, #132]	@, <variable>.frmHstBin.HISTOGRAM_BIN_4
	ldr	r8, [fp, #-136]	@ pcc_stat$PCC_BWD.857, pcc_stat.PCC_BWD
	ldr	r2, [fp, #-132]	@ pcc_stat$PCC_CRSS, pcc_stat.PCC_CRSS
	str	r0, [fp, #-184]	@, %sfp
	ldr	r0, [r5, #128]	@, <variable>.frmHstBin.HISTOGRAM_BIN_3
	ldr	ip, [fp, #-124]	@ pcc_stat$PCC_FWD_TKR, pcc_stat.PCC_FWD_TKR
	str	r0, [fp, #-192]	@, %sfp
	ldr	r5, [r5, #120]	@, <variable>.frmHstBin.HISTOGRAM_BIN_1
	str	r5, [fp, #-152]	@, %sfp
	beq	.L142	@,
	mov	r0, r8	@ pcc_stat$PCC_BWD, pcc_stat$PCC_BWD.857
	ubfx	lr, r2, #8, #8	@ tmp250, pcc_stat$PCC_CRSS,,
	ubfx	r5, r2, #16, #8	@ tmp259, pcc_stat$PCC_CRSS,,
	strb	lr, [r4, #41]	@ tmp250,
	strb	r5, [r4, #42]	@ tmp259,
	mov	lr, r2, lsr #24	@ tmp267, pcc_stat$PCC_CRSS,
	ubfx	r5, r8, #8, #8	@ tmp284, pcc_stat$PCC_BWD.857,,
	strb	lr, [r4, #43]	@ tmp267,
	strb	r5, [r4, #45]	@ tmp284,
	ubfx	lr, r8, #16, #8	@ tmp293, pcc_stat$PCC_BWD.857,,
	mov	r5, r8, lsr #24	@ tmp301, pcc_stat$PCC_BWD.857,
	strb	r2, [r4, #40]	@ pcc_stat$PCC_CRSS,
	strb	r8, [r4, #44]	@ pcc_stat$PCC_BWD.857,
	strb	lr, [r4, #46]	@ tmp293,
	strb	r5, [r4, #47]	@ tmp301,
.L26:
	cmp	r2, r0	@ pcc_stat$PCC_CRSS, pcc_stat$PCC_BWD
	movlt	lr, r2	@ tmp309, pcc_stat$PCC_CRSS
	movge	lr, r0	@ tmp309, pcc_stat$PCC_BWD
	cmp	r1, #80	@ pcc_stat$PCC_FWD,
	cmple	r0, #80	@, pcc_stat$PCC_BWD,
	mov	r5, lr, asl #1	@, tmp309,
	str	r5, [fp, #-160]	@, %sfp
	ble	.L27	@,
	add	sl, r1, r1, asl #1	@, tmp319, pcc_stat$PCC_FWD, pcc_stat$PCC_FWD,
	mov	r5, r0, asl #1	@ tmp2861, pcc_stat$PCC_BWD,
	cmp	sl, r5	@ tmp319, tmp2861
	ble	.L28	@,
.L43:
	add	r1, r7, r4	@ tmp460, phase, pCntxt22
	mov	r2, #1	@ anomalFlg,
	mov	sl, #0	@ tmp462,
	strb	sl, [r1, #88]	@ tmp462, <variable>.phaseCnt
.L29:
	mov	ip, ip, asl #5	@ tmp627, pcc_stat$PCC_FWD_TKR,
	cmp	ip, #127	@ tmp627,
	addgt	r7, r7, r4	@ tmp629, phase, pCntxt22
	ldrgtb	r1, [r7, #88]	@ zero_extendqisi2	@ tmp635, <variable>.phaseCnt
	subgt	r1, r1, #5	@ tmp636, tmp635,
	strgtb	r1, [r7, #88]	@ tmp636, <variable>.phaseCnt
	cmp	r2, #1	@ anomalFlg,
	beq	.L143	@,
	mov	lr, #0	@ tmp2834,
	strb	lr, [r4, #36]	@ tmp2834,
	mov	r2, lr	@ iftmp.463, tmp2834
	strb	lr, [r4, #37]	@ tmp2834,
	strb	lr, [r4, #38]	@ tmp2834,
	strb	lr, [r4, #39]	@ tmp2834,
.L56:
	ldrsb	r0, [r4, #88]	@ <variable>.phaseCnt, <variable>.phaseCnt
	mov	r1, r2, lsr #24	@ tmp708, iftmp.463,
	ldrsb	r9, [r4, #89]	@ <variable>.phaseCnt, <variable>.phaseCnt
	ubfx	lr, r2, #8, #8	@ tmp691, iftmp.463,,
	cmp	r0, #32	@ <variable>.phaseCnt,
	movge	r0, #32	@ iftmp.464,
	ubfx	r7, r2, #16, #8	@ tmp700, iftmp.463,,
	bic	r8, r0, r0, asr #31	@ tmp721, iftmp.464
	cmp	r9, #32	@ <variable>.phaseCnt,
	movge	r9, #32	@ iftmp.713,
	bic	r5, r9, r9, asr #31	@ tmp728, iftmp.713
	strb	r2, [r4, #36]	@ iftmp.463,
	uxtb	sl, r8	@ iftmp.858, tmp721
	strb	lr, [r4, #37]	@ tmp691,
	uxtb	r0, r5	@ iftmp.465, tmp728
	strb	r1, [r4, #39]	@ tmp708,
	sxtb	ip, sl	@ iftmp.858, iftmp.858
	strb	sl, [r4, #88]	@ iftmp.858, <variable>.phaseCnt
	cmp	ip, #24	@ iftmp.858,
	strb	r0, [r4, #89]	@ iftmp.465, <variable>.phaseCnt
	strb	r7, [r4, #38]	@ tmp700,
	mov	r2, #0	@ tmp685,
	ble	.L57	@,
	sxtb	r0, r0	@ iftmp.465, iftmp.465
	cmp	r0, #24	@ iftmp.465,
	ble	.L58	@,
	mov	ip, #1	@ tmp736,
	strb	r2, [r4, #93]	@ tmp685,
	strb	ip, [r4, #90]	@ tmp736,
	strb	r2, [r4, #91]	@ tmp685,
	strb	r2, [r4, #92]	@ tmp685,
.L59:
	ldrb	ip, [r4, #13]	@ zero_extendqisi2	@ tmp769,
	ubfx	r1, r3, #8, #8	@, Frame_IT_diff,,
	ldrb	r2, [r4, #12]	@ zero_extendqisi2	@ tmp768,
	movw	r8, #:lower16:-2999	@,
	ldrb	r9, [r4, #14]	@ zero_extendqisi2	@ tmp772,
	movt	r8, #:upper16:-2999	@,
	orr	sl, r2, ip, asl #8	@, tmp771, tmp768, tmp769,
	str	r1, [fp, #-156]	@, %sfp
	ldrb	r5, [r4, #9]	@ zero_extendqisi2	@ tmp813,
	movw	r0, #:lower16:1717986919	@ tmp983,
	ldrb	r7, [r4, #15]	@ zero_extendqisi2	@ tmp775,
	orr	r1, sl, r9, asl #16	@, tmp774, tmp771, tmp772,
	ldrb	lr, [r4, #8]	@ zero_extendqisi2	@ tmp812,
	movt	r0, #:upper16:1717986919	@ tmp983,
	ldrb	ip, [r4, #10]	@ zero_extendqisi2	@ tmp816,
	str	r8, [fp, #-160]	@, %sfp
	orr	r1, r1, r7, asl #24	@, tmp777, tmp774, tmp775,
	ldrb	r9, [r4, #1]	@ zero_extendqisi2	@,
	orr	r2, lr, r5, asl #8	@, tmp815, tmp812, tmp813,
	ldrb	sl, [r4, #5]	@ zero_extendqisi2	@ tmp857,
	orr	r2, r2, ip, asl #16	@, tmp818, tmp815, tmp816,
	ldrb	r8, [r4, #4]	@ zero_extendqisi2	@ tmp856,
	add	ip, r1, r3	@ tmp978, tmp777, Frame_IT_diff
	ldrb	r5, [r4, #11]	@ zero_extendqisi2	@ tmp819,
	ldrb	r7, [r4, #6]	@ zero_extendqisi2	@ tmp860,
	str	r9, [fp, #-168]	@, %sfp
	orr	r9, r8, sl, asl #8	@, tmp859, tmp856, tmp857,
	ldrb	lr, [r4, #7]	@ zero_extendqisi2	@,
	orr	r2, r2, r5, asl #24	@, tmp821, tmp818, tmp819,
	ldr	sl, [fp, #-168]	@, %sfp
	orr	r8, r9, r7, asl #16	@, tmp862, tmp859, tmp860,
	add	ip, ip, r2	@ tmp979, tmp978, tmp821
	str	lr, [fp, #-164]	@, %sfp
	ldrb	lr, [r4, #0]	@ zero_extendqisi2	@ tmp900,* pCntxt22
	ldrb	r7, [r4, #2]	@ zero_extendqisi2	@ tmp904,
	orr	r5, lr, sl, asl #8	@, tmp903, tmp900,,
	ldr	sl, [fp, #-164]	@, %sfp
	ldrb	r9, [r4, #3]	@ zero_extendqisi2	@ tmp907,
	orr	lr, r5, r7, asl #16	@, tmp906, tmp903, tmp904,
	strb	r1, [r4, #16]	@ tmp777,
	orr	r8, r8, sl, asl #24	@, tmp865, tmp862,,
	ubfx	r5, r1, #8, #8	@ tmp787, tmp777,,
	orr	sl, lr, r9, asl #24	@, tmp909, tmp906, tmp907,
	add	ip, ip, r8	@ tmp980, tmp979, tmp865
	add	lr, ip, sl	@ tmp981, tmp980, tmp909
	strb	r2, [r4, #12]	@ tmp821,
	mov	r9, sl, lsr #24	@ tmp936, tmp909,
	strb	r8, [r4, #8]	@ tmp865,
	smull	r7, r0, r0, lr	@, tmp982, tmp983, tmp981
	ubfx	r7, r1, #16, #8	@ tmp796, tmp777,,
	strb	sl, [r4, #4]	@ tmp909,
	strb	r5, [r4, #17]	@ tmp787,
	mov	r5, r1, lsr #24	@ tmp804, tmp777,
	strb	r7, [r4, #18]	@ tmp796,
	ubfx	r1, r2, #16, #8	@ tmp840, tmp821,,
	ubfx	r7, r2, #8, #8	@ tmp831, tmp821,,
	strb	r5, [r4, #19]	@ tmp804,
	strb	r7, [r4, #13]	@ tmp831,
	ubfx	r5, r8, #8, #8	@ tmp875, tmp865,,
	ubfx	r7, r8, #16, #8	@ tmp884, tmp865,,
	mov	r2, r2, lsr #24	@ tmp848, tmp821,
	strb	r1, [r4, #14]	@ tmp840,
	mov	r1, r8, lsr #24	@ tmp892, tmp865,
	strb	r2, [r4, #15]	@ tmp848,
	ubfx	r8, sl, #16, #8	@ tmp928, tmp909,,
	ubfx	r2, sl, #8, #8	@ tmp919, tmp909,,
	strb	r5, [r4, #9]	@ tmp875,
	strb	r7, [r4, #10]	@ tmp884,
	mov	r5, lr, asr #31	@ tmp985, tmp981,
	strb	r1, [r4, #11]	@ tmp892,
	rsb	r0, r5, r0, asr #1	@, D.37777, tmp985, tmp982,
	strb	r2, [r4, #5]	@ tmp919,
	strb	r8, [r4, #6]	@ tmp928,
	mov	sl, r0, lsr #8	@, D.37777,
	strb	r9, [r4, #7]	@ tmp936,
	mov	lr, r0, lsr #16	@, D.37777,
	strb	r3, [r4, #0]	@ Frame_IT_diff,* pCntxt22
	mov	r7, r0, lsr #24	@, D.37777,
	ldr	ip, [fp, #-156]	@, %sfp
	ubfx	r9, r3, #16, #8	@ tmp962, Frame_IT_diff,,
	ldrb	r8, [r4, #29]	@ zero_extendqisi2	@ tmp1021,
	mov	r3, r3, lsr #24	@ tmp970, Frame_IT_diff,
	ldrb	r5, [r4, #21]	@ zero_extendqisi2	@ tmp1031,
	strb	ip, [r4, #1]	@,
	and	ip, r0, #255	@ tmp2854, D.37777,
	str	sl, [fp, #-168]	@, %sfp
	ldrb	r1, [r4, #28]	@ zero_extendqisi2	@ tmp1020,
	str	lr, [fp, #-156]	@, %sfp
	ldrb	sl, [r4, #30]	@ zero_extendqisi2	@ tmp1024,
	orr	lr, r1, r8, asl #8	@, tmp1023, tmp1020, tmp1021,
	str	r7, [fp, #-180]	@, %sfp
	ldrb	r1, [r4, #31]	@ zero_extendqisi2	@ tmp1027,
	strb	r3, [r4, #3]	@ tmp970,
	orr	r8, lr, sl, asl #16	@, tmp1026, tmp1023, tmp1024,
	strb	r9, [r4, #2]	@ tmp962,
	strb	ip, [r4, #24]	@ tmp2854,
	orr	r9, r8, r1, asl #24	@, tmp1029, tmp1026, tmp1027,
	ldr	r1, [fp, #-168]	@, %sfp
	ldrb	r2, [r4, #20]	@ zero_extendqisi2	@ tmp1030,
	ldrb	r7, [r4, #22]	@ zero_extendqisi2	@ tmp1034,
	orr	r5, r2, r5, asl #8	@, tmp1033, tmp1030, tmp1031,
	strb	r1, [r4, #25]	@,
	ldrb	r2, [r4, #23]	@ zero_extendqisi2	@ tmp1037,
	orr	sl, r5, r7, asl #16	@, tmp1036, tmp1033, tmp1034,
	ldr	r5, [fp, #-156]	@, %sfp
	orr	lr, sl, r2, asl #24	@, tmp1039, tmp1036, tmp1037,
	strb	r5, [r4, #26]	@,
	rsb	r8, lr, r9	@ tmp1040, tmp1039, tmp1029
	ldr	sl, [fp, #-160]	@, %sfp
	add	r8, r8, r0	@ D.37772, tmp1040, D.37777
	ldr	r7, [fp, #-180]	@, %sfp
	cmp	r8, sl	@ D.37772,
	strb	r7, [r4, #27]	@,
	movwlt	r3, #:lower16:-3000	@ iftmp.466,
	movtlt	r3, #:upper16:-3000	@ iftmp.466,
	blt	.L62	@,
	movw	r3, #3000	@ tmp1042,
	cmp	r8, r3	@ D.37772, tmp1042
	movlt	r3, r8	@ iftmp.466, D.37772
	movge	r3, r3	@ iftmp.466, tmp1042
.L62:
	ldrb	r8, [r4, #91]	@ zero_extendqisi2	@ tmp2856,
	ubfx	r7, r3, #8, #8	@ tmp1052, iftmp.466,,
	ldrb	r1, [r4, #90]	@ zero_extendqisi2	@ tmp2855,
	ubfx	sl, r3, #16, #8	@ tmp1061, iftmp.466,,
	ldrb	r0, [r4, #92]	@ zero_extendqisi2	@ tmp2857,
	mov	lr, r3, lsr #24	@ tmp1069, iftmp.466,
	strb	r7, [r4, #29]	@ tmp1052,
	orr	r9, r1, r8, asl #8	@, tmp1114, tmp2855, tmp2856,
	strb	sl, [r4, #30]	@ tmp1061,
	mov	r7, #0	@ tmp1046,
	strb	lr, [r4, #31]	@ tmp1069,
	orr	r5, r9, r0, asl #16	@, tmp1117, tmp1114, tmp2857,
	strb	ip, [r4, #20]	@ tmp2854,
	ldr	r9, [fp, #-168]	@, %sfp
	ldrb	r2, [r4, #93]	@ zero_extendqisi2	@ tmp2858,
	strb	r9, [r4, #21]	@,
	ldr	sl, [fp, #-156]	@, %sfp
	orrs	r5, r5, r2, asl #24	@, tmp1120, tmp1117, tmp2858,
	strb	sl, [r4, #22]	@,
	ldr	lr, [fp, #-180]	@, %sfp
	strb	r3, [r4, #28]	@ iftmp.466,
	strb	lr, [r4, #23]	@,
	bne	.L63	@,
	strb	r5, [r4, #31]	@ tmp1120,
	strb	r5, [r4, #28]	@ tmp1120,
	strb	r5, [r4, #29]	@ tmp1120,
	strb	r5, [r4, #30]	@ tmp1120,
.L64:
	ldr	r7, [fp, #-184]	@, %sfp
	orr	r3, r1, r8, asl #8	@, tmp1201, tmp2855, tmp2856,
	ldr	r5, [fp, #-192]	@, %sfp
	orr	r8, r3, r0, asl #16	@, tmp1204, tmp1201, tmp2857,
	ldr	r9, [fp, #-188]	@, %sfp
	orr	r8, r8, r2, asl #24	@, lstLock, tmp1204, tmp2858,
	add	ip, r5, r7, asl #1	@, tmp1159,,,
	ldr	sl, [fp, #-152]	@, %sfp
	add	r0, r9, ip, asl #1	@, tmp1161,, tmp1159,
	add	r3, sl, r0, asl #1	@, tmp1163,, tmp1161,
	b	.L132	@
.L57:
	cmp	ip, #19	@ iftmp.858,
	ble	.L60	@,
	sxtb	r0, r0	@ iftmp.465, iftmp.465
.L58:
	cmp	r0, #19	@ iftmp.465,
	bgt	.L59	@,
.L60:
	mov	r2, #0	@ tmp754,
	strb	r2, [r4, #93]	@ tmp754,
	strb	r2, [r4, #90]	@ tmp754,
	strb	r2, [r4, #91]	@ tmp754,
	strb	r2, [r4, #92]	@ tmp754,
	b	.L59	@
.L63:
	cmp	r3, #1000	@ iftmp.466,
	blt	.L64	@,
	mov	r1, r7	@ tmp2855, tmp1046
	strb	r7, [r4, #88]	@ tmp1046, <variable>.phaseCnt
	mov	r8, r7	@ tmp2856, tmp2855
	mov	r0, r7	@ tmp2857, tmp2855
	mov	r2, r7	@ tmp2858, tmp2855
	strb	r7, [r4, #89]	@ tmp1046, <variable>.phaseCnt
	strb	r7, [r4, #90]	@ tmp1046,
	strb	r7, [r4, #91]	@ tmp1046,
	strb	r7, [r4, #92]	@ tmp1046,
	strb	r7, [r4, #93]	@ tmp1046,
	b	.L64	@
.L27:
	movw	lr, #5499	@ tmp457,
	cmp	sl, lr	@ um_stat$match_UM, tmp457
	bgt	.L43	@,
	ldr	r5, [fp, #-180]	@ nonmatch_UM.677, %sfp
	cmp	r5, #0	@ tmp8,
	moveq	r5, #20	@ nonmatch_UM.677,
	cmp	sl, r5	@ um_stat$match_UM, nonmatch_UM.677
	bgt	.L43	@,
	cmp	r1, #39	@ pcc_stat$PCC_FWD,
	ble	.L46	@,
	cmp	r1, r0, asl #1	@ pcc_stat$PCC_FWD, pcc_stat$PCC_BWD,
	bge	.L43	@,
.L46:
	cmp	r2, #80	@ pcc_stat$PCC_CRSS,
	ble	.L47	@,
	rsb	r2, r2, r0	@ tmp464, pcc_stat$PCC_CRSS, pcc_stat$PCC_BWD
	ldr	r9, [fp, #-160]	@, %sfp
	cmp	r2, #0	@ tmp464,
	add	r1, r9, #50	@ tmp466,,
	rsblt	r2, r2, #0	@ tmp465, tmp464
	cmp	r2, r1	@ tmp465, tmp466
	ble	.L47	@,
	ldrb	r2, [r4, #33]	@ zero_extendqisi2	@ tmp468,
	ldrb	r1, [r4, #32]	@ zero_extendqisi2	@ tmp467,
	ldrb	r0, [r4, #34]	@ zero_extendqisi2	@ tmp471,
	ldrb	r5, [r4, #35]	@ zero_extendqisi2	@ tmp474,
	orr	r8, r1, r2, asl #8	@, tmp470, tmp467, tmp468,
	orr	lr, r8, r0, asl #16	@, tmp473, tmp470, tmp471,
	orr	r2, lr, r5, asl #24	@, tmp476, tmp473, tmp474,
	cmp	r2, #10	@ tmp476,
	ble	.L47	@,
	ldrb	r5, [r4, #91]	@ zero_extendqisi2	@ tmp478,
	ldrb	r8, [r4, #90]	@ zero_extendqisi2	@ tmp477,
	ldrb	lr, [r4, #92]	@ zero_extendqisi2	@ tmp481,
	ldrb	sl, [r4, #93]	@ zero_extendqisi2	@ tmp484,
	orr	r9, r8, r5, asl #8	@, tmp480, tmp477, tmp478,
	orr	r1, r9, lr, asl #16	@, tmp483, tmp480, tmp481,
	orr	r1, r1, sl, asl #24	@, tmp486, tmp483, tmp484,
	cmp	r1, #1	@ tmp486,
	beq	.L52	@,
	movw	r1, #5000	@ tmp510,
	cmp	r2, r1	@ tmp476, tmp510
	ble	.L41	@,
	ldrb	r9, [r4, #37]	@ zero_extendqisi2	@ tmp518,
	add	r0, r7, r4	@ tmp512, phase, pCntxt22
	ldrb	lr, [r4, #36]	@ zero_extendqisi2	@ tmp517,
	mov	r2, #1	@ anomalFlg,
	ldrb	r8, [r4, #38]	@ zero_extendqisi2	@ tmp521,
	ldrb	sl, [r4, #39]	@ zero_extendqisi2	@ tmp524,
	orr	r1, lr, r9, asl #8	@, tmp520, tmp517, tmp518,
	ldrb	r9, [r0, #88]	@ zero_extendqisi2	@ tmp530, <variable>.phaseCnt
	orr	r5, r1, r8, asl #16	@, tmp523, tmp520, tmp521,
	orr	lr, r5, sl, asl #24	@, tmp526, tmp523, tmp524,
	mvn	r1, lr	@ tmp528, tmp526
	add	r1, r9, r1	@ tmp532, tmp530, tmp528
	strb	r1, [r0, #88]	@ tmp532, <variable>.phaseCnt
	b	.L29	@
.L72:
	add	r1, r3, r1	@ tmp1778, tmp2849, min_crss_nonmatch
	cmp	r5, r1	@ tmp2848, tmp1778
	ble	.L86	@,
	add	ip, r7, r4	@ tmp1780, phase, pCntxt22
	mov	r0, #1	@,
	mov	r3, #0	@ tmp1782,
	str	r0, [fp, #-168]	@, %sfp
	strb	r3, [ip, #88]	@ tmp1782, <variable>.phaseCnt
	b	.L70	@
.L139:
	ldr	r5, [fp, #-184]	@, %sfp
	cmp	r5, #1	@,
	bgt	.L69	@,
	mov	r1, #0	@ tmp1594,
	mov	r8, #1	@ tmp1596,
	strb	r1, [r4, #93]	@ tmp1594,
	strb	r8, [r4, #90]	@ tmp1596,
	strb	r1, [r4, #91]	@ tmp1594,
	strb	r1, [r4, #92]	@ tmp1594,
	b	.L65	@
.L28:
	add	sl, r0, r0, asl #2	@, tmp328, pcc_stat$PCC_BWD, pcc_stat$PCC_BWD,
	add	lr, sl, sl, lsr #31	@, tmp331, tmp328, tmp328,
	cmp	r2, lr, asr #1	@ pcc_stat$PCC_CRSS, tmp331,
	bgt	.L30	@,
	cmp	r2, #1000	@ pcc_stat$PCC_CRSS,
	ble	.L31	@,
	add	r9, r2, r2, asl #2	@, tmp335, pcc_stat$PCC_CRSS, pcc_stat$PCC_CRSS,
	rsb	lr, r0, r0, asl #3	@, tmp338, pcc_stat$PCC_BWD, pcc_stat$PCC_BWD,
	cmp	r9, lr	@ tmp335, tmp338
	bge	.L30	@,
.L31:
	cmp	r1, #99	@ pcc_stat$PCC_FWD,
	ble	.L32	@,
	cmp	r1, #500	@ pcc_stat$PCC_FWD,
	add	r2, r7, r4	@ tmp2860, phase, pCntxt22
	movlt	r8, r1, asr #31	@ tmp357, pcc_stat$PCC_FWD,
	movwlt	r5, #:lower16:1374389535	@ tmp355,
	movtlt	r5, #:upper16:1374389535	@ tmp355,
	ldrb	r0, [r2, #88]	@ zero_extendqisi2	@ temp.663, <variable>.phaseCnt
	movge	r1, #5	@ iftmp.459,
	smulllt	r9, r1, r5, r1	@, tmp354, tmp355, pcc_stat$PCC_FWD
	rsblt	r1, r8, r1, asr #5	@, tmp353, tmp357, tmp354,
	uxtblt	r1, r1	@ iftmp.459, tmp353
	rsb	r1, r1, r0	@ tmp362, iftmp.459, temp.663
	strb	r1, [r2, #88]	@ tmp362, <variable>.phaseCnt
	mov	r2, #1	@ anomalFlg,
	b	.L29	@
.L87:
	add	r3, r7, r4	@ tmp1805, phase, pCntxt22
	mov	r2, #1	@,
	mov	r9, #0	@ tmp1807,
	str	r2, [fp, #-168]	@, %sfp
	strb	r9, [r3, #88]	@ tmp1807, <variable>.phaseCnt
	b	.L70	@
.L86:
	add	r9, r7, r4	@ tmp1785, phase, pCntxt22
	mov	r1, #1	@,
	str	r1, [fp, #-168]	@, %sfp
	ldrb	r2, [r9, #88]	@ zero_extendqisi2	@ tmp1791, <variable>.phaseCnt
	sub	r5, r2, #5	@ tmp1792, tmp1791,
	strb	r5, [r9, #88]	@ tmp1792, <variable>.phaseCnt
	b	.L70	@
.L73:
	cmp	r0, #119	@ max_crss_nonmatch,
	ble	.L83	@,
	add	r5, r3, r1	@ tmp1738, tmp2849, min_crss_nonmatch
	cmp	r0, r5	@ max_crss_nonmatch, tmp1738
	ble	.L84	@,
	add	r9, r7, r4	@ tmp1740, phase, pCntxt22
	mov	r1, #1	@,
	mov	r2, #0	@ tmp1742,
	str	r1, [fp, #-168]	@, %sfp
	strb	r2, [r9, #88]	@ tmp1742, <variable>.phaseCnt
	b	.L70	@
.L77:
	mov	r0, #1	@,
	str	r0, [fp, #-168]	@, %sfp
	b	.L70	@
.L143:
	ldrb	ip, [r4, #37]	@ zero_extendqisi2	@ tmp639,
	ldrb	lr, [r4, #36]	@ zero_extendqisi2	@ tmp638,
	ldrb	r0, [r4, #38]	@ zero_extendqisi2	@ tmp642,
	ldrb	r8, [r4, #39]	@ zero_extendqisi2	@ tmp645,
	orr	r9, lr, ip, asl #8	@, tmp641, tmp638, tmp639,
	orr	r5, r9, r0, asl #16	@, tmp644, tmp641, tmp642,
	orr	r2, r5, r8, asl #24	@, tmp647, tmp644, tmp645,
	add	r2, r2, #1	@ iftmp.462, tmp647,
	strb	r2, [r4, #36]	@ iftmp.462,
	cmp	r2, #0	@ iftmp.462,
	ubfx	r1, r2, #8, #8	@ tmp657, iftmp.462,,
	ubfx	sl, r2, #16, #8	@ tmp666, iftmp.462,,
	mov	r7, r2, lsr #24	@ tmp674, iftmp.462,
	strb	r1, [r4, #37]	@ tmp657,
	movle	r2, #0	@ iftmp.463,
	strb	sl, [r4, #38]	@ tmp666,
	strb	r7, [r4, #39]	@ tmp674,
	ble	.L56	@,
	cmp	r2, #50	@ iftmp.462,
	movge	r2, #50	@ iftmp.463,
	b	.L56	@
.L129:
	add	r1, r7, r4	@ tmp1822, phase, pCntxt22
	mov	r2, #1	@,
	mov	r3, #0	@ tmp1824,
	str	r2, [fp, #-168]	@, %sfp
	strb	r3, [r1, #88]	@ tmp1824, <variable>.phaseCnt
	b	.L70	@
.L74:
	cmp	r0, r3	@ max_crss_nonmatch, tmp2849
	bgt	.L129	@,
	mov	r2, r0, asl #1	@ tmp1697, max_crss_nonmatch,
	add	r0, r2, r0	@ tmp1698, tmp1697, max_crss_nonmatch
	cmp	r0, r1, asl #2	@ tmp1698, min_crss_nonmatch,
	bge	.L81	@,
	add	r2, r5, r9	@ tmp1701, tmp2848, match_weave
	cmp	r3, r2	@ tmp2849, tmp1701
	ble	.L77	@,
	add	r9, r7, r4	@ tmp1703, phase, pCntxt22
	mov	r5, #0	@,
	str	r5, [fp, #-168]	@, %sfp
	ldrb	ip, [r9, #88]	@ zero_extendqisi2	@ tmp1709, <variable>.phaseCnt
	add	r3, ip, #1	@ tmp1710, tmp1709,
	strb	r3, [r9, #88]	@ tmp1710, <variable>.phaseCnt
	b	.L70	@
.L30:
	add	r1, r7, r4	@ tmp340, phase, pCntxt22
	mov	r2, #1	@ anomalFlg,
	ldrb	r9, [r1, #88]	@ zero_extendqisi2	@ tmp346, <variable>.phaseCnt
	sub	r8, r9, #1	@ tmp347, tmp346,
	strb	r8, [r1, #88]	@ tmp347, <variable>.phaseCnt
	b	.L29	@
.L83:
	add	r5, r7, r4	@ tmp1772, phase, pCntxt22
	mov	r2, #1	@,
	mov	r9, #0	@ tmp1774,
	str	r2, [fp, #-168]	@, %sfp
	strb	r9, [r5, #88]	@ tmp1774, <variable>.phaseCnt
	b	.L70	@
.L142:
	ldrb	r1, [r4, #45]	@ zero_extendqisi2	@,
	mov	ip, r9	@ pcc_stat$PCC_FWD_TKR, pcc_stat$PCC_BWD_TKR
	ldrb	lr, [r4, #41]	@ zero_extendqisi2	@ tmp222,
	str	r1, [fp, #-172]	@, %sfp
	mov	r1, r8	@ pcc_stat$PCC_FWD, pcc_stat$PCC_BWD.857
	ldrb	r0, [r4, #42]	@ zero_extendqisi2	@,
	ldrb	r2, [r4, #40]	@ zero_extendqisi2	@ tmp221,
	str	r0, [fp, #-160]	@, %sfp
	orr	r9, r2, lr, asl #8	@,, tmp221, tmp222,
	ldrb	r0, [r4, #44]	@ zero_extendqisi2	@,
	str	r9, [fp, #-164]	@, %sfp
	ldrb	r5, [r4, #46]	@ zero_extendqisi2	@,
	ldr	r9, [fp, #-172]	@, %sfp
	str	r5, [fp, #-176]	@, %sfp
	ldrb	lr, [r4, #43]	@ zero_extendqisi2	@,
	orr	r9, r0, r9, asl #8	@,,,,
	str	r9, [fp, #-172]	@, %sfp
	ldr	r5, [fp, #-160]	@, %sfp
	str	lr, [fp, #-168]	@, %sfp
	ldrb	r2, [r4, #47]	@ zero_extendqisi2	@,
	ldr	lr, [fp, #-164]	@, %sfp
	ldr	r0, [fp, #-176]	@, %sfp
	str	r2, [fp, #-156]	@, %sfp
	orr	r2, lr, r5, asl #16	@,,,,
	ldr	r5, [fp, #-168]	@, %sfp
	ldr	lr, [fp, #-156]	@, %sfp
	orr	r9, r9, r0, asl #16	@,,,,
	str	r9, [fp, #-164]	@, %sfp
	orr	r2, r2, r5, asl #24	@, pcc_stat$PCC_CRSS,,,
	orr	r0, r9, lr, asl #24	@, pcc_stat$PCC_BWD,,,
	b	.L26	@
.L84:
	rsb	r3, r2, ip	@ tmp1744, prephitmp.859, prephitmp.651
	cmp	r3, #0	@ tmp1744,
	rsblt	r3, r3, #0	@ diff_crss_nonmatch, tmp1744
	cmp	r3, #40	@ diff_crss_nonmatch,
	ble	.L85	@,
	cmp	r1, #1	@ min_crss_nonmatch,
	movlt	r1, #1	@,
	mov	r9, #1	@,
	bl	__aeabi_idiv	@
	add	ip, r7, r4	@ tmp1746, phase, pCntxt22
	str	r9, [fp, #-168]	@, %sfp
	ldrb	r5, [ip, #88]	@ zero_extendqisi2	@ tmp1757, <variable>.phaseCnt
	rsb	r3, r0, r5	@ tmp1759,, tmp1757
	strb	r3, [ip, #88]	@ tmp1759, <variable>.phaseCnt
	b	.L70	@
.L47:
	ldr	r0, [fp, #-180]	@, %sfp
	cmp	r0, #1000	@,
	ble	.L49	@,
	mov	sl, sl, asl #4	@ D.37803, um_stat$match_UM,
	mov	r2, r0, asl #1	@ D.37804,,
	cmp	r2, sl	@ D.37804, D.37803
	ble	.L50	@,
	movw	r2, #9000	@ tmp539,
	cmp	r0, r2	@, tmp539
	ble	.L41	@,
.L126:
	add	r0, r7, r4	@ tmp541, phase, pCntxt22
	mov	r2, #0	@ anomalFlg,
	ldrb	r5, [r0, #88]	@ zero_extendqisi2	@ tmp547, <variable>.phaseCnt
	add	r1, r5, #1	@ tmp548, tmp547,
	strb	r1, [r0, #88]	@ tmp548, <variable>.phaseCnt
	b	.L29	@
.L81:
	add	r9, r3, r1	@ tmp1714, tmp2849, min_crss_nonmatch
	cmp	r9, r2	@ tmp1714, tmp1697
	bgt	.L130	@,
	add	r2, r7, r4	@ tmp1727, phase, pCntxt22
	mov	ip, #1	@,
	str	ip, [fp, #-168]	@, %sfp
	ldrb	r3, [r2, #88]	@ zero_extendqisi2	@ tmp1733, <variable>.phaseCnt
	sub	r1, r3, #2	@ tmp1734, tmp1733,
	strb	r1, [r2, #88]	@ tmp1734, <variable>.phaseCnt
	b	.L70	@
.L90:
	ldr	r5, [fp, #-176]	@, %sfp
	movw	r0, #10000	@ tmp1843,
	cmp	r5, r0	@, tmp1843
	ble	.L91	@,
	ldr	r5, [fp, #-152]	@, %sfp
	ldr	r9, [fp, #-208]	@, %sfp
	mov	r2, r5, asl #1	@ tmp1844,,
	cmp	r2, r9, asl #4	@ tmp1844,,
	ble	.L92	@,
	ldr	r2, [fp, #-196]	@, %sfp
	cmp	r2, r0	@, tmp1843
	ble	.L93	@,
	ldr	r0, [fp, #-212]	@, %sfp
	mov	r9, r0, asl #4	@ tmp1848,,
	ldr	r0, [fp, #-164]	@, %sfp
	cmp	r9, r0, asl #1	@ tmp1848,,
	blt	.L128	@,
.L114:
	ldr	r5, [fp, #-160]	@, %sfp
	ldr	r9, [fp, #-168]	@, %sfp
	ldr	r3, [fp, #-156]	@, %sfp
	orr	r1, r1, r5, asl #8	@, tmp2219, tmp2862,,
	orr	r2, r1, r9, asl #16	@, tmp2222, tmp2219,,
	orr	r1, r2, r3, asl #24	@, tmp2225, tmp2222,,
	cmp	r1, #1	@ tmp2225,
	beq	.L127	@,
.L115:
	add	r2, r7, r4	@ tmp2251, phase, pCntxt22
	mov	ip, #1	@,
	str	ip, [fp, #-168]	@, %sfp
	ldrb	r5, [r2, #88]	@ zero_extendqisi2	@ tmp2257, <variable>.phaseCnt
	sub	r9, r5, #1	@ tmp2258, tmp2257,
	strb	r9, [r2, #88]	@ tmp2258, <variable>.phaseCnt
	b	.L70	@
.L32:
	mov	sl, r1, asl #3	@, pcc_stat$PCC_FWD,
	str	sl, [fp, #-172]	@, %sfp
	cmp	r0, sl	@ pcc_stat$PCC_BWD,
	blt	.L35	@,
	cmp	r1, #10	@ pcc_stat$PCC_FWD,
	movge	lr, r1	@, pcc_stat$PCC_FWD
	movlt	lr, #10	@,
	mov	r9, r2, asl #1	@, pcc_stat$PCC_CRSS,
	cmp	r9, lr, asl #3	@,,
	bge	.L36	@,
.L35:
	ldr	r9, [fp, #-160]	@ tmp369, %sfp
	rsb	sl, r2, r0	@ tmp367, pcc_stat$PCC_CRSS, pcc_stat$PCC_BWD
	cmp	r9, #150	@ tmp369,
	movlt	r9, #150	@ tmp369,
	cmp	sl, #0	@ tmp367,
	rsblt	sl, sl, #0	@, tmp367
	add	lr, r9, #50	@, tmp369,
	cmp	sl, lr	@,
	ble	.L36	@,
	ldrb	lr, [r4, #33]	@ zero_extendqisi2	@,
	str	lr, [fp, #-164]	@, %sfp
	ldrb	sl, [r4, #32]	@ zero_extendqisi2	@,
	str	sl, [fp, #-160]	@, %sfp
	ldrb	r9, [r4, #34]	@ zero_extendqisi2	@,
	ldr	sl, [fp, #-164]	@, %sfp
	str	r9, [fp, #-168]	@, %sfp
	ldrb	lr, [r4, #35]	@ zero_extendqisi2	@,
	ldr	r9, [fp, #-160]	@, %sfp
	str	lr, [fp, #-156]	@, %sfp
	orr	lr, r9, sl, asl #8	@,,,,
	ldr	sl, [fp, #-168]	@, %sfp
	orr	r9, lr, sl, asl #16	@,,,,
	ldr	sl, [fp, #-156]	@, %sfp
	str	r9, [fp, #-160]	@, %sfp
	orr	lr, r9, sl, asl #24	@,,,,
	str	lr, [fp, #-156]	@, %sfp
	cmp	lr, #10	@,
	ble	.L36	@,
	add	r5, r7, r4	@ tmp382, phase, pCntxt22
	mov	r2, #1	@ anomalFlg,
	ldrb	r1, [r5, #88]	@ zero_extendqisi2	@ tmp388, <variable>.phaseCnt
	sub	r1, r1, #5	@ tmp389, tmp388,
	strb	r1, [r5, #88]	@ tmp389, <variable>.phaseCnt
	b	.L29	@
.L36:
	ldr	r9, [fp, #-172]	@, %sfp
	cmp	r9, r5	@, tmp2861
	bge	.L37	@,
	cmp	r9, r2, asl #1	@, pcc_stat$PCC_CRSS,
	blt	.L38	@,
	ldrb	lr, [r4, #33]	@ zero_extendqisi2	@ tmp394,
	ldrb	r5, [r4, #32]	@ zero_extendqisi2	@ tmp393,
	ldrb	sl, [r4, #34]	@ zero_extendqisi2	@ tmp397,
	ldrb	r9, [r4, #35]	@ zero_extendqisi2	@ tmp400,
	orr	r2, r5, lr, asl #8	@, tmp396, tmp393, tmp394,
	orr	lr, r2, sl, asl #16	@, tmp399, tmp396, tmp397,
	orr	r2, lr, r9, asl #24	@, tmp402, tmp399, tmp400,
	cmp	r2, #9	@ tmp402,
	bgt	.L37	@,
.L38:
	ldr	r0, [fp, #-184]	@, %sfp
	add	r8, r0, #100	@ tmp404,,
	cmp	r8, r1, asl #2	@ tmp404, pcc_stat$PCC_FWD,
	bge	.L126	@,
	add	r9, r7, r4	@ tmp406, phase, pCntxt22
	mov	r2, #1	@ anomalFlg,
	ldrb	r1, [r9, #88]	@ zero_extendqisi2	@ tmp412, <variable>.phaseCnt
	sub	r1, r1, #15	@ tmp413, tmp412,
	strb	r1, [r9, #88]	@ tmp413, <variable>.phaseCnt
	b	.L29	@
.L49:
	add	r9, r7, r4	@ tmp618, phase, pCntxt22
	mov	r2, #1	@ anomalFlg,
	ldrb	lr, [r9, #88]	@ zero_extendqisi2	@ tmp624, <variable>.phaseCnt
	sub	r1, lr, #1	@ tmp625, tmp624,
	strb	r1, [r9, #88]	@ tmp625, <variable>.phaseCnt
	b	.L29	@
.L85:
	cmp	r3, #19	@ diff_crss_nonmatch,
	bgt	.L77	@,
	add	r2, r7, r4	@ tmp1762, phase, pCntxt22
	mov	r3, #0	@,
	str	r3, [fp, #-168]	@, %sfp
	ldrb	ip, [r2, #88]	@ zero_extendqisi2	@ tmp1768, <variable>.phaseCnt
	add	r1, ip, #1	@ tmp1769, tmp1768,
	strb	r1, [r2, #88]	@ tmp1769, <variable>.phaseCnt
	b	.L70	@
.L130:
	add	r2, r7, r4	@ tmp1977, phase, pCntxt22
	mov	r0, #1	@,
	str	r0, [fp, #-168]	@, %sfp
	ldrb	ip, [r2, #88]	@ zero_extendqisi2	@ tmp1983, <variable>.phaseCnt
	sub	r5, ip, #1	@ tmp1984, tmp1983,
	strb	r5, [r2, #88]	@ tmp1984, <variable>.phaseCnt
	b	.L70	@
.L37:
	add	r2, r0, #150	@ tmp425, pcc_stat$PCC_BWD,
	cmp	r1, r2	@ pcc_stat$PCC_FWD, tmp425
	bgt	.L40	@,
	add	sl, r8, #150	@ tmp426, pcc_stat$PCC_BWD.857,
	cmp	r1, sl	@ pcc_stat$PCC_FWD, tmp426
	ble	.L41	@,
.L40:
	ldrb	r1, [r4, #91]	@ zero_extendqisi2	@ tmp428,
	add	lr, r7, r4	@ tmp438, phase, pCntxt22
	ldrb	r2, [r4, #90]	@ zero_extendqisi2	@ tmp427,
	ldrb	r0, [r4, #92]	@ zero_extendqisi2	@ tmp431,
	ldrb	r5, [r4, #93]	@ zero_extendqisi2	@ tmp434,
	orr	r9, r2, r1, asl #8	@, tmp430, tmp427, tmp428,
	orr	r8, r9, r0, asl #16	@, tmp433, tmp430, tmp431,
	orr	r2, r8, r5, asl #24	@, tmp436, tmp433, tmp434,
	cmp	r2, #1	@ tmp436,
	ldreqb	r1, [lr, #88]	@ zero_extendqisi2	@ tmp444, <variable>.phaseCnt
	movne	r2, #1	@ anomalFlg,
	ldrneb	r1, [lr, #88]	@ zero_extendqisi2	@ tmp454, <variable>.phaseCnt
	subeq	r1, r1, #1	@ tmp445, tmp444,
	subne	r1, r1, #3	@ tmp455, tmp454,
	strb	r1, [lr, #88]	@ tmp455, <variable>.phaseCnt
	b	.L29	@
.L41:
	mov	r2, #1	@ anomalFlg,
	b	.L29	@
.L91:
	ldr	r5, [fp, #-176]	@, %sfp
	cmp	r5, #1000	@,
	ble	.L101	@,
	ldr	r9, [fp, #-208]	@, %sfp
	cmp	r2, r9, asl #4	@ tmp1815,,
	ble	.L102	@,
	ldr	r2, [fp, #-196]	@, %sfp
	cmp	r2, r0	@, tmp1843
	bgt	.L136	@,
	ldr	r5, [fp, #-196]	@, %sfp
	cmp	r5, #1000	@,
	ble	.L128	@,
	ldr	r0, [fp, #-212]	@, %sfp
	cmp	ip, r0, asl #4	@ tmp1832,,
	bgt	.L128	@,
	ldr	r9, [fp, #-212]	@, %sfp
	mov	r3, #3	@ tmp2069,
	ldr	ip, [fp, #-164]	@, %sfp
	mul	r0, r3, r9	@ tmp2068, tmp2069,
	cmp	r0, ip, asl #1	@ tmp2068,,
	blt	.L77	@,
	ldr	ip, [fp, #-160]	@, %sfp
	ldr	r0, [fp, #-168]	@, %sfp
	orr	r5, r1, ip, asl #8	@, tmp2073, tmp2862,,
	orr	r2, r5, r0, asl #16	@, tmp2076, tmp2073,,
	ldr	r0, [fp, #-156]	@, %sfp
	orr	r1, r2, r0, asl #24	@, tmp2079, tmp2076,,
	cmp	r1, #1	@ tmp2079,
	bne	.L115	@,
	ldrb	r3, [r4, #37]	@ zero_extendqisi2	@ tmp2087,
	mov	r0, #1	@,
	ldrb	r1, [r4, #36]	@ zero_extendqisi2	@ tmp2086,
	add	r9, r7, r4	@ tmp2081, phase, pCntxt22
	str	r0, [fp, #-168]	@, %sfp
	ldrb	r0, [r4, #38]	@ zero_extendqisi2	@ tmp2090,
	orr	r2, r1, r3, asl #8	@, tmp2089, tmp2086, tmp2087,
	ldrb	ip, [r4, #39]	@ zero_extendqisi2	@ tmp2093,
	ldrb	r1, [r9, #88]	@ zero_extendqisi2	@ tmp2100, <variable>.phaseCnt
	orr	r3, r2, r0, asl #16	@, tmp2092, tmp2089, tmp2090,
	orr	r5, r3, ip, asl #24	@, tmp2095, tmp2092, tmp2093,
	mvn	r2, r5	@ tmp2096, tmp2095
	add	r3, r1, r2, asl #1	@, tmp2102, tmp2100, tmp2096,
	strb	r3, [r9, #88]	@ tmp2102, <variable>.phaseCnt
	b	.L70	@
.L50:
	ldrb	r5, [r4, #91]	@ zero_extendqisi2	@ tmp551,
	ldrb	r0, [r4, #90]	@ zero_extendqisi2	@ tmp550,
	ldrb	lr, [r4, #92]	@ zero_extendqisi2	@ tmp554,
	ldrb	r8, [r4, #93]	@ zero_extendqisi2	@ tmp557,
	orr	r9, r0, r5, asl #8	@, tmp553, tmp550, tmp551,
	orr	r1, r9, lr, asl #16	@, tmp556, tmp553, tmp554,
	orr	r1, r1, r8, asl #24	@, tmp559, tmp556, tmp557,
	cmp	r1, #1	@ tmp559,
	bne	.L49	@,
	cmp	r2, sl	@ D.37804, D.37803
	bge	.L52	@,
	ldrb	lr, [r4, #37]	@ zero_extendqisi2	@ tmp567,
	add	r9, r7, r4	@ tmp561, phase, pCntxt22
	ldrb	r8, [r4, #36]	@ zero_extendqisi2	@ tmp566,
	mov	r2, r1	@ anomalFlg, tmp559
	ldrb	sl, [r4, #38]	@ zero_extendqisi2	@ tmp570,
	ldrb	r0, [r4, #39]	@ zero_extendqisi2	@ tmp573,
	orr	r5, r8, lr, asl #8	@, tmp569, tmp566, tmp567,
	ldrb	r8, [r9, #88]	@ zero_extendqisi2	@ tmp580, <variable>.phaseCnt
	orr	lr, r5, sl, asl #16	@, tmp572, tmp569, tmp570,
	orr	r1, lr, r0, asl #24	@, tmp575, tmp572, tmp573,
	mvn	sl, r1	@ tmp576, tmp575
	add	r1, r8, sl, asl #1	@, tmp582, tmp580, tmp576,
	strb	r1, [r9, #88]	@ tmp582, <variable>.phaseCnt
	b	.L29	@
.L76:
	add	r3, r0, r0, asl #1	@, tmp1652, max_crss_nonmatch, max_crss_nonmatch,
	cmp	ip, r3	@ tmp1636, tmp1652
	bgt	.L131	@,
	rsb	r0, r0, r0, asl #3	@, tmp1669, max_crss_nonmatch, max_crss_nonmatch,
	cmp	r0, r5, asl #1	@ tmp1669, tmp1637,
	blt	.L109	@,
	add	ip, r7, r4	@ tmp1681, phase, pCntxt22
	mov	r1, #1	@,
	str	r1, [fp, #-168]	@, %sfp
	ldrb	r5, [ip, #88]	@ zero_extendqisi2	@ tmp1687, <variable>.phaseCnt
	sub	r9, r5, #15	@ tmp1688, tmp1687,
	strb	r9, [ip, #88]	@ tmp1688, <variable>.phaseCnt
	b	.L70	@
.L101:
	beq	.L110	@,
	ldr	r9, [fp, #-196]	@, %sfp
	cmp	r9, r0	@, tmp1843
	bgt	.L136	@,
	ldr	r0, [fp, #-196]	@, %sfp
	cmp	r0, #1000	@,
	ble	.L77	@,
	ldr	r0, [fp, #-212]	@, %sfp
	cmp	ip, r0, asl #4	@ tmp1832,,
	ble	.L114	@,
.L128:
	add	r9, r7, r4	@ tmp2207, phase, pCntxt22
	str	r3, [fp, #-168]	@ tmp1837, %sfp
	ldrb	ip, [r9, #88]	@ zero_extendqisi2	@ tmp2213, <variable>.phaseCnt
	add	r5, ip, #1	@ tmp2214, tmp2213,
	strb	r5, [r9, #88]	@ tmp2214, <variable>.phaseCnt
	b	.L70	@
.L92:
	ldr	ip, [fp, #-212]	@, %sfp
	ldr	r5, [fp, #-152]	@, %sfp
	cmp	r5, ip, asl #1	@,,
	strgt	r3, [fp, #-168]	@ tmp1837, %sfp
	bgt	.L70	@,
	ldr	r1, [fp, #-212]	@, %sfp
	mov	r9, #3	@ tmp1975,
	mul	r3, r9, r1	@ tmp1974, tmp1975,
	cmp	r2, r3	@ tmp1844, tmp1974
	bgt	.L130	@,
	add	r9, r7, r4	@ tmp1987, phase, pCntxt22
	mov	r2, #1	@,
	str	r2, [fp, #-168]	@, %sfp
	ldrb	r1, [r9, #88]	@ zero_extendqisi2	@ tmp1993, <variable>.phaseCnt
	sub	r3, r1, #5	@ tmp1994, tmp1993,
	strb	r3, [r9, #88]	@ tmp1994, <variable>.phaseCnt
	b	.L70	@
.L102:
	ldr	ip, [fp, #-212]	@, %sfp
	mov	r5, #3	@ tmp2126,
	ldr	r0, [fp, #-152]	@, %sfp
	mul	r9, r5, ip	@ tmp2125, tmp2126,
	cmp	r9, r0, asl #1	@ tmp2125,,
	bge	.L109	@,
.L131:
	add	r2, r7, r4	@ tmp2128, phase, pCntxt22
	mov	r9, #1	@,
	str	r9, [fp, #-168]	@, %sfp
	ldrb	r1, [r2, #88]	@ zero_extendqisi2	@ tmp2134, <variable>.phaseCnt
	sub	r3, r1, #1	@ tmp2135, tmp2134,
	strb	r3, [r2, #88]	@ tmp2135, <variable>.phaseCnt
	b	.L70	@
.L109:
	add	r5, r7, r4	@ tmp2138, phase, pCntxt22
	mov	r3, #1	@,
	str	r3, [fp, #-168]	@, %sfp
	ldrb	r2, [r5, #88]	@ zero_extendqisi2	@ tmp2144, <variable>.phaseCnt
	sub	ip, r2, #5	@ tmp2145, tmp2144,
	strb	ip, [r5, #88]	@ tmp2145, <variable>.phaseCnt
	b	.L70	@
.L110:
	add	r1, r7, r4	@ tmp2261, phase, pCntxt22
	mov	r9, #1	@,
	str	r9, [fp, #-168]	@, %sfp
	ldrb	r2, [r1, #88]	@ zero_extendqisi2	@ tmp2267, <variable>.phaseCnt
	sub	r3, r2, #1	@ tmp2268, tmp2267,
	strb	r3, [r1, #88]	@ tmp2268, <variable>.phaseCnt
	b	.L70	@
.L93:
	ldr	r0, [fp, #-196]	@, %sfp
	cmp	r0, #1000	@,
	ble	.L128	@,
	ldr	r5, [fp, #-212]	@, %sfp
	cmp	ip, r5, asl #4	@ tmp1832,,
	bgt	.L128	@,
	ldr	r9, [fp, #-212]	@, %sfp
	mov	r3, #3	@ tmp1917,
	ldr	r2, [fp, #-164]	@, %sfp
	mul	ip, r3, r9	@ tmp1916, tmp1917,
	cmp	ip, r2, asl #1	@ tmp1916,,
	blt	.L77	@,
	ldr	r0, [fp, #-160]	@, %sfp
	ldr	r5, [fp, #-156]	@, %sfp
	orr	r2, r1, r0, asl #8	@, tmp1921, tmp2862,,
	ldr	r0, [fp, #-168]	@, %sfp
	orr	r1, r2, r0, asl #16	@, tmp1924, tmp1921,,
	orr	r1, r1, r5, asl #24	@, tmp1927, tmp1924,,
	cmp	r1, #1	@ tmp1927,
	beq	.L127	@,
	add	ip, r7, r4	@ tmp1953, phase, pCntxt22
	mov	r1, #1	@,
	str	r1, [fp, #-168]	@, %sfp
	ldrb	r9, [ip, #88]	@ zero_extendqisi2	@ tmp1959, <variable>.phaseCnt
	sub	r3, r9, #1	@ tmp1960, tmp1959,
	strb	r3, [ip, #88]	@ tmp1960, <variable>.phaseCnt
	b	.L70	@
.L136:
	ldr	r2, [fp, #-212]	@, %sfp
	ldr	ip, [fp, #-164]	@, %sfp
	mov	r5, r2, asl #4	@ tmp2149,,
	cmp	r5, ip, asl #1	@ tmp2149,,
	blt	.L128	@,
	ldr	r0, [fp, #-160]	@, %sfp
	ldr	r5, [fp, #-168]	@, %sfp
	ldr	r3, [fp, #-156]	@, %sfp
	orr	r9, r1, r0, asl #8	@, tmp2163, tmp2862,,
	orr	r1, r9, r5, asl #16	@, tmp2166, tmp2163,,
	orr	r1, r1, r3, asl #24	@, tmp2169, tmp2166,,
	cmp	r1, #1	@ tmp2169,
	beq	.L127	@,
	add	ip, r7, r4	@ tmp2195, phase, pCntxt22
	mov	r3, #1	@,
	str	r3, [fp, #-168]	@, %sfp
	ldrb	r1, [ip, #88]	@ zero_extendqisi2	@ tmp2201, <variable>.phaseCnt
	sub	r2, r1, #1	@ tmp2202, tmp2201,
	strb	r2, [ip, #88]	@ tmp2202, <variable>.phaseCnt
	b	.L70	@
.L52:
	ldrb	r0, [r4, #37]	@ zero_extendqisi2	@ tmp591,
	mov	r2, r1	@ anomalFlg, tmp559
	ldrb	r8, [r4, #36]	@ zero_extendqisi2	@ tmp590,
	add	r9, r7, r4	@ tmp585, phase, pCntxt22
	ldrb	r1, [r4, #38]	@ zero_extendqisi2	@ tmp594,
	ldrb	sl, [r4, #39]	@ zero_extendqisi2	@ tmp597,
	orr	r5, r8, r0, asl #8	@, tmp593, tmp590, tmp591,
	ldrb	r0, [r9, #88]	@ zero_extendqisi2	@ tmp603, <variable>.phaseCnt
	orr	lr, r5, r1, asl #16	@, tmp596, tmp593, tmp594,
	orr	r5, lr, sl, asl #24	@, tmp599, tmp596, tmp597,
	mvn	r1, r5	@ tmp601, tmp599
	add	r1, r0, r1	@ tmp605, tmp603, tmp601
	strb	r1, [r9, #88]	@ tmp605, <variable>.phaseCnt
	b	.L29	@
.L127:
	ldrb	r3, [r4, #37]	@ zero_extendqisi2	@ tmp2233,
	add	r2, r7, r4	@ tmp2227, phase, pCntxt22
	ldrb	r0, [r4, #36]	@ zero_extendqisi2	@ tmp2232,
	str	r1, [fp, #-168]	@ tmp2225, %sfp
	ldrb	r1, [r4, #38]	@ zero_extendqisi2	@ tmp2236,
	orr	ip, r0, r3, asl #8	@, tmp2235, tmp2232, tmp2233,
	ldrb	r5, [r4, #39]	@ zero_extendqisi2	@ tmp2239,
	ldrb	r0, [r2, #88]	@ zero_extendqisi2	@ tmp2246, <variable>.phaseCnt
	orr	r9, ip, r1, asl #16	@, tmp2238, tmp2235, tmp2236,
	orr	r1, r9, r5, asl #24	@, tmp2241, tmp2238, tmp2239,
	mvn	r3, r1	@ tmp2242, tmp2241
	add	ip, r0, r3, asl #1	@, tmp2248, tmp2246, tmp2242,
	strb	ip, [r2, #88]	@ tmp2248, <variable>.phaseCnt
	b	.L70	@
	.fnend
	.size	Detect22Pld, .-Detect22Pld
	.align	2
	.global	PQ_MNG_SetIFmdEn
	.type	PQ_MNG_SetIFmdEn, %function
PQ_MNG_SetIFmdEn:
	.fnstart
.LFB1415:
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
	.size	PQ_MNG_SetIFmdEn, .-PQ_MNG_SetIFmdEn
	.align	2
	.global	PQ_MNG_IFMD_SetIPDetect
	.type	PQ_MNG_IFMD_SetIPDetect, %function
PQ_MNG_IFMD_SetIPDetect:
	.fnstart
.LFB1414:
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
	movw	ip, #:lower16:-131071	@ tmp142,
	movt	ip, #:upper16:-131071	@ tmp142,
	cmp	r0, ip	@ u32Addr, tmp142
	cmpeq	r1, #0	@, u8Lsb,
	moveq	r0, #0	@, tmp146
	movne	r0, #1	@, tmp146
	bne	.L147	@,
	cmp	r2, #1	@ u8Msb,
	movweq	r2, #:lower16:.LANCHOR0	@ tmp150,
	movteq	r2, #:upper16:.LANCHOR0	@ tmp150,
	streq	r3, [r2, #4]	@ u32Value, sg_u32IPDetect
	bne	.L147	@,
.L149:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L147:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L151	@,
	movw	r3, #2264	@,
	movw	lr, #:lower16:.LC0	@ tmp149,
	movt	lr, #:upper16:.LC0	@ tmp149,
	str	lr, [sp, #0]	@ tmp149,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.37493,
	b	.L149	@
.L152:
	.align	2
.L151:
	.word	.LANCHOR1+100
	.fnend
	.size	PQ_MNG_IFMD_SetIPDetect, .-PQ_MNG_IFMD_SetIPDetect
	.align	2
	.global	PQ_MNG_IFMD_SofewareParaInitByHandleNo
	.type	PQ_MNG_IFMD_SofewareParaInitByHandleNo, %function
PQ_MNG_IFMD_SofewareParaInitByHandleNo:
	.fnstart
.LFB1393:
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
	mov	r3, #488	@ tmp141,
	mul	r3, r3, r0	@ tmp140, tmp141, u32HandleNo
	ldr	r2, .L157	@ tmp139,
	adds	r4, r2, r3	@ pstFmdSoftInfo, tmp139, tmp140
	mvneq	r0, #0	@ D.35964,
	ldmeqfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	mov	r5, #0	@ tmp144,
	add	r0, r4, #10	@, pstFmdSoftInfo,
	strb	r5, [r2, r3]	@ tmp144,
	movw	r1, #446	@,
	strb	r5, [r4, #1]	@ tmp144,
	mov	r6, #2	@ tmp265,
	strb	r5, [r4, #2]	@ tmp144,
	strb	r5, [r4, #3]	@ tmp144,
	bl	__memzero	@
	add	r2, r4, #30	@ D.35970, pstFmdSoftInfo,
	mvn	r3, #0	@ tmp243,
	and	ip, r2, #255	@ tmp159, D.35970,
	mov	r1, r2, lsr #24	@ tmp185, D.35970,
	strb	r6, [r4, #197]	@ tmp265,
	strb	r1, [r4, #101]	@ tmp185,
	mov	r6, #1	@ tmp279,
	strb	r1, [r4, #105]	@ tmp185,
	mov	r0, r5	@ D.35964, tmp144
	ubfx	r1, r2, #8, #8	@ tmp168, D.35970,,
	strb	r5, [r4, #94]	@ tmp144,
	ubfx	r2, r2, #16, #8	@ tmp177, D.35970,,
	strb	ip, [r4, #98]	@ tmp159,
	strb	r1, [r4, #99]	@ tmp168,
	strb	r2, [r4, #100]	@ tmp177,
	strb	r6, [r4, #431]	@ tmp279, <variable>.stFmdCtx.init_symbol
	strb	ip, [r4, #102]	@ tmp159,
	strb	r1, [r4, #103]	@ tmp168,
	strb	r2, [r4, #104]	@ tmp177,
	strb	r5, [r4, #95]	@ tmp144,
	strb	r5, [r4, #96]	@ tmp144,
	strb	r5, [r4, #97]	@ tmp144,
	strb	r3, [r4, #192]	@ tmp243, <variable>.stFmdCtx.Last32Phase
	strb	r5, [r4, #193]	@ tmp144,
	strb	r5, [r4, #194]	@ tmp144,
	strb	r5, [r4, #195]	@ tmp144,
	strb	r5, [r4, #196]	@ tmp144,
	strb	r5, [r4, #198]	@ tmp144,
	strb	r5, [r4, #199]	@ tmp144,
	strb	r5, [r4, #200]	@ tmp144,
	strb	r5, [r4, #432]	@ tmp144,
	strb	r5, [r4, #433]	@ tmp144,
	strb	r5, [r4, #434]	@ tmp144,
	strb	r5, [r4, #435]	@ tmp144,
	strb	r5, [r4, #436]	@ tmp144,
	strb	r5, [r4, #437]	@ tmp144,
	strb	r5, [r4, #438]	@ tmp144,
	strb	r5, [r4, #439]	@ tmp144,
	strb	r5, [r4, #440]	@ tmp144,
	strb	r5, [r4, #441]	@ tmp144,
	strb	r5, [r4, #442]	@ tmp144,
	strb	r5, [r4, #443]	@ tmp144,
	strb	r3, [r4, #9]	@ tmp243, <variable>.stBtMode.g_nxtbtmode
	strb	r5, [r4, #459]	@ tmp144,
	strb	r5, [r4, #444]	@ tmp144,
	strb	r5, [r4, #445]	@ tmp144,
	strb	r5, [r4, #446]	@ tmp144,
	strb	r5, [r4, #447]	@ tmp144,
	strb	r5, [r4, #448]	@ tmp144,
	strb	r5, [r4, #449]	@ tmp144,
	strb	r5, [r4, #450]	@ tmp144,
	strb	r5, [r4, #451]	@ tmp144,
	strb	r5, [r4, #452]	@ tmp144,
	strb	r5, [r4, #453]	@ tmp144,
	strb	r5, [r4, #454]	@ tmp144,
	strb	r5, [r4, #455]	@ tmp144,
	strb	r3, [r4, #4]	@ tmp243, <variable>.stRefFld.g_lstreffld
	strb	r3, [r4, #5]	@ tmp243, <variable>.stRefFld.g_curreffld
	strb	r3, [r4, #6]	@ tmp243, <variable>.stRefFld.g_nxtreffld
	strb	r3, [r4, #7]	@ tmp243, <variable>.stBtMode.g_lstbtmode
	strb	r3, [r4, #8]	@ tmp243, <variable>.stBtMode.g_curbtmode
	strb	r5, [r4, #456]	@ tmp144,
	strb	r5, [r4, #457]	@ tmp144,
	strb	r5, [r4, #458]	@ tmp144,
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L158:
	.align	2
.L157:
	.word	.LANCHOR0+8
	.fnend
	.size	PQ_MNG_IFMD_SofewareParaInitByHandleNo, .-PQ_MNG_IFMD_SofewareParaInitByHandleNo
	.align	2
	.global	PQ_MNG_IFMD_SofewareParaInit
	.type	PQ_MNG_IFMD_SofewareParaInit, %function
PQ_MNG_IFMD_SofewareParaInit:
	.fnstart
.LFB1395:
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
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #1	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #2	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #3	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #4	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #5	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #6	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #7	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #8	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #9	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #10	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #11	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #12	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #13	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #14	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #15	@,
	bl	PQ_MNG_IFMD_SofewareParaInitByHandleNo	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_IFMD_SofewareParaInit, .-PQ_MNG_IFMD_SofewareParaInit
	.align	2
	.global	PQ_MNG_IFMD_GetPlayBackConfig
	.type	PQ_MNG_IFMD_GetPlayBackConfig, %function
PQ_MNG_IFMD_GetPlayBackConfig:
	.fnstart
.LFB1412:
	@ args = 0, pretend = 0, frame = 856
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #868
	sub	sp, sp, #868	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r5, r1	@ pstIfmdCalc, pstIfmdCalc
	sub	r1, fp, #96	@,,
	str	r1, [fp, #-880]	@, %sfp
	ldrb	lr, [r5, #1]	@ zero_extendqisi2	@ tmp293,
	mov	r4, r0	@ pIfmdTotalHardPara, pIfmdTotalHardPara
	ldrb	r6, [r5, #0]	@ zero_extendqisi2	@ tmp292,* pstIfmdCalc
	mov	r0, r1	@,
	ldrb	r8, [r5, #2]	@ zero_extendqisi2	@ tmp296,
	mov	r1, #28	@,
	ldrb	r7, [r5, #3]	@ zero_extendqisi2	@ tmp299,
	orr	ip, r6, lr, asl #8	@, tmp295, tmp292, tmp293,
	mov	r6, #488	@ tmp303,
	str	r2, [fp, #-760]	@ pstIfmdResult, %sfp
	orr	r9, ip, r8, asl #16	@, tmp298, tmp295, tmp296,
	movw	sl, #:lower16:.LANCHOR0	@,
	orr	r3, r9, r7, asl #24	@, tmp301, tmp298, tmp299,
	movt	sl, #:upper16:.LANCHOR0	@,
	str	sl, [fp, #-772]	@, %sfp
	add	r7, sl, #8	@ tmp291,,
	mul	r6, r6, r3	@ tmp302, tmp303, tmp301
	bl	__memzero	@
	sub	r0, fp, #748	@,,
	mov	r1, #584	@,
	bl	__memzero	@
	mov	r1, r4	@, pIfmdTotalHardPara
	mov	r2, #332	@,
	sub	r0, fp, #664	@,,
	bl	memcpy	@
	add	r1, r4, #332	@, pIfmdTotalHardPara,
	mov	r2, #168	@,
	sub	r0, fp, #332	@,,
	bl	memcpy	@
	add	r1, r5, #28	@, pstIfmdCalc,
	mov	r2, #12	@,
	sub	r0, fp, #676	@,,
	bl	memcpy	@
	ldrb	r0, [r5, #21]	@ zero_extendqisi2	@ tmp323,
	ldrb	r2, [r5, #20]	@ zero_extendqisi2	@ tmp322,
	mov	r3, #1	@ tmp333,
	ldrb	lr, [r5, #22]	@ zero_extendqisi2	@ tmp326,
	add	r4, r7, r6	@ pstFmdSoftInfo, tmp291, tmp302
	ldrb	r9, [r5, #23]	@ zero_extendqisi2	@ tmp329,
	orr	r8, r2, r0, asl #8	@, tmp325, tmp322, tmp323,
	ldrb	ip, [r5, #17]	@ zero_extendqisi2	@,
	mov	r2, #0	@ tmp389,
	orr	r1, r8, lr, asl #16	@, tmp328, tmp325, tmp326,
	ldrb	sl, [r5, #5]	@ zero_extendqisi2	@ tmp336,
	ldrb	r8, [r5, #13]	@ zero_extendqisi2	@ tmp356,
	orr	r1, r1, r9, asl #24	@, tmp331, tmp328, tmp329,
	ldrb	r0, [r5, #9]	@ zero_extendqisi2	@ tmp346,
	str	ip, [fp, #-764]	@, %sfp
	mov	lr, r1, lsr r3	@, tmp331,
	ldrb	r9, [r5, #25]	@ zero_extendqisi2	@,
	str	lr, [fp, #-776]	@, %sfp
	str	r9, [fp, #-768]	@, %sfp
	ldrb	ip, [r5, #4]	@ zero_extendqisi2	@ tmp335,
	ldrb	r9, [r5, #6]	@ zero_extendqisi2	@ tmp339,
	ldrb	lr, [r5, #12]	@ zero_extendqisi2	@ tmp355,
	orr	sl, ip, sl, asl #8	@, tmp338, tmp335, tmp336,
	ldrb	r1, [r5, #8]	@ zero_extendqisi2	@ tmp345,
	ldrb	ip, [r5, #10]	@ zero_extendqisi2	@ tmp349,
	orr	lr, lr, r8, asl #8	@, tmp358, tmp355, tmp356,
	ldr	r8, [fp, #-764]	@, %sfp
	orr	r0, r1, r0, asl #8	@, tmp348, tmp345, tmp346,
	orr	r9, sl, r9, asl #16	@,, tmp338, tmp339,
	ldrb	r1, [r5, #14]	@ zero_extendqisi2	@ tmp359,
	str	r9, [fp, #-756]	@, %sfp
	orr	ip, r0, ip, asl #16	@,, tmp348, tmp349,
	ldrb	sl, [r5, #16]	@ zero_extendqisi2	@ tmp365,
	ldrb	r9, [r5, #18]	@ zero_extendqisi2	@ tmp369,
	orr	r1, lr, r1, asl #16	@, tmp361, tmp358, tmp359,
	str	ip, [fp, #-752]	@, %sfp
	orr	sl, sl, r8, asl #8	@, tmp368, tmp365,,
	ldr	ip, [fp, #-768]	@, %sfp
	ldrb	r0, [r5, #24]	@ zero_extendqisi2	@ tmp375,
	orr	sl, sl, r9, asl #16	@, tmp371, tmp368, tmp369,
	ldrb	r8, [r5, #26]	@ zero_extendqisi2	@ tmp379,
	ldrb	lr, [r5, #27]	@ zero_extendqisi2	@ tmp382,
	orr	r0, r0, ip, asl #8	@, tmp378, tmp375,,
	ldrb	ip, [r5, #7]	@ zero_extendqisi2	@ tmp342,
	orr	r8, r0, r8, asl #16	@, tmp381, tmp378, tmp379,
	ldrb	r9, [r5, #11]	@ zero_extendqisi2	@ tmp352,
	orr	r8, r8, lr, asl #24	@, tmp384, tmp381, tmp382,
	ldr	lr, [fp, #-756]	@, %sfp
	ldrb	r0, [r5, #15]	@ zero_extendqisi2	@ tmp362,
	orr	ip, lr, ip, asl #24	@, tmp344,, tmp342,
	ldr	lr, [fp, #-776]	@, %sfp
	ldrb	r5, [r5, #19]	@ zero_extendqisi2	@ tmp372,
	str	lr, [fp, #-668]	@, stDeiDrvPara.stVdecInfo.RealFrmRate
	ldr	lr, [fp, #-752]	@, %sfp
	orr	sl, sl, r5, asl #24	@, tmp374, tmp371, tmp372,
	str	ip, [fp, #-704]	@ tmp344, stDeiDrvPara.s32FrmWidth
	str	r8, [fp, #-680]	@ tmp384, stDeiDrvPara.bPreInfo
	orr	r9, lr, r9, asl #24	@, tmp354,, tmp352,
	str	sl, [fp, #-684]	@ tmp374, stDeiDrvPara.RefFld
	orr	lr, r1, r0, asl #24	@, tmp364, tmp361, tmp362,
	str	r9, [fp, #-708]	@ tmp354, stDeiDrvPara.s32FrmHeight
	str	r3, [fp, #-740]	@ tmp333, stDeiDrvPara.s32DeiMdLum
	str	r3, [fp, #-736]	@ tmp333, stDeiDrvPara.s32DeiMdChr
	str	lr, [fp, #-688]	@ tmp364, stDeiDrvPara.BtMode
	str	r3, [fp, #-700]	@ tmp333, stDeiDrvPara.bOfflineMode
	str	r3, [fp, #-728]	@ tmp333, stDeiDrvPara.FodEnable
	ldrb	ip, [r4, #1]	@ zero_extendqisi2	@ tmp392,
	ldrb	r1, [r7, r6]	@ zero_extendqisi2	@ tmp391,
	ldrb	r0, [r4, #2]	@ zero_extendqisi2	@ tmp395,
	orr	ip, r1, ip, asl #8	@, tmp394, tmp391, tmp392,
	ldrb	r1, [r4, #3]	@ zero_extendqisi2	@ tmp398,
	str	r2, [fp, #-696]	@ tmp389, stDeiDrvPara.s32Repeat
	orr	ip, ip, r0, asl #16	@, tmp397, tmp394, tmp395,
	str	r3, [fp, #-724]	@ tmp333, stDeiDrvPara.Pld22Enable
	str	r3, [fp, #-720]	@ tmp333, stDeiDrvPara.Pld32Enable
	orrs	ip, ip, r1, asl #24	@, tmp400, tmp397, tmp398,
	str	r2, [fp, #-692]	@ tmp389, stDeiDrvPara.s32Drop
	beq	.L376	@,
	sub	r0, fp, #96	@,,
	mov	r1, #28	@,
	bl	__memzero	@
	ldr	r0, [fp, #-680]	@ tmp455,
	cmp	r0, #1	@ tmp455,
	beq	.L377	@,
	ldrb	r2, [r4, #7]	@ zero_extendqisi2	@ <variable>.stBtMode.g_lstbtmode, <variable>.stBtMode.g_lstbtmode
	cmp	r2, #255	@ <variable>.stBtMode.g_lstbtmode,
	beq	.L165	@,
	ldrb	sl, [r4, #8]	@ zero_extendqisi2	@ <variable>.stBtMode.g_curbtmode, <variable>.stBtMode.g_curbtmode
	cmp	sl, #255	@ <variable>.stBtMode.g_curbtmode,
	beq	.L165	@,
	ldrb	r7, [r4, #9]	@ zero_extendqisi2	@ <variable>.stBtMode.g_nxtbtmode, <variable>.stBtMode.g_nxtbtmode
	cmp	r7, #255	@ <variable>.stBtMode.g_nxtbtmode,
	beq	.L165	@,
	ldrb	r8, [r4, #4]	@ zero_extendqisi2	@ <variable>.stRefFld.g_lstreffld, <variable>.stRefFld.g_lstreffld
	cmp	r8, #255	@ <variable>.stRefFld.g_lstreffld,
	beq	.L167	@,
.L395:
	ldrb	r3, [r4, #5]	@ zero_extendqisi2	@ <variable>.stRefFld.g_curreffld, <variable>.stRefFld.g_curreffld
	cmp	r3, #255	@ <variable>.stRefFld.g_curreffld,
	ldrne	r3, [fp, #-700]	@ tmp4855,
	beq	.L167	@,
.L168:
	cmp	r3, #0	@ tmp4855,
	mov	r1, #0	@ tmp498,
	strb	r1, [r4, #19]	@ tmp498,
	mov	sl, #0	@ tmp533,
	ldrneb	r2, [r4, #9]	@ zero_extendqisi2	@ iftmp.487, <variable>.stBtMode.g_nxtbtmode
	mov	lr, #0	@ tmp542,
	ldreqb	r2, [r4, #8]	@ zero_extendqisi2	@ iftmp.487, <variable>.stBtMode.g_curbtmode
	cmp	r3, #0	@ tmp4855,
	strb	r1, [r4, #20]	@ tmp507,
	strb	sl, [r4, #23]	@ tmp533,
	mov	r1, r2, lsr #24	@ tmp515, iftmp.487,
	strb	r1, [r4, #21]	@ tmp515,
	ldrneb	r1, [r4, #6]	@ zero_extendqisi2	@ iftmp.488, <variable>.stRefFld.g_nxtreffld
	ldreqb	r1, [r4, #5]	@ zero_extendqisi2	@ iftmp.488, <variable>.stRefFld.g_curreffld
	cmp	r3, #0	@ tmp4855,
	strb	r2, [r4, #18]	@ iftmp.487,
	movne	ip, #1	@, iftmp.489,
	moveq	ip, #2	@, iftmp.489,
	strb	lr, [r4, #24]	@ tmp542,
	strb	r1, [r4, #22]	@ iftmp.488,
	mov	r3, ip, lsr #24	@ tmp585, iftmp.489,
	strb	ip, [r4, #26]	@ iftmp.489,
	mov	r6, r1, lsr #24	@ tmp550, iftmp.488,
	strb	r3, [r4, #29]	@ tmp585,
	mov	r3, #0	@ tmp568,
	strb	r6, [r4, #25]	@ tmp550,
	strb	r3, [r4, #27]	@ tmp568,
	strb	r3, [r4, #28]	@ tmp577,
	ldreqb	r0, [r4, #6]	@ zero_extendqisi2	@ nxt_ref_fld, <variable>.stRefFld.g_nxtreffld
	ldrne	r0, [fp, #-684]	@ nxt_ref_fld,
	ldrne	r3, [fp, #-688]	@ nxt_btmode,
	ldreqb	r3, [r4, #9]	@ zero_extendqisi2	@ nxt_btmode, <variable>.stBtMode.g_nxtbtmode
	cmp	r2, #0	@ iftmp.487,
	bne	.L183	@,
	subs	r5, r1, #0	@, iftmp.488,
	movne	r5, #1	@
	str	r5, [fp, #-776]	@, %sfp
.L184:
	orrs	ip, r0, r3	@ tmp598, nxt_ref_fld, nxt_btmode
	beq	.L187	@,
	cmp	r0, #1	@ nxt_ref_fld,
	cmpeq	r3, #1	@, nxt_btmode,
	movne	r0, #0	@, tmp603
	moveq	r0, #1	@, tmp603
	eor	ip, r0, #1	@ NxtIs2ndFld, tmp603,
.L187:
	ldrb	r2, [r4, #437]	@ zero_extendqisi2	@ tmp675,
	sub	r5, fp, #56	@,,
	str	r5, [fp, #-884]	@, %sfp
	mov	sl, ip, lsr #24	@ tmp666, NxtIs2ndFld,
	ldrb	r7, [r4, #436]	@ zero_extendqisi2	@ tmp674,
	sub	lr, fp, #56	@,,
	ldrb	r6, [r4, #441]	@ zero_extendqisi2	@ tmp719,
	add	r5, lr, #4	@ tmp914,,
	ldrb	r8, [r4, #438]	@ zero_extendqisi2	@ tmp678,
	orr	r0, r7, r2, asl #8	@, tmp677, tmp674, tmp675,
	ldrb	r9, [r4, #440]	@ zero_extendqisi2	@ tmp718,
	mov	r2, #0	@ tmp609,
	ldrb	r3, [r4, #442]	@ zero_extendqisi2	@ tmp722,
	mov	lr, r5	@ tmp4865, tmp914
	ldrb	r7, [r4, #439]	@ zero_extendqisi2	@ tmp681,
	orr	r1, r9, r6, asl #8	@, tmp721, tmp718, tmp719,
	orr	r0, r0, r8, asl #16	@, tmp680, tmp677, tmp678,
	ldrb	r8, [r4, #449]	@ zero_extendqisi2	@ tmp795,
	ldrb	r9, [r4, #443]	@ zero_extendqisi2	@ tmp725,
	orr	r1, r1, r3, asl #16	@, tmp724, tmp721, tmp722,
	orr	r0, r0, r7, asl #24	@, tmp683, tmp680, tmp681,
	ldrb	r3, [r4, #448]	@ zero_extendqisi2	@ tmp794,
	ldrb	r7, [r4, #450]	@ zero_extendqisi2	@ tmp798,
	orr	r3, r3, r8, asl #8	@, tmp797, tmp794, tmp795,
	ldrb	r6, [fp, #-696]	@ zero_extendqisi2	@,
	ldrb	r8, [fp, #-695]	@ zero_extendqisi2	@,
	orr	r1, r1, r9, asl #24	@, tmp727, tmp724, tmp725,
	orr	r3, r3, r7, asl #16	@, tmp800, tmp797, tmp798,
	ldrb	r9, [fp, #-694]	@ zero_extendqisi2	@,
	ldrb	r7, [fp, #-693]	@ zero_extendqisi2	@,
	str	r6, [fp, #-788]	@, %sfp
	str	r8, [fp, #-756]	@, %sfp
	mov	r8, r0, lsr #24	@ tmp710, tmp683,
	str	r7, [fp, #-764]	@, %sfp
	mov	r7, r1, lsr #24	@ tmp754, tmp727,
	str	r9, [fp, #-752]	@, %sfp
	ldrb	r9, [r4, #451]	@ zero_extendqisi2	@ tmp801,
	strb	sl, [r4, #17]	@ tmp666,
	strb	r2, [r4, #11]	@ tmp615,
	ldr	r6, [fp, #-776]	@, %sfp
	orr	r3, r3, r9, asl #24	@, tmp803, tmp800, tmp801,
	strb	r2, [r4, #12]	@ tmp624,
	ubfx	r9, ip, #16, #8	@ tmp658, NxtIs2ndFld,,
	strb	r8, [r4, #435]	@ tmp710,
	ubfx	r8, r0, #16, #8	@ tmp702, tmp683,,
	mov	sl, r6, lsr #24	@ tmp632,,
	strb	r9, [r4, #16]	@ tmp658,
	strb	sl, [r4, #13]	@ tmp632,
	ubfx	r6, ip, #8, #8	@ tmp649, NxtIs2ndFld,,
	ubfx	sl, r0, #8, #8	@ tmp693, tmp683,,
	strb	r6, [r4, #15]	@ tmp649,
	strb	sl, [r4, #433]	@ tmp693,
	ubfx	r6, r1, #8, #8	@ tmp737, tmp727,,
	strb	r8, [r4, #434]	@ tmp702,
	add	r9, r5, #6	@, tmp914,
	ubfx	r8, r1, #16, #8	@ tmp746, tmp727,,
	strb	r6, [r4, #437]	@ tmp737,
	mov	r5, r3, lsr #24	@, tmp803,
	str	r9, [fp, #-780]	@, %sfp
	strb	r8, [r4, #438]	@ tmp746,
	ubfx	sl, r3, #8, #8	@, tmp803,,
	str	r5, [fp, #-784]	@, %sfp
	strb	r7, [r4, #439]	@ tmp754,
	ldr	r6, [fp, #-788]	@, %sfp
	str	sl, [fp, #-768]	@, %sfp
	strb	r6, [r4, #440]	@,
	ubfx	r6, r3, #16, #8	@ tmp822, tmp803,,
	ldr	r9, [fp, #-756]	@, %sfp
	strb	r9, [r4, #441]	@,
	ldr	r8, [fp, #-752]	@, %sfp
	strb	r8, [r4, #442]	@,
	ldr	r7, [fp, #-764]	@, %sfp
	strb	r7, [r4, #443]	@,
	ldr	r5, [fp, #-776]	@, %sfp
	strb	r0, [r4, #432]	@ tmp683,
	strb	r1, [r4, #436]	@ tmp727,
	strb	r5, [r4, #10]	@,
	strb	ip, [r4, #14]	@ NxtIs2ndFld,
	strb	r3, [r4, #444]	@ tmp803,
	ldrb	r8, [fp, #-692]	@ zero_extendqisi2	@ tmp882,
	ldrb	r7, [fp, #-691]	@ zero_extendqisi2	@ tmp890,
	ldrb	r5, [fp, #-690]	@ zero_extendqisi2	@ tmp898,
	ldrb	r3, [fp, #-689]	@ zero_extendqisi2	@,
	str	r2, [lr], #4	@ tmp609, Pld32Info
	strh	r2, [lr, #0]	@ movhi	@ tmp609, Pld32Info
	ldr	ip, [fp, #-708]	@,
	ldr	lr, [fp, #-704]	@,
	str	r3, [fp, #-752]	@, %sfp
	str	ip, [fp, #-868]	@, %sfp
	str	lr, [fp, #-872]	@, %sfp
	ldrb	r0, [r4, #453]	@ zero_extendqisi2	@ tmp839,
	ldrb	r1, [r4, #452]	@ zero_extendqisi2	@ tmp838,
	mul	r3, lr, ip	@ tmp921,,
	ldrb	sl, [r4, #454]	@ zero_extendqisi2	@ tmp842,
	ldrb	ip, [r4, #336]	@ zero_extendqisi2	@ tmp959,
	orr	r9, r1, r0, asl #8	@, tmp841, tmp838, tmp839,
	ldrb	r0, [r4, #335]	@ zero_extendqisi2	@ tmp958,
	orr	r1, r9, sl, asl #16	@, tmp844, tmp841, tmp842,
	ldrb	r9, [r4, #334]	@ zero_extendqisi2	@ tmp4818,
	orr	ip, r0, ip, asl #8	@, tmp962, tmp958, tmp959,
	ldr	r0, [fp, #-780]	@, %sfp
	ldrb	sl, [r4, #333]	@ zero_extendqisi2	@ tmp4817,
	mov	r3, r3, asr #11	@ D.38510, tmp921,
	ldrb	lr, [r4, #455]	@ zero_extendqisi2	@ tmp845,
	orr	r9, sl, r9, asl #8	@,, tmp4817, tmp4818,
	strb	r2, [r0, #0]	@ tmp609, Pld32Info
	str	r9, [fp, #-756]	@, %sfp
	mov	r0, ip, lsr #8	@ tmp973, tmp962,
	ldr	r9, [fp, #-768]	@, %sfp
	orr	r1, r1, lr, asl #24	@, tmp847, tmp844, tmp845,
	strb	r6, [r4, #446]	@ tmp822,
	ubfx	r6, r1, #8, #8	@ tmp857, tmp847,,
	mov	lr, r1, lsr #24	@ tmp874, tmp847,
	and	ip, ip, #255	@ tmp963, tmp962,
	strb	r9, [r4, #445]	@,
	ubfx	r9, r1, #16, #8	@ tmp866, tmp847,,
	ldr	sl, [fp, #-784]	@, %sfp
	strb	lr, [r4, #451]	@ tmp874,
	ubfx	lr, r3, #16, #8	@ tmp942, D.38510,,
	strb	r6, [r4, #449]	@ tmp857,
	ubfx	r6, r3, #8, #8	@ tmp933, D.38510,,
	strb	r9, [r4, #450]	@ tmp866,
	mov	r9, r3, lsr #24	@ tmp950, D.38510,
	strb	r7, [r4, #453]	@ tmp890,
	strb	sl, [r4, #447]	@,
	strb	r8, [r4, #452]	@ tmp882,
	ldr	sl, [fp, #-756]	@, %sfp
	mov	r7, sl, lsr #8	@,,
	str	r7, [fp, #-800]	@, %sfp
	strb	r5, [r4, #454]	@ tmp898,
	orr	r5, ip, r0, asl #8	@, tmp1698, tmp963, tmp973,
	ldr	r8, [fp, #-752]	@, %sfp
	cmp	r3, r5	@ D.38510, tmp1698
	strb	r6, [r4, #457]	@ tmp933,
	strb	lr, [r4, #458]	@ tmp942,
	strb	r8, [r4, #455]	@,
	strb	r9, [r4, #459]	@ tmp950,
	strb	r1, [r4, #448]	@ tmp847,
	str	r2, [fp, #-56]	@ tmp609, Pld32Info
	strb	ip, [r4, #337]	@ tmp963,
	strb	r0, [r4, #338]	@ tmp973,
	strb	r3, [r4, #456]	@ D.38510,
	ldr	sl, [fp, #-756]	@, %sfp
	ldrb	r7, [r4, #342]	@ zero_extendqisi2	@ tmp1005,
	ldrb	r5, [r4, #348]	@ zero_extendqisi2	@ tmp1051,
	strb	sl, [r4, #335]	@,
	ldrb	sl, [r4, #340]	@ zero_extendqisi2	@,
	ldrb	ip, [r4, #354]	@ zero_extendqisi2	@ tmp1097,
	ldrb	r1, [r4, #360]	@ zero_extendqisi2	@ tmp1143,
	str	sl, [fp, #-764]	@, %sfp
	ldrb	r9, [r4, #346]	@ zero_extendqisi2	@,
	str	r9, [fp, #-784]	@, %sfp
	ldrb	r6, [r4, #352]	@ zero_extendqisi2	@,
	str	r6, [fp, #-788]	@, %sfp
	ldrb	lr, [r4, #358]	@ zero_extendqisi2	@,
	str	lr, [fp, #-796]	@, %sfp
	ldrb	lr, [r4, #339]	@ zero_extendqisi2	@,
	ldrb	r8, [r4, #347]	@ zero_extendqisi2	@ tmp1050,
	ldrb	r2, [r4, #341]	@ zero_extendqisi2	@ tmp1004,
	ldrb	r0, [r4, #353]	@ zero_extendqisi2	@ tmp1096,
	orr	r5, r8, r5, asl #8	@, tmp1054, tmp1050, tmp1051,
	ldrb	r9, [r4, #359]	@ zero_extendqisi2	@ tmp1142,
	orr	r7, r2, r7, asl #8	@, tmp1008, tmp1004, tmp1005,
	str	lr, [fp, #-752]	@, %sfp
	orr	ip, r0, ip, asl #8	@, tmp1100, tmp1096, tmp1097,
	ldrb	r8, [r4, #345]	@ zero_extendqisi2	@,
	orr	r1, r9, r1, asl #8	@, tmp1146, tmp1142, tmp1143,
	ldr	r0, [fp, #-784]	@, %sfp
	str	r8, [fp, #-768]	@, %sfp
	ldrb	r6, [r4, #351]	@ zero_extendqisi2	@,
	str	r6, [fp, #-780]	@, %sfp
	orr	r6, lr, sl, asl #8	@, tmp1031,,,
	orr	lr, r8, r0, asl #8	@, tmp1077,,,
	ldr	r8, [fp, #-788]	@, %sfp
	ldr	r2, [fp, #-780]	@, %sfp
	ldrb	sl, [r4, #357]	@ zero_extendqisi2	@,
	orr	r0, r2, r8, asl #8	@, tmp1123,,,
	ldr	r8, [fp, #-796]	@, %sfp
	str	sl, [fp, #-792]	@, %sfp
	ldrb	r9, [r4, #366]	@ zero_extendqisi2	@ tmp1189,
	orr	r2, sl, r8, asl #8	@, tmp1169,,,
	ldrb	sl, [r4, #365]	@ zero_extendqisi2	@ tmp1188,
	ldr	r8, [fp, #-800]	@, %sfp
	orr	sl, sl, r9, asl #8	@, tmp1192, tmp1188, tmp1189,
	strb	r7, [r4, #343]	@ tmp1008,
	mov	r9, r6, lsr #8	@ tmp1042, tmp1031,
	strb	r9, [r4, #342]	@ tmp1042,
	strb	r8, [r4, #336]	@,
	mov	r9, ip, lsr #8	@ tmp1111, tmp1100,
	mov	r8, r7, lsr #8	@ tmp1019, tmp1008,
	strb	r9, [r4, #356]	@ tmp1111,
	mov	r7, r5, lsr #8	@ tmp1065, tmp1054,
	mov	r9, r2, lsr #8	@ tmp1180, tmp1169,
	strb	r8, [r4, #344]	@ tmp1019,
	mov	r8, lr, lsr #8	@ tmp1088, tmp1077,
	strb	r7, [r4, #350]	@ tmp1065,
	mov	r7, r0, lsr #8	@ tmp1134, tmp1123,
	strb	r8, [r4, #348]	@ tmp1088,
	mov	r8, r1, lsr #8	@ tmp1157, tmp1146,
	strb	r7, [r4, #354]	@ tmp1134,
	mov	r7, sl, lsr #8	@, tmp1192,
	strb	r8, [r4, #362]	@ tmp1157,
	strb	r9, [r4, #360]	@ tmp1180,
	str	r7, [fp, #-840]	@, %sfp
	strb	sl, [r4, #367]	@ tmp1192,
	ldrb	sl, [r4, #364]	@ zero_extendqisi2	@,
	strb	r6, [r4, #341]	@ tmp1031,
	strb	r5, [r4, #349]	@ tmp1054,
	strb	lr, [r4, #347]	@ tmp1077,
	strb	ip, [r4, #355]	@ tmp1100,
	strb	r0, [r4, #353]	@ tmp1123,
	strb	r1, [r4, #361]	@ tmp1146,
	strb	r2, [r4, #359]	@ tmp1169,
	ldrb	r8, [r4, #372]	@ zero_extendqisi2	@ tmp1235,
	ldrb	r5, [r4, #378]	@ zero_extendqisi2	@ tmp1281,
	ldrb	ip, [r4, #384]	@ zero_extendqisi2	@ tmp1327,
	str	sl, [fp, #-804]	@, %sfp
	ldrb	r6, [r4, #370]	@ zero_extendqisi2	@,
	str	r6, [fp, #-812]	@, %sfp
	ldrb	r0, [r4, #376]	@ zero_extendqisi2	@,
	str	r0, [fp, #-820]	@, %sfp
	ldrb	r1, [r4, #382]	@ zero_extendqisi2	@,
	str	r1, [fp, #-828]	@, %sfp
	ldrb	r7, [r4, #363]	@ zero_extendqisi2	@,
	ldrb	lr, [r4, #371]	@ zero_extendqisi2	@ tmp1234,
	ldrb	r9, [r4, #377]	@ zero_extendqisi2	@ tmp1280,
	orr	sl, r7, sl, asl #8	@, tmp1215,,,
	ldrb	r2, [r4, #383]	@ zero_extendqisi2	@ tmp1326,
	orr	r8, lr, r8, asl #8	@, tmp1238, tmp1234, tmp1235,
	ldrb	r1, [r4, #390]	@ zero_extendqisi2	@ tmp1373,
	orr	r5, r9, r5, asl #8	@, tmp1284, tmp1280, tmp1281,
	str	r7, [fp, #-800]	@, %sfp
	orr	ip, r2, ip, asl #8	@, tmp1330, tmp1326, tmp1327,
	ldrb	r0, [r4, #369]	@ zero_extendqisi2	@,
	ldr	lr, [fp, #-812]	@, %sfp
	ldr	r7, [fp, #-820]	@, %sfp
	str	r0, [fp, #-808]	@, %sfp
	ldrb	r9, [r4, #375]	@ zero_extendqisi2	@,
	str	r9, [fp, #-816]	@, %sfp
	ldrb	r6, [r4, #381]	@ zero_extendqisi2	@,
	str	r6, [fp, #-824]	@, %sfp
	orr	r6, r0, lr, asl #8	@, tmp1261,,,
	ldrb	r0, [r4, #388]	@ zero_extendqisi2	@,
	orr	lr, r9, r7, asl #8	@, tmp1307,,,
	ldrb	r2, [r4, #389]	@ zero_extendqisi2	@ tmp1372,
	str	r0, [fp, #-836]	@, %sfp
	orr	r1, r2, r1, asl #8	@, tmp1376, tmp1372, tmp1373,
	ldr	r9, [fp, #-828]	@, %sfp
	ldr	r7, [fp, #-824]	@, %sfp
	ldrb	r2, [r4, #387]	@ zero_extendqisi2	@,
	orr	r0, r7, r9, asl #8	@, tmp1353,,,
	ldr	r9, [fp, #-840]	@, %sfp
	mov	r7, sl, lsr #8	@ tmp1226, tmp1215,
	str	r2, [fp, #-832]	@, %sfp
	mov	r2, r8, lsr #8	@ tmp1249, tmp1238,
	strb	r9, [r4, #368]	@,
	mov	r9, r6, lsr #8	@ tmp1272, tmp1261,
	strb	r7, [r4, #366]	@ tmp1226,
	mov	r7, r5, lsr #8	@ tmp1295, tmp1284,
	strb	r2, [r4, #374]	@ tmp1249,
	mov	r2, lr, lsr #8	@ tmp1318, tmp1307,
	strb	r9, [r4, #372]	@ tmp1272,
	mov	r9, ip, lsr #8	@ tmp1341, tmp1330,
	strb	r7, [r4, #380]	@ tmp1295,
	mov	r7, r0, lsr #8	@ tmp1364, tmp1353,
	strb	r2, [r4, #378]	@ tmp1318,
	mov	r2, r1, lsr #8	@ tmp1387, tmp1376,
	strb	r9, [r4, #386]	@ tmp1341,
	strb	r2, [r4, #392]	@ tmp1387,
	strb	r7, [r4, #384]	@ tmp1364,
	ldr	r7, [fp, #-836]	@, %sfp
	ldr	r9, [fp, #-832]	@, %sfp
	strb	sl, [r4, #365]	@ tmp1215,
	orr	r2, r9, r7, asl #8	@, tmp1399,,,
	strb	r8, [r4, #373]	@ tmp1238,
	mov	r9, r2, lsr #8	@, tmp1399,
	str	r9, [fp, #-896]	@, %sfp
	strb	r0, [r4, #383]	@ tmp1353,
	ldrb	r0, [r4, #394]	@ zero_extendqisi2	@,
	ldrb	r8, [r4, #402]	@ zero_extendqisi2	@ tmp1465,
	strb	r6, [r4, #371]	@ tmp1261,
	strb	r5, [r4, #379]	@ tmp1284,
	strb	lr, [r4, #377]	@ tmp1307,
	ldrb	r5, [r4, #396]	@ zero_extendqisi2	@ tmp1419,
	strb	ip, [r4, #385]	@ tmp1330,
	strb	r1, [r4, #391]	@ tmp1376,
	strb	r2, [r4, #389]	@ tmp1399,
	ldrb	ip, [r4, #408]	@ zero_extendqisi2	@ tmp1511,
	ldrb	r1, [r4, #414]	@ zero_extendqisi2	@ tmp1557,
	str	r0, [fp, #-840]	@, %sfp
	ldrb	sl, [r4, #400]	@ zero_extendqisi2	@,
	str	sl, [fp, #-848]	@, %sfp
	ldrb	r6, [r4, #406]	@ zero_extendqisi2	@,
	str	r6, [fp, #-856]	@, %sfp
	ldrb	r7, [r4, #412]	@ zero_extendqisi2	@,
	str	r7, [fp, #-864]	@, %sfp
	ldrb	r0, [r4, #399]	@ zero_extendqisi2	@,
	ldrb	r2, [r4, #395]	@ zero_extendqisi2	@ tmp1418,
	ldrb	lr, [r4, #401]	@ zero_extendqisi2	@ tmp1464,
	ldrb	r9, [r4, #407]	@ zero_extendqisi2	@ tmp1510,
	orr	r7, r2, r5, asl #8	@, tmp1422, tmp1418, tmp1419,
	ldrb	sl, [r4, #413]	@ zero_extendqisi2	@ tmp1556,
	orr	r5, lr, r8, asl #8	@, tmp1468, tmp1464, tmp1465,
	ldrb	r8, [r4, #393]	@ zero_extendqisi2	@ tmp4839,
	orr	ip, r9, ip, asl #8	@, tmp1514, tmp1510, tmp1511,
	str	r0, [fp, #-844]	@, %sfp
	orr	r1, sl, r1, asl #8	@, tmp1560, tmp1556, tmp1557,
	ldrb	r6, [r4, #405]	@ zero_extendqisi2	@,
	ldr	r2, [fp, #-848]	@, %sfp
	ldr	r9, [fp, #-840]	@, %sfp
	str	r6, [fp, #-852]	@, %sfp
	ldrb	lr, [r4, #411]	@ zero_extendqisi2	@,
	ldr	sl, [fp, #-844]	@, %sfp
	orr	r6, r8, r9, asl #8	@, tmp1445, tmp4839,,
	ldr	r9, [fp, #-852]	@, %sfp
	str	lr, [fp, #-860]	@, %sfp
	orr	lr, sl, r2, asl #8	@, tmp1491,,,
	ldrb	r0, [r4, #420]	@ zero_extendqisi2	@,
	ldr	r2, [fp, #-856]	@, %sfp
	ldr	sl, [fp, #-864]	@, %sfp
	str	r0, [fp, #-900]	@, %sfp
	orr	r0, r9, r2, asl #8	@, tmp1537,,,
	ldr	r9, [fp, #-860]	@, %sfp
	orr	r2, r9, sl, asl #8	@, tmp1583,,,
	ldr	sl, [fp, #-896]	@, %sfp
	ldrb	r9, [r4, #419]	@ zero_extendqisi2	@ tmp1602,
	strb	sl, [r4, #390]	@,
	mov	sl, r7, lsr #8	@, tmp1422,
	str	sl, [fp, #-896]	@, %sfp
	ldr	sl, [fp, #-900]	@, %sfp
	orr	r9, r9, sl, asl #8	@, tmp1606, tmp1602,,
	ldr	sl, [fp, #-896]	@, %sfp
	strb	r7, [r4, #397]	@ tmp1422,
	mov	r7, r6, lsr #8	@ tmp1456, tmp1445,
	strb	r7, [r4, #396]	@ tmp1456,
	mov	r7, r5, lsr #8	@ tmp1479, tmp1468,
	strb	sl, [r4, #398]	@,
	strb	r7, [r4, #404]	@ tmp1479,
	mov	r7, lr, lsr #8	@ tmp1502, tmp1491,
	strb	r6, [r4, #395]	@ tmp1445,
	strb	r7, [r4, #402]	@ tmp1502,
	mov	r7, ip, lsr #8	@ tmp1525, tmp1514,
	strb	lr, [r4, #401]	@ tmp1491,
	strb	r7, [r4, #410]	@ tmp1525,
	mov	r7, r0, lsr #8	@ tmp1548, tmp1537,
	strb	r1, [r4, #415]	@ tmp1560,
	strb	r7, [r4, #408]	@ tmp1548,
	mov	r7, r1, lsr #8	@ tmp1571, tmp1560,
	ldrb	r6, [r4, #418]	@ zero_extendqisi2	@ tmp4848,
	ldrb	r1, [r4, #426]	@ zero_extendqisi2	@ tmp1649,
	ldrb	lr, [r4, #424]	@ zero_extendqisi2	@ tmp4850,
	strb	r7, [r4, #416]	@ tmp1571,
	mov	r7, r2, lsr #8	@ tmp1594, tmp1583,
	strb	r5, [r4, #403]	@ tmp1468,
	strb	ip, [r4, #409]	@ tmp1514,
	strb	r2, [r4, #413]	@ tmp1583,
	ldrb	r5, [r4, #417]	@ zero_extendqisi2	@ tmp4847,
	ldrb	r2, [r4, #425]	@ zero_extendqisi2	@ tmp1648,
	ldrb	ip, [r4, #423]	@ zero_extendqisi2	@ tmp4849,
	orr	r1, r2, r1, asl #8	@, tmp1652, tmp1648, tmp1649,
	strb	r0, [r4, #407]	@ tmp1537,
	orr	r2, ip, lr, asl #8	@, tmp1675, tmp4849, tmp4850,
	orr	r0, r5, r6, asl #8	@, tmp1629, tmp4847, tmp4848,
	strb	r7, [r4, #414]	@ tmp1594,
	mov	r7, r9, lsr #8	@ tmp1617, tmp1606,
	strb	r9, [r4, #421]	@ tmp1606,
	strb	r7, [r4, #422]	@ tmp1617,
	mov	r7, r1, lsr #8	@ tmp1663, tmp1652,
	strb	r0, [r4, #419]	@ tmp1629,
	strb	r7, [r4, #428]	@ tmp1663,
	mov	r7, r0, lsr #8	@ tmp1640, tmp1629,
	strb	r1, [r4, #427]	@ tmp1652,
	strb	r7, [r4, #420]	@ tmp1640,
	mov	r7, r2, lsr #8	@ tmp1686, tmp1675,
	strb	r2, [r4, #425]	@ tmp1675,
	strb	r7, [r4, #426]	@ tmp1686,
	ble	.L188	@,
	ldr	r1, [fp, #-756]	@, %sfp
	cmp	r3, r1	@ D.38510,
	bgt	.L378	@,
.L188:
	mov	r0, #0	@ stillBlkCnt,
.L189:
	ldrb	r1, [r4, #344]	@ zero_extendqisi2	@ tmp1732,
	ldrb	r2, [r4, #343]	@ zero_extendqisi2	@ tmp1731,
	orr	r1, r2, r1, asl #8	@, tmp1735, tmp1731, tmp1732,
	ldr	r2, [fp, #-512]	@ tmp1711,
	cmp	r3, r1	@ D.38510, tmp1735
	uxth	r2, r2	@ tmp1712, tmp1711
	strb	r2, [r4, #333]	@ tmp1712,
	mov	r2, r2, lsr #8	@ tmp1723, tmp1712,
	strb	r2, [r4, #334]	@ tmp1723,
	ble	.L190	@,
	ldr	r7, [fp, #-764]	@, %sfp
	ldr	r1, [fp, #-752]	@, %sfp
	orr	r2, r1, r7, asl #8	@, tmp1740,,,
	cmp	r3, r2	@ D.38510, tmp1740
	bgt	.L379	@,
.L190:
	ldrb	r1, [r4, #350]	@ zero_extendqisi2	@ tmp1767,
	ldrb	r2, [r4, #349]	@ zero_extendqisi2	@ tmp1766,
	orr	r1, r2, r1, asl #8	@, tmp1770, tmp1766, tmp1767,
	ldr	r2, [fp, #-508]	@ tmp1746,
	cmp	r3, r1	@ D.38510, tmp1770
	uxth	r2, r2	@ tmp1747, tmp1746
	strb	r2, [r4, #339]	@ tmp1747,
	mov	r2, r2, lsr #8	@ tmp1758, tmp1747,
	strb	r2, [r4, #340]	@ tmp1758,
	ble	.L191	@,
	ldr	sl, [fp, #-784]	@, %sfp
	ldr	r9, [fp, #-768]	@, %sfp
	orr	r1, r9, sl, asl #8	@, tmp1775,,,
	cmp	r3, r1	@ D.38510, tmp1775
	bgt	.L380	@,
.L191:
	ldrb	r1, [r4, #356]	@ zero_extendqisi2	@ tmp1802,
	ldrb	r2, [r4, #355]	@ zero_extendqisi2	@ tmp1801,
	orr	r1, r2, r1, asl #8	@, tmp1805, tmp1801, tmp1802,
	ldr	r2, [fp, #-504]	@ tmp1781,
	cmp	r3, r1	@ D.38510, tmp1805
	uxth	r2, r2	@ tmp1782, tmp1781
	strb	r2, [r4, #345]	@ tmp1782,
	mov	r2, r2, lsr #8	@ tmp1793, tmp1782,
	strb	r2, [r4, #346]	@ tmp1793,
	ble	.L192	@,
	ldr	r7, [fp, #-788]	@, %sfp
	ldr	r1, [fp, #-780]	@, %sfp
	orr	r2, r1, r7, asl #8	@, tmp1810,,,
	cmp	r3, r2	@ D.38510, tmp1810
	bgt	.L381	@,
.L192:
	ldrb	r1, [r4, #362]	@ zero_extendqisi2	@ tmp1837,
	ldrb	r2, [r4, #361]	@ zero_extendqisi2	@ tmp1836,
	orr	r1, r2, r1, asl #8	@, tmp1840, tmp1836, tmp1837,
	ldr	r2, [fp, #-500]	@ tmp1816,
	cmp	r3, r1	@ D.38510, tmp1840
	uxth	r2, r2	@ tmp1817, tmp1816
	strb	r2, [r4, #351]	@ tmp1817,
	mov	r2, r2, lsr #8	@ tmp1828, tmp1817,
	strb	r2, [r4, #352]	@ tmp1828,
	ble	.L193	@,
	ldr	sl, [fp, #-796]	@, %sfp
	ldr	r9, [fp, #-792]	@, %sfp
	orr	r1, r9, sl, asl #8	@, tmp1845,,,
	cmp	r3, r1	@ D.38510, tmp1845
	bgt	.L382	@,
.L193:
	ldrb	r1, [r4, #368]	@ zero_extendqisi2	@ tmp1872,
	ldrb	r2, [r4, #367]	@ zero_extendqisi2	@ tmp1871,
	orr	r1, r2, r1, asl #8	@, tmp1875, tmp1871, tmp1872,
	ldr	r2, [fp, #-496]	@ tmp1851,
	cmp	r3, r1	@ D.38510, tmp1875
	uxth	r2, r2	@ tmp1852, tmp1851
	strb	r2, [r4, #357]	@ tmp1852,
	mov	r2, r2, lsr #8	@ tmp1863, tmp1852,
	strb	r2, [r4, #358]	@ tmp1863,
	ble	.L194	@,
	ldr	r7, [fp, #-804]	@, %sfp
	ldr	r1, [fp, #-800]	@, %sfp
	orr	r2, r1, r7, asl #8	@, tmp1880,,,
	cmp	r3, r2	@ D.38510, tmp1880
	bgt	.L383	@,
.L194:
	ldrb	r1, [r4, #374]	@ zero_extendqisi2	@ tmp1907,
	ldrb	r2, [r4, #373]	@ zero_extendqisi2	@ tmp1906,
	orr	r1, r2, r1, asl #8	@, tmp1910, tmp1906, tmp1907,
	ldr	r2, [fp, #-492]	@ tmp1886,
	cmp	r3, r1	@ D.38510, tmp1910
	uxth	r2, r2	@ tmp1887, tmp1886
	strb	r2, [r4, #363]	@ tmp1887,
	mov	r2, r2, lsr #8	@ tmp1898, tmp1887,
	strb	r2, [r4, #364]	@ tmp1898,
	ble	.L195	@,
	ldr	sl, [fp, #-812]	@, %sfp
	ldr	r9, [fp, #-808]	@, %sfp
	orr	r1, r9, sl, asl #8	@, tmp1915,,,
	cmp	r3, r1	@ D.38510, tmp1915
	bgt	.L384	@,
.L195:
	ldrb	r1, [r4, #380]	@ zero_extendqisi2	@ tmp1942,
	ldrb	r2, [r4, #379]	@ zero_extendqisi2	@ tmp1941,
	orr	r1, r2, r1, asl #8	@, tmp1945, tmp1941, tmp1942,
	ldr	r2, [fp, #-488]	@ tmp1921,
	cmp	r3, r1	@ D.38510, tmp1945
	uxth	r2, r2	@ tmp1922, tmp1921
	strb	r2, [r4, #369]	@ tmp1922,
	mov	r2, r2, lsr #8	@ tmp1933, tmp1922,
	strb	r2, [r4, #370]	@ tmp1933,
	ble	.L196	@,
	ldr	r7, [fp, #-820]	@, %sfp
	ldr	r1, [fp, #-816]	@, %sfp
	orr	r2, r1, r7, asl #8	@, tmp1950,,,
	cmp	r3, r2	@ D.38510, tmp1950
	bgt	.L385	@,
.L196:
	ldrb	r1, [r4, #386]	@ zero_extendqisi2	@ tmp1977,
	ldrb	r2, [r4, #385]	@ zero_extendqisi2	@ tmp1976,
	orr	r1, r2, r1, asl #8	@, tmp1980, tmp1976, tmp1977,
	ldr	r2, [fp, #-484]	@ tmp1956,
	cmp	r3, r1	@ D.38510, tmp1980
	uxth	r2, r2	@ tmp1957, tmp1956
	strb	r2, [r4, #375]	@ tmp1957,
	mov	r2, r2, lsr #8	@ tmp1968, tmp1957,
	strb	r2, [r4, #376]	@ tmp1968,
	ble	.L197	@,
	ldr	sl, [fp, #-828]	@, %sfp
	ldr	r9, [fp, #-824]	@, %sfp
	orr	r1, r9, sl, asl #8	@, tmp1985,,,
	cmp	r3, r1	@ D.38510, tmp1985
	bgt	.L386	@,
.L197:
	ldrb	r1, [r4, #392]	@ zero_extendqisi2	@ tmp2012,
	ldrb	r2, [r4, #391]	@ zero_extendqisi2	@ tmp2011,
	orr	r1, r2, r1, asl #8	@, tmp2015, tmp2011, tmp2012,
	ldr	r2, [fp, #-480]	@ tmp1991,
	cmp	r3, r1	@ D.38510, tmp2015
	uxth	r2, r2	@ tmp1992, tmp1991
	strb	r2, [r4, #381]	@ tmp1992,
	mov	r2, r2, lsr #8	@ tmp2003, tmp1992,
	strb	r2, [r4, #382]	@ tmp2003,
	ble	.L198	@,
	ldr	r7, [fp, #-836]	@, %sfp
	ldr	r1, [fp, #-832]	@, %sfp
	orr	r2, r1, r7, asl #8	@, tmp2020,,,
	cmp	r3, r2	@ D.38510, tmp2020
	bgt	.L387	@,
.L198:
	ldrb	r1, [r4, #398]	@ zero_extendqisi2	@ tmp2047,
	ldrb	r2, [r4, #397]	@ zero_extendqisi2	@ tmp2046,
	orr	r1, r2, r1, asl #8	@, tmp2050, tmp2046, tmp2047,
	ldr	r2, [fp, #-476]	@ tmp2026,
	cmp	r3, r1	@ D.38510, tmp2050
	uxth	r2, r2	@ tmp2027, tmp2026
	strb	r2, [r4, #387]	@ tmp2027,
	mov	r2, r2, lsr #8	@ tmp2038, tmp2027,
	strb	r2, [r4, #388]	@ tmp2038,
	ble	.L199	@,
	ldr	r9, [fp, #-840]	@, %sfp
	orr	r8, r8, r9, asl #8	@, tmp2055, tmp4839,,
	cmp	r3, r8	@ D.38510, tmp2055
	bgt	.L388	@,
.L199:
	ldrb	r1, [r4, #404]	@ zero_extendqisi2	@ tmp2082,
	ldrb	r2, [r4, #403]	@ zero_extendqisi2	@ tmp2081,
	orr	r1, r2, r1, asl #8	@, tmp2085, tmp2081, tmp2082,
	ldr	r2, [fp, #-472]	@ tmp2061,
	cmp	r3, r1	@ D.38510, tmp2085
	uxth	r2, r2	@ tmp2062, tmp2061
	strb	r2, [r4, #393]	@ tmp2062,
	mov	r2, r2, lsr #8	@ tmp2073, tmp2062,
	strb	r2, [r4, #394]	@ tmp2073,
	ble	.L200	@,
	ldr	r1, [fp, #-848]	@, %sfp
	ldr	sl, [fp, #-844]	@, %sfp
	orr	r2, sl, r1, asl #8	@, tmp2090,,,
	cmp	r3, r2	@ D.38510, tmp2090
	bgt	.L389	@,
.L200:
	ldrb	r1, [r4, #410]	@ zero_extendqisi2	@ tmp2117,
	ldrb	r2, [r4, #409]	@ zero_extendqisi2	@ tmp2116,
	orr	r1, r2, r1, asl #8	@, tmp2120, tmp2116, tmp2117,
	ldr	r2, [fp, #-468]	@ tmp2096,
	cmp	r3, r1	@ D.38510, tmp2120
	uxth	r2, r2	@ tmp2097, tmp2096
	strb	r2, [r4, #399]	@ tmp2097,
	mov	r2, r2, lsr #8	@ tmp2108, tmp2097,
	strb	r2, [r4, #400]	@ tmp2108,
	ble	.L201	@,
	ldr	r8, [fp, #-856]	@, %sfp
	ldr	r7, [fp, #-852]	@, %sfp
	orr	r1, r7, r8, asl #8	@, tmp2125,,,
	cmp	r3, r1	@ D.38510, tmp2125
	bgt	.L390	@,
.L201:
	ldrb	r1, [r4, #416]	@ zero_extendqisi2	@ tmp2152,
	ldrb	r2, [r4, #415]	@ zero_extendqisi2	@ tmp2151,
	orr	r1, r2, r1, asl #8	@, tmp2155, tmp2151, tmp2152,
	ldr	r2, [fp, #-464]	@ tmp2131,
	cmp	r3, r1	@ D.38510, tmp2155
	uxth	r2, r2	@ tmp2132, tmp2131
	strb	r2, [r4, #405]	@ tmp2132,
	mov	r2, r2, lsr #8	@ tmp2143, tmp2132,
	strb	r2, [r4, #406]	@ tmp2143,
	ble	.L202	@,
	ldr	sl, [fp, #-864]	@, %sfp
	ldr	r9, [fp, #-860]	@, %sfp
	orr	r1, r9, sl, asl #8	@, tmp2160,,,
	cmp	r3, r1	@ D.38510, tmp2160
	bgt	.L391	@,
.L202:
	ldrb	r1, [r4, #422]	@ zero_extendqisi2	@ tmp2187,
	ldrb	r2, [r4, #421]	@ zero_extendqisi2	@ tmp2186,
	orr	r1, r2, r1, asl #8	@, tmp2190, tmp2186, tmp2187,
	ldr	r2, [fp, #-460]	@ tmp2166,
	cmp	r3, r1	@ D.38510, tmp2190
	uxth	r2, r2	@ tmp2167, tmp2166
	strb	r2, [r4, #411]	@ tmp2167,
	mov	r2, r2, lsr #8	@ tmp2178, tmp2167,
	strb	r2, [r4, #412]	@ tmp2178,
	ble	.L203	@,
	orr	r5, r5, r6, asl #8	@, tmp2195, tmp4847, tmp4848,
	cmp	r3, r5	@ D.38510, tmp2195
	bgt	.L392	@,
.L203:
	ldrb	r1, [r4, #428]	@ zero_extendqisi2	@ tmp2222,
	ldrb	r2, [r4, #427]	@ zero_extendqisi2	@ tmp2221,
	orr	r1, r2, r1, asl #8	@, tmp2225, tmp2221, tmp2222,
	ldr	r2, [fp, #-456]	@ tmp2201,
	cmp	r3, r1	@ D.38510, tmp2225
	uxth	r2, r2	@ tmp2202, tmp2201
	strb	r2, [r4, #417]	@ tmp2202,
	mov	r2, r2, lsr #8	@ tmp2213, tmp2202,
	strb	r2, [r4, #418]	@ tmp2213,
	ble	.L204	@,
	orr	ip, ip, lr, asl #8	@, tmp2230, tmp4849, tmp4850,
	cmp	r3, ip	@ D.38510, tmp2230
	bgt	.L393	@,
.L204:
	ldr	r3, [fp, #-452]	@ tmp2236,
	ldr	r2, [fp, #-728]	@ D.38509,
	str	r0, [fp, #-516]	@ stillBlkCnt, stDeiDrvPara.stFmdRtlStatPara.StillBlkInfo.StillBlkCnt
	uxth	r1, r3	@ tmp2237, tmp2236
	cmp	r2, #1	@ D.38509,
	strb	r1, [r4, #423]	@ tmp2237,
	mov	r3, r1, lsr #8	@ tmp2248, tmp2237,
	strb	r3, [r4, #424]	@ tmp2248,
	beq	.L394	@,
	cmp	r2, #2	@ D.38509,
	moveq	sl, #0	@,
	streq	sl, [fp, #-752]	@, %sfp
	beq	.L208	@,
	cmp	r2, #3	@ D.38509,
	moveq	ip, #1	@,
	streq	ip, [fp, #-752]	@, %sfp
	beq	.L208	@,
.L206:
	mov	lr, #2	@,
	str	lr, [fp, #-752]	@, %sfp
.L208:
	ldr	sl, [fp, #-776]	@, %sfp
	movw	r0, #:lower16:200000	@ tmp2882,
	ldrb	lr, [r4, #212]	@ zero_extendqisi2	@ tmp2652,
	movt	r0, #:upper16:200000	@ tmp2882,
	ldrb	r1, [r4, #208]	@ zero_extendqisi2	@ tmp2598,
	add	r6, sl, r4	@,, pstFmdSoftInfo
	ldrb	r9, [r4, #216]	@ zero_extendqisi2	@ tmp2706,
	str	r6, [fp, #-756]	@, %sfp
	ldrb	r2, [r4, #211]	@ zero_extendqisi2	@ tmp2651,
	ldrb	r3, [r4, #207]	@ zero_extendqisi2	@ tmp2597,
	ldrb	r5, [r4, #209]	@ zero_extendqisi2	@ tmp2601,
	orr	sl, r2, lr, asl #8	@, tmp2654, tmp2651, tmp2652,
	ldrb	lr, [r4, #210]	@ zero_extendqisi2	@ tmp2604,
	orr	r7, r3, r1, asl #8	@, tmp2600, tmp2597, tmp2598,
	ldrb	ip, [r4, #213]	@ zero_extendqisi2	@ tmp2655,
	ldrb	r8, [r4, #215]	@ zero_extendqisi2	@ tmp2705,
	orr	r1, r7, r5, asl #16	@, tmp2603, tmp2600, tmp2601,
	ldrb	r6, [r4, #217]	@ zero_extendqisi2	@ tmp2709,
	orr	r1, r1, lr, asl #24	@, tmp2606, tmp2603, tmp2604,
	ldrb	r5, [r4, #214]	@ zero_extendqisi2	@ tmp2658,
	orr	r3, r8, r9, asl #8	@, tmp2708, tmp2705, tmp2706,
	ldrb	r7, [r4, #218]	@ zero_extendqisi2	@ tmp2712,
	orr	r2, sl, ip, asl #16	@, tmp2657, tmp2654, tmp2655,
	ldrb	lr, [r4, #204]	@ zero_extendqisi2	@ tmp2588,
	orr	r9, r3, r6, asl #16	@, tmp2711, tmp2708, tmp2709,
	ldrb	ip, [r4, #203]	@ zero_extendqisi2	@ tmp2587,
	orr	r2, r2, r5, asl #24	@, tmp2660, tmp2657, tmp2658,
	ldrb	sl, [r4, #220]	@ zero_extendqisi2	@ tmp2760,
	orr	r3, r9, r7, asl #24	@, tmp2714, tmp2711, tmp2712,
	ldrb	r5, [r4, #205]	@ zero_extendqisi2	@ tmp2591,
	orr	lr, ip, lr, asl #8	@, tmp2590, tmp2587, tmp2588,
	ldrb	r8, [r4, #219]	@ zero_extendqisi2	@ tmp2759,
	ubfx	r9, r1, #8, #8	@ tmp2616, tmp2606,,
	ldrb	r7, [r4, #221]	@ zero_extendqisi2	@ tmp2763,
	ldrb	ip, [r4, #206]	@ zero_extendqisi2	@ tmp2594,
	orr	r6, r8, sl, asl #8	@, tmp2762, tmp2759, tmp2760,
	ldrb	r8, [r4, #222]	@ zero_extendqisi2	@ tmp2766,
	ubfx	sl, r1, #16, #8	@ tmp2625, tmp2606,,
	orr	r6, r6, r7, asl #16	@, tmp2765, tmp2762, tmp2763,
	orr	r7, lr, r5, asl #16	@, tmp2593, tmp2590, tmp2591,
	ubfx	r5, r2, #16, #8	@ tmp2679, tmp2660,,
	strb	r5, [r4, #209]	@ tmp2679,
	ubfx	r5, r3, #16, #8	@ tmp2733, tmp2714,,
	strb	r5, [r4, #213]	@ tmp2733,
	orr	r5, r7, ip, asl #24	@, tmp2596, tmp2593, tmp2594,
	orr	r6, r6, r8, asl #24	@, tmp2768, tmp2765, tmp2766,
	cmp	r1, r5	@ tmp2606, tmp2596
	movge	ip, r1	@ MaxSad.1316, tmp2606
	movlt	ip, r5	@ MaxSad.1316, tmp2596
	add	lr, r1, r5	@ SadMean.1317, tmp2606, tmp2596
	mov	r8, r1, lsr #24	@ tmp2633, tmp2606,
	strb	sl, [r4, #205]	@ tmp2625,
	strb	r1, [r4, #203]	@ tmp2606,
	ubfx	sl, r2, #8, #8	@ tmp2670, tmp2660,,
	strb	r8, [r4, #206]	@ tmp2633,
	mov	r8, r2, lsr #24	@ tmp2687, tmp2660,
	strb	sl, [r4, #208]	@ tmp2670,
	ubfx	sl, r3, #8, #8	@ tmp2724, tmp2714,,
	strb	r8, [r4, #210]	@ tmp2687,
	mov	r8, r3, lsr #24	@ tmp2741, tmp2714,
	strb	sl, [r4, #212]	@ tmp2724,
	cmp	r1, r5	@ tmp2606, tmp2596
	movlt	sl, r1	@ MaxSad.1315, tmp2606
	movge	sl, r5	@ MaxSad.1315, tmp2596
	strb	r8, [r4, #214]	@ tmp2741,
	cmp	r2, sl	@ tmp2660, MaxSad.1315
	movlt	sl, r2	@ MaxSad.1320, tmp2660
	movge	sl, sl	@ MaxSad.1320, MaxSad.1315
	strb	r2, [r4, #207]	@ tmp2660,
	add	r8, r2, lr	@ SadMean.1322, tmp2660, SadMean.1317
	strb	r9, [r4, #204]	@ tmp2616,
	cmp	r2, ip	@ tmp2660, MaxSad.1316
	movlt	r2, ip	@ MaxSad.1321, MaxSad.1316
	strb	r3, [r4, #211]	@ tmp2714,
	cmp	r3, sl	@ tmp2714, MaxSad.1320
	movlt	lr, r3	@ MaxSad.1325, tmp2714
	movge	lr, sl	@ MaxSad.1325, MaxSad.1320
	ldrb	r7, [r4, #224]	@ zero_extendqisi2	@ tmp2814,
	cmp	r3, r2	@ tmp2714, MaxSad.1321
	movge	r2, r3	@ MaxSad.1326, tmp2714
	movlt	r2, r2	@ MaxSad.1326, MaxSad.1321
	ldrb	r5, [r4, #223]	@ zero_extendqisi2	@ tmp2813,
	add	r8, r3, r8	@ SadMean.1327, tmp2714, SadMean.1322
	ldrb	ip, [r4, #225]	@ zero_extendqisi2	@ tmp2817,
	cmp	r6, lr	@ tmp2768, MaxSad.1325
	movlt	lr, r6	@ MaxSad.1330, tmp2768
	movge	lr, lr	@ MaxSad.1330, MaxSad.1325
	ldrb	r1, [r4, #226]	@ zero_extendqisi2	@ tmp2820,
	orr	r3, r5, r7, asl #8	@, tmp2816, tmp2813, tmp2814,
	strb	r6, [r4, #215]	@ tmp2768,
	add	r8, r6, r8	@ SadMean.1332, tmp2768, SadMean.1327
	ldr	r5, [fp, #-532]	@ tmp2581,
	orr	r7, r3, ip, asl #16	@, tmp2819, tmp2816, tmp2817,
	orr	r1, r7, r1, asl #24	@, tmp2822, tmp2819, tmp2820,
	ldr	r3, [fp, #-536]	@ tmp2583,
	cmp	r1, lr	@ tmp2822, MaxSad.1330
	movlt	ip, r1	@ tmp2868, tmp2822
	movge	ip, lr	@ tmp2868, MaxSad.1330
	cmp	r6, r2	@ tmp2768, MaxSad.1326
	movge	r2, r6	@ MaxSad.1331, tmp2768
	movlt	r2, r2	@ MaxSad.1331, MaxSad.1326
	add	r8, r1, r8	@ tmp2867, tmp2822, SadMean.1332
	add	r7, r3, r5, asl #1	@, tmp2582, tmp2583, tmp2581,
	cmp	r1, r2	@ tmp2822, MaxSad.1331
	movge	r2, r1	@ tmp2870, tmp2822
	movlt	r2, r2	@ tmp2870, MaxSad.1331
	rsb	r5, ip, r8	@ tmp2869, tmp2868, tmp2867
	rsb	r8, r2, r5	@ D.38474, tmp2870, tmp2869
	ldr	lr, [fp, #-540]	@ tmp2586,
	add	ip, r8, #3	@ tmp2876, D.38474,
	cmp	r8, #0	@ D.38474,
	add	r3, lr, r7, asl #1	@, tmp2585, tmp2586, tmp2582,
	strb	r1, [r4, #219]	@ tmp2822,
	movlt	r8, ip	@ D.38474, tmp2876
	ubfx	r5, r6, #8, #8	@ tmp2778, tmp2768,,
	mov	lr, r8, asr #2	@ tmp2877, D.38474,
	mov	r3, r3, asl #1	@ CurSad, tmp2585,
	strb	r5, [r4, #216]	@ tmp2778,
	ubfx	r7, r6, #16, #8	@ tmp2787, tmp2768,,
	cmp	r3, lr, asl #1	@ CurSad, tmp2877,
	str	r3, [r4, #223]	@ CurSad,
	strb	r7, [r4, #217]	@ tmp2787,
	mov	r2, r6, lsr #24	@ tmp2795, tmp2768,
	strb	r2, [r4, #218]	@ tmp2795,
	movle	ip, #0	@, tmp2880
	movgt	ip, #1	@, tmp2880
	ubfx	r8, r1, #8, #8	@ tmp2832, tmp2822,,
	cmp	r3, r0	@ CurSad, tmp2882
	movle	r3, #0	@, tmp2885
	andgt	r3, ip, #1	@,, tmp2885, tmp2880
	ubfx	r5, r1, #16, #8	@ tmp2841, tmp2822,,
	ldr	r0, [fp, #-776]	@, %sfp
	mov	r6, r1, lsr #24	@ tmp2849, tmp2822,
	strb	r8, [r4, #220]	@ tmp2832,
	strb	r5, [r4, #221]	@ tmp2841,
	cmp	r0, #0	@,
	strb	r6, [r4, #222]	@ tmp2849,
	ldr	r7, [fp, #-756]	@, %sfp
	strb	r3, [r7, #201]	@ tmp2885, <variable>.stFmdCtx.SceneChange
	beq	.L243	@,
	ldrsb	r3, [r4, #201]	@ <variable>.stFmdCtx.SceneChange, <variable>.stFmdCtx.SceneChange
	cmp	r3, #0	@ <variable>.stFmdCtx.SceneChange,
	beq	.L243	@,
	ldrsb	r0, [r4, #202]	@ <variable>.stFmdCtx.SceneChange, <variable>.stFmdCtx.SceneChange
	subs	r8, r0, #0	@ prephitmp.1043, <variable>.stFmdCtx.SceneChange,
	movne	r8, #1	@ prephitmp.1043
	b	.L244	@
.L165:
	ldrb	r8, [r4, #4]	@ zero_extendqisi2	@ <variable>.stRefFld.g_lstreffld, <variable>.stRefFld.g_lstreffld
	ldr	r9, [fp, #-688]	@ tmp465,
	cmp	r8, #255	@ <variable>.stRefFld.g_lstreffld,
	strb	r9, [r4, #9]	@ tmp465, <variable>.stBtMode.g_nxtbtmode
	strb	r9, [r4, #7]	@ tmp465, <variable>.stBtMode.g_lstbtmode
	strb	r9, [r4, #8]	@ tmp465, <variable>.stBtMode.g_curbtmode
	bne	.L395	@,
.L167:
	ldr	r3, [fp, #-700]	@ tmp4855,
	cmp	r3, #0	@ tmp4855,
	bne	.L396	@,
	ldr	r2, [fp, #-688]	@ tmp4856,
	uxtb	r1, r2	@ iftmp.484, tmp4856
.L170:
	cmp	r3, #0	@ tmp4855,
	strb	r1, [r4, #4]	@ iftmp.484, <variable>.stRefFld.g_lstreffld
	uxtbne	r1, r2	@ iftmp.485, tmp4856
	bne	.L172	@,
	rsbs	r1, r2, #1	@ iftmp.485, tmp4856
	movcc	r1, #0	@ iftmp.485
.L172:
	cmp	r3, #0	@ tmp4855,
	strb	r1, [r4, #5]	@ iftmp.485, <variable>.stRefFld.g_curreffld
	uxtbeq	r2, r2	@ iftmp.486, tmp4856
	beq	.L174	@,
	rsbs	r2, r2, #1	@ iftmp.486, tmp4856
	movcc	r2, #0	@ iftmp.486
.L174:
	strb	r2, [r4, #6]	@ iftmp.486, <variable>.stRefFld.g_nxtreffld
	b	.L168	@
.L376:
	strb	r3, [r7, r6]	@ tmp333,
	add	r0, r4, #460	@, pstFmdSoftInfo,
	str	lr, [fp, #-76]	@ tmp364, stFmdRtlOutPara.s32FieldOrder
	sub	r1, fp, #96	@,,
	strb	ip, [r4, #3]	@ tmp400,
	mov	r2, #28	@,
	str	ip, [fp, #-96]	@ tmp400, stFmdRtlOutPara.DirMch
	str	ip, [fp, #-88]	@ tmp400, stFmdRtlOutPara.DieOutSelChr
	str	ip, [fp, #-92]	@ tmp400, stFmdRtlOutPara.DieOutSelLum
	str	ip, [fp, #-84]	@ tmp400, stFmdRtlOutPara.EdgeSmoothEn
	strb	ip, [r4, #1]	@ tmp400,
	strb	ip, [r4, #2]	@ tmp400,
	bl	memcpy	@
.L163:
	ldr	r1, [fp, #-96]	@ tmp4709,
	mov	r0, #0	@,
	ldr	lr, [fp, #-76]	@ tmp4710,
	ldr	r3, [fp, #-84]	@ tmp4711,
	ldr	ip, [fp, #-92]	@ tmp4708,
	ldr	r4, [fp, #-760]	@, %sfp
	str	ip, [r4, #12]	@ tmp4708, <variable>.die_out_sel
	str	r1, [r4, #8]	@ tmp4709, <variable>.dir_mch
	str	r3, [r4, #36]	@ tmp4711, <variable>.u32EdgeSmoothEn
	str	lr, [r4, #20]	@ tmp4710, <variable>.s32FieldOrder
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L183:
	cmp	r2, #1	@ iftmp.487,
	movne	r5, #1	@,
	strne	r5, [fp, #-776]	@, %sfp
	bne	.L184	@,
	subs	r2, r1, #1	@, iftmp.488,
	movne	r2, #1	@
	str	r2, [fp, #-776]	@, %sfp
	b	.L184	@
.L396:
	ldr	r2, [fp, #-688]	@ tmp4856,
	rsbs	r1, r2, #1	@ iftmp.484, tmp4856
	movcc	r1, #0	@ iftmp.484
	b	.L170	@
.L243:
	mov	r8, #0	@ prephitmp.1043,
.L244:
	ldr	r5, [fp, #-724]	@ tmp2891,
	cmp	r5, #0	@ tmp2891,
	bne	.L397	@,
.L246:
	ldr	r7, [fp, #-720]	@ tmp2954,
	cmp	r7, #0	@ tmp2954,
	bne	.L256	@,
.L368:
	mov	r2, r7	@ Pld32Info$Pd32Det, tmp2974
	mov	r6, r7	@ Pld32Info$Pd32Det.1144, Pld32Info$Pd32Det
.L257:
	ldrb	lr, [r4, #429]	@ zero_extendqisi2	@ D.38456, <variable>.stFmdCtx.MainState
	ldrb	r7, [r4, #430]	@ zero_extendqisi2	@ D.38457, <variable>.stFmdCtx.PrevMainState
	sxtb	ip, lr	@ D.38456, D.38456
	cmp	ip, #1	@ D.38456,
	beq	.L331	@,
	cmp	ip, #2	@ D.38456,
	beq	.L398	@,
	cmp	r6, #1	@ Pld32Info$Pd32Det.1144,
	beq	.L340	@,
	cmp	r5, #1	@ IsProgressive,
	beq	.L341	@,
	ldr	r3, [fp, #-884]	@, %sfp
	sub	r6, fp, #68	@,,
	str	r2, [fp, #-56]	@ Pld32Info$Pd32Det, Pld32Info.Pd32Det
	movw	r5, #:lower16:.LANCHOR1	@ tmp4852,
	str	r6, [fp, #-888]	@, %sfp
	movt	r5, #:upper16:.LANCHOR1	@ tmp4852,
	ldmia	r3, {r0, r1, r2}	@,,,
	ldr	sl, [fp, #-740]	@,
	ldr	r6, [fp, #-888]	@, %sfp
	add	r3, r5, #124	@ tmp4633, tmp4852,
	sub	r9, fp, #164	@,,
	str	r9, [fp, #-892]	@, %sfp
	mov	r9, r2, lsr #16	@,,
	str	sl, [fp, #-800]	@, %sfp
	str	r9, [fp, #-804]	@, %sfp
	cmp	ip, #1	@ D.38456,
	ldrb	sl, [r4, #15]	@ zero_extendqisi2	@,
	stmia	r6!, {r0, r1}	@,,
	strh	r2, [r6, #0]	@ movhi	@, PdInfo
	uxtb	r2, r9	@,
	mov	r9, r3	@, tmp4633
	str	r2, [fp, #-756]	@, %sfp
	ldmia	r9!, {r0, r1, r2, r3}	@,,,,
	str	sl, [fp, #-764]	@, %sfp
	str	r9, [fp, #-772]	@, %sfp
	ldrb	sl, [r4, #27]	@ zero_extendqisi2	@,
	str	sl, [fp, #-788]	@, %sfp
	ldrb	r6, [r4, #14]	@ zero_extendqisi2	@,
	str	r6, [fp, #-776]	@, %sfp
	mov	r6, ip	@ PbState, D.38456
	ldrb	r9, [r4, #16]	@ zero_extendqisi2	@,
	str	r9, [fp, #-768]	@, %sfp
	ldrb	sl, [r4, #26]	@ zero_extendqisi2	@,
	ldr	r9, [fp, #-764]	@, %sfp
	str	sl, [fp, #-780]	@, %sfp
	ldr	sl, [fp, #-776]	@, %sfp
	orr	sl, sl, r9, asl #8	@,,,,
	ldr	r9, [fp, #-892]	@, %sfp
	str	sl, [fp, #-764]	@, %sfp
	stmia	r9!, {r0, r1, r2, r3}	@,,,,
	ldr	sl, [fp, #-772]	@, %sfp
	str	r9, [fp, #-776]	@, %sfp
	ldrb	r0, [r4, #28]	@ zero_extendqisi2	@,
	str	r0, [fp, #-792]	@, %sfp
	ldmia	sl!, {r0, r1, r2, r3}	@,,,,
	str	sl, [fp, #-772]	@, %sfp
	ldrb	r9, [r4, #17]	@ zero_extendqisi2	@,
	str	r9, [fp, #-784]	@, %sfp
	ldrb	sl, [r4, #29]	@ zero_extendqisi2	@,
	ldr	r9, [fp, #-788]	@, %sfp
	str	sl, [fp, #-796]	@, %sfp
	ldr	sl, [fp, #-780]	@, %sfp
	orr	sl, sl, r9, asl #8	@,,,,
	str	sl, [fp, #-780]	@, %sfp
	strb	lr, [r4, #429]	@ D.38456, <variable>.stFmdCtx.MainState
	ldr	r9, [fp, #-768]	@, %sfp
	ldr	sl, [fp, #-764]	@, %sfp
	strb	r7, [r4, #430]	@ D.38457, <variable>.stFmdCtx.PrevMainState
	ldr	r7, [fp, #-792]	@, %sfp
	orr	lr, sl, r9, asl #16	@, tmp4613,,,
	ldr	sl, [fp, #-780]	@, %sfp
	orr	r9, sl, r7, asl #16	@, tmp4623,,,
	ldr	r7, [fp, #-804]	@, %sfp
	ldr	sl, [fp, #-784]	@, %sfp
	strb	r7, [fp, #-58]	@, PdInfo
	ldr	r7, [fp, #-776]	@ tmp4883, %sfp
	orr	lr, lr, sl, asl #24	@, tmp4616, tmp4613,,
	ldr	sl, [fp, #-772]	@, %sfp
	stmia	r7!, {r0, r1, r2, r3}	@ tmp4883,,,,
	ldr	r3, [fp, #-796]	@, %sfp
	ldmia	sl, {r0, r1}	@,,
	orr	r2, r9, r3, asl #24	@, tmp4626, tmp4623,,
	mov	r3, lr	@ D.38490, tmp4616
	stmia	r7, {r0, r1}	@ tmp4883,,
	mov	r1, r2	@ temp.1119, tmp4626
	beq	.L344	@,
	cmp	ip, #2	@ D.38456,
	beq	.L345	@,
	cmp	ip, #0	@ D.38456,
	bne	.L364	@,
.L343:
	tst	r1, #1	@ temp.1119,
	mov	r2, #0	@ tmp4635,
	str	r2, [fp, #-88]	@ tmp4635, stFmdRtlOutPara.DieOutSelChr
	str	r2, [fp, #-92]	@ tmp4635, stFmdRtlOutPara.DieOutSelLum
	beq	.L371	@,
	cmp	r3, r2	@ D.38490,
	movne	r5, #0	@, tmp4638
	moveq	r5, #1	@, tmp4638
	str	r5, [fp, #-96]	@ tmp4638, stFmdRtlOutPara.DirMch
.L350:
	ldr	r5, [fp, #-752]	@, %sfp
	mov	r1, #0	@ tmp4676,
	str	r8, [fp, #-80]	@ prephitmp.1043, stFmdRtlOutPara.SceneChange
	str	r1, [fp, #-84]	@ tmp4676, stFmdRtlOutPara.EdgeSmoothEn
	str	r5, [fp, #-76]	@, stFmdRtlOutPara.s32FieldOrder
.L356:
	cmp	r6, #1	@ PbState,
	mvnne	r0, #0	@ s32FilmType.1125,
	beq	.L399	@,
.L358:
	ldr	r1, [fp, #-728]	@ tmp4696,
	ldrb	lr, [r4, #8]	@ zero_extendqisi2	@ <variable>.stBtMode.g_curbtmode, <variable>.stBtMode.g_curbtmode
	ldrb	r3, [r4, #9]	@ zero_extendqisi2	@ <variable>.stBtMode.g_nxtbtmode, <variable>.stBtMode.g_nxtbtmode
	cmp	r1, #1	@ tmp4696,
	str	r0, [fp, #-72]	@ s32FilmType.1125, stFmdRtlOutPara.s32FilmType
	strb	lr, [r4, #7]	@ <variable>.stBtMode.g_curbtmode, <variable>.stBtMode.g_lstbtmode
	strb	r3, [r4, #8]	@ <variable>.stBtMode.g_nxtbtmode, <variable>.stBtMode.g_curbtmode
	bne	.L359	@,
	ldr	r0, [fp, #-76]	@ D.38380,
	cmp	r0, #2	@ D.38380,
	strneb	r0, [r4, #9]	@ D.38380, <variable>.stBtMode.g_nxtbtmode
.L359:
	mov	r2, #28	@,
	sub	r1, fp, #96	@,,
	add	r0, r4, #460	@, pstFmdSoftInfo,
	bl	memcpy	@
	ldrb	r2, [r4, #5]	@ zero_extendqisi2	@ <variable>.stRefFld.g_curreffld, <variable>.stRefFld.g_curreffld
	ldrb	r3, [r4, #6]	@ zero_extendqisi2	@ <variable>.stRefFld.g_nxtreffld, <variable>.stRefFld.g_nxtreffld
	strb	r2, [r4, #4]	@ <variable>.stRefFld.g_curreffld, <variable>.stRefFld.g_lstreffld
	strb	r3, [r4, #5]	@ <variable>.stRefFld.g_nxtreffld, <variable>.stRefFld.g_curreffld
	ldr	ip, [fp, #-684]	@ tmp4706,
	strb	ip, [r4, #6]	@ tmp4706, <variable>.stRefFld.g_nxtreffld
	b	.L163	@
.L377:
	sub	r5, fp, #124	@ tmp456,,
	add	r1, r4, #460	@, pstFmdSoftInfo,
	mov	r2, #28	@,
	mov	r0, r5	@, tmp456
	bl	memcpy	@
	mov	ip, r5	@ tmp461, tmp456
	ldmia	ip!, {r0, r1, r2, r3}	@ tmp461,,,,
	ldr	r4, [fp, #-880]	@, %sfp
	stmia	r4!, {r0, r1, r2, r3}	@,,,,
	ldmia	ip, {r0, r1, r2}	@ tmp461,,,
	stmia	r4, {r0, r1, r2}	@ tmp460,,,
	b	.L163	@
.L397:
	ldr	r7, [fp, #-772]	@, %sfp
	ldr	ip, [r7, #4]	@ sg_u32IPDetect, sg_u32IPDetect
	cmp	ip, #1	@ sg_u32IPDetect,
	beq	.L400	@,
	ldr	lr, [fp, #-672]	@ tmp2923,
	cmp	lr, #1	@ tmp2923,
	beq	.L401	@,
.L253:
	ldr	r9, [fp, #-868]	@, %sfp
	cmp	r9, #288	@,
	bgt	.L254	@,
.L374:
	ldr	r3, [fp, #-676]	@ tmp2927,
.L373:
	cmp	r3, #1	@ tmp2927,
	beq	.L251	@,
.L254:
	ldrb	r2, [r4, #433]	@ zero_extendqisi2	@ tmp2929,
	ldrb	r5, [r4, #432]	@ zero_extendqisi2	@ tmp2928,
	ldrb	r7, [r4, #434]	@ zero_extendqisi2	@ tmp2932,
	orr	ip, r5, r2, asl #8	@, tmp2931, tmp2928, tmp2929,
	ldrb	r0, [r4, #435]	@ zero_extendqisi2	@ tmp2935,
	orr	r3, ip, r7, asl #16	@, tmp2934, tmp2931, tmp2932,
	orrs	r2, r3, r0, asl #24	@,, tmp2934, tmp2935,
	beq	.L402	@,
	ldrb	r1, [r4, #236]	@ zero_extendqisi2	@ tmp2945,
	ldrb	r3, [r4, #235]	@ zero_extendqisi2	@ tmp2944,
	ldrb	ip, [r4, #237]	@ zero_extendqisi2	@ tmp2948,
	ldrb	r6, [r4, #238]	@ zero_extendqisi2	@ tmp2951,
	orr	r0, r3, r1, asl #8	@, tmp2947, tmp2944, tmp2945,
	orr	r3, r0, ip, asl #16	@, tmp2950, tmp2947, tmp2948,
	orr	r5, r3, r6, asl #24	@, IsProgressive, tmp2950, tmp2951,
	b	.L246	@
.L378:
	ldrb	r1, [r4, #336]	@ zero_extendqisi2	@ tmp1705,
	ldrb	r0, [r4, #335]	@ zero_extendqisi2	@ tmp1704,
	orr	r2, r0, r1, asl #8	@, tmp1708, tmp1704, tmp1705,
	cmp	r3, r2	@ D.38510, tmp1708
	movle	r0, #0	@, stillBlkCnt
	movgt	r0, #1	@, stillBlkCnt
	b	.L189	@
.L393:
	ldrb	r1, [r4, #426]	@ zero_extendqisi2	@ tmp2232,
	ldrb	r2, [r4, #425]	@ zero_extendqisi2	@ tmp2231,
	orr	r2, r2, r1, asl #8	@, tmp2235, tmp2231, tmp2232,
	cmp	r3, r2	@ D.38510, tmp2235
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L204	@
.L392:
	ldrb	r1, [r4, #420]	@ zero_extendqisi2	@ tmp2197,
	ldrb	r2, [r4, #419]	@ zero_extendqisi2	@ tmp2196,
	orr	r2, r2, r1, asl #8	@, tmp2200, tmp2196, tmp2197,
	cmp	r3, r2	@ D.38510, tmp2200
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L203	@
.L391:
	ldrb	r1, [r4, #414]	@ zero_extendqisi2	@ tmp2162,
	ldrb	r2, [r4, #413]	@ zero_extendqisi2	@ tmp2161,
	orr	r2, r2, r1, asl #8	@, tmp2165, tmp2161, tmp2162,
	cmp	r3, r2	@ D.38510, tmp2165
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L202	@
.L390:
	ldrb	r1, [r4, #408]	@ zero_extendqisi2	@ tmp2127,
	ldrb	r2, [r4, #407]	@ zero_extendqisi2	@ tmp2126,
	orr	r2, r2, r1, asl #8	@, tmp2130, tmp2126, tmp2127,
	cmp	r3, r2	@ D.38510, tmp2130
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L201	@
.L389:
	ldrb	r1, [r4, #402]	@ zero_extendqisi2	@ tmp2092,
	ldrb	r2, [r4, #401]	@ zero_extendqisi2	@ tmp2091,
	orr	r2, r2, r1, asl #8	@, tmp2095, tmp2091, tmp2092,
	cmp	r3, r2	@ D.38510, tmp2095
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L200	@
.L388:
	ldrb	r1, [r4, #396]	@ zero_extendqisi2	@ tmp2057,
	ldrb	r2, [r4, #395]	@ zero_extendqisi2	@ tmp2056,
	orr	r2, r2, r1, asl #8	@, tmp2060, tmp2056, tmp2057,
	cmp	r3, r2	@ D.38510, tmp2060
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L199	@
.L387:
	ldrb	r1, [r4, #390]	@ zero_extendqisi2	@ tmp2022,
	ldrb	r2, [r4, #389]	@ zero_extendqisi2	@ tmp2021,
	orr	r2, r2, r1, asl #8	@, tmp2025, tmp2021, tmp2022,
	cmp	r3, r2	@ D.38510, tmp2025
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L198	@
.L386:
	ldrb	r1, [r4, #384]	@ zero_extendqisi2	@ tmp1987,
	ldrb	r2, [r4, #383]	@ zero_extendqisi2	@ tmp1986,
	orr	r2, r2, r1, asl #8	@, tmp1990, tmp1986, tmp1987,
	cmp	r3, r2	@ D.38510, tmp1990
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L197	@
.L385:
	ldrb	r1, [r4, #378]	@ zero_extendqisi2	@ tmp1952,
	ldrb	r2, [r4, #377]	@ zero_extendqisi2	@ tmp1951,
	orr	r2, r2, r1, asl #8	@, tmp1955, tmp1951, tmp1952,
	cmp	r3, r2	@ D.38510, tmp1955
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L196	@
.L384:
	ldrb	r1, [r4, #372]	@ zero_extendqisi2	@ tmp1917,
	ldrb	r2, [r4, #371]	@ zero_extendqisi2	@ tmp1916,
	orr	r2, r2, r1, asl #8	@, tmp1920, tmp1916, tmp1917,
	cmp	r3, r2	@ D.38510, tmp1920
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L195	@
.L383:
	ldrb	r1, [r4, #366]	@ zero_extendqisi2	@ tmp1882,
	ldrb	r2, [r4, #365]	@ zero_extendqisi2	@ tmp1881,
	orr	r2, r2, r1, asl #8	@, tmp1885, tmp1881, tmp1882,
	cmp	r3, r2	@ D.38510, tmp1885
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L194	@
.L382:
	ldrb	r1, [r4, #360]	@ zero_extendqisi2	@ tmp1847,
	ldrb	r2, [r4, #359]	@ zero_extendqisi2	@ tmp1846,
	orr	r2, r2, r1, asl #8	@, tmp1850, tmp1846, tmp1847,
	cmp	r3, r2	@ D.38510, tmp1850
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L193	@
.L381:
	ldrb	r1, [r4, #354]	@ zero_extendqisi2	@ tmp1812,
	ldrb	r2, [r4, #353]	@ zero_extendqisi2	@ tmp1811,
	orr	r2, r2, r1, asl #8	@, tmp1815, tmp1811, tmp1812,
	cmp	r3, r2	@ D.38510, tmp1815
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L192	@
.L380:
	ldrb	r1, [r4, #348]	@ zero_extendqisi2	@ tmp1777,
	ldrb	r2, [r4, #347]	@ zero_extendqisi2	@ tmp1776,
	orr	r2, r2, r1, asl #8	@, tmp1780, tmp1776, tmp1777,
	cmp	r3, r2	@ D.38510, tmp1780
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L191	@
.L379:
	ldrb	r1, [r4, #342]	@ zero_extendqisi2	@ tmp1742,
	ldrb	r2, [r4, #341]	@ zero_extendqisi2	@ tmp1741,
	orr	r2, r2, r1, asl #8	@, tmp1745, tmp1741, tmp1742,
	cmp	r3, r2	@ D.38510, tmp1745
	addgt	r0, r0, #1	@ stillBlkCnt, stillBlkCnt,
	b	.L190	@
.L398:
	cmp	r5, #1	@ IsProgressive,
	beq	.L337	@,
	cmp	r6, #1	@ Pld32Info$Pd32Det.1144,
	moveq	r3, ip	@ prephitmp.1152, D.38456
	beq	.L339	@,
.L335:
	ldrb	lr, [r4, #15]	@ zero_extendqisi2	@ tmp4766,
	mov	r2, #0	@ tmp4762,
	ldrb	r0, [r4, #27]	@ zero_extendqisi2	@ tmp4776,
	mov	r6, r2	@ PbState, tmp4762
	ldrb	r5, [r4, #14]	@ zero_extendqisi2	@ tmp4765,
	ldrb	r1, [r4, #26]	@ zero_extendqisi2	@ tmp4775,
	orr	r3, r5, lr, asl #8	@, tmp4768, tmp4765, tmp4766,
	ldrb	r7, [r4, #16]	@ zero_extendqisi2	@ tmp4769,
	ldrb	r5, [r4, #28]	@ zero_extendqisi2	@ tmp4779,
	orr	r1, r1, r0, asl #8	@, tmp4778, tmp4775, tmp4776,
	ldrb	lr, [r4, #17]	@ zero_extendqisi2	@ tmp4772,
	ldrb	r0, [r4, #29]	@ zero_extendqisi2	@ tmp4782,
	orr	r3, r3, r7, asl #16	@, tmp4771, tmp4768, tmp4769,
	orr	r1, r1, r5, asl #16	@, tmp4781, tmp4778, tmp4779,
	strb	ip, [r4, #430]	@ D.38456, <variable>.stFmdCtx.PrevMainState
	orr	r3, r3, lr, asl #24	@, D.38490, tmp4771, tmp4772,
	strb	r2, [r4, #429]	@ tmp4762, <variable>.stFmdCtx.MainState
	orr	r1, r1, r0, asl #24	@, temp.1119, tmp4781, tmp4782,
	b	.L343	@
.L400:
	ldr	r5, [fp, #-672]	@ tmp2894,
	cmp	r5, #1	@ tmp2894,
	bne	.L374	@,
	ldr	r3, [fp, #-676]	@ prephitmp.1051,
	cmp	r3, #0	@ prephitmp.1051,
	bne	.L373	@,
	ldr	r3, [fp, #-668]	@ D.38496,
	movw	r2, #23799	@ tmp2895,
	cmp	r3, r2	@ D.38496, tmp2895
	ble	.L254	@,
	add	r2, r2, #400	@ tmp2896, tmp2896,
	cmp	r3, r2	@ D.38496, tmp2896
	bgt	.L254	@,
.L251:
	mov	r5, #1	@ IsProgressive,
	b	.L246	@
.L331:
	cmp	r6, #1	@ Pld32Info$Pd32Det.1144,
	beq	.L333	@,
	cmp	r5, #1	@ IsProgressive,
	moveq	lr, r5	@ prephitmp.1153, IsProgressive
	bne	.L335	@,
.L336:
	ldrb	r0, [r4, #15]	@ zero_extendqisi2	@ tmp4733,
	movw	r5, #:lower16:.LANCHOR1	@ tmp4852,
	ldrb	r1, [r4, #27]	@ zero_extendqisi2	@ tmp4743,
	movt	r5, #:upper16:.LANCHOR1	@ tmp4852,
	ldrb	ip, [r4, #14]	@ zero_extendqisi2	@ tmp4732,
	ldrb	r2, [r4, #26]	@ zero_extendqisi2	@ tmp4742,
	orr	r3, ip, r0, asl #8	@, tmp4735, tmp4732, tmp4733,
	ldrb	r6, [r4, #16]	@ zero_extendqisi2	@ tmp4736,
	ldrb	ip, [r4, #28]	@ zero_extendqisi2	@ tmp4746,
	orr	r2, r2, r1, asl #8	@, tmp4745, tmp4742, tmp4743,
	ldrb	r0, [r4, #17]	@ zero_extendqisi2	@ tmp4739,
	ldrb	r1, [r4, #29]	@ zero_extendqisi2	@ tmp4749,
	orr	r3, r3, r6, asl #16	@, tmp4738, tmp4735, tmp4736,
	orr	r2, r2, ip, asl #16	@, tmp4748, tmp4745, tmp4746,
	strb	lr, [r4, #430]	@ prephitmp.1153, <variable>.stFmdCtx.PrevMainState
	orr	r3, r3, r0, asl #24	@, D.38490, tmp4738, tmp4739,
	mov	ip, #2	@ tmp4729,
	orr	r1, r2, r1, asl #24	@, temp.1119, tmp4748, tmp4749,
	strb	ip, [r4, #429]	@ tmp4729, <variable>.stFmdCtx.MainState
.L345:
	tst	r1, #1	@ temp.1119,
	mov	r2, #1	@ tmp4677,
	streq	r3, [fp, #-96]	@ D.38490, stFmdRtlOutPara.DirMch
	str	r2, [fp, #-88]	@ tmp4677, stFmdRtlOutPara.DieOutSelChr
	str	r2, [fp, #-92]	@ tmp4677, stFmdRtlOutPara.DieOutSelLum
	beq	.L352	@,
	rsbs	r0, r3, #1	@ tmp4680, D.38490
	movcc	r0, #0	@ tmp4680
	str	r0, [fp, #-96]	@ tmp4680, stFmdRtlOutPara.DirMch
.L352:
	ldr	r3, [fp, #-752]	@, %sfp
	mov	ip, #1	@ tmp4681,
	mov	r2, ip	@ s32FilmType, tmp4681
	str	r8, [fp, #-80]	@ prephitmp.1043, stFmdRtlOutPara.SceneChange
	str	ip, [fp, #-84]	@ tmp4681, stFmdRtlOutPara.EdgeSmoothEn
	str	r3, [fp, #-76]	@, stFmdRtlOutPara.s32FieldOrder
.L353:
	add	r2, r5, r2, asl #2	@, tmp4690, tmp4852, s32FilmType,
	ldr	r0, [r2, #164]	@ s32FilmType.1125, g_u32PDTypeNum
	b	.L358	@
.L256:
	ldrb	r2, [r4, #433]	@ zero_extendqisi2	@ tmp2966,
	ldrb	r0, [r4, #432]	@ zero_extendqisi2	@ tmp2965,
	ldrb	sl, [r4, #434]	@ zero_extendqisi2	@ tmp2969,
	orr	r3, r0, r2, asl #8	@, tmp2968, tmp2965, tmp2966,
	ldrb	r7, [r4, #435]	@ zero_extendqisi2	@ tmp2972,
	ldrb	r0, [r4, #27]	@ zero_extendqisi2	@ tmp2956,
	orr	ip, r3, sl, asl #16	@, tmp2971, tmp2968, tmp2969,
	ldrb	r1, [r4, #26]	@ zero_extendqisi2	@ tmp2955,
	ldrb	lr, [r4, #28]	@ zero_extendqisi2	@ tmp2959,
	ldrb	r2, [r4, #29]	@ zero_extendqisi2	@ tmp2962,
	orr	r6, r1, r0, asl #8	@, tmp2958, tmp2955, tmp2956,
	orrs	r7, ip, r7, asl #24	@, tmp2974, tmp2971, tmp2972,
	ldr	r3, [fp, #-540]	@ D.38619,
	orr	sl, r6, lr, asl #16	@, tmp2961, tmp2958, tmp2959,
	ldr	r1, [fp, #-532]	@ D.38618,
	orr	sl, sl, r2, asl #24	@, D.38491, tmp2961, tmp2962,
	ldr	r2, [fp, #-536]	@ D.38616,
	bne	.L258	@,
	ldrb	ip, [r4, #445]	@ zero_extendqisi2	@ tmp2976,
	ldrb	lr, [r4, #446]	@ zero_extendqisi2	@ tmp2979,
	ldrb	r0, [r4, #444]	@ zero_extendqisi2	@ tmp2975,
	ldrb	r6, [r4, #447]	@ zero_extendqisi2	@ tmp2982,
	orr	r0, r0, ip, asl #8	@, tmp2978, tmp2975, tmp2976,
	orr	ip, r0, lr, asl #16	@, tmp2981, tmp2978, tmp2979,
	orr	lr, ip, r6, asl #24	@, tmp2984, tmp2981, tmp2982,
	cmp	lr, #1	@ tmp2984,
	ble	.L259	@,
	add	r6, r4, #106	@ tmp2985, pstFmdSoftInfo,
	mov	r1, #55	@,
	mov	r0, r6	@, tmp2985
	bl	__memzero	@
	mov	r1, r6	@, tmp2985
	sub	r0, fp, #56	@,,
	mov	r2, #11	@,
	bl	memcpy	@
	add	r0, r4, #172	@, pstFmdSoftInfo,
	mov	r1, #20	@,
	bl	__memzero	@
	b	.L368	@
.L394:
	ldrb	r2, [r4, #433]	@ zero_extendqisi2	@ tmp2257,
	ldrb	ip, [r4, #432]	@ zero_extendqisi2	@ tmp2256,
	ldrb	r1, [r4, #434]	@ zero_extendqisi2	@ tmp2260,
	orr	r3, ip, r2, asl #8	@, tmp2259, tmp2256, tmp2257,
	ldrb	sl, [r4, #435]	@ zero_extendqisi2	@ tmp2263,
	orr	ip, r3, r1, asl #16	@, tmp2262, tmp2259, tmp2260,
	orrs	r3, ip, sl, asl #24	@, tmp2265, tmp2262, tmp2263,
	bne	.L206	@,
	ldr	r2, [fp, #-740]	@ D.38587,
	cmp	r2, #2	@ D.38587,
	beq	.L403	@,
	cmp	r2, #1	@ D.38587,
	beq	.L404	@,
.L209:
	ldrb	r2, [r4, #11]	@ zero_extendqisi2	@ tmp2325,
	ldrb	ip, [r4, #10]	@ zero_extendqisi2	@ tmp2324,
	ldrb	r1, [r4, #12]	@ zero_extendqisi2	@ tmp2328,
	orr	sl, ip, r2, asl #8	@, tmp2327, tmp2324, tmp2325,
	ldrb	r2, [r4, #13]	@ zero_extendqisi2	@ tmp2331,
	orr	r3, sl, r1, asl #16	@, tmp2330, tmp2327, tmp2328,
	orrs	r2, r3, r2, asl #24	@,, tmp2330, tmp2331,
	beq	.L365	@,
	ldrb	ip, [r4, #19]	@ zero_extendqisi2	@ tmp2345,
	ldrb	r1, [r4, #20]	@ zero_extendqisi2	@ tmp2348,
	ldrb	r2, [r4, #18]	@ zero_extendqisi2	@ tmp2344,
	ldrb	sl, [r4, #21]	@ zero_extendqisi2	@ tmp2351,
	orr	r3, r2, ip, asl #8	@, tmp2347, tmp2344, tmp2345,
	orr	r2, r3, r1, asl #16	@, tmp2350, tmp2347, tmp2348,
	orr	ip, r2, sl, asl #24	@, tmp2353, tmp2350, tmp2351,
	cmp	ip, #1	@ tmp2353,
	ldr	ip, [fp, #-520]	@ z34,
	ldreq	r6, [fp, #-528]	@ z32,
	ldrne	r6, [fp, #-524]	@ z32,
	ldreq	r5, [fp, #-524]	@ z14,
	ldrne	r5, [fp, #-528]	@ z14,
	cmp	r6, ip	@ z32, z34
	movge	r3, r6	@ biggerintwo, z32
	movlt	r3, ip	@ biggerintwo, z34
	cmp	r3, #254	@ biggerintwo,
	movgt	r1, r3, asr #31	@ tmp2357, biggerintwo,
	movwgt	sl, #:lower16:1717986919	@ tmp2355,
	movtgt	sl, #:upper16:1717986919	@ tmp2355,
	movle	sl, #50	@ iftmp.430,
	smullgt	lr, sl, sl, r3	@, tmp2354, tmp2355, biggerintwo
	rsbgt	sl, r1, sl, asr #1	@, iftmp.430, tmp2357, tmp2354,
	add	r2, sl, r3	@ tmp2358, iftmp.430, biggerintwo
	cmp	r5, ip	@ z14, z34
	movge	sl, r5	@ biggerintwo.1128, z14
	movlt	sl, ip	@ biggerintwo.1128, z34
	cmp	r2, r5	@ tmp2358, z14
	movge	r2, #0	@,
	movlt	r2, #1	@,
	cmp	sl, #254	@ biggerintwo.1128,
	str	r2, [fp, #-756]	@, %sfp
	movgt	r1, sl, asr #31	@ tmp2363, biggerintwo.1128,
	movwgt	r2, #:lower16:1717986919	@ tmp2361,
	movtgt	r2, #:upper16:1717986919	@ tmp2361,
	movle	r2, #50	@ iftmp.431,
	smullgt	r7, r2, r2, sl	@, tmp2360, tmp2361, biggerintwo.1128
	rsbgt	r2, r1, r2, asr #1	@, iftmp.431, tmp2363, tmp2360,
	cmp	r5, r6	@ z14, z32
	movge	r1, r5	@ biggerintwo.1129, z14
	movlt	r1, r6	@ biggerintwo.1129, z32
	add	r3, r2, sl	@ tmp2364, iftmp.431, biggerintwo.1128
	cmp	r6, r3	@ z32, tmp2364
	movle	sl, #0	@,
	movgt	sl, #1	@,
	cmp	r1, #254	@ biggerintwo.1129,
	str	sl, [fp, #-752]	@, %sfp
	movgt	r2, r1, asr #31	@ tmp2369, biggerintwo.1129,
	movwgt	sl, #:lower16:1717986919	@ tmp2367,
	movtgt	sl, #:upper16:1717986919	@ tmp2367,
	movle	sl, #50	@ iftmp.432,
	smullgt	r8, sl, sl, r1	@, tmp2366, tmp2367, biggerintwo.1129
	rsbgt	sl, r2, sl, asr #1	@, iftmp.432, tmp2369, tmp2366,
	cmp	r6, ip	@ z32, z34
	movlt	r2, r6	@ smallerintwo, z32
	movge	r2, ip	@ smallerintwo, z34
	add	r3, sl, r1	@ tmp2370, iftmp.432, biggerintwo.1129
	cmp	ip, r3	@ z34, tmp2370
	movle	sl, #0	@,
	movgt	sl, #1	@,
	cmp	r2, #254	@ smallerintwo,
	str	sl, [fp, #-764]	@, %sfp
	movgt	lr, r2, asr #31	@ tmp2375, smallerintwo,
	movwgt	sl, #:lower16:1717986919	@ tmp2373,
	movtgt	sl, #:upper16:1717986919	@ tmp2373,
	movle	sl, #50	@ iftmp.433,
	smullgt	r9, sl, sl, r2	@, tmp2372, tmp2373, smallerintwo
	ldr	r9, [fp, #-872]	@, %sfp
	rsbgt	sl, lr, sl, asr #1	@, iftmp.433, tmp2375, tmp2372,
	rsb	r3, sl, r2	@ tmp2376, iftmp.433, smallerintwo
	cmp	r5, ip	@ z14, z34
	movlt	r2, r5	@ smallerintwo.1130, z14
	movge	r2, ip	@ smallerintwo.1130, z34
	cmp	r5, r3	@ z14, tmp2376
	movge	sl, #0	@, islasi14smallest
	movlt	sl, #1	@, islasi14smallest
	cmp	r2, #254	@ smallerintwo.1130,
	movgt	lr, r2, asr #31	@ tmp2381, smallerintwo.1130,
	movwgt	r3, #:lower16:1717986919	@ tmp2379,
	movtgt	r3, #:upper16:1717986919	@ tmp2379,
	movle	r3, #50	@ iftmp.434,
	smullgt	r7, r3, r3, r2	@, tmp2378, tmp2379, smallerintwo.1130
	rsbgt	r3, lr, r3, asr #1	@, iftmp.434, tmp2381, tmp2378,
	rsb	r3, r3, r2	@ tmp2382, iftmp.434, smallerintwo.1130
	cmp	r5, r6	@ z14, z32
	movlt	r2, r5	@ smallerintwo.1131, z14
	movge	r2, r6	@ smallerintwo.1131, z32
	cmp	r6, r3	@ z32, tmp2382
	movge	r7, #0	@, islasi32smallest
	movlt	r7, #1	@, islasi32smallest
	cmp	r2, #254	@ smallerintwo.1131,
	movgt	lr, r2, asr #31	@ tmp2387, smallerintwo.1131,
	movwgt	r3, #:lower16:1717986919	@ tmp2385,
	movtgt	r3, #:upper16:1717986919	@ tmp2385,
	movle	r3, #50	@ iftmp.435,
	smullgt	r8, r3, r3, r2	@, tmp2384, tmp2385, smallerintwo.1131
	ldr	r8, [fp, #-868]	@, %sfp
	rsbgt	r3, lr, r3, asr #1	@, iftmp.435, tmp2387, tmp2384,
	mul	lr, r9, r8	@ tmp2391,,
	rsb	r9, r0, #16	@ tmp2390, stillBlkCnt,
	rsb	r0, r3, r2	@ tmp2388, iftmp.435, smallerintwo.1131
	cmp	ip, r0	@ z34, tmp2388
	movge	r8, #0	@, islasi34smallest
	movlt	r8, #1	@, islasi34smallest
	mov	r3, lr, asr #9	@ tmp2392, tmp2391,
	add	ip, r3, #31	@ tmp2395, tmp2392,
	cmp	r3, #0	@ tmp2392,
	movlt	r3, ip	@ tmp2394, tmp2395
	mov	r0, r3, asr #5	@ tmp2396, tmp2394,
	mul	ip, r0, r9	@ tmp2397, tmp2396, tmp2390
	cmp	ip, #0	@ tmp2397,
	add	lr, ip, #15	@ tmp2400, tmp2397,
	movlt	ip, lr	@ tmp2399, tmp2400
	mov	r3, ip, asr #4	@ tmp2401, tmp2399,
	add	r0, r3, r3, asl #1	@, tmp2404, tmp2401, tmp2401,
	add	r9, r0, r0, lsr #31	@, tmp2406, tmp2404, tmp2404,
	mov	lr, r9, asr #1	@ zthr.1132, tmp2406,
	cmp	lr, #6	@ zthr.1132,
	movge	r9, lr	@ zthr.1132, zthr.1132
	movlt	r9, #6	@ zthr.1132,
	cmp	r1, #100	@ biggerintwo.1129,
	ble	.L228	@,
	rsb	r3, r2, r1	@ tmp2408, smallerintwo.1131, biggerintwo.1129
	mov	lr, #100	@ tmp2410,
	mul	r0, lr, r3	@, tmp2410, tmp2408
	bl	__aeabi_idiv	@
	cmp	r0, #19	@,
	ble	.L229	@,
.L228:
	rsb	r0, r6, r5	@, z32, z14
	mov	r1, r9	@, zthr.1132
	bl	__aeabi_idiv	@
	add	r3, r0, #49	@ tmp2419, tmp2418,
	cmp	r3, #98	@ tmp2419,
	bls	.L229	@,
	cmp	r0, #500	@ tmp2418,
	movgt	r3, #500	@ fac.1133,
	ble	.L405	@,
.L231:
	ldr	r0, [fp, #-756]	@, %sfp
	eor	r5, r7, #1	@ tmp2422, islasi32smallest,
	uxtb	r2, r0	@ D.38561,
	tst	r2, r5	@ D.38561, tmp2422
	beq	.L232	@,
	cmp	r3, #50	@ fac.1133,
	movlt	r3, #50	@ fac.1133,
.L233:
	cmp	r8, #0	@ islasi34smallest,
	bne	.L234	@,
	ldr	lr, [fp, #-764]	@, %sfp
	cmp	lr, #0	@,
	bne	.L235	@,
	tst	r2, r7	@ D.38561, islasi32smallest
	bne	.L234	@,
	ldr	r2, [fp, #-752]	@, %sfp
	tst	sl, r2	@ islasi14smallest,
	bne	.L234	@,
	orrs	r1, r7, sl	@, islasi32smallest, islasi14smallest
	bne	.L235	@,
.L234:
	ldr	r9, [fp, #-752]	@, %sfp
	ldr	r1, [fp, #-756]	@, %sfp
	ldr	r5, [fp, #-764]	@, %sfp
	orr	r0, r9, r1	@ tmp2443,,
	orr	r6, r0, r5	@ tmp2444, tmp2443,
	orr	sl, r6, sl	@ tmp2445, tmp2444, islasi14smallest
	orr	r7, sl, r7	@ tmp2446, tmp2445, islasi32smallest
	orrs	r7, r7, r8	@, tmp2446, islasi34smallest
	bne	.L236	@,
	cmp	r3, #50	@ fac.1133,
	movge	r3, #50	@ fac.1136,
	mvn	r8, #49	@ tmp2448,
	cmp	r3, r8	@ fac.1136, tmp2448
	movlt	r3, r8	@ fac.1133, tmp2448
.L236:
	ldrb	r8, [r4, #194]	@ zero_extendqisi2	@ tmp2450,
	mov	r2, #0	@ tmp2462,
	ldrb	r1, [r4, #193]	@ zero_extendqisi2	@ tmp2449,
	ldrb	r9, [r4, #195]	@ zero_extendqisi2	@ tmp2453,
	ldrb	r0, [r4, #196]	@ zero_extendqisi2	@ tmp2456,
	orr	r5, r1, r8, asl #8	@, tmp2452, tmp2449, tmp2450,
	orr	r6, r5, r9, asl #16	@, tmp2455, tmp2452, tmp2453,
	orr	sl, r6, r0, asl #24	@, tmp2458, tmp2455, tmp2456,
	add	r3, r3, sl	@ D.38545, fac.1133, tmp2458
	strb	r3, [r4, #193]	@ D.38545,
	cmp	r3, #1000	@ D.38545,
	ubfx	r7, r3, #8, #8	@ tmp2468, D.38545,,
	ubfx	lr, r3, #16, #8	@ tmp2477, D.38545,,
	mov	ip, r3, lsr #24	@ tmp2485, D.38545,
	strb	r7, [r4, #194]	@ tmp2468,
	strb	lr, [r4, #195]	@ tmp2477,
	strb	ip, [r4, #196]	@ tmp2485,
	ble	.L237	@,
	mvn	ip, #23	@ tmp2498,
	mov	r3, #3	@ tmp2504,
	strb	r2, [r4, #196]	@ tmp2462,
	strb	ip, [r4, #193]	@ tmp2498,
	strb	r3, [r4, #194]	@ tmp2504,
	strb	r2, [r4, #195]	@ tmp2462,
.L238:
	mov	sl, #0	@ tmp2538,
	strb	sl, [r4, #197]	@ tmp2538,
	strb	sl, [r4, #198]	@ tmp2538,
	str	sl, [fp, #-752]	@ tmp2538, %sfp
	strb	sl, [r4, #199]	@ tmp2538,
	strb	sl, [r4, #200]	@ tmp2538,
	b	.L208	@
.L229:
	mov	r3, #0	@ fac.1133,
	b	.L231	@
.L235:
	mov	r3, #0	@ fac.1133,
	b	.L234	@
.L340:
	mov	r3, #0	@ prephitmp.1152,
.L339:
	ldr	r6, [fp, #-884]	@, %sfp
	sub	ip, fp, #68	@ tmp4755,,
	str	r2, [fp, #-56]	@ Pld32Info$Pd32Det, Pld32Info.Pd32Det
	mov	lr, #1	@ tmp4752,
	ldr	r7, [fp, #-740]	@,
	ldmia	r6, {r0, r1, r2}	@,,,
	ldr	r5, .L414	@ tmp4761,
	str	r7, [fp, #-800]	@, %sfp
	sub	r7, fp, #164	@ tmp4760,,
	strb	r3, [r4, #430]	@ prephitmp.1152, <variable>.stFmdCtx.PrevMainState
	mov	r6, lr	@ PbState, tmp4752
	mov	r3, r2, lsr #16	@ tmp4757,,
	strb	r3, [ip, #10]	@ tmp4757, PdInfo
	stmia	ip!, {r0, r1}	@ tmp4755,,
	uxtb	r3, r3	@, tmp4757
	strh	r2, [ip, #0]	@ movhi	@, PdInfo
	str	r3, [fp, #-756]	@, %sfp
	mov	ip, r7	@ tmp4887, tmp4760
	ldmia	r5!, {r0, r1, r2, r3}	@ tmp4886,,,,
	strb	lr, [r4, #429]	@ tmp4752, <variable>.stFmdCtx.MainState
	mov	lr, r5	@ tmp4888, tmp4886
	stmia	ip!, {r0, r1, r2, r3}	@ tmp4887,,,,
.L369:
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp4894,,,,
	stmia	ip!, {r0, r1, r2, r3}	@ tmp4893,,,,
	ldmia	lr, {r0, r1}	@ tmp4894,,
	stmia	ip, {r0, r1}	@ tmp4895,,
.L344:
	ldr	r2, [fp, #-800]	@, %sfp
	mov	lr, #1	@ tmp4640,
	mov	ip, #0	@ tmp4641,
	str	lr, [fp, #-92]	@ tmp4640, stFmdRtlOutPara.DieOutSelLum
	cmp	r2, #0	@,
	str	ip, [fp, #-88]	@ tmp4641, stFmdRtlOutPara.DieOutSelChr
	bne	.L349	@,
	ldr	r7, [fp, #-756]	@, %sfp
	movw	r2, #:lower16:1717986919	@ tmp4646,
	movt	r2, #:upper16:1717986919	@ tmp4646,
	sxtb	r9, r7	@ PdInfo$PdSubState,
	add	sl, r9, #1	@ tmp4643, PdInfo$PdSubState,
	smull	r9, lr, r2, sl	@, tmp4645, tmp4646, tmp4643
	mov	r1, sl, asr #31	@ tmp4648, tmp4643,
	rsb	ip, r1, lr, asr #2	@, tmp4644, tmp4648, tmp4645,
	add	r5, ip, ip, asl #2	@, tmp4651, tmp4644, tmp4644,
	sub	r3, sl, r5, asl #1	@ tmp4653, tmp4643, tmp4651,
	sub	sl, fp, #44	@,,
	add	r9, sl, r3, asl #2	@, tmp4656,, tmp4653,
	ldr	r1, [r9, #-120]	@ tmp4658, MchTab
	str	r1, [fp, #-96]	@ tmp4658, stFmdRtlOutPara.DirMch
	b	.L350	@
.L364:
	tst	r2, #1	@ tmp4626,
	mov	r3, #0	@ tmp4682,
	streq	lr, [fp, #-96]	@ tmp4616, stFmdRtlOutPara.DirMch
	str	r3, [fp, #-88]	@ tmp4682, stFmdRtlOutPara.DieOutSelChr
	str	r3, [fp, #-92]	@ tmp4682, stFmdRtlOutPara.DieOutSelLum
	beq	.L355	@,
	cmp	lr, r3	@ tmp4616,
	movne	lr, #0	@, tmp4685
	moveq	lr, #1	@, tmp4685
	str	lr, [fp, #-96]	@ tmp4685, stFmdRtlOutPara.DirMch
.L355:
	cmp	ip, #2	@ D.38456,
	ldr	ip, [fp, #-752]	@, %sfp
	mov	r1, #0	@ tmp4686,
	str	r8, [fp, #-80]	@ prephitmp.1043, stFmdRtlOutPara.SceneChange
	str	r1, [fp, #-84]	@ tmp4686, stFmdRtlOutPara.EdgeSmoothEn
	moveq	r2, #1	@ s32FilmType,
	str	ip, [fp, #-76]	@, stFmdRtlOutPara.s32FieldOrder
	bne	.L356	@,
	b	.L353	@
.L399:
	movw	r5, #:lower16:.LANCHOR1	@ tmp4852,
	mov	r2, #0	@ s32FilmType,
	movt	r5, #:upper16:.LANCHOR1	@ tmp4852,
	b	.L353	@
.L259:
	ldrb	ip, [r4, #103]	@ zero_extendqisi2	@ tmp3002,
	add	r7, r2, r1, asl #1	@, tmp3012, D.38616, D.38618,
	ldrb	r6, [r4, #102]	@ zero_extendqisi2	@ tmp3001,
	add	r9, r4, #90	@ temp.1141, pstFmdSoftInfo,
	ldrb	lr, [r4, #104]	@ zero_extendqisi2	@ tmp3005,
	add	r3, r3, r7, asl #1	@, tmp3014, D.38619, tmp3012,
	ldrb	r2, [r4, #105]	@ zero_extendqisi2	@ tmp3008,
	orr	r0, r6, ip, asl #8	@, tmp3004, tmp3001, tmp3002,
	mov	ip, r3, asl #1	@ tmp3015, tmp3014,
	ldrb	r3, [r4, #99]	@ zero_extendqisi2	@ tmp2992,
	orr	r7, r0, lr, asl #16	@, tmp3007, tmp3004, tmp3005,
	ldrb	r1, [r4, #98]	@ zero_extendqisi2	@ tmp2991,
	orr	r0, r7, r2, asl #24	@, tmp3010, tmp3007, tmp3008,
	ldrb	r2, [r4, #100]	@ zero_extendqisi2	@ tmp2995,
	ldrb	r7, [r4, #101]	@ zero_extendqisi2	@ tmp2998,
	orr	lr, r1, r3, asl #8	@, tmp2994, tmp2991, tmp2992,
	str	ip, [r0, #0]	@ tmp3015,
	orr	r6, lr, r2, asl #16	@, tmp2997, tmp2994, tmp2995,
	ldrb	r0, [r4, #103]	@ zero_extendqisi2	@ tmp3017,
	ldrb	r1, [r4, #102]	@ zero_extendqisi2	@ tmp3016,
	orr	ip, r6, r7, asl #24	@,, tmp2997, tmp2998,
	str	ip, [fp, #-772]	@, %sfp
	ldrb	lr, [r4, #104]	@ zero_extendqisi2	@ tmp3020,
	orr	r3, r1, r0, asl #8	@, tmp3019, tmp3016, tmp3017,
	ldrb	r6, [r4, #105]	@ zero_extendqisi2	@ tmp3023,
	ldrb	ip, [r4, #95]	@ zero_extendqisi2	@ tmp3061,
	orr	r2, r3, lr, asl #16	@, tmp3022, tmp3019, tmp3020,
	ldrb	r0, [r4, #96]	@ zero_extendqisi2	@ tmp3064,
	ldrb	r1, [r4, #94]	@ zero_extendqisi2	@ tmp3060,
	orr	r7, r2, r6, asl #24	@, tmp3025, tmp3022, tmp3023,
	ldrb	r6, [r4, #97]	@ zero_extendqisi2	@ tmp3067,
	add	r2, r7, #4	@ iftmp.443, tmp3025,
	orr	r1, r1, ip, asl #8	@, tmp3063, tmp3060, tmp3061,
	cmp	r2, r9	@ iftmp.443, temp.1141
	orr	ip, r1, r0, asl #16	@, tmp3066, tmp3063, tmp3064,
	addhi	r2, r4, #30	@ iftmp.443, pstFmdSoftInfo,
	orr	r0, ip, r6, asl #24	@, tmp3069, tmp3066, tmp3067,
	ubfx	r3, r2, #8, #8	@ tmp3035, iftmp.443,,
	add	r1, r0, #1	@ D.38675, tmp3069,
	mov	r7, r2, lsr #24	@ tmp3052, iftmp.443,
	cmp	r1, #4	@ D.38675,
	ubfx	lr, r2, #16, #8	@ tmp3044, iftmp.443,,
	strb	r3, [r4, #103]	@ tmp3035,
	mov	r3, #0	@ tmp3029,
	strb	lr, [r4, #104]	@ tmp3044,
	ubfx	lr, r1, #8, #8	@ tmp3079, D.38675,,
	strb	r7, [r4, #105]	@ tmp3052,
	mov	r7, r1, lsr #24	@ tmp3096, D.38675,
	strb	r2, [r4, #102]	@ iftmp.443,
	ubfx	r2, r1, #16, #8	@ tmp3088, D.38675,,
	strb	r1, [r4, #94]	@ D.38675,
	strb	lr, [r4, #95]	@ tmp3079,
	strb	r2, [r4, #96]	@ tmp3088,
	strb	r7, [r4, #97]	@ tmp3096,
	ble	.L406	@,
	ldr	lr, [fp, #-772]	@, %sfp
	ldr	r7, [lr, #0]	@ MinSad2nd.1139,
	mov	ip, lr	@ pRd.1336,
	add	lr, r4, #30	@ iftmp.446, pstFmdSoftInfo,
	str	r7, [fp, #-164]	@ MinSad2nd.1139, Sads
	ldr	r0, [ip], #4	@ MinSad2nd.1334,
	cmp	r9, ip	@ temp.1141, pRd.1336
	movcc	ip, lr	@ pRd.1336, iftmp.446
	cmp	r7, r0	@ MinSad2nd.1139, MinSad2nd.1334
	movlt	r6, r7	@, MinSad2nd.1139
	movge	r6, r0	@, MinSad2nd.1334
	str	r6, [fp, #-772]	@, %sfp
	cmp	r0, r7	@ MinSad2nd.1334, MinSad2nd.1139
	movlt	r0, r7	@ MinSad2nd.1335, MinSad2nd.1139
	ldr	r2, [ip, #0]	@ tmp3130,* pRd.1336
	str	r2, [fp, #-160]	@ tmp3130, Sads
	add	r2, ip, #4	@ pRd.1340, pRd.1336,
	ldr	r1, [ip, #0]	@ MinSad2nd.1337,* pRd.1336
	cmp	r1, r6	@ MinSad2nd.1337,
	strlt	r1, [fp, #-772]	@ MinSad2nd.1337, %sfp
	movlt	r3, #1	@ MinPos,
	cmp	r0, r1	@ MinSad2nd.1335, MinSad2nd.1337
	movge	ip, r0	@ MinSad2nd.1339, MinSad2nd.1335
	movlt	ip, r1	@ MinSad2nd.1339, MinSad2nd.1337
	cmp	r9, r2	@ temp.1141, pRd.1340
	ldr	r1, [fp, #-772]	@, %sfp
	movcc	r2, lr	@ pRd.1340, iftmp.446
	ldr	r7, [r2, #0]	@ tmp3131,* pRd.1340
	str	r7, [fp, #-156]	@ tmp3131, Sads
	add	r7, r2, #4	@ pRd.1344, pRd.1340,
	ldr	r0, [r2, #0]	@ MinSad2nd.1342,* pRd.1340
	cmp	r1, r0	@, MinSad2nd.1342
	strgt	r0, [fp, #-772]	@ MinSad2nd.1342, %sfp
	movgt	r3, #2	@ MinPos,
	cmp	ip, r0	@ MinSad2nd.1339, MinSad2nd.1342
	movge	r0, ip	@ MinSad2nd.1343, MinSad2nd.1339
	movlt	r0, r0	@ MinSad2nd.1343, MinSad2nd.1342
	cmp	r9, r7	@ temp.1141, pRd.1344
	ldr	ip, [fp, #-772]	@, %sfp
	movcc	r7, lr	@ pRd.1344, iftmp.446
	add	r1, r7, #4	@ pRd.1348, pRd.1344,
	ldr	r6, [r7, #0]	@ tmp3132,* pRd.1344
	str	r6, [fp, #-152]	@ tmp3132, Sads
	ldr	r2, [r7, #0]	@ MinSad2nd.1346,* pRd.1344
	ldr	r7, [fp, #-164]	@ MinSad2nd.1349, Sads
	cmp	ip, r2	@, MinSad2nd.1346
	strgt	r2, [fp, #-772]	@ MinSad2nd.1346, %sfp
	movgt	r3, #3	@ MinPos,
	cmp	r0, r2	@ MinSad2nd.1343, MinSad2nd.1346
	movlt	r0, r2	@ MinSad2nd.1347, MinSad2nd.1346
	cmp	r9, r1	@ temp.1141, pRd.1348
	ldr	r6, [fp, #-772]	@, %sfp
	movcc	r1, lr	@ pRd.1348, iftmp.446
	ldr	ip, [r1, #0]	@ MinSad2nd.1149,* pRd.1348
	str	ip, [fp, #-148]	@ MinSad2nd.1149, Sads
	ldr	r2, [r1, #0]	@ MinSad2nd.1140,* pRd.1348
	cmp	r2, r6	@ MinSad2nd.1140,
	ldr	r6, [fp, #-160]	@ MinSad2nd.1354, Sads
	strlt	r2, [fp, #-772]	@ MinSad2nd.1140, %sfp
	movlt	r3, #4	@ MinPos,
	cmp	r2, r0	@ MinSad2nd.1140, MinSad2nd.1347
	movlt	r2, r0	@ MinSad2nd.1140, MinSad2nd.1347
	cmp	r3, #0	@ MinPos,
	cmpne	r2, r7	@, MinSad2nd.1140, MinSad2nd.1349
	str	r2, [fp, #-776]	@ MinSad2nd.1140, %sfp
	ldrb	r1, [r4, #99]	@ zero_extendqisi2	@,
	mov	r0, #0	@,
	movgt	r2, r7	@, MinSad2nd.1349, MinSad2nd.1349
	cmp	r3, #1	@ MinPos,
	cmpne	r2, r6	@, MinSad2nd.1349, MinSad2nd.1354
	ldr	r7, [fp, #-156]	@, Sads
	str	r1, [fp, #-768]	@, %sfp
	movle	r6, r2	@, MinSad2nd.1354, MinSad2nd.1349
	ldrb	r2, [r4, #98]	@ zero_extendqisi2	@,
	cmp	r3, #2	@ MinPos,
	cmpne	r6, r7	@, MinSad2nd.1354,
	sub	r1, fp, #164	@,,
	str	r2, [fp, #-764]	@, %sfp
	ldrb	r7, [r4, #100]	@ zero_extendqisi2	@,
	ldr	r2, [fp, #-776]	@, %sfp
	str	r7, [fp, #-784]	@, %sfp
	ldr	r7, [fp, #-156]	@, Sads
	movle	r7, r6	@,, MinSad2nd.1354
	str	r7, [fp, #-756]	@, %sfp
	ldrb	r6, [r4, #95]	@ zero_extendqisi2	@,
	str	r6, [fp, #-788]	@, %sfp
	ldr	r6, [fp, #-152]	@, Sads
	cmp	r3, #3	@ MinPos,
	cmpne	r7, r6	@,,
	ldrb	r6, [r4, #101]	@ zero_extendqisi2	@,
	ldr	r7, [fp, #-768]	@, %sfp
	str	r6, [fp, #-780]	@, %sfp
	ldr	r6, [fp, #-764]	@, %sfp
	orr	r6, r6, r7, asl #8	@,,,,
	str	r6, [fp, #-792]	@, %sfp
	ldrb	r6, [r4, #94]	@ zero_extendqisi2	@,
	ldr	r7, [fp, #-756]	@, %sfp
	str	r6, [fp, #-764]	@, %sfp
	ldr	r6, [fp, #-152]	@ MinSad2nd.1364, Sads
	movle	r6, r7	@, MinSad2nd.1364,
	ldrb	r7, [r4, #96]	@ zero_extendqisi2	@,
	cmp	r3, #4	@ MinPos,
	cmpne	ip, r6	@, MinSad2nd.1149, MinSad2nd.1364
	ldr	r3, [fp, #-784]	@, %sfp
	str	r7, [fp, #-756]	@, %sfp
	movlt	r6, ip	@,, MinSad2nd.1149
	ldrb	r7, [r4, #97]	@ zero_extendqisi2	@,
	ldr	ip, [fp, #-624]	@ tmp3259,
	str	r7, [fp, #-768]	@, %sfp
	ldr	r7, [fp, #-792]	@, %sfp
	orr	r7, r7, r3, asl #16	@,,,,
	ldr	r3, [fp, #-788]	@, %sfp
	str	r7, [fp, #-784]	@, %sfp
	ldr	r7, [fp, #-764]	@, %sfp
	orr	r7, r7, r3, asl #8	@,,,,
	ldr	r3, [fp, #-780]	@, %sfp
	str	r7, [fp, #-788]	@, %sfp
	ldr	r7, [fp, #-784]	@, %sfp
	orr	r7, r7, r3, asl #24	@,,,,
	ldr	r3, [fp, #-756]	@, %sfp
	str	r7, [fp, #-764]	@, %sfp
	str	r6, [fp, #-756]	@, %sfp
	ldr	r7, [fp, #-788]	@, %sfp
	ldr	r6, [fp, #-768]	@, %sfp
	orr	r7, r7, r3, asl #16	@,,,,
	ldr	r3, [fp, #-620]	@ tmp3258,
	str	r7, [fp, #-780]	@, %sfp
	orr	r7, r7, r6, asl #24	@, tmp3221,,,
	ldr	r6, [fp, #-764]	@, %sfp
	cmp	r3, ip	@ tmp3258, tmp3259
	movge	r3, ip	@ tmp3257, tmp3259
	add	ip, r6, #4	@ iftmp.446,,
	cmp	r3, #64	@ tmp3257,
	movle	r3, #0	@,
	movgt	r3, #1	@,
	cmp	r9, ip	@ temp.1141, iftmp.446
	str	r3, [fp, #-764]	@, %sfp
	ldr	r3, [fp, #-772]	@, %sfp
	movcc	r9, lr	@ iftmp.446, iftmp.446
	sub	lr, r7, #1	@ tmp3222, tmp3221,
	movcs	r9, ip	@ iftmp.446, iftmp.446
	strb	lr, [r4, #94]	@ tmp3222,
	strb	r9, [r4, #98]	@ iftmp.446,
	mov	r7, r9, lsr #24	@ tmp3204, iftmp.446,
	strb	r0, [r4, #166]	@ tmp3270,
	mov	ip, lr, lsr #24	@ tmp3249, tmp3222,
	strb	r7, [r4, #101]	@ tmp3204,
	ubfx	r7, r9, #8, #8	@ tmp3187, iftmp.446,,
	strb	ip, [r4, #97]	@ tmp3249,
	ubfx	ip, r9, #16, #8	@ tmp3196, iftmp.446,,
	strb	r7, [r4, #99]	@ tmp3187,
	ubfx	r9, lr, #8, #8	@ tmp3232, tmp3222,,
	strb	ip, [r4, #100]	@ tmp3196,
	ubfx	r7, lr, #16, #8	@ tmp3241, tmp3222,,
	strb	r9, [r4, #95]	@ tmp3232,
	strb	r7, [r4, #96]	@ tmp3241,
	strb	r0, [r4, #167]	@ tmp3279,
	ldr	r7, [fp, #-764]	@, %sfp
	strb	r7, [r4, #165]	@,
	mov	lr, r7, lsr #24	@ tmp3287,,
	strb	lr, [r4, #168]	@ tmp3287,
	ldr	r9, [fp, #-756]	@, %sfp
	str	r9, [sp, #0]	@,
	bl	Check32PdPattern	@
	cmp	r0, #0	@ ValidFlag.1370
	mvneq	r6, #0	@ HitPhase,
	beq	.L279	@,
	cmp	r0, #1	@ ValidFlag.1370,
	bne	.L281	@,
	ldrsb	r3, [r4, #192]	@ temp.1368, <variable>.stFmdCtx.Last32Phase
	cmn	r3, #1	@ temp.1368,
	beq	.L285	@,
	cmp	r3, #4	@ temp.1368,
	beq	.L285	@,
.L281:
	mov	r6, #0	@ HitPhase,
.L279:
	mvn	r7, #0	@ HitPhase.1165,
	mov	r9, #1	@ InValidCnt,
.L280:
	ldr	ip, [fp, #-756]	@, %sfp
	mov	r0, #1	@,
	sub	r1, fp, #164	@,,
	ldr	r2, [fp, #-776]	@, %sfp
	ldr	r3, [fp, #-772]	@, %sfp
	str	ip, [sp, #0]	@,
	bl	Check32PdPattern	@
	cmp	r0, #0	@ ValidFlag.1304
	beq	.L287	@,
	cmp	r0, #1	@ ValidFlag.1304,
	bne	.L289	@,
	ldrsb	r3, [r4, #192]	@ temp.1294, <variable>.stFmdCtx.Last32Phase
	cmp	r3, #0	@ temp.1294,
	beq	.L293	@,
	cmp	r3, #5	@ temp.1294,
	beq	.L293	@,
.L289:
	mov	r6, #1	@ HitPhase,
.L287:
	add	r9, r9, #1	@ InValidCnt, InValidCnt,
.L288:
	ldr	ip, [fp, #-756]	@, %sfp
	mov	r0, #2	@,
	sub	r1, fp, #164	@,,
	ldr	r2, [fp, #-776]	@, %sfp
	ldr	r3, [fp, #-772]	@, %sfp
	str	ip, [sp, #0]	@,
	bl	Check32PdPattern	@
	cmp	r0, #0	@ ValidFlag.1378
	beq	.L295	@,
	cmp	r0, #1	@ ValidFlag.1378,
	bne	.L297	@,
	ldrsb	r3, [r4, #192]	@ temp.1376, <variable>.stFmdCtx.Last32Phase
	cmp	r3, #1	@ temp.1376,
	beq	.L301	@,
	cmp	r3, #6	@ temp.1376,
	beq	.L301	@,
.L297:
	mov	r6, #2	@ HitPhase,
.L295:
	add	r9, r9, #1	@ InValidCnt, InValidCnt,
.L296:
	ldr	ip, [fp, #-756]	@, %sfp
	mov	r0, #3	@,
	sub	r1, fp, #164	@,,
	ldr	r2, [fp, #-776]	@, %sfp
	ldr	r3, [fp, #-772]	@, %sfp
	str	ip, [sp, #0]	@,
	bl	Check32PdPattern	@
	cmp	r0, #0	@ ValidFlag.1158
	beq	.L303	@,
	cmp	r0, #1	@ ValidFlag.1158,
	bne	.L305	@,
	ldrsb	r3, [r4, #192]	@ temp.1372, <variable>.stFmdCtx.Last32Phase
	cmp	r3, #2	@ temp.1372,
	beq	.L309	@,
	cmp	r3, #7	@ temp.1372,
	beq	.L309	@,
.L305:
	mov	r6, #3	@ HitPhase,
.L303:
	add	r9, r9, #1	@ InValidCnt, InValidCnt,
.L304:
	ldr	ip, [fp, #-756]	@, %sfp
	sub	r1, fp, #164	@,,
	ldr	r2, [fp, #-776]	@, %sfp
	mov	r0, #4	@,
	ldr	r3, [fp, #-772]	@, %sfp
	str	ip, [sp, #0]	@,
	bl	Check32PdPattern	@
	cmp	r0, #0	@ ValidFlag
	beq	.L310	@,
	cmp	r0, #1	@ ValidFlag,
	bne	.L311	@,
	ldrsb	r3, [r4, #192]	@ D.38664, <variable>.stFmdCtx.Last32Phase
	cmp	r3, #3	@ D.38664,
	beq	.L312	@,
	cmp	r3, #8	@ D.38664,
	beq	.L312	@,
.L311:
	mov	r6, #4	@ HitPhase,
.L310:
	add	r9, r9, #1	@ InValidCnt, InValidCnt,
.L315:
	ldr	r3, [fp, #-764]	@, %sfp
	cmp	r9, #4	@ InValidCnt,
	orrgt	r3, r3, #1	@,,,
	cmp	r3, #0	@ tmp4119,
	beq	.L407	@,
	ldr	r7, [fp, #-764]	@, %sfp
	cmp	r7, #0	@,
	beq	.L317	@,
	mov	r0, #0	@ tmp4120,
	strb	r0, [r4, #169]	@ tmp4120, <variable>.stFmdCtx.PdInfo.PdState
.L320:
	ldrsb	r3, [r4, #169]	@ D.38652, <variable>.stFmdCtx.PdInfo.PdState
	mov	lr, #0	@ tmp4125,
	strb	lr, [r4, #170]	@ tmp4125, <variable>.stFmdCtx.PdInfo.RptFlag
	and	r9, r3, #255	@ tmp4122, D.38652,
	strb	lr, [r4, #161]	@ tmp4125,
	mov	ip, r3, lsr #24	@ tmp4148, D.38652,
	strb	r9, [r4, #188]	@ tmp4122,
	strb	ip, [r4, #191]	@ tmp4148,
	strb	ip, [r4, #189]	@ tmp4131,
	strb	ip, [r4, #190]	@ tmp4140,
	strb	r9, [r4, #172]	@ tmp4122,
	strb	ip, [r4, #173]	@ tmp4131,
	strb	ip, [r4, #174]	@ tmp4140,
	strb	ip, [r4, #175]	@ tmp4148,
	strb	r9, [r4, #176]	@ tmp4122,
	strb	ip, [r4, #177]	@ tmp4131,
	strb	ip, [r4, #178]	@ tmp4140,
	strb	ip, [r4, #179]	@ tmp4148,
	strb	r9, [r4, #180]	@ tmp4122,
	strb	ip, [r4, #181]	@ tmp4131,
	strb	ip, [r4, #182]	@ tmp4140,
	strb	ip, [r4, #183]	@ tmp4148,
	strb	r9, [r4, #184]	@ tmp4122,
	strb	ip, [r4, #185]	@ tmp4131,
	strb	ip, [r4, #186]	@ tmp4140,
	strb	ip, [r4, #187]	@ tmp4148,
	strb	lr, [r4, #162]	@ tmp4125,
	strb	lr, [r4, #163]	@ tmp4125,
	strb	lr, [r4, #164]	@ tmp4125,
	strb	lr, [r4, #171]	@ tmp4125, <variable>.stFmdCtx.PdInfo.PdSubState
.L319:
	uxtb	r6, r6	@ iftmp.1148, HitPhase
.L324:
	sub	r7, fp, #68	@,,
	str	r7, [fp, #-776]	@, %sfp
	strb	r6, [r4, #192]	@ iftmp.1148, <variable>.stFmdCtx.Last32Phase
	add	r1, r4, #161	@, pstFmdSoftInfo,
	mov	r2, #11	@,
	ldr	r0, [fp, #-776]	@, %sfp
	bl	memcpy	@
	ldr	r7, [fp, #-68]	@ NewPdInf$Pd32Det,
.L262:
	ldrb	r0, [r4, #140]	@ zero_extendqisi2	@ tmp4436,
	ldrb	r9, [r4, #139]	@ zero_extendqisi2	@ tmp4435,
	ldrb	r2, [r4, #141]	@ zero_extendqisi2	@ tmp4439,
	ldrb	r6, [r4, #142]	@ zero_extendqisi2	@ tmp4442,
	orr	r1, r9, r0, asl #8	@, tmp4438, tmp4435, tmp4436,
	orr	ip, r1, r2, asl #16	@, tmp4441, tmp4438, tmp4439,
	orr	r3, ip, r6, asl #24	@, tmp4444, tmp4441, tmp4442,
	cmp	r3, #1	@ tmp4444,
	beq	.L408	@,
.L325:
	add	r6, r4, #117	@ tmp4518, pstFmdSoftInfo,
	add	r9, r4, #128	@ tmp4522, pstFmdSoftInfo,
	mov	r2, #11	@,
	add	r0, r4, #106	@, pstFmdSoftInfo,
	mov	r1, r6	@, tmp4518
	add	lr, r4, #139	@, pstFmdSoftInfo,
	str	lr, [fp, #-772]	@, %sfp
	bl	memcpy	@
	mov	r0, r6	@, tmp4518
	mov	r1, r9	@, tmp4522
	mov	r2, #11	@,
	add	r6, r4, #150	@ tmp4530, pstFmdSoftInfo,
	bl	memcpy	@
	ldr	r1, [fp, #-772]	@, %sfp
	mov	r2, #11	@,
	mov	r0, r9	@, tmp4522
	bl	memcpy	@
	mov	r1, r6	@, tmp4530
	mov	r2, #11	@,
	ldr	r0, [fp, #-772]	@, %sfp
	bl	memcpy	@
	mov	r0, r6	@, tmp4530
	ldr	r1, [fp, #-776]	@, %sfp
	mov	r2, #11	@,
	str	r7, [fp, #-68]	@ NewPdInf$Pd32Det, NewPdInf.Pd32Det
	bl	memcpy	@
.L258:
	ldrb	r2, [r4, #441]	@ zero_extendqisi2	@ tmp4538,
	ldrb	r6, [r4, #440]	@ zero_extendqisi2	@ tmp4537,
	ldrb	r1, [r4, #442]	@ zero_extendqisi2	@ tmp4541,
	orr	r3, r6, r2, asl #8	@, tmp4540, tmp4537, tmp4538,
	ldrb	r7, [r4, #443]	@ zero_extendqisi2	@ tmp4544,
	orr	ip, r3, r1, asl #16	@, tmp4543, tmp4540, tmp4541,
	orrs	r2, ip, r7, asl #24	@,, tmp4543, tmp4544,
	bne	.L409	@,
	ldrb	lr, [r4, #437]	@ zero_extendqisi2	@ tmp4570,
	ldrb	r1, [r4, #438]	@ zero_extendqisi2	@ tmp4573,
	ldrb	r6, [r4, #436]	@ zero_extendqisi2	@ tmp4569,
	ldrb	r2, [r4, #439]	@ zero_extendqisi2	@ tmp4576,
	orr	r3, r6, lr, asl #8	@, tmp4572, tmp4569, tmp4570,
	orr	ip, r3, r1, asl #16	@, tmp4575, tmp4572, tmp4573,
	orrs	r2, ip, r2, asl #24	@,, tmp4575, tmp4576,
	addeq	r1, sl, sl, asl #2	@, tmp4595, D.38491, D.38491,
	subeq	r0, fp, #56	@,,
	moveq	r2, #11	@,
	beq	.L367	@,
.L327:
	sub	sl, sl, #1	@ tmp4579, D.38491,
	sub	r0, fp, #56	@,,
	mov	r2, #11	@,
	add	r1, sl, sl, asl #2	@, tmp4583, tmp4579, tmp4579,
.L367:
	add	r7, sl, r1, asl #1	@, tmp4597, D.38491, tmp4595,
	add	r1, r7, r4	@ tmp4598, tmp4597, pstFmdSoftInfo
	add	r1, r1, #106	@, tmp4598,
	bl	memcpy	@
	ldr	r6, [fp, #-56]	@ Pld32Info$Pd32Det.1144,
	mov	r2, r6	@ Pld32Info$Pd32Det, Pld32Info$Pd32Det.1144
	b	.L257	@
.L349:
	ldr	r3, [fp, #-800]	@, %sfp
	cmp	r3, #1	@,
	bne	.L350	@,
	ldr	lr, [fp, #-756]	@, %sfp
	movw	ip, #:lower16:1717986919	@ tmp4663,
	movt	ip, #:upper16:1717986919	@ tmp4663,
	sxtb	r3, lr	@ PdInfo$PdSubState,
	add	lr, r3, #2	@ tmp4660, PdInfo$PdSubState,
	smull	r0, r5, ip, lr	@, tmp4662, tmp4663, tmp4660
	mov	r0, lr, asr #31	@ tmp4665, tmp4660,
	sub	ip, fp, #44	@,,
	rsb	r2, r0, r5, asr #2	@, tmp4661, tmp4665, tmp4662,
	add	r1, r2, r2, asl #2	@, tmp4668, tmp4661, tmp4661,
	sub	r5, lr, r1, asl #1	@ tmp4670, tmp4660, tmp4668,
	add	r0, ip, r5, asl #2	@, tmp4673,, tmp4670,
	ldr	r3, [r0, #-120]	@ tmp4675, MchTab
.L371:
	str	r3, [fp, #-96]	@ tmp4675, stFmdRtlOutPara.DirMch
	b	.L350	@
.L402:
	ldr	lr, [fp, #-740]	@ tmp2943,
	sub	r1, fp, #664	@,,
	ldr	r0, [fp, #-776]	@, %sfp
	add	r2, r4, #239	@, pstFmdSoftInfo,
	add	r3, r4, #227	@, pstFmdSoftInfo,
	str	lr, [sp, #0]	@ tmp2943,
	bl	Detect22Pld	@
	mov	r5, r0	@ IsProgressive,
	b	.L246	@
.L401:
	ldr	r3, [fp, #-668]	@ temp.1112,
	movw	r1, #23799	@ tmp2924,
	cmp	r3, r1	@ temp.1112, tmp2924
	ble	.L253	@,
	movw	r6, #24199	@ tmp2925,
	cmp	r3, r6	@ temp.1112, tmp2925
	bgt	.L253	@,
	mov	r5, #1	@ IsProgressive,
	b	.L246	@
.L409:
	ldrb	r1, [r4, #437]	@ zero_extendqisi2	@ tmp4548,
	ldrb	r3, [r4, #436]	@ zero_extendqisi2	@ tmp4547,
	ldrb	ip, [r4, #438]	@ zero_extendqisi2	@ tmp4551,
	orr	r7, r3, r1, asl #8	@, tmp4550, tmp4547, tmp4548,
	ldrb	r0, [r4, #439]	@ zero_extendqisi2	@ tmp4554,
	orr	lr, r7, ip, asl #16	@, tmp4553, tmp4550, tmp4551,
	orrs	r2, lr, r0, asl #24	@,, tmp4553, tmp4554,
	beq	.L327	@,
	add	r7, sl, sl, asl #2	@, tmp4560, D.38491, D.38491,
	mov	r2, #11	@,
	sub	r0, fp, #56	@,,
	add	lr, sl, r7, asl #1	@, tmp4562, D.38491, tmp4560,
	add	r6, lr, r4	@ tmp4563, tmp4562, pstFmdSoftInfo
	add	r1, r6, #84	@, tmp4563,
	bl	memcpy	@
	ldr	r6, [fp, #-56]	@ Pld32Info$Pd32Det.1144,
	mov	r2, r6	@ Pld32Info$Pd32Det, Pld32Info$Pd32Det.1144
	b	.L257	@
.L333:
	ldr	sl, [fp, #-884]	@, %sfp
	sub	r5, fp, #68	@ tmp4809,,
	str	r2, [fp, #-56]	@ Pld32Info$Pd32Det, Pld32Info.Pd32Det
	sub	r9, fp, #164	@ tmp4814,,
	ldr	r3, .L414	@ tmp4815,
	ldmia	sl, {r0, r1, r2}	@,,,
	ldr	sl, [fp, #-740]	@,
	mov	ip, r2, lsr #16	@ tmp4811,,
	str	sl, [fp, #-800]	@, %sfp
	strb	lr, [r4, #429]	@ D.38456, <variable>.stFmdCtx.MainState
	mov	lr, r5	@, tmp4809
	strb	r7, [r4, #430]	@ D.38457, <variable>.stFmdCtx.PrevMainState
	stmia	lr!, {r0, r1}	@,,
	strh	r2, [lr, #0]	@ movhi	@, PdInfo
	uxtb	lr, ip	@, tmp4811
	str	lr, [fp, #-756]	@, %sfp
	mov	lr, r3	@ tmp4892, tmp4815
	ldmia	lr!, {r0, r1, r2, r3}	@ tmp4892,,,,
	strb	ip, [r5, #10]	@ tmp4811, PdInfo
	mov	ip, r9	@ tmp4893, tmp4814
	stmia	ip!, {r0, r1, r2, r3}	@ tmp4893,,,,
	b	.L369	@
.L337:
	ldrb	r0, [r4, #15]	@ zero_extendqisi2	@ tmp4788,
	movw	r5, #:lower16:.LANCHOR1	@ tmp4852,
	ldrb	r3, [r4, #14]	@ zero_extendqisi2	@ tmp4787,
	movt	r5, #:upper16:.LANCHOR1	@ tmp4852,
	ldrb	r1, [r4, #27]	@ zero_extendqisi2	@ tmp4798,
	ldrb	r2, [r4, #26]	@ zero_extendqisi2	@ tmp4797,
	orr	ip, r3, r0, asl #8	@, tmp4790, tmp4787, tmp4788,
	ldrb	r6, [r4, #16]	@ zero_extendqisi2	@ tmp4791,
	ldrb	r0, [r4, #28]	@ zero_extendqisi2	@ tmp4801,
	orr	r1, r2, r1, asl #8	@, tmp4800, tmp4797, tmp4798,
	ldrb	r3, [r4, #17]	@ zero_extendqisi2	@ tmp4794,
	ldrb	r2, [r4, #29]	@ zero_extendqisi2	@ tmp4804,
	orr	ip, ip, r6, asl #16	@, tmp4793, tmp4790, tmp4791,
	orr	r1, r1, r0, asl #16	@, tmp4803, tmp4800, tmp4801,
	strb	lr, [r4, #429]	@ D.38456, <variable>.stFmdCtx.MainState
	strb	r7, [r4, #430]	@ D.38457, <variable>.stFmdCtx.PrevMainState
	orr	r3, ip, r3, asl #24	@, D.38490, tmp4793, tmp4794,
	orr	r1, r1, r2, asl #24	@, temp.1119, tmp4803, tmp4804,
	b	.L345	@
.L341:
	mov	lr, #0	@ prephitmp.1153,
	b	.L336	@
.L312:
	ldrb	r0, [r4, #189]	@ zero_extendqisi2	@ tmp3965,
	mov	r3, #0	@ tmp3977,
	ldrb	lr, [r4, #188]	@ zero_extendqisi2	@ tmp3964,
	ldrb	r2, [r4, #190]	@ zero_extendqisi2	@ tmp3968,
	ldrb	ip, [r4, #191]	@ zero_extendqisi2	@ tmp3971,
	orr	r1, lr, r0, asl #8	@, tmp3967, tmp3964, tmp3965,
	orr	lr, r1, r2, asl #16	@, tmp3970, tmp3967, tmp3968,
	orr	r2, lr, ip, asl #24	@, tmp3973, tmp3970, tmp3971,
	add	r2, r2, #1	@ D.38660, tmp3973,
	strb	r2, [r4, #188]	@ D.38660,
	cmp	r2, r3	@ D.38660,
	ubfx	r0, r2, #8, #8	@ tmp3983, D.38660,,
	ubfx	lr, r2, #16, #8	@ tmp3992, D.38660,,
	mov	r1, r2, lsr #24	@ tmp4000, D.38660,
	strb	r0, [r4, #189]	@ tmp3983,
	strb	lr, [r4, #190]	@ tmp3992,
	strb	r1, [r4, #191]	@ tmp4000,
	ble	.L313	@,
	cmp	r2, #5	@ D.38660,
	movge	r2, #5	@ iftmp.451,
	strb	r2, [r4, #188]	@ iftmp.451,
	cmp	r2, #3	@ iftmp.451,
	ubfx	lr, r2, #8, #8	@ tmp4017, iftmp.451,,
	ubfx	r1, r2, #16, #8	@ tmp4026, iftmp.451,,
	mov	ip, r2, lsr #24	@ tmp4034, iftmp.451,
	movle	r6, #4	@ HitPhase,
	strb	lr, [r4, #189]	@ tmp4017,
	strb	r1, [r4, #190]	@ tmp4026,
	movle	r7, r6	@ HitPhase.1165, HitPhase
	strb	ip, [r4, #191]	@ tmp4034,
	ble	.L315	@,
	mov	r6, #4	@ HitPhase,
	mov	r2, #3	@ tmp4046,
	strb	r3, [r4, #187]	@ tmp3977,
	mov	r7, r6	@ HitPhase.1165, HitPhase
	strb	r3, [r4, #173]	@ tmp3977,
	strb	r2, [r4, #184]	@ tmp4046,
	strb	r2, [r4, #172]	@ tmp4046,
	strb	r3, [r4, #174]	@ tmp3977,
	strb	r3, [r4, #175]	@ tmp3977,
	strb	r2, [r4, #176]	@ tmp4046,
	strb	r3, [r4, #177]	@ tmp3977,
	strb	r3, [r4, #178]	@ tmp3977,
	strb	r3, [r4, #179]	@ tmp3977,
	strb	r2, [r4, #180]	@ tmp4046,
	strb	r3, [r4, #181]	@ tmp3977,
	strb	r3, [r4, #182]	@ tmp3977,
	strb	r3, [r4, #183]	@ tmp3977,
	strb	r3, [r4, #185]	@ tmp3977,
	strb	r3, [r4, #186]	@ tmp3977,
	b	.L315	@
.L309:
	ldrb	r1, [r4, #185]	@ zero_extendqisi2	@ tmp3798,
	mov	r3, #0	@ tmp3810,
	ldrb	r2, [r4, #184]	@ zero_extendqisi2	@ tmp3797,
	ldrb	r0, [r4, #186]	@ zero_extendqisi2	@ tmp3801,
	ldrb	ip, [r4, #187]	@ zero_extendqisi2	@ tmp3804,
	orr	lr, r2, r1, asl #8	@, tmp3800, tmp3797, tmp3798,
	orr	r1, lr, r0, asl #16	@, tmp3803, tmp3800, tmp3801,
	orr	r2, r1, ip, asl #24	@, tmp3806, tmp3803, tmp3804,
	add	r2, r2, #1	@ temp.1151, tmp3806,
	strb	r2, [r4, #184]	@ temp.1151,
	cmp	r2, r3	@ temp.1151,
	ubfx	r0, r2, #8, #8	@ tmp3816, temp.1151,,
	ubfx	lr, r2, #16, #8	@ tmp3825, temp.1151,,
	mov	r1, r2, lsr #24	@ tmp3833, temp.1151,
	strb	r0, [r4, #185]	@ tmp3816,
	strb	lr, [r4, #186]	@ tmp3825,
	strb	r1, [r4, #187]	@ tmp3833,
	ble	.L410	@,
	cmp	r2, #5	@ temp.1151,
	movge	r2, #5	@ iftmp.1333,
	strb	r2, [r4, #184]	@ iftmp.1333,
	cmp	r2, #3	@ iftmp.1333,
	ubfx	r0, r2, #8, #8	@ tmp3866, iftmp.1333,,
	ubfx	lr, r2, #16, #8	@ tmp3875, iftmp.1333,,
	mov	ip, r2, lsr #24	@ tmp3883, iftmp.1333,
	movle	r6, #3	@ HitPhase,
	strb	r0, [r4, #185]	@ tmp3866,
	strb	lr, [r4, #186]	@ tmp3875,
	movle	r7, r6	@ HitPhase.1165, HitPhase
	strb	ip, [r4, #187]	@ tmp3883,
	ble	.L304	@,
	mov	r2, #3	@ tmp3895,
	strb	r3, [r4, #191]	@ tmp3810,
	mov	r6, r2	@ HitPhase, tmp3895
	strb	r2, [r4, #172]	@ tmp3895,
	strb	r3, [r4, #173]	@ tmp3810,
	mov	r7, r2	@ HitPhase.1165, HitPhase
	strb	r3, [r4, #174]	@ tmp3810,
	strb	r3, [r4, #175]	@ tmp3810,
	strb	r2, [r4, #176]	@ tmp3895,
	strb	r3, [r4, #177]	@ tmp3810,
	strb	r3, [r4, #178]	@ tmp3810,
	strb	r3, [r4, #179]	@ tmp3810,
	strb	r2, [r4, #180]	@ tmp3895,
	strb	r3, [r4, #181]	@ tmp3810,
	strb	r3, [r4, #182]	@ tmp3810,
	strb	r3, [r4, #183]	@ tmp3810,
	strb	r2, [r4, #188]	@ tmp3895,
	strb	r3, [r4, #189]	@ tmp3810,
	strb	r3, [r4, #190]	@ tmp3810,
	b	.L304	@
.L293:
	ldrb	r1, [r4, #177]	@ zero_extendqisi2	@ tmp3464,
	mov	r3, #0	@ tmp3476,
	ldrb	r2, [r4, #176]	@ zero_extendqisi2	@ tmp3463,
	ldrb	r0, [r4, #178]	@ zero_extendqisi2	@ tmp3467,
	ldrb	ip, [r4, #179]	@ zero_extendqisi2	@ tmp3470,
	orr	lr, r2, r1, asl #8	@, tmp3466, tmp3463, tmp3464,
	orr	r1, lr, r0, asl #16	@, tmp3469, tmp3466, tmp3467,
	orr	r2, r1, ip, asl #24	@, tmp3472, tmp3469, tmp3470,
	add	r2, r2, #1	@ temp.1284, tmp3472,
	strb	r2, [r4, #176]	@ temp.1284,
	cmp	r2, r3	@ temp.1284,
	ubfx	lr, r2, #8, #8	@ tmp3482, temp.1284,,
	ubfx	r1, r2, #16, #8	@ tmp3491, temp.1284,,
	mov	r0, r2, lsr #24	@ tmp3499, temp.1284,
	strb	lr, [r4, #177]	@ tmp3482,
	strb	r1, [r4, #178]	@ tmp3491,
	strb	r0, [r4, #179]	@ tmp3499,
	ble	.L411	@,
	cmp	r2, #5	@ temp.1284,
	movge	r2, #5	@ iftmp.1275,
	strb	r2, [r4, #176]	@ iftmp.1275,
	cmp	r2, #3	@ iftmp.1275,
	ubfx	r0, r2, #8, #8	@ tmp3532, iftmp.1275,,
	ubfx	lr, r2, #16, #8	@ tmp3541, iftmp.1275,,
	mov	ip, r2, lsr #24	@ tmp3549, iftmp.1275,
	movle	r6, #1	@ HitPhase,
	strb	r0, [r4, #177]	@ tmp3532,
	strb	lr, [r4, #178]	@ tmp3541,
	movle	r7, r6	@ HitPhase.1165, HitPhase
	strb	ip, [r4, #179]	@ tmp3549,
	ble	.L288	@,
	mov	r6, #1	@ HitPhase,
	mov	r2, #3	@ tmp3561,
	strb	r3, [r4, #191]	@ tmp3476,
	mov	r7, r6	@ HitPhase.1165, HitPhase
	strb	r3, [r4, #173]	@ tmp3476,
	strb	r2, [r4, #188]	@ tmp3561,
	strb	r2, [r4, #172]	@ tmp3561,
	strb	r3, [r4, #174]	@ tmp3476,
	strb	r3, [r4, #175]	@ tmp3476,
	strb	r2, [r4, #180]	@ tmp3561,
	strb	r3, [r4, #181]	@ tmp3476,
	strb	r3, [r4, #182]	@ tmp3476,
	strb	r3, [r4, #183]	@ tmp3476,
	strb	r2, [r4, #184]	@ tmp3561,
	strb	r3, [r4, #185]	@ tmp3476,
	strb	r3, [r4, #186]	@ tmp3476,
	strb	r3, [r4, #187]	@ tmp3476,
	strb	r3, [r4, #189]	@ tmp3476,
	strb	r3, [r4, #190]	@ tmp3476,
	b	.L288	@
.L301:
	ldrb	r1, [r4, #181]	@ zero_extendqisi2	@ tmp3631,
	mov	r3, #0	@ tmp3643,
	ldrb	r2, [r4, #180]	@ zero_extendqisi2	@ tmp3630,
	ldrb	r0, [r4, #182]	@ zero_extendqisi2	@ tmp3634,
	ldrb	ip, [r4, #183]	@ zero_extendqisi2	@ tmp3637,
	orr	lr, r2, r1, asl #8	@, tmp3633, tmp3630, tmp3631,
	orr	r1, lr, r0, asl #16	@, tmp3636, tmp3633, tmp3634,
	orr	r2, r1, ip, asl #24	@, tmp3639, tmp3636, tmp3637,
	add	r2, r2, #1	@ temp.1374, tmp3639,
	strb	r2, [r4, #180]	@ temp.1374,
	cmp	r2, r3	@ temp.1374,
	ubfx	r0, r2, #8, #8	@ tmp3649, temp.1374,,
	ubfx	lr, r2, #16, #8	@ tmp3658, temp.1374,,
	mov	r1, r2, lsr #24	@ tmp3666, temp.1374,
	strb	r0, [r4, #181]	@ tmp3649,
	strb	lr, [r4, #182]	@ tmp3658,
	strb	r1, [r4, #183]	@ tmp3666,
	ble	.L412	@,
	cmp	r2, #5	@ temp.1374,
	movge	r2, #5	@ iftmp.1186,
	strb	r2, [r4, #180]	@ iftmp.1186,
	cmp	r2, #3	@ iftmp.1186,
	ubfx	r0, r2, #8, #8	@ tmp3699, iftmp.1186,,
	ubfx	lr, r2, #16, #8	@ tmp3708, iftmp.1186,,
	mov	ip, r2, lsr #24	@ tmp3716, iftmp.1186,
	movle	r6, #2	@ HitPhase,
	strb	r0, [r4, #181]	@ tmp3699,
	strb	lr, [r4, #182]	@ tmp3708,
	movle	r7, r6	@ HitPhase.1165, HitPhase
	strb	ip, [r4, #183]	@ tmp3716,
	ble	.L296	@,
	mov	r6, #2	@ HitPhase,
	mov	r2, #3	@ tmp3728,
	strb	r3, [r4, #191]	@ tmp3643,
	mov	r7, r6	@ HitPhase.1165, HitPhase
	strb	r3, [r4, #173]	@ tmp3643,
	strb	r2, [r4, #188]	@ tmp3728,
	strb	r2, [r4, #172]	@ tmp3728,
	strb	r3, [r4, #174]	@ tmp3643,
	strb	r3, [r4, #175]	@ tmp3643,
	strb	r2, [r4, #176]	@ tmp3728,
	strb	r3, [r4, #177]	@ tmp3643,
	strb	r3, [r4, #178]	@ tmp3643,
	strb	r3, [r4, #179]	@ tmp3643,
	strb	r2, [r4, #184]	@ tmp3728,
	strb	r3, [r4, #185]	@ tmp3643,
	strb	r3, [r4, #186]	@ tmp3643,
	strb	r3, [r4, #187]	@ tmp3643,
	strb	r3, [r4, #189]	@ tmp3643,
	strb	r3, [r4, #190]	@ tmp3643,
	b	.L296	@
.L285:
	ldrb	r0, [r4, #173]	@ zero_extendqisi2	@ tmp3297,
	mov	r3, #0	@ tmp3309,
	ldrb	lr, [r4, #172]	@ zero_extendqisi2	@ tmp3296,
	ldrb	r2, [r4, #174]	@ zero_extendqisi2	@ tmp3300,
	ldrb	ip, [r4, #175]	@ zero_extendqisi2	@ tmp3303,
	orr	r1, lr, r0, asl #8	@, tmp3299, tmp3296, tmp3297,
	orr	lr, r1, r2, asl #16	@, tmp3302, tmp3299, tmp3300,
	orr	r2, lr, ip, asl #24	@, tmp3305, tmp3302, tmp3303,
	add	r2, r2, #1	@ temp.1362, tmp3305,
	strb	r2, [r4, #172]	@ temp.1362,
	cmp	r2, r3	@ temp.1362,
	ubfx	ip, r2, #8, #8	@ tmp3315, temp.1362,,
	ubfx	r1, r2, #16, #8	@ tmp3324, temp.1362,,
	mov	r0, r2, lsr #24	@ tmp3332, temp.1362,
	strb	ip, [r4, #173]	@ tmp3315,
	strb	r1, [r4, #174]	@ tmp3324,
	strb	r0, [r4, #175]	@ tmp3332,
	ble	.L413	@,
	cmp	r2, #5	@ temp.1362,
	movge	r2, #5	@ iftmp.1353,
	strb	r2, [r4, #172]	@ iftmp.1353,
	cmp	r2, #3	@ iftmp.1353,
	ubfx	lr, r2, #8, #8	@ tmp3365, iftmp.1353,,
	ubfx	r1, r2, #16, #8	@ tmp3374, iftmp.1353,,
	mov	ip, r2, lsr #24	@ tmp3382, iftmp.1353,
	movle	r6, r3	@ HitPhase, tmp3309
	strb	lr, [r4, #173]	@ tmp3365,
	strb	r1, [r4, #174]	@ tmp3374,
	movle	r7, r6	@ HitPhase.1165, HitPhase
	strb	ip, [r4, #175]	@ tmp3382,
	movle	r9, r6	@ InValidCnt, HitPhase
	ble	.L280	@,
	mov	r2, #3	@ tmp3394,
	mov	r6, r3	@ HitPhase, tmp3309
	strb	r3, [r4, #177]	@ tmp3309,
	mov	r7, r3	@ HitPhase.1165, HitPhase
	strb	r3, [r4, #178]	@ tmp3309,
	mov	r9, r3	@ InValidCnt, HitPhase
	strb	r2, [r4, #188]	@ tmp3394,
	strb	r2, [r4, #176]	@ tmp3394,
	strb	r3, [r4, #179]	@ tmp3309,
	strb	r2, [r4, #180]	@ tmp3394,
	strb	r3, [r4, #181]	@ tmp3309,
	strb	r3, [r4, #182]	@ tmp3309,
	strb	r3, [r4, #183]	@ tmp3309,
	strb	r2, [r4, #184]	@ tmp3394,
	strb	r3, [r4, #185]	@ tmp3309,
	strb	r3, [r4, #186]	@ tmp3309,
	strb	r3, [r4, #187]	@ tmp3309,
	strb	r3, [r4, #189]	@ tmp3309,
	strb	r3, [r4, #190]	@ tmp3309,
	strb	r3, [r4, #191]	@ tmp3309,
	b	.L280	@
.L239:
	cmp	r3, #200	@ D.38545,
	bgt	.L238	@,
	cmn	r3, #200	@ D.38545,
	blt	.L240	@,
.L365:
	ldrb	r3, [r4, #198]	@ zero_extendqisi2	@ tmp2553,
	ldrb	r8, [r4, #197]	@ zero_extendqisi2	@ tmp2552,
	ldrb	r1, [r4, #199]	@ zero_extendqisi2	@ tmp2556,
	ldrb	r5, [r4, #200]	@ zero_extendqisi2	@ tmp2559,
	orr	r9, r8, r3, asl #8	@, tmp2555, tmp2552, tmp2553,
	orr	r0, r9, r1, asl #16	@, tmp2558, tmp2555, tmp2556,
	orr	r6, r0, r5, asl #24	@,, tmp2558, tmp2559,
	str	r6, [fp, #-752]	@, %sfp
	b	.L208	@
.L406:
	sub	r1, fp, #68	@,,
	str	r1, [fp, #-776]	@, %sfp
	strb	r3, [r4, #170]	@ tmp3029, <variable>.stFmdCtx.PdInfo.RptFlag
	add	r1, r4, #161	@, pstFmdSoftInfo,
	ldr	r0, [fp, #-776]	@, %sfp
	mov	r2, #11	@,
	strb	r3, [r4, #169]	@ tmp3029, <variable>.stFmdCtx.PdInfo.PdState
	mvn	r9, #0	@ tmp3124,
	strb	r3, [r4, #161]	@ tmp3029,
	strb	r9, [r4, #192]	@ tmp3124, <variable>.stFmdCtx.Last32Phase
	strb	r3, [r4, #162]	@ tmp3029,
	strb	r3, [r4, #163]	@ tmp3029,
	strb	r3, [r4, #164]	@ tmp3029,
	bl	memcpy	@
	ldr	r7, [fp, #-68]	@ NewPdInf$Pd32Det,
	b	.L262	@
.L404:
	ldrb	r2, [r4, #19]	@ zero_extendqisi2	@ tmp2285,
	ldrb	sl, [r4, #18]	@ zero_extendqisi2	@ tmp2284,
	ldrb	r1, [r4, #20]	@ zero_extendqisi2	@ tmp2288,
	orr	r3, sl, r2, asl #8	@, tmp2287, tmp2284, tmp2285,
	ldrb	ip, [r4, #21]	@ zero_extendqisi2	@ tmp2291,
	orr	sl, r3, r1, asl #16	@, tmp2290, tmp2287, tmp2288,
	orrs	r3, sl, ip, asl #24	@, tmp2293, tmp2290, tmp2291,
	bne	.L210	@,
	ldrb	r2, [r4, #23]	@ zero_extendqisi2	@ tmp2295,
	ldrb	ip, [r4, #22]	@ zero_extendqisi2	@ tmp2294,
	ldrb	r1, [r4, #24]	@ zero_extendqisi2	@ tmp2298,
	orr	sl, ip, r2, asl #8	@, tmp2297, tmp2294, tmp2295,
	ldrb	ip, [r4, #25]	@ zero_extendqisi2	@ tmp2301,
	orr	r3, sl, r1, asl #16	@, tmp2300, tmp2297, tmp2298,
	orrs	r2, r3, ip, asl #24	@,, tmp2300, tmp2301,
	bne	.L209	@,
	b	.L365	@
.L232:
	ldr	r1, [fp, #-752]	@, %sfp
	eor	r9, sl, #1	@ tmp2427, islasi14smallest,
	tst	r9, r1	@ tmp2427,
	beq	.L233	@,
	mvn	ip, #49	@ tmp2432,
	cmp	r3, ip	@ fac.1133, tmp2432
	movge	r3, ip	@ fac.1133, tmp2432
	b	.L233	@
.L237:
	cmn	r3, #1000	@ D.38545,
	bge	.L239	@,
	mvn	r7, #0	@ tmp2530,
	mvn	r2, #3	@ tmp2526,
	add	lr, r7, #25	@ tmp2519, tmp2519,
	strb	r7, [r4, #196]	@ tmp2530,
	strb	r7, [r4, #195]	@ tmp2530,
	strb	lr, [r4, #193]	@ tmp2519,
	strb	r2, [r4, #194]	@ tmp2526,
.L240:
	mov	ip, #0	@ tmp2564,
	mov	r2, #1	@ tmp2566,
	strb	r2, [r4, #197]	@ tmp2566,
	str	r2, [fp, #-752]	@ tmp2566, %sfp
	strb	ip, [r4, #200]	@ tmp2564,
	strb	ip, [r4, #198]	@ tmp2564,
	strb	ip, [r4, #199]	@ tmp2564,
	b	.L208	@
.L403:
	strb	r3, [r4, #200]	@ tmp2265,
	str	r2, [fp, #-752]	@ D.38587, %sfp
	strb	r2, [r4, #197]	@ D.38587,
	strb	r3, [r4, #198]	@ tmp2265,
	strb	r3, [r4, #199]	@ tmp2265,
	b	.L208	@
.L407:
	cmp	r8, #0	@ prephitmp.1043,
	bne	.L317	@,
	cmp	r7, #4	@ HitPhase.1165,
	bhi	.L321	@,
	add	r3, r7, #42	@ tmp4321, HitPhase.1165,
	ldrb	r0, [r4, #11]	@ zero_extendqisi2	@ tmp4413,
	ldrb	r9, [r4, #10]	@ zero_extendqisi2	@ tmp4412,
	and	lr, r7, #1	@ tmp4422, HitPhase.1165,
	add	r3, r4, r3, asl #2	@, tmp4324, pstFmdSoftInfo, tmp4321,
	ldrb	r2, [r4, #12]	@ zero_extendqisi2	@ tmp4416,
	orr	r1, r9, r0, asl #8	@, tmp4415, tmp4412, tmp4413,
	ldrb	ip, [r4, #13]	@ zero_extendqisi2	@ tmp4419,
	ldrb	r9, [r3, #4]	@ zero_extendqisi2	@ tmp4326,
	orr	r2, r1, r2, asl #16	@, tmp4418, tmp4415, tmp4416,
	orr	ip, r2, ip, asl #24	@, tmp4421, tmp4418, tmp4419,
	strb	r9, [r4, #169]	@ tmp4326, <variable>.stFmdCtx.PdInfo.PdState
	ldrb	r0, [r3, #5]	@ zero_extendqisi2	@ tmp4359,
	ldrb	r1, [r3, #4]	@ zero_extendqisi2	@ tmp4354,
	ldrb	r2, [r3, #6]	@ zero_extendqisi2	@ tmp4366,
	ldrb	r9, [r3, #7]	@ zero_extendqisi2	@ tmp4373,
	orr	r1, r1, r0, asl #8	@, tmp4361, tmp4354, tmp4359,
	mov	r0, #0	@ tmp4387,
	strb	r0, [r4, #162]	@ tmp4387,
	orr	r2, r1, r2, asl #16	@, tmp4368, tmp4361, tmp4366,
	strb	r0, [r4, #163]	@ tmp4396,
	orr	r3, r2, r9, asl #24	@, tmp4375, tmp4368, tmp4373,
	cmp	r3, #3	@ tmp4375,
	movle	r9, #0	@, tmp4377
	movgt	r9, #1	@, tmp4377
	cmp	ip, lr	@ tmp4421, tmp4422
	uxtbne	r6, r7	@ iftmp.1148, HitPhase.1165
	strb	r9, [r4, #161]	@ tmp4377,
	mov	r1, r9, lsr #24	@ tmp4404, tmp4377,
	strb	r1, [r4, #164]	@ tmp4404,
	addne	r1, r7, #5	@ tmp4424, HitPhase.1165,
	uxtbeq	r1, r7	@ iftmp.455, HitPhase.1165
	uxtbne	r1, r1	@ iftmp.455, tmp4424
	uxtbeq	r6, r1	@ iftmp.1148, iftmp.455
	strb	r1, [r4, #171]	@ iftmp.455, <variable>.stFmdCtx.PdInfo.PdSubState
	rsbs	r2, r7, #1	@ tmp4426, HitPhase.1165
	movcc	r2, #0	@ tmp4426
	strb	r2, [r4, #170]	@ tmp4426, <variable>.stFmdCtx.PdInfo.RptFlag
	b	.L324	@
.L408:
	cmp	r7, #0	@ NewPdInf$Pd32Det,
	bne	.L325	@,
	add	r3, r3, #1	@ tmp4445, tmp4445,
	strb	r7, [r4, #150]	@ NewPdInf$Pd32Det,
	strb	r3, [r4, #125]	@ tmp4445, <variable>.PdState
	strb	r3, [r4, #158]	@ tmp4445, <variable>.PdState
	strb	r7, [r4, #151]	@ NewPdInf$Pd32Det,
	strb	r7, [r4, #152]	@ NewPdInf$Pd32Det,
	strb	r7, [r4, #153]	@ NewPdInf$Pd32Det,
	strb	r3, [r4, #147]	@ tmp4445, <variable>.PdState
	strb	r7, [r4, #139]	@ NewPdInf$Pd32Det,
	strb	r7, [r4, #140]	@ NewPdInf$Pd32Det,
	strb	r7, [r4, #141]	@ NewPdInf$Pd32Det,
	strb	r7, [r4, #142]	@ NewPdInf$Pd32Det,
	strb	r3, [r4, #136]	@ tmp4445, <variable>.PdState
	strb	r7, [r4, #128]	@ NewPdInf$Pd32Det,
	strb	r7, [r4, #129]	@ NewPdInf$Pd32Det,
	strb	r7, [r4, #130]	@ NewPdInf$Pd32Det,
	strb	r7, [r4, #131]	@ NewPdInf$Pd32Det,
	strb	r7, [r4, #117]	@ NewPdInf$Pd32Det,
	strb	r7, [r4, #118]	@ NewPdInf$Pd32Det,
	strb	r7, [r4, #119]	@ NewPdInf$Pd32Det,
	strb	r7, [r4, #120]	@ NewPdInf$Pd32Det,
	b	.L325	@
.L317:
	ldrb	ip, [r4, #169]	@ zero_extendqisi2	@ <variable>.stFmdCtx.PdInfo.PdState, <variable>.stFmdCtx.PdInfo.PdState
	sub	lr, ip, #1	@ tmp4315, <variable>.stFmdCtx.PdInfo.PdState,
	sxtb	r0, lr	@ tmp4316, tmp4315
	cmp	r0, #4	@ tmp4316,
	movge	r0, #4	@ iftmp.452,
	bic	r7, r0, r0, asr #31	@ tmp4319, iftmp.452
	strb	r7, [r4, #169]	@ tmp4319, <variable>.stFmdCtx.PdInfo.PdState
	b	.L320	@
.L210:
	cmp	r3, #1	@ tmp2293,
	bne	.L209	@,
	ldrb	ip, [r4, #23]	@ zero_extendqisi2	@ tmp2305,
	ldrb	sl, [r4, #22]	@ zero_extendqisi2	@ tmp2304,
	ldrb	r1, [r4, #24]	@ zero_extendqisi2	@ tmp2308,
	ldrb	r2, [r4, #25]	@ zero_extendqisi2	@ tmp2311,
	orr	r3, sl, ip, asl #8	@, tmp2307, tmp2304, tmp2305,
	orr	sl, r3, r1, asl #16	@, tmp2310, tmp2307, tmp2308,
	orr	r3, sl, r2, asl #24	@, tmp2313, tmp2310, tmp2311,
	cmp	r3, #1	@ tmp2313,
	bne	.L209	@,
	b	.L365	@
.L415:
	.align	2
.L414:
	.word	.LANCHOR1+124
.L321:
	rsbs	lr, r7, #1	@ tmp4428, HitPhase.1165
	movcc	lr, #0	@ tmp4428
	cmn	r7, #1	@ HitPhase.1165,
	strb	lr, [r4, #170]	@ tmp4428, <variable>.stFmdCtx.PdInfo.RptFlag
	uxtbne	r6, r7	@ iftmp.1148, HitPhase.1165
	bne	.L324	@,
	b	.L319	@
.L410:
	mov	r6, #3	@ HitPhase,
	strb	r3, [r4, #187]	@ tmp3810,
	strb	r3, [r4, #184]	@ tmp3810,
	mov	r7, r6	@ HitPhase.1165, HitPhase
	strb	r3, [r4, #185]	@ tmp3810,
	strb	r3, [r4, #186]	@ tmp3810,
	b	.L304	@
.L411:
	mov	r6, #1	@ HitPhase,
	strb	r3, [r4, #179]	@ tmp3476,
	strb	r3, [r4, #176]	@ tmp3476,
	mov	r7, r6	@ HitPhase.1165, HitPhase
	strb	r3, [r4, #177]	@ tmp3476,
	strb	r3, [r4, #178]	@ tmp3476,
	b	.L288	@
.L313:
	mov	r6, #4	@ HitPhase,
	strb	r3, [r4, #191]	@ tmp3977,
	strb	r3, [r4, #188]	@ tmp3977,
	mov	r7, r6	@ HitPhase.1165, HitPhase
	strb	r3, [r4, #189]	@ tmp3977,
	strb	r3, [r4, #190]	@ tmp3977,
	b	.L315	@
.L412:
	mov	r6, #2	@ HitPhase,
	strb	r3, [r4, #183]	@ tmp3643,
	strb	r3, [r4, #180]	@ tmp3643,
	mov	r7, r6	@ HitPhase.1165, HitPhase
	strb	r3, [r4, #181]	@ tmp3643,
	strb	r3, [r4, #182]	@ tmp3643,
	b	.L296	@
.L413:
	mov	r6, r3	@ HitPhase, tmp3309
	strb	r3, [r4, #172]	@ tmp3309,
	strb	r3, [r4, #173]	@ tmp3309,
	mov	r7, r3	@ HitPhase.1165, HitPhase
	strb	r3, [r4, #174]	@ tmp3309,
	mov	r9, r3	@ InValidCnt, HitPhase
	strb	r3, [r4, #175]	@ tmp3309,
	b	.L280	@
.L405:
	movw	r6, #:lower16:-500	@ tmp2420,
	movt	r6, #:upper16:-500	@ tmp2420,
	cmp	r0, r6	@ tmp2418, tmp2420
	movge	r3, r0	@ fac.1133, tmp2418
	movlt	r3, r6	@ fac.1133, tmp2420
	b	.L231	@
	.fnend
	.size	PQ_MNG_IFMD_GetPlayBackConfig, .-PQ_MNG_IFMD_GetPlayBackConfig
	.align	2
	.global	PQ_MNG_IFMD_HardwareParaInit
	.type	PQ_MNG_IFMD_HardwareParaInit, %function
PQ_MNG_IFMD_HardwareParaInit:
	.fnstart
.LFB1392:
	@ args = 0, pretend = 0, frame = 200
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #208
	sub	sp, sp, #208	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	sub	r5, fp, #228	@ tmp136,,
	mov	r1, #200	@,
	mov	r4, #1	@ tmp137,
	mov	r0, r5	@, tmp136
	mov	r6, #20	@ tmp152,
	bl	__memzero	@
	mov	r3, #0	@ tmp154,
	mov	r1, r5	@, tmp136
	mov	r0, r3	@, tmp154
	mov	ip, #16	@ tmp144,
	mov	r2, #32	@ tmp145,
	mov	lr, #64	@ tmp146,
	mov	r5, #8	@ tmp143,
	str	r3, [fp, #-76]	@ tmp154, stIFmdDectCfg.stPqFmdLashThd.u32Lasi_mode
	mov	r7, #4	@ tmp147,
	str	ip, [fp, #-144]	@ tmp144, stIFmdDectCfg.stPqFmdPccThd.u32Pcc_vthd0
	str	ip, [fp, #-192]	@ tmp144, stIFmdDectCfg.stPqFmdHistbinThd.u32Hist_thd1
	str	r2, [fp, #-188]	@ tmp145, stIFmdDectCfg.stPqFmdHistbinThd.u32Hist_thd2
	str	lr, [fp, #-184]	@ tmp146, stIFmdDectCfg.stPqFmdHistbinThd.u32Hist_thd3
	str	r7, [fp, #-92]	@ tmp147, stIFmdDectCfg.stPqFmdItdiffThd.u32Itdiff_vthd0
	mov	r7, #15	@ tmp151,
	str	ip, [fp, #-84]	@ tmp144, stIFmdDectCfg.stPqFmdItdiffThd.u32Itdiff_vthd2
	str	r7, [fp, #-68]	@ tmp151, stIFmdDectCfg.stPqFmdLashThd.u32Edge_thd
	mov	r7, #90	@ tmp163,
	str	r2, [fp, #-80]	@ tmp145, stIFmdDectCfg.stPqFmdItdiffThd.u32Itdiff_vthd3
	str	r7, [fp, #-152]	@ tmp163, stIFmdDectCfg.stPqFmdPccThd.u32Coring_tkr
	mov	r7, #128	@ tmp168,
	str	r2, [fp, #-64]	@ tmp145, stIFmdDectCfg.stPqFmdLashThd.u32Lasi_mov_thr
	str	r7, [fp, #-132]	@ tmp168, stIFmdDectCfg.stPqFmdPccThd.u32Pcc_vthd3
	mov	r7, #50	@ tmp169,
	str	r3, [fp, #-60]	@ tmp154, stIFmdDectCfg.stPqFmdLashThd.u32LasiTxtAlpha
	str	r3, [fp, #-56]	@ tmp154, stIFmdDectCfg.stPqFmdLashThd.u32LasiTxtCoring
	str	r3, [fp, #-52]	@ tmp154, stIFmdDectCfg.stPqFmdLashThd.u32LasiTxtThd0
	str	r3, [fp, #-48]	@ tmp154, stIFmdDectCfg.stPqFmdLashThd.u32LasiTxtThd1
	str	r3, [fp, #-44]	@ tmp154, stIFmdDectCfg.stPqFmdLashThd.u32LasiTxtThd2
	str	r3, [fp, #-40]	@ tmp154, stIFmdDectCfg.stPqFmdLashThd.u32LasiTxtThd3
	str	ip, [fp, #-108]	@ tmp144, stIFmdDectCfg.stPqFmdPccBlk.u32Coring_blk
	str	ip, [fp, #-156]	@ tmp144, stIFmdDectCfg.stPqFmdPccThd.u32Coring_norm
	str	ip, [fp, #-148]	@ tmp144, stIFmdDectCfg.stPqFmdPccThd.u32Pcc_hthd
	mov	ip, #30	@ tmp177,
	str	r2, [fp, #-140]	@ tmp145, stIFmdDectCfg.stPqFmdPccThd.u32Pcc_vthd1
	str	lr, [fp, #-136]	@ tmp146, stIFmdDectCfg.stPqFmdPccThd.u32Pcc_vthd2
	str	r5, [fp, #-196]	@ tmp143, stIFmdDectCfg.stPqFmdHistbinThd.u32Hist_thd0
	str	r7, [fp, #-160]	@ tmp169, stIFmdDectCfg.stPqFmdPccThd.u32Mov_coring_tkr
	str	r5, [fp, #-88]	@ tmp143, stIFmdDectCfg.stPqFmdItdiffThd.u32Itdiff_vthd1
	str	r6, [fp, #-72]	@ tmp152, stIFmdDectCfg.stPqFmdLashThd.u32Lasi_thd
	str	r4, [fp, #-228]	@ tmp137, stIFmdDectCfg.stPqFmdCtrl.u32ifmd_en
	str	r4, [fp, #-212]	@ tmp137, stIFmdDectCfg.stPqFmdCtrl.u32Fod_en_mode
	str	r4, [fp, #-220]	@ tmp137, stIFmdDectCfg.stPqFmdCtrl.u32Pd22_en
	str	r4, [fp, #-224]	@ tmp137, stIFmdDectCfg.stPqFmdCtrl.u32Pd32_en
	str	r4, [fp, #-208]	@ tmp137, stIFmdDectCfg.stPqFmdCtrl.u32Edge_smooth_en
	str	r4, [fp, #-216]	@ tmp137, stIFmdDectCfg.stPqFmdCtrl.u32Pd22_mode
	str	r6, [fp, #-112]	@ tmp152, stIFmdDectCfg.stPqFmdPccBlk.u32Mov_coring_blk
	str	lr, [fp, #-96]	@ tmp146, stIFmdDectCfg.stPqFmdUmThd.u32Um_thd2
	mov	lr, #6	@ tmp175,
	str	r6, [fp, #-164]	@ tmp152, stIFmdDectCfg.stPqFmdPccThd.u32Mov_coring_norm
	str	r5, [fp, #-104]	@ tmp143, stIFmdDectCfg.stPqFmdUmThd.u32Um_thd0
	str	lr, [fp, #-200]	@ tmp175, stIFmdDectCfg.stPqFmdCtrl.u32Bitsmov2r
	str	r2, [fp, #-204]	@ tmp145, stIFmdDectCfg.stPqFmdCtrl.u32Edge_smooth_ratio
	str	ip, [fp, #-172]	@ tmp177, stIFmdDectCfg.stPqFmdHistbinThd.u32Diff_movblk_thd
	str	r2, [fp, #-100]	@ tmp145, stIFmdDectCfg.stPqFmdUmThd.u32Um_thd1
	str	r3, [fp, #-36]	@ tmp154, stIFmdDectCfg.stPqFmdRegion.u32Region1YStt
	str	r3, [fp, #-32]	@ tmp154, stIFmdDectCfg.stPqFmdRegion.u32Region1YEnd
	bl	PQ_HAL_SetIFmdRegist	@
	cmp	r0, #0	@ s32Ret
	bne	.L420	@,
.L418:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L420:
	mov	r0, r4	@, tmp137
	mov	r1, #41	@,
	ldr	r2, .L421	@,
	mov	r3, #171	@,
	movw	lr, #:lower16:.LC1	@ tmp183,
	movt	lr, #:upper16:.LC1	@ tmp183,
	str	lr, [sp, #0]	@ tmp183,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35950,
	b	.L418	@
.L422:
	.align	2
.L421:
	.word	.LANCHOR1+172
	.fnend
	.size	PQ_MNG_IFMD_HardwareParaInit, .-PQ_MNG_IFMD_HardwareParaInit
	.align	2
	.global	PQ_MNG_InitIfmd
	.type	PQ_MNG_InitIfmd, %function
PQ_MNG_InitIfmd:
	.fnstart
.LFB1396:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp222,
	movt	r4, #:upper16:.LANCHOR0	@ tmp222,
	ldr	r3, [r4, #0]	@ sg_bIFmdInitFlag, sg_bIFmdInitFlag
	cmp	r3, #1	@ sg_bIFmdInitFlag,
	moveq	r0, #0	@ D.35993,
	beq	.L425	@,
	cmp	r0, #0	@ pstPqParam,
	beq	.L438	@,
	add	r0, r0, #37888	@ ivtmp.1433, pstPqParam,
	movw	r1, #:lower16:-131071	@ tmp224,
	add	r0, r0, #244	@ ivtmp.1433, ivtmp.1433,
	movt	r1, #:upper16:-131071	@ tmp224,
	mov	r2, #0	@ i,
	b	.L430	@
.L428:
	ldr	r5, [r3, #-12]	@ <variable>.u32RegAddr, <variable>.u32RegAddr
	ldr	ip, [r0, #16]	@ u32IPDetect, <variable>.u32Value
	cmp	r5, r1	@ <variable>.u32RegAddr, tmp224
	ldrb	r0, [r3, #-8]	@ zero_extendqisi2	@ u8Lsb, <variable>.u8Lsb
	ldrb	lr, [r3, #-7]	@ zero_extendqisi2	@ u8Msb, <variable>.u8Msb
	beq	.L439	@,
.L435:
	add	r2, r2, #1	@ i, tmp225,
	add	r0, r3, #16	@ ivtmp.1433, tmp226,
	cmp	r2, #2048	@ i,
	beq	.L427	@,
.L430:
	ldr	lr, [r0, #-12]	@ <variable>.u32RegAddr, <variable>.u32RegAddr
	add	r3, r0, #16	@ tmp226, ivtmp.1433,
	add	r2, r2, #1	@ tmp225, i,
	ldr	ip, [r0, #0]	@ u32IPDetect, <variable>.u32Value
	cmp	lr, r1	@ <variable>.u32RegAddr, tmp224
	ldrb	r5, [r0, #-7]	@ zero_extendqisi2	@ u8Msb, <variable>.u8Msb
	ldrb	lr, [r0, #-8]	@ zero_extendqisi2	@ u8Lsb, <variable>.u8Lsb
	bne	.L428	@,
	cmp	lr, #0	@ u8Lsb,
	bne	.L428	@,
	cmp	r5, #1	@ u8Msb,
	bne	.L428	@,
.L429:
	str	ip, [r4, #4]	@ u32IPDetect, sg_u32IPDetect
.L432:
	bl	PQ_MNG_IFMD_HardwareParaInit	@
	mov	r5, r0	@ s32Ret,
	bl	PQ_MNG_IFMD_SofewareParaInit	@
	orrs	r0, r0, r5	@ tmp213,, s32Ret
	moveq	r3, #1	@ tmp219,
	streq	r3, [r4, #0]	@ tmp219, sg_bIFmdInitFlag
	bne	.L440	@,
.L425:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L439:
	cmp	r0, #0	@ u8Lsb,
	bne	.L435	@,
	cmp	lr, #1	@ u8Msb,
	bne	.L435	@,
	b	.L429	@
.L438:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L441	@,
	movw	r3, #2226	@,
	movw	ip, #:lower16:.LC2	@ tmp207,
	movt	ip, #:upper16:.LC2	@ tmp207,
	str	ip, [sp, #0]	@ tmp207,
	bl	HI_LogOut	@
.L427:
	mov	r1, #0	@ tmp212,
	str	r1, [r4, #4]	@ tmp212, sg_u32IPDetect
	b	.L432	@
.L440:
	mov	r0, #1	@,
	mov	r1, #41	@,
	ldr	r2, .L441+4	@,
	movw	r3, #274	@,
	movw	ip, #:lower16:.LC3	@ tmp217,
	movt	ip, #:upper16:.LC3	@ tmp217,
	str	ip, [sp, #0]	@ tmp217,
	bl	HI_LogOut	@
	mvn	r0, #0	@ D.35993,
	b	.L425	@
.L442:
	.align	2
.L441:
	.word	.LANCHOR1+204
	.word	.LANCHOR1+232
	.fnend
	.size	PQ_MNG_InitIfmd, .-PQ_MNG_InitIfmd
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	C.439.36258, %object
	.size	C.439.36258, 100
C.439.36258:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	1
	.type	__func__.37483, %object
	.size	__func__.37483, 24
__func__.37483:
	.ascii	"PQ_MNG_IFMD_SetIPDetect\000"
	.type	C.457.36426, %object
	.size	C.457.36426, 40
C.457.36426:
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.type	g_u32PDTypeNum, %object
	.size	g_u32PDTypeNum, 8
g_u32PDTypeNum:
	.word	32
	.word	22
	.type	__func__.35938, %object
	.size	__func__.35938, 29
__func__.35938:
	.ascii	"PQ_MNG_IFMD_HardwareParaInit\000"
	.space	3
	.type	__func__.37458, %object
	.size	__func__.37458, 25
__func__.37458:
	.ascii	"PQ_MNG_IFMD_FindIPDetect\000"
	.space	3
	.type	__func__.35989, %object
	.size	__func__.35989, 16
__func__.35989:
	.ascii	"PQ_MNG_InitIfmd\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"Set IPDetect Failure\012\000"
	.space	2
.LC1:
	.ascii	"set ifmd register is faild\012\000"
.LC2:
	.ascii	"pointer is NULL!\012\000"
	.space	2
.LC3:
	.ascii	"ifmd init failed\012\000"
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	sg_bIFmdInitFlag, %object
	.size	sg_bIFmdInitFlag, 4
sg_bIFmdInitFlag:
	.space	4
	.type	sg_u32IPDetect, %object
	.size	sg_u32IPDetect, 4
sg_u32IPDetect:
	.space	4
	.type	sgIfmdTotalSoftParaN, %object
	.size	sgIfmdTotalSoftParaN, 7808
sgIfmdTotalSoftParaN:
	.space	7808
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
