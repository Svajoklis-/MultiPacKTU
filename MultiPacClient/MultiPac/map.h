#pragma once
#include <SDL.h>
#include "game_state.h"
#include "globals.h"
#include<fstream>
#include<iostream>
using namespace std;


enum neighbours
{
	UPPER_LEFT,
	UPPER_MIDDLE,
	UPPER_RIGHT,
	MIDDLE_LEFT,
	MIDDLE_RIGHT,
	LOWER_LEFT,
	LOWER_MIDDLE,
	LOWER_RIGHT,
	NEIGHBOURS_TOTAL
};

enum different_tiles
{
	TILE_VERTICAL,
	TILE_HORIZONTAL,
	TILE_LEFT_DOWN,
	TILE_LEFT_UP,
	TILE_UP_RIGHT,
	TILE_DOWN_RIGHT,
	TILE_VERTICAL_END_UP,
	TILE_HORIZONTAL_END_RIGHT,
	TILE_VERTICAL_END_DOWN,
	TILE_HORIZONTAL_END_LEFT,
	TILE_T_UP,                     //T
	TILE_T_RIGHT,
	TILE_T_DOWN,
	TILE_T_LEFT,
	TILE_ALL_SIDES,
	TILE_FREE,
	TILE_TOTAL
};


class Map
{
public:
	Map();
	void render();
	void load_from_memory(int** map);
	void read_from_file();
	void assign_tiles();
	~Map();

private:
	void render_tile(int x, int y, SDL_Rect* clip);
	
	void load_tiles();



	int map_array[29][23];
	SDL_Texture *tile_sprite_sheet;
	SDL_Rect tile_sprite_clips[TILE_TOTAL];

};