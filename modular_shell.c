#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <sys/stat.h>   //mkdir
#include <unistd.h>     //rmdir, pwd
#include <pwd.h>        //pwd
#include <dirent.h>     //ls
#include <readline/readline.h>


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
#include "./Commands/grep.c"



#define CYAN "\x1b[96m"
#define GREEN "\x1b[92m"
#define BLUE "\x1b[94m"
#define BOLDCYAN    "\033[1m\033[36m" 
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDBLUE    "\033[1m\033[34m"  

char* input;
char* argval[10];
int argcount = 0;
int exitflag=0;

void process_input_inplace(char *text) 
{
	char* final = text;

	// loop while end of string '\0' is not reached
	while(*text != '\0')
	{
		// while((*text == ' ' && *(text+1) == ' ') || (*text == '\t' && *(text+1) == '\t'))
		while(((*(text) == ' ') || (*(text) == '\t')) && ((*(text+1) == ' ')||(*(text+1) == '\t')))
		{
			text++;
		}
		*final++ = *text++;
	}

	*final = '\0';	
}


void getInput()
{
    fflush(stdout); // clear all previous buffers if any
    // input = NULL;
    ssize_t buf = 0;
    // getline(&input,&buf,stdin);
     input = readline("> ");
    if (input) {

    argcount = 0;
    process_input_inplace(input);
    // printf("\nprocessed input:%s\n\n", input);
    while((argval[argcount] = strsep(&input, " \t\n")) != NULL  && argcount < 9)    //strsep(char **stringp, const char *delim);
    {
        // printf("\nSTART%sEND\n", argval[argcount]);
        if(sizeof(argval[argcount])==0)
        {
            free(argval[argcount]);
        }
        else argcount++;
    }
    free(input);
    }
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

    if(retCode==-1)
    {
        perror("+--- Error in mkdir ");
    }
    
}

void gcc_func(int i){
    if(i=0)
        execlp("gcc","gcc",argval[1],argval[2],argval[3],(char *)NULL);

}

/* Remove a folder */
void rmdir_func(char* name)
{
    int retCode = rmdir(name);
    if(retCode==-1)
    {
        perror("+--- Error in rmdir ");
    }
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
        getInput();

        if(strcmp(argval[0],"about")==0)
        {
            about();
        }
        else if(strcmp(argval[0],"mkdir")==0)
        {
            if(argval==NULL) perror("+--- Error in mkdir ");
            else
            {
                char* foldername = argval[1];
                mkdir_func(foldername);
            }
        }
        else if(strcmp(argval[0],"exit")==0)
        {
            exitflag=1;
        }
        else if(strcmp(argval[0],"rmdir")==0)
        {
            if(argval==NULL) perror("+--- Error in rmdir ");
            else
            {
                char* foldername = argval[1];
                rmdir_func(foldername);
            }
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
        else if(strcmp(argval[0],"gcc")==0)
        {
            int i=0;
            // if(argval[1]=='-o') perror("+--- Error in rmdir ");
            if(argval[2]=='-o') perror("+--- Error in format ");
            else if(argval[3]!=NULL) perror("+--- Error in format ");
            gcc_func(i);
        }
        else if(strcmp(argval[0],"grep")==0)
        {
        	char* text = argval[1];
        	char* filename = argval[2];
        	grep_func(text, filename);
        }
        else if(strcmp(argval[0],"")==0)
        {

        }
        else
        {   
            char *text = "Error: No Such Command Exists. Please type a valid command."; 
            printf("%s\n", text);
        }
    }
}