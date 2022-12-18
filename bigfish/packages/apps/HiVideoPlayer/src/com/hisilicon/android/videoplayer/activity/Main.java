package com.hisilicon.android.videoplayer.activity;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.ContentResolver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.DialogInterface.OnClickListener;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.SystemProperties;
import android.provider.MediaStore;
import android.provider.MediaStore.Video;
import android.text.TextUtils.TruncateAt;
import android.text.method.SingleLineTransformationMethod;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.View.OnFocusChangeListener;
import android.view.ViewGroup.LayoutParams;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Gallery;
import android.widget.GridView;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TableLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.android.videoplayer.R;
import com.hisilicon.android.videoplayer.activity.Main;
import com.hisilicon.android.videoplayer.activity.VideoModel;
import com.hisilicon.android.videoplayer.dao.DBOperateHelper;
import com.hisilicon.android.videoplayer.util.Common;
import com.hisilicon.android.videoplayer.util.Constants;
import com.hisilicon.android.videoplayer.util.Tools;


public class Main extends Activity
{
    private static final String TAG = "Main";
    private Context context = Main.this;

    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Log.i(TAG, "onCreate");
    }

    protected void onResume()
    {
        Log.i(TAG, "onResume()");

        super.onResume();
    }
    protected void onPause()
    {
        Log.i(TAG, "onPause()");

        super.onPause();
    }

    @Override
    protected void onDestroy()
    {
        Log.i(TAG, "onDestroy ...");

        super.onDestroy();
    }

}
