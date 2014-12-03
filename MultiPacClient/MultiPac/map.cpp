#include "map.h"

Map::Map()
{
	for (int i = 0; i < 29; i++)
	for (int j = 0; j < 23; j++)
		map_array[i][j] = 0;
	load_tiles();
}


void Map::render(int x_offset, int y_offset)
{
	for (int i = 1; i < 28; i++)
	for (int j = 1; j < 22; j++)
		render_tile((j - 1) * 8 + x_offset, (i - 1) * 8 + y_offset, &tile_sprite_clips[map_array[i][j]]);
}

void Map::load_from_memory(int** map)
{
	for (int i = 1; i < 28; i++)
	{
		for (int j = 1; j < 22; j++)
		{
			map_array[i][j] = map[i - 1][j - 1];
		}
	}

	assign_tiles();
}



void Map::read_from_file()
{
	ifstream file;
	file.open("res\\map\\map.txt");
	for (int i = 1; i < 28; i++)
	{
		for (int j = 1; j < 22; j++)
		{
			file >> map_array[i][j];
			if (map_array[i][j] > 1)
				map_array[i][j] = 0;
		}
	}
	file.close();

}

void Map::load_tiles()
{
	tile_sprite_sheet = load_image(ren, "res\\img\\tiles.bmp", 255, 0, 255);

	int row_y = 8;
	for (int i = 0; i < 8; i++)
	{
		tile_sprite_clips[i].x = i * 8;
		tile_sprite_clips[i].y = row_y;
		tile_sprite_clips[i].w = 8;
		tile_sprite_clips[i].h = 8;
	}
	row_y = 16;
	for (int i = 0; i < 8; i++)
	{
		tile_sprite_clips[i + 8].x = i * 8;
		tile_sprite_clips[i + 8].y = row_y;
		tile_sprite_clips[i + 8].w = 8;
		tile_sprite_clips[i + 8].h = 8;
	}

	tile_sprite_clips[TILE_GATE_LEFT] = { 0, 24, 8, 8 };
	tile_sprite_clips[TILE_GATE_CENTER] = { 8, 24, 8, 8 };
	tile_sprite_clips[TILE_GATE_RIGHT] = { 16, 24, 8, 8 };
}

