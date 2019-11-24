#include <stdio.h>

#include "systeme.h"

extern int screenh, screenw;

void ESP_setimgpath(char *buffer, int index, struct DIVERSsysteme *systeme)
{
    sprintf (systeme->creature[index].imgpath, buffer);
}

struct BOUTON* ESP_getbouton_nom(int index, struct DIVERSsysteme *systeme)
{
    return &systeme->creature[index].bouton;
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


char* ESP_getimgpath(int index, struct DIVERSsysteme *systeme)
{
    return systeme->creature[index].imgpath;
}

void ESP_setname(char* buffer, int index, struct DIVERSsysteme *systeme)
{
    sprintf(systeme->creature[index].name, buffer);
}

void ESP_refreshmob(struct DIVERSsysteme *systeme)
{
    char buffer[1024] = {'\0'};
    int i;

    for (i = 0 ; i < systeme->nbcreature ; i++)
    {
         systeme->creature[i].bouton.texture = imprime(systeme->creature[i].name, 114, BLANC, systeme, &systeme->creature[i].bouton.pos.w, &systeme->creature[i].bouton.pos.h);
         setPos2(&systeme->creature[i].bouton.pos,screenw-396, 698-(i*22));

         sprintf(buffer, "rs/bestiaire/%s", systeme->creature[i].imgpath);
         systeme->creature[i].pict.texture =loadTextureandsize(buffer, &systeme->creature[i].pict.pos);
    }
}

void ESP_create(struct CONSOLE *console, struct DIVERSsysteme *systeme)
{

    if (console->answered)
    {
        char buffer[1024];

        systeme->asked = false;
        console->answered = false;

        sprintf(systeme->creature[systeme->nbcreature].imgpath, "noimage.png");
        sprintf(systeme->creature[systeme->nbcreature].name, "%s", console->lastanswer);
        systeme->creature[systeme->nbcreature].vie = 0;
        systeme->creature[systeme->nbcreature].dps = 0;
        systeme->creature[systeme->nbcreature].Ratk = 0;
        systeme->creature[systeme->nbcreature].Rvision = 0;
        systeme->creature[systeme->nbcreature].vitesse = 0;
        systeme->creature[systeme->nbcreature].hitlaps = 100;

        systeme->activecreature = systeme->nbcreature;
        systeme->nbcreature++;
        sprintf(buffer, "monstre %s ajouté avec succès", console->lastanswer);
        say(buffer, console ,systeme);
    }
}

void ESP_delete(struct DIVERSsysteme *systeme, struct DATA *data)
{
    int i;

        for(i = 0 ; i < data->nbmonstre ; i++)
    {
        if (data->mob[i].ID == systeme->activecreature)
        {
            data->mob[i].actif = false;
        }
    }

    for(i = systeme->activecreature+1 ; i < systeme->nbcreature ; i++)
    {
        systeme->creature[i-1].vie = systeme->creature[i].vie;
        sprintf(systeme->creature[i-1].imgpath, "%s", systeme->creature[i].imgpath);
        sprintf(systeme->creature[i-1].name, "%s", systeme->creature[i].name);
    }


    systeme->nbcreature--;
}
