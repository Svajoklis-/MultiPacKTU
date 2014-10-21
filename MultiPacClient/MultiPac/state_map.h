#pragma once
#include <SDL.h>
#include "game_state.h"
#include "globals.h"
#include "map.h"
#include "pacman.h"

using namespace std;





class State_map : public Game_state
{
public:
	State_map();
	void events();
	void logic();
	void render();

	~State_map();
	
private:
	Map map;
	Pacman pacman;



};

