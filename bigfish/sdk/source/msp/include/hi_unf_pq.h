/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hi_unf_pq.h
  Version       : Initial Draft
  Author        : p00203646
  Created       : 2014/4/23
  Description   :

******************************************************************************/

#ifndef __HI_UNF_PQ_H__
#define __HI_UNF_PQ_H__

#include "hi_type.h"
#include "hi_unf_disp.h"


#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */
/******************************************************************************/


/********************************Struct Definition********************************/
/** \addtogroup      PQ */
/** @{ */  /** <!-- [PQ] */

/**<Image Mode Set Different Parameters Under Different Mode*/
/**<CNcomment:ͼ��ģʽѡ���ڲ�ͬ��ģʽ�����ò�ͬ�Ĳ��� CNend*/
typedef enum hiUNF_PQ_IMAGE_MODE_E
{
    HI_UNF_OPTION_MODE_NATURAL = 0,  /**<Natural mode*/ /**<CNcomment:��Ȼģʽ CNend*/
    HI_UNF_OPTION_MODE_PERSON,       /**<Person mode*/ /**<CNcomment:����ģʽ CNend*/
    HI_UNF_OPTION_MODE_FILM,         /**<Film mode*/ /**<CNcomment:��Ӱģʽ CNend*/
    HI_UNF_OPTION_MODE_UD,           /**<User Defined mode*/ /**<CNcomment:�û��Զ���ģʽ CNend*/
    HI_UNF_OPTION_MODE_BUTT,
} HI_UNF_PQ_IMAGE_MODE_E;

/**<HD and SD Channels Parameter*/
/**<CNcomment:�߱���ͨ������ CNend*/
typedef struct hiUNF_PQ_OPT_CHAN_S
{
    HI_U32       u32Brightness;         /**<Brightness; Range:0~100; recommended: 50 */ /**<CNcomment:���ȣ���Χ: 0~100���Ƽ�ֵ: 50 CNend*/
    HI_U32       u32Contrast;           /**<Contrast; Range:0~100; recommended: 50 */ /**<CNcomment:�Աȶȣ���Χ: 0~100���Ƽ�ֵ: 50 CNend*/ 
    HI_U32       u32Hue;                /**<HuePlus; Range:0~100; recommended: 50 */ /**<CNcomment:ɫ������Χ: 0~100���Ƽ�ֵ: 50 CNend*/ 
    HI_U32       u32Saturation;         /**<Saturation; Range:0~100; recommended: 50 */ /**<CNcomment:���Ͷȣ���Χ: 0~100���Ƽ�ֵ: 50 CNend*/
    HI_U32       u32Colortemperature;   /**<Color temperature mode; Range:0~2 Cold,Middle,Warm */ /**<CNcomment: ɫ��ģʽ����Χ: 0~2 ��ɫ��,�м�ɫ��,ůɫ�� CNend*/
    HI_U32       u32GammaMode;          /**<Gamma mode; Range:0~4 Intension_1.8,Intension_2.5,Curve_Light,Curve_Dark, Disabled */ /**<CNcomment:٤��ģʽѡ�񣻷�Χ: 0~4 1.8ǿ��,2.5ǿ��,��,��,�ر� CNend*/
    HI_U32       u32DynamicContrast;    /**<Color Dynamic Contrast mode; Range:0~3 Low, Middle,High,Disabled */ /**<CNcomment:��̬�Աȶȣ���Χ: 0~3 ��,��,��,�ر� CNend*/
    HI_U32       u32IntelligentColor;   /**<Color Intelligent Color; Range:0~5 Blue,Green,BG,Skin,Vivid,Disabled */ /**<CNcomment:������ɫ������Χ: 0~5 ��ɫ,��ɫ,������ǿ,��ɫ,����,�ر� CNend*/    
} HI_UNF_PQ_OPT_CHAN_S;

/**<Common Parameter*/
/**<CNcomment:ͨ�ò��� CNend*/
typedef struct hiUNF_PQ_OPT_COMMON_S
{
    HI_U32       u32Sharpeness;      /**<Sharpeness; Range:0~100; recommended: 50 */ /**<CNcomment:��ǿ�ȣ���Χ:0~100���Ƽ�ֵ:50 CNend*/                
    HI_U32       u32Denoise;         /**<Denoise; Range:0~1 Disabled,Auto */ /**<CNcomment:����ʹ�ܣ���Χ:0~1 �ر�,�� CNend*/       
    HI_U32       u32FilmMode;        /**<FileMode; Range:0~1 Disabled,Auto */ /**<CNcomment:��Ӱģʽʹ��ѡ�񣻷�Χ:0~1 �ر�,�� CNend*/    
    
} HI_UNF_PQ_OPT_COMMON_S;

