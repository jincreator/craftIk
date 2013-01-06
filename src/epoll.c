#include "event.h"

void craftIk_epoll_init( struct craftIk_epoll* epoll, int listenfd, int max_clients)
{
	struct epoll_event ev;
	
	epoll->listenfd = listenfd;
	epoll->max_clients = max_clients;
	epoll->events = (struct epoll_event*)malloc( sizeof(struct epoll_event) * max_clients );
	epoll->epfd = epoll_create(max_clients);
	if(!epoll->epfd){
		perror("epoll_create");
		exit(1);
	}
	
	ev.events = EPOLLIN | EPOLLHUP | EPOLLET;
	ev.data.fd = listenfd;
	if( epoll_ctl( epoll->epfd, EPOLL_CTL_ADD, listenfd, &ev) < 0 ){
		perror("epoll_ctl, adding listenfd");
		exit(1);
	}
}

void craftIk_epoll_add( struct craftIk_epoll* epoll, int clifd )
{
	struct epoll_event ev;
	
	nonblock(clifd);
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = clifd;
	if( epoll_ctl( epoll->epfd, EPOLL_CTL_ADD, clifd, &ev) < 0 ){
		perror("epoll_ctl ADD");
		exit(1);
	}	
}

void craftIk_epoll_del( struct craftIk_epoll* epoll, int clifd )
{
	if( epoll_ctl( epoll->epfd, EPOLL_CTL_DEL, clifd, NULL) < 0 ){
		perror("epoll_ctl DEL");
		exit(1);
	}	
}


int craftIk_epoll_getEvents( struct craftIk_epoll* epoll )
{
	return epoll_wait( epoll->epfd, epoll->events, epoll->max_clients, -1);
}


