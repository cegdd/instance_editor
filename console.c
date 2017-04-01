#include <string.h>
#include <stdio.h>

#include "console.h"

extern int screenh, screenw;

void initconsole(struct CONSOLE *console, struct DIVERSsysteme *systeme)
{
    int index;

    setPos4(&console->console.pos, 0, 12, screenw, 105);
    setPos4(&console->shooton.pos, 0, 0, screenw, 12);
    setPos4(&console->shootoff.pos, 0, 0, screenw, 12);
    setPos4(&console->cursor.pos, 0, 0, 2, 12);

    console->console.texture = loadTexture ("rs/ui/console.png");
    console->shooton.texture = loadTexture ("rs/ui/shootboxon.png");
    console->shootoff.texture = loadTexture ("rs/ui/shootboxoff.png");
    console->cursor.texture = loadTexture ("rs/divers/curseur.png");

    console->actif = 9;
    console->curseur = 0;
    console->answered = false;
    console->active = true;

    for (index = 0 ; index < 10 ; index++)
    {
        console->indice[index] = index;
        memset(console->string[index], '\0', 1024);
        console->texte[index].img.texture = imprime (console->string[index], screenw, NOIR, systeme, &console->texte[index].lenght, &console->texte[index].high);
        setPos4(&console->pos[index], 0, (index*10)+10, console->texte[index].lenght, 10);
        copypos(&console->pos[index], &console->texte[index].img.pos);
    }
    memset(console->tampon, '\0', 1024);
    memset(console->TamponToCursor, '\0', 1024);
    memset(console->lastanswer, '\0', 1024);

    console->ecris.img.texture = imprime (console->tampon, screenw, BLANC, systeme, &console->ecris.lenght, &console->ecris.high);
    setPos4(&console->ecris.img.pos, 0, 0, console->ecris.lenght, 10);

    if (glIsTexture(console->console.texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }
}
