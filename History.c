#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "History.h"

extern char* path;
extern char* history;
extern int count;

char* initialize()
{
   int size=0;
   char * cpypath = calloc(strlen(path) + 13,1);
   cpypath = strcpy(cpypath,path);
   cpypath = strcat(cpypath,"/history.txt");
   FILE* histtxt = fopen(cpypath,"r+");
   if(histtxt == NULL)
   {
      printf("Error al abrir el archivo de la ruta %s",cpypath);
      return NULL;
   }
   //Contar cant de carácteres en el historial
   int c;
   while( (c =fgetc(histtxt)) != EOF)
   {
      size++;
   }
   size++;
   size*=2;
   //Cerrar el archivo
   fclose(histtxt);
   //Crear un array de char con 1024 espacion mas el del historial anterior
   char * history = malloc(1024 + size);
   int args =0;

   histtxt = fopen(cpypath,"r+");
// Copio el historial 
   while( (c =fgetc(histtxt)) != EOF)
   {
      if((char)c == '\n')
      {
         count ++;
      }
      history[args++]= (char)c; 
   }
   fclose(histtxt);
return history;

}

int modify(char * comand)
{
     char *del;
     int arg =0;
     char* num;

        
         if(del = strstr(comand,"again "))
        {
           // realloc(history,(del - comand));
            strncat(history,comand,del-comand);
            char * endptr;
            del+=6;
            while(del==' ')
            del++;
            int n = strtol(del,&endptr,10);
            if(endptr!= '\0' || n >10 || n<1)
            {
               strcat(history,comand);
            }
            else{
            num = again(n);
            strcat(history,num);
            strcat(history,endptr);
            count +=1;
            }
        }
        else
        {
        strcat(history,comand);
        count +=1;
        }

       if(count >10)
       {
     history = strchr(history,'\n');
     *history = '\0';
     history++;
     count -=1;
      }
  
     return 0;     
}



int save()
{
char * cpypath = calloc(strlen(path),1);
cpypath = strcpy(cpypath,path);
int histtxt = fopen(strcat(cpypath,"/history.txt"),"w+");
if(!histtxt)
{
   printf("Error al abrir el archivo de la ruta %s /n",path);
   return 1;
}
int argc =0;
while(history[argc] != '\0')
{
  fputc(history[argc++],histtxt);
}
fclose(histtxt);
return 0;
}

char * again(int num)
{
   if(num <1 || num > count) 
   {
      printf("Error, Invalid again arguments \n");
      return NULL;
   }
   char *  ops = history;
   
   while(num > 1)
   {
       ops = strchr(ops,'\n');
       ops++;
       num --;
   }
   
   char * end = strchr(ops,'\n');
   int s = end - ops;
   char* ag = calloc(s+1,1);
   strncpy(ag,ops,s);
   return ag;
   
}
int printHistory()
{
int argc =0;
int cur = 2;
if(count ==10)
{
  char * str = strchr(history,'\n');
  argc= str -history +1;
}
printf("1: ");
while(history[argc] != '\0')
{
    if(history[argc] == '\n')
    {
      printf("\n%d: ", cur++);
      argc++;
    }
      else
       printf("%c",history[argc++]);
   
}
printf("history\n");

return 0;
}