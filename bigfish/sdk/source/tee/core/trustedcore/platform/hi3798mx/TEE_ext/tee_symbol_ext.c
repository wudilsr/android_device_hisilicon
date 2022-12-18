#include "tee_symbol.h"
#include "sre_syscalls_ext.h"
#include "tee_external_api.h"
#ifdef TEE_SUPPORT_TUI
#include "tui_api.h"
#include "tui_obj.h"
#include "tui_env.h"
#include "penpaint_api.h"
#include "tee_tui_api.h"
#endif
#ifdef WITH_HISI_SEC_MMZ
#include "hi_tee_mmz.h"
#endif
#ifdef WITH_HISI_CIPHER
#include "hi_tee_cipher.h"
#endif
#include "sre_syscall.h"
#ifdef WITH_HISI_OTP
#include "hi_tee_otp.h"
#endif
#ifdef WITH_HISI_ADVCA
#include "hi_tee_advca.h"
#endif

#ifdef WITH_HISI_DMX
#include "hi_tee_descrambler.h"
#include "hi_tee_scrambler.h"
#include "tee_demux_utils.h"
#endif
#ifdef WITH_HISI_PVR
#include "tee_pvr.h"
#endif
#ifdef WITH_HISI_SEC_HDMI
#include "hi_tee_hdmi.h"
#include "tee_hdmi.h"

#endif

#ifdef WITH_HISI_SMMU
#include "hi_tee_mem.h"
#endif


#ifdef WITH_STB_BEIDOU
#include "tee_beidou_api.h"
#endif


EXPORT_SYMBOL(__bsp_efuse_read);
EXPORT_SYMBOL(__bsp_efuse_write);
EXPORT_SYMBOL(__bsp_sec_call);
EXPORT_SYMBOL(__tee_hal_get_dieid);

EXPORT_SYMBOL(__hisi_fb_cfg_sec);
#if !(defined(WITH_STB_PLATFORM) || defined(WITH_DPT_PLATFORM)) //del by f00216599
EXPORT_SYMBOL(__hisi_get_vactive_flag);
EXPORT_SYMBOL(__hisi_wait_vactive_flag);
EXPORT_SYMBOL(__hisi_wait_release_flag);
EXPORT_SYMBOL(__hisi_fb_alpha_set);
#endif
EXPORT_SYMBOL(__hisi_get_disp_info);

EXPORT_SYMBOL(__scard_connect);
EXPORT_SYMBOL(__scard_disconnect);
EXPORT_SYMBOL(__scard_transmit);
#ifdef TEE_SUPPORT_TUI

// tee tui api
EXPORT_SYMBOL(init_tui_api);
EXPORT_SYMBOL(tui_init);
EXPORT_SYMBOL(tui_release);
EXPORT_SYMBOL(poll_tui_event);
EXPORT_SYMBOL(tui_show);
EXPORT_SYMBOL(tui_get_tpdata);
EXPORT_SYMBOL(init_keyboard);

//png
EXPORT_SYMBOL(canvas_blit);
EXPORT_SYMBOL(create_canvas);
EXPORT_SYMBOL(destroy_canvas);
EXPORT_SYMBOL(tui_draw_picture);
EXPORT_SYMBOL(tui_draw_picture_ext);
EXPORT_SYMBOL(tui_draw_pic);
EXPORT_SYMBOL(tui_draw_pic_ext);
EXPORT_SYMBOL(tui_draw_pic_ext_scale);

EXPORT_SYMBOL(create_screen_canvas);
EXPORT_SYMBOL(destroy_screen_canvas);


//ui func
EXPORT_SYMBOL(ui_draw_rect);
EXPORT_SYMBOL(ui_draw_round_rect);
EXPORT_SYMBOL(ui_draw_line);
EXPORT_SYMBOL(ui_draw_point);

EXPORT_SYMBOL(ui_system_open);
EXPORT_SYMBOL(ui_system_close);
EXPORT_SYMBOL(ui_open);
EXPORT_SYMBOL(ui_close);
EXPORT_SYMBOL(ui_show);
EXPORT_SYMBOL(ui_bitmap);


