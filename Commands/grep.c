#include<stdio.h>
#include<string.h>

void grep_func(char* word, char* filename)
{   

    //int w = strlen(word);

    printf("%s %s\n",word,filename);
    FILE * file;
    char c;
    char line[1000];
    memset(line,0,sizeof(line));
    int count=0;
    int j=0;

    int flag=0;

    file = fopen( filename , "r");
    
    if (file) 
    {   
        
        while((c=fgetc(file))!=EOF)
        {       
            if(c=='\n')
            {
                line[j]='\0';
            
                if(strstr(line , word)!=NULL)
                {
                    flag=1;
                    printf("%s\n",line);
                }
                memset(line,0,sizeof(line));
                j=0;
                count++;
            }
            else
            {
                line[j]=c;
                j++;
            }

        }
    
        if(flag==0)
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


void grep_func_linecount(char* word, char* filename, char* options)
{   

    //int w = strlen(word);

    FILE * file;
    char c;
    char line[1000];
    memset(line,0,sizeof(line));
    int count=0;
    int j=0;

    int flag=0;

    file = fopen( filename , "r");
    
    if (file) 
    {   
        while((c=fgetc(file))!=EOF)
        {       
            if(c=='\n')
            {
                line[j]='\0';

                if(strstr(line , word)!=NULL)
                {
                    flag=1;
                    printf("%d\t",count+1);
                    printf("%s\n",line);
                }
                memset(line,0,sizeof(line));
                j=0;
                count++;
            }
            else
            {
                line[j]=c;
                j++;
            }

        }
    
        if(flag==0)
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
//     char* filename=argv[2];
//     char* word=argv[1];
//     grep_func(word,filename);
// }