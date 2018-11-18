#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <sys/stat.h>   //mkdir
#include <unistd.h>     //rmdir, pwd
#include <pwd.h>        //pwd
#include <dirent.h>     //ls

#include "./Commands/cp.c"
#include "./Commands/cat.c"
#include "./Commands/ls.c"
#include "./Commands/mv.c"
#include "./Commands/pwd.c"
#include "./Commands/sort.c"
#include "./Commands/touch.c"
#include "./Commands/uniq.c"
#include "./Commands/wc.c"
#include "./Commands/free.c"
#include "./Commands/ifconfig.c"
#include "./Commands/lscpu.c"
#include "./Commands/ps.c"



#define CYAN "\x1b[96m"
#define GREEN "\x1b[92m"
#define BLUE "\x1b[94m"
#define BOLDCYAN    "\033[1m\033[36m" 
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDBLUE    "\033[1m\033[34m"  


char *process_input(char *text) {
   int length, c, d;
   char *start;
   
   c = d = 0;
   
   length = strlen(text);
 
   start = (char*)malloc(length+1);
   
   if (start == NULL)
      exit(EXIT_FAILURE);
   
   while (*(text+c) != '\0')
   {
   		if (*(text+c) == ' ')
      	{
        	int temp = c + 1;
         	if (*(text+temp) != '\0') 
         	{
	            while (*(text+temp) != '\0')
	            {
	               	if (*(text+temp) == ' ' || *(text+temp) == '\t')
	               	{
	               		c++;
	               	}  
	               	temp++;
            	}
        	}
    	}
	    *(start+d) = *(text+c);
	    c++;
	    d++;
   	}
   	*(start+d)= '\0';
   
   	return start;
}


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
    input = process_input(input);
    printf("\nprocessed input:%s\n", input);
    while((argval[argcount] = strsep(&input, " \t\n")) != NULL  && argcount < 9)    //strsep(char **stringp, const char *delim);
    {
        printf("\nSTART%sEND Size:%d\n", argval[argcount], strlen(argval[argcount]));
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


void clear()
{
    const char* blank = "\e[1;1H\e[2J";
    write(STDOUT_FILENO,blank,12);
}

int isEmpty_check(const char *str)
{
    char ch;
    do
    {
        ch = *(str++);
        // Check non whitespace character
        if(ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' && ch != '\0')
            return 0;
    } while (ch != '\0');
    return 1;
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
        else if(strcmp(argval[0],"wc")==0)
        {
            char* foldername = argval[1];
            wc_func(foldername);
        }

        else if(strcmp(argval[0],"cp")==0)
        {
            char* source;
            char* terminal;
            source = argval[1];
            terminal = argval[2];

            cp_command(source, terminal);
        }
        else if(strcmp(argval[0],"mv")==0)
        {
            char* source;
            char* terminal;
            source = argval[1];
            terminal = argval[2];

            mv_command(source, terminal);
        }
        // else if(strcmp(argval[0],"rm")==0)
        // {
        //     char* file;
        //     file = argval[1];
        //     rm_command(source, terminal);
        // }
        else if(strcmp(argval[0],"touch")==0)
        {
            touch_func(argcount, argval);
        }
        else if(strcmp(argval[0],"uniq")==0)
        {
            char* file;
            file = argval[1];
            uniq_func(file);
        }
        else if(strcmp(argval[0],"sort")==0)
        {
            char* file;
            file = argval[1];
            sort_func(file);
        }
         else if(strcmp(argval[0],"cat")==0)
        {
            char* file;
            file = argval[1];
            cat_func(file);
        }
        else if(strcmp(argval[0],"ls")==0)
        {
            char* dirname;
            dirname = argval[1];
            ls_func(dirname);
        }
        else if(strcmp(argval[0],"pwd")==0)
        {
            char pwdpath[1000];
            pwd_func(pwdpath,1);
        }
        else if(strcmp(argval[0],"free")==0)
        {
            free_command();
        }
        else if(strcmp(argval[0],"ifconfig")==0)
        {
            ifconfig_command();
        }
        else if(strcmp(argval[0],"lscpu")==0)
        {
            lscpu_command();
        }
        else if(strcmp(argval[0],"ps")==0)
        {
            ps_command();
        }
    }
}