package com.hisilicon.android.videoplayer.util;

import java.io.File;
import java.text.DecimalFormat;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.PorterDuffXfermode;
import android.graphics.RectF;
import android.graphics.Bitmap.Config;
import android.graphics.PorterDuff.Mode;
import android.graphics.drawable.BitmapDrawable;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class Tools
{
    public String formatSize(long size)
    {
        String strSize = null;
        DecimalFormat format = new DecimalFormat("#0.0");

        if (size / 1024.0 / 1024 / 1024 >= 1)
        {
            strSize = format.format(size / 1024.0 / 1024 / 1024) + "GB";
        }
        else if (size / 1024.0 / 1024 >= 1)
        {
            strSize = format.format(size / 1024.0 / 1024) + "MB";
        }
        else if (size / 1024.0 >= 1)
        {
            strSize = format.format(size / 1024.0) + "KB";
        }
        else
        {
            strSize = size + "B";
        }

        return strSize;
    }

    public String formatTime(Context con, int millionSeconds)
    {
        if (millionSeconds < 1000)
        {
            return "00:00:00";
        }

        int seconds = millionSeconds / 1000;
        StringBuffer strTime = new StringBuffer("");
        if (seconds / 60 / 60 >= 1)
        {
            if (seconds / 60 / 60 < 10)
            {
                strTime.append("0");
            }

            strTime.append(seconds / 60 / 60);
            strTime.append(":");
        }
        else
        {
            strTime.append("00:");
        }

        int remain = seconds % (60 * 60);
        if (remain / 60 >= 1)
        {
            if (remain / 60 < 10)
            {
                strTime.append("0");
            }

            strTime.append(remain / 60);
            strTime.append(":");
        }
        else
        {
            strTime.append("00:");
        }

        remain = remain % 60;
        if (remain >= 1)
        {
            if (remain < 10)
            {
                strTime.append("0");
            }

            strTime.append(remain);
        }
        else
        {
            strTime.append("00");
        }

        return strTime.toString();
    }

    public View createCascadeImgs(Activity activity, Bitmap originalImg, Bitmap centerImg, int num, int screenWidth)
    {
        LinearLayout layout = new LinearLayout(activity);

        layout.setLayoutParams(new ViewGroup.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
        layout.setOrientation(LinearLayout.HORIZONTAL);
        layout.setGravity(Gravity.CENTER_VERTICAL);

        int length = 0;
        if (num <= 0)
        {
            return null;
        }
        else
        {
            length = 2 * num - 1;
        }

        for (int i = 1; i <= length; i++)
        {
            int width  = originalImg.getWidth();
            int height = originalImg.getHeight();
            if ((centerImg != null) && (i == num))
            {
                width  = centerImg.getWidth();
                height = centerImg.getHeight();
            }

            int topNum = i;
            if (topNum > num)
            {
                topNum = 2 * num - i;
            }

            int needSize = (int)((screenWidth / num + 1) * topNum * 1.0 / num);
            float rate = needSize * 1.0f / width;

            Matrix matrix = new Matrix();
            matrix.setScale(rate, rate);

            float showRate = 0.8f;
            if (i == num)
            {
                showRate = 1.0f;
            }

            int x = 0;
            if (i > num)
            {
                x = (int)(width * 0.2f);
            }

            Bitmap img = null;
            if ((i == num) && (centerImg != null))
            {
                img = Bitmap.createBitmap(centerImg, x, 0, (int)(width * showRate), height, matrix, false);
            }
            else
            {
                img = Bitmap.createBitmap(originalImg, x, 0, (int)(width * showRate), height, matrix, false);
            }

            ImageView iv = new ImageView(activity);
            iv.setLayoutParams(new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
            iv.setAlpha((int)((topNum * 1.0 / num) * 255));
            iv.setImageBitmap(img);
            layout.addView(iv);
        }

        return layout;
    }

    public String accessImagePathFromVideoPath(String videoPath, String newEnds)
    {
        File file = new File(videoPath);
        String folderPath = file.getParentFile().getPath();
        String folderName = folderPath.substring(folderPath.lastIndexOf("/"));
        String imgPath = folderPath + folderName + newEnds;

        return imgPath;
    }

    public View dialogContentOfSelfDefined(Context context, View contentView, int resTitle)
    {
        ImageView imageView = new ImageView(context);

        imageView.setImageResource(android.R.drawable.ic_menu_more);
        imageView.setPadding(10, 10, 4, 10);

        TextView textView = new TextView(context);
        textView.setTextSize(22);
        textView.setTextColor(Color.WHITE);
        textView.setText(resTitle);
        textView.setPadding(4, 17, 10, 10);

        ImageView view = new ImageView(context);
        view.setBackgroundColor(Color.WHITE);
        view.setMaxHeight(1);
        view.setMinimumHeight(1);

        LinearLayout childLinear = new LinearLayout(context);
        childLinear.addView(imageView);
        childLinear.addView(textView);

        LinearLayout parentLinear = new LinearLayout(context);
        parentLinear.setOrientation(LinearLayout.VERTICAL);
        parentLinear.addView(childLinear);
        parentLinear.addView(view);
        parentLinear.addView(contentView);

        return parentLinear;
    }

    public BitmapDrawable drawPicture(int color)
    {
        Bitmap bm = Bitmap.createBitmap(30, 15, Config.ARGB_8888);
        Canvas co = new Canvas(bm);

        co.drawColor(color);
        Bitmap res = Bitmap.createBitmap(bm.getWidth(), bm.getHeight(), Config.ARGB_8888);
        Canvas canvas = new Canvas(res);
        Paint p = new Paint(Paint.ANTI_ALIAS_FLAG);
        canvas.drawRoundRect(new RectF(0, 0, bm.getWidth(), bm.getHeight()), 5, 5, p);
        p.setXfermode(new PorterDuffXfermode(Mode.SRC_IN));
        canvas.drawBitmap(bm, 0, 0, p);
        BitmapDrawable bd = new BitmapDrawable(res);
        return bd;
    }
}
