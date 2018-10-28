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

void wc_func(char* file_name)
{   
   char line[1000];

   FILE *fp;
 
   fp = fopen(file_name, "r"); 
 
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      // exit(EXIT_FAILURE);
   }
  
   int i = 0;
   int char_count = 0;
   int word_count = 0;

   while((fgets(line, 1000, fp)) != NULL)
   {
    int j=0;
    if (strncmp (&line[0]," ",1) != 0){ word_count++; }

    while(j < strlen(line)){
      if (strncmp (&line[j]," ",1) == 0){ word_count++; }

        char_count++;
      j++;
    }
    i++;
 }
   fclose(fp);
   printf("%d   %d   %d   %s\n",i-1,word_count,char_count,file_name);
}

void cp_command(char* source, char* target)
{
    FILE *file1, *file2;
    
    file1 = fopen(source, "rb");
    // open the source file and check whether it exists
    if (file1 == NULL)
    {
        perror("Error in reading source file\n" );
    }

    file2 = fopen(target, "wb"); // open the target file to write to it

    int line;
    line = fgetc(file1);

    while (line != EOF)
    {
        // putchar(line);
        fputc(line, file2);
        line = fgetc(file1);
    }

    fclose(file1);
    fclose(file2);
}

void mv_command(char* source, char* target)
{
    int returnval;
    // Rename moves the file from previous location to new loaction
    returnval = rename(source, target);

    if( returnval == 0)
    {
        printf("File moved successfully");
    }
    else
    {
        printf("Error: unable to move the file");
    }
}

void rm_command(char* path)
{
    int returnval;
    // Delete the file at path
    returnval = remove(path);

    if( returnval == 0)
    {
        printf("File/Directory deleted successfully");
    }
    else
    {
        printf("Error: unable to delete");
    }
   
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
            char* source, terminal;
            source = argval[1];
            terminal = argval[2];

            cp_command(source, terminal);
        }
        else if(strcmp(argval[0],"mv")==0)
        {
            char* source, terminal;
            source = argval[1];
            terminal = argval[2];

            mv_command(source, terminal);
        }
        else if(strcmp(argval[0],"rm")==0)
        {
            char* file;
            file = argval[1];
            rm_command(source, terminal);
        }

    }
}