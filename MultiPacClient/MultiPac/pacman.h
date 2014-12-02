#pragma once
#include <SDL.h>
#include "globals.h"
#include "timer.h"
#include<fstream>
using namespace std;



class Pacman
{
public:
	Pacman();
	void render(int x_offset, int y_offset);
	void set_coords(int x, int y, int direction);
	void set_state(int state);
	~Pacman();

private:
	void render_sprite(int x, int y, SDL_Rect* clip);
	void render_death_sprite(int x, int y, SDL_Rect* clip);
	void load_sprites();
	int x, y, direction;

	int state;

	Timer timer;
	int frame = 0, frame_count = 4, frame_interval = 100;

	SDL_Texture *sprite_sheet;
	SDL_Texture *death_sheet;
	SDL_Rect sprite_clips[16];
	SDL_Rect death_clips[10];

	Timer stop_timer;

};