#include <stdio.h>
#include <stdlib.h>
#include<stdio.h>

void head_func(char* numlines, char* filename)
{ 
  int count=0;
  int n=atoi(numlines);


  FILE * file;
  char c;
  file = fopen( filename , "r");
  if (file) 
  {
      while((c=fgetc(file))!=EOF)
      {
          if(count+1<=n)
          {         printf("%c",c);
                    if(c=='\n')
                    {
                        count++;
                    }
          }
      }
      
      if(count==0)
      {
          perror("File is empty\n");
      }

      fclose(file);
  }
  else
  {
    perror("No such file\n");
  }
}




// void main(int argc , char *argv[])
// {

//     char* numlines=argv[1];
//     char* filename=argv[2];
//     head_func(numlines,filename);
 
               
// }
