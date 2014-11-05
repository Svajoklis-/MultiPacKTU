#include "state_map.h"
#include <string>

State_map::State_map()
{
	map.read_from_file();
	map.assign_tiles();
	x = 8;
	y = 8;
	direction = 0;
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
			case SDLK_UP:
				lasty = y;
				lastx = x;
				y -= 4;
				break;
			case SDLK_DOWN:
				lasty = y;
				lastx = x;
				y += 4;
				break;
			case SDLK_LEFT:
				lasty = y;
				lastx = x;
				x -= 4;
				break;
			case SDLK_RIGHT:
				lasty = y;
				lastx = x;
				x += 4;
				break;
			}
		}
	}

}

void State_map::logic()
{
	if (x > lastx)
		direction = 0;
	else
	if (x < lastx)
		direction = 2;
	else
	if (y > lasty)
		direction = 1;
	else
	if (y < lasty)
		direction = 3;

	pacman.set_coords(x, y, direction);
}

void State_map::render()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);


	map.render(0, 0);
	
	pacman.render(0, 0);

	score.render(0, 0);

	SDL_RenderPresent(ren);

}


State_map::~State_map()
{

}
