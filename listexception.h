#pragma once
#ifndef LISTEXCEPTION_H
#define LISTEXCEPTION_H
#include <exception>

class ListException : public std::exception{
public:
  virtual const char* overflow() const throw(){ //Stack overflow case
    return "Error: Attempt to add to full list results in overflow.";
  }
  virtual const char* underflow() const throw(){ //Stack underflow case
    return "Error: Attempt to remove from list that is empty results in underflow";
  }
  /*virtual const char* greaterthan() const throw(){ //top greater than attempted moved disk
    return "";
  }*/
};
#endif
