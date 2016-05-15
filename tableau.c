#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "main.h"
#include "image.h"

extern int screenh, screenw;

int TotalTableauInt(int *ptrTableau, int nbcase)
{
	int total = 0, i = 0;
	for (i = 0 ; i < nbcase ; i++)
	{
		total = total + ptrTableau[i];
	}
	return total;
}

void initsystem(struct DIVERSsysteme *systeme)/*																	systeme*/
{
	systeme->shiftactif = false;
	systeme->altactif = false;
	systeme->inbattle = false;
	systeme->continuer = true;
	systeme->echap = 0;

	systeme->police = TTF_OpenFont("rs/divers/dalek.ttf", TAILLE_POLICE);
	systeme->police1 = TTF_OpenFont("rs/divers/police1.ttf", TAILLE_POLICE);
	if (systeme->police == NULL ||
        systeme->police1 == NULL)
    {
        printf("police not load2\n");
    }

    setPos(&systeme->pointeur.pos, 0, 0, 20, 30);

	systeme->pecran.x = 0;
	systeme->pecran.y = 0;
	systeme->pecran.w = screenw;
	systeme->pecran.h = screenh;

	systeme->ppobj.w = 50;
	systeme->ppobj.h = 50;

	systeme->oldpp.x = 0;
	systeme->oldpp.y = 0;
}

void initui (struct UI *ui)
{
    ui->creer.etat = B_NORMAL;
    ui->quitter.etat = B_NORMAL;

    setPos(&ui->creer.pos, 0, screenh-40, 120, 40);
    setPos(&ui->quitter.pos, screenw-120, screenh-40, 120, 40);

    ui->creer.texture = loadTexture ("rs/ui/creer.png");
    ui->quitter.texture = loadTexture ("rs/ui/quitter.png");

    if (glIsTexture(ui->creer.texture) == GL_FALSE          ||
        glIsTexture(ui->quitter.texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }
}

void initconsole(struct CONSOLE *console, struct DIVERSsysteme *systeme)
{
    int index;
    char string[10][1024];

    setPos(&console->console.pos, 0, 0, screenw, 105);

    console->console.texture = loadTexture ("rs/ui/console.png");

    for (index = 0 ; index < 10 ; index++)
    {
        sprintf(string[index], "un petit peu de texte");
        console->texte[index].img.texture = imprime (string[index], screenw, NOIR, systeme, &console->texte[index].lenght, &console->texte[index].high);
        console->texte[index].img.pos.x = 0;
        console->texte[index].img.pos.y = index*10;
        console->texte[index].img.pos.w = console->texte[index].lenght;
        console->texte[index].img.pos.h = 8;
    }

    if (glIsTexture(console->console.texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }
}