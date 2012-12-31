#include "worker_procs.h"

void add_clnt(share* shared, craftIk_epoll* clnt_epoll){
	struct sockaddr_in clnt_addr;
	int clnt_addr_size= sizeof(clnt_addr);
	int clnt_sock= accept(clnt_epoll->listenfd, (struct sockaddr*)&clnt_addr, (socklen_t*)&clnt_addr_size);

	if(clnt_sock>0){
		craftIk_epoll_add(clnt_epoll, clnt_sock);
	}
}

void clnt_event_procs(share* shared, craftIk_epoll* clnt_epoll, int clnt_num){
	unsigned char proto_type;

	int res= recv(clnt_epoll->events[clnt_num].data.fd, &proto_type, (size_t)sizeof(proto_type), 0);
	
	if(res== 0){
		craftIk_epoll_del(clnt_epoll, clnt_epoll->events[clnt_num].data.fd);
	} else if(res< 0){
		craftIk_epoll_del(clnt_epoll, clnt_epoll->events[clnt_num].data.fd);
	} else{
		if((int)proto_type == 0xFE){
			proc_0xFE(shared, clnt_epoll, clnt_num);
		}
		if((int)proto_type == 0x0B){
			proc_0x0B(shared, clnt_epoll, clnt_num);
		}
		if((int)proto_type == 0x0A){
			proc_0x0A(shared, clnt_epoll, clnt_num);
		}
	}
}
