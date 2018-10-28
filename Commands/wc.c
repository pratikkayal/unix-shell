#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 


void wc_func(char* file_name)
{	
   char arr[100][1000];
   char line[1000];

   FILE *fp;
 
   fp = fopen(file_name, "r"); 
 
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
  
   int i = 0;
   int char_count = 0;
   int word_count = 0;

   while((fgets(line, 1000, fp)) != NULL)
   {
   	int j=0;
    if (strncmp (&line[0]," ",1) != 0){ word_count++; }

   	while(j < strlen(line)){
      if (strncmp (&line[j]," ",1) == 0){ word_count++; }
   		char_count++;
      j++;
   	}
   	i++;
   	if (i==100){
   	  perror("File is large.\n");
      exit(EXIT_FAILURE);
   	} 
 }
   fclose(fp);
   printf("%d   %d   %d   %s\n",i-1,word_count,char_count,file_name);

}

int main(int argc, char* argv[])
{

	char* file_name = argv[1];
	wc_func(file_name);
	return 0;

}