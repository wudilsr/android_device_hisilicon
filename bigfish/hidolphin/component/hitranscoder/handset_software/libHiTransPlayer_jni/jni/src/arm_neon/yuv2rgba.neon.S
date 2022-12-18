// Copyright (c) 2011 ARM Limited. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifdef __ARM_NEON__

 /* Initial ARM Neon implementation of core YUV2RGB functions. */

    .text
    .align
    .global yuv420_2_rgba_neon
    .type   yuv420_2_rgba_neon, %function
    .global yuv422_2_rgba_neon
    .type   yuv422_2_rgba_neon, %function

/* Constants */
#define coef_y         D0
#define coef_v_r       D1
#define coef_u_g       D2
#define coef_v_g       D3
#define coef_u_b       D4
/* D5 is spare */
#define bias_r         Q3
#define bias_r_lo      D6
#define bias_r_hi      D7
#define bias_g         Q4
#define bias_g_lo      D8
#define bias_g_hi      D9
#define bias_b         Q5
#define bias_b_lo      D10
#define bias_b_hi      D11

/* Input data */
#define y_even         D25
#define y_odd          D27
#define u              D16 /*overlaps with Q8 - b_delta, but safe */
#define v              D17 /*overlaps with Q8 - b_delta, but safe */

/* Chrominance signal for whole 16x2 block */
#define r_delta        Q6
#define g_delta        Q7
#define b_delta        Q8

/* Current group of 8 pixels */
#define red            Q9
#define grn            Q10
#define blu            Q11
#define y_scale        Q15

/* output area, in the right order for interleaved output with VST4 */
#define blu8_e         D25 /* overlaps with y_even, but safe */
#define red8_e         D24
#define blu8_o         D27 /* overlaps with y_odd, but safe */
#define red8_o         D26
#define grn8_e         D28
#define alp8_e         D29
#define grn8_o         D30 /* overlaps with Q15 - y_scale, but safe */
#define alp8_o         D31 /* overlaps with Q15 - y_scale, but safe */

/* ARM registers */
#define rgb_t_ptr      r0
#define y_t_ptr        r1
#define u_ptr          r2
#define v_ptr          r3
#define width          r4
#define height         r5
#define y_pitch        r6
#define uv_pitch       r7
#define rgb_pitch      r8
#define count          r9
#define aligned_count  sl
#define rgb_b_ptr      fp
#define y_b_ptr        ip

/* Constants */
/* 8-bit constants can be loaded into vectors using VMOV */
#define C_Y_SCALE      74   /* Y scale , 74 */
#define C_V_RED        102  /* v -> red coefficient, 102 */
#define C_U_GREEN      25   /* u -> green , -25 */
#define C_V_GREEN      52   /* v -> green , -52 */
#define C_U_BLUE       129  /* u -> blue, +129 */

/* Coefficients */
coefficients:
coeff_bias_r:
    .short  -14240  /* bias_r = 74 * (-16)                + (102 * -128) */
                    /*          -1,184                    + -13,056      */
coeff_bias_g:
    .short    8672  /* bias_g = 74 * (-16) -  25 * (-128) - ( 52 * -128) */
                    /*          -1,184     -  -3200       - -6,656       */
coeff_bias_b:
    .short  -17696  /* bias_b = 74 * (-16) + 129 * (-128)                */
                    /*          -1,184     + -16,512                     */
coeff_pad:
    .short       0

 /* void yuv420_2_rgba_neon(uint8_t       *dst_ptr,
                               const uint8_t *y_ptr,
                               const uint8_t *u_ptr,
                               const uint8_t *v_ptr,
                               int            width,
                               int            height); */
