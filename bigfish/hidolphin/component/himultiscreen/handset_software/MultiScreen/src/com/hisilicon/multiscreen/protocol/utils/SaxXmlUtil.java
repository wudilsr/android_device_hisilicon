package com.hisilicon.multiscreen.protocol.utils;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.StringWriter;
import java.util.Date;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.sax.SAXTransformerFactory;
import javax.xml.transform.sax.TransformerHandler;
import javax.xml.transform.stream.StreamResult;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.AttributesImpl;
import org.xml.sax.helpers.DefaultHandler;

import android.util.Base64;

import com.hisilicon.multiscreen.protocol.message.Action;
import com.hisilicon.multiscreen.protocol.message.Argument;
import com.hisilicon.multiscreen.protocol.message.ArgumentValue;

/**
 * Utility class for serializing and parsing Action message.<br>
 * CN:序列化和解析Action消息的工具类。
 */
public class SaxXmlUtil
{
    // Xml.Encoding.UTF_8.name() "UTF_8" "UTF-8" "ISO-8859-1"
    public static final String ENCODE_UTF_8 = "UTF-8";

    /**
     * Parse input stream into Action message.<br>
     * CN:将输入流转成Action消息
     * @param inStream input stream to parse.<br>
     *        CN:要解析的输入流
     * @return - Action after parse CN:解析后的Action
     * @throws SAXException CN:SAX异常
     * @throws ParserConfigurationException CN:解析配置异常
     * @throws IOException CN:IO异常
     */
    public Action parse(InputStream inStream) throws ParserConfigurationException, SAXException,
        IOException
    {
        SAXParserFactory saxFactory = SAXParserFactory.newInstance();
        SAXParser saxParser = saxFactory.newSAXParser();
        if (inStream == null)
        {
            return null;
        }
        else
        {
            XMLHandler xmlHandler = new XMLHandler();
            saxParser.parse(inStream, xmlHandler);
            return xmlHandler.getAction();
        }
    }

    /**
     * Parse byte array into Action message.<br>
     * CN:将byte数组转成Action消息。
     * @param msgByte - inStream byte array to parse.<br>
     *        CN:要解析的输入流。
     * @return Action after parse.<br>
     *         CN:解析后的Action。
     * @throws SAXException - Exception of SAX.<br>
     *         CN:SAX异常。
     * @throws ParserConfigurationException - Exception of parser configuration.<br>
     *         CN:解析配置异常。
     * @throws IOException - Exception of IO.<br>
     *         CN:IO异常。
     */
    public Action parse(byte[] msgByte) throws ParserConfigurationException, SAXException,
        IOException
    {
        SAXParserFactory saxFactory = SAXParserFactory.newInstance();
        SAXParser saxParser = saxFactory.newSAXParser();
        if (msgByte == null)
        {
            LogTool.e("msgByte is null");
            return null;
        }
        else
        {
            ByteArrayInputStream vimeMsgInstream = new ByteArrayInputStream(msgByte);
            XMLHandler xmlHandler = new XMLHandler();
            saxParser.parse(vimeMsgInstream, xmlHandler);
            return xmlHandler.getAction();
        }
    }

    /**
     * Serialize Action message into string in xml format <br>
     * CN:将Action消息序列化为xml格式的字符串
     * @param action Action object <br>
     *        CN：Action 对象
     * @return string in xml format after serialize <br>
     *         CN: 序列化后的xml字符串
     * @throws TransformerConfigurationException CN:转换配置异常
     * @throws SAXException CN: SAX异常
     */
    public String serialize(Action action) throws TransformerConfigurationException, SAXException
    {
        if (null == action)
        {
            LogTool.e("action is null");
            return null;
        }
        SAXTransformerFactory factory = (SAXTransformerFactory) TransformerFactory.newInstance();
        TransformerHandler handler = factory.newTransformerHandler();
        Transformer transformer = handler.getTransformer();
        transformer.setOutputProperty(OutputKeys.ENCODING, ENCODE_UTF_8);
        transformer.setOutputProperty(OutputKeys.INDENT, "yes");
        transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "no");

        StringWriter writer = new StringWriter();
        StreamResult result = new StreamResult(writer);
        handler.setResult(result);

        String uri = "";
        String localName = "";
        String qName = "";

        handler.startDocument();

        AttributesImpl attrs = new AttributesImpl();
        char[] ch = null;
        attrs.clear();
        attrs.addAttribute(uri, localName, "id", "String",
            "0x" + Integer.toHexString(action.getId()));
        handler.startElement(uri, localName, "action", attrs);

        handler.startElement(uri, localName, "name", null);
        ch = String.valueOf(action.getName()).toCharArray();
        handler.characters(ch, 0, ch.length);
        handler.endElement(uri, localName, "name");

        attrs.clear();

