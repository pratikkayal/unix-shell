#include<stdio.h>

void cat_func(char* filename)
{	

	FILE * file;
	char c;
	int count=0;
	file = fopen( filename , "r");
	if (file) 
	{
    	while((c=fgetc(file))!=EOF)
    	{
        	printf("%c",c);
        	count++;
    	}
    
    	fclose(file);
    	if(count==0)
    	{
    		perror("File is empty\n");
    	}
	}
	else
	{
		perror("No such file \n");
	}
}


// void main(int argc,char*argv[])
// {

// 	char* filename = argv[1];
// 	cat_func(filename);

// }