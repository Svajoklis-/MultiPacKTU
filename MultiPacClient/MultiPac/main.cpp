/*
*
*	Main file. It runs and controls GameStates, initializes and deinitializes SDL.
*
*/

#include <SDL.h>
#include "globals.h"
#include "game_state.h"
#include "state_test.h"
#include "state_intro.h"
#include "state_menu.h"
#include "state_server_test.h"
#include "state_map.h"

#include "timer.h"

int init();
void quit();

game_states state = st_null;
Game_state *current_state;

// used by frame limiter
Timer timer;

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return 1;

	if (init() != 0)
		return 2;

	// you can set initial state here
	current_state = new State_intro();

	while (state != st_exit)
	{
		timer.restart();

		current_state->events();
		current_state->logic();

		// states render to window texture
		SDL_SetRenderTarget(ren, win_tx);
		current_state->render();

		// main loop scales rendered texture to window
		SDL_SetRenderTarget(ren, nullptr);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, win_tx, &scr_rect, &win_rect);
		SDL_RenderPresent(ren);

		// check if state hasn't changed
		state = current_state->get_state();

		if (state != st_null)
		{
			switch (state)
			{
			case st_exit:
				delete current_state;
				break;
			case st_intro:
				delete current_state;
				current_state = new State_intro();
				break;
			case st_menu:
				delete current_state;
				current_state = new State_menu();
				break;
			case st_server_test:
				delete current_state;
				current_state = new State_server_test();
				break;
			case st_map:
				delete current_state;
				current_state = new State_map();
			default:
				state = st_null;
				break;
			}
		}

		// delay if frame finished fast enough
		if (timer.ticks() < 1000 / scr_fps)
			SDL_Delay((1000 / scr_fps) - timer.ticks());
	}

	quit();

	return 0;
}

int init()
{
	win = SDL_CreateWindow("MultiPac", 100, 100, scr_w * scr_scale, scr_h * scr_scale,
		SDL_WINDOW_SHOWN);

	if (win == nullptr)
		return 1;

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_TARGETTEXTURE);
	//SDL_RenderSetLogicalSize(ren, scr_w, scr_h);
	
	win_tx = SDL_CreateTexture(ren, 0, SDL_TEXTUREACCESS_TARGET, scr_w, scr_h);

	if (ren == nullptr)
		return 1;

	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

	font_renderer = new Font_renderer("res\\img\\font.bmp");

	return 0;
}

void quit()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	delete font_renderer;

	SDL_Quit();
}
