#include <SDL.h>

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
	bool continuing = false;
};

#endif // H_BRANCH_MENU