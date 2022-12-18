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
	.file	"pq_mng_zme.c"
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
@ -DKBUILD_BASENAME=KBUILD_STR(pq_mng_zme)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_pq) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/pq/pq_v3_0/mng/.pq_mng_zme.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/pq/pq_v3_0/mng/pq_mng_zme.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/pq/pq_v3_0/mng/pq_mng_zme.o -O2 -Wall -Wundef
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
	.type	VZmeTransVpssCoefAlign, %function
VZmeTransVpssCoefAlign:
	.fnstart
.LFB654:
	@ args = 0, pretend = 0, frame = 152
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #156
	sub	sp, sp, #156	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	cmp	r1, #3	@ enTap,
	mov	sl, r2	@ pBitCoef, pBitCoef
	movhi	r7, #2	@ prephitmp.272,
	bhi	.L3	@,
	movw	r3, #:lower16:.LANCHOR0	@ tmp340,
	movt	r3, #:upper16:.LANCHOR0	@ tmp340,
	ldr	r7, [r3, r1, asl #2]	@ u32Tap, CSWTCH.219
	cmp	r7, #8	@ u32Tap,
	bne	.L19	@,
	ldrsh	r8, [r0, #0]	@ tmp348,* ps16Coef
	add	r4, r0, #2	@ ps16Coef.336, ps16Coef,
	ldrsh	r1, [r0, #2]	@ tmp341,
	movw	r3, #:lower16:1047552	@ tmp343,
	ldrsh	r5, [r4, #2]	@ tmp345,
	add	r0, r4, #2	@ ps16Coef.339, ps16Coef.336,
	mov	r2, r8, asl #22	@ tmp349, tmp348,
	movt	r3, #:upper16:1047552	@ tmp343,
	mov	r6, r1, asl #10	@ tmp342, tmp341,
	add	r8, r0, #2	@ ps16Coef.342, ps16Coef.339,
	and	ip, r6, r3	@ tmp343, tmp342, tmp343
	mov	r7, r2, lsr #22	@ tmp349, tmp349,
	add	r9, ip, r5, asl #20	@, tmp347, tmp343, tmp345,
	add	r1, r8, #2	@ ps16Coef.351, ps16Coef.342,
	add	r4, r9, r7	@ tmp351, tmp347, tmp349
	str	r4, [sl, #196]	@ tmp351, <variable>.s32CoefAttr
	ldrsh	r6, [r8, #2]	@ tmp352,
	movw	r3, #:lower16:1047552	@ tmp354,
	ldrsh	r2, [r0, #2]	@ tmp359,
	movt	r3, #:upper16:1047552	@ tmp354,
	ldrsh	ip, [r1, #2]	@ tmp356,
	add	r0, r1, #2	@ ps16Coef.354, ps16Coef.351,
	mov	r5, r6, asl #10	@ tmp353, tmp352,
	add	r6, r0, #2	@ ps16Coef.357, ps16Coef.354,
	mov	r7, r2, asl #22	@ tmp360, tmp359,
	and	r9, r5, r3	@ tmp354, tmp353, tmp354
	add	r8, r9, ip, asl #20	@, tmp358, tmp354, tmp356,
	add	r9, r6, #2	@ ps16Coef.366, ps16Coef.357,
	mov	r4, r7, lsr #22	@ tmp360, tmp360,
	add	ip, r9, #2	@ ps16Coef.369, ps16Coef.366,
	add	r2, r8, r4	@ tmp362, tmp358, tmp360
	str	r2, [sl, #200]	@ tmp362, <variable>.s32CoefAttr
	ldrsh	r5, [r0, #2]	@ tmp367,
	movw	r8, #:lower16:1047552	@ tmp365,
	ldrsh	r7, [r6, #2]	@ tmp363,
	movt	r8, #:upper16:1047552	@ tmp365,
	add	r2, ip, #2	@ ps16Coef.376, ps16Coef.369,
	mov	r4, r5, asl #22	@ tmp368, tmp367,
	mov	r5, r8	@ tmp373, tmp365
	mov	r3, r7, asl #10	@ tmp364, tmp363,
	add	r7, r2, #2	@ ps16Coef.379, ps16Coef.376,
	and	r0, r3, r8	@ tmp365, tmp364, tmp365
	mov	r1, r4, lsr #22	@ tmp368, tmp368,
	add	r6, r0, r1	@ tmp370, tmp365, tmp368
	str	r6, [sl, #204]	@ tmp370, <variable>.s32CoefAttr
	ldrsh	r3, [ip, #2]	@ tmp371,
	add	r6, r7, #2	@ ps16Coef.382, ps16Coef.379,
	ldrsh	r8, [r9, #2]	@ tmp378,
	add	r9, r6, #2	@ ps16Coef.391, ps16Coef.382,
	ldrsh	r0, [r2, #2]	@ tmp375,
	mov	r4, r3, asl #10	@ tmp372, tmp371,
	mov	r3, r5	@ tmp384, tmp373
	mov	r1, r8, asl #22	@ tmp379, tmp378,
	and	r2, r4, r5	@ tmp373, tmp372, tmp373
	add	r8, r2, r0, asl #20	@, tmp377, tmp373, tmp375,
	add	r0, r9, #2	@ ps16Coef.394, ps16Coef.391,
	mov	ip, r1, lsr #22	@ tmp379, tmp379,
	add	r4, r0, #2	@ ps16Coef.397, ps16Coef.394,
	add	r5, r8, ip	@ tmp381, tmp377, tmp379
	str	r5, [sl, #208]	@ tmp381, <variable>.s32CoefAttr
	ldrsh	r1, [r6, #2]	@ tmp382,
	add	r6, r4, #2	@ ps16Coef.406, ps16Coef.397,
	ldrsh	r2, [r7, #2]	@ tmp389,
	add	r7, r6, #2	@ ps16Coef.409, ps16Coef.406,
	ldrsh	ip, [r9, #2]	@ tmp386,
	mov	r8, r1, asl #10	@ tmp383, tmp382,
	mov	r1, r3	@ tmp395, tmp384
	mov	r9, r2, asl #22	@ tmp390, tmp389,
	and	r5, r8, r3	@ tmp384, tmp383, tmp384
	add	r3, r5, ip, asl #20	@, tmp388, tmp384, tmp386,
	add	r5, r7, #2	@ ps16Coef.416, ps16Coef.409,
	mov	r8, r9, lsr #22	@ tmp390, tmp390,
	add	ip, r5, #2	@ ps16Coef.419, ps16Coef.416,
	add	r2, r3, r8	@ tmp392, tmp388, tmp390
	str	r2, [sl, #212]	@ tmp392, <variable>.s32CoefAttr
	ldrsh	r9, [r0, #2]	@ tmp397,
	mov	r2, r1	@ tmp403, tmp395
	ldrsh	r3, [r4, #2]	@ tmp393,
	add	r4, ip, #2	@ ps16Coef.422, ps16Coef.419,
	mov	r0, r9, asl #22	@ tmp398, tmp397,
	add	r9, r4, #2	@ ps16Coef.431, ps16Coef.422,
	mov	r8, r3, asl #10	@ tmp394, tmp393,
	mov	r3, r1	@ tmp414, tmp403
	mov	r0, r0, lsr #22	@ tmp398, tmp398,
	and	r1, r8, r1	@ tmp395, tmp394, tmp395
	add	r1, r1, r0	@ tmp400, tmp395, tmp398
	str	r1, [sl, #216]	@ tmp400, <variable>.s32CoefAttr
	ldrsh	r7, [r7, #2]	@ tmp401,
	add	r0, r9, #2	@ ps16Coef.434, ps16Coef.431,
	ldrsh	r6, [r6, #2]	@ tmp408,
	add	r1, r0, #2	@ ps16Coef.437, ps16Coef.434,
	ldrsh	r8, [r5, #2]	@ tmp405,
	add	r5, r1, #2	@, ps16Coef.437,
	mov	r7, r7, asl #10	@, tmp401,
	str	r7, [fp, #-48]	@, %sfp
	str	r5, [fp, #-52]	@, %sfp
	add	r7, r5, #2	@ ps16Coef.449,,
	ldr	r5, [fp, #-48]	@, %sfp
	mov	r6, r6, asl #22	@ tmp409, tmp408,
	and	r2, r5, r2	@ tmp403,, tmp403
	mov	r6, r6, lsr #22	@ tmp409, tmp409,
	add	r2, r2, r8, asl #20	@, tmp407, tmp403, tmp405,
	mov	r5, r3	@ tmp425, tmp414
	add	r8, r2, r6	@ tmp411, tmp407, tmp409
	str	r8, [sl, #220]	@ tmp411, <variable>.s32CoefAttr
	ldrsh	r2, [r4, #2]	@ tmp412,
	add	r8, r7, #2	@ ps16Coef.456, ps16Coef.449,
	ldrsh	ip, [ip, #2]	@ tmp419,
	add	r6, r8, #2	@, ps16Coef.456,
	str	r6, [fp, #-56]	@, %sfp
	ldrsh	r6, [r9, #2]	@ tmp416,
	mov	r4, r2, asl #10	@ tmp413, tmp412,
	mov	ip, ip, asl #22	@ tmp420, tmp419,
	and	r9, r4, r3	@ tmp414, tmp413, tmp414
	mov	r2, r3	@ tmp433, tmp425
	ldr	r4, [fp, #-56]	@, %sfp
	add	r3, r9, r6, asl #20	@, tmp418, tmp414, tmp416,
	mov	ip, ip, lsr #22	@ tmp420, tmp420,
	add	r3, r3, ip	@ tmp422, tmp418, tmp420
	str	r3, [sl, #224]	@ tmp422, <variable>.s32CoefAttr
	ldrsh	r9, [r1, #2]	@,
	add	r6, r4, #2	@ ps16Coef.462,,
	ldrsh	ip, [r0, #2]	@ tmp427,
	add	r4, r6, #2	@ ps16Coef.471, ps16Coef.462,
	mov	r3, r5	@ tmp444, tmp433
	str	r9, [fp, #-48]	@, %sfp
	add	r9, r4, #2	@ ps16Coef.474, ps16Coef.471,
	ldr	r0, [fp, #-48]	@, %sfp
	add	r1, r9, #2	@, ps16Coef.474,
	str	r1, [fp, #-60]	@, %sfp
	mov	ip, ip, asl #22	@ tmp428, tmp427,
	mov	r1, r0, asl #10	@,,
	ldr	r0, [fp, #-60]	@, %sfp
	str	r1, [fp, #-48]	@, %sfp
	add	r1, r0, #2	@,,
	ldr	r0, [fp, #-48]	@, %sfp
	str	r1, [fp, #-76]	@, %sfp
	mov	r1, ip, lsr #22	@ tmp428, tmp428,
	and	r5, r0, r5	@ tmp425,, tmp425
	add	r0, r5, r1	@ tmp430, tmp425, tmp428
	str	r0, [sl, #228]	@ tmp430, <variable>.s32CoefAttr
	ldr	ip, [fp, #-52]	@, %sfp
	mov	r0, r2	@ tmp455, tmp444
	ldrsh	r7, [r7, #2]	@ tmp431,
	ldrsh	r8, [r8, #2]	@,
	ldr	r1, [fp, #-76]	@, %sfp
	ldrsh	r5, [ip, #2]	@ tmp438,
	mov	r7, r7, asl #10	@ tmp432, tmp431,
	str	r8, [fp, #-48]	@, %sfp
	add	ip, r1, #2	@ ps16Coef.489,,
	add	r8, ip, #2	@ ps16Coef.496, ps16Coef.489,
	and	r2, r7, r2	@ tmp433, tmp432, tmp433
	ldr	r7, [fp, #-48]	@, %sfp
	add	r1, r8, #2	@, ps16Coef.496,
	str	r1, [fp, #-64]	@, %sfp
	mov	r1, r5, asl #22	@ tmp439, tmp438,
	add	r2, r2, r7, asl #20	@, tmp437, tmp433,,
	mov	r5, r1, lsr #22	@ tmp439, tmp439,
	add	r7, r2, r5	@ tmp441, tmp437, tmp439
	str	r7, [sl, #232]	@ tmp441, <variable>.s32CoefAttr
	ldr	r2, [fp, #-56]	@, %sfp
	mov	r1, r3	@ tmp463, tmp455
	ldrsh	r7, [r6, #2]	@ tmp442,
	ldr	r6, [fp, #-64]	@, %sfp
	add	r5, r6, #2	@ ps16Coef.502,,
	ldrsh	r6, [r2, #2]	@ tmp449,
	mov	r7, r7, asl #10	@ tmp443, tmp442,
	add	r2, r5, #2	@, ps16Coef.502,
	str	r2, [fp, #-56]	@, %sfp
	mov	r2, r3	@ tmp474, tmp463
	ldrsh	r4, [r4, #2]	@ tmp446,
	and	r3, r7, r3	@ tmp444, tmp443, tmp444
	mov	r6, r6, asl #22	@ tmp450, tmp449,
	ldr	r7, [fp, #-56]	@, %sfp
	add	r3, r3, r4, asl #20	@, tmp448, tmp444, tmp446,
	mov	r6, r6, lsr #22	@ tmp450, tmp450,
	add	r4, r7, #2	@ ps16Coef.514,,
	add	r3, r3, r6	@ tmp452, tmp448, tmp450
	add	r7, r4, #2	@, ps16Coef.514,
	str	r7, [fp, #-48]	@, %sfp
	str	r3, [sl, #236]	@ tmp452, <variable>.s32CoefAttr
	ldrsh	r6, [r9, #2]	@ tmp457,
	add	r9, r7, #2	@,,
	ldr	r7, [fp, #-60]	@, %sfp
	str	r9, [fp, #-52]	@, %sfp
	add	r9, r9, #2	@ ps16Coef.529,,
	mov	r6, r6, asl #22	@ tmp458, tmp457,
	ldrsh	r3, [r7, #2]	@,
	add	r7, r9, #2	@, ps16Coef.529,
	mov	r6, r6, lsr #22	@ tmp458, tmp458,
	str	r3, [fp, #-68]	@, %sfp
	mov	r3, r0	@ tmp485, tmp474
	str	r7, [fp, #-60]	@, %sfp
	ldr	r7, [fp, #-68]	@, %sfp
	mov	r7, r7, asl #10	@,,
	str	r7, [fp, #-68]	@, %sfp
	ldr	r7, [fp, #-60]	@, %sfp
	add	r7, r7, #2	@,,
	str	r7, [fp, #-72]	@, %sfp
	ldr	r7, [fp, #-68]	@, %sfp
	and	r0, r7, r0	@ tmp455,, tmp455
	add	r0, r0, r6	@ tmp460, tmp455, tmp458
	str	r0, [sl, #240]	@ tmp460, <variable>.s32CoefAttr
	ldrsh	r0, [ip, #2]	@ tmp461,
	ldr	ip, [fp, #-76]	@, %sfp
	ldrsh	r7, [r8, #2]	@,
	mov	r0, r0, asl #10	@ tmp462, tmp461,
	ldr	r8, [fp, #-72]	@, %sfp
	ldrsh	r6, [ip, #2]	@ tmp468,
	mov	ip, r1	@ tmp493, tmp485
	str	r7, [fp, #-76]	@, %sfp
	and	r1, r0, r1	@ tmp463, tmp462, tmp463
	ldr	r0, [fp, #-76]	@, %sfp
	add	r7, r8, #2	@ ps16Coef.542,,
	mov	r6, r6, asl #22	@ tmp469, tmp468,
	add	r8, r7, #2	@ ps16Coef.551, ps16Coef.542,
	add	r1, r1, r0, asl #20	@, tmp467, tmp463,,
	mov	r6, r6, lsr #22	@ tmp469, tmp469,
	add	r1, r1, r6	@ tmp471, tmp467, tmp469
	str	r1, [sl, #244]	@ tmp471, <variable>.s32CoefAttr
	ldr	r1, [fp, #-64]	@, %sfp
	add	r6, r8, #2	@ ps16Coef.554, ps16Coef.551,
	ldrsh	r5, [r5, #2]	@ tmp472,
	mov	r0, r2	@ tmp504, tmp493
	ldrsh	r1, [r1, #2]	@,
	mov	r5, r5, asl #10	@, tmp472,
	str	r1, [fp, #-76]	@, %sfp
	add	r1, r6, #2	@, ps16Coef.554,
	str	r1, [fp, #-88]	@, %sfp
	ldr	r1, [fp, #-56]	@, %sfp
	ldrsh	r1, [r1, #2]	@,
	str	r5, [fp, #-80]	@, %sfp
	str	r1, [fp, #-64]	@, %sfp
	ldr	r1, [fp, #-88]	@, %sfp
	add	r1, r1, #2	@,,
	str	r1, [fp, #-68]	@, %sfp
	add	r5, r1, #2	@,,
	ldr	r1, [fp, #-76]	@, %sfp
	str	r5, [fp, #-56]	@, %sfp
	mov	r5, r1, asl #22	@ tmp480,,
	ldr	r1, [fp, #-80]	@, %sfp
	and	r2, r1, r2	@ tmp474,, tmp474
	ldr	r1, [fp, #-64]	@, %sfp
	mov	r5, r5, lsr #22	@ tmp480, tmp480,
	add	r2, r2, r1, asl #20	@, tmp478, tmp474,,
	mov	r1, r3	@ tmp515, tmp504
	add	r2, r2, r5	@ tmp482, tmp478, tmp480
	str	r2, [sl, #248]	@ tmp482, <variable>.s32CoefAttr
	ldr	r5, [fp, #-48]	@, %sfp
	ldr	r2, [fp, #-56]	@, %sfp
	ldrsh	r4, [r4, #2]	@ tmp487,
	add	r2, r2, #2	@,,
	str	r2, [fp, #-104]	@, %sfp
	ldrsh	r5, [r5, #2]	@,
	add	r2, r2, #2	@,,
	mov	r4, r4, asl #22	@ tmp488, tmp487,
	str	r5, [fp, #-48]	@, %sfp
	mov	r4, r4, lsr #22	@ tmp488, tmp488,
	str	r2, [fp, #-80]	@, %sfp
	mov	r2, r3	@ tmp523, tmp515
	ldr	r5, [fp, #-80]	@, %sfp
	add	r5, r5, #2	@,,
	str	r5, [fp, #-76]	@, %sfp
	ldr	r5, [fp, #-48]	@, %sfp
	mov	r5, r5, asl #10	@,,
	str	r5, [fp, #-48]	@, %sfp
	ldr	r5, [fp, #-76]	@, %sfp
	add	r5, r5, #2	@,,
	str	r5, [fp, #-64]	@, %sfp
	ldr	r5, [fp, #-48]	@, %sfp
	and	r3, r5, r3	@ tmp485,, tmp485
	add	r5, r3, r4	@ tmp490, tmp485, tmp488
	str	r5, [sl, #252]	@ tmp490, <variable>.s32CoefAttr
	ldrsh	r4, [r9, #2]	@ tmp491,
	ldr	r9, [fp, #-52]	@, %sfp
	ldr	r5, [fp, #-60]	@, %sfp
	ldrsh	r3, [r9, #2]	@,
	str	r3, [fp, #-84]	@, %sfp
	mov	r3, ip	@ tmp534, tmp523
	ldrsh	r9, [r5, #2]	@,
	ldr	r5, [fp, #-64]	@, %sfp
	str	r9, [fp, #-48]	@, %sfp
	add	r9, r5, #2	@ ps16Coef.594,,
	mov	r5, r4, asl #10	@, tmp491,
	str	r5, [fp, #-52]	@, %sfp
	ldr	r5, [fp, #-84]	@, %sfp
	add	r4, r9, #2	@, ps16Coef.594,
	str	r4, [fp, #-60]	@, %sfp
	mov	r4, r5, asl #22	@ tmp499,,
	ldr	r5, [fp, #-52]	@, %sfp
	and	ip, r5, ip	@ tmp493,, tmp493
	ldr	r5, [fp, #-48]	@, %sfp
	mov	r4, r4, lsr #22	@ tmp499, tmp499,
	add	ip, ip, r5, asl #20	@, tmp497, tmp493,,
	ldr	r5, [fp, #-60]	@, %sfp
	add	r5, r5, #2	@,,
	str	r5, [fp, #-48]	@, %sfp
	add	r5, r5, #2	@,,
	str	r5, [fp, #-52]	@, %sfp
	add	r5, ip, r4	@ tmp501, tmp497, tmp499
	str	r5, [sl, #256]	@ tmp501, <variable>.s32CoefAttr
	ldr	r4, [fp, #-72]	@, %sfp
	ldrsh	ip, [r7, #2]	@ tmp502,
	ldrsh	r8, [r8, #2]	@,
	ldrsh	r7, [r4, #2]	@ tmp509,
	mov	r4, r0	@ tmp545, tmp534
	mov	ip, ip, asl #10	@ tmp503, tmp502,
	ldr	r5, [fp, #-52]	@, %sfp
	str	r8, [fp, #-72]	@, %sfp
	and	r0, ip, r0	@ tmp504, tmp503, tmp504
	ldr	ip, [fp, #-72]	@, %sfp
	mov	r7, r7, asl #22	@ tmp510, tmp509,
	add	r8, r5, #2	@ ps16Coef.616,,
	add	r5, r8, #2	@, ps16Coef.616,
	mov	r7, r7, lsr #22	@ tmp510, tmp510,
	add	r0, r0, ip, asl #20	@, tmp508, tmp504,,
	str	r5, [fp, #-100]	@, %sfp
	add	r7, r0, r7	@ tmp512, tmp508, tmp510
	add	r0, r5, #2	@,,
	str	r7, [sl, #260]	@ tmp512, <variable>.s32CoefAttr
	mov	ip, r1	@ tmp553, tmp545
	ldr	r5, [fp, #-88]	@, %sfp
	ldrsh	r6, [r6, #2]	@ tmp517,
	str	r0, [fp, #-96]	@, %sfp
	add	r0, r0, #2	@,,
	ldrsh	r7, [r5, #2]	@ tmp513,
	str	r0, [fp, #-92]	@, %sfp
	mov	r6, r6, asl #22	@ tmp518, tmp517,
	ldr	r5, [fp, #-92]	@, %sfp
	mov	r0, r1	@ tmp564, tmp553
	mov	r7, r7, asl #10	@ tmp514, tmp513,
	mov	r6, r6, lsr #22	@ tmp518, tmp518,
	add	r5, r5, #2	@,,
	and	r1, r7, r1	@ tmp515, tmp514, tmp515
	str	r5, [fp, #-112]	@, %sfp
	add	r1, r1, r6	@ tmp520, tmp515, tmp518
	add	r5, r5, #2	@,,
	str	r5, [fp, #-108]	@, %sfp
	str	r1, [sl, #264]	@ tmp520, <variable>.s32CoefAttr
	add	r1, r5, #2	@,,
	ldr	r7, [fp, #-56]	@, %sfp
	ldr	r5, [fp, #-68]	@, %sfp
	ldrsh	r6, [r7, #2]	@ tmp521,
	str	r1, [fp, #-84]	@, %sfp
	add	r1, r1, #2	@,,
	ldrsh	r7, [r5, #2]	@ tmp528,
	ldr	r5, [fp, #-104]	@, %sfp
	mov	r6, r6, asl #10	@ tmp522, tmp521,
	str	r1, [fp, #-56]	@, %sfp
	ldrsh	r1, [r5, #2]	@,
	mov	r5, r7, asl #22	@ tmp529, tmp528,
	mov	r5, r5, lsr #22	@ tmp529, tmp529,
	str	r1, [fp, #-68]	@, %sfp
	mov	r1, r2	@ tmp575, tmp564
	ldr	r7, [fp, #-68]	@, %sfp
	and	r2, r6, r2	@ tmp523, tmp522, tmp523
	ldr	r6, [fp, #-56]	@, %sfp
	add	r2, r2, r7, asl #20	@, tmp527, tmp523,,
	add	r7, r6, #2	@,,
	add	r6, r7, #2	@,,
	str	r7, [fp, #-72]	@, %sfp
	str	r6, [fp, #-88]	@, %sfp
	add	r5, r2, r5	@ tmp531, tmp527, tmp529
	str	r5, [sl, #268]	@ tmp531, <variable>.s32CoefAttr
	ldr	r7, [fp, #-64]	@, %sfp
	ldr	r6, [fp, #-76]	@, %sfp
	ldr	r2, [fp, #-80]	@, %sfp
	ldrsh	r7, [r7, #2]	@,
	ldrsh	r5, [r6, #2]	@ tmp532,
	ldrsh	r6, [r2, #2]	@ tmp539,
	mov	r2, r3	@ tmp583, tmp575
	str	r7, [fp, #-64]	@, %sfp
	ldr	r7, [fp, #-88]	@, %sfp
	add	r7, r7, #2	@,,
	str	r7, [fp, #-68]	@, %sfp
	mov	r7, r5, asl #10	@ tmp533, tmp532,
	ldr	r5, [fp, #-68]	@, %sfp
	and	r3, r7, r3	@ tmp534, tmp533, tmp534
	add	r5, r5, #2	@,,
	str	r5, [fp, #-80]	@, %sfp
	ldr	r7, [fp, #-64]	@, %sfp
	mov	r5, r6, asl #22	@ tmp540, tmp539,
	add	r6, r3, r7, asl #20	@, tmp538, tmp534,,
	mov	r7, r5, lsr #22	@ tmp540, tmp540,
	add	r5, r6, r7	@ tmp542, tmp538, tmp540
	str	r5, [sl, #272]	@ tmp542, <variable>.s32CoefAttr
	ldr	r7, [fp, #-60]	@, %sfp
	mov	r3, r4	@ tmp594, tmp583
	ldr	r6, [fp, #-80]	@, %sfp
	ldrsh	r5, [r9, #2]	@ tmp547,
	add	r9, r6, #2	@ ps16Coef.674,,
	ldrsh	r6, [r7, #2]	@ tmp543,
	add	r7, r9, #2	@, ps16Coef.674,
	str	r7, [fp, #-76]	@, %sfp
	add	r7, r7, #2	@,,
	str	r7, [fp, #-64]	@, %sfp
	mov	r6, r6, asl #10	@, tmp543,
	str	r6, [fp, #-104]	@, %sfp
	ldr	r6, [fp, #-64]	@, %sfp
	mov	r5, r5, asl #22	@ tmp548, tmp547,
	mov	r7, r4	@ tmp605, tmp594
	add	r6, r6, #2	@,,
	str	r6, [fp, #-60]	@, %sfp
	ldr	r6, [fp, #-104]	@, %sfp
	and	r4, r6, r4	@ tmp545,, tmp545
	mov	r6, r5, lsr #22	@ tmp548, tmp548,
	add	r4, r4, r6	@ tmp550, tmp545, tmp548
	str	r4, [sl, #276]	@ tmp550, <variable>.s32CoefAttr
	ldr	r5, [fp, #-52]	@, %sfp
	ldr	r6, [fp, #-60]	@, %sfp
	ldrsh	r4, [r5, #2]	@ tmp551,
	add	r5, r6, #2	@,,
	ldr	r6, [fp, #-48]	@, %sfp
	str	r5, [fp, #-52]	@, %sfp
	ldrsh	r5, [r6, #2]	@ tmp558,
	ldr	r6, [fp, #-52]	@, %sfp
	add	r6, r6, #2	@,,
	str	r6, [fp, #-128]	@, %sfp
	ldrsh	r6, [r8, #2]	@,
	mov	r8, r4, asl #10	@ tmp552, tmp551,
	mov	r4, r5, asl #22	@ tmp559, tmp558,
	str	r6, [fp, #-48]	@, %sfp
	mov	r6, ip	@ tmp613, tmp605
	ldr	r5, [fp, #-48]	@, %sfp
	and	ip, r8, ip	@ tmp553, tmp552, tmp553
	ldr	r8, [fp, #-128]	@, %sfp
	mov	r4, r4, lsr #22	@ tmp559, tmp559,
	add	ip, ip, r5, asl #20	@, tmp557, tmp553,,
	add	r5, r8, #2	@,,
	add	r8, r5, #2	@,,
	str	r5, [fp, #-48]	@, %sfp
	str	r8, [fp, #-124]	@, %sfp
	add	r8, ip, r4	@ tmp561, tmp557, tmp559
	str	r8, [sl, #280]	@ tmp561, <variable>.s32CoefAttr
	ldr	r8, [fp, #-92]	@, %sfp
	ldr	r4, [fp, #-96]	@, %sfp
	ldr	r5, [fp, #-100]	@, %sfp
	ldrsh	r8, [r8, #2]	@,
	ldrsh	ip, [r4, #2]	@ tmp562,
	ldrsh	r4, [r5, #2]	@ tmp569,
	mov	r5, r0	@ tmp624, tmp613
	str	r8, [fp, #-92]	@, %sfp
	ldr	r8, [fp, #-124]	@, %sfp
	add	r8, r8, #2	@,,
	str	r8, [fp, #-140]	@, %sfp
	mov	r8, ip, asl #10	@ tmp563, tmp562,
	ldr	ip, [fp, #-140]	@, %sfp
	and	r0, r8, r0	@ tmp564, tmp563, tmp564
	ldr	r8, [fp, #-92]	@, %sfp
	add	ip, ip, #2	@,,
	str	ip, [fp, #-104]	@, %sfp
	mov	ip, r4, asl #22	@ tmp570, tmp569,
	ldr	r4, [fp, #-104]	@, %sfp
	add	r0, r0, r8, asl #20	@, tmp568, tmp564,,
	mov	ip, ip, lsr #22	@ tmp570, tmp570,
	add	r8, r4, #2	@,,
	add	r4, r8, #2	@,,
	str	r8, [fp, #-136]	@, %sfp
	str	r4, [fp, #-120]	@, %sfp
	add	ip, r0, ip	@ tmp572, tmp568, tmp570
	str	ip, [sl, #284]	@ tmp572, <variable>.s32CoefAttr
	ldr	r8, [fp, #-112]	@, %sfp
	ldr	r4, [fp, #-108]	@, %sfp
	ldr	ip, [fp, #-120]	@, %sfp
	ldrsh	r0, [r8, #2]	@ tmp577,
	ldrsh	r8, [r4, #2]	@ tmp573,
	add	ip, ip, #2	@,,
	str	ip, [fp, #-116]	@, %sfp
	mov	r4, r1	@ tmp635, tmp624
	mov	r0, r0, asl #22	@ tmp578, tmp577,
	mov	ip, r1	@ tmp643, tmp635
	mov	r8, r8, asl #10	@, tmp573,
	str	r8, [fp, #-92]	@, %sfp
	ldr	r8, [fp, #-116]	@, %sfp
	mov	r0, r0, lsr #22	@ tmp578, tmp578,
	add	r8, r8, #2	@,,
	str	r8, [fp, #-100]	@, %sfp
	ldr	r8, [fp, #-92]	@, %sfp
	and	r1, r8, r1	@ tmp575,, tmp575
	add	r1, r1, r0	@ tmp580, tmp575, tmp578
	str	r1, [sl, #288]	@ tmp580, <variable>.s32CoefAttr
	ldr	r8, [fp, #-56]	@, %sfp
	ldr	r0, [fp, #-100]	@, %sfp
	ldrsh	r1, [r8, #2]	@ tmp581,
	add	r8, r0, #2	@,,
	ldr	r0, [fp, #-84]	@, %sfp
	str	r8, [fp, #-96]	@, %sfp
	ldrsh	r8, [r0, #2]	@ tmp588,
	ldr	r0, [fp, #-96]	@, %sfp
	add	r0, r0, #2	@,,
	str	r0, [fp, #-56]	@, %sfp
	ldr	r0, [fp, #-72]	@, %sfp
	ldrsh	r0, [r0, #2]	@,
	str	r0, [fp, #-84]	@, %sfp
	mov	r0, r1, asl #10	@, tmp581,
	str	r0, [fp, #-72]	@, %sfp
	mov	r1, r8, asl #22	@ tmp589, tmp588,
	ldr	r8, [fp, #-72]	@, %sfp
	mov	r0, r2	@ tmp654, tmp643
	mov	r1, r1, lsr #22	@ tmp589, tmp589,
	and	r2, r8, r2	@ tmp583,, tmp583
	ldr	r8, [fp, #-84]	@, %sfp
	add	r2, r2, r8, asl #20	@, tmp587, tmp583,,
	ldr	r8, [fp, #-56]	@, %sfp
	add	r1, r2, r1	@ tmp591, tmp587, tmp589
	add	r8, r8, #2	@,,
	str	r8, [fp, #-92]	@, %sfp
	add	r8, r8, #2	@,,
	str	r8, [fp, #-112]	@, %sfp
	str	r1, [sl, #292]	@ tmp591, <variable>.s32CoefAttr
	add	r8, r8, #2	@,,
	ldr	r1, [fp, #-68]	@, %sfp
	ldrsh	r2, [r1, #2]	@ tmp592,
	ldr	r1, [fp, #-88]	@, %sfp
	str	r8, [fp, #-108]	@, %sfp
	ldrsh	r8, [r1, #2]	@ tmp599,
	ldr	r1, [fp, #-108]	@, %sfp
	add	r1, r1, #2	@,,
	str	r1, [fp, #-84]	@, %sfp
	ldr	r1, [fp, #-80]	@, %sfp
	ldrsh	r1, [r1, #2]	@,
	str	r1, [fp, #-68]	@, %sfp
	mov	r1, r2, asl #10	@, tmp592,
	str	r1, [fp, #-80]	@, %sfp
	mov	r2, r8, asl #22	@ tmp600, tmp599,
	ldr	r8, [fp, #-80]	@, %sfp
	mov	r1, r3	@ tmp665, tmp654
	mov	r2, r2, lsr #22	@ tmp600, tmp600,
	and	r3, r8, r3	@ tmp594,, tmp594
	ldr	r8, [fp, #-68]	@, %sfp
	add	r3, r3, r8, asl #20	@, tmp598, tmp594,,
	ldr	r8, [fp, #-84]	@, %sfp
	add	r2, r3, r2	@ tmp602, tmp598, tmp600
	add	r8, r8, #2	@,,
	str	r8, [fp, #-72]	@, %sfp
	add	r8, r8, #2	@,,
	str	r8, [fp, #-88]	@, %sfp
	str	r2, [sl, #296]	@ tmp602, <variable>.s32CoefAttr
	ldr	r3, [fp, #-76]	@, %sfp
	ldrsh	r9, [r9, #2]	@ tmp607,
	ldrsh	r2, [r3, #2]	@,
	add	r3, r8, #2	@,,
	add	r8, r3, #2	@,,
	str	r3, [fp, #-68]	@, %sfp
	mov	r9, r9, asl #22	@ tmp608, tmp607,
	str	r8, [fp, #-80]	@, %sfp
	str	r2, [fp, #-76]	@, %sfp
	mov	r2, r7	@ tmp673, tmp665
	ldr	r3, [fp, #-76]	@, %sfp
	mov	r9, r9, lsr #22	@ tmp608, tmp608,
	mov	r8, r3, asl #10	@,,
	mov	r3, r7	@ tmp684, tmp673
	and	r7, r8, r7	@ tmp605,, tmp605
	str	r8, [fp, #-76]	@, %sfp
	add	r7, r7, r9	@ tmp610, tmp605, tmp608
	str	r7, [sl, #300]	@ tmp610, <variable>.s32CoefAttr
	ldr	r8, [fp, #-60]	@, %sfp
	ldr	r7, [fp, #-80]	@, %sfp
	ldrsh	r9, [r8, #2]	@,
	add	r7, r7, #2	@,,
	ldr	r8, [fp, #-64]	@, %sfp
	str	r7, [fp, #-76]	@, %sfp
	str	r9, [fp, #-132]	@, %sfp
	ldrsh	r9, [r8, #2]	@,
	str	r9, [fp, #-144]	@, %sfp
	add	r9, r7, #2	@,,
	ldr	r8, [fp, #-52]	@, %sfp
	str	r9, [fp, #-60]	@, %sfp
	ldrsh	r7, [r8, #2]	@,
	add	r8, r9, #2	@,,
	ldr	r9, [fp, #-132]	@, %sfp
	str	r8, [fp, #-64]	@, %sfp
	add	r8, r8, #2	@,,
	str	r7, [fp, #-148]	@, %sfp
	mov	r7, r9, asl #10	@ tmp612,,
	ldr	r9, [fp, #-144]	@, %sfp
	str	r8, [fp, #-52]	@, %sfp
	mov	r8, r9, asl #22	@ tmp619,,
	and	r9, r7, r6	@ tmp613, tmp612, tmp613
	ldr	r7, [fp, #-148]	@, %sfp
	add	r6, r9, r7, asl #20	@, tmp617, tmp613,,
	mov	r9, r8, lsr #22	@ tmp619, tmp619,
	add	r8, r6, r9	@ tmp621, tmp617, tmp619
	str	r8, [sl, #304]	@ tmp621, <variable>.s32CoefAttr
	ldr	r9, [fp, #-48]	@, %sfp
	mov	r7, r5	@ tmp695, tmp684
	ldr	r6, [fp, #-52]	@, %sfp
	ldrsh	r8, [r9, #2]	@ tmp622,
	add	r9, r6, #2	@,,
	ldr	r6, [fp, #-128]	@, %sfp
	str	r9, [fp, #-48]	@, %sfp
	ldrsh	r9, [r6, #2]	@ tmp629,
	ldr	r6, [fp, #-48]	@, %sfp
	add	r6, r6, #2	@,,
	str	r6, [fp, #-156]	@, %sfp
	ldr	r6, [fp, #-124]	@, %sfp
	ldrsh	r6, [r6, #2]	@,
	str	r6, [fp, #-128]	@, %sfp
	mov	r6, r8, asl #10	@, tmp622,
	str	r6, [fp, #-124]	@, %sfp
	mov	r8, r9, asl #22	@ tmp630, tmp629,
	ldr	r9, [fp, #-124]	@, %sfp
	mov	r6, r5	@ tmp703, tmp695
	mov	r8, r8, lsr #22	@ tmp630, tmp630,
	and	r5, r9, r5	@ tmp624,, tmp624
	ldr	r9, [fp, #-128]	@, %sfp
	add	r5, r5, r9, asl #20	@, tmp628, tmp624,,
	ldr	r9, [fp, #-156]	@, %sfp
	add	r9, r9, #2	@,,
	str	r9, [fp, #-152]	@, %sfp
	add	r9, r9, #2	@,,
	str	r9, [fp, #-132]	@, %sfp
	add	r9, r5, r8	@ tmp632, tmp628, tmp630
	str	r9, [sl, #308]	@ tmp632, <variable>.s32CoefAttr
	ldr	r5, [fp, #-104]	@, %sfp
	ldr	r8, [fp, #-140]	@, %sfp
	ldrsh	r9, [r8, #2]	@ tmp637,
	ldrsh	r8, [r5, #2]	@,
	ldr	r5, [fp, #-132]	@, %sfp
	str	r8, [fp, #-104]	@, %sfp
	add	r5, r5, #2	@,,
	str	r5, [fp, #-148]	@, %sfp
	mov	r5, r9, asl #22	@, tmp637,
	ldr	r9, [fp, #-148]	@, %sfp
	mov	r8, r4	@ tmp714, tmp703
	str	r5, [fp, #-124]	@, %sfp
	add	r5, r9, #2	@,,
	ldr	r9, [fp, #-104]	@, %sfp
	str	r5, [fp, #-144]	@, %sfp
	mov	r5, r9, asl #10	@,,
	ldr	r9, [fp, #-144]	@, %sfp
	str	r5, [fp, #-104]	@, %sfp
	add	r5, r9, #2	@,,
	ldr	r9, [fp, #-104]	@, %sfp
	str	r5, [fp, #-180]	@, %sfp
	and	r5, r9, r4	@ tmp635,, tmp635
	ldr	r9, [fp, #-124]	@, %sfp
	mov	r9, r9, lsr #22	@,,
	add	r4, r5, r9	@ tmp640, tmp635,
	str	r4, [sl, #312]	@ tmp640, <variable>.s32CoefAttr
	ldr	r9, [fp, #-120]	@, %sfp
	ldr	r4, [fp, #-136]	@, %sfp
	ldrsh	r5, [r9, #2]	@,
	str	r5, [fp, #-104]	@, %sfp
	mov	r5, ip	@ tmp725, tmp714
	ldrsh	r9, [r4, #2]	@ tmp648,
	ldr	r4, [fp, #-180]	@, %sfp
	add	r4, r4, #2	@,,
	str	r4, [fp, #-168]	@, %sfp
	ldr	r4, [fp, #-116]	@, %sfp
	ldrsh	r4, [r4, #2]	@,
	str	r4, [fp, #-120]	@, %sfp
	ldr	r4, [fp, #-168]	@, %sfp
	add	r4, r4, #2	@,,
	str	r4, [fp, #-164]	@, %sfp
	ldr	r4, [fp, #-104]	@, %sfp
	mov	r4, r4, asl #10	@,,
	str	r4, [fp, #-116]	@, %sfp
	ldr	r4, [fp, #-164]	@, %sfp
	add	r4, r4, #2	@,,
	str	r4, [fp, #-176]	@, %sfp
	mov	r4, r9, asl #22	@ tmp649, tmp648,
	ldr	r9, [fp, #-116]	@, %sfp
	and	ip, r9, ip	@ tmp643,, tmp643
	ldr	r9, [fp, #-120]	@, %sfp
	mov	r4, r4, lsr #22	@ tmp649, tmp649,
	add	ip, ip, r9, asl #20	@,, tmp643,,
	str	ip, [fp, #-104]	@, %sfp
	ldr	r9, [fp, #-104]	@, %sfp
	mov	ip, r0	@ tmp733, tmp725
	add	r4, r9, r4	@ tmp651,, tmp649
	str	r4, [sl, #316]	@ tmp651, <variable>.s32CoefAttr
	ldr	r4, [fp, #-96]	@, %sfp
	ldrsh	r9, [r4, #2]	@,
	str	r9, [fp, #-96]	@, %sfp
	ldr	r4, [fp, #-176]	@, %sfp
	add	r9, r4, #2	@,,
	ldr	r4, [fp, #-100]	@, %sfp
	str	r9, [fp, #-172]	@, %sfp
	ldrsh	r9, [r4, #2]	@ tmp659,
	ldr	r4, [fp, #-172]	@, %sfp
	add	r4, r4, #2	@,,
	str	r4, [fp, #-160]	@, %sfp
	ldr	r4, [fp, #-56]	@, %sfp
	ldrsh	r4, [r4, #2]	@,
	str	r0, [fp, #-56]	@ tmp4, %sfp
	str	r4, [fp, #-100]	@, %sfp
	ldr	r4, [fp, #-96]	@, %sfp
	mov	r4, r4, asl #10	@,,
	str	r4, [fp, #-96]	@, %sfp
	mov	r4, r9, asl #22	@ tmp660, tmp659,
	ldr	r9, [fp, #-96]	@, %sfp
	and	r0, r9, r0	@ tmp654,, tmp654
	ldr	r9, [fp, #-100]	@, %sfp
	mov	r4, r4, lsr #22	@ tmp660, tmp660,
	add	r0, r0, r9, asl #20	@, tmp658, tmp654,,
	ldr	r9, [fp, #-160]	@, %sfp
	add	r4, r0, r4	@ tmp662, tmp658, tmp660
	add	r9, r9, #2	@,,
	str	r9, [fp, #-128]	@, %sfp
	add	r9, r9, #2	@,,
	str	r9, [fp, #-124]	@, %sfp
	str	r4, [sl, #320]	@ tmp662, <variable>.s32CoefAttr
	add	r9, r9, #2	@,,
	ldr	r4, [fp, #-92]	@, %sfp
	ldrsh	r0, [r4, #2]	@ tmp667,
	ldr	r4, [fp, #-112]	@, %sfp
	str	r9, [fp, #-140]	@, %sfp
	add	r9, r9, #2	@,,
	mov	r0, r0, asl #22	@ tmp668, tmp667,
	ldrsh	r4, [r4, #2]	@,
	str	r9, [fp, #-104]	@, %sfp
	mov	r0, r0, lsr #22	@ tmp668, tmp668,
	mov	r9, r1	@ tmp755, tmp733
	str	r4, [fp, #-92]	@, %sfp
	ldr	r4, [fp, #-104]	@, %sfp
	add	r4, r4, #2	@,,
	str	r4, [fp, #-136]	@, %sfp
	ldr	r4, [fp, #-92]	@, %sfp
	mov	r4, r4, asl #10	@,,
	str	r4, [fp, #-92]	@, %sfp
	ldr	r4, [fp, #-136]	@, %sfp
	add	r4, r4, #2	@,,
	str	r4, [fp, #-120]	@, %sfp
	ldr	r4, [fp, #-92]	@, %sfp
	and	r1, r4, r1	@ tmp665,, tmp665
	add	r4, r1, r0	@ tmp670, tmp665, tmp668
	str	r4, [sl, #324]	@ tmp670, <variable>.s32CoefAttr
	ldr	r1, [fp, #-84]	@, %sfp
	ldr	r0, [fp, #-108]	@, %sfp
	ldrsh	r4, [r1, #2]	@ tmp671,
	ldrsh	r1, [r0, #2]	@,
	mov	r4, r4, asl #10	@, tmp671,
	str	r1, [fp, #-84]	@, %sfp
	mov	r1, r2	@ tmp763, tmp755
	ldr	r0, [fp, #-72]	@, %sfp
	ldrsh	r0, [r0, #2]	@,
	str	r4, [fp, #-92]	@, %sfp
	str	r0, [fp, #-72]	@, %sfp
	ldr	r0, [fp, #-120]	@, %sfp
	add	r0, r0, #2	@,,
	str	r0, [fp, #-116]	@, %sfp
	add	r4, r0, #2	@,,
	ldr	r0, [fp, #-84]	@, %sfp
	str	r4, [fp, #-100]	@, %sfp
	mov	r4, r0, asl #22	@ tmp679,,
	ldr	r0, [fp, #-92]	@, %sfp
	and	r2, r0, r2	@ tmp673,, tmp673
	ldr	r0, [fp, #-72]	@, %sfp
	mov	r4, r4, lsr #22	@ tmp679, tmp679,
	add	r2, r2, r0, asl #20	@, tmp677, tmp673,,
	mov	r0, r3	@ tmp774, tmp763
	add	r4, r2, r4	@ tmp681, tmp677, tmp679
	str	r4, [sl, #328]	@ tmp681, <variable>.s32CoefAttr
	ldr	r2, [fp, #-68]	@, %sfp
	ldrsh	r4, [r2, #2]	@,
	ldr	r2, [fp, #-100]	@, %sfp
	str	r4, [fp, #-72]	@, %sfp
	add	r4, r2, #2	@,,
	ldr	r2, [fp, #-88]	@, %sfp
	str	r4, [fp, #-96]	@, %sfp
	ldrsh	r4, [r2, #2]	@ tmp689,
	ldr	r2, [fp, #-96]	@, %sfp
	add	r2, r2, #2	@,,
	str	r2, [fp, #-92]	@, %sfp
	ldr	r2, [fp, #-80]	@, %sfp
	ldrsh	r2, [r2, #2]	@,
	str	r2, [fp, #-68]	@, %sfp
	ldr	r2, [fp, #-92]	@, %sfp
	add	r2, r2, #2	@,,
	str	r2, [fp, #-112]	@, %sfp
	ldr	r2, [fp, #-72]	@, %sfp
	mov	r2, r2, asl #10	@,,
	str	r2, [fp, #-80]	@, %sfp
	ldr	r2, [fp, #-112]	@, %sfp
	add	r2, r2, #2	@,,
	str	r2, [fp, #-108]	@, %sfp
	mov	r2, r4, asl #22	@ tmp690, tmp689,
	ldr	r4, [fp, #-80]	@, %sfp
	and	r3, r4, r3	@ tmp684,, tmp684
	ldr	r4, [fp, #-68]	@, %sfp
	mov	r2, r2, lsr #22	@ tmp690, tmp690,
	add	r3, r3, r4, asl #20	@, tmp688, tmp684,,
	mov	r4, r7	@ tmp785, tmp774
	add	r2, r3, r2	@ tmp692, tmp688, tmp690
	str	r2, [sl, #332]	@ tmp692, <variable>.s32CoefAttr
	ldr	r3, [fp, #-76]	@, %sfp
	ldrsh	r2, [r3, #2]	@,
	str	r2, [fp, #-76]	@, %sfp
	ldr	r2, [fp, #-60]	@, %sfp
	ldr	r3, [fp, #-108]	@, %sfp
	add	r3, r3, #2	@,,
	str	r3, [fp, #-84]	@, %sfp
	ldrsh	r2, [r2, #2]	@,
	str	r7, [fp, #-60]	@ tmp3, %sfp
	str	r2, [fp, #-68]	@, %sfp
	add	r2, r3, #2	@,,
	str	r2, [fp, #-72]	@, %sfp
	ldr	r2, [fp, #-76]	@, %sfp
	mov	r3, r2, asl #22	@ tmp698,,
	ldr	r2, [fp, #-72]	@, %sfp
	add	r2, r2, #2	@,,
	str	r2, [fp, #-88]	@, %sfp
	ldr	r2, [fp, #-68]	@, %sfp
	mov	r2, r2, asl #10	@,,
	str	r2, [fp, #-76]	@, %sfp
	ldr	r2, [fp, #-88]	@, %sfp
	add	r2, r2, #2	@,,
	str	r2, [fp, #-68]	@, %sfp
	ldr	r2, [fp, #-76]	@, %sfp
	and	r7, r2, r7	@ tmp695,, tmp695
	mov	r2, r3, lsr #22	@ tmp698, tmp698,
	add	r3, r7, r2	@ tmp700, tmp695, tmp698
	str	r3, [sl, #336]	@ tmp700, <variable>.s32CoefAttr
	ldr	r7, [fp, #-52]	@, %sfp
	movw	r2, #:lower16:1047552	@,
	ldrsh	r3, [r7, #2]	@ tmp701,
	ldr	r7, [fp, #-64]	@, %sfp
	str	r2, [fp, #-52]	@, %sfp
	ldrsh	r2, [r7, #2]	@ tmp708,
	ldr	r7, [fp, #-48]	@, %sfp
	str	r6, [fp, #-52]	@ tmp7, %sfp
	ldrsh	r7, [r7, #2]	@,
	str	r7, [fp, #-48]	@, %sfp
	ldr	r7, [fp, #-68]	@, %sfp
	add	r7, r7, #2	@,,
	str	r7, [fp, #-80]	@, %sfp
	mov	r7, r3, asl #10	@ tmp702, tmp701,
	ldr	r3, [fp, #-80]	@, %sfp
	and	r6, r7, r6	@ tmp703, tmp702, tmp703
	add	r3, r3, #2	@,,
	str	r3, [fp, #-76]	@, %sfp
	mov	r3, r2, asl #22	@ tmp709, tmp708,
	ldr	r2, [fp, #-48]	@, %sfp
	ldr	r7, [fp, #-76]	@, %sfp
	mov	r3, r3, lsr #22	@ tmp709, tmp709,
	add	r6, r6, r2, asl #20	@, tmp707, tmp703,,
	add	r2, r7, #2	@,,
	add	r7, r2, #2	@,,
	add	r3, r6, r3	@ tmp711, tmp707, tmp709
	str	r2, [fp, #-64]	@, %sfp
	str	r7, [fp, #-48]	@, %sfp
	str	r3, [sl, #340]	@ tmp711, <variable>.s32CoefAttr
	ldr	r6, [fp, #-132]	@, %sfp
	ldr	r2, [fp, #-152]	@, %sfp
	ldr	r7, [fp, #-156]	@, %sfp
	ldrsh	r6, [r6, #2]	@,
	ldrsh	r3, [r2, #2]	@ tmp712,
	ldrsh	r2, [r7, #2]	@ tmp719,
	mov	r7, r8	@ tmp815, tmp785
	str	r6, [fp, #-132]	@, %sfp
	ldr	r6, [fp, #-48]	@, %sfp
	add	r6, r6, #2	@,,
	str	r6, [fp, #-156]	@, %sfp
	mov	r6, r3, asl #10	@ tmp713, tmp712,
	ldr	r3, [fp, #-156]	@, %sfp
	add	r3, r3, #2	@,,
	str	r3, [fp, #-152]	@, %sfp
	mov	r3, r2, asl #22	@ tmp720, tmp719,
	and	r2, r6, r8	@ tmp714, tmp713, tmp714
	ldr	r6, [fp, #-132]	@, %sfp
	add	r8, r2, r6, asl #20	@, tmp718, tmp714,,
	mov	r2, r3, lsr #22	@ tmp720, tmp720,
	add	r3, r8, r2	@ tmp722, tmp718, tmp720
	str	r3, [sl, #344]	@ tmp722, <variable>.s32CoefAttr
	ldr	r2, [fp, #-148]	@, %sfp
	mov	r6, r5	@ tmp823, tmp815
	ldr	r3, [fp, #-152]	@, %sfp
	ldrsh	r8, [r2, #2]	@ tmp727,
	add	r3, r3, #2	@,,
	ldr	r2, [fp, #-144]	@, %sfp
	str	r3, [fp, #-132]	@, %sfp
	add	r3, r3, #2	@,,
	mov	r8, r8, asl #22	@, tmp727,
	ldrsh	r2, [r2, #2]	@,
	str	r8, [fp, #-192]	@, %sfp
	add	r8, r3, #2	@,,
	str	r8, [fp, #-144]	@, %sfp
	str	r2, [fp, #-184]	@, %sfp
	mov	r2, r5	@ tmp834, tmp823
	ldr	r8, [fp, #-184]	@, %sfp
	str	r3, [fp, #-148]	@, %sfp
	mov	r3, r8, asl #10	@,,
	str	r3, [fp, #-184]	@, %sfp
	ldr	r8, [fp, #-184]	@, %sfp
	and	r3, r8, r5	@ tmp725,, tmp725
	ldr	r8, [fp, #-192]	@, %sfp
	mov	r8, r8, lsr #22	@,,
	add	r5, r3, r8	@ tmp730, tmp725,
	str	r5, [sl, #348]	@ tmp730, <variable>.s32CoefAttr
	ldr	r8, [fp, #-168]	@, %sfp
	ldr	r5, [fp, #-180]	@, %sfp
	ldrsh	r3, [r8, #2]	@,
	str	r3, [fp, #-184]	@, %sfp
	mov	r3, ip	@ tmp845, tmp834
	ldrsh	r8, [r5, #2]	@ tmp738,
	ldr	r5, [fp, #-164]	@, %sfp
	ldrsh	r5, [r5, #2]	@,
	str	r5, [fp, #-168]	@, %sfp
	ldr	r5, [fp, #-184]	@, %sfp
	mov	r5, r5, asl #10	@,,
	str	r5, [fp, #-164]	@, %sfp
	mov	r5, r8, asl #22	@ tmp739, tmp738,
	ldr	r8, [fp, #-164]	@, %sfp
	and	ip, r8, ip	@ tmp733,, tmp733
	ldr	r8, [fp, #-168]	@, %sfp
	add	ip, ip, r8, asl #20	@, tmp737, tmp733,,
	mov	r8, r5, lsr #22	@ tmp739, tmp739,
	add	ip, ip, r8	@ tmp741, tmp737, tmp739
	str	ip, [sl, #352]	@ tmp741, <variable>.s32CoefAttr
	ldr	r5, [fp, #-172]	@, %sfp
	ldr	r8, [fp, #-176]	@, %sfp
	ldrsh	ip, [r5, #2]	@ tmp742,
	ldrsh	r5, [r8, #2]	@ tmp749,
	ldr	r8, [fp, #-160]	@, %sfp
	ldrsh	r8, [r8, #2]	@,
	str	r8, [fp, #-160]	@, %sfp
	mov	r8, ip, asl #10	@ tmp743, tmp742,
	mov	ip, r5, asl #22	@ tmp750, tmp749,
	ldr	r5, [fp, #-56]	@, %sfp
	and	r5, r8, r5	@, tmp743,
	ldr	r8, [fp, #-160]	@, %sfp
	add	r8, r5, r8, asl #20	@,,,,
	mov	r5, ip, lsr #22	@ tmp750, tmp750,
	str	r8, [fp, #-56]	@, %sfp
	add	ip, r8, r5	@ tmp752,, tmp750
	str	ip, [sl, #356]	@ tmp752, <variable>.s32CoefAttr
	ldr	r5, [fp, #-128]	@, %sfp
	ldr	r8, [fp, #-124]	@, %sfp
	ldrsh	ip, [r5, #2]	@ tmp757,
	ldrsh	r5, [r8, #2]	@ tmp753,
	mov	ip, ip, asl #22	@ tmp758, tmp757,
	mov	r5, r5, asl #10	@ tmp754, tmp753,
	and	r9, r5, r9	@ tmp755, tmp754, tmp755
	mov	r8, ip, lsr #22	@ tmp758, tmp758,
	add	ip, r9, r8	@ tmp760, tmp755, tmp758
	str	ip, [sl, #360]	@ tmp760, <variable>.s32CoefAttr
	ldr	r5, [fp, #-104]	@, %sfp
	ldr	r9, [fp, #-140]	@, %sfp
	ldr	r8, [fp, #-136]	@, %sfp
	ldrsh	ip, [r5, #2]	@ tmp761,
	ldrsh	r5, [r9, #2]	@ tmp768,
	ldrsh	r9, [r8, #2]	@ tmp765,
	mov	r8, ip, asl #10	@ tmp762, tmp761,
	mov	ip, r5, asl #22	@ tmp769, tmp768,
	and	r5, r8, r1	@ tmp763, tmp762, tmp763
	add	r8, r5, r9, asl #20	@, tmp767, tmp763, tmp765,
	mov	ip, ip, lsr #22	@ tmp769, tmp769,
	add	r1, r8, ip	@ tmp771, tmp767, tmp769
	str	r1, [sl, #364]	@ tmp771, <variable>.s32CoefAttr
	ldr	r5, [fp, #-116]	@, %sfp
	ldr	r8, [fp, #-120]	@, %sfp
	ldr	r9, [fp, #-100]	@, %sfp
	ldrsh	r1, [r5, #2]	@ tmp772,
	ldrsh	ip, [r8, #2]	@ tmp779,
	ldrsh	r8, [r9, #2]	@ tmp776,
	mov	r5, r1, asl #10	@ tmp773, tmp772,
	mov	r9, ip, asl #22	@ tmp780, tmp779,
	and	ip, r5, r0	@ tmp774, tmp773, tmp774
	add	r0, ip, r8, asl #20	@, tmp778, tmp774, tmp776,
	mov	r8, r9, lsr #22	@ tmp780, tmp780,
	add	r1, r0, r8	@ tmp782, tmp778, tmp780
	str	r1, [sl, #368]	@ tmp782, <variable>.s32CoefAttr
	ldr	ip, [fp, #-96]	@, %sfp
	ldr	r5, [fp, #-92]	@, %sfp
	ldrsh	r9, [ip, #2]	@ tmp787,
	ldrsh	r8, [r5, #2]	@ tmp783,
	mov	r1, r9, asl #22	@ tmp788, tmp787,
	mov	r0, r8, asl #10	@ tmp784, tmp783,
	and	r9, r0, r4	@ tmp785, tmp784, tmp785
	mov	ip, r1, lsr #22	@ tmp788, tmp788,
	add	r5, r9, ip	@ tmp790, tmp785, tmp788
	str	r5, [sl, #372]	@ tmp790, <variable>.s32CoefAttr
	ldr	r4, [fp, #-108]	@, %sfp
	ldr	r8, [fp, #-112]	@, %sfp
	ldr	r9, [fp, #-84]	@, %sfp
	ldrsh	r1, [r4, #2]	@ tmp791,
	ldrsh	r0, [r8, #2]	@ tmp798,
	ldrsh	r4, [r9, #2]	@ tmp795,
	ldr	r5, [fp, #-60]	@, %sfp
	mov	ip, r1, asl #10	@ tmp792, tmp791,
	mov	r8, r0, asl #22	@ tmp799, tmp798,
	and	r0, ip, r5	@, tmp792,
	str	r0, [fp, #-60]	@, %sfp
	add	r9, r0, r4, asl #20	@, tmp797,, tmp795,
	mov	r1, r8, lsr #22	@ tmp799, tmp799,
	add	r5, r9, r1	@ tmp801, tmp797, tmp799
	str	r5, [sl, #376]	@ tmp801, <variable>.s32CoefAttr
	ldr	ip, [fp, #-88]	@, %sfp
	ldr	r8, [fp, #-72]	@, %sfp
	ldr	r0, [fp, #-68]	@, %sfp
	ldrsh	r9, [ip, #2]	@ tmp802,
	ldrsh	r4, [r8, #2]	@ tmp809,
	ldrsh	ip, [r0, #2]	@ tmp806,
	ldr	r5, [fp, #-52]	@, %sfp
	mov	r1, r9, asl #10	@ tmp803, tmp802,
	mov	r0, r4, asl #22	@ tmp810, tmp809,
	and	r8, r1, r5	@, tmp803,
	add	r4, r8, ip, asl #20	@, tmp808,, tmp806,
	mov	r9, r0, lsr #22	@ tmp810, tmp810,
	add	r5, r4, r9	@ tmp812, tmp808, tmp810
	str	r5, [sl, #380]	@ tmp812, <variable>.s32CoefAttr
	ldr	ip, [fp, #-80]	@, %sfp
	ldr	r8, [fp, #-76]	@, %sfp
	ldrsh	r1, [ip, #2]	@ tmp817,
	ldrsh	r0, [r8, #2]	@ tmp813,
	mov	r4, r1, asl #22	@ tmp818, tmp817,
	mov	r9, r0, asl #10	@ tmp814, tmp813,
	and	r5, r9, r7	@ tmp815, tmp814, tmp815
	mov	ip, r4, lsr #22	@ tmp818, tmp818,
	add	r8, r5, ip	@ tmp820, tmp815, tmp818
	str	r8, [sl, #384]	@ tmp820, <variable>.s32CoefAttr
	ldr	r7, [fp, #-48]	@, %sfp
	ldr	r8, [fp, #-156]	@, %sfp
	ldrsh	r0, [r7, #2]	@ tmp821,
	ldr	r7, [fp, #-64]	@, %sfp
	ldrsh	r4, [r8, #2]	@ tmp825,
	mov	r1, r0, asl #10	@ tmp822, tmp821,
	ldrsh	r9, [r7, #2]	@ tmp828,
	and	r6, r1, r6	@ tmp823, tmp822, tmp823
	add	ip, r6, r4, asl #20	@, tmp827, tmp823, tmp825,
	mov	r5, r9, asl #22	@ tmp829, tmp828,
	mov	r0, r5, lsr #22	@ tmp829, tmp829,
	add	r9, ip, r0	@ tmp831, tmp827, tmp829
	str	r9, [sl, #388]	@ tmp831, <variable>.s32CoefAttr
	ldr	r4, [fp, #-152]	@, %sfp
	ldr	r9, [fp, #-132]	@, %sfp
	ldrsh	r1, [r4, #2]	@ tmp839,
	ldr	r4, [fp, #-148]	@, %sfp
	ldrsh	r5, [r9, #2]	@ tmp832,
	ldrsh	r0, [r4, #2]	@ tmp836,
	mov	ip, r5, asl #10	@ tmp833, tmp832,
	mov	r5, r1, asl #22	@ tmp840, tmp839,
	and	r2, ip, r2	@ tmp834, tmp833, tmp834
	add	ip, r2, r0, asl #20	@, tmp838, tmp834, tmp836,
	mov	r1, r5, lsr #22	@ tmp840, tmp840,
	add	r5, ip, r1	@ tmp842, tmp838, tmp840
	str	r5, [sl, #392]	@ tmp842, <variable>.s32CoefAttr
	ldr	r5, [fp, #-144]	@, %sfp
	mov	r0, #204	@ tmp851,
	ldrsh	r2, [r5, #2]	@ tmp847,
	ldrsh	ip, [r5, #4]	@ tmp843,
	str	r0, [sl, #0]	@ tmp851, <variable>.u32Size
	mov	r0, r2, asl #22	@ tmp848, tmp847,
	mov	r1, ip, asl #10	@ tmp844, tmp843,
	and	ip, r1, r3	@ tmp845, tmp844, tmp845
	mov	r2, r0, lsr #22	@ tmp848, tmp848,
	add	r0, ip, r2	@ tmp850, tmp845, tmp848
	str	r0, [sl, #396]	@ tmp850, <variable>.s32CoefAttr
	b	.L6	@
.L19:
	mov	r7, r7, lsr #1	@ prephitmp.272, u32Tap,
.L3:
	mov	r9, #0	@ i,
	mov	r8, r9	@ j, i
.L5:
	cmp	r7, #0	@ prephitmp.272,
	beq	.L9	@,
	ldrsh	r3, [r0, #0]	@ s32CoefTmp1.331,* ps16Coef
	add	r4, r8, #48	@ tmp856, j,
	ldrsh	r5, [r0, #2]	@ s32CoefTmp2.333,
	mov	r2, #2	@ k,
	add	r1, sl, r4, asl #2	@, tmp858, pBitCoef, tmp856,
	cmp	r2, r7	@ k, prephitmp.272
	uxth	ip, r3	@ tmp886, s32CoefTmp1.331
	sub	r4, r7, #1	@ tmp865, prephitmp.272,
	add	r3, r1, #4	@ ivtmp.294, tmp858,
	add	ip, ip, r5, asl #16	@, tmp887, tmp886, s32CoefTmp2.333,
	and	r4, r4, #1	@ tmp866, tmp865,
	str	ip, [r1, #4]	@ tmp887, <variable>.s32CoefAttr
	add	r0, r0, #4	@ ps16Coef, ps16Coef,
	add	ip, r8, #1	@ j.894, j,
	add	r1, r3, #4	@ ivtmp.294, ivtmp.294,
	bhi	.L17	@,
	cmp	r4, #0	@ tmp866,
	beq	.L7	@,
	ldrsh	r4, [r0, #0]	@ s32CoefTmp1.331,* ps16Coef
	add	ip, r2, r8	@ j.894, k, j
	ldrsh	r5, [r0, #2]	@ s32CoefTmp2.333,
	mov	r2, #3	@ k,
	cmp	r2, r7	@ k, prephitmp.272
	add	r0, r0, #4	@ ps16Coef, ps16Coef,
	uxth	r4, r4	@ tmp892, s32CoefTmp1.331
	add	r1, r1, #4	@ ivtmp.294, ivtmp.294,
	add	r4, r4, r5, asl #16	@, tmp893, tmp892, s32CoefTmp2.333,
	str	r4, [r3, #4]	@ tmp893, <variable>.s32CoefAttr
	bhi	.L17	@,
.L7:
	ldrsh	r6, [r0, #2]	@ s32CoefTmp2.333,
	add	r4, r0, #4	@ tmp869, ps16Coef,
	ldrh	r5, [r0, #0]	@ tmp853,* ps16Coef
	mov	r3, r1	@ tmp868, ivtmp.294
	add	ip, r2, #1	@ tmp867, k,
	add	r2, r5, r6, asl #16	@, tmp855, tmp853, s32CoefTmp2.333,
	str	r2, [r3], #4	@ tmp855, <variable>.s32CoefAttr
	ldrsh	r6, [r0, #4]	@ s32CoefTmp1.331,
	add	r2, ip, #1	@ k, tmp867,
	ldrsh	r5, [r4, #2]	@ s32CoefTmp2.333,
	cmp	r2, r7	@ k, prephitmp.272
	add	r0, r4, #4	@ ps16Coef, tmp869,
	add	ip, ip, r8	@ j.894, tmp867, j
	uxth	r6, r6	@ tmp877, s32CoefTmp1.331
	add	r5, r6, r5, asl #16	@, tmp878, tmp877, s32CoefTmp2.333,
	str	r5, [r1, #4]	@ tmp878, <variable>.s32CoefAttr
	add	r1, r3, #4	@ ivtmp.294, tmp868,
	bls	.L7	@,
.L17:
	mov	r8, ip	@ j, j.894
.L9:
	add	r9, r9, #1	@ i, i,
	cmp	r9, #17	@ i,
	bne	.L5	@,
	add	r7, r7, r7, asl #4	@, tmp861, prephitmp.272, prephitmp.272,
	mov	r0, r7, asl #2	@ tmp862, tmp861,
	str	r0, [sl, #0]	@ tmp862, <variable>.u32Size
.L6:
	mov	r0, #0	@,
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
	.fnend
	.size	VZmeTransVpssCoefAlign, .-VZmeTransVpssCoefAlign
	.align	2
	.type	VZmeTransCoefAlign, %function
VZmeTransCoefAlign:
	.fnstart
.LFB660:
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
	cmp	r1, #3	@ enTap,
	bls	.L21	@,
	mov	r5, #6	@ u32Cnt,
.L23:
	mov	ip, #0	@ i,
	mov	r6, ip	@ tmp299, i
.L22:
	add	r1, r2, ip, asl #4	@, tmp161, pBitCoef, i,
	ldrh	r7, [r0, #0]	@ tmp166,* ps16Coef
	add	r3, r1, #8	@ tmp225, tmp224,
	add	ip, ip, #1	@ i, i,
	ldrh	r8, [r1, #4]	@,
	cmp	ip, r5	@ i, u32Cnt
	bfi	r8, r7, #0, #10	@ tmp163, tmp166,,
	strh	r8, [r1, #4]	@ movhi	@ tmp163,
	ldrh	r4, [r0, #2]	@ tmp174,
	ldr	r8, [r1, #4]	@ tmp172,
	bfi	r8, r4, #10, #10	@ tmp172, tmp174,,
	str	r8, [r1, #4]	@ tmp172,
	ldrh	r7, [r0, #4]	@ tmp183,
	mov	r4, r8, lsr #16	@ tmp180, tmp172,
	bfi	r4, r7, #4, #10	@ tmp180, tmp183,,
	strh	r4, [r1, #6]	@ movhi	@ tmp180,
	ldrsh	r7, [r0, #6]	@ u32Tmp,
	ldrb	r4, [r1, #7]	@ zero_extendqisi2	@,
	mov	r8, r7, lsr #2	@ tmp195, u32Tmp,
	bfi	r4, r7, #6, #2	@ tmp189, u32Tmp,,
	strb	r8, [r1, #8]	@ tmp195, <variable>.bits_38
	strb	r4, [r1, #7]	@ tmp189,
	ldr	r8, [r1, #8]	@ tmp201,
	ldrh	r4, [r0, #8]	@ tmp203,
	bfi	r8, r4, #8, #10	@ tmp201, tmp203,,
	str	r8, [r1, #8]	@ tmp201,
	ldrh	r7, [r0, #10]	@ tmp212,
	mov	r4, r8, lsr #16	@ tmp209, tmp201,
	bfi	r4, r7, #2, #10	@ tmp209, tmp212,,
	strh	r4, [r1, #10]	@ movhi	@ tmp209,
	ldrsh	r4, [r0, #12]	@ u32Tmp.1029,
	ldrb	r8, [r1, #11]	@ zero_extendqisi2	@,
	bfi	r8, r4, #4, #4	@ tmp218, u32Tmp.1029,,
	strb	r8, [r1, #11]	@ tmp218,
	ldrb	r1, [r3, #4]	@ zero_extendqisi2	@,
	mov	r7, r4, lsr #4	@ tmp222, u32Tmp.1029,
	ldrh	r4, [r3, #6]	@,
	bfi	r1, r7, #0, #6	@ tmp227, tmp222,,
	strb	r1, [r3, #4]	@ tmp227,
	ldrh	r8, [r0, #14]	@ tmp238,
	ldrh	r7, [r3, #4]	@,
	ldrb	r1, [r3, #8]	@ zero_extendqisi2	@,
	bfi	r7, r8, #6, #10	@ tmp235, tmp238,,
	strh	r7, [r3, #4]	@ movhi	@ tmp235,
	ldrh	r7, [r0, #16]	@ tmp249,
	bfi	r4, r7, #0, #10	@ tmp246, tmp249,,
	strh	r4, [r3, #6]	@ movhi	@ tmp246,
	ldrsh	r7, [r0, #18]	@ u32Tmp.1036,
	ldrb	r4, [r3, #7]	@ zero_extendqisi2	@,
	mov	r8, r7, lsr #6	@ tmp261, u32Tmp.1036,
	bfi	r4, r7, #2, #6	@ tmp257, u32Tmp.1036,,
	bfi	r1, r8, #0, #4	@ tmp266, tmp261,,
	strb	r4, [r3, #7]	@ tmp257,
	strb	r1, [r3, #8]	@ tmp266,
	ldrh	r4, [r0, #20]	@ tmp277,
	ldrh	r1, [r3, #8]	@,
	bfi	r1, r4, #4, #10	@ tmp274, tmp277,,
	strh	r1, [r3, #8]	@ movhi	@ tmp274,
	ldrh	r4, [r0, #22]	@ tmp287,
	add	r0, r0, #24	@ ps16Coef, ps16Coef,
	ldr	r1, [r3, #8]	@ tmp285,
	bfi	r1, r4, #14, #10	@ tmp285, tmp287,,
	str	r1, [r3, #8]	@ tmp285,
	strb	r6, [r3, #11]	@ tmp299, <variable>.bits_12
	bcc	.L22	@,
.L24:
	mov	r5, r5, asl #4	@ tmp297, u32Cnt,
	mov	r0, #0	@,
	str	r5, [r2, #0]	@ tmp297, <variable>.u32Size
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L21:
	movw	r5, #:lower16:.LANCHOR0	@ tmp147,
	movt	r5, #:upper16:.LANCHOR0	@ tmp147,
	add	r1, r5, r1, asl #2	@, tmp150, tmp147, enTap,
	movw	r5, #:lower16:-1431655765	@ tmp158,
	movt	r5, #:upper16:-1431655765	@ tmp158,
	ldr	r3, [r1, #16]	@ tmp152, CSWTCH.222
	add	ip, r3, r3, asl #3	@, tmp155, tmp152, tmp152,
	mov	r1, ip, asl #1	@ tmp156, tmp155,
	umull	ip, r3, r5, r1	@, tmp157, tmp158, tmp156
	movs	r5, r3, lsr #3	@ u32Cnt, tmp157,
	bne	.L23	@,
	b	.L24	@
	.fnend
	.size	VZmeTransCoefAlign, .-VZmeTransCoefAlign
	.align	2
	.global	ALG_VZmeVdpSRCoef
	.type	ALG_VZmeVdpSRCoef, %function
ALG_VZmeVdpSRCoef:
	.fnstart
.LFB664:
	@ args = 0, pretend = 0, frame = 64
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
	movw	r3, #:lower16:.LANCHOR0	@ tmp162,
	movt	r3, #:upper16:.LANCHOR0	@ tmp162,
	ldrh	r9, [r3, #50]	@, s16SRZmeCoef_8T2P_Lanc3
	ldrh	ip, [r3, #48]	@, s16SRZmeCoef_8T2P_Lanc3
	ldrh	r1, [r3, #32]	@ temp.1075, s16SRZmeCoef_8T2P_Lanc3
	str	r9, [fp, #-92]	@, %sfp
	ldrh	r9, [r3, #56]	@, s16SRZmeCoef_8T2P_Lanc3
	ldrh	r2, [r3, #52]	@, s16SRZmeCoef_8T2P_Lanc3
	str	ip, [fp, #-104]	@, %sfp
	str	r9, [fp, #-80]	@, %sfp
	ldrh	ip, [r3, #54]	@, s16SRZmeCoef_8T2P_Lanc3
	ldrh	r9, [r3, #62]	@, s16SRZmeCoef_8T2P_Lanc3
	ldrh	sl, [r3, #36]	@ temp.1077, s16SRZmeCoef_8T2P_Lanc3
	ldrh	r8, [r3, #38]	@ temp.1074, s16SRZmeCoef_8T2P_Lanc3
	ldrh	r7, [r3, #40]	@ temp.1078, s16SRZmeCoef_8T2P_Lanc3
	ldrh	r6, [r3, #42]	@ temp.1079, s16SRZmeCoef_8T2P_Lanc3
	ldrh	r5, [r3, #44]	@ temp.1080, s16SRZmeCoef_8T2P_Lanc3
	ldrh	r4, [r3, #46]	@ D.24172, s16SRZmeCoef_8T2P_Lanc3
	str	r2, [fp, #-88]	@, %sfp
	str	ip, [fp, #-84]	@, %sfp
	ldrh	r2, [r3, #58]	@, s16SRZmeCoef_8T2P_Lanc3
	ldrh	ip, [r3, #60]	@, s16SRZmeCoef_8T2P_Lanc3
	str	r9, [fp, #-100]	@, %sfp
	strh	r1, [r0, #32]	@ movhi	@ temp.1075, <variable>.s16HCCoef0
	ldrh	r9, [r3, #34]	@ temp.1076, s16SRZmeCoef_8T2P_Lanc3
	strh	r1, [r0, #0]	@ movhi	@ temp.1075, <variable>.s16HLCoef0
	ldr	r1, [fp, #-104]	@, %sfp
	str	r2, [fp, #-76]	@, %sfp
	str	ip, [fp, #-72]	@, %sfp
	strh	r9, [r0, #2]	@ movhi	@ temp.1076, <variable>.s16HLCoef0
	strh	sl, [r0, #4]	@ movhi	@ temp.1077, <variable>.s16HLCoef0
	strh	r8, [r0, #6]	@ movhi	@ temp.1074, <variable>.s16HLCoef0
	strh	r7, [r0, #8]	@ movhi	@ temp.1078, <variable>.s16HLCoef0
	strh	r6, [r0, #10]	@ movhi	@ temp.1079, <variable>.s16HLCoef0
	strh	r5, [r0, #12]	@ movhi	@ temp.1080, <variable>.s16HLCoef0
	strh	r4, [r0, #14]	@ movhi	@ D.24172, <variable>.s16HLCoef0
	strh	r1, [r0, #16]	@ movhi	@, <variable>.s16HLCoef1
	ldr	ip, [fp, #-88]	@, %sfp
	ldr	r2, [fp, #-92]	@, %sfp
	ldr	r1, [fp, #-84]	@, %sfp
	strh	ip, [r0, #20]	@ movhi	@, <variable>.s16HLCoef1
	ldr	ip, [fp, #-76]	@, %sfp
	strh	r2, [r0, #18]	@ movhi	@, <variable>.s16HLCoef1
	ldr	r2, [fp, #-80]	@, %sfp
	strh	ip, [r0, #26]	@ movhi	@, <variable>.s16HLCoef1
	ldrh	ip, [r3, #70]	@, s16SRZmeCoef_6T32P_6M_a25
	strh	r1, [r0, #22]	@ movhi	@, <variable>.s16HLCoef1
	strh	r2, [r0, #24]	@ movhi	@, <variable>.s16HLCoef1
	str	ip, [fp, #-68]	@, %sfp
	ldrh	ip, [r3, #72]	@, s16SRZmeCoef_6T32P_6M_a25
	ldr	r1, [fp, #-72]	@, %sfp
	ldr	r2, [fp, #-100]	@, %sfp
	str	ip, [fp, #-64]	@, %sfp
	ldrh	ip, [r3, #74]	@, s16SRZmeCoef_6T32P_6M_a25
	strh	r1, [r0, #28]	@ movhi	@, <variable>.s16HLCoef1
	strh	r2, [r0, #30]	@ movhi	@, <variable>.s16HLCoef1
	str	ip, [fp, #-96]	@, %sfp
	ldrh	ip, [r3, #76]	@, s16SRZmeCoef_6T32P_6M_a25
	ldrh	r1, [r3, #64]	@ temp.1088, s16SRZmeCoef_6T32P_6M_a25
	ldrh	r2, [r3, #66]	@ temp.1089, s16SRZmeCoef_6T32P_6M_a25
	str	ip, [fp, #-60]	@, %sfp
	ldrh	ip, [r3, #78]	@, s16SRZmeCoef_6T32P_6M_a25
	strh	r9, [r0, #34]	@ movhi	@ temp.1076, <variable>.s16HCCoef0
	strh	sl, [r0, #36]	@ movhi	@ temp.1077, <variable>.s16HCCoef0
	str	ip, [fp, #-56]	@, %sfp
	ldrh	ip, [r3, #80]	@, s16SRZmeCoef_6T32P_6M_a25
	ldrh	r9, [r3, #68]	@ temp.1090, s16SRZmeCoef_6T32P_6M_a25
	str	ip, [fp, #-52]	@, %sfp
	ldrh	ip, [r3, #82]	@, s16SRZmeCoef_6T32P_6M_a25
	str	ip, [fp, #-48]	@, %sfp
	strh	r8, [r0, #38]	@ movhi	@ temp.1074, <variable>.s16HCCoef0
	ldr	ip, [fp, #-104]	@, %sfp
	strh	r1, [r0, #64]	@ movhi	@ temp.1088, <variable>.s16VLCoef0
	strh	r2, [r0, #66]	@ movhi	@ temp.1089, <variable>.s16VLCoef0
	strh	ip, [r0, #48]	@ movhi	@, <variable>.s16HCCoef1
	ldr	ip, [fp, #-92]	@, %sfp
	strh	r7, [r0, #40]	@ movhi	@ temp.1078, <variable>.s16HCCoef0
	strh	r6, [r0, #42]	@ movhi	@ temp.1079, <variable>.s16HCCoef0
	strh	ip, [r0, #50]	@ movhi	@, <variable>.s16HCCoef1
	ldr	ip, [fp, #-88]	@, %sfp
	strh	r5, [r0, #44]	@ movhi	@ temp.1080, <variable>.s16HCCoef0
	strh	r4, [r0, #46]	@ movhi	@ D.24172, <variable>.s16HCCoef0
	strh	ip, [r0, #52]	@ movhi	@, <variable>.s16HCCoef1
	ldr	ip, [fp, #-84]	@, %sfp
	strh	r9, [r0, #68]	@ movhi	@ temp.1090, <variable>.s16VLCoef0
	strh	ip, [r0, #54]	@ movhi	@, <variable>.s16HCCoef1
	ldr	ip, [fp, #-80]	@, %sfp
	strh	ip, [r0, #56]	@ movhi	@, <variable>.s16HCCoef1
	ldr	ip, [fp, #-76]	@, %sfp
	strh	ip, [r0, #58]	@ movhi	@, <variable>.s16HCCoef1
	ldr	ip, [fp, #-72]	@, %sfp
	strh	ip, [r0, #60]	@ movhi	@, <variable>.s16HCCoef1
	ldr	ip, [fp, #-100]	@, %sfp
	strh	ip, [r0, #62]	@ movhi	@, <variable>.s16HCCoef1
	ldr	ip, [fp, #-68]	@, %sfp
	strh	ip, [r0, #70]	@ movhi	@, <variable>.s16VLCoef0
	ldr	ip, [fp, #-64]	@, %sfp
	strh	ip, [r0, #72]	@ movhi	@, <variable>.s16VLCoef0
	ldr	ip, [fp, #-96]	@, %sfp
	strh	ip, [r0, #74]	@ movhi	@, <variable>.s16VLCoef0
	ldr	ip, [fp, #-60]	@, %sfp
	strh	ip, [r0, #76]	@ movhi	@, <variable>.s16VLCoef1
	ldr	ip, [fp, #-56]	@, %sfp
	strh	ip, [r0, #78]	@ movhi	@, <variable>.s16VLCoef1
	ldr	ip, [fp, #-52]	@, %sfp
	strh	ip, [r0, #80]	@ movhi	@, <variable>.s16VLCoef1
	strh	r1, [r0, #88]	@ movhi	@ temp.1088, <variable>.s16VCCoef0
	ldr	r1, [fp, #-68]	@, %sfp
	strh	r2, [r0, #90]	@ movhi	@ temp.1089, <variable>.s16VCCoef0
	ldr	r2, [fp, #-64]	@, %sfp
	strh	r1, [r0, #94]	@ movhi	@, <variable>.s16VCCoef0
	ldr	r1, [fp, #-96]	@, %sfp
	ldr	ip, [fp, #-48]	@, %sfp
	strh	r2, [r0, #96]	@ movhi	@, <variable>.s16VCCoef0
	strh	r1, [r0, #98]	@ movhi	@, <variable>.s16VCCoef0
	ldr	r2, [fp, #-60]	@, %sfp
	ldr	r1, [fp, #-56]	@, %sfp
	strh	ip, [r0, #82]	@ movhi	@, <variable>.s16VLCoef1
	strh	r2, [r0, #100]	@ movhi	@, <variable>.s16VCCoef1
	ldrh	ip, [r3, #86]	@ D.24175, s16SRZmeCoef_6T32P_6M_a25
	strh	r1, [r0, #102]	@ movhi	@, <variable>.s16VCCoef1
	ldrh	r3, [r3, #84]	@ temp.1097, s16SRZmeCoef_6T32P_6M_a25
	ldr	r2, [fp, #-52]	@, %sfp
	ldr	r1, [fp, #-48]	@, %sfp
	strh	ip, [r0, #110]	@ movhi	@ D.24175, <variable>.s16VCCoef1
	strh	r9, [r0, #92]	@ movhi	@ temp.1090, <variable>.s16VCCoef0
	strh	r2, [r0, #104]	@ movhi	@, <variable>.s16VCCoef1
	strh	r1, [r0, #106]	@ movhi	@, <variable>.s16VCCoef1
	strh	r3, [r0, #108]	@ movhi	@ temp.1097, <variable>.s16VCCoef1
	strh	r3, [r0, #84]	@ movhi	@ temp.1097, <variable>.s16VLCoef1
	strh	ip, [r0, #86]	@ movhi	@ D.24175, <variable>.s16VLCoef1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
	.fnend
	.size	ALG_VZmeVdpSRCoef, .-ALG_VZmeVdpSRCoef
	.align	2
	.global	ALG_VZmeVdpComnDeInit
	.type	ALG_VZmeVdpComnDeInit, %function
ALG_VZmeVdpComnDeInit:
	.fnstart
.LFB666:
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
	.size	ALG_VZmeVdpComnDeInit, .-ALG_VZmeVdpComnDeInit
	.align	2
	.global	ALG_VZmeVpssComnDeInit
	.type	ALG_VZmeVpssComnDeInit, %function
ALG_VZmeVpssComnDeInit:
	.fnstart
.LFB668:
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
	.size	ALG_VZmeVpssComnDeInit, .-ALG_VZmeVpssComnDeInit
	.align	2
	.type	GetVerticalScalerOffset, %function
GetVerticalScalerOffset:
	.fnstart
.LFB669:
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
	ldr	r3, [r1, #20]	@ <variable>.bZmeFrmFmtIn, <variable>.bZmeFrmFmtIn
	cmp	r3, #0	@ <variable>.bZmeFrmFmtIn,
	beq	.L34	@,
	ldr	r2, [r1, #24]	@ <variable>.bZmeFrmFmtOut, <variable>.bZmeFrmFmtOut
	cmp	r2, #0	@ <variable>.bZmeFrmFmtOut,
	bne	.L35	@,
.L39:
	ldr	ip, [r1, #32]	@ <variable>.bZmeBFOut, <variable>.bZmeBFOut
	cmp	ip, #0	@ <variable>.bZmeBFOut,
	movne	r0, r0, asr #1	@ s32VOffset, u32VRatio,
	ldmnefd	sp, {fp, sp, pc}	@
.L35:
	mov	r0, #0	@ s32VOffset,
	ldmfd	sp, {fp, sp, pc}	@
.L34:
	ldr	ip, [r1, #24]	@ <variable>.bZmeFrmFmtOut, <variable>.bZmeFrmFmtOut
	cmp	ip, #0	@ <variable>.bZmeFrmFmtOut,
	bne	.L43	@,
	ldr	r3, [r1, #28]	@ <variable>.bZmeBFIn, <variable>.bZmeBFIn
	cmp	r3, #0	@ <variable>.bZmeBFIn,
	beq	.L39	@,
	ldr	r2, [r1, #32]	@ <variable>.bZmeBFOut, <variable>.bZmeBFOut
	cmp	r2, #0	@ <variable>.bZmeBFOut,
	subne	r0, r0, #4096	@ tmp144, u32VRatio,
	movne	r0, r0, asr #1	@ s32VOffset, tmp144,
	ldmnefd	sp, {fp, sp, pc}	@
	b	.L38	@
.L43:
	ldr	r0, [r1, #28]	@ <variable>.bZmeBFIn, <variable>.bZmeBFIn
	cmp	r0, #0	@ <variable>.bZmeBFIn,
	beq	.L35	@,
.L38:
	movw	r0, #:lower16:-2048	@ s32VOffset,
	movt	r0, #:upper16:-2048	@ s32VOffset,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	GetVerticalScalerOffset, .-GetVerticalScalerOffset
	.global	__aeabi_uidiv
	.align	2
	.type	GetHLfirCoef, %function
GetHLfirCoef:
	.fnstart
.LFB672:
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
	mov	r4, r0	@ pstCoefAddr, pstCoefAddr
	mov	r0, #16777216	@,
	bl	__aeabi_uidiv	@
	cmp	r0, #4096	@ tmp140,
	ldrhi	r0, [r4, #0]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHL8_1
	ldmhifd	sp, {r3, r4, fp, sp, pc}	@
	ldreq	r0, [r4, #4]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHL8_E1
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r0, #3072	@ tmp140,
	ldrcs	r0, [r4, #8]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHL8_075
	ldmcsfd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r0, #2048	@ tmp140,
	ldrcs	r0, [r4, #12]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHL8_05
	ldmcsfd	sp, {r3, r4, fp, sp, pc}	@
	movw	r3, #1364	@ tmp143,
	cmp	r0, r3	@ tmp140, tmp143
	ldrhi	r0, [r4, #16]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHL8_033
	ldmhifd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r0, #1024	@ tmp140,
	ldrcs	r0, [r4, #20]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHL8_025
	ldrcc	r0, [r4, #24]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHL8_0
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	GetHLfirCoef, .-GetHLfirCoef
	.align	2
	.type	GetHCfirCoef, %function
GetHCfirCoef:
	.fnstart
.LFB673:
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
	mov	r4, r0	@ pstCoefAddr, pstCoefAddr
	mov	r0, #16777216	@,
	bl	__aeabi_uidiv	@
	cmp	r0, #4096	@ tmp140,
	ldrhi	r0, [r4, #28]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHC4_1
	ldmhifd	sp, {r3, r4, fp, sp, pc}	@
	ldreq	r0, [r4, #32]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHC4_E1
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r0, #3072	@ tmp140,
	ldrcs	r0, [r4, #36]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHC4_075
	ldmcsfd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r0, #2048	@ tmp140,
	ldrcs	r0, [r4, #40]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHC4_05
	ldmcsfd	sp, {r3, r4, fp, sp, pc}	@
	movw	r3, #1364	@ tmp143,
	cmp	r0, r3	@ tmp140, tmp143
	ldrhi	r0, [r4, #44]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHC4_033
	ldmhifd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r0, #1024	@ tmp140,
	ldrcs	r0, [r4, #48]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHC4_025
	ldrcc	r0, [r4, #52]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHC4_0
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	GetHCfirCoef, .-GetHCfirCoef
	.align	2
	.type	GetVCfirCoef, %function
GetVCfirCoef:
	.fnstart
.LFB675:
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
	mov	r4, r0	@ pstCoefAddr, pstCoefAddr
	mov	r0, #16777216	@,
	bl	__aeabi_uidiv	@
	cmp	r0, #4096	@ tmp140,
	ldrhi	r0, [r4, #84]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVC4_1
	ldmhifd	sp, {r3, r4, fp, sp, pc}	@
	ldreq	r0, [r4, #88]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVC4_E1
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r0, #3072	@ tmp140,
	ldrcs	r0, [r4, #92]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVC4_075
	ldmcsfd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r0, #2048	@ tmp140,
	ldrcs	r0, [r4, #96]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVC4_05
	ldmcsfd	sp, {r3, r4, fp, sp, pc}	@
	movw	r3, #1364	@ tmp143,
	cmp	r0, r3	@ tmp140, tmp143
	ldrhi	r0, [r4, #100]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVC4_033
	ldmhifd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r0, #1024	@ tmp140,
	ldrcs	r0, [r4, #104]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVC4_025
	ldrcc	r0, [r4, #108]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVC4_0
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	GetVCfirCoef, .-GetVCfirCoef
	.align	2
	.type	GetVLFilterCoef, %function
GetVLFilterCoef:
	.fnstart
.LFB676:
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
	mov	r4, r0	@ pstCoefAddr, pstCoefAddr
	mov	r0, #16777216	@,
	bl	__aeabi_uidiv	@
	cmp	r0, #4096	@ tmp140,
	ldrhi	r0, [r4, #56]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVL6_1
	ldmhifd	sp, {r3, r4, fp, sp, pc}	@
	ldreq	r0, [r4, #60]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVL6_E1
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r0, #3072	@ tmp140,
	ldrcs	r0, [r4, #64]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVL6_075
	ldmcsfd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r0, #2048	@ tmp140,
	ldrcs	r0, [r4, #68]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVL6_05
	ldmcsfd	sp, {r3, r4, fp, sp, pc}	@
	movw	r3, #1364	@ tmp143,
	cmp	r0, r3	@ tmp140, tmp143
	ldrhi	r0, [r4, #72]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVL6_033
	ldmhifd	sp, {r3, r4, fp, sp, pc}	@
	cmp	r0, #1024	@ tmp140,
	ldrcs	r0, [r4, #76]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVL6_025
	ldrcc	r0, [r4, #80]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVL6_0
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	GetVLFilterCoef, .-GetVLFilterCoef
	.align	2
	.global	ALG_VZmeComnSet
	.type	ALG_VZmeComnSet, %function
ALG_VZmeComnSet:
	.fnstart
.LFB679:
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
	mov	r2, #1	@ tmp154,
	mov	r5, r0	@ pstZmeDrvPara, pstZmeDrvPara
	str	r2, [r1, #12]	@ tmp154, <variable>.bZmeEnVC
	str	r2, [r1, #0]	@ tmp154, <variable>.bZmeEnHL
	mov	r3, #0	@ tmp158,
	str	r2, [r1, #4]	@ tmp154, <variable>.bZmeEnHC
	mov	r4, r1	@ pstZmeRtlPara, pstZmeRtlPara
	str	r3, [r1, #44]	@ tmp158, <variable>.bZmeMedVC
	str	r2, [r1, #8]	@ tmp154, <variable>.bZmeEnVL
	str	r3, [r1, #32]	@ tmp158, <variable>.bZmeMedHL
	str	r3, [r1, #36]	@ tmp158, <variable>.bZmeMedHC
	str	r3, [r1, #40]	@ tmp158, <variable>.bZmeMedVL
	ldr	r0, [r0, #0]	@ D.24490, <variable>.u32ZmeFrmWIn
	cmp	r0, #4096	@ D.24490,
	str	r0, [r1, #72]	@ D.24490, <variable>.u32ZmeWIn
	ldr	r1, [r5, #8]	@ D.24491, <variable>.u32ZmeFrmWOut
	str	r1, [r4, #80]	@ D.24491, <variable>.u32ZmeWOut
	ldr	r7, [r5, #4]	@ D.24492, <variable>.u32ZmeFrmHIn
	str	r7, [r4, #76]	@ D.24492, <variable>.u32ZmeHIn
	ldr	r6, [r5, #12]	@ D.24493, <variable>.u32ZmeFrmHOut
	str	r6, [r4, #84]	@ D.24493, <variable>.u32ZmeHOut
	bcc	.L81	@,
	mov	r8, r0, lsr r2	@ tmp163, D.24490,
	mov	r0, r8, asl #20	@, tmp163,
	bl	__aeabi_uidiv	@
	mov	r0, r0, asl #1	@ tmp169,,
	str	r0, [r4, #88]	@ tmp169, <variable>.u32ZmeRatioHL
.L82:
	mov	r1, r6	@, D.24493
	mov	r0, r7, asl #12	@, D.24492,
	bl	__aeabi_uidiv	@
	ldr	r1, [r4, #80]	@ u32ZmeCWOut, <variable>.u32ZmeWOut
	ldr	r7, [r4, #76]	@ <variable>.u32ZmeHIn, <variable>.u32ZmeHIn
	str	r0, [r4, #92]	@, <variable>.u32ZmeRatioVL
	ldr	r0, [r4, #72]	@ u32ZmeCWIn, <variable>.u32ZmeWIn
	ldrb	r2, [r5, #16]	@ zero_extendqisi2	@ D.24510, <variable>.u8ZmeYCFmtIn
	ldrb	r6, [r5, #17]	@ zero_extendqisi2	@ D.24515, <variable>.u8ZmeYCFmtOut
	cmp	r2, #2	@ D.24510,
	movne	r0, r0, lsr #1	@ u32ZmeCWIn, <variable>.u32ZmeWIn,
	cmp	r6, #2	@ D.24515,
	movne	r1, r1, lsr #1	@ u32ZmeCWOut, <variable>.u32ZmeWOut,
	cmp	r2, #1	@ D.24510,
	moveq	r7, r7, lsr #1	@ u32ZmeCHIn, <variable>.u32ZmeHIn,
	cmp	r6, #1	@ D.24515,
	ldr	r6, [r4, #84]	@ <variable>.u32ZmeHOut, <variable>.u32ZmeHOut
	moveq	r6, r6, lsr #1	@ u32ZmeCHOut, <variable>.u32ZmeHOut,
	cmp	r0, #4096	@ u32ZmeCWIn,
	bcc	.L91	@,
	mov	ip, r0, lsr #1	@ tmp183, u32ZmeCWIn,
	mov	r0, ip, asl #20	@, tmp183,
	bl	__aeabi_uidiv	@
	mov	r1, r0, asl #1	@ tmp189,,
	mov	r0, r7, asl #12	@, u32ZmeCHIn,
	str	r1, [r4, #96]	@ tmp189, <variable>.u32ZmeRatioHC
	mov	r1, r6	@, u32ZmeCHOut
	bl	__aeabi_uidiv	@
	str	r0, [r4, #100]	@ u32ZmeRatioVCReal, <variable>.u32ZmeRatioVC
	mov	r6, r0	@ u32ZmeRatioVCReal,
	ldr	r7, [r5, #20]	@ <variable>.bZmeFrmFmtIn, <variable>.bZmeFrmFmtIn
	cmp	r7, #1	@ <variable>.bZmeFrmFmtIn,
	beq	.L109	@,
.L93:
	ldr	r8, [r4, #92]	@ u32ZmeRatioVLReal, <variable>.u32ZmeRatioVL
.L94:
	mov	r7, #0	@ tmp201,
	mov	r0, r8	@, u32ZmeRatioVLReal
	str	r7, [r4, #48]	@ tmp201, <variable>.s32ZmeOffsetHL
	mov	r1, r5	@, pstZmeDrvPara
	str	r7, [r5, #32]	@ tmp201, <variable>.bZmeBFOut
	bl	GetVerticalScalerOffset	@
	str	r0, [r4, #56]	@, <variable>.s32ZmeOffsetVL
	ldrb	r0, [r5, #16]	@ zero_extendqisi2	@ <variable>.u8ZmeYCFmtIn, <variable>.u8ZmeYCFmtIn
	cmp	r0, #1	@ <variable>.u8ZmeYCFmtIn,
	beq	.L110	@,
.L96:
	mov	lr, #0	@ tmp206,
	mov	r1, r5	@, pstZmeDrvPara
	str	lr, [r4, #52]	@ tmp206, <variable>.s32ZmeOffsetHC
	mov	r0, r6	@, u32ZmeRatioVCReal
	bl	GetVerticalScalerOffset	@
	mov	r3, #1	@ tmp208,
	mov	r1, r5	@, pstZmeDrvPara
	add	r0, r0, r7	@ tmp207,, s32VOffset
	str	r0, [r4, #60]	@ tmp207, <variable>.s32ZmeOffsetVC
	str	r3, [r5, #32]	@ tmp208, <variable>.bZmeBFOut
	mov	r0, r8	@, u32ZmeRatioVLReal
	bl	GetVerticalScalerOffset	@
	mov	r1, r5	@, pstZmeDrvPara
	str	r0, [r4, #64]	@, <variable>.s32ZmeOffsetVLBtm
	mov	r0, r6	@, u32ZmeRatioVCReal
	bl	GetVerticalScalerOffset	@
	ldr	r3, [r4, #88]	@ <variable>.u32ZmeRatioHL, <variable>.u32ZmeRatioHL
	ldr	r2, [r4, #96]	@ <variable>.u32ZmeRatioHC, <variable>.u32ZmeRatioHC
	ldr	r1, [r4, #92]	@ <variable>.u32ZmeRatioVL, <variable>.u32ZmeRatioVL
	subs	ip, r3, #1048576	@ tmp211, <variable>.u32ZmeRatioHL,
	movne	ip, #1	@ tmp211
	subs	r2, r2, #1048576	@ tmp213, <variable>.u32ZmeRatioHC,
	movne	r2, #1	@ tmp213
	str	ip, [r4, #16]	@ tmp211, <variable>.bZmeMdHL
	cmp	r1, #4096	@ <variable>.u32ZmeRatioVL,
	str	r2, [r4, #20]	@ tmp213, <variable>.bZmeMdHC
	add	r7, r0, r7	@ tmp209,, s32VOffset
	str	r7, [r4, #68]	@ tmp209, <variable>.s32ZmeOffsetVCBtm
	beq	.L111	@,
.L98:
	mov	r2, #1	@ tmp217,
.L107:
	ldr	r1, [r4, #100]	@ <variable>.u32ZmeRatioVC, <variable>.u32ZmeRatioVC
	str	r2, [r4, #24]	@ tmp217, <variable>.bZmeMdVL
	cmp	r1, #4096	@ <variable>.u32ZmeRatioVC,
	beq	.L112	@,
.L100:
	mov	r2, #1	@ tmp221,
.L108:
	str	r2, [r4, #28]	@ tmp221, <variable>.bZmeMdVC
	ldr	ip, [r5, #60]	@ <variable>.bDispProgressive, <variable>.bDispProgressive
	cmp	ip, #0	@ <variable>.bDispProgressive,
	bne	.L102	@,
	ldr	r2, [r5, #64]	@ <variable>.u32Fidelity, <variable>.u32Fidelity
	cmp	r2, #0	@ <variable>.u32Fidelity,
	bne	.L102	@,
	ldr	r0, [r5, #44]	@ <variable>.stOriRect.s32Width, <variable>.stOriRect.s32Width
	ldr	lr, [r5, #8]	@ <variable>.u32ZmeFrmWOut, <variable>.u32ZmeFrmWOut
	cmp	r0, lr	@ <variable>.stOriRect.s32Width, <variable>.u32ZmeFrmWOut
	beq	.L113	@,
	ldr	r1, [r5, #48]	@ prephitmp.1280, <variable>.stOriRect.s32Height
	ldr	r2, [r5, #12]	@ prephitmp.1291, <variable>.u32ZmeFrmHOut
.L104:
	cmp	r1, r2	@ prephitmp.1280, prephitmp.1291
	bls	.L102	@,
.L105:
	mov	r2, #1	@ tmp228,
	str	r2, [r4, #28]	@ tmp228, <variable>.bZmeMdVC
	str	r2, [r4, #16]	@ tmp228, <variable>.bZmeMdHL
	str	r2, [r4, #20]	@ tmp228, <variable>.bZmeMdHC
	str	r2, [r4, #24]	@ tmp228, <variable>.bZmeMdVL
.L102:
	cmp	r3, #1048576	@ <variable>.u32ZmeRatioHL,
	movcs	r1, #0	@, tmp235
	movcc	r1, #1	@, tmp235
	mov	lr, #0	@ tmp232,
	str	r1, [r4, #104]	@ tmp235, <variable>.bZmeOrder
	str	lr, [r4, #108]	@ tmp232, <variable>.bZmeTapVC
	ldrb	r0, [r5, #16]	@ zero_extendqisi2	@ <variable>.u8ZmeYCFmtIn, <variable>.u8ZmeYCFmtIn
	strb	r0, [r4, #112]	@ <variable>.u8ZmeYCFmtIn, <variable>.u8ZmeYCFmtIn
	ldrb	r3, [r5, #17]	@ zero_extendqisi2	@ <variable>.u8ZmeYCFmtOut, <variable>.u8ZmeYCFmtOut
	strb	r3, [r4, #113]	@ <variable>.u8ZmeYCFmtOut, <variable>.u8ZmeYCFmtOut
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, fp, sp, pc}	@
.L91:
	mov	r0, r0, asl #20	@, u32ZmeCWIn,
	bl	__aeabi_uidiv	@
	mov	r1, r6	@, u32ZmeCHOut
	str	r0, [r4, #96]	@, <variable>.u32ZmeRatioHC
	mov	r0, r7, asl #12	@, u32ZmeCHIn,
	bl	__aeabi_uidiv	@
	str	r0, [r4, #100]	@ u32ZmeRatioVCReal, <variable>.u32ZmeRatioVC
	mov	r6, r0	@ u32ZmeRatioVCReal,
	ldr	r7, [r5, #20]	@ <variable>.bZmeFrmFmtIn, <variable>.bZmeFrmFmtIn
	cmp	r7, #1	@ <variable>.bZmeFrmFmtIn,
	bne	.L93	@,
.L109:
	ldr	lr, [r5, #24]	@ <variable>.bZmeFrmFmtOut, <variable>.bZmeFrmFmtOut
	cmp	lr, #0	@ <variable>.bZmeFrmFmtOut,
	bne	.L93	@,
	ldr	r3, [r4, #92]	@ <variable>.u32ZmeRatioVL, <variable>.u32ZmeRatioVL
	mov	r6, r0, asl #1	@ u32ZmeRatioVCReal, u32ZmeRatioVCReal,
	mov	r8, r3, asl #1	@ u32ZmeRatioVLReal, <variable>.u32ZmeRatioVL,
	b	.L94	@
.L81:
	mov	r0, r0, asl #20	@, D.24490,
	bl	__aeabi_uidiv	@
	str	r0, [r4, #88]	@, <variable>.u32ZmeRatioHL
	b	.L82	@
.L112:
	ldr	r2, [r4, #60]	@ <variable>.s32ZmeOffsetVC, <variable>.s32ZmeOffsetVC
	cmp	r2, #0	@ <variable>.s32ZmeOffsetVC,
	bne	.L100	@,
	b	.L108	@
.L111:
	ldr	r2, [r4, #56]	@ <variable>.s32ZmeOffsetVL, <variable>.s32ZmeOffsetVL
	cmp	r2, #0	@ <variable>.s32ZmeOffsetVL,
	bne	.L98	@,
	b	.L107	@
.L110:
	ldr	r2, [r5, #20]	@ <variable>.bZmeFrmFmtIn, <variable>.bZmeFrmFmtIn
	cmp	r2, r7	@ <variable>.bZmeFrmFmtIn,
	beq	.L114	@,
.L97:
	movw	r7, #:lower16:-512	@ s32VOffset,
	movt	r7, #:upper16:-512	@ s32VOffset,
	b	.L96	@
.L114:
	ldr	r1, [r5, #28]	@ <variable>.bZmeBFIn, <variable>.bZmeBFIn
	cmp	r1, r7	@ <variable>.bZmeBFIn,
	movwne	r7, #:lower16:-1536	@ s32VOffset,
	movtne	r7, #:upper16:-1536	@ s32VOffset,
	bne	.L96	@,
	b	.L97	@
.L113:
	ldr	r1, [r5, #48]	@ prephitmp.1280, <variable>.stOriRect.s32Height
	ldr	r2, [r5, #12]	@ prephitmp.1291, <variable>.u32ZmeFrmHOut
	cmp	r1, r2	@ prephitmp.1280, prephitmp.1291
	bne	.L104	@,
	ldr	r1, [r5, #52]	@ <variable>.u32InRate, <variable>.u32InRate
	ldr	ip, [r5, #56]	@ <variable>.u32OutRate, <variable>.u32OutRate
	cmp	r1, ip	@ <variable>.u32InRate, <variable>.u32OutRate
	bne	.L105	@,
	b	.L102	@
	.fnend
	.size	ALG_VZmeComnSet, .-ALG_VZmeComnSet
	.align	2
	.global	ALG_VZmeVpssComnSet
	.type	ALG_VZmeVpssComnSet, %function
ALG_VZmeVpssComnSet:
	.fnstart
.LFB680:
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
	mov	r5, r0	@ pstZmeDrvPara, pstZmeDrvPara
	mov	r2, #1	@ tmp150,
	mov	r0, #0	@ tmp154,
	str	r2, [r1, #12]	@ tmp150, <variable>.bZmeEnVC
	mov	r4, r1	@ pstZmeRtlPara, pstZmeRtlPara
	str	r2, [r1, #0]	@ tmp150, <variable>.bZmeEnHL
	str	r0, [r1, #44]	@ tmp154, <variable>.bZmeMedVC
	str	r2, [r1, #4]	@ tmp150, <variable>.bZmeEnHC
	str	r2, [r1, #8]	@ tmp150, <variable>.bZmeEnVL
	str	r0, [r1, #32]	@ tmp154, <variable>.bZmeMedHL
	str	r0, [r1, #36]	@ tmp154, <variable>.bZmeMedHC
	str	r0, [r1, #40]	@ tmp154, <variable>.bZmeMedVL
	ldr	r0, [r5, #0]	@ D.24604, <variable>.u32ZmeFrmWIn
	str	r0, [r1, #72]	@ D.24604, <variable>.u32ZmeWIn
	ldr	r1, [r5, #8]	@ D.24605, <variable>.u32ZmeFrmWOut
	str	r1, [r4, #80]	@ D.24605, <variable>.u32ZmeWOut
	ldr	r6, [r5, #20]	@ <variable>.bZmeFrmFmtIn, <variable>.bZmeFrmFmtIn
	ldr	r7, [r5, #4]	@ iftmp.212, <variable>.u32ZmeFrmHIn
	cmp	r6, r2	@ <variable>.bZmeFrmFmtIn,
	movne	r7, r7, lsr #1	@ iftmp.212, <variable>.u32ZmeFrmHIn,
	str	r7, [r4, #76]	@ iftmp.212, <variable>.u32ZmeHIn
	ldr	r3, [r5, #24]	@ <variable>.bZmeFrmFmtOut, <variable>.bZmeFrmFmtOut
	ldr	r6, [r5, #12]	@ iftmp.213, <variable>.u32ZmeFrmHOut
	cmp	r3, #1	@ <variable>.bZmeFrmFmtOut,
	movne	r6, r6, lsr #1	@ iftmp.213, <variable>.u32ZmeFrmHOut,
	cmp	r0, #4096	@ D.24604,
	str	r6, [r4, #84]	@ iftmp.213, <variable>.u32ZmeHOut
	bcc	.L120	@,
	mov	r8, r0, lsr #1	@ tmp163, D.24604,
	mov	r0, r8, asl #20	@, tmp163,
	bl	__aeabi_uidiv	@
	mov	r1, r0, asl #1	@ tmp169,,
	str	r1, [r4, #88]	@ tmp169, <variable>.u32ZmeRatioHL
.L121:
	mov	r1, r6	@, iftmp.213
	mov	r0, r7, asl #12	@, iftmp.212,
	bl	__aeabi_uidiv	@
	ldr	r1, [r4, #80]	@ u32ZmeCWOut, <variable>.u32ZmeWOut
	ldr	r6, [r4, #76]	@ <variable>.u32ZmeHIn, <variable>.u32ZmeHIn
	str	r0, [r4, #92]	@, <variable>.u32ZmeRatioVL
	ldrb	sl, [r5, #16]	@ zero_extendqisi2	@ D.24634, <variable>.u8ZmeYCFmtIn
	ldrb	r7, [r5, #17]	@ zero_extendqisi2	@ D.24639, <variable>.u8ZmeYCFmtOut
	cmp	sl, #2	@ D.24634,
	ldrne	ip, [r4, #72]	@ u32ZmeCWIn.1324, <variable>.u32ZmeWIn
	ldreq	r0, [r4, #72]	@ u32ZmeCWIn, <variable>.u32ZmeWIn
	movne	r0, ip, lsr #1	@ u32ZmeCWIn, u32ZmeCWIn.1324,
	moveq	ip, r0	@ u32ZmeCWIn.1324, u32ZmeCWIn
	cmp	r7, #2	@ D.24639,
	movne	r1, r1, lsr #1	@ u32ZmeCWOut, <variable>.u32ZmeWOut,
	cmp	sl, #1	@ D.24634,
	moveq	r6, r6, lsr #1	@ u32ZmeCHIn, <variable>.u32ZmeHIn,
	cmp	r7, #1	@ D.24639,
	ldr	r7, [r4, #84]	@ <variable>.u32ZmeHOut, <variable>.u32ZmeHOut
	moveq	r7, r7, lsr #1	@ u32ZmeCHOut, <variable>.u32ZmeHOut,
	cmp	ip, #4096	@ u32ZmeCWIn.1324,
	bcc	.L130	@,
	mov	lr, r0, lsr #1	@ tmp182, u32ZmeCWIn,
	mov	r0, lr, asl #20	@, tmp182,
	bl	__aeabi_uidiv	@
	mov	ip, r0, asl #1	@ tmp188,,
	str	ip, [r4, #96]	@ tmp188, <variable>.u32ZmeRatioHC
.L131:
	mov	r1, r7	@, u32ZmeCHOut
	mov	r0, r6, asl #12	@, u32ZmeCHIn,
	bl	__aeabi_uidiv	@
	ldr	r7, [r4, #92]	@ <variable>.u32ZmeRatioVL, <variable>.u32ZmeRatioVL
	mov	r8, #0	@ tmp197,
	mov	r1, r5	@, pstZmeDrvPara
	str	r8, [r4, #48]	@ tmp197, <variable>.s32ZmeOffsetHL
	mov	r6, r0	@ D.24661,
	str	r0, [r4, #100]	@ D.24661, <variable>.u32ZmeRatioVC
	mov	r0, r7	@, <variable>.u32ZmeRatioVL
	bl	GetVerticalScalerOffset	@
	mov	r1, r5	@, pstZmeDrvPara
	str	r8, [r4, #52]	@ tmp197, <variable>.s32ZmeOffsetHC
	mov	sl, r0	@ D.24663,
	mov	r0, r6	@, D.24661
	str	sl, [r4, #56]	@ D.24663, <variable>.s32ZmeOffsetVL
	bl	GetVerticalScalerOffset	@
	ldr	r3, [r4, #88]	@ <variable>.u32ZmeRatioHL, <variable>.u32ZmeRatioHL
	ldr	ip, [r4, #96]	@ <variable>.u32ZmeRatioHC, <variable>.u32ZmeRatioHC
	subs	r1, r3, #1048576	@ tmp201, <variable>.u32ZmeRatioHL,
	movne	r1, #1	@ tmp201
	str	r1, [r4, #16]	@ tmp201, <variable>.bZmeMdHL
	subs	r2, ip, #1048576	@ tmp203, <variable>.u32ZmeRatioHC,
	movne	r2, #1	@ tmp203
	cmp	r7, #4096	@ <variable>.u32ZmeRatioVL,
	str	r2, [r4, #20]	@ tmp203, <variable>.bZmeMdHC
	str	r0, [r4, #60]	@, <variable>.s32ZmeOffsetVC
	beq	.L138	@,
.L132:
	mov	r0, #1	@ tmp206,
	str	r0, [r4, #24]	@ tmp206, <variable>.bZmeMdVL
.L133:
	cmp	r6, #4096	@ D.24661,
	beq	.L139	@,
.L134:
	mov	r2, #1	@ tmp209,
.L137:
	str	r2, [r4, #28]	@ tmp209, <variable>.bZmeMdVC
	mov	ip, #1	@ tmp210,
	cmp	r3, #1048576	@ <variable>.u32ZmeRatioHL,
	movcs	r1, #0	@, tmp217
	movcc	r1, #1	@, tmp217
	str	ip, [r4, #28]	@ tmp210, <variable>.bZmeMdVC
	str	r1, [r4, #104]	@ tmp217, <variable>.bZmeOrder
	mov	r2, #0	@ tmp214,
	str	ip, [r4, #16]	@ tmp210, <variable>.bZmeMdHL
	mov	r0, r2	@, tmp214
	str	ip, [r4, #20]	@ tmp210, <variable>.bZmeMdHC
	str	ip, [r4, #24]	@ tmp210, <variable>.bZmeMdVL
	str	r2, [r4, #108]	@ tmp214, <variable>.bZmeTapVC
	ldrb	lr, [r5, #16]	@ zero_extendqisi2	@ <variable>.u8ZmeYCFmtIn, <variable>.u8ZmeYCFmtIn
	strb	lr, [r4, #112]	@ <variable>.u8ZmeYCFmtIn, <variable>.u8ZmeYCFmtIn
	ldrb	r3, [r5, #17]	@ zero_extendqisi2	@ <variable>.u8ZmeYCFmtOut, <variable>.u8ZmeYCFmtOut
	strb	r3, [r4, #113]	@ <variable>.u8ZmeYCFmtOut, <variable>.u8ZmeYCFmtOut
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
.L130:
	mov	r0, r0, asl #20	@, u32ZmeCWIn,
	bl	__aeabi_uidiv	@
	str	r0, [r4, #96]	@, <variable>.u32ZmeRatioHC
	b	.L131	@
.L120:
	mov	r0, r0, asl #20	@, D.24604,
	bl	__aeabi_uidiv	@
	str	r0, [r4, #88]	@, <variable>.u32ZmeRatioHL
	b	.L121	@
.L139:
	ldr	r2, [r4, #60]	@ <variable>.s32ZmeOffsetVC, <variable>.s32ZmeOffsetVC
	cmp	r2, #0	@ <variable>.s32ZmeOffsetVC,
	bne	.L134	@,
	b	.L137	@
.L138:
	cmp	sl, r8	@ D.24663,
	streq	sl, [r4, #24]	@ D.24663, <variable>.bZmeMdVL
	beq	.L133	@,
	b	.L132	@
	.fnend
	.size	ALG_VZmeVpssComnSet, .-ALG_VZmeVpssComnSet
	.align	2
	.global	ALG_VZmeVdpHQSet
	.type	ALG_VZmeVdpHQSet, %function
ALG_VZmeVdpHQSet:
	.fnstart
.LFB681:
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
	mov	r4, r2	@ pstZmeRtlPara, pstZmeRtlPara
	mov	r5, r0	@ pstMem, pstMem
	mov	r0, r1	@, pstZmeDrvPara
	mov	r1, r2	@, pstZmeRtlPara
	add	r5, r5, #12	@ D.24688, pstMem,
	bl	ALG_VZmeComnSet	@
	ldr	r0, [r4, #88]	@ <variable>.u32ZmeRatioHL, <variable>.u32ZmeRatioHL
	mov	r1, r0, lsr #8	@, <variable>.u32ZmeRatioHL,
	mov	r0, r5	@, D.24688
	bl	GetHLfirCoef	@
	ldr	r1, [r4, #96]	@ <variable>.u32ZmeRatioHC, <variable>.u32ZmeRatioHC
	mov	r1, r1, lsr #8	@, <variable>.u32ZmeRatioHC,
	str	r0, [r4, #116]	@, <variable>.u32ZmeCoefAddrHL
	mov	r0, r5	@, D.24688
	bl	GetHCfirCoef	@
	ldr	r1, [r4, #92]	@, <variable>.u32ZmeRatioVL
	str	r0, [r4, #120]	@, <variable>.u32ZmeCoefAddrHC
	mov	r0, r5	@, D.24688
	bl	GetVLFilterCoef	@
	ldr	r1, [r4, #100]	@, <variable>.u32ZmeRatioVC
	str	r0, [r4, #124]	@, <variable>.u32ZmeCoefAddrVL
	mov	r0, r5	@, D.24688
	bl	GetVCfirCoef	@
	str	r0, [r4, #128]	@, <variable>.u32ZmeCoefAddrVC
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	ALG_VZmeVdpHQSet, .-ALG_VZmeVdpHQSet
	.align	2
	.global	ALG_VZmeVdpSQSetSptAddr
	.type	ALG_VZmeVdpSQSetSptAddr, %function
ALG_VZmeVdpSQSetSptAddr:
	.fnstart
.LFB683:
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
	mov	r4, r2	@ pstZmeRtlPara, pstZmeRtlPara
	mov	r6, r0	@ pstMem, pstMem
	mov	r0, r1	@, pstZmeDrvPara
	mov	r1, r2	@, pstZmeRtlPara
	add	r5, r6, #12	@ D.24724, pstMem,
	bl	ALG_VZmeComnSet	@
	ldr	r0, [r4, #88]	@ <variable>.u32ZmeRatioHL, <variable>.u32ZmeRatioHL
	mov	r1, r0, lsr #8	@, <variable>.u32ZmeRatioHL,
	mov	r0, r5	@, D.24724
	bl	GetHLfirCoef	@
	ldr	r1, [r4, #96]	@ <variable>.u32ZmeRatioHC, <variable>.u32ZmeRatioHC
	mov	r1, r1, lsr #8	@, <variable>.u32ZmeRatioHC,
	str	r0, [r4, #116]	@, <variable>.u32ZmeCoefAddrHL
	mov	r0, r5	@, D.24724
	bl	GetHCfirCoef	@
	ldr	r1, [r4, #92]	@, <variable>.u32ZmeRatioVL
	str	r0, [r4, #120]	@, <variable>.u32ZmeCoefAddrHC
	mov	r0, #16777216	@,
	bl	__aeabi_uidiv	@
	cmp	r0, #4096	@ tmp148,
	ldrhi	r3, [r6, #208]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_1
	bhi	.L144	@,
	ldreq	r3, [r6, #212]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_E1
	beq	.L144	@,
	cmp	r0, #3072	@ tmp148,
	ldrcs	r3, [r6, #216]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_075
	bcs	.L144	@,
	cmp	r0, #2048	@ tmp148,
	ldrcs	r3, [r6, #220]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_05
	bcs	.L144	@,
	movw	r3, #1364	@ tmp151,
	cmp	r0, r3	@ tmp148, tmp151
	ldrhi	r3, [r6, #224]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_033
	bhi	.L144	@,
	cmp	r0, #1024	@ tmp148,
	ldrcs	r3, [r6, #228]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_025
	ldrcc	r3, [r6, #232]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_0
.L144:
	str	r3, [r4, #124]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVL
	mov	r0, r5	@, D.24724
	ldr	r1, [r4, #100]	@, <variable>.u32ZmeRatioVC
	bl	GetVCfirCoef	@
	str	r0, [r4, #128]	@, <variable>.u32ZmeCoefAddrVC
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	ALG_VZmeVdpSQSetSptAddr, .-ALG_VZmeVdpSQSetSptAddr
	.align	2
	.global	ALG_VZmeVdpHQSetSptAddr
	.type	ALG_VZmeVdpHQSetSptAddr, %function
ALG_VZmeVdpHQSetSptAddr:
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
	mov	r4, r2	@ pstZmeRtlPara, pstZmeRtlPara
	mov	r5, r0	@ pstMem, pstMem
	mov	r0, r1	@, pstZmeDrvPara
	mov	r1, r2	@, pstZmeRtlPara
	add	r6, r5, #12	@ D.24740, pstMem,
	bl	ALG_VZmeComnSet	@
	ldr	r0, [r4, #88]	@ <variable>.u32ZmeRatioHL, <variable>.u32ZmeRatioHL
	mov	r1, r0, lsr #8	@, <variable>.u32ZmeRatioHL,
	mov	r0, r6	@, D.24740
	bl	GetHLfirCoef	@
	ldr	r1, [r4, #96]	@ <variable>.u32ZmeRatioHC, <variable>.u32ZmeRatioHC
	mov	r1, r1, lsr #8	@, <variable>.u32ZmeRatioHC,
	str	r0, [r4, #116]	@, <variable>.u32ZmeCoefAddrHL
	mov	r0, #16777216	@,
	bl	__aeabi_uidiv	@
	cmp	r0, #4096	@ tmp149,
	ldrhi	r3, [r5, #236]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_1
	bhi	.L153	@,
	ldreq	r3, [r5, #240]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_E1
	beq	.L153	@,
	cmp	r0, #3072	@ tmp149,
	ldrcs	r3, [r5, #244]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_075
	bcs	.L153	@,
	cmp	r0, #2048	@ tmp149,
	ldrcs	r3, [r5, #248]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_05
	bcs	.L153	@,
	movw	r3, #1364	@ tmp152,
	cmp	r0, r3	@ tmp149, tmp152
	ldrhi	r3, [r5, #252]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_033
	bls	.L167	@,
.L153:
	str	r3, [r4, #120]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHC
	mov	r0, r6	@, D.24740
	ldr	r1, [r4, #92]	@, <variable>.u32ZmeRatioVL
	bl	GetVLFilterCoef	@
	ldr	r1, [r4, #100]	@, <variable>.u32ZmeRatioVC
	str	r0, [r4, #124]	@, <variable>.u32ZmeCoefAddrVL
	mov	r0, #16777216	@,
	bl	__aeabi_uidiv	@
	cmp	r0, #4096	@ tmp157,
	ldrhi	r3, [r5, #264]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_1
	bhi	.L160	@,
	ldreq	r3, [r5, #268]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_E1
	beq	.L160	@,
	cmp	r0, #3072	@ tmp157,
	ldrcs	r3, [r5, #272]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_075
	bcs	.L160	@,
	cmp	r0, #2048	@ tmp157,
	ldrcs	r3, [r5, #276]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_05
	bcs	.L160	@,
	movw	r3, #1364	@ tmp160,
	cmp	r0, r3	@ tmp157, tmp160
	ldrhi	r3, [r5, #280]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_033
	bhi	.L160	@,
	cmp	r0, #1024	@ tmp157,
	ldrcs	r3, [r5, #284]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_025
	ldrcc	r3, [r5, #288]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_0
.L160:
	str	r3, [r4, #128]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVC
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L167:
	cmp	r0, #1024	@ tmp149,
	ldrcs	r3, [r5, #256]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_025
	ldrcc	r3, [r5, #260]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_0
	b	.L153	@
	.fnend
	.size	ALG_VZmeVdpHQSetSptAddr, .-ALG_VZmeVdpHQSetSptAddr
	.align	2
	.global	ALG_VZmeVpssHQSetSptAddr
	.type	ALG_VZmeVpssHQSetSptAddr, %function
ALG_VZmeVpssHQSetSptAddr:
	.fnstart
.LFB685:
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
	mov	r4, r2	@ pstZmeRtlPara, pstZmeRtlPara
	mov	r5, r0	@ pstMem, pstMem
	mov	r0, r1	@, pstZmeDrvPara
	mov	r1, r2	@, pstZmeRtlPara
	add	r5, r5, #12	@ D.24756, pstMem,
	bl	ALG_VZmeVpssComnSet	@
	ldr	r0, [r4, #88]	@ <variable>.u32ZmeRatioHL, <variable>.u32ZmeRatioHL
	mov	r1, r0, lsr #8	@, <variable>.u32ZmeRatioHL,
	mov	r0, r5	@, D.24756
	bl	GetHLfirCoef	@
	ldr	r1, [r4, #96]	@ <variable>.u32ZmeRatioHC, <variable>.u32ZmeRatioHC
	mov	r1, r1, lsr #8	@, <variable>.u32ZmeRatioHC,
	str	r0, [r4, #116]	@, <variable>.u32ZmeCoefAddrHL
	mov	r0, r5	@, D.24756
	bl	GetHCfirCoef	@
	ldr	r1, [r4, #92]	@, <variable>.u32ZmeRatioVL
	str	r0, [r4, #120]	@, <variable>.u32ZmeCoefAddrHC
	mov	r0, r5	@, D.24756
	bl	GetVLFilterCoef	@
	ldr	r1, [r4, #100]	@, <variable>.u32ZmeRatioVC
	str	r0, [r4, #124]	@, <variable>.u32ZmeCoefAddrVL
	mov	r0, r5	@, D.24756
	bl	GetVCfirCoef	@
	str	r0, [r4, #128]	@, <variable>.u32ZmeCoefAddrVC
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	ALG_VZmeVpssHQSetSptAddr, .-ALG_VZmeVpssHQSetSptAddr
	.align	2
	.global	ALG_VZmeVpssSetSptAddr
	.type	ALG_VZmeVpssSetSptAddr, %function
ALG_VZmeVpssSetSptAddr:
	.fnstart
.LFB686:
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
	mov	r4, r2	@ pstZmeRtlPara, pstZmeRtlPara
	mov	r5, r0	@ pstMem, pstMem
	mov	r0, r1	@, pstZmeDrvPara
	mov	r1, r2	@, pstZmeRtlPara
	add	r6, r5, #12	@ D.24772, pstMem,
	bl	ALG_VZmeVpssComnSet	@
	ldr	r0, [r4, #88]	@ <variable>.u32ZmeRatioHL, <variable>.u32ZmeRatioHL
	mov	r1, r0, lsr #8	@, <variable>.u32ZmeRatioHL,
	mov	r0, r6	@, D.24772
	bl	GetHLfirCoef	@
	ldr	r1, [r4, #96]	@ <variable>.u32ZmeRatioHC, <variable>.u32ZmeRatioHC
	mov	r1, r1, lsr #8	@, <variable>.u32ZmeRatioHC,
	str	r0, [r4, #116]	@, <variable>.u32ZmeCoefAddrHL
	mov	r0, #16777216	@,
	bl	__aeabi_uidiv	@
	cmp	r0, #4096	@ tmp149,
	ldrhi	r3, [r5, #236]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_1
	bhi	.L172	@,
	ldreq	r3, [r5, #240]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_E1
	beq	.L172	@,
	cmp	r0, #3072	@ tmp149,
	ldrcs	r3, [r5, #244]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_075
	bcs	.L172	@,
	cmp	r0, #2048	@ tmp149,
	ldrcs	r3, [r5, #248]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_05
	bcs	.L172	@,
	movw	r3, #1364	@ tmp152,
	cmp	r0, r3	@ tmp149, tmp152
	ldrhi	r3, [r5, #252]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_033
	bls	.L186	@,
.L172:
	str	r3, [r4, #120]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHC
	mov	r0, r6	@, D.24772
	ldr	r1, [r4, #92]	@, <variable>.u32ZmeRatioVL
	bl	GetVLFilterCoef	@
	ldr	r1, [r4, #100]	@, <variable>.u32ZmeRatioVC
	str	r0, [r4, #124]	@, <variable>.u32ZmeCoefAddrVL
	mov	r0, #16777216	@,
	bl	__aeabi_uidiv	@
	cmp	r0, #4096	@ tmp157,
	ldrhi	r3, [r5, #264]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_1
	bhi	.L179	@,
	ldreq	r3, [r5, #268]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_E1
	beq	.L179	@,
	cmp	r0, #3072	@ tmp157,
	ldrcs	r3, [r5, #272]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_075
	bcs	.L179	@,
	cmp	r0, #2048	@ tmp157,
	ldrcs	r3, [r5, #276]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_05
	bcs	.L179	@,
	movw	r3, #1364	@ tmp160,
	cmp	r0, r3	@ tmp157, tmp160
	ldrhi	r3, [r5, #280]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_033
	bhi	.L179	@,
	cmp	r0, #1024	@ tmp157,
	ldrcs	r3, [r5, #284]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_025
	ldrcc	r3, [r5, #288]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_0
.L179:
	str	r3, [r4, #128]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVC
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
.L186:
	cmp	r0, #1024	@ tmp149,
	ldrcs	r3, [r5, #256]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_025
	ldrcc	r3, [r5, #260]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_0
	b	.L172	@
	.fnend
	.size	ALG_VZmeVpssSetSptAddr, .-ALG_VZmeVpssSetSptAddr
	.align	2
	.global	ALG_VZmeSRSetAddr
	.type	ALG_VZmeSRSetAddr, %function
ALG_VZmeSRSetAddr:
	.fnstart
.LFB687:
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
	mov	r0, r1	@, pstZmeDrvPara
	mov	r1, r2	@, pstZmeRtlPara
	mov	r4, r2	@ pstZmeRtlPara, pstZmeRtlPara
	bl	ALG_VZmeComnSet	@
	add	r0, r4, #132	@, pstZmeRtlPara,
	bl	ALG_VZmeVdpSRCoef	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
	.fnend
	.size	ALG_VZmeSRSetAddr, .-ALG_VZmeSRSetAddr
	.align	2
	.global	ALG_VZmeVdpSQSet
	.type	ALG_VZmeVdpSQSet, %function
ALG_VZmeVdpSQSet:
	.fnstart
.LFB682:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #24
	sub	sp, sp, #24	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	sub	r5, fp, #40	@ tmp166,,
	mov	r4, r2	@ pstZmeRtlPara, pstZmeRtlPara
	mov	r7, r1	@ pstZmeDrvPara, pstZmeDrvPara
	mov	r6, r0	@ pstMem, pstMem
	mov	r1, #12	@,
	mov	r0, r5	@, tmp166
	bl	__memzero	@
	mov	r0, r7	@, pstZmeDrvPara
	mov	r1, r4	@, pstZmeRtlPara
	bl	ALG_VZmeComnSet	@
	ldr	r1, [r4, #88]	@ <variable>.u32ZmeRatioHL, <variable>.u32ZmeRatioHL
	mov	r0, #16777216	@,
	mov	r1, r1, lsr #8	@, <variable>.u32ZmeRatioHL,
	bl	__aeabi_uidiv	@
	cmp	r0, #4096	@ tmp145,
	ldrhi	r1, [r6, #124]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_1
	bhi	.L191	@,
	ldreq	r1, [r6, #128]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_E1
	beq	.L191	@,
	cmp	r0, #3072	@ tmp145,
	ldrcs	r1, [r6, #132]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_075
	bcs	.L191	@,
	cmp	r0, #2048	@ tmp145,
	ldrcs	r1, [r6, #136]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_05
	bcs	.L191	@,
	movw	r3, #1364	@ tmp148,
	cmp	r0, r3	@ tmp145, tmp148
	ldrhi	r1, [r6, #140]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_033
	bls	.L212	@,
.L191:
	ldr	r2, [r4, #92]	@ <variable>.u32ZmeRatioVL, <variable>.u32ZmeRatioVL
	mov	r0, #4	@ tmp151,
	str	r0, [fp, #-36]	@ tmp151, stPickCoef.u32TapL
	sub	ip, fp, #52	@ tmp152,,
	str	r1, [r4, #116]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrHL
	str	r2, [fp, #-40]	@ <variable>.u32ZmeRatioVL, stPickCoef.u32Ratio
	ldmia	r5, {r0, r1, r2}	@ tmp166,,,
	stmia	ip, {r0, r1, r2}	@ tmp152,,,
	mov	r0, #16777216	@,
	ldr	r1, [fp, #-52]	@, stPickCoef.u32Ratio
	bl	__aeabi_uidiv	@
	ldr	r3, [fp, #-48]	@ stPickCoef.u32TapL, stPickCoef.u32TapL
	cmp	r3, #6	@ stPickCoef.u32TapL,
	beq	.L213	@,
	cmp	r0, #4096	@ tmp156,
	ldrhi	r3, [r6, #180]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_1
	bhi	.L199	@,
	ldreq	r3, [r6, #184]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_E1
	beq	.L199	@,
	cmp	r0, #3072	@ tmp156,
	ldrcs	r3, [r6, #188]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_075
	bcs	.L199	@,
	cmp	r0, #2048	@ tmp156,
	ldrcs	r3, [r6, #192]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_05
	bcs	.L199	@,
	movw	r3, #1364	@ tmp164,
	cmp	r0, r3	@ tmp156, tmp164
	ldrhi	r3, [r6, #196]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_033
	bhi	.L199	@,
	cmp	r0, #1024	@ tmp156,
	ldrcs	r3, [r6, #200]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_025
	ldrcc	r3, [r6, #204]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_0
.L199:
	str	r3, [r4, #124]	@ u32CoefAddr, <variable>.u32ZmeCoefAddrVL
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L213:
	cmp	r0, #4096	@ tmp156,
	ldrhi	r3, [r6, #152]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_1
	bhi	.L199	@,
	ldreq	r3, [r6, #156]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_E1
	beq	.L199	@,
	cmp	r0, #3072	@ tmp156,
	ldrcs	r3, [r6, #160]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_075
	bcs	.L199	@,
	cmp	r0, #2048	@ tmp156,
	ldrcs	r3, [r6, #164]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_05
	bcs	.L199	@,
	movw	r3, #1364	@ tmp160,
	cmp	r0, r3	@ tmp156, tmp160
	ldrhi	r3, [r6, #168]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_033
	bhi	.L199	@,
	cmp	r0, #1024	@ tmp156,
	ldrcs	r3, [r6, #172]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_025
	ldrcc	r3, [r6, #176]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_0
	b	.L199	@
.L212:
	cmp	r0, #1024	@ tmp145,
	ldrcs	r1, [r6, #144]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_025
	ldrcc	r1, [r6, #148]	@ u32CoefAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_0
	b	.L191	@
	.fnend
	.size	ALG_VZmeVdpSQSet, .-ALG_VZmeVdpSQSet
	.align	2
	.type	VZmeLoadVdpCoefH, %function
VZmeLoadVdpCoefH:
	.fnstart
.LFB661:
	@ args = 0, pretend = 0, frame = 400
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #400
	sub	sp, sp, #400	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	rsb	r4, r0, r0, asl #3	@, tmp141, enCoefRatio, enCoefRatio,
	add	r0, r4, r1	@ tmp142, tmp141, enCoefType
	movw	r5, #:lower16:.LANCHOR0	@ tmp138,
	movt	r5, #:upper16:.LANCHOR0	@ tmp138,
	sub	r4, fp, #420	@ tmp148,,
	add	ip, r5, r0, asl #2	@, tmp145, tmp138, tmp142,
	mov	r1, r2	@, enZmeTap
	mov	r5, r3	@ pu8Addr, pu8Addr
	mov	r2, r4	@, tmp148
	ldr	r0, [ip, #88]	@, g_pVZmeCoef
	bl	VZmeTransCoefAlign	@
	mov	r0, r5	@, pu8Addr
	add	r1, r4, #4	@, tmp148,
	ldr	r2, [fp, #-420]	@, stArray.u32Size
	bl	memcpy	@
	mov	r0, #0	@,
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
	.fnend
	.size	VZmeLoadVdpCoefH, .-VZmeLoadVdpCoefH
	.align	2
	.type	VZmeLoadVdpCoefV, %function
VZmeLoadVdpCoefV:
	.fnstart
.LFB662:
	@ args = 0, pretend = 0, frame = 400
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #400
	sub	sp, sp, #400	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	rsb	r4, r0, r0, asl #3	@, tmp141, enCoefRatio, enCoefRatio,
	add	r0, r4, r1	@ tmp142, tmp141, enCoefType
	movw	r5, #:lower16:.LANCHOR0	@ tmp138,
	movt	r5, #:upper16:.LANCHOR0	@ tmp138,
	sub	r4, fp, #420	@ tmp148,,
	add	ip, r5, r0, asl #2	@, tmp145, tmp138, tmp142,
	mov	r1, r2	@, enZmeTap
	mov	r5, r3	@ pu8Addr, pu8Addr
	mov	r2, r4	@, tmp148
	ldr	r0, [ip, #88]	@, g_pVZmeCoef
	bl	VZmeTransCoefAlign	@
	mov	r0, r5	@, pu8Addr
	add	r1, r4, #4	@, tmp148,
	ldr	r2, [fp, #-420]	@, stArray.u32Size
	bl	memcpy	@
	mov	r0, #0	@,
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
	.fnend
	.size	VZmeLoadVdpCoefV, .-VZmeLoadVdpCoefV
	.align	2
	.global	ALG_VZmeVdpComnInit
	.type	ALG_VZmeVdpComnInit, %function
ALG_VZmeVdpComnInit:
	.fnstart
.LFB665:
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
	mov	r4, r0	@ pstVZmeVdpCoefMem, pstVZmeVdpCoefMem
	ldr	r8, [r4, #0]	@ pu8CurAddr, <variable>.stMBuf.u32StartVirAddr
	mov	r0, #0	@,
	ldr	r5, [r4, #4]	@ u32PhyAddr, <variable>.stMBuf.u32StartPhyAddr
	mov	r1, r0	@,
	mov	r2, r0	@,
	add	sl, r8, #4080	@ pu8CurAddr.1634, pu8CurAddr,
	mov	r3, r8	@, pu8CurAddr
	add	r7, r5, #192	@ u32PhyAddr.1571, u32PhyAddr,
	bl	VZmeLoadVdpCoefH	@
	str	r5, [r4, #12]	@ u32PhyAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8_1
	str	r5, [r4, #124]	@ u32PhyAddr, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_1
	add	r3, r8, #192	@, pu8CurAddr,
	mov	r1, #3	@,
	mov	r2, #2	@,
	mov	r0, #0	@,
	add	r6, r5, #288	@ u32PhyAddr.1573, u32PhyAddr,
	bl	VZmeLoadVdpCoefH	@
	mov	r1, #0	@,
	str	r7, [r4, #40]	@ u32PhyAddr.1571, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC4_1
	mov	r2, r1	@,
	add	r3, r8, #288	@, pu8CurAddr,
	mov	r0, #1	@,
	bl	VZmeLoadVdpCoefH	@
	str	r6, [r4, #128]	@ u32PhyAddr.1573, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_E1
	str	r6, [r4, #16]	@ u32PhyAddr.1573, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8_E1
	add	r3, r8, #480	@, pu8CurAddr,
	mov	r1, #3	@,
	mov	r2, #2	@,
	mov	r0, #1	@,
	add	r7, r5, #480	@ u32PhyAddr.1575, u32PhyAddr,
	bl	VZmeLoadVdpCoefH	@
	mov	r1, #0	@,
	str	r7, [r4, #44]	@ u32PhyAddr.1575, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC4_E1
	mov	r2, r1	@,
	add	r3, r8, #576	@, pu8CurAddr,
	mov	r0, #2	@,
	bl	VZmeLoadVdpCoefH	@
	mov	r0, #2	@,
	add	r1, r5, #576	@ u32PhyAddr.1577, u32PhyAddr,
	add	r3, r8, #768	@, pu8CurAddr,
	str	r1, [r4, #132]	@ u32PhyAddr.1577, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_075
	mov	r2, r0	@,
	str	r1, [r4, #20]	@ u32PhyAddr.1577, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8_075
	mov	r1, #3	@,
	bl	VZmeLoadVdpCoefH	@
	mov	r1, #0	@,
	mov	r2, r1	@,
	add	r3, r8, #864	@, pu8CurAddr,
	add	r0, r5, #768	@ u32PhyAddr.1579, u32PhyAddr,
	str	r0, [r4, #48]	@ u32PhyAddr.1579, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC4_075
	mov	r0, #3	@,
	add	r6, r5, #864	@ u32PhyAddr.1581, u32PhyAddr,
	bl	VZmeLoadVdpCoefH	@
	mov	r0, #3	@,
	str	r6, [r4, #136]	@ u32PhyAddr.1581, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_05
	add	r3, r8, #1056	@, pu8CurAddr,
	str	r6, [r4, #24]	@ u32PhyAddr.1581, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8_05
	mov	r1, r0	@,
	mov	r2, #2	@,
	add	r7, r5, #1056	@ u32PhyAddr.1583, u32PhyAddr,
	bl	VZmeLoadVdpCoefH	@
	mov	r1, #0	@,
	str	r7, [r4, #52]	@ u32PhyAddr.1583, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC4_05
	mov	r2, r1	@,
	add	r3, r8, #1152	@, pu8CurAddr,
	mov	r0, #4	@,
	bl	VZmeLoadVdpCoefH	@
	add	r3, r5, #1152	@ u32PhyAddr.1585, u32PhyAddr,
	mov	r1, #3	@,
	str	r3, [r4, #140]	@ u32PhyAddr.1585, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_033
	str	r3, [r4, #28]	@ u32PhyAddr.1585, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8_033
	mov	r2, #2	@,
	add	r3, r8, #1344	@, pu8CurAddr,
	mov	r0, #4	@,
	bl	VZmeLoadVdpCoefH	@
	mov	r1, #0	@,
	add	ip, r5, #1344	@ u32PhyAddr.1587, u32PhyAddr,
	mov	r2, r1	@,
	str	ip, [r4, #56]	@ u32PhyAddr.1587, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC4_033
	add	r3, r8, #1440	@, pu8CurAddr,
	mov	r0, #5	@,
	add	r6, r5, #1440	@ u32PhyAddr.1589, u32PhyAddr,
	bl	VZmeLoadVdpCoefH	@
	str	r6, [r4, #144]	@ u32PhyAddr.1589, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_025
	str	r6, [r4, #32]	@ u32PhyAddr.1589, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8_025
	add	r3, r8, #1632	@, pu8CurAddr,
	mov	r1, #3	@,
	mov	r2, #2	@,
	mov	r0, #5	@,
	add	r7, r5, #1632	@ u32PhyAddr.1591, u32PhyAddr,
	bl	VZmeLoadVdpCoefH	@
	mov	r1, #0	@,
	str	r7, [r4, #60]	@ u32PhyAddr.1591, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC4_025
	mov	r2, r1	@,
	add	r3, r8, #1728	@, pu8CurAddr,
	mov	r0, #6	@,
	bl	VZmeLoadVdpCoefH	@
	add	r2, r5, #1728	@ u32PhyAddr.1593, u32PhyAddr,
	add	r3, r8, #1920	@, pu8CurAddr,
	str	r2, [r4, #148]	@ u32PhyAddr.1593, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8C4_0
	str	r2, [r4, #36]	@ u32PhyAddr.1593, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHL8_0
	mov	r1, #3	@,
	mov	r2, #2	@,
	mov	r0, #6	@,
	bl	VZmeLoadVdpCoefH	@
	mov	r1, #1	@,
	mov	r2, r1	@,
	add	r3, r8, #2016	@, pu8CurAddr,
	add	r0, r5, #1920	@ u32PhyAddr.1595, u32PhyAddr,
	str	r0, [r4, #64]	@ u32PhyAddr.1595, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC4_0
	mov	r0, #0	@,
	add	r6, r5, #2016	@ u32PhyAddr.1597, u32PhyAddr,
	bl	VZmeLoadVdpCoefV	@
	str	r6, [r4, #152]	@ u32PhyAddr.1597, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_1
	str	r6, [r4, #68]	@ u32PhyAddr.1597, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6_1
	add	r3, r8, #2160	@, pu8CurAddr,
	mov	r1, #4	@,
	mov	r2, #2	@,
	mov	r0, #0	@,
	add	r7, r5, #2160	@ u32PhyAddr.1599, u32PhyAddr,
	bl	VZmeLoadVdpCoefV	@
	mov	r0, #1	@,
	str	r7, [r4, #96]	@ u32PhyAddr.1599, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_1
	add	r3, r8, #2256	@, pu8CurAddr,
	mov	r1, r0	@,
	mov	r2, r0	@,
	bl	VZmeLoadVdpCoefV	@
	add	r3, r5, #2256	@ u32PhyAddr.1601, u32PhyAddr,
	mov	r1, #4	@,
	str	r3, [r4, #156]	@ u32PhyAddr.1601, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_E1
	str	r3, [r4, #72]	@ u32PhyAddr.1601, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6_E1
	mov	r2, #2	@,
	add	r3, r8, #2400	@, pu8CurAddr,
	mov	r0, #1	@,
	bl	VZmeLoadVdpCoefV	@
	mov	r1, #1	@,
	add	ip, r5, #2400	@ u32PhyAddr.1603, u32PhyAddr,
	mov	r2, r1	@,
	str	ip, [r4, #100]	@ u32PhyAddr.1603, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_E1
	add	r3, r8, #2496	@, pu8CurAddr,
	mov	r0, #2	@,
	add	r6, r5, #2496	@ u32PhyAddr.1605, u32PhyAddr,
	bl	VZmeLoadVdpCoefV	@
	mov	r0, #2	@,
	str	r6, [r4, #160]	@ u32PhyAddr.1605, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_075
	add	r3, r8, #2640	@, pu8CurAddr,
	str	r6, [r4, #76]	@ u32PhyAddr.1605, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6_075
	mov	r1, #4	@,
	mov	r2, r0	@,
	add	r7, r5, #2640	@ u32PhyAddr.1607, u32PhyAddr,
	bl	VZmeLoadVdpCoefV	@
	mov	r1, #1	@,
	str	r7, [r4, #104]	@ u32PhyAddr.1607, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_075
	mov	r2, r1	@,
	add	r3, r8, #2736	@, pu8CurAddr,
	mov	r0, #3	@,
	bl	VZmeLoadVdpCoefV	@
	add	r2, r5, #2736	@ u32PhyAddr.1609, u32PhyAddr,
	add	r3, r8, #2880	@, pu8CurAddr,
	str	r2, [r4, #164]	@ u32PhyAddr.1609, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_05
	str	r2, [r4, #80]	@ u32PhyAddr.1609, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6_05
	mov	r1, #4	@,
	mov	r2, #2	@,
	mov	r0, #3	@,
	bl	VZmeLoadVdpCoefV	@
	mov	r1, #1	@,
	mov	r2, r1	@,
	add	r3, r8, #2976	@, pu8CurAddr,
	add	r0, r5, #2880	@ u32PhyAddr.1611, u32PhyAddr,
	str	r0, [r4, #108]	@ u32PhyAddr.1611, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_05
	mov	r0, #4	@,
	add	r6, r5, #2976	@ u32PhyAddr.1613, u32PhyAddr,
	bl	VZmeLoadVdpCoefV	@
	mov	r0, #4	@,
	str	r6, [r4, #168]	@ u32PhyAddr.1613, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_033
	add	r3, r8, #3120	@, pu8CurAddr,
	str	r6, [r4, #84]	@ u32PhyAddr.1613, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6_033
	mov	r1, r0	@,
	mov	r2, #2	@,
	add	r7, r5, #3120	@ u32PhyAddr.1615, u32PhyAddr,
	bl	VZmeLoadVdpCoefV	@
	mov	r1, #1	@,
	str	r7, [r4, #112]	@ u32PhyAddr.1615, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_033
	mov	r2, r1	@,
	add	r3, r8, #3216	@, pu8CurAddr,
	mov	r0, #5	@,
	bl	VZmeLoadVdpCoefV	@
	mov	r0, #4	@,
	add	r1, r5, #3216	@ u32PhyAddr.1617, u32PhyAddr,
	add	r3, r8, #3360	@, pu8CurAddr,
	str	r1, [r4, #172]	@ u32PhyAddr.1617, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_025
	mov	r2, #2	@,
	str	r1, [r4, #88]	@ u32PhyAddr.1617, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6_025
	mov	r1, r0	@,
	bl	VZmeLoadVdpCoefV	@
	mov	r1, #1	@,
	add	ip, r5, #3360	@ u32PhyAddr.1619, u32PhyAddr,
	mov	r2, r1	@,
	str	ip, [r4, #116]	@ u32PhyAddr.1619, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_025
	add	r3, r8, #3456	@, pu8CurAddr,
	mov	r0, #6	@,
	add	r6, r5, #3456	@ u32PhyAddr.1621, u32PhyAddr,
	bl	VZmeLoadVdpCoefV	@
	str	r6, [r4, #176]	@ u32PhyAddr.1621, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6C4_0
	str	r6, [r4, #92]	@ u32PhyAddr.1621, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL6_0
	add	r3, r8, #3600	@, pu8CurAddr,
	mov	r1, #4	@,
	mov	r2, #2	@,
	mov	r0, #6	@,
	add	r7, r5, #3600	@ u32PhyAddr.1623, u32PhyAddr,
	bl	VZmeLoadVdpCoefV	@
	mov	r1, #2	@,
	str	r7, [r4, #120]	@ u32PhyAddr.1623, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_0
	mov	r2, r1	@,
	add	r3, r8, #3696	@, pu8CurAddr,
	mov	r0, #0	@,
	bl	VZmeLoadVdpCoefV	@
	add	r3, r5, #3696	@ u32PhyAddr.1625, u32PhyAddr,
	mov	r1, #3	@,
	str	r3, [r4, #180]	@ u32PhyAddr.1625, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_1
	str	r3, [r4, #208]	@ u32PhyAddr.1625, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_1
	mov	r2, #2	@,
	add	r3, r8, #3792	@, pu8CurAddr,
	mov	r0, #0	@,
	bl	VZmeLoadVdpCoefH	@
	mov	r1, #2	@,
	mov	r2, r1	@,
	add	r3, r8, #3888	@, pu8CurAddr,
	add	r0, r5, #3792	@ u32PhyAddr.1627, u32PhyAddr,
	str	r0, [r4, #96]	@ u32PhyAddr.1627, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_1
	mov	r0, #1	@,
	add	r6, r5, #3888	@ u32PhyAddr.1629, u32PhyAddr,
	bl	VZmeLoadVdpCoefV	@
	str	r6, [r4, #184]	@ u32PhyAddr.1629, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_E1
	str	r6, [r4, #212]	@ u32PhyAddr.1629, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_E1
	add	r3, r8, #3984	@, pu8CurAddr,
	mov	r1, #3	@,
	mov	r2, #2	@,
	mov	r0, #1	@,
	add	r7, r5, #3984	@ u32PhyAddr.1631, u32PhyAddr,
	bl	VZmeLoadVdpCoefH	@
	mov	r0, #2	@,
	str	r7, [r4, #100]	@ u32PhyAddr.1631, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_E1
	mov	r3, sl	@, pu8CurAddr.1634
	mov	r1, r0	@,
	mov	r2, r0	@,
	bl	VZmeLoadVdpCoefV	@
	mov	r0, #2	@,
	add	r7, r5, #4080	@ u32PhyAddr.1633, u32PhyAddr,
	add	r3, sl, #96	@, pu8CurAddr.1634,
	str	r7, [r4, #216]	@ u32PhyAddr.1633, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_075
	mov	r1, #3	@,
	str	r7, [r4, #188]	@ u32PhyAddr.1633, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_075
	mov	r2, r0	@,
	bl	VZmeLoadVdpCoefH	@
	mov	r1, #2	@,
	add	ip, r7, #96	@ u32PhyAddr.1635, u32PhyAddr.1633,
	mov	r2, r1	@,
	str	ip, [r4, #104]	@ u32PhyAddr.1635, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_075
	add	r3, sl, #192	@, pu8CurAddr.1634,
	mov	r0, #3	@,
	add	r6, r7, #192	@ u32PhyAddr.1637, u32PhyAddr.1633,
	bl	VZmeLoadVdpCoefV	@
	mov	r0, #3	@,
	str	r6, [r4, #192]	@ u32PhyAddr.1637, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_05
	add	r3, sl, #288	@, pu8CurAddr.1634,
	str	r6, [r4, #220]	@ u32PhyAddr.1637, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_05
	mov	r1, r0	@,
	mov	r2, #2	@,
	add	r6, r7, #288	@ u32PhyAddr.1639, u32PhyAddr.1633,
	bl	VZmeLoadVdpCoefH	@
	mov	r1, #2	@,
	str	r6, [r4, #108]	@ u32PhyAddr.1639, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_05
	mov	r2, r1	@,
	add	r3, sl, #384	@, pu8CurAddr.1634,
	mov	r0, #4	@,
	bl	VZmeLoadVdpCoefV	@
	add	r2, r7, #384	@ u32PhyAddr.1641, u32PhyAddr.1633,
	add	r3, sl, #480	@, pu8CurAddr.1634,
	str	r2, [r4, #196]	@ u32PhyAddr.1641, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_033
	str	r2, [r4, #224]	@ u32PhyAddr.1641, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_033
	mov	r1, #3	@,
	mov	r2, #2	@,
	mov	r0, #4	@,
	bl	VZmeLoadVdpCoefH	@
	mov	r1, #2	@,
	mov	r2, r1	@,
	add	r3, sl, #576	@, pu8CurAddr.1634,
	add	r0, r7, #480	@ u32PhyAddr.1643, u32PhyAddr.1633,
	str	r0, [r4, #112]	@ u32PhyAddr.1643, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_033
	mov	r0, #5	@,
	add	r6, r7, #576	@ u32PhyAddr.1645, u32PhyAddr.1633,
	bl	VZmeLoadVdpCoefV	@
	str	r6, [r4, #200]	@ u32PhyAddr.1645, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_025
	str	r6, [r4, #228]	@ u32PhyAddr.1645, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_025
	add	r3, sl, #672	@, pu8CurAddr.1634,
	mov	r1, #3	@,
	mov	r2, #2	@,
	mov	r0, #5	@,
	add	r6, r7, #672	@ u32PhyAddr.1647, u32PhyAddr.1633,
	bl	VZmeLoadVdpCoefH	@
	mov	r1, #2	@,
	str	r6, [r4, #116]	@ u32PhyAddr.1647, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_025
	mov	r2, r1	@,
	add	r3, sl, #768	@, pu8CurAddr.1634,
	mov	r0, #6	@,
	bl	VZmeLoadVdpCoefV	@
	add	r3, r7, #768	@ u32PhyAddr.1649, u32PhyAddr.1633,
	mov	r1, #3	@,
	str	r3, [r4, #204]	@ u32PhyAddr.1649, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4C4_0
	str	r3, [r4, #232]	@ u32PhyAddr.1649, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVL4_0
	mov	r2, #2	@,
	add	r3, sl, #864	@, pu8CurAddr.1634,
	mov	r0, #6	@,
	bl	VZmeLoadVdpCoefH	@
	mov	r0, #0	@,
	add	ip, r7, #864	@ u32PhyAddr.1651, u32PhyAddr.1633,
	add	r3, sl, #960	@, pu8CurAddr.1634,
	str	ip, [r4, #120]	@ u32PhyAddr.1651, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC4_0
	mov	r1, #5	@,
	mov	r2, r0	@,
	add	r6, r7, #960	@ u32PhyAddr.1653, u32PhyAddr.1633,
	bl	VZmeLoadVdpCoefH	@
	str	r6, [r4, #236]	@ u32PhyAddr.1653, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_1
	add	r3, sl, #1152	@, pu8CurAddr.1634,
	mov	r1, #5	@,
	mov	r2, #0	@,
	mov	r0, #1	@,
	bl	VZmeLoadVdpCoefH	@
	add	r0, r7, #1152	@ u32PhyAddr.1655, u32PhyAddr.1633,
	add	r3, sl, #1344	@, pu8CurAddr.1634,
	str	r0, [r4, #240]	@ u32PhyAddr.1655, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_E1
	mov	r1, #5	@,
	mov	r2, #0	@,
	mov	r0, #2	@,
	add	r6, r7, #1344	@ u32PhyAddr.1657, u32PhyAddr.1633,
	bl	VZmeLoadVdpCoefH	@
	str	r6, [r4, #244]	@ u32PhyAddr.1657, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_075
	add	r3, sl, #1536	@, pu8CurAddr.1634,
	mov	r1, #5	@,
	mov	r2, #0	@,
	mov	r0, #3	@,
	bl	VZmeLoadVdpCoefH	@
	add	r2, r7, #1536	@ u32PhyAddr.1659, u32PhyAddr.1633,
	add	r3, sl, #1728	@, pu8CurAddr.1634,
	str	r2, [r4, #248]	@ u32PhyAddr.1659, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_05
	mov	r1, #5	@,
	mov	r2, #0	@,
	mov	r0, #4	@,
	add	r6, r7, #1728	@ u32PhyAddr.1661, u32PhyAddr.1633,
	bl	VZmeLoadVdpCoefH	@
	mov	r0, #5	@,
	str	r6, [r4, #252]	@ u32PhyAddr.1661, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_033
	add	r3, sl, #1920	@, pu8CurAddr.1634,
	mov	r1, r0	@,
	mov	r2, #0	@,
	bl	VZmeLoadVdpCoefH	@
	add	r1, r7, #1920	@ u32PhyAddr.1663, u32PhyAddr.1633,
	add	r3, sl, #2112	@, pu8CurAddr.1634,
	str	r1, [r4, #256]	@ u32PhyAddr.1663, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_025
	mov	r2, #0	@,
	mov	r1, #5	@,
	mov	r0, #6	@,
	add	r6, r7, #2112	@ u32PhyAddr.1665, u32PhyAddr.1633,
	bl	VZmeLoadVdpCoefH	@
	str	r6, [r4, #260]	@ u32PhyAddr.1665, <variable>.stZmeCoefAddr.u32ZmeCoefAddrHC8_0
	add	r3, sl, #2304	@, pu8CurAddr.1634,
	mov	r1, #6	@,
	mov	r2, #1	@,
	mov	r0, #0	@,
	bl	VZmeLoadVdpCoefV	@
	mov	r0, #1	@,
	add	ip, r7, #2304	@ u32PhyAddr.1667, u32PhyAddr.1633,
	add	r3, r8, #6528	@, pu8CurAddr,
	str	ip, [r4, #264]	@ u32PhyAddr.1667, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_1
	mov	r1, #6	@,
	mov	r2, r0	@,
	add	r6, r5, #6528	@ u32PhyAddr.1669, u32PhyAddr,
	bl	VZmeLoadVdpCoefV	@
	str	r6, [r4, #268]	@ u32PhyAddr.1669, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_E1
	add	r3, sl, #2592	@, pu8CurAddr.1634,
	mov	r1, #6	@,
	mov	r2, #1	@,
	mov	r0, #2	@,
	bl	VZmeLoadVdpCoefV	@
	add	r3, r7, #2592	@ u32PhyAddr.1671, u32PhyAddr.1633,
	mov	r1, #6	@,
	str	r3, [r4, #272]	@ u32PhyAddr.1671, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_075
	mov	r2, #1	@,
	add	r3, sl, #2736	@, pu8CurAddr.1634,
	mov	r0, #3	@,
	add	r6, r7, #2736	@ u32PhyAddr.1673, u32PhyAddr.1633,
	bl	VZmeLoadVdpCoefV	@
	add	r3, sl, #2880	@, pu8CurAddr.1634,
	str	r6, [r4, #276]	@ u32PhyAddr.1673, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_05
	mov	r1, #6	@,
	mov	r2, #1	@,
	mov	r0, #4	@,
	bl	VZmeLoadVdpCoefV	@
	add	r3, r8, #7104	@, pu8CurAddr,
	add	r0, r7, #2880	@ u32PhyAddr.1675, u32PhyAddr.1633,
	mov	r1, #6	@,
	str	r0, [r4, #280]	@ u32PhyAddr.1675, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_033
	mov	r2, #1	@,
	mov	r0, #5	@,
	add	r5, r5, #7104	@ u32PhyAddr.1677, u32PhyAddr,
	bl	VZmeLoadVdpCoefV	@
	mov	r0, #6	@,
	str	r5, [r4, #284]	@ u32PhyAddr.1677, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_025
	add	r3, sl, #3168	@, pu8CurAddr.1634,
	mov	r1, r0	@,
	mov	r2, #1	@,
	bl	VZmeLoadVdpCoefV	@
	add	r7, r7, #3168	@ tmp246, u32PhyAddr.1633,
	mov	r0, #0	@,
	str	r7, [r4, #288]	@ tmp246, <variable>.stZmeCoefAddr.u32ZmeCoefAddrVC6_0
	ldmfd	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}	@
	.fnend
	.size	ALG_VZmeVdpComnInit, .-ALG_VZmeVdpComnInit
	.align	2
	.type	VZmeLoadVpssCoefHL, %function
VZmeLoadVpssCoefHL:
	.fnstart
.LFB655:
	@ args = 0, pretend = 0, frame = 400
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #404
	sub	sp, sp, #404	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r4, #:lower16:.LANCHOR1	@ tmp136,
	rsb	r3, r0, r0, asl #3	@, tmp139, enCoefRatio, enCoefRatio,
	sub	r5, fp, #436	@ tmp143,,
	movt	r4, #:upper16:.LANCHOR1	@ tmp136,
	mov	r6, r0	@ enCoefRatio, enCoefRatio
	add	r7, r5, #196	@ tmp147, tmp143,
	mov	r8, r1	@ pu32Addr, pu32Addr
	ldr	r0, [r4, r3, asl #2]	@, g_pVZmeVpssCoef
	mov	r2, r5	@, tmp143
	mov	r1, #0	@,
	add	r4, r4, r6, asl #4	@, tmp155, tmp136, enCoefRatio,
	bl	VZmeTransVpssCoefAlign	@
	mov	r1, r7	@, tmp147
	ldr	r2, [fp, #-436]	@, stArray.u32Size
	mov	r0, r8	@, pu32Addr
	bl	memcpy	@
	mov	r2, r5	@, tmp143
	mov	r1, #0	@,
	ldr	r0, [r4, #196]	@, g_pVDtiZmeCoef
	bl	VZmeTransVpssCoefAlign	@
	add	r0, r8, #256	@, pu32Addr,
	mov	r1, r7	@, tmp147
	ldr	r2, [fp, #-436]	@, stArray.u32Size
	bl	memcpy	@
	mov	r0, #0	@,
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	.fnend
	.size	VZmeLoadVpssCoefHL, .-VZmeLoadVpssCoefHL
	.align	2
	.type	VZmeLoadVpssCoefHC, %function
VZmeLoadVpssCoefHC:
	.fnstart
.LFB656:
	@ args = 0, pretend = 0, frame = 400
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #404
	sub	sp, sp, #404	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r6, r0	@ enCoefRatio, enCoefRatio
	rsb	r0, r0, r0, asl #3	@, tmp140, enCoefRatio, enCoefRatio,
	movw	r4, #:lower16:.LANCHOR1	@ tmp136,
	movt	r4, #:upper16:.LANCHOR1	@ tmp136,
	sub	r5, fp, #436	@ tmp145,,
	add	r3, r4, r0, asl #2	@, tmp142, tmp136, tmp140,
	add	r7, r5, #196	@ tmp149, tmp145,
	mov	r8, r1	@ pu32Addr, pu32Addr
	mov	r2, r5	@, tmp145
	ldr	r0, [r3, #12]	@, g_pVZmeVpssCoef
	mov	r1, #2	@,
	add	r4, r4, r6, asl #4	@, tmp158, tmp136, enCoefRatio,
	bl	VZmeTransVpssCoefAlign	@
	mov	r1, r7	@, tmp149
	ldr	r2, [fp, #-436]	@, stArray.u32Size
	mov	r0, r8	@, pu32Addr
	bl	memcpy	@
	mov	r2, r5	@, tmp145
	mov	r1, #2	@,
	ldr	r0, [r4, #204]	@, g_pVDtiZmeCoef
	bl	VZmeTransVpssCoefAlign	@
	add	r0, r8, #256	@, pu32Addr,
	mov	r1, r7	@, tmp149
	ldr	r2, [fp, #-436]	@, stArray.u32Size
	bl	memcpy	@
	mov	r0, #0	@,
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	.fnend
	.size	VZmeLoadVpssCoefHC, .-VZmeLoadVpssCoefHC
	.align	2
	.type	VZmeLoadVpssCoefVL, %function
VZmeLoadVpssCoefVL:
	.fnstart
.LFB657:
	@ args = 0, pretend = 0, frame = 400
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #404
	sub	sp, sp, #404	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r6, r0	@ enCoefRatio, enCoefRatio
	rsb	r0, r0, r0, asl #3	@, tmp139, enCoefRatio, enCoefRatio,
	sub	r5, fp, #436	@ tmp142,,
	add	r3, r0, #1	@ tmp140, tmp139,
	movw	r4, #:lower16:.LANCHOR1	@ tmp136,
	movt	r4, #:upper16:.LANCHOR1	@ tmp136,
	add	r7, r5, #196	@ tmp146, tmp142,
	mov	r8, r1	@ pu32Addr, pu32Addr
	mov	r2, r5	@, tmp142
	ldr	r0, [r4, r3, asl #2]	@, g_pVZmeVpssCoef
	mov	r1, #1	@,
	add	r4, r4, r6, asl #4	@, tmp155, tmp136, enCoefRatio,
	bl	VZmeTransVpssCoefAlign	@
	mov	r1, r7	@, tmp146
	ldr	r2, [fp, #-436]	@, stArray.u32Size
	mov	r0, r8	@, pu32Addr
	bl	memcpy	@
	mov	r2, r5	@, tmp142
	mov	r1, #3	@,
	ldr	r0, [r4, #200]	@, g_pVDtiZmeCoef
	bl	VZmeTransVpssCoefAlign	@
	add	r0, r8, #256	@, pu32Addr,
	mov	r1, r7	@, tmp146
	ldr	r2, [fp, #-436]	@, stArray.u32Size
	bl	memcpy	@
	mov	r0, #0	@,
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	.fnend
	.size	VZmeLoadVpssCoefVL, .-VZmeLoadVpssCoefVL
	.align	2
	.type	VZmeLoadVpssCoefVC, %function
VZmeLoadVpssCoefVC:
	.fnstart
.LFB658:
	@ args = 0, pretend = 0, frame = 400
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #404
	sub	sp, sp, #404	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r6, r0	@ enCoefRatio, enCoefRatio
	rsb	r0, r0, r0, asl #3	@, tmp140, enCoefRatio, enCoefRatio,
	movw	r4, #:lower16:.LANCHOR1	@ tmp136,
	movt	r4, #:upper16:.LANCHOR1	@ tmp136,
	sub	r5, fp, #436	@ tmp145,,
	add	r3, r4, r0, asl #2	@, tmp142, tmp136, tmp140,
	add	r7, r5, #196	@ tmp149, tmp145,
	mov	r8, r1	@ pu32Addr, pu32Addr
	mov	r2, r5	@, tmp145
	ldr	r0, [r3, #16]	@, g_pVZmeVpssCoef
	mov	r1, #2	@,
	add	r4, r4, r6, asl #4	@, tmp157, tmp136, enCoefRatio,
	bl	VZmeTransVpssCoefAlign	@
	mov	r1, r7	@, tmp149
	ldr	r2, [fp, #-436]	@, stArray.u32Size
	mov	r0, r8	@, pu32Addr
	bl	memcpy	@
	mov	r2, r5	@, tmp145
	mov	r1, #3	@,
	ldr	r0, [r4, #208]	@, g_pVDtiZmeCoef
	bl	VZmeTransVpssCoefAlign	@
	add	r0, r8, #256	@, pu32Addr,
	mov	r1, r7	@, tmp149
	ldr	r2, [fp, #-436]	@, stArray.u32Size
	bl	memcpy	@
	mov	r0, #0	@,
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	.fnend
	.size	VZmeLoadVpssCoefVC, .-VZmeLoadVpssCoefVC
	.align	2
	.global	VZmeLoadVpssCoefHV
	.type	VZmeLoadVpssCoefHV, %function
VZmeLoadVpssCoefHV:
	.fnstart
.LFB659:
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
	mov	r4, r0	@ pu32CurAddr, pu32CurAddr
	mov	r5, r2	@ pstAddrTmp, pstAddrTmp
	mov	r6, r1	@ u32PhyAddr, u32PhyAddr
	mov	r0, #0	@,
	mov	r1, r4	@, pu32CurAddr
	bl	VZmeLoadVpssCoefHL	@
	add	r1, r4, #464	@, pu32CurAddr,
	str	r6, [r5, #0]	@ u32PhyAddr, <variable>.u32ZmeCoefAddrHL8_1
	mov	r0, #1	@,
	bl	VZmeLoadVpssCoefHL	@
	add	r9, r6, #464	@ u32PhyAddr.1804, u32PhyAddr,
	add	r1, r4, #928	@, pu32CurAddr,
	str	r9, [r5, #4]	@ u32PhyAddr.1804, <variable>.u32ZmeCoefAddrHL8_E1
	mov	r0, #2	@,
	add	sl, r6, #1392	@ u32PhyAddr.1808, u32PhyAddr,
	bl	VZmeLoadVpssCoefHL	@
	add	r3, r6, #928	@ u32PhyAddr.1806, u32PhyAddr,
	add	r1, r4, #1392	@, pu32CurAddr,
	str	r3, [r5, #8]	@ u32PhyAddr.1806, <variable>.u32ZmeCoefAddrHL8_075
	mov	r0, #3	@,
	add	r8, r6, #2320	@ u32PhyAddr.1812, u32PhyAddr,
	bl	VZmeLoadVpssCoefHL	@
	add	r1, r4, #1856	@, pu32CurAddr,
	str	sl, [r5, #12]	@ u32PhyAddr.1808, <variable>.u32ZmeCoefAddrHL8_05
	mov	r0, #4	@,
	bl	VZmeLoadVpssCoefHL	@
	add	ip, r6, #1856	@ u32PhyAddr.1810, u32PhyAddr,
	add	r1, r4, #2320	@, pu32CurAddr,
	str	ip, [r5, #16]	@ u32PhyAddr.1810, <variable>.u32ZmeCoefAddrHL8_033
	mov	r0, #5	@,
	add	r7, r6, #3648	@ u32PhyAddr.1818, u32PhyAddr,
	bl	VZmeLoadVpssCoefHL	@
	add	r1, r4, #2784	@, pu32CurAddr,
	str	r8, [r5, #20]	@ u32PhyAddr.1812, <variable>.u32ZmeCoefAddrHL8_025
	mov	r0, #6	@,
	add	r8, r4, #4048	@ pu32CurAddr.1821, pu32CurAddr,
	bl	VZmeLoadVpssCoefHL	@
	add	r2, r6, #2784	@ u32PhyAddr.1814, u32PhyAddr,
	add	r1, r4, #3248	@, pu32CurAddr,
	str	r2, [r5, #24]	@ u32PhyAddr.1814, <variable>.u32ZmeCoefAddrHL8_0
	mov	r0, #0	@,
	bl	VZmeLoadVpssCoefHC	@
	add	r1, r6, #3248	@ u32PhyAddr.1816, u32PhyAddr,
	mov	r0, #1	@,
	str	r1, [r5, #28]	@ u32PhyAddr.1816, <variable>.u32ZmeCoefAddrHC4_1
	add	r1, r4, #3648	@, pu32CurAddr,
	add	sl, r6, #5248	@ u32PhyAddr.1826, u32PhyAddr,
	bl	VZmeLoadVpssCoefHC	@
	str	r7, [r5, #32]	@ u32PhyAddr.1818, <variable>.u32ZmeCoefAddrHC4_E1
	mov	r1, r8	@, pu32CurAddr.1821
	mov	r0, #2	@,
	add	r7, r6, #4048	@ u32PhyAddr.1820, u32PhyAddr,
	bl	VZmeLoadVpssCoefHC	@
	str	r7, [r5, #36]	@ u32PhyAddr.1820, <variable>.u32ZmeCoefAddrHC4_075
	add	r1, r8, #400	@, pu32CurAddr.1821,
	mov	r0, #3	@,
	add	r9, r7, #400	@ u32PhyAddr.1822, u32PhyAddr.1820,
	bl	VZmeLoadVpssCoefHC	@
	str	r9, [r5, #40]	@ u32PhyAddr.1822, <variable>.u32ZmeCoefAddrHC4_05
	add	r1, r8, #800	@, pu32CurAddr.1821,
	mov	r0, #4	@,
	bl	VZmeLoadVpssCoefHC	@
	add	r0, r7, #800	@ u32PhyAddr.1824, u32PhyAddr.1820,
	add	r1, r4, #5248	@, pu32CurAddr,
	str	r0, [r5, #44]	@ u32PhyAddr.1824, <variable>.u32ZmeCoefAddrHC4_033
	mov	r0, #5	@,
	add	r9, r7, #2000	@ u32PhyAddr.1830, u32PhyAddr.1820,
	bl	VZmeLoadVpssCoefHC	@
	str	sl, [r5, #48]	@ u32PhyAddr.1826, <variable>.u32ZmeCoefAddrHC4_025
	add	r1, r8, #1600	@, pu32CurAddr.1821,
	mov	r0, #6	@,
	bl	VZmeLoadVpssCoefHC	@
	add	r3, r7, #1600	@ u32PhyAddr.1828, u32PhyAddr.1820,
	add	r1, r8, #2000	@, pu32CurAddr.1821,
	str	r3, [r5, #52]	@ u32PhyAddr.1828, <variable>.u32ZmeCoefAddrHC4_0
	mov	r0, #0	@,
	add	sl, r6, #6720	@ u32PhyAddr.1834, u32PhyAddr,
	bl	VZmeLoadVpssCoefVL	@
	str	r9, [r5, #56]	@ u32PhyAddr.1830, <variable>.u32ZmeCoefAddrVL6_1
	add	r1, r8, #2336	@, pu32CurAddr.1821,
	mov	r0, #1	@,
	bl	VZmeLoadVpssCoefVL	@
	add	ip, r7, #2336	@ u32PhyAddr.1832, u32PhyAddr.1820,
	add	r1, r4, #6720	@, pu32CurAddr,
	str	ip, [r5, #60]	@ u32PhyAddr.1832, <variable>.u32ZmeCoefAddrVL6_E1
	mov	r0, #2	@,
	add	r9, r7, #3008	@ u32PhyAddr.1836, u32PhyAddr.1820,
	bl	VZmeLoadVpssCoefVL	@
	str	sl, [r5, #64]	@ u32PhyAddr.1834, <variable>.u32ZmeCoefAddrVL6_075
	add	r1, r8, #3008	@, pu32CurAddr.1821,
	mov	r0, #3	@,
	bl	VZmeLoadVpssCoefVL	@
	str	r9, [r5, #68]	@ u32PhyAddr.1836, <variable>.u32ZmeCoefAddrVL6_05
	add	r1, r8, #3344	@, pu32CurAddr.1821,
	mov	r0, #4	@,
	add	sl, r8, #4352	@ pu32CurAddr.1845, pu32CurAddr.1821,
	bl	VZmeLoadVpssCoefVL	@
	add	r2, r7, #3344	@ u32PhyAddr.1838, u32PhyAddr.1820,
	add	r1, r8, #3680	@, pu32CurAddr.1821,
	str	r2, [r5, #72]	@ u32PhyAddr.1838, <variable>.u32ZmeCoefAddrVL6_033
	mov	r0, #5	@,
	bl	VZmeLoadVpssCoefVL	@
	add	r9, r7, #3680	@ u32PhyAddr.1840, u32PhyAddr.1820,
	add	r1, r4, #8064	@, pu32CurAddr,
	str	r9, [r5, #76]	@ u32PhyAddr.1840, <variable>.u32ZmeCoefAddrVL6_025
	mov	r0, #6	@,
	add	r6, r6, #8064	@ u32PhyAddr.1842, u32PhyAddr,
	bl	VZmeLoadVpssCoefVL	@
	str	r6, [r5, #80]	@ u32PhyAddr.1842, <variable>.u32ZmeCoefAddrVL6_0
	mov	r1, sl	@, pu32CurAddr.1845
	mov	r0, #0	@,
	add	r4, r7, #4352	@ u32PhyAddr.1844, u32PhyAddr.1820,
	bl	VZmeLoadVpssCoefVC	@
	str	r4, [r5, #84]	@ u32PhyAddr.1844, <variable>.u32ZmeCoefAddrVC4_1
	add	r1, sl, #336	@, pu32CurAddr.1845,
	mov	r0, #1	@,
	add	r6, r4, #672	@ u32PhyAddr.1848, u32PhyAddr.1844,
	bl	VZmeLoadVpssCoefVC	@
	add	r1, r4, #336	@ u32PhyAddr.1846, u32PhyAddr.1844,
	mov	r0, #2	@,
	str	r1, [r5, #88]	@ u32PhyAddr.1846, <variable>.u32ZmeCoefAddrVC4_E1
	add	r1, sl, #672	@, pu32CurAddr.1845,
	add	r7, r7, #5696	@ u32PhyAddr.1852, u32PhyAddr.1820,
	bl	VZmeLoadVpssCoefVC	@
	add	r1, sl, #1008	@, pu32CurAddr.1845,
	str	r6, [r5, #92]	@ u32PhyAddr.1848, <variable>.u32ZmeCoefAddrVC4_075
	mov	r0, #3	@,
	bl	VZmeLoadVpssCoefVC	@
	add	r0, r4, #1008	@ u32PhyAddr.1850, u32PhyAddr.1844,
	add	r1, r8, #5696	@, pu32CurAddr.1821,
	str	r0, [r5, #96]	@ u32PhyAddr.1850, <variable>.u32ZmeCoefAddrVC4_05
	mov	r0, #4	@,
	bl	VZmeLoadVpssCoefVC	@
	add	r1, sl, #1680	@, pu32CurAddr.1845,
	str	r7, [r5, #100]	@ u32PhyAddr.1852, <variable>.u32ZmeCoefAddrVC4_033
	mov	r0, #5	@,
	bl	VZmeLoadVpssCoefVC	@
	add	r3, r4, #1680	@ u32PhyAddr.1854, u32PhyAddr.1844,
	add	r1, sl, #2016	@, pu32CurAddr.1845,
	str	r3, [r5, #104]	@ u32PhyAddr.1854, <variable>.u32ZmeCoefAddrVC4_025
	mov	r0, #6	@,
	add	r4, r4, #2016	@ tmp189, u32PhyAddr.1844,
	bl	VZmeLoadVpssCoefVC	@
	str	r4, [r5, #108]	@ tmp189, <variable>.u32ZmeCoefAddrVC4_0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}	@
	.fnend
	.size	VZmeLoadVpssCoefHV, .-VZmeLoadVpssCoefHV
	.align	2
	.global	ALG_VZmeVpssComnInit
	.type	ALG_VZmeVpssComnInit, %function
ALG_VZmeVpssComnInit:
	.fnstart
.LFB667:
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
	mov	r3, r0	@ pstVZmeVpssCoefMem, pstVZmeVpssCoefMem
	add	r2, r0, #12	@, pstVZmeVpssCoefMem,
	ldr	r1, [r3, #4]	@, <variable>.stMBuf.u32StartPhyAddr
	ldr	r0, [r0, #0]	@, <variable>.stMBuf.u32StartVirAddr
	bl	VZmeLoadVpssCoefHV	@
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	ALG_VZmeVpssComnInit, .-ALG_VZmeVpssComnInit
	.global	g_pVZmeVpssCoef
	.global	g_pVDtiZmeCoef
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	CSWTCH.219, %object
	.size	CSWTCH.219, 16
CSWTCH.219:
	.word	8
	.word	6
	.word	4
	.word	2
	.type	CSWTCH.222, %object
	.size	CSWTCH.222, 16
CSWTCH.222:
	.word	8
	.word	6
	.word	4
	.word	2
	.type	s16SRZmeCoef_8T2P_Lanc3, %object
	.size	s16SRZmeCoef_8T2P_Lanc3, 32
s16SRZmeCoef_8T2P_Lanc3:
	.short	4
	.short	-22
	.short	40
	.short	468
	.short	40
	.short	-22
	.short	4
	.short	0
	.short	0
	.short	14
	.short	-68
	.short	310
	.short	310
	.short	-68
	.short	14
	.short	0
	.type	s16SRZmeCoef_6T32P_6M_a25, %object
	.size	s16SRZmeCoef_6T32P_6M_a25, 24
s16SRZmeCoef_6T32P_6M_a25:
	.short	-34
	.short	78
	.short	415
	.short	78
	.short	-34
	.short	9
	.short	2
	.short	-42
	.short	296
	.short	296
	.short	-42
	.short	2
	.type	g_pVZmeCoef, %object
	.size	g_pVZmeCoef, 196
g_pVZmeCoef:
	.word	s16ZmeCoef_8T32P_Lanc3
	.word	s16ZmeCoef_6T32P_6M_a25
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_8T32P_Lanc3
	.word	s16ZmeCoef_6T32P_6M_a25
	.word	s16ZmeCoef_8T32P_Lanc3
	.word	s16ZmeCoef_6T32P_6M_a25
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_8T32P_Lanc3
	.word	s16ZmeCoef_6T32P_6M_a25
	.word	s16ZmeCoef_8T32P_Lanc2
	.word	s16ZmeCoef_6T32P_5M_a25
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_8T32P_Lanc2
	.word	s16ZmeCoef_6T32P_5M_a25
	.word	s16ZmeCoef_8T32P_Lanc2
	.word	s16ZmeCoef_6T32P_4M_a20
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_8T32P_Lanc2
	.word	s16ZmeCoef_6T32P_4M_a20
	.word	s16ZmeCoef_8T32P_3M_a19
	.word	s16ZmeCoef_6T32P_3M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_8T32P_3M_a19
	.word	s16ZmeCoef_6T32P_3M_a15
	.word	s16ZmeCoef_8T32P_3M_a19
	.word	s16ZmeCoef_6T32P_3M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_8T32P_2M_a05
	.word	s16ZmeCoef_6T32P_2M_a05
	.word	s16ZmeCoef_8T32P_3M_a19
	.word	s16ZmeCoef_6T32P_3M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_8T32P_1_5M_a05
	.word	s16ZmeCoef_6T32P_1_5M_a05
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	g_pVZmeVpssCoef, %object
	.size	g_pVZmeVpssCoef, 196
g_pVZmeVpssCoef:
	.word	s16ZmeCoef_8T32P_Lanc3
	.word	s16ZmeCoef_6T32P_6M_a25
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_8T32P_Lanc3
	.word	s16ZmeCoef_6T32P_6M_a25
	.word	s16ZmeCoef_8T32P_Cubic
	.word	s16ZmeCoef_6T32P_Cubic
	.word	s16ZmeCoef_4T32P_Cubic
	.word	s16ZmeCoef_4T32P_Cubic
	.word	s16ZmeCoef_4T32P_Cubic
	.word	s16ZmeCoef_8T32P_Lanc3
	.word	s16ZmeCoef_6T32P_6M_a25
	.word	s16ZmeCoef_8T32P_Lanc2
	.word	s16ZmeCoef_6T32P_5M_a25
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_8T32P_Lanc2
	.word	s16ZmeCoef_6T32P_5M_a25
	.word	s16ZmeCoef_8T32P_Lanc2
	.word	s16ZmeCoef_6T32P_4M_a20
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_8T32P_Lanc2
	.word	s16ZmeCoef_6T32P_4M_a20
	.word	s16ZmeCoef_8T32P_3M_a19
	.word	s16ZmeCoef_6T32P_3M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_8T32P_3M_a19
	.word	s16ZmeCoef_6T32P_3M_a15
	.word	s16ZmeCoef_8T32P_3M_a19
	.word	s16ZmeCoef_6T32P_3M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_8T32P_2M_a05
	.word	s16ZmeCoef_6T32P_2M_a05
	.word	s16ZmeCoef_8T32P_3M_a19
	.word	s16ZmeCoef_6T32P_3M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_8T32P_1_5M_a05
	.word	s16ZmeCoef_6T32P_1_5M_a05
	.type	g_pVDtiZmeCoef, %object
	.size	g_pVDtiZmeCoef, 112
g_pVDtiZmeCoef:
	.word	s16ZmeCoef_8T32P_Lanc3
	.word	s16ZmeCoef_2T32P_Gus2_6M_a0_5
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_2T32P_4M_0_1
	.word	s16ZmeCoef_8T32P_Cubic
	.word	s16ZmeCoef_2T32P_Gus2_6M_a0_5
	.word	s16ZmeCoef_4T32P_Cubic
	.word	s16ZmeCoef_2T32P_4M_0_1
	.word	s16ZmeCoef_8T32P_Lanc2
	.word	s16ZmeCoef_2T32P_Gus2_6M_a0_5
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_2T32P_4M_0_1
	.word	s16ZmeCoef_8T32P_Lanc2
	.word	s16ZmeCoef_2T32P_Gus2_6M_a0_5
	.word	s16ZmeCoef_4T32P_5M_a15
	.word	s16ZmeCoef_2T32P_4M_0_1
	.word	s16ZmeCoef_8T32P_3M_a19
	.word	s16ZmeCoef_2T32P_Gus2_6M_a0_5
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_2T32P_4M_0_1
	.word	s16ZmeCoef_8T32P_3M_a19
	.word	s16ZmeCoef_2T32P_Gus2_6M_a0_5
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_2T32P_4M_0_1
	.word	s16ZmeCoef_8T32P_3M_a19
	.word	s16ZmeCoef_2T32P_Gus2_6M_a0_5
	.word	s16ZmeCoef_4T32P_4M_a15
	.word	s16ZmeCoef_2T32P_4M_0_1
	.type	s16ZmeCoef_8T32P_Lanc3, %object
	.size	s16ZmeCoef_8T32P_Lanc3, 288
s16ZmeCoef_8T32P_Lanc3:
	.short	4
	.short	-22
	.short	40
	.short	468
	.short	40
	.short	-22
	.short	4
	.short	0
	.short	3
	.short	-18
	.short	26
	.short	468
	.short	54
	.short	-26
	.short	5
	.short	0
	.short	2
	.short	-14
	.short	14
	.short	466
	.short	68
	.short	-30
	.short	6
	.short	0
	.short	2
	.short	-11
	.short	2
	.short	462
	.short	84
	.short	-34
	.short	7
	.short	0
	.short	1
	.short	-7
	.short	-9
	.short	457
	.short	100
	.short	-38
	.short	8
	.short	0
	.short	1
	.short	-4
	.short	-18
	.short	450
	.short	116
	.short	-42
	.short	9
	.short	0
	.short	1
	.short	-2
	.short	-27
	.short	443
	.short	133
	.short	-46
	.short	10
	.short	0
	.short	0
	.short	2
	.short	-35
	.short	434
	.short	151
	.short	-50
	.short	10
	.short	0
	.short	0
	.short	4
	.short	-42
	.short	425
	.short	168
	.short	-54
	.short	11
	.short	0
	.short	0
	.short	6
	.short	-49
	.short	414
	.short	186
	.short	-57
	.short	12
	.short	0
	.short	0
	.short	8
	.short	-54
	.short	401
	.short	204
	.short	-60
	.short	13
	.short	0
	.short	0
	.short	10
	.short	-58
	.short	387
	.short	222
	.short	-62
	.short	13
	.short	0
	.short	0
	.short	11
	.short	-62
	.short	374
	.short	240
	.short	-65
	.short	14
	.short	0
	.short	0
	.short	12
	.short	-65
	.short	359
	.short	258
	.short	-66
	.short	14
	.short	0
	.short	0
	.short	13
	.short	-67
	.short	344
	.short	276
	.short	-68
	.short	14
	.short	0
	.short	0
	.short	14
	.short	-68
	.short	327
	.short	293
	.short	-68
	.short	14
	.short	0
	.short	0
	.short	14
	.short	-68
	.short	310
	.short	310
	.short	-68
	.short	14
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_6T32P_6M_a25, %object
	.size	s16ZmeCoef_6T32P_6M_a25, 216
s16ZmeCoef_6T32P_6M_a25:
	.short	-34
	.short	78
	.short	415
	.short	78
	.short	-34
	.short	9
	.short	-32
	.short	66
	.short	415
	.short	90
	.short	-36
	.short	9
	.short	-29
	.short	54
	.short	413
	.short	103
	.short	-38
	.short	9
	.short	-26
	.short	43
	.short	411
	.short	116
	.short	-41
	.short	9
	.short	-23
	.short	33
	.short	406
	.short	129
	.short	-42
	.short	9
	.short	-21
	.short	24
	.short	401
	.short	143
	.short	-44
	.short	9
	.short	-18
	.short	14
	.short	396
	.short	157
	.short	-46
	.short	9
	.short	-16
	.short	6
	.short	389
	.short	171
	.short	-47
	.short	9
	.short	-14
	.short	-2
	.short	382
	.short	185
	.short	-48
	.short	9
	.short	-11
	.short	-9
	.short	374
	.short	199
	.short	-49
	.short	8
	.short	-9
	.short	-16
	.short	365
	.short	213
	.short	-49
	.short	8
	.short	-7
	.short	-21
	.short	354
	.short	228
	.short	-49
	.short	7
	.short	-5
	.short	-27
	.short	345
	.short	242
	.short	-49
	.short	6
	.short	-3
	.short	-32
	.short	333
	.short	256
	.short	-48
	.short	6
	.short	-1
	.short	-36
	.short	322
	.short	269
	.short	-46
	.short	4
	.short	0
	.short	-39
	.short	309
	.short	283
	.short	-44
	.short	3
	.short	2
	.short	-42
	.short	296
	.short	296
	.short	-42
	.short	2
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_4T32P_5M_a15, %object
	.size	s16ZmeCoef_4T32P_5M_a15, 144
s16ZmeCoef_4T32P_5M_a15:
	.short	103
	.short	335
	.short	103
	.short	-29
	.short	92
	.short	335
	.short	112
	.short	-27
	.short	84
	.short	335
	.short	121
	.short	-28
	.short	75
	.short	334
	.short	131
	.short	-28
	.short	67
	.short	332
	.short	141
	.short	-28
	.short	59
	.short	329
	.short	152
	.short	-28
	.short	51
	.short	326
	.short	162
	.short	-27
	.short	43
	.short	323
	.short	173
	.short	-27
	.short	36
	.short	319
	.short	183
	.short	-26
	.short	30
	.short	313
	.short	194
	.short	-25
	.short	23
	.short	308
	.short	204
	.short	-23
	.short	17
	.short	301
	.short	215
	.short	-21
	.short	12
	.short	295
	.short	225
	.short	-20
	.short	6
	.short	288
	.short	235
	.short	-17
	.short	2
	.short	280
	.short	244
	.short	-14
	.short	-3
	.short	271
	.short	254
	.short	-10
	.short	-7
	.short	263
	.short	263
	.short	-7
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_8T32P_Cubic, %object
	.size	s16ZmeCoef_8T32P_Cubic, 288
s16ZmeCoef_8T32P_Cubic:
	.short	0
	.short	0
	.short	0
	.short	511
	.short	0
	.short	0
	.short	0
	.short	0
	.short	-1
	.short	3
	.short	-12
	.short	511
	.short	14
	.short	-4
	.short	1
	.short	0
	.short	-2
	.short	6
	.short	-23
	.short	509
	.short	28
	.short	-8
	.short	2
	.short	0
	.short	-2
	.short	9
	.short	-33
	.short	503
	.short	44
	.short	-12
	.short	3
	.short	0
	.short	-3
	.short	11
	.short	-41
	.short	496
	.short	61
	.short	-16
	.short	4
	.short	0
	.short	-3
	.short	13
	.short	-48
	.short	488
	.short	79
	.short	-21
	.short	5
	.short	-1
	.short	-3
	.short	14
	.short	-54
	.short	477
	.short	98
	.short	-25
	.short	7
	.short	-2
	.short	-4
	.short	16
	.short	-59
	.short	465
	.short	118
	.short	-30
	.short	8
	.short	-2
	.short	-4
	.short	17
	.short	-63
	.short	451
	.short	138
	.short	-35
	.short	9
	.short	-1
	.short	-4
	.short	18
	.short	-66
	.short	437
	.short	158
	.short	-39
	.short	10
	.short	-2
	.short	-4
	.short	18
	.short	-68
	.short	421
	.short	180
	.short	-44
	.short	11
	.short	-2
	.short	-4
	.short	18
	.short	-69
	.short	404
	.short	201
	.short	-48
	.short	13
	.short	-3
	.short	-4
	.short	18
	.short	-70
	.short	386
	.short	222
	.short	-52
	.short	14
	.short	-2
	.short	-4
	.short	18
	.short	-70
	.short	368
	.short	244
	.short	-56
	.short	15
	.short	-3
	.short	-4
	.short	18
	.short	-69
	.short	348
	.short	265
	.short	-59
	.short	16
	.short	-3
	.short	-4
	.short	18
	.short	-67
	.short	329
	.short	286
	.short	-63
	.short	16
	.short	-3
	.short	-3
	.short	17
	.short	-65
	.short	307
	.short	307
	.short	-65
	.short	17
	.short	-3
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_6T32P_Cubic, %object
	.size	s16ZmeCoef_6T32P_Cubic, 216
s16ZmeCoef_6T32P_Cubic:
	.short	0
	.short	0
	.short	511
	.short	0
	.short	0
	.short	0
	.short	3
	.short	-12
	.short	511
	.short	13
	.short	-3
	.short	0
	.short	6
	.short	-22
	.short	507
	.short	28
	.short	-7
	.short	0
	.short	8
	.short	-32
	.short	502
	.short	44
	.short	-11
	.short	1
	.short	10
	.short	-40
	.short	495
	.short	61
	.short	-15
	.short	1
	.short	11
	.short	-47
	.short	486
	.short	79
	.short	-19
	.short	2
	.short	12
	.short	-53
	.short	476
	.short	98
	.short	-24
	.short	3
	.short	13
	.short	-58
	.short	464
	.short	117
	.short	-28
	.short	4
	.short	14
	.short	-62
	.short	451
	.short	137
	.short	-33
	.short	5
	.short	15
	.short	-65
	.short	437
	.short	157
	.short	-38
	.short	6
	.short	15
	.short	-67
	.short	420
	.short	179
	.short	-42
	.short	7
	.short	15
	.short	-68
	.short	404
	.short	200
	.short	-46
	.short	7
	.short	14
	.short	-68
	.short	386
	.short	221
	.short	-50
	.short	9
	.short	14
	.short	-68
	.short	367
	.short	243
	.short	-54
	.short	10
	.short	14
	.short	-67
	.short	348
	.short	264
	.short	-58
	.short	11
	.short	13
	.short	-66
	.short	328
	.short	286
	.short	-61
	.short	12
	.short	13
	.short	-63
	.short	306
	.short	306
	.short	-63
	.short	13
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_4T32P_Cubic, %object
	.size	s16ZmeCoef_4T32P_Cubic, 144
s16ZmeCoef_4T32P_Cubic:
	.short	0
	.short	511
	.short	0
	.short	0
	.short	-19
	.short	511
	.short	21
	.short	-1
	.short	-37
	.short	509
	.short	42
	.short	-2
	.short	-51
	.short	504
	.short	64
	.short	-5
	.short	-64
	.short	499
	.short	86
	.short	-9
	.short	-74
	.short	492
	.short	108
	.short	-14
	.short	-82
	.short	484
	.short	129
	.short	-19
	.short	-89
	.short	474
	.short	152
	.short	-25
	.short	-94
	.short	463
	.short	174
	.short	-31
	.short	-97
	.short	451
	.short	196
	.short	-38
	.short	-98
	.short	438
	.short	217
	.short	-45
	.short	-98
	.short	424
	.short	238
	.short	-52
	.short	-98
	.short	409
	.short	260
	.short	-59
	.short	-95
	.short	392
	.short	280
	.short	-65
	.short	-92
	.short	376
	.short	300
	.short	-72
	.short	-88
	.short	358
	.short	320
	.short	-78
	.short	-83
	.short	339
	.short	339
	.short	-83
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_8T32P_Lanc2, %object
	.size	s16ZmeCoef_8T32P_Lanc2, 288
s16ZmeCoef_8T32P_Lanc2:
	.short	-16
	.short	0
	.short	145
	.short	254
	.short	145
	.short	0
	.short	-16
	.short	0
	.short	-16
	.short	-2
	.short	140
	.short	253
	.short	151
	.short	3
	.short	-17
	.short	0
	.short	-15
	.short	-5
	.short	135
	.short	253
	.short	157
	.short	5
	.short	-18
	.short	0
	.short	-14
	.short	-7
	.short	129
	.short	252
	.short	162
	.short	8
	.short	-18
	.short	0
	.short	-13
	.short	-9
	.short	123
	.short	252
	.short	167
	.short	11
	.short	-19
	.short	0
	.short	-13
	.short	-11
	.short	118
	.short	250
	.short	172
	.short	15
	.short	-19
	.short	0
	.short	-12
	.short	-12
	.short	112
	.short	250
	.short	177
	.short	18
	.short	-20
	.short	-1
	.short	-11
	.short	-14
	.short	107
	.short	247
	.short	183
	.short	21
	.short	-20
	.short	-1
	.short	-10
	.short	-15
	.short	101
	.short	245
	.short	188
	.short	25
	.short	-21
	.short	-1
	.short	-9
	.short	-16
	.short	96
	.short	243
	.short	192
	.short	29
	.short	-21
	.short	-2
	.short	-8
	.short	-18
	.short	90
	.short	242
	.short	197
	.short	33
	.short	-22
	.short	-2
	.short	-8
	.short	-19
	.short	85
	.short	239
	.short	202
	.short	37
	.short	-22
	.short	-2
	.short	-7
	.short	-19
	.short	80
	.short	236
	.short	206
	.short	41
	.short	-22
	.short	-3
	.short	-7
	.short	-20
	.short	75
	.short	233
	.short	210
	.short	46
	.short	-22
	.short	-3
	.short	-6
	.short	-21
	.short	69
	.short	230
	.short	215
	.short	50
	.short	-22
	.short	-3
	.short	-5
	.short	-21
	.short	65
	.short	226
	.short	219
	.short	55
	.short	-22
	.short	-5
	.short	-5
	.short	-21
	.short	60
	.short	222
	.short	222
	.short	60
	.short	-21
	.short	-5
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_6T32P_5M_a25, %object
	.size	s16ZmeCoef_6T32P_5M_a25, 216
s16ZmeCoef_6T32P_5M_a25:
	.short	-31
	.short	104
	.short	362
	.short	104
	.short	-31
	.short	4
	.short	-30
	.short	94
	.short	362
	.short	114
	.short	-32
	.short	4
	.short	-29
	.short	84
	.short	361
	.short	125
	.short	-32
	.short	3
	.short	-28
	.short	75
	.short	359
	.short	136
	.short	-33
	.short	3
	.short	-27
	.short	66
	.short	356
	.short	147
	.short	-33
	.short	3
	.short	-25
	.short	57
	.short	353
	.short	158
	.short	-33
	.short	2
	.short	-24
	.short	49
	.short	349
	.short	169
	.short	-33
	.short	2
	.short	-22
	.short	41
	.short	344
	.short	180
	.short	-32
	.short	1
	.short	-20
	.short	33
	.short	339
	.short	191
	.short	-31
	.short	0
	.short	-19
	.short	26
	.short	333
	.short	203
	.short	-30
	.short	-1
	.short	-17
	.short	19
	.short	327
	.short	214
	.short	-29
	.short	-2
	.short	-16
	.short	13
	.short	320
	.short	225
	.short	-27
	.short	-3
	.short	-14
	.short	7
	.short	312
	.short	236
	.short	-25
	.short	-4
	.short	-13
	.short	1
	.short	305
	.short	246
	.short	-22
	.short	-5
	.short	-11
	.short	-4
	.short	295
	.short	257
	.short	-19
	.short	-6
	.short	-10
	.short	-8
	.short	286
	.short	267
	.short	-16
	.short	-7
	.short	-9
	.short	-12
	.short	277
	.short	277
	.short	-12
	.short	-9
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_6T32P_4M_a20, %object
	.size	s16ZmeCoef_6T32P_4M_a20, 216
s16ZmeCoef_6T32P_4M_a20:
	.short	-20
	.short	130
	.short	297
	.short	130
	.short	-20
	.short	-5
	.short	-21
	.short	122
	.short	298
	.short	138
	.short	-19
	.short	-6
	.short	-22
	.short	115
	.short	297
	.short	146
	.short	-17
	.short	-7
	.short	-22
	.short	108
	.short	296
	.short	153
	.short	-16
	.short	-7
	.short	-23
	.short	101
	.short	295
	.short	161
	.short	-14
	.short	-8
	.short	-23
	.short	93
	.short	294
	.short	169
	.short	-12
	.short	-9
	.short	-24
	.short	87
	.short	292
	.short	177
	.short	-10
	.short	-10
	.short	-24
	.short	80
	.short	289
	.short	185
	.short	-7
	.short	-11
	.short	-24
	.short	73
	.short	286
	.short	193
	.short	-4
	.short	-12
	.short	-23
	.short	66
	.short	283
	.short	200
	.short	-1
	.short	-13
	.short	-23
	.short	60
	.short	279
	.short	208
	.short	2
	.short	-14
	.short	-23
	.short	54
	.short	276
	.short	215
	.short	5
	.short	-15
	.short	-22
	.short	48
	.short	271
	.short	222
	.short	9
	.short	-16
	.short	-21
	.short	42
	.short	266
	.short	229
	.short	13
	.short	-17
	.short	-21
	.short	37
	.short	261
	.short	236
	.short	17
	.short	-18
	.short	-21
	.short	32
	.short	255
	.short	242
	.short	22
	.short	-18
	.short	-20
	.short	27
	.short	249
	.short	249
	.short	27
	.short	-20
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_8T32P_3M_a19, %object
	.size	s16ZmeCoef_8T32P_3M_a19, 288
s16ZmeCoef_8T32P_3M_a19:
	.short	-18
	.short	18
	.short	144
	.short	226
	.short	144
	.short	19
	.short	-17
	.short	-4
	.short	-17
	.short	16
	.short	139
	.short	226
	.short	148
	.short	21
	.short	-17
	.short	-4
	.short	-17
	.short	13
	.short	135
	.short	227
	.short	153
	.short	24
	.short	-18
	.short	-5
	.short	-17
	.short	11
	.short	131
	.short	226
	.short	157
	.short	27
	.short	-18
	.short	-5
	.short	-17
	.short	9
	.short	126
	.short	225
	.short	161
	.short	30
	.short	-17
	.short	-5
	.short	-16
	.short	6
	.short	122
	.short	225
	.short	165
	.short	33
	.short	-17
	.short	-6
	.short	-16
	.short	4
	.short	118
	.short	224
	.short	169
	.short	37
	.short	-17
	.short	-7
	.short	-16
	.short	2
	.short	113
	.short	224
	.short	173
	.short	40
	.short	-17
	.short	-7
	.short	-15
	.short	0
	.short	109
	.short	222
	.short	177
	.short	43
	.short	-17
	.short	-7
	.short	-15
	.short	-1
	.short	104
	.short	220
	.short	181
	.short	47
	.short	-16
	.short	-8
	.short	-14
	.short	-3
	.short	100
	.short	218
	.short	185
	.short	51
	.short	-16
	.short	-9
	.short	-14
	.short	-5
	.short	96
	.short	217
	.short	188
	.short	54
	.short	-15
	.short	-9
	.short	-14
	.short	-6
	.short	91
	.short	214
	.short	192
	.short	58
	.short	-14
	.short	-9
	.short	-13
	.short	-7
	.short	87
	.short	212
	.short	195
	.short	62
	.short	-14
	.short	-10
	.short	-13
	.short	-9
	.short	83
	.short	210
	.short	198
	.short	66
	.short	-13
	.short	-10
	.short	-12
	.short	-10
	.short	79
	.short	207
	.short	201
	.short	70
	.short	-12
	.short	-11
	.short	-12
	.short	-11
	.short	74
	.short	205
	.short	205
	.short	74
	.short	-11
	.short	-12
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_6T32P_3M_a15, %object
	.size	s16ZmeCoef_6T32P_3M_a15, 216
s16ZmeCoef_6T32P_3M_a15:
	.short	16
	.short	136
	.short	217
	.short	136
	.short	16
	.short	-9
	.short	13
	.short	132
	.short	217
	.short	141
	.short	18
	.short	-9
	.short	11
	.short	128
	.short	217
	.short	145
	.short	21
	.short	-10
	.short	9
	.short	124
	.short	216
	.short	149
	.short	24
	.short	-10
	.short	7
	.short	119
	.short	216
	.short	153
	.short	27
	.short	-10
	.short	5
	.short	115
	.short	216
	.short	157
	.short	30
	.short	-11
	.short	3
	.short	111
	.short	215
	.short	161
	.short	33
	.short	-11
	.short	1
	.short	107
	.short	214
	.short	165
	.short	36
	.short	-11
	.short	0
	.short	102
	.short	213
	.short	169
	.short	39
	.short	-11
	.short	-2
	.short	98
	.short	211
	.short	173
	.short	43
	.short	-11
	.short	-3
	.short	94
	.short	209
	.short	177
	.short	46
	.short	-11
	.short	-4
	.short	90
	.short	207
	.short	180
	.short	50
	.short	-11
	.short	-5
	.short	85
	.short	206
	.short	184
	.short	53
	.short	-11
	.short	-6
	.short	81
	.short	203
	.short	187
	.short	57
	.short	-10
	.short	-7
	.short	77
	.short	201
	.short	190
	.short	61
	.short	-10
	.short	-8
	.short	73
	.short	198
	.short	193
	.short	65
	.short	-9
	.short	-9
	.short	69
	.short	196
	.short	196
	.short	69
	.short	-9
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_4T32P_4M_a15, %object
	.size	s16ZmeCoef_4T32P_4M_a15, 144
s16ZmeCoef_4T32P_4M_a15:
	.short	120
	.short	281
	.short	120
	.short	-9
	.short	113
	.short	281
	.short	127
	.short	-9
	.short	106
	.short	280
	.short	134
	.short	-8
	.short	99
	.short	279
	.short	141
	.short	-7
	.short	92
	.short	277
	.short	148
	.short	-5
	.short	85
	.short	275
	.short	156
	.short	-4
	.short	79
	.short	273
	.short	162
	.short	-2
	.short	72
	.short	270
	.short	170
	.short	0
	.short	66
	.short	267
	.short	177
	.short	2
	.short	61
	.short	263
	.short	184
	.short	4
	.short	56
	.short	259
	.short	191
	.short	6
	.short	50
	.short	255
	.short	198
	.short	9
	.short	44
	.short	251
	.short	205
	.short	12
	.short	40
	.short	246
	.short	211
	.short	15
	.short	34
	.short	241
	.short	218
	.short	19
	.short	31
	.short	235
	.short	224
	.short	22
	.short	26
	.short	230
	.short	230
	.short	26
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_8T32P_2M_a05, %object
	.size	s16ZmeCoef_8T32P_2M_a05, 288
s16ZmeCoef_8T32P_2M_a05:
	.short	14
	.short	66
	.short	113
	.short	133
	.short	113
	.short	66
	.short	14
	.short	-7
	.short	12
	.short	65
	.short	112
	.short	133
	.short	114
	.short	68
	.short	15
	.short	-7
	.short	11
	.short	63
	.short	111
	.short	132
	.short	115
	.short	70
	.short	17
	.short	-7
	.short	10
	.short	62
	.short	110
	.short	132
	.short	116
	.short	71
	.short	18
	.short	-7
	.short	8
	.short	60
	.short	108
	.short	132
	.short	118
	.short	73
	.short	20
	.short	-7
	.short	7
	.short	58
	.short	107
	.short	132
	.short	119
	.short	75
	.short	21
	.short	-7
	.short	6
	.short	56
	.short	106
	.short	132
	.short	120
	.short	76
	.short	23
	.short	-7
	.short	5
	.short	55
	.short	105
	.short	131
	.short	121
	.short	78
	.short	24
	.short	-7
	.short	4
	.short	53
	.short	103
	.short	131
	.short	122
	.short	80
	.short	26
	.short	-7
	.short	3
	.short	51
	.short	102
	.short	131
	.short	122
	.short	81
	.short	28
	.short	-6
	.short	2
	.short	50
	.short	101
	.short	130
	.short	123
	.short	83
	.short	29
	.short	-6
	.short	1
	.short	48
	.short	99
	.short	131
	.short	124
	.short	84
	.short	31
	.short	-6
	.short	0
	.short	46
	.short	98
	.short	129
	.short	125
	.short	86
	.short	33
	.short	-5
	.short	-1
	.short	45
	.short	97
	.short	128
	.short	126
	.short	88
	.short	34
	.short	-5
	.short	-2
	.short	43
	.short	95
	.short	130
	.short	126
	.short	89
	.short	36
	.short	-5
	.short	-3
	.short	41
	.short	94
	.short	128
	.short	127
	.short	91
	.short	38
	.short	-4
	.short	-3
	.short	39
	.short	92
	.short	128
	.short	128
	.short	92
	.short	39
	.short	-3
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_6T32P_2M_a05, %object
	.size	s16ZmeCoef_6T32P_2M_a05, 216
s16ZmeCoef_6T32P_2M_a05:
	.short	66
	.short	115
	.short	138
	.short	115
	.short	66
	.short	12
	.short	64
	.short	114
	.short	136
	.short	116
	.short	68
	.short	14
	.short	63
	.short	113
	.short	134
	.short	117
	.short	70
	.short	15
	.short	61
	.short	111
	.short	135
	.short	118
	.short	71
	.short	16
	.short	59
	.short	110
	.short	133
	.short	119
	.short	73
	.short	18
	.short	57
	.short	108
	.short	134
	.short	120
	.short	74
	.short	19
	.short	55
	.short	107
	.short	133
	.short	121
	.short	76
	.short	20
	.short	53
	.short	105
	.short	133
	.short	121
	.short	78
	.short	22
	.short	51
	.short	104
	.short	133
	.short	122
	.short	79
	.short	23
	.short	49
	.short	102
	.short	132
	.short	123
	.short	81
	.short	25
	.short	47
	.short	101
	.short	132
	.short	124
	.short	82
	.short	26
	.short	45
	.short	99
	.short	131
	.short	125
	.short	84
	.short	28
	.short	44
	.short	98
	.short	130
	.short	125
	.short	85
	.short	30
	.short	42
	.short	96
	.short	130
	.short	126
	.short	87
	.short	31
	.short	40
	.short	95
	.short	128
	.short	127
	.short	89
	.short	33
	.short	38
	.short	93
	.short	129
	.short	127
	.short	90
	.short	35
	.short	36
	.short	92
	.short	128
	.short	128
	.short	92
	.short	36
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_8T32P_1_5M_a05, %object
	.size	s16ZmeCoef_8T32P_1_5M_a05, 288
s16ZmeCoef_8T32P_1_5M_a05:
	.short	39
	.short	69
	.short	93
	.short	102
	.short	93
	.short	69
	.short	39
	.short	8
	.short	38
	.short	68
	.short	92
	.short	102
	.short	93
	.short	70
	.short	40
	.short	9
	.short	37
	.short	67
	.short	91
	.short	102
	.short	93
	.short	71
	.short	41
	.short	10
	.short	36
	.short	66
	.short	91
	.short	101
	.short	94
	.short	71
	.short	42
	.short	11
	.short	35
	.short	65
	.short	90
	.short	102
	.short	94
	.short	72
	.short	43
	.short	11
	.short	34
	.short	64
	.short	89
	.short	102
	.short	94
	.short	73
	.short	44
	.short	12
	.short	33
	.short	63
	.short	88
	.short	101
	.short	95
	.short	74
	.short	45
	.short	13
	.short	32
	.short	62
	.short	88
	.short	100
	.short	95
	.short	75
	.short	46
	.short	14
	.short	31
	.short	62
	.short	87
	.short	100
	.short	95
	.short	75
	.short	47
	.short	15
	.short	30
	.short	61
	.short	86
	.short	99
	.short	96
	.short	76
	.short	48
	.short	16
	.short	29
	.short	60
	.short	86
	.short	98
	.short	96
	.short	77
	.short	49
	.short	17
	.short	28
	.short	59
	.short	85
	.short	98
	.short	96
	.short	78
	.short	50
	.short	18
	.short	27
	.short	58
	.short	84
	.short	99
	.short	97
	.short	78
	.short	50
	.short	19
	.short	26
	.short	57
	.short	83
	.short	99
	.short	97
	.short	79
	.short	51
	.short	20
	.short	25
	.short	56
	.short	83
	.short	98
	.short	97
	.short	80
	.short	52
	.short	21
	.short	24
	.short	55
	.short	82
	.short	97
	.short	98
	.short	81
	.short	53
	.short	22
	.short	23
	.short	54
	.short	81
	.short	98
	.short	98
	.short	81
	.short	54
	.short	23
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_6T32P_1_5M_a05, %object
	.size	s16ZmeCoef_6T32P_1_5M_a05, 216
s16ZmeCoef_6T32P_1_5M_a05:
	.short	80
	.short	105
	.short	116
	.short	105
	.short	80
	.short	26
	.short	79
	.short	104
	.short	115
	.short	105
	.short	81
	.short	28
	.short	77
	.short	103
	.short	116
	.short	106
	.short	81
	.short	29
	.short	76
	.short	102
	.short	115
	.short	106
	.short	82
	.short	31
	.short	74
	.short	101
	.short	115
	.short	106
	.short	83
	.short	33
	.short	73
	.short	100
	.short	114
	.short	106
	.short	84
	.short	35
	.short	71
	.short	99
	.short	114
	.short	107
	.short	84
	.short	37
	.short	70
	.short	98
	.short	113
	.short	107
	.short	85
	.short	39
	.short	68
	.short	98
	.short	113
	.short	107
	.short	86
	.short	40
	.short	67
	.short	97
	.short	112
	.short	108
	.short	86
	.short	42
	.short	65
	.short	96
	.short	112
	.short	108
	.short	87
	.short	44
	.short	63
	.short	95
	.short	112
	.short	108
	.short	88
	.short	46
	.short	62
	.short	94
	.short	112
	.short	108
	.short	88
	.short	48
	.short	60
	.short	93
	.short	111
	.short	109
	.short	89
	.short	50
	.short	58
	.short	93
	.short	111
	.short	109
	.short	90
	.short	51
	.short	57
	.short	92
	.short	110
	.short	110
	.short	90
	.short	53
	.short	55
	.short	91
	.short	110
	.short	110
	.short	91
	.short	55
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.type	s16ZmeCoef_2T32P_Gus2_6M_a0_5, %object
	.size	s16ZmeCoef_2T32P_Gus2_6M_a0_5, 72
s16ZmeCoef_2T32P_Gus2_6M_a0_5:
	.short	462
	.short	50
	.short	449
	.short	63
	.short	437
	.short	75
	.short	424
	.short	88
	.short	411
	.short	101
	.short	398
	.short	114
	.short	386
	.short	126
	.short	373
	.short	139
	.short	360
	.short	152
	.short	347
	.short	165
	.short	334
	.short	178
	.short	321
	.short	191
	.short	308
	.short	204
	.short	295
	.short	217
	.short	282
	.short	230
	.short	269
	.short	243
	.short	256
	.short	256
	.short	0
	.short	0
	.type	s16ZmeCoef_2T32P_4M_0_1, %object
	.size	s16ZmeCoef_2T32P_4M_0_1, 72
s16ZmeCoef_2T32P_4M_0_1:
	.short	366
	.short	146
	.short	359
	.short	153
	.short	351
	.short	161
	.short	344
	.short	168
	.short	337
	.short	175
	.short	330
	.short	182
	.short	323
	.short	189
	.short	316
	.short	196
	.short	309
	.short	203
	.short	302
	.short	210
	.short	296
	.short	216
	.short	289
	.short	223
	.short	282
	.short	230
	.short	276
	.short	236
	.short	269
	.short	243
	.short	263
	.short	249
	.short	256
	.short	256
	.short	0
	.short	0
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
