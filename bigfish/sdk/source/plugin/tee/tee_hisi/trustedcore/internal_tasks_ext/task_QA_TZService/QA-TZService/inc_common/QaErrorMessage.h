#ifndef QaErrorMessage_h__
#define QaErrorMessage_h__

#include "DxTypes.h"
#define QA_ERR_STR_SIZE 512
typedef struct _QaErrorMessage{
    DxChar mesageFormat[QA_ERR_STR_SIZE];
    DxChar file[QA_ERR_STR_SIZE];
    DxChar funcName[QA_ERR_STR_SIZE];
    DxUint32 line;
    DxUint32 param1;
    DxUint32 param2;
    DxUint32 param3;
} QaErrorMessage;

#endif // QaErrorMessage_h__

