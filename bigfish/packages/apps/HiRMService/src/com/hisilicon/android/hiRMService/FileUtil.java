package com.hisilicon.android.hiRMService;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class FileUtil {

    public File createSDFile(String fileName) throws IOException {
        File file = new File(fileName);
        file.createNewFile();
        return file;
    }

    public File createSDDir(String dirName) {
        File dir = new File(dirName);
        dir.mkdir();
        return dir;
    }

    public void delExistFile(String fileName) {
        File file = new File(fileName);
        if (file.exists()) {
            file.delete();
        }
    }

    public File write2SDFromInput(String path, String fileName,
            InputStream input) {
        File file = null;
        OutputStream output = null;
        int size = 0;
        try {
            file = new File(path, fileName);
            file.createNewFile();
            output = new FileOutputStream(file);
            byte buffer[] = new byte[4 * 1024];
            while ((size = input.read(buffer)) != -1) {
                output.write(buffer, 0, size);
            }
            output.flush();
        } catch (Exception e) {
            file.delete();
            file = null;
            e.printStackTrace();
        } finally {
            try {
                output.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return file;
    }
}