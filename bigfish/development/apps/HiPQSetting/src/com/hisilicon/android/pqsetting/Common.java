package com.hisilicon.android.pqsetting;

import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;

import android.app.Dialog;
import android.app.Service;
import android.app.AlertDialog;
import android.os.Binder;
import android.os.IBinder;
import android.os.Handler;
import android.os.Message;
import android.os.SystemProperties;
import android.content.Intent;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;
import android.view.WindowManager;
import android.view.View;
import android.view.Display;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View.OnKeyListener;
import android.view.View.OnClickListener;
import android.util.Log;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.SimpleAdapter;
import android.widget.RelativeLayout;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemSelectedListener;
import android.graphics.Typeface;

import com.hisilicon.android.PQManager;

public class Common {

    public static PQManager mPQManager;
    // display_mode
    public static RelativeLayout display_layout;
    public static RelativeLayout brightness_layout;
    public static RelativeLayout contrast_layout;
    public static RelativeLayout hue_layout;
    public static RelativeLayout saturation_layout;

    public static TextView display_text;
    public static TextView brightness_text;
    public static TextView contrast_text;
    public static TextView hue_text;
    public static TextView saturation_text;

    public static TextView display_info;
    public static TextView brightness_info;
    public static TextView contrast_info;
    public static TextView hue_info;
    public static TextView saturation_info;

    public static SeekBar brightness_seekbar;
    public static SeekBar contrast_seekbar;
    public static SeekBar hue_seekbar;
    public static SeekBar saturation_seekbar;

    public static ImageView display_left;
    public static ImageView display_right;

    // engine_mode
    public static RelativeLayout engine_layout;
    public static RelativeLayout smart_color_layout;
    public static RelativeLayout dynamic_contrast_layout;
    public static RelativeLayout sharpness_layout;
    public static RelativeLayout super_resolution_layout;

    public static TextView engine_text;
    public static TextView smart_color_text;
    public static TextView dynamic_contrast_text;
    public static TextView sharpness_text;
    public static TextView super_resolution_text;

    public static SeekBar sharpness_seekbar;

    public static ImageView engine_left;
    public static ImageView engine_right;
    public static ImageView smart_left;
    public static ImageView smart_right;
    public static ImageView contrast_left;
    public static ImageView contrast_right;
    public static ImageView super_left;
    public static ImageView super_right;

    // color_mode
    public static RelativeLayout color_layout;
    public static RelativeLayout red_layout;
    public static RelativeLayout green_layout;
    public static RelativeLayout blue_layout;
    public static RelativeLayout cyan_layout;
    public static RelativeLayout violet_layout;
    public static RelativeLayout yellow_layout;

    public static TextView color_text;
    public static TextView red_text;
    public static TextView green_text;
    public static TextView blue_text;
    public static TextView cyan_text;
    public static TextView violet_text;
    public static TextView yellow_text;

    public static TextView color_info;
    public static TextView red_info;
    public static TextView green_info;
    public static TextView blue_info;
    public static TextView cyan_info;
    public static TextView violet_info;
    public static TextView yellow_info;

    public static SeekBar red_seekbar;
    public static SeekBar green_seekbar;
    public static SeekBar blue_seekbar;
    public static SeekBar cyan_seekbar;
    public static SeekBar violet_seekbar;
    public static SeekBar yellow_seekbar;

    public static ImageView color_left;
    public static ImageView color_right;

    public static String[] display_array = null;
    public static String[] onoff_array = null;
    public static String[] onoff_split_array = null;
    public static String[] smart_color_array = null;
    public static String[] dynamic_contrast_array = null;

    public static boolean isPortrait() {
        String screenOrientation = SystemProperties.get("persist.sys.screenorientation");
        if (screenOrientation != null) {
            if ("portrait".equals(screenOrientation)) {
                return true;
            }
        }
        return false;
    }
}
