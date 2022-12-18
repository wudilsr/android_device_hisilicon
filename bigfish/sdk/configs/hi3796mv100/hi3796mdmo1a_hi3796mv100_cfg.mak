#
# Automatically generated make config: don't edit
# SDK version: KERNELVERSION
# Fri Mar 20 14:23:40 2015
#

#
# Base
#
CFG_LINUX_PRODUCT=y
# CFG_ANDROID_PRODUCT is not set
CFG_PRODUCT_TYPE=linux
# CFG_HI3716CV200 is not set
# CFG_HI3716MV400 is not set
# CFG_HI3718CV100 is not set
# CFG_HI3718MV100 is not set
# CFG_HI3719CV100 is not set
# CFG_HI3719MV100 is not set
# CFG_HI3796CV100 is not set
# CFG_HI3798CV100 is not set
# CFG_HI3798MV100 is not set
CFG_HI3796MV100=y
# CFG_HI3798CV200_A is not set
CFG_HI_CHIP_TYPE=hi3796mv100
CFG_ARM_HISIV200_LINUX=y
# CFG_ARM_HISTBV300_LINUX is not set
CFG_HI_TOOLCHAINS_NAME=arm-hisiv200-linux
# CFG_HI_LOADER_SUPPORT is not set
# CFG_HI_OPTM_SIZE_SUPPORT is not set

#
# Board
#

#
# Ethernet Config
#
CFG_HI_ETH_SUPPORT=y

#
# Flash Config
#
# CFG_HI_NAND_SUPPORT is not set
CFG_HI_EMMC_SUPPORT=y

#
# Tuner Config
#
CFG_HI_TUNER_NUMBER=1

#
# First Tuner Config
#
# CFG_HI_TUNER_SIGNAL_CAB is not set
CFG_HI_TUNER_SIGNAL_SAT=y
# CFG_HI_TUNER_SIGNAL_DVB_T is not set
# CFG_HI_TUNER_SIGNAL_DVB_T2 is not set
# CFG_HI_TUNER_SIGNAL_ISDB_T is not set
# CFG_HI_TUNER_SIGNAL_ATSC_T is not set
# CFG_HI_TUNER_SIGNAL_DTMB is not set
# CFG_HI_TUNER_DEV_TYPE_XG_3BL is not set
# CFG_HI_TUNER_DEV_TYPE_CD1616 is not set
# CFG_HI_TUNER_DEV_TYPE_ALPS_TDAE is not set
# CFG_HI_TUNER_DEV_TYPE_TDCC is not set
# CFG_HI_TUNER_DEV_TYPE_TDA18250 is not set
# CFG_HI_TUNER_DEV_TYPE_CD1616_DOUBLE is not set
# CFG_HI_TUNER_DEV_TYPE_MT2081 is not set
# CFG_HI_TUNER_DEV_TYPE_TMX7070X is not set
# CFG_HI_TUNER_DEV_TYPE_R820C is not set
# CFG_HI_TUNER_DEV_TYPE_MXL203 is not set
CFG_HI_TUNER_DEV_TYPE_AV2011=y
# CFG_HI_TUNER_DEV_TYPE_AV2018 is not set
# CFG_HI_TUNER_DEV_TYPE_SHARP7903 is not set
# CFG_HI_TUNER_DEV_TYPE_MXL101 is not set
# CFG_HI_TUNER_DEV_TYPE_MXL603 is not set
# CFG_HI_TUNER_DEV_TYPE_CXD2861 is not set
# CFG_HI_TUNER_DEV_TYPE_IT9170 is not set
# CFG_HI_TUNER_DEV_TYPE_TDA6651 is not set
# CFG_HI_TUNER_DEV_TYPE_TDA18250B is not set
# CFG_HI_TUNER_DEV_TYPE_M88TS2022 is not set
# CFG_HI_TUNER_DEV_TYPE_RDA5815 is not set
# CFG_HI_TUNER_DEV_TYPE_MXL254 is not set
# CFG_HI_TUNER_DEV_TYPE_SI2147 is not set
# CFG_HI_TUNER_DEV_TYPE_RAFAEL836 is not set
# CFG_HI_TUNER_DEV_TYPE_MXL608 is not set
# CFG_HI_TUNER_DEV_TYPE_MXL214 is not set
# CFG_HI_TUNER_DEV_TYPE_TDA18280 is not set
# CFG_HI_TUNER_DEV_TYPE_TDA182I5A is not set
# CFG_HI_TUNER_DEV_TYPE_SI2144 is not set
CFG_HI_TUNER_DEV_ADDR=0xc6
# CFG_HI_DEMOD_DEV_TYPE_NONE is not set
# CFG_HI_DEMOD_DEV_TYPE_3130I is not set
# CFG_HI_DEMOD_DEV_TYPE_3130E is not set
# CFG_HI_DEMOD_DEV_TYPE_J83B is not set
# CFG_HI_DEMOD_DEV_TYPE_AVL6211 is not set
# CFG_HI_DEMOD_DEV_TYPE_MXL101 is not set
# CFG_HI_DEMOD_DEV_TYPE_MN88472 is not set
# CFG_HI_DEMOD_DEV_TYPE_CXD2837 is not set
# CFG_HI_DEMOD_DEV_TYPE_IT9170 is not set
CFG_HI_DEMOD_DEV_TYPE_3136=y
# CFG_HI_DEMOD_DEV_TYPE_3137 is not set
# CFG_HI_DEMOD_DEV_TYPE_MXL254 is not set
# CFG_HI_DEMOD_DEV_TYPE_MXL214 is not set
# CFG_HI_DEMOD_DEV_TYPE_TDA18280 is not set
# CFG_HI_DEMOD_DEV_TYPE_HIDTV100 is not set
CFG_HI_DEMOD_DEV_ADDR=0xb4
# CFG_HI_DEMOD_TS_DEFAULT is not set
# CFG_HI_DEMOD_TS_PARALLEL_MODE_A is not set
# CFG_HI_DEMOD_TS_PARALLEL_MODE_B is not set
CFG_HI_DEMOD_TS_SERIAL=y
# CFG_HI_DEMOD_TS_SERIAL_50 is not set
# CFG_HI_DEMOD_TS_SERIAL_2BIT is not set
CFG_HI_DEMOD_I2C=y
# CFG_HI_DEMOD_GPIO is not set
CFG_HI_DEMOD_I2C_CHANNEL=0
CFG_HI_DEMOD_RESET_GPIO=0xd
CFG_HI_DEMUX_PORT=33

