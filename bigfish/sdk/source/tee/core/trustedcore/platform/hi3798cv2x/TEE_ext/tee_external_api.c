#include "tee_external_api.h"

extern void *asm_memmove(void *dest, const void *src, UINT32 n);
extern void *asm_memcpy(void *dest, const void *src, UINT32 n);

void ASM_MemMove(void* dest, void* src, UINT32 size)
{
	    asm_memmove(dest, src, size);
}
void ASM_MemCopy(void* dest, void* src, UINT32 size)
{
	    asm_memcpy(dest, src, size);
}

