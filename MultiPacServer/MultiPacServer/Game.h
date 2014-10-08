#include "Player.h"

class Game{
	vector<Player*> players; //mutex needed
	static int count;
public:
	Game(){
		count = 0;
	}

	void AddPlayer(Player *player){
		players.push_back(player);
	}

	static int RunGame(void *data){
		while (count > 0){

		}
		return 0;
	}

	bool CheckMap(Player::Coords coords, Player::Way way){
		return true;
	}

	~Game(){};
};