package com.hisilicon.multiscreen.protocol.utils;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.drawable.Drawable;

import com.hisilicon.multiscreen.protocol.message.Action;
import com.hisilicon.multiscreen.protocol.message.AppInfo;
import com.hisilicon.multiscreen.protocol.message.Argument;
import com.hisilicon.multiscreen.protocol.message.ArgumentValue;

/**
 * Class used for the conversion between application list and byte array.<br>
 * CN:APP应用列表转换类.
 */
public class AppListTransmitter
{

    /**
     * Convert byte array to application information list.<br>
     * CN:将字节数组转换为AppInfo列表.
     * @param data - byte array.<br>
     *        CN:传递的数据.
     * @return - Application information list.<br>
     *         CN:AppInfo列表.
     * @throws IOException - I/O异常
     * @throws ClassNotFoundException - 无法找到指定的类异常
     */
    public static List<AppInfo> fromTransmitPacket(byte[] data) throws IOException,
        ClassNotFoundException
    {
        ByteArrayInputStream bIn = new ByteArrayInputStream(data);
        ObjectInputStream oIn = new ObjectInputStream(bIn);
        @SuppressWarnings("unchecked")
        ArrayList<AppInfo> appList = (ArrayList<AppInfo>) oIn.readObject();
        oIn.close();
        return appList;
    }

    /**
     * Convert byte application information list to array.<br>
     * CN:将应用程序信息转换为字节数组。
     * @param pm - Package manager.<br>
     *        CN:应用程序信息。
     * @return - byte array.<br>
     *         CN:字节数组。
     * @throws IOException - CN:转换时可能产生的IO异常。
     */
    public static byte[] toTransmitPacket(PackageManager pm) throws IOException
    {
        ByteArrayOutputStream bOut = new ByteArrayOutputStream();
        ObjectOutputStream oOut = new ObjectOutputStream(bOut);
        ByteArrayOutputStream iOut = new ByteArrayOutputStream();

        Intent i = new Intent(Intent.ACTION_MAIN, null);
        i.addCategory(Intent.CATEGORY_LAUNCHER);
        List<ResolveInfo> rList = pm.queryIntentActivities(i, 0);

        if (rList == null)
        {
            return null;
        }

        // 排序
        Collections.sort(rList, new ResolveInfo.DisplayNameComparator(pm));

        int pIndex = 0; // package index
        ArrayList<AppInfo> appList = new ArrayList<AppInfo>();
        for (Iterator<ResolveInfo> it = rList.iterator(); it.hasNext(); pIndex++)
        {
            ResolveInfo resolve = it.next();

            /*
             * if(app.activityInfo.packageName.equalsIgnoreCase(
             * "com.android.settings")) { //隐藏设置 continue; }
             */

            AppInfo app = new AppInfo();
            app.setAppName(resolve.loadLabel(pm).toString());
            app.setPackageName(resolve.activityInfo.packageName);
            app.setPackageIndex(pIndex);

            Drawable img = resolve.loadIcon(pm);
            Bitmap src =
                Bitmap.createBitmap(img.getIntrinsicWidth(), img.getIntrinsicHeight(),
                    Bitmap.Config.ARGB_8888);

            // Draw icon to bitmap
            Canvas canvas = new Canvas(src);
            img.setBounds(0, 0, img.getIntrinsicWidth(), img.getIntrinsicHeight());
            img.draw(canvas);

            // Zoom the icon
            Bitmap zoom = zoomBitmap(src, 40, 40);

            iOut.reset();
            zoom.compress(CompressFormat.PNG, 50, iOut);
            iOut.flush();

            app.setPackageIcon(iOut.toByteArray());
            appList.add(app);

            // Free bitmap
            src.recycle();
            zoom.recycle();

        }

        oOut.writeObject(appList);
        oOut.flush();
        byte[] data = bOut.toByteArray();

        // Close stream
        oOut.close();
        iOut.close();

        return data;
    }

    /**
     * Transmit application information to response action.<br>
     * @param action - response action
     * @param pm - package manager
     * @return action to response
     * @throws IOException - exception stream
     */
    public static Action toTransmitPacket(Action action, PackageManager pm) throws IOException
    {
        ByteArrayOutputStream iOut = new ByteArrayOutputStream();

        Intent i = new Intent(Intent.ACTION_MAIN, null);
        i.addCategory(Intent.CATEGORY_LAUNCHER);
        List<ResolveInfo> rList = pm.queryIntentActivities(i, 0);

        if (rList == null)
        {
            return null;
        }

        // 排序
        Collections.sort(rList, new ResolveInfo.DisplayNameComparator(pm));

        int pIndex = 0;
        for (Iterator<ResolveInfo> it = rList.iterator(); it.hasNext(); pIndex++)
        {
            ResolveInfo resolve = it.next();

            Drawable img = resolve.loadIcon(pm);
            Bitmap src =
                Bitmap.createBitmap(img.getIntrinsicWidth(), img.getIntrinsicHeight(),
                    Bitmap.Config.ARGB_8888);

            // Draw icon to bitmap
            Canvas canvas = new Canvas(src);
            img.setBounds(0, 0, img.getIntrinsicWidth(), img.getIntrinsicHeight());
            img.draw(canvas);

            // Zoom the icon
            Bitmap zoom = zoomBitmap(src, 40, 40);

            iOut.reset();
            zoom.compress(CompressFormat.PNG, 50, iOut);
            iOut.flush();

            byte[] data = iOut.toByteArray();

            Argument argument = new Argument();

            for (int j = 0; j < 4; j++)
            {
                ArgumentValue argumentValue = new ArgumentValue();

                switch (j)
                {
                    case 0:
                    {

                        argumentValue.setKey("AppName");
                        argumentValue.setValue(resolve.loadLabel(pm).toString());
                        break;
                    }

                    case 1:
                    {
                        argumentValue.setKey("PackageName");
                        argumentValue.setValue(resolve.activityInfo.packageName);
                        break;
                    }

                    case 2:
                    {
                        argumentValue.setKey("PackageIndex");
                        argumentValue.setValue(pIndex);
                        break;
                    }

                    case 3:
                    {
                        argumentValue.setKey("PackageIcon");
                        argumentValue.setValue(data);
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }

                argument.addArgumentValue(argumentValue);
            }

            action.addArgument(argument);

            // Free bitmap
            src.recycle();
            zoom.recycle();
        }

        // Close stream
        iOut.close();

        return action;
    }

    /**
     * Zoom bitmap.<br>
     * CN:缩放位图。
     * @param bitmap - source bitmap
     * @param width
     * @param height
     * @return Bitmap
     */
    private static Bitmap zoomBitmap(Bitmap bitmap, int width, int height)
    {
        Bitmap zoom;
        int h = bitmap.getHeight();
        int w = bitmap.getWidth();
        float sx = ((float) width / w);
        float sy = ((float) height / h);
        Matrix matrix = new Matrix();
        matrix.postScale(sx, sy);
        zoom = Bitmap.createBitmap(bitmap, 0, 0, w, h, matrix, true);
        return zoom;
    }
}
