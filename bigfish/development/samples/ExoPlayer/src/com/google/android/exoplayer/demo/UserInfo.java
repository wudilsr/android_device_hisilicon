package com.google.android.exoplayer.demo;

import java.lang.reflect.Method;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.util.Log;

public class UserInfo {
    private static final String TAG = "UserInfo";

    public static final String USER_INFO = "userInfo";
    public static final String DISABLE_AUDIO = "disableAudio";
    public static final String SMALL_WINDOW = "smallWindow";
    public static final String TUNNELED_PLAYBACK = "tunneledPlayback";
    public static final String SECURE_PLAYBACK = "securePlayback";
    public static final String SOFTWARE_CODEC = "softwareCodec";
    public static final String ANDROID_EXTRACTOR = "androidExtractor";
    public static final String ENCODER = "encoder";

    private static final String PROP_OVERLAY = "service.media.codec.overlay";
    private static final String PROP_SAVEES = "service.media.codec.savees";
    private static final String PROP_TIME_STATS = "service.media.codec.stats";
    private static final String PROP_MEDIACODEC_LOGCAT = "service.media.codec.debug";
    private static final String PROP_ACODEC_LOGCAT = "service.media.codec.logcat";
    private static final String PROP_AUDIOTRACK_LOGCAT = "service.audio.track.debug";

    static Method systemProperties_get = null;
    static Method systemProperties_set = null;

    static private String sys_get(String key) {
        String ret;
        if (systemProperties_get == null) {
            try {
                systemProperties_get = Class.forName("android.os.SystemProperties").getMethod("get", String.class);
            } catch (Exception e) {
                Log.w(TAG, "get method android.os.SystemProperties.get() error:" + e);
                return null;
            }
        }

        try {
            if ((ret = (String) systemProperties_get.invoke(null, key)) != null)
                return ret;
        } catch (Exception e) {
            Log.w(TAG, "invoke method android.os.SystemProperties.get() error:" + e);
            return null;
        }

        return "";
    }

    static private int sys_set(String key, String value) {
        int ret = -1;
        if (systemProperties_set == null) {
            try {
                systemProperties_set = Class.forName("android.os.SystemProperties").getMethod("set", String.class, String.class);
            } catch (Exception e) {
                Log.w(TAG, "get method android.os.SystemProperties.set() error:" + e);
                return ret;
            }
        }

        if (systemProperties_set != null) {
            try {
                systemProperties_set.invoke(null, key,value);
            } catch (Exception e) {
                Log.w(TAG, "invoke method android.os.SystemProperties.set() error:" + e);
                return ret;
            }
        }

        return 0;
    }

    public static boolean getDiableAudio(Context context) {
        boolean disableAudio = false;
        if (context == null) {
            return disableAudio;
        }

        SharedPreferences userInfo = context.getSharedPreferences(UserInfo.USER_INFO, Context.MODE_PRIVATE);
        disableAudio = userInfo.getBoolean(UserInfo.DISABLE_AUDIO, false);
        Log.d(TAG, "Disable audio: " + disableAudio);
        return disableAudio;
    }

    public static void setDiableAudio(Context context, boolean disable) {
        if (disable) {
            Log.d(TAG, "Will disable audio, and not create audio codec");
        }
        if (context == null) return;

        SharedPreferences userInfo = context.getSharedPreferences(UserInfo.USER_INFO, Context.MODE_PRIVATE);
        boolean disableAudio = userInfo.getBoolean(UserInfo.DISABLE_AUDIO, false);
        if (disableAudio != disable) {
            Editor editor = userInfo.edit();
            editor.putBoolean(UserInfo.DISABLE_AUDIO, disable);
            editor.commit();
        }
    }

    public static boolean getResizeWindow(Context context) {
        boolean smallWindow = false;
        if (context == null) {
            return smallWindow;
        }

        SharedPreferences userInfo = context.getSharedPreferences(UserInfo.USER_INFO, Context.MODE_PRIVATE);
        smallWindow = userInfo.getBoolean(UserInfo.SMALL_WINDOW, false);
        Log.d(TAG, "Resize window: " + smallWindow);
        return smallWindow;
    }

