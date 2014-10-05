#include <SDL.h>

using namespace std;

#include "game_state.h"

#include "globals.h"

#ifndef H_STATE_TEST
#define H_STATE_TEST

class State_test : public Game_state
{
public:
	State_test();
	void events();
	void logic();
	void render();

	static int action(void *ptr);
	~State_test();
};

#endif // H_BRANCH_TEST
