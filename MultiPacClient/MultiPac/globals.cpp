#include "globals.h"

SDL_Window *win = nullptr;
SDL_Renderer *ren = nullptr;
SDL_Texture *win_tx = nullptr;

SDL_Rect scr_rect{ 0, 0, scr_w, scr_h };
SDL_Rect win_rect{ 0, 0, scr_w * scr_scale, scr_h * scr_scale };
Font_renderer *font_renderer = nullptr;

char *g_connectionstring = nullptr;
int g_fullscreen = 0;
int g_mute = 0;

SDL_Texture* load_image(SDL_Renderer* ren, std::string name)
{
	SDL_Texture* ret;
	SDL_Surface* load = SDL_LoadBMP(name.c_str());
	ret = SDL_CreateTextureFromSurface(ren, load);
	SDL_FreeSurface(load);

	return ret;
};

SDL_Texture* load_image(SDL_Renderer* ren, std::string name, int r, int g, int b)
{
	SDL_Texture* ret;
	SDL_Surface* load = SDL_LoadBMP(name.c_str());
	SDL_SetColorKey(load, SDL_TRUE, SDL_MapRGB(load->format, r, g, b));
	ret = SDL_CreateTextureFromSurface(ren, load);
	SDL_FreeSurface(load);

	return ret;
}



