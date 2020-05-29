#include "XML_node.h"

XML_node::~XML_node(){
    this->delete_node();
}

void XML_node::delete_node(){
    delete[] this->tag_name;
    delete[] this->data;
    for(auto it : this->attributes){
//        delete it.first;
        delete it.second;
    }

    for(auto it : this->children){
        for(auto node_it : *it.second){
            node_it->delete_node();
        }
    }
}

void XML_node::print_data_without_nested_tags(){

}

void XML_node::print_tree(){
    printf("%.*s<%s", this->depth*2, "---------------------------------------------------------------------------------------------",this->tag_name);

    for(auto it : this->attributes){
        printf(" %s=\"%s\"", it.first.c_str(), it.second);
    }
    printf(">\n");

//    printf("%*c%s\n", this->depth, ' ', this->data?this->data:"");

    if(this->is_self_closing){
        printf("/>");
        return;
    }

    for(auto it : this->children){
        for(auto& node_it : *it.second){
            node_it->print_tree();
        }
    }

    printf("%.*s</%s>\n", this->depth*2, "---------------------------------------------------------------------------------------------", this->tag_name);
}

XML_node* XML_node::getElementById(const char* id){

    XML_node* node = NULL;
    if(this->attributes["id"] && str_equals(this->attributes["id"], id)){
        return this;
    }else{
        for(auto childlist : this->children){ // this could be multi-threaded
            for(auto& child: *childlist.second){
                node = child->getElementById(id);
                if(node){
                    return node;
                }
            }
        }
    }

    return node;
}

std::vector<XML_node*> XML_node::querySelector(const char* selector){

}

std::vector<XML_node*> XML_node::getElementsByTagName(const char* tag){

}
