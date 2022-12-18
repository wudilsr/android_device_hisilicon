/* crypto/rsa/rsa_pk1.c */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#include <stdio.h>
#include "cryptlib.h"
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>

#define ASN1_STR_CONSTRUCTED_SEQUENCE	"\x30"
#define ASN1_STR_NULL			        "\x05"
#define ASN1_STR_OID			        "\x06"
#define ASN1_STR_OCTET_STRING		    "\x04"

#define OID_HASH_ALG_SHA2X	        "\x60\x86\x48\x01\x65\x03\x04\x02\x00"

#define OID_HASH_ALG_SHA1	        "\x2b\x0e\x03\x02\x1a"

#define ASN1_HASH_SHA2X					        \
    ASN1_STR_CONSTRUCTED_SEQUENCE "\x11"		\
      ASN1_STR_CONSTRUCTED_SEQUENCE "\x0d"		\
        ASN1_STR_OID "\x09"				        \
	  OID_HASH_ALG_SHA2X				        \
        ASN1_STR_NULL "\x00"				    \
      ASN1_STR_OCTET_STRING "\x00"

#define ASN1_HASH_SHA1					        \
    ASN1_STR_CONSTRUCTED_SEQUENCE "\x21"		\
      ASN1_STR_CONSTRUCTED_SEQUENCE "\x09"		\
        ASN1_STR_OID "\x05"				        \
	  OID_HASH_ALG_SHA1				            \
        ASN1_STR_NULL "\x00"				    \
      ASN1_STR_OCTET_STRING "\x14"

int RSA_padding_add_PKCS1_type_1(unsigned char *to, int tlen,
	     const unsigned char *from, int flen)
	{
	int j;
	unsigned char *p;

	if (flen > (tlen-RSA_PKCS1_PADDING_SIZE))
		{
		RSAerr(RSA_F_RSA_PADDING_ADD_PKCS1_TYPE_1,RSA_R_DATA_TOO_LARGE_FOR_KEY_SIZE);
		return(0);
		}
	
	p=(unsigned char *)to;

	*(p++)=0;
	*(p++)=1; /* Private Key BT (Block Type) */

	/* pad out with 0xff data */
	j=tlen-3-flen;
	memset(p,0xff,j);
	p+=j;
	*(p++)='\0';
	memcpy(p,from,(unsigned int)flen);
	return(1);
	}

int RSA_padding_check_PKCS1_type_1(unsigned char *to, int tlen,
	     const unsigned char *from, int flen, int num)
	{
	int i,j;
	const unsigned char *p;

	p=from;
	if ((num != (flen+1)) || (*(p++) != 01))
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_BLOCK_TYPE_IS_NOT_01);
		return(-1);
		}

	/* scan over padding data */
	j=flen-1; /* one for type. */
	for (i=0; i<j; i++)
		{
		if (*p != 0xff) /* should decrypt to 0xff */
			{
			if (*p == 0)
				{ p++; break; }
			else	{
				RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_BAD_FIXED_HEADER_DECRYPT);
				return(-1);
				}
			}
		p++;
		}

	if (i == j)
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_NULL_BEFORE_BLOCK_MISSING);
		return(-1);
		}

	if (i < 8)
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_BAD_PAD_BYTE_COUNT);
		return(-1);
		}
	i++; /* Skip over the '\0' */
	j-=i;
	if (j > tlen)
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_DATA_TOO_LARGE);
		return(-1);
		}
	memcpy(to,p,(unsigned int)j);

	return(j);
	}

int RSA_padding_add_PKCS1_type_2(unsigned char *to, int tlen,
	     const unsigned char *from, int flen)
	{
	int i,j;
	unsigned char *p;
	
	if (flen > (tlen-11))
		{
		RSAerr(RSA_F_RSA_PADDING_ADD_PKCS1_TYPE_2,RSA_R_DATA_TOO_LARGE_FOR_KEY_SIZE);
		return(0);
		}
	
	p=(unsigned char *)to;

	*(p++)=0;
	*(p++)=2; /* Public Key BT (Block Type) */

	/* pad out with non-zero random data */
	j=tlen-3-flen;

	if (RAND_bytes(p,j) <= 0)
		return(0);
	for (i=0; i<j; i++)
		{
		if (*p == '\0')
			do	{
				if (RAND_bytes(p,1) <= 0)
					return(0);
				} while (*p == '\0');
		p++;
		}

	*(p++)='\0';

	memcpy(p,from,(unsigned int)flen);
	return(1);
	}

int RSA_padding_check_PKCS1_type_2(unsigned char *to, int tlen,
	     const unsigned char *from, int flen, int num)
	{
	int i,j;
	const unsigned char *p;

	p=from;
	if ((num != (flen+1)) || (*(p++) != 02))
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_2,RSA_R_BLOCK_TYPE_IS_NOT_02);
		return(-1);
		}
#ifdef PKCS1_CHECK
	return(num-11);
#endif

	/* scan over padding data */
	j=flen-1; /* one for type. */
	for (i=0; i<j; i++)
		if (*(p++) == 0) break;

	if (i == j)
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_2,RSA_R_NULL_BEFORE_BLOCK_MISSING);
		return(-1);
		}

	if (i < 8)
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_2,RSA_R_BAD_PAD_BYTE_COUNT);
		return(-1);
		}
	i++; /* Skip over the '\0' */
	j-=i;
	if (j > tlen)
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_2,RSA_R_DATA_TOO_LARGE);
		return(-1);
		}
	memcpy(to,p,(unsigned int)j);

	return(j);
	}

