#include "server_connection.h"

Server_connection::Server_connection(){
	if (SDLNet_Init() < 0)
	{
		std::string error(SDLNet_GetError());
		throw std::runtime_error("Couldn't initialize SDL_net" + error);
	}

	if (SDLNet_ResolveHost(&ip, connectionstring, port) < 0)
	{
		std::string error(SDLNet_GetError());
		throw std::runtime_error("Couldn't resolvehost: " + error);
	}

	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		std::string error(SDLNet_GetError());
		throw std::runtime_error("Couldn't open TCP sock: " + error);
	}
	set = SDLNet_AllocSocketSet(1);
	if (!set) {
		std::string error(SDLNet_GetError());
		throw std::runtime_error("Couldn't alloc socket set: " + error);
	}
	if (SDLNet_TCP_AddSocket(set, sd) == -1)
	{
		std::string error(SDLNet_GetError());
		throw std::runtime_error("Couldn't add TCP sock to set: " + error);
	}
}

void Server_connection::send_code(int number){
	int code = number;
	int length = sizeof(code);
	if (SDLNet_TCP_Send(sd, (void *)&code, length) < length)
	{
		std::string error(SDLNet_GetError());
		throw std::runtime_error("Couldn't request server: " + error);
	}
}

void Server_connection::new_game(int *map){
	send_code(NEW_GAME);
	if (SDLNet_TCP_Recv(sd, (void *)map, 27 * 21 * sizeof(int)) <= 0){
		std::string error(SDLNet_GetError());
		throw std::runtime_error("Couldn't receive map: " + error);
	}
}

void Server_connection::ready(){
	send_code(READY);
}

void Server_connection::going_top(){
	send_code(GOINGTOP);
}

void Server_connection::going_bottom(){
	send_code(GOINGBOTTOM);
}

void Server_connection::going_right(){
	send_code(GOINGRIGHT);
}

void Server_connection::going_left(){
	send_code(GOINGLEFT);
}

void Server_connection::exit_game(){
	send_code(EXITGAME);
}

void Server_connection::get_coords(Coords *coords, int *count, int *ping)
{
	Timer ping_timer;
	if (!getting_coords){
		ping_timer.start();
		send_code(GETCOORDS);
	}
	if (SDLNet_CheckSockets(set, 0) == 1)
	{
		while (SDLNet_SocketReady(sd) != 0){
			if (SDLNet_TCP_Recv(sd, (void *)count, sizeof(int)) <= 0){
				std::string error(SDLNet_GetError());
				throw std::runtime_error("Couldn't receive coord count: " + error);
			}

			*ping = ping_timer.ticks();		//is esmes cia ping gauni, nors server side dar atliekami skaciavimai tai jis nera tikras :D

			if (*count > 1){
				printf("count: %d\n", *count);
			}

			if (SDLNet_TCP_Recv(sd, (void *)coords, *count*sizeof(Coords)) <= 0){
				std::string error(SDLNet_GetError());
				throw std::runtime_error("Couldn't receive coords: " + error);
			}

			getting_coords = false;
		}
	}
}

void Server_connection::get_state_packet(State_Packet *data, int *ping)
{
	Timer ping_timer;
	if (!getting_coords){
		ping_timer.start();
		send_code(GETSTATEPACKET);
	}
	if (SDLNet_CheckSockets(set, 0) == 1)
	{
		if (SDLNet_SocketReady(sd) != 0){
			if (SDLNet_TCP_Recv(sd, (void *)data, sizeof(State_Packet)) <= 0){
				std::string error(SDLNet_GetError());
				throw std::runtime_error("Couldn't receive coord count: " + error);
			}

			*ping = ping_timer.ticks();		//is esmes cia ping gauni, nors server side dar atliekami skaciavimai tai jis nera tikras :D

			getting_coords = false;
		}
	}
}

Server_connection::~Server_connection(){
	SDLNet_TCP_DelSocket(set, sd);
	SDLNet_FreeSocketSet(set);
	SDLNet_TCP_Close(sd);
	SDLNet_Quit();
}