#
# Satellite Attribute Config
#
CFG_HI_DEMOD_REF_CLOCK=24000
CFG_HI_TUNER_MAX_LPF=34
CFG_HI_TUNER_I2C_CLOCK=400
CFG_HI_TUNER_RFAGC_INVERT=y
# CFG_HI_TUNER_RFAGC_NORMAL is not set
CFG_HI_TUNER_IQSPECTRUM_NORMAL=y
# CFG_HI_TUNER_IQSPECTRUM_INVERT is not set
# CFG_HI_TUNER_TSCLK_POLAR_FALLING is not set
CFG_HI_TUNER_TSCLK_POLAR_RISING=y
CFG_HI_TUNER_TS_FORMAT_TS=y
# CFG_HI_TUNER_TS_FORMAT_TSP is not set
CFG_HI_TUNER_TS_SERIAL_PIN_0=y
# CFG_HI_TUNER_TS_SERIAL_PIN_7 is not set
CFG_HI_TUNER_DISEQCWAVE_NORMAL=y
# CFG_HI_TUNER_DISEQCWAVE_ENVELOPE is not set
# CFG_HI_LNBCTRL_DEV_TYPE_NONE is not set
CFG_HI_LNBCTRL_DEV_TYPE_MPS8125=y
# CFG_HI_LNBCTRL_DEV_TYPE_ISL9492 is not set
CFG_HI_LNB_CTRL_DEMOD=y
# CFG_HI_LNB_CTRL_GPIO is not set
CFG_HI_LNBCTRL_DEV_ADDR=0x0
CFG_HI_TUNER_TSOUT=y
# CFG_HI_TUNER_OUTPUT_PIN0_TSDAT0 is not set
# CFG_HI_TUNER_OUTPUT_PIN0_TSDAT1 is not set
# CFG_HI_TUNER_OUTPUT_PIN0_TSDAT2 is not set
# CFG_HI_TUNER_OUTPUT_PIN0_TSDAT3 is not set
# CFG_HI_TUNER_OUTPUT_PIN0_TSDAT4 is not set
# CFG_HI_TUNER_OUTPUT_PIN0_TSDAT5 is not set
# CFG_HI_TUNER_OUTPUT_PIN0_TSDAT6 is not set
CFG_HI_TUNER_OUTPUT_PIN0_TSDAT7=y
# CFG_HI_TUNER_OUTPUT_PIN0_TSSYNC is not set
# CFG_HI_TUNER_OUTPUT_PIN0_TSVLD is not set
# CFG_HI_TUNER_OUTPUT_PIN0_TSERR is not set
# CFG_HI_TUNER_OUTPUT_PIN1_TSDAT0 is not set
CFG_HI_TUNER_OUTPUT_PIN1_TSDAT1=y
# CFG_HI_TUNER_OUTPUT_PIN1_TSDAT2 is not set
# CFG_HI_TUNER_OUTPUT_PIN1_TSDAT3 is not set
# CFG_HI_TUNER_OUTPUT_PIN1_TSDAT4 is not set
# CFG_HI_TUNER_OUTPUT_PIN1_TSDAT5 is not set
# CFG_HI_TUNER_OUTPUT_PIN1_TSDAT6 is not set
# CFG_HI_TUNER_OUTPUT_PIN1_TSDAT7 is not set
# CFG_HI_TUNER_OUTPUT_PIN1_TSSYNC is not set
# CFG_HI_TUNER_OUTPUT_PIN1_TSVLD is not set
# CFG_HI_TUNER_OUTPUT_PIN1_TSERR is not set
# CFG_HI_TUNER_OUTPUT_PIN2_TSDAT0 is not set
# CFG_HI_TUNER_OUTPUT_PIN2_TSDAT1 is not set
CFG_HI_TUNER_OUTPUT_PIN2_TSDAT2=y
# CFG_HI_TUNER_OUTPUT_PIN2_TSDAT3 is not set
# CFG_HI_TUNER_OUTPUT_PIN2_TSDAT4 is not set
# CFG_HI_TUNER_OUTPUT_PIN2_TSDAT5 is not set
# CFG_HI_TUNER_OUTPUT_PIN2_TSDAT6 is not set
# CFG_HI_TUNER_OUTPUT_PIN2_TSDAT7 is not set
# CFG_HI_TUNER_OUTPUT_PIN2_TSSYNC is not set
# CFG_HI_TUNER_OUTPUT_PIN2_TSVLD is not set
# CFG_HI_TUNER_OUTPUT_PIN2_TSERR is not set
# CFG_HI_TUNER_OUTPUT_PIN3_TSDAT0 is not set
# CFG_HI_TUNER_OUTPUT_PIN3_TSDAT1 is not set
# CFG_HI_TUNER_OUTPUT_PIN3_TSDAT2 is not set
CFG_HI_TUNER_OUTPUT_PIN3_TSDAT3=y
# CFG_HI_TUNER_OUTPUT_PIN3_TSDAT4 is not set
# CFG_HI_TUNER_OUTPUT_PIN3_TSDAT5 is not set
# CFG_HI_TUNER_OUTPUT_PIN3_TSDAT6 is not set
# CFG_HI_TUNER_OUTPUT_PIN3_TSDAT7 is not set
# CFG_HI_TUNER_OUTPUT_PIN3_TSSYNC is not set
# CFG_HI_TUNER_OUTPUT_PIN3_TSVLD is not set
# CFG_HI_TUNER_OUTPUT_PIN3_TSERR is not set
# CFG_HI_TUNER_OUTPUT_PIN4_TSDAT0 is not set
# CFG_HI_TUNER_OUTPUT_PIN4_TSDAT1 is not set
# CFG_HI_TUNER_OUTPUT_PIN4_TSDAT2 is not set
# CFG_HI_TUNER_OUTPUT_PIN4_TSDAT3 is not set
CFG_HI_TUNER_OUTPUT_PIN4_TSDAT4=y
# CFG_HI_TUNER_OUTPUT_PIN4_TSDAT5 is not set
# CFG_HI_TUNER_OUTPUT_PIN4_TSDAT6 is not set
# CFG_HI_TUNER_OUTPUT_PIN4_TSDAT7 is not set
# CFG_HI_TUNER_OUTPUT_PIN4_TSSYNC is not set
# CFG_HI_TUNER_OUTPUT_PIN4_TSVLD is not set
# CFG_HI_TUNER_OUTPUT_PIN4_TSERR is not set
# CFG_HI_TUNER_OUTPUT_PIN5_TSDAT0 is not set
# CFG_HI_TUNER_OUTPUT_PIN5_TSDAT1 is not set
# CFG_HI_TUNER_OUTPUT_PIN5_TSDAT2 is not set
# CFG_HI_TUNER_OUTPUT_PIN5_TSDAT3 is not set
# CFG_HI_TUNER_OUTPUT_PIN5_TSDAT4 is not set
CFG_HI_TUNER_OUTPUT_PIN5_TSDAT5=y
# CFG_HI_TUNER_OUTPUT_PIN5_TSDAT6 is not set
# CFG_HI_TUNER_OUTPUT_PIN5_TSDAT7 is not set
# CFG_HI_TUNER_OUTPUT_PIN5_TSSYNC is not set
# CFG_HI_TUNER_OUTPUT_PIN5_TSVLD is not set
# CFG_HI_TUNER_OUTPUT_PIN5_TSERR is not set
# CFG_HI_TUNER_OUTPUT_PIN6_TSDAT0 is not set
# CFG_HI_TUNER_OUTPUT_PIN6_TSDAT1 is not set
# CFG_HI_TUNER_OUTPUT_PIN6_TSDAT2 is not set
# CFG_HI_TUNER_OUTPUT_PIN6_TSDAT3 is not set
# CFG_HI_TUNER_OUTPUT_PIN6_TSDAT4 is not set
# CFG_HI_TUNER_OUTPUT_PIN6_TSDAT5 is not set
CFG_HI_TUNER_OUTPUT_PIN6_TSDAT6=y
# CFG_HI_TUNER_OUTPUT_PIN6_TSDAT7 is not set
# CFG_HI_TUNER_OUTPUT_PIN6_TSSYNC is not set
# CFG_HI_TUNER_OUTPUT_PIN6_TSVLD is not set
# CFG_HI_TUNER_OUTPUT_PIN6_TSERR is not set
CFG_HI_TUNER_OUTPUT_PIN7_TSDAT0=y
# CFG_HI_TUNER_OUTPUT_PIN7_TSDAT1 is not set
# CFG_HI_TUNER_OUTPUT_PIN7_TSDAT2 is not set
# CFG_HI_TUNER_OUTPUT_PIN7_TSDAT3 is not set
# CFG_HI_TUNER_OUTPUT_PIN7_TSDAT4 is not set
# CFG_HI_TUNER_OUTPUT_PIN7_TSDAT5 is not set
# CFG_HI_TUNER_OUTPUT_PIN7_TSDAT6 is not set
# CFG_HI_TUNER_OUTPUT_PIN7_TSDAT7 is not set
# CFG_HI_TUNER_OUTPUT_PIN7_TSSYNC is not set
# CFG_HI_TUNER_OUTPUT_PIN7_TSVLD is not set
# CFG_HI_TUNER_OUTPUT_PIN7_TSERR is not set
# CFG_HI_TUNER_OUTPUT_PIN8_TSDAT0 is not set
# CFG_HI_TUNER_OUTPUT_PIN8_TSDAT1 is not set
# CFG_HI_TUNER_OUTPUT_PIN8_TSDAT2 is not set
# CFG_HI_TUNER_OUTPUT_PIN8_TSDAT3 is not set
# CFG_HI_TUNER_OUTPUT_PIN8_TSDAT4 is not set
# CFG_HI_TUNER_OUTPUT_PIN8_TSDAT5 is not set
# CFG_HI_TUNER_OUTPUT_PIN8_TSDAT6 is not set
# CFG_HI_TUNER_OUTPUT_PIN8_TSDAT7 is not set
CFG_HI_TUNER_OUTPUT_PIN8_TSSYNC=y
# CFG_HI_TUNER_OUTPUT_PIN8_TSVLD is not set
# CFG_HI_TUNER_OUTPUT_PIN8_TSERR is not set
# CFG_HI_TUNER_OUTPUT_PIN9_TSDAT0 is not set
# CFG_HI_TUNER_OUTPUT_PIN9_TSDAT1 is not set
# CFG_HI_TUNER_OUTPUT_PIN9_TSDAT2 is not set
# CFG_HI_TUNER_OUTPUT_PIN9_TSDAT3 is not set
# CFG_HI_TUNER_OUTPUT_PIN9_TSDAT4 is not set
# CFG_HI_TUNER_OUTPUT_PIN9_TSDAT5 is not set
# CFG_HI_TUNER_OUTPUT_PIN9_TSDAT6 is not set
# CFG_HI_TUNER_OUTPUT_PIN9_TSDAT7 is not set
# CFG_HI_TUNER_OUTPUT_PIN9_TSSYNC is not set
CFG_HI_TUNER_OUTPUT_PIN9_TSVLD=y
# CFG_HI_TUNER_OUTPUT_PIN9_TSERR is not set
# CFG_HI_TUNER_OUTPUT_PIN10_TSDAT0 is not set
# CFG_HI_TUNER_OUTPUT_PIN10_TSDAT1 is not set
# CFG_HI_TUNER_OUTPUT_PIN10_TSDAT2 is not set
# CFG_HI_TUNER_OUTPUT_PIN10_TSDAT3 is not set
# CFG_HI_TUNER_OUTPUT_PIN10_TSDAT4 is not set
# CFG_HI_TUNER_OUTPUT_PIN10_TSDAT5 is not set
# CFG_HI_TUNER_OUTPUT_PIN10_TSDAT6 is not set
# CFG_HI_TUNER_OUTPUT_PIN10_TSDAT7 is not set
# CFG_HI_TUNER_OUTPUT_PIN10_TSSYNC is not set
# CFG_HI_TUNER_OUTPUT_PIN10_TSVLD is not set
CFG_HI_TUNER_OUTPUT_PIN10_TSERR=y

