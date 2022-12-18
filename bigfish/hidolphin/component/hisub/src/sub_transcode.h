/**
\file
\brief subtitle transcode
\copyright Shenzhen Hisilicon Co., Ltd.
\date 2008-2018
\version draft
\author l00167705
\date 2013-9-16
*/

#ifndef __SUB_TRANSCODE_H__
#define __SUB_TRANSCODE_H__

/* add include here */


#ifdef __cplusplus
extern "C" {
#endif
/***************************** Macro Definition ******************************/



/*************************** Structure Definition ****************************/



/********************** Global Variable declaration **************************/



/******************************* API declaration *****************************/

HI_S32 sub_transcode_init();
HI_S32 sub_transcode_deinit();
HI_S32 sub_transcode_data(HI_U8* pu8DataIn, HI_U32 u32DataInLen, HI_U8* pu8Utf8DataOut,
                         HI_U32 u32DataOutBufferLen, HI_S32* ps32DataOutLen);


#ifdef __cplusplus
}
#endif
#endif /* __SUB_TRANSCODE_H__ */
