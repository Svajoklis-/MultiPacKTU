#include "Player.h"
#include <vector>
#include "SDL_net.h"

class Game{
	std::vector<Player*> players; //mutex needed
public:

	static const int maxcount = 4;

	Game(){}

	int GetPlayerCount() { return players.size(); }

	void AddPlayer(Player *player) { players.push_back(player); }

	void ReturnPlayersCoords();

	static int RunGame();

	bool CheckMap(Player::Coords coords, Player::Way way);

	~Game(){};
};