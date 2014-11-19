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

	items.load_from_memory(server_map);
	//map.load_from_memory(server_map);

	for (int i = 0; i < connection.mapheight; i++)
		delete[] server_map[i];

	delete[] server_map;

	delete[] buffer;


	snd_chomping = Mix_LoadWAV("res\\snd\\chomping.wav");
	snd_pause = Mix_LoadWAV("res\\snd\\pause.wav");

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
			case SDLK_a:
				if (!chomping) {
					chomp_channel = Mix_PlayChannel(-1, snd_chomping, -1);
					chomping = true;
				}
				break;
			case SDLK_s:
				if (chomping)
				{
					Mix_FadeOutChannel(chomp_channel, 1000);
					chomping = false;
				}
				break;
			case SDLK_d:
				Mix_PlayChannel(-1, snd_pause, 0);
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
	//connection.get_coords(coords, &coord_count, &ping);
				//cia visi duomenys gal dar visu neatsiunci bet bus
	connection.get_state_packet(&data, &ping);		//cia naujas gavimas kiti bus deprecated

	// ------------------------- LOAD MAP

	int **server_map = new int*[connection.mapheight];
	for (int i = 0; i < connection.mapheight; i++)
		server_map[i] = &data.map[i][0];

	items.load_from_memory(server_map);
	map.load_from_memory(server_map);

	delete[] server_map;
	
	// -------------------------

	coord_count = data.player_count;
	for (int i = 0; i < coord_count; i++){			//cia kad neapsiverktu kita tavo kodo dalis susitvarkysi
		coords[i] = data.players[i];
	}

	for (int i = 0; i < coord_count; i++)
	{
		pacman[i].set_coords(coords[i].x, coords[i].y, coords[i].way);
	}

	if (score.get_score() < data.score) Mix_PlayChannel(-1, snd_pause, 0);

	score.set_score(data.score);
}

void State_map_movement::render()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	map.render(10, 13);
	items.render(10, 13);

	for (int i = 0; i < coord_count; i++)
		pacman[i].render(10, 13);

	score.render(0, 0);

	SDL_RenderPresent(ren);
}

State_map_movement::~State_map_movement()
{
	connection.disconnect();
}