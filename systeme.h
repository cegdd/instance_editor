#ifndef SYSTEMEH
#define SYSTEMEH

#include "main.h"

int checkdistance(SDL_Rect *A, SDL_Rect *B, int lenght);
int calculoctant(int px, int py, int canonx, int canony, int* difx, int* dify);
int arrondi (float flottant);
void say(char *texte, struct CONSOLE *console, struct DIVERSsysteme *systeme);
void addletter(char lettre, struct CONSOLE *console);
void removeletter(struct CONSOLE *console);
void flushbuffer(struct CONSOLE *console);
int EndsWithRSmob( char *string );

void listmob(struct DIVERSsysteme *systeme);
void createmob(struct CONSOLE *console, struct DIVERSsysteme *systeme);
void deletecreature(struct DIVERSsysteme *systeme, struct DATA *data);
void deletemob(int index, struct DATA *data);

#endif
