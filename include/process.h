#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "craftik.h"
#include "share.h"

int start_master(share*);
int start_worker(share*,int);
void run_master(share*);
void run_worker(share*,int);

#endif
