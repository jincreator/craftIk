#include "master_procs.h"

void make_serv_sock(share* shared){
	struct sockaddr_in serv_addr;

	int opts;

	shared->listen_sock= socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family= AF_INET;
	serv_addr.sin_addr.s_addr= htonl(INADDR_ANY);
	serv_addr.sin_port= htons(shared->prop->port);

	opts= fcntl(shared->listen_sock, F_GETFL);
	if(opts< 0){
		perror("opts <0");
		exit(-1);
	}
	opts= (opts| O_NONBLOCK);
	if(fcntl(shared->listen_sock, F_SETFL, opts)< 0){
		perror("fcntl fail");
		exit(-1);
	}

	bind(shared->listen_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

	if(listen(shared->listen_sock, 5)== -1){
		perror("listen error\n");
		exit(-1);
	}
}
