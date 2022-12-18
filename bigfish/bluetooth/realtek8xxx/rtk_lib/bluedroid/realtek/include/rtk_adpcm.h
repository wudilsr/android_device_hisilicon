#if 0
#ifndef RTK_ADPCM_H
#define RTK_ADPCM_H

#include "bt_target.h"
#include "bta_att_api.h"
#include <pthread.h>
#include "adpcm.h"


#ifdef __cplusplus
extern "C" {
#endif

#define RTK_PATCH_DEBUG
#define MAX_FRAME_SIZE 1024

typedef struct {
    adpcm_decode_state_t * adpcm_state;
    int n_20bytes_pkts;
    uint8_t buffer[ADPCM_ENCODED_FRAME_SIZE];
    pthread_mutex_t mutex;
    pthread_t tid; /* main thread id */
    int running;
    BOOLEAN  channel_status;
} tADPCM_REC_CB;

void start_adpcm_voice_rec(void);
void stop_adpcm_voice_rec(void);
BOOLEAN adpcm_voice_encode(tBTA_ATT_HSDATA *att_data);

#ifdef __cplusplus
}
#endif


#endif
#endif
