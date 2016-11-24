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
    int i;

	systeme->shiftactif = false;
	systeme->altactif = false;
	systeme->projetouvert = false;
	systeme->continuer = true;
	systeme->asked = false;
	systeme->moletteactif = false;
	systeme->echap = 0;
	systeme->nbcreature = 0;

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

	systeme->oldpp.x = 0;
	systeme->oldpp.y = 0;

	for (i = 0 ; i < 128 ; i++)
    {
        systeme->creature[i].actif = false;
        systeme->creature[i].bouton.etat = B_NORMAL;

        setPos4(&systeme->creature[i].pict.pos, 1100, 620, 100, 100);
    }
}

void initui (struct UI *ui)
{
    ui->UIfondmob = FERMER;

    //start state
    ui->creer.etat =        B_NORMAL;
    ui->quitter.etat =      B_NORMAL;
    ui->loadmap.etat =      B_IMPOSSIBLE;
    ui->charger.etat =      B_NORMAL;
    ui->enregistrer.etat =  B_IMPOSSIBLE;
    ui->depart.etat =  B_IMPOSSIBLE;
    ui->monster.etat =  B_IMPOSSIBLE;
    ui->fermer.etat =  B_NORMAL;

    setPos4(&ui->creer.pos, 0, screenh-40, 120, 40);
    setPos4(&ui->loadmap.pos, 120, screenh-40, 120, 40);
    setPos4(&ui->enregistrer.pos, 240, screenh-40, 120, 40);
    setPos4(&ui->charger.pos, 360, screenh-40, 120, 40);
    setPos4(&ui->depart.pos, 480, screenh-40, 120, 40);
    setPos4(&ui->monster.pos, 600, screenh-40, 120, 40);
    setPos4(&ui->quitter.pos, screenw-120, screenh-40, 120, 40);
    setPos4(&ui->fondmob.pos, screenw-400, 110, 400,618);
    setPos4(&ui->fermer.pos, screenw-44, screenh-84, 40,40);

    ui->creer.texture =         loadTexture ("rs/ui/creer.png");
    ui->quitter.texture =       loadTexture ("rs/ui/quitter.png");
    ui->charger.texture =       loadTexture ("rs/ui/charger.png");
    ui->enregistrer.texture =   loadTexture ("rs/ui/enregistrer.png");
    ui->loadmap.texture =       loadTexture ("rs/ui/loadmap.png");
    ui->depart.texture =        loadTexture ("rs/ui/depart.png");
    ui->monster.texture =       loadTexture ("rs/ui/monster.png");
    ui->fondmob.texture =       loadTexture ("rs/ui/fondmonstre.png");
    ui->fermer.texture =        loadTexture ("rs/ui/fermer.png");

    if (glIsTexture(ui->creer.texture) == GL_FALSE          ||
        glIsTexture(ui->charger.texture) == GL_FALSE          ||
        glIsTexture(ui->enregistrer.texture) == GL_FALSE          ||
        glIsTexture(ui->loadmap.texture) == GL_FALSE          ||
        glIsTexture(ui->depart.texture) == GL_FALSE          ||
        glIsTexture(ui->monster.texture) == GL_FALSE          ||
        glIsTexture(ui->fondmob.texture) == GL_FALSE          ||
        glIsTexture(ui->fermer.texture) == GL_FALSE          ||
        glIsTexture(ui->quitter.texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }

    ui->ListeNb = 0;

    ui->ListeBouton[ui->ListeNb] = &ui->creer;        ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->quitter;      ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->charger;      ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->enregistrer;  ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->loadmap;      ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->depart;       ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->monster;      ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->fermer;
}

void initconsole(struct CONSOLE *console, struct DIVERSsysteme *systeme)
{
    int index;

    setPos4(&console->console.pos, 0, 12, screenw, 105);
    setPos4(&console->shooton.pos, 0, 0, screenw, 12);
    setPos4(&console->shootoff.pos, 0, 0, screenw, 12);

    console->console.texture = loadTexture ("rs/ui/console.png");
    console->shooton.texture = loadTexture ("rs/ui/shootboxon.png");
    console->shootoff.texture = loadTexture ("rs/ui/shootboxoff.png");

    console->actif = 9;
    console->curseur = 0;
    console->answered = false;
    console->active = true;

    for (index = 0 ; index < 10 ; index++)
    {
        console->indice[index] = index;
        memset(console->string[index], '\0', 1024);
        console->string[index][0] = ' ';
        console->texte[index].img.texture = imprime (console->string[index], screenw, NOIR, systeme, &console->texte[index].lenght, &console->texte[index].high);
        console->pos[index].x = 0;
        console->pos[index].y = (index*10)+10;
        console->pos[index].w = console->texte[index].lenght;
        console->pos[index].h = 10;
        console->texte[index].img.pos.x = console->pos[index].x;
        console->texte[index].img.pos.y = console->pos[index].y;
        console->texte[index].img.pos.w = console->pos[index].w;
        console->texte[index].img.pos.h = console->pos[index].h;
    }
    memset(console->tampon, '\0', 1024);
    console->tampon[0] = ' ';
    console->ecris.img.texture = imprime (console->tampon, screenw, BLANC, systeme, &console->ecris.lenght, &console->ecris.high);
    console->ecris.img.pos.x = 0;
    console->ecris.img.pos.y = 0;
    console->ecris.img.pos.w = console->ecris.lenght;
    console->ecris.img.pos.h = 10;

    memset(console->lastanswer, '\0', 1024);
    console->lastanswer[0] = ' ';

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
    data->monstre[0].pict.texture = loadTexture ("rs/images/mob0.0.png");
    for (i=0 ; i < 512 ; i++)
    {
        data->monstre[i].pict.texture = data->monstre[0].pict.texture;
        setPos4(&data->monstre[i].pict.pos, i*2, 0, 148, 38);
    }
}
