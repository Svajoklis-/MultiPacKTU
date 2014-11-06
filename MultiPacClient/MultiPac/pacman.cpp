#include "pacman.h"

Pacman::Pacman()
{
	x = 8;
	y = 8;
	direction = 0;
	load_sprites();
	timer.start();

	stop_timer.start();
}


void Pacman::render(int x_offset, int y_offset)
{
	
	render_sprite(x - 4 + x_offset, y - 4 + y_offset, &sprite_clips[frame + direction * 4]);

	int timer_ticks = timer.ticks();
	if (timer_ticks >= frame_interval)
	{
		if (stop_timer.ticks() < 20)
		{
			for (int i = 0; i < timer_ticks / frame_interval; i++)
			{
				frame += 1;
				if (frame >= frame_count)
				{
					frame = 0;
				}
			}
			timer.restart();
		}
	}

}

void Pacman::set_coords(int x_axis, int y_axis, int direction_num)
{
	if (x_axis == x && y_axis == y)
	{
		
	}
	else
	{
		stop_timer.restart();
	}

	x = x_axis;
	y = y_axis;
	direction = direction_num;
}


void Pacman::load_sprites()
{
	int y = 0;
	sprite_sheet = load_image(ren, "res\\img\\pacman.bmp", 255, 0, 255);

	for (int i = 0; i < 3; i++)
	{
		sprite_clips[i].x = i * 16;
		sprite_clips[i].y = y;
		sprite_clips[i].w = 16;
		sprite_clips[i].h = 16;
	}
	sprite_clips[3] = sprite_clips[1];
	y += 16;
	for (int i = 4; i < 7; i++)
	{
		sprite_clips[i].x = (i-4) * 16;
		sprite_clips[i].y = y;
		sprite_clips[i].w = 16;
		sprite_clips[i].h = 16;
	}
	sprite_clips[7] = sprite_clips[5];
	y += 16;
	for (int i = 8; i < 11; i++)
	{
		sprite_clips[i].x = (i - 8) * 16;
		sprite_clips[i].y = y;
		sprite_clips[i].w = 16;
		sprite_clips[i].h = 16;
	}
	sprite_clips[11] = sprite_clips[9];
	y += 16;
	for (int i = 12; i < 15; i++)
	{
		sprite_clips[i].x = (i - 12) * 16;
		sprite_clips[i].y = y;
		sprite_clips[i].w = 16;
		sprite_clips[i].h = 16;
	}
	sprite_clips[15] = sprite_clips[13];
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