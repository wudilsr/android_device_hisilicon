#include "stdio.h"
#include "string.h"
#include "config.h"
#if defined(POLARSSL_RSA_C)
#include "rsa.h"

/*
 * Initialize an RSA context
 */
void hi_rsa_init( rsa_context *ctx,
               int padding,
               int hash_id )
{
    memset( ctx, 0, sizeof( rsa_context ) );

    ctx->padding = padding;
    ctx->hash_id = hash_id;
}

#if defined(POLARSSL_GENPRIME)

/*
 * Generate an RSA keypair
 */
int hi_rsa_gen_key( rsa_context *ctx,
        int (*f_rng)(void *),
        void *p_rng,
        int nbits, int exponent )
{
    int ret;
    mpi P1, Q1, H, G;

    if( f_rng == NULL || nbits < 128 || exponent < 3 )
        return( POLARSSL_ERR_RSA_BAD_INPUT_DATA );

    hi_mpi_init( &P1 ); hi_mpi_init( &Q1 ); hi_mpi_init( &H ); hi_mpi_init( &G );

    /*
     * find primes P and Q with Q < P so that:
     * GCD( E, (P-1)*(Q-1) ) == 1
     */
    MPI_CHK( hi_mpi_lset( &ctx->E, exponent ) );

    do
    {
        MPI_CHK( hi_mpi_gen_prime( &ctx->P, ( nbits + 1 ) >> 1, 0,
                                f_rng, p_rng ) );

        MPI_CHK( hi_mpi_gen_prime( &ctx->Q, ( nbits + 1 ) >> 1, 0,
                                f_rng, p_rng ) );

        if( hi_mpi_cmp_mpi( &ctx->P, &ctx->Q ) < 0 )
            hi_mpi_swap( &ctx->P, &ctx->Q );

        if( hi_mpi_cmp_mpi( &ctx->P, &ctx->Q ) == 0 )
            continue;

        MPI_CHK( hi_mpi_mul_mpi( &ctx->N, &ctx->P, &ctx->Q ) );
        if( hi_mpi_msb( &ctx->N ) != nbits )
            continue;

        MPI_CHK( hi_mpi_sub_int( &P1, &ctx->P, 1 ) );
        MPI_CHK( hi_mpi_sub_int( &Q1, &ctx->Q, 1 ) );
        MPI_CHK( hi_mpi_mul_mpi( &H, &P1, &Q1 ) );
        MPI_CHK( hi_mpi_gcd( &G, &ctx->E, &H  ) );
    }
    while( hi_mpi_cmp_int( &G, 1 ) != 0 );

    /*
     * D  = E^-1 mod ((P-1)*(Q-1))
     * DP = D mod (P - 1)
     * DQ = D mod (Q - 1)
     * QP = Q^-1 mod P
     */
    MPI_CHK( hi_mpi_inv_mod( &ctx->D , &ctx->E, &H  ) );
    MPI_CHK( hi_mpi_mod_mpi( &ctx->DP, &ctx->D, &P1 ) );
    MPI_CHK( hi_mpi_mod_mpi( &ctx->DQ, &ctx->D, &Q1 ) );
    MPI_CHK( hi_mpi_inv_mod( &ctx->QP, &ctx->Q, &ctx->P ) );

    ctx->len = ( hi_mpi_msb( &ctx->N ) + 7 ) >> 3;

cleanup:

    hi_mpi_free( &P1 ); hi_mpi_free( &Q1 ); hi_mpi_free( &H ); hi_mpi_free( &G );

    if( ret != 0 )
    {
        hi_rsa_free( ctx );
        return( POLARSSL_ERR_RSA_KEY_GEN_FAILED | ret );
    }

    return( 0 );
}

#endif

/*
 * Check a public RSA key
 */
int hi_rsa_check_pubkey( const rsa_context *ctx )
{
    if( !ctx->N.p || !ctx->E.p )
        return( POLARSSL_ERR_RSA_KEY_CHECK_FAILED );

    if( ( ctx->N.p[0] & 1 ) == 0 ||
        ( ctx->E.p[0] & 1 ) == 0 )
        return( POLARSSL_ERR_RSA_KEY_CHECK_FAILED );

    if( hi_mpi_msb( &ctx->N ) < 128 ||
        hi_mpi_msb( &ctx->N ) > 4096 )
        return( POLARSSL_ERR_RSA_KEY_CHECK_FAILED );

    if( hi_mpi_msb( &ctx->E ) < 2 ||
        hi_mpi_msb( &ctx->E ) > 64 )
        return( POLARSSL_ERR_RSA_KEY_CHECK_FAILED );

    return( 0 );
}

