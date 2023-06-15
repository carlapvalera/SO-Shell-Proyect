#include "Structs.h"
#include "Parser.h"

//new
#include "Operations.h"

#include <string.h> 
#include <stdio.h>
#include <stdlib.h> 

/*La función recibe un puntero con lo introducido de consola y devuelve un arbol de nodos
con las instrucciones y punteros que referencian a las funciones que deben tomar 
*/


Node * parser(char * text)
{
  if(text==NULL)
  {
    return NULL;
  }

  char *index;
  if(index  = strchr(text ,'\n'))
    *index = '\0'; 

  if(index= strchr(text ,'#'))
  {
  *index = '\0';
  }
  return Tree(text);
} 
/* Este metodo es el que devuelve el arbol Tree de comandos donde mientras mas abajo en el arbol est'e el comando 
m'as prioridad tiene en la ejecuci'on */
Node * Tree(char *line)
{
   char *del; 
   Node * result = (Node*)malloc(sizeof(Node));
   //Split
   if(del = strchr(line,';'))
   {
      *del = '\0';
      
          result->operation=Separator;

        result->instruction = NULL;
         //Parte antes del ;
        result->left = Tree(line);
        //Parte después del ;
        result->rigth = Tree(++del);
      return result;
   }
// IF
    if( del = strstr(line,"if "))
   {  
      char * del2;
      if(!( del2= strstr(line," then ")))
      {
          printf("if-then-else-end sintax error \n");
          return NULL;
      }
      *del2  ='\0';
      result->operation=IF_THEN_ELSE;
      result->instruction = NULL;
      result->left = Tree(del+=3);
      result->rigth = Tree(++del2);
      return result;
   }
   if( del = strstr(line,"then "))
   {  
      char * del2;
      if(!( del2= strstr(line," else ")))
      {
          printf("if-then-else-end sintax error \n");
          return NULL;
      }
      *del2  ='\0';

      result->instruction = NULL;
      result->left = Tree(del+=5);
      result->rigth = Tree(++del2);
      return result;
   }
    if( del = strstr(line,"else "))
   {  
      char * del2;
      if(!( del2= strstr(line," end")))
      {
           printf("if-then-else-end sintax error \n");
          return NULL;
      }
      *del2  ='\0';
      result->instruction = NULL;
      result->left = Tree(del+=5);
      result->rigth = NULL;
      return result;
   }
   del = line;
   // operaciones logicas
   while(del = strpbrk(++del,"|&"))
   {
        if(*del == '|' && *(del+1)== '|')
        {
          *del = '\0';
          result->operation=OR;
          result->instruction = NULL;
          result->left = Tree(line);
          result->rigth = Tree(del+=2);
          return result;
        }
        if(*del == '&' && *(del+1)== '&')
      {
          *del = '\0';
          result->operation=AND;
          result->instruction = NULL;
          result->left = Tree(line);
          result->rigth = Tree(del+=2);
          return result;
        }
   }

   // si es un Pipe
   if(del = strchr(line,'|'))
   {   *del = '\0';
      
      
        result->instruction=Pipe;
        result->instruction = NULL;
        result->left = Tree(line);
        result->rigth = Tree(++del);
        return result;
   }
   //No tiene hijos
   Node * R = NULL;
   Node * WA = NULL;
   if(del = strpbrk(line,"><"))
   {

     char *read = NULL; 
     char *write_apnd =NULL;

      if(read = strrchr(line,'<'))
      {
        do
        read++;
        while(*read == ' ');
        R =  (Node*)malloc(sizeof(Node));
        R->instruction=Read;
        R->left=NULL;
        R->rigth =NULL;
        char ** file = malloc(sizeof(char*));
        file[0]= read;
        R->instruction = file;
      }
      if(write_apnd = strrchr(line,'>'))
      {
        WA =  (Node*)malloc(sizeof(Node));
        WA->left=NULL;
        WA->rigth =NULL;
      if(*(write_apnd-1) == '>')
      {
        WA->operation=Append;
      }
        else 
        {
         WA->operation=Replace;}

        do
        write_apnd++;
        while(*write_apnd == ' '); 
        char** file =malloc(sizeof(char*));
        file[0]= write_apnd;
        WA->instruction = file;
      }
      if(write_apnd && (write_apnd = strpbrk(write_apnd,">< ")))
      {
           *write_apnd='\0';
      }
       if(read && (read = strpbrk(read,">< ")))
      {
           *read='\0';
      }
        *del= '\0';
   }
   char ** comand=comnd(line);
  result->instruction =comand;
  others_func(result);
      
  result->left = NULL;
  result->rigth = NULL;

  if(R)
  {
    if(WA)
    {
      R->left = WA;
      WA->left = result;
    }
    else{
      R->left = result;
    }
    return R;
  }
  else if(WA)
  {
    WA->left = result;
    return WA;
  }

  return result;
}

char** comnd(char* line)
{

     while(*line== ' ')
         line++; 

     int size =0;
     char* index = line;
     while(index = strchr(index,' '))
     {
       size++;
       index++;
     }
     index=line;
     char ** comand = calloc(size +2,1);
     int argc =0;
     char* delim;

 

    while (delim = strchr(line,' '))
    {
      *delim = '\0';
       comand[argc++] = line;
       line = delim + 1;
       while (*line && (*line== ' '))
       line++;
   }
   
   if(strlen(line)==0)
     comand[argc] = NULL;
   else{

    comand[argc++] = line;
    comand[argc] = NULL;
   }
   return comand;
}


int others_func(Node * root)
{
if(root->instruction[0] !=NULL)
   {
          if(strcmp(root->instruction[0],"cd")==0)
          {
            root->operation=Cd;
          }
          else if(strcmp(root->instruction[0],"exit")==0)
          {
            root->operation=exist_O;
          }
          else if(strcmp(root->instruction[0],"true")==0)
          {
            root->operation=true_O;
          }
          else if(strcmp(root->instruction[0],"false")==0)
          {
             root->operation=false_O;
          }
          else if(strcmp(root->instruction[0],"help")==0)
          {
            root->operation=help;
          }
          else if(strcmp(root->instruction[0],"again")==0)
          {
             root->operation=again_O;
          }
          else if(strcmp(root->instruction[0],"history")==0)
          {
            root->operation=history_O;
          }
          else{
              root->operation=child_ejecution;
          }
          return 0;
      }
   }

