#include "ghost.h"


Ghost::Ghost()
{
	ghost_id = 0;
	x = 8;
	y = 8;
	direction = 0;
	load_sprites();
	timer.start();
}


void Ghost::render(int x_offset, int y_offset)
{
	render_sprite(x - 4 + x_offset, y - 4 + y_offset, &sprite_clips[frame + direction * 2]);

	int timer_ticks = timer.ticks();
	if (timer_ticks >= frame_interval)
	{
		for (int i = 0; i < timer_ticks / frame_interval; i++)
		{
			frame += 1;
			if (frame >= frame_count)
				frame = 0;
		}
		timer.restart();
	}

}
void Ghost::set_coords(int x_axis, int y_axis, int direction_num)
{
	x = x_axis;
	y = y_axis;
	direction = direction_num;
}


void Ghost::load_sprites()
{
	int y = ghost_id * 64;
	sprite_sheet = load_image(ren, "res\\img\\ghosts.bmp", 255, 0, 255);

	for (int i = 0; i < 2; i++)
	{
		sprite_clips[i].x = i * 16;
		sprite_clips[i].y = y;
		sprite_clips[i].w = 16;
		sprite_clips[i].h = 16;
	}
	y += 16;
	for (int i = 2; i < 4; i++)
	{
		sprite_clips[i].x = (i - 2) * 16;
		sprite_clips[i].y = y;
		sprite_clips[i].w = 16;
		sprite_clips[i].h = 16;
	}
	y += 16;
	for (int i = 4; i < 6; i++)
	{
		sprite_clips[i].x = (i - 4) * 16;
		sprite_clips[i].y = y;
		sprite_clips[i].w = 16;
		sprite_clips[i].h = 16;
	}
	y += 16;
	for (int i = 6; i < 8; i++)
	{
		sprite_clips[i].x = (i - 6) * 16;
		sprite_clips[i].y = y;
		sprite_clips[i].w = 16;
		sprite_clips[i].h = 16;
	}
}

void Ghost::render_sprite(int x, int y, SDL_Rect* clip)
{
	SDL_Rect tile_rect = { x, y, 16, 16 };
	SDL_RenderCopy(ren, sprite_sheet, clip, &tile_rect);
}

Ghost::~Ghost()
{
	SDL_DestroyTexture(sprite_sheet);
	timer.stop();
}

