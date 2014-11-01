#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

#include "SDL_net.h"
#include "Game.h"
#include "SDL.h"
#include "SDL_thread.h"
#include "timer.h"


enum ServerPackageIndex{

};

enum ClientPackageIndex{
	NOP = 0,
	NewGame = 10,			//send map and stuff
	Ready = 11,				//loaded everything
	NUMBEROFTHEDAY = 12,
	GetCoords = 15,
	GoingTop = 20,
	GoingRight = 21,
	GoingBottom = 22,
	GoingLeft = 23,
	ExitGame = 25,
	Disconnect = 30
};

void InitServer();
void AcceptClients();
int ClientService(void *data);
int ConsoleControl(void *data);
int GameLoop(void *data);
Game* AddToGame(Player* player);
void ReturnPlayersCoords(Game *game);
void FreeServer();

bool running = true;

int daynumber = 666;

TCPsocket serversocket;
IPaddress ip;
Uint16 port = 2001;

vector<Player*> players;	//mutex needed
vector<Game*> games;		//mutex needed

int main(int argc, char *argv[])
{
	InitServer();

	while (running){
		AcceptClients();
	}

	FreeServer();

	return EXIT_SUCCESS;
}

void InitServer(){
	if (SDL_Init(0) < 0)
	{
		//kazkaip erorus suhandlinti
		fprintf(stderr, "SDL_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDLNet_Init() < 0)
	{
		//kazkaip erorus suhandlinti
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!SDL_CreateThread(ConsoleControl, "PacmanConsoleControl", (void *)NULL))
	{
		//kazkaip erorus suhandlinti
		fprintf(stderr, "Creating Console Control: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (SDLNet_ResolveHost(&ip, NULL, port) < 0)
	{
		//kazkaip erorus suhandlinti
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!(serversocket = SDLNet_TCP_Open(&ip)))
	{
		//kazkaip erorus suhandlinti
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
}

int ConsoleControl(void *data){
	string result = "";
	while (result != "quit"){
		cin >> result;
		if (result == "joke"){ cout << "YOU SHALL NOT PASS!!!" << endl; }
		if (result == "clients"){
			for (unsigned i = 0; i < players.size(); i++){
				TCPsocket socket = players[i]->GetSocket();
				IPaddress *remoteIP = SDLNet_TCP_GetPeerAddress(socket);
				Uint8 *address = (Uint8*)&remoteIP->host;
				printf("Client connected: %d.%d.%d.%d %d\n", (unsigned short)address[0], (unsigned short)address[1], (unsigned short)address[2], (unsigned short)address[3], SDLNet_Read16(&remoteIP->port));
			}
		}
		if (result == "setmagicnumber"){ cin >> daynumber; }
	}
	running = false;
	return 0;
}

void AcceptClients(){
	TCPsocket clientsock;
	if ((clientsock = SDLNet_TCP_Accept(serversocket)))
	{
		Player *player = new Player(clientsock);
		players.push_back(player);
		if (!SDL_CreateThread(ClientService, "PackmanClientService", (void *)player))
		{
			//kazkaip erorus suhandlinti
			fprintf(stderr, "Creating Client Service: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}
	}
}

int ClientService(void *data){
	bool serving = true;
	Player *player = static_cast<Player*>(data);
	Game *game = NULL;
	while (running && serving){
		ClientPackageIndex index = NOP;
		if (SDLNet_TCP_Recv(player->GetSocket(), (void *)&index, sizeof(int)) > 0){
			switch (index)
			{
			case NewGame:
				game = AddToGame(player);
				int map[Game::mapheight][Game::mapwidth];
				game->GetMap(map);
				SDLNet_TCP_Send(player->GetSocket(), (void *)map, 27 * 21 * sizeof(int));
				//return map somehow
				break;
			case Ready:
				player->SetPlaying(true);
				break;
			case NUMBEROFTHEDAY:
				SDLNet_TCP_Send(player->GetSocket(), (void *)&daynumber, sizeof(int));
				break;
			case GetCoords:
				game->ReturnPlayersCoords();
				break;
			case GoingTop:
				player->SetNextWay(Player::Top);
				break;
			case GoingRight:
				player->SetNextWay(Player::Right);
				break;
			case GoingBottom:
				player->SetNextWay(Player::Bottom);
				break;
			case GoingLeft:
				player->SetNextWay(Player::Left);
				break;
			case ExitGame:
				game->RemovePlayer(player);
				game = NULL;
				break;
			case Disconnect:
				serving = false;
				if (game) { game->RemovePlayer(player); }
				break;
			default:
				printf("Got unknown numbah %d from client MUHAHAHA\n", index);
				break;
			}
		}
		else{
			//kazkaip erorus suhandlinti, jeigu tcp nutruko pasalinam zaideja
			serving = false;
			if (game) { game->RemovePlayer(player); }
		}
	}
	for (unsigned i = 0; i < players.size(); i++){
		if (players[i] == player) players.erase(players.begin() + i);
	}
	delete player;
	return 0;
}

Game* AddToGame(Player* player){
	for (unsigned i = 0; i < games.size(); i++){
		if (games[i]->GetPlayerCount() < games[i]->maxcount){
			games[i]->AddPlayer(player);
			return games[i];
		}
	}
	Game *game = new Game();
	games.push_back(game);
	game->AddPlayer(player);
	if (!SDL_CreateThread(GameLoop, "GameLoopService", (void *)game))
	{
		// kaþkaip suhandlinti errorus
		fprintf(stderr, "Creating Game Service: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	return game;
}

int GameLoop(void *data){
	Game *game = static_cast<Game*>(data);
	Timer game_tick;
	game_tick.start();

	// kiek laiko (ms) skiriama vienam þaidimo tick
	int tick_duration = 50;

	while (game->IsRunning()){
		game_tick.restart();

		game->Update();

		if (game_tick.ticks() < tick_duration)
		{
			SDL_Delay(tick_duration - game_tick.ticks());
		}
	}

	for (unsigned i = 0; i < games.size(); i++){
		if (games[i] == game) games.erase(games.begin() + i);
	}
	delete game;
	return 0;
}

void FreeServer(){
	SDLNet_Quit();
	SDL_Quit();
}