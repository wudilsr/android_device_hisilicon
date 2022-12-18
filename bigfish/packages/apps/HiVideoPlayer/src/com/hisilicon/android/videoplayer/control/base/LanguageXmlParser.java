package com.hisilicon.android.videoplayer.control.base;

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

import android.content.Context;

import com.hisilicon.android.videoplayer.R;
import com.hisilicon.android.videoplayer.model.ModelLanguage;

public class LanguageXmlParser
{
    private Context mContext;

    private List<ModelLanguage> mModelLanguageList;

    public LanguageXmlParser(Context pContext)
    {
        mContext = pContext;
        parseXml();
    }

    private void parseXml()
    {
        mModelLanguageList = new ArrayList<ModelLanguage>();
        InputStream _InputStream = mContext.getResources().openRawResource(R.raw.language);

        if (_InputStream == null)
        {
            return;
        }

        DocumentBuilderFactory _Factory = null;
        DocumentBuilder _Builder = null;
        Document _Doc = null;

        try
        {
            _Factory = DocumentBuilderFactory.newInstance();
            _Builder = _Factory.newDocumentBuilder();
            _Doc = _Builder.parse(_InputStream);
            _InputStream.close();
        }
        catch (ParserConfigurationException e)
        {
            e.printStackTrace();
        }
        catch (SAXException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        finally
        {
            _InputStream = null;
        }

        Element _Element = _Doc.getElementById("1");
        NodeList _NodeList = _Element.getChildNodes();

        for (int i = 0; i < _NodeList.getLength(); i++)
        {
            Node _Node = _NodeList.item(i);

            if (_Node.getNodeName().equals("nation"))
            {
                NamedNodeMap _NamedNodeMap = _Node.getAttributes();
                mModelLanguageList.add(new ModelLanguage(_NamedNodeMap.item(0).getNodeValue(),
                    _NamedNodeMap.item(1).getNodeValue()));
            }
        }
    }

    public String getLanguage(String pAbb)
    {
        String _Lang = pAbb;

        if (!mModelLanguageList.isEmpty())
        {
            for (ModelLanguage _ModelLanguage : mModelLanguageList)
            {
                if (_ModelLanguage.getAbb().equals(pAbb))
                {
                    _Lang = _ModelLanguage.getLang();
                    break;
                }
            }
        }

        return _Lang;
    }
}
