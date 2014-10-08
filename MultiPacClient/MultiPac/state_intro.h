#include <SDL.h>
#include <string>

using namespace std;

#include "game_state.h"
#include "globals.h"
#include "timer.h"

#ifndef H_STATE_INTRO
#define H_STATE_INTRO

class State_intro : public Game_state
{
public:
	State_intro();
	void events();
	void logic();
	void render();

	~State_intro();

private:
	SDL_Texture *logo;
	SDL_Texture *team_logo;

	Timer blink;
	int blink_interval = 1000;
	bool blink_on = true;
	std::string blink_message;

	bool continuing = false;

	Timer next_timer;
	int next_delay = 2000;
};

#endif // H_STATE_INTRO