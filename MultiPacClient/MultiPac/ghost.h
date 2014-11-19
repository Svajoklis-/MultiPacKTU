#pragma once
#include <SDL.h>
#include "globals.h"
#include "timer.h"
#include<fstream>
using namespace std;

class Ghost
{
public:
	Ghost();
	void render(int x_offset, int y_offset);
	void set_coords(int x, int y, int direction);
	void turn_vulnerable();
	~Ghost();
private:
	void render_sprite(int x, int y, SDL_Rect* clip);
	void render_blink_sprite(int x, int y, SDL_Rect* clip);
	void load_sprites();
	int x, y, direction;
	int ghost_id;

	int vulnerability_time = 10000;
	int blinking_interval = 500;
	bool vulnerable;
	Timer vulnerability_timer;

	Timer timer;
	int frame = 0, frame_count = 2, frame_interval = 100;
	SDL_Texture *sprite_sheet;
	SDL_Texture *blink_sheet;
	SDL_Rect sprite_clips[8];
	SDL_Rect blink_clips[4];

};




