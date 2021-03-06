#include "state_intro.h"

#include <cstdio>

State_intro::State_intro()
{
	logo = load_image(ren, "res\\img\\logo.bmp");

	team_logo = load_image(ren, "res\\img\\team_logo.bmp");

	blink.start();

	blink_message = "PRESS ENTER";
}

void State_intro::events()
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
			case SDLK_RETURN:
				continuing = true;
				next_timer.start();
				blink_interval = 100;
				blink_message = "LET'S PLAY!";
				break;
			}
		}
	}
}

void State_intro::logic()
{
	if (blink.ticks() > blink_interval)
	{
		blink_on = !blink_on;
		blink.restart();
	}

	if (next_timer.ticks() > next_delay)
	{
		state = st_menu;
	}
}

void State_intro::render()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	SDL_Rect dst_rect;
	int tx_w, tx_h;

	SDL_QueryTexture(logo, nullptr, nullptr, &tx_w, &tx_h);
	// x, y, w, h
	dst_rect = { (scr_w - tx_w) / 2, 40, tx_w, tx_h };
	SDL_RenderCopy(ren, logo, nullptr, &dst_rect);

	SDL_QueryTexture(team_logo, nullptr, nullptr, &tx_w, &tx_h);
	dst_rect = { (scr_w - tx_w) / 2, scr_h - tx_h - 45, tx_w, tx_h };
	SDL_RenderCopy(ren, team_logo, nullptr, &dst_rect);

	font_renderer->render("@ GHOSTS, 2014",
		(scr_w - font_renderer->width("@ GHOSTS, 2014")) / 2,
		scr_h - font_renderer->height("@ GHOSTS, 2014") - 20);
	
	if (blink_on)
		font_renderer->render(blink_message,
		(scr_w - font_renderer->width(blink_message)) / 2,
		scr_h - font_renderer->height(blink_message) - 120);

	SDL_RenderPresent(ren);
}

State_intro::~State_intro()
{
	SDL_DestroyTexture(logo);
	SDL_DestroyTexture(team_logo);
}