EXPORT_SYMBOL(get_win_info);
EXPORT_SYMBOL(env_init);
EXPORT_SYMBOL(env_attach_ui);
EXPORT_SYMBOL(env_attach_IM);
EXPORT_SYMBOL(env_attach_IM_keyboard);
EXPORT_SYMBOL(env_attach_SI);
EXPORT_SYMBOL(env_status_init);
EXPORT_SYMBOL(env_showup);
EXPORT_SYMBOL(env_release);
EXPORT_SYMBOL(env_event_loop);
EXPORT_SYMBOL(env_keyboard_loop);
EXPORT_SYMBOL(env_set_focus);
EXPORT_SYMBOL(env_event_loop_quit);
EXPORT_SYMBOL(keyboard_font_init);
EXPORT_SYMBOL(keyboard_font_exit);
EXPORT_SYMBOL(font_init);
EXPORT_SYMBOL(font_close);
EXPORT_SYMBOL(ui_set);



EXPORT_SYMBOL(create_pen);
EXPORT_SYMBOL(destroy_pen);
EXPORT_SYMBOL(tui_draw_string);
EXPORT_SYMBOL(tui_draw_string_ext);
EXPORT_SYMBOL(tui_check_text_format);

EXPORT_SYMBOL(TEE_TUIInitSession);
EXPORT_SYMBOL(TEE_TUIDisplayScreen);
EXPORT_SYMBOL(TEE_TUICloseSession);
EXPORT_SYMBOL(TEE_TUIGetScreenInfo);
EXPORT_SYMBOL(TEE_TUICheckTextFormat);
EXPORT_SYMBOL(TEE_TUISetInfo);
#endif
EXPORT_SYMBOL(__driver_dep_test);
EXPORT_SYMBOL(__driver_p61_factory_test);
EXPORT_SYMBOL(__driver_fingerprint_command);
EXPORT_SYMBOL(__driver_spi_full_duplex);

// vfmw interface
#ifdef WITH_HISI_VFMW
EXPORT_SYMBOL(__VDEC_Suspend);
EXPORT_SYMBOL(__VDEC_Init);
EXPORT_SYMBOL(__VDEC_Resume);
EXPORT_SYMBOL(__VFMW_CTRL_thread_sec);
EXPORT_SYMBOL(__VDEC_Control);
EXPORT_SYMBOL(__VDEC_InitWithOperation);
EXPORT_SYMBOL(__VDEC_MMZCA2TA);
EXPORT_SYMBOL(__VCTRL_WriteProc);
EXPORT_SYMBOL(__VCTRL_ReadProc);
EXPORT_SYMBOL(__VCTRL_SetDbgOption);
EXPORT_SYMBOL(__VCTRL_GetChanImage);
EXPORT_SYMBOL(__VCTRL_ReleaseChanImage);
EXPORT_SYMBOL(__VDEC_Exit);
#endif

#ifdef WITH_HISI_SEC_MMZ
//SEC MMZ interface
EXPORT_SYMBOL(__MMZ_MALLOC);
EXPORT_SYMBOL(__MMZ_FREE);
EXPORT_SYMBOL(__MMZ_NEW);
EXPORT_SYMBOL(__MMZ_DEL);
EXPORT_SYMBOL(__MMZ_MAP);
EXPORT_SYMBOL(__MMZ_UNMAP);
EXPORT_SYMBOL(__MMZ_FLUSH);
EXPORT_SYMBOL(__TEE_IsSecMMZ);

EXPORT_SYMBOL(HI_TEE_MMZ_New);
EXPORT_SYMBOL(HI_TEE_MMZ_Delete);
EXPORT_SYMBOL(HI_TEE_MMZ_Map);
EXPORT_SYMBOL(HI_TEE_MMZ_Unmap);
EXPORT_SYMBOL(HI_TEE_MMZ_Flush);

//SEC MEM

EXPORT_SYMBOL(__TEE_IsSecMem);
EXPORT_SYMBOL(__TEE_IsNonSecMem);
//SEC debug
EXPORT_SYMBOL(__call_debug);

#endif

