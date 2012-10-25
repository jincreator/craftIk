#ifndef _SHARE_H_
#define _SHARE_H_

#include "craftik.h"

typedef struct {
	int num_workers;
} properties;
typedef struct {
	int TODO;
} connections;
typedef struct {
	properties* prop;
	connections* conn;
} share;

#endif
