#include "Game.h"
#include <fstream>

Game::Game(){
	std::ifstream file;
	file.open("map\\map.txt");
	for (int i = 0; i < mapheight; i++)
		for (int j = 0; j < mapwidth; j++)
			file >> map[i][j];
	file.close();
}

void Game::GetMap(int map[][mapwidth]){
	for (int i = 0; i < mapheight; i++)
		for (int j = 0; j < mapwidth; j++)
			map[i][j] = this->map[i][j];
}

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

bool Game::CheckMap(Player *player, Player::Way way){
	//all the map checking
	//returns if next player instruction is valid
	Player::Coords coords = player->GetCoords();
	switch (way)
	{
	case Player::Right:
		if (map[coords.y / 8][coords.x / 8 + 1] == 0 && coords.y % 8 == 0) return true;
		break;
	case Player::Bottom:
		if (map[coords.y / 8 + 1][coords.x / 8] == 0 && coords.x % 8 == 0) return true;
		break;
	case Player::Left:
		if (map[coords.y / 8][(coords.x - 1) / 8] == 0 && coords.y % 8 == 0) return true;
		break;
	case Player::Top:
		if (map[(coords.y - 1) / 8][coords.x / 8] == 0 && coords.x % 8 == 0) return true;
		break;
	}
	return false;
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
			player->MakeAMove(CheckMap(player, player->GetCoords().way), CheckMap(player, player->GetNextWay()));
		}
	}
}