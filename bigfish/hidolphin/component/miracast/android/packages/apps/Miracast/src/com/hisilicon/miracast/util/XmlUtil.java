package com.hisilicon.miracast.util;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlSerializer;

import android.util.Xml;
import com.hisilicon.miracast.model.Hdcp;

public class XmlUtil
{
    public static Hdcp getHdcpInfo(InputStream xml) throws Exception
    {
        Hdcp hdcp = null;
        XmlPullParser pullParser = Xml.newPullParser();
        pullParser.setInput(xml, "UTF-8");
        int event = pullParser.getEventType();

        while (event != XmlPullParser.END_DOCUMENT)
        {
            switch (event)
            {
                case XmlPullParser.START_DOCUMENT:
                    break;
                case XmlPullParser.START_TAG:
                    if ("name".equals(pullParser.getName()))
                    {
                        hdcp = new Hdcp();
                        String hdcpName = pullParser.nextText();
                        hdcp.setHdcpName(hdcpName);
                    }
                    if ("mode".equals(pullParser.getName()))
                    {
                        int hdcpMode= Integer.valueOf(pullParser.nextText());
                        hdcp.setHdcpMode(hdcpMode);
                    }
                    break;

                case XmlPullParser.END_TAG:
                    break;

            }

            event = pullParser.next();
        }

        return hdcp;
    }

}
