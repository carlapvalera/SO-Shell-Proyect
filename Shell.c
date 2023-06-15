#include "History.h"
#include "Parser.h"
#include "Operations.h"
#include "Structs.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define KGRN "\x1B[32m"
#define KWHT "\x1B[37m"
#define True 1
char * path;
int stdincpy;
int stdoutcpy;
int stderrcpy;
char * history;
int count;



int main()
{
   stdincpy = dup(0);
   stdoutcpy = dup(1);
   stderrcpy = dup(2);
  
  //Asigno el directorio de trabajo actual 
   path = getcwd(NULL,0);
   //Historial
   history = initialize();
  //Nombre del shell
   const char prompt_name[15] ={'E','R','D','O','S','-','S','H','E','L','L','\0'}; 
   const char pronmpt_end[4] = {' ','$',' ','\0'};
 
  while(1)
  {

   printf("%s%s%s%s",KGRN,prompt_name,KWHT,pronmpt_end);
   char* line= NULL;
   int endPoint=0;
   if(getline(&line,&endPoint,stdin)<0)
   {
     printf("Error reading input line \n");
   }
   //Copiar la linea de entrada
   char *copy = malloc(strlen(line));
  
   strcpy(copy,line);
   if(*line != '\n')
   {
  

   Node* root =parser(line);
  
   int r=root->operation(root); 
   }
   free(line);
    if(*copy != ' ')
   {
     modify(copy);
   }
   free(copy);
}
}
