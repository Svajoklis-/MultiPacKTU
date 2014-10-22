#include "state_map_movement.h"

State_map_movement::State_map_movement()
{
	int **server_map = new int*[connection.dim_x];
	for (int i = 0; i < connection.dim_x; i++)
		server_map[i] = new int[connection.dim_y];

	int *buffer = new int[connection.dim_x * connection.dim_y];

	connection.new_game(buffer);

	for (int i = 0; i < connection.dim_x; i++)
	{
		for (int j = 0; j < connection.dim_y; j++)
		{
			server_map[i][j] = buffer[i * connection.dim_y + j];
		}
	}
	
	map.load_from_memory(server_map);

	for (int i = 0; i < connection.dim_x; i++)
		delete[] server_map[i];

	delete[] server_map;

	delete[] buffer;
}

void State_map_movement::events()
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
			case SDLK_UP:
				connection.going_top();
				break;
			case SDLK_DOWN:
				connection.going_bottom();
				break;
			case SDLK_LEFT:
				connection.going_left();
				break;
			case SDLK_RIGHT:
				connection.going_right();
				break;
			}
		}
	}

}

void State_map_movement::logic()
{
	connection.get_coords(coords, &coord_count, &ping);
	pacman.set_coords(coords[0].x, coords[0].y, coords[0].way);
}

void State_map_movement::render()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	map.render();

	pacman.render();

	SDL_RenderPresent(ren);
}

State_map_movement::~State_map_movement()
{

}