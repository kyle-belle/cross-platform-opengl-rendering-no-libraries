#include "XML_parser.h"
#include "stdio.h"

#define XML_TAG_OPEN_TOKEN '<'
#define XML_TAG_CLOSING_TOKEN '/'
#define XML_TAG_SELF_CLOSING_STRING "/>"
#define XML_TAG_CLOSING_STRING "</"
#define XML_TAG_END_TOKEN '>'
#define XML_XML_TAG_STRING "<?"
#define XML_IGNORE_TAG_TOKEN '?' // i really dont care about tag which start like "<?"

#define DEFAULT_TAG_NAME_LENGTH 64

void get_string_from_file(char*& s, unsigned int length, FILE* xml_file);
void get_tag_name(char*& s, unsigned int tag_name_length, FILE* xml_file){}
void get_tag_data(char*& s, unsigned int tag_data_length, FILE* xml_file){}
void get_attribute_name(char*& s, unsigned int attribute_name_length, FILE* xml_file){}
void get_attribute_value(char*& s, unsigned int attribute_value_length, FILE* xml_file){}


XML_parser::XML_parser(const char* file): Resource_loader(file){
    FILE* xml_file = fopen(file, "r");
    this->load(this->filepath);
    fclose(xml_file);
}

int XML_parser::load(const char* file){
    FILE* xml_file = fopen(file, "r");

    // Will not check for file extension as many file types use XML syntax.

    if(xml_file){
//        while(!feof(xml_file)){
            this->parse(xml_file, this->parent);
//        }
    }else{
        printf("file not found: %s. if you are sure the file exist relative to this location or at an absolute path then this may be a permissions issue\n", this->filepath);
        return FILE_NOT_FOUND;
    }

    fclose(xml_file);
}

