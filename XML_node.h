#ifndef XML_NODE_H_INCLUDED
#define XML_NODE_H_INCLUDED

#include <list>
#include <unordered_map>
#include <map>

// order on children nodes will not be maintained.
// as you can see i'm literally using an unordered_map.
/// if you want to maintain the original order of nested tag change "std::unordered_map" to "std::map".
/// the header files for both of them are already included

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
        void print_data_without_nested_tags(); // not implemented
};

#endif // XML_NODE_H_INCLUDED
