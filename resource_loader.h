#ifndef RESOURCE_LOADER_H_INCLUDED
#define RESOURCE_LOADER_H_INCLUDED

#include "macros.h"

#define FILE_NOT_FOUND 1
#define FILE_FORMAT_ERROR 2
#define FILE_FORMAT_UNSUPPORTED 3
#define FILE_EXTENSION_UNSUPPORTED 4

class Resource_loader{
    public:

        const char* filepath;

        Resource_loader(){}
        Resource_loader(const char* file): filepath(file){}
        virtual int load(const char* file) PURE_VIRTUAL;

};

#endif // RESOURCE_LOADER_H_INCLUDED