    public static void setResizeWindow(Context context, boolean small) {
        if (small) {
            Log.d(TAG, "Will resize window after 5 seconds playing");
        }
        if (context == null) return;

        SharedPreferences userInfo = context.getSharedPreferences(UserInfo.USER_INFO, Context.MODE_PRIVATE);
        boolean smallWindow = userInfo.getBoolean(UserInfo.SMALL_WINDOW, false);
        if (smallWindow != small) {
            Editor editor = userInfo.edit();
            editor.putBoolean(UserInfo.SMALL_WINDOW, small);
            editor.commit();
        }
    }

    public static boolean getTunneledPlayback(Context context) {
        boolean tunneled = false;
        if (context == null) {
            return tunneled;
        }

        SharedPreferences userInfo = context.getSharedPreferences(UserInfo.USER_INFO, Context.MODE_PRIVATE);
        tunneled = userInfo.getBoolean(UserInfo.TUNNELED_PLAYBACK, false);
        Log.d(TAG, "Tunneled-Playback: " + tunneled);
        return tunneled;
    }

    public static void setTunneledPlayback(Context context, boolean tunneled) {
        if (tunneled) {
            Log.d(TAG, "Will use Tunneled-Playback");
        }
        if (context == null) return;

        SharedPreferences userInfo = context.getSharedPreferences(UserInfo.USER_INFO, Context.MODE_PRIVATE);
        boolean tunneledPlayback = userInfo.getBoolean(UserInfo.TUNNELED_PLAYBACK, false);
        if (tunneledPlayback != tunneled) {
            Editor editor = userInfo.edit();
            editor.putBoolean(UserInfo.TUNNELED_PLAYBACK, tunneled);
            editor.commit();
        }
    }

    public static boolean getSecurePlayback(Context context) {
        boolean secure = false;
        if (context == null) {
            return secure;
        }

        SharedPreferences userInfo = context.getSharedPreferences(UserInfo.USER_INFO, Context.MODE_PRIVATE);
        secure = userInfo.getBoolean(UserInfo.SECURE_PLAYBACK, false);
        Log.d(TAG, "Secure-Playback: " + secure);
        return secure;
    }

    public static void setSecurePlayback(Context context, boolean secure) {
        if (secure) {
            Log.d(TAG, "File/Http/HLS urls will use Secure-Playback");
        }
        if (context == null) return;

        SharedPreferences userInfo = context.getSharedPreferences(UserInfo.USER_INFO, Context.MODE_PRIVATE);
        boolean securePlayback = userInfo.getBoolean(UserInfo.SECURE_PLAYBACK, false);
        if (securePlayback != secure) {
            Editor editor = userInfo.edit();
            editor.putBoolean(UserInfo.SECURE_PLAYBACK, secure);
            editor.commit();
        }
    }

    public static boolean isTrustedVideoPath() {
        if (sys_get("ro.drm.tee").equals("true")) {
            return true;
        }
        return false;
    }
    
    public static boolean getOverlay() {
        if (sys_get(PROP_OVERLAY).equals("false")) {
            return false;
        }
        return true;
    }

    public static void setOverlay(boolean overlay) {
        int ret = -1;
        if (overlay) {
            ret = sys_set(PROP_OVERLAY, "true");
        } else {
            ret = sys_set(PROP_OVERLAY, "false");
        }
        if (ret != -1) {
            Log.d(TAG, "setprop " + PROP_OVERLAY  + " " + sys_get(PROP_OVERLAY));
        }
    }

    public static boolean getSoftwareCodec(Context context) {
        boolean software = false;
        if (context == null) {
            return software;
        }

        SharedPreferences userInfo = context.getSharedPreferences(UserInfo.USER_INFO, Context.MODE_PRIVATE);
        software = userInfo.getBoolean(UserInfo.SOFTWARE_CODEC, false);
        Log.d(TAG, "Software codec: " + software);
        return software;
    }

    public static void setSoftwareCodec(Context context, boolean soft) {
        if (soft) {
            Log.d(TAG, "Will use Software Codec");
        }
        if (context == null) return;

        SharedPreferences userInfo = context.getSharedPreferences(UserInfo.USER_INFO, Context.MODE_PRIVATE);
        boolean softwareCodec = userInfo.getBoolean(UserInfo.SOFTWARE_CODEC, false);
        if (softwareCodec != soft) {
            Editor editor = userInfo.edit();
            editor.putBoolean(UserInfo.SOFTWARE_CODEC, soft);
            editor.commit();
        }
    }

