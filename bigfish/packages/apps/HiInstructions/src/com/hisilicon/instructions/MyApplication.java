package com.hisilicon.instructions;

import android.app.Application;
import android.content.Context;
import android.view.ViewGroup.LayoutParams;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

public class MyApplication extends Application {
    public static final String SIGN_ID = "persist.sys.instructions.id";
    private boolean isSign;
    private int pageNo;

    public boolean isSign() {
        return isSign;
    }

    public void setSign(boolean isSign) {
        this.isSign = isSign;
    }

    public int getPageNo() {
        return pageNo;
    }

    public void setPageNo(int pageNo) {
        this.pageNo = pageNo;
    }

    public RelativeLayout getRelativeLayout(Context context, int position) {
        RelativeLayout rLayout = new RelativeLayout(context);
        RelativeLayout.LayoutParams vParams = new RelativeLayout.LayoutParams(
                RelativeLayout.LayoutParams.MATCH_PARENT,
                RelativeLayout.LayoutParams.WRAP_CONTENT);
        vParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
        rLayout.setLayoutParams(vParams);

        LinearLayout lLayout = new LinearLayout(context);
        RelativeLayout.LayoutParams rParams = new RelativeLayout.LayoutParams(
                RelativeLayout.LayoutParams.WRAP_CONTENT,
                RelativeLayout.LayoutParams.WRAP_CONTENT);
        rParams.addRule(RelativeLayout.CENTER_HORIZONTAL, RelativeLayout.TRUE);
        rParams.setMargins(0, 0, 0, 30);
        lLayout.setLayoutParams(rParams);
        lLayout.setOrientation(LinearLayout.HORIZONTAL);
        for (int i = 0; i < pageNo; i++) {
            ImageView iv = new ImageView(context);
            iv.setLayoutParams(new LayoutParams(20, 20));
            if (i == position) {
                iv.setBackgroundResource(R.drawable.page_indicator_focused);
            } else {
                iv.setBackgroundResource(R.drawable.page_indicator);
            }
            lLayout.addView(iv);
        }
        rLayout.addView(lLayout);
        return rLayout;
    }
}