#include<stdlib.h>
//Reference : https://support.sas.com/documentation/onlinedoc/sasc/doc/lr2/execlp.htm

#include<stdio.h>
#include <unistd.h>


int main(int argc,char* argv[]){
	pid_t pid;
	pid = fork();
	if ( pid == -1)
		perror("fork error");
	else if (pid == 0) {
		execlp("/usr/bin/gnome-terminal", "--disable-factory", "-e", "./modular_shell", NULL);
	}
	else {
		;
	}
}