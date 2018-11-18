#include <stdio.h>
#include <stdlib.h>


// Add feature to recursively delete files inside a Directory

void rm_command(char* path)
{
	int returnval;
	// Delete the file at path
	returnval = remove(path);

	if( returnval != 0)
	{
		printf("Error: Unable to delete");
	}  
}


// main function to test

// void main()
// {
// 	// char source[50];

// 	// printf("Enter name of file to delete\n");
// 	// gets(source);

// 	// rm_command(source);
// }