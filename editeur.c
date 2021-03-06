#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "ui.h"
#include "evenement.h"
#include "systeme.h"
#include "editeur.h"

#include <LIBcegdd_ui.h>

extern int screenh, screenw;

int editeur(struct DIVERSsysteme *systeme)
{
    struct UI ui;
    struct CONSOLE console;
    struct DATA data;
    initui(&ui, systeme);
    initconsole(&console, systeme);
    initdata(&data, systeme);

    while(systeme->continuer)
    {
        boucleevent(systeme, &ui, &console, &data);
        pointeur(systeme, &ui, &data);

        if (systeme->asked)
        {
            BT_update_loop(&console, systeme, &ui, &data);
        }

        affichage(&console, systeme, &ui, &data);

        SDL_Delay(10);
    }
    return EXIT_SUCCESS;
}

void affichage(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data)
{
    int index;

    if (glIsTexture(data->map.texture))
    {
        data->map.pos.x = data->map.x + systeme->origine.x;
        data->map.pos.y = data->map.y + systeme->origine.y;
        CEGDD_UI_draw_pict(&data->map);
    }

    if (data->joueuractif)
    {
        CEGDD_UI_draw_hookpict(&data->joueur, &data->map.pos);
    }

    for(index = 0 ; index < data->nbmonstre ; index++)
    {
        if(data->mob[index].actif == true)
        {
            data->mob[index].monstre.pict.pos.w = data->mob[index].old.w * data->mob[index].scale;
            data->mob[index].monstre.pict.pos.h = data->mob[index].old.h * data->mob[index].scale;
            if(data->mob[index].selected == false)
            {
                CEGDD_UI_turn_draw_hookpict(data->mob[index].angle, &data->mob[index].monstre, &data->map.pos);
            }
            else
            {
                turn_draw_hookpict_selected(data->mob[index].angle, &data->mob[index].monstre, &data->map.pos);
            }
        }
    }

    if (systeme->projetouvert == true && ui->ListeBouton[4].etat == B_IMPOSSIBLE)
        {
            ui->ListeBouton[4].etat = B_NORMAL;
            ui->ListeBouton[3].etat = B_NORMAL;
            ui->ListeBouton[5].etat = B_NORMAL;
            ui->ListeBouton[6].etat = B_NORMAL;
        }

        CEGDD_UI_draw_button(&ui->ListeBouton[0]);
        CEGDD_UI_draw_button(&ui->ListeBouton[1]);
        CEGDD_UI_draw_button(&ui->ListeBouton[3]);
        CEGDD_UI_draw_button(&ui->ListeBouton[4]);
        CEGDD_UI_draw_button(&ui->ListeBouton[2]);
        CEGDD_UI_draw_button(&ui->ListeBouton[5]);
        CEGDD_UI_draw_button(&ui->ListeBouton[6]);

        if (UI_getslidestate(ui) != SLIDE_CLOSE)
        {
            UI_drawslide(ui, systeme, data);
        }

        CEGDD_UI_draw_pict(&console->console);
        if (console->active)
        {
            CEGDD_UI_draw_pict(&console->shooton);
        }
        else
        {
            CEGDD_UI_draw_pict(&console->shootoff);
        }
        for(index = 0 ; index < 10 ; index++)
        {
            CEGDD_UI_draw_pict(&console->texte[index].img);
        }
        if(console->tampon[0] != '\0')

        {
        console->ecris.img.texture = CEGDD_UI_imprime(console->tampon, screenw, &systeme->blanc, systeme->police1, &console->ecris.lenght, &console->ecris.high);
        console->ecris.img.pos.w = console->ecris.lenght;

        CEGDD_UI_draw_pict(&console->ecris.img);
        }


        if((SDL_GetTicks()/1000) % 2 == 0)
        {
            TTF_SizeText(systeme->police1,console->TamponToCursor,&console->LenToCursor,NULL);
            console->cursor.pos.x = console->ecris.img.pos.x + console->LenToCursor;

            CEGDD_UI_draw_pict(&console->cursor);
        }

        if (systeme->tookmob == true)
        {
            CEGDD_UI_setPos4(&systeme->temp,
                    systeme->pointeur.pos.x,
                    systeme->pointeur.pos.y + systeme->pointeur.pos.h,
                    ESP_getwidth(systeme->ActiveEspece, systeme),
                    ESP_gethight(systeme->ActiveEspece, systeme));
            CEGDD_UI_draw(ESP_gettexture(systeme->ActiveEspece, systeme), &systeme->temp);
        }

        glFlush();
        SDL_GL_SwapWindow(systeme->screen);

        /*effacage de l'�cran*/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
        SDL_GetMouseState(&systeme->pointeur.pos.x, &systeme->pointeur.pos.y);
        /*reverse for OpenGL*/
        systeme->pointeur.pos.y = (systeme->pointeur.pos.y - screenh + systeme->pointeur.pos.h) * -1;

}