#
# Second Tuner Config
#
CFG_HI_TUNER1_SIGNAL_CAB=y
# CFG_HI_TUNER1_SIGNAL_SAT is not set
# CFG_HI_TUNER1_SIGNAL_DVB_T is not set
# CFG_HI_TUNER1_SIGNAL_DVB_T2 is not set
# CFG_HI_TUNER1_SIGNAL_ISDB_T is not set
# CFG_HI_TUNER1_SIGNAL_ATSC_T is not set
# CFG_HI_TUNER1_SIGNAL_DTMB is not set
# CFG_HI_TUNER1_DEV_TYPE_XG_3BL is not set
# CFG_HI_TUNER1_DEV_TYPE_CD1616 is not set
# CFG_HI_TUNER1_DEV_TYPE_ALPS_TDAE is not set
# CFG_HI_TUNER1_DEV_TYPE_TDCC is not set
# CFG_HI_TUNER1_DEV_TYPE_TDA18250 is not set
# CFG_HI_TUNER1_DEV_TYPE_CD1616_DOUBLE is not set
# CFG_HI_TUNER1_DEV_TYPE_MT2081 is not set
# CFG_HI_TUNER1_DEV_TYPE_TMX7070X is not set
# CFG_HI_TUNER1_DEV_TYPE_R820C is not set
# CFG_HI_TUNER1_DEV_TYPE_MXL203 is not set
# CFG_HI_TUNER1_DEV_TYPE_AV2011 is not set
# CFG_HI_TUNER1_DEV_TYPE_AV2018 is not set
# CFG_HI_TUNER1_DEV_TYPE_SHARP7903 is not set
# CFG_HI_TUNER1_DEV_TYPE_MXL101 is not set
# CFG_HI_TUNER1_DEV_TYPE_MXL603 is not set
# CFG_HI_TUNER1_DEV_TYPE_CXD2861 is not set
# CFG_HI_TUNER1_DEV_TYPE_IT9170 is not set
# CFG_HI_TUNER1_DEV_TYPE_TDA6651 is not set
CFG_HI_TUNER1_DEV_TYPE_TDA18250B=y
# CFG_HI_TUNER1_DEV_TYPE_M88TS2022 is not set
# CFG_HI_TUNER1_DEV_TYPE_RDA5815 is not set
# CFG_HI_TUNER1_DEV_TYPE_MXL254 is not set
# CFG_HI_TUNER1_DEV_TYPE_SI2147 is not set
# CFG_HI_TUNER1_DEV_TYPE_RAFAEL836 is not set
# CFG_HI_TUNER1_DEV_TYPE_MXL608 is not set
# CFG_HI_TUNER1_DEV_TYPE_MXL214 is not set
# CFG_HI_TUNER1_DEV_TYPE_TDA18280 is not set
# CFG_HI_TUNER1_DEV_TYPE_TDA182I5A is not set
# CFG_HI_TUNER1_DEV_TYPE_SI2144 is not set
CFG_HI_TUNER1_DEV_ADDR=0xc0
# CFG_HI_DEMOD1_DEV_TYPE_NONE is not set
# CFG_HI_DEMOD1_DEV_TYPE_3130I is not set
CFG_HI_DEMOD1_DEV_TYPE_3130E=y
# CFG_HI_DEMOD1_DEV_TYPE_J83B is not set
# CFG_HI_DEMOD1_DEV_TYPE_AVL6211 is not set
# CFG_HI_DEMOD1_DEV_TYPE_MXL101 is not set
# CFG_HI_DEMOD1_DEV_TYPE_MN88472 is not set
# CFG_HI_DEMOD1_DEV_TYPE_CXD2837 is not set
# CFG_HI_DEMOD1_DEV_TYPE_IT9170 is not set
# CFG_HI_DEMOD1_DEV_TYPE_3136 is not set
# CFG_HI_DEMOD1_DEV_TYPE_3137 is not set
# CFG_HI_DEMOD1_DEV_TYPE_MXL254 is not set
# CFG_HI_DEMOD1_DEV_TYPE_MXL214 is not set
# CFG_HI_DEMOD1_DEV_TYPE_TDA18280 is not set
# CFG_HI_DEMOD1_DEV_TYPE_HIDTV100 is not set
CFG_HI_DEMOD1_DEV_ADDR=0xa0
# CFG_HI_DEMOD1_TS_DEFAULT is not set
# CFG_HI_DEMOD1_TS_PARALLEL_MODE_A is not set
# CFG_HI_DEMOD1_TS_PARALLEL_MODE_B is not set
CFG_HI_DEMOD1_TS_SERIAL=y
# CFG_HI_DEMOD1_TS_SERIAL_50 is not set
# CFG_HI_DEMOD1_TS_SERIAL_2BIT is not set
# CFG_HI_DEMOD1_I2C is not set
CFG_HI_DEMOD1_GPIO=y
CFG_HI_DEMOD1_GPIO_SDA=11
CFG_HI_DEMOD1_GPIO_SCL=12
CFG_HI_DEMOD1_RESET_GPIO=0x7
CFG_HI_DEMUX1_PORT=32

