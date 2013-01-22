#ifndef _MASTER_PROCS_H_
#define _MASTER_PROCS_H_

#include <memory.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>

#include "craftik.h"
#include "share.h"

void make_serv_sock(share* shared);

#endif
