#ifndef _HI_PQ_SETTING_H_
#define _HI_PQ_SETTING_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <hi_unf_disp.h>
#include <hi_unf_pq.h>

int pq_init(void);
int pq_deinit(void);

int pq_get_brightness(int *brightness);
int pq_set_brightness(int brightness);
int pq_get_contrast(int *contrast);
int pq_set_contrast(int contrast);
int pq_get_saturation(int *saturation);
int pq_set_saturation(int saturation);
int pq_get_hue(int *hue);
int pq_set_hue(int hue);
int pq_save_image(int bright, int contrast, int saturation, int hue);

int pq_set_engine_mode(int mode);

int pq_set_color_enhance(HI_UNF_PQ_COLOR_ENHANCE_S colorEnhanceParam);
int pq_get_color_enhance(HI_UNF_PQ_COLOR_ENHANCE_S * pColorEnhanceParam);
int pq_set_dynamic_contrast(int dcilevel);
int pq_get_dynamic_contrast(int * pDcilevel);
int pq_set_sharpness(int sharpness);
int pq_get_sharpness(int * pSharpness);
int pq_set_sr_mode(HI_UNF_PQ_SR_DEMO_E srmode);
int pq_get_sr_mode(HI_UNF_PQ_SR_DEMO_E * pSrmode);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
