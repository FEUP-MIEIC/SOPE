#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(){
	int pid=fork();

	if(pid>0){ // I'm the parent. My parent is the bash.
		int status;
		wait(&status);
		write(STDOUT_FILENO, "friends!\n", 9);
	}else{ // I'm the child!
		int cpid=fork();
		if(cpid>0){ // YAY, I get to be a parent now!
			int status;
			wait(&status);
			write(STDOUT_FILENO, "my ", 3);
		}else{ //I'm the last child, who should run first. I will never be a parent.
			write(STDOUT_FILENO, "Hello ", 6);
		}
	}
}
