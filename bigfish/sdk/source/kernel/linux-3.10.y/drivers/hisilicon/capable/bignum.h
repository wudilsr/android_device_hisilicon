/******************************************************************************
 *  Copyright (C) 2014 Hisilicon Technologies CO.,LTD.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Create By Cai Zhiyong 2014.12.22
 *
******************************************************************************/

#ifndef POLARSSL_BIGNUM_H
#define POLARSSL_BIGNUM_H

#if defined(__GNUC__)
#  if defined(__arm__)

#define MULADDC_INIT                            \
	asm("ldr    r0, %0         " :: "m" (s));  \
	asm("ldr    r1, %0         " :: "m" (d));  \
	asm("ldr    r2, %0         " :: "m" (c));  \
	asm("ldr    r3, %0         " :: "m" (b));

#define MULADDC_CORE                            \
	asm("ldr    r4, [r0], #4   ");            \
	asm("mov    r5, #0         ");            \
	asm("ldr    r6, [r1]       ");            \
	asm("umlal  r2, r5, r3, r4 ");            \
	asm("adds   r7, r6, r2     ");            \
	asm("adc    r2, r5, #0     ");            \
	asm("str    r7, [r1], #4   ");

#define MULADDC_STOP                            \
	asm("str    r2, %0         " : "=m" (c));  \
	asm("str    r1, %0         " : "=m" (d));  \
	asm("str    r0, %0         " : "=m" (s) :: \
	"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7");

#  endif /* ARMv3 */
#endif /* GNUC */


#if !defined(MULADDC_CORE)

#define MULADDC_INIT                    \
{                                       \
	t_int s0, s1, b0, b1;               \
	t_int r0, r1, rx, ry;               \
	b0 = (b << biH) >> biH;           \
	b1 = (b >> biH);

#define MULADDC_CORE                    \
	s0 = (*s << biH) >> biH;          \
	s1 = (*s >> biH); s++;            \
	rx = s0 * b1; r0 = s0 * b0;         \
	ry = s1 * b0; r1 = s1 * b1;         \
	r1 += (rx >> biH);                \
	r1 += (ry >> biH);                \
	rx <<= biH; ry <<= biH;             \
	r0 += rx; r1 += (r0 < rx);          \
	r0 += ry; r1 += (r0 < ry);          \
	r0 +=  c; r1 += (r0 <  c);          \
	r0 += *d; r1 += (r0 < *d);          \
	c = r1; *(d++) = r0;

#define MULADDC_STOP                    \
}
#endif /* C (longlong) */


#define POLARSSL_ERR_MPI_FILE_IO_ERROR                     0x0002
#define POLARSSL_ERR_MPI_BAD_INPUT_DATA                    0x0004
#define POLARSSL_ERR_MPI_INVALID_CHARACTER                 0x0006
#define POLARSSL_ERR_MPI_BUFFER_TOO_SMALL                  0x0008
#define POLARSSL_ERR_MPI_NEGATIVE_VALUE                    0x000A
#define POLARSSL_ERR_MPI_DIVISION_BY_ZERO                  0x000C
#define POLARSSL_ERR_MPI_NOT_ACCEPTABLE                    0x000E


#define MPI_CHK(f) if((ret = f) != 0) goto cleanup

/*
 * Define the base integer type, architecture-wise
 */

typedef unsigned long t_int;

/**
 * \brief          MPI structure
 */
typedef struct {
	int s;              /*!<  integer sign      */
	int n;              /*!<  total # of limbs  */
	t_int *p;           /*!<  pointer to limbs  */
} mpi;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          Initialize one or more mpi
 */
void hicap_bignum_init(mpi *X, ...);

/**
 * \brief          Unallocate one or more mpi
 */
void hicap_bignum_free(mpi *X, ...);

/**
 * \brief          Enlarge to the specified number of limbs
 *
 * \param X        MPI to grow
 * \param nblimbs  The target number of limbs
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_grow(mpi *X, int nblimbs);

/**
 * \brief          Copy the contents of Y into X
 *
 * \param X        Destination MPI
 * \param Y        Source MPI
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_copy(mpi *X, const mpi *Y);


/**
 * \brief          Return the number of most significant bits
 *
 * \param X        MPI to use
 */
