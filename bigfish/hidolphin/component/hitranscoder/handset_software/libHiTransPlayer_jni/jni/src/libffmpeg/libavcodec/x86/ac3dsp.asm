;*****************************************************************************
;* x86-optimized AC-3 DSP utils
;* Copyright (c) 2011 Justin Ruggles
;*
;* This file is part of Libav.
;*
;* Libav is free software; you can redistribute it and/or
;* modify it under the terms of the GNU Lesser General Public
;* License as published by the Free Software Foundation; either
;* version 2.1 of the License, or (at your option) any later version.
;*
;* Libav is distributed in the hope that it will be useful,
;* but WITHOUT ANY WARRANTY; without even the implied warranty of
;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
;* Lesser General Public License for more details.
;*
;* You should have received a copy of the GNU Lesser General Public
;* License along with Libav; if not, write to the Free Software
;* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
;******************************************************************************

%include "x86inc.asm"
%include "x86util.asm"

SECTION_RODATA

; 16777216.0f - used in ff_float_to_fixed24()
pf_1_24: times 4 dd 0x4B800000

SECTION .text

;-----------------------------------------------------------------------------
; void ff_ac3_exponent_min(uint8_t *exp, int num_reuse_blocks, int nb_coefs)
;-----------------------------------------------------------------------------

%macro AC3_EXPONENT_MIN 1
cglobal ac3_exponent_min_%1, 3,4,2, exp, reuse_blks, expn, offset
    shl  reuse_blksq, 8
    jz .end
    LOOP_ALIGN
.nextexp:
    mov      offsetq, reuse_blksq
    mova          m0, [expq+offsetq]
    sub      offsetq, 256
    LOOP_ALIGN
.nextblk:
    PMINUB        m0, [expq+offsetq], m1
    sub      offsetq, 256
    jae .nextblk
    mova      [expq], m0
    add         expq, mmsize
    sub        expnq, mmsize
    jg .nextexp
.end:
    REP_RET
%endmacro

%define PMINUB PMINUB_MMX
%define LOOP_ALIGN
INIT_MMX
AC3_EXPONENT_MIN mmx
%ifdef HAVE_MMX2
%define PMINUB PMINUB_MMXEXT
%define LOOP_ALIGN ALIGN 16
AC3_EXPONENT_MIN mmxext
%endif
%ifdef HAVE_SSE
INIT_XMM
AC3_EXPONENT_MIN sse2
%endif
%undef PMINUB
%undef LOOP_ALIGN

;-----------------------------------------------------------------------------
; int ff_ac3_max_msb_abs_int16(const int16_t *src, int len)
;
; This function uses 2 different methods to calculate a valid result.
; 1) logical 'or' of abs of each element
;        This is used for ssse3 because of the pabsw instruction.
;        It is also used for mmx because of the lack of min/max instructions.
; 2) calculate min/max for the array, then or(abs(min),abs(max))
;        This is used for mmxext and sse2 because they have pminsw/pmaxsw.
;-----------------------------------------------------------------------------

%macro AC3_MAX_MSB_ABS_INT16 2
cglobal ac3_max_msb_abs_int16_%1, 2,2,5, src, len
    pxor        m2, m2
    pxor        m3, m3
.loop:
%ifidn %2, min_max
    mova        m0, [srcq]
    mova        m1, [srcq+mmsize]
    pminsw      m2, m0
    pminsw      m2, m1
    pmaxsw      m3, m0
    pmaxsw      m3, m1
%else ; or_abs
%ifidn %1, mmx
    mova        m0, [srcq]
    mova        m1, [srcq+mmsize]
    ABS2        m0, m1, m3, m4
%else ; ssse3
    ; using memory args is faster for ssse3
    pabsw       m0, [srcq]
    pabsw       m1, [srcq+mmsize]
%endif
    por         m2, m0
    por         m2, m1
%endif
    add       srcq, mmsize*2
    sub       lend, mmsize
    ja .loop
%ifidn %2, min_max
    ABS2        m2, m3, m0, m1
    por         m2, m3
%endif
%ifidn mmsize, 16
    movhlps     m0, m2
    por         m2, m0
%endif
    PSHUFLW     m0, m2, 0xe
    por         m2, m0
    PSHUFLW     m0, m2, 0x1
    por         m2, m0
    movd       eax, m2
    and        eax, 0xFFFF
    RET
%endmacro

INIT_MMX
%define ABS2 ABS2_MMX
%define PSHUFLW pshufw
AC3_MAX_MSB_ABS_INT16 mmx, or_abs
%define ABS2 ABS2_MMX2
AC3_MAX_MSB_ABS_INT16 mmxext, min_max
INIT_XMM
%define PSHUFLW pshuflw
AC3_MAX_MSB_ABS_INT16 sse2, min_max
%define ABS2 ABS2_SSSE3
AC3_MAX_MSB_ABS_INT16 ssse3, or_abs

;-----------------------------------------------------------------------------
; macro used for ff_ac3_lshift_int16() and ff_ac3_rshift_int32()
;-----------------------------------------------------------------------------

