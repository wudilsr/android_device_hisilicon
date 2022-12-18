#include "tee_internal_api.h"
//#define TA_DEBUG
#include "tee_log.h"

#define rpmb_driver_print uart_printf_func
#define rpmb_driver_error ta_error
#define rpmb_driver_debug ta_debug

/*get rpmb info from bl31 forever, never from kernel*/
//#define RPMB_GET_INFO_FROM_ATF_FOREVER_DEBUG

struct rpmb_atf_info {
    uint8_t stuff[0x200];
    uint32_t ret;
    uint32_t start_blk;
    uint32_t total_blk;
    uint32_t data_len;
    uint32_t data_addr;
};

static TEE_Result tee_rpmb_get_info_from_atf(struct rpmb_atf_info *rai)
{
    uint32_t phy_addr;

    /* switch virtual addr to phy addr */
    phy_addr = rai;
    rpmb_driver_print("phy_addr=0x%x\n", phy_addr);
    rpmb_driver_print("before trap into BL31, ret=0x%x,"
        " arg1=0x%x, arg2=0x%x, arg3=0x%x, arg4=0x%x\n",
        rai->ret,
        rai->start_blk, rai->total_blk,
        rai->data_len, rai->data_addr);
    rpmb_driver_print("phy_addr=0x%x\n", phy_addr);
    rpmb_driver_print("before trap into BL31, ret=0x%x,"
        " arg1=0x%x, arg2=0x%x, arg3=0x%x, arg4=0x%x\n",
        rai->ret,
        rai->start_blk, rai->total_blk,
        rai->data_len, rai->data_addr);
    /*flush data in dcache to ram*/
    //__SRE_DCacheFlush(embed_buffer_addr, embed_buffer_len, 1);
    //__SRE_DCacheFlush(rai, sizeof(struct rpmb_atf_info), 1);

    //__v7_dma_flush_range(rai->data_addr, rai->data_addr+rai->data_len);
    //__v7_dma_flush_range(rai, rai+sizeof(struct rpmb_atf_info));

    /*smc switch to bl31*/
    __rpmb_smc_switch(phy_addr);

    /*invalidate dcache and read data from ram*/
    //__SRE_DCacheInv(rai, sizeof(struct rpmb_atf_info), 1);
    //__SRE_DCacheInvAll();

    //__v7_dma_inv_range(rai, rai+sizeof(struct rpmb_atf_info));
    //asm("dsb");
    //__v7_dma_inv_range(rai->data_addr, rai->data_addr+rai->data_len);
    //asm("dsb");

    rpmb_driver_print("after back from BL31, ret=0x%x,"
        " arg1=0x%x, arg2=0x%x, arg3=0x%x, arg4=0x%x\n",
        rai->ret,
        rai->start_blk, rai->total_blk,
        rai->data_len, rai->data_addr);
    rpmb_driver_print("after back from BL31, buffer=%s, len=%d\n",
        (uint8_t*)rai->data_addr, rai->data_len);

    /*check result from ATF*/
    if (rai->ret == 0) {
        rpmb_driver_debug("get info from ATF success\n");
        return TEE_SUCCESS;
    } else {
        rpmb_driver_error("get info from ATF failed, ret=0x%x\n", rai->ret);
        return TEE_ERROR_GENERIC;
    }
}

typedef enum{
    RPMB_KEY_UNKOWN = 0,
    RPMB_MANAGE_KEY,
    RPMB_DERIVE_KEY,
    RPMB_ACCESS_KEY,
} rpmb_key_type;

