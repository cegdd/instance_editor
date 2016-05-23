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

extern int screenh, screenw;

int editeur(struct DIVERSsysteme *systeme)
{
    int index;
    struct UI ui;
    struct CONSOLE console;
    initui(&ui);
    initconsole(&console, systeme);

    while(systeme->continuer)
    {
        /*effacage de l'écran*/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
        SDL_GetMouseState(&systeme->pointeur.pos.x, &systeme->pointeur.pos.y);
        /*reverse for OpenGL*/
        systeme->pointeur.pos.y = (systeme->pointeur.pos.y - screenh + systeme->pointeur.pos.h) * -1;

        boucleevent(systeme, &ui, &console);
        pointeur(systeme, &ui);

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
