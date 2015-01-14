#include <stdio.h>

#include <GL/gl.h>
#include <SDL.h>

#include "engine_data.h"
#include "show.h"
#include "vie.h"

#define UNIT 1.0f / LONGUEUR

void dessine_scene(SDL_Window** window)
{
	size_t x, y = 0;

	// effaçage
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // remettre à zéro

	glTranslatef(-0.5f, -0.5f, -1.5f);

	glBindTexture(GL_TEXTURE_2D, engine_data_get_texture(1));

	for (x = 0; x < LONGUEUR; ++x)
	{
		for (y = 0; y < HAUTEUR; ++y)
		{
			if ((x == 0) && (y == 0))
				glBindTexture(GL_TEXTURE_2D, engine_data_get_texture(TEXTURE_ROUGE));
			else if ((x == (LONGUEUR - 1)) && (y == (HAUTEUR - 1)))
				glBindTexture(GL_TEXTURE_2D, engine_data_get_texture(TEXTURE_VERT));
			else if (cellule(x, y) == 1)
				glBindTexture(GL_TEXTURE_2D, engine_data_get_texture(TEXTURE_BLEU));
			else
				glBindTexture(GL_TEXTURE_2D, engine_data_get_texture(TEXTURE_BLANC));

			glBegin(GL_QUADS);
				glTexCoord2f(0, 0); glVertex2f(x * UNIT,     UNIT * (y + 1));
				glTexCoord2f(0, 1); glVertex2f(x * UNIT,     UNIT * y);
				glTexCoord2f(1, 1); glVertex2f(UNIT * (x + 1), UNIT * y);
				glTexCoord2f(1, 0); glVertex2f(UNIT * (x + 1), UNIT * (y + 1));
			glEnd();
		}
	}

	/* Draw it to the screen */
	SDL_GL_SwapWindow(*window);
}
