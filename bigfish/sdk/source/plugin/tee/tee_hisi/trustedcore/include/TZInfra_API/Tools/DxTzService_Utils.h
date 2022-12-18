/* File: DxTzService_Utils.h */

#ifndef	__DXTZSERVICE_UTILS_H__
#define	__DXTZSERVICE_UTILS_H__

#include "DxTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Compares 2 buffers without exposing (by timing) the mismatch index.
 * !!!Don't touch w/o consulting the technology group!!!
 * @param [in] ptr1 points the first buffer.
 * @param [in] ptr2 points the second.
 * @param [in] nBytes specifies number of compared bytes.
 *
 * @return
 *  0 - if buffers are identical.
 *  non-zero - if buffers are not identical
 */
DxUint DxTzService_IsNotMemEqualSecured (const void *p1, const void *p2, DxUint32 nBytes);
DxUint32 DxTzService_StrLen (const char* str);
DxInt DxTzService_snprintf(DxChar *buffer, DxUint32 n, DxChar *format, /*args*/ ...);

#define DxHwLogTrace(debugOnlyLog, formatStr, ...) //DxHwLogTrace_func(__FILE__, __LINE__, __FUNCTION__, debugOnlyLog, formatStr,##__VA_ARGS__)
#define DxHwLogError(debugOnlyLog, formatStr,...) //DxHwLogError_func(__FILE__, __LINE__, __FUNCTION__, debugOnlyLog, formatStr,##__VA_ARGS__)

void DxHwLogTrace_func(const DxChar *fileName, DxUint32 lineNum, const DxChar *funcName, DxBool debugOnlyLog, const DxChar *formatStr, ...);
void DxHwLogError_func(const DxChar *fileName, DxUint32 lineNum, const DxChar *funcName, DxBool debugOnlyLog, const DxChar *formatStr, ...);

#ifdef __cplusplus
}
#endif

#endif
