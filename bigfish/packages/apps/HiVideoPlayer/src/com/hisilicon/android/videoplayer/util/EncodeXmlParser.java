package com.hisilicon.android.videoplayer.util;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import com.hisilicon.android.videoplayer.R;
import com.hisilicon.android.videoplayer.model.EncodeNameValue;

import android.content.Context;
import android.util.Log;

public class EncodeXmlParser
{
    private Context context;

    private List < List < EncodeNameValue >> encodesList;

    public EncodeXmlParser(Context context)
    {
        this.context = context;
        parser();
    }

    public List < List < EncodeNameValue >> getEncodesList()
    {
        return encodesList;
    }

    public void parser()
    {
        String[] encodeName = context.getResources().getStringArray(
            R.array.subtitle_encode);
        encodesList = new ArrayList < List < EncodeNameValue >> ();
        List <EncodeNameValue> list = new ArrayList <EncodeNameValue>();
        for (int i = 0; i < encodeName.length; i++)
        {
            EncodeNameValue encodeNameValue = new EncodeNameValue();
            encodeNameValue.setEncodeName(encodeName[i]);
            encodeNameValue.setEncodeValue(i);
            list.add(encodeNameValue);
        }

        encodesList.add(list);
    }
}
