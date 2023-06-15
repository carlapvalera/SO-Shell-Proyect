#include <string.h> 
#include <stdio.h>
#include <stdlib.h> 
#include "Structs.h"
int Manage(Node * root)
{
if(root->instruction[0] !=NULL)
   {
          if(strcmp(root->instruction[0],"cd")==0)
          {
            return Cd(root);
          }
          else if(strcmp(root->instruction[0],"exit")==0)
          {
            if(root->instruction[1]!=NULL)
            {
              printf("Exit function doesn't needs arguments \n");
            }
            save();
            exit(0);
          }
          else if(strcmp(root->instruction[0],"true")==0)
          {
            if(root->instruction[1]!=NULL)
            {
              printf("True doesn't needs arguments \n");
            }
            free(root);
            return 0;
          }
          else if(strcmp(root->instruction[0],"false")==0)
          {
            if(root->instruction[1]!=NULL)
            {
              printf("False doesn't needs arguments \n");
            }
            free(root);
            return 1;
          }
          else if(strcmp(root->instruction[0],"help")==0)
          {
            return help(root);
          }
          else if(strcmp(root->instruction[0],"again")==0)
          {
            if(root->instruction[1]==NULL)
            {
              printf("Again function needs arguments \n");
              free(root);
              return 1;
            }
            char * endptr;
            int res = strtol(root->instruction[1],&endptr,10);
            if(*endptr != '\0')
            {
              printf("Invalid again arguments");
              free (root);
              return 1;
            }
          char *comand = again(res);
          Node* p =parser(comand);
          res =Manage(p); 
          free(root);
          return res; 
          }
          else if(strcmp(root->instruction[0],"history")==0)
          {
            if(root->instruction[1]!=NULL)
                printf("Too many arguments for history \n");
          free(root);
          return printHistory();
          }
          else{
          int pid;
          int status;

          if((pid=fork())==0)
          {
            execvp(root->instruction[0],root->instruction);
          }
          else if(pid>0)
          {
            waitpid(pid,&status,WUNTRACED);
            free(root);
            return !(status>=0);
          }
        
          }
          return 0;
      }
   }

