#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

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
    int i;

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


    for (i = 0 ; i < systeme->nbcreature ; i++)
    {
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
    }
}

void clic_UP_L(struct DIVERSsysteme *systeme, struct UI *ui, struct CONSOLE *console)
{
    int i,i2,i3;

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
    }

    switch (i)
    {
        case CREER:
            console->answered = false;
            console->active = true;
            say ("name of the project :", console, systeme);
        break;

        case MAP:
            say ("name of the map to load :", console, systeme);
            console->answered = false;
            console->active = true;
        break;

        case QUITTER:
            systeme->continuer = false;
        break;

        case CHARGER:
            console->answered = false;
            console->active = true;
            say ("name of the project :", console, systeme);
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

        case CROIXMONSTRE:
            ui->UIfondmob = FERMER;
        break;
    }
}

void clic_DOWN_L(struct UI *ui, struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console)
{

    int i;

    for (i = 0 ; i <= ui->ListeNb ; i++)
    {
        if (ui->ListeBouton[i]->etat == B_SURVOLER)
        {
            ui->ListeBouton[i]->etat = B_CLIQUER;
        }
    }

    for (i = 0 ; i < systeme->nbcreature ; i++)
    {
        if (systeme->creature[i].bouton.etat == B_SURVOLER)
        {
            systeme->creature[i].bouton.etat = B_CLIQUER;
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
        // to do
        add(systeme, data, console);
    }
}
