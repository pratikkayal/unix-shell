#include <stdio.h> 
#include <dirent.h> 
#include <string.h>
  
void rm_dir(char direc[10000]) 
{ 
    
    struct dirent *de;  // Pointer for directory entry 
    DIR *dr = opendir(direc); 


    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
         int rm = remove(direc);
    } 
    else{
        char dir_copy[10000];
        strcpy(dir_copy, direc);

        while ((de = readdir(dr)) != NULL) 

            if (strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..")!=0){

                strcpy(direc,dir_copy);
                strcat(direc, "/");
                strcat(direc, de->d_name);

                int rm_n = remove(direc);

                if (rm_n != 0){
                    strcat(direc, "/");
                    rm_dir(direc);
                }
                int rim = remove(dir_copy);
            }
                
        closedir(dr);     
   }
} 

// int main(int argc, char const *argv[])
// {
//     char file[10000];
//     strcat(file, "test");

//     rm_dir(file);
//     return 0;
// }