/*
 * Check a private RSA key
 */
int hi_rsa_check_privkey( const rsa_context *ctx )
{
    int ret;
    mpi PQ, DE, P1, Q1, H, I, G, G2, L1, L2;

    if( ( ret = hi_rsa_check_pubkey( ctx ) ) != 0 )
        return( ret );

    if( !ctx->P.p || !ctx->Q.p || !ctx->D.p )
        return( POLARSSL_ERR_RSA_KEY_CHECK_FAILED );

    hi_mpi_init( &PQ ); hi_mpi_init( &DE ); hi_mpi_init( &P1 ); hi_mpi_init( &Q1 );
    hi_mpi_init( &H  ); hi_mpi_init( &I  ); hi_mpi_init( &G  ); hi_mpi_init( &G2 );
    hi_mpi_init( &L1 ); hi_mpi_init( &L2 );

    MPI_CHK( hi_mpi_mul_mpi( &PQ, &ctx->P, &ctx->Q ) );
    MPI_CHK( hi_mpi_mul_mpi( &DE, &ctx->D, &ctx->E ) );
    MPI_CHK( hi_mpi_sub_int( &P1, &ctx->P, 1 ) );
    MPI_CHK( hi_mpi_sub_int( &Q1, &ctx->Q, 1 ) );
    MPI_CHK( hi_mpi_mul_mpi( &H, &P1, &Q1 ) );
    MPI_CHK( hi_mpi_gcd( &G, &ctx->E, &H  ) );

    MPI_CHK( hi_mpi_gcd( &G2, &P1, &Q1 ) );
    MPI_CHK( hi_mpi_div_mpi( &L1, &L2, &H, &G2 ) );
    MPI_CHK( hi_mpi_mod_mpi( &I, &DE, &L1  ) );

    /*
     * Check for a valid PKCS1v2 private key
     */
    if( hi_mpi_cmp_mpi( &PQ, &ctx->N ) == 0 &&
        hi_mpi_cmp_int( &L2, 0 ) == 0 &&
        hi_mpi_cmp_int( &I, 1 ) == 0 &&
        hi_mpi_cmp_int( &G, 1 ) == 0 )
    {
        hi_mpi_free( &PQ ); hi_mpi_free( &DE ); hi_mpi_free( &P1 ); hi_mpi_free( &Q1 );
        hi_mpi_free( &H  ); hi_mpi_free( &I  ); hi_mpi_free( &G  ); hi_mpi_free( &G2 );
        hi_mpi_free( &L1 ); hi_mpi_free( &L2 );
        return( 0 );
    }

cleanup:

    hi_mpi_free( &PQ ); hi_mpi_free( &DE ); hi_mpi_free( &P1 ); hi_mpi_free( &Q1 );
    hi_mpi_free( &H  ); hi_mpi_free( &I  ); hi_mpi_free( &G  ); hi_mpi_free( &G2 );
    hi_mpi_free( &L1 ); hi_mpi_free( &L2 );
    return( POLARSSL_ERR_RSA_KEY_CHECK_FAILED | ret );
}

/*
 * Do an RSA public key operation
 */
int hi_rsa_public( rsa_context *ctx,
                const unsigned char *input,
                unsigned char *output )
{
    int ret, olen;
    mpi T;

    hi_mpi_init( &T );

    MPI_CHK( hi_mpi_read_binary( &T, input, ctx->len ) );

    if( hi_mpi_cmp_mpi( &T, &ctx->N ) >= 0 )
    {
        hi_mpi_free( &T );
        return( POLARSSL_ERR_RSA_BAD_INPUT_DATA );
    }

    olen = ctx->len;
    MPI_CHK( hi_mpi_exp_mod( &T, &T, &ctx->E, &ctx->N, &ctx->RN ) );
    MPI_CHK( hi_mpi_write_binary( &T, output, olen ) );

cleanup:

    hi_mpi_free( &T );

    if( ret != 0 )
        return( POLARSSL_ERR_RSA_PUBLIC_FAILED | ret );

    return( 0 );
}

/*
 * Do an RSA private key operation
 */
