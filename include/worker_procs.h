#ifndef _WORKER_PROCS_H_
#define _WORKER_PROCS_H_
#include "event.h"
#include "event_procs.h"

void add_clnt(share* shared, craftIk_epoll* clnt_epoll);

void clnt_event_procs(share* shared, craftIk_epoll* clnt_epoll, int clnt_num);

players* getThisPlayer();//TODO

#endif
