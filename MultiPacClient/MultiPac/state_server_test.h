#include <SDL.h>
#include <string>

using namespace std;

#include "game_state.h"
#include "globals.h"
#include "timer.h"

#ifndef H_STATE_SERVER_TEST
#define H_STATE_SERVER_TEST

class State_server_test : public Game_state
{
public:
	State_server_test();
	void events();
	void logic();
	void render();

	~State_server_test();

private:
};

#endif // H_STATE_SERVER_TEST