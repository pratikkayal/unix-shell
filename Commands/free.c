#include<stdio.h>
#include<stdlib.h>

// for free function. can allso be done using /proc/meminfo
#include <sys/sysinfo.h>

void free_command()
{
	struct sysinfo sys_info;
	int return_val;

	return_val = sysinfo(&sys_info);



	unsigned long TotalRAM = (sys_info.totalram*sys_info.mem_unit)/(1024);
	unsigned long FreeRAM = (sys_info.freeram*sys_info.mem_unit)/(1024);
	unsigned long UsedRAM = TotalRAM-FreeRAM;
	unsigned long SharedRAM = (sys_info.sharedram*sys_info.mem_unit)/(1024);	
	unsigned long BufferRAM = (sys_info.bufferram*sys_info.mem_unit)/(1024);
	unsigned long TotalSwapRAM = (sys_info.totalswap*sys_info.mem_unit)/(1024);
	unsigned long FreeSwapRAM = (sys_info.freeswap*sys_info.mem_unit)/(1024);
	unsigned long NumberofProcesses = sys_info.procs;

	printf("\t total \t\t used \t\t free \t\t shared \t buff/cache\n");
	printf("Mem:\t %-10ld \t %-10ld \t %-10ld \t %-10ld \t %-10ld \n",TotalRAM, UsedRAM, FreeRAM, SharedRAM, BufferRAM);
	printf("Swap:\t %-10ld \t %-10ld \t %-10ld \n", TotalSwapRAM, TotalSwapRAM-FreeSwapRAM, FreeSwapRAM);

	// printf("Total RAM: %ld\n",(sys_info.totalram*sys_info.mem_unit)/(1024));
	// printf("Free RAM: %ld\n",(sys_info.freeram*sys_info.mem_unit)/(1024));
	// printf("Shared RAM: %ld\n",(sys_info.sharedram*sys_info.mem_unit)/(1024));	
	// printf("Buffer RAM: %ld\n",(sys_info.bufferram*sys_info.mem_unit)/(1024));
	// printf("Total Swap RAM: %ld\n",(sys_info.totalswap*sys_info.mem_unit)/(1024));
	// printf("Free Swap RAM: %ld\n",(sys_info.freeswap*sys_info.mem_unit)/(1024));
	// printf("Number of Processes: %d\n",sys_info.procs );
}

// void main()
// {
// 	free_command();
// }