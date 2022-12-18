package com.hisilicon.android.acceleratd.ageing;

import java.io.IOException;
import java.io.PrintStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

class SendledThread extends Thread
{
    private byte SHour;
    private byte SMinute;
    private byte SSecond;
    private byte Scmd;
    private byte[] message;
    private byte[] str = new byte[10];

    public SendledThread(byte paramByte)
    {
        this.message = new byte[10];
        this.Scmd    = paramByte;
        this.SHour   = 0;
        this.SMinute = 0;
        this.SSecond = 0;
        this.message[0] = 0;
        this.message[1] = 0;
        this.message[2] = 0;
        this.message[3] = 0;
        this.message[4] = 0;
        this.message[5] = 0;
    }

    public SendledThread(byte paramByte1, byte paramByte2, byte paramByte3, byte paramByte4)
    {
        this.message = new byte[10];
        this.Scmd    = paramByte1;
        this.SHour   = paramByte2;
        this.SMinute = paramByte3;
        this.SSecond = paramByte4;
        this.message[0] = 0;
        this.message[1] = 0;
        this.message[2] = 0;
        this.message[3] = 0;
        this.message[4] = 0;
        this.message[5] = 0;
    }

    public SendledThread(String paramString)
    {
        this.message = new byte[10];
        this.str     = strtobyte(paramString);
        this.Scmd    = 48;
        this.SHour   = 0;
        this.SMinute = 0;
        this.SSecond = 0;
        this.message[0] = this.str[0];
        this.message[1] = this.str[1];
        this.message[2] = this.str[2];
        this.message[3] = this.str[3];
        this.message[4] = this.str[4];
        this.message[5] = this.str[5];
    }

    public void run()
    {
        try
        {
            DatagramSocket localDatagramSocket1 = new DatagramSocket();
            DatagramSocket localDatagramSocket2 = localDatagramSocket1;
        } catch (SocketException localUnknownHostException) {
            /*try
            {
                InetAddress localInetAddress2 = InetAddress.getByName("127.0.0.1");
                localInetAddress1  = localInetAddress2;
                byte[] arrayOfByte = new byte[10];
                arrayOfByte[0] = this.Scmd;
                arrayOfByte[1] = this.SHour;
                arrayOfByte[2] = this.SMinute;
                arrayOfByte[3] = this.SSecond;
                arrayOfByte[4] = this.message[0];
                arrayOfByte[5] = this.message[1];
                arrayOfByte[6] = this.message[2];
                arrayOfByte[7] = this.message[3];
                arrayOfByte[8] = this.message[4];
                arrayOfByte[9] = this.message[5];
                localDatagramPacket = new DatagramPacket(arrayOfByte, 10, localInetAddress1, 33333);
            } catch (UnknownHostException localUnknownHostException) {
                try
                {
                    while (true)
                    {
                        DatagramPacket localDatagramPacket;
                        System.out.println("YLM LOG call udpsend .....\n");
                        localDatagramSocket2.send(localDatagramPacket);
                        return;
                        localSocketException = localSocketException;
                        localSocketException.printStackTrace();
                        DatagramSocket localDatagramSocket2 = null;
                    }

                    localUnknownHostException = localUnknownHostException;
                    localUnknownHostException.printStackTrace();
                    InetAddress localInetAddress1 = null;
                } catch (IOException localIOException) {
                    localIOException.printStackTrace();
                }
            }*/
        }
    }

    public byte[] strtobyte(String paramString)
    {
        return paramString.getBytes();
    }
}

/* Location:           E:\反编译\jd-gui\classes_dex2jar.jar
 * Qualified Name:     com.android.diagtest.SendledThread
 * JD-Core Version:    0.6.1
 */
