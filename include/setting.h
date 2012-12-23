#ifndef _SETTING_H_
#define _SETTING_H_

#include <stdio.h>
#include <time.h>
#include <string.h>

#include "craftik.h"
#include "share.h"

FILE* generate_file(char* filename);
FILE* read_file(char* filename);

void generate_server();
void generate_ops();
void generate_whitelist();
void generate_bannedips();
void generate_bannedplayers();

void read_server(share* shared);
void read_ops(share* shared);
void read_whitelist(share* shared);
void read_bannedips(share* shared);
void read_bannedplayers(share* shared);

void read_setting(share* shared);
void read_valuebool(bool* prop,const char* value);
void read_valuechar(char* prop,const char* value);
void read_valueint(int* prop,const char* value);

#endif
