#ifndef __SVR_EXTRACTOR_INTF_H__
#define __SVR_EXTRACTOR_INTF_H__

#include "hi_type.h"
#include "hi_svr_format.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define MAX_URI_NAME_LEN    (1024)

HI_S32 SVR_EXTRACTOR_Create(HI_HANDLE *phandle);
HI_S32 SVR_EXTRACTOR_SetDataSource(HI_HANDLE handle, HI_CHAR *uri, HI_CHAR *headers);
HI_S32 SVR_EXTRACTOR_GetFileInfo(HI_HANDLE handle, HI_FORMAT_FILE_INFO_S **pstFileInfo);
HI_S32 SVR_EXTRACTOR_ReadFrame(HI_HANDLE handle, HI_FORMAT_FRAME_S *frame);
HI_S32 SVR_EXTRACTOR_Invoke(HI_HANDLE handle, HI_U32 u32InvokeId, void *pArg);
HI_S32 SVR_EXTRACTOR_Free(HI_HANDLE handle, HI_FORMAT_FRAME_S *frame);
HI_S32 SVR_EXTRACTOR_Seek(HI_HANDLE handle, HI_S64 timeMs);
HI_S32 SVR_EXTRACTOR_Delete(HI_HANDLE handle);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

