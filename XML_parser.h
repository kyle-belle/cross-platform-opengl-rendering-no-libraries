#ifndef XML_PARSER_H_INCLUDED
#define XML_PARSER_H_INCLUDED

#include <stdio.h>
#include "XML_node.h"
#include "resource_loader.h"

class XML_parser : public Resource_loader{
    public:
        FILE* xml_file = NULL;
        XML_node* parent = NULL;

        XML_parser(){}
        XML_parser(const char* file);
        virtual int load(const char* file) override;
};


#endif // XML_PARSER_H_INCLUDED
