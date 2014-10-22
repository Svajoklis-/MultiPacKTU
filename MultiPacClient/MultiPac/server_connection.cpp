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
	if (!getting_coords)
	{
		std::thread *run_thread = new std::thread(&Server_connection::thread_get_coords, this, coords, count, ping);
		getting_coords = true;
	}
}

void Server_connection::thread_get_coords(Coords *coords, int *count, int *ping)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(30)); //cia pabandymui kad per daznai nesiust
	Timer ping_timer;
	ping_timer.start();
	send_code(GETCOORDS);
	if (SDLNet_TCP_Recv(sd, (void *)count, sizeof(int)) <= 0){
		std::string error(SDLNet_GetError());
		throw std::runtime_error("Couldn't receive coord count: " + error);
	}

	*ping = ping_timer.ticks();		//is esmes cia ping gauni, nors server side dar atliekami skaciavimai tai jis nera tikras :D

	if (SDLNet_TCP_Recv(sd, (void *)coords, *count*sizeof(Coords)) <= 0){
		std::string error(SDLNet_GetError());
		throw std::runtime_error("Couldn't receive coords: " + error);
	}

	this->getting_coords = false;
	return;
}

Server_connection::~Server_connection(){
	SDLNet_TCP_Close(sd);
	SDLNet_Quit();
}