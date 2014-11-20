#include "Game.h"
#include <fstream>

Game::Game(){
	std::ifstream file;
	file.open("map\\map.txt");
	for (int i = 0; i < mapheight; i++)
		for (int j = 0; j < mapwidth; j++){
			file >> map[i][j];
		}
	file.close();
	UpdateMap();
}

void Game::GetMap(int map[][mapwidth]){
	for (int i = 0; i < mapheight; i++)
		for (int j = 0; j < mapwidth; j++)
			map[i][j] = this->map[i][j];
}

void Game::UpdateMap(){
	for (int i = 0; i < mapheight; i++)
		for (int j = 0; j < mapwidth; j++)
			data.map[i][j] = map[i][j];
	pellets = 200;
}

void Game::AddPlayer(Player *player){
	players.push_back(player);

}

void Game::ReturnPlayersCoords(Player::Coords coords[], int &count){
	for each (Player *player in players)
	{
		if (player->IsPlaying()){
			coords[count] = player->GetCoords();
			count++;
		}
	}
}

bool Game::CheckMap(Entity *entity, Entity::Way way){
	//all the map checking
	//returns if instruction is valid
	Entity::Coords coords = entity->GetCoords();
	switch (way)
	{
	case Entity::Right:
		if (data.map[coords.y / tile][coords.x / tile + 1] != Entity::Wall && coords.y % tile == 0) return true;
		break;
	case Entity::Bottom:
		if (data.map[coords.y / tile + 1][coords.x / tile] != Entity::Wall && coords.x % tile == 0) return true;
		break;
	case Entity::Left:
		if (data.map[coords.y / tile][(coords.x - 1) / tile] != Entity::Wall && coords.y % tile == 0) return true;
		break;
	case Entity::Top:
		if (data.map[(coords.y - 1) / tile][coords.x / tile] != Entity::Wall && coords.x % tile == 0) return true;
		break;
	}
	return false;
}

bool Game::CheckCollision(Entity *entity){
	Entity::Coords host = entity->GetCoords();
	for each (Player *player in players){
		Entity::Coords guest = player->GetCoords();
		if ((abs(host.x - guest.x) < 6) && (abs(host.y - guest.y) < 6)){
			if (typeid(*entity) == typeid(Player)){
				Player *collider = (Player *)entity;
				if (collider != player && !collider->IsInactive() && !player->IsInactive()){
					if(host.way != guest.way) guest.way = player->ReverseWay(guest.way);
					player->SetCoords(guest);
					player->SetInactive();
					player->SetNextWay(player->GetCoords().way);
					host.way = collider->ReverseWay(host.way);
					collider->SetCoords(host);
					collider->SetInactive();
					collider->SetNextWay(collider->GetCoords().way);
				}
			}
			else{
				//player dies or eats
			}
		}
	}
	/*if (typeid(*entity) == typeid(Player)){
		//patikrinam su kitais zaidejais - atsokam
		//patikrinam su vaiduokliais - mirstam arba valgom
	}
	else{
		//patikrinama su zaidejais - mirsta arba mirsta
	}*/

	return true;
}

void Game::CheckPellets(Player *player){
	Entity::Coords coords = player->GetCoords();
	if (coords.x % tile == 0 && coords.y % tile == 0){	//jeigu vidury tailo
		switch (data.map[coords.y / tile][coords.x / tile])
		{
		case Entity::NormalPellet:
			data.map[coords.y / tile][coords.x / tile] = Entity::Blank;
			pellets--;
			player->IncScore();
			break;
		case Entity::PowerPellet:
			break;
		}
	}
	
}

void Game::RemovePlayer(Player *player){
	for (unsigned int i = 0; i < players.size(); i++){
		if (player == players[i]){
			players.erase(players.begin() + i);
		}
	}
}

void Game::Update(){
	data.player_count = 0;
	for each (Player *player in players)
	{
		if (player->IsPlaying()){
			player->MakeAMove(CheckMap(player, player->GetCoords().way), CheckMap(player, player->GetNextWay()));
			Entity::Coords coords = player->GetCoords();
			if (coords.x <= 0){
				coords.x = mapwidth*tile - tile;
				player->SetCoords(coords);
			}else if (coords.x >= mapwidth*tile - tile){
				coords.x = 0;
				player->SetCoords(coords);
			}
			CheckPellets(player);
			CheckCollision(player);
			if (player->IsInactive()){
				Entity::Coords coords = player->GetCoords();
				coords.way = player->ReverseWay(coords.way);
				data.players[data.player_count] = coords;
			}
			else
			{
				data.players[data.player_count] = player->GetCoords();
			}
			data.player_count++;

		}
	}
	/*for each (Ghost *ghost in ghosts)
	{
		ghost->MakeAMove(CheckMap(ghost, ghost->GetCoords().way), CheckMap(ghost, ghost->));
	}
	for each (Player *player in players)
	{
		if (player->IsPlaying()){
			CheckCollision(player);
		}
	}
	for each (Ghost *ghost in ghosts)
	{
		CheckCollision(ghost);
	}*/
	if (pellets == 0) UpdateMap();
}