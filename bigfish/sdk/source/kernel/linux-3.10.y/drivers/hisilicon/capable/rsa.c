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

#include "rsa.h"

/******************************************************************************/

int hicap_rsa_init(rsa_context *rsa, int padding, int hash_id)
{
	memset(rsa, 0, sizeof(rsa_context));

	rsa->padding = padding;
	rsa->hash_id = hash_id;

	rsa->sz_buf = 4096;

	rsa->buf = hicap_vmalloc(rsa->sz_buf);
	if (!rsa->buf)
		return -1;

	return 0;
}
/******************************************************************************/
/*
* Check a public RSA key
*/
int hicap_rsa_check_pubkey(const rsa_context *ctx)
{
	if (!ctx->N.p || !ctx->E.p)
		return (POLARSSL_ERR_RSA_KEY_CHECK_FAILED);

	if ((ctx->N.p[0] & 1) == 0 || (ctx->E.p[0] & 1) == 0)
		return (POLARSSL_ERR_RSA_KEY_CHECK_FAILED);

	if (hicap_bignum_msb(&ctx->N) < 128 || hicap_bignum_msb(&ctx->N) > 4096)
		return (POLARSSL_ERR_RSA_KEY_CHECK_FAILED);

	if (hicap_bignum_msb(&ctx->E) < 2 || hicap_bignum_msb(&ctx->E) > 64)
		return (POLARSSL_ERR_RSA_KEY_CHECK_FAILED);

	return (0);
}
/******************************************************************************/
/*
* Check a private RSA key
*/
int hicap_rsa_check_privkey(const rsa_context *ctx)
{
	int ret;
	mpi PQ, DE, P1, Q1, H, I, G, G2, L1, L2;

	if ((ret = hicap_rsa_check_pubkey(ctx)) != 0)
		return (ret);

	if (!ctx->P.p || !ctx->Q.p || !ctx->D.p)
		return (POLARSSL_ERR_RSA_KEY_CHECK_FAILED);

	hicap_bignum_init(&PQ, &DE, &P1, &Q1, &H, &I, &G, &G2, &L1, &L2, NULL);

	MPI_CHK(hicap_bignum_mul_mpi(&PQ, &ctx->P, &ctx->Q));
	MPI_CHK(hicap_bignum_mul_mpi(&DE, &ctx->D, &ctx->E));
	MPI_CHK(hicap_bignum_sub_int(&P1, &ctx->P, 1));
	MPI_CHK(hicap_bignum_sub_int(&Q1, &ctx->Q, 1));
	MPI_CHK(hicap_bignum_mul_mpi(&H, &P1, &Q1));
	MPI_CHK(hicap_bignum_gcd(&G, &ctx->E, &H));

	MPI_CHK(hicap_bignum_gcd(&G2, &P1, &Q1));
	MPI_CHK(hicap_bignum_div_mpi(&L1, &L2, &H, &G2));
	MPI_CHK(hicap_bignum_mod_mpi(&I, &DE, &L1));

	/*
	* Check for a valid PKCS1v2 private key
	*/
	if (hicap_bignum_cmp_mpi(&PQ, &ctx->N) == 0 &&
	    hicap_bignum_cmp_int(&L2, 0) == 0 &&
	    hicap_bignum_cmp_int(&I, 1) == 0 &&
	    hicap_bignum_cmp_int(&G, 1) == 0) {
		hicap_bignum_free(&G, &I, &H, &Q1, &P1, &DE, &PQ, &G2, &L1, &L2, NULL);
		return (0);
	}

cleanup:
	hicap_bignum_free(&G, &I, &H, &Q1, &P1, &DE, &PQ, &G2, &L1, &L2, NULL);

	return (POLARSSL_ERR_RSA_KEY_CHECK_FAILED | ret);
}
/******************************************************************************/

