package com.hisilicon.android.videoplayer.control.base;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.xml.sax.SAXException;

import com.hisilicon.android.videoplayer.utility.FileTool;
import com.hisilicon.android.videoplayer.utility.LogTool;

public class SubtitleXmlParser
{
    private String mOriFilePath = "/system/etc/default_font_config.xml";

    private String mNewFilePath = "";

    private DocumentBuilderFactory mDocumentBuilderFactory;

    private DocumentBuilder mDocumentBuilder;

    private Document mDocument;

    public SubtitleXmlParser(String pNewFilePath)
    {
        mNewFilePath = pNewFilePath;
    }

    public List<Map<String, String>> getAttrMapList()
    {
        NamedNodeMap _FontNodeMap = getFontNodeFromXml();
        if (_FontNodeMap == null)
        {
            return null;
        }

        List<Map<String, String>> _AttrMapList = new ArrayList<Map<String, String>>();
        Map<String, String> _AttrMap;
        Node _AttrNode;

        for (int i = 0; i < _FontNodeMap.getLength(); i++)
        {
            _AttrNode = _FontNodeMap.item(i);
            _AttrMap = new HashMap<String, String>();
            _AttrMap.put(_AttrNode.getNodeName(), _AttrNode.getNodeValue());
            _AttrMapList.add(_AttrMap);
        }

        return _AttrMapList;
    }

    public String[] getAttrValues()
    {
        NamedNodeMap _FontNodeMap = getFontNodeFromXml();
        if (_FontNodeMap == null)
        {
            return null;
        }

        String[] _Values = new String[_FontNodeMap.getLength()];

        for (int i = 0; i < _FontNodeMap.getLength(); i++)
        {
            _Values[i] = _FontNodeMap.item(i).getNodeValue();
        }

        return _Values;
    }

    public void setAttrValues(List<?> pList)
    {
        if (pList == null)
        {
            return;
        }

        NamedNodeMap _FontNodeMap = null;
        Node _AttrNode = null;

        _FontNodeMap = getFontNodeFromXml();
        if (_FontNodeMap == null)
        {
            return;
        }

        for (int i = 1; i < _FontNodeMap.getLength(); i++)
        {
            _AttrNode = _FontNodeMap.item(i);
            String _AttrValue = pList.get(i).toString();
            if (!("-1".equals(_AttrValue)))
            {
                _AttrNode.setNodeValue(_AttrValue);
            }
        }

        try
        {
            TransformerFactory _TransformerFactory = TransformerFactory.newInstance();
            Transformer _Transformer = _TransformerFactory.newTransformer();
            DOMSource _Source = new DOMSource(mDocument);
            PrintWriter _Pw = new PrintWriter(new File(mNewFilePath));
            StreamResult _Result = new StreamResult(_Pw);
            _Transformer.transform(_Source, _Result);
            _Pw.close();
        }
        catch (TransformerConfigurationException e)
        {
            e.printStackTrace();
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (TransformerException e)
        {
            e.printStackTrace();
        }
    }

    public NamedNodeMap getFontNodeFromXml()
    {
        File _File = new File(mNewFilePath);
        if (_File != null)
        {
            try
            {
                mDocumentBuilderFactory = DocumentBuilderFactory.newInstance();
                mDocumentBuilder = mDocumentBuilderFactory.newDocumentBuilder();
                mDocument = mDocumentBuilder.parse(_File);

                Node _FontNode = mDocument.getElementsByTagName("font").item(0);
                return (_FontNode.getAttributes());

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
        }

        return null;
    }

    public void copyXmlFile()
    {
        File _OriFile = new File(mOriFilePath);
        File _NewFile = new File(mNewFilePath);

        if (_NewFile.exists())
        {
            LogTool.e("new file exists");
            return;
        }

        try
        {
            FileTool.cp(_OriFile, _NewFile);
            LogTool.i("copy xml file successed");

            Process _Process = Runtime.getRuntime().exec("chmod 666 " + mNewFilePath);
            int _Status = _Process.waitFor();
            if (_Status == 0)
            {
                LogTool.i("chmod successed");
            }
        }
        catch (IOException e)
        {
            LogTool.e("copy xml file failed");
            e.printStackTrace();
        }
        catch (InterruptedException e)
        {
            LogTool.e("copy xml file failed");
            e.printStackTrace();
        }
    }
}
