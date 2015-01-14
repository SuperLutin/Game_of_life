#include <SDL.h>

#include "engine_timer.h"

static int start_tick = 0;

void engine_timer_start()
{
	start_tick = SDL_GetTicks();
}

int engine_timer_get()
{
	return SDL_GetTicks() - start_tick;
}
