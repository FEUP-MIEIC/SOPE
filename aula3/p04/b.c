#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(){
	int pid=fork();

	if(pid>0){ // I'm the parent!
	//sleep(1);
		write(STDOUT_FILENO, "Hello ", 6);
	}else{ // I got the 0, I'm the child.
		int myparent=getppid();

		while(myparent==getppid()){
			usleep(10);
		}
		write(STDOUT_FILENO, "World!\n", 7);
	}
}
