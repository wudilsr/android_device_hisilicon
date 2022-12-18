package com.android.factorytest;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.StringWriter;
import java.util.ArrayList;
import java.util.List;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlSerializer;

import android.util.Xml;

public class XmlParser {
    public static List<String> parse(FileInputStream is) throws Exception {
        List<String> mlist = new ArrayList<String>();
        XmlPullParser parser = Xml.newPullParser();
        parser.setInput(is, "UTF-8");
        int eventType = parser.getEventType();
        while (eventType != XmlPullParser.END_DOCUMENT) {
            switch (eventType) {
            case XmlPullParser.START_DOCUMENT:
                break;
            case XmlPullParser.START_TAG:
                if (parser.getName().equals("mac_begin")) {
                    eventType = parser.next();
                    mlist.add(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("mac_current")) {
                    eventType = parser.next();
                    mlist.add(parser.getText().trim());
                    break;
                } else if (parser.getName().equals("mac_end")) {
                    eventType = parser.next();
                    mlist.add(parser.getText().trim());
                    break;
                }
            case XmlPullParser.END_TAG:
                break;
            }
            eventType = parser.next();
        }
        is.close();
        return mlist;
    }

    public static String write(List<String> list) {
        StringWriter xmlWriter = new StringWriter();
        XmlSerializer xmlSerializer = Xml.newSerializer();
        try {
            xmlSerializer.setOutput(xmlWriter);
            xmlSerializer.startDocument("UTF-8", true);
            xmlSerializer.startTag(null, "Action");
            xmlSerializer.startTag(null, "mac_begin");
            xmlSerializer.text(list.get(0));
            xmlSerializer.endTag(null, "mac_begin");
            xmlSerializer.startTag(null, "mac_current");
            xmlSerializer.text(list.get(1));
            xmlSerializer.endTag(null, "mac_current");
            xmlSerializer.startTag(null, "mac_end");
            xmlSerializer.text(list.get(2));
            xmlSerializer.endTag(null, "mac_end");
            xmlSerializer.endTag(null, "Action");
            xmlSerializer.endDocument();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return xmlWriter.toString();
    }

}