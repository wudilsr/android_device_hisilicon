#ifndef _ROOT_CRYPTOWRAP_H_
#define _ROOT_CRYPTOWRAP_H_

#define ENCRYPT 1
#define DECRYPT 0

void increment_char_array (u8 *arr, int size);
void do_aes256_cbc (u8 *output, const u8 *input, const u8 *iv, const u8 *key, int size, int encrypt);
void xor_two_array(const u8 *arr1, const u8 *arr2, u8 * output, int size );

#endif
