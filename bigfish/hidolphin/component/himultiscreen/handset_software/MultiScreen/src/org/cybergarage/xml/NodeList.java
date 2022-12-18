/******************************************************************
*
*    CyberXML for Java
*
*    Copyright (C) Satoshi Konno 2002
*
*    File: NodeList.java
*
*    Revision;
*
*    11/27/02
*        - first revision.
*
******************************************************************/

package org.cybergarage.xml;

import java.util.Vector;

import org.cybergarage.util.Mutex;

public class NodeList extends Vector
{
    public NodeList()
    {
    }

    public Node getNode(int n)
    {
        // Modify for MultiScreen.
        if (n < size())
        {
            return (Node) get(n);
        }
        return null;
        // End modify for MultiScreen.
    }

    public Node getNode(String name)
    {
        if (name == null)
            return null;
        // Begin modify for MultiScreen.
        int nLists = size();
        for (int n = 0; n < nLists; n++)
        {
            Node node = getNode(n);
            if (node == null)
            {
                continue;
            }
            String nodeName = node.getName();
            if (name.compareTo(nodeName) == 0)
            {
                return node;
            }
        }
        // End modify for MultiScreen.
        return null;
    }

    public Node getEndsWith(String name)
    {
        if (name == null)
            return null;
        // Begin modify for MultiScreen.
        int nLists = size();
        for (int n = 0; n < nLists; n++)
        {
            Node node = getNode(n);
            if (node == null)
            {
                continue;
            }
            String nodeName = node.getName();
            if (nodeName == null)
                continue;
            if (nodeName.endsWith(name) == true)
            {
                unlock();
                return node;
            }
        }
        // End modify for MultiScreen.
        return null;
    }

    // Begin modify for MultiScreen.
    private Mutex mutex = new Mutex();

    public void lock()
    {
        mutex.lock();
    }

    public void unlock()
    {
        mutex.unlock();
    }
    // End modify for MultiScreen.
}
