package com.explorer.common;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

import com.explorer.activity.MainExplorerActivity;
import com.explorer.common.CommonActivity;
/**
 * the default filter criteria
 */
public class FilterType {
	public static void filterType(CommonActivity ctx) {

		SharedPreferences share = ctx.getSharedPreferences("OPERATE",
				Context.MODE_WORLD_READABLE);
		Editor editor = share.edit();
		// audio criteria
		if (share.getBoolean("audioFlag", true)) {
			SharedPreferences.Editor shareAudio = ctx.getSharedPreferences(
					"AUDIO", Context.MODE_WORLD_READABLE).edit();
			shareAudio.putString("M3U", "M3U");
			shareAudio.putString("CUE", "CUE");
			shareAudio.putString("PLS", "PLS");
			shareAudio.putString("MP2", "MP2");
			shareAudio.putString("MP3", "MP3");
			shareAudio.putString("CDDA", "CDDA");
			shareAudio.putString("WMA", "WMA");
			shareAudio.putString("AAC", "AAC");
			shareAudio.putString("M4A", "M4A");
			shareAudio.putString("WAV", "WAV");
			shareAudio.putString("AIFF", "AIFF");
			shareAudio.putString("OGG", "OGG");
			shareAudio.putString("FLAC", "FLAC");
			shareAudio.putString("RA", "RA");
			shareAudio.putString("MKA", "MKA");
			shareAudio.putString("EC3", "EC3");
			shareAudio.putString("AC3", "AC3");
			shareAudio.putString("DTS", "DTS");
			shareAudio.putString("MLP", "MLP");
			shareAudio.putString("APE", "APE");
			shareAudio.putString("OGA", "OGA");
			shareAudio.putString("MID", "MID");
			shareAudio.putString("MIDI", "MIDI");
			shareAudio.putString("XMF", "XMF");
			shareAudio.putString("RTTTL", "RTTTL");
			shareAudio.putString("SMF", "SMF");
			shareAudio.putString("IMY", "IMY");
			shareAudio.putString("RTX", "RTX");
			shareAudio.putString("OTA", "OTA");
			shareAudio.putString("AMR", "AMR");
			shareAudio.putString("AWB", "AWB");

			shareAudio.putString("AEA", "AEA");
			shareAudio.putString("APC", "APC");
			shareAudio.putString("AU", "AU");
			shareAudio.putString("DAUD", "DAUD");
			shareAudio.putString("OMA", "OMA");
			shareAudio.putString("EAC3", "EAC3");
			shareAudio.putString("GSM", "GSM");
			shareAudio.putString("TRUEHD", "TRUEHD");
			shareAudio.putString("TTA", "TTA");
			shareAudio.putString("MPC", "MPC");
			shareAudio.putString("MPC8", "MPC8");

			editor.putBoolean("audioFlag", false);
			editor.commit();
			shareAudio.commit();
		}

		// video conditions
		if (share.getBoolean("videoFlag", true)) {
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

		// pictrun conditions
		if (share.getBoolean("imageFlag", true)) {
			SharedPreferences.Editor shareImage = ctx.getSharedPreferences(
					"IMAGE", Context.MODE_WORLD_READABLE).edit();
			shareImage.putString("JPG", "JPG");
			shareImage.putString("GIF", "GIF");
			shareImage.putString("BMP", "BMP");
			shareImage.putString("JPEG", "JPEG");
			shareImage.putString("TIFF", "TIFF");
			shareImage.putString("TIF", "TIF");
			shareImage.putString("PNG", "PNG");
			shareImage.putString("DNG", "DNG");
			shareImage.putString("WBMP", "WBMP");
			shareImage.putString("JFIF", "JFIF");
			shareImage.putString("JPE", "JPE");
			editor.putBoolean("imageFlag", false);
			editor.commit();
			shareImage.commit();
		}

	}
}
