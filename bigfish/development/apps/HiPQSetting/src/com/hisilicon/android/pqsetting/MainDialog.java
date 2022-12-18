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

public class MainDialog {

    private Context mContext;

    private ListView mListView;

    private ArrayList<HashMap<String, Object>> listItem;

    private SimpleAdapter listItemAdapter;

    public MainDialog(Context m)
    {
        mContext = m;
    }
    public AlertDialog showMainDialog() {
        //create ui

        //use custom UI.
        View v = View.inflate(mContext, R.layout.main_list, null);
        initListView(v);

        AlertDialog.Builder builder = new AlertDialog.Builder(mContext,R.style.MyTranslucent);
        builder.setTitle(mContext.getString(R.string.app_name));
        builder.setView(v,0,0,0,0);
        AlertDialog dialog = builder.create();
        dialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
        // dialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_OVERLAY);
        dialog.show();

        //set dialog size and position.
        WindowManager.LayoutParams lp=dialog.getWindow().getAttributes();
        WindowManager wm=(WindowManager) mContext.getSystemService(mContext.WINDOW_SERVICE);
        Display display = wm.getDefaultDisplay();
        if (Common.isPortrait()) {
            lp.width=(int) (display.getHeight()*0.35);
            lp.height=(int) (display.getWidth()*0.45);
            lp.x=(int) (600 * display.getWidth() / display.getHeight());
            lp.y=(int) (-400 * display.getHeight() / display.getWidth());
        } else {
            lp.width=(int) (display.getWidth()*0.35);
            lp.height=(int) (display.getHeight()*0.45);
            lp.x=600;
            lp.y=-400;
        }
        lp.alpha = 0.7f;
        dialog.getWindow().setAttributes(lp);
        return dialog;
    }

    private void initListView(View v) {
        mListView = (ListView) v.findViewById(android.R.id.list);

        listItem = new ArrayList<HashMap<String, Object>>();
        listItemAdapter = new SimpleAdapter(mContext, listItem,
				R.layout.list_items,
				new String[] { "ItemTitle", "ItemStatus" }, new int[] {
					R.id.ItemTitle, R.id.ItemStatus });

        mListView.setAdapter(listItemAdapter);

        listItem.clear();

        HashMap<String, Object> temp_map1 = new HashMap<String, Object>();
        temp_map1.put("ItemTitle", mContext.getString(R.string.display_mode));
        temp_map1.put("ItemStatus", Common.display_array[Common.mPQManager.getImageMode()]);
        listItem.add(temp_map1);

        HashMap<String, Object> temp_map2 = new HashMap<String, Object>();
        temp_map2.put("ItemTitle", mContext.getString(R.string.engine_mode));
        temp_map2.put("ItemStatus", Common.onoff_split_array[Common.mPQManager.getShopMode()]);
        listItem.add(temp_map2);

        HashMap<String, Object> temp_map3 = new HashMap<String, Object>();
        temp_map3.put("ItemTitle", mContext.getString(R.string.reset));
        listItem.add(temp_map3);

        mListView.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> parent, View view,
				int position, long id) {
				if (position == 0) {
					MainService.mMainDialog.dismiss();
					MainService.mDisplayDialog = MainService.cDisplayDialog.showDisplayDialog();
                                 MainService.dialogAutoDismiss(MainService.mDisplayDialog);
					MainService.mDisplayDialog.setOnCancelListener(new OnCancelListener()
					{
						public void onCancel(DialogInterface dialog)
						{
							MainService.mMainDialog = showMainDialog();
                                               MainService.dialogAutoDismiss(MainService.mMainDialog);
                                               Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_IMAGE);
                                        }
					});
				} else if (position == 1) {
					MainService.mMainDialog.dismiss();
					MainService.mEngineDialog = MainService.cEngineDialog.showEngineDialog();
                                 MainService.dialogAutoDismiss(MainService.mEngineDialog);
					MainService.mEngineDialog.setOnCancelListener(new OnCancelListener()
					{
						public void onCancel(DialogInterface dialog)
						{
							MainService.mMainDialog = showMainDialog();
                                               MainService.dialogAutoDismiss(MainService.mMainDialog);
						}
					});
				} else if (position == 2) {
					AlertDialog.Builder mBuilder = new AlertDialog.Builder(
						mContext);

					mBuilder.setTitle(mContext.getString(R.string.reset_to_default));
					mBuilder.setMessage(mContext.getString(R.string.reset_hint));

					mBuilder.setPositiveButton(mContext.getString(R.string.ok),
							new DialogInterface.OnClickListener() {
								@Override
								public void onClick(DialogInterface dialog,
										int which) {
									Common.mPQManager.reset();
								}
							}).setNegativeButton(R.string.cancel, null);

					AlertDialog mDialog = mBuilder.create();
					mDialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
					mDialog.show();
                                  MainService.dialogAutoDismiss(mDialog);
				}
			}
		});

             mListView.setOnItemSelectedListener(new OnItemSelectedListener() {

                public void onItemSelected(AdapterView < ? > arg0, View arg1, int arg2,
                                   long arg3)
                {
                    MainService.startTime = System.currentTimeMillis();
                }

                public void onNothingSelected(AdapterView < ? > arg0) {}
              });
		((SimpleAdapter) mListView.getAdapter()).notifyDataSetChanged();
		mListView.setSelection(0);
		mListView.requestFocus();
	}
       public ListView getListView()
       {
            return mListView;
       }
}
