#ifndef _SESSION_H_
#define _SESSION_H_

#include "craftik.h"
#include "rbtree.h"

typedef struct craftIk_session
{
	int sockfd;
	int EID;
	int AESon;
	char username[128];

	char* shared_secret;

} craftIk_session;

RBTNode* sessions;

void craftIk_session_init();
void craftIk_session_add( int sockfd );
void craftIk_session_del( int sockfd );

craftIk_session* craftIk_session_get( int sockfd );

#endif
