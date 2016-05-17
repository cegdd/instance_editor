#ifndef SYSTEMEH
#define SYSTEMEH

#include "main.h"

int checkdistance(SDL_Rect *A, SDL_Rect *B, int lenght);
int calculoctant(int px, int py, int canonx, int canony, int* difx, int* dify);
int arrondi (float flottant);
void say(char *texte, struct CONSOLE *console, struct DIVERSsysteme *systeme);

#endif