/*
* Do an RSA public key operation
*/
int hicap_rsa_public(rsa_context *ctx, const unsigned char *input,
	       unsigned char *output)
{
	int ret, olen;
	mpi T;

	hicap_bignum_init(&T, NULL);

	MPI_CHK(hicap_bignum_read_binary(&T, input, ctx->len));

	if (hicap_bignum_cmp_mpi(&T, &ctx->N) >= 0) {
		hicap_bignum_free(&T, NULL);
		return (POLARSSL_ERR_RSA_BAD_INPUT_DATA);
	}

	olen = ctx->len;
	MPI_CHK(hicap_bignum_exp_mod(&T, &T, &ctx->E, &ctx->N, &ctx->RN));
	MPI_CHK(hicap_bignum_write_binary(&T, output, olen));

cleanup:

	hicap_bignum_free(&T, NULL);

	if (ret != 0)
		return (POLARSSL_ERR_RSA_PUBLIC_FAILED | ret);

	return (0);
}
/******************************************************************************/
/*
* Do an RSA private key operation
*/
int hicap_rsa_private(rsa_context *ctx, const unsigned char *input,
		unsigned char *output)
{
	int ret, olen;
	mpi T, T1, T2;

	hicap_bignum_init(&T, &T1, &T2, NULL);

	MPI_CHK(hicap_bignum_read_binary(&T, input, ctx->len));

	if (hicap_bignum_cmp_mpi(&T, &ctx->N) >= 0) {
		hicap_bignum_free(&T, NULL);
		return (POLARSSL_ERR_RSA_BAD_INPUT_DATA);
	}

	MPI_CHK(hicap_bignum_exp_mod(&T, &T, &ctx->D, &ctx->N, &ctx->RN));

	olen = ctx->len;
	MPI_CHK(hicap_bignum_write_binary(&T, output, olen));

cleanup:

	hicap_bignum_free(&T, &T1, &T2, NULL);

	if (ret != 0)
		return (POLARSSL_ERR_RSA_PRIVATE_FAILED | ret);

	return (0);
}
/******************************************************************************/
/*
* Add the message padding, then do an RSA operation
*/
int hicap_rsa_pkcs1_encrypt(rsa_context *ctx, int (*f_rng)(void *), void *p_rng,
			    int mode, int  ilen, const unsigned char *input,
			    unsigned char *output)
{
	int nb_pad, olen;
	unsigned char *p = output;

	olen = ctx->len;

	switch(ctx->padding) {
	case RSA_PKCS_V15:

		if (ilen < 0 || olen < ilen + 11 || f_rng == NULL) {
			return (POLARSSL_ERR_RSA_BAD_INPUT_DATA);
		}

		nb_pad = olen - 3 - ilen;

		*p++ = 0;
		*p++ = RSA_CRYPT;

		while (nb_pad-- > 0) {
			int rng_dl = 100;

			do {
				*p = (unsigned char) f_rng(p_rng);
			} while (*p == 0 && --rng_dl);

			if (rng_dl == 0) {
				return POLARSSL_ERR_RSA_RNG_FAILED;
			}

			p++;
		}
		*p++ = 0;
		memcpy(p, input, ilen);
		break;

	default:

		return (POLARSSL_ERR_RSA_INVALID_PADDING);
	}

	return ((mode == RSA_PUBLIC)
		? hicap_rsa_public(ctx, output, output)
		: hicap_rsa_private(ctx, output, output));
}
/******************************************************************************/
/*
* Do an RSA operation, then remove the message padding
*/
int hicap_rsa_pkcs1_decrypt(rsa_context *ctx, int mode, int *olen,
			    const unsigned char *input,
			    unsigned char *output, int output_max_len)
{
	int ret, ilen;
	unsigned char *p;
	unsigned char *buf = (unsigned char *)ctx->buf;

	ilen = ctx->len;

	if (ilen < 16 || ilen > (int) ctx->sz_buf)
		return (POLARSSL_ERR_RSA_BAD_INPUT_DATA);

	ret = (mode == RSA_PUBLIC)
		? hicap_rsa_public(ctx, input, buf)
		: hicap_rsa_private(ctx, input, buf);

	if (ret != 0)
		return (ret);

	p = buf;

	switch(ctx->padding) {
	case RSA_PKCS_V15:
		if (*p++ != 0 || *p++ != RSA_CRYPT)
			return (POLARSSL_ERR_RSA_INVALID_PADDING);

		while (*p != 0) {
			if (p >= buf + ilen - 1)
				return (POLARSSL_ERR_RSA_INVALID_PADDING);
			p++;
		}
		p++;
		break;

	default:
		return (POLARSSL_ERR_RSA_INVALID_PADDING);
	}

	if (ilen - (int)(p - buf) > output_max_len)
		return (POLARSSL_ERR_RSA_OUTPUT_TOO_LARGE);

	*olen = ilen - (int)(p - buf);
	memcpy(output, p, *olen);

	return (0);
}
/******************************************************************************/
/*
* Do an RSA operation to sign the message digest
*/
int hicap_rsa_pkcs1_sign(rsa_context *ctx, int mode, int hash_id, int hashlen,
		   const unsigned char *hash, unsigned char *sig)
{
	int nb_pad, olen;
	unsigned char *p = sig;

	olen = ctx->len;

	switch(ctx->padding) {
	case RSA_PKCS_V15:

		switch(hash_id) {
		case SIG_RSA_RAW:
			nb_pad = olen - 3 - hashlen;
			break;

		case SIG_RSA_MD2:
		case SIG_RSA_MD4:
		case SIG_RSA_MD5:
			nb_pad = olen - 3 - 34;
			break;

		case SIG_RSA_SHA1:
			nb_pad = olen - 3 - 35;
			break;

		case SIG_RSA_SHA224:
			nb_pad = olen - 3 - 47;
			break;

		case SIG_RSA_SHA256:
			nb_pad = olen - 3 - 51;
			break;

		case SIG_RSA_SHA384:
			nb_pad = olen - 3 - 67;
			break;

		case SIG_RSA_SHA512:
			nb_pad = olen - 3 - 83;
			break;


		default:
			return (POLARSSL_ERR_RSA_BAD_INPUT_DATA);
		}

		if (nb_pad < 8)
			return (POLARSSL_ERR_RSA_BAD_INPUT_DATA);

		*p++ = 0;
		*p++ = RSA_SIGN;
		memset(p, 0xFF, nb_pad);
		p += nb_pad;
		*p++ = 0;
		break;

	default:
		return (POLARSSL_ERR_RSA_INVALID_PADDING);
	}

	switch(hash_id) {
	case SIG_RSA_RAW:
		memcpy(p, hash, hashlen);
		break;

	case SIG_RSA_MD2:
		memcpy(p, ASN1_HASH_MDX, 18);
		memcpy(p + 18, hash, 16);
		p[13] = 2; break;

	case SIG_RSA_MD4:
		memcpy(p, ASN1_HASH_MDX, 18);
		memcpy(p + 18, hash, 16);
		p[13] = 4; break;

	case SIG_RSA_MD5:
		memcpy(p, ASN1_HASH_MDX, 18);
		memcpy(p + 18, hash, 16);
		p[13] = 5; break;

	case SIG_RSA_SHA1:
		memcpy(p, ASN1_HASH_SHA1, 15);
		memcpy(p + 15, hash, 20);
		break;

	case SIG_RSA_SHA224:
		memcpy(p, ASN1_HASH_SHA2X, 19);
		memcpy(p + 19, hash, 28);
		p[1] += 28; p[14] = 4; p[18] += 28; break;

	case SIG_RSA_SHA256:
		memcpy(p, ASN1_HASH_SHA2X, 19);
		memcpy(p + 19, hash, 32);
		p[1] += 32; p[14] = 1; p[18] += 32; break;

	case SIG_RSA_SHA384:
		memcpy(p, ASN1_HASH_SHA2X, 19);
		memcpy(p + 19, hash, 48);
		p[1] += 48; p[14] = 2; p[18] += 48; break;

	case SIG_RSA_SHA512:
		memcpy(p, ASN1_HASH_SHA2X, 19);
		memcpy(p + 19, hash, 64);
		p[1] += 64; p[14] = 3; p[18] += 64; break;

	default:
		return (POLARSSL_ERR_RSA_BAD_INPUT_DATA);
	}

	return ((mode == RSA_PUBLIC)
		? hicap_rsa_public(ctx, sig, sig)
		: hicap_rsa_private(ctx, sig, sig));
}
/******************************************************************************/
/*
* Do an RSA operation and check the message digest
*/
int hicap_rsa_pkcs1_verify(rsa_context *ctx, int mode, int hash_id, int hashlen,
		     const unsigned char *hash, unsigned char *sig)
{
	int ret, len, siglen;
	unsigned char *p, c;
	unsigned char *buf = (unsigned char *)ctx->buf;

	siglen = ctx->len;

	if (siglen < 16 || siglen > (int) ctx->sz_buf)
		return (POLARSSL_ERR_RSA_BAD_INPUT_DATA);

	ret = (mode == RSA_PUBLIC) ? hicap_rsa_public(ctx, sig, buf)
		: hicap_rsa_private(ctx, sig, buf);

	if (ret != 0)
		return (ret);

	p = buf;

	switch(ctx->padding) {
	case RSA_PKCS_V15:
		if (*p++ != 0 || *p++ != RSA_SIGN)
			return (POLARSSL_ERR_RSA_INVALID_PADDING);

		while (*p != 0) {
			if (p >= buf + siglen - 1 || *p != 0xFF)
				return (POLARSSL_ERR_RSA_INVALID_PADDING);
			p++;
		}
		p++;
		break;

	default:
		return (POLARSSL_ERR_RSA_INVALID_PADDING);
	}

	len = siglen - (int)(p - buf);

	if (len == 34) {
		c = p[13];
		p[13] = 0;

		if (memcmp(p, ASN1_HASH_MDX, 18) != 0)
			return (POLARSSL_ERR_RSA_VERIFY_FAILED);

		if ((c == 2 && hash_id == SIG_RSA_MD2) ||
		    (c == 4 && hash_id == SIG_RSA_MD4) ||
		    (c == 5 && hash_id == SIG_RSA_MD5)) {
			if (memcmp(p + 18, hash, 16) == 0) 
				return (0);
			else
				return (POLARSSL_ERR_RSA_VERIFY_FAILED);
		}
	}

	if (len == 35 && hash_id == SIG_RSA_SHA1) {
		if (memcmp(p, ASN1_HASH_SHA1, 15) == 0 &&
			memcmp(p + 15, hash, 20) == 0)
			return (0);
		else
			return (POLARSSL_ERR_RSA_VERIFY_FAILED);
	}
	if ((len == 19 + 28 && p[14] == 4 && hash_id == SIG_RSA_SHA224) ||
	    (len == 19 + 32 && p[14] == 1 && hash_id == SIG_RSA_SHA256) ||
	    (len == 19 + 48 && p[14] == 2 && hash_id == SIG_RSA_SHA384) ||
	    (len == 19 + 64 && p[14] == 3 && hash_id == SIG_RSA_SHA512)) {
		c = p[1] - 17;
		p[1] = 17;
		p[14] = 0;

		if (p[18] == c &&
		    memcmp(p, ASN1_HASH_SHA2X, 18) == 0 &&
		    memcmp(p + 19, hash, c) == 0)
			return (0);
		else
			return (POLARSSL_ERR_RSA_VERIFY_FAILED);
	}

	if (len == hashlen && hash_id == SIG_RSA_RAW) {
		if (memcmp(p, hash, hashlen) == 0)
			return (0);
		else
			return (POLARSSL_ERR_RSA_VERIFY_FAILED);
	}

	return (POLARSSL_ERR_RSA_INVALID_PADDING);
}
/******************************************************************************/
/*
* Free the components of an RSA key
*/
void hicap_rsa_free(rsa_context *ctx)
{
	hicap_bignum_free(&ctx->RQ, &ctx->RP, &ctx->RN,
		&ctx->QP, &ctx->DQ, &ctx->DP,
		&ctx->Q,  &ctx->P,  &ctx->D,
		&ctx->E,  &ctx->N,  NULL);

	if (ctx->buf)
		hicap_vfree(ctx->buf);
}
/******************************************************************************/

