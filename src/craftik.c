#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "craftik.h"

int main(int argc, const char **argv) {
	int worker_num=3;
	pid_t *worker=(pid_t *)malloc(sizeof(pid_t)*worker_num);
	for(int i=0;i<worker_num;i++) {
		pid_t pid=fork();
		if(pid==0)
			break;
		else if(pid==-1)
			perror("fork() failed.\n");
		else
			worker[i]=pid;
	}
	printf("hello craftik\n");
	return 0;
}
