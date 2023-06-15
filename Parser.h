#ifndef PARSER_H
#define PARSER_H
#include "Structs.h"
Node * Tree(char *line); 
Node * parser(char * text);
char** comnd(char* line);
int others_func(Node * root);

#endif