
#ifndef __DRV_DEMUX_CONFIG_H__
#define __DRV_DEMUX_CONFIG_H__
/*==============================CHIP_TYPE_hi3716h,CHIP_TYPE_hi3716c==============================*/
#if defined(CHIP_TYPE_hi3716h) || defined(CHIP_TYPE_hi3716c)

#define DMX_INT_NUM                     (52 + 32)

#define HI_CRG_BASE                     IO_ADDRESS(0x101f5000)

#define HI_PVR_BASE                     IO_ADDRESS(0x600c0000)

#define DMX_CNT                         5

#define DMX_REC_CNT                     3

#define DMX_IFPORT_CNT                  1
#define DMX_TSIPORT_CNT                 2
#define DMX_TSOPORT_CNT                 0   
#define DMX_TUNERPORT_CNT               (DMX_IFPORT_CNT + DMX_TSIPORT_CNT)
#define DMX_RAMPORT_CNT                 4

#define DMX_CHANNEL_CNT                 96
#define DMX_AV_CHANNEL_CNT              32
#define DMX_PCR_CHANNEL_CNT             16

#define DMX_FILTER_CNT                  96

#define DMX_KEY_CNT                     32

#define DMX_FQ_CNT                      40
#define DMX_OQ_CNT                      128

#define DMX_USE_ECM

#define DMX_RAM_PORT_OFFSET             3

#define DMX_DESCRAMBLER_VERSION_0

#define DMX_DESCRAMBLER_TYPE_CSA3_SUPPORT

#define DMX_REGION_SUPPORT
/*======================================CHIP_TYPE_hi3716m======================================*/
#elif defined(CHIP_TYPE_hi3716m)

#define DMX_INT_NUM                     (52 + 32)

#define HI_CRG_BASE                     IO_ADDRESS(0x101f5000)

#define HI_PVR_BASE                     IO_ADDRESS(0x600c0000)

#define DMX_CNT                         5

#define DMX_REC_CNT                     3

#define DMX_IFPORT_CNT                  1
#define DMX_TSIPORT_CNT                 2
#define DMX_TSOPORT_CNT                 1   /*mv200 没有，mv300 有一路TSO*/    
#define DMX_TUNERPORT_CNT               (DMX_IFPORT_CNT + DMX_TSIPORT_CNT)
#define DMX_RAMPORT_CNT                 4

#define DMX_CHANNEL_CNT                 96
#define DMX_AV_CHANNEL_CNT              32
#define DMX_PCR_CHANNEL_CNT             16

#define DMX_FILTER_CNT                  96

#define DMX_KEY_CNT                     32

#define DMX_FQ_CNT                      40
#define DMX_OQ_CNT                      128

#define DMX_USE_ECM

#define DMX_RAM_PORT_OFFSET             3

#define DMX_SCD_NEW_FLT_SUPPORT

#define DMX_DESCRAMBLER_VERSION_0
#define DMX_DESCRAMBLER_VERSION_1

#define DMX_DESCRAMBLER_TYPE_CSA3_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SPE_SUPPORT
#define DMX_DESCRAMBLER_TYPE_DES_SUPPORT
#define DMX_DESCRAMBLER_TYPE_AES_NS_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_NS_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_IPTV_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_ECB_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_CBC_SUPPORT
#define DMX_DESCRAMBLER_TYPE_AES_CBC_SUPPORT

#define DMX_RAM_PORT_SET_LENGTH_SUPPORT
/*=============================================CHIP_TYPE_hi3712,=========================================*/
#elif defined(CHIP_TYPE_hi3712)

#define DMX_INT_NUM                     (52 + 32)

#define HI_CRG_BASE                     IO_ADDRESS(0x101f5000)

#define HI_PVR_BASE                     IO_ADDRESS(0x600c0000)

#define DMX_CNT                         5

#define DMX_REC_CNT                     DMX_CNT

#define DMX_IFPORT_CNT                  1
#define DMX_TSIPORT_CNT                 1
#define DMX_TSOPORT_CNT                 0  
#define DMX_TUNERPORT_CNT               (DMX_IFPORT_CNT + DMX_TSIPORT_CNT)
#define DMX_RAMPORT_CNT                 2

#define DMX_CHANNEL_CNT                 96
#define DMX_AV_CHANNEL_CNT              32
#define DMX_PCR_CHANNEL_CNT             16

#define DMX_FILTER_CNT                  96

#define DMX_KEY_CNT                     32

#define DMX_FQ_CNT                      40
#define DMX_OQ_CNT                      128

#define DMX_RAM_PORT_OFFSET             3

