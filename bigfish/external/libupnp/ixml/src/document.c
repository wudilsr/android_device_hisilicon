/*******************************************************************************
 *
 * Copyright (c) 2000-2003 Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * - Neither name of Intel Corporation nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/


/*!
 * \file
 */


#include "ixmldebug.h"
#include "ixmlparser.h"

/*lint -save -e* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*lint -restore * */

void ixmlDocument_init(IXML_Document *doc)
{
    memset(doc, 0, sizeof(IXML_Document));
}


void ixmlDocument_free(IXML_Document *doc)
{
    if (doc != NULL) {
        ixmlNode_free((IXML_Node *)doc);
    }
}


/*!
 * When this function is called first time, nodeptr is the root of the subtree,
 * so it is not necessay to do two steps recursion.
 *
 * Internal function called by ixmlDocument_importNode
 */
static void ixmlDocument_setOwnerDocument(
    /*! [in] The document node. */
    IXML_Document *doc,
    /*! [in] \todo documentation. */
    IXML_Node *nodeptr)
{
    if (nodeptr != NULL) {
        nodeptr->ownerDocument = doc;
        ixmlDocument_setOwnerDocument(
            doc, ixmlNode_getFirstChild(nodeptr));
        ixmlDocument_setOwnerDocument(
            doc, ixmlNode_getNextSibling(nodeptr));
    }
}


int ixmlDocument_importNode(
    IXML_Document *doc,
    IXML_Node *importNode,
    BOOL deep,
    IXML_Node **rtNode)
{
    unsigned short nodeType;
    IXML_Node *newNode;

    *rtNode = NULL;

    if (doc == NULL || importNode == NULL) {
        return IXML_INVALID_PARAMETER;
    }

    nodeType = ixmlNode_getNodeType(importNode);
    if (nodeType == eDOCUMENT_NODE) {
        return IXML_NOT_SUPPORTED_ERR;
    }

    newNode = ixmlNode_cloneNode(importNode, deep);
    if (newNode == NULL) {
        return IXML_FAILED;
    }

    ixmlDocument_setOwnerDocument(doc, newNode);
    *rtNode = newNode;

    return IXML_SUCCESS;
}


int ixmlDocument_createElementEx(
    IXML_Document *doc,
    const DOMString tagName,
    IXML_Element **rtElement)
{
    int errCode = IXML_SUCCESS;
    IXML_Element *newElement = NULL;

    if (doc == NULL || tagName == NULL) {
        errCode = IXML_INVALID_PARAMETER;
        goto ErrorHandler;
    }

    newElement = (IXML_Element *) UPNP_MALLOC(sizeof(IXML_Element));
    if (newElement == NULL) {
        errCode = IXML_INSUFFICIENT_MEMORY;
        goto ErrorHandler;
    }

    ixmlElement_init(newElement);
    newElement->tagName = UPNP_STRDUP(tagName);
    if (newElement->tagName == NULL) {
        /*lint -e423*/
        ixmlElement_free(newElement);
        newElement = NULL;
        errCode = IXML_INSUFFICIENT_MEMORY;
        /*lint +e423*/
        goto ErrorHandler;
    }
    /* set the node fields */
    newElement->n.nodeType = eELEMENT_NODE;
    newElement->n.nodeName = UPNP_STRDUP(tagName);
    if (newElement->n.nodeName == NULL) {
        /*lint -e423*/
        ixmlElement_free(newElement);
        newElement = NULL;
        errCode = IXML_INSUFFICIENT_MEMORY;
        /*lint +e423*/
        goto ErrorHandler;
    }

    newElement->n.ownerDocument = doc;

ErrorHandler:
    *rtElement = newElement;

    return errCode;
}


IXML_Element *ixmlDocument_createElement(
    IXML_Document *doc,
    const DOMString tagName)
{
    IXML_Element *newElement = NULL;

    (void)ixmlDocument_createElementEx(doc, tagName, &newElement);
    return newElement;
}


