#ifndef _SHARE_H_
#define _SHARE_H_

#include "craftik.h"

typedef struct {
	int num_workers;
	int num_connections_per_worker;
	int port;
} properties;
typedef struct {
	int TODO;
} connections;
typedef struct {
	properties* prop;
	connections* conn;
	int listen_sock;
} share;

#endif
