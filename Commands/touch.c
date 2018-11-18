#include <stdlib.h> 
#include <stdio.h> 


void touch_func(int argc, char* argv[])
{	
   FILE* fp;
   int i = 1;

   while(i<argc){
    if (strcmp(argv[i],"")!=0){
          fp = fopen(argv[i],"w+"); 

          if (fp == NULL)
         {
            perror("Error");
            break;
         }
          fclose(fp);
          
   }
   i++;
}}

// int main(int argc, char* argv[])
// {
// 	touch_func(argc, argv);
// 	return 0;
// }