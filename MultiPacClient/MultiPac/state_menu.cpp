#include "state_menu.h"

#include <cstdio>
#include <sstream>

State_menu::State_menu()
{
	logo = load_image(ren, "res\\img\\logo.bmp");

	team_logo = load_image(ren, "res\\img\\team_logo.bmp");

	fun.start();

	menu_items = new string[menu_item_count];
	menu_items[0] = "REPLAY INTRO";
	menu_items[1] = "MAP RENDER DEMO";
	menu_items[2] = "MAP MOVEMENT TEST";

	for (int i = 0; i < menu_item_count; i++)
	{
		if (menu_items[i].length() > longest_menu_element)
			longest_menu_element = menu_items[i].length();
	}
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
			case SDLK_UP:
				selected -= 1;
				if (selected < 0)
				{
					selected = menu_item_count - 1;
				}
				break;

			case SDLK_DOWN:
				selected += 1;
				if (selected >= menu_item_count)
				{
					selected = 0;
				}
				break;

			case SDLK_RETURN:
				switch(selected)
				{
				case 0:
					state = st_intro;
					break;
				case 1:
					state = st_map;
					break;
				case 2:
					state = st_map_movement;
					break;
				default:
					break;
				}
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
	int x_offset = (scr_w - longest_menu_element * (font_renderer->width(" ") + 1) + 3) / 2;
	for (int i = 0; i < menu_item_count; i++)
	{

		if (i == selected)
		{
			font_renderer->render(">",
				x_offset,
				scr_h - font_renderer->height(">") - 120 + item_offset);
		}

		font_renderer->render(menu_items[i],
			x_offset + font_renderer->width(" ") + 3,
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