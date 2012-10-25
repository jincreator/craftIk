#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "craftik.h"
#include "process.h"

int start_master(share* shared) {
	int num_workers=shared->prop->num_workers;
	pid_t pid,sid;
	pid=fork();
	if(pid<0) {
		perror("master fork() failed.\n");
		return -1;
	}
	if(pid>0) {
		return (int)pid;
	}
	run_master(shared);
	return 0;
}
void run_master(share* shared) {
	int num_workers=shared->prop->num_workers;
	pid_t *pid_worker=(pid_t *)malloc(sizeof(pid_t)*num_workers);
	for(int i=0;i<num_workers;i++) {
		pid_worker[i]=start_worker(shared);
	}
	while(1) {
		printf("Hello craftIk master!\n");
	}
}
int start_worker(share* shared){
	pid_t pid,sid;
	pid=fork();
	if(pid<0) {
		perror("worker fork() failed.\n");
		return -1;
	}
	if(pid>0) {
		return (int)pid;
	}
	run_worker(shared);
	return 0;
}
void run_worker(share* shared) {
	while(1) {
		printf("hello craftIk worker!\n");
	}
}
