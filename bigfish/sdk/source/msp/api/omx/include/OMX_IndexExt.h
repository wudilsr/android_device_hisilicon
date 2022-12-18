/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OMX_IndexExt_h
#define OMX_IndexExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header shall include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully
 */
#include <OMX_Index.h>


/** Vendor extension indices.

  This enum lists the current vendor extension indices to OpenMAX IL.
 */
typedef enum OMX_INDEXEXTTYPE {

    /* Component parameters and configurations */
    OMX_IndexExtComponentStartUnused = OMX_IndexVendorStartUnused + 0x00100000,

    OMX_IndexParamResourceInfo,                     /**< reference: OMX_RESOURCE_INFO */
    OMX_IndexParamLowLatencyMode,

    /* Port parameters and configurations */
    OMX_IndexExtPortStartUnused = OMX_IndexVendorStartUnused + 0x00200000,

    /* Audio parameters and configurations */
    OMX_IndexExtAudioStartUnused = OMX_IndexVendorStartUnused + 0x00400000,

    OMX_IndexParamAudioAc3,                         /**< reference: OMX_AUDIO_PARAM_AC3TYPE */
    OMX_IndexParamAudioDts,                         /**< reference: OMX_AUDIO_PARAM_DTSTYPE */

    OMX_IndexParamAudioMp1,                         /**< reference: OMX_AUDIO_PARAM_MP1TYPE */
    OMX_IndexParamAudioMp2,                         /**< reference: OMX_AUDIO_PARAM_MP2TYPE */

    /* Image parameters and configurations */
    OMX_IndexExtImageStartUnused = OMX_IndexVendorStartUnused + 0x00500000,

    /* Video parameters and configurations */
    OMX_IndexExtVideoStartUnused = OMX_IndexVendorStartUnused + 0x00600000,

    OMX_IndexParamVideoVp6,                         /**< reference: OMX_VIDEO_PARAM_VP6TYPE */

    /* Image & Video common configurations */
    OMX_IndexExtCommonStartUnused = OMX_IndexVendorStartUnused + 0x00700000,

    OMX_IndexConfigCommonDRM,                       /**< reference: OMX_CONFIG_DRMTYPE */

    /* Other configurations */
    OMX_IndexExtOtherStartUnused = OMX_IndexVendorStartUnused + 0x00800000,

    /* Time configurations */
    OMX_IndexExtTimeStartUnused = OMX_IndexVendorStartUnused + 0x00900000,

    OMX_IndexExtMax = 0x7FFFFFFF
} OMX_INDEXEXTTYPE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_IndexExt_h */
