package com.hisilicon.android.music.util;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

import android.util.Log;

import com.hisilicon.android.music.util.SearchResult.Task;

/**
 * @author
 */
public final class GAEUtil {

    private static final String getSingleResultURL = "";
    private static final String getLyricContentURL = "";
    private static final String getResultListURL = "";
    private static final String voteURL = "";
    private static final String versionURL = "";
    private static final Logger log = Logger.getLogger(GAEUtil.class.getName());

    public static List<SearchResult> getSearchResult(String artistParam,
            String titleParam) throws Exception {
        String urlContent = MessageFormat.format(getResultListURL,
                $(artistParam), $(titleParam));
        ObjectInputStream ois = getObjectInputStream(urlContent);
        int back = ois.readInt();
        List<SearchResult> list = new ArrayList<SearchResult>();
        if (back == 1) {
            int size = ois.readInt();
            for (int i = 0; i < size; i++) {
                final String artist = ois.readUTF();
                final String lrcCode = ois.readUTF();
                final String lrcId = ois.readUTF();
                final String title = ois.readUTF();
                final String id = ois.readUTF();
                final Task task = new Task() {

                    public String getLyricContent() {
                        return getLyricContent_S(id, lrcId, lrcCode, artist,
                                title);
                    }
                };
                list.add(new SearchResult(id, lrcId, lrcCode, artist, title,
                        task));
            }
        }
        return list;
    }

    private static String getSingleResult(String artistParam, String titleParam)
            throws Exception {
        String urlContent = MessageFormat.format(getSingleResultURL,
                $(artistParam), $(titleParam));
        ObjectInputStream ois = getObjectInputStream(urlContent);
        int back = ois.readInt();
        if (back == 1) {
            return ois.readUTF();
        } else {
            return null;
        }
    }

    private static String getLyricContent_S(String id, String lrcId,
            String lrcCode, String artist, String title) {
        try {
            String urlContent = MessageFormat.format(getLyricContentURL, $(id),
                    $(lrcId), $(lrcCode), $(artist), $(title));
            ObjectInputStream ois = getObjectInputStream(urlContent);
            int back = ois.readInt();
            if (back == 1) {
                return ois.readUTF();
            } else {
                return "";
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            return "";
        }
    }

    private static ObjectInputStream getObjectInputStream(String urlContent)
            throws Exception {
        URL url = new URL(urlContent);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        ObjectInputStream ois = new ObjectInputStream(conn.getInputStream());
        return ois;
    }

    private static String $(String s) throws UnsupportedEncodingException {
        return URLEncoder.encode(s, "GBK");
    }
}
