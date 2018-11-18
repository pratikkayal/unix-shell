#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/sysinfo.h> //for system memory and uptime info

#include <ctype.h> //for isdigit()

#include <dirent.h> //for dealing with directories

// for username
#include <sys/types.h>
#include <pwd.h>



int check_number(char *str)
{
	int i;
	for(i=0; str[i] != '\0'; i++)
	{
		if (!isdigit(str[i]))
		{
			return 0;
		}
	}
	return 1;
}

unsigned long long get_total_mem()
{
	struct sysinfo sys_info;
	int return_val;
	return_val = sysinfo(&sys_info);
	unsigned long long TotalRAM = (sys_info.totalram*sys_info.mem_unit)/(1024);
	return TotalRAM;
}

long get_uptime()
{
	struct sysinfo sys_info;
	int return_val;
	return_val = sysinfo(&sys_info);
	long uptime = sys_info.uptime;
	return uptime;
}

char *getusername(char *uid_str)
{
	int uid = atoi(uid_str);
	struct passwd *etc_passwd = getpwuid(uid);
	if (etc_passwd)
	{
		return etc_passwd->pw_name;
	}
	return uid_str;
}


void ps_command()
{
	// printf("Hi from ps_command\n");

	DIR *procdir;	//to read and iterate through directory
	FILE *filep;
	struct dirent *proc_file;	// iterate through directory

	char path[1024], read_buffer[1024], uid_integer_str[10];
	
	// for getline function calls
	char *line;
	size_t len = 0;

	unsigned long long total_memory = get_total_mem();

	long Hertz=sysconf(_SC_CLK_TCK);
	long uptime = get_uptime();


	procdir = opendir("/proc");
	if (procdir==NULL)
	{
		perror("Failed to open /proc directory");
		exit(0);
	}

	// print header line
	printf("username pid cpu_usage memory_usage vmsize vmrss state\tname\n");


	while((proc_file = readdir(procdir)) != NULL)
	{
		char *file_name = proc_file->d_name;
		if(check_number(file_name))
		{
			// get info from /proc/<pid>/stat
			strcpy(path, "/proc/");
			strcat(path, file_name);
			strcat(path, "/stat");

			// printf("%s\n", path);

			filep = fopen(path,"r");

			char comm[20],state;
			unsigned int flags;
			int pid,ppid,pgrp,session,tty_nr,tpgid;
			unsigned long minflt,cminflt,majflt,cmajflt,utime,stime;
			unsigned long long starttime;
			long cutime,cstime,priority,nice,num_threads,itreavalue;
			unsigned long total_time;
			float seconds;
			float cpu_usage;

			if (filep!=NULL)
			{
				getline(&line,&len,filep);
				sscanf(line,"%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld  %ld %llu",&pid,comm,&state,&ppid,&pgrp,&session,&tty_nr,&tpgid,&flags,&minflt,&cminflt,&majflt,&cmajflt,&utime,&stime,&cutime,&cstime,&priority,&nice,&num_threads,&itreavalue,&starttime);
				total_time=utime+stime;
				total_time=total_time+(unsigned long)cutime+(unsigned long)cstime;
				seconds=uptime-(starttime/Hertz);
				cpu_usage=100*((total_time/Hertz)/seconds);
			}
			else
				continue;

			// get user id(uid) and memory usage info from /proc/<pid>/status
			strcpy(path, "/proc/");
			strcat(path, file_name);
			strcat(path, "/status");

			// printf("%s\n", path);

			unsigned long long vmsize=0;
			unsigned long long vmrss=0;

			filep = fopen(path,"r");
			if (filep!=NULL)
			{
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				sscanf(line,"Uid:    %s ",uid_integer_str);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				sscanf(line,"VmSize:    %llu kB",&vmsize);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				getline(&line,&len,filep);
				sscanf(line,"VmRSS:     %llu kB",&vmrss);
			}
			else
				continue;
			fclose(filep);

			float memory_usage = (vmrss/total_memory)*100;

			// get username from uid
			char *username = getusername(uid_integer_str);

			// print output
			printf("%5s %5s %5.1f\t %5.1f\t %5llu %5llu %5c\t%5s\n",username,proc_file->d_name,cpu_usage,memory_usage,vmsize,vmrss,state,comm);

		}
	}

}