void Map::assign_tiles()
{
	int map_with_tiles[29][23];
	int neighbourhood[NEIGHBOURS_TOTAL];
	for (int i = 0; i < 29; i++)
	for (int j = 0; j < 23; j++)
		map_with_tiles[i][j] = map_array[i][j];

	for (int i = 1; i < 28; i++)
	{
		for (int j = 1; j < 22; j++)
		{
			if (map_array[i][j] != 0)
			{

				neighbourhood[UPPER_LEFT] = map_array[i - 1][j - 1];
				neighbourhood[UPPER_MIDDLE] = map_array[i - 1][j];
				neighbourhood[UPPER_RIGHT] = map_array[i - 1][j + 1];
				neighbourhood[MIDDLE_LEFT] = map_array[i][j - 1];
				neighbourhood[MIDDLE_RIGHT] = map_array[i][j + 1];
				neighbourhood[LOWER_LEFT] = map_array[i + 1][j - 1];
				neighbourhood[LOWER_MIDDLE] = map_array[i + 1][j];
				neighbourhood[LOWER_RIGHT] = map_array[i + 1][j + 1];


				//lower horizontal
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& !neighbourhood[LOWER_LEFT] && !neighbourhood[LOWER_MIDDLE] && !neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_HORIZONTAL;
				else
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& !neighbourhood[LOWER_LEFT] && !neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_HORIZONTAL;
				else
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && !neighbourhood[LOWER_MIDDLE] && !neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_HORIZONTAL;
				else
					//nonessential for default map
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && !neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_HORIZONTAL;
				else


					//upper horizontal
				if (!neighbourhood[UPPER_LEFT] && !neighbourhood[UPPER_MIDDLE] && !neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_HORIZONTAL;
				else
				if (neighbourhood[UPPER_LEFT] && !neighbourhood[UPPER_MIDDLE] && !neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_HORIZONTAL;
				else
				if (!neighbourhood[UPPER_LEFT] && !neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_HORIZONTAL;
				else
					//nonessential for default map
				if (neighbourhood[UPPER_LEFT] && !neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_HORIZONTAL;
				else


					//big T
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& !neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && !neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_T_UP;
				else
					//nonessential for default map (15 next ifs)
				if (!neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& !neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_T_RIGHT;
				else
				if (!neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && !neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_T_DOWN;
				else
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && !neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && !neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_T_LEFT;
				else


					//left vertical
				if (!neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& !neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& !neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_VERTICAL;
				else
				if (!neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& !neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_VERTICAL;
				else
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& !neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& !neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_VERTICAL;
				else
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& !neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_VERTICAL;
				else

					//right vertical
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && !neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && !neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && !neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_VERTICAL;
				else
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && !neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && !neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_VERTICAL;
				else
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && !neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && !neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_VERTICAL;
				else
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && !neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_VERTICAL;
				else

					//L shaped tiles
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& !neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_LEFT_DOWN;
				else
				if (!neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_LEFT_UP;
				else
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && !neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_UP_RIGHT;
				else
				if (neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
					&& neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT]
					&& neighbourhood[LOWER_LEFT] && neighbourhood[LOWER_MIDDLE] && !neighbourhood[LOWER_RIGHT] == 1)
					map_with_tiles[i][j] = TILE_DOWN_RIGHT;
				else
					//end of nonessential for default map


				if (!neighbourhood[MIDDLE_LEFT] && !neighbourhood[MIDDLE_RIGHT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_VERTICAL;
				else
				if (neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT] && !neighbourhood[UPPER_MIDDLE] && !neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_HORIZONTAL;
				else
				if (neighbourhood[MIDDLE_LEFT] && !neighbourhood[MIDDLE_RIGHT] && !neighbourhood[UPPER_MIDDLE] && neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_LEFT_DOWN;
				else
				if (neighbourhood[MIDDLE_LEFT] && !neighbourhood[MIDDLE_RIGHT] && neighbourhood[UPPER_MIDDLE] && !neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_LEFT_UP;
				else
				if (!neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT] && neighbourhood[UPPER_MIDDLE] && !neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_UP_RIGHT;
				else
				if (!neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT] && !neighbourhood[UPPER_MIDDLE] && neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_DOWN_RIGHT;
				else
				if (!neighbourhood[MIDDLE_LEFT] && !neighbourhood[MIDDLE_RIGHT] && !neighbourhood[UPPER_MIDDLE] && neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_VERTICAL_END_UP;
				else
				if (neighbourhood[MIDDLE_LEFT] && !neighbourhood[MIDDLE_RIGHT] && !neighbourhood[UPPER_MIDDLE] && !neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_HORIZONTAL_END_RIGHT;
				else
				if (!neighbourhood[MIDDLE_LEFT] && !neighbourhood[MIDDLE_RIGHT] && neighbourhood[UPPER_MIDDLE] && !neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_VERTICAL_END_DOWN;
				else
				if (!neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT] && !neighbourhood[UPPER_MIDDLE] && !neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_HORIZONTAL_END_LEFT;
				else
				if (neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT] && !neighbourhood[UPPER_MIDDLE] && neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_T_UP;
				else
				if (neighbourhood[MIDDLE_LEFT] && !neighbourhood[MIDDLE_RIGHT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_T_RIGHT;
				else
				if (neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT] && neighbourhood[UPPER_MIDDLE] && !neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_T_DOWN;
				else
				if (!neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_T_LEFT;
				else
					//nonessential for default map
				if (neighbourhood[MIDDLE_LEFT] && neighbourhood[MIDDLE_RIGHT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[LOWER_MIDDLE] == 1)
					map_with_tiles[i][j] = TILE_ALL_SIDES;

			}
			else
				map_with_tiles[i][j] = TILE_FREE;
		}
	}

	map_with_tiles[12][10] = TILE_GATE_LEFT;
	map_with_tiles[12][11] = TILE_GATE_CENTER;
	map_with_tiles[12][12] = TILE_GATE_RIGHT;

	for (int i = 1; i < 28; i++)
	for (int j = 1; j < 22; j++)
		map_array[i][j] = map_with_tiles[i][j];
}

void Map::render_tile(int x, int y, SDL_Rect* clip)
{
	SDL_Rect tile_rect = { x, y, 8, 8 };
	SDL_RenderCopy(ren, tile_sprite_sheet, clip, &tile_rect);
}

Map::~Map()
{
	SDL_DestroyTexture(tile_sprite_sheet);
}