TEE_Result tee_rpmb_get_partition_info(uint32_t *start_blk, uint32_t *total_blk)
{
    struct rpmb_atf_info rai;
    TEE_Result ret;
    uint8_t *data = NULL;
    uint32_t datalen = 0x100;

#ifdef TEE_GET_RPMB_PARTITION_FROM_ATF
#ifndef RPMB_GET_INFO_FROM_ATF_FOREVER_DEBUG
    uint32_t stat;
    stat = __rpmb_partition_info_read(start_blk, total_blk);
    if (stat == 0)
        return TEE_SUCCESS;
#endif

    data = TEE_Malloc(datalen, 0);
    if (data == NULL)
        return TEE_ERROR_OUT_OF_MEMORY;

    rai.data_len = datalen;
    rai.data_addr = data;
    rai.ret = TEE_ERROR_GENERIC;
    ret = tee_rpmb_get_info_from_atf(&rai);
    if (ret == TEE_SUCCESS) {
        *start_blk = rai.start_blk;
        *total_blk = rai.total_blk;
        datalen = rai.data_len;
#ifndef RPMB_GET_INFO_FROM_ATF_FOREVER_DEBUG
        __rpmb_partition_info_write(*start_blk, *total_blk);
        __rpmb_rootkey_info_write(data, datalen);
#endif
    } else {
        *start_blk = 0;
        *total_blk = 0;
    }
#else
    ret =  TEE_ERROR_SERVICE_NOT_EXIST;
#endif

out:
    if (data)
        TEE_Free(data);
    return ret;
}

TEE_Result tee_rpmb_get_rootkey_data(uint8_t *data, uint32_t *size)
{
    struct rpmb_atf_info rai;
    TEE_Result ret;
    uint32_t start_blk, total_blk;

#ifdef TEE_GET_RPMB_PARTITION_FROM_ATF
#ifndef RPMB_GET_INFO_FROM_ATF_FOREVER_DEBUG
    uint32_t stat;
    stat = __rpmb_rootkey_info_read(data, size);
    if (stat == 0)
        return TEE_SUCCESS;
#endif

    rai.ret = TEE_ERROR_GENERIC;
    rai.data_len = *size;
    rai.data_addr = data;
    ret = tee_rpmb_get_info_from_atf(&rai);
    if (ret == TEE_SUCCESS) {
        *size = rai.data_len;
        start_blk = rai.start_blk;
        total_blk = rai.total_blk;
#ifndef RPMB_GET_INFO_FROM_ATF_FOREVER_DEBUG
        __rpmb_rootkey_info_write(data, *size);
        __rpmb_partition_info_write(start_blk, total_blk);
#endif
    }
#else
    ret = TEE_ERROR_SERVICE_NOT_EXIST;
#endif

    return ret;
}
void tee_rpmb_get_key_type(uint32_t *key_type)
{
    if (key_type != NULL) {
#if defined(WITH_CHIP_HI3650)
        *key_type = RPMB_DERIVE_KEY;
#elif defined(WITH_CHIP_HI6250)
        *key_type = RPMB_ACCESS_KEY;
#elif defined(WITH_CHIP_HI3635)
        *key_type = RPMB_MANAGE_KEY;
#elif defined(WITH_DPT_PLATFORM) || defined(WITH_STB_PLATFORM)
        *key_type = RPMB_MANAGE_KEY;
#else
        *key_type = RPMB_KEY_UNKOWN;
#endif
    }
}

typedef enum {
    RPMB_FS_META_UNKOWN = 0,
    RPMB_FS_META,
    RPMB_FS_META_EX,
} rpmb_fs_meta_type;

void tee_rpmb_get_meta_type(uint32_t *meta_type)
{
    if (meta_type != NULL) {
#if defined(WITH_KIRIN_PLATFORM)
#if defined(WITH_CHIP_HI3650)
        *meta_type = RPMB_FS_META;
#elif defined(WITH_CHIP_HI6250)
        *meta_type = RPMB_FS_META;
#elif defined(WITH_CHIP_HI3660)
        *meta_type = RPMB_FS_META_EX;
#else
        *meta_type = RPMB_FS_META_UNKOWN;
#endif
#else
#if defined(WITH_DPT_PLATFORM) || defined(WITH_STB_PLATFORM)
        *meta_type = RPMB_FS_META_EX;
#else
        *meta_type = RPMB_FS_META_UNKOWN;
#endif
#endif
    }
}
