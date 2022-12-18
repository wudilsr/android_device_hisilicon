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
	.file	"pq_mng_scaler.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_mng_scaler)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/mng/.pq_mng_scaler.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/mng/pq_mng_scaler.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/mng/pq_mng_scaler.o -O2 -Wall -Wundef
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

	.global	__aeabi_uidiv
	.text
	.align	2
	.global	PQ_MNG_GetVdpScalerCoef
	.type	PQ_MNG_GetVdpScalerCoef, %function
PQ_MNG_GetVdpScalerCoef:
	.fnstart
.LFB656:
	@ args = 0, pretend = 0, frame = 16
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
	cmp	r1, #0	@ pvCoefAddrY,
	cmpne	r2, #0	@, pvCoefAddrC,
	mov	r5, r1	@ pvCoefAddrY, pvCoefAddrY
	mov	r4, r0	@ pstScalerInfo, pstScalerInfo
	bne	.L40	@,
.L2:
	mvn	r0, #0	@ D.24228,
.L35:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L40:
	ldr	r1, [r0, #12]	@ D.24231, <variable>.u32YRatio
	cmp	r1, #0	@ D.24231,
	beq	.L2	@,
	ldr	r6, [r0, #16]	@ u32RatioCH, <variable>.u32CRatio
	cmp	r6, #0	@ u32RatioCH,
	beq	.L2	@,
	ldr	r3, [r0, #20]	@ D.24236, <variable>.enInFmt
	cmp	r3, #0	@ D.24236,
	beq	.L41	@,
	cmp	r3, #1	@ D.24236,
	bne	.L6	@,
	ldr	r3, [r0, #24]	@ <variable>.enOutFmt, <variable>.enOutFmt
	cmp	r3, #0	@ <variable>.enOutFmt,
	moveq	r7, r6, asl #1	@ u32RatioCV, u32RatioCH,
	beq	.L5	@,
	cmp	r3, #2	@ <variable>.enOutFmt,
	moveq	r7, r6	@ u32RatioCV, u32RatioCH
	moveq	r6, r6, lsr #1	@ u32RatioCH, u32RatioCH,
	beq	.L5	@,
.L10:
	mov	r7, r6	@ u32RatioCV, u32RatioCH
.L5:
	ldr	r3, [r4, #0]	@ <variable>.bHorizontal, <variable>.bHorizontal
	cmp	r3, #0	@ <variable>.bHorizontal,
	beq	.L11	@,
	mov	r0, #104857600	@,
	str	r2, [fp, #-60]	@,
	bl	__aeabi_uidiv	@
	mov	r1, r6	@, u32RatioCH
	mov	r8, r0	@ u32ZmeRatioY,
	mov	r0, #104857600	@,
	bl	__aeabi_uidiv	@
	ldr	r2, [fp, #-60]	@,
	mov	r3, #0	@ enZmeTypeY,
	mov	r1, #2	@,
	str	r1, [fp, #-52]	@, %sfp
.L12:
	cmp	r8, #100	@ u32ZmeRatioY,
	movhi	r8, #0	@ enZmeCoefRatioY,
	bhi	.L14	@,
	moveq	r8, #1	@ enZmeCoefRatioY,
	beq	.L14	@,
	cmp	r8, #74	@ u32ZmeRatioY,
	movhi	r8, #2	@ enZmeCoefRatioY,
	bhi	.L14	@,
	cmp	r8, #49	@ u32ZmeRatioY,
	movhi	r8, #3	@ enZmeCoefRatioY,
	bhi	.L14	@,
	cmp	r8, #32	@ u32ZmeRatioY,
	movhi	r8, #4	@ enZmeCoefRatioY,
	bhi	.L14	@,
	cmp	r8, #24	@ u32ZmeRatioY,
	movhi	r8, #5	@ enZmeCoefRatioY,
	movls	r8, #6	@ enZmeCoefRatioY,
.L14:
	cmp	r0, #100	@ u32ZmeRatioC,
	movhi	r6, #0	@,
	strhi	r6, [fp, #-48]	@, %sfp
	bhi	.L21	@,
	moveq	r7, #1	@,
	streq	r7, [fp, #-48]	@, %sfp
	beq	.L21	@,
	cmp	r0, #74	@ u32ZmeRatioC,
	movhi	r0, #2	@,
	strhi	r0, [fp, #-48]	@, %sfp
	bhi	.L21	@,
	cmp	r0, #49	@ u32ZmeRatioC,
	movhi	r1, #3	@,
	strhi	r1, [fp, #-48]	@, %sfp
	bhi	.L21	@,
	cmp	r0, #32	@ u32ZmeRatioC,
	movhi	r6, #4	@,
	strhi	r6, [fp, #-48]	@, %sfp
	bhi	.L21	@,
	cmp	r0, #24	@ u32ZmeRatioC,
	movhi	r0, #5	@,
	movls	r0, #6	@,
	str	r0, [fp, #-48]	@, %sfp
.L21:
	ldr	ip, [r4, #4]	@ prephitmp.249, <variable>.bYUV
	cmp	ip, #0	@ prephitmp.249,
	beq	.L27	@,
	mov	r0, #6	@ tmp232,
	ldr	r1, [r4, #8]	@ <variable>.b3Dtype, <variable>.b3Dtype
	mla	r8, r0, r8, r3	@ tmp233, tmp232, enZmeCoefRatioY, enZmeTypeY
	movw	r9, #:lower16:.LANCHOR0	@ tmp455,
	movt	r9, #:upper16:.LANCHOR0	@ tmp455,
	cmp	r1, #0	@ <variable>.b3Dtype,
	ldr	r0, [r9, r8, asl #2]	@ ps32CoefTbl, paZmeCoefYuv
	addne	r8, r9, r8, asl #2	@, tmp241, tmp455, tmp233,
	ldrne	r0, [r8, #168]	@ ps32CoefTbl, paZme3DCoefYuv
.L28:
	add	r7, r9, r3, asl #2	@, tmp263, tmp455, enZmeTypeY,
	movw	lr, #:lower16:-1431655765	@ tmp271,
	movt	lr, #:upper16:-1431655765	@ tmp271,
	ldr	r6, [r7, #672]	@ tmp265, au32ZmeTap
	add	r8, r6, r6, asl #3	@, tmp268, tmp265, tmp265,
	mov	r3, r8, asl #1	@ tmp269, tmp268,
	umull	r7, sl, lr, r3	@, tmp270, tmp271, tmp269
	movs	r6, sl, lsr #3	@ u32Size, tmp270,
	beq	.L29	@,
	mov	ip, #0	@ i,
	mov	r3, r5	@ ivtmp.287, pvCoefAddrY
	mov	r7, r6	@ u32Size, u32Size
	mov	sl, r2	@ pvCoefAddrC, pvCoefAddrC
	str	r4, [fp, #-56]	@ pstScalerInfo, %sfp
.L30:
	ldr	r8, [r0, #0]	@ tmp272,* ps32CoefTbl
	add	ip, ip, #1	@ i, i,
	ldrh	lr, [r3, #0]	@,* ivtmp.287
	cmp	r7, ip	@ u32Size, i
	ldrb	r4, [r3, #8]	@ zero_extendqisi2	@,
	bfi	lr, r8, #0, #10	@ tmp273, tmp272,,
	strh	lr, [r3, #0]	@ movhi	@ tmp273,* ivtmp.287
	ldr	r1, [r0, #4]	@ tmp275,
	ldr	r2, [r3, #0]	@ tmp276,* ivtmp.287
	ldrh	lr, [r3, #10]	@,
	bfi	r2, r1, #10, #10	@ tmp276, tmp275,,
	str	r2, [r3, #0]	@ tmp276,* ivtmp.287
	ldr	r6, [r0, #8]	@ tmp277,
	ldrh	r5, [r3, #2]	@,
	ldrb	r2, [r3, #12]	@ zero_extendqisi2	@,
	bfi	r5, r6, #4, #10	@ tmp278, tmp277,,
	strh	r5, [r3, #2]	@ movhi	@ tmp278,
	ldr	r1, [r0, #12]	@ s32Tmp,
	ldrb	r5, [r3, #3]	@ zero_extendqisi2	@,
	mov	r8, r1, asr #2	@ tmp282, s32Tmp,
	bfi	r5, r1, #6, #2	@ tmp280, s32Tmp,,
	strb	r8, [r3, #4]	@ tmp282, <variable>.bits_38
	strb	r5, [r3, #3]	@ tmp280,
	ldr	r1, [r3, #4]	@ tmp285,
	ldr	r6, [r0, #16]	@ tmp284,
	bfi	r1, r6, #8, #10	@ tmp285, tmp284,,
	str	r1, [r3, #4]	@ tmp285,
	ldr	r5, [r0, #20]	@ tmp286,
	ldrh	r8, [r3, #6]	@,
	bfi	r8, r5, #2, #10	@ tmp287, tmp286,,
	strh	r8, [r3, #6]	@ movhi	@ tmp287,
	ldr	r6, [r0, #24]	@ s32Tmp.326,
	ldrb	r5, [r3, #7]	@ zero_extendqisi2	@,
	mov	r1, r6, asr #4	@ tmp291, s32Tmp.326,
	bfi	r5, r6, #4, #4	@ tmp289, s32Tmp.326,,
	bfi	r4, r1, #0, #6	@ tmp292, tmp291,,
	strb	r5, [r3, #7]	@ tmp289,
	strb	r4, [r3, #8]	@ tmp292,
	ldr	r8, [r0, #28]	@ tmp294,
	ldrh	r1, [r3, #8]	@,
	bfi	r1, r8, #6, #10	@ tmp295, tmp294,,
	strh	r1, [r3, #8]	@ movhi	@ tmp295,
	ldr	r5, [r0, #32]	@ tmp297,
	bfi	lr, r5, #0, #10	@ tmp298, tmp297,,
	strh	lr, [r3, #10]	@ movhi	@ tmp298,
	ldr	r4, [r0, #36]	@ s32Tmp.334,
	ldrb	r8, [r3, #11]	@ zero_extendqisi2	@,
	mov	r6, r4, asr #6	@ tmp302, s32Tmp.334,
	bfi	r8, r4, #2, #6	@ tmp300, s32Tmp.334,,
	bfi	r2, r6, #0, #4	@ tmp303, tmp302,,
	strb	r8, [r3, #11]	@ tmp300,
	strb	r2, [r3, #12]	@ tmp303,
	mov	r2, #0	@,
	ldr	r1, [r0, #40]	@ tmp305,
	ldrh	lr, [r3, #12]	@,
	bfi	lr, r1, #4, #10	@ tmp306, tmp305,,
	strh	lr, [r3, #12]	@ movhi	@ tmp306,
	ldr	r5, [r0, #44]	@ tmp308,
	add	r0, r0, #48	@ ps32CoefTbl, ps32CoefTbl,
	ldr	r4, [r3, #12]	@ tmp309,
	bfi	r4, r5, #14, #10	@ tmp309, tmp308,,
	str	r4, [r3, #12]	@ tmp309,
	strb	r2, [r3, #15]	@, <variable>.bits_12
	add	r3, r3, #16	@ ivtmp.287, ivtmp.287,
	bhi	.L30	@,
	ldr	r4, [fp, #-56]	@ pstScalerInfo, %sfp
	mov	r2, sl	@ pvCoefAddrC, pvCoefAddrC
	ldr	ip, [r4, #4]	@ prephitmp.249, <variable>.bYUV
	ldr	r1, [r4, #8]	@ <variable>.b3Dtype, <variable>.b3Dtype
.L29:
	cmp	ip, #0	@ prephitmp.249,
	beq	.L31	@,
	ldr	r3, [fp, #-48]	@, %sfp
	mov	r7, #6	@ tmp314,
	ldr	r5, [fp, #-52]	@, %sfp
	cmp	r1, #0	@ <variable>.b3Dtype,
	movw	r0, #:lower16:.LANCHOR0	@ tmp312,
	movt	r0, #:upper16:.LANCHOR0	@ tmp312,
	mla	sl, r7, r3, r5	@ tmp315, tmp314,,
	addne	r0, r0, sl, asl #2	@, tmp323, tmp312, tmp315,
	ldr	r3, [r9, sl, asl #2]	@ ps32CoefTbl.300, paZmeCoefYuv
	ldrne	r3, [r0, #168]	@ ps32CoefTbl.300, paZme3DCoefYuv
.L32:
	ldr	r0, [fp, #-52]	@, %sfp
	movw	lr, #:lower16:-1431655765	@ tmp353,
	movt	lr, #:upper16:-1431655765	@ tmp353,
	add	r8, r9, r0, asl #2	@, tmp345, tmp455,,
	ldr	r6, [r8, #672]	@ tmp347, au32ZmeTap
	add	r5, r6, r6, asl #3	@, tmp350, tmp347, tmp347,
	mov	r9, r5, asl #1	@ tmp351, tmp350,
	umull	r6, r7, lr, r9	@, tmp352, tmp353, tmp351
	movs	r9, r7, lsr #3	@ u32Size.308, tmp352,
	beq	.L33	@,
	mov	r1, #0	@ i,
	mov	sl, r4	@ pstScalerInfo, pstScalerInfo
	mov	r8, r1	@ tmp457, i
.L34:
	ldr	ip, [r3, #0]	@ tmp354,* ps32CoefTbl.300
	add	r1, r1, #1	@ i, i,
	ldrh	r7, [r2, #0]	@,* ivtmp.268
	cmp	r9, r1	@ u32Size.308, i
	ldrb	r4, [r2, #8]	@ zero_extendqisi2	@,
	bfi	r7, ip, #0, #10	@ tmp355, tmp354,,
	strh	r7, [r2, #0]	@ movhi	@ tmp355,* ivtmp.268
	ldr	r6, [r3, #4]	@ tmp357,
	ldr	r0, [r2, #0]	@ tmp358,* ivtmp.268
	ldrh	ip, [r2, #10]	@,
	bfi	r0, r6, #10, #10	@ tmp358, tmp357,,
	str	r0, [r2, #0]	@ tmp358,* ivtmp.268
	ldr	r5, [r3, #8]	@ tmp359,
	ldrh	lr, [r2, #2]	@,
	ldrb	r0, [r2, #12]	@ zero_extendqisi2	@,
	bfi	lr, r5, #4, #10	@ tmp360, tmp359,,
	strh	lr, [r2, #2]	@ movhi	@ tmp360,
	ldr	r6, [r3, #12]	@ s32Tmp,
	ldrb	r5, [r2, #3]	@ zero_extendqisi2	@,
	mov	r7, r6, asr #2	@ tmp364, s32Tmp,
	bfi	r5, r6, #6, #2	@ tmp362, s32Tmp,,
	strb	r7, [r2, #4]	@ tmp364, <variable>.bits_38
	strb	r5, [r2, #3]	@ tmp362,
	ldr	r7, [r2, #4]	@ tmp367,
	ldr	lr, [r3, #16]	@ tmp366,
	bfi	r7, lr, #8, #10	@ tmp367, tmp366,,
	str	r7, [r2, #4]	@ tmp367,
	ldr	r6, [r3, #20]	@ tmp368,
	ldrh	r5, [r2, #6]	@,
	bfi	r5, r6, #2, #10	@ tmp369, tmp368,,
	strh	r5, [r2, #6]	@ movhi	@ tmp369,
	ldr	lr, [r3, #24]	@ s32Tmp.354,
	ldrb	r5, [r2, #7]	@ zero_extendqisi2	@,
	mov	r7, lr, asr #4	@ tmp373, s32Tmp.354,
	bfi	r5, lr, #4, #4	@ tmp371, s32Tmp.354,,
	bfi	r4, r7, #0, #6	@ tmp374, tmp373,,
	strb	r5, [r2, #7]	@ tmp371,
	strb	r4, [r2, #8]	@ tmp374,
	ldr	r6, [r3, #28]	@ tmp376,
	ldrh	lr, [r2, #8]	@,
	bfi	lr, r6, #6, #10	@ tmp377, tmp376,,
	strh	lr, [r2, #8]	@ movhi	@ tmp377,
	ldr	r7, [r3, #32]	@ tmp379,
	bfi	ip, r7, #0, #10	@ tmp380, tmp379,,
	strh	ip, [r2, #10]	@ movhi	@ tmp380,
	ldr	r4, [r3, #36]	@ s32Tmp.362,
	ldrb	r6, [r2, #11]	@ zero_extendqisi2	@,
	mov	r5, r4, asr #6	@ tmp384, s32Tmp.362,
	bfi	r6, r4, #2, #6	@ tmp382, s32Tmp.362,,
	bfi	r0, r5, #0, #4	@ tmp385, tmp384,,
	strb	r6, [r2, #11]	@ tmp382,
	strb	r0, [r2, #12]	@ tmp385,
	ldr	lr, [r3, #40]	@ tmp387,
	ldrh	r7, [r2, #12]	@,
	bfi	r7, lr, #4, #10	@ tmp388, tmp387,,
	strh	r7, [r2, #12]	@ movhi	@ tmp388,
	ldr	ip, [r3, #44]	@ tmp390,
	add	r3, r3, #48	@ ps32CoefTbl.300, ps32CoefTbl.300,
	ldr	r4, [r2, #12]	@ tmp391,
	bfi	r4, ip, #14, #10	@ tmp391, tmp390,,
	str	r4, [r2, #12]	@ tmp391,
	strb	r8, [r2, #15]	@ tmp457, <variable>.bits_12
	add	r2, r2, #16	@ ivtmp.268, ivtmp.268,
	bhi	.L34	@,
	ldr	ip, [sl, #4]	@ prephitmp.249, <variable>.bYUV
	mov	r4, sl	@ pstScalerInfo, pstScalerInfo
	ldr	r1, [sl, #8]	@ <variable>.b3Dtype, <variable>.b3Dtype
.L33:
	ldr	r5, [r4, #0]	@ temp.309, <variable>.bHorizontal
	movw	r2, #:lower16:.LANCHOR1	@ tmp394,
	ldr	sl, [r4, #24]	@ <variable>.enOutFmt, <variable>.enOutFmt
	movt	r2, #:upper16:.LANCHOR1	@ tmp394,
	ldr	r8, [r4, #12]	@ <variable>.u32YRatio, <variable>.u32YRatio
	mov	r0, #0	@ D.24228,
	rsb	r6, r5, r5, asl #3	@, tmp397, temp.309, temp.309,
	ldr	r7, [r4, #16]	@ <variable>.u32CRatio, <variable>.u32CRatio
	ldr	r4, [r4, #20]	@ <variable>.enInFmt, <variable>.enInFmt
	add	r3, r2, r6, asl #2	@, tmp399, tmp394, tmp397,
	str	r5, [r2, r6, asl #2]	@ temp.309, <variable>.bHorizontal
	str	sl, [r3, #24]	@ <variable>.enOutFmt, <variable>.enOutFmt
	str	ip, [r3, #4]	@ prephitmp.249, <variable>.bYUV
	str	r1, [r3, #8]	@ <variable>.b3Dtype, <variable>.b3Dtype
	str	r8, [r3, #12]	@ <variable>.u32YRatio, <variable>.u32YRatio
	str	r7, [r3, #16]	@ <variable>.u32CRatio, <variable>.u32CRatio
	str	r4, [r3, #20]	@ <variable>.enInFmt, <variable>.enInFmt
	b	.L35	@
.L31:
	ldr	sl, [fp, #-48]	@, %sfp
	mov	r8, #6	@ tmp327,
	ldr	r0, [fp, #-52]	@, %sfp
	cmp	r1, #0	@ <variable>.b3Dtype,
	mla	lr, r8, sl, r0	@ tmp328, tmp327,,
	add	r6, r9, lr, asl #2	@, tmp331, tmp455, tmp328,
	ldr	r3, [r6, #336]	@ ps32CoefTbl.300, paZmeCoefRgb
	ldrne	r3, [r6, #504]	@ ps32CoefTbl.300, paZme3DCoefRgb
	b	.L32	@
.L27:
	mov	r9, #6	@ tmp245,
	ldr	r1, [r4, #8]	@ <variable>.b3Dtype, <variable>.b3Dtype
	mla	r7, r9, r8, r3	@ tmp246, tmp245, enZmeCoefRatioY, enZmeTypeY
	movw	r9, #:lower16:.LANCHOR0	@ tmp455,
	movt	r9, #:upper16:.LANCHOR0	@ tmp455,
	cmp	r1, #0	@ <variable>.b3Dtype,
	add	r6, r9, r7, asl #2	@, tmp249, tmp455, tmp246,
	ldr	r0, [r6, #336]	@ ps32CoefTbl, paZmeCoefRgb
	ldrne	r0, [r6, #504]	@ ps32CoefTbl, paZme3DCoefRgb
	b	.L28	@
.L11:
	mov	r0, #409600	@,
	str	r2, [fp, #-60]	@,
	bl	__aeabi_uidiv	@
	mov	r1, r7	@, u32RatioCV
	mov	r8, r0	@ u32ZmeRatioY,
	mov	r0, #409600	@,
	bl	__aeabi_uidiv	@
	mov	r1, #3	@,
	mov	r3, #1	@ enZmeTypeY,
	str	r1, [fp, #-52]	@, %sfp
	ldr	r2, [fp, #-60]	@,
	b	.L12	@
.L41:
	ldr	r3, [r0, #24]	@ D.24238, <variable>.enOutFmt
	cmp	r3, #1	@ D.24238,
	moveq	r7, r6, lsr #1	@ u32RatioCV, u32RatioCH,
	beq	.L5	@,
	cmp	r3, #2	@ D.24238,
	moveq	r6, r6, lsr #1	@ u32RatioCH, u32RatioCH,
	moveq	r7, r6	@ u32RatioCV, u32RatioCH
	bne	.L10	@,
	b	.L5	@
.L6:
	cmp	r3, #2	@ D.24236,
	bne	.L10	@,
	ldr	r3, [r0, #24]	@ prephitmp.252, <variable>.enOutFmt
	cmp	r3, #0	@ prephitmp.252,
	moveq	r6, r6, asl #1	@ u32RatioCH, u32RatioCH,
	moveq	r7, r6	@ u32RatioCV, u32RatioCH
	beq	.L5	@,
	cmp	r3, #1	@ prephitmp.252,
	moveq	r7, r6	@ u32RatioCV, u32RatioCH
	moveq	r6, r6, asl #1	@ u32RatioCH, u32RatioCH,
	bne	.L10	@,
	b	.L5	@
	.fnend
	.size	PQ_MNG_GetVdpScalerCoef, .-PQ_MNG_GetVdpScalerCoef
	.align	2
	.global	VPSS_DRV_Conver_ScaleCoef
	.type	VPSS_DRV_Conver_ScaleCoef, %function
VPSS_DRV_Conver_ScaleCoef:
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
	cmp	r0, #0	@ s32Value
	movlt	r0, r0, asl #22	@ D.24296, s32Value,
	movlt	r0, r0, lsr #22	@ D.24296, D.24296,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	VPSS_DRV_Conver_ScaleCoef, .-VPSS_DRV_Conver_ScaleCoef
	.align	2
	.global	vpss_sclverlumacoef_to_dut
	.type	vpss_sclverlumacoef_to_dut, %function
vpss_sclverlumacoef_to_dut:
	.fnstart
.LFB658:
	@ args = 0, pretend = 0, frame = 8
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
	mov	r3, #0	@ tmp161,
	add	r4, r1, #408	@ D.24915, ivtmp.432,
	str	r3, [fp, #-24]	@ tmp161, temp
	b	.L47	@
.L48:
	add	r1, r1, #24	@ ivtmp.432, ivtmp.432,
	ldr	ip, [fp, #-28]	@ temp, temp
	cmp	r1, r4	@ ivtmp.432, D.24915
	str	r2, [fp, #-24]	@ D.24621, temp
	add	r2, ip, r2, asl #16	@, tmp168, temp, D.24621,
	str	r2, [r0, r3, asl #2]	@ tmp168,* coef_start_addr
	add	r3, r3, #1	@ k, k.470,
	beq	.L62	@,
.L47:
	ldr	ip, [r1, #0]	@ temp.439,* ivtmp.432
	cmp	ip, #0	@ temp.439,
	movlt	ip, ip, asl #22	@ temp.443, temp.439,
	movlt	ip, ip, lsr #22	@ temp.443, temp.443,
	str	ip, [fp, #-28]	@ temp.443, temp
	ldr	r2, [r1, #4]	@ temp.444,
	add	ip, r3, #1	@ k.454, k,
	ldr	r5, [fp, #-28]	@ temp, temp
	cmp	r2, #0	@ temp.444,
	movlt	r2, r2, asl #22	@ temp.448, temp.444,
	movlt	r2, r2, lsr #22	@ temp.448, temp.448,
	str	r2, [fp, #-24]	@ temp.448, temp
	add	r2, r5, r2, asl #16	@, tmp177, temp, temp.448,
	str	r2, [r0, r3, asl #2]	@ tmp177,* coef_start_addr
	ldr	r3, [r1, #8]	@ temp.455,
	cmp	r3, #0	@ temp.455,
	movlt	r3, r3, asl #22	@ temp.459, temp.455,
	movlt	r3, r3, lsr #22	@ temp.459, temp.459,
	str	r3, [fp, #-28]	@ temp.459, temp
	ldr	r2, [r1, #12]	@ temp.460,
	add	r3, ip, #1	@ k.470, k.454,
	ldr	r5, [fp, #-28]	@ temp, temp
	cmp	r2, #0	@ temp.460,
	movlt	r2, r2, asl #22	@ temp.464, temp.460,
	movlt	r2, r2, lsr #22	@ temp.464, temp.464,
	str	r2, [fp, #-24]	@ temp.464, temp
	add	r2, r5, r2, asl #16	@, tmp186, temp, temp.464,
	str	r2, [r0, ip, asl #2]	@ tmp186,* coef_start_addr
	ldr	r2, [r1, #16]	@ temp.471,
	cmp	r2, #0	@ temp.471,
	movlt	r2, r2, asl #22	@ temp.475, temp.471,
	movlt	r2, r2, lsr #22	@ temp.475, temp.475,
	str	r2, [fp, #-28]	@ temp.475, temp
	ldr	r2, [r1, #20]	@ D.24319,
	cmp	r2, #0	@ D.24319,
	bge	.L48	@,
	mov	r2, r2, asl #22	@ D.24621, D.24319,
	add	r1, r1, #24	@ ivtmp.432, ivtmp.432,
	ldr	ip, [fp, #-28]	@ temp, temp
	cmp	r1, r4	@ ivtmp.432, D.24915
	mov	r2, r2, lsr #22	@ D.24621, D.24621,
	str	r2, [fp, #-24]	@ D.24621, temp
	add	r2, ip, r2, asl #16	@, tmp168, temp, D.24621,
	str	r2, [r0, r3, asl #2]	@ tmp168,* coef_start_addr
	add	r3, r3, #1	@ k, k.470,
	bne	.L47	@,
.L62:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
	.fnend
	.size	vpss_sclverlumacoef_to_dut, .-vpss_sclverlumacoef_to_dut
	.align	2
	.global	vpss_sclhorlumacoef_to_dut
	.type	vpss_sclhorlumacoef_to_dut, %function
vpss_sclhorlumacoef_to_dut:
	.fnstart
.LFB659:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #36
	sub	sp, sp, #36	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	sub	r3, fp, #68	@ tmp177,,
	mov	ip, #0	@ tmp146,
	add	r4, r3, #4	@ tmp180, tmp177,
	mov	r2, ip	@ i, tmp146
	mov	r8, ip	@ k, i
	str	ip, [r4], #4	@ tmp146, temp
	str	ip, [fp, #-68]	@ tmp146, temp
	str	ip, [r4], #4	@ tmp146, temp
	str	ip, [r4], #4	@ tmp146, temp
	str	ip, [r4], #4	@ tmp146, temp
	str	ip, [r4], #4	@ tmp146, temp
	str	ip, [r4], #4	@ tmp146, temp
	str	ip, [r4, #0]	@ tmp146, temp
.L65:
	mov	r5, r1	@ ivtmp.528, ivtmp.508
	mov	r7, #1	@ ivtmp.510,
	mov	ip, #0	@ ivtmp.507,
	b	.L74	@
.L68:
	cmp	ip, #5	@ ivtmp.507,
	beq	.L76	@,
	cmp	ip, #7	@ ivtmp.507,
	beq	.L77	@,
	cmp	r7, #7	@ ivtmp.510,
	bhi	.L72	@,
.L69:
	add	ip, ip, #1	@ ivtmp.507, ivtmp.507,
	add	r5, r5, #4	@ ivtmp.528, ivtmp.528,
	add	r7, r7, #1	@ ivtmp.510, ivtmp.510,
.L74:
	ldr	r4, [r5, #0]	@ D.24352,* ivtmp.528
	cmp	r4, #0	@ D.24352,
	mov	r6, r4	@ D.24627, D.24352
	movlt	r6, r4, asl #22	@ D.24627, D.24352,
	movlt	r6, r6, lsr #22	@ D.24627, D.24627,
	cmp	ip, #2	@ ivtmp.507,
	str	r6, [r3, ip, asl #2]	@ D.24627, temp
	bne	.L68	@,
	ldr	r4, [fp, #-64]	@ temp, temp
	ldr	r6, [fp, #-60]	@ temp, temp
	mov	r4, r4, asl #10	@ tmp161, temp,
	add	r4, r4, r6, asl #20	@, tmp163, tmp161, temp,
	ldr	r6, [fp, #-68]	@ temp, temp
	add	r4, r4, r6	@ tmp165, tmp163, temp
	str	r4, [r0, r8, asl #2]	@ tmp165,* coef_start_addr
	add	r8, r8, #1	@ k, k,
	b	.L69	@
.L76:
	ldr	r4, [fp, #-52]	@ temp, temp
	ldr	r6, [fp, #-48]	@ temp, temp
	mov	r4, r4, asl #10	@ tmp168, temp,
	add	r4, r4, r6, asl #20	@, tmp170, tmp168, temp,
	ldr	r6, [fp, #-56]	@ temp, temp
	add	r4, r4, r6	@ tmp172, tmp170, temp
	str	r4, [r0, r8, asl #2]	@ tmp172,* coef_start_addr
	add	r8, r8, #1	@ k, k,
	b	.L69	@
.L77:
	ldr	r4, [fp, #-40]	@ temp, temp
	ldr	ip, [fp, #-44]	@ temp, temp
	add	ip, ip, r4, asl #10	@, tmp176, temp, temp,
	str	ip, [r0, r8, asl #2]	@ tmp176,* coef_start_addr
	add	r8, r8, #1	@ k, k,
.L72:
	add	r2, r2, #1	@ i, i,
	add	r1, r1, #32	@ ivtmp.508, ivtmp.508,
	cmp	r2, #17	@ i,
	bne	.L65	@,
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	.fnend
	.size	vpss_sclhorlumacoef_to_dut, .-vpss_sclhorlumacoef_to_dut
	.align	2
	.global	PQ_MNG_GetVpssScalerCoef
	.type	PQ_MNG_GetVpssScalerCoef, %function
PQ_MNG_GetVpssScalerCoef:
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
	cmp	r1, #0	@ pvCoefAddrY,
	cmpne	r2, #0	@, pvCoefAddrC,
	mov	r4, r1	@ pvCoefAddrY, pvCoefAddrY
	mov	r5, r0	@ pstScalerInfo, pstScalerInfo
	bne	.L114	@,
.L79:
	mvn	r0, #0	@ D.24401,
.L112:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
.L114:
	ldr	r1, [r0, #12]	@ D.24404, <variable>.u32YRatio
	cmp	r1, #0	@ D.24404,
	beq	.L79	@,
	ldr	r6, [r0, #16]	@ u32RatioCH, <variable>.u32CRatio
	cmp	r6, #0	@ u32RatioCH,
	beq	.L79	@,
	ldr	r3, [r0, #20]	@ D.24409, <variable>.enInFmt
	cmp	r3, #0	@ D.24409,
	beq	.L115	@,
	cmp	r3, #1	@ D.24409,
	bne	.L83	@,
	ldr	r3, [r0, #24]	@ <variable>.enOutFmt, <variable>.enOutFmt
	cmp	r3, #0	@ <variable>.enOutFmt,
	moveq	sl, r6, asl #1	@ u32RatioCV, u32RatioCH,
	beq	.L82	@,
	cmp	r3, #2	@ <variable>.enOutFmt,
	moveq	sl, r6	@ u32RatioCV, u32RatioCH
	moveq	r6, r6, lsr #1	@ u32RatioCH, u32RatioCH,
	beq	.L82	@,
.L87:
	mov	sl, r6	@ u32RatioCV, u32RatioCH
.L82:
	ldr	r8, [r5, #0]	@ D.24433, <variable>.bHorizontal
	cmp	r8, #0	@ D.24433,
	beq	.L88	@,
	mov	r0, #104857600	@,
	str	r2, [fp, #-40]	@,
	bl	__aeabi_uidiv	@
	mov	r1, r6	@, u32RatioCH
	mov	sl, #2	@ enZmeTypeC,
	mov	r7, r0	@ u32ZmeRatioY,
	mov	r0, #104857600	@,
	bl	__aeabi_uidiv	@
	ldr	r2, [fp, #-40]	@,
	mov	r1, #0	@ enZmeTypeY,
.L89:
	cmp	r7, #100	@ u32ZmeRatioY,
	movhi	r3, #0	@ enZmeCoefRatioY,
	bhi	.L91	@,
	moveq	r3, #1	@ enZmeCoefRatioY,
	beq	.L91	@,
	cmp	r7, #74	@ u32ZmeRatioY,
	movhi	r3, #2	@ enZmeCoefRatioY,
	bhi	.L91	@,
	cmp	r7, #49	@ u32ZmeRatioY,
	movhi	r3, #3	@ enZmeCoefRatioY,
	bhi	.L91	@,
	cmp	r7, #32	@ u32ZmeRatioY,
	movhi	r3, #4	@ enZmeCoefRatioY,
	bhi	.L91	@,
	cmp	r7, #24	@ u32ZmeRatioY,
	movhi	r3, #5	@ enZmeCoefRatioY,
	movls	r3, #6	@ enZmeCoefRatioY,
.L91:
	cmp	r0, #100	@ u32ZmeRatioC,
	movhi	r7, #0	@ enZmeCoefRatioC,
	bhi	.L98	@,
	moveq	r7, #1	@ enZmeCoefRatioC,
	beq	.L98	@,
	cmp	r0, #74	@ u32ZmeRatioC,
	movhi	r7, #2	@ enZmeCoefRatioC,
	bhi	.L98	@,
	cmp	r0, #49	@ u32ZmeRatioC,
	movhi	r7, #3	@ enZmeCoefRatioC,
	bhi	.L98	@,
	cmp	r0, #32	@ u32ZmeRatioC,
	movhi	r7, #4	@ enZmeCoefRatioC,
	bhi	.L98	@,
	cmp	r0, #24	@ u32ZmeRatioC,
	movhi	r7, #5	@ enZmeCoefRatioC,
	movls	r7, #6	@ enZmeCoefRatioC,
.L98:
	mov	r0, #6	@ tmp180,
	ldr	r6, [r5, #4]	@ <variable>.bYUV, <variable>.bYUV
	mla	r3, r0, r3, r1	@ tmp181, tmp180, enZmeCoefRatioY, enZmeTypeY
	cmp	r6, #0	@ <variable>.bYUV,
	movw	r6, #:lower16:.LANCHOR0	@ tmp258,
	movt	r6, #:upper16:.LANCHOR0	@ tmp258,
	addeq	r3, r6, r3, asl #2	@, tmp188, tmp258, tmp185,
	ldrne	r1, [r6, r3, asl #2]	@ ps32CoefTbl, paZmeCoefYuv
	ldreq	r1, [r3, #336]	@ ps32CoefTbl, paZmeCoefRgb
	cmp	r8, #0	@ D.24433,
	beq	.L106	@,
	mov	r0, r4	@, pvCoefAddrY
	str	r2, [fp, #-40]	@,
	bl	vpss_sclhorlumacoef_to_dut	@
	ldr	r2, [fp, #-40]	@,
.L107:
	mov	r8, #6	@ tmp193,
	ldr	ip, [r5, #4]	@ <variable>.bYUV, <variable>.bYUV
	mla	r7, r8, r7, sl	@ tmp194, tmp193, enZmeCoefRatioC, enZmeTypeC
	cmp	ip, #0	@ <variable>.bYUV,
	ldr	r4, [r5, #0]	@ <variable>.bHorizontal, <variable>.bHorizontal
	addeq	r6, r6, r7, asl #2	@, tmp201, tmp258, tmp198,
	ldrne	r1, [r6, r7, asl #2]	@ ps32CoefTbl.556, paZmeCoefYuv
	ldreq	r1, [r6, #336]	@ ps32CoefTbl.556, paZmeCoefRgb
	cmp	r4, #0	@ <variable>.bHorizontal,
	beq	.L110	@,
	mov	r0, r2	@, pvCoefAddrC
	bl	vpss_sclhorlumacoef_to_dut	@
.L111:
	ldr	r2, [r5, #0]	@ temp.563, <variable>.bHorizontal
	movw	r3, #:lower16:.LANCHOR1	@ tmp204,
	ldr	r7, [r5, #24]	@ <variable>.enOutFmt, <variable>.enOutFmt
	movt	r3, #:upper16:.LANCHOR1	@ tmp204,
	ldr	r6, [r5, #4]	@ <variable>.bYUV, <variable>.bYUV
	mov	r0, #0	@ D.24401,
	rsb	r8, r2, r2, asl #3	@, tmp208, temp.563, temp.563,
	ldr	r4, [r5, #12]	@ <variable>.u32YRatio, <variable>.u32YRatio
	ldr	ip, [r5, #16]	@ <variable>.u32CRatio, <variable>.u32CRatio
	ldr	r1, [r5, #20]	@ <variable>.enInFmt, <variable>.enInFmt
	add	lr, r3, r8, asl #2	@, tmp210, tmp204, tmp208,
	str	r7, [lr, #80]	@ <variable>.enOutFmt, <variable>.enOutFmt
	str	r2, [lr, #56]	@ temp.563, <variable>.bHorizontal
	str	r6, [lr, #60]	@ <variable>.bYUV, <variable>.bYUV
	str	r4, [lr, #68]	@ <variable>.u32YRatio, <variable>.u32YRatio
	str	ip, [lr, #72]	@ <variable>.u32CRatio, <variable>.u32CRatio
	str	r1, [lr, #76]	@ <variable>.enInFmt, <variable>.enInFmt
	b	.L112	@
.L88:
	mov	r0, #409600	@,
	str	r2, [fp, #-40]	@,
	bl	__aeabi_uidiv	@
	mov	r1, sl	@, u32RatioCV
	mov	sl, #3	@ enZmeTypeC,
	mov	r7, r0	@ u32ZmeRatioY,
	mov	r0, #409600	@,
	bl	__aeabi_uidiv	@
	mov	r1, #1	@ enZmeTypeY,
	ldr	r2, [fp, #-40]	@,
	b	.L89	@
.L110:
	mov	r0, r2	@, pvCoefAddrC
	bl	vpss_sclverlumacoef_to_dut	@
	b	.L111	@
.L106:
	mov	r0, r4	@, pvCoefAddrY
	str	r2, [fp, #-40]	@,
	bl	vpss_sclverlumacoef_to_dut	@
	ldr	r2, [fp, #-40]	@,
	b	.L107	@
.L115:
	ldr	r3, [r0, #24]	@ D.24411, <variable>.enOutFmt
	cmp	r3, #1	@ D.24411,
	moveq	sl, r6, lsr #1	@ u32RatioCV, u32RatioCH,
	beq	.L82	@,
	cmp	r3, #2	@ D.24411,
	moveq	r6, r6, lsr #1	@ u32RatioCH, u32RatioCH,
	moveq	sl, r6	@ u32RatioCV, u32RatioCH
	bne	.L87	@,
	b	.L82	@
.L83:
	cmp	r3, #2	@ D.24409,
	bne	.L87	@,
	ldr	r3, [r0, #24]	@ prephitmp.545, <variable>.enOutFmt
	cmp	r3, #0	@ prephitmp.545,
	moveq	r6, r6, asl #1	@ u32RatioCH, u32RatioCH,
	moveq	sl, r6	@ u32RatioCV, u32RatioCH
	beq	.L82	@,
	cmp	r3, #1	@ prephitmp.545,
	moveq	sl, r6	@ u32RatioCV, u32RatioCH
	moveq	r6, r6, asl #1	@ u32RatioCH, u32RatioCH,
	bne	.L87	@,
	b	.L82	@
	.fnend
	.size	PQ_MNG_GetVpssScalerCoef, .-PQ_MNG_GetVpssScalerCoef
	.align	2
	.global	PQ_MNG_GetWbcScalerCoef
	.type	PQ_MNG_GetWbcScalerCoef, %function
PQ_MNG_GetWbcScalerCoef:
	.fnstart
.LFB661:
	@ args = 0, pretend = 0, frame = 16
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
	cmp	r1, #0	@ pvCoefAddrY,
	cmpne	r2, #0	@, pvCoefAddrC,
	mov	r5, r1	@ pvCoefAddrY, pvCoefAddrY
	mov	r4, r0	@ pstScalerInfo, pstScalerInfo
	bne	.L154	@,
.L117:
	mvn	r0, #0	@ D.24478,
.L150:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L154:
	ldr	r1, [r0, #12]	@ D.24481, <variable>.u32YRatio
	cmp	r1, #0	@ D.24481,
	beq	.L117	@,
	ldr	r6, [r0, #16]	@ u32RatioCH, <variable>.u32CRatio
	cmp	r6, #0	@ u32RatioCH,
	beq	.L117	@,
	ldr	r3, [r0, #20]	@ D.24486, <variable>.enInFmt
	cmp	r3, #0	@ D.24486,
	beq	.L155	@,
	cmp	r3, #1	@ D.24486,
	bne	.L121	@,
	ldr	r3, [r0, #24]	@ <variable>.enOutFmt, <variable>.enOutFmt
	cmp	r3, #0	@ <variable>.enOutFmt,
	moveq	r7, r6, asl #1	@ u32RatioCV, u32RatioCH,
	beq	.L120	@,
	cmp	r3, #2	@ <variable>.enOutFmt,
	moveq	r7, r6	@ u32RatioCV, u32RatioCH
	moveq	r6, r6, lsr #1	@ u32RatioCH, u32RatioCH,
	beq	.L120	@,
.L125:
	mov	r7, r6	@ u32RatioCV, u32RatioCH
.L120:
	ldr	r3, [r4, #0]	@ <variable>.bHorizontal, <variable>.bHorizontal
	cmp	r3, #0	@ <variable>.bHorizontal,
	beq	.L126	@,
	mov	r0, #104857600	@,
	str	r2, [fp, #-60]	@,
	bl	__aeabi_uidiv	@
	mov	r1, r6	@, u32RatioCH
	mov	r8, r0	@ u32ZmeRatioY,
	mov	r0, #104857600	@,
	bl	__aeabi_uidiv	@
	ldr	r2, [fp, #-60]	@,
	mov	r3, #0	@ enZmeTypeY,
	mov	r1, #4	@,
	str	r1, [fp, #-52]	@, %sfp
.L127:
	cmp	r8, #100	@ u32ZmeRatioY,
	movhi	r8, #0	@ enZmeCoefRatioY,
	bhi	.L129	@,
	moveq	r8, #1	@ enZmeCoefRatioY,
	beq	.L129	@,
	cmp	r8, #74	@ u32ZmeRatioY,
	movhi	r8, #2	@ enZmeCoefRatioY,
	bhi	.L129	@,
	cmp	r8, #49	@ u32ZmeRatioY,
	movhi	r8, #3	@ enZmeCoefRatioY,
	bhi	.L129	@,
	cmp	r8, #32	@ u32ZmeRatioY,
	movhi	r8, #4	@ enZmeCoefRatioY,
	bhi	.L129	@,
	cmp	r8, #24	@ u32ZmeRatioY,
	movhi	r8, #5	@ enZmeCoefRatioY,
	movls	r8, #6	@ enZmeCoefRatioY,
.L129:
	cmp	r0, #100	@ u32ZmeRatioC,
	movhi	r6, #0	@,
	strhi	r6, [fp, #-48]	@, %sfp
	bhi	.L136	@,
	moveq	ip, #1	@,
	streq	ip, [fp, #-48]	@, %sfp
	beq	.L136	@,
	cmp	r0, #74	@ u32ZmeRatioC,
	movhi	r0, #2	@,
	strhi	r0, [fp, #-48]	@, %sfp
	bhi	.L136	@,
	cmp	r0, #49	@ u32ZmeRatioC,
	movhi	r1, #3	@,
	strhi	r1, [fp, #-48]	@, %sfp
	bhi	.L136	@,
	cmp	r0, #32	@ u32ZmeRatioC,
	movhi	r6, #4	@,
	strhi	r6, [fp, #-48]	@, %sfp
	bhi	.L136	@,
	cmp	r0, #24	@ u32ZmeRatioC,
	movhi	r0, #5	@,
	movls	r0, #6	@,
	str	r0, [fp, #-48]	@, %sfp
.L136:
	ldr	r1, [r4, #4]	@ prephitmp.599, <variable>.bYUV
	movw	r9, #:lower16:.LANCHOR0	@ tmp340,
	mov	r0, #6	@ tmp195,
	movw	r7, #:lower16:-1431655765	@ tmp216,
	cmp	r1, #0	@ prephitmp.599,
	movt	r7, #:upper16:-1431655765	@ tmp216,
	movtne	r9, #:upper16:.LANCHOR0	@ tmp340,
	movteq	r9, #:upper16:.LANCHOR0	@ tmp340,
	add	ip, r9, r3, asl #2	@, tmp208, tmp340, enZmeTypeY,
	mlaeq	r0, r0, r8, r3	@ tmp200, tmp199, enZmeCoefRatioY, enZmeTypeY
	mlane	r8, r0, r8, r3	@ tmp196, tmp195, enZmeCoefRatioY, enZmeTypeY
	ldr	r3, [ip, #672]	@ tmp210, au32ZmeTap
	add	r6, r3, r3, asl #3	@, tmp213, tmp210, tmp210,
	addeq	r0, r9, r0, asl #2	@, tmp203, tmp340, tmp200,
	mov	lr, r6, asl #1	@ tmp214, tmp213,
	ldrne	r0, [r9, r8, asl #2]	@ ps32CoefTbl.692, paZmeCoefYuv
	ldreq	r0, [r0, #336]	@ ps32CoefTbl.692, paZmeCoefRgb
	umull	r6, ip, r7, lr	@, tmp215, tmp216, tmp214
	movs	r7, ip, lsr #3	@ u32Size, tmp215,
	beq	.L144	@,
	mov	ip, #0	@ i,
	mov	r3, r5	@ ivtmp.636, pvCoefAddrY
	mov	sl, r2	@ pvCoefAddrC, pvCoefAddrC
	str	r4, [fp, #-56]	@ pstScalerInfo, %sfp
.L145:
	ldr	r8, [r0, #0]	@ tmp217,* ps32CoefTbl.692
	add	ip, ip, #1	@ i, i,
	ldrh	lr, [r3, #0]	@,* ivtmp.636
	cmp	r7, ip	@ u32Size, i
	ldrb	r4, [r3, #8]	@ zero_extendqisi2	@,
	bfi	lr, r8, #0, #10	@ tmp218, tmp217,,
	strh	lr, [r3, #0]	@ movhi	@ tmp218,* ivtmp.636
	ldr	r1, [r0, #4]	@ tmp220,
	ldr	r2, [r3, #0]	@ tmp221,* ivtmp.636
	ldrh	lr, [r3, #10]	@,
	bfi	r2, r1, #10, #10	@ tmp221, tmp220,,
	str	r2, [r3, #0]	@ tmp221,* ivtmp.636
	ldr	r6, [r0, #8]	@ tmp222,
	ldrh	r5, [r3, #2]	@,
	ldrb	r2, [r3, #12]	@ zero_extendqisi2	@,
	bfi	r5, r6, #4, #10	@ tmp223, tmp222,,
	strh	r5, [r3, #2]	@ movhi	@ tmp223,
	ldr	r1, [r0, #12]	@ s32Tmp,
	ldrb	r5, [r3, #3]	@ zero_extendqisi2	@,
	mov	r8, r1, asr #2	@ tmp227, s32Tmp,
	bfi	r5, r1, #6, #2	@ tmp225, s32Tmp,,
	strb	r8, [r3, #4]	@ tmp227, <variable>.bits_38
	strb	r5, [r3, #3]	@ tmp225,
	ldr	r1, [r3, #4]	@ tmp230,
	ldr	r6, [r0, #16]	@ tmp229,
	bfi	r1, r6, #8, #10	@ tmp230, tmp229,,
	str	r1, [r3, #4]	@ tmp230,
	ldr	r5, [r0, #20]	@ tmp231,
	ldrh	r8, [r3, #6]	@,
	bfi	r8, r5, #2, #10	@ tmp232, tmp231,,
	strh	r8, [r3, #6]	@ movhi	@ tmp232,
	ldr	r6, [r0, #24]	@ s32Tmp.667,
	ldrb	r1, [r3, #7]	@ zero_extendqisi2	@,
	mov	r8, r6, asr #4	@ tmp236, s32Tmp.667,
	bfi	r1, r6, #4, #4	@ tmp234, s32Tmp.667,,
	bfi	r4, r8, #0, #6	@ tmp237, tmp236,,
	strb	r1, [r3, #7]	@ tmp234,
	strb	r4, [r3, #8]	@ tmp237,
	ldr	r5, [r0, #28]	@ tmp239,
	ldrh	r6, [r3, #8]	@,
	bfi	r6, r5, #6, #10	@ tmp240, tmp239,,
	strh	r6, [r3, #8]	@ movhi	@ tmp240,
	ldr	r1, [r0, #32]	@ tmp242,
	bfi	lr, r1, #0, #10	@ tmp243, tmp242,,
	strh	lr, [r3, #10]	@ movhi	@ tmp243,
	ldr	r4, [r0, #36]	@ s32Tmp.675,
	ldrb	r6, [r3, #11]	@ zero_extendqisi2	@,
	mov	r5, r4, asr #6	@ tmp247, s32Tmp.675,
	bfi	r6, r4, #2, #6	@ tmp245, s32Tmp.675,,
	bfi	r2, r5, #0, #4	@ tmp248, tmp247,,
	strb	r6, [r3, #11]	@ tmp245,
	strb	r2, [r3, #12]	@ tmp248,
	mov	r2, #0	@,
	ldr	r1, [r0, #40]	@ tmp250,
	ldrh	lr, [r3, #12]	@,
	bfi	lr, r1, #4, #10	@ tmp251, tmp250,,
	strh	lr, [r3, #12]	@ movhi	@ tmp251,
	ldr	r5, [r0, #44]	@ tmp253,
	add	r0, r0, #48	@ ps32CoefTbl.692, ps32CoefTbl.692,
	ldr	r4, [r3, #12]	@ tmp254,
	bfi	r4, r5, #14, #10	@ tmp254, tmp253,,
	str	r4, [r3, #12]	@ tmp254,
	strb	r2, [r3, #15]	@, <variable>.bits_12
	add	r3, r3, #16	@ ivtmp.636, ivtmp.636,
	bhi	.L145	@,
	ldr	r4, [fp, #-56]	@ pstScalerInfo, %sfp
	mov	r2, sl	@ pvCoefAddrC, pvCoefAddrC
	ldr	r1, [r4, #4]	@ prephitmp.599, <variable>.bYUV
.L144:
	cmp	r1, #0	@ prephitmp.599,
	beq	.L146	@,
	ldr	r6, [fp, #-48]	@, %sfp
	mov	r5, #6	@ tmp259,
	ldr	r1, [fp, #-52]	@, %sfp
	movw	ip, #:lower16:.LANCHOR0	@ tmp257,
	ldr	r3, [r4, #8]	@ <variable>.b3Dtype, <variable>.b3Dtype
	movt	ip, #:upper16:.LANCHOR0	@ tmp257,
	mla	r0, r5, r6, r1	@ tmp260, tmp259,,
	cmp	r3, #0	@ <variable>.b3Dtype,
	addne	ip, ip, r0, asl #2	@, tmp268, tmp257, tmp260,
	ldr	r3, [r9, r0, asl #2]	@ ps32CoefTbl, paZmeCoefYuv
	ldrne	r3, [ip, #168]	@ ps32CoefTbl, paZme3DCoefYuv
.L147:
	ldr	r6, [fp, #-52]	@, %sfp
	movw	lr, #:lower16:-1431655765	@ tmp298,
	movt	lr, #:upper16:-1431655765	@ tmp298,
	add	r9, r9, r6, asl #2	@, tmp290, tmp340,,
	ldr	r0, [r9, #672]	@ tmp292, au32ZmeTap
	add	r5, r0, r0, asl #3	@, tmp295, tmp292, tmp292,
	mov	ip, r5, asl #1	@ tmp296, tmp295,
	umull	r6, r1, lr, ip	@, tmp297, tmp298, tmp296
	movs	r5, r1, lsr #3	@ u32Size.654, tmp297,
	beq	.L148	@,
	mov	r1, #0	@ i,
	mov	r6, r1	@ tmp342, i
.L149:
	ldr	sl, [r3, #0]	@ tmp299,* ps32CoefTbl
	add	r1, r1, #1	@ i, i,
	ldrh	lr, [r2, #0]	@,* ivtmp.618
	cmp	r5, r1	@ u32Size.654, i
	ldrb	r4, [r2, #8]	@ zero_extendqisi2	@,
	bfi	lr, sl, #0, #10	@ tmp300, tmp299,,
	strh	lr, [r2, #0]	@ movhi	@ tmp300,* ivtmp.618
	ldr	r8, [r3, #4]	@ tmp302,
	ldr	r0, [r2, #0]	@ tmp303,* ivtmp.618
	ldrh	lr, [r2, #10]	@,
	bfi	r0, r8, #10, #10	@ tmp303, tmp302,,
	str	r0, [r2, #0]	@ tmp303,* ivtmp.618
	ldr	ip, [r3, #8]	@ tmp304,
	ldrh	r7, [r2, #2]	@,
	ldrb	r0, [r2, #12]	@ zero_extendqisi2	@,
	bfi	r7, ip, #4, #10	@ tmp305, tmp304,,
	strh	r7, [r2, #2]	@ movhi	@ tmp305,
	ldr	r8, [r3, #12]	@ s32Tmp,
	ldrb	ip, [r2, #3]	@ zero_extendqisi2	@,
	mov	sl, r8, asr #2	@ tmp309, s32Tmp,
	bfi	ip, r8, #6, #2	@ tmp307, s32Tmp,,
	strb	sl, [r2, #4]	@ tmp309, <variable>.bits_38
	strb	ip, [r2, #3]	@ tmp307,
	ldr	ip, [r2, #4]	@ tmp312,
	ldr	r7, [r3, #16]	@ tmp311,
	bfi	ip, r7, #8, #10	@ tmp312, tmp311,,
	str	ip, [r2, #4]	@ tmp312,
	ldr	r8, [r3, #20]	@ tmp313,
	ldrh	sl, [r2, #6]	@,
	bfi	sl, r8, #2, #10	@ tmp314, tmp313,,
	strh	sl, [r2, #6]	@ movhi	@ tmp314,
	ldr	r8, [r3, #24]	@ s32Tmp.696,
	ldrb	r7, [r2, #7]	@ zero_extendqisi2	@,
	mov	sl, r8, asr #4	@ tmp318, s32Tmp.696,
	bfi	r7, r8, #4, #4	@ tmp316, s32Tmp.696,,
	bfi	r4, sl, #0, #6	@ tmp319, tmp318,,
	strb	r7, [r2, #7]	@ tmp316,
	strb	r4, [r2, #8]	@ tmp319,
	ldr	ip, [r3, #28]	@ tmp321,
	ldrh	r4, [r2, #8]	@,
	bfi	r4, ip, #6, #10	@ tmp322, tmp321,,
	strh	r4, [r2, #8]	@ movhi	@ tmp322,
	ldr	r7, [r3, #32]	@ tmp324,
	bfi	lr, r7, #0, #10	@ tmp325, tmp324,,
	strh	lr, [r2, #10]	@ movhi	@ tmp325,
	ldr	r4, [r3, #36]	@ s32Tmp.704,
	ldrb	ip, [r2, #11]	@ zero_extendqisi2	@,
	mov	r7, r4, asr #6	@ tmp329, s32Tmp.704,
	bfi	ip, r4, #2, #6	@ tmp327, s32Tmp.704,,
	bfi	r0, r7, #0, #4	@ tmp330, tmp329,,
	strb	ip, [r2, #11]	@ tmp327,
	strb	r0, [r2, #12]	@ tmp330,
	ldr	lr, [r3, #40]	@ tmp332,
	ldrh	r0, [r2, #12]	@,
	bfi	r0, lr, #4, #10	@ tmp333, tmp332,,
	strh	r0, [r2, #12]	@ movhi	@ tmp333,
	ldr	ip, [r3, #44]	@ tmp335,
	add	r3, r3, #48	@ ps32CoefTbl, ps32CoefTbl,
	ldr	lr, [r2, #12]	@ tmp336,
	bfi	lr, ip, #14, #10	@ tmp336, tmp335,,
	str	lr, [r2, #12]	@ tmp336,
	strb	r6, [r2, #15]	@ tmp342, <variable>.bits_12
	add	r2, r2, #16	@ ivtmp.618, ivtmp.618,
	bhi	.L149	@,
.L148:
	mov	r0, #0	@ D.24478,
	b	.L150	@
.L146:
	ldr	r0, [fp, #-48]	@, %sfp
	mov	r5, #6	@ tmp272,
	ldr	r6, [fp, #-52]	@, %sfp
	ldr	r3, [r4, #8]	@ <variable>.b3Dtype, <variable>.b3Dtype
	mla	ip, r5, r0, r6	@ tmp273, tmp272,,
	cmp	r3, #0	@ <variable>.b3Dtype,
	add	lr, r9, ip, asl #2	@, tmp276, tmp340, tmp273,
	ldr	r3, [lr, #336]	@ ps32CoefTbl, paZmeCoefRgb
	ldrne	r3, [lr, #504]	@ ps32CoefTbl, paZme3DCoefRgb
	b	.L147	@
.L126:
	mov	r0, #409600	@,
	str	r2, [fp, #-60]	@,
	bl	__aeabi_uidiv	@
	mov	r1, r7	@, u32RatioCV
	mov	r8, r0	@ u32ZmeRatioY,
	mov	r0, #409600	@,
	bl	__aeabi_uidiv	@
	mov	r1, #5	@,
	mov	r3, #1	@ enZmeTypeY,
	str	r1, [fp, #-52]	@, %sfp
	ldr	r2, [fp, #-60]	@,
	b	.L127	@
.L155:
	ldr	r3, [r0, #24]	@ D.24488, <variable>.enOutFmt
	cmp	r3, #1	@ D.24488,
	moveq	r7, r6, lsr #1	@ u32RatioCV, u32RatioCH,
	beq	.L120	@,
	cmp	r3, #2	@ D.24488,
	moveq	r6, r6, lsr #1	@ u32RatioCH, u32RatioCH,
	moveq	r7, r6	@ u32RatioCV, u32RatioCH
	bne	.L125	@,
	b	.L120	@
.L121:
	cmp	r3, #2	@ D.24486,
	bne	.L125	@,
	ldr	r3, [r0, #24]	@ prephitmp.602, <variable>.enOutFmt
	cmp	r3, #0	@ prephitmp.602,
	moveq	r6, r6, asl #1	@ u32RatioCH, u32RatioCH,
	moveq	r7, r6	@ u32RatioCV, u32RatioCH
	beq	.L120	@,
	cmp	r3, #1	@ prephitmp.602,
	moveq	r7, r6	@ u32RatioCV, u32RatioCH
	moveq	r6, r6, asl #1	@ u32RatioCH, u32RatioCH,
	bne	.L125	@,
	b	.L120	@
	.fnend
	.size	PQ_MNG_GetWbcScalerCoef, .-PQ_MNG_GetWbcScalerCoef
	.align	2
	.global	PQ_MNG_ReadScalerInfo
	.type	PQ_MNG_ReadScalerInfo, %function
PQ_MNG_ReadScalerInfo:
	.fnstart
.LFB662:
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
	cmp	r0, #1	@ bVpssType,
	beq	.L160	@,
	rsb	r4, r1, r1, asl #3	@, tmp203, bHorizontal, bHorizontal,
	movw	r6, #:lower16:.LANCHOR1	@ tmp200,
	movt	r6, #:upper16:.LANCHOR1	@ tmp200,
	add	r3, r6, r4, asl #2	@, tmp205, tmp200, tmp203,
	ldr	r5, [r6, r4, asl #2]	@ <variable>.bHorizontal, <variable>.bHorizontal
	ldr	r0, [r3, #12]	@ <variable>.u32YRatio, <variable>.u32YRatio
	ldr	r6, [r3, #24]	@ <variable>.enOutFmt, <variable>.enOutFmt
	ldmib	r3, {r4, ip}	@ phole ldm
	ldr	r1, [r3, #16]	@ <variable>.u32CRatio, <variable>.u32CRatio
	ldr	r3, [r3, #20]	@ <variable>.enInFmt, <variable>.enInFmt
	str	r0, [r2, #12]	@ <variable>.u32YRatio, <variable>.u32YRatio
	mov	r0, #0	@,
	str	r6, [r2, #24]	@ <variable>.enOutFmt, <variable>.enOutFmt
	str	r5, [r2, #0]	@ <variable>.bHorizontal, <variable>.bHorizontal
	stmib	r2, {r4, ip}	@ phole stm
	str	r1, [r2, #16]	@ <variable>.u32CRatio, <variable>.u32CRatio
	str	r3, [r2, #20]	@ <variable>.enInFmt, <variable>.enInFmt
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
.L160:
	rsb	r4, r1, r1, asl #3	@, tmp141, bHorizontal, bHorizontal,
	movw	r5, #:lower16:.LANCHOR1	@ tmp137,
	movt	r5, #:upper16:.LANCHOR1	@ tmp137,
	add	r1, r5, r4, asl #2	@, tmp143, tmp137, tmp141,
	ldr	r0, [r1, #72]	@ <variable>.u32CRatio, <variable>.u32CRatio
	ldr	r7, [r1, #80]	@ <variable>.enOutFmt, <variable>.enOutFmt
	ldr	r6, [r1, #56]	@ <variable>.bHorizontal, <variable>.bHorizontal
	ldr	r5, [r1, #60]	@ <variable>.bYUV, <variable>.bYUV
	ldr	r4, [r1, #64]	@ <variable>.b3Dtype, <variable>.b3Dtype
	ldr	ip, [r1, #68]	@ <variable>.u32YRatio, <variable>.u32YRatio
	ldr	r3, [r1, #76]	@ <variable>.enInFmt, <variable>.enInFmt
	str	r0, [r2, #16]	@ <variable>.u32CRatio, <variable>.u32CRatio
	mov	r0, #0	@,
	str	r7, [r2, #24]	@ <variable>.enOutFmt, <variable>.enOutFmt
	str	r6, [r2, #0]	@ <variable>.bHorizontal, <variable>.bHorizontal
	str	r5, [r2, #4]	@ <variable>.bYUV, <variable>.bYUV
	str	r4, [r2, #8]	@ <variable>.b3Dtype, <variable>.b3Dtype
	str	ip, [r2, #12]	@ <variable>.u32YRatio, <variable>.u32YRatio
	str	r3, [r2, #20]	@ <variable>.enInFmt, <variable>.enInFmt
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}	@
	.fnend
	.size	PQ_MNG_ReadScalerInfo, .-PQ_MNG_ReadScalerInfo
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	paZmeCoefYuv, %object
	.size	paZmeCoefYuv, 168
paZmeCoefYuv:
	.word	coef_lanczos3
	.word	coef6_6M_a25
	.word	coef_lanczos3
	.word	coef6_6M_a25
	.word	coef4_5M_a15
	.word	coef4_5M_a15
	.word	coef8_cubic
	.word	coef6_cubic
	.word	coef8_cubic
	.word	coef6_cubic
	.word	coef4_cubic
	.word	coef4_cubic
	.word	coef8_lanczos2_8tap
	.word	coef6_5M_a25
	.word	coef8_lanczos2_8tap
	.word	coef6_5M_a25
	.word	coef4_5M_a15
	.word	coef4_5M_a15
	.word	coef8_lanczos2_8tap
	.word	coef6_4M_a20
	.word	coef8_lanczos2_8tap
	.word	coef6_4M_a20
	.word	coef4_5M_a15
	.word	coef4_5M_a15
	.word	coef8_3M_a19
	.word	coef6_3M_a15
	.word	coef8_3M_a19
	.word	coef6_3M_a15
	.word	coef4_2M_a05
	.word	coef4_2M_a05
	.word	coef8_2M_a05
	.word	coef6_2M_a05
	.word	coef8_2M_a05
	.word	coef6_2M_a05
	.word	coef4_1_5M_a05
	.word	coef4_1_5M_a05
	.word	coef8_1_5M_a05
	.word	coef6_1_5M_a05
	.word	coef8_1_5M_a05
	.word	coef6_1_5M_a05
	.word	coef4_1_5M_a05
	.word	coef4_1_5M_a05
	.type	paZme3DCoefYuv, %object
	.size	paZme3DCoefYuv, 168
paZme3DCoefYuv:
	.word	coef_lanczos3
	.word	coef6_cubic_3d
	.word	coef_lanczos3
	.word	coef6_cubic_3d
	.space	8
	.word	coef8_cubic
	.word	coef6_cubic
	.word	coef8_cubic
	.word	coef6_cubic
	.space	8
	.word	coef8_lanczos2_8tap
	.word	coef6_5M_a25
	.word	coef8_lanczos2_8tap
	.word	coef6_5M_a25
	.space	8
	.word	coef8_lanczos2_8tap
	.word	coef6_4M_a20
	.word	coef8_lanczos2_8tap
	.word	coef6_4M_a20
	.space	8
	.word	coef8_3M_a19
	.word	coef6_3M_a15
	.word	coef8_3M_a19
	.word	coef6_3M_a15
	.space	8
	.word	coef8_2M_a05
	.word	coef6_2M_a05
	.word	coef8_2M_a05
	.word	coef6_2M_a05
	.space	8
	.word	coef8_1_5M_a05
	.word	coef6_1_5M_a05
	.word	coef8_1_5M_a05
	.word	coef6_1_5M_a05
	.space	8
	.type	paZmeCoefRgb, %object
	.size	paZmeCoefRgb, 168
paZmeCoefRgb:
	.word	coef_lanczos3
	.word	coef6_6M_a25
	.word	coef_lanczos3
	.word	coef6_6M_a25
	.word	coef4_5M_a15
	.word	coef4_5M_a15
	.word	coef8_cubic
	.word	coef6_cubic
	.word	coef8_cubic
	.word	coef6_cubic
	.word	coef4_cubic
	.word	coef4_cubic
	.word	coef8_lanczos2_8tap
	.word	coef6_5M_a25
	.word	coef8_lanczos2_8tap
	.word	coef6_5M_a25
	.word	coef4_5M_a15
	.word	coef4_5M_a15
	.word	coef8_lanczos2_8tap
	.word	coef6_4M_a20
	.word	coef8_lanczos2_8tap
	.word	coef6_4M_a20
	.word	coef4_5M_a15
	.word	coef4_5M_a15
	.word	coef8_3M_a19
	.word	coef6_3M_a15
	.word	coef8_3M_a19
	.word	coef6_3M_a15
	.word	coef4_2M_a05
	.word	coef4_2M_a05
	.word	coef8_2M_a05
	.word	coef6_2M_a05
	.word	coef8_2M_a05
	.word	coef6_2M_a05
	.word	coef4_1_5M_a05
	.word	coef4_1_5M_a05
	.word	coef8_1_5M_a05
	.word	coef6_1_5M_a05
	.word	coef8_1_5M_a05
	.word	coef6_1_5M_a05
	.word	coef4_1_5M_a05
	.word	coef4_1_5M_a05
	.type	paZme3DCoefRgb, %object
	.size	paZme3DCoefRgb, 168
paZme3DCoefRgb:
	.word	coef_lanczos3
	.word	coef6_cubic_3d
	.word	coef_lanczos3
	.word	coef6_cubic_3d
	.space	8
	.word	coef8_cubic
	.word	coef6_cubic
	.word	coef8_cubic
	.word	coef6_cubic
	.space	8
	.word	coef8_lanczos2_8tap
	.word	coef6_5M_a25
	.word	coef8_lanczos2_8tap
	.word	coef6_5M_a25
	.space	8
	.word	coef8_lanczos2_8tap
	.word	coef6_4M_a20
	.word	coef8_lanczos2_8tap
	.word	coef6_4M_a20
	.space	8
	.word	coef8_3M_a19
	.word	coef6_3M_a15
	.word	coef8_3M_a19
	.word	coef6_3M_a15
	.space	8
	.word	coef8_2M_a05
	.word	coef6_2M_a05
	.word	coef8_2M_a05
	.word	coef6_2M_a05
	.space	8
	.word	coef8_1_5M_a05
	.word	coef6_1_5M_a05
	.word	coef8_1_5M_a05
	.word	coef6_1_5M_a05
	.space	8
	.type	au32ZmeTap, %object
	.size	au32ZmeTap, 24
au32ZmeTap:
	.word	8
	.word	6
	.word	8
	.word	6
	.word	4
	.word	4
	.type	coef_lanczos3, %object
	.size	coef_lanczos3, 576
coef_lanczos3:
	.word	4
	.word	-22
	.word	40
	.word	468
	.word	40
	.word	-22
	.word	4
	.word	0
	.word	3
	.word	-18
	.word	26
	.word	468
	.word	54
	.word	-26
	.word	5
	.word	0
	.word	2
	.word	-14
	.word	14
	.word	466
	.word	68
	.word	-30
	.word	6
	.word	0
	.word	2
	.word	-11
	.word	2
	.word	462
	.word	84
	.word	-34
	.word	7
	.word	0
	.word	1
	.word	-7
	.word	-9
	.word	457
	.word	100
	.word	-38
	.word	8
	.word	0
	.word	1
	.word	-4
	.word	-18
	.word	450
	.word	116
	.word	-42
	.word	9
	.word	0
	.word	1
	.word	-2
	.word	-27
	.word	443
	.word	133
	.word	-46
	.word	10
	.word	0
	.word	0
	.word	2
	.word	-35
	.word	434
	.word	151
	.word	-50
	.word	10
	.word	0
	.word	0
	.word	4
	.word	-42
	.word	425
	.word	168
	.word	-54
	.word	11
	.word	0
	.word	0
	.word	6
	.word	-49
	.word	414
	.word	186
	.word	-57
	.word	12
	.word	0
	.word	0
	.word	8
	.word	-54
	.word	401
	.word	204
	.word	-60
	.word	13
	.word	0
	.word	0
	.word	10
	.word	-58
	.word	387
	.word	222
	.word	-62
	.word	13
	.word	0
	.word	0
	.word	11
	.word	-62
	.word	374
	.word	240
	.word	-65
	.word	14
	.word	0
	.word	0
	.word	12
	.word	-65
	.word	359
	.word	258
	.word	-66
	.word	14
	.word	0
	.word	0
	.word	13
	.word	-67
	.word	344
	.word	276
	.word	-68
	.word	14
	.word	0
	.word	0
	.word	14
	.word	-68
	.word	327
	.word	293
	.word	-68
	.word	14
	.word	0
	.word	0
	.word	14
	.word	-68
	.word	310
	.word	310
	.word	-68
	.word	14
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef6_6M_a25, %object
	.size	coef6_6M_a25, 432
coef6_6M_a25:
	.word	-34
	.word	78
	.word	415
	.word	78
	.word	-34
	.word	9
	.word	-32
	.word	66
	.word	415
	.word	90
	.word	-36
	.word	9
	.word	-29
	.word	54
	.word	413
	.word	103
	.word	-38
	.word	9
	.word	-26
	.word	43
	.word	411
	.word	116
	.word	-41
	.word	9
	.word	-23
	.word	33
	.word	406
	.word	129
	.word	-42
	.word	9
	.word	-21
	.word	24
	.word	401
	.word	143
	.word	-44
	.word	9
	.word	-18
	.word	14
	.word	396
	.word	157
	.word	-46
	.word	9
	.word	-16
	.word	6
	.word	389
	.word	171
	.word	-47
	.word	9
	.word	-14
	.word	-2
	.word	382
	.word	185
	.word	-48
	.word	9
	.word	-11
	.word	-9
	.word	374
	.word	199
	.word	-49
	.word	8
	.word	-9
	.word	-16
	.word	365
	.word	213
	.word	-49
	.word	8
	.word	-7
	.word	-21
	.word	354
	.word	228
	.word	-49
	.word	7
	.word	-5
	.word	-27
	.word	345
	.word	242
	.word	-49
	.word	6
	.word	-3
	.word	-32
	.word	333
	.word	256
	.word	-48
	.word	6
	.word	-1
	.word	-36
	.word	322
	.word	269
	.word	-46
	.word	4
	.word	0
	.word	-39
	.word	309
	.word	283
	.word	-44
	.word	3
	.word	2
	.word	-42
	.word	296
	.word	296
	.word	-42
	.word	2
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef4_5M_a15, %object
	.size	coef4_5M_a15, 288
coef4_5M_a15:
	.word	103
	.word	335
	.word	103
	.word	-29
	.word	92
	.word	335
	.word	112
	.word	-27
	.word	84
	.word	335
	.word	121
	.word	-28
	.word	75
	.word	334
	.word	131
	.word	-28
	.word	67
	.word	332
	.word	141
	.word	-28
	.word	59
	.word	329
	.word	152
	.word	-28
	.word	51
	.word	326
	.word	162
	.word	-27
	.word	43
	.word	323
	.word	173
	.word	-27
	.word	36
	.word	319
	.word	183
	.word	-26
	.word	30
	.word	313
	.word	194
	.word	-25
	.word	23
	.word	308
	.word	204
	.word	-23
	.word	17
	.word	301
	.word	215
	.word	-21
	.word	12
	.word	295
	.word	225
	.word	-20
	.word	6
	.word	288
	.word	235
	.word	-17
	.word	2
	.word	280
	.word	244
	.word	-14
	.word	-3
	.word	271
	.word	254
	.word	-10
	.word	-7
	.word	263
	.word	263
	.word	-7
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef8_cubic, %object
	.size	coef8_cubic, 576
coef8_cubic:
	.word	0
	.word	0
	.word	0
	.word	511
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-1
	.word	3
	.word	-12
	.word	511
	.word	14
	.word	-4
	.word	1
	.word	0
	.word	-2
	.word	6
	.word	-23
	.word	509
	.word	28
	.word	-8
	.word	2
	.word	0
	.word	-2
	.word	9
	.word	-33
	.word	503
	.word	44
	.word	-12
	.word	3
	.word	0
	.word	-3
	.word	11
	.word	-41
	.word	496
	.word	61
	.word	-16
	.word	4
	.word	0
	.word	-3
	.word	13
	.word	-48
	.word	488
	.word	79
	.word	-21
	.word	5
	.word	-1
	.word	-3
	.word	14
	.word	-54
	.word	477
	.word	98
	.word	-25
	.word	7
	.word	-2
	.word	-4
	.word	16
	.word	-59
	.word	465
	.word	118
	.word	-30
	.word	8
	.word	-2
	.word	-4
	.word	17
	.word	-63
	.word	451
	.word	138
	.word	-35
	.word	9
	.word	-1
	.word	-4
	.word	18
	.word	-66
	.word	437
	.word	158
	.word	-39
	.word	10
	.word	-2
	.word	-4
	.word	18
	.word	-68
	.word	421
	.word	180
	.word	-44
	.word	11
	.word	-2
	.word	-4
	.word	18
	.word	-69
	.word	404
	.word	201
	.word	-48
	.word	13
	.word	-3
	.word	-4
	.word	18
	.word	-70
	.word	386
	.word	222
	.word	-52
	.word	14
	.word	-2
	.word	-4
	.word	18
	.word	-70
	.word	368
	.word	244
	.word	-56
	.word	15
	.word	-3
	.word	-4
	.word	18
	.word	-69
	.word	348
	.word	265
	.word	-59
	.word	16
	.word	-3
	.word	-4
	.word	18
	.word	-67
	.word	329
	.word	286
	.word	-63
	.word	16
	.word	-3
	.word	-3
	.word	17
	.word	-65
	.word	307
	.word	307
	.word	-65
	.word	17
	.word	-3
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef6_cubic, %object
	.size	coef6_cubic, 432
coef6_cubic:
	.word	0
	.word	0
	.word	511
	.word	0
	.word	0
	.word	0
	.word	3
	.word	-12
	.word	511
	.word	13
	.word	-3
	.word	0
	.word	6
	.word	-22
	.word	507
	.word	28
	.word	-7
	.word	0
	.word	8
	.word	-32
	.word	502
	.word	44
	.word	-11
	.word	1
	.word	10
	.word	-40
	.word	495
	.word	61
	.word	-15
	.word	1
	.word	11
	.word	-47
	.word	486
	.word	79
	.word	-19
	.word	2
	.word	12
	.word	-53
	.word	476
	.word	98
	.word	-24
	.word	3
	.word	13
	.word	-58
	.word	464
	.word	117
	.word	-28
	.word	4
	.word	14
	.word	-62
	.word	451
	.word	137
	.word	-33
	.word	5
	.word	15
	.word	-65
	.word	437
	.word	157
	.word	-38
	.word	6
	.word	15
	.word	-67
	.word	420
	.word	179
	.word	-42
	.word	7
	.word	15
	.word	-68
	.word	404
	.word	200
	.word	-46
	.word	7
	.word	14
	.word	-68
	.word	386
	.word	221
	.word	-50
	.word	9
	.word	14
	.word	-68
	.word	367
	.word	243
	.word	-54
	.word	10
	.word	14
	.word	-67
	.word	348
	.word	264
	.word	-58
	.word	11
	.word	13
	.word	-66
	.word	328
	.word	286
	.word	-61
	.word	12
	.word	13
	.word	-63
	.word	306
	.word	306
	.word	-63
	.word	13
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef4_cubic, %object
	.size	coef4_cubic, 288
coef4_cubic:
	.word	0
	.word	511
	.word	0
	.word	0
	.word	-19
	.word	511
	.word	21
	.word	-1
	.word	-37
	.word	509
	.word	42
	.word	-2
	.word	-51
	.word	504
	.word	64
	.word	-5
	.word	-64
	.word	499
	.word	86
	.word	-9
	.word	-74
	.word	492
	.word	108
	.word	-14
	.word	-82
	.word	484
	.word	129
	.word	-19
	.word	-89
	.word	474
	.word	152
	.word	-25
	.word	-94
	.word	463
	.word	174
	.word	-31
	.word	-97
	.word	451
	.word	196
	.word	-38
	.word	-98
	.word	438
	.word	217
	.word	-45
	.word	-98
	.word	424
	.word	238
	.word	-52
	.word	-98
	.word	409
	.word	260
	.word	-59
	.word	-95
	.word	392
	.word	280
	.word	-65
	.word	-92
	.word	376
	.word	300
	.word	-72
	.word	-88
	.word	358
	.word	320
	.word	-78
	.word	-83
	.word	339
	.word	339
	.word	-83
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef8_lanczos2_8tap, %object
	.size	coef8_lanczos2_8tap, 576
coef8_lanczos2_8tap:
	.word	-16
	.word	0
	.word	145
	.word	254
	.word	145
	.word	0
	.word	-16
	.word	0
	.word	-16
	.word	-2
	.word	140
	.word	253
	.word	151
	.word	3
	.word	-17
	.word	0
	.word	-15
	.word	-5
	.word	135
	.word	253
	.word	157
	.word	5
	.word	-18
	.word	0
	.word	-14
	.word	-7
	.word	129
	.word	252
	.word	162
	.word	8
	.word	-18
	.word	0
	.word	-13
	.word	-9
	.word	123
	.word	252
	.word	167
	.word	11
	.word	-19
	.word	0
	.word	-13
	.word	-11
	.word	118
	.word	250
	.word	172
	.word	15
	.word	-19
	.word	0
	.word	-12
	.word	-12
	.word	112
	.word	250
	.word	177
	.word	18
	.word	-20
	.word	-1
	.word	-11
	.word	-14
	.word	107
	.word	247
	.word	183
	.word	21
	.word	-20
	.word	-1
	.word	-10
	.word	-15
	.word	101
	.word	245
	.word	188
	.word	25
	.word	-21
	.word	-1
	.word	-9
	.word	-16
	.word	96
	.word	243
	.word	192
	.word	29
	.word	-21
	.word	-2
	.word	-8
	.word	-18
	.word	90
	.word	242
	.word	197
	.word	33
	.word	-22
	.word	-2
	.word	-8
	.word	-19
	.word	85
	.word	239
	.word	202
	.word	37
	.word	-22
	.word	-2
	.word	-7
	.word	-19
	.word	80
	.word	236
	.word	206
	.word	41
	.word	-22
	.word	-3
	.word	-7
	.word	-20
	.word	75
	.word	233
	.word	210
	.word	46
	.word	-22
	.word	-3
	.word	-6
	.word	-21
	.word	69
	.word	230
	.word	215
	.word	50
	.word	-22
	.word	-3
	.word	-5
	.word	-21
	.word	65
	.word	226
	.word	219
	.word	55
	.word	-22
	.word	-5
	.word	-5
	.word	-21
	.word	60
	.word	222
	.word	222
	.word	60
	.word	-21
	.word	-5
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef6_5M_a25, %object
	.size	coef6_5M_a25, 432
coef6_5M_a25:
	.word	-31
	.word	104
	.word	362
	.word	104
	.word	-31
	.word	4
	.word	-30
	.word	94
	.word	362
	.word	114
	.word	-32
	.word	4
	.word	-29
	.word	84
	.word	361
	.word	125
	.word	-32
	.word	3
	.word	-28
	.word	75
	.word	359
	.word	136
	.word	-33
	.word	3
	.word	-27
	.word	66
	.word	356
	.word	147
	.word	-33
	.word	3
	.word	-25
	.word	57
	.word	353
	.word	158
	.word	-33
	.word	2
	.word	-24
	.word	49
	.word	349
	.word	169
	.word	-33
	.word	2
	.word	-22
	.word	41
	.word	344
	.word	180
	.word	-32
	.word	1
	.word	-20
	.word	33
	.word	339
	.word	191
	.word	-31
	.word	0
	.word	-19
	.word	26
	.word	333
	.word	203
	.word	-30
	.word	-1
	.word	-17
	.word	19
	.word	327
	.word	214
	.word	-29
	.word	-2
	.word	-16
	.word	13
	.word	320
	.word	225
	.word	-27
	.word	-3
	.word	-14
	.word	7
	.word	312
	.word	236
	.word	-25
	.word	-4
	.word	-13
	.word	1
	.word	305
	.word	246
	.word	-22
	.word	-5
	.word	-11
	.word	-4
	.word	295
	.word	257
	.word	-19
	.word	-6
	.word	-10
	.word	-8
	.word	286
	.word	267
	.word	-16
	.word	-7
	.word	-9
	.word	-12
	.word	277
	.word	277
	.word	-12
	.word	-9
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef6_4M_a20, %object
	.size	coef6_4M_a20, 432
coef6_4M_a20:
	.word	-20
	.word	130
	.word	297
	.word	130
	.word	-20
	.word	-5
	.word	-21
	.word	122
	.word	298
	.word	138
	.word	-19
	.word	-6
	.word	-22
	.word	115
	.word	297
	.word	146
	.word	-17
	.word	-7
	.word	-22
	.word	108
	.word	296
	.word	153
	.word	-16
	.word	-7
	.word	-23
	.word	101
	.word	295
	.word	161
	.word	-14
	.word	-8
	.word	-23
	.word	93
	.word	294
	.word	169
	.word	-12
	.word	-9
	.word	-24
	.word	87
	.word	292
	.word	177
	.word	-10
	.word	-10
	.word	-24
	.word	80
	.word	289
	.word	185
	.word	-7
	.word	-11
	.word	-24
	.word	73
	.word	286
	.word	193
	.word	-4
	.word	-12
	.word	-23
	.word	66
	.word	283
	.word	200
	.word	-1
	.word	-13
	.word	-23
	.word	60
	.word	279
	.word	208
	.word	2
	.word	-14
	.word	-23
	.word	54
	.word	276
	.word	215
	.word	5
	.word	-15
	.word	-22
	.word	48
	.word	271
	.word	222
	.word	9
	.word	-16
	.word	-21
	.word	42
	.word	266
	.word	229
	.word	13
	.word	-17
	.word	-21
	.word	37
	.word	261
	.word	236
	.word	17
	.word	-18
	.word	-21
	.word	32
	.word	255
	.word	242
	.word	22
	.word	-18
	.word	-20
	.word	27
	.word	249
	.word	249
	.word	27
	.word	-20
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef8_3M_a19, %object
	.size	coef8_3M_a19, 576
coef8_3M_a19:
	.word	-18
	.word	18
	.word	144
	.word	226
	.word	144
	.word	19
	.word	-17
	.word	-4
	.word	-17
	.word	16
	.word	139
	.word	226
	.word	148
	.word	21
	.word	-17
	.word	-4
	.word	-17
	.word	13
	.word	135
	.word	227
	.word	153
	.word	24
	.word	-18
	.word	-5
	.word	-17
	.word	11
	.word	131
	.word	226
	.word	157
	.word	27
	.word	-18
	.word	-5
	.word	-17
	.word	9
	.word	126
	.word	225
	.word	161
	.word	30
	.word	-17
	.word	-5
	.word	-16
	.word	6
	.word	122
	.word	225
	.word	165
	.word	33
	.word	-17
	.word	-6
	.word	-16
	.word	4
	.word	118
	.word	224
	.word	169
	.word	37
	.word	-17
	.word	-7
	.word	-16
	.word	2
	.word	113
	.word	224
	.word	173
	.word	40
	.word	-17
	.word	-7
	.word	-15
	.word	0
	.word	109
	.word	222
	.word	177
	.word	43
	.word	-17
	.word	-7
	.word	-15
	.word	-1
	.word	104
	.word	220
	.word	181
	.word	47
	.word	-16
	.word	-8
	.word	-14
	.word	-3
	.word	100
	.word	218
	.word	185
	.word	51
	.word	-16
	.word	-9
	.word	-14
	.word	-5
	.word	96
	.word	217
	.word	188
	.word	54
	.word	-15
	.word	-9
	.word	-14
	.word	-6
	.word	91
	.word	214
	.word	192
	.word	58
	.word	-14
	.word	-9
	.word	-13
	.word	-7
	.word	87
	.word	212
	.word	195
	.word	62
	.word	-14
	.word	-10
	.word	-13
	.word	-9
	.word	83
	.word	210
	.word	198
	.word	66
	.word	-13
	.word	-10
	.word	-12
	.word	-10
	.word	79
	.word	207
	.word	201
	.word	70
	.word	-12
	.word	-11
	.word	-12
	.word	-11
	.word	74
	.word	205
	.word	205
	.word	74
	.word	-11
	.word	-12
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef6_3M_a15, %object
	.size	coef6_3M_a15, 432
coef6_3M_a15:
	.word	16
	.word	136
	.word	217
	.word	136
	.word	16
	.word	-9
	.word	13
	.word	132
	.word	217
	.word	141
	.word	18
	.word	-9
	.word	11
	.word	128
	.word	217
	.word	145
	.word	21
	.word	-10
	.word	9
	.word	124
	.word	216
	.word	149
	.word	24
	.word	-10
	.word	7
	.word	119
	.word	216
	.word	153
	.word	27
	.word	-10
	.word	5
	.word	115
	.word	216
	.word	157
	.word	30
	.word	-11
	.word	3
	.word	111
	.word	215
	.word	161
	.word	33
	.word	-11
	.word	1
	.word	107
	.word	214
	.word	165
	.word	36
	.word	-11
	.word	0
	.word	102
	.word	213
	.word	169
	.word	39
	.word	-11
	.word	-2
	.word	98
	.word	211
	.word	173
	.word	43
	.word	-11
	.word	-3
	.word	94
	.word	209
	.word	177
	.word	46
	.word	-11
	.word	-4
	.word	90
	.word	207
	.word	180
	.word	50
	.word	-11
	.word	-5
	.word	85
	.word	206
	.word	184
	.word	53
	.word	-11
	.word	-6
	.word	81
	.word	203
	.word	187
	.word	57
	.word	-10
	.word	-7
	.word	77
	.word	201
	.word	190
	.word	61
	.word	-10
	.word	-8
	.word	73
	.word	198
	.word	193
	.word	65
	.word	-9
	.word	-9
	.word	69
	.word	196
	.word	196
	.word	69
	.word	-9
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef4_2M_a05, %object
	.size	coef4_2M_a05, 288
coef4_2M_a05:
	.word	148
	.word	171
	.word	148
	.word	45
	.word	145
	.word	170
	.word	149
	.word	48
	.word	142
	.word	170
	.word	149
	.word	51
	.word	139
	.word	168
	.word	150
	.word	55
	.word	136
	.word	167
	.word	151
	.word	58
	.word	133
	.word	167
	.word	151
	.word	61
	.word	130
	.word	165
	.word	152
	.word	65
	.word	127
	.word	164
	.word	153
	.word	68
	.word	124
	.word	164
	.word	153
	.word	71
	.word	121
	.word	162
	.word	154
	.word	75
	.word	118
	.word	162
	.word	154
	.word	78
	.word	115
	.word	160
	.word	155
	.word	82
	.word	111
	.word	161
	.word	155
	.word	85
	.word	108
	.word	160
	.word	156
	.word	88
	.word	105
	.word	159
	.word	156
	.word	92
	.word	102
	.word	158
	.word	157
	.word	95
	.word	98
	.word	158
	.word	158
	.word	98
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef8_2M_a05, %object
	.size	coef8_2M_a05, 576
coef8_2M_a05:
	.word	14
	.word	66
	.word	113
	.word	133
	.word	113
	.word	66
	.word	14
	.word	-7
	.word	12
	.word	65
	.word	112
	.word	133
	.word	114
	.word	68
	.word	15
	.word	-7
	.word	11
	.word	63
	.word	111
	.word	132
	.word	115
	.word	70
	.word	17
	.word	-7
	.word	10
	.word	62
	.word	110
	.word	132
	.word	116
	.word	71
	.word	18
	.word	-7
	.word	8
	.word	60
	.word	108
	.word	132
	.word	118
	.word	73
	.word	20
	.word	-7
	.word	7
	.word	58
	.word	107
	.word	132
	.word	119
	.word	75
	.word	21
	.word	-7
	.word	6
	.word	56
	.word	106
	.word	132
	.word	120
	.word	76
	.word	23
	.word	-7
	.word	5
	.word	55
	.word	105
	.word	131
	.word	121
	.word	78
	.word	24
	.word	-7
	.word	4
	.word	53
	.word	103
	.word	131
	.word	122
	.word	80
	.word	26
	.word	-7
	.word	3
	.word	51
	.word	102
	.word	131
	.word	122
	.word	81
	.word	28
	.word	-6
	.word	2
	.word	50
	.word	101
	.word	130
	.word	123
	.word	83
	.word	29
	.word	-6
	.word	1
	.word	48
	.word	99
	.word	131
	.word	124
	.word	84
	.word	31
	.word	-6
	.word	0
	.word	46
	.word	98
	.word	129
	.word	125
	.word	86
	.word	33
	.word	-5
	.word	-1
	.word	45
	.word	97
	.word	128
	.word	126
	.word	88
	.word	34
	.word	-5
	.word	-2
	.word	43
	.word	95
	.word	130
	.word	126
	.word	89
	.word	36
	.word	-5
	.word	-3
	.word	41
	.word	94
	.word	128
	.word	127
	.word	91
	.word	38
	.word	-4
	.word	-3
	.word	39
	.word	92
	.word	128
	.word	128
	.word	92
	.word	39
	.word	-3
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef6_2M_a05, %object
	.size	coef6_2M_a05, 432
coef6_2M_a05:
	.word	66
	.word	115
	.word	138
	.word	115
	.word	66
	.word	12
	.word	64
	.word	114
	.word	136
	.word	116
	.word	68
	.word	14
	.word	63
	.word	113
	.word	134
	.word	117
	.word	70
	.word	15
	.word	61
	.word	111
	.word	135
	.word	118
	.word	71
	.word	16
	.word	59
	.word	110
	.word	133
	.word	119
	.word	73
	.word	18
	.word	57
	.word	108
	.word	134
	.word	120
	.word	74
	.word	19
	.word	55
	.word	107
	.word	133
	.word	121
	.word	76
	.word	20
	.word	53
	.word	105
	.word	133
	.word	121
	.word	78
	.word	22
	.word	51
	.word	104
	.word	133
	.word	122
	.word	79
	.word	23
	.word	49
	.word	102
	.word	132
	.word	123
	.word	81
	.word	25
	.word	47
	.word	101
	.word	132
	.word	124
	.word	82
	.word	26
	.word	45
	.word	99
	.word	131
	.word	125
	.word	84
	.word	28
	.word	44
	.word	98
	.word	130
	.word	125
	.word	85
	.word	30
	.word	42
	.word	96
	.word	130
	.word	126
	.word	87
	.word	31
	.word	40
	.word	95
	.word	128
	.word	127
	.word	89
	.word	33
	.word	38
	.word	93
	.word	129
	.word	127
	.word	90
	.word	35
	.word	36
	.word	92
	.word	128
	.word	128
	.word	92
	.word	36
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef4_1_5M_a05, %object
	.size	coef4_1_5M_a05, 288
coef4_1_5M_a05:
	.word	150
	.word	158
	.word	150
	.word	54
	.word	147
	.word	157
	.word	150
	.word	58
	.word	145
	.word	156
	.word	150
	.word	61
	.word	143
	.word	156
	.word	149
	.word	64
	.word	140
	.word	155
	.word	149
	.word	68
	.word	138
	.word	154
	.word	149
	.word	71
	.word	135
	.word	153
	.word	149
	.word	75
	.word	133
	.word	152
	.word	149
	.word	78
	.word	130
	.word	152
	.word	149
	.word	81
	.word	128
	.word	150
	.word	149
	.word	85
	.word	125
	.word	150
	.word	149
	.word	88
	.word	122
	.word	150
	.word	149
	.word	91
	.word	119
	.word	150
	.word	148
	.word	95
	.word	116
	.word	150
	.word	148
	.word	98
	.word	113
	.word	150
	.word	148
	.word	101
	.word	110
	.word	149
	.word	149
	.word	104
	.word	107
	.word	149
	.word	149
	.word	107
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef8_1_5M_a05, %object
	.size	coef8_1_5M_a05, 576
coef8_1_5M_a05:
	.word	39
	.word	69
	.word	93
	.word	102
	.word	93
	.word	69
	.word	39
	.word	8
	.word	38
	.word	68
	.word	92
	.word	102
	.word	93
	.word	70
	.word	40
	.word	9
	.word	37
	.word	67
	.word	91
	.word	102
	.word	93
	.word	71
	.word	41
	.word	10
	.word	36
	.word	66
	.word	91
	.word	101
	.word	94
	.word	71
	.word	42
	.word	11
	.word	35
	.word	65
	.word	90
	.word	102
	.word	94
	.word	72
	.word	43
	.word	11
	.word	34
	.word	64
	.word	89
	.word	102
	.word	94
	.word	73
	.word	44
	.word	12
	.word	33
	.word	63
	.word	88
	.word	101
	.word	95
	.word	74
	.word	45
	.word	13
	.word	32
	.word	62
	.word	88
	.word	100
	.word	95
	.word	75
	.word	46
	.word	14
	.word	31
	.word	62
	.word	87
	.word	100
	.word	95
	.word	75
	.word	47
	.word	15
	.word	30
	.word	61
	.word	86
	.word	99
	.word	96
	.word	76
	.word	48
	.word	16
	.word	29
	.word	60
	.word	86
	.word	98
	.word	96
	.word	77
	.word	49
	.word	17
	.word	28
	.word	59
	.word	85
	.word	98
	.word	96
	.word	78
	.word	50
	.word	18
	.word	27
	.word	58
	.word	84
	.word	99
	.word	97
	.word	78
	.word	50
	.word	19
	.word	26
	.word	57
	.word	83
	.word	99
	.word	97
	.word	79
	.word	51
	.word	20
	.word	25
	.word	56
	.word	83
	.word	98
	.word	97
	.word	80
	.word	52
	.word	21
	.word	24
	.word	55
	.word	82
	.word	97
	.word	98
	.word	81
	.word	53
	.word	22
	.word	23
	.word	54
	.word	81
	.word	98
	.word	98
	.word	81
	.word	54
	.word	23
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef6_1_5M_a05, %object
	.size	coef6_1_5M_a05, 432
coef6_1_5M_a05:
	.word	80
	.word	105
	.word	116
	.word	105
	.word	80
	.word	26
	.word	79
	.word	104
	.word	115
	.word	105
	.word	81
	.word	28
	.word	77
	.word	103
	.word	116
	.word	106
	.word	81
	.word	29
	.word	76
	.word	102
	.word	115
	.word	106
	.word	82
	.word	31
	.word	74
	.word	101
	.word	115
	.word	106
	.word	83
	.word	33
	.word	73
	.word	100
	.word	114
	.word	106
	.word	84
	.word	35
	.word	71
	.word	99
	.word	114
	.word	107
	.word	84
	.word	37
	.word	70
	.word	98
	.word	113
	.word	107
	.word	85
	.word	39
	.word	68
	.word	98
	.word	113
	.word	107
	.word	86
	.word	40
	.word	67
	.word	97
	.word	112
	.word	108
	.word	86
	.word	42
	.word	65
	.word	96
	.word	112
	.word	108
	.word	87
	.word	44
	.word	63
	.word	95
	.word	112
	.word	108
	.word	88
	.word	46
	.word	62
	.word	94
	.word	112
	.word	108
	.word	88
	.word	48
	.word	60
	.word	93
	.word	111
	.word	109
	.word	89
	.word	50
	.word	58
	.word	93
	.word	111
	.word	109
	.word	90
	.word	51
	.word	57
	.word	92
	.word	110
	.word	110
	.word	90
	.word	53
	.word	55
	.word	91
	.word	110
	.word	110
	.word	91
	.word	55
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	coef6_cubic_3d, %object
	.size	coef6_cubic_3d, 432
coef6_cubic_3d:
	.word	0
	.word	0
	.word	511
	.word	511
	.word	0
	.word	0
	.word	8
	.word	8
	.word	511
	.word	511
	.word	-8
	.word	-8
	.word	17
	.word	17
	.word	510
	.word	510
	.word	-15
	.word	-15
	.word	26
	.word	26
	.word	508
	.word	508
	.word	-22
	.word	-22
	.word	36
	.word	36
	.word	504
	.word	504
	.word	-28
	.word	-28
	.word	46
	.word	46
	.word	500
	.word	500
	.word	-34
	.word	-34
	.word	57
	.word	57
	.word	494
	.word	494
	.word	-39
	.word	-39
	.word	68
	.word	68
	.word	488
	.word	488
	.word	-44
	.word	-44
	.word	80
	.word	80
	.word	480
	.word	480
	.word	-48
	.word	-48
	.word	92
	.word	92
	.word	472
	.word	472
	.word	-52
	.word	-52
	.word	105
	.word	105
	.word	462
	.word	462
	.word	-55
	.word	-55
	.word	118
	.word	118
	.word	452
	.word	452
	.word	-58
	.word	-58
	.word	132
	.word	132
	.word	440
	.word	440
	.word	-60
	.word	-60
	.word	146
	.word	146
	.word	428
	.word	428
	.word	-62
	.word	-62
	.word	161
	.word	161
	.word	414
	.word	414
	.word	-63
	.word	-63
	.word	176
	.word	176
	.word	400
	.word	400
	.word	-64
	.word	-64
	.word	0
	.word	0
	.word	256
	.word	256
	.word	256
	.word	256
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	stVdpScalerInfo, %object
	.size	stVdpScalerInfo, 56
stVdpScalerInfo:
	.space	56
	.type	stVpssScalerInfo, %object
	.size	stVpssScalerInfo, 56
stVpssScalerInfo:
	.space	56
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