#ifdef WITH_HISI_CIPHER
extern HI_S32 HI_TEE_CIPHER_Test(HI_U32 u32Cmd, HI_VOID *pu8Param, HI_U32 u32ParamSize);

EXPORT_SYMBOL(HI_TEE_CIPHER_Init);
EXPORT_SYMBOL(HI_TEE_CIPHER_DeInit);
EXPORT_SYMBOL(HI_TEE_CIPHER_Encrypt);
EXPORT_SYMBOL(HI_TEE_CIPHER_Decrypt);
EXPORT_SYMBOL(HI_TEE_CIPHER_EncryptMulti);
EXPORT_SYMBOL(HI_TEE_CIPHER_DecryptMulti);
EXPORT_SYMBOL(HI_TEE_CIPHER_ConfigHandle);
EXPORT_SYMBOL(HI_TEE_CIPHER_CreateHandle);
EXPORT_SYMBOL(HI_TEE_CIPHER_DestroyHandle);
EXPORT_SYMBOL(HI_TEE_CIPHER_GetHandleConfig);
EXPORT_SYMBOL(HI_TEE_CIPHER_GetRandomNumber);
EXPORT_SYMBOL(HI_TEE_CIPHER_HashInit);
EXPORT_SYMBOL(HI_TEE_CIPHER_HashUpdate);
EXPORT_SYMBOL(HI_TEE_CIPHER_HashFinal);
EXPORT_SYMBOL(HI_TEE_CIPHER_RsaPublicEncrypt);
EXPORT_SYMBOL(HI_TEE_CIPHER_RsaPrivateDecrypt);
EXPORT_SYMBOL(HI_TEE_CIPHER_RsaPrivateEncrypt);
EXPORT_SYMBOL(HI_TEE_CIPHER_RsaPublicDecrypt);
EXPORT_SYMBOL(HI_TEE_CIPHER_RsaSign);
EXPORT_SYMBOL(HI_TEE_CIPHER_RsaVerify);
EXPORT_SYMBOL(HI_TEE_CIPHER_PBKDF2);
EXPORT_SYMBOL(HI_TEE_CIPHER_Test);
#endif

#ifdef WITH_HISI_OTP
EXPORT_SYMBOL(__OTP_Init);
EXPORT_SYMBOL(__OTP_DeInit);
EXPORT_SYMBOL(__OTP_Reset);
EXPORT_SYMBOL(__OTP_GetChipID);
EXPORT_SYMBOL(__OTP_ReadWord);
EXPORT_SYMBOL(__OTP_ReadByte);
EXPORT_SYMBOL(__OTP_WriteWord);
EXPORT_SYMBOL(__OTP_WriteByte);


EXPORT_SYMBOL(HI_TEE_OTP_Init);
EXPORT_SYMBOL(HI_TEE_OTP_DeInit);
EXPORT_SYMBOL(HI_TEE_OTP_Reset);
EXPORT_SYMBOL(HI_TEE_OTP_GetChipID);
EXPORT_SYMBOL(HI_TEE_OTP_ReadWord);
EXPORT_SYMBOL(HI_TEE_OTP_ReadByte);
EXPORT_SYMBOL(HI_TEE_OTP_WriteWord);
EXPORT_SYMBOL(HI_TEE_OTP_WriteByte);
#endif

