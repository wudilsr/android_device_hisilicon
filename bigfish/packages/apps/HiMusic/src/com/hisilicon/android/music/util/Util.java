package com.hisilicon.android.music.util;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.apache.commons.httpclient.Header;
import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.URI;
import org.apache.commons.httpclient.UsernamePasswordCredentials;
import org.apache.commons.httpclient.auth.AuthScope;
import org.apache.commons.httpclient.methods.GetMethod;
import org.apache.http.client.utils.URLEncodedUtils;

import com.hisilicon.android.music.MediaPlaybackActivity;

import android.os.Environment;
import android.util.Log;

/**
 * A utility class, is mainly responsible for the analysis of lyricsAnd find
 * lyrics download, and then save the file into a standard formatThere are some
 * commonly used method
 * @author
 */
public final class Util {

    public static String VERSION = "1.2";
    private static Logger log = Logger.getLogger(Util.class.getName());
    private static String proxyHost = "";
    private static String proxyPort = "";
    private static String proxyUserName = "";
    private static String proxyPwd = "";

    private Util() {
    }

    /**
     * According to the remote access to the version and the version now
     * contrast can update
     * @param remote
     *            version
     * @return is updated
     */
    private static boolean canUpdate(String version) {
        if (version == null) {
            return false;
        }
        return VERSION.compareTo(version) < 0;
    }

    /**
     * A simple method to get pass, the singer and the lyrics of the title
     * search results, return to a list form
     * @param artist
     * @param title
     *            , not null
     * @return
     */
    public static List<SearchResult> getSearchResults(String artist,
            String title) {
        List<SearchResult> list = new ArrayList<SearchResult>();
        try {
            list = LrcUtil.search(artist, title);
        } catch (Exception ex) {
            Logger.getLogger(Util.class.getName()).log(Level.SEVERE, null, ex);
        }
        return list;
    }

    /**
     * From a int worth it to represent the number of bytes
     * @param i
     * @return byte[]
     */
    public static byte[] getBytesFromInt(int i) {
        byte[] data = new byte[4];
        data[0] = (byte) (i & 0xff);
        data[1] = (byte) ((i >> 8) & 0xff);
        data[2] = (byte) ((i >> 16) & 0xff);
        data[3] = (byte) ((i >> 24) & 0xff);
        return data;
    }

    /**
     * A simple method, turn into another string of a string
     * @param source
     * @param encoding
     * @return String
     */
    public static String convertString(String source, String encoding) {
        try {
            byte[] data = source.getBytes("ISO8859-1");
            return new String(data, encoding);
        } catch (UnsupportedEncodingException ex) {
            return source;
        }
    }

    /**
     * A convenient method of transcoding
     * @param source
     * @param sourceEnc
     * @param distEnc
     * @return
     */
    public static String convertString(String source, String sourceEnc,
            String distEnc) {
        try {
            byte[] data = source.getBytes(sourceEnc);
            return new String(data, distEnc);
        } catch (UnsupportedEncodingException ex) {
            return source;
        }
    }

    /**
     * This array of integer size from incoming number
     * @param data
     *            byte[]
     * @return integer
     */
    public static int getInt(byte[] data) {
        if (data.length != 4) {
            throw new IllegalArgumentException(
                    "The length of the array to be illegal, length 4!");
        }
        return (data[0] & 0xff) | ((data[1] & 0xff) << 8)
                | ((data[2] & 0xff) << 16) | ((data[3] & 0xff) << 24);
    }

    /**
     * The byte array composed of long integer results from incoming byte array
     * @param data
     *            byte[]
     * @return long
     */
    public static long getLong(byte[] data) {
        if (data.length != 8) {
            throw new IllegalArgumentException(
                    "The length of the array to be illegal, length 4!");
        }
        return (data[0] & 0xff) | ((data[1] & 0xff) << 8)
                | ((data[2] & 0xff) << 16) | ((data[3] & 0xff) << 24)
                | ((data[4] & 0xff) << 32) | ((data[5] & 0xff) << 40)
                | ((data[6] & 0xff) << 48) | ((data[7] & 0xff) << 56);
    }

