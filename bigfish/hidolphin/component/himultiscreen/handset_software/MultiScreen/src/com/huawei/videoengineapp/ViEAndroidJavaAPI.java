/*
 *  Copyright (c) 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

package com.huawei.videoengineapp;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import android.content.Context;
import android.os.Build;
import android.util.Log;

public class ViEAndroidJavaAPI {

    private static final String LOG_TAG = "hme-video";

    private static boolean getNeon() {
        boolean neon = false;
        FileReader fr = null;
        BufferedReader br = null;
        try {
        fr = new FileReader("/proc/cpuinfo");
        br = new BufferedReader(fr, 1024);
        String line = null;
        while ((line = br.readLine()) != null) {
        line = line.toLowerCase();
        if (line.contains("neon") && line.contains("features")) {
        neon = true;
        }
        }
        } catch (IOException ex) {
        ex.printStackTrace();
        } finally {
        if (br != null) {
        try {
        br.close();
        } catch (IOException e) {
        e.printStackTrace();
        }
        br = null;
        }

        if (fr != null) {
        try {
        fr.close();
        } catch (IOException e) {
        }
        fr = null;
        }
        }

        Log.d("getNeon", "neon:" + neon);
        return neon;
    }

    public ViEAndroidJavaAPI(Context context) {
        // Log.d(LOG_TAG, "Loading libHME_Video_H264D.so...");
        // System.loadLibrary("HME_Video_H264D");

        // Log.d(LOG_TAG, "Loading libHME_Video_H264E.so...");
        // System.loadLibrary("HME_Video_H264E");

        // �ж��Ƿ�֧��V7
        if (Build.CPU_ABI.contains("armeabi-v7a")) {
        Log.i("HME_DEMO", "---------------armeabi-v7a :" + Build.CPU_ABI);
        Log.d(LOG_TAG, "android version:" + Build.VERSION.SDK_INT);
        // �ж��Ƿ�֧��NEONָ��
        if (getNeon())// ����V7��
        {
        Log.d(LOG_TAG, "Loading libHME-Video.so...");
        System.loadLibrary("HME-Video");
        Log.d(LOG_TAG, "Loading libHME_VideoEngine_jni.so...");
        System.loadLibrary("HME_VideoEngine_jni");
        } else // ����V6��
        {
        Log.d(LOG_TAG, "Loading libHME-Video-v6.so...");
        System.loadLibrary("HME-Video-v6");
        Log.d(LOG_TAG, "Loading libHME_VideoEngine_jni-v6.so...");
        System.loadLibrary("HME_VideoEngine_jni-v6");
        }
        } else // ����V6��
        {
        Log.d(LOG_TAG, "Loading libHME-Video-v6.so...");
        System.loadLibrary("HME-Video-v6");
        Log.d(LOG_TAG, "Loading libHME_VideoEngine_jni-v6.so...");
        System.loadLibrary("HME_VideoEngine_jni-v6");
        }

        String a = "";
        a.getBytes();
    }

    public static boolean enableVideoSend = true;
    public static boolean enableVideoReceive = true;
    // Engine params
    public static int logLevel = 0; // 0-NONE 1-API 2-ERROR 3-IO 4-ALL

    public static int eRtpType = 1; // 0-SINGLE 1-SINGLE_FU 2-SINGLE_FU_STAP
    public static int eProfile = 0;
    // _HME_V_ENC_PARAMS
    public static int eCodecType = 0; // ���� 0-H264_SW 1-H264_HW 2-H263_SW
        // 3-SVC_SW
    public static int uiPayloadType = 122;
    public static int uiEncQuality = 0;
    public static int uiKeyInterval = 2000;  //150
    public static int uiWidth = 320; //1280; // 320;
    public static int uiHeight = 240; //720; // 240;
    public static int fFrameRate = 15; //30; // 15;
    public static int eRCType = 0;
    public static int uiBitRate = 256; //2000; // 256;
    public static int uiSendBitRate = 300; //2000; // 300;
    public static int uiMaxPktLen = 1500;
    public static int eAntiPktLoss = 3; // FEC 0-NONE 1-FEC 2-STND 3-RS 4-ARQ
    // HME_V_ARS_PARAMS
    public static boolean bCtrlResolution = true; //false; // true;
    public static boolean bCtrlFec = true; //false; // true;
    public static int uiMaxBitRate = 2500; //2500; // 640;
    public static int uiMaxFrameRate = 30; //60; // 20;
    public static int uiMinFrameRate = 1;
    // HME_V_SEND_PARAMS
    public static String szLocalIP = "127.0.0.1";
    public static int uiLocalPort = 11111;
    public static String szRemoteIP = "127.0.0.1";
    public static int uiRemotePort = 11111;
    // HME_V_RTCP_PARAMS
    public static int eRtcpType = 1;
    // HME_V_SRTP_PARAMS
    public static boolean eCipherType = false;
    // HME_V_PRIVATE_FEC_PARAMS
    public static int uiFecPktPT = 97;
    public static int uiRedPktPT = 96;
    // HME_V_FEC_PARAMS
    public static int uiLossRate = 0;
    public static boolean bMultiFrm = false;

    public static boolean bDenoise = false;
    public static boolean bColorEnhance = false;
    // Decoder params
    // HME_V_DEC_PARAMS
    public static int eDecCodecType = 0; // ���� 0-H264_SW 1-H264_HW 2-H263_SW
        // 3-SVC_SW
    // Render params
    // HME_V_RENDER_PARAMS
    public static int eDisplayMode = 1;
    public static int eRotateAngle = 0;
    public static boolean bMirrorYAxis = false;

    // Statistic params
    public static int EncStatisticParams_uiImageWidth;
    public static int EncStatisticParams_uiImageHeight;
    public static int EncStatisticParams_uiEncFrameRate;
    public static int EncStatisticParams_uiEncBitRate;
    public static int EncStatisticParams_uiPktRate;
    public static int EncStatisticParams_uiSendBitRate;
    public static int EncStatisticParams_fKeyRedundanceRate;
    public static int EncStatisticParams_fRefRedundanceRate;
    public static int EncStatisticParams_fNoRefRedundanceRate;
    public static int EncStatisticParams_uiBufferData;

    public static int DecStatisticParams_uiImageWidth;
    public static int DecStatisticParams_uiImageHeight;
    public static int DecStatisticParams_uiBitRate;
    public static int DecStatisticParams_uiPktRate;

    public static int stCaptureCapability_uiImageWidth;
    public static int stCaptureCapability_uiImageHeight;
    public static int stCaptureCapability_uiMaxFps;
    public static int stCaptureCapability_eVideoRawType;
    public static int stCaptureCapability_eVideoCodecType;

    // API Native
    private native boolean NativeInit(Context context);

    // Video Engine API
    // Initialization and Termination functions
    public native int Init(int logLevel);

    public native int Terminate();

    /*********** ��ȡ���� *****************************/
    public native int[] QueryCPUConsume(int[] cpu);

    public native int GetEncChannelStatistics();

    public native int GetDecoderChannelStatistics();

    public native int GetRenderSnapshot();

    /************************************************/

    public native int StartSend();

    public native int getCaptureShot();

    public native int StopSend();

    public native int SetRotationAPI();

    public native int SwitchCapture();

    public native int ResetStream();

    public native int SetupStream();

    public native int StartReceive(Object glSurface);

    public native int StopReceive();

    // Receiver & Destination functions
    public native int SetLocalReceiver(int port, byte ipadr[]);

    public native int SetSendDestination(int port, byte ipadr[]);

    // Codec
    public native int SetReceiveCodec(int intbitRate, int width, int height, int frameRate,
        boolean enableSrtp);

    public native int SetSendCodec(int frameRate, boolean enableSrtp);

    public native int SetHook(int valueHook);

    // Capture
    public native int StartCamera(int cameraNum);

    public native int GetCameraOrientation(int cameraNum);

    public native int SetRotation(int degrees);

    /* Start: Added by Changwenliang+202247 2012/4/5 */
    public native String getVersion();

}