%macro AC3_SHIFT 4 ; l/r, 16/32, shift instruction, instruction set
cglobal ac3_%1shift_int%2_%4, 3,3,5, src, len, shift
    movd      m0, shiftd
.loop:
    mova      m1, [srcq         ]
    mova      m2, [srcq+mmsize  ]
    mova      m3, [srcq+mmsize*2]
    mova      m4, [srcq+mmsize*3]
    %3        m1, m0
    %3        m2, m0
    %3        m3, m0
    %3        m4, m0
    mova  [srcq         ], m1
    mova  [srcq+mmsize  ], m2
    mova  [srcq+mmsize*2], m3
    mova  [srcq+mmsize*3], m4
    add     srcq, mmsize*4
    sub     lend, mmsize*32/%2
    ja .loop
.end:
    REP_RET
%endmacro

;-----------------------------------------------------------------------------
; void ff_ac3_lshift_int16(int16_t *src, unsigned int len, unsigned int shift)
;-----------------------------------------------------------------------------

INIT_MMX
AC3_SHIFT l, 16, psllw, mmx
INIT_XMM
AC3_SHIFT l, 16, psllw, sse2

;-----------------------------------------------------------------------------
; void ff_ac3_rshift_int32(int32_t *src, unsigned int len, unsigned int shift)
;-----------------------------------------------------------------------------

INIT_MMX
AC3_SHIFT r, 32, psrad, mmx
INIT_XMM
AC3_SHIFT r, 32, psrad, sse2

;-----------------------------------------------------------------------------
; void ff_float_to_fixed24(int32_t *dst, const float *src, unsigned int len)
;-----------------------------------------------------------------------------

; The 3DNow! version is not bit-identical because pf2id uses truncation rather
; than round-to-nearest.
INIT_MMX
cglobal float_to_fixed24_3dnow, 3,3,0, dst, src, len
    movq   m0, [pf_1_24]
.loop:
    movq   m1, [srcq   ]
    movq   m2, [srcq+8 ]
    movq   m3, [srcq+16]
    movq   m4, [srcq+24]
    pfmul  m1, m0
    pfmul  m2, m0
    pfmul  m3, m0
    pfmul  m4, m0
    pf2id  m1, m1
    pf2id  m2, m2
    pf2id  m3, m3
    pf2id  m4, m4
    movq  [dstq   ], m1
    movq  [dstq+8 ], m2
    movq  [dstq+16], m3
    movq  [dstq+24], m4
    add  srcq, 32
    add  dstq, 32
    sub  lend, 8
    ja .loop
    REP_RET

INIT_XMM
cglobal float_to_fixed24_sse, 3,3,3, dst, src, len
    movaps     m0, [pf_1_24]
.loop:
    movaps     m1, [srcq   ]
    movaps     m2, [srcq+16]
    mulps      m1, m0
    mulps      m2, m0
    cvtps2pi  mm0, m1
    movhlps    m1, m1
    cvtps2pi  mm1, m1
    cvtps2pi  mm2, m2
    movhlps    m2, m2
    cvtps2pi  mm3, m2
    movq  [dstq   ], mm0
    movq  [dstq+ 8], mm1
    movq  [dstq+16], mm2
    movq  [dstq+24], mm3
    add      srcq, 32
    add      dstq, 32
    sub      lend, 8
    ja .loop
    REP_RET

INIT_XMM
cglobal float_to_fixed24_sse2, 3,3,9, dst, src, len
    movaps     m0, [pf_1_24]
.loop:
    movaps     m1, [srcq    ]
    movaps     m2, [srcq+16 ]
    movaps     m3, [srcq+32 ]
    movaps     m4, [srcq+48 ]
%ifdef m8
    movaps     m5, [srcq+64 ]
    movaps     m6, [srcq+80 ]
    movaps     m7, [srcq+96 ]
    movaps     m8, [srcq+112]
%endif
    mulps      m1, m0
    mulps      m2, m0
    mulps      m3, m0
    mulps      m4, m0
%ifdef m8
    mulps      m5, m0
    mulps      m6, m0
    mulps      m7, m0
    mulps      m8, m0
%endif
    cvtps2dq   m1, m1
    cvtps2dq   m2, m2
    cvtps2dq   m3, m3
    cvtps2dq   m4, m4
%ifdef m8
    cvtps2dq   m5, m5
    cvtps2dq   m6, m6
    cvtps2dq   m7, m7
    cvtps2dq   m8, m8
%endif
    movdqa  [dstq    ], m1
    movdqa  [dstq+16 ], m2
    movdqa  [dstq+32 ], m3
    movdqa  [dstq+48 ], m4
%ifdef m8
    movdqa  [dstq+64 ], m5
    movdqa  [dstq+80 ], m6
    movdqa  [dstq+96 ], m7
    movdqa  [dstq+112], m8
    add      srcq, 128
    add      dstq, 128
    sub      lenq, 32
%else
    add      srcq, 64
    add      dstq, 64
    sub      lenq, 16
%endif
    ja .loop
    REP_RET
