#include <string.h> 
#include <stdio.h>
#include <stdlib.h> 
#include "Structs.h" 
#include "Operations.h"
#include <unistd.h>
#include <sys/wait.h>
#include "History.h"
#include "Parser.h"

extern char* path;

int Separator(Node * root)
  {
      Node *left =root->left;
      int l=left->operation(left);
      Node * right=root->rigth;
      int r= right->operation(right);
      free(root);
  }
   
 int Replace(Node * root)
  {
     int org_stdout = dup(1);
      if( freopen(root->instruction[0],"w+",stdout)== NULL)
     {  
       printf("Error openning file %s \n",root->instruction[0]);
       return 1;
     }   
     Node * x = root->left;
     if(!x->instruction[0])
     {
        free(root);
        dup2(org_stdout,1);
        close(org_stdout);
        return 0;
     } 
      Node *left=root->left;
      int res =left->operation(left);
      dup2(org_stdout,1);
      close(org_stdout);
      free(root);
      return res;
   }

 int Append(Node * root)
  {
      int org_stdout = dup(1);
   
      if(freopen(root->instruction[0],"a+",stdout) == NULL)
     {  
       printf("Error openning file %s \n", root->instruction[0]);
       return 1;
     }
      Node* left=root->left;
      int res =left->operation(left);
      dup2(org_stdout,1);
      close(org_stdout);
      free(root);
      return res;

  } 
  
 int Read(Node * root)
  {
     int org_stdin = dup(0);
     if(freopen(root->instruction[0],"r",stdin)== NULL)
     {  
       printf("Error openning file: %s file doesn't exist or wrong directory\n",root->instruction[0]);
       return 1;
     }
      
      Node* left=root->left;
      int res =left->operation(left);
      dup2(org_stdin,0);
      close(org_stdin);
      free(root);
      return res;
  }
 
 int Cd(Node * root)
  {
    if(root->instruction[1] == NULL)
    {
      if(chdir(path) < 0)
    {
     printf("Error changing directory to %s \n",root->instruction[1]);
     free(root);
     return 1;
    }
    }
    if(chdir(root->instruction[1]) < 0)
    {
     printf("Error changing directory to %s \n",root->instruction[1]);
     free(root);
     return 1;
    }
    free(root);
    return 0;
  }

 int AND(Node *root)
  {
    if(root->left!=NULL)
    {
       Node* left=root->left;
      int r =left->operation(left);
        if(r==0)
        { 
          Node *rigth=root->rigth;
          int res =rigth->operation(rigth);
          free(root);
          return res;
        }
    }
    free(root);
    return 1;
  }
 
 int OR(Node * root)
  {
     if(root->left!=NULL)
     {
       Node* left=root->left;
       int r=left->operation(left);
       if(r!=0)
       {
          Node* rigth=root->rigth;
          int res =rigth->operation(rigth);
          free(root);
          return res;
       }
     }
      free(root);
     return 0;
  }

 int Pipe(Node *root)
  {
    int pipefd[2];
    if(pipe(pipefd)==-1)
    {
      printf("Error creating pipe \n");
      free(root);
      return 1;
    }
    int org_stdout = dup(1);
    dup2(pipefd[1],1);
    close(pipefd[1]);
    
    Node * left=root->left;
    int r=left->operation(left);

    if(r)
    {
      
      dup2(org_stdout,1);
      close(org_stdout);
      fclose(pipefd[0]);
      free(root);
      return 1;
    }
    int org_stdin = dup(0);
    dup2(pipefd[0],0);
    dup2(org_stdout,1);
    close(org_stdout);
    close(pipefd[0]);
    
    Node* rigth= root->rigth;
    int res = rigth->operation(rigth);
    dup2(org_stdin,0);
    close(org_stdin);
    free(root);
    return res;

  }  
  
   int IF_THEN_ELSE(Node *root)
   {
      Node* leftt=root->left;
      int r= leftt->operation(leftt);
     if(r>-1)
     {
       Node * left = root->rigth;
       left = left->rigth; 
        Node* lleft=left->left;
       int res = lleft->operation(lleft);
       free(left);
       free(root->rigth);
       free(root);
       return res;
     }

     Node* left = root->rigth; 
     Node* lleft=left->left;

    return lleft->operation(lleft);
   }
  
 int help(Node* root)
   {
      char* file = calloc(strlen(path)+20,sizeof(char));
      strncpy(file,path,strlen(path));
      strcat(file,"/");
      for (int i = 0; root->instruction[i] !=NULL; i++)
      {
        strcat(file,root->instruction[i]);
     
      }
      strcat(file,".txt");
     int fd = fopen(file,"r");
     if(fd == NULL)
     {
       printf("Comand not implemented \n");
       free(root);
       return 1;
     }
     int p;
     while((p = fgetc(fd))!= EOF)
     {
       printf("%c",p);
     }
    printf("\n");
    free(file);
    free(root);
    fclose(fd);
    return 0;
   }
  int exist_O(Node* root)
  {
    if(root->instruction[1]!=NULL)
            {
              printf("Exit function doesn't needs arguments \n");
            }
            save();
            exit(0);
  }
 int true_O(Node* root)
 {
    if(root->instruction[1]!=NULL)
            {
              printf("True doesn't needs arguments \n");
            }
            free(root);
            return 0;
 }

 int false_O(Node* root)
 {
     if(root->instruction[1]!=NULL)
            {
              printf("False doesn't needs arguments \n");
            }
            free(root);
            return 1;
 }

 int again_O(Node* root)
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
            res =p->operation(p); 
            free(root);
            return res; 
 }

 int history_O(Node* root)
 {
     if(root->instruction[1]!=NULL)
                printf("Too many arguments for history \n");
          free(root);
          return printHistory();
 }

 int child_ejecution(Node* root)
 {
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
      return -1;
 }