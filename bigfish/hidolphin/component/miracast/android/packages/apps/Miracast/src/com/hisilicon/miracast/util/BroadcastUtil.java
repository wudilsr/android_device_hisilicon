package com.hisilicon.miracast.util;

import android.os.Bundle;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import com.hisilicon.miracast.constant.IntentConst;

public class BroadcastUtil
{
    private Context mContext = null;

    public BroadcastUtil(Context context)
    {
        mContext = context;
    }

    public void sendWfdBroadCast(int statetId)
    {
        LogUtil.d("wfdstate:" + statetId);

        Intent intent = new Intent(IntentConst.ACTION_MIRACAST_STATE_CHANGE);
        intent.putExtra(IntentConst.EXTRA_WFD_STATE, statetId);
        mContext.sendBroadcast(intent);
    }
}
