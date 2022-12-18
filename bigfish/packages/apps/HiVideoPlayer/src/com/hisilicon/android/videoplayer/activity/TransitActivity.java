package com.hisilicon.android.videoplayer.activity;

import com.hisilicon.android.videoplayer.R;
import com.hisilicon.android.videoplayer.util.Constants;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;



public class TransitActivity extends Activity {
       protected void onCreate(Bundle savedInstanceState) {
               super.onCreate(savedInstanceState);
               Log.i("TransitActivity","onCreate");
               Intent service = new Intent();
               service.setClassName("com.hisilicon.android.videoplayer","com.hisilicon.android.videoplayer.activity.MediaFileListService");
               service.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
               service.setData(getIntent().getData());
               String path = getIntent().getData().getPath();
               String dex = path.substring(path.lastIndexOf(".") + 1, path.length());
               dex = dex.toUpperCase();
               if(dex != null && dex.equals("ISO"))
               {
                    service.setDataAndType(getIntent().getData(), "video/iso");
               }
               else
                    service.setDataAndType(getIntent().getData(), getIntent().getType());
               service.putExtra("sortCount", getIntent().getIntExtra("sortCount",-1));
               startService(service);
               TransitActivity.this.finish();
       }

}
