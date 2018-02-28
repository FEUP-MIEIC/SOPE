/**
 * @file a.c
 * @Daniel Silva
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10240

int min(int a, int b){
	if(a<b)
		return a;
	return b;
	
}


int main(int argc, char* argv[]){

	if(argc!=3){
		write(STDOUT_FILENO, "Utilização: ./a.out source dest\n", 34);
		return 1;
	}
	
	char buffer[BUFFER_SIZE];
	FILE* src;
	FILE* dst;
	int status, lSize;
	
	src=fopen(argv[1], "r");
	if(src==NULL){
		printf("There was an error opening the file %s for reading!\n", argv[1]);
		exit(1);
	}
	
	dst=fopen(argv[2], "w");
	if(dst==NULL){
		printf("There was an error opening the file %s for writing!\n", argv[2]);
		exit(1);
	}

	// obtain file size:
	fseek (src , 0 , SEEK_END);	
	lSize = ftell (src);
	rewind (src);
	
	if(lSize>BUFFER_SIZE){
		printf("Source file is bigger than the available buffer! However, there are loops!\n");
	}
	int i=1;
	
	while((status=fread(buffer, 1, min(lSize, BUFFER_SIZE), src))){
		//printf("Passagem %d: %d\n", i, status);
		fwrite(buffer, status, 1, dst);
		lSize-=status;
		i++;
		//sleep(1);
	}
	
	fclose(dst);
	fclose(src);
	return 0;
}
