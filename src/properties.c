#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "craftik.h"
#include "properties.h"

int read_properties(share* shared) {
	shared->prop->num_workers=3;
	return 0;
}
