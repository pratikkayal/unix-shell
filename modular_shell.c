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
// #include "./Commands/w.c"


#define CYAN "\x1b[96m"
#define GREEN "\x1b[92m"
#define BLUE "\x1b[94m"
#define BOLDCYAN    "\033[1m\033[36m" 
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDBLUE    "\033[1m\033[34m"  


//////////////Test Block////////////////////

// #include "minunit.h"

int wc = 0;
int wc_test = 50;
// int test_run =0;
// static char * test_wc() 
// {
//     mu_assert("error, wc is not correct", wc == wc_test);
//     return 0;
// }

// static char * all_tests() {
// mu_run_test(test_wc);
// return 0;
// }

////////////////////////////////////////////

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
    char* aboutStr = "\n  Made By:\n\n \t Pratik Kayal\n\t Pranjali Jain\n\t Naman Jain\n\t Soham Pachpande\n";

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
            wc = wc_func(foldername);
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

            // printf("count %d\n", argcount);
            // printf("%d\n",strlen(argval[1]));
            if(argcount==1)
                ps_command();
            else if(argcount==2) 
            {    
                if(strlen(argval[1])==0)
                    ps_command();
                else
                {
                    ps_command_pid(argval[1]);
                }
            }
            else if(argcount==3)
            {
                if(strcmp(argval[1], "pid") == 0 || strcmp(argval[1], "p") == 0 || strcmp(argval[1], "-pid")==0 || strcmp(argval[1], "-p")==0)
                    ps_command_pid(argval[2]);
            }
        }
        else if(strcmp(argval[0],"gcc")==0)
        {
            int i=0;
            gcc_func(i);

            if(strcmp(argval[2],"-o")!=0) {
                i=1;
                perror("+--- Error in format \n Correct format: gcc filename1 -o filename2 for");}
            else if(argval[3]==NULL || strcmp(argval[2]," ")==0) {
                i=1;
                perror("+--- Error in format \n Correct format: gcc filename1 -o filename2 for");}
            else {
                printf("gcc Done!\n");
                gcc_func(i);
            }

        }
        else if(strcmp(argval[0],"grep")==0)
        {
        	char* text = argval[1];
        	char* filename = argval[2];
        	grep_func(text, filename);
        }
        else if(strcmp(argval[0],"w")==0)
        {
            // w_func();
        }
        else if(strcmp(argval[0],"testwc")==0)
        {
            char* foldername = "./wc_test.txt";
            wc = wc_func(foldername);
            
            if (wc == wc_test)
            {
                printf("Test Successful\n");
            }
            else
            {
                printf("Test Fail\n");
            }

            // char* test_results = all_tests();

            // if (test_result != 0)
            // {
            //     printf("%s\n", test_result);
            // }
            // else
            // {
            //     printf("ALL TESTS PASSED\n");
            // }
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