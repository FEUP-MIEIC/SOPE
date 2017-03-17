#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

void cleaner(){
	write(STDOUT_FILENO, "\n", 1);
}

int main(){
	atexit(cleaner);
	char cmd[100];
	printf("minsh> ");
	int scanStatus;
	scanStatus=scanf("%s", cmd);
	while(strcmp(cmd, "quit")!=0 && scanStatus>0){
		if(fork()==0){ // Child

			execlp(cmd, cmd, NULL);
			printf("-----> Command not found!");
			exit(1);
		}else{ // Father
			int status;
			wait(&status);
			printf("\n-----> Command '%s' ended with errno: %d\n", cmd, WEXITSTATUS(status));
			printf("minsh> ");
			scanStatus=scanf("%s", cmd);
		}
	}
	exit(0);
}
