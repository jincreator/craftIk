#include "packet.h"


#include <openssl/rsa.h>
#include <openssl/rand.h>


void proc_0xFE(share* shared, craftIk_epoll* clnt_epoll, int clnt_num){
	char message[1];
	recv(clnt_epoll->events[clnt_num].data.fd, message, (size_t)sizeof(message), 0);
	proc_0xFF(shared, clnt_epoll, clnt_num);
}
void proc_0xFF(share* shared, craftIk_epoll* clnt_epoll, int clnt_num){
	const char* motd= shared->prop->motd;
	int motd_length= ucs_str_length(motd, 1024);
	const char* serv_ver= shared->prop->server_version;
	int ver_length= ucs_str_length(serv_ver, 64);
	int proto_ver= shared->prop->protocol_version;
	int proto_ver_len= 0;
	int cur_player= shared-> player_count;
	int cur_player_len= 0 ;
	int max_player= shared->prop->max_players;
	int max_player_len= 0;

	int temp;

	char message[1024];

	short cur_length=0;

	memset(message, 0, sizeof(message));
	
	temp= proto_ver;
	while(temp>0|| proto_ver_len== 0){
		proto_ver_len++;
		temp/= 10;
	}
	temp= cur_player;
	while(temp>0|| cur_player_len== 0){
		cur_player_len++;
		temp/= 10;
	}
	temp= max_player;
	while(temp>0|| max_player_len== 0){
		max_player_len++;
		temp/= 10;
	}

	message[0]= 0xff;
	cur_length+= 1;// length of 0xff
	cur_length+= 2;// length of length of string
	message[4]= 0xa7;
	message[6]= 0x31;
	cur_length+= 4; // length of §1
	cur_length+= 2; // length of server_version delimeter
	for(int i=0; i< proto_ver_len; i++){
		message[cur_length+2*(proto_ver_len-i)-1]
			=proto_ver% 10+ '0';
		proto_ver/= 10;
	}

	cur_length+= proto_ver_len* 2;// length of protocol version
	
	cur_length+= 2;// length of server version delilmeter

	for(int i=0; i<ver_length; i++){
		message[cur_length+i]= serv_ver[i];
	}
	cur_length+= ver_length* 2;// length of server version

	cur_length+= 2;//length of motd delimeter

	for(int i=0; i<motd_length; i++){
		message[cur_length+i]= motd[i];
	}
	cur_length+= motd_length* 2;// length of motd

	cur_length+= 2;//length of cur player count delimeter


	for(int i=0; i< cur_player_len; i++){
		message[cur_length+2*(cur_player_len-i)-1]
			=cur_player% 10+ '0';
		cur_player/= 10;
	}

	cur_length+= cur_player_len* 2;// length of cur player count

	for(int i=0; i< max_player_len; i++){
		message[cur_length+2*(max_player_len-i)-1]
			=max_player% 10+ '0';
		max_player/= 10;
	}

	cur_length+= max_player_len* 2;// length of max player

	cur_length-=3;
	memcpy(message+1, &cur_length, sizeof(short));
	send(clnt_epoll->events[clnt_num].data.fd, message, cur_length+3, 0);
}

void proc_0x0A(share* shared, craftIk_epoll* clnt_epoll, int clnt_num){
	char message[1];
	recv(clnt_epoll->events[clnt_num].data.fd, message, (size_t)sizeof(message), 0);
	players* thisPlayer= getThisPlayer();
	memcpy(&(thisPlayer->on_ground), message, sizeof(thisPlayer->on_ground));
	if(alive_tick_cool()== true){//TODO: alive_tick_cool
		proc_0x00(shared, clnt_epoll, clnt_num);
	}
}

void proc_0x0B(share* shared, craftIk_epoll* clnt_epoll, int clnt_num){

	char message[33];
	recv(clnt_epoll->events[clnt_num].data.fd, message, (size_t)sizeof(message), 0);
	players* thisPlayer= getThisPlayer();//TODO: make get this player
	memcpy(&(thisPlayer->abs_x_pos), message, sizeof(thisPlayer->abs_x_pos));
	memcpy(&(thisPlayer->abs_y_pos), message+ 8, sizeof(thisPlayer->abs_y_pos));
	memcpy(&(thisPlayer->stance), message+ 16, sizeof(thisPlayer->stance));
	memcpy(&(thisPlayer->abs_z_pos), message+ 24, sizeof(thisPlayer->abs_z_pos));
	memcpy(&(thisPlayer->on_ground), message+ 32, sizeof(thisPlayer->on_ground));

}

void proc_0x00(share* shared, craftIk_epoll* clnt_epoll, int clnt_num){//TODO
}
