#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "craftik.h"
#include "share.h"
#include "properties.h"
#include "process.h"

int main(int argc, const char **argv) {
	share* shared=(share*)malloc(sizeof(share));
	shared->prop=(properties*)malloc(sizeof(properties));
	shared->conn=(connections*)malloc(sizeof(connections));
	read_properties(shared);
	start_master(shared);
	printf("hello craftik\n");
	return 0;
}
