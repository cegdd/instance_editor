#ifndef SYSTEMEH
#define SYSTEMEH

#include <stdbool.h>

#include "image.h"
#include "espece.h"

struct DIVERSsysteme
{

    bool shiftactif;
    bool altactif;
    bool moletteactif;
    bool projetouvert;
    bool pathmode;

    bool asked;
    int askID;

    bool continuer;
    int echap;
    int typeclavier;
    int nbcreature;
    int activecreature;

    struct pict pointeur;
    struct ESPECE creature[128];
    bool tookmob;

    SDL_Texture *BGmort;
    GLuint BG;
    SDL_Texture *BGblanc;


    SDL_Event evenement;

    SDL_Window *screen;

    TTF_Font *police;
    TTF_Font *police1;

	SDL_Rect pecran;
	SDL_Rect pcreature;
	SDL_Rect oldpp;
	SDL_Rect ppobj;
	SDL_Rect origine;
	SDL_Rect temp;

};



int checkdistance(SDL_Rect *A, SDL_Rect *B, int lenght);
int calculoctant(int px, int py, int canonx, int canony, int* difx, int* dify);
int arrondi (float flottant);
void say(char *texte, struct CONSOLE *console, struct DIVERSsysteme *systeme);
void addletter(char lettre, struct CONSOLE *console);
void removeletter(struct CONSOLE *console);
void flushbuffer(struct CONSOLE *console);

void createmob(struct CONSOLE *console, struct DIVERSsysteme *systeme);
int checkactifmob(struct DATA *data);

void initsystem(struct DIVERSsysteme *systeme);

#endif