yuv420_2_rgba_neon:
    /*  r0 = dst_ptr */
    /*  r1 = y_ptr */
    /*  r2 = u_ptr */
    /*  r3 = v_ptr */
    /*  <> = width */
    /*  <> = height */
    /*  <> = y_pitch */
    /*  <> = uv_pitch */
    /*  <> = rgb_pitch */
    .fnstart
        PUSH            {r4-r12, lr}         /* 10 words */
        VPUSH           {q4-q7}              /* 4Q -> 16 words */

        LDR             width,  [sp, #26*4]
        LDR             height, [sp, #27*4]
        LDR             y_pitch, [sp, #28*4]
        LDR             uv_pitch, [sp, #29*4]
        LDR             rgb_pitch, [sp, #30*4]
        ADR             lr, coefficients

        /* We can't cope with a width less than 16. Check for that. */
        CMP             width, #16
        VPOPLT          {q4-q7}
        POPLT           {r4-r12, pc}

        /* Load up vectors containing the bias values. */
        VLD1.S16        {bias_r_lo[], bias_r_hi[]}, [lr]!
        VLD1.S16        {bias_g_lo[], bias_g_hi[]}, [lr]!
        VLD1.S16        {bias_b_lo[], bias_b_hi[]}, [lr]!

        /* Build coefficient vectors containing the same value in each element. */
        VMOV.U8         coef_y, #C_Y_SCALE
        VMOV.U8         coef_v_r, #C_V_RED
        VMOV.U8         coef_u_g, #C_U_GREEN
        VMOV.U8         coef_v_g, #C_V_GREEN
        VMOV.U8         coef_u_b, #C_U_BLUE

loop_v_420:
        ADD             y_b_ptr, y_t_ptr, y_pitch
        ADD             rgb_b_ptr, rgb_t_ptr, rgb_pitch
        MOV             aligned_count, width

        /* If width is not an integer multiple of 16, run the
           first pass through the loop with the correct number
           of pixels to correct the size for the remaining loops. */
        ANDS            count, width, #15
        /* If we're already aligned (i.e. count is now 0), set count
           to 16 to run the first loop as normal. */
        MOVEQ           count, #16

loop_h_420:
        /*****************************/
        /* COMMON CODE FOR BOTH ROWS */
        /*****************************/
        /* Load u and v. */
        VLD1.U8         v, [v_ptr]
        ADD             v_ptr, count, ASR #1
        VLD1.U8         u, [u_ptr]
        ADD             u_ptr, count, ASR #1

        /* Calculate contribution from chrominance signals. */
        VMULL.U8        r_delta, v, coef_v_r
        VMULL.U8        g_delta, u, coef_u_g
        VMLAL.U8        g_delta, v, coef_v_g
        VMULL.U8        b_delta, u, coef_u_b

        /* Add bias. */
        VADD.S16        r_delta, r_delta, bias_r
        VSUB.S16        g_delta, bias_g, g_delta
        VADD.S16        b_delta, b_delta, bias_b

        /* Attempt to preload the next set of u and v input data, for
           better performance. */
        PLD             [v_ptr]
        PLD             [u_ptr]

        /***********/
        /* TOP ROW */
        /***********/
        /* Top row: Load 16 pixels of y, even and odd. */
        VLD2.U8         {y_even, y_odd}, [y_t_ptr], count

        /* Top row, even: combine luminance and chrominance. */
        VMULL.U8        y_scale, y_even, coef_y
        VQADD.S16       red, y_scale, r_delta
        VQADD.S16       grn, y_scale, g_delta
        VQADD.S16       blu, y_scale, b_delta

        /* Top row, even: set up alpha data. */
        VMOV.U8         alp8_e, #0xFF

        /* Top row, even: clamp, rescale and clip colour components to 8 bits. */
        VQRSHRUN.S16    red8_e, red, #6
        VQRSHRUN.S16    grn8_e, grn, #6
        VQRSHRUN.S16    blu8_e, blu, #6

        /* Top row: attempt to preload the next set of Y data, for
           better performance. */
        PLD             [y_t_ptr]

        /* Top row, even: interleave the colour and alpha components
           ready for storage. */
        VZIP.U8         blu8_e, alp8_e
        VZIP.U8         red8_e, grn8_e

        /* Top row, odd: combine luminance and chrominance. */
        VMULL.U8        y_scale, y_odd, coef_y
        VQADD.S16       red, y_scale, r_delta
        VQADD.S16       grn, y_scale, g_delta
        VQADD.S16       blu, y_scale, b_delta

        /* Top row, odd: set up alpha data. */
        VMOV.U8         alp8_o, #0xFF

        /* Top row, odd: clamp, rescale and clip colour components to 8 bits. */
        VQRSHRUN.S16    red8_o, red, #6
        VQRSHRUN.S16    blu8_o, blu, #6
        VQRSHRUN.S16    grn8_o, grn, #6

        /* Top row, odd: interleave the colour and alpha components
           ready for storage. */
        VZIP.U8         blu8_o, alp8_o
        VZIP.U8         red8_o, grn8_o

        /* Top row: Store 16 pixels of ARGB32, interleaving even and
           odd. */
        VST4.U16        {red8_e, blu8_e, red8_o, blu8_o}, [rgb_t_ptr]
        ADD             rgb_t_ptr, count, LSL #1
        VST4.U16        {grn8_e, alp8_e, grn8_o, alp8_o}, [rgb_t_ptr]
        ADD             rgb_t_ptr, count, LSL #1

        /**************/
        /* BOTTOM ROW */
        /**************/
        /* Bottom row: Load 16 pixels of y, even and odd. */
        VLD2.U8         {y_even, y_odd}, [y_b_ptr], count

        /* Bottom row, even: combine luminance and chrominance. */
        VMULL.U8        y_scale, y_even, coef_y
        VQADD.S16       red, y_scale, r_delta
        VQADD.S16       grn, y_scale, g_delta
        VQADD.S16       blu, y_scale, b_delta

        /* Bottom row, even: set up alpha data. */
        VMOV.U8         alp8_e, #0xFF

        /* Bottom row, even: clamp, rescale and clip colour components to 8 bits. */
        VQRSHRUN.S16    red8_e, red, #6
        VQRSHRUN.S16    blu8_e, blu, #6
        VQRSHRUN.S16    grn8_e, grn, #6

        /* Bottom row: attempt to preload the next set of Y data, for
           better performance. */
        PLD             [y_b_ptr]

        /* Bottom row, even: interleave the colour and alpha components
           ready for storage. */
        VZIP.U8         blu8_e, alp8_e
        VZIP.U8         red8_e, grn8_e

        /* Bottom row, odd: combine luminance and chrominance. */
        VMULL.U8        y_scale, y_odd, coef_y
        VQADD.S16       red, y_scale, r_delta
        VQADD.S16       grn, y_scale, g_delta
        VQADD.S16       blu, y_scale, b_delta

        /* Bottom row, odd: set up alpha data. */
        VMOV.U8         alp8_o, #0xFF

        /* Bottom row, odd: clamp, rescale and clip colour components to 8 bits. */
        VQRSHRUN.S16    red8_o, red, #6
        VQRSHRUN.S16    blu8_o, blu, #6
        VQRSHRUN.S16    grn8_o, grn, #6

        /* Bottom row, odd: Interleave the colour and alpha components
           ready for storage. */
        VZIP.U8         blu8_o, alp8_o
        VZIP.U8         red8_o, grn8_o

        /* Have we reached the end of the row yet? */
        SUBS            aligned_count, aligned_count, count

        /* Bottom row: Store 16 pixels of ARGB32, interleaving even and
           odd. */
        VST4.U16        {red8_e, blu8_e, red8_o, blu8_o}, [rgb_b_ptr]
        ADD             rgb_b_ptr, count, LSL #1
        VST4.U16        {grn8_e, alp8_e, grn8_o, alp8_o}, [rgb_b_ptr]
        ADD             rgb_b_ptr, count, LSL #1

        /* On the second (and subsequent) passes through this code,
           we'll always be working on 16 pixels at once. */
        MOV             count, #16
        BGT             loop_h_420

        /* Update pointers for new row of data. */
        SUB             rgb_t_ptr, width, LSL #2
        SUB             y_t_ptr, width
        SUB             u_ptr, width, ASR #1
        SUB             v_ptr, width, ASR #1
        ADD             rgb_t_ptr, rgb_pitch, LSL #1
        ADD             y_t_ptr, y_pitch, LSL #1
        ADD             u_ptr, uv_pitch
        ADD             v_ptr, uv_pitch

        /* Have we reached the bottom row yet? */
        SUBS            height, height, #2
        BGT             loop_v_420

        VPOP            {q4-q7}
        POP             {r4-r12, pc}
        .fnend

/* Much the same as the above code, but simplified to work on a single
   row at a time. Each U and V value only covers 2 adjacent pixels on
   one row, not a 2x2 matrix */
#define rgb_ptr     rgb_t_ptr
#define y_ptr       y_t_ptr

yuv422_2_rgba_neon:
    /*  r0 = dst_ptr */
    /*  r1 = y_ptr */
    /*  r2 = u_ptr */
    /*  r3 = v_ptr */
    /*  <> = width */
    /*  <> = height */
    /*  <> = y_pitch */
    /*  <> = uv_pitch */
    /*  <> = rgb_pitch */
    .fnstart
        PUSH            {r4-r12, lr}         /* 10 words */
        VPUSH           {q4-q7}              /* 4Q -> 16 words */

        LDR             width,  [sp, #26*4]
        LDR             height, [sp, #27*4]
        LDR             y_pitch, [sp, #28*4]
        LDR             uv_pitch, [sp, #29*4]
        LDR             rgb_pitch, [sp, #30*4]
        ADR             lr, coefficients

        /* We can't cope with a width less than 16. Check for that. */
        CMP             width, #16
        VPOPLT          {q4-q7}
        POPLT           {r4-r12, pc}

        /* Load up vectors containing the bias values. */
        VLD1.S16        {bias_r_lo[], bias_r_hi[]}, [lr]!
        VLD1.S16        {bias_g_lo[], bias_g_hi[]}, [lr]!
        VLD1.S16        {bias_b_lo[], bias_b_hi[]}, [lr]!

        /* Build coefficient vectors containing the same value in each element. */
        VMOV.U8         coef_y, #C_Y_SCALE
        VMOV.U8         coef_v_r, #C_V_RED
        VMOV.U8         coef_u_g, #C_U_GREEN
        VMOV.U8         coef_v_g, #C_V_GREEN
        VMOV.U8         coef_u_b, #C_U_BLUE

loop_v_422:
        MOV             aligned_count, width
        /* If width is not an integer multiple of 16, run the
           first pass through the loop with the correct number
           of pixels to correct the size for the remaining loops. */
        ANDS            count, width, #15
        /* If we're already aligned (i.e. count is now 0), set count
           to 16 to run the first loop as normal. */
        MOVEQ           count, #16

loop_h_422:
        /* Load u and v. */
        VLD1.U8         v, [v_ptr]
        ADD             v_ptr, count, ASR #1
        VLD1.U8         u, [u_ptr]
        ADD             u_ptr, count, ASR #1

        /* Calculate contribution from chrominance signals. */
        VMULL.U8        r_delta, v, coef_v_r
        VMULL.U8        g_delta, u, coef_u_g
        VMLAL.U8        g_delta, v, coef_v_g
        VMULL.U8        b_delta, u, coef_u_b

        /* Attempt to preload the next set of u and v input data, for
           better performance. */
        PLD             [v_ptr]
        PLD             [u_ptr]

        /* Load 16 pixels of y, even and odd. */
        VLD2.U8         {y_even, y_odd}, [y_ptr], count

        /* Add bias. */
        VADD.S16        r_delta, r_delta, bias_r
        VSUB.S16        g_delta, bias_g, g_delta
        VADD.S16        b_delta, b_delta, bias_b

        /* Even: combine luminance and chrominance. */
        VMULL.U8        y_scale, y_even, coef_y
        VQADD.S16       red, y_scale, r_delta
        VQADD.S16       grn, y_scale, g_delta
        VQADD.S16       blu, y_scale, b_delta

        /* Even: set up alpha data. */
        VMOV.U8         alp8_e, #0xFF

        /* Attempt to preload the next set of Y data, for better
           performance. */
        PLD             [y_ptr]

        /* Even: clamp, rescale and clip colour components to 8 bits. */
        VQRSHRUN.S16    red8_e, red, #6
        VQRSHRUN.S16    grn8_e, grn, #6
        VQRSHRUN.S16    blu8_e, blu, #6

        /* Even: Interleave the colour and alpha components
           ready for storage. */
        VZIP.U8         blu8_e, alp8_e
        VZIP.U8         red8_e, grn8_e

        /* Odd: combine luminance and chrominance. */
        VMULL.U8        y_scale, y_odd, coef_y
        VQADD.S16       red, y_scale, r_delta
        VQADD.S16       grn, y_scale, g_delta
        VQADD.S16       blu, y_scale, b_delta

        /* Odd: set up alpha data. */
        VMOV.U8         alp8_o, #0xFF

        /* Odd: clamp, rescale and clip colour components to 8 bits. */
        VQRSHRUN.S16    red8_o, red, #6
        VQRSHRUN.S16    blu8_o, blu, #6
        VQRSHRUN.S16    grn8_o, grn, #6

        /* Odd: Interleave the colour and alpha components
           ready for storage. */
        VZIP.U8         blu8_o, alp8_o
        VZIP.U8         red8_o, grn8_o

        /* Have we reached the end of the row yet? */
        SUBS            aligned_count, aligned_count, count

        /* Store 16 pixels of ARGB32, interleaving even and odd. */
        VST4.U16        {red8_e, blu8_e, red8_o, blu8_o}, [rgb_ptr]
        ADD             rgb_ptr, count, LSL #1
        VST4.U16        {grn8_e, alp8_e, grn8_o, alp8_o}, [rgb_ptr]
        ADD             rgb_ptr, count, LSL #1

        /* On the second (and subsequent) passes through this code,
           we'll always be working on 16 pixels at once. */
        MOV             count, #16
        BGT             loop_h_422

        /* Update pointers for new row of data. */
        SUB             rgb_ptr, width, LSL #2
        SUB             y_ptr, width
        SUB             u_ptr, width, ASR #1
        SUB             v_ptr, width, ASR #1
        ADD             rgb_ptr, rgb_pitch
        ADD             y_ptr, y_pitch
        ADD             u_ptr, uv_pitch
        ADD             v_ptr, uv_pitch

        /* Have we reached the bottom yet? */
        SUBS            height, height, #1
        BGT             loop_v_422

        VPOP            {q4-q7}
        POP             {r4-r12, pc}
        .fnend

#endif /* __ARM_NEON__ */