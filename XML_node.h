#ifndef XML_NODE_H_INCLUDED
#define XML_NODE_H_INCLUDED

#include <list>
#include <string>
#include <unordered_map>

class XML_node {
    public:

        const char* tag_name = NULL;
        const char* data = NULL;
        std::unordered_map<std::string, std::string> attribute_values;
        std::unordered_map<std::string, std::list<XML_node>> children;
};

#endif // XML_NODE_H_INCLUDED
