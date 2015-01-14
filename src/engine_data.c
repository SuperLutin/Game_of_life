#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <SDL.h>

#include "engine_data.h"

bool engine_data_load_texture_num(char* fichier, int i);

GLuint texture[4];

bool engine_data_load_texture()
{
	bool loaded = true;

	if (engine_data_load_texture_num("./data/blanc.bmp", 0) == false)
		loaded = false;
	if (engine_data_load_texture_num("./data/bleu.bmp", 1) == false)
		loaded = false;
	if (engine_data_load_texture_num("./data/vert.bmp", 2) == false)
		loaded = false;
	if (engine_data_load_texture_num("./data/rouge.bmp", 3) == false)
		loaded = false;

	return loaded;
}

bool engine_data_load_texture_num(char* fichier, int i)
{
	SDL_Surface* surf_texture = SDL_LoadBMP(fichier);

	if (surf_texture == NULL)
	{
		return false;
	}

	glGenTextures(1, &texture[i]);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, surf_texture->w, surf_texture->h, 0,
	             GL_BGR, GL_UNSIGNED_BYTE, surf_texture->pixels);

	// filtrage lineaire
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surf_texture);

	return true;
}

GLuint engine_data_get_texture(unsigned int n)
{
	return texture[n];
}

