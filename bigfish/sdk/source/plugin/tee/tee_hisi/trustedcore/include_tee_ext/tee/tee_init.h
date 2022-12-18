#ifndef __TEE_INIT_H
#define __TEE_INIT_H

#include "tee_internal_api.h"
#include "ta_framework.h"

TEE_Result tee_init(struct TA_init_msg *init_msg, uint32_t init_build);

void tee_exit(void);

void tee_init_context(uint32_t session_id, uint32_t dev_id);

TEE_UUID* get_current_uuid(void);

uint32_t get_current_session_id(void);

uint32_t get_current_dev_id(void);

#endif
