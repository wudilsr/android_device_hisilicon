package com.HiMediaSample;
import android.util.Log;
import android.widget.Toast;
import android.content.Context;
import android.os.Parcel;
import android.media.MediaPlayer;
import java.lang.reflect.Method;
import java.lang.Class;
import java.lang.Integer;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.widget.EditText;
import android.widget.RelativeLayout;
import android.content.Context;
import android.content.DialogInterface;
import android.view.LayoutInflater;
import android.app.Activity;
import java.lang.StringBuilder;
import android.os.Message;
import android.os.Handler;
import android.widget.Toast;

public class InvokeCommon
{
    private Context mContext;
    private String LOG_TAG = "dqptest";
    private StringBuilder mArgs;

    public InvokeCommon(Context context)
    {
        mContext = context;
    }

    public void ShowResult(String strResult)
    {
        Toast.makeText(mContext, strResult, Toast.LENGTH_LONG).show();
    }

    public String getArgsString()
    {
        if (null == mArgs)
            return null;
        return mArgs.toString();
    }

    public void setInvokeArgsDialog1(final Handler NotifyExec)
    {
        final AlertDialog.Builder builder = new AlertDialog.Builder(mContext);
        mArgs = null;
        builder.setTitle("InvokeDialog1");
        LayoutInflater inflater = ((Activity)mContext).getLayoutInflater();
        RelativeLayout linear = (RelativeLayout)inflater.inflate(R.layout.invokeargdlg1, null);
        final EditText ArgsEt = (EditText)linear.findViewById(R.id.arg_dlg1_et1);
        builder.setView(linear);
        builder.setPositiveButton(R.string.confirm, new DialogInterface.OnClickListener()
        {
            public void onClick(DialogInterface dialog, int which)
            {
                mArgs = new StringBuilder(ArgsEt.getText().toString());
                Message m = NotifyExec.obtainMessage();
                NotifyExec.sendMessage(m);

        }
        }).setNegativeButton(R.string.cancel, null);

        AlertDialog dialog = builder.create();

        dialog.show();
        dialog.getButton(DialogInterface.BUTTON_POSITIVE).requestFocus();
        return;
    }
}
