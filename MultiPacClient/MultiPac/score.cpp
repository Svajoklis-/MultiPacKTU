#include "score.h"


Score::Score()
{
	score = 0;
}

void Score::render(int x_offset, int y_offset)
{
	string title = "HI-SCORE";
	int char_width = font_renderer->width(" ");
	int char_height = font_renderer->height(" ");
	int map_width = 21 * 8;

	font_renderer->render(title, 
		map_width + char_width + x_offset,
		char_height * 2 + y_offset);

	font_renderer->render(to_string(score),
		map_width + font_renderer->width(title) - font_renderer->width(to_string(score)) + x_offset,
		char_height * 4 + y_offset);

}
void Score::set_score(int sc)
{
	score = sc;
}
int Score::get_score()
{
	return score;
}

Score::~Score()
{
}
