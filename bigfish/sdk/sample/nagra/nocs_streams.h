/**
**  @file nocs_streams.h
**
**  @brief
**    Variables related to nocs test streams.
**
**  @ingroup
**    Test
**
**  @author
**    NOCS team
**    	- Prasad Somwanshi
**
**  @version
**    Revision: 1.1
**
**   
*/
/*
** REMARK:
**    Comments in this file use special tags to allow automatic test
**    documentation generation in HTML format, using the
**    GNU-General Public Licensed Doxygen tool.
**    For more information about Doxygen, please check www.doxygen.org
*/

/** 
 * @mainpage
 *
 * @brief
 *    NOCS Test streams definition for NOCS Secure chipset
 *
 *
 *  @section hist HISTORY
 *   $Log: __________ $
 *   Revision 1.0 12.04.2012 13:39:02 Nocs team
 *   First published version
 *
 *   Revision 1.1 14.02.2013 12:12:33 Prasad Somwanshi
 *   Corrected the version of the streams for EMI 0x0001
 *   and ScrClearRef_Clear streams. Modified the 
 *   NOCS_STREAM_NAME_PARSER to support 48bit CW and 64 bit CW.
 * 
 *
 *  @section cr COPYRIGHT
 *     Copyright (c) 2011 - 2012 Nagravision SA. All rights reserved.\n
 *     NAGRA and NAGRAVISION are registered trademarks of Kudelski SA, 1033 Cheseaux,
 *     Switzerland.\n
 *     Confidential and privileged information.
 *
 *     2012  The year of creation of the source file. \n
 *
 *
 */


#ifndef NOCS_STREAMS_H
#define NOCS_STREAMS_H

/******************************************************************************/
/*                                                                            */
/*                               INCLUDE FILES                                */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                              TYPES DEFINITIONS                             */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                             GENERIC TYPES DEFINITIONS                      */
/*                                                                            */
/******************************************************************************/
/***************************   DSC/SCR  ***************************************/
#define unscrambledServiceAudioPid                         0x1112
#define unscrambledServiceVideoPid                         0x1110
#define unscrambledServicePCRPid                           0x1110
#define hostKeyScrambledServiceAudioPid                    0x1122
#define hostKeyScrambledServiceVideoPid                    0x1120
#define hostKeyScrambledServicePCRPid                      0x1120
#define hostKeyScrambledServiceECMPid                      0x1126
#define contentKeyScrambledServiceAudioPid                 0x1132
#define contentKeyScrambledServiceVideoPid                 0x1130
#define contentKeyScrambledServicePCRPid                   0x1130
#define contentKeyScrambledServiceECMPid                   0x1136
#define symmetricalContentKeyScrambledServiceAudioPid      0x1142
#define symmetricalContentKeyScrambledServiceVideoPid      0x1140
#define symmetricalContentKeyScrambledServicePCRPid        0x1140
#define symmetricalContentKeyScrambledServiceECMPid        0x1146

#define scrServiceAudioPid                                 0x1112
#define scrServiceVideoPid                                 0x1110
#define scrServicePCRPid                                   0x1110

#define NAGRA_EVEN_TABLE_ID        												 0x80
#define NAGRA_ODD_TABLE_ID         												 0x81

struct SCertificationEcm1
{
 	TCsdUnsignedInt8 table_id;
	TCsdUnsignedInt8 reserved [6];
	TCsdUnsignedInt8 control_word_1 [8];
	TCsdUnsignedInt8 control_word_2 [8];
	TCsdUnsignedInt8 control_word_1_index;
	TCsdUnsignedInt8 control_word_2_index;
  TCsdUnsignedInt8 cken_flag_1;
  TCsdUnsignedInt8 cken_flag_2;
	TCsdUnsignedInt8 crc32 [4];

};

struct SCertificationEcm2
{
 	TCsdUnsignedInt8 table_id;
	TCsdUnsignedInt8 reserved [6];
	TCsdUnsignedInt8 control_word_1 [16];
	TCsdUnsignedInt8 control_word_2 [16];
	TCsdUnsignedInt8 control_word_1_index;
	TCsdUnsignedInt8 control_word_2_index;
  TCsdUnsignedInt8 cken_flag_1;
  TCsdUnsignedInt8 cken_flag_2;
	TCsdUnsignedInt8 crc32 [4];

};

