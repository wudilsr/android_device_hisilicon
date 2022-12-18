

static uint16 FXlog10_table[] = {
    0x0000, 0x00DD, 0x01B9, 0x0293, 0x036B, 0x0442, 0x0517, 0x05EB,
    0x06BD, 0x078E, 0x085D, 0x092A, 0x09F6, 0x0AC1, 0x0B8A, 0x0C51,
    0x0D18, 0x0DDD, 0x0EA0, 0x0F63, 0x1024, 0x10E3, 0x11A2, 0x125F,
    0x131B, 0x13D5, 0x148F, 0x1547, 0x15FE, 0x16B4, 0x1769, 0x181C,
    0x18CF, 0x1980, 0x1A30, 0x1ADF, 0x1B8D, 0x1C3A, 0x1CE6, 0x1D91,
    0x1E3B, 0x1EE4, 0x1F8C, 0x2033, 0x20D9, 0x217E, 0x2222, 0x22C5,
    0x2367, 0x2409, 0x24A9, 0x2548, 0x25E7, 0x2685, 0x2721, 0x27BD,
    0x2858, 0x28F3, 0x298C, 0x2A25, 0x2ABD, 0x2B54, 0x2BEA, 0x2C7F,
    0x2D14, 0x2DA8, 0x2E3B, 0x2ECD, 0x2F5F, 0x2FF0, 0x3080, 0x310F,
    0x319E, 0x322C, 0x32B9, 0x3345, 0x33D1, 0x345C, 0x34E7, 0x3571,
    0x35FA, 0x3682, 0x370A, 0x3792, 0x3818, 0x389E, 0x3923, 0x39A8,
    0x3A2C, 0x3AB0, 0x3B32, 0x3BB5, 0x3C36, 0x3CB7, 0x3D38, 0x3DB8,
    0x3E37, 0x3EB6, 0x3F34, 0x3FB2, 0x402F, 0x40AC, 0x4128, 0x41A3,
    0x421E, 0x4298, 0x4312, 0x438C, 0x4405, 0x447D, 0x44F5, 0x456C,
    0x45E3, 0x4659, 0x46CF, 0x4744, 0x47B9, 0x482E, 0x48A2, 0x4915,
    0x4988, 0x49FB, 0x4A6D, 0x4ADE, 0x4B50, 0x4BC0, 0x4C31, 0x4CA0,
    0x4D10,
};

static uint32 FXlog2_table[] = {
    0x00000000L, 0x00004D10L, 0x00009A20L, 0x0000E730L,
    0x00013441L, 0x00018151L, 0x0001CE61L, 0x00021B72L,
    0x00026882L, 0x0002B592L, 0x000302A3L, 0x00034FB3L,
    0x00039CC3L, 0x0003E9D3L, 0x000436E4L, 0x000483F4L,
    0x0004d104L,
};

static long FHLL_mul(long f, long g)

