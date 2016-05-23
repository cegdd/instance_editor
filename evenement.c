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

extern int screenh, screenw;

void boucleevent (struct DIVERSsysteme *systeme, struct UI *ui, struct CONSOLE *console)
{
	while(SDL_PollEvent(&systeme->evenement) == 1)
	{
		switch(systeme->evenement.type)
		{
		    case SDL_MOUSEBUTTONDOWN:
                if( systeme->evenement.button.button == SDL_BUTTON_LEFT )
                {
                    clic_DOWN_L(ui);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if( systeme->evenement.button.button == SDL_BUTTON_LEFT )
                {
                    clic_UP_L(systeme, ui, console);
                }
                break;
            case SDL_KEYUP:
                 intputtexte(systeme, console);
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
    /* creer*/
    if (colisionbox(&systeme->pointeur.pos, &ui->creer.pos, true) == true &&
        ui->creer.etat == B_CLIQUER)
    {
        ui->creer.etat = B_NORMAL;
        say ("map path to load :", console, systeme);
    }
    else if(ui->creer.etat == B_CLIQUER)
    {
        ui->creer.etat = B_NORMAL;
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

void clic_DOWN_L(struct UI *ui)
{
    /*creer*/
    if (ui->creer.etat == B_SURVOLER){
        ui->creer.etat = B_CLIQUER;
    }
    /*quitter*/
    if (ui->quitter.etat == B_SURVOLER){
        ui->quitter.etat = B_CLIQUER;
    }
}
