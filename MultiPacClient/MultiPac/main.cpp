/*
*
*	Main file. It runs and controls GameStates, initializes and deinitializes SDL.
*
*/

#include <SDL.h>
#include "globals.h"
#include "game_state.h"
#include "state_test.h"

#include "timer.h"

int init();
void quit();

game_states state = st_null;
Game_state *current_state;

Timer timer;

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return 1;

	if (init() != 0)
		return 2;

	current_state = new State_test();

	while (state != st_exit)
	{
		timer.restart();

		current_state->events();
		current_state->logic();
		current_state->render();

		state = current_state->get_state();

		if (state != st_null)
		{
			switch (state)
			{
			case st_exit:
				delete current_state;
				break;
			default:
				state = st_null;
				break;
			}
		}

		if (timer.ticks() < 1000 / scr_fps)
			SDL_Delay((1000 / scr_fps) - timer.ticks());
	}

	quit();

	return 0;

	return 0;
}

int init()
{
	win = SDL_CreateWindow("MultiPac", 100, 100, scr_w, scr_h,
		SDL_WINDOW_SHOWN);

	if (win == nullptr)
		return 1;

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	if (ren == nullptr)
		return 1;

	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

	return 0;
}

void quit()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	SDL_Quit();
}
