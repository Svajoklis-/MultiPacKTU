#include "state_server_test.h"

State_server_test::State_server_test()
{

}

void State_server_test::events()
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

void State_server_test::logic()
{

}

void State_server_test::render()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	//SDL_QueryTexture(logo, nullptr, nullptr, &tx_w, &tx_h);
	// x, y, w, h
	//dst_rect = { (scr_w - tx_w) / 2, 40, tx_w, tx_h };
	//SDL_RenderCopy(ren, logo, nullptr, &dst_rect);

	SDL_RenderPresent(ren);
}

State_server_test::~State_server_test()
{

}