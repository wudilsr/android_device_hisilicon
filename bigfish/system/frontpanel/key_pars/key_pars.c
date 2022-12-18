#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linux_key.h"
#include "key_pars.h"
#include "libxml/parser.h"
#include "libxml/tree.h"

#define PARS_LOG(fmt ...)

#define KEY_XML_PATH  "/etc/frontPanel.xml"

int find_linux_key_code(const char *str, unsigned int *linux_key_code)
{
    int i = 0;
    int j = 0;

    j = sizeof(Linux_KeyCode_Ary)/sizeof(Linux_KeyCode_Ary[0]);

    for(i = 0 ;i < j ;i++)
    {
        if(!strcmp(Linux_KeyCode_Ary[i].linux_keycode_name,str))
        {
            *linux_key_code =  Linux_KeyCode_Ary[i].linux_keycode;
            return 1;
        }
    }
    return 0;
}

xmlNodePtr readXml(char *filename)
{
    xmlDocPtr mDoc;
    xmlNodePtr curNode;

    mDoc = xmlReadFile(filename,NULL,XML_PARSE_NOBLANKS);
    if (mDoc == NULL){
        PARS_LOG("can't open the frontPanel.xml\n");
    }

    curNode = xmlDocGetRootElement(mDoc);

    if (NULL == curNode){
        PARS_LOG("style.xml is empty file \n");
        xmlFreeDoc(mDoc);
        return NULL;
    }

    PARS_LOG("RootElement=%s\n",curNode->name);

    if (xmlStrcmp(curNode->name, BAD_CAST "frontPanel_xml")){
        PARS_LOG("document of the wrong type, root node != root\n");
        xmlFreeDoc(mDoc);
        return NULL;
    }

    return curNode;
}

char* getProp(xmlNodePtr nodeptr,const char* prop)
{
    xmlAttrPtr attrPtr = nodeptr->properties;
    while (attrPtr != NULL){
        if (!xmlStrcmp(attrPtr->name, BAD_CAST prop)){
            xmlChar* szAttr = xmlGetProp(nodeptr,BAD_CAST prop);
            ("%s = %s \n",prop,szAttr);
            return (char*)szAttr;
        }
        attrPtr = attrPtr->next;
    }
    return NULL;
}

void Pars_Key(xmlNodePtr nodeptr, struct _key_arry *keyarry)
{
    int keynum = 0;
    int ret = -1;
    char *keyname =NULL;
    char *pchar = NULL;
    xmlChar *szKey;
    unsigned long long bottom_keycode;
    unsigned int linux_keycode;
    xmlNodePtr xmlChildNodePtr;

    if (nodeptr != NULL) {
        memcpy(keyarry->keyname,nodeptr->name,strlen(nodeptr->name));
        keyarry->keyname[strlen(nodeptr->name)] = '\0';
        PARS_LOG("remote controler name=%s\n",keyarry->keyname);
    }

    xmlChildNodePtr = nodeptr->children;

    while (xmlChildNodePtr != NULL) {

        pchar = getProp(xmlChildNodePtr,"value");
        if (pchar != NULL) {
            bottom_keycode = strtoull(pchar,NULL,16);
        }
        pchar = getProp(xmlChildNodePtr,"name");
        if (pchar != NULL) {
            ret = find_linux_key_code(pchar,&linux_keycode);
            if (ret != 0 ) {
                keyarry->hi_keycode[keynum].bottom_keycode = bottom_keycode;
                keyarry->hi_keycode[keynum].linux_keycode = linux_keycode;
                keynum = keynum +1;
                PARS_LOG("   linux_keycode=0x%04x, bottom_keycode=0x%.08llx, %s\n",linux_keycode,bottom_keycode,pchar);
                if (keynum >= KEYNUMMAX) {
                    PARS_LOG("we only support max num %d keys in one Remote controler\n");
                    break;
                }
            }
        }
        xmlChildNodePtr = xmlChildNodePtr->next;
    }
    keyarry->keynum = keynum;
}

void get_keycode(struct _key_arry *keyarry, int keyarry_num)
{
    int i = 0;
    xmlNodePtr xmlRootNodePtr;
    xmlNodePtr nodeptr;

    xmlRootNodePtr = readXml(KEY_XML_PATH);

    nodeptr = xmlRootNodePtr->children;

    for(i = 0; i<keyarry_num; i++)
    {
        if (nodeptr != NULL) {
            Pars_Key(nodeptr,keyarry);
            nodeptr = nodeptr->next;
            keyarry = keyarry + 1;
        }
    }
}
