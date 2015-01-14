#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vie.h"

///////////////////////////////////////////
// Variables privées
///////////////////////////////////////////
int** matrice_prim;
int** matrice_bis;
int*** p_matrice;
int*** p_matrice_blit;
bool torique = false;

///////////////////////////////////////////
// Fonctions privées
///////////////////////////////////////////
int** creer_matrice(int l, int c);
void detruire(int** mat);
void init_jeu(int** matrice); // init
void init_canon(int** matrice); // init
void swap(int*** matrice, int*** matrice_blit);
void gen_vie(int** matrice, int** matrice_blit); // on fait de la vie
bool sk8_or_die(int x, int y, int** matrice); // cellule vit ou meurt
int voisinage_torique(int x, int y, int** matrice); // comptage des voisins
int voisinage(int x, int y, int** matrice); // comptage des voisins

#define MTOR(taille, val) ((taille + val) % taille)

int voisinage_torique(int x, int y, int** matrice)
{
	int badauds = matrice[MTOR(LONGUEUR, x - 1)][MTOR(HAUTEUR, y - 1)] +
	              matrice[MTOR(LONGUEUR, x)]    [MTOR(HAUTEUR, y - 1)] +
	              matrice[MTOR(LONGUEUR, x + 1)][MTOR(HAUTEUR, y - 1)] +

	              matrice[MTOR(LONGUEUR, x - 1)][MTOR(HAUTEUR, y)] +
	              matrice[MTOR(LONGUEUR, x + 1)][MTOR(HAUTEUR, y)] +

	              matrice[MTOR(LONGUEUR, x - 1)][MTOR(HAUTEUR, y + 1)] +
	              matrice[MTOR(LONGUEUR, x)]    [MTOR(HAUTEUR, y + 1)] +
	              matrice[MTOR(LONGUEUR, x + 1)][MTOR(HAUTEUR, y + 1)];

	return badauds;
}

int voisinage(int x, int y, int** matrice)
{
	bool n = false;
	bool s = false;
	bool e = false;
	bool o = false;

	int badauds = 0;

	if (x == 0)
	{
		o = true;
	}
	if (x == (LONGUEUR - 1))
	{
		e = true;
	}
	if (y == 0)
	{
		s = true;
	}
	if (y == (HAUTEUR - 1))
	{
		n = true;
	}

	if ((n == false) && (s == false) && (e == false) && (o == false))
	{
		badauds = matrice[x - 1][y - 1] +
	             matrice[x]    [y - 1] +
	             matrice[x + 1][y - 1] +
	             matrice[x - 1][y] +
	             matrice[x + 1][y] +
	             matrice[x - 1][y + 1] +
	             matrice[x]    [y + 1] +
	             matrice[x + 1][y + 1];
	}
	else if ((n == true) && (e == true))
	{
		badauds = matrice[LONGUEUR - 2][HAUTEUR - 1] +
	             matrice[LONGUEUR - 2][HAUTEUR - 2] +
	             matrice[LONGUEUR - 1][HAUTEUR - 1];
	}
	else if ((n == true) && (o == true))
	{
		badauds = matrice[1][HAUTEUR - 1] +
	             matrice[0][HAUTEUR - 2] +
	             matrice[1][HAUTEUR - 2];
	}
	else if ((s == true) && (e == true))
	{
		badauds = matrice[LONGUEUR - 2][0] +
	             matrice[LONGUEUR - 2][1] +
	             matrice[LONGUEUR - 1][1];
	}
	else if ((s == true) && (o == true))
	{
		badauds = matrice[0][1] +
	             matrice[1][0] +
	             matrice[1][1];
	}
	else if (n == true)
	{
		badauds = matrice[x - 1][HAUTEUR - 2] +
	             matrice[x]    [HAUTEUR - 2] +
	             matrice[x + 1][HAUTEUR - 2] +

	             matrice[x - 1][HAUTEUR - 1] +
	             matrice[x + 1][HAUTEUR - 1];
	}
	else if (s == true)
	{
		badauds = matrice[x - 1][1] +
	             matrice[x]    [1] +
	             matrice[x + 1][1] +

	             matrice[x - 1][0] +
	             matrice[x + 1][0];
	}
	else if (e == true)
	{
		badauds = matrice[LONGUEUR - 2][y + 1] +
	             matrice[LONGUEUR - 2][y] +
	             matrice[LONGUEUR - 2][y - 1] +

	             matrice[LONGUEUR - 1][y + 1] +
	             matrice[LONGUEUR - 1][y - 1];
	}
	else if (o == true)
	{
		badauds = matrice[1][y + 1] +
	             matrice[1][y] +
	             matrice[1][y - 1] +

	             matrice[0][y + 1] +
	             matrice[0][y - 1];
	}

	return badauds;
}

