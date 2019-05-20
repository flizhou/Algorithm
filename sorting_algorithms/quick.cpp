// quick.cpp

#include "volsort.hpp"

#include <iostream>

// Prototypes

Node *qsort(Node *head, bool numeric);
void  partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric);
Node *concatenate(Node *left, Node *right);
bool node_number_compare(const Node *a, const Node *b);
bool node_string_compare(const Node *a, const Node *b);
inline bool compare(const Node *a, const Node *b, bool numeric);
void dump_node(Node *n);

// Implementations

void quick_sort(List &l, bool numeric) {
    
    l.head = qsort(l.head, numeric);
}

Node *qsort(Node *head, bool numeric) {
    
    if(head->next != NULL){
        
        Node *left, *right;
        partition(head->next, head, left, right, numeric);
        if(left){
            left = qsort(left, numeric);
        }
        if(right->next){
            right->next = qsort(right->next, numeric);
        }

        head = concatenate(left, right);
        
    }
    
    return head;
}

void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric) {
    
    Node * curr_left, *curr_right;
    curr_right = right = pivot;
    
    while(head and compare(head, pivot, numeric)){
        curr_right = head;
        head = head->next;
    }
    curr_left = left = head;

    while(head and head->next){
        head = head->next;
        if(compare(head, pivot, numeric)){
            curr_right->next = head;
            curr_right = head;
        }else{
            curr_left->next = head;
            curr_left = head;
        }
    }

    if(curr_left){
        curr_left->next = NULL;
    }
    if(curr_right){
        curr_right->next = NULL;
    }

}

Node *concatenate(Node *left, Node *right) {
    
    Node *head;
    if(left){
        head = left;
        while(left and left->next){
            left = left->next;
        }
        left->next = right;
    }else{
        head = right;
    }
    return head;
}

inline bool compare(const Node *a, const Node *b, bool numeric){

    if(numeric){
        return node_number_compare(a, b);
    }else{
        return node_string_compare(a, b);
    }
}
