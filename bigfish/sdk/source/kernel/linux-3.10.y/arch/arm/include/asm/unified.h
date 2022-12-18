/*
 * include/asm-arm/unified.h - Unified Assembler Syntax helper macros
 *
 * Copyright (C) 2008 ARM Limited
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef __ASM_UNIFIED_H
#define __ASM_UNIFIED_H

#if defined(__ASSEMBLY__) && defined(CONFIG_ARM_ASM_UNIFIED)
	.syntax unified
#endif

#ifdef CONFIG_THUMB2_KERNEL

#if __GNUC__ < 4
#error Thumb-2 kernel requires gcc >= 4
#endif

/* The CPSR bit describing the instruction set (Thumb) */
#define PSR_ISETSTATE	PSR_T_BIT

#define ARM(x...)
#define THUMB(x...)	x
#ifdef __ASSEMBLY__
#define W(instr)	instr.w
#define BSYM(sym)	sym + 1
#endif

#else	/* !CONFIG_THUMB2_KERNEL */

/* The CPSR bit describing the instruction set (ARM) */
#define PSR_ISETSTATE	0

#define ARM(x...)	x
#define THUMB(x...)
#ifdef __ASSEMBLY__
#define W(instr)	instr
#define BSYM(sym)	sym
#endif

#endif	/* CONFIG_THUMB2_KERNEL */

#endif	/* !__ASM_UNIFIED_H */
