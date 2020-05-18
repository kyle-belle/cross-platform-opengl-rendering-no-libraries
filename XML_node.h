#ifndef XML_NODE_H_INCLUDED
#define XML_NODE_H_INCLUDED

#include <list>
#include <unordered_map>

class XML_node {
    public:

        const char* tag_name = NULL;
        const char* data = NULL;
        std::unordered_map<char*, char*> attribute_values;
        std::unordered_map<char*, std::list<XML_node>> children;
};

#endif // XML_NODE_H_INCLUDED
