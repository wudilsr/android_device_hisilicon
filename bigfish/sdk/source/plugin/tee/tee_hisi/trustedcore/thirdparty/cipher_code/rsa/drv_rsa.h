
#ifndef __DRV_RSA_H__
#define __DRV_RSA_H__

#include "drv_rsa_bignum.h"

#define CIPHER_MAX_RSA_KEY_LEN   512

/*
 * RSA Error codes
 */
#define ALG_ERR_RSA_BAD_INPUT_DATA                    -0x0400
#define ALG_ERR_RSA_INVALID_PADDING                   -0x0410
#define ALG_ERR_RSA_KEY_GEN_FAILED                    -0x0420
#define ALG_ERR_RSA_KEY_CHECK_FAILED                  -0x0430
#define ALG_ERR_RSA_PUBLIC_FAILED                     -0x0440
#define ALG_ERR_RSA_PRIVATE_FAILED                    -0x0450
#define ALG_ERR_RSA_VERIFY_FAILED                     -0x0460
#define ALG_ERR_RSA_OUTPUT_TOO_LARGE                  -0x0470
#define ALG_ERR_RSA_RNG_FAILED                        -0x0480

/*
 * PKCS#1 constants
 */
#define SIG_RSA_RAW     0
#define SIG_RSA_MD2     2
#define SIG_RSA_MD4     3
#define SIG_RSA_MD5     4
#define SIG_RSA_SHA1	5
#define SIG_RSA_SHA224	14
#define SIG_RSA_SHA256	11
#define	SIG_RSA_SHA384	12
#define SIG_RSA_SHA512	13

#define RSA_PUBLIC      0
#define RSA_PRIVATE     1

#define RSA_PKCS_V15    0
#define RSA_PKCS_V21    1

#define RSA_SIGN        1
#define RSA_CRYPT       2

#define ASN1_STR_CONSTRUCTED_SEQUENCE	"\x30"
#define ASN1_STR_NULL			        "\x05"
#define ASN1_STR_OID			        "\x06"
#define ASN1_STR_OCTET_STRING		    "\x04"

#define OID_DIGEST_ALG_MDX	        "\x2A\x86\x48\x86\xF7\x0D\x02\x00"
#define OID_HASH_ALG_SHA1	        "\x2b\x0e\x03\x02\x1a"
#define OID_HASH_ALG_SHA2X	        "\x60\x86\x48\x01\x65\x03\x04\x02\x00"

#define OID_ISO_MEMBER_BODIES	    "\x2a"
#define OID_ISO_IDENTIFIED_ORG	    "\x2b"

/*
 * ISO Member bodies OID parts
 */
#define OID_COUNTRY_US		        "\x86\x48"
#define OID_RSA_DATA_SECURITY	    "\x86\xf7\x0d"

/*
 * ISO Identified organization OID parts
 */
#define OID_OIW_SECSIG_SHA1	        "\x0e\x03\x02\x1a"

/*
 * DigestInfo ::= SEQUENCE {
 *   digestAlgorithm DigestAlgorithmIdentifier,
 *   digest Digest }
 *
 * DigestAlgorithmIdentifier ::= AlgorithmIdentifier
 *
 * Digest ::= OCTET STRING
 */
#define ASN1_HASH_MDX					        \
(							                    \
    ASN1_STR_CONSTRUCTED_SEQUENCE "\x20"		\
      ASN1_STR_CONSTRUCTED_SEQUENCE "\x0C"		\
        ASN1_STR_OID "\x08"				        \
	  OID_DIGEST_ALG_MDX				        \
	ASN1_STR_NULL "\x00"				        \
      ASN1_STR_OCTET_STRING "\x10"			    \
)

#define ASN1_HASH_SHA1					        \
    ASN1_STR_CONSTRUCTED_SEQUENCE "\x21"		\
      ASN1_STR_CONSTRUCTED_SEQUENCE "\x09"		\
        ASN1_STR_OID "\x05"				        \
	  OID_HASH_ALG_SHA1				            \
        ASN1_STR_NULL "\x00"				    \
      ASN1_STR_OCTET_STRING "\x14"

#define ASN1_HASH_SHA2X					        \
    ASN1_STR_CONSTRUCTED_SEQUENCE "\x11"		\
      ASN1_STR_CONSTRUCTED_SEQUENCE "\x0d"		\
        ASN1_STR_OID "\x09"				        \
	  OID_HASH_ALG_SHA2X				        \
        ASN1_STR_NULL "\x00"				    \
      ASN1_STR_OCTET_STRING "\x00"

/**
 * \brief          RSA context structure
 */
