#include<stdio.h>
#include<string.h>

void grep_func(char* word, char* filename)
{
    printf("commands/grep ke andar%s, %s\n", word, filename);
    FILE *fp;
    char line[1000];
    fp = fopen(filename,"r");
    while(fscanf(fp , "%[^\n]\n" , line)!=EOF)
    {
        if(strstr(line , word) !=NULL)
        {
                // print that line
                printf("%s\n" , line);
        }
        else
        {
                continue;
        }
    }
    fclose(fp);

}

// void main(int argc , char *argv[])
// {
//     char* filename=argv[2];
//     char* word=argv[1];
//     grep_func(word,filename);
// }