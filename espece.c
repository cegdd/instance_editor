#include <stdio.h>
#include "core.h"
#include "image.h"

/*
char* ESP_getimgpath(int index, struct DIVERSsysteme *systeme)
{
    return &systeme->creature[index].imgpath;
}
*/
void ESP_setimgpath(char *string, int index, struct DIVERSsysteme *systeme)
{
    sprintf (systeme->creature[index].imgpath, string);
}

struct BOUTON* ESP_getbouton_nom(int index, struct DIVERSsysteme *systeme)
{
    return &systeme->creature[index].bouton;
};

struct BOUTON* ESP_getbouton_vie(int index, struct DIVERSsysteme *systeme)
{
    return &systeme->creature[index].bt_vie.bouton;
};


struct BOUTON* ESP_getbouton_imgpath(int index, struct DIVERSsysteme *systeme)
{
    return &systeme->creature[index].bt_imgpath.bouton;
};

void ESP_drawthumb(struct DIVERSsysteme *systeme)
{
    draw_limitedpict(&systeme->creature[systeme->activecreature].pict, &systeme->pcreature);
}

void ESP_setlife(int life, int index, struct DIVERSsysteme *systeme)
{
    systeme->creature[index].vie = life;
}

int ESP_getwidth(int index, struct DIVERSsysteme *systeme)
{
    return systeme->creature[index].pict.pos.w;
}

int ESP_gethight(int index, struct DIVERSsysteme *systeme)
{
    return systeme->creature[index].pict.pos.h;
}

GLuint ESP_gettexture(int index, struct DIVERSsysteme *systeme)
{
    return systeme->creature[index].pict.texture;
}

