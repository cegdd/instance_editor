#ifndef COLISIONH
#define COLISIONH

#include <stdbool.h>
#include "struct.h"
bool colisionbox(SDL_Rect *A, SDL_Rect *B, bool pointeur);
bool colisionfromage(SDL_Rect *lanceur, SDL_Rect *recepteur, SDL_Rect *curseur, double marge);
double FindAngle(SDL_Rect *A, SDL_Rect *B);

#endif
