package com.hisilicon.android.videoplayer.util;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class FilterType
{
    public static void filterType(Context ctx)
    {
        SharedPreferences share = ctx.getSharedPreferences("OPERATE",
                                                           Context.MODE_WORLD_READABLE);
        Editor editor = share.edit();

        if (share.getBoolean("videoFlag", true))
        {
            SharedPreferences.Editor shareVideo = ctx.getSharedPreferences(
                "VIDEO", Context.MODE_WORLD_READABLE).edit();
            shareVideo.putString("AVSTS", "AVSTS");
            shareVideo.putString("MTS", "MTS");
            shareVideo.putString("M2T", "M2T");
            shareVideo.putString("ISO", "ISO");
            shareVideo.putString("M2TS", "M2TS");
            shareVideo.putString("TRP", "TRP");
            shareVideo.putString("TP", "TP");
            shareVideo.putString("PS", "PS");
            shareVideo.putString("AVS", "AVS");
            shareVideo.putString("SWF", "SWF");
            shareVideo.putString("OGM", "OGM");
            shareVideo.putString("FLV", "FLV");
            shareVideo.putString("RMVB", "RMVB");
            shareVideo.putString("RM", "RM");
            shareVideo.putString("3GP", "3GP");
            shareVideo.putString("M4V", "M4V");
            shareVideo.putString("MP4", "MP4");
            shareVideo.putString("MOV", "MOV");
            shareVideo.putString("MKV", "MKV");
            shareVideo.putString("IFO", "IFO");
            shareVideo.putString("DIVX", "DIVX");
            shareVideo.putString("TS", "TS");
            shareVideo.putString("AVI", "AVI");
            shareVideo.putString("DAT", "DAT");
            shareVideo.putString("VOB", "VOB");
            shareVideo.putString("MPG", "MPG");
            shareVideo.putString("MPEG", "MPEG");
            shareVideo.putString("ASF", "ASF");
            shareVideo.putString("WMV", "WMV");
            shareVideo.putString("3GPP", "3GPP");
            shareVideo.putString("3G2", "3G2");
            shareVideo.putString("3GPP2", "3GPP2");
            shareVideo.putString("F4V", "F4V");
            shareVideo.putString("M1V", "M1V");
            shareVideo.putString("M2V", "M2V");
            shareVideo.putString("M2P", "M2P");
            shareVideo.putString("ASF", "ASF");
            shareVideo.putString("DV", "DV");
            shareVideo.putString("IFF", "IFF");
            shareVideo.putString("MJ2", "MJ2");
            shareVideo.putString("ANM", "ANM");
            shareVideo.putString("H261", "H261");
            shareVideo.putString("H263", "H263");
            shareVideo.putString("H264", "H264");
            shareVideo.putString("YUV", "YUV");
            shareVideo.putString("CIF", "CIF");
            shareVideo.putString("QCIF", "QCIF");
            shareVideo.putString("RGB", "RGB");
            shareVideo.putString("VC1", "VC1");
            shareVideo.putString("Y4M", "Y4M");
            shareVideo.putString("WEBM", "WEBM");

            editor.putBoolean("videoFlag", false);
            editor.commit();
            shareVideo.commit();
        }
    }
}