int RSA_padding_add_PKCS1_type_3(unsigned char *to, int tlen,
         const unsigned char *from, int flen)
    {
    int j;
    unsigned char *p;

    if (flen > (tlen-RSA_PKCS1_PADDING_SIZE))
        {
        RSAerr(RSA_F_RSA_PADDING_ADD_PKCS1_TYPE_3,RSA_R_DATA_TOO_LARGE_FOR_KEY_SIZE);
        return(0);
        }
    
    p=(unsigned char *)to;

    *(p++)=0;
    *(p++)=1; /* Private Key BT (Block Type) */

    /* pad out with 0xff data */
    j=tlen-3-51;
    memset(p,0xff,j);
    p+=j;
    *(p++)='\0';
    memcpy( p, ASN1_HASH_SHA2X, 19 );
    memcpy( p + 19, from, 32 );
    p[1] += 32; p[14] = 1; p[18] += 32;

    return(1);
    }

int RSA_padding_check_PKCS1_type_3(unsigned char *to, int tlen,
         const unsigned char *from, int flen, int num)
    {
    int i,j;
    unsigned char *p;
    int len;
    unsigned char c;

    p=(unsigned char *)from;
    if ((num != (flen+1)) || (*(p++) != 01))
        {
        RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_3,RSA_R_BLOCK_TYPE_IS_NOT_01);
        return(-1);
        }

    /* scan over padding data */
    j=flen-1; /* one for type. */
    for (i=0; i<j; i++)
        {
        if (*p != 0xff) /* should decrypt to 0xff */
            {
            if (*p == 0)
                { p++; break; }
            else    {
                RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_3,RSA_R_BAD_FIXED_HEADER_DECRYPT);
                return(-1);
                }
            }
        p++;
        }

    if (i == j)
        {
        RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_3,RSA_R_NULL_BEFORE_BLOCK_MISSING);
        return(-1);
        }

    len = j - (i + 1);

    if ((len == (19 + 32)) && (p[14] == 1))
    {
        c = p[1] - 17;
        p[1] = 17;
        p[14] = 0;

        if( p[18] == c &&
                memcmp( p, ASN1_HASH_SHA2X, 18 ) == 0)
        {
            memcpy( to, p + 19, c );
            return( c );
        }
        else
            RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_3,RSA_R_BAD_SIGNATURE);
    }

    RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_3,RSA_R_INVALID_PADDING);
    return (-1);
    }

int RSA_padding_add_PKCS1_type_4(unsigned char *to, int tlen,
         const unsigned char *from, int flen)
    {
    int j;
    unsigned char *p;

    if (flen > (tlen-RSA_PKCS1_PADDING_SIZE))
        {
        RSAerr(RSA_F_RSA_PADDING_ADD_PKCS1_TYPE_4,RSA_R_DATA_TOO_LARGE_FOR_KEY_SIZE);
        return(0);
        }
    
    p=(unsigned char *)to;

    *(p++)=0;
    *(p++)=1; /* Private Key BT (Block Type) */

    /* pad out with 0xff data */
    j=tlen-3-35;
    memset(p,0xff,j);
    p+=j;
    *(p++)='\0';
    memcpy( p, ASN1_HASH_SHA1, 15 );
    memcpy( p + 15, from, 20 );

    return(1);
    }

int RSA_padding_check_PKCS1_type_4(unsigned char *to, int tlen,
         const unsigned char *from, int flen, int num)
    {
    int i,j;
    unsigned char *p;
    int len;
    unsigned char c;

    p=(unsigned char *)from;
    if ((num != (flen+1)) || (*(p++) != 01))
        {
        RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_4,RSA_R_BLOCK_TYPE_IS_NOT_01);
        return(-1);
        }

    /* scan over padding data */
    j=flen-1; /* one for type. */
    for (i=0; i<j; i++)
        {
        if (*p != 0xff) /* should decrypt to 0xff */
            {
            if (*p == 0)
                { p++; break; }
            else    {
                RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_4,RSA_R_BAD_FIXED_HEADER_DECRYPT);
                return(-1);
                }
            }
        p++;
        }

    if (i == j)
        {
        RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_4,RSA_R_NULL_BEFORE_BLOCK_MISSING);
        return(-1);
        }

    len = j - (i + 1);

    if( len == 35 )
    {
        if( memcmp( p, ASN1_HASH_SHA1, 15 ) == 0 )
        {
            memcpy( to, p + 15, 20 );
            return( 20 );
        }
        else
            RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_4,RSA_R_BAD_SIGNATURE);
    }

    if ((len == (19 + 32)) && (p[14] == 1))
    {
        c = p[1] - 17;
        p[1] = 17;
        p[14] = 0;

        if( p[18] == c &&
                memcmp( p, ASN1_HASH_SHA2X, 18 ) == 0)
        {
            memcpy( to, p + 19, c );
            return( c );
        }
        else
            RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_4,RSA_R_BAD_SIGNATURE);
    }

    RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_4,RSA_R_INVALID_PADDING);
    return (-1);
    }

