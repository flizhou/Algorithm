// merge.cpp

#include "volsort.hpp"

#include <iostream>

// Prototypes

Node *msort(Node *head, bool numeric);
void  split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, bool numeric);
bool node_number_compare(const Node *a, const Node *b);
bool node_string_compare(const Node *a, const Node *b);
inline bool compare(const Node *a, const Node *b, bool numeric);

// Implementations

void merge_sort(List &l, bool numeric) {
    
    l.head = msort(l.head, numeric);
}

Node *msort(Node *head, bool numeric) {
    

    if(head->next != NULL){
        Node* left, *right;
        split(head, left, right);
        left = msort(left, numeric);
        right = msort(right, numeric);
        head = merge(left, right, numeric);
        
    }
    
    return head;
}

void split(Node *head, Node *&left, Node *&right) {
    
    int size = 0;
    left = head;
    while(head!=NULL){
        ++size;
        head = head->next;
    }
    
    head = left;
    size /= 2;
    while(--size){
        head = head->next;
    }
    
    right = head->next;
    head->next = NULL;
}

Node *merge(Node *left, Node *right, bool numeric) {
    
    Node * head, *curr;
    if(compare(left, right, numeric)){

        head = right;
        right = right->next;
    }else{

        head = left;
        left = left->next;
    }
    
    curr = head;
    while(left and right){
        if(compare(left, right, numeric)){
            curr->next = right;
            curr = right;
            right = right->next;
        }else{
            curr->next = left;
            curr = left;
            left = left->next;
        }

    }
    while(left){
        curr->next = left;
        curr = left;
        left = left->next;

    }
    
    while(right){
        curr->next = right;
        curr = right;
        right = right->next;

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
