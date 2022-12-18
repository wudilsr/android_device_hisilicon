package com.hisilicon.dlna.dmr;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.sax.StartElementListener;
import com.hisilicon.dlna.util.CommonDef;

//import com.hisilicon.dlna.media.share.IDMSServer;

/**
 *
 * @author t00204177 After received the "android.intent.action.BOOT_COMPLETED" broadcast, start
 *         UpnpBootBroadcastService.class <br>
 *         CN: 当接收到开机完成事件后，启动UpnpBootBroadcastService.class 服务<br>
 *
 */
public class UpnpBootBroadcastRec extends BroadcastReceiver
{

    public void onReceive(Context context, Intent intent)
    {
        //final Intent serviceDMSIntent = new Intent();
        //serviceDMSIntent.setAction("com.hisilicon.dlna.settings.UPNP_BOOT_BROADCAST_SERVICE_DMS");
        //CommonDef.startServiceEx(context,serviceDMSIntent);
        final Intent serviceDMRIntent = new Intent(context,UpnpBootBroadcastServiceDMR.class);
        //serviceDMRIntent.setAction("com.hisilicon.dlna.dmr.UPNP_BOOT_BROADCAST_SERVICE_DMR");
        CommonDef.startServiceEx(context,serviceDMRIntent);
    };

}
