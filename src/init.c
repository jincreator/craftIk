#include "init.h"

share* init() {
	clock_t init_start=clock();
	printf(
		"[INFO] "
		"Starting craftIk version "VERSION"\n");

	share* shared=(share*)malloc(sizeof(share));

	RAND_status();
	shared->private_key = RSA_generate_key(1024, 3, NULL, NULL);

	shared->prop=(properties*)malloc(sizeof(properties));
	shared->conn=(connections*)malloc(sizeof(connections));
	read_setting(shared);


  puts("+------------------------------");
  puts("| Settings Result      ");
  puts("|                      ");
printf("| Server port : %d\n", shared->prop->port);
printf("| Server workers : %d\n", shared->prop->num_workers);
printf("| Connections per workers : %d\n", shared->prop->num_connections_per_worker);
  puts("+------------------------------");
  puts("");

	clock_t init_end=clock();
	printf("[INFO] Done (%.3fs)! For help, type \"help\" or \"?\"\n",
		((double)(init_end-init_start))/CLOCKS_PER_SEC);

	return shared;
}
