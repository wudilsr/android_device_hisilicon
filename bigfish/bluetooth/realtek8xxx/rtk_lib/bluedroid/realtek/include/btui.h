#ifndef RTK_PATCH_H
#define RTK_PATCH_H

#include "bt_target.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RTK_BT_DEBUG


enum{
    HCI_I2SPCM_ROLE_SLAVE=0,
    HCI_I2SPCM_ROLE_MASTER
};
enum{
    HCI_I2SPCM_SAMPLE_8K = 8000,
    HCI_I2SPCM_SAMPLE_16K = 16000
};
enum{
    HCI_I2SPCM_CLOCK_128K = 0,
    HCI_I2SPCM_CLOCK_256K,
    HCI_I2SPCM_CLOCK_512K,
    HCI_I2SPCM_CLOCK_1M,
    HCI_I2SPCM_CLOCK_2M,
    HCI_I2SPCM_CLOCK_4M
};
#define HCI_BRCM_I2SPCM_IS_DEFAULT_ROLE (HCI_I2SPCM_ROLE_SLAVE)     //0:salve 1:master
#define HCI_BRCM_I2SPCM_SAMPLE_DEFAULT (HCI_I2SPCM_SAMPLE_8K)       //sample rate
#define HCI_BRCM_I2SPCM_CLOCK_DEFAULT (HCI_I2SPCM_CLOCK_256K)   //I2S clock
#define HCI_BRCM_SCO_ROUTE_PCM (0)
#define HCI_BRCM_SCO_ROUTE_HCI (1)

typedef void (tBTUI_SCO_CODEC_CB)(UINT16 event, UINT16 sco_handle);
typedef struct {
    tBTUI_SCO_CODEC_CB * p_cback;
    UINT16 cb_event;
    UINT8 pool_id;
    UINT8 pkt_size;
}tBTUI_SCO_CODEC_CFG;
#define BTUI_DM_SCO_4_HS_APP_ID (3)
struct btui_cfg_st{
    BOOLEAN hs_sco_over_hci;
    BOOLEAN ag_sco_over_hci;
    BOOLEAN sco_use_mic;
};
struct btui_cb_st{
    BOOLEAN sco_hci;
};

extern struct btui_cfg_st btui_cfg;
extern struct btui_cb_st btui_cb;

BT_API extern void btui_sco_init(void);
BT_API extern BOOLEAN btui_sco_codec_init(UINT32 rx_bw, UINT32 tx_bw);
BT_API extern BOOLEAN btui_sco_codec_open(tBTUI_SCO_CODEC_CFG * cfg);
BT_API extern BOOLEAN btui_sco_codec_start(UINT16 handle);
BT_API extern BOOLEAN btui_sco_codec_close();
BT_API extern BOOLEAN btui_sco_codec_inqdata(BT_HDR  *p_buf);
BT_API extern BOOLEAN btui_sco_codec_readbuf(BT_HDR  **pp_buf);


#ifdef __cplusplus
}
#endif


#endif
