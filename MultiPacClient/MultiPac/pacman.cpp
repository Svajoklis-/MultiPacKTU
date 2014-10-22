#include "pacman.h"

Pacman::Pacman()
{
	load_sprites();
	timer.start();
}


void Pacman::render(int x, int y, int degrees)
{
	

	


	render_sprite(x - 4, y - 4, &sprite_clips[timer.ticks() / 75 % 4], degrees);
	


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
void Pacman::render_sprite(int x, int y, SDL_Rect* clip, double angle)
{
	SDL_Rect tile_rect = { x, y, 16, 16 };

	SDL_RenderCopyEx(ren, sprite_sheet, clip, &tile_rect, angle, NULL, SDL_FLIP_NONE);
	//SDL_RenderCopy(ren, sprite_sheet, clip, &tile_rect);
}


Pacman::~Pacman()
{
	SDL_DestroyTexture(sprite_sheet);
	timer.stop();
}