#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

#include "game_state.h"
#include "server_connection.h"
#include "globals.h"
#include "timer.h"
#include "map.h"
#include "pacman.h"
#include "score.h"

#ifndef H_STATE_MAP_MOVEMENT
#define H_STATE_MAP_MOVEMENT

class State_map_movement : public Game_state
{
public:
	State_map_movement();
	void events();
	void logic();
	void render();

	~State_map_movement();

private:

	Server_connection connection;
	Server_connection::Coords coords[4];
	int coord_count = 0;
	Server_connection::State_Packet data;

	int ping = 0;

	int dir = 0;

	Map map;

	// -1 no, 0 up, 1 right, 2 down, 3 left
	int last_sent = -1;

	Pacman pacman[4];
	Score score;

	// sounds

	Mix_Chunk *snd_chomping;
	int chomp_channel;
	Mix_Chunk *snd_pause;
};

#endif // H_STATE_MAP_MOVEMENT