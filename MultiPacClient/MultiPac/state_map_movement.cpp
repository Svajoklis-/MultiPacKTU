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

	connection.ready();
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
			}
		}
	}

	const Uint8 *keyb_state = SDL_GetKeyboardState(NULL);

	int now = keyb_state[SDL_SCANCODE_UP] | keyb_state[SDL_SCANCODE_DOWN] | keyb_state[SDL_SCANCODE_LEFT] | keyb_state[SDL_SCANCODE_RIGHT];

	// -1 no, 0 up, 1 right, 2 down, 3 left
	int send_key = -1;

	if (now == 0) 
		send_key = -1;
	else if (keyb_state[SDL_SCANCODE_UP] == 1)
		send_key = 0;
	else if (keyb_state[SDL_SCANCODE_RIGHT] == 1)
		send_key = 1;
	else if (keyb_state[SDL_SCANCODE_DOWN] == 1)
		send_key = 2;
	else if (keyb_state[SDL_SCANCODE_LEFT] == 1)
		send_key = 3;

	if (last_sent != send_key)
	{
		switch (send_key)
		{
		case -1:
			connection.dir_reset();
			break;
		case 0:
			connection.going_top();
			break;
		case 1:
			connection.going_right();
			break;
		case 2:
			connection.going_bottom();
			break;
		case 3:
			connection.going_left();
			break;
		}

		last_sent = send_key;
	}
}

void State_map_movement::logic()
{
	connection.get_coords(coords, &coord_count, &ping);

	for (int i = 0; i < coord_count; i++)
	{
		pacman[i].set_coords(coords[i].x, coords[i].y, coords[i].way);
	}

	int scorei;
	connection.get_score(&scorei);
	score.set_score(scorei);
}

void State_map_movement::render()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	map.render(0, 0);

	for (int i = 0; i < coord_count; i++)
		pacman[i].render(0, 0);

	score.render(0, 0);

	SDL_RenderPresent(ren);
}

State_map_movement::~State_map_movement()
{
	connection.exit_game();
}