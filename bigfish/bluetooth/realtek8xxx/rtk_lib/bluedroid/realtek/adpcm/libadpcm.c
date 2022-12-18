#include "adpcm.h"
#include "dvi_adpcm.h"

#include <stdlib.h>


adpcm_decode_state_t *adpcm_decode_alloc(void)
{
    adpcm_decode_state_t *s;

    s = malloc(sizeof(adpcm_decode_state_t));
    if (!s)
        return NULL;

    dvi_adpcm_init(s,0);

    return s;
}

void adpcm_decode_free(adpcm_decode_state_t *s)
{
    free(s);
}

int adpcm_decode(adpcm_decode_state_t *s, uint8_t amp[], const uint8_t *in, int len)
{
    int out_size;
    //return IMAAdpcm_DecodeBuffer(in, amp, len, s);
    dvi_adpcm_decode(in, len, amp, &out_size, s);

    return out_size;
}