void loadingmap(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data)
{
    if (console->answered)
    {
        systeme->asked = false;
        char temp[1132];
        console->answered = false;
        systeme->asked = false;

        sprintf(data->projectmap, "%s", console->lastanswer);
        sprintf(temp, "rs/map/%s.png", console->lastanswer);
        data->map.texture = CEGDD_UI_loadTextureandsize(temp, &data->map.pos);
        data->map.x = data->map.pos.x;
        data->map.y = data->map.pos.y;


        if(glIsTexture(data->map.texture))
        {
            sprintf(temp, "texture successfuly loaded %d x %d", data->map.pos.w, data->map.pos.h);
            say (temp, console, systeme);
        }
        else
        {
            say("ERROR : texture not successfuly loaded", console, systeme);
        }
    }
}

void loadingknownmap(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data, char *name)
{
    systeme->asked = false;
    char temp[128];
    console->answered = false;
    systeme->asked = false;

    sprintf(data->projectmap, "%s", name);
    sprintf(temp, "rs/map/%s.png", name);
    data->map.texture = CEGDD_UI_loadTextureandsize(temp, &data->map.pos);
    //data->map.x = data->map.pos.x;
    //data->map.y = data->map.pos.y;


    if(glIsTexture(data->map.texture))
    {
        sprintf(temp, "texture successfuly loaded %d x %d", data->map.pos.w, data->map.pos.h);
        say (temp, console, systeme);
    }
    else
    {
        say("ERROR : texture not successfuly loaded", console, systeme);
    }
}

void createproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data)
{
    if (console->answered)
    {
        char temp2[1132];

        systeme->asked = false;
        console->answered = false;
        systeme->asked = false;

        snprintf(data->projectname, 63, "%s", console->lastanswer);
        sprintf(temp2, "projet \"%s\" cr�e\n", data->projectname);
        say(temp2, console, systeme);

        systeme->projetouvert = true;
    }
}

void depart(struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console)
{

    data->joueuractif = true;
    data->joueur.translation.x = (systeme->evenement.motion.x - data->joueur.pict.pos.w/2) - data->map.pos.x;
    data->joueur.translation.y = (screenh - systeme->evenement.motion.y - data->joueur.pict.pos.h/2) - data->map.pos.y;
    say("joueur positioner", console, systeme);

}

void add(struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console)
{
    int check = checkactifmob(data);
    if (check == -1)
    {
        check = data->nbmonstre;
        if(data->nbmonstre < 512)
        {
            data->nbmonstre++;
        }
    }

    data->mob[check].monstre.translation.x = (systeme->evenement.motion.x - data->mob[check].monstre.pict.pos.w/2) - data->map.pos.x;
    data->mob[check].monstre.translation.y = (screenh - systeme->evenement.motion.y - data->mob[check].monstre.pict.pos.h/2) - data->map.pos.y;
    data->mob[check].monstre.pict.pos.w = ESP_getwidth(systeme->ActiveEspece, systeme);
    data->mob[check].monstre.pict.pos.h = ESP_gethight(systeme->ActiveEspece, systeme);
    data->mob[check].old.w = ESP_getwidth(systeme->ActiveEspece, systeme);
    data->mob[check].old.h = ESP_gethight(systeme->ActiveEspece, systeme);
    data->mob[check].monstre.pict.texture = ESP_gettexture(systeme->ActiveEspece, systeme);
    strcpy(data->mob[check].name, ESP_getname(systeme->ActiveEspece , systeme));
    say(data->mob[check].name, console, systeme);
    data->mob[check].vie = ESP_getlife(systeme->ActiveEspece, systeme);
    data->mob[check].ID = systeme->ActiveEspece;
    data->mob[check].actif = true;
    say("monstre positionn�", console, systeme);
}
