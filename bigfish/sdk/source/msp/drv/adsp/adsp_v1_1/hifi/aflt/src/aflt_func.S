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
	.file	"aflt_func.c"
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
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/adsp/adsp_v1_1
@ -Idrivers/msp/adsp/adsp_v1_1
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/mach-hi3798mx/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/api/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/common/drv/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/api/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/component/ha_codec/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/component/ha_effect/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/include/comp
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/common/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/aoe/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/aflt/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/aoe/src/include
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/component/codec/iapcm_dec
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/component/codec/iamp3_dec
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1/./hifi/component/effect/base_effect
@ -I/hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/../../../source/msp/drv/adsp/adsp_v1_1
@ -imultilib armv7a_soft -iprefix
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/
@ -isysroot /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../target
@ -D__KERNEL__ -D__LINUX_ARM_ARCH__=7 -Uarm -DCHIP_TYPE_hi3796mv100
@ -DSDK_VERSION=HiSTBAndroidV600R001C00SPC060_v2015040918 -DHI_MCE_SUPPORT
@ -DHI_GPIOI2C_SUPPORT -DHI_LOG_SUPPORT=1 -DHI_LOG_LEVEL=4
@ -DHI_PROC_SUPPORT=1 -DHI_HDMI_SUPPORT_1_4 -DHI_KEYLED_SUPPORT
@ -DHI_HDCP_SUPPORT -DHI_SCI_SUPPORT -DHI_PVR_SUPPORT -DHI_VI_SUPPORT
@ -DHI_VENC_SUPPORT -DHI_AENC_SUPPORT -DHI_PQ_V3_0
@ -DHI_SND_AOE_SWSIMULATE_SUPPORT -DHI_SND_AFLT_SWSIMULATE_SUPPORT
@ -DINTERLEAVED_OUTPUT -DPCM_DECODER_SUPPORT -DBASE_EFFECT_SUPPORT
@ -DHI_SND_TIMER_CAST -DKBUILD_STR(s)=#s
@ -DKBUILD_BASENAME=KBUILD_STR(aflt_func)
@ -DKBUILD_MODNAME=KBUILD_STR(hi_adsp) -isystem
@ /opt/hisi-linux/x86-arm/arm-hisiv200-linux/bin/../lib/gcc/arm-hisiv200-linux-gnueabi/4.4.1/include
@ -include
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/include/linux/kconfig.h
@ -MD drivers/msp/adsp/adsp_v1_1/./hifi/aflt/src/.aflt_func.o.d
@ /hihome/HiSTBAndroidV5/images_and_tools/release/hi3798mv100/master_4.4/HiSTBAndroidV5_release/HiSTBAndroidV600R001C00SPC060/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/drivers/msp/adsp/adsp_v1_1/./hifi/aflt/src/aflt_func.c
@ -mlittle-endian -mapcs -mno-sched-prolog -mabi=aapcs-linux
@ -mno-thumb-interwork -marm -march=armv7-a -msoft-float -auxbase-strip
@ drivers/msp/adsp/adsp_v1_1/./hifi/aflt/src/aflt_func.o -O2 -Wall -Wundef
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
	.global	AFLTFlushInfifo
	.type	AFLTFlushInfifo, %function
AFLTFlushInfifo:
	.fnstart
