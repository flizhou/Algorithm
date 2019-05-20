// qsort.cpp

#include "volsort.hpp"

#include <cstdlib>
#include <array>
#include <iostream>

int node_number_compare(const void *a, const void *b);
int node_string_compare(const void *a, const void *b);

void qsort_sort(List &l, bool numeric) {

    Node nodeArray[l.size];
    Node* curr = l.head;
    
    for(size_t i=0; i<l.size; ++i){
        
        nodeArray[i] = *curr;
        curr = curr->next;

    }
    
    if(numeric){
        std::qsort(&nodeArray, l.size, sizeof(Node), node_number_compare);
    }else{
        std::qsort(&nodeArray, l.size, sizeof(Node), node_string_compare);
    }
    
    curr = l.head;
    for(size_t i=0; i<l.size; ++i){
        
        curr->string = nodeArray[i].string;
        curr->number = nodeArray[i].number;
        nodeArray[i].next = &nodeArray[i-1];
        curr = curr->next;
    }
    
}

int node_number_compare(const void *a, const void *b){

    return (*(Node*)a).number- (*(Node*)b).number;
}

int node_string_compare(const void *a, const void *b){

    return std::strcmp((*(Node*)a).string.c_str(),(*(Node*)b).string.c_str());
}
