#include "state_map_movement.h"

State_map_movement::State_map_movement()
{
	int **server_map = new int *[connection.dim_x];
	for (int i = 0; i < connection.dim_x; i++)
		server_map[i] = new int[connection.dim_y];

	connection.new_game(server_map);
	
	map.load_from_memory(server_map);

	for (int i = 0; i < connection.dim_x; i++)
		delete[] server_map[i];

	delete[] server_map;
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
	map.render();

	pacman.render();
}

State_map_movement::~State_map_movement()
{

}