#include "model_loader.h"

Model_loader::Model_loader(const char* file): Resource_loader(file){
//    this->load(this->filepath);
}
Model_loader::Model_loader(const char* file, Object* object): Resource_loader(file){
//    this->load(this->filepath);
    // TODO: load object data into buffers after
}
