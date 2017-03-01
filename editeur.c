#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "struct.h"
#include "tableau.h"
#include "evenement.h"
#include "image.h"
#include "systeme.h"
#include "clavier.h"
#include "save.h"
#include "core.h"
#include "editeur.h"
#include "espece.h"
#include "ui.h"

extern int screenh, screenw;

int editeur(struct DIVERSsysteme *systeme)
{
    int index;
    struct UI ui;
    struct CONSOLE console;
    struct DATA data;
    initui(&ui, systeme);
    initconsole(&console, systeme);
    initdata(&data);

    while(systeme->continuer)
    {
        /*effacage de l'écran*/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
        SDL_GetMouseState(&systeme->pointeur.pos.x, &systeme->pointeur.pos.y);
        /*reverse for OpenGL*/
        systeme->pointeur.pos.y = (systeme->pointeur.pos.y - screenh + systeme->pointeur.pos.h) * -1;

        boucleevent(systeme, &ui, &console, &data);
        pointeur(systeme, &ui, &data);

        if (systeme->asked)
        {
            if(systeme->askID == 4)
            {
                loadingmap(&console, systeme, &data);
            }
            else if(systeme->askID == 0)
            {
                createproject(&console, systeme, &data);
                ui.ListeBouton[0].etat = B_IMPOSSIBLE;
                ui.ListeBouton[2].etat = B_IMPOSSIBLE;
            }
            else if(systeme->askID == 3)
            {
                saveproject(&console, systeme, &data);
            }
            else if(systeme->askID == 2)
            {
                loadproject(&console, systeme, &data);
                ui.ListeBouton[0].etat = B_IMPOSSIBLE;
                ui.ListeBouton[2].etat = B_IMPOSSIBLE;
            }
            else if(systeme->askID == 8)
            {
                ESP_create(&console, systeme);
                ESP_refreshmob(systeme);
            }
            else if(systeme->askID == 11)
            {
                if (console.answered)
                {
                    systeme->asked = true;
                    console.answered = false;

                    ESP_setimgpath(console.lastanswer, systeme->activecreature, systeme);
                    ESP_refreshmob(systeme);
                    ESP_updateUI(systeme->activecreature, systeme, &ui);
                }
            }
            else if(systeme->askID == 12)
            {
                if (console.answered)
                {
                    systeme->asked = true;
                    console.answered = false;

                    ESP_setlife(atoi(console.lastanswer), systeme->activecreature, systeme);
                    ESP_refreshmob(systeme);
                    ESP_updateUI(systeme->activecreature, systeme, &ui);
                }
            }
        }

        if (glIsTexture(data.map.texture))
        {
            data.map.pos.x = data.map.x + systeme->origine.x;
            data.map.pos.y = data.map.y + systeme->origine.y;
            draw_pict(&data.map);
        }
        if (data.joueuractif)
        {
            draw_hookpict(&data.joueur, &data.map.pos);
        }
        for(index = 0 ; index < data.nbmonstre ; index++)
        {
            if(data.mob[index].actif == true)
            {
                if(data.mob[index].selected == false)
                {
                    draw_hookpict(&data.mob[index].monstre, &data.map.pos);
                }
                else
                {
                    draw_hookpict_selected(&data.mob[index].monstre, &data.map.pos);
                }
            }
        }




        //   ui ************************************

        if (systeme->projetouvert == true && ui.ListeBouton[4].etat == B_IMPOSSIBLE)
        {
            ui.ListeBouton[4].etat = B_NORMAL;
            ui.ListeBouton[3].etat = B_NORMAL;
            ui.ListeBouton[5].etat = B_NORMAL;
            ui.ListeBouton[6].etat = B_NORMAL;
        }

        draw_button(&ui.ListeBouton[0]);
        draw_button(&ui.ListeBouton[1]);
        draw_button(&ui.ListeBouton[3]);
        draw_button(&ui.ListeBouton[4]);
        draw_button(&ui.ListeBouton[2]);
        draw_button(&ui.ListeBouton[5]);
        draw_button(&ui.ListeBouton[6]);

        if (UI_getslidestate(&ui) != UI_close)
        {
            UI_drawslide(&ui, systeme, &data);
        }

        draw_pict(&console.console);
        if (console.active)
        {
            draw_pict(&console.shooton);
        }
        else
        {
            draw_pict(&console.shootoff);
        }
        for(index = 0 ; index < 10 ; index++)
        {
            draw_pict(&console.texte[index].img);
        }
        if(console.tampon[0] != '\0')
        {
        console.ecris.img.texture = imprime (console.tampon, screenw, BLANC, systeme, &console.ecris.lenght, &console.ecris.high);
        console.ecris.img.pos.w = console.ecris.lenght;

        draw_pict(&console.ecris.img);
        }

        if((SDL_GetTicks()/1000) % 2 == 0)
        {
            TTF_SizeText(systeme->police1,console.TamponToCursor,&console.LenToCursor,NULL);
            console.cursor.pos.x = console.ecris.img.pos.x + console.LenToCursor;

            draw_pict(&console.cursor);
        }

        if (systeme->tookmob == true)
        {
            setPos4(&systeme->temp,
                    systeme->pointeur.pos.x,
                    systeme->pointeur.pos.y + systeme->pointeur.pos.h,
                    ESP_getwidth(systeme->activecreature, systeme),
                    ESP_gethight(systeme->activecreature, systeme));
            draw(ESP_gettexture(systeme->activecreature, systeme), &systeme->temp);
        }

        glFlush();
        SDL_GL_SwapWindow(systeme->screen);

        SDL_Delay(25);
    }
    return EXIT_SUCCESS;
}

void loadingmap(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data)
{
    if (console->answered)
    {
        systeme->asked = false;
        char temp[128];
        console->answered = false;
        systeme->asked = false;

        sprintf(data->projectmap, "%s", console->lastanswer);
        sprintf(temp, "rs/map/%s.png", console->lastanswer);
        data->map.texture = loadTextureandsize(temp, &data->map.pos);
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
    data->map.texture = loadTextureandsize(temp, &data->map.pos);
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
        char temp2[128];

        systeme->asked = false;
        console->answered = false;
        systeme->asked = false;

        sprintf(data->projectname, "%s", console->lastanswer);
        sprintf(temp2, "projet \"%s\" crée\n", data->projectname);
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
    data->mob[check].monstre.pict.pos.w = ESP_getwidth(systeme->activecreature, systeme);
    data->mob[check].monstre.pict.pos.h = ESP_gethight(systeme->activecreature, systeme);
    data->mob[check].monstre.pict.texture = ESP_gettexture(systeme->activecreature, systeme);
    sprintf(data->mob[check].name, ESP_getname(systeme->activecreature , systeme));
    say(data->mob[check].name, console, systeme);
    data->mob[check].vie = ESP_getlife(systeme->activecreature, systeme);
    data->mob[check].ID = systeme->activecreature;
    data->mob[check].actif = true;
    say("monstre positionné", console, systeme);
}