/****************************************************************************
*
* Function:     FHLL_mul
* Parameters:   f   - long point mutiplicand
*               g   - long point number to multiply by
* Returns:      Result of the multiplication.
*
* Description:  Multiplies two fixed point number in 16.16 format together
*               and returns the result. We cannot simply multiply the
*               two 32 bit numbers together since we need to shift the
*               64 bit result right 16 bits, but the result of a long
*               multiply is only ever 32 bits! Thus we must resort to
*               computing it from first principles (this is slow and
*               should ideally be re-coded in assembler for the target
*               machine).
*
*               We can visualise the fixed point number as having two
*               parts, a whole part and a fractional part:
*
*                   long = (whole + frac * 2^-16)
*
*               Thus if we multiply two of these numbers together we
*               get a 64 bit result:
*
*               (a_whole + a_frac * 2^-16) * (b_whole + b_frac * 2^-16)
*
*                 = (a_whole * b_whole) +
*                   (a_whole * b_frac)*2^-16 +
*                   (b_whole * a_frac)*2^-16 +
*                   (a_frac * b_frac)*2^-32
*
*               To convert this back to a 64 bit fixed point number to 32
*               bit format we simply shift it right by 16 bits (we can round
*               it by adding 2^-17 before doing this shift). The formula
*               with the shift integrated is what is used below. Natrually
*               you can alleviate most of this if the target machine can
*               perform a native 32 by 32 bit multiplication (since it
*               will produce a 64 bit result).
*
****************************************************************************/
{
    long a_whole, b_whole;
    long a_frac, b_frac;

    // Extract the whole and fractional parts of the numbers. We strip the
    // sign bit from the fractional parts but leave it intact for the
    // whole parts. This ensures that the sign of the result will be correct.

    a_frac  = f & 0x0000FFFF;
    a_whole = f >> 16;
    b_frac  = g & 0x0000FFFF;
    b_whole = g >> 16;

    // We round the result by adding 2^(-17) before we shift the
    // fractional part of the result left 16 bits.

    return ((a_whole * b_whole) << 16) +
           (a_whole * b_frac) +
           (a_frac * b_whole) +
           ((a_frac * b_frac + 0x8000) >> 16);
}

static long FHLL_log10(long f)

/****************************************************************************
*
* Function:     FHLL_log10
* Parameters:   f   - Number to take the square root of
* Returns:      Approximate square root of the number f
*
* Description:  Caculates the common logarithm of a fixed point number
*               using table lookup and linear interpolation.
*
*               First we isolate the first 8 bits of the mantissa in our
*               fixed point number. We do this by scanning along until we
*               find the first 1 bit in the number, and shift it all right
*               until this is in bit position 7. Since IEEE floating point
*               numbers have an implied 1 bit in the mantissa, we mask this
*               bit out and use the 7 bits as an index into the table. We
*               then look up this value, and add in the appropriate logarithm
*               for the power for two represented by the numbers exponent.
*
*               Because of the linear interpolation, this routine will
*               provide a common logarithm of any 16.16 fixed point
*               number that is as good as you can get given the precision
*               of fixed point (approx 1e-4 deviation).
*
****************************************************************************/
{
    unsigned short e, eindex;                // Exponent and index into table
    long r, diff, interpolant;

    if (f <= 0)
    {
        // Check for -ve and zero
        return 0;
    }

    // Search for the index of the first 1 bit in the number (start of
    // the mantissa. Note that we are only working with positive numbers
    // here, so we ignore the sign bit (bit 31).
    e = 14;                         // Exponent for number with 1 in bit
                                    // position 30
    while ((f & 0x40000000) == 0)
    {
        // Isolate first bit
        f <<= 1;                    // Shift all left 1
        e--;                        // Decrement exponent for number
    }

    // At this stage our number is in the following format:
    //
    //   bits 23-30        15-22       0-14
    //  +-------------+-------------+---------+
    //  |.table index.|.interpolant.|.ignored.|
    //  +-------------+-------------+---------+
    //
    // We compute the index into the table by shifting the mantissa
    // so that the first 1 bit ends up in bit position 7, and mask it
    // out. The interpolant factor that we use is the bottom 16
    // bits left in the original number after the index is extracted out,
    // and is used to linearly interpolate the results between the two
    // consecutive entries in the table.
    eindex = (unsigned short)(f >> 23) & 0x7F;
    interpolant = (f >> 7) & 0xFFFF;

    // Lookup the values for the 7 bits of mantissa in the table, and
    // linearly interpolate between the two entries.
    diff = FXlog10_table[eindex + 1] - (r = FXlog10_table[eindex]);
    r += FHLL_mul(diff, interpolant);

    // Now find the appropriate power of 2 logarithm to add to the final
    // result.
    if (e < 0)
    {
        r -= FXlog2_table[-e];
    }
    else
    {
        r += FXlog2_table[e];
    }

    return r;
}