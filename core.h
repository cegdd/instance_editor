#ifndef  COREH
#define COREH

#include "espece.h"



struct DIVERSsysteme
{

    bool shiftactif;
    bool altactif;
    bool moletteactif;
    bool projetouvert;

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

#endif