#
# Third Tuner Config
#
CFG_HI_TUNER2_SIGNAL_CAB=y
# CFG_HI_TUNER2_SIGNAL_SAT is not set
# CFG_HI_TUNER2_SIGNAL_DVB_T is not set
# CFG_HI_TUNER2_SIGNAL_DVB_T2 is not set
# CFG_HI_TUNER2_SIGNAL_ISDB_T is not set
# CFG_HI_TUNER2_SIGNAL_ATSC_T is not set
# CFG_HI_TUNER2_SIGNAL_DTMB is not set
# CFG_HI_TUNER2_DEV_TYPE_XG_3BL is not set
# CFG_HI_TUNER2_DEV_TYPE_CD1616 is not set
# CFG_HI_TUNER2_DEV_TYPE_ALPS_TDAE is not set
# CFG_HI_TUNER2_DEV_TYPE_TDCC is not set
CFG_HI_TUNER2_DEV_TYPE_TDA18250=y
# CFG_HI_TUNER2_DEV_TYPE_CD1616_DOUBLE is not set
# CFG_HI_TUNER2_DEV_TYPE_MT2081 is not set
# CFG_HI_TUNER2_DEV_TYPE_TMX7070X is not set
# CFG_HI_TUNER2_DEV_TYPE_R820C is not set
# CFG_HI_TUNER2_DEV_TYPE_MXL203 is not set
# CFG_HI_TUNER2_DEV_TYPE_AV2011 is not set
# CFG_HI_TUNER2_DEV_TYPE_AV2018 is not set
# CFG_HI_TUNER2_DEV_TYPE_SHARP7903 is not set
# CFG_HI_TUNER2_DEV_TYPE_MXL101 is not set
# CFG_HI_TUNER2_DEV_TYPE_MXL603 is not set
# CFG_HI_TUNER2_DEV_TYPE_CXD2861 is not set
# CFG_HI_TUNER2_DEV_TYPE_IT9170 is not set
# CFG_HI_TUNER2_DEV_TYPE_TDA6651 is not set
# CFG_HI_TUNER2_DEV_TYPE_TDA18250B is not set
# CFG_HI_TUNER2_DEV_TYPE_M88TS2022 is not set
# CFG_HI_TUNER2_DEV_TYPE_RDA5815 is not set
# CFG_HI_TUNER2_DEV_TYPE_MXL254 is not set
# CFG_HI_TUNER2_DEV_TYPE_SI2147 is not set
# CFG_HI_TUNER2_DEV_TYPE_RAFAEL836 is not set
# CFG_HI_TUNER2_DEV_TYPE_MXL608 is not set
# CFG_HI_TUNER2_DEV_TYPE_MXL214 is not set
# CFG_HI_TUNER2_DEV_TYPE_TDA18280 is not set
# CFG_HI_TUNER2_DEV_TYPE_TDA182I5A is not set
# CFG_HI_TUNER2_DEV_TYPE_SI2144 is not set
CFG_HI_TUNER2_DEV_ADDR=0xc0
# CFG_HI_DEMOD2_DEV_TYPE_NONE is not set
CFG_HI_DEMOD2_DEV_TYPE_3130I=y
# CFG_HI_DEMOD2_DEV_TYPE_3130E is not set
# CFG_HI_DEMOD2_DEV_TYPE_J83B is not set
# CFG_HI_DEMOD2_DEV_TYPE_AVL6211 is not set
# CFG_HI_DEMOD2_DEV_TYPE_MXL101 is not set
# CFG_HI_DEMOD2_DEV_TYPE_MN88472 is not set
# CFG_HI_DEMOD2_DEV_TYPE_CXD2837 is not set
# CFG_HI_DEMOD2_DEV_TYPE_IT9170 is not set
# CFG_HI_DEMOD2_DEV_TYPE_3136 is not set
# CFG_HI_DEMOD2_DEV_TYPE_3137 is not set
# CFG_HI_DEMOD2_DEV_TYPE_MXL254 is not set
# CFG_HI_DEMOD2_DEV_TYPE_MXL214 is not set
# CFG_HI_DEMOD2_DEV_TYPE_TDA18280 is not set
# CFG_HI_DEMOD2_DEV_TYPE_HIDTV100 is not set
CFG_HI_DEMOD2_DEV_ADDR=0xa0
# CFG_HI_DEMOD2_TS_DEFAULT is not set
CFG_HI_DEMOD2_TS_PARALLEL_MODE_A=y
# CFG_HI_DEMOD2_TS_PARALLEL_MODE_B is not set
# CFG_HI_DEMOD2_TS_SERIAL is not set
# CFG_HI_DEMOD2_TS_SERIAL_50 is not set
# CFG_HI_DEMOD2_TS_SERIAL_2BIT is not set
CFG_HI_DEMOD2_I2C=y
# CFG_HI_DEMOD2_GPIO is not set
CFG_HI_DEMOD2_I2C_CHANNEL=5
CFG_HI_DEMOD2_RESET_GPIO=0x0
CFG_HI_DEMUX2_PORT=0

