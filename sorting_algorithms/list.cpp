#include "volsort.hpp"


List::List() : head(NULL), size(0){
    
}

List::~List() {
    
    while(head!=NULL){
        
        Node* ptr = head->next;
        delete head;
        head = ptr;
    }
}

void List::push_front(const std::string &s){
    
    Node* newNode = new Node;
    newNode->string = s;
    
    if(std::stoi(s)){
        newNode->number = std::stoi(s);
    }else{
        newNode->number = 0;
    }
    
    newNode->next = head;
    head = newNode;
    ++ size;
}


