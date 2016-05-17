#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "main.h"
#include "image.h"

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
}