int hicap_bignum_msb(const mpi *X);

/**
 * \brief          Import from an ASCII string
 *
 * \param X        Destination MPI
 * \param radix    Input numeric base
 * \param s        Null-terminated string buffer
 *
 * \return         0 if successful, or an POLARSSL_ERR_MPI_XXX error code
 */
int hicap_bignum_read_string(mpi *X, int radix, const char *s);

/**
 * \brief          Import X from unsigned binary data, big endian
 *
 * \param X        Destination MPI
 * \param buf      Input buffer
 * \param buflen   Input buffer size
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_read_binary(mpi *X, const unsigned char *buf, int buflen);

/**
 * \brief          Export X into unsigned binary data, big endian
 *
 * \param X        Source MPI
 * \param buf      Output buffer
 * \param buflen   Output buffer size
 *
 * \return         0 if successful,
 *                 POLARSSL_ERR_MPI_BUFFER_TOO_SMALL if buf isn't large enough
 */
int hicap_bignum_write_binary(const mpi *X, unsigned char *buf, int buflen);

/**
 * \brief          Left-shift: X <<= count
 *
 * \param X        MPI to shift
 * \param count    Amount to shift
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_shift_l(mpi *X, int count);

/**
 * \brief          Right-shift: X >>= count
 *
 * \param X        MPI to shift
 * \param count    Amount to shift
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_shift_r(mpi *X, int count);

/**
 * \brief          Compare unsigned values
 *
 * \param X        Left-hand MPI
 * \param Y        Right-hand MPI
 *
 * \return         1 if |X| is greater than |Y|,
 *                -1 if |X| is lesser  than |Y| or
 *                 0 if |X| is equal to |Y|
 */
int hicap_bignum_cmp_abs(const mpi *X, const mpi *Y);

/**
 * \brief          Compare signed values
 *
 * \param X        Left-hand MPI
 * \param Y        Right-hand MPI
 *
 * \return         1 if X is greater than Y,
 *                -1 if X is lesser  than Y or
 *                 0 if X is equal to Y
 */
int hicap_bignum_cmp_mpi(const mpi *X, const mpi *Y);

/**
 * \brief          Compare signed values
 *
 * \param X        Left-hand MPI
 * \param z        The integer value to compare to
 *
 * \return         1 if X is greater than z,
 *                -1 if X is lesser  than z or
 *                 0 if X is equal to z
 */
int hicap_bignum_cmp_int(const mpi *X, int z);

/**
 * \brief          Unsigned addition: X = |A| + |B|
 *
 * \param X        Destination MPI
 * \param A        Left-hand MPI
 * \param B        Right-hand MPI
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_add_abs(mpi *X, const mpi *A, const mpi *B);

/**
 * \brief          Unsigned substraction: X = |A| - |B|
 *
 * \param X        Destination MPI
 * \param A        Left-hand MPI
 * \param B        Right-hand MPI
 *
 * \return         0 if successful,
 *                 POLARSSL_ERR_MPI_NEGATIVE_VALUE if B is greater than A
 */
int hicap_bignum_sub_abs(mpi *X, const mpi *A, const mpi *B);

