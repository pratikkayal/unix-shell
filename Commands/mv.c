// Code by Soham

#include <stdio.h>
#include <stdlib.h>


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


// main function to test

// void main()
// {
// 	// char source[50], target[50];

// 	// printf("Enter name of file to copy\n");
// 	// gets(source);

// 	// printf("Enter name of target file\n");
// 	// gets(target);

// 	// mv_command(source, target);
// }