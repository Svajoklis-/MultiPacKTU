#include "items.h"


Items::Items()
{
	for (int i = 0; i < 29; i++)
	for (int j = 0; j < 23; j++)
		item_array[i][j] = 0;
	load_items();
}



void Items::render(int x_offset, int y_offset)
{
	for (int i = 1; i < 28; i++)
	{
		for (int j = 1; j < 22; j++)
		{
			if (item_array[i][j] < 3 && item_array[i][j] > 0)
				render_pellet((j - 1) * 8 + x_offset, (i - 1) * 8 + y_offset, &item_sprite_clips[item_array[i][j]]);
			else
			if (item_array[i][j] > 2)
				render_item((j - 1) * 8 - 4 + x_offset, (i - 1) * 8 - 4 + y_offset, &item_sprite_clips[item_array[i][j]]);
		}
			
	}
	
}

void Items::read_from_file()
{
	ifstream file;
	file.open("res\\map\\map.txt");
	for (int i = 1; i < 28; i++)
	{
		for (int j = 1; j < 22; j++)
		{
			file >> item_array[i][j];
			if (item_array[i][j] < 2)
				item_array[i][j] = 0;
			else item_array[i][j]--;
		}
	}
	file.close();

}


void Items::load_from_memory(int** map)
{
	for (int i = 1; i < 28; i++)
	{
		for (int j = 1; j < 22; j++)
		{
			if (map[i - 1][j - 1] > 1)
			{
				item_array[i][j] = map[i - 1][j - 1] - 1;
				map[i - 1][j - 1] = 0;
			}
		}
	}


}

void Items::load_items()
{

	pellet_sprite_sheet = load_image(ren, "res\\img\\tiles.bmp", 255, 0, 255);

	int row_y = 0;


	item_sprite_clips[0] = { 16, 0, 8, 8 };

	for (int i = 1; i < 3; i++)
	{
		item_sprite_clips[i].x = (i-1) * 8;
		item_sprite_clips[i].y = row_y;
		item_sprite_clips[i].w = 8;
		item_sprite_clips[i].h = 8;
	}

	item_sprite_sheet = load_image(ren, "res\\img\\bonus_items.bmp", 255, 0, 255);

	for (int i = 3; i < 10; i++)
	{
		item_sprite_clips[i].x = (i-3) * 16;
		item_sprite_clips[i].y = row_y;
		item_sprite_clips[i].w = 16;
		item_sprite_clips[i].h = 16;
	}

}

void Items::render_pellet(int x, int y, SDL_Rect* clip)
{
	SDL_Rect tile_rect = { x, y, 8, 8 };
	SDL_RenderCopy(ren, pellet_sprite_sheet, clip, &tile_rect);
}

void Items::render_item(int x, int y, SDL_Rect* clip)
{
	SDL_Rect tile_rect = { x, y, 16, 16 };
	SDL_RenderCopy(ren, item_sprite_sheet, clip, &tile_rect);
}

Items::~Items()
{
	SDL_DestroyTexture(pellet_sprite_sheet);
	SDL_DestroyTexture(item_sprite_sheet);
}
