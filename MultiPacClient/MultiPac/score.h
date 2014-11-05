#pragma once
#include <SDL.h>
#include "globals.h"

using namespace std;
class Score
{
public:
	Score();
	void render(int x_offset, int y_offset);
	void set_score(int sc);
	int get_score();
	~Score();

private:
	int score;

};

