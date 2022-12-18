#ifndef __ULIB_SHA256_H
#define __ULIB_SHA256_H
#include <inttypes.h>
#define SHA256_HASH_SIZE 32
/* 256 bit */
#define SHA256_HASH_WORDS 8
#define BLOCK_SIZE  512  
#define SHATABLE_DIR    "shatable"
#define TMP_FILE    "shatable/verify0"
struct _SHA256Context {
	uint64_t totalLength;
	uint32_t hash[SHA256_HASH_WORDS];
	uint32_t bufferLength;
	union {
		uint32_t words[16];
		uint8_t bytes[64];
	} buffer;
};
typedef struct _SHA256Context SHA256Context;
#ifdef __cplusplus
extern "C"
{
#endif
	void SHA256Init(SHA256Context * sc);
	void SHA256Update(SHA256Context * sc, const void *data, uint32_t len);
	void SHA256Final(SHA256Context * sc, uint8_t hash[SHA256_HASH_SIZE]);
#ifdef __cplusplus
}
#endif
#endif  /* __ULIB_SHA256_H */  
