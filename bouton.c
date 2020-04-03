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
        case B_SAVE_PROJECT:
            saveproject(console, systeme, data, ui);
        break;
        case B_NEW_PROJECT:
            console->answered = false;
            console->active = true;
            say ("name of the project to create:", console, systeme);
            systeme->askID = i;
        break;

        case B_LOAD_MAP:
            say ("name of the map to load :", console, systeme);
            console->answered = false;
            console->active = true;
            systeme->askID = i;
        break;

        case B_QUITTER:
            systeme->continuer = false;
        break;

        case B_LOAD_PROJECT:
            console->answered = false;
            console->active = true;
            say ("name of the project to load:", console, systeme);
            systeme->askID = i;
        break;

        case B_PLAYER_START:
            console->answered = false;
            console->active = true;
            systeme->askID = i;
            say ("placez le joueur a ca position de depart", console, systeme);
        break;

        case B_SLIDE_CREATURE://creature
            UI_setslidestate(SLIDE_ESPECE, ui);
            console->answered = false;
            console->active = true;
            if(systeme->NBespece > 0)
            {
                systeme->ActiveEspece = 0;
            }
            systeme->ActiveEspece = -1;
            UI_updateESP(0, systeme, ui);
        break;

        case B_NEW_CREATURE:
            console->answered = false;
            console->active = true;
            say("nom du mob : ", console, systeme);
            systeme->askID = i;
        break;

        case B_DELETE_CREATURE_MOB:
            if (systeme->NBespece != 0)
            {
                if (UI_getslidestate(ui) == SLIDE_ESPECE)
                {
                    ESP_delete(systeme, data);
                    ESP_refreshmob(systeme);
                }
                else if (UI_getslidestate(ui) == SLIDE_DETAIL)
                {
                    data->mob[data->mob_selected].actif = false;
                    UI_setslidestate(SLIDE_CLOSE, ui);
                }
            }
        break;

        case B_SLIDE_CLOSE:
            UI_setslidestate(SLIDE_CLOSE, ui);
            break;
        case 11:
        console->answered = false;
        console->active = true;
        say ("nouveau chemin de l'image :", console, systeme);
        sprintf(console->tampon, ".png");
        console->curseur = strlen(console->tampon);
        console->curseur -=4;
        strcpy(console->TamponToCursor, console->tampon);
        //sprintf(console->TamponToCursor, console->tampon);
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
    case B_NEW_PROJECT:
        createproject(console, systeme, data);
        ui->ListeBouton[0].etat = B_IMPOSSIBLE;
        ui->ListeBouton[2].etat = B_IMPOSSIBLE;
        break;
    case B_LOAD_PROJECT:
        if( loadproject(console, systeme, data, ui) == EXIT_SUCCESS)
        {
            ui->ListeBouton[0].etat = B_IMPOSSIBLE;
            ui->ListeBouton[2].etat = B_IMPOSSIBLE;
        }
        break;
    case B_LOAD_MAP:
        loadingmap(console, systeme, data);
        break;
    case B_NEW_CREATURE:
        ESP_create(console, systeme);
        ESP_refreshmob(systeme);
        UI_updateESP(systeme->ActiveEspece, systeme, ui);
        break;
    case 11:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            ESP_setimgpath(console->lastanswer, systeme->ActiveEspece, systeme);
            ESP_refreshmob(systeme);
            UI_updateESP(systeme->ActiveEspece, systeme, ui);
        }
        break;
    case 12:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            ESP_setlife(atoi(console->lastanswer), systeme->ActiveEspece, systeme);
            ESP_refreshmob(systeme);
            UI_updateESP(systeme->ActiveEspece, systeme, ui);
        }
        break;
    case 13:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            systeme->creature[systeme->ActiveEspece].Rvision = atoi(console->lastanswer);
            ESP_refreshmob(systeme);
            UI_updateESP(systeme->ActiveEspece, systeme, ui);
        }
        break;
    case 14:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;

            systeme->creature[systeme->ActiveEspece].vitesse = atoi(console->lastanswer);
            UI_updateESP(systeme->ActiveEspece, systeme, ui);
        }
        break;
    case 15:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;


            systeme->creature[systeme->ActiveEspece].dps = atoi(console->lastanswer);
            UI_updateESP(systeme->ActiveEspece, systeme, ui);
        }
        break;
    case 16:
        if (console->answered)
        {
            systeme->asked = true;
            console->answered = false;


            systeme->creature[systeme->ActiveEspece].Ratk = atoi(console->lastanswer);
            UI_updateESP(systeme->ActiveEspece, systeme, ui);
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


            systeme->creature[systeme->ActiveEspece].hitlaps = atoi(console->lastanswer);
            UI_updateESP(systeme->ActiveEspece, systeme, ui);
        }
        break;
    }
}

bool isInTheGoodPanel(struct UI *ui, int index)
{
    if (ui->ListeBouton[index].flag == B_detail && ui->slidestate == SLIDE_DETAIL)
    {
        return true;
    }
    else if (ui->ListeBouton[index].flag == B_liste && ui->slidestate == SLIDE_ESPECE)
    {
        return true;
    }
    else if (ui->ListeBouton[index].flag == B_none)
    {
        return true;
    }
    return false;
}
