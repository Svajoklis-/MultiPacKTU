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

enum ClientPackageIndex{
	NOP = 0,
	NewGame = 10,			//send map and stuff
	Ready = 11,				//loaded everything
	GetCoords = 15,
	GetMap = 16,
	GetScore = 17,
	GetStatePacket = 18,	//future is here
	GoingTop = 20,
	GoingRight = 21,
	GoingBottom = 22,
	GoingLeft = 23,
	ResetDir = 24,
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
int servertickduration = 30;	// kiek laiko (ms) skiriama vienam zaidimo tick

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
		if (result == "resetscore"){
			for (unsigned i = 0; i < players.size(); i++){
				players[i]->SetScore(0);
			}
		}
		if (result == "setgamespeed"){
			cin >> servertickduration;
		}
		if (result == "help"){
			cout << "resetscore\nsetgamespeed\nclients\nquit\n";
		}
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
	int count;
	Game::State_Packet packet;
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
				break;
			case Ready:
				player->SetPlaying(true);
				break;
			case GetCoords:
				count = 0;
				Player::Coords coords[Game::maxplayercount];
				game->ReturnPlayersCoords(coords, count);
				if (SDLNet_TCP_Send(player->GetSocket(), (void *)&count, sizeof(int)) == sizeof(int)){
					SDLNet_TCP_Send(player->GetSocket(), (void *)&coords, count*sizeof(Player::Coords));
				}
				break;
			case GetStatePacket:
				packet = game->GetStatePacket();
				packet.lives = player->GetLives();
				packet.score = player->GetScore();
				SDLNet_TCP_Send(player->GetSocket(), (void *)&packet, sizeof(Game::State_Packet));
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
			case ResetDir:
				//player->SetNextWay(player->GetCoords().way);		//sitas mane uzkniso - KKarolis
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
		if (games[i]->GetPlayerCount() < games[i]->maxplayercount){
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

	while (game->IsRunning()){
		game_tick.restart();

		game->Update();

		if (game_tick.ticks() < servertickduration)
		{
			SDL_Delay(servertickduration - game_tick.ticks());
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