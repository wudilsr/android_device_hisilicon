package com.hisilicon.android.music.util;

import java.util.Arrays;

/**
 * @author
 */
@SuppressWarnings("unchecked")
public class FileUtil {

    public static String padString(String s, int length) {
        return padString(s, ' ', length);
    }

    public static String padString(String s, char padChar, int length) {
        int slen, numPads = 0;
        if (s == null) {
            s = "";
            numPads = length;
        } else if ((slen = s.length()) > length) {
            s = s.substring(0, length);
        } else if (slen < length) {
            numPads = length - slen;
        }
        if (numPads == 0) {
            return s;
        }
        char[] c = new char[numPads];
        Arrays.fill(c, padChar);
        return s + new String(c);
    }

    public static String rightPadString(String s, int length) {
        return (rightPadString(s, ' ', length));
    }

    public static String rightPadString(String s, char padChar, int length) {
        int slen, numPads = 0;
        if (s == null) {
            s = "";
            numPads = length;
        } else if ((slen = s.length()) > length) {
            s = s.substring(length);
        } else if (slen < length) {
            numPads = length - slen;
        }
        if (numPads == 0) {
            return (s);
        }
        char[] c = new char[numPads];
        Arrays.fill(c, padChar);
        return new String(c) + s;
    }
}
