#pragma once
#include "globals.h"
#include<fstream>
using namespace std;

enum different_items
{
	ITEM_NOTHING,
	ITEM_PELLET,
	ITEM_SUPERPELLET,
	ITEM_BONUS_1,
	ITEM_BONUS_2,
	ITEM_BONUS_3,
	ITEM_BONUS_4,
	ITEM_BONUS_5,
	ITEM_BONUS_6,
	ITEM_BONUS_7,
	ITEM_TOTAL
};


class Items
{
public:
	Items();
	void render(int x_offset, int y_offset);
	void read_from_file();
	void load_from_memory(int** map);
	void assign_tiles();
	~Items();

private:
	void render_pellet(int x, int y, SDL_Rect* clip);
	void render_item(int x, int y, SDL_Rect* clip);

	void load_items();

	int item_array[29][23];
	SDL_Texture *item_sprite_sheet;
	SDL_Texture *pellet_sprite_sheet;
	SDL_Rect item_sprite_clips[ITEM_TOTAL];

};