int hi_rsa_private( rsa_context *ctx,
                 const unsigned char *input,
                 unsigned char *output )
{
    int ret, olen;
    mpi T, T1, T2;

    hi_mpi_init( &T ); hi_mpi_init( &T1 ); hi_mpi_init( &T2 );
    MPI_CHK( hi_mpi_read_binary( &T, input, ctx->len ) );

    if( hi_mpi_cmp_mpi( &T, &ctx->N ) >= 0 )
    {
        hi_mpi_free( &T );
        return( POLARSSL_ERR_RSA_BAD_INPUT_DATA );
    }

#if 1
    MPI_CHK( hi_mpi_exp_mod( &T, &T, &ctx->D, &ctx->N, &ctx->RN ) );
#else
    /*
     * faster decryption using the CRT
     *
     * T1 = input ^ dP mod P
     * T2 = input ^ dQ mod Q
     */
    MPI_CHK( hi_mpi_exp_mod( &T1, &T, &ctx->DP, &ctx->P, &ctx->RP ) );
    MPI_CHK( hi_mpi_exp_mod( &T2, &T, &ctx->DQ, &ctx->Q, &ctx->RQ ) );

    /*
     * T = (T1 - T2) * (Q^-1 mod P) mod P
     */
    MPI_CHK( hi_mpi_sub_mpi( &T, &T1, &T2 ) );
    MPI_CHK( hi_mpi_mul_mpi( &T1, &T, &ctx->QP ) );
    MPI_CHK( hi_mpi_mod_mpi( &T, &T1, &ctx->P ) );

    /*
     * output = T2 + T * Q
     */
    MPI_CHK( hi_mpi_mul_mpi( &T1, &T, &ctx->Q ) );
    MPI_CHK( hi_mpi_add_mpi( &T, &T2, &T1 ) );
#endif

    olen = ctx->len;
    MPI_CHK( hi_mpi_write_binary( &T, output, olen ) );

cleanup:

    hi_mpi_free( &T ); hi_mpi_free( &T1 ); hi_mpi_free( &T2 );

    if( ret != 0 )
        return( POLARSSL_ERR_RSA_PRIVATE_FAILED | ret );

    return( 0 );
}

/*
 * Do an RSA operation to sign the message digest
 */
int hi_rsa_pkcs1_sign( rsa_context *ctx,
                    int mode,
                    int hash_id,
                    int hashlen,
                    const unsigned char *hash,
                    unsigned char *sig )
{
    int nb_pad, olen;
    unsigned char *p = sig;

    olen = ctx->len;

    switch( ctx->padding )
    {
        case RSA_PKCS_V15:

            switch( hash_id )
            {
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
                    return( POLARSSL_ERR_RSA_BAD_INPUT_DATA );
            }

            if( nb_pad < 8 )
                return( POLARSSL_ERR_RSA_BAD_INPUT_DATA );

            *p++ = 0;
            *p++ = RSA_SIGN;
            memset( p, 0xFF, nb_pad );
            p += nb_pad;
            *p++ = 0;
            break;

        default:

            return( POLARSSL_ERR_RSA_INVALID_PADDING );
    }

    switch( hash_id )
    {
        case SIG_RSA_RAW:
            memcpy( p, hash, hashlen );
            break;

        case SIG_RSA_MD2:
            memcpy( p, ASN1_HASH_MDX, 18 );
            memcpy( p + 18, hash, 16 );
            p[13] = 2; break;

        case SIG_RSA_MD4:
            memcpy( p, ASN1_HASH_MDX, 18 );
            memcpy( p + 18, hash, 16 );
            p[13] = 4; break;

        case SIG_RSA_MD5:
            memcpy( p, ASN1_HASH_MDX, 18 );
            memcpy( p + 18, hash, 16 );
            p[13] = 5; break;

        case SIG_RSA_SHA1:
            memcpy( p, ASN1_HASH_SHA1, 15 );
            memcpy( p + 15, hash, 20 );
            break;

        case SIG_RSA_SHA224:
            memcpy( p, ASN1_HASH_SHA2X, 19 );
            memcpy( p + 19, hash, 28 );
            p[1] += 28; p[14] = 4; p[18] += 28; break;

        case SIG_RSA_SHA256:
            memcpy( p, ASN1_HASH_SHA2X, 19 );
            memcpy( p + 19, hash, 32 );
            p[1] += 32; p[14] = 1; p[18] += 32; break;

        case SIG_RSA_SHA384:
            memcpy( p, ASN1_HASH_SHA2X, 19 );
            memcpy( p + 19, hash, 48 );
            p[1] += 48; p[14] = 2; p[18] += 48; break;

        case SIG_RSA_SHA512:
            memcpy( p, ASN1_HASH_SHA2X, 19 );
            memcpy( p + 19, hash, 64 );
            p[1] += 64; p[14] = 3; p[18] += 64; break;

        default:
            return( POLARSSL_ERR_RSA_BAD_INPUT_DATA );
    }

    return( ( mode == RSA_PUBLIC )
            ? hi_rsa_public(  ctx, sig, sig )
            : hi_rsa_private( ctx, sig, sig ) );
}

