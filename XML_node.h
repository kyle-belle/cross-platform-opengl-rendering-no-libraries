#ifndef XML_NODE_H_INCLUDED
#define XML_NODE_H_INCLUDED

#include <list>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include "utils.h"

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
        std::unordered_map<std::string, const char*> attributes;
        std::unordered_map<std::string, std::list<XML_node*>*> children;

        XML_node(){}
        ~XML_node();

        void print_tree();

        /**
         * @param id
         *
         * Get the first node which has an id attribute whose value is equal to @param id
        */
        XML_node* getElementById(const char* id);
        std::vector<XML_node*> querySelector(const char* selector);
        std::vector<XML_node*> getElementsByTagName(const char* tag);
        void delete_node();
        void print_data_without_nested_tags(); // not implemented
};

#endif // XML_NODE_H_INCLUDED
