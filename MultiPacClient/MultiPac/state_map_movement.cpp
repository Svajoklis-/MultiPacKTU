#include "state_map_movement.h"

State_map_movement::State_map_movement()
{
	int **server_map = new int*[connection.mapheight];
	for (int i = 0; i < connection.mapheight; i++)
		server_map[i] = new int[connection.mapwidth];

	int *buffer = new int[connection.mapheight * connection.mapwidth];

	connection.new_game(buffer);
	

	for (int i = 0; i < connection.mapheight; i++)
	{
		for (int j = 0; j < connection.mapwidth; j++)
		{
			server_map[i][j] = buffer[i * connection.mapwidth + j];
		}
	}
	
	map.load_from_memory(server_map);

	for (int i = 0; i < connection.mapheight; i++)
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
			case SDLK_UP:
				if (!dir_sent)
				{
					connection.going_top();
					dir_sent = true;
				}
				break;
			case SDLK_DOWN:
				if (!dir_sent)
				{
					connection.going_bottom();
					dir_sent = true;
				}
				break;
			case SDLK_LEFT:
				if (!dir_sent)
				{
					connection.going_left();
					dir_sent = true;
				}
				break;
			case SDLK_RIGHT:
				if (!dir_sent)
				{
					connection.going_right();
					dir_sent = true;
				}
				break;
			}
		}

		if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
			case SDLK_DOWN:
			case SDLK_LEFT:
			case SDLK_RIGHT:
				if (dir_sent)
				{
					connection.dir_reset();
					dir_sent = false;
				}
				break;
			}
		}
	}

}

void State_map_movement::logic()
{
	//connection.get_coords(coords, &coord_count, &ping);
	Server_connection::State_Packet data;			//cia visi duomenys gal dar visu neatsiunci bet bus
	connection.get_state_packet(&data, &ping);		//cia naujas gavimas kiti bus deprecated
	coord_count = data.player_count;
	for (int i = 0; i < coord_count; i++){			//cia kad neapsiverktu kita tavo kodo dalis susitvarkysi
		coords[i] = data.players[i];
	}

	for (int i = 0; i < coord_count; i++)
	{
		pacman[i].set_coords(coords[i].x, coords[i].y, coords[i].way);
	}
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