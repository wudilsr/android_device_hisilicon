
#ifndef __SRE_SECURITYCPU_H
#define __SRE_SECURITYCPU_H

#include "sre_base.h"

#define SCTLR_M     0x00000001  /* MMU bit        */
#define SCTLR_C     (1 << 2)    /* Dcache enable      */
#define SCTLR_I     (1 << 12)   /* Icache enable      */
#define SCTLR_Z     (1 << 11)   /* Branch prediction enable      */


INLINE  UINT32 get_mpid()
{
	UINT32  rval;

	__asm__ __volatile__ (
                "mrc     p15, 0, %0, c0, c0, 5"
                :"=r"(rval));

	return  rval;
}

INLINE  UINT32 read_sctlr()
{
	UINT32  rval;

	__asm__ __volatile__ (
                "mrc     p15, 0, %0, c1, c0, 0"
                :"=r"(rval));

	return  rval;
}

INLINE  VOID write_sctlr(UINT32 val)
{
	__asm__ __volatile__ (
                "mcr     p15, 0, %0, c1, c0, 0\n"
                "isb"
                ::"r"(val));
}

INLINE  UINT32 read_vbar()
{
	UINT32  rval;

	__asm__ __volatile__ (
                "mrc     p15, 0, %0, c12, c0, 0"
                :"=r"(rval));

	return  rval;
}

INLINE  UINT32 get_ttbcr()
{
	UINT32  rval;

	__asm__ __volatile__(
                "mrc     p15, 0, %0, c2, c0, 2"
                :"=r"(rval));

	return  rval;
}

INLINE VOID set_ttbcr(UINT32 val)
{

	__asm__ __volatile__(
                "mcr     p15, 0, %0, c2, c0, 2"
                ::"r"(val));
}

INLINE  UINT32 read_domain()
{
	UINT32  rval;

	__asm__ __volatile__(
                "mrc     p15, 0, %0, c3, c0, 0"
                :"=r"(rval));

	return  rval;
}

INLINE VOID write_domain(UINT32 val)
{
	__asm__ __volatile__(
                "mcr     p15, 0, %0, c3, c0, 0"
                ::"r"(val));
}

INLINE  UINT32 read_ttbr0()
{
	UINT32  rval;

	__asm__ __volatile__(
                "mrc     p15, 0, %0, c2, c0, 0"
                :"=r"(rval));

	return  rval;
}

INLINE VOID write_ttbr0(UINT32 val)
{
	__asm__ __volatile__(
                "mcr     p15, 0, %0, c2, c0, 0"
                ::"r"(val));
}

INLINE  UINT32 read_ttbr1()
{
	UINT32  rval;

	__asm__ __volatile__(
                "mrc  p15, 0, %0, c2, c0, 1"
                :"=r"(rval));

	return  rval;
}

INLINE VOID write_ttbr1(UINT32 val)
{
	__asm__ __volatile__(
                "mcr  p15, 0, %0, c2, c0, 1"
                ::"r"(val));
}

void cpu_wait_for_irq(void);


#endif
