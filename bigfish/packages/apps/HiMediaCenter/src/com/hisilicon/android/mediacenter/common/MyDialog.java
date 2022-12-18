
package com.hisilicon.android.mediacenter.common;

import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager.LayoutParams;

/**
 * custom Dialog 
 */
public class MyDialog extends Dialog {
    int layout;

    public MyDialog(Context context, int layout) {
        super(context);
        this.layout = layout;
    }

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(layout);
        LayoutParams params = getWindow().getAttributes();
        params.width = LayoutParams.WRAP_CONTENT;
        params.height = LayoutParams.WRAP_CONTENT;
        getWindow().setAttributes(params);
    }
    
}