typedef struct
{
    int ver;                    /*!<  always 0          */
    int len;                    /*!<  size(N) in chars  */

    mpi N;                      /*!<  public modulus    */
    mpi E;                      /*!<  public exponent   */

    mpi D;                      /*!<  private exponent  */
    mpi P;                      /*!<  1st prime factor  */
    mpi Q;                      /*!<  2nd prime factor  */
    mpi DP;                     /*!<  D % (P - 1)       */
    mpi DQ;                     /*!<  D % (Q - 1)       */
    mpi QP;                     /*!<  1 / (Q % P)       */

    mpi RN;                     /*!<  cached R^2 mod N  */
    mpi RP;                     /*!<  cached R^2 mod P  */
    mpi RQ;                     /*!<  cached R^2 mod Q  */

    int padding;                /*!<  1.5 or OAEP/PSS   */
    int hash_id;                /*!<  hash identifier   */
}
rsa_context;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Initialize an RSA context
 */
void rsa_init( rsa_context *ctx,
               int padding,
               int hash_id );

int rsa_gen_key( rsa_context *ctx,
                 int (*f_rng)(void *),
                 void *p_rng,
                 int nbits, int exponent );

/**
 * \brief          Check a public RSA key
 *
 * \param ctx      RSA context to be checked
 *
 * \return         0 if successful, or an ALG_ERR_RSA_XXX error code
 */
int rsa_check_pubkey( const rsa_context *ctx );

/**
 * \brief          Check a private RSA key
 *
 * \param ctx      RSA context to be checked
 *
 * \return         0 if successful, or an ALG_ERR_RSA_XXX error code
 */
int rsa_check_privkey( const rsa_context *ctx );

/**
 * \brief          Do an RSA public key operation
 *
 * \param ctx      RSA context
 * \param input    input buffer
 * \param output   output buffer
 *
 * \return         0 if successful, or an ALG_ERR_RSA_XXX error code
 *
 * \note           This function does NOT take care of message
 *                 padding. Also, be sure to set input[0] = 0 or assure that
 *                 input is smaller than N.
 *
 * \note           The input and output buffers must be large
 *                 enough (eg. 128 bytes if RSA-1024 is used).
 */
 
int rsa_public( rsa_context *ctx,
                const unsigned char *input,
                unsigned char *output );

/**
 * \brief          Do an RSA private key operation
 *
 * \param ctx      RSA context
 * \param input    input buffer
 * \param output   output buffer
 *
 * \return         0 if successful, or an ALG_ERR_RSA_XXX error code
 *
 * \note           The input and output buffers must be large
 *                 enough (eg. 128 bytes if RSA-1024 is used).
 */
int rsa_private( rsa_context *ctx,
                 const unsigned char *input,
                 unsigned char *output );

/**
 * \brief          Do a private RSA to sign a message digest
 *
 * \param ctx      RSA context
 * \param mode     RSA_PUBLIC or RSA_PRIVATE
 * \param hash_id  SIG_RSA_RAW, SIG_RSA_MD{2,4,5} or SIG_RSA_SHA{1,224,256,384,512}
 * \param hashlen  message digest length (for SIG_RSA_RAW only)
 * \param hash     buffer holding the message digest
 * \param sig      buffer that will hold the ciphertext
 *
 * \return         0 if the signing operation was successful,
 *                 or an ALG_ERR_RSA_XXX error code
 *
 * \note           The "sig" buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 */
int rsa_pkcs1_sign( rsa_context *ctx,
                    int mode,
                    int hash_id,
                    int hashlen,
                    const unsigned char *hash,
                    unsigned char *sig );

/**
 * \brief          Do a public RSA and check the message digest
 *
 * \param ctx      points to an RSA public key
 * \param mode     RSA_PUBLIC or RSA_PRIVATE
 * \param hash_id  SIG_RSA_RAW, SIG_RSA_MD{2,4,5} or SIG_RSA_SHA{1,224,256,384,512}
 * \param hashlen  message digest length (for SIG_RSA_RAW only)
 * \param hash     buffer holding the message digest
 * \param sig      buffer holding the ciphertext
 *
 * \return         0 if the verify operation was successful,
 *                 or an ALG_ERR_RSA_XXX error code
 *
 * \note           The "sig" buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 */
int rsa_pkcs1_verify( rsa_context *ctx,
                      int mode,
                      int hash_id,
                      int hashlen,
                      const unsigned char *hash,
                      unsigned char *sig );

/**
 * \brief          Free the components of an RSA key
 *
 * \param ctx      RSA Context to free
 */
void rsa_free( rsa_context *ctx );

#ifdef __cplusplus
}
#endif

#endif /* alg.h */
