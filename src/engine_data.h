#ifndef ENGINE_DATA_H
#define ENGINE_DATA_H

#include <stdbool.h>

#define TEXTURE_BLANC  0
#define TEXTURE_BLEU   1
#define TEXTURE_VERT   2
#define TEXTURE_ROUGE  3

bool engine_data_load_texture();
GLuint engine_data_get_texture(unsigned int n);

#endif
