#include <stdio.h>

#include "craftik.h"
#include "init.h"
#include "process.h"

int main(int argc, const char **argv) {
	share* shared=init();
	if(shared==NULL) {
		perror("Could not initialized craftIk.\n");
		return 1;
	}
	start_master(shared);
	printf("hello craftik\n");
	return 0;
}