    /**
     * Get file Type
     * @param f
     *            File
     * @return Type
     */
    public static String getType(File f) {
        String name = f.getName();
        return name.substring(name.lastIndexOf(".") + 1);
    }

    /**
     * According to the file return the name of the song
     * @param f
     *            file
     * @return the name of the song
     */
    public static String getSongName(File f) {
        String name = f.getName();
        name = name.substring(0, name.lastIndexOf("."));
        return name;
    }

    /**
     * According to the file name return the name of the song
     * @param name
     *            file name
     * @return the name of the song
     */
    public static String getSongName(String name) {
        try {
            int index = name.lastIndexOf(File.separator);
            name = name.substring(index + 1, name.lastIndexOf("."));
            return name;
        } catch (Exception exe) {
            return name;
        }

    }

    /**
     * According to the information content of the lyrics of songs to download
     * @param fileName
     * @param info
     * @return Lyric
     */
    public static String getLyric(Audio info) throws IOException {
        String ly = null;
        if (ly != null) {
        } else {
            ly = getLyricInternet(info);
        }
        return ly;

    }

    /**
     * Search the lyrics from the TT player on the server
     * @param info
     * @return Lyric
     * @throws java.io.IOException
     */
    private static String getLyricTTPlayer(Audio info) throws IOException {
        List<SearchResult> list = LrcUtil.search(info);
        if (list.isEmpty()) {
            return null;
        } else {
            return list.get(0).getContent();
        }
    }

    /**
     * The string that flow from a stream.
     * @param is
     *            InputStream
     * @return String
     */
    private static String getString(InputStream is) {
        InputStreamReader r = null;
        try {
            StringBuilder sb = new StringBuilder();
            r = new InputStreamReader(is, "GBK");
            char[] buffer = new char[128];
            int length = -1;
            while ((length = r.read(buffer)) != -1) {
                sb.append(new String(buffer, 0, length));
            }
            return sb.toString();
        } catch (Exception ex) {
            Logger.getLogger(Util.class.getName()).log(Level.SEVERE, null, ex);
            return "";
        } finally {
            try {
                r.close();
            } catch (Exception ex) {
                Logger.getLogger(Util.class.getName()).log(Level.SEVERE, null,
                        ex);
            }
        }
    }

    /**
     * The number of seconds to convert a string like 00:00
     * @param sec
     *            seconds
     * @return string
     */
    public static String secondToString(int sec) {
        DecimalFormat df = new DecimalFormat("00");
        StringBuilder sb = new StringBuilder();
        sb.append(df.format(sec / 60)).append(":").append(df.format(sec % 60));
        return sb.toString();
    }

    /**
     * Get the contents of URL, it is best used for Baidu
     * @param url
     *            URL
     * @return contents
     * @throws java.lang.Exception
     */
    private static String getURLContent(String url) throws IOException {
        HttpClient http = new HttpClient();
        if (true) {
            if (proxyUserName != null && proxyPwd != null) {
                http.getState()
                        .setProxyCredentials(
                                new AuthScope(proxyHost,
                                        Integer.parseInt(proxyPort)),
                                new UsernamePasswordCredentials(proxyUserName,
                                        proxyPwd));
            }
            http.getHostConfiguration().setProxy(proxyPort,
                    Integer.parseInt(proxyPort));
        }
        http.getParams().setContentCharset("GBK");
        GetMethod get = new GetMethod();
        URI uri = new URI(url, false, "GBK");
        get.setURI(uri);
        http.executeMethod(get);
        Header[] hs = get.getResponseHeaders();
        return getString(get.getResponseBodyAsStream());

    }

