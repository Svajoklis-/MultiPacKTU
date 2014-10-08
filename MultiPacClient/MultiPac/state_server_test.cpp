#include "state_server_test.h"

#include <sstream>

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
	ping_timer.start();
	connection.get_coords(&server_num);
	ping = ping_timer.ticks();
	ping_timer.stop();
}

void State_server_test::render()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	std::stringstream text;
	int x_offset = 20;
	int y_offset = 20;

	text.str("");
	text << "PING :" << ping << " MS";

	font_renderer->render(text.str(),
		x_offset,
		y_offset);

	y_offset += font_renderer->height(text.str());

	text.str("");
	text << "MAGIC NUMBER: " << server_num;

	font_renderer->render(text.str(),
		x_offset,
		y_offset);

	y_offset += font_renderer->height(text.str());

	SDL_RenderPresent(ren);
}

State_server_test::~State_server_test()
{

}