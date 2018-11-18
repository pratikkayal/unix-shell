#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

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
        perror("Error : getcwd() not working \n");
    }

}

// void main(int argc, char* argv[])
// {
//     char* pwdpath=argv[1];
//     pwd_func(pwdpath,1);
// }