#define DMX_SCD_NEW_FLT_SUPPORT

#define DMX_DESCRAMBLER_VERSION_1

#define DMX_DESCRAMBLER_TYPE_SPE_SUPPORT
#define DMX_DESCRAMBLER_TYPE_DES_SUPPORT
#define DMX_DESCRAMBLER_TYPE_AES_NS_SUPPORT
#define DMX_DESCRAMBLER_TYPE_AES_CBC_SUPPORT

#define DMX_TUNER_PORT_SERIAL_2BIT_AND_SERIAL_NOSYNC_SUPPORT

#define DMX_RAM_PORT_SET_LENGTH_SUPPORT
#define DMX_RAM_PORT_AUTO_SCAN_SUPPORT

#define DMX_SECTION_PARSE_NOPUSI_SUPPORT

#define DMX_FILTER_DEPTH_SUPPORT

/*=============================================CHIP_TYPE_hi3716cv200=========================================*/
#elif defined(CHIP_TYPE_hi3716cv200) || defined (CHIP_TYPE_hi3716mv400)

#define DMX_INT_NUM                     (82 + 32)

#define HI_PVR_BASE                     IO_ADDRESS(0xF9C00000)

#define DMX_CNT                         7

#define DMX_REC_CNT                     DMX_CNT

#define DMX_IFPORT_CNT                  1
#define DMX_TSIPORT_CNT                 4
#define DMX_TSOPORT_CNT                 2 /*两路串行或者一路并行*/  
#define DMX_TUNERPORT_CNT               (DMX_IFPORT_CNT + DMX_TSIPORT_CNT)
#define DMX_RAMPORT_CNT                 5

#define DMX_CHANNEL_CNT                 96
#define DMX_AV_CHANNEL_CNT              32
#define DMX_PCR_CHANNEL_CNT             16

#define DMX_FILTER_CNT                  96

#define DMX_KEY_CNT                     32

#define DMX_FQ_CNT                      40
#define DMX_OQ_CNT                      128

#define DMX_RAM_PORT_OFFSET             15

#define DMX_SCD_NEW_FLT_SUPPORT

#define DMX_DESCRAMBLER_VERSION_1

#define DMX_DESCRAMBLER_TYPE_CSA3_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SPE_SUPPORT
#define DMX_DESCRAMBLER_TYPE_DES_SUPPORT
#define DMX_DESCRAMBLER_TYPE_AES_NS_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_NS_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_IPTV_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_ECB_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_CBC_SUPPORT
#define DMX_DESCRAMBLER_TYPE_AES_CBC_SUPPORT
#define DMX_DESCRAMBLER_TYPE_DES_IPTV_SUPPORT
#define DMX_DESCRAMBLER_TYPE_TDES_SUPPORT

#define DMX_TUNER_PORT_SERIAL_2BIT_AND_SERIAL_NOSYNC_SUPPORT

#define DMX_RAM_PORT_SET_LENGTH_SUPPORT
#define DMX_RAM_PORT_AUTO_SCAN_SUPPORT

#define DMX_SECTION_PARSE_NOPUSI_SUPPORT

#define DMX_FILTER_DEPTH_SUPPORT

#define DMX_REC_EXCLUDE_PID_SUPPORT
#define DMX_REC_EXCLUDE_PID_NUM         (30)

#define DMX_SUPPORT_RAM_CLK_AUTO_CTL

/*==============================CHIP_TYPE_hi3719cv100,CHIP_TYPE_hi3719mv100==============================*/
#elif defined(CHIP_TYPE_hi3719cv100) || defined (CHIP_TYPE_hi3719mv100)

#define DMX_INT_NUM                     (82 + 32)

#define HI_PVR_BASE                     IO_ADDRESS(0xF9C00000)

#define DMX_CNT                         7

#define DMX_REC_CNT                     DMX_CNT

#ifdef CHIP_TYPE_hi3719cv100
    #define DMX_IFPORT_CNT               1
	#define DMX_TSIPORT_CNT              4
	#define DMX_RAMPORT_CNT              5
#elif defined (CHIP_TYPE_hi3719mv100)
    #define DMX_IFPORT_CNT               0
	#define DMX_TSIPORT_CNT              2
	#define DMX_RAMPORT_CNT              6
#endif

#define DMX_TSOPORT_CNT                0

#define DMX_TUNERPORT_CNT               (DMX_IFPORT_CNT + DMX_TSIPORT_CNT)

#define DMX_CHANNEL_CNT                 96
#define DMX_AV_CHANNEL_CNT              32
#define DMX_PCR_CHANNEL_CNT             16