static char *RSA_N = "c78b25787f4f6c2c6b802fd5a59aefe12000029527f5e5f7654f4c90" \
	"6f1c695fbb0c4317ec0fa28d13b836fa18ddccd27158b3a18afc469c" \
	"651cd29cbcd5c9723d4f3e4b5f59fa9589da725e957b130c47429aed" \
	"c4c1ee7d31a68dcd15a260f61841a15ee2fb2287d5c3d24db7dfd8aa" \
	"d734da4c4700ae55c40ed691bdc86a8fe86259aa05eaab039acb712c" \
	"2eee719427eb01d90856deb8452b6830de178443014d35257ad22ac2" \
	"2330d8255112fd988f43d7f56b560ec5a368836698ae3eab5975f89b" \
	"470bb52f74c0788069632b55a2968aea2061d6eb5b6282d9fcb76ff5" \
	"4b6d0d6d1714f606a86c5e7ced24d65093d211c99fd863cb0fcc1c02" \
	"ebdd5e25";

static char *RSA_E = "010001";

int hicap_rsa_set_pubkey(rsa_context *rsa)
{
	int ret;

	ret = hicap_bignum_read_string(&rsa->N, 16, RSA_N);
	if (ret)
		return ret;

	ret = hicap_bignum_read_string(&rsa->E, 16, RSA_E);
	if (ret)
		return ret;

	return 0;
}

