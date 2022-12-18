/*
 * DOMParser.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "DOMParser.h"

using namespace dash::xml;
using namespace dash::helpers;

DOMParser::DOMParser    (std::string url) :
           hisiUrl          (url),
           url(""),
           reader       (NULL),
           root         (NULL)
{
    this->ParseHisiUrl();
    this->Init();
}
DOMParser::~DOMParser   ()
{
    xmlCleanupParser();
    delete(this->root);
}

bool DOMParser::ParseHisiUrl()
{
    int pos;

    if (this->hisiUrl.length() <= 0)
        return false;

    pos = this->hisiUrl.find(HISIURL_END, 0);
    if (pos == std::string::npos)
    {
        this->url = this->hisiUrl;
    }
    else
    {
        this->url.assign(this->hisiUrl, 0, pos);
    }

    return true;
}

Node*   DOMParser::GetRootNode              () const
{
    return this->root;
}

void  DOMParser::XMLReaderErrorCallback(void *arg,
                                                const char *msg,
                                                xmlParserSeverities severity,
                                                xmlTextReaderLocatorPtr locator)
{
  //  xmlChar *filename = xmlTextReaderLocatorBaseURI(locator);
    int line = xmlTextReaderLocatorLineNumber(locator);
    char tag[128];

    if (msg == NULL)
        return;

    switch(severity)
    {
        case XML_PARSER_SEVERITY_VALIDITY_WARNING:
            snprintf(tag, sizeof(tag), "[XML-VALIDITY-WARN]");
            break;
        case XML_PARSER_SEVERITY_VALIDITY_ERROR:
            snprintf(tag, sizeof(tag), "[XML-VALIDITY-ERROR]");
            break;
        case XML_PARSER_SEVERITY_WARNING:
            snprintf(tag, sizeof(tag), "[XML-WARN]");
            break;
        case XML_PARSER_SEVERITY_ERROR:
            snprintf(tag, sizeof(tag), "[XML-ERROR]");
            break;
         default:
            snprintf(tag, sizeof(tag), "[XML-UNKNOWN-LEVEL]");
    }

    dash_log(DASH_LOG_ERROR, "%s line=%d,msg=%s\n", tag, line, msg);

/*
    if (filename != NULL)
    {
        free(filename);
        filename = NULL;
    }
*/
}

bool    DOMParser::Parse                    (int *err)
{
    *err = DashError_Success;
    this->reader = xmlReaderForFile(this->hisiUrl.c_str(), NULL, 0);
    if(this->reader == NULL)
    {
        *err = DashError_Unknown;
        dash_log(DASH_LOG_ERROR, "[%s,%d] error, xml reader is NULL\n", __FUNCTION__, __LINE__);
        return false;
    }
   // xmlTextReaderSetErrorHandler(this->reader, XMLReaderErrorCallback, (void *)this);

    if(xmlTextReaderRead(this->reader))
        this->root = this->ProcessNode(err);

    if(this->root == NULL)
    {
        return false;
    }

    xmlFreeTextReader(this->reader);

    return true;
}

Node*   DOMParser::ProcessNode              ()
{
    int type = xmlTextReaderNodeType(this->reader);

    if(type != WhiteSpace && type != Text)
    {
        while (type == Comment || type == WhiteSpace)
        {
            xmlTextReaderRead(this->reader);
            type = xmlTextReaderNodeType(this->reader);
        }

        Node *node = new Node();
        node->SetType(type);
        node->SetMPDPath(Path::GetDirectoryPath(url));

        if(xmlTextReaderConstName(this->reader) == NULL)
        {
            delete node;
            return NULL;
        }

        std::string name    = (const char *) xmlTextReaderConstName(this->reader);
        int         isEmpty = xmlTextReaderIsEmptyElement(this->reader);

        node->SetName(name);
        this->AddAttributesToNode(node);

        if(isEmpty)
            return node;

        Node    *subnode    = NULL;
        int     ret         = xmlTextReaderRead(this->reader);

        while(ret == 1)
        {
            if(xmlTextReaderConstName(this->reader) != NULL &&
               !strcmp(name.c_str(), (const char *) xmlTextReaderConstName(this->reader)))
            {
                return node;
            }

            subnode = this->ProcessNode();

            if(subnode != NULL)
            {
                node->AddSubNode(subnode);
            }

            ret = xmlTextReaderRead(this->reader);
            //comment or whitespace after subnode do not start a new depth search,
            //must process here. verify it by hbbtv testcase org.hbbtv_00007121.
            type = xmlTextReaderNodeType(this->reader);
            while (type == Comment || type == WhiteSpace)
            {
                ret = xmlTextReaderRead(this->reader);
                type = xmlTextReaderNodeType(this->reader);
            }
        }

        return node;
    } else if (type == Text)
    {
       const char* text = (const char *) xmlTextReaderReadString(this->reader);

       if(text != NULL)
       {
           Node *node = new Node();
           node->SetType(type);
           node->SetText(text);
           return node;
       }
    }
    return NULL;
}

Node*   DOMParser::ProcessNode              (int *err)
{
#if 0
    int ret = 1;
    int type = -1;

    while(ret == 1)
    {
        type = xmlTextReaderNodeType(this->reader);
        if(xmlTextReaderConstName(this->reader) != NULL)
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] name=%s, type=%d\n", __FUNCTION__, __LINE__, xmlTextReaderConstName(this->reader), type);
        }
        ret = xmlTextReaderRead(this->reader);
    }

#else
    Node *node = ProcessNode();

    if (node == NULL)
    {
        if (xmlTextReaderNodeType(this->reader) == 0)
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] error, empty file\n", __FUNCTION__, __LINE__);
            *err = DashError_EmptyMPD;
        }
        else
        {
            *err = DashError_Unknown;
        }
    }
    else
    {
        *err = DashError_Success;
    }

    return node;
#endif
}

void    DOMParser::AddAttributesToNode      (Node *node)
{
    if(xmlTextReaderHasAttributes(this->reader))
    {
        while(xmlTextReaderMoveToNextAttribute(this->reader))
        {
            std::string key      = (const char *) xmlTextReaderConstName(this->reader);
            std::string value    = (const char *) xmlTextReaderConstValue(this->reader);
            node->AddAttribute(key, value);
        }
    }
}
void    DOMParser::Print                    (Node *node, int offset)
{
    std::stringstream ss;
    for(int i = 0; i < offset; i++)
        ss << " ";
    ss << node->GetName();

    std::vector<std::string> keys = node->GetAttributeKeys();

    ss.clear();
    for(unsigned int i = 0; i < keys.size(); i++)
    {
        ss << " " << keys.at(i) << "=" << node->GetAttributeValue(keys.at(i));
    }

    offset++;

    for(unsigned int i = 0; i < node->GetSubNodes().size(); i++)
    {
        this->Print(node->GetSubNodes().at(i), offset);
    }
}
void    DOMParser::Init                     ()
{
    this->root      = NULL;
    this->reader    = NULL;
}
void    DOMParser::Print                    ()
{
    this->Print(this->root, 0);
}