#
# Fourth Tuner Config
#
CFG_HI_TUNER3_SIGNAL_CAB=y
# CFG_HI_TUNER3_SIGNAL_SAT is not set
# CFG_HI_TUNER3_SIGNAL_DVB_T is not set
# CFG_HI_TUNER3_SIGNAL_DVB_T2 is not set
# CFG_HI_TUNER3_SIGNAL_ISDB_T is not set
# CFG_HI_TUNER3_SIGNAL_ATSC_T is not set
# CFG_HI_TUNER3_SIGNAL_DTMB is not set
# CFG_HI_TUNER3_DEV_TYPE_XG_3BL is not set
# CFG_HI_TUNER3_DEV_TYPE_CD1616 is not set
# CFG_HI_TUNER3_DEV_TYPE_ALPS_TDAE is not set
# CFG_HI_TUNER3_DEV_TYPE_TDCC is not set
CFG_HI_TUNER3_DEV_TYPE_TDA18250=y
# CFG_HI_TUNER3_DEV_TYPE_CD1616_DOUBLE is not set
# CFG_HI_TUNER3_DEV_TYPE_MT2081 is not set
# CFG_HI_TUNER3_DEV_TYPE_TMX7070X is not set
# CFG_HI_TUNER3_DEV_TYPE_R820C is not set
# CFG_HI_TUNER3_DEV_TYPE_MXL203 is not set
# CFG_HI_TUNER3_DEV_TYPE_AV2011 is not set
# CFG_HI_TUNER3_DEV_TYPE_AV2018 is not set
# CFG_HI_TUNER3_DEV_TYPE_SHARP7903 is not set
# CFG_HI_TUNER3_DEV_TYPE_MXL101 is not set
# CFG_HI_TUNER3_DEV_TYPE_MXL603 is not set
# CFG_HI_TUNER3_DEV_TYPE_CXD2861 is not set
# CFG_HI_TUNER3_DEV_TYPE_IT9170 is not set
# CFG_HI_TUNER3_DEV_TYPE_TDA6651 is not set
# CFG_HI_TUNER3_DEV_TYPE_TDA18250B is not set
# CFG_HI_TUNER3_DEV_TYPE_M88TS2022 is not set
# CFG_HI_TUNER3_DEV_TYPE_RDA5815 is not set
# CFG_HI_TUNER3_DEV_TYPE_MXL254 is not set
# CFG_HI_TUNER3_DEV_TYPE_SI2147 is not set
# CFG_HI_TUNER3_DEV_TYPE_RAFAEL836 is not set
# CFG_HI_TUNER3_DEV_TYPE_MXL608 is not set
# CFG_HI_TUNER3_DEV_TYPE_MXL214 is not set
# CFG_HI_TUNER3_DEV_TYPE_TDA18280 is not set
# CFG_HI_TUNER3_DEV_TYPE_TDA182I5A is not set
# CFG_HI_TUNER3_DEV_TYPE_SI2144 is not set
CFG_HI_TUNER3_DEV_ADDR=0xc0
# CFG_HI_DEMOD3_DEV_TYPE_NONE is not set
CFG_HI_DEMOD3_DEV_TYPE_3130I=y
# CFG_HI_DEMOD3_DEV_TYPE_3130E is not set
# CFG_HI_DEMOD3_DEV_TYPE_J83B is not set
# CFG_HI_DEMOD3_DEV_TYPE_AVL6211 is not set
# CFG_HI_DEMOD3_DEV_TYPE_MXL101 is not set
# CFG_HI_DEMOD3_DEV_TYPE_MN88472 is not set
# CFG_HI_DEMOD3_DEV_TYPE_CXD2837 is not set
# CFG_HI_DEMOD3_DEV_TYPE_IT9170 is not set
# CFG_HI_DEMOD3_DEV_TYPE_3136 is not set
# CFG_HI_DEMOD3_DEV_TYPE_3137 is not set
# CFG_HI_DEMOD3_DEV_TYPE_MXL254 is not set
# CFG_HI_DEMOD3_DEV_TYPE_MXL214 is not set
# CFG_HI_DEMOD3_DEV_TYPE_TDA18280 is not set
# CFG_HI_DEMOD3_DEV_TYPE_HIDTV100 is not set
CFG_HI_DEMOD3_DEV_ADDR=0xa0
# CFG_HI_DEMOD3_TS_DEFAULT is not set
CFG_HI_DEMOD3_TS_PARALLEL_MODE_A=y
# CFG_HI_DEMOD3_TS_PARALLEL_MODE_B is not set
# CFG_HI_DEMOD3_TS_SERIAL is not set
# CFG_HI_DEMOD3_TS_SERIAL_50 is not set
# CFG_HI_DEMOD3_TS_SERIAL_2BIT is not set
CFG_HI_DEMOD3_I2C=y
# CFG_HI_DEMOD3_GPIO is not set
CFG_HI_DEMOD3_I2C_CHANNEL=5
CFG_HI_DEMOD3_RESET_GPIO=0x0
CFG_HI_DEMUX3_PORT=0

#
# Demux Config
#

#
# IF Config
#
CFG_HI_IF_TYPE=parallel_nosync_188
CFG_HI_IF_BIT_SELECTOR=0

#
# TSI Config
#
CFG_HI_TSI_NUMBER=4

#
# TSI0 Config
#
CFG_HI_TSI0_TYPE=serial_nosync
CFG_HI_TSI0_CLK_PHASE_REVERSE=0
CFG_HI_TSI0_BIT_SELECTOR=0

#
# TSI1 Config
#
CFG_HI_TSI1_TYPE=serial
CFG_HI_TSI1_CLK_PHASE_REVERSE=0
CFG_HI_TSI1_BIT_SELECTOR=0

#
# TSI2 Config
#
CFG_HI_TSI2_TYPE=parallel_nosync_188
CFG_HI_TSI2_CLK_PHASE_REVERSE=1
CFG_HI_TSI2_BIT_SELECTOR=0

#
# TSI3 Config
#
CFG_HI_TSI3_TYPE=parallel_nosync_188
CFG_HI_TSI3_CLK_PHASE_REVERSE=1
CFG_HI_TSI3_BIT_SELECTOR=0

#
# TSI4 Config
#
CFG_HI_TSI4_TYPE=parallel_nosync_188
CFG_HI_TSI4_CLK_PHASE_REVERSE=1
CFG_HI_TSI4_BIT_SELECTOR=0

#
# TSI5 Config
#
CFG_HI_TSI5_TYPE=parallel_nosync_188
CFG_HI_TSI5_CLK_PHASE_REVERSE=1
CFG_HI_TSI5_BIT_SELECTOR=0

#
# TSO Config
#
CFG_HI_TSO_NUMBER=2

#
# TSO0 Config
#
CFG_HI_TSO0_CLK_100M=y
# CFG_HI_TSO0_CLK_150M is not set
# CFG_HI_TSO0_CLK_1200M is not set
# CFG_HI_TSO0_CLK_1500M is not set
CFG_HI_TSO0_CLK_MODE_NORMAL=y
# CFG_HI_TSO0_CLK_MODE_JITTER is not set
CFG_HI_TSO0_VALID_ACTIVE_OUTPUT=y
# CFG_HI_TSO0_VALID_ACTIVE_HIGH is not set
CFG_HI_TSO0_SERIAL=y
# CFG_HI_TSO0_PARALLEL is not set
CFG_HI_TSO0_SERIAL_BIT_0=y
# CFG_HI_TSO0_SERIAL_BIT_7 is not set

#
# TSO1 Config
#
CFG_HI_TSO1_CLK_100M=y
# CFG_HI_TSO1_CLK_150M is not set
# CFG_HI_TSO1_CLK_1200M is not set
# CFG_HI_TSO1_CLK_1500M is not set
CFG_HI_TSO1_CLK_MODE_NORMAL=y
# CFG_HI_TSO1_CLK_MODE_JITTER is not set
CFG_HI_TSO1_VALID_ACTIVE_OUTPUT=y
# CFG_HI_TSO1_VALID_ACTIVE_HIGH is not set
CFG_HI_TSO1_SERIAL=y
# CFG_HI_TSO1_PARALLEL is not set
CFG_HI_TSO1_SERIAL_BIT_0=y
# CFG_HI_TSO1_SERIAL_BIT_7 is not set