    /**
     * Get to the lyrics in Baidu search content
     * @param key
     * @return content
     * @throws java.lang.Exception
     */
    private static String getInternet_Lyric(String key, String artist)
            throws Exception {
        URL url = null;
        StringBuffer sb = new StringBuffer();
        // Lynnfield if Chinese characters, then to encode conversion
        String key_url = "";
        String artist_url = "";
        try {
            key_url = URLEncoder.encode(key, "utf-8");
            artist_url = URLEncoder.encode(artist, "utf-8");
        } catch (UnsupportedEncodingException e2) {
            // TODO Auto-generated catch block
            e2.printStackTrace();
        }

        String strUrl = "http://box.zhangmen.baidu.com/x?op=12&count=1&title="
                + key_url + "$$" + artist_url + "$$$$";

        Log.i("getInternet_Lyric","strUrl:"+strUrl);

        try {
            url = new URL(strUrl);
        } catch (Exception e1) {
            e1.printStackTrace();
        }
        BufferedReader br = null;
        String s;

        try {
            HttpURLConnection httpConn = (HttpURLConnection) url
                    .openConnection();
            httpConn.connect();
            InputStreamReader inReader = new InputStreamReader(
                    httpConn.getInputStream());
            br = new BufferedReader(inReader);
        } catch (IOException e1) {
            e1.printStackTrace();
        }

        try {
            while ((s = br.readLine()) != null) {
                sb.append(s + "/r/n");
                br.close();
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        int begin = 0, end = 0, number = 0;
        String strid = "";
        begin = sb.indexOf("<lrcid>");
        if (begin != -1) {
            end = sb.indexOf("</lrcid>", begin);
            strid = sb.substring(begin + 7, end);
            number = Integer.parseInt(strid);
        }
        String geciURL = "http://box.zhangmen.baidu.com/bdlrc/" + number / 100
                + "/" + number + ".lrc";
        String ss = new String();
        try {
            url = new URL(geciURL);
        } catch (MalformedURLException e2) {
            e2.printStackTrace();
        }
        StringBuffer sbLrc = new StringBuffer();
        ArrayList<String> gcContent = new ArrayList<String>();
        BufferedReader brs = null;
        try {
            brs = new BufferedReader(new InputStreamReader(url.openStream(),
                    "GB2312"));
        } catch (IOException e1) {
            e1.printStackTrace();
        }
        if (brs == null) {
        } else {
            try {
                while ((ss = brs.readLine()) != null) {
                    sbLrc.append(ss);
                    gcContent.add(ss);
                }
                brs.close();
                saveLyric(gcContent, key, artist);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return sbLrc.toString();
    }

    /**
     * Download the lyrics saved, lest the next to find
     * @param lyric
     * @param info
     */
    private static void saveLyric(ArrayList<String> lrcList, String title,
            String artist) {
        try {
            // If the singer is not empty, the singers name + song for the best
            // combination
            String name = artist + "-" + title + ".lrc";
            File dir = new File(MediaPlaybackActivity.HOME, "Lyrics"
                    + File.separator);
            dir.mkdirs();
            File file = new File(dir, name);
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(
                    new FileOutputStream(file), "GBK"));
            for (int i = 0; i < lrcList.size(); i++) {
                bw.write(lrcList.get(i));
                bw.newLine();
            }
            bw.close();
        } catch (Exception exe) {

        }
    }

    /**
     * delete HTML tag
     * @param str1
     * @return String
     */
    public static String htmlTrim(String str1) {
        String str = "";
        str = str1;
        str = str.replaceAll("</?[^>]+>", "");
        str = str.replaceAll("\\s", "");
        str = str.replaceAll("&nbsp;", "");
        str = str.replaceAll("&amp;", "&");
        str = str.replace(".", "");
        str = str.replace("\"", "‘");
        str = str.replace("'", "‘");
        return str;
    }

    private static String htmlTrim2(String str1) {
        String str = "";
        str = str1;
        str = str.replaceAll("<BR>", "\n");
        str = str.replaceAll("<br>", "\n");
        str = str.replaceAll("</?[^>]+>", "");
        return str;
    }

    /**
     * To search the lyrics from Baidu
     * @param info
     * @return
     */
    private static String getLyricInternet(Audio info) {
        try {
            String song = info.getArtist();
            String name = info.getFormattedName();
            String s = getInternet_Lyric(name, song);
            return s;
        } catch (Exception ex) {
            return null;
        }
    }

    static enum Test {

        Album, TITLE;
    }

}
