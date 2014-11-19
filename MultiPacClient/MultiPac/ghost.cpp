#include "ghost.h"


Ghost::Ghost()
{
	ghost_id = 1;
	vulnerable = false;
	x = 8;
	y = 8;
	direction = 0;
	load_sprites();
	timer.start();
}


void Ghost::render(int x_offset, int y_offset)
{
	if (!vulnerable)
	{
		render_sprite(x - 4 + x_offset, y - 4 + y_offset, &sprite_clips[frame + direction * 2]);
	}
	else
	{
		int vulnerability_ticks = vulnerability_timer.ticks();

		if (vulnerability_ticks > vulnerability_time)
		{
			vulnerability_timer.stop();
			vulnerable = false;
		}
		else
		{
			if (vulnerability_ticks < vulnerability_time / 2 || (vulnerability_ticks % blinking_interval) < blinking_interval/2)
			{
				render_blink_sprite(x - 4 + x_offset, y - 4 + y_offset, &blink_clips[frame]);
			}
			else
			{
				render_blink_sprite(x - 4 + x_offset, y - 4 + y_offset, &blink_clips[frame+2]);
			}
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

void Ghost::turn_vulnerable()
{
	vulnerability_timer.start();
	vulnerable = true;
	
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

	blink_sheet = load_image(ren, "res\\img\\blinking.bmp", 255, 0, 255);
	y = 0;
	for (int i = 0; i < 2; i++)
	{
		blink_clips[i].x = i * 16;
		blink_clips[i].y = y;
		blink_clips[i].w = 16;
		blink_clips[i].h = 16;
	}
	y += 16;
	for (int i = 2; i < 4; i++)
	{
		blink_clips[i].x = (i - 2) * 16;
		blink_clips[i].y = y;
		blink_clips[i].w = 16;
		blink_clips[i].h = 16;
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

Ghost::~Ghost()
{
	SDL_DestroyTexture(sprite_sheet);
	SDL_DestroyTexture(blink_sheet);
	timer.stop();
}

