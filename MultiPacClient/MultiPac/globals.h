/*
*
*	Global program variables.
*	If you need to define a global pointer define it with extern and initialize it in globals.cpp
*
*/

#include <SDL.h>
#include <string>

#ifndef H_GLOBALS
#define H_GLOBALS

extern SDL_Window *win;
extern SDL_Renderer *ren;

// standard NES dimensions
const int scr_w = 256;
const int scr_h = 228;

extern SDL_Rect scr_rect;

const int scr_fps = 5000;

// loads an image to SDL_Texture
// second version loads an image with single color alpha channel (eg. magenta background)
SDL_Texture* load_image(SDL_Renderer* ren, std::string name);
SDL_Texture* load_image(SDL_Renderer* ren, std::string name, int r, int g, int b);

#endif // H_GLOBALS



