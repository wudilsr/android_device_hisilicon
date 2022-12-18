#include <linux/crypto.h>
#include <linux/scatterlist.h>
#include <linux/err.h>
#include "rootagent_common.h"

/* size of [iv] is 16 and [key] must be 32 bytes.
 * [size] is the size of [output] and [input].
 * [size] must be mutiple of 32. */
void do_aes256_cbc(u8 *output, const u8 *input, const u8 *iv, const u8 *key, int size, int encrypt)
{
	struct scatterlist src;
	struct scatterlist dst;
	struct blkcipher_desc desc;
	struct crypto_blkcipher *cipher = crypto_alloc_blkcipher("cbc(aes)", 0, 0);

	if (IS_ERR(cipher)) {
		antiroot_error("rootagent: crypto_alloc_blkcipher() failed. %p\n", cipher);
		return;
	}
	if (size <= 0 || size % 32 > 0) {
		antiroot_error("rootagent: do_aes256_cbc size=%d\n", size);
		return;
	}

	crypto_blkcipher_setkey(cipher, key, 32);
	crypto_blkcipher_set_iv(cipher, iv, 16);
	sg_init_table(&dst, 1);
	sg_init_table(&src, 1);
	sg_set_buf(&dst, output, size);
	sg_set_buf(&src, input, size);
	desc.tfm   = cipher;
	desc.flags = 0;

	if (encrypt)
		crypto_blkcipher_encrypt(&desc, &dst, &src, size);
	else
		crypto_blkcipher_decrypt(&desc, &dst, &src, size);

	crypto_free_blkcipher(cipher);
}

#if 0
void test (void)
{
	// refer to rfc3602
	char iv[] = "\xc7\x82\xdc\x4c\x09\x8c\x66\xcb\xd9\xcd\x27\xd8\x25\x68\x2c\x81";
	char key[] = "\x6c\x3e\xa0\x47\x76\x30\xce\x21\xa2\xce\x33\x4a\xa7\x46\xc2\xcd";
	char input[] = "This is a 48-byte message (exactly 3 AES blocks)";
	char output[48];
	do_aes256_cbc(output, input, iv, key, 48, 1);
	// output should be "d0a02b3836451753d493665d33f0e886 2dea54cdb293abc7506939276772f8d5 021c19216bad525c8579695d83ba2684"
}
#endif