int ixmlDocument_createDocumentEx(IXML_Document **rtDoc)
{
    IXML_Document *doc;
    int errCode = IXML_SUCCESS;

    doc = NULL;
    doc = (IXML_Document *)UPNP_MALLOC(sizeof (IXML_Document));
    if (doc == NULL) {
        errCode = IXML_INSUFFICIENT_MEMORY;
        goto ErrorHandler;
    }

    ixmlDocument_init(doc);

    doc->n.nodeName = UPNP_STRDUP(DOCUMENTNODENAME);
    if (doc->n.nodeName == NULL) {
        /*lint -e423*/
        ixmlDocument_free(doc);
        doc = NULL;
        errCode = IXML_INSUFFICIENT_MEMORY;
        /*lint +e423*/
        goto ErrorHandler;
    }

    doc->n.nodeType = eDOCUMENT_NODE;
    doc->n.ownerDocument = doc;

ErrorHandler:
    *rtDoc = doc;
    return errCode;
}


IXML_Document *ixmlDocument_createDocument()
{
    IXML_Document *doc = NULL;

    (void)ixmlDocument_createDocumentEx(&doc);

    return doc;
}


int ixmlDocument_createTextNodeEx(
    IXML_Document *doc,
    const DOMString data,
    IXML_Node **textNode)
{
    IXML_Node *returnNode;
    int rc = IXML_SUCCESS;

    returnNode = NULL;
    if (doc == NULL || data == NULL) {
        rc = IXML_INVALID_PARAMETER;
        goto ErrorHandler;
    }

    returnNode = (IXML_Node *)UPNP_MALLOC(sizeof (IXML_Node));
    if (returnNode == NULL) {
        rc = IXML_INSUFFICIENT_MEMORY;
        goto ErrorHandler;
    }
    /* initialize the node */
    ixmlNode_init(returnNode);

    returnNode->nodeName = UPNP_STRDUP(TEXTNODENAME);
    if (returnNode->nodeName == NULL) {
        /*lint -e423*/
        ixmlNode_free(returnNode);
        returnNode = NULL;
        rc = IXML_INSUFFICIENT_MEMORY;
        /*lint +e423*/
        goto ErrorHandler;
    }
    /* add in node value */
    if (data != NULL) {
        returnNode->nodeValue = UPNP_STRDUP(data);
        if (returnNode->nodeValue == NULL) {
            /*lint -save -e423 */
            ixmlNode_free(returnNode);
            returnNode = NULL;
            rc = IXML_INSUFFICIENT_MEMORY;
            /*lint -restore */
            goto ErrorHandler;
        }
    }

    returnNode->nodeType = eTEXT_NODE;
    returnNode->ownerDocument = doc;

ErrorHandler:
    *textNode = returnNode;
    return rc;
}


IXML_Node *ixmlDocument_createTextNode(
    IXML_Document *doc,
    const DOMString data)
{
    IXML_Node *returnNode = NULL;

    (void)ixmlDocument_createTextNodeEx(doc, data, &returnNode);

    return returnNode;
}


int ixmlDocument_createAttributeEx(
    IXML_Document *doc,
    const char *name,
    IXML_Attr **rtAttr)
{
    IXML_Attr *attrNode = NULL;
    int errCode = IXML_SUCCESS;

    attrNode = (IXML_Attr *)UPNP_MALLOC(sizeof (IXML_Attr));
    if (attrNode == NULL) {
        errCode = IXML_INSUFFICIENT_MEMORY;
        goto ErrorHandler;
    }

    if (doc == NULL || name == NULL) {
        /*lint -e423*/
        ixmlAttr_free(attrNode);
        attrNode = NULL;
        errCode = IXML_INVALID_PARAMETER;
        /*lint +e423*/
        goto ErrorHandler;
    }

    ixmlAttr_init(attrNode);
    attrNode->n.nodeType = eATTRIBUTE_NODE;

    /* set the node fields */
    attrNode->n.nodeName = UPNP_STRDUP(name);
    if (attrNode->n.nodeName == NULL) {
        /*lint -save -e423 */
        ixmlAttr_free(attrNode);
        attrNode = NULL;
        errCode = IXML_INSUFFICIENT_MEMORY;
        /*lint -restore */
        goto ErrorHandler;
    }

    attrNode->n.ownerDocument = doc;

ErrorHandler:
    *rtAttr = attrNode;
    return errCode;
}


IXML_Attr *ixmlDocument_createAttribute(
    IXML_Document *doc,
    const char *name)
{
    IXML_Attr *attrNode = NULL;

    (void)ixmlDocument_createAttributeEx(doc, name, &attrNode);

    return attrNode;
}


