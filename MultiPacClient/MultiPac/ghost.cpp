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
	if (ghost_id < 4)
	{
		render_sprite(x - 4 + x_offset, y - 4 + y_offset, &sprite_clips[frame + direction * 2 + ghost_id * 8]);
	}
	else
	{
		if (ghost_id == 4)
		{
			render_blink_sprite(x - 4 + x_offset, y - 4 + y_offset, &blink_clips[frame]);
		}
		if (ghost_id == 5)
		{
			render_blink_sprite(x - 4 + x_offset, y - 4 + y_offset, &blink_clips[frame + 2]);
		}
		if (ghost_id == 6)
		{
			render_eyes_sprite(x - 4 + x_offset, y - 4 + y_offset, &eyes_clips[direction]);
		}
	}

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

void Ghost::set_ghost_id(int id)
{
	ghost_id = id;
}





void Ghost::load_sprites()
{
	int y = -16;
	sprite_sheet = load_image(ren, "res\\img\\ghosts.bmp", 255, 0, 255);
	int counter = 0;

	for (int i = 0; i < 32; i++)
	{
		if (counter % 2 == 0)
		{
			sprite_clips[i].x = (i - counter) * 16;
			y += 16;
		}
		else
			sprite_clips[i].x = (i - counter + 1) * 16;
		sprite_clips[i].y = y;
		sprite_clips[i].w = 16;
		sprite_clips[i].h = 16;
		counter++;
	}

	blink_sheet = load_image(ren, "res\\img\\blinking.bmp", 255, 0, 255);
    y = -16;
	counter = 0;
	for (int i = 0; i < 4; i++)
	{

		if (counter % 2 == 0)
		{
			blink_clips[i].x = (i - counter) * 16;
			y += 16;
		}
		else
			blink_clips[i].x = (i - counter + 1) * 16;
		blink_clips[i].y = y;
		blink_clips[i].w = 16;
		blink_clips[i].h = 16;
		counter++;
	}

	eyes_sheet = load_image(ren, "res\\img\\eyes.bmp", 255, 0, 255);
	y = 0;
	for (int i = 0; i < 4; i++)
	{
		eyes_clips[i].x = i * 16;
		eyes_clips[i].y = y;
		eyes_clips[i].w = 16;
		eyes_clips[i].h = 16;
	}

}

void Ghost::render_sprite(int x, int y, SDL_Rect* clip)
{
	SDL_Rect tile_rect = { x, y, 16, 16 };
	SDL_RenderCopy(ren, sprite_sheet, clip, &tile_rect);
}

void Ghost::render_blink_sprite(int x, int y, SDL_Rect* clip)
{
	SDL_Rect tile_rect = { x, y, 16, 16 };
	SDL_RenderCopy(ren, blink_sheet, clip, &tile_rect);
}
void Ghost::render_eyes_sprite(int x, int y, SDL_Rect* clip)
{
	SDL_Rect tile_rect = { x, y, 16, 16 };
	SDL_RenderCopy(ren, eyes_sheet, clip, &tile_rect);
}

Ghost::~Ghost()
{
	SDL_DestroyTexture(sprite_sheet);
	SDL_DestroyTexture(blink_sheet);
	SDL_DestroyTexture(eyes_sheet);
	timer.stop();
}

