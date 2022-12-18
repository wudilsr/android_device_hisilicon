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

#include <linux/kernel.h>
#include <stdarg.h>

#include "bignum.h"

#define ciL    ((int) sizeof(t_int))    /* chars in limb  */
#define biL    (ciL << 3)               /* bits  in limb  */
#define biH    (ciL << 2)               /* half limb size */

/*
* Convert between bits/chars and number of limbs
*/
#define BITS_TO_LIMBS(i)  (((i) + biL - 1) / biL)
#define CHARS_TO_LIMBS(i) (((i) + ciL - 1) / ciL)

static int hicap_bignum_lset(mpi *X, int z);
static int hicap_bignum_lsb(const mpi *X);
static int hicap_bignum_size(const mpi *X);
/******************************************************************************/
/*
* Initialize one or more mpi
*/
void hicap_bignum_init(mpi *X, ...)
{
	va_list args;

	va_start(args, X);

	while (X != NULL) {
		X->s = 1;
		X->n = 0;
		X->p = NULL;

		X = va_arg(args, mpi*);
	}

	va_end(args);
}
/******************************************************************************/
/*
* Unallocate one or more mpi
*/
void hicap_bignum_free(mpi *X, ...)
{
	va_list args;

	va_start(args, X);

	while (X != NULL) {
		if (X->p != NULL)
		{
			memset(X->p, 0, X->n * ciL);
			hicap_vfree(X->p);
		}

		X->s = 1;
		X->n = 0;
		X->p = NULL;

		X = va_arg(args, mpi*);
	}

	va_end(args);
}
/******************************************************************************/
/*
* Enlarge to the specified number of limbs
*/
int hicap_bignum_grow(mpi *X, int nblimbs)
{
	t_int *p;

	if (X->n < nblimbs) {
		if ((p = (t_int *)hicap_vmalloc(nblimbs * ciL)) == NULL)
			return (1);

		memset(p, 0, nblimbs * ciL);

		if (X->p != NULL) {
			memcpy(p, X->p, X->n * ciL);
			memset(X->p, 0, X->n * ciL);
			hicap_vfree(X->p);
		}

		X->n = nblimbs;
		X->p = p;
	}

	return (0);
}

