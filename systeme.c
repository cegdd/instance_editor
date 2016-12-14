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

    systeme->nbcreature = 0;

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
                 sprintf(systeme->creature[systeme->nbcreature].path,"%s%s", path, ent->d_name);

                 ent->d_name[strlen(ent->d_name)-6] = '\0';
                 sprintf(systeme->creature[systeme->nbcreature].filename, ent->d_name);

                 fichier = fopen(systeme->creature[systeme->nbcreature].path, "r");

                 systeme->creature[systeme->nbcreature].bouton.texture = imprime(ent->d_name, 114, BLANC, systeme, &systeme->creature[systeme->nbcreature].bouton.pos.w, &systeme->creature[systeme->nbcreature].bouton.pos.h);
                 setPos2(&systeme->creature[systeme->nbcreature].bouton.pos,screenw-396, screenh-70-(systeme->nbcreature*22));

                 lis(fichier, buffer);
                 uncrypt(buffer, ret);
                 sprintf(systeme->creature[systeme->nbcreature].imgpath, "%s", ret);
                 sprintf(buffer, "rs/bestiaire/%s", ret);
                 systeme->creature[systeme->nbcreature].pict.texture =loadTexture (buffer);
                 systeme->creature[systeme->nbcreature].bt_imgpath.texte.img.texture = imprime(buffer, 114, BLANC, systeme, &systeme->creature[systeme->nbcreature].bt_imgpath.texte.img.pos.w, &systeme->creature[systeme->nbcreature].bt_imgpath.texte.img.pos.h);
                 setPos2(&systeme->creature[systeme->nbcreature].bt_imgpath.texte.img.pos,1100, screenh-170);
                 //copie de la texture+pos de "texte" a "bouton"
                 systeme->creature[systeme->nbcreature].bt_imgpath.bouton.texture = systeme->creature[systeme->nbcreature].bt_imgpath.texte.img.texture;
                 copypos(&systeme->creature[systeme->nbcreature].bt_imgpath.texte.img.pos, &systeme->creature[systeme->nbcreature].bt_imgpath.bouton.pos);

                 lis(fichier, buffer);
                 uncrypt(buffer, ret);
                 systeme->creature[systeme->nbcreature].vie = atoi(ret);
                 sprintf(buffer, "vie : %d", systeme->creature[systeme->nbcreature].vie);
                 systeme->creature[systeme->nbcreature].bt_vie.texte.img.texture = imprime(buffer, 114, BLANC, systeme, &systeme->creature[systeme->nbcreature].bt_vie.texte.img.pos.w, &systeme->creature[systeme->nbcreature].bt_vie.texte.img.pos.h);
                 setPos2(&systeme->creature[systeme->nbcreature].bt_vie.texte.img.pos,1100, screenh-190);
                 //copie de la texture+pos de "texte" a "bouton"
                 systeme->creature[systeme->nbcreature].bt_vie.bouton.texture = systeme->creature[systeme->nbcreature].bt_vie.texte.img.texture;
                 copypos(&systeme->creature[systeme->nbcreature].bt_vie.texte.img.pos, &systeme->creature[systeme->nbcreature].bt_vie.bouton.pos);

                 systeme->nbcreature++;
             }
        }

        closedir(rep);
    }
}

void createmob(struct CONSOLE *console, struct DIVERSsysteme *systeme)
{

    if (console->answered)
    {
        char buffer[128];
        FILE *fichier = NULL;

        systeme->asked = false;
        console->answered = false;


        sprintf(buffer, "rs/bestiaire/%s.RSmob", console->lastanswer);
        fichier = fopen(buffer, "w+");
        if (fichier != NULL)
        {
            sprintf(buffer, "noimage.png");
            ecris(buffer, fichier);
            sprintf(buffer, "0");
            ecris(buffer, fichier);

            fclose(fichier);

            systeme->nbcreature++;
            sprintf(buffer, "monstre %s ajouté avec succès", console->lastanswer);
            say(buffer, console ,systeme);
        }
        int i;
        for (i = 0 ; i < 128 ; i++)
        {
            systeme->creature[i].actif = false;
            systeme->creature[i].bouton.etat = B_NORMAL;
            systeme->creature[i].filename[0]    = '\0';
            systeme->creature[i].name[0]        = '\0';
            systeme->creature[i].path[0]        = '\0';
            systeme->creature[i].imgpath[0]     = '\0';

            setPos4(&systeme->creature[i].pict.pos, 1100, 620, 100, 100);

            systeme->nbdetail = 0;
            systeme->creature[i].detail[systeme->nbdetail] = &systeme->creature[i].bt_imgpath.bouton;    systeme->nbdetail++;
            systeme->creature[i].detail[systeme->nbdetail] = &systeme->creature[i].bt_vie.bouton;
        }

        listmob(systeme);

    }
}

void refreshmob(struct CREATURE *creature)
{
    FILE *fichier = NULL;
    char buffer[128];

    remove(creature->path);
    fichier = fopen(creature->path, "w+");
    ecris(creature->imgpath, fichier);
    sprintf(buffer, "%d", creature->vie);
    ecris(buffer, fichier);
    fclose(fichier);
}
