#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "engine_data.h"
#include "engine_sdl.h"

/* Destroy */
void engine_sdl_quit(SDL_Window** window, SDL_GLContext glcontexte)
{
	SDL_DestroyWindow(*window);
	SDL_GL_DeleteContext(glcontexte);
	SDL_Quit();
}

bool engine_sdl_init()
{
	if (SDL_Init(SDL_INIT_VIDEO != 0))
	{
		return false;
	}

	return true;
}

void engine_sdl_toggle_fullscreen(SDL_Window** window)
{
	if ((SDL_GetWindowFlags(*window) & SDL_WINDOW_FULLSCREEN) == 0)
		SDL_SetWindowFullscreen(*window, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(*window, 0);
}

bool engine_sdl_create_window(SDL_Window** window, SDL_GLContext glcontexte, int width, int height, char* title)
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	*window = SDL_CreateWindow(title,
	                          SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED,
	                          width,
	                          height,
	                          SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

	if (*window == NULL)
	{
		fprintf(stdout, "Échec de création de fenêtre SDL (%s)\n", SDL_GetError());
		SDL_Quit();
		return false;
	}

	glcontexte = SDL_GL_CreateContext(*window);
	if (glcontexte == NULL)
	{
		fprintf(stdout, "Échec de création de contexte OpenGL (%s)\n", SDL_GetError());
		SDL_Quit();
		return false;
	}

	// sync buffer swap with monitor's vertical refresh rate
	SDL_GL_SetSwapInterval(1);

	return true;
}

bool engine_sdl_init_gl()
{
	glShadeModel(GL_SMOOTH); // ombrage

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // fond noir

	glClearDepth(1.0f); // tampon de profondeur
	glEnable(GL_DEPTH_TEST); // test de profondeur
	//glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // c'est joli tout plein

	// chargement des textures
	if (engine_data_load_texture() == false)
	{
		fprintf(stdout, "Pas de texture: (%s)\n", SDL_GetError());
		SDL_Quit();
		return false;
	}

	glEnable(GL_TEXTURE_2D);

	return true;
}

void engine_sdl_resize_window(int width, int height)
{
	GLfloat ratio;

	if (height == 0) // évite une division par zéro
	{
		height = 1;
	}
	glViewport(0, 0, width, height);

	ratio = (GLfloat)width / height;

	glMatrixMode(GL_PROJECTION);    // matrice de projection
	glLoadIdentity();               // remise à 0

	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW); // Choisir la matrice de modélisation
	glLoadIdentity(); // Remettre a zéro la matrice de modélisation
}


