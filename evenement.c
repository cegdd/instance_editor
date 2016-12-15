#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <string.h>

#include "struct.h"

#include "main.h"
#include "image.h"
#include "evenement.h"
#include "tableau.h"
#include "systeme.h"
#include "clavier.h"
#include "colision.h"
#include "editeur.h"

extern int screenh, screenw;

void boucleevent (struct DIVERSsysteme *systeme, struct UI *ui, struct CONSOLE *console, struct DATA *data)
{
	while(SDL_PollEvent(&systeme->evenement) == 1)
	{
		switch(systeme->evenement.type)
		{
            case SDL_MOUSEMOTION:
                if (systeme->moletteactif)
                {
                    systeme->origine.x += systeme->evenement.motion.xrel;
                    systeme->origine.y -= systeme->evenement.motion.yrel;
                }
		    case SDL_MOUSEBUTTONDOWN:
                if( systeme->evenement.button.button == SDL_BUTTON_LEFT )
                {
                    clic_DOWN_L(ui, systeme, data, console);
                }
                else if( systeme->evenement.button.button == SDL_BUTTON_MIDDLE )
                {
                    systeme->moletteactif = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if( systeme->evenement.button.button == SDL_BUTTON_LEFT )
                {
                    clic_UP_L(systeme, ui, console);
                }
                else if( systeme->evenement.button.button == SDL_BUTTON_MIDDLE )
                {
                    systeme->moletteactif = false;
                }
                break;
            case SDL_KEYDOWN:
                if (console->active)
                {
                    intputtextedown(systeme, console);
                }
                else
                {
                    pressdown(systeme);
                }
                break;
            case SDL_KEYUP:
                if (console->active)
                {
                    intputtexteup(systeme, console);
                }
                else
                {
                    if (systeme->evenement.key.keysym.scancode == SDL_SCANCODE_TAB)
                    {
                        console->active = true;
                    }
                }
                break;
		}
	}
}

void pointeur(struct DIVERSsysteme *systeme, struct UI *ui)
{
    int i, j;

    for (i = 0 ; i <= ui->ListeNb ; i++)
    {
        if ( colisionbox(&systeme->pointeur.pos, &ui->ListeBouton[i]->pos, true) == true &&
            ui->ListeBouton[i]->etat != B_CLIQUER &&
            ui->ListeBouton[i]->etat != B_IMPOSSIBLE)
            {
                ui->ListeBouton[i]->etat = B_SURVOLER;
            }
        else if ( ui->ListeBouton[i]->etat != B_CLIQUER &&
                  ui->ListeBouton[i]->etat != B_IMPOSSIBLE )
        {
            ui->ListeBouton[i]->etat = B_NORMAL;
        }
    }

    if (ui->UIfondmob == OUVERT)
    {
        for (i = 0 ; i < systeme->nbcreature ; i++)
        {//le nom du mob
            if ( colisionbox(&systeme->pointeur.pos, &systeme->creature[i].bouton.pos, true) == true &&
                systeme->creature[i].bouton.etat != B_CLIQUER &&
                systeme->creature[i].bouton.etat != B_IMPOSSIBLE)
                {
                    systeme->creature[i].bouton.etat = B_SURVOLER;
                }
            else if ( systeme->creature[i].bouton.etat != B_CLIQUER &&
                      systeme->creature[i].bouton.etat != B_IMPOSSIBLE )
            {
                systeme->creature[i].bouton.etat = B_NORMAL;
            }

            for (j = 0 ; j <= systeme->nbdetail ; j++)
            {//les details du mob
                if ( colisionbox(&systeme->pointeur.pos, &systeme->creature[i].detail[j]->pos, true) == true &&
                    systeme->creature[i].detail[j]->etat != B_CLIQUER &&
                    systeme->creature[i].detail[j]->etat != B_IMPOSSIBLE)
                    {
                        systeme->creature[i].detail[j]->etat = B_SURVOLER;
                    }
                else if ( systeme->creature[i].detail[j]->etat != B_CLIQUER &&
                          systeme->creature[i].detail[j]->etat != B_IMPOSSIBLE )
                {
                    systeme->creature[i].detail[j]->etat = B_NORMAL;
                }
            }
        }
    }
}

void clic_UP_L(struct DIVERSsysteme *systeme, struct UI *ui, struct CONSOLE *console)
{
    int i,i2,i3,j;

    /*shootbox*/
    if (colisionbox(&systeme->pointeur.pos, &console->shooton.pos, true))
    {
        console->active = true;
    }
    else
    {
        console->active = false;
    }

    for (i = 0 ; i <= ui->ListeNb ; i++)
    {
        if ( colisionbox(&systeme->pointeur.pos, &ui->ListeBouton[i]->pos, true) == true &&
             ui->ListeBouton[i]->etat == B_CLIQUER)
        {
            ui->ListeBouton[i]->etat = B_NORMAL;
            systeme->asked = true;
            systeme->askID = i;
            break;
        }
        else if( ui->ListeBouton[i]->etat == B_CLIQUER )
        {
            ui->ListeBouton[i]->etat = B_NORMAL;
        }
    }

    if (ui->UIfondmob == OUVERT)
    {
        for (i2 = 0 ; i2 < systeme->nbcreature ; i2++)
        {
            if ( colisionbox(&systeme->pointeur.pos, &systeme->creature[i2].bouton.pos, true) == true &&
                 systeme->creature[i2].bouton.etat == B_CLIQUER)
            {
                systeme->creature[i2].bouton.etat = B_NORMAL;
                for (i3 = 0 ; i3 < systeme->nbcreature ; i3++)
                {
                    systeme->creature[i3].actif = false;
                }
                systeme->creature[i2].actif = true;
                break;
            }
            else if( systeme->creature[i2].bouton.etat == B_CLIQUER )
            {
                systeme->creature[i2].bouton.etat = B_NORMAL;
                systeme->creature[i2].actif = false;
            }

            for (j = 0 ; j <= systeme->nbdetail ; j++)
                {//les details du mob
                    if ( colisionbox(&systeme->pointeur.pos, &systeme->creature[i2].detail[j]->pos, true) == true &&
                        systeme->creature[i2].detail[j]->etat == B_CLIQUER)
                    {
                        systeme->creature[i2].detail[j]->etat = B_NORMAL;
                        systeme->asked = true;
                        break;
                    }
                }
        }
        commandedetail(j, console, systeme);
    }

    commandebouton(i,console, systeme, ui);

}

void clic_DOWN_L(struct UI *ui, struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console)
{

    int i, j;

    for (i = 0 ; i <= ui->ListeNb ; i++)
    {
        if (ui->ListeBouton[i]->etat == B_SURVOLER)
        {
            ui->ListeBouton[i]->etat = B_CLIQUER;
        }
    }

    if (ui->UIfondmob == OUVERT)
    {
        for (i = 0 ; i < systeme->nbcreature ; i++)
        {//le nom des mobs
            if (systeme->creature[i].bouton.etat == B_SURVOLER)
            {
                systeme->creature[i].bouton.etat = B_CLIQUER;
            }
            for (j = 0 ; j <= systeme->nbdetail ; j++)
            {//les details du mob
                if (systeme->creature[i].detail[j]->etat == B_SURVOLER)
                {
                    systeme->creature[i].detail[j]->etat = B_CLIQUER;
                }
            }
        }
    }

    if(systeme->askID == DEPART &&
            systeme->projetouvert)
    {
        systeme->askID = -1;
        depart(systeme, data, console);
    }

    else if(systeme->askID == MONSTER &&
            systeme->projetouvert)
    {
        systeme->askID = -1;
        add(systeme, data, console);
    }
}

void commandebouton(int i, struct CONSOLE *console, struct DIVERSsysteme *systeme, struct UI *ui)
{
    switch (i)
    {
        case CREER:
            console->answered = false;
            console->active = true;
            say ("name of the project :", console, systeme);
            systeme->askID = CREER;
        break;

        case MAP:
            say ("name of the map to load :", console, systeme);
            console->answered = false;
            console->active = true;
            systeme->askID = MAP;
        break;

        case QUITTER:
            systeme->continuer = false;
        break;

        case CHARGER:
            console->answered = false;
            console->active = true;
            say ("name of the project :", console, systeme);
            systeme->askID = CHARGER;
        break;

        case DEPART:
            console->answered = false;
            console->active = true;
            say ("placez le joueur a ca position de depart", console, systeme);
        break;

        case MONSTER:

            ui->UIfondmob = OUVERT;
            if (systeme->nbcreature == 0)
            {
                listmob(systeme);
            }
            //console->answered = false;
            //console->active = true;
            //say ("placez le monstre a ca position de depart", console, systeme);
        break;

        case CREERMOB:
            console->answered = false;
            console->active = true;
            say("nom du mob : ", console, systeme);
            systeme->askID = CREERMOB;
        break;

        case CROIXMONSTRE:
            ui->UIfondmob = FERMER;
        break;
    }
}

void commandedetail(int j, struct CONSOLE *console, struct DIVERSsysteme *systeme)
{
    switch  (j)
    {
    case 0:
        console->answered = false;
        console->active = true;
        say ("nouveau chemin de l'image :", console, systeme);
        sprintf(console->tampon, ".png");
        console->curseur = strlen(console->tampon);
        console->curseur -=4;
        sprintf(console->TamponToCursor, console->tampon);
        console->TamponToCursor[console->curseur] = '\0';
        systeme->askID = DETAIL_IMGPATH;

        break;
    case 1:
        console->answered = false;
        console->active = true;
        say ("nouveau taux de vie :", console, systeme);
        systeme->askID = DETAIL_LIFE;
        break;
    }
}
