#ifndef __SEC_MMZ_COMMON_H
#define __SEC_MMZ_COMMON_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

typedef enum {
	HI_MMZ_NEW = 0x1000,
	HI_MMZ_DEL,
	HI_MMZ_CP_CA2TA,
	HI_MMZ_CP_TA2CA,
	HI_MMZ_CP_TA2TA,
	HI_MMZ_TEST,
	HI_MMZ_DEBUG
} hi_mmz_cmd;

#define SEC_MMZ_UUID 0x79b77788, 0x9789, 0x4a7a, \
	{ 0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf5 }

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* __SEC_MMZ_COMMON_H */
