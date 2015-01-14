#ifndef ENGINE_SDL_H
#define ENGINE_SDL_H

#include <stdbool.h>

#include <SDL.h>

void engine_sdl_quit(SDL_Window** window, SDL_GLContext glcontexte);
bool engine_sdl_init();
void engine_sdl_toggle_fullscreen(SDL_Window** window);
bool engine_sdl_create_window(SDL_Window** window, SDL_GLContext glcontexte,
                              int width, int height, char* title);

bool engine_sdl_init_gl();
void engine_sdl_resize_window(int width, int height);
bool engine_sdl_load_texture();

#endif /* ENGINE_SDL_H */
