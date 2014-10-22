#include "Player.h"
#include <vector>
#include "SDL_net.h"

class Game{

	std::vector<Player*> players; //mutex needed
	int map[27][21];
public:

	static const int maxcount = 4;

	Game(){
		for (int i = 0; i < 27; i++)
			for (int j = 0; j < 21; j++)
				map[i][j] = 1;
	}

	int GetPlayerCount() { return players.size(); }
	void GetMap(int map[][21]){ map = this->map; }
	void AddPlayer(Player *player) { players.push_back(player); }
	void RemovePlayer(Player *player);
	void ReturnPlayersCoords();

	bool CheckMap(Player *player);
	bool IsRunning(){ return players.size() > 0; }
	void Update();

	~Game(){};
};