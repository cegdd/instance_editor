#ifndef ESPECEH
#define ESPECEH

#include "struct.h"

struct DIVERSsysteme;

struct ESPECE
{
    int vie;

    char name[64];
    char imgpath[128];

    struct pict pict;
    struct BOUTON bouton;
    struct BOUTON_TEXTE bt_vie;
    struct BOUTON_TEXTE bt_imgpath;

    struct BOUTON *detail[64];
};

/*
char* ESP_getimgpath(int index, struct DIVERSsysteme *systeme);*/
void ESP_setimgpath(char *string, int index, struct DIVERSsysteme *systeme);
struct BOUTON* ESP_getbouton_nom(int index, struct DIVERSsysteme *systeme);
struct BOUTON* ESP_getbouton_vie(int index, struct DIVERSsysteme *systeme);
struct BOUTON* ESP_getbouton_imgpath(int index, struct DIVERSsysteme *systeme);
void ESP_drawthumb(struct DIVERSsysteme *systeme);
void ESP_setlife(int life, int index, struct DIVERSsysteme *systeme);
int ESP_getwidth(int index, struct DIVERSsysteme *systeme);
int ESP_gethight(int index, struct DIVERSsysteme *systeme);
GLuint ESP_gettexture(int index, struct DIVERSsysteme *systeme);
#endif
