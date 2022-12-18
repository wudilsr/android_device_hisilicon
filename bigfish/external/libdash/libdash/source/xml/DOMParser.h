/*
 * DOMParser.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef DOMPARSER_H_
#define DOMPARSER_H_

#include "config.h"

#include "Node.h"
#include <libxml/xmlreader.h>
#include "../helpers/Path.h"

namespace dash
{
    namespace xml
    {
        enum NodeType
        {
            Start           = 1,
            End             = 15,
            Comment         = 8,
            WhiteSpace      = 14,
            Text            = 3,
        };

        class DOMParser
        {
            public:
                DOMParser           (std::string url);
                virtual ~DOMParser  ();

              //  bool    Parse       ();
                bool    Parse       (int *err);
                Node*   GetRootNode () const;
                void    Print       ();
                static void   XMLReaderErrorCallback(void *arg,
                                                const char *msg,
                                                xmlParserSeverities severity,
                                                xmlTextReaderLocatorPtr locator);

            private:
                xmlTextReaderPtr    reader;
                Node                *root;
                std::string         url;
                std::string         hisiUrl;//specify url can't be used directly

                void    Init                    ();
                Node*   ProcessNode             ();
                Node*   ProcessNode             (int *err);
                void    AddAttributesToNode     (Node *node);
                void    Print                   (Node *node, int offset);
                bool   ParseHisiUrl();
        };
    }
}
#endif /* DOMPARSER_H_ */