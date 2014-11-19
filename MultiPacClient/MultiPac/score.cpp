#include "score.h"


Score::Score()
{
	score = 0;
	lives = 3;
}

void Score::render(int x_offset, int y_offset)
{
	string title = "SCORE";
	int char_width = font_renderer->width(" ");
	int char_height = font_renderer->height(" ");
	//int map_width = 21 * 8;
	int map_width = 200;

	/*font_renderer->render(title, 
		map_width + char_width + x_offset,
		char_height * 2 + y_offset);*/

	font_renderer->render(title,
		205,
		10);

	font_renderer->render(to_string(score),
		scr_w - 11 - font_renderer->width(to_string(score)) + x_offset,
		char_height * 3 + y_offset);



	title = "LIVES";
	font_renderer->render(title,
		205,
		58);

	font_renderer->render(to_string(lives),
		scr_w - 11 - font_renderer->width(to_string(score)) + x_offset,
		char_height * 9 + y_offset);

}
void Score::set_score(int sc)
{
	score = sc;
}
void Score::set_score(int sc, int lv)
{
	score = sc;
	lives = lv;
}
int Score::get_score()
{
	return score;
}

Score::~Score()
{
}