/******************************************************************************/
/*
* Copy the contents of Y into X
*/
int hicap_bignum_copy(mpi *X, const mpi *Y)
{
	int ret, i;

	if (X == Y)
		return(0);

	for (i = Y->n - 1; i > 0; i--)
		if (Y->p[i] != 0)
			break;
	i++;

	X->s = Y->s;

	MPI_CHK(hicap_bignum_grow(X, i));

	memset(X->p, 0, X->n * ciL);
	memcpy(X->p, Y->p, i * ciL);

cleanup:

	return(ret);
}
/******************************************************************************/
/*
* Set value from integer
*/
static int hicap_bignum_lset(mpi *X, int z)
{
	int ret;

	MPI_CHK(hicap_bignum_grow(X, 1));
	memset(X->p, 0, X->n * ciL);

	X->p[0] = (z < 0) ? -z : z;
	X->s    = (z < 0) ? -1 : 1;

cleanup:

	return(ret);
}
/******************************************************************************/
/*
* Return the number of least significant bits
*/
static int hicap_bignum_lsb(const mpi *X)
{
	int i, j, count = 0;

	for (i = 0; i < X->n; i++)
		for (j = 0; j < (int) biL; j++, count++)
			if (((X->p[i] >> j) & 1) != 0)
				return(count);

	return(0);
}
/******************************************************************************/
/*
* Return the number of most significant bits
*/
int hicap_bignum_msb(const mpi *X)
{
	int i, j;

	for (i = X->n - 1; i > 0; i--)
		if (X->p[i] != 0)
			break;

	for (j = biL - 1; j >= 0; j--)
		if (((X->p[i] >> j) & 1) != 0)
			break;

	return((i * biL) + j + 1);
}
/******************************************************************************/
/*
* Return the total size in bytes
*/
static int hicap_bignum_size(const mpi *X)
{
	return((hicap_bignum_msb(X) + 7) >> 3);
}
/******************************************************************************/
/*
* Convert an ASCII character to digit value
*/
static int mpi_get_digit(t_int *d, int radix, char c)
{
	*d = 255;

	if (c >= 0x30 && c <= 0x39)
		*d = c - 0x30;
	if (c >= 0x41 && c <= 0x46)
		*d = c - 0x37;
	if (c >= 0x61 && c <= 0x66)
		*d = c - 0x57;

	if (*d >= (t_int) radix)
		return(POLARSSL_ERR_MPI_INVALID_CHARACTER);

	return(0);
}
/******************************************************************************/
/*
* Import from an ASCII string
*/
int hicap_bignum_read_string(mpi *X, int radix, const char *s)
{
	int ret, i, j, n, slen;
	t_int d;
	mpi T;

	if (radix < 2 || radix > 16)
		return(POLARSSL_ERR_MPI_BAD_INPUT_DATA);

	hicap_bignum_init(&T, NULL);

	slen = strlen(s);

	if (radix == 16) {
		n = BITS_TO_LIMBS(slen << 2);

		MPI_CHK(hicap_bignum_grow(X, n));
		MPI_CHK(hicap_bignum_lset(X, 0));

		for (i = slen - 1, j = 0; i >= 0; i--, j++) {
			if (i == 0 && s[i] == '-') {
				X->s = -1;
				break;
			}

			MPI_CHK(mpi_get_digit(&d, radix, s[i]));
			X->p[j / (2 * ciL)] |= d << ((j % (2 * ciL)) << 2);
		}
	} else {
		MPI_CHK(hicap_bignum_lset(X, 0));

		for (i = 0; i < slen; i++) {
			if (i == 0 && s[i] == '-') {
				X->s = -1;
				continue;
			}

			MPI_CHK(mpi_get_digit(&d, radix, s[i]));
			MPI_CHK(hicap_bignum_mul_int(&T, X, radix));

			if (X->s == 1) {
				MPI_CHK(hicap_bignum_add_int(X, &T, d));
			} else {
				MPI_CHK(hicap_bignum_sub_int(X, &T, d));
			}
		}
	}

cleanup:

	hicap_bignum_free(&T, NULL);

	return(ret);
}
/******************************************************************************/
/*
* Import X from unsigned binary data, big endian
*/
int hicap_bignum_read_binary(mpi *X, const unsigned char *buf, int buflen)
{
	int ret, i, j, n;

	for (n = 0; n < buflen; n++)
		if (buf[n] != 0)
			break;

	MPI_CHK(hicap_bignum_grow(X, CHARS_TO_LIMBS(buflen - n)));
	MPI_CHK(hicap_bignum_lset(X, 0));

	for (i = buflen - 1, j = 0; i >= n; i--, j++)
		X->p[j / ciL] |= ((t_int) buf[i]) << ((j % ciL) << 3);

cleanup:

	return(ret);
}
/******************************************************************************/
/*
* Export X into unsigned binary data, big endian
*/
int hicap_bignum_write_binary(const mpi *X, unsigned char *buf, int buflen)
{
	int i, j, n;

	n = hicap_bignum_size(X);

	if (buflen < n)
		return(POLARSSL_ERR_MPI_BUFFER_TOO_SMALL);

	memset(buf, 0, buflen);

	for (i = buflen - 1, j = 0; n > 0; i--, j++, n--)
		buf[i] = (unsigned char)(X->p[j / ciL] >> ((j % ciL) << 3));

	return(0);
}
/******************************************************************************/
/*
* Left-shift: X <<= count
*/
int hicap_bignum_shift_l(mpi *X, int count)
{
	int ret, i, v0, t1;
	t_int r0 = 0, r1;

	v0 = count / (biL);
	t1 = count & (biL - 1);

	i = hicap_bignum_msb(X) + count;

	if (X->n * (int) biL < i)
		MPI_CHK(hicap_bignum_grow(X, BITS_TO_LIMBS(i)));

	ret = 0;

	/*
	* shift by count / limb_size
	*/
	if (v0 > 0) {
		for (i = X->n - 1; i >= v0; i--)
			X->p[i] = X->p[i - v0];

		for (; i >= 0; i--)
			X->p[i] = 0;
	}

	/*
	* shift by count % limb_size
	*/
	if (t1 > 0) {
		for (i = v0; i < X->n; i++) {
			r1 = X->p[i] >> (biL - t1);
			X->p[i] <<= t1;
			X->p[i] |= r0;
			r0 = r1;
		}
	}

cleanup:

	return(ret);
}
/******************************************************************************/
/*
* Right-shift: X >>= count
*/
int hicap_bignum_shift_r(mpi *X, int count)
{
	int i, v0, v1;
	t_int r0 = 0, r1;

	v0 = count /  biL;
	v1 = count & (biL - 1);

	/*
	* shift by count / limb_size
	*/
	if (v0 > 0) {
		for (i = 0; i < X->n - v0; i++)
			X->p[i] = X->p[i + v0];

		for (; i < X->n; i++)
			X->p[i] = 0;
	}

	/*
	* shift by count % limb_size
	*/
	if (v1 > 0) {
		for (i = X->n - 1; i >= 0; i--) {
			r1 = X->p[i] << (biL - v1);
			X->p[i] >>= v1;
			X->p[i] |= r0;
			r0 = r1;
		}
	}

	return(0);
}
/******************************************************************************/
/*
* Compare unsigned values
*/
int hicap_bignum_cmp_abs(const mpi *X, const mpi *Y)
{
	int i, j;

	for (i = X->n - 1; i >= 0; i--)
		if (X->p[i] != 0)
			break;

	for (j = Y->n - 1; j >= 0; j--)
		if (Y->p[j] != 0)
			break;

	if (i < 0 && j < 0)
		return(0);

	if (i > j) return(1);
	if (j > i) return(-1);

	for (; i >= 0; i--) {
		if (X->p[i] > Y->p[i]) return(1);
		if (X->p[i] < Y->p[i]) return(-1);
	}

	return(0);
}
/******************************************************************************/
/*
* Compare signed values
*/
int hicap_bignum_cmp_mpi(const mpi *X, const mpi *Y)
{
	int i, j;

	for (i = X->n - 1; i >= 0; i--)
		if (X->p[i] != 0)
			break;

	for (j = Y->n - 1; j >= 0; j--)
		if (Y->p[j] != 0)
			break;

	if (i < 0 && j < 0)
		return(0);

	if (i > j) return(X->s);
	if (j > i) return(-X->s);

	if (X->s > 0 && Y->s < 0) return(1);
	if (Y->s > 0 && X->s < 0) return(-1);

	for (; i >= 0; i--) {
		if (X->p[i] > Y->p[i]) return(X->s);
		if (X->p[i] < Y->p[i]) return(-X->s);
	}

	return(0);
}
/******************************************************************************/
/*
* Compare signed values
*/
int hicap_bignum_cmp_int(const mpi *X, int z)
{
	mpi Y;
	t_int p[1];

	*p  = (z < 0) ? -z : z;
	Y.s = (z < 0) ? -1 : 1;
	Y.n = 1;
	Y.p = p;

	return(hicap_bignum_cmp_mpi(X, &Y));
}
/******************************************************************************/
/*
* Unsigned addition: X = |A| + |B|  (HAC 14.7)
*/
int hicap_bignum_add_abs(mpi *X, const mpi *A, const mpi *B)
{
	int ret, i, j;
	t_int *o, *p, c;

	if (X == B) {
		const mpi *T = A; A = X; B = T;
	}

	if (X != A)
		MPI_CHK(hicap_bignum_copy(X, A));

	/*
	* X should always be positive as a result of unsigned additions.
	*/
	X->s = 1;

	for (j = B->n - 1; j >= 0; j--)
		if (B->p[j] != 0)
			break;

	MPI_CHK(hicap_bignum_grow(X, j + 1));

	o = B->p; p = X->p; c = 0;

	for (i = 0; i <= j; i++, o++, p++) {
		*p +=  c; c  = (*p <  c);
		*p += *o; c += (*p < *o);
	}

	while (c != 0) {
		if (i >= X->n) {
			MPI_CHK(hicap_bignum_grow(X, i + 1));
			p = X->p + i;
		}

		*p += c; c = (*p < c); i++;
	}

cleanup:
	return(ret);
}
/******************************************************************************/
/*
* Helper for mpi substraction
*/
static void mpi_sub_hlp(int n, t_int *s, t_int *d)
{
	int i;
	t_int c, z;

	for (i = c = 0; i < n; i++, s++, d++) {
		z = (*d <  c);     *d -=  c;
		c = (*d < *s) + z; *d -= *s;
	}

	while (c != 0) {
		z = (*d < c); *d -= c;
		c = z; i++; d++;
	}
}
/******************************************************************************/
/*
* Unsigned substraction: X = |A| - |B|  (HAC 14.9)
*/
int hicap_bignum_sub_abs(mpi *X, const mpi *A, const mpi *B)
{
	mpi TB;
	int ret, n;

	if (hicap_bignum_cmp_abs(A, B) < 0)
		return(POLARSSL_ERR_MPI_NEGATIVE_VALUE);

	hicap_bignum_init(&TB, NULL);

	if (X == B) {
		MPI_CHK(hicap_bignum_copy(&TB, B));
		B = &TB;
	}

	if (X != A)
		MPI_CHK(hicap_bignum_copy(X, A));

	/*
	* X should always be positive as a result of unsigned substractions.
	*/
	X->s = 1;

	ret = 0;

	for (n = B->n - 1; n >= 0; n--)
		if (B->p[n] != 0)
			break;

	mpi_sub_hlp(n + 1, B->p, X->p);

cleanup:

	hicap_bignum_free(&TB, NULL);

	return(ret);
}
/******************************************************************************/
/*
* Signed addition: X = A + B
*/
int hicap_bignum_add_mpi(mpi *X, const mpi *A, const mpi *B)
{
	int ret, s = A->s;

	if (A->s * B->s < 0) {
		if (hicap_bignum_cmp_abs(A, B) >= 0) {
			MPI_CHK(hicap_bignum_sub_abs(X, A, B));
			X->s =  s;
		} else {
			MPI_CHK(hicap_bignum_sub_abs(X, B, A));
			X->s = -s;
		}
	} else {
		MPI_CHK(hicap_bignum_add_abs(X, A, B));
		X->s = s;
	}

cleanup:

	return(ret);
}
/******************************************************************************/
/*
* Signed substraction: X = A - B
*/
int hicap_bignum_sub_mpi(mpi *X, const mpi *A, const mpi *B)
{
	int ret, s = A->s;

	if (A->s * B->s > 0) {
		if (hicap_bignum_cmp_abs(A, B) >= 0) {
			MPI_CHK(hicap_bignum_sub_abs(X, A, B));
			X->s =  s;
		} else {
			MPI_CHK(hicap_bignum_sub_abs(X, B, A));
			X->s = -s;
		}
	} else {
		MPI_CHK(hicap_bignum_add_abs(X, A, B));
		X->s = s;
	}

cleanup:

	return(ret);
}
/******************************************************************************/
/*
* Signed addition: X = A + b
*/
int hicap_bignum_add_int(mpi *X, const mpi *A, int b)
{
	mpi _B;
	t_int p[1];

	p[0] = (b < 0) ? -b : b;
	_B.s = (b < 0) ? -1 : 1;
	_B.n = 1;
	_B.p = p;

	return(hicap_bignum_add_mpi(X, A, &_B));
}
/******************************************************************************/
/*
* Signed substraction: X = A - b
*/
int hicap_bignum_sub_int(mpi *X, const mpi *A, int b)
{
	mpi _B;
	t_int p[1];

	p[0] = (b < 0) ? -b : b;
	_B.s = (b < 0) ? -1 : 1;
	_B.n = 1;
	_B.p = p;

	return(hicap_bignum_sub_mpi(X, A, &_B));
}
/******************************************************************************/
/*
* Helper for mpi multiplication
*/ 
static void mpi_mul_hlp(int i, t_int *s, t_int *d, t_int b)
{
	t_int c = 0, t = 0;

	for (; i >= 16; i -= 16) {
		MULADDC_INIT
			MULADDC_CORE   MULADDC_CORE
			MULADDC_CORE   MULADDC_CORE
			MULADDC_CORE   MULADDC_CORE
			MULADDC_CORE   MULADDC_CORE

			MULADDC_CORE   MULADDC_CORE
			MULADDC_CORE   MULADDC_CORE
			MULADDC_CORE   MULADDC_CORE
			MULADDC_CORE   MULADDC_CORE
			MULADDC_STOP
	}

	for (; i >= 8; i -= 8) {
		MULADDC_INIT
			MULADDC_CORE   MULADDC_CORE
			MULADDC_CORE   MULADDC_CORE

			MULADDC_CORE   MULADDC_CORE
			MULADDC_CORE   MULADDC_CORE
			MULADDC_STOP
	}

	for (; i > 0; i--) {
		MULADDC_INIT
			MULADDC_CORE
			MULADDC_STOP
	}

	t++;

	do {
		*d += c; c = (*d < c); d++;
	} while (c != 0);
}
/******************************************************************************/
/*
* Baseline multiplication: X = A * B  (HAC 14.12)
*/
int hicap_bignum_mul_mpi(mpi *X, const mpi *A, const mpi *B)
{
	int ret, i, j;
	mpi TA, TB;

	hicap_bignum_init(&TA, &TB, NULL);

	if (X == A) {
		MPI_CHK(hicap_bignum_copy(&TA, A));
		A = &TA;
	}
	if (X == B) {
		MPI_CHK(hicap_bignum_copy(&TB, B));
		B = &TB;
	}

	for (i = A->n - 1; i >= 0; i--)
		if (A->p[i] != 0)
			break;

	for (j = B->n - 1; j >= 0; j--)
		if (B->p[j] != 0)
			break;

	MPI_CHK(hicap_bignum_grow(X, i + j + 2));
	MPI_CHK(hicap_bignum_lset(X, 0));

	for (i++; j >= 0; j--)
		mpi_mul_hlp(i, A->p, X->p + j, B->p[j]);

	X->s = A->s * B->s;

cleanup:

	hicap_bignum_free(&TB, &TA, NULL);

	return(ret);
}
/******************************************************************************/
/*
* Baseline multiplication: X = A * b
*/
int hicap_bignum_mul_int(mpi *X, const mpi *A, t_int b)
{
	mpi _B;
	t_int p[1];

	_B.s = 1;
	_B.n = 1;
	_B.p = p;
	p[0] = b;

	return(hicap_bignum_mul_mpi(X, A, &_B));
}
/******************************************************************************/
/*
* Division by mpi: A = Q * B + R  (HAC 14.20)
*/
int hicap_bignum_div_mpi(mpi *Q, mpi *R, const mpi *A, const mpi *B)
{
	int ret, i, n, t, k;
	mpi X, Y, Z, T1, T2;

	if (hicap_bignum_cmp_int(B, 0) == 0)
		return(POLARSSL_ERR_MPI_DIVISION_BY_ZERO);

	hicap_bignum_init(&X, &Y, &Z, &T1, &T2, NULL);

	if (hicap_bignum_cmp_abs(A, B) < 0) {
		if (Q != NULL) MPI_CHK(hicap_bignum_lset(Q, 0));
		if (R != NULL) MPI_CHK(hicap_bignum_copy(R, A));
		return(0);
	}

	MPI_CHK(hicap_bignum_copy(&X, A));
	MPI_CHK(hicap_bignum_copy(&Y, B));
	X.s = Y.s = 1;

	MPI_CHK(hicap_bignum_grow(&Z, A->n + 2));
	MPI_CHK(hicap_bignum_lset(&Z,  0));
	MPI_CHK(hicap_bignum_grow(&T1, 2));
	MPI_CHK(hicap_bignum_grow(&T2, 3));

	k = hicap_bignum_msb(&Y) % biL;
	if (k < (int) biL - 1) {
		k = biL - 1 - k;
		MPI_CHK(hicap_bignum_shift_l(&X, k));
		MPI_CHK(hicap_bignum_shift_l(&Y, k));
	}
	else k = 0;

	n = X.n - 1;
	t = Y.n - 1;
	hicap_bignum_shift_l(&Y, biL * (n - t));

	while (hicap_bignum_cmp_mpi(&X, &Y) >= 0) {
		Z.p[n - t]++;
		hicap_bignum_sub_mpi(&X, &X, &Y);
	}
	hicap_bignum_shift_r(&Y, biL * (n - t));

	for (i = n; i > t ; i--) {
		if (X.p[i] >= Y.p[t])
			Z.p[i - t - 1] = ~0;
		else {
			/*
			* __udiv_qrnnd_c, from gmp/longlong.h
			*/
			t_int q0, q1, r0, r1;
			t_int d0, d1, d, m;

			d  = Y.p[t];
			d0 = (d << biH) >> biH;
			d1 = (d >> biH);

			q1 = X.p[i] / d1;
			r1 = X.p[i] - d1 * q1;
			r1 <<= biH;
			r1 |= (X.p[i - 1] >> biH);

			m = q1 * d0;
			if (r1 < m) {
				q1--, r1 += d;
				while (r1 >= d && r1 < m)
					q1--, r1 += d;
			}
			r1 -= m;

			q0 = r1 / d1;
			r0 = r1 - d1 * q0;
			r0 <<= biH;
			r0 |= (X.p[i - 1] << biH) >> biH;

			m = q0 * d0;
			if (r0 < m) {
				q0--, r0 += d;
				while (r0 >= d && r0 < m)
					q0--, r0 += d;
			}
			r0 -= m;

			Z.p[i - t - 1] = (q1 << biH) | q0;
		}

		Z.p[i - t - 1]++;
		do {
			Z.p[i - t - 1]--;

			MPI_CHK(hicap_bignum_lset(&T1, 0));
			T1.p[0] = (t < 1) ? 0 : Y.p[t - 1];
			T1.p[1] = Y.p[t];
			MPI_CHK(hicap_bignum_mul_int(&T1, &T1, Z.p[i - t - 1]));

			MPI_CHK(hicap_bignum_lset(&T2, 0));
			T2.p[0] = (i < 2) ? 0 : X.p[i - 2];
			T2.p[1] = (i < 1) ? 0 : X.p[i - 1];
			T2.p[2] = X.p[i];
		} while (hicap_bignum_cmp_mpi(&T1, &T2) > 0);

		MPI_CHK(hicap_bignum_mul_int(&T1, &Y, Z.p[i - t - 1]));
		MPI_CHK(hicap_bignum_shift_l(&T1,  biL * (i - t - 1)));
		MPI_CHK(hicap_bignum_sub_mpi(&X, &X, &T1));

		if (hicap_bignum_cmp_int(&X, 0) < 0) {
			MPI_CHK(hicap_bignum_copy(&T1, &Y));
			MPI_CHK(hicap_bignum_shift_l(&T1, biL * (i - t - 1)));
			MPI_CHK(hicap_bignum_add_mpi(&X, &X, &T1));
			Z.p[i - t - 1]--;
		}
	}

	if (Q != NULL) {
		hicap_bignum_copy(Q, &Z);
		Q->s = A->s * B->s;
	}

	if (R != NULL) {
		hicap_bignum_shift_r(&X, k);
		hicap_bignum_copy(R, &X);

		R->s = A->s;
		if (hicap_bignum_cmp_int(R, 0) == 0)
			R->s = 1;
	}

cleanup:

	hicap_bignum_free(&X, &Y, &Z, &T1, &T2, NULL);

	return(ret);
}
/******************************************************************************/
/*
* Modulo: R = A mod B
*/
int hicap_bignum_mod_mpi(mpi *R, const mpi *A, const mpi *B)
{
	int ret;

	if (hicap_bignum_cmp_int(B, 0) < 0)
		return POLARSSL_ERR_MPI_NEGATIVE_VALUE;

	MPI_CHK(hicap_bignum_div_mpi(NULL, R, A, B));

	while (hicap_bignum_cmp_int(R, 0) < 0)
		MPI_CHK(hicap_bignum_add_mpi(R, R, B));

	while (hicap_bignum_cmp_mpi(R, B) >= 0)
		MPI_CHK(hicap_bignum_sub_mpi(R, R, B));

cleanup:

	return(ret);
}
/******************************************************************************/
/*
* Modulo: r = A mod b
*/
int hicap_bignum_mod_int(t_int *r, const mpi *A, int b)
{
	int i;
	t_int x, y, z;

	if (b == 0)
		return(POLARSSL_ERR_MPI_DIVISION_BY_ZERO);

	if (b < 0)
		return POLARSSL_ERR_MPI_NEGATIVE_VALUE;

	/*
	* handle trivial cases
	*/
	if (b == 1) {
		*r = 0;
		return(0);
	}

	if (b == 2) {
		*r = A->p[0] & 1;
		return(0);
	}

	/*
	* general case
	*/
	for (i = A->n - 1, y = 0; i >= 0; i--) {
		x  = A->p[i];
		y  = (y << biH) | (x >> biH);
		z  = y / b;
		y -= z * b;

		x <<= biH;
		y  = (y << biH) | (x >> biH);
		z  = y / b;
		y -= z * b;
	}

	/*
	* If A is negative, then the current y represents a negative value.
	* Flipping it to the positive side.
	*/
	if (A->s < 0 && y != 0)
		y = b - y;

	*r = y;

	return(0);
}
/******************************************************************************/
/*
* Fast Montgomery initialization (thanks to Tom St Denis)
*/
static void mpi_montg_init(t_int *mm, const mpi *N)
{
	t_int x, m0 = N->p[0];

	x  = m0;
	x += ((m0 + 2) & 4) << 1;
	x *= (2 - (m0 * x));

	if (biL >= 16) x *= (2 - (m0 * x));
	if (biL >= 32) x *= (2 - (m0 * x));
	if (biL >= 64) x *= (2 - (m0 * x));

	*mm = ~x + 1;
}
/******************************************************************************/
/*
* Montgomery multiplication: A = A * B * R^-1 mod N  (HAC 14.36)
*/
static void mpi_montmul(mpi *A, const mpi *B, const mpi *N, t_int mm, const mpi *T)
{
	int i, n, m;
	t_int u0, u1, *d;

	memset(T->p, 0, T->n * ciL);

	d = T->p;
	n = N->n;
	m = (B->n < n) ? B->n : n;

	for (i = 0; i < n; i++) {
		/*
		* T = (T + u0*B + u1*N) / 2^biL
		*/
		u0 = A->p[i];
		u1 = (d[0] + u0 * B->p[0]) * mm;

		mpi_mul_hlp(m, B->p, d, u0);
		mpi_mul_hlp(n, N->p, d, u1);

		*d++ = u0; d[n + 1] = 0;
	}

	memcpy(A->p, d, (n + 1) * ciL);

	if (hicap_bignum_cmp_abs(A, N) >= 0)
		mpi_sub_hlp(n, N->p, A->p);
	else
		/* prevent timing attacks */
		mpi_sub_hlp(n, A->p, T->p);
}
/******************************************************************************/
/*
* Montgomery reduction: A = A * R^-1 mod N
*/
static void mpi_montred(mpi *A, const mpi *N, t_int mm, const mpi *T)
{
	t_int z = 1;
	mpi U;

	U.n = U.s = z;
	U.p = &z;

	mpi_montmul(A, &U, N, mm, T);
}
/******************************************************************************/
/*
* Sliding-window exponentiation: X = A^E mod N  (HAC 14.85)
*/
int hicap_bignum_exp_mod(mpi *X, const mpi *A, const mpi *E, const mpi *N, mpi *_RR)
{
	int ret, i, j, wsize, wbits;
	int bufsize, nblimbs, nbits;
	t_int ei, mm, state;
	mpi RR, T, W[64];

	if (hicap_bignum_cmp_int(N, 0) < 0 || (N->p[0] & 1) == 0)
		return(POLARSSL_ERR_MPI_BAD_INPUT_DATA);

	/*
	* Init temps and window size
	*/
	mpi_montg_init(&mm, N);
	hicap_bignum_init(&RR, &T, NULL);
	memset(W, 0, sizeof(W));

	i = hicap_bignum_msb(E);

	wsize = (i > 671) ? 6 : (i > 239) ? 5 :
		(i >  79) ? 4 : (i >  23) ? 3 : 1;

	j = N->n + 1;
	MPI_CHK(hicap_bignum_grow(X, j));
	MPI_CHK(hicap_bignum_grow(&W[1],  j));
	MPI_CHK(hicap_bignum_grow(&T, j * 2));

	/*
	* If 1st call, pre-compute R^2 mod N
	*/
	if (_RR == NULL || _RR->p == NULL) {
		MPI_CHK(hicap_bignum_lset(&RR, 1));
		MPI_CHK(hicap_bignum_shift_l(&RR, N->n * 2 * biL));
		MPI_CHK(hicap_bignum_mod_mpi(&RR, &RR, N));

		if (_RR != NULL)
			memcpy(_RR, &RR, sizeof(mpi));
	} else
		memcpy(&RR, _RR, sizeof(mpi));

	/*
	* W[1] = A * R^2 * R^-1 mod N = A * R mod N
	*/
	if (hicap_bignum_cmp_mpi(A, N) >= 0)
		hicap_bignum_mod_mpi(&W[1], A, N);
	else
		hicap_bignum_copy(&W[1], A);

	mpi_montmul(&W[1], &RR, N, mm, &T);

	/*
	* X = R^2 * R^-1 mod N = R mod N
	*/
	MPI_CHK(hicap_bignum_copy(X, &RR));
	mpi_montred(X, N, mm, &T);

	if (wsize > 1) {
		/*
		* W[1 << (wsize - 1)] = W[1] ^ (wsize - 1)
		*/
		j =  1 << (wsize - 1);

		MPI_CHK(hicap_bignum_grow(&W[j], N->n + 1));
		MPI_CHK(hicap_bignum_copy(&W[j], &W[1]));

		for (i = 0; i < wsize - 1; i++)
			mpi_montmul(&W[j], &W[j], N, mm, &T);

		/*
		* W[i] = W[i - 1] * W[1]
		*/
		for (i = j + 1; i < (1 << wsize); i++) {
			MPI_CHK(hicap_bignum_grow(&W[i], N->n + 1));
			MPI_CHK(hicap_bignum_copy(&W[i], &W[i - 1]));

			mpi_montmul(&W[i], &W[1], N, mm, &T);
		}
	}

	nblimbs = E->n;
	bufsize = 0;
	nbits   = 0;
	wbits   = 0;
	state   = 0;

	while (1) {
		if (bufsize == 0) {
			if (nblimbs-- == 0)
				break;

			bufsize = sizeof(t_int) << 3;
		}

		bufsize--;

		ei = (E->p[nblimbs] >> bufsize) & 1;

		/*
		* skip leading 0s
		*/
		if (ei == 0 && state == 0)
			continue;

		if (ei == 0 && state == 1) {
			/*
			* out of window, square X
			*/
			mpi_montmul(X, X, N, mm, &T);
			continue;
		}

		/*
		* add ei to current window
		*/
		state = 2;

		nbits++;
		wbits |= (ei << (wsize - nbits));

		if (nbits == wsize) {
			/*
			* X = X^wsize R^-1 mod N
			*/
			for (i = 0; i < wsize; i++)
				mpi_montmul(X, X, N, mm, &T);

			/*
			* X = X * W[wbits] R^-1 mod N
			*/
			mpi_montmul(X, &W[wbits], N, mm, &T);

			state--;
			nbits = 0;
			wbits = 0;
		}
	}

	/*
	* process the remaining bits
	*/
	for (i = 0; i < nbits; i++) {
		mpi_montmul(X, X, N, mm, &T);

		wbits <<= 1;

		if ((wbits & (1 << wsize)) != 0)
			mpi_montmul(X, &W[1], N, mm, &T);
	}

	/*
	* X = A^E * R * R^-1 mod N = A^E mod N
	*/
	mpi_montred(X, N, mm, &T);

cleanup:

	for (i = (1 << (wsize - 1)); i < (1 << wsize); i++)
		hicap_bignum_free(&W[i], NULL);

	if (_RR != NULL)
		hicap_bignum_free(&W[1], &T, NULL);
	else
		hicap_bignum_free(&W[1], &T, &RR, NULL);

	return(ret);
}
/******************************************************************************/
/*
* Greatest common divisor: G = gcd(A, B)  (HAC 14.54)
*/
int hicap_bignum_gcd(mpi *G, const mpi *A, const mpi *B)
{
	int ret, lz, lzt;
	mpi TG, TA, TB;

	hicap_bignum_init(&TG, &TA, &TB, NULL);

	MPI_CHK(hicap_bignum_copy(&TA, A));
	MPI_CHK(hicap_bignum_copy(&TB, B));

	lz = hicap_bignum_lsb(&TA);
	lzt = hicap_bignum_lsb(&TB);

	if (lzt < lz)
		lz = lzt;

	MPI_CHK(hicap_bignum_shift_r(&TA, lz));
	MPI_CHK(hicap_bignum_shift_r(&TB, lz));

	TA.s = TB.s = 1;

	while (hicap_bignum_cmp_int(&TA, 0) != 0) {
		MPI_CHK(hicap_bignum_shift_r(&TA, hicap_bignum_lsb(&TA)));
		MPI_CHK(hicap_bignum_shift_r(&TB, hicap_bignum_lsb(&TB)));

		if (hicap_bignum_cmp_mpi(&TA, &TB) >= 0) {
			MPI_CHK(hicap_bignum_sub_abs(&TA, &TA, &TB));
			MPI_CHK(hicap_bignum_shift_r(&TA, 1));
		} else {
			MPI_CHK(hicap_bignum_sub_abs(&TB, &TB, &TA));
			MPI_CHK(hicap_bignum_shift_r(&TB, 1));
		}
	}

	MPI_CHK(hicap_bignum_shift_l(&TB, lz));
	MPI_CHK(hicap_bignum_copy(G, &TB));

cleanup:

	hicap_bignum_free(&TB, &TA, &TG, NULL);

	return(ret);
}
/******************************************************************************/

