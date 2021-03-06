#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"
#include <string.h>

#include "LIBcegdd_ui.h"

#include "systeme.h"
#include "ui.h"
#include "evenement.h"
#include "clavier.h"
#include "editeur.h"
#include "path.h"

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
                break;
		    case SDL_MOUSEBUTTONDOWN:
                if( systeme->evenement.button.button == SDL_BUTTON_LEFT )
                {
                    clic_DOWN_L(ui, systeme, data, console);
                }
                else if( systeme->evenement.button.button == SDL_BUTTON_RIGHT )
                {
                    clic_DOWN_R(ui, systeme, data, console);
                }
                else if( systeme->evenement.button.button == SDL_BUTTON_MIDDLE )
                {
                    systeme->moletteactif = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if( systeme->evenement.button.button == SDL_BUTTON_LEFT )
                {
                    clic_UP_L(systeme, ui, console, data);
                }
                else if( systeme->evenement.button.button == SDL_BUTTON_MIDDLE )
                {
                    systeme->moletteactif = false;
                }
                break;
            case SDL_KEYDOWN:
                if (console->active)
                {
                    intputtextedown(systeme);
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

void pointeur(struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data)
{
    int i;

    CEGDD_UI_BT_pointeur(systeme->pointeur.pos, ui->ListeBouton, &ui->ListeNb, ui->slidestate);

    if (UI_getslidestate(ui) == SLIDE_ESPECE)
    {
        for (i = 0 ; i < systeme->NBespece ; i++)
        {//le nom du mob
            if ( CEGDD_UI_colisionbox(&systeme->pointeur.pos, ESP_getboutonpos(i, systeme), true) == true &&
                ESP_getboutonstate(i, systeme) != B_CLIQUER &&
                ESP_getboutonstate(i, systeme) != B_IMPOSSIBLE &&
                ESP_getboutonstate(i, systeme) != B_INUSE)
                {
                    ESP_setboutonstate(B_SURVOLER, i, systeme);
                }
            else if (   ESP_getboutonstate(i, systeme) != B_CLIQUER &&
                        ESP_getboutonstate(i, systeme) != B_IMPOSSIBLE &&
                        ESP_getboutonstate(i, systeme) != B_INUSE )
            {
                ESP_setboutonstate(B_NORMAL, i, systeme);
            }
            else if (   ESP_getboutonstate(i, systeme) == B_INUSE &&
                        systeme->ActiveEspece != i)
            {
                systeme->ActiveEspece = i;
            }
        }
    }
    for(i = 0 ; i < data->nbmonstre ; i++)
    {
        if(data->mob[i].actif == true)
        {
            if (CEGDD_UI_colisionbox(&systeme->pointeur.pos, &data->mob[i].monstre.pict.pos, true) == true)
            {
                data->mob[i].state = B_SURVOLER;
            }
        }
    }
}

void clic_UP_L(struct DIVERSsysteme *systeme, struct UI *ui, struct CONSOLE *console, struct DATA *data)
{
    int i = 0,i2;

    /*shootbox*/
    if (CEGDD_UI_colisionbox(&systeme->pointeur.pos, &console->shooton.pos, true))
    {
        console->active = true;
    }
    else
    {
        console->active = false;
    }

    i = CEGDD_UI_BT_up(systeme->pointeur.pos, ui->ListeBouton, &ui->ListeNb, &systeme->asked);

    if (UI_getslidestate(ui) == SLIDE_ESPECE)
    {
        for (i2 = 0 ; i2 < systeme->NBespece ; i2++)
        {
            if ( CEGDD_UI_colisionbox(&systeme->pointeur.pos, ESP_getboutonpos(i2, systeme), true) == true &&
                 ESP_getboutonstate(i2, systeme) == B_CLIQUER)
            {
                int i3;
                for (i3 = 0 ; i3 < systeme->NBespece ; i3++)
                {
                    ESP_setboutonstate(B_NORMAL, i3, systeme);
                }
                systeme->ActiveEspece = i2;
                ESP_setboutonstate(B_INUSE, systeme->ActiveEspece, systeme);
                UI_updateESP(i2, systeme, ui);
                break;
            }
        }

       gestion_coche(&ui->aggressif_pos, &ui->aggressif_state[systeme->ActiveEspece], ui, systeme);

        if (systeme->tookmob == true)
        {
            add(systeme, data, console);
            systeme->tookmob = false;
        }
    }
    else if (UI_getslidestate(ui) == SLIDE_DETAIL)
    {
        gestion_coche(&ui->fixe_pos, &ui->fixe_state[data->mob_selected], ui, systeme);
        gestion_coche(&ui->loop_pos, &ui->loop_state[data->mob_selected], ui, systeme);
        if (UI_is_inside(ui, systeme, console) == false && systeme->pathmode == true)
        {
            PATH_add(&data->mob[data->mob_selected].path, systeme->pointeur.pos.x, systeme->pointeur.pos.y, data);
        }
    }
     BT_event(i,console, systeme, ui, data);

     if (UI_is_inside(ui, systeme, console) == false)
     {
         gestion_survol_mob (systeme, ui, data);
     }
}

void clic_DOWN_L(struct UI *ui, struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console)
{

    int i;

    CEGDD_UI_BT_down(ui->ListeBouton, &ui->ListeNb);

    if (UI_getslidestate(ui) == SLIDE_ESPECE)
    {
        for (i = 0 ; i < systeme->NBespece ; i++)
        {//le nom des mobs
            if (ESP_getboutonstate(i, systeme) == B_SURVOLER)
            {
                ESP_setboutonstate(B_CLIQUER, i, systeme);
            }
        }
        if (CEGDD_UI_colisionbox(&systeme->pointeur.pos, &ui->posthumbcreature, true) == true)
        {
            systeme->tookmob = true;
        }
    }

    if(systeme->askID == 5 &&
            systeme->projetouvert)
    {
        systeme->askID = -1;
        depart(systeme, data, console);
    }
}

void clic_DOWN_R(struct UI *ui, struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console)
{
    if (UI_getslidestate(ui) == SLIDE_DETAIL)
    {
        if (UI_is_inside(ui, systeme, console) == false && systeme->pathmode == true)
        {
            PATH_remove(&data->mob[data->mob_selected].path);
        }
    }
}



void gestion_coche (struct SDL_Rect *pos, bool *state, struct UI *ui, struct DIVERSsysteme *systeme)
{
    if (CEGDD_UI_colisionbox(&systeme->pointeur.pos, pos, true) == true )
    {
        if (*state == false)
        {
            *state = true;
            ui->ListeBouton[13].etat = B_NORMAL;
        }
        else
        {
            *state = false;
            ui->ListeBouton[13].etat = B_IMPOSSIBLE;
        }
    }
}

void gestion_survol_mob (struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data)
{
    int i, i2;
    for(i = 0 ; i < data->nbmonstre ; i++)
    {
        if(data->mob[i].actif == true)
        {
            if (data->mob[i].state == B_SURVOLER &&
                CEGDD_UI_colisionbox(&systeme->pointeur.pos, &data->mob[i].monstre.pict.pos, true) == true)
            {
                UI_setslidestate(SLIDE_DETAIL, ui);
                systeme->pathmode = false;
                data->mob[i].state = B_NORMAL;
                for(i2 = 0 ; i2 < data->nbmonstre ; i2++)
                {
                    data->mob[i2].selected = false;
                }
                data->mob[i].selected = true;
                data->mob_selected = i;

                UI_updateMOB(data->mob_selected , systeme, ui, data);
            }
        }
    }
}
