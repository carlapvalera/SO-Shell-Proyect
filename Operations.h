#ifndef OPERATIONS_H
#define OPERATIONS_H
#include "Structs.h"
int Separator(Node * root);
int Replace(Node * root);
int Append(Node * root);
int Read(Node * root);
int Cd(Node * root);
int AND(Node *root);
int OR(Node * root);
int Pipe(Node *root);
int IF_THEN_ELSE(Node *root);
int help(Node * root);
int exist_O(Node* root);
int true_O(Node*root);
int false_O(Node* root);
int again_O(Node* root);
int history_O(Node* root);
int child_ejecution(Node* root);
#endif