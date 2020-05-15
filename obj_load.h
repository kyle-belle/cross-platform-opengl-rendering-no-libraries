#ifndef OBJ_LOAD_H_INCLUDED
#define OBJ_LOAD_H_INCLUDED

#include "model_loader.h"

class OBJ_loader : public Model_loader{

    public:

        OBJ_loader(){}
        OBJ_loader(const char* file);
        OBJ_loader(const char* file, Object* object);
        virtual int load(const char* file) override;
};

#endif // OBJ_LOAD_H_INCLUDED
