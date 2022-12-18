package com.android.hisiliconsetting;

import android.app.ProgressDialog;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.Window;
import android.view.WindowManager.LayoutParams;
import android.widget.TextView;

public class ProDialog extends ProgressDialog{
    private View load;
    private TextView msgtext;
    public ProDialog(Context context) {
        super(context);
    }
    public ProDialog(Context context,int them){
        super(context, them);
        load = LayoutInflater.from(context).inflate(R.layout.loadmore, null);
        msgtext = (TextView)load.findViewById(R.id.load_msg);
    }
    public void SetLocation(int x,int y){
        Window win = this.getWindow();
        LayoutParams params = new LayoutParams();
        if(x!=0)
        params.x = x;
        if(y!=0)
        params.y = y;
        win.setAttributes(params);
    }
    public void SetCancleAble(boolean isable){
        if(!isable){
        this.setCancelable(false);
        }
    }
    public void SetShowMsg(String msg){
        msgtext.setText(msg);
    }
    public void SetTextColor(int colorid){
        msgtext.setTextColor(colorid);
    }
    public void Show(){
        this.show();
        this.setContentView(load);
    }
    public void Dismiss(){
        this.dismiss();
    }

}
