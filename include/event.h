#ifndef _EVENT_H_
#define _EVENT_H_

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/timeb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/epoll.h> // epoll
#include <netinet/in.h>

#include "craftik.h"

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