.LFB884:
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
	mov	r3, #0	@ tmp134,
	str	r3, [r0, #116]	@ tmp134, <variable>.u32DMAInFifoBytesLeft
	str	r3, [r0, #120]	@ tmp134, <variable>.u32DMAInFifoReadOffset
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	AFLTFlushInfifo, .-AFLTFlushInfifo
	.align	2
	.global	AFLTFlushOutbuf
	.type	AFLTFlushOutbuf, %function
AFLTFlushOutbuf:
	.fnstart
.LFB885:
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
	ldr	ip, [r0, #92]	@ <variable>.Id, <variable>.Id
	movw	r0, #:lower16:.LANCHOR0	@ tmp141,
	movt	r0, #:upper16:.LANCHOR0	@ tmp141,
	ldr	r3, [r0, ip, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r1, [r3, #56]	@ D.15185, <variable>.OP_BUF_WIDX.u32
	ldr	r2, [r3, #60]	@ D.15186, <variable>.OP_BUF_RIDX.u32
	bfc	r1, #0, #4	@ OP_BUF_WIDX,,
	bfc	r2, #0, #4	@ OP_BUF_RIDX,,
	bfc	r1, #4, #1	@ OP_BUF_WIDX,,
	bfc	r2, #4, #1	@ OP_BUF_RIDX,,
	str	r1, [r3, #56]	@ OP_BUF_WIDX, <variable>.OP_BUF_WIDX.u32
	str	r2, [r3, #60]	@ OP_BUF_RIDX, <variable>.OP_BUF_RIDX.u32
	ldmfd	sp, {fp, sp, pc}	@
	.fnend
	.size	AFLTFlushOutbuf, .-AFLTFlushOutbuf
	.align	2
	.global	AFLTProcFrame
	.type	AFLTProcFrame, %function
AFLTProcFrame:
	.fnstart
.LFB921:
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
	movw	r5, #:lower16:.LANCHOR0	@ tmp147,
	add	r0, r0, #8	@ tmp148, Id,
	movt	r5, #:upper16:.LANCHOR0	@ tmp147,
	mov	r6, r2	@ pstDstFrame, pstDstFrame
	ldr	r4, [r5, r0, asl #2]	@ state, g_stAfltRm.hAflt
	cmp	r4, #0	@ state,
	beq	.L9	@,
	ldr	r3, [r4, #0]	@ <variable>.stAttr.bMaster, <variable>.stAttr.bMaster
	cmp	r3, #1	@ <variable>.stAttr.bMaster,
	beq	.L9	@,
	ldr	r3, [r4, #92]	@ <variable>.Id, <variable>.Id
	ldr	r0, [r5, r3, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r2, [r0, #72]	@ Cnt, <variable>.TRY_EXE_CNT
	add	ip, r2, #1	@ D.16044, Cnt,
	str	ip, [r0, #72]	@ D.16044, <variable>.TRY_EXE_CNT
	ldr	r2, [r4, #96]	@ <variable>.enCurnStatus, <variable>.enCurnStatus
	cmp	r2, #0	@ <variable>.enCurnStatus,
	beq	.L11	@,
	ldr	r0, [r1, #0]	@ <variable>.pDataBuf, <variable>.pDataBuf
	str	r0, [r6, #0]	@ <variable>.pDataBuf, <variable>.pDataBuf
.L9:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L11:
	ldr	lr, [r4, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r2, [r1, #8]	@, <variable>.u32DataBytes
	ldr	r0, [r4, #84]	@, <variable>.hComponent
	ldr	ip, [lr, #32]	@ <variable>.SetInputBuffer, <variable>.SetInputBuffer
	ldr	r1, [r1, #0]	@, <variable>.pDataBuf
	blx	ip	@ <variable>.SetInputBuffer
	ldr	r1, [r4, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r2, [r6, #8]	@, <variable>.u32DataBytes
	ldr	r0, [r4, #84]	@, <variable>.hComponent
	ldr	r3, [r1, #36]	@ <variable>.SetOutputBuffer, <variable>.SetOutputBuffer
	ldr	r1, [r6, #0]	@, <variable>.pDataBuf
	blx	r3	@ <variable>.SetOutputBuffer
	ldr	ip, [r4, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r0, [r4, #84]	@, <variable>.hComponent
	sub	r1, fp, #36	@,,
	ldr	r3, [ip, #48]	@ <variable>.ExcuteFrame, <variable>.ExcuteFrame
	blx	r3	@ <variable>.ExcuteFrame
	ldr	r2, [r4, #92]	@ <variable>.Id, <variable>.Id
	ldr	ip, [r5, r2, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	orrs	r3, r0, r1	@,
	ldreqh	r2, [ip, #64]	@ <variable>.STATUS0.bits.frame_cnt, <variable>.STATUS0.bits.frame_cnt
	ldrneb	r2, [ip, #66]	@ zero_extendqisi2	@ <variable>.STATUS0.bits.frame_err_cnt, <variable>.STATUS0.bits.frame_err_cnt
	addeq	r2, r2, #1	@ tmp171, <variable>.STATUS0.bits.frame_cnt,
	addne	r2, r2, #1	@ tmp176, <variable>.STATUS0.bits.frame_err_cnt,
	uxtheq	r2, r2	@ D.16052, tmp171
	streqh	r2, [ip, #64]	@ movhi	@ D.16052, <variable>.STATUS0.bits.frame_cnt
	uxtbne	r2, r2	@ D.16059, tmp176
	strneb	r2, [ip, #66]	@ D.16059, <variable>.STATUS0.bits.frame_err_cnt
	b	.L9	@
	.fnend
	.size	AFLTProcFrame, .-AFLTProcFrame
	.align	2
	.type	AFLTDestroyChn, %function
AFLTDestroyChn:
	.fnstart
.LFB882:
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
	subs	r4, r0, #0	@ inst, inst
	ldmeqfd	sp, {r3, r4, fp, sp, pc}	@
	ldr	r1, [r4, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r0, [r4, #84]	@, <variable>.hComponent
	ldr	r3, [r1, #4]	@ <variable>.DeInit, <variable>.DeInit
	blx	r3	@ <variable>.DeInit
	ldr	r1, [r4, #108]	@ D.15156, <variable>.pDMAInFifo
	cmp	r1, #0	@ D.15156,
	beq	.L14	@,
	mov	r0, #25	@,
	bl	HI_ADSP_FREE	@
	mov	r0, #0	@ tmp141,
	str	r0, [r4, #108]	@ tmp141, <variable>.pDMAInFifo
.L14:
	ldr	r0, [r4, #124]	@ D.15159, <variable>.hRingIn
	cmp	r0, #0	@ D.15159,
	bne	.L17	@,
.L15:
	ldr	r0, [r4, #92]	@ <variable>.Id, <variable>.Id
	movw	r3, #:lower16:.LANCHOR0	@ tmp143,
	movt	r3, #:upper16:.LANCHOR0	@ tmp143,
	mov	r2, #0	@ tmp146,
	mov	r1, r4	@, inst
	ldr	r3, [r3, r0, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	mov	r0, #25	@,
	ldr	ip, [r3, #12]	@ tmp145,
	bfc	ip, #29, #1	@ tmp145,,
	str	ip, [r3, #12]	@ tmp145,
	str	r2, [r3, #72]	@ tmp146, <variable>.TRY_EXE_CNT
	strh	r2, [r3, #64]	@ movhi	@ tmp146, <variable>.STATUS0.bits.frame_cnt
	strb	r2, [r3, #66]	@ tmp147, <variable>.STATUS0.bits.frame_err_cnt
	bl	HI_ADSP_FREE	@
	ldmfd	sp, {r3, r4, fp, sp, pc}	@
.L17:
	bl	RBUF_Destroy	@
	mov	r2, #0	@ tmp142,
	str	r2, [r4, #124]	@ tmp142, <variable>.hRingIn
	b	.L15	@
	.fnend
	.size	AFLTDestroyChn, .-AFLTDestroyChn
	.align	2
	.global	AFLTChnDeInit
	.type	AFLTChnDeInit, %function
AFLTChnDeInit:
	.fnstart
.LFB924:
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
	movw	r4, #:lower16:.LANCHOR0	@ tmp134,
	add	r5, r0, #8	@ tmp135, Id,
	movt	r4, #:upper16:.LANCHOR0	@ tmp134,
	ldr	r0, [r4, r5, asl #2]	@, g_stAfltRm.hAflt
	bl	AFLTDestroyChn	@
	mov	r3, #0	@ tmp139,
	str	r3, [r4, r5, asl #2]	@ tmp139, g_stAfltRm.hAflt
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	AFLTChnDeInit, .-AFLTChnDeInit
	.align	2
	.global	AFLTChnInit
	.type	AFLTChnInit, %function
AFLTChnInit:
	.fnstart
.LFB923:
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
	add	ip, r1, r0, asl #7	@, D.15777, u32AfltChnRegBase, Id,
	movw	r5, #:lower16:.LANCHOR0	@ tmp137,
	movt	r5, #:upper16:.LANCHOR0	@ tmp137,
	mov	r4, r0	@ Id, Id
	mov	r6, r1	@ u32AfltChnRegBase, u32AfltChnRegBase
	mov	r0, ip	@, D.15777
	mov	r1, #128	@,
	str	ip, [r5, r4, asl #2]	@ D.15777, g_stAfltRm.hwAfltReg
	bl	__memzero	@
	ldr	r1, [r6, r4, asl #7]	@ tmp138,* u32AfltChnRegBase
	add	r3, r4, #8	@ tmp141, Id,
	mov	r2, #0	@ tmp142,
	orr	r0, r1, #16	@ tmp143, tmp138,
	str	r0, [r6, r4, asl #7]	@ tmp143,* u32AfltChnRegBase
	str	r2, [r5, r3, asl #2]	@ tmp142, g_stAfltRm.hAflt
	ldmfd	sp, {r3, r4, r5, r6, fp, sp, pc}	@
	.fnend
	.size	AFLTChnInit, .-AFLTChnInit
	.align	2
	.global	AFLTProcChn
	.type	AFLTProcChn, %function
AFLTProcChn:
	.fnstart
.LFB922:
	@ args = 0, pretend = 0, frame = 136
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #140
	sub	sp, sp, #140	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	movw	r4, #:lower16:.LANCHOR0	@ tmp705,
	movt	r4, #:upper16:.LANCHOR0	@ tmp705,
	mov	r6, r0	@ Id, Id
	ldr	r5, [r4, r0, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r3, [r5, #0]	@ D.16901,* pAfltReg
	tst	r3, #16	@ D.16901,
	addne	r7, r0, #8	@ tmp707, Id,
	movne	r2, r5	@ pAfltReg.534, pAfltReg
	bne	.L26	@,
	ldr	r0, [r5, #0]	@ tmp321,* pAfltReg
	and	r3, r0, #15	@ D.16903, tmp321,
	cmp	r3, #13	@ D.16903,
	bls	.L96	@,
	ldr	r8, [r5, #0]	@ tmp323,* pAfltReg
	mov	ip, #4	@ tmp324,
	add	r7, r6, #8	@ tmp707, Id,
	bfi	r8, ip, #5, #4	@ tmp323, tmp324,,
	str	r8, [r5, #0]	@ tmp323,* pAfltReg
	ldr	r2, [r5, #0]	@ tmp325,* pAfltReg
	orr	r1, r2, #16	@ tmp715, tmp325,
	str	r1, [r5, #0]	@ tmp715,* pAfltReg
	ldr	r2, [r4, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
.L26:
	ldr	r3, [r4, r7, asl #2]	@ state, g_stAfltRm.hAflt
	movw	r8, #:lower16:.LANCHOR0	@ tmp541,
	movt	r8, #:upper16:.LANCHOR0	@ tmp541,
	cmp	r3, #0	@ state,
	beq	.L78	@,
	ldr	r2, [r2, #12]	@ D.16596,
	ubfx	r6, r2, #27, #1	@ tmp544, D.16596,,
	str	r6, [r3, #100]	@ tmp544, <variable>.bEosFlag
	ldr	r6, [r8, r7, asl #2]	@ state, g_stAfltRm.hAflt
	cmp	r6, #0	@ state,
	beq	.L78	@,
	ldr	r3, [r6, #0]	@ <variable>.stAttr.bMaster, <variable>.stAttr.bMaster
	cmp	r3, #0	@ <variable>.stAttr.bMaster,
	beq	.L78	@,
	ldr	r7, [r6, #96]	@ <variable>.enCurnStatus, <variable>.enCurnStatus
	cmp	r7, #0	@ <variable>.enCurnStatus,
	beq	.L107	@,
.L78:
	ldr	r1, [r5, #12]	@ D.15765,
	mov	r0, r1, lsr #31	@, D.15765,
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, pc}
.L96:
	sub	r3, r3, #1	@ tmp328, D.16903,
	cmp	r3, #12	@ tmp328,
	ldrls	pc, [pc, r3, asl #2]	@ tmp328
	b	.L27	@
.L41:
	.word	.L28
	.word	.L29
	.word	.L30
	.word	.L31
	.word	.L32
	.word	.L33
	.word	.L34
	.word	.L35
	.word	.L36
	.word	.L37
	.word	.L38
	.word	.L39
	.word	.L40
.L107:
	ldr	lr, [r6, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	sub	sl, fp, #156	@ tmp721,,
	sub	r9, fp, #48	@ tmp722,,
	mov	r0, #0	@,
	mov	r1, #0	@,
	strd	r0, [fp, #-172]	@,,
	ldr	r0, [r6, #84]	@, <variable>.hComponent
	ldr	r1, [r6, #100]	@, <variable>.bEosFlag
	ldr	r7, [lr, #56]	@ <variable>.SetEosFlag, <variable>.SetEosFlag
	blx	r7	@ <variable>.SetEosFlag
	str	r5, [fp, #-176]	@ pAfltReg, %sfp
	str	r4, [fp, #-180]	@ tmp705, %sfp
.L86:
	ldr	lr, [r6, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	mov	r1, r9	@, tmp722
	ldr	r0, [r6, #84]	@, <variable>.hComponent
	movw	r7, #:lower16:.LANCHOR0	@ tmp565,
	movt	r7, #:upper16:.LANCHOR0	@ tmp565,
	ldr	r5, [lr, #40]	@ <variable>.GetInputBytesleft, <variable>.GetInputBytesleft
	blx	r5	@ <variable>.GetInputBytesleft
	ldr	r4, [r6, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r0, [r6, #120]	@ <variable>.u32DMAInFifoReadOffset, <variable>.u32DMAInFifoReadOffset
	ldr	r1, [r6, #108]	@ <variable>.pDMAInFifo, <variable>.pDMAInFifo
	ldr	ip, [r4, #32]	@ <variable>.SetInputBuffer, <variable>.SetInputBuffer
	ldr	r2, [r6, #116]	@, <variable>.u32DMAInFifoBytesLeft
	add	r1, r1, r0	@, <variable>.pDMAInFifo, <variable>.u32DMAInFifoReadOffset
	ldr	r0, [r6, #84]	@, <variable>.hComponent
	blx	ip	@ <variable>.SetInputBuffer
	mov	r0, sl	@, tmp721
	mov	r1, #24	@,
	bl	__memzero	@
	ldr	r3, [r6, #92]	@ <variable>.Id, <variable>.Id
	ldr	r2, [fp, #-180]	@, %sfp
	ldr	r4, [r2, r3, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r5, [r4, #56]	@ D.17177, <variable>.OP_BUF_WIDX.u32
	ubfx	r0, r5, #4, #1	@ tmp574, D.17177,,
	and	r2, r5, #15	@ u32FrameIdx, D.17177,
	str	r5, [fp, #-56]	@ D.17177, OP_BUF_WIDX.u32
	ldr	r3, [r4, #60]	@ D.17176, <variable>.OP_BUF_RIDX.u32
	and	r1, r3, #15	@ tmp579, D.17176,
	ubfx	ip, r3, #4, #1	@ tmp571, D.17176,,
	subs	r4, ip, r0	@, tmp571, tmp574
	movne	r4, #1	@
	cmp	r1, r2	@ tmp579, u32FrameIdx
	str	r3, [fp, #-72]	@ D.17176, OP_BUF_RIDX.u32
	movne	r4, #0	@,,
	cmp	r4, #0	@ tmp584,
	ldrne	r5, [fp, #-176]	@ pAfltReg, %sfp
	bne	.L78	@
.L108:
	ldr	r1, [r6, #64]	@ <variable>.stAttr.u32OutbufPeriondSize, <variable>.stAttr.u32OutbufPeriondSize
	ldr	ip, [r6, #60]	@ <variable>.stAttr.u32OutbufBaseAddr, <variable>.stAttr.u32OutbufBaseAddr
	str	r2, [fp, #-156]	@ u32FrameIdx, stAdspFrame.u32FrameIndex
	mla	r0, r1, r2, ip	@ u32FrameBufAddr, <variable>.stAttr.u32OutbufPeriondSize, u32FrameIdx, <variable>.stAttr.u32OutbufBaseAddr
	add	r1, r0, #24	@, u32FrameBufAddr,
	str	r0, [fp, #-148]	@ u32FrameBufAddr, stAdspFrame.pFrameBuf
	ldr	r5, [r6, #64]	@ temp.518, <variable>.stAttr.u32OutbufPeriondSize
	sub	r2, r5, #24	@, temp.518,
	str	r5, [fp, #-144]	@ temp.518, stAdspFrame.u32FrameBufSize
	ldr	lr, [r6, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r0, [r6, #84]	@, <variable>.hComponent
	ldr	r4, [lr, #36]	@ <variable>.SetOutputBuffer, <variable>.SetOutputBuffer
	blx	r4	@ <variable>.SetOutputBuffer
	ldr	r3, [r6, #92]	@ <variable>.Id, <variable>.Id
	sub	r1, fp, #64	@,,
	ldr	ip, [r8, r3, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r2, [ip, #72]	@ Cnt, <variable>.TRY_EXE_CNT
	add	r0, r2, #1	@ D.17159, Cnt,
	str	r0, [ip, #72]	@ D.17159, <variable>.TRY_EXE_CNT
	ldr	r5, [r6, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r0, [r6, #84]	@, <variable>.hComponent
	ldr	r4, [r5, #48]	@ <variable>.ExcuteFrame, <variable>.ExcuteFrame
	blx	r4	@ <variable>.ExcuteFrame
	ldr	r3, [r6, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	ip, [r3, #40]	@ <variable>.GetInputBytesleft, <variable>.GetInputBytesleft
	mov	r4, r0	@ enRetCurn,
	mov	r5, r1	@ enRetCurn,
	ldr	r0, [r6, #84]	@, <variable>.hComponent
	sub	r1, fp, #52	@,,
	blx	ip	@ <variable>.GetInputBytesleft
	ldr	r0, [fp, #-64]	@ stExecuteFrame.u32InBytesConsumed, stExecuteFrame.u32InBytesConsumed
	ldr	r2, [fp, #-52]	@ u32CurnCompLeftBytes, u32CurnCompLeftBytes
	orrs	r1, r4, r5	@, enRetCurn
	ldr	r1, [fp, #-48]	@ u32LastCompLeftBytes, u32LastCompLeftBytes
	ldr	ip, [r6, #92]	@ <variable>.Id, <variable>.Id
	add	r3, r2, r0	@ tmp693, u32CurnCompLeftBytes, stExecuteFrame.u32InBytesConsumed
	rsb	r3, r1, r3	@ u32InFifoConsumeBytes, u32LastCompLeftBytes, tmp693
	ldr	r0, [r6, #120]	@ <variable>.u32DMAInFifoReadOffset, <variable>.u32DMAInFifoReadOffset
	ldr	r1, [r6, #116]	@ <variable>.u32DMAInFifoBytesLeft, <variable>.u32DMAInFifoBytesLeft
	add	r2, r0, r3	@ tmp698, <variable>.u32DMAInFifoReadOffset, u32InFifoConsumeBytes
	ldr	r0, [r6, #108]	@ D.17157, <variable>.pDMAInFifo
	str	r2, [r6, #120]	@ tmp698, <variable>.u32DMAInFifoReadOffset
	rsb	r3, r3, r1	@ tmp700, u32InFifoConsumeBytes, <variable>.u32DMAInFifoBytesLeft
	str	r3, [r6, #116]	@ tmp700, <variable>.u32DMAInFifoBytesLeft
	ldr	r3, [r8, ip, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	str	r0, [r3, #32]	@ D.17157, <variable>.IP_FIFO_ADDR
	ldr	ip, [r6, #112]	@ D.17156, <variable>.u32DMAInFifoSize
	str	ip, [r3, #36]	@ D.17156, <variable>.IP_FIFO_SIZE
	ldr	r2, [r6, #120]	@ D.17155, <variable>.u32DMAInFifoReadOffset
	str	r2, [r3, #40]	@ D.17155, <variable>.IP_FIFO_RPTR
	ldr	r1, [r6, #116]	@ D.17154, <variable>.u32DMAInFifoBytesLeft
	str	r1, [r3, #44]	@ D.17154, <variable>.IP_FIFO_BYTES
	beq	.L109	@,
	movw	r0, #:lower16:-2147479549	@,
	movt	r0, #:upper16:-2147479549	@,
	mvn	r1, #0	@,
	cmp	r5, r1	@ enRetCurn,
	cmpeq	r4, r0	@ enRetCurn,
	bne	.L83	@,
	ldr	r1, [r6, #92]	@ <variable>.Id, <variable>.Id
	ldr	r4, [r6, #56]	@ u32StreamReadPos, <variable>.stAttr.u32StreamReadPos
	ldr	r5, [r6, #52]	@ D.17122, <variable>.stAttr.u32InBufBoundary
	ldr	r7, [r8, r1, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	cmp	r4, r5	@ u32StreamReadPos, D.17122
	rsbcs	r4, r5, r4	@ u32StreamReadPos, D.17122, u32StreamReadPos
	str	r4, [r7, #80]	@ u32StreamReadPos, <variable>.READPOS
	movw	r7, #:lower16:.LANCHOR0	@ tmp627,
	ldr	lr, [r6, #120]	@ <variable>.u32DMAInFifoReadOffset, <variable>.u32DMAInFifoReadOffset
	movt	r7, #:upper16:.LANCHOR0	@ tmp627,
	ldr	r0, [r6, #108]	@ D.17113, <variable>.pDMAInFifo
	ldr	r2, [r6, #116]	@, <variable>.u32DMAInFifoBytesLeft
	add	r1, r0, lr	@,, <variable>.u32DMAInFifoReadOffset
	bl	memmove	@
	mov	r2, #0	@,
	str	r2, [r6, #120]	@, <variable>.u32DMAInFifoReadOffset
	ldr	r3, [r6, #92]	@ <variable>.Id, <variable>.Id
	ldr	ip, [fp, #-180]	@, %sfp
	ldr	r0, [r6, #108]	@ D.17120, <variable>.pDMAInFifo
	ldr	r1, [ip, r3, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	str	r0, [r1, #32]	@ D.17120, <variable>.IP_FIFO_ADDR
	ldr	r5, [r6, #112]	@ D.17119, <variable>.u32DMAInFifoSize
	str	r5, [r1, #36]	@ D.17119, <variable>.IP_FIFO_SIZE
	ldr	r4, [r6, #120]	@ D.17118, <variable>.u32DMAInFifoReadOffset
	str	r4, [r1, #40]	@ D.17118, <variable>.IP_FIFO_RPTR
	ldr	r2, [r6, #116]	@ D.17117, <variable>.u32DMAInFifoBytesLeft
	str	r2, [r1, #44]	@ D.17117, <variable>.IP_FIFO_BYTES
	ldr	r3, [r6, #116]	@ D.17098, <variable>.u32DMAInFifoBytesLeft
	ldr	ip, [r6, #120]	@ <variable>.u32DMAInFifoReadOffset, <variable>.u32DMAInFifoReadOffset
	ldr	r0, [r6, #108]	@ <variable>.pDMAInFifo, <variable>.pDMAInFifo
	ldr	r4, [r6, #112]	@ <variable>.u32DMAInFifoSize, <variable>.u32DMAInFifoSize
	add	r5, r3, ip	@ tmp630, D.17098, <variable>.u32DMAInFifoReadOffset
	add	r1, r5, r0	@, tmp630, <variable>.pDMAInFifo
	ldr	r0, [r6, #124]	@, <variable>.hRingIn
	rsb	r2, r3, r4	@, D.17098, <variable>.u32DMAInFifoSize
	movw	r4, #:lower16:-2147479549	@,
	bl	RBUF_ReadDataDma	@
	ldrd	r2, [fp, #-172]	@,,
	movt	r4, #:upper16:-2147479549	@,
	ldr	r1, [r6, #116]	@ <variable>.u32DMAInFifoBytesLeft, <variable>.u32DMAInFifoBytesLeft
	mvn	r5, #0	@,
	cmp	r3, r5	@,
	cmpeq	r2, r4	@,
	ldr	r2, [r6, #56]	@ <variable>.stAttr.u32StreamReadPos, <variable>.stAttr.u32StreamReadPos
	ldr	ip, [r6, #92]	@ <variable>.Id, <variable>.Id
	add	r1, r1, r0	@ tmp637, <variable>.u32DMAInFifoBytesLeft, ReadBytes
	str	r1, [r6, #116]	@ tmp637, <variable>.u32DMAInFifoBytesLeft
	add	r1, r2, r0	@ tmp639, <variable>.stAttr.u32StreamReadPos, ReadBytes
	str	r1, [r6, #56]	@ tmp639, <variable>.stAttr.u32StreamReadPos
	ldr	r5, [fp, #-180]	@, %sfp
	ldr	r2, [r6, #108]	@ D.17111, <variable>.pDMAInFifo
	ldr	r1, [r5, ip, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	str	r2, [r1, #32]	@ D.17111, <variable>.IP_FIFO_ADDR
	ldr	ip, [r6, #112]	@ D.17110, <variable>.u32DMAInFifoSize
	str	ip, [r1, #36]	@ D.17110, <variable>.IP_FIFO_SIZE
	ldr	r0, [r6, #120]	@ D.17109, <variable>.u32DMAInFifoReadOffset
	str	r0, [r1, #40]	@ D.17109, <variable>.IP_FIFO_RPTR
	ldr	r5, [r6, #116]	@ D.17108, <variable>.u32DMAInFifoBytesLeft
	str	r5, [r1, #44]	@ D.17108, <variable>.IP_FIFO_BYTES
	beq	.L85	@,
	movw	r0, #:lower16:-2147479549	@,
	mvn	r1, #0	@,
	movt	r0, #:upper16:-2147479549	@,
	strd	r0, [fp, #-172]	@,,
	b	.L86	@
.L39:
	add	r7, r6, #8	@ tmp707, Id,
	movw	r3, #:lower16:.LANCHOR0	@ tmp522,
	movt	r3, #:upper16:.LANCHOR0	@ tmp522,
	ldr	r2, [r4, r7, asl #2]	@ temp.511, g_stAfltRm.hAflt
	cmp	r2, #0	@ temp.511,
	beq	.L75	@,
	ldr	r8, [r2, #96]	@ <variable>.enCurnStatus, <variable>.enCurnStatus
	cmp	r8, #1	@ <variable>.enCurnStatus,
	bne	.L75	@,
	ldr	r1, [r2, #92]	@ <variable>.Id, <variable>.Id
	ldr	r1, [r3, r1, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	ip, [r1, #12]	@ D.16829,
	tst	ip, #67108864	@ D.16829,
	beq	.L76	@,
	ldr	r3, [r1, #48]	@ D.16831, <variable>.OP_BUF_ADDR
	cmp	r3, #0	@ D.16831,
	beq	.L75	@,
	ldr	r8, [r1, #52]	@ D.16832,
	bic	r0, r8, #-16777216	@ tmp528, D.16832,
	cmp	r0, #0	@ tmp528,
	beq	.L75	@,
	ldr	r3, [r1, #52]	@ tmp529,
	ubfx	ip, r3, #24, #4	@ D.16834, tmp529,,
	cmp	ip, #1	@ D.16834,
	ble	.L75	@,
.L76:
	ldr	r0, [r1, #48]	@ D.16841, <variable>.OP_BUF_ADDR
	mov	r3, #0	@ ack,
	str	r0, [r2, #60]	@ D.16841, <variable>.stAttr.u32OutbufBaseAddr
	ldr	r8, [r1, #52]	@ tmp671,
	ubfx	ip, r8, #0, #24	@ D.16840, tmp671,,
	str	ip, [r2, #64]	@ D.16840, <variable>.stAttr.u32OutbufPeriondSize
	ldr	r0, [r1, #52]	@ tmp672,
	ubfx	r8, r0, #24, #4	@ D.16838, tmp672,,
	str	r8, [r2, #68]	@ D.16838, <variable>.stAttr.u32OutbufPeriondNum
	ldr	r2, [r4, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	b	.L48	@
.L40:
	add	r7, r6, #8	@ tmp707, Id,
	ldr	r3, [r4, r7, asl #2]	@ temp.512, g_stAfltRm.hAflt
	cmp	r3, #0	@ temp.512,
	bne	.L110	@,
.L77:
	mov	r2, r5	@ pAfltReg.534, pAfltReg
	mov	r3, #15	@ ack,
	b	.L48	@
.L31:
	add	r7, r6, #8	@ tmp707, Id,
	movw	r8, #:lower16:.LANCHOR0	@ tmp391,
	movt	r8, #:upper16:.LANCHOR0	@ tmp391,
	ldr	r1, [r4, r7, asl #2]	@ temp.503, g_stAfltRm.hAflt
	cmp	r1, #0	@ temp.503,
	beq	.L51	@,
	ldr	r3, [r1, #96]	@ <variable>.enCurnStatus, <variable>.enCurnStatus
	cmp	r3, #1	@ <variable>.enCurnStatus,
	bne	.L51	@,
	ldr	r0, [r1, #92]	@ <variable>.Id, <variable>.Id
	ldr	r3, [r1, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r2, [r1, #8]	@, <variable>.stAttr.u32MsgPoolAddr
	ldr	ip, [r8, r0, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r3, [r3, #20]	@ <variable>.SetParameter, <variable>.SetParameter
	ldr	r0, [r1, #84]	@, <variable>.hComponent
	ldr	lr, [ip, #0]	@ D.16896, <variable>.CTRL.u32
	ubfx	r1, lr, #9, #7	@, D.16896,,
	blx	r3	@ <variable>.SetParameter
	orrs	r2, r0, r1	@,
	beq	.L60	@,
	ldr	r2, [r8, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	mov	r3, #6	@ ack,
	b	.L48	@
.L32:
	add	r7, r6, #8	@ tmp707, Id,
	movw	sl, #:lower16:.LANCHOR0	@ tmp404,
	movt	sl, #:upper16:.LANCHOR0	@ tmp404,
	ldr	r8, [r4, r7, asl #2]	@ temp.504, g_stAfltRm.hAflt
	cmp	r8, #0	@ temp.504,
	moveq	r2, r5	@ pAfltReg.534, pAfltReg
	moveq	r3, #7	@ ack,
	beq	.L48	@,
	ldr	ip, [r8, #92]	@ <variable>.Id, <variable>.Id
	sub	r3, fp, #52	@,,
	ldr	r2, [r8, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r0, [r8, #84]	@, <variable>.hComponent
	ldr	lr, [sl, ip, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	ip, [r2, #16]	@ <variable>.GetParameter, <variable>.GetParameter
	ldr	r2, [r8, #8]	@, <variable>.stAttr.u32MsgPoolAddr
	ldr	r1, [lr, #0]	@ D.16885, <variable>.CTRL.u32
	ubfx	r1, r1, #9, #7	@, D.16885,,
	blx	ip	@ <variable>.GetParameter
	orrs	r3, r0, r1	@,
	beq	.L58	@,
	ldr	r2, [sl, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	mov	r3, #7	@ ack,
	b	.L48	@
.L33:
	add	r7, r6, #8	@ tmp707, Id,
	movw	r8, #:lower16:.LANCHOR0	@ tmp424,
	movt	r8, #:upper16:.LANCHOR0	@ tmp424,
	ldr	r1, [r4, r7, asl #2]	@ temp.505, g_stAfltRm.hAflt
	cmp	r1, #0	@ temp.505,
	moveq	r2, r5	@ pAfltReg.534, pAfltReg
	moveq	r3, #8	@ ack,
	beq	.L48	@,
	ldr	r0, [r1, #92]	@ <variable>.Id, <variable>.Id
	ldr	ip, [r1, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r2, [r1, #8]	@, <variable>.stAttr.u32MsgPoolAddr
	ldr	lr, [r8, r0, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r0, [r1, #84]	@, <variable>.hComponent
	ldr	r3, [ip, #8]	@ <variable>.SetConfig, <variable>.SetConfig
	ldr	r1, [lr, #0]	@ D.16877, <variable>.CTRL.u32
	ubfx	r1, r1, #9, #7	@, D.16877,,
	blx	r3	@ <variable>.SetConfig
	orrs	r2, r0, r1	@,
	beq	.L60	@,
	ldr	r2, [r8, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	mov	r3, #8	@ ack,
	b	.L48	@
.L34:
	add	r7, r6, #8	@ tmp707, Id,
	movw	sl, #:lower16:.LANCHOR0	@ tmp436,
	movt	sl, #:upper16:.LANCHOR0	@ tmp436,
	ldr	r8, [r4, r7, asl #2]	@ temp.506, g_stAfltRm.hAflt
	cmp	r8, #0	@ temp.506,
	moveq	r2, r5	@ pAfltReg.534, pAfltReg
	moveq	r3, #9	@ ack,
	beq	.L48	@,
	ldr	ip, [r8, #92]	@ <variable>.Id, <variable>.Id
	sub	r3, fp, #52	@,,
	ldr	r2, [r8, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r0, [r8, #84]	@, <variable>.hComponent
	ldr	lr, [sl, ip, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	ip, [r2, #12]	@ <variable>.GetConfig, <variable>.GetConfig
	ldr	r2, [r8, #8]	@, <variable>.stAttr.u32MsgPoolAddr
	ldr	r1, [lr, #0]	@ D.16867, <variable>.CTRL.u32
	ubfx	r1, r1, #9, #7	@, D.16867,,
	blx	ip	@ <variable>.GetConfig
	orrs	r3, r0, r1	@,
	beq	.L58	@,
	ldr	r2, [sl, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	mov	r3, #9	@ ack,
	b	.L48	@
.L35:
	add	r7, r6, #8	@ tmp707, Id,
	movw	r8, #:lower16:.LANCHOR0	@ tmp456,
	movt	r8, #:upper16:.LANCHOR0	@ tmp456,
	ldr	r2, [r4, r7, asl #2]	@ temp.507, g_stAfltRm.hAflt
	cmp	r2, #0	@ temp.507,
	moveq	r2, r5	@ pAfltReg.534, pAfltReg
	moveq	r3, #10	@ ack,
	beq	.L48	@,
	ldr	r0, [r2, #92]	@ <variable>.Id, <variable>.Id
	ldr	lr, [r2, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r1, [r2, #8]	@, <variable>.stAttr.u32MsgPoolAddr
	ldr	ip, [r8, r0, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r3, [lr, #28]	@ <variable>.RestoreSetting, <variable>.RestoreSetting
	ldr	r0, [r2, #84]	@, <variable>.hComponent
	ldr	r2, [ip, #0]	@ D.16859, <variable>.CTRL.u32
	blx	r3	@ <variable>.RestoreSetting
	orrs	r2, r0, r1	@,
	beq	.L60	@,
	ldr	r2, [r8, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	mov	r3, #10	@ ack,
	b	.L48	@
.L36:
	add	r7, r6, #8	@ tmp707, Id,
	movw	sl, #:lower16:.LANCHOR0	@ tmp466,
	movt	sl, #:upper16:.LANCHOR0	@ tmp466,
	ldr	r8, [r4, r7, asl #2]	@ temp.508, g_stAfltRm.hAflt
	cmp	r8, #0	@ temp.508,
	moveq	r2, r5	@ pAfltReg.534, pAfltReg
	moveq	r3, #11	@ ack,
	beq	.L48	@,
	ldr	lr, [r8, #92]	@ <variable>.Id, <variable>.Id
	sub	r2, fp, #52	@,,
	ldr	r1, [r8, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r0, [r8, #84]	@, <variable>.hComponent
	ldr	r3, [sl, lr, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	ip, [r1, #24]	@ <variable>.StoreSetting, <variable>.StoreSetting
	ldr	r1, [r8, #8]	@, <variable>.stAttr.u32MsgPoolAddr
	ldr	r3, [r3, #0]	@ D.16850, <variable>.CTRL.u32
	blx	ip	@ <variable>.StoreSetting
	orrs	r3, r0, r1	@,
	beq	.L62	@,
	ldr	r2, [sl, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	mov	r3, #11	@ ack,
	b	.L48	@
.L37:
	add	r7, r6, #8	@ tmp707, Id,
	mov	r2, #0	@ tmp488,
	movw	r3, #:lower16:.LANCHOR0	@ tmp486,
	str	r2, [fp, #-52]	@ tmp488, hRingIn
	ldr	r8, [r4, r7, asl #2]	@ temp.509, g_stAfltRm.hAflt
	movt	r3, #:upper16:.LANCHOR0	@ tmp486,
	cmp	r8, r2	@ temp.509,
	beq	.L64	@,
	ldr	ip, [r8, #96]	@ <variable>.enCurnStatus, <variable>.enCurnStatus
	cmp	ip, #1	@ <variable>.enCurnStatus,
	beq	.L111	@,
.L64:
	mov	r3, #12	@ ack,
.L106:
	ldr	r2, [r4, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	b	.L48	@
.L38:
	add	r7, r6, #8	@ tmp707, Id,
	ldr	r8, [r4, r7, asl #2]	@ temp.510, g_stAfltRm.hAflt
	cmp	r8, #0	@ temp.510,
	beq	.L72	@,
	ldr	r1, [r8, #96]	@ <variable>.enCurnStatus, <variable>.enCurnStatus
	cmp	r1, #1	@ <variable>.enCurnStatus,
	bne	.L72	@,
	ldr	r1, [r8, #108]	@ D.16843, <variable>.pDMAInFifo
	cmp	r1, #0	@ D.16843,
	beq	.L73	@,
	mov	r0, #25	@,
	bl	HI_ADSP_FREE	@
	mov	r0, #0	@ tmp518,
	str	r0, [r8, #108]	@ tmp518, <variable>.pDMAInFifo
.L73:
	ldr	r3, [r8, #124]	@ D.16844, <variable>.hRingIn
	cmp	r3, #0	@ D.16844,
	beq	.L106	@,
	mov	r0, r3	@, D.16844
	bl	RBUF_Destroy	@
	mov	r3, #0	@ tmp520,
	str	r3, [r8, #124]	@ tmp520, <variable>.hRingIn
	ldr	r2, [r4, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	b	.L48	@
.L27:
	sub	r9, fp, #156	@ tmp708,,
	mov	r1, #84	@,
	mov	r0, r9	@, tmp708
	bl	__memzero	@
	ldr	r3, [r4, r6, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r7, [r3, #4]	@ D.16956, <variable>.MSGPOOL_ADDR
	cmp	r7, #0	@ D.16956,
	beq	.L42	@,
	ldrh	lr, [r3, #12]	@ <variable>.ATTR.bits.msgpool_size, <variable>.ATTR.bits.msgpool_size
	cmp	lr, #0	@ <variable>.ATTR.bits.msgpool_size,
	beq	.L42	@,
	ldr	r0, [r3, #12]	@ tmp661,
	ubfx	r2, r0, #26, #1	@ D.16944, tmp661,,
	str	r2, [fp, #-156]	@ D.16944, stAttr.bMaster
	ldrb	ip, [r3, #14]	@ zero_extendqisi2	@ <variable>.ATTR.bits.filter_id, <variable>.ATTR.bits.filter_id
	str	ip, [fp, #-152]	@ <variable>.ATTR.bits.filter_id, stAttr.enComType
	ldr	lr, [r3, #4]	@ D.16948, <variable>.MSGPOOL_ADDR
	str	lr, [fp, #-148]	@ D.16948, stAttr.u32MsgPoolAddr
	ldrh	r7, [r3, #12]	@ <variable>.ATTR.bits.msgpool_size, <variable>.ATTR.bits.msgpool_size
	str	r7, [fp, #-144]	@ <variable>.ATTR.bits.msgpool_size, stAttr.u32MsgPoolSize
	ldr	r8, [r3, #96]	@ D.16951, <variable>.AUTH_KEY
	ands	r3, r8, #1	@ tmp667, D.16951,
	movne	r3, #1	@ tmp333,
	strne	r3, [fp, #-84]	@ tmp333, stAttr.bAuthorize
	streq	r3, [fp, #-84]	@ tmp667, stAttr.bAuthorize
.L44:
	mov	r0, #25	@,
	mov	r1, #128	@,
	bl	HI_ADSP_MALLOC	@
	subs	r8, r0, #0	@ state,
	beq	.L42	@,
	mov	r1, #128	@,
	bl	__memzero	@
	ldr	r3, [fp, #-156]	@ stAttr.bMaster, stAttr.bMaster
	ldr	r2, [r4, r6, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	cmp	r3, #1	@ stAttr.bMaster,
	beq	.L45	@,
.L105:
	ldr	r3, [fp, #-152]	@ prephitmp.488, stAttr.enComType
.L46:
	cmp	r3, #6	@ prephitmp.488,
	bhi	.L47	@,
	movw	r2, #:lower16:.LANCHOR1	@ tmp339,
	movt	r2, #:upper16:.LANCHOR1	@ tmp339,
	ldr	r7, [r2, r3, asl #2]	@ ExeApi, CSWTCH.310
	cmp	r7, #0	@ ExeApi,
	beq	.L47	@,
	ldr	sl, [r7, #0]	@ <variable>.Init, <variable>.Init
	add	r0, r8, #84	@, state,
	blx	sl	@ <variable>.Init
	subs	sl, r0, #0	@ D.16958,
	beq	.L112	@,
.L47:
	mov	r1, r8	@, state
	mov	r0, #25	@,
	bl	HI_ADSP_FREE	@
.L42:
	ldr	r2, [r4, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	add	r7, r6, #8	@ tmp707, Id,
	mov	r3, #0	@ tmp361,
	movw	r1, #:lower16:.LANCHOR0	@ tmp359,
	str	r3, [r4, r7, asl #2]	@ tmp361, g_stAfltRm.hAflt
	movt	r1, #:upper16:.LANCHOR0	@ tmp359,
	ldr	r8, [r2, #0]	@ D.16899,* pAfltReg.534
	ands	r0, r8, #16	@ tmp363, D.16899,
	bne	.L48	@,
	ldr	r8, [r2, #0]	@ tmp364,* pAfltReg.534
	mov	r3, r0	@ ack, tmp363
	mov	r0, #3	@ tmp365,
	bfi	r8, r0, #5, #4	@ tmp364, tmp365,,
	str	r8, [r2, #0]	@ tmp364,* pAfltReg.534
	ldr	ip, [r2, #0]	@ tmp366,* pAfltReg.534
	orr	lr, ip, #16	@ tmp718, tmp366,
	str	lr, [r2, #0]	@ tmp718,* pAfltReg.534
	ldr	r2, [r1, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	b	.L48	@
.L28:
	add	r7, r6, #8	@ tmp707, Id,
	ldr	r0, [r4, r7, asl #2]	@, g_stAfltRm.hAflt
	bl	AFLTDestroyChn	@
	mov	r2, #0	@ tmp374,
	mov	r3, r2	@ ack, tmp374
	str	r2, [r4, r7, asl #2]	@ tmp374, g_stAfltRm.hAflt
	ldr	r2, [r4, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
.L48:
	ldr	r1, [r2, #0]	@ D.16821,* pAfltReg.534
	tst	r1, #16	@ D.16821,
	bne	.L26	@,
	ldr	ip, [r2, #0]	@ tmp537,* pAfltReg.534
	bfi	ip, r3, #5, #4	@ tmp537, ack,,
	str	ip, [r2, #0]	@ tmp537,* pAfltReg.534
	ldr	r8, [r2, #0]	@ tmp538,* pAfltReg.534
	orr	r0, r8, #16	@ tmp720, tmp538,
	str	r0, [r2, #0]	@ tmp720,* pAfltReg.534
	ldr	r2, [r4, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	b	.L26	@
.L29:
	add	r7, r6, #8	@ tmp707, Id,
	movw	r2, #:lower16:.LANCHOR0	@ tmp376,
	movt	r2, #:upper16:.LANCHOR0	@ tmp376,
	ldr	r1, [r4, r7, asl #2]	@ temp.501, g_stAfltRm.hAflt
	cmp	r1, #0	@ temp.501,
	bne	.L113	@,
.L50:
	mov	r2, r5	@ pAfltReg.534, pAfltReg
	mov	r3, #0	@ ack,
	b	.L48	@
.L30:
	add	r7, r6, #8	@ tmp707, Id,
	movw	r2, #:lower16:.LANCHOR0	@ tmp384,
	movt	r2, #:upper16:.LANCHOR0	@ tmp384,
	ldr	r1, [r4, r7, asl #2]	@ temp.502, g_stAfltRm.hAflt
	cmp	r1, #0	@ temp.502,
	beq	.L50	@,
	ldr	r0, [r1, #92]	@ <variable>.Id, <variable>.Id
	mov	ip, #1	@ tmp388,
	mov	r3, #0	@ ack,
	ldr	r8, [r2, r0, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	str	ip, [r1, #96]	@ tmp388, <variable>.enCurnStatus
	ldr	r1, [r8, #12]	@ tmp389,
	bfc	r1, #30, #1	@ tmp389,,
	str	r1, [r8, #12]	@ tmp389,
	ldr	r2, [r2, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	b	.L48	@
.L75:
	mov	r2, r5	@ pAfltReg.534, pAfltReg
	mov	r3, #14	@ ack,
	b	.L48	@
.L85:
	ldr	r0, [r6, #100]	@ <variable>.bEosFlag, <variable>.bEosFlag
	ldr	r5, [fp, #-176]	@ pAfltReg, %sfp
	cmp	r0, #1	@ <variable>.bEosFlag,
	bne	.L78	@,
	ldr	lr, [r6, #92]	@ <variable>.Id, <variable>.Id
	ldr	r3, [r7, lr, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r2, [r3, #12]	@ tmp646,
	orr	ip, r2, #268435456	@ tmp723, tmp646,
	str	ip, [r3, #12]	@ tmp723,
	b	.L78	@
.L51:
	mov	r2, r5	@ pAfltReg.534, pAfltReg
	mov	r3, #6	@ ack,
	b	.L48	@
.L72:
	mov	r2, r5	@ pAfltReg.534, pAfltReg
	mov	r3, #13	@ ack,
	b	.L48	@
.L110:
	ldr	r2, [r3, #96]	@ <variable>.enCurnStatus, <variable>.enCurnStatus
	cmp	r2, #1	@ <variable>.enCurnStatus,
	bne	.L77	@,
	b	.L50	@
.L113:
	ldr	r0, [r1, #92]	@ <variable>.Id, <variable>.Id
	mov	ip, #0	@ tmp380,
	mov	r3, ip	@ ack, tmp380
	ldr	r8, [r2, r0, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	str	ip, [r1, #96]	@ tmp380, <variable>.enCurnStatus
	ldr	ip, [r8, #12]	@ tmp381,
	orr	r1, ip, #1073741824	@ tmp719, tmp381,
	str	r1, [r8, #12]	@ tmp719,
	ldr	r2, [r2, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	b	.L48	@
.L111:
	ldr	r0, [r8, #92]	@ <variable>.Id, <variable>.Id
	ldr	r3, [r3, r0, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r1, [r3, #12]	@ D.17013,
	tst	r1, #67108864	@ D.17013,
	beq	.L65	@,
	ldr	r2, [r3, #16]	@ D.17011, <variable>.IP_BUF_ADDR
	cmp	r2, #0	@ D.17011,
	beq	.L64	@,
	ldr	r1, [r3, #20]	@ D.17010,
	bic	ip, r1, #-268435456	@ tmp493, D.17010,
	cmp	ip, #0	@ tmp493,
	beq	.L64	@,
	ldr	r0, [r3, #20]	@ D.17008,
	tst	r0, #268435456	@ D.17008,
	beq	.L66	@,
	ldr	r2, [r3, #24]	@ D.17006, <variable>.IP_BUF_WPTR
	cmp	r2, #0	@ D.17006,
	beq	.L64	@,
	ldr	ip, [r3, #28]	@ D.17005, <variable>.IP_BUF_RPTR
	cmp	ip, #0	@ D.17005,
	beq	.L64	@,
.L66:
	ldr	r1, [r3, #8]	@ D.17004, <variable>.IPBUF_BOUNDARY
	ldr	r2, [r3, #20]	@ tmp495,
	ubfx	r0, r2, #0, #28	@ D.17003, tmp495,,
	cmp	r1, r0	@ D.17004, D.17003
	bcc	.L64	@,
.L65:
	mov	r2, #1	@ tmp668,
	str	r2, [r8, #16]	@ tmp668, <variable>.stAttr.stRbfInAttr.bExtMem
	ldr	ip, [r3, #16]	@ D.16985, <variable>.IP_BUF_ADDR
	str	ip, [r8, #20]	@ D.16985, <variable>.stAttr.stRbfInAttr.uBufAddr
	ldr	lr, [r3, #20]	@ tmp669,
	ubfx	r1, lr, #0, #28	@ D.16986, tmp669,,
	str	r1, [r8, #24]	@ D.16986, <variable>.stAttr.stRbfInAttr.uBufSize
	ldr	sl, [r3, #20]	@ D.16988,
	tst	sl, #268435456	@ D.16988,
	beq	.L114	@,
	ldr	lr, [r3, #24]	@ D.16990, <variable>.IP_BUF_WPTR
	str	lr, [r8, #28]	@ D.16990, <variable>.stAttr.stRbfInAttr.uBufWptr
	ldr	sl, [r3, #28]	@ D.16991, <variable>.IP_BUF_RPTR
	str	sl, [r8, #32]	@ D.16991, <variable>.stAttr.stRbfInAttr.uBufRptr
.L67:
	ldr	r1, [r8, #24]	@ <variable>.stAttr.stRbfInAttr.uBufSize, <variable>.stAttr.stRbfInAttr.uBufSize
	mov	sl, #0	@ tmp499,
	ldr	ip, [r3, #20]	@ tmp496,
	mov	r0, #1	@ tmp498,
	str	sl, [r8, #48]	@ tmp499, <variable>.stAttr.stRbfInAttr.uLatencyMs
	str	r0, [r8, #40]	@ tmp498, <variable>.stAttr.stRbfInAttr.uFrameSize
	ubfx	lr, ip, #28, #1	@ D.16996, tmp496,,
	str	r1, [r8, #44]	@ <variable>.stAttr.stRbfInAttr.uBufSize, <variable>.stAttr.stRbfInAttr.uLatencySize
	sub	r0, fp, #52	@,,
	str	lr, [r8, #36]	@ D.16996, <variable>.stAttr.stRbfInAttr.uBufFlag
	add	r1, r8, #16	@, temp.509,
	ldr	r2, [r3, #8]	@ D.16999, <variable>.IPBUF_BOUNDARY
	str	r2, [r8, #52]	@ D.16999, <variable>.stAttr.u32InBufBoundary
	ldr	r3, [r3, #80]	@ D.17000, <variable>.READPOS
	str	r3, [r8, #56]	@ D.17000, <variable>.stAttr.u32StreamReadPos
	bl	RBUF_Create	@
	ldr	r3, [fp, #-52]	@ hRingIn.274, hRingIn
	cmp	r3, sl	@ hRingIn.274,
	bne	.L115	@,
.L68:
	ldr	r1, [r8, #108]	@ D.17016, <variable>.pDMAInFifo
	cmp	r1, #0	@ D.17016,
	beq	.L71	@,
	mov	r0, #25	@,
	bl	HI_ADSP_FREE	@
	mov	r3, #0	@ tmp512,
	str	r3, [r8, #108]	@ tmp512, <variable>.pDMAInFifo
.L71:
	ldr	r0, [r8, #124]	@ D.17015, <variable>.hRingIn
	cmp	r0, #0	@ D.17015,
	beq	.L64	@,
	bl	RBUF_Destroy	@
	mov	r2, #0	@ tmp513,
	mov	r3, #12	@ ack,
	str	r2, [r8, #124]	@ tmp513, <variable>.hRingIn
	ldr	r2, [r4, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	b	.L48	@
.L45:
	ldr	r3, [fp, #-152]	@ prephitmp.488, stAttr.enComType
	cmp	r3, #2	@ prephitmp.488,
	bhi	.L46	@,
	ldr	r1, [r2, #12]	@ tmp337,
	orr	r0, r1, #-2147483648	@ tmp716, tmp337,
	str	r0, [r2, #12]	@ tmp716,
	b	.L105	@
.L83:
	ldr	r1, [r6, #56]	@ u32StreamReadPos, <variable>.stAttr.u32StreamReadPos
	ldr	r0, [fp, #-52]	@ u32CurnCompLeftBytes, u32CurnCompLeftBytes
	ldr	r2, [r6, #116]	@ <variable>.u32DMAInFifoBytesLeft, <variable>.u32DMAInFifoBytesLeft
	rsb	ip, r0, r1	@ u32StreamReadPos.539, u32CurnCompLeftBytes, u32StreamReadPos
	ldr	r0, [r6, #92]	@ <variable>.Id, <variable>.Id
	ldr	r3, [fp, #-64]	@ stExecuteFrame.u32InBytesConsumed, stExecuteFrame.u32InBytesConsumed
	rsb	lr, r2, ip	@ u32StreamReadPos.540, <variable>.u32DMAInFifoBytesLeft, u32StreamReadPos.539
	ldr	r2, [r6, #52]	@ D.17094, <variable>.stAttr.u32InBufBoundary
	rsb	ip, r3, lr	@ u32StreamReadPos.541, stExecuteFrame.u32InBytesConsumed, u32StreamReadPos.540
	ldr	lr, [r7, r0, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	cmp	ip, r2	@ u32StreamReadPos.541, D.17094
	ldr	r4, [fp, #-180]	@ tmp705, %sfp
	rsbcs	ip, r2, ip	@ u32StreamReadPos.541, D.17094, u32StreamReadPos.541
	ldr	r5, [fp, #-176]	@ pAfltReg, %sfp
	rsbcs	r2, r2, r1	@ tmp653, D.17094, u32StreamReadPos
	strcs	r2, [r6, #56]	@ tmp653, <variable>.stAttr.u32StreamReadPos
	str	ip, [lr, #80]	@ u32StreamReadPos.541, <variable>.READPOS
	ldr	r3, [r6, #92]	@ <variable>.Id, <variable>.Id
	ldr	r0, [r4, r3, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldrb	r2, [r0, #66]	@ zero_extendqisi2	@ <variable>.STATUS0.bits.frame_err_cnt, <variable>.STATUS0.bits.frame_err_cnt
	add	ip, r2, #1	@ tmp658, <variable>.STATUS0.bits.frame_err_cnt,
	uxtb	r1, ip	@ D.17092, tmp658
	strb	r1, [r0, #66]	@ D.17092, <variable>.STATUS0.bits.frame_err_cnt
	b	.L78	@
.L60:
	ldr	r2, [r8, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	mov	r3, #0	@ ack,
	b	.L48	@
.L58:
	ldr	lr, [r8, #92]	@ <variable>.Id, <variable>.Id
	mov	r3, #0	@ ack,
	ldr	r0, [fp, #-52]	@ u32ConfigStructureSize,
	ldr	r1, [sl, lr, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r8, [r1, #0]	@ tmp454,* pAfltReg
	bfi	r8, r0, #16, #13	@ tmp454, u32ConfigStructureSize,,
	str	r8, [r1, #0]	@ tmp454,* pAfltReg
	ldr	r2, [sl, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	b	.L48	@
.L109:
	ldr	r1, [r6, #56]	@ u32StreamReadPos, <variable>.stAttr.u32StreamReadPos
	ldr	lr, [fp, #-52]	@ u32CurnCompLeftBytes, u32CurnCompLeftBytes
	ldr	r2, [r6, #116]	@ <variable>.u32DMAInFifoBytesLeft, <variable>.u32DMAInFifoBytesLeft
	rsb	ip, lr, r1	@ u32StreamReadPos.528, u32CurnCompLeftBytes, u32StreamReadPos
	ldr	lr, [r6, #92]	@ <variable>.Id, <variable>.Id
	ldr	r3, [fp, #-64]	@ stExecuteFrame.u32InBytesConsumed, stExecuteFrame.u32InBytesConsumed
	rsb	r0, r2, ip	@ u32StreamReadPos.529, <variable>.u32DMAInFifoBytesLeft, u32StreamReadPos.528
	ldr	r2, [r6, #52]	@ D.17146, <variable>.stAttr.u32InBufBoundary
	ldr	ip, [r7, lr, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	rsb	r3, r3, r0	@ u32StreamReadPos.530, stExecuteFrame.u32InBytesConsumed, u32StreamReadPos.529
	cmp	r3, r2	@ u32StreamReadPos.530, D.17146
	ldr	r4, [fp, #-180]	@ tmp705, %sfp
	rsbcs	r3, r2, r3	@ u32StreamReadPos.530, D.17146, u32StreamReadPos.530
	ldr	r5, [fp, #-176]	@ pAfltReg, %sfp
	rsbcs	r2, r2, r1	@ tmp590, D.17146, u32StreamReadPos
	strcs	r2, [r6, #56]	@ tmp590, <variable>.stAttr.u32StreamReadPos
	str	r3, [ip, #80]	@ u32StreamReadPos.530, <variable>.READPOS
	sub	r1, fp, #72	@,,
	ldr	r2, [fp, #-60]	@ D.17144, stExecuteFrame.u32OutDataBytesProduced
	ldr	r0, [fp, #-144]	@ stAdspFrame.u32FrameBufSize, stAdspFrame.u32FrameBufSize
	str	r3, [fp, #-152]	@ u32StreamReadPos.530, stAdspFrame.u32PtsReadPos
	add	lr, r2, #24	@ tmp591, D.17144,
	ldr	r3, [fp, #-148]	@ stAdspFrame.pFrameBuf, stAdspFrame.pFrameBuf
	sub	ip, r0, #24	@ tmp594, stAdspFrame.u32FrameBufSize,
	str	r2, [fp, #-140]	@ D.17144, stAdspFrame.u32FrameDataBytes
	add	r0, r3, lr	@ tmp593, stAdspFrame.pFrameBuf, tmp591
	rsb	r3, r2, ip	@ tmp596, D.17144, tmp594
	str	r0, [fp, #-72]	@ tmp593, stFramePrivInfo.pOutPrivInfo
	str	r3, [fp, #-68]	@ tmp596, stFramePrivInfo.u32OutPrivBytesProduced
	ldr	lr, [r6, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	ldr	r0, [r6, #84]	@, <variable>.hComponent
	ldr	r2, [lr, #52]	@ <variable>.GetCurnFramePrivInfo, <variable>.GetCurnFramePrivInfo
	blx	r2	@ <variable>.GetCurnFramePrivInfo
	ldr	ip, [fp, #-68]	@ stFramePrivInfo.u32OutPrivBytesProduced, stFramePrivInfo.u32OutPrivBytesProduced
	mov	r1, sl	@, tmp721
	mov	r2, #24	@,
	ldr	r0, [fp, #-148]	@, stAdspFrame.pFrameBuf
	str	ip, [fp, #-136]	@ stFramePrivInfo.u32OutPrivBytesProduced, stAdspFrame.u32FramePrivBytes
	bl	memcpy	@
	ldr	r3, [r6, #92]	@ <variable>.Id, <variable>.Id
	ldr	ip, [r6, #68]	@ <variable>.stAttr.u32OutbufPeriondNum, <variable>.stAttr.u32OutbufPeriondNum
	ldr	r1, [r4, r3, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r3, [r1, #56]	@ OP_BUF_WIDX, <variable>.OP_BUF_WIDX.u32
	and	r0, r3, #15	@ WriteIdx, OP_BUF_WIDX,
	ubfx	r2, r3, #4, #1	@ WriteWrap, OP_BUF_WIDX,,
	add	r0, r0, #1	@ WriteIdx.533, WriteIdx,
	cmp	r0, ip	@ WriteIdx.533, <variable>.stAttr.u32OutbufPeriondNum
	eorcs	r2, r2, #1	@ WriteWrap, WriteWrap,
	andcc	r0, r0, #15	@ prephitmp.484, WriteIdx.533,
	bfi	r3, r2, #4, #1	@ OP_BUF_WIDX, WriteWrap,,
	movcs	r0, #0	@ prephitmp.484,
	bfi	r3, r0, #0, #4	@ OP_BUF_WIDX, prephitmp.484,,
	str	r3, [r1, #56]	@ OP_BUF_WIDX, <variable>.OP_BUF_WIDX.u32
	ldr	r0, [r6, #92]	@ <variable>.Id, <variable>.Id
	ldr	r3, [r4, r0, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldrh	r1, [r3, #64]	@ <variable>.STATUS0.bits.frame_cnt, <variable>.STATUS0.bits.frame_cnt
	add	ip, r1, #1	@ tmp619, <variable>.STATUS0.bits.frame_cnt,
	uxth	r2, ip	@ D.17125, tmp619
	strh	r2, [r3, #64]	@ movhi	@ D.17125, <variable>.STATUS0.bits.frame_cnt
	b	.L78	@
.L62:
	ldr	r0, [r8, #92]	@ <variable>.Id, <variable>.Id
	ldr	r1, [fp, #-52]	@ u32SettingStructureSize, u32SettingStructureSize
	ldr	r3, [sl, r0, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	lr, [r3, #0]	@ tmp482,* pAfltReg
	bfi	lr, r1, #16, #13	@ tmp482, u32SettingStructureSize,,
	str	lr, [r3, #0]	@ tmp482,* pAfltReg
	ldr	ip, [r8, #92]	@ <variable>.Id, <variable>.Id
	mov	r3, #0	@ ack,
	ldr	r2, [r8, #52]	@ D.16854, <variable>.stAttr.u32InBufBoundary
	ldr	r0, [r8, #56]	@ u32StreamReadPos, <variable>.stAttr.u32StreamReadPos
	ldr	r8, [sl, ip, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	cmp	r0, r2	@ u32StreamReadPos, D.16854
	rsbcs	r0, r2, r0	@ u32StreamReadPos, D.16854, u32StreamReadPos
	str	r0, [r8, #80]	@ u32StreamReadPos, <variable>.READPOS
	ldr	r2, [r4, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	b	.L48	@
.L112:
	mov	r1, r9	@, tmp708
	mov	r2, #84	@,
	str	r6, [r8, #92]	@ Id, <variable>.Id
	mov	r0, r8	@, state
	bl	memcpy	@
	str	r7, [r8, #88]	@ ExeApi, <variable>.hExeAPI
	str	sl, [r8, #100]	@ D.16958, <variable>.bEosFlag
	mov	r7, #1	@ tmp347,
	str	r7, [r8, #96]	@ tmp347, <variable>.enCurnStatus
	add	r7, r6, #8	@ tmp707, Id,
	ldr	r1, [r5, #12]	@ tmp349,
	mov	r3, sl	@ ack, D.16958
	orr	r0, r1, #536870912	@ tmp717, tmp349,
	str	r0, [r5, #12]	@ tmp717,
	str	sl, [r5, #72]	@ D.16958, <variable>.TRY_EXE_CNT
	strh	sl, [r5, #64]	@ movhi	@ D.16958, <variable>.STATUS0.bits.frame_cnt
	strb	sl, [r5, #66]	@ D.16958, <variable>.STATUS0.bits.frame_err_cnt
	str	r8, [r4, r7, asl #2]	@ state, g_stAfltRm.hAflt
	ldr	r2, [r4, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	b	.L48	@
.L114:
	add	r1, r3, #24	@ D.16992, pAfltReg,
	add	ip, r3, #28	@ D.16994, pAfltReg,
	str	r1, [r8, #28]	@ D.16992, <variable>.stAttr.stRbfInAttr.uBufWptr
	str	ip, [r8, #32]	@ D.16994, <variable>.stAttr.stRbfInAttr.uBufRptr
	b	.L67	@
.L115:
	ldr	r2, [r8, #0]	@ <variable>.stAttr.bMaster, <variable>.stAttr.bMaster
	str	r3, [r8, #124]	@ hRingIn.274, <variable>.hRingIn
	cmp	r2, #1	@ <variable>.stAttr.bMaster,
	movne	r3, sl	@ ack, tmp499
	bne	.L106	@,
	ldr	lr, [r8, #88]	@ <variable>.hExeAPI, <variable>.hExeAPI
	sub	r1, fp, #48	@,,
	ldr	r0, [r8, #84]	@, <variable>.hComponent
	ldr	r3, [lr, #44]	@ <variable>.GetMinInputBufSize, <variable>.GetMinInputBufSize
	blx	r3	@ <variable>.GetMinInputBufSize
	orrs	r2, r0, r1	@,
	bne	.L68	@,
	mov	r0, #25	@,
	ldr	r1, [fp, #-48]	@, u32DMAInFifoSize
	bl	HI_ADSP_MALLOC	@
	cmp	r0, #0	@ D.17017,
	str	r0, [r8, #108]	@ D.17017, <variable>.pDMAInFifo
	beq	.L71	@,
	ldr	ip, [fp, #-48]	@ u32DMAInFifoSize, u32DMAInFifoSize
	mov	r3, sl	@ ack, tmp499
	ldr	lr, [r8, #92]	@ <variable>.Id, <variable>.Id
	str	sl, [r8, #120]	@ tmp499, <variable>.u32DMAInFifoReadOffset
	str	ip, [r8, #112]	@ u32DMAInFifoSize, <variable>.u32DMAInFifoSize
	str	sl, [r8, #116]	@ tmp499, <variable>.u32DMAInFifoBytesLeft
	ldr	r2, [r4, lr, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	str	r0, [r2, #32]	@ D.17017, <variable>.IP_FIFO_ADDR
	ldr	r0, [r8, #112]	@ D.16982, <variable>.u32DMAInFifoSize
	str	r0, [r2, #36]	@ D.16982, <variable>.IP_FIFO_SIZE
	ldr	r1, [r8, #120]	@ D.16983, <variable>.u32DMAInFifoReadOffset
	str	r1, [r2, #40]	@ D.16983, <variable>.IP_FIFO_RPTR
	ldr	ip, [r8, #116]	@ D.16984, <variable>.u32DMAInFifoBytesLeft
	str	ip, [r2, #44]	@ D.16984, <variable>.IP_FIFO_BYTES
	ldr	r2, [r4, r6, asl #2]	@ pAfltReg.534, g_stAfltRm.hwAfltReg
	b	.L48	@
	.fnend
	.size	AFLTProcChn, .-AFLTProcChn
	.align	2
	.global	AFLTFlushInbuf
	.type	AFLTFlushInbuf, %function
AFLTFlushInbuf:
	.fnstart
.LFB883:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}	@,
	.pad #4
	.save {r4, r5, fp, ip, lr}
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
	.pad #40
	sub	sp, sp, #40	@,,
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r4, r0	@ state, state
	ldr	r0, [r0, #124]	@ D.15169, <variable>.hRingIn
	movw	r3, #:lower16:.LANCHOR0	@ tmp137,
	ldr	r2, [r4, #92]	@ <variable>.Id, <variable>.Id
	movt	r3, #:upper16:.LANCHOR0	@ tmp137,
	cmp	r0, #0	@ D.15169,
	ldr	r5, [r3, r2, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	beq	.L117	@,
	sub	r1, fp, #56	@,,
	bl	RBUF_QueryInfo	@
	ldr	r0, [r4, #124]	@, <variable>.hRingIn
	ldr	r1, [fp, #-36]	@, stRbfIn.u32TotalDataSize
	bl	RBUF_ReadDataComplete	@
.L117:
	ldr	r0, [r5, #80]	@ D.15173, <variable>.READPOS
	str	r0, [r4, #56]	@ D.15173, <variable>.stAttr.u32StreamReadPos
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
	.fnend
	.size	AFLTFlushInbuf, .-AFLTFlushInbuf
	.align	2
	.global	AFLTFlushChn
	.type	AFLTFlushChn, %function
AFLTFlushChn:
	.fnstart
.LFB886:
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
	tst	r1, #1	@ type,
	mov	r4, r1	@ type, type
	mov	r5, r0	@ state, state
	bne	.L124	@,
	tst	r4, #2	@ type,
	movne	r3, #0	@ tmp144,
	strne	r3, [r5, #116]	@ tmp144, <variable>.u32DMAInFifoBytesLeft
	strne	r3, [r5, #120]	@ tmp144, <variable>.u32DMAInFifoReadOffset
	tst	r4, #4	@ type,
	ldmeqfd	sp, {r4, r5, fp, sp, pc}	@
.L125:
	ldr	ip, [r5, #92]	@ <variable>.Id, <variable>.Id
	movw	r0, #:lower16:.LANCHOR0	@ tmp147,
	movt	r0, #:upper16:.LANCHOR0	@ tmp147,
	ldr	r3, [r0, ip, asl #2]	@ pAfltReg, g_stAfltRm.hwAfltReg
	ldr	r1, [r3, #56]	@ D.16607, <variable>.OP_BUF_WIDX.u32
	ldr	r2, [r3, #60]	@ D.16606, <variable>.OP_BUF_RIDX.u32
	bfc	r1, #0, #4	@ OP_BUF_WIDX,,
	bfc	r2, #0, #4	@ OP_BUF_RIDX,,
	bfc	r1, #4, #1	@ OP_BUF_WIDX,,
	bfc	r2, #4, #1	@ OP_BUF_RIDX,,
	str	r1, [r3, #56]	@ OP_BUF_WIDX, <variable>.OP_BUF_WIDX.u32
	str	r2, [r3, #60]	@ OP_BUF_RIDX, <variable>.OP_BUF_RIDX.u32
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
.L124:
	bl	AFLTFlushInbuf	@
	tst	r4, #2	@ type,
	movne	r3, #0	@ tmp144,
	strne	r3, [r5, #116]	@ tmp144, <variable>.u32DMAInFifoBytesLeft
	strne	r3, [r5, #120]	@ tmp144, <variable>.u32DMAInFifoReadOffset
	tst	r4, #4	@ type,
	bne	.L125	@,
	ldmfd	sp, {r4, r5, fp, sp, pc}	@
	.fnend
	.size	AFLTFlushChn, .-AFLTFlushChn
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	CSWTCH.310, %object
	.size	CSWTCH.310, 28
CSWTCH.310:
	.word	g_stComponentBaseAudioEffect
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	g_stComponentPcmDecoder
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_stAfltRm, %object
	.size	g_stAfltRm, 64
g_stAfltRm:
	.space	64
	.ident	"GCC: (Hisilicon_v200(gcc4.4-290+glibc-2.11+eabi+nptl)) 4.4.1"
	.section	.note.GNU-stack,"",%progbits
