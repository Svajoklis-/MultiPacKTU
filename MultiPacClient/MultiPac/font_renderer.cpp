#include "font_renderer.h"

#include <cstdio>

Font_renderer::Font_renderer(std::string font_bmp)
{
	font = load_image(ren, font_bmp);
	if (!font)
	{
		printf("Font failed to load...\n");
	}

	int tx_w, tx_h;
	SDL_QueryTexture(font, nullptr, nullptr, &tx_w, &tx_h);

	chr_w = tx_w / 16;
	chr_h = tx_h / 4;
}

int Font_renderer::width(std::string text)
{
	return text.length() * chr_w;
}

int Font_renderer::height(std::string text)
{
	return chr_h;
}

void Font_renderer::render(std::string text, int x, int y)
{
	int chr;
	SDL_Rect from, to;
	for (unsigned i = 0; i < text.length(); i++)
	{
		chr = text[i];
		if (chr < 32 || chr > 95)
		{
			chr = 32;
		}
		
		from = { ((chr - 32) % 16) * chr_w, ((chr - 32) / 16) * chr_h, chr_w, chr_h };
		to = { x + i * chr_w, y, chr_w, chr_h };

		SDL_RenderCopy(ren, font, &from, &to);
	}
}