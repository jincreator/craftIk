#include "process.h"

int start_master(share* shared) {
	int num_workers=shared->prop->num_workers;
	pid_t pid,sid;
	pid=fork();
	if(pid<0) {
		perror("master fork()");
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
	if(pid_worker==NULL) {
		perror("pid_worker malloc()");
	}
	int *sv_worker=(int *)malloc(sizeof(int)*num_workers);
	if(sv_worker==NULL) {
		perror("sv_worker malloc()");
	}
	for(int i=0;i<num_workers;i++) {
		int sv[2];
		if(socketpair(AF_UNIX,SOCK_STREAM,0,sv[2])!=0) {
			perror("master socketpair()");
		}
		pid_worker[i]=start_worker(shared,sv[1]);
		sv_worker[i]=dup(sv[0]);
		close(sv[0]);
		close(sv[1]);
	}
	while(1) {
		printf("Hello craftIk master!\n");
	}
}
int start_worker(share* shared,int sv){
	pid_t pid,sid;
	pid=fork();
	if(pid<0) {
		perror("worker fork()");
		return -1;
	}
	if(pid>0) {
		return (int)pid;
	}
	run_worker(shared,sv);
	return 0;
}
void run_worker(share* shared,int sv) {
	while(1) {
		printf("hello craftIk worker!\n");
	}
}
