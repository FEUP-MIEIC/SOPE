#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(){
	int pid=fork();

	if(pid>0){
		int status;
		wait(&status);
		write(STDOUT_FILENO, "World!\n", 7);
	}else{
		write(STDOUT_FILENO, "Hello ", 6);
	}
}
