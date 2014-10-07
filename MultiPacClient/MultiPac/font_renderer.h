class Font_renderer;

#ifndef H_FONT_RENDERER
#define H_FONT_RENDERER

#include "globals.h"
#include <SDL.h>

class Font_renderer
{
public:
	Font_renderer(std::string font_bmp);
	int width(std::string text);
	int height(std::string text);
	void render(std::string text, int x, int y);

private:
	SDL_Texture *font;

	int chr_w, chr_h;
};

#endif