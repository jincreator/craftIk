//
//  WatchFox.c
//  WatchFox
//
//  Created by Hyun Hwang on 7/14/12.
//  Copyright (c) 2012 SI Cyrusian. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define CRAFTIK_WATCHFOX_VERSION "1.0.0"


int main(int argc, const char **argv) {
	int WFExitCode=EXIT_SUCCESS;
	
	printf(
		"Running craftIk WatchFox(TM) %s.\nIn case the server daemon "
		"crashes or hangs, WatchFox(TM) will restart the process.\n\n",
		CRAFTIK_WATCHFOX_VERSION);
	
	char **WFExecArgs=(char **)malloc(sizeof(char *)*(argc+2));
	if(WFExecArgs==NULL) { // near impossible to happen.
		fprintf(stderr, "ERROR: Termination due to memory shortage.\n");
		abort();
	}
	
	WFExecArgs[0]=strstr(argv[0], "craftIk_run");
	if(WFExecArgs==NULL) { // this is ridiculous...
		fprintf(stderr, "ERROR: Something went wrong. Terminating.\n");
		free(WFExecArgs);
		abort();
	} else {
		size_t WFTemp=(size_t)(((uintptr_t)WFExecArgs[0])-((uintptr_t)argv[0]));
		
		WFExecArgs[0]=(char *)malloc(sizeof(char)*(WFTemp+8));
		if(WFExecArgs[0]==NULL) {
			fprintf(stderr, "ERROR: Termination due to memory "
					"shortage.\n");
			free(WFExecArgs);
			abort();
		}
		memset(WFExecArgs[0], '\0', sizeof(char)*(WFTemp+8));
		strncpy(stpcpy(WFExecArgs[0], argv[0]), "craftIk", 7);
	}
	WFExecArgs[1]="--fox-watching-u";
	for(int cidx=1; cidx<argc; ++cidx)
		WFExecArgs[cidx+1]=(char *)argv[cidx];
	WFExecArgs[argc+1]=NULL; // end of array indicator
	
	while(1) {
		pid_t WFChildProcessID=fork();
		
		if(WFChildProcessID==-1) { // fork() failed.
			fprintf(stderr, "ERROR: Termination due to sub-process "
					"creation failure.\n");
			free(WFExecArgs[0]);
			free(WFExecArgs);
			abort();
		} else if(WFChildProcessID==0) { // on child's side.
			/*
			 * Note: All malloc()ed memories will be automatically
			 * retrieved by OS upon calling exec*().
			 */
			execv(WFExecArgs[0], WFExecArgs);
			
			/*
			 * Note: Lines below will never be executed upon
			 * successful exec*() call.
			 */
			fprintf(stderr, "ERROR: Something went wrong upon "
					"executing server daemon. "
					"Terminating.\n");
			abort();
		} else { // on WatchFox(TM)'s side.
			/*
			 * TODO: to be reimplemented to use IPC heartbeat check
			 * with craftIk process.
			 */
			int tmp_WFChildExitCode=0;
			
			waitpid(WFChildProcessID, &tmp_WFChildExitCode, 0);
		}
		
		printf(
			"Server restart in 5 seconds. "
			"To stop, press ctrl+C now.\n");
		sleep(5);
	}
	free(WFExecArgs[0]);
	free(WFExecArgs);
	
	return WFExitCode;
}
