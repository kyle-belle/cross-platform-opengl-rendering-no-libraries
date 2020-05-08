#include <string.h>
#include "GL/glew.h"

char* l_trim(char* s, char what = ' '){
    while(s){
        if((*s) == what) ++s; else break;
    }
    return s;
}

char* r_trim(char* s, char what = ' '){
    char* l = s + (strlen(s) - 1);
    while(l != s){
        if((*l) == what) *l='\0', --l; else break;
    }
    return s;
}

char* trim(char* s, char what = ' '){
    return l_trim(r_trim(s, what), what);
}


bool is_extension_supported(const char* extension){
    return glewIsExtensionSupported(extension);
}