static const int small_prime[] =
{
	3,    5,    7,   11,   13,   17,   19,   23,
	29,   31,   37,   41,   43,   47,   53,   59,
	61,   67,   71,   73,   79,   83,   89,   97,
	101,  103,  107,  109,  113,  127,  131,  137,
	139,  149,  151,  157,  163,  167,  173,  179,
	181,  191,  193,  197,  199,  211,  223,  227,
	229,  233,  239,  241,  251,  257,  263,  269,
	271,  277,  281,  283,  293,  307,  311,  313,
	317,  331,  337,  347,  349,  353,  359,  367,
	373,  379,  383,  389,  397,  401,  409,  419,
	421,  431,  433,  439,  443,  449,  457,  461,
	463,  467,  479,  487,  491,  499,  503,  509,
	521,  523,  541,  547,  557,  563,  569,  571,
	577,  587,  593,  599,  601,  607,  613,  617,
	619,  631,  641,  643,  647,  653,  659,  661,
	673,  677,  683,  691,  701,  709,  719,  727,
	733,  739,  743,  751,  757,  761,  769,  773,
	787,  797,  809,  811,  821,  823,  827,  829,
	839,  853,  857,  859,  863,  877,  881,  883,
	887,  907,  911,  919,  929,  937,  941,  947,
	953,  967,  971,  977,  983,  991,  997, -103
};
/******************************************************************************/
/*
* Miller-Rabin primality test  (HAC 4.24)
*/
int hicap_bignum_is_prime(mpi *X, int (*f_rng)(void *), void *p_rng)
{
	int ret, i, j, n, s, xs;
	mpi W, R, T, A, RR;
	unsigned char *p;

	if (hicap_bignum_cmp_int(X, 0) == 0 ||
		hicap_bignum_cmp_int(X, 1) == 0)
		return(POLARSSL_ERR_MPI_NOT_ACCEPTABLE);

	if (hicap_bignum_cmp_int(X, 2) == 0)
		return(0);

	hicap_bignum_init(&W, &R, &T, &A, &RR, NULL);

	xs = X->s; X->s = 1;

	/*
	* test trivial factors first
	*/
	if ((X->p[0] & 1) == 0)
		return(POLARSSL_ERR_MPI_NOT_ACCEPTABLE);

	for (i = 0; small_prime[i] > 0; i++) {
		t_int r;

		if (hicap_bignum_cmp_int(X, small_prime[i]) <= 0)
			return(0);

		MPI_CHK(hicap_bignum_mod_int(&r, X, small_prime[i]));

		if (r == 0)
			return(POLARSSL_ERR_MPI_NOT_ACCEPTABLE);
	}

	/*
	* W = |X| - 1
	* R = W >> lsb(W)
	*/
	MPI_CHK(hicap_bignum_sub_int(&W, X, 1));
	s = hicap_bignum_lsb(&W);
	MPI_CHK(hicap_bignum_copy(&R, &W));
	MPI_CHK(hicap_bignum_shift_r(&R, s));

	i = hicap_bignum_msb(X);
	/*
	* HAC, table 4.4
	*/
	n = ((i >= 1300) ?  2 : (i >=  850) ?  3 :
		(i >=  650) ?  4 : (i >=  350) ?  8 :
		(i >=  250) ? 12 : (i >=  150) ? 18 : 27);

	for (i = 0; i < n; i++) {
		/*
		* pick a random A, 1 < A < |X| - 1
		*/
		MPI_CHK(hicap_bignum_grow(&A, X->n));

		p = (unsigned char *) A.p;
		for (j = 0; j < A.n * ciL; j++)
			*p++ = (unsigned char) f_rng(p_rng);

		j = hicap_bignum_msb(&A) - hicap_bignum_msb(&W);
		MPI_CHK(hicap_bignum_shift_r(&A, j + 1));
		A.p[0] |= 3;

		/*
		* A = A^R mod |X|
		*/
		MPI_CHK(hicap_bignum_exp_mod(&A, &A, &R, X, &RR));

		if (hicap_bignum_cmp_mpi(&A, &W) == 0 ||
			hicap_bignum_cmp_int(&A,  1) == 0)
			continue;

		j = 1;
		while (j < s && hicap_bignum_cmp_mpi(&A, &W) != 0) {
			/*
			* A = A * A mod |X|
			*/
			MPI_CHK(hicap_bignum_mul_mpi(&T, &A, &A));
			MPI_CHK(hicap_bignum_mod_mpi(&A, &T, X));

			if (hicap_bignum_cmp_int(&A, 1) == 0)
				break;

			j++;
		}

		/*
		* not prime if A != |X| - 1 or A == 1
		*/
		if (hicap_bignum_cmp_mpi(&A, &W) != 0 ||
		    hicap_bignum_cmp_int(&A,  1) == 0) {
			ret = POLARSSL_ERR_MPI_NOT_ACCEPTABLE;
			break;
		}
	}

cleanup:

	X->s = xs;

	hicap_bignum_free(&RR, &A, &T, &R, &W, NULL);

	return(ret);
}
