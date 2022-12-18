package com.hisilicon.android.videoplayer.utility;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Locale;

public class FileTool
{
    public static void cp(String from, String to) throws IOException
    {
        cp(new File(from), new File(to));
    }

    public static void cp(File from, File to) throws IOException
    {
        cp(new FileInputStream(from), new FileOutputStream(to));
    }

    public static void cp(InputStream in, String to) throws IOException
    {
        cp(in, new FileOutputStream(new File(to)));
    }

    public static void cp(InputStream in, OutputStream out) throws IOException
    {
        // 1K byte buffer
        byte[] buf = new byte[1024];
        int count;
        while ((count = in.read(buf)) != -1)
        {
            out.write(buf, 0, count);
        }
        in.close();
        out.close();
    }

    public static String getExtension(File pFile)
    {
        String _FileName = pFile.getName();
        String _Extension = " ";
        if (_FileName != null && _FileName.length() > 0)
        {
            int _DotIndex = _FileName.lastIndexOf('.');
            if (_DotIndex > -1 && (_DotIndex < _FileName.length() - 1))
            {
                _Extension = _FileName.substring(_DotIndex + 1).toLowerCase(Locale.getDefault());
            }
        }

        return _Extension;
    }
}