int ixmlDocument_createAttributeNSEx(
    IXML_Document *doc,
    const DOMString namespaceURI,
    const DOMString qualifiedName,
    IXML_Attr **rtAttr )
{
    IXML_Attr *attrNode = NULL;
    int errCode = IXML_SUCCESS;

    if (doc == NULL || namespaceURI == NULL || qualifiedName == NULL) {
        errCode = IXML_INVALID_PARAMETER;
        goto ErrorHandler;
    }

    errCode =
        ixmlDocument_createAttributeEx(doc, qualifiedName, &attrNode);
    if (errCode != IXML_SUCCESS) {
        goto ErrorHandler;
    }
    /* set the namespaceURI field */
    attrNode->n.namespaceURI = UPNP_STRDUP(namespaceURI);
    if (attrNode->n.namespaceURI == NULL) {
        ixmlAttr_free(attrNode);
        attrNode = NULL;
        errCode = IXML_INSUFFICIENT_MEMORY;
        goto ErrorHandler;
    }
    /* set the localName and prefix */
    errCode =
        ixmlNode_setNodeName((IXML_Node *)attrNode, qualifiedName);
    if (errCode != IXML_SUCCESS) {
        ixmlAttr_free(attrNode);
        attrNode = NULL;
        goto ErrorHandler;
    }

ErrorHandler:
    *rtAttr = attrNode;
    return errCode;
}


IXML_Attr *ixmlDocument_createAttributeNS(
    IXML_Document *doc,
    const DOMString namespaceURI,
    const DOMString qualifiedName)
{
    IXML_Attr *attrNode = NULL;
    int ret =     IXML_SUCCESS;

    ret = ixmlDocument_createAttributeNSEx(
        doc, namespaceURI, qualifiedName, &attrNode);
    if (ret != IXML_SUCCESS)
    {
        return NULL;
    }

    return attrNode;
}


int ixmlDocument_createCDATASectionEx(
    IXML_Document *doc,
    const DOMString data,
    IXML_CDATASection **rtCD)
{
    int errCode = IXML_SUCCESS;
    IXML_CDATASection *cDSectionNode = NULL;

    if(doc == NULL || data == NULL) {
        errCode = IXML_INVALID_PARAMETER;
        goto ErrorHandler;
    }

    cDSectionNode = (IXML_CDATASection *)UPNP_MALLOC(sizeof (IXML_CDATASection));
    if (cDSectionNode == NULL) {
        errCode = IXML_INSUFFICIENT_MEMORY;
        goto ErrorHandler;
    }

    ixmlCDATASection_init(cDSectionNode);
    cDSectionNode->n.nodeType = eCDATA_SECTION_NODE;
    cDSectionNode->n.nodeName = UPNP_STRDUP(CDATANODENAME);
    if (cDSectionNode->n.nodeName == NULL) {
        /*lint -e423*/
        ixmlCDATASection_free(cDSectionNode);
        cDSectionNode = NULL;
        errCode = IXML_INSUFFICIENT_MEMORY;
        /*lint +e423*/
        goto ErrorHandler;
    }

    cDSectionNode->n.nodeValue = UPNP_STRDUP(data);
    if (cDSectionNode->n.nodeValue == NULL) {
        /*lint -e423*/
        ixmlCDATASection_free( cDSectionNode );
        cDSectionNode = NULL;
        errCode = IXML_INSUFFICIENT_MEMORY;
        /*lint +e423*/
        goto ErrorHandler;
    }

    cDSectionNode->n.ownerDocument = doc;

ErrorHandler:
    *rtCD = cDSectionNode;
    return errCode;
}


IXML_CDATASection *ixmlDocument_createCDATASection(
    IXML_Document *doc,
    const DOMString data)
{
    IXML_CDATASection *cDSectionNode = NULL;
    int ret =     IXML_SUCCESS;

    ret = ixmlDocument_createCDATASectionEx(doc, data, &cDSectionNode);
    if (ret != IXML_SUCCESS)
    {
        return NULL;
    }

    return cDSectionNode;
}


