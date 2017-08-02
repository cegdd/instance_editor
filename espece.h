#ifndef ESPECEH
#define ESPECEH

#include <GL/gl.h>
#include <GL/glu.h>

#include "bouton.h"



struct DIVERSsysteme;

struct ESPECE
{
    int vie;
    int Rvision;
    int vitesse;
    int dps;
    int Ratk;
    int hitlaps;

    char name[64];
    char imgpath[128];

    struct pict pict;
    struct BOUTON bouton;
};

void ESP_refreshmob(struct DIVERSsysteme *systeme);
void ESP_create(struct CONSOLE *console, struct DIVERSsysteme *systeme);
void ESP_delete(struct DIVERSsysteme *systeme, struct DATA *data);

void ESP_setlife(int life, int index, struct DIVERSsysteme *systeme);
void ESP_setimgpath(char *buffer, int index, struct DIVERSsysteme *systeme);
void ESP_setboutonstate(int state, int index, struct DIVERSsysteme *systeme);
void ESP_setdetailboutonstate(int state, int index, int indexdetail,  struct DIVERSsysteme *systeme);
void ESP_setname(char* buffer, int index, struct DIVERSsysteme *systeme);

void ESP_drawthumb(struct DIVERSsysteme *systeme);


struct BOUTON* ESP_getbouton_nom(int index, struct DIVERSsysteme *systeme);
struct BOUTON* ESP_getbouton_vie(int index, struct DIVERSsysteme *systeme);
struct BOUTON* ESP_getbouton_imgpath(int index, struct DIVERSsysteme *systeme);
struct SDL_Rect* ESP_getboutonpos(int index, struct DIVERSsysteme *systeme);
int ESP_getwidth(int index, struct DIVERSsysteme *systeme);
int ESP_gethight(int index, struct DIVERSsysteme *systeme);
GLuint ESP_gettexture(int index, struct DIVERSsysteme *systeme);
int ESP_getlife(int index, struct DIVERSsysteme *systeme);
char* ESP_getname(int index, struct DIVERSsysteme *systeme);
int ESP_getboutonstate(int index, struct DIVERSsysteme *systeme);
int ESP_getdetailboutonstate(int index, int indexdetail,  struct DIVERSsysteme *systeme);
struct SDL_Rect* ESP_getdetailboutonpos(int index, int indexdetail, struct DIVERSsysteme *systeme);
char* ESP_getimgpath(int index, struct DIVERSsysteme *systeme);

#endif
