#include "Game.h"
#include <fstream>
#include <cstdlib>

Game::Game(){
	std::ifstream file;
	file.open("map\\map.txt");
	for (int i = 0; i < mapheight; i++)
		for (int j = 0; j < mapwidth; j++){
			file >> map[i][j];
		}
	file.close();
	UpdateMap();
	for (int i = 0; i < maxghostcount; i++){
		Ghost *ghost = new Ghost((Ghost::Personality)i);
		ghosts.push_back(ghost);
	}
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
	//add some ghosts
	
	//add player
	players.push_back(player);
}

//deprecated
void Game::ReturnPlayersCoords(Player::Coords coords[], int &count){
	for each (Player *player in players)
	{
		if (player->IsAlive()){
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

int Game::GetPlayerCount() { return players.size(); }

Game::State_Packet Game::GetStatePacket(){ return data; }

bool Game::IsRunning(){ return players.size() > 0; }

void Game::CheckCollision(Entity *entity){
	Entity::Coords host = entity->GetCoords();
	for each (Player *player in players){
		Entity::Coords target = player->GetCoords();
		if ((abs(host.x - target.x) <= 4) && (abs(host.y - target.y) <= 4)){
			if (typeid(*entity) == typeid(Player)){												//if its a player
				Player *collider = (Player *)entity;
				if (collider != player && collider->IsActive() && player->IsActive() &&	//if not the same player and both active
					(!(target.x == Player::startingx && target.y == Player::startingy) &&		//and target isnt at starting position
					!(host.x == Player::startingx && host.y == Player::startingy))){			//and collider isnt at the starting position
					if (host.way != target.way) target.way = Entity::ReverseWay(target.way);	//if it comes from behind do not flip
					player->SetCoords(target);
					player->Deactivate();
					player->SetNextWay(target.way);
					host.way = Entity::ReverseWay(host.way);
					collider->SetCoords(host);
					collider->Deactivate();
					collider->SetNextWay(host.way);
				}
			}
			else{
				Ghost *collider = (Ghost *)entity;
				Ghost::Personality current = collider->GetPersonality();
				if (current != Ghost::Eyes){	//if ghost isnt dead
					//if ghosts are not frightened
					if (current != Ghost::FrightBlue && current != Ghost::FrightWhite){
						//kill pacman
						if (player->IsAlive()) player->Kill();
					}
					else{
						//ghost dies
						collider->SetPersonality(Ghost::Eyes);
						player->IncScore(200);
					}
				}	
			}
		}
	}
}

void Game::CheckGhostBrain(Ghost *ghost){
	Entity::Coords coords = ghost->GetCoords();
	//if its in the middle of the tile - able to turn (or not) and not in pacman domain
	if (coords.x % tile == 0 && coords.y % tile == 0 && coords.y != Player::startingy){		
		Entity::Way banned = Entity::ReverseWay(coords.way);	//ghost (almost) never turn back
		std::vector<Entity::Way> selection;
		int choice;
		int mindistance = (mapheight + mapwidth) * tile;
		Ghost::Personality current = ghost->GetPersonality();
		bool homebanned = coords.x == 80 && current != Ghost::Eyes; //cant go home if ure not dead
		if (CheckMap(ghost, Entity::Top) && banned != Entity::Top) selection.push_back(Entity::Top);
		if (CheckMap(ghost, Entity::Bottom) && banned != Entity::Bottom && !homebanned) selection.push_back(Entity::Bottom);
		if (CheckMap(ghost, Entity::Right) && banned != Entity::Right) selection.push_back(Entity::Right);
		if (CheckMap(ghost, Entity::Left) && banned != Entity::Left) selection.push_back(Entity::Left);
		
		switch (current)
		{
		case Ghost::Blinky:
		case Ghost::Pinky:
		case Ghost::Inky:
			for (unsigned i = 0; i < selection.size(); i++){
				Entity::Coords temp = coords;
				temp.way = selection[i];
				ghost->SetCoords(temp);
				temp = Entity::CoordsAfterMoving(ghost, tile);
				for each(Player *player in players){
					int distance;
					Entity::Coords pacman = player->GetCoords();
					switch (current)
					{
					case Ghost::Blinky:		//goes to closest pacman location
						distance = Entity::ManhattansDistance(temp, pacman);
						break;
					case Ghost::Pinky:		//goes to closest pacman location after 4 turns
						pacman = Entity::CoordsAfterMoving(player, 4*tile);
						distance = Entity::ManhattansDistance(temp, pacman);
						break;
					case Ghost::Inky:		//if its further than 6 tiles goes to closest pacman otherwise random
						distance = Entity::ManhattansDistance(temp, pacman);
						if (distance < 6*tile){
							distance = (mapheight + mapwidth) * tile;
							choice = std::rand() % selection.size();
						}
						break;
					}
					if (distance < mindistance){
						mindistance = distance;
						choice = i;
					}
				}
				ghost->SetCoords(coords);
			}
			break;
		case Ghost::Eyes:		//goes to the ghost house
			for (unsigned i = 0; i < selection.size(); i++){	
				Entity::Coords home = { Ghost::homex, Ghost::homey, Entity::Top };
				Entity::Coords temp = coords;
				temp.way = selection[i];
				ghost->SetCoords(temp);
				temp = Entity::CoordsAfterMoving(ghost, 1);
				int distance = Entity::ManhattansDistance(temp, home);
				if (distance < mindistance){
					mindistance = distance;
					choice = i;
				}
				ghost->SetCoords(coords);
			}
			break;
		case Ghost::Sue:		//roams randomly
		case Ghost::FrightBlue: //roams randomly
		case Ghost::FrightWhite://roams randomly
			choice = std::rand() % selection.size();
			break;	
		}
		coords.way = selection[choice];
		ghost->SetCoords(coords);
	}
}

void Game::CheckPellets(Player *player){
	Entity::Coords coords = player->GetCoords();
	if (coords.x % tile == 0 && coords.y % tile == 0){	//jeigu vidury tailo
		switch (data.map[coords.y / tile][coords.x / tile])
		{
		case Entity::Blank:
			break;
		case Entity::NormalPellet:
			data.map[coords.y / tile][coords.x / tile] = Entity::Blank;
			pellets--;
			player->IncScore(10);
			break;
		case Entity::PowerPellet:
			data.map[coords.y / tile][coords.x / tile] = Entity::Blank;
			for each (Ghost *ghost in ghosts){
				Entity::Coords coords2 = ghost->GetCoords();
				coords2.way = Entity::ReverseWay(coords2.way);
				ghost->SetPersonality(Ghost::FrightBlue);
				ghost->SetCoords(coords2);
				ghost->Frighten();
			}		
			player->IncScore(50);
			break;
		}
	}
	
}

void Game::CheckTeleport(Entity *entity){
	Entity::Coords tcoords = entity->GetCoords();
	if (tcoords.x <= 0){
		tcoords.x = mapwidth*tile - tile;
		entity->SetCoords(tcoords);
	}else if (tcoords.x >= mapwidth*tile - tile){
		tcoords.x = 0;
		entity->SetCoords(tcoords);
	}
	if (tcoords.y <= 0){
		tcoords.y = mapheight*tile - tile;
		entity->SetCoords(tcoords);
	}
	else if (tcoords.y >= mapheight*tile - tile){
		tcoords.y = 0;
		entity->SetCoords(tcoords);
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
	data.ghost_count = 0;
	for each (Player *player in players)
	{
		bool alive = player->IsAlive();
		for (int i = 0; i < player->GetSpeed(); i++){
			player->MakeAMove(CheckMap(player, player->GetCoords().way)&&alive, CheckMap(player, player->GetNextWay())&&alive);
			CheckTeleport(player);
			CheckPellets(player);
			CheckCollision(player);
		}

		//Updating state packet-----------------
		Entity::Coords scoords = player->GetCoords();
		if (!player->IsActive()){	//if player is inactive reverse way for flying effect
			scoords.way = Entity::ReverseWay(scoords.way);
			data.players[data.player_count] = scoords;
		}
		else
		{
			data.players[data.player_count] = scoords;
		}
		data.playing[data.player_count] = player->IsAlive();
		data.player_count++;
		//-------------------------------------
		player->Tick();
	}
	
	for each (Ghost *ghost in ghosts)
	{
		for (int i = 0; i < ghost->GetSpeed(); i++){
			CheckGhostBrain(ghost);
			ghost->MakeAMove(true, false);
			CheckTeleport(ghost);
			CheckCollision(ghost);
		}

		//Updating state packet------------
		data.ghosts[data.ghost_count] = ghost->GetCoords();
		data.ghostmodel[data.ghost_count] = ghost->GetPersonality();
		data.ghost_count++;
		//---------------------------------

		ghost->Tick();
	}

	if (pellets == 0) UpdateMap();
}