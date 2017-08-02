#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui.h"
#include "colision.h"
#include "console.h"
#include "data.h"
#include "systeme.h"
#include "espece.h"
#include "editeur.h"
#include "save.h"

void BT_pointeur(struct DIVERSsysteme *systeme, struct UI *ui)
{
    int i;

    for (i = 0 ; i <= ui->ListeNb ; i++)
    {
        if ( colisionbox(&systeme->pointeur.pos, &ui->ListeBouton[i].pos, true) == true &&
            ui->ListeBouton[i].etat != B_CLIQUER &&
            ui->ListeBouton[i].etat != B_IMPOSSIBLE &&
            isInTheGoodPanel(ui, i) == true)
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
            systeme->activecreature = -1;
            UI_updateESP(0, systeme, ui);
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
        say ("nouveau rayon de vision", console, systeme);
        systeme->askID = i;
        break;
    case 14:
        console->answered = false;
        console->active = true;
        say ("nouveau taux de vitesse", console, systeme);
        systeme->askID = i;
        break;
    case 15:
        console->answered = false;
        console->active = true;
        say ("nouveau taux de degat par seconde", console, systeme);
        systeme->askID = i;
        break;
    case 16:
        console->answered = false;
        console->active = true;
        say ("nouveau rayon d'attaque", console, systeme);
        systeme->askID = i;
        break;
    case 17:
        console->answered = false;
        console->active = true;
        say ("nouvelle position en x", console, systeme);
        systeme->askID = i;
        break;
    case 18:
        console->answered = false;
        console->active = true;
        say ("nouvelle position en y", console, systeme);
        systeme->askID = i;
        break;
    case 19:
        console->answered = false;
        console->active = true;
        say ("nouvelle échelle", console, systeme);
        systeme->askID = i;
        break;
    case 20:
        console->answered = false;
        console->active = true;
        say ("nouvel angle", console, systeme);
        systeme->askID = i;
        break;
    case 21:
        if (systeme->pathmode == true)
        {
            say ("pathmode désactivé", console, systeme);
            systeme->pathmode = false;
        }
        else
        {
            say ("pathmode activé", console, systeme);
            systeme->pathmode = true;
        }
        break;
    case 22:
        console->answered = false;
        console->active = true;
        say ("nouveau temps entre dégats", console, systeme);
        systeme->askID = i;
        break;
    }
}

void BT_update_loop(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data)
{

    switch (systeme->askID)
    {
    case 0:
        createproject(console, systeme, data);
        ui->ListeBouton[0].etat = B_IMPOSSIBLE;
        ui->ListeBouton[2].etat = B_IMPOSSIBLE;
        break;
    case 2:
        loadproject(console, systeme, data, ui);
        ui->ListeBouton[0].etat = B_IMPOSSIBLE;
        ui->ListeBouton[2].etat = B_IMPOSSIBLE;
        break;
    case 3:
        saveproject(console, systeme, data, ui);
        break;
    case 4:
        loadingmap(console, systeme, data);
        break;
    case 8:
        ESP_create(console, systeme);
        ESP_refreshmob(systeme);
        break;
    case 11:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            ESP_setimgpath(console->lastanswer, systeme->activecreature, systeme);
            ESP_refreshmob(systeme);
            UI_updateESP(systeme->activecreature, systeme, ui);
        }
        break;
    case 12:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            ESP_setlife(atoi(console->lastanswer), systeme->activecreature, systeme);
            ESP_refreshmob(systeme);
            UI_updateESP(systeme->activecreature, systeme, ui);
        }
        break;
    case 13:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            systeme->creature[systeme->activecreature].Rvision = atoi(console->lastanswer);
            ESP_refreshmob(systeme);
            UI_updateESP(systeme->activecreature, systeme, ui);
        }
        break;
    case 14:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            systeme->creature[systeme->activecreature].vitesse = atoi(console->lastanswer);
            UI_updateESP(systeme->activecreature, systeme, ui);
        }
        break;
    case 15:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;


            systeme->creature[systeme->activecreature].dps = atoi(console->lastanswer);
            UI_updateESP(systeme->activecreature, systeme, ui);
        }
        break;
    case 16:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;


            systeme->creature[systeme->activecreature].Ratk = atoi(console->lastanswer);
            UI_updateESP(systeme->activecreature, systeme, ui);
        }
        break;
    case 17:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            data->mob[data->mob_selected].monstre.translation.x = atoi(console->lastanswer);

            UI_updateMOB(data->mob_selected, systeme, ui, data);
        }
        break;
    case 18:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            data->mob[data->mob_selected].monstre.translation.y = atoi(console->lastanswer);

            UI_updateMOB(data->mob_selected, systeme, ui, data);
        }
        break;
    case 19:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            data->mob[data->mob_selected].scale = atof(console->lastanswer);

            UI_updateMOB(data->mob_selected, systeme, ui, data);
        }
        break;
    case 20:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            data->mob[data->mob_selected].angle = atoi(console->lastanswer);

            UI_updateMOB(data->mob_selected, systeme, ui, data);
        }
        break;
    case 22:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;


            systeme->creature[systeme->activecreature].hitlaps = atoi(console->lastanswer);
            UI_updateESP(systeme->activecreature, systeme, ui);
        }
        break;
    }
}

bool isInTheGoodPanel(struct UI *ui, int index)
{
    if (ui->ListeBouton[index].flag == B_detail && ui->slidestate == UI_detail)
    {
        return true;
    }
    else if (ui->ListeBouton[index].flag == B_liste && ui->slidestate == UI_listmob)
    {
        return true;
    }
    else if (ui->ListeBouton[index].flag == B_none)
    {
        return true;
    }
    return false;
}
