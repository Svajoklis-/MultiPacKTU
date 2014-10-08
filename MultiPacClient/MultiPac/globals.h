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

// main window
extern SDL_Window *win;

// main renderer
extern SDL_Renderer *ren;

// window texture
extern SDL_Texture *win_tx;

// standard NES dimensions
const int scr_w = 256;
const int scr_h = 240;
const int scr_scale = 2;

extern SDL_Rect scr_rect;
extern SDL_Rect win_rect;

// used to render text to screen
extern Font_renderer *font_renderer;

const int scr_fps = 100;

// loads an image to SDL_Texture
// second version loads an image with single color alpha channel (e.g. magenta background)
SDL_Texture* load_image(SDL_Renderer* ren, std::string name);
SDL_Texture* load_image(SDL_Renderer* ren, std::string name, int r, int g, int b);

#endif // H_GLOBALS



