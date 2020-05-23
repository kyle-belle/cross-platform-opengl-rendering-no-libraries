#ifndef COLLADA_LOADER_H_INCLUDED
#define COLLADA_LOADER_H_INCLUDED

#include "model_loader.h"

class Collada_loader : public Model_loader{
    public:

        Collada_loader(){}
        Collada_loader(const char* file);
        Collada_loader(const char* file, Object* object);
        virtual int load(const char* file) override;
};


#endif // COLLADA_LOADER_H_INCLUDED
