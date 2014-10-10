#include "state_map.h"

State_map::State_map()
{
	for (int i = 0; i < 29; i++)
		for (int j = 0; j < 23; j++)
			map_array[i][j] = 0;
	read_from_file();
	load_tiles();
	assign_tiles();
}

void State_map::events()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			state = st_exit;
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				state = st_menu;
				break;
			}
		}
	}

}

void State_map::logic()
{

}

void State_map::render()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	for (int i = 1; i < 28; i++)
		for (int j = 1; j < 22; j++)
			render_tile((j - 1) * 8, (i - 1) * 8, &tile_sprite_clips[map_array[i][j]]);
	SDL_RenderPresent(ren);
}

void State_map::read_from_file()
{

	ifstream file;
	file.open("res\\map\\map.txt");
	for (int i = 1; i < 28; i++)
		for (int j = 1; j < 22; j++)
			file >> map_array[i][j];
		file.close();

}

void State_map::load_tiles()
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

}

void State_map::assign_tiles()
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
				if(neighbourhood[UPPER_LEFT] && neighbourhood[UPPER_MIDDLE] && neighbourhood[UPPER_RIGHT]
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
	for (int i = 1; i < 28; i++)
		for (int j = 1; j < 22; j++)
			map_array[i][j] = map_with_tiles[i][j];
}

void State_map::render_tile(int x, int y, SDL_Rect* clip)
{
	SDL_Rect tile_rect = { x, y, 8, 8 };
	SDL_RenderCopy(ren, tile_sprite_sheet, clip, &tile_rect);
}

State_map::~State_map()
{
	SDL_DestroyTexture(tile_sprite_sheet);
}
