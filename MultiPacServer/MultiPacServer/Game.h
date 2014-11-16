#include "Player.h"
#include "Ghost.h"
#include <vector>
#include "SDL_net.h"

class Game{
public:
	static const int mapheight = 27;
	static const int mapwidth = 21;
	static const int maxplayercount = 4;
	static const int maxghostcount = 8;
	static const int tile = 8;

	struct State_Packet{
		int player_count;
		int ghost_count;
		int score;
		int lives;
		bool playing;
		Player::Coords players[maxplayercount];
		Player::Coords ghosts[maxghostcount];
		int map[mapheight][mapwidth];
	};

private:
	std::vector<Player*> players;	//mutex needed
	std::vector<Ghost*> ghosts;		//mutex needed
	int map[mapheight][mapwidth];
	State_Packet data;

public:
	Game();

	int GetPlayerCount() { return players.size(); }
	void GetMap(int map[][mapwidth]);
	void AddPlayer(Player *player);
	void RemovePlayer(Player *player);
	void ReturnPlayersCoords(Player::Coords coords[], int &count);
	State_Packet GetStatePacket(){ return data; }

	bool CheckMap(Entity *entity, Entity::Way way);
	void CheckPellets(Player *player);
	bool CheckCollision(Entity *entity);
	bool IsRunning(){ return players.size() > 0; }
	void Update();

	~Game(){};

};