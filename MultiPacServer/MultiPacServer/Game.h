#include "Player.h"

class Game{
	vector<Player*> players; //mutex needed
	int count;
public:

	static const int maxcount = 4;

	Game(){
		count = 0;
	}

	int GetPlayerCount(){
		return count;
	}

	void AddPlayer(Player *player){
		players.push_back(player);
	}

	void ReturnPlayersCoords(){
		int code = 666;
		int length = sizeof(int);
		SDLNet_TCP_Send(players[0]->GetSocket(), (void *)&code, length);
	}

	static int RunGame(){
		return 0;
	}

	bool CheckMap(Player::Coords coords, Player::Way way){
		return true;
	}

	~Game(){};
};