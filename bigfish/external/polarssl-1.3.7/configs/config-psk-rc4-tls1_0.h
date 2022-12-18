/*
 * Custom compact configuration for TLS 1.0 with PSK and RC4
 * Distinguishing features: no bignum, no PK, no X509.
 *
 * See README.txt for usage instructions.
 */

#ifndef POLARSSL_CONFIG_H
#define POLARSSL_CONFIG_H

/* System support */
#define POLARSSL_HAVE_TIME
#define POLARSSL_HAVE_IPV6

/* PolarSSL feature support */
#define POLARSSL_KEY_EXCHANGE_PSK_ENABLED
#define POLARSSL_SSL_PROTO_TLS1

/* PolarSSL modules */
#define POLARSSL_AES_C
#define POLARSSL_ARC4_C
#define POLARSSL_ASN1_PARSE_C
#define POLARSSL_ASN1_WRITE_C
#define POLARSSL_CIPHER_C
#define POLARSSL_CTR_DRBG_C
#define POLARSSL_ENTROPY_C
#define POLARSSL_MD_C
#define POLARSSL_MD5_C
#define POLARSSL_NET_C
#define POLARSSL_OID_C
#define POLARSSL_SHA1_C
#define POLARSSL_SHA256_C
#define POLARSSL_SSL_CLI_C
#define POLARSSL_SSL_SRV_C
#define POLARSSL_SSL_TLS_C

#include "check_config.h"

#endif /* POLARSSL_CONFIG_H */
