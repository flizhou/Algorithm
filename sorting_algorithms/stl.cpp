// stl.cpp

#include "volsort.hpp"

#include <algorithm>
#include <iostream>

bool node_number_compare(const Node *a, const Node *b);
bool node_string_compare(const Node *a, const Node *b);

void stl_sort(List &l, bool numeric) {
        
    Node* nodeArray[l.size];
    Node* curr = l.head;
    
    for(size_t i=0; i<l.size; ++i){
        
        nodeArray[i] = curr;
        curr = curr->next;
    }

    if(numeric){
        std::sort(nodeArray, nodeArray+l.size, node_number_compare);
    }else{
        std::sort(nodeArray, nodeArray+l.size, node_string_compare);
    }
    
    nodeArray[0]->next = NULL;
    for(size_t i=1; i<l.size; ++i){
        
        nodeArray[i]->next = nodeArray[i-1];

    }
    l.head = nodeArray[l.size-1];

}