#
# Keyled Config
#
# CFG_HI_KEYLED_74HC164_SELECT is not set
CFG_HI_KEYLED_CT1642_SELECT=y
# CFG_HI_KEYLED_PT6961_SELECT is not set
# CFG_HI_KEYLED_PT6964_SELECT is not set
# CFG_HI_KEYLED_FD650_SELECT is not set
CFG_HI_GPIO_LIGHT_SUPPORT=y
CFG_HI_POSITIVE_GPIO_LIGHT_NUMBER=0x2e
CFG_HI_NEGATIVE_GPIO_LIGHT_NUMBER=0x2d

#
# PowerManagement Config
#
# CFG_HI_PMU_DEVICE_SELECT is not set

#
# SCI Config
#
CFG_HI_SCI_CLK_MODE_CMOS=y
# CFG_HI_SCI_CLK_MODE_OD is not set
# CFG_HI_SCI_VCCEN_MODE_CMOS is not set
CFG_HI_SCI_VCCEN_MODE_OD=y
CFG_HI_SCI_RESET_MODE_CMOS=y
# CFG_HI_SCI_RESET_MODE_OD is not set
CFG_HI_SCI_VCCEN_LOW=y
# CFG_HI_SCI_VCCEN_HIGH is not set
# CFG_HI_SCI_DETECT_LOW is not set
CFG_HI_SCI_DETECT_HIGH=y
CFG_HI_SND_MUTECTL_SUPPORT=y
CFG_HI_SND_MUTECTL_GPIO=0x23
CFG_HI_SND_MUTECTL_LEVEL=0
# CFG_HI_SND_AMP_SUPPORT is not set

#
# Video DAC Config
#
CFG_HI_DAC_CVBS=0
CFG_HI_DAC_YPBPR_Y=1
CFG_HI_DAC_YPBPR_PB=2
CFG_HI_DAC_YPBPR_PR=3

#
# Boot Regfile Config
#
CFG_HI_BOOT_REG_NAME=hi3796mdmo1a_hi3796mv100_ddr3_1gbyte_16bitx2_4layers_emmc.reg

#
# Boot
#
CFG_HI_UBOOT_SUPPORT=y
# CFG_HI_MINIBOOT_SUPPORT is not set
# CFG_HI_FORCE_ENV_TO_MEDIA is not set
CFG_HI_BOOT_ENV_STARTADDR=0x80000
CFG_HI_BOOT_ENV_SIZE=0x10000
CFG_HI_BOOT_ENV_RANGE=0x10000
# CFG_HI_BOOT_ENV_BAK_SUPPORT is not set
# CFG_HI_BOOT_COMPRESSED is not set
# CFG_HI_BENCH_SUPPORT is not set
CFG_HI_BOOT_USB_SUPPORT=y

#
# Build Product Code in Boot
#
CFG_HI_BUILD_WITH_PRODUCT=y
# CFG_HI_BUILD_WITH_ANDROID is not set
CFG_HI_BUILD_WITH_KEYLED=y
# CFG_HI_BUILD_WITH_IR is not set
# CFG_HI_BUILD_WITH_HDMI_EDID is not set

#
# Kernel
#
CFG_LINUX-3.10.y=y
CFG_HI_KERNEL_VERSION=linux-3.10.y
CFG_HI_KERNEL_CFG=hi3796mv100_defconfig
# CFG_HI_FS_BUILDIN is not set
# CFG_HI_MSP_BUILDIN is not set

#
# Rootfs
#

#
# Board Tools Config
#
CFG_HI_TOOL_UDEV_SUPPORT=y
CFG_HI_TOOL_DOSFS_SUPPORT=y
CFG_HI_TOOL_E2FSPROGS_SUPPORT=y
CFG_HI_TOOL_FILECAP_SUPPORT=y
CFG_HI_TOOL_GDB_SUPPORT=y
CFG_HI_TOOL_IPTABLES_SUPPORT=y
CFG_HI_TOOL_MTDUTILS_SUPPORT=y
CFG_HI_TOOL_REG_SUPPORT=y
# CFG_HI_TOOL_REG_UART_SUPPORT is not set
CFG_HI_TOOL_TOP_SUPPORT=y
# CFG_HI_TOOL_PPPD_SUPPORT is not set
# CFG_HI_TOOL_MIITOOLS_SUPPORT is not set
# CFG_HI_TOOL_IPERF_SUPPORT is not set
CFG_HI_TOOL_MSP_DEBUG_SUPPORT=y
CFG_HI_TOOL_PQ_DEBUG_SUPPORT=y
# CFG_HI_TOOL_SOC_SERVER is not set
# CFG_HI_LXC_CONTAINER_SUPPORT is not set
# CFG_HI_TOOL_SYSSTAT_SUPPORT is not set
# CFG_HI_TOOL_MEMTESTER_SUPPORT is not set

#
# Busybox Config
#
CFG_BUSYBOX_1.16.1=y
# CFG_BUSYBOX_1.22.1 is not set
CFG_HI_BUSYBOX_CFG_NAME=glibc.config
CFG_HI_LIBCPP_SUPPORT=y

#
# File System Config
#
CFG_HI_ROOTFS_STRIP=y
CFG_HI_ROOTFS_INSTALL_SHARED_LIBS=y
CFG_HI_ROOTFS_CRAMFS=y
CFG_HI_ROOTFS_SQUASHFS=y
CFG_HI_ROOTFS_EXT4=y
CFG_HI_EMMC_ROOTFS_SIZE=96

#
# Common
#
CFG_HI_LOG_SUPPORT=y
CFG_HI_LOG_LEVEL=4
CFG_HI_LOG_NETWORK_SUPPORT=y
CFG_HI_LOG_UDISK_SUPPORT=y
# CFG_HI_MMZ_V2_SUPPORT is not set
# CFG_HI_MEMMGR_SUPPORT is not set
CFG_HI_PROC_SUPPORT=y

#
# Component
#
# CFG_HI_ADVCA_SUPPORT is not set
CFG_HI_ZLIB_SUPPORT=y
# CFG_HI_WIFI_SUPPORT is not set
CFG_HI_FAT_SUPPORT=y
CFG_HI_NTFS_SUPPORT=y
CFG_HI_NTFS_MODULE_SUPPORT=y
CFG_HI_NTFS_TOOLS_SUPPORT=y
CFG_HI_EXFAT_SUPPORT=y
# CFG_HI_3G_SUPPORT is not set
CFG_HI_ALSA_SUPPORT=y
# CFG_HI_BLUETOOTH_SUPPORT is not set