/*
 * Do an RSA operation and check the message digest
 */
int hi_rsa_pkcs1_verify( rsa_context *ctx,
                      int mode,
                      int hash_id,
                      int hashlen,
                      const unsigned char *hash,
                      unsigned char *sig )
{
    int ret, len, siglen;
    unsigned char *p, c;
    unsigned char buf[1024];

    siglen = ctx->len;

    if( siglen < 16 || siglen > (int) sizeof( buf ) )
    {
        return( POLARSSL_ERR_RSA_BAD_INPUT_DATA );
    }
    ret = ( mode == RSA_PUBLIC )
          ? hi_rsa_public(  ctx, sig, buf )
          : hi_rsa_private( ctx, sig, buf );

    if( ret != 0 )
    {
        return( ret );
    }

    p = buf;

    switch( ctx->padding )
    {
        case RSA_PKCS_V15:

            if( *p++ != 0 || *p++ != RSA_SIGN )
                return( POLARSSL_ERR_RSA_INVALID_PADDING );

            while( *p != 0 )
            {
                if( p >= buf + siglen - 1 || *p != 0xFF )
                    return( POLARSSL_ERR_RSA_INVALID_PADDING );
                p++;
            }
            p++;
            break;

        default:

            return( POLARSSL_ERR_RSA_INVALID_PADDING );
    }

    len = siglen - (int)( p - buf );

    if( len == 34 )
    {
        c = p[13];
        p[13] = 0;

        if( memcmp( p, ASN1_HASH_MDX, 18 ) != 0 )
            return( POLARSSL_ERR_RSA_VERIFY_FAILED );

        if( ( c == 2 && hash_id == SIG_RSA_MD2 ) ||
            ( c == 4 && hash_id == SIG_RSA_MD4 ) ||
            ( c == 5 && hash_id == SIG_RSA_MD5 ) )
        {
            if( memcmp( p + 18, hash, 16 ) == 0 )
                return( 0 );
            else
                return( POLARSSL_ERR_RSA_VERIFY_FAILED );
        }
    }

    if( len == 35 && hash_id == SIG_RSA_SHA1 )
    {
        if( memcmp( p, ASN1_HASH_SHA1, 15 ) == 0 &&
            memcmp( p + 15, hash, 20 ) == 0 )
            return( 0 );
        else
            return( POLARSSL_ERR_RSA_VERIFY_FAILED );
    }
    if( ( len == 19 + 28 && p[14] == 4 && hash_id == SIG_RSA_SHA224 ) ||
        ( len == 19 + 32 && p[14] == 1 && hash_id == SIG_RSA_SHA256 ) ||
        ( len == 19 + 48 && p[14] == 2 && hash_id == SIG_RSA_SHA384 ) ||
        ( len == 19 + 64 && p[14] == 3 && hash_id == SIG_RSA_SHA512 ) )
    {
        c = p[1] - 17;
        p[1] = 17;
        p[14] = 0;

        if( p[18] == c &&
                memcmp( p, ASN1_HASH_SHA2X, 18 ) == 0 &&
                memcmp( p + 19, hash, c ) == 0 )
            return( 0 );
        else
            return( POLARSSL_ERR_RSA_VERIFY_FAILED );
    }

    if( len == hashlen && hash_id == SIG_RSA_RAW )
    {
        if( memcmp( p, hash, hashlen ) == 0 )
            return( 0 );
        else
            return( POLARSSL_ERR_RSA_VERIFY_FAILED );
    }

    return( POLARSSL_ERR_RSA_INVALID_PADDING );
}

/*
 * Free the components of an RSA key
 */
void hi_rsa_free( rsa_context *ctx )
{
    hi_mpi_free( &ctx->RQ ); hi_mpi_free( &ctx->RP ); hi_mpi_free( &ctx->RN );
    hi_mpi_free( &ctx->QP ); hi_mpi_free( &ctx->DQ ); hi_mpi_free( &ctx->DP );
    hi_mpi_free( &ctx->Q  ); hi_mpi_free( &ctx->P  ); hi_mpi_free( &ctx->D );
    hi_mpi_free( &ctx->E  ); hi_mpi_free( &ctx->N  );
}


#endif