void ps_command_pid(char* var)
{
	// printf("Hi from ps_command_pid\n");

	char* pid = var;
	// printf("%s\n", pid);
	
	char* val[20];
	int count = 0;
	while((val[count] = strsep(&pid, ",")) != NULL  && count < 19)    //strsep(char **stringp, const char *delim);
    {
    	// printf("%s\n", val[count]);
 		count++;
    }

	int count_p = 0;
	char* pid_temp;
	DIR *procdir;	//to read and iterate through directory
	FILE *filep;
	struct dirent *proc_file;	// iterate through directory

	char path[1024], read_buffer[1024], uid_integer_str[10];
	
	// for getline function calls
	char *line;
	size_t len = 0;

	unsigned long long total_memory = get_total_mem();

	long Hertz=sysconf(_SC_CLK_TCK);
	long uptime = get_uptime();


	// print header line
	printf("username pid cpu_usage memory_usage vmsize vmrss state\tname\n");

	for(int pid_c = 0; pid_c < count; pid_c++)
	{
		pid_temp = val[pid_c];
		// printf("%s\n", pid_temp);
		
		procdir = opendir("/proc");
		if (procdir==NULL)
		{
			perror("Failed to open /proc directory");
			exit(0);
		}

		while((proc_file = readdir(procdir)) != NULL)
		{
			char *file_name = proc_file->d_name;

			// printf("names inside ps pid %s %s\n", file_name, pid);
			
			if(check_number(file_name) && strcmp(pid_temp, file_name)==0)
			{
				count_p ++;
				// get info from /proc/<pid>/stat
				strcpy(path, "/proc/");
				strcat(path, file_name);
				strcat(path, "/stat");

				// printf("%s\n", path);

				filep = fopen(path,"r");

				char comm[20],state;
				unsigned int flags;
				int pid,ppid,pgrp,session,tty_nr,tpgid;
				unsigned long minflt,cminflt,majflt,cmajflt,utime,stime;
				unsigned long long starttime;
				long cutime,cstime,priority,nice,num_threads,itreavalue;
				unsigned long total_time;
				float seconds;
				float cpu_usage;

				if (filep!=NULL)
				{
					getline(&line,&len,filep);
					sscanf(line,"%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld  %ld %llu",&pid,comm,&state,&ppid,&pgrp,&session,&tty_nr,&tpgid,&flags,&minflt,&cminflt,&majflt,&cmajflt,&utime,&stime,&cutime,&cstime,&priority,&nice,&num_threads,&itreavalue,&starttime);
					total_time=utime+stime;
					total_time=total_time+(unsigned long)cutime+(unsigned long)cstime;
					seconds=uptime-(starttime/Hertz);
					cpu_usage=100*((total_time/Hertz)/seconds);
				}
				else
					continue;

				// get user id(uid) and memory usage info from /proc/<pid>/status
				strcpy(path, "/proc/");
				strcat(path, file_name);
				strcat(path, "/status");

				// printf("%s\n", path);

				unsigned long long vmsize=0;
				unsigned long long vmrss=0;

				filep = fopen(path,"r");
				if (filep!=NULL)
				{
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					sscanf(line,"Uid:    %s ",uid_integer_str);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					sscanf(line,"VmSize:    %llu kB",&vmsize);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					getline(&line,&len,filep);
					sscanf(line,"VmRSS:     %llu kB",&vmrss);
				}
				else
					continue;
				fclose(filep);

				float memory_usage = (vmrss/total_memory)*100;

				// get username from uid
				char *username = getusername(uid_integer_str);

				// print output
				printf("%5s %5s %5.1f\t %5.1f\t %5llu %5llu %5c\t%5s\n",username,proc_file->d_name,cpu_usage,memory_usage,vmsize,vmrss,state,comm);
			}
		}
	}
	if (count_p==0)
	{
		printf("No process with given pid found running/invalid pid\n");
	}
}

// void main()
// {
// 	ps_command();
// }