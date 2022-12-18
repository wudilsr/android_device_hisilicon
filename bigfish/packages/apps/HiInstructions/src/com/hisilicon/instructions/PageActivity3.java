package com.hisilicon.instructions;

import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.RelativeLayout;

public class PageActivity3 extends PageActivity {
    private final static String mURL = "http://2.moonlightjewelbox.sinaapp.com/himultiscreen/baohe/HandsetForMultiScreen.apk";
    private final static int mQRImgWidth = 360;
    private final static int mQRImgHeight = 288;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        QRCodeGenerator mQRGen = new QRCodeGenerator();
        Bitmap bm = mQRGen.createQRImage(mURL, mQRImgWidth, mQRImgHeight);
        if (bm != null) {
            RelativeLayout mQR = (RelativeLayout) findViewById(R.id.viewQR);
            ImageView mQRimage = new ImageView(this);
            mQRimage.setImageBitmap(bm);
            mQR.addView(mQRimage);
        }
    }

    @Override
    public int getLayoutId() {
        return R.layout.page_activity_3;
    }

    @Override
    public int getPosition() {
        return 2;
    }

    @Override
    public void startPrvActivity() {
        Intent intent = new Intent(PageActivity3.this, PageActivity2.class);
        startActivity(intent);
        finish();
    }

    @Override
    public void startNextActivity() {
        Intent intent = new Intent(PageActivity3.this, PageActivity4.class);
        startActivity(intent);
        finish();
    }
}