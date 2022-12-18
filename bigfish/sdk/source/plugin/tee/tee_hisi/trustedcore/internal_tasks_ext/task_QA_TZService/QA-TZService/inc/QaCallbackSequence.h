#ifndef C_CALLBACK_SEQUENCE_H__
#define C_CALLBACK_SEQUENCE_H__

#include "QaTestEnumeration.h"
#include "DxTypes.h"
#include "QaTestDataStruct.h"
#include "DxTzCommon.h"





typedef struct
{
	DxChar * fileName;

	QaClbSecuenceValueArray clbSequenceArr;

	DxBool wasClbSecuenceCmdSent;

	DxUint32 sequentialNumber;

} QA_TZ_ClbSequenceData;


void ClbSequenceDataInit(void);



/**
 * Recognizes callback event by filling appropriate cell with appropriate value in global array.
 * This functiuon called from SRVX_XXXXX callbacks from Service application.
 * [in] EQaCallbackEvent callbackType - type of callback occurred.
 */
void SetClbSequenceEvent(EQaClbSecuenceIndex callbackType);


/**
 * Stores callback event data array from application memory to SFS.
 */
DxStatus WriteClbSequenceDataToSfs(void);

/**
 * Restores callback event data array from SFS in to memRefBufferPtr.
 * [out] memRefBufferPtr - regular memory buffer in which data will be read.
 */
DxStatus ReadClbSequenceDataFromSfs(DxTzServiceMemRef *memRefBufferPtr);


DxStatus DeleteClbSequenceDataFromSfs(void);

#endif

