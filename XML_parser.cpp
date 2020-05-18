#include "XML_parser.h"
#include "stdio.h"

#define XML_TAG_OPEN_TOKEN '<'
#define XML_TAG_CLOSING_TOKEN '/'
#define XML_TAG_SELF_CLOSING_STRING "/>"
#define XML_TAG_CLOSING_STRING "</"
#define XML_TAG_END_TOKEN '>'
#define XML_XML_TAG_STRING "<?"
#define XML_IGNORE_TAG_TOKEN '?' // i really dont care about tag which start like "<?"

XML_parser::XML_parser(const char* file): Resource_loader(file){
    xml_file = fopen(file, "r");
    this->load(this->filepath);
    fclose(xml_file);
}

// assuming xml file is valid. Not performing any validity checks as of now
// basucally right now i'm just reading and reconstructing (printing) it in the console to ensure i'm reading the file correctly
// will need to create a function which takes in a FILE* and XML_node I'm think but still not sure if it'll work out in the end but i'll see
// will have to account for if an attribute's value contain any of the tokens
int XML_parser::load(const char* file){
    char token;
    char* tag_name = new char[64]; // will pre-allocate 64 byte for this as i don't expect to have tag names longer than this but the xml spec doesn't specify a limit so will reallocate later if needed
    bool tag_open = false, reading_tag_name = false, reading_attribute_name = false, reading_attribute_value = false, reading_data = false;
    long int tag_start = 0, tag_end = 0, attribute_name_start = 0, attribute_name_end = 0, attribute_value_start = 0, attribute_value_end = 0;

    // Will not check for file extension as many file types use XML syntax.

    if(xml_file){

        while(!feof(xml_file)){
            token = fgetc(xml_file);

            switch(token){

                case XML_TAG_OPEN_TOKEN: // check for tag opening '<'
                    tag_open = true;

                    token = fgetc(xml_file);

                    switch(token){
                        case XML_IGNORE_TAG_TOKEN: // check for opening question mark
                            printf("<?");

                            while(!feof(xml_file)){ // loop until tag is closed

                                token = fgetc(xml_file);
                                printf("%c", token);
                                if(token == XML_IGNORE_TAG_TOKEN){// check for closing question mark
                                    token = fgetc(xml_file);
                                    if (token == XML_TAG_END_TOKEN){
                                        fgetc(xml_file); printf(">\n");
                                        break;
                                    }
                                    continue;
                                }
                            }
                            tag_open = false;
                        break;

                        default:
                            reading_tag_name = true;
                            reading_data = false;
                            tag_start = ftell(xml_file);
                            printf("\n\tTag - <");
                            printf("%c", token);
                            while(!feof(xml_file)){
                                token = fgetc(xml_file);
//                                printf("%c", token);

                                switch(token){
                                    case XML_TAG_CLOSING_TOKEN: // forward slash

                                        if(!reading_data){ // if we are reading data then this can just be considered text in the data
                                            if(tag_start+1 == ftell(xml_file)){ // closing tag like "</tag>
                                                printf("/");
                                                while(!feof(xml_file)){ // just loop till the end of this tag or till end of file, whichever comes first
                                                    token = fgetc(xml_file);
                                                    if(token == XML_TAG_END_TOKEN){
                                                        printf(">\n");
                                                        tag_open = false;
                                                        break;
                                                    }
                                                    printf("%c", token);
                                                }
                                            }else{ //is a self closing tag like <tag />
                                                printf("/>\n");
                                                tag_end = ftell(xml_file) - 1; //may need to minus 2 to account for space but couldn't hurt to allocate an extra byte //may need to trim so we only get tag's name
//                                                printf("tag name length: %ld", tag_end - tag_start);
                                                tag_open = false;
                                            }
                                        }else{
                                            printf("/");
                                        }
                                    break;

                                    case XML_TAG_END_TOKEN:
                                        // if we've gotten pass case `XML_TAG_CLOSING_TOKEN:` above this means we've reached the end of an opening tag i.e <tag>
                                        // now we start reading it's data until we meet a tag opening character (not yet checking if the tag opening char is escaped);
                                        if(!reading_data){ // if we are infact reading data then the shouldn't be an unescaped tag end character. maybe a invalid xml file but will ignore for now and just print it
                                            reading_tag_name = false;
                                            reading_attribute_name = false;
                                            reading_attribute_value = false;
                                            reading_data = true;
                                            printf(">\ndata\n\t");
                                        }else{
                                            printf("/");
                                        }

                                    break;

                                    case XML_TAG_OPEN_TOKEN: // another XML node inside current one will call this function recursively and see what hsppens
                                        fseek(xml_file, -1, SEEK_CUR);
                                        this->load(file);
                                    break;

                                    case '=':
                                        // safe to assume we are now reading attibute's value i feel
                                        attribute_name_end = ftell(xml_file) - 1;
                                        attribute_value_start = attribute_name_end + 2;
//                                        printf("attribute name length: %ld", attribute_name_end - attribute_name_start);
                                        fseek(xml_file, 1, SEEK_CUR);
                                        printf("=");
                                        reading_attribute_name = false;
                                        reading_attribute_value = true;
                                    break;

                                    case '"':
                                        if(reading_attribute_value){
                                            attribute_value_end = ftell(xml_file) - 1;
                                            continue;
                                        }
                                        printf("\"");
                                    break;

                                    case ' ':
                                        printf(" ");
                                        if(reading_tag_name){ // after reading tag's name comes the attribute name
                                            attribute_name_start = ftell(xml_file);
                                            reading_attribute_name = true;
                                        }else if(reading_attribute_value){ // after reading an attribute's value we possibly start reading another attribute's name
                                            attribute_name_start = ftell(xml_file);
                                            reading_attribute_value = false;
                                            reading_attribute_name = true;
                                        }
                                        reading_tag_name = false; // no need to do any check. this should alway be false after a space
                                    break;

                                    default:
                                        printf("%c", token);

                                }
                            }
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

    return 0;
}
