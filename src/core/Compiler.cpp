#include <functional>

#include "Compilation.h"
#include "../SDK/headers/InfoStructure.hpp"

Token * copySection(Token * start, Token * end){

  if (start == NULL || end == NULL)
    return NULL;

  Token * seq = NULL;

  for (Token * itr = start; itr <= end; itr=itr->next){
    Token * nTkn = new Token;
    nTkn->raw = itr->raw;
    nTkn->type = itr->type;
    nTkn->next = NULL;

    if (seq==NULL){
      seq = nTkn;
      seq->previous = NULL;
    }else{
      seq->next = nTkn;
      nTkn->previous = seq;
    }

    seq = nTkn;
  }

  return seq;
}

class Node;

class Node{
  function<unsigned(Node*)> logic;

public:

  Node(function<unsigned(Node*)> handle){
    logic = handle;
  }

  ~Node(){

  }

  unsigned invoke(){
    return logic(this);
  }
};

int nestLevel = -1;
LCode nestCodes [256] = {lnan};

//logic node
Node * errorNode;//error
Node * idleNode;//idle node
Node * attrNode;//attribute
Node * typeNode;//type
Node * symNode;//symbol
Node * pTypeNode;//argument type
Node * pSymNode;//argument symbol
Node * pOpNode;//(
Node * pObNode;//{
Node * pOiNode;//[
Node * endNode;//;

//global information
Token * cursor = NULL;
Config * cnf = NULL;
Codestruct * cs = NULL;
Node * node = NULL;
LCode errState = lnan;
static unsigned i = 0;

void constructNodeLogic(){
  idleNode = new Node([] (Node*)->unsigned {printf("Hello world | "); return ++i;});
}

//generates system model from token stream
void Compile(Token*stream, Config&config, Codestruct&codestruct){

  constructNodeLogic();

  Node * current = idleNode;
  cursor = stream;
  cnf = &config;
  cs  = &codestruct;

  while(cursor != NULL){
    //end state check
    if (cursor->type==lpend){
      //validate body closure
      break;
    }

    printf("%u\n", current->invoke());
    //node movement

    cursor=cursor->next;
  }
}
