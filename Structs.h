#ifndef STRUCT_H 
#define STRUCT_H


typedef int (*operations)(Node);

typedef struct 
{
  
  operations operation;
  char** instruction; 
  struct Node* left;
  struct Node* rigth;

}Node;
#endif