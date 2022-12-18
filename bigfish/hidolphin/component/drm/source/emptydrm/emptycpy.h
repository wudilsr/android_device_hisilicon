#ifndef __EMPTYCPY_H__
#define __EMPTYCPY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

int initMMZBuffer();
int deinitMMZBuffer();
int emptyca2ta(const unsigned char* inputaddr,unsigned int TEEAddr, int  len);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
