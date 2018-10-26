#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <sys/stat.h>

char * input;
// char * input1;
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
    while((argval[argcount] = strsep(&input, " \t\n")) != NULL  && argcount < 9)
    {
        if(sizeof(argval[argcount])==0)
        {
            free(argval[argcount]);
        }
        else argcount++;
        if(strcmp(argval[argcount-1],"&")==0)
        {
            return;
        }
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



int main(int argc, char* argv[])
{
	printf("Welcome to the new unix shell!!\n");
    while(exitflag==0)
    {
    	printf(">>");
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

	}
}