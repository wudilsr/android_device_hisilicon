#ifndef HLS_READ_H_INCLUDED
#define HLS_READ_H_INCLUDED
#include "avformat.h"
#include "internal.h"

int hls_open_h(URLContext **puc, const char *filename, int flags, const AVIOInterruptCB *int_cb, AVDictionary **options);

int hls_read_complete(URLContext *h, int64_t offset, unsigned char *buf, int size);

int hls_read(URLContext *h, int64_t offset, unsigned char *buf, int size);

int hls_close(URLContext *h);

#endif /*HLS_READ_H_INCLUDED*/
