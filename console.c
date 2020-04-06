#include <string.h>
#include <stdio.h>

#include "console.h"
#include "systeme.h"

#include <LIBcegdd_ui.h>

extern int screenh, screenw;

void initconsole(struct CONSOLE *console, struct DIVERSsysteme *systeme)
{
    int index;

    CEGDD_UI_setPos4(&console->console.pos, 0, 12, screenw, 105);
    CEGDD_UI_setPos4(&console->shooton.pos, 0, 0, screenw, 12);
    CEGDD_UI_setPos4(&console->shootoff.pos, 0, 0, screenw, 12);
    CEGDD_UI_setPos4(&console->cursor.pos, 0, 0, 2, 12);

    console->console.texture = CEGDD_UI_loadTexture     ("rs/ui/console.png");
    console->shooton.texture = CEGDD_UI_loadTexture     ("rs/ui/shootboxon.png");
    console->shootoff.texture = CEGDD_UI_loadTexture    ("rs/ui/shootboxoff.png");
    console->cursor.texture = CEGDD_UI_loadTexture      ("rs/divers/curseur.png");

    console->actif = 9;
    console->curseur = 0;
    console->answered = false;
    console->active = true;

    for (index = 0 ; index < 10 ; index++)
    {
        console->indice[index] = index;
        memset(console->string[index], '\0', 1024);
        console->texte[index].img.texture = CEGDD_UI_imprime(console->string[index], screenw, &systeme->noir, systeme->police1, &console->texte[index].lenght, &console->texte[index].high);
        CEGDD_UI_setPos4(&console->pos[index], 0, (index*10)+10, console->texte[index].lenght, 10);
        copypos(&console->pos[index], &console->texte[index].img.pos);
    }
    memset(console->tampon, '\0', 1024);
    memset(console->TamponToCursor, '\0', 1024);
    memset(console->lastanswer, '\0', 1024);

    console->ecris.img.texture = CEGDD_UI_imprime (console->tampon, screenw, &systeme->blanc, systeme->police1, &console->ecris.lenght, &console->ecris.high);
    CEGDD_UI_setPos4(&console->ecris.img.pos, 0, 0, console->ecris.lenght, 10);

    if (glIsTexture(console->console.texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }
}
