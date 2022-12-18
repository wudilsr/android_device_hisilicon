package com.google.android.exoplayer.demo;

import java.util.HashMap;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

public class ListAdapterEncode extends BaseAdapter {
    private static final String TAG = "ListAdapterEncode";
    
    private String CPU_UNIT = " %";
    private String MEMORY_UNIT = " MB";
    
    private Context mContext;
    private HashMap<String, HashMap<String, String>> mItemList = new HashMap<String, HashMap<String, String>>();

	//public int[] ResolutionIds = {R.id.textQcif, R.id.textD1, R.id.text720p, R.id.text1080p};
	//public int[] ResolutionIds = {R.id.text720p, R.id.text1080p};
	public int[] ResolutionIds = {R.id.text720p};
    
    public String[] KeyResults = {"Score", "Frames", "Time", "Delay", "Rate", "CPU", "Memory"};
    //public String[] KeyResolutions = {"QCIF", "D1", "720P", "1080P"};
    //public String[] KeyResolutions = {"720P", "1080P"};
    public String[] KeyResolutions = {"720P"};
    
    public ListAdapterEncode(Context context) {
        mContext = context;
        
        initItemList();
    }
    
    private void initItemList() {
		for (int i = 0; i < KeyResolutions.length; i++) {
			HashMap<String, String> col = new HashMap<String, String>();
			for (int j = 0; j < KeyResults.length; j++) {
				col.put(KeyResults[j], "");
			}
			
			mItemList.put(KeyResolutions[i], col);
		}
    }
    
    public void updateItem(String resolution, String result, String value) {
//        Log.d(TAG, "update Column " + resolution + " Row " + result + " value " + value);
        HashMap<String, String> column = mItemList.get(resolution);
        column.put(result, value);

        //logItemList();
    }
    
    public void resetColumn(String resolution) {
		HashMap<String, String> column = mItemList.get(resolution);
		for (int i = 0; i < KeyResults.length; i++) {
			String result = KeyResults[i];
			String value = "0";
			if (result.equalsIgnoreCase("cpu")) {
				value += CPU_UNIT;
			} else if (result.equalsIgnoreCase("memory")) {
				value += MEMORY_UNIT;
			}
			
			column.put(KeyResults[i], value);
		}

		notifyDataSetChanged();
    }
    
    @Override
    public int getCount() {
        // TODO Auto-generated method stub
        return KeyResults.length + 1;
    }

    @Override
    public Object getItem(int position) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public long getItemId(int position) {
        // TODO Auto-generated method stub
        return position;
    }
    
    private void drawTableTitle(int position, View itemView) {
        if (position == 0) {
            TextView textResult = (TextView) itemView.findViewById(R.id.textResult);
            textResult.setText("\\");
            
            String[] resolutions = mContext.getResources().getStringArray(R.array.resolution_items);

            for (int i = 0; i < ResolutionIds.length; i++) {
                TextView textView = (TextView) itemView.findViewById(ResolutionIds[i]);
                textView.setText(resolutions[i]);
            }
        } else {
            String[] results = mContext.getResources().getStringArray(R.array.encode_results);
            
            TextView textResult = (TextView) itemView.findViewById(R.id.textResult);
            textResult.setText(results[position - 1]);
        }
    }
    
    private void drawTableCell(int position, View itemView) {
        if (position == 0) {
            // table title.
            return;
        }
        
        String result = KeyResults[position - 1];
        for (int i = 0; i < KeyResolutions.length; i++) {
            HashMap<String, String> column = mItemList.get(KeyResolutions[i]);
            String value = column.get(result);
            //Log.d(TAG, "value " + value);
            
            TextView textView = (TextView) itemView.findViewById(ResolutionIds[i]);
            textView.setText(value);
        }
    }

    private void logItemList() {
        Log.d(TAG, "log start =================================");
        for (int i = 0; i < KeyResolutions.length; i++) {
            String resolution = KeyResolutions[i];
            HashMap<String, String> column = mItemList.get(resolution);
            for (int j = 0; j < KeyResults.length; j++) {
                String result = KeyResults[j];
                String value = column.get(KeyResults[j]);
                Log.d(TAG, "log Column " + resolution + " Row " + result + " value " + value);
            }
        }
        Log.d(TAG, "log end ==================================");
    }
    
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        //Log.d(TAG, "getView position = " + position);
    
        View itemView = convertView;
        if (convertView == null) {
            //Log.d(TAG, "new view " + position);
            itemView = LayoutInflater.from(mContext).inflate(R.layout.ctrl_results_item, parent, false);
        }
//        logItemList();
        drawTableTitle(position, itemView);
        drawTableCell(position, itemView);
        
        return itemView;        
        
    }

}
