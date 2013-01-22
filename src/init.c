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

#ifdef DEBUG
  puts("+--------------------------------+");
  puts("| Settings Result                |");
  puts("|                                |");
printf("| Server port : %5d            |\n", shared->prop->port);
printf("| Server workers : %2d            |\n", shared->prop->num_workers);
printf("| Connections per workers : %3d  |\n", shared->prop->num_connections_per_worker);
  puts("+--------------------------------+");
  puts("");
#endif

	clock_t init_end=clock();
	printf("[INFO] Done (%.3fs)! For help, type \"help\" or \"?\"\n",
		((double)(init_end-init_start))/CLOCKS_PER_SEC);

	return shared;
}
