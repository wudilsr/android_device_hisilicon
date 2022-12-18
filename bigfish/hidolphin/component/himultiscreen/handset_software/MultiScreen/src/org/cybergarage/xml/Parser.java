/******************************************************************
 *
 *    CyberXML for Java
 *
 *    Copyright (C) Satoshi Konno 2002
 *
 *    File: Parser.java
 *
 *    Revision;
 *
 *    11/26/2003
 *        - first revision.
 *    03/30/2005
 *        - Change parse(String) to use StringBufferInputStream instead of URL.
 *    11/11/2009
 *        - Changed Parser::parser() to use ByteArrayInputStream instead of StringBufferInputStream because of bugs in Android v1.6.
 *
 ******************************************************************/

package org.cybergarage.xml;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URISyntaxException;
import java.net.URL;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
import org.cybergarage.http.HTTP;
import org.cybergarage.http.HTTPRequest;
import org.cybergarage.http.HTTPResponse;
import org.cybergarage.http.HTTPServer;
import org.cybergarage.util.Debug;

import android.os.Build;

public abstract class Parser
{
    // //////////////////////////////////////////////
    // Constructor
    // //////////////////////////////////////////////

    public Parser()
    {
    }

    // //////////////////////////////////////////////
    // parse
    // //////////////////////////////////////////////

    public abstract Node parse(InputStream inStream) throws ParserException;

    // //////////////////////////////////////////////
    // parse (URL)
    // //////////////////////////////////////////////

    public Node parse(URL locationURL) throws ParserException
    {
        String host = locationURL.getHost();
        int port = locationURL.getPort();
        // Thanks for Hao Hu
        if (port == -1)
            port = 80;
        String uri = locationURL.getPath();

        Node rootElem = getRootNode(locationURL);

        if (rootElem != null)
        {
            return rootElem;
        }
        Debug.message("Get root node fail");

        // comment for on android 2.3,the connection may be blocked.

        // try {
        // HttpURLConnection urlCon =
        // (HttpURLConnection)locationURL.openConnection();
        // urlCon.setRequestMethod("GET");
        // urlCon.setRequestProperty(HTTP.CONTENT_LENGTH,"0");
        // // Modify for HiMultiScreen
        // urlCon.setConnectTimeout(HTTPServer.DEFAULT_CONNECT_TIMEOUT);
        // urlCon.setReadTimeout(HTTPServer.DEFAULT_TIMEOUT);
        // // end modify
        // if (host != null)
        // urlCon.setRequestProperty(HTTP.HOST, host);
        //
        // InputStream urlIn = urlCon.getInputStream();
        //
        // Node rootElem = parse(urlIn);
        //
        // urlIn.close();
        // urlCon.disconnect();
        //
        // return rootElem;
        //
        // } catch (Exception e) {
        // //throw new ParserException(e);
        // }

        HTTPRequest httpReq = new HTTPRequest();
        httpReq.setMethod(HTTP.GET);
        httpReq.setURI(uri);
        HTTPResponse httpRes = httpReq.post(host, port);
        if (httpRes.isSuccessful() == false)
            throw new ParserException("HTTP comunication failed: no answer from peer."
                + "Unable to retrive resoure -> " + locationURL.toString());
        String content = new String(httpRes.getContent());
        ByteArrayInputStream strBuf = new ByteArrayInputStream(content.getBytes());
        return parse(strBuf);
    }

    // //////////////////////////////////////////////
    // parse (File)
    // //////////////////////////////////////////////

    public Node parse(File descriptionFile) throws ParserException
    {
        try
        {
            InputStream fileIn = new FileInputStream(descriptionFile);
            Node root = parse(fileIn);
            fileIn.close();
            return root;

        }
        catch (Exception e)
        {
            throw new ParserException(e);
        }
    }

    // //////////////////////////////////////////////
    // parse (Memory)
    // //////////////////////////////////////////////

