#ifndef _dvi_adpcm_h
#define _dvi_adpcm_h

#include <stdint.h>
#include "adpcm.h"

typedef struct dvi_adpcm_state dvi_adpcm_state_t;

int dvi_adpcm_decode(const uint8_t *in_buf, int in_size, void  *out_buf, int *out_size, void *state);
void dvi_adpcm_init(dvi_adpcm_state_t *, double);
#endif
