#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

// Server

int fifo_req, fifo_ans;


void destroyFifos(){
	close(fifo_req);
	unlink("/tmp/fifo_req");
	close(fifo_ans);
	unlink("/tmp/fifo_ans");
}

int main(){
	//create fifos.

	fifo_req = mkfifo("/tmp/fifo_req", 0666);
	fifo_ans = mkfifo("/tmp/fifo_ans", 0666);
	atexit(destroyFifos);
	getchar();
}
