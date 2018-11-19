#include<stdio.h>
#include<sys/utsname.h>
#include<utmp.h>
#include<time.h>

#include <sys/stat.h>
 

int w_func()
{
 struct utmp *n;
  // struct utmp *t;
 FILE *fp;
 n = getutent();
 struct tm  ts;
 char   buf[80];
 char* string;

 char buffer[32];
 int c = 0;


 printf("%s       %s    %s    %s\n","USER", "TTY", "FROM", "LOGIN");
 while(n) {
 	if (n->ut_type == 7){
 		// int time_n = time_(n->ut_time);
 		c++;
 		// t = getutid(&n);
 		
 		snprintf(buffer, sizeof(char) * 32, "/proc/%d/cmdline", n->ut_pid);

 		// fp = fopen(buffer, "rb");
 		// fscanf(fp, "%s", string);

 		strftime(buf, sizeof(buf), "%a", &n->ut_time);
   		printf("%s   %s    %s       %s\n", n->ut_name, n->ut_line, n->ut_host, buf);//, string);
   }
   n=getutent();
 }

 printf("\nNumber of User - %d\n",c);
 return 0;
}