#
# HACODEC Config
#
CFG_HI_HACODEC_MP3DECODE_SUPPORT=y
CFG_HI_HACODEC_AACDECODE_SUPPORT=y
CFG_HI_HACODEC_AACENCODE_SUPPORT=y
CFG_HI_HACODEC_AC3PASSTHROUGH_SUPPORT=y
CFG_HI_HACODEC_AMRNBCODEC_SUPPORT=y
CFG_HI_HACODEC_AMRWBCODEC_SUPPORT=y
CFG_HI_HACODEC_BLURAYLPCMDECODE_SUPPORT=y
CFG_HI_HACODEC_COOKDECODE_SUPPORT=y
CFG_HI_HACODEC_DRADECODE_SUPPORT=y
CFG_HI_HACODEC_DTSPASSTHROUGH_SUPPORT=y
CFG_HI_HACODEC_G711CODEC_SUPPORT=y
CFG_HI_HACODEC_G722CODEC_SUPPORT=y
CFG_HI_HACODEC_MP2DECODE_SUPPORT=y
CFG_HI_HACODEC_PCMDECODE_SUPPORT=y
CFG_HI_HACODEC_TRUEHDPASSTHROUGH_SUPPORT=y
CFG_HI_HACODEC_WMADECODE_SUPPORT=y
CFG_HI_HACODEC_PCMDECODE_HW_SUPPORT=y
CFG_HI_HACODEC_MP3DECODE_HW_SUPPORT=y

#
# HAEFFECT Config
#
# CFG_HI_HAEFFECT_BASE_SUPPORT is not set
CFG_HI_VP_SUPPORT=y
CFG_HI_PES_SUPPORT=y

#
# Caption Config
#
CFG_HI_CAPTION_SUBT_SUPPORT=y
CFG_HI_CAPTION_TTX_SUPPORT=y
CFG_HI_CAPTION_SO_SUPPORT=y
CFG_HI_CAPTION_CC_SUPPORT=y
CFG_HI_PLAYER_SUPPORT=y
CFG_HI_PLAYER_FULL_SUPPORT=y
# CFG_HI_PLAYER_HBBTV_SUPPORT is not set
# CFG_HI_CURL_SUPPORT is not set
# CFG_HI_DLNA_SUPPORT is not set
# CFG_HI_TRANSCODER_SUPPORT is not set
# CFG_HI_PLAYREADY_SUPPORT is not set

#
# Msp
#
CFG_HI_FRONTEND_SUPPORT=y
CFG_HI_DVBC_SUPPORT=y

#
# DVB-C Demod Config
#
CFG_HI_DEMOD_TYPE_HI3130=y
CFG_HI_DEMOD_TYPE_J83B=y
# CFG_HI_DEMOD_TYPE_MXL254 is not set
# CFG_HI_DEMOD_TYPE_MXL214 is not set
# CFG_HI_DEMOD_TYPE_TDA18280 is not set

#
# DVB-C Tuner Config
#
CFG_HI_TUNER_TYPE_TDA18250=y
CFG_HI_TUNER_TYPE_TDA18250B=y
# CFG_HI_TUNER_TYPE_MXL254 is not set
# CFG_HI_TUNER_TYPE_MXL214 is not set
# CFG_HI_TUNER_TYPE_TDA18280 is not set
# CFG_HI_TUNER_TYPE_MXL203 is not set
CFG_HI_TUNER_TYPE_MXL603=y
# CFG_HI_TUNER_TYPE_ALPS_TDAE is not set
# CFG_HI_TUNER_TYPE_TDCC is not set
# CFG_HI_TUNER_TYPE_MT2081 is not set
# CFG_HI_TUNER_TYPE_TMX7070X is not set
# CFG_HI_TUNER_TYPE_R820C is not set
# CFG_HI_TUNER_TYPE_TDA6651 is not set
# CFG_HI_TUNER_TYPE_XG_3BL is not set
# CFG_HI_TUNER_TYPE_CD1616 is not set
# CFG_HI_TUNER_TYPE_CD1616_LF_GIH_4 is not set
CFG_HI_TUNER_TYPE_si2147=y
CFG_HI_TUNER_TYPE_MXL608=y
CFG_HI_DVBS_SUPPORT=y

#
# DVB-S/S2 Demod Config
#
CFG_HI_DEMOD_TYPE_AVL6211=y
CFG_HI_DEMOD_TYPE_HI3136=y

#
# DVB-S/S2 Tuner Config
#
CFG_HI_TUNER_TYPE_AV2011=y
CFG_HI_TUNER_TYPE_AV2018=y
CFG_HI_TUNER_TYPE_SHARP7903=y
CFG_HI_TUNER_TYPE_RDA5815=y
CFG_HI_TUNER_TYPE_M88TS2022=y
CFG_HI_DISEQC_SUPPORT=y

#
# LNB Chip Config
#
CFG_HI_LNB_CTRL_ISL9492=y
CFG_HI_LNB_CTRL_MPS8125=y
CFG_HI_DVBT_SUPPORT=y

#
# DVB-T/T2 Demod Config
#
CFG_HI_DEMOD_TYPE_HI3137=y
CFG_HI_DEMOD_TYPE_CXD2837=y
CFG_HI_DEMOD_TYPE_MXL101=y
CFG_HI_DEMOD_TYPE_MN88472=y
CFG_HI_DEMOD_TYPE_IT9170=y

#
# DVB-T/T2 Tuner Config
#
CFG_HI_TUNER_TYPE_CXD2861=y
CFG_HI_TUNER_TYPE_RAFAEL836=y
CFG_HI_TUNER_TYPE_SI2147=y
CFG_HI_TUNER_TYPE_TDA182I5A=y
# CFG_HI_TUNER_TYPE_SI2144 is not set

#
# DEMUX Config
#
CFG_HI_DEMUX_POOLBUF_SIZE=0x200000

#
# Audio Config
#
# CFG_HI_SND_ALSA_AO_SUPPORT is not set
CFG_HI_AI_SUPPORT=y
# CFG_HI_SND_ALSA_AI_SUPPORT is not set
CFG_HI_ADEC_MAX_INSTANCE=8
CFG_HI_ADEC_AUDSPECTRUM_SUPPORT=y
# CFG_HI_SND_SMARTVOLUME_SUPPORT is not set
# CFG_HI_SND_VIRTUALCHN_SUPPORT is not set
# CFG_HI_RESAMPLER_QUALITY_LINEAR is not set
CFG_HI_AENC_SUPPORT=y
# CFG_HI_SND_SIF_SUPPORT is not set
# CFG_HI_ADAC_SUPPORT is not set
# CFG_HI_ALSA_TVL320_KERNEL_SUPPORT is not set

#
# Video Decoder Config
#

#
# Video Memory Config In 512M DDR
#
# CFG_HI_VIDEO_PRE_CAP_1080P_IN_512 is not set
CFG_HI_VIDEO_PRE_CAP_MVC_IN_512=y
# CFG_HI_VIDEO_PRE_CAP_2160P_IN_512 is not set
# CFG_HI_VIDEO_PRE_CAP_4K_IN_512 is not set
CFG_HI_VIDEO_MAX_REF_FRAME_NUM_IN_512=7
CFG_HI_VIDEO_MAX_DISP_FRAME_NUM_IN_512=2
CFG_HI_VIDEO_SCD_BUF_SIZE_IN_512=10
CFG_HI_VIDEO_MAX_VDH_BUF_IN_512=110

#
# Video Memory Config In 1024M DDR
#
# CFG_HI_VIDEO_PRE_CAP_1080P_IN_1024 is not set
# CFG_HI_VIDEO_PRE_CAP_MVC_IN_1024 is not set
# CFG_HI_VIDEO_PRE_CAP_2160P_IN_1024 is not set
CFG_HI_VIDEO_PRE_CAP_4K_IN_1024=y
CFG_HI_VIDEO_MAX_REF_FRAME_NUM_IN_1024=5
CFG_HI_VIDEO_MAX_DISP_FRAME_NUM_IN_1024=4
CFG_HI_VIDEO_SCD_BUF_SIZE_IN_1024=20
CFG_HI_VIDEO_MAX_VDH_BUF_IN_1024=180

