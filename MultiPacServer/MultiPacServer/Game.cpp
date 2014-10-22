#include "Game.h"

void Game::ReturnPlayersCoords(){
	int count = 0;
	Player::Coords coords[maxcount];
	for each (Player *player in players)
	{
		if (player->IsPlaying()){
			coords[count] = player->GetCoords();
			count++;
		}
	}
	for each (Player *player in players)
	{
		if (player->IsPlaying()){
			//kazkaip erorus suhandlinti
			SDLNet_TCP_Send(player->GetSocket(), (void *)&count, sizeof(int));
			SDLNet_TCP_Send(player->GetSocket(), (void *)&coords, count*sizeof(Player::Coords));
		}
	}
}

bool Game::CheckMap(Player *player){
	//all the map checking
	//returns if next player instruction is valid
	return true;
}

void Game::RemovePlayer(Player *player){
	for (unsigned int i = 0; i < players.size(); i++){
		if (player == players[i]){
			players.erase(players.begin() + i);
		}
	}
}

void Game::Update(){
	for each (Player *player in players)
	{
		if (player->IsPlaying()){
			player->MakeAMove(CheckMap(player));
		}
	}
}