// assuming xml file is valid. Not performing any validity checks as of now
// basucally right now i'm just reading and reconstructing (printing) it in the console to ensure i'm reading the file correctly // UPDATE: now i am actual building the tree list structure // TODO: get attributes and data
// will need to create a function which takes in a FILE* and XML_node I'm think but still not sure if it'll work out in the end but i'll see
// will have to account for if an attribute's value contain any of the tokens
// for now i will use fseek to move around. if i find it too slow i'll look into file memory mapping
XML_node* XML_parser::parse(FILE* xml_file, XML_node*& node){
    char token;
    char* tag_name = new char[DEFAULT_TAG_NAME_LENGTH]; // will pre-allocate 64 byte for this as i don't expect to have tag names longer than this but the xml spec doesn't specify a limit so will reallocate later if needed
    char* attribute_name = new char[DEFAULT_TAG_NAME_LENGTH]; // will pre-allocate 64 byte for this as i don't expect to have tag names longer than this but the xml spec doesn't specify a limit so will reallocate later if needed
    char* attribute_value = new char[DEFAULT_TAG_NAME_LENGTH]; // will pre-allocate 64 byte for this as i don't expect to have tag names longer than this but the xml spec doesn't specify a limit so will reallocate later if needed
    char* data = NULL; // will pre-allocate 64 byte for this as i don't expect to have tag names longer than this but the xml spec doesn't specify a limit so will reallocate later if needed
    bool tag_open = false, reading_tag_name = false, reading_attribute_name = false, reading_attribute_value = false, reading_data = false;
    long int tag_start = 0, tag_end = 0, tag_length = 0, data_start = 0, data_end = 0, data_length = 0, attribute_name_start = 0, attribute_name_end = 0, attribute_name_length = 0, attribute_value_start = 0, attribute_value_end = 0, attribute_value_length = 0;

    ++this->current_depth;
//    printf("depth: %d\n", this->current_depth);
    XML_node* current_node = new XML_node();
    current_node->depth = this->current_depth;

    while(!feof(xml_file)){
        token = fgetc(xml_file);

        switch(token){

            case XML_TAG_OPEN_TOKEN: // check for tag opening '<'
                tag_open = true;

//                printf("<");
                token = fgetc(xml_file);

                switch(token){
                    case XML_IGNORE_TAG_TOKEN: // check for opening question mark
                printf("<");
                        printf("?");

                        while(!feof(xml_file)){ // loop until tag is closed

                            token = fgetc(xml_file);
                            printf("%c", token);
                            if(token == XML_IGNORE_TAG_TOKEN){// check for closing question mark
                                token = fgetc(xml_file);
                                if (token == XML_TAG_END_TOKEN){
                                    fgetc(xml_file);
                                    printf(">\n");
                                    break;
                                }
                                continue;
                            }
                        }
                        tag_open = false;
                    break;

                    case XML_TAG_CLOSING_TOKEN: //forward slash // coming right after tag opening so assume it is closing tag like </tag>
                        current_node->is_self_closing = false;

//                        printf("/");
                        tag_start = ftell(xml_file) + 1;
                        while(!feof(xml_file)){ // just loop till the end of this tag or till end of file, whichever comes first
                            token = fgetc(xml_file);
                            if(token == XML_TAG_END_TOKEN){
                                tag_open = false;
                                tag_end = ftell(xml_file) - 1;
                                tag_length = tag_end - tag_start + 1;
                                if(tag_length < DEFAULT_TAG_NAME_LENGTH){
                                    fseek(xml_file, -1 * (tag_length + 1), SEEK_CUR);
                                    fgets(tag_name, tag_length+1, xml_file);
//                                    printf("%s", tag_name);
                                    fseek(xml_file, 1, SEEK_CUR);
                                }
//                                printf(">");
//                                printf(" tag name length: %ld\n", tag_length);

                                return current_node;
                            }else if(token == ' '){ // this shouldn't occur. only if the author puts a space before the closing tag
                                tag_open = false;
                                tag_end = ftell(xml_file) - 1;
                                tag_length = tag_end - tag_start + 1;
                                if(tag_length < DEFAULT_TAG_NAME_LENGTH){ // will extract this to a function ..... i hope
                                    fseek(xml_file, -1 * (tag_length + 1), SEEK_CUR);
                                    fgets(tag_name, tag_length, xml_file);
//                                    printf("%s", tag_name);
                                    fseek(xml_file, 1, SEEK_CUR);
                                }
//                                printf(">");
//                                printf(" tag name length: %ld\n", tag_length);

                                node = current_node;
                                if(current_node->depth){
                                    std::list<XML_node*>* child_list = node->children[tag_name];
                                    if(!child_list){
                                        node->children[tag_name] =  new std::list<XML_node*>(1, node);
                                    }else{
                                        child_list->push_back(current_node);
                                    }
                                }

//                                return current_node;
                            }
//                                printf("%c", token);
                        }
                    break;

                    default:
                        reading_tag_name = true;
                        reading_data = false;
                        tag_start = ftell(xml_file);
//                            printf("\n\tTag - <");
//                            printf("%c", token);
                        while(!feof(xml_file)){
                            token = fgetc(xml_file);
//                                printf("%c", token);

                            switch(token){
                                case XML_TAG_CLOSING_TOKEN: // forward slash //is a self closing tag like <tag /> if not reading data

                                    if(!reading_data && !reading_attribute_value){ // if we are reading data then this can just be considered text in the data
                                            current_node->is_self_closing = true;
                                            --this->current_depth;
//                                            printf("/> %c\n", token);
                                            if(reading_tag_name){
                                                tag_end = ftell(xml_file); //may need to minus 2 to account for space but couldn't hurt to allocate an extra byte //may need to trim so we only get tag's name
                                                tag_length = tag_end - tag_start + 1;
                                                if(tag_length < DEFAULT_TAG_NAME_LENGTH){ // will extract this to a function ..... i hope
                                                    fseek(xml_file, -1 * (tag_length + 1), SEEK_CUR);
                                                    fgets(tag_name, tag_length+1, xml_file);
                                                    fseek(xml_file, 1, SEEK_CUR);
//                                                    printf("%s", tag_name);
                                                    current_node->tag_name = tag_name;
                                                }

//                                                printf(" tag name length: %ld", tag_end - tag_start + 1);
                                            }
                                            tag_open = false;

                                            node = current_node;
                                            if(current_node->depth){
                                                std::list<XML_node*>* child_list = node->children[tag_name];
                                                if(!child_list){
                                                    node->children[tag_name] =  new std::list<XML_node*>(1, node);
                                                }else{
                                                    child_list->push_back(current_node);
                                                }
                                            }

                                            return current_node;
                                    }else{
//                                        printf("/");
                                    }
                                break;

                                case XML_TAG_END_TOKEN:
                                    // if we've gotten pass case `XML_TAG_CLOSING_TOKEN:` above this means we've reached the end of an opening tag i.e <tag>
                                    // now we start reading it's data until we meet a tag opening character (not yet checking if the tag opening char is escaped);
//                                    printf("reading data: %s, reading attribute value: %s\n", reading_data?"true":"false", reading_attribute_value?"true":"false");
                                    if(!reading_data && !reading_attribute_value){ // if we are infact reading data then the shouldn't be an unescaped tag end character. maybe a invalid xml file but will ignore for now and just print it
                                        data_start = ftell(xml_file) + 1;
                                        if(reading_tag_name){
                                            tag_end = ftell(xml_file) - 1;

                                            tag_length = tag_end - tag_start + 1;
                                            if(tag_length < DEFAULT_TAG_NAME_LENGTH){ // will extract this to a function ..... i hope
                                                fseek(xml_file, -1 * (tag_length + 1), SEEK_CUR);
                                                fgets(tag_name, tag_length+1, xml_file);
                                                fseek(xml_file, 1, SEEK_CUR);
//                                                printf("%s\n", tag_name);
                                                current_node->tag_name = tag_name;
                                            }

//                                            printf(" tag name length: %ld >", tag_end - tag_start + 1);
                                        }


//                                        printf(" parent: <%s>\n", node?node->tag_name:"none");
                                        if(current_node->depth){
                                            std::list<XML_node*>* child_list = node->children[tag_name];
                                            if(!child_list){
                                                node->children[tag_name] =  new std::list<XML_node*>(1, current_node);
                                            }else{
                                                child_list->push_back(current_node);
                                            }
                                        }
                                        node = current_node;

                                        reading_tag_name = false;
                                        reading_attribute_name = false;
                                        reading_attribute_value = false;
                                        reading_data = true;
                                    }else{
//                                        printf(">");
                                    }

                                break;

                                case XML_TAG_OPEN_TOKEN: // another XML node inside current one will call this function recursively and see what hsppens
                                    if(reading_data){

                                        token=fgetc(xml_file);
                                        if(token == XML_TAG_CLOSING_TOKEN){ //forward slash // coming right after tag opening so assume it is closing tag like </tag>
//                                            printf("ftell() before: %ld\n", ftell(xml_file));
                                            data_end = ftell(xml_file) - 2;
                                            data_length = data_end - data_start;
                                            data = new char[data_length+1];
//                                            printf("data length: %d\n", data_length);
                                            fseek(xml_file, -1 * (data_length + 1), SEEK_CUR);
//                                            printf("ftell() before fgets: %ld\n", ftell(xml_file));
//                                            fgets(data, (data_length + 1), xml_file); // i was kinda screwed by the fgets function. didn't know it would stop at a newline. thought it would read the specified amount
                                            for(int i = 0; i < data_length; ++i){
                                                data[i] = fgetc(xml_file);
                                            }
                                            data[data_length] = '\0';
                                            fseek(xml_file, 1, SEEK_CUR);
//                                            printf("ftell() after: %ld\n", ftell(xml_file));
                                            current_node->data = data;

//                                            reading_data = false;
                                            current_node->is_self_closing = false;
                                            --this->current_depth;
//


                                            tag_start = ftell(xml_file) + 1;
                                            while(!feof(xml_file)){ // just loop till the end of this tag or till end of file, whichever comes first
//                                            printf("tag: %s, token after data: %c, data: %sd\n", current_node->tag_name, token, data);
                                                token = fgetc(xml_file);
                                                if(token == XML_TAG_END_TOKEN){
                                                    tag_open = false;
                                                    tag_end = ftell(xml_file) - 1;
                                                    tag_length = tag_end - tag_start + 1;
                                                    if(tag_length < DEFAULT_TAG_NAME_LENGTH){ // will extract this to a function ..... i hope
                                                        fseek(xml_file, -1 * (tag_length + 1), SEEK_CUR);
                                                        fgets(tag_name, tag_length+1, xml_file);
//                                                        printf("%s", tag_name);
                                                        fseek(xml_file, 1, SEEK_CUR);
                                                    }
//                                                    printf(">");
//                                                    printf(" tag name length: %ld\n", tag_length);

//                                                    if(current_node->depth){
//                                                        printf("tagnameeee %s\n", node->data);
//                                                        std::list<XML_node*>* child_list = node->children[tag_name];
//                                                        if(!child_list){
//                                                            node->children[tag_name] =  new std::list<XML_node*>(1, current_node);
//                                                        }else{
//                                                            child_list->push_back(current_node);
//                                                        }
//                                                    }else{
//                                                        node = current_node;
//                                                    }

                                                    return current_node;
                                                }else if(token == ' '){ // this shouldn't occur. only if the author puts a space before the closing tag
                                                    tag_open = false;
                                                    tag_end = ftell(xml_file) - 1;
                                                    tag_length = tag_end - tag_start + 1;
                                                    if(tag_length < DEFAULT_TAG_NAME_LENGTH){
                                                        fseek(xml_file, -1 * (tag_length + 1), SEEK_CUR);
                                                        fgets(tag_name, tag_length, xml_file);
//                                                        printf("%s", tag_name);
                                                        fseek(xml_file, 1, SEEK_CUR);
                                                    }
//                                                    printf(">");
//                                                    printf(" tag name length: %ld\n", tag_length);

                    //                                return current_node;
                                                }
                    //                                printf("%c", token);
                                            }
                                        }else{
                                            fseek(xml_file, -2, SEEK_CUR);
                                            this->parse(xml_file, node);
                                            node = current_node;
                                        }
                                    }
                                break;

                                case '=':
                                    // safe to assume we are now reading attibute's value i feel
                                    attribute_name_end = ftell(xml_file) - 1;
                                    attribute_value_start = attribute_name_end + 2;
                                    attribute_name_length = attribute_name_end - attribute_name_start;

                                    if(attribute_name_length < DEFAULT_TAG_NAME_LENGTH){ // will extract this to a function ..... i hope
                                        fseek(xml_file, -1 * (attribute_name_length + 1), SEEK_CUR);
                                        fgets(attribute_name, (attribute_name_length + 1), xml_file);
                                        fseek(xml_file, 1, SEEK_CUR);
                                    }
//                                        printf("attribute name length: %ld", attribute_name_end - attribute_name_start);
//                                    printf("attribute name: %s", attribute_name);

                                    fseek(xml_file, 1, SEEK_CUR);
//                                    printf("=");
                                    reading_attribute_name = false;
                                    reading_attribute_value = true;
                                break;

                                case '"':
                                    if(reading_attribute_value){
                                        reading_attribute_value=false;
                                        attribute_value_end = ftell(xml_file) - 1;
                                        attribute_value_length = attribute_value_end - attribute_value_start;

                                        if(attribute_value_length < DEFAULT_TAG_NAME_LENGTH){ // will extract this to a function ..... i hope
                                            fseek(xml_file, -1 * (attribute_value_length + 1), SEEK_CUR);
                                            fgets(attribute_value, (attribute_value_length + 1), xml_file);
                                            fseek(xml_file, 1, SEEK_CUR);
                                        }
//                                        printf("attribute value: %s", attribute_value);

                                        current_node->attributes[attribute_name] = attribute_value;

                                        continue;
                                    }
//                                    printf("\"");
                                break;

                                case ' ':
                                    if(reading_tag_name){ // after reading tag's name comes the attribute name
                                        tag_end = ftell(xml_file) - 1;
                                        tag_length = tag_end - tag_start + 1;
                                        if(tag_length < DEFAULT_TAG_NAME_LENGTH){
                                            fseek(xml_file, -1 * (tag_length + 1), SEEK_CUR);
                                            fgets(tag_name, tag_length+1, xml_file);
                                            fseek(xml_file, 1, SEEK_CUR);
//                                            printf("%s", tag_name);
                                            current_node->tag_name = tag_name;
                                        }

//                                        printf(" tag name length: %ld, max: %d", tag_length, DEFAULT_TAG_NAME_LENGTH);
//                                        printf(" ");
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
//                                        if(reading_data){
//                                            printf("%c", token);
//                                        }
                                break;

                            }
                        }
                }
            break;

            default:
                continue;
        }
    }

    return current_node;
}