/**<Interface Type and Interface Ialue*/
/**<CNcomment:�ӿ����ͺ�ͨ������ CNend*/
typedef struct hiUNF_PQ_OPT_CHANS_S
{
    HI_UNF_DISP_E enChan;               /**<interface type */ /**<CNcomment:�ӿ����� CNend*/
    HI_UNF_PQ_OPT_CHAN_S stChanOpt;     /**<interface value*/ /**<CNcomment:ͨ������ CNend*/
} HI_UNF_PQ_OPT_CHANS_S;


/******************************************************************************/

/* ����ģʽ */
typedef enum hiUNF_PQ_DEMO_E
{
     HI_UNF_PQ_DEMO_SHARPNESS = 0,
     HI_UNF_PQ_DEMO_DCI,
     HI_UNF_PQ_DEMO_COLOR,
     HI_UNF_PQ_DEMO_SR,
     HI_UNF_PQ_DEMO_ALL,

     HI_UNF_PQ_DEMO_BUTT
}  HI_UNF_PQ_DEMO_E;

/* PQģ��*/
typedef enum hiUNF_PQ_MODULE_E
{
     HI_UNF_PQ_MODULE_SHARPNESS = 0,
     HI_UNF_PQ_MODULE_DCI,
     HI_UNF_PQ_MODULE_COLOR,
     HI_UNF_PQ_MODULE_SR,
    HI_UNF_PQ_MODULE_ALL,

     HI_UNF_PQ_MODULE_BUTT
}  HI_UNF_PQ_MODULE_E;



/*SR��ʾģʽ*/
typedef enum hiUNF_PQ_SR_DEMO_E
{
     HI_UNF_PQ_SR_DISABLE  = 0,//�ص�SR,ֻZME
     HI_UNF_PQ_SR_ENABLE_R,  //  �ұ�SR
     HI_UNF_PQ_SR_ENABLE_L,  //���SR
     HI_UNF_PQ_SR_ENABLE_A,  //ȫ��

     HI_UNF_PQ_SR_DEMO_BUTT
}HI_UNF_PQ_SR_DEMO_E;


/*����ɫ��ǿ����*/
typedef struct  hiUNF_PQ_SIX_BASE_S
{
    HI_U32  u32Red;       //��Χ:0~100 
    HI_U32  u32Green;     //��Χ:0~100      
    HI_U32  u32Blue;      //��Χ:0~100 
	
    HI_U32  u32Cyan;      //��Χ:0~100   
    HI_U32  u32Magenta;   //��Χ:0~100        
    HI_U32  u32Yellow;    //��Χ:0~100  	
}HI_UNF_PQ_SIX_BASE_S;


/*��ɫ�������*/
typedef enum hiUNF_PQ_FLESHTONE_E
{
     HI_UNF_PQ_FLESHTONE_GAIN_OFF = 0,
     HI_UNF_PQ_FLESHTONE_GAIN_LOW,
     HI_UNF_PQ_FLESHTONE_GAIN_MID,
     HI_UNF_PQ_FLESHTONE_GAIN_HIGH,

     HI_UNF_PQ_FLESHTONE_GAIN_BUTT
}  HI_UNF_PQ_FLESHTONE_E;


/*��ɫ��ǿ����*/
typedef enum hiUNF_PQ_COLOR_ENHANCE_E
{
    HI_UNF_PQ_COLOR_ENHANCE_FLESHTONE = 0,    //��ɫ��ǿ
    HI_UNF_PQ_COLOR_ENHANCE_SIX_BASE,         //����ɫ��ǿ,�Զ�����ɫ����ǿ
    HI_UNF_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE,  //�̶�ģʽ����ɫ��ǿģʽ
    HI_UNF_PQ_COLOR_ENHANCE_BUTT
} HI_UNF_PQ_COLOR_ENHANCE_E;


/*��ɫ��ǿ����*/
typedef enum hiUNF_PQ_COLOR_SPEC_MODE_E
{
    HI_UNF_PQ_COLOR_MODE_RECOMMEND = 0, //�Ƽ�����ɫ��ǿģʽ
    HI_UNF_PQ_COLOR_MODE_BLUE,          //�̶�����ɫ��ǿģʽ
    HI_UNF_PQ_COLOR_MODE_GREEN,         //�̶�����ɫ��ǿģʽ
    HI_UNF_PQ_COLOR_MODE_BG,            //�̶�������ɫ��ǿģʽ
    HI_UNF_PQ_COLOR_MODE_BUTT
} HI_UNF_PQ_COLOR_SPEC_MODE_E;


