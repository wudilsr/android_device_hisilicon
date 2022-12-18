package com.hisilicon.multiscreen.server.speech;

import android.app.Dialog;
import android.view.WindowManager;

public class DialogUtil
{
    public static void setDialogForService(Dialog dialog)
    {
        dialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
    }

    public static void showServiceDialog(Dialog dialog)
    {
        setDialogForService(dialog);
        dialog.show();
    }
}
