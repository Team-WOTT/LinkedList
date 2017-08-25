#ifndef NODE_H
#define NODE_H

#include "student.h"

struct Node{
  Node* next;
  Student data;

  Node(){
    next = nullptr;
    data = Student();
  }

  Node(const Student& tData){
    next = nullptr;
    data = tData;
  }

  Node(const Node* tNode){
    next = nullptr;
    data = tNode->data;
  }

};
#endif
