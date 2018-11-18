#include <stdio.h>
#include <stdlib.h>

void cp_command(char* source, char* target);

void cp_command(char* source, char* target)
{
	FILE *file1, *file2;
	
	file1 = fopen(source, "rb");
	// open the source file and check whether it exists
	if (file1 == NULL)
	{
		perror("Error" );
	}
	else
	{	
		file2 = fopen(target, "wb"); // open the target file to write to it
		if (file2 == NULL)
		{
			perror("Error" );
		}
		else
		{
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

// 	// cp_command(source, target);
// }