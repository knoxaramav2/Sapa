#include "../headers/InfoStructure.hpp"

#include <stdio.h>

OBase::OBase(string title, LCode type){
  this->title = title;
  this->type = type;

  parent=NULL;
}

Attribute::Attribute(int attr, string val){
  id = attr;
  value = val;
}

Function::Function(string title, LCode type):OBase(title, type){
  this->title = title;
  this->type = type;
}

Object::Object(string title, LCode type):OBase(title, type){
  this->title = title;
}

Namespace::Namespace(string title):OBase(title, lnamespace){

  target=NULL;
}

SContext::SContext(){

  //selectors
  currentObject = NULL;
  //setup global namespace
  Namespace * globalNs = new Namespace("");//empty namespace represents global

  namespaces.push_back(globalNs);
}
