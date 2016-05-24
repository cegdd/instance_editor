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
#include "editeur.h"

extern int screenh, screenw;

int editeur(struct DIVERSsysteme *systeme)
{
    int index;
    struct UI ui;
    struct CONSOLE console;
    struct DATA data;
    initui(&ui);
    initconsole(&console, systeme);
    initdata(&data);

    while(systeme->continuer)
    {
        /*effacage de l'écran*/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
        SDL_GetMouseState(&systeme->pointeur.pos.x, &systeme->pointeur.pos.y);
        /*reverse for OpenGL*/
        systeme->pointeur.pos.y = (systeme->pointeur.pos.y - screenh + systeme->pointeur.pos.h) * -1;

        boucleevent(systeme, &ui, &console);
        pointeur(systeme, &ui);

        if (systeme->mapasked)
        {
            loadingmap(&console, systeme, &data);
        }

        draw_button(&ui.creer);
        draw_button(&ui.quitter);

        draw_pict(&console.console);
        for(index = 0 ; index < 10 ; index++)
        {
            draw_pict(&console.texte[index].img);
        }
        console.ecris.img.texture = imprime (console.tampon, screenw, BLANC, systeme, &console.ecris.lenght, &console.ecris.high);
        console.ecris.img.pos.w = console.ecris.lenght;

        draw_pict(&console.ecris.img);

        glFlush();
        SDL_GL_SwapWindow(systeme->screen);

        SDL_Delay(10);
    }
    return EXIT_SUCCESS;
}

void loadingmap(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data)
{
    char temp[128];
    if (console->answered)
    {
        console->answered = false;
        systeme->mapasked = false;

        sprintf(temp, "rs/map/%s", console->lastanswer);
        data->map.texture = loadTexture(temp);

        if(glIsTexture(data->map.texture))
        {
            say("texture successfuly loaded", console, systeme);
        }
        else
        {
            say("ERROR : texture not successfuly loaded", console, systeme);
        }
    }
}
