# include <stdio.h>
#include <dirent.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//#include "./cd.c"
//#include "./pwd.c"

#define CYAN "\x1b[96m"
#define GREEN "\x1b[92m"
#define BLUE "\x1b[94m"
#define BOLDCYAN    "\033[1m\033[36m" 
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDBLUE    "\033[1m\033[34m"  

/*

void nameFile(struct dirent* name,char* followup)
{
    if(name->d_type == DT_REG)          // regular file
    {
        printf("%s%s", name->d_name, followup);
    }
    else if(name->d_type == DT_DIR)    // a directory
    {
        printf("%s%s/%s",GREEN, name->d_name, followup);
    }
    else                              // unknown file types
    {
        printf("%s%s%s",CYAN, name->d_name, followup);
    }
}

*/

void ls_func(char* dirname)
{ 

    
    int i=0;
    struct dirent **dir;
    struct stat sb;
    int numfiles = scandir(dirname, &dir, 0, alphasort);
    int j=0;


    char pwdpath[1000];
    char pathofpresent[1000];
    pwd_func(pathofpresent,0);

    
    cd_func_for_ls(pwdpath,dirname);
    
    dirname=".";
    if (numfiles >= 0)
    {
        
        for(i = 0; i < numfiles; i++ )
        {
            if((strcmp(dir[i]->d_name,".")!=0 && strcmp(dir[i]->d_name,"..")!=0) && dir[i]->d_name[0]!='.')            
            {

                

                struct dirent* name=dir[i];
                //char names[20]=dir[i]->d_name;
                
                if(name->d_type == DT_DIR)    // a directory
                {
                    printf("%s%s\t\t",BOLDBLUE, name->d_name);
                }
                else if (stat(dir[i]->d_name, &sb) == 0 && sb.st_mode & S_IXUSR)
                {
                    printf("%s%s\t\t",BOLDGREEN, name->d_name);
                }
                // if (access(dir[i]->d_name, F_OK|X_OK) == 0)
                // {
                //     printf("inside executable\n");
                //     printf("%s%s\t\t",BOLDGREEN, name->d_name);
                // }
                else if(name->d_type == DT_REG)          // regular file
                {
                    printf("%s\t\t", name->d_name);
                }
                else if(name->d_type == DT_CHR)    // a character device 
                {
                    printf("%s%s\t\t",CYAN, name->d_name);
                }
                else if(name->d_type == DT_FIFO)    // a named pipe 
                {
                    printf("%s%s\t\t",GREEN, name->d_name);
                }
                else                              // unknown file types
                {
                    printf("%s%s\t\t",BOLDCYAN, name->d_name);
                }
                
                
                j++;
            }
            
            if(j!=0 && j%1==0) printf("\033[0m\n");
            //printf("\n");
        }
        //printf("\n");
    }
    else
    {
        perror("Error");

        perror("Error ");

    }
    cd_func_for_ls(pwdpath,pathofpresent);

}
void ls_func_present(char* dirname)
{ 
    
    int i=0;
    struct dirent **dir;
    struct stat sb;
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
                
                if(name->d_type == DT_DIR)    // a directory
                {
                    printf("%s%s\t\t",BOLDBLUE, name->d_name);
                }
                else if (stat(dir[i]->d_name, &sb) == 0 && sb.st_mode & S_IXUSR)
                {
                    printf("%s%s\t\t",BOLDGREEN, name->d_name);
                }
                else if(name->d_type == DT_REG)          // regular file
                {
                    printf("%s\t\t", name->d_name);
                }
                else if(name->d_type == DT_CHR)    // a character device 
                {
                    printf("%s%s\t\t",CYAN, name->d_name);
                }
                else if(name->d_type == DT_FIFO)    // a named pipe 
                {
                    printf("%s%s\t\t",GREEN, name->d_name);
                }
                else                              // unknown file types
                {
                    printf("%s%s\t\t",BOLDCYAN, name->d_name);
                }
                
                
                j++;
            }
            
            if(j!=0 && j%1==0) printf("\033[0m\n");
            //printf("\n");
        }
        //printf("\n");
    }
    else
    {

        perror("Error");
        perror("Error ");
    }

}

// void main(int argc, char* argv[])
// {

//     char* dirname = argv[1];
//     ls_func(dirname);
// }