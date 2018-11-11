#include<stdio.h>
#include<stdlib.h>

void lscpu_command()
{
	FILE *file;
	
	file = fopen("/proc/cpuinfo", "r");
	//read line by line
	const size_t line_size = 300;
	char* line = malloc(line_size);
	while (fgets(line, line_size, file) != NULL)
	{
	    printf("%s\n",line);
	}
	free(line); 
	fclose(file);
}

// void main()
// {
// 	lscpu_command();
// 	// ifconfig_command();
// }