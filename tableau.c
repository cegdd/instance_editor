#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "main.h"
#include "image.h"
#include "ui.h"


extern int screenh, screenw;


void initsystem(struct DIVERSsysteme *systeme)/*																	systeme*/
{
    int i;

	systeme->shiftactif = false;
	systeme->altactif = false;
	systeme->projetouvert = false;
	systeme->continuer = true;
	systeme->asked = false;
	systeme->moletteactif = false;
	systeme->tookmob = false;
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

void initconsole(struct CONSOLE *console, struct DIVERSsysteme *systeme)
{
    int index;

    setPos4(&console->console.pos, 0, 12, screenw, 105);
    setPos4(&console->shooton.pos, 0, 0, screenw, 12);
    setPos4(&console->shootoff.pos, 0, 0, screenw, 12);
    setPos4(&console->cursor.pos, 0, 0, 2, 12);

    console->console.texture = loadTexture ("rs/ui/console.png");
    console->shooton.texture = loadTexture ("rs/ui/shootboxon.png");
    console->shootoff.texture = loadTexture ("rs/ui/shootboxoff.png");
    console->cursor.texture = loadTexture ("rs/divers/curseur.png");

    console->actif = 9;
    console->curseur = 0;
    console->answered = false;
    console->active = true;

    for (index = 0 ; index < 10 ; index++)
    {
        console->indice[index] = index;
        memset(console->string[index], '\0', 1024);
        console->texte[index].img.texture = imprime (console->string[index], screenw, NOIR, systeme, &console->texte[index].lenght, &console->texte[index].high);
        setPos4(&console->pos[index], 0, (index*10)+10, console->texte[index].lenght, 10);
        copypos(&console->pos[index], &console->texte[index].img.pos);
    }
    memset(console->tampon, '\0', 1024);
    memset(console->TamponToCursor, '\0', 1024);
    memset(console->lastanswer, '\0', 1024);

    console->ecris.img.texture = imprime (console->tampon, screenw, BLANC, systeme, &console->ecris.lenght, &console->ecris.high);
    setPos4(&console->ecris.img.pos, 0, 0, console->ecris.lenght, 10);

    if (glIsTexture(console->console.texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }
}

void initdata(struct DATA *data)
{
    int i;

    data->joueuractif = false;

    data->map.texture = -1;
    setPos4(&data->map.pos, 0, 0, 0, 0);
    data->map.x = 0;
    data->map.y = 0;

    setPos4(&data->joueur.pict.pos, 0, 0, 68, 51);

    data->joueur.pict.texture = loadTexture ("rs/images/perso0.png");

    data->nbmonstre = 0;
    data->mob_selected = -1;
    data->mob[0].monstre.pict.texture = loadTexture ("rs/images/mob0.0.png");
    for (i=0 ; i < 512 ; i++)
    {
        data->mob[i].state = B_NORMAL;
        data->mob[i].selected = false;
        data->mob[i].ID = 0;
        data->mob[i].monstre.pict.texture = 0;
        setPos4(&data->mob[i].monstre.pict.pos, 0, 0, 0, 0);
    }
}
