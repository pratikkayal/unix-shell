#include <stdio.h>
#include <stdlib.h>


void tail_func(char* numlines, char* filename)
{ 
    int totallines=1;
    int n=atoi(numlines);
    int count=0;

    FILE * file;
    char c;
    file = fopen( filename , "r");
    if (file) 
    {
        while((c=fgetc(file))!=EOF)
        {
            if(c=='\n')
            {
                totallines++;
            }
        }
        fclose(file);
        printf("\n");
    }

    else
    {
      perror("Error");
      exit(0);
    }

    file = fopen( filename , "r");
    if(file)
    {
        
        while((c=fgetc(file))!=EOF)
        {
            if(c=='\n')
            {
                count++;
            }
            if(count+1>=totallines-n)
            {  
                printf("%c",c);         
            }
        }

        if(count ==0)
        {
            perror("Error");
        }
        fclose(file);
        
    }
    else
    {
      perror("Error");
    }
}




// void main(int argc , char *argv[])
// {

//     char* numlines=argv[1];
//     char* filename=argv[2];
//     tail_func(numlines,filename);
 
               
// }
