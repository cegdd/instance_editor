#ifndef TABLEAUH
#define TABLEAUH

#include <SDL_ttf.h>

#include "main.h"

#include "core.h"

int TotalTableauInt(int *ptrTableau, int nbcase);
void initsystem(struct DIVERSsysteme *systeme);
void initui (struct UI *ui);
void initconsole(struct CONSOLE *console, struct DIVERSsysteme *systeme);
void initdata(struct DATA *data);
#endif
