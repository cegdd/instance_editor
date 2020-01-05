
#ifndef CONSOLEH
#define CONSOLEH

#include <stdbool.h>

#include "image.h"

struct CONSOLE
{
    struct pict shooton;
    struct pict cursor;
    struct pict shootoff;
    struct pict console;
    struct TEXTE texte[10];
    struct TEXTE ecris;
    struct SDL_Rect pos [10];
    int indice[10];
    int LenToCursor;
    int actif;

    char string[10][1024];
    char tampon[1024];
    char TamponToCursor[1024];
    char lastanswer[1024];
    short curseur;
    bool answered;
    bool active;
};

void initconsole(struct CONSOLE *console, struct DIVERSsysteme *systeme);

#endif

