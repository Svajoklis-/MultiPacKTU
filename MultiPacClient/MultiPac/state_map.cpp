#include "state_map.h"

State_map::State_map()
{
	x = 8;
	y = 8;
	degrees = 0;
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
		degrees = 0;
	else
	if (x < lastx)
		degrees = 180;
	else
	if (y > lasty)
		degrees = 90;
	else
	if (y < lasty)
		degrees = 270;

}

void State_map::render()
{
	map.render();
	pacman.render(x,y, degrees);
	
}


State_map::~State_map()
{

}