#
# Video Memory Config In 2048M DDR
#
# CFG_HI_VIDEO_PRE_CAP_1080P_IN_2048 is not set
# CFG_HI_VIDEO_PRE_CAP_MVC_IN_2048 is not set
# CFG_HI_VIDEO_PRE_CAP_2160P_IN_2048 is not set
CFG_HI_VIDEO_PRE_CAP_4K_IN_2048=y
CFG_HI_VIDEO_MAX_REF_FRAME_NUM_IN_2048=6
CFG_HI_VIDEO_MAX_DISP_FRAME_NUM_IN_2048=6
CFG_HI_VIDEO_SCD_BUF_SIZE_IN_2048=30
CFG_HI_VIDEO_MAX_VDH_BUF_IN_2048=250
CFG_HI_VDEC_DEINTERLACE_SUPPORT=y
CFG_HI_VDEC_SVDEC_SUPPORT=y
CFG_HI_VDEC_REG_CODEC_SUPPORT=y
CFG_HI_VDEC_MJPEG_SUPPORT=y
CFG_HI_VDEC_USERDATA_CC_SUPPORT=y
CFG_HI_VDEC_USERDATA_CC_BUFSIZE=0xC000
CFG_HI_VDEC_DFS_SUPPORT=y

#
# VO Config
#
CFG_HI_VIDEO_BUFF_DEMO=y
# CFG_HI_VIDEO_BUFF_TYPE0 is not set
# CFG_HI_DISP_USE_QPLL_SOLELY is not set
CFG_HI_DISP_TTX_INBUFFERSIZE=0x4000
CFG_HI_DISP_CC_INBUFFERSIZE=0x4000
CFG_HI_PQ_V3_0=y
# CFG_HI_DISP_VIRT_OFFSET_EFFECT_WHEN_FULLSCREEN is not set

#
# VPSS Config
#
CFG_HI_VPSS_MAX_BUFFER_NUMB=6

#
# HDMI Config
#
CFG_HI_HDMI_SUPPORT_1_4=y
CFG_HI_HDMI_SUPPORT_HDCP=y
CFG_HI_HDMI_SUPPORT_CEC=y
# CFG_HI_HDMI_SUPPORT_DEBUG is not set
CFG_HI_HDMI_DEBUG_MEM_SIZE=0x80000

#
# Graphic Config
#
CFG_LIB_JPEG_VERSION_6B=y
# CFG_LIB_JPEG_VERSION_9A is not set
CFG_HI_LIB_JPEG_VERSION=libjpeg-6b
CFG_LIB_PNG_VERSION_1.4.0=y
# CFG_LIB_PNG_VERSION_1.6.16 is not set
CFG_HI_LIB_PNG_VERSION=libpng-1.4.0
CFG_HIFB_STEREO3D_SUPPORT=y
# CFG_HIFB_COMPRESSION_SUPPORT is not set
# CFG_HIFB_SCROLLTEXT_SUPPORT is not set
# CFG_HIFB_CURSOR_SUPPORT is not set
CFG_HI_PNG_DECODER_SUPPORT=y
CFG_HI_FREETYPE_FONT_SUPPORT=y
CFG_HI_TDE_CSCTMPBUFFER_SIZE=0x0
CFG_HI_JPEG6B_STREAMBUFFER_SIZE=0x100000
CFG_HI_HD0_FB_VRAM_SIZE=7200
CFG_HI_HD1_FB_VRAM_SIZE=0
CFG_HI_HD2_FB_VRAM_SIZE=0
CFG_HI_SD0_FB_VRAM_SIZE=0

#
# GPU Config
#
CFG_HI_GPU=y
CFG_HI_GPU_MALI450_SUPPORT=y
# CFG_HI_GPU_DEBUG is not set
CFG_HI_GPU_PROFILING=y
# CFG_HI_GPU_INTERNAL_PROFILING is not set
CFG_HI_GPU_MAX_SHARE_MEM_SIZE=0x10000000
# CFG_EGL_HIGO is not set
CFG_EGL_FB=y
# CFG_EGL_DFB is not set
CFG_HI_EGL_TYPE=fb

#
# IR Config
#
CFG_HI_IR_TYPE_S2=y
# CFG_HI_IR_TYPE_STD is not set
# CFG_HI_IR_TYPE_LIRC is not set
CFG_HI_IR_NEC_SUPPORT=y
CFG_HI_IR_RC6_SUPPORT=y
CFG_HI_IR_RC5_SUPPORT=y
CFG_HI_IR_SONY_SUPPORT=y
CFG_HI_IR_TC9012_SUPPORT=y
# CFG_HI_IR_CREDIT_SUPPORT is not set

#
# Keyled Config
#
CFG_HI_KEYLED_SUPPORT=y
CFG_HI_KEYLED_74HC164_SUPPORT=y
CFG_HI_KEYLED_CT1642_SUPPORT=y
# CFG_HI_KEYLED_CT1642_GPIO_MODE is not set
CFG_HI_KEYLED_PT6961_SUPPORT=y
CFG_HI_KEYLED_PT6961_CLOCK_GPIO=0x2a
CFG_HI_KEYLED_PT6961_STB_GPIO=0x2b
CFG_HI_KEYLED_PT6961_DIN_GPIO=0x2c
CFG_HI_KEYLED_PT6961_DOUT_GPIO=0x2d
CFG_HI_KEYLED_PT6964_SUPPORT=y
CFG_HI_KEYLED_PT6964_CLOCK_GPIO=0x2a
CFG_HI_KEYLED_PT6964_STB_GPIO=0x2b
CFG_HI_KEYLED_PT6964_DINOUT_GPIO=0x2c
CFG_HI_KEYLED_FD650_SUPPORT=y
CFG_HI_KEYLED_FD650_CLOCK_GPIO=0x2b
CFG_HI_KEYLED_FD650_DINOUT_GPIO=0x2d

#
# PowerManagement Config
#
CFG_HI_DVFS_CPU_SUPPORT=y
CFG_HI_DVFS_CORE_SUPPORT=y
CFG_HI_DVFS_GPU_SUPPORT=y
CFG_HI_AVS_SUPPORT=y
# CFG_HI_DONGLE_CONFIG is not set
# CFG_HI_PM_POWERUP_MODE1_SUPPORT is not set
CFG_HI_TEMP_CTRL_CONFIG=y
CFG_HI_TEMP_CTRL_DOWN_THRESHOLD=0xd5
CFG_HI_TEMP_CTRL_UP_THRESHOLD=0xc8
CFG_HI_TEMP_CTRL_REBOOT_THRESHOLD=0xea

#
# SCI Config
#
CFG_HI_SCI_SUPPORT=y
CFG_HI_GPIOI2C_SUPPORT=y
CFG_HI_VI_SUPPORT=y
# CFG_HI_VI_BT656_HIGH8 is not set
CFG_HI_VENC_SUPPORT=y

#
# Pvr Config
#
CFG_HI_PVR_SUPPORT=y
# CFG_HI_PVR_L2_CACHE_SUPPORT is not set
# CFG_HI_SPI_BUS_SUPPORT is not set

#
# CI/CI+ Config
#
# CFG_HI_CIPLUS_SUPPORT is not set
