#include<stdio.h>

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


void main(int argc,char*argv[])
{

	char* filename = argv[1];
	cat_func(filename);

}