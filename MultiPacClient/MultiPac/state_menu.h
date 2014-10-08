#include <SDL.h>
#include <string>

using namespace std;

#include "game_state.h"
#include "globals.h"
#include "timer.h"

#ifndef H_STATE_MENU
#define H_STATE_MENU

class State_menu : public Game_state
{
public:
	State_menu();
	void events();
	void logic();
	void render();

	~State_menu();

private:
	SDL_Texture *logo;
	SDL_Texture *team_logo;

	Timer blink;
	int blink_interval = 1000;
	bool blink_on = true;
	std::string blink_message;

	bool continuing = false;

	Timer alpha;
	int cover_alpha = 0;
	int alpha_delay = 2000;
};

#endif // H_BRANCH_MENU