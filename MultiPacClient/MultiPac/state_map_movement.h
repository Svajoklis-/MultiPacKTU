#include <SDL.h>

using namespace std;

#include "game_state.h"
#include "server_connection.h"
#include "globals.h"
#include "timer.h"
#include "map.h"
#include "pacman.h"

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
	int ping = 0;

	int dir = 0;

	Map map;

	bool dir_sent = false;

	Pacman pacman[4];
};

#endif // H_STATE_MAP_MOVEMENT