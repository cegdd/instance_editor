#include "bouton.h"
#include "core.h"
#include "ui.h"
#include "colision.h"

void BT_pointeur(struct DIVERSsysteme *systeme, struct UI *ui)
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
}

int BT_up(struct DIVERSsysteme *systeme, struct UI *ui)
{
    int i;
    for (i = 0 ; i <= ui->ListeNb ; i++)
    {
        if ( colisionbox(&systeme->pointeur.pos, &ui->ListeBouton[i]->pos, true) == true &&
             ui->ListeBouton[i]->etat == B_CLIQUER)
        {
            ui->ListeBouton[i]->etat = B_NORMAL;
            systeme->asked = true;
            return i;
        }
        else if( ui->ListeBouton[i]->etat == B_CLIQUER )
        {
            ui->ListeBouton[i]->etat = B_NORMAL;
        }
    }
    return i;
}

void BT_down(struct UI *ui)
{
    int i;

    for (i = 0 ; i <= ui->ListeNb ; i++)
    {
        if (ui->ListeBouton[i]->etat == B_SURVOLER)
        {
            ui->ListeBouton[i]->etat = B_CLIQUER;
        }
    }
}
