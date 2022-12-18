#ifndef LIBADPCM_ADPCM_H
#define LIBADPCM_ADPCM_H

#include <inttypes.h>

#define ADPCM_ENCODED_FRAME_SIZE 259

struct dvi_adpcm_state {
    int16_t valpred;    /* Previous predicted value */
    uint8_t index;     /* Index into stepsize table */
};

typedef struct dvi_adpcm_state adpcm_decode_state_t;

adpcm_decode_state_t *adpcm_decode_alloc(void);
void adpcm_decode_free(adpcm_decode_state_t *s);
int adpcm_decode(adpcm_decode_state_t *s, uint8_t amp[], const uint8_t *in,
         int len);

#endif
