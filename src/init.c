#include "init.h"

share* init() {
	share* shared=(share*)malloc(sizeof(share));
	shared->prop=(properties*)malloc(sizeof(properties));
	shared->conn=(connections*)malloc(sizeof(connections));
	read_properties(shared);
	return shared;
}
