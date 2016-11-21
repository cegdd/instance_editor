#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <dirent.h>

#include "main.h"
#include "image.h"
#include "save.h"

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

void addletter(char lettre, struct CONSOLE *console)
{
    console->tampon[console->curseur] = lettre;
    console->curseur++;
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
        console->tampon[console->curseur] = ' ';
    }
}

void flushbuffer(struct CONSOLE *console)
{
    memset(console->tampon, '\0', 1024);
    console->tampon[0] = ' ';
    console->curseur = 0;
}

int EndsWithRSmob( char *string )
{
  string = strrchr(string, '.');

  if( string != NULL )
    return( strcmp(string, ".RSmob") );

  return( -1 );
}

void listmob(struct DIVERSsysteme *systeme)
{
    char buffer[4096] = {'\0'};
    char ret[50] = {'\0'};
    char path[16];

    FILE *fichier = NULL;

    sprintf(path, "./rs/bestiaire/");

    DIR *rep = opendir(path);

    if (rep != NULL)
    {
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL)
        {
             if (strcmp(ent->d_name, ".") != 0 &&
                 strcmp(ent->d_name, "..") != 0 &&
                 !EndsWithRSmob(ent->d_name) )
             {
                 systeme->creature[systeme->nbcreature].actif = true;
                 sprintf(systeme->creature[systeme->nbcreature].path,"%s%s", path, ent->d_name);

                 ent->d_name[strlen(ent->d_name)-6] = '\0';
                 sprintf(systeme->creature[systeme->nbcreature].filename, ent->d_name);

                 fichier = fopen(systeme->creature[systeme->nbcreature].path, "r");

                 lis(fichier, buffer);
                 uncrypt(buffer, ret);
                 sprintf(buffer, "rs/bestiaire/%s", ret);
                 printf("%s\n",buffer);

                 systeme->creature[systeme->nbcreature].bouton.texture = imprime(ent->d_name, 114, NOIR, systeme, &systeme->creature[systeme->nbcreature].bouton.pos.w, &systeme->creature[systeme->nbcreature].bouton.pos.h);
                 setPos2(&systeme->creature[systeme->nbcreature].bouton.pos,screenw-396, screenh-95-(systeme->nbcreature*50));





                 systeme->nbcreature++;
             }
        }

        closedir(rep);
    }
}
