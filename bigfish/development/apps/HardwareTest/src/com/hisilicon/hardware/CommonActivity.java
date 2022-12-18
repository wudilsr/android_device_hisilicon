package com.hisilicon.hardware;

import java.io.File;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface.OnCancelListener;
import android.os.Environment;
import android.view.WindowManager;

import com.hisilicon.hardware.util.Common;
import com.hisilicon.hardwaretest.R;

public class CommonActivity extends Activity {

    public final String USB_PATH = "/mnt/sda";
    public final String PROPERTY_PATH = "ro.product.device";
    public final String DEVICE_98M = "Hi3798MV100";
    public final String DEVICE_16C = "Hi3716CV100";

    public static final int NORMAL_PLAY = 0;
    public static final int VIDEO_PLAY = 1;
    public static final int AUDIO_PLAY = 2;

    public String getStoragePath() {
        File file = new File(USB_PATH);
        if (file.exists() && file.canRead())
            return USB_PATH;
        else
            return Environment.getExternalStorageDirectory().getPath();
    }

    public boolean isEmptyString(String str) {
        return null == str || "".equals(str);
    }

    public void showMessageDialog(int stringId) {
        AlertDialog.Builder builder = new AlertDialog.Builder(
                CommonActivity.this);
        builder.setTitle(getResources().getString(R.string.dialog_title));
        builder.setMessage(getResources().getString(stringId));
        builder.setNegativeButton("OK", null);

        AlertDialog dialog = builder.create();
        dialog.getWindow()
                .setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
        dialog.setCanceledOnTouchOutside(false);
        dialog.setCancelable(false);
        dialog.show();
    }

    public void showLoadingDialog(String title, String message,
            OnCancelListener listener) {
        ProgressDialog.show(CommonActivity.this, title, message, true, true,
                listener);
    }

    public int getFileType(String path) {
        String fileType = path.substring(path.lastIndexOf(".") + 1);
        for (String type : Common.VIDEO_TYPE) {
            if (type.equalsIgnoreCase(fileType)) {
                return VIDEO_PLAY;
            }
        }
        for (String type : Common.AUDIO_TYPE) {
            if (type.equalsIgnoreCase(fileType)) {
                return AUDIO_PLAY;
            }
        }
        return NORMAL_PLAY;
    }

}