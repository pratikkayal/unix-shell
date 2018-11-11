#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <sys/stat.h>   //mkdir
#include <unistd.h>     //rmdir, pwd
#include <pwd.h>        //pwd
#include <dirent.h>     //ls
#define CYAN "\x1b[96m"
#define GREEN "\x1b[92m"
#define BLUE "\x1b[94m"
#define BOLDCYAN    "\033[1m\033[36m" 
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDBLUE    "\033[1m\033[34m"  



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

void wc_func(char* file_name)
{   
   char line[1000];

   FILE *fp;
 
   fp = fopen(file_name, "r"); 
 
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
   }
  
   int i = 0;
   int char_count = 0;
   int word_count = 0;

   while((fgets(line, 1000, fp)) != NULL)
   { 
    int j=0;
    if (strncmp (&line[0]," ",1) != 0){ word_count++; }

    while(j < strlen(line)){
      if (!isEmpty_check(line)){
      if (strncmp (&line[j]," ",1) == 0){ word_count++; }
    }
        char_count++;
      j++;
    }
    i++;
 }

   fclose(fp);
   printf("%d   %d   %d   %s\n",i-1,word_count,char_count,file_name);
}


void touch_func(int argc, char* argv[])
{   
   FILE* fp;
   int i = 1;

   while(i<argc){

    fp = fopen(argv[i],"w+");
    fclose(fp);
    i++;

   }

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



void uniq_func(char* file_name)
{ 
   char ch;
   char arr[100][1000];
   char line[100];

   FILE *fp;
 
   fp = fopen(file_name, "r"); 
 
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
  
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
      perror("File is large.\n");
      exit(EXIT_FAILURE);
    } 
 }

  char* arr1[i];
  char* arr2[i];

  int u = 0;

   while(u < i){
      arr1[u] = arr[u];
      u++;
    }

int y, r, p;
int flg = 0;

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

   while(k<p){
    printf("%s\n", arr2[k]);
    k++;
   }

}

static int myCompare (const void * a, const void * b) 
{ 
    return strcmp (*(const char **) a, *(const char **) b); 
} 


void sort_func(char* file_name)
{   
   char ch;
   char arr[100][1000];
   char line[100];

   FILE *fp;
 
   fp = fopen(file_name, "r"); 
 
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
   }
  
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
      perror("File is large.\n");
    } 
 }

  char* arr1[i];
  int u = 0;

   while(u < i){
        arr1[u] = arr[u];
        u++;
    }

   qsort (arr1, i, sizeof (char *), myCompare); 

   char* c;
   int k = 0;

   fclose(fp);

   k = 0;
   fp = fopen(file_name,"w+");
   while(k<i){
    fprintf(fp,"%s\n", arr1[k]);
    k++;
   }
   fclose(fp);

}


void cat_func(char* filename)
{ 

  FILE * file;
  char c;
  file = fopen( filename , "r");
  if (file) 
  {
      while((c=fgetc(file))!=EOF)
      {
          printf("%c",c);
      }
    
      fclose(file);
  }
  else
  {
    printf("file doesn't exist\n");
  }
}

void ls_func(char* dirname)
{ 
    int i=0;
    struct dirent **dir;
    int numfiles = scandir(dirname, &dir, 0, alphasort);
    int j=0;
    if (numfiles >= 0)
    {
        
        for(i = 0; i < numfiles; i++ )
        {
            if((strcmp(dir[i]->d_name,".")!=0 && strcmp(dir[i]->d_name,"..")!=0) && dir[i]->d_name[0]!='.')            
            {

                struct dirent* name=dir[i];
                //char names[20]=dir[i]->d_name;
                if(name->d_type == DT_REG)          // regular file
                {
                    printf("%s\t\t", name->d_name);
                }
                else if(name->d_type == DT_CHR)    // a character device 
                {
                    printf("%s%s\t\t",CYAN, name->d_name);
                }
                else if(name->d_type == DT_FIFO)    // a named pipe 
                {
                    printf("%s%s\t\t",BOLDGREEN, name->d_name);
                }
                else if(name->d_type == DT_DIR)    // a directory
                {
                    printf("%s%s\t\t",BOLDBLUE, name->d_name);
                }
                else                              // unknown file types
                {
                    printf("%s%s\t\t",BOLDCYAN, name->d_name);
                }
                j++;
            }
            
            if(j!=0 && j%1==0) printf("\033[0m\n");
            //printf("\033[0m;")
            //printf("\n");
        }
        //printf("\n");
    }
    else
    {
        
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
    }
}