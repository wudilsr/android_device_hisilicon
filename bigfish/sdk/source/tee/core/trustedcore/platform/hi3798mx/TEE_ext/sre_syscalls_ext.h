#include "sre_typedef.h"
#include "tee_internal_api.h"
#ifdef WITH_HISI_SEC_HDMI
#include "tee_drv_hdmi.h"
#endif
#ifdef WITH_HISI_SEC_MMZ
#include "mmz_struct.h"
#endif
#ifdef WITH_HISI_PVR
/*
TODU: ��tee_pvr.h��api/include�Ƶ�api/pvr�ᵼ��SMMU TA����ʧ��,
��ʱ���θ�ͷ�ļ�����. ͬʱ��HI_U32����TEE_PVR_TYPE_E����������
*/
//#include "tee_drv_pvr.h" 
#endif

extern int __bsp_efuse_read(unsigned int* buf, const unsigned int group, const unsigned int size);
extern int __bsp_efuse_write(unsigned int* buf, const unsigned int group, const unsigned int size);
extern int __bsp_sec_call(unsigned int func_cmd, unsigned int arg);

extern int __hisi_tui_get_tpdata(void *finger_data_buf);
extern void __set_notify_addr(char *addr, int mode);
extern void __send_simu_tp(void *tp_t);

extern int __tee_hal_get_dieid(unsigned int * pBuffer, unsigned int u32Length);
unsigned int __scard_connect(int reader_id, void *p_atr, unsigned int *atr_len);
unsigned int __scard_disconnect(int reader_id);
unsigned int __scard_transmit(int reader_id, unsigned char *p_cmd , unsigned int cmd_len,
        unsigned char *p_rsp , unsigned int *rsp_len);
extern int __driver_dep_test();
extern int __driver_p61_factory_test(void);
/*VFMW begin*/
#ifdef WITH_HISI_VFMW
extern int __VDEC_Suspend(void);
extern int __VDEC_Init(unsigned int pCallback);
extern int __VDEC_Resume(void);
extern int __VFMW_CTRL_thread_sec(void);
extern int __VDEC_Control(unsigned int ChanID, unsigned int eCmdID, unsigned int pArgs);
extern int __VDEC_InitWithOperation(unsigned int pArgs);
extern int __VDEC_MMZCA2TA(unsigned int pArgs);
extern int __VCTRL_WriteProc(unsigned int option, unsigned int value);
extern int __VCTRL_ReadProc(unsigned int page, unsigned int pagelen);
extern int __VCTRL_SetDbgOption(unsigned int opt, unsigned int p_ags);
extern int __VCTRL_GetChanImage(unsigned int ChanID, unsigned int p_image);
extern int __VCTRL_ReleaseChanImage(unsigned int ChanID, unsigned int p_image);
extern int __VDEC_Exit(void);
#endif

/*VFMW end*/

/* display */
extern int __hisi_fb_cfg_sec(int value);
extern int __hisi_fb_alpha_set(int value);
extern int __hisi_pan_display_sec(void *rect);
extern int __hisi_wait_vactive_flag(void);
extern int __hisi_wait_release_flag(void);
extern int __hisi_get_disp_info(void *hisi_disp_info);
extern int __is_device_rooted(void);
#ifdef WITH_HISI_SEC_MMZ
/*MMZ*/
extern int __MMZ_MALLOC(SEC_MMZ_BUF_S *pBuf);
extern int __MMZ_FREE(SEC_MMZ_BUF_S *pBuf);
extern int __MMZ_NEW(SEC_MMZ_BUF_S *pBuf, char *mmz_name, char *mmb_name);
extern int __MMZ_DEL(unsigned long addr);
extern int __MMZ_MAP(unsigned long addr, unsigned long cached);
extern int __MMZ_UNMAP(unsigned long addr);
extern int __MMZ_FLUSH(unsigned long addr);
extern int __TEE_IsSecMMZ(unsigned long phys_addr);

