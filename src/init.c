#include "init.h"

share* init() {
	clock_t init_start=clock();
	printf(
		"[INFO] "
		"Starting craftIk version "VERSION"\n");
	share* shared=(share*)malloc(sizeof(share));
	shared->prop=(properties*)malloc(sizeof(properties));
	shared->conn=(connections*)malloc(sizeof(connections));
	read_setting(shared);
	clock_t init_end=clock();
	printf("[INFO] Done (%.3fs)! For help, type \"help\" or \"?\"\n",
		((double)(init_end-init_start))/CLOCKS_PER_SEC);
	return shared;
}