#define DMX_FILTER_CNT                  96

#define DMX_KEY_CNT                     32

#define DMX_FQ_CNT                      40
#define DMX_OQ_CNT                      128

/*0xf9c03a04 , switch :
0x00： 关闭TS源；
0x01～0x07：分别选择DVB下的TS1～TS7端口码流；
0x10～0x15：分别选择IP下的IP0～IP5内部端口码流。*/
#define DMX_RAM_PORT_OFFSET             15         


#define DMX_SCD_NEW_FLT_SUPPORT

#define DMX_DESCRAMBLER_VERSION_1

#define DMX_DESCRAMBLER_TYPE_SPE_SUPPORT
#define DMX_DESCRAMBLER_TYPE_DES_SUPPORT
#define DMX_DESCRAMBLER_TYPE_AES_NS_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_NS_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_IPTV_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_ECB_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_CBC_SUPPORT
#define DMX_DESCRAMBLER_TYPE_AES_CBC_SUPPORT
#define DMX_DESCRAMBLER_TYPE_DES_IPTV_SUPPORT
#define DMX_DESCRAMBLER_TYPE_TDES_SUPPORT

#define DMX_TUNER_PORT_SERIAL_2BIT_AND_SERIAL_NOSYNC_SUPPORT

#define DMX_RAM_PORT_SET_LENGTH_SUPPORT
#define DMX_RAM_PORT_AUTO_SCAN_SUPPORT

#define DMX_SECTION_PARSE_NOPUSI_SUPPORT

#define DMX_FILTER_DEPTH_SUPPORT

#define DMX_REC_EXCLUDE_PID_SUPPORT
#define DMX_REC_EXCLUDE_PID_NUM         (30)
#define DMX_REC_TIME_STAMP_SUPPORT      

/*=================================CHIP_TYPE_hi3718cv100,CHIP_TYPE_hi3718mv100==================================*/
#elif defined(CHIP_TYPE_hi3718cv100)  || defined (CHIP_TYPE_hi3718mv100) /*not support descrambler*/

#define DMX_INT_NUM                     (82 + 32)

#define HI_PVR_BASE                     IO_ADDRESS(0xF9C00000)

#define DMX_CNT                         7

#define DMX_REC_CNT                     DMX_CNT

#ifdef CHIP_TYPE_hi3718cv100
    #define DMX_IFPORT_CNT               0
	#define DMX_TSIPORT_CNT              0
	#define DMX_RAMPORT_CNT              5
#elif defined (CHIP_TYPE_hi3718mv100)
    #define DMX_IFPORT_CNT               0
	#define DMX_TSIPORT_CNT              0
	#define DMX_RAMPORT_CNT              6
#endif
#define DMX_TSOPORT_CNT                0
#define DMX_TUNERPORT_CNT               (DMX_IFPORT_CNT + DMX_TSIPORT_CNT)
#define DMX_CHANNEL_CNT                 96
#define DMX_AV_CHANNEL_CNT              32
#define DMX_PCR_CHANNEL_CNT             16

#define DMX_FILTER_CNT                  96

#define DMX_KEY_CNT                     32

#define DMX_FQ_CNT                      40
#define DMX_OQ_CNT                      128

/*0xf9c03a04 , switch :
0x00： 关闭TS源；
0x01～0x07：分别选择DVB下的TS1～TS7端口码流；
0x10～0x15：分别选择IP下的IP0～IP5内部端口码流。*/
#define DMX_RAM_PORT_OFFSET             15         


#define DMX_SCD_NEW_FLT_SUPPORT

#define DMX_DESCRAMBLER_VERSION_1


#define DMX_TUNER_PORT_SERIAL_2BIT_AND_SERIAL_NOSYNC_SUPPORT

#define DMX_RAM_PORT_SET_LENGTH_SUPPORT
#define DMX_RAM_PORT_AUTO_SCAN_SUPPORT

#define DMX_SECTION_PARSE_NOPUSI_SUPPORT

#define DMX_FILTER_DEPTH_SUPPORT

#define DMX_REC_EXCLUDE_PID_SUPPORT
#define DMX_REC_EXCLUDE_PID_NUM         (30)
/*=============================================CHIP_TYPE_hi3796cv100/CHIP_TYPE_hi3798cv100=========================================*/
#elif defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)

#define DMX_INT_NUM                     (82 + 32)/*A9一共有128个中断，A9自己占用32个*/

#define HI_PVR_BASE                     IO_ADDRESS(0xF9C00000)

#define DMX_CNT                         7

#define DMX_REC_CNT                     DMX_CNT

