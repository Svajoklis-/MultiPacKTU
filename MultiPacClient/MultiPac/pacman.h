#pragma once
#include <SDL.h>
#include "game_state.h"
#include "globals.h"
#include "timer.h"
#include<fstream>
#include<iostream>
using namespace std;



class Pacman
{
public:
	Pacman();
	void render(int x, int y, int degrees);
	~Pacman();

private:
	void render_sprite(int x, int y, SDL_Rect* clip, double angle);
	void load_sprites();


	Timer timer;
	SDL_Texture *sprite_sheet;
	SDL_Rect sprite_clips[4];

	

};