int ixmlDocument_createElementNSEx(
    IXML_Document *doc,
    const DOMString namespaceURI,
    const DOMString qualifiedName,
    IXML_Element **rtElement)
{
    IXML_Element *newElement = NULL;
    int ret = IXML_SUCCESS;
    int line = 0;

    if (doc == NULL || namespaceURI == NULL || qualifiedName == NULL) {
        line = __LINE__;
        ret = IXML_INVALID_PARAMETER;
        goto ErrorHandler;
    }

    ret = ixmlDocument_createElementEx(doc, qualifiedName, &newElement);
    if (ret != IXML_SUCCESS) {
        line = __LINE__;
        goto ErrorHandler;
    }
    /* set the namespaceURI field */
    newElement->n.namespaceURI = UPNP_STRDUP(namespaceURI);
    if (newElement->n.namespaceURI == NULL) {
        line = __LINE__;
        ixmlElement_free(newElement);
        newElement = NULL;
        ret = IXML_INSUFFICIENT_MEMORY;
        goto ErrorHandler;
    }
    /* set the localName and prefix */
    ret = ixmlNode_setNodeName((IXML_Node *)newElement, qualifiedName);
    if (ret != IXML_SUCCESS) {
        line = __LINE__;
        ixmlElement_free(newElement);
        newElement = NULL;
        ret = IXML_INSUFFICIENT_MEMORY;
        goto ErrorHandler;
    }

    newElement->n.nodeValue = NULL;

ErrorHandler:
    *rtElement = newElement;
    if (ret != IXML_SUCCESS) {
        IxmlPrintf(__FILE__, line, "ixmlDocument_createElementNSEx", "Error %d\n", ret);
    }

    return ret;
}


IXML_Element *ixmlDocument_createElementNS(
    IXML_Document *doc,
    const DOMString namespaceURI,
    const DOMString qualifiedName)
{
    IXML_Element *newElement = NULL;
    int ret =     IXML_SUCCESS;

       ret = ixmlDocument_createElementNSEx(doc, namespaceURI, qualifiedName, &newElement);
    if (ret != IXML_SUCCESS)
    {
        return NULL;
    }

    return newElement;
}


IXML_NodeList *ixmlDocument_getElementsByTagName(
    IXML_Document *doc,
    const DOMString tagName)
{
    IXML_NodeList *returnNodeList = NULL;

    if (doc == NULL || tagName == NULL) {
        return NULL;
    }

    ixmlNode_getElementsByTagName((IXML_Node *)doc, tagName, &returnNodeList);

    return returnNodeList;
}


IXML_NodeList *ixmlDocument_getElementsByTagNameNS(
    IXML_Document *doc,
    const DOMString namespaceURI,
    const DOMString localName)
{
    IXML_NodeList *returnNodeList = NULL;

    if (doc == NULL || namespaceURI == NULL || localName == NULL) {
        return NULL;
    }

    ixmlNode_getElementsByTagNameNS(
        (IXML_Node *)doc, namespaceURI, localName, &returnNodeList);

    return returnNodeList;
}


IXML_Element *ixmlDocument_getElementById(
    IXML_Document *doc,
    const DOMString tagName)
{
    IXML_Element *rtElement = NULL;
    IXML_Node *nodeptr = (IXML_Node *)doc;
    const char *name;

    if (nodeptr == NULL || tagName == NULL) {
        return rtElement;
    }

    if (ixmlNode_getNodeType(nodeptr) == eELEMENT_NODE) {
        name = ixmlNode_getNodeName(nodeptr);
        if (name == NULL) {
            return rtElement;
        }

        if (HISTRCMP(tagName, name) == 0) {
            rtElement = (IXML_Element *)nodeptr;
            return rtElement;
        } else {
            rtElement = ixmlDocument_getElementById(
                (IXML_Document *)ixmlNode_getFirstChild(nodeptr),
                tagName );
            if (rtElement == NULL) {
                rtElement = ixmlDocument_getElementById(
                    (IXML_Document *)ixmlNode_getNextSibling(nodeptr),
                    tagName);
            }
        }
    } else {
        rtElement = ixmlDocument_getElementById(
            (IXML_Document *)ixmlNode_getFirstChild(nodeptr),
            tagName);
        if (rtElement == NULL) {
            rtElement = ixmlDocument_getElementById(
                (IXML_Document *)ixmlNode_getNextSibling(nodeptr),
                tagName);
        }
    }

    return rtElement;
}
