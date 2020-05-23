#ifndef XML_NODE_H_INCLUDED
#define XML_NODE_H_INCLUDED

#include <list>
#include <unordered_map>

class XML_node {
    public:

        char* tag_name = NULL;
        char* data = NULL;
        int depth;
        bool is_self_closing = false;
        std::unordered_map<char*, char*> attributes;
        std::unordered_map<char*, std::list<XML_node*>*> children;

        XML_node(){}
        ~XML_node();

        void print_tree();
        void delete_node();
};

#endif // XML_NODE_H_INCLUDED
