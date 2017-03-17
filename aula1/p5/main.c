#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[], char* envp[]){
	char username[256];
	int i=0;
	while(envp[i]!=NULL){
		if(strstr(envp[i],"USER=") && envp[i][4]=='='){
			char* a=strchr(envp[i], '=');
			strcpy(username, (a+(sizeof(char))));
			break;
		}
		i++;
	}

	printf("Hello, %s!\n", username);
}
