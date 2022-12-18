package com.hisilicon.android.videoplayer.activity.base;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.StrictMode;
import android.view.LayoutInflater;
import android.widget.Toast;

import com.hisilicon.android.videoplayer.R;

/**
 * ActivityBase: business independent
 */
public class ActivityBase extends Activity
{
    protected ProgressDialog mProgressDialog;

    private static final int TOAST_DEFAULT_DURATION = 1000;

    protected void enableStrictMode()
    {
        StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder().detectAll().penaltyLog()
            .build());
        StrictMode.setVmPolicy(new StrictMode.VmPolicy.Builder().detectAll().penaltyLog().build());
    }

    protected void showToast(int pMsgId)
    {
        showToast(getString(pMsgId));
    }

    protected void showToast(int pMsgId, int pDuration)
    {
        showToast(getString(pMsgId), pDuration);
    }

    protected void showToast(String pMsg)
    {
        Toast.makeText(this, pMsg, TOAST_DEFAULT_DURATION).show();
    }

    protected void showToast(String pMsg, int pDuration)
    {
        Toast.makeText(this, pMsg, pDuration).show();
    }

    protected void openActivity(Class<?> pClass)
    {
        Intent _Intent = new Intent();
        _Intent.setClass(this, pClass);
        startActivity(_Intent);
    }

    protected LayoutInflater getInflater()
    {
        LayoutInflater _Inflater = LayoutInflater.from(this);
        return _Inflater;
    }

    /**
     * get single operation dialog
     * @param pTitleId dialog title id
     * @param pMessageId dialog message id
     * @param pOnClickListener dialog click listener
     * @return dialog
     */
    protected AlertDialog getSingleOperationDialog(int pTitleId, int pMessageId,
        DialogInterface.OnClickListener pOnClickListener)
    {
        return new AlertDialog.Builder(this).setTitle(pTitleId).setMessage(pMessageId)
            .setPositiveButton(android.R.string.ok, pOnClickListener).setCancelable(false).show();
    }

    /**
     * get double operation dialog
     * @param pTitleId dialog title id
     * @param pMessageId dialog message id
     * @param pOnClickListener dialog click listener
     * @return dialog
     */
    protected AlertDialog getDoubleOperationDialog(int pTitleId, int pMessageId,
        DialogInterface.OnClickListener pOnClickListener)
    {
        return new AlertDialog.Builder(this).setTitle(pTitleId).setMessage(pMessageId)
            .setPositiveButton(android.R.string.yes, pOnClickListener)
            .setNegativeButton(android.R.string.no, pOnClickListener).setCancelable(true).show();
    }

    protected void showProgressDialog(int pTitleId, int pMessageId)
    {
        if (mProgressDialog == null)
        {
            mProgressDialog = new ProgressDialog(this);
        }

        mProgressDialog.setTitle(pTitleId);
        mProgressDialog.setMessage(getString(pMessageId));
        mProgressDialog.setCancelable(true);
        mProgressDialog.show();
    }

    protected void dismissProgressDialog()
    {
        if (mProgressDialog != null)
        {
            mProgressDialog.dismiss();
            mProgressDialog = null;
        }
    }
}
