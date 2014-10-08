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

	Timer fun;

	int menu_item_count = 2;
	string *menu_items;
	int longest_menu_element = 0;
	int selected = 0;
};

#endif // H_STATE_MENU