        if (action.getArgumentList().size() > 0)
        {
            String tmpValue = null;
            attrs.addAttribute(uri, localName, "number", "String",
                String.valueOf(action.getArgumentList().size()));
            handler.startElement(uri, localName, "argumentList", attrs);

            attrs.clear();
            for (int i = 0; i < action.getArgumentList().size(); i++)
            {
                Argument argument = action.getArgument(i);
                attrs.addAttribute(uri, localName, "number", "String",
                    String.valueOf(argument.getArgumentValueList().size()));
                handler.startElement(uri, localName, "argument", attrs);
                attrs.clear();
                for (int j = 0; j < argument.getArgumentValueList().size(); j++)
                {

                    attrs.addAttribute(uri, localName, "name", "String",
                        String.valueOf(argument.getArgumentValue(j).getKey()));
                    ArgumentValue value = argument.getArgumentValue(j);
                    boolean isByteArray = false;
                    if (value.getType().equals("byte[]"))
                    {
                        isByteArray = true;
                    }

                    attrs.addAttribute(uri, localName, "type", "String", value.getType());

                    handler.startElement(uri, localName, "value", attrs);

                    if (value.getVaule() != null)
                    {
                        if (isByteArray)
                        {
                            byte[] data = (byte[]) value.getVaule();
                            tmpValue = Base64.encodeToString(data, Base64.DEFAULT);
                        }
                        else
                        {
                            tmpValue = value.getVaule().toString();
                        }

                        ch = tmpValue.toCharArray();
                        handler.characters(ch, 0, ch.length);
                    }

                    handler.endElement(uri, localName, "value");
                }
                handler.endElement(uri, localName, "argument");
            }
            handler.endElement(uri, localName, "argumentList");
        }

        attrs.clear();
        attrs.addAttribute(uri, localName, "responseFlag", "String",
            String.valueOf(action.getResponseFlag()));
        attrs.addAttribute(uri, localName, "responseId", "String",
            "0x" + Integer.toHexString(action.getResponseId()));
        handler.startElement(uri, localName, "response", attrs);
        handler.endElement(uri, localName, qName);

        handler.endElement(uri, localName, "action");
        handler.endDocument();

        return writer.toString();
    }

}

class XMLHandler extends DefaultHandler
{
    private Action action;

    Argument argument = null;

    ArgumentValue value = null;

    String myString = null;

    public Action getAction()
    {
        return action;
    }

    public void startDocument()
    {
        try
        {
            super.startDocument();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

    }

    public void endDocument() throws SAXException
    {
        super.endDocument();
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes)
        throws SAXException
    {
        super.startElement(uri, localName, qName, (org.xml.sax.Attributes) attributes);
        myString = null;

        if ("action".equals(localName))
        {
            action = new Action();
            action.setId(Integer.decode(attributes.getValue("id")));
        }
        else if ("response".equals(localName))
        {
            action.setResponseFlag(attributes.getValue("responseFlag"));
            action.setResponseId(Integer.decode(attributes.getValue("responseId")));
        }
        else if ("value".equals(localName))
        {
            value = new ArgumentValue();
            value.setKey(attributes.getValue("name"));
            value.setType(attributes.getValue("type"));

        }
        else if ("argument".equals(localName))
        {
            argument = new Argument();
            argument.setArgumentValueNum(Integer.decode(attributes.getValue("number")));
        }

    }

    @Override
    public void characters(char[] ch, int start, int length) throws SAXException
    {
        super.characters(ch, start, length);
        if (myString == null)
        {
            myString = String.valueOf(ch, start, length);
        }
        else
        {
            myString += String.valueOf(ch, start, length);
        }

    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException
    {
        super.endElement(uri, localName, qName);

        if ("name".equals(localName))
        {
            action.setName(myString);
        }
        else if (localName.equals("value"))
        {
            if (value.getType().equals("Integer"))
            {
                Integer mInteger = Integer.valueOf(myString);
                value.setValue(mInteger);
            }
            else if (value.getType().equals("Short"))
            {
                Short mShort = new Short(myString);
                value.setValue(mShort);
            }
            else if (value.getType().equals("Byte"))
            {
                Byte mByte = new Byte(myString);
                value.setValue(mByte);
            }
            else if (value.getType().equals("Long"))
            {
                // Long mLong = new Long(myString);
                Long mLong = Long.valueOf(myString);
                value.setValue(mLong);
            }
            else if (value.getType().equals("Float"))
            {
                // Float mFloat = new Float(myString);
                Float mFloat = Float.valueOf(myString);
                value.setValue(mFloat);
            }
            else if (value.getType().equals("Double"))
            {
                // Double mDouble = new Double(myString);
                Double mDouble = Double.valueOf(myString);
                value.setValue(mDouble);
            }
            else if (value.getType().equals("Boolean"))
            {
                // Boolean mBoolean = new Boolean(myString);
                Boolean mBoolean = Boolean.valueOf(myString);
                value.setValue(mBoolean);
            }
            else if (value.getType().equals("Date"))
            {
                Date mDate = new Date(myString);
                value.setValue(mDate);
            }
            else if (value.getType().equals("String"))
            {
                myString = SpecialCharUtil.getSpecialChar(myString);
                value.setValue(myString);
            }
            else if (value.getType().equals("byte[]"))
            {
                byte[] data = Base64.decode(myString, Base64.DEFAULT);
                value.setValue(data);
            }
            else
            {
                LogTool.e("vaule is other type " + value.getType());
            }

            argument.addArgumentValue(value);
        }
        else if (localName.equals("argument"))
        {
            action.addArgument(argument);
        }

        myString = null;
    }

}
