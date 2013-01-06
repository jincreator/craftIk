#ifndef _EVENT_PROCS_H_
#define _EVENT_PROCS_H_

#include <math.h>

#include "share.h"
#include "event.h"
#include "proc_lib.h"

void proc_0xFE(share* shared, craftIk_epoll* clnt_epoll, int clnt_num);
void proc_0xFF(share* shared, craftIk_epoll* clnt_epoll, int clnt_num);
void proc_0x00(share* shared, craftIk_epoll* clnt_epoll, int clnt_num);
void proc_0x02(share* shared, craftIk_epoll* clnt_epoll, int clnt_num);
void proc_0x0A(share* shared, craftIk_epoll* clnt_epoll, int clnt_num);
void proc_0x0B(share* shared, craftIk_epoll* clnt_epoll, int clnt_num);


#endif
