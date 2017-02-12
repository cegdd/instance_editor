#include <stdio.h>
#include "core.h"
#include "image.h"
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

void ESP_refreshmob(struct DIVERSsysteme *systeme)
{
    char buffer[1024] = {'\0'};
    int i;

    for (i = 0 ; i < systeme->nbcreature ; i++)
    {
         systeme->creature[i].bouton.texture = imprime(systeme->creature[i].name, 114, BLANC, systeme, &systeme->creature[i].bouton.pos.w, &systeme->creature[i].bouton.pos.h);
         setPos2(&systeme->creature[i].bouton.pos,screenw-396, screenh-70-(i*22));

         sprintf(buffer, "rs/bestiaire/%s", systeme->creature[i].imgpath);
         systeme->creature[i].pict.texture =loadTextureandsize(buffer, &systeme->creature[i].pict.pos);
         systeme->creature[i].bt_imgpath.texte.img.texture = imprime(buffer, 114, BLANC, systeme, &systeme->creature[i].bt_imgpath.texte.img.pos.w, &systeme->creature[i].bt_imgpath.texte.img.pos.h);
         setPos2(&systeme->creature[i].bt_imgpath.texte.img.pos,1100, screenh-170);
         //copie de la texture+pos de "texte" a "bouton"
         systeme->creature[i].bt_imgpath.bouton.texture = systeme->creature[i].bt_imgpath.texte.img.texture;
         copypos(&systeme->creature[i].bt_imgpath.texte.img.pos, &systeme->creature[i].bt_imgpath.bouton.pos);

         sprintf(buffer, "vie : %d", systeme->creature[i].vie);
         systeme->creature[i].bt_vie.texte.img.texture = imprime(buffer, 114, BLANC, systeme, &systeme->creature[i].bt_vie.texte.img.pos.w, &systeme->creature[i].bt_vie.texte.img.pos.h);
         setPos2(&systeme->creature[i].bt_vie.texte.img.pos,1100, screenh-190);
         //copie de la texture+pos de "texte" a "bouton"
         systeme->creature[i].bt_vie.bouton.texture = systeme->creature[i].bt_vie.texte.img.texture;
         copypos(&systeme->creature[i].bt_vie.texte.img.pos, &systeme->creature[i].bt_vie.bouton.pos);

        systeme->creature[i].detail[systeme->nbdetail] = &systeme->creature[i].bt_imgpath.bouton;
        systeme->creature[i].detail[systeme->nbdetail] = &systeme->creature[i].bt_vie.bouton;
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

        systeme->nbcreature++;
        sprintf(buffer, "monstre %s ajouté avec succès", console->lastanswer);
        say(buffer, console ,systeme);
        ESP_refreshmob(systeme);
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
     ESP_refreshmob(systeme);
}
