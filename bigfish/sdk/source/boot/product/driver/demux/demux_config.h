
#ifndef __DEMUX_CONFIG_H__
#define __DEMUX_CONFIG_H__

#if defined(CHIP_TYPE_hi3716h) || defined(CHIP_TYPE_hi3716c)

#define HI_CRG_BASE             0x101f5000

#define HI_PVR_BASE             0x600c0000

#define HI_DEMUX_COUNT          5
#define HI_TUNER_PORT_COUNT     3
#define HI_OQ_COUNT             128
#define HI_CHANNEL_COUNT        96
#define HI_FILTER_COUNT         96

#define DMX_REGION_SUPPORT

#elif defined(CHIP_TYPE_hi3716m)

#define HI_CRG_BASE             0x101f5000

#define HI_PVR_BASE             0x600c0000

#define HI_DEMUX_COUNT          5
#define HI_TUNER_PORT_COUNT     2
#define HI_OQ_COUNT             128
#define HI_CHANNEL_COUNT        96
#define HI_FILTER_COUNT         96

#elif defined(CHIP_TYPE_hi3712)

#define HI_CRG_BASE             0x101f5000

#define HI_PVR_BASE             0x600c0000

#define HI_DEMUX_COUNT          5
#define HI_TUNER_PORT_COUNT     2
#define HI_OQ_COUNT             128
#define HI_CHANNEL_COUNT        96
#define HI_FILTER_COUNT         96

#elif defined(CHIP_TYPE_hi3716cv200es)

#define HI_PVR_BASE             0xF9C00000

#define HI_DEMUX_COUNT          7
#define HI_TUNER_PORT_COUNT     7
#define HI_OQ_COUNT             128
#define HI_CHANNEL_COUNT        96
#define HI_FILTER_COUNT         96

#elif defined(CHIP_TYPE_hi3716cv200) || defined(CHIP_TYPE_hi3716mv400)

#define HI_PVR_BASE             0xF9C00000

#define HI_DEMUX_COUNT          7
#define HI_TUNER_PORT_COUNT     5
#define HI_OQ_COUNT             128
#define HI_CHANNEL_COUNT        96
#define HI_FILTER_COUNT         96

#elif  defined(CHIP_TYPE_hi3718cv100)   \
    || defined(CHIP_TYPE_hi3719cv100)   \
    || defined(CHIP_TYPE_hi3718mv100)   \
    || defined(CHIP_TYPE_hi3719mv100)   \
    || defined(CHIP_TYPE_hi3719mv100_a)

#define HI_PVR_BASE             0xF9C00000

#define HI_DEMUX_COUNT          7
#define HI_TUNER_PORT_COUNT     2
#define HI_OQ_COUNT             128
#define HI_CHANNEL_COUNT        96
#define HI_FILTER_COUNT         96
#else

#error "Unknown chip type"

#endif

#endif  // __DEMUX_CONFIG_H__

