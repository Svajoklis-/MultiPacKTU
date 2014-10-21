#include "state_map.h"

State_map::State_map()
{

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
	map.render();
	
}


State_map::~State_map()
{

}
