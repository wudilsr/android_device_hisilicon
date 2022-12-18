package com.hisilicon.android.videoplayer.utility;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class MD5Tool
{
    protected static char mHexDigits[] =
    { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

    protected static MessageDigest mMessageDigest = null;

    static
    {
        try
        {
            mMessageDigest = MessageDigest.getInstance("MD5");
        }
        catch (NoSuchAlgorithmException pException)
        {
            pException.printStackTrace();
        }
    }

    /**
     * get file MD5
     * @param pFilePath file absolute path
     * @return file MD5
     * @throws IOException
     */
    public static String getFileMD5String(String pFilePath) throws IOException
    {
        File _File = new File(pFilePath);
        return getFileMD5String(_File);
    }

    /**
     * get file MD5
     * @param pFile file object
     * @return file MD5
     * @throws IOException
     */
    public static String getFileMD5String(File pFile) throws IOException
    {
        FileInputStream _In = new FileInputStream(pFile);
        FileChannel _FileChannel = _In.getChannel();
        MappedByteBuffer _ByteBuffer =
            _FileChannel.map(FileChannel.MapMode.READ_ONLY, 0, pFile.length());
        mMessageDigest.update(_ByteBuffer);
        _In.close();
        return bufferToHex(mMessageDigest.digest());
    }

    private static String bufferToHex(byte pBytes[])
    {
        return bufferToHex(pBytes, 0, pBytes.length);
    }

    private static String bufferToHex(byte pBytes[], int pM, int pN)
    {
        StringBuffer _StrBuffer = new StringBuffer(2 * pN);
        int _K = pM + pN;
        for (int _L = pM; _L < _K; _L++)
        {
            appendHexPair(pBytes[_L], _StrBuffer);
        }
        return _StrBuffer.toString();
    }

    private static void appendHexPair(byte pByte, StringBuffer pStrBuffer)
    {
        char _C0 = mHexDigits[(pByte & 0xf0) >> 4];
        char _C1 = mHexDigits[pByte & 0xf];
        pStrBuffer.append(_C0);
        pStrBuffer.append(_C1);
    }
}
