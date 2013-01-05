#include "setting.h"

#define LINELEN_MAX 2048
#define PROPLEN_MAX 1024
#define VALUELEN_MAX 1024

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
		"texture-pack=\n"
		"online-mode=true\n"
		"pvp=true\n"
		"difficulty=1\n"
		"gamemode=0\n"
		"max-players=20\n"
		"spawn-monsters=true\n"
		"generate-structures=true\n"
		"view-distance=10\n"
		"motd=A Minecraft Server for craftIk\n"
		"num-workers=3\n"
		"num-connections-per-worker=300\n");
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

void read_valuebool(bool* prop,const char* value) {
	if(strcmp(value,"true")==0) {
		*prop=true;
	} else if(strcmp(value,"false")==0) {
		*prop=false;
	} else {
		;//TODO:Show error message.
	}
}

void read_valuechar(char* prop,const char* value) {
	strcpy(prop,value);
	//TODO:Show error message.
}

void read_valueint(int* prop,const char* value) {
	char* endptr;
	*prop=(int)strtol(value,&endptr,10);
	//TODO:Show error message.
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
	char line[LINELEN_MAX];
	for(int linenum=0;
		fgets(line,sizeof(char)*LINELEN_MAX,server);
		linenum++) {
		int prop_start=0,prop_end,
			value_start,value_end=strlen(line);
		while(line[prop_start]==' '||line[prop_start]=='\t') {
			prop_start++;
		}
		if(line[prop_start]=='#') {
			continue;
		}
		prop_end=prop_start;
		while(line[prop_end]!=' '
			&&line[prop_end]!='\t'
			&&line[prop_end]!='=') {
			prop_end++;
		}
		value_start=prop_end;
		prop_end--;
		while( (line[value_start]==' '||line[value_start]=='\t')
			&&line[prop_end]!='=') {
			value_start++;
		}
		if(line[value_start]!='=') {
			printf("[WARNING] "
				"Problem parsing server.properties #%d:%d\n",
				linenum,value_start);
			printf("    %s\n",line);
			for(int i=0;i<value_start+3;i++) {
				printf(" ");
			}
			printf("^\n");
			printf("    "
				"Check \'=\' is at right place"
				" or no space at prop name.");
			continue;
		}
		value_start++;
		while(line[value_start]==' '||line[value_start]=='\t') {
			value_start++;
		}
		while((line[value_end]==' '||line[value_end]=='\t')
			&&line[value_end]!='\n') {
			value_end--;
		}
		//TODO:Show error message when no value.
		char prop[PROPLEN_MAX],value[VALUELEN_MAX];
		strncpy(prop,line+prop_start,
			(prop_end-prop_start+1)*sizeof(char));
		prop[prop_end-prop_start+1]='\0';
		strncpy(value,line+value_start,
			(value_end-value_start+1)*sizeof(char));
		value[value_end-value_start+1]='\0';

		if(strcmp("num-workers",prop)==0) {
			read_valueint(&shared->prop->num_workers, value);
			printf("[DEBUG] workers : [%d]\n", shared->prop->num_workers);

		}else if(strcmp("num-connections-per-worker", prop)==0){
			read_valueint(&shared->prop->num_connections_per_worker, value);
			printf("[DEBUG] connections per workers : [%d]\n", shared->prop->num_connections_per_worker);

		}else if(strcmp("server-port",prop)==0){
			read_valueint(&shared->prop->port, value);
			printf("[DEBUG] listen port : [%d]\n", shared->prop->port);

		}else{
			//TODO:Add more properties.
			//printf("prop=[%s],value=[%s]\n", prop,value);
		}

		memset(line, 0x00, LINELEN_MAX);
	}
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
