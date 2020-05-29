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

/* std::vector<char*> */char** split(const char* s, unsigned int* count, char splitter = ' '){
    unsigned int s_length = strlen(s);
    char** segments = NULL;
    unsigned int segment_count = 1;
    unsigned int i = 0;
    for(; i < s_length; ++i){//first go over string to get amount of segments
        if(s[i] == splitter){
            ++segment_count;
            continue;
        }
    }

    *count = segment_count; // maybe should just use vector so i don't have to maintain this size count
    if(segment_count){
        segments = new char*[segment_count];
    }

    unsigned int segment_start = 0;
    unsigned int segment_end = 0;
    unsigned int segment_length = 0;
    for(i=0; i < segment_count; ++i){
        while(s[segment_end] != splitter && s[segment_end] != '\0'){
            ++segment_end;
        }

        segment_length = segment_end - segment_start;
        segments[i] = new char[segment_length + 1];
        memcpy(segments[i], &s[segment_start], segment_length);
        segments[i][segment_length] = '\0';// we must set this explicity
        segment_start = ++segment_end;
    }

    return segments;
}

bool is_extension_supported(const char* extension){
    return glewIsExtensionSupported(extension);
}
