#include "Player.h"
#include <vector>
#include "SDL_net.h"

class Game{
public:
	static const int mapheight = 27;
	static const int mapwidth = 21;
	static const int maxcount = 4;

private:
	std::vector<Player*> players; //mutex needed
	int map[mapheight][mapwidth];

public:
	Game();

	int GetPlayerCount() { return players.size(); }
	void GetMap(int map[][mapwidth]);
	void AddPlayer(Player *player) { players.push_back(player); }
	void RemovePlayer(Player *player);
	void ReturnPlayersCoords(Player::Coords coords[], int &count);

	bool CheckMap(Player *player, Player::Way way);
	bool IsRunning(){ return players.size() > 0; }
	void Update();

	~Game(){};

};