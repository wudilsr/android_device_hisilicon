package com.hisilicon.android.videoplayer.utility;

import android.util.Log;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import java.math.BigInteger;
import java.io.File;
import java.io.FileInputStream;

public class ShooterMD5
{
    public static final String TAG = "ShooterMD5";

    public static String getFileMD5(File file)
    {
        if (!file.isFile())
        {
            return null;
        }
        MessageDigest digest1 = null;
        MessageDigest digest2 = null;
        MessageDigest digest3 = null;
        MessageDigest digest4 = null;

        FileInputStream in1 = null;
        FileInputStream in2 = null;
        FileInputStream in3 = null;
        FileInputStream in4 = null;
        byte buffer[] = new byte[4096];
        int len;
        try
        {
            digest1 = MessageDigest.getInstance("MD5");
            in1 = new FileInputStream(file);
            int length = in1.available();
            Log.i(TAG,"length:"+length);
            int offset1 = 4096;
            int offset2 = length / 3 * 2;
            int offset3 = length / 3;
            int offset4 = length - 8192;
            in1.skip(offset1);
            len = in1.read(buffer, 0, 4096);
            if(len != -1)
                digest1.update(buffer, 0, len);
            in1.close();

            digest2 = MessageDigest.getInstance("MD5");
            in2 = new FileInputStream(file);
            in2.skip(offset2);
            len = in2.read(buffer, 0, 4096);
            if(len != -1)
                digest2.update(buffer, 0, len);
            in2.close();

            digest3 = MessageDigest.getInstance("MD5");
            in3 = new FileInputStream(file);
            in3.skip(offset3);
            len = in3.read(buffer, 0, 4096);
            if(len != -1)
                digest3.update(buffer, 0, len);
            in3.close();

            digest4 = MessageDigest.getInstance("MD5");
            in4 = new FileInputStream(file);
            in4.skip(offset4);
            len = in4.read(buffer, 0, 4096);
            if(len != -1)
                digest4.update(buffer, 0, len);
            in4.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
            return null;
        }
        BigInteger bigInt1 = new BigInteger(1, digest1.digest());
        Log.i(TAG,"bigInt1.toString(16):"+bigInt1.toString(16));
        BigInteger bigInt2 = new BigInteger(1, digest2.digest());
        Log.i(TAG,"bigInt2.toString(16):"+bigInt2.toString(16));
        BigInteger bigInt3 = new BigInteger(1, digest3.digest());
        Log.i(TAG,"bigInt3.toString(16):"+bigInt3.toString(16));
        BigInteger bigInt4 = new BigInteger(1, digest4.digest());
        Log.i(TAG,"bigInt4.toString(16):"+bigInt4.toString(16));
        return bigInt1.toString(16)+";"+bigInt2.toString(16)+";"+bigInt3.toString(16)+";"+bigInt4.toString(16);
    }
}