/*��ɫ��ǿ����*/
typedef struct  hiUNF_PQ_COLOR_ENHANCE_S
{
    HI_UNF_PQ_COLOR_ENHANCE_E    enColorEnhanceType;   //ɫ����ǿ����   
    union
    {
        HI_UNF_PQ_FLESHTONE_E    enFleshtone;        //��ɫ��ǿ����
        HI_UNF_PQ_SIX_BASE_S     stSixBase;          //����ɫ��ǿ����
        HI_UNF_PQ_COLOR_SPEC_MODE_E   enColorMode;   //�̶�����ɫ��ǿģʽ

    } unColorGain;
} HI_UNF_PQ_COLOR_ENHANCE_S;



/******************************************************************************/
/**
 \brief Set PQ mode . CNcomment: ����ͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] enImageMode Destination DISP channel PQ mode CNcomment: Ŀ��ͨ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_SetImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E enImageMode);

/**
 \brief Get PQ mode . CNcomment: ��ȡͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] penImageMode  pointer of image mode CNcomment: ָ�����ͣ�ָ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_GetImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E* penImageMode);

/**
 \brief Init PQ mode . CNcomment: ��ʼ��ͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] penImageMode  pointer of image mode CNcomment: ָ�����ͣ�ָ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_InitImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E enImageMode);

/**
 \brief Set channel option. CNcomment: ����ͨ��optionֵ CNend
 \attention \n
 \param[in] pstChanOption pointer of channel option CNcomment: ָ�����ͣ�ָ��ͨ��optionֵ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_SetChanOption(const HI_UNF_PQ_OPT_CHANS_S* pstChanOption);

/**
 \brief Set channel option. CNcomment: ��ȡͨ��optionֵ CNend
 \attention \n
 \param[out] pstChanOption pointer of channel option CNcomment: ָ�����ͣ�ָ��ͨ��optionֵ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_GetChanOption(HI_UNF_PQ_OPT_CHANS_S * pstChanOption);

/**
 \brief Set channel common option. CNcomment: ����ͨ�� common optionֵ CNend
 \attention \n
 \param[in] pstCommOption pointer of channel common option CNcomment: ָ�����ͣ�ָ��ͨ��common optionֵ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_SetCommOption(const HI_UNF_PQ_OPT_COMMON_S* pstCommOption);

/**
 \brief Set channel option. CNcomment: ��ȡͨ��common optionֵ CNend
 \attention \n
 \param[out] pstChanOption pointer of channel option CNcomment: ָ�����ͣ�ָ��ͨ��common optionֵ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_GetCommOption(HI_UNF_PQ_OPT_COMMON_S* pstCommOption);


/**
 \brief Modifies the basic configuration information.  CNcomment:����PQ��������Ϣ CNend
	\attention \n
	\param[in] N/A CNcomment: �� CNend
	\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
	\see \n
 N/A CNcomment: �� CNend
	*/
	
HI_S32 HI_UNF_PQ_UpdatePqParam(HI_VOID);

/**
 \brief Set the default PQ configuration for video parameter test.  CNcomment: Ϊ����ָ���������PQ ��Ĭ��ֵCNend
	\attention \n
	\param[in] N/A CNcomment: �� CNend
	\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
	\see \n
 N/A CNcomment: �� CNend
	*/
	
HI_S32 HI_UNF_PQ_SetDefaultParam(HI_VOID);


/******************************************************************************/


/** \addtogroup      PQ */
/** @{ */  /** <!-- ��PQ�� */

/**
 \brief Initializes the picture quality unit (PQU). CNcomment: ��ʼ��PQ CNend
 \attention \n
Before calling the PQU, you must call this application programming interface (API).
CNcomment: ����PQģ��Ҫ�����ȵ��øýӿ� CNend
 \param[in] N/A CNcomment: �� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \retval ::HI_ERR_PQ_DEV_NOT_EXIST No PQ device exists. CNcomment: �豸������ CNend
 \retval ::HI_ERR_PQ_NOT_DEV_FILE The file is not a PQ file. CNcomment: �ļ����豸 CNend
 \retval ::HI_ERR_PQ_DEV_OPENED The PQ device fails to be started. CNcomment: ���豸ʧ�� CNend
 \see \n
N/A CNcomment: �� CNend
 */

extern HI_S32 HI_UNF_PQ_Init(HI_VOID);

