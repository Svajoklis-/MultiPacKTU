#include <SDL.h>

#include "timer.h"

Timer::Timer()
	: start_ticks(0), paused_ticks(0), started(false), paused(false)
{

}

void Timer::stop()
{
	started = false;
	paused = true;
	start_ticks = SDL_GetTicks();
}

void Timer::start()
{
	started = true;
	paused = false;
	start_ticks = SDL_GetTicks();
}

int Timer::restart()
{
	int elapsedTicks = ticks();
	start();
	return elapsedTicks;
}

int Timer::ticks() const
{
	if (started)
	{
		if (paused)
			return paused_ticks;
		else
			return SDL_GetTicks() - start_ticks;
	}
	return 0;
}

bool Timer::is_started() const
{
	return started;
}

bool Timer::is_paused() const
{
	return paused;
}

void Timer::preset(int pre)
{
	start_ticks = SDL_GetTicks() - pre;
	started = true;
	paused = false;
}