#ifdef WITH_HISI_ADVCA
EXPORT_SYMBOL(HI_TEE_ADVCA_Init);
EXPORT_SYMBOL(HI_TEE_ADVCA_DeInit);
EXPORT_SYMBOL(HI_TEE_ADVCA_GetOtpFuse);
EXPORT_SYMBOL(HI_TEE_ADVCA_SetOtpFuse);
EXPORT_SYMBOL(HI_TEE_ADVCA_SetKeyLadderAttr);
EXPORT_SYMBOL(HI_TEE_ADVCA_DCASClose);
EXPORT_SYMBOL(HI_TEE_ADVCA_DCASOpen);
EXPORT_SYMBOL(HI_TEE_ADVCA_GetDCASChipId);
EXPORT_SYMBOL(HI_TEE_ADVCA_SetDCASSessionKey);
EXPORT_SYMBOL(HI_TEE_ADVCA_CalculteAES_CMAC);
EXPORT_SYMBOL(HI_TEE_ADVCA_CaVendorOperation);
EXPORT_SYMBOL(HI_TEE_ADVCA_VMXMiscOpen);
EXPORT_SYMBOL(HI_TEE_ADVCA_VMXMiscClose);
EXPORT_SYMBOL(HI_TEE_ADVCA_SetVMXMiscSessionKey);
EXPORT_SYMBOL(HI_TEE_ADVCA_SetVMXMiscAlg);
EXPORT_SYMBOL(HI_TEE_ADVCA_SetVMXMiscDscMode);
EXPORT_SYMBOL(HI_TEE_ADVCA_GetVMXMiscKlLevel);
EXPORT_SYMBOL(HI_TEE_ADVCA_VMXSPOpen);
EXPORT_SYMBOL(HI_TEE_ADVCA_VMXSPClose);
EXPORT_SYMBOL(HI_TEE_ADVCA_SetVMXSPSessionKey);
EXPORT_SYMBOL(HI_TEE_ADVCA_SetVMXSPAlg);
EXPORT_SYMBOL(HI_TEE_ADVCA_SetVMXSPDscMode);
EXPORT_SYMBOL(HI_TEE_ADVCA_GetVMXSPKlLevel);
#endif

#ifdef WITH_HISI_SMMU
EXPORT_SYMBOL(__hisi_sec_maptosmmu);
EXPORT_SYMBOL(__hisi_sec_unmapfromsmmu);
EXPORT_SYMBOL(__hisi_sec_maptosmmu_and_setflag);
EXPORT_SYMBOL(__hisi_sec_unmapfromsmmu_and_clrflg);
EXPORT_SYMBOL(__hisi_sec_alloc);
EXPORT_SYMBOL(__hisi_sec_free);
EXPORT_SYMBOL(__hisi_sec_map_to_cpu);
EXPORT_SYMBOL(__hisi_sec_unmap_from_cpu);
EXPORT_SYMBOL(__hisi_sec_map_to_sec_smmu);
EXPORT_SYMBOL(__hisi_sec_unmap_from_sec_smmu);
EXPORT_SYMBOL(__hisi_nonsec_mem_map_to_sec_cpu);
EXPORT_SYMBOL(__hisi_nosec_mem_unmap_from_sec_cpu);
EXPORT_SYMBOL(__hisi_nosec_mem_map_to_sec_smmu);
EXPORT_SYMBOL(__hisi_nosec_mem_unmap_from_sec_smmu);
EXPORT_SYMBOL(__agent_closed);


EXPORT_SYMBOL(HI_TEE_SMMU_Alloc);
EXPORT_SYMBOL(HI_TEE_SMMU_Free);
EXPORT_SYMBOL(HI_TEE_SMMU_MapToCpu);
EXPORT_SYMBOL(HI_TEE_SMMU_UnmapFromCpu);
EXPORT_SYMBOL(HI_TEE_MMZ_Alloc);
EXPORT_SYMBOL(HI_TEE_MMZ_Free);
EXPORT_SYMBOL(HI_TEE_MMZ_MapToCpu);
EXPORT_SYMBOL(HI_TEE_MMZ_UnmapFromCpu);
EXPORT_SYMBOL(HI_TEE_MMZ_FlushMem);
EXPORT_SYMBOL(HI_TEE_MMZ_MapToSmmu);
EXPORT_SYMBOL(HI_TEE_MMZ_UnmapFromSmmu);
EXPORT_SYMBOL(HI_TEE_SMMU_NonsecSmmu_MapToCpu);
EXPORT_SYMBOL(HI_TEE_SMMU_NonsecSmmu_UnmapFromCpu);
EXPORT_SYMBOL(HI_TEE_SMMU_NonsecSmmu_MapToSecSmmu);
EXPORT_SYMBOL(HI_TEE_SMMU_NonsecSmmu_UnmapFromSecSmmu);
EXPORT_SYMBOL(HI_TEE_SMMU_NonsecMMZ_MapToCpu);
EXPORT_SYMBOL(HI_TEE_SMMU_NonsecMMZ_UnmapFromCpu);
EXPORT_SYMBOL(HI_TEE_SMMU_NonsecMMZ_MapToSecSmmu);
EXPORT_SYMBOL(HI_TEE_SMMU_NonsecMMZ_UnmapFromSecSmmu);
#endif

