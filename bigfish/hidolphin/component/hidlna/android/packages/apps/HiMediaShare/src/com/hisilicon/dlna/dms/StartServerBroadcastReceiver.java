package com.hisilicon.dlna.dms;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.sax.StartElementListener;
import com.hisilicon.dlna.util.CommonDef;
import android.widget.Toast;

public class StartServerBroadcastReceiver extends BroadcastReceiver
{

    public void onReceive(Context context, Intent intent)
    {
        final Intent serviceDMSIntent = new Intent(context,MediaService.class);
        //serviceDMSIntent.setAction("com.hisilicon.dlna.dms.IDMSServer");
        CommonDef.startServiceEx(context,serviceDMSIntent);
    }
}