/**
 * \brief          Signed addition: X = A + B
 *
 * \param X        Destination MPI
 * \param A        Left-hand MPI
 * \param B        Right-hand MPI
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_add_mpi(mpi *X, const mpi *A, const mpi *B);

/**
 * \brief          Signed substraction: X = A - B
 *
 * \param X        Destination MPI
 * \param A        Left-hand MPI
 * \param B        Right-hand MPI
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_sub_mpi(mpi *X, const mpi *A, const mpi *B);

/**
 * \brief          Signed addition: X = A + b
 *
 * \param X        Destination MPI
 * \param A        Left-hand MPI
 * \param b        The integer value to add
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_add_int(mpi *X, const mpi *A, int b);

/**
 * \brief          Signed substraction: X = A - b
 *
 * \param X        Destination MPI
 * \param A        Left-hand MPI
 * \param b        The integer value to subtract
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_sub_int(mpi *X, const mpi *A, int b);

/**
 * \brief          Baseline multiplication: X = A * B
 *
 * \param X        Destination MPI
 * \param A        Left-hand MPI
 * \param B        Right-hand MPI
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_mul_mpi(mpi *X, const mpi *A, const mpi *B);

/**
 * \brief          Baseline multiplication: X = A * b
 *                 Note: b is an unsigned integer type, thus
 *                 Negative values of b are ignored.
 *
 * \param X        Destination MPI
 * \param A        Left-hand MPI
 * \param b        The integer value to multiply with
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_mul_int(mpi *X, const mpi *A, t_int b);

/**
 * \brief          Division by mpi: A = Q * B + R
 *
 * \param Q        Destination MPI for the quotient
 * \param R        Destination MPI for the rest value
 * \param A        Left-hand MPI
 * \param B        Right-hand MPI
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed,
 *                 POLARSSL_ERR_MPI_DIVISION_BY_ZERO if B == 0
 *
 * \note           Either Q or R can be NULL.
 */
int hicap_bignum_div_mpi(mpi *Q, mpi *R, const mpi *A, const mpi *B);

/**
 * \brief          Modulo: R = A mod B
 *
 * \param R        Destination MPI for the rest value
 * \param A        Left-hand MPI
 * \param B        Right-hand MPI
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed,
 *                 POLARSSL_ERR_MPI_DIVISION_BY_ZERO if B == 0,
 *                 POLARSSL_ERR_MPI_NEGATIVE_VALUE if B < 0
 */
int hicap_bignum_mod_mpi(mpi *R, const mpi *A, const mpi *B);

/**
 * \brief          Modulo: r = A mod b
 *
 * \param r        Destination t_int
 * \param A        Left-hand MPI
 * \param b        Integer to divide by
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed,
 *                 POLARSSL_ERR_MPI_DIVISION_BY_ZERO if b == 0,
 *                 POLARSSL_ERR_MPI_NEGATIVE_VALUE if b < 0
 */
int hicap_bignum_mod_int(t_int *r, const mpi *A, int b);

/**
 * \brief          Sliding-window exponentiation: X = A^E mod N
 *
 * \param X        Destination MPI 
 * \param A        Left-hand MPI
 * \param E        Exponent MPI
 * \param N        Modular MPI
 * \param _RR      Speed-up MPI used for recalculations
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed,
 *                 POLARSSL_ERR_MPI_BAD_INPUT_DATA if N is negative or even
 *
 * \note           _RR is used to avoid re-computing R*R mod N across
 *                 multiple calls, which speeds up things a bit. It can
 *                 be set to NULL if the extra performance is unneeded.
 */
int hicap_bignum_exp_mod(mpi *X, const mpi *A, const mpi *E, const mpi *N, mpi *_RR);

/**
 * \brief          Greatest common divisor: G = gcd(A, B)
 *
 * \param G        Destination MPI
 * \param A        Left-hand MPI
 * \param B        Right-hand MPI
 *
 * \return         0 if successful,
 *                 1 if memory allocation failed
 */
int hicap_bignum_gcd(mpi *G, const mpi *A, const mpi *B);

/**
 * \brief          Miller-Rabin primality test
 *
 * \param X        MPI to check
 * \param f_rng    RNG function
 * \param p_rng    RNG parameter
 *
 * \return         0 if successful (probably prime),
 *                 1 if memory allocation failed,
 *                 POLARSSL_ERR_MPI_NOT_ACCEPTABLE if X is not prime
 */
int hicap_bignum_is_prime(mpi *X, int (*f_rng)(void *), void *p_rng);

void *hicap_vmalloc(unsigned int size);

void hicap_vfree(void *ptr);

#ifdef __cplusplus
}
#endif

#endif /* bignum.h */
