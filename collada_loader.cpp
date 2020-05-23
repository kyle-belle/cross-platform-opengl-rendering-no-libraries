#include "collada_loader.h"
#include "XML_parser.h"

Collada_loader::Collada_loader(const char* file): Model_loader(file){
    this->load(file);
}

Collada_loader::Collada_loader(const char* file, Object* object): Model_loader(file){
    this->load(file);
}

int Collada_loader::load(const char* file){
    const XML_node* XML = (new XML_parser(file))->parent;
}
