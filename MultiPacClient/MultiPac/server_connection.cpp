#include "server_connection.h"

#include <cstdio>
#include "timer.h"

Server_connection::Server_connection(){
	error = "";
	if (SDLNet_Init() < 0)
	{
		//error = SDLNet_GetError();
	}

	/* Resolve the host we are connecting to */
	if (SDLNet_ResolveHost(&ip, connectionstring, port) < 0)
	{
		//error = SDLNet_GetError();
	}

	/* Open a connection with the IP provided (listen on the host's port) */
	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		//error = SDLNet_GetError();
	}
}


int Server_connection::get_code(int code){
	int length = sizeof(code);
	if (SDLNet_TCP_Send(sd, (void *)&code, length) < length)
	{
		return -1;
	}

	if (code == 15){
		int index = 0;
		if (SDLNet_TCP_Recv(sd, (void *)&index, sizeof(int)) > 0){
			return index;
		}
		return -1;
	}
	return 0;
}

void Server_connection::get_coords(int *num, int *ping)
{
	if (!getting_coords)
	{
		std::thread *run_thread = new std::thread(&Server_connection::thread_get_coords, this, num, ping);
		getting_coords = true;
	}
}

void Server_connection::thread_get_coords(int *num, int *ping)
{
	Timer ping_timer;
	ping_timer.start();
	int code = MESSAGEOFTHEDAY;
	int length = sizeof(code);
	if (SDLNet_TCP_Send(sd, (void *)&code, length) < length)
	{
		*num = -1;
	}

	int index = 0;
	if (SDLNet_TCP_Recv(sd, (void *)&index, sizeof(int)) > 0){
		*num = index;
		*ping = ping_timer.ticks();
		this->getting_coords = false;
		return;
	}

	*num = -1;
	*ping = ping_timer.ticks();
	this->getting_coords = false;
	return;
}

Server_connection::~Server_connection(){
	SDLNet_TCP_Close(sd);
	SDLNet_Quit();
}