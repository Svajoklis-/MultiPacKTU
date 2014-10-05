#include "state_test.h"

#include <cstdlib>

State_test::State_test()
{

}

void State_test::events()
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
				state = st_exit;
				break;
			}
		}
	}
}

void State_test::logic()
{

}

void State_test::render()
{
	SDL_SetRenderDrawColor(ren, rand() % 256, rand() % 256, rand() % 256, rand() % 256);
	SDL_RenderFillRect(ren, &scr_rect);

	SDL_RenderPresent(ren);
}

State_test::~State_test()
{

}