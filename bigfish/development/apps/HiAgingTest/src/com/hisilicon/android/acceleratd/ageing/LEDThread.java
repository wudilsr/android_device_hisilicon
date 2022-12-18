package com.hisilicon.android.acceleratd.ageing;

import java.io.IOException;
import java.io.PrintStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

import android.util.Log;
import com.hisilicon.android.sdkinvoke.HiSdkinvoke;

class LEDThread extends Thread
{
    public static boolean start = true;
    public void run()
    {
        HiSdkinvoke mSDKInvoke = new HiSdkinvoke();
        mSDKInvoke.hiBitSet(0xF8000044,4,3,0x00);
        int t = 1;
        while(true)
        {
            if(start == false)
                break;
            t = (t+1)%2 ;
            mSDKInvoke.hiGpioBitSet(0xF8004000,3,t);
            try
            {
                Thread.sleep(500);
		    }
            catch (InterruptedException e)
            {
                e.printStackTrace();
		    }
        }
    }
}
