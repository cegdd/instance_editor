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

int ESP_getlife(int index, struct DIVERSsysteme *systeme)
{
    return systeme->creature[index].vie;
}

char* ESP_getname(int index, struct DIVERSsysteme *systeme)
{
    return systeme->creature[index].name;
}

struct SDL_Rect* ESP_getboutonpos(int index, struct DIVERSsysteme *systeme)
{
    return &systeme->creature[index].bouton.pos;
}

int ESP_getboutonstate(int index, struct DIVERSsysteme *systeme)
{
        return systeme->creature[index].bouton.etat;
}

void ESP_setboutonstate(int state, int index, struct DIVERSsysteme *systeme)
{
    systeme->creature[index].bouton.etat = state;
}

int ESP_getdetailboutonstate(int index, int indexdetail,  struct DIVERSsysteme *systeme)
{
    return systeme->creature[index].detail[indexdetail]->etat;
}

void ESP_setdetailboutonstate(int state, int index, int indexdetail,  struct DIVERSsysteme *systeme)
{
    systeme->creature[index].detail[indexdetail]->etat = state;
}

struct SDL_Rect* ESP_getdetailboutonpos(int index, int indexdetail, struct DIVERSsysteme *systeme)
{
    return &systeme->creature[index].detail[indexdetail]->pos;
}

char* ESP_getimgpath(int index, struct DIVERSsysteme *systeme)
{
    return systeme->creature[index].imgpath;
}

void ESP_setname(char* buffer, int index, struct DIVERSsysteme *systeme)
{
    sprintf(systeme->creature[index].name, buffer);
}
