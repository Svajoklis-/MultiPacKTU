#pragma once
#include <SDL.h>
#include "globals.h"
#include "timer.h"
#include<fstream>
//#include<iostream>
using namespace std;



class Pacman
{
public:
	Pacman();
	void render(int x_offset, int y_offset);
	void set_coords(int x, int y, int direction);
	~Pacman();

private:
	void render_sprite(int x, int y, SDL_Rect* clip);
	void load_sprites();
	int x, y, direction;

	Timer timer;
	int frame = 0, frame_count = 4, frame_interval = 100;
	SDL_Texture *sprite_sheet;
	SDL_Rect sprite_clips[16];

};