#ifdef WITH_HISI_DMX
EXPORT_SYMBOL(HI_TEE_DMX_CreateDescrambler);
EXPORT_SYMBOL(HI_TEE_DMX_DestroyDescrambler);
EXPORT_SYMBOL(HI_TEE_DMX_GetDescramblerAttr);
EXPORT_SYMBOL(HI_TEE_DMX_SetDescramblerAttr);
EXPORT_SYMBOL(HI_TEE_DMX_SetDescramblerEvenKey);
EXPORT_SYMBOL(HI_TEE_DMX_SetDescramblerOddKey);
EXPORT_SYMBOL(HI_TEE_DMX_SetDescramblerEvenIVKey);
EXPORT_SYMBOL(HI_TEE_DMX_SetDescramblerOddIVKey);
EXPORT_SYMBOL(HI_TEE_DMX_AttachDescrambler);
EXPORT_SYMBOL(HI_TEE_DMX_DetachDescrambler);
EXPORT_SYMBOL(HI_TEE_DMX_GetDescramblerKeyHandle);

EXPORT_SYMBOL(HI_TEE_DMX_GetScramblerDefaultAttr);
EXPORT_SYMBOL(HI_TEE_DMX_CreateScrambler);
EXPORT_SYMBOL(HI_TEE_DMX_DestroyScrambler);
EXPORT_SYMBOL(HI_TEE_DMX_GetScramblerAttr);
EXPORT_SYMBOL(HI_TEE_DMX_SetScramblerAttr);
EXPORT_SYMBOL(HI_TEE_DMX_SetScramblerEvenKey);
EXPORT_SYMBOL(HI_TEE_DMX_SetScramblerOddKey);
EXPORT_SYMBOL(HI_TEE_DMX_AttachScrambler);
EXPORT_SYMBOL(HI_TEE_DMX_DetachScrambler);
EXPORT_SYMBOL(HI_TEE_DMX_GetScramblerKeyHandle);

EXPORT_SYMBOL(HI_TEE_DMX_GetChannelHandle);

EXPORT_SYMBOL(TEE_DMX_RegisterChannel);
EXPORT_SYMBOL(TEE_DMX_UnregisterChannel);
EXPORT_SYMBOL(TEE_DMX_RegisterOq);
EXPORT_SYMBOL(TEE_DMX_UnregisterOq);
EXPORT_SYMBOL(TEE_DMX_RegisterRamPort);
EXPORT_SYMBOL(TEE_DMX_UnregisterRamPort);
EXPORT_SYMBOL(TEE_DMX_RegisterVidSecBuf);
EXPORT_SYMBOL(TEE_DMX_UnregisterVidSecBuf);
EXPORT_SYMBOL(TEE_DMX_RegisterAudSecBuf);
EXPORT_SYMBOL(TEE_DMX_UnregisterAudSecBuf);
EXPORT_SYMBOL(TEE_DMX_RegisterRecSecBuf);
EXPORT_SYMBOL(TEE_DMX_UnregisterRecSecBuf);
EXPORT_SYMBOL(TEE_DMX_LockChannel);
EXPORT_SYMBOL(TEE_DMX_UnlockChannel);
EXPORT_SYMBOL(TEE_DMX_ParserPesHeader);
EXPORT_SYMBOL(TEE_DMX_ParserPesDispCtrlInfo);
EXPORT_SYMBOL(TEE_DMX_GetPesHeaderLen);
EXPORT_SYMBOL(TEE_DMX_FixupAudSecBuf);
EXPORT_SYMBOL(TEE_DMX_ParserSCData);
EXPORT_SYMBOL(TEE_DMX_ParserFilterSCData);
#endif

