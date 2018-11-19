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
    	printf("\n");
    	fclose(file);
    	if(count==0)
    	{
    		perror("Error");
    	}
	}
	else
	{
		perror("Error");
	}
}


// void main(int argc,char*argv[])
// {

// 	char* filename = argv[1];
// 	cat_func(filename);

// }