    public Node parse(String descr) throws ParserException
    {
        try
        {
            InputStream decrIn = new ByteArrayInputStream(descr.getBytes());
            Node root = parse(decrIn);
            return root;
        }
        catch (Exception e)
        {
            throw new ParserException(e);
        }
    }

    public Node getRootNode(URL locationURL)
    {
        Node rootElem = null;
        if (android.os.Build.VERSION.SDK_INT < Build.VERSION_CODES.HONEYCOMB)
        {
            rootElem = GetRootElemFromApachHttp(locationURL);
        }
        else
        {
            rootElem = GetRootElemFromCyberHttp(locationURL);
        }
        return rootElem;
    }

    // ///////////////////////////////////////////////////////////
    // Get rootElem for platform version higher Android HONEYCOMB
    // ///////////////////////////////////////////////////////////
    public Node GetRootElemFromCyberHttp(URL locationURL)
    {
        Node rootElem = null;
        HttpURLConnection urlCon = null;
        InputStream urlIn = null;
        String host = locationURL.getHost();
        int port = locationURL.getPort();
        // Thanks for Hao Hu
        if (port == -1)
            port = 80;
        String uri = locationURL.getPath();
        try
        {
            urlCon = (HttpURLConnection) locationURL.openConnection();
            urlCon.setRequestMethod("GET");
            urlCon.setRequestProperty(HTTP.CONTENT_LENGTH, "0");
            // Modify for HiMultiScreen
            urlCon.setConnectTimeout(HTTPServer.DEFAULT_CONNECT_TIMEOUT);
            urlCon.setReadTimeout(HTTPServer.DEFAULT_TIMEOUT);
            urlCon.connect();
            // end modify
            if (host != null)
                urlCon.setRequestProperty(HTTP.HOST, host);
            urlIn = urlCon.getInputStream();
            rootElem = parse(urlIn);
        }
        catch (Exception e)
        {
            Debug.message(e.getMessage());
        }

        finally
        {
            if (urlIn != null)
            {
                try
                {
                    urlIn.close();
                }
                catch (IOException e)
                {
                    Debug.message(e.getMessage());
                }
            }
            if (urlCon != null)
            {
                urlCon.disconnect();
            }
        }
        return rootElem;
    }

    // ///////////////////////////////////////////////////////////////
    // Get rootElem for platform version higher than Android HONEYCOMB
    // ///////////////////////////////////////////////////////////////
    public Node GetRootElemFromApachHttp(URL locationURL)
    {
        Node rootElem = null;
        HttpParams httpParameters = new BasicHttpParams();
        HttpConnectionParams.setConnectionTimeout(httpParameters,
            HTTPServer.DEFAULT_CONNECT_TIMEOUT);
        HttpConnectionParams.setSoTimeout(httpParameters, HTTPServer.DEFAULT_TIMEOUT);

        HttpGet httpget = null;
        DefaultHttpClient httpClient = null;
        HttpResponse response = null;
        InputStream urlIn = null;
        try
        {
            httpget = new HttpGet(locationURL.toURI());
            httpClient = new DefaultHttpClient();
            httpClient.setParams(httpParameters);
            response = httpClient.execute(httpget);
            HttpEntity entity = response.getEntity();
            urlIn = entity.getContent();
            rootElem = parse(urlIn);
        }
        catch (URISyntaxException e)
        {
            Debug.message(e.getMessage());
        }
        catch (ClientProtocolException e)
        {
            Debug.message(e.getMessage());
        }
        catch (IOException e)
        {
            Debug.message(e.getMessage());
        }
        catch (IllegalStateException e)
        {
            Debug.message(e.getMessage());
        }
        catch (ParserException e)
        {
            Debug.message(e.getMessage());
        }
        finally
        {
            if (urlIn != null)
            {
                try
                {
                    urlIn.close();
                }
                catch (IOException e)
                {
                    Debug.message(e.getMessage());
                }
            }

        }
        return rootElem;
    }
}
