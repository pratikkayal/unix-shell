#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

void uniq_func(char* file_name)
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


             if (i!=100){
                           char* arr1[i];
                          char* arr2[i];

                          int u = 0;

                           while(u < i){
                              arr1[u] = arr[u];
                              u++;
                            }

                        int y, r, p;
                        int flg = 0;

                        p = 0;
                        y = 0;

                          while(y<i){
                            flg = 0;
                            r = 0;

                            while(r<p){
                              if (*arr1[y] == *arr2[r]){
                                flg = 1;
                              }
                              r++;
                            }


                            if (flg!=1){
                              arr2[p] = arr1[y];
                              p++;
                            }
                            y++;
                          }
                           // qsort (arr1, i, sizeof (char *), myCompare); 

                           char* c;
                           int k = 0;

                           fclose(fp);

                           k = 0;
                           fp = fopen(file_name,"w+");

                           while(k<p){
                            fprintf(fp,"%s\n", arr2[k]);
                            k++;
                           }


             }
               fclose(fp);


  }


}

// int main(int argc, char* argv[])
// {

// 	char* file_name = argv[1];
// 	uniq_func(file_name);
// 	return 0;

// }