extern int __TEE_IsSecMem(unsigned long phys_addr, unsigned long size);
extern int __TEE_IsNonSecMem(unsigned long phys_addr, unsigned long size);
extern int __call_debug(unsigned long arg0, unsigned long arg1, unsigned long arg2, unsigned long arg3);
#endif

#ifdef WITH_HISI_CIPHER
extern int __TEE_CIPHER_Ioctl(unsigned int cmd, void *argp);
#endif

#ifdef WITH_HISI_OTP
extern int __OTP_Init(void);
extern int __OTP_DeInit(void);
extern int __OTP_Reset(void);
extern int __OTP_GetChipID(uint8_t *pChipID);
extern int __OTP_ReadWord(uint32_t Addr, uint32_t *pu32Value);
extern int __OTP_ReadByte(uint32_t Addr, uint8_t *pu8Value);
extern int __OTP_WriteWord(uint32_t Addr, uint32_t u32Value);
extern int __OTP_WriteByte(uint32_t Addr, uint8_t u8Value);
#endif
#ifdef WITH_HISI_ADVCA
extern int __TEE_ADVCA_Ioctl(unsigned int cmd, void *argp);

#endif

/* smmu  */
#ifdef WITH_HISI_SMMU
extern UINT32 __hisi_sec_maptosmmu(unsigned long buf_phys, unsigned long buf_size);
extern int __hisi_sec_unmapfromsmmu(unsigned long buf_phys, unsigned long buf_size);
extern UINT32 __hisi_sec_maptosmmu_and_setflag(unsigned long buf_phys, unsigned long buf_size);
extern int __hisi_sec_unmapfromsmmu_and_clrflg(unsigned long buf_phys, unsigned long buf_size);
extern UINT32 __hisi_sec_alloc(const char *bufname, unsigned long size, unsigned long align, int memtype);
extern int __hisi_sec_free(unsigned long sec_addr, int memtype);
extern UINT32 __hisi_sec_map_to_cpu(unsigned long sec_addr, int memtype);
extern int __hisi_sec_unmap_from_cpu(void *sec_virt);
extern UINT32 __hisi_sec_map_to_sec_smmu(unsigned long phys_addr, unsigned long size, int share_mem);
extern int __hisi_sec_unmap_from_sec_smmu(unsigned long sec_smmu, int share_mem);
extern UINT32 __hisi_nonsec_mem_map_to_sec_cpu(unsigned long nonsec_addr, int memtype);
extern int __hisi_nosec_mem_unmap_from_sec_cpu(void *va_addr);
extern UINT32 __hisi_nosec_mem_map_to_sec_smmu(unsigned long nonsec_addr, int memtype);
extern int __hisi_nosec_mem_unmap_from_sec_smmu(unsigned long sec_smmu);
extern int __agent_closed(void);
#endif

extern int __get_vsim_sharemem(unsigned int *addr, unsigned int *size);
extern int __driver_fingerprint_command(void* cmmand_info);
extern int __driver_spi_full_duplex(void* p_write_info, void* p_read_info);

extern int __get_target_product(char* targe_product, int* size);
#ifdef WITH_HISI_PVR
extern HI_S32 __TEE_PVR_DeInit(HI_VOID);
//extern HI_S32 __TEE_PVR_OpenChannel(HI_U32 *pu32ChnId, HI_S32 s32BufLen, TEE_PVR_TYPE_E enType);
extern HI_S32 __TEE_PVR_OpenChannel(HI_U32 *pu32ChnId, HI_S32 s32BufLen, HI_U32 enType);
extern HI_S32 __TEE_PVR_CloseChannel(HI_U32 u32ChnId);
extern HI_S32 __TEE_PVR_RecProcTsData(HI_U32 u32ChnId, HI_U32 u32NoSecureSmmuAddr);
extern HI_S32 __TEE_PVR_RecCopyToRee(HI_U32 u32ChnId, HI_U32 u32NoSecureSmmuAddr, HI_U32 *pu32DataLen);
extern HI_S32 __TEE_PVR_PlayCopyFromRee(HI_U32 u32ReeAddr, HI_U32 u32TeeAddr, HI_U32 u32DataLen);
extern HI_S32 __TEE_PVR_RecGetOutputBufInfo(HI_U32 u32ChnId, HI_U32 *pu32SecureSmmuAddr, HI_U32 *pu32DataLen);
extern HI_S32 __TEE_PVR_RecGetStatus(HI_U32 u32ChnId, HI_U32 u32SecureSmmuAddr);
#endif

