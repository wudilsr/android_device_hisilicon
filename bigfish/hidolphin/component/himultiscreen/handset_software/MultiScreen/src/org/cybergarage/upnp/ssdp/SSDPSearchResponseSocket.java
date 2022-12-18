/******************************************************************
*
*    CyberUPnP for Java
*
*    Copyright (C) Satoshi Konno 2002
*
*    File: SSDPSearchResponseSocket.java
*
*    Revision;
*
*    11/20/02
*        - first revision.
*    05/28/03
*        - Added post() to send a SSDPSearchRequest.
*    01/31/08
*        - Changed start() not to abort when the interface infomation is null on Android m3-rc37a.
*
******************************************************************/

package org.cybergarage.upnp.ssdp;

import java.net.DatagramSocket;
import java.net.InetAddress;

import org.cybergarage.upnp.ControlPoint;

public class SSDPSearchResponseSocket extends HTTPUSocket implements Runnable
{
    ////////////////////////////////////////////////
    //    Constructor
    ////////////////////////////////////////////////

    public SSDPSearchResponseSocket()
    {
        setControlPoint(null);
    }

    public SSDPSearchResponseSocket(String bindAddr, int port)
    {
        super(bindAddr, port);
        setControlPoint(null);
    }

    ////////////////////////////////////////////////
    //    ControlPoint
    ////////////////////////////////////////////////

    private ControlPoint controlPoint = null;

    public void setControlPoint(ControlPoint ctrlp)
    {
        this.controlPoint = ctrlp;
    }

    public ControlPoint getControlPoint()
    {
        return controlPoint;
    }

    ////////////////////////////////////////////////
    //    run
    ////////////////////////////////////////////////

    private Thread deviceSearchResponseThread = null;

    public void run()
    {
        Thread thisThread = Thread.currentThread();

        ControlPoint ctrlPoint = getControlPoint();

        while (deviceSearchResponseThread == thisThread) {
            Thread.yield();
            SSDPPacket packet = receive();
            if (packet == null)
                break;
            if (ctrlPoint != null)
            {
                // Begin modify by MultiScreen.
                new SSDPSearchResponseHandleThread(ctrlPoint, packet).start();
                // ctrlPoint.searchResponseReceived(packet);
                // End modify by MultiScreen.
            }
        }
    }

    public void start()    {

        StringBuffer name = new StringBuffer("Cyber.SSDPSearchResponseSocket/");
        DatagramSocket s = getDatagramSocket();
        // localAddr is null on Android m3-rc37a (01/30/08)
        // modify for DatagramSocket may null, HTTPUSocket may not initial done.
        InetAddress localAddr = null;

        if (s != null)
        {
            localAddr = s.getLocalAddress();
        }

        if (localAddr != null)
        {
            name.append(s.getLocalAddress()).append(':');
            name.append(s.getLocalPort());
        }
        deviceSearchResponseThread = new Thread(this,name.toString());
        deviceSearchResponseThread.start();
    }

    public void stop()
    {
        //for MultiScreen
        close();

        deviceSearchResponseThread = null;
    }

    ////////////////////////////////////////////////
    //    post
    ////////////////////////////////////////////////

    public boolean post(String addr, int port, SSDPSearchResponse res)
    {
        return post(addr, port, res.getHeader());
    }

    ////////////////////////////////////////////////
    //    post
    ////////////////////////////////////////////////

    public boolean post(String addr, int port, SSDPSearchRequest req)
    {
        return post(addr, port, req.toString());
    }

    // Begin modify by MultiScreen.
    /**
     * Thread of handle SSDP search response SSDPPacket.<br>
     * CN:SSDP搜索响应包处理线程。
     */
    private class SSDPSearchResponseHandleThread extends Thread
    {
        ControlPoint mCtrlPoint = null;

        SSDPPacket mPacket = null;

        public SSDPSearchResponseHandleThread(ControlPoint point, SSDPPacket packet)
        {
            mCtrlPoint = point;
            mPacket = packet;
        }

        @Override
        public void run()
        {
            mCtrlPoint.searchResponseReceived(mPacket);
        }
    }
    // End modify by MultiScreen.
}
