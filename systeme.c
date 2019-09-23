#include "C:\Users\antoi\Documents\programation\SDL2\SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <errno.h>

#include "console.h"
#include "data.h"
#include "systeme.h"
#include "main.h"

extern int screenh, screenw;

int checkdistance(SDL_Rect *A, SDL_Rect *B, int lenght)
{
    double resultat;
	double difx = (A->x+(A->w/2)) - (B->x+(B->w/2));
	double dify = (A->y+(A->h/2)) - (B->y+(B->h/2));

	if (difx < 0) {difx *= -1;}
	if (dify < 0) {dify *= -1;}

	resultat = sqrt((difx*difx)+(dify*dify));

	if (resultat <= lenght) {return -1;} /* dedans*/
	return 1; /* dehors*/
}

int arrondi (float flottant)
{
    return (int)(flottant+0.5);
}

int calculoctant(int x, int y, int x2, int y2, int* difx, int* dify)
{
	int octant = 0;

	if (x >= x2)
	{
		if (difx != NULL)
		{
			*difx = x - x2;
		}

		if (y >= y2)
        {
			if (difx != NULL)
			{
				*dify = y - y2;
			}
            octant = 2;
        }
        else
        {
			if (difx != NULL)
			{
				*dify = y2 - y;
			}
            octant = 1;
        }
    }
    else
    {
		if (difx != NULL)
		{
			*difx = x2 - x;
		}

        if (y >= y2)
        {
			if (difx != NULL)
			{
				*dify = y - y2;
			}
            octant = 3;
        }
        else
        {
			if (difx != NULL)
			{
				*dify = y2 - y;
			}
            octant = 4;
        }
    }

    return octant;
}
void say(char *texte, struct CONSOLE *console, struct DIVERSsysteme *systeme)
{
   // if(console->tampon[0] != '\0')
   // {
        int index;

        sprintf (console->string[console->actif], texte);
        console->texte[console->actif].img.texture = imprime (console->string[console->actif], screenw, NOIR, systeme, &console->texte[console->actif].lenght, NULL);
        console->actif--;
        if(console->actif < 0)
        {
            console ->actif = 9;
        }


        for (index = 0 ; index <= 9 ; index++)
        {
            console->indice[index]++;
            if (console->indice[index] == 10)
            {
                console->indice[index] = 0;
            }
            console->texte[index].img.pos.x = console->pos[console->indice[index]].x;
            console->texte[index].img.pos.y = console->pos[console->indice[index]].y;
            console->texte[index].img.pos.w = console->texte[index].lenght;
        }
   // }
}
void addletter(char lettre, struct CONSOLE *console)
{
    int i = strlen(console->tampon);
    i++;
    if(i < 1024)
    {
        while(i >= console->curseur)
        {
            console->tampon[i+1] =console->tampon[i];
            i--;
        }
        console->tampon[console->curseur] = lettre;
        console->curseur++;
        sprintf(console->TamponToCursor, console->tampon);
        console->TamponToCursor[console->curseur] = '\0';
    }
}

void removeletter(struct CONSOLE *console)
{
    if (console->curseur > 1)
    {
        console->curseur--;
        console->tampon[console->curseur] = '\0';
    }
    else if (console->curseur == 1)
    {
        console->curseur = 0;
        console->tampon[console->curseur] = '\0';
    }
}

void flushbuffer(struct CONSOLE *console)
{
    memset(console->tampon, '\0', 1024);
    memset(console->TamponToCursor, '\0', 1024);
    console->curseur = 0;
}


int checkactifmob(struct DATA *data)
{
    int i;

    for (i = 0 ; i < data->nbmonstre ; i++)
    {
        if (data->mob[i].actif == false)
        {
            return i;
        }
    }
    return -1;
}

void initsystem(struct DIVERSsysteme *systeme)
{
    int i;

	systeme->shiftactif     = false;
	systeme->altactif       = false;
	systeme->projetouvert   = false;
	systeme->continuer      = true;
	systeme->asked          = false;
	systeme->moletteactif   = false;
	systeme->tookmob        = false;
	systeme->pathmode       = false;

	systeme->echap = 0;
	systeme->nbcreature = 0;
	systeme->activecreature = 0;

	systeme->police = TTF_OpenFont("rs/divers/dalek.ttf", TAILLE_POLICE);
	systeme->police1 = TTF_OpenFont("rs/divers/arial.ttf", TAILLE_POLICE);
	if (systeme->police == NULL ||
        systeme->police1 == NULL)
    {
        printf("police not load2\n");
    }

    setPos4(&systeme->pointeur.pos, 0, 0, 20, 30);

	systeme->pecran.x = 0;
	systeme->pecran.y = 0;
	systeme->pecran.w = screenw;
	systeme->pecran.h = screenh;

	systeme->ppobj.w = 50;
	systeme->ppobj.h = 50;

	setPos4(&systeme->origine, 0, 0, 0, 0);
	setPos4(&systeme->pcreature, 1100, 620, 100, 100);

	systeme->oldpp.x = 0;
	systeme->oldpp.y = 0;

	for (i = 0 ; i < 128 ; i++)
    {
        systeme->creature[i].vie = 0;
        systeme->creature[i].bouton.etat = B_NORMAL;
        systeme->creature[i].name[0]        = '\0';

        setPos4(&systeme->creature[i].pict.pos, 1100, 620, 0, 0);
    }
    systeme->creature[0].bouton.etat = B_INUSE;
}