    public static boolean getSaveES() {
        if (sys_get(PROP_SAVEES).equals("true")) {
            return true;
        }
        return false;
    }

    public static void setSaveES(boolean save) {
        int ret = -1;
        if (save) {
            ret = sys_set(PROP_SAVEES, "true");
        } else {
            ret = sys_set(PROP_SAVEES, "false");
        }
        if (ret != -1) {
            Log.d(TAG, "setprop " + PROP_SAVEES  + " " + sys_get(PROP_SAVEES));
        }
    }

    public static boolean getTimeStats() {
        if (sys_get(PROP_TIME_STATS).equals("true")) {
            return true;
        }
        return false;
    }

    public static void setTimeStats(boolean enable) {
        int ret = -1;
        if (enable) {
            ret = sys_set(PROP_TIME_STATS, "true");
        } else {
            ret = sys_set(PROP_TIME_STATS, "false");
        }
        if (ret != -1) {
            Log.d(TAG, "setprop " + PROP_TIME_STATS  + " " + sys_get(PROP_TIME_STATS));
        }
    }

    public static boolean getMediaCodecLogcat() {
        if (sys_get(PROP_MEDIACODEC_LOGCAT).equals("true")) {
            return true;
        }
        return false;
    }

    public static void setMediaCodecLogcat(boolean enable) {
        int ret = -1;
        if (enable) {
            ret = sys_set(PROP_MEDIACODEC_LOGCAT, "true");
        } else {
            ret = sys_set(PROP_MEDIACODEC_LOGCAT, "false");
        }
        if (ret != -1) {
            Log.d(TAG, "setprop " + PROP_MEDIACODEC_LOGCAT  + " " + sys_get(PROP_MEDIACODEC_LOGCAT));
        }
    }


    public static boolean getACodecLogcat() {
        if (sys_get(PROP_ACODEC_LOGCAT).equals("true")) {
            return true;
        }
        return false;
    }

    public static void setACodecLogcat(boolean enable) {
        int ret = -1;
        if (enable) {
            ret = sys_set(PROP_ACODEC_LOGCAT, "true");
        } else {
            ret = sys_set(PROP_ACODEC_LOGCAT, "false");
        }
        if (ret != -1) {
            Log.d(TAG, "setprop " + PROP_ACODEC_LOGCAT  + " " + sys_get(PROP_ACODEC_LOGCAT));
        }
    }

    public static boolean getAudioTrackLogcat() {
        if (sys_get(PROP_AUDIOTRACK_LOGCAT).equals("true")) {
            return true;
        }
        return false;
    }

    public static void setAudioTrackLogcat(boolean enable) {
        int ret = -1;
        if (enable) {
            ret = sys_set(PROP_AUDIOTRACK_LOGCAT, "true");
        } else {
            ret = sys_set(PROP_AUDIOTRACK_LOGCAT, "false");
        }
        if (ret != -1) {
            Log.d(TAG, "setprop " + PROP_AUDIOTRACK_LOGCAT  + " " + sys_get(PROP_AUDIOTRACK_LOGCAT));
        }
    }

    public static boolean getAndroidExtractor(Context context) {
        boolean androidExtractor = false;
        if (context == null) {
            return androidExtractor;
        }

        SharedPreferences userInfo = context.getSharedPreferences(UserInfo.USER_INFO, Context.MODE_PRIVATE);
        androidExtractor = userInfo.getBoolean(UserInfo.ANDROID_EXTRACTOR, false);
        Log.d(TAG, "android.media.MediaExtractor: " + androidExtractor);
        return androidExtractor;
    }

    public static void setAndroidExtractor(Context context, boolean enable) {
        if (enable) {
            Log.d(TAG, "Will use android.media.MediaExtractor");
        }
        if (context == null) return;

        SharedPreferences userInfo = context.getSharedPreferences(UserInfo.USER_INFO, Context.MODE_PRIVATE);
        boolean androidExtractor = userInfo.getBoolean(UserInfo.ANDROID_EXTRACTOR, false);
        if (androidExtractor != enable) {
            Editor editor = userInfo.edit();
            editor.putBoolean(UserInfo.ANDROID_EXTRACTOR, enable);
            editor.commit();
        }
    }

}
