#include "XML_parser.h"
#include "stdio.h"

#define XML_TAG_OPEN_TOKEN '<'
#define XML_TAG_SELF_CLOSING_STRING "/>"
#define XML_TAG_CLOSING_STRING "</"
#define XML_TAG_END_TOKEN '>'
#define XML_XML_TAG_STRING "<?"
#define XML_IGNORE_TAG_TOKEN '?' // i really dont care about tag which start like "<?"

XML_parser::XML_parser(const char* file): Resource_loader(file){
    this->load(this->filepath);
}

int XML_parser::load(const char* file){
    FILE* xml_file = NULL;
    char token;
    char* tag_name = new char[64]; // will pre-allocate 64 byte for this as i don't expect to have tag names longer than this but the xml spec doesn't specify a limit so will reallocate later if needed
    bool tag_open = false;
    unsigned int tag_start = 0, tag_end = 0, attribute_name_start = 0, attribute_name_end = 0, attribute_value_start = 0, attribute_value_end = 0;

    // Will not check for file extension as many file types use XML syntax.
    xml_file = fopen(file, "r");

    if(xml_file){

        while(!feof(xml_file)){
            token = fgetc(xml_file);

            switch(token){

                case XML_TAG_OPEN_TOKEN: // check for tag opening '<'
                    tag_open = true;

                    token = fgetc(xml_file);

                    switch(token){
                        case XML_IGNORE_TAG_TOKEN: // check for opening question mark

                            while(!feof(xml_file)){ // loop until tag is closed

                                token = fgetc(xml_file);
                                printf("%c", token);
                                if(token == XML_IGNORE_TAG_TOKEN){// check for closing question mark
                                    token = fgetc(xml_file);
                                    if (token == XML_TAG_END_TOKEN){
                                        fgetc(xml_file); printf("\n");
                                        break;
                                    }
                                    continue;
                                }
                            }
                        break;

                        default:
                            continue;
                    }
                break;

                default:
                    continue;
            }
        }

    }else{
        printf("file not found: %s. if you are sure the file exist relative to this location then this may be a permissions issue\n", file);
        return FILE_NOT_FOUND;
    }
}
