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
    /* creer*/
    if (colisionbox(&systeme->pointeur.pos, &ui->creer.pos, true) == true &&
        ui->creer.etat != B_CLIQUER)
    {
        ui->creer.etat = B_SURVOLER;
    }
    else if(ui->creer.etat != B_CLIQUER)
    {
        ui->creer.etat = B_NORMAL;
    }

    /* depart*/
    if (colisionbox(&systeme->pointeur.pos, &ui->depart.pos, true) == true &&
        ui->depart.etat != B_CLIQUER &&
        ui->depart.etat != B_IMPOSSIBLE)
    {
        ui->depart.etat = B_SURVOLER;
    }
    else if(ui->depart.etat != B_CLIQUER)
    {
         if (ui->depart.etat != B_IMPOSSIBLE)
        {
            ui->depart.etat = B_NORMAL;
        }
    }

    /* load map*/
    if (colisionbox(&systeme->pointeur.pos, &ui->loadmap.pos, true) == true &&
        ui->loadmap.etat != B_CLIQUER &&
        ui->loadmap.etat != B_IMPOSSIBLE)
    {
        ui->loadmap.etat = B_SURVOLER;
    }
    else if(ui->loadmap.etat != B_CLIQUER)
    {
        if (ui->loadmap.etat != B_IMPOSSIBLE)
        {
            ui->loadmap.etat = B_NORMAL;
        }
    }

    /* charger*/
    if (colisionbox(&systeme->pointeur.pos, &ui->charger.pos, true) == true &&
        ui->charger.etat != B_CLIQUER)
    {
        ui->charger.etat = B_SURVOLER;
    }
    else if(ui->charger.etat != B_CLIQUER)
    {
        ui->charger.etat = B_NORMAL;
    }

    /* enregistrer*/
    if (colisionbox(&systeme->pointeur.pos, &ui->enregistrer.pos, true) == true &&
        ui->enregistrer.etat != B_CLIQUER &&
        ui->enregistrer.etat != B_IMPOSSIBLE)
    {
        ui->enregistrer.etat = B_SURVOLER;
    }
    else if(ui->enregistrer.etat != B_CLIQUER)
    {
        if (ui->enregistrer.etat != B_IMPOSSIBLE)
        {
            ui->enregistrer.etat = B_NORMAL;
        }
    }

    /*quitter*/
    if (colisionbox(&systeme->pointeur.pos, &ui->quitter.pos, true) == true &&
        ui->quitter.etat != B_CLIQUER)
    {
        ui->quitter.etat = B_SURVOLER;
    }
    else if (ui->quitter.etat != B_CLIQUER)
    {
    ui->quitter.etat = B_NORMAL;
    }
}

void clic_UP_L(struct DIVERSsysteme *systeme, struct UI *ui, struct CONSOLE *console)
{
    /*shootbox*/
    if (colisionbox(&systeme->pointeur.pos, &console->shooton.pos, true))
    {
        console->active = true;
    }
    else
    {
        console->active = false;
    }

    /* load map */
    if (colisionbox(&systeme->pointeur.pos, &ui->loadmap.pos, true) == true &&
        ui->loadmap.etat == B_CLIQUER)
    {
        ui->loadmap.etat = B_NORMAL;
        say ("name of the map to load :", console, systeme);
        systeme->asked = true;
        systeme->askID = MAP;
        console->answered = false;
        console->active = true;
    }
    else if(ui->loadmap.etat == B_CLIQUER)
    {
        ui->loadmap.etat = B_NORMAL;
    }

     /* creer */
    if (colisionbox(&systeme->pointeur.pos, &ui->creer.pos, true) == true &&
        ui->creer.etat == B_CLIQUER)
    {
        ui->creer.etat = B_NORMAL;
        systeme->asked = true;
        systeme->askID = CREER;
        console->answered = false;
        console->active = true;

        say ("name of the project :", console, systeme);
    }
    else if(ui->creer.etat == B_CLIQUER)
    {
        ui->creer.etat = B_NORMAL;
    }

     /* charger */
    if (colisionbox(&systeme->pointeur.pos, &ui->charger.pos, true) == true &&
        ui->charger.etat == B_CLIQUER)
    {
        ui->charger.etat = B_NORMAL;
        systeme->asked = true;
        systeme->askID = CHARGER;
        console->answered = false;
        console->active = true;

        say ("name of the project :", console, systeme);
    }
    else if(ui->charger.etat == B_CLIQUER)
    {
        ui->charger.etat = B_NORMAL;
    }

     /* depart */
    if (colisionbox(&systeme->pointeur.pos, &ui->depart.pos, true) == true &&
        ui->depart.etat == B_CLIQUER)
    {
        ui->depart.etat = B_NORMAL;
        systeme->asked = true;
        systeme->askID = DEPART;
        console->answered = false;
        console->active = true;

        say ("placez le joueur a ca position de depart", console, systeme);
    }
    else if(ui->depart.etat == B_CLIQUER)
    {
        ui->depart.etat = B_NORMAL;
    }

     /* enregistrer */
    if (colisionbox(&systeme->pointeur.pos, &ui->enregistrer.pos, true) == true &&
        ui->enregistrer.etat == B_CLIQUER)
    {
        ui->enregistrer.etat = B_NORMAL;
        systeme->asked = true;
        systeme->askID = ENREGISTRER;
        console->answered = false;
        console->active = true;
    }
    else if(ui->enregistrer.etat == B_CLIQUER)
    {
        ui->enregistrer.etat = B_NORMAL;
    }

    /* quitter*/
    if (colisionbox(&systeme->pointeur.pos, &ui->quitter.pos, true) == true &&
        ui->quitter.etat == B_CLIQUER)
    {
        ui->quitter.etat = B_NORMAL;
        systeme->continuer = false;
    }
    else if(ui->quitter.etat == B_CLIQUER)
    {
        ui->quitter.etat = B_NORMAL;
    }
}

void clic_DOWN_L(struct UI *ui, struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console)
{
    /*creer*/
    if (ui->creer.etat == B_SURVOLER){
        ui->creer.etat = B_CLIQUER;
    }
     /*charger*/
   else if (ui->charger.etat == B_SURVOLER){
        ui->charger.etat = B_CLIQUER;
    }
     /*loadmap*/
    else if (ui->loadmap.etat == B_SURVOLER){
        ui->loadmap.etat = B_CLIQUER;
    }
     /*enregistrer*/
    else if (ui->enregistrer.etat == B_SURVOLER){
        ui->enregistrer.etat = B_CLIQUER;
    }
    /*quitter*/
    else if (ui->quitter.etat == B_SURVOLER){
        ui->quitter.etat = B_CLIQUER;
    }
    /*depart*/
    else if (ui->depart.etat == B_SURVOLER){
        ui->depart.etat = B_CLIQUER;
    }

    else if(systeme->askID == DEPART &&
            systeme->projetouvert)
    {
        systeme->askID = -1;
        depart(systeme, data, console);
    }
}
