
#ifndef __EVENT_H__
#define __EVENT_H__


#include <stdio.h>
#include <sys/timeb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/epoll.h> // epoll
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#include <stdlib.h>
#include <unistd.h>


// create nonblock socket
void nonblock(int sockfd);



// epoll
typedef struct craftIk_epoll
{
	int max_clients;
	int listenfd;
	int epfd;
	struct epoll_event* events;
} craftIk_epoll;


void craftIk_epoll_init( struct craftIk_epoll* epoll, int listenfd, int max_clients );
void craftIk_epoll_add( struct craftIk_epoll* epoll, int clifd );
void craftIk_epoll_del( struct craftIk_epoll* epoll, int clifd );
int craftIk_epoll_getEvents( struct craftIk_epoll* epoll);


#endif
