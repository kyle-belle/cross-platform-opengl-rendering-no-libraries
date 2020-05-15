#include <string.h>
#include "GL/glew.h"

char* l_trim(char* s, const char what = ' '){
    while(s){
        if((*s) == what) ++s; else break;
    }
    return s;
}

char* r_trim(char* s, const char what = ' '){
    char* l = s + (strlen(s) - 1);
    while(l != s){
        if((*l) == what) *l='\0', --l; else break;
    }
    return s;
}

char* trim(char* s, const char what = ' '){
    return l_trim(r_trim(s, what), what);
}

char* get_file_extension(const char* file){
    const unsigned int length = strlen(file);
    char* extension = NULL;
    for(int i = length-1; i >= 0; --i){
        if(file[i] == '.'){
            unsigned int extension_length = length - i; //this should leave space for end of line char
            extension = new char[extension_length]; // should i use new or malloc here;
            memcpy(extension, &file[i+1], extension_length);// this should also copy end of line char
        }
    }

    return extension;
}

bool is_extension_supported(const char* extension){
    return glewIsExtensionSupported(extension);
}