#ifdef WITH_HISI_SEC_HDMI
extern HI_S32 __HI_DRV_HDMI_SetSRM(HI_DRV_HDMI_DEVICE_ID_E enHdmiId, HI_U8 *pSrm);
extern HI_S32 __HI_DRV_HDMI_SetHDCPStrategy(HI_DRV_HDMI_DEVICE_ID_E enHdmiId, HI_DRV_HDMI_HDCP_LEVEL_E enHdcpLevle);
extern HI_S32 __HI_DRV_HDMI_GetHDCPStrategy(HI_DRV_HDMI_DEVICE_ID_E enHdmiId, HI_DRV_HDMI_HDCP_LEVEL_E *penHdcpLevel);
extern HI_S32 __HI_DRV_HDMI_GetHDCPStatus(HI_DRV_HDMI_DEVICE_ID_E enHdmiId, HI_DRV_HDMI_HDCP_STATUS_E *penHdcpStatus);
extern HI_S32 __HI_DRV_HDMI_SetHDCPMute(HI_DRV_HDMI_DEVICE_ID_E enHdmiId, HI_BOOL bMute);
extern HI_S32 __HI_DRV_HDMI_HDCP22_Init(HI_DRV_HDMI_DEVICE_ID_E enHdmiId);
extern HI_S32 __HI_DRV_HDMI_TeeProc(HI_DRV_HDMI_DEVICE_ID_E enHdmi);
extern HI_S32 __HI_DRV_HDMI_SetHDCPCaps(HI_DRV_HDMI_DEVICE_ID_E enHdmiId, HI_DRV_HDMI_HDCP_CAPS_S *pstHdcpCaps);
extern HI_S32 __HI_DRV_HDMI_GetHDCPCaps(HI_DRV_HDMI_DEVICE_ID_E enHdmiId, HI_DRV_HDMI_HDCP_CAPS_S *pstHdcpCaps);
extern HI_S32 __HI_DRV_HDMI_Init(HI_DRV_HDMI_DEVICE_ID_E enHdmiId);
extern HI_S32 __HI_DRV_HDMI_DeInit(HI_DRV_HDMI_DEVICE_ID_E enHdmiId);
extern HI_S32 __HI_DRV_HDMI_Start(HI_DRV_HDMI_DEVICE_ID_E enHdmiId);
extern HI_S32 __HI_DRV_HDMI_Stop(HI_DRV_HDMI_DEVICE_ID_E enHdmiId);

#endif

#ifdef WITH_STB_BEIDOU
extern int __Beidou_GetSoftwareVersion(char* version, unsigned int length);
extern int __Beidou_GetPositionParameters(int* longitude, int* latitude, unsigned int* timestamp);
extern unsigned int __Beidou_CalculateDistance(int longitudeA, int latitudeA, int longitudeB, int latitudeB);
#endif

#ifdef WITH_STB_I2C_DRIVER
extern int   __HI_DRV_I2C_SetRate(unsigned int I2cNum, unsigned int I2cRate);
extern int   __HI_DRV_I2C_Read(unsigned int  I2cNum, unsigned char I2cDevAddr, unsigned int I2cRegAddr, unsigned int I2cRegAddrByteNum, unsigned char *pData,unsigned int DataLen);
extern int   __HI_DRV_I2C_Write(unsigned int I2cNum, unsigned char I2cDevAddr, unsigned int I2cRegAddr, unsigned int I2cRegAddrByteNum, unsigned char *pData,unsigned int DataLen);
extern int   __HI_DRV_I2C_Init(void);
extern void  __HI_DRV_I2C_DeInit(void);
#endif