bool sk8_or_die(int x, int y, int** matrice)
{
	bool etat;

	int voisins;
	
	if (torique == true)
		voisins = voisinage_torique(x, y, matrice);
	else
		voisins = voisinage(x, y, matrice);
		
	if (matrice[x][y] == 0)
		etat = false;
	else
		etat = true;

	if (etat == true)
	{
		if ((voisins == 2) || (voisins == 3))
			return true;
		else
			return false;
	}
	else
	{
		if (voisins == 3)
			return true;
		else
			return false;
	}

	return false;
}

int** creer_matrice(int l, int c)
{
	int** tab_1 = (int**)malloc(sizeof(int*) * l);

	int* tab_2 = (int*)malloc(sizeof(int) * (l * c));

	for (int i = 0; i < l; ++i)
	{
		tab_1[i] = &tab_2[i * c];
	}
	return tab_1;
}

void detruire(int** mat)
{
	free(mat[0]);
	free(mat);
}

void init_jeu(int** matrice)
{
	srand(time(NULL));
	for (size_t i = 0; i < LONGUEUR; ++i)
	{
		for (size_t j = 0; j < HAUTEUR; ++j)
		{
			if ((rand()%100) > 40)
			{
				matrice[i][j] = 1;
			}
			else
			{
				matrice[i][j] = 0;
			}
		}
	}
}

void init_canon(int** matrice)
{
	for (size_t i = 0; i < LONGUEUR; ++i)
	{
		for (size_t j = 0; j < HAUTEUR; ++j)
		{
			matrice[i][j] = 0;
		}
	}
	// canon
	matrice[1][43] = 1;
	matrice[1][44] = 1;
	matrice[2][43] = 1;
	matrice[2][44] = 1;

	matrice[11][42] = 1;
	matrice[11][43] = 1;
	matrice[11][44] = 1;

	matrice[12][41] = 1;
	matrice[12][45] = 1;

	matrice[13][40] = 1;
	matrice[13][46] = 1;
	matrice[14][40] = 1;
	matrice[14][46] = 1;

	// œuil
	matrice[15][43] = 1;

	// bec
	matrice[16][41] = 1;
	matrice[16][45] = 1;
	matrice[17][42] = 1;
	matrice[17][43] = 1;
	matrice[17][44] = 1;
	matrice[18][43] = 1;

	// canon
	matrice[21][44] = 1;
	matrice[21][45] = 1;
	matrice[21][46] = 1;
	matrice[22][44] = 1;
	matrice[22][45] = 1;
	matrice[22][46] = 1;
	matrice[23][43] = 1;
	matrice[23][47] = 1;

	matrice[25][42] = 1;
	matrice[25][43] = 1;
	matrice[25][47] = 1;
	matrice[25][48] = 1;

	// cible
	matrice[35][45] = 1;
	matrice[35][46] = 1;
	matrice[36][45] = 1;
	matrice[36][46] = 1;
	
	set_torique(false);
}

void swap(int*** matrice, int*** matrice_blit)
{
	int** swap_mat = *matrice;

	*matrice = *matrice_blit;
	*matrice_blit = &(*swap_mat);
}

void set_torique(bool b_tor)
{
	torique = b_tor;
}

void gen_vie(int** matrice, int** matrice_blit)
{
	for (size_t i = 0; i < LONGUEUR; ++i)
	{
		for (size_t j = 0; j < HAUTEUR; ++j)
		{
			if (sk8_or_die(i, j, matrice))
				matrice_blit[i][j] = 1;
			else
				matrice_blit[i][j] = 0;
		}
	}
}

void super_init(bool create, bool canon)
{
	if (create == true)
	{
		matrice_prim = creer_matrice(LONGUEUR, HAUTEUR);
		matrice_bis = creer_matrice(LONGUEUR, HAUTEUR);
	}
	
	if (canon)
		init_canon(matrice_prim);
	else
		init_jeu(matrice_prim);

	p_matrice = &matrice_prim;
	p_matrice_blit = &matrice_bis;
}

int cellule(int x, int y)
{
	return (*p_matrice)[x][y];
}

void loop_vie()
{
		gen_vie(*p_matrice, *p_matrice_blit);
		swap(&(*p_matrice), &(*p_matrice_blit));
}

void detruire_tout()
{
	detruire(matrice_prim);
	detruire(matrice_bis);
}
