#ifndef _PROC_LIB_H_
#define _PROC_LIB_H

#include <memory.h>

#include "share.h"

bool alive_tick_cool();
players* getThisPlayer();

int int2crft_str(char* buffer, int src, int buffer_size);
int ucs_str2crft_str(char* buffer, char* src, int buffer_size);
int ascii_str2crft_str(char* buffer, char* src, int buffer_size);
int ucs_str_length(const char* str, int arr_size);

#endif
