#include "setting.h"

FILE* generate_file(char* filename) {
	FILE* filepointer=fopen(filename,"w");
	if(filepointer==NULL) {
		char errorstring[64]="[Error] Can't make ";
		strcat(errorstring,filename);
		perror(errorstring);
		exit(1);
	}
	return filepointer;
}

FILE* read_file(char* filename) {
	FILE* filepointer=fopen(filename,"r");
	if(filepointer==NULL) {
		if(errno==ENOENT) {
			return NULL;
		}
		else {
			char errorstring[64]="[DEBUG] Can't read ";
			strcat(errorstring,filename);
			perror(errorstring);
			exit(1);
		}
	}
	return filepointer;
}

void generate_server() {
	printf("[INFO] Generating new properties file\n");
	FILE* server=generate_file("server.properties");
	time_t t=time(NULL);
	struct tm* datetime=localtime(&t);
	char datestring[64];
	fprintf(server,
		"#craftIk properties\n");
	strftime(datestring,64,"%a %b %d %H:%M:%S %Z %Y",datetime);
	fprintf(server,
		"#%s\n",datestring);
	fprintf(server,
		"generator-settings=\n"
		"allow-nether=true\n"
		"level-name=world\n"
		"enable-query=false\n"
		"allow-flight=false\n"
		"server-port=25565\n"
		"level-type=DEFAULT\n"
		"enable-rcon=false\n"
		"level-seed=\n"
		"server-ip=\n"
		"max-build-height=256\n"
		"spawn-npcs=true\n"
		"white-list=false\n"
		"spawn-animals=true\n"
		"snooper-enabled=true\n"
		"hardcore=false\n"
		"texture-pack="
		"online-mode=true\n"
		"pvp=true\n"
		"difficulty=1\n"
		"gamemode=0\n"
		"max-players=20\n"
		"spawn-monsters=true\n"
		"generate-structures=true\n"
		"view-distance=10\n"
		"motd=A Minecraft Server");
	fclose(server);
}

void generate_ops() {
	FILE* ops=generate_file("ops.txt");
	fclose(ops);
}

void generate_whitelist() {
	FILE* whitelist=generate_file("white-list.txt");
	fclose(whitelist);
}

void generate_bannedips() {
	FILE* bannedips=generate_file("banned-ips.txt");
	time_t t=time(NULL);
	struct tm* datetime=localtime(&t);
	char datestring[64];
	strftime(datestring,64,"%y. %m. %d %p %I:%M",datetime);
	fprintf(bannedips,
		"# Updated %s by craftIk "VERSION"\n",datestring);
	fprintf(bannedips,
		"# victim name | ban date | banned by | banned until | reason"
			"\n\n");
	fclose(bannedips);
}

void generate_bannedplayers() {
	FILE* bannedips=generate_file("banned-players.txt");
	time_t t=time(NULL);
	struct tm* datetime=localtime(&t);
	char datestring[64];
	strftime(datestring,64,"%y. %m. %d %p %I:%M",datetime);
	fprintf(bannedips,
		"# Updated %s by craftIk "VERSION"\n",datestring);
	fprintf(bannedips,
		"# victim name | ban date | banned by | banned until | reason"
		"\n\n"
	);
	fclose(bannedips);
}

void read_server(share* shared) {
	printf("[INFO] Loading properties\n");
	FILE* server=read_file("server.properties");
	if(server==NULL) {
		printf("[WARNING] server.properties does not exist\n");
		generate_server();
		server=read_file("server.properties");
		if(server==NULL) {
			perror("[ERROR] "
				"Problem generating server.properties");
			exit(1);
		}
	}
	shared->prop->num_workers=3;
}

void read_ops(share* shared) {
	FILE* ops=read_file("ops.txt");
	if(ops==NULL) {
		errno=ENOENT;
		perror("[WARNING] Failed to load operators list:\n");
		generate_ops();
		ops=read_file("ops.txt");
		if(ops==NULL) {
			perror("[ERROR] "
				"Problem generating ops.txt");
			exit(1);
		}
	}

}

void read_whitelist(share* shared) {
	FILE* whitelist=read_file("white-list.txt");
	if(whitelist==NULL) {
		errno=ENOENT;
		perror("[WARNING] Failed to load white-list:\n");
		generate_whitelist();
		whitelist=read_file("white-list.txt");
		if(whitelist==NULL) {
			perror("[ERROR] "
				"Problem generating white-list.txt");
			exit(1);
		}
	}
}

void read_bannedips(share* shared) {
	FILE* bannedips=read_file("banned-ips.txt");
	if(bannedips==NULL) {
#ifdef DEBUG
		perror("[DEBUG] banned-ips.txt does not exist");
#endif
		generate_bannedips();
		bannedips=read_file("banned-ips.txt");
		if(bannedips==NULL) {
			perror("[ERROR] "
				"Problem generating banned-ips.txt");
			exit(1);
		}
	}
}

void read_bannedplayers(share* shared) {
	FILE* bannedplayers=read_file("banned-players.txt");
	if(bannedplayers==NULL) {
#ifdef DEBUG
		perror("[DEBUG] banned-players.txt does not exist");
#endif
		generate_bannedplayers();
		bannedplayers=read_file("banned-players.txt");
		if(bannedplayers==NULL) {
			perror("[ERROR] "
				"Problem generating banned-players.txt");
			exit(1);
		}
	}
}

void read_setting(share* shared) {
	read_server(shared);
	read_ops(shared);
	read_whitelist(shared);
	read_bannedips(shared);
	read_bannedplayers(shared);
}
