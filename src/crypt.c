#include "crypt.h"

//TODO: This function is only for compile test.
//      Remove this after implement cryptography.
//
void keygen() {
	RAND_status();
	RSA* private_key = RSA_generate_key(1024, 3, NULL, NULL);
}
