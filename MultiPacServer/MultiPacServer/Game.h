#include "Player.h"
#include "Ghost.h"
#include <vector>
#include "SDL_net.h"

class Game{
public:
	static const int mapheight = 27;
	static const int mapwidth = 21;
	static const int maxplayercount = 4;
	static const int maxghostcount = 4;
	static const int tile = 8;

	struct State_Packet{
		int player_count;
		int ghost_count;
		int score;
		int lives;
		bool playing[maxplayercount];
		Entity::Coords players[maxplayercount];
		Entity::Coords ghosts[maxghostcount];
		Ghost::Personality ghostmodel[maxghostcount];
		int map[mapheight][mapwidth];
	};

private:
	std::vector<Player*> players;	//mutex needed
	std::vector<Ghost*> ghosts;		//mutex needed
	int map[mapheight][mapwidth];
	State_Packet data;
	int pellets;

	void UpdateMap();
	bool CheckMap(Entity *entity, Entity::Way way);
	void CheckPellets(Player *player);
	void CheckCollision(Entity *entity);
	void CheckTeleport(Entity *entity);
	void CheckGhostBrain(Ghost *ghost);

public:
	Game();

	int GetPlayerCount();
	void GetMap(int map[][mapwidth]);
	void AddPlayer(Player *player);
	void RemovePlayer(Player *player);
	void ReturnPlayersCoords(Player::Coords coords[], int &count);
	State_Packet GetStatePacket();

	bool IsRunning();
	void Update();

	~Game(){};

};