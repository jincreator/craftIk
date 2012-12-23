#ifndef _MASTER_PROCS_H_
#define _MASTER_PROCS_H_

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "share.h"

void make_serv_sock(share* shared);


#endif
