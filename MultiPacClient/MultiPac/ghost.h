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
	~Ghost();
private:
	void render_sprite(int x, int y, SDL_Rect* clip);
	void load_sprites();
	int x, y, direction;
	int ghost_id;
	Timer timer;
	int frame = 0, frame_count = 2, frame_interval = 100;
	SDL_Texture *sprite_sheet;
	SDL_Rect sprite_clips[8];

};




