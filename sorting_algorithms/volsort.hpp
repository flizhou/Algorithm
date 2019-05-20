// volsort.hpp

#ifndef volsort_hpp
#define volsort_hpp

#include <string>
#include <iostream>

struct Node {
    std::string string;
    int         number;
    Node       *next;
};

struct List {
    Node       *head;
    size_t      size;
    
    List();                     // define in list.cpp
    ~List();                    // define in list.cpp
    
    void push_front(const std::string &s);    //define below
};


#endif
