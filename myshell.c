#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <sys/stat.h>   //mkdir
#include <unistd.h>     //rmdir, pwd

char * input;
char* argval[10];
int argcount = 0;
int exitflag=0;

void getInput()
{
    fflush(stdout); // clear all previous buffers if any
    input = NULL;
    ssize_t buf = 0;
    getline(&input,&buf,stdin);
    argcount = 0;
    while((argval[argcount] = strsep(&input, " \t\n")) != NULL  && argcount < 9)    //strsep(char **stringp, const char *delim);
    {
        // printf("START%sEND", argval[argcount]);
        if(sizeof(argval[argcount])==0)
        {
            free(argval[argcount]);
        }
        else argcount++;
    }
    free(input);
}

/* about function*/
void about()
{
    char* aboutStr = "\n  Made By:\n\n \t Pratik Kayal\n\t Pranjali Jain\n\t Naman Jain\n\t Soham Pachpandes\n";

    printf("%s",aboutStr);
}

/* Make a new folder */
void mkdir_func(char* name)
{
    int retCode = mkdir(name,0777);// 0777 for widest possible permissions given to mkdir
    
}

/* Remove a folder */
void rmdir_func(char* name)
{
    int retCode = rmdir(name);
    
}

void pwd_func(char* pwdpath,int printornot) // if printornot=1 --> print 
{
    char temp[1000];
    char* path=getcwd(temp, sizeof(temp));
    if(path != NULL)
    {
        strcpy(pwdpath,temp);
        if(printornot==1)  
        {
            printf("%s\n",pwdpath);
        }
    }
    else 
    {

    }
}

void clear()
{
    const char* blank = "\e[1;1H\e[2J";
    write(STDOUT_FILENO,blank,12);
}


int main(int argc, char* argv[])
{
    printf("Welcome to the new unix shell!!\n");
    while(exitflag==0)
    {
        char temp[1000];
        char* path=getcwd(temp, sizeof(temp));
        printf("%s>>", temp);
        // printf(">>");
        // scanf("%s",input); //fails due to spaces, tabs
        getInput();

        if(strcmp(argval[0],"about")==0)
        {
            about();
        }
        else if(strcmp(argval[0],"mkdir")==0)
        {
            char* foldername = argval[1];
            mkdir_func(foldername);
        }
        else if(strcmp(argval[0],"exit")==0)
        {
            exitflag=1;
        }
        else if(strcmp(argval[0],"rmdir")==0)
        {
            char* foldername = argval[1];
            rmdir_func(foldername);
        }
        else if(strcmp(argval[0],"clear")==0)
        {
            clear();
        }
    }
}