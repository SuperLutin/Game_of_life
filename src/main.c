#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include "engine_sdl.h"
#include "engine_timer.h"
#include "game.h"
#include "show.h"
#include "vie.h"

#define WIDTH  300
#define HEIGHT 300

SDL_Window* main_window = NULL;
SDL_GLContext glcontexte = NULL;

// atexit
void casse_tout();

T_MODE handle_key(SDL_Keycode keycode, T_MODE old_mode)
{
	T_MODE mode = old_mode;

	if (keycode == SDLK_ESCAPE)
		mode = MODE_QUIT;
	if (keycode == SDLK_p)
		mode = MODE_PAUSE;
	if (keycode == SDLK_r)
	{
		super_init(true, false);
		set_torique(true);
	}
	if (keycode == SDLK_n)
	{
		super_init(true, true);
		set_torique(false);
	}
	if (keycode == SDLK_SPACE)
		mode = MODE_PLAY;
	if (keycode == SDLK_f)
		engine_sdl_toggle_fullscreen(&main_window);

	return mode;
}

int main(int N, char* T[])
{
	T_MODE joue = MODE_PLAY;
	bool visible = true;
	SDL_Event event;

	atexit(casse_tout);

	if (engine_sdl_init() == false)
	{
		fprintf(stderr, "SDL, c'est plus fort que toi !\n");
		return 1;
	}

	if (engine_sdl_create_window(&main_window, &glcontexte,
	    WIDTH, HEIGHT, "Jeu de la vie") == false)
	{
		fprintf(stderr, "Bill Gates, c'est plus fort que toi !\n");
		return 1;
	}

	if (engine_sdl_init_gl() == false)
	{
		fprintf(stderr, "OpenGL, c'est plus fort que toi !\n");
		return 1;
	}

	// initialisation du jeu
	engine_sdl_resize_window(WIDTH, HEIGHT);
	super_init(true, true);
	engine_timer_start();

	while (joue != MODE_QUIT)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_WINDOWEVENT:
					switch(event.window.event)
					{
						case SDL_WINDOWEVENT_RESIZED:
							/* handle resize event */
							engine_sdl_resize_window(event.window.data1, event.window.data2);
							break;
						case SDL_WINDOWEVENT_HIDDEN:
							visible = false;
							break;
						case SDL_WINDOWEVENT_SHOWN:
							visible = true;
							break;
					}
					break;
				case SDL_KEYDOWN:
					joue = handle_key(event.key.keysym.sym, joue);
					break;
				case SDL_QUIT:
					joue = MODE_QUIT;
					break;
				default:
					break;
			}
		}
		if (visible == true)
		{
			if (engine_timer_get() > (1000 / FRAMES_PAR_SECONDE))
			{
				if (joue == MODE_PLAY)
				{
					dessine_scene(&main_window);
					loop_vie();

					engine_timer_start();
				}
			}
		}
	}

	return 0;

	(void)N; (void)T;
}

void casse_tout()
{
	detruire_tout();
	engine_sdl_quit(&main_window, &glcontexte);
}
