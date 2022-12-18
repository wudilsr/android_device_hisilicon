package com.hisilicon.android.videoplayer.utility;

import java.lang.reflect.Field;

import android.app.Dialog;
import android.content.DialogInterface;
import android.view.Window;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;

public class DialogTool
{
    /**
     * set dialog open/close by reflection
     * @param pDialog
     * @param pIsClose true - close false - open
     */
    public static void setClose(DialogInterface pDialog, Boolean pIsClose)
    {
        try
        {
            Field _Field = pDialog.getClass().getSuperclass().getDeclaredField("mShowing");
            _Field.setAccessible(true);
            _Field.set(pDialog, pIsClose);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public static void disableBackgroundDim(Dialog pDialog)
    {
        Window _Window = pDialog.getWindow();
        WindowManager.LayoutParams _Params = _Window.getAttributes();
        _Params.dimAmount = 0f;
        _Window.setAttributes(_Params);
        _Window.addFlags(WindowManager.LayoutParams.FLAG_DIM_BEHIND);
    }

    public static void setLayout(Dialog pDialog, int pWidth, int pHeight)
    {
        Window _Window = pDialog.getWindow();
        _Window.setLayout(pWidth, pHeight);
    }

    public static void setPosition(Dialog pDialog, int pPosX, int pPosY)
    {
        Window _Window = pDialog.getWindow();
        WindowManager.LayoutParams _Params = _Window.getAttributes();
        _Params.x = pPosX;
        _Params.y = pPosY;
        _Window.setAttributes(_Params);
    }

    public static void setWidth(Dialog pDialog, int pWidth)
    {
        Window _Window = pDialog.getWindow();
        WindowManager.LayoutParams _Params = _Window.getAttributes();
        _Params.width = pWidth;
        _Window.setAttributes(_Params);
    }

    public static void setWidthAndPosition(Dialog pDialog, int pWidth, int pPosX, int pPosY)
    {
        setWidth(pDialog, pWidth);
        setPosition(pDialog, pPosX, pPosY);
    }

    public static void setDefaultTipDisplay(Dialog pDialog)
    {
        setPosition(pDialog, 0, -200);
        setLayout(pDialog, LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
    }

    public static void setDefaultSelectDisplay(Dialog pDialog)
    {
        setLayout(pDialog, 400, 480);
    }
}