#ifdef WITH_HISI_PVR
EXPORT_SYMBOL(TEE_PVR_DeInit);
EXPORT_SYMBOL(TEE_PVR_RecOpenChannel);
EXPORT_SYMBOL(TEE_PVR_RecCloseChannel);
EXPORT_SYMBOL(TEE_PVR_RecProcTsData);
EXPORT_SYMBOL(TEE_PVR_RecCopyToRee);
EXPORT_SYMBOL(TEE_PVR_PlayCopyFromRee);
EXPORT_SYMBOL(TEE_PVR_RecGetOutputBufInfo);
EXPORT_SYMBOL(TEE_PVR_RecGetStatus);
#endif
#if !(defined(WITH_STB_PLATFORM) || defined(WITH_DPT_PLATFORM)) //del by f00216599
EXPORT_SYMBOL(__get_target_product);
#endif

#ifdef WITH_HISI_SEC_HDMI

EXPORT_SYMBOL(__HI_DRV_HDMI_SetSRM);
EXPORT_SYMBOL(__HI_DRV_HDMI_SetHDCPStrategy);
EXPORT_SYMBOL(__HI_DRV_HDMI_GetHDCPStrategy);
EXPORT_SYMBOL(__HI_DRV_HDMI_GetHDCPStatus);
EXPORT_SYMBOL(__HI_DRV_HDMI_SetHDCPMute);
EXPORT_SYMBOL(__HI_DRV_HDMI_HDCP22_Init);
EXPORT_SYMBOL(__HI_DRV_HDMI_TeeProc);
EXPORT_SYMBOL(__HI_DRV_HDMI_SetHDCPCaps);
EXPORT_SYMBOL(__HI_DRV_HDMI_GetHDCPCaps);
EXPORT_SYMBOL(__HI_DRV_HDMI_Init);
EXPORT_SYMBOL(__HI_DRV_HDMI_DeInit);
EXPORT_SYMBOL(__HI_DRV_HDMI_Start);
EXPORT_SYMBOL(__HI_DRV_HDMI_Stop);

EXPORT_SYMBOL(TEE_DRV_HDMI_HDCP22_Init);
EXPORT_SYMBOL(TEE_DRV_HDMI_HDCP14_Init);
EXPORT_SYMBOL(TEE_DRV_HDMI_TEEProc);
EXPORT_SYMBOL(TEE_DRV_HDMI_SetHDCPCaps);
EXPORT_SYMBOL(TEE_DRV_HDMI_Init);
EXPORT_SYMBOL(TEE_DRV_HDMI_DeInit);
EXPORT_SYMBOL(TEE_DRV_HDMI_Start);
EXPORT_SYMBOL(TEE_DRV_HDMI_Stop);

EXPORT_SYMBOL(HI_TEE_HDMI_CreateHandle);
EXPORT_SYMBOL(HI_TEE_HDMI_DestoryHandle);
EXPORT_SYMBOL(HI_TEE_HDMI_GetHDCPStatus);
EXPORT_SYMBOL(HI_TEE_HDMI_SetHDCPStrategy);
EXPORT_SYMBOL(HI_TEE_HDMI_GetHDCPStrategy);
EXPORT_SYMBOL(HI_TEE_HDMI_GetHDCPCaps);


#endif
extern void std_printf_func(const char *fmt, ...);
EXPORT_SYMBOL(std_printf_func);
#ifdef WITH_HISI_DEMO
extern TEE_Result tee_rpmb_write_key(void);
EXPORT_SYMBOL(tee_rpmb_write_key);
#endif

EXPORT_SYMBOL(ASM_MemMove);
EXPORT_SYMBOL(ASM_MemCopy);


#ifdef WITH_STB_BEIDOU
EXPORT_SYMBOL(__Beidou_GetSoftwareVersion);
EXPORT_SYMBOL(__Beidou_GetPositionParameters);
EXPORT_SYMBOL(__Beidou_CalculateDistance);

EXPORT_SYMBOL(TEE_Beidou_GetSoftwareVersion);
EXPORT_SYMBOL(TEE_Beidou_GetPositionParameters);
EXPORT_SYMBOL(TEE_Beidou_CalculateDistance);

#endif