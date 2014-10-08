#include "Game.h"

void Game::ReturnPlayersCoords(){
	int code = 666;
	int length = sizeof(int);
	SDLNet_TCP_Send(players[0]->GetSocket(), (void *)&code, length);
}

int Game::RunGame(){
	return 0;
}

bool Game::CheckMap(Player::Coords coords, Player::Way way){
	//all the map checking
	//returns if next player instruction is valid
	return true;
}