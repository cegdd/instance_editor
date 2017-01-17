#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <errno.h>

#include "main.h"
#include "image.h"
#include "save.h"
#include "systeme.h"

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

int EndsWithRSmob( char *string )
{
  string = strrchr(string, '.');

  if( string != NULL )
    return( strcmp(string, ".RSmob") );

  return( -1 );
}

void listmob(struct DIVERSsysteme *systeme)
{
    char buffer[1024] = {'\0'};
    int i;

    for (i = 0 ; i < systeme->nbcreature ; i++)
    {
         systeme->creature[i].bouton.texture = imprime(systeme->creature[i].name, 114, BLANC, systeme, &systeme->creature[i].bouton.pos.w, &systeme->creature[i].bouton.pos.h);
         setPos2(&systeme->creature[i].bouton.pos,screenw-396, screenh-70-(i*22));

         sprintf(buffer, "rs/bestiaire/%s", systeme->creature[i].imgpath);
         systeme->creature[i].pict.texture =loadTextureandsize(buffer, &systeme->creature[i].pict.pos);
         systeme->creature[i].bt_imgpath.texte.img.texture = imprime(buffer, 114, BLANC, systeme, &systeme->creature[i].bt_imgpath.texte.img.pos.w, &systeme->creature[i].bt_imgpath.texte.img.pos.h);
         setPos2(&systeme->creature[i].bt_imgpath.texte.img.pos,1100, screenh-170);
         //copie de la texture+pos de "texte" a "bouton"
         systeme->creature[i].bt_imgpath.bouton.texture = systeme->creature[i].bt_imgpath.texte.img.texture;
         copypos(&systeme->creature[i].bt_imgpath.texte.img.pos, &systeme->creature[i].bt_imgpath.bouton.pos);

         sprintf(buffer, "vie : %d", systeme->creature[i].vie);
         systeme->creature[i].bt_vie.texte.img.texture = imprime(buffer, 114, BLANC, systeme, &systeme->creature[i].bt_vie.texte.img.pos.w, &systeme->creature[i].bt_vie.texte.img.pos.h);
         setPos2(&systeme->creature[i].bt_vie.texte.img.pos,1100, screenh-190);
         //copie de la texture+pos de "texte" a "bouton"
         systeme->creature[i].bt_vie.bouton.texture = systeme->creature[i].bt_vie.texte.img.texture;
         copypos(&systeme->creature[i].bt_vie.texte.img.pos, &systeme->creature[i].bt_vie.bouton.pos);

        systeme->creature[i].detail[systeme->nbdetail] = &systeme->creature[i].bt_imgpath.bouton;
        systeme->creature[i].detail[systeme->nbdetail] = &systeme->creature[i].bt_vie.bouton;
    }
}

void createmob(struct CONSOLE *console, struct DIVERSsysteme *systeme)
{

    if (console->answered)
    {
        char buffer[1024];

        systeme->asked = false;
        console->answered = false;

        sprintf(systeme->creature[systeme->nbcreature].imgpath, "noimage.png");
        sprintf(systeme->creature[systeme->nbcreature].name, "%s", console->lastanswer);
        systeme->creature[systeme->nbcreature].vie = 0;

        systeme->nbcreature++;
        sprintf(buffer, "monstre %s ajouté avec succès", console->lastanswer);
        say(buffer, console ,systeme);
        listmob(systeme);
    }
}

void deletecreature(struct DIVERSsysteme *systeme, struct DATA *data)
{
    int i;

        for(i = 0 ; i < data->nbmonstre ; i++)
    {
        if (data->mob[i].ID == systeme->activecreature)
        {
            data->mob[i].actif = false;
        }
    }

    for(i = systeme->activecreature+1 ; i < systeme->nbcreature ; i++)
    {
        systeme->creature[i-1].vie = systeme->creature[i].vie;
        sprintf(systeme->creature[i-1].imgpath, "%s", systeme->creature[i].imgpath);
        sprintf(systeme->creature[i-1].name, "%s", systeme->creature[i].name);
    }


    systeme->nbcreature--;
     listmob(systeme);
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
