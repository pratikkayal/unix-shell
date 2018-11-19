#include <stdio.h>
#include<unistd.h>
#include <string.h>



// void pwd_func(char* pwdpath,int printornot) // if printornot=1 --> print 
// {
//     char temp[1000];
//     char* path=getcwd(temp, sizeof(temp));
//     if(path != NULL)
//     {
//         strcpy(pwdpath,temp);
//         if(printornot==1)  
//         {
//             printf("%s\n",pwdpath);
//         }
//     }
//     else 
//     {

//     }

// }


void cd_func(char* pwdpath,char* path)
{
    int value = chdir(path);
    //printf("cd done\n");
    if(value==0) 
    {
        pwd_func(pwdpath,0);
    }
    else 
    {
        perror("Error");
    }
    
}
void cd_func_for_ls(char* pwdpath,char* path)
{
    int value = chdir(path);
    //printf("cd done\n");
    if(value==0) 
    {
        pwd_func(pwdpath,0);
    }
    else 
    {
        //perror("Error : incorrect path \n");
    }
    
}


// void main(int argc, char* argv[])
// {
// 	char* path = argv[1];
//     char pwdpath[1000];
// 	cd_func(pwdpath,path);

// }
