#include "pacman.h"

Pacman::Pacman()
{
	load_sprites();
	timer.start();
}


void Pacman::render()
{

	for (int i = 2; i < 9; i++)
	for (int j = 2; j < 9; j++)
		render_sprite((j - 1) * 16 - 12, (i - 1) * 16 - 12 , &sprite_clips[timer.ticks() / 75 % 4]);
}



void Pacman::load_sprites()
{

	sprite_sheet = load_image(ren, "res\\img\\pacman.bmp", 255, 0, 255);

	for (int i = 0; i < 3; i++)
	{
		sprite_clips[i].x = i * 16;
		sprite_clips[i].y = 0;
		sprite_clips[i].w = 16;
		sprite_clips[i].h = 16;
	}
	sprite_clips[3] = sprite_clips[1];
	

}
void Pacman::render_sprite(int x, int y, SDL_Rect* clip)
{
	SDL_Rect tile_rect = { x, y, 16, 16 };
	SDL_RenderCopy(ren, sprite_sheet, clip, &tile_rect);
}


Pacman::~Pacman()
{
	SDL_DestroyTexture(sprite_sheet);
	timer.stop();
}