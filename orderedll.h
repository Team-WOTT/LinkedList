#pragma once
#ifndef ORDEREDLL_H
#define ORDEREDLL_H

#include "node.h"
#include "listexception.h"
#include <iostream>
#include <iomanip>

using namespace std;

template<class Type>
class OrderedLL{
private:
  ListException exception;
  Type* tail;
  Type* location; //Location storage for See at/see next
  int length;
public:
  OrderedLL();

  ~OrderedLL();

  void addItem(Type* node);

  Type* getItem(Type* node); //finds/removes item

  bool isInList(Type* node); //returns true if item exists

  Type* seeNext(); //returns item without removing

  Type* seeAt(int location); //returns item at location without removing

  void reset(); //resets the location that seeNext uses to point

  int size();

  bool isEmpty();

  void makeEmpty();

  void print();
};

template<class Type>
OrderedLL<Type>::OrderedLL(){
  tail = nullptr;
  location = nullptr;
  length = 0;
}

template<class Type>
OrderedLL<Type>::~OrderedLL(){
  makeEmpty();
}

template<class Type>
void OrderedLL<Type>::addItem(Type* node){
  Type* searched = tail;
  while(searched != nullptr && searched->next != nullptr && length > 1 && searched->next->data > node->data){
    searched = searched->next;
  }
  if(length > 1 && searched != nullptr && searched->next != nullptr && searched->data > node->data && searched->next->data < node->data){
    node->next = searched->next;
    searched->next = node;
  }else if(length == 0 || (length > 1 && searched != nullptr && searched->data == tail->data)){
    node->next = searched;
    if(location == tail){
      location = node;
    }
    tail = node;
  }else if(searched != nullptr && searched->next == nullptr){
    Node* tmp = searched->next;
    searched->next = node;
    node->next = tmp;
  }
  length++;
}

template<class Type>
Type* OrderedLL<Type>::getItem(Type* node){
  Type* searched = tail;
  Type* found = nullptr;
  if(tail == nullptr){
    throw exception.underflow();
  }
  if(searched->data == node->data){ //check to see if node is tail
    found = new Node(searched);
    tail = searched->next; //move tail
    delete searched;
    length--;
  }
  while(found == nullptr && searched->next != nullptr){
    if(searched->next->data == node->data){ //check to see if next value is node
      found = new Node(searched->next); //set found as the target node
      Type*tmp = searched->next->next;
      delete searched->next;
      searched->next = tmp; //make sure the current node now points to the node after the target
      length--;
    }else{
      searched = searched->next;
    }
  }
  return found;
}

template<class Type>
Type* OrderedLL<Type>::seeNext(){
  if(location == nullptr){
    location = tail;
    return nullptr;
  }
  Type* retNode = new Node(location->data);
  cout << retNode->data.getName() << endl;
  location = location->next;
  return retNode;
}

template<class Type>
Type* OrderedLL<Type>::seeAt(int loc){
  int counter = 0;
  Node* searched = tail;
  while(abs(length-counter-1) > loc && searched != nullptr){
    searched = searched->next;
    counter++;
  }
  if(searched == nullptr){
    throw exception.seeOutOfRange();
  }
  cout << counter << endl;
  location = searched->next;
  Type* retNode = new Node(searched->data);
  return retNode;
}

template<class Type>
bool OrderedLL<Type>::isInList(Type* node){
  Type* searched = tail;
  while(searched != nullptr){
    if(searched->data == node->data){
      return true;
    }else{
      searched = searched->next;
    }
  }
  return false;
}

template<class Type>
bool OrderedLL<Type>::isEmpty(){
  return length == 0;
}

template<class Type>
void OrderedLL<Type>::reset(){
  location = tail;
}

template<class Type>
int OrderedLL<Type>::size(){
  return length;
}

template<class Type>
void OrderedLL<Type>::makeEmpty(){
  Type* tmp;
  reset();
  while(!isEmpty()){
    tmp = tail->next;
    delete tail;
    tail = tmp;
    length--;
  }
}

template<class Type>
void OrderedLL<Type>::print(){
  char separator = ' ';
  int nameWidth = 9;
  int MNumWidth = 9;
  int max_fields = 5;
  for(int i = 0;i < max_fields;i++){
    Node* toPrint = tail;
    while(toPrint != nullptr){
      if( i > 0 && i < max_fields-1){
        switch(i){
          case 1:{
            toPrint->data.printName();
            break;
          }
          case 2:{
            toPrint->data.print("Age: " + toPrint->data.getAge(),0);
            break;
          }
          case 3:{
            toPrint->data.print(toPrint->data.getMNumber(),0);
          }
        }
        if(i == 1){
          cout << setw((nameWidth-length)/2-1) << " | NEXT | -> "; //Name line
        }else{
          cout << setw((nameWidth-length)/2-1) << " |      |    "; //All other lines
        }
      }else{
        cout << setfill('-') << setw(nameWidth+MNumWidth) << "-"; //top bar
        cout << setfill(separator) << setw(nameWidth-5) << " "; //top bar
      }
      toPrint = toPrint->next;
    }
    if(i != 1){
      cout << endl;
    }else{
      cout << "NULL" << endl; //Print null for end of list
    }
  }
}
#endif
