#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bouton.h"
#include "core.h"
#include "ui.h"
#include "colision.h"
#include "systeme.h"
#include "editeur.h"
#include "save.h"

void BT_pointeur(struct DIVERSsysteme *systeme, struct UI *ui)
{
    int i;

    for (i = 0 ; i <= ui->ListeNb ; i++)
    {
        if ( colisionbox(&systeme->pointeur.pos, &ui->ListeBouton[i].pos, true) == true &&
            ui->ListeBouton[i].etat != B_CLIQUER &&
            ui->ListeBouton[i].etat != B_IMPOSSIBLE)
            {
                ui->ListeBouton[i].etat = B_SURVOLER;
            }
        else if ( ui->ListeBouton[i].etat != B_CLIQUER &&
                  ui->ListeBouton[i].etat != B_IMPOSSIBLE )
        {
            ui->ListeBouton[i].etat = B_NORMAL;
        }
    }
}

int BT_up(struct DIVERSsysteme *systeme, struct UI *ui)
{
    int i;
    for (i = 0 ; i <= ui->ListeNb ; i++)
    {
        if ( colisionbox(&systeme->pointeur.pos, &ui->ListeBouton[i].pos, true) == true &&
             ui->ListeBouton[i].etat == B_CLIQUER)
        {
            ui->ListeBouton[i].etat = B_NORMAL;
            systeme->asked = true;
            return i;
        }
        else if( ui->ListeBouton[i].etat == B_CLIQUER )
        {
            ui->ListeBouton[i].etat = B_NORMAL;
        }
    }
    return i;
}

void BT_down(struct UI *ui)
{
    int i;

    for (i = 0 ; i <= ui->ListeNb ; i++)
    {
        if (ui->ListeBouton[i].etat == B_SURVOLER)
        {
            ui->ListeBouton[i].etat = B_CLIQUER;
        }
    }
}

void BT_event(int i, struct CONSOLE *console, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data)
{
    switch (i)
    {
        case 3:
            systeme->askID = i;
        break;
        case 0:
            console->answered = false;
            console->active = true;
            say ("name of the project :", console, systeme);
            systeme->askID = i;
        break;

        case 4:
            say ("name of the map to load :", console, systeme);
            console->answered = false;
            console->active = true;
            systeme->askID = i;
        break;

        case 1:
            systeme->continuer = false;
        break;

        case 2:
            console->answered = false;
            console->active = true;
            say ("name of the project :", console, systeme);
            systeme->askID = i;
        break;

        case 5:
            console->answered = false;
            console->active = true;
            systeme->askID = i;
            say ("placez le joueur a ca position de depart", console, systeme);
        break;

        case 6://creature
            UI_setslidestate(UI_listmob, ui);
            console->answered = false;
            console->active = true;
            ESP_updateUI(0, systeme, ui);
        break;

        case 8:
            console->answered = false;
            console->active = true;
            say("nom du mob : ", console, systeme);
            systeme->askID = i;
        break;

        case 9:
            if (UI_getslidestate(ui) == UI_listmob)
            {
                ESP_delete(systeme, data);
                ESP_refreshmob(systeme);
            }
            else if (UI_getslidestate(ui) == UI_detail)
            {
                data->mob[data->mob_selected].actif = false;
                UI_setslidestate(UI_close, ui);
            }
        break;

        case 7:
            UI_setslidestate(UI_close, ui);
            break;
        case 11:
        console->answered = false;
        console->active = true;
        say ("nouveau chemin de l'image :", console, systeme);
        sprintf(console->tampon, ".png");
        console->curseur = strlen(console->tampon);
        console->curseur -=4;
        sprintf(console->TamponToCursor, console->tampon);
        console->TamponToCursor[console->curseur] = '\0';
        systeme->askID = i;

        break;
    case 12:
        console->answered = false;
        console->active = true;
        say ("nouveau taux de vie :", console, systeme);
        systeme->askID = i;
        break;
    case 13:
        console->answered = false;
        console->active = true;
        say ("nouveau rayon d'attaque", console, systeme);
        systeme->askID = i;
        break;
    case 14:
        console->answered = false;
        console->active = true;
        say ("nouveau taux de vitesse", console, systeme);
        systeme->askID = i;
        break;
    }
}

void BT_update_loop(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data)
{
    if(systeme->askID == 4)
    {
        loadingmap(console, systeme, data);
    }
    else if(systeme->askID == 0)
    {
        createproject(console, systeme, data);
        ui->ListeBouton[0].etat = B_IMPOSSIBLE;
        ui->ListeBouton[2].etat = B_IMPOSSIBLE;
    }
    else if(systeme->askID == 3)
    {
        saveproject(console, systeme, data);
    }
    else if(systeme->askID == 2)
    {
        loadproject(console, systeme, data);
        ui->ListeBouton[0].etat = B_IMPOSSIBLE;
        ui->ListeBouton[2].etat = B_IMPOSSIBLE;
    }
    else if(systeme->askID == 8)
    {
        ESP_create(console, systeme);
        ESP_refreshmob(systeme);
    }
    else if(systeme->askID == 11)
    {
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            ESP_setimgpath(console->lastanswer, systeme->activecreature, systeme);
            ESP_refreshmob(systeme);
            ESP_updateUI(systeme->activecreature, systeme, ui);
        }
    }
    else if(systeme->askID == 12)
    {
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            ESP_setlife(atoi(console->lastanswer), systeme->activecreature, systeme);
            ESP_refreshmob(systeme);
            ESP_updateUI(systeme->activecreature, systeme, ui);
        }
    }
    else if(systeme->askID == 13)
    {
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;


            setboutontexte(console->lastanswer, 13, ui, systeme);
            ESP_refreshmob(systeme);
            ESP_updateUI(systeme->activecreature, systeme, ui);
        }
    }
    else if(systeme->askID == 14)
    {
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;


            setboutontexte(console->lastanswer, 14, ui, systeme);
            ESP_refreshmob(systeme);
            ESP_updateUI(systeme->activecreature, systeme, ui);
        }
    }
}
