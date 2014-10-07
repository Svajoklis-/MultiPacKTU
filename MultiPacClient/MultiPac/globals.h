/*
*
*	Global program variables.
*	If you need to define a global pointer define it with extern and initialize it in globals.cpp
*
*/

#include <SDL.h>
#include <string>
#include "font_renderer.h"

#ifndef H_GLOBALS
#define H_GLOBALS

extern SDL_Window *win;
extern SDL_Renderer *ren;
extern SDL_Texture *win_tx;

// standard NES dimensions
const int scr_w = 256;
const int scr_h = 240;
const int scr_scale = 2;

extern SDL_Rect scr_rect;
extern SDL_Rect win_rect;

extern Font_renderer *font_renderer;

const int scr_fps = 5000;

// loads an image to SDL_Texture
// second version loads an image with single color alpha channel (eg. magenta background)
SDL_Texture* load_image(SDL_Renderer* ren, std::string name);
SDL_Texture* load_image(SDL_Renderer* ren, std::string name, int r, int g, int b);

#endif // H_GLOBALS