/**
 \brief Deinitializes the PQU. CNcomment: ȥ��ʼ��PQ CNend
 \attention \n
 \param[in] N/A CNcomment: �� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

extern HI_S32 HI_UNF_PQ_DeInit(HI_VOID);

/**
 \brief ��ȡ����
 \attention \n
��
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] pu32Brightness������ֵ,��Ч��Χ: 0~100;
 \param[out] 

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_GetBrightness(HI_UNF_DISP_E enChan, HI_U32 *pu32Brightness);

/**
 \brief ��������
 \attention \n
��
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] u32Brightness������ֵ,��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_SetBrightness(HI_UNF_DISP_E enChan, HI_U32 u32Brightness);

/**
 \brief ��ȡ�Աȶ�
 \attention \n
��

 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] pu32Contrast���Աȶ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_GetContrast(HI_UNF_DISP_E enChan, HI_U32 *pu32Contrast);

/**
 \brief ���öԱȶ�
 \attention \n
��
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] u32Contrast���Աȶ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_SetContrast(HI_UNF_DISP_E enChan, HI_U32 u32Contrast);

/**
 \brief ��ȡ���Ͷ�
 \attention \n
��
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] pu32Saturation�����Ͷ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_GetSaturation(HI_UNF_DISP_E enChan, HI_U32 *pu32Saturation);

/**
 \brief ���ñ��Ͷ�
 \attention \n
��
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] u32Saturation�����Ͷ�,��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_SetSaturation(HI_UNF_DISP_E enChan, HI_U32 u32Saturation);

/**
 \brief ��ȡɫ��
 \attention \n
��

 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] pu32Hue��ɫ��, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_GetHue(HI_UNF_DISP_E enChan, HI_U32 *pu32Hue);

/**
 \brief ����ɫ��
 \attention \n
��
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] u32Hue��ɫ��, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_SetHue(HI_UNF_DISP_E enChan, HI_U32 u32Hue);



/**
 \brief ��ȡSR��ʾ����
 \attention \n
��
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] *penType


 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_GetSRMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_SR_DEMO_E *penType);

/**
 \brief ����SR��ʾ����
 \attention \n
��
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] enType

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_SetSRMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_SR_DEMO_E enType);

/**
 \brief ��ȡ������
 \attention \n
��
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] pu32Sharpness��������, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_GetSharpness(HI_UNF_DISP_E enChan, HI_U32 *pu32Sharpness);

/**
 \brief ����������
 \attention \n
��
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] u32Sharpness��������, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_SetSharpness(HI_UNF_DISP_E enChan, HI_U32 u32Sharpness);



/**
 \brief ��ȡ��ɫ��ǿ
 \attention \n
��
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] pu32ColorGainLevel

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_GetColorGain(HI_UNF_DISP_E enChan, HI_U32 *pu32ColorGainLevel);

/**
 \brief ������ɫ��ǿ
 \attention \n
��
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] u32ColorGainLevel����Χ0-100

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_SetColorGain(HI_UNF_DISP_E enChan, HI_U32 u32ColorGainLevel);


/**
 \brief ��ȡ��ɫ��ǿ�����ͺ�ǿ��
 \attention \n
��

 \param[out] pstColorEnhanceParam:��ɫ��ǿ�����ͺ�ǿ��;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_GetColorEnhanceParam(HI_UNF_PQ_COLOR_ENHANCE_S *pstColorEnhanceParam); 

/**
 \brief ������ɫ��ǿ�����ͺ�ǿ��
 \attention \n
��

 \param[out] enColorEnhanceType:��ɫ��ǿ�����ͺ�ǿ��;

 \retval ::HI_SUCCESS

 */
 
 extern HI_S32 HI_UNF_PQ_SetColorEnhanceParam(HI_UNF_PQ_COLOR_ENHANCE_S stColorEnhanceParam);  

/**
 \brief ��ȡDCI����̬�Աȶ���ǿ����ǿ�ȷ�Χ
 \attention \n
��

 \param[out] pu32DCIlevel:��̬�Աȶȵȼ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_GetDynamicContrast(HI_U32 *pu32DCIlevel); 

/**
 \brief ����DCI����̬�Աȶ���ǿ����ǿ�ȷ�Χ
 \attention \n
��

 \param[in] u32DCIlevel:��̬�Աȶȵȼ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_SetDynamicContrast(HI_U32 u32DCIlevel); 



/**
 \brief ����PQģ�鿪��
 \attention \n
  ��

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */
 
extern HI_S32 HI_UNF_PQ_SetPQModule( HI_UNF_PQ_MODULE_E enFlags, HI_U32 u32OnOff);

/**
 \brief ��ȡPQģ�鿪��
 \attention \n
  ��

 \param[in] enFlags
 \param[in] pu32OnOff

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_UNF_PQ_GetPQModule( HI_UNF_PQ_MODULE_E enFlags, HI_U32 *pu32OnOff);

/**
 \brief ��������ģʽ����
 \attention \n
��

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */
 
extern HI_S32 HI_UNF_PQ_SetDemo( HI_UNF_PQ_DEMO_E enFlags, HI_U32 u32OnOff);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /* End of #ifndef __HI_UNF_PQ_H__ */