/**
 *  @brief
 *    Stream Name Parser to determine correct stream name as per the 
 * 		Stream Type, Tuner, EMI.
 *
 *  If the Stream Type is DSC then all the DSC EMIs are applicable
 *  If the Stream Type is SCR then all the SCR EMIs are applicable
 *  If the Tuner Type is none of Cable, Satellite or Terrestrial,
 *  xCWEntropy parameter is only applicable for DVB-CSA2 stream which
 *  selects the Entropy of the Control Word (48 bits or 64 bits)
 *  then the streams for cable are applicable
*/

#define NOCS_STREAM_NAME_PARSER(StreamType, TunerType, xEmi, xStreamName, xCWEntropy) \
	if (strcmp("DSC", StreamType) == 0)\
	{\
		if ( strcmp("Cable", TunerType) == 0)\
		{\
			if (xEmi == 0x0000) \
			{\
				if (xCWEntropy == 48) \
				{\
					xStreamName = "NoPCDC_DSC_Emi0x0000_01.02.ts";\
				}\
				else if (xCWEntropy == 64) \
				{\
					xStreamName = "NoPCDC_DSC_Emi0x0000-64bitsCW_01.01.ts";\
				}\
			}\
			else if ( xEmi == 0x0001 )\
			{\
				xStreamName = "NoPCD3_DSC_Emi0x0001_01.02.ts";\
			}\
			else if ( xEmi == 0x0020 )\
			{\
				xStreamName = "NoPCDA_DSC_Emi0x0020_01.01.ts";\
			}\
			else if ( xEmi == 0x0021 )\
			{\
				xStreamName = "NoPCDA_DSC_Emi0x0021_01.01.ts";\
			}\
			else if ( xEmi == 0x0022 )\
			{\
				xStreamName = "NoPCDA_DSC_Emi0x0022_01.00.ts";\
			}\
			else if ( xEmi == 0x0040 )\
			{\
				xStreamName = "NoPCDT_DSC_Emi0x0040_01.00.ts";\
			}\
				else if ( xEmi == 0x0041 )\
			{\
				xStreamName = "NoPCDT_DSC_Emi0x0041_01.00.ts";\
			}\
		}\
		else if ( strcmp("Satellite", TunerType) == 0 )\
		{\
			if (xEmi == 0x0000) \
			{\
				if (xCWEntropy == 48) \
				{\
					xStreamName = "NoPSDC_DSC_Emi0x0000_01.02.ts";\
				}\
				else if (xCWEntropy == 64) \
				{\
					xStreamName = "NoPSDC_DSC_Emi0x0000-64bitsCW_01.01.ts";\
				}\
			}\
			else if ( xEmi == 0x0001 )\
			{\
				xStreamName = "NoPSD3_DSC_Emi0x0001_01.02.ts";\
			}\
			else if ( xEmi == 0x0020 )\
			{\
				xStreamName = "NoPSDA_DSC_Emi0x0020_01.01.ts";\
			}\
			else if ( xEmi == 0x0021 )\
			{\
				xStreamName = "NoPSDA_DSC_Emi0x0021_01.01.ts";\
			}\
			else if ( xEmi == 0x0022 )\
			{\
				xStreamName = "NoPSDA_DSC_Emi0x0022_01.00.ts";\
			}\
			else if ( xEmi == 0x0040 )\
			{\
				xStreamName = "NoPSDT_DSC_Emi0x0040_01.00.ts";\
			}\
				else if ( xEmi == 0x0041 )\
			{\
				xStreamName = "NoPSDT_DSC_Emi0x0041_01.00.ts";\
			}\
		}\
		else if ( strcmp("Terrestrial", TunerType) == 0 )\
		{\
			if (xEmi == 0x0000) \
			{\
				if (xCWEntropy == 48) \
				{\
					xStreamName = "NoPTDC_DSC_Emi0x0000_01.02.ts";\
				}\
				else if (xCWEntropy == 64) \
				{\
					xStreamName = "NoPTDC_DSC_Emi0x0000-64bitsCW_01.01.ts";\
				}\
			}\
			else if ( xEmi == 0x0001 )\
			{\
				xStreamName = "NoPTD3_DSC_Emi0x0001_01.02.ts";\
			}\
			else if ( xEmi == 0x0020 )\
			{\
				xStreamName = "NoPTDA_DSC_Emi0x0020_01.01.ts";\
			}\
			else if ( xEmi == 0x0021 )\
			{\
				xStreamName = "NoPTDA_DSC_Emi0x0021_01.01.ts";\
			}\
			else if ( xEmi == 0x0022 )\
			{\
				xStreamName = "NoPTDA_DSC_Emi0x0022_01.00.ts";\
			}\
			else if ( xEmi == 0x0040 )\
			{\
				xStreamName = "NoPTDT_DSC_Emi0x0040_01.00.ts";\
			}\
				else if ( xEmi == 0x0041 )\
			{\
				xStreamName = "NoPTDT_DSC_Emi0x0041_01.00.ts";\
			}\
		}\
		else \
		{\
			if (xEmi == 0x0000) \
			{\
				if (xCWEntropy == 48) \
				{\
					xStreamName = "NoPCDC_DSC_Emi0x0000_01.02.ts";\
				}\
				else if (xCWEntropy == 64) \
				{\
					xStreamName = "NoPCDC_DSC_Emi0x0000-64bitsCW_01.01.ts";\
				}\
			}\
			else if ( xEmi == 0x0001 )\
			{\
				xStreamName = "NoPCD3_DSC_Emi0x0001_01.00.ts";\
			}\
			else if ( xEmi == 0x0020 )\
			{\
				xStreamName = "NoPCDA_DSC_Emi0x0020_01.01.ts";\
			}\
			else if ( xEmi == 0x0021 )\
			{\
				xStreamName = "NoPCDA_DSC_Emi0x0021_01.01.ts";\
			}\
			else if ( xEmi == 0x0022 )\
			{\
				xStreamName = "NoPCDA_DSC_Emi0x0022_01.00.ts";\
			}\
			else if ( xEmi == 0x0040 )\
			{\
				xStreamName = "NoPCDT_DSC_Emi0x0040_01.00.ts";\
			}\
				else if ( xEmi == 0x0041 )\
			{\
				xStreamName = "NoPCDT_DSC_Emi0x0041_01.00.ts";\
			}\
		}\
	}\
	else if ( strcmp("SCR", StreamType) == 0 )\
	{\
		if (xEmi == 0x0020) \
		{\
			xStreamName = "NoPzDA_SCR_Emi0x0020_01.02.ts";\
		}\
		else if (xEmi == 0x0021) \
		{\
			xStreamName = "NoPzDA_SCR_Emi0x0021_01.02.ts";\
		}\
		else if (xEmi == 0x0022) \
		{\
			xStreamName = "NoPzDA_SCR_Emi0x0022_01.02.ts";\
		}\
		else if (xEmi == 0x0040) \
		{\
			xStreamName = "NoPzDT_SCR_Emi0x0040_01.02.ts";\
		}\
		else if (xEmi == 0x0041) \
		{\
			xStreamName = "NoPzDT_SCR_Emi0x0041_01.02.ts";\
		}\
		else if (xEmi == 0x4020) \
		{\
			xStreamName = "NoPzDA_SCR_Emi0x4020_01.01.ts";\
		}\
		else if (xEmi == 0x4021) \
		{\
			xStreamName = "NoPzDA_SCR_Emi0x4021_01.01.ts";\
		}\
		else if (xEmi == 0x4022) \
		{\
			xStreamName = "NoPzDA_SCR_Emi0x4022_01.00.ts";\
		}\
		else if (xEmi == 0x4023) \
		{\
			xStreamName = "NoPzDA_SCR_Emi0x4023_01.00.ts";\
		}\
		else if (xEmi == 0x4024) \
		{\
			xStreamName = "NoPzDA_SCR_Emi0x4024_01.00.ts";\
		}\
		else if (xEmi == 0x4040) \
		{\
			xStreamName = "NoPzDT_SCR_Emi0x4040_01.01.ts";\
		}\
		else if (xEmi == 0x4041) \
		{\
			xStreamName = "NoPzDT_SCR_Emi0x4041_01.01.ts";\
		}\
		else \
		{\
			xStreamName = "NoPzDU_ScrClearRef_Clear_01.01.ts";\
		}\
	}	

#endif /* NOCS_STREAMS_H */

/* End nocs_streams.h */                       