#define DMX_IFPORT_CNT                  2
#define DMX_TSIPORT_CNT                 6
#define DMX_TSOPORT_CNT                 2 /*两路串行或者一路并行*/  
#define DMX_TUNERPORT_CNT               (DMX_IFPORT_CNT + DMX_TSIPORT_CNT)
#define DMX_RAMPORT_CNT                 6

#define DMX_CHANNEL_CNT                 96
#define DMX_AV_CHANNEL_CNT              32
#define DMX_PCR_CHANNEL_CNT             16

#define DMX_FILTER_CNT                  96

#define DMX_KEY_CNT                     32

#define DMX_FQ_CNT                      40
#define DMX_OQ_CNT                      128

#define DMX_RAM_PORT_OFFSET             15

#define DMX_SCD_NEW_FLT_SUPPORT

#define DMX_DESCRAMBLER_VERSION_1

#define DMX_DESCRAMBLER_TYPE_CSA3_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SPE_SUPPORT
#define DMX_DESCRAMBLER_TYPE_DES_SUPPORT
#define DMX_DESCRAMBLER_TYPE_AES_NS_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_NS_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_IPTV_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_ECB_SUPPORT
#define DMX_DESCRAMBLER_TYPE_SMS4_CBC_SUPPORT
#define DMX_DESCRAMBLER_TYPE_AES_CBC_SUPPORT
#define DMX_DESCRAMBLER_TYPE_DES_IPTV_SUPPORT
#define DMX_DESCRAMBLER_TYPE_TDES_SUPPORT

#define DMX_TUNER_PORT_SERIAL_2BIT_AND_SERIAL_NOSYNC_SUPPORT

#define DMX_RAM_PORT_SET_LENGTH_SUPPORT
#define DMX_RAM_PORT_AUTO_SCAN_SUPPORT

#define DMX_SECTION_PARSE_NOPUSI_SUPPORT

#define DMX_FILTER_DEPTH_SUPPORT

#define DMX_REC_EXCLUDE_PID_SUPPORT
#define DMX_REC_EXCLUDE_PID_NUM         (30)
#define DMX_REC_TIME_STAMP_SUPPORT       
#elif defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)

#define DMX_INT_NUM                     (82 + 32)/*A9一共有128个中断，A9自己占用32个*/

#define HI_PVR_BASE                     IO_ADDRESS(0xF9C00000)

#define DMX_CNT                         7

#define DMX_REC_CNT                     DMX_CNT

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
#define DMX_IFPORT_CNT                  0
#define DMX_TSIPORT_CNT                 2
#define DMX_RAMPORT_CNT                 3
#endif

#define DMX_TSOPORT_CNT                 0 
#define DMX_TUNERPORT_CNT               (DMX_IFPORT_CNT + DMX_TSIPORT_CNT)

#define DMX_CHANNEL_CNT                 96
#define DMX_AV_CHANNEL_CNT              32
#define DMX_PCR_CHANNEL_CNT             16

#define DMX_FILTER_CNT                  96

#define DMX_KEY_CNT                     32

#define DMX_FQ_CNT                      40
#define DMX_OQ_CNT                      128

#define DMX_RAM_PORT_OFFSET             15

#define DMX_SCD_NEW_FLT_SUPPORT

#define DMX_DESCRAMBLER_VERSION_1

#define DMX_DESCRAMBLER_TYPE_SPE_SUPPORT
#define DMX_DESCRAMBLER_TYPE_DES_SUPPORT
#define DMX_DESCRAMBLER_TYPE_AES_NS_SUPPORT
#define DMX_DESCRAMBLER_TYPE_AES_CBC_SUPPORT
#define DMX_DESCRAMBLER_TYPE_DES_IPTV_SUPPORT
#define DMX_DESCRAMBLER_TYPE_TDES_SUPPORT

#define DMX_TUNER_PORT_SERIAL_2BIT_AND_SERIAL_NOSYNC_SUPPORT

#define DMX_RAM_PORT_SET_LENGTH_SUPPORT
#define DMX_RAM_PORT_AUTO_SCAN_SUPPORT

#define DMX_SECTION_PARSE_NOPUSI_SUPPORT

#define DMX_FILTER_DEPTH_SUPPORT

#define DMX_REC_EXCLUDE_PID_SUPPORT
#define DMX_REC_EXCLUDE_PID_NUM         (30)

#define DMX_SUPPORT_RAM_CLK_AUTO_CTL
#define DMX_SUPPORT_DMX_CLK_DYNAMIC_TUNE
#else

#error must define CHIP_TYPE

#endif

#endif  // __DRV_DEMUX_CONFIG_H__

