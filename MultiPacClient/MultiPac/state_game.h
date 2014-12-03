#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

#include "game_state.h"
#include "server_connection.h"
#include "globals.h"
#include "timer.h"
#include "map.h"
#include "items.h"
#include "pacman.h"
#include "ghost.h"
#include "score.h"

#ifndef H_STATE_GAME
#define H_STATE_GAME

class State_game : public Game_state
{
public:
	State_game();
	void events();
	void logic();
	void render();

	~State_game();

private:
	Server_connection connection;
	Server_connection::Coords coords[4];	//deprecated?
	int coord_count = 0;					//deprecated?
	Server_connection::State_Packet data;

	int ping = 0;

	int dir = 0;

	Map map;
	Items items;

	// -1 no, 0 up, 1 right, 2 down, 3 left
	int last_sent = -1;

	Pacman pacman[4];
	Ghost ghost[8];
	Score score;

	// sounds

	Mix_Chunk *snd_ghosts_active;
	bool ghosts_active = false;
	int ghosts_active_channel;

	Mix_Chunk *snd_ghosts_scared;
	bool ghosts_scared = false;
	int ghosts_scared_channel;

	Mix_Chunk *snd_pause;
	Mix_Chunk *snd_eat_low, *snd_eat_high;
	bool played_low = false;
};

#endif // H_STATE_GAME