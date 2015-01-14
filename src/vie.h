#ifndef VIE_H
#define VIE_H

#define HAUTEUR 50
#define LONGUEUR 50
#define FRAMES_PAR_SECONDE 10

void super_init(bool create, bool canon);
void set_torique(bool b_tor);
void loop_vie();
int cellule(int x, int y);
void detruire_tout();


#endif
