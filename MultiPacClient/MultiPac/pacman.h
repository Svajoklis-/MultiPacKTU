#pragma once
#include <SDL.h>
#include "game_state.h"
#include "globals.h"
#include "timer.h"
#include<fstream>
#include<iostream>
using namespace std;


enum sprites
{
	FULL,
	ONE_SIXTH,
	ONE_FOURTH,
	SPRITES_TOTAL
};




class Pacman
{
public:
	Pacman();
	void render();
	~Pacman();

private:
	void render_sprite(int x, int y, SDL_Rect* clip);
	void load_sprites();


	double temporary_scale_var;
	Timer timer;
	SDL_Texture *sprite_sheet;
	SDL_Rect sprite_clips[SPRITES_TOTAL];

};