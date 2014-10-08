#include "state_menu.h"

#include <cstdio>
#include <sstream>

State_menu::State_menu()
{
	logo = load_image(ren, "res\\img\\logo.bmp");

	team_logo = load_image(ren, "res\\img\\team_logo.bmp");

	fun.start();

	menu_items = new string[menu_item_count];
	menu_items[0] = "SERVER TEST";
	menu_items[1] = "MAP RENDER";
}

void State_menu::events()
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
				break;
			}
		}
	}
}

void State_menu::logic()
{

}

void State_menu::render()
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

	int item_offset = 0;
	for (int i = 0; i < menu_item_count; i++)
	{
		font_renderer->render(menu_items[i],
			(scr_w - font_renderer->width(menu_items[i])) / 2,
			scr_h - font_renderer->height(menu_items[i]) - 120 + item_offset);

		item_offset += font_renderer->height(menu_items[i]) + 5;
	}

	SDL_RenderPresent(ren);
}

State_menu::~State_menu()
{
	SDL_DestroyTexture(logo);
	SDL_DestroyTexture(team_logo);

	delete[] menu_items;
}