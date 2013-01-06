#include "session.h"

void craftIk_session_init()
{
	sessions=NULL;
	RBT_InitNil();
	RBT_InsertNode( &sessions, RBT_CreateNode(0, NULL) );

#ifdef DEBUG
	fprintf(stderr, "[DEBUG] craftIk session manager initialized\n");
#endif

}

void craftIk_session_add( int sockfd )
{
	int key;
	craftIk_session* newsession;

	key = sockfd;
	newsession = malloc(sizeof(craftIk_session));

	RBT_InsertNode( &sessions, RBT_CreateNode(key,newsession) ); 

#ifdef DEBUG
	fprintf(stderr,"[DEBUG] craftIk session added : fd(%d)\n", sockfd);
#endif

}

void craftIk_session_del( int sockfd )
{
	RBTNode* toremove = RBT_RemoveNode( &sessions, sockfd );

	if( toremove == NULL ){
#ifdef DEBUG
		fprintf(stderr,"[DEBUG] no node found to delete : fd(%d)\n", sockfd);
#endif
	} else {
		RBT_DestroyNode( toremove );
#ifdef DEBUG
		fprintf(stderr,"[DEBUG] craftIk session deleted : fd(%d)\n", sockfd);
#endif
	}
		
}

craftIk_session* craftIk_session_get( int sockfd )
{
	RBTNode* nodeget = RBT_SearchNode( sessions, sockfd );

	if( nodeget == NULL ){
#ifdef DEBUG
		fprintf(stderr,"[DEBUG] no node found to get : fd(%d)\n", sockfd );
#endif
		return NULL;
	} else {
		return nodeget;
	}

}


