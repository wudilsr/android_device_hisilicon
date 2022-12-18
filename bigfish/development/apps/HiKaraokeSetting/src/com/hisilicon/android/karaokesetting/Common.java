package com.hisilicon.android.karaokesetting;

import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;

import android.R.string;
import android.app.Dialog;
import android.app.Service;
import android.app.AlertDialog;
import android.os.Binder;
import android.os.IBinder;
import android.os.Handler;
import android.os.Message;
//import android.os.SystemProperties;
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
import com.cmcc.media.Micphone;
import com.cmcc.media.RTSoundEffects;

public class Common {
    public static RTSoundEffects rtSoundEffects;
    public static Micphone micphone;

    public static RelativeLayout micphone_layout;
    public static RelativeLayout karaoke_mode_layout;
    public static RelativeLayout soundEffects_layout;

    public static TextView micphone_text;
    public static TextView soundEffects_text;
    public static TextView karaoke_mode_text;


    public static SeekBar micphone_seekbar;

    public static ImageView soundEffects_left;
    public static ImageView soundEffects_right;
    public static ImageView karaoke_mode_left;
    public static ImageView karaoke_mode_right;

    public static String[] onoff_array = null;
    public static String[] soundEffects_array = null;

    public static boolean KaraokOnOff=false;
    public static String soundEffects_type;
    public static String volume;
    public static String MIC_ONOFF;
}
