#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 


static int myCompare (const void * a, const void * b) 
{ 
    return strcmp (*(const char **) a, *(const char **) b); 
} 


void sort_func(char* file_name)
{	
   char ch;
   char arr[100][1000];
   char line[100];

   FILE *fp;
 
   fp = fopen(file_name, "r"); 
 
   if (fp == NULL)
   {
      perror("Error");
   }
  else{
             int i = 0;
             while(fscanf(fp,"%[^\n]\n",line)!=EOF)
             {
             	
             	int j=0;
             	while(j<1000){
             		arr[i][j]=line[j];
             		j++;
             	}
             	i++;
             	if (i==100){
                 char *text = "Error: File is large";
                 printf("%s\n", text); //"File is large.\n"
                 break;
               }  
           }

           if(i!=100){
                          char* arr1[i];
                        int u = 0;

                         while(u < i){
                            arr1[u] = arr[u];
                            u++;
                          }

                         qsort (arr1, i, sizeof (char *), myCompare); 

                         char* c;
                         int k = 0;

                         fclose(fp);

                         k = 0;
                         fp = fopen(file_name,"w+");
                         while(k<i){
                          fprintf(fp,"%s\n", arr1[k]);
                          k++;
                         }

           }

             fclose(fp);
 }
}

void sort_func_o(char* file_name1, char* file_name2)
{ 
   char ch;
   char arr[100][1000];
   char line[100];

   FILE *fp;
 
   fp = fopen(file_name1, "r"); 
 
   if (fp == NULL)
   {
      perror("Error");
   }
  else{
             int i = 0;
             while(fscanf(fp,"%[^\n]\n",line)!=EOF)
             {
              
              int j=0;
              while(j<1000){
                arr[i][j]=line[j];
                j++;
              }
              i++;
              if (i==100){
                 char *text = "Error: File is large";
                 printf("%s\n", text); //"File is large.\n"
                 break;
               }  
           }

           if(i!=100){
                          char* arr1[i];
                        int u = 0;

                         while(u < i){
                            arr1[u] = arr[u];
                            u++;
                          }

                         qsort (arr1, i, sizeof (char *), myCompare); 

                         char* c;
                         int k = 0;

                         fclose(fp);

                         k = 0;
                         fp = fopen(file_name2,"w+");
                         while(k<i){
                          fprintf(fp,"%s\n", arr1[k]);
                          k++;
                         }

           }

             fclose(fp);
 }
}


void sort_func_r(char* file_name)
{ 
   char ch;
   char arr[100][1000];
   char line[100];

   FILE *fp;
 
   fp = fopen(file_name, "r"); 
 
   if (fp == NULL)
   {
      perror("Error");
   }
  else{
             int i = 0;
             while(fscanf(fp,"%[^\n]\n",line)!=EOF)
             {
              
              int j=0;
              while(j<1000){
                arr[i][j]=line[j];
                j++;
              }
              i++;
              if (i==100){
                 char *text = "Error: File is large";
                 printf("%s\n", text); //"File is large.\n"
                 break;
               }  
           }

           if(i!=100){
                        char* arr1[i];
                        int u = 0;

                         while(u < i){
                            arr1[u] = arr[u];
                            u++;
                          }

                         qsort (arr1, i, sizeof (char *), myCompare); 

                         char* c;
                         int k = 0;

                         fclose(fp);

                         k = i-1;
                         fp = fopen(file_name,"w+");

                         while(k > -1){
                          fprintf(fp,"%s\n", arr1[k]);
                          k--;
                         }

           }

             fclose(fp);
 }
}


// int main(int argc, char* argv[])
// {

// 	char* file_name = argv[1];
// 	sort_func(file_name);
// 	return 0;

// }